/*!
 *****************************************************************************
 *
 * @File       memmgr_km.c
 * @Title      Kernel mode memory management routines
 * @Description    Kernel mode memory management routines
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

#include "tal.h"
#include "rman_api.h"
#include "img_types.h"
#include "img_errors.h"
#include "system.h"
#include "sysmem_utils.h"
#include "talmmu_api.h"
#include "memmgr_api.h"
#include "memmgr_km.h"
#include "topazmmu.h"
#include "page_alloc_km.h"
#include "sysos_api_km.h"
#include "sysdev_utils.h"

//#define DEBUG_PA

// Debug Page Alloc leaks
#ifdef DEBUG_PA
# include <linux/kernel.h>
#endif

#define RMAN_SOCKETS_ID 0x101
#define RMAN_BUFFERS_ID 0x102

extern IMG_HANDLE g_SYSDevHandle;
extern IMG_BOOL g_bUseTiledMemory;
extern IMG_BOOL g_bUseInterleavedTiling;
extern IMG_BOOL g_bUseSecureFwUpload;
extern SYSDEVU_sInfo topaz_device;
extern IMG_HANDLE hMMUTemplate;

struct Topaz_CoreMMUContext {
	IMG_HANDLE Topaz_Core_mmu_context;
	IMG_UINT32 ptd_phys_addr;
};

extern struct Topaz_CoreMMUContext hTopaz_CoreMMUContext;
extern IMG_UINT32 g_ui32MMUTileStride;
extern TALMMU_sHeapInfo	asMMU_HeapInfo[];
extern IMG_BOOL g_bUseExtendedAddressing;
extern TALMMU_sDevMemInfo sMMU_DeviceMemoryInfo;

/* Guarantee thread-safe access to the memmgr_km */
static IMG_HANDLE g_hMemmgrMutex = NULL;


static IMG_BOOL allocateMemoryHelper(
	IMG_UINT32	ui32Size,
	IMG_UINT32	ui32Alignment,
	IMG_UINT32  ui32Heap,
	IMG_BOOL	bSaveRestore,
	MEMORY_INFO	*ppMemInfo,
	IMG_BOOL tileSensitive, SYS_eMemAttrib mem_attrib)
{
	IMG_RESULT		result;
	IMG_PHYSADDR		paAddr;

	/* If tileSensitive then change the alignment and the heapID, otherwise .. don't change the params. */
	if(tileSensitive && g_bUseTiledMemory)
	{
			ui32Alignment = 512 << asMMU_HeapInfo[0].ui32XTileStride;
			ui32Heap = 0;//MMU_TILED_HEAP_ID

			ui32Alignment <<=4;

			ui32Size = (ui32Size + ui32Alignment - 1) & ~(ui32Alignment - 1);

	}	

    /* Allocate device memory. */
    /* We always for to be at least page aligned. */
    if ( ui32Alignment >= SYS_MMU_PAGE_SIZE )
    {
        /* Alignment requirement specified by user is larger than page size - make sure alignment	*/
        /* is a multiple of page size.																*/
        IMG_ASSERT ( (ui32Alignment % SYS_MMU_PAGE_SIZE) == 0 );
    }
    else
    {
        /* Alignment requirement specified by user is smaller than page size - make sure page size	*/
        /* is a multiple of alignment.																*/
        if ( ui32Alignment != 0 )
        {
            IMG_ASSERT ( (SYS_MMU_PAGE_SIZE % ui32Alignment) == 0 );
        }

        /* Now round up alignment to one page */
        ui32Alignment = SYS_MMU_PAGE_SIZE;
    }

    /* Round size up to next multiple of physical pages */
    if (( ui32Size % SYS_MMU_PAGE_SIZE ) != 0)
    {
        ui32Size = ((ui32Size / SYS_MMU_PAGE_SIZE) + 1) * SYS_MMU_PAGE_SIZE;
	}

	SYSOSKM_LockMutex(g_hMemmgrMutex); // lock as soon as we allocate something

	result = SYSMEMU_AllocatePages(ui32Size,
    		mem_attrib,
    		topaz_device.sMemPool,
    		&ppMemInfo->sysMemHandle,
    		IMG_NULL);
	IMG_ASSERT(result == IMG_SUCCESS);

	result = SYSMEMU_GetCpuKmAddr(&(ppMemInfo->pvLinAddress), ppMemInfo->sysMemHandle);
	IMG_ASSERT(result == IMG_SUCCESS);

    /* Allocate device "virtual" memory. */
	result = TALMMU_DevMemMapExtMem1(hTopaz_CoreMMUContext.Topaz_Core_mmu_context, asMMU_HeapInfo[ui32Heap].ui32HeapId, ui32Size, ui32Alignment, ppMemInfo->pvLinAddress, ppMemInfo->sysMemHandle, &ppMemInfo->hShadowMem);
	IMG_ASSERT(result == IMG_SUCCESS && ppMemInfo->hShadowMem != NULL);

	SYSOSKM_UnlockMutex(g_hMemmgrMutex); // release after allocations

	paAddr = SYSMEMU_CpuKmAddrToCpuPAddr(topaz_device.sMemPool, (IMG_VOID*)(IMG_UINTPTR)ppMemInfo->pvLinAddress);
	ppMemInfo->ui64umTocken = paAddr;
	paAddr = SYSDEVU_CpuPAddrToDevPAddr(g_SYSDevHandle, paAddr);
	if (result != IMG_SUCCESS)
	{
		return IMG_FALSE;
	}

	ppMemInfo->ui64DevPhysAddr = paAddr;
	ppMemInfo->ui32Size = ui32Size;
	ppMemInfo->bufferId = 0;


	#ifdef DEBUG_PA
	printk(KERN_ERR"-- Alloc to %p --\n", ppMemInfo->sysMemHandle);
	dump_stack();
	printk(KERN_ERR"-- End Alloc --\n");
	#endif

	return(IMG_TRUE);
}

