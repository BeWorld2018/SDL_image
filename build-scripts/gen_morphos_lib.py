#!/usr/bin/env python3
#
# Generates the sdl3_image.library glue from include/SDL3_image/SDL_image.h:
#
#   MorphOS/sdk/fd/sdl3_image_lib.fd       function descriptor (LVO order)
#   MorphOS/sdk/clib/sdl3_image_protos.h   prototypes for cvinclude.pl
#   MorphOS/IMG_stubs.h                    library jump table / trampolines
#
# The LVO order is the src/SDL_image.sym order: upstream appends new
# functions at its end, so offsets never move across SDL3_image updates.
#
#   python3 build-scripts/gen_morphos_lib.py [--defined symbols.txt]
#
# symbols.txt: one symbol per line, the functions the library objects
# define (Makefile.mos "glue" target: nm of libSDL3_image_lib.a). A function
# not built keeps its slot but becomes ##private and points to a stub
# returning 0. Without --defined, the previous classification in the .fd is
# kept.

import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
HEADER = os.path.join(ROOT, 'include', 'SDL3_image', 'SDL_image.h')
SYM = os.path.join(ROOT, 'src', 'SDL_image.sym')
CORE = os.path.join(ROOT, 'MorphOS')
FD = os.path.join(CORE, 'sdk', 'fd', 'sdl3_image_lib.fd')
CLIB = os.path.join(CORE, 'sdk', 'clib', 'sdl3_image_protos.h')
STUBS = os.path.join(CORE, 'IMG_stubs.h')

RESERVED = 4  # spare private slots before the SDL3_image functions

# SysV PPC: 64-bit integers take an aligned GPR pair (r3:r4, r5:r6, ...)
INT64 = {'Uint64', 'Sint64', 'uint64_t', 'int64_t', 'long long', 'unsigned long long'}
FLOATS = {'float', 'double'}

PROTO = re.compile(r'extern\s+SDL_DECLSPEC\s+(.*?)\s*\bSDLCALL\s+(\w+)\s*\((.*?)\)\s*;', re.S)


def split_top(s):
    """Split on commas outside parentheses."""
    out, depth, cur = [], 0, ''
    for c in s:
        if c == '(':
            depth += 1
        elif c == ')':
            depth -= 1
        if c == ',' and depth == 0:
            out.append(cur)
            cur = ''
        else:
            cur += c
    out.append(cur)
    return [x.strip() for x in out]


def needs_stack(params):
    """True when some arguments are passed on the stack (more than r3-r10
    or f1-f8): the trampoline then has to copy the caller's argument area."""
    gpr = fpr = 0
    if params != 'void':
        for p in split_top(params):
            t = re.sub(r'\w+\s*$', '', p).replace('const', ' ')
            t = ' '.join(t.split())
            if '*' in t:
                gpr += 1
            elif t in FLOATS:
                fpr += 1
            elif t in INT64:
                gpr += (gpr & 1) + 2
            else:
                gpr += 1
    return gpr > 8 or fpr > 8


def parse_header():
    protos = {}
    text = re.sub(r'/\*.*?\*/', '', open(HEADER, encoding='utf-8').read(), flags=re.S)
    for rc, name, params in PROTO.findall(text):
        params = ' '.join(params.split())
        if '...' in params:
            sys.exit('%s: variadic, not supported' % name)
        args = []
        if params and params != 'void':
            for p in split_top(params):
                args.append(re.search(r'(\w+)\s*(?:\[\])?$', p).group(1))
        else:
            params = 'void'
        protos[name] = {'rc': ' '.join(rc.split()), 'name': name,
                        'params': params, 'args': args}
    return protos


def sym_order():
    names = []
    for line in open(SYM):
        m = re.match(r'^\s*(IMG_\w+)\s*;', line)
        if m:
            names.append(m.group(1))
    return names


def previous_private():
    """Unbuilt functions as classified in the existing .fd."""
    private, state = set(), 'public'
    if not os.path.exists(FD):
        return set()
    for line in open(FD):
        line = line.strip()
        if line in ('##private', '##public'):
            state = line[2:]
        elif state == 'private' and line.startswith('private_IMG_'):
            private.add(line[len('private_'):line.index('(')])
    return private


def fix_inline(path):
    """Post-process cvinclude's ppcinline/sdl3_image.h: skip a macro when
    the name is already defined."""
    s = open(path).read()
    s = re.sub(r'^#define (\w+)(\(.*?)\n\n', r'#ifndef \1\n#define \1\2\n#endif\n\n',
               s, flags=re.M | re.S)
    open(path, 'w', newline='\n').write(s)


