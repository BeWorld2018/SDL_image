#include <exec/memory.h>
#include <proto/exec.h>

#include <SDL3/SDL_version.h>

#include "IMG_library.h"

/*********************************************************************/

/* The SDL calls go through libb32/libSDL3-nc.a (-mresident32 glue, no
   constructor): SDL3Base is per opener, opened in AMIGA_Startup(). */
struct Library           *SDL3Base = NULL;
extern struct Library    *SDL3ImageBase;

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

int SAVEDS AMIGA_Startup(struct SDL3ImageLibrary *LibBase)
{
	SDL3ImageBase = &LibBase->Library;

	if ((libnix_mempool = CreatePool(MEMF_ANY | MEMF_SEM_PROTECTED, _MSTEP, _MSTEP / 2)) == NULL)
		return 0;

	/* Same task as the program: sdl3.library returns the program's own
	   child base, so both share one SDL state. sdl3.library version =
	   SDL version (REVISION = minor * 100 + micro): any micro
	   release of the SDL we were built against has our functions. */
	if ((SDL3Base = OpenLibrary("sdl3.library", SDL_MAJOR_VERSION)) == NULL)
		return 0;

	if (!LIB_MINVER(SDL3Base, SDL_MAJOR_VERSION, SDL_MINOR_VERSION * 100))
		return 0;

	return 1;
}

VOID SAVEDS AMIGA_Cleanup(struct SDL3ImageLibrary *LibBase)
{
	CloseLibrary(SDL3Base);
	SDL3Base = NULL;

	if (libnix_mempool)
	{
		DeletePool(libnix_mempool);
		libnix_mempool = NULL;
	}
}

void __chkabort(void) { }
void abort(void) { for (;;) Wait(0); }
