/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : ImsaProcImsSmsMsg.c
  Description     : 该C文件实现IMS短信消息处理和IMS短信消息发送
  History           :
     1.sunbing 49683      2013-06-19  Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "ImsaProcImsSmsMsg.h"
#include "ImsaEntity.h"
#include "ImsaImsInterface.h"
#include "ImsaProcSmsMsg.h"
#include "ImsaPublic.h"


/*lint -e767*/
#define    THIS_FILE_ID         PS_FILE_ID_IMSAPROCIMSSMSMSG_C
#define    THIS_NAS_FILE_ID     NAS_FILE_ID_IMSAPROCIMSSMSMSG_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
extern VOS_VOID IMSA_SMS_SndMsgDataInd(const VOS_UINT8* ucData, VOS_UINT32 ulDataLen);
extern VOS_VOID IMSA_SMS_ProcNwSmsReceived(const IMSA_IMS_OUTPUT_SMS_EVENT_STRU  *pstOutSms);
extern VOS_VOID IMSA_SMS_ProcNwSmsErr(const IMSA_IMS_OUTPUT_SMS_EVENT_STRU  *pstOutSms);
extern VOS_VOID IMSA_SMS_ProcNwSmsRpError(const IMSA_IMS_OUTPUT_SMS_EVENT_STRU  *pstOutSms);

/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name  : IMSA_SMS_SndMsgDataInd()
 Description    : 发送Data ind消息
 Input          : ucData MSG内容，ulDataLen MSG长度
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-08-10  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SMS_SndMsgDataInd(const VOS_UINT8* ucData, VOS_UINT32 ulDataLen)
{
    IMSA_MSG_DATA_IND_STRU      *pstDataInd;
    VOS_UINT32                   ulMsgDataLen;

    if(ulDataLen < 4)
    {
        ulMsgDataLen = sizeof(IMSA_MSG_DATA_IND_STRU);
    }
    else
    {
        /*lint -e961*/
        ulMsgDataLen = sizeof(IMSA_MSG_DATA_IND_STRU)+ ulDataLen -4;
        /*lint +e961*/
    }

    /*分配消息空间*/
    pstDataInd = (VOS_VOID*)IMSA_ALLOC_MSG(ulMsgDataLen);

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstDataInd)
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_SMS_SndMsgDataInd:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SMS_SndMsgDataInd_ENUM, LNAS_NULL_PTR);
        return ;
    }

    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY_BY_NAME(pstDataInd),
                    IMSA_GET_MSG_LENGTH(pstDataInd),
                    0,
                    IMSA_GET_MSG_LENGTH(pstDataInd));

    IMSA_WRITE_MSG_MSG_HEAD(pstDataInd,ID_IMSA_MSG_DATA_IND);

    /*短信接受域为PS域*/
    pstDataInd->ucRcvDomain = 0;

    /*填写SMS内容*/
    pstDataInd->ulDataLen  = ulDataLen;
    IMSA_MEM_CPY_S(pstDataInd->aucData,ulDataLen,ucData,ulDataLen);

    /*调用消息发送函数 */
    IMSA_SND_MSG(pstDataInd);

}

/*****************************************************************************
 Function Name  : IMSA_SMS_SndMsgReportInd()
 Description    : 发送report消息
 Input          : ucData MSG内容，ulDataLen MSG长度
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-08-10  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SMS_SndMsgReportInd(VOS_UINT32 ulErrCode,
                                              const VOS_UINT8* pucData,
                                              VOS_UINT32 ulDataLen)
{
    IMSA_MSG_REPORT_IND_STRU    *pstReportInd;

    /*超长短信*/
    if(ulDataLen > SMR_SMT_RP_USER_DATA_LENGTH)
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_SMS_SndMsgReportInd:Length is too long!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SMS_SndMsgReportInd_ENUM, LNAS_PARAM_INVALID);
        return ;
    }

    /*分配消息空间*/
    pstReportInd = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_MSG_REPORT_IND_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstReportInd)
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_SMS_SndMsgReportInd:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SMS_SndMsgReportInd_ENUM, LNAS_NULL_PTR);
        return ;
    }

    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY_BY_NAME(pstReportInd),
                    IMSA_GET_MSG_LENGTH(pstReportInd),
                    0,
                    IMSA_GET_MSG_LENGTH(pstReportInd));

    IMSA_WRITE_MSG_MSG_HEAD(pstReportInd,ID_IMSA_MSG_REPORT_IND);

    /*填写SMS内容*/
    pstReportInd->enErrorCode           = ulErrCode;

    if(VOS_NULL_PTR != pucData)
    {
        pstReportInd->stRpduData.ulDataLen  = ulDataLen;
        IMSA_MEM_CPY_S(pstReportInd->stRpduData.aucData,ulDataLen,pucData,ulDataLen);
    }

    /*调用消息发送函数 */
    IMSA_SND_MSG(pstReportInd);

}

