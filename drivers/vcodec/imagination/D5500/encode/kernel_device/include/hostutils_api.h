/*!
 *****************************************************************************
 *
 * @File       hostutils_api.h
 * @Title      Interface to VXE hostutils kernel functions.
 * @Description    Interface to VXE hostutils kernel functions.
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

#if !defined (__HOSTUTILS_API_H__)

#include "memmgr_common.h"
#include <apiinternal.h>

#ifdef  __RPCCODEGEN__
  #define rpc_prefix      HOSTUTILS
  #define rpc_filename    hostutils_api
#endif

#	define CODEC_MASK_JPEG		0x0001
#	define CODEC_MASK_MPEG2		0x0002
#	define CODEC_MASK_MPEG4		0x0004
#	define CODEC_MASK_H263		0x0008
#	define CODEC_MASK_H264		0x0010
#	define CODEC_MASK_H264MVC	0x0020
#	define CODEC_MASK_VP8		0x0040
#	define CODEC_MASK_H265		0x0080
#	define CODEC_MASK_FAKE		0x007F

/*
******************************************************************************

 @Function              COMM_Initialize

 @details

 Initialise driver and retrieve the number of pipes in the hardware

 @return   IMG_ERR_OK on success

******************************************************************************/
IMG_ERRORCODE
COMMKM_Initialize(
	IMG_UINT32 ui32ConnId,
	SYSBRG_POINTER_ARG(MEMORY_INFO) apsWBDataInfo,
	SYSBRG_POINTER_ARG(IMG_UINT32) pui32NumPipes,
	IMG_UINT32 ui32MmuFlags,
	IMG_UINT32 ui32MMUTileStride);

/*
******************************************************************************

 @Function              COMM_OpenSocket

 @details

 Create a COMM socket to use with an encode context

 @return   IMG_ERR_OK on success

******************************************************************************/
IMG_ERRORCODE
COMMKM_OpenSocket(
	IMG_UINT32			ui32ConnId,
	SYSBRG_POINTER_ARG(IMG_UINT32) ui32SockId,
	IMG_CODEC			eCodec
);

/*
******************************************************************************

 @Function              COMMKM_SetupSocket

 @details

 Configure an encode context prior to use.

 @return   IMG_ERR_OK on success

******************************************************************************/
IMG_ERRORCODE
COMMKM_SetupSocket(
	IMG_UINT32			ui32SockId,
	IMG_UINT16			ui16FrameHeight,
	IMG_UINT16			ui16Width,
	IMG_BOOL			bDoSerializedComm,
	SYSBRG_POINTER_ARG(IMG_UINT8) ui8CtxtNum,
	SYSBRG_POINTER_ARG(IMG_UINT32) usedSocket
);

/*
******************************************************************************

 @Function              COMMKM_CloseSocket

 @details

 Destroy an encode context

 @return   IMG_ERR_OK on success

******************************************************************************/
IMG_ERRORCODE
COMMKM_CloseSocket(
	IMG_UINT32			ui32SockId
);

/*
******************************************************************************

 @Function              COMMKM_Send

 @details

 Sends a command message to the encoder firmware

 @return   IMG_ERR_OK on success

******************************************************************************/
IMG_ERRORCODE
COMMKM_Send(
	IMG_UINT32	ui32SockId,
	MTX_CMD_ID	msg_eCmdId,
	IMG_UINT32	msg_ui32Data,
	SYSBRG_POINTER_ARG(MEMORY_INFO) msg_pCommandDataBuf,
	SYSBRG_POINTER_ARG(IMG_UINT32) pui32WritebackVal);

/*
******************************************************************************

 @Function              COMMKM_Recv

 @details

 Retrieves messages sent by the firmware

 @param		hSocket			: COMM socket handle

 @param		pMsg			: pointer to MTX message buffer

 @param		bBlocking		: Selects blocking behaviour if no firmware messages are available.

 @return   IMG_ERRORCODE	: IMG_ERR_OK on success

******************************************************************************/
IMG_ERRORCODE
COMMKM_Recv(
	IMG_UINT32	ui32SockId,
	SYSBRG_POINTER_ARG(IMG_WRITEBACK_MSG) pMsg,
	IMG_BOOL bBlocking);

