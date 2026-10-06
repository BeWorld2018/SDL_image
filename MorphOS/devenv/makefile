# -lSDL3_image glue libraries for sdl3_image.library
#
#   lib/libSDL3_image.a             programs
#   lib/libb32/libSDL3_image.a      -mresident32 code
#   lib/libb32/libSDL3_image-nc.a   -mresident32, no constructor (SDL3ImageBase set by hand)
#
# Each archive = cvinclude.pl glue from ../sdk/fd/sdl3_image_lib.fd + sdl-startup.o

CC      = ppc-morphos-gcc-9 -noixemul
INCLUDE = -I../../include -I/gg/usr/local/include -I../sdk
CFLAGS  = -mcpu=750 -mtune=7450 -O2 $(INCLUDE) -Wall -Wno-pointer-sign -fno-strict-aliasing
AR      = ppc-morphos-ar
CVI     = /gg/bin/cvinclude.pl
FD      = ../sdk/fd/sdl3_image_lib.fd
CLIB    = ../sdk/clib/sdl3_image_protos.h
DEPS    = sdl-startup.c ../IMG_version.h

COMPILING = @echo "compiling $@..."
ARCHIVING = @echo "archiving $@..."

all: lib/libSDL3_image.a lib/libb32/libSDL3_image.a lib/libb32/libSDL3_image-nc.a

sdl-startup.o: $(DEPS)
	$(COMPILING)
	@$(CC) $(CFLAGS) -o $@ -c sdl-startup.c

sdl-startup-brel.o: $(DEPS)
	$(COMPILING)
	@$(CC) $(CFLAGS) -mresident32 -o $@ -c sdl-startup.c

sdl-startup-brel-nc.o: $(DEPS)
	$(COMPILING)
	@$(CC) $(CFLAGS) -mresident32 -o $@ -c sdl-startup.c -D__NO_SDL_CONSTRUCTORS

lib/libSDL3_image.a: sdl-startup.o $(FD) $(CLIB)
	$(ARCHIVING)
	@mkdir -p lib
	@-rm -f $@
	@$(CVI) --fd=$(FD) --clib=$(CLIB) --gluelib=$@ > /dev/null
	@$(AR) crus $@ sdl-startup.o

lib/libb32/libSDL3_image.a: sdl-startup-brel.o $(FD) $(CLIB)
	$(ARCHIVING)
	@mkdir -p lib/libb32
	@-rm -f $@
	@$(CVI) --fd=$(FD) --clib=$(CLIB) --brelgluelib=$@ > /dev/null
	@$(AR) crus $@ sdl-startup-brel.o

lib/libb32/libSDL3_image-nc.a: sdl-startup-brel-nc.o $(FD) $(CLIB)
	$(ARCHIVING)
	@mkdir -p lib/libb32
	@-rm -f $@
	@$(CVI) --fd=$(FD) --clib=$(CLIB) --brelgluelib=$@ > /dev/null
	@$(AR) crus $@ sdl-startup-brel-nc.o

clean:
	@-rm -rf lib *.s *.o

dump:
	ppc-morphos-objdump --disassemble-all --reloc lib/libSDL3_image.a >lib/libSDL3_image.s
