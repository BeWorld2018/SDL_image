#!/usr/bin/env python3
#
# Checks every vector of sdl3_image.library against MorphOS/sdk/fd/sdl3_image_lib.fd:
#   - jump table entry N (FuncTable in sdl3_image.library.db) is LIB_<name of fd entry N>
#   - LIB_<name> calls <name> (the SDL3_image function itself)
#
#   python3 build-scripts/check_morphos_lvo.py [sdl3_image.library.db]
#   (Makefile.mos target "checklvo")

import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
FD = os.path.join(ROOT, 'MorphOS', 'sdk', 'fd', 'sdl3_image_lib.fd')
OBJDUMP = os.environ.get('OBJDUMP', 'ppc-morphos-objdump')


def run(*args):
    return subprocess.run([OBJDUMP] + list(args), check=True,
                          stdout=subprocess.PIPE, universal_newlines=True).stdout


def fd_entries():
    out, bias = [], None
    for line in open(FD):
        line = line.strip()
        if line.startswith('##bias'):
            bias = int(line.split()[1])
        m = re.match(r'^(\w+)\(', line)
        if m and not line.startswith('*'):
            out.append(m.group(1))
    return out


def main():
    db = sys.argv[1] if len(sys.argv) > 1 else os.path.join(ROOT, 'sdl3_image.library.db')

    # symbols: .text offset -> name, and FuncTable offset in .rodata
    text, functable = {}, None
    for line in run('-t', db).splitlines():
        f = line.split()
        if len(f) >= 5 and f[-2] != '*ABS*':
            if '.text' in f and f[-1].startswith(('LIB_', 'IMG_')) or f[-1] == 'LIB_Unsupported':
                text.setdefault(int(f[0], 16), f[-1])
            if f[-1] == 'FuncTable':
                functable = int(f[0], 16)
    if functable is None:
        sys.exit('FuncTable not found in %s' % db)

    # .rodata relocations: FuncTable slots
    slots = {}
    for line in run('-r', '-j', '.rodata', db).splitlines():
        m = re.match(r'^([0-9a-f]{8}) R_PPC_ADDR32\s+\.text(?:\+0x([0-9a-f]+))?$', line.strip())
        if m:
            slots[int(m.group(1), 16)] = int(m.group(2) or '0', 16)

    # FuncTable: BEGIN, 32BIT_NATIVE, Open, Close, Expunge, Reserved, -1, 32BIT_SYSTEMV, ...
    first = functable + 8 * 4
    entries = fd_entries()
    errors = 0
    stubs = {}
    for i, name in enumerate(entries):
        off = first + 4 * i
        if off not in slots:
            print('slot %4d %-40s: no function pointer' % (i, name))
            errors += 1
            continue
        got = text.get(slots[off], '.text+0x%x' % slots[off])
        if name.startswith('private_reserved'):
            want = 'LIB_Reserved'
        elif name.startswith('private_'):
            real = name[len('private_'):]
            want = ('LIB_' + real, 'LIB_Unsupported')
        else:
            want = 'LIB_' + name
        ok = got in want if isinstance(want, tuple) else got == want
        if not ok:
            print('slot %4d %-40s: points to %s' % (i, name, got))
            errors += 1
        elif got.startswith('LIB_IMG_'):
            stubs[got] = got[len('LIB_'):]

    # each stub must call its SDL function
    calls, cur = {}, None
    for line in run('-d', '--no-show-raw-insn', db).splitlines():
        m = re.match(r'^[0-9a-f]{8} <(\w+)>:$', line)
        if m:
            cur = m.group(1) if m.group(1) in stubs else None
            continue
        if cur and cur not in calls:
            m = re.search(r'\sbl\s+[0-9a-f]+ <(\w+)>', line)
            if m and m.group(1) != '__restore_r13':
                calls[cur] = m.group(1)
    for stub, target in sorted(stubs.items()):
        if calls.get(stub) != target:
            print('%-44s calls %s, not %s' % (stub, calls.get(stub), target))
            errors += 1

    print('%d vectors, %d stubs checked, %d errors' % (len(entries), len(stubs), errors))
    sys.exit(1 if errors else 0)


if __name__ == '__main__':
    main()
