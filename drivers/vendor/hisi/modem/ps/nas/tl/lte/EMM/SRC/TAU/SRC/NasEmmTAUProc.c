/*******************************************************************************
  Copyright     : 2005-2007, Huawei Tech. Co., Ltd.
  File name     : NasEmmTAUProc.c
  Description   : EMM TAU REQUEST功能相关处理用源文件
  Function List :
    01.   Nas_Emm_TAU_RcvSysinfo
    02.   Nas_Emm_TAU_RcvT3412Exp
    03.   Nas_Emm_TAU_RcvT3411Exp
    04.   Nas_Emm_TAU_RcvT3402Exp
    05.   Nas_Emm_TAU_RcvT3430Exp
    06.   Nas_Emm_TAU_RcvTAUAcp
    07.   Nas_Emm_TAU_RcvTAURej
    08.   Nas_Emm_TAU_RcvRrcRelInd
    09.   Nas_Emm_TAU_RcvMrrcRelInd
    10.   Nas_Emm_TAU_RcvAppMmStopReq
    11.   Nas_Emm_TAU_RcvTAURejCause**
    12.   Nas_Emm_TAU_RcvTAURejCauseOthers
    13.   Nas_Emm_TAU_AbnormalOver
    14.   Nas_Emm_TAU_TAUStart
    15.   Nas_Emm_TAU_ReleaseRRCConnect
    16.   Nas_Emm_TAU_GetSERRejCause
  History       :
    1.  Zhouyan 00125190  2008.09.09  新规作成
    2.  hanlufeng 41410  2009-03-11  BA8D01164 把NAS_EMM_INFO_GUTI  修改为
        SER专用的接口
    3.  leili       00132387    2009.06.25   BJ9001269 收到系统消息后处理优化
*******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "NasEmmTauSerInclude.h"
#include  "NasLmmPubMPrint.h"
#include "NasMmlCtx.h"
#include "NasEmmAttDetInclude.h"
#include "NasLmmCore.h"
#include "LRrcLNasInterface.h"
#include "NasEmmPubUResume.h"

#include "ImsaInterface.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMTAUPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMTAUPROC_C
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
EMM_TAU_CTRL_STRU                g_stEmmTAUCtrlTbl;



/*******************************************************************************
  Module   :
  Function : NAS_EMM_TAU_Init
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190  2008.09.17  新规作成
*******************************************************************************/
/*lint -e589*/
/*lint -e669*/
/*lint -e831*/
/*lint -e960*/
/*lint -e961*/
VOS_VOID NAS_EMM_TAU_Init(VOS_VOID)
{
    NAS_EMM_TAU_LOG_NORM("NAS_EMM_TAU_Init                   START INIT...");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_Init_ENUM,LNAS_ENTRY);

    /* 初始化TAU全局变量 */
    NAS_LMM_MEM_SET_S(  &g_stEmmTAUCtrlTbl,
                        sizeof(g_stEmmTAUCtrlTbl),
                        0,
                        sizeof(g_stEmmTAUCtrlTbl));

    g_stEmmTAUCtrlTbl.enEmmTauType = NAS_EMM_CN_TAU_TYPE_TA_UPDATING;

    /* 初始化BAR信息*/
    NAS_EMM_ClearBarResouce();

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_TAU_ClearResouce
 Description     : UE去注册，清理TAU流程所有资源
                   挂起时，怎样处理两个TAU发起标识，待后续优化，此处不缓存此信息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunbing49683      2010-9-8  Draft Enact
    2.zhengjunyan 00148421 2010-10-15 Mod:统一各模块资源释放

*****************************************************************************/
VOS_VOID  NAS_EMM_TAU_ClearResouce( VOS_VOID )
{
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_ClearResouce entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_ClearResouce_ENUM,LNAS_ENTRY);

    /* 初始化TAU全局变量 */
    NAS_LMM_MEM_SET_S(&g_stEmmTAUCtrlTbl, sizeof(g_stEmmTAUCtrlTbl), 0, sizeof(g_stEmmTAUCtrlTbl));

    g_stEmmTAUCtrlTbl.enEmmTauType = NAS_EMM_CN_TAU_TYPE_TA_UPDATING;

    /* 释放缓存的ESM消息*/
    NAS_EMM_SerClearEsmDataBuf();

    /* 清空接入Bar信息*/
    NAS_EMM_ClearBarResouce();

    /*停止相关定时器*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_TAU_T3430);
    NAS_LMM_Stop3402Timer();
    NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3411);
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_TAU_SuspendInitClearResouce
 Description     : UE挂起清理TAU流程所有资源
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.FTY       2012-02-24  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_TAU_SuspendInitClearResouce( VOS_VOID )
{
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_SuspendInitClearResouce entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_SuspendInitClearResouce_ENUM,LNAS_ENTRY);

    /* 初始化TAU全局变量 */
    NAS_LMM_MEM_SET_S(&g_stEmmTAUCtrlTbl, sizeof(g_stEmmTAUCtrlTbl), 0, sizeof(g_stEmmTAUCtrlTbl));

    g_stEmmTAUCtrlTbl.enEmmTauType = MMC_LMM_TA_UPDATING;

    /* 释放缓存的ESM消息*/
    NAS_EMM_SerClearEsmDataBuf();

    /* 清空接入Bar信息*/
    NAS_EMM_ClearBarResouce();

    /*停止相关定时器*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_TAU_T3430);
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

    return;
}

VOS_VOID  NAS_EMM_FreeTauDyn( VOS_VOID )
{
    /*需要时添加操作*/

    return;
}


VOS_VOID    NAS_EMM_TAUSER_FSMTranState(
                                    NAS_EMM_MAIN_STATE_ENUM_UINT16  stMS,
                                    NAS_EMM_SUB_STATE_ENUM_UINT16   stSS,
                                    NAS_EMM_STATE_TI_ENUM_UINT16    stTI

)
{

    NAS_LMM_FSM_STATE_STRU              EmmStat;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAUSER_FSMTranState is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAUSER_FSMTranState_ENUM,LNAS_ENTRY);

    EmmStat.enFsmId                   = NAS_LMM_PARALLEL_FSM_EMM;
    EmmStat.enMainState               = stMS;
    EmmStat.enSubState                = stSS;
    EmmStat.enStaTId                  = stTI;
    NAS_LMM_StaTransProc(EmmStat);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_TauUpdateGutiFromCnMsg
 Description     : 收到 TAU ACP消息，更新 GUTI
 Input           :
 Output          :
 Return          :
 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_EMM_TauUpdateGutiFromCnMsg(
                                const NAS_EMM_CN_TAU_ACP_STRU     *pstTAUAcp)
{
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_TauUpdateGutiFromCnMsg is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TauUpdateGutiFromCnMsg_ENUM,LNAS_ENTRY);

    if(NAS_EMM_BIT_SLCT == pstTAUAcp->ucBitOpGuti)
    {
        NAS_LMM_GetEmmInfoUeidAddr()->bitOpGuti = NAS_EMM_BIT_SLCT;
        NAS_LMM_MEM_CPY_S(              NAS_LMM_GetEmmInfoUeidGutiAddr() ,
                                        sizeof(NAS_EMM_GUTI_STRU),
                                        &(pstTAUAcp->stGuti),
                                        sizeof(NAS_EMM_GUTI_STRU));

    }

    return;
}

/*******************************************************************************
  Module   :
  Function : NAS_EMM_TaiListSet
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190  2008.09.17  新规作成
    2.  X00148705         2009.06.29  增加bitOpTaiList的设置。
*******************************************************************************/
VOS_VOID NAS_EMM_TAUSER_TaiListSet( const NAS_EMM_TA_LIST_STRU *pstTALIST)
{
    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO( "NAS_EMM_TAUSER_TaiListSet is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAUSER_TaiListSet_ENUM,LNAS_ENTRY);

    /* 更新TAILIST的全局变量 */
    NAS_LMM_MEM_CPY_S(                          &(g_stEmmInfo.stNetInfo.stTaiList),
                                                sizeof(NAS_MM_TA_LIST_STRU),
                                                pstTALIST,
                                                sizeof(NAS_EMM_TA_LIST_STRU));
    g_stEmmInfo.stNetInfo.bitOpTaiList =        NAS_EMM_BIT_SLCT;

    return;
}


NasMmIntraMsgBlock *    NAS_EMM_TAUSER_GetSendIntraMsgBuffAddr(VOS_UINT32 ulBuffSize)
{
    NasMmIntraMsgBlock *                    pIntraMsg = NAS_EMM_NULL_PTR;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO( "NAS_EMM_TAUSER_GetSendIntraMsgBuffAddr is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAUSER_GetSendIntraMsgBuffAddr_ENUM,LNAS_ENTRY);

    pIntraMsg = NAS_LMM_GetSendIntraMsgBuffAddr(ulBuffSize );

    return pIntraMsg;
}


VOS_VOID* NAS_EMM_TauRsltCommProc( VOS_VOID )
{
    LMM_MMC_TAU_RESULT_IND_STRU     *pstRsltInd = NAS_EMM_NULL_PTR;

    /* 申请MMC内部消息 */
    pstRsltInd  = (VOS_VOID *)NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_TAU_RESULT_IND_STRU));

    if(NAS_EMM_NULL_PTR == pstRsltInd)
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_TauRsltCommProc: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_TauRsltCommProc_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_NULL_PTR;
    }

    NAS_LMM_MEM_SET_S(  pstRsltInd,
                        sizeof(LMM_MMC_TAU_RESULT_IND_STRU),
                        0,
                        sizeof(LMM_MMC_TAU_RESULT_IND_STRU));

    /* 填充给MMC的DOPRA头 */
    EMM_PUBU_COMP_MMC_MSG_HEADER(       pstRsltInd,
                                        sizeof(LMM_MMC_TAU_RESULT_IND_STRU) -
                                        EMM_LEN_VOS_MSG_HEADER);

    /*填充OPID*/


    /* 填充消息ID */
    pstRsltInd->ulMsgId                 = ID_LMM_MMC_TAU_RESULT_IND;

    /* 注册/服务状态上报上移优化:TAU 结果带EU值 */
    pstRsltInd->bitOpEpsUpdateStuts     = NAS_EMM_BIT_SLCT;
    pstRsltInd->enEmmUpStat             = NAS_EMM_UPDATE_STAE;

    return pstRsltInd;
}
/*******************************************************************************
  Module   : NAS_EMM_TauRstLeadSndAttachRst
  Function :
  Input    :
  Output   :
  NOTE     : 无
  Return   : 无
  History  :
    1.  z00179470  2011.12.15  新规作成
*******************************************************************************/
VOS_VOID NAS_EMM_TauRstLeadSndAttachRst(MMC_LMM_ATTACH_RSLT_ENUM_UINT32 ulAttRst)
{
    if (NAS_EMM_OK == NAS_EMM_CheckAppMsgPara(ID_MMC_LMM_ATTACH_REQ))
    {
        if( (MMC_LMM_ATT_REQ_TYPE_CS_ONLY == NAS_EMM_GLO_GetAttReqType())
          ||(MMC_LMM_ATT_REQ_TYPE_CS_PS == NAS_EMM_GLO_GetAttReqType()))
        {
           NAS_EMM_AppSendAttRstInTau(ulAttRst);
        }
    }
    return;
}
/*******************************************************************************
  Module   : NAS_EMM_TauRstSuccLeadSndAttachRst
  Function :
  Input    :
  Output   :
  NOTE     : 无
  Return   : 无
  History  :
    1.  z00179470  2011.12.15  新规作成
*******************************************************************************/
VOS_VOID NAS_EMM_TauRstSuccLeadSndAttachRst( VOS_VOID)
{
    /* 如果是ATTACH引起的TAU，在TAU结束后上报ATTACH */
    if (NAS_EMM_OK == NAS_EMM_CheckAppMsgPara(ID_MMC_LMM_ATTACH_REQ))
    {
        if( (MMC_LMM_ATT_REQ_TYPE_CS_ONLY == NAS_EMM_GLO_GetAttReqType())
          ||(MMC_LMM_ATT_REQ_TYPE_CS_PS == NAS_EMM_GLO_GetAttReqType()))
        {
            /* CS_PS的TAU成功,返回结果为成功*/
            if( (NAS_EMM_EPS_UPDATE_RST_COMBINED_TA_LA_UPDATED == NAS_EMM_TAU_GetEpsUpdateRslt())
              ||(NAS_EMM_EPS_UPDATE_RST_COMBINED_TA_LA_UPDATED_AND_ISR == NAS_EMM_TAU_GetEpsUpdateRslt()))
            {
                NAS_EMM_AppSendAttRstInTau(MMC_LMM_ATT_RSLT_SUCCESS);
            }
            /* 只有PS成功，结果为失败 */
            else
            {
                NAS_EMM_AppSendAttRstInTau(MMC_LMM_ATT_RSLT_FAILURE);
            }
        }
    }
    return;
}


MMC_LMM_TAU_TYPE_ENUM_UINT32  NAS_EMM_MmcTauReqTypeInTauRslt(VOS_VOID)
{
    NAS_EMM_CN_TAU_TYPE_ENUM_UINT32     ulCnTauType;

    ulCnTauType = NAS_EMM_TAU_GetTAUtype();
    if(ulCnTauType == NAS_EMM_CN_TAU_TYPE_TA_UPDATING)
    {
        return  MMC_LMM_TA_UPDATING;
    }
    if(ulCnTauType == NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_UPDATING)
    {
        return  MMC_LMM_COMBINED_TA_LA_UPDATING;
    }
    if(ulCnTauType == NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI)
    {
        return  MMC_LMM_COMBINED_TA_LA_WITH_IMSI;
    }

    if( NAS_LMM_REG_DOMAIN_PS == NAS_EMM_TAU_GetPeriodTauRegDomain())
    {
        return  MMC_LMM_PS_PERIODIC_UPDATING;
    }
    else if(NAS_LMM_REG_DOMAIN_CS_PS == NAS_EMM_TAU_GetPeriodTauRegDomain())
    {
        return  MMC_LMM_CS_PS_PERIODIC_UPDATING;
    }
    else
    {

    }

    NAS_EMM_TAU_LOG_ERR("NAS_EMM_MmcPeriodTauReqType: RegState is WRONG !!");
    TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmcTauReqTypeInTauRslt_ENUM,LNAS_ERROR);
    return  MMC_LMM_TAU_TYPE_BUTT;

}


/*****************************************************************************
 Function Name   : NAS_EMM_MmcSendTauActionResultIndSucc
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-4-7  Draft Enact
    2.yanglei 00307272    2015-7-15 周期TAU,不携带原因值

*****************************************************************************/
VOS_VOID  NAS_EMM_MmcSendTauActionResultIndSucc(VOS_VOID)
{
    LMM_MMC_TAU_RESULT_IND_STRU     *pstRsltInd = NAS_EMM_NULL_PTR;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MmcSendTauActionResultIndSucc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcSendTauActionResultIndSucc_ENUM,LNAS_ENTRY);

    pstRsltInd = NAS_EMM_TauRsltCommProc();
    if (NAS_EMM_NULL_PTR == pstRsltInd)
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_MmcSendTauActionResultIndSucc: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmcSendTauActionResultIndSucc_ENUM,LNAS_NULL_PTR);
        return;
    }

    /* 填充消息内容 */
    pstRsltInd->ulTauRst                = MMC_LMM_TAU_RSLT_SUCCESS;
    pstRsltInd->ulReqType               = NAS_EMM_MmcTauReqTypeInTauRslt();

    pstRsltInd->bitOpCnRst              = NAS_EMM_BIT_SLCT;
    pstRsltInd->ulCnRst                 = NAS_EMM_TAU_GetEpsUpdateRslt();


    /*填充EPLMN*/
    pstRsltInd->bitOpEplmn              = NAS_EMM_BIT_SLCT;
    if (NAS_EMM_BIT_SLCT == NAS_LMM_GetEmmInfoNetInfoOpEplmnListAddr())
    {
        NAS_EMM_TAU_LOG1_INFO("NAS_EMM_MmcSendTauActionResultIndSucc: EPMN NUM ==",
                            NAS_LMM_GetEmmInfoNetInfoEplmnListAddr()->ulPlmnNum);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_MmcSendTauActionResultIndSucc_ENUM,LNAS_EMM_PLMN,
                            NAS_LMM_GetEmmInfoNetInfoEplmnListAddr()->ulPlmnNum);
        NAS_LMM_MEM_CPY_S(              &pstRsltInd->stEplmnList,
                                        sizeof(MMC_LMM_EPLMN_STRU),
                                        NAS_LMM_GetEmmInfoNetInfoEplmnListAddr(),
                                        sizeof(MMC_LMM_EPLMN_STRU));
    }

    /*填充LAI*/
    if (NAS_EMM_BIT_SLCT == NAS_EMM_TAU_GetOpLai())
    {
        pstRsltInd->bitOpLai            = NAS_EMM_BIT_SLCT;
        NAS_LMM_MEM_CPY_S(              &pstRsltInd->stLai,
                                        sizeof(MMC_LMM_LAI_STRU),
                                        NAS_EMM_TAU_GetLaiAddr(),
                                        sizeof(MMC_LMM_LAI_STRU));
    }
    /*填充TMSI*/
    if (NAS_EMM_BIT_SLCT == NAS_EMM_TAU_GetOpMsId())
    {
        pstRsltInd->bitOpMsIdentity           = NAS_EMM_BIT_SLCT;
        NAS_LMM_MEM_CPY_S(              pstRsltInd->stMsIdentity.aucMsIdentity,
                                        NAS_MAX_SIZE_MS_IDENTITY,
                                        NAS_EMM_TAU_GetMsIdAddr()->aucMsId,
                                        NAS_MAX_SIZE_MS_IDENTITY);
    }
    /*填充消息内容----EMM CAUSE。24301 5.5.3.2章节对周期性TAU处理的描述，没有要求
    在周期性TAU成功时要处理原因值，在逻辑上，周期性TAU也不应该携带原因值，为了防止
    GUNAS在周期性TAU成功时还处理原因值导致影响到CS域的注册状态，LMM在周期性TAU成功
    时，即使网侧误携带了原因值，LMM也不带给GUNAS*/
    if ((NAS_EMM_BIT_SLCT == NAS_EMM_TAU_GetOpCnCause())&&
        (pstRsltInd->ulReqType != MMC_LMM_CS_PS_PERIODIC_UPDATING)&&
        (pstRsltInd->ulReqType != MMC_LMM_PS_PERIODIC_UPDATING))
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttSucc:EMM CAUSE");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcSendTauActionResultIndSucc_ENUM,LNAS_CAUSE_NUMBER);
        pstRsltInd->bitOpCnCause        = NAS_EMM_BIT_SLCT;
        pstRsltInd->ucCnCause           = NAS_EMM_TAU_GetCnCause();
    }
    /* 填充TAU ATTEMPT COUTER */
    if (NAS_EMM_NULL != NAS_EMM_TAU_GetEmmTAUAttemptCnt())
    {
        pstRsltInd->bitOpAtmpCnt        = NAS_EMM_BIT_SLCT;
        pstRsltInd->ulAttemptCount      = NAS_EMM_TAU_GetEmmTAUAttemptCnt();
    }
    /* 发送LMM_MMC_TAU_RESULT_IND消息 */
    NAS_LMM_SendLmmMmcMsg(                    pstRsltInd);

    NAS_EMM_TauRstSuccLeadSndAttachRst();
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MmcSendTauActionResultIndRejTaUpdatedOnly
 Description     : 在联合TAU,结果值为TA UPDATED ONLY，原因值为其他或者不带时，给
                   MMC发送TAU RESULT IND消息
 Input           : pstRsvMsg--------------TAU ACCEPT消息指针
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-08-24    Draft Enact
    2.lihong 00150010     2011-11-18    Modify
    3.sunjitan 00193151   2012-05-31  Modify     原因值不为#2#16#17#18#22时不给MMC上报原因值
