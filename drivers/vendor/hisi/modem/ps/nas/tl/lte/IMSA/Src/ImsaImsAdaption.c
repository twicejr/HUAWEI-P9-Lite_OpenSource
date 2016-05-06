/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : ImsaImsAdaption.c
  Description     : 该C文件实现IMS相关的适配功能，如字符转换等
  History           :
     1.sunbing 49683      2013-06-19  Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "ImsaImsAdaption.h"
#include "ImsaPublic.h"
#include "ImsaImsInterface.h"
#include "ImsaImsApi.h"
#include "VcImsaInterface.h"
#include "ImsaProcImsRegMsg.h"
#include "ImsCodecInterface.h"
#include "ImsaProcImsCallMsg.h"
#include "ImsaProcImsSmsMsg.h"
#include "ImsaImsInterface.h"
#include "MnClient.h"
#include "NasCommPrint.h"
#include "ImsaProcSpmMsg.h"

#include "ImsaProcImsUssdMsg.h"

#include "ImsaProcAtMsg.h"
#include "ImsaRegManagement.h"

#include "ImsaLrrcInterface.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_IMSAIMSADAPTION_C
#define    THIS_NAS_FILE_ID    NAS_FILE_ID_IMSAIMSADAPTION_C
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
HTIMER    aphTimer[IMSA_IMS_TIMER_NAME_BUTT] = {0};


extern VOS_VOID IMSA_ImsMsgDistr(const VOS_VOID *pRcvMsg );
extern VOS_VOID IMSA_SndVcStartHifiMsg(IMSA_VOICE_CODEC_ENUM_UINT16 enCodecType );
extern VOS_VOID IMSA_SndVcChangeHifiParaMsg(IMSA_VOICE_CODEC_ENUM_UINT16 enCodecType );
extern VOS_VOID IMSA_SndVcStopHifiMsg(VOS_VOID);
extern VOS_VOID IMSA_SndSpmOpenCodecChannel(IMSA_VOICE_CODEC_ENUM_UINT16 enCodecType);
extern VOS_VOID IMSA_SndSpmCloseCodecChannel(VOS_VOID);


/*****************************************************************************
  3 Function
*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
/*****************************************************************************
 Function Name  : IMSA_ImsaIntraMsgDistr()
 Description    : IMS消息分发函数，通过IMS消息的事件，判断分发给不同的内部模块处理
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-20  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ImsMsgDistr(const VOS_VOID *pRcvMsg )
{
    /* 定义消息头指针*/
    ImsaImsInterface_MSG          *pHeader = VOS_NULL_PTR;

    /* 获取消息头指针*/
    pHeader = (ImsaImsInterface_MSG *) pRcvMsg;

    /*根据事件类型*/
    switch(pHeader->stMsgData.ulMsgId)
    {
        case ID_IMS_IMSA_OUTPUT_SERVICE_MSG:
            IMSA_ImsMsgServiceEvent(&pHeader->stMsgData.aucMsg[0]);
            break;

        case ID_IMS_IMSA_OUTPUT_CALL_MSG:
            IMSA_ImsMsgCallEvent(&pHeader->stMsgData.aucMsg[0]);
            break;

        case ID_IMS_IMSA_OUTPUT_SMS_MSG:
            IMSA_ImsMsgSmsEvent(&pHeader->stMsgData.aucMsg[0]);
            break;

        case ID_IMS_IMSA_OUTPUT_SYSTEM_MSG:
            IMSA_ImsMsgSystemEvent(&pHeader->stMsgData.aucMsg[0]);
            break;

        case ID_IMS_IMSA_OUTPUT_PARA_MSG:
            IMSA_ImsMsgParaEvent(&pHeader->stMsgData.aucMsg[0]);
            break;

        case ID_IMS_IMSA_OUTPUT_USSD_MSG:
            IMSA_ImsMsgUssdEvent(&pHeader->stMsgData.aucMsg[0]);
            break;

        case ID_IMS_IMSA_OUTPUT_NV_INFO_MSG:
            IMSA_ImsMsgNvInfoEvent(&pHeader->stMsgData.aucMsg[0]);
            break;


        default:
            break;

    }
}

/*****************************************************************************
 Function Name  : IMSA_ProcHifiMsgTxDataInd()
 Description    : 获取来自HIFI的语音数据，调用IMS协议栈接口，把数据包发给IMS协议栈
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-12-16  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ProcHifiMsgTxDataInd
(
    const VOICE_IMSA_TX_DATA_IND_STRU  *pstTxDataInd
)
{
    IMSA_TX_VOICE_PARA_STRU             stTxPara = {0};

    IMSA_INFO_LOG("IMSA_ProcHifiMsgTxDataInd: enter!");
    TLPS_PRINT2LAYER_INFO(IMSA_ProcHifiMsgTxDataInd_ENUM, LNAS_ENTRY);

    stTxPara.usFrameType = pstTxDataInd->usFrameType;
    stTxPara.usStatus    = pstTxDataInd->usStatus;

    IMSA_Send2ImsTxVoiceData(&stTxPara,pstTxDataInd->ausData);
}

/*****************************************************************************
 Function Name  : IMSA_ProcHifiMsgRxDataAck()
 Description    : 处理HIFI回复ack的函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.zhaochen 00308719      2015-11-25  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ProcHifiMsgRxDataAck
(
    const VOICE_IMSA_RX_DATA_ACK_STRU  *pstRxDataAck
)
{
    VOS_UINT8                           i;
    IMSA_HIFI_DATA_BUFFER_NODE_STRU    *pstTempNode = VOS_NULL_PTR;

    /* 如果opid不匹配，则忽略此消息 */
    if (pstRxDataAck->ulOpid != IMSA_GetHifiDataOpid())
    {
        TLPS_PRINT2LAYER_ERROR(IMSA_ProcHifiMsgRxDataAck_ENUM, IMSA_OPID_NOT_MATCH);
        return;
    }

    /* 停止ack保护定时器 */
    IMSVA_StopTimer(&IMSA_GetHifiDataAckProtectTimer());

    /* 发包个数清0 */
    IMSA_GetHifiDataSentDataNum() = 0;

    /* 发送NV配置的条数的 缓存的消息 */
    for (i = 0 ; i < IMSA_GetHifiDataNeedAckNum() ; i ++)
    {
        /* 如果缓存队列没有消息，则直接返回 */
        if ((0 == IMSA_GetHifiDataBufferDataNum()) || (VOS_NULL_PTR == IMSA_GetHifiDataBufferDataHead()))
        {
            IMSA_GetHifiDataBufferDataNum() = 0;
            /* 释放链表 */
            while (VOS_NULL_PTR != IMSA_GetHifiDataBufferDataHead())
            {
                /* 释放节点 */
                pstTempNode = IMSA_GetHifiDataBufferDataHead()->pstNextBufferData;
#if(VOS_WIN32 == VOS_OS_VER)
                /*PC测试，需要调用MemFree来释放内存*/
                IMSA_MEM_FREE(IMSA_GetHifiDataBufferDataHead()->pstRxDataInd);
#else
                IMSA_FREE_MSG(IMSA_GetHifiDataBufferDataHead()->pstRxDataInd);
#endif
                IMSA_MEM_FREE(IMSA_GetHifiDataBufferDataHead());
                IMSA_GetHifiDataBufferDataHead() = pstTempNode;
            }
            IMSA_GetHifiDataBufferDataHead()     = VOS_NULL_PTR;
            IMSA_GetHifiDataBufferDataTail()     = VOS_NULL_PTR;
            return;
        }

        IMSA_GetHifiDataSentDataNum() ++;

        /* 如果缓存消息达到5条，则需要将回复标志置为TRUE */
        if(IMSA_GetHifiDataNeedAckNum() > IMSA_GetHifiDataSentDataNum())
        {
            IMSA_SendOneBufferData(VOS_FALSE);
        }
        else
        {
            IMSA_SendOneBufferData(VOS_TRUE);

            /* 启动ack保护定时器 */
            IMSVA_StartTimer(&IMSA_GetHifiDataAckProtectTimer());
        }
    }
    return;
}

/*****************************************************************************
 Function Name  : IMSVA_ProcHifiMsg()
 Description    : IMSVA处理HIFI的语音包处理函数
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-07-15  Draft Enact
      2.lihong 00150010    2013-12-16  Modify:JitterBuffer移到HIFI
*****************************************************************************/
VOS_VOID IMSVA_ProcHifiMsg(const VOS_VOID *pRcvMsg )
{
    /* 定义消息头指针*/
    PS_MSG_HEADER_STRU          *pHeader = VOS_NULL_PTR;

    /* 获取消息头指针*/
    pHeader = (PS_MSG_HEADER_STRU *) pRcvMsg;

    switch(pHeader->ulMsgName)
    {
        case ID_VOICE_IMSA_TX_DATA_IND:
            IMSA_ProcHifiMsgTxDataInd((VOICE_IMSA_TX_DATA_IND_STRU*)pRcvMsg);
            break;

        default:

            /*打印异常信息*/
            IMSA_WARN_LOG("IMSVA_ProcHifiMsg:Msg Id is err!");
            TLPS_PRINT2LAYER_WARNING(IMSVA_ProcHifiMsg_ENUM, LNAS_MSG_INVALID);
            break;
    }
}

/*****************************************************************************
 Function Name  : IMSVA_ProcHifiRtMsg()
 Description    : IMSVA处理VOICE_RT发送的消息的处理函数
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.zhaochen 00308719      2015-11-25  Draft Enact
*****************************************************************************/
VOS_VOID IMSVA_ProcHifiRtMsg(const VOS_VOID *pRcvMsg )
{
    /* 定义消息头指针*/
    PS_MSG_HEADER_STRU          *pHeader = VOS_NULL_PTR;
    VOS_INT32                    intLockLevel;

    /* 获取消息头指针*/
    pHeader = (PS_MSG_HEADER_STRU *) pRcvMsg;

    switch(pHeader->ulMsgName)
    {
        case ID_VOICE_IMSA_CFG_CNF:

            IMSA_INFO_LOG1("IMSA_VOICE_CFG_CNF,result=",((VOICE_IMSA_CFG_CNF_STRU*)pRcvMsg)->ulResult);
            TLPS_PRINT2LAYER_INFO1(IMSVA_ProcHifiMsg_ENUM, 1, ((VOICE_IMSA_CFG_CNF_STRU*)pRcvMsg)->ulResult);
            break;

        case ID_VOICE_IMSA_RX_DATA_ACK:

            /* 任务加锁 */
            intLockLevel = VOS_SplIMP();

            IMSA_ProcHifiMsgRxDataAck((VOICE_IMSA_RX_DATA_ACK_STRU*)pRcvMsg);

            /* 任务解锁 */
            VOS_Splx(intLockLevel);
            break;

        default:

            /*打印异常信息*/
            IMSA_WARN_LOG("IMSVA_ProcHifiMsg:Msg Id is err!");
            TLPS_PRINT2LAYER_WARNING(IMSVA_ProcHifiMsg_ENUM, LNAS_MSG_INVALID);
            break;
    }
}

/*****************************************************************************
 Function Name  : IMSVA_TimerMsgDistr()
 Description    : TIMER消息分发函数
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.zhaochen 00308719      2015-11-13  Draft Enact
*****************************************************************************/
VOS_VOID IMSVA_TimerMsgDistr(const REL_TIMER_MSG *pRcvMsg )
{
    IMSA_TIMER_ID_ENUM_UINT16           enTimerName;

    enTimerName = (VOS_UINT16)PS_GET_REL_TIMER_NAME(pRcvMsg);

    /* 目前只处理HIFI回复 */
    if ( TI_IMSA_HIFI_ACK_PROTECT == enTimerName )
    {
        IMSA_ProcTimerMsgHifiAckProtect(pRcvMsg);
    }

    else
    {
        /*lint -e961*/
        IMSA_ERR_LOG1("IMSVA_TimerMsgDistr: Unexpected event received! <enTimerName>",
            enTimerName);
        /*lint +e961*/

    }

    return;

}


