/*!
 *****************************************************************************
 *
 * @File       vxd_ext.h
 * @Title      Low-level video decoder device interface component
 * @Description    This file contains the interface to communicate with an video
 *  decoder device core.
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

#if !defined (__VXD_EXT_H__)
#define __VXD_EXT_H__

#if defined(__cplusplus)
extern "C" {
#endif

#include "img_include.h"
#include "vdec.h"

#include "vdecfw.h"
#include "vdecfw_bin.h"

#include "mem_io.h"
#include "reg_io2.h"
#include "vxd_buf.h"

/*!
******************************************************************************
 This structure contains embedded processor runtime information.
 @brief  Embedded Processor Runtime Information
******************************************************************************/
typedef struct
{
    IMG_UINT32  ui32MTX_PC;
    IMG_UINT32  ui32MTX_PCX;
    IMG_UINT32  ui32MTX_ENABLE;
    IMG_UINT32  ui32MTX_STATUS_BITS;
    IMG_UINT32  ui32MTX_FAULT0;
    IMG_UINT32  ui32MTX_A0StP;
    IMG_UINT32  ui32MTX_A0FrP;

    IMG_UINT32  ui32DMA_SETUP[3];
    IMG_UINT32  ui32DMA_COUNT[3];
    IMG_UINT32  ui32DMA_PERIPHERAL_ADDR[3];

} VXD_sEPRuntimeStatus;

/*!
******************************************************************************
 This structure describes macroblock coordinates.
 @brief  Macroblock Coordinates
******************************************************************************/
typedef struct
{
    IMG_UINT32  ui32X;  /*!< X MB coordinate.  */
    IMG_UINT32  ui32Y;  /*!< Y MB coordinate.  */

} VXD_sMBCoords;

/*!
******************************************************************************
 This structure contains firmware and decoding pipe state information.
 @brief  Decoding Pipe State Information
******************************************************************************/
typedef struct
{
    IMG_BOOL       bPipePresent;                           /*!< IMG_TRUE if this pipe is available for processing.         */
    IMG_UINT8      ui8CurCodec;                            /*!< VDECFW_eCodecType - currently loaded codec.                */
    IMG_UINT8      ui8MasterPipeId;                        /*!< Id of pipe that's master to this pipe.                     */
    IMG_UINT32     aui32CheckPoint[VDECFW_CHECKPOINT_MAX]; /*!< Transaction id at each checkpoint.                         */
    IMG_UINT32     eFirmwareAction;                        /*!< VDECFW_eFirmwareAction (UINT32 used to guarantee size).    */
    IMG_UINT32     ui32FenceValue;                         /*!< Value in the FENCE field of the FENCEMSG.                  */
    IMG_UINT32     ui32FeSlices;                           /*!< Number of FE slices processed for the last picture in FE.  */
    IMG_UINT32     ui32BeSlices;                           /*!< Number of BE slices processed for the last picture in BE.  */
    IMG_UINT32     aui32DMACStatus[2];                     /*!< DMAC CNT on SR channels - 2 and 3.                         */
    VXD_sMBCoords  sFeMb;                                  /*!< Last processed MB in front-end hardware.                   */
    VXD_sMBCoords  sBeMb;                                  /*!< Last processed MB in back-end hardware.                    */
    IMG_UINT32     ui32IntStatus;                          /*!< Decoding pipe interrupt status.                            */
    IMG_UINT32     ui32FeIntStatus;                        /*!< Decoding pipe front-end interrupt status.                  */

} VXD_sPipeState;

/*!
******************************************************************************
 This structure contains firmware and decoder core state information.
 @brief  Firmware State Information
******************************************************************************/
typedef struct
{
    IMG_UINT8 aui8ControlFenceID[VDECFW_MSGID_CONTROL_TYPES];        /*!< FenceID of last message processed in control message buffer.     */
    IMG_UINT8 aui8DecodeFenceID[VDECFW_MSGID_DECODE_TYPES];          /*!< FenceID of last message processed in decode message buffer.      */
    IMG_UINT8 aui8CompletionFenceID[VDECFW_MSGID_COMPLETION_TYPES];  /*!< FenceID of last message processed in completion message buffer.  */

    VXD_sPipeState asPipeState[VDECFW_MAX_DP];                       /*!< Pipe state array.                                                */

    IMG_BOOL bPanic;                                                 /*!< Firmware PANIC indicator.                                        */

} VXD_sFirmwareState;

