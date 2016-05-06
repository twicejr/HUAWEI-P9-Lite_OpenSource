/*!
 *****************************************************************************
 *
 * @File       sysmem_api_km.c
 * @Description    This file contains DEVIF user mode implementation of the
 *  System Memory Kernel Mode API.
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
#include "sysmem_utils.h"
#include "sysbrg_utils.h"
#include "sysos_api_km.h"

#ifdef CONFIG_ARM
    #include <asm/cacheflush.h>
#endif // CONFIG_ARM



struct priv_params {
    IMG_UINTPTR  vstart;
    IMG_PHYSADDR pstart;
    IMG_UINT32   size;

    IMG_UINT32   npages;
    IMG_UINT32   cur_index;

    IMG_UINT8 *  alloc_pool;
};

/*!
******************************************************************************

 @Function                Initialise

******************************************************************************/
static IMG_RESULT Initialise(
    SYSMEM_Heap *  heap
)
{
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function                Deinitialise

******************************************************************************/
static IMG_VOID Deinitialise(
    SYSMEM_Heap *  heap
)
{
    IMG_UINT32            i;
    struct priv_params *  prv = (struct priv_params *)heap->priv;

    /* If we have a page allocation array - free it...*/
    if (prv->alloc_pool != IMG_NULL)
    {
        /* Check all pages are free...*/
        for (i=0; i<prv->npages; i++)
        {
            IMG_ASSERT(prv->alloc_pool[i] == IMG_FALSE);
        }
        IMG_BIGFREE(prv->alloc_pool);
        prv->alloc_pool = IMG_NULL;
        prv->size = 0;
    }
}
static IMG_VOID *CpuPAddrToCpuKmAddr(
    SYSMEM_Heap *  heap,
    IMG_PHYSADDR     paCpuPAddr
)
{
    IMG_PHYSADDR offset = 0LL;
    struct priv_params *prv = (struct priv_params *)heap->priv;

    IMG_ASSERT(paCpuPAddr > prv->pstart && (paCpuPAddr < (prv->pstart + prv->size)));
    offset = paCpuPAddr - prv->pstart;
    return (IMG_VOID *)((IMG_UINTPTR)offset + prv->vstart);
}

static IMG_PHYSADDR CpuKmAddrToCpuPAddr(
    SYSMEM_Heap *  heap,
    IMG_VOID *     pvCpuKmAddr
)
{
    IMG_UINTPTR offset = 0LL;
    struct priv_params *prv = (struct priv_params *)heap->priv;

    IMG_ASSERT(((IMG_UINTPTR)pvCpuKmAddr >= prv->vstart) && ((IMG_UINTPTR)pvCpuKmAddr < (prv->vstart + prv->size)));
    offset = (IMG_UINTPTR)pvCpuKmAddr - prv->vstart;
    return (IMG_PHYSADDR)offset + prv->pstart;
}

/*!
******************************************************************************

 @Function                AllocPages

******************************************************************************/

static IMG_RESULT AllocPages(
    SYSMEM_Heap *     heap,
    IMG_UINT32        ui32Size,
    SYSMEMU_sPages *  psPages,
    SYS_eMemAttrib    eMemAttrib
)
{
    IMG_UINT32  ui32NoPages;
    IMG_UINT32  ui32ExamPages;
    IMG_UINT32  i;
    IMG_UINT64  ui64DeviceMemoryBase;
    IMG_PHYSADDR  paCpuPhysAddr;
    IMG_UINT32  ui32Result;
    size_t      physAddrArrSize;

    struct priv_params *  prv = (struct priv_params *)heap->priv;

    /* If we don't know where the memory is...*/
    SYSOSKM_DisableInt();

    /* Calculate required no. of pages...*/
    ui32NoPages = (ui32Size + (HOST_MMU_PAGE_SIZE-1)) / HOST_MMU_PAGE_SIZE;

    /* Loop over allocated pages until we find an unallocated slot big enough for this allocation...*/
    ui32ExamPages = 0;
    while (ui32ExamPages < prv->npages)
    {
        /* If the current page is not allocated and we might have enough remaining to make this allocation...*/
        if (
                (!prv->alloc_pool[prv->cur_index]) &&
                ((prv->cur_index + ui32NoPages) <= prv->npages)
            )
        {
            /* Can we make this allocation...*/
            for (i=0; i<ui32NoPages; i++)
            {
                if (prv->alloc_pool[prv->cur_index+i])
                {
                    break;
                }
            }
            if (i == ui32NoPages)
            {
                /* Yes, mark pages as allocated...*/
                for (i=0; i<ui32NoPages; i++)
                {
                    prv->alloc_pool[prv->cur_index+i] = IMG_TRUE;
                }

                /* Calculate the memory address of the start of the allocation...*/
                //psPages->pvCpuKmAddr = (IMG_VOID *)((IMG_UINTPTR)prv->vstart + (prv->cur_index * HOST_MMU_PAGE_SIZE));
                psPages->pvImplData = (IMG_VOID *)(prv->vstart + (prv->cur_index * HOST_MMU_PAGE_SIZE));

                /* Update the current page index....*/
                prv->cur_index += ui32NoPages;
                if (prv->cur_index >= prv->npages)
                {
                    prv->cur_index = 0;
                }
                break;
            }
        }

        /* Update examined pages and page index...*/
        ui32ExamPages++;
        prv->cur_index++;
        if (prv->cur_index >= prv->npages)
        {
            prv->cur_index = 0;
        }
    }
    SYSOSKM_EnableInt();

    /* Check if allocation failed....*/
    IMG_ASSERT(ui32ExamPages < prv->npages);
    if (ui32ExamPages >= prv->npages)
    {
        /* Failed...*/
        /* dump some fragmentation information */
        int i = 0;
        int nAllocated = 0;
        int n64kBlocks  = 0;    // number of blocks of <16 consecutive pages
        int n128kBlocks = 0;
        int n256kBlocks = 0;
        int nBigBlocks  = 0;    // number of blocks of >=64 consecutive pages
        int nMaxBlocks  = 0;
        int nPages = 0;
        for(i = 0; i < (int)prv->npages; i++)
        {
            IMG_UINT8 isallocated = prv->alloc_pool[i];
            nPages++;
            if(i == prv->npages-1 || isallocated != prv->alloc_pool[i+1])
            {
                if(isallocated)
                    nAllocated += nPages;
                else if(nPages < 16)
                    n64kBlocks++;
                else if(nPages < 32)
                    n128kBlocks++;
                else if(nPages < 64)
                    n256kBlocks++;
                else
                    nBigBlocks++;
                    if(nMaxBlocks < nPages)
                        nMaxBlocks = nPages;
                isallocated = prv->alloc_pool[i];
                nPages = 0;
            }
        }
#ifdef printk
        /* hopefully, this will give some idea of the fragmentation of the memory */
        printk("AllocPages not able to allocate memory \n");
        printk("  number available memory areas under 64k:%d\n", n64kBlocks);
        printk("  number available memory areas under 128k:%d\n", n128kBlocks);
        printk("  number available memory areas under 256k:%d\n", n256kBlocks);
        printk("  number available memory areas over 256k:%d\n", nBigBlocks);
        printk("  total allocated memory:%dk/%dk\n", nAllocated*4, prv->npages*4);
#endif


        return IMG_ERROR_OUT_OF_MEMORY;
    }


    paCpuPhysAddr = CpuKmAddrToCpuPAddr(heap, psPages->pvImplData);
    IMG_ASSERT(paCpuPhysAddr != 0);
    if (paCpuPhysAddr == 0)
    {
        return IMG_ERROR_GENERIC_FAILURE;
    }

#ifdef CONFIG_ARM
    /* This flushes the outer cache in ARM, so we avoid memory corruption by late
       flushes of memory previously marked as cached. */
    if ((eMemAttrib & SYS_MEMATTRIB_CACHED) == 0) {
        mb();
        /* the following two calls are somewhat expensive, but are there for defensive reasons */
        flush_cache_all();
        outer_flush_all();
    }
#endif
    {
        IMG_PHYSADDR *      ppaCpuPhysAddrs;
        size_t numPages, pg_i, offset;

        // Memory for physical addresses
        numPages = (ui32Size + HOST_MMU_PAGE_SIZE - 1)/HOST_MMU_PAGE_SIZE;
        physAddrArrSize = sizeof(*ppaCpuPhysAddrs) * numPages;
        ppaCpuPhysAddrs = IMG_BIGORSMALL_ALLOC(physAddrArrSize);
        if (!ppaCpuPhysAddrs)
        {
            return IMG_ERROR_OUT_OF_MEMORY;
        }
        for (pg_i = 0, offset = 0; pg_i < numPages; offset += HOST_MMU_PAGE_SIZE, ++pg_i)
        {
                ppaCpuPhysAddrs[pg_i] = paCpuPhysAddr + offset;
        }
        // Set pointer to physical address in structure
        psPages->ppaPhysAddr = ppaCpuPhysAddrs;

    }
    /* Add this to the list of mappable regions...*/
    ui32Result = SYSBRGU_CreateMappableRegion(paCpuPhysAddr, ui32Size, eMemAttrib, psPages, &psPages->hRegHandle);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS) 
    {
        goto error_mappable_region;
    }

#if defined (CLEAR_PAGES)
        if (psPages->pvImplData)
    IMG_MEMSET( psPages->pvImplData, 0, ui32Size);
#endif

    return IMG_SUCCESS;

    /* Error handling. */
error_mappable_region:
    IMG_BIGORSMALL_FREE(physAddrArrSize, psPages->ppaPhysAddr);
    psPages->ppaPhysAddr = IMG_NULL;

    return ui32Result;
}

