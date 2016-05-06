

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasEmmcRcvMsg.h"
#include  "NasEmmcPublic.h"
#include  "NasEmmcSendMsg.h"
#include  "NasEmmcMain.h"
#include  "NasEmmPubUResume.h"
#include  "NasLmmPubMPrint.h"
#include  "NasLmmPubMTimer.h"
#include  "NasEmmTauSerInclude.h"
#include  "NasEmmAttDetInclude.h"
#if (FEATURE_LPP == FEATURE_ON)
#include  "NasEmmLppMsgProc.h"
#endif
#include "TlPsDrv.h"
/*end*/

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMCRCVMSG_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMCRCVMSG_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/

/*****************************************************************************
 Function Name   : NAS_EMMC_RcvEmmStartReq
 Description     : EMMC收到EMMC_EMM_START_REQ消息处理
 Input           : pMsg-------EMMC收到的消息
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.    leili  00132387      2011-2-22  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMMC_RcvEmmStartReq( MsgBlock *pMsg )
{
    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvEmmStartReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvEmmStartReq_ENUM
,LNAS_ENTRY);

    (void)pMsg;

    /* 入参检查 */
    if ( NAS_EMMC_NULL_PTR == pMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvEmmStartReq:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvEmmStartReq_ENUM
,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    NAS_EMMC_Init();

    /*发送EMMC_EMM_START_CNF消息*/
    NAS_EMMC_SendEmmStartCnf();

    return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMMC_RcvEmmStopReq
 Description     : EMMC收到EMMC_EMM_STOP_REQ消息的处理
 Input           : pMsg-----EMMC收到的消息
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    leili  00132387      2011-2-22  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMMC_RcvEmmStopReq( MsgBlock *pMsg )
{
    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvEmmStopReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvEmmStopReq_ENUM
,LNAS_ENTRY);
    (void)pMsg;

    /* 入参检查 */
    if ( NAS_EMMC_NULL_PTR == pMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvEmmStopReq:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvEmmStopReq_ENUM
,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /*发送EMMC_EMM_START_CNF消息*/
    NAS_EMMC_SendEmmStopCnf();

    return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMMC_RcvMmcPlmnSrchReq
 Description     : EMMC收到MMC_LMM_PLMN_SRCH_REQ消息的处理
 Input           : pMsg---------EMMC收到的消息
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.    leili  00132387      2011-2-21  Draft Enact
    2.    zhengjunyan 00148421 2011-11-10 MOD:添加判断条件，如果LTE被DISABLE，则
                                          丢弃MMC_LMM_PLMN_SEARCH_REQ
    3.    zhengjunyan 00148421 2011-12-07 MOD:DISABLE LTE后，响应LIST搜网
    4.    zhengjunyan 00148421 2011-12-27 MOD:连接态下不处理搜网请求
    5.    wangchen    00209181 2012-05-28 MODIFY:PlmnSrch与RRC的挂起请求对冲
    6.    liuhua      00212067 2013-02-05 使用新函数进行是否是背景LIST搜判断，
                                          新函数中增加对是否收到Not Camp On消息的判断
*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_UINT32  NAS_EMMC_RcvMmcPlmnSrchReq(MsgBlock *pMsg )
{

    MMC_LMM_PLMN_SRCH_REQ_STRU         *pstMmcPlmnReq = NAS_EMMC_NULL_PTR;
    LRRC_LNAS_PLMN_SEARCH_TYPE_ENUM_UINT32   ulPlmnType;
#if (VOS_OS_VER != VOS_WIN32)
    static VOS_UINT32  s_ulPlmnSrchReqCnt = 1;
#endif

    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvMmcPlmnSrchReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvMmcPlmnSrchReq_ENUM
,LNAS_ENTRY);

    /* 入参检查 */
    if ( NAS_EMMC_NULL_PTR == pMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvMmcPlmnSrchReq:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvMmcPlmnSrchReq_ENUM
,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /* 结构转化 */
    pstMmcPlmnReq = (MMC_LMM_PLMN_SRCH_REQ_STRU *)pMsg;

    /* 检查搜网类型 */
    ulPlmnType = NAS_LMM_MmcPlmnReqTypeCheck(pstMmcPlmnReq->enSrchType);
    if (LRRC_LNAS_PLMN_SEARCH_TYPE_BUTT == ulPlmnType)
    {
        NAS_LMM_EMMC_LOG_ERR(" NAS_EMMC_RcvMmcPlmnSrchReq: PLMN TYPE IS ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvMmcPlmnSrchReq_ENUM
,LNAS_FUNCTION_LABEL1);
        return NAS_LMM_MSG_HANDLED;
    }

    /* H00234341 FOR MMC_LIST_PLMN SRS LIST搜网请求，20130603 BEGIN */
    /*非空闲态时，回复LIST搜索拒绝.
    LMM无论是否处于空闲态，MMC均可直接下发MMC_LMM_PLMN_SEARCH_REQ要求LMM进行
    LIST搜索；
    1) 若LMM处于非空闲态，LMM回复LMM_MMC_PLMN_SEARCH_CNF，
    结果为 LIST搜索拒绝;
    2) 如果MMC在空闲态发送MMC_LMM_PLMN_SEARCH_REQ命令，但是LMM收到该消息时转到了
    建链过程中，若搜索类型为LIST,则LMM回复MMC_LMM_PLMN_SEARCH_CNF，结果为
    LIST搜索拒绝；
    20130603 BEGIN */
    /*
    if((LRRC_LNAS_PLMN_SEARCH_LIST == ulPlmnType)
        && (NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState()))
    {
        NAS_LMM_EMMC_LOG_INFO(" NAS_EMMC_RcvMmcPlmnSrchReq: PLMN LIST TYPE IS REJECT!");
        NAS_EMMC_SendMmcPlmnListSrchRej();
        return NAS_LMM_MSG_HANDLED;
    }
    */

    /* 如果当前不是IDLE态 和 NAS_EMM_CONN_RELEASING */
    /*lint -e539*/
    /*lint -e830*/
    if (NAS_EMM_YES == NAS_EMM_IsNotIdle())
    {
         /* 若是list搜索 , 则回复list拒绝 */
        if(LRRC_LNAS_PLMN_SEARCH_LIST == ulPlmnType)
        {
            NAS_LMM_EMMC_LOG_INFO(" NAS_EMMC_RcvMmcPlmnSrchReq: PLMN LIST TYPE IS REJECT!");
            TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvMmcPlmnSrchReq_ENUM
,LNAS_FUNCTION_LABEL2);
            NAS_EMMC_SendMmcPlmnListSrchRej();
        }
        else
        {   /* 若不是 list 搜索，则 丢弃此搜网请求消息 */
            NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvMmcPlmnSrchReq:Not Idle,Discard!");
            TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvMmcPlmnSrchReq_ENUM
,LNAS_FUNCTION_LABEL3);
        }

        return NAS_LMM_MSG_HANDLED;
    }
    NAS_LMM_EMMC_LOG_INFO(" NAS_EMMC_RcvMmcPlmnSrchReq: PLMN SEARCH BEGIN!");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvMmcPlmnSrchReq_ENUM
,LNAS_FUNCTION_LABEL4);
    /*lint +e830*/
    /*lint +e539*/
    /* H00234341 FOR MMC_LIST_PLMN SRS LIST搜网请求，20130603 END */

#if (VOS_OS_VER != VOS_WIN32)
    if(1 == s_ulPlmnSrchReqCnt)
    {
        (VOS_VOID) LDRV_SYSBOOT_STAMPADD("LTE Cell search start",__LINE__);
        s_ulPlmnSrchReqCnt++;
    }
