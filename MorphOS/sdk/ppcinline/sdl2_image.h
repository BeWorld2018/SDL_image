/* Automatically generated header! Do not edit! */

#ifndef _PPCINLINE_SDL2_IMAGE_H
#define _PPCINLINE_SDL2_IMAGE_H

#ifndef __PPCINLINE_MACROS_H
#include <ppcinline/macros.h>
#endif /* !__PPCINLINE_MACROS_H */

#ifndef SDL2_IMAGE_BASE_NAME
#define SDL2_IMAGE_BASE_NAME SDL2ImageBase
#endif /* !SDL2_IMAGE_BASE_NAME */

#define IMG_Linked_Version() \
	({ \
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((const SDL_version *(*)(void))*(void**)(__base - 232))());\
	})

#define IMG_LoadTyped_RW(__p0, __p1, __p2) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		char * __t__p2 = __p2;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Surface *(*)(SDL_RWops *, int , char *))*(void**)(__base - 28))(__t__p0, __t__p1, __t__p2));\
	})

#define IMG_Load(__p0) \
	({ \
		const char * __t__p0 = __p0;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Surface *(*)(const char *))*(void**)(__base - 34))(__t__p0));\
	})

#define IMG_Load_RW(__p0, __p1) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Surface *(*)(SDL_RWops *, int ))*(void**)(__base - 40))(__t__p0, __t__p1));\
	})

#define IMG_SavePNG(__p0, __p1) \
	({ \
		SDL_Surface * __t__p0 = __p0;\
		const char * __t__p1 = __p1;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Surface *, const char *))*(void**)(__base - 46))(__t__p0, __t__p1));\
	})

#define IMG_SavePNG_RW(__p0, __p1, __p2) \
	({ \
		SDL_Surface * __t__p0 = __p0;\
		SDL_RWops * __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Surface *, SDL_RWops *, int ))*(void**)(__base - 52))(__t__p0, __t__p1, __t__p2));\
	})

#define IMG_LoadTexture(__p0, __p1) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		const char * __t__p1 = __p1;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Texture *(*)(SDL_Renderer *, const char *))*(void**)(__base - 58))(__t__p0, __t__p1));\
	})

#define IMG_LoadTexture_RW(__p0, __p1, __p2) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		SDL_RWops * __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Texture *(*)(SDL_Renderer *, SDL_RWops *, int ))*(void**)(__base - 64))(__t__p0, __t__p1, __t__p2));\
	})

#define IMG_LoadTextureTyped_RW(__p0, __p1, __p2, __p3) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		SDL_RWops * __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		const char * __t__p3 = __p3;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Texture *(*)(SDL_Renderer *, SDL_RWops *, int , const char *))*(void**)(__base - 70))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define IMG_isBMP(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_RWops *))*(void**)(__base - 76))(__t__p0));\
	})

#define IMG_isPNM(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_RWops *))*(void**)(__base - 82))(__t__p0));\
	})

#define IMG_isXPM(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_RWops *))*(void**)(__base - 88))(__t__p0));\
	})

#define IMG_isXCF(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_RWops *))*(void**)(__base - 94))(__t__p0));\
	})

#define IMG_isPCX(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_RWops *))*(void**)(__base - 100))(__t__p0));\
	})

#define IMG_isGIF(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_RWops *))*(void**)(__base - 106))(__t__p0));\
	})

#define IMG_isJPG(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_RWops *))*(void**)(__base - 112))(__t__p0));\
	})

#define IMG_isTIF(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_RWops *))*(void**)(__base - 118))(__t__p0));\
	})

#define IMG_isPNG(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_RWops *))*(void**)(__base - 124))(__t__p0));\
	})

#define IMG_isLBM(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_RWops *))*(void**)(__base - 130))(__t__p0));\
	})

#define IMG_isXV(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_RWops *))*(void**)(__base - 136))(__t__p0));\
	})

#define IMG_isWEBP(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_RWops *))*(void**)(__base - 142))(__t__p0));\
	})

#define IMG_LoadBMP_RW(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Surface *(*)(SDL_RWops *))*(void**)(__base - 148))(__t__p0));\
	})