/*****************************************************************************
 Function Name  : IMSA_Snd2ImsaCallMsg()
 Description    : 给IMSA发送call消息
 Input          : pstHicsmOutputCall
 Output         : VOS_VOID
 Return Value   : unsigned int 返回结果 0成功，1失败

 History        :
      1.sunbing 49683      2013-07-16  Draft Enact
      2.lihong 00150010    2013-10-09  Modify
*****************************************************************************/
VOS_VOID IMSA_Snd2ImsaCallMsg
(
    const IMSA_IMS_OUTPUT_CALL_EVENT_STRU      *pstOutputCallEvent
)
{
    IMS_IMSA_OUTPUT_CALL_MSG_STRU      *pstMsgOutputCall = VOS_NULL_PTR;

    /*分配空间并检验分配是否成功*/
    pstMsgOutputCall = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMS_IMSA_OUTPUT_CALL_MSG_STRU));

    if ( VOS_NULL_PTR == pstMsgOutputCall )
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_Snd2ImsaCallMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_Snd2ImsaCallMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstMsgOutputCall),
                    IMSA_GET_MSG_LENGTH(pstMsgOutputCall),
                    0,
                    IMSA_GET_MSG_LENGTH(pstMsgOutputCall));

    /*填写消息头*/
    IMSA_WRITE_IMSA_MSG_HEAD(pstMsgOutputCall,ID_IMS_IMSA_OUTPUT_CALL_MSG);

    IMSA_MEM_CPY_S( &pstMsgOutputCall->stOutputCall,
                    sizeof(IMSA_IMS_OUTPUT_CALL_EVENT_STRU),
                    pstOutputCallEvent,
                    sizeof(IMSA_IMS_OUTPUT_CALL_EVENT_STRU));

    IMSA_SND_MSG(pstMsgOutputCall);
}

/*****************************************************************************
 Function Name  : IMSA_Snd2ImsaSmsMsg()
 Description    : 给IMSA发送SMS消息
 Input          : pstHicsmOutputSms
 Output         : VOS_VOID
 Return Value   : unsigned int 返回结果 0成功，1失败

 History        :
      1.sunbing 49683      2013-07-16  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_Snd2ImsaSmsMsg(const IMSA_IMS_OUTPUT_SMS_EVENT_STRU *pstImsaImsOutputSms)
{
    IMS_IMSA_OUTPUT_SMS_MSG_STRU                *pstMsgOutputSms;

    /*分配空间并检验分配是否成功*/
    pstMsgOutputSms = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMS_IMSA_OUTPUT_SMS_MSG_STRU));

    if ( VOS_NULL_PTR == pstMsgOutputSms )
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_Snd2ImsaSmsMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_Snd2ImsaSmsMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstMsgOutputSms),
                    IMSA_GET_MSG_LENGTH(pstMsgOutputSms),
                    0,
                    IMSA_GET_MSG_LENGTH(pstMsgOutputSms));

    /*填写消息头*/
    IMSA_WRITE_IMSA_MSG_HEAD(pstMsgOutputSms,ID_IMS_IMSA_OUTPUT_SMS_MSG);

    IMSA_MEM_CPY_S( &pstMsgOutputSms->stOutputSms,
                    sizeof(IMSA_IMS_OUTPUT_SMS_EVENT_STRU),
                    pstImsaImsOutputSms,
                    sizeof(IMSA_IMS_OUTPUT_SMS_EVENT_STRU));

    IMSA_SND_MSG(pstMsgOutputSms);

}

/*****************************************************************************
 Function Name  : IMSA_Snd2ImsaServiceMsg()
 Description    : 给IMSA发送SERVCIE消息
 Input          : pstHicsmOutputService
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-07-16  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_Snd2ImsaServiceMsg(const IMSA_IMS_OUTPUT_SERVICE_EVENT_STRU *pstOutputService)
{
    IMS_IMSA_OUTPUT_SERVICE_MSG_STRU      *pstMsgOutputService;

    /*分配空间并检验分配是否成功*/
    pstMsgOutputService = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMS_IMSA_OUTPUT_SERVICE_MSG_STRU));

    if ( VOS_NULL_PTR == pstMsgOutputService )
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_Snd2ImsaServiceMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_Snd2ImsaServiceMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstMsgOutputService),
                    IMSA_GET_MSG_LENGTH(pstMsgOutputService),
                    0,
                    IMSA_GET_MSG_LENGTH(pstMsgOutputService));

    /*填写消息头*/
    IMSA_WRITE_IMSA_MSG_HEAD(pstMsgOutputService,ID_IMS_IMSA_OUTPUT_SERVICE_MSG);

    IMSA_MEM_CPY_S( &pstMsgOutputService->stOutputService,
                    sizeof(IMSA_IMS_OUTPUT_SERVICE_EVENT_STRU),
                    pstOutputService,
                    sizeof(IMSA_IMS_OUTPUT_SERVICE_EVENT_STRU));

    IMSA_SND_MSG(pstMsgOutputService);

}

/*****************************************************************************
 Function Name  : IMSA_Snd2ImsaParaMsg()
 Description    : 给IMSA发送PARA消息
 Input          : pstHicsmOutputService
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2013-10-11   Draft Enact
*****************************************************************************/
VOS_VOID IMSA_Snd2ImsaParaMsg(const IMSA_IMS_OUTPUT_PARA_EVENT_STRU *pstOutputService)
{
    IMS_IMSA_OUTPUT_PARA_MSG_STRU      *pstMsgOutputPara;

    /*分配空间并检验分配是否成功*/
    pstMsgOutputPara = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMS_IMSA_OUTPUT_PARA_MSG_STRU));

    if ( VOS_NULL_PTR == pstMsgOutputPara )
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_Snd2ImsaParaMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_Snd2ImsaParaMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstMsgOutputPara),
                    IMSA_GET_MSG_LENGTH(pstMsgOutputPara),
                    0,
                    IMSA_GET_MSG_LENGTH(pstMsgOutputPara));

    /*填写消息头*/
    IMSA_WRITE_IMSA_MSG_HEAD(pstMsgOutputPara,ID_IMS_IMSA_OUTPUT_PARA_MSG);

    IMSA_MEM_CPY_S( &pstMsgOutputPara->stOutputPara,
                    sizeof(IMSA_IMS_OUTPUT_PARA_EVENT_STRU),
                    pstOutputService,
                    sizeof(IMSA_IMS_OUTPUT_PARA_EVENT_STRU));

    IMSA_SND_MSG(pstMsgOutputPara);

}

/*****************************************************************************
 Function Name  : IMSA_Snd2ImsaSystemMsg()
 Description    : 给IMSA发送PARA消息
 Input          : pstHicsmOutputService
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2013-10-11   Draft Enact
*****************************************************************************/
VOS_VOID IMSA_Snd2ImsaSystemMsg(const IMSA_IMS_OUTPUT_SYSTEM_EVENT_STRU *pstOutputSystem)
{
    IMS_IMSA_OUTPUT_SYSTEM_MSG_STRU      *pstMsgOutputSystem;

    /*分配空间并检验分配是否成功*/
    pstMsgOutputSystem = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMS_IMSA_OUTPUT_SYSTEM_MSG_STRU));

    if ( VOS_NULL_PTR == pstMsgOutputSystem )
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_Snd2ImsaSystemMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_Snd2ImsaSystemMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstMsgOutputSystem),
                    IMSA_GET_MSG_LENGTH(pstMsgOutputSystem),
                    0,
                    IMSA_GET_MSG_LENGTH(pstMsgOutputSystem));

    /*填写消息头*/
    IMSA_WRITE_IMSA_MSG_HEAD(pstMsgOutputSystem,ID_IMS_IMSA_OUTPUT_SYSTEM_MSG);

    IMSA_MEM_CPY_S( &pstMsgOutputSystem->stOutputSystem,
                    sizeof(IMSA_IMS_OUTPUT_SYSTEM_EVENT_STRU),
                    pstOutputSystem,
                    sizeof(IMSA_IMS_OUTPUT_SYSTEM_EVENT_STRU));

    IMSA_SND_MSG(pstMsgOutputSystem);

}




/*****************************************************************************
 Function Name  : IMSA_Send2ImsaMsg()
 Description    : 实现IMS给IMSA发送消息功能，该函数提供给IMS使用
 Input          : VOS_UINT8  *pstOutEvent
 Output         : VOS_VOID
 Return Value   : unsigned int 返回结果 0成功，1失败

 History        :
      1.sunbing 49683      2013-06-25  Draft Enact
      2.wangchen 00209181  2013-10-11  Modify
*****************************************************************************/
unsigned int IMSA_Send2ImsaMsg(void *pstOutputEvent)
{
    IMSA_IMS_OUTPUT_EVENT_STRU  *pstImsaImsOutputEvent = pstOutputEvent;

    if( VOS_NULL_PTR == pstImsaImsOutputEvent)
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_Send2ImsaMsg:ERROR:Para is null!");
        TLPS_PRINT2LAYER_ERROR(IMSA_Send2ImsaMsg_ENUM, LNAS_NULL_PTR);
        return VOS_ERR;
    }

    switch(pstImsaImsOutputEvent->enEventType)
    {
        case IMSA_IMS_EVENT_TYPE_CALL:
            IMSA_Snd2ImsaCallMsg(&pstImsaImsOutputEvent->evt.stOutputCallEvent);
            break;
        case IMSA_IMS_EVENT_TYPE_SMS:
            IMSA_Snd2ImsaSmsMsg(&pstImsaImsOutputEvent->evt.stOutputSmsEvent);
            break;
        case IMSA_IMS_EVENT_TYPE_SERVICE:
            IMSA_Snd2ImsaServiceMsg(&pstImsaImsOutputEvent->evt.stOutputServiceEvent);
            break;

        case IMSA_IMS_EVENT_TYPE_PARA:
            IMSA_Snd2ImsaParaMsg(&pstImsaImsOutputEvent->evt.stOutputParaEvent);
            break;
        case IMSA_IMS_EVENT_TYPE_SYSTEM:
            IMSA_Snd2ImsaSystemMsg(&pstImsaImsOutputEvent->evt.stOutputSystemEvent);
            break;
        default:
            IMSA_WARN_LOG("IMSA_Snd2ImsaMsg:Type is err!");
            TLPS_PRINT2LAYER_ERROR(IMSA_Send2ImsaMsg_ENUM, LNAS_MSG_INVALID);
            break;
    }

    return VOS_OK;

}

