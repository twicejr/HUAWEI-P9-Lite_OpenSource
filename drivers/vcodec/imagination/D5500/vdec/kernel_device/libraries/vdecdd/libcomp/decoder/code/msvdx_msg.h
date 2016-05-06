/*!
 *****************************************************************************
 *
 * @File       msvdx_msg.h
 * @Title      Messages to MSVDX firmware.
 * @Description    This file contains functions for creating messages to MSVDX firmware.
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

#ifndef __MSVDX_MSG_H__
#define __MSVDX_MSG_H__

#include <img_defs.h>
#include "vdecdd_int.h"
#include "decoder_int.h"
#include "vxd.h"
#include "msvdx_int.h"
#include "hwctrl_api.h"

#ifdef __cplusplus
extern "C" {
#endif

//Size of buffer used for batching messages
#define BATCH_MSG_BUFFER_SIZE   4096

/*!
******************************************************************************

 @Function              MSVDX_GetInitMessage

 @Description

 Prepares init message for MSVDX firmware.


 @Return   IMG_RESULT      : This function returns either IMG_SUCCESS or an
                             error code.

******************************************************************************/
extern IMG_RESULT
MSVDX_GetInitMessage(
    IMG_HANDLE                     hVxd,
    IMG_UINT8                   ** ppui8Msg,
    HWCTRL_sMsgStatus            * psHostMsgStatus,
    VDECDD_sDdDevConfig          * psDevConfig,
    VXDIO_sDdBufInfo             * psRendecBufInfo,
    const VDECFW_sCoreInitData   * psCoreInitData,
    const VXDIO_sDdBufInfo       * psDevPtdBufInfo
);

/*!
******************************************************************************

 @Function              MSVDX_GetDecodeMessage

 @Description

 Prepares decode message for MSVDX firmware.


 @Return   IMG_RESULT      : This function returns either IMG_SUCCESS or an
                             error code.

******************************************************************************/
extern IMG_RESULT
MSVDX_GetDecodeMessage(
    IMG_HANDLE                    hVxd,
    IMG_UINT8                  ** ppui8Msg,
    HWCTRL_sMsgStatus           * psHostMsgStatus,
    const VDECDD_sDdDevConfig   * psDevConfig,
    const VXDIO_sDdBufInfo      * psStrPtdBufInfo,
    const VXDIO_sDdBufInfo      * psPsrModInfo,
    const VXDIO_sDdBufInfo      * psTransactionBufInfo
);

/*!
******************************************************************************

 @Function              MSVDX_GetBatchMessage

 @Description

 Prepares batch message for MSVDX firmware.


 @Return   IMG_RESULT      : This function returns either IMG_SUCCESS or an
                             error code.

******************************************************************************/
extern IMG_RESULT
MSVDX_GetBatchMessage(
    IMG_HANDLE                    hVxd,
    IMG_UINT8                  ** ppui8Msg,
    HWCTRL_sMsgStatus           * psHostMsgStatus,
    const VDECDD_sDdDevConfig   * psDevConfig,
    const IMG_UINT8               ui8BatchMessageID,
    LST_T                       * psDecPictSegList,
    HWCTRL_sBatchMsgData        * psBatchMsgData
);


/*!
******************************************************************************

 @Function              MSVDX_GetFragmentMessage

 @Description

 Prepares fragment message for MSVDX firmware.

 @Return   IMG_RESULT      : This function returns either IMG_SUCCESS or an
                             error code.

******************************************************************************/
extern IMG_RESULT
MSVDX_GetFragmentMessage(
    IMG_HANDLE               hVxd,
    IMG_UINT8             ** ppui8Msg,
    HWCTRL_sMsgStatus      * psHostMsgStatus,
    VDECDD_sDdBufMapInfo   * psDdBufMapInfo,
    DECODER_sDecPictSeg    * psDecPictSeg
);


/*!
******************************************************************************

 @Function              MSVDX_GetEndBytesMessage

 @Description

 Prepares end bytes message for MSVDX firmware.

 @Return   IMG_RESULT      : This function returns either IMG_SUCCESS or an
                             error code.


******************************************************************************/
extern IMG_RESULT
MSVDX_GetEndBytesMessage(
    IMG_HANDLE             hVxd,
    IMG_UINT8           ** ppui8Msg,
    HWCTRL_sMsgStatus    * psHostMsgStatus,
    VXDIO_sDdBufInfo     * psEndBytesBufInfo
);

/*!
******************************************************************************

 @Function              MSVDX_ReturnMsg

 @Description

 This functions should be called once buffer returned by one of functions
 for getting messages is no longer needed.

 @Input       pui8Msg      : Buffer to return.


******************************************************************************/
extern IMG_VOID
MSVDX_ReturnMsg(
    IMG_HANDLE    hVxd,
    IMG_UINT8   * pui8Msg
);

/*!
******************************************************************************

 @Function              MSVDX_ProcessMessage

 @Description

 Processes message from MSVDX firmware .Updates status of picture in
 pending pictures list and status of messages queues.

 @Input     psHostMsgStatus : Pointer to MSVDX message status.

 @Input     pui32Msg        : Pointer to the message.

 @Input     psPendPictList  : Pointer to the pictures pending list.

 @Input     bPdumpAndRes    : Indicates that we are pdumping and res files
                              will be generated. This will force the driver
                              to update do the shadow memory copies at this point
                              so they are in sync with the messages received
                              from the firmware.

 @Output    pbDecodedMsg    : Pointer to boolean to return whether messages
                              was decoded message.

 @Return    IMG_RESULT      : This function returns either IMG_SUCCESS or an
                              error code.

******************************************************************************/
extern IMG_RESULT
MSVDX_ProcessMessage(
    IMG_HANDLE           hVxd,
    IMG_UINT32         * pui32Msg,
    HWCTRL_sMsgStatus  * psHostMsgStatus,
    LST_T              * psPendPictList,
#ifndef IMG_KERNEL_MODULE
    IMG_BOOL             bPdumpAndRes,
#endif
    IMG_BOOL           * pbDecodedMsg
);


#ifdef __cplusplus
}
#endif

#endif /* __MSVDX_MSG_H__   */
