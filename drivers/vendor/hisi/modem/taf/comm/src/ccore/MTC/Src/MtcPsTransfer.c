/******************************************************************************

                  版权所有 (C), 2001-2013, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MtcPsTransfer.c
  版 本 号   : 初稿
  作    者   : l00198894
  生成日期   : 2013年10月21日
  最近修改   :
  功能描述   : 处理PS域切换相关功能
  函数列表   :
  修改历史   :
  1.日    期   : 2013年10月21日
    作    者   : l00198894
    修改内容   : 创建文件

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "MtcDebug.h"
#include "MtcComm.h"
#include "MtcPsTransfer.h"

#include "MtcGmmInterface.h"

#include "UsimPsInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

/*lint -e767 修改人: l00198894; */
#define    THIS_FILE_ID        PS_FILE_ID_MTC_PS_TRANSFER_C
/*lint +e767 修改人: l00198894; */

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : MTC_SndModem0MtaPsTransferInd
 功能描述  : 通知Modem0 MTA模块上报^PSTRANSFER命令
 输入参数  : enPsTransferCause    -- PS域切换原因值
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月21日
    作    者   : l00198894
    修改内容   : V9R1C50 SVLTE离网重选项目新增
*****************************************************************************/
VOS_VOID MTC_SndModem0MtaPsTransferInd(
    MTC_PS_TRANSFER_CAUSE_ENUM_UINT8    enPsTransferCause
)
{
    VOS_UINT16                          ulLenth;
    MTC_MTA_PS_TRANSFER_IND_STRU       *pstPsTransferInd = VOS_NULL_PTR;

    /* Added by Y00213812 for 主动离网重选, 2014-04-10, begin */
    MTC_PS_TRANSFER_CTX_STRU           *pstPsTransferCtx = VOS_NULL_PTR;

    pstPsTransferCtx                    = MTC_GetPsTransferCtxAddr();
    pstPsTransferCtx->enReportCause     = enPsTransferCause;
    /* Added by Y00213812 for 主动离网重选, 2014-04-10, end */

    ulLenth = sizeof(MTC_MTA_PS_TRANSFER_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 分配消息空间 */
    pstPsTransferInd = (MTC_MTA_PS_TRANSFER_IND_STRU*)PS_ALLOC_MSG(UEPS_PID_MTC, ulLenth);

    if (VOS_NULL_PTR == pstPsTransferInd)
    {
        MTC_ERROR_LOG("MTC_SndModem0MtaPsTransferInd: Alloc msg fail!");
        return;
    }

    /* 清消息空间 */
    PS_MEM_SET((VOS_UINT8*)pstPsTransferInd + VOS_MSG_HEAD_LENGTH, 0, ulLenth);

    /* 填充消息 */
    pstPsTransferInd->stMsgHeader.ulReceiverPid = I0_UEPS_PID_MTA;
    pstPsTransferInd->stMsgHeader.ulMsgName     = ID_MTC_MTA_PS_TRANSFER_IND;
    pstPsTransferInd->ucCause                   = enPsTransferCause;

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTC, pstPsTransferInd))
    {
        MTC_ERROR1_LOG("MTC_SndModem0MtaPsTransferInd: Snd Msg err. Rec Pid ", I0_UEPS_PID_MTA);
        return;
    }

    /* 可维可测: 记录上报PS域迁移指示次数 */
    MTC_DEBUG_SndPsTransferInd(enPsTransferCause);

    return;
}

/*****************************************************************************
 函 数 名  : MTC_SndModem0GmmRrcAreaLostInd
 功能描述  : 通知Modem0 gmm rrc假丢网指示
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月8日
    作    者   : z00161729
    修改内容   : SVLTE优化G-TL ps切换性能修改
*****************************************************************************/
VOS_VOID MTC_SndModem0GmmRrcAreaLostInd(VOS_VOID)
{
    VOS_UINT16                          ulLenth;
    MTC_GMM_RRC_AREA_LOST_IND_STRU     *pstAreaLostInd = VOS_NULL_PTR;

    ulLenth = sizeof(MTC_GMM_RRC_AREA_LOST_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 分配消息空间 */
    pstAreaLostInd = (MTC_GMM_RRC_AREA_LOST_IND_STRU*)PS_ALLOC_MSG(UEPS_PID_MTC, ulLenth);

    if (VOS_NULL_PTR == pstAreaLostInd)
    {
        MTC_ERROR_LOG("MTC_SndModem0GmmRrcAreaLostInd: Alloc msg fail!");
        return;
    }

    /* 清消息空间 */
    PS_MEM_SET((VOS_UINT8*)pstAreaLostInd + VOS_MSG_HEAD_LENGTH, 0, ulLenth);

    /* 填充消息 */
    pstAreaLostInd->stMsgHeader.ulReceiverPid   = I0_WUEPS_PID_GMM;
    pstAreaLostInd->stMsgHeader.ulMsgName       = ID_MTC_GMM_RRC_AREA_LOST_IND;

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTC, pstAreaLostInd))
    {
        MTC_ERROR1_LOG("MTC_SndModem0GmmRrcAreaLostInd: Snd Msg err. Rec Pid ", I0_UEPS_PID_MTA);
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : MTC_SndModem0MmaPsTransferInd
 功能描述  : 通知Modem0的mma ps transfer消息
 输入参数  : enPsTransferCause - MTC模块PS域切换原因值
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月25日
    作    者   : z00161729
    修改内容   : SVLTE优化G-TL ps切换性能修改
  2.日    期   : 2014年01月17日
    作    者   : l00198894
    修改内容   : V9R1C53 C+L 离网重选项目
*****************************************************************************/
VOS_VOID MTC_SndModem0MmaPsTransferInd(
    MTC_PS_TRANSFER_CAUSE_ENUM_UINT8    enPsTransferCause
)
{
    VOS_UINT16                          ulLenth;
    MTC_MMA_PS_TRANSFER_IND_STRU       *pstPsTransferInd = VOS_NULL_PTR;

    ulLenth = sizeof(MTC_MMA_PS_TRANSFER_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 分配消息空间 */
    pstPsTransferInd = (MTC_MMA_PS_TRANSFER_IND_STRU*)PS_ALLOC_MSG(UEPS_PID_MTC, ulLenth);

    if (VOS_NULL_PTR == pstPsTransferInd)
    {
        MTC_ERROR_LOG("MTC_SndMmaPsTransferInd: Alloc msg fail!");
        return;
    }

    /* 清消息空间 */
    PS_MEM_SET((VOS_UINT8*)pstPsTransferInd + VOS_MSG_HEAD_LENGTH, 0, ulLenth);

    /* 填充消息 */
    pstPsTransferInd->stMsgHeader.ulReceiverPid     = I0_WUEPS_PID_MMA;
    pstPsTransferInd->stMsgHeader.ulMsgName         = ID_MTC_MMA_PS_TRANSFER_IND;
    pstPsTransferInd->enSolutionCfg                 = MTC_GetPsTransferCfg();
    pstPsTransferInd->ucCause                       = enPsTransferCause;

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTC, pstPsTransferInd))
    {
        MTC_ERROR1_LOG("MTC_SndMmaPsTransferInd: Snd Msg err. Rec Pid ", I0_WUEPS_PID_MMA);
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : MTC_RcvRrcAreaLostInd
 功能描述  : 收到接入层上报丢网消息
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月21日
    作    者   : l00198894
    修改内容   : V9R1C50 SVLTE离网重选项目新增
  2.日    期   : 2013年11月22日
    作    者   : z00161729
    修改内容   : SVLTE优化G-TL ps切换性能修改
  3.日    期   : 2014年01月17日
    作    者   : l00198894
    修改内容   : V9R1C53 C+L 离网重选项目
  4.日    期   : 2014年1月23日
    作    者   : z00161729
    修改内容   : DTS2014012305088:svlte特性开启卡无效场景mtc无需上报pstransfer:0
  5.日    期   : 2014年4月09日
    作    者   : Y00213812
    修改内容   : 主动离网重选需需要记录是否上报过pstransfer:0
*****************************************************************************/
VOS_VOID MTC_RcvRrcAreaLostInd(VOS_VOID * pMsg)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    RRC_MTC_AREA_LOST_IND_STRU         *pstAreaLostInd = VOS_NULL_PTR;
    MTC_MODEM_POWER_STATE_ENUM_UINT8    enModem1PowerState;
    MTC_OPERATOR_CUST_SOLUTION_ENUM_UINT8   enOperatorCustSolution;
    VOS_BOOL                            enTestCardFlg;

    /* Added by Y00213812 for 主动离网重选, 2014-04-10, begin */
    MTC_PS_TRANSFER_CTX_STRU           *pstPsTransferCtx    = VOS_NULL_PTR;
    pstPsTransferCtx                    = MTC_GetPsTransferCtxAddr();
    /* Added by Y00213812 for 主动离网重选, 2014-04-10, end */

    /* GCF测试时不需要启动PSTRANSFER流程，否则导致GCF测试部不通过 */
    enTestCardFlg = USIMM_IsTestCard();
    if (VOS_TRUE == enTestCardFlg)
    {
        return;
    }

    pstAreaLostInd      = (RRC_MTC_AREA_LOST_IND_STRU*)pMsg;
    enModemId           = VOS_GetModemIDFromPid(pstAreaLostInd->stMsgHeader.ulSenderPid);

    /* 仅处理Modem0发送的丢网指示 */
    if (enModemId != MODEM_ID_0)
    {
        MTC_ERROR1_LOG("MTC_RcvRrcAreaLostInd: Err ModemId ", enModemId);
        return;
    }

    /* 未开启PS域迁移策略，只记录次数 */
    if (MTC_PS_TRANSFER_NONE == MTC_GetPsTransferCfg())
    {
        /* 可维可测: 记录接收到丢网指示的次数 */
        MTC_DEBUG_RcvRrcAreaLostInd(pstAreaLostInd->stMsgHeader.ulSenderPid);
        return;
    }

    /* 运营商定制方案SVLTE或C+L时需要上报AT丢网指示 */
    enOperatorCustSolution  = MTC_GetOperatorCustSolution();
    enModem1PowerState      = MTC_GetModemPowerState(MODEM_ID_1);

    /* 当接入层在业务态或idle态丢网且Modem1开机且卡有效时，上报PS域迁移指示 */
    if ((VOS_TRUE == MTC_GetModemUsimValidFlag(enModemId))
     && (((MTC_OPERATOR_CUST_CMCC_SVLTE == enOperatorCustSolution)
       && (MTC_MODEM_POWER_ON == enModem1PowerState))
      || (MTC_OPERATOR_CUST_CT_LC == enOperatorCustSolution) ))
    {
        /* Modified by Y00213812 for 主动离网重选, 2014-04-10, begin */
        if (MTC_PS_TRANSFER_CAUSE_AREA_LOST != pstPsTransferCtx->enReportCause)
        {
            MTC_SndModem0MtaPsTransferInd(MTC_PS_TRANSFER_CAUSE_AREA_LOST);

            /* 通知modem0 gmm丢网，gmm记录全局变量后续detach只做一次减少detach时间 */
            MTC_SndModem0GmmRrcAreaLostInd();
        }
        /* Modified by Y00213812 for 主动离网重选, 2014-04-10, end */
    }

    /* Added by Y00213812 for 主动离网重选, 2014-04-10, begin */
    pstPsTransferCtx->enRrcCause = MTC_PS_TRANSFER_CAUSE_AREA_LOST;
    /* Added by Y00213812 for 主动离网重选, 2014-04-10, end */

    /* 可维可测: 记录接收到丢网指示的次数 */
    MTC_DEBUG_RcvRrcAreaLostInd(pstAreaLostInd->stMsgHeader.ulSenderPid);

    return;
}

/*****************************************************************************
 函 数 名  : MTC_RcvRrcAreaAvaliableInd
 功能描述  : 收到接入层上报网络恢复消息
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年01月17日
    作    者   : l00198894
    修改内容   : V9R1C53 C+L 离网重选项目

  2.日    期   : 2014年4月09日
    作    者   : Y00213812
    修改内容   : 主动离网重选需需要记录主模是否Avaliable

  3.日    期   : 2014年5月29日
    作    者   : x00203213
    修改内容   : 增加NCELL搜网RAT 顺序更改；当驻留LTE 的时候，NCELL 搜索先搜索TDS，防止LTE差信号始终没有机会搜索TDS；
                              为保证离网的时候有足够的时间评估，驻留的时候不发消息给mma停艘网定时器
*****************************************************************************/
VOS_VOID MTC_RcvRrcAreaAvaliableInd(VOS_VOID * pMsg)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    RRC_MTC_AREA_AVALIABLE_IND_STRU    *pstAreaAvaliableInd = VOS_NULL_PTR;
    MTC_MODEM_NETWORK_INFO_STRU        *pstNetworkInfo      = VOS_NULL_PTR;

    /* Added by Y00213812 for 主动离网重选, 2014-04-10, begin */
    VOS_UINT8                           ucUsimValidFlag;
    MTC_PS_TRANSFER_CTX_STRU           *pstPsTransferCtx    = VOS_NULL_PTR;

    pstPsTransferCtx    = MTC_GetPsTransferCtxAddr();
    ucUsimValidFlag     = MTC_GetModemUsimValidFlag(MODEM_ID_0);
    /* Added by Y00213812 for 主动离网重选, 2014-04-10, end */

    pstAreaAvaliableInd = (RRC_MTC_AREA_AVALIABLE_IND_STRU*)pMsg;
    enModemId           = VOS_GetModemIDFromPid(pstAreaAvaliableInd->stMsgHeader.ulSenderPid);

    /* 仅处理Modem0发送的网络恢复指示 */
    if (enModemId != MODEM_ID_0)
    {
        MTC_ERROR1_LOG("MTC_RcvRrcAreaAvaliableInd: Err ModemId ", enModemId);
        return;
    }

    /* PS域离网重选策略开启时 */
    if (MTC_PS_TRANSFER_OFF_AREA == MTC_GetPsTransferCfg())
    {
        pstNetworkInfo = MTC_GetModemNetworkInfoAddr(enModemId);

        /* Modified by Y00213812 for 主动离网重选, 2014-04-10, begin */
        /* 当前驻留网络非禁止PLMN、非禁止GPRS接入、卡状态有效、不重复上报 */
        if ( (VOS_FALSE == pstNetworkInfo->ucIsForbiddenPlmnFlag)
          && (VOS_TRUE == pstNetworkInfo->stPsDomainInfo.ucPsSupportFlg)
          && (VOS_TRUE == ucUsimValidFlag)
          && (MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE != pstPsTransferCtx->enReportCause))
        {
            /* 上报PS域迁移网络恢复指示AT命令 */
            MTC_SndModem0MtaPsTransferInd(MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE);
        }

        pstPsTransferCtx->enRrcCause = MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE;
        /* Modified by Y00213812 for 主动离网重选, 2014-04-10, end */

        MTC_SndModem0MmaPsTransferInd(MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE);
 
    }

    /* 可维可测: 记录接收到丢网指示的次数 */
    MTC_DEBUG_RcvRrcAreaAvaliableInd();

    return;
}

/*****************************************************************************
 函 数 名  : MTC_ProcCurrCampPlmnInfoForSvlte
 功能描述  : SVLTE方案Modem0网络恢复时PS域迁移流程处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年01月17日
    作    者   : l00198894
    修改内容   : V9R1C53 C+L 离网重选项目
  2.日    期   : 2014年1月23日
    作    者   : z00161729
    修改内容   : DTS2014012305088:svlte特性开启卡无效场景mtc无需上报pstransfer:0和1
  3.日    期   : 2014年4月09日
    作    者   : Y00213812
    修改内容   : 主动离网重选:主模注册成功后上报pstransfer:1

    4.日    期   : 2014年5月29日
    作    者   : x00203213
    修改内容   : 增加NCELL搜网RAT 顺序更改；当驻留LTE 的时候，NCELL 搜索先搜索TDS，防止LTE差信号始终没有机会搜索TDS；
                              为保证离网的时候有足够的时间评估，驻留的时候不发消息给mma停艘网定时器
*****************************************************************************/
VOS_VOID MTC_ProcCurrCampPlmnInfoForSvlte(VOS_VOID)
{
    MTC_MODEM_POWER_STATE_ENUM_UINT8    enModem1PowerState;
    MTC_MODEM_NETWORK_INFO_STRU        *pstModem0NetworkInfo = VOS_NULL_PTR;
    MTC_PS_TRANSFER_ENUM_UINT8          enPsTransferSolution;
    MTC_RATMODE_ENUM_UINT8              enModem0RateMode;

    VOS_UINT8                           ucUsimValidFlag;

    /* Added by Y00213812 for 主动离网重选, 2014-04-10, begin */
    MTC_PS_TRANSFER_CTX_STRU           *pstPsTransferCtx    = VOS_NULL_PTR;
    pstPsTransferCtx                    = MTC_GetPsTransferCtxAddr();
    /* Added by Y00213812 for 主动离网重选, 2014-04-10, end */

    enModem1PowerState      = MTC_GetModemPowerState(MODEM_ID_1);
    pstModem0NetworkInfo    = MTC_GetModemNetworkInfoAddr(MODEM_ID_0);
    enPsTransferSolution    = MTC_GetPsTransferCfg();
    enModem0RateMode        = MTC_GetModemRatMode(MODEM_ID_0);



    /* Modem1关机，国外模式无需PS域迁移 */
    if (MTC_MODEM_POWER_OFF == enModem1PowerState)
    {
        return;
    }

    ucUsimValidFlag = MTC_GetModemUsimValidFlag(MODEM_ID_0);

    /* 1、modem1处于开机状态
       2、当前驻留网络接入技术为T/L(OscarTL通过主卡的G重选回T/L)
       3、当前驻留网络非禁止plmn
       4、单待模式modem0的ps是detach状态，上报PS域迁移指示 */
    if ( ( (MTC_RATMODE_LTE == enModem0RateMode)
        || (MTC_RATMODE_TDS == enModem0RateMode) )
      && (VOS_FALSE == pstModem0NetworkInfo->ucIsForbiddenPlmnFlag)
      && (VOS_TRUE == ucUsimValidFlag)
      && (VOS_FALSE == pstModem0NetworkInfo->stPsDomainInfo.ucPsAttachAllowFlg)
      && (VOS_TRUE == pstModem0NetworkInfo->stPsDomainInfo.ucPsSupportFlg) )
    {
        /* PS域迁移策略脱网重选，上报网络恢复指示AT命令 */
        if (MTC_PS_TRANSFER_LOST_AREA == enPsTransferSolution)
        {
            MTC_SndModem0MtaPsTransferInd(MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE);
            MTC_SndModem0MmaPsTransferInd(MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE);
        }

        /* Added by Y00213812 for 主动离网重选, 2014-04-10, begin */
        /* PS域迁移策略离网重选，上报网络恢复指示AT命令 */
        if ((MTC_PS_TRANSFER_OFF_AREA == enPsTransferSolution)
         && (MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE == pstPsTransferCtx->enRrcCause))
        {
            MTC_SndModem0MtaPsTransferInd(MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE);
            MTC_SndModem0MmaPsTransferInd(MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE);
        }
        /* Added by Y00213812 for 主动离网重选, 2014-04-10, end */
        //MTC_SndModem0MmaPsTransferInd(MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE);

    }

    return;
}

/*****************************************************************************
 函 数 名  : MTC_ProcCurrCampPlmnInfoForLC
 功能描述  : C+L方案Modem0网络恢复时PS域迁移流程处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年01月17日
    作    者   : l00198894
    修改内容   : V9R1C53 C+L 离网重选项目
  2.日    期   : 2014年4月09日
    作    者   : Y00213812
    修改内容   : 主动离网重选:主模注册成功后上报pstransfer:1
*****************************************************************************/
VOS_VOID MTC_ProcCurrCampPlmnInfoForLC(VOS_VOID)
{
    MTC_MODEM_NETWORK_INFO_STRU        *pstModem0NetworkInfo = VOS_NULL_PTR;
    MTC_PS_TRANSFER_ENUM_UINT8          enPsTransferSolution;
    MTC_RATMODE_ENUM_UINT8              enModem0RateMode;

    /* Added by Y00213812 for 主动离网重选, 2014-04-10, begin */
    MTC_PS_TRANSFER_CTX_STRU           *pstPsTransferCtx    = VOS_NULL_PTR;
    pstPsTransferCtx                    = MTC_GetPsTransferCtxAddr();
    /* Added by Y00213812 for 主动离网重选, 2014-04-10, end */


    pstModem0NetworkInfo    = MTC_GetModemNetworkInfoAddr(MODEM_ID_0);
    enPsTransferSolution    = MTC_GetPsTransferCfg();
    enModem0RateMode        = MTC_GetModemRatMode(MODEM_ID_0);

    /* 1、当前驻留网络非禁止plmn
        2、单待模式modem0的ps是detach状态，上报PS域迁移指示 */
    if ( (MTC_RATMODE_LTE == enModem0RateMode)
      && (VOS_FALSE == pstModem0NetworkInfo->ucIsForbiddenPlmnFlag)
      && (VOS_FALSE == pstModem0NetworkInfo->stPsDomainInfo.ucPsAttachAllowFlg))
    {
        /* PS域迁移策略脱网重选，上报网络恢复指示AT命令 */
        if (MTC_PS_TRANSFER_LOST_AREA == enPsTransferSolution)
        {
            MTC_SndModem0MtaPsTransferInd(MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE);
        }

        /* Added by Y00213812 for 主动离网重选, 2014-04-10, begin */
        /* PS域迁移策略离网重选，上报网络恢复指示AT命令 */
        if ((MTC_PS_TRANSFER_OFF_AREA == enPsTransferSolution)
         && (MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE == pstPsTransferCtx->enRrcCause))
        {
            MTC_SndModem0MtaPsTransferInd(MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE);
        }
        /* Added by Y00213812 for 主动离网重选, 2014-04-10, end */

        MTC_SndModem0MmaPsTransferInd(MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE);
    }

    return;
}

/* Added by Y00213812 for 主动离网重选, 2014-04-10, begin */
/*****************************************************************************
 函 数 名  : MTC_RcvGsmCellInfoInd
 功能描述  : 接收到ID_MTC_RRC_GSM_CELL_INFO_IND上报频点和信号强度消息的处理
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年04月08日
    作    者   : Y00213812
    修改内容   : RF&LCD干扰规避项目新增
*****************************************************************************/
VOS_VOID MTC_RcvGsmCellInfoInd(VOS_VOID *pMsg)
{
    RRC_MTC_GSM_CELL_INFO_IND_STRU     *pstGsmInfoInd  = VOS_NULL_PTR;
    MTC_RRC_GSM_CELL_INFO_IND_STRU     *pstGsmCellInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;

    /* 如果当前已经关机，则停止发送信息 */
    if (MTC_MODEM_POWER_OFF == MTC_GetModemPowerState(MODEM_ID_0))
    {
        return;
    }

    /* 判断当前主模状态, 为TDS/LTE时发送 */
    if (MTC_RATMODE_TDS == MTC_GetModemRatMode(MODEM_ID_0))
    {
        ulReceiverPid = TPS_PID_RRC;
    }
    else if (MTC_RATMODE_LTE== MTC_GetModemRatMode(MODEM_ID_0))
    {
        ulReceiverPid = PS_PID_ERRC;
    }
    else
    {
        return;
    }

    /* 分配消息空间 */
    pstGsmCellInfo  = (MTC_RRC_GSM_CELL_INFO_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                UEPS_PID_MTC,
                                                                sizeof(MTC_RRC_GSM_CELL_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstGsmCellInfo)
    {
        MTC_ERROR_LOG("MTC_RcvGsmCellInfoInd: Alloc Msg Fail!");
        return;
    }

    pstGsmCellInfo->stMsgHeader.ulReceiverPid = ulReceiverPid;
    pstGsmCellInfo->stMsgHeader.ulMsgName     = ID_MTC_RRC_GSM_CELL_INFO_IND;

    pstGsmInfoInd                             = (RRC_MTC_GSM_CELL_INFO_IND_STRU *)pMsg;
    PS_MEM_CPY(&pstGsmCellInfo->stGsmCellInfo,
               &pstGsmInfoInd->stGsmCellInfo,
               sizeof(RRC_MTC_GSM_CELL_INFO_STRU));

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTC, pstGsmCellInfo))
    {
        MTC_ERROR_LOG("MTC_RcvGsmCellInfoInd: Snd Msg Err!");
    }

    return;

}
/* Added by Y00213812 for 主动离网重选, 2014-04-10, end */

/*lint +e958*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of MtcPsTransfer.c */