/*****************************************************************************
 Function Name  : IMSA_SndHifiCfgReq()
 Description    : 给HIFI发配置参数请求，目前只会配置HIFI上行的交互周期
 Input          : ulTransTime 交互周期
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-12-16  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SndHifiCfgReq( unsigned long ulTransTime, unsigned long ulSendBitrate )
{
    IMSA_VOICE_CFG_REQ_STRU                 *pstImsaCfgReq = VOS_NULL_PTR;

    /*分配空间并检验分配是否成功*/
    pstImsaCfgReq = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_VOICE_CFG_REQ_STRU));

    if ( VOS_NULL_PTR == pstImsaCfgReq )
    {
       /*打印异常信息*/
       IMSA_ERR_LOG("IMSA_SndHifiCfgReq:ERROR:Alloc Msg fail!");
       TLPS_PRINT2LAYER_ERROR(IMSA_SndHifiCfgReq_ENUM, LNAS_NULL_PTR);
       return ;
    }

    pstImsaCfgReq->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstImsaCfgReq->ulSenderPid      = PS_PID_IMSVA;

    /*CPU ID无需要填写。OSA会根据目的pid得出CPU ID，再根据CPU ID，将消息发送到对应的CPU上*/
    pstImsaCfgReq->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstImsaCfgReq->ulReceiverPid    = DSP_PID_VOICE;

    pstImsaCfgReq->usMsgId          = ID_IMSA_VOICE_CFG_REQ;

    pstImsaCfgReq->ulTransTime      = ulTransTime;

    pstImsaCfgReq->ulSendBitrate    = ulSendBitrate;

    /* 调用消息发送函数 */
    IMSA_SND_MSG(pstImsaCfgReq);
}


/*****************************************************************************
 Function Name  : IMSA_SndVcStartHifiMsg()
 Description    : 给VC发送启动HIFI消息
 Input          : enCodecType
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-07-15  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SndVcStartHifiMsg(IMSA_VOICE_CODEC_ENUM_UINT16 enCodecType )
{
    IMSA_VC_START_HIFI_NTF_STRU         *pstStartHifiNtf;

    /*分配空间并检验分配是否成功*/
    pstStartHifiNtf = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_VC_START_HIFI_NTF_STRU));

    if ( VOS_NULL_PTR == pstStartHifiNtf )
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_SndVcStartHifiMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndVcStartHifiMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*填写消息头*/
    IMSA_WRITE_VC_MSG_HEAD(pstStartHifiNtf,ID_IMSA_VC_START_HIFI_NTF);

    pstStartHifiNtf->enMode = IMSA_VC_MODE_EUTRAN_IMS;

    switch(enCodecType)
    {
        case IMSA_VOICE_CODEC_AMR_NB:
        case IMSA_VOICE_CODEC_AMR_NB2:
            pstStartHifiNtf->enCodeType = IMSA_VC_CODEC_TYPE_AMR;
            break;

        case IMSA_VOICE_CODEC_AMR_WB:
            pstStartHifiNtf->enCodeType = IMSA_VC_CODEC_TYPE_AMRWB;
            break;

        case IMSA_VOICE_CODEC_G711:
            pstStartHifiNtf->enCodeType = IMSA_VC_CODEC_TYPE_G711;
            break;

        default:
            IMSA_WARN_LOG("IMSA_SndVcStartHifiMsg:codec type is err!");
            TLPS_PRINT2LAYER_ERROR(IMSA_SndVcStartHifiMsg_ENUM, LNAS_PARAM_INVALID);
            pstStartHifiNtf->enCodeType = IMSA_VC_CODEC_TYPE_AMR;
            break;
    }

    /* 调用消息发送函数 */
    IMSA_SND_MSG(pstStartHifiNtf);

}

/*****************************************************************************
 Function Name  : IMSA_SndVcChangeHifiParaMsg()
 Description    : 给VC发送codec变更消息
 Input          : enCodecType
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-07-15  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SndVcChangeHifiParaMsg(IMSA_VOICE_CODEC_ENUM_UINT16 enCodecType )
{
    IMSA_VC_HIFI_PARA_CHANGED_NTF_STRU  *pstHifiParaChangeNtf;

    /*分配空间并检验分配是否成功*/
    pstHifiParaChangeNtf = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_VC_HIFI_PARA_CHANGED_NTF_STRU));

    if ( VOS_NULL_PTR == pstHifiParaChangeNtf )
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_SndVcChangeHifiParaMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndVcChangeHifiParaMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*填写消息头*/
    IMSA_WRITE_VC_MSG_HEAD(pstHifiParaChangeNtf,ID_IMSA_VC_HIFI_PARA_CHANGED_NTF);

    pstHifiParaChangeNtf->enMode = IMSA_VC_MODE_EUTRAN_IMS;

    switch(enCodecType)
    {
        case IMSA_VOICE_CODEC_AMR_NB:
        case IMSA_VOICE_CODEC_AMR_NB2:
            pstHifiParaChangeNtf->enCodeType = IMSA_VC_CODEC_TYPE_AMR;
            break;

        case IMSA_VOICE_CODEC_AMR_WB:
            pstHifiParaChangeNtf->enCodeType = IMSA_VC_CODEC_TYPE_AMRWB;
            break;

        case IMSA_VOICE_CODEC_G711:
            pstHifiParaChangeNtf->enCodeType = IMSA_VC_CODEC_TYPE_G711;
            break;

        default:
            IMSA_WARN_LOG("IMSA_SndVcChangeHifiParaMsg:codec type is err!");
            TLPS_PRINT2LAYER_WARNING(IMSA_SndVcChangeHifiParaMsg_ENUM, LNAS_PARAM_INVALID);
            pstHifiParaChangeNtf->enCodeType = IMSA_VC_CODEC_TYPE_AMR;
            break;
    }

    /* 调用消息发送函数 */
    IMSA_SND_MSG(pstHifiParaChangeNtf);

}

/*****************************************************************************
 Function Name  : IMSA_SndVcStopHifiMsg()
 Description    : 给VC发送停止HIFI消息
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-08-16  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SndVcStopHifiMsg(VOS_VOID)
{
    IMSA_VC_STOP_HIFI_NTF_STRU          *pstStopHifiNtf;

    /*分配空间并检验分配是否成功*/
    pstStopHifiNtf = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_VC_STOP_HIFI_NTF_STRU));

    if ( VOS_NULL_PTR == pstStopHifiNtf )
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_SndVcStopHifiMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndVcStopHifiMsg_ENUM, LNAS_NULL_PTR);
        return;
    }

    /*填写消息头*/
    IMSA_WRITE_VC_MSG_HEAD(pstStopHifiNtf,ID_IMSA_VC_STOP_HIFI_NTF);

    /* 调用消息发送函数 */
    IMSA_SND_MSG(pstStopHifiNtf);
}


/*****************************************************************************
 Function Name  : IMSA_SndSpmOpenCodecChannel
 Description    : IMSA给SPM发送打开通道的信息
 Input          : enCodecType     编码类型
 Output         : VOS_VOID
 Return Value   : 发送结果

 History        :
      1.sunbing 49683      2013-08-16  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SndSpmOpenCodecChannel(IMSA_VOICE_CODEC_ENUM_UINT16 enCodecType)
{
    IMSA_SPM_CHANNEL_INFO_IND_STRU *pstSpmChannelInfoMsg = VOS_NULL_PTR;

    /* 分配空间并检验分配是否成功 */
    pstSpmChannelInfoMsg = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_SPM_CHANNEL_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstSpmChannelInfoMsg)
    {
        IMSA_ERR_LOG("IMSA_SndSpmOpenCodecChannel: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndSpmOpenCodecChannel_ENUM, LNAS_NULL_PTR);
        return;
    }

    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstSpmChannelInfoMsg),
                    IMSA_GET_MSG_LENGTH(pstSpmChannelInfoMsg),
                    0,
                    IMSA_GET_MSG_LENGTH(pstSpmChannelInfoMsg));

    /* 填写消息头 */
    IMSA_WRITE_SPM_MSG_HEAD(pstSpmChannelInfoMsg, ID_IMSA_SPM_CHANNEL_INFO_IND);

    /* 设置Client Id */
    pstSpmChannelInfoMsg->usClientId                          = MN_CLIENT_ID_BROADCAST;

    pstSpmChannelInfoMsg->ucIsLocalAlertingFlag               = VOS_FALSE;

    switch(enCodecType)
    {
        case IMSA_VOICE_CODEC_AMR_NB:
            pstSpmChannelInfoMsg->enCodecType = MN_CALL_CODEC_TYPE_AMR;
            break;
        case IMSA_VOICE_CODEC_EFR:
            pstSpmChannelInfoMsg->enCodecType = MN_CALL_CODEC_TYPE_EFR;
            break;
        case IMSA_VOICE_CODEC_FR:
            pstSpmChannelInfoMsg->enCodecType = MN_CALL_CODEC_TYPE_FR;
            break;
        case IMSA_VOICE_CODEC_HR:
            pstSpmChannelInfoMsg->enCodecType = MN_CALL_CODEC_TYPE_HR;
            break;
        case IMSA_VOICE_CODEC_AMR_NB2:
            pstSpmChannelInfoMsg->enCodecType = MN_CALL_CODEC_TYPE_AMR2;
            break;
        case IMSA_VOICE_CODEC_AMR_WB:
            pstSpmChannelInfoMsg->enCodecType = MN_CALL_CODEC_TYPE_AMRWB;
            break;
        case IMSA_VOICE_CODEC_G711:
            pstSpmChannelInfoMsg->enCodecType = IMSA_VOICE_CODEC_G711;
            break;
        default:
            IMSA_WARN_LOG("IMSA_SndSpmOpenCodecChannel:codec type is err!");
            TLPS_PRINT2LAYER_WARNING(IMSA_SndSpmOpenCodecChannel_ENUM, LNAS_PARAM_INVALID);
            pstSpmChannelInfoMsg->enCodecType = MN_CALL_CODEC_TYPE_AMR;
            break;

    }

    /* lihong00150010 降全复杂度 2014-04-21 begin */
    /*pstSpmChannelInfoMsg->enChannelEvent                      = MN_CALL_EVT_CHANNEL_OPEN;
    pstSpmChannelInfoMsg->stChannelInfo.bChannelEnable        = VOS_TRUE;
    pstSpmChannelInfoMsg->stChannelInfo.stChannelParam.enMode = MN_CALL_RADIO_MODE_IMS_EUTRAN;

    switch(enCodecType)
    {
        case IMSA_VOICE_CODEC_AMR_NB:
            pstSpmChannelInfoMsg->stChannelInfo.stChannelParam.enCodecType = MN_CALL_CODEC_TYPE_AMR;
            break;

        case IMSA_VOICE_CODEC_EFR:
            pstSpmChannelInfoMsg->stChannelInfo.stChannelParam.enCodecType = MN_CALL_CODEC_TYPE_EFR;
            break;

        case IMSA_VOICE_CODEC_FR:
            pstSpmChannelInfoMsg->stChannelInfo.stChannelParam.enCodecType = MN_CALL_CODEC_TYPE_FR;
            break;

        case IMSA_VOICE_CODEC_HR:
            pstSpmChannelInfoMsg->stChannelInfo.stChannelParam.enCodecType = MN_CALL_CODEC_TYPE_HR;
            break;

        case IMSA_VOICE_CODEC_AMR_NB2:
            pstSpmChannelInfoMsg->stChannelInfo.stChannelParam.enCodecType = MN_CALL_CODEC_TYPE_AMR2;
            break;

        case IMSA_VOICE_CODEC_AMR_WB:
            pstSpmChannelInfoMsg->stChannelInfo.stChannelParam.enCodecType = MN_CALL_CODEC_TYPE_AMRWB;
            break;

        case IMSA_VOICE_CODEC_G711:
            pstSpmChannelInfoMsg->stChannelInfo.stChannelParam.enCodecType = MN_CALL_CODEC_TYPE_G711;
            break;

        default:
            IMSA_WARN_LOG("IMSA_SndSpmOpenCodecChannel:codec type is err!");
            pstSpmChannelInfoMsg->stChannelInfo.stChannelParam.enCodecType = IMSA_VC_CODEC_TYPE_AMR;
            break;
    }*/
    /* lihong00150010 降全复杂度 2014-04-21 end */

    /* 调用消息发送函数 */
    IMSA_SND_MSG(pstSpmChannelInfoMsg);
}

