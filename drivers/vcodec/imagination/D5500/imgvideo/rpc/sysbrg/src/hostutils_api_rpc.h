/*!
 *****************************************************************************
 *
 * @File       hostutils_api_rpc.h
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

#ifndef __HOSTUTILS_RPC_H__
#define __HOSTUTILS_RPC_H__

#include "img_defs.h"
#include "sysbrg_api.h"
#include "hostutils_api.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	COMMKM_Initialize_ID,
	COMMKM_OpenSocket_ID,
	COMMKM_SetupSocket_ID,
	COMMKM_CloseSocket_ID,
	COMMKM_Send_ID,
	COMMKM_Recv_ID,
	COMMKM_LoadBias_ID,
	COMMKM_GetFwConfigInt_ID,
	COMM_GetPipeUsage_ID,
	COMM_SetPipeUsage_ID,
	COMMKM_IsIdle_ID,
	TOPAZKM_IsIdle_ID,
	TOPAZKM_Suspend_ID,
	TOPAZKM_Resume_ID,
	TOPAZKM_GetCoreDes1_ID,
	TOPAZKM_GetCoreRev_ID,
	TOPAZKM_GetNumPipes_ID,

} HOSTUTILS_eFuncId;

typedef struct
{
	HOSTUTILS_eFuncId	eFuncId;
    union
	{
	
		struct
		{
			 IMG_UINT32 ui32ConnId;
                          		 sysbrg_user_pointer apsWBDataInfo;
                          		 sysbrg_user_pointer pui32NumPipes;
                          		 IMG_UINT32 ui32MmuFlags;
                          		 IMG_UINT32 ui32MMUTileStride;
                          
		} sCOMMKM_InitializeCmd;
	
		struct
		{
			 IMG_UINT32 ui32ConnId;
                          		 sysbrg_user_pointer ui32SockId;
                          		 IMG_CODEC eCodec;
                          
		} sCOMMKM_OpenSocketCmd;
	
		struct
		{
			 IMG_UINT32 ui32SockId;
                          		 IMG_UINT16 ui16FrameHeight;
                          		 IMG_UINT16 ui16Width;
                          		 IMG_BOOL bDoSerializedComm;
                          		 sysbrg_user_pointer ui8CtxtNum;
                          		 sysbrg_user_pointer usedSocket;
                          
		} sCOMMKM_SetupSocketCmd;
	
		struct
		{
			 IMG_UINT32 ui32SockId;
                          
		} sCOMMKM_CloseSocketCmd;
	
		struct
		{
			 IMG_UINT32 ui32SockId;
                          		 MTX_CMD_ID msg_eCmdId;
                          		 IMG_UINT32 msg_ui32Data;
                          		 sysbrg_user_pointer msg_pCommandDataBuf;
                          		 sysbrg_user_pointer pui32WritebackVal;
                          
		} sCOMMKM_SendCmd;
	
		struct
		{
			 IMG_UINT32 ui32SockId;
                          		 sysbrg_user_pointer pMsg;
                          		 IMG_BOOL bBlocking;
                          
		} sCOMMKM_RecvCmd;
	
		struct
		{
			 IMG_UINT32 ui32SockId;
                          
		} sCOMMKM_LoadBiasCmd;
	
		struct
		{
			 IMG_UINT32 ui32ConnId;
                          		 sysbrg_user_pointer name;
                          		 SYSBRG_UINT64 szNameSize;
                          
		} sCOMMKM_GetFwConfigIntCmd;
	
		struct
		{
			 IMG_UINT8 ui8Pipe;
                          
		} sCOMM_GetPipeUsageCmd;
	
		struct
		{
			 IMG_UINT8 ui8Pipe;
                          		 IMG_UINT8 ui8Val;
                          
		} sCOMM_SetPipeUsageCmd;
	
		struct
		{
			 IMG_UINT32 ui32SockId;
                          
		} sCOMMKM_IsIdleCmd;
	
		struct
		{
			 IMG_UINT32 ui32SockId;
                          
		} sTOPAZKM_IsIdleCmd;
	
		struct
		{
			 IMG_UINT32 ui32ConnId;
                          
		} sTOPAZKM_SuspendCmd;
	
		struct
		{
			 IMG_UINT32 ui32ConnId;
                          
		} sTOPAZKM_ResumeCmd;
	
	} sCmd;
} HOSTUTILS_sCmdMsg;

typedef struct
{
    union
	{
	
		struct
		{
			IMG_ERRORCODE		xCOMMKM_InitializeResp;
		} sCOMMKM_InitializeResp;
            
		struct
		{
			IMG_ERRORCODE		xCOMMKM_OpenSocketResp;
		} sCOMMKM_OpenSocketResp;
            
		struct
		{
			IMG_ERRORCODE		xCOMMKM_SetupSocketResp;
		} sCOMMKM_SetupSocketResp;
            
		struct
		{
			IMG_ERRORCODE		xCOMMKM_CloseSocketResp;
		} sCOMMKM_CloseSocketResp;
            
		struct
		{
			IMG_ERRORCODE		xCOMMKM_SendResp;
		} sCOMMKM_SendResp;
            
		struct
		{
			IMG_ERRORCODE		xCOMMKM_RecvResp;
		} sCOMMKM_RecvResp;
            
		struct
		{
			IMG_ERRORCODE		xCOMMKM_LoadBiasResp;
		} sCOMMKM_LoadBiasResp;
            
		struct
		{
			IMG_UINT32		xCOMMKM_GetFwConfigIntResp;
		} sCOMMKM_GetFwConfigIntResp;
            
		struct
		{
			IMG_UINT8		xCOMM_GetPipeUsageResp;
		} sCOMM_GetPipeUsageResp;
            
		struct
		{
			IMG_BOOL		xCOMMKM_IsIdleResp;
		} sCOMMKM_IsIdleResp;
            
		struct
		{
			IMG_BOOL		xTOPAZKM_IsIdleResp;
		} sTOPAZKM_IsIdleResp;
            
		struct
		{
			IMG_UINT32		xTOPAZKM_GetCoreDes1Resp;
		} sTOPAZKM_GetCoreDes1Resp;
            
		struct
		{
			IMG_UINT32		xTOPAZKM_GetCoreRevResp;
		} sTOPAZKM_GetCoreRevResp;
            
		struct
		{
			IMG_UINT32		xTOPAZKM_GetNumPipesResp;
		} sTOPAZKM_GetNumPipesResp;
            
	} sResp;
} HOSTUTILS_sRespMsg;



extern IMG_VOID HOSTUTILS_dispatch(SYSBRG_sPacket __user *psPacket);

#ifdef __cplusplus
}
#endif

#endif
