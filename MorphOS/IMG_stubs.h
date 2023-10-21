/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2014 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#undef STUB

#if defined(GENERATE_STUBS)
#define STUB(name) extern int name(); int __saveds LIB_##name() { return name(); }
#elif defined(GENERATE_POINTERS)
#define STUB(name) (APTR)&LIB_##name ,
#else
#define STUB(name) extern int LIB_##name();
#endif

	STUB(IMG_LoadTyped_RW)
	STUB(IMG_Load)
	STUB(IMG_Load_RW)

	STUB(IMG_SavePNG)
	STUB(IMG_SavePNG_RW)

	STUB(IMG_LoadTexture)
	STUB(IMG_LoadTexture_RW)
	STUB(IMG_LoadTextureTyped_RW)

	STUB(IMG_isBMP)
	STUB(IMG_isPNM)
	STUB(IMG_isXPM)
	STUB(IMG_isXCF)
	STUB(IMG_isPCX)
	STUB(IMG_isGIF)
	STUB(IMG_isJPG)
	STUB(IMG_isTIF)
	STUB(IMG_isPNG)
	STUB(IMG_isLBM)
	STUB(IMG_isXV)
	STUB(IMG_isWEBP)

	STUB(IMG_LoadBMP_RW)
	STUB(IMG_LoadPNM_RW)
	STUB(IMG_LoadXPM_RW)
	STUB(IMG_LoadXCF_RW)
	STUB(IMG_LoadPCX_RW)
	STUB(IMG_LoadGIF_RW)
	STUB(IMG_LoadJPG_RW)
	STUB(IMG_LoadTIF_RW)
	STUB(IMG_LoadPNG_RW)
	STUB(IMG_LoadTGA_RW)
	STUB(IMG_LoadLBM_RW)
	STUB(IMG_LoadXV_RW)
	STUB(IMG_LoadWEBP_RW)

	STUB(IMG_ReadXPMFromArray)
	STUB(IMG_Linked_Version)

	STUB(IMG_Init)
	STUB(IMG_Quit)
	
	STUB(IMG_isSVG)
	STUB(IMG_LoadSVG_RW)
	STUB(IMG_SaveJPG)
	STUB(IMG_SaveJPG_RW)
	STUB(IMG_LoadAnimation)
	STUB(IMG_LoadAnimation_RW)
	STUB(IMG_LoadAnimationTyped_RW)
	STUB(IMG_FreeAnimation)
	STUB(IMG_LoadGIFAnimation_RW)
	
	STUB(IMG_isICO)
	STUB(IMG_LoadICO_RW)
	STUB(IMG_isCUR)
	STUB(IMG_LoadCUR_RW)
	STUB(IMG_isQOI)
	STUB(IMG_LoadQOI_RW)
	
	STUB(IMG_isJXL)
	STUB(IMG_LoadJXL_RW)
	STUB(IMG_ReadXPMFromArrayToRGB888)
	STUB(IMG_isAVIF)
	STUB(IMG_LoadAVIF_RW)
	
	STUB(IMG_LoadSizedSVG_RW)
	STUB(IMG_LoadWEBPAnimation_RW)