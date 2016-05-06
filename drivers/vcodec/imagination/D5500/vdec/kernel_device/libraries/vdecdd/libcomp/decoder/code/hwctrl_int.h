/*!
 *****************************************************************************
 *
 * @File       hwctrl_int.h
 * @Title      Low-level video decoder interface
 * @Description    This file contains the low-level video decoder interface.
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

#ifndef __HWCTRL_INT_H__
#define __HWCTRL_INT_H__

#include "img_defs.h"
#include "vxd_ext.h"
#include "vdecdd_int.h"
#include "msvdx_ext.h"
#include "decoder_int.h"

#ifdef __cplusplus
extern "C" {
#endif

#define VDEC_NUM_RENDEC_BUFFERS 2

/*!
******************************************************************************
 This structure contains buffers needed to create batch message.
 @brief  Buffers needed for batch message.
******************************************************************************/
typedef struct
{
    VXDIO_sDdBufInfo    * psTransactionBufInfo;
    VXDIO_sDdBufInfo    * psStartCodeBufInfo;
    VXDIO_sDdBufInfo    * psBatchMsgBufInfo;
    VXDIO_sDdBufInfo    * psPsrModInfo;
    VXDIO_sDdBufInfo    * psStrPtdBufInfo;
#ifdef VDEC_USE_PVDEC
    VXDIO_sDdBufInfo    * psPvdecFwCtx;
    IMG_UINT32            ui32CtrlAllocBytes;
    IMG_UINT32            ui32OperatingMode;
    IMG_UINT32            ui32TransactionId;
    IMG_UINT8             ui8Pipe;
    IMG_BOOL              bFirstPicOfSequence;
    IMG_BOOL              bSizeDelimitedMode;
#endif /* VDEC_USE_PVDEC */

} HWCTRL_sBatchMsgData;


/*!
******************************************************************************
 This structure contains MSVDX Message information.
 @brief  MSVDX Message Information
******************************************************************************/
typedef struct
{
    IMG_UINT8  aui8ControlFenceID[VDECFW_MSGID_CONTROL_TYPES];        /*!< FenceID of last message sent to the control message buffer.         */
    IMG_UINT8  aui8DecodeFenceID[VDECFW_MSGID_DECODE_TYPES];          /*!< FenceID of last message sent to the decode message buffer.          */
    IMG_UINT8  aui8CompletionFenceID[VDECFW_MSGID_COMPLETION_TYPES];  /*!< FenceID of last message received in the completion message buffer.  */

} HWCTRL_sMsgStatus;


/*!
******************************************************************************
 This structure contains rendec properties.
 @brief  Rendec Properties
******************************************************************************/
typedef struct
{
    IMG_BOOL    bInUse;                                        /*!< Enable/Disable use of external memory.              */
    IMG_UINT32  aui32BufferSize[VDEC_NUM_RENDEC_BUFFERS];      /*!< Size of Rendec buffer 0 in multiples of 4KB.        */
    IMG_UINT32  ui32DecodeStartSize;                           /*!< Threshold in bytes before Rendec starts processing. */

    IMG_UINT8   ui8BurstSizeWrite;                             /*!< Burst size of Rendec write: 0--2.                   */
    IMG_UINT8   ui8BurstSizeRead;                              /*!< Burst size of Rendec read: 0--3.                    */

    IMG_UINT32  aui32InitialContext[6];                        /*!< Initial context for Rendec.                         */

} HWCTRL_sRendec;


/*!
******************************************************************************

 @Function              HWCTRL_pfnReadVLR

 @Description

 This is the prototype of function for reading VLR.

 @Input    hVxd         : A handle to the video decoder context.

 @Input    ui32Offset   : Offset within VLR to read from.

 @Input    pui32        : Pointer to buffer where to put data.

 @Input    ui32Words    : Number of words to read.

 @Return   IMG_RESULT   : This function returns either IMG_SUCCESS or an error
                          code.

******************************************************************************/
typedef IMG_RESULT ( * HWCTRL_pfnReadVLR)(
    const IMG_HANDLE    hVxd,
    IMG_UINT32          ui32Offset,
    IMG_UINT32        * pui32,
    IMG_UINT32          ui32Words
);

