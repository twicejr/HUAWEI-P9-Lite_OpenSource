/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : ImsaMain.c
  Description     : 该C文件给出了IMSA模块初始化和消息处理入口的实现
  History           :
     1.sunbing 49683      2013-04-23  Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "PsTypeDef.h"
#include "ImsaMain.h"
#include "ImsaEntity.h"
#include "ImsaPublic.h"
#include "ImsaImsAdaption.h"
#include "UsimPsInterface.h"
#include "ImsaProcTimerMsg.h"
#include "ImsaProcCdsMsg.h"
#include "ImsaServiceManagement.h"
#include "ImsaProcMsccMsg.h"
#include "ImsaConnManagement.h"
#include "ImsaServiceManagement.h"
#include "ImsaRegManagement.h"
#include "ImsaCallManagement.h"
#include "VcImsaInterface.h"
#include "ImsaDsDsPublic.h"
#if (VOS_OS_VER != VOS_WIN32)
#include "siapppih.h"
#endif
#include "ImsaProcApsMsg.h"
#include "ImsaProcSmsMsg.h"
#include "CallImsaInterface.h"
#include "ImsaProcAtMsg.h"
#include "ImsaProcSpmMsg.h"
#include "ImsaProcUssdMsg.h"

#if (FEATURE_ON == FEATURE_PTM)
#include "ImsaProcOmMsg.h"
#endif

#include "ImsaMtcInterface.h"

#include "ImsaLmmInterface.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_IMSAMAIN_C
#define    THIS_NAS_FILE_ID    NAS_FILE_ID_IMSAMAIN_C
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
IMSA_ENTITY_STRU                        g_stImsaEntity;
IMSA_ENTITY_STRU                       *pgstImsaEntity = &g_stImsaEntity;


/*****************************************************************************
  3 Function
*****************************************************************************/
extern VOS_VOID IMSA_MsgHandle(const VOS_VOID *pRcvMsg );

extern VOS_VOID IMSA_IntraMsgProcess(VOS_VOID);

extern VOS_VOID IMSA_TafMsgDistr(const VOS_VOID *pRcvMsg );

extern VOS_VOID IMSA_IntraMsgDistr(const VOS_VOID *pRcvMsg );

extern VOS_VOID IMSA_ImsMsgDistr(const VOS_VOID *pRcvMsg );

extern VOS_VOID IMSA_UsimMsgDistr(const VOS_VOID *pRcvMsg );

extern VOS_VOID IMSA_PihMsgDistr(const VOS_VOID *pRcvMsg );

extern VOS_VOID IMSA_VcMsgDistr(const VOS_VOID *pRcvMsg);

extern VOS_VOID IMSA_AtMsgDistr(const VOS_VOID *pRcvMsg);
#if (FEATURE_ON == FEATURE_PTM)
extern VOS_VOID IMSA_OmMsgDistr(const VOS_VOID *pRcvMsg);
#endif

extern VOS_VOID IMSA_MtcMsgDistr(const VOS_VOID *pRcvMsg);


extern VOS_VOID IMSA_Init(VOS_VOID);
extern VOS_VOID IMSA_PrintState( VOS_VOID );
extern VOS_UINT8 * IMSA_GetNextIntraMsg(VOS_VOID);
extern VOS_UINT32 IMSA_PidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 IMSVA_PidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_VOID IMSA_TaskEntry(MsgBlock * pMsg);
extern VOS_VOID IMSVA_TaskEntry(MsgBlock * pMsg);

extern VOS_VOID IMSA_LmmMsgDistr(const MsgBlock * pMsg);

/*****************************************************************************
 Function Name  : IMSA_Init()
 Description    : IMSA初始化函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1. sunbing 49683      2013-04-23  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_Init(VOS_VOID)
{
    /*各模块的初始化*/
    IMSA_CONN_Init();

    IMSA_CONTROL_Init();

    IMSA_RegMgrInit();

    (VOS_VOID)IMSA_CallCtxInit();

    IMSA_SMS_Init();

    IMSA_ResetImsOpId();

    IMSA_ResetUsimOpId();

    IMSA_USSD_Init();

    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_DsdsInit();
    #endif
    #if (FEATURE_ON == FEATURE_PTM)
    IMSA_InitErrLogInfo();
    #endif
    IMSA_ImsAdaption_Init();
}

