/*!
 *****************************************************************************
 *
 * @File       sysmem_utils.c
 * @Description    This file contains the System Memory Kernel Mode UtilitiesAPI.
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

#include "img_defs.h"
#include "system.h"
#ifdef IMG_MEM_ERROR_INJECTION
#undef IMG_MEM_ERROR_INJECTION
#include "sysmem_utils.h"
#define IMG_MEM_ERROR_INJECTION
#else
#include "sysmem_utils.h"
#endif
#include "lst.h"

#ifdef IMG_KERNEL_MODULE
#include <linux/module.h>
#include <linux/device.h>
#include <linux/dma-mapping.h>
#endif

#define MAX_SYSMEM_HEAPS (5)
static IMG_INT32 gNoHeaps;
static LST_T gHeaps;

static IMG_BOOL	gSysMemInitialised = IMG_FALSE;		/*!< Indicates where the API has been initialised	*/

__inline static SYSMEM_Heap *findHeapById(SYS_eMemPool memId) {
	SYSMEM_Heap *heap = (SYSMEM_Heap *)LST_first(&gHeaps);
	while(heap != IMG_NULL)
	{
		if(memId == heap->memId)
			return heap;
		heap = LST_next(heap);
	}
	return IMG_NULL;
}

static SYSMEMU_sPages *_preparePages(
	IMG_UINT32				ui32Size,
	SYS_eMemAttrib			eMemAttrib,
	SYSMEM_Heap				*memHeap
)
{
	SYSMEMU_sPages *			psPages;

	IMG_ASSERT(gSysMemInitialised);

	/* Allocate connection context...*/
	psPages = IMG_MALLOC(sizeof(*psPages));
	IMG_ASSERT(psPages != IMG_NULL);
	if (psPages == IMG_NULL)
	{
		return IMG_NULL;
	}
	IMG_MEMSET(psPages, 0, sizeof(*psPages));

	/* Setup control block...*/
	psPages->ui32Size	= ui32Size;
	psPages->eMemAttrib = eMemAttrib;
	psPages->memHeap	= memHeap;

	/* Return pointer to stucture...*/
	return psPages;
}

static IMG_RESULT duplicateHandle(
    SYSMEM_Heap *  heap,
    IMG_UINT32     ui32Size,
    SYSMEMU_sPages *psPages,
    SYSMEMU_sPages **phPagesHandle
)
{
    SYSMEMU_sPages *  psNewPages;

    /**** In this implementation we are importing buffers that we have allocated. */
    /* Allocate a new memory structure...*/
    psNewPages = IMG_MALLOC(sizeof(*psNewPages));
    IMG_ASSERT(psNewPages != IMG_NULL);
    if (psNewPages == IMG_NULL)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }

    /* Take a copy of the original page allocation. */
    *psNewPages = *psPages;

    *phPagesHandle = psNewPages;
    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function				SYSMEMU_Initialise

******************************************************************************/
IMG_RESULT SYSMEMU_Initialise(IMG_VOID)
{
	if (!gSysMemInitialised)
	{
		gSysMemInitialised = IMG_TRUE;
	}

	return IMG_SUCCESS;
}

IMG_RESULT SYSMEMU_AddMemoryHeap(
    SYSMEM_Ops *    ops,
	SYSDEVU_sInfo *sysdev,
    IMG_BOOL        contiguous,
    IMG_VOID *      priv,
    SYS_eMemPool *  peMemPool
)
{

	SYSMEM_Heap *heap = IMG_MALLOC(sizeof(SYSMEM_Heap));
	IMG_ASSERT(heap != IMG_NULL);
    if(IMG_NULL == heap)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }

    IMG_MEMSET(heap, 0, sizeof(*heap));

	heap->ops = ops;
	heap->contiguous = contiguous;
	heap->priv = priv;
	heap->memId = gNoHeaps;

	heap->sysdev = sysdev;

	if (!ops->DuplicateHandle)
		ops->DuplicateHandle = duplicateHandle;

