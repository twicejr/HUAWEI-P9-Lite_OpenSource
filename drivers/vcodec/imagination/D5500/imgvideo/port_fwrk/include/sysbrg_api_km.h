/*!
 *****************************************************************************
 *
 * @File       sysbrg_api_km.h
 * @Title      The System Bridge kernel mode API.
 * @Description    This file contains the header file information for the
 *  System Bridge Kernel Mode API.
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

#if !defined (__SYSBRG_API_KM_H__)
#define __SYSBRG_API_KM_H__	//!< Defined to prevent file being included more than once

#include "img_defs.h"
#include "lst.h"
#include "sysbrg_api.h"
#include "system.h"

#if defined(__cplusplus)
extern "C" {
#endif

/*!
******************************************************************************

 @Function              SYSBRGKM_pfnDispatcher

 @Description

 This is the prototype for dispatcher callback functions.  This function 
 is called when an API call is make via the bridge to dispatch the the
 call to the appropriate function.

 @Input		psPacket :		A pointer to the system bridge packet structure
							#SYSBRG_sPacket for this function call.

 @Return	None.
******************************************************************************/
typedef void  (*SYSBRGKM_pfnDispatcher)(SYSBRG_sPacket __user * psPacket);

/*!
******************************************************************************
 Macro used to initialise a #SYSBRGKM_sAPIInfo structure.
******************************************************************************/
#define SYS_BRIDGE(prefix)						\
{ NULL, API_ID_##prefix, & prefix##_dispatch, },

/*!
******************************************************************************
 This structure contains information for a bridged API.

 NOTE: This structure MUST be defined in static memory as it is retained and
 used by the SYSBRG component whilst the system is active.

 NOTE: The order of the items is important - see ##SYS_BRIDGE.

 @brief		This structure contains information for a SYSBRGKM API.

******************************************************************************/
typedef struct
{
	LST_LINK;			/*!< List link (allows the structure to be part of a MeOS list).*/
	IMG_UINT32					ui32APIId;		//!< API Id number/
	SYSBRGKM_pfnDispatcher		pfnDispatcher;	//!< A pointer to the API dispatcher function/

} SYSBRGKM_sAPIInfo; 

/*!
******************************************************************************

 @Function				SYSBRGKM_Initialise
 
 @Description 
 
 This function is used to initialise the system/SoC and is called at start-up.  

 NOTE: This function will call SYSBRG_RegisterBridgedApisKM() to register the
 bridged APIs.
  
 @Input		None. 

 @Return    IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT SYSBRGKM_Initialise(IMG_VOID);


/*!
******************************************************************************

 @Function				SYSBRGKM_Deinitialise
 
 @Description 
 
 This function is used to deinitialises the system/SoC and would normally be 
 called at shutdown. 
 
 @Input		None.

 @Return	None.

******************************************************************************/
extern IMG_VOID SYSBRGKM_Deinitialise(IMG_VOID);



/*!
******************************************************************************

 @Function              SYSBRGKM_pfnProcessLostCb

 @Description

 This is the prototype for "process lost" callback functions.  This function 
 is called by the bridging code if/when the process dies.

 @Input		pvParam :		Pointer parameter, defined when the
						    callback was registered.

 @Return	None.

******************************************************************************/
typedef IMG_VOID ( * SYSBRGKM_pfnProcessLostCb) (
    IMG_VOID *                  pvParam
);


/*!
******************************************************************************

 @Function				SYSBRGKM_RegisterProcessLostCb
 
 @Description 
 
 This function is used to register a "process lost" callback function - 
 called by the bridging code if/when the CURRENT process dies.

 @Input		pfnProcessLostCb :	A pointer to the "process lost" callback function.

 @Input		pvParam :		An IMG_VOID * value passed to the "process lost" function
							when if/when the process dies.

 @Output	phProcLostCbHandle :	A pointer used to return a handle to the callback
									this can be used with SYSBRGKM_RemoveProcessLostCb()
									to removed the callback.

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT SYSBRGKM_RegisterProcessLostCb(
	SYSBRGKM_pfnProcessLostCb	pfnProcessLostCb,
    IMG_VOID *                  pvParam,
    IMG_HANDLE *				phProcLostCbHandle
);


/*!
******************************************************************************

 @Function				SYSBRGKM_RemoveProcessLostCb
 
 @Description 
 
 This function is used to removed a "process lost" callback.

 @Input		hProcLostCbHandle :		The callback handle returned by 
									SYSBRGKM_RegisterProcessLostCb().

 @Return	None.

******************************************************************************/
extern IMG_VOID SYSBRGKM_RemoveProcessLostCb(
    IMG_HANDLE				hProcLostCbHandle
);

/*!
******************************************************************************

 @Function              SYSBRGKM_CheckParams


 @Description

 This function checks the validity of the parameters passed from user space

 @Input     pvAddress :            A pointer to the user space data

 @Input     ui32Size :             Size of the user space data     
 
 @Return    IMG_RESULT :           This function returns either IMG_SUCCESS or
                                   an error code.

******************************************************************************/
extern 
IMG_RESULT SYSBRGKM_CheckParams (
    IMG_VOID __user *         pvAddress,
	IMG_UINT32                ui32Size
);

#if defined(__cplusplus)
}
#endif
 
#endif /* __SYSBRG_API_KM_H__	*/