/*****************************************************************************
 Function Name  : IMSA_ClearResource()
 Description    : IMSA清除资源
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1. lihong00150010      2013-07-27  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_ClearResource( VOS_VOID )
{
    IMSA_CONN_ClearResource();

    IMSA_CONTROL_ClearResource();

    IMSA_RegMgrDeinit();

    (VOS_VOID)IMSA_CallCtxDeinit();

    IMSA_SMS_ClearResource();

    IMSA_USSD_ClearResource();

    IMSA_ResetImsOpId();

    IMSA_ResetUsimOpId();

    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_DsdsClearResource();
    #endif

    IMSA_ImsAdaption_ClearResource();
}

/*****************************************************************************
 Function Name  : IMSA_PrintState()
 Description    : 打印子模块的状态
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-08-29  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_PrintState( VOS_VOID )
{
    IMSA_SRV_PrintNrmSrvState();
    IMSA_CONN_PrintNrmConnState();
    IMSA_RegPrintNrmRegState();
    IMSA_SRV_PrintEmcSrvState();
    IMSA_CONN_PrintEmcConnState();
    IMSA_RegPrintEmcRegState();
}

/*****************************************************************************
 Function Name  : IMSA_MsgHandle()
 Description    : IMSA函数处理函数，,根据接收到的消息的所属模块，将消息分发给处理该模块消息的子模块。
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-20  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_MsgHandle(const VOS_VOID *pRcvMsg )
{
    /* 定义消息头指针*/
    PS_MSG_HEADER_STRU          *pHeader = VOS_NULL_PTR;

    /* 获取消息头指针*/
    pHeader = (PS_MSG_HEADER_STRU *) pRcvMsg;

    IMSA_PrintImsaRevMsg(pHeader,IMSA_GET_IMSA_PRINT_BUF());
    IMSA_PrintState();

    switch(pHeader->ulSenderPid)
    {
        /*TAF有多个模块，需要进一步分发*/
        case WUEPS_PID_TAF:
            IMSA_TafMsgDistr(pRcvMsg);
            break;

        case UEPS_PID_MSCC:
            IMSA_ProcMsccMsg(pRcvMsg);
            break;

        case VOS_PID_TIMER:
            IMSA_TimerMsgDistr((REL_TIMER_MSG *)pRcvMsg);
            break;

        case PS_PID_IMSA:
            IMSA_IntraMsgDistr(pRcvMsg);
            break;

        case PS_PID_IMSVA:
            IMSA_ImsMsgDistr(pRcvMsg);
            break;

        /*USIM消息处理*/
        case WUEPS_PID_USIM:
            IMSA_UsimMsgDistr(pRcvMsg);
            break;

        /*向USIM注册PID，USIM会通过这个PID通知IMSA*/
        case MAPS_PIH_PID:
            IMSA_PihMsgDistr(pRcvMsg);
            break;

        case UEPS_PID_CDS:
            IMSA_CdsMsgDistr(pRcvMsg);
            break;

        case WUEPS_PID_VC:
            IMSA_VcMsgDistr(pRcvMsg);
            break;
        case WUEPS_PID_AT:
            IMSA_AtMsgDistr(pRcvMsg);
            break;
        #if (FEATURE_PTM == FEATURE_ON)
        case MSP_PID_DIAG_APP_AGENT:
            IMSA_OmMsgDistr(pRcvMsg);
            break;
        #endif

        case UEPS_PID_MTC:
            IMSA_MtcMsgDistr(pRcvMsg);
            break;

        #if (FEATURE_ON == FEATURE_DSDS)
        case UEPS_PID_RRM:
            IMSA_RrmMsgDistr(pRcvMsg);
            break;
        #endif

        case PS_PID_MM:
            IMSA_LmmMsgDistr(pRcvMsg);
            break;

        /*发送对象错误，报警*/
        default:
            IMSA_WARN_LOG("IMSA_MsgHandle:NORM: Error SenderPid!");
            TLPS_PRINT2LAYER_WARNING(IMSA_MsgHandle_ENUM, LNAS_MSG_INVALID);
            break;

    }


    IMSA_WhenImsSrvConnStatusChangeNotifyMtc();
}

