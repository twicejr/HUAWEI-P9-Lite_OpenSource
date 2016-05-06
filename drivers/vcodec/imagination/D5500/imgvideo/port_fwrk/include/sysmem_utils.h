/*!
 *****************************************************************************
 *
 * @File       sysmem_utils.h
 * @Description    This file contains the header file information for the
 *  System Memory Kernel Mode API.
 *  The implementation of the System Memory Kernel Mode API is
 *  specific to a given system/SoC (and possibly OS).
 * ---------------------------------------------------------------------------
 *
 * Copyright (c) Imagination Technologies Ltd.
 * 
 * The contents of this file are subject to the MIT license as set out below.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
 * 
 * Alternatively, the contents of this file may be used under the terms of the 
 * GNU General Public License Version 2 ("GPL")in which case the provisions of
 * GPL are applicable instead of those above. 
 * 
 * If you wish to allow use of your version of this file only under the terms 
 * of GPL, and not to allow others to use your version of this file under the 
 * terms of the MIT license, indicate your decision by deleting the provisions 
 * above and replace them with the notice and other provisions required by GPL 
 * as set out in the file called "GPLHEADER" included in this distribution. If 
 * you do not delete the provisions above, a recipient may use your version of 
 * this file under the terms of either the MIT license or GPL.
 * 
 * This License is also included in this distribution in the file called 
 * "MIT_COPYING".
 *
 *****************************************************************************/

#if !defined (__SYSMEM_UTILS_H__)
#define __SYSMEM_UTILS_H__

#include "img_errors.h"
#include "img_defs.h"
#include "img_mem.h"
#include "lst.h"
#include "sysdev_utils.h"

#ifdef IMG_MEM_ERROR_INJECTION
#define SYSMEMU_AllocatePages  MEMERRINJ_DevAlloc
#define SYSMEMU_FreePages      MEMERRINJ_DevFree
#endif /* IMG_MEM_ERROR_INJECTION */