static IMG_BOOL freeMemoryHelper(MEMORY_INFO *pMemInfo)
{
	#ifdef DEBUG_PA
	printk(KERN_ERR"-- Free of %p --\n", pMemInfo->sysMemHandle);
	#endif

	SYSOSKM_LockMutex(g_hMemmgrMutex); // _free_Memory (callback associated with the buffer resource) comes back here, same for bridging direct call

    /* Free the memory. */
    TALMMU_DevMemFree1(pMemInfo->hShadowMem);

    if (pMemInfo->sysMemHandle != IMG_NULL)
	{
        SYSMEMU_FreePages(pMemInfo->sysMemHandle);
    }

	SYSOSKM_UnlockMutex(g_hMemmgrMutex);

	return(IMG_TRUE);
}

static IMG_BOOL allocateMemoryCommon(
	TOPAZKM_DevContext *devContext,
	IMG_UINT32	ui32Size,
	IMG_UINT32	ui32Alignment,
	IMG_UINT32  ui32Heap,
	IMG_BOOL	bSaveRestore,
	MEMORY_INFO	**ppMemInfo,
	IMG_BOOL tileSensitive,
	IMG_BOOL allocMemInfo)
{
	IMG_BOOL result;
	MEMORY_INFO *pMemoryInfo;

	if (allocMemInfo)
		pMemoryInfo = (MEMORY_INFO *)IMG_MALLOC(sizeof(MEMORY_INFO));
	else
		pMemoryInfo = *ppMemInfo;
	IMG_ASSERT(pMemoryInfo != IMG_NULL);
	if(pMemoryInfo == IMG_NULL)
		return IMG_FALSE;
	IMG_MEMSET(pMemoryInfo, 0, sizeof(*pMemoryInfo));
	result = allocateMemoryHelper(ui32Size, ui32Alignment, ui32Heap, bSaveRestore, pMemoryInfo, tileSensitive, (SYS_MEMATTRIB_UNCACHED | SYS_MEMATTRIB_WRITECOMBINE));
	IMG_ASSERT(result == IMG_TRUE);
	if(result != IMG_TRUE)
	{
		if (allocMemInfo)
			IMG_FREE(pMemoryInfo);
		return IMG_FALSE;
	}

	pMemoryInfo->hMemoryRegionID = TAL_GetMemSpaceHandle("MEMSYSMEM");

       	if (allocMemInfo)
		*ppMemInfo = pMemoryInfo;
	return IMG_TRUE;
}

