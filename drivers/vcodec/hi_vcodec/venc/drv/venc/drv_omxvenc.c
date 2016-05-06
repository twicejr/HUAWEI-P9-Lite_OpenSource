

#include "hal_venc.h"
#include "drv_venc_ext.h"
#include "drv_venc_efl.h"
#include "drv_omxvenc_efl.h"
#include "drv_venc_osal.h"
#include "drv_venc_buf_mng.h"
#include "drv_omxvenc.h"
#include "hi_drv_video.h"
#include "hi_drv_mem.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */

extern OPTM_VENC_CHN_S g_stVencChn[VENC_MAX_CHN_NUM];

#define D_VENC_GET_CHN(u32VeChn, hVencChn) \
    do {\
        u32VeChn = 0; \
        while (u32VeChn < VENC_MAX_CHN_NUM)\
        {   \
            if (g_stVencChn[u32VeChn].hVEncHandle == hVencChn)\
            { \
                break; \
            } \
            u32VeChn++; \
        } \
    } while (0)

#define D_VENC_GET_PRIORITY_ID(s32VeChn, sPriorityID) \
    do {\
        sPriorityID = 0; \
        while (sPriorityID < VENC_MAX_CHN_NUM)\
        {   \
            if (PriorityTab[0][sPriorityID] == s32VeChn)\
            { \
                break; \
            } \
            sPriorityID++; \
        } \
    } while (0)

enum {
	OMX_VENC_YUV_420	= 0,
	OMX_VENC_YUV_422	= 1,
	OMX_VENC_YUV_444	= 2,
	OMX_VENC_YUV_NONE	= 3
};

enum {
	OMX_VENC_V_U		= 0,
	OMX_VENC_U_V		= 1,
	OMX_VENC_A_R_G_B	= 2,
	OMX_VENC_R_G_B_A	= 3,
	OMX_VENC_A_B_G_R	= 4,
	OMX_VENC_B_G_R_A	= 5
};

enum {
	OMX_VENC_STORE_SEMIPLANNAR	= 0,
	OMX_VENC_STORE_PACKAGE		= 1,
	OMX_VENC_STORE_PLANNAR		= 2,
	OMX_VENC_STORE_RGB			= 3
};

enum {
	OMX_VENC_PACKAGE_UY0VY1 	= 141/*0b10001101*/,
	OMX_VENC_PACKAGE_Y0UY1V 	= 216/*0b11011000*/,
	OMX_VENC_PACKAGE_Y0VY1U 	= 120/*0b01111000*/,
	OMX_VENC_PACKAGE_VY0UY1 	= 121
};


HI_S32 VENC_DRV_QueueFrame_OMX(HI_HANDLE hVencChn, venc_user_buf *pstFrameInfo)
{
   HI_S32 s32Ret   = HI_SUCCESS;
   HI_U32 u32VeChn = 0;
   VeduEfl_EncPara_S  *pEncPara = NULL;
   HI_DRV_VIDEO_FRAME_S stFrame;

   memset((HI_VOID *)&stFrame,0,sizeof(HI_DRV_VIDEO_FRAME_S));
   D_VENC_GET_CHN(u32VeChn, hVencChn);
   if(VENC_MAX_CHN_NUM == u32VeChn )
   {
       HI_ERR_VENC("the handle(%x) does not start or even not be create either!\n",hVencChn);
       return HI_FAILURE;
   }

   pEncPara = (VeduEfl_EncPara_S *)hVencChn;
   pEncPara->stStat.QueueFrameNumTry++;
#ifdef TEST_TIME
   pEncPara->stStat.EtbTime[pEncPara->stStat.InputNum] = HI_GetTS();
   pEncPara->stStat.InputNum++;
   if(5 == pEncPara->stStat.InputNum)
   {
	   pEncPara->stStat.InputNum = 0;
   }
#endif

   s32Ret = VENC_DRV_EflPutMsg_OMX(pEncPara->FrameQueue_OMX,VENC_MSG_RESP_INPUT_DONE, 0, pstFrameInfo);
   if (!s32Ret)
   {
      pEncPara->stStat.QueueNum++;
      pEncPara->stStat.QueueFrameNumOK++;
	  pEncPara->bInPutbufflush = HI_FALSE;
   }

   return s32Ret;
}