/*****************************************************************************
 Function Name  : IMSA_SndSpmCloseCodecChannel
 Description    : IMSA给SPM发送关闭通道的信息
 Input          : enCodecType     编码类型
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-08-16  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SndSpmCloseCodecChannel(VOS_VOID)
{

}

/*****************************************************************************
 Function Name  : IMSA_SndLRrcHifiSyncSwtichInd()
 Description    : 给LRRC发送HIFI同步开关指示消息
 Input          : enCodecType
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2014-11-17  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SndLRrcHifiSyncSwtichInd
(
    VOS_UINT8                           ucHifiSyncEnalbed
)
{
    IMSA_LRRC_HIFI_SYNC_SWITCH_IND_STRU    *pstRrcHifiSyncSwtichInd = VOS_NULL_PTR;

    /* 申请DOPRA消息 */
    pstRrcHifiSyncSwtichInd = (VOS_VOID *) IMSA_ALLOC_MSG(sizeof(IMSA_LRRC_HIFI_SYNC_SWITCH_IND_STRU));
    if(VOS_NULL_PTR == pstRrcHifiSyncSwtichInd)
    {
        /* 打印异常，ERROR_LEVEL */
        IMSA_INFO_LOG("IMSA_SndLRrcHifiSyncSwtichInd: MSG ALLOC ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndLRrcHifiSyncSwtichInd_ENUM, LNAS_NULL_PTR);
        return;
    }

    IMSA_INFO_LOG2("IMSA_SndLRrcHifiSyncSwtichInd: ucHifiSyncEnalbed = , ucPowerState = ",
                   ucHifiSyncEnalbed, IMSA_GetPowerState());
    TLPS_PRINT2LAYER_INFO2(IMSA_SndLRrcHifiSyncSwtichInd_ENUM, 1, ucHifiSyncEnalbed, IMSA_GetPowerState());

    /* 设置为0 */
    IMSA_MEM_SET_S( pstRrcHifiSyncSwtichInd,
                    sizeof(IMSA_LRRC_HIFI_SYNC_SWITCH_IND_STRU),
                    0,
                    sizeof(IMSA_LRRC_HIFI_SYNC_SWITCH_IND_STRU));

    /*填写消息头*/
    IMSA_WRITE_LRRC_MSG_HEAD(pstRrcHifiSyncSwtichInd,ID_IMSA_LRRC_HIFI_SYNC_SWITCH_IND,
                             sizeof(IMSA_LRRC_HIFI_SYNC_SWITCH_IND_STRU));

    /* 填充消息体 */
    pstRrcHifiSyncSwtichInd->ucHifiSyncEnabled  = ucHifiSyncEnalbed;
    pstRrcHifiSyncSwtichInd->ucPowerState = IMSA_GetPowerState();

    /* 发送DOPRA消息 */
    IMSA_SND_MSG(pstRrcHifiSyncSwtichInd);

    return;
}

/*****************************************************************************
 函 数 名  : IMSA_SndHifiDataInfo
 功能描述  : 将IMSA的控制的HIFI消息的丢包和缓存情况 信息勾到HIDS
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月13日
    作    者   : z00308719
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IMSA_SndHifiDataInfo(VOS_VOID)
{
    IMSA_HIFI_DATA_INFO_IND_STRU       *pstMsg = VOS_NULL_PTR;

    IMSA_NORM_LOG("IMSA_SndHifiDataInfo:ENTER.");
    TLPS_PRINT2LAYER_INFO(IMSA_SndRegErrLogInfo_ENUM, LNAS_ENTRY);

    pstMsg = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_HIFI_DATA_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        IMSA_ERR_LOG("IMSA_SndHifiDataInfo:ERROR:Alloc Mem Fail.");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndRegErrLogInfo_ENUM, LNAS_NULL_PTR);
        return;
    }

    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstMsg),
                    IMSA_GET_MSG_LENGTH(pstMsg),
                    0,
                    IMSA_GET_MSG_LENGTH(pstMsg));

    /*填写消息头*/
    IMSA_WRITE_INTRA_MSG_HEAD(  pstMsg,
                                ID_IMSA_HIFI_DATA_INFO_IND,
                                sizeof(IMSA_HIFI_DATA_INFO_IND_STRU));

    pstMsg->ulDataLoseNum        = IMSA_GetHifiDataDataLoseNum();
    pstMsg->ulTotalDataLoseNum   = IMSA_GetHifiDataTotalDataLoseNum();
    pstMsg->ulDataBufferNum      = IMSA_GetHifiDataDataBufferNum();
    pstMsg->ulTotalDataBufferNum = IMSA_GetHifiDataTotalDataBufferNum();

#if(VOS_WIN32 == VOS_OS_VER)
    /*PC测试，将消息发送出去，用于ST验证*/
    IMSA_SND_MSG(pstMsg);

#else
    /*消息勾到HSO上*/
    (VOS_VOID)LTE_MsgHook(pstMsg);

    /*释放消息空间*/
    IMSA_FREE_MSG(pstMsg);

#endif

    return;
}

/*****************************************************************************
 Function Name  : IMSA_StartVoiceDsp()
 Description    : 海思提供给D2 tech的API，用于D2 IMS协议栈打电话启动HIFI或者语音编码格式改变时调用，
                  在该API中，IMSA会通知HIFI启动编解码，并且设置codec类型
 Input          : enCodecType
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-07-15  Draft Enact
      2.lihong 00150010    2013-12-16  Modify:JitterBuffer移到HIFI
      3.zhaochen 00308719  2015-11-10  Modify:规避HIFI邮箱满复位
*****************************************************************************/
unsigned int IMSA_StartVoiceDsp
(
    IMSA_VOICE_CODEC_ENUM_UINT16    enCodecType,
    unsigned long                   ulPacketTime,
    unsigned long                   ulSendBitrate
)
{
    VOS_INT32                           intLockLevel;

    IMSA_INFO_LOG("IMSA_StartVoiceDsp:the function is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_StartVoiceDsp_ENUM, LNAS_ENTRY);

    /* 任务加锁 */
    intLockLevel = VOS_SplIMP();

    /*清除本地的缓存*/
    IMSA_ClearHifiData();

    /* 停止ack保护定时器 */
    IMSVA_StopTimer(&IMSA_GetHifiDataAckProtectTimer());

    /* 任务解锁 */
    VOS_Splx(intLockLevel);

    /*通知VC，启动HIFI*/
    IMSA_SndVcStartHifiMsg(enCodecType);

    /*通知VC，codec变更*/
    IMSA_SndVcChangeHifiParaMsg(enCodecType);

    /*通知SPM，打开模拟codec*/
    IMSA_SndSpmOpenCodecChannel(enCodecType);

    /*清除本地振铃信息*/
    IMSA_CallClearLocalAlertInfo();

    /* 通知HIFI，配置交互周期 */
    IMSA_SndHifiCfgReq(ulPacketTime, ulSendBitrate);

    IMSA_SndLRrcHifiSyncSwtichInd(IMSA_TRUE);

    return VOS_OK;
}

/*****************************************************************************
 Function Name  : IMSA_StopVoiceDsp()
 Description    : 海思提供给D2 tech的API，用于D2 IMS协议栈在挂断所有电话后调用
                  在该API中，IMSA会通知HIFI,停止语音编解码
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-07-15  Draft Enact
*****************************************************************************/
unsigned int IMSA_StopVoiceDsp(void)
{
    VOS_INT32                                    intLockLevel;
    IMSA_INFO_LOG("IMSA_StopVoiceDsp:the function is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_StopVoiceDsp_ENUM, LNAS_ENTRY);

    /* 可维可测 */
    IMSA_SndHifiDataInfo();

    /* 任务加锁 */
    intLockLevel = VOS_SplIMP();

    /*清除本地的缓存*/
    IMSA_ClearHifiData();

    /* 停止ack保护定时器 */
    IMSVA_StopTimer(&IMSA_GetHifiDataAckProtectTimer());

    /* 任务解锁 */
    VOS_Splx(intLockLevel);

    /*通知VC，停止HIFI*/
    IMSA_SndVcStopHifiMsg();

    /*停止codec通道*/
    /* IMSA_SndSpmCloseCodecChannel(); */

    IMSA_SndLRrcHifiSyncSwtichInd(IMSA_FALSE);

    return VOS_OK;
}

/*****************************************************************************
 Function Name  : IMSA_Send2HifiRxVoiceData()
 Description    : D2IMS协议栈调用，用于将下行语音数据发送给HIFI，HIFI收到后进行译码
 Input          : usLength 标示语音数据长度，pcData数据存放地址(内存由调用者释放)
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-07-15  Draft Enact
*****************************************************************************/
unsigned int IMSA_Send2HifiRxVoiceData(const IMSA_RX_VOICE_PARA_STRU *pstVoicePara,
                                               const unsigned short *pusData)
{
    IMSA_VOICE_RX_DATA_IND_STRU                 *pstRxDataInd;
    VOS_INT32                                    intLockLevel;

    if((VOS_NULL_PTR == pstVoicePara)
        ||(VOS_NULL_PTR == pusData))
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_Send2HifiRxVoiceData:ERROR Input Para!");
        TLPS_PRINT2LAYER_ERROR(IMSA_Send2HifiRxVoiceData_ENUM, LNAS_PARAM_INVALID);
        return VOS_ERR;
    }


    /*分配空间并检验分配是否成功*/
    pstRxDataInd = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_VOICE_RX_DATA_IND_STRU));

    if ( VOS_NULL_PTR == pstRxDataInd )
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_Send2HifiRxVoiceData:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_Send2HifiRxVoiceData_ENUM, LNAS_NULL_PTR);
        return VOS_ERR;
    }

    /* 组装消息 */
    pstRxDataInd->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstRxDataInd->ulSenderPid      = PS_PID_IMSVA;

    /*CPU ID无需要填写。OSA会根据目的pid得出CPU ID，再根据CPU ID，将消息发送到对应的CPU上*/
    pstRxDataInd->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstRxDataInd->ulReceiverPid    = DSP_PID_VOICE_RT;

    pstRxDataInd->usMsgId          = ID_IMSA_VOICE_RX_DATA_IND;

    pstRxDataInd->usCodecType      = pstVoicePara->enCodecType;
    pstRxDataInd->usDtxEnable      = pstVoicePara->usDtxEnable;
    pstRxDataInd->usErrorFlag      = pstVoicePara->usErrorFlag;
    pstRxDataInd->usRateMode       = pstVoicePara->usRateMode;
    pstRxDataInd->usFrameType      = pstVoicePara->usFrameType;
    pstRxDataInd->usQualityIdx     = pstVoicePara->usQualityIdx;
    pstRxDataInd->usSN             = pstVoicePara->usSN;
    pstRxDataInd->ulTS             = pstVoicePara->ulTS;
    pstRxDataInd->ulSSRC           = pstVoicePara->ulSsrc;

    pstRxDataInd->ulNeedAckFlag    = VOS_FALSE;
    pstRxDataInd->ulOpid           = 0;

    IMSA_MEM_CPY_S( pstRxDataInd->ausData,
                    sizeof(pstRxDataInd->ausData),
                    pusData,
                    IMSA_CODEC_MAX_DATA_LEN*sizeof(unsigned short));

    /* 如果NV没有打开，则不进行处理，按照原流程直接发包 */
    if (VOS_FALSE == IMSA_GetHifiDataControlFlag())
    {
        /* 调用消息发送函数，HIFI邮箱满的情况下，该消息发送失败，会丢弃该消息不会造成整机复位 */
        /*IMSA_SND_MSG(pstRxDataInd);*/
        IMSA_SND_MSG_NORMALLY(pstRxDataInd);
        return VOS_OK;
    }

    /* 如果发送过的消息的数量为设置的条数，说明HIFI之前还没有回复，此时缓存 */
    /* 任务加锁 */
    intLockLevel = VOS_SplIMP();
    if (IMSA_GetHifiDataNeedAckNum() <= IMSA_GetHifiDataSentDataNum())
    {
        /* 缓存函数 */
        IMSA_AddDataToBuffer(pstRxDataInd);

        /* 任务解锁 */
        VOS_Splx(intLockLevel);
        return VOS_OK;
    }

    /* 发送消息数量+1 */
    IMSA_GetHifiDataSentDataNum() ++;

    /* 如果发送的消息数量到达设置的条数，则需要HIFI回复 */
    if (IMSA_GetHifiDataNeedAckNum() <= IMSA_GetHifiDataSentDataNum())
    {
        pstRxDataInd->ulNeedAckFlag = VOS_TRUE;

        /* 启动ack保护定时器 */
        IMSVA_StartTimer(&IMSA_GetHifiDataAckProtectTimer());
    }

    /* 生成OPID */
    IMSA_GetHifiDataOpid() ++;
    pstRxDataInd->ulOpid           = IMSA_GetHifiDataOpid();

    /* 调用消息发送函数，HIFI邮箱满的情况下，该消息发送失败，会丢弃该消息不会造成整机复位 */
    /*IMSA_SND_MSG(pstRxDataInd);*/
    IMSA_SND_MSG_NORMALLY(pstRxDataInd);

    /* 任务解锁 */
    VOS_Splx(intLockLevel);

    return VOS_OK;
}

