

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "RnicCtx.h"
#include "RnicProcMsg.h"
#include "AtRnicInterface.h"
#include "v_typdef.h"
#include "RnicTimerMgmt.h"
#include "mdrv.h"
#include "RnicEntity.h"
#include "AdsDeviceInterface.h"
#include "RnicLog.h"
#include "PsTypeDef.h"
#include "PsCommonDef.h"
#include "RnicDebug.h"

#include "AcpuReset.h"

#include "ImsaRnicInterface.h"

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
#include "SdioInterface.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_RNIC_PROCMSG_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* RNIC模块定时器超时消息处理函数对应表 */
const RNIC_RCV_TI_EXPRIED_PROC_STRU g_astRnicTiExpriedProcTab[]=
{
    /* 消息ID */                            /* 定时器超时处理函数 */
    {TI_RNIC_DSFLOW_STATS_0,                RNIC_RcvTiDsflowStatsExpired},
    {TI_RNIC_DSFLOW_STATS_1,                RNIC_RcvTiDsflowStatsExpired},
    {TI_RNIC_DSFLOW_STATS_2,                RNIC_RcvTiDsflowStatsExpired},
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    {TI_RNIC_DSFLOW_STATS_3,                RNIC_RcvTiDsflowStatsExpired},
    {TI_RNIC_DSFLOW_STATS_4,                RNIC_RcvTiDsflowStatsExpired},
#if  (MULTI_MODEM_NUMBER == 3)
    {TI_RNIC_DSFLOW_STATS_5,                RNIC_RcvTiDsflowStatsExpired},
    {TI_RNIC_DSFLOW_STATS_6,                RNIC_RcvTiDsflowStatsExpired},
#endif /* #if (MULTI_MODEM_NUMBER == 3) */
#endif
    {TI_RNIC_DEMAND_DIAL_DISCONNECT,        RNIC_RcvTiDemandDialDisconnectExpired},
    {TI_RNIC_DEMAND_DIAL_PROTECT,           RNIC_RcvTiDemandDialProtectExpired}
 };

/* Deleted by wx270776 for OM融合, 2015-08-21, Begin */
/* Deleted by wx270776 for OM融合, 2012-08-21, End */

/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : RNIC_MNTN_TraceDialConnEvt
 功能描述  : 可维可测钩包: 输出拨号连接事件
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月6日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2012年6月18日
    作    者   : A00165503
    修改内容   : DTS2012061800997: 修改按需拨号可维可测钩包方式
  3.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
VOS_VOID RNIC_MNTN_TraceDialConnEvt(VOS_VOID)
{
    RNIC_MNTN_DIAL_CONN_EVT_STRU       *pstDialEvt = VOS_NULL_PTR;

    /* 构造消息 */
    pstDialEvt = (RNIC_MNTN_DIAL_CONN_EVT_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        ACPU_PID_RNIC,
                        sizeof(RNIC_MNTN_DIAL_CONN_EVT_STRU));
    if (VOS_NULL_PTR == pstDialEvt)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_MNTN_TraceDialEvent: Memory alloc failed.");
        return;
    }

    /* 填写消息 */
    pstDialEvt->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstDialEvt->ulReceiverPid   = ACPU_PID_RNIC;
    pstDialEvt->enMsgId         = ID_RNIC_MNTN_EVT_DIAL_CONNECT;

    /* 钩出可维可测消息 */
    if (VOS_OK != PS_SEND_MSG(ACPU_PID_RNIC, pstDialEvt))
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_MNTN_TraceDialConnEvt():WARNING:SEND MSG FIAL");
    }

    return;
}

/*****************************************************************************
 函 数 名  : RNIC_MNTN_TraceDialDisconnEvt
 功能描述  : 可维可测钩包: 输出拨号断开事件
 输入参数  : ulPktNum      - 拨号断开时收到的数据包个数
             ulUsrExistFlg - 用户连接状态(USB或者WIFI)
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月6日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2012年6月18日
    作    者   : A00165503
    修改内容   : DTS2012061800997: 修改按需拨号可维可测钩包方式
  3.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
VOS_VOID RNIC_MNTN_TraceDialDisconnEvt(
    VOS_UINT32                          ulPktNum,
    VOS_UINT32                          ulUsrExistFlg
)
{
    RNIC_MNTN_DIAL_DISCONN_EVT_STRU    *pstDialEvt = VOS_NULL_PTR;

    /* 构造消息 */
    pstDialEvt = (RNIC_MNTN_DIAL_DISCONN_EVT_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        ACPU_PID_RNIC,
                        sizeof(RNIC_MNTN_DIAL_DISCONN_EVT_STRU));
    if (VOS_NULL_PTR == pstDialEvt)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_MNTN_TraceDialEvent: Memory alloc failed.");
        return;
    }

    /* 填写消息头 */
    pstDialEvt->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstDialEvt->ulReceiverPid   = ACPU_PID_RNIC;
    pstDialEvt->enMsgId         = ID_RNIC_MNTN_EVT_DIAL_DISCONNECT;

    /* 填写消息内容 */
    pstDialEvt->ulPktNum        = ulPktNum;
    pstDialEvt->ulUsrExistFlg   = ulUsrExistFlg;

    /* 钩出可维可测消息 */
    if (VOS_OK != PS_SEND_MSG(ACPU_PID_RNIC, pstDialEvt))
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_MNTN_TraceDialDisconnEvt():WARNING:SEND MSG FIAL");
    }

    return;
}