/*!
******************************************************************************

 @Function              HWCTRL_pfnwriteVLR

 @Description

 This is the prototype of function for writing to VLR.

 @Input    hVxd         : A handle to the video decoder context.

 @Input    ui32Offset   : Offset within VLR to write to.

 @Input    pui32        : Pointer to buffer to fetch data from.

 @Input    ui32Words    : Number of words to write.

 @Return   IMG_RESULT   : This function returns either IMG_SUCCESS or an error
                          code.

******************************************************************************/
typedef IMG_RESULT ( * HWCTRL_pfnWriteVLR)(
    const IMG_HANDLE    hVxd,
    IMG_UINT32          ui32Offset,
    IMG_UINT32        * pui32,
    IMG_UINT32          ui32Words
);

/*!
******************************************************************************

 @Function              HWCTRL_pfnHandleInt

 @Description

 This is the prototype of function for writing to VLR.

 @Input    hVxd         : A handle to the video decoder context.

 @Output   psIntStatus  : Interrupt status to update.

 @Return   IMG_RESULT   : This function returns either IMG_SUCCESS or an error
                          code.

******************************************************************************/
typedef IMG_RESULT ( * HWCTRL_pfnHandleInt)(
    const IMG_HANDLE    hVxd,
    VXD_sIntStatus    * psIntStatus
);

/*!
******************************************************************************

 @Function              HWCTRL_pfnGetStatus

 @Description

 This is the prototype of function for getting the interrupts status.
 Unlike HWCTRL_pfnHandleInt, it ignores psMsgQueue and does not clear MMU
 fault status.
 @note: it's NOT atomic (manually create critical section if needed)

 @Input    hVxd         : A handle to the video decoder context.

 @Output   psIntStatus  : Interrupt status to update.

 @Return   IMG_RESULT   : This function returns either IMG_SUCCESS or an error
                          code.

******************************************************************************/
typedef IMG_RESULT ( * HWCTRL_pfnGetIntStatus)(
    const IMG_HANDLE    hVxd,
    VXD_sIntStatus    * psIntStatus
);

/*!
******************************************************************************

 @Function              HWCTRL_pfnDumpRegisters

 @Description

 This is prototype of function for reporting state of registers

 @Input    hVxd         : A handle to the video decoder context.

 @Return   IMG_RESULT   : This function returns either IMG_SUCCESS or an error
                          code.

******************************************************************************/
typedef IMG_RESULT ( * HWCTRL_pfnDumpRegisters)(
    const IMG_HANDLE  hVxd
);

/*!
******************************************************************************

 @Function              HWCTRL_pfnSendFirmwareMessage

 @Description

 This is the prototype of function for submitting message to video decoder
 firmware.

 @Input    hVxd         : A handle to the video decoder context.

 @Input    eArea        : Type of communication area to use.

 @Input    psMsgHdr     : Buffer with message to send.

 @Return   IMG_RESULT   : This function returns either IMG_SUCCESS or an error
                          code.

******************************************************************************/
typedef IMG_RESULT ( * HWCTRL_pfnSendFirmwareMessage)(
    const IMG_HANDLE    hVxd,
    VXD_eCommsArea      eArea,
    const IMG_VOID    * psMsgHdr
);

/*!
******************************************************************************

 @Function              HWCTRL_pfnGetCoreState

 @Description

 This is the prototype of function for obtaining video decoder core state.

 @Input    hVxd         : A handle to the video decoder context.

 @Output   psState      : Video decoder core state to fill.

 @Return   IMG_RESULT   : This function returns either IMG_SUCCESS or an error
                          code.

******************************************************************************/
typedef IMG_RESULT ( * HWCTRL_pfnGetCoreState)(
    const IMG_HANDLE     hVxd,
    VXDIO_sState       * psState
);