*****************************************************************************/
VOS_VOID  NAS_EMM_MmcSendTauActionResultIndRejTaUpdatedOnly
(
    const VOS_VOID                     *pvTauRslt
)
{
    LMM_MMC_TAU_RESULT_IND_STRU     *pstRsltInd = NAS_EMM_NULL_PTR;
    VOS_UINT32                      ulTaRslt;

    (VOS_VOID)pvTauRslt;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MmcSendTauActionResultIndRejTaUpdatedOnly is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcSendTauActionResultIndRejTaUpdatedOnly_ENUM,LNAS_ENTRY);

    pstRsltInd = NAS_EMM_TauRsltCommProc();
    if (NAS_EMM_NULL_PTR == pstRsltInd)
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_MmcSendTauActionResultIndRejTaUpdatedOnly: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmcSendTauActionResultIndRejTaUpdatedOnly_ENUM,LNAS_NULL_PTR);
        return;
    }
    /* 大数据: 更新TAU OTHERS_FAIL次数 */
    NAS_LMM_AddTauCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
    /* 填充消息内容 */
    pstRsltInd->ulTauRst                = MMC_LMM_TAU_RSLT_CN_REJ;
    pstRsltInd->ulReqType               = NAS_EMM_MmcTauReqTypeInTauRslt();

    pstRsltInd->bitOpCnRst              = NAS_EMM_BIT_SLCT;
    pstRsltInd->ulCnRst                 = NAS_EMM_TAU_GetEpsUpdateRslt();

    /*填充EPLMN*/
    pstRsltInd->bitOpEplmn              = NAS_EMM_BIT_SLCT;
    if (NAS_EMM_BIT_SLCT == NAS_LMM_GetEmmInfoNetInfoOpEplmnListAddr())
    {
        NAS_EMM_TAU_LOG1_INFO("NAS_EMM_MmcSendTauActionResultIndRejTaUpdatedOnly: EPMN NUM ==",
                            NAS_LMM_GetEmmInfoNetInfoEplmnListAddr()->ulPlmnNum);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_MmcSendTauActionResultIndRejTaUpdatedOnly_ENUM,LNAS_EMM_PLMN,
                            NAS_LMM_GetEmmInfoNetInfoEplmnListAddr()->ulPlmnNum);
        NAS_LMM_MEM_CPY_S(              &pstRsltInd->stEplmnList,
                                        sizeof(MMC_LMM_EPLMN_STRU),
                                        NAS_LMM_GetEmmInfoNetInfoEplmnListAddr(),
                                        sizeof(MMC_LMM_EPLMN_STRU));
    }

    /*填充LAI*/
    if (NAS_EMM_BIT_SLCT == NAS_EMM_TAU_GetOpLai())
    {
        pstRsltInd->bitOpLai            = NAS_EMM_BIT_SLCT;
        NAS_LMM_MEM_CPY_S(              &pstRsltInd->stLai,
                                        sizeof(MMC_LMM_LAI_STRU),
                                        NAS_EMM_TAU_GetLaiAddr(),
                                        sizeof(MMC_LMM_LAI_STRU));
    }

    /*填充TMSI*/
    if (NAS_EMM_BIT_SLCT == NAS_EMM_TAU_GetOpMsId())
    {
        pstRsltInd->bitOpMsIdentity           = NAS_EMM_BIT_SLCT;
        NAS_LMM_MEM_CPY_S(              pstRsltInd->stMsIdentity.aucMsIdentity,
                                        NAS_MAX_SIZE_MS_IDENTITY,
                                        NAS_EMM_TAU_GetMsIdAddr()->aucMsId,
                                        NAS_MAX_SIZE_MS_IDENTITY);
    }

    /* 原因值不为#2#16#17#18#22时不给MMC上报原因值 */
    /*填充消息内容----EMM CAUSE*/
    pstRsltInd->bitOpCnCause            = NAS_EMM_BIT_NO_SLCT;
    pstRsltInd->ucCnCause               = NAS_EMM_CAUSE_BUTT;

    /* 填充TAU ATTEMPT COUTER */
    if (NAS_EMM_NULL != NAS_EMM_TAU_GetEmmTAUAttemptCnt())
    {
        pstRsltInd->bitOpAtmpCnt        = NAS_EMM_BIT_SLCT;
        pstRsltInd->ulAttemptCount      = NAS_EMM_TAU_GetEmmTAUAttemptCnt();

        /* 如果TAU尝试次数小于5，则携带EPS update status和TAI是否在TAI LIST中标识 */
        if (NAS_EMM_TAU_ATTEMPT_CNT_MAX > pstRsltInd->ulAttemptCount)
        {
            pstRsltInd->bitOpEpsUpdateStuts = NAS_EMM_BIT_SLCT;
            pstRsltInd->enEmmUpStat         = NAS_EMM_UPDATE_STAE;
            pstRsltInd->bitOpTaiInListFlag  = NAS_EMM_BIT_SLCT;

            ulTaRslt                        = NAS_EMM_TAU_IsCurrentTAInTaList();
            if (NAS_EMM_SUCC == ulTaRslt)
            {
                pstRsltInd->enTaiInListFlag = MMC_LMM_TAI_IN_TAI_LIST;
            }
            else
            {
                pstRsltInd->enTaiInListFlag = MMC_LMM_TAI_NOT_IN_TAI_LIST;
            }
        }
    }

    /* 发送LMM_MMC_TAU_RESULT_IND消息 */
    NAS_LMM_SendLmmMmcMsg(                    pstRsltInd);

    /* 如果是ATTACH引起的TAU，在TAU结束后上报ATTACH */
    NAS_EMM_TauRstLeadSndAttachRst(MMC_LMM_ATT_RSLT_FAILURE);

    return;
}


VOS_VOID  NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara( VOS_VOID )
{
    LMM_MMC_TAU_RESULT_IND_STRU     *pstRsltInd = NAS_EMM_NULL_PTR;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara_ENUM,LNAS_ENTRY);

    pstRsltInd = NAS_EMM_TauRsltCommProc();
    if (NAS_EMM_NULL_PTR == pstRsltInd)
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara_ENUM,LNAS_NULL_PTR);
        return;
    }

    /* 填充消息内容 */
    pstRsltInd->ulTauRst                = MMC_LMM_TAU_RSLT_SUCCESS;
    pstRsltInd->ulReqType               = NAS_EMM_MmcTauReqTypeInTauRslt();


    /* 发送LMM_MMC_TAU_RESULT_IND消息 */
    NAS_LMM_SendLmmMmcMsg(                    pstRsltInd);

    /* 如果是ATTACH引起的TAU，在TAU结束后上报ATTACH */
    NAS_EMM_TauRstLeadSndAttachRst(MMC_LMM_ATT_RSLT_FAILURE);

    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_IsTauRejCauseOthers
 Description     : 判断TAU REJ原因值是否为5.5.3.2.5章节所列
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-11-18  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_IsTauRejCauseOthers
(
    VOS_UINT8                           ucCnCause
)
{
    VOS_UINT32                          ulRslt = NAS_EMM_YES;

    switch(ucCnCause)
    {
        case    NAS_LMM_CAUSE_ILLEGAL_UE   :
        case    NAS_LMM_CAUSE_ILLEGAL_ME   :
        case    NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW   :
        case    NAS_LMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW:
        case    NAS_LMM_CAUSE_UE_ID_NOT_DERIVED    :
        case    NAS_LMM_CAUSE_IMPLICIT_DETACHED   :
        case    NAS_LMM_CAUSE_PLMN_NOT_ALLOW    :
        case    NAS_LMM_CAUSE_TA_NOT_ALLOW   :
        case    NAS_LMM_CAUSE_ROAM_NOT_ALLOW    :
        case    NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN    :
        case    NAS_LMM_CAUSE_NO_SUITABL_CELL   :
        case    NAS_LMM_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG   :
        case    NAS_LMM_CAUSE_NO_EPS_BEARER_CONTEXT_ACTIVATED:

                ulRslt = NAS_EMM_NO;
                break;
        default :

                ulRslt = NAS_EMM_YES;
                break;
    }

    return ulRslt;
}



VOS_VOID  NAS_EMM_MmcSendTauActionResultIndRej
(
    const VOS_VOID                     *pvTauRslt
)
{
    LMM_MMC_TAU_RESULT_IND_STRU     *pstRsltInd  = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulTaRslt = NAS_EMM_FAIL;
    NAS_LMM_CN_CAUSE_ENUM_UINT8         ucCnCause  = NAS_EMM_CAUSE_BUTT;

    (VOS_VOID)pvTauRslt;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MmcSendTauActionResultIndRej is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcSendTauActionResultIndRej_ENUM,LNAS_ENTRY);

    pstRsltInd = NAS_EMM_TauRsltCommProc();
    if (NAS_EMM_NULL_PTR == pstRsltInd)
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_MmcSendTauActionResultIndRej: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmcSendTauActionResultIndRej_ENUM,LNAS_NULL_PTR);
        return;
    }
    /* 大数据: 更新TAU OTHERS_FAIL次数 */
    NAS_LMM_AddTauCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
    ucCnCause                             = NAS_EMM_TAU_GetEmmTauCnRejCause();
    /* 填充消息内容 */
    pstRsltInd->ulTauRst                = MMC_LMM_TAU_RSLT_CN_REJ;
    pstRsltInd->ulReqType               = NAS_EMM_MmcTauReqTypeInTauRslt();


    /*填充拒绝原因值*/
    pstRsltInd->bitOpCnCause            = NAS_EMM_BIT_SLCT;
    pstRsltInd->ucCnCause               = ucCnCause;

    if (NAS_EMM_NULL != NAS_EMM_TAU_GetEmmTAUAttemptCnt())
    {
        pstRsltInd->bitOpAtmpCnt        = NAS_EMM_BIT_SLCT;
        pstRsltInd->ulAttemptCount      = NAS_EMM_TAU_GetEmmTAUAttemptCnt();

        /* 如果TAU REJ原因值不为5.5.3.2.5章节所列，且TAU尝试次数小于5，
           则携带EPS update status和TAI是否在TAI LIST中标识 */
        if ((NAS_EMM_YES == NAS_EMM_IsTauRejCauseOthers(ucCnCause))
            && (NAS_EMM_TAU_ATTEMPT_CNT_MAX > pstRsltInd->ulAttemptCount))
        {
            pstRsltInd->bitOpEpsUpdateStuts = NAS_EMM_BIT_SLCT;
            pstRsltInd->enEmmUpStat         = NAS_EMM_UPDATE_STAE;
            pstRsltInd->bitOpTaiInListFlag  = NAS_EMM_BIT_SLCT;

            ulTaRslt                        = NAS_EMM_TAU_IsCurrentTAInTaList();
            if (NAS_EMM_SUCC == ulTaRslt)
            {
                pstRsltInd->enTaiInListFlag = MMC_LMM_TAI_IN_TAI_LIST;
            }
            else
            {
                pstRsltInd->enTaiInListFlag = MMC_LMM_TAI_NOT_IN_TAI_LIST;
            }
        }
    }

    /* 发送LMM_MMC_TAU_RESULT_IND消息 */
    NAS_LMM_SendLmmMmcMsg(                    pstRsltInd);

    /* 如果是ATTACH引起的TAU，在TAU结束后上报ATTACH */
    NAS_EMM_TauRstLeadSndAttachRst(MMC_LMM_ATT_RSLT_FAILURE);

    return;
}


VOS_VOID  NAS_EMM_MmcSendTauActionResultIndTimerExp
(
    const VOS_VOID                     *pvTauRslt
)
{
    LMM_MMC_TAU_RESULT_IND_STRU     *pstRsltInd  = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulTaRslt = NAS_EMM_FAIL;

    (VOS_VOID)pvTauRslt;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MmcSendTauActionResultIndTimerExp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcSendTauActionResultIndTimerExp_ENUM,LNAS_ENTRY);

    pstRsltInd = NAS_EMM_TauRsltCommProc();
    if (NAS_EMM_NULL_PTR == pstRsltInd)
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_MmcSendTauActionResultIndTimerExp: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmcSendTauActionResultIndTimerExp_ENUM,LNAS_NULL_PTR);
        return;
    }
    /* 大数据: 更新TAU OTHERS_FAIL次数 */
    NAS_LMM_AddTauCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
    /* 填充消息内容 */
    pstRsltInd->ulTauRst                = MMC_LMM_TAU_RSLT_TIMER_EXP;
    pstRsltInd->ulReqType               = NAS_EMM_MmcTauReqTypeInTauRslt();


    /*填充尝试次数*/
    pstRsltInd->bitOpAtmpCnt            = NAS_EMM_BIT_SLCT;
    pstRsltInd->ulAttemptCount          = NAS_EMM_TAU_GetEmmTAUAttemptCnt();

   /* 如果TAU尝试次数小于5，则携带EPS update status和TAI是否在TAI LIST中标识 */
    if (NAS_EMM_TAU_ATTEMPT_CNT_MAX > pstRsltInd->ulAttemptCount)
    {
        pstRsltInd->bitOpEpsUpdateStuts = NAS_EMM_BIT_SLCT;
        pstRsltInd->enEmmUpStat         = NAS_EMM_UPDATE_STAE;
        pstRsltInd->bitOpTaiInListFlag  = NAS_EMM_BIT_SLCT;

        ulTaRslt                        = NAS_EMM_TAU_IsCurrentTAInTaList();
        if (NAS_EMM_SUCC == ulTaRslt)
        {
            pstRsltInd->enTaiInListFlag = MMC_LMM_TAI_IN_TAI_LIST;
        }
        else
        {
            pstRsltInd->enTaiInListFlag = MMC_LMM_TAI_NOT_IN_TAI_LIST;
        }
    }

    /* 发送LMM_MMC_TAU_RESULT_IND消息 */
    NAS_LMM_SendLmmMmcMsg(                    pstRsltInd);

    /* 如果是ATTACH引起的TAU，在TAU结束后上报ATTACH */
    NAS_EMM_TauRstLeadSndAttachRst(MMC_LMM_ATT_RSLT_FAILURE);

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_MmcSendTauActionResultIndFailWithPara
 Description     : 底层失败或连接释放，给MMC回复LMM_MMC_TAU_RESULT_IND消息，
                    结果为失败，携带尝试次数
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-4-25     Draft Enact
    2.lihong 00150010     2011-11-18    Modify

*****************************************************************************/
VOS_VOID  NAS_EMM_MmcSendTauActionResultIndFailWithPara
(
    const VOS_VOID                     *pvTauRslt
)
{
    LMM_MMC_TAU_RESULT_IND_STRU     *pstRsltInd  = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulTaRslt = NAS_EMM_FAIL;

    (VOS_VOID)pvTauRslt;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MmcSendTauActionResultIndFailWithPara is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcSendTauActionResultIndFailWithPara_ENUM,LNAS_ENTRY);

    pstRsltInd = NAS_EMM_TauRsltCommProc();
    if (NAS_EMM_NULL_PTR == pstRsltInd)
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_MmcSendTauActionResultIndFailWithPara: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmcSendTauActionResultIndFailWithPara_ENUM,LNAS_NULL_PTR);
        return;
    }
    /* 大数据: 更新TAU OTHERS_FAIL次数 */
    NAS_LMM_AddTauCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
    /* 填充消息内容 */
    pstRsltInd->ulTauRst                = MMC_LMM_TAU_RSLT_FAILURE;

    pstRsltInd->ulReqType               = NAS_EMM_MmcTauReqTypeInTauRslt();


    if (NAS_EMM_NULL != NAS_EMM_TAU_GetEmmTAUAttemptCnt())
    {
        pstRsltInd->bitOpAtmpCnt        = NAS_EMM_BIT_SLCT;
        pstRsltInd->ulAttemptCount      = NAS_EMM_TAU_GetEmmTAUAttemptCnt();

        /* 如果TAU尝试次数小于5，则携带EPS update status和TAI是否在TAI LIST中标识 */
        if (NAS_EMM_TAU_ATTEMPT_CNT_MAX > pstRsltInd->ulAttemptCount)
        {
            pstRsltInd->bitOpEpsUpdateStuts = NAS_EMM_BIT_SLCT;
            pstRsltInd->enEmmUpStat         = NAS_EMM_UPDATE_STAE;
            pstRsltInd->bitOpTaiInListFlag  = NAS_EMM_BIT_SLCT;

            ulTaRslt                        = NAS_EMM_TAU_IsCurrentTAInTaList();
            if (NAS_EMM_SUCC == ulTaRslt)
            {
                pstRsltInd->enTaiInListFlag = MMC_LMM_TAI_IN_TAI_LIST;
            }
            else
            {
                pstRsltInd->enTaiInListFlag = MMC_LMM_TAI_NOT_IN_TAI_LIST;
            }
        }
    }

    /* 发送LMM_MMC_TAU_RESULT_IND消息 */
    NAS_LMM_SendLmmMmcMsg(                    pstRsltInd);

    /* 如果是ATTACH引起的TAU，在TAU结束后上报ATTACH */
    NAS_EMM_TauRstLeadSndAttachRst(MMC_LMM_ATT_RSLT_FAILURE);

    return;
}



VOS_VOID  NAS_EMM_MmcSendTauActionResultIndOthertype
(
    const VOS_VOID                     *pvTauRslt
)
{
    LMM_MMC_TAU_RESULT_IND_STRU     *pstRsltInd = NAS_EMM_NULL_PTR;
    MMC_LMM_TAU_RSLT_ENUM_UINT32     ulTauRslt;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MmcSendTauActionResultIndOthertype is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcSendTauActionResultIndOthertype_ENUM,LNAS_ENTRY);

    ulTauRslt = *(MMC_LMM_TAU_RSLT_ENUM_UINT32*)pvTauRslt;


    pstRsltInd = NAS_EMM_TauRsltCommProc();
    if (NAS_EMM_NULL_PTR == pstRsltInd)
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_MmcSendTauActionResultIndOthertype: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmcSendTauActionResultIndOthertype_ENUM,LNAS_NULL_PTR);
        return;
    }
    /* 大数据: 更新TAU OTHERS_FAIL次数 */
    NAS_LMM_AddTauCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
    /* 填充消息内容 */
    if ((MMC_LMM_TAU_RSLT_ACCESS_BARED == ulTauRslt) ||
        (MMC_LMM_TAU_RSLT_AUTH_REJ == ulTauRslt) ||
        (MMC_LMM_TAU_RSLT_FAILURE == ulTauRslt)||
        (MMC_LMM_TAU_RSLT_T3402_RUNNING == ulTauRslt)||
        (MMC_LMM_TAU_RSLT_MO_DETACH_FAILURE == ulTauRslt)||
        (MMC_LMM_TAU_RSLT_MT_DETACH_FAILURE == ulTauRslt)||
        (MMC_LMM_TAU_RSLT_T3402_RUNNING == ulTauRslt)||
        (MMC_LMM_TAU_RSLT_T3402_RUNNING_EPS_ONLY_SUCC == ulTauRslt))
    {
        NAS_EMM_TAU_LOG1_NORM("NAS_EMM_MmcSendTauActionResultIndOthertype:ulTauRslt =",
                            ulTauRslt);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_MmcSendTauActionResultIndOthertype_ENUM,LNAS_FUNCTION_LABEL1,
                            ulTauRslt);
        pstRsltInd->ulTauRst            = ulTauRslt;
    }
    else
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_MmcSendTauActionResultIndOthertype:\
                                Input TAU Result Type is err !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmcSendTauActionResultIndOthertype_ENUM,LNAS_ERROR);
    }

    pstRsltInd->ulReqType               = NAS_EMM_MmcTauReqTypeInTauRslt();


    /* 发送LMM_MMC_TAU_RESULT_IND消息 */
    NAS_LMM_SendLmmMmcMsg(                    pstRsltInd);

    /* 如果是ATTACH引起的TAU，在TAU结束后上报ATTACH */
    NAS_EMM_TauRstLeadSndAttachRst(MMC_LMM_ATT_RSLT_FAILURE);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MmcSendTauActionResultIndForbType
 Description     : 给MMC上报禁止信息结果
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2012-1-10  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_MmcSendTauActionResultIndForbType
(
    const VOS_VOID                     *pvForbInfo
)
{
    LMM_MMC_TAU_RESULT_IND_STRU     *pstRsltInd = NAS_EMM_NULL_PTR;
    EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32 ulForbInfo;

    ulForbInfo = *(EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32*)pvForbInfo;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MmcSendTauActionResultIndForbType is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcSendTauActionResultIndForbType_ENUM,LNAS_ENTRY);

    pstRsltInd = NAS_EMM_TauRsltCommProc();
    if (NAS_EMM_NULL_PTR == pstRsltInd)
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_MmcSendTauActionResultIndForbType: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmcSendTauActionResultIndForbType_ENUM,LNAS_NULL_PTR);
        return;
    }
    /* 大数据: 更新TAU OTHERS_FAIL次数 */
    NAS_LMM_AddTauCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
    NAS_EMM_TAU_LOG1_NORM("NAS_EMM_MmcSendTauActionResultIndForbType:ulForbInfo =",
                            ulForbInfo);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MmcSendTauActionResultIndForbType_ENUM,LNAS_EMM_FORB_INFO,
                            ulForbInfo);

    /* 填充消息内容 */
    if (EMMC_EMM_FORBIDDEN_PLMN == ulForbInfo)
    {
        pstRsltInd->ulTauRst            = MMC_LMM_TAU_RSLT_FORBID_PLMN;
    }
    else if (EMMC_EMM_FORBIDDEN_PLMN_FOR_GPRS == ulForbInfo)
    {
        pstRsltInd->ulTauRst            = MMC_LMM_TAU_RSLT_FORBID_PLMN_FOR_GPRS;
    }
    else if (EMMC_EMM_FORBIDDEN_TA_FOR_ROAMING == ulForbInfo)
    {
        pstRsltInd->ulTauRst            = MMC_LMM_TAU_RSLT_FORBID_TA_FOR_ROAMING;
    }
    else if (EMMC_EMM_FORBIDDEN_TA_FOR_RPOS == ulForbInfo)
    {
        pstRsltInd->ulTauRst            = MMC_LMM_TAU_RSLT_FORBID_TA_FOR_RPOS;
    }
    else if(EMMC_EMM_NO_FORBIDDEN == ulForbInfo)
    {
        /* 系统消息未被禁，但是调用此函数上报结果，一定是ANY CELL的系统消息 */
        pstRsltInd->ulTauRst            = MMC_LMM_TAU_RSLT_FAILURE;
    }
    else
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_MmcSendTauActionResultIndForbType:\
                                Input TAU Result Type is err !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmcSendTauActionResultIndForbType_ENUM,LNAS_ERROR);
        pstRsltInd->ulTauRst            = MMC_LMM_TAU_RSLT_FAILURE;
    }

    pstRsltInd->ulReqType               =  NAS_EMM_MmcTauReqTypeInTauRslt();


    /* 发送LMM_MMC_TAU_RESULT_IND消息 */
    NAS_LMM_SendLmmMmcMsg(                    pstRsltInd);

    /* 如果是ATTACH引起的TAU，在TAU结束后上报ATTACH */
    NAS_EMM_TauRstLeadSndAttachRst(MMC_LMM_ATT_RSLT_FAILURE);

    return;
}


