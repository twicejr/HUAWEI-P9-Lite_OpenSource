



/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/

#include    "NasEmmAttDetInclude.h"
#include    "NasLmmPubMPrint.h"
#include    "LNasStkInterface.h"
#include    "LmmCssInterface.h"
#include    "NasLmmPubMEntry.h"

#if ( FEATURE_LPP == FEATURE_ON )
#include    "NasEmmSsMsgProc.h"
#endif

#include "NasMmlCtx.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMATTACHCNMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMATTACHCNMSGPROC_C
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
NAS_LMM_REJ_CAUSE_PROC_STRU  gstEmmAttRejCauseProcTbl[]=
{
    {NAS_LMM_CAUSE_IMEI_NOT_ACCEPTED,                       NAS_EMM_ProcRejCauseVal5},
    {NAS_LMM_CAUSE_ILLEGAL_UE,                              NAS_EMM_ProcRejCauseVal3678},
    {NAS_LMM_CAUSE_ILLEGAL_ME,                              NAS_EMM_ProcRejCauseVal3678},
    {NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW,                      NAS_EMM_ProcRejCauseVal3678},
    {NAS_LMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW,     NAS_EMM_ProcRejCauseVal3678},
    {NAS_LMM_CAUSE_PLMN_NOT_ALLOW,                          NAS_EMM_ProcRejCauseVal11},
    {NAS_LMM_CAUSE_TA_NOT_ALLOW,                            NAS_EMM_ProcRejCauseVal12},
    {NAS_LMM_CAUSE_ROAM_NOT_ALLOW,                          NAS_EMM_ProcRejCauseVal13},
    {NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN,              NAS_EMM_ProcRejCauseVal14},
    {NAS_LMM_CAUSE_NO_SUITABL_CELL,                         NAS_EMM_ProcRejCauseVal15},
#if(FEATURE_ON == FEATURE_CSG)
    {NAS_LMM_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG,             NAS_EMM_ProcRejCauseVal25},
#endif
    {NAS_LMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN,NAS_EMM_ProcRejCauseVal35},
    {NAS_LMM_CAUSE_SERVER_NETWORK_FAILURE,                  NAS_EMM_ProcRejCauseVal42}
};

VOS_UINT32        gstEmmAttRejCauseProcTblLen = sizeof(gstEmmAttRejCauseProcTbl)
                                                / sizeof(NAS_LMM_REJ_CAUSE_PROC_STRU);


/*****************************************************************************
  3 Function
*****************************************************************************/
/*lint -e960*/

/*****************************************************************************
 Function Name   : NAS_EMM_CnAttachAccMsgChk
 Description     : 检查空口消息ATTACH ACCEPT的消息内容是否正确
 Input           :
 Output          :
 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact
    2.zhengjunyan 00148421   2010-11-03  MOD:添加判断:如果UE没有GUTI，且ATTACH ACP
                                         中没有GUTI，则返回PARA_INVALID

*****************************************************************************/
VOS_UINT32  NAS_EMM_CnAttachAcpMsgChk(const NAS_EMM_CN_ATTACH_ACP_STRU  *pMsgMsg)
{

    NAS_LMM_UEID_STRU                   *pstEmmInfoUeIdAddr = VOS_NULL_PTR;

    /* EPS attach result合法性检查*/
    if ((NAS_EMM_CN_MSG_ATTACH_TYPE_PS != pMsgMsg->ucAttachRst)
       &&(NAS_EMM_CN_MSG_ATTACH_TYPE_PS_CS != pMsgMsg->ucAttachRst))
    {
        return  NAS_EMM_PARA_INVALID;
    }

    /* UE没有GUTI，网络也没有分配GUTI*/
    pstEmmInfoUeIdAddr =                NAS_LMM_GetEmmInfoUeidAddr();
    if((NAS_EMM_BIT_NO_SLCT == pMsgMsg->ucBitOpGuti)
      &&(NAS_EMM_BIT_NO_SLCT == pstEmmInfoUeIdAddr->bitOpGuti))
    {
        /*发送EMM STATUS, 接收到conditional IE错误的消息 */
        NAS_EMM_SendMsgEmmStatus( NAS_LMM_CAUSE_CONDITIONAL_IE_ERROR );
        return  NAS_EMM_PARA_INVALID;
    }

    return NAS_EMM_PARA_VALID;

}

/*****************************************************************************
 Function Name   : NAS_EMM_CnAttachRejMsgChk
 Description     : 检查空口消息ATTACH REJECT的消息内容是否正确
 Input           :
 Output          :
 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_CnAttachRejMsgChk(const NAS_EMM_CN_ATTACH_REJ_STRU *pMsgMsg)
{

    /*消息内容检查 */

    (VOS_VOID)pMsgMsg;
    return  NAS_EMM_PARA_VALID;


}


/*****************************************************************************
 Function Name   : NAS_EMM_EsmSendEstCnf
 Description     : 向ESM发送ID_EMM_ESM_EST_CNF消息

 Input           :
 Output          :
 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
/*lint -e960*/
VOS_VOID    NAS_EMM_EsmSendEstCnf (EMM_ESM_ATTACH_STATUS_ENUM_UINT32 ucEstRst)
{
    EMM_ESM_EST_CNF_STRU                 *pEmmEsmEstCnfMsg;


    /*申请消息内存*/
    pEmmEsmEstCnfMsg   = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(EMM_ESM_EST_CNF_STRU));

    /*判断申请结果，若失败退出*/
    if (NAS_EMM_NULL_PTR == pEmmEsmEstCnfMsg)
    {
        return;
    }

    /*构造ID_EMM_ESM_EST_CNF消息*/
    /*填充消息头*/
    NAS_EMM_COMP_AD_ESM_MSG_HEADER(      pEmmEsmEstCnfMsg,
                                        (sizeof(EMM_ESM_EST_CNF_STRU)-
                                        NAS_EMM_LEN_VOS_MSG_HEADER));

    /*填充消息ID*/
    pEmmEsmEstCnfMsg->ulMsgId            = ID_EMM_ESM_EST_CNF;

    /*填充消息内容*/
    pEmmEsmEstCnfMsg->ulEstRst           = ucEstRst;

    /*向ESM发送ID_EMM_ESM_EST_CNF消息*/
    NAS_LMM_SEND_MSG(                   pEmmEsmEstCnfMsg);

    return;

}