/*****************************************************************************
 Function Name  : IMSA_GetIntraMsgBuffAddr
 Discription    : 获取发送内部消息的地址
                  发送内部消息的过程为:
                    1.申请内部消息地址,
                    2.填充内部消息内容
                    3.发送内部消息
 Input          : 消息长度:该长度含义同DOPRA申请消息时的长度，即不包括
                    消息头 VOS_MSG_HEADER的长度
 Output         : None
 Return         : 消息地址
 History:
       1.sunbing 49683      2013-06-25  Draft Enact
*****************************************************************************/
VOS_VOID *IMSA_GetIntraMsgBuffAddr( VOS_UINT32 ulBuffSize )
{
    IMSA_INTRA_MSG_QUEUE_STRU          *pstIntraMsgQueue;
    VOS_UINT8                          *pucMsgBuff;
    IMSA_INTRA_MSG                     *pstIntraMsgHead;

    if ( (0 == ulBuffSize) || (IMSA_INTRA_MSG_MAX_SIZE < ulBuffSize ) )
    {
        /* 打印错误信息 */
        /*lint -e961*/
        IMSA_ERR_LOG1("IMSA_GetIntraMsgBuffAddr: Size error, ", ulBuffSize);
        TLPS_PRINT2LAYER_ERROR1(IMSA_GetIntraMsgBuffAddr_ENUM, 1, ulBuffSize);
        /*lint +e961*/

        return VOS_NULL_PTR;
    }

    /* 获取队列地址 */
    pstIntraMsgQueue = IMSA_GetIntraMsgQueueAddress();

    /* 验证是否队列满，留出一个消息不使用，避免正在处理的消息空间被分配出去 */
    if ( ((pstIntraMsgQueue->usTail + 1 + 1) % IMSA_INTRA_MSG_MAX_NUM) != pstIntraMsgQueue->usHeader )
    {
        pucMsgBuff = pstIntraMsgQueue->aucMsgBuff[pstIntraMsgQueue->usTail];

        /* 将申请的缓冲区清0 */
        IMSA_MEM_SET_S(pucMsgBuff, IMSA_INTRA_MSG_MAX_SIZE, 0, IMSA_INTRA_MSG_MAX_SIZE);

        /*lint -e826*/
        pstIntraMsgHead                = (IMSA_INTRA_MSG *)pucMsgBuff;
        /*lint -e826*/

        /* 填写内部消息消息头中的长度域，需要减去OSA消息头长度 */
        pstIntraMsgHead->ulLength      = ulBuffSize - 20;

        return (VOS_VOID *)pucMsgBuff;
    }
    else
    {
        /* 打印错误信息 */
        IMSA_ERR_LOG("IMSA_GetIntraMsgBuffAddr: Queue full!");
        TLPS_PRINT2LAYER_ERROR(IMSA_GetIntraMsgBuffAddr_ENUM, 2);

        return VOS_NULL_PTR;
    }

}

/*****************************************************************************
 Function Name  : IMSA_SndIntraMsg()
 Description    : IMSA内部消息发送函数
 Input          : VOS_VOID* pIntraMsg
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.sunbing 49683      2013-06-25  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_SndIntraMsg(VOS_VOID* pIntraMsg)
{
    IMSA_INTRA_MSG_QUEUE_STRU     *pstIntraMsgQueue;
    IMSA_INTRA_MSG                *pstIntraMsgHead;

    if ( VOS_NULL_PTR == pIntraMsg )
    {
        /* 打印出错信息 */
        IMSA_ERR_LOG("IMSA_SndIntraMsg: IntraMsg Null Pointer.");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndIntraMsg_ENUM, LNAS_NULL_PTR);

        return  VOS_ERR;
    }

    pstIntraMsgQueue = IMSA_GetIntraMsgQueueAddress();

    /*判断消息长度是否合法，长度要加上OSA消息头长度*/
    pstIntraMsgHead = (IMSA_INTRA_MSG*)pIntraMsg;
    if((pstIntraMsgHead->ulLength + 20)> IMSA_INTRA_MSG_MAX_SIZE)
    {
        /* 打印出错信息 */
        IMSA_ERR_LOG("IMSA_SndIntraMsg: IntraMsg Length is too long.");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndIntraMsg_ENUM, 1);

        return  VOS_ERR;
    }

    /*判断发送消息正处队尾*/
    if(pIntraMsg != pstIntraMsgQueue->aucMsgBuff[pstIntraMsgQueue->usTail])
    {
        /* 打印出错信息 */
        IMSA_ERR_LOG("IMSA_SndIntraMsg: IntraMsg Pointer is err.");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndIntraMsg_ENUM, 2);

        /*不符合逻辑，返回错误*/
        return  VOS_ERR;
    }

    /* 循环队列的队尾指向下一个位置 */
    pstIntraMsgQueue->usTail = (pstIntraMsgQueue->usTail + 1) % IMSA_INTRA_MSG_MAX_NUM;

    return VOS_OK;
}