/*****************************************************************************
 函 数 名  : RNIC_SendDialInfoMsg
 功能描述  : RNIC发送给自己的拨号模式信息用于可维可测
 输入参数  : RNIC_DEMAND_DIAL_INFO_MSG_ID_ENUM_UINT32                enMsgId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月1日
    作    者   : w00199382
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 RNIC_SendDialInfoMsg(
    RNIC_MSG_ID_ENUM_UINT32            enMsgId
)
{
    RNIC_NOTIFY_MSG_STRU               *pstDialInfo;
    RNIC_DIAL_MODE_STRU                *pstDialMode;


    /* 内存分配 */
    pstDialInfo = (RNIC_NOTIFY_MSG_STRU *)PS_ALLOC_MSG(ACPU_PID_RNIC,
                                                      sizeof(RNIC_NOTIFY_MSG_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstDialInfo)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_SendDialInfoMsg: Malloc failed!");
        return VOS_ERR;
    }

    pstDialMode                         = RNIC_GetDialModeAddr();

    /* 填充消息 */
    pstDialInfo->ulSenderCpuId          = VOS_LOCAL_CPUID;
    pstDialInfo->ulSenderPid            = ACPU_PID_RNIC;
    pstDialInfo->ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstDialInfo->ulReceiverPid          = ACPU_PID_RNIC;
    pstDialInfo->enMsgId                = enMsgId;

    PS_MEM_CPY(&(pstDialInfo->stDialInfo), pstDialMode, sizeof(RNIC_DIAL_MODE_STRU));

    if (VOS_OK != PS_SEND_MSG(ACPU_PID_RNIC, pstDialInfo))
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_SendDialInfoMsg: Send msg failed!");
        return VOS_ERR;
    }

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : RNIC_SendDialEvent
 功能描述  : RNIC通过netlink通知APP拨号或断开
 输入参数  : ulDeviceId :设备号
             ulEventId  :事件ID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月13日
   作    者   : S62952
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 RNIC_SendDialEvent(
    VOS_UINT32                          ulDeviceId,
    VOS_UINT32                          ulEventId
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulSize;
    DEVICE_EVENT                        stEvent;

    ulSize                              = sizeof(DEVICE_EVENT);
    stEvent.device_id                   = (DEVICE_ID)ulDeviceId;
    stEvent.event_code                  = (VOS_INT)ulEventId;
    stEvent.len                         = 0;

    /* 上报按需拨号事件*/
    ulRet = (VOS_UINT32)device_event_report(&stEvent, (VOS_INT)ulSize);

    if (VOS_OK != ulRet)
    {
        RNIC_WARNING_LOG(ACPU_PID_RNIC, "RNIC_SendDialEvent: can't add event");
        return VOS_ERR;
    }

    RNIC_INFO_LOG2(ACPU_PID_RNIC, "RNIC_SendDialEvent Done ulEventId  ulDeviceId",ulEventId,ulDeviceId);

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : RNIC_GetDsflowTimerIdByNetId
 功能描述  : 通过网卡ID得到流量统计定时器ID
 输入参数  : ucRmNetId :网卡ID
 输出参数  : 无
 返 回 值  : RNIC_TIMER_ID_ENUM_UINT16 定时器ID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月28日
    作    者   : f00179208
    修改内容   : 新生成函数

  2.日    期   : 2015年5月27日
    作    者   : l00198894
    修改内容   : TSTS
*****************************************************************************/
RNIC_TIMER_ID_ENUM_UINT16 RNIC_GetDsflowTimerIdByNetId(VOS_UINT8 ucRmNetId)
{
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId;

    switch (ucRmNetId)
    {
        case RNIC_RMNET_ID_0 :
            enTimerId = TI_RNIC_DSFLOW_STATS_0;
            break;

        case RNIC_RMNET_ID_1 :
            enTimerId = TI_RNIC_DSFLOW_STATS_1;
            break;

        case RNIC_RMNET_ID_2 :
            enTimerId = TI_RNIC_DSFLOW_STATS_2;
            break;

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
        case RNIC_RMNET_ID_3 :
            enTimerId = TI_RNIC_DSFLOW_STATS_3;
            break;

        case RNIC_RMNET_ID_4 :
            enTimerId = TI_RNIC_DSFLOW_STATS_4;
            break;
#if (MULTI_MODEM_NUMBER == 3)
        case RNIC_RMNET_ID_5 :
            enTimerId = TI_RNIC_DSFLOW_STATS_5;
            break;

        case RNIC_RMNET_ID_6 :
            enTimerId = TI_RNIC_DSFLOW_STATS_6;
            break;
#endif
#endif

        default :
            enTimerId = TI_RNIC_TIMER_BUTT;
            break;
    }

    return enTimerId;
}

/*****************************************************************************
 函 数 名  : RNIC_GetNetIdByTimerId
 功能描述  : 根据定时器ID获取网卡ID
 输入参数  : ucRmNetId :网卡ID
 输出参数  : 无
 返 回 值  : VOS_UINT8 网卡ID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月28日
    作    者   : f00179208
    修改内容   : 新生成函数

  2.日    期   : 2015年5月27日
    作    者   : l00198894
    修改内容   : TSTS
*****************************************************************************/
VOS_UINT8 RNIC_GetNetIdByTimerId(VOS_UINT32 ulMsgId)
{
    VOS_UINT8                           ucRmNedId;

    switch (ulMsgId)
    {
        case TI_RNIC_DSFLOW_STATS_0 :
            ucRmNedId = RNIC_RMNET_ID_0;
            break;

        case TI_RNIC_DSFLOW_STATS_1 :
            ucRmNedId = RNIC_RMNET_ID_1;
            break;

        case TI_RNIC_DSFLOW_STATS_2 :
            ucRmNedId = RNIC_RMNET_ID_2;
            break;

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
        case TI_RNIC_DSFLOW_STATS_3 :
            ucRmNedId = RNIC_RMNET_ID_3;
            break;

        case TI_RNIC_DSFLOW_STATS_4 :
            ucRmNedId = RNIC_RMNET_ID_4;
            break;
#if  (MULTI_MODEM_NUMBER == 3)
        case TI_RNIC_DSFLOW_STATS_5 :
            ucRmNedId = RNIC_RMNET_ID_5;
            break;

        case TI_RNIC_DSFLOW_STATS_6 :
            ucRmNedId = RNIC_RMNET_ID_6;
            break;
#endif /* #if (MULTI_MODEM_NUMBER == 3) */
#endif

        case TI_RNIC_DEMAND_DIAL_DISCONNECT :
        case TI_RNIC_DEMAND_DIAL_PROTECT :
            ucRmNedId = RNIC_RMNET_ID_0;
            break;

        default :
            ucRmNedId = RNIC_RMNET_ID_BUTT;
            break;
    }

    return ucRmNedId;
}

/*****************************************************************************
 函 数 名  : RNIC_BuildRabIdByModemId
 功能描述  : 根据ModemId生成Rabid
 输入参数  : enModemId : Modem ID
             ucRabId   : RabId
 输出参数  : pucRabId  : 生成的RabId
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月06日
    作    者   : f00179208
    修改内容   : 新生成函数

  2.日    期   : 2015年5月28日
    作    者   : l00198894
    修改内容   : TSTS
*****************************************************************************/
VOS_UINT32 RNIC_BuildRabIdByModemId(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucRabId,
    VOS_UINT8                          *pucRabId
)
{
    if (MODEM_ID_0 == enModemId)
    {
        /* Modem0的RABID的高两位用00表示 */
        *pucRabId = ucRabId;
    }
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    else if (MODEM_ID_1 == enModemId)
    {
        /* Modem1的RABID的高两位用01表示 */
        *pucRabId = ucRabId | RNIC_RABID_TAKE_MODEM_1_MASK;
    }
    else if (MODEM_ID_2 == enModemId)
    {
        /* Modem2的RABID的高两位用10表示 */
        *pucRabId = ucRabId | RNIC_RABID_TAKE_MODEM_2_MASK;
    }
#endif
    else
    {
        /* 既不是Modem0也不是Modem1的，返回失败 */
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : RNIC_SaveNetIdByRabId
 功能描述  : 根据rabid存储网卡ID
 输入参数  : enModemId : Modem ID
             ucRmNetId : 网卡ID
             ucRabId   : RabId
 输出参数  :
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年12月10日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 RNIC_SaveNetIdByRabId(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucRabId,
    VOS_UINT8                           ucRmNetId
)
{
    RNIC_RABID_INFO_STAU               *pstRabIdInfo;

    if ((ucRabId < RNIC_RAB_ID_MIN)
     || (ucRabId > RNIC_RAB_ID_MAX))
    {
        return VOS_ERR;
    }

    /* 获取指定Modem的RABID信息 */
    pstRabIdInfo = RNIC_GET_SPEC_MODEM_RABID_INFO(enModemId);

    pstRabIdInfo->aucRmNetId[ucRabId - RNIC_RAB_ID_OFFSET] = ucRmNetId;

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : RNIC_RcvIpv4PdpActInd
 功能描述  : RNIC收到AT消息ID_AT_RNIC_IPV4_PDP_ACT_IND的处理
 输入参数  : pMsg:消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月06日
   作    者   : f00179208
   修改内容   : 新生成函数
 2.日    期   : 2012年1月31日
   作    者   : w00199382
   修改内容   : 拨号保护定时器超时删除
 3.日    期   : 2012年6月6日
   作    者   : A00165503
   修改内容   : DTS2012060502819: 灌包方式触发按需拨号, 导致频繁上报事件
 4.日    期   : 2012年11月23日
   作    者   : f00179208
   修改内容   : DSDA Phase I: RNIC多实例

 5.日    期   : 2014年11月7日
   作    者   : y00218312
   修改内容   : 增加CDMA模式下的处理
*****************************************************************************/
VOS_UINT32 RNIC_RcvAtIpv4PdpActInd(
    MsgBlock                           *pstMsg
)
{
    AT_RNIC_IPV4_PDP_ACT_IND_STRU      *pstRcvInd;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           ucRabid;
    VOS_UINT8                           ucRmNetId;

    pstRcvInd                           = (AT_RNIC_IPV4_PDP_ACT_IND_STRU *)pstMsg;
    ucRmNetId                           = pstRcvInd->ucRmNetId;

    /* 获取PDP上下文地址 */
    pstPdpAddr                          = RNIC_GetPdpCtxAddr(ucRmNetId);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);

    ucRabid                             = RNIC_RAB_ID_INVALID;

    /* 根据modem id和网卡id，填充Rabid */
    if (VOS_OK != RNIC_BuildRabIdByModemId(pstSpecNetCardCtx->enModemId,
                                           pstRcvInd->ucRabId,
                                           &ucRabid))
    {
        RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_RcvAtIpv4PdpActInd, modemId:%d", pstSpecNetCardCtx->enModemId);
        return VOS_ERR;
    }

    /* 存储RABID对应的网卡ID */
    if (VOS_OK != RNIC_SaveNetIdByRabId(pstSpecNetCardCtx->enModemId,
                                        pstRcvInd->ucRabId,
                                        ucRmNetId))
    {
        RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_RcvAtIpv4PdpActInd, RabId:%d", pstRcvInd->ucRabId);
        return VOS_ERR;
    }

    /* Modified by l60609 for L-C互操作项目, 2014-1-14, begin */
    pstSpecNetCardCtx->enModemType        = RNIC_MODEM_TYPE_INSIDE;
    /* Modified by l60609 for L-C互操作项目, 2014-1-14, end */

    /* 更新PDP上下文信息 */
    pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4PdpInfo.ucRabId     = pstRcvInd->ucRabId;
    pstPdpAddr->stIpv4PdpInfo.ulIpv4Addr  = pstRcvInd->ulIpv4Addr;



    /* 根据网卡ID获取流量统计的定时器ID */
    enTimerId = RNIC_GetDsflowTimerIdByNetId(ucRmNetId);

    /* 启动流量统计定时器 */
    RNIC_StartTimer(enTimerId, TI_RNIC_DSFLOW_STATS_LEN);

    /* 停止按需拨号保护定时器 */
    if (RNIC_RMNET_ID_0 == ucRmNetId)
    {
        RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_PROTECT);
    }


    /* 注册下行发送函数，ADS调用注册的函数发送下行数据 */
    ADS_DL_RegDlDataCallback(ucRabid, RNIC_RcvAdsDlData, ucRmNetId);


    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : RNIC_RcvIpv6PdpActInd
 功能描述  : RNIC收到AT消息ID_AT_RNIC_IPV6_PDP_ACT_IND的处理
 输入参数  : pMsg:消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_OK
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年12月06日
   作    者   : f00179208
   修改内容   : 新生成函数
 2.日    期   : 2012年11月23日
   作    者   : f00179208
   修改内容   : DSDA Phase I: RNIC多实例
 3.日    期   : 2015年1月22日
   作    者   : Y00213812
   修改内容   : 增加CDMA模式下PPP在ACUP时的处理
*****************************************************************************/
VOS_UINT32 RNIC_RcvAtIpv6PdpActInd(
    MsgBlock                           *pstMsg
)
{
    AT_RNIC_IPV6_PDP_ACT_IND_STRU      *pstRcvInd;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           ucRabid;
    VOS_UINT8                           ucRmNetId;

    pstRcvInd                           = (AT_RNIC_IPV6_PDP_ACT_IND_STRU *)pstMsg;
    ucRmNetId                           = pstRcvInd->ucRmNetId;

    /* 获取PDP上下文地址 */
    pstPdpAddr                          = RNIC_GetPdpCtxAddr(ucRmNetId);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);

    ucRabid                             = RNIC_RAB_ID_INVALID;

    /* 根据modem id和网卡id，填充Rabid */
    if (VOS_OK != RNIC_BuildRabIdByModemId(pstSpecNetCardCtx->enModemId,
                                           pstRcvInd->ucRabId,
                                           &ucRabid))
    {
        RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_RcvAtIpv6PdpActInd, modemId:%d", pstSpecNetCardCtx->enModemId);
        return VOS_ERR;
    }

    /* 存储RABID对应的网卡ID */
    if (VOS_OK != RNIC_SaveNetIdByRabId(pstSpecNetCardCtx->enModemId,
                                        pstRcvInd->ucRabId,
                                        ucRmNetId))
    {
        RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_RcvAtIpv6PdpActInd, RabId:%d", pstRcvInd->ucRabId);
        return VOS_ERR;
    }

    /* Modified by l60609 for L-C互操作项目, 2014-1-14, begin */
    pstSpecNetCardCtx->enModemType        = RNIC_MODEM_TYPE_INSIDE;
    /* Modified by l60609 for L-C互操作项目, 2014-1-14, end */

    /* 更新PDP上下文信息 */
    pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv6PdpInfo.ucRabId     = pstRcvInd->ucRabId;
    VOS_MemCpy(pstPdpAddr->stIpv6PdpInfo.aucIpv6Addr,
               pstRcvInd->aucIpv6Addr,
               RNICITF_MAX_IPV6_ADDR_LEN);


    /* 根据网卡ID获取流量统计的定时器ID */
    enTimerId = RNIC_GetDsflowTimerIdByNetId(ucRmNetId);

    /* 启动流量统计定时器 */
    RNIC_StartTimer(enTimerId, TI_RNIC_DSFLOW_STATS_LEN);

    /* 注册下行发送函数，ADS调用注册的函数发送下行数据 */


    ADS_DL_RegDlDataCallback(ucRabid, RNIC_RcvAdsDlData, ucRmNetId);



    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : RNIC_RcvIpvv46PdpActInd
 功能描述  : RNIC收到AT消息ID_AT_RNIC_IPV4V6_PDP_ACT_IND的处理
 输入参数  : pMsg:消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_OK
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年12月17日
   作    者   : f00179208
   修改内容   : 新生成函数
 2.日    期   : 2012年6月6日
   作    者   : A00165503
   修改内容   : DTS2012060502819: 灌包方式触发按需拨号, 导致频繁上报事件
 3.日    期   : 2012年11月23日
   作    者   : f00179208
   修改内容   : DSDA Phase I: RNIC多实例
 4.日    期   : 2015年1月22日
   作    者   : Y00213812
   修改内容   : 增加CDMA模式下PPP在ACUP时的处理

*****************************************************************************/
VOS_UINT32 RNIC_RcvAtIpv4v6PdpActInd(
    MsgBlock                           *pstMsg
)
{
    AT_RNIC_IPV4V6_PDP_ACT_IND_STRU    *pstRcvInd;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           ucRabid;
    VOS_UINT8                           ucRmNetId;

    pstRcvInd                           = (AT_RNIC_IPV4V6_PDP_ACT_IND_STRU *)pstMsg;
    ucRmNetId                           = pstRcvInd->ucRmNetId;

    /* 获取PDP上下文地址 */
    pstPdpAddr                          = RNIC_GetPdpCtxAddr(ucRmNetId);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);

    ucRabid                             = RNIC_RAB_ID_INVALID;

    /* 根据modem id和网卡id，填充Rabid */
    if (VOS_OK != RNIC_BuildRabIdByModemId(pstSpecNetCardCtx->enModemId,
                                           pstRcvInd->ucRabId,
                                           &ucRabid))
    {
        RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_RcvAtIpv4v6PdpActInd, modemId:%d", pstSpecNetCardCtx->enModemId);
        return VOS_ERR;
    }

    /* 存储RABID对应的网卡ID */
    if (VOS_OK != RNIC_SaveNetIdByRabId(pstSpecNetCardCtx->enModemId,
                                        pstRcvInd->ucRabId,
                                        ucRmNetId))
    {
        RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_RcvAtIpv4v6PdpActInd, modemId:%d", pstSpecNetCardCtx->enModemId);
        return VOS_ERR;
    }

    /* Modified by l60609 for L-C互操作项目, 2014-1-14, begin */
    pstSpecNetCardCtx->enModemType          = RNIC_MODEM_TYPE_INSIDE;
    /* Modified by l60609 for L-C互操作项目, 2014-1-14, end */

    /* 更新PDP上下文信息 */
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4v6PdpInfo.ucRabId     = pstRcvInd->ucRabId;
    pstPdpAddr->stIpv4PdpInfo.ucRabId       = pstRcvInd->ucRabId;
    pstPdpAddr->stIpv6PdpInfo.ucRabId       = pstRcvInd->ucRabId;



    /* 根据网卡ID获取流量统计的定时器ID */
    enTimerId = RNIC_GetDsflowTimerIdByNetId(ucRmNetId);

    /* 启动流量统计定时器 */
    RNIC_StartTimer(enTimerId, TI_RNIC_DSFLOW_STATS_LEN);

    /* 停止按需拨号保护定时器 */
    RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_PROTECT);


    /* 注册下行发送函数，ADS调用注册的函数发送下行数据 */
    ADS_DL_RegDlDataCallback(ucRabid, RNIC_RcvAdsDlData, ucRmNetId);


    return VOS_OK;

}


/*****************************************************************************
 函 数 名  : RNIC_RcvPdpDeactInd
 功能描述  : RNIC收到AT消息ID_AT_RNIC_PDP_DEACT_IND的处理
 输入参数  : pMsg:消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月06日
   作    者   : f00179208
   修改内容   : 新生成函数
 2.日    期   : 2012年6月16日
   作    者   : z60575
   修改内容   : DTS2012061502207: 上报按需断开时间时增加投票不睡眠，避免应用
                处理消息前又进入深睡
 3.日    期   : 2012年11月23日
   作    者   : f00179208
   修改内容   : DSDA Phase I: RNIC多实例
*****************************************************************************/
VOS_UINT32 RNIC_RcvAtPdpDeactInd(
    MsgBlock                           *pstMsg
)
{
    AT_RNIC_PDP_DEACT_IND_STRU         *pstRcvInd;
    RNIC_PDP_CTX_STRU                  *pstPdpCtxAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId;
    VOS_UINT8                           ucRmNetId;

    pstRcvInd                           = (AT_RNIC_PDP_DEACT_IND_STRU *)pstMsg;
    ucRmNetId                           = pstRcvInd->ucRmNetId;

    /* 获取PDP上下文地址 */
    pstPdpCtxAddr                       = RNIC_GetPdpCtxAddr(ucRmNetId);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);

    /* 根据网卡ID获取流量统计的定时器ID */
    enTimerId = RNIC_GetDsflowTimerIdByNetId(ucRmNetId);

    /* 如果是IPV4 PDP去激活 */
    if ((pstPdpCtxAddr->stIpv4PdpInfo.ucRabId == pstRcvInd->ucRabId)
     && (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtxAddr->stIpv4PdpInfo.enRegStatus))
    {
        /* 清空IPV4 PDP上下文信息 */
        RNIC_InitIpv4PdpCtx(&pstPdpCtxAddr->stIpv4PdpInfo);

        /* 在网卡0上才有按需拨号的功能 */
        if (RNIC_RMNET_ID_0 == ucRmNetId)
        {
            /* 停止按需拨号断开定时器 */
            RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT);

            /* 清空拨号断开定时器超时统计 */
            RNIC_ClearTiDialDownExpCount();
        }
    }

    if ((pstPdpCtxAddr->stIpv6PdpInfo.ucRabId == pstRcvInd->ucRabId)
     && (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtxAddr->stIpv6PdpInfo.enRegStatus))
    {
        /* 清空IPV6 PDP上下文信息 */
        RNIC_InitIpv6PdpCtx(&pstPdpCtxAddr->stIpv6PdpInfo);
    }

    if ((pstPdpCtxAddr->stIpv4v6PdpInfo.ucRabId == pstRcvInd->ucRabId)
     && (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtxAddr->stIpv4v6PdpInfo.enRegStatus))
    {
        /* 清空IPV4V6 PDP上下文信息 */
        RNIC_InitIpv4v6PdpCtx(&pstPdpCtxAddr->stIpv4v6PdpInfo, ucRmNetId);
    }

    /* PDP都未激活的时候 */
    if ((RNIC_PDP_REG_STATUS_ACTIVE != pstPdpCtxAddr->stIpv4PdpInfo.enRegStatus)
     && (RNIC_PDP_REG_STATUS_ACTIVE != pstPdpCtxAddr->stIpv6PdpInfo.enRegStatus)
     && (RNIC_PDP_REG_STATUS_ACTIVE != pstPdpCtxAddr->stIpv4v6PdpInfo.enRegStatus))
    {
        /* 停止流量统计定时器 */
        RNIC_StopTimer(enTimerId);

        /* 清除流量统计信息 */
        RNIC_ClearNetDsFlowStats(ucRmNetId);

        /* Modified by l60609 for L-C互操作项目, 2014-1-14, begin */
        pstSpecNetCardCtx->enModemType = RNIC_MODEM_TYPE_INSIDE;
        /* Modified by l60609 for L-C互操作项目, 2014-1-14, end */
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* 在断开拨号成功时解除投票睡眠，以便能进入深睡 */
    DRV_PWRCTRL_SLEEPVOTE_UNLOCK(PWRCTRL_SLEEP_RNIC);
#endif

    /* 清除RABID对应的网卡ID */
    if (VOS_OK != RNIC_SaveNetIdByRabId(pstSpecNetCardCtx->enModemId,
                                        pstRcvInd->ucRabId,
                                        RNIC_RMNET_ID_BUTT))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : RNIC_RcvAtDialModeReq
 功能描述  : RNIC收到AT消息ID_AT_RNIC_DIAL_MODE_REQ的处理
 输入参数  : pMsg:消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_OK
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年12月21日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 RNIC_RcvAtDialModeReq(
    MsgBlock                           *pstMsg
)
{
    AT_RNIC_DIAL_MODE_REQ_STRU         *pstRcvInd;
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    RNIC_AT_DIAL_MODE_CNF_STRU         *pstSndMsg;

    /* 内存分配 */
    pstSndMsg = (RNIC_AT_DIAL_MODE_CNF_STRU *)PS_ALLOC_MSG(ACPU_PID_RNIC,
                        sizeof(RNIC_AT_DIAL_MODE_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstSndMsg)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_RcvAtDialModeReq: Malloc failed!");
        return VOS_ERR;
    }

    pstRcvInd                           = (AT_RNIC_DIAL_MODE_REQ_STRU *)pstMsg;

    /* 获取按需拨号的模式以及时长的地址 */
    pstDialMode                         = RNIC_GetDialModeAddr();
    pstSndMsg->clientId                 = pstRcvInd->clientId;
    pstSndMsg->ulDialMode               = pstDialMode->enDialMode;
    pstSndMsg->ulIdleTime               = pstDialMode->ulIdleTime;
    pstSndMsg->ulEventReportFlag        = pstDialMode->enEventReportFlag;

    /* 通过ID_RNIC_AT_DIAL_MODE_CNF消息发送给AT模块 */
    /* 填充消息 */
    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = ACPU_PID_RNIC;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = WUEPS_PID_AT;
    pstSndMsg->enMsgId                  = ID_RNIC_AT_DIAL_MODE_CNF;

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(ACPU_PID_RNIC, pstSndMsg))
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_RcvAtDialModeReq: Send msg failed!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : RNIC_RcvDsflowInd
 功能描述  : RNIC收到AT消息ID_AT_RNIC_DSFLOW_IND的处理
 输入参数  : pMsg:消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32 VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月06日
   作    者   : f00179208
   修改内容   : 新生成函数
 2.日    期   : 2012年11月23日
   作    者   : f00179208
   修改内容   : DSDA Phase I: RNIC多实例
*****************************************************************************/
VOS_UINT32 RNIC_RcvAtDsflowInd(
    MsgBlock                           *pstMsg
)
{
    AT_RNIC_DSFLOW_IND_STRU            *pstRcvInd;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_AT_DSFLOW_RSP_STRU            *pstDsflowRsp;

    /* 内存分配 */
    pstDsflowRsp = (RNIC_AT_DSFLOW_RSP_STRU *)PS_ALLOC_MSG(ACPU_PID_RNIC,
                        sizeof(RNIC_AT_DSFLOW_RSP_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstDsflowRsp)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_RcvAtDsflowInd: Malloc failed!");
        return VOS_ERR;
    }

    pstRcvInd                               = (AT_RNIC_DSFLOW_IND_STRU *)pstMsg;
    pstDsflowRsp->clientId                  = pstRcvInd->clientId;

    pstPdpAddr                              = RNIC_GetPdpCtxAddr(pstRcvInd->enRnicRmNetId);

    /* 产品要求未拨上号，速率为0 */
    pstDsflowRsp->stRnicDataRate.ulDLDataRate = 0;
    pstDsflowRsp->stRnicDataRate.ulULDataRate = 0;

    /* PDP激活的时候，获取当前的上下行速率 */
    if ((RNIC_PDP_REG_STATUS_ACTIVE == pstPdpAddr->stIpv4PdpInfo.enRegStatus)
     || (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpAddr->stIpv6PdpInfo.enRegStatus)
     || (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpAddr->stIpv4v6PdpInfo.enRegStatus))
    {
        pstDsflowRsp->stRnicDataRate.ulDLDataRate = RNIC_GetCurrentDlRate(pstRcvInd->enRnicRmNetId);
        pstDsflowRsp->stRnicDataRate.ulULDataRate = RNIC_GetCurrentUlRate(pstRcvInd->enRnicRmNetId);
    }

    /* 通过ID_RNIC_AT_DSFLOW_RSP消息发送给AT模块 */
    /* 填充消息 */
    pstDsflowRsp->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstDsflowRsp->ulSenderPid                 = ACPU_PID_RNIC;
    pstDsflowRsp->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstDsflowRsp->ulReceiverPid               = WUEPS_PID_AT;
    pstDsflowRsp->enMsgId                     = ID_RNIC_AT_DSFLOW_RSP;

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(ACPU_PID_RNIC, pstDsflowRsp))
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_RcvAtDsflowInd: Send msg failed!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : RNIC_RcvAtPdnInfoCfgInd
 功能描述  : RNIC收到AT消息ID_AT_RNIC_PDN_INFO_CFG_IND的处理
 输入参数  : pMsg:消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32 VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : z00214637
    修改内容   : V3R3 Share-PDP项目新增
*****************************************************************************/
VOS_UINT32 RNIC_RcvAtPdnInfoCfgInd(
    MsgBlock                           *pstMsg
)
{
    AT_RNIC_PDN_INFO_CFG_IND_STRU      *pstRnicPdnCfgInd;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    ADS_FILTER_IP_ADDR_INFO_STRU        stFilterIpAddr;
    VOS_UINT8                           ucRabid;
    VOS_UINT8                           ucRmNetId;

    PS_MEM_SET(&stFilterIpAddr, 0, sizeof(ADS_FILTER_IP_ADDR_INFO_STRU));
    pstRnicPdnCfgInd = (AT_RNIC_PDN_INFO_CFG_IND_STRU *)pstMsg;
    ucRmNetId        = pstRnicPdnCfgInd->ucRmNetId;

    /* 获取PDP上下文地址 */
    pstPdpAddr                          = RNIC_GetPdpCtxAddr(ucRmNetId);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);
    ucRabid                             = RNIC_RAB_ID_INVALID;

    /* 根据modem id填充Rabid */
    if (VOS_OK != RNIC_BuildRabIdByModemId(pstSpecNetCardCtx->enModemId,
                                           pstRnicPdnCfgInd->ucRabId,
                                           &ucRabid))
    {
        RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_RcvAtPdnInfoCfgInd, modemId:%d", pstSpecNetCardCtx->enModemId);
        return VOS_ERR;
    }

    /* 存储RABID对应的网卡ID */
    if (VOS_OK != RNIC_SaveNetIdByRabId(pstSpecNetCardCtx->enModemId,
                                        pstRnicPdnCfgInd->ucRabId,
                                        ucRmNetId))
    {
        RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_RcvAtPdnInfoCfgInd, RabId:%d", pstRnicPdnCfgInd->ucRabId);
        return VOS_ERR;
    }

    /* Modified by l60609 for L-C互操作项目, 2014-1-14, begin */
    pstSpecNetCardCtx->enModemType        = RNIC_MODEM_TYPE_INSIDE;
    /* Modified by l60609 for L-C互操作项目, 2014-1-14, end */

    if (VOS_TRUE == pstRnicPdnCfgInd->bitOpIpv4PdnInfo)
    {
        /* 更新PDP上下文信息 */
        pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
        pstPdpAddr->stIpv4PdpInfo.ucRabId     = pstRnicPdnCfgInd->ucRabId;
        pstPdpAddr->stIpv4PdpInfo.ulIpv4Addr  = pstRnicPdnCfgInd->stIpv4PdnInfo.ulPdnAddr;

        /* 更新过滤IP地址信息 */
        stFilterIpAddr.bitOpIpv4Addr          = VOS_TRUE;
        PS_MEM_CPY(stFilterIpAddr.aucIpv4Addr,
                   (VOS_UINT8 *)&pstRnicPdnCfgInd->stIpv4PdnInfo.ulPdnAddr,
                   ADS_IPV4_ADDR_LEN);
    }

    if (VOS_TRUE == pstRnicPdnCfgInd->bitOpIpv6PdnInfo)
    {
        /* 更新PDP上下文信息 */
        pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
        pstPdpAddr->stIpv6PdpInfo.ucRabId     = pstRnicPdnCfgInd->ucRabId;
        PS_MEM_CPY(pstPdpAddr->stIpv6PdpInfo.aucIpv6Addr,
                   pstRnicPdnCfgInd->stIpv6PdnInfo.aucPdnAddr,
                   RNICITF_MAX_IPV6_ADDR_LEN);

        /* 更新过滤IP地址信息 */
        stFilterIpAddr.bitOpIpv6Addr          = VOS_TRUE;
        PS_MEM_CPY(stFilterIpAddr.aucIpv6Addr,
                   pstRnicPdnCfgInd->stIpv6PdnInfo.aucPdnAddr,
                   ADS_IPV6_ADDR_LEN);
    }

    /* 根据网卡ID获取流量统计的定时器ID */
    enTimerId = RNIC_GetDsflowTimerIdByNetId(ucRmNetId);

    /* 启动流量统计定时器 */
    RNIC_StartTimer(enTimerId, TI_RNIC_DSFLOW_STATS_LEN);

    /* 注册下行过滤回调函数，ADS调用注册的函数发送下行数据 */
    ADS_DL_RegFilterDataCallback(ucRabid, &stFilterIpAddr, (RCV_DL_DATA_FUNC)RNIC_RcvAdsDlData);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : RNIC_RcvAtPdnInfoRelInd
 功能描述  : RNIC收到AT消息ID_AT_RNIC_PDN_INFO_REL_REQ的处理
 输入参数  : pMsg:消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32 VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : z00214637
    修改内容   : V3R3 Share-PDP项目新增
*****************************************************************************/
VOS_UINT32 RNIC_RcvAtPdnInfoRelInd(
    MsgBlock                           *pstMsg
)
{
    AT_RNIC_PDN_INFO_REL_IND_STRU      *pstRnicPdnRelInd;
    RNIC_PDP_CTX_STRU                  *pstPdpCtxAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId;
    VOS_UINT8                           ucRmNetId;

    pstRnicPdnRelInd = (AT_RNIC_PDN_INFO_REL_IND_STRU *)pstMsg;

    ucRmNetId                           = pstRnicPdnRelInd->ucRmNetId;

    /* 获取PDP上下文地址 */
    pstPdpCtxAddr                       = RNIC_GetPdpCtxAddr(ucRmNetId);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);

    /* 根据网卡ID获取流量统计的定时器ID */
    enTimerId = RNIC_GetDsflowTimerIdByNetId(ucRmNetId);

    /* 更新PDP上下文信息 */
    if ((pstPdpCtxAddr->stIpv4PdpInfo.ucRabId == pstRnicPdnRelInd->ucRabId)
     && (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtxAddr->stIpv4PdpInfo.enRegStatus))
    {
        /* 清空IPV4 PDP上下文信息 */
        RNIC_InitIpv4PdpCtx(&pstPdpCtxAddr->stIpv4PdpInfo);
    }

    if ((pstPdpCtxAddr->stIpv6PdpInfo.ucRabId == pstRnicPdnRelInd->ucRabId)
     && (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtxAddr->stIpv6PdpInfo.enRegStatus))
    {
        /* 清空IPV6 PDP上下文信息 */
        RNIC_InitIpv6PdpCtx(&pstPdpCtxAddr->stIpv6PdpInfo);
    }

    if ((pstPdpCtxAddr->stIpv4v6PdpInfo.ucRabId == pstRnicPdnRelInd->ucRabId)
     && (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtxAddr->stIpv4v6PdpInfo.enRegStatus))
    {
        /* 清空IPV4V6 PDP上下文信息 */
        RNIC_InitIpv4v6PdpCtx(&pstPdpCtxAddr->stIpv4v6PdpInfo, ucRmNetId);
    }

    /* PDP都未激活的时候 */
    if ((RNIC_PDP_REG_STATUS_ACTIVE != pstPdpCtxAddr->stIpv4PdpInfo.enRegStatus)
     && (RNIC_PDP_REG_STATUS_ACTIVE != pstPdpCtxAddr->stIpv6PdpInfo.enRegStatus)
     && (RNIC_PDP_REG_STATUS_ACTIVE != pstPdpCtxAddr->stIpv4v6PdpInfo.enRegStatus))
    {
        /* 停止流量统计定时器 */
        RNIC_StopTimer(enTimerId);

        /* Modified by l60609 for L-C互操作项目, 2014-1-14, begin */
        pstSpecNetCardCtx->enModemType        = RNIC_MODEM_TYPE_INSIDE;
        /* Modified by l60609 for L-C互操作项目, 2014-1-14, end */

        /* 清除流量统计信息 */
        RNIC_ClearNetDsFlowStats(ucRmNetId);
    }

    /* 清除RABID对应的网卡ID */
    if (VOS_OK != RNIC_SaveNetIdByRabId(pstSpecNetCardCtx->enModemId,
                                        pstRnicPdnRelInd->ucRabId,
                                        RNIC_RMNET_ID_BUTT))
    {
        return VOS_ERR;
    }

    /* 去注册下行过滤回调函数 */
    ADS_DL_DeregFilterDataCallback(pstRnicPdnRelInd->ucRabId);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : RNIC_RcvTiAppDsflowExpired
 功能描述  : 流量统计定时器超时处理，计算RNIC数传中当前的速率
 输入参数  : pstMsg:定时器消息首地址
             enRmNetId:网卡ID
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_OK
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年12月06日
   作    者   : f00179208
   修改内容   : 新生成函数
 2.日    期   : 2012年3月02日
   作    者   : f00179208
   修改内容   : 问题单;DTS2012032406513,数传过程中，查询流量为0
 3.日    期   : 2012年11月23日
   作    者   : f00179208
   修改内容   : DSDA Phase I: RNIC多实例
*****************************************************************************/
VOS_UINT32  RNIC_RcvTiDsflowStatsExpired(
    MsgBlock                           *pstMsg,
    VOS_UINT8                           ucRmNetId
)
{
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt = VOS_NULL_PTR;
    VOS_UINT32                          ulTaBytes;
    VOS_UINT32                          ulRate;
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId;

    /* 获取上下文地址 */
    pstNetCntxt = RNIC_GET_SPEC_NET_CTX(ucRmNetId);

    /* 根据网卡ID获取流量统计的定时器ID */
    enTimerId   = RNIC_GetDsflowTimerIdByNetId(ucRmNetId);

    /* Added by f00179208 for DTS2012032406513，2012-03-24 Begin */
    RNIC_StopTimer(enTimerId);
    /* Added by f00179208 for DTS2012032406513，2012-03-24 End */

    /* 获取2秒的下行流量 */
    ulTaBytes   = pstNetCntxt->stDsFlowStats.ulTotalRecvFluxLow;

    /* 产品要求每2秒钟计算一次,单位为:byte/s */
    ulRate = ulTaBytes>>1;
    RNIC_SetCurrentDlRate(ulRate, ucRmNetId);

    /* 获取2秒的上行流量 */
    ulTaBytes   = pstNetCntxt->stDsFlowStats.ulTotalSendFluxLow;

    /* 产品要求每2秒钟计算一次,单位为:byte/s */
    ulRate      = ulTaBytes>>1;
    RNIC_SetCurrentUlRate(ulRate, ucRmNetId);

    /* 每个流量统计周期结束后，需要将周期统计Byte数清除 */
    pstNetCntxt->stDsFlowStats.ulTotalRecvFluxLow = 0;
    pstNetCntxt->stDsFlowStats.ulTotalSendFluxLow = 0;

    RNIC_StartTimer(enTimerId, TI_RNIC_DSFLOW_STATS_LEN);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : RNIC_RcvTiAppDemandDialDownExpired
 功能描述  : 拨号断开定时器超时处理，通知应用断开拨号
 输入参数  : pstMsg:定时器消息首地址
             enRmNetId - 网卡ID
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_OK
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年12月06日
   作    者   : f00179208
   修改内容   : 新生成函数
 2.日    期   : 2012年3月02日
   作    者   : w00199382
   修改内容   : DTS201203025734
 3.日    期   : 2012年6月6日
   作    者   : A00165503
   修改内容   : DTS2012060502819: 灌包方式触发按需拨号, 导致频繁上报事件
 4.日    期   : 2012年6月15日
   作    者   : z60575
   修改内容   : DTS2012061502207: 上报按需断开时间时增加投票不睡眠，避免应用
                处理消息前又进入深睡
 5.日    期   : 2012年11月23日
   作    者   : f00179208
   修改内容   : DSDA Phase I: RNIC多实例
*****************************************************************************/
VOS_UINT32 RNIC_RcvTiDemandDialDisconnectExpired(
    MsgBlock                           *pstMsg,
    VOS_UINT8                           ucRmNetId
)
{
    RNIC_DIAL_MODE_STRU                *pstDialMode = VOS_NULL_PTR;
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt = VOS_NULL_PTR;
    VOS_UINT32                          ulPktsNum;
    VOS_UINT32                          ulCount;
    VOS_UINT32                          ulUserExistFlg;
    VOS_UINT32                          ulExpiredCount;

    /* 获取上下文地址 */
    pstNetCntxt     = RNIC_GET_SPEC_NET_CTX(ucRmNetId);

    /* 获取按需拨号的模式以及时长的地址 */
    pstDialMode     = RNIC_GetDialModeAddr();

    /* 将用户设置的时长按定时器时长等分 */
    ulExpiredCount  = (pstDialMode->ulIdleTime * TI_RNIC_UNIT) / TI_RNIC_DEMAND_DIAL_DISCONNECT_LEN;

    /* Added by w00199382 for DTS201203025734，2012-03-02,  Begin */
    RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT);
    /* Added by w00199382 for DTS201203025734，2012-03-02,  End */

    /* 如果当前是手动拨号,则直接返回,不需要通知 */
    if (RNIC_DIAL_MODE_DEMAND_CONNECT != pstDialMode->enDialMode)
    {
        RNIC_NORMAL_LOG(ACPU_PID_RNIC, "RNIC_RcvTiDemandDialDisconnectExpired: Dialmode is manual!");
        return VOS_OK;
    }

    /* 获取在定时器启动后上下行统计的数据包数以及当前用户连接状态 */
    ulPktsNum = pstNetCntxt->stDsFlowStats.ulPeriodSendPktNum;
    ulUserExistFlg  = DRV_AT_GET_USER_EXIST_FLAG();

    /* 按需拨号断开逻辑如下:
         有用户连接且有数据包:
             计数器清零
         其他情况:
             计数器++
       以下场景无法识别:
          当前连接USB，但用户无数据发送，而网络有数据下发，导致也会认为
          是有用户连接且有数据包，而重新计数。
    */
    if ((0 != ulPktsNum)
     && (VOS_TRUE == ulUserExistFlg))
    {
        RNIC_ClearTiDialDownExpCount();
    }
    else
    {
        RNIC_IncTiDialDownExpCount();
    }

    /* 判断统计计数器是否大于等于用户设置断开拨号时长与定时器时长等分 */
    ulCount = RNIC_GetTiDialDownExpCount();

    if ((ulCount >= ulExpiredCount)
       &&(RNIC_ALLOW_EVENT_REPORT == pstDialMode->enEventReportFlag))
    {
        /*通知应用断开拨号 */
        if (VOS_OK == RNIC_SendDialEvent(DEVICE_ID_WAN, RNIC_DAIL_EVENT_DOWN))
        {
            /* 上报断开拨号事件后投票不进入睡眠，在断开拨号成功时解除 */
#if (FEATURE_ON == FEATURE_LTE)
            DRV_PWRCTRL_SLEEPVOTE_LOCK(PWRCTRL_SLEEP_RNIC);
#endif
            RNIC_DBG_SEND_APP_DIALDOWN_SUCC_NUM(1, ucRmNetId);

            RNIC_WARNING_LOG(ACPU_PID_RNIC, "RNIC_ProcUlIpv4DataInPdpDeactive:Send Act PDP Msg to APP");
        }
        else
        {
            RNIC_DBG_SEND_APP_DIALDOWN_FAIL_NUM(1, ucRmNetId);
        }

        RNIC_MNTN_TraceDialDisconnEvt(ulPktsNum, ulUserExistFlg);
    }

    RNIC_StartTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT, TI_RNIC_DEMAND_DIAL_DISCONNECT_LEN);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : RNIC_RcvTiDemandDialProtectExpired
 功能描述  : 拨号保护定时器超时处理, 显式停止定时器, 定时器状态置为停止
 输入参数  : pstMsg  - 定时器消息
             enRmNetId - 网卡ID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月6日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 RNIC_RcvTiDemandDialProtectExpired(
    MsgBlock                           *pstMsg,
    VOS_UINT8                           ucRmNetId
)
{
    /* 停止按需拨号保护定时器 */
    RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_PROTECT);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : RNIC_GetTiExpiredFuncByMsgId
 功能描述  : 获取消息处理函数
 输入参数  : ulMsgId            - 消息ID
 输出参数  : 无
 返 回 值  : pTiExpriedProcFunc - 定时器超时处理函数地址
             VOS_NULL_PTR       - 空
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月28日
    作    者   : f00179208
    修改内容   : 新生成函数

*****************************************************************************/
RNIC_RCV_TI_EXPRIED_PROC_FUNC RNIC_GetTiExpiredFuncByMsgId(VOS_UINT32 ulMsgId)
{
    VOS_UINT8                           i;
    VOS_UINT32                          ulTableSize;

    /* 从g_astRnicTiExpriedProcTab中获取操作个数 */
    ulTableSize = sizeof(g_astRnicTiExpriedProcTab)/sizeof(RNIC_RCV_TI_EXPRIED_PROC_STRU);

    /* g_astRnicTiExpriedProcTab查表，进行消息处理的分发 */
    for (i = 0; i < ulTableSize; i++)
    {
        if (g_astRnicTiExpriedProcTab[i].ulMsgId== ulMsgId)
        {
            return g_astRnicTiExpriedProcTab[i].pTiExpriedProcFunc;
        }
    }

    return VOS_NULL_PTR;
}

/*****************************************************************************
 函 数 名  : RNIC_RcvCcpuResetStartInd
 功能描述  : RNIC收到RNIC消息ID_CCPU_RESET_RNIC_START_IND的处理
 输入参数  : pMsg:消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_OK
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2013年04月15日
    作    者   : f00179208
    修改内容   : 新生成函数
  2.日    期   : 2014年02月14日
    作    者   : m00217266
    修改内容   : 添加L-C互操作项目新添加的全局变量的初始化
*****************************************************************************/
VOS_UINT32 RNIC_RcvCcpuResetStartInd(
    MsgBlock                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    RNIC_CTX_STRU                      *pstRnicCtx;

    pstRnicCtx                          = RNIC_GetRnicCtxAddr();

    printk("\n RNIC_RcvCcpuResetStartInd enter, %u \n", VOS_GetSlice());

    /* 停止所有启动的定时器 */
    RNIC_StopAllTimer();

    for (ucIndex = 0 ; ucIndex < RNIC_NET_ID_MAX_NUM ; ucIndex++)
    {
        /* 清除流量统计信息 */
        RNIC_ClearNetDsFlowStats(ucIndex);

        /* 初始化RNIC PDP上下文 */
        RNIC_InitPdpCtx(&(pstRnicCtx->astSpecCtx[ucIndex].stPdpCtx), ucIndex);

        /* 初始化流控状态 */
        pstRnicCtx->astSpecCtx[ucIndex].enFlowCtrlStatus = RNIC_FLOW_CTRL_STATUS_STOP;

        /* 初始化模块ID */
        /* 初始化的时候就已经确定了哪张网卡对应哪个MODEM */
        pstRnicCtx->astSpecCtx[ucIndex].enModemId        = RNIC_GET_MODEM_ID_BY_NET_ID(ucIndex);

        /* Added by m00217266 for L-C互操作项目, 2014-1-27, begin */
        pstRnicCtx->astSpecCtx[ucIndex].enModemType      = RNIC_MODEM_TYPE_INSIDE;
        /* Added by m00217266 for L-C互操作项目, 2014-1-27, end */
    }

    /* 初始化RABID信息 */
    for (ucIndex = 0 ; ucIndex < RNIC_MODEM_ID_MAX_NUM ; ucIndex++)
    {
        RNIC_InitRabidInfo(&pstRnicCtx->astRabIdInfo[ucIndex]);
    }

    /* Added by m00217266 for L-C互操作项目, 2014-1-27, begin */
    /* 初始化PDNID信息 */
    RNIC_InitPdnIdInfo(&(pstRnicCtx->stPdnIdInfo));
    /* Added by m00217266 for L-C互操作项目, 2014-1-27, end */

    /* 初始化RNIC定时器上下文 */
    RNIC_InitAllTimers(pstRnicCtx->astTimerCtx);

    /* 初始化拨号模式信息 */
    RNIC_ResetDialMode(&(pstRnicCtx->stDialMode));

    /* 初始化拨号断开定时器超时次数参数统计 */
    RNIC_ClearTiDialDownExpCount();

    /* 初始化TIMER4唤醒标志 */
    RNIC_SetTimer4WakeFlg(VOS_FALSE);

    /* 释放信号量，使得调用API任务继续运行 */
    VOS_SmV(RNIC_GetResetSem());

    /* Added by m00217266 for L-C互操作项目, 2014-2-17, begin */
    /* 此处是否要清空sdio下行注册函数 */
    /* Added by m00217266 for L-C互操作项目, 2014-2-17, end */
    printk("\n RNIC_RcvCcpuResetStartInd leave, %u \n", VOS_GetSlice());
    return VOS_OK;
}

#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 函 数 名  : RNIC_RcvImsaPdnActInd
 功能描述  : RNIC收到IMSA消息ID_IMSA_RNIC_PDN_ACT_IND的处理
 输入参数  : pMsg:消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_OK
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年07月31日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 RNIC_RcvImsaPdnActInd(
    MsgBlock                           *pstMsg
)
{
    IMSA_RNIC_PDN_ACT_IND_STRU         *pstRcvInd;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           ucRabid;
    VOS_UINT8                           ucRmNetId;

    pstRcvInd                           = (IMSA_RNIC_PDN_ACT_IND_STRU *)pstMsg;

    /* 指定一张专门的网卡用于VT视频数据传输 */
    ucRmNetId                           = RNIC_RMNET_ID_VT;

    /* 获取PDP上下文地址 */
    pstPdpAddr                          = RNIC_GetPdpCtxAddr(ucRmNetId);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);
    ucRabid                             = RNIC_RAB_ID_INVALID;

    /* 根据modem id和网卡id，填充Rabid */
    if (VOS_OK != RNIC_BuildRabIdByModemId(pstSpecNetCardCtx->enModemId,
                                           pstRcvInd->stPdnInfo.ucRabId,
                                           &ucRabid))
    {
        RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_RcvImsaPdnActInd, modemId:%d", pstSpecNetCardCtx->enModemId);
        return VOS_ERR;
    }

    /* 存储RABID对应的网卡ID */
    if (VOS_OK != RNIC_SaveNetIdByRabId(pstSpecNetCardCtx->enModemId,
                                        pstRcvInd->stPdnInfo.ucRabId,
                                        ucRmNetId))
    {
        RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_RcvImsaPdnActInd, RabId:%d", pstRcvInd->stPdnInfo.ucRabId);
        return VOS_ERR;
    }

    pstSpecNetCardCtx->enModemType        = RNIC_MODEM_TYPE_INSIDE;

    /* 更新PDP上下文信息 */

    /* IPV4激活 */
    if (VOS_TRUE == pstRcvInd->stPdnInfo.bitOpIpv4PdnInfo)
    {
        pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
        pstPdpAddr->stIpv4PdpInfo.ucRabId     = pstRcvInd->stPdnInfo.ucRabId;
    }

    /* IPV6激活 */
    if (VOS_TRUE == pstRcvInd->stPdnInfo.bitOpIpv6PdnInfo)
    {
        pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
        pstPdpAddr->stIpv6PdpInfo.ucRabId     = pstRcvInd->stPdnInfo.ucRabId;
    }

    /* IPV4V6激活 */
    if (VOS_TRUE == (pstRcvInd->stPdnInfo.bitOpIpv4PdnInfo & pstRcvInd->stPdnInfo.bitOpIpv6PdnInfo))
    {
        pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
        pstPdpAddr->stIpv4v6PdpInfo.ucRabId     = pstRcvInd->stPdnInfo.ucRabId;
    }

    /* 注册下行发送函数，ADS调用注册的函数发送下行数据 */
    ADS_DL_RegDlDataCallback(ucRabid, RNIC_RcvAdsDlData, ucRmNetId);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : RNIC_RcvImsaPdnDeactInd
 功能描述  : RNIC收到IMSA消息ID_IMSA_RNIC_PDN_DEACT_IND的处理
 输入参数  : pMsg:消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_OK
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年07月31日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 RNIC_RcvImsaPdnDeactInd(
    MsgBlock                           *pstMsg
)
{
    IMSA_RNIC_PDN_DEACT_IND_STRU       *pstRcvInd;
    RNIC_PDP_CTX_STRU                  *pstPdpCtxAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           ucRmNetId;

    pstRcvInd                           = (IMSA_RNIC_PDN_DEACT_IND_STRU *)pstMsg;

    /* 指定一张专门的网卡用于VT视频数据传输 */
    ucRmNetId                           = RNIC_RMNET_ID_VT;

    /* 获取PDP上下文地址 */
    pstPdpCtxAddr                       = RNIC_GetPdpCtxAddr(ucRmNetId);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);

    /* 如果是IPV4 PDP去激活 */
    if ((pstPdpCtxAddr->stIpv4PdpInfo.ucRabId == pstRcvInd->ucRabId)
     && (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtxAddr->stIpv4PdpInfo.enRegStatus))
    {
        /* 清空IPV4 PDP上下文信息 */
        RNIC_InitIpv4PdpCtx(&pstPdpCtxAddr->stIpv4PdpInfo);
    }

    if ((pstPdpCtxAddr->stIpv6PdpInfo.ucRabId == pstRcvInd->ucRabId)
     && (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtxAddr->stIpv6PdpInfo.enRegStatus))
    {
        /* 清空IPV6 PDP上下文信息 */
        RNIC_InitIpv6PdpCtx(&pstPdpCtxAddr->stIpv6PdpInfo);
    }

    if ((pstPdpCtxAddr->stIpv4v6PdpInfo.ucRabId == pstRcvInd->ucRabId)
     && (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtxAddr->stIpv4v6PdpInfo.enRegStatus))
    {
        /* 清空IPV4V6 PDP上下文信息 */
        RNIC_InitIpv4v6PdpCtx(&pstPdpCtxAddr->stIpv4v6PdpInfo, ucRmNetId);
    }

    /* 该网卡上面PDP都去激活的时候，清空该网卡的上下文信息 */
    if ((RNIC_PDP_REG_STATUS_ACTIVE != pstPdpCtxAddr->stIpv4PdpInfo.enRegStatus)
     && (RNIC_PDP_REG_STATUS_ACTIVE != pstPdpCtxAddr->stIpv6PdpInfo.enRegStatus)
     && (RNIC_PDP_REG_STATUS_ACTIVE != pstPdpCtxAddr->stIpv4v6PdpInfo.enRegStatus))
    {
        /* 清除流量统计信息 */
        RNIC_ClearNetDsFlowStats(ucRmNetId);
        pstSpecNetCardCtx->enModemType = RNIC_MODEM_TYPE_INSIDE;
    }

    /* 清除RABID对应的网卡ID */
    if (VOS_OK != RNIC_SaveNetIdByRabId(pstSpecNetCardCtx->enModemId,
                                        pstRcvInd->ucRabId,
                                        RNIC_RMNET_ID_BUTT))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}
