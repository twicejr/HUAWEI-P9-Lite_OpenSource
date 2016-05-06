/*!
 *****************************************************************************
 *
 * @File       sysbrg_api_km.c
 * @Description    This file contains the System Bridge Kernel Mode API.
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

#include <img_defs.h>
#include <sysbrg_api.h>
#include <sysbrg_api_km.h>
#include <sysbrg_utils.h>
#include <sysos_api_km.h>
#include <asm/uaccess.h>

/*!
******************************************************************************

 @Function				SYSBRGKM_Initialise

******************************************************************************/
IMG_RESULT SYSBRGKM_Initialise(IMG_VOID)
{
	IMG_UINT32		ui32Result;

	/* Initialise the utilities...*/
	ui32Result = SYSBRGU_Initialise();
	IMG_ASSERT(ui32Result == IMG_SUCCESS);
	if (ui32Result != IMG_SUCCESS)
	{
		return ui32Result;
	}

	/* Return success...*/
	return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function				SYSBRGKM_Deinitialise

******************************************************************************/
IMG_VOID SYSBRGKM_Deinitialise(IMG_VOID)
{
	/* Deinitialise the utilities...*/
	SYSBRGU_Deinitialise();
}


/*!
******************************************************************************

 @Function				SYSBRGKM_RegisterProcessLostCb

******************************************************************************/
IMG_RESULT SYSBRGKM_RegisterProcessLostCb(
	SYSBRGKM_pfnProcessLostCb		pfnProcessLostCb,
    IMG_VOID *                  pvParam,
    IMG_HANDLE *				phProcLostCbHandle
)
{
	/* Return success...*/
	return SYSBRGU_RegisterProcessLostCb(pfnProcessLostCb, pvParam, phProcLostCbHandle);
}


/*!
******************************************************************************

 @Function				SYSBRGKM_RemoveProcessLostCb

******************************************************************************/
IMG_VOID SYSBRGKM_RemoveProcessLostCb(
    IMG_HANDLE				hProcLostCbHandle
)
{
	SYSBRGU_RemoveProcessLostCb(hProcLostCbHandle);
}

/*!
******************************************************************************

 @Function              SYSBRGKM_CheckParams

******************************************************************************/
IMG_RESULT SYSBRGKM_CheckParams (
    IMG_VOID __user *         pvAddress,
	IMG_UINT32                ui32Size
)
{
	IMG_RESULT ui32Result;

	/* Check the validity of the pointer.  */
	if(access_ok(VERIFY_WRITE, pvAddress, ui32Size))
		ui32Result = IMG_SUCCESS;
	else
		ui32Result = IMG_ERROR_GENERIC_FAILURE;

	return ui32Result;
}