/*****************************************************************************
 Function Name  : IMSA_GetNextIntraMsg()
 Description    : 获取一条内部消息
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT8 *

 History        :
      1.sunbing 49683      2013-06-20  Draft Enact
*****************************************************************************/
VOS_UINT8 * IMSA_GetNextIntraMsg(VOS_VOID)
{
    IMSA_INTRA_MSG_QUEUE_STRU           *pstIntraMsgQueue;
    VOS_UINT8                           *pucMsg;

    /* 获取队列地址 */
    pstIntraMsgQueue = IMSA_GetIntraMsgQueueAddress();

    /*未到队尾*/
    if(pstIntraMsgQueue->usHeader != pstIntraMsgQueue->usTail)
    {
        pucMsg = pstIntraMsgQueue->aucMsgBuff[pstIntraMsgQueue->usHeader];

        /* 取完一条消息,头指针向后偏移 */
        pstIntraMsgQueue->usHeader = (pstIntraMsgQueue->usHeader+1)%IMSA_INTRA_MSG_MAX_NUM;

        return pucMsg;
    }

    return VOS_NULL_PTR;
}

/*****************************************************************************
 Function Name  : IMSA_IntraMsgProcess()
 Description    : IMSA内部消息处理函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-20  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_IntraMsgProcess(VOS_VOID)
{
    VOS_UINT8                          *pucMsg              = VOS_NULL_PTR;

    /* 获取一条内部消息 */
    pucMsg = IMSA_GetNextIntraMsg();

    while(VOS_NULL_PTR != pucMsg)
    {
        /*勾取消息，便于HSO显示*/
        (VOS_VOID)LTE_MsgHook(pucMsg);

        /*消息处理*/
        IMSA_MsgHandle((VOS_VOID *)pucMsg);

        /* 寻找下一条内部消息 */
        pucMsg = IMSA_GetNextIntraMsg();
    }

}

/*****************************************************************************
 Function Name  : IMSA_TafMsgDistr()
 Description    : TAF消息分发函数
                  TAF这个PID下有多个模块MMA/SPM/APS，需要实现对这个模块消息的分发
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-20  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_TafMsgDistr(const VOS_VOID *pRcvMsg )
{
    /* 定义消息头指针*/
    PS_MSG_HEADER_STRU          *pHeader = VOS_NULL_PTR;

    /* 获取消息头指针*/
    pHeader = (PS_MSG_HEADER_STRU *) pRcvMsg;

    /*APS消息*/
    if(MN_CALLBACK_PS_CALL == pHeader->ulMsgName)
    {
        IMSA_CONN_ProcTafPsEvt((TAF_PS_EVT_STRU*)pRcvMsg);

        return ;
    }

    /*CALL 消息*/
    if((pHeader->ulMsgName >= ID_CALL_IMSA_SRVCC_STATUS_NOTIFY)
        &&(pHeader->ulMsgName <= ID_CALL_IMSA_MSG_TYPE_BUTT))
    {
        IMSA_ProcTafCallMsg(pRcvMsg);
        return;
    }


    /*SPM消息*/
    if ((pHeader->ulMsgName >= ID_SPM_IMSA_CALL_ORIG_REQ)
        && (pHeader->ulMsgName <= ID_SPM_IMSA_MSG_TYPE_BUTT))
    {
        IMSA_ProcSpmCallMsg(pRcvMsg);
        return;
    }

    /*短信消息*/
    if((pHeader->ulMsgName >= ID_MSG_IMSA_RP_DATA_REQ )
       &&(pHeader->ulMsgName <= ID_IMSA_MSG_TYPE_BUTT))
    {
        IMSA_ProcSmsMsg(pRcvMsg);
        return;
    }

}

