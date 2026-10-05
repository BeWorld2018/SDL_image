#ifndef CLIB_SDL2_IMAGE_PROTOS_H
#define CLIB_SDL2_IMAGE_PROTOS_H

/*
	sdl2_image.library prototypes, in FD order.
	Must match include/SDL_image.h exactly (cvinclude.pl builds the glue
	libraries and ppcinline/sdl2_image.h from this file).
	Like the SDL2 SDK, expects -I<prefix>/include/SDL2.
*/

#include <SDL.h>
#include <SDL_image.h>

#ifdef __cplusplus
extern "C" {
#endif

SDL_Surface * IMG_LoadTyped_RW(SDL_RWops *src, int freesrc, const char *type);
SDL_Surface * IMG_Load(const char *file);
SDL_Surface * IMG_Load_RW(SDL_RWops *src, int freesrc);
int IMG_SavePNG(SDL_Surface *surface, const char *file);
int IMG_SavePNG_RW(SDL_Surface *surface, SDL_RWops *dst, int freedst);
SDL_Texture * IMG_LoadTexture(SDL_Renderer *renderer, const char *file);
SDL_Texture * IMG_LoadTexture_RW(SDL_Renderer *renderer, SDL_RWops *src, int freesrc);
SDL_Texture * IMG_LoadTextureTyped_RW(SDL_Renderer *renderer, SDL_RWops *src, int freesrc, const char *type);
int IMG_isBMP(SDL_RWops *src);
int IMG_isPNM(SDL_RWops *src);
int IMG_isXPM(SDL_RWops *src);
int IMG_isXCF(SDL_RWops *src);
int IMG_isPCX(SDL_RWops *src);
int IMG_isGIF(SDL_RWops *src);
int IMG_isJPG(SDL_RWops *src);
int IMG_isTIF(SDL_RWops *src);
int IMG_isPNG(SDL_RWops *src);
int IMG_isLBM(SDL_RWops *src);
int IMG_isXV(SDL_RWops *src);
int IMG_isWEBP(SDL_RWops *src);
SDL_Surface * IMG_LoadBMP_RW(SDL_RWops *src);
SDL_Surface * IMG_LoadPNM_RW(SDL_RWops *src);
SDL_Surface * IMG_LoadXPM_RW(SDL_RWops *src);
SDL_Surface * IMG_LoadXCF_RW(SDL_RWops *src);
SDL_Surface * IMG_LoadPCX_RW(SDL_RWops *src);
SDL_Surface * IMG_LoadGIF_RW(SDL_RWops *src);
SDL_Surface * IMG_LoadJPG_RW(SDL_RWops *src);
SDL_Surface * IMG_LoadTIF_RW(SDL_RWops *src);
SDL_Surface * IMG_LoadPNG_RW(SDL_RWops *src);
SDL_Surface * IMG_LoadTGA_RW(SDL_RWops *src);
SDL_Surface * IMG_LoadLBM_RW(SDL_RWops *src);
SDL_Surface * IMG_LoadXV_RW(SDL_RWops *src);
SDL_Surface * IMG_LoadWEBP_RW(SDL_RWops *src);
SDL_Surface * IMG_ReadXPMFromArray(char **xpm);
const SDL_version * IMG_Linked_Version(void);
int IMG_Init(int flags);
void IMG_Quit(void);
int IMG_isSVG(SDL_RWops *src);
SDL_Surface * IMG_LoadSVG_RW(SDL_RWops *src);
int IMG_SaveJPG(SDL_Surface *surface, const char *file, int quality);
int IMG_SaveJPG_RW(SDL_Surface *surface, SDL_RWops *dst, int freedst, int quality);
IMG_Animation * IMG_LoadAnimation(const char *file);
IMG_Animation * IMG_LoadAnimation_RW(SDL_RWops *src, int freesrc);
IMG_Animation * IMG_LoadAnimationTyped_RW(SDL_RWops *src, int freesrc, const char *type);
void IMG_FreeAnimation(IMG_Animation *anim);
IMG_Animation * IMG_LoadGIFAnimation_RW(SDL_RWops *src);
int IMG_isICO(SDL_RWops *src);
SDL_Surface * IMG_LoadICO_RW(SDL_RWops *src);
int IMG_isCUR(SDL_RWops *src);
SDL_Surface * IMG_LoadCUR_RW(SDL_RWops *src);
int IMG_isQOI(SDL_RWops *src);
SDL_Surface * IMG_LoadQOI_RW(SDL_RWops *src);
int IMG_isJXL(SDL_RWops *src);
SDL_Surface * IMG_LoadJXL_RW(SDL_RWops *src);
SDL_Surface * IMG_ReadXPMFromArrayToRGB888(char **xpm);
int IMG_isAVIF(SDL_RWops *src);
SDL_Surface * IMG_LoadAVIF_RW(SDL_RWops *src);
SDL_Surface * IMG_LoadSizedSVG_RW(SDL_RWops *src, int width, int height);
IMG_Animation * IMG_LoadWEBPAnimation_RW(SDL_RWops *src);

#ifdef __cplusplus
}
#endif

#endif /* CLIB_SDL2_IMAGE_PROTOS_H */