/*****************************************************************************
 Function Name  : IMSA_SMS_ProcNwSmsErr()
 Description    : 收到IMS协议栈的短信错误的处理函数
 Input          : HICSM_OutputSms  *pstOutSms
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-08-10  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SMS_ProcNwSmsErr(const IMSA_IMS_OUTPUT_SMS_EVENT_STRU  *pstOutSms)
{
    IMSA_SMS_SMR_MO_STRU                *pstSmrMoEntity;
    VOS_UINT32                          ulErrCode;

    pstSmrMoEntity = IMSA_SMS_GetSmrMoEntityAddress();
    if(IMSA_SMS_SMR_STATE_WAIT_FOR_RP_ACK != pstSmrMoEntity->enState)
    {
        IMSA_WARN_LOG("IMSA_SMS_ProcNwSmsErr: Mo entity is not WAIT_FOR_RP_ACK!");
        TLPS_PRINT2LAYER_WARNING(IMSA_SMS_ProcNwSmsErr_ENUM, 1);
        return;
    }

    /*MO实体状态进行空闲态，停止TI_IMSA_SMS_TR1M保护定时器*/
    pstSmrMoEntity->enState = IMSA_SMS_SMR_STATE_IDLE;

    pstSmrMoEntity->ucMemAvailFlg = IMSA_SMS_FALSE;                   /* 清除mem avail标志                        */
    pstSmrMoEntity->ucRetransFlg  = IMSA_SMR_RETRANS_PERMIT;          /* 复位重发标志                             */

    IMSA_StopTimer(&pstSmrMoEntity->stTR1MTimer);
    ulErrCode = SMR_SMT_ERROR_IMS_ERROR_BEGIN + pstOutSms->stErrorCode.usSipStatusCode;

    IMSA_SMS_SndMsgReportInd(ulErrCode,VOS_NULL_PTR,0);

    #if (FEATURE_ON == FEATURE_DSDS)
    if ((PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared()) &&
        (IMSA_TASKTYPE_STATUS_NULL != IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS)))
    {
        /* 如果延迟回复抢占定时器超时，应该直接回复CNF */
        IMSA_DsdsProcResourceOccupyCnf(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS);

        IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS);
    }
    #endif

    IMSA_CommonDeregProc();
}

