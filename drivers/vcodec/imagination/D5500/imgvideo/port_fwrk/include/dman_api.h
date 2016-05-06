/*!
 *****************************************************************************
 *
 * @File       dman_api.h
 * @Title      The Device Manager user mode API.
 * @Description    This file contains the header file information for the
 *  Device Manager API.
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

#if !defined (__DMAN_API_H__)
#define __DMAN_API_H__

#include <img_errors.h>
#include <img_defs.h>
#include <img_types.h>

#if defined(__cplusplus)
extern "C" {
#endif

#ifdef  __RPCCODEGEN__
  #define rpc_prefix      DMAN
  #define rpc_filename    dman_api
#endif

/* Clears '__user' in user space but make it visible for doxygen */
#if !defined(IMG_KERNEL_MODULE) && !defined(__RPCCODEGEN__)
    #define __user
#endif

/*!
******************************************************************************
 This type defines the open mode flags.

 NOTE: Some flags can be used in combination with others.
******************************************************************************/
typedef enum
{
    DMAN_OMODE_EXCLUSIVE = 0x00000001,  //!< Set to obtain exclusive use of the device (exclusive to the application/process).
    DMAN_OMODE_SHARED	 = 0x00000002,  //!< Set to allow shared use of the device (exclusive to the application/process).

} DMAN_eOpenMode;

/*!
******************************************************************************

 @Function				DMAN_Initialise
 
 @Description 
 
 This function is used to initialises the Device Manager component and should 
 be called at start-up.
 
 @Input		None. 

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT DMAN_Initialise(IMG_VOID);


/*!
******************************************************************************

 @Function				DMAN_Deinitialise
 
 @Description 
 
 This function is used to deinitialises the Device Manager component and 
 would normally be called at shutdown.
 
 @Input		None. 

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT DMAN_Deinitialise(IMG_VOID);


/*!
******************************************************************************

 @Function				DMAN_OpenDevice
 
 @Description 
 
 This function is used to open a device and connect to it.  The connection
 id returned is used in may of the subsequent calls to the device or
 device related functions.
 
 @Input		pszDevName :	A pointer to the device name.

 @Input		eOpenMode :		Mode in which the device is to be opened.	

 @Output	pui32ConnId :	Pointer used to return the connection Id.

 @Return    IMG_RESULT :    This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern SYSBRG_DO_NOT_BRIDGE IMG_RESULT DMAN_OpenDevice(
	IMG_CHAR *				pszDevName,
	DMAN_eOpenMode			eOpenMode,
	IMG_UINT32 *			pui32ConnId
);


/*!
******************************************************************************

 @Function				DMAN_CloseDevice
 
 @Description 
 
 This function is used to close a device connection.

 @Input		ui32ConnId :	The connection Id returned by DMAN_OpenDevice().

 @Return    IMG_RESULT :    This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT DMAN_CloseDevice(
	IMG_UINT32  			ui32ConnId
);


/*!
******************************************************************************

 @Function				DMAN_GetDeviceId
 
 @Description 
 
 This function is used to obtain a the device ID - a id unique to this device.
 
 @Input		ui32ConnId :	The connection Id returned by DMAN_OpenDevice().
 
 @Output	pui32DeviceId :	A pointer used to return the device Id.
 
 @Return	IMG_RESULT:		This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT DMAN_GetDeviceId(
	IMG_UINT32  			ui32ConnId,
	SYSBRG_POINTER_ARG(IMG_UINT32)  pui32DeviceId
);

/*!
******************************************************************************

 @Function				DMAN_GetKmBuildFlags
 
 @Description

 This function is used to obtain kernel mode build flags

 @Output     pui32KmBuildFlags : Pointer to kernel mode build flags

 @Return     IMG_RESULT :   This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT DMAN_GetKmBuildFlags(
	SYSBRG_POINTER_ARG(IMG_UINT32) pui32KmBuildFlags
);

#if !defined (DOXYGEN_WILL_SEE_THIS)

/*!
******************************************************************************

 @Function				DMAN_OpenDevice1
 
 @Description 
 
 This function is used to open a device and connect to it.  The connection
 id returned is used in may of the subsequent calls to the device or
 device related functions.
 
 @Input		pszDevName :	A pointer to the device name.

 @Input		ui32DevNameSize :	The size of the device name.

 @Input		eOpenMode :		Mode in which the device is to be opened.	

 @Output	pui32ConnId :	Pointer used to return the connection Id.

 @Return    IMG_RESULT :    This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT DMAN_OpenDevice1(
	SYSBRG_POINTER_ARG(IMG_CHAR)       pszDevName,
	IMG_UINT32                              ui32DevNameSize,
	DMAN_eOpenMode		                 	eOpenMode,
	SYSBRG_POINTER_ARG(IMG_UINT32)  pui32ConnId
);
#endif

#if defined (__cplusplus)
}
#endif
 
#endif /* __DMAN_API_H__	*/