#define IMG_LoadPNM_RW(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Surface *(*)(SDL_RWops *))*(void**)(__base - 154))(__t__p0));\
	})

#define IMG_LoadXPM_RW(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Surface *(*)(SDL_RWops *))*(void**)(__base - 160))(__t__p0));\
	})

#define IMG_LoadXCF_RW(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Surface *(*)(SDL_RWops *))*(void**)(__base - 166))(__t__p0));\
	})

#define IMG_LoadPCX_RW(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Surface *(*)(SDL_RWops *))*(void**)(__base - 172))(__t__p0));\
	})

#define IMG_LoadGIF_RW(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Surface *(*)(SDL_RWops *))*(void**)(__base - 178))(__t__p0));\
	})

#define IMG_LoadJPG_RW(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Surface *(*)(SDL_RWops *))*(void**)(__base - 184))(__t__p0));\
	})

#define IMG_LoadTIF_RW(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Surface *(*)(SDL_RWops *))*(void**)(__base - 190))(__t__p0));\
	})

#define IMG_LoadPNG_RW(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Surface *(*)(SDL_RWops *))*(void**)(__base - 196))(__t__p0));\
	})

#define IMG_LoadTGA_RW(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Surface *(*)(SDL_RWops *))*(void**)(__base - 202))(__t__p0));\
	})

#define IMG_LoadLBM_RW(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Surface *(*)(SDL_RWops *))*(void**)(__base - 208))(__t__p0));\
	})

#define IMG_LoadXV_RW(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Surface *(*)(SDL_RWops *))*(void**)(__base - 214))(__t__p0));\
	})

#define IMG_LoadWEBP_RW(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Surface *(*)(SDL_RWops *))*(void**)(__base - 220))(__t__p0));\
	})

#define IMG_ReadXPMFromArray(__p0) \
	({ \
		char ** __t__p0 = __p0;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Surface *(*)(char **))*(void**)(__base - 226))(__t__p0));\
	})

#define IMG_Init(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int ))*(void**)(__base - 238))(__t__p0));\
	})

#define IMG_Quit() \
	({ \
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(void))*(void**)(__base - 244))());\
	})

#define IMG_isSVG(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_RWops *))*(void**)(__base - 250))(__t__p0));\
	})

#define IMG_LoadSVG_RW(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Surface *(*)(SDL_RWops *))*(void**)(__base - 256))(__t__p0));\
	})

#define IMG_SaveJPG(__p0, __p1, __p2) \
	({ \
		SDL_Surface * __t__p0 = __p0;\
		const char * __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Surface *, const char *, int ))*(void**)(__base - 262))(__t__p0, __t__p1, __t__p2));\
	})

#define IMG_SaveJPG_RW(__p0, __p1, __p2, __p3) \
	({ \
		SDL_Surface * __t__p0 = __p0;\
		SDL_RWops * __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		int  __t__p3 = __p3;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Surface *, SDL_RWops *, int , int ))*(void**)(__base - 268))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define IMG_LoadAnimation(__p0) \
	({ \
		const char * __t__p0 = __p0;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((IMG_Animation *(*)(const char *))*(void**)(__base - 274))(__t__p0));\
	})

#define IMG_LoadAnimation_RW(__p0, __p1) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((IMG_Animation *(*)(SDL_RWops *, int ))*(void**)(__base - 280))(__t__p0, __t__p1));\
	})

#define IMG_LoadAnimationTyped_RW(__p0, __p1, __p2) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		const char * __t__p2 = __p2;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((IMG_Animation *(*)(SDL_RWops *, int , const char *))*(void**)(__base - 286))(__t__p0, __t__p1, __t__p2));\
	})

#define IMG_FreeAnimation(__p0) \
	({ \
		IMG_Animation * __t__p0 = __p0;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(IMG_Animation *))*(void**)(__base - 292))(__t__p0));\
	})

#define IMG_LoadGIFAnimation_RW(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_IMAGE_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((IMG_Animation *(*)(SDL_RWops *))*(void**)(__base - 298))(__t__p0));\
	})

#endif /* !_PPCINLINE_SDL2_IMAGE_H */
