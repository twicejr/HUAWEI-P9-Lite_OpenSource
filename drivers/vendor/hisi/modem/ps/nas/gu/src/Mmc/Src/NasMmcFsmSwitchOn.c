

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "PsTypeDef.h"
#include "NasMmSublayerDef.h"
#include "NasMmcCtx.h"
#include "NasMmlLib.h"
#include "NasMmcSndLmm.h"
#include "NasMmcSndMm.h"
#include "NasMmcSndGmm.h"
#include "NasMmcSndInternalMsg.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcSndMscc.h"
#include "NasMmcSndOm.h"
#include "NasMmcFsmSwitchOn.h"
#include "NasMmcFsmSwitchOnTbl.h"
#include "NasMmcTimerMgmt.h"
#include "NasMmcProcNvim.h"
#include "NasMmcProcUsim.h"
#include "NasComm.h"
#include "NasMmcProcRegRslt.h"
#include "NasMmcPlmnSelectionStrategy.h"
#include "NasMmcComFunc.h"
#include "NasMmlCtx.h"
#include "NasMmcComFunc.h"

#include "MsccMmcInterface.h"
#include "NasUsimmApi.h"

#include "PsRrmInterface.h"

#include "NasUtranCtrlInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_SWITCHON_C


/*lint -save -e958 */


VOS_VOID NAS_MMC_SaveCardStatus_SwitchOn(NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 enCardStatus)
{
    NAS_MML_SIM_STATUS_STRU            *pstSimStatus;

    pstSimStatus    = NAS_MML_GetSimStatus();

    if ( NAS_MSCC_PIF_CARD_STATUS_SIM_PRESENT == enCardStatus )
    {
        pstSimStatus->enSimType = NAS_MML_SIM_TYPE_SIM;

        NAS_MML_SetSimPresentStatus(VOS_TRUE);
    }
    else if ( NAS_MSCC_PIF_CARD_STATUS_USIM_PRESENT == enCardStatus)
    {
        pstSimStatus->enSimType = NAS_MML_SIM_TYPE_USIM;

        NAS_MML_SetSimPresentStatus(VOS_TRUE);
    }
    else
    {
        NAS_MML_SetSimPresentStatus(VOS_FALSE);
    }
}


VOS_VOID NAS_MMC_SetCsPsAttachAllowFlagAccordingToRegDomain_SwitchOn(
    NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_ENUM_UINT8 enRegDomain
)
{
    switch (enRegDomain)
    {
        case NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_PS:
            NAS_MML_SetPsAttachAllowFlg(VOS_TRUE);
            break;

        case NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_CS:
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            break;

        case NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_CS_PS:
            NAS_MML_SetPsAttachAllowFlg(VOS_TRUE);
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            break;

        case NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_NULL:
        default:
            NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            break;
    }
}



VOS_UINT32 NAS_MMC_RcvStartReq_SwitchOn_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_START_REQ_STRU              *pstStartReq     = VOS_NULL_PTR;
    NAS_MML_SIM_MS_IDENTITY_STRU       *pstMsIdentity   = VOS_NULL_PTR;
    VOS_UINT8                           aucImsi[NAS_MAX_IMSI_LENGTH];
    VOS_UINT8                           aucPsLocInfo[NAS_MML_PS_LOCI_SIM_FILE_LEN];

    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;



    pstMsIdentity                       = NAS_MML_GetSimMsIdentity();
    pstStartReq                         = (MSCC_MMC_START_REQ_STRU*)pstMsg;
    pstRplmnCfgInfo                     = NAS_MML_GetRplmnCfg();

    /* 保存入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 保存模式信息到mml全局变量 */
#if (FEATURE_ON == FEATURE_ECALL)
    NAS_MML_SetCallMode((NAS_MML_CALL_MODE_ENUM_UINT8)(pstStartReq->enCallMode));
#endif



    /* 保存接入技术 */
    NAS_MMC_SavePlmnRatPrio_SwitchOn(&(pstStartReq->stPlmnRatPrio));

    /* 保存支持3GPP2的接入技术到MML全局变量 */
    NAS_MMC_Save3Gpp2RatPrio_SwitchOn(&(pstStartReq->st3Gpp2Rat));

    /* 保存搜网注册控制到MMC全局变量 */
    NAS_MMC_SetRegCtrl(pstStartReq->enRegCtrl);


    NAS_MMC_SaveAllowRegDomain_SwitchOn(pstStartReq->enRegDomain);

    /* 保存SIM卡状态信息 */
    NAS_MMC_SaveCardStatus_SwitchOn(pstStartReq->enUsimStatus);

    NAS_MML_InitSimPlmnInfoCtx(NAS_MML_INIT_CTX_STARTUP, NAS_MML_GetSimPlmnInfo());

    /* 必须保证SIM卡在前面更新,因为读取NV需要判断卡类型,获取NV项相关信息 */
    if ( VOS_TRUE == NAS_MML_GetSimPresentStatus())
    {
        PS_MEM_CPY( pstMsIdentity->aucImsi, pstStartReq->aucImsi, NAS_MAX_IMSI_LENGTH );
    }
    NAS_MMC_ReadNvimInfo_SwitchOn();


    NAS_MMC_LogRplmnCfgInfo();


    /* 将NV中保存的上次的IMSI保存到开机上下文中，用于开机状态机的IMSI是否改变的判决 */
    PS_MEM_CPY( NAS_MMC_GetLastImsi_SwitchOn(),
                pstRplmnCfgInfo->aucLastImsi, NAS_MAX_IMSI_LENGTH );

    /* SIM卡存在，读取相关文件。文件读取成功后才通知MM/GMM初始化 */
    if ( VOS_TRUE == NAS_MML_GetSimPresentStatus())
    {

        /* 如果掉卡 或者换卡，更新TIN类型 */
        if ( VOS_TRUE == NAS_MMC_IsImsiChange_SwitchOn())
        {
#if (FEATURE_ON == FEATURE_LTE)
            NAS_MMC_WriteTinInfoNvim(NAS_MML_TIN_TYPE_INVALID, pstStartReq->aucImsi);

            NAS_MML_SetTinType(NAS_MML_TIN_TYPE_INVALID);
#else
            NAS_MMC_UpdateLastImsi();
#endif
            /* 更新Ps Loc file无效*/
            PS_MEM_SET(aucPsLocInfo, (VOS_CHAR)0xFF, sizeof(aucPsLocInfo));

            /* routing area update status应该为02 */
            aucPsLocInfo[NAS_MML_PS_LOCI_SIM_FILE_LEN-1] = NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED;

            /* LAC应该为OXFFFE*/
            aucPsLocInfo[NAS_MML_PS_LOCI_SIM_FILE_LEN-3] = NAS_MML_LAC_HIGH_BYTE_INVALID;

            NAS_MMC_WritePsLociNvim(aucPsLocInfo, sizeof(aucPsLocInfo));
        }

        /* 获取USIM文件 */
        NAS_MMC_SndUsimReadFileReq();

        /* 启动保护定时器，期望在MMC_READ_AGENT_PRO_TIMER超时前读取文件成功 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_SWITCH_ON_STA_WAIT_SIM_FILES_CNF);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_READ_SIM_FILES,TI_NAS_MMC_WAIT_READ_SIM_FILES_LEN);
    }
    /* SIM卡不存在 */
    else
    {
        /* 设置无效IMSI变量 */
        PS_MEM_SET(aucImsi, (VOS_CHAR)0xFF, NAS_MAX_IMSI_LENGTH);


        /* 给MM发送开机请求 */
        NAS_MMC_SndMmStartReq();
        NAS_MMC_SetWaitMmStartCnfFlg_SwitchOn(NAS_MMC_WAIT_MMCMM_START_CNF);

        /* 给GMM发送开机请求 */
        NAS_MMC_SndGmmStartReq();
        NAS_MMC_SetWaitMmStartCnfFlg_SwitchOn(NAS_MMC_WAIT_MMCGMM_START_CNF);

        /* 启动保护定时器，期望在定时器超时前收齐MM、GMM的初始化回复消息 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_SWITCH_ON_STA_WAIT_MM_START_CNF);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_START_CNF,TI_NAS_MMC_WAIT_MM_START_CNF_LEN);
    }

#ifndef __PS_WIN32_RECUR__

    if ( VOS_TRUE == NAS_MML_IsSndOmPcRecurMsgValid() )
    {
        NAS_MMC_SndOutsideFixedContextData();
        NAS_MMC_SndOutsideContextData();
    }

#endif

    NAS_MMC_SetCsPsAttachAllowFlagAccordingToRegDomain_SwitchOn(pstStartReq->enRegDomain);

    return VOS_TRUE;
}


VOS_VOID NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn_WaitSimFilesCnf(
    USIMM_DEF_FILEID_ENUM_UINT32        enEfId
)
{
    switch ( enEfId )
    {
        case USIMM_USIM_EFHPLMNwACT_ID:
        case USIMM_GSM_EFHPLMNACT_ID:
            NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_HPLMN_SEL_FILE_ID_FLG);
            break;

        case USIMM_USIM_EFFPLMN_ID:
        case USIMM_GSM_EFFPLMN_ID:
            NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_FORBIDDEN_PLMN_LIST_FILE_ID_FLG);
            break;

        case USIMM_USIM_EFPLMNWACT_ID:
        case USIMM_GSM_EFPLMNWACT_ID:
            NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_UPLMN_SEL_FILE_ID_FLG);
            break;
        case USIMM_USIM_EFOPLMNWACT_ID:
        case USIMM_GSM_EFOPLMNWACT_ID:
            NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_OPLMN_SEL_FILE_ID_FLG);
            break;

        case USIMM_USIM_EFHPPLMN_ID:
        case USIMM_GSM_EFHPLMN_ID:
            NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_HPLMN_PERI_FILE_ID_FLG);
            break;

        case USIMM_USIM_EFAD_ID:
        case USIMM_GSM_EFAD_ID:
            NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_MNC_LENGTH_FILE_ID_FLG);
            break;

        case USIMM_USIM_EFLOCI_ID:
        case USIMM_GSM_EFLOCI_ID:
            NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_CS_LOC_FILE_ID_FLG);
            break;

        case USIMM_USIM_EFKEYS_ID:
            NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_CS_CKIK_FILE_ID_FLG);
            break;

        /* 增加对SIM卡中的cskc文件读取 */
        case USIMM_GSM_EFKC_ID:
            NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_CS_KC_FILE_ID_FLG);
            break;

        case USIMM_USIM_EFKEYSPS_ID:
            NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_PS_KEY_FILE_ID_FLG);
            break;

        /* 增加对SIM卡中的PSkc文件读取处理 */
        case USIMM_GSM_EFKCGPRS_ID:
            NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_PS_KC_FILE_ID_FLG);
            break;

        case USIMM_USIM_EFPSLOCI_ID:
        case USIMM_GSM_EFLOCIGPRS_ID:
            NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_PS_LOC_FILE_ID_FLG);
            break;

        /* 增加对SIM卡中的cskc文件读取 */
        case USIMM_GSM_EFPLMNSEL_ID:
            NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_PLMN_SEL_FILE_ID_FLG);
            break;

        case USIMM_USIM_EFEHPLMN_ID:
            NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_EHPLMN_FILE_ID_FLG);
            break;

        case USIMM_USIM_EFEHPLMNPI_ID:
            NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_EHPLMNPI_FILE_ID_FLG);
            break;

        case USIMM_USIM_EFLRPLMNSI_ID:
            NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_LRPLMNSI_FILE_ID_FLG);
            break;

        case USIMM_ATTGSM_EFACTINGHPLMN_ID:
        case USIMM_ATTUSIM_EFACTINGHPLMN_ID:
            NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_ACTING_HPLMN_FILE_ID_FLG);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn_WaitSimFilesCnf:WARNING: File Id Abnormal");
            break;
    }

    return;
}