#endif
    /*end*/

    /* 结构转化 */
    pstMmcPlmnReq = (MMC_LMM_PLMN_SRCH_REQ_STRU *)pMsg;

    /* 如果当前接入技术没有L或者LTE被DISABLED，则只响应LIST搜网，其他类型直接返回 */
    if((NAS_LMM_FAIL == NAS_EMM_lteRatIsExist())
     ||(NAS_LMM_SUCC == NAS_EMM_IsLteDisabled()))
    {
        if(MMC_LMM_PLMN_SRCH_LIST != pstMmcPlmnReq->enSrchType)
        {
            NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvMmcPlmnSrchReq: LTE IS NOT EXIST or LTE DISABLED");
            TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvMmcPlmnSrchReq_ENUM
,LNAS_FUNCTION_LABEL5);
            return NAS_LMM_MSG_HANDLED;
        }
    }
#if (FEATURE_ON == FEATURE_CSG)
    if (MMC_LMM_PLMN_SRCH_USER_CSG_SPEC == pstMmcPlmnReq->enSrchType)
    {
        NAS_EMMC_SetUserSpecPlmnFlag(NAS_EMMC_USER_SPEC_PLMN_YES);
    }

#endif
    if (MMC_LMM_PLMN_SRCH_USER_SPEC == pstMmcPlmnReq->enSrchType)
    {
        NAS_EMMC_SetUserSpecPlmnFlag(NAS_EMMC_USER_SPEC_PLMN_YES);
    }

    if (pstMmcPlmnReq->enSrchType != MMC_LMM_PLMN_SRCH_LIST)
    {
        /*发送EMMC_EMM_PLMN_IND消息*/
        NAS_EMMC_SendEmmPlmnInd();
    }

/* 注册/服务状态上报上移MMC，删除注册/服务状态相关代码 */
    /*发送RRC_MM_PLMN_SEARCH_REQ消息*/
    NAS_EMMC_SendRrcPlmnSrchReq(pstMmcPlmnReq);

    /* 背景lIST搜时不设置搜网标记 */
    if (VOS_FALSE == NAS_EMMC_IsBgListSearch(pstMmcPlmnReq->enSrchType))
    {
        NAS_EMMC_SetPlmnSrchFlag(NAS_EMM_PLMN_SRCH_FLAG_VALID);
        NAS_LMM_StartStateTimer(TI_NAS_EMMC_STATE_WAIT_PLMN_SRCH_CNF_TIMER);
    }

    return NAS_LMM_MSG_HANDLED;

}





/*****************************************************************************
 Function Name   : NAS_EMMC_RcvRrcPlmnSrchCnf
 Description     : EMMC收到RRC_MM_PLMN_SEARCH_CNF消息
 Input           : pMsg-------EMMC收到的消息
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.    leili  00132387      2011-2-22  Draft Enact
    2.    wangchen    00209181 2012-05-28 MODIFY:PlmnSrch与RRC的挂起请求对冲
*****************************************************************************/
VOS_UINT32  NAS_EMMC_RcvRrcPlmnSrchCnf (MsgBlock *pMsg)
{
    LRRC_LMM_PLMN_SEARCH_CNF_STRU         *pstPlmnCnf = NAS_EMMC_NULL_PTR;

    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvRrcPlmnSrchCnf is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvRrcPlmnSrchCnf_ENUM
,LNAS_ENTRY);

    /* 入参检查 */
    if ( NAS_EMMC_NULL_PTR == pMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvRrcPlmnSrchCnf:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvRrcPlmnSrchCnf_ENUM
,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /* 如果设置了搜网标识，则清除 */
    if (NAS_EMM_PLMN_SRCH_FLAG_VALID == NAS_EMMC_GetPlmnSrchFlag())
    {
        NAS_EMMC_SetPlmnSrchFlag(NAS_EMM_PLMN_SRCH_FLAG_INVALID);
        NAS_LMM_StopStateTimer(TI_NAS_EMMC_STATE_WAIT_PLMN_SRCH_CNF_TIMER);
    }

    /* 结构转化 */
    pstPlmnCnf = (LRRC_LMM_PLMN_SEARCH_CNF_STRU *)pMsg;

    /*发送LMM_MMC_PLMN_SRCH_CNF消息*/
    NAS_EMMC_SendMmcPlmnSrchCnf(pstPlmnCnf);

    return NAS_LMM_MSG_HANDLED;
}
/* 删除没有调用函数 */