/*****************************************************************************
 Function Name  : IMSA_SndD2ImsMsgStopReq()
 Description    : 给IMS发送关机消息
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-07-16  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SndImsMsgStopReq(VOS_VOID  )
{
    IMSA_IMS_INPUT_EVENT_STRU                    *pstImsaImsInputEvent;

    /*分配空间并检验分配是否成功*/
    pstImsaImsInputEvent = IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    if ( VOS_NULL_PTR == pstImsaImsInputEvent )
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_SndImsMsgStopReq:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndImsMsgStopReq_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    IMSA_MEM_SET_S( pstImsaImsInputEvent,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU),
                    0,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    pstImsaImsInputEvent->enEventType = IMSA_IMS_EVENT_TYPE_SYSTEM;

    pstImsaImsInputEvent->evt.stInputSystemEvent.enInputSysReason = IMSA_IMS_INPUT_SYSTEM_REASON_STOP;

    pstImsaImsInputEvent->evt.stInputSystemEvent.ulOpId = IMSA_AllocImsOpId();

    IMSA_SndImsMsgSystemEvent(pstImsaImsInputEvent);

    /*释放消息空间*/
    IMSA_MEM_FREE(pstImsaImsInputEvent);

}


/*****************************************************************************
 Function Name  : IMSA_SndD2ImsMsgStartReq()
 Description    : 给IMS发送开机消息
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-07-16  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SndImsMsgStartReq(VOS_VOID  )
{
    IMSA_IMS_INPUT_EVENT_STRU                    *pstImsaImsInputEvent;

    /*分配空间并检验分配是否成功*/
    pstImsaImsInputEvent = IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    if ( VOS_NULL_PTR == pstImsaImsInputEvent )
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_SndImsMsgStartReq:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndImsMsgStartReq_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    IMSA_MEM_SET_S( pstImsaImsInputEvent,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU),
                    0,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    pstImsaImsInputEvent->enEventType = IMSA_IMS_EVENT_TYPE_SYSTEM;

    pstImsaImsInputEvent->evt.stInputSystemEvent.enInputSysReason = IMSA_IMS_INPUT_SYSTEM_REASON_START;

    pstImsaImsInputEvent->evt.stInputSystemEvent.ulOpId = IMSA_AllocImsOpId();

    IMSA_SndImsMsgSystemEvent(pstImsaImsInputEvent);

    /*释放消息空间*/
    IMSA_MEM_FREE(pstImsaImsInputEvent);

}

/*****************************************************************************
 Function Name  : IMSA_SndD2ImsMsgSystemEvent()
 Description    : 给IMS发送System事件
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2013-10-09  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SndImsMsgSystemEvent(IMSA_IMS_INPUT_EVENT_STRU *pstImsaImsInputEvent)
{
    IMSA_IMS_INPUT_SYSTEM_MSG_STRU              *pstMsgInputSystem;

    IMSA_INFO_LOG("IMSA_SndImsMsgSystemEvent:enter!");
    TLPS_PRINT2LAYER_INFO(IMSA_SndImsMsgSystemEvent_ENUM, LNAS_ENTRY);

    /*分配空间并检验分配是否成功*/
    pstMsgInputSystem = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_IMS_INPUT_SYSTEM_MSG_STRU));

    if ( VOS_NULL_PTR == pstMsgInputSystem )
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_SndD2ImsMsgSystemEvent:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndImsMsgSystemEvent_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstMsgInputSystem),
                    IMSA_GET_MSG_LENGTH(pstMsgInputSystem),
                    0,
                    IMSA_GET_MSG_LENGTH(pstMsgInputSystem));

    /*填写消息头*/
    IMSA_WRITE_IMS_MSG_HEAD(pstMsgInputSystem,ID_IMSA_IMS_INPUT_SYSTEM_MSG);

    IMSA_MEM_CPY_S( &pstMsgInputSystem->stInputSystem,
                    sizeof(IMSA_IMS_INPUT_SYSTEM_EVENT_STRU),
                    &pstImsaImsInputEvent->evt.stInputSystemEvent,
                    sizeof(IMSA_IMS_INPUT_SYSTEM_EVENT_STRU));


#if(VOS_WIN32 == VOS_OS_VER)
    /*PC测试，将消息发送出去，用于ST验证*/
    IMSA_SND_MSG(pstMsgInputSystem);

#else
    /*消息勾到HSO上*/
    (VOS_VOID)LTE_MsgHook(pstMsgInputSystem);

    /*释放消息空间*/
    IMSA_FREE_MSG(pstMsgInputSystem);

    (VOS_VOID)IMSA_WriteImsEvent((VOS_VOID*)pstImsaImsInputEvent);

#endif

}

/*****************************************************************************
 Function Name  : IMSA_SndImsMsgParaEvent()
 Description    : 给IMS发送Para事件
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2013-10-09  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SndImsMsgParaEvent(IMSA_IMS_INPUT_EVENT_STRU *pstImsaImsInputEvent)
{
    IMSA_IMS_INPUT_PARA_MSG_STRU              *pstMsgInputPara;

    IMSA_INFO_LOG("IMSA_SndImsMsgParaEvent:enter!");
    TLPS_PRINT2LAYER_INFO(IMSA_SndImsMsgParaEvent_ENUM, LNAS_ENTRY);

    /*分配空间并检验分配是否成功*/
    pstMsgInputPara = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_IMS_INPUT_PARA_MSG_STRU));

    if ( VOS_NULL_PTR == pstMsgInputPara )
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_SndImsMsgParaEvent:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndImsMsgParaEvent_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstMsgInputPara),
                    IMSA_GET_MSG_LENGTH(pstMsgInputPara),
                    0,
                    IMSA_GET_MSG_LENGTH(pstMsgInputPara));

    /*填写消息头*/
    IMSA_WRITE_IMS_MSG_HEAD(pstMsgInputPara,ID_IMSA_IMS_INPUT_PARA_MSG);

    IMSA_MEM_CPY_S( &pstMsgInputPara->stInputPara,
                    sizeof(IMSA_IMS_INPUT_PARA_EVENT_STRU),
                    &pstImsaImsInputEvent->evt.stInputParaEvent,
                    sizeof(IMSA_IMS_INPUT_PARA_EVENT_STRU));


#if(VOS_WIN32 == VOS_OS_VER)
    /*PC测试，将消息发送出去，用于ST验证*/
    IMSA_SND_MSG(pstMsgInputPara);

#else
    /*消息勾到HSO上*/
    (VOS_VOID)LTE_MsgHook(pstMsgInputPara);

    /*释放消息空间*/
    IMSA_FREE_MSG(pstMsgInputPara);

    (VOS_VOID)IMSA_WriteImsEvent((VOS_VOID*)pstImsaImsInputEvent);

#endif

}

/*****************************************************************************
 Function Name  : IMSA_SndImsMsgParaEvent()
 Description    : 给IMS发送Para事件
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2013-10-09  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SndImsMsgNvInfoEvent
(
    IMSA_IMS_INPUT_EVENT_STRU   *pstImsaImsInputEvent,
    VOS_UINT32                  ulNvInfoStruLen
)
{
    IMSA_IMS_INPUT_NV_INFO_MSG_STRU     *pstMsgInputNvInfo;

    IMSA_INFO_LOG("IMSA_SndImsMsgNvInfoEvent:enter!");
    TLPS_PRINT2LAYER_INFO(IMSA_SndImsMsgNvInfoEvent_ENUM, LNAS_ENTRY);

    /*分配空间并检验分配是否成功*/
    pstMsgInputNvInfo = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_IMS_INPUT_NV_INFO_MSG_STRU)
                                                    + ulNvInfoStruLen - IMSA_NV_INFO_LEN);

    if ( VOS_NULL_PTR == pstMsgInputNvInfo )
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_SndImsMsgParaEvent:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndImsMsgNvInfoEvent_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstMsgInputNvInfo),
                    IMSA_GET_MSG_LENGTH(pstMsgInputNvInfo),
                    0,
                    IMSA_GET_MSG_LENGTH(pstMsgInputNvInfo));

    /*填写消息头*/
    IMSA_WRITE_IMS_MSG_HEAD(pstMsgInputNvInfo,ID_IMSA_IMS_INPUT_NV_INFO_MSG);

    IMSA_MEM_CPY_S( &pstMsgInputNvInfo->stInputNvInfo,
                    sizeof(IMSA_IMS_INPUT_NV_INFO_EVENT_STRU)+ ulNvInfoStruLen - IMSA_NV_INFO_LEN,
                    &pstImsaImsInputEvent->evt.stInputNvInfoEvent,
                    sizeof(IMSA_IMS_INPUT_NV_INFO_EVENT_STRU)+ ulNvInfoStruLen - IMSA_NV_INFO_LEN);


#if(VOS_WIN32 == VOS_OS_VER)
    /*PC测试，将消息发送出去，用于ST验证*/
    IMSA_SND_MSG(pstMsgInputNvInfo);

#else
    /*消息勾到HSO上*/
    (VOS_VOID)LTE_MsgHook(pstMsgInputNvInfo);

    /*释放消息空间*/
    IMSA_FREE_MSG(pstMsgInputNvInfo);

    (VOS_VOID)IMSA_WriteImsEvent((VOS_VOID*)pstImsaImsInputEvent);

#endif

}


/*****************************************************************************
 Function Name  : IMSA_SndImsMsgServiceEvent()
 Description    : 给IMS发送Service事件
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-07-16  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SndImsMsgServiceEvent(IMSA_IMS_INPUT_EVENT_STRU *pstHiInputEvent)
{
    IMSA_IMS_INPUT_SERVICE_MSG_STRU              *pstMsgInputSevice;

    IMSA_INFO_LOG("IMSA_SndImsMsgServiceEvent:enter!");
    TLPS_PRINT2LAYER_INFO(IMSA_SndImsMsgServiceEvent_ENUM, LNAS_ENTRY);

    /*分配空间并检验分配是否成功*/
    pstMsgInputSevice = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_IMS_INPUT_SERVICE_MSG_STRU));

    if ( VOS_NULL_PTR == pstMsgInputSevice )
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_SndImsMsgServiceEvent:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndImsMsgServiceEvent_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstMsgInputSevice),
                    IMSA_GET_MSG_LENGTH(pstMsgInputSevice),
                    0,
                    IMSA_GET_MSG_LENGTH(pstMsgInputSevice));

    /*填写消息头*/
    IMSA_WRITE_IMS_MSG_HEAD(pstMsgInputSevice,ID_IMSA_IMS_INPUT_SERVICE_MSG);



    IMSA_MEM_CPY_S( &pstMsgInputSevice->stInputService,
                    sizeof(IMSA_IMS_INPUT_SERVICE_EVENT_STRU),
                    &pstHiInputEvent->evt.stInputServiceEvent,
                    sizeof(IMSA_IMS_INPUT_SERVICE_EVENT_STRU));


