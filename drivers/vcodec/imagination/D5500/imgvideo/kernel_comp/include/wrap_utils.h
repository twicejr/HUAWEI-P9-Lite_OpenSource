/*!
 *****************************************************************************
 *
 * @File       wrap_utils.h
 * @Title      The TAL Wrapper Utilities user mode API.
 * @Description    This file contains the header file information for the
 *  TAL Wrapper Utilities - a kernel component used within the
 *  Portablity Framework.
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

#if !defined (__WRAP_UTILS_H__)
#define __WRAP_UTILS_H__

#include "img_errors.h"
#include "img_types.h"
#include "img_defs.h"
#include "api_common.h"
#include "target.h"

#if defined(__cplusplus)
extern "C" {
#endif

/* Clears '__user' in user space but make it visible for doxygen */
#if !defined(IMG_KERNEL_MODULE) && !defined(__RPCCODEGEN__)
    #define __user
#endif

#ifdef  __RPCCODEGEN__
  #define rpc_prefix      WRAPU
  #define rpc_filename    wrap_utils
#endif

/*!
******************************************************************************
 This type defines the device region(s).
******************************************************************************/
typedef enum
{
    WRAPU_REGID_REGISTERS,   //!< Device registers
    WRAPU_REGID_SLAVE_PORT,  //!< Device slave port

} WRAPU_eRegionId;


/*!
******************************************************************************

 @Function                WRAPU_Initialise

 @Description

 This function is used to initialises the wrapper utilities component
 and should be called at start-up.

 @Input     None.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS
                         or an error code.

******************************************************************************/
extern IMG_RESULT WRAPU_Initialise(IMG_VOID);


/*!
******************************************************************************

 @Function                WRAPU_Deinitialise

 @Description

 This function is used to deinitialises the wrapper utilities component
 and would normally be called at shutdown.

 @Input     None.

 @Return    None.

******************************************************************************/
extern IMG_VOID WRAPU_Deinitialise(IMG_VOID);


/*!
******************************************************************************

 @Function                WRAPU_AttachToConnection

 @Description

 This function is used to attach the rapper utilities to a device
 connection.

 @Input     ui32ConnId :    The connection Id returned by DMAN_OpenDevice()

 @Output    pui32AttachId : A pointer used to return the attachment Id.

 @Return    IMG_RESULT :    This function returns either IMG_SUCCESS
                            or an error code.

******************************************************************************/
extern IMG_RESULT WRAPU_AttachToConnection(
    IMG_UINT32          ui32ConnId,
    SYSBRG_POINTER_ARG(IMG_UINT32) pui32AttachId
);


/*!
******************************************************************************

 @Function                WRAPU_GetCpuUmAddr

 @Description

 This function is used to obtain a user mode mapping of the device registers
 etc.

 @Input     ui32AttachId :  Attachment Id returned by WRAPU_AttachToConnection().

 @Input     eRegionId :     The region of the device to be mapped.

 @Output    ppvCpuUmAddr :  A pointer user to return linear user mode CPU
                            mapping for the device region.

 @Return    IMG_RESULT :    This function returns either IMG_SUCCESS
                            or an error code.

******************************************************************************/
extern SYSBRG_DO_NOT_BRIDGE IMG_RESULT WRAPU_GetCpuUmAddr(
    IMG_UINT32         ui32AttachId,
    WRAPU_eRegionId    eRegionId,
    IMG_VOID **        ppvCpuUmAddr
);

#if !defined (DOXYGEN_WILL_SEE_THIS)

/*!
******************************************************************************

 @Function                WRAPU_GetUmMappableAddr

 @Description

 This function is used to obtain a user mode mappable address of the device registers
 etc.

 @Input     ui32AttachId :    Attachment Id returned by WRAPU_AttachToConnection().

 @Input     eRegionId :       The region of the device to be mapped.

 @Output    ppvKmAddr :       A pointer used to return the kernel mode address

 @Output    pui32RegionSize : A pointer used to return the size of the region

 @Return    IMG_VOID * :      A virtual user mode CPU  mapping for the device
                              region.  IMG_NULL if the mapping failed.

******************************************************************************/
IMG_RESULT WRAPU_GetUmMappableAddr(
    IMG_UINT32          ui32AttachId,
    WRAPU_eRegionId     eRegionId,
    SYSBRG_POINTER_ARG(IMG_UINT64)  pui64KmAddr,
    SYSBRG_POINTER_ARG(IMG_UINT32) pui32RegionSize
);

#endif


#if defined(__cplusplus)
}
#endif

#endif /* __WRAP_UTILS_H__    */