VOS_UINT32 NAS_LMM_PreProcMmcLteSysInfoInd(MsgBlock *pMsg )
{
    MMC_LMM_LTE_SYS_INFO_IND_STRU      *pstLteSysInfoInd = NAS_EMMC_NULL_PTR;
    EMMC_EMM_CHANGE_INFO_ENUM_UINT32    ulChangeInfo;
    VOS_UINT32                          ulTaCellIdChangeInfo;
    /* 注册/服务状态上报上移MMC，删除注册/服务状态相关代码 */
    NAS_EMM_REJ_FLAG_ENUM_UINT32        ulMatchRslt;
    EMMC_EMM_CELL_STATUS_ENUM_UINT32    enCellStatus = EMMC_EMM_CELL_STATUS_NORMAL;
    EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32 enForbdInfo = EMMC_EMM_NO_FORBIDDEN;

    NAS_LMM_EMMC_LOG_NORM("NAS_LMM_PreProcMmcLteSysInfoInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcLteSysInfoInd_ENUM,LNAS_ENTRY);

    /* 入参检查 */
    if ( NAS_EMMC_NULL_PTR == pMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_LMM_PreProcMmcLteSysInfoInd:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_PreProcMmcLteSysInfoInd_ENUM,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /* 如果是从模，则丢弃 */
    if(NAS_EMM_IS_SUSPEND == NAS_EMM_IsSuspended())
    {
        NAS_LMM_EMMC_LOG_NORM("NAS_LMM_PreProcMmcLteSysInfoInd:EMM_MS_RRC_CONN_REL_INIT is discard");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcLteSysInfoInd_ENUM
,LNAS_FUNCTION_LABEL1);
        return NAS_LMM_MSG_HANDLED;
    }

    /* 结构转化 */
    pstLteSysInfoInd = (MMC_LMM_LTE_SYS_INFO_IND_STRU *)pMsg;

    /* 目前RRC给NAS上报的系统消息在所有场景下astSuitPlmnList都是只上报1个PLMN,
       stSpecPlmnIdList中的ulSuitPlmnNum 也只填的固定值为1*/

    /* 设置共享网络标识 */
    if (pstLteSysInfoInd->stLteSysInfo.stSpecPlmnIdList.ulSuitPlmnNum > 1)
    {
        NAS_EMMC_SetShareNetFlag(VOS_TRUE);
    }
    else
    {
        NAS_EMMC_SetShareNetFlag(VOS_FALSE);
    }

    /*NAS_EMM_SetLteNoSubscribeExtCauseFlag(NAS_EMM_EUTRAN_ALLOWED);*/

    /*TA活着CELL ID 改变*/
    NAS_EMMC_ProcessMmcLteSysInfoIndTaOrCellID( &pstLteSysInfoInd->stLteSysInfo,
                                                &ulTaCellIdChangeInfo);

    /*系统消息中的PLMN是否在拒绝#18列表中*/
    ulMatchRslt = NAS_EMMC_PlmnMatchRej18PlmnList((NAS_MM_PLMN_ID_STRU *)&pstLteSysInfoInd->stLteSysInfo.stSpecPlmnIdList.astSuitPlmnList[0]);

    /*设置当前PLMN是否在拒绝#18列表中的标识*/
    NAS_EMMC_SetRejCause18Flag(ulMatchRslt);

    NAS_LMM_EMMC_LOG1_NORM("NAS_LMM_PreProcMmcLteSysInfoInd:ulMatchRslt = ",
                                ulMatchRslt);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_PreProcMmcLteSysInfoInd_ENUM
,LNAS_FUNCTION_LABEL2,
                                ulMatchRslt);

    if ((NAS_EMM_REJ_YES == ulMatchRslt) &&
        (NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain()))
    {
        NAS_LMM_EMMC_LOG_NORM("NAS_LMM_PreProcMmcLteSysInfoInd:Reg Domain update");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcLteSysInfoInd_ENUM
,LNAS_FUNCTION_LABEL3);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    /* 判断系统消息是否发生变化*/
    NAS_EMMC_ProcessMmcLteSysInfoInd(   &pstLteSysInfoInd->stLteSysInfo,
                                        &ulChangeInfo,
                                        &enCellStatus,
                                        &enForbdInfo);

    /* The emergency number(s) received in the Emergency Number List IE are valid only in networks
        in the same country as the cell on which this IE is received.    */
    /* 通知MMC紧急呼号码列表，网侧是否支持IMS VOICE和紧急呼，以及LTE的CS域能力 */
    if (NAS_EMM_IsCountryChanged())
    {
        NAS_EMM_ClearEmergencyList();

        NAS_EMM_SendMmcInfoChangeNotify();

    }

    NAS_EMMC_SendEmmSysInfoInd(ulChangeInfo,enCellStatus,enForbdInfo);

    if (NAS_RELEASE_R11)
    {
        /* 如果PLMN发生改变，且T3402的时长来源于ATTACH REJ，则将T3402的时长设置为默认值 */
        if ((EMMC_EMM_CHANGE_PLMN == ulChangeInfo) && (NAS_EMM_T3402_SRC_ATTACH_REJ == NAS_LMM_GetT3402Src()))
        {
            if (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3402))
            {
                NAS_LMM_Stop3402Timer();
            }
            NAS_LMM_ModifyPtlTimer(TI_NAS_EMM_PTL_T3402,NAS_LMM_TIMER_T3402_LEN);
            /* T3402长度有修改，需要写入对应的全局变量 */
            g_ulEmmT3402length  = NAS_LMM_TIMER_T3402_LEN;
            NAS_LMM_SetT3402Src(NAS_EMM_T3402_SRC_OTHERS);
        }
    }

    if (EMMC_EMM_NO_CHANGE != ulChangeInfo)
    {
        NAS_LMM_EMMC_LOG_NORM("NAS_LMM_PreProcMmcLteSysInfoInd:Sys info is change");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcLteSysInfoInd_ENUM
,LNAS_FUNCTION_LABEL4);

        /*向APP发送APP_MM_REG_STAT_IND消息*/
        NAS_EMM_AppRegStatInd(NAS_LMM_GetNasAppRegState(),NAS_LMM_GetEmmCurFsmMS());
    }

   /* 注册/服务状态上报上移MMC，删除注册/服务状态相关代码 */
    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMMC_RcvRrcSysInfoInd
 Description     : EMMC收到RRC_MM_SYS_INFO_IND消息处理
 Input           : pMsg--------EMMC收到的消息
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.    leili  00132387      2011-2-24  Draft Enact
    2.    lihong 00150010      2012-12-22 Modify:DTS2012121306127，系统消息机制变更

*****************************************************************************/
VOS_UINT32  NAS_EMMC_RcvRrcSysInfoInd(MsgBlock *pMsg )
{
    LRRC_LMM_SYS_INFO_IND_STRU         *pstSysInfoInd = NAS_EMMC_NULL_PTR;

    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvRrcSysInfoInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvRrcSysInfoInd_ENUM
,LNAS_ENTRY);

    /* 入参检查 */
    if ( NAS_EMMC_NULL_PTR == pMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvRrcSysInfoInd:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvRrcSysInfoInd_ENUM
,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /* 链路释放过程中和AUTH_INIT状态正常不会收到系统消息，直接丢弃 */
    if( (NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
        || (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440))
        || (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_REATTACH_DELAY))
        || (EMM_MS_AUTH_INIT == NAS_LMM_GetEmmCurFsmMS()))
    {
        NAS_LMM_EMMC_LOG1_NORM("NAS_EMMC_RcvRrcSysInfoInd: releasing or 3440 and reattach delay is runing, discard!", NAS_EMM_GetConnState());
        TLPS_PRINT2LAYER_INFO1(NAS_EMMC_RcvRrcSysInfoInd_ENUM
,LNAS_FUNCTION_LABEL1,NAS_EMM_GetConnState());
        return NAS_LMM_MSG_HANDLED;
    }

    /* 结构转化 */
    pstSysInfoInd = (LRRC_LMM_SYS_INFO_IND_STRU *)pMsg;

    /* 清除Not Camp On标识 */
    NAS_EMMC_SetNotCampOnFlag(VOS_FALSE);

    #if (FEATURE_LPP == FEATURE_ON)
    NAS_EMM_SendLppCellChangeInd(pstSysInfoInd->ulCellId,
                                 pstSysInfoInd->ulArfcn,
                                 pstSysInfoInd->usPhysCellId,
                                 pstSysInfoInd->stSpecPlmnIdList.astSuitPlmnList[0].aucPlmnId);
    #endif

    /*发送LMM_MMC_SYS_INFO_IND消息*/
    NAS_EMMC_SendMmcSysInfo(pstSysInfoInd);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMMC_RcvMmcEplmnNotifyReq
 Description     : EMMC收到MMC_LMM_EPLMN_NOTIFY_REQ消息处理
 Input           : pMsg-------EMMC收到的消息
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-2-28  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMMC_RcvMmcEplmnNotifyReq(MsgBlock *pMsg)
{
    MMC_LMM_EPLMN_NOTIFY_REQ_STRU       *pstEplmnReq;
    NAS_MM_PLMN_LIST_STRU               *pstEPlmnList;

    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvMmcEplmnNotifyReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvMmcEplmnNotifyReq_ENUM
,LNAS_ENTRY);

    /* 入参检查 */
    if ( NAS_EMMC_NULL_PTR == pMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvMmcEplmnNotifyReq:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvMmcEplmnNotifyReq_ENUM
,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    pstEplmnReq                        = (MMC_LMM_EPLMN_NOTIFY_REQ_STRU *)pMsg;

    /* 保存等效PLMN列表 */
    pstEPlmnList = NAS_EMMC_GetEplmnListAddr();
    if(MMC_LMM_MAX_EQUPLMN_NUM < (pstEplmnReq->ulEplmnNum))
    {
        pstEPlmnList->ulPlmnNum = MMC_LMM_MAX_EQUPLMN_NUM;
        NAS_LMM_GetEmmInfoNetInfoEplmnListAddr()->ulPlmnNum = MMC_LMM_MAX_EQUPLMN_NUM;
    }
    else
    {
        pstEPlmnList->ulPlmnNum = pstEplmnReq->ulEplmnNum;
        NAS_LMM_GetEmmInfoNetInfoEplmnListAddr()->ulPlmnNum = pstEplmnReq->ulEplmnNum;
    }
    NAS_LMM_MEM_CPY_S(  &(pstEPlmnList->astPlmnId[0]),
                        sizeof(NAS_MM_PLMN_ID_STRU)*NAS_MM_MAX_PLMN_NUM,
                        &(pstEplmnReq->astEplmnList[0]),
                        sizeof(NAS_MM_PLMN_ID_STRU)*(pstEPlmnList->ulPlmnNum));
    NAS_LMM_MEM_CPY_S(  &(NAS_LMM_GetEmmInfoNetInfoEplmnListAddr()->astPlmnId[0]),
                        sizeof(NAS_MM_PLMN_ID_STRU)*NAS_MM_MAX_PLMN_NUM,
                        &(pstEplmnReq->astEplmnList[0]),
                        sizeof(NAS_MM_PLMN_ID_STRU)*(NAS_LMM_GetEmmInfoNetInfoEplmnListAddr()->ulPlmnNum));

    /*发送RRC_MM_EQU_PLMN_NOTIFY_REQ消息*/
    NAS_EMMC_SendRrcEplmnNotifyReq(pstEplmnReq);

    if(NAS_LMM_CUR_LTE_SUSPEND == NAS_EMM_GetCurLteState())
    {
        NAS_LMM_EMMC_LOG_INFO("NAS_EMMC_RcvMmcEplmnNotifyReq: SEND FORB_TA TO LRRC.");
        TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvMmcEplmnNotifyReq_ENUM
,LNAS_FUNCTION_LABEL1);
        NAS_EMMC_SendRrcCellSelectionReq(LRRC_LNAS_FORBTA_CHANGE);
    }

    return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMMC_RcvMmcStopSrchReq
 Description     : EMMC收到MMC_LMM_STOP_SRCH_REQ消息处理
 Input           : pMsg--------EMMC收到的消息
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-2-28  Draft Enact
    2.wangchen    00209181 2012-05-28 MODIFY:PlmnSrch与RRC的挂起请求对冲