#endif


/* Modified by l60609 for L-C互操作项目, 2014-01-06, Begin */
/*****************************************************************************
 函 数 名  : RNIC_ProcInsideModemIpv4ActInd
 功能描述  : 内modem ipv4激活
 输入参数  : RNIC_RMNET_CONFIG_REQ_STRU           *pstPdpStatusInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月27日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID RNIC_ProcInsideModemIpv4ActInd(
    RNIC_RMNET_CONFIG_REQ_STRU         *pstPdpStatusInd
)
{
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId;
    VOS_UINT8                           ucRabid;
    VOS_UINT8                           ucRmNetId;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr          = VOS_NULL_PTR;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx   = VOS_NULL_PTR;

    ucRmNetId                           = pstPdpStatusInd->ucRmNetId;

    /* 获取PDP上下文地址 */
    pstPdpAddr                          = RNIC_GetPdpCtxAddr(ucRmNetId);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);

    ucRabid                             = RNIC_RAB_ID_INVALID;

    /* 根据modem id和网卡id，填充Rabid */
    if (VOS_OK != RNIC_BuildRabIdByModemId(pstSpecNetCardCtx->enModemId,
                                           pstPdpStatusInd->ucRabId,
                                           &ucRabid))
    {
        RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_ProcInsideModemIpv4ActInd, modemId:%d", pstSpecNetCardCtx->enModemId);
        return;
    }

    /* 存储RABID对应的网卡ID */
    if (VOS_OK != RNIC_SaveNetIdByRabId(pstSpecNetCardCtx->enModemId,
                                        pstPdpStatusInd->ucRabId,
                                        ucRmNetId))
    {
        RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_ProcInsideModemIpv4ActInd, RabId:%d", pstPdpStatusInd->ucRabId);
        return;
    }

    pstSpecNetCardCtx->enModemType        = RNIC_MODEM_TYPE_INSIDE;

    /* 更新PDP上下文信息 */
    pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4PdpInfo.ucRabId     = pstPdpStatusInd->ucRabId;

    /* 根据网卡ID获取流量统计的定时器ID */
    enTimerId = RNIC_GetDsflowTimerIdByNetId(ucRmNetId);

    /* 启动流量统计定时器 */
    RNIC_StartTimer(enTimerId, TI_RNIC_DSFLOW_STATS_LEN);

    /* 停止按需拨号保护定时器 */
    if (RNIC_RMNET_ID_0 == ucRmNetId)
    {
        RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_PROTECT);
    }

    /* 注册下行发送函数，ADS调用注册的函数发送下行数据 */
    ADS_DL_RegDlDataCallback(ucRabid, RNIC_RcvAdsDlData, ucRmNetId);

    return;
}

