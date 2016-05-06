

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "NasEmmPubUResume.h"
#include "NasEmmPubUSuspend.h"
#include "NasLmmPubMFsm.h"
#include "NasLmmPublic.h"
#include "NasLmmPubMOsa.h"
#include "NasEmmPubUGlobal.h"
#include "NasLmmPubMTimer.h"
#include "MmcLmmInterface.h"
#include "NasEmmcEmmInterface.h"
#include "NasEmmTauInterface.h"
#include "NasEmmMrrcPubInterface.h"
#include "NasEmmAttDetInterface.h"
#include "NasEmmPlmnInterface.h"
#include "NasEmmSecuInterface.h"
#include "NasEmmAttDetInclude.h"

#include "NasEmmTAUProc.h"
#include "NasEmmPlmn.h"
#include "NasEmmPubUGlobal.h"


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

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMPUBURESUME_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMPUBURESUME_C
/*lint +e767*/


/* DCM定制需求 GU到L的切换不判断被禁TA开关, 初始化为关闭 */
VOS_UINT32    g_ulHoIgnoreForbidTaFlag = NAS_EMM_HO_IGNORE_FORBID_TA_FLAG_INVALID;

/* 兰州CSFB定制需求 RRC触发的GU到L的异系统变换TAU类型NV开关, 打开: 1, 关闭: 0
功能开启时，所有RRC触发的GU到L的异系统变换后，到L下均要发起imsi_attach类型的TAU */
VOS_UINT32    g_ulNasCsfbTauType2Flag = 0;

/* 澳电定制需求 3402定时器启动期间在GU下用户指定搜网到L是否立即发起注册的NV开关, 打开: 1, 关闭: 0 */
VOS_UINT32    g_ulNasAustraliaFlag = 0;

/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name   : NAS_EMM_PUBU_FSMTranState
 Description     :
 Input           :
 Output          :
 Return          :

 History         :
    1.HanLufeng 41410      2011-4-26  Draft Enact
*****************************************************************************/
VOS_VOID    NAS_EMM_PUBU_FSMTranState(
                                    NAS_EMM_MAIN_STATE_ENUM_UINT16  usMs,
                                    NAS_EMM_SUB_STATE_ENUM_UINT16   usSs,
                                    NAS_EMM_STATE_TI_ENUM_UINT16    usTi)
{
    NAS_LMM_FSM_STATE_STRU              EmmStat;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PUBU_FSMTranState is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PUBU_FSMTranState_ENUM,LNAS_ENTRY);

    EmmStat.enFsmId                   = NAS_LMM_PARALLEL_FSM_EMM;
    EmmStat.enMainState               = usMs;
    EmmStat.enSubState                = usSs;
    EmmStat.enStaTId                  = usTi;
    NAS_LMM_StaTransProc(EmmStat);

    /* 启动定时器 */
    NAS_LMM_StartStateTimer(usTi);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SaveLrrcResumePara
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-28  Draft Enact

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID  NAS_EMM_SaveLrrcResumePara( const LRRC_LMM_RESUME_IND_STRU  *pLrrcLmmResumeInd )
{
    NAS_EMM_SetResumeOri(NAS_LMM_SYS_CHNG_ORI_LRRC);
    NAS_EMM_SetResumeDir(pLrrcLmmResumeInd->enRsmDir);
    NAS_EMM_SetResumeType(pLrrcLmmResumeInd->enResumeType);

    NAS_LMM_MEM_CPY_S(  NAS_EMM_GetStateBeforeResumeAddr(),
                        sizeof(NAS_LMM_FSM_STATE_STRU),
                        NAS_LMM_GetCurFsmAddr(NAS_LMM_PARALLEL_FSM_EMM),
                        sizeof(NAS_LMM_FSM_STATE_STRU));
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SaveMmcResumePara
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-28  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SaveMmcResumePara( VOS_VOID )
{
    NAS_EMM_SetResumeOri(NAS_LMM_SYS_CHNG_ORI_MMC);

    NAS_LMM_MEM_CPY_S(  NAS_EMM_GetStateBeforeResumeAddr(),
                        sizeof(NAS_LMM_FSM_STATE_STRU),
                        NAS_LMM_GetCurFsmAddr(NAS_LMM_PARALLEL_FSM_EMM),
                        sizeof(NAS_LMM_FSM_STATE_STRU));

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_MsAnySsNoCellAvailMsgRrcRsumeInd
 Description     : LMM收到解挂消息，要先给ESM和ERABM解挂，等ERABM解挂
                   结束，能够数传时，再通知MMC解挂

                    MMC    ERABM/ESM        LMM         LRRC
                    |           |           |           |
                    |           |           |   RSM_IND |
                    |           |  RSM_IND  | <-------- |
                    |           | <-------- |           |
                    |           | <-------- |           |
                    |           |           |           |
                    |           | --------> |           |
                    |           | --------> |           |
                    |    RSM_IND|           |           |
                    |  <------------------- | RSM_RSP   |
                    |           |           | --------> |
                    |           |           |           |
                    |           |           |           |

 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.Hanlufeng 41410      2011-4-23  Draft Enact
    2.zhengjunyan 00148421 2011-09-13 DTS2011082202543
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsAnySsNoCellAvailMsgRrcRsumeInd(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru )
{
    LRRC_LMM_RESUME_IND_STRU  *pLrrcLmmResumeInd;

    /* 注册/服务状态上报上移MMC，删除注册/服务状态相关代码 */
    (VOS_VOID)ulMsgId;

    pLrrcLmmResumeInd = (LRRC_LMM_RESUME_IND_STRU *)pMsgStru;

    NAS_EMM_PUBU_LOG2_INFO("NAS_EMM_MsAnySsNoCellAvailMsgRrcRsumeInd: DIR = , enResumeType =.",
                        pLrrcLmmResumeInd->enRsmDir,
                        pLrrcLmmResumeInd->enResumeType);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsAnySsNoCellAvailMsgRrcRsumeInd_ENUM,LNAS_EMM_RESUME_DIR,
                        pLrrcLmmResumeInd->enRsmDir);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsAnySsNoCellAvailMsgRrcRsumeInd_ENUM,LNAS_EMM_RESUME_TYPE,
                        pLrrcLmmResumeInd->enResumeType);

    /* 记录RESUME参数 */
    NAS_EMM_SaveLrrcResumePara(pLrrcLmmResumeInd);

    /* 激活ESM, ERABM */
    NAS_EMM_SendEsmResumeInd();
    NAS_EMM_SendErabmResumeInd();

    /* 状态迁移 */
    NAS_EMM_PUBU_FSMTranState(  EMM_MS_RESUME,
                                EMM_SS_RESUME_RRCRSM_WAIT_OTHER_RESUME,
                                TI_NAS_EMM_RRCRSM_WAIT_OTHER_RESUME_RSP_TIMER);

    /* 当前的 LTE为激活态 */
    NAS_EMM_GetCurLteState() = NAS_LMM_CUR_LTE_ACTIVE;
    if(LRRC_LMM_SYS_CHNG_TYPE_RESEL_REVERSE > pLrrcLmmResumeInd->enResumeType)
    {
        /* 注册/服务状态上报上移MMC，删除注册/服务状态相关代码 */

        /* 删除当前小区 */
        NAS_EMMC_DeleteCurrentAreaCellId();
    }

    /* 判读如果是HO类型的resume,则清空映射安全上下文产生的标志*/
    if(LRRC_LMM_SYS_CHNG_TYPE_HO == pLrrcLmmResumeInd->enResumeType)
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsAnySsNoCellAvailMsgRrcRsumeInd:HO succ.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAnySsNoCellAvailMsgRrcRsumeInd_ENUM,LNAS_EMM_HO_SUCC);
        NAS_EMM_SecuSetInterRatHoNotMapped();

        /*在GU->L的切换场景，先将L的链路状态切换为信令连接态，便于处理后续收到的RABM DRB建立的消息 */
        NAS_EMM_ChangeRrcConnStateToEstSignal();

        /* 停止T3412和T3423定时器*/
        NAS_LMM_StopPtlTimer(               TI_NAS_EMM_PTL_T3412);
        NAS_LMM_StopPtlTimer(               TI_NAS_EMM_PTL_T3423);


        /*通知GU模T3412停止*/
        NAS_EMM_SendTimerStateNotify(TI_NAS_EMM_PTL_T3412, LMM_MMC_TIMER_STOP);

        /*通知GU模T3423停止*/
        NAS_EMM_SendTimerStateNotify(TI_NAS_EMM_PTL_T3423, LMM_MMC_TIMER_STOP);

    }


    /*RESEL/HO/REDIR:L模收到RESUME消息后就认为该过程结束，不会回退到GU模*/
    if ((LRRC_LMM_SYS_CHNG_TYPE_RESEL == pLrrcLmmResumeInd->enResumeType) ||
        (LRRC_LMM_SYS_CHNG_TYPE_HO == pLrrcLmmResumeInd->enResumeType) ||
        (LRRC_LMM_SYS_CHNG_TYPE_REDIR == pLrrcLmmResumeInd->enResumeType))
    {
        if (EMM_MS_REG != NAS_EMM_GetMsBefResume())
        {
            NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsAnySsNoCellAvailMsgRrcRsumeInd:HO succ.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAnySsNoCellAvailMsgRrcRsumeInd_ENUM,LNAS_EMM_HO_SUCC);
            return NAS_LMM_MSG_HANDLED;
        }
        NAS_EMM_ProcInterSystemTransferBearerInfo();
    }
    /*CCO过程等待触发TAU建链成功后才认为该过程结束:存在ISR激活后承载，如果CCO成功
       去激活ISR并更新承载的ISR标识；如果CCO失败不去激活ISR*/
    if (LRRC_LMM_SYS_CHNG_TYPE_CCO == pLrrcLmmResumeInd->enResumeType)
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsAnySsNoCellAvailMsgRrcRsumeInd:CCO TYPE.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAnySsNoCellAvailMsgRrcRsumeInd_ENUM,LNAS_EMM_CCO_TYPE);
        if (EMM_MS_REG != NAS_EMM_GetMsBefResume())
        {
            NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsAnySsNoCellAvailMsgRrcRsumeInd:HO succ.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAnySsNoCellAvailMsgRrcRsumeInd_ENUM,LNAS_EMM_HO_SUCC);
            return NAS_LMM_MSG_HANDLED;
        }
        if ((MMC_LMM_TIN_RAT_RELATED_TMSI == NAS_EMM_GetTinType()) &&
            (NAS_EMM_SUCC == NAS_EMM_IsBearIsrActAfter()))
        {
            NAS_LMM_SetEmmInfoTinChagFlag(NAS_EMM_CCO_CHANGE_TIN_VALID);
            NAS_LMM_SetTempEmmInfoTinType(MMC_LMM_TIN_RAT_RELATED_TMSI);
            NAS_EMM_SetTinType(MMC_LMM_TIN_P_TMSI);
        }
    }
    return NAS_LMM_MSG_HANDLED;

}


/*****************************************************************************
 Function Name   : NAS_EMM_SendMmcResumeInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-26  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SendMmcResumeInd( VOS_VOID )
{
    LMM_MMC_RESUME_IND_STRU           *pstMmcSuspendIndMsg;

    /* 申请MMC内部消息 */
    pstMmcSuspendIndMsg = (VOS_VOID *) NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_RESUME_IND_STRU));
    if (NAS_LMM_NULL_PTR == pstMmcSuspendIndMsg)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_SendMmcResumeInd: MSG ALLOC ERROR!!!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SendMmcResumeInd_ENUM,LNAS_NULL_PTR);
        return ;
    }

    /* 清空 */
    NAS_LMM_MEM_SET_S(  pstMmcSuspendIndMsg,
                        sizeof(LMM_MMC_RESUME_IND_STRU),
                        0,
                        sizeof(LMM_MMC_RESUME_IND_STRU));

    /* 打包VOS消息头 */
    EMM_PUBU_COMP_MMC_MSG_HEADER((pstMmcSuspendIndMsg),
                             NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LMM_MMC_RESUME_IND_STRU));

    /* 填充消息ID */
    pstMmcSuspendIndMsg->ulMsgId        = ID_LMM_MMC_RESUME_IND;

    /* 填充消息体 */
    pstMmcSuspendIndMsg->ulOpId         = NAS_EMM_OPID_MMC;

    /* 发送MMC内部消息 */
    NAS_LMM_SendLmmMmcMsg(pstMmcSuspendIndMsg);

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_SendEsmResumeInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-26  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SendEsmResumeInd( VOS_VOID )
{
    EMM_ESM_RESUME_IND_STRU           *pstEsmResumeIndMsg;

    /* 申请DOPRA消息 */
    pstEsmResumeIndMsg = (VOS_VOID *) NAS_LMM_ALLOC_MSG(sizeof(EMM_ESM_RESUME_IND_STRU));
    if (NAS_LMM_NULL_PTR == pstEsmResumeIndMsg)
    {
        return ;
    }

    /* 清空 */
    NAS_LMM_MEM_SET_S(  pstEsmResumeIndMsg,
                        sizeof(EMM_ESM_RESUME_IND_STRU),
                        0,
                        sizeof(EMM_ESM_RESUME_IND_STRU));

    /* 打包VOS消息头 */
    EMM_PUBU_COMP_ESM_MSG_HEADER((pstEsmResumeIndMsg),
                             NAS_EMM_GET_MSG_LENGTH_NO_HEADER(EMM_ESM_RESUME_IND_STRU));

    /* 填充消息ID */
    pstEsmResumeIndMsg->ulMsgId        = ID_EMM_ESM_RESUME_IND;


    /* 发送DOPRA消息 */
    NAS_LMM_SEND_MSG(pstEsmResumeIndMsg);

    return;
}



/*****************************************************************************
 Function Name   : NAS_EMM_SendErabmResumeInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-26  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SendErabmResumeInd( VOS_VOID )
{
    EMM_ERABM_RESUME_IND_STRU           *pstLrabmResumeIndMsg;

    /* 申请DOPRA消息 */
    pstLrabmResumeIndMsg = (VOS_VOID *) NAS_LMM_ALLOC_MSG(sizeof(EMM_ERABM_RESUME_IND_STRU));
    if (NAS_LMM_NULL_PTR == pstLrabmResumeIndMsg)
    {
        return ;
    }

    /* 清空 */
    NAS_LMM_MEM_SET_S(  pstLrabmResumeIndMsg,
                        sizeof(EMM_ERABM_RESUME_IND_STRU),
                        0,
                        sizeof(EMM_ERABM_RESUME_IND_STRU));

    /* 打包VOS消息头 */
    EMM_PUBU_COMP_ERABM_MSG_HEADER((pstLrabmResumeIndMsg),
                             NAS_EMM_GET_MSG_LENGTH_NO_HEADER(EMM_ERABM_RESUME_IND_STRU));

    /* 填充消息ID */
    pstLrabmResumeIndMsg->ulMsgId        = ID_EMM_ERABM_RESUME_IND;
    pstLrabmResumeIndMsg->enSysChngType  = NAS_EMM_GetResumeType();


    /* 发送DOPRA消息 */
    NAS_LMM_SEND_MSG(pstLrabmResumeIndMsg);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SendLrcResumeRsp
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-28  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_EMM_SendLrcResumeRsp( VOS_VOID)
{
    LRRC_LMM_RESUME_RSP_STRU           *pstLrrcResumeRspMsg;

    /* 申请DOPRA消息 */
    pstLrrcResumeRspMsg = (VOS_VOID *) NAS_LMM_ALLOC_MSG(sizeof(LRRC_LMM_RESUME_RSP_STRU));
    if (NAS_LMM_NULL_PTR == pstLrrcResumeRspMsg)
    {
        return ;
    }

    /* 清空 */
    NAS_LMM_MEM_SET_S(  pstLrrcResumeRspMsg,
                        sizeof(LRRC_LMM_RESUME_RSP_STRU),
                        0,
                        sizeof(LRRC_LMM_RESUME_RSP_STRU));

    /* 打包VOS消息头 */
    NAS_EMM_SET_RRC_MSG_HEADER((pstLrrcResumeRspMsg),
            NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LRRC_LMM_RESUME_RSP_STRU));

    /* 填充消息ID */
    pstLrrcResumeRspMsg->enMsgId       = ID_LRRC_LMM_RESUME_RSP;

    /* 发送DOPRA消息 */
    NAS_LMM_SEND_MSG(pstLrrcResumeRspMsg);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_NoCellSuspendMsgMmcPlmnReq
 Description     : 若当前的 LTE为挂起态，则给ESM和ERABM通知激活，并改为LTE激活态
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.Hanlufeng 41410      2011-5-5  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_EMM_NoCellSuspendMsgMmcPlmnReq( VOS_VOID )
{
    /* 注册/服务状态上报上移MMC，删除注册/服务状态相关代码 */

    /* 若当前的 LTE为挂起态，则给ESM和ERABM通知激活，并改为LTE激活态 */
    if( (   (NAS_EMM_PUBU_CHK_STAT_VALID(EMM_MS_DEREG,EMM_SS_DEREG_NO_CELL_AVAILABLE))
           ||(NAS_EMM_PUBU_CHK_STAT_VALID(EMM_MS_REG,EMM_SS_REG_NO_CELL_AVAILABLE))
         )
         && (NAS_LMM_CUR_LTE_SUSPEND == NAS_EMM_GetCurLteState())
       )
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_NoCellSuspendMsgMmcPlmnReq: LTE SUSPEND. ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_NoCellSuspendMsgMmcPlmnReq_ENUM,LNAS_EMM_LTE_SUSPEND);

        /* 当前的 LTE为激活态 */
        NAS_EMM_GetCurLteState() = NAS_LMM_CUR_LTE_ACTIVE;

        /* 记录RESUME参数 */
        NAS_EMM_SaveMmcResumePara();

        /*去激活ISR必须放在获取安全参数之前，否则，获取不到正确的安全参数*/
        NAS_EMM_ProcInterSystemTransferBearerInfo();

        /* 连接状态仍为空闲态 */

        /* 若TIN ==  PTMSI，则获取GU的安全参数 */
        NAS_EMM_MmcRsmGetSecuPara();

        /* 激活ESM, ERABM */
        NAS_EMM_SendEsmResumeInd();
        NAS_EMM_SendErabmResumeInd();

        /* 丢网后，上层会清除PLMN ID等消息，因此重新驻留后，需要上报location info */
        /* 删除当前小区 */
        NAS_EMMC_DeleteCurrentAreaCellId();
        /* 注册/服务状态上报上移MMC，删除注册/服务状态相关代码 */

        if(EMM_MS_REG == NAS_LMM_GetEmmCurFsmMS())
        {
             /* 如果当前为注册态，且当前只有L接入技术，当TIN为PTMSI时，先LOCAL DETACH，
                这样等收到系统信息时一定发起ATTACH */
            if ((MMC_LMM_TIN_P_TMSI == NAS_EMM_GetTinType())
                &&(NAS_LMM_SUCC ==  NAS_EMM_lteRatIsOnlyExist()))
            {

                NAS_EMM_LocalDetachProc();
                #if (FEATURE_PTM == FEATURE_ON)
                NAS_EMM_LocalDetachErrRecord(EMM_ERR_LOG_LOCAL_DETACH_TYPE_OTHER);
                #endif

                /* 将状态转移至MS_DEREG + SS_DEREG_PLMN_SEARCH状态 */
                NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                            EMM_SS_DEREG_PLMN_SEARCH,
                                            TI_NAS_EMM_STATE_NO_TIMER);

                /*向MMC发送本地LMM_MMC_DETACH_IND消息*/
                NAS_EMM_MmcSendDetIndLocal(MMC_LMM_L_LOCAL_DETACH_OTHERS);

                return NAS_LMM_MSG_HANDLED;
            }

        }

        /* 将状态转移至MS_RESUME + SS_RESUME_MMCORI_WAIT_SYS_INFO状态 */
        NAS_EMM_PUBU_FSMTranState(      EMM_MS_RESUME,
                                        EMM_SS_RESUME_MMCORI_WAIT_SYS_INFO_IND,
                                        TI_NAS_EMM_STATE_NO_TIMER);

        return NAS_LMM_MSG_HANDLED;
    }

    return NAS_LMM_MSG_DISCARD;
}


