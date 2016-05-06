/*!
 *****************************************************************************
 *
 * @File       sysmem_api_km.c
 * @Description    This file contains kernel mode implementation of the
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
#include "sysdev_utils.h"
#include <linux/kobject.h>
#include <linux/interrupt.h>
#include <asm/io.h>
#include <asm/page.h>
#include <linux/mm.h>
#include <linux/scatterlist.h>
#include <linux/dma-buf.h>
#include <linux/version.h>
#include <linux/module.h>
#include "target.h"
#include "sysenv_api_km.h"
#include "system.h"
#include "sysmem_utils.h"
#include "sysbrg_utils.h"
#include "sysos_api_km.h"
#include "report_api.h"
#include <asm/io.h>
#include <linux/mm.h>
#include <linux/gfp.h>
#include <linux/version.h>
#include <linux/vmalloc.h>
#include <linux/dma-mapping.h>

#include <linux/highmem.h>
#include <asm/cacheflush.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0)
#include <asm/barrier.h>
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,2,0)
#include <linux/export.h>
#endif

#if !defined dma_to_phys
#warning "dma_to_phys is supposed to be defined by arch-specific code, default to identity mapping (dma == phys)"
#define dma_to_phys(dev, dma) (dma)
#endif

#if !defined phys_to_dma
#warning "phys_to_dma is supposed to be defined by arch-specific code, default to identity mapping (dma == phys)"
#define phys_to_dma(dev, phys) (phys)
#endif

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
}


#define VAL64(val) (((int64_t)(val)) & 0x00000000ffffffffL)
#define VAL32(val) (((int32_t)(val)) & 0xffffffffL)

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
    IMG_UINT32 Res;
    dma_addr_t dma;
    unsigned numPages, pg_i;
    IMG_UINT64 *pCpuPhysAddrs;
    IMG_VOID **pCpuKernAddrs = IMG_NULL;
    size_t physAddrArrSize;
    struct device *dev = heap->sysdev->native_device;

    // This heap only supports uncached | write-combined memory allocations
    IMG_ASSERT(eMemAttrib == (SYS_MEMATTRIB_UNCACHED | SYS_MEMATTRIB_WRITECOMBINE));
    eMemAttrib = SYS_MEMATTRIB_UNCACHED | SYS_MEMATTRIB_WRITECOMBINE;

    numPages = (ui32Size + HOST_MMU_PAGE_SIZE - 1)/HOST_MMU_PAGE_SIZE;

    // Memory for physical addresses
    physAddrArrSize = sizeof(*pCpuPhysAddrs) * numPages;
    pCpuPhysAddrs = IMG_BIGORSMALL_ALLOC(physAddrArrSize);
    if (!pCpuPhysAddrs) {
        Res = IMG_ERROR_OUT_OF_MEMORY;
        goto errPhysAddrsAlloc;
    }

    psPages->pvCpuKmAddr = dma_alloc_coherent(dev, ui32Size, &dma, GFP_KERNEL | __GFP_HIGHMEM);
    if (!psPages->pvCpuKmAddr) {
    	pCpuKernAddrs = IMG_BIGORSMALL_ALLOC(numPages*(sizeof(IMG_VOID **)));
    	if (!pCpuKernAddrs) {
    		Res = IMG_ERROR_OUT_OF_MEMORY;
    		goto errKernAddrsAlloc;
    	}

    	for (pg_i = 0; pg_i < numPages; ++pg_i) {
    		pCpuKernAddrs[pg_i] = dma_alloc_coherent(dev, PAGE_SIZE, &dma, GFP_KERNEL | __GFP_HIGHMEM);
    		if (!pCpuKernAddrs[pg_i]) {
    			Res = IMG_ERROR_OUT_OF_MEMORY;
    			goto errPageAlloc;
    		}

			pCpuPhysAddrs[pg_i] = VAL64(dma_to_phys(dev, dma));
        }
    	psPages->pvImplData = (IMG_VOID *)((long)pCpuKernAddrs | 1);
    } else {
    	int paddr;

		psPages->pvImplData = (IMG_VOID *)dma;
    	paddr = dma_to_phys(dev, dma);

        for (pg_i = 0; pg_i < numPages; ++pg_i) {
			pCpuPhysAddrs[pg_i] = VAL64(paddr + (PAGE_SIZE * pg_i));
        }
    }

    // Set pointer to physical address in structure
    psPages->ppaPhysAddr = pCpuPhysAddrs;

    Res = SYSBRGU_CreateMappableRegion(psPages->ppaPhysAddr[0], ui32Size, eMemAttrib,
                                       psPages, &psPages->hRegHandle);
    DEBUG_REPORT(REPORT_MODULE_SYSMEM, "%s (unified) region of size %u phys 0x%llx",
                 __FUNCTION__, ui32Size, psPages->ppaPhysAddr[0]);
    IMG_ASSERT(Res == IMG_SUCCESS);
    if (Res != IMG_SUCCESS)
    {
        goto errCreateMapRegion;
    }

    return IMG_SUCCESS;

errCreateMapRegion:
errPageAlloc:
	for (--pg_i;pg_i >= 0; pg_i--) {
		dma_free_coherent(dev, PAGE_SIZE, pCpuKernAddrs[pg_i], psPages->ppaPhysAddr[pg_i]);
	}
	IMG_BIGORSMALL_FREE(numPages * sizeof(*pCpuKernAddrs), pCpuKernAddrs);
errKernAddrsAlloc:
    IMG_BIGORSMALL_FREE(numPages * sizeof(*pCpuPhysAddrs), pCpuPhysAddrs);
errPhysAddrsAlloc:
    return Res;
}

struct palloc_dmabuf_priv {
	struct sg_table *sgt;
	struct dma_buf *buf;
	struct dma_buf_attachment *attach;
};

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
	struct sg_table *sgt;
	struct dma_buf *buf;
    IMG_VOID *pvCpuKmAddr = IMG_NULL;
    IMG_RESULT result = IMG_ERROR_FATAL;
    unsigned numPages, pg_i = 0;
    struct scatterlist *sgl, *next;
    struct dma_buf_attachment *attach;
    struct palloc_dmabuf_priv *tmp;

    DEBUG_REPORT(REPORT_MODULE_SYSMEM, "Importing dmabuf %d of size %u", buff_fd, ui32Size);

    tmp = kzalloc(sizeof(struct palloc_dmabuf_priv), GFP_KERNEL);
    if (!tmp) {
    	IMG_ASSERT(IMG_FALSE);
    	goto alloc_priv_err;
    }

    buf = dma_buf_get(buff_fd);
    if (IS_ERR(buf)) {
    	IMG_ASSERT(IMG_FALSE);
    	goto buf_no_found;
    }

    numPages = (ui32Size + PAGE_SIZE - 1) / PAGE_SIZE;

    IMG_ASSERT(sysdev);
    IMG_ASSERT(sysdev->native_device);
    attach = dma_buf_attach(buf, sysdev->native_device);
    if (IS_ERR(attach)) {
    	IMG_ASSERT(IMG_FALSE);
    	goto attach_error;
    }

    sgt = dma_buf_map_attachment(attach, DMA_BIDIRECTIONAL);
    if (IS_ERR(sgt)) {
    	IMG_ASSERT(IMG_FALSE);
		goto map_error;
    }

	sgl = sgt->sgl;

	if (sgl == NULL) {
		IMG_ASSERT(IMG_FALSE);
		REPORT(REPORT_MODULE_SYSMEM, REPORT_ERR, "Error obtaining scatter list");
		goto map_error;
	}

	// Get physical addresses from scatter list
	for (next = sgl; next; next = sg_next(next))
	{
		int offset;
		dma_addr_t chunkBase = sg_phys(next);

		for (offset = 0; offset < next->length; offset += PAGE_SIZE, ++pg_i)
		{
			if (pg_i >= numPages)
				break;

			pPhyAddrs[pg_i] = chunkBase + offset;
		}

		if (pg_i >= numPages)
			break;
	}

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


	if (kernelMapped) {
		result = dma_buf_begin_cpu_access(buf, 0 /* start */, ui32Size /* size */, DMA_BIDIRECTIONAL);
		if (!result) {
			IMG_ASSERT(IMG_FALSE);
			REPORT(REPORT_MODULE_SYSMEM, REPORT_ERR, "begin_cpu_access failed");
			goto cpu_access_error;
		}

		pvCpuKmAddr = dma_buf_vmap(buf);
		if (!pvCpuKmAddr) {
			IMG_ASSERT(IMG_FALSE);
			REPORT(REPORT_MODULE_SYSMEM, REPORT_ERR, "Error mapping to kernel address");
			result = IMG_ERROR_FATAL;
			goto buf_vmap_error;
		}
	}

    tmp->attach = attach;
    tmp->buf = buf;
    tmp->sgt = sgt;

    psPages->sysdev = sysdev;
    psPages->hRegHandle = NULL;
    //psPages->ppaPhysAddr = pPhyAddrs;
    psPages->pvCpuKmAddr = pvCpuKmAddr;
    psPages->pvImplData = (IMG_HANDLE)tmp;

    return IMG_SUCCESS;

