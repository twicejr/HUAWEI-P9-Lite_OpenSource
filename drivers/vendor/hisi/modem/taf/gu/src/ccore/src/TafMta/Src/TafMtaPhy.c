/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMtaPhy.c
  版 本 号   : 初稿
  作    者   : 张鹏/00214637
  生成日期   : 2013年03月11日
  最近修改   :
  功能描述   : 包含MTA模块射频相关函数
  函数列表   :
  修改历史   :
  1.日    期   : 2012年8月30日
    作    者   : 张鹏/00214637
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafMtaPhy.h"
#include "TafMtaMain.h"
#include "TafMtaComm.h"
#include "TafSdcCtx.h"
#include "TafMtaMntn.h"
#include "TafMtaMbms.h"

/* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
#include "NasUtranCtrlInterface.h"
/* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, End */

#include "TafSdcLib.h"




#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

/*lint -e767 修改人: 张鹏 00214637; */
#define    THIS_FILE_ID        PS_FILE_ID_TAF_MTA_PHY_C
/*lint +e767 修改人: 张鹏 00214637; */

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_MTA_SndPhyBodySarReqMsg
 功能描述  : MTA向接入层发送ID_MTA_APM_BODY_SAR_SET_REQ消息
 输入参数  : ulReceiverPid - 接收方pid
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
 修改历史  :
  1.日    期   : 2013年03月11日
    作    者   : z00214637
    修改内容   : 支持BODYSAR

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndPhyBodySarReqMsg(
    MTA_BODY_SAR_STATE_ENUM_UINT16      enState,
    MTA_BODY_SAR_PARA_STRU             *pstBodySarPara
)
{
    VOS_UINT8                           i;
    VOS_UINT32                          ulLength;
    MTA_APM_BODY_SAR_SET_REQ_STRU      *pstMtaPhyBodySarReq = VOS_NULL_PTR;

    /* 申请消息结构内存 */
    ulLength            = sizeof(MTA_APM_BODY_SAR_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaPhyBodySarReq = (MTA_APM_BODY_SAR_SET_REQ_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaPhyBodySarReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndPhyBodySarReqMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_UINT8*)pstMtaPhyBodySarReq + VOS_MSG_HEAD_LENGTH, 0x00, ulLength);

    /* 构造消息结构体 */
    pstMtaPhyBodySarReq->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstMtaPhyBodySarReq->ulSenderPid        = UEPS_PID_MTA;
    pstMtaPhyBodySarReq->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstMtaPhyBodySarReq->ulReceiverPid      = DSP_PID_APM;
    pstMtaPhyBodySarReq->usMsgID            = ID_MTA_APM_BODY_SAR_SET_REQ;
    pstMtaPhyBodySarReq->enState            = enState;

    PS_MEM_CPY((VOS_UINT8*)&pstMtaPhyBodySarReq->stBodySARPara, pstBodySarPara,  sizeof(MTA_BODY_SAR_PARA_STRU));

    /* 实际传到PHY的功率门限值为用户配置的10倍 */
    for (i = 0; i < MTA_BODY_SAR_GBAND_MAX_NUM; i++)
    {
        pstMtaPhyBodySarReq->stBodySARPara.astGBandPara[i].sGPRSPower   *= 10;
        pstMtaPhyBodySarReq->stBodySARPara.astGBandPara[i].sEDGEPower   *= 10;
    }

    for (i = 0; i < MTA_BODY_SAR_WBAND_MAX_NUM; i++)
    {
        pstMtaPhyBodySarReq->stBodySARPara.astWBandPara[i].sPower       *= 10;
    }

    /* 发送消息到 PHY */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaPhyBodySarReq))
    {
        MTA_ERROR_LOG("TAF_MTA_SndPhyBodySarReqMsg(): WARNING:SEND MSG FIAL");
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtBodySarSetReq
 功能描述  : mta收到ID_AT_MTA_BODY_SAR_SET_REQ消息处理函数
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年03月11日
    作    者   : z00214637
    修改内容   : 支持^BODYSARON新增函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtBodySarSetReq(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                    *pstBodySarReqMsg    = VOS_NULL_PTR;
    AT_MTA_BODY_SAR_SET_REQ_STRU       *pstBodySarReqPara   = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU              stBodySarCnf;
    VOS_UINT32                          ulResult;

    /* 局部变量初始化 */
    pstBodySarReqMsg    = (AT_MTA_MSG_STRU*)pMsg;
    pstBodySarReqPara   = (AT_MTA_BODY_SAR_SET_REQ_STRU*)pstBodySarReqMsg->aucContent;

    /* 如果当前定时器已启动，则直接返回失败 */
    if (TAF_MTA_TIMER_STATUS_STOP != TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_PHY_SET_BODYSAR_CNF))
    {
        stBodySarCnf.enResult = MTA_AT_RESULT_ERROR;

        TAF_MTA_SndAtMsg(&pstBodySarReqMsg->stAppCtrl,
                         ID_MTA_AT_BODY_SAR_SET_CNF,
                         sizeof(stBodySarCnf),
                         (VOS_UINT8*)&stBodySarCnf );
        return;
    }

    /* 收到at的BODYSAR设置请求，发ID_MTA_APM_BODY_SAR_SET_REQ消息通知PHY */
    ulResult = TAF_MTA_SndPhyBodySarReqMsg(pstBodySarReqPara->enState,
                                           &pstBodySarReqPara->stBodySARPara);

    /* 消息发送失败，给AT回复ERROR */
    if (VOS_ERR == ulResult)
    {
        stBodySarCnf.enResult = MTA_AT_RESULT_ERROR;

        TAF_MTA_SndAtMsg(&pstBodySarReqMsg->stAppCtrl,
                          ID_MTA_AT_BODY_SAR_SET_CNF,
                          sizeof(stBodySarCnf),
                          (VOS_UINT8*)&stBodySarCnf );
        return;
    }

    /* 启动保护定时器 */
    if (TAF_MTA_TIMER_START_FAILURE == TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_PHY_SET_BODYSAR_CNF, TI_TAF_MTA_WAIT_PHY_SET_BODYSAR_CNF_TIMER_LEN))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvAtBodySarSetReq: WARNING: Start Timer failed!");
    }

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_PHY_SET_BODYSAR_CNF,
                                     (VOS_UINT8*)&pstBodySarReqMsg->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvPhyBodySarSetCnf
 功能描述  : mta收到ID_APM_MTA_BODY_SAR_SET_CNF消息处理函数
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年03月11日
    作    者   : z00214637
    修改内容   : 支持^BODYSARON新增函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvPhyBodySarSetCnf(VOS_VOID *pMsg)
{
    APM_MTA_BODY_SAR_SET_CNF_STRU      *pstBodySarCnfMsg    = VOS_NULL_PTR;
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf           = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU              stBodySarCnf;

    pstBodySarCnfMsg = (APM_MTA_BODY_SAR_SET_CNF_STRU*)pMsg;

    /* 如果当前定时器不为运行状态 */
    if (TAF_MTA_TIMER_STATUS_RUNING != TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_PHY_SET_BODYSAR_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvPhyBodySarSetCnf: WARNING: Timer was already stop!");
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_PHY_SET_BODYSAR_CNF);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_PHY_SET_BODYSAR_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    /* 将PHY APM返回结果转换后发给AT */
    if (MTA_PHY_RESULT_NO_ERROR == pstBodySarCnfMsg->enResult)
    {
        stBodySarCnf.enResult = MTA_AT_RESULT_NO_ERROR;
    }
    else
    {
        stBodySarCnf.enResult = MTA_AT_RESULT_ERROR;
    }

    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU*)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_BODY_SAR_SET_CNF,
                     sizeof(stBodySarCnf),
                     (VOS_UINT8*)&stBodySarCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_PHY_SET_BODYSAR_CNF);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiWaitPhySetBodySarExpired
 功能描述  : 等待phy BodySar设置回复保护定时器超时的处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
  1.日    期   : 2013年03月11日
    作    者   : z00214637
    修改内容   :支持^BODYSARON新增函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitPhySetBodySarExpired(VOS_VOID *pMsg)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf   = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU              stBodySarCnf;

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_PHY_SET_BODYSAR_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    PS_MEM_SET(&stBodySarCnf, 0x0, sizeof(stBodySarCnf));

    stBodySarCnf.enResult = MTA_AT_RESULT_ERROR;

    /* 把接入层上报的nmr数据上报给AT模块 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_BODY_SAR_SET_CNF,
                     sizeof(stBodySarCnf),
                     (VOS_UINT8*)&stBodySarCnf );

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_PHY_SET_BODYSAR_CNF);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndPhyEmergencyCallStatus
 功能描述  : MTA向接入层发送ID_MTA_APM_EMERGENCY_CALL_STATUS_NTF消息
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
  1.日    期   : 2013年03月11日
    作    者   : z00214637
    修改内容   : 支持温保项目
*****************************************************************************/
VOS_VOID TAF_MTA_SndPhyEmergencyCallStatus(
    MTA_PHY_EMERGENCY_CALL_STATUS_ENUM_UINT16               enState
)
{
    MTA_PHY_EMERGENCY_CALL_STATUS_NOTIFY_STRU              *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulLength;

    /* 申请消息结构内存 */
    ulLength    = sizeof(MTA_PHY_EMERGENCY_CALL_STATUS_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg      = (MTA_PHY_EMERGENCY_CALL_STATUS_NOTIFY_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        MTA_ERROR_LOG("TAF_MTA_SndPhyEmergencyCallStatus: Alloc msg fail!");
        return;
    }

    /* 填写新消息内容 */
    pstMsg->ulSenderCpuId           = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid             = UEPS_PID_MTA;
    pstMsg->ulReceiverCpuId         = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid           = DSP_PID_APM;
    pstMsg->ulLength                = ulLength;
    pstMsg->usMsgID                 = ID_MTA_APM_EMERGENCY_CALL_STATUS_NOTIFY;
    pstMsg->enEmergencyCallStatus   = enState;
    PS_MEM_SET(&(pstMsg->usReserved0), 0x00, sizeof(pstMsg->usReserved0));
    PS_MEM_SET(pstMsg->ausReserved1, 0x00, sizeof(pstMsg->ausReserved1));

    /*发送消息到OAM的指定PID ;*/
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMsg))
    {
        MN_ERR_LOG("TAF_MTA_SndPhyEmergencyCallStatus: PS_SEND_MSG fail.");
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtSetHandleDectReq
 功能描述  : 处理at下发的设置手持位置消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月8日
    作    者   : M00217266
    修改内容   : AP Sensor:

*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtSetHandleDectReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstSetReq       = VOS_NULL_PTR;
    MTA_AT_HANDLEDECT_SET_CNF_STRU      stSetCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usHandleType;

    pstSetReq          = (AT_MTA_MSG_STRU *)pMsg;
    ulResult           = MTA_AT_RESULT_ERROR;
    usHandleType       = pstSetReq->aucContent[0];
    PS_MEM_SET(&stSetCnf, 0x0, sizeof(stSetCnf));

    /* 如果当前定时器已启动，则返回失败 */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_PHY_HANDLEDECT_SET_CNF))
    {
        stSetCnf.enResult = MTA_AT_RESULT_ERROR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                      ID_MTA_AT_HANDLEDECT_SET_CNF,
                      sizeof(stSetCnf),
                      (VOS_UINT8*)&stSetCnf );
        return;
    }

    /* 收到at命令请求，发请求消息通知APM */
    ulResult = TAF_MTA_SndPhySetHandleDectReqMsg(usHandleType);

    if (ulResult != VOS_OK)
    {
        /* 消息发送失败，给at回复失败*/
        stSetCnf.enResult = MTA_AT_RESULT_ERROR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_HANDLEDECT_SET_CNF,
                         sizeof(stSetCnf),
                         (VOS_UINT8*)&stSetCnf );
        return;
    }

    /* 启动保护定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_PHY_HANDLEDECT_SET_CNF,
                        TI_TAF_MTA_WAIT_PHY_HANDLEDECT_SET_CNF_TIMER_LEN);

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_PHY_HANDLEDECT_SET_CNF,
                                     (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtQryHandleDectReq
 功能描述  : 处理at下发的查询cp侧手持位置消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月8日
    作    者   : M00217266
    修改内容   : AP Sensor:

*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtQryHandleDectReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstQryReq       = VOS_NULL_PTR;
    MTA_AT_HANDLEDECT_QRY_CNF_STRU      stQryCnf;
    VOS_UINT32                          ulResult;

    pstQryReq           = (AT_MTA_MSG_STRU *)pMsg;
    ulResult            = MTA_AT_RESULT_ERROR;
    PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));

    /* 如果当前定时器已启动，则返回失败 */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_PHY_HANDLEDECT_QRY_CNF))
    {
        stQryCnf.enResult = MTA_AT_RESULT_ERROR;

        TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                      ID_MTA_AT_HANDLEDECT_QRY_CNF,
                      sizeof(stQryCnf),
                      (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* 收到at命令请求，发请求消息通知APM */
    ulResult = TAF_MTA_SndPhyQryHandleDectReqMsg();

    if (ulResult != VOS_OK)
    {
        /* 消息发送失败，给at回复失败*/
        stQryCnf.enResult = MTA_AT_RESULT_ERROR;

        TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                         ID_MTA_AT_HANDLEDECT_QRY_CNF,
                         sizeof(stQryCnf),
                         (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* 启动保护定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_PHY_HANDLEDECT_QRY_CNF,
                        TI_TAF_MTA_WAIT_PHY_HANDLEDECT_QRY_CNF_TIMER_LEN);

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_PHY_HANDLEDECT_QRY_CNF,
                                     (VOS_UINT8*)&pstQryReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;

}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndPhySetHandleDectReqMsg
 功能描述  : MTA下发的查询cp侧手持位置消息给phy
 输入参数  : VOS_UINT8 ucHandleType
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月8日
    作    者   : M00217266
    修改内容   : AP Sensor:

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndPhySetHandleDectReqMsg(
    VOS_UINT16                          usHandleType
)
{
    VOS_UINT32                          ulLength;
    MTA_APM_HANDLE_DETECT_SET_REQ_STRU *pstMtaPhyReq = VOS_NULL_PTR;

    /* 申请消息结构内存 */
    ulLength            = sizeof(MTA_APM_HANDLE_DETECT_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaPhyReq        = (MTA_APM_HANDLE_DETECT_SET_REQ_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaPhyReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndPhySetHandleDectReqMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_UINT8*)pstMtaPhyReq + VOS_MSG_HEAD_LENGTH, 0x00, ulLength);

    /* 构造消息结构体 */
    pstMtaPhyReq->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMtaPhyReq->ulSenderPid       = UEPS_PID_MTA;
    pstMtaPhyReq->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMtaPhyReq->ulReceiverPid     = DSP_PID_APM;
    pstMtaPhyReq->usMsgID           = ID_MTA_APM_HANDLE_DETECT_SET_REQ;
    pstMtaPhyReq->usHandle          = usHandleType;

    /* 发送消息到 PHY */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaPhyReq))
    {
        MTA_ERROR_LOG("TAF_MTA_SndPhySetHandleDectReqMsg(): WARNING:SEND MSG FIAL");
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : TAF_MTA_SndPhyQryHandleDectReqMsg
 功能描述  : MTA下发的查询cp侧手持位置消息给phy
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月8日
    作    者   : M00217266
    修改内容   : AP Sensor:

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndPhyQryHandleDectReqMsg(VOS_VOID)
{
    VOS_UINT32                          ulLength;
    MTA_APM_HANDLE_DETECT_QRY_REQ_STRU *pstMtaPhyReq = VOS_NULL_PTR;

    /* 申请消息结构内存 */
    ulLength            = sizeof(MTA_APM_HANDLE_DETECT_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaPhyReq        = (MTA_APM_HANDLE_DETECT_QRY_REQ_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaPhyReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndPhyQryHandleDectReqMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_UINT8*)pstMtaPhyReq + VOS_MSG_HEAD_LENGTH, 0x00, ulLength);

    /* 构造消息结构体 */
    pstMtaPhyReq->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMtaPhyReq->ulSenderPid       = UEPS_PID_MTA;
    pstMtaPhyReq->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMtaPhyReq->ulReceiverPid     = DSP_PID_APM;
    pstMtaPhyReq->usMsgID           = ID_MTA_APM_HANDLE_DETECT_QRY_REQ;

    /* 发送消息到 PHY */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaPhyReq))
    {
        MTA_ERROR_LOG("TAF_MTA_SndPhyQryHandleDectReqMsg(): WARNING:SEND MSG FIAL");
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndPhyQryHandleDectReqMsg
 功能描述  : MTA处理物理层配置cp侧手持位置结果
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月8日
    作    者   : M00217266
    修改内容   : AP Sensor:

*****************************************************************************/
VOS_VOID TAF_MTA_RcvPhyHandleDectSetCnf(
    VOS_VOID                           *pMsg
)
{
    APM_MTA_HANDLE_DETECT_SET_CNF_STRU     *pstApmMtaCnf   = VOS_NULL_PTR;
    TAF_MTA_CMD_BUFFER_STRU                *pstCmdBuf   = VOS_NULL_PTR;
    MTA_AT_HANDLEDECT_SET_CNF_STRU          stMtaAtCnf;

    pstApmMtaCnf = (APM_MTA_HANDLE_DETECT_SET_CNF_STRU *)pMsg;

    /* 如果当前定时器不为运行状态 */
    if (TAF_MTA_TIMER_STATUS_RUNING != TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_PHY_HANDLEDECT_SET_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvPhyHandleDectSetCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_PHY_HANDLEDECT_SET_CNF);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_PHY_HANDLEDECT_SET_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    /* 将PHY APM返回结果转换后发给AT */
    if (MTA_PHY_RESULT_NO_ERROR == pstApmMtaCnf->enResult)
    {
        stMtaAtCnf.enResult = MTA_AT_RESULT_NO_ERROR;
    }
    else
    {
        stMtaAtCnf.enResult = MTA_AT_RESULT_ERROR;
    }

    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU*)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_HANDLEDECT_SET_CNF,
                     sizeof(stMtaAtCnf),
                     (VOS_UINT8*)&stMtaAtCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_PHY_HANDLEDECT_SET_CNF);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndPhyQryHandleDectReqMsg
 功能描述  : MTA处理物理层查询cp侧手持位置结果
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月8日
    作    者   : M00217266
    修改内容   : AP Sensor:

*****************************************************************************/
VOS_VOID TAF_MTA_RcvPhyHandleDectQryCnf(
    VOS_VOID                           *pMsg
)
{
    APM_MTA_HANDLE_DETECT_QRY_CNF_STRU     *pstApmMtaCnf   = VOS_NULL_PTR;
    TAF_MTA_CMD_BUFFER_STRU                *pstCmdBuf   = VOS_NULL_PTR;
    MTA_AT_HANDLEDECT_QRY_CNF_STRU          stMtaAtCnf;

    pstApmMtaCnf = (APM_MTA_HANDLE_DETECT_QRY_CNF_STRU *)pMsg;
    PS_MEM_SET((VOS_UINT8*)&stMtaAtCnf, 0x00, sizeof(MTA_AT_HANDLEDECT_QRY_CNF_STRU));

    /* 如果当前定时器不为运行状态 */
    if (TAF_MTA_TIMER_STATUS_RUNING != TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_PHY_HANDLEDECT_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvPhyHandleDectQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_PHY_HANDLEDECT_QRY_CNF);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_PHY_HANDLEDECT_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    /* 将PHY APM返回结果转换后发给AT */
    if (MTA_PHY_RESULT_NO_ERROR == pstApmMtaCnf->enResult)
    {
        stMtaAtCnf.enResult = MTA_AT_RESULT_NO_ERROR;
        stMtaAtCnf.usHandle = pstApmMtaCnf->usHandle;
    }
    else
    {
        stMtaAtCnf.enResult = MTA_AT_RESULT_ERROR;
    }

    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU*)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_HANDLEDECT_QRY_CNF,
                     sizeof(stMtaAtCnf),
                     (VOS_UINT8*)&stMtaAtCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_PHY_HANDLEDECT_QRY_CNF);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiWaitPhySetHandleDectExpired
 功能描述  : MTA处理TI_TAF_MTA_WAIT_PHY_HANDLEDECT_SET_CNF消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月8日
    作    者   : M00217266
    修改内容   : AP Sensor:

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitPhySetHandleDectExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_HANDLEDECT_SET_CNF_STRU      stMtaAtSetCnf;

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_PHY_HANDLEDECT_SET_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        /*定时器超时log*/
        MTA_ERROR_LOG("TAF_MTA_RcvTiWaitPhySetHandleDectExpired: get command buffer failed!");
        return;
    }

    PS_MEM_SET(&stMtaAtSetCnf, 0x0, sizeof(stMtaAtSetCnf));

    stMtaAtSetCnf.enResult = MTA_AT_RESULT_ERROR;

    /* 上报给AT模块错误信息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_HANDLEDECT_SET_CNF,
                     sizeof(stMtaAtSetCnf),
                     (VOS_UINT8*)&stMtaAtSetCnf );


    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiWaitPhyQryHandleDectExpired
 功能描述  : MTA处理TI_TAF_MTA_WAIT_PHY_HANDLEDECT_QRY_CNF消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月8日
    作    者   : M00217266
    修改内容   : AP Sensor:

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitPhyQryHandleDectExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_HANDLEDECT_QRY_CNF_STRU      stMtaAtQryCnf;

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_PHY_HANDLEDECT_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        /*定时器超时log*/
        MTA_ERROR_LOG("TAF_MTA_RcvTiWaitPhyQryHandleDectExpired: get command buffer failed!");
        return;
    }

    PS_MEM_SET(&stMtaAtQryCnf, 0x0, sizeof(stMtaAtQryCnf));

    stMtaAtQryCnf.enResult = MTA_AT_RESULT_ERROR;

    /* 上报给AT模块错误信息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_HANDLEDECT_QRY_CNF,
                     sizeof(stMtaAtQryCnf),
                     (VOS_UINT8*)&stMtaAtQryCnf );


    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_CheckRatModeTypeValid
 功能描述  : 根据当前系统驻留的模式，对请求或回复消息中ratMode进行有效性判断
 输入参数  : AT_MTA_CMD_RATMODE_ENUM_UINT8       enRatMode
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月4日
    作    者   : g00261581
    修改内容   : 新建
  2.日    期   : 2014年06月16日
    作    者   : j00174725
    修改内容   : K3V3 多模多天线特性
*****************************************************************************/
VOS_UINT32 TAF_MTA_CheckRatModeTypeValid(
    AT_MTA_CMD_RATMODE_ENUM_UINT8       enRatMode
)
{
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysCurrMode;
    /* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranctrlMode;

    enUtranctrlMode = NAS_UTRANCTRL_GetCurrUtranMode();
    /* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, End */
    enSysCurrMode   = TAF_SDC_GetSysMode();

    if ( (AT_MTA_CMD_RATMODE_GSM        == enRatMode)
     && (TAF_SDC_SYS_MODE_GSM           == enSysCurrMode) )
    {
        return VOS_OK;
    }

    /* Modify by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
    if ( (AT_MTA_CMD_RATMODE_WCDMA      == enRatMode)
     && (TAF_SDC_SYS_MODE_WCDMA         == enSysCurrMode)
     && (NAS_UTRANCTRL_UTRAN_MODE_FDD   == enUtranctrlMode) )
    {
        return VOS_OK;
    }

    if ( (AT_MTA_CMD_RATMODE_TD         == enRatMode)
     && (TAF_SDC_SYS_MODE_WCDMA         == enSysCurrMode)
     && (NAS_UTRANCTRL_UTRAN_MODE_TDD   == enUtranctrlMode) )
    {
        return VOS_OK;
    }
    /* Modify by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */

    if ((AT_MTA_CMD_RATMODE_LTE == enRatMode)
     && (TAF_SDC_SYS_MODE_LTE   == enSysCurrMode))
    {
        return VOS_OK;
    }

    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndGuPhySetDpdtTestFlagNtfMsg
 功能描述  : MTA发送Set DpdtTest Flag请求消息到GU PHY
 输入参数  : AT_MTA_SET_DPDT_VALUE_REQ_STRU     *pstQryDpdtReq
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月4日
    作    者   : g00261581
    修改内容   : 新建

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndGuPhySetDpdtTestFlagNtfMsg(
    AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU  *pstSetDpdtFlagReq
)
{
    MTA_GUPHY_SET_DPDTTEST_FLAG_NTF_STRU   *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                              ulLength;

    /* 申请消息结构内存 */
    ulLength    = sizeof(MTA_GUPHY_SET_DPDTTEST_FLAG_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg      = (MTA_GUPHY_SET_DPDTTEST_FLAG_NTF_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        MTA_ERROR_LOG("TAF_MTA_SndGuPhySetDpdtTestFlagNtfMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0, ulLength);

    /* 填写新消息内容 */
    pstMsg->ulSenderCpuId           = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid             = UEPS_PID_MTA;
    pstMsg->ulReceiverCpuId         = VOS_LOCAL_CPUID;
    pstMsg->ulLength                = ulLength;
    pstMsg->usMsgID                 = ID_MTA_GUPHY_SET_DPDTTEST_FLAG_NTF;

    if (AT_MTA_CMD_RATMODE_GSM   == pstSetDpdtFlagReq->enRatMode)
    {
        pstMsg->ulReceiverPid       = DSP_PID_GPHY;
    }
    else if (AT_MTA_CMD_RATMODE_WCDMA   == pstSetDpdtFlagReq->enRatMode)
    {
        pstMsg->ulReceiverPid       = DSP_PID_WPHY;
    }
    else if (AT_MTA_CMD_RATMODE_CDMA   == pstSetDpdtFlagReq->enRatMode)
    {
        pstMsg->ulReceiverPid       = DSP_PID_RCM;
    }
    else
    {
    }

    pstMsg->usDpdtTest = (VOS_UINT16)pstSetDpdtFlagReq->ucFlag;

    /* 发送消息到Gu phy */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMsg))
    {
        MTA_ERROR_LOG("TAF_MTA_SndGuPhySetDpdtTestFlagNtfMsg: PS_SEND_MSG fail.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndGuPhySetDpdtValueNtfMsg
 功能描述  : MTA发送Set Dpdt Value请求消息到GU PHY
 输入参数  : AT_MTA_SET_DPDT_VALUE_REQ_STRU     *pstQryDpdtReq
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月4日
    作    者   : g00261581
    修改内容   : 新建

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndGuPhySetDpdtValueNtfMsg(
    AT_MTA_SET_DPDT_VALUE_REQ_STRU     *pstSetDpdtReq
)
{
    MTA_GUPHY_SET_DPDT_VALUE_NTF_STRU  *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    /* 申请消息结构内存 */
    ulLength    = sizeof(MTA_GUPHY_SET_DPDT_VALUE_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg      = (MTA_GUPHY_SET_DPDT_VALUE_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        MTA_ERROR_LOG("TAF_MTA_SndGuPhySetDpdtValueNtfMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0, ulLength);

    /* 填写新消息内容 */
    pstMsg->ulSenderCpuId           = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid             = UEPS_PID_MTA;
    pstMsg->ulReceiverCpuId         = VOS_LOCAL_CPUID;
    pstMsg->ulLength                = ulLength;
    pstMsg->usMsgID                 = ID_MTA_GUPHY_SET_DPDT_VALUE_NTF;

    if (AT_MTA_CMD_RATMODE_GSM   == pstSetDpdtReq->enRatMode)
    {
        pstMsg->ulReceiverPid       = DSP_PID_GPHY;
    }
    else
    {
        pstMsg->ulReceiverPid       = DSP_PID_WPHY;
    }

    pstMsg->ulDpdtValue = pstSetDpdtReq->ulDpdtValue;

    /* 发送消息到Gu phy */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMsg))
    {
        MTA_ERROR_LOG("TAF_MTA_SndGuPhySetDpdtValueNtfMsg: PS_SEND_MSG fail.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndGuPhyQryDpdtValueReqMsg
 功能描述  : MTA发送Qry Dpdt Value请求消息到GU PHY
 输入参数  : AT_MTA_QRY_DPDT_VALUE_REQ_STRU     *pstQryDpdtReq
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月4日
    作    者   : g00261581
    修改内容   : 新建

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndGuPhyQryDpdtValueReqMsg(
    AT_MTA_QRY_DPDT_VALUE_REQ_STRU     *pstQryDpdtReq
)
{
    MTA_GUPHY_QRY_DPDT_VALUE_REQ_STRU  *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    /* 申请消息结构内存 */
    ulLength    = sizeof(MTA_GUPHY_QRY_DPDT_VALUE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg      = (MTA_GUPHY_QRY_DPDT_VALUE_REQ_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        MTA_ERROR_LOG("TAF_MTA_SndGuPhyQryDpdtValueReqMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0, ulLength);

    /* 填写新消息内容 */
    pstMsg->ulSenderCpuId           = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid             = UEPS_PID_MTA;
    pstMsg->ulReceiverCpuId         = VOS_LOCAL_CPUID;
    pstMsg->ulLength                = ulLength;
    pstMsg->usMsgID                 = ID_MTA_GUPHY_QRY_DPDT_VALUE_REQ;

    if (AT_MTA_CMD_RATMODE_GSM   == pstQryDpdtReq->enRatMode)
    {
        pstMsg->ulReceiverPid       = DSP_PID_GPHY;
    }
    else
    {
        pstMsg->ulReceiverPid       = DSP_PID_WPHY;
    }

    /* 发送消息到Gu phy */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMsg))
    {
        MTA_ERROR_LOG("TAF_MTA_SndGuPhyQryDpdtValueReqMsg: PS_SEND_MSG fail.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtSetDpdtTestFlagReq
 功能描述  : 处理at下发的双天线特性开关打开、关闭命令
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月4日
    作    者   : g00261581
    修改内容   : 新建
  2.日    期   : 2014年06月16日
    作    者   : j00174725
    修改内容   : K3V3 多模多天线特性

*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtSetDpdtTestFlagReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstQryReq      = VOS_NULL_PTR;
    AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU  *pstAtMtaQryReq = VOS_NULL_PTR;
    MTA_AT_SET_DPDTTEST_FLAG_CNF_STRU   stMtaAtQryCnf;
    VOS_UINT32                          ulResult;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          ulIsClMode;

    ulIsClMode              = TAF_SDC_IsConfigCLMode();
#endif
    ulResult                = VOS_ERR;
    stMtaAtQryCnf.enResult  = MTA_AT_RESULT_ERROR;

    /* 解析AT发送过来的消息结构 */
    pstQryReq       = (AT_MTA_MSG_STRU *)pMsg;
    pstAtMtaQryReq  = (AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU *)(pstQryReq->aucContent);


    /* Modify by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
    /* 根据RatMode,将消息结构发送至GU phy或者LRRC */
    if ( (AT_MTA_CMD_RATMODE_GSM    == pstAtMtaQryReq->enRatMode)
     ||  (AT_MTA_CMD_RATMODE_WCDMA  == pstAtMtaQryReq->enRatMode) )
    {
        ulResult = TAF_MTA_SndGuPhySetDpdtTestFlagNtfMsg(pstAtMtaQryReq);
    }
    /* Modify by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */

#if (FEATURE_ON == FEATURE_LTE)
    if (AT_MTA_CMD_RATMODE_LTE      == pstAtMtaQryReq->enRatMode)
    {
        ulResult = TAF_MTA_SndTLrrcSetDpdtTestFlagNtfMsg(pstAtMtaQryReq);
    }
#endif

    /* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
    if (AT_MTA_CMD_RATMODE_TD       == pstAtMtaQryReq->enRatMode)
    {
        ulResult = TAF_MTA_SndTLrrcSetDpdtTestFlagNtfMsg(pstAtMtaQryReq);
    }
#endif
    /* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, End */

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    if (AT_MTA_CMD_RATMODE_CDMA    == pstAtMtaQryReq->enRatMode)
    {
    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if (VOS_FALSE == ulIsClMode)
    #endif
        {
            ulResult = TAF_MTA_SndGuPhySetDpdtTestFlagNtfMsg(pstAtMtaQryReq);
        }
    }
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if ((AT_MTA_CMD_RATMODE_CDMA    == pstAtMtaQryReq->enRatMode)
     && (VOS_TRUE                   == ulIsClMode))
    {
        ulResult = TAF_MTA_SndCtasSetDpdtTestFlagNtfMsg(pstAtMtaQryReq);
    }
#endif

    if (VOS_OK == ulResult)
    {
        stMtaAtQryCnf.enResult = MTA_AT_RESULT_NO_ERROR;
    }

    /* MTA回复AT模块DPDT FLAG设置请求结果 */
    TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                    ID_MTA_AT_SET_DPDTTEST_FLAG_CNF,
                    sizeof(stMtaAtQryCnf),
                    (VOS_UINT8 *)&stMtaAtQryCnf);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtSetDpdtValueReq
 功能描述  : 处理at下发的设置DPDT Value值的命令
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月4日
    作    者   : g00261581
    修改内容   : 新建
  4.日    期   : 2014年06月16日
    作    者   : j00174725
    修改内容   : K3V3 多模多天线特性
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtSetDpdtValueReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstQryReq      = VOS_NULL_PTR;
    AT_MTA_SET_DPDT_VALUE_REQ_STRU     *pstAtMtaQryReq = VOS_NULL_PTR;
    MTA_AT_SET_DPDT_VALUE_CNF_STRU      stMtaAtQryCnf;
    VOS_UINT32                          ulResult;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          ulIsClMode;

    ulIsClMode              = TAF_SDC_IsConfigCLMode();
#endif

    ulResult               = VOS_ERR;
    stMtaAtQryCnf.enResult = MTA_AT_RESULT_ERROR;

    /* 解析AT发送过来的消息结构 */
    pstQryReq       = (AT_MTA_MSG_STRU *)pMsg;
    pstAtMtaQryReq  = (AT_MTA_SET_DPDT_VALUE_REQ_STRU *)(pstQryReq->aucContent);


    /* Modify by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
    /* 根据RatMode,将消息结构发送至GU phy或者LRRC */
    if ( (AT_MTA_CMD_RATMODE_GSM        == pstAtMtaQryReq->enRatMode)
     ||  (AT_MTA_CMD_RATMODE_WCDMA      == pstAtMtaQryReq->enRatMode) )
    {
        ulResult = TAF_MTA_SndGuPhySetDpdtValueNtfMsg(pstAtMtaQryReq);
    }
    /* Modify by j00174725 for K3V3 多模多天线特性, 2014-06-16, End */

#if (FEATURE_ON == FEATURE_LTE)
    if (AT_MTA_CMD_RATMODE_LTE          == pstAtMtaQryReq->enRatMode)
    {
        ulResult = TAF_MTA_SndTLrrcSetDpdtValueNtfMsg(pstAtMtaQryReq);
    }
#endif

/* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
    if (AT_MTA_CMD_RATMODE_TD           == pstAtMtaQryReq->enRatMode)
    {
        ulResult = TAF_MTA_SndTLrrcSetDpdtValueNtfMsg(pstAtMtaQryReq);
    }
#endif
/* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, End */

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if ((AT_MTA_CMD_RATMODE_CDMA        == pstAtMtaQryReq->enRatMode)
     && (VOS_TRUE                       == ulIsClMode))
    {
        ulResult = TAF_MTA_SndCtasSetDpdtValueNtfMsg(pstAtMtaQryReq);
    }
#endif

    if (VOS_OK == ulResult)
    {
        stMtaAtQryCnf.enResult = MTA_AT_RESULT_NO_ERROR;
    }

    /* MTA回复AT模块DPDT VALUE设置请求结果 */
    TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                    ID_MTA_AT_SET_DPDT_VALUE_CNF,
                    sizeof(stMtaAtQryCnf),
                    (VOS_UINT8 *)&stMtaAtQryCnf);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtSetDpdtValueInd
 功能描述  : 处理at下发的查询DPDT Value的请求
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月4日
    作    者   : g00261581
    修改内容   : 新建

*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtQryDpdtValueReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstQryReq      = VOS_NULL_PTR;
    AT_MTA_QRY_DPDT_VALUE_REQ_STRU     *pstAtMtaQryReq = VOS_NULL_PTR;
    MTA_AT_QRY_DPDT_VALUE_CNF_STRU      stMtaAtQryCnf;
    VOS_UINT32                          ulResult;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          ulIsClMode;

    ulIsClMode              = TAF_SDC_IsConfigCLMode();
#endif
    ulResult                = VOS_ERR;
    PS_MEM_SET(&stMtaAtQryCnf, 0x0, sizeof(stMtaAtQryCnf));
    stMtaAtQryCnf.enResult = MTA_AT_RESULT_ERROR;

    /* 解析AT发送过来的消息结构 */
    pstQryReq       = (AT_MTA_MSG_STRU *)pMsg;
    pstAtMtaQryReq  = (AT_MTA_QRY_DPDT_VALUE_REQ_STRU *)(pstQryReq->aucContent);

    /* 如果定时器TI_TAF_MTA_WAIT_DPDT_VALUE_QRY_CNF已启动，则返回失败 */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_DPDT_VALUE_QRY_CNF))
    {
        TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                        ID_MTA_AT_QRY_DPDT_VALUE_CNF,
                        sizeof(stMtaAtQryCnf),
                        (VOS_UINT8 *)&stMtaAtQryCnf );
        return;
    }


    /* Modify by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
    /* 根据RatMode,将消息结构发送至GU phy或者LRRC */
    if ( (AT_MTA_CMD_RATMODE_GSM    == pstAtMtaQryReq->enRatMode)
      || (AT_MTA_CMD_RATMODE_WCDMA  == pstAtMtaQryReq->enRatMode) )
    {
        ulResult = TAF_MTA_SndGuPhyQryDpdtValueReqMsg(pstAtMtaQryReq);
    }
    /* Modify by j00174725 for K3V3 多模多天线特性, 2014-06-16, end */

#if (FEATURE_ON == FEATURE_LTE)
    if (AT_MTA_CMD_RATMODE_LTE      == pstAtMtaQryReq->enRatMode)
    {
        ulResult = TAF_MTA_SndTLrrcQryDpdtValueReqMsg(pstAtMtaQryReq);
    }
#endif

/* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
    if ( AT_MTA_CMD_RATMODE_TD      == pstAtMtaQryReq->enRatMode)
    {
        ulResult = TAF_MTA_SndTLrrcQryDpdtValueReqMsg(pstAtMtaQryReq);
    }
#endif
/* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, End */

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if ((AT_MTA_CMD_RATMODE_CDMA    == pstAtMtaQryReq->enRatMode)
     && (VOS_TRUE                   == ulIsClMode))
    {
        ulResult = TAF_MTA_SndCtasQryDpdtValueReqMsg(pstAtMtaQryReq);
    }
#endif

    if (VOS_OK != ulResult)
    {
        TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                        ID_MTA_AT_QRY_DPDT_VALUE_CNF,
                        sizeof(stMtaAtQryCnf),
                        (VOS_UINT8 *)&stMtaAtQryCnf);

        return;
    }

    /* 启动保护定时器TI_TAF_MTA_WAIT_DPDT_VALUE_QRY_CNF */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_DPDT_VALUE_QRY_CNF,
                        TI_TAF_MTA_WAIT_DPDT_VALUE_QRY_CNF_TIMER_LEN);

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_DPDT_VALUE_QRY_CNF,
                                     (VOS_UINT8*)&pstQryReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvGuPhyQryDpdtValueCnf
 功能描述  : MTA收到GU phy层DPDT Value查询回复消息处理函数
 输入参数  : pMsg  -- 消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月4日
    作    者   : g00261581
    修改内容   : 新建
*****************************************************************************/
VOS_VOID TAF_MTA_RcvGuPhyQryDpdtValueCnf(VOS_VOID *pMsg)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf         = VOS_NULL_PTR;
    GUPHY_MTA_QRY_DPDT_VALUE_CNF_STRU  *pstGuPhyMtaQryCnf = VOS_NULL_PTR;
    MTA_AT_QRY_DPDT_VALUE_CNF_STRU      stMtaAtQryCnf;
    TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId;

    /* 局部变量初始化 */
    pstGuPhyMtaQryCnf = (GUPHY_MTA_QRY_DPDT_VALUE_CNF_STRU *)pMsg;
    enTimerId = TI_TAF_MTA_WAIT_DPDT_VALUE_QRY_CNF;

    if (TAF_MTA_TIMER_STATUS_RUNING != TAF_MTA_GetTimerStatus(enTimerId))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvGuPhyQryDpdtValueCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(enTimerId);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(enTimerId);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    /* 构造消息结构体 */
    stMtaAtQryCnf.enResult = MTA_AT_RESULT_NO_ERROR;
    stMtaAtQryCnf.ulDpdtValue = pstGuPhyMtaQryCnf->ulDpdtValue;

    /* 发送消息给AT模块 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                      ID_MTA_AT_QRY_DPDT_VALUE_CNF,
                      sizeof(MTA_AT_QRY_DPDT_VALUE_CNF_STRU),
                      (VOS_UINT8 *)&stMtaAtQryCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiReqDpdtValueQryExpired
 功能描述  : DPDTQRY命令执行超时
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月4日
    作    者   : g00261581
    修改内容   : 新建

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiReqDpdtValueQryExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf   = VOS_NULL_PTR;
    MTA_AT_QRY_DPDT_VALUE_CNF_STRU      stQryDpdtValueCnf;

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_DPDT_VALUE_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    PS_MEM_SET(&stQryDpdtValueCnf, 0x0, sizeof(stQryDpdtValueCnf));

    stQryDpdtValueCnf.enResult = MTA_AT_RESULT_ERROR;

    /* 上报AT模块错误信息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_QRY_DPDT_VALUE_CNF,
                     sizeof(stQryDpdtValueCnf),
                     (VOS_UINT8 *)&stQryDpdtValueCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_DPDT_VALUE_QRY_CNF);

    return;
}

/*lint +e958*/

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : TAF_MTA_SndCtasSetDpdtTestFlagNtfMsg
 功能描述  : MTA发送Set DpdtTest Flag请求消息到CTAS
 输入参数  : AT_MTA_SET_DPDT_VALUE_REQ_STRU     *pstQryDpdtReq
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月18日
    作    者   : h00313353
    修改内容   : 新建

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndCtasSetDpdtTestFlagNtfMsg(
    AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU  *pstSetDpdtFlagReq
)
{
    MTA_CTAS_SET_DPDTTEST_FLAG_NTF_STRU    *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                              ulLength;

    /* 申请消息结构内存 */
    ulLength    = sizeof(MTA_CTAS_SET_DPDTTEST_FLAG_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg      = (MTA_CTAS_SET_DPDTTEST_FLAG_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        MTA_ERROR_LOG("TAF_MTA_SndCtasSetDpdtTestFlagNtfMsg: Alloc msg fail!");

        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0, ulLength);

    /* 填写新消息内容 */
    pstMsg->ulSenderCpuId           = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid             = UEPS_PID_MTA;
    pstMsg->ulReceiverCpuId         = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid           = CPROC_PID_1X_CTAS;
    pstMsg->ulLength                = ulLength;
    pstMsg->ulMsgName               = (VOS_UINT32)ID_MTA_CTAS_SET_DPDTTEST_FLAG_NTF;
    pstMsg->usDpdtTest              = (VOS_UINT16)pstSetDpdtFlagReq->ucFlag;

    /* 发送消息到CTAS */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMsg))
    {
        MTA_ERROR_LOG("TAF_MTA_SndCtasSetDpdtTestFlagNtfMsg: PS_SEND_MSG fail.");

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndCtasSetDpdtValueNtfMsg
 功能描述  : MTA发送Set Dpdt Value请求消息到CTAS
 输入参数  : AT_MTA_SET_DPDT_VALUE_REQ_STRU     *pstQryDpdtReq
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月18日
    作    者   : h00313353
    修改内容   : 新建

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndCtasSetDpdtValueNtfMsg(
    AT_MTA_SET_DPDT_VALUE_REQ_STRU     *pstSetDpdtReq
)
{
    MTA_CTAS_SET_DPDT_VALUE_NTF_STRU   *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    /* 申请消息结构内存 */
    ulLength    = sizeof(MTA_CTAS_SET_DPDT_VALUE_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg      = (MTA_CTAS_SET_DPDT_VALUE_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        MTA_ERROR_LOG("TAF_MTA_SndCtasSetDpdtValueNtfMsg: Alloc msg fail!");

        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0, ulLength);

    /* 填写新消息内容 */
    pstMsg->ulSenderCpuId           = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid             = UEPS_PID_MTA;
    pstMsg->ulReceiverCpuId         = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid           = CPROC_PID_1X_CTAS;
    pstMsg->ulLength                = ulLength;
    pstMsg->ulMsgName               = (VOS_UINT32)ID_MTA_CTAS_SET_DPDT_VALUE_NTF;
    pstMsg->ulDpdtValue             = pstSetDpdtReq->ulDpdtValue;

    /* 发送消息到CTAS */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMsg))
    {
        MTA_ERROR_LOG("TAF_MTA_SndCtasSetDpdtValueNtfMsg: PS_SEND_MSG fail.");

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndCtasQryDpdtValueReqMsg
 功能描述  : MTA发送Qry Dpdt Value请求消息到CTAS
 输入参数  : AT_MTA_QRY_DPDT_VALUE_REQ_STRU     *pstQryDpdtReq
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月18日
    作    者   : h00313353
    修改内容   : 新建

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndCtasQryDpdtValueReqMsg(
    AT_MTA_QRY_DPDT_VALUE_REQ_STRU     *pstQryDpdtReq
)
{
    MTA_CTAS_QRY_DPDT_VALUE_REQ_STRU   *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    /* 申请消息结构内存 */
    ulLength    = sizeof(MTA_CTAS_QRY_DPDT_VALUE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg      = (MTA_CTAS_QRY_DPDT_VALUE_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        MTA_ERROR_LOG("TAF_MTA_SndCtasQryDpdtValueReqMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0, ulLength);

    /* 填写新消息内容 */
    pstMsg->ulSenderCpuId           = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid             = UEPS_PID_MTA;
    pstMsg->ulReceiverCpuId         = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid           = CPROC_PID_1X_CTAS;
    pstMsg->ulLength                = ulLength;
    pstMsg->ulMsgName               = (VOS_UINT32)ID_MTA_CTAS_QRY_DPDT_VALUE_REQ;

    /* 发送消息到CTAS */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMsg))
    {
        MTA_ERROR_LOG("TAF_MTA_SndCtasQryDpdtValueReqMsg: PS_SEND_MSG fail.");

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvCtasQryDpdtValueCnf
 功能描述  : MTA收到CTAS层DPDT Value查询回复消息处理函数
 输入参数  : pMsg  -- 消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月18日
    作    者   : h00313353
    修改内容   : 新建
*****************************************************************************/
VOS_VOID TAF_MTA_RcvCtasQryDpdtValueCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf         = VOS_NULL_PTR;
    CTAS_MTA_QRY_DPDT_VALUE_CNF_STRU   *pstCtasMtaQryCnf  = VOS_NULL_PTR;
    MTA_AT_QRY_DPDT_VALUE_CNF_STRU      stMtaAtQryCnf;
    TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId;

    /* 局部变量初始化 */
    pstCtasMtaQryCnf = (CTAS_MTA_QRY_DPDT_VALUE_CNF_STRU *)pMsg;
    enTimerId        = TI_TAF_MTA_WAIT_DPDT_VALUE_QRY_CNF;
    PS_MEM_SET(&stMtaAtQryCnf, 0x00, sizeof(MTA_AT_QRY_DPDT_VALUE_CNF_STRU));

    if (TAF_MTA_TIMER_STATUS_RUNING != TAF_MTA_GetTimerStatus(enTimerId))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvCtasQryDpdtValueCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(enTimerId);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(enTimerId);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    /* 构造消息结构体 */
    stMtaAtQryCnf.enResult      = MTA_AT_RESULT_NO_ERROR;
    stMtaAtQryCnf.ulDpdtValue   = pstCtasMtaQryCnf->ulDpdtValue;

    /* 发送消息给AT模块 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     (VOS_UINT32)ID_MTA_AT_QRY_DPDT_VALUE_CNF,
                      sizeof(MTA_AT_QRY_DPDT_VALUE_CNF_STRU),
                     (VOS_UINT8 *)&stMtaAtQryCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}
#endif

#if(FEATURE_ON == FEATURE_LTE)
#if 0
/*****************************************************************************
 函 数 名  : TAF_MTA_SndLphySetIsmCoexReqMsg
 功能描述  : 给lphy发送设置命令^SIMCOEX
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MTA_SndLphySetIsmCoexReqMsg(
    AT_MTA_LTE_WIFI_COEX_SET_REQ_STRU           *pstCoexPara
)
{
    VOS_UINT32                                      ulLength;
    MTA_LPHY_LTE_WIFI_COEX_SET_REQ_STRU            *pstMtaLphySetReq = VOS_NULL_PTR;
    VOS_UINT32                                      ulCoexParaPtr;

    /* 申请消息结构内存 */
    ulLength              = sizeof(pstCoexPara->aucCoexPara) + sizeof(MTA_LPHY_LTE_WIFI_COEX_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH - 4;
    pstMtaLphySetReq      = (MTA_LPHY_LTE_WIFI_COEX_SET_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaLphySetReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLphySetIsmCoexReqMsg: Alloc msg fail!");
        return;
    }

    /* 构造消息结构体 */
    MTA_FILL_MSG_HEADER(pstMtaLphySetReq, TLPHY_PID_RTTAGENT);
    pstMtaLphySetReq->usMsgID                       = ID_MTA_LPHY_LTE_WIFI_COEX_SET_REQ;
    pstMtaLphySetReq->usCoexParaNum                 = pstCoexPara->usCoexParaNum;
    pstMtaLphySetReq->usCoexParaSize                = pstCoexPara->usCoexParaSize;
    ulCoexParaPtr                                   = (VOS_UINT32)pstMtaLphySetReq->aucCoexPara;
    PS_MEM_CPY((VOS_UINT8 *)ulCoexParaPtr, pstCoexPara->aucCoexPara, sizeof(pstCoexPara->aucCoexPara));

    /* 发送消息到LPHY */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaLphySetReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndLphySetIsmCoexReqMsg: Send msg fail!");
        return;
    }

    return;
}
#endif
/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtIsmCoexSetReq
 功能描述  : MTA处理^ISMCOEX命令
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtIsmCoexSetReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                                        *pstSetReq               = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                                  stSetCnf;
    VOS_UINT32                                              ulResult;

    pstSetReq = (AT_MTA_MSG_STRU *)pMsg;
    ulResult  = VOS_OK;

    /* 模式状态机不在运行且当前不为开机模式，则给at回复失败 */
    if (TAF_SDC_PHONE_MODE_FULL != TAF_SDC_GetCurPhoneMode())
    {
        ulResult  = VOS_ERR;
    }

    /* 如果当前定时器已启动，则给at回复失败 */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LTE_WIFI_COEX_SET_CNF))
    {
        ulResult  = VOS_ERR;
    }

    if (ulResult != VOS_OK)
    {
        /* 消息发送失败，给at回复失败*/
        PS_MEM_SET(&stSetCnf, 0x0, sizeof(stSetCnf));
        stSetCnf.enResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_LTE_WIFI_COEX_SET_CNF,
                         sizeof(stSetCnf),
                         (VOS_UINT8*)&stSetCnf );
        return;
    }
#if 0
    /* 收到at命令请求，发请求消息通知LPHY*/
    TAF_MTA_SndLphySetIsmCoexReqMsg((AT_MTA_LTE_WIFI_COEX_SET_REQ_STRU *)pstSetReq->aucContent);
#endif

    /* 收到at命令请求，发请求消息通知LRRC*/
    TAF_MTA_SndLrrcSetIsmCoexReqMsg((AT_MTA_LTE_WIFI_COEX_SET_REQ_STRU *)pstSetReq->aucContent);

    /* 启动保护定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_LTE_WIFI_COEX_SET_CNF,
                       TI_TAF_MTA_WAIT_SET_LTE_WIFI_COEX_CNF_TIMER_LEN);

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LTE_WIFI_COEX_SET_CNF,
                                     (VOS_UINT8*)pstSetReq,
                                     sizeof(AT_MTA_LTE_WIFI_COEX_SET_REQ_STRU) + sizeof(AT_MTA_MSG_STRU) - 4);
    return;
}
#if 0
/*****************************************************************************
 函 数 名  : TAF_MTA_RcvLphyIsmCoexSetCnf
 功能描述  : MTA收到LPHY ^ISMCOEX设置结果
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvLphyIsmCoexSetCnf(
    VOS_VOID                           *pLphyCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                        *pstCmdBuf               = VOS_NULL_PTR;
    LPHY_MTA_LTE_WIFI_COEX_SET_CNF_STRU            *pstRcvLphyCnf           = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                          stSndAtCnf;
    AT_MTA_MSG_STRU                                *pstMsg                  = VOS_NULL_PTR;

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LTE_WIFI_COEX_SET_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLphyIsmCoexSetCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LTE_WIFI_COEX_SET_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLphyIsmCoexSetCnf: get command buffer failed!");
        return;
    }

    pstRcvLphyCnf           = (LPHY_MTA_LTE_WIFI_COEX_SET_CNF_STRU *)pLphyCnfMsg;
    stSndAtCnf.enResult     = pstRcvLphyCnf->enResult;

    pstMsg                  = (AT_MTA_MSG_STRU *)pstCmdBuf->pucMsgInfo;

    if (VOS_OK != stSndAtCnf.enResult)
    {
        /* 给at回消息 */
        TAF_MTA_SndAtMsg(&pstMsg->stAppCtrl,
                         ID_MTA_AT_LTE_WIFI_COEX_SET_CNF,
                         sizeof(stSndAtCnf),
                         (VOS_UINT8*)&stSndAtCnf );

        /* 停止保护定时器 */
        TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_LTE_WIFI_COEX_SET_CNF);

        /* 从等待队列中删除消息 */
        TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LTE_WIFI_COEX_SET_CNF);
    }
    else
    {
        /* 发请求消息通知LRRC*/
        TAF_MTA_SndLrrcSetIsmCoexReqMsg((AT_MTA_LTE_WIFI_COEX_SET_REQ_STRU *)pstMsg->aucContent);
    }

    return;
}
#endif
/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiWaitSetIsmCoexList
 功能描述  : 设置命令^ISMCOEX超时的处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增函数
*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitSetIsmCoexList(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf       = VOS_NULL_PTR;
    AT_MTA_MSG_STRU                            *pstMsg          = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                      stSndAtCnf;

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LTE_WIFI_COEX_SET_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    pstMsg              = (AT_MTA_MSG_STRU *)pstCmdBuf->pucMsgInfo;

    stSndAtCnf.enResult = MTA_AT_RESULT_ERROR;

    /* 上报给AT模块查询错误 */
    TAF_MTA_SndAtMsg(&pstMsg->stAppCtrl,
                     ID_MTA_AT_LTE_WIFI_COEX_SET_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LTE_WIFI_COEX_SET_CNF);

    return;
}
#endif

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtRficSsiRdQryReq
 功能描述  : MTA模块收到AT发来的RFICSSIRD请求消息的处理函数
 输入参数  : pMsg   -- AT发送的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月29日
    作    者   : x00316382
    修改内容   : 新增
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtRficSsiRdQryReq(VOS_VOID *pMsg)
{
    VOS_UINT32                              ulLength;
    MTA_AGENT_RFICSSIRD_REQ_STRU           *pstMtaRficSsiRdReq  = VOS_NULL_PTR;
    AT_MTA_MSG_STRU                        *pstAtMtaReqMsg      = VOS_NULL_PTR;     /* 收到AT发来的消息指针 */
    AT_MTA_RFICSSIRD_REQ_STRU              *pstRficSsiRdReq     = VOS_NULL_PTR;

    pstAtMtaReqMsg          = ( AT_MTA_MSG_STRU *)pMsg;
    pstRficSsiRdReq         = ( AT_MTA_RFICSSIRD_REQ_STRU *)pstAtMtaReqMsg->aucContent;

    /* 申请消息结构内存 */
    ulLength                = sizeof(MTA_AGENT_RFICSSIRD_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaRficSsiRdReq      = (MTA_AGENT_RFICSSIRD_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaRficSsiRdReq)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvAtRficSsiRdQryReq: Alloc msg fail!");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstMtaRficSsiRdReq + VOS_MSG_HEAD_LENGTH, 0, ulLength);

    /* 构造消息结构体 */
    MTA_FILL_MSG_HEADER(pstMtaRficSsiRdReq, TLPHY_PID_RTTAGENT);
    pstMtaRficSsiRdReq->usMsgID           = ID_MTA_AGENT_RFIC_SSI_RD_NTF;
    pstMtaRficSsiRdReq->usChannelNo       = pstRficSsiRdReq->usChannelNo;
    pstMtaRficSsiRdReq->usRficReg         = pstRficSsiRdReq->usRficReg;

    /* 发送消息到TLPHY */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaRficSsiRdReq))
    {
        MTA_ERROR_LOG("TAF_MTA_SndTlphyAfclockStatusNtf: Send msg fail!");
    }

    return;

}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTlPhyRficSsiRdInd
 功能描述  : taf模块收到mta发来的RFICSSIRD回复消息的处理函数
 输入参数  : pMsg   -- AT发送的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月29日
    作    者   : x00316382
    修改内容   : 新增
*****************************************************************************/
VOS_VOID TAF_MTA_RcvTlPhyRficSsiRdInd(VOS_VOID *pMsg)
{
    APM_MTA_RFICSSIRD_IND_STRU             *pstRficSsiRdInd = VOS_NULL_PTR;
    MTA_AT_RFICSSIRD_CNF_STRU               stRficSsiRdInd;
    AT_APPCTRL_STRU                         stAppCtrl;

    pstRficSsiRdInd     = (APM_MTA_RFICSSIRD_IND_STRU *)pMsg;

    PS_MEM_SET(&stRficSsiRdInd, 0, sizeof(stRficSsiRdInd));
    PS_MEM_SET(&stAppCtrl, 0, sizeof(stAppCtrl));

    stRficSsiRdInd.ulRegValue   = pstRficSsiRdInd->ulRegValue;
    stAppCtrl.usClientId        = MTA_CLIENTID_BROADCAST;
    stAppCtrl.ucOpId            = MTA_INVALID_TAB_INDEX;

    TAF_MTA_SndAtMsg(&stAppCtrl,
                     ID_MTA_AT_RFICSSIRD_QRY_CNF,
                     sizeof(stRficSsiRdInd),
                     (VOS_UINT8*)&stRficSsiRdInd);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndRcmAfcClkAndXoCoEfReq
 功能描述  : send rcm the afcclk and xocoef req
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月24日
    作    者   : c00299064
    修改内容   : 新增
*****************************************************************************/
VOS_VOID TAF_MTA_SndRcmAfcClkAndXoCoEfQryReq(
    VOS_VOID
)
{
    MTA_RCM_AFC_CLK_INFO_QRY_REQ_STRU  *pstAfcReq;

    pstAfcReq = (MTA_RCM_AFC_CLK_INFO_QRY_REQ_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA,
                                                    sizeof(MTA_RCM_AFC_CLK_INFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstAfcReq)
    {
        return;
    }

    pstAfcReq->ulReceiverPid    =   DSP_PID_RCM;

    PS_MEM_SET((VOS_UINT8*)pstAfcReq + VOS_MSG_HEAD_LENGTH, 0, sizeof(MTA_RCM_AFC_CLK_INFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstAfcReq->usMsgID          =   ID_MTA_RCM_AFC_CLK_INFO_QRY_REQ;

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_MTA, pstAfcReq);

    return;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


