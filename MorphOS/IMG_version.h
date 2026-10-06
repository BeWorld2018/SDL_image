/*
 * sdl3_image.library version = SDL_image version: VERSION.REVISION =
 * SDL_image major.minor (the micro version is in $VER only).
 *
 * IMG_LIB_MAJOR/MINOR/MICRO come from include/SDL3_image/SDL_image.h,
 * passed by Makefile.mos and devenv/makefile.
 */
#if !defined(IMG_LIB_MAJOR) || !defined(IMG_LIB_MINOR) || !defined(IMG_LIB_MICRO)
#error "IMG_LIB_MAJOR/MINOR/MICRO not defined (see Makefile.mos)"
#endif

#define	str(s) #s
#define	xstr(s) str(s)
#define	VERSION	IMG_LIB_MAJOR
#define	REVISION	IMG_LIB_MINOR
#define	VERSTAG	"\0$VER: sdl3_image.library " xstr(VERSION) "." xstr(REVISION) " (" __AMIGADATE__ ") SDL_image " xstr(IMG_LIB_MAJOR) "." xstr(IMG_LIB_MINOR) "." xstr(IMG_LIB_MICRO) " (c) Bruno Peloille"