/*****************************************************************************
 Function Name  : IMSA_IntraMsgDistr()
 Description    : IMSA自己发给自己的消息分发函数
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-20  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_IntraMsgDistr(const VOS_VOID *pRcvMsg )
{
    PS_MSG_HEADER_STRU                 *pstImsaIntraMsg = VOS_NULL_PTR;

    /*打印进入该函数*/
    IMSA_INFO_LOG("IMSA_IntraMsgDistr is entered.");
    TLPS_PRINT2LAYER_INFO(IMSA_IntraMsgDistr_ENUM, LNAS_ENTRY);

    pstImsaIntraMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    switch (pstImsaIntraMsg->ulMsgName)
    {
        /* CONN模块处理的相关消息 */
        case ID_IMSA_CONN_SETUP_REQ:
            IMSA_CONN_ProcConnSetupReq((IMSA_CONN_SETUP_REQ_STRU*)pRcvMsg);
            break;
        case ID_IMSA_CONN_REL_REQ:
            IMSA_CONN_ProcConnRelReq((IMSA_CONN_REL_REQ_STRU*)pRcvMsg);
            break;

        /* SERVICES模块处理的相关消息 */
        case ID_IMSA_REG_REG_IND:
            IMSA_SRV_ProcRegRegIndMsg((IMSA_REG_REG_IND_STRU *)pRcvMsg);
            break;
        case ID_IMSA_REG_DEREG_IND:
            IMSA_SRV_ProcRegDeregIndMsg((IMSA_REG_DEREG_IND_STRU *)pRcvMsg);
            break;
        case ID_IMSA_CONN_SETUP_IND:
            IMSA_SRV_ProcConnSetupIndMsg((IMSA_CONN_SETUP_IND_STRU *)pRcvMsg);
            break;
        case ID_IMSA_CONN_REL_IND:
            IMSA_SRV_ProcConnRelIndMsg((IMSA_CONN_REL_IND_STRU *)pRcvMsg);
            break;
        case ID_IMSA_CONN_MODIFY_IND:
            IMSA_SRV_ProcConnModifyIndMsg((IMSA_CONN_MODIFY_IND_STRU *)pRcvMsg);
            break;
        case ID_IMSA_CALL_RESULT_ACTION_IND:
            IMSA_SRV_ProcCallRsltActionIndMsg((IMSA_CALL_RESULT_ACTION_IND_STRU *)pRcvMsg);
            break;
        case ID_IMSA_CALL_SRVCC_SUCC_IND:
            IMSA_SRV_ProcCallSrvccSuccIndMsg((IMSA_CALL_SRVCC_SUCC_IND_STRU *)pRcvMsg);
            break;

        /* 注册模块处理的相关消息 */
        case ID_IMSA_REG_REG_REQ:
            (VOS_VOID)IMSA_RegProcUserRegReqMsg(pRcvMsg);
            break;
        case ID_IMSA_REG_DEREG_REQ:
            (VOS_VOID)IMSA_RegProcUserDeregReqMsg(pRcvMsg);
            break;

        /* 呼叫模块处理的相关消息 */
        case ID_IMSA_NRM_CALL_SRV_STATUS_IND:
            (VOS_VOID)IMSA_CallProcIntraMsgNrmCallSrvStatus(pRcvMsg);
            break;
        case ID_IMSA_EMC_CALL_SRV_STATUS_IND:
            (VOS_VOID)IMSA_CallProcIntraMsgEmcCallSrvStatus(pRcvMsg);
            break;

        default:
            IMSA_WARN_LOG("IMSA_IntraMsgDistr:Illegal Msg id!");
            TLPS_PRINT2LAYER_WARNING(IMSA_IntraMsgDistr_ENUM, LNAS_MSG_INVALID);
            break;
    }
}



/*****************************************************************************
 Function Name  : IMSA_UsimMsgDistr()
 Description    : USIM消息分发函数
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-20  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_UsimMsgDistr(const VOS_VOID *pRcvMsg )
{
    /* 定义消息头指针*/
    PS_MSG_HEADER_STRU          *pHeader = VOS_NULL_PTR;

    /* 获取消息头指针*/
    pHeader = (PS_MSG_HEADER_STRU *) pRcvMsg;

    switch(pHeader->ulMsgName)
    {
        /*读文件结果*/
        case USIMM_READFILE_CNF:
            (VOS_VOID)IMSA_ProcReadIsimFileResult((VOS_VOID*)pRcvMsg);
            break;

        /*鉴权结果*/
        case USIMM_AUTHENTICATION_CNF:
            IMSA_ProcIsimAuthRsp(pRcvMsg);
            break;

        default:
            IMSA_ERR_LOG("IMSA_UsimMsgDistr: Msg id is err.");
            TLPS_PRINT2LAYER_ERROR(IMSA_UsimMsgDistr_ENUM, LNAS_MSG_INVALID);
            break;

    }
}