/*****************************************************************************
 函 数 名  : RNIC_ProcInsideModemIpv6ActInd
 功能描述  : 内modem ipv6激活
 输入参数  : RNIC_RMNET_CONFIG_REQ_STRU           *pstPdpStatusInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月27日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID RNIC_ProcInsideModemIpv6ActInd(
    RNIC_RMNET_CONFIG_REQ_STRU           *pstPdpStatusInd
)
{
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId;
    VOS_UINT8                           ucRabid;
    VOS_UINT8                           ucRmNetId;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr          = VOS_NULL_PTR;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx   = VOS_NULL_PTR;


    ucRmNetId                           = pstPdpStatusInd->ucRmNetId;

    /* 获取PDP上下文地址 */
    pstPdpAddr                          = RNIC_GetPdpCtxAddr(ucRmNetId);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);

    ucRabid                             = RNIC_RAB_ID_INVALID;

    /* 根据modem id和网卡id，填充Rabid */
    if (VOS_OK != RNIC_BuildRabIdByModemId(pstSpecNetCardCtx->enModemId,
                                           pstPdpStatusInd->ucRabId,
                                           &ucRabid))
    {
        RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_ProcInsideModemIpv6ActInd, modemId:%d", pstSpecNetCardCtx->enModemId);
        return;
    }

    /* 存储RABID对应的网卡ID */
    if (VOS_OK != RNIC_SaveNetIdByRabId(pstSpecNetCardCtx->enModemId,
                                        pstPdpStatusInd->ucRabId,
                                        ucRmNetId))
    {
        RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_ProcInsideModemIpv6ActInd, RabId:%d", pstPdpStatusInd->ucRabId);
        return;
    }

    pstSpecNetCardCtx->enModemType        = RNIC_MODEM_TYPE_INSIDE;

    /* 更新PDP上下文信息 */
    pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv6PdpInfo.ucRabId     = pstPdpStatusInd->ucRabId;

    /* 根据网卡ID获取流量统计的定时器ID */
    enTimerId = RNIC_GetDsflowTimerIdByNetId(ucRmNetId);

    /* 启动流量统计定时器 */
    RNIC_StartTimer(enTimerId, TI_RNIC_DSFLOW_STATS_LEN);

    /* 注册下行发送函数，ADS调用注册的函数发送下行数据 */
    ADS_DL_RegDlDataCallback(ucRabid, RNIC_RcvAdsDlData, ucRmNetId);

    return;
}