*****************************************************************************/
VOS_UINT32  NAS_EMMC_RcvMmcStopSrchReq( MsgBlock *pMsg)
{
    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvMmcStopSrchReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvMmcStopSrchReq_ENUM
,LNAS_ENTRY);

    (void)pMsg;

    /* 入参检查 */
    if ( NAS_EMMC_NULL_PTR == pMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvMmcStopSrchReq:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvMmcStopSrchReq_ENUM
,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /* 如果设置了搜网标识，则清除 */
    if (NAS_EMM_PLMN_SRCH_FLAG_VALID == NAS_EMMC_GetPlmnSrchFlag())
    {
        NAS_EMMC_SetPlmnSrchFlag(NAS_EMM_PLMN_SRCH_FLAG_INVALID);
        NAS_LMM_StopStateTimer(TI_NAS_EMMC_STATE_WAIT_PLMN_SRCH_CNF_TIMER);
    }

    /*发送RRC_MM_PLMN_SEARCH_STOP_REQ消息*/
    NAS_EMMC_SendRrcPlmnSrchStopReq();

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMMC_RcvRrcPlmnSrchStopCnf
 Description     : EMMC收到RRC_MM_PLMN_SEARCH_STOP_CNF消息处理
 Input           : pMsg--------EMMC收到的消息
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-3-1  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMMC_RcvRrcPlmnSrchStopCnf(MsgBlock *pMsg)
{

    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvRrcPlmnSrchStopCnf is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvRrcPlmnSrchStopCnf_ENUM
,LNAS_ENTRY);

    (void)pMsg;

    /* 入参检查 */
    if ( NAS_EMMC_NULL_PTR == pMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvRrcPlmnSrchStopCnf:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvRrcPlmnSrchStopCnf_ENUM
,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /*发送LMM_MMC_STOP_SRCH_CNF消息*/
    NAS_EMMC_SendMmcStopSrchCnf();

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMMC_RcvRrcAreaLostInd
 Description     : EMMC收到RRC_MM_AREA_LOST_IND消息处理
 Input           : pMsg------RRC发送的消息
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-3-1  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMMC_RcvRrcAreaLostInd(MsgBlock *pMsg )
{
    LRRC_LMM_AREA_LOST_IND_STRU *pstAreaLostIndMsg = NAS_EMMC_NULL_PTR;
    MMC_LMM_AREA_LOST_REASON_UINT32 enAreaLostReason;

    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvRrcAreaLostInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvRrcAreaLostInd_ENUM
,LNAS_ENTRY);

    (void)pMsg;

    /* 入参检查 */
    if ( NAS_EMMC_NULL_PTR == pMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvRrcAreaLostInd:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvRrcAreaLostInd_ENUM
,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    pstAreaLostIndMsg = (LRRC_LMM_AREA_LOST_IND_STRU *)pMsg;

    (VOS_VOID)pstAreaLostIndMsg;

    /*转换AREA LOST REASON*/
    #if (FEATURE_ON == FEATURE_DSDS)
    if(LRRC_LNAS_RADIO_RESOURCE_AREA_LOST == pstAreaLostIndMsg->enRptMode)
    {
        enAreaLostReason = MMC_LMM_AREA_LOST_REASON_NO_RF;
    }
    else
    #endif
    {
        enAreaLostReason = MMC_LMM_AREA_LOST_REASON_NO_COVERAGE;
    }

    /* 收到area lost 后处理*/
    NAS_EMMC_ProcessRrcAreaLostInd();

    /*发送ID_EMMC_EMM_COVERAGE_LOST_IND消息*/
    NAS_EMMC_SendEmmCoverageLostInd();

    /* 如果当前CSFB延时定时器在运行，说明在REG-NORMAL态下释放过程中收到CSFB，
       但是在释放后搜小区出现丢网，此时应触发去GU搜网继续CSFB */
    if((NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_CSFB_DELAY))
        &&(VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure()))
    {
        /* 停止CSFB时延定时器 */
        NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_CSFB_DELAY);

        /* 给MMC上报SERVICE失败触发搜网去GU */
        NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);
    }

    /*发送LMM_MMC_AREA_LOST_IND消息*/
    NAS_EMMC_SendMmcAreaLostInd(enAreaLostReason, &(pstAreaLostIndMsg->stPlmnIdList), &(pstAreaLostIndMsg->stSearchedType));

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMMC_RcvMmcUserPlmnEndNotify
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-11-28  Draft Enact
    2.leili 00132387      2011-12-09  MOD:L模在挂起态时也需要处理该消息，
                                      以便给LRRC通知禁止TA信息