#if(VOS_WIN32 == VOS_OS_VER)
    /*PC测试，将消息发送出去，用于ST验证*/
    IMSA_SND_MSG(pstMsgInputSevice);

#else
    /*消息勾到HSO上*/
    (VOS_VOID)LTE_MsgHook(pstMsgInputSevice);

    /*释放消息空间*/
    IMSA_FREE_MSG(pstMsgInputSevice);

    (VOS_VOID)IMSA_WriteImsEvent((VOS_VOID*)pstHiInputEvent);

#endif

}

/*****************************************************************************
 Function Name  : IMSA_SndImsMsgCallEvent()
 Description    : 给IMS发送呼叫相关消息
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.liuhua 212067      2013-07-17  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SndImsMsgCallEvent(const IMSA_IMS_INPUT_EVENT_STRU *pstInputEvent)
{
    IMSA_IMS_INPUT_CALL_MSG_STRU                 *pstMsgInputCall;

    if(VOS_NULL_PTR == pstInputEvent)
    {
        IMSA_ERR_LOG("IMSA_SndImsMsgCallEvent:Input para err!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndImsMsgCallEvent_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*分配空间并检验分配是否成功*/
    pstMsgInputCall = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_IMS_INPUT_CALL_MSG_STRU));

    if ( VOS_NULL_PTR == pstMsgInputCall )
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_SndImsMsgCallEvent:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndImsMsgCallEvent_ENUM, 2);
        return ;
    }

    /*清空*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstMsgInputCall),
                    IMSA_GET_MSG_LENGTH(pstMsgInputCall),
                    0,
                    IMSA_GET_MSG_LENGTH(pstMsgInputCall));

    /*填写消息头*/
    IMSA_WRITE_IMS_MSG_HEAD(pstMsgInputCall,ID_IMSA_IMS_INPUT_CALL_MSG);

    IMSA_MEM_CPY_S( &pstMsgInputCall->stInputCall,
                    sizeof(IMSA_IMS_INPUT_CALL_EVENT_STRU),
                    &pstInputEvent->evt.stInputCallEvent,
                    sizeof(IMSA_IMS_INPUT_CALL_EVENT_STRU));

#if(VOS_WIN32 == VOS_OS_VER)
    /*PC测试，将消息发送出去，用于ST验证*/
    IMSA_SND_MSG(pstMsgInputCall);

#else
    /*消息勾到HSO上*/
    (VOS_VOID)LTE_MsgHook(pstMsgInputCall);

    /*释放消息空间*/
    IMSA_FREE_MSG(pstMsgInputCall);

    IMSA_NORM_LOG1("before write ims event,tick value:", PS_GET_TICK());
    TLPS_PRINT2LAYER_INFO1(IMSA_SndImsMsgCallEvent_ENUM, IMSA_TICK, PS_GET_TICK());

    (VOS_VOID)IMSA_WriteImsEvent((VOS_VOID*)pstInputEvent);

    IMSA_NORM_LOG1("after write ims event,tick value:", PS_GET_TICK());
    TLPS_PRINT2LAYER_INFO1(IMSA_SndImsMsgCallEvent_ENUM, IMSA_TICK, PS_GET_TICK());

#endif

}


/*****************************************************************************
 Function Name  : IMSA_SndImsMsgSmsEvent()
 Description    : 给IMS发送Sms事件
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-07-17  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SndImsMsgSmsEvent(IMSA_IMS_INPUT_EVENT_STRU *pstImsaImsInputEvent)
{
    IMSA_IMS_INPUT_SMS_MSG_STRU                  *pstMsgInputSms;

    /*分配空间并检验分配是否成功*/
    pstMsgInputSms = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_IMS_INPUT_SMS_MSG_STRU));

    if ( VOS_NULL_PTR == pstMsgInputSms )
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_SndImsMsgSmsEvent:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndImsMsgSmsEvent_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstMsgInputSms),
                    IMSA_GET_MSG_LENGTH(pstMsgInputSms),
                    0,
                    IMSA_GET_MSG_LENGTH(pstMsgInputSms));

    /*填写消息头*/
    IMSA_WRITE_IMS_MSG_HEAD(pstMsgInputSms,ID_IMSA_IMS_INPUT_SMS_MSG);

    IMSA_MEM_CPY_S( &pstMsgInputSms->stInputSms,
                    sizeof(IMSA_IMS_INPUT_SMS_EVENT_STRU),
                    &pstImsaImsInputEvent->evt.stInputSmsEvent,
                    sizeof(IMSA_IMS_INPUT_SMS_EVENT_STRU));

#if(VOS_WIN32 == VOS_OS_VER)
    /*PC测试，将消息发送出去，用于ST验证*/
    IMSA_SND_MSG(pstMsgInputSms);

#else
    /*消息勾到HSO上*/
    (VOS_VOID)LTE_MsgHook(pstMsgInputSms);

    /*释放消息空间*/
    IMSA_FREE_MSG(pstMsgInputSms);

    (VOS_VOID)IMSA_WriteImsEvent((VOS_VOID*)pstImsaImsInputEvent);

#endif

}

/*****************************************************************************
 Function Name  : IMSA_SndImsMsgUssdEvent()
 Description    : 给IMS发送USSD事件
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.leili 00132387      2013-12-23  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SndImsMsgUssdEvent(IMSA_IMS_INPUT_EVENT_STRU *pstImsaImsInputEvent)
{
    IMSA_IMS_INPUT_USSD_MSG_STRU                  *pstMsgInputUssd;

    /*分配空间并检验分配是否成功*/
    pstMsgInputUssd = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_IMS_INPUT_USSD_MSG_STRU));

    if ( VOS_NULL_PTR == pstMsgInputUssd )
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_SndImsMsgUssdEvent:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndImsMsgUssdEvent_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstMsgInputUssd),
                    IMSA_GET_MSG_LENGTH(pstMsgInputUssd),
                    0,
                    IMSA_GET_MSG_LENGTH(pstMsgInputUssd));

    /*填写消息头*/
    IMSA_WRITE_IMS_MSG_HEAD(pstMsgInputUssd,ID_IMSA_IMS_INPUT_USSD_MSG);

    IMSA_MEM_CPY_S( &pstMsgInputUssd->stInputUssd,
                    sizeof(IMSA_IMS_INPUT_USSD_EVENT_STRU),
                    &pstImsaImsInputEvent->evt.stInputUssdEvent,
                    sizeof(IMSA_IMS_INPUT_USSD_EVENT_STRU));

#if(VOS_WIN32 == VOS_OS_VER)
    /*PC测试，将消息发送出去，用于ST验证*/
    IMSA_SND_MSG(pstMsgInputUssd);

#else
    /*消息勾到HSO上*/
    (VOS_VOID)LTE_MsgHook(pstMsgInputUssd);

    /*释放消息空间*/
    IMSA_FREE_MSG(pstMsgInputUssd);

    (VOS_VOID)IMSA_WriteImsEvent((VOS_VOID*)pstImsaImsInputEvent);

#endif

}



/*****************************************************************************
 Function Name  : IMSA_ImsQryParaMsgSave
 Description    : 保存正在执行的IMS命令及参数。目前只保存opid和正在执行的命令类型
 Input          : pstCallEvt    正在执行的IMS消息
 Output         : VOS_VOID
 Return Value   : 保存结果

 History        :
      1.wangchen 00209181   2013-12-30  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_ImsInputParaMsgSave(const IMSA_IMS_INPUT_PARA_EVENT_STRU *pstParaEvt)
{
    IMSA_ENTITY_STRU *pstImsaEntity = IMSA_CtxGet();

    IMSA_INFO_LOG("IMSA_ImsInputParaMsgSave is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ImsInputParaMsgSave_ENUM, LNAS_ENTRY);

    pstImsaEntity->stImsaControlManager.stImsMsg.ulCsmId     = pstParaEvt->ulOpId;
    pstImsaEntity->stImsaControlManager.stImsMsg.ulCsmReason = pstParaEvt->enInputParaReason;

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_ImsQryParaMsgSave
 Description    : 保存正在执行的IMS命令及参数。目前只保存opid和正在执行的命令类型
 Input          : pstCallEvt    正在执行的IMS消息
 Output         : VOS_VOID
 Return Value   : 保存结果

 History        :
      1.wangchen 00209181   2013-12-30  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ImsInputParaMsgClear(VOS_VOID)
{
    IMSA_ENTITY_STRU *pstImsaEntity = IMSA_CtxGet();

    IMSA_INFO_LOG("IMSA_ImsInputParaMsgClear is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ImsInputParaMsgClear_ENUM, LNAS_ENTRY);

    pstImsaEntity->stImsaControlManager.stImsMsg.bitOpImsMsg = IMSA_FALSE;
    pstImsaEntity->stImsaControlManager.stImsMsg.ulCsmId     = 0;
    pstImsaEntity->stImsaControlManager.stImsMsg.ulCsmReason = 0xffffffff;
}

/*****************************************************************************
 Function Name  : IMSA_SendImsVolteImpuQryReq()
 Description    : 给IMS发送IMPU查询事件
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181       2013-12-19  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SendImsVolteImpuQryReq(VOS_VOID)
{
    IMSA_IMS_INPUT_EVENT_STRU          *pstImsaImsInputEvent = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SendImsVolteImpuQryReq is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SendImsVolteImpuQryReq_ENUM, LNAS_ENTRY);

    /*分配空间并检验分配是否成功*/
    pstImsaImsInputEvent = IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    if ( VOS_NULL_PTR == pstImsaImsInputEvent )
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_SendImsVolteImpuQryReq:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SendImsVolteImpuQryReq_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    IMSA_MEM_SET_S( pstImsaImsInputEvent,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU),
                    0,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    pstImsaImsInputEvent->enEventType = IMSA_IMS_EVENT_TYPE_PARA;
    pstImsaImsInputEvent->evt.stInputParaEvent.enInputParaReason = IMAS_IMS_INPUT_PARA_REASON_QUERY_IMPU;
    pstImsaImsInputEvent->evt.stInputParaEvent.ulOpId = IMSA_AllocImsOpId();

    IMSA_SndImsMsgParaEvent(pstImsaImsInputEvent);

    /* 保存查询IMPU的消息 */
    (VOS_VOID)IMSA_ImsInputParaMsgSave(&pstImsaImsInputEvent->evt.stInputParaEvent);

    /*释放消息空间*/
    IMSA_MEM_FREE(pstImsaImsInputEvent);

    return;
}
/*****************************************************************************
 Function Name  : IMSA_SendImsCcwaiSetReq()
 Description    : 给IMS发送IMPU查询事件
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181       2013-12-19  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SendImsCcwaiSetReq(VOS_UINT8 ucCallWaiting)
{
    IMSA_IMS_INPUT_EVENT_STRU          *pstImsaImsInputEvent = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SendImsCcwaiSetReq is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SendImsCcwaiSetReq_ENUM, LNAS_ENTRY);

    /*分配空间并检验分配是否成功*/
    pstImsaImsInputEvent = IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    if ( VOS_NULL_PTR == pstImsaImsInputEvent )
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_SendImsCcwaiSetReq:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SendImsCcwaiSetReq_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    IMSA_MEM_SET_S( pstImsaImsInputEvent,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU),
                    0,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    pstImsaImsInputEvent->enEventType = IMSA_IMS_EVENT_TYPE_PARA;
    pstImsaImsInputEvent->evt.stInputParaEvent.enInputParaReason = IMAS_IMS_INPUT_PARA_REASON_SET_CALL_WAITING;
    pstImsaImsInputEvent->evt.stInputParaEvent.ulOpId = IMSA_AllocImsOpId();
    pstImsaImsInputEvent->evt.stInputParaEvent.u.stUeCapability.ucCallWaiting = ucCallWaiting;

    IMSA_SndImsMsgParaEvent(pstImsaImsInputEvent);

    /* 保存设置CCWAI的消息 */
    (VOS_VOID)IMSA_ImsInputParaMsgSave(&pstImsaImsInputEvent->evt.stInputParaEvent);

    /*释放消息空间*/
    IMSA_MEM_FREE(pstImsaImsInputEvent);

    return;
}