IMG_BOOL allocMemory(
	TOPAZKM_DevContext *devContext,
	IMG_UINT32	ui32Size,
	IMG_UINT32	ui32Alignment,
	IMG_BOOL	bSaveRestore,
	MEMORY_INFO	**ppMemInfo)
{
	return allocateMemoryCommon(devContext, ui32Size, ui32Alignment, 1, bSaveRestore, ppMemInfo, IMG_FALSE, IMG_TRUE);
}

IMG_BOOL allocGenericMemory(
	TOPAZKM_DevContext *devContext,
	IMG_UINT32	ui32Size,
	struct MEMORY_INFO_TAG	**ppMemoryInfo,
	IMG_BOOL allocMemInfo)
{
	IMG_PVOID	pData;

	if (allocateMemoryCommon(devContext, ui32Size, 64, 1, IMG_FALSE, ppMemoryInfo, IMG_FALSE, allocMemInfo))
	{
		pData = getKMAddress(*ppMemoryInfo);
		IMG_MEMSET(pData, 0, ui32Size);
		return IMG_TRUE;
	}

	return IMG_FALSE;
}

IMG_BOOL allocNonMMUMemory(
	TOPAZKM_DevContext *devContext,
	IMG_UINT32	ui32Size,
	IMG_UINT32	ui32Alignment,
	IMG_BOOL	bSaveRestore,
	MEMORY_INFO	**ppMemInfo)
{
	IMG_UINT32 ui32Result;
	IMG_PHYSADDR paAddr;
	MEMORY_INFO	*pMemoryInfo;

	pMemoryInfo = (MEMORY_INFO*) IMG_MALLOC(sizeof(MEMORY_INFO));
	IMG_ASSERT(pMemoryInfo != IMG_NULL);
	if(pMemoryInfo == IMG_NULL)
	{
		*ppMemInfo = IMG_NULL;
		return(IMG_FALSE);
	}


	IMG_MEMSET(pMemoryInfo, 0, sizeof(*pMemoryInfo));
	ui32Result = SYSMEMU_AllocatePages(ui32Size, sMMU_DeviceMemoryInfo.eMemAttrib, sMMU_DeviceMemoryInfo.eMemPool, &pMemoryInfo->sysMemHandle, (IMG_PHYSADDR **)&(pMemoryInfo->pvLinAddress));
	IMG_ASSERT(ui32Result == IMG_SUCCESS);
	if (ui32Result != IMG_SUCCESS)
	{
		IMG_FREE(pMemoryInfo);
		*ppMemInfo = pMemoryInfo = NULL;
		return(IMG_FALSE);
	}


	paAddr = SYSMEMU_CpuKmAddrToCpuPAddr(topaz_device.sMemPool, pMemoryInfo->pvLinAddress);
	paAddr = SYSDEVU_CpuPAddrToDevPAddr(g_SYSDevHandle, paAddr);

	pMemoryInfo->ui64DevPhysAddr = paAddr;
	pMemoryInfo->hShadowMem = pMemoryInfo;
	*ppMemInfo = pMemoryInfo;
	return(IMG_TRUE);
}

IMG_BOOL freeMemory(MEMORY_INFO **ppMemoryInfo, IMG_BOOL freeMemInfo)
{
	freeMemoryHelper(*ppMemoryInfo);
	if (freeMemInfo) {
		IMG_FREE(*ppMemoryInfo);
		*ppMemoryInfo = IMG_NULL;
	}
	return(IMG_TRUE);
}

IMG_BOOL freeMemoryNonMMU(MEMORY_INFO **ppMemoryInfo)
{
	MEMORY_INFO *pMemoryInfo = *ppMemoryInfo;

		SYSMEMU_FreePages(pMemoryInfo->sysMemHandle);
	*ppMemoryInfo = IMG_NULL;
	return(IMG_TRUE);
}