/*****************************************************************************
 Function Name  : IMSA_PihMsgDistr()
 Description    : 向USIM注册后，相应主动上报消息的分发函数
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-08-28  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_PihMsgDistr(const VOS_VOID *pRcvMsg )
{
    /* 定义消息头指针*/
    PS_MSG_HEADER_STRU          *pHeader = VOS_NULL_PTR;

    /* 获取消息头指针*/
    pHeader = (PS_MSG_HEADER_STRU *) pRcvMsg;

    switch(pHeader->ulMsgName)
    {
        /*卡状态变化指示*/
        case USIMM_CARDSTATUS_IND:
            IMSA_ProcIsimStatusInd(pRcvMsg);
            break;

        /*文件刷新*/
        case USIMM_STKREFRESH_IND:
            IMSA_ProcIsimRefreshInd(pRcvMsg);
            break;

        default:
            IMSA_ERR_LOG("IMSA_PihMsgDistr: Msg id is err.");
            TLPS_PRINT2LAYER_ERROR(IMSA_PihMsgDistr_ENUM, LNAS_MSG_INVALID);
            break;

    }
}

/*****************************************************************************
 Function Name  : IMSA_VcMsgDistr()
 Description    : HIFI消息处理函数
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-07-22  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_VcMsgDistr(const VOS_VOID *pRcvMsg)
{
    /* 定义消息头指针*/
    PS_MSG_HEADER_STRU          *pHeader = VOS_NULL_PTR;

    /* 获取消息头指针*/
    pHeader = (PS_MSG_HEADER_STRU *) pRcvMsg;

    switch(pHeader->ulMsgName)
    {
        /*HIFI异常*/
        case ID_VC_IMSA_HIFI_EXCEPTION_NTF:
            IMSA_ProcHifiExceptionNtf((VOS_VOID *)pRcvMsg);
            break;

        default:
            break;
    }
}

/*****************************************************************************
 Function Name  : IMSA_AtMsgDistr()
 Description    : AT消息处理函数
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.leili 00132387      2013-10-15  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_AtMsgDistr(const VOS_VOID *pRcvMsg)
{
    /* 定义消息头指针*/
    PS_MSG_HEADER_STRU          *pHeader = VOS_NULL_PTR;

    /* 获取消息头指针*/
    pHeader = (PS_MSG_HEADER_STRU *) pRcvMsg;

    switch(pHeader->ulMsgName)
    {
        /**/
        case ID_AT_IMSA_CIREG_SET_REQ:
            IMSA_ProcMsgCiregSetReq((VOS_VOID *)pRcvMsg);
            break;
        case ID_AT_IMSA_CIREG_QRY_REQ:
            IMSA_ProcMsgCiregQryReq((VOS_VOID *)pRcvMsg);
            break;
        case ID_AT_IMSA_CIREP_SET_REQ:
            IMSA_ProcMsgCirepSetReq((VOS_VOID *)pRcvMsg);
            break;
        case ID_AT_IMSA_CIREP_QRY_REQ:
            IMSA_ProcMsgCirepQryReq((VOS_VOID *)pRcvMsg);
            break;
        case ID_AT_IMSA_VOLTEIMPU_QRY_REQ:
            IMSA_ProcMsgVolteImpuQryReq((VOS_VOID *)pRcvMsg);
            break;

        case ID_AT_IMSA_CCWAI_SET_REQ:
            IMSA_ProcMsgCcwaiSetReq((VOS_VOID *)pRcvMsg);
            break;
        default:
            break;
    }
}

#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 Function Name  : IMSA_OmMsgDistr()
 Description    : OM消息处理函数
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-01-04  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_OmMsgDistr(const VOS_VOID *pRcvMsg)
{
    /* 定义消息头指针*/
    PS_MSG_HEADER_STRU          *pHeader = VOS_NULL_PTR;

    /* 获取消息头指针*/
    pHeader = (PS_MSG_HEADER_STRU *) pRcvMsg;

    switch(pHeader->ulMsgName)
    {
        /**/
        case ID_OM_ERR_LOG_CTRL_IND:
            IMSA_RcvAcpuOmErrLogCtrlInd((VOS_VOID *)pRcvMsg);
            break;
        case ID_OM_ERR_LOG_REPORT_REQ:
            IMSA_RcvAcpuOmErrLogRptReq((VOS_VOID *)pRcvMsg);
            break;

        default:
            break;
    }
}
#endif
/*****************************************************************************
 Function Name  : IMSA_MtcMsgDistr()
 Description    : MTC消息处理函数
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.xiongxianghui 00253310   2015-01-04  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_MtcMsgDistr(const VOS_VOID *pRcvMsg)
{
    /* 定义消息头指针*/
    PS_MSG_HEADER_STRU          *pHeader = VOS_NULL_PTR;

    /* 获取消息头指针*/
    pHeader = (PS_MSG_HEADER_STRU *) pRcvMsg;

    switch(pHeader->ulMsgName)
    {
        case ID_MTC_IMSA_MODEM1_INFO_IND:
            IMSA_ProcMtcMsgModem1InfoInd(pRcvMsg);
            break;
        default:
            break;
    }
}



