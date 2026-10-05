#include <exec/memory.h>
#include <proto/exec.h>

#include "IMG_library.h"

/*********************************************************************/

/* Defined by libSDL2.a(sdl-startup-brel.o), which the library needs anyway
   for the SDL varargs wrappers (SDL_SetError, SDL_sscanf...). */
extern struct Library    *SDL2Base;
extern struct Library    *SDL2ImageBase;

int ThisRequiresConstructorHandling = 0;

/* This function must preserve all registers except r13 */
asm
("\n"
"	.section \".text\"\n"
"	.align 2\n"
"	.type __restore_r13, @function\n"
"__restore_r13:\n"
"	lwz 13, 36(3)\n"
"	blr\n"
"__end__restore_r13:\n"
"	.size __restore_r13, __end__restore_r13 - __restore_r13\n"
);

/*
	libnix malloc()/free() (used by libwebp) allocate from this pool. libnix
	creates it lazily and only deletes it in its __exitmalloc destructor,
	which never runs here (no constructor handling), so each opener owns
	its pool explicitly: created in AMIGA_Startup(), deleted in
	AMIGA_Cleanup(). Same parameters as libnix.
*/
APTR libnix_mempool;
extern ULONG _MSTEP;

/**********************************************************************
	Startup/Cleanup
**********************************************************************/

int SAVEDS AMIGA_Startup(struct SDL2ImageLibrary *LibBase)
{
	SDL2ImageBase = &LibBase->Library;

	if ((libnix_mempool = CreatePool(MEMF_ANY | MEMF_SEM_PROTECTED, _MSTEP, _MSTEP / 2)) == NULL)
		return 0;

	if ((SDL2Base = OpenLibrary("sdl2.library", 53)) == NULL)
		return 0;

	return 1;
}

VOID SAVEDS AMIGA_Cleanup(struct SDL2ImageLibrary *LibBase)
{
		CloseLibrary(SDL2Base);
		SDL2Base = NULL;

		if (libnix_mempool)
		{
			DeletePool(libnix_mempool);
			libnix_mempool = NULL;
		}
}

void __chkabort(void) { }
void abort(void) { for (;;) Wait(0); }