/*****************************************************************************
 Function Name   : NAS_EMM_EsmSendDataInd
 Description     : 向ESM发送ID_EMM_ESM_DATA_IND
                   (ACTIVATE DEFAULT EPS BEARER REQUEST)消息

 Input           :
 Output          :
 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_EMM_EsmSendDataInd (const NAS_EMM_CN_MSGCON_STRU *pstEsmBearerReq)
{
    EMM_ESM_DATA_IND_STRU                *pEmmEsmBearerReqMsg;
    VOS_UINT32                          ulEsmMsgLen;
    VOS_UINT32                          ulDataIndLenNoHeader;


    ulEsmMsgLen                          = pstEsmBearerReq->ulMsgLen;
    ulDataIndLenNoHeader                = NAS_EMM_CountEsmDataIndLen(ulEsmMsgLen);


    /*申请消息内存*/
    if (ulEsmMsgLen < 4)
    {
        pEmmEsmBearerReqMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(EMM_ESM_DATA_IND_STRU));

    }
    else
    {
        pEmmEsmBearerReqMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(
                                        ulDataIndLenNoHeader + NAS_EMM_LEN_VOS_MSG_HEADER);
    }

    /*判断申请结果，若失败退出*/
    if (NAS_EMM_NULL_PTR == pEmmEsmBearerReqMsg)
    {
        return;
    }

    /*构造ID_EMM_ESM_DATA_IND消息*/
    /*填充消息头*/
    NAS_EMM_COMP_AD_ESM_MSG_HEADER(pEmmEsmBearerReqMsg, ulDataIndLenNoHeader);

    /*填充消息ID*/
    pEmmEsmBearerReqMsg->ulMsgId         = ID_EMM_ESM_DATA_IND;

    /*填充消息内容*/
    pEmmEsmBearerReqMsg->stEsmMsg.ulEsmMsgSize = pstEsmBearerReq->ulMsgLen;

    NAS_LMM_MEM_CPY_S(  pEmmEsmBearerReqMsg->stEsmMsg.aucEsmMsg,
                        pstEsmBearerReq->ulMsgLen,
                        pstEsmBearerReq->aucMsg,
                        pstEsmBearerReq->ulMsgLen);

    /*向ESM发送ID_EMM_ESM_DATA_IND消息*/
    NAS_LMM_SEND_MSG(                   pEmmEsmBearerReqMsg);

    return;

}
/*****************************************************************************
 Function Name  : NAS_LMM_SendCssStartInd()
 Description    : LMM通知CSS开机消息
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-14  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_SendCssStartInd
(
    VOS_VOID
)
{
    LMM_CSS_START_IND_STRU             *pstLmmCssStartInd;

    /*分配消息空间*/
    pstLmmCssStartInd = (VOS_VOID*)NAS_LMM_ALLOC_MSG(sizeof(LMM_CSS_START_IND_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstLmmCssStartInd)
    {
        /*打印异常信息*/
        NAS_EMM_ATTACH_LOG_ERR("LMM_SendCssStartInd:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_SendCssStartInd_ENUM,LNAS_NULL_PTR);
        return ;
    }

    NAS_LMM_MEM_SET_S(  pstLmmCssStartInd,
                        sizeof(LMM_CSS_START_IND_STRU),
                        0,
                        sizeof(LMM_CSS_START_IND_STRU));

    NAS_EMM_COMP_AD_CSS_PS_MSG_HEADER(pstLmmCssStartInd,
                                    (sizeof(LMM_CSS_START_IND_STRU)-
                                    NAS_EMM_LEN_VOS_MSG_HEADER));

    pstLmmCssStartInd->ulMsgId = ID_LMM_CSS_START_IND;

    /*调用消息发送函数 */
    NAS_LMM_SEND_MSG(pstLmmCssStartInd);


    return ;
}

/*****************************************************************************
 Function Name  : NAS_LMM_SendCssStoptInd()
 Description    : LMM通知CSS关机消息
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-14  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_SendCssStopInd
(
    VOS_VOID
)
{
    LMM_CSS_STOP_IND_STRU              *pstLmmCssStopInd;

    /*分配消息空间*/
    pstLmmCssStopInd = (VOS_VOID*)NAS_LMM_ALLOC_MSG(sizeof(LMM_CSS_STOP_IND_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstLmmCssStopInd)
    {
        /*打印异常信息*/
        NAS_EMM_ATTACH_LOG_ERR("LMM_SendCssStoptInd:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_SendCssStopInd_ENUM,LNAS_NULL_PTR);
        return ;
    }

    NAS_LMM_MEM_SET_S(  pstLmmCssStopInd,
                        sizeof(LMM_CSS_STOP_IND_STRU),
                        0,
                        sizeof(LMM_CSS_STOP_IND_STRU));

    NAS_EMM_COMP_AD_CSS_PS_MSG_HEADER(pstLmmCssStopInd,
                                    (sizeof(LMM_CSS_STOP_IND_STRU)-
                                    NAS_EMM_LEN_VOS_MSG_HEADER));

    pstLmmCssStopInd->ulMsgId = ID_LMM_CSS_STOP_IND;

    /*调用消息发送函数 */
    NAS_LMM_SEND_MSG(pstLmmCssStopInd);


    return ;
}

/*****************************************************************************
 Function Name   : NAS_EMM_EsmSendStopNotifyInd
 Description     : 向ESM发送ID_EMM_ESM_STOP_NOTIFY_IND消息

 Input           :
 Output          :
 Return          :

 History         :
    1.wangchen 00209181     2014-09-05  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_EMM_EsmSendStopNotifyInd (VOS_VOID)
{
    EMM_ESM_STOP_NOTIFY_IND_STRU                *pEmmEsmStopNotifyMsg;

    pEmmEsmStopNotifyMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(EMM_ESM_STOP_NOTIFY_IND_STRU));

    /*判断申请结果，若失败打印错误并退出*/
    if (NAS_EMM_NULL_PTR == pEmmEsmStopNotifyMsg)
    {
        /*打印错误*/
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_EsmSendStopNotifyInd: MSG ALLOC ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EsmSendStopNotifyInd_ENUM,LNAS_NULL_PTR);
        return;

    }

    /*构造ID_EMM_ESM_DATA_IND消息*/
    /*填充消息头*/
    NAS_EMM_COMP_AD_ESM_MSG_HEADER(pEmmEsmStopNotifyMsg,
                                    (sizeof(EMM_ESM_STOP_NOTIFY_IND_STRU)-
                                    NAS_EMM_LEN_VOS_MSG_HEADER));

    /*填充消息ID*/
    pEmmEsmStopNotifyMsg->ulMsgId         = ID_EMM_ESM_STOP_NOTIFY_IND;

    /*向ESM发送ID_EMM_ESM_STOP_NOTIFY_IND消息*/
    NAS_LMM_SEND_MSG(                   pEmmEsmStopNotifyMsg);

    return;

}

/*****************************************************************************
 Function Name   : NAS_EMM_TcSendDataInd
 Description     : 向TC发送ID_EMM_ETC_DATA_IND消息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-10-16  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_TcSendDataInd
(
    const NAS_EMM_CN_MSGCON_STRU       *pstTcMsg
)
{
    EMM_ETC_DATA_IND_STRU               *pEmmTcDataIndMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulTcMsgLen;
    VOS_UINT32                          ulDataIndLenNoHeader;


    ulTcMsgLen                          = pstTcMsg->ulMsgLen;
    ulDataIndLenNoHeader                = NAS_EMM_CountTcDataIndLen(ulTcMsgLen);


    /*申请消息内存*/
    if (ulTcMsgLen < 4)
    {
        pEmmTcDataIndMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(EMM_ETC_DATA_IND_STRU));

    }
    else
    {
        pEmmTcDataIndMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(
                                        ulDataIndLenNoHeader + NAS_EMM_LEN_VOS_MSG_HEADER);
    }

    /*判断申请结果，若失败退出*/
    if (NAS_EMM_NULL_PTR == pEmmTcDataIndMsg)
    {
        return;
    }

    /*构造ID_EMM_ETC_DATA_IND消息*/
    /*填充消息头*/
    NAS_EMM_COMP_AD_TC_MSG_HEADER(pEmmTcDataIndMsg, ulDataIndLenNoHeader);

    /*填充消息ID*/
    pEmmTcDataIndMsg->ulMsgId         = ID_EMM_ETC_DATA_IND;

    /*填充消息内容*/
    pEmmTcDataIndMsg->stTcMsg.ulTcMsgSize = pstTcMsg->ulMsgLen;


    NAS_LMM_MEM_CPY_S(  pEmmTcDataIndMsg->stTcMsg.aucTcMsg,
                        pstTcMsg->ulMsgLen,
                        pstTcMsg->aucMsg,
                        pstTcMsg->ulMsgLen);

    /*向TC发送ID_EMM_ETC_DATA_IND消息*/
    NAS_LMM_SEND_MSG(                   pEmmTcDataIndMsg);

    /* 打印发送消息 */
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_TcSendDataInd:NORM:Send ID_EMM_ETC_DATA_IND!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TcSendDataInd_ENUM,LNAS_END);
}

/*****************************************************************************
 Function Name   : NAS_EMM_CountEsmDataIndLen
 Description     : 计算ID_EMM_ESM_DATA_IND消息长度

 Input           :
 Output          :
 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_CountEsmDataIndLen(VOS_UINT32 ulNasEsmMsgLen)
{
    VOS_UINT32                          ulMsgLen;

    ulMsgLen                          = NAS_EMM_AD_LEN_MSG_ID                      +
                                        NAS_EMM_AD_LEN_IE_MSGSIZE_OF_NAS_MSG_STRU  +
                                        (ulNasEsmMsgLen);

    return ulMsgLen;

}
/*****************************************************************************
 Function Name   : NAS_EMM_CountTcDataIndLen
 Description     : 计算ID_EMM_ETC_DATA_IND消息长度

 Input           : ulNasTcMsgLen------TC消息长度
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010         2009-10-16  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_CountTcDataIndLen(VOS_UINT32 ulNasTcMsgLen)
{
    VOS_UINT32                          ulMsgLen;

    ulMsgLen                          = NAS_EMM_AD_LEN_MSG_ID                      +
                                        NAS_EMM_AD_LEN_IE_MSGSIZE_OF_NAS_MSG_STRU  +
                                        (ulNasTcMsgLen);

    return ulMsgLen;

}
/*****************************************************************************
 Function Name   : NAS_EMM_AttDataUpdate
 Description     :
 Input           :
 Output          :
 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact
    2.zhengjunyan 148421     2009-09-23  BJ9D01922:ATTACH REJ #14协议不要求
                                          reset attach attempt counter
    3.zhengjunyan 00148421   2011-12-13  MOD:删除KSIasme修改为删除所有安全上下文
*****************************************************************************/

