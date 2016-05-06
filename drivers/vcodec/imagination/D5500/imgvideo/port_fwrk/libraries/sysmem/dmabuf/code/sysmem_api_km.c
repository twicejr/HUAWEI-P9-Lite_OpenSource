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

#include <linux/mm.h>
#include <linux/gfp.h>
#include <linux/module.h>
#include <linux/vmalloc.h>
#include <linux/dma-buf.h>
#include <linux/scatterlist.h>
#include <linux/dma-mapping.h>

#include "img_defs.h"
#include "report_api.h"
#include "sysmem_utils.h"

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
		//Using sg_dma_address(next) rather than sg_phys(next) to get the base physical address.
		//sg_phys(next) return incorrect value when used with DMA API in Linux
		int offset;
		dma_addr_t chunkBase = sg_dma_address(next);

		for (offset = 0; offset < sg_dma_len(next); offset += PAGE_SIZE, ++pg_i)
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

		for (phy_i = 0; phy_i < numPages; ++phy_i) {
			psPages->ppaPhysAddr[phy_i] = pPhyAddrs[phy_i];
		}

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
 @Function                FreePages

******************************************************************************/
static IMG_VOID FreePages(
    SYSMEM_Heap *  heap,
    IMG_HANDLE     hPagesHandle
)
{
    SYSMEMU_sPages *  psPages = hPagesHandle;
    size_t            numPages;

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
    }
}

static SYSMEM_Ops dmabuf_ops = {
        .FreePages = FreePages,
        .ImportPages = ImportPages,
};

IMG_RESULT SYSMEMKM_AddDMABufMemory(
	SYSDEVU_sInfo *sysdev,
    SYS_eMemPool *peMemPool
)
{
    IMG_RESULT ui32Result;
    SYS_eMemPool memPool;

	ui32Result = SYSMEMU_AddMemoryHeap(&dmabuf_ops, sysdev, IMG_TRUE, IMG_NULL, &memPool);
	IMG_ASSERT(IMG_SUCCESS == ui32Result);
	if (IMG_SUCCESS != ui32Result)
	{
		return ui32Result;
	}

    *peMemPool = memPool;

    return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(SYSMEMKM_AddDMABufMemory)