*****************************************************************************/
VOS_UINT32  NAS_EMMC_RcvMmcUserPlmnEndNotify(MsgBlock *pMsg )
{
    VOS_UINT32                                  i = 0;
    NAS_LMM_NETWORK_INFO_STRU                   *pstNetInfo = NAS_LMM_NULL_PTR;
    NAS_EMM_GRADUAL_FORBIDDEN_RESULT_ENUM_UINT32 enResult = NAS_EMM_GRADUAL_FORB_TA_NEED_ADD_ROAM_LIST;

    NAS_EMM_PUBU_LOG_NORM("NAS_EMMC_RcvMmcUserPlmnEndNotify is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvMmcUserPlmnEndNotify_ENUM
,LNAS_ENTRY);

    (void)pMsg;

     /* 入参检查 */
    if ( NAS_EMM_NULL_PTR == pMsg)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_EMMC_RcvMmcUserPlmnEndNotify:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvMmcUserPlmnEndNotify_ENUM
,LNAS_NULL_PTR);
        return  NAS_LMM_MSG_HANDLED;
    }

    pstNetInfo = (VOS_VOID*)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_NET_INFO);

    NAS_EMM_PUBU_LOG1_NORM("NAS_LMM_PreProcMmcUserPlmnEndNotify:Rej15 TA NUM =, ",
                               pstNetInfo->stForbTaForRej15.ulTaNum);
    TLPS_PRINT2LAYER_INFO1(NAS_EMMC_RcvMmcUserPlmnEndNotify_ENUM
,LNAS_FUNCTION_LABEL1,
                               pstNetInfo->stForbTaForRej15.ulTaNum);

    for (i = 0; i < pstNetInfo->stForbTaForRej15.ulTaNum; i++)
    {
        /* 先加入临时列表, 函数里有开关判断 */
        enResult = NAS_LMM_AddTaInGradualForbTempTaList(&pstNetInfo->stForbTaForRej15.astTa[i]);
        /* 新增判断是否要加入Roam Forb列表 */
        if ((NAS_EMM_GRADUAL_FORB_TA_NEED_ADD_ROAM_LIST == enResult)
            && (NAS_LMM_MATCH_FAIL == NAS_LMM_TaMatchTaList(&pstNetInfo->stForbTaForRej15.astTa[i], &pstNetInfo->stForbTaForRoam)))
        {
            NAS_LMM_AddTaInTaList( &pstNetInfo->stForbTaForRej15.astTa[i],
                                &pstNetInfo->stForbTaForRoam,
                                NAS_MM_MAX_TA_NUM);

        }
    }

    /*删除拒绝15 TA列表*/
    NAS_LMM_MEM_SET_S(&pstNetInfo->stForbTaForRej15, sizeof(NAS_MM_FORB_TA_LIST_STRU), 0, sizeof(NAS_MM_FORB_TA_LIST_STRU));

    /*清除用户指定搜网标识*/
    NAS_EMMC_SetUserSpecPlmnFlag(NAS_EMMC_USER_SPEC_PLMN_NO);

    NAS_EMM_PUBU_LOG1_NORM("NAS_LMM_PreProcMmcUserPlmnEndNotify:FORB TA NUM =, ",
                                  pstNetInfo->stForbTaForRoam.ulTaNum);
    TLPS_PRINT2LAYER_INFO1(NAS_EMMC_RcvMmcUserPlmnEndNotify_ENUM
,LNAS_FUNCTION_LABEL2,
                                  pstNetInfo->stForbTaForRoam.ulTaNum);

    /*发送LRRC_LMM_CELL_SELECTION_CTRL_REQ消息给RRC*/
    NAS_EMMC_SendRrcCellSelectionReq(LRRC_LNAS_FORBTA_CHANGE);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMMC_RcvMmcBgPlmnSearchReq
 Description     : EMMC收到背景搜请求后，如果当前是空闲态，则向LRRC透传
                   背景搜请求；如果不是空闲态，则丢弃此背景搜请求
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.liuhua 00212067      2012-05-22  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMMC_RcvMmcBgPlmnSearchReq(MsgBlock *pMsg)
{
    MMC_LMM_BG_PLMN_SEARCH_REQ_STRU  *pstMmcMsg = NAS_EMMC_NULL_PTR;

    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvMmcBgPlmnSearchReq: entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvMmcBgPlmnSearchReq_ENUM
,LNAS_ENTRY);

    /* 入口参数检查 */
    if (NAS_EMMC_NULL_PTR == pMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvMmcBgPlmnSearchReq: input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvMmcBgPlmnSearchReq_ENUM
,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /* 如果当前不是空闲态，则丢弃此背景搜请求 */
    if ((NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
        && (NAS_EMM_CONN_RELEASING != NAS_EMM_GetConnState())
        && (NAS_EMM_CONN_WAIT_SYS_INFO != NAS_EMM_GetConnState()))
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvMmcBgPlmnSearchReq: not idle, discard!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvMmcBgPlmnSearchReq_ENUM
,LNAS_FUNCTION_LABEL1);
        return NAS_LMM_MSG_DISCARD;
    }
    pstMmcMsg = (MMC_LMM_BG_PLMN_SEARCH_REQ_STRU *)pMsg;

    /* 向LRRC发送背景搜请求 */
    NAS_EMMC_SendRrcBgPlmnSearchReq(pstMmcMsg);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMMC_RcvMmcStopBgPlmnSearchReq
 Description     : EMMC接收到停止背景搜请求后，向LRRC透传停止背景搜请求
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.liuhua 00212067      2012-05-22  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMMC_RcvMmcStopBgPlmnSearchReq(MsgBlock *pMsg)
{
    MMC_LMM_STOP_BG_PLMN_SEARCH_REQ_STRU *pstMmcMsg;

    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvMmcStopBgPlmnSearchReq: entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvMmcStopBgPlmnSearchReq_ENUM
,LNAS_ENTRY);

    /* 入参检查 */
    if ( NAS_EMMC_NULL_PTR == pMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvMmcStopBgPlmnSearchReq: input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvMmcStopBgPlmnSearchReq_ENUM
,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    pstMmcMsg = (MMC_LMM_STOP_BG_PLMN_SEARCH_REQ_STRU *)pMsg;

    /* 向LRRC发送停止背景搜请求 */
    NAS_EMMC_SendRrcBgPlmnSearchStopReq(pstMmcMsg);

    return NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMMC_RcvRrcBgPlmnSearchCnf(MsgBlock *pMsg)
{
    LRRC_LMM_BG_PLMN_SEARCH_CNF_STRU *pLrrcMsg = NAS_LMM_NULL_PTR;

    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvRrcBgPlmnSearchCnf: entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvRrcBgPlmnSearchCnf_ENUM
,LNAS_ENTRY);

    /* 入参检查 */
    if (NAS_LMM_NULL_PTR == pMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvRrcBgPlmnSearchCnf: input null");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvRrcBgPlmnSearchCnf_ENUM
,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /* 结构转化 */
    pLrrcMsg = (LRRC_LMM_BG_PLMN_SEARCH_CNF_STRU *)pMsg;

    /* 发送LMM_MMC_BG_PLMN_SEARCH_CNF消息 */
    NAS_EMMC_SendMmcBgPlmnSearchCnf(pLrrcMsg);

    return NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMMC_RcvRrcBgPlmnSearchStopCnf(MsgBlock *pMsg)
{
    LRRC_LMM_BG_PLMN_SEARCH_STOP_CNF_STRU *pLrrcMsg = NAS_LMM_NULL_PTR;

    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvRrcBgPlmnSearchStopCnf: entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvRrcBgPlmnSearchStopCnf_ENUM
,LNAS_ENTRY);

    /* 入参检查 */
    if (NAS_EMMC_NULL_PTR == pMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvRrcBgPlmnSearchStopCnf: input null");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvRrcBgPlmnSearchStopCnf_ENUM
,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /* 结构转化 */
    pLrrcMsg = (LRRC_LMM_BG_PLMN_SEARCH_STOP_CNF_STRU *)pMsg;

    /* 发送LMM_MMC_STOP_BG_PLMN_SEARCH_CNF消息 */
    NAS_EMMC_SendMmcBgPlmnSearchStopCnf(pLrrcMsg);

    return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMMC_RcvRrcNotCampOnInd
 Description     : EMMC收到LRRC的NOT_CAMP_ON消息后，向内部发送丢网消息，
                   同时向MMC透传此消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.liuhua 00212067      2012-05-22  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMMC_RcvRrcNotCampOnInd(MsgBlock *pMsg)
{
    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvRrcNotCampOnInd: entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvRrcNotCampOnInd_ENUM
,LNAS_ENTRY);

    (VOS_VOID)pMsg;

    /* 入参检查 */
    if ( NAS_EMMC_NULL_PTR == pMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvRrcNotCampOnInd: input null");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvRrcNotCampOnInd_ENUM
,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /* 收到NOT_CAMP_ON后处理*/
    NAS_EMMC_ProcessRrcNotCampOnInd();

    /* 发送ID_EMMC_EMM_COVERAGE_LOST_IND消息 */
    /* NAS_EMMC_SendEmmCoverageLostInd(); */

    /* 发送LMM_MMC_NOT_CAMP_ON_IND消息 */
    NAS_EMMC_SendMmcNotCampOnInd();

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMMC_RcvRrcSearchPlmnInfoInd
 Description     : 收到LRRC上报的搜网信息，透传给MMC
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151     2014-11-20  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMMC_RcvRrcSearchPlmnInfoInd(MsgBlock *pMsg)
{
    LRRC_LMM_SEARCHED_PLMN_INFO_IND_STRU *pLrrcMsg = NAS_LMM_NULL_PTR;

    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvRrcSearchPlmnInfoInd: entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvRrcSearchPlmnInfoInd_ENUM,LNAS_ENTRY);

    /* 入参检查 */
    if (NAS_EMMC_NULL_PTR == pMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvRrcSearchPlmnInfoInd: input null");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvRrcSearchPlmnInfoInd_ENUM,LNAS_MSG_INVALID);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /* 结构转化 */
    pLrrcMsg = (LRRC_LMM_SEARCHED_PLMN_INFO_IND_STRU *)pMsg;

    /* 发送LMM_MMC_SEARCHED_PLMN_INFO_IND消息 */
    NAS_EMMC_SendMmcSearchPlmnInfoInd(pLrrcMsg);

    return NAS_LMM_MSG_HANDLED;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 Function Name   : NAS_EMMC_RcvRrcBgSearchHrpdCnf
 Description     : EMMC收到ID_LRRC_LMM_BG_SEARCH_HRPD_CNF消息的处理
 Input           : pMsg-----EMMC收到的消息
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMMC_RcvRrcBgSearchHrpdCnf(MsgBlock *pMsg)
{
    LRRC_LMM_BG_SEARCH_HRPD_CNF_STRU    *pstBgSearchCnf = NAS_EMMC_NULL_PTR;

    pstBgSearchCnf = (LRRC_LMM_BG_SEARCH_HRPD_CNF_STRU*)pMsg;

    /* 向MMC发送背景搜EHRPD的结果消息 */
    NAS_EMMC_SendMmcBgSearchHrpdCnf(pstBgSearchCnf);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMMC_RcvRrcBgSearchHrpdStopCnf
 Description     : EMMC收到ID_LRRC_LMM_BG_SEARCH_HRPD_STOP_CNF消息的处理
 Input           : pMsg-----EMMC收到的消息
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMMC_RcvRrcBgSearchHrpdStopCnf(MsgBlock *pMsg)
{
    /* 向MMC发送停止背景搜EHRPD的CNF消息 */
    NAS_EMMC_SendMmcStopBgSearchHrpdCnf();

    return NAS_LMM_MSG_HANDLED;
}
#endif


/*****************************************************************************
 Function Name   : NAS_EMMC_RcvMmcCellSelectionReq
 Description     : EMMC收到MMC_LMM_CELL_SELECTION_REQ消息
 Input           : pMsg-----EMMC收到的消息
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387     2011-3-3  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMMC_RcvMmcCellSelectionReq(  MsgBlock *pMsg )
{
    MMC_LMM_CELL_SELECTION_CTRL_REQ_STRU    *pstCellSelReq;
    LRRC_LNAS_RESEL_TYPE_ENUM_UINT32          ulReselType;

    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvMmcCellSelectionReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvMmcCellSelectionReq_ENUM
,LNAS_ENTRY);

    /* 入参检查 */
    if ( NAS_EMMC_NULL_PTR == pMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvMmcCellSelectionReq:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvMmcCellSelectionReq_ENUM
,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /* 结构转化 */
    pstCellSelReq = (MMC_LMM_CELL_SELECTION_CTRL_REQ_STRU *)pMsg;

    if (MMC_LMM_RESEL_SUITABLE == pstCellSelReq->ulSelecType)
    {
        NAS_LMM_EMMC_LOG1_NORM("NAS_EMMC_RcvMmcCellSelectionReq: Cell type = ",
                                pstCellSelReq->ulSelecType);
        TLPS_PRINT2LAYER_INFO1(NAS_EMMC_RcvMmcCellSelectionReq_ENUM
,LNAS_FUNCTION_LABEL1,
                                pstCellSelReq->ulSelecType);
        ulReselType = LRRC_LNAS_RESEL_SUITABLE;
    }
    else
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvMmcCellSelectionReq:Input Cell type is err! ");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_RcvMmcCellSelectionReq_ENUM
,LNAS_FUNCTION_LABEL2);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;
    }


    /*发送RRC_MM_CELL_SELECTION_CTRL_REQ消息*/
    NAS_EMMC_SendRrcCellSelectionReq(ulReselType);

    return NAS_LMM_MSG_HANDLED;
}
/*lint +e961*/
/*lint +e960*/

VOS_UINT32 NAS_EMMC_RcvMmcGsmSysInfoInd(MsgBlock *pMsg )
{
    MMC_LMM_GSM_SYS_INFO_IND_STRU      *pstGsmSysInfoInd = NAS_EMMC_NULL_PTR;

    /* 如果L模当前处于激活态，则不处理GU的SYS_INFO,直接丢弃*/
    if(NAS_LMM_CUR_LTE_SUSPEND != NAS_EMM_GetCurLteState())
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMMC_RcvMmcGsmSysInfoInd:LTE is not SUSPEND.");
        TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvMmcGsmSysInfoInd_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_LMM_MSG_HANDLED;
    }

    pstGsmSysInfoInd                    = (MMC_LMM_GSM_SYS_INFO_IND_STRU*)pMsg;

    /*保存GU系统消息中的网络信息*/
    NAS_EMMC_GetGuSysInfoAddr()->bitOpRac   = pstGsmSysInfoInd->bitOpRac;
    NAS_EMMC_GetGuSysInfoAddr()->ucRac      = pstGsmSysInfoInd->ucRac;
    NAS_EMMC_GetGuSysInfoAddr()->usLac      = pstGsmSysInfoInd->usLac;
    NAS_EMMC_GetGuSysInfoAddr()->ulCellId   = pstGsmSysInfoInd->ulCellId;
    NAS_EMMC_GetGuSysInfoPlmnAddr()->aucPlmnId[0] = pstGsmSysInfoInd->stPlmnId.aucPlmnId[0];
    NAS_EMMC_GetGuSysInfoPlmnAddr()->aucPlmnId[1] = pstGsmSysInfoInd->stPlmnId.aucPlmnId[1];
    NAS_EMMC_GetGuSysInfoPlmnAddr()->aucPlmnId[2] = pstGsmSysInfoInd->stPlmnId.aucPlmnId[2];

    /*保存GSM制式*/
    NAS_EMMC_GetGuSysInfoAddr()->ucRatType  = 0 ;


    /*收到GU系统消息,停止运行的T3402以及T3411 */
    NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3411);

    /*问题背景:主叫走CSFB流程被用户快速挂断电话，此时走CSFB回退流程，
    回退到L的时候，由于TA在TALIST里面，所以不会发起TAU跟网侧交互，但是
    此时核心网PS域已经开始往2/3G迁移，这样会导致被叫不通，或者收不到短信
    改动:增加标识维护识别上面的这种场景，在回到L的时候保证发起TAU*/
    NAS_EMM_SetCsfbProcedureFlag(PS_FALSE);

    /* 收到系统消息后，判断LAI是否发生变化 */
    NAS_LMM_SetEmmInfoLaiChangeFlag(NAS_MML_IsCsLaiChanged());

/*lint -e960*/
/* GCF测试情况下如果3402在运行不停止3402，也不必清次数，待3402超时后自然会清，
   3411定时器先不修改，暂还按照原来的停止处理 */
#if (VOS_OS_VER != VOS_WIN32)
    if(PS_SUCC == LPS_OM_IsTestMode())
    {
        if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3402))
        {
           return NAS_LMM_MSG_HANDLED;
        }
    }
#endif
/*lint +e960*/

    NAS_LMM_Stop3402Timer();

    NAS_EMM_TAU_SaveEmmTAUAttemptCnt(0);

    NAS_EMM_AttResetAttAttempCounter();

    return NAS_LMM_MSG_HANDLED;
}


