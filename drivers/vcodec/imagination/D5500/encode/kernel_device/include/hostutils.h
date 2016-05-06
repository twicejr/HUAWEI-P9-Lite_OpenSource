/*!
 *****************************************************************************
 *
 * @File       hostutils.h
 * @Title      Interface to VXE hostutils kernel functions
 * @Description    Interface to VXE hostutils kernel functions.
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

#ifndef _HOST_UTILS_
#define _HOST_UTILS_

#include "apiinternal.h"
#include "img_types.h"
#include "hostutils_api.h"

#include "topazscfwif.h" // header from FW with command IDs

#include "MTX_FwIF.h"


#define FUNC_TAL_POLL TALREG_Poll32

/*
******************************************************************************

 @Function              COMM_PrepareSocket

 @details Prepares firmware for upload.

 This function gets executed automatically by `COMM_OpenSocket`. It should only be
 called manually if there is need to preload firmware earlier than it gets uploaded.

 E.g. to be able to `COMM_GetFwConfigInt`.

 Does not change state nether of host or encoder.

 @return   Standard errorcode

******************************************************************************/
IMG_ERRORCODE
comm_PrepareFirmware(
	IMG_FW_CONTEXT *fwCtxt,
	IMG_CODEC eCodec
);

/*
******************************************************************************

 @Function              AllocateGenericDeviceMemory

 @details

 Allocate device memory with 64-byte alignment, and set all bytes to 0.

 @param		ui32Size		: Number of bytes to allocate.

 @param		ppMemoryInfo	: Pointer to memory info pointer.

******************************************************************************/
IMG_BOOL TOPAZKM_AllocateGenericDeviceMemory(
	IMG_UINT32	ui32Size,
	struct MEMORY_INFO_TAG	**ppMemoryInfo);


#endif