IMG_PVOID getKMAddress(MEMORY_INFO *pMemoryInfo)
{
	return pMemoryInfo->pvLinAddress;
}

/*****************************************************************************
 FUNCTION	: MMWriteDeviceMemRef

 PURPOSE	: Abstracts old TAL call 'TALREG_WriteDevMemRef32' so host isn't calling TAL directly.
			  Also allows behind the scenes substitution of TAL access with TALMMU access

 PARAMETERS	:

 RETURNS	:

 Notes		:
*****************************************************************************/
IMG_VOID writeMemoryRef(
	IMG_HANDLE                      ui32MemSpaceId,
    IMG_UINT32                      ui32Offset,
    IMG_HANDLE                      hRefDeviceMem,
    IMG_UINT32                      ui32RefOffset)
{
	MEMORY_INFO *srcMem;
	IMG_UINT32 devVirtAddress;
	IMG_UINT32 ui32Result;

	srcMem = (MEMORY_INFO *)hRefDeviceMem;
	ui32Result = TALMMU_GetDevVirtAddress(srcMem->hShadowMem, &devVirtAddress);
	IMG_ASSERT(ui32Result == IMG_SUCCESS);
	TALREG_WriteWord32(ui32MemSpaceId, ui32Offset, devVirtAddress + ui32RefOffset);
}

IMG_VOID writeMemoryRefNoMMU(
	IMG_HANDLE                      ui32MemSpaceId,
    IMG_UINT32                      ui32Offset,
    IMG_HANDLE                      hRefDeviceMem,
    IMG_UINT32                      ui32RefOffset)
{
	MEMORY_INFO *mem = (MEMORY_INFO *)hRefDeviceMem;
	TALREG_WriteWord32(ui32MemSpaceId, ui32Offset, (IMG_UINT32)mem->ui64DevPhysAddr + ui32RefOffset);
}

IMG_VOID writeMemRefToMemRef(
    MEMORY_INFO                    *hDeviceMem,
    IMG_UINT32                      ui32Offset,
    IMG_UINT32                      ui32ManglerFuncIdExt,
    MEMORY_INFO                    *hRefDeviceMem,
    IMG_UINT32                      ui32RefOffset)
{
	MEMORY_INFO *memDst = hDeviceMem;
	MEMORY_INFO *memSrc = hRefDeviceMem;
	IMG_UINT32 devVirtAddress;
	IMG_RESULT ui32Result;
	ui32Result = TALMMU_GetDevVirtAddress(memSrc->hShadowMem, &devVirtAddress);
	IMG_ASSERT(ui32Result == IMG_SUCCESS);
	*(IMG_UINT32 *)(memDst->pvLinAddress + ui32Offset) = devVirtAddress + ui32RefOffset;
}

/*
 * Bridge ..
 */

/*****************************************************************************
 FUNCTION	: MMFreeDeviceMemory

 PURPOSE	: Free device memory

 PARAMETERS	:	pvMemInfo				Location of allocation handle to TRACK_FREE

 RETURNS	: IMG_TRUE - successful, IMG_FALSE - failed

 Notes		:
*****************************************************************************/
IMG_BOOL TOPAZKM_MMUMFreeDeviceMemory(SYSBRG_POINTER_ARG(MEMORY_INFO) pMemInfo)
{
	IMG_RESULT result;
	IMG_HANDLE resHandle;
	MEMORY_INFO *pMemoryInfo = (MEMORY_INFO *)IMG_MALLOC(sizeof(MEMORY_INFO));
	IMG_ASSERT(pMemoryInfo != IMG_NULL);
	if(pMemoryInfo == IMG_NULL)
	{
		return(IMG_FALSE);
	}
	
	IMG_MEMSET(pMemoryInfo, 0, sizeof(*pMemoryInfo));
	result = SYSOSKM_CopyFromUser(pMemoryInfo, pMemInfo, sizeof(MEMORY_INFO));
	IMG_ASSERT(result == IMG_SUCCESS);

	if(pMemoryInfo->bufferId)
	{
		// Stream buffer
		result = RMAN_GetResource(pMemoryInfo->bufferId, RMAN_BUFFERS_ID, IMG_NULL, &resHandle);
		IMG_ASSERT(result == IMG_SUCCESS);
		if (result != IMG_SUCCESS)
		{
			IMG_FREE(pMemoryInfo);
			return IMG_FALSE;
		}

		RMAN_FreeResource(resHandle);
	}
	else
	{
		freeMemoryHelper(pMemoryInfo);
	}

	IMG_FREE(pMemoryInfo);

	return(IMG_TRUE);
}