VOS_UINT32 NAS_EMMC_RcvMmcUmtsSysInfoInd(MsgBlock *pMsg )
{
    MMC_LMM_WCDMA_SYS_INFO_IND_STRU    *pstUmtsSysInfoInd = NAS_EMMC_NULL_PTR;

    /* 如果L模当前处于激活态，则不处理GU的SYS_INFO,直接丢弃*/
    if(NAS_LMM_CUR_LTE_SUSPEND != NAS_EMM_GetCurLteState())
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMMC_RcvMmcUmtsSysInfoInd:LTE is not SUSPEND.");
        TLPS_PRINT2LAYER_INFO(NAS_EMMC_RcvMmcUmtsSysInfoInd_ENUM
,LNAS_FUNCTION_LABEL1);
        return NAS_LMM_MSG_HANDLED;
    }

    pstUmtsSysInfoInd                   = (MMC_LMM_WCDMA_SYS_INFO_IND_STRU*)pMsg;

    /*保存GU系统消息中的网络信息*/
    NAS_EMMC_GetGuSysInfoAddr()->bitOpRac   = pstUmtsSysInfoInd->bitOpRac;
    NAS_EMMC_GetGuSysInfoAddr()->ucRac      = pstUmtsSysInfoInd->ucRac;
    NAS_EMMC_GetGuSysInfoAddr()->usLac      = pstUmtsSysInfoInd->usLac;
    NAS_EMMC_GetGuSysInfoAddr()->ulCellId   = pstUmtsSysInfoInd->ulCellId;
    NAS_EMMC_GetGuSysInfoPlmnAddr()->aucPlmnId[0] = pstUmtsSysInfoInd->stPlmnId.aucPlmnId[0];
    NAS_EMMC_GetGuSysInfoPlmnAddr()->aucPlmnId[1] = pstUmtsSysInfoInd->stPlmnId.aucPlmnId[1];
    NAS_EMMC_GetGuSysInfoPlmnAddr()->aucPlmnId[2] = pstUmtsSysInfoInd->stPlmnId.aucPlmnId[2];

    /*保存UMTS制式*/
    NAS_EMMC_GetGuSysInfoAddr()->ucRatType  = 1 ;


    /*收到GU系统消息,停止运行的T3402以及T3411 */
    NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3411);

    /*问题背景:主叫走CSFB流程被用户快速挂断电话，此时走CSFB回退流程，
    回退到L的时候，由于TA在TALIST里面，所以不会发起TAU跟网侧交互，但是
    此时核心网PS域已经开始往2/3G迁移，这样会导致被叫不通，或者收不到短信
    改动:增加标识维护识别上面的这种场景，在回到L的时候保证发起TAU*/
    NAS_EMM_SetCsfbProcedureFlag(PS_FALSE);

    /* 收到系统消息后，判断LAI是否发生变化 */
    NAS_LMM_SetEmmInfoLaiChangeFlag(NAS_MML_IsCsLaiChanged());

