/*!
 *****************************************************************************
 *
 * @File       vdecdd_server.c
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

#include "sysbrg_api.h"
#include "sysbrg_api_km.h"
#include "sysos_api_km.h"
#include "vdecdd.h"
#include "vdecdd_rpc.h"


IMG_VOID VDECDD_dispatch(SYSBRG_sPacket *psPacket)
{
	VDECDD_sCmdMsg sCommandMsg;
	VDECDD_sRespMsg sResponseMsg;

	if(SYSOSKM_CopyFromUser(&sCommandMsg, psPacket->pvCmdData, sizeof(sCommandMsg)))
		IMG_ASSERT(!"failed to copy from user");

	switch (sCommandMsg.eFuncId)
	{
	
      case VDECDD_IsSupportedFeature_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "VDECDD_IsSupportedFeature");
#else
      printk("bridge %s %s\n", __FUNCTION__, "VDECDD_IsSupportedFeature");
#endif
#endif
      
	sResponseMsg.sResp.sVDECDD_IsSupportedFeatureResp.xVDECDD_IsSupportedFeatureResp =
      		VDECDD_IsSupportedFeature(
      
	  sCommandMsg.sCmd.sVDECDD_IsSupportedFeatureCmd.ui32ConnId,
	  sCommandMsg.sCmd.sVDECDD_IsSupportedFeatureCmd.eFeature,
	  sCommandMsg.sCmd.sVDECDD_IsSupportedFeatureCmd.pbSupported
      );
      break;
      
    
      case VDECDD_SupportedFeatures_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "VDECDD_SupportedFeatures");
#else
      printk("bridge %s %s\n", __FUNCTION__, "VDECDD_SupportedFeatures");
#endif
#endif
      
	sResponseMsg.sResp.sVDECDD_SupportedFeaturesResp.xVDECDD_SupportedFeaturesResp =
      		VDECDD_SupportedFeatures(
      
	  sCommandMsg.sCmd.sVDECDD_SupportedFeaturesCmd.ui32ConnId,
	  sCommandMsg.sCmd.sVDECDD_SupportedFeaturesCmd.psFeature
      );
      break;
      
    
      case VDECDD_StreamCreate_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "VDECDD_StreamCreate");
#else
      printk("bridge %s %s\n", __FUNCTION__, "VDECDD_StreamCreate");
#endif
#endif
      
	sResponseMsg.sResp.sVDECDD_StreamCreateResp.xVDECDD_StreamCreateResp =
      		VDECDD_StreamCreate(
      
	  sCommandMsg.sCmd.sVDECDD_StreamCreateCmd.psStrConfigData,
	  sCommandMsg.sCmd.sVDECDD_StreamCreateCmd.pvStrCbParam,
	  sCommandMsg.sCmd.sVDECDD_StreamCreateCmd.pui32StrId
      );
      break;
      
    
      case VDECDD_StreamDestroy_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "VDECDD_StreamDestroy");
#else
      printk("bridge %s %s\n", __FUNCTION__, "VDECDD_StreamDestroy");
#endif
#endif
      
	sResponseMsg.sResp.sVDECDD_StreamDestroyResp.xVDECDD_StreamDestroyResp =
      		VDECDD_StreamDestroy(
      
	  sCommandMsg.sCmd.sVDECDD_StreamDestroyCmd.ui32StrId
      );
      break;
      
    
      case VDECDD_GetCallbackEvent_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "VDECDD_GetCallbackEvent");
#else
      printk("bridge %s %s\n", __FUNCTION__, "VDECDD_GetCallbackEvent");
#endif
#endif
      
	sResponseMsg.sResp.sVDECDD_GetCallbackEventResp.xVDECDD_GetCallbackEventResp =
      		VDECDD_GetCallbackEvent(
      
	  sCommandMsg.sCmd.sVDECDD_GetCallbackEventCmd.ui32StrId,
	  sCommandMsg.sCmd.sVDECDD_GetCallbackEventCmd.psCallBackInfo
      );
      break;
      
    
      case VDECDD_PreemptCallbackEvent_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "VDECDD_PreemptCallbackEvent");
#else
      printk("bridge %s %s\n", __FUNCTION__, "VDECDD_PreemptCallbackEvent");
#endif
#endif
      
	sResponseMsg.sResp.sVDECDD_PreemptCallbackEventResp.xVDECDD_PreemptCallbackEventResp =
      		VDECDD_PreemptCallbackEvent(
      
	  sCommandMsg.sCmd.sVDECDD_PreemptCallbackEventCmd.ui32StrId
      );
      break;
      
    
      case VDECDD_StreamPlay_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "VDECDD_StreamPlay");
#else
      printk("bridge %s %s\n", __FUNCTION__, "VDECDD_StreamPlay");
#endif
#endif
      
	sResponseMsg.sResp.sVDECDD_StreamPlayResp.xVDECDD_StreamPlayResp =
      		VDECDD_StreamPlay(
      
	  sCommandMsg.sCmd.sVDECDD_StreamPlayCmd.ui32StrId,
	  sCommandMsg.sCmd.sVDECDD_StreamPlayCmd.ePlayMode,
	  sCommandMsg.sCmd.sVDECDD_StreamPlayCmd.eStopPoint,
	  sCommandMsg.sCmd.sVDECDD_StreamPlayCmd.ui32StopPointQual
      );
      break;
      
    
      case VDECDD_StreamStop_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "VDECDD_StreamStop");
#else
      printk("bridge %s %s\n", __FUNCTION__, "VDECDD_StreamStop");
#endif
#endif
      
	sResponseMsg.sResp.sVDECDD_StreamStopResp.xVDECDD_StreamStopResp =
      		VDECDD_StreamStop(
      
	  sCommandMsg.sCmd.sVDECDD_StreamStopCmd.ui32StrId,
	  sCommandMsg.sCmd.sVDECDD_StreamStopCmd.eStopPoint,
	  sCommandMsg.sCmd.sVDECDD_StreamStopCmd.ui32StopPointQual
      );
      break;
      
    
      case VDECDD_StreamGetStopInfo_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "VDECDD_StreamGetStopInfo");
#else
      printk("bridge %s %s\n", __FUNCTION__, "VDECDD_StreamGetStopInfo");
#endif
#endif
      
	sResponseMsg.sResp.sVDECDD_StreamGetStopInfoResp.xVDECDD_StreamGetStopInfoResp =
      		VDECDD_StreamGetStopInfo(
      
	  sCommandMsg.sCmd.sVDECDD_StreamGetStopInfoCmd.ui32StrId,
	  sCommandMsg.sCmd.sVDECDD_StreamGetStopInfoCmd.psStopInfo
      );
      break;
      
    
      case VDECDD_StreamGetSequHdrInfo_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "VDECDD_StreamGetSequHdrInfo");
#else
      printk("bridge %s %s\n", __FUNCTION__, "VDECDD_StreamGetSequHdrInfo");
#endif
#endif
      
	sResponseMsg.sResp.sVDECDD_StreamGetSequHdrInfoResp.xVDECDD_StreamGetSequHdrInfoResp =
      		VDECDD_StreamGetSequHdrInfo(
      
	  sCommandMsg.sCmd.sVDECDD_StreamGetSequHdrInfoCmd.ui32StrId,
	  sCommandMsg.sCmd.sVDECDD_StreamGetSequHdrInfoCmd.psComSequHdrInfo
      );
      break;
      
    
      case VDECDD_StreamMapBuf_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "VDECDD_StreamMapBuf");
#else
      printk("bridge %s %s\n", __FUNCTION__, "VDECDD_StreamMapBuf");
#endif
#endif
      
	sResponseMsg.sResp.sVDECDD_StreamMapBufResp.xVDECDD_StreamMapBufResp =
      		VDECDD_StreamMapBuf(
      
	  sCommandMsg.sCmd.sVDECDD_StreamMapBufCmd.ui32StrId,
	  sCommandMsg.sCmd.sVDECDD_StreamMapBufCmd.pvBufCbParam,
	  sCommandMsg.sCmd.sVDECDD_StreamMapBufCmd.eBufType,
	  sCommandMsg.sCmd.sVDECDD_StreamMapBufCmd.psBufInfo,
	  sCommandMsg.sCmd.sVDECDD_StreamMapBufCmd.pui32BufMapId
      );
      break;
      
    
      case VDECDD_StreamUnmapBuf_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "VDECDD_StreamUnmapBuf");
#else
      printk("bridge %s %s\n", __FUNCTION__, "VDECDD_StreamUnmapBuf");
#endif
#endif
      
	sResponseMsg.sResp.sVDECDD_StreamUnmapBufResp.xVDECDD_StreamUnmapBufResp =
      		VDECDD_StreamUnmapBuf(
      
	  sCommandMsg.sCmd.sVDECDD_StreamUnmapBufCmd.ui32BufMapId
      );
      break;
      
    
      case VDECDD_StreamSetOutputConfig_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "VDECDD_StreamSetOutputConfig");
#else
      printk("bridge %s %s\n", __FUNCTION__, "VDECDD_StreamSetOutputConfig");
#endif
#endif
      
	sResponseMsg.sResp.sVDECDD_StreamSetOutputConfigResp.xVDECDD_StreamSetOutputConfigResp =
      		VDECDD_StreamSetOutputConfig(
      
	  sCommandMsg.sCmd.sVDECDD_StreamSetOutputConfigCmd.ui32StrId,
	  sCommandMsg.sCmd.sVDECDD_StreamSetOutputConfigCmd.psStrOutputConfig,
	  sCommandMsg.sCmd.sVDECDD_StreamSetOutputConfigCmd.psPictBufConfig
      );
      break;
      
    
      case VDECDD_StreamFillPictBuf_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "VDECDD_StreamFillPictBuf");
#else
      printk("bridge %s %s\n", __FUNCTION__, "VDECDD_StreamFillPictBuf");
#endif
#endif
      
	sResponseMsg.sResp.sVDECDD_StreamFillPictBufResp.xVDECDD_StreamFillPictBufResp =
      		VDECDD_StreamFillPictBuf(
      
	  sCommandMsg.sCmd.sVDECDD_StreamFillPictBufCmd.ui32BufMapId
      );
      break;
      
    
      case VDECDD_StreamFlush_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "VDECDD_StreamFlush");
#else
      printk("bridge %s %s\n", __FUNCTION__, "VDECDD_StreamFlush");
#endif
#endif
      
	sResponseMsg.sResp.sVDECDD_StreamFlushResp.xVDECDD_StreamFlushResp =
      		VDECDD_StreamFlush(
      
	  sCommandMsg.sCmd.sVDECDD_StreamFlushCmd.ui32StrId,
	  sCommandMsg.sCmd.sVDECDD_StreamFlushCmd.bDiscardRefs
      );
      break;
      
    
      case VDECDD_StreamReleaseBufs_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "VDECDD_StreamReleaseBufs");
#else
      printk("bridge %s %s\n", __FUNCTION__, "VDECDD_StreamReleaseBufs");
#endif
#endif
      
	sResponseMsg.sResp.sVDECDD_StreamReleaseBufsResp.xVDECDD_StreamReleaseBufsResp =
      		VDECDD_StreamReleaseBufs(
      
	  sCommandMsg.sCmd.sVDECDD_StreamReleaseBufsCmd.ui32StrId,
	  sCommandMsg.sCmd.sVDECDD_StreamReleaseBufsCmd.eBufType
      );
      break;
      
    
      case VDECDD_StreamSetBehaviourOnErrors_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "VDECDD_StreamSetBehaviourOnErrors");
#else
      printk("bridge %s %s\n", __FUNCTION__, "VDECDD_StreamSetBehaviourOnErrors");
#endif
#endif
      
	sResponseMsg.sResp.sVDECDD_StreamSetBehaviourOnErrorsResp.xVDECDD_StreamSetBehaviourOnErrorsResp =
      		VDECDD_StreamSetBehaviourOnErrors(
      
	  sCommandMsg.sCmd.sVDECDD_StreamSetBehaviourOnErrorsCmd.ui32StrId,
	  sCommandMsg.sCmd.sVDECDD_StreamSetBehaviourOnErrorsCmd.eErrorHandling
      );
      break;
      
    
      case VDECDD_StreamGetStatus_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "VDECDD_StreamGetStatus");
#else
      printk("bridge %s %s\n", __FUNCTION__, "VDECDD_StreamGetStatus");
#endif
#endif
      
	sResponseMsg.sResp.sVDECDD_StreamGetStatusResp.xVDECDD_StreamGetStatusResp =
      		VDECDD_StreamGetStatus(
      
	  sCommandMsg.sCmd.sVDECDD_StreamGetStatusCmd.ui32StrId,
	  sCommandMsg.sCmd.sVDECDD_StreamGetStatusCmd.psStrStatus
      );
      break;
      
    
      case VDECDD_StreamSubmitUnit_ID:
      
#if 0
#ifdef CONFIG_COMPAT      
      printk("bridge %d %s %s\n", is_compat_task(), __FUNCTION__, "VDECDD_StreamSubmitUnit");
#else
      printk("bridge %s %s\n", __FUNCTION__, "VDECDD_StreamSubmitUnit");
#endif
#endif
      
	sResponseMsg.sResp.sVDECDD_StreamSubmitUnitResp.xVDECDD_StreamSubmitUnitResp =
      		VDECDD_StreamSubmitUnit(
      
	  sCommandMsg.sCmd.sVDECDD_StreamSubmitUnitCmd.ui32StrId,
	  sCommandMsg.sCmd.sVDECDD_StreamSubmitUnitCmd.psStrUnit
      );
      break;
      
    
	}
	if(SYSOSKM_CopyToUser(psPacket->pvRespData, &sResponseMsg, sizeof(sResponseMsg)))
		IMG_ASSERT(!"failed to copy to user");
}