buf_vmap_error:
	dma_buf_end_cpu_access(buf, 0, ui32Size, DMA_BIDIRECTIONAL);
cpu_access_error:
	dma_buf_unmap_attachment(attach, sgt, DMA_BIDIRECTIONAL);
map_error:
	dma_buf_detach(buf, attach);
attach_error:
	dma_buf_put(buf);
buf_no_found:
alloc_priv_err:
    return result;
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
        IMG_UINT32 numPages;
        pgprot_t pageProt;
        unsigned pg_i;
        struct page **pages;

        pageProt = PAGE_KERNEL;
        numPages = (psPages->ui32Size + HOST_MMU_PAGE_SIZE - 1)/HOST_MMU_PAGE_SIZE;


#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,29)
        /* Write combined implies non-cached in Linux x86. If we additionally call
           pgprot_noncached, we will not have write combining, just non-cached. */
        if ((psPages->eMemAttrib & SYS_MEMATTRIB_WRITECOMBINE) != 0)
        {
            pageProt = pgprot_writecombine(pageProt);
        }
#if defined(CONFIG_X86)
        else
#endif
#endif
        /* If uncached...*/
        if ((psPages->eMemAttrib & SYS_MEMATTRIB_UNCACHED) != 0)
        {
            pageProt = pgprot_noncached(pageProt);
        }

        pages = IMG_BIGORSMALL_ALLOC(numPages*(sizeof *pages));
        IMG_ASSERT(IMG_NULL != pages);
        if(IMG_NULL == pages)
        {
            return IMG_ERROR_OUT_OF_MEMORY;
        }
        for (pg_i = 0; pg_i < numPages; ++pg_i) {
        	pages[pg_i] = pfn_to_page(VAL32((psPages->ppaPhysAddr[pg_i]) >> PAGE_SHIFT));
        }

        psPages->pvCpuKmAddr = vmap(pages, numPages, VM_MAP, pageProt);

        IMG_BIGORSMALL_FREE(numPages*sizeof(*pages), pages);

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
    SYSMEMU_sPages *  psPages = hPagesHandle;
    size_t            numPages;
    struct device *dev = psPages->sysdev->native_device;

    numPages = (psPages->ui32Size + HOST_MMU_PAGE_SIZE - 1)/HOST_MMU_PAGE_SIZE;

    if (psPages->bImported) {
		struct palloc_dmabuf_priv *priv = psPages->pvImplData;

		IMG_ASSERT(psPages);
		if (!psPages)
			return;

		DEBUG_REPORT(REPORT_MODULE_SYSMEM, "Releasing dmabuf 0x%p", psPages);

		if (psPages->pvCpuKmAddr) {
			dma_buf_vunmap(priv->buf, psPages->pvCpuKmAddr);
			dma_buf_end_cpu_access(priv->buf, 0, psPages->ui32Size, DMA_BIDIRECTIONAL);
		}


		if (priv->sgt)
			dma_buf_unmap_attachment(priv->attach, priv->sgt, DMA_BIDIRECTIONAL);


		if (priv->attach)
			dma_buf_detach(priv->buf, priv->attach);

		dma_buf_put(priv->buf);

		kfree(priv);

		psPages->pvImplData = IMG_NULL;

		if(psPages->ppaPhysAddr != IMG_NULL)
		{
			IMG_BIGORSMALL_FREE(numPages * sizeof(psPages->ppaPhysAddr[0]), psPages->ppaPhysAddr);
			psPages->ppaPhysAddr = IMG_NULL;
		}

		return;
    }

    if (psPages->bDuplicated)
    	return;

    /* Removed this from the list of mappable regions...*/
    SYSBRGU_DestroyMappableRegion(psPages->hRegHandle);

    /* Free pages and mapping if present */
    {
        unsigned pg_i;

        if ((long)psPages->pvImplData & 0x1) {
			IMG_VOID **pCpuKernAddrs;

        	if (psPages->pvCpuKmAddr) {
				vunmap(psPages->pvCpuKmAddr);
			}

        	pCpuKernAddrs = (IMG_VOID **)((long)psPages->pvImplData & ~0x1);
			for (pg_i = 0; pg_i < numPages; ++pg_i) {
				dma_free_coherent(dev, PAGE_SIZE, pCpuKernAddrs[pg_i], phys_to_dma(dev, psPages->ppaPhysAddr[pg_i]));
			}
			IMG_BIGORSMALL_FREE(numPages * sizeof(IMG_VOID *), pCpuKernAddrs);
        } else {
        	dma_free_coherent(dev, psPages->ui32Size, psPages->pvCpuKmAddr, (dma_addr_t)(psPages->pvImplData));
        }
    }

    IMG_BIGORSMALL_FREE(numPages * sizeof(psPages->ppaPhysAddr[0]), psPages->ppaPhysAddr);
}