IMG_BOOL MMUDeviceMemoryInitialise(IMG_UINT32 ui32MmuFlags, IMG_UINT32 ui32MMUTileStride)
{
	g_bUseTiledMemory = (ui32MmuFlags & MMU_TILED_FLAG);
	g_bUseInterleavedTiling = (ui32MmuFlags & MMU_TILED_INTERLEAVED);
	g_bUseSecureFwUpload = (ui32MmuFlags & MMU_SECURE_FW_UPLOAD);

	g_bUseExtendedAddressing = (ui32MmuFlags & MMU_EXTENDED_ADDR_FLAG);

	if (SYSOSKM_CreateMutex(&g_hMemmgrMutex) != IMG_SUCCESS)
	{
		IMG_ASSERT(g_hMemmgrMutex != NULL);
		return IMG_FALSE;
	}

	//TALMMU_Initialise(); Called in the following function instead
	// Let's try configuring our MMU space here for now..
	g_ui32MMUTileStride = 512;
	while (g_ui32MMUTileStride < ui32MMUTileStride) g_ui32MMUTileStride <<= 1;

	return Topaz_Core_MMU_Configure();
}

IMG_BOOL MMUDeviceMemoryHWSetup(IMG_HANDLE ui32TCoreReg)
{
	return Topaz_Core_MMU_HWSetup(ui32TCoreReg);
}

IMG_VOID MMDeviceMemoryDeInitialise(IMG_VOID)
{
	if(hMMUTemplate)	
		TALMMU_DevMemTemplateDestroy(hMMUTemplate);

	if (g_hMemmgrMutex)
	{
		SYSOSKM_DestroyMutex(g_hMemmgrMutex);
	}
}

IMG_BOOL TOPAZKM_MMUFlushMMUTableCache()
{
	Topaz_Core_MMU_FlushCache();

	return IMG_TRUE;
}

/*****************************************************************************
 FUNCTION	: MMAllocateHeapDeviceMemory

 PURPOSE	: Allocate device memory using the TAL (from a specified heap, if using the MMU)

 PARAMETERS	:	ui32Size				Size of memory to allocate in bytes
				ui32Alignment			Alignment requirements of allocation
				ui32Heap				MMU heap from which to allocate
				bSaveRestore			Save surface on power transitions
				pvMemInfo				Location to return allocation handle

 RETURNS	: IMG_TRUE - successful, IMG_FALSE - failed

 Notes		:
*****************************************************************************/
IMG_BOOL TOPAZKM_MMUMAllocateHeapDeviceMemory(
	IMG_UINT32	ui32Size,
	IMG_UINT32	ui32Alignment,
	IMG_UINT32  ui32Heap,
	IMG_BOOL	bSaveRestore,
	SYSBRG_POINTER_ARG(MEMORY_INFO) ppMemInfo,
	IMG_BOOL tileSensitive)
{
	MEMORY_INFO		*pMemoryInfo;
	IMG_BOOL		result;
	IMG_RESULT		out;

	/* Allocate memory handle */
	pMemoryInfo = (MEMORY_INFO *)IMG_MALLOC(sizeof(MEMORY_INFO));
	IMG_ASSERT(pMemoryInfo != IMG_NULL);
	if(pMemoryInfo == IMG_NULL)
		return(IMG_FALSE);
	IMG_MEMSET(pMemoryInfo, 0, sizeof(*pMemoryInfo));

	SYSOSKM_CopyFromUser(pMemoryInfo, ppMemInfo, sizeof(MEMORY_INFO));
	result = allocateMemoryHelper(ui32Size, ui32Alignment, ui32Heap, bSaveRestore, pMemoryInfo, tileSensitive, (SYS_MEMATTRIB_UNCACHED | SYS_MEMATTRIB_WRITECOMBINE));
	IMG_ASSERT(result == IMG_TRUE);
	if(result != IMG_TRUE)
	{
		IMG_FREE(pMemoryInfo);
		return IMG_FALSE;
	}

	out = SYSOSKM_CopyToUser(ppMemInfo, pMemoryInfo, sizeof(MEMORY_INFO));
	IMG_ASSERT(out == IMG_SUCCESS);
	IMG_FREE(pMemoryInfo);

	return result;
}