#if defined(IMG_KERNEL_MODULE)
	if (sysdev) {
		struct device *dev = heap->sysdev->native_device;
		if (dev) {
			if (!dev->dma_mask)
				dev->dma_mask = &dev->coherent_dma_mask;
			dma_set_mask(dev, dma_get_mask(dev));
		}
	}
#endif

	LST_add(&gHeaps, (void *)heap);

	if(heap->ops->Initialise)
		heap->ops->Initialise(heap);

	*peMemPool = gNoHeaps++;

    return IMG_SUCCESS;
}

IMGVIDEO_EXPORT_SYMBOL(SYSMEMU_AddMemoryHeap)

IMG_RESULT SYSMEMU_RemoveMemoryHeap(SYS_eMemPool memPool)
{
	SYSMEM_Heap *heap;
	heap = findHeapById(memPool);
	IMG_ASSERT(heap != IMG_NULL);
	if(!heap)
	{
		return IMG_ERROR_GENERIC_FAILURE;
	}
	heap = LST_remove(&gHeaps, (void *)heap);
    IMG_ASSERT(heap != IMG_NULL);
    if(heap == IMG_NULL)
    {
        return IMG_ERROR_FATAL;
    }

	if(heap->ops->Deinitialise)
		heap->ops->Deinitialise(heap);
	IMG_FREE(heap);
	return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(SYSMEMU_RemoveMemoryHeap)


/*!
******************************************************************************

 @Function				SYSMEMU_Deinitialise

******************************************************************************/
IMG_VOID SYSMEMU_Deinitialise(IMG_VOID)
{
	if (gSysMemInitialised)
	{
		gSysMemInitialised = IMG_FALSE;
	}
}

// allocation/free
IMG_RESULT SYSMEMU_AllocatePages(IMG_UINT32 ui32Size, SYS_eMemAttrib eMemAttrib,
		SYS_eMemPool eMemPool, IMG_HANDLE *phPagesHandle, IMG_PHYSADDR **pppaPhyAddrs)
{
	IMG_RESULT result;
	SYSMEMU_sPages *psPages;
	SYSMEM_Heap *heap;

	heap = findHeapById(eMemPool);
	IMG_ASSERT(heap != IMG_NULL);
	IMG_ASSERT(phPagesHandle != IMG_NULL);
    if((!heap) || (!phPagesHandle))
	{
		return IMG_ERROR_GENERIC_FAILURE;
	}

    IMG_ASSERT(heap->ops->AllocatePages);
    if (!heap->ops->AllocatePages)
    {
    	return IMG_ERROR_GENERIC_FAILURE;
    }

	psPages = _preparePages(ui32Size, eMemAttrib, heap);
	IMG_ASSERT(psPages != IMG_NULL);
	if (psPages == IMG_NULL)
	{
		return IMG_ERROR_OUT_OF_MEMORY;
	}

	result = heap->ops->AllocatePages(heap, ui32Size, psPages, eMemAttrib);

	IMG_ASSERT(result == IMG_SUCCESS);
	if(result != IMG_SUCCESS)
	{
		IMG_FREE(psPages);
		return result;
	}

	*phPagesHandle = psPages;

    if(pppaPhyAddrs)
    {
        *pppaPhyAddrs = psPages->ppaPhysAddr;
    }


	return result;
}
IMGVIDEO_EXPORT_SYMBOL(SYSMEMU_AllocatePages)


IMG_VOID SYSMEMU_FreePages(IMG_HANDLE hPagesHandle)
{
	SYSMEMU_sPages *psPages = hPagesHandle;
	SYSMEM_Heap *heap = psPages->memHeap;

	heap->ops->FreePages(heap, psPages);
	IMG_FREE(psPages);
}
IMGVIDEO_EXPORT_SYMBOL(SYSMEMU_FreePages)


// import
SYSMEMU_sPages *SYSMEMU_ImportPages(SYS_eMemPool eMemPool, SYSDEVU_sInfo *sysdev, IMG_UINT32 ui32Size,
		SYS_eMemAttrib eMemAttrib, IMG_UINT32 buff_fd, IMG_PHYSADDR * ppaPhyAddrs, IMG_VOID *priv, IMG_BOOL kernelMapped)
{
	IMG_RESULT result;
	SYSMEMU_sPages *psPages;
	SYSMEM_Heap *heap;

	heap = findHeapById(eMemPool);
	IMG_ASSERT(heap != IMG_NULL);
	if(!heap)
	{
		return IMG_NULL;
	}

	// If no sysdev is passed, use the default sysdev.
	if (!sysdev)
		sysdev = heap->sysdev;

    IMG_ASSERT(heap->ops->ImportPages);
    if (!heap->ops->ImportPages)
    {
    	return IMG_NULL;
    }

	psPages = _preparePages(ui32Size, eMemAttrib, heap);
	IMG_ASSERT(psPages != IMG_NULL);
	if (psPages == IMG_NULL)
	{
		return IMG_NULL;
	}

	psPages->bImported = IMG_TRUE;

	result = heap->ops->ImportPages(heap, sysdev, ui32Size, psPages, eMemAttrib, buff_fd, ppaPhyAddrs, priv, kernelMapped);
	IMG_ASSERT(result == IMG_SUCCESS);
	if(result != IMG_SUCCESS)
	{
		IMG_FREE(psPages);
		return IMG_NULL;
	}

	return psPages;

}
IMGVIDEO_EXPORT_SYMBOL(SYSMEMU_ImportPages)

IMG_RESULT SYSMEMU_DuplicateHandle(IMG_UINT32 ui32Size, IMG_HANDLE hExtImportHandle,
		IMG_HANDLE *phPagesHandle, IMG_VOID **ppvCpuKmAddr)
{
	IMG_RESULT result;
	SYSMEMU_sPages *psPages = hExtImportHandle;
	SYSMEMU_sPages **psNewPages = (SYSMEMU_sPages **)phPagesHandle;
	SYSMEM_Heap *heap = psPages->memHeap;

    IMG_ASSERT(heap->ops->DuplicateHandle);
    if (!heap->ops->DuplicateHandle)
    {
    	return IMG_ERROR_GENERIC_FAILURE;
    }

	result = heap->ops->DuplicateHandle(heap, ui32Size, psPages, psNewPages);
	IMG_ASSERT(result == IMG_SUCCESS);
	if(result != IMG_SUCCESS)
	{
		return result;
	}

	(*psNewPages)->bImported = IMG_FALSE;
	(*psNewPages)->bDuplicated = IMG_TRUE;

    if(ppvCpuKmAddr)
    {
        *ppvCpuKmAddr = (*psNewPages)->pvCpuKmAddr;
    }

	return result;
}

// translation
IMG_RESULT SYSMEMU_GetCpuKmAddr(IMG_VOID **ppvCpuKmAddr,IMG_HANDLE hPagesHandle)
{
	SYSMEMU_sPages *psPages = hPagesHandle;
	SYSMEM_Heap *heap = psPages->memHeap;
	IMG_ASSERT(ppvCpuKmAddr != IMG_NULL);
	if(!ppvCpuKmAddr)
	{
		return IMG_ERROR_GENERIC_FAILURE;
	}

    IMG_ASSERT(heap->ops->GetCpuKmAddr);
    if (!heap->ops->GetCpuKmAddr)
    {
    	return IMG_ERROR_GENERIC_FAILURE;
    }

	return heap->ops->GetCpuKmAddr(heap, ppvCpuKmAddr, hPagesHandle);
}
IMGVIDEO_EXPORT_SYMBOL(SYSMEMU_GetCpuKmAddr)

IMG_PHYSADDR SYSMEMU_CpuKmAddrToCpuPAddr(SYS_eMemPool eMemPool, IMG_VOID *pvCpuKmAddr)
{
	SYSMEM_Heap *heap;
	heap = findHeapById(eMemPool);
	IMG_ASSERT(heap != IMG_NULL);
	if(!heap)
		return -1;

    IMG_ASSERT(heap->ops->CpuKmAddrToCpuPAddr);
    if (!heap->ops->CpuKmAddrToCpuPAddr)
    {
    	return -1;
    }

	return heap->ops->CpuKmAddrToCpuPAddr(heap, pvCpuKmAddr);
}
IMGVIDEO_EXPORT_SYMBOL(SYSMEMU_CpuKmAddrToCpuPAddr)


IMG_VOID *SYSMEMU_CpuPAddrToCpuKmAddr(SYS_eMemPool eMemPool, IMG_PHYSADDR paCpuPAddr)
{
	SYSMEM_Heap *heap;
	heap = findHeapById(eMemPool);
	IMG_ASSERT(heap != IMG_NULL);
	if(!heap)
		return IMG_NULL;

    IMG_ASSERT(heap->ops->CpuPAddrToCpuKmAddr);
    if (!heap->ops->CpuPAddrToCpuKmAddr)
    {
    	return IMG_NULL;
    }

	return heap->ops->CpuPAddrToCpuKmAddr(heap, paCpuPAddr);
}

// maintenance
IMG_VOID SYSMEMU_UpdateMemory(IMG_HANDLE hPagesHandle, SYSMEM_UpdateDirection dir)
{
	SYSMEMU_sPages *psPages = hPagesHandle;
	SYSMEM_Heap *heap;

	if(hPagesHandle == IMG_NULL) {
		/* Some drivers pass IMG_NULL as a memory handle!!! */
		switch(dir)
		{
		case CPU_TO_DEV:
#ifdef IMG_KERNEL_MODULE
#ifdef CONFIG_ARM
		/* ARM Cortex write buffer needs to be synchronised before device can access it */
			dmb();
#else
			mb();
#endif
#endif
			break;
		case DEV_TO_CPU:
			break;
		default:
			break;
		}

		return;
	}

	heap = psPages->memHeap;

    IMG_ASSERT(heap->ops->UpdateMemory);
    if (!heap->ops->UpdateMemory)
    {
    	return;
    }

	return heap->ops->UpdateMemory(heap, hPagesHandle, dir);
}
IMGVIDEO_EXPORT_SYMBOL(SYSMEMU_UpdateMemory)

IMG_VOID SYSMEMU_UpdateMemoryRegion(IMG_HANDLE hPagesHandle, SYSMEM_UpdateDirection dir, IMG_UINT32 offset, IMG_UINT32 size)
{
	SYSMEMU_sPages *psPages = hPagesHandle;
	SYSMEM_Heap *heap = psPages->memHeap;

	if(hPagesHandle == IMG_NULL) {
		//IMG_ASSERT(IMG_FALSE);
		switch(dir)
		{
		case CPU_TO_DEV:
#ifdef CONFIG_ARM
		/* ARM Cortex write buffer needs to be synchronised before device can access it */
			dmb();
#endif
			break;
		case DEV_TO_CPU:
			break;
		default:
			break;
		}

		return;
	}

	if(heap->ops->UpdateMemoryRegion)
		return heap->ops->UpdateMemoryRegion(heap, hPagesHandle, dir, offset, size);
	else
		return SYSMEMU_UpdateMemory(hPagesHandle, dir);
}
IMGVIDEO_EXPORT_SYMBOL(SYSMEMU_UpdateMemoryRegion)


IMG_BOOL SYSMEMKM_IsContiguous(IMG_HANDLE hPagesHandle) {
	SYSMEMU_sPages *psPages = hPagesHandle;
	SYSMEM_Heap *heap = psPages->memHeap;

	if(!heap)
		return IMG_FALSE;

	return heap->contiguous;
}


IMG_INT SYSMEMU_MapToUser(SYSMEMU_sPages *psPages, IMG_VOID *priv) {
	SYSMEM_Heap *heap = psPages->memHeap;

	if (!heap->ops->MapUser) {
		IMG_ASSERT(heap->ops->MapUser);
		return -1;
	}

	return heap->ops->MapUser(psPages, priv);
}
IMGVIDEO_EXPORT_SYMBOL(SYSMEMU_MapToUser)