/*****************************************************************************
 Function Name  : IMSA_PidInit
 Discription    : IMSA的PID初始化函数
 Input          :
 Output         : None
 Return         : None
 History:
      1. sunbing 49683      2013-04-23  Draft Enact

*****************************************************************************/
VOS_UINT32 IMSA_PidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    switch( ip )
    {
        case    VOS_IP_LOAD_CONFIG:
                {
                    IMSA_Init();

                    /*向卡模块注册状态接受PID*/
                    (VOS_VOID)PIH_RegUsimCardStatusIndMsg(PS_PID_IMSA);
                }
                break;

        case    VOS_IP_FARMALLOC:
        case    VOS_IP_INITIAL:
        case    VOS_IP_ENROLLMENT:
        case    VOS_IP_LOAD_DATA:
        case    VOS_IP_FETCH_DATA:
        case    VOS_IP_STARTUP:
        case    VOS_IP_RIVAL:
        case    VOS_IP_KICKOFF:
        case    VOS_IP_STANDBY:
        case    VOS_IP_BROADCAST_STATE:
        case    VOS_IP_RESTART:
        case    VOS_IP_BUTT:
                break;

        default:
                break;
    }

    return VOS_OK;
}

/*****************************************************************************
 Function Name  : IMSVA_PidInit
 Discription    : IMSVA的PID初始化函数
 Input          :
 Output         : None
 Return         : None
 History:
      1. sunbing 49683      2013-07-15  Draft Enact

*****************************************************************************/
VOS_UINT32 IMSVA_PidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    (VOS_VOID)ip;
    return VOS_OK;
}

/*****************************************************************************
 Function Name  : IMSA_TaskEntry()
 Description    : IMSA模块TASK入口处理
 Input          : struct MsgCB* pMsg-----------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1. sunbing 49683      2013-04-23  Draft Enact

 *****************************************************************************/
VOS_VOID IMSA_TaskEntry(MsgBlock * pMsg)/*lint -e818 -e830*/
{
    /* 判断入口参数是否合法*/
    if( VOS_NULL_PTR == pMsg)
    {
        return;
    }

    /* 消息处理 */
    IMSA_MsgHandle((const VOS_VOID *)pMsg);

    /* 内部消息处理 */
    IMSA_IntraMsgProcess();
    /* IMSA消息处理完推送打印 */
    TLPS_SendPrintBufferInfo();

}

/*****************************************************************************
 Function Name  : IMSA_TaskEntry()
 Description    : IMSVA模块TASK入口处理
 Input          : struct MsgCB* pMsg-----------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1. sunbing 49683      2013-07-12  Draft Enact

 *****************************************************************************/
VOS_VOID IMSVA_TaskEntry(MsgBlock * pMsg)
{
    /* 定义消息头指针*/
    PS_MSG_HEADER_STRU          *pHeader = VOS_NULL_PTR;

    /* 判断入口参数是否合法*/
    if( VOS_NULL_PTR == pMsg)
    {
        return;
    }

    /* 获取消息头指针*/
    pHeader = (PS_MSG_HEADER_STRU *) pMsg;

    switch(pHeader->ulSenderPid)
    {
        case DSP_PID_VOICE:
            IMSVA_ProcHifiMsg(pMsg);
            break;

        case DSP_PID_VOICE_RT:
            IMSVA_ProcHifiRtMsg(pMsg);
            break;

        case VOS_PID_TIMER:
            IMSVA_TimerMsgDistr((REL_TIMER_MSG *)pMsg);
            break;

        default:
            IMSA_WARN_LOG("IMSVA_TaskEntry:NORM: Error SenderPid!");
            TLPS_PRINT2LAYER_WARNING(IMSVA_TaskEntry_ENUM, LNAS_MSG_INVALID);
            break;
    }

}

