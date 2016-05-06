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
#include "sysdev_utils.h"
#include "sysbrg_utils.h"
#include "sysos_api_km.h"
#include "system.h"
#include <linux/mm.h>
#include <linux/genalloc.h>

//#define CLEAR_PAGES     (1)                         //!< Defined to clear memory pages (normally only for debug/test)


struct priv_params {
    IMG_UINTPTR  vstart;
    IMG_PHYSADDR   pstart;
    IMG_UINT32   size;

    struct gen_pool *pool;
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
    struct priv_params *priv = (struct priv_params *)heap->priv;

    /* If we have a page allocation array - free it...*/
    gen_pool_destroy(priv->pool);
    IMG_FREE(priv);
    heap->priv = IMG_NULL;
}

static IMG_VOID *CpuPAddrToCpuKmAddr(
    SYSMEM_Heap *  heap,
    IMG_PHYSADDR   paCpuPAddr
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
    struct priv_params *  prv = (struct priv_params *)heap->priv;
    IMG_PHYSADDR          paCpuPhysAddr, paOffset;
    IMG_RESULT            ui32Result;
    IMG_PHYSADDR *        ppaCpuPhysAddrs;
    size_t                numPages, pg_i;
    size_t                physAddrArrSize;

    /* Calculate required no. of pages...*/
    psPages->pvImplData = (IMG_VOID *)gen_pool_alloc(prv->pool, ui32Size);
    if(psPages->pvImplData == IMG_NULL)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }

    paCpuPhysAddr = CpuKmAddrToCpuPAddr(heap, psPages->pvImplData);
    IMG_ASSERT(paCpuPhysAddr != 0);
    if (paCpuPhysAddr == 0)
    {
        ui32Result = IMG_ERROR_GENERIC_FAILURE;
        goto error_map;
    }

    numPages = (ui32Size + HOST_MMU_PAGE_SIZE - 1)/HOST_MMU_PAGE_SIZE;
    physAddrArrSize = sizeof(*ppaCpuPhysAddrs) * numPages;
    ppaCpuPhysAddrs = IMG_BIGORSMALL_ALLOC(physAddrArrSize);
    if (!ppaCpuPhysAddrs)
    {
        ui32Result = IMG_ERROR_OUT_OF_MEMORY;
        goto error_array_alloc;
    }
    for (pg_i = 0, paOffset = 0; pg_i < numPages; paOffset += HOST_MMU_PAGE_SIZE, ++pg_i)
    {
        ppaCpuPhysAddrs[pg_i] = paCpuPhysAddr + paOffset;
    }
    psPages->ppaPhysAddr = ppaCpuPhysAddrs;

    /* Add this to the list of mappable regions...*/
    ui32Result = SYSBRGU_CreateMappableRegion(psPages->ppaPhysAddr[0], ui32Size, eMemAttrib, psPages, &psPages->hRegHandle);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error_region_create;
    }

#if defined (CLEAR_PAGES)
    IMG_MEMSET( psPages->pvImplData, 0, ui32Size);
#endif

    return IMG_SUCCESS;

    /* Error handling. */
error_region_create:
    IMG_BIGORSMALL_FREE(physAddrArrSize, psPages->ppaPhysAddr);
error_array_alloc:
error_map:
    gen_pool_free(prv->pool, (unsigned long)psPages->pvImplData, ui32Size);

    psPages->ppaPhysAddr = IMG_NULL;
    psPages->hRegHandle = IMG_NULL;

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
    IMG_UINT32            physAddrArrSize;

    /* Calculate required no. of pages...*/
    ui32NoPages = (psPages->ui32Size + (HOST_MMU_PAGE_SIZE-1)) / HOST_MMU_PAGE_SIZE;

    /* If mapping then free on the copy of the page structure. */
    /* This will happen after we call this function by sysmemutils */
    if (psPages->bImported)
    {
    	if (IMG_NULL != psPages->ppaPhysAddr)
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

    /* Calculate the size of page table...*/
    physAddrArrSize = sizeof(psPages->ppaPhysAddr[0]) * ui32NoPages;

    /* Free memory...*/
    gen_pool_free(prv->pool, (unsigned long)psPages->pvImplData, psPages->ui32Size);
    IMG_BIGORSMALL_FREE(physAddrArrSize, psPages->ppaPhysAddr);
    psPages->ppaPhysAddr = IMG_NULL;
    psPages->hRegHandle = IMG_NULL;
}


static IMG_VOID UpdateMemory(
    SYSMEM_Heap *           heap,
    IMG_HANDLE              hPagesHandle,
    SYSMEM_UpdateDirection  dir
)
{
    return;
}

static int map_user(SYSMEMU_sPages *psPages, IMG_VOID *priv) {
	struct vm_area_struct *vma = priv;
	int ret;
    ret =  remap_pfn_range(vma,
                            vma->vm_start,
                            vma->vm_pgoff,
                            vma->vm_end - vma->vm_start,
                            vma->vm_page_prot
                           );
    IMG_ASSERT(ret == 0);
	return ret;
}


static SYSMEM_Ops carveout_ops = {
        .Initialise = Initialise,
        .Deinitialise = Deinitialise,

        .AllocatePages = AllocPages,
        .FreePages = FreePages,

        .GetCpuKmAddr = GetCpuKmAddr,
        .CpuKmAddrToCpuPAddr = CpuKmAddrToCpuPAddr,
        .CpuPAddrToCpuKmAddr = CpuPAddrToCpuKmAddr,

        .UpdateMemory = UpdateMemory,

        .MapUser = map_user
};


IMG_RESULT SYSMEMKM_AddCarveoutMemory(
	SYSDEVU_sInfo *sysdev,
    IMG_UINTPTR     vstart,
    IMG_PHYSADDR    pstart,
    IMG_UINT32      size,
    SYS_eMemPool *  peMemPool
)
{
    IMG_RESULT ui32Result;
    struct priv_params *prv;
    struct gen_pool *pool = gen_pool_create(12, -1);

    prv = (struct priv_params *)IMG_MALLOC(sizeof(*prv));
    IMG_ASSERT(prv != IMG_NULL);
    if(IMG_NULL == prv)
    {
        ui32Result = IMG_ERROR_OUT_OF_MEMORY;
        goto error_priv_alloc;
    }
    IMG_MEMSET((void *)prv, 0, sizeof(*prv));

    IMG_ASSERT(pool != IMG_NULL);
    IMG_ASSERT(size != 0);
    IMG_ASSERT((vstart & (HOST_MMU_PAGE_SIZE-1)) == 0);
    gen_pool_add_virt(pool, (unsigned long)vstart, (unsigned long)pstart, size, -1);

    prv->pool = pool;
    prv->pstart = pstart;
    prv->size = size;
    prv->vstart = vstart;

    ui32Result = SYSMEMU_AddMemoryHeap(&carveout_ops, sysdev, IMG_TRUE, (IMG_VOID *)prv, peMemPool);
    IMG_ASSERT(IMG_SUCCESS == ui32Result);
    if(IMG_SUCCESS != ui32Result)
    {
        goto error_heap_add;
    }

    return IMG_SUCCESS;

error_heap_add:
    IMG_FREE(prv);
error_priv_alloc:
    gen_pool_destroy(pool);

    return ui32Result;
}
IMGVIDEO_EXPORT_SYMBOL(SYSMEMKM_AddCarveoutMemory)