/*!
******************************************************************************

 @Function              HWCTRL_pfnFlushMmuCache

 @Description

 This is the prototype of function for flushing MMU cache of video decoder.

 @Input    hVxd         : A handle to the video decoder context.

 @Return   IMG_RESULT   : This function returns either IMG_SUCCESS or an error
                          code.

******************************************************************************/
typedef IMG_RESULT ( * HWCTRL_pfnFlushMmuCache)(
    const IMG_HANDLE  hVxd
);

/*!
******************************************************************************

 @Function              HWCTRL_pfnInitialise

 @Description

 This is the prototype of function for initialisation of video decoder context.

 @Input    hVxd         : A handle to the video decoder context.

 @Input    psInitConfig : Pointer to the structure with MMU and Rendec
                          configuration.

 @Return   IMG_RESULT   : This function returns either IMG_SUCCESS or an error
                          code.

******************************************************************************/
typedef IMG_RESULT ( * HWCTRL_pfnInitialise)(
    const IMG_HANDLE        hVxd,
    VDECFW_sCoreInitData  * psInitConfig
);

/*!
******************************************************************************

 @Function              HWCTRL_pfnDeInitialise

 @Description

 This is the prototype of function for de-initialisation of video decoder
 context.

 @Input    hVxd         : A handle to the video decoder context.

 @Return   IMG_RESULT   : This function returns either IMG_SUCCESS or an error
                          code.

******************************************************************************/
typedef IMG_RESULT ( * HWCTRL_pfnDeInitialise)(
    const IMG_HANDLE  hVxd
);

/*!
******************************************************************************

 @Function              HWCTRL_pfnDestroy

 @Description

 This is the prototype of function which destroys video decoder context.

 @Input    hVxd         : A handle to the video decoder context.

 @Return   IMG_RESULT   : This function returns either IMG_SUCCESS or an error
                          code.

******************************************************************************/
typedef IMG_RESULT ( * HWCTRL_pfnDestroy)(
    const IMG_HANDLE  hVxd
);

/*!
******************************************************************************

 @Function              HWCTRL_pfnPrepareFirmware

 @Description

 This is the prototype of function which prepares buffer with firmware for
 uploading to video decoder device.

 @Input    hVxd         : A handle to the video decoder context.

 @Input    psFw         : Structure with pointers to buffers with firmware
                          binaries.

 @Input    psPtdInfo    : Structure which contains location of page table
                          directory within video decoder memory.

 @Return   IMG_RESULT   : This function returns either IMG_SUCCESS or an error
                          code.

******************************************************************************/
typedef IMG_RESULT ( * HWCTRL_pfnPrepareFirmware)(
    const IMG_HANDLE        hVxd,
    const MSVDXIO_sFw     * psFw,
    const VXDIO_sPtdInfo  * psPtdInfo
);

/*!
******************************************************************************

 @Function              HWCTRL_pfnGetRegsOffsets

 @Description

 This is the prototype of function for getting register spaces offsets.

 @Input    hVxd           : A handle to the video decoder context.

 @Output   psRegsOffsets  : Structure with register spaces offsets.

 @Return   IMG_RESULT     : This function returns either IMG_SUCCESS or an error
                            code.

******************************************************************************/
typedef IMG_RESULT ( * HWCTRL_pfnGetRegsOffsets)(
    const IMG_HANDLE        hVxd,
    DECODER_sRegsOffsets  * psRegsOffsets
);

