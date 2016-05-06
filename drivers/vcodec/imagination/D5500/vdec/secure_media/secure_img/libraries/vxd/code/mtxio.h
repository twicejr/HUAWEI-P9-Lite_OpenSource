/*!
 *****************************************************************************
 *
 * @File       mtxio.h
 * @Title      Low-level MTX interface component
 * @Description    This file contains the interface to communicate with MTX firmware.  This
 *  includes sending and receiving messages and state indicators.
 *  It is a subcomponent of the Decoder block and operates on the Decoder
 *  block state.
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

#if !defined (__MTXIO_H__)
#define __MTXIO_H__

#if defined(__cplusplus)
extern "C" {
#endif

#include <img_types.h>
#include <lst.h>

#include <system.h>
#include <vdecfw.h>

#include "secure_defs.h"
#include "mtxio.h"
#include "msvdx_ext.h"
#include "vxd_ext.h"

/*!
******************************************************************************
 Size and offsets to data in message buffers
******************************************************************************/
typedef struct
{
    IMG_UINT32      ui32Size;               //!< Size of cyclic buffer (in 32-bit words)
    IMG_UINT32      ui32SizeOffset;         //!< Offset to size field
    IMG_UINT32      ui32RdIndexOffset;      //!< Offset to read index
    IMG_UINT32      ui32WrtIndexOffset;     //!< Offset to write index
    IMG_UINT32      ui32BufOffset;          //!< Offset to buffer start
    MEM_REGIONS     eMemSpace;              //!< Memory space to use for this comms area

} MTXIO_sCommsInfo;


/*!
******************************************************************************
 This structure is used to retain MTXIO specific data for a particular core
******************************************************************************/
typedef struct
{
    IMG_HANDLE          hMsvdxIoCtx;
 
    /* Description of MTX comms buffers */
    MTXIO_sCommsInfo    asComms[MTXIO_AREA_MAX];            //!< Offsets to header elements in comms areas
    
} MTXIO_sContext;


/*!
******************************************************************************

 @Function              MTXIO_InitMTXComms

 @Description

 This function should be called immediately prior to loading the MTX firmware
 It initialses VEC Local RAM and the MTX message buffers.
 
 This allows messages to be sent to the firmware before the firmware load is 
 complete.
 
 It also sets up MTXIO context required for MTX communication.
 
 This should probably be called after FakeMTX has started (if being used) and
 may be reworked/replaced by code elsewhere in the Decoder block.
 
 @Input     hMsvdxIoCtx : A handle to MSVDXIO context.

 @Input     psMtxIoCtx  : A pointer to MTXIO context.

 @Return	IMG_RESULT      : This function returns either IMG_SUCCESS or an
						      error code.

******************************************************************************/
extern IMG_RESULT 
MTXIO_InitMTXComms(
    const IMG_HANDLE    hMsvdxIoCtx,
    MTXIO_sContext    * psMtxIoCtx
);


/*!
******************************************************************************

 @Function              MTXIO_SendMTXMsg

 @Description

 This function is used to send a message to MTX.

 The message is copied to a message buffer, so (on return) the message
 structure is free for use by the calling host code.
 
 It is only valid to send messages to the #MTXIO_AREA_CONTROL or 
 #MTXIO_AREA_DECODE message buffers.
 

 @Input     psContext :     A pointer to the device context.

 @Input     eArea :         The buffer to write the message to.

 @Input     psMsgHdr :      A pointer to the message header and message to be sent

 @Return	IMG_RESULT      : This function returns either IMG_SUCCESS or an
						      error code.

******************************************************************************/
extern IMG_RESULT 
MTXIO_SendMTXMsg(
    const MTXIO_sContext  * psContext,
    VXD_eCommsArea          eArea,
    const IMG_VOID *        psMsgHdr
);


/*!
******************************************************************************

 @Function              MTXIO_ProcessMTXMsgs

 @Description

 This function is called to process messages from MTX to the host.  This would
 usually be done in an interrupt service routine.
 

 @Input     psContext       : Pointer to the MTXIO context.

 @Output    psMsgQStatus    : Pointer to message queue resources.

 @Return	IMG_RESULT      : This function returns either IMG_SUCCESS or an
						      error code.

******************************************************************************/
extern IMG_RESULT
MTXIO_ProcessMTXMsgs(
    MTXIO_sContext    * psContext,
    VXD_sMsgQueue     * psMsgQStatus
);


#if defined(__cplusplus)
}
#endif

#endif /* __MTXIO_H__ */