VOS_VOID    NAS_EMM_AttDataUpdate(VOS_UINT32 ulDeleteRplmn)
{

    /*设置 EPS update status为EU3*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    /*删除GUTI*/
    NAS_EMM_ClearGuti();

    /*删除LVR TAI*/
    if (NAS_EMM_DELETE_RPLMN == ulDeleteRplmn)
    {
        NAS_EMM_ClearLVRTai();
    }
    else
    {
        NAS_EMM_SetLVRTacInvalid();
    }

    /*删除KSIasme*/
    /*NAS_EMM_ClearCurSecuCntxt();*/
    NAS_EMM_ClearAllSecuCntxt();

    if((NAS_LMM_CAUSE_PLMN_NOT_ALLOW == NAS_EMM_GLO_AD_GetAttRejCau()) ||
       (NAS_LMM_CAUSE_TA_NOT_ALLOW == NAS_EMM_GLO_AD_GetAttRejCau()) ||
       (NAS_LMM_CAUSE_ROAM_NOT_ALLOW == NAS_EMM_GLO_AD_GetAttRejCau()) ||
       (NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN == NAS_EMM_GLO_AD_GetAttRejCau()) ||
       (NAS_LMM_CAUSE_NO_SUITABL_CELL == NAS_EMM_GLO_AD_GetAttRejCau()))
    {
        /*清除ATTACH ATTEMPTING COUNTER计数器*/
        NAS_EMM_AttResetAttAttempCounter();
    }

    /* 将无效的安全上下文直接在函数内部写卡 */
    NAS_LMM_WriteEpsSecuContext(NAS_NV_ITEM_UPDATE);
    /*保存PS LOC信息*/
    NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);

    return;

}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcRejCauseVal2
 Description     : 原因值为#2的处理
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2011-7-5  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcRejCauseVal2(VOS_VOID)
{

    /*清除ATTACH ATTEMPTING COUNTER和TRACKING AREA UPDATING ATTEMPT计数器*/
    NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);

    /*设置EPS UPDATE STAUS为EU1*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_UPDATED_EU1);


    /*启动定时器TI_NAS_EMM_WAIT_ESM_BEARER_CNF*/
    NAS_LMM_StartStateTimer(            TI_NAS_EMM_WAIT_ESM_BEARER_CNF);

    /*修改状态：进入主状态REG_INIT子状态ATTACH_WAIT_ESM_BEARER_CNF*/
    NAS_EMM_AdStateConvert(             EMM_MS_REG_INIT,
                                        EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF,
                                        TI_NAS_EMM_WAIT_ESM_BEARER_CNF);
    /* leixiantiao 00258641v 2015-03-15 begin */
    /* 上报EPS LOC信息 */
    NAS_EMM_SndOmLogEpsLocInfo();
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcRejCauseVal5
 Description     : 对ATTACH拒绝原因值#5的处理

 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong 00150010         2012-10-30  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_EMM_ProcRejCauseVal5(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal)
{
    (VOS_VOID)ucRejCauseVal;

    /*向ESM发送ATTACH结果*/
    NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_DETACHED);

    /* 自研CL版本，PS DETACH通知ESM删除所有EHRPD相关承载记录 */
    NAS_EMM_SndEsmClearAllClBearerNotify();

    /*修改状态：进入主状态DEREG子状态DEREG_LIMITED_SERVICE*/
    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                EMM_SS_DEREG_NO_IMSI,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /* 向MMC发送结果 */
    NAS_EMM_AppSendAttRej();

    /*向MRRC发送NAS_EMM_MRRC_REL_REQ消息*/
    NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);

    /* 通知IMSA不再尝试CS域 */

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcRejCauseVal3678
 Description     : 对ATTACH拒绝原因值#3#6#7#8的处理

 Input           :
 Output          :
 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_EMM_ProcRejCauseVal3678(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal)
{
    (VOS_VOID)ucRejCauseVal;

    NAS_EMM_AttDataUpdate(NAS_EMM_DELETE_RPLMN);

    NAS_LMM_SetPsSimValidity(NAS_LMM_SIM_INVALID);

    if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
    {
        /* 通知ESM紧接着EMM还要做紧急注册，ESM不需要清除动态表中的紧急PDN建立记录 */
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
    }
    else
    {
        /*向ESM发送ATTACH结果*/
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_DETACHED);

        /* 自研CL版本，PS DETACH通知ESM删除所有EHRPD相关承载记录 */
        NAS_EMM_SndEsmClearAllClBearerNotify();
    }

    /*修改状态：进入主状态DEREG子状态DEREG_LIMITED_SERVICE*/
    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                EMM_SS_DEREG_NO_IMSI,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /* 向MMC发送结果 */
    NAS_EMM_AppSendAttRej();

    /*向LRRC发送LRRC_LMM_NAS_INFO_CHANGE_REQ携带USIM卡状态*/
    NAS_EMM_SendUsimStatusToRrc(LRRC_LNAS_USIM_PRESENT_INVALID);

    /*向MRRC发送NAS_EMM_MRRC_REL_REQ消息*/
    NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);

    if (EMM_ATTACH_CAUSE_ESM_EMC_ATTACH == NAS_EMM_GLO_AD_GetAttCau())
    {
        /* 通知IMSA再尝试CS域 */
    }

    /* 清除之前记录的attach原因值 */
    NAS_LMM_ClearEmmInfoMmcAttachReason();

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_ProcRejCauseVal11
 Description     : 对ATTACH拒绝原因值#11的处理

 Input           :
 Output          :
 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_EMM_ProcRejCauseVal11(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal)
{
    (VOS_VOID)ucRejCauseVal;

    NAS_EMM_AttDataUpdate(NAS_EMM_NOT_DELETE_RPLMN);

    if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
    {
        /* 通知ESM紧接着EMM还要做紧急注册，ESM不需要清除动态表中的紧急PDN建立记录 */
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
    }
    else
    {
        /*向ESM发送ATTACH结果*/
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_DETACHED);
    }

    /*修改状态：进入主状态DEREG子状态DEREG_LIMITED_SERVICE*/
    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                EMM_SS_DEREG_LIMITED_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /* 向MMC发送结果 */
    NAS_EMM_AppSendAttRej();

    NAS_EMM_WaitNetworkRelInd();

    if (EMM_ATTACH_CAUSE_ESM_EMC_ATTACH == NAS_EMM_GLO_AD_GetAttCau())
    {
        /* 通知IMSA再尝试CS域 */
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcRejCauseVal12
 Description     : 对ATTACH拒绝原因值#12的处理

 Input           :
 Output          :
 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_EMM_ProcRejCauseVal12(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal)
{
    NAS_MM_TA_STRU                      stTa;

    (VOS_VOID)ucRejCauseVal;

    /* 获取当前TA */
    NAS_EMM_GetCurrentTa(&stTa);

    NAS_EMM_AttDataUpdate(NAS_EMM_NOT_DELETE_RPLMN);

    NAS_EMM_AddForbTa(&stTa,NAS_LMM_GetEmmInfoNetInfoForbTaForRposAddr());
    /* 注册/服务状态上报上移MMC，删除注册/服务状态相关代码 */
    if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
    {
        /* 通知ESM紧接着EMM还要做紧急注册，ESM不需要清除动态表中的紧急PDN建立记录 */
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
    }
    else
    {
        /*向ESM发送ATTACH结果*/
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_DETACHED);
    }

    /*修改状态：进入主状态DEREG子状态DEREG_LIMITED_SERVICE*/
    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                EMM_SS_DEREG_LIMITED_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /* 向MMC发送结果 */
    NAS_EMM_AppSendAttRej();

    NAS_EMM_WaitNetworkRelInd();

    if (EMM_ATTACH_CAUSE_ESM_EMC_ATTACH == NAS_EMM_GLO_AD_GetAttCau())
    {
        /* 通知IMSA再尝试CS域 */
    }

    return;

}


