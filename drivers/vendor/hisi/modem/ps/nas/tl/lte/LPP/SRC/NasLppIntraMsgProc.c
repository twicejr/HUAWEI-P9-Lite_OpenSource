/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasLppIntraMsgProc.c
  版 本 号   : 初稿
  作    者   : XiaoJun
  生成日期   : 2015年7月30日
  最近修改   :
  功能描述   : LPP 模块的内部消息处理
  函数列表   :
  修改历史   :
  1.日    期   : 2015年7月30日
    作    者   : XiaoJun
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "NasLppPublic.h"
#include  "NasLppSendMsg.h"
#include  "NasLppIntraInterface.h"
#include  "NasLppOm.h"

#if (FEATURE_LPP == FEATURE_ON)
extern LPP_UPLINK_MSG_BUF_STRU*  NAS_LPP_GetLppMsgUpBuffByOpId
(
    VOS_UINT32              ulLmmLppOpId
);
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#define    THIS_FILE_ID            PS_FILE_ID_NASLPPINTRAMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLPPINTRAMSGPROC_C


/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 Function Name   : NAS_LPP_ReleaseTransactionOrSession
 Description     : 释放transaction或者session的逻辑
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.lifuxin 00253982      2015-10-22  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_ReleaseTransactionOrSession
(
    VOS_UINT8                       ucSessionIndx,
    VOS_UINT8                       ucSessionTransIndx,
    NAS_LPP_TRANS_ID_STRU          *pstTransId
)
{
    if( PS_FALSE == NAS_LPP_IsThereOtherTransactionRunningInSession(ucSessionIndx, pstTransId) )
    {
        NAS_LPP_WARN_LOG("NAS_LPP_ReleaseTransactionOrSession:No running transaction, Release this session!");
        TLPS_PRINT2LAYER_WARNING(NAS_LPP_ReleaseTransactionOrSession_ENUM, LNAS_LPP_NoRunningTransReleaseSession);
        NAS_LPP_ReleaseSessionEntityByIndex(ucSessionIndx);
    }
    else
    {
        NAS_LPP_WARN_LOG("NAS_LPP_ReleaseTransactionOrSession: Have other transaction, Just release this Transaction!");
        TLPS_PRINT2LAYER_WARNING(NAS_LPP_ReleaseTransactionOrSession_ENUM, LNAS_LPP_HaveOtherTransJustReleaseThisTrans);
        NAS_LPP_ReleaseTransEntity(ucSessionIndx, ucSessionTransIndx);
    }

    return;
}
/*****************************************************************************
 Function Name   : NAS_LPP_RcvIntraDataCnf
 Description     : 处理内部data cnf消息
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-20  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LPP_RcvIntraDataCnf( NAS_LPP_INTRA_DATA_CNF_STRU *pRcvMsg)
{
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU    *pstTransEntity;
    VOS_UINT8                                   ucSessionIndex = PS_NULL_UINT8;
    VOS_UINT8                                   ucSessionTransIndx = PS_NULL_UINT8;
    NAS_LPP_SUB_STATE_ENUM_UINT32 enSubState;
    LPP_UPLINK_MSG_BUF_STRU  *pstUplinkMsgBuff = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_RcvIntraDataCnf enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvIntraDataCnf_ENUM, LNAS_LPP_Func_Enter);

    NAS_LPP_OmIntraDataCnf(pRcvMsg);

    ucSessionIndex = NAS_LPP_SearchSessionIndx(pRcvMsg->stLppMsgIdentity.ulSessionId);
    if (ucSessionIndex >= NAS_LPP_MAX_SESSION_COUNT)
    {
        NAS_LPP_NORM_LOG("NAS_LPP_RcvIntraDataCnf: can't find the session !");
        TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvIntraDataCnf_ENUM, LNAS_LPP_CanntFindSession);
        return;
    }

    /*先搜索到对应的SESSION和TRANSACTION*/
    pstTransEntity = NAS_LPP_SearchTransEntity(pRcvMsg->stLppMsgIdentity.ulSessionId,
                                             &(pRcvMsg->stLppMsgIdentity.stTransId),
                                              &ucSessionTransIndx);
    if(NAS_LPP_NULL_PTR == pstTransEntity)
    {
        /* 在收到冲突消息时(辅助数据冲突)，都会给网侧回复ACK，但是在这个时候并没有创建transaction，只释放缓存消息空间 */
        pstUplinkMsgBuff = NAS_LPP_GetLppMsgUpBuffByOpId(pRcvMsg->ulOpId);
        if(NAS_LPP_NULL_PTR == pstUplinkMsgBuff)
        {
            NAS_LPP_ERR_LOG("NAS_LPP_AckDataCnfSuccHandle: No buffer!");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvIntraDataCnf_ENUM, LNAS_LPP_CantFindUpBuff);
            return;
        }

        NAS_LPP_RelUpMsgBuffer(&pstUplinkMsgBuff);
        NAS_LPP_NORM_LOG("NAS_LPP_RcvIntraDataCnf: Null!");
        TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvIntraDataCnf_ENUM, LNAS_LPP_CanntFindTransaction);
        return;
    }

    /*停止所有的session的流程*/
    if (NAS_LPP_CONN_MANAGE_FAIL == pRcvMsg->enRslt)
    {
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvIntraDataCnf_ENUM, LNAS_LPP_ConnManageFail);
        /* NAS_LPP_ReleaseAllSession(); */
        NAS_LPP_ReleaseTransactionOrSession(ucSessionIndex,
                                            ucSessionTransIndx,
                                          &(pstTransEntity->stTransId));

        return;
    }

    pstUplinkMsgBuff = NAS_LPP_GetLppMsgUpBuffByOpId(pRcvMsg->ulOpId);
    if(NAS_LPP_NULL_PTR == pstUplinkMsgBuff)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_AckDataCnfSuccHandle: No buffer!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvIntraDataCnf_ENUM, LNAS_LPP_CantFindUpBuff);
        return;
    }

    /*根据搜索到的TRANSACTION取当前的状态机状态，确定是否是要执行的消息:如果不是，退出*/
    if (NAS_LPP_SUCCESS != NAS_LPP_TransFsmCheck(pstTransEntity->enLppMainState,
                                                 pstTransEntity->enLppSubState,
                                                 (PS_MSG_HEADER_STRU *)pRcvMsg) )
    {
        NAS_LPP_ERR_LOG2("intra data msg not match fsm, Main State,SubState",
                          pstTransEntity->enLppMainState,
                          pstTransEntity->enLppSubState);
        TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvIntraDataCnf_ENUM, LNAS_LPP_MainStat);
        TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvIntraDataCnf_ENUM, LNAS_LPP_SubStat);
        return;
    }

    /*如果本transaction是在等待上行LPP ACK(对下行LPP ABORT /LPP ERROR)发送完成的状态*/
    if ( LPP_SS_WAIT_INTRA_DATA_CNF_OF_UP_LPP_ACK == pstTransEntity->enLppSubState )
    {
        /*如果当前收到的的intra data cnf是对应下行abort或者error的回复，则根据场景清空session等*/
        NAS_LPP_WARN_LOG("NAS_LPP_RcvIntraDataCnf: Dn Abort or Error Msg's Up Lpp Ack!");
        TLPS_PRINT2LAYER_WARNING(NAS_LPP_RcvIntraDataCnf_ENUM, LNAS_LPP_DnAbortOrErrorMsgAndCnfUpLppAck);
        NAS_LPP_AbortAndErrorProcess(ucSessionIndex,
                                     ucSessionTransIndx,
                                     &(pRcvMsg->stLppMsgIdentity.stTransId));
        return;
    }

    /*结束本transaction的*/
    if (NAS_LPP_SUCCESS != pRcvMsg->enRslt)
    {
        /*收到的intra data cnf非成功的原因值，走释放session*/
        NAS_LPP_WARN_LOG("NAS_LPP_RcvIntraDataCnf: Intra Data cnf fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_LPP_RcvIntraDataCnf_ENUM, LNAS_LPP_IntraDataCnfFail);

        NAS_LPP_ReleaseTransactionOrSession(ucSessionIndex,
                                            ucSessionTransIndx,
                                            &(pstUplinkMsgBuff->stLppMsgIdentity.stTransId));
    }
    else if (PS_TRUE == pstTransEntity->ucTransEndFlag)
    {
        /*upbuffer可能有2条LPPMSG: LPP ACK +  up lpp msg;满足此条件，肯定只有
          一个LPP ACK在发送，没有其他消息, 比如网侧下发辅助数据的场景*/
        if (NAS_LPP_AIR_MSG_UP_LPP_ACK == pstTransEntity->enLastUpMsgId)
        {
            NAS_LPP_WARN_LOG("NAS_LPP_RcvIntraDataCnf: Only One Ack Msg!");
            TLPS_PRINT2LAYER_WARNING(NAS_LPP_RcvIntraDataCnf_ENUM, LNAS_LPP_OnlyOneAckMsg);
            NAS_LPP_ReleaseTransactionOrSession(ucSessionIndex,
                                                ucSessionTransIndx,
                                                &(pstUplinkMsgBuff->stLppMsgIdentity.stTransId));

            return;
        }

        if(  NAS_LPP_UPLINK_MSG_TYPE_ACK == pstUplinkMsgBuff->stLppMsgIdentity.enUplinkMsgType)
        {
            /*这个分支的场景比如当前是网络侧下发能力请求，UE同时发送上行ACK，以及provideCap，
            此时收到ack的data cnf，需要释放对应的ack的buff*/
            NAS_LPP_WARN_LOG("NAS_LPP_RcvIntraDataCnf: Have two upMsg!");
            TLPS_PRINT2LAYER_WARNING(NAS_LPP_RcvIntraDataCnf_ENUM, LNAS_LPP_HaveTwoUpMsg);

            NAS_LPP_RelUpMsgBuffer(&pstUplinkMsgBuff);
            return;
        }
    }
    else
    {
        if (  NAS_LPP_UPLINK_MSG_TYPE_ACK == pstUplinkMsgBuff->stLppMsgIdentity.enUplinkMsgType)
        {
            /*transaction还没有结束，仅仅释放对应ACK的buff即可*/
            NAS_LPP_WARN_LOG("NAS_LPP_RcvIntraDataCnf: Not End And Normal Ack Msg!");
            TLPS_PRINT2LAYER_WARNING(NAS_LPP_RcvIntraDataCnf_ENUM, LNAS_LPP_NotEndNormalAckMsg);

            NAS_LPP_RelUpMsgBuffer(&pstUplinkMsgBuff);
            return;
        }
        else
		{

        }

    }

    /*成功的流程:转换状态机，启动等待ACK的定时器*/
    enSubState = NAS_LPP_GetWaitAckSubState( pstTransEntity->enLastUpMsgId, pstTransEntity->enLppMainState);
    NAS_LPP_INFO_LOG2("NAS_LPP_RcvIntraDataCnf: MainState, SubState", pstTransEntity->enLppMainState, enSubState);
    NAS_LPP_ChangeTransFsmState(ucSessionIndex, ucSessionTransIndx, pstTransEntity->enLppMainState, enSubState );
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvIntraDataCnf_ENUM, LNAS_LPP_MainStat);
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvIntraDataCnf_ENUM, LNAS_LPP_SubStat);
}