/*****************************************************************************
 Function Name   : NAS_EMM_NoImsiSuspendMsgMmcPlmnReq
 Description     : 若当前的 LTE为挂起态，则给ESM和ERABM通知激活，并改为LTE激活态
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.Hanlufeng 41410      2011-5-5  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_EMM_NoImsiSuspendMsgMmcPlmnReq( VOS_VOID )
{
    /* 若当前的 LTE为挂起态，则给ESM和ERABM通知激活，并改为LTE激活态 */
    if(     (NAS_EMM_PUBU_CHK_STAT_VALID(EMM_MS_DEREG,EMM_SS_DEREG_NO_IMSI))
         && (NAS_LMM_CUR_LTE_SUSPEND == NAS_EMM_GetCurLteState())
       )
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_NoImsiSuspendMsgMmcPlmnReq: LTE SUSPEND. ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_NoImsiSuspendMsgMmcPlmnReq_ENUM,LNAS_EMM_LTE_SUSPEND);

        /* 当前的 LTE为激活态 */
        NAS_EMM_GetCurLteState() = NAS_LMM_CUR_LTE_ACTIVE;

        /* 记录RESUME参数 */
        NAS_EMM_SaveMmcResumePara();

        /* 连接状态仍为空闲态 */


        /* 激活ESM, ERABM */
        NAS_EMM_SendEsmResumeInd();
        NAS_EMM_SendErabmResumeInd();
        /* 转移到EMM_SS_RESUME_MMCORI_WAIT_SYS_INFO_IND状态 */
        NAS_EMM_PUBU_FSMTranState(EMM_MS_RESUME,
                                  EMM_SS_RESUME_MMCORI_WAIT_SYS_INFO_IND,
                                  TI_NAS_EMM_STATE_NO_TIMER);
    }

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_MmcRsmGetSecuPara
 Description     : MMC恢复LTE时，获取GU的安全参数
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-5-11  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_MmcRsmGetSecuPara( VOS_VOID )
{
    MMC_LMM_PUB_INFO_STRU           stTin;
    MMC_LMM_RESULT_ID_ENUM_UINT32   ulRst;
    ulRst = NAS_EMM_GetGulPubInfo(MMC_LMM_TIN_TYPE, &stTin);
    if(MMC_LMM_FAIL == ulRst)
    {
        NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_MmcRsmGetSecuPara: NAS_EMM_GetGulPubInfo rst = ",
                                ulRst);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_MmcRsmGetSecuPara_ENUM,LNAS_FUNCTION_LABEL1,ulRst);
        return;
    }

    NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_MmcRsmGetSecuPara:  ulTinType = ",
                            stTin.u.ulTinType);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MmcRsmGetSecuPara_ENUM,LNAS_EMM_TIN_TYPE,
                            stTin.u.ulTinType);

    if(MMC_LMM_TIN_P_TMSI == stTin.u.ulTinType)
    {
        NAS_EMM_SecuResumeIdle();
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsSuspendSsWaitEndMsgLrrcResumeInd
 Description     : 收到 LRRC 解挂指示，类型应该为回退
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-4-25  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsSuspendSsWaitEndMsgLrrcResumeInd(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  )
{
    VOS_UINT32                          ulRst;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsSuspendSsWaitEndMsgLrrcResumeInd: enter. ");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsSuspendSsWaitEndMsgLrrcResumeInd_ENUM,LNAS_ENTRY);

    /* 停止定时器 */
    NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_SUSPEND_END_TIMER);

    /* 编码时发现回退的处理和从GU过来的RESUME完全相同 */
    ulRst = NAS_EMM_MsAnySsNoCellAvailMsgRrcRsumeInd(ulMsgId, pMsgStru);

    return ulRst;

}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsNoCellAvailMsgRrcSecuParaInd
 Description     : GU->L的切换时，LRRC要获取安全参数
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-4-25  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsNoCellAvailMsgRrcSecuParaInd(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru )
{
    LRRC_LMM_SECU_PARA_IND_STRU        *pstLrrcSecuParaInd = VOS_NULL_PTR;

    (VOS_VOID)ulMsgId;
    /* 获取 LRRC_LMM_SECU_PARA_IND消息*/
    pstLrrcSecuParaInd = (LRRC_LMM_SECU_PARA_IND_STRU *)pMsgStru;

    /* 如果LMM不处在挂起态，则报错*/
    if(NAS_LMM_CUR_LTE_SUSPEND != NAS_EMM_GetCurLteState())
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_MsRegSsNoCellAvailMsgRrcSecuParaInd:sta err.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsNoCellAvailMsgRrcSecuParaInd_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_HANDLED;
    }

    /* 调用 secu 模块的函数，产生 current mapped secu context并激活*/
    NAS_EMM_SecuRrcSecuParamIndHo(pstLrrcSecuParaInd->aucSecuPara);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsNoCellAvailMsgRrcRelInd
 Description     : 从G/U模向 L 模切换失败;
                   L->GU的切换完成，LMM进入 NO CELL状态，会收到REL IND信息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-5-31  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsNoCellAvailMsgRrcRelInd(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru )
{
    LRRC_LMM_REL_IND_STRU              *pLrrcRelInd = VOS_NULL_PTR;

    (VOS_VOID)ulMsgId;
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsRegSsNoCellAvailMsgRrcRelInd enter.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRegSsNoCellAvailMsgRrcRelInd_ENUM,LNAS_ENTRY);

    pLrrcRelInd = (LRRC_LMM_REL_IND_STRU *)pMsgStru;

    /* 检查释放原因值,如果不是切换失败，则应该是 L->GU的 HO或CCO 成功 */
    if(LRRC_LNAS_REL_CAUSE_GU2L_HO_ERR != pLrrcRelInd->enRelCause)
    {
        NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_MsRegSsNoCellAvailMsgRrcRelInd: enRelCause = , .",
                                pLrrcRelInd->enRelCause );
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsRegSsNoCellAvailMsgRrcRelInd_ENUM,LNAS_EMM_REL_CAUSE,
                                pLrrcRelInd->enRelCause );

        NAS_EMM_PUBU_LOG2_INFO("NAS_EMM_MsRegSsNoCellAvailMsgRrcRelInd: SuspendType = , ResumeType = .",
                                NAS_EMM_GetSuspendType(),
                                NAS_EMM_GetResumeType() );
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsRegSsNoCellAvailMsgRrcRelInd_ENUM,LNAS_EMM_SUSPEND_TYPE,
                                NAS_EMM_GetSuspendType());
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsRegSsNoCellAvailMsgRrcRelInd_ENUM,LNAS_EMM_RESUME_TYPE,NAS_EMM_GetResumeType());

        return NAS_LMM_MSG_HANDLED;
    }

    /* 释放原因值如果是切换失败，恢复安全上下文 */
    /* 调用 secu 模块函数，恢复安全上下文状态*/
    NAS_EMM_SecuRrcRelIndHoFail();

    return NAS_LMM_MSG_HANDLED;

}

/*****************************************************************************
 Function Name   : NAS_EMM_MsResumeSsRrcRsmWaitOtherMsgRsmRsp
 Description     : ESM和ERABM响应后，给MMC和RRC发恢复；
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-4-23  Draft Enact
    2.sunbing 49683             2012-5-29  删除无效的ESM/RABM回复处理，CM层不会 有失败回复
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsResumeSsRrcRsmWaitOtherMsgRsmRsp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  )
{
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsResumeSsRrcRsmWaitOtherMsgRsmRsp: enter. ");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsResumeSsRrcRsmWaitOtherMsgRsmRsp_ENUM,LNAS_ENTRY);

    NAS_EMM_GetUplayerCount()++;

    if(NAS_EMM_RESUME_UPLAYER_NUM_CM == NAS_EMM_GetUplayerCount())
    {

        /* 停定时器 */
        NAS_LMM_StopStateTimer(TI_NAS_EMM_RRCRSM_WAIT_OTHER_RESUME_RSP_TIMER);

        /* 清除此次挂起的上层响应记录，为下一次挂起过程做准备 */
        NAS_EMM_GetUplayerCount() = NAS_EMM_RESUME_UPLAYER_NUM_INITVALUE;

        /* 给MMC发送恢复 */
        NAS_EMM_SendMmcResumeInd();

        /* RESUME，不改变连接状态:
        REVERSE类型的，继续REVERSE前的连接状态；
        从GU过来的，重选、重定向: 持续IDLE，
                     切换: 等待LRRC的自动建链接消息，直接进入数传状态，或
                            收到REL_IND消息；
                     CCO: LNAS将发起建链，建链时改连接状态 */
        /*NAS_EMM_ResumeConnStateChng(); */

        /* 如果是HO_REVERSE/CCO_REVERSE，需要将安全状态恢复为激活态*/
        if((NAS_LMM_SYS_CHNG_TYPE_REVERSE_HO == NAS_EMM_GetResumeType())
         ||(NAS_LMM_SYS_CHNG_TYPE_REVERSE_CCO == NAS_EMM_GetResumeType()))
        {
            NAS_EMM_SecuHoOrCcoReverse();
        }

        /* 给LRRC响应 */
        NAS_EMM_SendLrcResumeRsp();

        /* 改状态: 无论回退，还是GU->L，都先进入等系统消息的状态，
        在等系统消息的状态下，在处理系统消息、REL消息、丢网消息时，
        再根据RESUME的类型、消息类型，决定回退后的状态。*/

        NAS_EMM_PUBU_FSMTranState(  EMM_MS_RESUME,
                                    EMM_SS_RESUME_RRCORI_WAIT_SYS_INFO_IND,
                                    TI_NAS_EMM_WAIT_SYS_INFO_IND_TIMER);

    }


    return NAS_LMM_MSG_HANDLED;

}


VOS_UINT32  NAS_EMM_MsResumeSsRrcRsmWaitOtherMsgWtOtherTimerExp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  )
{
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    /* 清除此次挂起的上层响应记录，为下一次挂起过程做准备 */
    NAS_EMM_GetUplayerCount() = NAS_EMM_RESUME_UPLAYER_NUM_INITVALUE;

    /* 复位处理*/
    NAS_EMM_SendMmcErrInd(NAS_EMM_REBOOT_TYPE_RRC_RESUME_ECM_FAIL);

    return NAS_LMM_MSG_HANDLED;

}

/*****************************************************************************
 Function Name   : NAS_EMM_PreProcSysWhenResumingReverse
 Description     : 对于挂起过程中回退的场景，收到RESUME后，继续收到SYS后，
                   要根据挂起前的状态，转换到两种NO CELL状态或NO IMSI状态。
                   该函数的调用点在预处理系统消息处；
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421 & Hanlufeng 41410  2011-4-25  Draft Enact
    2.zhengjunyan 00148421  2011-11-30  DTS20111112801762
*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcSysWhenResumingReverse(
                            const EMMC_EMM_SYS_INFO_IND_STRU *pstsysinfo )
{
    VOS_UINT32                          ulRslt = NAS_LMM_MSG_DISCARD;

    /* 停定时器 */
    NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_SYS_INFO_IND_TIMER);

    /* 判断RESUME类型如果不是REVERSE类型，则直接返回，继续进入状态机处理*/
    if((NAS_LMM_SYS_CHNG_TYPE_RSL   == NAS_EMM_GetResumeType())
     ||(NAS_LMM_SYS_CHNG_TYPE_HO    == NAS_EMM_GetResumeType())
     ||(NAS_LMM_SYS_CHNG_TYPE_CCO   == NAS_EMM_GetResumeType())
     ||(NAS_LMM_SYS_CHNG_TYPE_REDIR == NAS_EMM_GetResumeType()))
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PreProcSysWhenResumingReverse:NOT REVERSE. ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcSysWhenResumingReverse_ENUM,LNAS_FUNCTION_LABEL1);
        return  NAS_LMM_MSG_DISCARD;
    }

    /* 没有执行上面分支，则RESUME类型为REVERSE，满足以下条件需要释放连接:
       1)小区被禁
       2)不在IDLE态，
       3)不存在Emergency Bearer*/

    /* 然后区分不同的回退类型，进行不同处理*/
    switch(NAS_EMM_GetResumeType())
    {
        /* 检查ResumeType，如果是重选回退，处理如下:
           1)挂起前的状态为Dereg.Attach_Needed，状态恢复为Dereg.Attach_Needed，
             进入状态机继续处理；
           2)挂起前的状态为Reg.WtAccessGrantInd，根据BarProcedure做不同处理，
             不再进入状态；
           3)其他状态迁移到Dereg.No_Cell_Available;Reg.No_Cell_Available或者Dereg.No_Imsi,
             进入状态机继续处理
        */
        case    NAS_LMM_SYS_CHNG_TYPE_REVERSE_RSL:
                ulRslt = NAS_EMM_PreProcSysInfoReselReverse(pstsysinfo);
                break;

        /*对于挂起过程中非重选回退的场景，收到RESUME后，继续收到SYS后，要根据挂起前
        的状态，转换到回退到的状态，然后再进入状态机处理，则开始标准的LTE处理 */
        case    NAS_LMM_SYS_CHNG_TYPE_REVERSE_HO:
        case    NAS_LMM_SYS_CHNG_TYPE_REVERSE_CCO:
                ulRslt = NAS_EMM_PreProcSysInfoHoAndCcoReverse(pstsysinfo);
                break;
        case    NAS_LMM_SYS_CHNG_TYPE_REVERSE_REDIR:
                NAS_EMM_ReverseStateChng();
                ulRslt = NAS_LMM_MSG_DISCARD;
                break;

        default :
                NAS_EMM_PUBU_LOG_ERR("NAS_EMM_PreProcSysWhenResumingReverse:ResumeType err. ");
                TLPS_PRINT2LAYER_ERROR(NAS_EMM_PreProcSysWhenResumingReverse_ENUM,LNAS_ERROR);
                break;
    }

    return  ulRslt;
}



VOS_VOID  NAS_EMM_ReverseStateChng( VOS_VOID )
{
    NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_ReverseStateChng: CurState = ",
                            NAS_EMM_GetMsBefSuspend());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ReverseStateChng_ENUM,LNAS_FUNCTION_LABEL1,
                            NAS_EMM_GetMsBefSuspend());

    /* 根据记录的 staBeforeSuspend 迁移状态*/
    if(( EMM_MS_REG == NAS_EMM_GetMsBefSuspend())
        ||( EMM_MS_TAU_INIT == NAS_EMM_GetMsBefSuspend())
        ||( EMM_MS_SER_INIT == NAS_EMM_GetMsBefSuspend()))
    {
        NAS_EMM_PUBU_FSMTranState(      EMM_MS_REG,
                                        EMM_SS_REG_NO_CELL_AVAILABLE,
                                        TI_NAS_EMM_STATE_NO_TIMER);
    }
    else
    {
        if( EMM_SS_DEREG_NO_IMSI == NAS_EMM_GetSsBefSuspend())
        {
            NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                        EMM_SS_DEREG_NO_IMSI,
                                        TI_NAS_EMM_STATE_NO_TIMER);
        }
        else
        {
            NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                        EMM_SS_DEREG_NO_CELL_AVAILABLE,
                                        TI_NAS_EMM_STATE_NO_TIMER);
        }
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ReverseStateChngAsPlmnInd
 Description     : 由于PLMN IND消息，且恢复类型是回退类型时的状态转换
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010      2012-12-22  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ReverseStateChngAsPlmnInd( VOS_VOID )
{
    NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_ReverseStateChng: CurState = ",
                            NAS_EMM_GetMsBefSuspend());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ReverseStateChngAsPlmnInd_ENUM,LNAS_FUNCTION_LABEL1,
                            NAS_EMM_GetMsBefSuspend());

    /* 根据记录的 staBeforeSuspend 迁移状态*/
    if(( EMM_MS_REG == NAS_EMM_GetMsBefSuspend())
        ||( EMM_MS_TAU_INIT == NAS_EMM_GetMsBefSuspend())
        ||( EMM_MS_SER_INIT == NAS_EMM_GetMsBefSuspend()))
    {
        NAS_EMM_PUBU_FSMTranState(      EMM_MS_REG,
                                        EMM_SS_REG_PLMN_SEARCH,
                                        TI_NAS_EMM_STATE_NO_TIMER);
    }
    else
    {
        if( EMM_SS_DEREG_NO_IMSI == NAS_EMM_GetSsBefSuspend())
        {
            NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                        EMM_SS_DEREG_NO_IMSI,
                                        TI_NAS_EMM_STATE_NO_TIMER);
        }
        else
        {
            NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                        EMM_SS_DEREG_PLMN_SEARCH,
                                        TI_NAS_EMM_STATE_NO_TIMER);
        }
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_PreProcSysInfoReselReverse
 Description     : 重选回退收到LRRC_LMM_SYS_INFO_IND进入状态机前预处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-11-30  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcSysInfoReselReverse(
                                   const EMMC_EMM_SYS_INFO_IND_STRU *pstsysinfo )
{
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt = MMC_LMM_TAU_RSLT_BUTT;
    VOS_UINT32                          ulEmmStaBeforeSuspend = 0;
    VOS_UINT32                          ulRslt = NAS_LMM_MSG_HANDLED;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PreProcSysInfoReselReverse entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcSysInfoReselReverse_ENUM,LNAS_ENTRY);

    /* 获取挂起前的状态*/
    ulEmmStaBeforeSuspend = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_GetMsBefSuspend(),
                                                      NAS_EMM_GetSsBefSuspend());

    /* 根据挂起前的状态做不同处理*/
    switch(ulEmmStaBeforeSuspend)
    {
        /* 挂起前的状态为Dereg.Attach_Needed，根据小区是否被禁，给MMC上报ATTACH
           结果，不再进入状态机处理
         */
        case NAS_LMM_PUB_COMP_EMMSTATE( EMM_MS_DEREG,
                                        EMM_SS_DEREG_ATTACH_NEEDED):
            NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PreProcSysInfoReselReverse:Dereg.Attach_Needed");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcSysInfoReselReverse_ENUM,LNAS_EMM_ATTACH_NEEDED);
             /* 判断系统消息如果被禁，则迁移到限制服务*/

            if((EMMC_EMM_NO_FORBIDDEN != pstsysinfo->ulForbiddenInfo)
                || (EMMC_EMM_CELL_STATUS_ANYCELL == pstsysinfo->ulCellStatus))
            {
                /* 状态迁移: Reg.Limite_Service*/
                NAS_EMM_PUBU_FSMTranState(      EMM_MS_DEREG,
                                                EMM_SS_DEREG_LIMITED_SERVICE,
                                                TI_NAS_EMM_STATE_NO_TIMER);

                NAS_EMM_SetAttType();

                /*向MMC发送ATTACH结果*/
                NAS_EMM_AppSendAttRsltForb(pstsysinfo->ulForbiddenInfo);
            }
            else
            {
                /*EMM当前状态迁移到DEREG.ATTACH_NEEDED*/
                NAS_EMM_PUBU_FSMTranState(      EMM_MS_DEREG,
                                                EMM_SS_DEREG_ATTACH_NEEDED,
                                                TI_NAS_EMM_STATE_NO_TIMER);
                /*向MMC发送ATTACH结果*/
                NAS_EMM_AppSendAttRstDefaultReqType(MMC_LMM_ATT_RSLT_ACCESS_BAR);

            }
            ulRslt = NAS_LMM_MSG_HANDLED;
            break;

        /* 挂起前的状态为Reg.WtAccessGrantInd,处理完不再进入状态机  */
        case NAS_LMM_PUB_COMP_EMMSTATE( EMM_MS_REG,
                                        EMM_SS_REG_WAIT_ACCESS_GRANT_IND):
            NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PreProcSysInfoReselReverse:Reg.WtAccessGrantInd");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcSysInfoReselReverse_ENUM,LNAS_FUNCTION_LABEL1);

            /* 判断系统消息如果被禁，则迁移到限制服务*/
            if((EMMC_EMM_NO_FORBIDDEN != pstsysinfo->ulForbiddenInfo)
                 || (EMMC_EMM_CELL_STATUS_ANYCELL == pstsysinfo->ulCellStatus))
            {
                NAS_EMM_SetTauTypeNoProcedure();

                /* 清空Bar信息*/
                NAS_EMM_ClearBarResouce();

                /* 状态迁移: Reg.Limite_Service*/
                NAS_EMM_PUBU_FSMTranState(      EMM_MS_REG,
                                                EMM_SS_REG_LIMITED_SERVICE,
                                                TI_NAS_EMM_STATE_NO_TIMER);

                /*向MMC发送LMM_MMC_TAU_RESULT_IND消息*/
                NAS_EMM_MmcSendTauActionResultIndForbType((VOS_VOID*)&pstsysinfo->ulForbiddenInfo);

            }
            else
            {
                /* 系统消息不被禁，调用REG态下解Bar的公共处理*/
                NAS_EMM_RegBarCommProc();

                /* 如果经过公共处理，EMM当前的状态仍然处于Resume.RrcOriWtSysInfo,
                   则说明没有触发任何流程，需要给MMC上报结果，并将状态迁移到
                   Reg.WtAccessGrantInd状态；反之，清空BarProcedure
                */
                if((EMM_MS_RESUME                           == NAS_LMM_GetEmmCurFsmMS())
                 &&(EMM_SS_RESUME_RRCORI_WAIT_SYS_INFO_IND  == NAS_LMM_GetEmmCurFsmSS()))
                {
                    NAS_EMM_SetTauTypeNoProcedure();

                    NAS_EMM_PUBU_FSMTranState(  EMM_MS_REG,
                                                EMM_SS_REG_WAIT_ACCESS_GRANT_IND,
                                                TI_NAS_EMM_STATE_NO_TIMER);

                    ulTauRslt = MMC_LMM_TAU_RSLT_ACCESS_BARED;
                    NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);


                }
            }

            ulRslt = NAS_LMM_MSG_HANDLED;
            break;

        /* 其他状态,迁移状态后，继续进入状态机处理*/
        default:
            NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PreProcSysInfoReselReverse:Others.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcSysInfoReselReverse_ENUM,LNAS_FUNCTION_LABEL2);
            NAS_EMM_ReverseStateChng();
            ulRslt = NAS_LMM_MSG_DISCARD;
            break;
    }

    return ulRslt;
}

/*****************************************************************************
 Function Name   : NAS_EMM_PreProcSysInfoHoAndCcoReverse
 Description     : 重选回退收到LRRC_LMM_SYS_INFO_IND进入状态机前预处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2012-5-30  Draft Enact
    2.lihong00150010      2012-12-20 Modify:Emergency

*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcSysInfoHoAndCcoReverse(
                                   const EMMC_EMM_SYS_INFO_IND_STRU *pstsysinfo )
{
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PreProcSysInfoHoAndCcoReverse is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcSysInfoHoAndCcoReverse_ENUM,LNAS_ENTRY);
    if(((EMMC_EMM_NO_FORBIDDEN  != pstsysinfo->ulForbiddenInfo)
        || (EMMC_EMM_CELL_STATUS_ANYCELL == pstsysinfo->ulCellStatus))
        &&(NAS_EMM_CONN_IDLE   != NAS_EMM_GetConnState())
        &&(NAS_LMM_REG_STATUS_NORM_REGED == NAS_LMM_GetEmmInfoRegStatus()))
    {
        NAS_EMM_PUBU_FSMTranState(      EMM_MS_REG,
                            EMM_SS_REG_LIMITED_SERVICE,
                            TI_NAS_EMM_STATE_NO_TIMER);

        NAS_EMM_SetTauTypeNoProcedure();

        /*向MMC发送LMM_MMC_TAU_RESULT_IND消息*/
        NAS_EMM_MmcSendTauActionResultIndForbType((VOS_VOID*)&pstsysinfo->ulForbiddenInfo);


        /*发送RRC_MM_REL_REQ*/
        NAS_EMM_RelReq(      NAS_LMM_NOT_BARRED);

        return NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_PUBU_FSMTranState(      EMM_MS_REG,
                        EMM_SS_REG_NO_CELL_AVAILABLE,
                        TI_NAS_EMM_STATE_NO_TIMER);
    return NAS_LMM_MSG_DISCARD;

}


VOS_VOID  NAS_EMM_GU2LResumeStateChng(VOS_VOID)
{
    NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_GU2LResumeStateChng: CurState = ",
                            NAS_EMM_GetMsBefResume());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_GU2LResumeStateChng_ENUM,LNAS_FUNCTION_LABEL1,
                            NAS_EMM_GetMsBefResume());

    /* 根据记录的 staBeforeSuspend 迁移状态*/
    if( EMM_MS_REG == NAS_EMM_GetMsBefResume())
    {
        NAS_EMM_PUBU_FSMTranState(      EMM_MS_REG,
                                        EMM_SS_REG_NO_CELL_AVAILABLE,
                                        TI_NAS_EMM_STATE_NO_TIMER);
    }
    else
    {
        if( EMM_SS_DEREG_NO_IMSI == NAS_EMM_GetSsBefResume())
        {
            NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                        EMM_SS_DEREG_NO_IMSI,
                                        TI_NAS_EMM_STATE_NO_TIMER);
        }
        else
        {
            NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                        EMM_SS_DEREG_NO_CELL_AVAILABLE,
                                        TI_NAS_EMM_STATE_NO_TIMER);
        }
    }

    return;
}