VOS_UINT32 NAS_MMC_RcvUsimGetFileRsp_SwitchOn_WaitSimFilesCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU                   *pstRcvMsg           = VOS_NULL_PTR;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                       *pstForbidPlmnInfo   = VOS_NULL_PTR;

    NAS_MML_SIM_MS_IDENTITY_STRU                           *pstMsIdentity       = VOS_NULL_PTR;
    NAS_MML_SIM_EHPLMN_INFO_STRU                           *pstSimEhplmnInfo    = VOS_NULL_PTR;
    USIMM_DEF_FILEID_ENUM_UINT32                            enEfId;

    pstSimEhplmnInfo                    = NAS_MML_GetSimEhplmnList();
    pstMsIdentity                       = NAS_MML_GetSimMsIdentity();

    pstRcvMsg                           = (PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU*)pstMsg;
    pstForbidPlmnInfo                   = NAS_MML_GetForbidPlmnInfo();

    NAS_MMC_RcvAgentUsimReadFileCnf(pstRcvMsg);

    if (VOS_OK != USIMM_ChangePathToDefFileID(USIMM_GUTL_APP, pstRcvMsg->stFilePath.ulPathLen, pstRcvMsg->stFilePath.acPath, &enEfId))
    {
        return VOS_FALSE;
    }

    NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn_WaitSimFilesCnf(enEfId);

    /* 未收齐向agient要求的响应，继续等待 */
    if (NAS_MML_READ_USIM_FILE_FLG_NULL != NAS_MMC_GetWaitSimFilesCnfFlg_SwitchOn())
    {
        return VOS_TRUE;
    }

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_READ_SIM_FILES);


    NAS_MMC_InitLastRplmnRat_SwitchOn();



    /* 如果当前的EHplmn的个数为0个，则需要将获取IMSI中的HOME PLMN或者NV中用户
       配置的HOME PLMN */
    if ( 0 == pstSimEhplmnInfo->ucEhPlmnNum)
    {
        NAS_MMC_UpdateEhplmnInfo_SwitchOn(pstMsIdentity->aucImsi);
    }

    /* 通知MSCC优选PLMN信息 */
    NAS_MMC_SndMsccPrefPlmnInfoInd(NAS_MSCC_PREF_PLMN_OPLMN);

    if (VOS_FALSE == NAS_MML_Get3GPP2UplmnNotPrefFlg())
    {
        NAS_MMC_SndMsccPrefPlmnInfoInd(NAS_MSCC_PREF_PLMN_UPLMN);
    }

    /* 这里通知EHPLMN信息,而且需要在EHPLMN信息未拆分前通知 */
    NAS_MMC_SndMsccPrefPlmnInfoInd(NAS_MSCC_PREF_PLMN_HPLMN);

    /* 更新HPLMN接入技术 */
    NAS_MMC_UpdateEhplmnRat();

    /* 删除FPLMN中的无效PLMN */
    (VOS_VOID)NAS_MML_DelInvalidPlmnFromList(pstForbidPlmnInfo->ucForbPlmnNum, pstForbidPlmnInfo->astForbPlmnIdList);

    /* 删除FPLMN中的HPLMN */
    NAS_MMC_DelHplmnInFplmn();

    /* 当USIM卡在2G下做过2g鉴权，重新开机，ucUsimDoneGsmCsAuthFlg ucUsimDoneGsmPsAuthFlg 无效，
       所以在开机时将Cs PS 鉴权标记置true，以在鉴权时清CKSN */
    if (VOS_TRUE == NAS_MMC_IsNeedClearCksn_SwitchOn())
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvUsimGetFileRsp_SwitchOn_WaitSimFilesCnf Set UsimDoneGsm Cs PS AuthFlg TO ture");

        NAS_MML_SetUsimDoneGsmCsAuthFlg(VOS_TRUE);
        NAS_MML_SetUsimDoneGsmPsAuthFlg(VOS_TRUE);
    }


    /* 给MM发送开机请求 */
    NAS_MMC_SndMmStartReq();

    NAS_MMC_SetWaitMmStartCnfFlg_SwitchOn(NAS_MMC_WAIT_MMCMM_START_CNF);

    /* 给GMM发送开机请求 */
    NAS_MMC_SndGmmStartReq();
    NAS_MMC_SetWaitMmStartCnfFlg_SwitchOn(NAS_MMC_WAIT_MMCGMM_START_CNF);

    /*启动保护定时器，期望在定时器超时前收齐MM、GMM的初始化回复消息*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_SWITCH_ON_STA_WAIT_MM_START_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_START_CNF,TI_NAS_MMC_WAIT_MM_START_CNF_LEN);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvTiReadSimFilesExpired_SwitchOn_WaitSimFilesCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                       *pstForbidPlmnInfo   = VOS_NULL_PTR;
    NAS_MML_RPLMN_CFG_INFO_STRU                            *pstRplmnCfgInfo     = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList      = VOS_NULL_PTR;

    NAS_MML_SIM_MS_IDENTITY_STRU                           *pstMsIdentity       = VOS_NULL_PTR;
    NAS_MML_SIM_EHPLMN_INFO_STRU                           *pstSimEhplmnInfo    = VOS_NULL_PTR;

    pstSimEhplmnInfo                    = NAS_MML_GetSimEhplmnList();
    pstMsIdentity                       = NAS_MML_GetSimMsIdentity();

    pstForbidPlmnInfo                   = NAS_MML_GetForbidPlmnInfo();
    pstRplmnCfgInfo                     = NAS_MML_GetRplmnCfg();
    pstPrioRatList                      = NAS_MML_GetMsPrioRatList();

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiReadSimFilesExpired_SwitchOn_WaitSimFilesCnf:ENTERED");

    /* 未获取到重搜plmn时间，使用默认的60分钟 */
    if ( NAS_MML_READ_HPLMN_PERI_FILE_ID_FLG
        == (NAS_MML_READ_HPLMN_PERI_FILE_ID_FLG & NAS_MMC_GetWaitSimFilesCnfFlg_SwitchOn()))
    {
        NAS_MML_SetSimHplmnTimerLen(TI_NAS_MMC_HPLMN_TIMER_DEFAULT_LEN);
    }

    /* 清除等待接收SIM卡文件标志位 */
    NAS_MMC_ClearAllWaitSimFilesCnfFlg_SwitchOn();


    /* IMSI改变时，enLastRplmnRat需要更新为SYSCFG设置的最高优先级的 */
    if ((VOS_TRUE   == NAS_MMC_IsImsiChange_SwitchOn())
     || (NAS_MML_NET_RAT_TYPE_BUTT == pstRplmnCfgInfo->enLastRplmnRat))
    {
        pstRplmnCfgInfo->enLastRplmnRat = pstPrioRatList->aucRatPrio[0];
    }



    /* 如果当前的EHplmn的个数为0个，则需要将获取IMSI中的HOME PLMN或者NV中用户
       配置的HOME PLMN */
    if ( 0 == pstSimEhplmnInfo->ucEhPlmnNum)
    {
        NAS_MMC_UpdateEhplmnInfo_SwitchOn(pstMsIdentity->aucImsi);
    }

    /* 更新HPLMN接入技术 */
    NAS_MMC_UpdateEhplmnRat();

    /* 删除FPLMN中的无效PLMN */
    (VOS_VOID)NAS_MML_DelInvalidPlmnFromList(pstForbidPlmnInfo->ucForbPlmnNum, pstForbidPlmnInfo->astForbPlmnIdList);

    /* 删除FPLMN中的HPLMN */
    NAS_MMC_DelHplmnInFplmn();

    /* 当USIM卡在2G下做过2g鉴权，重新开机，ucUsimDoneGsmCsAuthFlg ucUsimDoneGsmPsAuthFlg 无效，
       所以在开机时将Cs PS 鉴权标记置true，以在鉴权时清CKSN */
    if (VOS_TRUE == NAS_MMC_IsNeedClearCksn_SwitchOn())
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiReadSimFilesExpired_SwitchOn_WaitSimFilesCnf Set UsimDoneGsm Cs PS AuthFlg TO ture");

        NAS_MML_SetUsimDoneGsmCsAuthFlg(VOS_TRUE);
        NAS_MML_SetUsimDoneGsmPsAuthFlg(VOS_TRUE);
    }

    /* 给MM发送开机请求 */
    NAS_MMC_SndMmStartReq();
    NAS_MMC_SetWaitMmStartCnfFlg_SwitchOn(NAS_MMC_WAIT_MMCMM_START_CNF);

    /* 给GMM发送开机请求 */
    NAS_MMC_SndGmmStartReq();
    NAS_MMC_SetWaitMmStartCnfFlg_SwitchOn(NAS_MMC_WAIT_MMCGMM_START_CNF);

    /* 启动保护定时器，期望在定时器超时前收齐MM、GMM的初始化回复消息 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_SWITCH_ON_STA_WAIT_MM_START_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_START_CNF,TI_NAS_MMC_WAIT_MM_START_CNF_LEN);

    return VOS_TRUE;

}


VOS_UINT32  NAS_MMC_RcvMmStartCnf_SwitchOn_WaitMmStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_SENDING_AS_SWITCH_ON_SEQUENCE_CTRL_STRU        *pstSwitchOnSettingRecord = VOS_NULL_PTR;
    NAS_MMC_ClearMmStartCnfFlg_SwitchOn(NAS_MMC_WAIT_MMCMM_START_CNF);

    /* 未收齐MM和GMM的开机回复消息,继续等待 */
    if (NAS_MMC_WAIT_MMGMM_START_CNF_NULL != NAS_MMC_GetWaitMmStartCnfFlg_SwitchOn())
    {
        return VOS_TRUE;
    }

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_MM_START_CNF);


    /* 初始化向接入层发送开机的先后顺序 :G->L->W */
    NAS_MMC_SetSwitchOnSendingAsOrder_SwitchOn();
    pstSwitchOnSettingRecord            = NAS_MMC_GetSwitchOnSequenceRecord_SwitchOn();

    /* 开机顺序设置完成后，对异常情况进行判断 */
    /* 异常情况：下发开机的接入层个数为0，打印异常，给MSCC回复开机失败，退状态机 */
    if (0 == pstSwitchOnSettingRecord->ucTotalSwitchOnRatNum)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmStartCnf_SwitchOn_WaitMmStartCnf,ERROR:Switch On Rat Num 0");

        NAS_TRACE_HIGH("Switch On Rat Num 0!");

        /* 给TAF发送开机失败 */
        NAS_Mmc_SndMsccStartCnf(TAF_FAILURE);

        NAS_MMC_SndSwitchOnRlst(VOS_FALSE);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 向接入层发送开机请求 */
    NAS_MMC_SndRatModeSwitchOnReq_SwitchOn( NAS_MMC_GetNextSendingRat_SwitchOn() );

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvGmmStartCnf_SwitchOn_WaitMmStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_SENDING_AS_SWITCH_ON_SEQUENCE_CTRL_STRU        *pstSwitchOnSettingRecord = VOS_NULL_PTR;
    /* 根据PID清除等待MM或者GMM的标志 */
    NAS_MMC_ClearMmStartCnfFlg_SwitchOn(NAS_MMC_WAIT_MMCGMM_START_CNF);

    /* 未收齐MM和GMM的开机回复消息,继续等待 */
    if ( NAS_MMC_WAIT_MMGMM_START_CNF_NULL != NAS_MMC_GetWaitMmStartCnfFlg_SwitchOn() )
    {
        return VOS_TRUE;
    }

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_MM_START_CNF);


    /* 初始化向接入层发送开机的先后顺序 :G->L->W */
    NAS_MMC_SetSwitchOnSendingAsOrder_SwitchOn();
    pstSwitchOnSettingRecord            = NAS_MMC_GetSwitchOnSequenceRecord_SwitchOn();
    /* 开机顺序设置完成后，对异常情况进行判断 */
    /* 异常情况：下发开机的接入层个数为0，打印异常，给MSCC回复开机失败，退状态机 */
    if (0 == pstSwitchOnSettingRecord->ucTotalSwitchOnRatNum)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvGmmStartCnf_SwitchOn_WaitMmStartCnf,ERROR:Switch On Rat Num 0");

        NAS_TRACE_HIGH("Switch On Rat Num 0!");

        /* 给TAF发送开机失败 */
        NAS_Mmc_SndMsccStartCnf(TAF_FAILURE);

        NAS_MMC_SndSwitchOnRlst(VOS_FALSE);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 向接入层发送开机请求 */
    NAS_MMC_SndRatModeSwitchOnReq_SwitchOn( NAS_MMC_GetNextSendingRat_SwitchOn() );

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvTiMmStartCnfExpired_SwitchOn_WaitMmStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiMmStartCnfExpired_SwitchOn_WaitMmStartCnf:ENTERED");

    NAS_TRACE_HIGH("Enter!");

    /* 清除等待MM/GMM开机回复消息的标志位 */
    NAS_MMC_ClearAllWaitMmStartCnfFlg_SwitchOn();

    /* 未收到MM和GMM的回复也认为开机失败 */
    NAS_Mmc_SndMsccStartCnf(TAF_FAILURE);

    NAS_MMC_SndSwitchOnRlst(VOS_FALSE);

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvGasStartCnf_SwitchOn_WaitGasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_START_CNF_STRU                        *pstRrStartCnfMsg          = VOS_NULL_PTR;

    pstRrStartCnfMsg          = (RRMM_START_CNF_STRU *)pstMsg;

    (VOS_VOID)vos_printf("NAS_MMC_RcvGasStartCnf_SwitchOn_WaitGasStartCnf.ulResult = %d.\n ", pstRrStartCnfMsg->ulResult);

    NAS_TRACE_HIGH("ulResult = %d", pstRrStartCnfMsg->ulResult);

    if (MMC_START_FAILURE == pstRrStartCnfMsg->ulResult)
    {
        /* 若WAS或者GAS有一个开机失败则直接迁移到关机状态 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_START_CNF);

        /* 给TAF发送开机失败 */
        NAS_Mmc_SndMsccStartCnf(TAF_FAILURE);

        NAS_MMC_SndSwitchOnRlst(VOS_FALSE);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }


    /* 收到GAS的开机回复后，停止等待GAS回复的定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_START_CNF);

    /* 如果开机未完成，则继续给下一个模发送开机请求 */
    if ( NAS_MML_NET_RAT_TYPE_BUTT != NAS_MMC_GetNextSendingRat_SwitchOn() )
    {
        /* 向接入层发送开机请求:目前开机的发送顺序为G->L->W;在收到G模的成功回复后，则给L模发送开机请求 */
        NAS_MMC_SndRatModeSwitchOnReq_SwitchOn( NAS_MMC_GetNextSendingRat_SwitchOn() );
        return VOS_TRUE;
    }

    if (VOS_TRUE == NAS_MML_GetSimPresentStatus())
    {
        NAS_MMC_SndAsHplmnReq(WUEPS_PID_WRR);

        NAS_MMC_SndAsHplmnReq(UEPS_PID_GAS);


        /* 开机的时候判断卡的IMSI是否在禁止列表里，初始化IMSI的禁止状态 */
        NAS_MMC_RcvStartCnf_SwitchOn_InitRatForbidListCfg();

        NAS_MMC_RcvStartCnf_SwitchOn_ProcAsRatCapabilityStatus();

    }

    /* 开机完成，初始化用户指定的PLMN */
    NAS_MMC_InitUserSpecPlmnId_SwitchOn();

    /* 开机完成，用SIM卡中的RPLMN更新NV中的RPLMN */
    NAS_MMC_UpdateNvRplmnWithSimRplmn_SwitchOn();

    /* 开机完成，更新等效PLMN */
    NAS_MMC_UpdateEplmn_SwitchOn();

    /* 开机完成，增加AT主动上报 */
    NAS_MMC_SndGasInfoReportReq();

    NAS_MMC_SndWasInfoReportReq();

    /* 通知LMM信号质量上报的时间间隔和门限 */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_SndLmmCellSignReportNotify();
