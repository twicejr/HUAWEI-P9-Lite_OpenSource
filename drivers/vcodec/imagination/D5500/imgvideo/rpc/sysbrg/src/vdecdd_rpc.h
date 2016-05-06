/*!
 *****************************************************************************
 *
 * @File       vdecdd_rpc.h
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

#ifndef __VDECDD_RPC_H__
#define __VDECDD_RPC_H__

#include "img_defs.h"
#include "sysbrg_api.h"
#include "vdecdd.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	VDECDD_IsSupportedFeature_ID,
	VDECDD_SupportedFeatures_ID,
	VDECDD_StreamCreate_ID,
	VDECDD_StreamDestroy_ID,
	VDECDD_GetCallbackEvent_ID,
	VDECDD_PreemptCallbackEvent_ID,
	VDECDD_StreamPlay_ID,
	VDECDD_StreamStop_ID,
	VDECDD_StreamGetStopInfo_ID,
	VDECDD_StreamGetSequHdrInfo_ID,
	VDECDD_StreamMapBuf_ID,
	VDECDD_StreamUnmapBuf_ID,
	VDECDD_StreamSetOutputConfig_ID,
	VDECDD_StreamFillPictBuf_ID,
	VDECDD_StreamFlush_ID,
	VDECDD_StreamReleaseBufs_ID,
	VDECDD_StreamSetBehaviourOnErrors_ID,
	VDECDD_StreamGetStatus_ID,
	VDECDD_StreamSubmitUnit_ID,

} VDECDD_eFuncId;

typedef struct
{
	VDECDD_eFuncId	eFuncId;
    union
	{
	
		struct
		{
			 IMG_UINT32 ui32ConnId;
                          		 VDEC_eFeature eFeature;
                          		 sysbrg_user_pointer pbSupported;
                          
		} sVDECDD_IsSupportedFeatureCmd;
	
		struct
		{
			 IMG_UINT32 ui32ConnId;
                          		 sysbrg_user_pointer psFeature;
                          
		} sVDECDD_SupportedFeaturesCmd;
	
		struct
		{
			 sysbrg_user_pointer psStrConfigData;
                          		 sysbrg_user_pointer pvStrCbParam;
                          		 sysbrg_user_pointer pui32StrId;
                          
		} sVDECDD_StreamCreateCmd;
	
		struct
		{
			 IMG_UINT32 ui32StrId;
                          
		} sVDECDD_StreamDestroyCmd;
	
		struct
		{
			 IMG_UINT32 ui32StrId;
                          		 sysbrg_user_pointer psCallBackInfo;
                          
		} sVDECDD_GetCallbackEventCmd;
	
		struct
		{
			 IMG_UINT32 ui32StrId;
                          
		} sVDECDD_PreemptCallbackEventCmd;
	
		struct
		{
			 IMG_UINT32 ui32StrId;
                          		 VDEC_ePlayMode ePlayMode;
                          		 VDEC_eStopPoint eStopPoint;
                          		 IMG_UINT32 ui32StopPointQual;
                          
		} sVDECDD_StreamPlayCmd;
	
		struct
		{
			 IMG_UINT32 ui32StrId;
                          		 VDEC_eStopPoint eStopPoint;
                          		 IMG_UINT32 ui32StopPointQual;
                          
		} sVDECDD_StreamStopCmd;
	
		struct
		{
			 IMG_UINT32 ui32StrId;
                          		 sysbrg_user_pointer psStopInfo;
                          
		} sVDECDD_StreamGetStopInfoCmd;
	
		struct
		{
			 IMG_UINT32 ui32StrId;
                          		 sysbrg_user_pointer psComSequHdrInfo;
                          
		} sVDECDD_StreamGetSequHdrInfoCmd;
	
		struct
		{
			 IMG_UINT32 ui32StrId;
                          		 sysbrg_user_pointer pvBufCbParam;
                          		 VDEC_eBufType eBufType;
                          		 sysbrg_user_pointer psBufInfo;
                          		 sysbrg_user_pointer pui32BufMapId;
                          
		} sVDECDD_StreamMapBufCmd;
	
		struct
		{
			 IMG_UINT32 ui32BufMapId;
                          
		} sVDECDD_StreamUnmapBufCmd;
	
		struct
		{
			 IMG_UINT32 ui32StrId;
                          		 sysbrg_user_pointer psStrOutputConfig;
                          		 sysbrg_user_pointer psPictBufConfig;
                          
		} sVDECDD_StreamSetOutputConfigCmd;
	
		struct
		{
			 IMG_UINT32 ui32BufMapId;
                          
		} sVDECDD_StreamFillPictBufCmd;
	
		struct
		{
			 IMG_UINT32 ui32StrId;
                          		 IMG_BOOL bDiscardRefs;
                          
		} sVDECDD_StreamFlushCmd;
	
		struct
		{
			 IMG_UINT32 ui32StrId;
                          		 VDEC_eBufType eBufType;
                          
		} sVDECDD_StreamReleaseBufsCmd;
	
		struct
		{
			 IMG_UINT32 ui32StrId;
                          		 VDEC_eErrorHandling eErrorHandling;
                          
		} sVDECDD_StreamSetBehaviourOnErrorsCmd;
	
		struct
		{
			 IMG_UINT32 ui32StrId;
                          		 sysbrg_user_pointer psStrStatus;
                          
		} sVDECDD_StreamGetStatusCmd;
	
		struct
		{
			 IMG_UINT32 ui32StrId;
                          		 sysbrg_user_pointer psStrUnit;
                          
		} sVDECDD_StreamSubmitUnitCmd;
	
	} sCmd;
} VDECDD_sCmdMsg;

typedef struct
{
    union
	{
	
		struct
		{
			IMG_RESULT		xVDECDD_IsSupportedFeatureResp;
		} sVDECDD_IsSupportedFeatureResp;
            
		struct
		{
			IMG_RESULT		xVDECDD_SupportedFeaturesResp;
		} sVDECDD_SupportedFeaturesResp;
            
		struct
		{
			IMG_RESULT		xVDECDD_StreamCreateResp;
		} sVDECDD_StreamCreateResp;
            
		struct
		{
			IMG_RESULT		xVDECDD_StreamDestroyResp;
		} sVDECDD_StreamDestroyResp;
            
		struct
		{
			IMG_RESULT		xVDECDD_GetCallbackEventResp;
		} sVDECDD_GetCallbackEventResp;
            
		struct
		{
			IMG_RESULT		xVDECDD_PreemptCallbackEventResp;
		} sVDECDD_PreemptCallbackEventResp;
            
		struct
		{
			IMG_RESULT		xVDECDD_StreamPlayResp;
		} sVDECDD_StreamPlayResp;
            
		struct
		{
			IMG_RESULT		xVDECDD_StreamStopResp;
		} sVDECDD_StreamStopResp;
            
		struct
		{
			IMG_RESULT		xVDECDD_StreamGetStopInfoResp;
		} sVDECDD_StreamGetStopInfoResp;
            
		struct
		{
			IMG_RESULT		xVDECDD_StreamGetSequHdrInfoResp;
		} sVDECDD_StreamGetSequHdrInfoResp;
            
		struct
		{
			IMG_RESULT		xVDECDD_StreamMapBufResp;
		} sVDECDD_StreamMapBufResp;
            
		struct
		{
			IMG_RESULT		xVDECDD_StreamUnmapBufResp;
		} sVDECDD_StreamUnmapBufResp;
            
		struct
		{
			IMG_RESULT		xVDECDD_StreamSetOutputConfigResp;
		} sVDECDD_StreamSetOutputConfigResp;
            
		struct
		{
			IMG_RESULT		xVDECDD_StreamFillPictBufResp;
		} sVDECDD_StreamFillPictBufResp;
            
		struct
		{
			IMG_RESULT		xVDECDD_StreamFlushResp;
		} sVDECDD_StreamFlushResp;
            
		struct
		{
			IMG_RESULT		xVDECDD_StreamReleaseBufsResp;
		} sVDECDD_StreamReleaseBufsResp;
            
		struct
		{
			IMG_RESULT		xVDECDD_StreamSetBehaviourOnErrorsResp;
		} sVDECDD_StreamSetBehaviourOnErrorsResp;
            
		struct
		{
			IMG_RESULT		xVDECDD_StreamGetStatusResp;
		} sVDECDD_StreamGetStatusResp;
            
		struct
		{
			IMG_RESULT		xVDECDD_StreamSubmitUnitResp;
		} sVDECDD_StreamSubmitUnitResp;
            
	} sResp;
} VDECDD_sRespMsg;



extern IMG_VOID VDECDD_dispatch(SYSBRG_sPacket __user *psPacket);

#ifdef __cplusplus
}
#endif

#endif
