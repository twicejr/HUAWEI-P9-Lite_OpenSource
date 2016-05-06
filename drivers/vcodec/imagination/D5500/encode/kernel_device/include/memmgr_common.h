/*!
 *****************************************************************************
 *
 * @File       memmgr_common.h
 * @Title      Shared user/kernel memory management code
 * @Description    Shared user/kernel memory management code
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

#ifndef MEMMGR_COMMON_H_
#define MEMMGR_COMMON_H_

#include "img_types.h"
#include "img_errors.h"
#include "topaz_device.h"

/* set the default tile stride to 0=512-bytes stride */
#define DEFAULT_TILE_STRIDE     0

typedef struct MEMORY_INFO_TAG
{
	SYSBRG_HANDLE(hMemoryRegionID);
	SYSBRG_KHANDLE(hShadowMem);

	SYSBRG_UINT64	ui64umTocken;

	SYSBRG_UINT64	ui64DevPhysAddr;	/* Offset from start of Frame buffer to surface */
	SYSBRG_POINTER(IMG_VOID, pvLinAddress);		/* Linear Surface Address */
	SYSBRG_UPOINTER(IMG_VOID, pvUmAddress);

	IMG_UINT32	ui32Size;
	SYSBRG_KHANDLE(sysMemHandle);

	IMG_UINT32 bufferId;
} MEMORY_INFO;

#endif /* MEMMGR_COMMON_H_ */
