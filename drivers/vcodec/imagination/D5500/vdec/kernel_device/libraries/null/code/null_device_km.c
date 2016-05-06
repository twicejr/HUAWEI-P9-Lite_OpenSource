/*!
 *****************************************************************************
 *
 * @File       null_device_km.c
 * @Description    This file contains a NULL Device Kernel Mode component.
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

#include <null_device_km.h>

/*!
******************************************************************************

 @Function              nullkm_fnDevInit

 See definition of #DMANKM_pfnDevInit.

******************************************************************************/
static IMG_RESULT nullkm_fnDevInit (
	IMG_HANDLE					hDevHandle,
	IMG_HANDLE					hInitConnHandle,
    IMG_VOID **					ppvDevInstanceData
)
{
	return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              nullkm_fnDevDeinit

 See definition of #DMANKM_pfnDevDeinit.

******************************************************************************/
static IMG_VOID nullkm_fnDevDeinit (
	IMG_HANDLE					hDevHandle,
	IMG_HANDLE					hInitConnHandle,
    IMG_VOID *					pvDevInstanceData
)
{}

/*!
******************************************************************************

 @Function              nullkm_fnDevConnect

 See definition of #DMANKM_fnDevConnect.

******************************************************************************/
static IMG_RESULT nullkm_fnDevConnect (
	IMG_HANDLE					hConnHandle,
    IMG_VOID *					pvDevInstanceData,
    IMG_VOID **					ppvDevConnectionData
)
{
	return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              nullkm_fnDevDisconnect

 See definition of #DMANKM_pfnDevDisconnect.

******************************************************************************/
static IMG_RESULT nullkm_fnDevDisconnect (
	IMG_HANDLE					hConnHandle,
    IMG_VOID *					pvDevInstanceData,
    IMG_VOID *					pvDevConnectionData,
	DMANKM_eDisconnType			eDisconnType
)
{
    IMG_UINT32                        ui32Result;

	/* Signal the disconnect has completed. */
    ui32Result = DMANKM_DevDisconnectComplete(hConnHandle);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

	return IMG_SUCCESS;
}

#if 0
/*!
******************************************************************************

 @Function              nullkm_fnDevKmHisr

******************************************************************************/
static IMG_VOID nullkm_fnDevKmHisr (
	IMG_HANDLE				hDevHandle,
    IMG_VOID *				pvDevInstanceData
)
{}


/*!
******************************************************************************

 @Function              nullkm_fnDevKmLisr

******************************************************************************/
static IMG_BOOL nullkm_fnDevKmLisr (
	IMG_HANDLE				hDevHandle,
    IMG_VOID *				pvDevInstanceData
)
{
	return IMG_FALSE;
}


/*!
******************************************************************************

 @Function              nullkm_fnDevPowerPreS5

 See definition of #DMANKM_pfnDevPowerPreS5

******************************************************************************/
static IMG_VOID nullkm_fnDevPowerPreS5(
    IMG_HANDLE                  hDevHandle,
    IMG_VOID *                  pvDevInstanceData
)
{}

/*!
******************************************************************************

 @Function              nullkm_fnDevPowerPostS0

 See definition of #DMANKM_pfnDevPowerPostS0

******************************************************************************/
static IMG_VOID nullkm_fnDevPowerPostS0(
    IMG_HANDLE                  hDevHandle,
    IMG_VOID *                  pvDevInstanceData
	)
{}
#endif

/*!
******************************************************************************

 @Function              NULLKM_fnDevRegister

 See definition of #DMANKM_pfnDevRegister.

******************************************************************************/
IMG_RESULT NULLKM_fnDevRegister (
    DMANKM_sDevRegister *		psDevRegister
)
{
	psDevRegister->ui32ConnFlags		= DMAN_CFLAG_SHARED;
	psDevRegister->ui32DevFlags			|= DMAN_DFLAG_PSEUDO_DEVICE;

	psDevRegister->pfnDevInit			= nullkm_fnDevInit;
	psDevRegister->pfnDevDeinit			= nullkm_fnDevDeinit;

	psDevRegister->pfnDevConnect		= nullkm_fnDevConnect;
	psDevRegister->pfnDevDisconnect		= nullkm_fnDevDisconnect;

//	psDevRegister->pfnDevKmHisr			= nullkm_fnDevKmHisr;
//	psDevRegister->pfnDevKmLisr			= nullkm_fnDevKmLisr;

	/* suspend/resume functions.  */
//	psDevRegister->pfnDevPowerPreS5     = nullkm_fnDevPowerPreS5;
//	psDevRegister->pfnDevPowerPostS0    = nullkm_fnDevPowerPostS0;

	/* Return success...*/
	return IMG_SUCCESS;
}

