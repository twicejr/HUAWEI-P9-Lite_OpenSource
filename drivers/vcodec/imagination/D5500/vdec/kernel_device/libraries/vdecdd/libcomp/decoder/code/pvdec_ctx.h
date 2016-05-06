/*!
 *****************************************************************************
 *
 * @File       pvdec_ctx.h
 * @Title      PVDEC internal core context
 * @Description    This file contains the PVDEC internal core context declaration.
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

#if !defined (__PVDECCTX_H__)
#define __PVDECCTX_H__

#if defined(__cplusplus)
extern "C" {
#endif

#include "img_defs.h"
#include "vdecdd_int.h"
#include "vxd_ext.h"
#include "hwctrl_int.h"
#include "vxd.h"
#ifdef SECURE_MEDIA_SUPPORT
#include "secureapi.h"
#include "vxd_secure_msg.h"
#endif /* SECURE_MEDIA_SUPPORT */


/*!
******************************************************************************
 This structure describes link between message id and transaction id for PVDEC.
******************************************************************************/
typedef struct
{
    LST_LINK;           /*!< List link (allows the structure to be part of a MeOS list).  */

    IMG_UINT16           ui16MsgId;
    IMG_UINT32           ui32TransId;

} PVDEC_sMsgIdTransID;


/*!
******************************************************************************
 This structure is used to retain PVDEC specific data for a particular core.
******************************************************************************/
typedef struct
{
    IMG_BOOL               bInitialised;        /*!< Whether init function was called and deinit was not.               */

#ifdef SECURE_MEDIA_SUPPORT
    IMG_HANDLE             hDev;                /*!< Handle to the secure device.                                       */
    IMG_VIDEO_CORE         eSecureCore;         /*!<                                                                    */
    VXD_sEnableClocksArgs  sEnableClocksArgs;   /*!<                                                                    */
    VXD_sSendFwMsgArgs     sFwMsgArgs;          /*!<                                                                    */
#else
    IMG_HANDLE             hVideoBus4RegSpace;
    IMG_HANDLE             hPvdecCoreRegSpace;  /*!< This is only for non-secure no bridging
                                                     systems where interrupts are polled.                               */


    IMG_HANDLE             hDev;                /* Handle to PVDECIO Context for non-secure no
                                                   bridging systems                                                     */
#endif


    VXD_sCoreProps         sProps;              /*!< MSVDX core properties.                                             */
    HWCTRL_sRendec         sRendec;             /*!<                                                                    */

    IMG_UINT32             ui32CoreNum;         /*!<                                                                    */

    IMG_BOOL               bFakeMtx;            /*!<                                                                    */
    IMG_BOOL               bCSim;               /*!<                                                                    */

    VXDIO_sPtdInfo         sPtdInfo;            /*!< Pointer to memory structure which holds
                                                     Device Page Table Directory address.                               */

    IMG_UINT32             ui32NumEntropyPipes; /*!< Number of entropy pipes, read out from H/W                         */
    IMG_UINT32             ui32NumPixelPipes;   /*!< Number of pixel pipes, read out from H/W                           */

    VDECDD_eDecodeLevel    eDecodeLevel;        /*!< Level in device to which decoding should take place.               */

    IMG_UINT16             ui16CurrentMsgId;    /*!< The last message id assigned.                                      */

    IMG_BOOL               bFWPanic;            /*!< At least one PANIC message was received from FW since last reset.  */

} PVDEC_sContext;


#if defined(__cplusplus)
}
#endif

#endif /* __PVDECCTX_H__ */