/*lint -e960*/
/* GCF测试情况下如果3402在运行不停止3402，也不必清次数，待3402超时后自然会清，
   3411定时器先不修改，暂还按照原来的停止处理 */
#if (VOS_OS_VER != VOS_WIN32)
    if(PS_SUCC == LPS_OM_IsTestMode())
    {
        if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3402))
        {
           return NAS_LMM_MSG_HANDLED;
        }
    }
#endif
/*lint +e960*/

    NAS_LMM_Stop3402Timer();

    NAS_EMM_TAU_SaveEmmTAUAttemptCnt(0);

    NAS_EMM_AttResetAttAttempCounter();

    return NAS_LMM_MSG_HANDLED;
}


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 Function Name   : NAS_EMMC_RcvMmcBgSearchHrpdReq
 Description     : EMMC收到ID_MMC_LMM_BG_SEARCH_HRPD_REQ消息的处理
 Input           : pMsg-----EMMC收到的消息
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMMC_RcvMmcBgSearchHrpdReq(MsgBlock *pMsg)
{
    /* 如果当前不是空闲态，则丢弃此背景搜请求 */
    if ((NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
        && (NAS_EMM_CONN_RELEASING != NAS_EMM_GetConnState())
        && (NAS_EMM_CONN_WAIT_SYS_INFO != NAS_EMM_GetConnState()))
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvMmcBgSearchHrpdReq: not idle, discard!");
        return NAS_LMM_MSG_DISCARD;
    }

    /* 向LRRC发送背景搜EHRPD请求消息 */
    NAS_EMMC_SendRrcBgSearchHrpdReq();

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMMC_RcvMmcStopBgSearchHrpdReq
 Description     : EMMC收到ID_MMC_LMM_STOP_BG_SEARCH_HRPD_REQ消息
 Input           : pMsg-----EMMC收到的消息
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMMC_RcvMmcStopBgSearchHrpdReq(MsgBlock *pMsg)
{
    /* 向LRRC发送停止背景搜EHRPD请求 */
    NAS_EMMC_SendRrcBgSearchHrpdStopReq();

    return NAS_LMM_MSG_HANDLED;
}
#endif

#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 Function Name   : NAS_EMMC_RcvMmcCsgWhiteListNotify
 Description     : EMMC收到ID_MMC_LMM_CSG_WHITE_LIST_NOTIFY消息的处理
 Input           : pMsg-----EMMC收到的消息
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.yanglei 00307272    2015-09-10   Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_EMMC_RcvMmcCsgWhiteListNotify(MsgBlock *pMsg)
{
    MMC_LMM_CSG_WHITE_LIST_NOTIFY_STRU           *pstCsgWhiteList = VOS_NULL_PTR;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMMC_RcvMmcCsgWhiteListNotify Enter.");
    TLPS_PRINT2LAYER_INFO(  NAS_EMMC_RcvMmcCsgWhiteListNotify_ENUM,
                            LNAS_ENTRY);

    pstCsgWhiteList = (MMC_LMM_CSG_WHITE_LIST_NOTIFY_STRU *)pMsg;
    NAS_EMMC_SendRrcCsgWhiteListNotify(pstCsgWhiteList);
    return NAS_LMM_MSG_HANDLED;
}
/*****************************************************************************
 Function Name   : NAS_EMMC_RcvMmcCsgListSearchReq
 Description     : EMMC收到ID_MMC_LMM_CSG_LIST_SEARCH_REQ消息的处理
 Input           : pMsg-----EMMC收到的消息
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.yanglei 00307272    2015-10-27   Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMMC_RcvMmcCsgListSearchReq(MsgBlock *pMsg)
{
    MMC_LMM_CSG_LIST_SEARCH_REQ_STRU             *pstMmcCsgPlmnReq = NAS_EMMC_NULL_PTR;

    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvMmcCsgListSearchReq is entered.");
    TLPS_PRINT2LAYER_INFO(  NAS_EMMC_RcvMmcCsgListSearchReq_ENUM,
                            LNAS_ENTRY);

    if ((NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
        && (NAS_EMM_CONN_RELEASING != NAS_EMM_GetConnState())
        && (NAS_EMM_CONN_WAIT_SYS_INFO != NAS_EMM_GetConnState()))
    {


        NAS_LMM_EMMC_LOG_INFO(" NAS_EMMC_RcvMmcCsgListSearchReq: PLMN LIST TYPE IS REJECT!");
        TLPS_PRINT2LAYER_INFO(  NAS_EMMC_RcvMmcCsgListSearchReq_ENUM,
                                LNAS_FUNCTION_LABEL1);
        NAS_EMMC_SendMmcCsgListSrchRej();

        return NAS_LMM_MSG_HANDLED;
    }
    NAS_LMM_EMMC_LOG_INFO(" NAS_EMMC_RcvMmcCsgListSearchReq: PLMN SEARCH BEGIN!");
    TLPS_PRINT2LAYER_INFO(  NAS_EMMC_RcvMmcCsgListSearchReq_ENUM,
                            LNAS_FUNCTION_LABEL2);

    /* 结构转化 */
    pstMmcCsgPlmnReq = (MMC_LMM_CSG_LIST_SEARCH_REQ_STRU *)pMsg;

    /*发送消息*/
    NAS_EMMC_SendRrcCsgListSrchReq(pstMmcCsgPlmnReq);

    /* 背景CSG lIST搜时不设置搜网标记 */
    if (VOS_FALSE == NAS_EMMC_IsBgCsgListSearch())
    {
        NAS_EMMC_SetPlmnSrchFlag(NAS_EMM_PLMN_SRCH_FLAG_VALID);
        NAS_LMM_StartStateTimer(TI_NAS_EMMC_STATE_WAIT_PLMN_SRCH_CNF_TIMER);
    }

    return NAS_LMM_MSG_HANDLED;
}
/*****************************************************************************
 Function Name   : NAS_EMMC_RcvMmcCsgBgPlmnSearchReq
 Description     : EMMC收到CSG背景搜请求后，如果当前是空闲态，则向LRRC透传
                   CSG背景搜请求；如果不是空闲态，则丢弃此背景搜请求
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.yanglei 00307272      2015-10-27  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMMC_RcvMmcCsgBgPlmnSearchReq(MsgBlock *pMsg)
{
    MMC_LMM_CSG_BG_SEARCH_REQ_STRU  *pstMmcMsg = NAS_EMMC_NULL_PTR;

    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvMmcCsgBgPlmnSearchReq: entered.");
    TLPS_PRINT2LAYER_INFO(  NAS_EMMC_RcvMmcCsgBgPlmnSearchReq_ENUM,
                            LNAS_ENTRY);

    /* 如果当前不是空闲态，则丢弃此背景搜请求 */
    if ((NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
        && (NAS_EMM_CONN_RELEASING != NAS_EMM_GetConnState())
        && (NAS_EMM_CONN_WAIT_SYS_INFO != NAS_EMM_GetConnState()))
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_RcvMmcCsgBgPlmnSearchReq: not idle, discard!");
        TLPS_PRINT2LAYER_ERROR( NAS_EMMC_RcvMmcCsgBgPlmnSearchReq_ENUM,
                                LNAS_FUNCTION_LABEL1);
        return NAS_LMM_MSG_DISCARD;
    }

    pstMmcMsg = (MMC_LMM_CSG_BG_SEARCH_REQ_STRU *)pMsg;

    /* 向LRRC发送背景搜请求 */
    NAS_EMMC_SendRrcCsgBgSearchReq(pstMmcMsg);

    return NAS_LMM_MSG_HANDLED;
}