VOS_UINT32    NAS_EMM_SendIntraAttachReq(VOS_VOID)
{
    NAS_LMM_INTRA_ATTACH_REQ_STRU        *pIntraAttachReqMsg = NAS_EMM_NULL_PTR;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO( "NAS_EMM_SendAttachReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendIntraAttachReq_ENUM,LNAS_ENTRY);

    /* 申请DOPRA消息 */
    pIntraAttachReqMsg = (VOS_VOID *)NAS_EMM_TAUSER_GetSendIntraMsgBuffAddr(
                                        sizeof(NAS_LMM_INTRA_ATTACH_REQ_STRU) -
                                        EMM_LEN_VOS_MSG_HEADER);

    if(NAS_EMM_NULL_PTR == pIntraAttachReqMsg)
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_SendAttachReq: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SendIntraAttachReq_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }

    /* 填写NAS_EMM_INTRA_ATTACH_REQ 的DOPRA消息头 */
    EMM_COMP_MM_MSG_HEADER(pIntraAttachReqMsg, sizeof(NAS_LMM_INTRA_ATTACH_REQ_STRU) -
                                        EMM_LEN_VOS_MSG_HEADER);

    /* 填写NAS_EMM_INTRA_ATTACH_REQ 的消息ID标识 */
    pIntraAttachReqMsg->ulMsgId         = ID_NAS_LMM_INTRA_ATTACH_REQ;

    /* 发送消息(Send the msg of) NAS_EMM_INTRA_ATTACH_REQ */
    NAS_EMM_SEND_INTRA_MSG(             pIntraAttachReqMsg);

    return NAS_EMM_SUCC;

}


/*******************************************************************************
  Module   :
  Function : Nas_Emm_TAU_AbnormalOver
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190     2008.09.17  新规作成
    2.  zhengjunyan 00148421 2010.07.30 添加:清空TauStartCasue
*******************************************************************************/
VOS_VOID NAS_EMM_TAU_AbnormalOver( )
{
    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO( "NAS_EMM_TAU_AbnormalOver is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_AbnormalOver_ENUM,LNAS_ENTRY);

    /*停止T3430定时器*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_TAU_T3430);

    /*停止T3440定时器*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

    /* 清除发起TAU的原因值*/
    NAS_EMM_TAU_SaveEmmTAUStartCause(   NAS_EMM_TAU_START_CAUSE_DEFAULT);

    /* 清空Tau Attempt Counter*/
    NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);

    return;
}