/*****************************************************************************
 Function Name   : NAS_EMM_ProcRejCauseVal13
 Description     : 对ATTACH拒绝原因值#13的处理

 Input           :
 Output          :
 Return          :

 History         :
    1.leili    00132387      2008-09-09  Draft Enact
    2.liuhua   00212067      2012-05-30  Notify RRC when TA is added into
                                         forbidden list for roaming
*****************************************************************************/
VOS_VOID    NAS_EMM_ProcRejCauseVal13(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal)
{
    NAS_MM_TA_STRU                      stTa;

    (VOS_VOID)ucRejCauseVal;

    /* 获取当前TA */
    NAS_EMM_GetCurrentTa(&stTa);

    NAS_EMM_AttDataUpdate(NAS_EMM_NOT_DELETE_RPLMN);

    /* 需要把当前TA从临时列表中剔除 */
    NAS_LMM_DelCurrTaFromGradualForbTaList(&stTa);

    NAS_EMM_AddForbTa(&stTa,NAS_LMM_GetEmmInfoNetInfoForbTaForRoamAddr());
    NAS_EMMC_SendRrcCellSelectionReq(LRRC_LNAS_FORBTA_CHANGE);

    if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
    {
        /* 通知ESM紧接着EMM还要做紧急注册，ESM不需要清除动态表中的紧急PDN建立记录 */
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
    }
    else
    {
        /*向ESM发送ATTACH结果*/
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_DETACHED);
    }

    /*修改状态：进入主状态DEREG子状态DEREG_LIMITED_SERVICE*/
    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                EMM_SS_DEREG_LIMITED_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /* 向MMC发送结果 */
    NAS_EMM_AppSendAttRej();

    NAS_EMM_WaitNetworkRelInd();

    if (EMM_ATTACH_CAUSE_ESM_EMC_ATTACH == NAS_EMM_GLO_AD_GetAttCau())
    {
        /* 通知IMSA再尝试CS域 */
    }

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_ProcRejCauseVal14
 Description     : 对ATTACH拒绝原因值#14的处理

 Input           :
 Output          :
 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_EMM_ProcRejCauseVal14(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal)
{
    (VOS_VOID)ucRejCauseVal;

    NAS_EMM_AttDataUpdate(NAS_EMM_NOT_DELETE_RPLMN);

    if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
    {
        /* 通知ESM紧接着EMM还要做紧急注册，ESM不需要清除动态表中的紧急PDN建立记录 */
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
    }
    else
    {
        /*向ESM发送ATTACH结果*/
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_DETACHED);
    }

    /*修改状态：进入主状态DEREG子状态DEREG_LIMITED_SERVICE*/
    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                EMM_SS_DEREG_LIMITED_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /* 向MMC发送结果 */
    NAS_EMM_AppSendAttRej();

    NAS_EMM_WaitNetworkRelInd();

    if (EMM_ATTACH_CAUSE_ESM_EMC_ATTACH == NAS_EMM_GLO_AD_GetAttCau())
    {
        /* 通知IMSA再尝试CS域 */
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcRejCauseVal15
 Description     :对ATTACH拒绝原因值#15的处理

 Input           :
 Output          :
 Return          :

 History         :
    1.leili    00132387      2008-09-09  Draft Enact
    2.liuhua   00212067      2012-05-30  Notify RRC when TA is added into
                                         forbidden list for roaming
*****************************************************************************/
VOS_VOID    NAS_EMM_ProcRejCauseVal15(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal)
{
    /* 删掉无用变量 */
    MMC_LMM_LTE_NO_SUBSCRIBE_PLMN_LIST_STRU  stLteNoSubsPlmnList;
    VOS_UINT32                               ulIsNeedExecLteNotAllow = NAS_EMM_YES;

    (VOS_VOID)ucRejCauseVal;

    /* 删掉无用代码 */

    NAS_EMM_AttDataUpdate(NAS_EMM_NOT_DELETE_RPLMN);

    /* Forb Ta列表维护移到下面4G未开户判断分支维护 */

    if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
    {
        /* 通知ESM紧接着EMM还要做紧急注册，ESM不需要清除动态表中的紧急PDN建立记录 */
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
    }
    else
    {
        /*向ESM发送ATTACH结果*/
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_DETACHED);
    }

    /*修改状态：进入主状态DEREG子状态DEREG_LIMITED_SERVICE*/
    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                EMM_SS_DEREG_LIMITED_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /* 向MMC发送结果 */
    NAS_EMM_AppSendAttRej();

    /*被15拒绝，当前PLMN只有一个*/
    stLteNoSubsPlmnList.ulPlmnNum = 1;

    /*拷贝当前PLMN*/
    NAS_LMM_MEM_CPY_S(  &(stLteNoSubsPlmnList.astPlmnId[0]),
                        sizeof(MMC_LMM_PLMN_ID_STRU),
                        NAS_LMM_GetEmmInfoPresentPlmnAddr(),
                        sizeof(MMC_LMM_PLMN_ID_STRU));

    /*如果网络侧带了扩展原因值，而且当前对应值是EUTRAN NOT ALLOW，则走正常的协议流程*/
    if((NAS_EMM_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetAttRejEmmExtCau())
        &&(NAS_EMM_EUTRAN_NOT_ALLOWED == NAS_EMM_GLO_AD_GetAttRejEmmExtCau())
        &&(PS_FALSE == NAS_EMM_GetLteNoSubscribeNvConfigDiscardExtCauseFlag()))
    {
        /*被15原因值拒绝而且当前有扩展原因值，指示USIM未在LTE开户，走正常的LTE未开户流程*/
        /*NAS_EMM_SetLteNoSubscribeExtCauseFlag(NAS_EMM_EUTRAN_NOT_ALLOWED);*/
        NAS_LMM_LteNoSubscribeWithExtCauseHandle(&stLteNoSubsPlmnList);

        /* Forb Ta列表维护 */
        NAS_LMM_AddTaInForbListWithAttRejCauseVal15(NAS_EMM_YES, &ulIsNeedExecLteNotAllow);
    }
    else
    {
        /* Forb Ta列表维护, 并判断是否要走4G未开户流程 */
        NAS_LMM_AddTaInForbListWithAttRejCauseVal15(NAS_EMM_NO, &ulIsNeedExecLteNotAllow);

        /* 判断是否要走4G未开户流程 */
        if (NAS_EMM_YES == ulIsNeedExecLteNotAllow)
        {
            /*被15原因值拒绝但是没有带扩展原因值，走LTE未开户定制流程*/
            NAS_LMM_LteNoSubscribeWithOutExtCauseHandle(&stLteNoSubsPlmnList);
        }
    }
    NAS_EMM_WaitNetworkRelInd();

    if (EMM_ATTACH_CAUSE_ESM_EMC_ATTACH == NAS_EMM_GLO_AD_GetAttCau())
    {
        /* 通知IMSA再尝试CS域 */
    }

    return;

}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcRejCauseVal1617
 Description     : 原因值为#16#17#22的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-7-5  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcRejCauseVal1617(VOS_VOID )
{

    /*根据GCF协议36523 9.2.1.2.3章节描述，先清除ATTACH ATTEMPTING COUNTER和
      TRACKING AREA UPDATING ATTEMPT计数器，再对TRACKING AREA UPDATING ATTEMPT
      计数器加1*/
    NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);

    /*tracking area updating attempt counter shall be incremented*/
    NAS_EMM_TAU_GetEmmTAUAttemptCnt() ++;

     /*设置EPS UPDATE STAUS为EU1*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_UPDATED_EU1);


    /*启动定时器TI_NAS_EMM_WAIT_ESM_BEARER_CNF*/
    NAS_LMM_StartStateTimer(         TI_NAS_EMM_WAIT_ESM_BEARER_CNF);

    /*修改状态：进入主状态REG_INIT子状态ATTACH_WAIT_ESM_BEARER_CNF*/
    NAS_EMM_AdStateConvert(             EMM_MS_REG_INIT,
                                        EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF,
                                        TI_NAS_EMM_WAIT_ESM_BEARER_CNF);
    /* 上报EPS LOC信息 */
    NAS_EMM_SndOmLogEpsLocInfo();
    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_ProcRejCauseVal22
 Description     : 原因值为#22的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen 00209181     2014-09-03  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcRejCauseVal22(VOS_VOID )
{

     /* 设置尝试次数为5 */
    NAS_EMM_TAU_GetEmmTAUAttemptCnt()  = NAS_EMM_TAU_ATTEMPT_CNT_MAX;

    /*设置设置EU1 */
    NAS_LMM_GetMmAuxFsmAddr()->ucEmmUpStat = EMM_US_UPDATED_EU1;

    /*启动定时器TI_NAS_EMM_WAIT_ESM_BEARER_CNF*/
    NAS_LMM_StartStateTimer(         TI_NAS_EMM_WAIT_ESM_BEARER_CNF);

    /*修改状态：进入主状态REG_INIT子状态ATTACH_WAIT_ESM_BEARER_CNF*/
    NAS_EMM_AdStateConvert(             EMM_MS_REG_INIT,
                                        EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF,
                                        TI_NAS_EMM_WAIT_ESM_BEARER_CNF);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcRejCauseVal18
 Description     : 原因值为#2的处理
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2011-7-5  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcRejCauseVal18(VOS_VOID)
{

    /*清除ATTACH ATTEMPTING COUNTER和TRACKING AREA UPDATING ATTEMPT计数器*/
    NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);

    /*设置EPS UPDATE STAUS为EU1*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_UPDATED_EU1);


    /*启动定时器TI_NAS_EMM_WAIT_ESM_BEARER_CNF*/
    NAS_LMM_StartStateTimer(         TI_NAS_EMM_WAIT_ESM_BEARER_CNF);

    /*修改状态：进入主状态REG_INIT子状态ATTACH_WAIT_ESM_BEARER_CNF*/
    NAS_EMM_AdStateConvert(             EMM_MS_REG_INIT,
                                        EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF,
                                        TI_NAS_EMM_WAIT_ESM_BEARER_CNF);

    /*后续需增加根据UE操作模式进行不同的处理*/
    /* 上报EPS LOC信息 */
    NAS_EMM_SndOmLogEpsLocInfo();
    return;
}
#if(FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 Function Name   : NAS_EMM_ProcRejCauseVal25
 Description     : 原因值为#25的处理
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.yanglei 00307272      2015-09-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcRejCauseVal25(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal)
{
    if(NAS_EMM_NO == NAS_LMM_IsCsgCampOn())
    {
        NAS_EMM_ProcRejCauseValOther(ucRejCauseVal);
    }
    else
    {
        /*清除ATTACH ATTEMPTING COUNTER计数器*/
        NAS_EMM_AttResetAttAttempCounter();

        /*设置EPS UPDATE STAUS为EU3*/
        NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);


       if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
        {
            /* 通知ESM紧接着EMM还要做紧急注册，ESM不需要清除动态表中的紧急PDN建立记录 */
            NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
        }
        else
        {
            /*向ESM发送ATTACH结果*/
            NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_DETACHED);
        }

        /*修改状态：进入主状态DEREG子状态DEREG_LIMITED_SERVICE*/
        NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                    EMM_SS_DEREG_LIMITED_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

        /* 向MMC发送结果 */
        NAS_EMM_AppSendAttRej();

        /*向MRRC发送NAS_EMM_MRRC_REL_REQ消息*/
        NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);
        return;
    }

}
#endif