#endif

    /* 开机完成，向TAF发送成功的TAFMMC_START_CNF */
    NAS_Mmc_SndMsccStartCnf(TAF_SUCCESS);

    /* 开机完成，初始化高优先级搜网列表信息 */
    NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_PLMN_SEARCH,
                                  VOS_NULL_PTR,
                                  NAS_MMC_GetHighPrioPlmnList());

    NAS_MMC_SndSwitchOnRlst(VOS_TRUE);

    /* 开机完成，退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();


    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvWasStartCnf_SwitchOn_WaitWasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_START_CNF_STRU                        *pstRrStartCnfMsg = VOS_NULL_PTR;

    pstRrStartCnfMsg          = (RRMM_START_CNF_STRU *)pstMsg;

    (VOS_VOID)vos_printf("NAS_MMC_RcvWasStartCnf_SwitchOn_WaitWasStartCnf.ulResult = %d.tick=0x%x\n ", pstRrStartCnfMsg->ulResult,VOS_GetSlice());

    NAS_TRACE_HIGH("%s ulResult = %d",
        (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode()) ? "FDD" : "TDD", pstRrStartCnfMsg->ulResult);

    if (MMC_START_FAILURE == pstRrStartCnfMsg->ulResult)
    {
        /* 若WAS或者GAS有一个开机失败则直接迁移到关机状态 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_START_CNF);

        /* 给TAF发送开机失败 */
        NAS_Mmc_SndMsccStartCnf(TAF_FAILURE);

        NAS_MMC_SndSwitchOnRlst(VOS_FALSE);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }


    /* 收到WAS的开机回复后，停止等待WAS回复的定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_START_CNF);

    /* 如果开机未完成，则继续给下一个模发送开机请求 */
    if ( NAS_MML_NET_RAT_TYPE_BUTT != NAS_MMC_GetNextSendingRat_SwitchOn() )
    {
        /* 向接入层发送开机请求:目前开机的发送顺序为G->L->W;在收到W模的成功回复后，则给L模发送开机请求 */
        NAS_MMC_SndRatModeSwitchOnReq_SwitchOn( NAS_MMC_GetNextSendingRat_SwitchOn() );
        return VOS_TRUE;
    }


    if (VOS_TRUE == NAS_MML_GetSimPresentStatus())
    {
        NAS_MMC_SndAsHplmnReq(WUEPS_PID_WRR);

        NAS_MMC_SndAsHplmnReq(UEPS_PID_GAS);


        /* 开机的时候判断卡的IMSI是否在禁止列表里，初始化IMSI的禁止状态 */
        NAS_MMC_RcvStartCnf_SwitchOn_InitRatForbidListCfg();

        NAS_MMC_RcvStartCnf_SwitchOn_ProcAsRatCapabilityStatus();

    }

    /* 开机完成，用SIM卡中的RPLMN更新NV中的RPLMN */
    NAS_MMC_UpdateNvRplmnWithSimRplmn_SwitchOn();

    /* 开机完成，初始化用户指定的PLMN */
    NAS_MMC_InitUserSpecPlmnId_SwitchOn();

    /* 开机完成，更新等效PLMN */
    NAS_MMC_UpdateEplmn_SwitchOn();

    /* 开机完成，增加AT主动上报 */
    NAS_MMC_SndWasInfoReportReq();

    NAS_MMC_SndGasInfoReportReq();

    /* 通知LMM信号质量上报的时间间隔和门限 */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_SndLmmCellSignReportNotify();
#endif

    /* 开机完成，向TAF发送成功的TAFMMC_START_CNF */
    NAS_Mmc_SndMsccStartCnf(MMC_START_SUCCESS);

    /* 开机成功，初始化高优先级搜网列表 */
    NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_PLMN_SEARCH,
                                  VOS_NULL_PTR,
                                  NAS_MMC_GetHighPrioPlmnList());

    NAS_MMC_SndSwitchOnRlst(VOS_TRUE);

    /* 开机完成，退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();


    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvTiWaitGasStartCnfExpired_SwitchOn_WaitGasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Enter!");

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasStartCnfExpired_SwitchOn_WaitGasStartCnf:ENTERED");

    /* 超时认为失败 */
    NAS_Mmc_SndMsccStartCnf(TAF_FAILURE);

    NAS_MMC_SndSwitchOnRlst(VOS_FALSE);

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvTiWaitWasStartCnfExpired_SwitchOn_WaitWasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("%s", (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode()) ? "FDD" : "TDD");

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasStartCnfExpired_SwitchOn_WaitWasStartCnf:ENTERED");

    /* 超时认为失败 */
    NAS_Mmc_SndMsccStartCnf(TAF_FAILURE);

    NAS_MMC_SndSwitchOnRlst(VOS_FALSE);

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


#if   (FEATURE_ON == FEATURE_LTE)


VOS_UINT32 NAS_MMC_RcvLmmStartCnf_SwitchOn_WaitLStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_START_CNF_STRU                     *pstRrStartCnfMsg          = VOS_NULL_PTR;

    pstRrStartCnfMsg          = (LMM_MMC_START_CNF_STRU *)pstMsg;

    /* 停止保护定时器，此定时器在给L模发出开机消息时启动 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_START_CNF);

    (VOS_VOID)vos_printf("NAS_MMC_RcvLmmStartCnf_SwitchOn_WaitLStartCnf.ulResult = %d,tick=0x%x\r\n ", pstRrStartCnfMsg->ulRst,VOS_GetSlice());

    NAS_TRACE_HIGH("ulResult = %d", pstRrStartCnfMsg->ulRst);

    /* L下开机不成功，则开机失败，退出状态机 */
    if (MMC_LMM_SUCC != pstRrStartCnfMsg->ulRst)
    {
        /* 向TAF发送TAFMMC_START_CNF */
        NAS_Mmc_SndMsccStartCnf(TAF_FAILURE);

        NAS_MMC_SndSwitchOnRlst(VOS_FALSE);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果开机未完成，则继续给下一个模发送开机请求 */
    if ( NAS_MML_NET_RAT_TYPE_BUTT != NAS_MMC_GetNextSendingRat_SwitchOn() )
    {
        /* 向接入层发送开机请求:目前开机的发送顺序为G->L->W;在收到L模的成功回复后，则给W模发送开机请求 */
        NAS_MMC_SndRatModeSwitchOnReq_SwitchOn( NAS_MMC_GetNextSendingRat_SwitchOn() );

        return VOS_TRUE;
    }

    /* 开机完成，初始化用户指定的PLMN */
    NAS_MMC_InitUserSpecPlmnId_SwitchOn();

    /* 开机完成，用SIM卡中的RPLMN更新NV中的RPLMN */
    NAS_MMC_UpdateNvRplmnWithSimRplmn_SwitchOn();

    /* 开机完成，更新等效PLMN */
    NAS_MMC_UpdateEplmn_SwitchOn();

    if (VOS_TRUE == NAS_MML_GetSimPresentStatus())
    {
        NAS_MMC_SndAsHplmnReq(WUEPS_PID_WRR);

        NAS_MMC_SndAsHplmnReq(UEPS_PID_GAS);


        /* 开机的时候判断卡的IMSI是否在禁止列表里，初始化IMSI的禁止状态 */
        NAS_MMC_RcvStartCnf_SwitchOn_InitRatForbidListCfg();

        NAS_MMC_RcvStartCnf_SwitchOn_ProcAsRatCapabilityStatus();

    }

    /* 开机完成，增加AT主动上报 */
    NAS_MMC_SndGasInfoReportReq();

    NAS_MMC_SndWasInfoReportReq();

    /* 通知LMM信号质量上报的时间间隔和门限 */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_SndLmmCellSignReportNotify();
#endif

    /* 开机完成，向TAF发送成功的TAFMMC_START_CNF */
    NAS_Mmc_SndMsccStartCnf(TAF_SUCCESS);

    NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_PLMN_SEARCH,
                                  VOS_NULL_PTR,
                                  NAS_MMC_GetHighPrioPlmnList());

    NAS_MMC_SndSwitchOnRlst(VOS_TRUE);

    /* 开机完成，退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();
    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvTiLmmStartCnfExpired_SwitchOn_WaitLStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Enter!");

    /* 超时认为开机失败 */
    NAS_Mmc_SndMsccStartCnf(TAF_FAILURE);

    NAS_MMC_SndSwitchOnRlst(VOS_FALSE);

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

#endif


VOS_UINT32  NAS_MMC_IsSimRplmnInNvRplmn_SwitchOn(
    NAS_MML_PLMN_ID_STRU               *pstSimRplmnId
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulExistSamePlmn;
    NAS_MML_PLMN_ID_STRU               *pstNVRplmn      = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;

    pstRplmnCfgInfo         = NAS_MML_GetRplmnCfg();
    ulExistSamePlmn         = VOS_FALSE;

    pstPrioRatList = NAS_MML_GetMsPrioRatList();

    /* 对当前支持的所有接入技术，逐项进行检查 */
    pstNVRplmn = &(pstRplmnCfgInfo->stGRplmnInNV);

    for ( i = 0 ; i < pstPrioRatList->ucRatNum ; i++ )
    {
        switch (pstPrioRatList->aucRatPrio[i] )
        {
            case NAS_MML_NET_RAT_TYPE_GSM:
                pstNVRplmn = &(pstRplmnCfgInfo->stGRplmnInNV);
                break;

            case NAS_MML_NET_RAT_TYPE_WCDMA:
                pstNVRplmn = &(pstRplmnCfgInfo->stWRplmnInNV);
                break;

            default:
                continue;
        }

        /* 判断NV中各个Rplmn是否有与SimRplmn相同的，
        有相同的，则保留使用各NV中的Rplmn;否则，统一使用 Sim卡中Rplmn*/
        if ( VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstNVRplmn, pstSimRplmnId))
        {
            ulExistSamePlmn = VOS_TRUE;
        }

    }

    return ulExistSamePlmn;
}