/*******************************************************************************
      Module   :
      Function : NAS_EMM_NvimSetEPSUpdataStatus
      Input    :
      Output   :
      NOTE     :
      Return   :
      History  :
        1.  Zhouyan 00125190  2008.09.17  新规作成
*******************************************************************************/
NAS_EMM_UPDATE_STATE_ENUM_UINT8 NAS_EMM_TAU_GetEmmEPSUPState()
{
    NAS_EMM_UPDATE_STATE_ENUM_UINT8   ucupdatastate;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO( "NAS_EMM_TAU_GetEmmEPSUPState is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_GetEmmEPSUPState_ENUM,LNAS_ENTRY);

    ucupdatastate = NAS_EMM_TAUSER_GetAuxFsmUpStat();

    return ucupdatastate;
}



/*******************************************************************************
  Module   :
  Function : NAS_EMM_TAU_SendEsmStatusInd
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190  2008.09.17  新规作成

*******************************************************************************/
VOS_VOID    NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_ENUM_UINT32  stATTACHStatus)
{


    EMM_ESM_STATUS_IND_STRU                *pstsmstatusInd            = NAS_EMM_NULL_PTR;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_TAU_LOG1_INFO( "NAS_EMM_TAU_SendEsmStatusInd is entered.", stATTACHStatus);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_TAU_SendEsmStatusInd_ENUM,LNAS_ENTRY,stATTACHStatus);

    /* 申请DOPRA消息 */
    pstsmstatusInd  = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(EMM_ESM_STATUS_IND_STRU));

    if(NAS_EMM_NULL_PTR == pstsmstatusInd)
    {
        return;
    }

    /* 填充给RRC的DOPRA头 */
    EMM_COMP_ESM_MSG_HEADER(pstsmstatusInd, sizeof(EMM_ESM_STATUS_IND_STRU) -
                                        EMM_LEN_VOS_MSG_HEADER);

    /* 填充消息ID */
    pstsmstatusInd->ulMsgId = ID_EMM_ESM_STATUS_IND;

    /* 填充消息内容 -- stATTACHStatus */
    pstsmstatusInd->enEMMStatus = stATTACHStatus;

    /*clear global:EpsContextStatusChange*/
    if(stATTACHStatus == EMM_ESM_ATTACH_STATUS_DETACHED)
    {
        NAS_EMM_GetEpsContextStatusChange() = NAS_EMM_EPS_BEARER_STATUS_NOCHANGE;
    }

    /* 发送DOPRA消息 */
    NAS_LMM_SEND_MSG(pstsmstatusInd);

    return;

}
/*****************************************************************************
 Function Name   : NAS_EMM_TAU_GetEpsUpdateType
 Description     : 编码TAU REQ消息时，获取Eps Update Type的值
 Input           : 无
 Output          : 无
 Return          : MMC_LMM_TAU_TYPE_ENUM_UINT32

 History         :
    1.lihong00150010      2011-11-18    Draft Enact

*****************************************************************************/
NAS_EMM_CN_TAU_TYPE_ENUM_UINT32 NAS_EMM_TAU_GetEpsUpdateType
(
    NAS_EMM_TAU_START_CAUSE_ENUM_UINT8      enTauStartCause
)
{
    NAS_LMM_REG_DOMAIN_ENUM_UINT32          enRegDomain     = NAS_LMM_REG_DOMAIN_BUTT;


    /* 获取L模注册域 */
    enRegDomain = NAS_LMM_GetEmmInfoRegDomain();

    if (NAS_EMM_TAU_START_CAUSE_T3412EXP == enTauStartCause)
    {
        /* 保存周期性TAU的注册域，
            便于向MMC上报结果时区分是PS_PERIOD_TAU还是CS_PS_PERIOD_TAU */
        NAS_EMM_TAU_SavePeriodTauRegDomain(enRegDomain);
        return  NAS_EMM_CN_TAU_TYPE_PERIODIC_UPDATING;
    }

    /* 判断是否为CP/PS1或者CS/PS2 */
    if (NAS_EMM_NO == NAS_EMM_IsCsPsUeMode())
    {
        return  NAS_EMM_CN_TAU_TYPE_TA_UPDATING;
    }

    /* 判断是否被原因值2拒绝过 */
    if (NAS_EMM_REJ_YES == NAS_LMM_GetEmmInfoRejCause2Flag())
    {
        return  NAS_EMM_CN_TAU_TYPE_TA_UPDATING;
    }

    /* 判断是否被原因值18拒绝过 */
    if (NAS_EMM_REJ_YES == NAS_EMMC_GetRejCause18Flag())
    {
        return  NAS_EMM_CN_TAU_TYPE_TA_UPDATING;
    }

    /* 判断联合DETACH是否被TAU打断 */
    if (NAS_EMM_COM_DET_BLO_YES == NAS_EMM_TAU_GetEmmCombinedDetachBlockFlag())
    {
        return  NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_UPDATING;
    }
    /* 判断是否允许CS域注册 */
    if (NAS_EMM_AUTO_ATTACH_NOT_ALLOW == NAS_EMM_GetCsAttachAllowFlg())
    {
        return  NAS_EMM_CN_TAU_TYPE_TA_UPDATING;
    }

    if(NAS_LMM_REG_DOMAIN_PS == enRegDomain)
    {
        return  NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI;
    }
    else if(NAS_LMM_REG_DOMAIN_CS_PS == enRegDomain)
    {
        return  NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_UPDATING;
    }
    else
    {
        /* 打印异常 */
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_TAU_GetEpsUpdateType:enRegDomain = NAS_LMM_REG_DOMAIN_NULL");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_TAU_GetEpsUpdateType_ENUM,LNAS_FUNCTION_LABEL1);

        return  NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_UPDATING;
    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_TAU_CompCnTAUReqNasMsg
 Description     : 为规避PC-LINT检查数组越界的问题，独立出来一个打包CN消息的函数
 Input           : pulIndex     : 既作输入，也作输出
 Output          : pucCnNasMsg  : 指向 LRRC_LNAS_MSG_STRU.aucNasMsg
                   pulIndex     : 也作输出 : 打包此函数中的码流后，主调函数中字符
                                 下一个可用的字节位置；
 Return          : VOS_UINT32

 History         :
    1.h41410      2009-2-1  Draft Enact  PCLINT修改
    2.zhengjunyan 00148421 2009-12-09  CR39:TAU REQ信元变更
    3.zhengjunyan 00148421 2010-11-23  MOD:问题单DTS2010101502052,Service成功后，
                                       连接态下重新TAU希望携带承载状态与网侧同步，
                                       所以删除携带承载状态IE的判断条件:IDLE和CONN
                                       触发TAU都携带承载状态。
*****************************************************************************/
VOS_VOID    NAS_EMM_TAU_CompCnTAUReqNasMsg
(
    VOS_UINT8      *pucCnNasMsg,
    VOS_UINT32     *pulIndex
)
{
    VOS_UINT32                          ulIndex             = 0;
    VOS_UINT32                          ulIeLength          = 0;
    VOS_UINT8                           ucKsi;
    NAS_EMM_CN_TAU_TYPE_ENUM_UINT32     enTauUpdateType     = NAS_EMM_CN_TAU_TYPE_BUTT;
    NAS_EMM_TAU_START_CAUSE_ENUM_UINT8  enTauStartCause     = NAS_EMM_TAU_START_CAUSE_BUTT;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_TAU_LOG1_INFO("NAS_EMM_TAU_CompCnTAUReqNasMsg is entered.",*pulIndex);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_TAU_CompCnTAUReqNasMsg_ENUM,LNAS_ENTRY,*pulIndex);


    /* 填充 Security header type  +  Protocol Discriminator */
    pucCnNasMsg[ulIndex++]              = EMM_TAU_REQ_MSG_PD_AND_SEC_TY;

    /* 填充 TAU request message identity   */
    pucCnNasMsg[ulIndex++]              = NAS_EMM_CN_MT_TAU_REQ;

    /* 获取TAU更新类型 */
    enTauStartCause = NAS_EMM_TAU_GetEmmTAUStartCause();
    enTauUpdateType = NAS_EMM_TAU_GetEpsUpdateType(enTauStartCause);
    NAS_EMM_TAU_LOG1_NORM("Tau Type: ", enTauUpdateType);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_TAU_CompCnTAUReqNasMsg_ENUM,LNAS_FUNCTION_LABEL1,enTauUpdateType);
    NAS_EMM_TAU_SaveTAUtype(enTauUpdateType);

    /* 填充 EPS update type */
    pucCnNasMsg[ulIndex] = (VOS_UINT8)NAS_EMM_TAU_GetTAUtype();
    pucCnNasMsg[ulIndex] |= (NAS_EMM_TAU_GetEmmTauReqActiveCtrl()&0x1f)<<3;

    /* 填充信元NAS key set identifierASME */
    ucKsi = NAS_EMM_SecuGetKSIValue();
    pucCnNasMsg[ulIndex] |= (VOS_UINT8)(ucKsi << 4);
    ulIndex++;

    /*填充OLD GUTI*/
    NAS_EMM_EncodeOldGuti(              &(pucCnNasMsg[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /*填充Non-current native NAS key set identifier*/
    NAS_EMM_EncodeNonCurrentNativeKSI(  &(pucCnNasMsg[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /*填充GPRS ciphering key sequence number*/
    NAS_EMM_EncodeGprsCkSn(             &(pucCnNasMsg[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /* 填充Old P-TMSI signature*/
    NAS_EMM_EncodePtmsiSignature(       &(pucCnNasMsg[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /*填充Additional GUTI*/
    NAS_EMM_EncodeAdditionalGuti(       &(pucCnNasMsg[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /*填充NonceUE*/
    NAS_EMM_EncodeNonceUE(              &(pucCnNasMsg[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /* 填充UE network capability*/
    if((EMM_TAU_AD_BIT_SLCT == NAS_EMM_TAU_UE_NET_CAP_BIT())
        && ( NAS_EMM_CN_TAU_TYPE_PERIODIC_UPDATING != NAS_EMM_TAU_GetTAUtype()))
    {
        pucCnNasMsg[ulIndex++]          = NAS_EMM_TAU_REQ_UE_NET_CAP_IEI;

        /* UE NETWORK CAPABILITY 是必选IE, LV，3~14*/
        NAS_EMM_EncodeUeNetCapa(        &(pucCnNasMsg[ulIndex]),
                                        NAS_LMM_IE_FORMAT_LV,
                                        &ulIeLength);
        ulIndex += ulIeLength;

    }

    /* 填充Last visited registered TAI */
    NAS_EMM_EncodeLRVTai(               &(pucCnNasMsg[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /* 填充 DRX parameter */
    NAS_EMM_EncodeDrxPara(              &(pucCnNasMsg[ulIndex]),
                                        &ulIeLength,
                                        NAS_EMM_CN_MT_TAU_REQ);
    ulIndex                             += ulIeLength;


    /*填充UE radio capability information update needed*/
    NAS_EMM_EncodeURCUpdateNeed(        &(pucCnNasMsg[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /* 填充EPS bearer context status */
    NAS_EMM_EncodeEpsBearStatus(        &(pucCnNasMsg[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;
    /* 填充 MS network capability */
    NAS_EMM_EncodeMsNetworkCapability(  &(pucCnNasMsg[ulIndex]),
                                        &ulIeLength,
                                        NAS_EMM_CN_MT_TAU_REQ);
    ulIndex                             += ulIeLength;


    /* 填充Old location area identification */
    NAS_EMM_EncodeLai(                  &(pucCnNasMsg[ulIndex]),
                                        &ulIeLength,
                                        NAS_EMM_CN_MT_TAU_REQ);
    ulIndex                             += ulIeLength;


    /*填充TMSI STATUS*/
    NAS_EMM_EncodeTmsiStatus(           &(pucCnNasMsg[ulIndex]),
                                        &ulIeLength,
                                        NAS_EMM_CN_MT_TAU_REQ);
    ulIndex                             += ulIeLength;

    /*填充Mobile station classmark 2*/
    NAS_EMM_EncodeMsClassMark2(         &(pucCnNasMsg[ulIndex]),
                                        &ulIeLength,
                                        NAS_EMM_CN_MT_TAU_REQ);
    ulIndex                             += ulIeLength;

    /*填充Mobile station classmark 3*/
    NAS_EMM_EncodeMsClassMark3(         &(pucCnNasMsg[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /*填充Supported Codecs*/
    NAS_EMM_EncodeSupportedCodecs(      &(pucCnNasMsg[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /*填充Additional update type*/
    if ((NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_UPDATING  == NAS_EMM_TAU_GetTAUtype()) ||
        (NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI == NAS_EMM_TAU_GetTAUtype()))
    {
        NAS_EMM_EncodeAdditionUpdateType(   &(pucCnNasMsg[ulIndex]),
                                            &ulIeLength);
        ulIndex                             += ulIeLength;
    }

    /*填充Voice domain preference and UE's usage setting*/
    NAS_EMM_EncodeVoiceDomainAndUsageSetting(&(pucCnNasMsg[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;
    if (NAS_RELEASE_CTRL)
    {
        /* 填充Old GUTI type */
        NAS_EMM_EncodeGutiType(             &(pucCnNasMsg[ulIndex]),
                                            &ulIeLength);
        ulIndex                            += ulIeLength;
    }

    if (NAS_RELEASE_R11)
    {
        if ((NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_UPDATING  == NAS_EMM_TAU_GetTAUtype()) ||
            (NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI == NAS_EMM_TAU_GetTAUtype()))
        {
            /* 填充TMSI based NRI container */
            NAS_EMM_EncodeTmsiBasedNriContainer(    &(pucCnNasMsg[ulIndex]),
                                                    &ulIeLength);
            ulIndex                             += ulIeLength;
        }
    }

    *pulIndex += ulIndex;

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_EncodeOldGuti
 Description     : Old GUTI编码函数
 Input           : None
 Output          : pMsg-------------IE内容
                   pulIeLength------IE长度
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2011-5-9  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_EncodeOldGuti
(
    VOS_UINT8       *pMsg,
    VOS_UINT32      *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    VOS_UINT32                          ulLen = NAS_EMM_NULL;
    MMC_LMM_TIN_TYPE_ENUM_UINT32        ulTinType;
    ulTinType = NAS_EMM_GetTinType();

    if((VOS_NULL_PTR == pMsg) ||
        (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_EncodeOldGuti: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeOldGuti_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

    if(NAS_EMM_SUCC == NAS_EMM_CheckMutiModeSupport())
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_EncodeOldGuti:SUPPORT GU MODE ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeOldGuti_ENUM,LNAS_FUNCTION_LABEL1);
        if (MMC_LMM_TIN_P_TMSI == ulTinType)
        {
            NAS_EMM_TAU_LOG_NORM("NAS_EMM_EncodeOldGuti:TIN IS P-TMSI ");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeOldGuti_ENUM,LNAS_FUNCTION_LABEL2);
            if (NAS_EMM_SUCC == NAS_EMM_CheckPtmsiAndRaiValidity())
            {
                NAS_EMM_TAU_LOG_NORM("NAS_EMM_EncodeOldGuti:P-TMSI AND RAI VALID ");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeOldGuti_ENUM,LNAS_FUNCTION_LABEL3);
                NAS_EMM_CompMappedGuti(&(pucReqMsg[ulIndex]),&ulLen);
                *pulIeLength                = ulLen;
            }
        }
        else if ((MMC_LMM_TIN_GUTI == ulTinType) ||
            (MMC_LMM_TIN_RAT_RELATED_TMSI == ulTinType))
        {
            NAS_EMM_TAU_LOG_NORM("NAS_EMM_EncodeOldGuti:TIN IS GUTI or RAT RELATED TMSI");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeOldGuti_ENUM,LNAS_FUNCTION_LABEL4);
            if (NAS_EMM_BIT_SLCT == NAS_EMM_TAUSER_OP_GUTI())
            {
                NAS_EMM_TAU_LOG_NORM("NAS_EMM_EncodeOldGuti: NATIVE GUTI VALID");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeOldGuti_ENUM,LNAS_FUNCTION_LABEL5);
                NAS_EMM_CompNativeGuti(&(pucReqMsg[ulIndex]),&ulLen);
                *pulIeLength            = ulLen;
            }
        }
        else
        {
            NAS_EMM_TAU_LOG_ERR("NAS_EMM_EncodeOldGuti: TIN INVALID");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeOldGuti_ENUM,LNAS_FUNCTION_LABEL6);
        }
    }
    else
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_EncodeOldGuti:NOT SUPPORT GU MODE ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeOldGuti_ENUM,LNAS_FUNCTION_LABEL7);
        if (NAS_EMM_BIT_SLCT == NAS_EMM_TAUSER_OP_GUTI())
        {
            NAS_EMM_TAU_LOG_NORM("NAS_EMM_EncodeOldGuti:NATIVE GUTI INVALID ");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeOldGuti_ENUM,LNAS_FUNCTION_LABEL8);
            NAS_EMM_CompNativeGuti(&(pucReqMsg[ulIndex]),&ulLen);
            *pulIeLength                = ulLen;
        }
    }

    return;
}



/*****************************************************************************
 Function Name   : NAS_EMM_IsPtmsiAndConn
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.Hanlufeng 41410      2011-6-24  Draft Enact
    2.sunjitan 00193151   2012-05-24 修改增加处于ISR激活态时的满足条件

*****************************************************************************/
VOS_UINT32  NAS_EMM_IsConnChangeToLte( VOS_VOID )
{
    MMC_LMM_TIN_TYPE_ENUM_UINT32        ulTinType;
    ulTinType = NAS_EMM_GetTinType();
    if((MMC_LMM_TIN_P_TMSI == ulTinType)
        || (MMC_LMM_TIN_RAT_RELATED_TMSI == ulTinType))
    {   /* 刚从GU过来 */

        if( (NAS_LMM_SYS_CHNG_ORI_LRRC == NAS_EMM_GetResumeOri()) &&
            (NAS_LMM_SYS_CHNG_TYPE_HO   == NAS_EMM_GetResumeType())
           )
        {   /* HO,过来 */

            return  NAS_EMM_YES;
        }
    }

    return  NAS_EMM_NO;
}


/*****************************************************************************
 Function Name   : NAS_EMM_IsPtmsiAndIdle
 Description     : 预研认为，CCO和重定向时，网络节点间不存在安全上下文的传递，
                   因此CCO和重定向当做IDLE过程来处理；
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.Hanlufeng 41410      2011-6-24  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_IsPtmsiAndIdle( VOS_VOID )
{
    if(MMC_LMM_TIN_P_TMSI == NAS_EMM_GetTinType())
    {   /* 刚从GU过来 */

        if( (NAS_LMM_SYS_CHNG_ORI_LRRC == NAS_EMM_GetResumeOri()) &&
            (   (NAS_LMM_SYS_CHNG_TYPE_RSL  == NAS_EMM_GetResumeType()) ||
                (NAS_LMM_SYS_CHNG_TYPE_CCO  == NAS_EMM_GetResumeType()) ||
                (NAS_LMM_SYS_CHNG_TYPE_REDIR== NAS_EMM_GetResumeType())
            ))
        {   /* 重选/CCO/重定向 过来 */

            return  NAS_EMM_YES;
        }
        else if(NAS_LMM_SYS_CHNG_ORI_MMC == NAS_EMM_GetResumeOri())
        {   /* MMC触发过来的 */

            return  NAS_EMM_YES;
        }
        else
        {

        }
    }

    return  NAS_EMM_NO;
}



/*****************************************************************************
 Function Name   : NAS_EMM_EncodeNonCurrentNativeKSI
 Description     : Non-current native NAS key set identifier编码函数
 Input           : None
 Output          : pMsg-------Non-current native NAS key set identifier IE 内容
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2011-5-9  Draft Enact
    2.zhengjunyan 00148421 2011-06-02 从SECU模块获取 non-current KSIasme,填充信元
*****************************************************************************/
VOS_VOID  NAS_EMM_EncodeNonCurrentNativeKSI
(
    VOS_UINT8       *pMsg,
    VOS_UINT32      *pulIeLength
)
{
    VOS_UINT8                          *pucReqMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    MMC_LMM_TIN_TYPE_ENUM_UINT32        ulTinType;
    ulTinType = NAS_EMM_GetTinType();

    /* 入参合法性检查*/
    if((VOS_NULL_PTR == pMsg) ||
        (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_EncodeNonCurrentNativeKSI: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeNonCurrentNativeKSI_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
   *pulIeLength                         = NAS_EMM_NULL;

    /* 如果不存在 non-current native security context,则直接返回，不填充该信元*/
    if(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE == NAS_EMM_SecuGetNonCurKSIasme())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_EncodeNonCurrentNativeKSI: no para.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeNonCurrentNativeKSI_ENUM,LNAS_FUNCTION_LABEL1);
        return;
    }

    /* 若是从GU过来，并且CONNECT 态则填，与预研交流，认为重定向也属连接态.
    8.2.29.2    Non-current native NAS key set identifier
    The UE shall include this IE if the UE has a valid non-current native EPS
    security context when the UE performs an A/Gb mode or Iu mode to S1 mode
    inter-system change in EMM-CONNECTED mode and the UE uses a mapped EPS
    security context to protect the TRACKING AREA UPDATE REQUEST message.
    */
    if(NAS_EMM_YES == NAS_EMM_IsConnChangeToLte())
    {
        NAS_EMM_TAU_LOG2_INFO("NAS_EMM_EncodeNonCurrentNativeKSI: TinType = , ResumeType = ",
                                ulTinType,
                                NAS_EMM_GetResumeType());
        /* coverity[unchecked_value] */
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_EncodeNonCurrentNativeKSI_ENUM,LNAS_EMM_TIN_TYPE,
                                ulTinType);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_EncodeNonCurrentNativeKSI_ENUM,LNAS_EMM_RESUME_TYPE,
                                NAS_EMM_GetResumeType());

        /* 填充Non-current native NAS key set identifier IEI*/
        pucReqMsg[ulIndex]              = NAS_EMM_TAU_REQ_NON_CURRENT_NATIVE_KSI;

        /* 填充 Non-current native NAS key set identifier的 TSC */
        pucReqMsg[ulIndex]              |= NAS_EMM_SecuGetNonCurKSIasme();
        ulIndex++;

        /* 信元长度*/
        *pulIeLength = ulIndex;
    }

    /* non-current native security context存在，填充该信元*/

    return;

}

/*****************************************************************************
 Function Name   : NAS_EMM_EncodeGprsCkSn
 Description     : GPRS ciphering key sequence number编码函数
 Input           : None
 Output          : pMsg-------------GPRS ciphering key sequence number内容

 Return          : VOS_VOID

 History         :
    1.leili 00132387      2011-5-9  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_EncodeGprsCkSn
(
    VOS_UINT8       *pMsg,
    VOS_UINT32      *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    VOS_UINT8                           ucGprsCkSn = NAS_EMM_NULL;

    if((VOS_NULL_PTR == pMsg) ||
        (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_EncodeGprsCkSn: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeGprsCkSn_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

    ucGprsCkSn = (VOS_UINT8)NAS_EMM_SecuGetUmtsKsi();

    /*
    8.2.29.3    GPRS ciphering key sequence number
    The UE shall include this IE if the UE performs an A/Gb mode or Iu mode
    to S1 mode inter-system change in EMM-IDLE mode and the TIN indicates "P-TMSI"
    */
    if (NAS_EMM_YES == NAS_EMM_IsPtmsiAndIdle() )
    {
        /*填充GPRS ciphering key sequence number IEI*/
        pucReqMsg[ulIndex]              = NAS_EMM_TAU_REQ_GPRS_CK_SN;

        /* 填充 GPRS ciphering key sequence number的 spare */
        pucReqMsg[ulIndex]              &= NAS_EMM_TAU_REQ_IE_SPARE;

        /* 填充GPRS ciphering key sequence number的key sequence */
        pucReqMsg[ulIndex]              |= ucGprsCkSn;

        ulIndex ++;
        *pulIeLength                = ulIndex;

    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_EncodeNonceUe
 Description     : Nonce UE编码函数
 Input           : None
 Output          : pMsg-------------Nonce UE内容
                   pulIeLength------Nonce UE长度
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2011-5-9  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_EncodeNonceUE
(
    VOS_UINT8       *pMsg,
    VOS_UINT32      *pulIeLength
)
{

    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;

    if((VOS_NULL_PTR == pMsg) ||
        (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_EncodeNonceUE: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeNonceUE_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;


    /*
    8.2.29.6    NonceUE
    This IE is included if the UE performs an A/Gb mode or Iu mode to S1 mode
    inter-system change in idle mode.
    */
    if (NAS_EMM_YES == NAS_EMM_IsPtmsiAndIdle() )
    {

        /*填充NONCE UE IEI*/
        pucReqMsg[ulIndex++]                = NAS_EMM_TAU_REQ_Nonce_UE_IEI;

        /* 填充 NONCE UE的 VALUE */
        NAS_LMM_MEM_CPY_S(                  &pucReqMsg[ulIndex],
                                            NAS_EMM_SECU_NONCE_UE_LEN,
                                            NAS_EMM_SecuGetNonceUE(),
                                            sizeof(VOS_UINT32));

        ulIndex                             += sizeof(VOS_UINT32);

        *pulIeLength                        = ulIndex;
    }

    return;

}

/*****************************************************************************
 Function Name   : NAS_EMM_EncodeURCUpdateNeed
 Description     : UE radio capability information update needed编码函数
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-5-12  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_EncodeURCUpdateNeed
(
    VOS_UINT8       *pMsg,
    VOS_UINT32      *pulIeLength
)
{

    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;

    if((VOS_NULL_PTR == pMsg) ||
        (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_EncodeURCUpdateNeed: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeURCUpdateNeed_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;


    /* 如果发起TAU时UE的GU无线能力改变标识仍存在，则应填充URC_UPDATE_NEED
       用于UE无线能力上报，提醒MME对UE能力进行重新查询 */
    if(NAS_LMM_UE_RADIO_CAP_GU_CHG == NAS_LMM_GetEmmInfoUeRadioCapChgFlag())
    {
        NAS_LMM_SetEmmInfoFirstTauFlag(NAS_EMM_FIRST_TAU);
    }


    /*if (MMC_LMM_TIN_P_TMSI == NAS_EMM_GetTinType())*/
    if (NAS_EMM_FIRST_TAU == NAS_LMM_GetEmmInfoFirstTauFlag())
    {
        /*填充UE radio capability information update needed IEI*/
        pucReqMsg[ulIndex]            = NAS_EMM_TAU_REQ_RADIO_CAP_UPDATE_NEED_IEI;

        /* 填充 UE radio capability information update needed IEI的spare*/
        pucReqMsg[ulIndex]              &= NAS_EMM_TAU_REQ_IE_SPARE;

        /* 填充UE radio capability information update needed IEI的update needed */
        pucReqMsg[ulIndex]              |= NAS_EMM_URC_UPDATE_NEED;

        ulIndex ++;

        *pulIeLength                        = ulIndex;

    }

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_EncodeEpsBearStatus
 Description     : EPS BEARER STATUS编码函数
 Input           : None
 Output          : pMsg ------EPS BEARER STATUS内容
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2012-3-1  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_EncodeEpsBearStatus
(
    VOS_UINT8       *pMsg,
    VOS_UINT32      *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    VOS_UINT32                          i;
    NAS_MML_PS_BEARER_CONTEXT_STRU      *pstEpsBearerCxt;
    VOS_UINT32                          ucEpsId;
    VOS_UINT8                           ucEsmEPS1           = 0;
    VOS_UINT8                           ucEsmEPS2           = 0;

    if((VOS_NULL_PTR == pMsg) ||
        (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_EncodeEpsBearStatus: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeEpsBearStatus_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;
    pstEpsBearerCxt = NAS_EMM_GetPsBearerCtx();
    pucReqMsg[ulIndex++]          = NAS_EMM_TAU_REQ_EPS_STATUS_IEI;
    pucReqMsg[ulIndex++]          = NAS_EMM_CN_EPS_CONTEXT_LEN;

    /*lint -e701*/
    for(i = 0; i < EMM_ESM_MAX_EPS_BEARER_NUM; i++)
    {
        if (NAS_MML_PS_BEARER_STATE_ACTIVE == pstEpsBearerCxt[i].enPsBearerState)
        {
            ucEpsId = i + NAS_EMM_MIN_EPS_ID;
            if( NAS_EMM_EPS_BEARER_STATUS_NUM_SEVEN < ucEpsId)
            {
                ucEpsId             = ucEpsId - NAS_EMM_EPS_BEARER_STATUS_NUM_EIGNT;
                ucEsmEPS2 = ucEsmEPS2 | NAS_EMM_TAU_ESM_BEARER_LEFT_N(ucEpsId);
            }
            else
            {
                ucEsmEPS1 = ucEsmEPS1 | NAS_EMM_TAU_ESM_BEARER_LEFT_N(ucEpsId);
            }

        }
    }
    /*lint +e701*/

    pucReqMsg[ulIndex++]                = ucEsmEPS1;
    pucReqMsg[ulIndex++]                = ucEsmEPS2;
    *pulIeLength                        = ulIndex;


    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_SndOmLogActiveFlagInfo
 Description     : 触发TAU REQ消息中携带ACTIVE标识的条件上报
 Input           :
 Output          : None
 Return          : None

 History         :
    1.wangchen 00209181 2015-07-28  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SndOmLogActiveFlagInfo
(
    VOS_VOID
)
{
    NAS_LMM_OM_LOG_ACTIVE_FLAG_INFO_STRU      *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LMM_OM_LOG_ACTIVE_FLAG_INFO_STRU*)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_LOG_ACTIVE_FLAG_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_LMM_MEM_SET_S(  pstMsg,
                        sizeof(NAS_LMM_OM_LOG_ACTIVE_FLAG_INFO_STRU),
                        0,
                        sizeof(NAS_LMM_OM_LOG_ACTIVE_FLAG_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LMM_OM_LOG_ACTIVE_FLAG_INFO_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName       = ID_NAS_LMM_OM_LOG_ACTIVE_FLAG_INFO;

    pstMsg->enEmmCollisionCtrl          = NAS_EMM_TAU_GetEmmCollisionCtrl();

    if (NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ == NAS_EMM_TAU_GetEmmTAUStartCause())
    {
        pstMsg->ucEsmEmcPdnReq              = VOS_TRUE;
    }

    pstMsg->ucCsAttachAllowFlag         = NAS_EMM_GetCsAttachAllowFlg();
    pstMsg->enTmoActiveFlag             = NAS_EMM_TAU_GetEmmTmoActiveFlagCtrl();
    #if (FEATURE_ON == FEATURE_IMS)
    /* 接口名修改 */
    pstMsg->ucImsProcedureOngoing       = (VOS_UINT8)IMSA_IsExitImsService();
    #endif
    if (EMM_ESM_UP_SINGNAL_PENDING == NAS_ESM_IsUpSingnalPending())
    {
        pstMsg->ucUpSignalPendingFlag   = VOS_TRUE;
    }

    if (EMM_ERABM_UP_DATA_PENDING == NAS_ERABM_IsDataPending())
    {
        pstMsg->ucDataPendingFlag       = VOS_TRUE;
    }
    pstMsg->enPtmsiActiveFlag           = NAS_EMM_TAU_GetEmmPtmsiActiveFlagCtrl();

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_LMM_MEM_FREE(pstMsg);
    return;
}

/*******************************************************************************
  Module   :
  Function : Nas_Emm_TAU_SendMrrcDataReq_TAUReq
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190  2008.09.17  新规作成
    2.  X00148705         2009.09.19  修改DRX Length:4-->3(byte)
    3.  z00148421         2009.07.21  CR187:只有SER过程中触发的TAU,携带'active'
    4.  zhuyiqiang 00138739    2009-08-11  MODIFY    BJ9D01672,上行编码优化
    5.  lihong 00150010   2012-12-13  Modify:Emergency

*******************************************************************************/
VOS_VOID    NAS_EMM_TAU_SendMrrcDataReq_TAUReq(NAS_EMM_MSG_TYPE_ENUM_UINT32 ulEmmMsgType)
{
    NAS_EMM_MRRC_DATA_REQ_STRU          *pMrrcDataReqMsg    = NAS_EMM_NULL_PTR;
    VOS_UINT32                          uldataReqMsgLenNoHeader;
    VOS_UINT32                          ulIndex             =0;


    /* 打印进入该函数， INFO_LEVEL */
    if(NAS_EMM_MSG_LOAD_BALANCING_TAU == ulEmmMsgType)
    {
        NAS_EMM_TAU_LOG_NORM( "NAS_EMM_TAU_SendMrrcDataReq_TAUReq is entered,TAUType:NAS_EMM_MSG_LOAD_BALANCING_TAU");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_SendMrrcDataReq_TAUReq_ENUM,LNAS_FUNCTION_LABEL1);
    }
    else
    {
        NAS_EMM_TAU_LOG_NORM( "NAS_EMM_TAU_SendMrrcDataReq_TAUReq is entered,TAUType:NAS_EMM_MSG_NOT_LOAD_BALANCING_TAU");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_SendMrrcDataReq_TAUReq_ENUM,LNAS_FUNCTION_LABEL2);
    }

    /* 计算NAS_MSG_STRU消息长度 */


    /* 以最短消息长度申请DOPRA消息 */
    pMrrcDataReqMsg = (VOS_VOID *)NAS_LMM_MEM_ALLOC( NAS_EMM_INTRA_MSG_MAX_SIZE);
    if(NAS_EMM_NULL_PTR == pMrrcDataReqMsg)
    {
        return;
    }
    /* 如果存在上行Pending或者存在COLLISION标志，则携带'ACTIVE'标志*/
    if((NAS_EMM_UPLINK_PENDING == NAS_EMM_TAU_GetEmmUplinkPending())
     || (NAS_EMM_COLLISION_NONE != NAS_EMM_TAU_GetEmmCollisionCtrl())
     || (NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ == NAS_EMM_TAU_GetEmmTAUStartCause())
     || (NAS_EMM_TMO_ACTIVE_FLAG_CTRL_VALID == NAS_EMM_TAU_GetEmmTmoActiveFlagCtrl())
     || (NAS_EMM_PTMSI_ACTIVE_FLAG_CTRL_VALID == NAS_EMM_TAU_GetEmmPtmsiActiveFlagCtrl()))

    {
        NAS_EMM_TAU_SaveEmmTauReqActiveCtrl(NAS_EMM_TAU_WITH_BEARER_EST_REQ);

        NAS_EMM_SndOmLogActiveFlagInfo();
    }
    else
    {
        NAS_EMM_TAU_SaveEmmTauReqActiveCtrl(NAS_EMM_TAU_NO_BEARER_EST_REQ);
    }

    /* 构造MRRC_DATA_REQ 中的 NAS_MSG_STRU,即CN消息(Compose the msg of): TAU_REQ */
    NAS_EMM_TAU_CompCnTAUReqNasMsg(pMrrcDataReqMsg->stNasMsg.aucNasMsg,&ulIndex);

    NAS_EMM_TAU_SaveEmmTauImsiDetachFlag(NAS_EMM_IMSI_DETACH_INVALID);

    uldataReqMsgLenNoHeader              = EMM_COUNT_DATA_REQ_LEN(ulIndex);

    if ( NAS_EMM_INTRA_MSG_MAX_SIZE < uldataReqMsgLenNoHeader )
    {
        /* 打印错误信息 */
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_TAU_CompCnTAUReqNasMsg, Size error ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_SendMrrcDataReq_TAUReq_ENUM,LNAS_ERROR);

        NAS_LMM_MEM_FREE(pMrrcDataReqMsg);
        return ;
    }

    /* 填写MRRC_DATA_REQ 的DOPRA消息头 */
    EMM_COMP_MM_MSG_HEADER(pMrrcDataReqMsg, uldataReqMsgLenNoHeader);

    /* 填写MRRC_DATA_REQ 的消息ID标识 */
    pMrrcDataReqMsg->ulMsgId                 = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;

    /*填充 TAU_REQ_EST_CAUSE*/
    /*填充 TAU_REQ_EST_CAUSE*/
    if ((NAS_LMM_REG_STATUS_EMC_REGED == NAS_LMM_GetEmmInfoRegStatus())
        || (NAS_LMM_REG_STATUS_NORM_REGED_AND_EMC_BEAR == NAS_LMM_GetEmmInfoRegStatus())
        || (NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ == NAS_EMM_TAU_GetEmmTAUStartCause()))
    {
        pMrrcDataReqMsg->enEstCaue = LRRC_LNAS_EST_CAUSE_EMERGENCY_CALL;
        pMrrcDataReqMsg->enCallType= LRRC_LNAS_CALL_TYPE_EMERGENCY_CALL;
    }
    else
    {
        pMrrcDataReqMsg->enEstCaue = LRRC_LNAS_EST_CAUSE_MO_SIGNALLING;
        pMrrcDataReqMsg->enCallType= LRRC_LNAS_CALL_TYPE_ORIGINATING_SIGNALLING;
    }
    pMrrcDataReqMsg->enEmmMsgType = ulEmmMsgType;

    pMrrcDataReqMsg->enDataCnf               = LRRC_LMM_DATA_CNF_NEED;

    /* 填写MRRC_DATA_REQ 的NAS消息长度标识 */
    pMrrcDataReqMsg->stNasMsg.ulNasMsgSize   = ulIndex;

    /*设置TAU触发时的连接状态*/
    NAS_EMM_TAU_SaveEmmTauStartConnSta(NAS_EMM_GetConnState());

    /* 如果是联合TAU，则通知MM进入MM LOCATION UPDATING PENDING状态 */
    if ((NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_UPDATING == NAS_EMM_TAU_GetTAUtype())
        || (NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI == NAS_EMM_TAU_GetTAUtype()))
    {
        NAS_EMM_SendMmCombinedStartNotifyReq(MM_LMM_COMBINED_TAU);
    }

    /*NAS_EMM_TAU_SaveEmmT3412ExpCtrl(NAS_EMM_NO);*/

    /*空口消息上报TAU REQ*/
    NAS_LMM_SendOmtAirMsg(NAS_EMM_OMT_AIR_MSG_UP, NAS_EMM_TAU_REQ,(NAS_MSG_STRU *)&(pMrrcDataReqMsg->stNasMsg));

    /*关键事件上报TAU REQ*/
    NAS_LMM_SendOmtKeyEvent(         EMM_OMT_KE_TAU_REQ);

    /* 发送消息(Send the msg of) MRRC_DATA_REQ(TAU_REQ) */
    NAS_EMM_SndUplinkNasMsg(             pMrrcDataReqMsg);



    NAS_LMM_MEM_FREE(pMrrcDataReqMsg);

    return;

}

/*******************************************************************************
  Module   :
  Function : NAS_EMM_TAU_SendEsmBearerStatusInd
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190  2008.09.17  新规作成
*******************************************************************************/
VOS_VOID    NAS_EMM_TAU_SendEsmBearerStatusInd(const NAS_EMM_CN_TAU_ACP_STRU   *pMsgStru )
{
    EMM_ESM_BEARER_STATUS_IND_STRU       *psmbearerstatusind  =  NAS_EMM_NULL_PTR;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO( "NAS_EMM_TAU_SendEsmBearerStatusInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_SendEsmBearerStatusInd_ENUM,LNAS_ENTRY);

    /* 申请DOPRA消息 */
    psmbearerstatusind = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(EMM_ESM_BEARER_STATUS_IND_STRU));

    if(NAS_EMM_NULL_PTR == psmbearerstatusind)
    {
        return;
    }

    /* 填写DOPRA消息头 */
    EMM_COMP_ESM_MSG_HEADER(psmbearerstatusind, sizeof(EMM_ESM_BEARER_STATUS_IND_STRU) -
                                        EMM_LEN_VOS_MSG_HEADER);

    /* 填写消息ID标识 */
    psmbearerstatusind->ulMsgId    = ID_EMM_ESM_BEARER_STATUS_IND;

    /* 填写当前已激活的EPSID个数  */
    psmbearerstatusind->ulEpsIdNum = pMsgStru->stEPSBearerstatus.ulEpsIdNum;

    /* 填写 存贮已激活的EPS BID  */
    NAS_LMM_MEM_CPY_S(                  &(psmbearerstatusind->aulEsmEpsId[0]),
                                        EMM_ESM_MAX_EPS_BEARER_NUM*sizeof(VOS_UINT32),
                                        &(pMsgStru->stEPSBearerstatus.aulEsmEpsId[0]),
                                        EMM_ESM_MAX_EPS_BEARER_NUM*sizeof(VOS_UINT32));


    /* 发送消息*/
    NAS_LMM_SEND_MSG(psmbearerstatusind);

    return;


}


VOS_VOID    NAS_EMM_TAU_SendDetachReq()
{
    NAS_LMM_INTRA_DETACH_REQ_STRU             *pIntraDetachReqMsg = NAS_EMM_NULL_PTR;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_SendDetachReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_SendDetachReq_ENUM,LNAS_ENTRY);

    /* 申请DOPRA消息 */
    pIntraDetachReqMsg = (VOS_VOID *)NAS_EMM_TAUSER_GetSendIntraMsgBuffAddr(
                                        sizeof(NAS_LMM_INTRA_DETACH_REQ_STRU) -
                                        EMM_LEN_VOS_MSG_HEADER);

    if(NAS_EMM_NULL_PTR == pIntraDetachReqMsg)
    {
        NAS_EMM_TAU_LOG_ERR( "Nas_Emm_Sau_SendAttachReq: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_TAU_SendDetachReq_ENUM,LNAS_NULL_PTR);
        return;
    }

    /* 填写NAS_EMM_INTRA_DETACH_REQ 的DOPRA消息头 */
    EMM_COMP_MM_MSG_HEADER(pIntraDetachReqMsg, sizeof(NAS_LMM_INTRA_DETACH_REQ_STRU) -
                                        EMM_LEN_VOS_MSG_HEADER);

    /* 填写NAS_EMM_INTRA_DETACH_REQ 的消息ID标识 */
    pIntraDetachReqMsg->ulMsgId                 = ID_NAS_LMM_INTRA_DETACH_REQ;

    /* 发送消息(Send the msg of) NAS_EMM_INTRA_DETACH_REQ */
/*    NAS_EMM_TAUSER_SendIntraMsg(pIntraDetachReqMsg);*/
    NAS_EMM_SEND_INTRA_MSG(             pIntraDetachReqMsg);

    return;
}



/*****************************************************************************
 Function Name   : Nas_Emm_TAU_CompCnTAUCmpl
 Description     :
 Input           :
 Output          :
 Return          :

 History         :
    1.zhouyan 00125190       2008-09-08  Draft Enact
    2.zhuyiqiang 00138739    2009-08-11  MODIFY    BJ9D01672,上行编码优化

*****************************************************************************/
VOS_VOID    NAS_EMM_TAU_CompCnTAUCmpl(LRRC_LNAS_MSG_STRU  *pNasMsg,
                                                        VOS_UINT32 *pulIndex )
{
    VOS_UINT32                          ulIndex             = 0;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO( "NAS_EMM_TAU_CompCnTAUCmpl is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_CompCnTAUCmpl_ENUM,LNAS_ENTRY);

    /* 清空将填充CN消息的空间 */
    /* NAS_LMM_MEM_SET(pNasMsg->aucNasMsg, 0, pNasMsg->ulNasMsgSize); */

    /* 填充 Skip indicator  +  Protocol Discriminator */
    pNasMsg->aucNasMsg[ulIndex++]       = EMM_CN_MSG_PD_EMM;

    /* 填充 TAU CMPL message identity   */
    pNasMsg->aucNasMsg[ulIndex++]       = NAS_EMM_CN_MT_TAU_CMP;

    *pulIndex = ulIndex;

    return;

}

/*******************************************************************************
  Module   :
  Function : NAS_EMM_TAU_SendMrrcDataReqTauCmpl
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190  2008.09.17  新规作成
    2.  zhuyiqiang 00138739    2009-08-11  MODIFY    BJ9D01672,上行编码优化

*******************************************************************************/
VOS_VOID    NAS_EMM_TAU_SendMrrcDataReqTauCmpl( )
{
    NAS_EMM_MRRC_DATA_REQ_STRU          *pMrrcDataReqMsg    = NAS_EMM_NULL_PTR;
    VOS_UINT32                          uldataReqMsgLenNoHeader;
    VOS_UINT32                          ulIndex             = 0;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_SendMrrcDataReqTauCmpl is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_SendMrrcDataReqTauCmpl_ENUM,LNAS_ENTRY);


    /* 申请消息队列 */

    pMrrcDataReqMsg = (VOS_VOID *)NAS_LMM_MEM_ALLOC( NAS_EMM_INTRA_MSG_MAX_SIZE);
    if(NAS_EMM_NULL_PTR == pMrrcDataReqMsg)
    {
        return;
    }

    NAS_LMM_MEM_SET_S(pMrrcDataReqMsg, NAS_EMM_INTRA_MSG_MAX_SIZE, 0, NAS_EMM_INTRA_MSG_MAX_SIZE);

    /* 构造MRRC_DATA_REQ 中的 NAS_MSG_STRU,即CN消息(Compose the msg of): TAU_REQ */
    NAS_EMM_TAU_CompCnTAUCmpl(            &(pMrrcDataReqMsg->stNasMsg),&ulIndex);

    uldataReqMsgLenNoHeader              = EMM_COUNT_DATA_REQ_LEN(ulIndex);

    if ( NAS_EMM_INTRA_MSG_MAX_SIZE < uldataReqMsgLenNoHeader )
    {
        /* 打印错误信息 */
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_TAU_CompCnTAUCmpl, Size error ");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_TAU_SendMrrcDataReqTauCmpl_ENUM,LNAS_ERROR);
        NAS_LMM_MEM_FREE(pMrrcDataReqMsg);
        return ;
    }

    /* 填写MRRC_DATA_REQ 的DOPRA消息头 */
    EMM_COMP_MM_MSG_HEADER(pMrrcDataReqMsg, uldataReqMsgLenNoHeader);

    /* 填写MRRC_DATA_REQ 的消息ID标识 */
    pMrrcDataReqMsg->ulMsgId            = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;

    /*填充 TAU_COMPL_EST_CAUSE*/
    pMrrcDataReqMsg->enEstCaue          = LRRC_LNAS_EST_CAUSE_MO_SIGNALLING;
    pMrrcDataReqMsg->enCallType         = LRRC_LNAS_CALL_TYPE_ORIGINATING_SIGNALLING;
    pMrrcDataReqMsg->enEmmMsgType       = NAS_EMM_MSG_TAU_CMP;

    pMrrcDataReqMsg->enDataCnf          = LRRC_LMM_DATA_CNF_NEED;

    /* 填写MRRC_DATA_REQ 的NAS消息长度标识 */
    pMrrcDataReqMsg->stNasMsg.ulNasMsgSize   = ulIndex;

    /*空口消息上报TAU COMPLETE*/
    NAS_LMM_SendOmtAirMsg(NAS_EMM_OMT_AIR_MSG_UP, NAS_EMM_TAU_CMP, (NAS_MSG_STRU *)&(pMrrcDataReqMsg->stNasMsg));

    /*关键事件上报TAU COMPLETE*/
    NAS_LMM_SendOmtKeyEvent(         EMM_OMT_KE_TAU_CMP);

    NAS_EMM_SndUplinkNasMsg(             pMrrcDataReqMsg);

    NAS_LMM_MEM_FREE(pMrrcDataReqMsg);
    return;

}




VOS_UINT32    NAS_EMM_TAU_CHKFSMStateMsgp(
                                    NAS_EMM_MAIN_STATE_ENUM_UINT16  stMS,
                                    NAS_EMM_SUB_STATE_ENUM_UINT16   stSS,
                                    VOS_VOID   *pMsgStru)
{
    (VOS_VOID)(pMsgStru);
    if(NAS_EMM_CHK_STAT_INVALID(stMS, stSS))
    {
        NAS_EMM_TAU_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMState: STATE ERR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_TAU_CHKFSMStateMsgp_ENUM,LNAS_ERROR);
        return NAS_EMM_FAIL;
    }
    if ( NAS_EMM_NULL_PTR == pMsgStru )
    {
        /* 打印异常 */
        NAS_EMM_TAU_LOG_WARN( "NAS_EMM_TAUSER_CHKMsgp: pMsgStru is NULL_PTR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_TAU_CHKFSMStateMsgp_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }
    return NAS_EMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_TAU_GetTauStartCause
 Description     : 获取当前TAU触发的原因，以函数的形式提供给TAU之外的其他模
                   块使用
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-10-25  Draft Enact

*****************************************************************************/
NAS_EMM_TAU_START_CAUSE_ENUM_UINT8  NAS_EMM_TAU_GetTauStartCause(
                                        VOS_VOID)
{
    return NAS_EMM_TAU_GetEmmTAUStartCause();
}

/*****************************************************************************
 Function Name   : NAS_EMM_TAU_GetImsiDetachFlag
 Description     : 获取IMSI DETACH FLAG标识

 Input           : None
 Output          : None
 Return          : NAS_EMM_IMSI_DETACH_FLAG_ENUM_UINT8

 History         :
    1.lihong 00150010      2012-03-13  Draft Enact

*****************************************************************************/
NAS_EMM_IMSI_DETACH_FLAG_ENUM_UINT8  NAS_EMM_TAU_GetImsiDetachFlag( VOS_VOID )
{
    return NAS_EMM_TAU_GetEmmTauImsiDetachFlag();
}

/*****************************************************************************
 Function Name   : NAS_EMM_TAU_SetImsiDetachFlag
 Description     : 设置IMSI DETACH FLAG标识

 Input           : None
 Output          : None
 Return          : NAS_EMM_IMSI_DETACH_FLAG_ENUM_UINT8

 History         :
    1.lihong 00150010      2012-03-13  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_TAU_SetImsiDetachFlag
(
    NAS_EMM_IMSI_DETACH_FLAG_ENUM_UINT8 enImsiDetachFlag
)
{
    NAS_EMM_TAU_SaveEmmTauImsiDetachFlag(enImsiDetachFlag);
}

/*****************************************************************************
 Function Name   : NAS_EMM_TAU_IsUplinkPending
 Description     : 调用ESM和RABM提供的API，判断是否存在上行信令或者上行数据
                   阻塞，如果不存在上行信令阻塞，则清空缓存的ESM信令
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-2-15  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_TAU_IsUplinkPending( VOS_VOID )
{
    if((EMM_ESM_UP_SINGNAL_PENDING == NAS_ESM_IsUpSingnalPending())
        ||(EMM_ERABM_UP_DATA_PENDING == NAS_ERABM_IsDataPending())
#if (FEATURE_ON == FEATURE_IMS)
        /* 如果有IMS业务，且当前不是数据连接态时，才设置上行PENDING的标识，
        避免IMS通话过程中，在L内切换时，还将上行pending设置为true */
        /*数据连接态，有IMS业务时，TAU REQ消息中不应该带ACTIVE标识*/
        /* 接口名修改 */
        ||((VOS_TRUE == IMSA_IsExitImsService())
        && (NAS_EMM_CONN_DATA != NAS_EMM_GetConnState()))
#endif
        )
    {
        NAS_EMM_TAU_SetEmmUplinkPending(NAS_EMM_UPLINK_PENDING);
    }
    else
    {
        NAS_EMM_TAU_SetEmmUplinkPending(NAS_EMM_NO_UPLINK_PENDING);
    }

    return;
}

VOS_UINT32 NAS_EMM_TAU_CanTriggerComTauWithIMSI(VOS_VOID)
{
    if((NAS_LMM_REG_DOMAIN_PS == NAS_LMM_GetEmmInfoRegDomain())
        && ( NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI == NAS_EMM_TAU_GetEpsUpdateType(NAS_EMM_TAU_START_CAUSE_OTHERS))
        && (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus()))
    {
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}


VOS_UINT32  NAS_EMM_TAU_RrcRelCauseTriggerTau(VOS_VOID)
{
    NAS_LMM_NETWORK_INFO_STRU           *pMmNetInfo = NAS_EMM_NULL_PTR;

    if(NAS_EMM_TRIGGER_TAU_RRC_REL_LOAD_BALANCE == NAS_LMM_GetEmmInfoTriggerTauRrcRel())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RrcRelCauseTriggerTau:load balance");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_RrcRelCauseTriggerTau_ENUM,LNAS_FUNCTION_LABEL1);
        /*NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_RRC_REL_LOAD_BALANCE);*/
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_LOAD_BALANCE);
        return NAS_EMM_YES;
    }
    else if(NAS_EMM_TRIGGER_TAU_RRC_REL_CONN_FAILURE ==
                                        NAS_LMM_GetEmmInfoTriggerTauRrcRel())
    {
        /* 如果是因CSFB DELAY定时器导致的之前的CSFB没能发起，此时无论需发起TAU还是SERVICE，
        都要先发EXT SERVICE，否则一旦发起SERVICE，后续就不会再发起EXT SERVICE*/
        if((VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
            &&(NAS_EMM_COLLISION_SERVICE == NAS_EMM_TAU_GetEmmCollisionCtrl()))
        {
            /* 设置UE接受CSFB */
            NAS_EMM_SER_SaveEmmSerCsfbRsp(NAS_EMM_CSFB_RSP_ACCEPTED_BY_UE);

            /*启动定时器3417*/
            NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

            /*转换EMM状态机MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
            NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

            /* ESR空口发送前,通知LRRC CSFB流程INIT,LRRC置一个全局变量,当ESR发送时发生重建,直接回LMM REL,搜网去GU */
            NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_INIT);

            /*组合并发送MRRC_DATA_REQ(SERVICE_REQ)*/
            NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq();

            /* 清除之前记录的SERVICE冲突 */
            NAS_EMM_TAU_SaveEmmCollisionCtrl(NAS_EMM_COLLISION_NONE);

            return NAS_EMM_YES;
        }
        else
        {
            /* 不能删除，如果有上行PENDING,则会发起SERVICE */
            NAS_EMM_TAU_IsUplinkPending();

            if(NAS_EMM_UPLINK_PENDING == NAS_EMM_TAU_GetEmmUplinkPending())
            {
                /*存在上行数据pending时,触发SR之前需要给MMC上报TAU结果以使MMC通知CDS切换至LTE模式 */
                pMmNetInfo                          = NAS_LMM_GetEmmInfoNetInfoAddr();
                NAS_EMM_SetLVRTai(&pMmNetInfo->stPresentNetId);
                NAS_EMM_SetTauTypeNoProcedure();
                /* 注册/服务状态上报上移MMC优化：先设置EU值再给MMC回复TAU结果 */
                NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_UPDATED_EU1);
                NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara();
                if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
                {
                    /*保存PS LOC信息*/
                    NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
                }
                NAS_EMM_TAU_LOG_INFO("NAS_EMM_RrcRelCauseTriggerTau:Init Ser.");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_RrcRelCauseTriggerTau_ENUM,LNAS_FUNCTION_LABEL2);
                NAS_EMM_SER_UplinkPending();
            }
            else
            {
                NAS_EMM_TAU_LOG_INFO("NAS_EMM_RrcRelCauseTriggerTau:RRC connection failure");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_RrcRelCauseTriggerTau_ENUM,LNAS_FUNCTION_LABEL3);
                /*NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_RRC_REL_CONN_FAILURE );*/
                NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

                /* 新增入参TAU发起原因 */
                NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_CONN_FAIL);
            }

            return NAS_EMM_YES;
        }
    }
    else
    {

    }

    return NAS_EMM_NO;
}
/*****************************************************************************
 Function Name   : NAS_EMM_RegSomeStateMsgSysInfoT3412ExpProc
 Description     : Reg.Limite_Service
                   Reg.Plmn_Search
                   Reg.No_Cell_Available
                   状态下收到SYS_INFO_IND时处理T3412定时器超时
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010  2011-08-31  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_RegSomeStateMsgSysInfoT3412ExpProc( VOS_VOID )
{
    /* 协议24301 5.3.5章节描述，在REG+NO_AVAILABLE_CELL状态下，T3412超时，如果
       ISR激活，就启动T3423定时器;如果ISR没有激活，如果
       当前是联合注册成功，则回到REG+NORMAL_SERVICE态后，发起联合TAU，TAU类型为
       combined TA/LA updating with IMSI attach；如果不是联合注册成功，则发起周期性TAU
   */
    if (NAS_EMM_T3412_EXP_YES_REG_NO_AVALABLE_CELL ==  NAS_LMM_GetEmmInfoT3412ExpCtrl())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateMsgSysInfoT3412ExpProc:REG+NO_AVAILABE_CELL T3412exp.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateMsgSysInfoT3412ExpProc_ENUM,LNAS_FUNCTION_LABEL1);

        if (NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain())
        {
             /* 将注册域改为PS，是为了回到REG+NORMAL_SERVICE态后，如果要发起联合TAU，则
                TAU类型应该填为combined TA/LA updating with IMSI attach */
            NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
             /*NAS_EMM_TAU_SaveEmmTAUStartCause(     NAS_EMM_TAU_START_CAUSE_SYSINFO);*/
             NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        }
        else
        {
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_T3412EXP);
        }
        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_3412_EXP_HAPPENED);
        return NAS_LMM_MSG_HANDLED;
    }

    /* 协议24301 5.3.5章节描述，如果在非REG+NO_AVAILABLE_CELL状态下，T3412超时，
       则当回到REG+NORMAL_SERVICE态后，应触发 Periodic TAU*/
    if(NAS_EMM_T3412_EXP_YES_OTHER_STATE ==  NAS_LMM_GetEmmInfoT3412ExpCtrl())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateMsgSysInfoT3412ExpProc:Other State T3412exp.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateMsgSysInfoT3412ExpProc_ENUM,LNAS_FUNCTION_LABEL2);
        NAS_EMM_TAU_SaveEmmTAUStartCause( NAS_EMM_TAU_START_CAUSE_T3412EXP);

        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_3412_EXP_HAPPENED);

        return NAS_LMM_MSG_HANDLED;
    }

    return NAS_LMM_MSG_DISCARD;
}



/*****************************************************************************
 Function Name   : NAS_EMM_RegSomeStateStartTAUNeeded
 Description     :   判断是否需要发起TAU，如需要，直接发起
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151  2012-7-10  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_RegSomeStateStartTAUNeeded( VOS_VOID )
{
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateStartTAUNeeded is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartTAUNeeded_ENUM,LNAS_ENTRY);

    /* 如果期间发生过ESM本地修改承载上下文*/
    if(NAS_EMM_EPS_BEARER_STATUS_CHANGEED == NAS_EMM_GetEpsContextStatusChange())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateStartTAUNeeded:Bearer Status Change.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartTAUNeeded_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_BEARER_STATUS_CHANGEED);
        return NAS_EMM_YES;
    }

    /* 如果期间发生过UE_NET_CAP or DRX改变，触发TA-Updating TAU*/
    if(NAS_EMM_YES == NAS_LMM_GetEmmInfoDrxNetCapChange())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateStartTAUNeeded:DrxOrNetCap Change.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartTAUNeeded_ENUM,LNAS_FUNCTION_LABEL2);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_DRX_CHANGEED);
        return NAS_EMM_YES;
    }

    /*对异系统标识进行判断*/
    if(NAS_EMM_YES == NAS_LMM_GetEmmInfoTriggerTauSysChange() )
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateStartTAUNeeded: Sys Change flag");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartTAUNeeded_ENUM,LNAS_FUNCTION_LABEL3);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_INTER_CHANGE);
        return NAS_EMM_YES;
    }

    /* 如果当前注册域为PS，且当前有能力发起CS域的注册，则发起联合TAU */
    if (NAS_EMM_YES == NAS_EMM_TAU_CanTriggerComTauWithIMSI())
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegSomeStateStartTAUNeeded: with imsi attach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartTAUNeeded_ENUM,LNAS_FUNCTION_LABEL4);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_ATTACH_NON_EPS);
        return NAS_EMM_YES;
    }

    /* 判断接入技术变化标识，如果变化 */
    if (NAS_LMM_UE_RADIO_CAP_NOT_CHG != NAS_LMM_GetEmmInfoUeRadioCapChgFlag())
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegSomeStateStartTAUNeeded: UE radio capability is changed !");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartTAUNeeded_ENUM,LNAS_FUNCTION_LABEL5);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_RADIO_CAP_CHANGE);
        return NAS_EMM_YES;
    }

    /*对RRC Rel原因进行判断*/
    if(NAS_EMM_YES == NAS_EMM_TAU_RrcRelCauseTriggerTau())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateStartTAUNeeded:rrc rel cause");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartTAUNeeded_ENUM,LNAS_EMM_REL_CAUSE);
        return NAS_EMM_YES;
    }

    /* e)when the UE enters EMM-REGISTERED.NORMAL-SERVICE and the UE's TIN indicates "P-TMSI"
       主要用于在L模下激活ISR，后续在L模下3412和3423定时器均超时的场景，此场景不能发起周期性TAU */
    if (MMC_LMM_TIN_P_TMSI == NAS_EMM_GetTinType())
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegSomeStateStartTAUNeeded: TIN is P-TMSI !");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartTAUNeeded_ENUM,LNAS_FUNCTION_LABEL6);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_PTMSI);
        return NAS_EMM_YES;
    }

    /* 处理定时器T3412超时 */
    if (NAS_LMM_MSG_HANDLED == NAS_EMM_RegSomeStateMsgSysInfoT3412ExpProc())
    {
        return NAS_EMM_YES;
    }

    /* o)when the UE's usage setting or the voice domain preference for E-UTRAN change in the UE */
    if(NAS_EMM_YES == NAS_EMM_GetVoiceDomainChange() )
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateStartTAUNeeded: VOICE DOMAIN CHANG ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartTAUNeeded_ENUM,LNAS_FUNCTION_LABEL7);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_VOICE_DOMAIN_CHANGE);
        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_VOICE_DOMAIN_CHANGE);
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;

}
/*****************************************************************************
 Function Name   : NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded
 Description     : 异系统回到L判断是否需要发起TAU，如需要，直接发起
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1. leixiantiao 00258641  2015-5-27  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded( VOS_VOID )
{
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded_ENUM,LNAS_ENTRY);

    /* 如果期间发生过ESM本地修改承载上下文*/
    if(NAS_EMM_EPS_BEARER_STATUS_CHANGEED == NAS_EMM_GetEpsContextStatusChange())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded:Bearer Status Change.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded_ENUM,LNAS_FUNCTION_LABEL1);
        /* 异系统TAU调用异系统TAU封装函数 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_BEARER_STATUS_CHANGEED);
        return NAS_EMM_YES;
    }

    /* 如果期间发生过UE_NET_CAP or DRX改变，触发TA-Updating TAU*/
    if(NAS_EMM_YES == NAS_LMM_GetEmmInfoDrxNetCapChange())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded:DrxOrNetCap Change.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded_ENUM,LNAS_FUNCTION_LABEL2);
        /* 异系统TAU调用异系统TAU封装函数 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_DRX_CHANGEED);
        return NAS_EMM_YES;
    }

    /*对异系统标识进行判断*/
    if(NAS_EMM_YES == NAS_LMM_GetEmmInfoTriggerTauSysChange() )
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded: Sys Change flag");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded_ENUM,LNAS_FUNCTION_LABEL3);
        /* 异系统TAU调用异系统TAU封装函数 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_INTER_CHANGE);
        return NAS_EMM_YES;
    }

    /* 如果当前注册域为PS，且当前有能力发起CS域的注册，则发起联合TAU */
    if (NAS_EMM_YES == NAS_EMM_TAU_CanTriggerComTauWithIMSI())
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded: with imsi attach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded_ENUM,LNAS_FUNCTION_LABEL4);
        /* 异系统TAU调用异系统TAU封装函数 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_ATTACH_NON_EPS);
        return NAS_EMM_YES;
    }

    /* 判断接入技术变化标识，如果变化 */
    if (NAS_LMM_UE_RADIO_CAP_NOT_CHG != NAS_LMM_GetEmmInfoUeRadioCapChgFlag())
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded: UE radio capability is changed !");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded_ENUM,LNAS_FUNCTION_LABEL5);
        /* 异系统TAU调用异系统TAU封装函数 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_RADIO_CAP_CHANGE);
        return NAS_EMM_YES;
    }

    /*对RRC Rel原因进行判断*/
    if(NAS_EMM_YES == NAS_EMM_TAU_RrcRelCauseTriggerTau())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded:rrc rel cause");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded_ENUM,LNAS_EMM_REL_CAUSE);
        return NAS_EMM_YES;
    }

    /* e)when the UE enters EMM-REGISTERED.NORMAL-SERVICE and the UE's TIN indicates "P-TMSI"
       主要用于在L模下激活ISR，后续在L模下3412和3423定时器均超时的场景，此场景不能发起周期性TAU */
    if (MMC_LMM_TIN_P_TMSI == NAS_EMM_GetTinType())
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded: TIN is P-TMSI !");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded_ENUM,LNAS_FUNCTION_LABEL6);
        /* 异系统TAU调用异系统TAU封装函数 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_PTMSI);
        return NAS_EMM_YES;
    }

    /* 处理定时器T3412超时 */
    if (NAS_LMM_MSG_HANDLED == NAS_EMM_RegSomeStateMsgSysInfoT3412ExpProc())
    {
        return NAS_EMM_YES;
    }

    /* o)when the UE's usage setting or the voice domain preference for E-UTRAN change in the UE */
    if(NAS_EMM_YES == NAS_EMM_GetVoiceDomainChange() )
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded: VOICE DOMAIN CHANG ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded_ENUM,LNAS_FUNCTION_LABEL7);
        /* 异系统TAU调用异系统TAU封装函数 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_VOICE_DOMAIN_CHANGE, NAS_LMM_OM_TAU_START_TYPE_VOICE_DOMAIN_CHANGE);
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;

}

/*****************************************************************************
 Function Name   : NAS_EMM_RegSomeStateMsgSysInfoTaiNotInTaiList
 Description     : Reg.Limite_Service
                   Reg.Plmn_Search
                   Reg.No_Cell_Available
                   状态下收到SYS_INFO_IND，TAI不在TAI LIST中
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010    2014-01-23  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_RegSomeStateMsgSysInfoTaiNotInTaiList( VOS_VOID )
{
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt = MMC_LMM_TAU_RSLT_BUTT;
    NAS_MM_TA_STRU                     *pstLastAttmpRegTa = NAS_EMM_NULL_PTR;
    NAS_MM_TA_STRU                      stCurTa;
    NAS_LMM_PTL_TI_ENUM_UINT16          enPtlTimerId     = NAS_LMM_PTL_TI_BUTT;

    NAS_LMM_MEM_SET_S(&stCurTa, sizeof(NAS_MM_TA_STRU), 0, sizeof(NAS_MM_TA_STRU));

    NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegSomeStateMsgSysInfoTaiNotInTaiList is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateMsgSysInfoTaiNotInTaiList_ENUM,LNAS_ENTRY);

    /* 获取当前TA和上次尝试注册的TA信息 */
    NAS_EMM_GetCurrentTa(&stCurTa);
    pstLastAttmpRegTa                  = NAS_LMM_GetEmmInfoNetInfoLastAttmpRegTaAddr();

    /* TA没变&&有定时器&&EU值不是EU1，等超时; 否则立即发起TAU*/
    if( (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatch(pstLastAttmpRegTa, &stCurTa))
        && (NAS_EMM_YES == NAS_EMM_IsT3411orT3402Running(&enPtlTimerId))
        && (EMM_US_UPDATED_EU1 != NAS_EMM_TAUSER_GetAuxFsmUpStat()))
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegSomeStateMsgSysInfoTaiNotInTaiList: wait timer expired.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateMsgSysInfoTaiNotInTaiList_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_EMM_TAUSER_FSMTranState( EMM_MS_REG,
                                     EMM_SS_REG_ATTEMPTING_TO_UPDATE,
                                     TI_NAS_EMM_STATE_NO_TIMER);

        /* 有定时器3402在运行, 需上报TAU结果 */
        if ( TI_NAS_EMM_PTL_T3402 == enPtlTimerId )
        {
            NAS_EMM_SetTauTypeNoProcedure();

            ulTauRslt = MMC_LMM_TAU_RSLT_T3402_RUNNING;
            NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);


        }
        return;
    }

    /* 重置TAU计数，启动TAU Procedure */
    NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);
    NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

    /* 新增入参TAU发起原因 */
    NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_NOT_IN_TAI_LIST);
    return;
}
#if(FEATURE_ON == FEATURE_CSG)

VOS_UINT32  NAS_EMM_RegSomeStateMsgSysInfoCsgIdNotInCsgList( VOS_VOID )
{
    NAS_LMM_PTL_TI_ENUM_UINT16          enPtlTimerId     = NAS_LMM_PTL_TI_BUTT;


    NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegSomeStateMsgSysInfoCsgIdNotInCsgList is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateMsgSysInfoCsgIdNotInCsgList_ENUM,LNAS_ENTRY);


    /* CSG ID和上次尝试的CSG ID不同,或没有T3411或T3402 */
    if ((NAS_EMM_NO == NAS_LMM_IsCurCsgIdEqualLastAttmpRegCsgId())
        ||(NAS_EMM_NO == NAS_EMM_IsT3411orT3402Running(&enPtlTimerId)))
    {
        /* 重置TAU计数，启动TAU Procedure */
        NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_NOT_IN_CSG_LIST);
        return NAS_EMM_YES;
    }


    return NAS_EMM_NO;
}
#endif

/*****************************************************************************
 Function Name   : NAS_EMM_RegSomeStateMsgSysInfoCommProc
 Description     : Reg.Limite_Service
                   Reg.Plmn_Search
                   Reg.No_Cell_Available
                   状态下收到SYS_INFO_IND的公共处理部分
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151  2012-7-10  Draft Enact
    2.lihong 00150010    2012-12-18 Modify:Emergency
*****************************************************************************/
VOS_VOID  NAS_EMM_RegSomeStateMsgSysInfoCommProc( VOS_VOID )
{
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt = MMC_LMM_TAU_RSLT_BUTT;
    NAS_MM_NETWORK_ID_STRU             *pstPresentNetInfo = NAS_EMM_NULL_PTR;
    NAS_LMM_PTL_TI_ENUM_UINT16          enPtlTimerId     = NAS_LMM_PTL_TI_BUTT;

    /* 获取当前TA和上次尝试注册的TA信息 */
    pstPresentNetInfo                  = NAS_LMM_GetEmmInfoNetInfoPresentNetAddr();

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateMsgSysInfoCommProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateMsgSysInfoCommProc_ENUM,LNAS_ENTRY);

#if(FEATURE_ON == FEATURE_CSG)
    if((NAS_EMM_YES == NAS_LMM_IsCsgCampOn())
        &&(NAS_EMM_FAIL == NAS_EMM_TAU_IsCsgIdInAllowedOrOperatorCsgList()))
    {
        if(NAS_EMM_YES == NAS_EMM_RegSomeStateMsgSysInfoCsgIdNotInCsgList())
        {
            return;
        }
    }
#endif

    /* 如果当前TA不在TAI LIST */
    if (NAS_EMM_FAIL == NAS_EMM_TAU_IsCurrentTAInTaList())
    {
        NAS_EMM_RegSomeStateMsgSysInfoTaiNotInTaiList();

        return ;
    }

    /* TA在TAI LIST && EU值不为EU1 */
    if (EMM_US_UPDATED_EU1 != NAS_EMM_TAUSER_GetAuxFsmUpStat())
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegSomeStateMsgSysInfoCommProc: TA is in TAI LIST, not EU1.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateMsgSysInfoCommProc_ENUM,LNAS_FUNCTION_LABEL1);

        /* 上次尝试发起注册或TAU的TA不在TAI LIST，重置计数发起TAU */
        if (NAS_EMM_NO == NAS_LMM_IsLastAttemptRegTaInTaiList())
        {
            NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

            /* 新增入参TAU发起原因 */
            NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_LAST_ATTEMPT_TA_NOT_IN_TAI_LIST);
            return;
        }

        /*有定时器 && 当前TA与上次尝试发起注册的TA等效，等超时*/
        if (NAS_EMM_YES == NAS_EMM_IsT3411orT3402Running(&enPtlTimerId))
        {
            NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegSomeStateMsgSysInfoCommProc: Equivalent TA, wait timer expired.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateMsgSysInfoCommProc_ENUM,LNAS_FUNCTION_LABEL2);
            NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG,
                                        EMM_SS_REG_ATTEMPTING_TO_UPDATE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

            /* 有定时器是3402在运行, 需上报TAU结果 */
            if ( TI_NAS_EMM_PTL_T3402 == enPtlTimerId )
            {
                NAS_EMM_SetTauTypeNoProcedure();

                ulTauRslt = MMC_LMM_TAU_RSLT_T3402_RUNNING;
                NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);

            }
            return;
        }

        /* 没有定时器 && 当前TA与上次尝试发起注册的TA等效，触发TAU但不重置尝试次数 */
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_NOT_EU1);
        return;
    }

    /* TA在TAI LIST && EU值为EU1*/
    /* 如果有定时器，则判断该转入NORMAL SEVICE还是UPDATE MM态，等超时 */
    if ((NAS_EMM_YES == NAS_EMM_IsT3411orT3402Running(&enPtlTimerId))
        && (VOS_TRUE != NAS_EMM_IsEnterRegLimitService()))
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegSomeStateMsgSysInfoCommProc: Check enter Nor-service or Upt-MM state.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateMsgSysInfoCommProc_ENUM,LNAS_FUNCTION_LABEL3);

        if (NAS_EMM_YES == NAS_EMM_TAU_CanTriggerComTauWithIMSI())
        {
            /* 将状态转移至MS_REG + EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM状态 */
            NAS_EMM_TAUSER_FSMTranState(   EMM_MS_REG,
                                           EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM,
                                           TI_NAS_EMM_STATE_NO_TIMER);

            /* 有定时器是3402在运行, 需上报TAU结果 */
            if (TI_NAS_EMM_PTL_T3402 == enPtlTimerId)
            {
                NAS_EMM_SetTauTypeNoProcedure();

                ulTauRslt = MMC_LMM_TAU_RSLT_T3402_RUNNING_EPS_ONLY_SUCC;
                NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);
                return;
            }
        }
        else
        {
            /* 将状态转移至MS_REG + SS_REG_NORMAL_SERVICE状态 */
            NAS_EMM_TAUSER_FSMTranState(   EMM_MS_REG,
                                           EMM_SS_REG_NORMAL_SERVICE,
                                           TI_NAS_EMM_STATE_NO_TIMER);
        }

        NAS_EMM_SetTauTypeNoProcedure();

        /*向MMC发送LMM_MMC_TAU_RESULT_IND消息*/
        NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara();

        return ;
    }

    /* TA在TAI LIST && EU值为EU1*/
    /* 如果没有定时器 */
    /* 如果满足发起TAU的条件，直接发起，否则转NORMAL SERVICE */
    if (NAS_EMM_NO == NAS_EMM_RegSomeStateStartTAUNeeded())
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegSomeStateMsgSysInfoCommProc: TAU not needed, return Nor-service.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateMsgSysInfoCommProc_ENUM,LNAS_FUNCTION_LABEL4);

        /* TA在TAI List中，更新 L.V.R TAI*/
        NAS_EMM_SetLVRTai(pstPresentNetInfo);
        if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
        {
            /*保存PS LOC信息*/
            NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
        }

        NAS_EMM_TranStateRegNormalServiceOrRegLimitService();

        /* 转换EMM状态机MS_REG+SS_NORMAL_SEARVICE*/
        /*NAS_EMM_TAUSER_FSMTranState(    EMM_MS_REG,
                                        EMM_SS_REG_NORMAL_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);*/
        NAS_EMM_SetTauTypeNoProcedure();

        /*向MMC发送LMM_MMC_TAU_RESULT_IND消息*/
        NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara();
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_RegStateMmcOriResumeSysInfoWaitTimerExp3411or3402Running
 Description     : 收到系统消息时识别出要等待T3402超时的情况
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010    2014-01-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_RegStateMmcOriResumeSysInfoWaitTimerExp3411or3402Running
(
    NAS_LMM_PTL_TI_ENUM_UINT16          enPtlTimerId
)
{
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt;

    NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegStateMmcOriResumeSysInfoRecogniseWaitTimerExp: Check enter Nor-service or Upt-MM state.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_RegStateMmcOriResumeSysInfoWaitTimerExp3411or3402Running_ENUM,LNAS_FUNCTION_LABEL1);

    if (MMC_LMM_TIN_P_TMSI == NAS_EMM_GetTinType())
    {
        NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);

        if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
        {
            /*保存PS LOC信息*/
            NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
        }

        /* 将状态转移至MS_REG + EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM状态 */
        NAS_EMM_TAUSER_FSMTranState(   EMM_MS_REG,
                                       EMM_SS_REG_ATTEMPTING_TO_UPDATE,
                                       TI_NAS_EMM_STATE_NO_TIMER);
    }
    else
    {
        if (VOS_TRUE == NAS_EMM_IsEnterRegLimitService())
        {
            return NAS_EMM_FAIL;
        }
        if (NAS_EMM_YES == NAS_EMM_TAU_CanTriggerComTauWithIMSI())
        {
            /* 将状态转移至MS_REG + EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM状态 */
            NAS_EMM_TAUSER_FSMTranState(   EMM_MS_REG,
                                           EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM,
                                           TI_NAS_EMM_STATE_NO_TIMER);

            /* 有定时器是3402在运行, 需上报TAU结果 */
            if (TI_NAS_EMM_PTL_T3402 == enPtlTimerId)
            {
                TLPS_PRINT2LAYER_INFO(NAS_EMM_RegStateMmcOriResumeSysInfoWaitTimerExp3411or3402Running_ENUM,LNAS_FUNCTION_LABEL2);

                NAS_EMM_SetTauTypeNoProcedure();

                ulTauRslt = MMC_LMM_TAU_RSLT_T3402_RUNNING_EPS_ONLY_SUCC;
                NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);
                return NAS_EMM_SUCC;
            }
        }
        else
        {
            /* 将状态转移至MS_REG + SS_REG_NORMAL_SERVICE状态 */
            NAS_EMM_TAUSER_FSMTranState(   EMM_MS_REG,
                                           EMM_SS_REG_NORMAL_SERVICE,
                                           TI_NAS_EMM_STATE_NO_TIMER);
        }
    }

    NAS_EMM_SetTauTypeNoProcedure();

    /*向MMC发送LMM_MMC_TAU_RESULT_IND消息*/
    NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara();

    return NAS_EMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_RegStateMmcOriResumeSysInfoRecogniseWaitTimerExp
 Description     : 收到系统消息时识别出要等待T3402超时的情况
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen          2012-10-31  Draft Enact
    2.lihong00150010    2012-12-18  Modify:Emergency