VOS_VOID  NAS_EMM_GU2LResumeStateChngAsPlmnInd(VOS_VOID)
{
    NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_GU2LResumeStateChngAsPlmnInd: CurState = ",
                            NAS_EMM_GetMsBefResume());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_GU2LResumeStateChngAsPlmnInd_ENUM,LNAS_FUNCTION_LABEL1,
                            NAS_EMM_GetMsBefResume());

    /* 根据记录的 staBeforeSuspend 迁移状态*/
    if( EMM_MS_REG == NAS_EMM_GetMsBefResume())
    {
        NAS_EMM_PUBU_FSMTranState(      EMM_MS_REG,
                                        EMM_SS_REG_PLMN_SEARCH,
                                        TI_NAS_EMM_STATE_NO_TIMER);
    }
    else
    {
        if( EMM_SS_DEREG_NO_IMSI == NAS_EMM_GetSsBefResume())
        {
            NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                        EMM_SS_DEREG_NO_IMSI,
                                        TI_NAS_EMM_STATE_NO_TIMER);
        }
        else
        {
            NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                        EMM_SS_DEREG_PLMN_SEARCH,
                                        TI_NAS_EMM_STATE_NO_TIMER);
        }
    }

    return;
}

VOS_VOID  NAS_EMM_RegForbidSysInfoProc( EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32  ulForbiddenInfo)
{
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_RegForbidSysInfoProc is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_RegForbidSysInfoProc_ENUM,LNAS_ENTRY);

    if (NAS_RELEASE_CTRL)
    {
        /* 判断承载上下文是否激活，如果未激活，则本地DETACH，转入DEREG+LIMITED_SERVICE状态；
        如果激活，则保持原有处理 */
        if(NAS_MML_PS_BEARER_STATE_INACTIVE == NAS_EMM_IsEpsBearStatusAct())
        {
            NAS_EMM_LocalDetachProc();
            #if (FEATURE_PTM == FEATURE_ON)
            NAS_EMM_LocalDetachErrRecord(EMM_ERR_LOG_LOCAL_DETACH_TYPE_GU2L_NO_EPS_BEAR);
            #endif
            NAS_LMM_DeregReleaseResource();

            NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                        EMM_SS_DEREG_LIMITED_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

            /*向MMC发送本地LMM_MMC_DETACH_IND消息*/
            NAS_EMM_MmcSendDetIndLocal(MMC_LMM_L_LOCAL_DETACH_OTHERS);

            NAS_EMM_AppSendAttRsltForb(ulForbiddenInfo);

        }
        else
        {
            /* 注册态，进入REG.LIMITED； */
            NAS_EMM_SetTauTypeNoProcedure();

            NAS_EMM_PUBU_FSMTranState(  EMM_MS_REG,
                                        EMM_SS_REG_LIMITED_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);
            /*向MMC发送LMM_MMC_TAU_RESULT_IND消息*/
            NAS_EMM_MmcSendTauActionResultIndForbType((VOS_VOID*)&ulForbiddenInfo);
        }
    }
    else
    {
        /* 注册态，进入REG.LIMITED； */
        NAS_EMM_SetTauTypeNoProcedure();

        NAS_EMM_PUBU_FSMTranState(  EMM_MS_REG,
                                    EMM_SS_REG_LIMITED_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);
        /*向MMC发送LMM_MMC_TAU_RESULT_IND消息*/
        NAS_EMM_MmcSendTauActionResultIndForbType((VOS_VOID*)&ulForbiddenInfo);
    }


    return;
}


VOS_VOID  NAS_EMM_GU2LNoEpsBearProc(VOS_VOID)
{
    VOS_UINT32                          ulRst;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_GU2LNoEpsBearProc is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_GU2LNoEpsBearProc_ENUM,LNAS_ENTRY);

    NAS_EMM_LocalDetachProc();
    #if (FEATURE_PTM == FEATURE_ON)
    NAS_EMM_LocalDetachErrRecord(EMM_ERR_LOG_LOCAL_DETACH_TYPE_GU2L_NO_EPS_BEAR);
    #endif

    NAS_LMM_DeregReleaseResource();

    NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                EMM_SS_DEREG_NORMAL_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /*向MMC发送本地LMM_MMC_DETACH_IND消息*/
    NAS_EMM_MmcSendDetIndLocal(MMC_LMM_L_LOCAL_DETACH_OTHERS);

    /* 重新发起ATTACH */
    ulRst = NAS_EMM_SendIntraAttachReq();
    if (NAS_EMM_SUCC != ulRst)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_GU2LNoEpsBearProc:  send INTRA ATTACH REQ ERR !");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_GU2LNoEpsBearProc_ENUM,LNAS_EMM_SEND_ATT_REQ_ERR);
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgMmcPlmnInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-6-15  Draft Enact
    2.lihong 00150010     2012-12-22 Modify:DTS2012121306127，系统消息机制变更

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgMmcPlmnInd
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    if (NAS_EMM_NULL_PTR == pMsgStru)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgMmcPlmnInd: \
                            Input para invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgMmcPlmnInd_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_SYS_INFO_IND_TIMER);

    /*清除BAR标识*/
    NAS_EMM_ClearBarResouce();


    NAS_EMM_PUBU_LOG2_NORM("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgMmcPlmnInd:\
                            NAS_EMM_GetResumeType()= ,NAS_EMM_GetMsBefSuspend()",
                            NAS_EMM_GetResumeType(),NAS_EMM_GetMsBefSuspend());
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgMmcPlmnInd_ENUM,LNAS_FUNCTION_LABEL1,
                            NAS_EMM_GetResumeType(),
                            NAS_EMM_GetMsBefSuspend());

    /* GU到L的重选、重定向时，MMC收到LMM的RESUME IND就会下发搜网请求 */
    if (NAS_LMM_SYS_CHNG_TYPE_RSL == NAS_EMM_GetResumeType())
    {
        if (EMM_MS_REG == NAS_EMM_GetMsBefResume())
        {
            NAS_EMM_RrcResumeReselTypeSetTauStartCause();
        }
        /* 读取GU的UMTS安全上下文，生成LTE的安全参数，并设置安全状态*/
        NAS_EMM_SecuResumeIdle();
        NAS_EMM_GU2LResumeStateChngAsPlmnInd();

        return NAS_LMM_MSG_HANDLED;
    }

    if (NAS_LMM_SYS_CHNG_TYPE_REDIR == NAS_EMM_GetResumeType())
    {
        if (EMM_MS_REG == NAS_EMM_GetMsBefResume())
        {
            NAS_EMM_RrcResumeRedirTypeSetTauStartCause();
        }
        /* 读取GU的UMTS安全上下文，生成LTE的安全参数，并设置安全状态*/
        NAS_EMM_SecuResumeIdle();
        NAS_EMM_GU2LResumeStateChngAsPlmnInd();

        return NAS_LMM_MSG_HANDLED;
    }

    /* L2GU回退过程中可以收到MMC的搜网请求消息，CCO/HO的回退过程中为连接态，
       也不会收到MMC的搜网请求消息 */
    if((NAS_LMM_SYS_CHNG_TYPE_REVERSE_RSL == NAS_EMM_GetResumeType()) ||
        (NAS_LMM_SYS_CHNG_TYPE_REVERSE_REDIR == NAS_EMM_GetResumeType()))
    {
        NAS_EMM_ReverseStateChngAsPlmnInd();
    }

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgMmcDetachReq
 Description     : RRC触发解挂等系统消息过程中收到MMC的DETACH
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151      2013-12-30  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgMmcDetachReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    /* 通知ESM执行了本地DETACH */
    NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);

    /* 自研CL版本，PS DETACH通知ESM删除所有EHRPD相关承载记录 */
    NAS_EMM_SndEsmClearAllClBearerNotify();

    /* 给MMC回DETACH成功 */
    NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* 无卡状态下如果是紧急注册中有可能要到L */
    if (NAS_LMM_SIM_STATUS_UNAVAILABLE == NAS_LMM_GetSimState())
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgMmcDetachReq: NO_IMSI ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgMmcDetachReq_ENUM,LNAS_EMM_NO_IMSI);
        NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                               EMM_SS_DEREG_NO_IMSI,
                               TI_NAS_EMM_STATE_NO_TIMER);

        NAS_LMM_DeregReleaseResource();

        /* 除了CCO的场景，全部都给RRC发释放，CCO只能靠后续不发起建链让GAS等CNF超时回退 */
        if(LRRC_LMM_SYS_CHNG_TYPE_CCO != NAS_EMM_GetResumeType())
        {
            NAS_EMM_SndRrcRelReq(NAS_LMM_NOT_BARRED);
            NAS_EMM_SetConnState(NAS_EMM_CONN_RELEASING);
        }

        return  NAS_LMM_MSG_HANDLED;

    }

    /* 有卡 */
    switch(NAS_EMM_GetResumeType())
    {
                /* 重选、重定向、重选回退、重定向回退和CCO的场景，本地DETACH等系统消息 */
        case    LRRC_LMM_SYS_CHNG_TYPE_RESEL:
        case    LRRC_LMM_SYS_CHNG_TYPE_REDIR:
        case    LRRC_LMM_SYS_CHNG_TYPE_CCO:
        case    LRRC_LMM_SYS_CHNG_TYPE_RESEL_REVERSE:
        case    LRRC_LMM_SYS_CHNG_TYPE_REDIR_REVERSE:

                NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                                       EMM_SS_DEREG_NO_CELL_AVAILABLE,
                                       TI_NAS_EMM_STATE_NO_TIMER);

                /* 本地DETACH释放资源:动态内存、赋初值 */
                NAS_LMM_DeregReleaseResource();
                break;

                /* 切换、切换回退和CCO回退的场景，均作本地DETACH后给RRC发释放 */
        case    LRRC_LMM_SYS_CHNG_TYPE_HO:
        case    LRRC_LMM_SYS_CHNG_TYPE_HO_REVERSE:
        case    LRRC_LMM_SYS_CHNG_TYPE_CCO_REVERSE:

                NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                                       EMM_SS_DEREG_PLMN_SEARCH,
                                       TI_NAS_EMM_STATE_NO_TIMER);

                /* 本地DETACH释放资源:动态内存、赋初值 */
                NAS_LMM_DeregReleaseResource();

                /* 释放RRC，修改连接状态为释放过程中 */
                NAS_EMM_SndRrcRelReq(NAS_LMM_NOT_BARRED);
                NAS_EMM_SetConnState(NAS_EMM_CONN_WAIT_SYS_INFO);
                break;

        default:
                NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgMmcDetachReq: Invalid resume type = ",
                                        NAS_EMM_GetResumeType());
                TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgMmcDetachReq_ENUM,LNAS_EMM_RESUME_TYPE,
                                        NAS_EMM_GetResumeType());
                break;
    }

    return  NAS_LMM_MSG_HANDLED;

}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcSuitSysWhenRrcOriRsmGu2LReg
 Description     : RRC触发GU到L的异系统变换，处于REG态下收到正常系统消息的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2013-3-25  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_ProcSuitSysWhenRrcOriRsmGu2LReg(VOS_VOID)
{

    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_ProcSuitSysWhenRrcOriRsmGu2LReg is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSuitSysWhenRrcOriRsmGu2LReg_ENUM,LNAS_ENTRY);
    if (NAS_RELEASE_CTRL)
    {
        if(NAS_MML_PS_BEARER_STATE_INACTIVE == NAS_EMM_IsEpsBearStatusAct())
        {
            NAS_EMM_GU2LNoEpsBearProc();
        }
        else
        {
            NAS_EMM_ProcSuitSysWhenRsmGu2LReg();
        }
    }
    else
    {
        NAS_EMM_ProcSuitSysWhenRsmGu2LReg();
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgAnyCellOrForbidden
 Description     : 在回复等待RRC的系统消息状态收到ANYCELL或者被禁的系统消息
 Input           : const EMMC_EMM_SYS_INFO_IND_STRU   *pstsysinfo
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong 00150010      2014-01-23  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgAnyCellOrForbidden
(
    const EMMC_EMM_SYS_INFO_IND_STRU   *pstsysinfo
)
{
    /* 从异系统变换过来时，可能是ANY CELL驻留时向LTE的重选 */
    NAS_EMM_PUBU_LOG_WARN("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgAnyCellOrForbidden: Forbidden ");
    TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgAnyCellOrForbidden_ENUM,LNAS_EMM_FORBIDDEN);

    /* 读取GU的UMTS安全上下文，生成LTE的安全参数，并设置安全状态*/
    NAS_EMM_SecuResumeIdle();

    if(EMM_MS_REG == NAS_EMM_GetMsBefResume())
    {   /* 注册态，进入REG.LIMITED； */
        if (NAS_LMM_REG_STATUS_NORM_REGED == NAS_LMM_GetEmmInfoRegStatus())
        {
            NAS_EMM_RegForbidSysInfoProc(pstsysinfo->ulForbiddenInfo);
            if (MMC_LMM_CONN_IDLE != NAS_EMM_GetConnState())
            {
                NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgSysInfoInd:Limited Srv Connected");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgAnyCellOrForbidden_ENUM,LNAS_FUNCTION_LABEL1);

                /*发送NAS_EMM_REL_REQ*/
                NAS_EMM_RelReq(         NAS_LMM_NOT_BARRED);
            }
        }
        else
        {
            NAS_EMM_ProcSuitSysWhenRsmGu2LReg();
        }
    }
    else
    {   /* 未注册: 包括两种状态: DEREG. NO_CELL和NO IMSI；可能进入DEREG.LIMITED */
        NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                    EMM_SS_DEREG_LIMITED_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

        NAS_EMM_SetAttType();

        /*向MMC发送LMM_MMC_ATTACH_CNF或LMM_MMC_ATTACH_IND消息*/
        NAS_EMM_AppSendAttRsltForb(pstsysinfo->ulForbiddenInfo);
    }
}


/*****************************************************************************
 Function Name   : NAS_EMM_IsHoIgnoreForbSysInfo
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    lifuxin 00253982 2015-4-25  初稿
*****************************************************************************/
VOS_UINT32  NAS_EMM_IsHoIgnoreForbSysInfo(
                     EMMC_EMM_SYS_INFO_IND_STRU         *pstsysinfo)
{
    VOS_UINT32                           ulIsHplmnFlag = NAS_EMM_NO;

    ulIsHplmnFlag = NAS_LMM_LteNoSubscribeIsRegisteredInHplmn(&(pstsysinfo->stPlmnId));

    /*DCM定制需求*/
    if((NAS_EMM_HO_IGNORE_FORBID_TA_FLAG_VALID == g_ulHoIgnoreForbidTaFlag)
            &&(NAS_LMM_SYS_CHNG_TYPE_HO == NAS_EMM_GetResumeType()))
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_IsHoIgnoreForbSysInfo:DCM");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsHoIgnoreForbSysInfo_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_YES;
    }

    /*4G未开户HPLMN场景*/
    if((PS_SUCC != LPS_OM_IsTestMode())
                && (PS_TRUE == NAS_EMM_GetLteNoSubscribeNvConfigHplmnSwitch())
                && (NAS_EMM_YES == ulIsHplmnFlag))
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_IsHoIgnoreForbSysInfo:Hplmn");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsHoIgnoreForbSysInfo_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_YES;
    }

    /*4G未开户VHPLMN*/
    if((PS_SUCC != LPS_OM_IsTestMode())
                && (PS_TRUE == NAS_EMM_GetLteNoSubscribeNvConfigVplmnSwitch())
                && (NAS_EMM_YES != ulIsHplmnFlag))
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_IsHoIgnoreForbSysInfo:Vplmn");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsHoIgnoreForbSysInfo_ENUM,LNAS_FUNCTION_LABEL3);
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgSysInfoInd
 Description     : 状态机中，此状态下收到系统消息，一定是从GU变换过来的过程。
                   回退类型的处理，在预处理中就回退到 NO CELL状态去了，不会
                   进入这个状态；
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.Hanlufeng 41410      2011-4-25  Draft Enact
    2.sunjitan 00193151    2012-02-02 Modify for UE radio capability
    3.sunjitan 00193151    2013-01-22 DCM对于GU到L的切换要求不考虑被禁TA的修改
    4.lihong 00150010      2012-12-19 Modify:Emergency
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgSysInfoInd(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  )
{
    EMMC_EMM_SYS_INFO_IND_STRU         *pstsysinfo;
    EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32  ulForbiddenInfo = EMMC_EMM_NO_FORBIDDEN;

    (VOS_VOID)ulMsgId;
    NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgSysInfoInd: ResumeType = ",
                        NAS_EMM_GetResumeType());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgSysInfoInd_ENUM,LNAS_EMM_RESUME_TYPE,
                        NAS_EMM_GetResumeType());

    pstsysinfo = (EMMC_EMM_SYS_INFO_IND_STRU *)pMsgStru;

    /* 停定时器 */
    NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_SYS_INFO_IND_TIMER);

    if(((NAS_EMM_LAU_OR_COMBINED_RAU_HAPPENED == NAS_LMM_GetEmmInfoLauOrComRauFlag())
        ||(NAS_EMM_SRVCC_HAPPENED == NAS_LMM_GetEmmInfoSrvccFlag()))
        && (NAS_EMM_YES == NAS_EMM_IsCsPsUeMode()))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgSysInfoInd:LAU OR COMBINED RAU");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgSysInfoInd_ENUM,LNAS_EMM_LAU_OR_COMB_RAU);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    if (NAS_EMM_YES == NAS_EMM_IsEmcCsfbHappenedAndLaiChangWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgSysInfoInd:EMC CSFB,LAI CHANG ");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgSysInfoInd_ENUM,LNAS_EMM_EMC_CSFB_LAI_CHG);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    /* 若RESUME之前是 NO IMSI状态，过来后还要继续NO IMSI状态 */
    if(EMM_SS_DEREG_NO_IMSI == NAS_EMM_GetSsBefResume())
    {
        /*向MMC发送注册结果 消息*/

        NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                    EMM_SS_DEREG_NO_IMSI,
                                    TI_NAS_EMM_STATE_NO_TIMER);

        /*向MMC发送ATTACH失败*/
        NAS_EMM_AppSendAttRstDefaultReqType(MMC_LMM_ATT_RSLT_FAILURE);

        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgSysInfoInd: NO_IMSI ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgSysInfoInd_ENUM,LNAS_EMM_NO_IMSI);
        return  NAS_LMM_MSG_HANDLED;
    }

    ulForbiddenInfo = pstsysinfo->ulForbiddenInfo;
    /* 如果DCM定制需求关于切换被禁TA的标识有效，则GU到L的切换不考虑被禁TA FOR Roaming */
    /* 如果是4G未开户遇到切换场景，则也不考虑TA被禁*/
    if(NAS_EMM_YES == NAS_EMM_IsHoIgnoreForbSysInfo(pstsysinfo))
    {
        NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgSysInfoInd:forbiddenInfo = ",
                               pstsysinfo->ulForbiddenInfo);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgSysInfoInd_ENUM,LNAS_EMM_FORB_INFO,
                               pstsysinfo->ulForbiddenInfo);
        if(EMMC_EMM_FORBIDDEN_TA_FOR_ROAMING == pstsysinfo->ulForbiddenInfo)
        {
            ulForbiddenInfo = EMMC_EMM_NO_FORBIDDEN;
        }
    }

    /*GU2L后LRRC能否驻留属于"forbidden tracking areas for regional provision of service"列表
    中的TA小区需讨论确定，暂时按照会驻留实现，SYS判断禁止注册 */
    if((EMMC_EMM_NO_FORBIDDEN != ulForbiddenInfo)
        || (EMMC_EMM_CELL_STATUS_ANYCELL == pstsysinfo->ulCellStatus))
    {
        NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgAnyCellOrForbidden(pstsysinfo);
    }
    else
    {   /* 如果SYS判断能够注册, 根据RESUME前的状态, 判断是发起ATTACH，还是TAU */

        if(EMM_MS_REG == NAS_EMM_GetMsBefResume())
        {
            /* 判断承载上下文是否激活，如果未激活，则本地DETACH，转入DEREG+NORMAL_SERVICE状态；
            发起ATTACH流程；
            如果激活，则保持原有处理 */
            NAS_EMM_ProcSuitSysWhenRrcOriRsmGu2LReg();
        }
        else
        {
            /*未注册态: 改状态为DEREG.NORMAL_SERVICE*/
            NAS_EMM_ProcSuitSysWhenRrcOriRsmGu2LDeReg();
        }
    }

    return NAS_LMM_MSG_HANDLED;
}



/*****************************************************************************
 Function Name   : NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgAreaLostInd
 Description     : RESUME+RRCORI_WAIT_SYS_INFO状态收到丢网消息处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-4-25  Draft Enact
    2.leili 00132387            2011-11-30 modify
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgAreaLostInd
(
    VOS_UINT32      ulMsgId,
    VOS_VOID        *pMsgStru
)
{
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;


    NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgAreaLostInd:NAS_EMM_GetResumeType() = ",
                            NAS_EMM_GetResumeType());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgAreaLostInd_ENUM,LNAS_EMM_RESUME_TYPE,
                            NAS_EMM_GetResumeType());

    /*清除BAR标识*/
    NAS_EMM_ClearBarResouce();

    /* 关闭当前EMM的除Del Forb Ta Proid之外的状态定时器, Del Forb Ta Proid只能在关机时停止*/
    NAS_LMM_StopAllStateTimerExceptDelForbTaProidTimer();

    switch(NAS_EMM_GetResumeType())
    {
        case    NAS_LMM_SYS_CHNG_TYPE_HO:
                if(((NAS_EMM_LAU_OR_COMBINED_RAU_HAPPENED == NAS_LMM_GetEmmInfoLauOrComRauFlag())
                    || (NAS_EMM_SRVCC_HAPPENED == NAS_LMM_GetEmmInfoSrvccFlag()))
                    && (NAS_EMM_YES == NAS_EMM_IsCsPsUeMode()))
                {
                    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgAreaLostInd:LAU OR COMBINED RAU");
                    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgAreaLostInd_ENUM,LNAS_EMM_LAU_OR_COMB_RAU);
                    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
                }

                if (NAS_EMM_YES == NAS_EMM_IsEmcCsfbHappenedAndLaiChangWithCsPsUeMode())
                {
                    NAS_EMM_TAU_LOG_WARN("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgAreaLostInd:EMC CSFB,LAI CHANG ");
                    TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgAreaLostInd_ENUM,LNAS_EMM_EMC_CSFB_LAI_CHG);
                    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
                }

                if (NAS_RELEASE_R11)
                {
                    NAS_EMM_IsG2LGmmSuspendAndIsrAct();
                }
                NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
                NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);
                NAS_EMM_PUBU_FSMTranState(  EMM_MS_REG,
                                            EMM_SS_REG_NO_CELL_AVAILABLE,
                                            TI_NAS_EMM_STATE_NO_TIMER);

                break;
        case    NAS_LMM_SYS_CHNG_TYPE_RSL:
        case    NAS_LMM_SYS_CHNG_TYPE_CCO:
        case    NAS_LMM_SYS_CHNG_TYPE_REDIR:
                /*CCO/REDIR/RESEL流程在此状态不会收到丢网消息*/
                break;

        case    NAS_LMM_SYS_CHNG_TYPE_REVERSE_RSL:
        case    NAS_LMM_SYS_CHNG_TYPE_REVERSE_HO:
        case    NAS_LMM_SYS_CHNG_TYPE_REVERSE_CCO:
        case    NAS_LMM_SYS_CHNG_TYPE_REVERSE_REDIR:
                NAS_EMM_ReverseStateChng();
                break;
        default:
                NAS_EMM_PUBU_LOG_WARN("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgAreaLostInd:Resume type is err!");
                TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgAreaLostInd_ENUM,LNAS_ERROR);
                break;

    }
    return NAS_LMM_MSG_HANDLED;
}
/* leixiantiao 00258641 重构代码降低圈复杂度 2014-7-30 begin */