VOS_UINT32  NAS_EMMC_RcvRrcCsgBgPlmnSearchCnf(MsgBlock *pMsg)
{
    LRRC_LMM_CSG_BG_SEARCH_CNF_STRU *pstCsgBgSrchCnfMsg = NAS_LMM_NULL_PTR;

    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvRrcCsgBgPlmnSearchCnf: entered");
    TLPS_PRINT2LAYER_INFO(  NAS_EMMC_RcvRrcCsgBgPlmnSearchCnf_ENUM,
                            LNAS_ENTRY);

    /* 结构转化 */
    pstCsgBgSrchCnfMsg = (LRRC_LMM_CSG_BG_SEARCH_CNF_STRU *)pMsg;

    /* 发送ID_LMM_MMC_CSG_BG_SEARCH_CNF消息 */
    NAS_EMMC_SendMmcCsgBgSearchCnf(pstCsgBgSrchCnfMsg);

    return NAS_LMM_MSG_HANDLED;

}

VOS_UINT32  NAS_EMMC_RcvRrcCsgListSrchCnf (MsgBlock *pMsg)
{
    LRRC_LMM_CSG_LIST_SEARCH_CNF_STRU         *pstCsgListSrchCnfMsg = NAS_EMMC_NULL_PTR;

    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvRrcCsgListSrchCnf is entered.");
    TLPS_PRINT2LAYER_INFO(  NAS_EMMC_RcvRrcCsgListSrchCnf_ENUM,
                            LNAS_ENTRY);

    /* 如果设置了搜网标识，则清除 */
    if (NAS_EMM_PLMN_SRCH_FLAG_VALID == NAS_EMMC_GetPlmnSrchFlag())
    {
        NAS_EMMC_SetPlmnSrchFlag(NAS_EMM_PLMN_SRCH_FLAG_INVALID);
        NAS_LMM_StopStateTimer(TI_NAS_EMMC_STATE_WAIT_PLMN_SRCH_CNF_TIMER);
    }

    /* 结构转化 */
    pstCsgListSrchCnfMsg = (LRRC_LMM_CSG_LIST_SEARCH_CNF_STRU *)pMsg;

    /*发送ID_LMM_MMC_CSG_LIST_SEARCH_CNF消息*/
    NAS_EMMC_SendMmcCsgListSrchCnf(pstCsgListSrchCnfMsg);

    return NAS_LMM_MSG_HANDLED;
}

VOS_UINT32  NAS_EMMC_RcvRrcCsgIdHomeNodeBNameInd (MsgBlock *pMsg)
{
    LRRC_LMM_CSG_ID_HOME_NODEB_NAME_IND_STRU         *pstCsgHomeNodeBMsg = NAS_EMMC_NULL_PTR;

    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_RcvRrcCsgListSrchCnf is entered.");
    TLPS_PRINT2LAYER_INFO(  NAS_EMMC_RcvRrcCsgIdHomeNodeBNameInd_ENUM,
                            LNAS_ENTRY);

    /* 结构转化 */
    pstCsgHomeNodeBMsg = (LRRC_LMM_CSG_ID_HOME_NODEB_NAME_IND_STRU *)pMsg;

    /*发送LMM_MMC_PLMN_SRCH_CNF消息*/
    NAS_EMMC_SendMmcCsgIdHomeNodeBNameInd(pstCsgHomeNodeBMsg);

    return NAS_LMM_MSG_HANDLED;
}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif









