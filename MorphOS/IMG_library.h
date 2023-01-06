#ifndef SDL_IMAGE_LIBRARY_H
#define SDL_IMAGE_LIBRARY_H

#ifndef DOS_DOS_H
#include <dos/dos.h>
#endif

#ifndef EXEC_LIBRARIES_H
#include <exec/libraries.h>
#endif

#ifndef EXEC_SEMAPHORES_H
#include <exec/semaphores.h>
#endif

#define SAVEDS __saveds

#if defined(__PPC__)
#define __TEXTSEGMENT__ __attribute__((section(".text")))
#else
#define __TEXTSEGMENT__
#endif

struct HunkSegment
{
	unsigned int Size;
	struct HunkSegment *Next;
};

struct TaskNode
{
	struct MinNode Node;
	struct Task *Task;
};

struct SDL2ImageLibrary
{
	struct Library Library;
	UWORD          Alloc;
	APTR           DataSeg;	   /* DON'T CHANGE POSITION */

	ULONG                    DataSize;
	struct SDL2ImageLibrary *Parent;
	BPTR                     SegList;
	struct ExecBase         *MySysBase;
	struct DosLibrary       *MyDOSBase;

	union
	{
		struct MinList TaskList;
		struct TaskNode TaskNode;
	} TaskContext;

	// library management

	struct SignalSemaphore Semaphore;
};

#endif /* SDL_IMAGE_LIBRARY_H */
