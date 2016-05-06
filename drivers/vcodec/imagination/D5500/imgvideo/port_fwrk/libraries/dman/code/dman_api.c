/*!
 *****************************************************************************
 *
 * @File       dman_api.c
 * @Description    This file contains the Device Manager API.
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

#include "dman_api.h"
#include "dman_api_km.h"
#include "sysdev_utils.h"
#include "system.h"

#ifdef IMG_KERNEL_MODULE
#include <linux/module.h>
#endif


/*!
******************************************************************************

 @Function				DMAN_Initialise

******************************************************************************/
IMG_RESULT DMAN_Initialise(IMG_VOID)
{
	/* Return success...*/
	return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function				DMAN_Deinitialise

******************************************************************************/
IMG_RESULT DMAN_Deinitialise(IMG_VOID)
{
	/* Return success...*/
	return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function				DMAN_OpenDevice1

******************************************************************************/
IMG_RESULT DMAN_OpenDevice1(
	SYSBRG_POINTER_ARG(IMG_CHAR) pszDevName,
	IMG_UINT32              ui32DevNameSize,
	DMAN_eOpenMode			eOpenMode,
	SYSBRG_POINTER_ARG(IMG_UINT32) pui32ConnId
)
{
	IMG_HANDLE					hDevHandle;
	IMG_UINT32					ui32Result;
	IMG_CHAR *					pszLocDevName;
	IMG_UINT32					ui32ConnId;

	/* Copy the name into kernel memory. */
	pszLocDevName = IMG_MALLOC(ui32DevNameSize+1);
	IMG_ASSERT(pszLocDevName != IMG_NULL);
	if (pszLocDevName == IMG_NULL)
	{
		return IMG_ERROR_OUT_OF_MEMORY;
	}
	ui32Result = SYSOSKM_CopyFromUser(pszLocDevName, pszDevName, (ui32DevNameSize+1));
	IMG_ASSERT(ui32Result == IMG_SUCCESS);
	if (ui32Result != IMG_SUCCESS)
	{
		IMG_FREE(pszLocDevName);
		return ui32Result;
	}

	/* Locate the device...*/
	ui32Result = DMANKM_LocateDevice(pszLocDevName, &hDevHandle);
	IMG_FREE(pszLocDevName);
	IMG_ASSERT(ui32Result == IMG_SUCCESS);
	if (ui32Result != IMG_SUCCESS)
	{
		return ui32Result;
	}

	/* Lock the device...*/
	DMANKM_LockDeviceContext(hDevHandle);

	/* Call on to the kernel function...*/
	ui32Result = DMANKM_OpenDevice(hDevHandle, eOpenMode, IMG_NULL, &ui32ConnId);

	/* Unlock the device...*/
	DMANKM_UnlockDeviceContext(hDevHandle);

	IMG_ASSERT(ui32Result == IMG_SUCCESS || ui32Result == IMG_ERROR_INTERRUPTED);
	if (ui32Result != IMG_SUCCESS && ui32Result != IMG_ERROR_INTERRUPTED)
	{
		return ui32Result;
	}

	/* Copy id to user mode. */
	if(SYSOSKM_CopyToUser(pui32ConnId, &ui32ConnId, sizeof(ui32ConnId)))
	{
		IMG_ASSERT(!"failed to copy to user");
			return IMG_ERROR_GENERIC_FAILURE;

	}

	return ui32Result;
}


/*!
******************************************************************************

 @Function				DMAN_CloseDevice

******************************************************************************/
IMG_RESULT DMAN_CloseDevice(
	IMG_UINT32 					ui32ConnId
)
{
	IMG_HANDLE					hDevHandle;
	IMG_UINT32					ui32Result;
	IMG_HANDLE 					hConnHandle;

	/* Get the connection handle from it's ID...*/
	ui32Result = DMANKM_GetConnHandleFromId(ui32ConnId, &hConnHandle);
	IMG_ASSERT(ui32Result == IMG_SUCCESS);
	if (ui32Result != IMG_SUCCESS)
	{
		return ui32Result;
	}

	/* Get the device handle...*/
	hDevHandle = DMANKM_GetDevHandleFromConn(hConnHandle);

	/* Lock the device...*/
	DMANKM_LockDeviceContext(hDevHandle);

	/* Call on to the kernel function...*/
	ui32Result = DMANKM_CloseDevice(hDevHandle, hConnHandle, DMAN_DCONN_NORMAL);
	IMG_ASSERT(ui32Result == IMG_SUCCESS || ui32Result == IMG_ERROR_INTERRUPTED);

// NOTE: We do not unlock the device as this will be done by
//	     DMANKM_DevDisconnectComplete().
//	/* Unlock the device...*/
//	DMANKM_UnlockDeviceContext(hDevHandle);

	return ui32Result;
}

/*!
******************************************************************************

 @Function				DMAN_GetDeviceId

******************************************************************************/
IMG_RESULT DMAN_GetDeviceId(
	IMG_UINT32  			ui32ConnId,
	SYSBRG_POINTER_ARG(IMG_UINT32) pui32DeviceId
)
{
	IMG_HANDLE					hDevHandle;
	IMG_UINT32					ui32Result;
	IMG_HANDLE 					hConnHandle;
	IMG_UINT32 					ui32DeviceId;

	/* Get the connection handle from it's ID...*/
	ui32Result = DMANKM_GetConnHandleFromId(ui32ConnId, &hConnHandle);
	IMG_ASSERT(ui32Result == IMG_SUCCESS);
	if (ui32Result != IMG_SUCCESS)
	{
		return ui32Result;
	}

	/* Get the device handle...*/
	hDevHandle = DMANKM_GetDevHandleFromConn(hConnHandle);

	/* Get the device id...*/
	ui32Result = DMANKM_GetDeviceId(hDevHandle, &ui32DeviceId);
	IMG_ASSERT(ui32Result == IMG_SUCCESS);
	if (ui32Result != IMG_SUCCESS)
	{
		return ui32Result;
	}

	/* Copy id to user mode. */
	ui32Result = SYSOSKM_CopyToUser(pui32DeviceId, &ui32DeviceId, sizeof(ui32DeviceId));
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

 @Function				DMAN_GetKmBuildFlags

******************************************************************************/
IMG_RESULT DMAN_GetKmBuildFlags(
	SYSBRG_POINTER_ARG(IMG_UINT32) pui32KmBuildFlags
	)
{
	IMG_UINT32 					ui32KmBuildFlags;
	IMG_UINT32					ui32Result;

	DMANKM_GetKmBuildFlags(&ui32KmBuildFlags);

	/* Copy id to use mode. */
	ui32Result = SYSOSKM_CopyToUser(pui32KmBuildFlags, &ui32KmBuildFlags, sizeof(ui32KmBuildFlags));
	IMG_ASSERT(ui32Result == IMG_SUCCESS);
	if (ui32Result != IMG_SUCCESS)
	{
		return ui32Result;
	}

	return IMG_SUCCESS;
}