/*****************************************************************************
 Function Name   : NAS_EMM_ProcRejCauseVal11
 Description     : 对ATTACH拒绝原因值#11的处理

 Input           :
 Output          :
 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_EMM_ProcRejCauseVal35(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal)
{
    if (NAS_RELEASE_R10)
    {
        NAS_EMM_ProcRejCauseVal11(ucRejCauseVal);
    }
    else
    {
        NAS_EMM_ProcRejCauseValOther(ucRejCauseVal);
    }
}
/*****************************************************************************
 Function Name   : NAS_EMM_ProcRejCauseVal42
 Description     :对ATTACH拒绝原因值#42的处理

 Input           :
 Output          :
 Return          :

 History         :
    1.wangchen 00209181     2014-09-01  Draft Enact
*****************************************************************************/
VOS_VOID    NAS_EMM_ProcRejCauseVal42(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal)
{
    if (NAS_RELEASE_R11)
    {
        /* 设置尝试次数为5 */
        NAS_EMM_GLO_AD_GetAttAtmpCnt()  = 5;

        /* 删除GUTI后会自动保存EPS_LOC,所以需要先设置STATUS */
        /*设置设置EU2 NOT UPDATED*/
        NAS_LMM_GetMmAuxFsmAddr()->ucEmmUpStat = EMM_US_NOT_UPDATED_EU2;

        /*删除GUTI,KSIasme,TAI list,GUTI*/
        NAS_EMM_ClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);

        if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
        {
            /* 通知ESM紧接着EMM还要做紧急注册，ESM不需要清除动态表中的紧急PDN建立记录 */
            NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
        }
        else
        {
            /*向ESM发送ATTACH结果*/
            NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_DETACHED);
        }

        /*修改状态：进入主状态DEREG子状态DEREG_LIMITED_SERVICE*/
        NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                    EMM_SS_DEREG_LIMITED_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

        /* 向MMC发送结果 */
        NAS_EMM_AppSendAttRej();

        /*向MRRC发送NAS_EMM_MRRC_REL_REQ消息*/
        NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);
    }
    else
    {
        NAS_EMM_ProcRejCauseValOther(ucRejCauseVal);
    }
    return;

}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcRejCauseValOther
 Description     : 对ATTACH拒绝原因值为其它值的处理
                  1.the UE should set the attach attempt counter to 5
                  2.the UE shall delete any GUTI, TAI list, last visited
                    registered TAI,list of equivalent PLMNs and KSI
                  3.the update status to EU2 NOT UPDATED, and shall
                    start timer T3402
 Input           :
 Output          :
 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_EMM_ProcRejCauseValOther(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal)
{
    if((NAS_LMM_CAUSE_SEMANTICALLY_INCORRECT_MSG == ucRejCauseVal) ||
       (NAS_LMM_CAUSE_INVALID_MANDATORY_INF == ucRejCauseVal)       ||
       (NAS_LMM_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE == ucRejCauseVal)  ||
       (NAS_LMM_CAUSE_IE_NONEXIST_NOTIMPLEMENTED == ucRejCauseVal)  ||
       (NAS_LMM_CAUSE_PROTOCOL_ERROR == ucRejCauseVal)||
       (VOS_TRUE == NAS_LMM_GetRoamingRejectNoRetryFlg(ucRejCauseVal)))/* 产品线刘海波定制需求DTS2014073107501 */
    {
        NAS_EMM_GLO_AD_GetAttAtmpCnt()  = 5;
    }
    else if(NAS_LMM_CAUSE_ESM_FAILURE == ucRejCauseVal)
    {
        /* 美国AT&T定制需求，在AT&T的PLMN上收到#19时，计数需特殊处理 */
        if((NAS_EMM_YES == NAS_EMM_IsDamConfitionSatisfied())
            ||(NAS_EMM_YES == NAS_EMM_GetEmmInfoRej19AtmptCntFlag()))
        {
            NAS_EMM_DamAttachRej19CountProc();
        }
        else if(NAS_LMM_ESM_CAUSE_PDN_CONNECTION_DOES_NOT_EXIST == NAS_EMM_GLO_AD_GetAttRejEsmCau())
        {
            /*CL multimode 当EMM原因值为#19且ESM原因值为#54时attach尝试次数加1 2014-02-14*/
            /* 清除之前保存的attach原因值 */
            NAS_LMM_ClearEmmInfoMmcAttachReason();
            NAS_EMM_GLO_AD_GetAttAtmpCnt() ++;
        }
        else
        {
            NAS_EMM_GLO_AD_GetAttAtmpCnt() = 5;
        }
    }
    else
    {
        NAS_EMM_GLO_AD_GetAttAtmpCnt() ++;
    }

    if (EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER == NAS_EMM_GLO_AD_GetAttCau())
    {
        /* 通知ESM紧接着EMM还要做紧急注册，ESM不需要清除动态表中的紧急PDN建立记录 */
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
    }
    else
    {
        /*向ESM发送ATTACH结果*/
        NAS_EMM_AttSendEsmResult(EMM_ESM_ATTACH_STATUS_DETACHED);
    }

    NAS_EMM_ProcRejCauOtherAbnormal();

    /*向MRRC发送NAS_EMM_MRRC_REL_REQ消息*/
    NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);

    if (EMM_ATTACH_CAUSE_ESM_EMC_ATTACH == NAS_EMM_GLO_AD_GetAttCau())
    {
        /* 通知IMSA再尝试CS域 */
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_RejCauseValProc
 Description     : 根据网络侧拒绝ATTACH REQUEST的原因值不同进行不同处理

 Input           :
 Output          :
 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact
    2.zhengjunyan 00148421   2011-12-23  DTS2011122103346:CSG功能尚未实现，收到
                                         REJ #25按非CSG处理，进入default处理分支
    3.wangchen 00209181     2014-09-28  Modify:R11,降圈复杂度
*****************************************************************************/
VOS_VOID    NAS_EMM_RejCauseValProc(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucRejCauseVal)
{
    VOS_UINT32                          ulIndex = 0;
    NAS_LMM_REJ_CAUSE_PROC_FUN          pfRejCauseProcFun;

    for (ulIndex = 0; ulIndex < gstEmmAttRejCauseProcTblLen; ulIndex++)
    {
        if (ucRejCauseVal == gstEmmAttRejCauseProcTbl[ulIndex].enRejCauseVal)
        {
            pfRejCauseProcFun = gstEmmAttRejCauseProcTbl[ulIndex].pfRejCauseProcFun;

            /* 有处理函数 */
            if (VOS_NULL_PTR != pfRejCauseProcFun)
            {
                (pfRejCauseProcFun)(ucRejCauseVal);
            }
            return;
        }
    }

    /* 其他原因值的处理 */
    NAS_EMM_ProcRejCauseValOther(ucRejCauseVal);

}
/*****************************************************************************
 Function Name   : NAS_EMM_ProcEpsOnlySucc
 Description     : 联合注册时，仅EPS ONLY注册成功，对携带不同原因值的处理
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2011-7-5  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcEpsOnlySucc
(
    VOS_VOID                *pstRcvMsg
)
{
    NAS_EMM_CN_ATTACH_ACP_STRU          *pstAttAcp;

    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_ProcEpsOnlySucc is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcEpsOnlySucc_ENUM,LNAS_ENTRY);

    pstAttAcp = (NAS_EMM_CN_ATTACH_ACP_STRU *)pstRcvMsg;
    /*lint -e961*/
    if (NAS_EMM_BIT_SLCT == pstAttAcp->ucBitOpEmmCau)
    {
        NAS_EMM_ATTACH_LOG1_NORM("NAS_EMM_ProcEpsOnlySucc EmmCause:",pstAttAcp->ucEMMCause);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProcEpsOnlySucc_ENUM,LNAS_CAUSE_NUMBER,pstAttAcp->ucEMMCause);
        NAS_EMM_ProcEpsOnlyWithCause(pstRcvMsg);
    }
    else
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_ProcEpsOnlySucc No EmmCause");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcEpsOnlySucc_ENUM,LNAS_NO_CAUSE);
        NAS_EMM_ProcEpsOnlyNoCause();
    }
    /*lint +e961*/
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcEpsOnlyWithCause
 Description     : 联合注册时，仅EPS ONLY注册成功，对携带不同原因值的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-7-5  Draft Enact
    2.wangchen 00209181     2014-09-03  Modify:R11
*****************************************************************************/
VOS_VOID  NAS_EMM_ProcEpsOnlyWithCause
(
    VOS_VOID                *pstRcvMsg
)
{
    NAS_EMM_CN_ATTACH_ACP_STRU          *pstAttAcp;

    pstAttAcp = (NAS_EMM_CN_ATTACH_ACP_STRU *)pstRcvMsg;

    NAS_EMM_GLO_AD_GetAttRejCau() = pstAttAcp->ucEMMCause;
    NAS_MML_SetOriginalRejectCause(pstAttAcp->ucEMMCause);
    switch (pstAttAcp->ucEMMCause)
    {
        case    NAS_LMM_CAUSE_IMSI_UNKNOWN_IN_HSS:
                NAS_EMM_ProcRejCauseVal2();
                break;

        case    NAS_LMM_CAUSE_CS_NOT_AVAIL:
                NAS_EMM_ProcRejCauseVal18();
                break;
        case    NAS_LMM_CAUSE_PROCEDURE_CONGESTION:
                if (NAS_RELEASE_R11)
                {
                    NAS_EMM_ProcRejCauseVal22();
                }
                else
                {
                    NAS_EMM_ProcRejCauseVal1617();
                }
                break;
        default:
                NAS_EMM_ProcRejCauseVal1617();
                break;
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcEpsOnlyNoCause
 Description     : 联合注册时，仅EPS ONLY注册成功，但不携带原因值
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-7-5  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcEpsOnlyNoCause( VOS_VOID)
{
    NAS_MML_SetOriginalRejectCause(NAS_LMM_CAUSE_NULL);
    NAS_EMM_ProcRejCauseVal1617();

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_TimerValTransfer
 Description     : 将定时器的值转换为毫秒

 Input           :
 Output          :
 Return          :

 History         :
    1.leili 00132387         2008-11-19  Draft Enact
    2.zhengjunyan 00148421   2009-10-21  MOD:BJ9D02171
*****************************************************************************/
VOS_UINT32 NAS_EMM_TimerValTransfer(NAS_EMM_TIMER_UNIT_ENUM_UINT8        ucUnit,
                                  VOS_UINT8                           ucTimerVal)
{
    VOS_UINT32                          ulTimerValue = 0;

    switch(ucUnit)
    {
        case NAS_EMM_TIMER_UNIT_2SENDS:
             ulTimerValue = ucTimerVal*2*NAS_EMM_SECOND_TRANSFER_MILLISECOND;
             break;

        case NAS_EMM_TIMER_UNIT_1MINUTE:
             ulTimerValue = ucTimerVal*NAS_EMM_MINUTE_TRANSFER_MILLISECOND;
             break;

        case NAS_EMM_TIMER_UNIT_6MINUTES:
             ulTimerValue = ucTimerVal*6*NAS_EMM_MINUTE_TRANSFER_MILLISECOND;
             break;

             /*定时器时长赋为零，不会启动该定时器*/
        case NAS_EMM_TIMER_DEACTIVATE:
             ulTimerValue = 0;
             break;

             /*其他值，单位为1min*/
        default:
             ulTimerValue = ucTimerVal*NAS_EMM_MINUTE_TRANSFER_MILLISECOND;
             break;
    }

    return ulTimerValue;

}
/*****************************************************************************
 Function Name   : NAS_EMM_AttSetLai
 Description     : 设置LAI

 Input           :
 Output          :
 Return          :

 History         :
    1.z00179470         2011-12-13      Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_AttSetLai(VOS_VOID                *pstRcvMsg)
{
    NAS_EMM_CN_ATTACH_ACP_STRU          *pstAttAcp;

    if (NAS_EMM_NULL_PTR == pstRcvMsg)
    {
        /*打印错误*/
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_AppSendAttSucc: Input para is invalid!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AttSetLai_ENUM,LNAS_PARAM_INVALID);
        return;
    }

    pstAttAcp = (NAS_EMM_CN_ATTACH_ACP_STRU *)pstRcvMsg;

    if(pstAttAcp->ucBitOpLai == NAS_EMM_AD_BIT_SLCT)
    {
        NAS_EMM_GLO_AD_OP_GetLai()      = NAS_EMM_BIT_SLCT;

        NAS_LMM_MEM_CPY_S(  NAS_EMM_GLO_AD_GetLaiAddr(),
                            sizeof(NAS_EMM_LA_STRU),
                            &pstAttAcp->stLai,
                            sizeof(NAS_EMM_LA_STRU));
    }
    else
    {
        NAS_EMM_GLO_AD_OP_GetLai()   = NAS_EMM_AD_BIT_NO_SLCT;

        NAS_LMM_MEM_SET_S(  NAS_EMM_GLO_AD_GetLaiAddr(),
                            sizeof(NAS_EMM_LA_STRU),
                            0,
                            sizeof(MMC_LMM_LAI_STRU));
    }
    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_AttSetEplms
 Description     : 设置EPLMNS

 Input           :
 Output          :
 Return          :

 History         :
    1.z00179470         2011-12-13      Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_AttSetEplms(VOS_VOID                *pstRcvMsg)
{
    NAS_EMM_CN_ATTACH_ACP_STRU          *pstAttAcp;

    if (NAS_EMM_NULL_PTR == pstRcvMsg)
    {
        /*打印错误*/
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_AppSendAttSucc: Input para is invalid!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AttSetEplms_ENUM,LNAS_PARAM_INVALID);
        return;
    }

    pstAttAcp = (NAS_EMM_CN_ATTACH_ACP_STRU *)pstRcvMsg;

    if(pstAttAcp->ucBitOpPlmnList == NAS_EMM_AD_BIT_SLCT)
    {
        NAS_LMM_GetEmmInfoNetInfoOpEplmnListAddr()   = NAS_EMM_AD_BIT_SLCT;

        NAS_LMM_MEM_CPY_S(  NAS_LMM_GetEmmInfoNetInfoEplmnListAddr(),
                            sizeof(NAS_MM_PLMN_LIST_STRU),
                            &pstAttAcp->stPlmnList,
                            sizeof(MMC_LMM_EPLMN_STRU));
    }
    else
    {
        NAS_LMM_GetEmmInfoNetInfoOpEplmnListAddr()   = NAS_EMM_AD_BIT_NO_SLCT;

        NAS_LMM_MEM_SET_S(  NAS_LMM_GetEmmInfoNetInfoEplmnListAddr(),
                            sizeof(NAS_MM_PLMN_LIST_STRU),
                            0,
                            sizeof(MMC_LMM_EPLMN_STRU));
    }
    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_AttSetMsId
 Description     : 设置MsId

 Input           :
 Output          :
 Return          :

 History         :
    1.z00179470         2011-12-13      Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_AttSetMsId(VOS_VOID                *pstRcvMsg)
{
    NAS_EMM_CN_ATTACH_ACP_STRU          *pstAttAcp;

    if (NAS_EMM_NULL_PTR == pstRcvMsg)
    {
        /*打印错误*/
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_AppSendAttSucc: Input para is invalid!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AttSetMsId_ENUM,LNAS_PARAM_INVALID);
        return;
    }

    pstAttAcp = (NAS_EMM_CN_ATTACH_ACP_STRU *)pstRcvMsg;

    if(pstAttAcp->ucBitOpMsId == NAS_EMM_AD_BIT_SLCT)
    {
        NAS_EMM_GLO_AD_OP_GetMsId()   = NAS_EMM_AD_BIT_SLCT;

        NAS_LMM_MEM_CPY_S(  NAS_EMM_GLO_AD_GetMsIdAddr(),
                            sizeof(NAS_EMM_MSID_STRU),
                            &pstAttAcp->stMsId,
                            sizeof(NAS_EMM_MSID_STRU));
    }
    else
    {
        NAS_EMM_GLO_AD_OP_GetMsId()   = NAS_EMM_AD_BIT_NO_SLCT;

        NAS_LMM_MEM_SET_S(  NAS_EMM_GLO_AD_GetMsIdAddr(),
                            sizeof(NAS_EMM_MSID_STRU),
                            0,
                            sizeof(NAS_EMM_MSID_STRU));
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SaveAttachAcpIe
 Description     : 存储ATTACH ACCPET中携带的信元
 Input           : pMsgStru------------ATTACH ACCEPT消息指针
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2012-02-27  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SaveAttachAcpIe
(
    VOS_VOID                           *pMsgStru
)
{
    NAS_EMM_CN_ATTACH_ACP_STRU         *pRcvEmmMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulTimerLen = NAS_EMM_NULL;

    pRcvEmmMsg                          = (NAS_EMM_CN_ATTACH_ACP_STRU *)pMsgStru;

    /*保存ATTACH结果*/
    NAS_EMM_GLO_AD_SetAttRslt(pRcvEmmMsg->ucAttachRst);

    /*保存T3412 VALUE*/
    ulTimerLen = NAS_EMM_TimerValTransfer(pRcvEmmMsg->stT3412Value.ucUnit,
                                           pRcvEmmMsg->stT3412Value.ucTimerVal);
    NAS_LMM_ModifyPtlTimer(TI_NAS_EMM_PTL_T3412,ulTimerLen);

     /*保存TAI LIST*/
    NAS_LMM_MEM_CPY_S(  NAS_EMM_GLO_AD_GetTaiListAddr(),
                        sizeof(NAS_MM_TA_LIST_STRU),
                        &(pRcvEmmMsg->stTaiList),
                        sizeof(NAS_EMM_TA_LIST_STRU));

    /*保存新的TAI List的同时更新ForbTA for Roaming和ForbTA for RPOS*/
    NAS_EMMC_UpdateForbTaList();

    /*向ESM发送ACTIVATE DEFAULT EPS BEARER REQUEST消息*/
    NAS_EMM_EsmSendDataInd(              &(pRcvEmmMsg->stMsgCon));

    /* ATTACH ACP携带GUTI,更新GUTI到EMM的全局变量中*/
    if(NAS_EMM_BIT_SLCT == pRcvEmmMsg->ucBitOpGuti)
    {
        NAS_EMM_SetGuti(&(pRcvEmmMsg->stGuti));

    }

    /* Location area identification,MS identity,EMM cause,EPLMNS收到ATTACH ACCEPT保存，
        发出ATTACH COMPLETE或后续ATTACH失败从本地保存的读取，携带给MMC */

    NAS_EMM_AttSetLai(pMsgStru);

    NAS_EMM_AttSetEplms(pMsgStru);

    NAS_EMM_AttSetMsId(pMsgStru);

    if(pRcvEmmMsg->ucBitOpEmmCau == NAS_EMM_AD_BIT_SLCT)
    {
        NAS_EMM_GLO_AD_OP_GetEmmCau() = NAS_EMM_AD_BIT_SLCT;
        NAS_EMM_GLO_AD_GetEmmCau()    = pRcvEmmMsg->ucEMMCause;
    }
    else
    {
        NAS_EMM_GLO_AD_OP_GetEmmCau()   = NAS_EMM_AD_BIT_NO_SLCT;
        NAS_EMM_GLO_AD_GetEmmCau()      = 0;
    }

    /*ATTACH ACP携带T3402,修改定时器时长*/
    if(pRcvEmmMsg->ucBitOpT3402 == NAS_EMM_AD_BIT_SLCT)
    {
        ulTimerLen = NAS_EMM_TimerValTransfer(pRcvEmmMsg->stT3402Value.ucUnit,
                                            pRcvEmmMsg->stT3402Value.ucTimerVal);
        NAS_LMM_ModifyPtlTimer(TI_NAS_EMM_PTL_T3402,ulTimerLen);

    }
    else
    {
        /*如果ATTACH ACP消息中不携带T3402信元，则恢复默认值12min*/
        NAS_LMM_ModifyPtlTimer(TI_NAS_EMM_PTL_T3402,NAS_LMM_TIMER_T3402_LEN);
        ulTimerLen = NAS_LMM_TIMER_T3402_LEN;
    }
    /* T3402长度有修改，需要写入对应的全局变量 */
    g_ulEmmT3402length  = ulTimerLen;

    /* AT&T定制需求，3402时长变更需通知MMC */
    if(ulTimerLen != NAS_EMM_GetEmmInfoDamParaT3402Len())
    {
        NAS_EMM_GetEmmInfoDamParaT3402Len() = ulTimerLen;
        NAS_EMM_SendMMCT3402LenNotify(ulTimerLen);
    }

    /*ATTACH ACP携带T3423,修改定时器时长*/
    if(pRcvEmmMsg->ucBitOpT3423 == NAS_EMM_AD_BIT_SLCT)
    {
        ulTimerLen = NAS_EMM_TimerValTransfer(pRcvEmmMsg->stT3423Value.ucUnit,
                                            pRcvEmmMsg->stT3423Value.ucTimerVal);
        NAS_LMM_ModifyPtlTimer(TI_NAS_EMM_PTL_T3423,ulTimerLen);

    }
    else
    {
        /*如果ATTACH ACP消息中不携带T3423信元，则恢复默认值为T3412时长*/
        NAS_LMM_GetPtlTimerLen(TI_NAS_EMM_PTL_T3412, &ulTimerLen);
        NAS_LMM_ModifyPtlTimer(TI_NAS_EMM_PTL_T3423,ulTimerLen);
    }

    /*更新Emergency number list到全局变量中*/
    NAS_EMM_SetEmergencyList(   pRcvEmmMsg->ucBitOpEmergencyList,
                                &(pRcvEmmMsg->stEmergencyNumList));

    /*更新EPS network feature support到全局变量中*/
    NAS_EMM_SetEpsNetFeature(   pRcvEmmMsg->ucBitOpEpsNetFeature,
                                pRcvEmmMsg->ucEpsNetFeature);

    /*更新Additional update result到全局变量中*/
    if(EMM_ATTACH_RST_PS == pRcvEmmMsg->ucAttachRst)
    {
        /* 仅EPS ONLY成功 则ulAdditionUpRslt保存为NAS_LMM_ADDITIONAL_UPDATE_NOT_ATTACHED */
        NAS_EMM_SetAddUpdateRslt(NAS_EMM_BIT_SLCT, NAS_LMM_ADDITIONAL_UPDATE_NOT_ATTACHED);
    }
    else
    {
        NAS_EMM_SetAddUpdateRslt(   pRcvEmmMsg->ucBitOpAdditionalUpRslt,
                                    pRcvEmmMsg->ulAdditionUpRslt);
    }

    /* 通知MMC紧急呼号码列表，网侧是否支持IMS VOICE和紧急呼，以及LTE的CS域能力 */
    /* NAS_EMM_SendGmmInfoChangeNotify(); */
    NAS_EMM_SendMmcInfoChangeNotify();
    /*NAS_EMM_SendMmInfoChangeNotify();*/
    /* 勾出EPS LOC信息 */
    NAS_EMM_SndOmLogEpsLocInfo();
#if (FEATURE_LPP == FEATURE_ON)
    NAS_EMM_SndLcsPosCapInfoInd();
#endif
}
/*lint +e960*/

/*****************************************************************************
 Function Name   : NAS_EMM_SaveAttachAcpIe
 Description     : 存储ATTACH ACCPET中携带的信元
 Input           : pMsgStru------------ATTACH ACCEPT消息指针
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2012-02-27  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SaveAttachRejIe
(
    VOS_VOID                           *pMsgStru
)
{
    NAS_EMM_CN_ATTACH_REJ_STRU         *pRcvEmmMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulTimerLen = NAS_EMM_NULL;

    pRcvEmmMsg                          = (NAS_EMM_CN_ATTACH_REJ_STRU *)pMsgStru;

     /*ATTACH REJ携带T3402,且ATTACH REJ消息是完整性保护的，修改定时器时长*/
    if(pRcvEmmMsg->ucBitOpT3402 == NAS_EMM_AD_BIT_SLCT)
    {
        if (VOS_TRUE == NAS_LMM_GetMsgIsIntegrityFlag())
        {
            ulTimerLen = NAS_EMM_TimerValTransfer(pRcvEmmMsg->stT3402Value.ucUnit,
                                            pRcvEmmMsg->stT3402Value.ucTimerVal);
            NAS_LMM_ModifyPtlTimer(TI_NAS_EMM_PTL_T3402,ulTimerLen);
        }
        else
        {
            /*如果ATTACH REJ消息中是明文，则恢复默认值12min*/
            NAS_LMM_ModifyPtlTimer(TI_NAS_EMM_PTL_T3402,NAS_LMM_TIMER_T3402_LEN);
            ulTimerLen = NAS_LMM_TIMER_T3402_LEN;
        }
        /* T3402长度有修改，需要写入对应的全局变量 */
        g_ulEmmT3402length  = ulTimerLen;

        /* 设置T3402时长的来源为ATATCH REJ */
        NAS_LMM_SetT3402Src(NAS_EMM_T3402_SRC_ATTACH_REJ);
    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachAccept
 Description     : 主状态REG_INIT+子状态ATTACH_WAIT_CN_ATTACH_CNF下收到网侧发送的
                   ATTACH ACCEPT消息
 Input           :
 Output          :
 Return          :
 History         :
    1.leili       00132387   2008-09-09  Draft Enact
    2.zhengjunyan 00148421   2009-08-11  BJ9D01646:T3402定时器时长
    3.zhengjunyan 00148421   2011-12-21  DTS2011122004363:清除TAU/service/detach资源
    4.lihong      00150010   2012-12-18  Modify:参照标杆做法，在收到ATTACH ACCEPT时就
                                                更新GUTI, LAST VISIT TAI，EU值，并写卡或者NV
    5.houzhiyuan  00285180   2014-10-20  Add: 拒绝原因值优化PhaseII DTS2014110307415
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachAcp(VOS_UINT32  ulMsgId,
                                                VOS_VOID   *pMsgStru)
{
    NAS_EMM_CN_ATTACH_ACP_STRU         *pRcvEmmMsg;
    NAS_LMM_NETWORK_INFO_STRU          *pMmNetInfo = VOS_NULL_PTR;
#if (VOS_OS_VER != VOS_WIN32)
    static VOS_UINT32  s_ulAttachAcpCnt = 1;
#endif

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (NAS_EMM_CN_ATTACH_ACP_STRU *)pMsgStru;

    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachAcp is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachAcp_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF))
    {
        /*打印出错信息*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachAcp: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachAcp_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /* 如果ATTACH ACP消息内容不合法,不处理消息，直接丢弃*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_CnAttachAcpMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachAcp: NAS_EMM_CN_ATTACH_ACC_STRU para err!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachAcp_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;

    }

    NAS_EMM_SetLteNoSubscribeLteRegFlag(NAS_LMM_HAVE_REG_SUCC_ON_LTE);

    /* 大数据: 记录ATTACH ACP时间 */
    NAS_LMM_SaveAttachAcpTimeStamp();
    NAS_EMM_ResetRejCauseChangedCounter();

    NAS_EMM_ResetHplmnAuthRejCout();

    /*停止定时器T3410*/
    NAS_LMM_StopStateTimer(          TI_NAS_EMM_T3410);

    /* 存储ATTACH ACCPET中携带的信元 */
    NAS_EMM_SaveAttachAcpIe(pMsgStru);

    /* 收到ATTACH ACP，将注册状态设置为RCV CN ACP */
    NAS_EMM_GLO_AD_SetAttClRegStatus(MMC_LMM_CL_REG_STATUS_ATTACH_RCV_CN_ACP);

    /*清除ATTACH ATTEMPTING COUNTER和TRACKING AREA UPDATING ATTEMPT计数器*/
    NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);

    /* 美国AT&T定制需求: ATTACH成功清除CService计数，无论结果如何，PS域均已OK */
    NAS_EMM_GetEmmInfoDamParaCserviceCnt() = 0;

    /*注册成功后，注册前的TAU/SERVICE/DETACH模块记录的历史信息不应该影响后续流程
      清除TAU/service/detach资源
    */
    NAS_EMM_TAU_ClearResouce();
    NAS_EMM_SER_ClearResource();
    NAS_EMM_Detach_ClearResourse();

    /*联合注册仅EPS ONLY成功*/
    if ((MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI == NAS_EMM_GLO_GetCnAttReqType()) &&
        (EMM_ATTACH_RST_PS == pRcvEmmMsg->ucAttachRst))
    {
        NAS_EMM_ProcEpsOnlySucc(pMsgStru);
        #if (FEATURE_PTM == FEATURE_ON)
        NAS_EMM_AttachErrRecord(pMsgStru, EMM_OM_ERRLOG_TYPE_EPS_ONLY);
        #endif
    }
    else
    {
        /*设置EPS UPDATE STAUS为EU1*/
        NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_UPDATED_EU1);

        /*启动定时器TI_NAS_EMM_WAIT_ESM_BEARER_CNF*/
        NAS_LMM_StartStateTimer(         TI_NAS_EMM_WAIT_ESM_BEARER_CNF);

        /*修改状态：进入主状态REG_INIT子状态ATTACH_WAIT_ESM_BEARER_CNF*/
        NAS_EMM_AdStateConvert(             EMM_MS_REG_INIT,
                                            EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF,
                                            TI_NAS_EMM_WAIT_ESM_BEARER_CNF);
    }

    /* 参照标杆做法，在收到ATTACH ACCEPT时就更新GUTI, LAST VISIT TAI，EU值，
       并写卡或者NV */
    pMmNetInfo                          = NAS_LMM_GetEmmInfoNetInfoAddr();
    NAS_EMM_SetLVRTai(                  &pMmNetInfo->stPresentNetId);

    /* 判断没有放到函数NAS_LMM_WritePsLoc中来做，是由于紧急注册被拒或者尝试次数
       达到5次时还是要删除参数 ，协议只规定是紧急注册成功后才不写卡或者NV项 */
    if (NAS_LMM_REG_STATUS_EMC_REGING != NAS_LMM_GetEmmInfoRegStatus())
    {
        /*保存PS LOC信息*/
        NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
    }

    /* 清除接入技术变化标识，在这里清除不考虑ATTACH失败的原因值
          因为要么必然转入了DEREG态，要么MME已经查询完UE无线能力*/
    NAS_EMM_ClearUeRadioAccCapChgFlag();

#if (VOS_OS_VER != VOS_WIN32)
    if(1 == s_ulAttachAcpCnt)
    {
        (VOS_VOID)LDRV_SYSBOOT_STAMPADD("UE attach success",__LINE__);
        s_ulAttachAcpCnt++;
    }
#endif

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   :  NAS_EMM_SendRejEventToSTK
 Description     :  在nas收到attach and TAU 拒绝的时候上报消息给STK
 Input           :  ucCauseCode 表示网络拒绝原因
                    enUpdateType区分attach类型还是tau类型
 Output          :  发消息给STK
 Return          :

 History         :
    1.lifuxin 00253982         2013-10-10  新增文件

*****************************************************************************/
/*lint -e960*/
VOS_VOID    NAS_EMM_SendRejEventToSTK(VOS_UINT8 ucCauseCode,
                      LNAS_STK_UPDATE_TYPE_ENUM_UINT8          enUpdateType)
{
    LNAS_STK_NETWORK_REJECTION_EVENT_STRU       *pEmmNetworkRejectMsg;
    NAS_MM_PLMN_ID_STRU     *pEmmPlmnID;
    NAS_MM_TAC_STRU         *pEmmTac;

    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_SendRejEventToSTK is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendRejEventToSTK_ENUM,LNAS_ENTRY);
    /*申请消息内存*/
    pEmmNetworkRejectMsg   = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(LNAS_STK_NETWORK_REJECTION_EVENT_STRU));

    /*判断申请结果，若失败退出*/
    if (NAS_EMM_NULL_PTR == pEmmNetworkRejectMsg)
    {
        return;
    }

    /*构造ID_LNAS_STK_NETWORK_REJECTION_EVENT消息*/
    /*填充消息头*/
    NAS_EMM_STK_MSG_HEADER(      pEmmNetworkRejectMsg,
                                        (sizeof(LNAS_STK_NETWORK_REJECTION_EVENT_STRU)-
                                        NAS_EMM_LEN_VOS_MSG_HEADER));

    /*填充消息ID*/
    pEmmNetworkRejectMsg->ulMsgName = ID_LNAS_STK_NETWORK_REJECTION_EVENT;

    /*填充消息内容*/
    pEmmNetworkRejectMsg->stNetworkRejectionEvent.ucCauseCode = ucCauseCode;

    /*填充消息plmn*/
    pEmmPlmnID = NAS_LMM_GetEmmInfoPresentPlmnAddr();
    pEmmNetworkRejectMsg->stNetworkRejectionEvent.stTaiInfo.stCurPlmnID.aucPlmnId[0] =
                        pEmmPlmnID->aucPlmnId[0];
    pEmmNetworkRejectMsg->stNetworkRejectionEvent.stTaiInfo.stCurPlmnID.aucPlmnId[1] =
                        pEmmPlmnID->aucPlmnId[1];
    pEmmNetworkRejectMsg->stNetworkRejectionEvent.stTaiInfo.stCurPlmnID.aucPlmnId[2] =
                        pEmmPlmnID->aucPlmnId[2];

    /*填充消息TAC*/
    pEmmTac = NAS_LMM_GetEmmInfoPresentTacAddr();
    pEmmNetworkRejectMsg->stNetworkRejectionEvent.stTaiInfo.stTac.ucTac    = pEmmTac->ucTac;
    pEmmNetworkRejectMsg->stNetworkRejectionEvent.stTaiInfo.stTac.ucTacCnt = pEmmTac->ucTacCnt;

    /*填充消息enUpdateAttachType*/
    pEmmNetworkRejectMsg->stNetworkRejectionEvent.enUpdateAttachType = enUpdateType;

    /*向stk发送rejection消息*/
    NAS_LMM_SEND_MSG(pEmmNetworkRejectMsg);

    return;
}
/*lint +e960*/

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachReject
 Description     : 主状态REG_INIT+子状态ATTACH_WAIT_CN_ATTACH_CNF下收到
                   ATTACH REJECT消息
                   拒绝原因值#3(Illegal MS)#6(Illegal ME)
                   拒绝原因值#7(GPRS services not allowed)
                   拒绝原因值#8(GPRS services and non-GPRS services not allowed)
                   拒绝原因值#11(PLMN not allowed)
                   拒绝原因值#12(Tracking area not allowed)
                   拒绝原因值#13(Roaming not allowed in this tracking area)
                   拒绝原因值#14(GPRS services not allowed in this PLMN)
                   拒绝原因值#15(No suitable cells in tracking area)
 Input           :
 Output          :
 Return          :

 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachReject(
                                                VOS_UINT32  ulMsgId,
                                                VOS_VOID   *pMsgStru )
{
    NAS_EMM_CN_ATTACH_REJ_STRU          *pRcvEmmMsg;
    LNAS_STK_UPDATE_TYPE_ENUM_UINT8     uAttachType;

    (VOS_VOID)ulMsgId;

    pRcvEmmMsg                          = (NAS_EMM_CN_ATTACH_REJ_STRU *) pMsgStru;

    /*打印进入该函数*/
    NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachReject is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachReject_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if (NAS_EMM_AD_CHK_STAT_INVALID(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF))
    {
        /*打印出错信息*/
        NAS_EMM_ATTACH_LOG_WARN("NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachReject: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachReject_ENUM,LNAS_ERROR);
        return  NAS_LMM_MSG_DISCARD;
    }

    /*消息内容检查*/
    if (NAS_EMM_PARA_INVALID == NAS_EMM_CnAttachRejMsgChk(pRcvEmmMsg))
    {
        NAS_EMM_ATTACH_LOG_ERR("NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachReject: NAS_EMM_CN_ATTACH_REJ_STRU para err!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachReject_ENUM,LNAS_PARAM_INVALID);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /*停止定时器T3410*/
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3410);

    if (NAS_RELEASE_R11)
    {
        /* 存储ATTACH REJ携带的信元 */
        NAS_EMM_SaveAttachRejIe(pMsgStru);
    }
    /* 大数据: 更新attach被Rej次数 */
    NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_CN_REJ);
    /*保存ATTACH拒绝原因*/
    NAS_EMM_GLO_AD_GetAttRejCau()       = pRcvEmmMsg->ucCause;
    NAS_EMM_GLO_AD_GetAttRejEsmCau()    = pRcvEmmMsg->ucEsmCause;

    if(NAS_EMM_BIT_SLCT == pRcvEmmMsg->ucBitOpExtCause)
    {
        NAS_EMM_GLO_AD_OP_GetAttRejEmmExtCau() = NAS_EMM_BIT_SLCT;
        NAS_EMM_GLO_AD_GetAttRejEmmExtCau() = pRcvEmmMsg->ucExtendedEmmCause;
    }

    /* 收到ATTACH REJ，将注册状态设置为RCV CN REJ */
    NAS_EMM_GLO_AD_SetAttClRegStatus(MMC_LMM_CL_REG_STATUS_ATTACH_RCV_CN_REJ);

    /* s00193151 begin for 自适应网络拒绝原因值 */
    /* 根据当前场景考虑是否修改原因值 */
    NAS_LMM_AdaptRegRejCau(&NAS_EMM_GLO_AD_GetAttRejCau());
    /* s00193151 end for 自适应网络拒绝原因值 */

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_EMM_AttachErrRecord(pMsgStru, EMM_OM_ERRLOG_TYPE_CN_REJ);
    #endif

    if(pRcvEmmMsg->ucBitOpMsgCon == NAS_EMM_AD_BIT_SLCT)
    {
        /*向ESM发送消息*/
        NAS_EMM_EsmSendDataInd(          &(pRcvEmmMsg->stMsgCon));
    }
    switch(NAS_EMM_GLO_GetCnAttReqType())
    {
        case MMC_LMM_ATT_TYPE_EPS_ONLY:
                uAttachType = LNAS_STK_UPDATE_TYPE_EPS_ATTACH;
                break;

        case  MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI:
                uAttachType = LNAS_STK_UPDATE_TYPE_COMBINED_ATTACH;
                break;

        default:
                uAttachType = LNAS_STK_UPDATE_TYPE_EPS_ATTACH;
                break;

    }

    /* s00193151 begin for 自适应网络拒绝原因值 */
    /*在ATTACH过程中出现rej，将rej事件报告给STK*/
    NAS_EMM_SendRejEventToSTK(NAS_EMM_GLO_AD_GetAttRejCau(), uAttachType);

    /*判断拒绝原因值,根据不同原因值进行处理*/
    NAS_EMM_RejCauseValProc(NAS_EMM_GLO_AD_GetAttRejCau());
    /* s00193151 end for 自适应网络拒绝原因值 */

    return  NAS_LMM_MSG_HANDLED;
}
/*lint +e960*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