/*****************************************************************************
 函 数 名  : RNIC_ProcRnicPdpActInd
 功能描述  : 处理PDP激活消息
 输入参数  : RNIC_PDP_STATUS_IND_STRU           *pstPdpStatusInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID RNIC_ProcRnicPdpActInd(
    RNIC_RMNET_CONFIG_REQ_STRU           *pstPdpStatusInd
)
{
    /* 默认ipv4和ipv6激活成功分两次下发 */
    if (RNIC_MODEM_TYPE_INSIDE == pstPdpStatusInd->enModemType)
    {
        if (RNIC_IP_TYPE_IPV4 == pstPdpStatusInd->enIpType)
        {
            /* balong modem ipv4激活 */
            RNIC_ProcInsideModemIpv4ActInd(pstPdpStatusInd);
        }

        if (RNIC_IP_TYPE_IPV6 == pstPdpStatusInd->enIpType)
        {
            /* balong modem ipv6激活 */
            RNIC_ProcInsideModemIpv6ActInd(pstPdpStatusInd);
        }
    }

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    if (RNIC_MODEM_TYPE_OUTSIDE == pstPdpStatusInd->enModemType)
    {
        if (RNIC_IP_TYPE_IPV4 == pstPdpStatusInd->enIpType)
        {
            /* 外置modem ipv4激活*/
            RNIC_ProcOutsideModemIpv4ActInd(pstPdpStatusInd);
        }

        if (RNIC_IP_TYPE_IPV6 == pstPdpStatusInd->enIpType)
        {
            /* 外置modem ipv6激活*/
            RNIC_ProcOutsideModemIpv6ActInd(pstPdpStatusInd);
        }
    }