VOS_VOID NAS_MMC_UpdateNvRplmnWithSimRplmn_SwitchOn(VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstNVRplmn      = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stRplmn;
    VOS_UINT32                          ulExistSamePlmn;
    VOS_UINT32                          ulRplmnExistFlg;
    VOS_UINT32                          i;

    pstPrioRatList          = NAS_MML_GetMsPrioRatList();
    pstRplmnCfgInfo         = NAS_MML_GetRplmnCfg();
    ulRplmnExistFlg         = VOS_TRUE;

#if (FEATURE_ON == FEATURE_LTE)
    /* 若支持单Rplmn,且lastRplmnRat为Lte,则需要使用LRplmn更新stGRplmnInNV,stWRplmnInNV,否则使用GU Rplmn更新NV */
    if ((NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetLastRplmnRat())
    && (VOS_FALSE  == pstRplmnCfgInfo->ucMultiRATRplmnFlg))
    {
        ulRplmnExistFlg = NAS_MML_GetLteRPlmn(&stRplmn);
    }
    else
#endif
    {
        ulRplmnExistFlg = NAS_MML_GetGURPlmn(&stRplmn);
    }

    /* 获取RPLMN失败或者IMSI改变时，清除NV中的RPLMN信息 */
    if ((VOS_TRUE   == NAS_MMC_IsImsiChange_SwitchOn())
     || (VOS_FALSE  == ulRplmnExistFlg))
    {
        pstRplmnCfgInfo->stGRplmnInNV.ulMcc = NAS_MML_INVALID_MCC;
        pstRplmnCfgInfo->stGRplmnInNV.ulMnc = NAS_MML_INVALID_MNC;
        pstRplmnCfgInfo->stWRplmnInNV.ulMcc = NAS_MML_INVALID_MCC;
        pstRplmnCfgInfo->stWRplmnInNV.ulMnc = NAS_MML_INVALID_MNC;

        return;
    }

    /* Sim卡中Rplmn是否在NV中的Plmn中  */
    ulExistSamePlmn = NAS_MMC_IsSimRplmnInNvRplmn_SwitchOn(&stRplmn);

    /* 对当前支持的所有接入技术，逐项进行设置 */
    pstNVRplmn = &(pstRplmnCfgInfo->stGRplmnInNV);

    for ( i = 0 ; i < pstPrioRatList->ucRatNum; i++ )
    {
        switch (pstPrioRatList->aucRatPrio[i] )
        {
            case NAS_MML_NET_RAT_TYPE_GSM:
                pstNVRplmn = &(pstRplmnCfgInfo->stGRplmnInNV);
                break;

            case NAS_MML_NET_RAT_TYPE_WCDMA:
                pstNVRplmn = &(pstRplmnCfgInfo->stWRplmnInNV);
                break;

            default:
                /* L模使用EPSLoci中的数据，不需要再额外处理 */
                continue;
        }

        /* NV中Rplmn 无效或当前只支持一个Rplmn或所有NV中Rplmn与卡中Plmn不同，则使用Sim中的Rplmn */
        if ((VOS_FALSE  == NAS_MML_IsPlmnIdValid(pstNVRplmn))
         || (VOS_FALSE  == ulExistSamePlmn)
         || (VOS_FALSE  == pstRplmnCfgInfo->ucMultiRATRplmnFlg))
        {
            pstNVRplmn->ulMcc = stRplmn.ulMcc;
            pstNVRplmn->ulMnc = stRplmn.ulMnc;
        }

    }

    return;
}


VOS_VOID NAS_MMC_UpdateLastRplmnRat_LastRplmnRatInvalid_SwitchOn(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstLasRplmn,
    VOS_UINT8                           ucLastRplmnExistFlag
)
{
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatOrder     = VOS_NULL_PTR;

    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();
    pstRatOrder     = NAS_MML_GetMsPrioRatList();

    /* 换卡开机会将last rplmn rat更新为butt，获取完rplmn后需要更新last rplmn rat全局变量 */
    if (NAS_MML_NET_RAT_TYPE_BUTT != pstRplmnCfgInfo->enLastRplmnRat)
    {
        return;
    }

    /* 如果l和gu的rplmn都不存在，将last rplmn rat更新为syscfg设置的最高优先级网络 */
    if (VOS_FALSE == ucLastRplmnExistFlag)
    {
        pstRplmnCfgInfo->enLastRplmnRat = pstRatOrder->aucRatPrio[0];
        return;
    }

#if   (FEATURE_ON == FEATURE_LTE)
    if (NAS_MML_NET_RAT_TYPE_LTE == pstLasRplmn->enRat)
    {
        pstRplmnCfgInfo->enLastRplmnRat = pstLasRplmn->enRat;
        return;
    }
#endif

    if (VOS_TRUE == NAS_MML_IsWcdmaPrioGsm(pstRatOrder))
    {
        pstRplmnCfgInfo->enLastRplmnRat = NAS_MML_NET_RAT_TYPE_WCDMA;
        return;
    }

    pstRplmnCfgInfo->enLastRplmnRat = NAS_MML_NET_RAT_TYPE_GSM;
    return;

}



VOS_VOID NAS_MMC_UpdateEplmn_SwitchOn(VOS_VOID)
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnList    = VOS_NULL_PTR;

    NAS_MML_PLMN_WITH_RAT_STRU          stTmpPlmn;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo     = VOS_NULL_PTR;

    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstEHPlmnInfo   = VOS_NULL_PTR;

    pstEplmnList           = NAS_MML_GetEquPlmnList();


    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

    /* 根据上次关机的接入技术，决定取那个模式的RPLMN，不存在直接返回 */
    if  (VOS_FALSE == NAS_MMC_GetLastRplmn_SwitchOn(&stTmpPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_BUTT == pstRplmnCfgInfo->enLastRplmnRat)
        {
            NAS_MMC_UpdateLastRplmnRat_LastRplmnRatInvalid_SwitchOn(&stTmpPlmn, VOS_FALSE);
        }

        /* EPS/MM/GMM的update status无效时,EPLMN需要填写一个值保证开机注册失败时
           给RRC发的EPLMN个数不为0或者不发 */

        pstEHPlmnInfo       = NAS_MML_GetSimEhplmnList();

        pstEplmnList->ucEquPlmnNum = 1;
        pstEplmnList->astEquPlmnAddr[0].ulMcc = pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMcc;
        pstEplmnList->astEquPlmnAddr[0].ulMnc = pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMnc;

        /* 设置EPLMN有效标记 */
        NAS_MML_SetEplmnValidFlg(VOS_TRUE);

        return;
    }

    if (NAS_MML_NET_RAT_TYPE_BUTT == pstRplmnCfgInfo->enLastRplmnRat)
    {
        NAS_MMC_UpdateLastRplmnRat_LastRplmnRatInvalid_SwitchOn(&stTmpPlmn, VOS_TRUE);
    }

    /* 如果RPLMN不在EPLMN中，更新EPLMN列表 */
    if ((pstEplmnList->astEquPlmnAddr[0].ulMcc != stTmpPlmn.stPlmnId.ulMcc)
     || (pstEplmnList->astEquPlmnAddr[0].ulMnc != stTmpPlmn.stPlmnId.ulMnc))
    {
        pstEplmnList->ucEquPlmnNum = 1;
        pstEplmnList->astEquPlmnAddr[0].ulMcc = stTmpPlmn.stPlmnId.ulMcc;
        pstEplmnList->astEquPlmnAddr[0].ulMnc = stTmpPlmn.stPlmnId.ulMnc;


    }

    /* 设置EPLMN有效标记 */
    NAS_MML_SetEplmnValidFlg(VOS_TRUE);


    return;
}


VOS_VOID NAS_MMC_InitUserSpecPlmnId_SwitchOn(VOS_VOID)
{
    NAS_MML_PLMN_WITH_RAT_STRU          stUserPlmn;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserPlmnInfo     = VOS_NULL_PTR;
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstEHPlmnInfo       = VOS_NULL_PTR;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo     = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stGuRplmn;

    VOS_UINT8                           ucLastRplmnExistFlag;

    ucLastRplmnExistFlag = VOS_TRUE;

    /* 手动模式设置用户指定的PLMN ID */
    if ( NAS_MMC_PLMN_SELECTION_MODE_MANUAL != NAS_MMC_GetPlmnSelectionMode())
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_InitUserSpecPlmnId_SwitchOn:Need not set!");

        return;
    }

    /* SIM卡不存在或存在PIN码,直接返回 */
    if (VOS_FALSE == NAS_MML_GetSimPresentStatus())
    {
        return;
    }

    pstUserPlmnInfo     = NAS_MMC_GetUserSpecPlmnId();

    pstRplmnCfgInfo     = NAS_MML_GetRplmnCfg();

    /* 根据上次关机的接入技术,获取RPLMN,不存在则使用HPLMN */
    if (VOS_FALSE == NAS_MMC_GetLastRplmn_SwitchOn(&stUserPlmn))
    {
        ucLastRplmnExistFlag = VOS_FALSE;

        /* 获取RPLMN失败时,LastRAT为GU时直接获取EFLOCI文件中的PLMN ID */
        if ((VOS_TRUE   == NAS_MML_GetEfLociPlmn(&stGuRplmn))
         && ((NAS_MML_NET_RAT_TYPE_WCDMA == pstRplmnCfgInfo->enLastRplmnRat)
          || (NAS_MML_NET_RAT_TYPE_GSM   == pstRplmnCfgInfo->enLastRplmnRat)))
        {
            stUserPlmn.stPlmnId = stGuRplmn;
            stUserPlmn.enRat    = NAS_MML_NET_RAT_TYPE_WCDMA;
            ucLastRplmnExistFlag = VOS_TRUE;
        }
        else
        {
            pstEHPlmnInfo       = NAS_MML_GetSimEhplmnList();
            stUserPlmn.stPlmnId = pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId;
        }
    }

    if (NAS_MML_NET_RAT_TYPE_BUTT == pstRplmnCfgInfo->enLastRplmnRat)
    {
        NAS_MMC_UpdateLastRplmnRat_LastRplmnRatInvalid_SwitchOn(&stUserPlmn, ucLastRplmnExistFlag);
    }

    stUserPlmn.enRat    = pstRplmnCfgInfo->enLastRplmnRat;

    /* 开机时将指定搜网之前保存的网络设置为RPLMN, RPLMN不存在则设置为HPLMN */
    NAS_MMC_SetUserReselPlmnId(&(stUserPlmn.stPlmnId), stUserPlmn.enRat);

    /* 上次保存的用户指定的PLMN ID有效 */
    if ( VOS_TRUE == NAS_MML_IsPlmnIdValid(&(pstUserPlmnInfo->stPlmnId)))
    {
        return;
    }

    NAS_MMC_SetUserSpecPlmnId(&stUserPlmn);

    return;
}



VOS_UINT32  NAS_MMC_GetLastRplmn_SwitchOn(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstLasRplmn
)
{
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo     = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stGuRplmn;
    VOS_UINT32                          ulGuRplmnExistFlg;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_ID_STRU                stLRplmn;
    VOS_UINT32                          ulLRplmnExistFlg;
#endif

    pstRplmnCfgInfo     = NAS_MML_GetRplmnCfg();

    /* 根据上次关机的接入技术，决定取那个模式的RPLMN */
    switch(pstRplmnCfgInfo->enLastRplmnRat)
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:
        case NAS_MML_NET_RAT_TYPE_GSM:
            /* 获取GU的RPLMN */
            ulGuRplmnExistFlg   = NAS_MML_GetGURPlmn(&stGuRplmn);

            if (VOS_FALSE == ulGuRplmnExistFlg)
            {
                return VOS_FALSE;
            }

            pstLasRplmn->stPlmnId.ulMcc = stGuRplmn.ulMcc;
            pstLasRplmn->stPlmnId.ulMnc = stGuRplmn.ulMnc;
            pstLasRplmn->enRat          = pstRplmnCfgInfo->enLastRplmnRat;
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            /* 获取L的RPLMN */
            ulLRplmnExistFlg    = NAS_MML_GetLteRPlmn(&stLRplmn);

            if (VOS_FALSE == ulLRplmnExistFlg)
            {
                return VOS_FALSE;
            }

            pstLasRplmn->stPlmnId.ulMcc = stLRplmn.ulMcc;
            pstLasRplmn->stPlmnId.ulMnc = stLRplmn.ulMnc;
            pstLasRplmn->enRat          = pstRplmnCfgInfo->enLastRplmnRat;
            break;
#endif

        case NAS_MML_NET_RAT_TYPE_BUTT:
#if (FEATURE_ON == FEATURE_LTE)
            /* 获取L的RPLMN */
            ulLRplmnExistFlg    = NAS_MML_GetLteRPlmn(&stLRplmn);

            if (VOS_TRUE == ulLRplmnExistFlg)
            {
                pstLasRplmn->stPlmnId.ulMcc = stLRplmn.ulMcc;
                pstLasRplmn->stPlmnId.ulMnc = stLRplmn.ulMnc;
                pstLasRplmn->enRat          = NAS_MML_NET_RAT_TYPE_LTE;

                return VOS_TRUE;
            }
#endif
            /* 获取GU的RPLMN */
            ulGuRplmnExistFlg   = NAS_MML_GetGURPlmn(&stGuRplmn);

            if (VOS_FALSE == ulGuRplmnExistFlg)
            {
                return VOS_FALSE;
            }

            pstLasRplmn->stPlmnId.ulMcc = stGuRplmn.ulMcc;
            pstLasRplmn->stPlmnId.ulMnc = stGuRplmn.ulMnc;
            pstLasRplmn->enRat          = NAS_MML_NET_RAT_TYPE_WCDMA;
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetLastRplmn_SwitchOn:Unexpected Rat Type!");
            return VOS_FALSE;
    }


    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_IsImsiChange_SwitchOn(VOS_VOID)
{
    VOS_UINT8                           i;
    VOS_UINT8                          *pucLastImsi         = VOS_NULL_PTR;
    NAS_MML_SIM_MS_IDENTITY_STRU       *pstMsIdentity       = VOS_NULL_PTR;

    pstMsIdentity       = NAS_MML_GetSimMsIdentity();
    pucLastImsi         = NAS_MMC_GetLastImsi_SwitchOn();


    /* 当开机时判断IMSI和上次关机前的IMSI不同时，设置需要进行全频带搜网 */
    /* 获取IMSI长度，当IMSI长度不等时，认为IMSI发生改变 */
    if (pstMsIdentity->aucImsi[0] != pucLastImsi[0])
    {
        return VOS_TRUE;
    }
    else
    {
        /* 还需要判断长度是否合法 */
        if ( pstMsIdentity->aucImsi[0] > NAS_MML_MAX_IMSI_LEN)
        {
            return VOS_TRUE;
        }

        /* IMSI的长度相等，则从第二位开始比较IMSI的内容是否相同 */
        for (i = 1; i < (pstMsIdentity->aucImsi[0] + 1); i++)
        {
            if (pucLastImsi[i] != pstMsIdentity->aucImsi[i])
            {
                return VOS_TRUE;
            }
        }

    }


    return VOS_FALSE;
}


VOS_UINT32 NAS_MMC_IsNeedClearCksn_SwitchOn(VOS_VOID)
{
    NAS_MML_SIM_TYPE_ENUM_UINT8         ucSimType;
    VOS_UINT8                           ucUsimGsmAuthNvCfg;
    VOS_UINT32                          ulIsImsiChange;

    ucSimType                           = NAS_MML_GetSimType();
    ulIsImsiChange                      = NAS_MMC_IsImsiChange_SwitchOn();
    ucUsimGsmAuthNvCfg                  = NAS_MML_GetUsimGsmAuthNvCfg();

    if (VOS_FALSE == ulIsImsiChange)
    {
        return VOS_FALSE;
    }

    if (NAS_MML_SIM_TYPE_USIM != ucSimType)
    {
        return VOS_FALSE;
    }

    if (VOS_FALSE == ucUsimGsmAuthNvCfg)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_VOID NAS_MMC_RcvStartCnf_SwitchOn_ProcAsRatCapabilityStatus (VOS_VOID)
{
    if (VOS_FALSE == NAS_MML_GetImsiInForbiddenListFlg())
    {
        return;
    }

    NAS_MMC_SndAsRatCapabilityStatusChangeInfo();

    #if (FEATURE_ON == FEATURE_LTE)
    /* 如果LTE被禁止，单独通知LTE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        NAS_MMC_SndLmmDisableLteNotify(MMC_LMM_DISABLE_LTE_REASON_IMSI_IN_FORBIDDEN_LIST);

        /* 更新disable LTE能力标记 */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS);

        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_IMSI_IN_FORBIDDEN_LIST);
    }
    #endif

    return;
}


VOS_VOID NAS_MMC_RcvStartCnf_SwitchOn_InitRatForbidListCfg (VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_MML_RAT_FORBIDDEN_LIST_STRU    *pstBlackList = VOS_NULL_PTR;

    i            = 0;
    pstBlackList = NAS_MML_GetRatForbiddenListCfg();

    if (VOS_FALSE == NAS_MML_IsImsiInForbiddenList())
    {
        NAS_MML_SetImsiInForbiddenListFlg(VOS_FALSE);
        return;
    }

    /* 初始化卡是否在禁止列表的全局变量 */
    NAS_MML_SetImsiInForbiddenListFlg(VOS_TRUE);

    /* 初始化每个接入技术的禁止状态 */
    for (i = 0; i < pstBlackList->ucForbidRatNum; i++)
    {
        if (NAS_MML_NET_RAT_TYPE_GSM         == pstBlackList->aenForbidRatList[i])
        {
            NAS_MML_SetGsmForbiddenStatusFlg(NAS_MML_RAT_CAPABILITY_STATUS_DISABLE);
        }
        else if (NAS_MML_NET_RAT_TYPE_WCDMA  == pstBlackList->aenForbidRatList[i])
        {
            NAS_MML_SetUtranForbiddenStatusFlg(NAS_MML_RAT_CAPABILITY_STATUS_DISABLE);
        }
        else if (NAS_MML_NET_RAT_TYPE_LTE    == pstBlackList->aenForbidRatList[i])
        {
            /* 如果UE支持的接入技术为LTE Only则不禁止LTE */
            if (VOS_FALSE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
            {
                NAS_MML_SetLteForbiddenStatusFlg(NAS_MML_RAT_CAPABILITY_STATUS_DISABLE);
            }
        }
        else
        {
        }
    }

    return;
}


VOS_VOID NAS_MMC_ReadNvimInfo_SwitchOn()
{
    /* en_NV_Item_Platform_RAT_CAP */
    NAS_MMC_ReadPlatformRatCapNvim();
    /* en_NV_Item_Gsm_Classmark1 */
    NAS_MMC_ReadClassMark1Nvim();

    /* en_NV_Item_Gsm_Classmark2 */
    NAS_MMC_ReadClassMark2Nvim();

    /* en_NV_Item_IMEI en_NV_Item_Imei_Svn */
    NAS_MMC_ReadImeisvNvim();


    NAS_MMC_ReadRoamingRejectNoRetryFlgNvim();

    /* 从NV中读取协议版本 */
    NAS_MMC_ReadSupported3GppReleaseNvim();

    /* en_NV_Item_NetworkCapability */
    NAS_MMC_ReadNetworkCapabilityNvim();

    /* en_NV_Item_MMA_MsClass */
    NAS_MMC_ReadMsModeNvim();

    /* en_NV_Item_Support_Freqbands */
    NAS_MMC_ReadUserSetBandNvim();


    /* en_NV_Item_EFust_Service_Cfg */
    NAS_MMC_ReadGsmForbidAccessInfoNvim();


    /* en_NV_Item_Use_Single_Rplmn_When_Area_Lost */
    NAS_MMC_ReadUseSingleRplmnFlagNvim();

    /* en_NV_Item_RPlmnWithRat */
    NAS_MMC_ReadRplmnWithRatNvim();

    /* en_NV_Item_Standard_EHplmn_Support_Flg */
    NAS_MMC_ReadEHPlmnSupportNvim();

    /* en_NV_Item_SrchHplmnFlg_StartOrAreaLostInAutoMode */
    NAS_MMC_ReadSearchHPlmnFlgAutoModeNvim();

    /* en_NV_Item_SrchHplmnFlg_StartInManualMode */
    NAS_MMC_ReadSearchHPlmnFlgManualModeNvim();

    /* en_NV_Item_Add_EHPLMN_WHEN_SRCH_HPLMN_CFG */
    NAS_MMC_ReadAddEhplmnWhenSrchHplmnNvim();

    /* en_NV_Item_SearchHplmnAtPowerOn */
    NAS_MMC_ReadSearchHplmnFlgPowerOnNvim();

    /* en_NV_Item_Enhanced_Hplmn_Srch_Flg */
    NAS_MMC_ReadEnhancedHPlmnSearchFlagNvim();

    /* en_NV_Item_Special_Roam_Flag */
    NAS_MMC_ReadSpecialRoamFlgNvim();

    /* en_NV_Item_Network_Name_From_MM_Info */
    NAS_MMC_ReadNetworkNameNvim();

#if (FEATURE_ON == FEATURE_LTE)
    /* en_NV_Item_TIN_INFO */
    NAS_MMC_ReadTinInfoNvim();

    /* en_NV_Item_Lte_Cs_Service_Config */
    NAS_MMC_ReadLteCsServiceConfigNvim();


    NAS_MMC_ReadLteRoamConfigNvim();

    /*软银定制,漫游时掉网先搜RPLMN*/
    NAS_MMC_ReadRPLMNConfigNvim();

    /*软银搜网定制开关*/
    NAS_MMC_ReadSBMCustomDualIMSIConfigNvim();

    NAS_MMC_ReadHoWaitSysinfoTimeLenNvim();


    /* 从NV中读取L协议版本 */
    NAS_MMC_ReadLNasReleaseNvim();
#else
    NAS_MMC_ReadLastImsiNvim();
#endif
    /* en_NV_Item_Csfb_Emg_Call_LaiChg_Lau_First_CFG*/
    NAS_MMC_ReadCsfbEmgCallLaiChgLauFirstNvim();

    NAS_MMC_ReadDailRejectConfigNvim();

    /* en_NV_Item_HPlmnFirstTimer */
    NAS_MMC_ReadHplmnFirstSearchPeriodNvim();

    /* en_NV_Item_Default_Max_Hplmn_Srch_Peri */
    NAS_MMC_ReadDefaultHplmnSrchPeriodNvim();

    NAS_MMC_ReadHighPrioPlmnRefreshTriggerBGSearchFlagNvim();

    /* en_NV_Item_SearchHplmnTtimerValue */
    NAS_MMC_ReadSrchHplmnTtimerValueNvim();

    /* en_NV_Item_OPERLOCK_PLMN_INFO_WHITE */
    NAS_MMC_ReadWhiteOpeLockPlmnInfoNvim();

    /* en_NV_Item_DISABLED_RAT_PLMN_INFO */
    NAS_MMC_ReadDisabledRatPlmnInfoNvim();

    /* en_NV_Item_User_Cfg_Ext_Ehplmn_Info */
    NAS_MMC_ReadUserCfgExtEhplmnInfoNvim();

    /* en_NV_Item_OperLock_Plmn_Info */
    NAS_MMC_ReadBlackOperLockPlmnInfoNvim();



    /* en_NV_Item_Standard_STK_SteeringOfRoaming_Support_Flg */
    NAS_MMC_ReadStandardSTKSteeringOfRoamingFlgNvim();

    /* en_NV_Item_SteeringofRoaming_SUPPORT_CTRL */
    NAS_MMC_ReadCsRejSearchSupportFlagNvim();

    /* en_NV_Item_Autoattach */
    NAS_MMC_ReadAutoAttachNvim();

    /* en_NV_Item_SelPlmn_Mode */
    NAS_MMC_ReadPlmnSelectionModeNvim();

    /* en_NV_Item_EquivalentPlmn */
    NAS_MMC_ReadEquivalentPlmnNvim();

    /* en_NV_Item_Max_Forb_Roam_La */
    NAS_MMC_ReadMaxForbRoamLaNvim();

    /* en_NV_Item_Register_Fail_Cnt */
    NAS_MMC_ReadRoamBrokerRegisterFailCntNvim();

    NAS_MMC_ReadPsLociNvim();

    NAS_MMC_ReadRoamCfgInfoNvim();

    NAS_MMC_ReadDtSingleDomainPlmnSearchNvim();

    /* en_NV_Item_NVIM_WCDMA_PRIORITY_GSM_SUPPORT_FLG */
    NAS_MMC_ReaducWcdmaPriorityGsmNvim();

    /* en_NV_Item_NVIM_PS_ONLY_CS_SERVICE_SUPPORT_FLG */
    NAS_MMC_ReadPsOnlyCsServiceSupportNvim();

    /* en_NV_Item_System_APP_Config */
    NAS_MMC_ReadAPPConfigSupportNvim();

    NAS_MMC_ReadAisRoamingNvim();


    NAS_MMC_ReadUserAutoReselCfgNvim();


    NAS_MMC_ReadScanCtrlNvim();

    /* en_NV_Item_ACTING_PLMN_SUPPORT_FLAG */
    NAS_MMC_ReadActingHPlmnSupportNvim();

    /* en_NV_Item_Hplmn_Search_Regardless_Mcc_Support */
    NAS_MMC_ReadHPlmnSearchRegardLessMccNvim();

    /* en_NV_Item_SINGLE_DOMAIN_FAIL_ACTION_LIST */
    NAS_MMC_ReadSingleDomainFailActionListNvim();

    /* en_NV_Item_CS_FAIL_NETWORK_FAILURE_PLMN_SEARCH_FLAG */
    NAS_MMC_ReadRegFailNetWorkFailureCustomFlagNvim();



    /* en_NV_Item_PRIO_HPLMNACT_CFG */
    NAS_MMC_ReadPrioHplmnActCfgNvim();


    NAS_MMC_ReadPlmnExactlyCompareNvim();

    NAS_MMC_ReadCustomizeServiceNvim();

    NAS_MMC_ReadHplmnRegisterCtrlNvim();

    NAS_MMC_ReadCellSignReportCfgNvim();

    NAS_MMC_ReadUcs2CustomizationNvim();

    NAS_MMC_ReadCloseSmsCapabilityConfigNvim();

    NAS_MMC_ReadH3gCtrlNvim();

#if  (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_ReadEnableLteTimerLenNvim();

    NAS_MMC_ReadDisableLteStartT3402EnableLteCfgNvim();

    NAS_MMC_ReadCsfbRauFollowOnFlgNvim();

    NAS_MMC_ReadLteCustomMccInfoNvim();

    NAS_MMC_ReadUltraFlashCsfbSupportFlgNvim();

    /* 0xD20B这个NV项会更新aucNetworkCapability中的srvcc能力，如果和8197中的配置不一致，以0xD20B中的为准
       该NV要放在8197 NV项之后读取 */
    NAS_MMC_ReadSrvccSupportFlgNvim();
#endif

    NAS_MMC_ReadSvlteSupportFlagNvim();

    NAS_MMC_ReadPsTransferCfgNvim();

    NAS_MMC_ReadIsrSupportNvim( );
    NAS_MMC_ReadAccBarPlmnSearchNvim();
    NAS_MMC_ReadUserCfgOPlmnInfoNvim();

#if (FEATURE_ON == FEATURE_PTM)
    NAS_MMC_ReadErrlogCtrlInfoNvim();
    NAS_MMC_ReadErrlogNwSrchRecordcfgNvim();
#endif

    NAS_VSIM_InitVsimCfgInfo();

    NAS_MMC_ReadRatForbiddenListConfigNvim();

     NAS_MMC_ReadDsdaPlmnSearchEnhancedCfgNvim();

#if (FEATURE_ON == FEATURE_DSDS)
    NAS_MMC_ReadModemRfShareCfgNvim();

    NAS_MMC_ReadDsdsEndSessionDelayNvim();
#endif
    NAS_MMC_ReadWgRfMainBandNvim();

    NAS_MMC_ReadImsVoiceMMEnableNvim();

    NAS_MMC_ReadLcCtrlParaNvim();

    NAS_MMC_ReadCsOnlyDataServiceSupportNvim();

    NAS_MMC_ReadIgnoreAuthRejFlgNvim();
    NAS_MMC_ReadLteDisabledUseLteInfoFlagNvim();

    NAS_MMC_ReadHighPrioRatHplmnTimerCfgNvim();

    NAS_MMC_Read3GPP2UplmnNotPrefFlgNvim();

    NAS_MMC_ReadSyscfgTriPlmnSrchCfgNvim();

    NAS_MMC_ReadUmtsCodecTypeNvim();
    NAS_MMC_ReadMedCodecTypeNvim();
    NAS_MMC_ReadDplmnNplmnInfoNvim();
    NAS_MMC_ReadChangeNwCauseCfgNvim( );

    NAS_MMC_ReadRelPsSignalConCfgNvim();

#if  (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_ReadLteRejCause14CfgNvim();
#endif

#if  (FEATURE_ON == FEATURE_IMS)
    NAS_MMC_ReadImsRatSupportNvim();
    NAS_MMC_ReadImsCapNvim();
    NAS_MMC_ReadUssdOnImsNvim();
#endif

    NAS_MMC_ReadDsdsActiveModemModeNvim();

    NAS_MMC_ReadDamCfgNvim();
    NAS_MMC_ReadCsmoSupportedCfgNvim();

    NAS_MMC_ReadT3212TimerCfgNvim();

    NAS_MMC_ReadRoamDisplayCfgNvim();
    NAS_MMC_ReadProtectMtCsfbPagingProcedureLenNvim();

    NAS_MMC_ReadLowPrioAnycellsearchLteCfgNvim();
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_ReadLteOos2GPrefPlmnSelCfgNvim();
#endif

#if (FEATURE_ON == FEATURE_CSG)
    NAS_MMC_ReadCsgCfgNvim();
#endif
    NAS_MMC_ReadRoamPlmnSelectionSortCfgNvim();
    NAS_MMC_ReadGetGeoCfgInfoNvim();
    NAS_MMC_ReadNonOosPlmnSearchFeatureSupportCfgNvim();

    NAS_MMC_ReadOosPlmnSearchStrategyCfgNvim();

    NAS_MMC_ReadPsRegFailMaxTimesTrigLauOnceFlgNvim();
    NAS_MMC_ReadKeepSrchHplmnEvenRejByCause13Nvim();
    NAS_MMC_ReadEpsRejByCause14InVplmnAllowPsRegFlgNvim();
    NAS_MMC_ReadCarryEplmnWhenSrchRplmnCfgNvim();
    NAS_MMC_ReadLauRejNeedNoRetryWhenCmSrvExistNvim();
    NAS_MMC_ReadLauRejTrigPlmnSearchNvim();


    NAS_MMC_ReadRefreshRplmnWhenEplmnInvalidCfgNvim();

    NAS_MMC_ReadCsRegFailForbLaTimeCfgNvim();

    NAS_MMC_ReadKeepCsForbInfoWhenPsRegSuccCfgNvim();

    NAS_MMC_ReadClearCksnCfgNvim();

    return;
}



VOS_VOID NAS_MMC_SavePlmnRatPrio_SwitchOn(
    MSCC_MMC_PLMN_RAT_PRIO_STRU          *pRcvPlmnRatPrio
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatPrioList = VOS_NULL_PTR;

    pstRatPrioList           = NAS_MML_GetMsPrioRatList();
    pstRatPrioList->ucRatNum = pRcvPlmnRatPrio->ucRatNum;

    PS_MEM_CPY(pstRatPrioList->aucRatPrio, pRcvPlmnRatPrio->aucRatPrio, NAS_MML_MAX_RAT_NUM);

    return;
}


VOS_VOID NAS_MMC_Save3Gpp2RatPrio_SwitchOn(
    MSCC_MMC_3GPP2_RAT_STRU             *pst3Gpp2Rat
)
{
    NAS_MML_3GPP2_RAT_PRIO_STRU        *pst3Gpp2RatPrioList = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pst3Gpp2RatPrioList           = NAS_MML_GetMs3Gpp2PrioRatList();

    /* 个数赋值 */
    pst3Gpp2RatPrioList->ucRatNum = pst3Gpp2Rat->ucRatNum;

    /* 防止个数异常导致数组越界 */
    if ( pst3Gpp2RatPrioList->ucRatNum > NAS_MML_MAX_3GPP2_RAT_NUM )
    {
        pst3Gpp2RatPrioList->ucRatNum = NAS_MML_MAX_3GPP2_RAT_NUM;
    }

    /* 保存数组内容 */
    for ( i = 0 ; i < pst3Gpp2RatPrioList->ucRatNum; i++ )
    {
        /* 将MSCC传递过来的3GPP2类型转换为MML格式 */
        NAS_MMC_Convert3GPP2RatType( pst3Gpp2Rat->auc3GPP2Rat[i],
                                     &(pst3Gpp2RatPrioList->aucRatPrio[i]));
    }

    return;
}


VOS_VOID NAS_MMC_SaveAllowRegDomain_SwitchOn(
    NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_ENUM_UINT8                   enRegDomain
)
{
    switch (enRegDomain)
    {
        case NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_PS:
            NAS_MML_SetPsAttachAllowFlg(VOS_TRUE);
            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            break;

        case NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_CS:
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
            break;

        case NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_CS_PS:
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            NAS_MML_SetPsAttachAllowFlg(VOS_TRUE);
            break;

        default:
            break;
    }

    return;
}


VOS_VOID NAS_MMC_SndRatModeSwitchOnReq_SwitchOn(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrSwitchOnRat
)
{
    /* 根据接入模式，进行SwitchOn的设置 */
    switch ( enCurrSwitchOnRat )
    {

#if (FEATURE_ON == FEATURE_LTE)

        case NAS_MML_NET_RAT_TYPE_LTE:
            NAS_TRACE_HIGH("Send start req to LTE!");

            /* 向L模下发SwitchOn设置请求 */
            NAS_MMC_SndLmmStartReq();
            NAS_MMC_AddSwitchOnIndex_SwitchOn();

            /* 进行SwitchOn状态机的子状态的迁移 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_SWITCH_ON_STA_WAIT_L_START_CNF);

            /* 启动等待回复定时器 */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_START_CNF, TI_NAS_MMC_WAIT_LMM_START_CNF_LEN);
            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:
            NAS_TRACE_HIGH("Send start req to %s!",
                (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode()) ? "WRRC" : "TRRC");

            /* 向w模下发SwitchOn设置请求 */
            NAS_MMC_SndAsStartReq(WUEPS_PID_WRR);
            NAS_MMC_AddSwitchOnIndex_SwitchOn();

            /* 进行SwitchOn状态机的子状态的迁移 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_SWITCH_ON_STA_WAIT_WAS_START_CNF);

            /* 启动等待回复定时器 */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_START_CNF, TI_NAS_MMC_WAIT_WAS_START_CNF_LEN);
            break;

        case NAS_MML_NET_RAT_TYPE_GSM:
            NAS_TRACE_HIGH("Send start req to GAS!");

            /* 向G模下发SwitchOn设置请求 */
            NAS_MMC_SndAsStartReq(UEPS_PID_GAS);
            NAS_MMC_AddSwitchOnIndex_SwitchOn();

            /* 进行SwitchOn状态机的子状态的迁移 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_SWITCH_ON_STA_WAIT_GAS_START_CNF);

            /* 启动等待回复定时器 */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_START_CNF, TI_NAS_MMC_WAIT_GAS_START_CNF_LEN);
            break;

        default:
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndRatModeSwitchOnReq_SwitchOn():Invalid net rat type");
            break;
    }

    return;
}


VOS_VOID NAS_MMC_UpdateEhplmnInfo_SwitchOn(
    VOS_UINT8                           *pucImsi
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           ucUserCfgEhplmnListNum;
    NAS_MML_PLMN_ID_STRU                astUserCfgEhPlmnList[NAS_MML_MAX_USER_CFG_EHPLMN_NUM];
    VOS_UINT16                          usUeSptRat;
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstSimEhplmnInfo    = VOS_NULL_PTR;

#if (FEATURE_ON == FEATURE_LTE)
    usUeSptRat                          = NAS_MML_SIM_UE_SUPPORT_RAT_SUPPORT_LTE;
#else
    usUeSptRat                          = NAS_MML_SIM_UE_SUPPORT_RAT;
#endif

    pstSimEhplmnInfo                    = NAS_MML_GetSimEhplmnList();
    ucUserCfgEhplmnListNum              = 0;
    PS_MEM_SET(astUserCfgEhPlmnList, (VOS_UINT8)0X00, sizeof(astUserCfgEhPlmnList));

    /* 根据IMSI信息，解析en_NV_Item_User_Cfg_Ehplmn中的Ehplmn */
    NAS_MML_GetValidUserCfgEhplmnInfo( pucImsi,
                                       &ucUserCfgEhplmnListNum,
                                       astUserCfgEhPlmnList );

    /* 如果当前当前用户没有通过NV配置EHPLMN，即有效的EHplmn的个数为0个，
       则将IMSI中的HOME PLMN更新到EHplmn列表中 */
    if ( 0 == ucUserCfgEhplmnListNum )
    {
        NAS_MMC_UpdateHomePlmn(pucImsi);

        /* 更新当前HPLMN的类型 */
        NAS_MML_SetHPlmnType(NAS_MML_HPLMN_TYPE_HPLMN);
    }
    else
    {
        /* 将用户配置的EHplmn列表信息加入到USIM/SIM卡中保存的EHplmn信息里 */
        pstSimEhplmnInfo->ucEhPlmnNum = ucUserCfgEhplmnListNum;
        for ( i = 0; i < ucUserCfgEhplmnListNum; i++ )
        {
            pstSimEhplmnInfo->astEhPlmnInfo[i].stPlmnId = astUserCfgEhPlmnList[i];
            pstSimEhplmnInfo->astEhPlmnInfo[i].usSimRat = usUeSptRat;
        }

        NAS_MML_SetHPlmnType(NAS_MML_HPLMN_TYPE_EHPLMN);
    }

    return;
}


VOS_VOID NAS_MMC_InitLastRplmnRat_SwitchOn(VOS_VOID)
{
    NAS_MML_RPLMN_CFG_INFO_STRU             *pstRplmnCfgInfo     = VOS_NULL_PTR;

    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

    if (VOS_TRUE   == NAS_MMC_IsImsiChange_SwitchOn())
    {
        /* 非SIM卡时,初始化为BUTT;
           SIM卡时,当非LTE ONLY时,因为需要disable LTE,所以初始化为次高优先级的RAT */
        pstRplmnCfgInfo->enLastRplmnRat = NAS_MML_NET_RAT_TYPE_BUTT;

        /* 将新RAT记入NV */
        NAS_MMC_WriteRplmnWithRatNvim();
    }


}




/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