/*****************************************************************************
 Function Name   : NAS_LPP_LppMsgDistr
 Description     : LPP模块给LPP模块自己发的内部消息的处理入口函数
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_LppMsgDistr( VOS_VOID *pRcvMsg )
{
    NAS_LPP_INTRA_MSG_STRU *pstIntraMsg = NAS_LPP_NULL_PTR;

    NAS_LPP_INFO_LOG("NAS_LPP_LppMsgDistr enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_LppMsgDistr_ENUM, LNAS_LPP_Func_Enter);

    pstIntraMsg = (NAS_LPP_INTRA_MSG_STRU*)pRcvMsg;

    /*根据消息名，调用相应的消息处理函数*/
    switch ( pstIntraMsg->ulMsgId )
    {
        case ID_NAS_LPP_INTRA_DATA_CNF :
            NAS_LPP_RcvIntraDataCnf((NAS_LPP_INTRA_DATA_CNF_STRU *)pstIntraMsg);
            break;

        default:
            NAS_LPP_INFO_LOG("NAS_LPP_LppMsgDistr: Error Msg id!");
            TLPS_PRINT2LAYER_INFO(NAS_LPP_LppMsgDistr_ENUM, LNAS_LPP_ErrorSenderPid);
            break;
    }

    return;
}









#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