HI_S32 VENC_DRV_QueueStream_OMX(HI_HANDLE hVencChn, venc_user_buf *pstFrameInfo)
{
   HI_S32 s32Ret   = HI_SUCCESS;
   HI_S32 s32VeChn = 0;
   VeduEfl_EncPara_S  *pEncPara = NULL;

   D_VENC_GET_CHN(s32VeChn, hVencChn);
   if(VENC_MAX_CHN_NUM == s32VeChn )
   {
       HI_ERR_VENC("the handle(%x) does not start or even not be create either!\n",hVencChn);
       return HI_FAILURE;
   }

   pEncPara = (VeduEfl_EncPara_S *)hVencChn;
   HI_DBG_VENC("pEncPara:0x%x\n",pEncPara);
   pEncPara->stStat.QueueStreamNumTry++;

   s32Ret = VENC_DRV_EflPutMsg_OMX(pEncPara->StreamQueue_OMX,VENC_MSG_RESP_OUTPUT_DONE, 0, pstFrameInfo);
   if (!s32Ret)
   {
      pEncPara->stStat.StreamQueueNum++;
      pEncPara->stStat.QueueStreamNumOK++;
	  pEncPara->bOutPutbufflush = HI_FALSE;
   }

   return s32Ret;
}

HI_S32 VENC_DRV_GetMessage_OMX(HI_HANDLE hVencChn, venc_msginfo *pmsg_info )
{
   HI_S32 s32Ret   = HI_SUCCESS;
   HI_S32 s32VeChn = 0;
   VeduEfl_EncPara_S* pstEncChnPara = NULL;
   venc_msginfo msg_info;

   memset((HI_VOID *)&msg_info, 0, sizeof(msg_info));
   D_VENC_GET_CHN(s32VeChn, hVencChn);
   if(VENC_MAX_CHN_NUM == s32VeChn )
   {
       HI_ERR_VENC("the handle(%x) does not start or even not be create either!\n",hVencChn);
       return HI_FAILURE;
   }

   if(NULL == pmsg_info)
   {
       HI_ERR_VENC("%s :: invalid param : pmsg_info = %p !!!\n", __func__, pmsg_info);
       return HI_FAILURE;
   }
   pstEncChnPara = (VeduEfl_EncPara_S*)hVencChn;

   s32Ret = VENC_DRV_EflGetMsg_OMX(pstEncChnPara->MsgQueue_OMX, &msg_info);
   if (HI_SUCCESS != s32Ret)
   {
        return HI_FAILURE;
   }

   pstEncChnPara->stStat.MsgQueueNum--;
   memcpy((HI_VOID *)pmsg_info ,(HI_VOID *)(&msg_info) , sizeof(venc_msginfo));

   return HI_SUCCESS;
}

HI_S32 VENC_DRV_FlushPort_OMX(HI_HANDLE hVencChn, HI_U32 u32PortIndex)
{
   HI_S32 s32VeChn = 0;

   D_VENC_GET_CHN(s32VeChn, hVencChn);
   if(VENC_MAX_CHN_NUM == s32VeChn )
   {
       HI_ERR_VENC("the handle(%x) does not start or even not be create either!\n",hVencChn);
       return HI_FAILURE;
   }

   return VENC_DRV_EflFlushPort_OMX(hVencChn,u32PortIndex,HI_FALSE);
}

HI_S32 VENC_DRV_KEN_Map_OMX(venc_user_buf * pstFrameBuf)
{
   HI_S32 s32Ret = HI_SUCCESS;

   if(NULL == pstFrameBuf)
   {
      HI_ERR_VENC("%s:: invalid param : pstFrameBuf = %p !!\n",__func__, pstFrameBuf);
      return HI_FAILURE;
   }

   s32Ret = DRV_MMU_GetPhyAddr_KernelVaddr(pstFrameBuf);
   if((s32Ret != HI_SUCCESS) || (NULL == (HI_U64 *)pstFrameBuf->kernelbufferaddr))
   {
      HI_ERR_VENC("%s:: VENC_DRV_EflMMapToKernel failed!\n",__func__);
      return HI_FAILURE;
   }

   return HI_SUCCESS;
}

HI_S32 VENC_DRV_KEN_UMMap_OMX(venc_user_buf * pstFrameBuf )
{
   HI_S32 s32Ret = HI_SUCCESS;

   if(!pstFrameBuf)
   {
      HI_ERR_VENC("%s:: bad input!!\n",__func__);
      return HI_FAILURE;
   }

 //  s32Ret = VENC_DRV_EflUMMapToKernel_OMX(hVencChn, pMMZbuf);
   if( HI_SUCCESS != s32Ret )
   {
      HI_ERR_VENC("%s:: VENC_DRV_EflUMMapToKernel failed!\n",__func__);
      return HI_FAILURE;
   }
   return HI_SUCCESS;
}

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */

