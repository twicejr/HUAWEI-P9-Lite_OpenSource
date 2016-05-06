/*!
 *****************************************************************************
 *
 * @File       sysmem_api_km.c
 * @Description    This file contains kernel mode implementation of the
 *  System Memory Kernel Mode API, for devices with ION heap allocator.
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
#include <linux/mm.h>
#include <linux/version.h>

/*
 * gcc preprocessor defines "linux" as "1".
 * [ http://stackoverflow.com/questions/19210935 ]
 * IMG_KERNEL_ION_HEADER can be <linux/ion.h>, which expands to <1/ion.h>
 */
#undef linux
#include IMG_KERNEL_ION_HEADER
#include <linux/scatterlist.h>
#include <linux/dma-mapping.h>

#include "img_errors.h"
#include "report_api.h"

#include <ion_client.h>

#ifdef IMG_MEMALLOC_UNIFIED_VMALLOC
#define ION_SYSTEM_HEAP
#endif

/*!
******************************************************************************
 @Function                Initialise
******************************************************************************/
static IMG_RESULT Initialise(SYSMEM_Heap *heap)
{
	struct ion_client *ion_client;

	ion_client = get_ion_client();
	if (!ion_client) {
		REPORT(REPORT_MODULE_SYSMEM, REPORT_ERR, "Error retrieving ion client");
		return IMG_ERROR_FATAL;
    }

	heap->priv = ion_client;

	return IMG_SUCCESS;
}

/*!
******************************************************************************
 @Function                Deinitialise
******************************************************************************/
static IMG_VOID Deinitialise(SYSMEM_Heap *heap)
{
	release_ion_client();
}

/*****************************************************************************
 @Function                AllocPages
******************************************************************************/
static IMG_RESULT AllocPages(
	SYSMEM_Heap *		heap,
	IMG_UINT32			ui32Size,
	SYSMEMU_sPages *	psPages,
	SYS_eMemAttrib		eMemAttrib
)
{
    IMG_UINT32           Res;
    struct ion_handle *  ion_handle;
    unsigned             allocFlags;
    struct ion_client *  ion_client;
    IMG_UINT64 *         pCpuPhysAddrs;
    size_t               numPages;
    size_t               physAddrArrSize;

    ion_client = (struct ion_client *)heap->priv;

    if (   (eMemAttrib & SYS_MEMATTRIB_WRITECOMBINE)
        || (eMemAttrib & SYS_MEMATTRIB_UNCACHED))
    {
        allocFlags = 0;
    } else {
        allocFlags = ION_FLAG_CACHED;
    }

    if (eMemAttrib == SYS_MEMATTRIB_UNCACHED)
        REPORT(REPORT_MODULE_SYSMEM, REPORT_WARNING,
               "Purely uncached memory is not supported by ION");

    // PAGE_SIZE aligment, heap depends on platform
    ion_handle = ion_alloc(ion_client, ui32Size, PAGE_SIZE,
    					ION_HEAP_SYSTEM_MASK,
                          allocFlags);
    if (!ion_handle) {
        REPORT(REPORT_MODULE_SYSMEM, REPORT_ERR,
               "Error allocating %u bytes from ion", ui32Size);
        Res = IMG_ERROR_OUT_OF_MEMORY;
        goto errAlloc;
    }

    /* Find out physical addresses in the mappable region */
    numPages = (ui32Size + HOST_MMU_PAGE_SIZE - 1)/HOST_MMU_PAGE_SIZE;

    physAddrArrSize = sizeof *pCpuPhysAddrs * numPages;
    pCpuPhysAddrs = IMG_BIGORSMALL_ALLOC(physAddrArrSize);
    if (!pCpuPhysAddrs) {
        Res = IMG_ERROR_OUT_OF_MEMORY;
        goto errPhysArrAlloc;
    }

    {
        struct scatterlist *psScattLs, *psScattLsAux;
        struct sg_table *psSgTable;
        size_t pg_i = 0;

        psSgTable = ion_sg_table(ion_client, ion_handle);
        if (psSgTable == NULL)
        {
            REPORT(REPORT_MODULE_SYSMEM, REPORT_ERR, "Error obtaining sg table");
            Res = IMG_ERROR_FATAL;
            goto errGetPhys;
        }
        psScattLs = psSgTable->sgl;

        if (psScattLs == NULL)
        {
            REPORT(REPORT_MODULE_SYSMEM, REPORT_ERR, "Error obtaining scatter list");
            Res = IMG_ERROR_FATAL;
            goto errGetPhys;
        }

        // Get physical addresses from scatter list
        for (psScattLsAux = psScattLs; psScattLsAux; psScattLsAux = sg_next(psScattLsAux))
        {
            int offset;
            dma_addr_t chunkBase = sg_phys(psScattLsAux);

            for (offset = 0; offset < psScattLsAux->length; offset += PAGE_SIZE, ++pg_i)
            {
                if (pg_i >= numPages)
                    break;

                //pCpuPhysAddrs[pg_i] = dma_map_page(NULL, page, 0, PAGE_SIZE, DMA_FROM_DEVICE);
                pCpuPhysAddrs[pg_i] = chunkBase + offset;
            }
            if (pg_i >= numPages)
                break;
        }
    }

    // Set pointer to physical address in structure
    psPages->ppaPhysAddr = pCpuPhysAddrs;

    DEBUG_REPORT(REPORT_MODULE_SYSMEM, "%s region of size %u phys 0x%llx",
                 __FUNCTION__, ui32Size, psPages->ppaPhysAddr[0]);

    Res = SYSBRGU_CreateMappableRegion(psPages->ppaPhysAddr[0], ui32Size, eMemAttrib,
    						psPages, &psPages->hRegHandle);
    if (Res != IMG_SUCCESS) {
        REPORT(REPORT_MODULE_SYSMEM, REPORT_ERR,
               "Error %u in SYSBRGU_CreateMappableRegion", Res);
        goto errCreateMapRegion;
    }

    psPages->pvImplData = ion_handle;

    return IMG_SUCCESS;

errCreateMapRegion:
errGetPhys:
    IMG_BIGORSMALL_FREE(numPages*sizeof(*pCpuPhysAddrs), pCpuPhysAddrs);
errPhysArrAlloc:
    ion_unmap_kernel(ion_client, ion_handle);
    ion_free(ion_client, ion_handle);
errAlloc:
    return Res;
}

/*!
******************************************************************************

 @Function              ImportPages

******************************************************************************/
static IMG_RESULT ImportPages(
    SYSMEM_Heap		*heap,
    SYSDEVU_sInfo	*sysdev,
    IMG_UINT32		ui32Size,
    SYSMEMU_sPages *psPages,
    SYS_eMemAttrib	eMemAttrib,
    IMG_INT32		buff_fd,
    IMG_UINT64		*pPhyAddrs,
    IMG_VOID		*priv,
    IMG_BOOL		kernelMapped
)
{
	size_t numPages = (ui32Size + HOST_MMU_PAGE_SIZE - 1)/HOST_MMU_PAGE_SIZE;
	struct ion_handle *ionHandle;
	IMG_RESULT result = IMG_ERROR_FATAL;
	unsigned pg_i = 0;
	struct ion_client *pIONcl;

	DEBUG_REPORT(REPORT_MODULE_SYSMEM, "Importing buff_fd %d of size %u", buff_fd, ui32Size);

	pIONcl = get_ion_client();
	if (!pIONcl)
		goto exitFailGetClient;

	ionHandle = ion_import_dma_buf(pIONcl, buff_fd);
	if (IS_ERR(ionHandle)) {
		REPORT(REPORT_MODULE_SYSMEM, REPORT_ERR, "Error obtaining handle from fd %d", buff_fd);
		result = IMG_ERROR_FATAL;
		goto exitFailImportFD;
	}

	psPages->pvImplData = ionHandle;

#if defined(ION_SYSTEM_HEAP)
	{
		struct scatterlist *psScattLs, *psScattLsAux;
		struct sg_table *psSgTable;

		psSgTable = ion_sg_table(pIONcl, ionHandle);

		if (psSgTable == NULL)
		{
			REPORT(REPORT_MODULE_SYSMEM, REPORT_ERR, "Error obtaining sg table");
			result = IMG_ERROR_FATAL;
			goto exitFailMap;
		}
		psScattLs = psSgTable->sgl;

		if (psScattLs == NULL)
		{
			REPORT(REPORT_MODULE_SYSMEM, REPORT_ERR, "Error obtaining scatter list");
			result = IMG_ERROR_FATAL;
			goto exitFailMap;
		}

		// Get physical addresses from scatter list
		for (psScattLsAux = psScattLs; psScattLsAux; psScattLsAux = sg_next(psScattLsAux))
		{
			int offset;
			dma_addr_t chunkBase = sg_phys(psScattLsAux);

			for (offset = 0; offset < psScattLsAux->length; offset += PAGE_SIZE, ++pg_i)
			{
				if (pg_i >= numPages)
					break;

				pPhyAddrs[pg_i] = chunkBase + offset;
			}

			if (pg_i >= numPages)
				break;
		}

		if (kernelMapped)
			psPages->pvCpuKmAddr = ion_map_kernel(pIONcl, ionHandle);
	}
#else
	{
		int offset;
		ion_phys_addr_t physaddr;
		size_t len = 0;

		result = ion_phys(pIONcl, ionHandle, &physaddr, &len);

		if(result)
		{
			IMG_ASSERT(!"ion_phys failed");
			result = IMG_ERROR_FATAL;
			goto exitFailMap;
		}

		for (offset = 0; pg_i < numPages; offset += PAGE_SIZE, ++pg_i)
		{
			if (pg_i >= numPages)
				break;
			pPhyAddrs[pg_i] = physaddr + offset;
		}

		if (kernelMapped)
			psPages->pvCpuKmAddr = SYSMEMU_CpuPAddrToCpuKmAddr(heap->memId, physaddr);
	}
#endif

	{
		size_t  physAddrArrSize = numPages * sizeof(psPages->ppaPhysAddr[0]);
		size_t  phy_i;

		psPages->ppaPhysAddr = IMG_BIGORSMALL_ALLOC(physAddrArrSize);
		IMG_ASSERT(psPages->ppaPhysAddr != IMG_NULL);
		if (psPages->ppaPhysAddr == IMG_NULL)
		{
			return IMG_ERROR_OUT_OF_MEMORY;
		}

		for (phy_i = 0; phy_i < numPages; ++phy_i)
			psPages->ppaPhysAddr[phy_i] = pPhyAddrs[phy_i];
	}

	if (kernelMapped && psPages->pvCpuKmAddr == NULL) {
		REPORT(REPORT_MODULE_SYSMEM, REPORT_ERR, "Error mapping to kernel address");
		result = IMG_ERROR_FATAL;
		goto exitFailMapKernel;
	}

	result = IMG_SUCCESS;

exitFailMapKernel:
exitFailMap:
exitFailImportFD:
exitFailGetClient:
	return result;
}