/*****************************************************************************
 Function Name  : IMSA_SMS_ProcNwSmsRpError()
 Description    : 收到网络回复的RP-ERROR的处理
 Input          : IMSA_IMS_OUTPUT_SMS_EVENT_STRU  *pstOutSms
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2013-10-10  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SMS_ProcNwSmsRpError(const IMSA_IMS_OUTPUT_SMS_EVENT_STRU  *pstOutSms)
{
    IMSA_SMS_SMR_MO_STRU                *pstSmrMoEntity;

    IMSA_WARN_LOG("IMSA_SMS_ProcNwSmsRpError: enter.");
    TLPS_PRINT2LAYER_WARNING(IMSA_SMS_ProcNwSmsRpError_ENUM, LNAS_ENTRY);

    pstSmrMoEntity = IMSA_SMS_GetSmrMoEntityAddress();

    if(IMSA_SMS_SMR_STATE_WAIT_FOR_RP_ACK != pstSmrMoEntity->enState)
    {
        IMSA_WARN_LOG("IMSA_SMS_ProcNwSmsRpError: Mo entity is not WAIT_FOR_RP_ACK!");
        TLPS_PRINT2LAYER_WARNING(IMSA_SMS_ProcNwSmsRpError_ENUM, 2);
        return;
    }

    if(pstOutSms->aucMessage[1] != pstSmrMoEntity->ucMessageReference)
    {
        IMSA_WARN_LOG("IMSA_SMS_ProcNwSmsRpError: MR is not equel.");
        TLPS_PRINT2LAYER_WARNING(IMSA_SMS_ProcNwSmsRpError_ENUM, 3);
        return;
    }

    /*MO实体状态进行空闲态，停止TI_IMSA_SMS_TR1M保护定时器*/
    pstSmrMoEntity->enState = IMSA_SMS_SMR_STATE_IDLE;
    IMSA_StopTimer(&pstSmrMoEntity->stTR1MTimer);

    if (IMSA_SMS_TRUE == pstSmrMoEntity->ucMemAvailFlg )
    {
        /* 此过程是mem avail过程                    */
        /* 对错误原因值的处理，参考GU代码实现，在协议要求在#41时，重传RP-SMMA的基础上，
        增加在原因值为#42，47,38时重传RP-SMMA */
        if ((IMSA_SMR_ERR_CAUSE_TEMP_FAILURE   == pstOutSms->aucMessage[IMSA_SMS_RP_ERROR_OFFSET])
            || (IMSA_SMR_ERR_CAUSE_CONGESTION  == pstOutSms->aucMessage[IMSA_SMS_RP_ERROR_OFFSET])
            || (IMSA_SMR_ERR_CAUSE_RES_UNAVAIL == pstOutSms->aucMessage[IMSA_SMS_RP_ERROR_OFFSET])
            || (IMSA_SMR_ERR_CAUSE_NET_OUT_OF_ORDER == pstOutSms->aucMessage[IMSA_SMS_RP_ERROR_OFFSET]))
        {                                                               /* 是temporary error                        */
            IMSA_SMS_MemNotifyRetrans(SMR_SMT_ERROR_RP_ERROR_BEGIN|pstOutSms->aucMessage[IMSA_SMS_RP_ERROR_OFFSET]);         /* 调用重发过程的处理                       */
        }
        else
        {
            /*错误码是RP ERR加上网络携带的错误码*/
            IMSA_SMS_SndMsgReportInd(SMR_SMT_ERROR_RP_ERROR_BEGIN|pstOutSms->aucMessage[IMSA_SMS_RP_ERROR_OFFSET],
                                       (VOS_UINT8*)pstOutSms->aucMessage,\
                                        pstOutSms->ucMessageLen);
            pstSmrMoEntity->ucMemAvailFlg = IMSA_SMS_FALSE;                   /* 清除mem avail标志                        */
            pstSmrMoEntity->ucRetransFlg  = IMSA_SMR_RETRANS_PERMIT;          /* 复位重发标志                             */
            pstSmrMoEntity->enState = IMSA_SMS_SMR_STATE_IDLE;                                      /* 状态迁移到空闲状态                       */

            #if (FEATURE_ON == FEATURE_DSDS)
            if ((PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared()) &&
                (IMSA_TASKTYPE_STATUS_NULL != IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS)))
            {
                /* 如果延迟回复抢占定时器超时，应该直接回复CNF */
                IMSA_DsdsProcResourceOccupyCnf(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS);

                IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS);
            }
            #endif

            IMSA_CommonDeregProc();
        }
    }
    else
    {
        /*错误码是RP ERR加上网络携带的错误码*/
        IMSA_SMS_SndMsgReportInd(SMR_SMT_ERROR_RP_ERROR_BEGIN|pstOutSms->aucMessage[IMSA_SMS_RP_ERROR_OFFSET],
                           (VOS_UINT8*)pstOutSms->aucMessage,\
                            pstOutSms->ucMessageLen);

        #if (FEATURE_ON == FEATURE_DSDS)
        if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
        {
            /* 如果延迟回复抢占定时器超时，应该直接回复CNF */
            IMSA_DsdsProcResourceOccupyCnf(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS);

            IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS);
        }
        #endif

        IMSA_CommonDeregProc();
    }
}


