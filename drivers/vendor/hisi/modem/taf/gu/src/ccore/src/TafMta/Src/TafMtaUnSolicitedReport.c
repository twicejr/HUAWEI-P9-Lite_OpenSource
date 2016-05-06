/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMtaUnsolicitedReport.c
  版 本 号   : 初稿
  作    者   : 赵学理
  生成日期   : 2013年4月11日
  最近修改   :
  功能描述   : MTA模块与at模块交互主动上报相关命令的处理函数
  函数列表   :
  修改历史   :
  1.日    期   : 2013年4月11日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */
#include "TafMtaUnSolicitedReport.h"
/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-2, end */

/*lint -e958*/

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 */
#define    THIS_FILE_ID                 PS_FILE_ID_TAF_MTA_UNSILICITED_REPORT_C
/*lint +e767 */

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-1, begin */
/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtSetCurcNotify
 功能描述  : mta收到ID_AT_MTA_SET_CURC_NOTIFY消息处理函数
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月1日
    作    者   : s00217060
    修改内容   : 主动上报AT命令控制下移至C核新增函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtSetCurcNotify(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                            *pstAtMtaMsg             = VOS_NULL_PTR;
    AT_MTA_CURC_SET_NOTIFY_STRU                *pstAtMtaSetCurcNotify   = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU                 *pstCurcRptCtrl          = VOS_NULL_PTR;

    pstAtMtaMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstAtMtaSetCurcNotify   = (AT_MTA_CURC_SET_NOTIFY_STRU *)pstAtMtaMsg->aucContent;
    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();

    /* 更新CURC全局变量 */
    pstCurcRptCtrl->enStatusRptGeneralControl = pstAtMtaSetCurcNotify->enCurcRptType;
    PS_MEM_CPY(pstCurcRptCtrl->aucRptCfg, pstAtMtaSetCurcNotify->aucRptCfg, sizeof(pstCurcRptCtrl->aucRptCfg));

    /* 给STK发送消息通知本次CURC设置 */
    TAF_MTA_SndStkCurcRptCfgInfoInd(pstAtMtaSetCurcNotify);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtQryCurcReq
 功能描述  : mta收到ID_AT_MTA_QRY_CURC_REQ消息处理函数
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月1日
    作    者   : s00217060
    修改内容   : 主动上报AT命令控制下移至C核新增函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtQryCurcReq(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                            *pstAtMtaMsg             = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU                 *pstCurcRptCtrl          = VOS_NULL_PTR;
    MTA_AT_CURC_QRY_CNF_STRU                    stQryCurcCnf;

    pstAtMtaMsg             = (AT_MTA_MSG_STRU *)pMsg;

    /* 获取CURC全局变量 */
    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();

    /* 填充消息内容 */
    PS_MEM_SET(&stQryCurcCnf, 0x00, sizeof(stQryCurcCnf));
    stQryCurcCnf.enResult       = MTA_AT_RESULT_NO_ERROR;
    stQryCurcCnf.enCurcRptType  = (AT_MTA_RPT_GENERAL_CTRL_TYPE_ENUM_UINT8)
                                    pstCurcRptCtrl->enStatusRptGeneralControl;

    PS_MEM_CPY(stQryCurcCnf.aucRptCfg, pstCurcRptCtrl->aucRptCfg, sizeof(stQryCurcCnf.aucRptCfg));

    /* 给AT发送查询CURC回复 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)&(pstAtMtaMsg->stAppCtrl),
                     ID_MTA_AT_CURC_QRY_CNF,
                     sizeof(stQryCurcCnf),
                     (VOS_UINT8*)&stQryCurcCnf);

    return;
}
/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtSetUnsolicitedRptReq
 功能描述  : mta收到ID_AT_MTA_SET_UNSOLICITED_RPT_REQ消息处理函数
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月1日
    作    者   : s00217060
    修改内容   : 主动上报AT命令控制下移至C核新增函数
  2.日    期   : 2013年5月25日
    作    者   : s00217060
    修改内容   : for DTS2013052406352:
                 DSFLOWRPT设置命令通过ID_MSG_TAF_PS_CONFIG_DSFLOW_RPT_REQ到APS更新
  3.日    期   : 2014年8月18日
    作    者   : w00242748
    修改内容   : DTS2014082204531:CREG=1或CGREG=1设置之后，CREG主动上报和CGREG主动上报
                 不断上报。
  4.日    期   : 2015年11月19日
    作    者   : h00360002
    修改内容   : 为ctzr添加ctze上报方式
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtSetUnsolicitedRptReq(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                            *pstAtMtaMsg             = VOS_NULL_PTR;
    AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU        *pstSetUnsolicitedRptReq = VOS_NULL_PTR;
    MTA_AT_UNSOLICITED_RPT_SET_CNF_STRU         stSetUnsolicitedRptCnf;
    TAF_SDC_RPT_CMD_INDEX_ENUM_UINT8            enRptCmdIndex;
    VOS_UINT32                                  ulRptCmdStatus;

    pstAtMtaMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstSetUnsolicitedRptReq = (AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU *)pstAtMtaMsg->aucContent;

    /* 更新单个命令设置主动上报的全局变量 */
    switch (pstSetUnsolicitedRptReq->enReqType)
    {
        case AT_MTA_SET_MODE_RPT_TYPE:
            enRptCmdIndex   = TAF_SDC_RPT_CMD_MODE;
            ulRptCmdStatus  = (VOS_UINT32)pstSetUnsolicitedRptReq->u.ucModeRptFlg;
            break;

        case AT_MTA_SET_SRVST_RPT_TYPE:
            enRptCmdIndex   = TAF_SDC_RPT_CMD_SRVST;
            ulRptCmdStatus  = (VOS_UINT32)pstSetUnsolicitedRptReq->u.ucSrvstRptFlg;
            break;

        case AT_MTA_SET_RSSI_RPT_TYPE:
            enRptCmdIndex   = TAF_SDC_RPT_CMD_RSSI;
            ulRptCmdStatus  = (VOS_UINT32)pstSetUnsolicitedRptReq->u.ucRssiRptFlg;
            break;

        case AT_MTA_SET_TIME_RPT_TYPE:
            enRptCmdIndex   = TAF_SDC_RPT_CMD_TIME;
            ulRptCmdStatus  = (VOS_UINT32)pstSetUnsolicitedRptReq->u.ucTimeRptFlg;
            break;

        case AT_MTA_SET_CTZR_RPT_TYPE:

            ulRptCmdStatus  = (VOS_UINT32)pstSetUnsolicitedRptReq->u.ucCtzrRptFlg;

            /* 如果是CTZE则更新CTZE上报使能,CTZV去使能, 如果是CTZV则更新CTZV上报使能,CTZE去使能, 否则均去使能 */
            if (MTA_TAF_CTZR_CTZE == (MTA_TAF_CTZR_TYPE_ENUM_UINT32)ulRptCmdStatus)
            {
                TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CTZE, VOS_TRUE);
                enRptCmdIndex   = TAF_SDC_RPT_CMD_CTZV;
                ulRptCmdStatus = VOS_FALSE;
            }
            else if (MTA_TAF_CTZR_CTZV == (MTA_TAF_CTZR_TYPE_ENUM_UINT32)ulRptCmdStatus)
            {
                TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CTZV, VOS_TRUE);
                enRptCmdIndex   = TAF_SDC_RPT_CMD_CTZE;
                ulRptCmdStatus = VOS_FALSE;
            }
            else
            {
                TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CTZE, VOS_FALSE);
                enRptCmdIndex   = TAF_SDC_RPT_CMD_CTZV;
                ulRptCmdStatus = VOS_FALSE;
            }
            break;

        /* DSFLOWRPT设置命令通过ID_MSG_TAF_PS_CONFIG_DSFLOW_RPT_REQ到APS更新，此处删除 */

        case AT_MTA_SET_SIMST_RPT_TYPE:
            enRptCmdIndex   = TAF_SDC_RPT_CMD_SIMST;
            ulRptCmdStatus  = (VOS_UINT32)pstSetUnsolicitedRptReq->u.ucSimstRptFlg;
            break;


        case AT_MTA_SET_CREG_RPT_TYPE:
            enRptCmdIndex   = TAF_SDC_RPT_CMD_CREG;
            ulRptCmdStatus  = (VOS_UINT32)pstSetUnsolicitedRptReq->u.ucCregRptFlg;

            TAF_SDC_SetCregType(pstSetUnsolicitedRptReq->u.ucCregRptFlg);
            break;

        case AT_MTA_SET_CGREG_RPT_TYPE:
            enRptCmdIndex   = TAF_SDC_RPT_CMD_CGREG;
            ulRptCmdStatus  = (VOS_UINT32)pstSetUnsolicitedRptReq->u.ucCgregRptFlg;

            TAF_SDC_SetCgregType(pstSetUnsolicitedRptReq->u.ucCgregRptFlg);
            break;

        case AT_MTA_SET_CEREG_RPT_TYPE:
            enRptCmdIndex   = TAF_SDC_RPT_CMD_CEREG;
            ulRptCmdStatus  = (VOS_UINT32)pstSetUnsolicitedRptReq->u.ucCeregRptFlg;

            TAF_SDC_SetCeregType(pstSetUnsolicitedRptReq->u.ucCeregRptFlg);
            break;
        case AT_MTA_SET_CSID_RPT_TYPE:
            enRptCmdIndex   = TAF_SDC_RPT_CMD_CSID;
            ulRptCmdStatus  = (VOS_UINT32)pstSetUnsolicitedRptReq->u.ucCsidRptFlg;
            break;
        case AT_MTA_SET_CLOCINFO_RPT_TYPE:
            enRptCmdIndex   = TAF_SDC_RPT_CMD_CLOCINFO;
            ulRptCmdStatus  = (VOS_UINT32)pstSetUnsolicitedRptReq->u.ucClocinfoRptFlg;
            break;
        default:
            enRptCmdIndex   = TAF_SDC_RPT_CMD_BUTT;
            ulRptCmdStatus  = VOS_TRUE;
            break;
    }

    TAF_SDC_UpdateRptCmdStatus(enRptCmdIndex, ulRptCmdStatus);

    /* 填充消息内容 */
    PS_MEM_SET(&stSetUnsolicitedRptCnf, 0x00, sizeof(stSetUnsolicitedRptCnf));
    stSetUnsolicitedRptCnf.enResult = MTA_AT_RESULT_NO_ERROR;

    /* 给AT发送设置回复 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)&(pstAtMtaMsg->stAppCtrl),
                     ID_MTA_AT_UNSOLICITED_RPT_SET_CNF,
                     sizeof(stSetUnsolicitedRptCnf),
                     (VOS_UINT8*)&stSetUnsolicitedRptCnf);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtQryUnsolicitedRptReq
 功能描述  : mta收到ID_AT_MTA_QRY_UNSOLICITED_RPT_REQ消息处理函数
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月1日
    作    者   : s00217060
    修改内容   : 主动上报AT命令控制下移至C核新增函数
  2.日    期   : 2015年11月17日
    作    者   : h00360002
    修改内容   : CTZR中新增CTZE上报
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtQryUnsolicitedRptReq(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                            *pstAtMtaMsg             = VOS_NULL_PTR;
    AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU        *pstQryUnsolicitedRptReq = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU          *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;
    MTA_AT_UNSOLICITED_RPT_QRY_CNF_STRU         stQryUnsolicitedRptCnf;

    pstAtMtaMsg                 = (AT_MTA_MSG_STRU *)pMsg;
    pstQryUnsolicitedRptReq     = (AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU *)pstAtMtaMsg->aucContent;

    /* 获取单个命令主动上报的全局变量 */
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    PS_MEM_SET(&stQryUnsolicitedRptCnf, 0x00, sizeof(stQryUnsolicitedRptCnf));
    stQryUnsolicitedRptCnf.enReqType = pstQryUnsolicitedRptReq->enReqType;
    stQryUnsolicitedRptCnf.enResult  = MTA_AT_RESULT_NO_ERROR;

    switch (pstQryUnsolicitedRptReq->enReqType)
    {
        case AT_MTA_QRY_TIME_RPT_TYPE:
            stQryUnsolicitedRptCnf.u.ucTimeRptFlg =
                        (VOS_UINT8)TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                                TAF_SDC_RPT_CMD_TIME);
            break;

        case AT_MTA_QRY_CTZR_RPT_TYPE:
            if (VOS_TRUE == (VOS_UINT8)TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                    TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                    TAF_SDC_RPT_CMD_CTZV))
            {
                stQryUnsolicitedRptCnf.u.ucCtzrRptFlg = MTA_TAF_CTZR_CTZV;
            }
            else if (VOS_TRUE == (VOS_UINT8)TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                    TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                    TAF_SDC_RPT_CMD_CTZE))
            {
                stQryUnsolicitedRptCnf.u.ucCtzrRptFlg = MTA_TAF_CTZR_CTZE;
            }
            else
            {
                stQryUnsolicitedRptCnf.u.ucCtzrRptFlg = MTA_TAF_CTZR_OFF;
            }
            break;

        case AT_MTA_QRY_CSSN_RPT_TYPE:
            stQryUnsolicitedRptCnf.u.stCssnRptFlg.ucCssiRptFlg =
                    (VOS_UINT8)TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                            TAF_SDC_RPT_CMD_CSSI);

            stQryUnsolicitedRptCnf.u.stCssnRptFlg.ucCssuRptFlg =
                    (VOS_UINT8)TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                            TAF_SDC_RPT_CMD_CSSU);
            break;

        case AT_MTA_QRY_CUSD_RPT_TYPE:
            stQryUnsolicitedRptCnf.u.ucCusdRptFlg =
                    (VOS_UINT8)TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                            TAF_SDC_RPT_CMD_CUSD);
            break;

         default:
            break;
    }

    /* 给AT发送查询回复 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)&(pstAtMtaMsg->stAppCtrl),
                     ID_MTA_AT_UNSOLICITED_RPT_QRY_CNF,
                     sizeof(stQryUnsolicitedRptCnf),
                     (VOS_UINT8*)&stQryUnsolicitedRptCnf);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SysModeTransfer
 功能描述  : 接入技术模式转换
 输入参数  : TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode
 输出参数  : 无
 返 回 值  : TAF_SYS_MODE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月17日
    作    者   : zwx247453
    修改内容   : 新增函数

*****************************************************************************/
TAF_SYS_MODE_ENUM_UINT8 TAF_MTA_SysModeTransfer(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSdcSysMode
)
{
    TAF_SYS_MODE_ENUM_UINT8             enSysMode;

    enSysMode = TAF_PH_INFO_NONE_RAT;

    switch (enSdcSysMode)
    {
        case TAF_SDC_SYS_MODE_GSM:
            enSysMode = TAF_PH_INFO_GSM_RAT;
            break;

        case TAF_SDC_SYS_MODE_WCDMA:
            if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
            {
                enSysMode = TAF_PH_INFO_WCDMA_RAT;
            }
            else
            {
                enSysMode = TAF_PH_INFO_TD_SCDMA_RAT;
            }
            break;

        case TAF_SDC_SYS_MODE_LTE:
            enSysMode = TAF_PH_INFO_LTE_RAT;
            break;

        case TAF_SDC_SYS_MODE_CDMA_1X:
            enSysMode = TAF_PH_INFO_CDMA_1X_RAT;
            break;

        case TAF_SDC_SYS_MODE_EVDO:
            enSysMode = TAF_PH_INFO_HRPD_RAT;
            break;

        case TAF_SDC_SYS_MODE_HYBRID:
            enSysMode = TAF_PH_INFO_HYBRID_RAT;
            break;

        case TAF_SDC_SYS_MODE_SVLTE:
            enSysMode = TAF_PH_INFO_SVLTE_SRLTE_RAT;
            break;

        default:
            break;
    }

    return enSysMode;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTafAgentGetSysModeReq
 功能描述  : mta收到ID_TAFAGENT_MTA_GET_SYSMODE_REQ消息处理函数
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月1日
    作    者   : s00217060
    修改内容   : 主动上报AT命令控制下移至C核新增函数
  2.日    期   : 2014年11月29日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseI项目修改
  3.日    期   : 2015年11月17日
    作    者   : zwx247453
    修改内容   : dallas gps参考时钟虚焊检测

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTafAgentGetSysModeReq(VOS_VOID *pMsg)
{
    TAFAGENT_MTA_GET_SYSMODE_CNF_STRU          *pstGetSysModeCnf    = VOS_NULL_PTR;

    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8      enSysSubMode;

    /* 获取系统模式 */
    /* 1x CDMA无服务状态和注册状态延时上报,取当前的系统模式和系统子模式，3GPP时取AppNetworkInfo中的系统模式和系统子模式 */
    if (TAF_SDC_SYS_MODE_CDMA_1X == TAF_SDC_GetSysMode())
    {
        enSysMode    = TAF_SDC_SYS_MODE_CDMA_1X;
        enSysSubMode = TAF_SDC_SYS_SUBMODE_CDMA_1X;
    }
    else
    {
        enSysMode    = TAF_SDC_GetAppSysMode();
        enSysSubMode = TAF_SDC_GetAppSysSubMode();
    }


    pstGetSysModeCnf = (TAFAGENT_MTA_GET_SYSMODE_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA,
                                                              sizeof(TAFAGENT_MTA_GET_SYSMODE_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstGetSysModeCnf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvTafAgentGetSysModeReq:alloc msg failed.");
        return;
    }

    /* 消息头 */
    pstGetSysModeCnf->ulSenderCpuId                 = VOS_LOCAL_CPUID;
    pstGetSysModeCnf->ulSenderPid                   = UEPS_PID_MTA;
    pstGetSysModeCnf->ulReceiverCpuId               = VOS_LOCAL_CPUID;
    pstGetSysModeCnf->ulReceiverPid                 = ACPU_PID_TAFAGENT;

    /* 消息内容 */
    pstGetSysModeCnf->enMsgId                 = ID_TAFAGENT_MTA_GET_SYSMODE_CNF;
    pstGetSysModeCnf->ulRet                   = VOS_OK;
    pstGetSysModeCnf->stSysMode.enSysSubMode  = enSysSubMode;

    pstGetSysModeCnf->stSysMode.enRatType = TAF_MTA_SysModeTransfer(enSysMode);

    /* 给TAFAGENT发送查询回复 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstGetSysModeCnf))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvTafAgentGetSysModeReq:send msg failed.");

        return;
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MTA_SndStkCurcRptCfgInfoInd
 功能描述  : mta给STK发送CURC设置消息函数
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月1日
    作    者   : s00217060
    修改内容   : 主动上报AT命令控制下移至C核新增函数

*****************************************************************************/
VOS_VOID TAF_MTA_SndStkCurcRptCfgInfoInd(AT_MTA_CURC_SET_NOTIFY_STRU *pMsg)
{
    TAF_STK_CURC_RPT_CFG_INFO_MSG_STRU          *pstStkCurcRptInfo  = VOS_NULL_PTR;

    /* 分配内存 */
    pstStkCurcRptInfo = (TAF_STK_CURC_RPT_CFG_INFO_MSG_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA,
                                                              sizeof(TAF_STK_CURC_RPT_CFG_INFO_MSG_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 内存分配异常处理 */
    if (VOS_NULL_PTR == pstStkCurcRptInfo)
    {
        MTA_WARNING_LOG("TAF_MTA_SndStkCurcRptCfgInfoInd:alloc msg failed.");
        return;
    }

    /* 填写新消息内容 */
    pstStkCurcRptInfo->ulSenderPid      = UEPS_PID_MTA;
    pstStkCurcRptInfo->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstStkCurcRptInfo->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstStkCurcRptInfo->ulReceiverPid    = MAPS_STK_PID;
    pstStkCurcRptInfo->ulMsgId          = TAF_STK_CURC_RPT_CFG_INFO_IND;
    PS_MEM_CPY(pstStkCurcRptInfo->aucCurcRptCfg,
               pMsg->aucRptCfg,
               sizeof(pstStkCurcRptInfo->aucCurcRptCfg));

    /* 发送消息异常处理 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstStkCurcRptInfo))
    {
        MTA_WARNING_LOG("TAF_MTA_SndStkCurcRptCfgInfoInd: PS_SEND_MSG ERROR");
        return;
    }

    return;
}

/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-1, end */
#ifdef DMT
/*****************************************************************************
 函 数 名  : DMT_GetSysMode
 功能描述  : DMT桩函数，用于A核获取接入模式
 输入参数  : 无
 输出参数  : TAF_AGENT_SYS_MODE_STRU *pstSysMode -- 系统当前接入模式
 返 回 值  : VOS_OK  获取成功
             VOS_ERR 获取失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年05月21日
    作    者   : l00198894
    修改内容   : TAF&SM接口优化项目新增函数

*****************************************************************************/
VOS_UINT32 DMT_GetSysMode(TAF_AGENT_SYS_MODE_STRU *pstSysMode)
{
    TAF_SDC_SYS_INFO_STRU                 *pst3gppSysInfo     = VOS_NULL_PTR;

    /* 获取系统模式 */
    pst3gppSysInfo   = TAF_SDC_GetSysInfo();

    pstSysMode->enSysSubMode  = pst3gppSysInfo->enSysSubMode;
    pstSysMode->enRatType     = TAF_MTA_SysModeTransfer(pst3gppSysInfo->enSysMode);

    return VOS_OK;
}
#endif

/*lint +e958*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