VOS_UINT32 NAS_EMM_IsLauOrComRauOrSrvccHappenedWithCsPsUeMode(VOS_VOID)
{
    if(((NAS_EMM_LAU_OR_COMBINED_RAU_HAPPENED == NAS_LMM_GetEmmInfoLauOrComRauFlag())
        || (NAS_EMM_SRVCC_HAPPENED == NAS_LMM_GetEmmInfoSrvccFlag()))
        && (NAS_EMM_YES == NAS_EMM_IsCsPsUeMode()))
    {
        return NAS_EMM_YES;
    }
    return NAS_EMM_NO;
}
/*****************************************************************************
 Function Name   : NAS_EMM_IsG2LAndGmmSuspendMmcOri
 Description     : DTS2015122100087去掉方向判断
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.yanglei 00307272      2015-12-23 Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_EMM_IsG2LAndGmmSuspendWithCsPsUeMode(VOS_VOID)
{
    if ((GMM_LMM_GPRS_SUSPENSION == NAS_LMM_GetEmmInfoPsState())
        && (NAS_EMM_YES == NAS_EMM_IsCsPsUeMode()))
    {
        return NAS_EMM_YES;
    }
    return NAS_EMM_NO;
}

/* leixiantiao 00258641 重构代码降低圈复杂度 2014-7-30 edn */


VOS_UINT32 NAS_EMM_IsEmcCsfbHappenedAndLaiChangWithCsPsUeMode(VOS_VOID)
{
    if ((NAS_EMM_LAU_OR_COMBINED_RAU_NOT_HAPPENED == NAS_LMM_GetEmmInfoLauOrComRauFlag())
        && (VOS_TRUE == NAS_LMM_GetEmmInfoCsEmcConneExitFlag())
        && (VOS_TRUE == NAS_LMM_GetEmmInfoLaiChangeFlag())
        && (NAS_EMM_YES == NAS_EMM_IsCsPsUeMode()))
    {
        return NAS_EMM_YES;
    }
    return NAS_EMM_NO;
}


VOS_UINT32 NAS_EMM_IsG2LIsrActAndP4ConditionSatisfied(NAS_LMM_RSM_SYS_CHNG_DIR_ENUM_UINT32    enRsmDir )
{
    if ((NAS_LMM_RSM_SYS_CHNG_DIR_G2L == enRsmDir)
        && (NAS_EMM_YES == NAS_EMM_IsAnnexP4ConditionSatisfied())
        && (MMC_LMM_TIN_RAT_RELATED_TMSI == NAS_EMM_GetTinType()))
    {
        return NAS_EMM_YES;
    }
    return NAS_EMM_NO;
}




VOS_UINT32 NAS_EMM_IsPmmConnectAndIsrAct
(
    VOS_VOID
)
{
    if ((GMM_LMM_PACKET_MM_STATE_PMM_CONNECTED == NAS_LMM_GetEmmInfoUConnState())
        && (MMC_LMM_TIN_RAT_RELATED_TMSI == NAS_EMM_GetTinType()))
    {
        return NAS_EMM_YES;
    }
    return NAS_EMM_NO;
}

VOS_UINT32 NAS_EMM_IsG2LAndGprsStateReady
(
    NAS_LMM_RSM_SYS_CHNG_DIR_ENUM_UINT32    enRsmDir
)
{
    if ((NAS_LMM_RSM_SYS_CHNG_DIR_G2L == enRsmDir)
        && (GMM_LMM_GPRS_MM_STATE_READY == NAS_LMM_GetEmmInfoGConnState()))
    {
        return NAS_EMM_YES;
    }
    return NAS_EMM_NO;
}

VOS_UINT32 NAS_EMM_IsW2LAndPmmConnect
(
    NAS_LMM_RSM_SYS_CHNG_DIR_ENUM_UINT32    enRsmDir
)
{
    if ((NAS_LMM_RSM_SYS_CHNG_DIR_W2L == enRsmDir)
        && (GMM_LMM_PACKET_MM_STATE_PMM_CONNECTED == NAS_LMM_GetEmmInfoUConnState()))
    {
        return NAS_EMM_YES;
    }
    return NAS_EMM_NO;
}


VOS_VOID NAS_EMM_SetTinToPtmsiWhenIsrAct(VOS_VOID)
{
    NAS_LMM_RSM_SYS_CHNG_DIR_ENUM_UINT32    enRsmDir    = NAS_LMM_RSM_SYS_CHNG_DIR_BUTT;

    NAS_MML_PS_BEARER_CONTEXT_STRU          *pstPsBearerCtx = NAS_EMM_NULL_PTR;
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_SetTinToPtmsiWhenIsrAct is entry");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SetTinToPtmsiWhenIsrAct_ENUM,LNAS_ENTRY);

    pstPsBearerCtx = NAS_EMM_GetPsBearerCtx();

    /* 获取恢复方向 */
    enRsmDir = NAS_EMM_GetResumeDir();

    if (((NAS_EMM_YES == NAS_EMM_IsW2LAndPmmConnect(enRsmDir))
        || (NAS_EMM_YES == NAS_EMM_IsG2LAndGprsStateReady(enRsmDir))
        || (NAS_EMM_YES == NAS_EMM_IsG2LAndGmmSuspendWithCsPsUeMode()))
        &&(MMC_LMM_TIN_RAT_RELATED_TMSI == NAS_EMM_GetTinType()))
    {
        NAS_EMM_SetTinType(MMC_LMM_TIN_P_TMSI);

        NAS_EMM_UpdateBearISRFlag(pstPsBearerCtx);

        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_SetTinToPtmsiWhenIsrAct: UPDATE MML PS BEARER INFO:");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SetTinToPtmsiWhenIsrAct_ENUM,LNAS_FUNCTION_LABEL2);
        NAS_LMM_LogPsBearerCtxInfo(pstPsBearerCtx);
    }
    return ;
}

/*****************************************************************************
 Function Name   : NAS_EMM_IsG2LGmmSuspendAndIsrAct
 Description     : For case c, if the TIN indicates "RAT-related TMSI" and
                    the EPS services were not resumed before returning to S1 mode,
                    the UE shall set the TIN to "P-TMSI" before initiating the
                    combined tracking area updating procedure
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 132387     2014-10-16  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_IsG2LGmmSuspendAndIsrAct(VOS_VOID)
{

    NAS_MML_PS_BEARER_CONTEXT_STRU *pstPsBearerCtx;
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_IsG2LGmmSuspendAndIsrAct is entry");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_IsG2LGmmSuspendAndIsrAct_ENUM,LNAS_ENTRY);

    pstPsBearerCtx = NAS_EMM_GetPsBearerCtx();

    /* For case c, if the TIN indicates "RAT-related TMSI" and the EPS services were
    not resumed before returning to S1 mode, the UE shall set the TIN to "P-TMSI" before
    initiating the combined tracking area updating procedure*/
    if ((NAS_EMM_YES == NAS_EMM_IsG2LAndGmmSuspendWithCsPsUeMode())
        && (MMC_LMM_TIN_RAT_RELATED_TMSI == NAS_EMM_GetTinType()))
    {
        NAS_EMM_SetTinType(MMC_LMM_TIN_P_TMSI);

        NAS_EMM_UpdateBearISRFlag(pstPsBearerCtx);

        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_IsG2LGmmSuspendAndIsrAct: UPDATE MML PS BEARER INFO:");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsG2LGmmSuspendAndIsrAct_ENUM,LNAS_FUNCTION_LABEL2);
        NAS_LMM_LogPsBearerCtxInfo(pstPsBearerCtx);
    }
    return;
}


VOS_VOID  NAS_EMM_RrcResumeReselTypeSetTauStartCause(VOS_VOID  )
{
    MMC_LMM_TIN_TYPE_ENUM_UINT32        enTinType       = MMC_LMM_TIN_INVALID;
    NAS_LMM_RSM_SYS_CHNG_DIR_ENUM_UINT32    enRsmDir    = NAS_LMM_RSM_SYS_CHNG_DIR_BUTT;

    /* 获取TIN值 */
    enTinType = NAS_EMM_GetTinType();

    /* leixiantiao 00258641 重构代码降低圈复杂度 2014-7-30 begin */
    if(NAS_EMM_YES == NAS_EMM_IsLauOrComRauOrSrvccHappenedWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RrcResumeReselTypeSetTauStartCause:LAU OR COMBINED RAU");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RrcResumeReselTypeSetTauStartCause_ENUM,LNAS_EMM_LAU_OR_COMB_RAU);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }
    /* leixiantiao 00258641 重构代码降低圈复杂度 2014-7-30 end */

    if (NAS_EMM_YES == NAS_EMM_IsEmcCsfbHappenedAndLaiChangWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RrcResumeReselTypeSetTauStartCause:EMC CSFB,LAI CHANG ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RrcResumeReselTypeSetTauStartCause_ENUM,LNAS_EMM_EMC_CSFB_LAI_CHG);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    /* For case l, if the UE was in PMM-CONNECTED mode and the TIN indicates
       "RAT-related TMSI", the UE shall set the TIN to "P-TMSI" before initiating
       the combined tracking area updating procedure. */
    if (NAS_RELEASE_R11)
    {
        NAS_EMM_SetTinToPtmsiWhenIsrAct();
    }
    else
    {
        NAS_EMM_ProcConnGu2LReselect();
    }

    /* e)when the UE enters EMM-REGISTERED.NORMAL-SERVICE and the UE's TIN indicates "P-TMSI" */
    if (MMC_LMM_TIN_P_TMSI == enTinType)
    {
        NAS_EMM_ResumeProcPTMSITau();
        return;
    }

    /* 获取恢复方向 */
    enRsmDir = NAS_EMM_GetResumeDir();

    /* l)when the UE reselects an E-UTRAN cell while it was in GPRS READY state or PMM-CONNECTED mode; */
    if (NAS_EMM_YES == NAS_EMM_IsG2LAndGprsStateReady(enRsmDir))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RrcResumeReselTypeSetTauStartCause:GPRS READY init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RrcResumeReselTypeSetTauStartCause_ENUM,LNAS_EMM_GPRS_READY_TAU);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);
        return;
    }

    if (NAS_EMM_YES == NAS_EMM_IsW2LAndPmmConnect(enRsmDir))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RrcResumeReselTypeSetTauStartCause:PMM-CONNECTED init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RrcResumeReselTypeSetTauStartCause_ENUM,LNAS_EMM_PMM_CONNECTED_TAU);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);
        return;
    }

    /* c)when the UE performs an intersystem change from A/Gb mode to S1 mode and
         the EPS services were previously suspended in A/Gb mode;
         这个条件时联合TAU所独有的 */
    /* leixiantiao 00258641 重构代码降低圈复杂度 2014-7-30 begin */
    if (NAS_EMM_YES == NAS_EMM_IsG2LAndGmmSuspendWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RrcResumeReselTypeSetTauStartCause:EPS service suspended init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RrcResumeReselTypeSetTauStartCause_ENUM,LNAS_EMM_EPS_SERV_SUSP_TAU);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);
        return;
    }
    /* leixiantiao 00258641 重构代码降低圈复杂度 2014-7-30 end */


    /*q)When the UE performs an intersystem change from A/Gb mode to S1 mode and the TIN indicates "RAT-related TMSI",
    but the UE is required to perform tracking area updating for IMS voice termination as specified in 3GPP TS 24.008 [13],
    annex P.4*/
    if ((NAS_LMM_RSM_SYS_CHNG_DIR_G2L == enRsmDir)
        && (NAS_EMM_YES == NAS_EMM_IsAnnexP4ConditionSatisfied())
        && (MMC_LMM_TIN_RAT_RELATED_TMSI == enTinType))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RrcResumeReselTypeSetTauStartCause:ISR ACT and P.4 init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RrcResumeReselTypeSetTauStartCause_ENUM,LNAS_EMM_ISR_ACT_P4_TAU);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);
        return;
    }
    return;
}



VOS_VOID  NAS_EMM_RrcResumeRedirTypeSetTauStartCause(VOS_VOID )
{
    MMC_LMM_TIN_TYPE_ENUM_UINT32            ulTinType   = MMC_LMM_TIN_INVALID;
    NAS_LMM_RSM_SYS_CHNG_DIR_ENUM_UINT32    enRsmDir    = NAS_LMM_RSM_SYS_CHNG_DIR_BUTT;

    /* 获取TIN值 */
    ulTinType = NAS_EMM_GetTinType();

    if (NAS_RELEASE_R11)
    {
        NAS_EMM_IsG2LGmmSuspendAndIsrAct();
    }
    if(((NAS_EMM_LAU_OR_COMBINED_RAU_HAPPENED == NAS_LMM_GetEmmInfoLauOrComRauFlag())
        || (NAS_EMM_SRVCC_HAPPENED == NAS_LMM_GetEmmInfoSrvccFlag()))
        && (NAS_EMM_YES == NAS_EMM_IsCsPsUeMode()))
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_RrcResumeRedirTypeSetTauStartCause:LAU OR COMBINED RAU");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RrcResumeRedirTypeSetTauStartCause_ENUM,LNAS_EMM_LAU_OR_COMB_RAU);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    if (NAS_EMM_YES == NAS_EMM_IsEmcCsfbHappenedAndLaiChangWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgAreaLostInd:EMC CSFB,LAI CHANG ");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_RrcResumeRedirTypeSetTauStartCause_ENUM,LNAS_EMM_EMC_CSFB_LAI_CHG);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    /* e)when the UE enters EMM-REGISTERED.NORMAL-SERVICE and the UE's TIN indicates "P-TMSI" */
    if (MMC_LMM_TIN_P_TMSI == ulTinType)
    {
        NAS_EMM_ResumeProcPTMSITau();
        return;
    }

    /* 获取恢复方向 */
    enRsmDir = NAS_EMM_GetResumeDir();

    /* c)when the UE performs an intersystem change from A/Gb mode to S1 mode and
         the EPS services were previously suspended in A/Gb mode;
         这个条件时联合TAU所独有的 */
    if ((NAS_LMM_RSM_SYS_CHNG_DIR_G2L == enRsmDir)
        && (GMM_LMM_GPRS_SUSPENSION == NAS_LMM_GetEmmInfoPsState())
        && (NAS_EMM_YES == NAS_EMM_IsCsPsUeMode()))
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_RrcResumeRedirTypeSetTauStartCause:EPS service suspended init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RrcResumeRedirTypeSetTauStartCause_ENUM,LNAS_EMM_EPS_SERV_SUSP_TAU);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);
        return;
    }

    /* d)when the UE performs an intersystem change from A/Gb or Iu mode to S1 mode,
         and the UE previously either performed a location area update procedure
         or a combined routing area update procedure in A/Gb or Iu mode,
         in order to re-establish the SGs association. In this case the EPS update
         type IE shall be set to "combined TA/LA updating with IMSI attach"; */
    if ((NAS_EMM_LAU_OR_COMBINED_RAU_HAPPENED == NAS_LMM_GetEmmInfoLauOrComRauFlag())
        && (NAS_EMM_YES == NAS_EMM_IsCsPsUeMode()))
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_RrcResumeRedirTypeSetTauStartCause:LAU or Combined Rau init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RrcResumeRedirTypeSetTauStartCause_ENUM,LNAS_EMM_LAU_COMB_RAU_TAU);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);
        return;
    }

    if (NAS_EMM_YES == NAS_EMM_IsEmcCsfbHappenedAndLaiChangWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_RrcResumeRedirTypeSetTauStartCause:EMC CSFB,LAI CHANG ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RrcResumeRedirTypeSetTauStartCause_ENUM,LNAS_EMM_EMC_CSFB_LAI_CHG);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    /*q)When the UE performs an intersystem change from A/Gb mode to S1 mode and the TIN indicates "RAT-related TMSI",
    but the UE is required to perform tracking area updating for IMS voice termination as specified in 3GPP TS 24.008 [13],
    annex P.4*/
    if (NAS_EMM_YES == NAS_EMM_IsG2LIsrActAndP4ConditionSatisfied(enRsmDir))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RrcResumeRedirTypeSetTauStartCause:ISR ACT and P.4 init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RrcResumeRedirTypeSetTauStartCause_ENUM,LNAS_EMM_ISR_ACT_P4_TAU);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);
        return;
    }
    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgWtSysInfoTimerExpHoProc
 Description     : 对于GU2L的场景，根据激活前状态进入NO CELL状态或NO IMSI状态
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leixiantiao 00258641      2014-7-30  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgWtSysInfoTimerExpHoProc(VOS_VOID)
{
    /*对于GU2L的场景，根据激活前状态进入NO CELL状态或NO IMSI状态 */
    if(NAS_EMM_YES == NAS_EMM_IsLauOrComRauOrSrvccHappenedWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgWtSysInfoTimerExp:LAU OR COMBINED RAU");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgWtSysInfoTimerExpHoProc_ENUM,LNAS_EMM_LAU_OR_COMB_RAU);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    if (NAS_EMM_YES == NAS_EMM_IsEmcCsfbHappenedAndLaiChangWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgWtSysInfoTimerExp:EMC CSFB,LAI CHANG ");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgWtSysInfoTimerExpHoProc_ENUM,LNAS_EMM_EMC_CSFB_LAI_CHG);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    if (NAS_RELEASE_R11)
    {
        NAS_EMM_IsG2LGmmSuspendAndIsrAct();
    }

    NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
    NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);
    NAS_EMM_GU2LResumeStateChng();
    if (NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
    {
        /*发送RRC_MM_REL_REQ*/
        NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
    }
    return;

}

/*****************************************************************************
 Function Name   : NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgWtSysInfoTimerExp
 Description     : 根据激活类型进行不同的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-4-25  Draft Enact
    2.leili 00132387            2011-11-30 modify
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgWtSysInfoTimerExp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  )
{
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgWtSysInfoTimerExp:NAS_EMM_GetResumeType()=",
                               NAS_EMM_GetResumeType());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgWtSysInfoTimerExp_ENUM,LNAS_EMM_RESUME_TYPE,
                               NAS_EMM_GetResumeType());

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_EMM_RatErrRecord(EMM_OM_ERRLOG_REVERSE_WAIT_SYSINFO_TIMEOUT_PROCEDURE);
    #endif

    switch(NAS_EMM_GetResumeType())
    {
        /*对于挂起过程中回退的场景，根据挂起状态进入NO CELL状态或NO IMSI状态 */

        case    NAS_LMM_SYS_CHNG_TYPE_REVERSE_HO:
        case    NAS_LMM_SYS_CHNG_TYPE_REVERSE_CCO:
                NAS_EMM_ReverseStateChng();
                if (NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
                {
                    /*发送RRC_MM_REL_REQ*/
                    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
                }
                break;
        case    NAS_LMM_SYS_CHNG_TYPE_REVERSE_RSL:
        case    NAS_LMM_SYS_CHNG_TYPE_REVERSE_REDIR:
                NAS_EMM_ReverseStateChng();
                break;
        /*对于GU2L的场景，根据激活前状态进入NO CELL状态或NO IMSI状态 */
        case    NAS_LMM_SYS_CHNG_TYPE_HO:
                /* leixiantiao 00258641 重构函数降低圈复杂度 begin */
                NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgWtSysInfoTimerExpHoProc();
                /* leixiantiao 00258641 重构函数降低圈复杂度 end */
                break;
        case    NAS_LMM_SYS_CHNG_TYPE_RSL:
                if (EMM_MS_REG == NAS_EMM_GetMsBefResume())
                {
                    NAS_EMM_RrcResumeReselTypeSetTauStartCause();
                }
                /* 读取GU的UMTS安全上下文，生成LTE的安全参数，并设置安全状态*/
                NAS_EMM_SecuResumeIdle();
                NAS_EMM_GU2LResumeStateChng();
                break;
        case    NAS_LMM_SYS_CHNG_TYPE_CCO:

                if((NAS_EMM_LAU_OR_COMBINED_RAU_HAPPENED == NAS_LMM_GetEmmInfoLauOrComRauFlag())
                    && (NAS_EMM_YES == NAS_EMM_IsCsPsUeMode()))
                {
                    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgWtSysInfoTimerExp:LAU OR COMBINED RAU");
                    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgWtSysInfoTimerExp_ENUM,LNAS_EMM_LAU_OR_COMB_RAU);
                    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
                }

                if (NAS_EMM_YES == NAS_EMM_IsEmcCsfbHappenedAndLaiChangWithCsPsUeMode())
                {
                    NAS_EMM_TAU_LOG_WARN("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgWtSysInfoTimerExp:EMC CSFB,LAI CHANG ");
                    TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgWtSysInfoTimerExp_ENUM,LNAS_EMM_EMC_CSFB_LAI_CHG);
                    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
                }
                if (NAS_RELEASE_R11)
                {
                    NAS_EMM_IsG2LGmmSuspendAndIsrAct();
                }

                NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
                NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);

                /* 读取GU的UMTS安全上下文，生成LTE的安全参数，并设置安全状态*/
                NAS_EMM_SecuResumeIdle();
                NAS_EMM_GU2LResumeStateChng();
                break;
        case    NAS_LMM_SYS_CHNG_TYPE_REDIR:
                if (EMM_MS_REG == NAS_EMM_GetMsBefResume())
                {
                    NAS_EMM_RrcResumeRedirTypeSetTauStartCause();
                }
                /* 读取GU的UMTS安全上下文，生成LTE的安全参数，并设置安全状态*/
                NAS_EMM_SecuResumeIdle();
                NAS_EMM_GU2LResumeStateChng();
                break;
        default :
                NAS_EMM_PUBU_LOG_WARN("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgRrcRelInd:Resume type is err!");
                TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgWtSysInfoTimerExp_ENUM,LNAS_ERROR);
                break;
    }
    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgRrcRelInd
 Description     : RESUME过程等待系统消息时，收到REL_IND，应该是
                   切换回退，或CCO类型的回退，
                   改变连接状态，并通知MMC即可;
                   然后进入标准的LTE模式继续等待SYS或丢网消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-4-25  Draft Enact
    2.leili 00132387            2011-11-30 modify
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgRrcRelInd(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  )
{
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;


    NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgRrcRelInd:NAS_EMM_GetResumeType()=",
                            NAS_EMM_GetResumeType());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgRrcRelInd_ENUM,LNAS_EMM_RESUME_TYPE,
                            NAS_EMM_GetResumeType());

    /* 通知ERABM释放连接,预处理中已经发了，此处不再发 */

    switch(NAS_EMM_GetResumeType())
    {
        /*对于挂起过程中回退的场景，收到释放后，进入NO CELL状态或NO IMSI状态 */
        case    NAS_LMM_SYS_CHNG_TYPE_REVERSE_RSL:
        case    NAS_LMM_SYS_CHNG_TYPE_REVERSE_HO:
        case    NAS_LMM_SYS_CHNG_TYPE_REVERSE_CCO:
        case    NAS_LMM_SYS_CHNG_TYPE_REVERSE_REDIR:
                /*停止定时器TI_NAS_EMM_WAIT_SYS_INFO_IND_TIMER*/
                NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_SYS_INFO_IND_TIMER);
                NAS_EMM_ReverseStateChng();
                break;
        case    NAS_LMM_SYS_CHNG_TYPE_HO:
        case    NAS_LMM_SYS_CHNG_TYPE_RSL:
        case    NAS_LMM_SYS_CHNG_TYPE_CCO:
        case    NAS_LMM_SYS_CHNG_TYPE_REDIR:
                /*GU->L仅在HO过程中能收到LRRC_LMM_REL_IND消息，且在预处理中连接已释放*/
                break;
        default :
                NAS_EMM_PUBU_LOG_WARN("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgRrcRelInd:Resume type is err!");
                TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgRrcRelInd_ENUM,LNAS_ERROR);
                break;
    }
    return NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsResumeSsRrcOriMsgT3412Exp
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    (void)ulMsgId;
    (void)pMsgStru;
    NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsResumeSsRrcOriMsgT3412Exp:NAS_EMM_GetResumeType() =",
                            NAS_EMM_GetResumeType());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsRrcOriMsgT3412Exp_ENUM,LNAS_EMM_RESUME_TYPE,
                            NAS_EMM_GetResumeType());
    if((NAS_LMM_SYS_CHNG_TYPE_RSL == NAS_EMM_GetResumeType()) ||
        (NAS_LMM_SYS_CHNG_TYPE_HO == NAS_EMM_GetResumeType()) ||
        (NAS_LMM_SYS_CHNG_TYPE_CCO == NAS_EMM_GetResumeType()) ||
        (NAS_LMM_SYS_CHNG_TYPE_REDIR == NAS_EMM_GetResumeType()))
    {
        NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsResumeSsRrcOriMsgT3412Exp:NAS_EMM_GetMsBefResume() =",
                            NAS_EMM_GetMsBefResume());
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsRrcOriMsgT3412Exp_ENUM,LNAS_FUNCTION_LABEL1,
                            NAS_EMM_GetMsBefResume());

        /*根据RESUME前的状态进行状态迁移*/
        if(EMM_MS_DEREG == NAS_EMM_GetMsBefResume())
        {
            return NAS_LMM_MSG_HANDLED;
        }
        if (NAS_RELEASE_R11)
        {
            if (NAS_LMM_SYS_CHNG_TYPE_RSL == NAS_EMM_GetResumeType())
            {
                NAS_EMM_SetTinToPtmsiWhenIsrAct();
            }
            else
            {
                NAS_EMM_IsG2LGmmSuspendAndIsrAct();
            }
        }

        /*设置周期TAU定制器超时标志*/
        NAS_LMM_SetEmmInfoT3412ExpCtrl(NAS_EMM_T3412_EXP_YES_OTHER_STATE);

    }
    else
    {
        /*回退过程的处理*/
        NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsResumeSsRrcOriMsgT3412Exp:NAS_EMM_GetMsBefResume() =",
                                    NAS_EMM_GetMsBefSuspend());
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsRrcOriMsgT3412Exp_ENUM,LNAS_FUNCTION_LABEL2,
                                     NAS_EMM_GetMsBefSuspend());

        /*根据SUSPEND前的状态进行状态迁移*/
        if(EMM_MS_DEREG == NAS_EMM_GetMsBefSuspend())
        {
            return NAS_LMM_MSG_HANDLED;
        }

        /*设置周期TAU定制器超时标志*/
        NAS_LMM_SetEmmInfoT3412ExpCtrl(NAS_EMM_T3412_EXP_YES_OTHER_STATE);
    }

    return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgBearStatusReq
 Description     : 收到承载状态请求消息处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-11-22  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgBearStatusReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    (void)ulMsgId;
    (void)pMsgStru;
    NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgBearStatusReq:NAS_EMM_GetResumeType() =",
                            NAS_EMM_GetResumeType());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgBearStatusReq_ENUM,LNAS_EMM_RESUME_TYPE,
                            NAS_EMM_GetResumeType());
    if((NAS_LMM_SYS_CHNG_TYPE_RSL == NAS_EMM_GetResumeType()) ||
        (NAS_LMM_SYS_CHNG_TYPE_HO == NAS_EMM_GetResumeType()) ||
        (NAS_LMM_SYS_CHNG_TYPE_CCO == NAS_EMM_GetResumeType()) ||
        (NAS_LMM_SYS_CHNG_TYPE_REDIR == NAS_EMM_GetResumeType()))
    {
        NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgBearStatusReq:NAS_EMM_GetMsBefResume() =",
                            NAS_EMM_GetMsBefResume());
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgBearStatusReq_ENUM,LNAS_FUNCTION_LABEL1,
                            NAS_EMM_GetMsBefResume());

        /*根据RESUME前的状态进行状态迁移*/
        if(EMM_MS_DEREG == NAS_EMM_GetMsBefResume())
        {
            return NAS_LMM_MSG_HANDLED;
        }

        /* 设置承载上下文变化*/
        NAS_EMM_SetEpsContextStatusChange(NAS_EMM_EPS_BEARER_STATUS_CHANGEED);
    }
    else
    {
        /*回退过程的处理*/
        NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgBearStatusReq:NAS_EMM_GetMsBefResume() =",
                                    NAS_EMM_GetMsBefSuspend());
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgBearStatusReq_ENUM,LNAS_FUNCTION_LABEL2,
                                    NAS_EMM_GetMsBefSuspend());

        /*根据SUSPEND前的状态进行状态迁移*/
        if(EMM_MS_DEREG == NAS_EMM_GetMsBefSuspend())
        {
            return NAS_LMM_MSG_HANDLED;
        }

        /* 设置承载上下文变化*/
        NAS_EMM_SetEpsContextStatusChange(NAS_EMM_EPS_BEARER_STATUS_CHANGEED);

    }
    return NAS_LMM_MSG_HANDLED;
}



VOS_UINT32  NAS_EMM_ProcInterSysCheckRrcRelCause(VOS_VOID)
{
    if(NAS_EMM_TRIGGER_TAU_RRC_REL_LOAD_BALANCE == NAS_LMM_GetEmmInfoTriggerTauRrcRel())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RrcRelCauseTriggerTau:load balance");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcInterSysCheckRrcRelCause_ENUM,LNAS_FUNCTION_LABEL1);
        /* 大数据: 异系统TAU使用异系统TAU接口 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_LOAD_BALANCE);
        return NAS_EMM_YES;
    }
    else if(NAS_EMM_TRIGGER_TAU_RRC_REL_CONN_FAILURE == NAS_LMM_GetEmmInfoTriggerTauRrcRel())
    {
        /* 不能删除，如果有上行PENDING,则会发起SERVICE */
        NAS_EMM_TAU_IsUplinkPending();

        if(NAS_EMM_UPLINK_PENDING == NAS_EMM_TAU_GetEmmUplinkPending())
        {
            NAS_EMM_TAU_LOG_INFO("NAS_EMM_RrcRelCauseTriggerTau:Init Ser.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcInterSysCheckRrcRelCause_ENUM,LNAS_FUNCTION_LABEL2);
            NAS_EMM_SER_UplinkPending();
        }
        else
        {
            NAS_EMM_TAU_LOG_INFO("NAS_EMM_RrcRelCauseTriggerTau:RRC connection failure");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcInterSysCheckRrcRelCause_ENUM,LNAS_FUNCTION_LABEL3);

            /* 大数据: 异系统TAU使用异系统TAU接口 */
            NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_CONN_FAIL);
        }

        return NAS_EMM_YES;
    }
    else
    {

    }

    return NAS_EMM_NO;
}


VOS_UINT32 NAS_EMM_ProcSysCheck3412Exp( VOS_VOID )
{
    if (NAS_EMM_T3412_EXP_YES_REG_NO_AVALABLE_CELL ==  NAS_LMM_GetEmmInfoT3412ExpCtrl())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysCheck3412Exp:REG+NO_AVAILABE_CELL T3412exp.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysCheck3412Exp_ENUM,LNAS_FUNCTION_LABEL1);
        if (NAS_LMM_SYS_CHNG_TYPE_HO != NAS_EMM_GetResumeType())
        {
            /* 读取GU的UMTS安全上下文，生成LTE的安全参数，并设置安全状态*/
            NAS_EMM_SecuResumeIdle();
        }

        if (NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain())
        {
            NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        }
        else
        {
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_T3412EXP);
        }

        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);
        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_3412_EXP_HAPPENED);
        return NAS_EMM_YES;
    }

    /* 协议24301 5.3.5章节描述，如果在非REG+NO_AVAILABLE_CELL状态下，T3412超时，
     则当回到REG+NORMAL_SERVICE态后，应触发 Periodic TAU*/
    if(NAS_EMM_T3412_EXP_YES_OTHER_STATE == NAS_LMM_GetEmmInfoT3412ExpCtrl())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysCheck3412Exp:Other State T3412exp.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysCheck3412Exp_ENUM,LNAS_FUNCTION_LABEL2);
        if (NAS_LMM_SYS_CHNG_TYPE_HO != NAS_EMM_GetResumeType())
        {
            /* 读取GU的UMTS安全上下文，生成LTE的安全参数，并设置安全状态*/
            NAS_EMM_SecuResumeIdle();
        }

        NAS_EMM_TAU_SaveEmmTAUStartCause( NAS_EMM_TAU_START_CAUSE_T3412EXP);
        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);

        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_3412_EXP_HAPPENED);
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}


VOS_UINT32 NAS_EMM_ProcSysCommonCheckTauFlag( VOS_VOID )
{
    /* 如果TA不在TA List中，需要发起TAU */
    if (NAS_EMM_FAIL == NAS_EMM_TAU_IsCurrentTAInTaList())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysCommonCheckTauFlag:TAI not in TAI LIST init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysCommonCheckTauFlag_ENUM,LNAS_EMM_TA_NOT_IN_LIST_TAU);
        /* 大数据: 异系统TAU使用异系统TAU接口 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_NOT_IN_TAI_LIST);
        return NAS_EMM_YES;
    }

    /* 如果期间发生过ESM本地修改承载上下文*/
    if(NAS_EMM_EPS_BEARER_STATUS_CHANGEED == NAS_EMM_GetEpsContextStatusChange())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysCommonCheckTauFlag: Bearer Status Change.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysCommonCheckTauFlag_ENUM,LNAS_FUNCTION_LABEL1);

        /* 大数据: 异系统TAU使用异系统TAU接口 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_BEARER_STATUS_CHANGEED);
        return NAS_EMM_YES;
    }

    /* 如果期间发生过UE_NET_CAP or DRX改变，触发TA-Updating TAU*/
    if(NAS_EMM_YES == NAS_LMM_GetEmmInfoDrxNetCapChange())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysCommonCheckTauFlag: DrxOrNetCap Change.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysCommonCheckTauFlag_ENUM,LNAS_FUNCTION_LABEL2);

        /* 大数据: 异系统TAU使用异系统TAU接口 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_DRX_CHANGEED);
        return NAS_EMM_YES;
    }

    /* 如果当前注册域为PS，且当前有能力发起CS域的注册，则发起联合TAU */
    if (NAS_EMM_YES == NAS_EMM_TAU_CanTriggerComTauWithIMSI())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysCommonCheckTauFlag:current reg domain=PS,can register in cs domain");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysCommonCheckTauFlag_ENUM,LNAS_FUNCTION_LABEL3);
        /* 大数据: 异系统TAU使用异系统TAU接口 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_ATTACH_NON_EPS);
        return NAS_EMM_YES;
    }

    /*如果当前EU值不是EU1*/
    if(EMM_US_UPDATED_EU1 != NAS_EMM_TAUSER_GetAuxFsmUpStat())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysCommonCheckTauFlag:EU value is not EU1");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysCommonCheckTauFlag_ENUM,LNAS_FUNCTION_LABEL4);

        /* 大数据: 异系统TAU使用异系统TAU接口 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_NOT_EU1);
        return NAS_EMM_YES;
    }

    /*判断RRC Rel原因标识*/
    if(NAS_EMM_YES == NAS_EMM_ProcInterSysCheckRrcRelCause())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysCommonCheckTauFlag:rrc rel cause");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysCommonCheckTauFlag_ENUM,LNAS_EMM_REL_CAUSE);
        return NAS_EMM_YES;
    }

    /* 如果UE无线能力发生变更 */
    if(NAS_LMM_UE_RADIO_CAP_NOT_CHG != NAS_LMM_GetEmmInfoUeRadioCapChgFlag())
    {
        /* 大数据: 异系统TAU使用异系统TAU接口 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_RADIO_CAP_CHANGE);
        return NAS_EMM_YES;
    }

    /*如果T3412曾经超时过*/
    if(NAS_EMM_YES == NAS_EMM_ProcSysCheck3412Exp() )
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysCommonCheckTauFlag:3412 exp");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysCommonCheckTauFlag_ENUM,LNAS_TIMER_EXPIRED);

        return NAS_EMM_YES;
    }

    if(NAS_EMM_YES == NAS_EMM_GetVoiceDomainChange() )
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateStartTAUNeeded: VOICE DOMAIN CHANG ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysCommonCheckTauFlag_ENUM,LNAS_FUNCTION_LABEL5);

        /* 大数据: 异系统TAU使用异系统TAU接口 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_VOICE_DOMAIN_CHANGE, NAS_LMM_OM_TAU_START_TYPE_VOICE_DOMAIN_CHANGE);
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}

VOS_UINT32 NAS_EMM_ProcHoSysCommonCheckTauFlag( VOS_VOID )
{
#if(FEATURE_ON == FEATURE_CSG)
    if((NAS_EMM_YES == NAS_LMM_IsCsgCampOn())
        &&(NAS_EMM_FAIL == NAS_EMM_TAU_IsCsgIdInAllowedOrOperatorCsgList()))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysCommonCheckTauFlag:CSG ID not in CSG LIST init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysCommonCheckTauFlag_ENUM,LNAS_EMM_NOT_IN_CSG_LIST_TAU);

        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_NOT_IN_CSG_LIST);

        return NAS_EMM_YES;
    }
#endif

    /* 如果TA不在TA List中，需要发起TAU */
    if (NAS_EMM_FAIL == NAS_EMM_TAU_IsCurrentTAInTaList())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysCommonCheckTauFlag:TAI not in TAI LIST init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcHoSysCommonCheckTauFlag_ENUM,LNAS_EMM_TA_NOT_IN_LIST_TAU);
        /* 大数据: 异系统TAU使用异系统TAU接口 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_NOT_IN_TAI_LIST);
        return NAS_EMM_YES;
    }

    /* 如果期间发生过ESM本地修改承载上下文*/
    if(NAS_EMM_EPS_BEARER_STATUS_CHANGEED == NAS_EMM_GetEpsContextStatusChange())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysCommonCheckTauFlag: Bearer Status Change.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcHoSysCommonCheckTauFlag_ENUM,LNAS_FUNCTION_LABEL1);

        /* 大数据: 异系统TAU使用异系统TAU接口 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_BEARER_STATUS_CHANGEED);
        return NAS_EMM_YES;
    }

    /* 如果期间发生过UE_NET_CAP or DRX改变，触发TA-Updating TAU*/
    if(NAS_EMM_YES == NAS_LMM_GetEmmInfoDrxNetCapChange())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysCommonCheckTauFlag: DrxOrNetCap Change.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcHoSysCommonCheckTauFlag_ENUM,LNAS_FUNCTION_LABEL2);

        /* 大数据: 异系统TAU使用异系统TAU接口 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_DRX_CHANGEED);
        return NAS_EMM_YES;
    }

    /* 如果当前注册域为PS，且当前有能力发起CS域的注册，则发起联合TAU */
    if (NAS_EMM_YES == NAS_EMM_TAU_CanTriggerComTauWithIMSI())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysCommonCheckTauFlag:current reg domain=PS,can register in cs domain");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcHoSysCommonCheckTauFlag_ENUM,LNAS_FUNCTION_LABEL3);
        /* 大数据: 异系统TAU使用异系统TAU接口 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_ATTACH_NON_EPS);
        return NAS_EMM_YES;
    }

    /*如果当前EU值不是EU1*/
    if(EMM_US_UPDATED_EU1 != NAS_EMM_TAUSER_GetAuxFsmUpStat())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysCommonCheckTauFlag:EU value is not EU1");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcHoSysCommonCheckTauFlag_ENUM,LNAS_FUNCTION_LABEL4);

        /* 大数据: 异系统TAU使用异系统TAU接口 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_NOT_EU1);
        return NAS_EMM_YES;
    }

    /* 如果UE无线能力发生变更 */
    if(NAS_LMM_UE_RADIO_CAP_NOT_CHG != NAS_LMM_GetEmmInfoUeRadioCapChgFlag())
    {
        /* 大数据: 异系统TAU使用异系统TAU接口 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_RADIO_CAP_CHANGE);
        return NAS_EMM_YES;
    }

    /*如果T3412曾经超时过*/
    if(NAS_EMM_YES == NAS_EMM_ProcSysCheck3412Exp() )
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysCommonCheckTauFlag:3412 exp");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcHoSysCommonCheckTauFlag_ENUM,LNAS_TIMER_EXPIRED);

        return NAS_EMM_YES;
    }

    if(NAS_EMM_YES == NAS_EMM_GetVoiceDomainChange() )
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateStartTAUNeeded: VOICE DOMAIN CHANG ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcHoSysCommonCheckTauFlag_ENUM,LNAS_FUNCTION_LABEL5);
        /* 大数据: 异系统TAU使用异系统TAU接口 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_VOICE_DOMAIN_CHANGE, NAS_LMM_OM_TAU_START_TYPE_VOICE_DOMAIN_CHANGE);
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcGu
 Description     : 处理注册态下重选类型的解挂.
                   收到系统消息后，两种可能: TAU, 无动作。
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387     2012-03-22  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcConnGu2LReselect( VOS_VOID )
{
    GMM_LMM_PACKET_MM_STATE_ENUM_UINT32 enPacketMmState = GMM_LMM_PACKET_MM_STATE_BUTT;
    MMC_LMM_TIN_TYPE_ENUM_UINT32        enTinType       = MMC_LMM_TIN_INVALID;
    NAS_MML_PS_BEARER_CONTEXT_STRU      *pstPsBearerCtx = NAS_EMM_NULL_PTR;
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_ProcConnGu2LReselect is entry");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcConnGu2LReselect_ENUM,LNAS_ENTRY);

    pstPsBearerCtx = NAS_EMM_GetPsBearerCtx();

     /* 获取TIN值 */
    enTinType = NAS_EMM_GetTinType();

    /* 获取U模连接状态 */
    enPacketMmState = NAS_LMM_GetEmmInfoUConnState();

    /* For case l, if the UE was in PMM-CONNECTED mode and the TIN indicates
       "RAT-related TMSI", the UE shall set the TIN to "P-TMSI" before initiating
       the combined tracking area updating procedure. */
    if ((GMM_LMM_PACKET_MM_STATE_PMM_CONNECTED == enPacketMmState)
        && (MMC_LMM_TIN_RAT_RELATED_TMSI == enTinType))
    {
        NAS_EMM_SetTinType(MMC_LMM_TIN_P_TMSI);
        NAS_EMM_UpdateBearISRFlag(pstPsBearerCtx);
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_ProcConnGu2LReselect: UPDATE MML PS BEARER INFO:");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcConnGu2LReselect_ENUM,LNAS_FUNCTION_LABEL2);
        NAS_LMM_LogPsBearerCtxInfo(pstPsBearerCtx);

    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcSysWhenRsmGu2LRegReselect
 Description     : 处理注册态下重选类型的解挂.
                   收到系统消息后，两种可能: TAU, 无动作。
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010     2011-08-15  Draft Enact
    2.wangchen  00209181        2013-10-24  Modify
    3.lihong00150010     2012-12-18  Modify:Emergency

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcSysWhenRsmGu2LRegReselect( VOS_VOID )
{
    MMC_LMM_TIN_TYPE_ENUM_UINT32        enTinType       = MMC_LMM_TIN_INVALID;
    NAS_LMM_RSM_SYS_CHNG_DIR_ENUM_UINT32    enRsmDir    = NAS_LMM_RSM_SYS_CHNG_DIR_BUTT;
    NAS_LMM_NETWORK_INFO_STRU          *pMmNetInfo      = NAS_EMM_NULL_PTR;

    if (NAS_EMM_YES == NAS_EMM_IsPtmsiTauActiveFlagSatified())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegReselect: PTMSI, save active flag ctrl.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegReselect_ENUM, LNAS_EMM_PTMSI_SET_ACT_FLAG);
        NAS_EMM_TAU_SaveEmmPtmsiActiveFlagCtrl(NAS_EMM_PTMSI_ACTIVE_FLAG_CTRL_VALID);
    }

    /* For case l, if the UE was in PMM-CONNECTED mode and the TIN indicates
       "RAT-related TMSI", the UE shall set the TIN to "P-TMSI" before initiating
       the combined tracking area updating procedure. */
    if (NAS_RELEASE_R11)
    {
        NAS_EMM_SetTinToPtmsiWhenIsrAct();
    }
    else
    {
        NAS_EMM_ProcConnGu2LReselect();
    }

    /* 获取TIN值 */
    enTinType = NAS_EMM_GetTinType();

    /* e)when the UE enters EMM-REGISTERED.NORMAL-SERVICE and the UE's TIN indicates "P-TMSI" */
    if (MMC_LMM_TIN_P_TMSI == enTinType)
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegReselect:P-TMSI init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegReselect_ENUM,LNAS_EMM_PTMSI_TAU);

        if ((NAS_EMM_T3412_EXP_YES_REG_NO_AVALABLE_CELL == NAS_LMM_GetEmmInfoT3412ExpCtrl())
            && (NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain()))
        {
            NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegReselect:combined succ");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegReselect_ENUM,LNAS_FUNCTION_LABEL1);

            /* 将注册域改为PS，是为了回到REG+NORMAL_SERVICE态后，如果要发起联合TAU，则
                TAU类型应该填为combined TA/LA updating with IMSI attach */
            NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

        }
        /* 大数据: 异系统TAU使用异系统TAU接口 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_PTMSI);
        return;
    }

    /* 获取恢复方向 */
    enRsmDir = NAS_EMM_GetResumeDir();

    /* l)when the UE reselects an E-UTRAN cell while it was in GPRS READY state or PMM-CONNECTED mode; */
    /* For case l, if the TIN indicates "RAT-related TMSI", the UE shall set the TIN to "P-TMSI" before
    initiating the tracking area updating procedure.*/
    if (NAS_EMM_YES == NAS_EMM_IsG2LAndGprsStateReady(enRsmDir))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegReselect:GPRS READY init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegReselect_ENUM,LNAS_EMM_GPRS_READY_TAU);

        /* 大数据: 异系统TAU使用异系统TAU接口 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_GPRS_READY_OR_PMM_CONNECT);
        return ;
    }

    if (NAS_EMM_YES == NAS_EMM_IsW2LAndPmmConnect(enRsmDir))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegReselect:PMM-CONNECTED init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegReselect_ENUM,LNAS_EMM_PMM_CONNECTED_TAU);
        /* 大数据: 异系统TAU使用异系统TAU接口 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_GPRS_READY_OR_PMM_CONNECT);
        return ;
    }

    /* c)when the UE performs an intersystem change from A/Gb mode to S1 mode and
         the EPS services were previously suspended in A/Gb mode;
         这个条件时联合TAU所独有的 */
    /* For case c, if the TIN indicates "RAT-related TMSI" and the EPS services were
    not resumed before returning to S1 mode, the UE shall set the TIN to "P-TMSI" before
    initiating the combined tracking area updating procedure*/
    /* leixiantiao 00258641 重构代码降低圈复杂度 2014-7-30 begin */
    if (NAS_EMM_YES == NAS_EMM_IsG2LAndGmmSuspendWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegReselect:EPS service suspended init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegReselect_ENUM,LNAS_EMM_EPS_SERV_SUSP_TAU);

        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_GSM_PS_SUSPEND);
        return ;
    }

    /* leixiantiao 00258641 重构代码降低圈复杂度 2014-7-30 end */
    /* d)when the UE performs an intersystem change from A/Gb or Iu mode to S1 mode,
         and the UE previously either performed a location area update procedure
         or a combined routing area update procedure in A/Gb or Iu mode,
         in order to re-establish the SGs association. In this case the EPS update
         type IE shall be set to "combined TA/LA updating with IMSI attach"; */
    /* leixiantiao 00258641 重构代码降低圈复杂度 2014-7-30 begin */
    if (NAS_EMM_YES == NAS_EMM_IsLauOrComRauOrSrvccHappenedWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegReselect:LAU or Combined Rau init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegReselect_ENUM,LNAS_EMM_LAU_COMB_RAU_TAU);
        /* 大数据: 异系统TAU使用异系统TAU接口 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_SRVCC);
        return ;
    }

    if (NAS_EMM_YES == NAS_EMM_IsEmcCsfbHappenedAndLaiChangWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_ProcSysWhenRsmGu2LRegReselect:EMC CSFB,LAI CHANG ");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_ProcSysWhenRsmGu2LRegReselect_ENUM,LNAS_EMM_EMC_CSFB_LAI_CHG);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    /* leixiantiao 00258641 重构代码降低圈复杂度 2014-7-30 end */
    /*q)When the UE performs an intersystem change from A/Gb mode to S1 mode and the TIN indicates "RAT-related TMSI",
    but the UE is required to perform tracking area updating for IMS voice termination as specified in 3GPP TS 24.008 [13],
    annex P.4*/
    if (NAS_EMM_YES == NAS_EMM_IsG2LIsrActAndP4ConditionSatisfied(enRsmDir))

    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegReselect:ISR act and P.4 init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegReselect_ENUM,LNAS_EMM_ISR_ACT_P4_TAU);
        /* 大数据: 异系统TAU使用异系统TAU接口 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_P4);
        return;
    }

    /*把TA不在TA List等条件封装到下面函数判断*/
    if(NAS_EMM_YES == NAS_EMM_ProcSysCommonCheckTauFlag())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegReselect:entered NAS_EMM_ProcSysCommonCheckTauFlag");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegReselect_ENUM,LNAS_FUNCTION_LABEL1);
        return;
    }

    /* 以上条件都不符合，则不需要触发TAU,直接回复正常服务*/
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegReselect:Trans Reg.Normal_Servie.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegReselect_ENUM,LNAS_FUNCTION_LABEL2);

    /* 获取EMM维护的网络信息*/
    pMmNetInfo = NAS_LMM_GetEmmInfoNetInfoAddr();

    /* TA在TAI List中，更新 L.V.R TAI*/
    NAS_EMM_SetLVRTai(&pMmNetInfo->stPresentNetId);
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
    /* 注册/服务状态上报上移MMC优化:先保存EU值再回复TAU结果 */
    /* 确保EU状态为EU1*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_UPDATED_EU1);
    /*向MMC发送LMM_MMC_TAU_RESULT_IND消息*/
    NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara();
    /* 清除Active flag */
    NAS_EMM_TAU_ClearActiveFlagProc();

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcSysWhenRsmGu2LRegRedirect
 Description     : 处理注册态下重定向类型的解挂.
                   收到系统消息后，两种可能: TAU, 无动作。
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010     2011-08-15  Draft Enact
    2.sunjitan 00193151  2012-07-12 Modify: 删除对定时器的判断
    3.wangchen  00209181        2013-10-24  Modify
    4.lihong00150010     2012-12-18  Modify:Emergency
*****************************************************************************/
VOS_VOID  NAS_EMM_ProcSysWhenRsmGu2LRegRedirect( VOS_VOID )
{
    MMC_LMM_TIN_TYPE_ENUM_UINT32            ulTinType   = MMC_LMM_TIN_INVALID;
    NAS_LMM_RSM_SYS_CHNG_DIR_ENUM_UINT32    enRsmDir    = NAS_LMM_RSM_SYS_CHNG_DIR_BUTT;
    NAS_LMM_NETWORK_INFO_STRU              *pMmNetInfo  = NAS_EMM_NULL_PTR;

    if (NAS_EMM_YES == NAS_EMM_IsPtmsiTauActiveFlagSatified())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegRedirect: PTMSI, save active flag ctrl.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegRedirect_ENUM, LNAS_EMM_PTMSI_SET_ACT_FLAG);
        NAS_EMM_TAU_SaveEmmPtmsiActiveFlagCtrl(NAS_EMM_PTMSI_ACTIVE_FLAG_CTRL_VALID);
    }

    if (NAS_RELEASE_R11)
    {
        NAS_EMM_IsG2LGmmSuspendAndIsrAct();
    }

    /* 获取TIN值 */
    ulTinType = NAS_EMM_GetTinType();

    /* e)when the UE enters EMM-REGISTERED.NORMAL-SERVICE and the UE's TIN indicates "P-TMSI" */
    if (MMC_LMM_TIN_P_TMSI == ulTinType)
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegRedirect:P-TMSI init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegRedirect_ENUM,LNAS_EMM_PTMSI_TAU);

        if ((NAS_EMM_T3412_EXP_YES_REG_NO_AVALABLE_CELL == NAS_LMM_GetEmmInfoT3412ExpCtrl())
            && (NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain()))
        {
            NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegRedirect:combined succ");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegRedirect_ENUM,LNAS_FUNCTION_LABEL1);

            /* 将注册域改为PS，是为了回到REG+NORMAL_SERVICE态后，如果要发起联合TAU，则
                TAU类型应该填为combined TA/LA updating with IMSI attach */
            NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

        }
        /* 大数据: 异系统TAU使用异系统TAU接口 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_PTMSI);
        return;
    }

    /* 获取恢复方向 */
    enRsmDir = NAS_EMM_GetResumeDir();

    /* c)when the UE performs an intersystem change from A/Gb mode to S1 mode and
         the EPS services were previously suspended in A/Gb mode;
         这个条件时联合TAU所独有的 */
    /* leixiantiao 00258641 重构函数降低圈复杂度 2014-7-30 begin */
    if (NAS_EMM_YES == NAS_EMM_IsG2LAndGmmSuspendWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegRedirect:EPS service suspended init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegRedirect_ENUM,LNAS_EMM_EPS_SERV_SUSP_TAU);
        /* 大数据: 异系统TAU使用异系统TAU接口 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_GSM_PS_SUSPEND);
        return ;
    }
    /* leixiantiao 00258641 重构函数降低圈复杂度 2014-7-30 end */

    /* d)when the UE performs an intersystem change from A/Gb or Iu mode to S1 mode,
         and the UE previously either performed a location area update procedure
         or a combined routing area update procedure in A/Gb or Iu mode,
         in order to re-establish the SGs association. In this case the EPS update
         type IE shall be set to "combined TA/LA updating with IMSI attach"; */
    /* leixiantiao 00258641 重构函数降低圈复杂度 2014-7-30 begin */
    if (NAS_EMM_YES == NAS_EMM_IsLauOrComRauOrSrvccHappenedWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegRedirect:LAU or Combined Rau init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegRedirect_ENUM,LNAS_EMM_LAU_COMB_RAU_TAU);
        /* 大数据: 异系统TAU使用异系统TAU接口 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_LAU_COMRAU);
        return ;
    }

    if (NAS_EMM_YES == NAS_EMM_IsEmcCsfbHappenedAndLaiChangWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_ProcSysWhenRsmGu2LRegRedirect:EMC CSFB,LAI CHANG ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegRedirect_ENUM,LNAS_EMM_EMC_CSFB_LAI_CHG);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }
    /* leixiantiao 00258641 重构函数降低圈复杂度 2014-7-30 end */
    /*q)When the UE performs an intersystem change from A/Gb mode to S1 mode and the TIN indicates "RAT-related TMSI",
    but the UE is required to perform tracking area updating for IMS voice termination as specified in 3GPP TS 24.008 [13],
    annex P.4*/
    if ((NAS_LMM_RSM_SYS_CHNG_DIR_G2L == enRsmDir)
        && (NAS_EMM_YES == NAS_EMM_IsAnnexP4ConditionSatisfied())
        && (MMC_LMM_TIN_RAT_RELATED_TMSI == ulTinType))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegRedirect:ISR act and P.4 init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegRedirect_ENUM,LNAS_EMM_ISR_ACT_P4_TAU);
        /* 大数据: 异系统TAU使用异系统TAU接口 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_P4);
        return;
    }

    /*把TA不在TA List等条件的判断，封装到下面的函数*/
    if(NAS_EMM_YES == NAS_EMM_ProcSysCommonCheckTauFlag())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegRedirect:entered NAS_EMM_ProcSysCommonCheckTauFlag");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegRedirect_ENUM,LNAS_FUNCTION_LABEL2);
        return;
    }

    /* 以上条件都不符合，则不需要触发TAU,直接回复正常服务*/
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegRedirect:Trans Reg.Normal_Servie.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegRedirect_ENUM,LNAS_FUNCTION_LABEL3);

    /* 获取EMM维护的网络信息*/
    pMmNetInfo = NAS_LMM_GetEmmInfoNetInfoAddr();

    /* TA在TAI List中，更新 L.V.R TAI*/
    NAS_EMM_SetLVRTai(&pMmNetInfo->stPresentNetId);
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

    /* 确保EU状态为EU1*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_UPDATED_EU1);

    /* 清除Active flag */
    NAS_EMM_TAU_ClearActiveFlagProc();

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcSysWhenRsmGu2LRegCco
 Description     : 处理注册态下CCO类型的解挂,收到系统消息后TAU。
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151     2015-03-15  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_ProcSysWhenRsmGu2LRegCco( VOS_VOID )
{
    if (NAS_EMM_YES == NAS_EMM_IsPtmsiTauActiveFlagSatified())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegCco: PTMSI, save active flag ctrl.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegCco_ENUM, LNAS_EMM_PTMSI_SET_ACT_FLAG);
        NAS_EMM_TAU_SaveEmmPtmsiActiveFlagCtrl(NAS_EMM_PTMSI_ACTIVE_FLAG_CTRL_VALID);
    }

    if (NAS_RELEASE_R11)
    {
        NAS_EMM_IsG2LGmmSuspendAndIsrAct();
    }

    /* CCO需要发起建链，暂定发起TAU */
    if ((NAS_EMM_T3412_EXP_YES_REG_NO_AVALABLE_CELL == NAS_LMM_GetEmmInfoT3412ExpCtrl())
    && (NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain()))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegCco:combined succ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LRegCco_ENUM,LNAS_FUNCTION_LABEL1);

        /* 将注册域改为PS，是为了回到REG+NORMAL_SERVICE态后，如果要发起联合TAU，则
            TAU类型应该填为combined TA/LA updating with IMSI attach */
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    /* 大数据: 异系统TAU使用异系统TAU接口 */
    NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_CCO);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcSysWhenRsmGu2LHo
 Description     : 切换的系统变换，发起TAU
                   5.5.3.2.2  l)when the UE reselects an E-UTRAN cell while it
                   was in GPRS READY state or PMM-CONNECTED mode;
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-4-26  Draft Enact
    2.wangchen 00209181    2013-10-24 Modify
*****************************************************************************/
VOS_VOID  NAS_EMM_ProcSysWhenRsmGu2LHo( VOS_VOID )
{
    MMC_LMM_TIN_TYPE_ENUM_UINT32            ulTinType   = MMC_LMM_TIN_INVALID;
    NAS_LMM_RSM_SYS_CHNG_DIR_ENUM_UINT32    enRsmDir    = NAS_LMM_RSM_SYS_CHNG_DIR_BUTT;
    NAS_LMM_NETWORK_INFO_STRU              *pMmNetInfo  = NAS_EMM_NULL_PTR;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LHo: ENTER.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LHo_ENUM,LNAS_ENTRY);

    NAS_LMM_SetEmmInfoTriggerTauRrcRel(NAS_EMM_TRIGGER_TAU_RRC_REL_NO);

    /* 获取TIN值 */
    ulTinType = NAS_EMM_GetTinType();

    if (NAS_RELEASE_R11)
    {
        NAS_EMM_IsG2LGmmSuspendAndIsrAct();
    }

    /* e)when the UE enters EMM-REGISTERED.NORMAL-SERVICE and the UE's TIN indicates "P-TMSI" */
    if (MMC_LMM_TIN_P_TMSI == ulTinType)
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LHo:P-TMSI init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LHo_ENUM,LNAS_EMM_PTMSI_TAU);

        if ((NAS_EMM_T3412_EXP_YES_REG_NO_AVALABLE_CELL == NAS_LMM_GetEmmInfoT3412ExpCtrl())
            && (NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain()))
        {
            NAS_EMM_PUBU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LHo:combined succ");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LHo_ENUM,LNAS_FUNCTION_LABEL1);

            /* 将注册域改为PS，是为了回到REG+NORMAL_SERVICE态后，如果要发起联合TAU，则
                TAU类型应该填为combined TA/LA updating with IMSI attach */
            NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

        }
        /* 大数据: 异系统TAU使用异系统TAU接口 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_PTMSI);
        return;
    }

    /* ISR激活的情况下，判断是否需要发起TAU */

    /* 获取恢复方向 */
    enRsmDir = NAS_EMM_GetResumeDir();

    /* c)when the UE performs an intersystem change from A/Gb mode to S1 mode and
         the EPS services were previously suspended in A/Gb mode;
         这个条件时联合TAU所独有的 */
    /* For case c, if the TIN indicates "RAT-related TMSI" and the EPS services were
    not resumed before returning to S1 mode, the UE shall set the TIN to "P-TMSI" before
    initiating the combined tracking area updating procedure*/
    if (NAS_EMM_YES == NAS_EMM_IsG2LAndGmmSuspendWithCsPsUeMode())
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegRedirect:EPS service suspended init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LHo_ENUM,LNAS_EMM_EPS_SERV_SUSP_TAU);

        /* 大数据: 异系统TAU使用异系统TAU接口 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_GSM_PS_SUSPEND);
        return ;
    }

    /* d)when the UE performs an intersystem change from A/Gb or Iu mode to S1 mode,
         and the UE previously either performed a location area update procedure
         or a combined routing area update procedure in A/Gb or Iu mode,
         in order to re-establish the SGs association. In this case the EPS update
         type IE shall be set to "combined TA/LA updating with IMSI attach"; */
    if (NAS_EMM_YES == NAS_EMM_IsLauOrComRauOrSrvccHappenedWithCsPsUeMode())
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegRedirect:LAU or Combined Rau init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LHo_ENUM,LNAS_EMM_LAU_COMB_RAU_TAU);
        /* 大数据: 异系统TAU使用异系统TAU接口 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_LAU_COMRAU);
        return ;
    }

    if (NAS_EMM_YES == NAS_EMM_IsEmcCsfbHappenedAndLaiChangWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_ProcSysWhenRsmGu2LRegRedirect:EMC CSFB,LAI CHANG ");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_ProcSysWhenRsmGu2LHo_ENUM,LNAS_EMM_EMC_CSFB_LAI_CHG);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    /*q)When the UE performs an intersystem change from A/Gb mode to S1 mode and the TIN indicates "RAT-related TMSI",
    but the UE is required to perform tracking area updating for IMS voice termination as specified in 3GPP TS 24.008 [13],
    annex P.4*/
    if ((NAS_LMM_RSM_SYS_CHNG_DIR_G2L == enRsmDir)
        && (NAS_EMM_YES == NAS_EMM_IsAnnexP4ConditionSatisfied())
        && (MMC_LMM_TIN_RAT_RELATED_TMSI == ulTinType))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegRedirect:ISR act and P.4 init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LHo_ENUM,LNAS_EMM_ISR_ACT_P4_TAU);
        /* 大数据: 异系统TAU使用异系统TAU接口 */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_P4);
        return;
    }

    /*把TA不在TA List等条件的判断，封装到下面的函数*/
    if(NAS_EMM_YES == NAS_EMM_ProcHoSysCommonCheckTauFlag())
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegRedirect:entered NAS_EMM_ProcSysCommonCheckTauFlag");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LHo_ENUM,LNAS_FUNCTION_LABEL2);
        return;
    }

    /* 以上条件都不符合，则不需要触发TAU,直接回复正常服务*/
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegRedirect:Trans Reg.Normal_Servie.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSysWhenRsmGu2LHo_ENUM,LNAS_FUNCTION_LABEL3);

    /* 获取EMM维护的网络信息*/
    pMmNetInfo = NAS_LMM_GetEmmInfoNetInfoAddr();

    /* TA在TAI List中，更新 L.V.R TAI*/
    NAS_EMM_SetLVRTai(&pMmNetInfo->stPresentNetId);

    /* 转换EMM状态机MS_REG+SS_NORMAL_SEARVICE*/
    NAS_EMM_TAUSER_FSMTranState(    EMM_MS_REG,
                                    EMM_SS_REG_NORMAL_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

    NAS_EMM_SetTauTypeNoProcedure();
    /* 注册/服务状态上报上移MMC优化:先保存EU值再回复TAU结果 */
    /* 先保存EU值再回复TAU结果 */
    /* 确保EU状态为EU1*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_UPDATED_EU1);
    /*向MMC发送LMM_MMC_TAU_RESULT_IND消息*/
    NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara();
    /* 上报EPS LOC信息 */
    NAS_EMM_SndOmLogEpsLocInfo();

    return;
}


VOS_VOID  NAS_EMM_ProcSuitSysWhenRsmGu2LReg(VOS_VOID)
{
    /* 兰州CSFB定制需求开关打开时，所有RRC触发的异系统变换到L下均发起
       IMSI_ATTACH类型TAU,目的是解决发起type1类型的TAU导致概率无法收到被叫问题，
       GCF测试场景此开关无效，仍走协议流程 */
    if((NAS_EMM_YES == g_ulNasCsfbTauType2Flag)
        &&(PS_SUCC != LPS_OM_IsTestMode()))
    {
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_ProcSuitSysWhenRsmGu2LReg: LanZhou CSFB flag is valid, set reg domain ps.");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_ProcSuitSysWhenRsmGu2LReg_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    /* 如果是TMO卡，并且是重选、重定向或CCO，则变换到L下发起TAU应携带active标识 */
    if(NAS_EMM_YES == NAS_EMM_IsTmoUsimCard())
    {
        if((NAS_LMM_SYS_CHNG_TYPE_RSL == NAS_EMM_GetResumeType())
            ||(NAS_LMM_SYS_CHNG_TYPE_REDIR == NAS_EMM_GetResumeType())
            ||(NAS_LMM_SYS_CHNG_TYPE_CCO == NAS_EMM_GetResumeType()))
        {
            NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSuitSysWhenRsmGu2LReg: TMO card, save active flag ctrl.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSuitSysWhenRsmGu2LReg_ENUM,LNAS_FUNCTION_LABEL2);
            NAS_EMM_TAU_SaveEmmTmoActiveFlagCtrl(NAS_EMM_TMO_ACTIVE_FLAG_CTRL_VALID);
        }
    }

    switch ( NAS_EMM_GetResumeType())
    {
        case NAS_LMM_SYS_CHNG_TYPE_RSL:

            NAS_EMM_ProcSysWhenRsmGu2LRegReselect();
            break;

        case NAS_LMM_SYS_CHNG_TYPE_REDIR:

            NAS_EMM_ProcSysWhenRsmGu2LRegRedirect();
            break;
        case NAS_LMM_SYS_CHNG_TYPE_CCO:
            NAS_EMM_ProcSysWhenRsmGu2LRegCco();
            break;

        case NAS_LMM_SYS_CHNG_TYPE_HO:
            NAS_EMM_ProcSysWhenRsmGu2LHo();
            break;

        default:
            NAS_EMM_PUBU_LOG_INFO("NAS_EMM_ProcSuitSysWhenRsmGu2LReg: HO.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSuitSysWhenRsmGu2LReg_ENUM,LNAS_FUNCTION_LABEL3);
            break;
    }

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_ProcSuitSysWhenRrcOriRsmGu2LDeReg
 Description     : RRC触发GU到L的异系统变换，处于DEREG态下收到正常系统消息的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151      2012-7-12  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_ProcSuitSysWhenRrcOriRsmGu2LDeReg(VOS_VOID)
{
    VOS_UINT32                          ulSendResult = NAS_EMM_FAIL;

    /* 将状态转移至MS_DEREG + SS_DEREG_NORMAL_SERVICE状态 */
    NAS_EMM_PUBU_FSMTranState(          EMM_MS_DEREG,
                                        EMM_SS_DEREG_NORMAL_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    /* 若TIN ==  PTMSI，则获取GU的安全参数 */
    NAS_EMM_MmcRsmGetSecuPara();

    /* 向ATTACH模块发送EMM_INTRA_ATTACH_REQ消息 */
    ulSendResult = NAS_EMM_SendIntraAttachReq();
    if (NAS_EMM_FAIL == ulSendResult)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_ProcSuitSysWhenRrcOriRsmGu2LDeReg : Send IntraMsg Failure !");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_ProcSuitSysWhenRrcOriRsmGu2LDeReg_ENUM,LNAS_FAIL);
        return ;
    }

    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_ProcSuitSysWhenMmcOriRsmGu2LDeReg
 Description     : MMC触发GU到L的异系统变换，处于DEREG态下收到正常系统消息的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151      2012-7-12  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_ProcSuitSysWhenMmcOriRsmGu2LDeReg(VOS_VOID)
{
    VOS_UINT32                          ulSendResult;
    NAS_MM_TA_STRU                     *pstLastAttmpRegTa = NAS_EMM_NULL_PTR;
    NAS_MM_TA_STRU                      stCurTa;

    NAS_LMM_MEM_SET_S(&stCurTa, sizeof(NAS_MM_TA_STRU), 0, sizeof(NAS_MM_TA_STRU));

    /* 获取当前TA和上次尝试注册的TA信息 */
    NAS_EMM_GetCurrentTa(&stCurTa);
    pstLastAttmpRegTa                  = NAS_LMM_GetEmmInfoNetInfoLastAttmpRegTaAddr();

    /* TA与上次尝试发起注册的TA相同，有定时器，则应该等超时*/
    if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatch(pstLastAttmpRegTa, &stCurTa))
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_ProcSuitSysWhenMmcOriRsmGu2LDeReg: The same as last attempt TA.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSuitSysWhenMmcOriRsmGu2LDeReg_ENUM,LNAS_EMM_TA_NO_CHANGE);

        /* 澳电定制需求 3402定时器启动期间在GU下用户指定搜网到L立即发起注册 */
        if ((VOS_TRUE == g_ulNasAustraliaFlag)
          &&(NAS_EMMC_USER_SPEC_PLMN_YES == NAS_EMMC_GetUserSpecPlmnFlag()))

        {
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSuitSysWhenMmcOriRsmGu2LDeReg_ENUM,LNAS_EMM_UE_USG_SETTING);
            NAS_LMM_Stop3402Timer();
        }

        if(NAS_EMM_YES == NAS_EMM_Attach_IsTimerRunning())
        {
            return;
        }
    }

    /*重设attach attempt counter*/
    NAS_EMM_AttResetAttAttempCounter();

    /* 将状态转移至MS_DEREG + SS_DEREG_NORMAL_SERVICE状态 */
    NAS_EMM_PUBU_FSMTranState(          EMM_MS_DEREG,
                                        EMM_SS_DEREG_NORMAL_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    /* 若TIN ==  PTMSI，则获取GU的安全参数 */
    NAS_EMM_MmcRsmGetSecuPara();

    /* 向ATTACH模块发送EMM_INTRA_ATTACH_REQ消息 */
    ulSendResult = NAS_EMM_SendIntraAttachReq();
    if (NAS_EMM_FAIL == ulSendResult)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_ProcSuitSysWhenMmcOriRsmGu2LDeReg : Send IntraMsg Failure !");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSuitSysWhenMmcOriRsmGu2LDeReg_ENUM,LNAS_FAIL);
        return ;
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgMmcPlmnInd
 Description     : 收到搜网消息的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili     00132387     2011-11-21  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgMmcPlmnInd
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;
    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgMmcPlmnInd is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgMmcPlmnInd_ENUM,LNAS_ENTRY);

    /*根据RESUME前的状态进行状态迁移*/
    if(EMM_MS_REG == NAS_EMM_GetMsBefResume())
    {
        /*MMC激活L模后需要设置TAU原因的条件*/
        NAS_EMM_MmcResumeSetTauStartCause();

        /* 将状态转移至MS_DEREG + SS_DEREG_PLMN_SEARCH状态 */
        NAS_EMM_PUBU_FSMTranState(      EMM_MS_REG,
                                        EMM_SS_REG_PLMN_SEARCH,
                                        TI_NAS_EMM_STATE_NO_TIMER);
    }
    else
    {
        /* 如果RESUME之前子状态为NO IMSI */
        if (EMM_SS_DEREG_NO_IMSI == NAS_EMM_GetSsBefResume())
        {
            /* 将状态转移至MS_DEREG + SS_DEREG_NO_IMSI状态 */
            NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                        EMM_SS_DEREG_NO_IMSI,
                                        TI_NAS_EMM_STATE_NO_TIMER);
        }
        else
        {
            /* 将状态转移至MS_DEREG + SS_DEREG_NORMAL_SERVICE状态 */
            NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                        EMM_SS_DEREG_PLMN_SEARCH,
                                        TI_NAS_EMM_STATE_NO_TIMER);
        }
    }

    return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMM_ResumeProcPTMSITau
 Description     : 处理TIN值为P-TMSI时触发的TAU

 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2012-2-28  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ResumeProcPTMSITau( VOS_VOID )
{

    NAS_EMM_TAU_LOG2_INFO("NAS_EMM_ProcPTMSITau:NAS_EMM_TAU_GetEmmT3412ExpCtrl() = ,\
        NAS_LMM_GetEmmInfoRegDomain()", NAS_LMM_GetEmmInfoT3412ExpCtrl(),
        NAS_LMM_GetEmmInfoRegDomain());
    /* coverity[unchecked_value] */
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_ResumeProcPTMSITau_ENUM,LNAS_FUNCTION_LABEL1,
                                        NAS_LMM_GetEmmInfoT3412ExpCtrl(),
                                        NAS_LMM_GetEmmInfoRegDomain());

    if ((NAS_EMM_T3412_EXP_YES_REG_NO_AVALABLE_CELL == NAS_LMM_GetEmmInfoT3412ExpCtrl())
        && (NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain()))
    {
        /* 将注册域改为PS，是为了回到REG+NORMAL_SERVICE态后，如果要发起联合TAU，则
            TAU类型应该填为combined TA/LA updating with IMSI attach */
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

    }
    /*NAS_EMM_TAU_SaveEmmTAUStartCause(     NAS_EMM_TAU_START_CAUSE_SYSINFO);*/
    NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
    NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MmcResumeSetTauStartCause
 Description     : MMC激活L模后，需要设置TAU启动原因的条件
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-11-22  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_MmcResumeSetTauStartCause(VOS_VOID)
{
    MMC_LMM_TIN_TYPE_ENUM_UINT32            enTinType   = MMC_LMM_TIN_BUTT;

    enTinType = NAS_EMM_GetTinType();

    if (NAS_RELEASE_R11)
    {
        NAS_EMM_IsG2LGmmSuspendAndIsrAct();
    }

    if(((NAS_EMM_LAU_OR_COMBINED_RAU_HAPPENED == NAS_LMM_GetEmmInfoLauOrComRauFlag())
        || (NAS_EMM_SRVCC_HAPPENED == NAS_LMM_GetEmmInfoSrvccFlag()))
        && (NAS_EMM_YES == NAS_EMM_IsCsPsUeMode()))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MmcResumeSetTauStartCause:LAU OR COMBINED RAU");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcResumeSetTauStartCause_ENUM,LNAS_EMM_LAU_OR_COMB_RAU);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    if (NAS_EMM_YES == NAS_EMM_IsEmcCsfbHappenedAndLaiChangWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_MmcResumeSetTauStartCause:EMC CSFB,LAI CHANG ");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MmcResumeSetTauStartCause_ENUM,LNAS_EMM_EMC_CSFB_LAI_CHG);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    /*c)when the UE enters EMM-REGISTERED.NORMAL-SERVICE and the UE's TIN indicates "P-TMSI"*/
    if (MMC_LMM_TIN_P_TMSI == enTinType)
    {
        NAS_EMM_ResumeProcPTMSITau();
        return;
    }

    /* d)when the UE performs an intersystem change from A/Gb or Iu mode to S1 mode,
           and the UE previously either performed a location area update procedure
           or a combined routing area update procedure in A/Gb or Iu mode,
           in order to re-establish the SGs association. In this case the EPS update
           type IE shall be set to "combined TA/LA updating with IMSI attach"; */
    if (NAS_EMM_LAU_OR_COMBINED_RAU_HAPPENED == NAS_LMM_GetEmmInfoLauOrComRauFlag())
    {
        /*NAS_EMM_TAU_SaveEmmTAUStartCause(     NAS_EMM_TAU_START_CAUSE_SYSINFO);*/
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);
    }

    /* For case c, if the TIN indicates "RAT-related TMSI" and the EPS services were not resumed before
    returning to S1 mode, the UE shall set the TIN to "P-TMSI" before initiating
    the combined tracking area updating procedure*/
    if (NAS_RELEASE_R11)
    {
        /* 获取恢复方向 */

        if (NAS_EMM_YES == NAS_EMM_IsG2LAndGmmSuspendWithCsPsUeMode())
        {
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
            NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);
        }
    }

    return;
}



/*****************************************************************************
 Function Name   : NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgAreaLostInd
 Description     : 收到丢网消息处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-11-22  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgAreaLostInd
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    (void)ulMsgId;
    (void)pMsgStru;
    NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgAreaLostInd:NAS_EMM_GetMsBefResume() =",
                            NAS_EMM_GetMsBefResume());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgAreaLostInd_ENUM,LNAS_FUNCTION_LABEL1,
                            NAS_EMM_GetMsBefResume());

    /* 关闭当前EMM的除Del Forb Ta Proid之外的状态定时器, Del Forb Ta Proid只能在关机时停止*/
    NAS_LMM_StopAllStateTimerExceptDelForbTaProidTimer();

    /*根据RESUME前的状态进行状态迁移*/
    if(EMM_MS_DEREG == NAS_EMM_GetMsBefResume())
    {
        /* 如果RESUME之前是NO IMSI态 */
        if(EMM_SS_DEREG_NO_IMSI== NAS_EMM_GetSsBefResume())
        {
            /* 将状态转移至MS_DEREG + SS_DEREG_NO_IMSI状态 */
            NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                        EMM_SS_DEREG_NO_IMSI,
                                        TI_NAS_EMM_STATE_NO_TIMER);
        }
        else
        {
            /* 将状态转移至MS_DEREG + SS_DEREG_NO_CELL_AVAILABLE状态 */
            NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                        EMM_SS_DEREG_NO_CELL_AVAILABLE,
                                        TI_NAS_EMM_STATE_NO_TIMER);
        }
        return NAS_LMM_MSG_HANDLED;
    }

    /*MMC激活L模后需要设置TAU原因的条件*/
    NAS_EMM_MmcResumeSetTauStartCause();

    /* 将状态转移至MS_REG + SS_REG_NO_CELL_AVAILABLE状态 */
    NAS_EMM_PUBU_FSMTranState(          EMM_MS_REG,
                                        EMM_SS_REG_NO_CELL_AVAILABLE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

    return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgAppDetachReq
 Description     : MMC触发的激活等系统消息过程中收到MMC的DETACH消息处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151      2013-12-30  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgMmcDetachReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    (void)ulMsgId;
    (void)pMsgStru;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgMmcDetachReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgMmcDetachReq_ENUM,LNAS_ENTRY);

    /* 通知ESM执行了本地DETACH */
    NAS_EMM_EsmSendStatResult(EMM_ESM_ATTACH_STATUS_DETACHED);

    /* 自研CL版本，PS DETACH通知ESM删除所有EHRPD相关承载记录 */
    NAS_EMM_SndEsmClearAllClBearerNotify();

    /* 给MMC回DETACH成功 */
    NAS_EMM_AppSendDetCnf(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* 有可能是处于紧急注册的无卡状态 */
    if (NAS_LMM_SIM_STATUS_UNAVAILABLE == NAS_LMM_GetSimState())
    {
        /* 无卡 */
        NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                               EMM_SS_DEREG_NO_IMSI,
                               TI_NAS_EMM_STATE_NO_TIMER);
    }
    else
    {
        /* 有卡 */
        NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                               EMM_SS_DEREG_PLMN_SEARCH,
                               TI_NAS_EMM_STATE_NO_TIMER);
    }

    /* 本地DETACH释放资源:动态内存、赋初值 */
    NAS_LMM_DeregReleaseResource();

    return NAS_LMM_MSG_HANDLED;

}

/*****************************************************************************
 Function Name   : NAS_EMM_MmcOriResumeCheckTauFlag
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.FTY         2012-02-27   Draft Enact

*****************************************************************************/
VOS_UINT32   NAS_EMM_MmcOriResumeCheckTauFlag(VOS_VOID)
{
    /* 如果TA不在TAI List中，触发TA-Updating类型的TAU*/
    if (NAS_EMM_FAIL == NAS_EMM_TAU_IsCurrentTAInTaList())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MmcOriResumeCheckTauFlag:TA not in TAI List.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcOriResumeCheckTauFlag_ENUM,LNAS_EMM_TA_NOT_IN_TA_LIST);

        /*NAS_EMM_TAU_SaveEmmTAUStartCause(     NAS_EMM_TAU_START_CAUSE_SYSINFO);*/
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);

        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_NOT_IN_TAI_LIST);
        return NAS_EMM_YES;
    }

    /* 如果期间发生过ESM本地修改承载上下文*/
    if(NAS_EMM_EPS_BEARER_STATUS_CHANGEED == NAS_EMM_GetEpsContextStatusChange())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MmcOriResumeCheckTauFlag:Bearer Status Change.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcOriResumeCheckTauFlag_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);

        /*NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_BEARER_CNTXT_LOCAL_CHANGED);*/
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_BEARER_STATUS_CHANGEED);
        return NAS_EMM_YES;
    }

    /* 如果期间发生过UE_NET_CAP or DRX改变，触发TA-Updating TAU*/
    if(NAS_EMM_YES == NAS_LMM_GetEmmInfoDrxNetCapChange())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MmcOriResumeCheckTauFlag:DrxOrNetCap Change.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcOriResumeCheckTauFlag_ENUM,LNAS_FUNCTION_LABEL2);
        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);

        /*NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_BEARER_CNTXT_LOCAL_CHANGED);*/
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_DRX_CHANGEED);
        return NAS_EMM_YES;
    }

    /*当前注册域为PS,并且有能力发起CS域的注册*/
    if (NAS_EMM_YES == NAS_EMM_TAU_CanTriggerComTauWithIMSI())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MmcOriResumeCheckTauFlag:current reg domain=PS,can register in cs domain.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcOriResumeCheckTauFlag_ENUM,LNAS_FUNCTION_LABEL3);

        /*NAS_EMM_TAU_SaveEmmTAUStartCause(     NAS_EMM_TAU_START_CAUSE_SYSINFO);*/
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);

        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_ATTACH_NON_EPS);
        return NAS_EMM_YES;
    }

    /*EU值不是EU1*/
    if(EMM_US_UPDATED_EU1 != NAS_EMM_TAUSER_GetAuxFsmUpStat() )
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MmcOriResumeCheckTauFlag: EU is not EU1");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcOriResumeCheckTauFlag_ENUM,LNAS_FUNCTION_LABEL4);
        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);

        /*NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_BEARER_CNTXT_LOCAL_CHANGED);*/
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_NOT_EU1);
        return NAS_EMM_YES;
    }

    /*对RRC Rel原因标识进行判断*/
    if(NAS_EMM_YES == NAS_EMM_TAU_RrcRelCauseTriggerTau())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MmcOriResumeCheckTauFlag:rrc rel cause");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcOriResumeCheckTauFlag_ENUM,LNAS_EMM_REL_CAUSE);

        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);
        return NAS_EMM_YES;
    }


    /* 如果UE无线能力发生变更 */
    if(NAS_LMM_UE_RADIO_CAP_NOT_CHG != NAS_LMM_GetEmmInfoUeRadioCapChgFlag())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MmcOriResumeCheckTauFlag: UE radio capability change. ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcOriResumeCheckTauFlag_ENUM,LNAS_FUNCTION_LABEL5);
        /*NAS_EMM_TAU_SaveEmmTAUStartCause( NAS_EMM_TAU_START_CAUSE_INTRA_TAU_REQ);*/
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_RADIO_CAP_CHANGE);
        return NAS_EMM_YES;
    }


    /* 处理定时器T3412超时 */
    if (NAS_LMM_MSG_HANDLED == NAS_EMM_RegSomeStateMsgSysInfoT3412ExpProc())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MmcOriResumeCheckTauFlag:T3412 Exp.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcOriResumeCheckTauFlag_ENUM,LNAS_TIMER_EXPIRED);

        NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);
        return NAS_EMM_YES;
    }

    if(NAS_EMM_YES == NAS_EMM_GetVoiceDomainChange() )
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateStartTAUNeeded: VOICE DOMAIN CHANG ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcOriResumeCheckTauFlag_ENUM,LNAS_FUNCTION_LABEL6);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_VOICE_DOMAIN_CHANGE);
        /* 新增入参TAU发起原因 */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_VOICE_DOMAIN_CHANGE);
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MmcOriResumeSysInfoProc
 Description     : MMC激活L模时收到系统消息触发TAU的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387     2011-11-22  Draft Enact
    2.sunjitan 00193151  2012-07-12 Modify: Last TA维护，修改触发TAU和ATTACH的判定逻辑
*****************************************************************************/
VOS_VOID  NAS_EMM_MmcOriResumeSysInfoProc(VOS_VOID)
{
    /* 澳电定制需求 3402定时器启动期间在GU下用户指定搜网到L立即发起注册 */
    if ((VOS_TRUE == g_ulNasAustraliaFlag)
      &&(NAS_EMMC_USER_SPEC_PLMN_YES == NAS_EMMC_GetUserSpecPlmnFlag()))
    {
        NAS_LMM_Stop3402Timer();
    }

    /* 如果T3411/3402在运行，且需要等超时，则先将该场景识别出来 */
    if (NAS_EMM_SUCC == NAS_EMM_RegStateMmcOriResumeSysInfoRecogniseWaitTimerExp())
    {
        return;
    }

    /* 注册态下收到系统消息,不需要等T3411或者T3402超时的公共处理 */

    NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc();

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcSuitSysWhenMmcOriRsmGu2LReg
 Description     : MMC触发GU到L的异系统变换，处于REG态下收到正常系统消息的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2013-3-25  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_ProcSuitSysWhenMmcOriRsmGu2LReg(VOS_VOID)
{

    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_ProcSuitSysWhenMmcOriRsmGu2LReg is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcSuitSysWhenMmcOriRsmGu2LReg_ENUM,LNAS_ENTRY);
    if (NAS_RELEASE_CTRL)
    {
        if(NAS_MML_PS_BEARER_STATE_INACTIVE == NAS_EMM_IsEpsBearStatusAct())
        {
            NAS_EMM_GU2LNoEpsBearProc();
        }
        else
        {
            /* 进入收到SYS_INFO的公共处理*/
            NAS_EMM_MmcOriResumeSysInfoProc();
        }
    }
    else
    {
        /* 进入收到SYS_INFO的公共处理*/
        NAS_EMM_MmcOriResumeSysInfoProc();
    }
    return;
}