static IMG_VOID *CpuPAddrToCpuKmAddr(
        SYSMEM_Heap *heap, IMG_UINT64 pvCpuPAddr
)
{
    IMG_ASSERT(!"SYSDEVU1_CpuPAddrToCpuKmAddr not implemented");
    return NULL;
}

static IMG_UINT64 CpuKmAddrToCpuPAddr(
    SYSMEM_Heap *  heap,
    IMG_VOID *     pvCpuKmAddr
)
{
    IMG_UINT64 ret = 0;

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

    return VAL64(ret);
}

static IMG_VOID UpdateMemory(
    struct SYSMEM_Heap *    heap,
    IMG_HANDLE              hPagesHandle,
    SYSMEM_UpdateDirection  dir
)
{
	if(dir == CPU_TO_DEV) {
#ifdef CONFIG_ARM
		/* ARM Cortex write buffer needs to be synchronised before device can access it */
		dmb();
#else
		mb();
#endif
	}
	return;
}

static IMG_VOID UpdateMemoryRegion(
    struct SYSMEM_Heap *    heap,
    IMG_HANDLE              hPagesHandle,
    SYSMEM_UpdateDirection  dir,
    IMG_UINT32 offset, IMG_UINT32 size
)
{
	UpdateMemory(heap, hPagesHandle, dir);
}