#if defined(__cplusplus)
extern "C" {
#endif

/*!
******************************************************************************
 This structure contains the pages information.
******************************************************************************/
typedef struct
{
    LST_LINK;                             //!< List link (allows the structure to be part of a MeOS list).
    IMG_BOOL        bDuplicated;         //!< IMG_TRUE if this is a "dup"ed handle ( created by DuplicateHandle )
    IMG_BOOL        bImported;            //!< IMG_TRUE if this is allocation was imported
    IMG_UINT32      ui32Size;             //!< Size of allocation
    SYS_eMemAttrib  eMemAttrib;           //!< Memory attributes
    struct SYSMEM_Heap *memHeap;             //!< Memory heap
    IMG_VOID *      pvCpuKmAddr;          //!< CPU kernel mode address
    IMG_HANDLE      hRegHandle;           //!< Handle to mapping
    IMG_VOID *      pvImplData;           //!< Pointer that holds data specific to sysmem implementation
    IMG_PHYSADDR *  ppaPhysAddr;            //!< Array with physical addresses of the pages
    SYSDEVU_sInfo	*sysdev;
} SYSMEMU_sPages;


struct SYSMEM_Heap;

typedef enum {
    CPU_TO_DEV,
    DEV_TO_CPU
} SYSMEM_UpdateDirection;

typedef struct SYSMEM_Ops {
    IMG_RESULT (*Initialise)(struct SYSMEM_Heap *);
    IMG_VOID (*Deinitialise)(struct SYSMEM_Heap *);

    // allocation/free
    IMG_RESULT (*AllocatePages)(struct SYSMEM_Heap *, IMG_UINT32 ui32Size, SYSMEMU_sPages *psPages,
            SYS_eMemAttrib eMemAttrib);

    IMG_VOID (*FreePages)(struct SYSMEM_Heap *, IMG_HANDLE hPagesHandle);

    // import
    IMG_RESULT (*ImportPages)(struct SYSMEM_Heap *, SYSDEVU_sInfo *sysdev,
    		IMG_UINT32 ui32Size, SYSMEMU_sPages *psPages, SYS_eMemAttrib eMemAttrib,
    		IMG_INT32 buff_fd, IMG_UINT64 *pPhyAddrs, IMG_VOID *priv, IMG_BOOL kernelMapped);

    IMG_RESULT (*DuplicateHandle)(struct SYSMEM_Heap *, IMG_UINT32 ui32Size, SYSMEMU_sPages *hExtImportHandle,
    		SYSMEMU_sPages **phPagesHandle);

    // translation
    IMG_RESULT    (*GetCpuKmAddr)(struct SYSMEM_Heap *, IMG_VOID **ppvCpuKmAddr,IMG_HANDLE hPagesHandle);
    IMG_PHYSADDR (*CpuKmAddrToCpuPAddr)(struct SYSMEM_Heap *heap, IMG_VOID *pvCpuKmAddr);
    IMG_VOID *(*CpuPAddrToCpuKmAddr)(struct SYSMEM_Heap *heap, IMG_PHYSADDR paCpuPAddr);

    // maintenance

    IMG_VOID (*UpdateMemory)(struct SYSMEM_Heap *, IMG_HANDLE hPagesHandle, SYSMEM_UpdateDirection dir);
    IMG_VOID (*UpdateMemoryRegion)(struct SYSMEM_Heap *, IMG_HANDLE hPagesHandle, SYSMEM_UpdateDirection dir, IMG_UINT32 offset, IMG_UINT32 size);

    // mmap
    IMG_INT (*MapUser)(SYSMEMU_sPages *psPages, IMG_VOID *priv);
} SYSMEM_Ops;

typedef struct SYSMEM_Heap {
    LST_LINK;
    SYS_eMemPool memId;
    SYSMEM_Ops *ops;
    SYSDEVU_sInfo *sysdev;
    IMG_BOOL contiguous;

    IMG_VOID *priv;
} SYSMEM_Heap;

/*!
******************************************************************************

 @Function                SYSMEMU_Initialise

 @Description

 This function is used to initialise the system memory component and is called
 at start-up.

 @Input     None.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.

******************************************************************************/
extern IMG_RESULT SYSMEMU_Initialise(IMG_VOID);


/*!
******************************************************************************

 @Function                SYSMEMU_Deinitialise

 @Description

 This function is used to de-initialises the system memory component and would
 normally be called at shutdown.

 @Input     None.

 @Return    None.

******************************************************************************/
extern IMG_VOID SYSMEMU_Deinitialise(IMG_VOID);


/*!
******************************************************************************

 @Function                SYSMEMU_AddMemoryHeap

 @Description

 Register a new generic memory heap in SYSMEM subsystem.

 @Input		ops: A SYSMEM_Ops that contains pointers to functions that is implements this heap ops.

 @Input		contiguous: Indicate whether or not the memory allocated by this heap is contiguous.

 @Input		priv: A priv pointer that can come in handy for the heap.

 @Output    peMemPool: The memory pool id of the newly created pool.

 @Return    IMG_RESULT: IMG_SUCCESS if succeeds.

******************************************************************************/
extern IMG_RESULT SYSMEMU_AddMemoryHeap(SYSMEM_Ops *ops, SYSDEVU_sInfo *sysdev, IMG_BOOL contiguous, IMG_VOID *priv, SYS_eMemPool *peMemPool);

/*!
******************************************************************************

 @Function                SYSMEMU_RemoveMemoryHeap

 @Description

 Unregister a memory heap from SYSMEM subsystem.

 @Input     peMemPool: The memory pool id of the pool that you would like to remove.

 @Return    IMG_RESULT: IMG_SUCCESS if succeeds.

******************************************************************************/
extern IMG_RESULT SYSMEMU_RemoveMemoryHeap(SYS_eMemPool memPool);

/* Memory pool initialisation. */

/*!
******************************************************************************

 @Function                SYSMEMKM_AddSystemMemory

 @Description

 Allocate a system memory pool. This allows you to allocate memory from normal system memory that's managed by the kernel

 @Output     peMemPool: The memory pool id of the newly created pool.

 @Return    IMG_RESULT: IMG_SUCCESS if succeeds.

******************************************************************************/
extern IMG_RESULT SYSMEMKM_AddSystemMemory(
	SYSDEVU_sInfo *sysdev,
    SYS_eMemPool *  peMemPool
);

extern IMG_RESULT SYSMEMKM_AddIONMemory(
		SYSDEVU_sInfo *sysdev,
		SYS_eMemPool *peMemPool
);


/*!
******************************************************************************

 @Function                SYSMEMKM_AddDevIFMemory

 @Description

 Allocate a DEVIF memory pool. This allows you to allocate memory that can be used with DEVIF interface.

 @Input     vstart: The host virtual address of the memory pool

 @Input     pstart: The host physical address of the memory pool

 @Input     size: The size of this memory pool

 @Output    peMemPool: The memory pool id of the newly created pool.

 @Return    IMG_RESULT: IMG_SUCCESS if succeeds.

******************************************************************************/
extern IMG_RESULT SYSMEMKM_AddDevIFMemory(
	SYSDEVU_sInfo	*sysdev,
    IMG_UINTPTR     vstart,
    IMG_PHYSADDR    pstart,
    IMG_UINT32      size,
    SYS_eMemPool *  peMemPool
);

/*!
******************************************************************************

 @Function                SYSMEMKM_AddCarveoutMemory

 @Description

 Allocate a DEVIF memory pool. This allows you to allocate memory that can be used with DEVIF interface.

 @Input     vstart: The host virtual address of the memory pool

 @Input     pstart: The host physical address of the memory pool

 @Input     size: The size of this memory pool

 @Output    peMemPool: The memory pool id of the newly created pool.

 @Return    IMG_RESULT: IMG_SUCCESS if succeeds.

******************************************************************************/
extern IMG_RESULT SYSMEMKM_AddCarveoutMemory(
	SYSDEVU_sInfo	*sysdev,
    IMG_UINTPTR     vstart,
    IMG_PHYSADDR    pstart,
    IMG_UINT32      size,
    SYS_eMemPool *  peMemPool
);

/*!
******************************************************************************

 @Function                SYSMEMKM_AddCoherentMemory

 @Description

 Allocate a coherent memory pool. This allows you to allocate memory using the linux kernel coherent dma-api

 @Output     peMemPool: The memory pool id of the newly created pool.

 @Return    IMG_RESULT: IMG_SUCCESS if succeeds.

******************************************************************************/
IMG_RESULT SYSMEMKM_AddCoherentMemory(
	SYSDEVU_sInfo	*sysdev,
    SYS_eMemPool *peMemPool
);

IMG_RESULT SYSMEMKM_AddDMABufMemory(
	SYSDEVU_sInfo *sysdev,
    SYS_eMemPool *peMemPool
);

IMG_RESULT SYSMEMKM_AddAshMemory(
	SYSDEVU_sInfo *sysdev,
    SYS_eMemPool *peMemPool
);

// allocation/free

/*!
******************************************************************************

 @Function                SYSMEMU_AllocatePages

 @Description

 Allocate a number of memory pages which can be accessed by the devices within the system/SoC.

 @Input     ui32Size:   The size of the allocation (in bytes).

 @Input     eMemAttrib: The memory attributes.

 @Input     eMemPool:   The pool from which the memory is to be allocated.

 @Output    phPagesHandle : A pointer to the pages control block, IMG_NULL
                              if the creation of the control block fails.

 @Output    pPhyAddrs : An array of physical page addresses that was allocated

 @Return    IMG_RESULT : IMG_SUCCESS on success.

******************************************************************************/
IMG_RESULT SYSMEMU_AllocatePages(IMG_UINT32 ui32Size, SYS_eMemAttrib eMemAttrib,
        SYS_eMemPool eMemPool, IMG_HANDLE *phPagesHandle, IMG_PHYSADDR **pppaPhyAddrs);


/*!
******************************************************************************

 @Function                SYSMEMU_AllocatePages

 @Description

 Free the control block

 @Input    phPagesHandle : The pages control block that you want to free

 @Return    IMG_RESULT : IMG_SUCCESS on success.

******************************************************************************/
IMG_VOID SYSMEMU_FreePages(IMG_HANDLE hPagesHandle);


// import

/*!
******************************************************************************

 @Function                SYSMEMU_ImportPages

 @Description

 Import externally allocated buffer to our SYSMEM.

 @Input     eMemPool:   The pool from which will be used for importing.

 @Input     ui32Size:   The size of the allocation (in bytes).

 @Input     eMemAttrib: The memory attributes.

 @Input    pPhyAddrs : An array of physical page addresses of the external memory block.

 @Input    pvCpuKmAddr : The host virtual address of the external memory block.

 @Output    phPagesHandle : A pointer to the pages control block that represent
 	 	 	 	 	 this memory in our SYSMEM subsystem.

 @Return    IMG_RESULT : IMG_SUCCESS on success.

******************************************************************************/
SYSMEMU_sPages *SYSMEMU_ImportPages(SYS_eMemPool eMemPool, SYSDEVU_sInfo *sysdev,
    		IMG_UINT32 ui32Size, SYS_eMemAttrib eMemAttrib, IMG_UINT32 buff_fd,
    		IMG_UINT64 *pPhyAddrs, IMG_VOID *priv, IMG_BOOL kernelMapped);

/*!
******************************************************************************

 @Function                SYSMEMU_DuplicateHandle

 @Description

 Duplicate a control block.

 @Input     ui32Size:   The size of the imported control block (in bytes).

 @Input    hExtImportHandle : A pointer to the pages control block that needs to be imported

 @Output    phPagesHandle : A pointer to the newly imported pages control block.

 @Output    ppvCpuKmAddr : A host virtual address of the newly imported control block.

 @Return    IMG_RESULT : IMG_SUCCESS on success.

******************************************************************************/
IMG_RESULT SYSMEMU_DuplicateHandle(IMG_UINT32 ui32Size, IMG_HANDLE hExtImportHandle,
        IMG_HANDLE *phPagesHandle, IMG_VOID **ppvCpuKmAddr);


// translation

/*!
******************************************************************************

 @Function                SYSMEMU_GetCpuKmAddr

 @Description

 Get a CPU accessible handle for SYSMEM handle.

 @Input     hPagesHandle: A handle to the memory control block.

 @Input/Output     ppvCpuKmAddr: The CPU accessible pointer will be store in this pointer.

 @Return    IMG_RESULT: IMG_SUCCESS if succeeds.

******************************************************************************/
IMG_RESULT SYSMEMU_GetCpuKmAddr(IMG_VOID **ppvCpuKmAddr,IMG_HANDLE hPagesHandle);

/*!
******************************************************************************

 @Function                SYSMEMU_CpuKmAddrToCpuPAddr

 @Description

 Convert the CPU accessible handle, that was previously retrieved by GetCpuKmAddr, to a physical address

 @Input     eMemPool: Memory heap ID.

 @Input pvCpuKmAddr: The CPU accessible address.

 @Return    IMG_UINT64: The physical address.

******************************************************************************/
IMG_PHYSADDR SYSMEMU_CpuKmAddrToCpuPAddr(SYS_eMemPool eMemPool, IMG_VOID *pvCpuKmAddr);

/*!
******************************************************************************

 @Function                SYSMEMU_CpuPAddrToCpuKmAddr

 @Description

 Convert a physical address that is owned by this heap to a CPU accessible handle ( if possible )

 @Input     eMemPool: Memory heap ID.

 @Input pvCpuKmAddr: The physical address.

 @Return IMG_VOID *: The CPU accessible address.

******************************************************************************/
IMG_VOID *SYSMEMU_CpuPAddrToCpuKmAddr(SYS_eMemPool eMemPool, IMG_PHYSADDR paCpuPAddr);



// maintenance

/**
 * Make sure that the observer view of memory is correct
 * CPU_TO_DEV : Make sure that the device view of memory is correct after a write from CPU to memory.
 * 		( by writing back all dirty cache lines and draining the writeback buffer )
 * DEV_TO_CPU : Make sure that CPU view of memory is correct after a DMA from the device to memory.
 * 		( by invalidating any stale cache lines - if any - )
 */

/*!
******************************************************************************

 @Function                SYSMEMU_UpdateMemory

 @Description

 Update all memory related to a specific SYSMEM handle.

 @Input     hPagesHandle: A handle to the memory control block.

 @Input     dir: The direction of maintenance operation.

 @Return    None.

******************************************************************************/
IMG_VOID SYSMEMU_UpdateMemory(IMG_HANDLE hPagesHandle, SYSMEM_UpdateDirection dir);


/*!
******************************************************************************

 @Function                SYSMEMU_UpdateMemoryRegion

 @Description

 Update a region of the memory related to a specific SYSMEM handle.

 @Input     hPagesHandle: A handle to the memory control block.

 @Input     dir: The direction of maintenance operation.

 @Input     offset: offset in the memory block that flushing should start from.

 @Input     size: The size of the region that needs to be flushed.

 @Return    None.

******************************************************************************/
IMG_VOID SYSMEMU_UpdateMemoryRegion(IMG_HANDLE hPagesHandle, SYSMEM_UpdateDirection dir, IMG_UINT32 offset, IMG_UINT32 size);


/*!
******************************************************************************

 @Function                SYSMEMKM_IsContiguous

 @Description

 Check whether this memory block is physically contiguous or not

 @Input     hPagesHandle:  A handle to the memory control block.

 @Return    IMG_BOOL : IMG_TRUE if contiguous and IMG_FALSE if not.

******************************************************************************/
IMG_BOOL SYSMEMKM_IsContiguous(IMG_HANDLE hPagesHandle);

/*!
******************************************************************************

 @Function                SYSMEMU_MapToUser

 @Description

 Map memory block to user memory.

 @Input     psPages: A handle to the memory control block.

 @Input     priv

 @Return    None.

******************************************************************************/
IMG_INT SYSMEMU_MapToUser(SYSMEMU_sPages *psPages, IMG_VOID *priv);

/*!
******************************************************************************
 
 @Function IMG_BIGORSMALL_ALLOC

 @Description

 Allocate and free using either kmalloc or vmalloc, depending on the size

 @Input ui32Size   : number of bytes to be allocated
 @Return pointer to allocated memory
 
******************************************************************************/
static size_t max_kmalloc_size = 8192;	// arbitrary size boundary: 2 pages
static IMG_INLINE void * IMG_BIGORSMALL_ALLOC(IMG_UINT32 ui32Size)
{
    void * ptr;
    if(ui32Size <= max_kmalloc_size)
        ptr = IMG_MALLOC(ui32Size);
    else
        ptr = IMG_BIGALLOC(ui32Size);
    return ptr;
}

/*!
******************************************************************************
 
 @Function IMG_BIGORSMALL_FREE

 @Description

 Free using either kfree or vfree, depending on the size

 @Input ui32Size   : number of bytes to be allocated
 @Input ptr :        memory to be freed
 @Return none
 
******************************************************************************/
static IMG_INLINE void IMG_BIGORSMALL_FREE(IMG_UINT32 ui32Size, void* ptr)
{
    if(ui32Size <= max_kmalloc_size)
        IMG_FREE(ptr);
    else
        IMG_BIGFREE(ptr);
}



#if defined(__cplusplus)
}
#endif

#endif /* __SYSMEM_UTILS_H__    */