/*!
******************************************************************************

 @Function              HWCTRL_pfnGetInitMessage

 @Description

 This is the prototype of function which prepares initial message to video
 decoder firmware.

 @Input   hVxd               : A handle to the video decoder context.

 @Output  ppui8Msg           : Pointer to buffer with message. Buffer is
                               allocated in this function.

 @Input   psHostMsgStatus    : IDs of messages submitted to particular
                               message areas.

 @Input   psDevConfig        : Video decoder device configuration.

 @Input   psRendecBufInfo    : Buffer within video decoder memory allocated
                               for Rendec usage.

 @Input   psCoreInitData     : MMU and Rendec configuration.

 @Input   psDevPtdBufInfo    : Buffer within video decoder memory containing
                               address of device PTD.

 @Return  IMG_RESULT         : This function returns either IMG_SUCCESS or an
                               error code.

******************************************************************************/
typedef IMG_RESULT ( * HWCTRL_pfnGetInitMessage)(
    const IMG_HANDLE               hVxd,
    IMG_UINT8                   ** ppui8Msg,
    HWCTRL_sMsgStatus            * psHostMsgStatus,
    VDECDD_sDdDevConfig          * psDevConfig,
    VXDIO_sDdBufInfo             * psRendecBufInfo,
    const VDECFW_sCoreInitData   * psCoreInitData,
    const VXDIO_sDdBufInfo       * psDevPtdBufInfo
);

/*!
******************************************************************************

 @Function              HWCTRL_pfnGetDecodeMessage

 @Description

 This is the prototype of function which prepares message to video decoder
 firmware with request to decode a picture.

 @Input   hVxd               : A handle to the video decoder context.

 @Output  ppui8Msg           : Pointer to buffer with message. Buffer is
                               allocated in this function.

 @Input   psHostMsgStatus    : IDs of messages submitted to particular
                               message areas.

 @Input   psDevConfig        : Video decoder device configuration.

 @Input   psStrPtdBufInfo    : Buffer within video decoder memory containing
                               address of stream PTD.

 @Input   psPsrModInfo       : Buffer within video decoder memory with binary
                               of firmware's module.

 @Input   psTransBufInfo     : Buffer within video decoder memory with
                               transaction data.

 @Return  IMG_RESULT         : This function returns either IMG_SUCCESS or an
                               error code.

******************************************************************************/
typedef IMG_RESULT ( * HWCTRL_pfnGetDecodeMessage)(
    const IMG_HANDLE              hVxd,
    IMG_UINT8                  ** ppui8Msg,
    HWCTRL_sMsgStatus           * psHostMsgStatus,
    const VDECDD_sDdDevConfig   * psDevConfig,
    const VXDIO_sDdBufInfo      * psStrPtdBufInfo,
    const VXDIO_sDdBufInfo      * psPsrModInfo,
    const VXDIO_sDdBufInfo      * psTransBufInfo
);

/*!
******************************************************************************

 @Function              HWCTRL_pfnGetBatchMessage

 @Description

 This is the prototype of function which prepares batch message to video
 decoder firmware which contains request to decode a picture and bitstream
 buffers information.

 @Input   hVxd               : A handle to the video decoder context.

 @Output  ppui8Msg           : Pointer to buffer with message. Buffer is
                               allocated in this function.

 @Input   psHostMsgStatus    : IDs of messages submitted to particular
                               message areas.

 @Input   psDevConfig        : Video decoder device configuration.

 @Input   ui8BatchMessageID  : ID of batch message.

 @Input   psDecPictSegList   : List of picture segments.

 @Input   psBatchMsgData     : Pointer to structure containing description of
                               buffers within video decoder memory and some
                               parameters needed to create batch message.

 @Return  IMG_RESULT         : This function returns either IMG_SUCCESS or an
                               error code.

******************************************************************************/
typedef IMG_RESULT ( * HWCTRL_pfnGetBatchMessage)(
    const IMG_HANDLE              hVxd,
    IMG_UINT8                  ** ppui8Msg,
    HWCTRL_sMsgStatus           * psHostMsgStatus,
    const VDECDD_sDdDevConfig   * psDevConfig,
    const IMG_UINT8               ui8BatchMessageID,
    LST_T                       * psDecPictSegList,
    HWCTRL_sBatchMsgData        * psBatchMsgData
);