/*!
******************************************************************************
 @Function                GetCpuKmAddr
******************************************************************************/
static IMG_RESULT GetCpuKmAddr(
	SYSMEM_Heap *			heap,
	IMG_VOID **				ppvCpuKmAddr,
	IMG_HANDLE 				hPagesHandle
)
{
	struct ion_client *ion_client = heap->priv;
    SYSMEMU_sPages *  psPages = hPagesHandle;

    if(psPages->pvCpuKmAddr == IMG_NULL)
    {
        psPages->pvCpuKmAddr = ion_map_kernel(ion_client, psPages->pvImplData);

        if (!psPages->pvCpuKmAddr) {
            REPORT(REPORT_MODULE_SYSMEM, REPORT_ERR,
                   "Error mapping buffer to kernel address space");
            return IMG_ERROR_FATAL;
        }
        
    }
    *ppvCpuKmAddr = psPages->pvCpuKmAddr;
    /* Return success...*/
    return IMG_SUCCESS;
}


/*****************************************************************************
 @Function                FreePages
******************************************************************************/
static IMG_VOID FreePages(
	SYSMEM_Heap *			heap,
	IMG_HANDLE				hPagesHandle
)
{
    size_t numPages;
    SYSMEMU_sPages *     psPages = hPagesHandle;
    struct ion_client *ion_client;
    struct ion_handle *ion_handle;

    ion_client = heap->priv;

    if (psPages->bImported)
    {
		IMG_RESULT result = IMG_ERROR_FATAL;
		struct ion_client *pIONcl;
		struct ion_handle *ionHandle;

		DEBUG_REPORT(REPORT_MODULE_SYSMEM, "Releasing ion_handle 0x%p", psPages->pvImplData);

		if (psPages->ppaPhysAddr) {
			/*Free array with physical addresses*/
			numPages = (psPages->ui32Size + HOST_MMU_PAGE_SIZE - 1)/HOST_MMU_PAGE_SIZE;
			IMG_BIGORSMALL_FREE(numPages * sizeof(*psPages->ppaPhysAddr), psPages->ppaPhysAddr);
			psPages->ppaPhysAddr = NULL;
		}

		IMG_ASSERT(psPages->pvImplData);
		ionHandle = (struct ion_handle *)psPages->pvImplData;

		pIONcl = get_ion_client();
		if (pIONcl) {
#if defined(ION_SYSTEM_HEAP)
			if (psPages->pvCpuKmAddr)
				ion_unmap_kernel(pIONcl, ionHandle);
#endif
			ion_free(pIONcl, ionHandle);
			result = IMG_SUCCESS;
		} else {
			REPORT(REPORT_MODULE_SYSMEM, REPORT_ERR, "Releasing cannot find ION client");
		}

        return;
    }

    if (psPages->bDuplicated)
    	return;

    /* Remove from the list of mappable regions */
    SYSBRGU_DestroyMappableRegion(psPages->hRegHandle);

    /* Free array with physical addresses */
    numPages = (psPages->ui32Size + HOST_MMU_PAGE_SIZE - 1)/HOST_MMU_PAGE_SIZE;
    IMG_BIGORSMALL_FREE(numPages * sizeof(*psPages->ppaPhysAddr), psPages->ppaPhysAddr);

    /* Free memory */
    ion_handle = psPages->pvImplData;

    if (psPages->pvCpuKmAddr)
        ion_unmap_kernel(ion_client, ion_handle);

    ion_free(ion_client, ion_handle);
}