/*****************************************************************************
 Function Name  : IMSA_ProcImsMsgQryVolteImpuCnf()
 Description    : IMS发送IMPU查询回复事件处理
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181       2013-12-19  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ProcImsMsgQryVolteImpuCnf(const IMSA_IMS_OUTPUT_PARA_EVENT_STRU *pstOutPara)
{
    VOS_UINT32                          ulResult = VOS_ERR;
    VOS_UINT32                          ulImpuLen = 0;
    VOS_CHAR                            aucImpu[IMSA_IMS_EVENT_STRING_SZ+1] = {0};

    IMSA_INFO_LOG("IMSA_ProcImsMsgQryVolteImpuCnf is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ProcImsMsgQryVolteImpuCnf_ENUM, LNAS_ENTRY);

    if (VOS_TRUE == pstOutPara->bitOpResult)
    {
        ulResult = pstOutPara->ulResult;
    }

    if (VOS_TRUE == pstOutPara->bitOpImpu)
    {
        ulImpuLen = pstOutPara->ulImpuLen;

        IMSA_MEM_CPY_S( aucImpu,
                        IMSA_IMS_EVENT_STRING_SZ+1,
                        pstOutPara->aucImpu,
                        IMSA_IMS_EVENT_STRING_SZ+1);
    }

    IMSA_SndMsgAtQryVolteImpuCnf(ulResult, ulImpuLen, aucImpu);

}

/*****************************************************************************
 Function Name  : IMSA_ProcImsMsgCcwaiSetCnf()
 Description    : IMS发送IMPU查询回复事件处理
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181       2013-12-19  Draft Enact
      2.jiaguocai 00355737      2015-9-07   amend for ccwa
*****************************************************************************/
VOS_VOID IMSA_ProcImsMsgCcwaiSetCnf(const IMSA_IMS_OUTPUT_PARA_EVENT_STRU *pstOutPara)
{
    VOS_UINT32                          ulResult = VOS_ERR;
    IMSA_AT_CONTROL_STRU                *pstImsaAtControl;

    pstImsaAtControl = IMSA_GetAtControlAddress();

    IMSA_INFO_LOG("IMSA_ProcImsMsgCcwaiSetCnf is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ProcImsMsgCcwaiSetCnf_ENUM, LNAS_ENTRY);

    if (IMSA_IMS_OUTPUT_PARA_REASON_SET_OK == pstOutPara->enOutputParaReason)
    {
        ulResult = VOS_OK;

        /*向TAF发送ccwa配置信息*/
        IMSA_CallSendCcwaCapInfo(pstImsaAtControl->enMode);
    }

    IMSA_SndMsgAtCcwaiSetCnf(ulResult);
}





/*****************************************************************************
 Function Name  : IMSA_ImsStartTimer()
 Description    : IMS协议栈调用，用于启动定时器
 Input          : pstTimerPara 定时器参数存放地址(内存由调用者释放)
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-07-25  Draft Enact
*****************************************************************************/
unsigned int IMSA_ImsStartTimer(const IMSA_TIMER_PARA_STRU  *pstTimerPara)
{
    if((VOS_NULL_PTR == pstTimerPara)
        ||(pstTimerPara->ulTimerName >= IMSA_IMS_TIMER_NAME_BUTT))
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_ImsStartTimer:ERROR input para!");
        TLPS_PRINT2LAYER_ERROR(IMSA_ProcImsMsgCcwaiSetCnf_ENUM, LNAS_PARAM_INVALID);
        return VOS_ERR;
    }

    /*判断定时器是否打开，已打开则关闭*/
    if(VOS_NULL_PTR != aphTimer[pstTimerPara->ulTimerName])
    {
        /*关闭失败，则报警返回*/
        if (VOS_OK != PS_STOP_REL_TIMER(&(aphTimer[pstTimerPara->ulTimerName])))
        {
            /*打印异常信息*/
            IMSA_WARN_LOG("IMSA_D2ImsStartTimer:WARN: stop reltimer error!");
            TLPS_PRINT2LAYER_WARNING(IMSA_ProcImsMsgCcwaiSetCnf_ENUM, IMSA_CALL_API_ERROR);
            return VOS_ERR;
        }

        /*打印异常信息*/
        IMSA_WARN_LOG1("(TimerType) Timer not close!",pstTimerPara->ulTimerName);
        TLPS_PRINT2LAYER_WARNING1(IMSA_ProcImsMsgCcwaiSetCnf_ENUM, IMSA_TIMER_PARA, pstTimerPara->ulTimerName);
    }

    if (pstTimerPara->ulLen == 0)
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_ImsStartTimer:ERROR: start unreasonable reltimer.");
        TLPS_PRINT2LAYER_ERROR(IMSA_ProcImsMsgCcwaiSetCnf_ENUM, 1);
        return VOS_ERR;
    }

    /*设定定时器NAME，打开失败则报警返回*/
    if (VOS_OK !=\
            PS_START_CALLBACK_REL_TIMER(&(aphTimer[pstTimerPara->ulTimerName]),\
                                        PS_PID_IMSVA,  pstTimerPara->ulLen, \
                                        pstTimerPara->ulTimerName,\
                                        pstTimerPara->ulParam, pstTimerPara->ucMode,\
                                        (REL_TIMER_FUNC)pstTimerPara->TimeOutRoutine, \
                                        pstTimerPara->enPrecision))
    {
          /*打印异常信息*/
          IMSA_WARN_LOG("IMSA_ImsStartTimer:WARN: start reltimer error!");
          TLPS_PRINT2LAYER_WARNING(IMSA_ProcImsMsgCcwaiSetCnf_ENUM, 2);
          return VOS_ERR;
    }

    return VOS_OK;

}


/*****************************************************************************
 Function Name  : IMSA_D2ImsStartTimer()
 Description    : IMS协议栈调用，用于停止定时器
 Input          : pstTimerPara 定时器参数存放地址(内存由调用者释放)
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-07-25  Draft Enact
*****************************************************************************/
unsigned int IMSA_ImsStopTimer(unsigned int  ulTimerName)
{
    if(ulTimerName >= IMSA_IMS_TIMER_NAME_BUTT)
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_ImsStopTimer:ERROR input para!");
        TLPS_PRINT2LAYER_ERROR(IMSA_ImsStopTimer_ENUM, LNAS_PARAM_INVALID);
        return VOS_ERR;
    }

    /*判断定时器是否打开，已打开则关闭*/
    if(VOS_NULL_PTR != aphTimer[ulTimerName])
    {
        /*关闭失败，则报警返回*/
        if (VOS_OK != PS_STOP_REL_TIMER(&(aphTimer[ulTimerName])))
        {
            /*打印异常信息*/
            IMSA_WARN_LOG("IMSA_ImsStopTimer:WARN: stop reltimer error!");
            TLPS_PRINT2LAYER_WARNING(IMSA_ImsStopTimer_ENUM, IMSA_CALL_API_ERROR);
            return VOS_ERR;
        }

        aphTimer[ulTimerName] = VOS_NULL_PTR;
    }

    return VOS_OK;

}

/*****************************************************************************
 Function Name  : IMSVA_StartTimer()
 Description    : IMSVA调用，用于启动定时器
 Input          : pstTimerPara 定时器参数存放地址(内存由调用者释放)
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.zhaochen 00308719      2015-11-16  Draft Enact
*****************************************************************************/
VOS_VOID IMSVA_StartTimer(IMSA_TIMER_STRU *pstTimer)
{
    if(pstTimer == VOS_NULL_PTR)
    {
        return;
    }

    /*判断定时器是否打开，已打开则关闭*/
    if(VOS_NULL_PTR != pstTimer->phTimer)
    {
        /*关闭失败，则报警返回*/
        if (VOS_OK != PS_STOP_REL_TIMER(&(pstTimer->phTimer)))
        {
            /*打印异常信息*/
            IMSA_WARN_LOG("IMSVA_StartTimer:WARN: stop reltimer error!");
            TLPS_PRINT2LAYER_WARNING(IMSA_StartTimer_ENUM, LNAS_ERROR);
            return;
        }

        /*打印异常信息*/
        IMSA_WARN_LOG1("(TimerType) Timer not close!",pstTimer->usName);
        TLPS_PRINT2LAYER_WARNING1(IMSA_StartTimer_ENUM, 2, pstTimer->usName);
    }

    if (pstTimer->ulTimerLen == 0)
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSVA_StopTimer:ERROR: start unreasonable reltimer.");
        TLPS_PRINT2LAYER_ERROR(IMSA_StartTimer_ENUM, 3);
        return;
    }

    /*设定定时器NAME，打开失败则报警返回*/
    if (VOS_OK !=\
            PS_START_REL_TIMER(&(pstTimer->phTimer),PS_PID_IMSVA,\
                                pstTimer->ulTimerLen,(VOS_UINT32)pstTimer->usName,\
                                pstTimer->usPara,pstTimer->ucMode))
    {
          /*打印异常信息*/
          IMSA_WARN_LOG("IMSVA_StartTimer:WARN: start reltimer error!");
          TLPS_PRINT2LAYER_WARNING(IMSA_StartTimer_ENUM, 4);
          return;
    }

}

/*****************************************************************************
 Function Name  : IMSVA_StopTimer()
 Description    : IMSVA调用，用于停止定时器
 Input          : pstTimerPara 定时器参数存放地址(内存由调用者释放)
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.zhaochen 00308719      2015-11-16  Draft Enact
*****************************************************************************/
VOS_VOID IMSVA_StopTimer(IMSA_TIMER_STRU *pstTimer)
{
    if(pstTimer == VOS_NULL_PTR)
    {
        return;
    }

    /*判断定时器是否打开，已打开则关闭*/
    if(VOS_NULL_PTR != pstTimer->phTimer)
    {
        /*关闭失败，则报警返回*/
        if (VOS_OK != PS_STOP_REL_TIMER(&(pstTimer->phTimer)))
        {
            /*打印异常信息*/
            IMSA_WARN_LOG("IMSA_StopTimer:WARN: stop reltimer error!");
            TLPS_PRINT2LAYER_WARNING(IMSA_StopTimer_ENUM, IMSA_CALL_API_ERROR);
            return;
        }

        pstTimer->phTimer = VOS_NULL_PTR;

        IMSA_INFO_LOG1("(TimerType) Timer closed!",pstTimer->usName);
        TLPS_PRINT2LAYER_INFO(IMSA_StopTimer_ENUM, LNAS_TIMER_STOP);
    }

}


