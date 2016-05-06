/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMtaMbms.c
  版 本 号   : 初稿
  作    者   : w00316404
  生成日期   : 2015年5月22日
  最近修改   :
  功能描述   : MTA模块处理MBMS特性功能
  函数列表   :
  修改历史   :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : eMBMS项目新增

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "TafMtaMbms.h"
#include "TafSdcLib.h"
#include "TafMtaComm.h"
#include "TafMtaMain.h"



/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 */
#define    THIS_FILE_ID                 PS_FILE_ID_TAF_MTA_MBMS_C
/*lint +e767 */

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数实现
*****************************************************************************/

#if((FEATURE_ON == FEATURE_LTE) && (FEATURE_ON == FEATURE_LTE_MBMS))
/*****************************************************************************
 函 数 名  : TAF_MTA_SndLrrcSetMBMSServiceOptionReqMsg
 功能描述  : 给lrrc发送设置MBMS服务特性消息
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
VOS_VOID TAF_MTA_SndLrrcSetMBMSServiceOptionReqMsg(
    VOS_UINT8                           ucMBMSServiceOption
)
{
    MTA_LRRC_MBMS_SERVICE_OPTION_REQ_STRU      *pstMtaLrrcSetReq = VOS_NULL_PTR;
    VOS_UINT32                                  ulLength;

    /* 申请消息结构内存 */
    ulLength              = sizeof(MTA_LRRC_MBMS_SERVICE_OPTION_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaLrrcSetReq      = (MTA_LRRC_MBMS_SERVICE_OPTION_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaLrrcSetReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrSetCellsrhReqMsg: Alloc msg fail!");
        return;
    }

    /* 构造消息结构体 */
    MTA_FILL_MSG_HEADER(&pstMtaLrrcSetReq->stMsgHeader, PS_PID_ERRC);
    pstMtaLrrcSetReq->stMsgHeader.ulMsgName         = ID_MTA_LRRC_MBMS_SERVICE_OPTION_REQ;
    pstMtaLrrcSetReq->enOption                      = ucMBMSServiceOption;

    /* 传递给消息包内容 */
    PS_MEM_SET(pstMtaLrrcSetReq->aucReserved, 0, sizeof(pstMtaLrrcSetReq->aucReserved));

    /* 发送消息到LRRC */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaLrrcSetReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcSetMBMSServiceOptionReqMsg: Send msg fail!");
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtMBMSServiceOptionSetReq
 功能描述  : MTA处理^MBMSCMD="MBMS_SERVICE_ENABLER",<param1>命令，设置MBMS服务特性
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
VOS_VOID TAF_MTA_RcvAtMBMSServiceOptionSetReq(
    VOS_VOID                           *pMsg
)
{

    AT_MTA_MSG_STRU                                        *pstSetReq = VOS_NULL_PTR;
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
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_OPTION_SET_CNF))
    {
        ulResult  = VOS_ERR;
    }

    if (ulResult != VOS_OK)
    {
        /* 消息发送失败，给at回复失败*/
        PS_MEM_SET(&stSetCnf, 0x0, sizeof(stSetCnf));
        stSetCnf.enResult= VOS_ERR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_MBMS_SERVICE_OPTION_SET_CNF,
                         sizeof(stSetCnf),
                         (VOS_UINT8*)&stSetCnf );
        return;
    }

    /* 收到at命令请求，发请求消息通知as */
    TAF_MTA_SndLrrcSetMBMSServiceOptionReqMsg(pstSetReq->aucContent[0]);

    /* 启动保护定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_OPTION_SET_CNF,
                                 TI_TAF_MTA_WAIT_SET_MBMS_SERVICE_OPTION_CNF_TIMER_LEN);

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_OPTION_SET_CNF,
                                     (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvLrrcMBMSServiceOptionSetCnf
 功能描述  : MTA收到LRRC设置MBMS服务特性结果
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
VOS_VOID TAF_MTA_RcvLrrcMBMSServiceOptionSetCnf(
    VOS_VOID                           *pLrrcCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf               = VOS_NULL_PTR;
    LRRC_MTA_MBMS_SERVICE_OPTION_CNF_STRU      *pstRcvLrrcCnf           = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                      stSndAtCnf;

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_OPTION_SET_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcMBMSServiceOptionSetCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_OPTION_SET_CNF);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_OPTION_SET_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcMBMSServiceOptionSetCnf: get command buffer failed!");
        return;
    }

    pstRcvLrrcCnf           = (LRRC_MTA_MBMS_SERVICE_OPTION_CNF_STRU *)pLrrcCnfMsg;
    stSndAtCnf.enResult     = pstRcvLrrcCnf->enResult;

    /* 给at回消息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_MBMS_SERVICE_OPTION_SET_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf );

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_OPTION_SET_CNF);
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiWaitLrrcSetMBMSServiceOption
 功能描述  : 设置MBMS服务特性超时的处理函数
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
VOS_VOID TAF_MTA_RcvTiWaitLrrcSetMBMSServiceOption(
    VOS_VOID                           *pMsg
)
{

    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf       = VOS_NULL_PTR;
    AT_APPCTRL_STRU                            *pstAppCtrl      = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                      stSndAtCnf;

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_OPTION_SET_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    pstAppCtrl          = (AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo;

    stSndAtCnf.enResult = MTA_AT_RESULT_OPTION_TIMEOUT;

    /* 上报给AT模块查询错误 */
    TAF_MTA_SndAtMsg(pstAppCtrl,
                     ID_MTA_AT_MBMS_SERVICE_OPTION_SET_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_OPTION_SET_CNF);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndLrrcSetMBMSServiceStateReqMsg
 功能描述  : 给lrrc发送设置MBMS服务状态消息
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
VOS_VOID TAF_MTA_SndLrrcSetMBMSServiceStateReqMsg(
    AT_MTA_MBMS_SERVICE_STATE_SET_REQ_STRU      *pstMBMSServiceState
)
{
    MTA_LRRC_MBMS_SERVICE_STATE_SET_REQ_STRU       *pstMtaLrrcSetReq = VOS_NULL_PTR;
    VOS_UINT32                                      ulLength;

    /* 申请消息结构内存 */
    ulLength              = sizeof(MTA_LRRC_MBMS_SERVICE_STATE_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaLrrcSetReq      = (MTA_LRRC_MBMS_SERVICE_STATE_SET_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaLrrcSetReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcSetMBMSServiceStateReqMsg: Alloc msg fail!");
        return;
    }

    /* 构造消息结构体 */
    MTA_FILL_MSG_HEADER(&pstMtaLrrcSetReq->stMsgHeader, PS_PID_ERRC);
    pstMtaLrrcSetReq->stMsgHeader.ulMsgName         = ID_MTA_LRRC_MBMS_SERVICE_STATE_SET_REQ;
    pstMtaLrrcSetReq->enStateSet                    = pstMBMSServiceState->enStateSet;
    pstMtaLrrcSetReq->ulAreaId                      = pstMBMSServiceState->ulAreaId;
    pstMtaLrrcSetReq->stTMGI.ulMbmsSerId            = pstMBMSServiceState->stTMGI.ulMbmsSerId;
    pstMtaLrrcSetReq->stTMGI.stPlmnId.ulMcc         = pstMBMSServiceState->stTMGI.stPlmnId.ulMcc;
    pstMtaLrrcSetReq->stTMGI.stPlmnId.ulMnc         = pstMBMSServiceState->stTMGI.stPlmnId.ulMnc;

    TAF_SDC_ConvertPlmnId2NasStyle(&pstMtaLrrcSetReq->stTMGI.stPlmnId);

    /* 发送消息到LRRC */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaLrrcSetReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcSetMBMSServiceStateReqMsg: Send msg fail!");
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtMBMSServiceStateSetReq
 功能描述  : MTA处理^MBMSCMD="ACTIVATE",<param1>,<param2>
                    ^MBMSCMD="DEACTIVATE",<param1>,<param2>
                    ^MBMSCMD="DEACTIVATE_ALL"
             命令，设置MBMS服务状态
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
VOS_VOID TAF_MTA_RcvAtMBMSServiceStateSetReq(
    VOS_VOID                           *pMsg
)
{

    AT_MTA_MSG_STRU                                        *pstSetReq = VOS_NULL_PTR;
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
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_STATE_SET_CNF))
    {
        ulResult  = VOS_ERR;
    }

    if (ulResult != VOS_OK)
    {
        /* 消息发送失败，给at回复失败*/
        PS_MEM_SET(&stSetCnf, 0x0, sizeof(stSetCnf));
        stSetCnf.enResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_MBMS_SERVICE_STATE_SET_CNF,
                         sizeof(stSetCnf),
                         (VOS_UINT8*)&stSetCnf );
        return;
    }

    /* 收到at命令请求，发请求消息通知as */
    TAF_MTA_SndLrrcSetMBMSServiceStateReqMsg((AT_MTA_MBMS_SERVICE_STATE_SET_REQ_STRU *)pstSetReq->aucContent);

    /* 启动保护定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_STATE_SET_CNF,
                                 TI_TAF_MTA_WAIT_SET_MBMS_SERVICE_STATE_CNF_TIMER_LEN);

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_STATE_SET_CNF,
                                     (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvLrrcMBMSServiceStateSetCnf
 功能描述  : MTA收到LRRC设置MBMS服务状态结果
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
VOS_VOID TAF_MTA_RcvLrrcMBMSServiceStateSetCnf(
    VOS_VOID                           *pLrrcCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf               = VOS_NULL_PTR;
    LRRC_MTA_MBMS_SERVICE_STATE_SET_CNF_STRU   *pstRcvLrrcCnf           = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                      stSndAtCnf;

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_STATE_SET_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcMBMSServiceStateSetCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_STATE_SET_CNF);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_STATE_SET_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcMBMSServiceStateSetCnf: get command buffer failed!");
        return;
    }

    pstRcvLrrcCnf           = (LRRC_MTA_MBMS_SERVICE_STATE_SET_CNF_STRU *)pLrrcCnfMsg;
    stSndAtCnf.enResult     = pstRcvLrrcCnf->enResult;

    /* 给at回消息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_MBMS_SERVICE_STATE_SET_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf );

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_STATE_SET_CNF);
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiWaitLrrcSetMBMSServiceState
 功能描述  : 设置MBMS服务状态超时的处理函数
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
VOS_VOID TAF_MTA_RcvTiWaitLrrcSetMBMSServiceState(
    VOS_VOID                           *pMsg
)
{

    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf       = VOS_NULL_PTR;
    AT_APPCTRL_STRU                            *pstAppCtrl      = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                      stSndAtCnf;

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_STATE_SET_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    pstAppCtrl          = (AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo;

    stSndAtCnf.enResult = MTA_AT_RESULT_OPTION_TIMEOUT;

    /* 上报给AT模块查询错误 */
    TAF_MTA_SndAtMsg(pstAppCtrl,
                     ID_MTA_AT_MBMS_SERVICE_STATE_SET_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_STATE_SET_CNF);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndLrrcSetMBMSPreferenceReqMsg
 功能描述  : 给lrrc发送设置MBMS广播模式消息
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
VOS_VOID TAF_MTA_SndLrrcSetMBMSPreferenceReqMsg(
    VOS_UINT8                           ucMBMSCastMode
)
{
    MTA_LRRC_MBMS_PREFERENCE_SET_REQ_STRU      *pstMtaLrrcSetReq = VOS_NULL_PTR;
    VOS_UINT32                                  ulLength;

    /* 申请消息结构内存 */
    ulLength              = sizeof(MTA_LRRC_MBMS_PREFERENCE_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaLrrcSetReq      = (MTA_LRRC_MBMS_PREFERENCE_SET_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaLrrcSetReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcSetMBMSPreferenceReqMsg: Alloc msg fail!");
        return;
    }

    /* 构造消息结构体 */
    MTA_FILL_MSG_HEADER(&pstMtaLrrcSetReq->stMsgHeader, PS_PID_ERRC);
    pstMtaLrrcSetReq->stMsgHeader.ulMsgName         = ID_MTA_LRRC_MBMS_PREFERENCE_SET_REQ;
    pstMtaLrrcSetReq->enCastMode                    = ucMBMSCastMode;

    /* 传递给消息包内容 */
    PS_MEM_SET(pstMtaLrrcSetReq->aucReserved, 0, sizeof(pstMtaLrrcSetReq->aucReserved));

    /* 发送消息到LRRC */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaLrrcSetReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcSetMBMSPreferenceReqMsg: Send msg fail!");
        return;
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtMBMSPreferenceSetReq
 功能描述  : MTA处理^MBMSCMD="MBMS_PREFERENCE",<param1>命令，设置MBMS广播模式
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
VOS_VOID TAF_MTA_RcvAtMBMSPreferenceSetReq(
    VOS_VOID                           *pMsg
)
{

    AT_MTA_MSG_STRU                                        *pstSetReq = VOS_NULL_PTR;
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
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_PREFERENCE_SET_CNF))
    {
        ulResult  = VOS_ERR;
    }

    if (ulResult != VOS_OK)
    {
        /* 消息发送失败，给at回复失败*/
        PS_MEM_SET(&stSetCnf, 0x0, sizeof(stSetCnf));
        stSetCnf.enResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_MBMS_PREFERENCE_SET_CNF,
                         sizeof(stSetCnf),
                         (VOS_UINT8*)&stSetCnf );
        return;
    }

    /* 收到at命令请求，发请求消息通知as */
    TAF_MTA_SndLrrcSetMBMSPreferenceReqMsg(pstSetReq->aucContent[0]);

    /* 启动保护定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_PREFERENCE_SET_CNF,
                                 TI_TAF_MTA_WAIT_SET_MBMS_PREFERENCE_CNF_TIMER_LEN);

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_PREFERENCE_SET_CNF,
                                     (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvLrrcMBMSPreferenceSetCnf
 功能描述  : MTA收到LRRC设置MBMS广播模式结果
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
VOS_VOID TAF_MTA_RcvLrrcMBMSPreferenceSetCnf(
    VOS_VOID                           *pLrrcCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf               = VOS_NULL_PTR;
    LRRC_MTA_MBMS_PREFERENCE_SET_CNF_STRU      *pstRcvLrrcCnf           = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                      stSndAtCnf;

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_PREFERENCE_SET_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcMBMSPreferenceSetCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_PREFERENCE_SET_CNF);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_PREFERENCE_SET_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcMBMSPreferenceSetCnf: get command buffer failed!");
        return;
    }

    pstRcvLrrcCnf           = (LRRC_MTA_MBMS_PREFERENCE_SET_CNF_STRU *)pLrrcCnfMsg;
    stSndAtCnf.enResult     = pstRcvLrrcCnf->enResult;

    /* 给at回消息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_MBMS_PREFERENCE_SET_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf );

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_PREFERENCE_SET_CNF);
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiWaitLrrcSetMBMSPreference
 功能描述  : 设置MBMS广播模式超时的处理函数
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
VOS_VOID TAF_MTA_RcvTiWaitLrrcSetMBMSPreference(
    VOS_VOID                           *pMsg
)
{

    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf       = VOS_NULL_PTR;
    AT_APPCTRL_STRU                            *pstAppCtrl      = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                      stSndAtCnf;

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_PREFERENCE_SET_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    pstAppCtrl          = (AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo;

    stSndAtCnf.enResult = MTA_AT_RESULT_OPTION_TIMEOUT;

    /* 上报给AT模块查询错误 */
    TAF_MTA_SndAtMsg(pstAppCtrl,
                     ID_MTA_AT_MBMS_PREFERENCE_SET_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_PREFERENCE_SET_CNF);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndLrrcSetMBMSPreferenceReqMsg
 功能描述  : 给lrrc发送查询SIB16网络时间消息
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
VOS_VOID TAF_MTA_SndLrrcQrySIB16NetworkTimeReqMsg(VOS_VOID)
{
    MTA_LRRC_SIB16_NETWORK_TIME_QRY_REQ_STRU   *pstMtaLrrcQryReq = VOS_NULL_PTR;
    VOS_UINT32                                  ulLength;

    /* 申请消息结构内存 */
    ulLength              = sizeof(MTA_LRRC_SIB16_NETWORK_TIME_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaLrrcQryReq      = (MTA_LRRC_SIB16_NETWORK_TIME_QRY_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaLrrcQryReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcQrySIB16NetworkTimeReqMsg: Alloc msg fail!");
        return;
    }

    /* 构造消息结构体 */
    MTA_FILL_MSG_HEADER(&pstMtaLrrcQryReq->stMsgHeader, PS_PID_ERRC);
    pstMtaLrrcQryReq->stMsgHeader.ulMsgName         = ID_MTA_LRRC_SIB16_NETWORK_TIME_QRY_REQ;

    /* 传递给消息包内容 */
    PS_MEM_SET(pstMtaLrrcQryReq->aucReserved, 0, sizeof(pstMtaLrrcQryReq->aucReserved));

    /* 发送消息到LRRC */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaLrrcQryReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcQrySIB16NetworkTimeReqMsg: Send msg fail!");
        return;
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtSIB16NetworkTimeQryReq
 功能描述  : MTA处理^MBMSCMD="SIB16_GET_NETWORK_TIME"，查询SIB16网络时间
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
VOS_VOID TAF_MTA_RcvAtSIB16NetworkTimeQryReq(
    VOS_VOID                           *pMsg
)
{

    AT_MTA_MSG_STRU                                        *pstSetReq = VOS_NULL_PTR;
    MTA_AT_MBMS_SIB16_NETWORK_TIME_QRY_CNF_STRU             stQryCnf;
    VOS_UINT32                                              ulResult;

    pstSetReq = (AT_MTA_MSG_STRU *)pMsg;
    ulResult  = VOS_OK;

    /* 模式状态机不在运行且当前不为开机模式，则给at回复失败 */
    if (TAF_SDC_PHONE_MODE_FULL != TAF_SDC_GetCurPhoneMode())
    {
        ulResult  = VOS_ERR;
    }

    /* 如果当前定时器已启动，则给at回复失败 */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_SIB16_NETWORK_TIME_QRY_CNF))
    {
        ulResult  = VOS_ERR;
    }

    if (ulResult != VOS_OK)
    {
        /* 消息发送失败，给at回复失败*/
        PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));
        stQryCnf.enResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_SIB16_NETWORK_TIME_QRY_CNF,
                         sizeof(stQryCnf),
                         (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* 收到at命令请求，发请求消息通知as */
    TAF_MTA_SndLrrcQrySIB16NetworkTimeReqMsg();

    /* 启动保护定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_SIB16_NETWORK_TIME_QRY_CNF,
                                 TI_TAF_MTA_WAIT_QRY_MBMS_SIB16_NETWORK_TIME_CNF_TIMER_LEN);

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_SIB16_NETWORK_TIME_QRY_CNF,
                                     (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvLrrcMBMSSIB16NetworkTimeQryCnf
 功能描述  : MTA收到LRRC查询SIB16网络时间结果
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
VOS_VOID TAF_MTA_RcvLrrcMBMSSIB16NetworkTimeQryCnf(
    VOS_VOID                           *pLrrcCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf               = VOS_NULL_PTR;
    LRRC_MTA_SIB16_NETWORK_TIME_QRY_CNF_STRU   *pstRcvLrrcCnf           = VOS_NULL_PTR;
    VOS_UINT64                                 *pullUTC;
    MTA_AT_MBMS_SIB16_NETWORK_TIME_QRY_CNF_STRU stSndAtCnf;

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_SIB16_NETWORK_TIME_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcMBMSSIB16NetworkTimeQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_SIB16_NETWORK_TIME_QRY_CNF);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_SIB16_NETWORK_TIME_QRY_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcMBMSSIB16NetworkTimeQryCnf: get command buffer failed!");
        return;
    }

    pstRcvLrrcCnf           = (LRRC_MTA_SIB16_NETWORK_TIME_QRY_CNF_STRU *)pLrrcCnfMsg;
    stSndAtCnf.enResult     = pstRcvLrrcCnf->enResult;
    pullUTC                 = (VOS_UINT64 *)stSndAtCnf.aulUTC;
    *pullUTC                = pstRcvLrrcCnf->ullUTC;

    /* 给at回消息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_SIB16_NETWORK_TIME_QRY_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf );

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_SIB16_NETWORK_TIME_QRY_CNF);
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiWaitLrrcQrySIB16NetworkTime
 功能描述  : 查询SIB16网络时间超时的处理函数
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
VOS_VOID TAF_MTA_RcvTiWaitLrrcQrySIB16NetworkTime(
    VOS_VOID                           *pMsg
)
{

    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf       = VOS_NULL_PTR;
    AT_APPCTRL_STRU                            *pstAppCtrl      = VOS_NULL_PTR;
    MTA_AT_MBMS_SIB16_NETWORK_TIME_QRY_CNF_STRU stSndAtCnf;

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_SIB16_NETWORK_TIME_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    pstAppCtrl          = (AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo;

    stSndAtCnf.enResult = MTA_AT_RESULT_OPTION_TIMEOUT;

    /* 上报给AT模块查询错误 */
    TAF_MTA_SndAtMsg(pstAppCtrl,
                     ID_MTA_AT_SIB16_NETWORK_TIME_QRY_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_SIB16_NETWORK_TIME_QRY_CNF);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndLrrcQryBSSISignalLevelReqMsg
 功能描述  : 给lrrc发送查询BSSI信号强度消息
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
VOS_VOID TAF_MTA_SndLrrcQryBSSISignalLevelReqMsg(VOS_VOID)
{
    MTA_LRRC_BSSI_SIGNAL_LEVEL_QRY_REQ_STRU    *pstMtaLrrcQryReq = VOS_NULL_PTR;
    VOS_UINT32                                  ulLength;

    /* 申请消息结构内存 */
    ulLength              = sizeof(MTA_LRRC_BSSI_SIGNAL_LEVEL_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaLrrcQryReq      = (MTA_LRRC_BSSI_SIGNAL_LEVEL_QRY_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaLrrcQryReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcQryBSSISignalLevelReqMsg: Alloc msg fail!");
        return;
    }

    /* 构造消息结构体 */
    MTA_FILL_MSG_HEADER(&pstMtaLrrcQryReq->stMsgHeader, PS_PID_ERRC);
    pstMtaLrrcQryReq->stMsgHeader.ulMsgName         = ID_MTA_LRRC_BSSI_SIGNAL_LEVEL_QRY_REQ;

    /* 传递给消息包内容 */
    PS_MEM_SET(pstMtaLrrcQryReq->aucReserved, 0, sizeof(pstMtaLrrcQryReq->aucReserved));

    /* 发送消息到LRRC */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaLrrcQryReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcQryBSSISignalLevelReqMsg: Send msg fail!");
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtBSSISignalLevelQryReq
 功能描述  : MTA处理^MBMSCMD="BSSI_SIGNAL_LEVEL"，查询BSSI信号强度
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
VOS_VOID TAF_MTA_RcvAtBSSISignalLevelQryReq(
    VOS_VOID                           *pMsg
)
{

    AT_MTA_MSG_STRU                                        *pstSetReq = VOS_NULL_PTR;
    MTA_AT_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF_STRU              stQryCnf;
    VOS_UINT32                                              ulResult;

    pstSetReq = (AT_MTA_MSG_STRU *)pMsg;
    ulResult  = VOS_OK;

    /* 模式状态机不在运行且当前不为开机模式，则给at回复失败 */
    if (TAF_SDC_PHONE_MODE_FULL != TAF_SDC_GetCurPhoneMode())
    {
        ulResult  = VOS_ERR;
    }

    /* 如果当前定时器已启动，则给at回复失败 */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF))
    {
        ulResult  = VOS_ERR;
    }

    if (ulResult != VOS_OK)
    {
        /* 消息发送失败，给at回复失败*/
        PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));
        stQryCnf.enResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_BSSI_SIGNAL_LEVEL_QRY_CNF,
                         sizeof(stQryCnf),
                         (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* 收到at命令请求，发请求消息通知as */
    TAF_MTA_SndLrrcQryBSSISignalLevelReqMsg();

    /* 启动保护定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF,
                                 TI_TAF_MTA_WAIT_QRY_MBMS_BSSI_SIGNAL_LEVEL_CNF_TIMER_LEN);

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF,
                                     (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvLrrcMBMSBSSISignalLevelQryCnf
 功能描述  : MTA收到LRRC查询BSSI信号强度结果
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
VOS_VOID TAF_MTA_RcvLrrcMBMSBSSISignalLevelQryCnf(
    VOS_VOID                           *pLrrcCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf               = VOS_NULL_PTR;
    LRRC_MTA_BSSI_SIGNAL_LEVEL_QRY_CNF_STRU    *pstRcvLrrcCnf           = VOS_NULL_PTR;
    MTA_AT_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF_STRU  stSndAtCnf;

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcMBMSBSSISignalLevelQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcMBMSBSSISignalLevelQryCnf: get command buffer failed!");
        return;
    }

    pstRcvLrrcCnf           = (LRRC_MTA_BSSI_SIGNAL_LEVEL_QRY_CNF_STRU *)pLrrcCnfMsg;
    stSndAtCnf.enResult     = pstRcvLrrcCnf->enResult;
    stSndAtCnf.ucBSSILevel  = pstRcvLrrcCnf->ucBSSILevel;

    /* 给at回消息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_BSSI_SIGNAL_LEVEL_QRY_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf );

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF);
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiWaitLrrcQryBSSISignalLevel
 功能描述  : 查询BSSI信号强度超时的处理函数
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
VOS_VOID TAF_MTA_RcvTiWaitLrrcQryBSSISignalLevel(
    VOS_VOID                           *pMsg
)
{

    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf       = VOS_NULL_PTR;
    AT_APPCTRL_STRU                            *pstAppCtrl      = VOS_NULL_PTR;
    MTA_AT_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF_STRU  stSndAtCnf;

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    pstAppCtrl          = (AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo;

    stSndAtCnf.enResult = MTA_AT_RESULT_OPTION_TIMEOUT;

    /* 上报给AT模块查询错误 */
    TAF_MTA_SndAtMsg(pstAppCtrl,
                     ID_MTA_AT_BSSI_SIGNAL_LEVEL_QRY_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndLrrcQryNetworkInfoReqMsg
 功能描述  : 给lrrc发送查询网络信息消息
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
VOS_VOID TAF_MTA_SndLrrcQryNetworkInfoReqMsg(VOS_VOID)
{
    MTA_LRRC_NETWORK_INFO_QRY_REQ_STRU         *pstMtaLrrcQryReq = VOS_NULL_PTR;
    VOS_UINT32                                  ulLength;

    /* 申请消息结构内存 */
    ulLength              = sizeof(MTA_LRRC_NETWORK_INFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaLrrcQryReq      = (MTA_LRRC_NETWORK_INFO_QRY_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaLrrcQryReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcQryNetworkInfoReqMsg: Alloc msg fail!");
        return;
    }

    /* 构造消息结构体 */
    MTA_FILL_MSG_HEADER(&pstMtaLrrcQryReq->stMsgHeader, PS_PID_ERRC);
    pstMtaLrrcQryReq->stMsgHeader.ulMsgName         = ID_MTA_LRRC_NETWORK_INFO_QRY_REQ;

    /* 传递给消息包内容 */
    PS_MEM_SET(pstMtaLrrcQryReq->aucReserved, 0, sizeof(pstMtaLrrcQryReq->aucReserved));

    /* 发送消息到LRRC */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaLrrcQryReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcQryNetworkInfoReqMsg: Send msg fail!");
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtNetworkInfoQryReq
 功能描述  : MTA处理^MBMSCMD="NETWORK_INFORMATION"，查询网络信息
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
VOS_VOID TAF_MTA_RcvAtNetworkInfoQryReq(
    VOS_VOID                           *pMsg
)
{

    AT_MTA_MSG_STRU                                        *pstSetReq = VOS_NULL_PTR;
    MTA_AT_MBMS_NETWORK_INFO_QRY_CNF_STRU                   stQryCnf;
    VOS_UINT32                                              ulResult;

    pstSetReq = (AT_MTA_MSG_STRU *)pMsg;
    ulResult  = VOS_OK;

    /* 模式状态机不在运行且当前不为开机模式，则给at回复失败 */
    if (TAF_SDC_PHONE_MODE_FULL != TAF_SDC_GetCurPhoneMode())
    {
        ulResult  = VOS_ERR;
    }

    /* 如果当前定时器已启动，则给at回复失败 */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_NETWORK_INFO_QRY_CNF))
    {
        ulResult  = VOS_ERR;
    }

    if (ulResult != VOS_OK)
    {
        /* 消息发送失败，给at回复失败*/
        PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));
        stQryCnf.enResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_NETWORK_INFO_QRY_CNF,
                         sizeof(stQryCnf),
                         (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* 收到at命令请求，发请求消息通知as */
    TAF_MTA_SndLrrcQryNetworkInfoReqMsg();

    /* 启动保护定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_NETWORK_INFO_QRY_CNF,
                                 TI_TAF_MTA_WAIT_QRY_MBMS_NETWORK_INFO_CNF_TIMER_LEN);

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_NETWORK_INFO_QRY_CNF,
                                     (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvLrrcMBMSNetworkInfoQryCnf
 功能描述  : MTA收到LRRC查询网络信息结果
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
VOS_VOID TAF_MTA_RcvLrrcMBMSNetworkInfoQryCnf(
    VOS_VOID                           *pLrrcCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf               = VOS_NULL_PTR;
    LRRC_MTA_NETWORK_INFO_QRY_CNF_STRU         *pstRcvLrrcCnf           = VOS_NULL_PTR;
    MTA_AT_MBMS_NETWORK_INFO_QRY_CNF_STRU       stSndAtCnf;

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_NETWORK_INFO_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcMBMSNetworkInfoQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_NETWORK_INFO_QRY_CNF);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_NETWORK_INFO_QRY_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcMBMSNetworkInfoQryCnf: get command buffer failed!");
        return;
    }

    pstRcvLrrcCnf           = (LRRC_MTA_NETWORK_INFO_QRY_CNF_STRU *)pLrrcCnfMsg;
    stSndAtCnf.enResult     = pstRcvLrrcCnf->enResult;
    stSndAtCnf.ulCellId     = pstRcvLrrcCnf->ulCellId;

    /* 给at回消息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_NETWORK_INFO_QRY_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf );

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_NETWORK_INFO_QRY_CNF);
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiWaitLrrcQryNetworkInfo
 功能描述  : 查询网络信息超时的处理函数
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
VOS_VOID TAF_MTA_RcvTiWaitLrrcQryNetworkInfo(
    VOS_VOID                           *pMsg
)
{

    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf       = VOS_NULL_PTR;
    AT_APPCTRL_STRU                            *pstAppCtrl      = VOS_NULL_PTR;
    MTA_AT_MBMS_NETWORK_INFO_QRY_CNF_STRU       stSndAtCnf;

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_NETWORK_INFO_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    pstAppCtrl          = (AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo;

    stSndAtCnf.enResult = MTA_AT_RESULT_OPTION_TIMEOUT;

    /* 上报给AT模块查询错误 */
    TAF_MTA_SndAtMsg(pstAppCtrl,
                     ID_MTA_AT_NETWORK_INFO_QRY_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_NETWORK_INFO_QRY_CNF);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndLrrcQryEMBMSStatusReqMsg
 功能描述  : 给lrrc发送查询EMBMS功能状态消息
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
VOS_VOID TAF_MTA_SndLrrcQryEMBMSStatusReqMsg(VOS_VOID)
{
    MTA_LRRC_EMBMS_STATUS_QRY_REQ_STRU         *pstMtaLrrcQryReq = VOS_NULL_PTR;
    VOS_UINT32                                  ulLength;

    /* 申请消息结构内存 */
    ulLength              = sizeof(MTA_LRRC_EMBMS_STATUS_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaLrrcQryReq      = (MTA_LRRC_EMBMS_STATUS_QRY_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaLrrcQryReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcQryEMBMSStatusReqMsg: Alloc msg fail!");
        return;
    }

    /* 构造消息结构体 */
    MTA_FILL_MSG_HEADER(&pstMtaLrrcQryReq->stMsgHeader, PS_PID_ERRC);
    pstMtaLrrcQryReq->stMsgHeader.ulMsgName         = ID_MTA_LRRC_EMBMS_STATUS_QRY_REQ;

    /* 传递给消息包内容 */
    PS_MEM_SET(pstMtaLrrcQryReq->aucReserved, 0, sizeof(pstMtaLrrcQryReq->aucReserved));

    /* 发送消息到LRRC */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaLrrcQryReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcQryEMBMSStatusReqMsg: Send msg fail!");
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtEMBMSStatusQryReq
 功能描述  : MTA处理^MBMSCMD="MODEM_STATUS"，查询eMBMS功能状态
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
VOS_VOID TAF_MTA_RcvAtEMBMSStatusQryReq(
    VOS_VOID                           *pMsg
)
{

    AT_MTA_MSG_STRU                                        *pstSetReq = VOS_NULL_PTR;
    MTA_AT_EMBMS_STATUS_QRY_CNF_STRU                        stQryCnf;
    VOS_UINT32                                              ulResult;

    pstSetReq = (AT_MTA_MSG_STRU *)pMsg;
    ulResult  = VOS_OK;

    /* 模式状态机不在运行且当前不为开机模式，则给at回复失败 */
    if (TAF_SDC_PHONE_MODE_FULL != TAF_SDC_GetCurPhoneMode())
    {
        ulResult  = VOS_ERR;
    }

    /* 如果当前定时器已启动，则给at回复失败 */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_EMBMS_STATUS_QRY_CNF))
    {
        ulResult  = VOS_ERR;
    }

    if (ulResult != VOS_OK)
    {
        /* 消息发送失败，给at回复失败*/
        PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));
        stQryCnf.enResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_EMBMS_STATUS_QRY_CNF,
                         sizeof(stQryCnf),
                         (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* 收到at命令请求，发请求消息通知as */
    TAF_MTA_SndLrrcQryEMBMSStatusReqMsg();

    /* 启动保护定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_LRRC_EMBMS_STATUS_QRY_CNF,
                                 TI_TAF_MTA_WAIT_QRY_EMBMS_STATUS_CNF_TIMER_LEN);

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_EMBMS_STATUS_QRY_CNF,
                                     (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvLrrcEMBMSStatusQryCnf
 功能描述  : MTA收到LRRC查询EMBMS功能状态结果
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
VOS_VOID TAF_MTA_RcvLrrcEMBMSStatusQryCnf(
    VOS_VOID                           *pLrrcCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf               = VOS_NULL_PTR;
    LRRC_MTA_EMBMS_STATUS_QRY_CNF_STRU         *pstRcvLrrcCnf           = VOS_NULL_PTR;
    MTA_AT_EMBMS_STATUS_QRY_CNF_STRU            stSndAtCnf;

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_EMBMS_STATUS_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcEMBMSStatusQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_LRRC_EMBMS_STATUS_QRY_CNF);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_EMBMS_STATUS_QRY_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcEMBMSStatusQryCnf: get command buffer failed!");
        return;
    }

    pstRcvLrrcCnf           = (LRRC_MTA_EMBMS_STATUS_QRY_CNF_STRU *)pLrrcCnfMsg;
    stSndAtCnf.enResult     = pstRcvLrrcCnf->enResult;
    stSndAtCnf.enStatus     = pstRcvLrrcCnf->enStatus;

    /* 给at回消息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_EMBMS_STATUS_QRY_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf );

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_EMBMS_STATUS_QRY_CNF);
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiWaitLrrcQryEMBMSStatus
 功能描述  : 查询EMBMS功能状态超时的处理函数
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
VOS_VOID TAF_MTA_RcvTiWaitLrrcQryEMBMSStatus(
    VOS_VOID                           *pMsg
)
{

    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf       = VOS_NULL_PTR;
    AT_APPCTRL_STRU                            *pstAppCtrl      = VOS_NULL_PTR;
    MTA_AT_EMBMS_STATUS_QRY_CNF_STRU            stSndAtCnf;

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_EMBMS_STATUS_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    pstAppCtrl          = (AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo;

    stSndAtCnf.enResult = MTA_AT_RESULT_OPTION_TIMEOUT;

    /* 上报给AT模块查询错误 */
    TAF_MTA_SndAtMsg(pstAppCtrl,
                     ID_MTA_AT_EMBMS_STATUS_QRY_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_EMBMS_STATUS_QRY_CNF);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndLrrcSetMBMSUnsolicitedCfgReqMsg
 功能描述  : 给lrrc发送设置MBMS主动上报配置消息
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
VOS_VOID TAF_MTA_SndLrrcSetMBMSUnsolicitedCfgReqMsg(
    VOS_UINT8                           ucMBMSUnsolicitedCfg
)
{
    MTA_LRRC_MBMS_UNSOLICITED_CFG_SET_REQ_STRU *pstMtaLrrcSetReq = VOS_NULL_PTR;
    VOS_UINT32                                  ulLength;

    /* 申请消息结构内存 */
    ulLength              = sizeof(MTA_LRRC_MBMS_UNSOLICITED_CFG_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaLrrcSetReq      = (MTA_LRRC_MBMS_UNSOLICITED_CFG_SET_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaLrrcSetReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcSetMBMSUnsolicitedCfgReqMsg: Alloc msg fail!");
        return;
    }

    /* 构造消息结构体 */
    MTA_FILL_MSG_HEADER(&pstMtaLrrcSetReq->stMsgHeader, PS_PID_ERRC);
    pstMtaLrrcSetReq->stMsgHeader.ulMsgName         = ID_MTA_LRRC_MBMS_UNSOLICITED_CFG_SET_REQ;
    pstMtaLrrcSetReq->enCfg                         = ucMBMSUnsolicitedCfg;

    /* 传递给消息包内容 */
    PS_MEM_SET(pstMtaLrrcSetReq->aucReserved, 0, sizeof(pstMtaLrrcSetReq->aucReserved));

    /* 发送消息到LRRC */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaLrrcSetReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcSetMBMSUnsolicitedCfgReqMsg: Send msg fail!");
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtMBMSUnsolicitedCfgSetReq
 功能描述  : MTA处理^MBMSEV命令，设置MBMS主动上报配置
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
VOS_VOID TAF_MTA_RcvAtMBMSUnsolicitedCfgSetReq(
    VOS_VOID                           *pMsg
)
{

    AT_MTA_MSG_STRU                                        *pstSetReq = VOS_NULL_PTR;
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
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_UNSOLICITED_CFG_SET_CNF))
    {
        ulResult  = VOS_ERR;
    }

    if (ulResult != VOS_OK)
    {
        /* 消息发送失败，给at回复失败*/
        PS_MEM_SET(&stSetCnf, 0x0, sizeof(stSetCnf));
        stSetCnf.enResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_MBMS_UNSOLICITED_CFG_SET_CNF,
                         sizeof(stSetCnf),
                         (VOS_UINT8*)&stSetCnf );
        return;
    }

    /* 收到at命令请求，发请求消息通知as */
    TAF_MTA_SndLrrcSetMBMSUnsolicitedCfgReqMsg(pstSetReq->aucContent[0]);

    /* 启动保护定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_UNSOLICITED_CFG_SET_CNF,
                                 TI_TAF_MTA_WAIT_SET_MBMS_UNSOLICITED_CFG_CNF_TIMER_LEN);

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_UNSOLICITED_CFG_SET_CNF,
                                     (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvLrrcMBMSUnsolicitedCfgSetCnf
 功能描述  : MTA收到LRRC设置MBMS主动上报配置结果
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
VOS_VOID TAF_MTA_RcvLrrcMBMSUnsolicitedCfgSetCnf(
    VOS_VOID                           *pLrrcCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf               = VOS_NULL_PTR;
    LRRC_MTA_MBMS_UNSOLICITED_CFG_SET_CNF_STRU *pstRcvLrrcCnf           = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                      stSndAtCnf;

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_UNSOLICITED_CFG_SET_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcMBMSUnsolicitedCfgSetCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_UNSOLICITED_CFG_SET_CNF);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_UNSOLICITED_CFG_SET_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcMBMSUnsolicitedCfgSetCnf: get command buffer failed!");
        return;
    }

    pstRcvLrrcCnf           = (LRRC_MTA_MBMS_UNSOLICITED_CFG_SET_CNF_STRU *)pLrrcCnfMsg;
    stSndAtCnf.enResult     = pstRcvLrrcCnf->enResult;

    /* 给at回消息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_MBMS_UNSOLICITED_CFG_SET_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf );

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_UNSOLICITED_CFG_SET_CNF);
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiWaitLrrcSetMBMSUnsolicitedCfg
 功能描述  : 设置MBMS主动上报配置超时的处理函数
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
VOS_VOID TAF_MTA_RcvTiWaitLrrcSetMBMSUnsolicitedCfg(
    VOS_VOID                           *pMsg
)
{

    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf       = VOS_NULL_PTR;
    AT_APPCTRL_STRU                            *pstAppCtrl      = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                      stSndAtCnf;

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_UNSOLICITED_CFG_SET_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    pstAppCtrl          = (AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo;

    stSndAtCnf.enResult = MTA_AT_RESULT_OPTION_TIMEOUT;

    /* 上报给AT模块查询错误 */
    TAF_MTA_SndAtMsg(pstAppCtrl,
                     ID_MTA_AT_MBMS_UNSOLICITED_CFG_SET_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_UNSOLICITED_CFG_SET_CNF);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvLrrcMBMSServiceEventInd
 功能描述  : mta收到lrrc ID_LRRC_MTA_MBMS_SERVICE_EVENT_IND消息处理函数
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvLrrcMBMSServiceEventInd(
    VOS_VOID                           *pMsg
)
{
    LRRC_MTA_MBMS_SERVICE_EVENT_IND_STRU               *pstLrrcMtaInd = VOS_NULL_PTR;
    MTA_AT_MBMS_SERVICE_EVENT_IND_STRU                  stMtaAtInd;
    AT_APPCTRL_STRU                                     stAppCtrl;

    /* 填写主动上报的消息内容 */
    PS_MEM_SET(&stMtaAtInd, 0, sizeof(stMtaAtInd));
    pstLrrcMtaInd           = (LRRC_MTA_MBMS_SERVICE_EVENT_IND_STRU *)pMsg;
    stMtaAtInd.enEvent      = pstLrrcMtaInd->enEvent;

    /* 填写消息头，上报类型为广播事件 */
    PS_MEM_SET(&stAppCtrl, 0, sizeof(stAppCtrl));
    stAppCtrl.usClientId = MTA_CLIENTID_BROADCAST;
    stAppCtrl.ucOpId     = MTA_INVALID_TAB_INDEX;

    /* 给at回消息 */
    TAF_MTA_SndAtMsg(&stAppCtrl,
                     ID_MTA_AT_MBMS_SERVICE_EVENT_IND,
                     sizeof(stMtaAtInd),
                     (VOS_UINT8*)&stMtaAtInd);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndLrrcSetInterestListReqMsg
 功能描述  : 给lrrc发送设置Interest消息
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
VOS_VOID TAF_MTA_SndLrrcSetInterestListReqMsg(
    AT_MTA_MBMS_INTERESTLIST_SET_REQ_STRU           *pstMBMSInterestList
)
{
    MTA_LRRC_INTEREST_LIST_SET_REQ_STRU            *pstMtaLrrcSetReq = VOS_NULL_PTR;
    VOS_UINT32                                      ulLength;

    /* 申请消息结构内存 */
    ulLength              = sizeof(MTA_LRRC_INTEREST_LIST_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaLrrcSetReq      = (MTA_LRRC_INTEREST_LIST_SET_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaLrrcSetReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcSetInterestListReqMsg: Alloc msg fail!");
        return;
    }

    /* 构造消息结构体 */
    MTA_FILL_MSG_HEADER(&pstMtaLrrcSetReq->stMsgHeader, PS_PID_ERRC);
    pstMtaLrrcSetReq->stMsgHeader.ulMsgName         = ID_MTA_LRRC_INTEREST_LIST_SET_REQ;
    pstMtaLrrcSetReq->bMbmsPriority                 = (VOS_BOOL)pstMBMSInterestList->enMbmsPriority;
    PS_MEM_CPY(pstMtaLrrcSetReq->aulFreqList, pstMBMSInterestList->aulFreqList, sizeof(pstMtaLrrcSetReq->aulFreqList));

    /* 发送消息到LRRC */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaLrrcSetReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcSetInterestListReqMsg: Send msg fail!");
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtMBMSInterestListSetReq
 功能描述  : MTA处理^MBMSINTERESTLIST命令，设置INTERESTLIST请求
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
VOS_VOID TAF_MTA_RcvAtMBMSInterestListSetReq(
    VOS_VOID                           *pMsg
)
{

    AT_MTA_MSG_STRU                                        *pstSetReq = VOS_NULL_PTR;
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
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_INTERESTLIST_SET_CNF))
    {
        ulResult  = VOS_ERR;
    }

    if (ulResult != VOS_OK)
    {
        /* 消息发送失败，给at回复失败*/
        PS_MEM_SET(&stSetCnf, 0x0, sizeof(stSetCnf));
        stSetCnf.enResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_INTEREST_LIST_SET_CNF,
                         sizeof(stSetCnf),
                         (VOS_UINT8*)&stSetCnf );
        return;
    }

    /* 收到at命令请求，发请求消息通知as */
    TAF_MTA_SndLrrcSetInterestListReqMsg((AT_MTA_MBMS_INTERESTLIST_SET_REQ_STRU *)pstSetReq->aucContent);

    /* 启动保护定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_INTERESTLIST_SET_CNF,
                                 TI_TAF_MTA_WAIT_SET_MBMS_INTERESTLIST_CNF_TIMER_LEN);

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_INTERESTLIST_SET_CNF,
                                     (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvLrrcInterestListSetCnf
 功能描述  : MTA收到LRRC设置Interest List结果
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
VOS_VOID TAF_MTA_RcvLrrcInterestListSetCnf(
    VOS_VOID                           *pLrrcCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                        *pstCmdBuf               = VOS_NULL_PTR;
    LRRC_MTA_INTEREST_LIST_SET_CNF_STRU            *pstRcvLrrcCnf           = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                          stSndAtCnf;

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_INTERESTLIST_SET_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcInterestListSetCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_INTERESTLIST_SET_CNF);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_INTERESTLIST_SET_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcInterestListSetCnf: get command buffer failed!");
        return;
    }

    pstRcvLrrcCnf           = (LRRC_MTA_INTEREST_LIST_SET_CNF_STRU *)pLrrcCnfMsg;
    stSndAtCnf.enResult     = pstRcvLrrcCnf->enResult;

    /* 给at回消息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_INTEREST_LIST_SET_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf );

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_INTERESTLIST_SET_CNF);
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiWaitLrrcSetInterestList
 功能描述  : 设置Interest List超时的处理函数
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
VOS_VOID TAF_MTA_RcvTiWaitLrrcSetInterestList(
    VOS_VOID                           *pMsg
)
{

    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf       = VOS_NULL_PTR;
    AT_APPCTRL_STRU                            *pstAppCtrl      = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                      stSndAtCnf;

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_INTERESTLIST_SET_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    pstAppCtrl          = (AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo;

    stSndAtCnf.enResult = MTA_AT_RESULT_OPTION_TIMEOUT;

    /* 上报给AT模块查询错误 */
    TAF_MTA_SndAtMsg(pstAppCtrl,
                     ID_MTA_AT_INTEREST_LIST_SET_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_INTERESTLIST_SET_CNF);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndLrrcQryAvlServiceListReqMsg
 功能描述  : 给lrrc发送查询MBMS可用服务列表消息
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
VOS_VOID TAF_MTA_SndLrrcQryAvlServiceListReqMsg(VOS_VOID)
{
    MTA_LRRC_MBMS_AVL_SERVICE_LIST_QRY_REQ_STRU    *pstMtaLrrcQryReq = VOS_NULL_PTR;
    VOS_UINT32                                      ulLength;

    /* 申请消息结构内存 */
    ulLength              = sizeof(MTA_LRRC_MBMS_AVL_SERVICE_LIST_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaLrrcQryReq      = (MTA_LRRC_MBMS_AVL_SERVICE_LIST_QRY_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaLrrcQryReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcQryAvlServiceListReqMsg: Alloc msg fail!");
        return;
    }

    /* 构造消息结构体 */
    MTA_FILL_MSG_HEADER(&pstMtaLrrcQryReq->stMsgHeader, PS_PID_ERRC);
    pstMtaLrrcQryReq->stMsgHeader.ulMsgName         = ID_MTA_LRRC_MBMS_AVL_SERVICE_LIST_QRY_REQ;

    /* 传递给消息包内容 */
    PS_MEM_SET(pstMtaLrrcQryReq->aucReserved, 0, sizeof(pstMtaLrrcQryReq->aucReserved));

    /* 发送消息到LRRC */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaLrrcQryReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcQryAvlServiceListReqMsg: Send msg fail!");
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtMBMSAvlServiceListQryReq
 功能描述  : MTA处理^MBMSCMD?
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
VOS_VOID TAF_MTA_RcvAtMBMSAvlServiceListQryReq(
    VOS_VOID                           *pMsg
)
{

    AT_MTA_MSG_STRU                                        *pstSetReq = VOS_NULL_PTR;
    MTA_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU               stQryCnf;
    VOS_UINT32                                              ulResult;

    pstSetReq = (AT_MTA_MSG_STRU *)pMsg;
    ulResult  = VOS_OK;

    /* 模式状态机不在运行且当前不为开机模式，则给at回复失败 */
    if (TAF_SDC_PHONE_MODE_FULL != TAF_SDC_GetCurPhoneMode())
    {
        ulResult  = VOS_ERR;
    }

    /* 如果当前定时器已启动，则给at回复失败 */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_AVL_SERVICE_LIST_QRY_CNF))
    {
        ulResult  = VOS_ERR;
    }

    if (ulResult != VOS_OK)
    {
        /* 消息发送失败，给at回复失败*/
        PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));
        stQryCnf.enResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF,
                         sizeof(stQryCnf),
                         (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* 收到at命令请求，发请求消息通知as */
    TAF_MTA_SndLrrcQryAvlServiceListReqMsg();

    /* 启动保护定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_AVL_SERVICE_LIST_QRY_CNF,
                                 TI_TAF_MTA_WAIT_QRY_MBMS_AVL_SERVICE_LIST_CNF_TIMER_LEN);

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_AVL_SERVICE_LIST_QRY_CNF,
                                     (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvLrrcMBMSAvlServiceListQryCnf
 功能描述  : MTA收到LRRC查询MBMS可用服务信息结果
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
VOS_VOID TAF_MTA_RcvLrrcMBMSAvlServiceListQryCnf(
    VOS_VOID                           *pLrrcCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                        *pstCmdBuf               = VOS_NULL_PTR;
    LRRC_MTA_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU    *pstRcvLrrcCnf           = VOS_NULL_PTR;
    MTA_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU       stSndAtCnf;
    VOS_UINT32                                      ulAvlServiceListNum;

    PS_MEM_SET(&stSndAtCnf, 0x0, sizeof(stSndAtCnf));

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_AVL_SERVICE_LIST_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcMBMSAvlServiceListQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_AVL_SERVICE_LIST_QRY_CNF);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_AVL_SERVICE_LIST_QRY_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcMBMSAvlServiceListQryCnf: get command buffer failed!");
        return;
    }

    pstRcvLrrcCnf               = (LRRC_MTA_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU *)pLrrcCnfMsg;
    stSndAtCnf.enResult         = pstRcvLrrcCnf->enResult;
    stSndAtCnf.ulAvlServiceNum  = pstRcvLrrcCnf->ulAvlServiceNum;

    if(0 != stSndAtCnf.ulAvlServiceNum)
    {
        PS_MEM_CPY(&stSndAtCnf.astAvlServices[0], &pstRcvLrrcCnf->astAvlServices[0], sizeof(MTA_AT_MBMS_AVL_SERVICE_STRU) * stSndAtCnf.ulAvlServiceNum);
    }

    for (ulAvlServiceListNum = 0; ulAvlServiceListNum < stSndAtCnf.ulAvlServiceNum; ulAvlServiceListNum++)
    {
        TAF_SDC_PlmnId2Bcd(&stSndAtCnf.astAvlServices[ulAvlServiceListNum].stTMGI.stPlmnId);
    }

    /* 给at回消息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf );

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_AVL_SERVICE_LIST_QRY_CNF);
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiWaitLrrcQryAvlServiceList
 功能描述  : 查询MBMS可用服务列表信息超时的处理函数
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
VOS_VOID TAF_MTA_RcvTiWaitLrrcQryAvlServiceList(
    VOS_VOID                           *pMsg
)
{

    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf       = VOS_NULL_PTR;
    AT_APPCTRL_STRU                            *pstAppCtrl      = VOS_NULL_PTR;
    MTA_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU   stSndAtCnf;

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_AVL_SERVICE_LIST_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    pstAppCtrl          = (AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo;

    stSndAtCnf.enResult = MTA_AT_RESULT_OPTION_TIMEOUT;

    /* 上报给AT模块查询错误 */
    TAF_MTA_SndAtMsg(pstAppCtrl,
                     ID_MTA_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_AVL_SERVICE_LIST_QRY_CNF);

    return;
}
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

