/*******************************************************************************
  ed_dynamic.c  Developed by Dafocus - http://www.dafocus.com/
*******************************************************************************/
#include "ed_dynamic.h"

/*------------------------------------------------------------------------------
	Generic binary dynamic allocation function
------------------------------------------------------------------------------*/
void EDAllocBinary (ED_BYTE** dataPtr, unsigned requiredBits, int* usedBits)
{
	if ((*dataPtr) != NULL) {
		EDFree (*dataPtr);
	}
	(*dataPtr) = (ED_BYTE*)EDAlloc ((requiredBits+7) >> 3);
	(*usedBits) = requiredBits;
}

#ifdef ED_DEBUG_ALLOC
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
size_t ED_MemAllocated = 0;
size_t ED_MaxMemAllocated = 0;
unsigned ED_AllocationId = 0;

#define ED_DEBUG_MEM_HEADER (sizeof (size_t)+sizeof (unsigned))

typedef struct SEDMemHeader {
	unsigned Signature;
	size_t Size;
	unsigned AllocationId;

	/* Pointer to the next header */
	struct SEDMemHeader* NextHeader;

	/* Pointer to the pointer pointing to this in the previous header */
	struct SEDMemHeader** PrevHeaderPointer;
	
} TEDMemHeader;

typedef struct SEDMemFooter {
	unsigned Signature;
	size_t Size;
	unsigned AllocationId;
} TEDMemFooter;

TEDMemHeader* ED_MemoryRoot = NULL;

#define ED_SIGNATURE_HEADER 0x12345678
#define ED_SIGNATURE_FOOTER 0xADACADAB

void EDDebugCheckMemory ()
{
	const TEDMemHeader* hdr;
	
	for (hdr = ED_MemoryRoot; hdr != NULL; hdr = hdr->NextHeader) {
		TEDMemFooter* footer =(TEDMemFooter*)(((char*)hdr)+(sizeof (TEDMemHeader)+hdr->Size));
		
		assert (hdr->Signature == ED_SIGNATURE_HEADER);
		assert (footer->Signature == ED_SIGNATURE_FOOTER);
		assert (hdr->Size == footer->Size);
		assert (hdr->AllocationId == footer->AllocationId);
		assert (*(hdr->PrevHeaderPointer) == hdr);
	}
}

void* EDDebugAlloc (size_t size)
{
	TEDMemHeader* ret;
	TEDMemFooter* footer;
#ifdef PS_UT_SWITCH
    return malloc(size);
#endif
	ED_MemAllocated += size;
	if (ED_MemAllocated > ED_MaxMemAllocated) ED_MaxMemAllocated = ED_MemAllocated;
	ret = (TEDMemHeader*)malloc (sizeof (TEDMemHeader)+size+sizeof (TEDMemFooter));
	footer = (TEDMemFooter*)(((char*)ret)+(sizeof (TEDMemHeader)+size));
	ret->Size = size;
	ret->Signature = ED_SIGNATURE_HEADER;
	ret->AllocationId = ED_AllocationId;
	footer->Size = size;
	footer->Signature = ED_SIGNATURE_FOOTER;
	footer->AllocationId = ED_AllocationId;
	memset (ret+1, 0xAB, size);
	ED_AllocationId++;
	
	/* Setup the linked list */
	ret->NextHeader = ED_MemoryRoot;
	ret->PrevHeaderPointer = &ED_MemoryRoot;
	ED_MemoryRoot = ret;
	if (ret->NextHeader) {
		ret->NextHeader->PrevHeaderPointer = &ret->NextHeader;
	}
	
#ifdef ED_TRACE_ALLOCS
	{
		static int firstTime = 1;
		FILE* f=fopen ("memory.log", (firstTime?"w":"a"));
		firstTime = 0;
		fprintf (f, "ALLC [ID:%08X] %08X %6d\n", ret->AllocationId, (unsigned)(ret+1), (int)size);
		fclose (f);
		if (ret->AllocationId == 0x00000010) {
			printf ("");
		}
	}
#endif
	EDDebugCheckMemory ();
	return (ret+1);
}

void EDDebugFree (void* ptr)
{
	TEDMemHeader* sptr = ((TEDMemHeader*)ptr)-1;
	TEDMemFooter* footer =(TEDMemFooter*)(((char*)sptr)+(sizeof (TEDMemHeader)+sptr->Size));

#ifdef PS_UT_SWITCH
    free(ptr);
    return;
#endif
	EDDebugCheckMemory ();
	
	assert (sptr->Signature == ED_SIGNATURE_HEADER);
	assert (footer->Signature == ED_SIGNATURE_FOOTER);
	assert (sptr->Size == footer->Size);
	assert (sptr->AllocationId == footer->AllocationId);
	memset (ptr, 0xCD, sptr->Size);
	
	(*sptr->PrevHeaderPointer) = sptr->NextHeader;
	if (sptr->NextHeader) {
		sptr->NextHeader->PrevHeaderPointer = sptr->PrevHeaderPointer;
	}
	
	ED_MemAllocated -= sptr->Size;
#ifdef ED_TRACE_ALLOCS
	{
		FILE* f=fopen ("memory.log", "a");
		if (sptr->AllocationId == 0x00000010) {
			printf ("");
		}
		fprintf (f, "FREE [ID:%08X] %08X %6d\n", sptr->AllocationId, (unsigned)ptr, (unsigned)sptr->Size);
		fclose (f);
	}
#endif
	EDDebugCheckMemory ();
	free (sptr);
}

int EDDebugPrintSummary ()
{
	printf ("Memory leaked: %d bytes  Max ED_MemAllocated: %d bytes\n", ED_MemAllocated, ED_MaxMemAllocated);
	return (ED_MemAllocated != 0);
}
#endif