IMG_VOID _free_Memory(IMG_VOID *params)
{
	MEMORY_INFO *pMemInfo = (MEMORY_INFO *)params;
	freeMemoryHelper(pMemInfo);
	IMG_FREE(pMemInfo);
}


IMG_BOOL TOPAZKM_StreamMMUMAllocateHeapDeviceMemory(
	IMG_UINT32	ui32StreamId,
	IMG_UINT32	ui32Size,
	IMG_UINT32	ui32Alignment,
	IMG_UINT32  ui32Heap,
	IMG_BOOL	bSaveRestore,
	SYSBRG_POINTER_ARG(MEMORY_INFO) ppMemInfo,
	IMG_BOOL tileSensitive)
{
	IMG_RESULT out;
	IMG_BOOL result;
	MEMORY_INFO *pMemoryInfo;
	IMG_COMM_SOCKET *pSocket;

	out = RMAN_GetResource(ui32StreamId, RMAN_SOCKETS_ID, (IMG_VOID **)&pSocket, IMG_NULL);
	IMG_ASSERT(out == IMG_SUCCESS);
	if (out != IMG_SUCCESS)
		return IMG_FALSE;

	/* Allocate memory handle */
	pMemoryInfo = (MEMORY_INFO *)IMG_MALLOC(sizeof(MEMORY_INFO));
	IMG_ASSERT(pMemoryInfo != IMG_NULL);
	if(pMemoryInfo == IMG_NULL)
		return(IMG_FALSE);
	IMG_MEMSET(pMemoryInfo, 0, sizeof(*pMemoryInfo));

	SYSOSKM_CopyFromUser(pMemoryInfo, ppMemInfo, sizeof(MEMORY_INFO));
	result = allocateMemoryHelper(ui32Size, ui32Alignment, ui32Heap, bSaveRestore, pMemoryInfo, tileSensitive, (SYS_MEMATTRIB_UNCACHED | SYS_MEMATTRIB_WRITECOMBINE));
	IMG_ASSERT(result == IMG_TRUE);
	if(result != IMG_TRUE) {
		IMG_FREE(pMemoryInfo);
		return IMG_FALSE;
	}

	out = RMAN_RegisterResource(pSocket->hResBHandle, RMAN_BUFFERS_ID, _free_Memory, (IMG_VOID *)pMemoryInfo, IMG_NULL, &pMemoryInfo->bufferId);
	IMG_ASSERT(out == IMG_SUCCESS);
	if(out != IMG_SUCCESS)
		return IMG_FALSE;

	out = SYSOSKM_CopyToUser(ppMemInfo, pMemoryInfo, sizeof(MEMORY_INFO));
	IMG_ASSERT(out == IMG_SUCCESS);

	return result;
}