/*!
******************************************************************************

 @Function                GetCpuKmAddr

******************************************************************************/
static IMG_RESULT GetCpuKmAddr(
    SYSMEM_Heap *  heap,
    IMG_VOID **    ppvCpuKmAddr,
    IMG_HANDLE     hPagesHandle
)
{
    SYSMEMU_sPages *  psPages = hPagesHandle;

    if(psPages->pvCpuKmAddr == IMG_NULL)
    {
        psPages->pvCpuKmAddr = psPages->pvImplData;
    }

    *ppvCpuKmAddr = psPages->pvCpuKmAddr;

    /* Return success...*/
    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function                FreePages

******************************************************************************/
static IMG_VOID FreePages(
    SYSMEM_Heap *  heap,
    IMG_HANDLE     hPagesHandle
)
{
    struct priv_params *  prv = (struct priv_params *)heap->priv;
    SYSMEMU_sPages *      psPages = hPagesHandle;
    IMG_UINT32            ui32NoPages;
    IMG_UINT32            ui32PageIndex;
    IMG_UINT32            i;
    IMG_UINT32            physAddrArrSize;

    /* Calculate required no. of pages...*/
    ui32NoPages = (psPages->ui32Size + (HOST_MMU_PAGE_SIZE-1)) / HOST_MMU_PAGE_SIZE;

    /* If mapping then free on the copy of the page structure. */
    if (psPages->bImported)
    {
        if(IMG_NULL != psPages->ppaPhysAddr)
        {
            IMG_BIGORSMALL_FREE(ui32NoPages * sizeof(psPages->ppaPhysAddr[0]), psPages->ppaPhysAddr);
            psPages->ppaPhysAddr = IMG_NULL;
        }

        return;
    }

    if (psPages->bDuplicated)
    	return;

    /* Removed this from the list of mappable regions...*/
    SYSBRGU_DestroyMappableRegion(psPages->hRegHandle);

    /* Free memory...*/
    SYSOSKM_DisableInt();
    IMG_ASSERT((IMG_UINTPTR)psPages->pvCpuKmAddr >= prv->vstart);
    IMG_ASSERT((IMG_UINTPTR)psPages->pvCpuKmAddr < (prv->vstart + prv->size));

    /* Calculate page table size and index...*/
    physAddrArrSize = sizeof(psPages->ppaPhysAddr[0]) * ui32NoPages;
    ui32PageIndex = (IMG_UINT32) ((((IMG_UINTPTR)psPages->pvCpuKmAddr) - prv->vstart) / HOST_MMU_PAGE_SIZE);

    /* Mark pages as unallocated...*/
    for (i=0; i<ui32NoPages; i++)
    {
        IMG_ASSERT(prv->alloc_pool[ui32PageIndex+i]);
        prv->alloc_pool[ui32PageIndex+i] = IMG_FALSE;
    }
    prv->cur_index -= ui32NoPages;
    SYSOSKM_EnableInt();
    IMG_BIGORSMALL_FREE(physAddrArrSize, psPages->ppaPhysAddr);

}


static IMG_VOID UpdateMemory(
    SYSMEM_Heap *           heap,
    IMG_HANDLE              hPagesHandle,
    SYSMEM_UpdateDirection  dir
)
{
    return;
}

static SYSMEM_Ops devif_ops = {
        Initialise,
        Deinitialise,

        AllocPages,
        FreePages,

        IMG_NULL,
        IMG_NULL, /* Import Pages */

        GetCpuKmAddr,
        CpuKmAddrToCpuPAddr,
        CpuPAddrToCpuKmAddr,

        UpdateMemory
};

IMG_RESULT SYSMEMKM_AddDevIFMemory(
	SYSDEVU_sInfo	*sysdev,
    IMG_UINTPTR     vstart,
    IMG_PHYSADDR    pstart,
    IMG_UINT32      size,
    SYS_eMemPool *  peMemPool
)
{
    IMG_RESULT ui32Result;
    struct priv_params *prv;

    IMG_ASSERT(size != 0);
    IMG_ASSERT((vstart & (HOST_MMU_PAGE_SIZE - 1)) == 0);
    if((0 == size) ||
       (0 != (vstart & (HOST_MMU_PAGE_SIZE - 1))))
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    prv = (struct priv_params *)IMG_MALLOC(sizeof(*prv));
    IMG_ASSERT(IMG_NULL != prv);
    if (IMG_NULL == prv)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    IMG_MEMSET((void *)prv, 0, sizeof(*prv));

    IMG_ASSERT(size != 0);
    IMG_ASSERT((((IMG_UINTPTR)vstart) & (HOST_MMU_PAGE_SIZE-1)) == 0);

    // not allowed to use kmalloc for this size of buffer in the kernel.
    prv->npages = (size + (HOST_MMU_PAGE_SIZE-1)) / HOST_MMU_PAGE_SIZE;

    prv->alloc_pool = IMG_BIGALLOC(prv->npages);
    IMG_ASSERT(prv->alloc_pool != IMG_NULL);
    if(IMG_NULL == prv->alloc_pool)
    {
        ui32Result = IMG_ERROR_OUT_OF_MEMORY;
        goto error_pool_alloc;
    }
    IMG_MEMSET(prv->alloc_pool, 0, prv->npages);

    prv->pstart = pstart;
    prv->size = size;
    prv->vstart = vstart;

    ui32Result = SYSMEMU_AddMemoryHeap(&devif_ops, sysdev, IMG_TRUE, (IMG_VOID *)prv, peMemPool);
    IMG_ASSERT(IMG_SUCCESS == ui32Result);
    if(IMG_SUCCESS != ui32Result)
    {
        goto error_heap_add;
    }

    return IMG_SUCCESS;

    /* Error handling. */
error_heap_add:
    IMG_BIGFREE(prv->alloc_pool);
error_pool_alloc:
    IMG_FREE(prv);

    return ui32Result;
}
