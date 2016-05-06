/*!
 *****************************************************************************
 *
 * @File       memmgr_km.h
 * @Title      Kernel driver memory management
 * @Description    Kernel driver memory management
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

#ifndef MEMMGR_KM_H_
#define MEMMGR_KM_H_

#include "memmgr_common.h"
#include <sysmem_utils.h>

IMG_BOOL allocMemory(
	TOPAZKM_DevContext *devContext,
	IMG_UINT32	ui32Size,
	IMG_UINT32	ui32Alignment,
	IMG_BOOL	bSaveRestore,
	MEMORY_INFO	**ppMemInfo);

IMG_BOOL allocGenericMemory(
	TOPAZKM_DevContext *devContext,
	IMG_UINT32	ui32Size,
	struct MEMORY_INFO_TAG	**ppMemoryInfo,
	IMG_BOOL allocMemInfo);

IMG_BOOL allocNonMMUMemory(
	TOPAZKM_DevContext *devContext,
	IMG_UINT32	ui32Size,
	IMG_UINT32	ui32Alignment,
	IMG_BOOL	bSaveRestore,
	MEMORY_INFO	**ppMemInfo);

IMG_BOOL freeMemory(MEMORY_INFO **ppMemoryInfo, IMG_BOOL freeMemInfo);

IMG_BOOL freeMemoryNonMMU(MEMORY_INFO **ppMemoryInfo);

IMG_PVOID getKMAddress(MEMORY_INFO *pMemoryInfo);

IMG_VOID writeMemoryRef(
	IMG_HANDLE                      ui32MemSpaceId,
    IMG_UINT32                      ui32Offset,
    IMG_HANDLE                      hRefDeviceMem,
    IMG_UINT32                      ui32RefOffset);

IMG_VOID writeMemoryRefNoMMU(
	IMG_HANDLE                      ui32MemSpaceId,
    IMG_UINT32                      ui32Offset,
    IMG_HANDLE                      hRefDeviceMem,
    IMG_UINT32                      ui32RefOffset);

IMG_VOID writeMemRefToMemRef(
    MEMORY_INFO                    *hDeviceMem,
    IMG_UINT32                      ui32Offset,
    IMG_UINT32                      ui32ManglerFuncIdExt,
    MEMORY_INFO                    *hRefDeviceMem,
    IMG_UINT32                      ui32RefOffset);

#ifndef SYSBRG_NO_BRIDGING
#define updateDeviceMemory(memoryInfo)     SYSMEMU_UpdateMemory((memoryInfo)->sysMemHandle, CPU_TO_DEV)
#define updateDeviceMemoryRegion(x, y, z)  SYSMEMU_UpdateMemory((memoryInfo)->sysMemHandle, CPU_TO_DEV)
#define updateHostMemory(memoryInfo)       SYSMEMU_UpdateMemory((memoryInfo)->sysMemHandle, DEV_TO_CPU)
#define updateHostMemoryNoPdump(memoryInfo) SYSMEMU_UpdateMemory((memoryInfo)->sysMemHandle, DEV_TO_CPU)
#define updateHostMemoryRegion(x, y, z)    SYSMEMU_UpdateMemory((memoryInfo)->sysMemHandle, DEV_TO_CPU)
#define COMM_PdumpComment(text)
#define updateNonMMUDeviceMemory(memoryInfo) SYSMEMU_UpdateMemory((memoryInfo)->sysMemHandle, CPU_TO_DEV)
#else
#define updateDeviceMemory(memoryInfo)	UpdateDeviceMemory(memoryInfo)
#define updateDeviceMemoryRegion(x, y, z)	UpdateDeviceMemoryRegion(x, y, z)
#define updateHostMemory(memoryInfo)	UpdateHostMemory(memoryInfo)
#define updateHostMemoryNoPdump(memoryInfo)	UpdateHostMemoryNoPdump(memoryInfo)
#define updateHostMemoryRegion(x, y, z) UpdateHostMemoryRegion(x, y, z) 

IMG_BOOL UpdateDeviceMemory(MEMORY_INFO *pMemoryInfo);
IMG_BOOL UpdateDeviceMemoryRegion(const	struct MEMORY_INFO_TAG *const pMemoryInfo ,
								  const IMG_UINT32 ui32Offset,
								  const IMG_UINT32 ui32Size	  );
IMG_BOOL UpdateHostMemoryNoPdump(MEMORY_INFO *pMemoryInfo);
IMG_BOOL UpdateHostMemory(MEMORY_INFO *pMemoryInfo);
IMG_BOOL UpdateHostMemoryRegion(const	struct MEMORY_INFO_TAG *const pMemoryInfo ,
								  const IMG_UINT32 ui32Offset,
								  const IMG_UINT32 ui32Size	  );

IMG_VOID COMM_PdumpComment(IMG_CHAR * pszCommentText);
IMG_BOOL updateNonMMUDeviceMemory(MEMORY_INFO *pMemoryInfo);
#endif


IMG_BOOL MMUDeviceMemoryInitialise(IMG_UINT32 ui32MmuFlags, IMG_UINT32 ui32MMUTileStride);

IMG_BOOL MMUDeviceMemoryHWSetup(IMG_HANDLE ui32TCoreReg);

IMG_VOID MMDeviceMemoryDeInitialise(IMG_VOID);


IMG_BOOL TOPAZKM_MMUFlushMMUTableCache(IMG_VOID);

#endif /* MEMMGR_NEW_H_ */