/*!
******************************************************************************
 This structure contains the video decoder device state.
 @brief  VXD core state
******************************************************************************/
typedef struct
{
    VXD_sFirmwareState     sFwState;          /*!< Firmware state.                     */
    VXD_sEPRuntimeStatus   sEPRuntimeStatus;  /*!< Embedded processor runtime status.  */

} VXDIO_sState;

/*!
******************************************************************************
 @brief  VXIO Poll function modes
******************************************************************************/
typedef enum
{
    VXDIO_POLL_EQUAL,
    VXDIO_POLL_NOT_EQUAL,
    VXDIO_POLL_MAX

} VXDIO_ePollMode;


/*!
******************************************************************************
 This structure contains device's page table directory location.
 @brief  VXD PTD location.
******************************************************************************/
typedef struct
{
#ifdef SYSBRG_BRIDGING
    IMG_UINT32  ui32PtdPhysAddr;  /*!< Page table directory's physical address                  */
#else /* not SYSBRG_BRIDGING */
    IMG_HANDLE  hPtdMemSpace;     /*!< Handle to page table directory's memory space.           */
    IMG_UINT32  ui32IntRegNum;    /*!< Internal register number used to store the PTD address.  */
#endif /* not SYSBRG_BRIDGING */
} VXDIO_sPtdInfo;


/*!
******************************************************************************
 Message between LISR and HISR
******************************************************************************/
typedef struct
{
    LST_LINK;

    IMG_UINT32  ui32MsgIndex;    /*!< Message index into aui32MsgBuffer.       */
    IMG_UINT32  ui32MsgSize;     /*!< Size of the message.                     */
    IMG_UINT32  ui32NewWriteIndex;  /*!< New write index after message processed.  */

} VXDIO_sHISRMsg;


/*!
******************************************************************************
 Queue of messages received from firmware.
******************************************************************************/
typedef struct
{
    IMG_BOOL    bEmpty;        /*!< Indicates whether all the MTX messages were processed.
                                    This should only be IMG_FALSE if there were not
                                    enough messages in sFreeMsgList list.
                                    The remaining messages can be processed when more
                                    sFreeMsgList have been made available.                                    */
    IMG_BOOL    bQueued;       /*!< Indicates whether messages have been queued in
                                    the MTXIO message buffer "sNewMsgList".                                   */

    LST_T       sFreeMsgList;  /*!< Free HISR messages of type MSVDXIO_sHISRMsg.                              */
    LST_T       sNewMsgList;   /*!< New HISR messages of type MSVDXIO_sHISRMsg.                               */

    IMG_UINT32  ui32ReadIdx;   /*!< Read index into host copy message buffer.                                 */
    IMG_UINT32  ui32WriteIdx;  /*!< Write index into host copy message buffer.                                */

    IMG_UINT32  aui32MsgBuf[MSVDX_SIZE_MSG_BUFFER]; /*!< Message buffer used for messages received from MTX.  */

} VXD_sMsgQueue;


/*!
******************************************************************************
 This structure contains video decoder device interrupt status information.
 @brief  VXD interrupt status information
******************************************************************************/
typedef struct
{
    IMG_UINT32         ui32Pending;

    // MMU fault.
    IMG_UINT32         ui32Requestor;
    IMG_UINT32         MMU_FAULT_ADDR;
    IMG_BOOL           MMU_FAULT_RNW;
    IMG_BOOL           MMU_PF_N_RW;

    // Firmware messages.
    VXD_sMsgQueue   *  psMsgQueue;

} VXD_sIntStatus;


/*!
******************************************************************************
 Comms areas
******************************************************************************/
typedef enum
{
    MTXIO_AREA_CONTROL = 0,     /*!< The control comms area     */
    MTXIO_AREA_DECODE = 1,      /*!< The decode comms area      */
    MTXIO_AREA_COMPLETION = 2,  /*!< The completion comms area  */

    MTXIO_AREA_MAX,             /*!< The end marker             */

} VXD_eCommsArea;


#if defined(__cplusplus)
}
#endif

#endif /* __VXD_EXT_H__ */