/*****************************************************************************
 Function Name  : IMSA_SMS_ProcNwSmsReceived()
 Description    : 收到网络的短信内容的处理函数
 Input          : HICSM_OutputSms  *pstOutSms
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-08-10  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SMS_ProcNwSmsReceived(const IMSA_IMS_OUTPUT_SMS_EVENT_STRU  *pstOutSms)
{
    IMSA_SMS_SMR_MO_STRU                *pstSmrMoEntity;
    IMSA_SMS_SMR_MT_STRU                *pstSmrMtEntity;

    /*根据消息类型处理*/
    switch(pstOutSms->aucMessage[0])
    {
    /*MT RP Data*/
    case IMSA_SMS_NTM_DATA_TYPE_RP_DATA:
        pstSmrMtEntity = IMSA_SMS_GetSmrMtEntityAddress();
        if(pstSmrMtEntity->enState != IMSA_SMS_SMR_STATE_IDLE)
        {
            IMSA_WARN_LOG("IMSA_SMS_ProcNwSmsReceived: Mt entity is not idle!");
            TLPS_PRINT2LAYER_WARNING(IMSA_SMS_ProcNwSmsReceived_ENUM, 1);
            break;
        }
        switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_MT_SMS))
        {
            case IMSA_RESOURCE_STATUS_ACTIVE:

                /*MT短信，MT实体转状态，保存MR，启动TI_IMSA_SMS_TR2M定时器*/
                pstSmrMtEntity->enState = IMSA_SMS_SMR_STATE_WAIT_TO_SND_RP_ACK;
                pstSmrMtEntity->ucMessageReference = (VOS_UINT8)pstOutSms->aucMessage[1];
                IMSA_StartTimer(&pstSmrMtEntity->stTimerInfo);

                /*短信数据发给MSG*/
                IMSA_SMS_SndMsgDataInd((VOS_UINT8*)pstOutSms->aucMessage,\
                                        pstOutSms->ucMessageLen);
                break;

            #if (FEATURE_ON == FEATURE_DSDS)
            case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:

                IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_MT_SMS,
                                              IMSA_RF_RES_APPLY_TRIGER_SRC_SMMA_RETRANS,
                                              VOS_FALSE,
                                              VOS_FALSE);

                /*MT短信，MT实体转状态，保存MR，启动TI_IMSA_SMS_TR2M定时器*/
                pstSmrMtEntity->enState = IMSA_SMS_SMR_STATE_WAIT_TO_SND_RP_ACK;
                pstSmrMtEntity->ucMessageReference = (VOS_UINT8)pstOutSms->aucMessage[1];
                IMSA_StartTimer(&pstSmrMtEntity->stTimerInfo);

                /*短信数据发给MSG*/
                IMSA_SMS_SndMsgDataInd((VOS_UINT8*)pstOutSms->aucMessage,\
                                        pstOutSms->ucMessageLen);
                break;

            case  IMSA_RESOURCE_STATUS_NULL:

                IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_MT_SMS,
                                              IMSA_RF_RES_APPLY_TRIGER_SRC_MT_SMS,
                                              VOS_FALSE,
                                              VOS_TRUE);

                IMSA_DsdsSaveMtSmsMsg(pstOutSms);
                break;
            #endif
            default:
                break;

        }
        break;

    /*MO RP ACK*/
    case IMSA_SMS_NTM_DATA_TYPE_RP_ACK:
        pstSmrMoEntity = IMSA_SMS_GetSmrMoEntityAddress();
        if(IMSA_SMS_SMR_STATE_WAIT_FOR_RP_ACK != pstSmrMoEntity->enState)
        {
            IMSA_WARN_LOG("IMSA_SMS_ProcNwSmsReceived: Mo entity is not WAIT_FOR_RP_ACK!");
            TLPS_PRINT2LAYER_WARNING(IMSA_SMS_ProcNwSmsReceived_ENUM, 2);
            break;
        }

        if(pstOutSms->aucMessage[1] != pstSmrMoEntity->ucMessageReference)
        {
            IMSA_WARN_LOG("IMSA_SMS_ProcNwSmsReceived: MR is not equel.");
            TLPS_PRINT2LAYER_WARNING(IMSA_SMS_ProcNwSmsReceived_ENUM, 3);
            break;
        }

        /*MO实体状态进行空闲态，停止TI_IMSA_SMS_TR1M保护定时器*/
        pstSmrMoEntity->enState = IMSA_SMS_SMR_STATE_IDLE;
        IMSA_StopTimer(&pstSmrMoEntity->stTR1MTimer);

        if (IMSA_SMS_TRUE == pstSmrMoEntity->ucMemAvailFlg)
        {                                                                   /* 此过程是mem avail过程                    */
            pstSmrMoEntity->ucMemAvailFlg = IMSA_SMS_FALSE;                       /* 清除mem avail标志                        */
            pstSmrMoEntity->ucRetransFlg  = IMSA_SMR_RETRANS_PERMIT;              /* 复位重发标志                             */
        }

        IMSA_SMS_SndMsgReportInd(SMR_SMT_ERROR_NO_ERROR,
                           (VOS_UINT8*)pstOutSms->aucMessage,\
                            pstOutSms->ucMessageLen);

        #if (FEATURE_ON == FEATURE_DSDS)
        if ((PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared()) &&
            (IMSA_TASKTYPE_STATUS_NULL != IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS)))
        {
            /* 如果延迟回复抢占定时器超时，应该直接回复CNF */
            IMSA_DsdsProcResourceOccupyCnf(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS);

            IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS);
        }
        #endif

        IMSA_CommonDeregProc();
        break;

    case IMSA_SMS_NTM_DATA_TYPE_RP_ERR:
        IMSA_SMS_ProcNwSmsRpError(pstOutSms);
        break;

    default:
        IMSA_WARN_LOG("IMSA_SMS_ProcNwReportReceived: Msg Type ERR.");
        TLPS_PRINT2LAYER_WARNING(IMSA_SMS_ProcNwSmsReceived_ENUM, LNAS_MSG_INVALID);
        break;
    }


}

