#ifndef SDL2_IMAGE_PROTOS
#define SDL2_IMAGE_PROTOS

#ifndef	_SDL_H
#include <SDL/SDL.h>
#endif

#include <SDL/SDL_image.h>

#ifdef __cplusplus
extern "C" {
#endif

/* This function gets the version of the dynamically linked SDL_image library.
   it should NOT be used to fill a version structure, instead you should
   use the SDL_IMAGE_VERSION() macro.
 */
const SDL_version *IMG_Linked_Version(void);

/* Load an image from an SDL data source.
   The 'type' may be one of: "BMP", "GIF", "PNG", etc.

   If the image format supports a transparent pixel, SDL will set the
   colorkey for the surface.  You can enable RLE acceleration on the
   surface afterwards by calling:
	SDL_SetColorKey(image, SDL_RLEACCEL, image->format->colorkey);
 */
SDL_Surface *IMG_LoadTyped_RW(SDL_RWops *src, int freesrc, char *type);
/* Convenience functions */
SDL_Surface *IMG_Load(const char *file);
SDL_Surface *IMG_Load_RW(SDL_RWops *src, int freesrc);

int IMG_SavePNG(SDL_Surface *surface, const char *file);
int IMG_SavePNG_RW(SDL_Surface *surface, SDL_RWops *dst, int freedst);

SDL_Texture *IMG_LoadTexture(SDL_Renderer *renderer, const char *file);
SDL_Texture *IMG_LoadTexture_RW(SDL_Renderer *renderer, SDL_RWops *src, int freesrc);
SDL_Texture *IMG_LoadTextureTyped_RW(SDL_Renderer *renderer, SDL_RWops *src, int freesrc, const char *type);

/* Functions to detect a file type, given a seekable source */
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

/* Individual loading functions */
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

int IMG_Init(int flags);
void IMG_Quit(void);
/* 2.0.5 */
int IMG_isSVG(SDL_RWops *src);
SDL_Surface * IMG_LoadSVG_RW(SDL_RWops *src);
int IMG_SaveJPG(SDL_Surface *surface, const char *file, int quality);
int IMG_SaveJPG_RW(SDL_Surface *surface, SDL_RWops *dst, int freedst, int quality);
/* 2.0.6 */
IMG_Animation * IMG_LoadAnimation(const char *file);
IMG_Animation * IMG_LoadAnimation_RW(SDL_RWops *src, int freesrc);
IMG_Animation * IMG_LoadAnimationTyped_RW(SDL_RWops *src, int freesrc, const char *type);
void IMG_FreeAnimation(IMG_Animation *anim);
 
/* Individual loading functions */
IMG_Animation * IMG_LoadGIFAnimation_RW(SDL_RWops *src);

#ifdef __cplusplus
}
#endif

#endif /* SDL2_IMAGE_PROTOS */