/*****************************************************************************
 FUNCTION	: MMDeviceMemWriteDeviceMemRef

 PURPOSE	: Abstracts old TAL call 'TAL_DeviceMemWriteDeviceMemRefWithBitPattern' so host isn't calling TAL directly.
			  Also allows behind the scenes substitution of TAL access with TALMMU access

 PARAMETERS	:

 RETURNS	:

 Notes		:
*****************************************************************************/
IMG_VOID WriteMemRefToMemRef(
    SYSBRG_POINTER_ARG(MEMORY_INFO) hDeviceMem,
    IMG_UINT32                      ui32Offset,
    IMG_UINT32                      ui32ManglerFuncIdExt,
    SYSBRG_POINTER_ARG(MEMORY_INFO) hRefDeviceMem,
    IMG_UINT32                      ui32RefOffset)
{
	MEMORY_INFO *hDeviceMemL;
	MEMORY_INFO *hRefDeviceMemL;
	IMG_RESULT result;

	hDeviceMemL = IMG_MALLOC(sizeof(MEMORY_INFO));
	IMG_ASSERT(hDeviceMemL != IMG_NULL);
	if(hDeviceMemL == IMG_NULL)
		return;
	result = SYSOSKM_CopyFromUser(hDeviceMemL, hDeviceMem, sizeof(MEMORY_INFO));
	IMG_ASSERT(result == IMG_SUCCESS);

	hRefDeviceMemL = IMG_MALLOC(sizeof(MEMORY_INFO));
	IMG_ASSERT(hRefDeviceMemL != IMG_NULL);
	if(hRefDeviceMemL == IMG_NULL) {
		IMG_FREE(hDeviceMemL);
		return;
	}
	result = SYSOSKM_CopyFromUser(hRefDeviceMemL, hRefDeviceMem, sizeof(MEMORY_INFO));
	IMG_ASSERT(result == IMG_SUCCESS);

	writeMemRefToMemRef(hDeviceMemL, ui32Offset, ui32ManglerFuncIdExt, hRefDeviceMemL, ui32RefOffset);
	IMG_FREE(hDeviceMemL);
	IMG_FREE(hRefDeviceMemL);
}


/* Exported API through bridging */

IMG_BOOL TOPAZKM_MapExternal(
	IMG_UINT32 ui32BufLen,
	IMG_UINT32 ui32PallocId,
	IMG_UINT32 ui32Heap,
	IMG_UINT32 ui32Alignment,
	SYSBRG_POINTER_ARG(MEMORY_INFO) memInfo)
{
	IMG_RESULT		result;
	IMG_HANDLE		hTemp;
	MEMORY_INFO* pMemoryInfo;
	IMG_HANDLE hDevMemHeap;
	IMG_HANDLE pallocHandle;
	IMG_VOID *pvUM = (void*)0x42424242;

	result = PALLOCKM_GetPagesHandle(ui32PallocId, &pallocHandle);
	IMG_ASSERT(pallocHandle != IMG_NULL);
	if(pallocHandle == IMG_NULL)
		return IMG_FALSE;

	pMemoryInfo = (MEMORY_INFO *)IMG_MALLOC(sizeof(MEMORY_INFO));
	IMG_ASSERT(pMemoryInfo != IMG_NULL);
	if(pMemoryInfo == IMG_NULL)
		return IMG_FALSE;
	IMG_MEMSET(pMemoryInfo, 0, sizeof(*pMemoryInfo));

	result = TALMMU_GetHeapHandle(asMMU_HeapInfo[ui32Heap].ui32HeapId, hTopaz_CoreMMUContext.Topaz_Core_mmu_context, &hDevMemHeap);
	IMG_ASSERT(result == IMG_SUCCESS);
	if(result != IMG_SUCCESS)
		goto map_failed;

	SYSOSKM_LockMutex(g_hMemmgrMutex); // lock before call which will update
	result = TALMMU_DevMemMapExtMem(hTopaz_CoreMMUContext.Topaz_Core_mmu_context, hDevMemHeap, ui32BufLen, ui32Alignment, pvUM, pallocHandle, &hTemp);
	SYSOSKM_UnlockMutex(g_hMemmgrMutex);

	IMG_ASSERT(result == IMG_SUCCESS);
	if (result != IMG_SUCCESS)
		goto map_failed;

	pMemoryInfo->pvLinAddress = pvUM;
	pMemoryInfo->hShadowMem = hTemp;
	pMemoryInfo->ui64DevPhysAddr = 0;

	result = SYSOSKM_CopyToUser(memInfo, pMemoryInfo, sizeof(MEMORY_INFO));
	IMG_ASSERT(result == IMG_SUCCESS);

	IMG_FREE(pMemoryInfo);  // Free up the temporary memory
	return IMG_TRUE;

map_failed:
	IMG_FREE(pMemoryInfo);
	return IMG_FALSE;
}

IMG_BOOL TOPAZKM_UnMapExternal(SYSBRG_POINTER_ARG(MEMORY_INFO) memInfo)
{
	IMG_RESULT result;
	MEMORY_INFO* pMemoryInfo;

	pMemoryInfo = (MEMORY_INFO *)IMG_MALLOC(sizeof(MEMORY_INFO));
	IMG_ASSERT(pMemoryInfo != IMG_NULL);
	if(pMemoryInfo == IMG_NULL)
		return IMG_FALSE;
	IMG_MEMSET(pMemoryInfo, 0, sizeof(*pMemoryInfo));

	result = SYSOSKM_CopyFromUser(pMemoryInfo, memInfo, sizeof(MEMORY_INFO));
	IMG_ASSERT(result == IMG_SUCCESS);
	if(result != IMG_SUCCESS)
		goto umap_failed;

	SYSOSKM_LockMutex(g_hMemmgrMutex); // on TAL call
	result = TALMMU_DevMemUnmap(pMemoryInfo->hShadowMem);
	SYSOSKM_UnlockMutex(g_hMemmgrMutex);

	IMG_ASSERT(result == IMG_SUCCESS);
	if (result != IMG_SUCCESS)
		goto umap_failed;

	IMG_FREE(pMemoryInfo); // Free up the temporary memory
	return IMG_TRUE;

umap_failed:
	IMG_FREE(pMemoryInfo);
	return IMG_FALSE;
}

/*****************************************************************************
 FUNCTION	: MMCopyTiledBuffer

 PURPOSE	: Perform tile or detile operation between host view of a buffer and user mode memory

 PARAMETERS	:	pvMemInfo		Allocation handle of tiled memory
				 ui32Offset		Byte offset from shadow
				 ui32Size		Number of bytes to transfer
				 pcBuffer		User mode buffer containing untiled data
				 bToMemory		Direction of transfer (IMG_TRUE for tiling, IMG_FALSE for detiling)

 RETURNS	: IMG_TRUE - successful, IMG_FALSE - failed

 Notes		:
*****************************************************************************/
IMG_BOOL TOPAZKM_MMCopyTiledBuffer(
	SYSBRG_POINTER_ARG(MEMORY_INFO) pMemoryInfo,
	SYSBRG_POINTER_ARG(IMG_CHAR) pcBuffer,
	IMG_UINT32 ui32Size,
	IMG_UINT32 ui32Offset,
	IMG_BOOL bToMemory)
{
	IMG_RESULT result;
	struct MEMORY_INFO_TAG *memInfo;
	IMG_CHAR *buffer;


	buffer = IMG_MALLOC(ui32Size);
	if(!buffer)
		return IMG_FALSE;

	memInfo = IMG_MALLOC(sizeof(*memInfo));
	if(!memInfo)
	{
		IMG_FREE(buffer);
		return IMG_FALSE;
	}

	result = SYSOSKM_CopyFromUser(buffer, pcBuffer, ui32Size);
	IMG_ASSERT(result == IMG_SUCCESS);
	if(result != IMG_SUCCESS)
		goto fail;

	result = SYSOSKM_CopyFromUser(memInfo, pMemoryInfo, sizeof(*memInfo));
	IMG_ASSERT(result == IMG_SUCCESS);
	if(result != IMG_SUCCESS)
		goto fail;

	if(TALMMU_CopyTileBuffer(memInfo->hShadowMem, ui32Offset, ui32Size, buffer, bToMemory) != IMG_SUCCESS)
		goto fail;

	IMG_FREE(buffer);
	IMG_FREE(memInfo);
	return IMG_TRUE;

fail:
	IMG_FREE(buffer);
	IMG_FREE(memInfo);
	return IMG_FALSE;
}