/*****************************************************************************
 Function Name  : IMSA_D2ImsMsgSmsEvent()
 Description    : D2IMS短信类型的事件处理函数
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-21  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ImsMsgSmsEvent(VOS_VOID *pSmsEvent)
{
    IMSA_IMS_OUTPUT_SMS_EVENT_STRU       *pstOutSms;

    pstOutSms = (IMSA_IMS_OUTPUT_SMS_EVENT_STRU*)pSmsEvent;

    if(IMSA_IMS_OUTPUT_SMS_REASON_SMS_RECEIVED == pstOutSms->enOutputSmsReason)
    {
        IMSA_SMS_ProcNwSmsReceived(pstOutSms);
    }
    /*发送消息回复*/
    else if(IMSA_IMS_OUTPUT_SMS_REASON_OK == pstOutSms->enOutputSmsReason)
    {
        IMSA_INFO_LOG("IMSA_ImsMsgSmsEvent: Receive OK!");
        TLPS_PRINT2LAYER_INFO(IMSA_SMS_ProcNwSmsReceived_ENUM, 2);
    }
    /*错误处理*/
    else if(IMSA_IMS_OUTPUT_SMS_REASON_ERROR == pstOutSms->enOutputSmsReason)
    {
        IMSA_SMS_ProcNwSmsErr(pstOutSms);
    }
    else
    {
    }

}
#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 Function Name  : IMSA_SMSProcMoResourceApplyCnf
 Discription    : 申请MO SMS资源定时器超时的处理
 Input          :
 Output         : None
 Return         : None
 History:
      1. wangchen 00209181  2015-11-23  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SMSProcMtResourceApplyCnf
(
    const IMSA_IMS_OUTPUT_SMS_EVENT_STRU  *pstOutSms
)
{
    IMSA_SMS_SMR_MT_STRU                *pstSmrMtEntity;

    pstSmrMtEntity = IMSA_SMS_GetSmrMtEntityAddress();
    if(pstSmrMtEntity->enState != IMSA_SMS_SMR_STATE_IDLE)
    {
        IMSA_WARN_LOG("IMSA_SMS_ProcNwSmsReceived: Mt entity is not idle!");
        TLPS_PRINT2LAYER_WARNING(IMSA_SMS_ProcNwSmsReceived_ENUM, 1);
    }

    /*MT短信，MT实体转状态，保存MR，启动TI_IMSA_SMS_TR2M定时器*/
    pstSmrMtEntity->enState = IMSA_SMS_SMR_STATE_WAIT_TO_SND_RP_ACK;
    pstSmrMtEntity->ucMessageReference = (VOS_UINT8)pstOutSms->aucMessage[1];
    IMSA_StartTimer(&pstSmrMtEntity->stTimerInfo);

    /*短信数据发给MSG*/
    IMSA_SMS_SndMsgDataInd((VOS_UINT8*)pstOutSms->aucMessage,\
                            pstOutSms->ucMessageLen);

    return;
}
#endif


#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of ImsaProcImsSmsMsg.c */