/*!
******************************************************************************

 @Function              HWCTRL_pfnGetEndBytesMessage

 @Description

 This is the prototype of function which prepares message to video decoder
 firmware with description of bitstream buffer containing last segment of
 picture.

 @Input   hVxd               : A handle to the video decoder context.

 @Output  ppui8Msg           : Pointer to buffer with message. Buffer is
                               allocated in this function.

 @Input   psHostMsgStatus    : IDs of messages submitted to particular
                               message areas.

 @Input   psEndBytesBufInfo  : Buffer within video decoder memory containing
                               last segment of picture.

 @Return  IMG_RESULT         : This function returns either IMG_SUCCESS or an
                               error code.

******************************************************************************/
typedef IMG_RESULT ( * HWCTRL_pfnGetEndBytesMessage)(
    const IMG_HANDLE       hVxd,
    IMG_UINT8           ** ppui8Msg,
    HWCTRL_sMsgStatus    * psHostMsgStatus,
    VXDIO_sDdBufInfo     * psEndBytesBufInfo
);

/*!
******************************************************************************

 @Function              HWCTRL_pfnGetFragmentMessage

 @Description

 This is the prototype of function which prepares message to video decoder
 firmware with description of bitstream segments within picture.

 @Input   hVxd               : A handle to the video decoder context.

 @Output  ppui8Msg           : Pointer to buffer with message. Buffer is
                               allocated in this function.

 @Input   psHostMsgStatus    : IDs of messages submitted to particular
                               message areas.

 @Input   psDdBufMapInfo     : Buffer with bitstream segment.

 @Input   psDecPictSeg       : Description of bitstream segment.

 @Return  IMG_RESULT         : This function returns either IMG_SUCCESS or an
                               error code.

******************************************************************************/
typedef IMG_RESULT ( * HWCTRL_pfnGetFragmentMessage)(
    const IMG_HANDLE         hVxd,
    IMG_UINT8             ** ppui8Msg,
    HWCTRL_sMsgStatus      * psHostMsgStatus,
    VDECDD_sDdBufMapInfo   * psDdBufMapInfo,
    DECODER_sDecPictSeg    * psDecPictSeg
);

/*!
******************************************************************************

 @Function              HWCTRL_pfnReturnMsg

 @Description

 This is the prototype of function which has to called once message buffer
 obtained with one of functions for getting messages.

 @Input   hVxd               : A handle to the video decoder context.

 @Input   pui8Msg            : Buffer to return.

******************************************************************************/
typedef IMG_VOID ( * HWCTRL_pfnReturnMsg)(
    const IMG_HANDLE    hVxd,
    IMG_UINT8         * pui8Msg
);

/*!
******************************************************************************

 @Function              HWCTRL_pfnProcessMessage

 @Description

 This is the prototype of function for processing messages received from
 video decoder firmware.

 @Input   hVxd               : A handle to the video decoder context.

 @Output  pui8Msg            : Pointer to buffer with message. Buffer is
                               allocated in this function.

 @Input   psHostMsgStatus    : IDs of messages submitted to particular
                               message areas.

 @Input   psPendPictList     : List of pictures pending decode.

 @Output  pbDecodedMsg       : Whether message was a decode indication.

 @Return  IMG_RESULT         : This function returns either IMG_SUCCESS or an
                               error code.

******************************************************************************/
typedef IMG_RESULT ( * HWCTRL_pfnProcessMessage)(
    const IMG_HANDLE       hVxd,
    IMG_UINT32           * pui32Msg,
    HWCTRL_sMsgStatus    * psHostMsgStatus,
    LST_T                * psPendPictList,
#ifndef IMG_KERNEL_MODULE
    IMG_BOOL               bPdumpAndRes,
#endif
    IMG_BOOL             * pbDecodedMsg
);

