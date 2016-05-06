/*!
 *****************************************************************************
 *
 * @File       memmgr_api.h
 * @Title      Interface to TOPAZ memory manager.
 * @Description    Interface to TOPAZ memory manager.
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

#if !defined (__MEMMGR_API_H__)

#include "memmgr_common.h"

#ifdef  __RPCCODEGEN__
  #define rpc_prefix      MEMMGR
  #define rpc_filename    memmgr_api
#endif

IMG_VOID WriteMemRefToMemRef(
    SYSBRG_POINTER_ARG(MEMORY_INFO) hDeviceMem,
    IMG_UINT32                      ui32Offset,
    IMG_UINT32                      ui32ManglerFuncIdExt,
    SYSBRG_POINTER_ARG(MEMORY_INFO) hRefDeviceMem,
    IMG_UINT32                      ui32RefOffset
);

IMG_BOOL TOPAZKM_MMUMAllocateHeapDeviceMemory(
	IMG_UINT32	ui32Size,
	IMG_UINT32	ui32Alignment,
	IMG_UINT32  ui32Heap,
	IMG_BOOL	bSaveRestore,
	SYSBRG_POINTER_ARG(MEMORY_INFO) ppMemInfo,
	IMG_BOOL tileSensetive);

IMG_BOOL TOPAZKM_StreamMMUMAllocateHeapDeviceMemory(
	IMG_UINT32	ui32StreamId,
	IMG_UINT32	ui32Size,
	IMG_UINT32	ui32Alignment,
	IMG_UINT32  ui32Heap,
	IMG_BOOL	bSaveRestore,
	SYSBRG_POINTER_ARG(MEMORY_INFO) ppMemInfo,
	IMG_BOOL tileSensetive);

IMG_BOOL TOPAZKM_MMUMFreeDeviceMemory(SYSBRG_POINTER_ARG(MEMORY_INFO) pMemInfo);

IMG_BOOL TOPAZKM_MMUFlushMMUTableCache(IMG_VOID);

IMG_BOOL TOPAZKM_MapExternal(
	IMG_UINT32 ui32BufLen,
	IMG_UINT32 ui32PallocId,
	IMG_UINT32 ui32Heap,
	IMG_UINT32 ui32Alignment,
	SYSBRG_POINTER_ARG(MEMORY_INFO) memInfo);
IMG_BOOL TOPAZKM_UnMapExternal(SYSBRG_POINTER_ARG(MEMORY_INFO) memInfo);

IMG_BOOL TOPAZKM_MMCopyTiledBuffer(
	SYSBRG_POINTER_ARG(MEMORY_INFO) pMemoryInfo,
	SYSBRG_POINTER_ARG(IMG_CHAR) pcBuffer,
	IMG_UINT32 ui32Size,
	IMG_UINT32 ui32Offset,
	IMG_BOOL bToMemory);

#endif