/*
******************************************************************************

 @Function              COMMKM_LoadBias

 @details

 Configures the bias tables in the encoder hardware.

 @param		ui32SockId		: Socket ID

 @return   IMG_ERRORCODE	: IMG_ERR_OK on success

******************************************************************************/
IMG_ERRORCODE COMMKM_LoadBias(IMG_UINT32 ui32SockId);

/*
******************************************************************************

 @Function              COMM_GetFwConfigInt

 @details
	Return configuration value for given firmware

 @param		name		: configuration field name

 @return	IMG_UINT32	:	Value. "-1" if not found.

******************************************************************************/
IMG_UINT32 COMMKM_GetFwConfigInt(IMG_UINT32 ui32ConnId, SYSBRG_POINTER_ARG(IMG_CHAR) name, IMG_UINT64 szNameSize);

/*
******************************************************************************

 @Function              COMM_GetPipeUsage

 @details

 Return details regarding which context (if any) is using a given pipe

 @return    >0 = Video context Id
			0 = Not allocated to a context


******************************************************************************/
IMG_UINT8 COMM_GetPipeUsage(IMG_UINT8 ui8Pipe);

/*
******************************************************************************

 @Function              COMM_SetPipeUsage

 @details

 Associates a pipe with a given video context Id

 @return   void

******************************************************************************/
IMG_VOID COMM_SetPipeUsage(IMG_UINT8 ui8Pipe, IMG_UINT8 ui8Val);

/*
******************************************************************************

 @Function              COMM_IsIdle

 @details

 Checks if there is any pending commands waiting for an ACK from MTX

 @param		hSocket		: COMM socket handle

 @return	IMG_BOOL	:	Returns IMG_TRUE if MTX acknowledged all the commands
							for this COMM socket

******************************************************************************/
IMG_BOOL COMMKM_IsIdle(IMG_UINT32 ui32SockId);

/*
******************************************************************************

 @Function              TOPAZKM_IsIdle

 @details

 Checks if there is any outstanding work in the firmware and that all messages 
 from the firmware have been received. 

 @param		hSocket		: COMM socket handle

 @return	IMG_BOOL	:	Returns IMG_TRUE if MTX acknowledged all the commands
							for this COMM socket

******************************************************************************/
IMG_BOOL TOPAZKM_IsIdle(IMG_UINT32 ui32SockId);

/*
******************************************************************************

 @function              TOPAZ_Suspend

 @details

 Suspend the encoder and put into power saving mode.

 @param    psEncCtxt        : Pointer to Encoder Context

 @return   None

******************************************************************************/
IMG_VOID
TOPAZKM_Suspend(IMG_UINT32 ui32ConnId);

/*
******************************************************************************

 @function              TOPAZ_Resume

 @details

 Restore the TopazSC encoder and resume encoding.

 @param    psEncCtxt        : Pointer to Encoder Context

 @return   None

******************************************************************************/
IMG_VOID
TOPAZKM_Resume(IMG_UINT32 ui32ConnId);

/*
******************************************************************************

 @Function              TOPAZ_GetCoreDes1

 @details

 Get the enabled core settings flags

 @return   Enabled core settings

******************************************************************************/
IMG_UINT32
TOPAZKM_GetCoreDes1(IMG_VOID);

/*
******************************************************************************

 @Function              TOPAZ_GetCoreRev

 @details

 Get the core revision

 @return   Core revision

******************************************************************************/
IMG_UINT32
TOPAZKM_GetCoreRev(IMG_VOID);

/*
******************************************************************************

 @Function              TOPAZ_GetNumPipes

 @details

 Get the number of pipes present

 @return   Number of pipes present

******************************************************************************/
IMG_UINT32
TOPAZKM_GetNumPipes(IMG_VOID);

#endif