static int map_user(SYSMEMU_sPages *psPages, IMG_VOID *priv) {
	struct vm_area_struct *vma = priv;
	int i, offset, ret;

	for(i = 0, offset = 0;
		i < (vma->vm_end - vma->vm_start) / PAGE_SIZE;
		++i, offset += PAGE_SIZE)
	{
		phys_addr_t pfn = psPages->ppaPhysAddr[i] >> PAGE_SHIFT;
		unsigned long start = vma->vm_start + offset;

		/*
		* On x86 remap_pfn_range will use the flags for
		* the kernel direct mapped memory (if any)
		* instead of the vm_page_prot flags which will override
		* our write-combining flags!
		* NOTE: We can use page->flags |= _PGMT_WC to override that (!?)
		*/

#ifdef CONFIG_X86
		ret = vm_insert_page(vma, start, pfn_to_page(pfn));
#else
		ret = remap_pfn_range(vma, start, pfn, PAGE_SIZE, vma->vm_page_prot);
#endif

		IMG_ASSERT(ret == 0);

		if (ret != 0)
			break;
	}

	return ret;
}

static SYSMEM_Ops coherent_ops = {
        .Initialise = Initialise,
        .Deinitialise = Deinitialise,

        .AllocatePages = AllocPages,
        .FreePages = FreePages,

        .GetCpuKmAddr = GetCpuKmAddr,
        .CpuKmAddrToCpuPAddr = CpuKmAddrToCpuPAddr,
        .CpuPAddrToCpuKmAddr = CpuPAddrToCpuKmAddr,

        .ImportPages = ImportPages,

        .UpdateMemory = UpdateMemory,
        .UpdateMemoryRegion = UpdateMemoryRegion,

        .MapUser = map_user
};

IMG_RESULT SYSMEMKM_AddCoherentMemory(
	SYSDEVU_sInfo *sysdev,
    SYS_eMemPool *peMemPool
)
{
    IMG_RESULT ui32Result;
    SYS_eMemPool memPool;

	ui32Result = SYSMEMU_AddMemoryHeap(&coherent_ops, sysdev, IMG_TRUE, IMG_NULL, &memPool);
	IMG_ASSERT(IMG_SUCCESS == ui32Result);
	if (IMG_SUCCESS != ui32Result)
	{
		return ui32Result;
	}

    *peMemPool = memPool;

    return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(SYSMEMKM_AddCoherentMemory)