*****************************************************************************/
VOS_UINT32  NAS_EMM_RegStateMmcOriResumeSysInfoRecogniseWaitTimerExp( VOS_VOID )
{
    NAS_MM_TA_STRU                     *pstLastAttmpRegTa = NAS_EMM_NULL_PTR;
    NAS_MM_TA_STRU                      stCurTa;
    NAS_LMM_PTL_TI_ENUM_UINT16          enPtlTimerId     = NAS_LMM_PTL_TI_BUTT;
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt = MMC_LMM_TAU_RSLT_BUTT;

    NAS_LMM_MEM_SET_S(&stCurTa, sizeof(NAS_MM_TA_STRU), 0, sizeof(NAS_MM_TA_STRU));

    /* 获取当前TA和上次尝试注册的TA信息 */
    NAS_EMM_GetCurrentTa(&stCurTa);
    pstLastAttmpRegTa                  = NAS_LMM_GetEmmInfoNetInfoLastAttmpRegTaAddr();

    if (NAS_RELEASE_R11)
    {
        NAS_EMM_IsG2LGmmSuspendAndIsrAct();
    }
#if(FEATURE_ON == FEATURE_CSG)
    if(NAS_EMM_YES ==NAS_EMM_RegStateMmcOriResumeSysInfoIsCsgIdNotInListTauNeed())
    {
        return NAS_EMM_FAIL;
    }
#endif

    /* 如果当前TA不在TAI LIST */
    if (NAS_EMM_FAIL == NAS_EMM_TAU_IsCurrentTAInTaList())
    {
        /* TA没变&&有定时器&&EU值不是EU1，等超时; 否则立即发起TAU*/
        if( (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatch(pstLastAttmpRegTa, &stCurTa))
            && (NAS_EMM_YES == NAS_EMM_IsT3411orT3402Running(&enPtlTimerId))
            && (EMM_US_UPDATED_EU1 != NAS_EMM_TAUSER_GetAuxFsmUpStat()))
        {
            NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegStateMmcOriResumeSysInfoRecogniseWaitTimerExp: TA is not in TAI LIST, wait timer expired.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_RegStateMmcOriResumeSysInfoRecogniseWaitTimerExp_ENUM,LNAS_FUNCTION_LABEL1);
            NAS_EMM_TAUSER_FSMTranState( EMM_MS_REG,
                                         EMM_SS_REG_ATTEMPTING_TO_UPDATE,
                                         TI_NAS_EMM_STATE_NO_TIMER);

            /* 有定时器3402在运行, 需上报TAU结果 */
            if ( TI_NAS_EMM_PTL_T3402 == enPtlTimerId )
            {
                NAS_EMM_SetTauTypeNoProcedure();

                ulTauRslt = MMC_LMM_TAU_RSLT_T3402_RUNNING;
                NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);


            }
            return NAS_EMM_SUCC;
        }
        return NAS_EMM_FAIL;

    }

    if (EMM_US_UPDATED_EU1 != NAS_EMM_TAUSER_GetAuxFsmUpStat())
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegStateMmcOriResumeSysInfoRecogniseWaitTimerExp: TA is in TAI LIST, not EU1.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegStateMmcOriResumeSysInfoRecogniseWaitTimerExp_ENUM,LNAS_FUNCTION_LABEL2);

        /*有定时器 && 当前TA与上次尝试发起注册的TA等效，等超时*/
        if ((NAS_EMM_YES == NAS_LMM_IsLastAttemptRegTaInTaiList())
            && (NAS_EMM_YES == NAS_EMM_IsT3411orT3402Running(&enPtlTimerId)))
        {
                NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegStateMmcOriResumeSysInfoRecogniseWaitTimerExp: Equivalent TA, wait timer expired.");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_RegStateMmcOriResumeSysInfoRecogniseWaitTimerExp_ENUM,LNAS_FUNCTION_LABEL3);
                NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG,
                                            EMM_SS_REG_ATTEMPTING_TO_UPDATE,
                                            TI_NAS_EMM_STATE_NO_TIMER);

            /* 有定时器3402在运行, 需上报TAU结果 */
            if ( TI_NAS_EMM_PTL_T3402 == enPtlTimerId )
            {
                NAS_EMM_SetTauTypeNoProcedure();

                ulTauRslt = MMC_LMM_TAU_RSLT_T3402_RUNNING;
                NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);

            }
            return NAS_EMM_SUCC;
        }
        return NAS_EMM_FAIL;
    }
    /* TA在TAI LIST && EU值为EU1*/

    /* 如果有定时器，则判断该转入NORMAL SEVICE还是UPDATE MM态，等超时 */
    if (NAS_EMM_YES == NAS_EMM_IsT3411orT3402Running(&enPtlTimerId))
    {
        return NAS_EMM_RegStateMmcOriResumeSysInfoWaitTimerExp3411or3402Running(enPtlTimerId);
    }

    return NAS_EMM_FAIL;
}
/* leixiantiao 00258641 重构函数降低圈复杂度 2014-7-30 begin */
/*****************************************************************************
 Function Name   : NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc
 Description     : 注册态下收到系统消息,不需要等T3411或者T3402超时的且TIN类型为
                    P-TMSI的公共处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641     2014-7-30  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_RegStateMmcOriResumeSysInfoWithTmsiProc(VOS_VOID)
{
    if ((NAS_EMM_T3412_EXP_YES_REG_NO_AVALABLE_CELL == NAS_LMM_GetEmmInfoT3412ExpCtrl())
        && (NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain()))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc:combined succ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegStateMmcOriResumeSysInfoWithTmsiProc_ENUM,LNAS_FUNCTION_LABEL1);

        /* 将注册域改为PS，是为了回到REG+NORMAL_SERVICE态后，如果要发起联合TAU，则
            TAU类型应该填为combined TA/LA updating with IMSI attach */
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

    }
    /*NAS_EMM_TAU_SaveEmmTAUStartCause(     NAS_EMM_TAU_START_CAUSE_SYSINFO);*/
    /* 异系统TAU调用异系统TAU封装函数 */
    NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_PTMSI);
    return;
}
/* leixiantiao 00258641 重构函数降低圈复杂度 2014-7-30 end */
/*****************************************************************************
 Function Name   : NAS_EMM_RegStateMmcOriResumeSysInfoWithNotEu1Proc
 Description     : 注册态下收到系统消息,不需要等T3411或者T3402超时的且EU值不为EUI的公共处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen 00209181 2014-09-26  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_RegStateMmcOriResumeSysInfoWithNotEu1Proc(VOS_VOID)
{
    NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc: TA is in TAI LIST, not EU1.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_RegStateMmcOriResumeSysInfoWithNotEu1Proc_ENUM,LNAS_FUNCTION_LABEL1);

    /* 上次尝试发起注册或TAU的TA不在TAI LIST，重置计数发起TAU */
    if (NAS_EMM_NO == NAS_LMM_IsLastAttemptRegTaInTaiList())
    {
        NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);
        /* 大数据: 异系统TAU调用异系统TAU封装函数 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_NOT_EU1);
        return;
    }

    /* 没有定时器 && 当前TA与上次尝试发起注册的TA等效，触发TAU但不重置尝试次数 */
    /* 大数据: 异系统TAU调用异系统TAU封装函数 */
    NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_NOT_EU1);
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc
 Description     : 注册态下收到系统消息,不需要等T3411或者T3402超时的公共处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen          2012-10-31  Draft Enact
    2.lihong00150010    2012-12-18  Modify:Emergency
*****************************************************************************/
VOS_VOID  NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc( VOS_VOID )
{
    NAS_MM_NETWORK_ID_STRU             *pstPresentNetInfo = NAS_EMM_NULL_PTR;
    GMM_LMM_GPRS_MM_STATE_ENUM_UINT32   enGprsMmState   = GMM_LMM_GPRS_MM_STATE_BUTT;
    MMC_LMM_TIN_TYPE_ENUM_UINT32        ulTinType;
    ulTinType = NAS_EMM_GetTinType();
    pstPresentNetInfo                 = NAS_LMM_GetEmmInfoNetInfoPresentNetAddr();
    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc is entered.");

    if (NAS_EMM_YES == NAS_EMM_IsPtmsiTauActiveFlagSatified())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc: PTMSI, save active flag ctrl.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc_ENUM, LNAS_EMM_PTMSI_SET_ACT_FLAG);
        NAS_EMM_TAU_SaveEmmPtmsiActiveFlagCtrl(NAS_EMM_PTMSI_ACTIVE_FLAG_CTRL_VALID);
    }

    /*c)when the UE enters EMM-REGISTERED.NORMAL-SERVICE and the UE's TIN indicates "P-TMSI"*/
    if (MMC_LMM_TIN_P_TMSI == ulTinType)
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc:TIN is p-tmsi");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc_ENUM,LNAS_FUNCTION_LABEL1);

        /* leixiantiao 00258641 降低圈复杂度 2014-7-30 begin */
        NAS_EMM_RegStateMmcOriResumeSysInfoWithTmsiProc();
        /* leixiantiao 00258641 降低圈复杂度 2014-7-30 end */
        return;
    }

    /* d)when the UE performs an intersystem change from A/Gb or Iu mode to S1 mode,
     and the UE previously either performed a location area update procedure
     or a combined routing area update procedure in A/Gb or Iu mode,
     in order to re-establish the SGs association. In this case the EPS update
     type IE shall be set to "combined TA/LA updating with IMSI attach"; */
    if (NAS_EMM_YES == NAS_EMM_IsLauOrComRauOrSrvccHappenedWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc:FIRST TAU");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc_ENUM,LNAS_FUNCTION_LABEL2);

        /*发起TAU流程*/
        /*NAS_EMM_TAU_SaveEmmTAUStartCause(     NAS_EMM_TAU_START_CAUSE_SYSINFO);*/
        /* 大数据: 异系统TAU调用异系统TAU封装函数 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_LAU_COMRAU);

        return;
    }

    if (NAS_EMM_YES == NAS_EMM_IsEmcCsfbHappenedAndLaiChangWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc:EMC CSFB,LAI CHANG ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc_ENUM,LNAS_EMM_EMC_CSFB_LAI_CHG);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    /* 获取G模连接状态 */
    enGprsMmState = NAS_LMM_GetEmmInfoGConnState();

    /* l)when the UE reselects an E-UTRAN cell while it was in GPRS READY state or PMM-CONNECTED mode; */
    /* For case l, if the TIN indicates "RAT-related TMSI", the UE shall set the TIN to "P-TMSI" before
    initiating the tracking area updating procedure.*/
    if (GMM_LMM_GPRS_MM_STATE_READY  == enGprsMmState)
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc:GPRS READY init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc_ENUM,LNAS_EMM_GPRS_READY_TAU);
        NAS_EMM_SetTinToPtmsiWhenIsrAct();
        /* 大数据: 异系统TAU调用异系统TAU封装函数 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_GPRS_READY_OR_PMM_CONNECT);
        return ;
    }

    /* 触发TAU */
    /* For case c, if the TIN indicates "RAT-related TMSI" and the EPS services were not resumed before
    returning to S1 mode, the UE shall set the TIN to "P-TMSI" before initiating
    the combined tracking area updating procedure*/

    if (NAS_EMM_YES == NAS_EMM_IsG2LAndGmmSuspendWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc:EPS service suspended init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc_ENUM,LNAS_EMM_EPS_SERV_SUSP_TAU);
        NAS_EMM_SetTinToPtmsiWhenIsrAct();
        /* 大数据: 异系统TAU调用异系统TAU封装函数 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_GSM_PS_SUSPEND);
        return ;
    }

    /*q)When the UE performs an intersystem change from A/Gb mode to S1 mode and the TIN indicates "RAT-related TMSI",
    but the UE is required to perform tracking area updating for IMS voice termination as specified in 3GPP TS 24.008 [13],
    annex P.4*/
    if (NAS_EMM_YES == NAS_EMM_RegStateMmcOriResumeSysInfoIsIsrActP4TAUNeed())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegRedirect:ISR act and P.4 init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc_ENUM,LNAS_EMM_ISR_ACT_P4_TAU);
        /* 大数据: 异系统TAU调用异系统TAU封装函数 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_P4);
        return;
    }
#if(FEATURE_ON == FEATURE_CSG)
    if((NAS_EMM_YES == NAS_LMM_IsCsgCampOn())
        &&(NAS_EMM_FAIL == NAS_EMM_TAU_IsCsgIdInAllowedOrOperatorCsgList()))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegRedirect:CSG not in CSG list tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc_ENUM,LNAS_FUNCTION_LABEL3);

        NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);

        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_NOT_IN_CSG_LIST);

        return;
    }
#endif

    /* 如果当前TA不在TAI LIST */
    if (NAS_EMM_FAIL == NAS_EMM_TAU_IsCurrentTAInTaList())
    {
        /* 重置TAU计数，启动TAU Procedure */
        NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);
        /* 大数据: 异系统TAU调用异系统TAU封装函数 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_NOT_IN_TAI_LIST);
        return;

    }

    /* TA在TAI LIST && EU值不为EU1 */
    if (EMM_US_UPDATED_EU1 != NAS_EMM_TAUSER_GetAuxFsmUpStat())
    {
        NAS_EMM_RegStateMmcOriResumeSysInfoWithNotEu1Proc();
        return;
    }


    /* TA在TAI LIST && EU值为EU1*/
    /* 如果没有定时器 */
    /* 如果满足发起TAU的条件，直接发起，否则转NORMAL SERVICE */
    /* 大数据: 异系统TAU调用异系统TAU封装函数 */
    if (NAS_EMM_NO == NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded())
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc: TAU not needed, return Nor-service.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc_ENUM,LNAS_FUNCTION_LABEL3);

        /* TA在TAI List中，更新 L.V.R TAI*/
        NAS_EMM_SetLVRTai(pstPresentNetInfo);
        if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
        {
            /*保存PS LOC信息*/
            NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
        }

        NAS_EMM_TranStateRegNormalServiceOrRegLimitService();

        /* 转换EMM状态机MS_REG+SS_NORMAL_SEARVICE*/
        /*NAS_EMM_TAUSER_FSMTranState(    EMM_MS_REG,
                                        EMM_SS_REG_NORMAL_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);*/

        NAS_EMM_SetTauTypeNoProcedure();

        NAS_EMM_ProcHoWaitSysInfoBufferMsg();

        /*向MMC发送LMM_MMC_TAU_RESULT_IND消息*/
        NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara();

        NAS_EMM_TAU_ClearActiveFlagProc();

        return;
    }
    /* 修改函数名称 */
    (VOS_VOID)NAS_EMM_ClrWaitSysInfoBufferMsg();

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_RegNormalServiceOrUpdateMMMsgSysInfoCommProc
 Description     : REG+NORMAL_SERVICE状态或者UPDATE_MM状态下收到系统消息，判断是否发起TAU的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

  History             :
     1.wangchen 00209181    2012-08-24  Draft Enact
     2.lihong 00150010      2012-12-18  Modify:Emergency
     3.leixiantiao 00258641 2015-07-02  fix DTS2015062301014
*****************************************************************************/
VOS_VOID  NAS_EMM_RegNormalServiceOrUpdateMMMsgSysInfoCommProc( EMMC_EMM_CHANGE_INFO_ENUM_UINT32    ulChangeInfo )
{
    NAS_MM_NETWORK_ID_STRU             *pstPresentNetInfo = NAS_EMM_NULL_PTR;
    NAS_MM_TA_STRU                      stCurTa;
    NAS_LMM_PTL_TI_ENUM_UINT16          enPtlTimerId     = NAS_LMM_PTL_TI_BUTT;
    VOS_UINT32                          ulRslt = NAS_EMM_FAIL;
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt;

    NAS_LMM_MEM_SET_S(&stCurTa, sizeof(NAS_MM_TA_STRU), 0, sizeof(NAS_MM_TA_STRU));

    /* 获取当前TA信息 */
    NAS_EMM_GetCurrentTa(&stCurTa);
    pstPresentNetInfo                  = NAS_LMM_GetEmmInfoNetInfoPresentNetAddr();

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegNormalServiceOrUpdateMMMsgSysInfoCommProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_RegNormalServiceOrUpdateMMMsgSysInfoCommProc_ENUM,LNAS_ENTRY);
#if(FEATURE_ON == FEATURE_CSG)
    if((NAS_EMM_YES == NAS_LMM_IsCsgCampOn())
        &&(NAS_EMM_FAIL == NAS_EMM_TAU_IsCsgIdInAllowedOrOperatorCsgList()))
    {
        /* 重置TAU计数，启动TAU Procedure */
        NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

        ulRslt = NAS_EMM_ClrWaitSysInfoBufferMsg();
        if (NAS_EMM_SUCC == ulRslt)
        {
            NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);

            /*保存PS LOC信息*/
            NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
        }

        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_NOT_IN_CSG_LIST);

        return;
    }
#endif
    /* 如果当前TA不在TAI LIST */
    if (NAS_EMM_FAIL == NAS_EMM_TAU_IsCurrentTAInTaList())
    {
        /* 重置TAU计数，启动TAU Procedure */
        NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        /* 修改函数名称 */
        ulRslt = NAS_EMM_ClrWaitSysInfoBufferMsg();
        if (NAS_EMM_SUCC == ulRslt)
        {
            NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);

            /*保存PS LOC信息*/
            NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
        }
        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_NOT_IN_TAI_LIST);
        return;

    }
     /* TA在TAI LIST */
    /* 如果有定时器，等超时 */
    if ((NAS_EMM_YES == NAS_EMM_IsT3411orT3402Running(&enPtlTimerId))
        && (VOS_TRUE != NAS_EMM_IsEnterRegLimitService()))
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegNormalServiceOrUpdateMMMsgSysInfoCommProc: Check enter Nor-service or Upt-MM state.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegNormalServiceOrUpdateMMMsgSysInfoCommProc_ENUM,LNAS_FUNCTION_LABEL1);

        NAS_EMM_ProcHoWaitSysInfoBufferMsg();
        /* 小区信息更新,MMA不会立即更新网络信息,需要收到TAU IND才会更新,为规避该问题,
           LMM构造一条不带任何参数TAU IND消息上报给MMC */
        /* 在UE收到MMC发来的系统消息之后，若要发起attach或tau流程，按照原有流程处理；若有T3411或T3402在run，那么给MMC上报TAU结果的假消息 */
        /* 有定时器是3402在运行, 需上报TAU结果 */
        if ( TI_NAS_EMM_PTL_T3402 == enPtlTimerId )
        {
            NAS_EMM_SetTauTypeNoProcedure();

            ulTauRslt = MMC_LMM_TAU_RSLT_T3402_RUNNING_EPS_ONLY_SUCC;

            NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);
        }
        /* 有定时器是3411在运行, 需上报TAU结果 */
        if ( TI_NAS_EMM_PTL_T3411 == enPtlTimerId )
        {
            NAS_EMM_SetTauTypeNoProcedure();

            ulTauRslt = MMC_LMM_TAU_RSLT_FAILURE;
            NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);
        }
        return ;
    }

    /* TA在TAI LIST && 没有定时器  */
    /* 如果满足发起TAU的条件，直接发起，否则状态不变(UPDATE MM态一定有定时器) */
    if (NAS_EMM_NO == NAS_EMM_RegSomeStateStartTAUNeeded())
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegNormalServiceOrUpdateMMMsgSysInfoCommProc: TAU not needed, return Nor-service.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegNormalServiceOrUpdateMMMsgSysInfoCommProc_ENUM,LNAS_FUNCTION_LABEL2);

        /* TA在TAI List中，更新 L.V.R TAI*/
        NAS_EMM_SetLVRTai(pstPresentNetInfo);

        if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
        {
            /*保存PS LOC信息*/
            NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
        }

        if (VOS_TRUE == NAS_EMM_IsEnterRegLimitService())
        {
            NAS_EMM_TAUSER_FSMTranState(    EMM_MS_REG,
                                            EMM_SS_REG_LIMITED_SERVICE,
                                            TI_NAS_EMM_STATE_NO_TIMER);
        }
        else
        {
            NAS_EMM_ProcConnRelWaitSysInfoBufferMsg();
            NAS_EMM_ProcHoWaitSysInfoBufferMsg();
        }

        /* 当出现这样的场景，LMM在REG+NormalServiceOrUpdateMM状态收到MMC发来的系统消息，判断若此时是否有相应timer需要等待，
        若无timer，那么不论当前的TA,CELL,PLMN是否变化，LMM会给MMC上报一个TAU参数为空的ind. */
        /* 网络信息更新,MMA不会立即更新网络信息,需要收到TAU IND才会更新,为规避该问题,
        LMM构造一条不带任何参数TAU IND消息上报给MMC */
        NAS_EMM_SetTauTypeNoProcedure();

        /*向MMC发送LMM_MMC_TAU_RESULT_IND消息*/
        NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara();
        return;
    }
    /* 修改函数名称 */
    (VOS_VOID)NAS_EMM_ClrWaitSysInfoBufferMsg();

    return;

}
/*****************************************************************************
 Function Name   : NAS_EMM_TAU_StartTauForInterRat
 Description     : 异系统变换触发的TAU
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-4-30  Draft Enact
    2.wangchen 00209181         2013-10-24 Modify
    3.leixiantiao 00258641      2015-07-23 新增入参用于上报TAU发起原因
*****************************************************************************/
VOS_VOID  NAS_EMM_TAU_StartTauForInterRat( NAS_EMM_TAU_START_CAUSE_ENUM_UINT8 ucTauStartCause,
                                                        NAS_LMM_OM_TAU_START_TYPE_ENUM_UINT32 enTauStartType)
{
    if (NAS_LMM_SYS_CHNG_TYPE_HO != NAS_EMM_GetResumeType())
    {
        /* 读取GU的UMTS安全上下文，生成LTE的安全参数，并设置安全状态*/
        NAS_EMM_SecuResumeIdle();
    }
    /* 大数据: 置异系统标志，该标志在DISABLE LTE、DEREG和TAU SUCC成功时清除 */
    NAS_EMM_SetOmInterTauFlag(NAS_EMM_YES);
    /*NAS_EMM_TAU_SaveEmmTAUStartCause(     NAS_EMM_TAU_START_CAUSE_SYSINFO);*/
    NAS_EMM_TAU_SaveEmmTAUStartCause(ucTauStartCause);
    NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);

    NAS_EMM_TAU_StartTAUREQ(enTauStartType);
    return;
}