/*!
******************************************************************************

 @Function              HWCTRL_pfnDisableCoreInterrupts

 @Description

 This is the prototype of function for disabling video decoder core interrupts.

 @Input    hVxd         : A handle to the video decoder context.

 @Return   IMG_RESULT   : This function returns either IMG_SUCCESS or an error
                          code.

******************************************************************************/
typedef IMG_RESULT ( * HWCTRL_pfnDisableCoreInterrupts)(
    const IMG_HANDLE  hVxd
);


#ifndef IMG_KERNEL_MODULE
/*!
******************************************************************************

 @Function              HWCTRL_pfnPDULPSync

 @Description

 Sync pdump contexts

 @Input   hVxd : A handle to the video decoder context.

******************************************************************************/
typedef IMG_RESULT ( * HWCTRL_pfnPDULPSync)(
    const IMG_HANDLE  hVxd
);

/*!
******************************************************************************

 @Function              HWCTRL_pfnPDULPUnlock

 @Description

 Unlock pdump context

 @Input   hVxd : A handle to the video decoder context.

******************************************************************************/
typedef IMG_RESULT ( * HWCTRL_pfnPDULPUnlock)(
    const IMG_HANDLE  hVxd
);

/*!
******************************************************************************

 @Function              HWCTRL_pfnPDULPLock

 @Description

 Lock pdump context

 @Input   hVxd : A handle to the video decoder context.

******************************************************************************/
typedef IMG_RESULT ( * HWCTRL_pfnPDULPLock)(
    const IMG_HANDLE  hVxd
);

#endif

/*!
******************************************************************************
 This structure contains low level video decoder callbacks.

******************************************************************************/
typedef struct
{
    HWCTRL_pfnReadVLR                 pfnReadVLR;
    HWCTRL_pfnWriteVLR                pfnWriteVLR;
    HWCTRL_pfnHandleInt               pfnHandleInt;
    HWCTRL_pfnGetIntStatus            pfnGetIntStatus;
    HWCTRL_pfnDumpRegisters           pfnDumpRegisters;
    HWCTRL_pfnSendFirmwareMessage     pfnSendFirmwareMessage;
    HWCTRL_pfnGetCoreState            pfnGetCoreState;
    HWCTRL_pfnFlushMmuCache           pfnFlushMmuCache;
    HWCTRL_pfnDisableCoreInterrupts   pfnDisableCoreInterrupts;
    HWCTRL_pfnInitialise              pfnInitialise;
    HWCTRL_pfnDeInitialise            pfnDeInitialise;
    HWCTRL_pfnDestroy                 pfnDestroy;
    HWCTRL_pfnPrepareFirmware         pfnPrepareFirmware;
    HWCTRL_pfnGetRegsOffsets          pfnGetRegsOffsets;
    HWCTRL_pfnGetInitMessage          pfnGetInitMessage;
    HWCTRL_pfnGetDecodeMessage        pfnGetDecodeMessage;
    HWCTRL_pfnGetBatchMessage         pfnGetBatchMessage;
    HWCTRL_pfnGetEndBytesMessage      pfnGetEndBytesMessage;
    HWCTRL_pfnGetFragmentMessage      pfnGetFragmentMessage;
    HWCTRL_pfnReturnMsg               pfnReturnMsg;
    HWCTRL_pfnProcessMessage          pfnProcessMessage;
#ifndef IMG_KERNEL_MODULE
    HWCTRL_pfnPDULPUnlock             pfnPDUMPUnlock;
    HWCTRL_pfnPDULPLock               pfnPDUMPLock;
    HWCTRL_pfnPDULPSync               pfnPDUMPSync;
#endif

} HWCTRL_sFunctions;

#ifdef __cplusplus
}
#endif

#endif /* __HWCTRL_INT_H__   */
