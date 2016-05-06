#include "drv_venc_efl.h"
#include "drv_omxvenc_efl.h"
#include "drv_venc_osal.h"
#include "hi_drv_mem.h"

#include "hal_venc.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

extern OPTM_VENC_CHN_S g_stVencChn[VENC_MAX_CHN_NUM];
extern VeduEfl_IpCtx_S VeduIpCtx;

HI_U32 g_stKernelVirAddr[6] = {0};

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

/******************************************************************************
Function   :
Description:
Calls      :
Input      :
Output     :
Return     :
Others     :
******************************************************************************/
HI_S32 VENC_DRV_EflPutMsg_OMX(queue_info_s *queue, HI_U32 MsgID, HI_U32 Status, HI_VOID *MsgData)
{
    HI_S32 s32Ret = HI_SUCCESS;
	queue_data_s QueueData;

    memset((HI_VOID *)&QueueData, 0, sizeof(QueueData));
	if (NULL == queue)
	{
	   HI_ERR_VENC("%s :: invalid param queue = %p !!\n", __func__, queue);
	   return HI_FAILURE;
	}

	if (MsgData)
	{
	    memcpy((HI_VOID *)(&QueueData.msg_info_omx.buf), MsgData, sizeof(venc_user_buf));
	}
    s32Ret = VENC_DRV_MngQueue(queue, &QueueData, MsgID, Status);
    if (s32Ret == HI_SUCCESS)
    {
        VENC_DRV_EflWakeUpThread();
    }

    return s32Ret;
}

/******************************************************************************
Function   :
Description:
Calls      :
Input      :
Output     :
Return     :
Others     :
******************************************************************************/
HI_S32 VENC_DRV_EflGetMsg_OMX(queue_info_s *queue, venc_msginfo *pmsg_info)
{
    queue_data_s Queue_Data;
    memset((HI_VOID *)&Queue_Data, 0, sizeof(Queue_Data));

    if (VENC_DRV_MngDequeue(queue, &Queue_Data))
    {
        return HI_FAILURE;
    }
	memcpy((HI_VOID *)pmsg_info,(HI_VOID *)&Queue_Data.msg_info_omx,sizeof(venc_msginfo));

    return HI_SUCCESS;
}

HI_S32 VENC_DRV_EflFlushPort_OMX(HI_HANDLE EncHandle, HI_U32 u32PortIndex,HI_BOOL bIntra)
{
    HI_U32 u32ChnID             = 0;
    HI_S32 s32Ret1              = 0;
    HI_S32 s32Ret2              = 0;
    VeduEfl_EncPara_S *pEncPara = NULL;
    VEDU_LOCK_FLAG flag;

    D_VENC_GET_CHN(u32ChnID,EncHandle);
	D_VENC_CHECK_CHN(u32ChnID);
    pEncPara  = (VeduEfl_EncPara_S *)EncHandle;
    if(u32PortIndex != ALL_PORT && u32PortIndex > OUTPUT_PORT)
    {
        HI_ERR_VENC("%s, bad PortIndex(%d)!!\n",__func__, u32PortIndex);
        return HI_FAILURE;
    }

    VENC_DRV_OsalLock( VeduIpCtx.pChnLock, &flag);
    if( (OUTPUT_PORT == u32PortIndex) || (ALL_PORT == u32PortIndex) )
    {
       queue_data_s QueueData;
       memset((HI_VOID *)&QueueData, 0, sizeof(QueueData));

       while((!VENC_DRV_MngQueueEmpty(pEncPara->StreamQueue_OMX)) && (!s32Ret1))
       {
          s32Ret1 |= VENC_DRV_MngDequeue(pEncPara->StreamQueue_OMX, &QueueData);
		  if (!s32Ret1)
		  {
		     pEncPara->stStat.FlushUndoStreamNum++;//lzl add 记录flush undo stream的次数
		     pEncPara->stStat.StreamQueueNum--;
			 QueueData.msg_info_omx.buf.data_len = 0;
             VENC_DRV_EflPutMsg_OMX(pEncPara->MsgQueue_OMX, VENC_MSG_RESP_OUTPUT_DONE, s32Ret1, &(QueueData.msg_info_omx.buf));
			 pEncPara->stStat.MsgQueueNum++;
		  }
		  HI_INFO_VENC("%s, flush output port!\n", __func__);
       }

       HI_INFO_VENC("%s, flush output port ok!put message!\n", __func__);
	   if (!bIntra)
	   {
         VENC_DRV_EflPutMsg_OMX(pEncPara->MsgQueue_OMX, VENC_MSG_RESP_FLUSH_OUTPUT_DONE, s32Ret1 , NULL);
		 pEncPara->stStat.MsgQueueNum++;
	   }
	   pEncPara->bOutPutbufflush = HI_TRUE;
    }

    VENC_DRV_OsalUnlock( VeduIpCtx.pChnLock, &flag );

    if((INPUT_PORT == u32PortIndex) || (ALL_PORT == u32PortIndex))
    {
		HI_S32 s32Ret = HI_SUCCESS;
		do{
			s32Ret = VENC_DRV_EflGetImage_OMX(EncHandle, &(pEncPara->stImage_OMX));
			if (s32Ret == HI_SUCCESS)
			{
                pEncPara->stStat.FlushUndoFrameNum++;//lzl add 记录flush undo frame的次数
				VENC_DRV_EflPutMsg_OMX(pEncPara->MsgQueue_OMX, VENC_MSG_RESP_INPUT_DONE, HI_SUCCESS , &(pEncPara->stImage_OMX));
	            pEncPara->stStat.MsgQueueNum++;

				HI_INFO_VENC("%s, flush input port! QueueNum:%d VeduIpCtx.StopTask:%d\n",__func__, pEncPara->stStat.QueueNum,VeduIpCtx.StopTask);
			}

            msleep(5); //是否需要延时?  ljh
  		  }while((!VeduIpCtx.StopTask) && (!VENC_DRV_MngQueueEmpty(pEncPara->FrameQueue_OMX)));

        HI_INFO_VENC("%s, flush input port ok!\n", __func__);
	    if (!bIntra)
	    {
	        VENC_DRV_EflPutMsg_OMX(pEncPara->MsgQueue_OMX, VENC_MSG_RESP_FLUSH_INPUT_DONE, HI_SUCCESS , NULL);
		    pEncPara->stStat.MsgQueueNum++;
	    }
		pEncPara->bInPutbufflush = HI_TRUE;
    }

    return (s32Ret1||s32Ret2);
}
/*************************************************************************************/
#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif
