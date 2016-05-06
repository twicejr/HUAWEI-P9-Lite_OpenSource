/*!
 *****************************************************************************
 *
 * @File       pman_api.h
 * @Title      The Process Manager API.
 * @Description    This file contains the header file information for the
 *  Process Manager API.
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

#if !defined (__PMAN_API_H__)
#define __PMAN_API_H__

#include <img_errors.h>
#include <img_types.h>
#include <img_defs.h>
#include <lst.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*!
******************************************************************************

 @Function				PMAN_Initialise
 
 @Description 
 
 This function is used to initialises the Process Manager component and should 
 be called at start-up.
 
 @Input		None. 

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT PMAN_Initialise(IMG_VOID);


/*!
******************************************************************************

 @Function				PMAN_Deinitialise
 
 @Description 
 
 This function is used to deinitialises the Process Manager component and 
 would normally be called at shutdown.
 
 @Input		None. 

 @Return	None.

******************************************************************************/
extern IMG_VOID PMAN_Deinitialise(IMG_VOID);


/*!
******************************************************************************

 @Function              PMAN_GetProcResBucket

 @Description

 This function is used to get the resource bucket associated with this process.
 The resource bucket is created if the process is not "know".

 @Input     hProcessId :		The process handle.

 @Output	phResBHandle :		A pointer used to return the resource bucket handle.

 @Return    IMG_RESULT :        This function returns either IMG_SUCCESS or an
                                error code.

******************************************************************************/
extern IMG_RESULT PMAN_GetProcResBucket(
    IMG_HANDLE				hProcessId,
	IMG_HANDLE *			phResBHandle
);


/*!
******************************************************************************

 @Function              PMAN_pfnProcessLostCb

 @Description

 This is the prototype for "process lost" callback functions.  This function 
 is called by the Process Manager if/when the process dies.

 @Input		pvParam :		Pointer parameter, defined when the
						    callback was registered.

 @Return	None.

******************************************************************************/
typedef IMG_VOID ( * PMAN_pfnProcessLostCb) (
    IMG_VOID *                  pvParam
);


/*!
******************************************************************************

 @Function				PMAN_RegisterProcessLostCb
 
 @Description 
 
 This function is used to register a "process lost" callback function - 
 called by the Process Manager if/when the CURRENT process dies.

 NOTE: Registering a callback implies a connecton has been made by this process
 to a device.  This connection is retained until PMAN_DevDisconnectComplete()
 is call.  Calling PMAN_RemoveProcessLostCb() removes the callback, but not the
 connection.

 @Input		pfnProcessLostCb :	A pointer to the "process lost" callback function.

 @Input		pvParam :		An IMG_VOID * value passed to the "process lost" function
							when if/when the process dies.

 @Output	phProcLostCbHandle :	A pointer used to return a handle to the callback
									this can be used with PMAN_RemoveProcessLostCb()
									to removed the callback.

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT PMAN_RegisterProcessLostCb(
	PMAN_pfnProcessLostCb			pfnProcessLostCb,
    IMG_VOID *						pvParam,
    IMG_HANDLE *					phProcLostCbHandle
);


/*!
******************************************************************************

 @Function				PMAN_RemoveProcessLostCb
 
 @Description 
 
 This function is used to removed a "process lost" callback.

 @Input		hProcLostCbHandle :		The callback handle returned by 
									PMAN_RegisterProcessLostCb().

 @Return	None.

******************************************************************************/
extern IMG_VOID PMAN_RemoveProcessLostCb(
    IMG_HANDLE				hProcLostCbHandle
);


/*!
******************************************************************************

 @Function              PMAN_DevDisconnectComplete

 @Description

 This function is used to indicate that the disconnect has completed.

 @Input     hProcessId :		The process handle.

 @Return    None.

******************************************************************************/
extern IMG_VOID PMAN_DevDisconnectComplete(
    IMG_HANDLE				hProcessId
);


#if defined(__cplusplus)
}
#endif
 
#endif /* __PMAN_API_H__	*/


