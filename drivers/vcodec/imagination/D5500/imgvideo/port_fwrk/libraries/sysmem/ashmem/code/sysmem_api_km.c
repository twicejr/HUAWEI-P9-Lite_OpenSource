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

#include "img_defs.h"
#include "report_api.h"
#include "sysmem_utils.h"

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
    IMG_VOID		*cpuUmAddr,
    IMG_BOOL		kernelMapped
)
{
	IMG_RESULT result;
	int numPages = (ui32Size + HOST_MMU_PAGE_SIZE - 1) / HOST_MMU_PAGE_SIZE;
    IMG_VOID __user *pvUmBuff = cpuUmAddr;
    IMG_ASSERT(pvUmBuff);
    psPages->pvImplData = cpuUmAddr;

    /* Assign and lock physical addresses to the user space buffer.
       The mapping of the first page in the kernel is also returned */
    result = SYSOSKM_CpuUmAddrToCpuPAddrArray(pvUmBuff, pPhyAddrs,
    		numPages, &psPages->pvCpuKmAddr);
    IMG_ASSERT(result == IMG_SUCCESS);
    if (result != IMG_SUCCESS)
    {
    	return result;
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

    numPages = (psPages->ui32Size + HOST_MMU_PAGE_SIZE - 1)/HOST_MMU_PAGE_SIZE;

    if (psPages->bImported) {
		SYSOSKM_ReleaseCpuPAddrArray(psPages->pvCpuKmAddr,
				psPages->pvImplData,
				psPages->ppaPhysAddr, numPages);

		if (IMG_NULL != psPages->ppaPhysAddr)
		{
			IMG_BIGORSMALL_FREE(numPages * sizeof(psPages->ppaPhysAddr[0]), psPages->ppaPhysAddr);
			psPages->ppaPhysAddr = IMG_NULL;
		}
    }
}

static SYSMEM_Ops ashmem_ops = {
        .FreePages = FreePages,
        .ImportPages = ImportPages,
};

IMG_RESULT SYSMEMKM_AddAshMemory(
	SYSDEVU_sInfo *sysdev,
    SYS_eMemPool *peMemPool
)
{
    IMG_RESULT ui32Result;
    SYS_eMemPool memPool;

	ui32Result = SYSMEMU_AddMemoryHeap(&ashmem_ops, sysdev, IMG_TRUE, IMG_NULL, &memPool);
	IMG_ASSERT(IMG_SUCCESS == ui32Result);
	if (IMG_SUCCESS != ui32Result)
	{
		return ui32Result;
	}

    *peMemPool = memPool;

    return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(SYSMEMKM_AddAshMemory)