static IMG_PHYSADDR CpuKmAddrToCpuPAddr(
    SYSMEM_Heap *  heap,
    IMG_VOID *     pvCpuKmAddr
)
{
    IMG_PHYSADDR ret = 0;

    if(virt_addr_valid(pvCpuKmAddr))
    {
        /* direct mapping of kernel addresses.
         * this works for kmalloc.
         */
        ret = virt_to_phys(pvCpuKmAddr);
    }
    else
    {
        /* walk the page table.
         * Works for ioremap, vmalloc, and kmalloc(GPF_DMA),
          but not, for some reason, kmalloc(GPF_KERNEL)
         */
        struct page * pg = vmalloc_to_page(pvCpuKmAddr);
        if(pg) {
            ret = page_to_phys(pg);
        }
        else {
            IMG_ASSERT(!"vmalloc_to_page failure");
        }
    }

    IMG_ASSERT(ret != 0);

    return ret;
}

static IMG_VOID *CpuPAddrToCpuKmAddr(
        SYSMEM_Heap *heap, IMG_PHYSADDR paCpuPAddr
)
{
    IMG_ASSERT(!"SYSDEVU1_CpuPAddrToCpuKmAddr not implemented");
    return NULL;
}

static IMG_VOID UpdateMemory(
    struct SYSMEM_Heap *    heap,
    IMG_HANDLE              hPagesHandle,
    SYSMEM_UpdateDirection  dir
)
{

}

static SYSMEM_Ops ion_ops = {
		.Initialise = Initialise,
		.Deinitialise = Deinitialise,

		.AllocatePages = AllocPages,
		.FreePages = FreePages,

		.GetCpuKmAddr = GetCpuKmAddr,
		.CpuKmAddrToCpuPAddr = CpuKmAddrToCpuPAddr,
		.CpuPAddrToCpuKmAddr = CpuPAddrToCpuKmAddr,

		.ImportPages = ImportPages,

		.UpdateMemory = UpdateMemory
};

extern IMG_RESULT SYSMEMKM_AddIONMemory(SYSDEVU_sInfo *sysdev, SYS_eMemPool *peMemPool)
{
	static SYS_eMemPool memPool;
	static IMG_BOOL initialized = IMG_FALSE;

	/* Only one system heap is allowed to be inserted - obviously - */
	if(initialized)
		return memPool;

	SYSMEMU_AddMemoryHeap(&ion_ops, sysdev, IMG_FALSE, IMG_NULL, &memPool);

	initialized = IMG_TRUE;

	*peMemPool = memPool;

	return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(SYSMEMKM_AddIONMemory)