def main():
    if '--fix-inline' in sys.argv:
        fix_inline(sys.argv[sys.argv.index('--fix-inline') + 1])
        return

    protos = parse_header()
    order = sym_order()
    missing = [n for n in order if n not in protos]
    extra = [n for n in protos if n not in order]
    if missing or extra:
        sys.exit('SDL_image.sym and SDL_image.h differ: missing %s, extra %s' % (missing, extra))
    procs = [protos[n] for n in order]

    if '--defined' in sys.argv:
        path = sys.argv[sys.argv.index('--defined') + 1]
        defined = set(l.strip() for l in open(path) if l.strip())
        unsupported = set(p['name'] for p in procs if p['name'] not in defined)
    else:
        unsupported = previous_private()

    for d in (os.path.dirname(FD), os.path.dirname(CLIB)):
        os.makedirs(d, exist_ok=True)

    # ---- fd
    fd = ['##base _SDL3ImageBase', '##bias 30', '* sdl3_image.library',
          '* Generated by build-scripts/gen_morphos_lib.py from SDL_image.h, do not edit.',
          '##private']
    for i in range(RESERVED):
        fd.append('private_reserved%d()()' % (i + 1))
    fd.append('##public')
    state = 'public'
    for p in procs:
        priv = p['name'] in unsupported
        want = 'private' if priv else 'public'
        if want != state:
            fd.append('##' + want)
            state = want
        if priv:
            fd.append('private_%s()()' % p['name'])
        else:
            fd.append('%s(%s)(sysv,r12base)' % (p['name'], ','.join(p['args'])))
    if state != 'public':
        fd.append('##public')
    fd.append('##end')
    open(FD, 'w', newline='\n').write('\n'.join(fd) + '\n')

    # ---- clib
    cl = ['#ifndef CLIB_SDL3_IMAGE_PROTOS_H', '#define CLIB_SDL3_IMAGE_PROTOS_H', '',
          '/* Generated by build-scripts/gen_morphos_lib.py, do not edit. */', '',
          '#include <SDL3_image/SDL_image.h>', '']
    for p in procs:
        if p['name'] not in unsupported:
            cl.append('%s %s(%s);' % (p['rc'], p['name'], p['params']))
    cl += ['', '#endif /* CLIB_SDL3_IMAGE_PROTOS_H */']
    open(CLIB, 'w', newline='\n').write('\n'.join(cl) + '\n')

    # ---- stubs
    st = ['/* Generated by build-scripts/gen_morphos_lib.py, do not edit. */',
          '/* Jump table order: must match sdk/fd/sdl3_image_lib.fd */', '',
          '#undef STUB', '#undef STUB_STACK', '#undef STUB_UNSUPPORTED', '',
          '#if defined(GENERATE_STUBS)',
          '/* r12 = library base: set this opener\'s r13, registers go through untouched */',
          '#define STUB(name) extern int name(); int __saveds LIB_##name() { return name(); }',
          '/* Same with arguments on the stack: a stub frame would hide them from the',
          '   callee, so this one copies the caller\'s argument area (16 words) */',
          '#define STUB_STACK(name) asm("\\n\\t.section \\".text\\"\\n\\t.align 2\\n" \\',
          '\t"\\t.globl LIB_" #name "\\n\\t.type LIB_" #name ",@function\\nLIB_" #name ":\\n" \\',
          '\t"\\tstwu 1,-96(1)\\n\\tmflr 0\\n\\tstw 0,100(1)\\n\\tstw 13,88(1)\\n" \\',
          '\t' + ' '.join('"\\tlwz 0,%d(1)\\n\\tstw 0,%d(1)\\n"' % (104 + 4 * k, 8 + 4 * k) for k in range(16)) + ' \\',
          '\t"\\tlwz 13,36(12)\\n\\tbl " #name "\\n" \\',
          '\t"\\tlwz 0,100(1)\\n\\tlwz 13,88(1)\\n\\taddi 1,1,96\\n\\tmtlr 0\\n\\tblr\\n" \\',
          '\t"\\t.size LIB_" #name ",.-LIB_" #name "\\n");',
          '#define STUB_UNSUPPORTED(name)',
          '#elif defined(GENERATE_POINTERS)',
          '#define STUB(name) (APTR)&LIB_##name,',
          '#define STUB_STACK(name) (APTR)&LIB_##name,',
          '#define STUB_UNSUPPORTED(name) (APTR)&LIB_Unsupported,',
          '#else',
          '#define STUB(name) extern int LIB_##name();',
          '#define STUB_STACK(name) extern int LIB_##name();',
          '#define STUB_UNSUPPORTED(name)',
          '#endif', '']
    for p in procs:
        if p['name'] in unsupported:
            macro = 'STUB_UNSUPPORTED'
        elif needs_stack(p['params']):
            macro = 'STUB_STACK'
        else:
            macro = 'STUB'
        st.append('\t%s(%s)' % (macro, p['name']))
    open(STUBS, 'w', newline='\n').write('\n'.join(st) + '\n')

    print('%d functions, %d not built' % (len(procs), len(unsupported)))


if __name__ == '__main__':
    main()
