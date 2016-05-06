/******************************************************************************

                  版权所有 (C), 2001-2013, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MtcComm.c
  版 本 号   : 初稿
  作    者   : l00198894
  生成日期   : 2013年08月19日
  最近修改   :
  功能描述   : MTC模块Modem状态公共消息处理文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年08月19日
    作    者   : l00198894
    修改内容   : 新生成

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "MtcComm.h"
#include "MtcCtx.h"
#include "MtcIntrusion.h"
#include "MtcMmaInterface.h"
#include "MtcDebug.h"
#include "TafMtcInterface.h"

#include "MtcPsTransfer.h"
#include "CmmcaMtcInterface.h"
#include "MtcRfLcdIntrusion.h"

/* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
#include "ImsaMtcInterface.h"
#include "TafMtcApi.h"
#include "MtcMrma.h"
/* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, End */
#include  "NVIM_Interface.h"
#include "MtcCalcFreq.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

/*lint -e767 修改人: l00198894; */
#define    THIS_FILE_ID        PS_FILE_ID_MTC_COMM_C
/*lint +e767 修改人: l00198894; */

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/* Added by l00198894 for V9R1 Notch Bypass项目, 2013-12-21, begin */
/*****************************************************************************
 函 数 名  : MTC_GetIntrusionActionEnableFlag
 功能描述  : 获取频段信息上报使能标志
 输入参数  : PS_BOOL_ENUM_UINT8 enFlag
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月21日
    作    者   : l00198894
    修改内容   : V9R1 Notch Bypass项目
  2.日    期   : 2014年02月13日
    作    者   : f00179208
    修改内容   : Jazz Narrow Band dcs项目
  3.日    期   : 2014年3月24日
    作    者   : A00165503
    修改内容   : B39&B32 Intrusion
*****************************************************************************/
PS_BOOL_ENUM_UINT8 MTC_GetIntrusionActionEnableFlag(VOS_VOID)
{
    MTC_CFG_ENUM_UINT8                  enIntrusionCfg;
    MTC_CFG_ENUM_UINT8                  enNotchCfg;
    MTC_CFG_ENUM_UINT8                  enNarrowBandDcsCfg;
    MTC_CFG_ENUM_UINT8                  enTlRfCtrlCfg;

    enIntrusionCfg      = MTC_GetIntrusionCfg();
    enNotchCfg          = MTC_GetNotchCfg();
    enNarrowBandDcsCfg  = MTC_GetNarrowBandDcsCfg();
    enTlRfCtrlCfg   = MTC_GetTlRfCtrlCfg();

    if ((MTC_CFG_ENABLE == enIntrusionCfg)
     || (MTC_CFG_ENABLE == enNotchCfg)
     || (MTC_CFG_ENABLE == enNarrowBandDcsCfg)
     || (MTC_CFG_ENABLE == enTlRfCtrlCfg))
    {
        return PS_TRUE;
    }

    return PS_FALSE;
}
/* Added by l00198894 for V9R1 Notch Bypass项目, 2013-12-21, end */

/*****************************************************************************
 函 数 名  : MTC_GetOtherModemId
 功能描述  : 获取另一个ModemID
 输入参数  : enModemId          -- 源ModemID
             penOtherModemId    -- 另一个ModemID
 输出参数  : 无
 返 回 值  : VOS_OK             -- 获取成功
             VOS_ERR            -- 获取失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年01月17日
    作    者   : l00198894
    修改内容   : V9R1C53 C+L 离网重选项目
*****************************************************************************/
VOS_UINT32 MTC_GetOtherModemId(
    MODEM_ID_ENUM_UINT16                enModemId,
    MODEM_ID_ENUM_UINT16               *penOtherModemId
)
{

    if (MODEM_ID_0 == enModemId)
    {
        *penOtherModemId = MODEM_ID_1;
    }
    else if (MODEM_ID_1 == enModemId)
    {
        *penOtherModemId = MODEM_ID_0;
    }
    else
    {
        return VOS_ERR;
    }

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : MTC_ProcModem0BufMsg
 功能描述  : MTC模块处理缓存消息
 输入参数  : VOS_VOID
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月13日
    作    者   : l00198894
    修改内容   : V9R1 干扰控制项目
*****************************************************************************/
VOS_VOID MTC_ProcModem0BufMsg(VOS_VOID)
{
    MTC_MSG_BUF_STRU                       *pstBufAddr     = VOS_NULL_PTR;
    RRC_MTC_INTRUSION_BAND_INFO_IND_STRU   *pstBandInfoMsg      = VOS_NULL_PTR;
    RRC_MTC_USING_FREQ_IND_STRU            *pstUsingFreqInfoMsg = VOS_NULL_PTR;

    /* 清空Band信息和临区中的TL Band信息 */
    MTC_ResetNCellBandInfo(MODEM_ID_0);
    MTC_ResetModemCurBandInfo(MODEM_ID_0);

    pstBufAddr          = MTC_GetBufAddr(MODEM_ID_0);
    pstBandInfoMsg      = &(pstBufAddr->stBufBandInfoMsg.stIntrusionBandInfoMsg);
    pstUsingFreqInfoMsg = &(pstBufAddr->stBufUsingFreqInfoMsg.stUsingFreqInfoMsg);

    if (PS_TRUE == pstBufAddr->stBufBandInfoMsg.enExitBufMsgFlag)
    {
        if (PS_TRUE == MTC_IsNeedPopModem0BufMsg(pstBandInfoMsg->stMsgHeader.ulSenderPid))
        {
            /* 清缓存标志 */
            pstBufAddr->stBufBandInfoMsg.enExitBufMsgFlag = PS_FALSE;

            MTC_RcvIntrusionBandInfoInd((VOS_VOID*)pstBandInfoMsg);
        }
    }

    if (PS_TRUE == pstBufAddr->stBufUsingFreqInfoMsg.enExitBufMsgFlag)
    {
        if (PS_TRUE == MTC_IsNeedPopModem0BufMsg(pstUsingFreqInfoMsg->stMsgHeader.ulSenderPid))
        {
            /* 清缓存标志 */
            pstBufAddr->stBufUsingFreqInfoMsg.enExitBufMsgFlag = PS_FALSE;

            MTC_RcvRrcUsingFreqInd((VOS_VOID*)pstUsingFreqInfoMsg);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : MTC_RcvMmaRatModeInd
 功能描述  : MTC模块接收MMA模块通知的接入模式信息
 输入参数  : MsgBlock* pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月13日
    作    者   : l00198894
    修改内容   : V9R1 干扰控制项目
*****************************************************************************/
VOS_VOID MTC_RcvMmaRatModeInd(VOS_VOID *pMsg)
{
    MMA_MTC_RAT_MODE_IND_STRU              *pstRatMode          = VOS_NULL_PTR;
    VOS_UINT32                              ulPid;
    MODEM_ID_ENUM_UINT16                    enModemId;
    MTC_RATMODE_ENUM_UINT8                  enOldRatMode;

    pstRatMode  = (MMA_MTC_RAT_MODE_IND_STRU *)pMsg;
    ulPid       = pstRatMode->stMsgHeader.ulSenderPid;

    /* 根据 Pid获取modem ID */
    enModemId   = VOS_GetModemIDFromPid(ulPid);
    if (enModemId >= MODEM_ID_BUTT)
    {
        MTC_ERROR_LOG("MTC_RcvMmaRatModeInd: Modem ID Err.");
        return ;
    }

    enOldRatMode = MTC_GetModemRatMode(enModemId);
    /* 接入模式变化 */
    if (enOldRatMode != pstRatMode->enRatMode)
    {
        /* 更新Modem的接入模式 */
        MTC_SetModemRatMode(enModemId, pstRatMode->enRatMode);

        /* 模式变化执行notch裁决 */
        if (MODEM_ID_0 == enModemId)
        {
            MTC_ProcModem0BufMsg();
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : MTC_RcvMmaCurrCampPlmnInfoInd
 功能描述  : MTC模块接收MMA模块通知的当前驻留plmn相关信息
 输入参数  : MsgBlock* pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月23日
    作    者   : z00161729
    修改内容   : SVLTE优化G-TL ps切换性能修改
  2.日    期   : 2013年12月24日
    作    者   : z00161729
    修改内容   : SVLTE支持NCELL搜网
  3.日    期   : 2014年1月6日
    作    者   : z00161729
    修改内容   : DTS2014010202583:SVLTE优化G-TL ps切换性能修改
  4.日    期   : 2014年01月17日
    作    者   : l00198894
    修改内容   : V9R1C53 C+L 离网重选项目
  5.日    期   : 2014年11月17日
    作    者   : l00198894
    修改内容   : ECID命令产品线定制需求
  6.日    期   : 2015年01月07日
    作    者   : l00198894
    修改内容   : DTS2015010702687: 中国区跳过W搜网不生效
  3.日    期   : 2015年05月30日
    作    者   : w00281933
    修改内容   : TSTS
*****************************************************************************/
VOS_VOID MTC_RcvMmaCurrCampPlmnInfoInd(VOS_VOID *pMsg)
{
    VOS_UINT32                                  ulPid;
    MODEM_ID_ENUM_UINT16                        enModemId;
    MODEM_ID_ENUM_UINT16                        enOtherModemId;
    MMA_MTC_CURR_CAMP_PLMN_INFO_IND_STRU       *pstCurrCampPlmnInfo = VOS_NULL_PTR;
    MTC_MODEM_NETWORK_INFO_STRU                *pstNetworkInfo      = VOS_NULL_PTR;
    MTC_GSM_CELLINFO_EX_STRU                   *pstGsmCellInfoEx    = VOS_NULL_PTR;
    MTC_OPERATOR_CUST_SOLUTION_ENUM_UINT8       enOperatorCustSolution;
    MTC_RATMODE_ENUM_UINT8                      enOldRatMode;

    pstCurrCampPlmnInfo = (MMA_MTC_CURR_CAMP_PLMN_INFO_IND_STRU *)pMsg;
    ulPid               = pstCurrCampPlmnInfo->stMsgHeader.ulSenderPid;

    /* 根据 Pid获取modem ID */
    enModemId           = VOS_GetModemIDFromPid(ulPid);
    enOtherModemId      = MODEM_ID_BUTT;

    if (enModemId >= MODEM_ID_BUTT)
    {
        MTC_ERROR_LOG("MTC_RcvMmaCurrCampPlmnInfoInd: Modem ID Err.");
        return ;
    }

    /* 保存Modem系统消息中的Modem网络信息 */
    pstNetworkInfo      = MTC_GetModemNetworkInfoAddr(enModemId);
    pstNetworkInfo->stPlmnId                            = pstCurrCampPlmnInfo->stPlmnId;
    pstNetworkInfo->stPsDomainInfo.ucPsSupportFlg       = pstCurrCampPlmnInfo->ucPsSupportFlg;
    pstNetworkInfo->stPsDomainInfo.ucPsAttachAllowFlg   = pstCurrCampPlmnInfo->ucPsAttachAllowFlag;
    pstNetworkInfo->ucIsForbiddenPlmnFlag               = pstCurrCampPlmnInfo->ucIsForbiddenPlmnFlag;

    enOldRatMode = MTC_GetModemRatMode(enModemId);
    if (enOldRatMode != pstCurrCampPlmnInfo->enRatMode)
    {
        MTC_SetModemRatMode(enModemId, pstCurrCampPlmnInfo->enRatMode);

        /* 模式变化执行notch裁决 */
        if (MODEM_ID_0 == enModemId)
        {
            MTC_ProcModem0BufMsg();
        }
    }

    if (MTC_RATMODE_GSM != pstCurrCampPlmnInfo->enRatMode)
    {
        /* 模式切换为非GSM模式需要清空GSM小区扩展信息 */
        pstGsmCellInfoEx = MTC_GetModemGsmCellInfoEx(enModemId);
        PS_MEM_SET(pstGsmCellInfoEx, 0, sizeof(MTC_GSM_CELLINFO_EX_STRU));
    }

    if (MODEM_ID_2 == enModemId)
    {
        /* 当前Modem2没有相关需求，仅保存全局变量 */
        return;
    }

    /* 获取当前运营商的定制方案 */
    enOperatorCustSolution = MTC_GetOperatorCustSolution();

    /* 无条件通知另一个Modem当前的PLMN ID */
    if (VOS_OK == MTC_GetOtherModemId(enModemId, &enOtherModemId))
    {
        /* 通知modem0的mmc modem1的驻留信息，UTRAN 搜网T/W的状态中，
            额外判断副卡的PLMN。如果发现中国区的，跳过W的搜索*/
        MTC_SndMmaOtherModemInfoNotify(enOtherModemId,
                                       &pstCurrCampPlmnInfo->stPlmnId,
                                       VOS_NULL_PTR);
    }

    /* PS域迁移策略开启时触发流程 */
    if (MTC_PS_TRANSFER_NONE == MTC_GetPsTransferCfg())
    {
        return;
    }

    /* 处理Modem0发送的驻留plmn消息 */
    if (MODEM_ID_0 == enModemId)
    {
        switch (enOperatorCustSolution)
        {
            case MTC_OPERATOR_CUST_CMCC_SVLTE:
                MTC_ProcCurrCampPlmnInfoForSvlte();
                break;
            case MTC_OPERATOR_CUST_CT_LC:
                MTC_ProcCurrCampPlmnInfoForLC();
                break;
            default:
                break;
        }
    }

    return;
}


/*****************************************************************************
 函 数 名  : MTC_RcvMmaEplmnInfoInd
 功能描述  : MTC模块接收MMA模块通知的当前驻留plmn等效plmn信息
 输入参数  : MsgBlock* pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月24日
    作    者   : z00161729
    修改内容   : SVLTE支持NCELL搜网
  2.日    期   : 2014年01月17日
    作    者   : l00198894
    修改内容   : V9R1C53 C+L 离网重选项目
  3.日    期   : 2015年05月30日
    作    者   : w00281933
    修改内容   : Modified for The TSTS Project
*****************************************************************************/
VOS_VOID MTC_RcvMmaEplmnInfoInd(VOS_VOID *pMsg)
{
    VOS_UINT32                                              ulPid;
    MODEM_ID_ENUM_UINT16                                    enModemId;
    MODEM_ID_ENUM_UINT16                                    enOtherModemId;
    MMA_MTC_EPLMN_INFO_IND_STRU                            *pstEplmnInfo = VOS_NULL_PTR;

    pstEplmnInfo    = (MMA_MTC_EPLMN_INFO_IND_STRU *)pMsg;
    ulPid           = pstEplmnInfo->stMsgHeader.ulSenderPid;

    /* 根据 Pid获取modem ID */
    enModemId       = VOS_GetModemIDFromPid(ulPid);
    enOtherModemId  = MODEM_ID_BUTT;

    if (enModemId >= MODEM_ID_BUTT)
    {
        MTC_ERROR_LOG("MTC_RcvMmaEplmnInfoInd: Modem ID Err.");
        return ;
    }

    if (MODEM_ID_2 == enModemId)
    {
        /* Modem2没有EPLMN处理需求 */
        return;
    }

    /* 只有在PS域迁移策略使能时才执行后续流程 */
    if (MTC_PS_TRANSFER_NONE == MTC_GetPsTransferCfg())
    {
        return;
    }

    /* 只有中移SVLTE方案才需要同步两个Modem的等效PLMN */
    if (MTC_OPERATOR_CUST_CMCC_SVLTE == MTC_GetOperatorCustSolution())
    {
        if (VOS_OK == MTC_GetOtherModemId(enModemId, &enOtherModemId))
        {
            MTC_SndMmaOtherModemInfoNotify(enOtherModemId, VOS_NULL_PTR, &pstEplmnInfo->stEplmnInfo);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : MTC_RcvRrcNcellInfoInd
 功能描述  : gas上报tds和l的频点信息消息处理
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月24日
    作    者   : z00161729
    修改内容   : SVLTE支持NCELL搜网
  2.日    期   : 2014年01月17日
    作    者   : l00198894
    修改内容   : V9R1C53 C+L 离网重选项目
  3.日    期   : 2015年05月30日
    作    者   : w00281933
    修改内容   : Modified for The TSTS Project

*****************************************************************************/
VOS_VOID MTC_RcvRrcNcellInfoInd(VOS_VOID * pMsg)
{
    MODEM_ID_ENUM_UINT16                                    enModemId;
    MODEM_ID_ENUM_UINT16                                    enOtherModemId;
    RRC_MTC_NCELL_INFO_IND_STRU                            *pstNcellInfoInd;
    MTC_MMA_TDS_NCELL_INFO_STRU                             stTdsNcellInfo;
    MTC_MMA_LTE_NCELL_INFO_STRU                             stLteNcellInfo;

    pstNcellInfoInd = (RRC_MTC_NCELL_INFO_IND_STRU*)pMsg;
    enModemId       = VOS_GetModemIDFromPid(pstNcellInfoInd->stMsgHeader.ulSenderPid);
    enOtherModemId  = MODEM_ID_BUTT;

    PS_MEM_SET(&stTdsNcellInfo, 0x00, sizeof(stTdsNcellInfo));
    PS_MEM_SET(&stLteNcellInfo, 0x00, sizeof(stLteNcellInfo));

    if (enModemId >= MODEM_ID_BUTT)
    {
        MTC_ERROR1_LOG("MTC_RcvRrcNcellInfoInd: Err ModemId ", enModemId);
        return;
    }

    if (MODEM_ID_2 == enModemId)
    {
        /* Modem2没有NCELL INFO的处理需求 */
        return;
    }

    /* 只有在PS域迁移策略使能时才执行后续流程 */
    if (MTC_PS_TRANSFER_NONE == MTC_GetPsTransferCfg())
    {
        return;
    }

    /* 只有中移SVLTE方案才需要发送 */
    if (MTC_OPERATOR_CUST_CMCC_SVLTE == MTC_GetOperatorCustSolution())
    {
        if (VOS_OK == MTC_GetOtherModemId(enModemId, &enOtherModemId))
        {
            stTdsNcellInfo.ucTdsArfcnNum = pstNcellInfoInd->stTdsNCellInfo.ucTdsArfcnNum;
            PS_MEM_CPY(stTdsNcellInfo.ausTdsArfcnList, pstNcellInfoInd->stTdsNCellInfo.ausTdsArfcnList,
                       sizeof(stTdsNcellInfo.ausTdsArfcnList));
            stLteNcellInfo.ucLteArfcnNum = pstNcellInfoInd->stLteNCellInfo.ucLteArfcnNum;
            PS_MEM_CPY(stLteNcellInfo.aulLteArfcnList, pstNcellInfoInd->stLteNCellInfo.aulLteArfcnList,
                       sizeof(stLteNcellInfo.aulLteArfcnList));
            MTC_SndMmaNcellInfoInd(enOtherModemId, &stTdsNcellInfo, &stLteNcellInfo);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : MTC_RcvMmaRegStatusInd
 功能描述  : MTC模块接收MMA模块通知的注册状态相关信息
 输入参数  : MsgBlock* pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月23日
    作    者   : z00161729
    修改内容   : DTS2014012305088:svlte特性开启卡无效场景mtc无需上报pstransfer:0

*****************************************************************************/
VOS_VOID MTC_RcvMmaRegStatusInd(VOS_VOID *pMsg)
{
    VOS_UINT32                          ulPid;
    MODEM_ID_ENUM_UINT16                enModemId;
    MMA_MTC_REG_STATUS_IND_STRU        *pstRegStatusInd = VOS_NULL_PTR;

    pstRegStatusInd = (MMA_MTC_REG_STATUS_IND_STRU *)pMsg;
    ulPid           = pstRegStatusInd->stMsgHeader.ulSenderPid;

    /* 根据 Pid获取modem ID */
    enModemId       = VOS_GetModemIDFromPid(ulPid);
    if (enModemId >= MODEM_ID_BUTT)
    {
        MTC_ERROR_LOG("MTC_RcvMmaRegStatusInd: Modem ID Err.");
        return ;
    }

    /* 更新卡是否有效标识 */
    MTC_SetModemUsimValidFlag(enModemId, pstRegStatusInd->ucIsUsimValidFlg);
    return;
}



/*****************************************************************************
 函 数 名  : MTC_SndMmaOtherModemDplmnNplmnInfoNotify
 功能描述  : 通知Modem0的mma modem1的nplmn和dplmn信息
 输入参数  : enModemId          - Modem ID
             enOtherModemId     - Other Modem ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月3日
   作    者   : z00161729
   修改内容   : 开机漫游搜网项目修改
*****************************************************************************/
VOS_VOID MTC_SndMmaOtherModemDplmnNplmnInfoNotify(
    MODEM_ID_ENUM_UINT16                enModemId,
    MODEM_ID_ENUM_UINT16                enOtherModemId
)
{
    VOS_UINT32                                              ulMsgLenth;
    VOS_UINT32                                              ulNvLen;
    VOS_UINT32                                              ulReceivePid;
    MTC_MMA_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU       *pstOtherModemDplmnNplmnInfoNotify = VOS_NULL_PTR;
    NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU                 *pstNvimCfgDPlmnNPlmnInfo = VOS_NULL_PTR;
    NAS_MMC_NVIM_DPLMN_NPLMN_CFG_STRU                       stNvimDPlmnNPlmnCfg;

    PS_MEM_SET(&stNvimDPlmnNPlmnCfg, 0x00, sizeof(NAS_MMC_NVIM_DPLMN_NPLMN_CFG_STRU));
    ulMsgLenth = 0;
    ulNvLen    = 0;
    ulMsgLenth = sizeof(MTC_MMA_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;

    if (MODEM_ID_0 == enOtherModemId)
    {
        ulReceivePid = I0_WUEPS_PID_MMA;
    }
    else if (MODEM_ID_1 == enOtherModemId)
    {
        ulReceivePid = I1_WUEPS_PID_MMA;
    }
    else
    {
        MTC_ERROR_LOG("MTC_SndMmaOtherModemDplmnNplmnInfoNotify: Error Modem Id!");
        return;
    }

    /* 分配消息空间 */
    pstOtherModemDplmnNplmnInfoNotify = (MTC_MMA_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU*)PS_ALLOC_MSG(UEPS_PID_MTC, ulMsgLenth);

    if (VOS_NULL_PTR == pstOtherModemDplmnNplmnInfoNotify)
    {
        MTC_ERROR_LOG("MTC_SndMmaOtherModemDplmnNplmnInfoNotify: Alloc msg fail!");
        return;
    }

    /* 清消息空间 */
    PS_MEM_SET((VOS_UINT8*)pstOtherModemDplmnNplmnInfoNotify + VOS_MSG_HEAD_LENGTH, 0, ulMsgLenth);

    pstNvimCfgDPlmnNPlmnInfo = (NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU*)PS_MEM_ALLOC(
                                                      UEPS_PID_MTC,
                                                      sizeof(NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU));
    if (VOS_NULL_PTR == pstNvimCfgDPlmnNPlmnInfo)
    {
        PS_FREE_MSG(UEPS_PID_MTC, pstOtherModemDplmnNplmnInfoNotify);
        return;
    }

    (VOS_VOID)NV_GetLength(en_NV_Item_Dplmn_Nplmn_Cfg, &ulNvLen);

    if (ulNvLen > sizeof(NAS_MMC_NVIM_DPLMN_NPLMN_CFG_STRU))
    {
        PS_MEM_FREE(UEPS_PID_MTC, pstNvimCfgDPlmnNPlmnInfo);
        PS_FREE_MSG(UEPS_PID_MTC, pstOtherModemDplmnNplmnInfoNotify);
        return;
    }

    /* 读取本modem的nv项 */
    if (NV_OK != NV_ReadEx(enModemId, en_NV_Item_Dplmn_Nplmn_Cfg, &stNvimDPlmnNPlmnCfg, ulNvLen))
    {
        PS_MEM_FREE(UEPS_PID_MTC, pstNvimCfgDPlmnNPlmnInfo);
        PS_FREE_MSG(UEPS_PID_MTC, pstOtherModemDplmnNplmnInfoNotify);
        return;
    }

    pstOtherModemDplmnNplmnInfoNotify->ucEHplmnNum = stNvimDPlmnNPlmnCfg.ucEHplmnNum;
    PS_MEM_CPY(pstOtherModemDplmnNplmnInfoNotify->aucEHplmnList, stNvimDPlmnNPlmnCfg.aucEHplmnList, NAS_MMC_NVIM_MAX_CFG_HPLMN_NUM);
    PS_MEM_SET(pstNvimCfgDPlmnNPlmnInfo, 0x00, sizeof(NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU));

    /* 填充消息 */
    pstOtherModemDplmnNplmnInfoNotify->stMsgHeader.ulReceiverPid   = ulReceivePid;
    pstOtherModemDplmnNplmnInfoNotify->stMsgHeader.ulMsgName       = ID_MTC_MMA_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY;

    /* 读NV项en_NV_Item_Self_Learn_Dplmn_Nplmn_Cfg*/
    if (NV_OK == NV_ReadEx(enModemId, en_NV_Item_Self_Learn_Dplmn_Nplmn_Cfg,
                         pstNvimCfgDPlmnNPlmnInfo, ulNvLen))
    {
        PS_MEM_CPY(&pstOtherModemDplmnNplmnInfoNotify->stSelfLearnDplmnNplmnInfo,
            pstNvimCfgDPlmnNPlmnInfo, sizeof(pstOtherModemDplmnNplmnInfoNotify->stSelfLearnDplmnNplmnInfo));
    }
    /* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-28, end */


    /* 不存在自学习的DPLMN/NPLMN，则不通知Other Modem */
    if (0 == (pstNvimCfgDPlmnNPlmnInfo->usDplmnListNum + pstNvimCfgDPlmnNPlmnInfo->usNplmnListNum))
    {
        PS_MEM_FREE(UEPS_PID_MTC, pstNvimCfgDPlmnNPlmnInfo);
        PS_FREE_MSG(UEPS_PID_MTC, pstOtherModemDplmnNplmnInfoNotify);

        return;
    }

    /* 存在自学习的DPLMN/NPLMN，则通知Other Modem */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTC, pstOtherModemDplmnNplmnInfoNotify))
    {
        MTC_ERROR1_LOG("MTC_SndMmaOtherModemDplmnNplmnInfoNotify: Snd Msg err. Rec Pid ", I0_WUEPS_PID_MMA);
    }

    PS_MEM_FREE(UEPS_PID_MTC, pstNvimCfgDPlmnNPlmnInfo);
    return;

}


/*****************************************************************************
 函 数 名  : MTC_RcvMmaPowerStateInd
 功能描述  : MTC模块接收MMA模块通知的开机状态信息
 输入参数  : MsgBlock* pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月13日
    作    者   : j00174725
    修改内容   : V9R1 干扰控制项目
  2.日    期   : 2013年12月21日
    作    者   : l00198894
    修改内容   : V9R1 Notch Bypass项目
  3.日    期   : 2014年02月13日
    作    者   : f00179208
    修改内容   : Jazz Narrow Band dcs项目
  4.日    期   : 2014年3月24日
    作    者   : A00165503
    修改内容   : B39&B32 Intrusion
  5.日    期   : 2014年9月24日
    作    者   : j00174725
    修改内容   : 打孔新方案
  6.日    期   : 2014年11月3日
    作    者   : z00161729
    修改内容   : 开机漫游搜网项目修改
  7.日    期   : 2015年03月13日
    作    者   : l00198894
    修改内容   : VOLTE Rank1方案项目
  8.日    期   : 2015年05月30日
    作    者   : w00281933
    修改内容   : Modified for The TSTS Project
  9.日    期   : 2015年07月20日
    作    者   : zwx247453
    修改内容   : Modified for 3 modem TAS
 10.日    期   : 2015年12月11日
    作    者   : w00242748
    修改内容   : DTS2015103000174:支持软开关读取平台能力，为适配动态切C模
*****************************************************************************/
VOS_VOID MTC_RcvMmaPowerStateInd(VOS_VOID *pMsg)
{
    VOS_UINT32                          ulPid;
    MODEM_ID_ENUM_UINT16                enModemId;
    MMA_MTC_POWER_STATE_IND_STRU       *pstPowerState = VOS_NULL_PTR;
    /* Modified by l00198894 for V9R1 Notch Bypass项目, 2013-12-21, begin */
    MTC_CFG_ENUM_UINT8                  enIntrusionCfg;
    MTC_CFG_ENUM_UINT8                  enNotchCfg;

    MTC_CFG_ENUM_UINT8                  enNarrowDcsCfg;
    MTC_CFG_ENUM_UINT8                  enTlRfCtrlCfg;
    MTC_MODEM_MIPI_CLK_PRI_STRU         stMomdemPri;
    VOS_UINT16                          usMipiClk;

    MODEM_ID_ENUM_UINT16                enOtherModemId;

    /* Added by Y00213812 for 主动离网重选, 2014-04-10, begin */
    MTC_PS_TRANSFER_CTX_STRU           *pstPsTransferCtx = VOS_NULL_PTR;

    /* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
    MTC_MODEM_POWER_STATE_ENUM_UINT8    enPowerState;
    /* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, End */
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usIndex;

    PLATAFORM_RAT_CAPABILITY_STRU       stModemPlatFormRat;
    MTC_MODEM_INFO_STRU                *pastModemCtxAddr    = VOS_NULL_PTR;

    pstPsTransferCtx = MTC_GetPsTransferCtxAddr();
    /* Added by Y00213812 for 主动离网重选, 2014-04-10, end */

    pstPowerState   = (MMA_MTC_POWER_STATE_IND_STRU *)pMsg;
    ulPid           = pstPowerState->stMsgHeader.ulSenderPid;
    PS_MEM_SET(&stMomdemPri, 0, sizeof(MTC_MODEM_MIPI_CLK_PRI_STRU));

    /* 根据 Pid获取modem ID */
    enModemId       = VOS_GetModemIDFromPid(ulPid);
    if (enModemId >= MODEM_ID_BUTT)
    {
        MTC_ERROR_LOG("MTC_RcvMmaPowerStateInd: Modem ID Err.");
        return ;
    }


    if (MTC_MODEM_POWER_ON == pstPowerState->enPowerState)
    {
        for (usIndex = 0; usIndex < MODEM_ID_BUTT; usIndex++)
        {
            PS_MEM_SET(&stModemPlatFormRat, 0, sizeof(stModemPlatFormRat));

            /* 读取Modem当前接入技术nv项 */
            ulRet = NV_ReadEx(usIndex,
                              en_NV_Item_Platform_RAT_CAP,
                              &stModemPlatFormRat,
                              sizeof(PLATAFORM_RAT_CAPABILITY_STRU));
            if (VOS_OK != ulRet)
            {
                MTC_WARNING_LOG("MTC_RcvMmaPowerStateInd: Read Nv Fail.");
                continue;
            }

            pastModemCtxAddr = MTC_GetModemCtxAddr(usIndex);

            MTC_ParsePlatFormRat(&(pastModemCtxAddr->ucRatCap), &stModemPlatFormRat);
        }

        if (MODEM_ID_2 != enModemId)
        {
            /* 如果是开机消息，给接入层发送启用干扰控制指示 */
            if (PS_TRUE == MTC_GetIntrusionActionEnableFlag())
            {
                MTC_SndIntrusionActionSetReq(enModemId, PS_TRUE);
            }

            (VOS_VOID)MTC_GetOtherModemId(enModemId, &enOtherModemId);
            MTC_SndMmaOtherModemDplmnNplmnInfoNotify(enModemId,enOtherModemId);
        }
    }
    else
    {
        /* 收到关机指示时需要重置Modem信息 */
        MTC_ResetModemInfo(enModemId);

        if (MODEM_ID_2 != enModemId)
        {
            /* 收到关机状态指示，需要将对应modem的重置RfCellInfo，并重新计算bitmap上报给MTA */
            if (MTC_CFG_DISABLE != MTC_GetRfLcdIntrusionCfg())
            {
                MTC_InitRfCellInfo(enModemId);

                /* 根据各modem当前的业务调整优先级 */
                MTC_VerdictModemBitMapPri(&stMomdemPri);

                /* 筛选最佳位图 */
                usMipiClk = MTC_ProcLcdMipiClkBitMap(&stMomdemPri);

                /* 上报LCD MipiClk位图给MTA */
                MTC_SndMtaMipiClkInfoInd(usMipiClk);
            }

            /* Added by Y00213812 for 主动离网重选, 2014-04-10, begin */
            /* 关机时重置PSTRANSFER的上报状态值 */
            if (MODEM_ID_0 == enModemId)
            {
                pstPsTransferCtx->enReportCause     = MTC_PS_TRANSFER_CAUSE_BUTT;
                pstPsTransferCtx->enRrcCause        = MTC_PS_TRANSFER_CAUSE_BUTT;
            }
            /* Added by Y00213812 for 主动离网重选, 2014-04-10, end */
        }
    }

    /* 勾取可维可测信息 */
    MTC_DEBUG_TraceAllModemConnStateInfo();

    enPowerState = MTC_GetModemPowerState(enModemId);

    /* 开关机状态发生变化 */
    if (pstPowerState->enPowerState != enPowerState)
    {
        /* 更新本地开关机状态 */
        MTC_SetModemPowerState(enModemId, pstPowerState->enPowerState);

        /* 报到RCM */
        MTC_SndRcmModemStateInd();
    }

    /*Modem2 暂时不处理干扰控制相关*/
    if (MODEM_ID_2 != enModemId)
    {
        /* 判断干扰控制是否使能 */
        enIntrusionCfg = MTC_GetIntrusionCfg();
        if (MTC_CFG_ENABLE == enIntrusionCfg)
        {
            /* 干扰控制使能，调用对应Modem的开关机状态变化处理函数 */
            MTC_IntrusionModemPowerStateChange(enModemId, pstPowerState->enPowerState);
        }



        /* 判断Notch裁决是否使能 */
        enNotchCfg = MTC_GetNotchCfg();
        if (MTC_CFG_ENABLE == enNotchCfg)
        {
            /* Notch裁决功能使能，执行Notch裁决 */
            MTC_ProcNotchStrategy();
        }
        /* Modified by l00198894 for V9R1 Notch Bypass项目, 2013-12-21, end */

        /* 判断Narrow band dcs裁决是否使能 */
        enNarrowDcsCfg = MTC_GetNarrowBandDcsCfg();
        if (MTC_CFG_ENABLE == enNarrowDcsCfg)
        {
            /* 执行Narrow band dcs裁决 */
            MTC_ProcNarrowDcsStrategy();
        }

        /* 根据开关机状态控制TL射频的上行发射 */
        enTlRfCtrlCfg = MTC_GetTlRfCtrlCfg();
        if (MTC_CFG_ENABLE == enTlRfCtrlCfg)
        {
            MTC_ProcB39B32Intrusion();
        }

        MTC_ProcRseStrategy();
    }

    /* 将当前MTC上下文上报到SDT */
    MTC_DEBUG_TraceCtxInfo();

    if (MODEM_ID_1 == enModemId)
    {
        /* VOLTE Rank1方案: Modem1的开关机状态变化要通知到IMSA */
        MTC_SndImsaModem1InfoInd();
    }

    /* 可维可测记录开关机状态上报次数 */
    MTC_DEBUG_RcvPowerStateInd(enModemId, pstPowerState->enPowerState);

    return;
}

/*****************************************************************************
 函 数 名  : MTC_RcvTafCsSrvInfoInd
 功能描述  : MTC模块处理TAF模块的ID_TAF_MTC_CS_SERVICE_INFO_IND消息函数
 输入参数  : pMsg   --消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月19日
    作    者   : l00198894
    修改内容   : V9R1 干扰控制项目
  2.日    期   : 2014年01月17日
    作    者   : l00198894
    修改内容   : V9R1C53 C+L 离网重选项目
*****************************************************************************/
VOS_VOID MTC_RcvTafCsSrvInfoInd(VOS_VOID *pMsg)
{
    VOS_UINT32                          ulPid;
    MODEM_ID_ENUM_UINT16                enModemId;
    TAF_MTC_CS_SERVICE_INFO_IND_STRU   *pstCsSrvInfo = VOS_NULL_PTR;
    MTC_CS_SERVICE_STATE_ENUM_UINT8     enCsSrvStateOld;
    MTC_CS_SERVICE_STATE_ENUM_UINT8     enCsSrvStateNew;
    MTC_CFG_ENUM_UINT8                  enIntrusionCfg;

    pstCsSrvInfo    = (TAF_MTC_CS_SERVICE_INFO_IND_STRU *)pMsg;
    ulPid           = pstCsSrvInfo->stMsgHeader.ulSenderPid;
    enIntrusionCfg  = MTC_GetIntrusionCfg();

    /* 根据 Pid获取modem ID */
    enModemId       = VOS_GetModemIDFromPid(ulPid);
    if (enModemId >= MODEM_ID_BUTT)
    {
        MTC_ERROR_LOG("MTC_RcvMmaPowerStateInd: Modem ID Err.");
        return;
    }

    /* 先获取原CS域服务状态 */
    enCsSrvStateOld = MTC_GetModemCsSrvExistFlg(enModemId);

    /* 更新modem 信息中CS域业务状态 */
    MTC_SetModemCallSrvExistFlg(enModemId, pstCsSrvInfo->ucCallSrvExistFlg);
    MTC_SetModemSmsSrvExistFlg(enModemId, pstCsSrvInfo->ucSmsSrvExistFlg);
    MTC_SetModemSsSrvExistFlg(enModemId, pstCsSrvInfo->ucSsSrvExistFlg);

    /* 在获取当前CS域服务状态 */
    enCsSrvStateNew = MTC_GetModemCsSrvExistFlg(enModemId);

    /* 可维可测信息记录 */
    MTC_DEBUG_RcvCsSrvInfoInd(enModemId);

    /* 如果Modem1的CS域服务状态发生变化，且干扰控制特性开启，则需要触发干扰控制裁决 */
    if ( (MODEM_ID_1 == enModemId)
      && (enCsSrvStateNew != enCsSrvStateOld)
      && (MTC_CFG_ENABLE == enIntrusionCfg) )
    {
        MTC_ProcIntrusionStrategy();
    }

    return;
}

/*****************************************************************************
 函 数 名  : MTC_SndMmaOtherModemInfoNotify
 功能描述  : 通知Modem0的mma modem1的驻留plmn信息
 输入参数  : enModemId          -- ModemID
             pstCurrCampPlmnId  -- 当前驻留网络plmn id
             pstEplmnInfo        - 等效plmn信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年11月25日
   作    者   : z00161729
   修改内容   : SVLTE优化G-TL ps切换性能修改
 2.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
 3.日    期   : 2014年01月17日
   作    者   : l00198894
   修改内容   : V9R1C53 C+L 离网重选项目
*****************************************************************************/
VOS_VOID MTC_SndMmaOtherModemInfoNotify(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_MMA_PLMN_ID_STRU               *pstCurrCampPlmnId,
    MTC_MMA_EPLMN_INFO_STRU            *pstEplmnInfo
)
{
    VOS_UINT32                                  ulLenth;
    VOS_UINT32                                  ulReceivePid;
    MTC_MMA_OTHER_MODEM_INFO_NOTIFY_STRU       *pstOtherModemInfoNotify = VOS_NULL_PTR;

    ulLenth = sizeof(MTC_MMA_OTHER_MODEM_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;

    if (MODEM_ID_0 == enModemId)
    {
        ulReceivePid = I0_WUEPS_PID_MMA;
    }
    else if (MODEM_ID_1 == enModemId)
    {
        ulReceivePid = I1_WUEPS_PID_MMA;
    }
    else
    {
        MTC_ERROR_LOG("MTC_SndMmaOtherModemInfoNotify: Error Modem Id!");
        return;
    }

    /* 分配消息空间 */
    pstOtherModemInfoNotify = (MTC_MMA_OTHER_MODEM_INFO_NOTIFY_STRU*)PS_ALLOC_MSG(UEPS_PID_MTC, ulLenth);

    if (VOS_NULL_PTR == pstOtherModemInfoNotify)
    {
        MTC_ERROR_LOG("MTC_SndMmaOtherModemInfoNotify: Alloc msg fail!");
        return;
    }

    /* 清消息空间 */
    PS_MEM_SET((VOS_UINT8*)pstOtherModemInfoNotify + VOS_MSG_HEAD_LENGTH, 0, ulLenth);

    /* 填充消息 */
    pstOtherModemInfoNotify->stMsgHeader.ulReceiverPid   = ulReceivePid;
    pstOtherModemInfoNotify->stMsgHeader.ulMsgName       = ID_MTC_MMA_OTHER_MODEM_INFO_NOTIFY;

    if (VOS_NULL_PTR != pstCurrCampPlmnId)
    {
        pstOtherModemInfoNotify->stCurrCampPlmnId.ulMcc = pstCurrCampPlmnId->ulMcc;
        pstOtherModemInfoNotify->stCurrCampPlmnId.ulMnc = pstCurrCampPlmnId->ulMnc;
        pstOtherModemInfoNotify->bitOpCurrCampPlmnId    = VOS_TRUE;
    }

    if (VOS_NULL_PTR != pstEplmnInfo)
    {
        pstOtherModemInfoNotify->bitOpEplmnInfo           = VOS_TRUE;
        pstOtherModemInfoNotify->stEplmnInfo.ucEquPlmnNum = pstEplmnInfo->ucEquPlmnNum;
        PS_MEM_CPY(pstOtherModemInfoNotify->stEplmnInfo.astEquPlmnAddr, pstEplmnInfo->astEquPlmnAddr,
                   sizeof(pstOtherModemInfoNotify->stEplmnInfo.astEquPlmnAddr));
    }

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTC, pstOtherModemInfoNotify))
    {
        MTC_ERROR1_LOG("MTC_SndMmaOtherModemInfoNotify: Snd Msg err. Rec Pid ", I0_WUEPS_PID_MMA);
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : MTC_SndMmaNcellInfoNotify
 功能描述  : 通知Modem0的mma modem1的ncell信息
 输入参数  : pstTddNcellInfo - tds频点列表信息
             pstLteNcellInfo - lte频点列表信息
             ulRecievePid    - 接收pid
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
 2.日    期   : 2014年01月17日
   作    者   : l00198894
   修改内容   : V9R1C53 C+L 离网重选项目
*****************************************************************************/
VOS_VOID MTC_SndMmaNcellInfoInd(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_MMA_TDS_NCELL_INFO_STRU        *pstTddNcellInfo,
    MTC_MMA_LTE_NCELL_INFO_STRU        *pstLteNcellInfo
)
{
    VOS_UINT32                          ulLenth;
    MTC_MMA_NCELL_INFO_IND_STRU        *pstNcellInfoInd = VOS_NULL_PTR;
    VOS_UINT32                          ulReceivePid;

    ulLenth = sizeof(MTC_MMA_NCELL_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    if (MODEM_ID_0 == enModemId)
    {
        ulReceivePid = I0_WUEPS_PID_MMA;
    }
    else if (MODEM_ID_1 == enModemId)
    {
        ulReceivePid = I1_WUEPS_PID_MMA;
    }
    else
    {
        MTC_ERROR_LOG("MTC_SndMmaNcellInfoInd: Error Modem Id!");
        return;
    }

    /* 分配消息空间 */
    pstNcellInfoInd = (MTC_MMA_NCELL_INFO_IND_STRU*)PS_ALLOC_MSG(UEPS_PID_MTC, ulLenth);

    if (VOS_NULL_PTR == pstNcellInfoInd)
    {
        MTC_ERROR_LOG("MTC_SndMmaNcellInfoInd: Alloc msg fail!");
        return;
    }

    /* 清消息空间 */
    PS_MEM_SET((VOS_UINT8*)pstNcellInfoInd + VOS_MSG_HEAD_LENGTH, 0, ulLenth);

    /* 填充消息 */
    pstNcellInfoInd->stMsgHeader.ulReceiverPid   = ulReceivePid;
    pstNcellInfoInd->stMsgHeader.ulMsgName       = ID_MTC_MMA_NCELL_INFO_IND;

    if (VOS_NULL_PTR != pstTddNcellInfo)
    {
        PS_MEM_CPY(&pstNcellInfoInd->stTdsNcellInfo,
                    pstTddNcellInfo,
                    sizeof(pstNcellInfoInd->stTdsNcellInfo));
    }

    if (VOS_NULL_PTR != pstLteNcellInfo)
    {
        PS_MEM_CPY(&pstNcellInfoInd->stLteNcellInfo,
                    pstLteNcellInfo,
                    sizeof(pstNcellInfoInd->stLteNcellInfo));
    }

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTC, pstNcellInfoInd))
    {
        MTC_ERROR_LOG("MTC_SndMmaNcellInfoInd: Snd Msg err.");
        return;
    }

    return;
}


/*****************************************************************************
 函 数 名  : MTC_TransCdmaPlmnId
 功能描述  : 将CDMA发来的PLMN ID转换为MTC_MMA_PLMN_ID_STRU格式
 输入参数  : ulSrcPlmnId
 输出参数  : pstDetPlmnId
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年01月17日
    作    者   : l00198894
    修改内容   : V9R1C53 C+L 离网重选项目
*****************************************************************************/
VOS_VOID MTC_TransCdmaPlmnId(
    VOS_UINT32                          ulSrcPlmnId,
    MTC_MMA_PLMN_ID_STRU               *pstDetPlmnId
)
{
    /* CDMA的PLMN ID格式0x0024005F */
    /* MCC 0x00000402 */
    pstDetPlmnId->ulMcc = 0;
    pstDetPlmnId->ulMcc += (ulSrcPlmnId & 0x00F00000) >> 20;
    pstDetPlmnId->ulMcc += (ulSrcPlmnId & 0x000F0000) >> 8;
    pstDetPlmnId->ulMcc += (ulSrcPlmnId & 0x0000F000) << 4;

    /* MNC 0x000F0500 */
    pstDetPlmnId->ulMnc = 0;
    pstDetPlmnId->ulMnc += (ulSrcPlmnId & 0x00000F00) >> 8;
    pstDetPlmnId->ulMnc += (ulSrcPlmnId & 0x000000F0) << 4;
    pstDetPlmnId->ulMnc += (ulSrcPlmnId & 0x0000000F) << 16;

    return;
}

/*****************************************************************************
 函 数 名  : MTC_IsContainPlmnId
 功能描述  : 判断是否已存在此PLMN ID
 输入参数  : pstPlmnId      -- 待判断PLMN ID
             ulPlmnNum      -- 源PLMN ID个数
             pstSrcPlmnId   -- 源PLMN ID数组
 输出参数  : 无
 返 回 值  : VOS_TRUE   -- 存在
             VOS_FALSE  -- 不存在
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年01月17日
    作    者   : l00198894
    修改内容   : V9R1C53 C+L 离网重选项目
*****************************************************************************/
VOS_UINT32 MTC_IsContainPlmnId(
    MTC_MMA_PLMN_ID_STRU               *pstPlmnId,
    VOS_UINT32                          ulPlmnNum,
    MTC_MMA_PLMN_ID_STRU               *pastSrcPlmnId
)
{
    VOS_UINT32                          ulLoop;

    for (ulLoop = 0; ulLoop < ulPlmnNum; ulLoop++)
    {
        if ( (pstPlmnId->ulMcc == pastSrcPlmnId[ulLoop].ulMcc)
          && (pstPlmnId->ulMnc == pastSrcPlmnId[ulLoop].ulMnc) )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : MTC_GetEplmnFromOtherRatInfoInd
 功能描述  : 从CMMCA_OTHER_RAT_INFO_IND_STRU中获取等效PLMN
 输入参数  : pstOtherRatInfoInd
 输出参数  : pstEplmnInfo
 返 回 值  : VOS_OK     -- 获取成功
             VOS_ERR    -- 获取失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年01月17日
    作    者   : l00198894
    修改内容   : V9R1C53 C+L 离网重选项目
*****************************************************************************/
VOS_UINT32 MTC_GetEplmnFromOtherRatInfoInd(
    MTC_MMA_EPLMN_INFO_STRU            *pstEplmnInfo,
    CMMCA_OTHER_RAT_INFO_IND_STRU      *pstOtherRatInfoInd
)
{
    VOS_UINT16                          usLoop1;
    VOS_UINT8                           ucLoop2;

    if (pstOtherRatInfoInd->usEarfcnListSize > CMMCA_MAX_ARFCN_NUM)
    {
        MTC_ERROR_LOG("MTC_GetEplmnFromOtherRatInfoInd: usEarfcnListSize too big!");
        return VOS_ERR;
    }

    pstEplmnInfo->ucEquPlmnNum = 0;

    for (usLoop1 = 0; usLoop1 < pstOtherRatInfoInd->usEarfcnListSize; usLoop1++)
    {
        if (pstOtherRatInfoInd->astOtherRatInfo[usLoop1].ucNumPlmn > CMMCA_MAX_EUTRA_NEIGHBOR_PLMN_NUM)
        {
            MTC_ERROR2_LOG("MTC_GetEplmnFromOtherRatInfoInd: ucNumPlmn too big! ",
                           usLoop1,
                           pstOtherRatInfoInd->astOtherRatInfo[usLoop1].ucNumPlmn);
            return VOS_ERR;
        }

        for (ucLoop2 = 0; ucLoop2 < pstOtherRatInfoInd->astOtherRatInfo[usLoop1].ucNumPlmn; ucLoop2++)
        {
            MTC_TransCdmaPlmnId(pstOtherRatInfoInd->astOtherRatInfo[usLoop1].aulPlmnId[ucLoop2],
                                &pstEplmnInfo->astEquPlmnAddr[pstEplmnInfo->ucEquPlmnNum]);

            /* 清除重复PLNM ID */
            if (VOS_FALSE == MTC_IsContainPlmnId(&pstEplmnInfo->astEquPlmnAddr[pstEplmnInfo->ucEquPlmnNum],
                                                 pstEplmnInfo->ucEquPlmnNum,
                                                 pstEplmnInfo->astEquPlmnAddr))
            {
                pstEplmnInfo->ucEquPlmnNum++;
            }

            if (pstEplmnInfo->ucEquPlmnNum >= MTC_MMA_MAX_EQUPLMN_NUM)
            {
                return VOS_OK;
            }
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : MTC_GetLteNcellInfoFromOtherRatInfoInd
 功能描述  : 从CMMCA_OTHER_RAT_INFO_IND_STRU中获取LTE频点信息
 输入参数  : pstOtherRatInfoInd
 输出参数  : pstLteNcellInfo
 返 回 值  : VOS_OK     -- 获取成功
             VOS_ERR    -- 获取失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年01月17日
    作    者   : l00198894
    修改内容   : V9R1C53 C+L 离网重选项目
*****************************************************************************/
VOS_UINT32 MTC_GetLteNcellInfoFromOtherRatInfoInd(
    MTC_MMA_LTE_NCELL_INFO_STRU        *pstLteNcellInfo,
    CMMCA_OTHER_RAT_INFO_IND_STRU      *pstOtherRatInfoInd
)
{
    VOS_UINT16                          usLoop;

    if (pstOtherRatInfoInd->usEarfcnListSize > CMMCA_MAX_ARFCN_NUM)
    {
        return VOS_ERR;
    }

    pstLteNcellInfo->ucLteArfcnNum = 0;

    for (usLoop = 0; usLoop < pstOtherRatInfoInd->usEarfcnListSize; usLoop++)
    {
        pstLteNcellInfo->ucLteArfcnNum++;
        pstLteNcellInfo->aulLteArfcnList[usLoop] = pstOtherRatInfoInd->astOtherRatInfo[usLoop].ulEarfcn;
        if (pstLteNcellInfo->ucLteArfcnNum >= MTC_MMA_LTE_ARFCN_MAX_NUM)
        {
            return VOS_OK;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : MTC_RcvCmmcaOtherRatInfoInd
 功能描述  : MTC模块接收CMMCA模块发来的LTE邻区信息
 输入参数  : VOS_VOID* pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年01月17日
    作    者   : l00198894
    修改内容   : V9R1C53 C+L 离网重选项目
*****************************************************************************/
VOS_VOID MTC_RcvCmmcaOtherRatInfoInd(VOS_VOID* pMsg)
{
    /* Added by l60609 for L-C互操作项目, 2014-02-19, Begin */
    CMMCA_MTC_OTHER_RAT_INFO_IND_STRU  *pstOtherRatInfoInd = VOS_NULL_PTR;
    MTC_MMA_EPLMN_INFO_STRU             stEplmnInfo;
    MTC_MMA_LTE_NCELL_INFO_STRU         stLteNcellInfo;

    PS_MEM_SET(&stEplmnInfo, 0, sizeof(MTC_MMA_EPLMN_INFO_STRU));
    PS_MEM_SET(&stLteNcellInfo, 0, sizeof(MTC_MMA_LTE_NCELL_INFO_STRU));

    pstOtherRatInfoInd = (CMMCA_MTC_OTHER_RAT_INFO_IND_STRU *)pMsg;

    /* PS域迁移策略开启时触发流程 */
    if (MTC_PS_TRANSFER_NONE == MTC_GetPsTransferCfg())
    {
        return;
    }

    /* 中国电信C+L定制方案执行后续流程 */
    if (MTC_OPERATOR_CUST_CT_LC != MTC_GetOperatorCustSolution())
    {
        return;
    }

    /* 非LTE接入技术无需处理 */
    if (CMMCA_MMC_RAT_ID_EUTRAN != pstOtherRatInfoInd->stOtherRatInfo.enRatId)
    {
        return;
    }

    /* 通知MMA等效PLMN */
    if (VOS_OK == MTC_GetEplmnFromOtherRatInfoInd(&stEplmnInfo, &(pstOtherRatInfoInd->stOtherRatInfo)))
    {
        MTC_SndMmaOtherModemInfoNotify(MODEM_ID_0, VOS_NULL_PTR, &stEplmnInfo);
    }

    /* 通知MMA LTE频点信息 */
    if (VOS_OK == MTC_GetLteNcellInfoFromOtherRatInfoInd(&stLteNcellInfo, &(pstOtherRatInfoInd->stOtherRatInfo)))
    {
        MTC_SndMmaNcellInfoInd(MODEM_ID_0, VOS_NULL_PTR, &stLteNcellInfo);
    }
    /* Added by l60609 for L-C互操作项目, 2014-02-19, End */

    return;
}

/* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
/*****************************************************************************
 函 数 名  : MTC_ProcSetCdmaConnStateInfo
 功能描述  : 处理外部cdma modem状态消息
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月16日
    作    者   : j00174725
    修改内容   : 新生成函数
  2.日    期   : 2015年7月20日
    作    者   : zwx247453
    修改内容   : 3 modem TAS
*****************************************************************************/
VOS_VOID MTC_ProcSetCdmaExtModemConnStateInfo(VOS_VOID* pMsg)
{
    TAF_PS_MSG_STRU                    *pstMsg         = VOS_NULL_PTR;
    TAF_MTC_CDMA_STATE_IND_STRU        *pstCmdStateInd = VOS_NULL_PTR;
    TAF_MTC_CDMA_STATE_INFO_STRU       *pstCdmaState   = VOS_NULL_PTR;
    VOS_UINT32                          ulSndMsgFlag;

    ulSndMsgFlag    = VOS_FALSE;
    pstMsg          = (TAF_PS_MSG_STRU *)pMsg;
    pstCmdStateInd  = (TAF_MTC_CDMA_STATE_IND_STRU *)pstMsg->aucContent;
    pstCdmaState    = (TAF_MTC_CDMA_STATE_INFO_STRU *)&pstCmdStateInd->stCdmaState;

    /* 勾取可维可测信息 */
    MTC_DEBUG_TraceAllModemConnStateInfo();

    /* 保存外部cdma modem状态消息 */
    /* 判断CS状态是否变化 */
    if (pstCdmaState->enCsConnSt != MTC_GetOutSideCsConnStateInfo(MTC_OUTSIDE_MODEM_CDMA))
    {
        ulSndMsgFlag = VOS_TRUE;
        MTC_SetOutSideCsConnStateInfo(MTC_OUTSIDE_MODEM_CDMA, pstCdmaState->enCsConnSt);
    }

    /* 判断PS状态是否变化 */
    if (pstCdmaState->enPsConnSt != MTC_GetOutSidePsConnStateInfo(MTC_OUTSIDE_MODEM_CDMA))
    {
        ulSndMsgFlag = VOS_TRUE;
        MTC_SetOutSidePsConnStateInfo(MTC_OUTSIDE_MODEM_CDMA, pstCdmaState->enPsConnSt);
    }

    /* 判断开关机状态是否变化 */
    if (pstCdmaState->enPowerState != MTC_GetOutSideModemPowerState(MTC_OUTSIDE_MODEM_CDMA))
    {
        ulSndMsgFlag = VOS_TRUE;
        MTC_SetOutSideModemPowerState(MTC_OUTSIDE_MODEM_CDMA, pstCdmaState->enPowerState);
    }

    /* 判断卡状态是否变化 */
    if (pstCdmaState->enUsimmState != MTC_GetOutSideModemUsimmState(MTC_OUTSIDE_MODEM_CDMA))
    {
        ulSndMsgFlag = VOS_TRUE;
        MTC_SetOutSideModemUsimmState(MTC_OUTSIDE_MODEM_CDMA, pstCdmaState->enUsimmState);
    }

    /* 状态是否有变化，变化就发送消息通知RCM */
    if (VOS_TRUE == ulSndMsgFlag)
    {
        /* 发送消息通知RCM */
        MTC_SndRcmModemStateInd();
    }

    return;
}

/*****************************************************************************
 函 数 名  : MTC_ProcModemServiceConnStateInd
 功能描述  : 处理modem 服务状态信息
 输入参数  : MsgBlock* pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月16日
    作    者   : j00174725
    修改内容   : K3V3 多模多天线特性
  2.日    期   : 2014年09月24日
    作    者   : j00174725
    修改内容   : 打孔新方案
 3 .日    期   : 2014年09月24日
    作    者   : j00174725
    修改内容   : DTS2015012600981
  4.日    期   : 2015年07月20日
    作    者   : zwx247453
    修改内容   : 3 modem TAS
*****************************************************************************/
VOS_VOID MTC_ProcModemServiceConnStateInd(VOS_VOID *pMsg)
{
    TAF_PS_MSG_STRU                    *pstMsg              = VOS_NULL_PTR;
    TAF_MTC_MODEM_CONN_STATUS_IND_STRU *pstModemStateInd    = VOS_NULL_PTR;
    TAF_MTC_SRV_CONN_STATE_INFO_STRU   *pstModemState       = VOS_NULL_PTR;
    VOS_UINT32                          ulSndMsgFlag;
    VOS_UINT32                          ulPid;
    MODEM_ID_ENUM_UINT16                enModemId;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enOldsConnState;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enCurrsConnState;
    MTC_CFG_ENUM_UINT8                  enTlRfCtrlCfg;

    /* 勾取可维可测信息 */
    MTC_DEBUG_TraceAllModemConnStateInfo();

    ulSndMsgFlag        = VOS_FALSE;
    pstMsg              = (TAF_PS_MSG_STRU *)pMsg;
    pstModemStateInd    = (TAF_MTC_MODEM_CONN_STATUS_IND_STRU *)pstMsg->aucContent;
    pstModemState       = (TAF_MTC_SRV_CONN_STATE_INFO_STRU *)&pstModemStateInd->stModemConnStateInfo;
    ulPid               = pstModemStateInd->stCtrl.ulModuleId;
    enOldsConnState     = TAF_MTC_SRV_NO_EXIST;
    enCurrsConnState    = TAF_MTC_SRV_NO_EXIST;

    /* 根据 Pid获取modem ID */
    enModemId           = VOS_GetModemIDFromPid(ulPid);
    if (enModemId >= MODEM_ID_BUTT)
    {
        MTC_ERROR_LOG("MTC_ProcModemServiceConnStateInd: Modem ID Err.");
        return ;
    }

    /* 更新上下文件 */
    /* CS状态 */
    if (VOS_TRUE == pstModemState->bitOpCsSrv)
    {
        if (PS_TRUE == MTC_IsNeedSndTasCsInfo2Rcm(enModemId, pstModemState->enCsSrvConnState, MTC_CS_TYPE_GU))
        {
            ulSndMsgFlag        = VOS_TRUE;
        }

        /* 置标记 */
        MTC_SetCsTypeInfo(enModemId, MTC_CS_TYPE_GU, pstModemState->enCsSrvConnState);
    }

    /* PS状态 */
    enOldsConnState = MTC_GetPsSrvState(enModemId);
    if (VOS_TRUE == pstModemState->bitOpPsSrv)
    {
        if (MTC_RATMODE_GSM != MTC_GetModemRatMode(enModemId))
        {
            MTC_SetPsTypeInfo(enModemId, MTC_PS_TYPE_GU, pstModemState->enPsSrvConnState);
        }
        /* GSM要求一直上报PS不存在 */
        else
        {
            MTC_SetPsTypeInfo(enModemId, MTC_PS_TYPE_GU, TAF_MTC_SRV_NO_EXIST);
        }
    }

    /* EPS状态 */
    if (VOS_TRUE == pstModemState->bitOpEpsSrv)
    {
        MTC_SetPsTypeInfo(enModemId, MTC_PS_TYPE_LTE, pstModemState->enEpsSrvConnState);
    }

    enCurrsConnState = MTC_GetPsSrvState(enModemId);
    if (enCurrsConnState != enOldsConnState)
    {
        ulSndMsgFlag = VOS_TRUE;
    }

    /* 状态是否有变化，变化就发送消息通知RCM */
    if (VOS_TRUE == ulSndMsgFlag)
    {
        /* 发送消息通知RCM */
        MTC_SndRcmModemStateInd();
    }

    /* 打孔方案 */
    enTlRfCtrlCfg = MTC_GetTlRfCtrlCfg();
    if ((MTC_CFG_ENABLE == enTlRfCtrlCfg)
        && (MODEM_ID_2 != enModemId))
    {
        MTC_ProcB39B32Intrusion();
    }
    return;
}

/*****************************************************************************
 函 数 名  : MTC_ProcUsimmStateInd
 功能描述  : 处理卡状态信息
 输入参数  : MsgBlock* pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月16日
    作    者   : j00174725
    修改内容   : K3V3 多模多天线特性

  2.日    期   : 2015年10月21日
    作    者   : h00313353
    修改内容   : Iteration 19 TAS
*****************************************************************************/
VOS_VOID MTC_ProcUsimmStateInd(VOS_VOID *pMsg)
{
    TAF_PS_MSG_STRU                        *pstMsg              = VOS_NULL_PTR;
    TAF_MTC_USIMM_STATUS_IND_STRU          *pstUsimmStateInd    = VOS_NULL_PTR;
    VOS_UINT32                              ulPid;
    MODEM_ID_ENUM_UINT16                    enModemId;
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16   enUsimState;
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16   enCsimState;
    MTC_RCM_MODEM_RAT_CFG_ENUM_UINT16       enRatModeCfg;

    enUsimState                             = TAF_MTC_USIMM_CARD_SERVIC_ABSENT;
    enCsimState                             = TAF_MTC_USIMM_CARD_SERVIC_ABSENT;
    enRatModeCfg                            = MTC_RCM_MODEM_RAT_CFG_BUTT;

    /* 勾取可维可测信息 */
    MTC_DEBUG_TraceAllModemConnStateInfo();

    pstMsg              = (TAF_PS_MSG_STRU *)pMsg;
    pstUsimmStateInd    = (TAF_MTC_USIMM_STATUS_IND_STRU *)pstMsg->aucContent;
    ulPid               = pstUsimmStateInd->stCtrl.ulModuleId;

    /* 根据 Pid获取modem ID */
    enModemId           = VOS_GetModemIDFromPid(ulPid);
    if (enModemId >= MODEM_ID_BUTT)
    {
        MTC_ERROR_LOG("MTC_ProcUsimmStateInd: Modem Id Err.");
        return ;
    }

    enUsimState         = MTC_GetUsimStateInfo(enModemId);
    enCsimState         = MTC_GetCsimStateInfo(enModemId);

    /* 刷新卡状态 */
    MTC_SetUsimStateInfo(enModemId, pstUsimmStateInd->enUsimState);
    MTC_SetCsimStateInfo(enModemId, pstUsimmStateInd->enCsimState);

    enRatModeCfg        = MTC_ConvertToRcmRatCfg(pstUsimmStateInd->enUsimState, MTC_GetRatCfgByModemId(enModemId));

    /* 未收到RatCfg消息，不发送消息 */
    if (MTC_RCM_MODEM_RAT_CFG_BUTT == enRatModeCfg)
    {
        return;
    }

    /* 判断卡状态是否变化 */
    if ((MTC_RCM_MODEM_RAT_CFG_CL == enRatModeCfg)
     || (MTC_RCM_MODEM_RAT_CFG_C  == enRatModeCfg))
    {
        /* 非GUL模式，Csim卡状态未改变不发送 */
        if (enCsimState == pstUsimmStateInd->enCsimState)
        {
            return;
        }
    }
    else
    {
        /* GUL模式，Usim卡状态未改变不发送 */
        if (enUsimState == pstUsimmStateInd->enUsimState)
        {
            return;
        }
    }

    /* 发送消息通知RCM */
    MTC_SndRcmModemStateInd();

    return;
}

/*****************************************************************************
 函 数 名  : MTC_RcvTcStatusInfo
 功能描述  : MTC模块通知RCM模块TC环回测试状态
 输入参数  : MsgBlock* pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月6日
    作    者   : wx270776
    修改内容   : 生成新函数
  2.日    期   : 2015年7月20日
    作    者   : zwx247453
    修改内容   : 3 modem TAS
*****************************************************************************/
VOS_VOID MTC_RcvTcStatusInfo(
    VOS_VOID                           *pMsg
)
{
    MTC_RCM_TC_STATUS_NOTIFY_STRU      *pstTcStatus  = VOS_NULL_PTR;
    NAS_MTC_TC_STATUS_INFO_IND_STRU    *pstNasMtcMsg = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                enModemId;
    MTC_NAS_TC_STATUS_ENUM_UINT16       enCurTcStat;

    pstNasMtcMsg                      = (NAS_MTC_TC_STATUS_INFO_IND_STRU*)pMsg;
    enModemId                         = VOS_GetModemIDFromPid(pstNasMtcMsg->ulSenderPid);

    if ( enModemId >= MODEM_ID_BUTT )
    {
        MTC_ERROR_LOG("MTC_RcvTcStatusInfo: Modem ID Error!");
        return ;
    }

    enCurTcStat                       = (MTC_NAS_TC_STATUS_ENUM_UINT16)MTC_GetCurrentTcStatus(enModemId);

    /* 如果收到重复的环回状态则直接返回 */
    if( enCurTcStat == pstNasMtcMsg->enTcStatus )
    {
        return;
    }

    /* 申请消息包 */
    pstTcStatus = (MTC_RCM_TC_STATUS_NOTIFY_STRU *)MTC_ALLOC_MSG_WITH_HDR(sizeof(MTC_RCM_TC_STATUS_NOTIFY_STRU));
    if (VOS_NULL_PTR == pstTcStatus)
    {
        MTC_ERROR_LOG("MTC_RcvTcStatusInfo: Alloc Msg Fail!");
        return;
    }

    /* 清空消息内容 */
    PS_MEM_SET( MTC_GET_MSG_ENTITY(pstTcStatus), 0, MTC_GET_MSG_LENGTH(pstTcStatus) );

    /* 填充消息头 */
    MTC_CFG_RCM_MSG_HDR(&pstTcStatus->stMsgHeader, ID_MTC_RCM_TC_STATUS_NOTIFY);

    /* 填充消息内容 */
    pstTcStatus->enModemId            = enModemId;
    pstTcStatus->enRatMode            = MTC_ConvertRcmRatMode(pstNasMtcMsg->enRatMode);
    pstTcStatus->enTcStatus           = pstNasMtcMsg->enTcStatus;

    /* 在全局变量中记录环回状态 */
    MTC_SetCurrentTcStatus(enModemId, pstTcStatus->enTcStatus);

    /* 发送消息 */
    MTC_SEND_MSG(pstTcStatus);

    return;
}


/*****************************************************************************
 函 数 名  : MTC_ConvertRcmRatMode
 功能描述  : 将NAS给MTC的接入技术转换为MTC给RCM的形式
 输入参数  : MTC_NAS_RAT_MODE_ENUM_UINT16   enMtcNasRatMode
 输出参数  : 无
 返 回 值  : MTC_RCM_RAT_MODE_ENUM_UINT16   enMtcRcmRatMode
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月22日
    作    者   : wx270776
    修改内容   : 新生成函数
*****************************************************************************/
MTC_RCM_RAT_MODE_ENUM_UINT16 MTC_ConvertRcmRatMode(
    MTC_NAS_RAT_MODE_ENUM_UINT16        enMtcNasRatMode
)
{
    MTC_RCM_RAT_MODE_ENUM_UINT16        enMtcRcmRatMode;

    switch(enMtcNasRatMode)
    {
    case MTC_NAS_RAT_MODE_GSM:
        enMtcRcmRatMode = MTC_RCM_RAT_MODE_GSM;
        break;

    case MTC_NAS_RAT_MODE_WCDMA:
        enMtcRcmRatMode = MTC_RCM_RAT_MODE_WCDMA;
        break;

    case MTC_NAS_RAT_MODE_TDSCDMA:
        enMtcRcmRatMode = MTC_RCM_RAT_MODE_TDSCDMA;
        break;

    case MTC_NAS_RAT_MODE_LTE:
        enMtcRcmRatMode = MTC_RCM_RAT_MODE_LTE;
        break;

    case MTC_NAS_RAT_MODE_CDMA:
        enMtcRcmRatMode = MTC_RCM_RAT_MODE_CDMA;
        break;

    default:
        enMtcRcmRatMode = MTC_RCM_RAT_MODE_BUTT;
        break;
    }

    return enMtcRcmRatMode;
}


/*****************************************************************************
 函 数 名  : MTC_ConvertToRcmRatCfg
 功能描述  : 将MTC存储的RatCfg转换成RCM的形式
 输入参数  : TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16    enUsimState--Usim卡状态
             MTC_MODEM_RAT_CONFIG_STRU               *pstRatCfg  --配置信息
 输出参数  : 无
 返 回 值  : MTC_RCM_MODEM_RAT_CFG_ENUM_UINT16
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : h00313353
    修改内容   : Iteration 19 TAS
*****************************************************************************/
MTC_RCM_MODEM_RAT_CFG_ENUM_UINT16 MTC_ConvertToRcmRatCfg(
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16    enUsimmState,
    MTC_MODEM_RAT_CONFIG_STRU               *pstRatCfg
)
{
    /* 卡状态上报信息未获取到，不进行判断 */
    if (TAF_MTC_USIMM_CARD_SERVIC_BUTT  == enUsimmState)
    {
        return MTC_RCM_MODEM_RAT_CFG_BUTT;
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if ((VOS_TRUE == pstRatCfg->ucIs1xExist)
     || (VOS_TRUE == pstRatCfg->ucIsHrpdExist))
    {
        if (VOS_FALSE == pstRatCfg->ucIsLteExist)
        {
            return MTC_RCM_MODEM_RAT_CFG_C;
        }

        if (TAF_MTC_USIMM_CARD_SERVIC_ABSENT == enUsimmState)
        {
            return MTC_RCM_MODEM_RAT_CFG_C;
        }

        return MTC_RCM_MODEM_RAT_CFG_CL;
    }
#endif

    if ((VOS_TRUE == pstRatCfg->ucIsLteExist)
     || (VOS_TRUE == pstRatCfg->ucIsGuExist))
    {
        return MTC_RCM_MODEM_RAT_CFG_GUL;
    }

    return MTC_RCM_MODEM_RAT_CFG_BUTT;
}

#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 函 数 名  : MTC_ProcImsaSrvConnStateInfo
 功能描述  : 处理IMSA状态消息
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月16日
    作    者   : j00174725
    修改内容   : 新生成函数
  2.日    期   : 2015年7月20日
    作    者   : zwx247453
    修改内容   : 3 modem TAS
  3.日    期   : 2015年9月18日
    作    者   : j00174725
    修改内容   :  DTS2015091108014
*****************************************************************************/
VOS_VOID MTC_ProcImsaSrvConnStateInfo(VOS_VOID* pMsg)
{

    IMSA_MTC_SRV_CONN_STATUS_NOTIFY_STRU   *pstImsaStatus;
    VOS_UINT32                              ulSndRcmFlag;
    MODEM_ID_ENUM_UINT16                    enModemId;
    MTC_CFG_ENUM_UINT8                      enTlRfCtrlCfg;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8       enCsSrvConnState;

    ulSndRcmFlag    = VOS_FALSE;
    pstImsaStatus   = (IMSA_MTC_SRV_CONN_STATUS_NOTIFY_STRU *)pMsg;
    enModemId       = VOS_GetModemIDFromPid(pstImsaStatus->ulSenderPid);

    if (enModemId >= MODEM_ID_BUTT)
    {
        MTC_ERROR_LOG("MTC_ProcImsaSrvConnStateInfo: Modem ID Error!");
        return ;
    }

    if ( IMSA_SRV_CONN_STATUS_IS_EXIST == pstImsaStatus->enIsImsSrvExist)
    {
        enCsSrvConnState = TAF_MTC_SRV_EXIST;
    }
    else
    {
        enCsSrvConnState = TAF_MTC_SRV_NO_EXIST;
    }

    if (PS_TRUE == MTC_IsNeedSndTasCsInfo2Rcm(enModemId, enCsSrvConnState, MTC_CS_TYPE_IMS))
    {
        ulSndRcmFlag    = VOS_TRUE;
    }

    /* 设置IMS标记 */
    MTC_SetCsTypeInfo(enModemId, MTC_CS_TYPE_IMS, enCsSrvConnState);

    if (VOS_TRUE == ulSndRcmFlag)
    {
        /* 发送消息通知RCM */
        MTC_SndRcmModemStateInd();
    }

    /* 打孔方案 */
    enTlRfCtrlCfg = MTC_GetTlRfCtrlCfg();
    if ((MTC_CFG_ENABLE == enTlRfCtrlCfg)
        && (MODEM_ID_2 != enModemId))
    {
        MTC_ProcB39B32Intrusion();
    }

    return;

}
#endif
/* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, End */

/*****************************************************************************
 函 数 名  : MTC_RcvGsmCellInfoExInd
 功能描述  : 接收到ID_MTC_RRC_GSM_CELL_INFO_EX_IND将GSM小区扩展信息保存到上下文
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月17日
    作    者   : l00198894
    修改内容   : 新增函数
*****************************************************************************/
VOS_VOID MTC_RcvGsmCellInfoExInd(VOS_VOID *pMsg)
{
    RRC_MTC_GSM_CELL_INFO_EX_IND_STRU  *pstGsmCellInfoExInd = VOS_NULL_PTR;
    MTC_GSM_CELLINFO_EX_STRU           *pstGsmCellInfoEx    = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulPid;

    pstGsmCellInfoExInd = (RRC_MTC_GSM_CELL_INFO_EX_IND_STRU *)pMsg;
    ulPid               = pstGsmCellInfoExInd->stMsgHeader.ulSenderPid;

    /* 根据 Pid获取modem ID */
    enModemId       = VOS_GetModemIDFromPid(ulPid);
    if (enModemId >= MODEM_ID_BUTT)
    {
        MTC_ERROR_LOG("MTC_RcvGsmCellInfoExInd: Modem ID Err.");
        return ;
    }

    pstGsmCellInfoEx = MTC_GetModemGsmCellInfoEx(enModemId);
    pstGsmCellInfoEx->ulValidFlg        = VOS_TRUE;
    pstGsmCellInfoEx->stPlmnId.ulMcc    = pstGsmCellInfoExInd->stGsmCellInfoEx.stPlmnId.ulMcc;
    pstGsmCellInfoEx->stPlmnId.ulMnc    = pstGsmCellInfoExInd->stGsmCellInfoEx.stPlmnId.ulMnc;
    pstGsmCellInfoEx->usLac             = pstGsmCellInfoExInd->stGsmCellInfoEx.usLac;
    pstGsmCellInfoEx->usCellId          = pstGsmCellInfoExInd->stGsmCellInfoEx.usCellId;

    return;
}

/*****************************************************************************
 函 数 名  : MTC_RcvMtaGsmCellInfoQryReq
 功能描述  : 接收到ID_MTC_RRC_GSM_CELL_INFO_EX_IND将GSM小区扩展信息保存到上下文
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月17日
    作    者   : l00198894
    修改内容   : 新增函数
*****************************************************************************/
VOS_VOID MTC_RcvMtaGsmCellInfoQryReq(VOS_VOID *pMsg)
{
    MTA_MTC_RESERVE_STRU               *pstReqMsg           = VOS_NULL_PTR;
    VOS_UINT32                          ulLenth;
    MTC_MTA_GSM_CELLINFO_QRY_CNF_STRU  *pstCnfMsg           = VOS_NULL_PTR;
    MTC_GSM_CELLINFO_EX_STRU           *pstGsmCellInfoEx    = VOS_NULL_PTR;

    pstReqMsg = (MTA_MTC_RESERVE_STRU *)pMsg;

    /* 仅处理Modem0 MTA模块的查询请求 */
    if (UEPS_PID_MTA != pstReqMsg->stMsgHeader.ulSenderPid)
    {
        return;
    }

    ulLenth = sizeof(MTC_MTA_GSM_CELLINFO_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 分配消息空间 */
    pstCnfMsg = (MTC_MTA_GSM_CELLINFO_QRY_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MTC, ulLenth);

    if (VOS_NULL_PTR == pstCnfMsg)
    {
        MTC_ERROR_LOG("MTC_RcvMtaGsmCellInfoQryReq: Alloc msg fail!");
        return;
    }

    /* 清消息空间 */
    PS_MEM_SET((VOS_UINT8*)pstCnfMsg + VOS_MSG_HEAD_LENGTH, 0, ulLenth);

    /* 填充消息 */
    pstCnfMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_MTA;
    pstCnfMsg->stMsgHeader.ulMsgName        = ID_MTC_MTA_GSM_CELLINFO_QRY_CNF;

    pstGsmCellInfoEx = MTC_GetModemGsmCellInfoEx(MODEM_ID_1);

    pstCnfMsg->enResult                     = MTA_MTC_RESULT_NO_ERROR;
    pstCnfMsg->stCellInfoEx.ulValidFlg      = pstGsmCellInfoEx->ulValidFlg;
    pstCnfMsg->stCellInfoEx.stPlmnId        = pstGsmCellInfoEx->stPlmnId;
    pstCnfMsg->stCellInfoEx.usLac           = pstGsmCellInfoEx->usLac;
    pstCnfMsg->stCellInfoEx.usCellId        = pstGsmCellInfoEx->usCellId;

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTC, pstCnfMsg))
    {
        MTC_ERROR_LOG("MTC_RcvMtaGsmCellInfoQryReq: Snd Msg err.");
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : MTC_RcvMmaImsaStateInd
 功能描述  : MTC模块接收MMA模块通知的IMSA开机状态信息
 输入参数  : MsgBlock* pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月13日
    作    者   : l00198894
    修改内容   : VOLTE Rank1方案项目
*****************************************************************************/
VOS_VOID MTC_RcvMmaImsaStateInd(VOS_VOID *pMsg)
{
    VOS_UINT32                          ulPid;
    MMA_MTC_IMSA_STATE_IND_STRU        *pstImsaStateInd = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                enModemId;

    pstImsaStateInd = (MMA_MTC_IMSA_STATE_IND_STRU *)pMsg;
    ulPid           = pstImsaStateInd->stMsgHeader.ulSenderPid;

    /* 根据 Pid获取modem ID */
    enModemId       = VOS_GetModemIDFromPid(ulPid);
    if (enModemId >= MODEM_ID_BUTT)
    {
        MTC_ERROR_LOG("MTC_RcvMmaPowerStateInd: Modem ID Err.");
        return ;
    }

    /* 更新IMSA开关机状态 */
    MTC_SetModemImsaState(enModemId, pstImsaStateInd->enPowerState);

    if (MTC_MODEM_POWER_ON == pstImsaStateInd->enPowerState)
    {
        /* 如果是开机消息，需要将另一个Modem的开机状态通知到IMSA */
        MTC_SndImsaModem1InfoInd();
    }

    return;
}

/*****************************************************************************
 函 数 名  : MTC_RcvMmaImsVoiceCapInd
 功能描述  : MTC模块接收MMA模块通知的IMS语音可用状态信息
 输入参数  : MsgBlock* pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月17日
    作    者   : w00316404
    修改内容   : 新增函数
*****************************************************************************/
VOS_VOID MTC_RcvMmaImsVoiceCapInd(VOS_VOID *pMsg)
{
    MMA_MTC_IMS_VOICE_CAP_IND_STRU     *pstImsVoiceCap  = VOS_NULL_PTR;
    VOS_UINT32                          ulPid;
    MODEM_ID_ENUM_UINT16                enModemId;
    MTC_MODEM_IMS_VOICE_CAP_ENUM_UINT8  enImsVoiceCap;

    pstImsVoiceCap  = (MMA_MTC_IMS_VOICE_CAP_IND_STRU *)pMsg;
    ulPid           = pstImsVoiceCap->stMsgHeader.ulSenderPid;

    /* 根据Pid获取modem ID */
    enModemId   = VOS_GetModemIDFromPid(ulPid);
    if (MODEM_ID_0 != enModemId)
    {
        MTC_ERROR_LOG("MTC_RcvMmaImsVoiceCapInd: Modem ID is not MODEM_ID_0.");
        return ;
    }

    /* 获取当前IMS语音可用状态 */
    enImsVoiceCap = MTC_GetModemImsVoiceCap(enModemId);

    /* IMS语音可用状态发生变化时，更新IMS语音可用状态并发送到RCM */
    if (pstImsVoiceCap->enImsVoiceCap != enImsVoiceCap)
    {
        /* 更新IMS语音可用状态 */
        MTC_SetModemImsVoiceCap(enModemId, pstImsVoiceCap->enImsVoiceCap);

        MTC_SndRcmModemImsVoiceCapInd();
    }

    return;
}

/*****************************************************************************
 函 数 名  : MTC_RcvMmaRatCfgInd
 功能描述  : MTC模块接收MMA模块Rat Cfg Ind消息的处理
 输入参数  : MsgBlock* pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : h00313353
    修改内容   : Iteration 19 TAS
*****************************************************************************/
VOS_VOID MTC_RcvMmaRatCfgInd(
    VOS_VOID                           *pMsg
)
{
    MMA_MTC_RAT_CFG_IND_STRU                               *pstRatCfgInd    = VOS_NULL_PTR;
    MTC_MODEM_RAT_CONFIG_STRU                              *pstLastRatCfg   = VOS_NULL_PTR;
    MTC_MODEM_RAT_CONFIG_STRU                               stRatConfig;
    MODEM_ID_ENUM_UINT16                                    enModemId;
    MTC_RCM_MODEM_RAT_CFG_ENUM_UINT16                       enLastRatCfg;
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16                   enUsimState;
    VOS_UINT32                                              i;

    pstRatCfgInd    = (MMA_MTC_RAT_CFG_IND_STRU *)pMsg;
    PS_MEM_SET(&stRatConfig, 0x00, sizeof(MTC_MODEM_RAT_CONFIG_STRU));
    enLastRatCfg    = MTC_RCM_MODEM_RAT_CFG_BUTT;
    i               = 0;
    enUsimState     = TAF_MTC_USIMM_CARD_SERVIC_BUTT;

    /* 根据Pid获取modem ID */
    enModemId       = VOS_GetModemIDFromPid(pstRatCfgInd->stMsgHeader.ulSenderPid);
    if (enModemId >= MODEM_ID_BUTT)
    {
        MTC_ERROR_LOG("MTC_RcvMmaRatCfgInd: Modem ID Err.");
        return ;
    }

    pstLastRatCfg   = MTC_GetRatCfgByModemId(enModemId);
    enUsimState     = MTC_GetUsimStateInfo(enModemId);

    for (i = 0; i < pstRatCfgInd->ucRatOrderNum; i++)
    {
        if (MTC_RATMODE_LTE == pstRatCfgInd->aenRatOrder[i])
        {
            stRatConfig.ucIsLteExist        = VOS_TRUE;

            continue;
        }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if (MTC_RATMODE_1X  == pstRatCfgInd->aenRatOrder[i])
        {
            stRatConfig.ucIs1xExist         = VOS_TRUE;

            MTC_GetCtxAddr()->enCdmaModemId = enModemId;

            continue;
        }

        if (MTC_RATMODE_HRPD == pstRatCfgInd->aenRatOrder[i])
        {
            stRatConfig.ucIsHrpdExist       = VOS_TRUE;

            MTC_GetCtxAddr()->enCdmaModemId = enModemId;

            continue;
        }
#endif

        if (pstRatCfgInd->aenRatOrder[i] <= MTC_RATMODE_TDS)
        {
            stRatConfig.ucIsGuExist         = VOS_TRUE;
        }
    }

    enLastRatCfg = MTC_ConvertToRcmRatCfg(enUsimState, pstLastRatCfg);

    MTC_SetRatCfgByModemId(enModemId, &stRatConfig);

    /* 卡未初始化，暂不报告给RCM */
    if ((TAF_MTC_USIMM_CARD_SERVIC_BUTT == MTC_GetCsimStateInfo(enModemId))
     && (TAF_MTC_USIMM_CARD_SERVIC_BUTT == enUsimState))
    {
        return;
    }

    /* 能力发生改变,通知RCM */
    if (enLastRatCfg != MTC_ConvertToRcmRatCfg(enUsimState, &stRatConfig))
    {
        MTC_SndRcmModemStateInd();

        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : MTC_ProcBeginSessionInd
 功能描述  : 处理BEGIN SESSION 消息
 输入参数  : MsgBlock* pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月04日
    作    者   : j00174725
    修改内容   : DTS2015082406288
  2.日    期   : 2015年9月18日
    作    者   : j00174725
    修改内容   :  DTS2015091108014
  3.日    期   : 2015年10月22日
    作    者   : h00313353
    修改内容   : Iteration 19 TAS
*****************************************************************************/
VOS_VOID MTC_ProcBeginSessionInd(VOS_VOID *pMsg)
{
    TAF_PS_MSG_STRU                    *pstMsg              = VOS_NULL_PTR;
    MTC_BEGIN_SESSION_IND_STRU         *pstBeginSessionInd  = VOS_NULL_PTR;
    VOS_UINT32                          ulPid;
    MODEM_ID_ENUM_UINT16                enModemId;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enCsSrvStatus;
    MTC_SESSION_TYPE_ENUM_UINT8         enSessionType;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    MTC_RCM_MODEM_RAT_CFG_ENUM_UINT16   enRatCfg;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enPsSrvStatus;

    enRatCfg                            = MTC_RCM_MODEM_RAT_CFG_BUTT;
    enPsSrvStatus                       = TAF_MTC_SRV_CONN_STATE_BUTT;
#endif

    /* 勾取可维可测信息 */
    MTC_DEBUG_TraceAllModemConnStateInfo();

    pstMsg              = (TAF_PS_MSG_STRU *)pMsg;
    pstBeginSessionInd  = (MTC_BEGIN_SESSION_IND_STRU *)pstMsg->aucContent;
    ulPid               = pstBeginSessionInd->stCtrl.ulModuleId;

    /* 根据 Pid获取modem ID */
    enModemId       = VOS_GetModemIDFromPid(ulPid);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (UEPS_PID_XCC == ulPid)
    {
        enModemId       = MTC_GetCtxAddr()->enCdmaModemId;

        if (enModemId < MODEM_ID_BUTT)
        {
            enRatCfg        = MTC_ConvertToRcmRatCfg(MTC_GetUsimStateInfo(enModemId),
                                                     MTC_GetRatCfgByModemId(enModemId));

            enPsSrvStatus   = MTC_GetPsSrvState(enModemId);
        }
    }
#endif

    if (enModemId >= MODEM_ID_BUTT)
    {
        MTC_ERROR_LOG("MTC_ProcBeginSessionInd: Modem Id Err.");
        return;
    }

    enSessionType       = pstBeginSessionInd->enSessionType;

    /* 异常Session排除 */
    if ((MTC_SESSION_TYPE_CS_BUTT   == enSessionType)
     || (MTC_SESSION_TYPE_BUTT      <= enSessionType))
    {
        return;
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (MTC_SESSION_TYPE_CS_LOOP_BACK == enSessionType)
    {
        /* 环回模式START，发送给RCM */
        if (MTC_RCM_TC_STOP == MTC_GetCurrentTcStatus(enModemId))
        {
            /* 在全局变量中记录环回状态 */
            MTC_SetCurrentTcStatus(enModemId, MTC_RCM_TC_START);

            /* 通知RCM */
            MTC_SndRcmTcStatusNtf(enModemId, MTC_RCM_TC_START);
        }
    }
#endif

    /* CS STATE */
    if (enSessionType < MTC_SESSION_TYPE_CS_BUTT)
    {
        /* 若之前没有上报过，则需要通知RCM */
        enCsSrvStatus = MTC_GetCsSrvState(enModemId);
        if ( (PS_FALSE == MTC_IsCsSessionInfoExit(enModemId))
          && (TAF_MTC_SRV_NO_EXIST == enCsSrvStatus))
        {
            /* 置Session 类型 */
            MTC_SetCsSessionInfo(enModemId, enSessionType);

            MTC_SndRcmModemStateInd();

            return;
        }

        MTC_SetCsSessionInfo(enModemId, enSessionType);

        return;
    }

    /* Ps State发生改变，需要通知RCM */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (MTC_SESSION_TYPE_1X_PS_CALL != enSessionType)
    {
        return;
    }

    if ((PS_FALSE == MTC_IsPsSessionInfoExit(enModemId))
     && (TAF_MTC_SRV_NO_EXIST == enPsSrvStatus))
    {
        /* 置PS Session 类型 */
        MTC_SetPsSessionInfo(enModemId, enSessionType);

        if (MTC_RCM_MODEM_RAT_CFG_CL == enRatCfg)
        {
            /* CL模式不下发1X PS状态 */
            return;
        }

        MTC_SndRcmModemStateInd();

        return;
    }

    /* 置PS Session 类型 */
    MTC_SetPsSessionInfo(enModemId, enSessionType);
#endif
    return;
}

/*****************************************************************************
 函 数 名  : MTC_ProcEndSessionInd
 功能描述  : 处理END SESSION 消息
 输入参数  : MsgBlock* pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月04日
    作    者   : j00174725
    修改内容   : DTS2015082406288
  2.日    期   : 2015年9月18日
    作    者   : j00174725
    修改内容   :  DTS2015091108014
  3.日    期   : 2015年10月22日
    作    者   : h00313353
    修改内容   : Iteration 19 TAS
*****************************************************************************/
VOS_VOID MTC_ProcEndSessionInd(VOS_VOID *pMsg)
{
    TAF_PS_MSG_STRU                    *pstMsg              = VOS_NULL_PTR;
    MTC_END_SESSION_IND_STRU           *pstEndSessionInd    = VOS_NULL_PTR;
    VOS_UINT32                          ulPid;
    VOS_UINT32                          ulSessionValue;
    MODEM_ID_ENUM_UINT16                enModemId;
    MTC_SESSION_TYPE_ENUM_UINT8         enSessionType;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enCsSrvStatus;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    MTC_RCM_MODEM_RAT_CFG_ENUM_UINT16   enRatCfg;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enPsSrvStatus;

    enRatCfg                            = MTC_RCM_MODEM_RAT_CFG_BUTT;
    enPsSrvStatus                       = TAF_MTC_SRV_CONN_STATE_BUTT;
#endif

    /* 勾取可维可测信息 */
    MTC_DEBUG_TraceAllModemConnStateInfo();

    pstMsg              = (TAF_PS_MSG_STRU *)pMsg;
    pstEndSessionInd    = (MTC_END_SESSION_IND_STRU *)pstMsg->aucContent;
    ulPid               = pstEndSessionInd->stCtrl.ulModuleId;
    ulSessionValue      = 0;

    /* 根据 Pid获取modem ID */
    enModemId       = VOS_GetModemIDFromPid(ulPid);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (UEPS_PID_XCC == ulPid)
    {
        enModemId       = MTC_GetCtxAddr()->enCdmaModemId;

        if (enModemId < MODEM_ID_BUTT)
        {
            enRatCfg        = MTC_ConvertToRcmRatCfg(MTC_GetUsimStateInfo(enModemId),
                                                     MTC_GetRatCfgByModemId(enModemId));

            enPsSrvStatus   = MTC_GetPsSrvState(enModemId);
        }
    }
#endif

    if (enModemId >= MODEM_ID_BUTT)
    {
        MTC_ERROR_LOG("MTC_ProcBeginSessionInd: Modem Id Err.");
        return;
    }

    enSessionType       = pstEndSessionInd->enSessionType;

    /* 异常Session排除 */
    if ((MTC_SESSION_TYPE_CS_BUTT   == enSessionType)
     || (MTC_SESSION_TYPE_BUTT      <= enSessionType))
    {
        return;
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (MTC_SESSION_TYPE_CS_LOOP_BACK == enSessionType)
    {
        /* 环回模式END，发送给RCM */
        if (MTC_RCM_TC_START == MTC_GetCurrentTcStatus(enModemId))
        {
            /* 在全局变量中记录环回状态 */
            MTC_SetCurrentTcStatus(enModemId, MTC_RCM_TC_STOP);

            /* 通知RCM */
            MTC_SndRcmTcStatusNtf(enModemId, MTC_RCM_TC_STOP);
        }
    }
#endif

    if (enSessionType < MTC_SESSION_TYPE_CS_BUTT)
    {
        /* 判断是否给RCM上报 */
        ulSessionValue  = ~(MTC_SET_BIT(enSessionType));
        enCsSrvStatus   = MTC_GetCsSrvState(enModemId);
        if ( (MTC_NO_SESSION_INFO   == (MTC_GetCsSessionInfo(enModemId) & ulSessionValue))
          && (TAF_MTC_SRV_NO_EXIST  == enCsSrvStatus) )
        {
            /* 清除session记录 */
            MTC_ClearCsSessionInfo(enModemId, enSessionType);

            /* 发送消息通知RCM */
            MTC_SndRcmModemStateInd();

            return ;
        }

        /* 清除session记录 */
        MTC_ClearCsSessionInfo(enModemId, enSessionType);

        return;
    }

    /* Ps State发生改变，需要通知RCM */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* 只处理1X上报的PS Session Type */
    if (MTC_SESSION_TYPE_1X_PS_CALL != enSessionType)
    {
        return;
    }

    ulSessionValue  = ~(MTC_SET_BIT(enSessionType));
    if ((MTC_NO_SESSION_INFO    == (MTC_GetPsSessionInfo(enModemId) & ulSessionValue))
     && (TAF_MTC_SRV_NO_EXIST   == enPsSrvStatus))
    {
        /* 清除PS Session 类型 */
        MTC_ClearPsSessionInfo(enModemId, enSessionType);

        if (MTC_RCM_MODEM_RAT_CFG_CL == enRatCfg)
        {
            /* CL模式不下发1X PS状态 */
            return;
        }

        MTC_SndRcmModemStateInd();

        return;
    }

    /* 置PS Session 类型 */
    MTC_ClearPsSessionInfo(enModemId, enSessionType);
#endif

    return;
}

/*****************************************************************************
 函 数 名  : MTC_IsNeedSndTasCsInfo2Rcm
 功能描述  : 判断是否需要将CS状态发送给rcm
 输入参数  : MTC_CS_TYPE_ENUM_UINT8
 输出参数  : 无
 返 回 值  : PS_TRUE/PS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月18日
    作    者   : j00174725
    修改内容   : DTS2015091108014
*****************************************************************************/
PS_BOOL_ENUM_UINT8 MTC_IsNeedSndTasCsInfo2Rcm(
    MODEM_ID_ENUM_UINT16                enModemId,
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enCsSrvConnState,
    MTC_CS_TYPE_ENUM_UINT8              enCsType
)
{
    PS_BOOL_ENUM_UINT8                  enSndFlag;
    PS_BOOL_ENUM_UINT8                  enCsSessionExit;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enCsSrvStatus;
    VOS_UINT8                           ucCsTypeInfo;
    VOS_UINT8                           ucCsTypeValue;


    enCsSessionExit     = MTC_IsCsSessionInfoExit(enModemId);
    enCsSrvStatus       = MTC_GetCsSrvState(enModemId);
    enSndFlag           = PS_FALSE;

    switch(enCsType)
    {
        case MTC_CS_TYPE_GU:
            ucCsTypeValue = MTC_SET_BIT(MTC_CS_TYPE_GU);
            break;

        case MTC_CS_TYPE_IMS:
            ucCsTypeValue = MTC_SET_BIT(MTC_CS_TYPE_IMS);
            break;

        case MTC_CS_TYPE_CDMA:
        default:
            return PS_FALSE;
    }

    /* 新状态为CS存在 */
    if (TAF_MTC_SRV_EXIST == enCsSrvConnState)
    {
        /* CS状态是否是从无到有 */
        if ( (PS_FALSE              == enCsSessionExit)
          && (TAF_MTC_SRV_NO_EXIST  == enCsSrvStatus) )
        {
            enSndFlag = PS_TRUE;
        }
        else
        {
            enSndFlag = PS_FALSE;
        }
    }
    else /* 新状态为CS不存在 */
    {
        /* 之前的CS 类型信息 */
        ucCsTypeInfo    = MTC_GetCsTypeInfo(enModemId);

        /* 如果之前唯一存在当前类型的CS,则从有到无，需要通知RCM */
        if ( (ucCsTypeValue == ucCsTypeInfo)
          && (PS_FALSE == enCsSessionExit))
        {
            enSndFlag = PS_TRUE;
        }
        else
        {
            enSndFlag = PS_FALSE;
        }
    }

    return enSndFlag;
}

/*****************************************************************************
 函 数 名  : MTC_IsNeedBufModem0Msg
 功能描述  : 判断是否需要缓存消息
 输入参数  : ulSendPid
 输出参数  : 无
 返 回 值  : PS_TRUE/PS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月18日
    作    者   : j00174725
    修改内容   : DTS2015091108014
*****************************************************************************/
PS_BOOL_ENUM_UINT8 MTC_IsNeedBufModem0Msg(VOS_UINT32 ulSendPid)
{
    MTC_RATMODE_ENUM_UINT8                  enRatMode;

    enRatMode = MTC_GetModemRatMode(MODEM_ID_0);

    if ( (MTC_RATMODE_GSM == enRatMode)
      && (I0_UEPS_PID_GAS == ulSendPid))
    {
        return PS_FALSE;
    }

    if ( (MTC_RATMODE_WCDMA == enRatMode)
      && (WUEPS_PID_WRR == ulSendPid) )
    {
        return PS_FALSE;
    }

    if ( (MTC_RATMODE_LTE == enRatMode)
      && (PS_PID_ERRC == ulSendPid) )
    {
        return PS_FALSE;
    }

    if ( (MTC_RATMODE_TDS == enRatMode)
      && (TPS_PID_RRC == ulSendPid) )
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}

/*****************************************************************************
 函 数 名  : MTC_IsNeedPopModem0BufMsg
 功能描述  : 判断是否需要Pop缓存消息
 输入参数  : ulSendPid
 输出参数  : 无
 返 回 值  : PS_TRUE/PS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月18日
    作    者   : j00174725
    修改内容   : DTS2015091108014
*****************************************************************************/
PS_BOOL_ENUM_UINT8 MTC_IsNeedPopModem0BufMsg(VOS_UINT32 ulSendPid)
{
    MTC_RATMODE_ENUM_UINT8                  enRatMode;

    enRatMode = MTC_GetModemRatMode(MODEM_ID_0);

    if ( (MTC_RATMODE_GSM == enRatMode)
      && (I0_UEPS_PID_GAS == ulSendPid))
    {
        return PS_TRUE;
    }

    if ( (MTC_RATMODE_WCDMA == enRatMode)
      && (WUEPS_PID_WRR == ulSendPid) )
    {
        return PS_TRUE;
    }

    if ( (MTC_RATMODE_LTE == enRatMode)
      && (PS_PID_ERRC == ulSendPid) )
    {
        return PS_TRUE;
    }

    if ( (MTC_RATMODE_TDS == enRatMode)
      && (TPS_PID_RRC == ulSendPid) )
    {
        return PS_TRUE;
    }

    return PS_FALSE;
}


/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