VOS_UINT32  NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgSysInfoInd
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    EMMC_EMM_SYS_INFO_IND_STRU         *pstsysinfo;

    (VOS_VOID)ulMsgId;
    NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgSysInfoInd: ResumeType = ",
                        NAS_EMM_GetResumeType());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgSysInfoInd_ENUM,LNAS_EMM_RESUME_TYPE,
                        NAS_EMM_GetResumeType());

    pstsysinfo = (EMMC_EMM_SYS_INFO_IND_STRU *)pMsgStru;
    /*问题背景:主叫走CSFB流程被用户快速挂断电话，此时走CSFB回退流程，
    回退到L的时候，由于TA在TALIST里面，所以不会发起TAU跟网侧交互，但是
    此时核心网PS域已经开始往2/3G迁移，这样会导致被叫不通，或者收不到短信
    改动:增加标识维护识别上面的这种场景，在回到L的时候保证发起TAU*/
    if(PS_TRUE == NAS_EMM_GetCsfbProcedureFlag())
    {
         NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);
         NAS_EMM_SetCsfbProcedureFlag(PS_FALSE);
    }

    if(((NAS_EMM_LAU_OR_COMBINED_RAU_HAPPENED == NAS_LMM_GetEmmInfoLauOrComRauFlag())
        || (NAS_EMM_SRVCC_HAPPENED == NAS_LMM_GetEmmInfoSrvccFlag()))
        && (NAS_EMM_YES == NAS_EMM_IsCsPsUeMode()))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgSysInfoInd:LAU OR COMBINED RAU");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgSysInfoInd_ENUM,LNAS_EMM_LAU_OR_COMB_RAU);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    if (NAS_EMM_YES == NAS_EMM_IsEmcCsfbHappenedAndLaiChangWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgSysInfoInd:EMC CSFB,LAI CHANG ");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgSysInfoInd_ENUM,LNAS_EMM_EMC_CSFB_LAI_CHG);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    /* 如果RESUME之前状态为MS_DEREG + SS_DEREG_NO_IMSI */
    if (EMM_SS_DEREG_NO_IMSI == NAS_EMM_GetSsBefResume())
    {
        /* 将状态转移至MS_DEREG + SS_DEREG_NO_IMSI状态 */
        NAS_EMM_PUBU_FSMTranState(  EMM_MS_DEREG,
                                    EMM_SS_DEREG_NO_IMSI,
                                    TI_NAS_EMM_STATE_NO_TIMER);

        /*向MMC发送LMM_MMC_ATTACH_CNF或LMM_MMC_ATTACH_IND消息*/
        NAS_EMM_AppSendAttRstDefaultReqType(MMC_LMM_ATT_RSLT_FAILURE);;

        return NAS_LMM_MSG_HANDLED;
    }


    if ((EMMC_EMM_NO_FORBIDDEN != pstsysinfo->ulForbiddenInfo)
        || (EMMC_EMM_CELL_STATUS_ANYCELL == pstsysinfo->ulCellStatus))
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgSysInfoInd: Forb sys info");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgSysInfoInd_ENUM,LNAS_EMM_FORB_INFO);

        /*根据RESUME前的状态进行状态迁移*/
        if(EMM_MS_DEREG == NAS_EMM_GetMsBefResume())
        {
            /*修改状态：进入主状态DEREG子状态DEREG_LIMITED_SERVICE*/
            NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                    EMM_SS_DEREG_LIMITED_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

            NAS_EMM_SetAttType();

            /*向MMC发送LMM_MMC_ATTACH_CNF或LMM_MMC_ATTACH_IND消息*/
            NAS_EMM_AppSendAttRsltForb(pstsysinfo->ulForbiddenInfo);
        }
        else
        {
            if (NAS_LMM_REG_STATUS_NORM_REGED == NAS_LMM_GetEmmInfoRegStatus())
            {
                /*MMC激活L模后需要设置TAU原因的条件*/
                NAS_EMM_MmcResumeSetTauStartCause();
                NAS_EMM_RegForbidSysInfoProc(pstsysinfo->ulForbiddenInfo);
            }
            else
            {
                NAS_EMM_MmcOriResumeSysInfoProc();
            }
        }

        return NAS_LMM_MSG_HANDLED;
    }

    /*根据RESUME前的状态进行状态迁移*/
    if(EMM_MS_DEREG == NAS_EMM_GetMsBefResume())
    {
        NAS_EMM_ProcSuitSysWhenMmcOriRsmGu2LDeReg();
    }
    else
    {
        /* 判断承载上下文是否激活，如果未激活，则本地DETACH，转入DEREG+NORMAL_SERVICE状态；
            发起ATTACH流程；
            如果激活，则保持原有处理 */
        NAS_EMM_ProcSuitSysWhenMmcOriRsmGu2LReg();
    }
    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgT3412Exp
 Description     : 收到T3412超时处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-11-22  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgT3412Exp
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    (void)ulMsgId;
    (void)pMsgStru;
    NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgT3412Exp:NAS_EMM_GetMsBefResume() =",
                            NAS_EMM_GetMsBefResume());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgT3412Exp_ENUM,LNAS_FUNCTION_LABEL1,
                            NAS_EMM_GetMsBefResume());

    /*根据RESUME前的状态进行状态迁移*/
    if(EMM_MS_DEREG == NAS_EMM_GetMsBefResume())
    {
        return NAS_LMM_MSG_HANDLED;
    }

    if (NAS_RELEASE_R11)
    {
        NAS_EMM_IsG2LGmmSuspendAndIsrAct();
    }

    /*设置周期TAU定制器超时标志*/
    /* 针对GCF9.2.3.1.5 用例，UE丢网，MMC发起搜网，搜网期间T3412超时，发起的TAU类型是combined TAU with IMSI类型的*/
    NAS_LMM_SetEmmInfoT3412ExpCtrl(NAS_EMM_T3412_EXP_YES_REG_NO_AVALABLE_CELL);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgBearStatusReq
 Description     : 收到承载状态请求消息处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-11-22  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgBearStatusReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    (void)ulMsgId;
    (void)pMsgStru;
    NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgBearStatusReq:NAS_EMM_GetMsBefResume() =",
                            NAS_EMM_GetMsBefResume());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgBearStatusReq_ENUM,LNAS_FUNCTION_LABEL1,
                            NAS_EMM_GetMsBefResume());

    /*根据RESUME前的状态进行状态迁移*/
    if(EMM_MS_DEREG == NAS_EMM_GetMsBefResume())
    {
        return NAS_LMM_MSG_HANDLED;
    }

    if (NAS_RELEASE_R11)
    {
        NAS_EMM_IsG2LGmmSuspendAndIsrAct();
    }

    /* 设置承载上下文变化*/
    NAS_EMM_SetEpsContextStatusChange(NAS_EMM_EPS_BEARER_STATUS_CHANGEED);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsResumeReverseMsgRrcAccessGrantInd
 Description     : Resume.WtCmResume
                   Resume.RrcOriWtSysInfo
                   两个状态下收到LRRC_LMM_ACCESS_GRANT_IND消息的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-11-29  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsResumeReverseMsgRrcAccessGrantInd(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru  )
{
    VOS_UINT32                          ulRslt;
    (void)ulMsgId;
    (void)pMsgStru;
    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_MsResumeReverseMsgRrcAccessGrantInd entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsResumeReverseMsgRrcAccessGrantInd_ENUM,LNAS_ENTRY);

    /* 检查ResumeType，如果不是重选回退，则打印出错信息*/
    if(LRRC_LMM_SYS_CHNG_TYPE_RESEL_REVERSE != NAS_EMM_GetResumeType())
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_MsResumeReverseMsgRrcAccessGrantInd:ResumeType Err.");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsResumeReverseMsgRrcAccessGrantInd_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_HANDLED;
    }

    /* 如果是重选回退，则与挂起态下的处理相同*/
    ulRslt = NAS_EMM_MsSuspendSsRrcOriMsgRrcAccessGrantInd(ulMsgId, pMsgStru);

    return ulRslt;
}

VOS_UINT32  NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgIntraTauReq( VOS_UINT32  ulMsgId,
                                                        VOS_VOID   *pMsgStru )
{
    NAS_LMM_INTRA_TAU_REQ_STRU         *pIntraTauReq = NAS_EMM_NULL_PTR;
    (VOS_VOID)ulMsgId;
    pIntraTauReq    = (NAS_LMM_INTRA_TAU_REQ_STRU*)pMsgStru;

    /* 打印进入该函数*/
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgIntraTauReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgIntraTauReq_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查*/
    if(NAS_EMM_NULL_PTR                 == pMsgStru)
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgIntraTauReq PARA NULL!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgIntraTauReq_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_MSG_DISCARD;
    }

    if((NAS_LMM_SYS_CHNG_TYPE_RSL == NAS_EMM_GetResumeType()) ||
        (NAS_LMM_SYS_CHNG_TYPE_HO == NAS_EMM_GetResumeType()) ||
        (NAS_LMM_SYS_CHNG_TYPE_CCO == NAS_EMM_GetResumeType()) ||
        (NAS_LMM_SYS_CHNG_TYPE_REDIR == NAS_EMM_GetResumeType()))
    {
        NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgBearStatusReq:NAS_EMM_GetMsBefResume() =",
                            NAS_EMM_GetMsBefResume());
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgIntraTauReq_ENUM,LNAS_FUNCTION_LABEL1,
                            NAS_EMM_GetMsBefResume());

        /*根据RESUME前的状态进行状态迁移*/
        if(EMM_MS_DEREG == NAS_EMM_GetMsBefResume())
        {
            return NAS_LMM_MSG_HANDLED;
        }

        /*设置DRX或NetCapability改变标志*/
        if(NAS_LMM_INTRA_TAU_TYPE_PARA_CHANGE == pIntraTauReq->enIntraTauType)
        {
            NAS_LMM_SetEmmInfoDrxNetCapChange( NAS_EMM_YES);
        }
    }
    else
    {
        /*回退过程的处理*/
        NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgBearStatusReq:NAS_EMM_GetMsBefResume() =",
                                    NAS_EMM_GetMsBefSuspend());
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsResumeSsRrcOriWaitSysInfoIndMsgIntraTauReq_ENUM,LNAS_FUNCTION_LABEL2,
                                    NAS_EMM_GetMsBefSuspend());

        /*根据SUSPEND前的状态进行状态迁移*/
        if(EMM_MS_DEREG == NAS_EMM_GetMsBefSuspend())
        {
            return NAS_LMM_MSG_HANDLED;
        }

        /*设置DRX或NetCapability改变标志*/
        if(NAS_LMM_INTRA_TAU_TYPE_PARA_CHANGE == pIntraTauReq->enIntraTauType)
        {
            NAS_LMM_SetEmmInfoDrxNetCapChange( NAS_EMM_YES);
        }
    }

    return NAS_LMM_MSG_HANDLED;
}
/*lint +e961*/
/*lint +e960*/

VOS_UINT32  NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgIntraTauReq( VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru )
{
    NAS_LMM_INTRA_TAU_REQ_STRU         *pIntraTauReq = NAS_EMM_NULL_PTR;
    (VOS_VOID)ulMsgId;
    pIntraTauReq    = (NAS_LMM_INTRA_TAU_REQ_STRU*)pMsgStru;

    /* 打印进入该函数*/
    NAS_EMM_TAU_LOG_INFO( "NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgIntraTauReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgIntraTauReq_ENUM,LNAS_ENTRY);

    /* 函数输入指针参数检查*/
    if(NAS_EMM_NULL_PTR                 == pMsgStru)
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgIntraTauReq PARA NULL!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsResumeSsMmcOriWaitSysInfoIndMsgIntraTauReq_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*如果RESUME前的状态DEREG，则不设置*/
    if(EMM_MS_DEREG == NAS_EMM_GetMsBefResume())
    {
        return NAS_LMM_MSG_HANDLED;
    }
    if (NAS_RELEASE_R11)
    {
        NAS_EMM_IsG2LGmmSuspendAndIsrAct();
    }
    /*设置DRX或NetCapability改变标志*/
    if(NAS_LMM_INTRA_TAU_TYPE_PARA_CHANGE == pIntraTauReq->enIntraTauType)
    {
        NAS_LMM_SetEmmInfoDrxNetCapChange( NAS_EMM_YES);
    }

    return NAS_LMM_MSG_HANDLED;
}



VOS_UINT32  NAS_LMM_PreProcMmcImsVoiceCapChangeNotify(MsgBlock *    pMsg )
{

    MMC_LMM_IMS_VOICE_CAP_CHANGE_NOTIFY_STRU     *pstImsVoiceCapNotify;
    NAS_EMM_PUB_INFO_STRU                        *pstPubInfo;
    MMC_LMM_IMS_VOICE_CAP_ENUM_UINT8              enImsaVoiceCap;

    NAS_EMM_PUBU_LOG_INFO("NAS_LMM_PreProcMmcImsVoiceCapChangeNotify is entered");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcImsVoiceCapChangeNotify_ENUM,LNAS_ENTRY);

    pstImsVoiceCapNotify = (VOS_VOID*)pMsg;
    pstPubInfo = NAS_LMM_GetEmmInfoAddr();

    enImsaVoiceCap = pstPubInfo->enImsaVoiceCap;

    pstPubInfo->enImsaVoiceCap = pstImsVoiceCapNotify->enImsVoiceCap;

    if ((MMC_LMM_IMS_VOICE_CAP_UNAVAILABLE == enImsaVoiceCap)
        && (MMC_LMM_IMS_VOICE_CAP_AVAILABLE == pstImsVoiceCapNotify->enImsVoiceCap))
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_LMM_PreProcMmcImsVoiceCapChangeNotify: IMS voice avail");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcImsVoiceCapChangeNotify_ENUM,LNAS_EMM_IMS_VOICE_AVAIL);

        if ((NAS_LMM_CUR_LTE_ACTIVE == NAS_EMM_GetCurLteState())
            && ((NAS_EMM_PUBU_CHK_STAT_VALID(EMM_MS_REG,EMM_SS_REG_NORMAL_SERVICE))
                ||(NAS_EMM_PUBU_CHK_STAT_VALID(EMM_MS_REG,EMM_SS_REG_ATTEMPTING_TO_UPDATE))
                ||(NAS_EMM_PUBU_CHK_STAT_VALID(EMM_MS_REG,EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM))))
        {
            /*p）when the UE activates mobility management for IMS voice termination as specified in 3GPP TS 24.008 [13],
            annex P.2, and the TIN indicates "RAT-related TMSI";*/
            /*IMS voice from not available to available,ISR激活，start TAU*/
            /*lint -e960*/
            if ((NAS_EMM_YES == NAS_EMM_IsAnnexP2ConditionSatisfied())
                && (MMC_LMM_TIN_RAT_RELATED_TMSI == NAS_EMM_GetTinType()))
            {
                NAS_EMM_PUBU_LOG_INFO("NAS_LMM_PreProcMmcImsVoiceCapChangeNotify: start TAU");
                TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcImsVoiceCapChangeNotify_ENUM,LNAS_FUNCTION_LABEL1);
                NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

                /* 新增入参TAU发起原因 */
                NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_P2);
            }
            /*lint +e960*/
        }

    }

    return NAS_LMM_MSG_HANDLED;
}




/*****************************************************************************
 Function Name   : NAS_LMM_PreProcMmcImsVoiceDomainChangeInd
 Description     : IMS voice domain通知
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen 00209181 2015-02-26  Draft Enact
    2.yanglei  00307272 2015-07-28  可维可测，设置VOICE DOMAIN时上报UE能力

*****************************************************************************/
VOS_UINT32  NAS_LMM_PreProcMmcImsVoiceDomainChangeInd(MsgBlock *    pMsg )
{

    MMC_LMM_VOICE_DOMAIN_CHANGE_IND_STRU        *pstImsVoiceDomainChangInd;
    NAS_EMM_PUB_INFO_STRU                        *pstPubInfo;
    NAS_LMM_VOICE_DOMAIN_ENUM_UINT32            enVoiceDomain;
    VOS_UINT32                                  ulCurEmmStat;
    NAS_LMM_PTL_TI_ENUM_UINT16                  enPtlTimerId;
    MMC_LMM_TAU_RSLT_ENUM_UINT32                ulTauRslt = MMC_LMM_TAU_RSLT_BUTT;

    NAS_EMM_PUBU_LOG_INFO("NAS_LMM_PreProcMmcImsVoiceDomainChangeInd is entered");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcImsVoiceDomainChangeInd_ENUM,LNAS_ENTRY);

    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT,
                                            NAS_EMM_CUR_SUB_STAT);

    pstImsVoiceDomainChangInd = (VOS_VOID*)pMsg;
    pstPubInfo = NAS_LMM_GetEmmInfoAddr();

    enVoiceDomain = pstPubInfo->ulVoiceDomain;

    //pstPubInfo->ulVoiceDomain = pstImsVoiceDomainChangInd->enVoiceDomain;

    /* 如果voice domain没有发生变化，直接退出 */
    if (enVoiceDomain == pstImsVoiceDomainChangInd->enVoiceDomain)
    {
        return NAS_LMM_MSG_HANDLED;
    }

    /* 如果当前处于从模，则直接退出 */
    if (NAS_LMM_CUR_LTE_SUSPEND == NAS_EMM_GetCurLteState())
    {
        NAS_LMM_SetVoiceDomain(pstImsVoiceDomainChangInd->enVoiceDomain);
        /* 设置触发TAU的标识 */
        NAS_EMM_SetVoiceDomainChange(VOS_TRUE);
        return NAS_LMM_MSG_HANDLED;
    }

    /* 在开机或者关机，DETACH过程中，不处理该消息 */
    if((EMM_MS_NULL == NAS_EMM_CUR_MAIN_STAT) ||
        (EMM_MS_DEREG == NAS_EMM_CUR_MAIN_STAT) ||
        (EMM_MS_DEREG_INIT == NAS_EMM_CUR_MAIN_STAT))
    {
        return NAS_LMM_MSG_HANDLED;
    }

    if( (NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
        || (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440)))
    {
        return NAS_LMM_STORE_HIGH_PRIO_MSG;
    }

    if(NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState())
    {
        /* 停止 定时器*/
        NAS_LMM_StopStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_CONN_CNF);
    }

    switch(ulCurEmmStat)
    {
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_ESM_PDN_RSP):
                NAS_LMM_SetVoiceDomain(pstImsVoiceDomainChangInd->enVoiceDomain);
                break;

        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_RRC_DATA_CNF):
                return NAS_LMM_STORE_LOW_PRIO_MSG;

        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE):
                NAS_LMM_SetVoiceDomain(pstImsVoiceDomainChangInd->enVoiceDomain);
                /* 设置触发TAU的标识 */
                NAS_EMM_SetVoiceDomainChange(VOS_TRUE);
                NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_VOICE_DOMAIN_CHANGE);
                /* 新增入参TAU发起原因 */
                NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_VOICE_DOMAIN_CHANGE);
                break;

        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM):
                NAS_LMM_SetVoiceDomain(pstImsVoiceDomainChangInd->enVoiceDomain);
                /* 设置触发TAU的标识 */
                NAS_EMM_SetVoiceDomainChange(VOS_TRUE);
                /* 如果T3411启动，或者3402启动，则等定时器超时 */
                if (NAS_EMM_YES != NAS_EMM_IsT3411orT3402Running(&enPtlTimerId))
                {
                    NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_VOICE_DOMAIN_CHANGE);
                    /* 新增入参TAU发起原因 */
                    NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_VOICE_DOMAIN_CHANGE);
                }
                break;

        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_WAIT_ACCESS_GRANT_IND):
                NAS_LMM_SetVoiceDomain(pstImsVoiceDomainChangInd->enVoiceDomain);
                /* 设置触发TAU的标识 */
                NAS_EMM_SetVoiceDomainChange(VOS_TRUE);
                 /* 看信令是否被BAR，否: TAU;   是: 不做特殊处理 */
                if (NAS_EMM_SUCC != NAS_EMM_JudgeBarType(NAS_EMM_BAR_TYPE_MO_SIGNAL))
                {
                    NAS_LMM_PUBM_LOG_NORM("NAS_LMM_PreProcMmcImsVoiceDomainChangeInd: TAU  start");
                    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcImsVoiceDomainChangeInd_ENUM,LNAS_FUNCTION_LABEL1);

                    NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_VOICE_DOMAIN_CHANGE);
                    /* 新增入参TAU发起原因 */
                    NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_VOICE_DOMAIN_CHANGE);
                }
                break;

        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF):
                return NAS_LMM_STORE_LOW_PRIO_MSG;

        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_TAU_INIT, EMM_SS_TAU_WAIT_CN_TAU_CNF):
                NAS_LMM_SetVoiceDomain(pstImsVoiceDomainChangInd->enVoiceDomain);
                /* 设置触发TAU的标识 */
                NAS_EMM_SetVoiceDomainChange(VOS_TRUE);
                /* 终止原有TAU流程，重新发起 */
                ulTauRslt = MMC_LMM_TAU_RSLT_FAILURE;
                NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);
                NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_TAU_T3430);

                NAS_EMM_AdStateConvert(EMM_MS_REG,
                                       EMM_SS_REG_PLMN_SEARCH,
                                       TI_NAS_EMM_STATE_NO_TIMER);

                NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
                break;

        /* SERVICE过程中，终止原有SERVICE流程，重新发起TAU */
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF):
                NAS_LMM_SetVoiceDomain(pstImsVoiceDomainChangInd->enVoiceDomain);

                /* 设置触发TAU的标识 */
                NAS_EMM_SetVoiceDomainChange(VOS_TRUE);

                NAS_EMM_SER_AbnormalOver();


                /*设置流程冲突标志位*/
                NAS_EMM_TAU_SaveEmmCollisionCtrl(NAS_EMM_COLLISION_SERVICE);

                /* 转入REG.PLMN-SEARCH等系统消息 */
                NAS_EMM_AdStateConvert(EMM_MS_REG,
                                       EMM_SS_REG_PLMN_SEARCH,
                                       TI_NAS_EMM_STATE_NO_TIMER);

                /* 全都发释放，RRC在空闲态和连接态处理基本相同 */
                /* 如果处于连接态，直接发送释放消息 */
                NAS_EMM_PUBU_LOG_NORM("NAS_EMM_MsTauSerRcvLrrcSyscfgCnfProc: Connected! SndRrcRelReq. ");
                TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcImsVoiceDomainChangeInd_ENUM,LNAS_FUNCTION_LABEL2);

                /*发送RRC_MM_REL_REQ*/
                NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
                break;

        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_AUTH_INIT, EMM_SS_AUTH_WAIT_CN_AUTH):
                return NAS_LMM_STORE_HIGH_PRIO_MSG;

        default:
                NAS_LMM_SetVoiceDomain(pstImsVoiceDomainChangInd->enVoiceDomain);
                /* 设置触发TAU的标识 */
                NAS_EMM_SetVoiceDomainChange(VOS_TRUE);
                break;
    }

    return NAS_LMM_MSG_HANDLED;
}
/*****************************************************************************
 Function Name   : NAS_LMM_PreProcMmcCsConnStatusNotify
 Description     : CS域建链通知
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangchen 00209181     2015-04-15  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_PreProcMmcCsConnStatusNotify(MsgBlock *    pMsg )
{

    MMC_LMM_CS_CONN_STATUS_NOTIFY_STRU     *pstCsConnStatusNotify;

    NAS_EMM_PUBU_LOG_INFO("NAS_LMM_PreProcMmcCsConnStatusNotify is entered");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcCsConnStatusNotify_ENUM,LNAS_ENTRY);

    pstCsConnStatusNotify = (MMC_LMM_CS_CONN_STATUS_NOTIFY_STRU *)pMsg;

    /* 如果发起了紧急建链，则记录紧急建链的标识，否则清除该标识 */
    if((VOS_TRUE == pstCsConnStatusNotify->ucCsRrConnStatusFlg) &&
        (VOS_TRUE == pstCsConnStatusNotify->ucCsEmergencyConnStatusFlg))
    {
        NAS_EMM_PUBU_LOG_INFO("NAS_LMM_PreProcMmcCsConnStatusNotify is entered,EMC CONN EXIT");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcCsConnStatusNotify_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_LMM_SetEmmInfoCsEmcConneExitFlag(VOS_TRUE);
    }
    else
    {
    }
    return NAS_LMM_MSG_HANDLED;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

/* end of 子系统+模块+文件名.c */