/*****************************************************************************
 Function Name  : IMSA_ImsAdaption_Init()
 Description    : 初始化接口相关的函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.zhaochen 00308719      2015-11-09  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ImsAdaption_Init(VOS_VOID)
{
    IMSA_HIFI_DATA_MANAGER_STRU        *pstHifiDataManager;
    pstHifiDataManager = IMSA_GetHifiDataManagerAddress();
    IMSA_ClearHifiData();

    /*设置定时器长度，名称等*/
    pstHifiDataManager->stHifiAckProtectTimer.usName     = TI_IMSA_HIFI_ACK_PROTECT;
    pstHifiDataManager->stHifiAckProtectTimer.ulTimerLen = IMSA_HIFI_ACK_PROTECT_LENGTH;
    pstHifiDataManager->stHifiAckProtectTimer.ucMode     = 0;
    pstHifiDataManager->ulTotalDataLoseNum               = 0;
    pstHifiDataManager->ulTotalDataBufferNum             = 0;
}

/*****************************************************************************
 Function Name  : IMSA_ClearHifiData()
 Description    : 清除HIFI控制函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.zhaochen 00308719      2015-11-09  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ClearHifiData(VOS_VOID)
{
    /* IMSA需要控制给HIFI发消息的速度，防止复位。 */
    IMSA_HIFI_DATA_MANAGER_STRU        *pstHifiDataManager;
    IMSA_HIFI_DATA_BUFFER_NODE_STRU    *pstTempNode = VOS_NULL_PTR;
    pstHifiDataManager = IMSA_GetHifiDataManagerAddress();

    /* 释放链表 */
    while (VOS_NULL_PTR != pstHifiDataManager->pstBufferDataHead)
    {
        /* 释放节点 */
        pstTempNode = pstHifiDataManager->pstBufferDataHead->pstNextBufferData;
    #if(VOS_WIN32 == VOS_OS_VER)
        /*PC测试，需要调用MemFree来释放内存*/
        IMSA_MEM_FREE(pstHifiDataManager->pstBufferDataHead->pstRxDataInd);
    #else
        IMSA_FREE_MSG(pstHifiDataManager->pstBufferDataHead->pstRxDataInd);
    #endif
        IMSA_MEM_FREE(pstHifiDataManager->pstBufferDataHead);
        pstHifiDataManager->pstBufferDataHead = pstTempNode;
    }

    pstHifiDataManager->pstBufferDataHead     = VOS_NULL_PTR;
    pstHifiDataManager->pstBufferDataTail     = VOS_NULL_PTR;
    pstHifiDataManager->ucBufferDataNum       = 0;
    pstHifiDataManager->ucSentDataNum         = 0;
    pstHifiDataManager->ulOpid                = 0;
    pstHifiDataManager->ulDataLoseNum         = 0;
    pstHifiDataManager->ulDataBufferNum       = 0;

}

/*****************************************************************************
 Function Name  : IMSA_ImsAdaption_Init()
 Description    : 初始化接口相关的函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.zhaochen 00308719      2015-11-09  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ImsAdaption_ClearResource(VOS_VOID)
{
    /* 清除缓存数据 */
    IMSA_ClearHifiData();

    /*停止定时器*/
    IMSVA_StopTimer(&IMSA_GetHifiDataAckProtectTimer());
}

/*****************************************************************************
 Function Name  : IMSA_AddDataToBuffer()
 Description    : 将消息添加到缓存链表中
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.zhaochen 00308719      2015-11-09  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_AddDataToBuffer(IMSA_VOICE_RX_DATA_IND_STRU *pstRxDataInd)
{
    IMSA_HIFI_DATA_BUFFER_NODE_STRU    *pstTempNode;
    IMSA_HIFI_DATA_BUFFER_NODE_STRU    *pstTempNode2;

    /*分配空间并检验分配是否成功*/
    /* 申请链表节点内存 */
    pstTempNode = (VOS_VOID*)IMSA_MEM_ALLOC(sizeof(IMSA_HIFI_DATA_BUFFER_NODE_STRU));
    if ( VOS_NULL_PTR == pstTempNode )
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_AddDataToBuffer:ERROR:Alloc Msg fail!");
        return;
    }
    pstTempNode->pstRxDataInd      = pstRxDataInd;
    pstTempNode->pstNextBufferData = VOS_NULL_PTR;

    /* 可维可测 */
    IMSA_GetHifiDataDataBufferNum() ++;
    IMSA_GetHifiDataTotalDataBufferNum() ++;

    /* 如果链表还为空，则初始化链表，将消息存进链表头结点，当前节点指针和头结点指针相同 */
    if (0 == IMSA_GetHifiDataBufferDataNum() || VOS_NULL_PTR == IMSA_GetHifiDataBufferDataHead())
    {
        IMSA_GetHifiDataBufferDataNum() = 0;

        /* 释放链表 */
        while (VOS_NULL_PTR != IMSA_GetHifiDataBufferDataHead())
        {
            /* 释放节点 */
            pstTempNode2 = IMSA_GetHifiDataBufferDataHead()->pstNextBufferData;
#if(VOS_WIN32 == VOS_OS_VER)
            /*PC测试，需要调用MemFree来释放内存*/
            IMSA_MEM_FREE(IMSA_GetHifiDataBufferDataHead()->pstRxDataInd);
#else
            IMSA_FREE_MSG(IMSA_GetHifiDataBufferDataHead()->pstRxDataInd);
#endif
            IMSA_MEM_FREE(IMSA_GetHifiDataBufferDataHead());
            IMSA_GetHifiDataBufferDataHead() = pstTempNode2;
        }
        IMSA_GetHifiDataBufferDataHead()     = VOS_NULL_PTR;
        IMSA_GetHifiDataBufferDataTail()     = pstTempNode;

        /* 由于是初始化链表，头结点和尾节点是同一个节点 */
        IMSA_GetHifiDataBufferDataHead() = IMSA_GetHifiDataBufferDataTail();

        /* 节点个数+1 */
        IMSA_GetHifiDataBufferDataNum()++;
        return;
    }

    /* 将消息添加到链表的最后 */
    /* 取下一个节点的地址，作为新的当前节点地址 */
    IMSA_GetHifiDataBufferDataTail()->pstNextBufferData = pstTempNode;
    IMSA_GetHifiDataBufferDataTail() = IMSA_GetHifiDataBufferDataTail()->pstNextBufferData;


    /* 节点个数+1 */
    IMSA_GetHifiDataBufferDataNum()++;

    /* 如果链表满了，则删除头结点，将第二个节点作为头结点 */
    while (IMSA_GetHifiDataMaxBufferNum() < IMSA_GetHifiDataBufferDataNum())
    {
        /* 可维可测 */
        IMSA_GetHifiDataDataLoseNum() ++;
        IMSA_GetHifiDataTotalDataLoseNum() ++;

        /* 释放掉头结点的内存 */
        pstTempNode = IMSA_GetHifiDataBufferDataHead()->pstNextBufferData;
#if(VOS_WIN32 == VOS_OS_VER)
        /*PC测试，需要调用MemFree来释放内存*/
        IMSA_MEM_FREE(IMSA_GetHifiDataBufferDataHead()->pstRxDataInd);
#else
        IMSA_FREE_MSG(IMSA_GetHifiDataBufferDataHead()->pstRxDataInd);
#endif

        IMSA_MEM_FREE(IMSA_GetHifiDataBufferDataHead());

        /* 将第二个节点作为新的头结点 */
        IMSA_GetHifiDataBufferDataHead() = pstTempNode;
        IMSA_GetHifiDataBufferDataNum() --;
    }

    return;
}

/*****************************************************************************
 Function Name  : IMSA_SendOneBufferData()
 Description    : 从缓存链表中取出一条发送出去
 Input          : ucNeedAckFlag 需要HIFI回复的标志
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.zhaochen 00308719      2015-11-09  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SendOneBufferData(VOS_UINT8 ulNeedAckFlag)
{
    IMSA_HIFI_DATA_BUFFER_NODE_STRU    *pstTempNode;
    IMSA_VOICE_RX_DATA_IND_STRU        *pstRxDataInd;

    pstRxDataInd = IMSA_GetHifiDataBufferDataHead()->pstRxDataInd;
    pstRxDataInd->ulNeedAckFlag = ulNeedAckFlag;

    /* 生成OPID */
    IMSA_GetHifiDataOpid() ++;
    pstRxDataInd->ulOpid           = IMSA_GetHifiDataOpid();

    /* 发送消息 */
    IMSA_SND_MSG_NORMALLY(pstRxDataInd);

    /* 释放掉头结点的内存 */
    pstTempNode = IMSA_GetHifiDataBufferDataHead()->pstNextBufferData;
    IMSA_MEM_FREE(IMSA_GetHifiDataBufferDataHead());

    /* 将第二个节点作为新的头结点 */
    IMSA_GetHifiDataBufferDataHead() = pstTempNode;

    /* 节点个数-1 */
    IMSA_GetHifiDataBufferDataNum()--;

    return;
}

/*****************************************************************************
 Function Name  : IMSA_ProcTimerMsgHifiAckProtect()
 Description    : 处理HIFI回执保护定时器超时的函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.zhaochen 00308719      2015-11-09  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ProcTimerMsgHifiAckProtect(const VOS_VOID *pRcvMsg)
{
    VOS_INT32                           intLockLevel;
    IMSA_HIFI_DATA_BUFFER_NODE_STRU    *pstTempNode = VOS_NULL_PTR;

    /* 任务加锁 */
    intLockLevel = VOS_SplIMP();

    /* 如果当前没有缓存的消息，则将发包个数-1 */
    if (0 == IMSA_GetHifiDataBufferDataNum() || VOS_NULL_PTR == IMSA_GetHifiDataBufferDataHead())
    {
        IMSA_GetHifiDataBufferDataNum() = 0;
        /* 释放链表 */
        while (VOS_NULL_PTR != IMSA_GetHifiDataBufferDataHead())
        {
            /* 释放节点 */
            pstTempNode = IMSA_GetHifiDataBufferDataHead()->pstNextBufferData;
#if(VOS_WIN32 == VOS_OS_VER)
            /*PC测试，需要调用MemFree来释放内存*/
            IMSA_MEM_FREE(IMSA_GetHifiDataBufferDataHead()->pstRxDataInd);
#else
            IMSA_FREE_MSG(IMSA_GetHifiDataBufferDataHead()->pstRxDataInd);
#endif
            IMSA_MEM_FREE(IMSA_GetHifiDataBufferDataHead());
            IMSA_GetHifiDataBufferDataHead() = pstTempNode;
        }

        IMSA_GetHifiDataBufferDataHead()     = VOS_NULL_PTR;
        IMSA_GetHifiDataBufferDataTail()     = VOS_NULL_PTR;

        /* 防止翻转 */
        if (IMSA_GetHifiDataNeedAckNum() <= IMSA_GetHifiDataSentDataNum())
        {
            IMSA_GetHifiDataSentDataNum() --;
        }

        /* 任务解锁 */
        VOS_Splx(intLockLevel);
        return;
    }

    /* 如果当前有缓存的消息，则将缓存链表中头结点的消息发出，启动定时器 */
    IMSA_SendOneBufferData(VOS_TRUE);

    /* 任务解锁 */
    VOS_Splx(intLockLevel);

    /* 启动ack保护定时器 */
    IMSVA_StartTimer(&IMSA_GetHifiDataAckProtectTimer());
    return;
}

/*lint +e961*/
/*lint +e960*/


#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of ImsaImsAdaption.c */



