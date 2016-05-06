/*!
 *****************************************************************************
 *
 * @File       sysbrg_api.h
 * @Title      The System Bridge user mode API.
 * @Description    This file contains the header file information for the
 *  System Bridge User Mode API.
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

#ifndef __SYSBRG_API_H__
#define __SYSBRG_API_H__

#include "img_errors.h"
#include "img_types.h"
#include "img_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Clears '__user' in user space but make it visible for doxygen */
#if !defined(IMG_KERNEL_MODULE) && !defined(__RPCCODEGEN__)
    #define __user
#endif

/*!
******************************************************************************
 This structure used to send information from user to kernel component.

    @brief	This structure used to send information from user to kernel component.
******************************************************************************/
typedef struct
{
    IMG_UINT32          ui32APIId;			//!< The Id of the target API
    sysbrg_user_pointer	pvCmdData;			//!< A pointer to the command data (arguments)
    sysbrg_user_pointer pvRespData;			//!< A pointer to the response data

} SYSBRG_sPacket;


/*!
******************************************************************************

 @Function              SYSBRG_UserKernelExchange

 @Description

 This function is used by the user to send a packet to the kernel. The function
 blocks until the exchange is completed.

 @Input     psPacket :		A pointer to the packet structure.

 @Return    IMG_RESULT :	This function returns IMG_SUCCESS or an
							error code.

******************************************************************************/
extern
IMG_RESULT SYSBRG_UserKernelExchange (
	SYSBRG_sPacket *				psPacket
);


/*!
******************************************************************************

 @Function              SYSBRG_CreateCpuUmAddrMapping

 @Description

 This function is used by the user to create a user linear address mapping for
 a region of kernel mode addresses.

 @Input     pvCpuKmAddr :	The kernel mode address.

 @Input     ui32Size :		Size of the mapping.

 @Output     ppvCpuUmAddr :	A pointer used to return the mapped user mode address.

 @Return    IMG_RESULT :	This function returns IMG_SUCCESS or an
							error code.

******************************************************************************/
extern
IMG_RESULT SYSBRG_CreateCpuUmAddrMapping (
	IMG_UINT64				ui64CpuKmAddr,
	IMG_UINT32				ui32Size,
	IMG_VOID **				ppvCpuUmAddr
);


/*!
******************************************************************************

 @Function              SYSBRG_DestroyCpuUmAddrMapping


 @Description

 This function is used by the user to destroy a user linear address mapping.

 @Input     pvCpuUmAddr :	User address for the mapping.

 @Input     ui32Size :		Size of the mapping.
 
 @Return    IMG_RESULT :	This function returns IMG_SUCCESS or an
							error code.

******************************************************************************/
extern
IMG_RESULT SYSBRG_DestroyCpuUmAddrMapping (
	IMG_VOID *				pvCpuUmAddr,
	IMG_UINT32				ui32Size
);


#ifdef __cplusplus
}
#endif

#endif  //#ifndef __SYSBRG_API_H__