#endif

    return;
}

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
/*****************************************************************************
 函 数 名  : RNIC_SaveNetIdByPdnId
 功能描述  : 根据pdn id保存网卡id
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月7日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 RNIC_SaveNetIdByPdnId(
    VOS_UINT8                           ucPdnId,
    VOS_UINT8                           ucRmNetId
)
{
    RNIC_PDNID_INFO_STAU               *pstPdnIdInfo;

    if ((ucPdnId < RNIC_PDN_ID_MIN)
     || (ucPdnId > RNIC_PDN_ID_MAX))
    {
        return VOS_ERR;
    }

    /* 获取指定Modem的RABID信息 */
    pstPdnIdInfo = RNIC_GET_SPEC_MODEM_PDNID_INFO();

    pstPdnIdInfo->aucRmNetId[ucPdnId - RNIC_PDN_ID_OFFSET] = ucRmNetId;

    return VOS_OK;

}


/*****************************************************************************
 函 数 名  : RNIC_ProcOutsideModemIpv4ActInd
 功能描述  : 外modem ipv4激活
 输入参数  : RNIC_RMNET_CONFIG_REQ_STRU           *pstPdpStatusInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月27日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID RNIC_ProcOutsideModemIpv4ActInd(
    RNIC_RMNET_CONFIG_REQ_STRU           *pstPdpStatusInd
)
{
    VOS_UINT8                           ucPdnId;
    VOS_UINT8                           ucRmNetId;
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx   = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr          = VOS_NULL_PTR;

    ucRmNetId                           = pstPdpStatusInd->ucRmNetId;

    /* 获取PDP上下文地址 */
    pstPdpAddr                          = RNIC_GetPdpCtxAddr(ucRmNetId);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);

    ucPdnId                             = pstPdpStatusInd->ucPdnId;

    /* 存储PDNID对应的网卡ID */
    if (VOS_OK != RNIC_SaveNetIdByPdnId(ucPdnId,
                                        ucRmNetId))
    {
        RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_ProcOutsideModemIpv4ActInd, PdnId:%d", ucPdnId);
        return;
    }

    pstSpecNetCardCtx->enModemType        = RNIC_MODEM_TYPE_OUTSIDE;

    /* 更新PDP上下文信息 */
    pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4PdpInfo.ucPdnId     = ucPdnId;

    /* 根据网卡ID获取流量统计的定时器ID */
    enTimerId = RNIC_GetDsflowTimerIdByNetId(ucRmNetId);

    /* 启动流量统计定时器 */
    RNIC_StartTimer(enTimerId, TI_RNIC_DSFLOW_STATS_LEN);

    /* 注册下行发送函数，ADS调用注册的函数发送下行数据 */
    SDIO_DL_RegDataCallback(ucPdnId, (RCV_C_DL_DATA_FUNC)RNIC_RcvSdioDlData);

    return;
}


/*****************************************************************************
 函 数 名  : RNIC_ProcOutsideModemIpv6ActInd
 功能描述  : 外modem ipv6激活
 输入参数  : RNIC_RMNET_CONFIG_REQ_STRU           *pstPdpStatusInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月27日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID RNIC_ProcOutsideModemIpv6ActInd(
    RNIC_RMNET_CONFIG_REQ_STRU           *pstPdpStatusInd
)
{
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId;
    VOS_UINT8                           ucPdnId;
    VOS_UINT8                           ucRmNetId;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr          = VOS_NULL_PTR;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx   = VOS_NULL_PTR;

    ucRmNetId                           = pstPdpStatusInd->ucRmNetId;

    /* 获取PDP上下文地址 */
    pstPdpAddr                          = RNIC_GetPdpCtxAddr(ucRmNetId);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);

    ucPdnId                             = pstPdpStatusInd->ucPdnId;

    /* 存储PDNID对应的网卡ID */
    if (VOS_OK != RNIC_SaveNetIdByPdnId(ucPdnId,
                                        ucRmNetId))
    {
        RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_ProcOutsideModemIpv6ActInd, PdnId:%d", ucPdnId);
        return;
    }

    pstSpecNetCardCtx->enModemType        = RNIC_MODEM_TYPE_OUTSIDE;

    /* 更新PDP上下文信息 */
    pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv6PdpInfo.ucPdnId     = ucPdnId;

    /* 根据网卡ID获取流量统计的定时器ID */
    enTimerId = RNIC_GetDsflowTimerIdByNetId(ucRmNetId);

    /* 启动流量统计定时器 */
    RNIC_StartTimer(enTimerId, TI_RNIC_DSFLOW_STATS_LEN);

    /* 注册下行发送函数，ADS调用注册的函数发送下行数据 */
    SDIO_DL_RegDataCallback(ucPdnId, (RCV_C_DL_DATA_FUNC)RNIC_RcvSdioDlData);

    return;
}

/*****************************************************************************
 函 数 名  : RNIC_ClearIpv4PdpCtxInSwitch
 功能描述  : 在内外网卡切换过程中清空网卡的ipv4 pdp上下文
 输入参数  : VOS_UINT8  ucRmNetId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月19日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID RNIC_ClearIpv4PdpCtxInSwitch(
    VOS_UINT8                           ucRmNetId
)
{
    VOS_UINT8                           ucPdnId;
    VOS_UINT8                           ucRabId;
    VOS_UINT16                          usModemId;
    RNIC_PDP_CTX_STRU                  *pstPdpCtx           = VOS_NULL_PTR;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx   = VOS_NULL_PTR;

    ucPdnId           = RNIC_PDN_ID_INVALID;
    ucRabId           = RNIC_RAB_ID_INVALID;
    pstPdpCtx         = RNIC_GET_SPEC_NET_PDP_CTX(ucRmNetId);
    pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);
    usModemId         = pstSpecNetCardCtx->enModemId;

    /* 根据PDP激活类型，清空PDN ID 和 RAB ID对应的网卡id信息 */
    /* 对于外置modem需要置空下行数据发送指针 */
    if (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtx->stIpv4PdpInfo.enRegStatus)
    {
        if (RNIC_PDN_ID_INVALID != pstPdpCtx->stIpv4PdpInfo.ucPdnId)
        {
            ucPdnId = pstPdpCtx->stIpv4PdpInfo.ucPdnId;

            if (VOS_OK != RNIC_SaveNetIdByPdnId(ucPdnId, RNIC_RMNET_ID_BUTT))
            {
                RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_ClearIpv4PdpCtxInSwitch, Pdnid:%d", ucPdnId);
            }

            SDIO_DL_RegDataCallback(ucPdnId, (RCV_C_DL_DATA_FUNC)VOS_NULL_PTR);
        }

        if (RNIC_RAB_ID_INVALID != pstPdpCtx->stIpv4PdpInfo.ucRabId)
        {
            ucRabId = pstPdpCtx->stIpv4PdpInfo.ucRabId;

            if (VOS_OK != RNIC_SaveNetIdByRabId(usModemId, ucRabId, RNIC_RMNET_ID_BUTT))
            {
                RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_ClearIpv4PdpCtxInSwitch, ucRabId:%d", ucRabId);
            }
        }
    }

    /* 清空ip上下文 */
    RNIC_InitIpv4PdpCtx(&(pstPdpCtx->stIpv4PdpInfo));
    return;
}

/*****************************************************************************
 函 数 名  : RNIC_ClearIpv6PdpCtxInSwitch
 功能描述  : 在内外网卡切换过程中清空网卡的ipv6 pdp上下文
 输入参数  : VOS_UINT8  ucRmNetId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月19日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID RNIC_ClearIpv6PdpCtxInSwitch(
    VOS_UINT8                           ucRmNetId
)
{
    VOS_UINT8                           ucPdnId;
    VOS_UINT8                           ucRabId;
    VOS_UINT16                          usModemId;
    RNIC_PDP_CTX_STRU                  *pstPdpCtx           = VOS_NULL_PTR;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx   = VOS_NULL_PTR;

    ucPdnId           = RNIC_PDN_ID_INVALID;
    ucRabId           = RNIC_RAB_ID_INVALID;
    pstPdpCtx         = RNIC_GET_SPEC_NET_PDP_CTX(ucRmNetId);
    pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);
    usModemId         = pstSpecNetCardCtx->enModemId;

    /* 根据PDP激活类型，清空PDN ID 和 RAB ID对应的网卡id信息 */
    /* 对于外置modem需要置空下行数据发送指针 */
    if (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtx->stIpv6PdpInfo.enRegStatus)
    {
        if (RNIC_PDN_ID_INVALID != pstPdpCtx->stIpv6PdpInfo.ucPdnId)
        {
            ucPdnId = pstPdpCtx->stIpv6PdpInfo.ucPdnId;

            if (VOS_OK != RNIC_SaveNetIdByPdnId(ucPdnId, RNIC_RMNET_ID_BUTT))
            {
                RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_ClearIpv6PdpCtxInSwitch, Pdnid:%d", ucPdnId);
            }

            SDIO_DL_RegDataCallback(ucPdnId, (RCV_C_DL_DATA_FUNC)VOS_NULL_PTR);
        }

        if (RNIC_RAB_ID_INVALID != pstPdpCtx->stIpv6PdpInfo.ucRabId)
        {
            ucRabId = pstPdpCtx->stIpv6PdpInfo.ucRabId;

            if (VOS_OK != RNIC_SaveNetIdByRabId(usModemId, ucRabId, RNIC_RMNET_ID_BUTT))
            {
                RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_ClearIpv6PdpCtxInSwitch, ucRabId:%d", ucRabId);
            }
        }
    }

    /* 清空ip上下文 */
    RNIC_InitIpv6PdpCtx(&(pstPdpCtx->stIpv6PdpInfo));
    return;
}

/*****************************************************************************
 函 数 名  : RNIC_ClearIpv4v6PdpCtxInSwitch
 功能描述  : 在内外网卡切换过程中清空网卡的ipv4v6 pdp上下文
 输入参数  : VOS_UINT8 ucRmNetId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月19日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID RNIC_ClearIpv4v6PdpCtxInSwitch(
    VOS_UINT8                           ucRmNetId
)
{
    VOS_UINT8                           ucPdnId;
    VOS_UINT8                           ucRabId;
    VOS_UINT16                          usModemId;
    RNIC_PDP_CTX_STRU                  *pstPdpCtx           = VOS_NULL_PTR;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx   = VOS_NULL_PTR;

    ucPdnId           = RNIC_PDN_ID_INVALID;
    ucRabId           = RNIC_RAB_ID_INVALID;
    pstPdpCtx         = RNIC_GET_SPEC_NET_PDP_CTX(ucRmNetId);
    pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);
    usModemId         = pstSpecNetCardCtx->enModemId;

    /* 根据PDP激活类型，清空PDN ID 和 RAB ID对应的网卡id信息 */
    /* 对于外置modem需要置空下行数据发送指针 */
    if (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtx->stIpv4v6PdpInfo.enRegStatus)
    {
        if (RNIC_PDN_ID_INVALID != pstPdpCtx->stIpv4v6PdpInfo.ucPdnId)
        {
            ucPdnId = pstPdpCtx->stIpv4v6PdpInfo.ucPdnId;

            if (VOS_OK != RNIC_SaveNetIdByPdnId(ucPdnId, RNIC_RMNET_ID_BUTT))
            {
                RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_ClearIpv4v6PdpCtxInSwitch, Pdnid:%d", ucPdnId);
            }

            SDIO_DL_RegDataCallback(ucPdnId, (RCV_C_DL_DATA_FUNC)VOS_NULL_PTR);
        }

        if (RNIC_RAB_ID_INVALID != pstPdpCtx->stIpv4v6PdpInfo.ucRabId)
        {
            ucRabId = pstPdpCtx->stIpv4v6PdpInfo.ucRabId;

            if (VOS_OK != RNIC_SaveNetIdByRabId(usModemId, ucRabId, RNIC_RMNET_ID_BUTT))
            {
                RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_ClearIpv4v6PdpCtxInSwitch, ucRabId:%d", ucRabId);
            }
        }
    }

    /* 清空ip上下文 */
    RNIC_InitIpv4v6PdpCtx(&(pstPdpCtx->stIpv4v6PdpInfo), ucRmNetId);
    return;
}

/*****************************************************************************
 函 数 名  : RNIC_ClearSwitchPdpCtx
 功能描述  : 在内外网卡切换过程中清空pdp上下文
 输入参数  : ucRmNetId
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月10日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID RNIC_ClearPdpCtxInSwitch(
    VOS_UINT8                           ucRmNetId
)
{
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx   = VOS_NULL_PTR;

    pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);

    /* 根据PDP激活类型，分别清空PDN ID 和 RAB ID对应的网卡id信息 */
    /* 对于外置modem需要置空下行数据发送指针 */
    /* 清空ipv4 pdp上下文 */
    RNIC_ClearIpv4PdpCtxInSwitch(ucRmNetId);

    /* 清空ipv6 pdp上下文 */
    RNIC_ClearIpv6PdpCtxInSwitch(ucRmNetId);

    /* 清空ipv4v6 pdp上下文 */
    RNIC_ClearIpv4v6PdpCtxInSwitch(ucRmNetId);

    /* 重置modem type */
    pstSpecNetCardCtx->enModemType = RNIC_MODEM_TYPE_INSIDE;

    return;
}

/*****************************************************************************
 函 数 名  : RNIC_ProcRnicPdpHandoverInd
 功能描述  : 处理PDP handover消息
 输入参数  : RNIC_PDP_STATUS_IND_STRU           *pstPdpStatusInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月6日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID RNIC_ProcRnicPdpHandoverInd(
    RNIC_RMNET_CONFIG_REQ_STRU           *pstPdpStatusInd
)
{
    VOS_UINT8                           ucRmNetId;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx = VOS_NULL_PTR;

    ucRmNetId                           = pstPdpStatusInd->ucRmNetId;
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);

    /* handover处理流程分为两步，
       1、首次handover清除req消息处理之前pdp上下文和网卡信息
       2、保存本次req中PDP上下文，该流程处理与PDP激活流程一致*/

    /* step1:首次handover清除pdp上下文和网卡信息 */
    if (pstPdpStatusInd->enModemType != pstSpecNetCardCtx->enModemType)
    {
        RNIC_ClearPdpCtxInSwitch(ucRmNetId);
    }

    /* step2:保存PDP上下文 */
    RNIC_ProcRnicPdpActInd(pstPdpStatusInd);

    return;
}

/*****************************************************************************
 函 数 名  : RNIC_ProcOutsideModemDeactInd
 功能描述  : 处理外部modem PDP去激活
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月8日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID RNIC_ProcOutsideModemDeactInd(
    RNIC_RMNET_CONFIG_REQ_STRU         *pstPdpStatusInd
)
{
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId;
    VOS_UINT8                           ucRmNetId;
    RNIC_PDP_CTX_STRU                  *pstPdpCtxAddr       = VOS_NULL_PTR;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx   = VOS_NULL_PTR;

    ucRmNetId                           = pstPdpStatusInd->ucRmNetId;

    /* 获取PDP上下文地址 */
    pstPdpCtxAddr                       = RNIC_GetPdpCtxAddr(ucRmNetId);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);

    /* 根据网卡ID获取流量统计的定时器ID */
    enTimerId = RNIC_GetDsflowTimerIdByNetId(ucRmNetId);

    /* 如果是IPV4 PDP去激活 */
    if ((pstPdpCtxAddr->stIpv4PdpInfo.ucPdnId == pstPdpStatusInd->ucPdnId)
     && (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtxAddr->stIpv4PdpInfo.enRegStatus))
    {
        /* 清空IPV4 PDP上下文信息 */
        RNIC_InitIpv4PdpCtx(&pstPdpCtxAddr->stIpv4PdpInfo);
    }

    if ((pstPdpCtxAddr->stIpv6PdpInfo.ucPdnId == pstPdpStatusInd->ucPdnId)
     && (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtxAddr->stIpv6PdpInfo.enRegStatus))
    {
        /* 清空IPV6 PDP上下文信息 */
        RNIC_InitIpv6PdpCtx(&pstPdpCtxAddr->stIpv6PdpInfo);
    }

    if ((pstPdpCtxAddr->stIpv4v6PdpInfo.ucPdnId == pstPdpStatusInd->ucPdnId)
     && (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtxAddr->stIpv4v6PdpInfo.enRegStatus))
    {
        /* 清空IPV4V6 PDP上下文信息 */
        RNIC_InitIpv4v6PdpCtx(&pstPdpCtxAddr->stIpv4v6PdpInfo, ucRmNetId);
    }

    /* PDP都未激活的时候 */
    if ((RNIC_PDP_REG_STATUS_ACTIVE != pstPdpCtxAddr->stIpv4PdpInfo.enRegStatus)
     && (RNIC_PDP_REG_STATUS_ACTIVE != pstPdpCtxAddr->stIpv6PdpInfo.enRegStatus)
     && (RNIC_PDP_REG_STATUS_ACTIVE != pstPdpCtxAddr->stIpv4v6PdpInfo.enRegStatus))
    {
        /* 停止流量统计定时器 */
        RNIC_StopTimer(enTimerId);

        /* 清除流量统计信息 */
        RNIC_ClearNetDsFlowStats(ucRmNetId);

        pstSpecNetCardCtx->enModemType = RNIC_MODEM_TYPE_INSIDE;
    }

    /* 清除注册给SDIO的回调函数 */
    SDIO_DL_RegDataCallback(pstPdpStatusInd->ucPdnId, (RCV_C_DL_DATA_FUNC)VOS_NULL_PTR);

    /* 清除PDNID对应的网卡ID */
    if (VOS_OK != RNIC_SaveNetIdByPdnId(pstPdpStatusInd->ucPdnId,
                                        RNIC_RMNET_ID_BUTT))
    {
        return;
    }

    return;
}

#endif

/*****************************************************************************
 函 数 名  : RNIC_ProcInsideModemDeactInd
 功能描述  : 处理内部modem PDP去激活
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月8日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID RNIC_ProcInsideModemDeactInd(
    RNIC_RMNET_CONFIG_REQ_STRU         *pstPdpStatusInd
)
{
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId;
    VOS_UINT8                           ucRmNetId;
    RNIC_PDP_CTX_STRU                  *pstPdpCtxAddr       = VOS_NULL_PTR;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx   = VOS_NULL_PTR;

    ucRmNetId                           = pstPdpStatusInd->ucRmNetId;

    /* 获取PDP上下文地址 */
    pstPdpCtxAddr                       = RNIC_GetPdpCtxAddr(ucRmNetId);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);

    /* 根据网卡ID获取流量统计的定时器ID */
    enTimerId = RNIC_GetDsflowTimerIdByNetId(ucRmNetId);

    /* 如果是IPV4 PDP去激活 */
    if ((pstPdpCtxAddr->stIpv4PdpInfo.ucRabId == pstPdpStatusInd->ucRabId)
     && (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtxAddr->stIpv4PdpInfo.enRegStatus))
    {
        /* 清空IPV4 PDP上下文信息 */
        RNIC_InitIpv4PdpCtx(&pstPdpCtxAddr->stIpv4PdpInfo);

        /* 在网卡0上才有按需拨号的功能 */
        if (RNIC_RMNET_ID_0 == ucRmNetId)
        {
            /* 停止按需拨号断开定时器 */
            RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT);

            /* 清空拨号断开定时器超时统计 */
            RNIC_ClearTiDialDownExpCount();
        }
    }

    if ((pstPdpCtxAddr->stIpv6PdpInfo.ucRabId == pstPdpStatusInd->ucRabId)
     && (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtxAddr->stIpv6PdpInfo.enRegStatus))
    {
        /* 清空IPV6 PDP上下文信息 */
        RNIC_InitIpv6PdpCtx(&pstPdpCtxAddr->stIpv6PdpInfo);
    }

    if ((pstPdpCtxAddr->stIpv4v6PdpInfo.ucRabId == pstPdpStatusInd->ucRabId)
     && (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtxAddr->stIpv4v6PdpInfo.enRegStatus))
    {
        /* 清空IPV4V6 PDP上下文信息 */
        RNIC_InitIpv4v6PdpCtx(&pstPdpCtxAddr->stIpv4v6PdpInfo, ucRmNetId);
    }

    /* PDP都未激活的时候 */
    if ((RNIC_PDP_REG_STATUS_ACTIVE != pstPdpCtxAddr->stIpv4PdpInfo.enRegStatus)
     && (RNIC_PDP_REG_STATUS_ACTIVE != pstPdpCtxAddr->stIpv6PdpInfo.enRegStatus)
     && (RNIC_PDP_REG_STATUS_ACTIVE != pstPdpCtxAddr->stIpv4v6PdpInfo.enRegStatus))
    {
        /* 停止流量统计定时器 */
        RNIC_StopTimer(enTimerId);

        /* 清除流量统计信息 */
        RNIC_ClearNetDsFlowStats(ucRmNetId);

        pstSpecNetCardCtx->enModemType = RNIC_MODEM_TYPE_INSIDE;
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* 在断开拨号成功时解除投票睡眠，以便能进入深睡 */
    DRV_PWRCTRL_SLEEPVOTE_UNLOCK(PWRCTRL_SLEEP_RNIC);
#endif

    /* 清除RABID对应的网卡ID */
    if (VOS_OK != RNIC_SaveNetIdByRabId(pstSpecNetCardCtx->enModemId,
                                        pstPdpStatusInd->ucRabId,
                                        RNIC_RMNET_ID_BUTT))
    {
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : RNIC_ProcRnicPdpDeactInd
 功能描述  : 处理PDP去激活消息
 输入参数  : RNIC_PDP_STATUS_IND_STRU           *pstPdpStatusInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月6日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID RNIC_ProcRnicPdpDeactInd(
    RNIC_RMNET_CONFIG_REQ_STRU           *pstPdpStatusInd
)
{
    /* 清空对应网卡的PDP上下文 */
    if (RNIC_MODEM_TYPE_INSIDE == pstPdpStatusInd->enModemType)
    {
        /* 清除内部modem PDP去激活相关上下文 */
        RNIC_ProcInsideModemDeactInd(pstPdpStatusInd);
    }
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    if (RNIC_MODEM_TYPE_OUTSIDE == pstPdpStatusInd->enModemType)
    {
        /* 清除外部modem PDP去激活相关上下文 */
        RNIC_ProcOutsideModemDeactInd(pstPdpStatusInd);
    }
#endif
    return;
}


/*****************************************************************************
 函 数 名  : RNIC_RcvRnicRmnetConfigReq
 功能描述  : 处理ID_RNIC_RMNET_CONFIG_REQ消息
 输入参数  : MsgBlock                           *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月6日
    作    者   : m00217266
    修改内容   : 新生成函数
  2.日    期   : 2014年6月3日
    作    者   : m00217266
    修改内容   : DTS2014052902453
*****************************************************************************/
VOS_UINT32 RNIC_RcvRnicRmnetConfigReq(
    MsgBlock                           *pstMsg
)
{
    VOS_UINT8                           ucRmNetId;
    RNIC_RMNET_CONFIG_REQ_STRU         *pstRmnetConfigReq = VOS_NULL_PTR;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx = VOS_NULL_PTR;

    pstRmnetConfigReq       = (RNIC_RMNET_CONFIG_REQ_STRU *)pstMsg;
    ucRmNetId               = pstRmnetConfigReq->ucRmNetId;
    pstSpecNetCardCtx       = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);

    /* pdp激活成功，rnic网卡up */
    if (RNIC_RMNET_STATUS_UP == pstRmnetConfigReq->enRmnetStatus)
    {
        /* RNIC_MODEM_TYPE_BUTT修改为RNIC_MODEM_TYPE_INSIDE，主要为了适配v3r3按需拨号功能 */
        if ((pstSpecNetCardCtx->enModemType == pstRmnetConfigReq->enModemType)
         || (RNIC_MODEM_TYPE_INSIDE == pstSpecNetCardCtx->enModemType))
        {
            RNIC_ProcRnicPdpActInd(pstRmnetConfigReq);
        }
    }
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    /* 内外modem ps域handover，rnic网卡switch */
    else if (RNIC_RMNET_STATUS_SWITCH == pstRmnetConfigReq->enRmnetStatus)
    {
        RNIC_ProcRnicPdpHandoverInd(pstRmnetConfigReq);
    }
#endif
    /* pdp去激活成功，rnic网卡down */
    else
    {
        if (pstSpecNetCardCtx->enModemType == pstRmnetConfigReq->enModemType)
        {
            RNIC_ProcRnicPdpDeactInd(pstRmnetConfigReq);
        }
    }

    return VOS_OK;
}
/* Modified by l60609 for L-C互操作项目, 2014-01-06, End */


/*****************************************************************************
 函 数 名  : Rnic_RcvAtMsg
 功能描述  : RNIC收到AT消息的分发
 输入参数  : pMsg:AT的发来的消息
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_OK, VOS_ERR
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年12月06日
   作    者   : f00179208
   修改内容   : 新生成函数
 2.日    期   : 2012年1月31日
   作    者   : w00199382
   修改内容   : ID_AT_RNIC_DIAL_MODE_IND ID_AT_RNIC_DIAL_MODE_REQ删除
  3.日    期   : 2012年11月23日
    作    者   : f00179208
    修改内容   : DSDA Phase I: 增加MTU更改消息
  4.日    期   : 2013年6月4日
    作    者   : z00214637
    修改内容   : V3R3 Share-PDP项目修改
*****************************************************************************/
VOS_UINT32 RNIC_RcvAtMsg(MsgBlock *pstMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    switch(pstMsgHeader->ulMsgName)
    {
        case ID_AT_RNIC_IPV4_PDP_ACT_IND:
            RNIC_RcvAtIpv4PdpActInd(pstMsg);
            break;

        case ID_AT_RNIC_IPV6_PDP_ACT_IND:
            RNIC_RcvAtIpv6PdpActInd(pstMsg);
            break;

        case ID_AT_RNIC_IPV4V6_PDP_ACT_IND:
            RNIC_RcvAtIpv4v6PdpActInd(pstMsg);
            break;

        case ID_AT_RNIC_PDP_DEACT_IND:
            RNIC_RcvAtPdpDeactInd(pstMsg);
            break;

        case ID_AT_RNIC_DSFLOW_IND:
            RNIC_RcvAtDsflowInd(pstMsg);
            break;

        case ID_AT_RNIC_DIAL_MODE_REQ:
            RNIC_RcvAtDialModeReq(pstMsg);
            break;

        case ID_AT_RNIC_PDN_INFO_CFG_IND:
            RNIC_RcvAtPdnInfoCfgInd(pstMsg);
            break;

        case ID_AT_RNIC_PDN_INFO_REL_IND:
            RNIC_RcvAtPdnInfoRelInd(pstMsg);
            break;

        default:
            RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_RcvAtMsg:MsgId", pstMsgHeader->ulMsgName);
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : RNIC_ProcTimerMsg
 功能描述  : RNIC收到定时器消息超时的分发
 输入参数  : pMsg:定时器超时消息
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_OK, VOS_ERR
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2011年12月06日
    作    者   : f00179208
    修改内容   : 新生成函数
  2.日    期   : 2012年1月31日
    作    者   : w00199382
    修改内容   : 拨号保护定时器超时删除
  3.日    期   : 2012年11月23日
    作    者   : f00179208
    修改内容   : DSDA Phase I: RNIC多实例
*****************************************************************************/
VOS_UINT32 RNIC_RcvTimerMsg(MsgBlock *pstMsg)
{
    REL_TIMER_MSG                      *pstRcvMsg;
    VOS_UINT8                           ucRmNetId;
    RNIC_RCV_TI_EXPRIED_PROC_FUNC       pTiExpriedProcFunc;
    VOS_UINT32                          ulRst;

    pTiExpriedProcFunc = VOS_NULL_PTR;
    pstRcvMsg = (REL_TIMER_MSG *)pstMsg;

    /* 根据定时器ID获取网卡ID */
    ucRmNetId = RNIC_GetNetIdByTimerId(pstRcvMsg->ulName);

    /* 查找定时器超时处理表中消息处理操作 */
    pTiExpriedProcFunc = RNIC_GetTiExpiredFuncByMsgId(pstRcvMsg->ulName);
    if (VOS_NULL_PTR != pTiExpriedProcFunc)
    {
        ulRst = pTiExpriedProcFunc(pstMsg, ucRmNetId);
        if (VOS_ERR == ulRst)
        {
            RNIC_INFO_LOG(ACPU_PID_RNIC, "RNIC_RcvTimerMsg:proc func error! \r\n");
            return VOS_ERR;
        }
    }
    else
    {
        RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_RcvTimerMsg:pstRcvMsg->ulName\r\n", pstRcvMsg->ulName);
    }

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : RNIC_RcvRnicMsg
 功能描述  : RNIC收到RNIC消息的分发
 输入参数  : pstMsg:RNIC消息
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_OK, VOS_ERR
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2013年04月15日
    作    者   : f00179208
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 RNIC_RcvRnicMsg(MsgBlock *pstMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    switch(pstMsgHeader->ulMsgName)
    {
        case ID_RNIC_CCPU_RESET_START_IND:
            RNIC_RcvCcpuResetStartInd(pstMsg);
            break;

        case ID_RNIC_CCPU_RESET_END_IND:

            /* do nothing */
            RNIC_NORMAL_LOG(ACPU_PID_RNIC, "RNIC_RcvRnicMsg: rcv ID_CCPU_RNIC_RESET_END_IND");
            break;

        /* Modified by l60609 for L-C互操作项目, 2014-01-06, Begin */
        case ID_RNIC_RMNET_CONFIG_REQ:
            RNIC_RcvRnicRmnetConfigReq(pstMsg);
            break;

        /* Modified by l60609 for L-C互操作项目, 2014-01-06, End */

        default:
            RNIC_NORMAL_LOG1(ACPU_PID_RNIC, "RNIC_RcvRnicMsg: rcv error msg id %d\r\n", pstMsgHeader->ulMsgName);
            break;
    }

    return VOS_OK;
}

#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 函 数 名  : RNIC_RcvImsaMsg
 功能描述  : RNIC收到IMSA消息的分发
 输入参数  : pstMsg:IMSA消息
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_OK, VOS_ERR
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2014年07月31日
    作    者   : f00179208
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 RNIC_RcvImsaMsg(MsgBlock *pstMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    switch(pstMsgHeader->ulMsgName)
    {
        case ID_IMSA_RNIC_PDN_ACT_IND:
            RNIC_RcvImsaPdnActInd(pstMsg);
            break;

        case ID_IMSA_RNIC_PDN_DEACT_IND:
            RNIC_RcvImsaPdnDeactInd(pstMsg);
            break;

        default:
            RNIC_NORMAL_LOG1(ACPU_PID_RNIC, "RNIC_RcvImsaMsg: rcv error msg id %d\r\n", pstMsgHeader->ulMsgName);
            break;
    }

    return VOS_OK;
}
#endif

/*****************************************************************************
 函 数 名  : RNIC_PidMsgProc
 功能描述  : RNIC数据接收task消息处理函数
 输入参数  : pMsg:待处理消息
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_OK, VOS_ERR
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年12月06日
   作    者   : f00179208
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 RNIC_ProcMsg (MsgBlock *pstMsg)
{
    if (VOS_NULL_PTR == pstMsg)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ProcMsg: Msg is invalid!");
        return VOS_ERR;
    }

    /* 消息的分发处理 */
    switch (pstMsg->ulSenderPid)
    {
        case WUEPS_PID_AT:

            /* 接收AT消息 */
            RNIC_RcvAtMsg(pstMsg);
            break;

        case VOS_PID_TIMER:

            /* 接收定时器超时消息 */
            RNIC_RcvTimerMsg(pstMsg);
            break;

        case ACPU_PID_RNIC:

            /* 接收RNIC的消息*/
            RNIC_RcvRnicMsg(pstMsg);
            break;

#if (FEATURE_ON == FEATURE_IMS)
        case PS_PID_IMSA:

            /* 接收IMSA的消息*/
            RNIC_RcvImsaMsg(pstMsg);
            break;
#endif

        default:
            RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_ProcMsg:SendPid", pstMsg->ulSenderPid);
            break;
    }

    return VOS_OK;
}

/* Modified by m00217266 for L-C互操作项目, 2014-01-06, Begin */
/*****************************************************************************
 函 数 名  : RNIC_SndRnicRmnetConfigReq
 功能描述  : RNIC内部发送PDP 状态信息
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月18日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 RNIC_SndRnicRmnetConfigReq(
    RNIC_RMNET_CONFIG_STRU             *pstConfigInfo
)
{
    RNIC_RMNET_CONFIG_REQ_STRU         *pstSndMsg = VOS_NULL_PTR;

    /* 内存分配 */
    pstSndMsg = (RNIC_RMNET_CONFIG_REQ_STRU *)PS_ALLOC_MSG(ACPU_PID_RNIC,
                        sizeof(RNIC_RMNET_CONFIG_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSndMsg)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_SndRnicRmnetConfigMsg: Malloc failed!");
        return VOS_ERR;
    }

    /* 填充消息头 */
    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = ACPU_PID_RNIC;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = ACPU_PID_RNIC;
    pstSndMsg->enMsgId                  = ID_RNIC_RMNET_CONFIG_REQ;

    /* 填充消息 */
    pstSndMsg->enModemType              = pstConfigInfo->enModemType;
    pstSndMsg->enRmnetStatus            = pstConfigInfo->enRmnetStatus;
    pstSndMsg->enIpType                 = pstConfigInfo->enIpType;
    pstSndMsg->ucPdnId                  = pstConfigInfo->ucPdnId;
    pstSndMsg->ucRabId                  = pstConfigInfo->ucRabId;
    pstSndMsg->ucRmNetId                = pstConfigInfo->ucRmNetId;
    pstSndMsg->usModemId                = pstConfigInfo->usModemId;

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(ACPU_PID_RNIC, pstSndMsg))
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_SndRnicRmnetConfigMsg: Send msg failed!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : RNIC_SendConfigInfoMsg
 功能描述  : 可维可测，记录外部调用点的初始入参
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月28日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID RNIC_MNTN_SndRmnetConfigInfoMsg(
    RNIC_RMNET_CONFIG_STRU             *pstConfigInfo
)
{
    RNIC_RMNET_CONFIG_REQ_STRU          *pstSndMsg = VOS_NULL_PTR;

    /* 内存分配 */
    pstSndMsg = (RNIC_RMNET_CONFIG_REQ_STRU *)PS_ALLOC_MSG(ACPU_PID_RNIC,
                        sizeof(RNIC_RMNET_CONFIG_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSndMsg)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_SndRnicRmnetConfigMsg: Malloc failed!");
        return;
    }

    /* 填充消息 */
    pstSndMsg->enModemType              = pstConfigInfo->enModemType;
    pstSndMsg->enRmnetStatus            = pstConfigInfo->enRmnetStatus;
    pstSndMsg->enIpType                 = pstConfigInfo->enIpType;
    pstSndMsg->ucPdnId                  = pstConfigInfo->ucPdnId;
    pstSndMsg->ucRabId                  = pstConfigInfo->ucRabId;
    pstSndMsg->ucRmNetId                = pstConfigInfo->ucRmNetId;
    pstSndMsg->usModemId                = pstConfigInfo->usModemId;

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = ACPU_PID_RNIC;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = ACPU_PID_RNIC;
    pstSndMsg->enMsgId                  = ID_RNIC_MNTN_RMNET_CONFIG_INFO;

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(ACPU_PID_RNIC, pstSndMsg))
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_SndRnicRmnetConfigMsg: Send msg failed!");
        return;
    }

    return;
}

/* Modified by m00217266 for L-C互操作项目, 2014-01-06, End */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