/*****************************************************************************
 Function Name   : NAS_LMM_PreProcMsgSrvccNofify
 Description     : 收到ID_MM_LMM_SRVCC_NOFIFY消息处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387    2014-12-18  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_PreProcMsgSrvccNofify(MsgBlock *    pMsg )
{
    MM_LMM_SRVCC_STATUS_NOTIFY_STRU            *pstSrvccNotify;

    pstSrvccNotify = (VOS_VOID*)pMsg;

    if (MM_LMM_SRVCC_STATUS_SUCC == pstSrvccNotify->enSrvccStatus)
    {
        NAS_LMM_SetEmmInfoSrvccFlag(NAS_EMM_SRVCC_HAPPENED);

    }
    else
    {
        NAS_LMM_SetEmmInfoSrvccFlag(NAS_EMM_SRVCC_NOT_HAPPENED);
    }
    return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMM_EmcPndReqTauAbnormalCommProc
 Description     : 紧急PDN连接建立引起的TAU异常公共处理
 Input           : pfTauRslt----------------TAU结果上报函数指针
                   pvPara-------------------TAU结果上报函数的入参
                   ucSs---------------------子状态
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2012-12-31  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_EmcPndReqTauAbnormalCommProc
(
    NAS_LMM_SEND_TAU_RESULT_ACT_FUN     pfTauRslt,
    const VOS_VOID                     *pvPara,
    NAS_EMM_SUB_STATE_ENUM_UINT16       ucSs
)
{
    /* 上报TAU结果 */
    NAS_EMM_TAU_SEND_MMC_RESULT_IND(pfTauRslt, pvPara);

    NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);

    /* 本地DETACH释放资源:动态内存、赋初值 */
    NAS_LMM_DeregReleaseResource();

    /*向MMC发送本地LMM_MMC_DETACH_IND消息*/
    NAS_EMM_MmcSendDetIndLocal( MMC_LMM_L_LOCAL_DETACH_OTHERS);

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_EMM_LocalDetachErrRecord(EMM_ERR_LOG_LOCAL_DETACH_TYPE_OTHER);
    #endif
    /* 记录ATTACH触发原因值 */
    NAS_EMM_GLO_AD_GetAttCau() = EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER;

    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                ucSs,
                                TI_NAS_EMM_STATE_NO_TIMER);
}

/*****************************************************************************
 Function Name   : NAS_EMM_TAU_ClearActiveFlagProc
 Description     : TAU清除Active flag的相关处理
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151      2015-03-15  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_TAU_ClearActiveFlagProc(VOS_VOID)
{
    NAS_EMM_TAU_LOG_INFO( "NAS_EMM_TAU_ClearActiveFlagProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_ClearActiveFlagProc_ENUM,LNAS_ENTRY);

    /* TMO定制需求控制active flag标识清除 */
    NAS_EMM_TAU_SaveEmmTmoActiveFlagCtrl(NAS_EMM_TMO_ACTIVE_FLAG_CTRL_INVALID);

    /* 勾出当前FLAG的状态 */
    NAS_LMM_SndOmSetTmoActiveFlag(NAS_EMM_TMO_ACTIVE_FLAG_CTRL_INVALID);

    /* TAU的active flag标识清除 */
    NAS_EMM_TAU_SaveEmmTauReqActiveCtrl(NAS_EMM_TAU_NO_BEARER_EST_REQ);

    NAS_EMM_TAU_SaveEmmPtmsiActiveFlagCtrl(NAS_EMM_PTMSI_ACTIVE_FLAG_CTRL_INVALID);
    return;
}
#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 Function Name   : NAS_EMM_TAU_SendRrcDsdsBeginNotify
 Description     : TAU流程保护，发送业务通知开始消息给LRRC模块
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.c00134407      2014-7-9  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_TAU_SendRrcDsdsBeginNotify(VOS_VOID)
{
    LRRC_LNAS_SESSION_TYPE_ENUM_UINT8  enSessionType;
    NAS_EMM_DSDS_TAU_TYPE_ENUM_UINT32  enTauType;

     /*若异常后能进入NORMAL态，则认为当前TAU流程为LOW-TAU，否则为HIGH-TAU*/
    /* if(NAS_EMM_SUCC == NAS_EMM_CheckEnterRegNormal())
    {
        enSessionType = LRRC_LNAS_SESSION_TYPE_PS_LOW_TAU;
    }
    else
    {
        enSessionType = LRRC_LNAS_SESSION_TYPE_PS_HIGH_TAU;
    }*/
    /* Low优先级的TAU很少见，若流程异常时，可能会导致资源没有释放，而HIGH类型，
       即使TAU流程没有正常结束，下次TAU时，申请相同资源，TAU成功后,会释放资源因此取消LOW类型 */
    enSessionType = LRRC_LNAS_SESSION_TYPE_PS_HIGH_TAU;

    enTauType = (NAS_EMM_DSDS_TAU_TYPE_ENUM_UINT32)enSessionType;

    /*保存当前TAU的类型*/
    NAS_EMM_SetDsdsTauType(enTauType);

    /*组装并发送业务通知开始消息给LRRC模块*/
    NAS_LMM_SendRrcDsdsBeginNotify(enSessionType);

     return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_TAU_SendRrcDsdsEndNotify
 Description     : TAU流程保护，发送业务通知结束消息给LRRC模块
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.c00134407      2014-7-9  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_TAU_SendRrcDsdsEndNotify(VOS_VOID)
{
     LRRC_LNAS_SESSION_TYPE_ENUM_UINT8  enSessionType;

     /*获取当前TAU的类型*/
     enSessionType = (LRRC_LNAS_SESSION_TYPE_ENUM_UINT8)NAS_EMM_GetDsdsTauType();

     /*组装并发送业务通知结束消息给LRRC模块*/
     NAS_LMM_SendRrcDsdsEndNotify(enSessionType);

     return;
}
#endif
#if(FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 Function Name   : NAS_EMM_IsCsgIdChangeTauStart
 Description     : 是否发起CSG ID CHANGE 导致的TAU
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.yanglei    2015-11-3  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsTauInitSsWaitCNCnfIsCsgIdChangeTauStart(VOS_VOID)
{

    if((NAS_EMM_YES == NAS_LMM_IsCsgCampOn())
        &&(NAS_EMM_FAIL == NAS_EMM_TAU_IsCsgIdInAllowedOrOperatorCsgList())
        &&(NAS_EMM_NO == NAS_LMM_IsCurCsgIdEqualLastAttmpRegCsgId()))
    {
        /*设置EPS状态为EU2*/
        NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);

        if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
        {
            /*保存PS LOC信息*/
            NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
        }

        /*停止T3430定时器*/
        NAS_LMM_StopStateTimer(              TI_NAS_EMM_STATE_TAU_T3430);

#if (FEATURE_ON == FEATURE_DSDS)
        /*发送end notify消息给RRC，通知RRC释放资源*/
        NAS_EMM_TAU_SendRrcDsdsEndNotify();
#endif

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
        NAS_EMM_SendMtcTAUEndType();
#endif

        /* TauAttemptCount清零*/
        NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);

        if (NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ != NAS_EMM_TAU_GetEmmTAUStartCause())
        {
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        }

        /* 重新触发TAU*/
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_CSG_ID_CHANGE);

        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}
/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsAtpUpdataIsCsgIdNotInListTauStart
 Description     : 是否发起CSG ID NOT IN LIST 导致的TAU
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.yanglei    2015-11-3  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsAtpUpdataIsCsgIdNotInListTauStart
(
    VOS_VOID
)
{
    NAS_LMM_PTL_TI_ENUM_UINT16          enPtlTimerId    = NAS_LMM_PTL_TI_BUTT;
    if((NAS_EMM_YES == NAS_LMM_IsCsgCampOn())
        &&(NAS_EMM_FAIL == NAS_EMM_TAU_IsCsgIdInAllowedOrOperatorCsgList()))
    {
        if (NAS_LMM_TIMER_RUNNING != NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3346))
        {
            /* CSG ID和上次尝试的CSG ID不同,或没有T3411或T3402 */
            if ((NAS_EMM_NO == NAS_LMM_IsCurCsgIdEqualLastAttmpRegCsgId())
                || (NAS_EMM_NO == NAS_EMM_IsT3411orT3402Running(&enPtlTimerId)))
            {

                /* 重置TAU计数 */
                NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);
                NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

                /*启动TAU Procedure*/
                /* 新增入参TAU发起原因 */
                NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_NOT_IN_CSG_LIST);

                return NAS_EMM_YES;

            }
        }

    }
    return NAS_EMM_NO;
}
/*****************************************************************************
 Function Name   : NAS_EMM_MsDeRegInitSsWaitCNDetachCnfIsCsgIdNotInListTauStart
 Description     : 是否发起CSG ID NOT IN LIST 导致的TAU
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.yanglei    2015-11-3  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsDeRegInitSsWaitCNDetachCnfIsCsgIdNotInListTauStart(VOS_VOID)
{

    if((NAS_EMM_YES == NAS_LMM_IsCsgCampOn())
        &&(NAS_EMM_FAIL == NAS_EMM_TAU_IsCsgIdInAllowedOrOperatorCsgList()))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsDeRegInitSsWaitCNDetachCnfIsCsgIdNotInListTauStart:CSGID not in CSG List.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDeRegInitSsWaitCNDetachCnfIsCsgIdNotInListTauStart_ENUM,LNAS_FUNCTION_LABEL1);

        /* 设置流程冲突标志位DETACH */
        NAS_EMM_TAU_SaveEmmCollisionCtrl(NAS_EMM_COLLISION_DETACH);

        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

        /* 如果是DETACH类型为EPS/IMSI，则设置联合DETACH被TAU打断标识，这样
        发起的TAU类型为联合TAU */
        if (MMC_LMM_MO_DET_CS_PS == NAS_EMM_GetDetachType())
        {
            /* 设置联合DETACH被TAU打断标识，这样后续发起的TAU类型仍然为联合TAU */
            NAS_EMM_TAU_SetEmmCombinedDetachBlockFlag(NAS_EMM_COM_DET_BLO_YES);
        }

        /* 调用DETACH的函数，结束DETACH流程*/
        NAS_EMM_DetachToTAU();

        /* 启动TAU Procedure
        注:MO_DETACH流程中触发TAU，因为DETACH_COLLISION标志，必然携带ACTVIE,
        不判断上行阻塞*/
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_NOT_IN_CSG_LIST);

        return NAS_EMM_YES;
    }
    return NAS_EMM_NO;
}
/*****************************************************************************
 Function Name   : NAS_EMM_RegStateMmcOriResumeSysInfoIsCsgIdNotInListTauNeed
 Description     : 是否发起CSG ID NOT IN LIST 导致的TAU
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.yanglei    2015-11-3  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_RegStateMmcOriResumeSysInfoIsCsgIdNotInListTauNeed
(
    VOS_VOID
)
{
    NAS_LMM_PTL_TI_ENUM_UINT16          enPtlTimerId     = NAS_LMM_PTL_TI_BUTT;
    if((NAS_EMM_YES == NAS_LMM_IsCsgCampOn())
        &&(NAS_EMM_FAIL == NAS_EMM_TAU_IsCsgIdInAllowedOrOperatorCsgList()))
    {
        /* CSG ID和上次尝试的CSG ID不同,或没有T3411或T3402,直接发起TAU */
        if ((NAS_EMM_NO == NAS_LMM_IsCurCsgIdEqualLastAttmpRegCsgId())
           || (NAS_EMM_NO == NAS_EMM_IsT3411orT3402Running(&enPtlTimerId)))
        {
            return NAS_EMM_YES;
        }
    }
    return NAS_EMM_NO;
}
#endif
/*****************************************************************************
 Function Name   : NAS_EMM_MsTauInitSsWaitCNCnfSysChangeOrNotProc
 Description     : 系统消息改变与否的处理
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.yanglei    2015-11-3  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_MsTauInitSsWaitCNCnfSysChangeOrNotProc
(
    EMMC_EMM_CHANGE_INFO_ENUM_UINT32 ulChangeInfo
)
{

    VOS_UINT32                          ulTaRslt    = NAS_EMM_FAIL;
    NAS_LMM_NETWORK_INFO_STRU          *pMmNetInfo = NAS_EMM_NULL_PTR;

    /* 获取EMM维护的网络信息*/
    pMmNetInfo                          = NAS_LMM_GetEmmInfoNetInfoAddr();

    /* 如果TA发生变化，先释放连接，再重新触发TAU*/
    if ((EMMC_EMM_CHANGE_PLMN == ulChangeInfo)
      ||(EMMC_EMM_CHANGE_TA == ulChangeInfo))
    {
        /*设置EPS状态为EU2*/
        NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);
        if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
        {
            /*保存PS LOC信息*/
            NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
        }
        /*停止T3430定时器*/
        NAS_LMM_StopStateTimer(              TI_NAS_EMM_STATE_TAU_T3430);

        #if (FEATURE_ON == FEATURE_DSDS)
        /*发送end notify消息给RRC，通知RRC释放资源*/
        NAS_EMM_TAU_SendRrcDsdsEndNotify();
        #endif

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
        NAS_EMM_SendMtcTAUEndType();
#endif

        /* TauAttemptCount清零*/
        NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);
        /* 如果TA不在TAI List中，修改TAU启动原因，触发TA-Updating TAU,
           如果TA在TAI List中，则不做处理，TAU启动原因不变*/
        ulTaRslt = NAS_EMM_TAU_IsCurrentTAInTaList();
        if ((NAS_EMM_FAIL == ulTaRslt)
            && (NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ != NAS_EMM_TAU_GetEmmTAUStartCause()))
        {
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        }
        /* 重新触发TAU*/
        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_PLMN_TA_CHANGE);
    }
    else
    {
        /*设置L.V.R TAI*/
        NAS_EMM_SetLVRTai(&pMmNetInfo->stPresentNetId);

        if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
        {
            /*保存PS LOC信息*/
            NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
        }
    }
    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsAtpUpdataIsTaNotListProc
 Description     : TA不在TAI LIST的处理
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.yanglei    2015-11-3  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_MsRegSsAtpUpdataTaIsNotListProc
(
    VOS_VOID
)
{
    NAS_LMM_PTL_TI_ENUM_UINT16          enPtlTimerId;
    NAS_MM_TA_STRU                     *pstLastAttmpRegTa = NAS_EMM_NULL_PTR;
    NAS_MM_TA_STRU                      stCurTa;
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt = MMC_LMM_TAU_RSLT_BUTT;

    NAS_LMM_MEM_SET_S(&stCurTa, sizeof(NAS_MM_TA_STRU), 0, sizeof(NAS_MM_TA_STRU));

    /* 获取当前TA和上次尝试注册的TA信息 */
    NAS_EMM_GetCurrentTa(&stCurTa);
    pstLastAttmpRegTa                   = NAS_LMM_GetEmmInfoNetInfoLastAttmpRegTaAddr();

    if (NAS_LMM_TIMER_RUNNING != NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3346))
    {
        /* 与上次尝试注册的TA相同 && 有定时器 && EU值不为EU1 ，等超时;  否则立即发起TAU */
        if(    (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatch(pstLastAttmpRegTa, &stCurTa))
            && (NAS_EMM_YES == NAS_EMM_IsT3411orT3402Running(&enPtlTimerId))
            && (EMM_US_UPDATED_EU1 != NAS_EMM_TAUSER_GetAuxFsmUpStat()) )
        {
            /* 若之前有过因RRC_REL导致的TAU_REQ发送失败的情况，那么此时应发起TAU */
            if(PS_TRUE == NAS_LMM_GetTauReqSndFailFlag())
            {
                 TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsAtpUpdataMsgSysinfo_ENUM,LNAS_LEAVE);
                 /* 新增入参TAU发起原因 */
                 NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_SND_MSG_FAIL);

                 return;
            }

            /* 网络信息更新,MMA不会立即更新网络信息,需要收到TAU IND才会更新,为规避该问题,
               LMM构造一条不带任何参数TAU IND消息上报给MMC */
            /* 在UE收到MMC发来的系统消息之后，若要发起attach或tau流程，按照原有流程处理；若有T3346在run，且有T3411或T3402在run，那么给MMC上报TAU结果的假消息 */
            /* 有定时器是3402在运行, 需上报TAU结果 */
            if ( TI_NAS_EMM_PTL_T3402 == enPtlTimerId )
            {
                NAS_EMM_SetTauTypeNoProcedure();

                ulTauRslt = MMC_LMM_TAU_RSLT_T3402_RUNNING;
                NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);

            }
            /* 有定时器是3411在运行, 需上报TAU结果 */
            if ( TI_NAS_EMM_PTL_T3411 == enPtlTimerId )
            {
                NAS_EMM_SetTauTypeNoProcedure();

                ulTauRslt = MMC_LMM_TAU_RSLT_FAILURE;
                NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);
            }
            return;
        }
        else
        {
            /* 重置TAU计数 */
            NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

            /*启动TAU Procedure*/
            /* 新增入参TAU发起原因 */
            NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_NOT_IN_TAI_LIST);
        }
    }
    else
    {
        /* 在UE收到MMC发来的系统消息之后，若要发起attach或tau流程，按照原有流程处理；若无T3346在run，那么给MMC上报TAU结果的假消息 */
        /* 小区信息更新,MMA不会立即更新网络信息,需要收到TAU IND才会更新,为规避该问题,
        LMM构造一条不带任何参数TAU IND消息上报给MMC */
        NAS_EMM_SetTauTypeNoProcedure();

        /*向MMC发送LMM_MMC_TAU_RESULT_IND消息*/
        NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara();
    }
    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_RegStateMmcOriResumeSysInfoIsIsrActP4TAUNeed
 Description     : 判断是否需要发起ISR_ACT_P4_TAU
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.yanglei    2015-11-3  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_RegStateMmcOriResumeSysInfoIsIsrActP4TAUNeed(VOS_VOID)
{
    MMC_LMM_TIN_TYPE_ENUM_UINT32        ulTinType;
    ulTinType = NAS_EMM_GetTinType();

    if ((NAS_LMM_RSM_SYS_CHNG_DIR_G2L == NAS_EMM_GetResumeDir())
           && (NAS_EMM_YES == NAS_EMM_IsAnnexP4ConditionSatisfied())
           && (MMC_LMM_TIN_RAT_RELATED_TMSI == ulTinType))
    {
        return NAS_EMM_YES;
    }
    return NAS_EMM_NO;
}
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
/*****************************************************************************
 Function Name   : NAS_EMM_SendMtcTAUEndType
 Description     :
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.yanglei    2015-01-05  Draft Enact

*****************************************************************************/
MTC_SESSION_TYPE_ENUM_UINT8  NAS_EMM_GetTAUMtcSessionType
(
    VOS_VOID
)
{
    MTC_SESSION_TYPE_ENUM_UINT8         enMtcSessionType = MTC_SESSION_TYPE_BUTT;

    if (NAS_EMM_CN_TAU_TYPE_TA_UPDATING == NAS_EMM_TAU_GetTAUtype())
    {
        enMtcSessionType = MTC_SESSION_TYPE_TAU_ONLY_EPS;
    }
    else if(NAS_EMM_CN_TAU_TYPE_PERIODIC_UPDATING == NAS_EMM_TAU_GetTAUtype())
    {
        enMtcSessionType = MTC_SESSION_TYPE_TAU_PERIODIC;
    }
    else
    {
        enMtcSessionType = MTC_SESSION_TYPE_TAU_COMBINED;
    }

    return  enMtcSessionType;

}

/*****************************************************************************
 Function Name   : NAS_EMM_SendMtcTAUEndType
 Description     :
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.yanglei    2015-01-05  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SendMtcTAUEndType
(
    VOS_VOID
)
{
    TAF_CTRL_STRU                       stCtrl;
    MTC_SESSION_TYPE_ENUM_UINT8         enMtcSessionType = MTC_SESSION_TYPE_BUTT;
    PS_MEM_SET(&stCtrl, 0x00, sizeof(TAF_CTRL_STRU));

    enMtcSessionType = NAS_EMM_GetTAUMtcSessionType();

    stCtrl.ulModuleId = PS_PID_MM;
    MTC_SetEndSessionInfo(&stCtrl,enMtcSessionType);
    return;
}
#endif


/*lint +e961*/
/*lint +e960*/
/*lint +e831*/
/*lint +e669*/
/*lint +e589*/



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