/*****************************************************************************
 Function Name  : IMSA_EmmMsgDistr()
 Description    : EMM消息处理入口
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.leixiantiao 00258641      2015-12-10  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_LmmMsgDistr(const MsgBlock * pMsg)
{
    /* 定义消息头指针*/
    PS_MSG_HEADER_STRU          *pHeader = VOS_NULL_PTR;

    /* 判断入口参数是否合法*/
    if( VOS_NULL_PTR == pMsg)
    {
        return;
    }

    /* 获取消息头指针*/
    pHeader = (PS_MSG_HEADER_STRU *) pMsg;

    switch(pHeader->ulMsgName)
    {
        case ID_LMM_IMSA_ATTACH_BEGIN_IND:
            IMSA_ProcLmmAttachBeginInd(pMsg);
            break;

        default:
            break;
    }
}

#endif

/*****************************************************************************
 Function Name  : IMSA_FidInit
 Discription    : IMSA的FID初始化函数
 Input          :
 Output         : None
 Return         : None
 History:
      1. sunbing 49683      2013-07-15  Draft Enact

*****************************************************************************/
VOS_UINT32 IMSA_FidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    VOS_UINT32                              ulRet = 0;

    (VOS_VOID)ulRet;

    switch( ip )
    {
        case    VOS_IP_LOAD_CONFIG:

                #if (FEATURE_ON == FEATURE_IMS)
                ulRet = VOS_RegisterPIDInfo(PS_PID_IMSA,
                                            IMSA_PidInit,
                                            IMSA_TaskEntry);
                if( VOS_OK != ulRet )
                {
                    return VOS_ERR;
                }


                ulRet = VOS_RegisterMsgTaskPrio(PS_FID_IMSA, VOS_PRIORITY_M5);
                if( PS_SUCC != ulRet )
                {
                    return ulRet;
                }
                #endif

                break;

        case    VOS_IP_FARMALLOC:
        case    VOS_IP_INITIAL:
        case    VOS_IP_ENROLLMENT:
        case    VOS_IP_LOAD_DATA:
        case    VOS_IP_FETCH_DATA:
        case    VOS_IP_STARTUP:
        case    VOS_IP_RIVAL:
        case    VOS_IP_KICKOFF:
        case    VOS_IP_STANDBY:
        case    VOS_IP_BROADCAST_STATE:
        case    VOS_IP_RESTART:
        case    VOS_IP_BUTT:
                break;
    }

    return VOS_OK;
}

/*****************************************************************************
 Function Name  : IMSVA_FidInit
 Discription    : IMSVA的FID初始化函数
 Input          :
 Output         : None
 Return         : None
 History:
      1. sunbing 49683      2013-07-15  Draft Enact

*****************************************************************************/
VOS_UINT32 IMSVA_FidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    VOS_UINT32                              ulRet = 0;

    (VOS_VOID)ulRet;

    switch( ip )
    {
        case    VOS_IP_LOAD_CONFIG:

                #if (FEATURE_ON == FEATURE_IMS)
                ulRet = VOS_RegisterPIDInfo(PS_PID_IMSVA,
                                            IMSVA_PidInit,
                                            IMSVA_TaskEntry);
                if( VOS_OK != ulRet )
                {
                    return VOS_ERR;
                }

                /*优先级需要比MAC上行(123)低，比MAC下行(VOS_PRIORITY_P4 126)高*/
                #if(VOS_OS_VER != VOS_WIN32)/*单板上直接指定相应的优先级，PC上dorpra没有对应API*/
                #if (VOS_RTOSCK == VOS_OS_VER)
                ulRet = VOS_RegisterTaskPrio(PS_FID_IMSVA, 31);
                #else
                ulRet = VOS_RegisterTaskPrio(PS_FID_IMSVA, 125);
                #endif
                #else
                ulRet = VOS_RegisterMsgTaskPrio(PS_FID_IMSVA, VOS_PRIORITY_P4);
                #endif
                if( PS_SUCC != ulRet )
                {
                    return ulRet;
                }
                #endif

                break;

        case    VOS_IP_FARMALLOC:
        case    VOS_IP_INITIAL:
        case    VOS_IP_ENROLLMENT:
        case    VOS_IP_LOAD_DATA:
        case    VOS_IP_FETCH_DATA:
        case    VOS_IP_STARTUP:
        case    VOS_IP_RIVAL:
        case    VOS_IP_KICKOFF:
        case    VOS_IP_STANDBY:
        case    VOS_IP_BROADCAST_STATE:
        case    VOS_IP_RESTART:
        case    VOS_IP_BUTT:
                break;
    }

    return VOS_OK;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of ImsaMain.c */



