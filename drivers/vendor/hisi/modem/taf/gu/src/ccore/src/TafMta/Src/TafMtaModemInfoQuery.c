/******************************************************************************

                  版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMtaModemInfoQuery.c
  版 本 号   : 初稿
  作    者   : zwx247453
  生成日期   : 2015年10月19日
  最近修改   :
  功能描述   : MTA模块处理AT侧下发查询功能
  函数列表   :
  修改历史   :
  1.日    期   : 2015年10月19日
    作    者   : zwx247453
    修改内容   : Network Monitor新增

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "TafMtaModemInfoQuery.h"
#include "TafSdcLib.h"
#include "TafMtaComm.h"
#include "TafMtaMain.h"
#include "MtaRrcInterface.h"
#include "NasUtranCtrlInterface.h"

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 */
#define    THIS_FILE_ID                 PS_FILE_ID_TAF_MTA_MODEM_INFO_QUERY_C
/*lint +e767 */

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvQryWrrAutotestReq
 功能描述  : MTA处理at命令^WAS
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 新生成函数
  2.日    期   : 2013年3月18日
    作    者   : s00217060
    修改内容   : DTS2013031800705：关机状态下发CWAS回复ERROR
*****************************************************************************/
VOS_VOID TAF_MTA_RcvQryWrrAutotestReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstQryReq       = VOS_NULL_PTR;
    MTA_WRR_AUTOTEST_PARA_STRU         *pstRrcAtQryPara = VOS_NULL_PTR;
    MTA_AT_WRR_AUTOTEST_QRY_CNF_STRU    stQryCnf;
    VOS_UINT32                          ulResult;
    /* 不用UtranMode判断是否给was发送消息，改为平台支持FDD，都给WAS发送消息 */

    pstQryReq          = (AT_MTA_MSG_STRU *)pMsg;
    pstRrcAtQryPara    = (MTA_WRR_AUTOTEST_PARA_STRU *)pstQryReq->aucContent;
    ulResult           = VOS_ERR;

    /* 如果当前定时器已启动，则返回失败 */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_AUTOTEST_QRY_CNF))
    {
        PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));
        stQryCnf.ulResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                      ID_MTA_AT_WRR_AUTOTEST_QRY_CNF,
                      sizeof(stQryCnf),
                      (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* 如果平台支持W模，则发送请求给as，否则给at回复失败 */
    if ( VOS_TRUE == TAF_SDC_IsPlatformSupportUtranFdd() )
    {
        /* 收到at命令请求，发请求消息通知as */
        ulResult = TAF_MTA_SndWrrQryAutotestReqMsg(pstRrcAtQryPara);
    }

    if (ulResult != VOS_OK)
    {
        /* 消息发送失败，给at回复失败*/
        PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));
        stQryCnf.ulResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                         ID_MTA_AT_WRR_AUTOTEST_QRY_CNF,
                         sizeof(stQryCnf),
                         (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* 启动保护定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_WRR_AUTOTEST_QRY_CNF,
                        TI_TAF_MTA_WAIT_WRR_AUTOTEST_QRY_CNF_TIMER_LEN);

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_AUTOTEST_QRY_CNF,
                                     (VOS_UINT8*)&pstQryReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvQryWrrCellInfoReq
 功能描述  : MTA处理at命令^CELLINFO查询小区信息
 输入参数  : void *pMsg
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 新生成函数
  2.日    期   : 2013年3月18日
    作    者   : s00217060
    修改内容   : DTS2013031800705：关机状态下发CWAS回复ERROR
*****************************************************************************/
VOS_VOID TAF_MTA_RcvQryWrrCellInfoReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstQryCellinfoReq = VOS_NULL_PTR;
    MTA_AT_WRR_CELLINFO_QRY_CNF_STRU    stQryCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulAtCmdCellInfo;
    /* 不用UtranMode判断是否给was发送消息，改为平台支持FDD，都给WAS发送消息 */

    ulAtCmdCellInfo        = 0;
    pstQryCellinfoReq      = (AT_MTA_MSG_STRU *)pMsg;
    ulResult               = VOS_ERR;

    PS_MEM_CPY(&ulAtCmdCellInfo, pstQryCellinfoReq->aucContent, sizeof(VOS_UINT32));

    PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));

    /* 如果当前定时器已启动，则给AT回复查询失败 */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_CELLINFO_QRY_CNF))
    {
        stQryCnf.ulResult = VOS_ERR;
        TAF_MTA_SndAtMsg(&pstQryCellinfoReq->stAppCtrl,
                        ID_MTA_AT_WRR_CELLINFO_QRY_CNF,
                        sizeof(stQryCnf),
                        (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* 如果平台支持W模，则发送请求给as，否则给at回复失败 */
    if ( VOS_TRUE == TAF_SDC_IsPlatformSupportUtranFdd() )
    {
        ulResult = TAF_MTA_SndWrrQryCellinfoReqMsg(ulAtCmdCellInfo);
    }

    /* 如果当前的Utran模式不是FDD模式,ulResult为VOS_ERR，
       或者给接入层发送消息失败,ulResult也为VOS_ERR，给AT回复查询失败 */
    if (VOS_OK != ulResult)
    {
        /* 消息发送失败，给at回复失败*/
        stQryCnf.ulResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstQryCellinfoReq->stAppCtrl,
                         ID_MTA_AT_WRR_CELLINFO_QRY_CNF,
                         sizeof(stQryCnf),
                         (VOS_UINT8*)&stQryCnf );

        return;
    }

    /* 启动保护定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_WRR_CELLINFO_QRY_CNF, TI_TAF_MTA_WAIT_WRR_CELLINFO_QRY_CNF_TIMER_LEN);

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_CELLINFO_QRY_CNF,
                                     (VOS_UINT8*)&pstQryCellinfoReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvQryWrrMeanrptReq
 功能描述  : MTA处理^MEANRPT命令
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 新生成函数
  2.日    期   : 2013年3月18日
    作    者   : s00217060
    修改内容   : DTS2013031800705：关机状态下发CWAS回复ERROR
*****************************************************************************/
VOS_VOID TAF_MTA_RcvQryWrrMeanrptReq(
    VOS_VOID                           *pMsg
)
{

    AT_MTA_MSG_STRU                    *pstQryReq = VOS_NULL_PTR;
    MTA_AT_WRR_MEANRPT_QRY_CNF_STRU     stQryCnf;
    VOS_UINT32                          ulResult;
    /* 不用UtranMode判断是否给was发送消息，改为平台支持FDD，都给WAS发送消息 */

    pstQryReq           = (AT_MTA_MSG_STRU *)pMsg;
    ulResult            = VOS_ERR;
    PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));

    /* 如果当前定时器已启动，则给AT回复查询失败 */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_MEANRPT_QRY_CNF))
    {
        stQryCnf.ulResult = VOS_ERR;
        TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                      ID_MTA_AT_WRR_MEANRPT_QRY_CNF,
                      sizeof(stQryCnf),
                      (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* 如果平台支持W模，则发送请求给as，否则给at回复失败 */
    if ( VOS_TRUE == TAF_SDC_IsPlatformSupportUtranFdd() )
    {
        /* 收到at命令请求，发请求消息通知as */
        ulResult = TAF_MTA_SndWrrQryMeanrptReqMsg();
    }

    if (VOS_OK != ulResult)
    {
        /* 消息发送失败，给at回复失败*/
        stQryCnf.ulResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                         ID_MTA_AT_WRR_MEANRPT_QRY_CNF,
                         sizeof(stQryCnf),
                         (VOS_UINT8*)&stQryCnf );

        return;
    }

    /* 启动保护定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_WRR_MEANRPT_QRY_CNF, TI_TAF_MTA_WAIT_WRR_MEANRPT_QRY_CNF_TIMER_LEN);

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_MEANRPT_QRY_CNF,
                                     (VOS_UINT8*)&pstQryReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndWrrQryAutotestReqMsg
 功能描述  : 给as发送mntn查询消息
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月31日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndWrrQryAutotestReqMsg(
    MTA_WRR_AUTOTEST_PARA_STRU         *pAutotestQryPara
)
{
    VOS_UINT32                          ulLength;
    MTA_WRR_AUTOTEST_QRY_REQ_STRU      *pstMtaWrrQryReq = VOS_NULL_PTR;

    /* 申请消息结构内存 */
    ulLength              = sizeof(MTA_WRR_AUTOTEST_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaWrrQryReq       = (MTA_WRR_AUTOTEST_QRY_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaWrrQryReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrQryAutotestReqMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    /* 构造消息结构体 */
    pstMtaWrrQryReq->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMtaWrrQryReq->ulSenderPid       = UEPS_PID_MTA;
    pstMtaWrrQryReq->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMtaWrrQryReq->ulReceiverPid     = WUEPS_PID_WRR;
    pstMtaWrrQryReq->ulMsgName         = ID_MTA_WRR_AUTOTEST_QRY_REQ;

    /* 传递给消息包内容 */
    PS_MEM_CPY(&(pstMtaWrrQryReq->stWrrAutotestPara),
        pAutotestQryPara,
        sizeof(MTA_WRR_AUTOTEST_PARA_STRU));

    /* 发送消息到AS */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaWrrQryReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrQryAutotestReqMsg: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndWrrQryCellinfoReqMsg
 功能描述  : 给as发送Cellinfo查询消息
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月31日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndWrrQryCellinfoReqMsg(
    VOS_UINT32                          ulSetCellInfo
)
{
    VOS_UINT32                          ulLength;
    MTA_WRR_CELLINFO_QRY_REQ_STRU      *pstMtaWrrQryCellinfoReq = VOS_NULL_PTR;

    /* 申请消息结构内存 */
    ulLength                    = sizeof(MTA_WRR_CELLINFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaWrrQryCellinfoReq     = (MTA_WRR_CELLINFO_QRY_REQ_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);
    if (VOS_NULL_PTR == pstMtaWrrQryCellinfoReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrQryCellinfoReqMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    /* 构造消息结构体 */
    pstMtaWrrQryCellinfoReq->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMtaWrrQryCellinfoReq->ulSenderPid       = UEPS_PID_MTA;
    pstMtaWrrQryCellinfoReq->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMtaWrrQryCellinfoReq->ulReceiverPid     = WUEPS_PID_WRR;
    pstMtaWrrQryCellinfoReq->ulMsgName         = ID_MTA_WRR_CELLINFO_QRY_REQ;
    pstMtaWrrQryCellinfoReq->ulSetCellInfo     = ulSetCellInfo;

    /* 发送消息到AS */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaWrrQryCellinfoReq))
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrQryCellinfoReqMsg: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}



/*****************************************************************************
 函 数 名  : TAF_MTA_SndWrrQryMeanrptReqMsg
 功能描述  : 给as发送查询meanrpt查询消息
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月31日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndWrrQryMeanrptReqMsg( VOS_VOID )
{
    VOS_UINT32                          ulLength;
    MTA_WRR_MEANRPT_QRY_REQ_STRU       *pstMtaWrrQryMeanrptReq = VOS_NULL_PTR;

    /* 申请消息结构内存 */
    ulLength                    = sizeof(MTA_WRR_MEANRPT_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaWrrQryMeanrptReq      = (MTA_WRR_MEANRPT_QRY_REQ_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);
    if (VOS_NULL_PTR == pstMtaWrrQryMeanrptReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrQryMeanrptReqMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    /* 构造消息结构体 */
    pstMtaWrrQryMeanrptReq->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMtaWrrQryMeanrptReq->ulSenderPid       = UEPS_PID_MTA;
    pstMtaWrrQryMeanrptReq->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMtaWrrQryMeanrptReq->ulReceiverPid     = WUEPS_PID_WRR;
    pstMtaWrrQryMeanrptReq->ulMsgName         = ID_MTA_WRR_MEASRPT_QRY_REQ;

    /* 发送消息到AS */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaWrrQryMeanrptReq))
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrQryMeanrptReqMsg: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : TAF_MTA_RcvWrrAutotestQryCnf
 功能描述  : MTA收到was回复的MNTN消息
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvWrrAutotestQryCnf(
    VOS_VOID                           *pWrrCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf            = VOS_NULL_PTR;
    WRR_MTA_AUTOTEST_QRY_CNF_STRU      *pstRcvWrrAutotestCnf = VOS_NULL_PTR;
    MTA_AT_WRR_AUTOTEST_QRY_CNF_STRU    stSndAtAutotestCnf;

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_AUTOTEST_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrAutotestQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_WRR_AUTOTEST_QRY_CNF);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_AUTOTEST_QRY_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrAutotestQryCnf: get command buffer failed!");
        return;
    }

    pstRcvWrrAutotestCnf                 = (WRR_MTA_AUTOTEST_QRY_CNF_STRU *)pWrrCnfMsg;
    stSndAtAutotestCnf.ulResult          = pstRcvWrrAutotestCnf->ulResult;
    stSndAtAutotestCnf.stWrrAutoTestRslt.ulRsltNum = pstRcvWrrAutotestCnf->stWrrAutoTestRslt.ulRsltNum;
    PS_MEM_CPY(stSndAtAutotestCnf.stWrrAutoTestRslt.aulRslt,
               pstRcvWrrAutotestCnf->stWrrAutoTestRslt.aulRslt,
               sizeof(pstRcvWrrAutotestCnf->stWrrAutoTestRslt.aulRslt));

    /* 给at回消息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_AUTOTEST_QRY_CNF,
                     sizeof(stSndAtAutotestCnf),
                     (VOS_UINT8*)&stSndAtAutotestCnf );

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_AUTOTEST_QRY_CNF);
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvWrrCellInfoQryCnf
 功能描述  : MTA收到WAS回复的CELLINFO信息
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvWrrCellInfoQryCnf(
    VOS_VOID                           *pWrrCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf            = VOS_NULL_PTR;
    WRR_MTA_CELLINFO_QRY_CNF_STRU      *pstRcvWrrCellinfoCnf = VOS_NULL_PTR;
    MTA_AT_WRR_CELLINFO_QRY_CNF_STRU    stSndAtCellinfoQryCnf;

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_CELLINFO_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrCellInfoQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_WRR_CELLINFO_QRY_CNF);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_CELLINFO_QRY_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrCellInfoQryCnf: get command buffer failed!");
        return;
    }

    pstRcvWrrCellinfoCnf           = (WRR_MTA_CELLINFO_QRY_CNF_STRU *)pWrrCnfMsg;
    stSndAtCellinfoQryCnf.ulResult = pstRcvWrrCellinfoCnf->ulResult;
    PS_MEM_CPY(&(stSndAtCellinfoQryCnf.stWrrCellInfo),
                &(pstRcvWrrCellinfoCnf->stWrrCellInfo),
                sizeof(pstRcvWrrCellinfoCnf->stWrrCellInfo));

    /* 给at回消息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_CELLINFO_QRY_CNF,
                     sizeof(stSndAtCellinfoQryCnf),
                     (VOS_UINT8*)&stSndAtCellinfoQryCnf );

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_CELLINFO_QRY_CNF);
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvWrrMeanrptQryCnf
 功能描述  : 收到was回复的MEANRPT信息
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvWrrMeanrptQryCnf(
    VOS_VOID                           *pWrrCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf           = VOS_NULL_PTR;
    WRR_MTA_MEANRPT_QRY_CNF_STRU       *pstRcvWrrMeanrptCnf = VOS_NULL_PTR;
    MTA_AT_WRR_MEANRPT_QRY_CNF_STRU     stSndAtMeanrptQryCnf;

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_MEANRPT_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrMeanrptQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_WRR_MEANRPT_QRY_CNF);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_MEANRPT_QRY_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrMeanrptQryCnf: get command buffer failed!");
        return;
    }

    pstRcvWrrMeanrptCnf                         = (WRR_MTA_MEANRPT_QRY_CNF_STRU *)pWrrCnfMsg;
    stSndAtMeanrptQryCnf.ulResult               = pstRcvWrrMeanrptCnf->ulResult;
    stSndAtMeanrptQryCnf.stMeanRptRslt.ulRptNum = pstRcvWrrMeanrptCnf->stMeanRptRslt.ulRptNum;
    PS_MEM_CPY((stSndAtMeanrptQryCnf.stMeanRptRslt.astMeanRptInfo), pstRcvWrrMeanrptCnf->stMeanRptRslt.astMeanRptInfo, sizeof(pstRcvWrrMeanrptCnf->stMeanRptRslt.astMeanRptInfo));

    /* 给at回消息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_MEANRPT_QRY_CNF,
                     sizeof(stSndAtMeanrptQryCnf),
                     (VOS_UINT8*)&stSndAtMeanrptQryCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_MEANRPT_QRY_CNF);
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiReqAutotestQryExpired
 功能描述  : CWAS命令执行超时
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiReqAutotestQryExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_WRR_AUTOTEST_QRY_CNF_STRU    stQryAutotestCnf;

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_AUTOTEST_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        /*定时器超时log*/
        MTA_ERROR_LOG("TAF_MTA_RcvTiReqAutotestQryExpired: get command buffer failed!");
        return;
    }

    PS_MEM_SET(&stQryAutotestCnf, 0x0, sizeof(stQryAutotestCnf));

    stQryAutotestCnf.ulResult = VOS_ERR;

    /* 上报给AT模块错误信息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_AUTOTEST_QRY_CNF,
                     sizeof(stQryAutotestCnf),
                     (VOS_UINT8*)&stQryAutotestCnf );


    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;

}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiReqCellInfoQryExpired
 功能描述  : ^CELLINFO执行超时处理
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiReqCellInfoQryExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_WRR_CELLINFO_QRY_CNF_STRU    stCellinfoQryCnf;

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_CELLINFO_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        /*定时器超时log*/
        MTA_ERROR_LOG("TAF_MTA_RcvTiReqCellInfoQryExpired: get command buffer failed!");
        return;
    }

    PS_MEM_SET(&stCellinfoQryCnf, 0x0, sizeof(stCellinfoQryCnf));

    stCellinfoQryCnf.ulResult = VOS_ERR;

    /* 上报给AT模块错误信息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_CELLINFO_QRY_CNF,
                     sizeof(stCellinfoQryCnf),
                     (VOS_UINT8*)&stCellinfoQryCnf );


    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;

}



/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiReqMeanrptQryExpired
 功能描述  : ^MEANRPT执行超时处理
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月29日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiReqMeanrptQryExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_WRR_MEANRPT_QRY_CNF_STRU     stMeanrptQryCnf;

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_MEANRPT_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        /*定时器超时log*/
        MTA_ERROR_LOG("TAF_MTA_RcvTiReqMeanrptQryExpired: get command buffer failed!");
        return;
    }

    PS_MEM_SET(&stMeanrptQryCnf, 0x0, sizeof(stMeanrptQryCnf));

    stMeanrptQryCnf.ulResult = VOS_ERR;

    /* 上报给AT模块错误信息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_MEANRPT_QRY_CNF,
                     sizeof(stMeanrptQryCnf),
                     (VOS_UINT8*)&stMeanrptQryCnf );


    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;

}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtTransModeQryReq
 功能描述  : mta收到ID_AT_MTA_TRANSMODE_QRY_REQ消息处理函数
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 日    期   : 2015年7月30日
 作    者   : lwx277467
 修改内容   : ^TRANSMODE新增函数
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtTransModeQryReq(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                    *pstTransModeQryReq      = VOS_NULL_PTR;
    MTA_AT_TRANSMODE_QRY_CNF_STRU       stTransModeQryCnf;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enRatType;

    pstTransModeQryReq      = (AT_MTA_MSG_STRU *)pMsg;
    enRatType               = TAF_SDC_GetSysMode();
    PS_MEM_SET(&stTransModeQryCnf, 0x0, sizeof(stTransModeQryCnf));

    /* 查询是否在LTE模式下，否则返回失败*/
    if (TAF_SDC_SYS_MODE_LTE != enRatType)
    {
        stTransModeQryCnf.enResult = MTA_AT_RESULT_INCORRECT_PARAMETERS;

        TAF_MTA_SndAtMsg(&pstTransModeQryReq->stAppCtrl,
                      ID_MTA_AT_TRANSMODE_QRY_CNF,
                      sizeof(stTransModeQryCnf),
                      (VOS_UINT8*)&stTransModeQryCnf );

        return;
    }

    /* 如果当前定时器已启动，则返回失败 */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_TRANSMODE_QRY_CNF))
    {
        stTransModeQryCnf.enResult = MTA_AT_RESULT_ERROR;

        TAF_MTA_SndAtMsg(&pstTransModeQryReq->stAppCtrl,
                      ID_MTA_AT_TRANSMODE_QRY_CNF,
                      sizeof(stTransModeQryCnf),
                      (VOS_UINT8*)&stTransModeQryCnf );
        return;
    }

#if (FEATURE_ON == FEATURE_LTE)
    TAF_MTA_SndLrrcTransModeQryReq();

    /* 启动保护定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_TRANSMODE_QRY_CNF, TI_TAF_MTA_WAIT_TRANSMODE_QRY_CNF_TIMER_LEN);

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_TRANSMODE_QRY_CNF,
                                     (VOS_UINT8*)&pstTransModeQryReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));
#else
    stTransModeQryCnf.enResult = MTA_AT_RESULT_ERROR;

    TAF_MTA_SndAtMsg(&pstTransModeQryReq->stAppCtrl,
                  ID_MTA_AT_TRANSMODE_QRY_CNF,
                  sizeof(stTransModeQryCnf),
                  (VOS_UINT8*)&stTransModeQryCnf );
#endif
    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : TAF_MTA_SndLrrcTransModeQryReq
 功能描述  : MTA发消息ID_MTA_LRRC_TRANSMODE_QRY_REQ给LRRC查询LTE传输模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月30日
    作    者   : lwx277467
    修改内容   : 新增^TRANSMODE命令
*****************************************************************************/
VOS_VOID TAF_MTA_SndLrrcTransModeQryReq(VOS_VOID)
{
    VOS_UINT32                           ulLength;
    MTA_LRRC_TRANSMODE_QRY_REQ_STRU     *pstTransModeQryReq = VOS_NULL_PTR;

    /* 申请消息结构内存 */
    ulLength               = sizeof(MTA_LRRC_TRANSMODE_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstTransModeQryReq     = (MTA_LRRC_TRANSMODE_QRY_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);
    if (VOS_NULL_PTR == pstTransModeQryReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcTransModeQryReq: Alloc msg fail!");
        return;
    }

    /* 构造消息结构体 */
    pstTransModeQryReq->stMsgHeader.ulSenderPid       = UEPS_PID_MTA;
    pstTransModeQryReq->stMsgHeader.ulReceiverPid     = PS_PID_ERRC;
    pstTransModeQryReq->stMsgHeader.ulMsgName         = ID_MTA_LRRC_TRANSMODE_QRY_REQ;

    PS_MEM_SET(pstTransModeQryReq->aucReserved, 0, sizeof(pstTransModeQryReq->aucReserved));

    /* 发送消息到LTE */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstTransModeQryReq))
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcTransModeQryReq(): Send MSG Fail!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndLrrcTransModeQryCnf
 功能描述  : MTA收到LTE接入层传输模式查询回复消息处理函数
 输入参数  : pMsg  -- 消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月30日
    作    者   : lwx277467
    修改内容   : 新增^TRANSMODE命令
*****************************************************************************/
VOS_VOID TAF_MTA_RcvLrrcTransModeQryCnf(VOS_VOID *pMsg)
{
    TAF_MTA_CMD_BUFFER_STRU             *pstCmdBuf          = VOS_NULL_PTR;
    LRRC_MTA_TRANSMODE_QRY_CNF_STRU     *pstTransModeQryCnf = VOS_NULL_PTR;
    MTA_AT_TRANSMODE_QRY_CNF_STRU        stMtaAtTransModeQryCnf;

    PS_MEM_SET(&stMtaAtTransModeQryCnf, 0x00, sizeof(MTA_AT_TRANSMODE_QRY_CNF_STRU));

    pstTransModeQryCnf = (LRRC_MTA_TRANSMODE_QRY_CNF_STRU *)pMsg;

    /* 如果当前定时器不为运行状态 */
    if (TAF_MTA_TIMER_STATUS_RUNING != TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_TRANSMODE_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcTransModeQryCnf: Timer was already stoped!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_TRANSMODE_QRY_CNF);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_TRANSMODE_QRY_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvLrrcTransModeQryCnf: No Buffer!");
        return;
    }

    if (MTA_RRC_RESULT_NO_ERROR != pstTransModeQryCnf->enResult)
    {
        stMtaAtTransModeQryCnf.enResult    = MTA_AT_RESULT_ERROR;
    }
    else
    {
        stMtaAtTransModeQryCnf.enResult    = MTA_AT_RESULT_NO_ERROR;
        stMtaAtTransModeQryCnf.ucTransMode = pstTransModeQryCnf->ucTransMode;
    }

    TAF_MTA_SndAtMsg( (AT_APPCTRL_STRU *)(pstCmdBuf->pucMsgInfo),
                      ID_MTA_AT_TRANSMODE_QRY_CNF,
                      sizeof(MTA_AT_TRANSMODE_QRY_CNF_STRU),
                      (VOS_UINT8*)&stMtaAtTransModeQryCnf );

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiWaitLrrcTransModeQryExpired
 功能描述  : 查询LTE传输模式超时的处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
  1.日    期   : 2015年08月04日
    作    者   : lwx277467
    修改内容   : 新增函数
*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitLrrcTransModeQryExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_TRANSMODE_QRY_CNF_STRU       stMtaAtTransModeQryCnf;

    PS_MEM_SET(&stMtaAtTransModeQryCnf, 0, sizeof(MTA_AT_TRANSMODE_QRY_CNF_STRU));

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_TRANSMODE_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        /*定时器超时log*/
        MTA_ERROR_LOG("TAF_MTA_RcvTiWaitLrrcTransModeQryExpired: get command buffer failed!");
        return;
    }

    PS_MEM_SET(&stMtaAtTransModeQryCnf, 0x0, sizeof(stMtaAtTransModeQryCnf));

    stMtaAtTransModeQryCnf.enResult = VOS_ERR;

    /* 上报给AT模块错误信息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_TRANSMODE_QRY_CNF,
                     sizeof(stMtaAtTransModeQryCnf),
                     (VOS_UINT8*)&stMtaAtTransModeQryCnf );


    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}
#endif

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtSetNetMonSCellReq
 功能描述  : 处理at下发的设置MONSC命令
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月19日
    作    者   : zwx247453
    修改内容   : 新建

*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtSetNetMonSCellReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstSetReq = VOS_NULL_PTR;
    MTA_AT_NETMON_CELL_INFO_STRU        stMoncellInfo;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulReceiverPid;

    PS_MEM_SET(&stMoncellInfo, 0, sizeof(MTA_AT_NETMON_CELL_INFO_STRU));
    pstSetReq                     = (AT_MTA_MSG_STRU *)pMsg;
    ulResult                      = VOS_ERR;
    ulMsgName                     = TAF_SDC_SYS_MODE_GSM;
    ulReceiverPid                 = UEPS_PID_GAS;
    stMoncellInfo.enResult        = MTA_AT_RESULT_ERROR;

    /* 如果当前定时器已启动，则返回失败 */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_RRC_NETMON_SCELL_QRY_CNF))
    {
        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_SET_NETMON_SCELL_CNF,
                         sizeof(MTA_AT_NETMON_CELL_INFO_STRU),
                         (VOS_UINT8*)&stMoncellInfo);
        return;
    }

    ulResult = TAF_MTA_GetNetMonSndMsgInfo(&ulMsgName, &ulReceiverPid);
    if (VOS_OK != ulResult)
    {
        /* 消息发送失败，给at回复失败*/
        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_SET_NETMON_SCELL_CNF,
                         sizeof(MTA_AT_NETMON_CELL_INFO_STRU),
                         (VOS_UINT8*)&stMoncellInfo);
        return;
    }

#if (FEATURE_ON == FEATURE_LTE)
    if (PS_PID_ERRC == ulReceiverPid)
    {
        TAF_MTA_SndLrrcSetNetMonCellReq(ulMsgName, ulReceiverPid, MTA_NETMON_SCELL_TYPE);
    }
    else
#endif
    {
        TAF_MTA_SndRrcSetNetMonCellReq(ulMsgName, ulReceiverPid, MTA_NETMON_SCELL_TYPE);
    }

    /* 启动保护定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_RRC_NETMON_SCELL_QRY_CNF,
                                 TI_TAF_MTA_WAIT_RRC_NETMON_SCELL_QRY_CNF_TIMER_LEN);

    /* 添加消息进等待队列 */
   TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_RRC_NETMON_SCELL_QRY_CNF,
                                   (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                    sizeof(AT_APPCTRL_STRU));
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtSetNetMonNCellReq
 功能描述  : 处理at下发的设置MONNC命令
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月19日
    作    者   : zwx247453
    修改内容   : 新建

*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtSetNetMonNCellReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstSetReq = VOS_NULL_PTR;
    MTA_AT_NETMON_CELL_INFO_STRU        stMoncellInfo;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulReceiverPid;

    PS_MEM_SET(&stMoncellInfo, 0, sizeof(MTA_AT_NETMON_CELL_INFO_STRU));
    pstSetReq              = (AT_MTA_MSG_STRU *)pMsg;
    ulResult               = VOS_ERR;
    ulMsgName              = TAF_SDC_SYS_MODE_GSM;
    ulReceiverPid          = UEPS_PID_GAS;
    stMoncellInfo.enResult = MTA_AT_RESULT_ERROR;

    /* 如果当前定时器已启动，则返回失败 */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_RRC_NETMON_NCELL_QRY_CNF))
    {
        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_SET_NETMON_NCELL_CNF,
                         sizeof(MTA_AT_NETMON_CELL_INFO_STRU),
                         (VOS_UINT8*)&stMoncellInfo);
        return;
    }

   ulResult = TAF_MTA_GetNetMonSndMsgInfo(&ulMsgName, &ulReceiverPid);
   if (VOS_OK != ulResult)
   {
       /* 消息发送失败，给at回复失败*/
       TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                        ID_MTA_AT_SET_NETMON_NCELL_CNF,
                        sizeof(MTA_AT_NETMON_CELL_INFO_STRU),
                        (VOS_UINT8*)&stMoncellInfo);
       return;
   }

   /* 收到at命令请求，发请求消息通知AS */
#if (FEATURE_ON == FEATURE_LTE)
   if (PS_PID_ERRC == ulReceiverPid)
   {
       TAF_MTA_SndLrrcSetNetMonCellReq(ulMsgName, ulReceiverPid, MTA_NETMON_NCELL_TYPE);
   }
   else
#endif
   {
       TAF_MTA_SndRrcSetNetMonCellReq(ulMsgName, ulReceiverPid, MTA_NETMON_NCELL_TYPE);
   }

   /* 启动保护定时器 */
   (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_RRC_NETMON_NCELL_QRY_CNF,
                                TI_TAF_MTA_WAIT_RRC_NETMON_NCELL_QRY_CNF_TIMER_LEN);

   /* 添加消息进等待队列 */
   TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_RRC_NETMON_NCELL_QRY_CNF,
                                   (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                    sizeof(AT_APPCTRL_STRU));
   return;
}
/*****************************************************************************
 函 数 名  : TAF_MTA_GetNetMonSndMsgInfo
 功能描述  : 获取要发送消息的ID 及接收PID
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月19日
    作    者   : zwx247453
    修改内容   : 新增函数

*****************************************************************************/
VOS_UINT32 TAF_MTA_GetNetMonSndMsgInfo(
    VOS_UINT32                         *pulMsgName,
    VOS_UINT32                         *pulReceiverPid
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulMsgName;

    ulResult      = VOS_OK;
    ulReceiverPid = UEPS_PID_GAS;
    ulMsgName     = ID_MTA_GRR_NETMON_CELL_QRY_REQ;

    /*根据当前模式确定发送的消息 ID 及接收PID*/
    switch (TAF_SDC_GetSysMode())
    {
        case TAF_SDC_SYS_MODE_GSM:
        {
            ulReceiverPid = UEPS_PID_GAS;
            ulMsgName     = ID_MTA_GRR_NETMON_CELL_QRY_REQ;
            break;
        }
        case TAF_SDC_SYS_MODE_WCDMA:
        {
            /*FDD*/
            if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
            {
                ulReceiverPid = WUEPS_PID_WRR;
                ulMsgName     = ID_MTA_RRC_NETMON_CELL_QRY_REQ;
            }
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
            else if (NAS_UTRANCTRL_UTRAN_MODE_TDD == NAS_UTRANCTRL_GetCurrUtranMode())  /*TDD*/
            {
                ulReceiverPid = TPS_PID_RRC;
                ulMsgName     = ID_MTA_RRC_NETMON_CELL_QRY_REQ;
            }
#endif
            else
            {
                 ulResult = VOS_ERR;
            }
            break;
        }
#if (FEATURE_ON == FEATURE_LTE)
        case TAF_SDC_SYS_MODE_LTE:
        {
            ulReceiverPid = PS_PID_ERRC;
            ulMsgName     = ID_MTA_LRRC_NETMON_CELL_QRY_REQ;
            break;
        }
#endif
        default:
            ulResult = VOS_ERR;
     }

     if (VOS_OK == ulResult)
     {
        *pulReceiverPid = ulReceiverPid;
        *pulMsgName     = ulMsgName;
     }

     return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndRrcSetNetMonCellReq
 功能描述  : mta给GUAS发送小区信息查询消息
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月19日
    作    者   : zwx247453
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID TAF_MTA_SndRrcSetNetMonCellReq(
    VOS_UINT32                          ulMsgName,
    VOS_UINT32                          ulReceiverPid,
    MTA_NETMON_CELL_TYPE_ENUM_UINT32    enCelltype
)
{
    MTA_RRC_NETMON_CELL_QRY_REQ_STRU   *pstMtaRrcMonCellReq = VOS_NULL_PTR;

    /* 申请消息结构内存 */
    pstMtaRrcMonCellReq   = (MTA_RRC_NETMON_CELL_QRY_REQ_STRU*)TAF_MTA_ALLOC_MSG_WITH_HDR(sizeof(MTA_RRC_NETMON_CELL_QRY_REQ_STRU));
    if (VOS_NULL_PTR == pstMtaRrcMonCellReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndRrcSetNetMonCellReq: Alloc msg fail!");
        return ;
    }

    /* 清空消息内容 */
    TAF_MTA_CLR_MSG_ENTITY(pstMtaRrcMonCellReq);

    /* 填写消息头 */
    TAF_MTA_CFG_MSG_HDR(pstMtaRrcMonCellReq, ulReceiverPid, ulMsgName);

    /* 填写消息内容 */
    pstMtaRrcMonCellReq->enCelltype        = enCelltype;

    /* 发送消息到AS */
    TAF_MTA_SEND_MSG(pstMtaRrcMonCellReq);

    /*记录GSM 查询服务小区状态*/
    if ((UEPS_PID_GAS == ulReceiverPid) &&  (MTA_NETMON_SCELL_TYPE == enCelltype))
    {
        TAF_MTA_SetNetmonGsmState(MTA_AT_NETMON_GSM_STATTE_WAIT_CELL_INFO);
    }

    return ;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndGasNetMonQryTaReq
 功能描述  : 向GAS发送请求，获取TA信息
 输入参数  :
 输出参数  :
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月19日
    作    者   : zwx247453
    修改内容   : 新建

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndGasNetMonQryTaReq(
    AT_APPCTRL_STRU                    *pstAppCtrl
)
{
    MTA_GRR_NETMON_TA_QRY_REQ_STRU     *pstMtaGrrNetMonTaReq = VOS_NULL_PTR;

    /* 如果当前定时器已启动，则返回失败 */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_GAS_NETMON_TA_QRY_CNF))
    {
        return VOS_ERR;
    }

    /* 申请消息结构内存 */
    pstMtaGrrNetMonTaReq  = (MTA_GRR_NETMON_TA_QRY_REQ_STRU*)TAF_MTA_ALLOC_MSG_WITH_HDR(sizeof(MTA_GRR_NETMON_TA_QRY_REQ_STRU));
    if (VOS_NULL_PTR == pstMtaGrrNetMonTaReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndGasNetMonQryTaReq: Alloc msg fail!");
        return VOS_ERR;
    }

    /* 清空消息内容 */
    TAF_MTA_CLR_MSG_ENTITY(pstMtaGrrNetMonTaReq);

    /* 填写消息头 */
    TAF_MTA_CFG_MSG_HDR(pstMtaGrrNetMonTaReq, UEPS_PID_GAS, ID_MTA_GRR_NETMON_TA_QRY_REQ);

    /* 发送消息到AS */
    TAF_MTA_SEND_MSG(pstMtaGrrNetMonTaReq);

    /* 启动保护定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_GAS_NETMON_TA_QRY_CNF,
                                 TI_TAF_MTA_WAIT_GAS_NETMON_TA_QRY_CNF_TIMER_LEN);

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_GAS_NETMON_TA_QRY_CNF,
                                    (VOS_UINT8*)pstAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvGasNetMonTaQryCnf
 功能描述  : MTA收到GAS ID_MTA_GAS_QRY_TA_CNF消息处理函数
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月19日
    作    者   : zwx247453
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvGasNetMonTaQryCnf(
    VOS_VOID                           *pMsg
)
{
    GRR_MTA_NETMON_TA_QRY_CNF_STRU     *pstGQryTA            = VOS_NULL_PTR;
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf            = VOS_NULL_PTR;
    MTA_AT_NETMON_CELL_INFO_STRU       *pstNetMonCellInfo    = VOS_NULL_PTR;

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_GAS_NETMON_TA_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvGasNetMonTaQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_GAS_NETMON_TA_QRY_CNF);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_GAS_NETMON_TA_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvGasNetMonTaQryCnf: get command buffer failed!");
        return;
    }

    pstGQryTA = (GRR_MTA_NETMON_TA_QRY_CNF_STRU *)pMsg;

    if (MTA_AT_NETMON_GSM_STATTE_WAIT_TA == TAF_MTA_GetNetmonGsmState())
    {
        TAF_MTA_SetNetmonGsmState(MTA_AT_NETMON_GSM_STATE_INIT);

        pstNetMonCellInfo = TAF_MTA_GetNetmonCellInfo();

        /* 填写主动上报的消息内容 */
        if (MTA_NETMON_RESULT_NO_ERR == pstGQryTA->enResult)
        {
            if (TAF_MTA_NETMON_GSM_TA_INVALID_VALUE == pstGQryTA->usTa)
            {
                pstNetMonCellInfo->unSCellInfo.stGsmSCellInfo.bitOpTa = PS_IE_NOT_PRESENT;
                pstNetMonCellInfo->unSCellInfo.stGsmSCellInfo.usTa    = 0xFFFF;
            }
            else
            {
                pstNetMonCellInfo->unSCellInfo.stGsmSCellInfo.bitOpTa = PS_IE_PRESENT;
                pstNetMonCellInfo->unSCellInfo.stGsmSCellInfo.usTa    = pstGQryTA->usTa;
            }
        }
        else
        {
            pstNetMonCellInfo->unSCellInfo.stGsmSCellInfo.bitOpTa = PS_IE_NOT_PRESENT;
            pstNetMonCellInfo->unSCellInfo.stGsmSCellInfo.usTa    = 0xFFFF;
        }
        /* 给at回消息 */
        TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                         ID_MTA_AT_SET_NETMON_SCELL_CNF,
                         sizeof(MTA_AT_NETMON_CELL_INFO_STRU),
                         (VOS_UINT8*)pstNetMonCellInfo);
    }

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_GAS_NETMON_TA_QRY_CNF);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvGasNetMonCellQryCnf
 功能描述  : MTA收到GAS ID_RRC_MTA_MON_CELL_INFO_CNF消息处理函数
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月19日
    作    者   : zwx247453
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvGasNetMonCellQryCnf(
    VOS_VOID                           *pMsg
)
{
    GRR_MTA_NETMON_CELL_QRY_CNF_STRU    *pstGsmNetMonCellInfo = VOS_NULL_PTR;
    TAF_MTA_CMD_BUFFER_STRU             *pstCmdBuf            = VOS_NULL_PTR;
    MTA_AT_NETMON_CELL_INFO_STRU        *pstNetMonCellInfo    = VOS_NULL_PTR;
    MTA_AT_NETMON_CELL_INFO_STRU         stMtaAtInd;
    VOS_UINT32                           ulMsgId;
    TAF_MTA_TIMER_ID_ENUM_UINT32         enTimerId;

    pstGsmNetMonCellInfo = (GRR_MTA_NETMON_CELL_QRY_CNF_STRU *)pMsg;
    PS_MEM_SET(&stMtaAtInd, 0, sizeof(MTA_AT_NETMON_CELL_INFO_STRU));

    if (MTA_NETMON_SCELL_TYPE == pstGsmNetMonCellInfo->enCelltype)
    {
        enTimerId = TI_TAF_MTA_WAIT_RRC_NETMON_SCELL_QRY_CNF;
        ulMsgId   = ID_MTA_AT_SET_NETMON_SCELL_CNF;
        PS_MEM_CPY(&stMtaAtInd.unSCellInfo.stGsmSCellInfo.stSCellInfo,
                   &pstGsmNetMonCellInfo->u.stSCellinfo,
                   sizeof(GRR_MTA_NETMON_SCELL_INFO_STRU));
    }
    else if (MTA_NETMON_NCELL_TYPE == pstGsmNetMonCellInfo->enCelltype)
    {
        enTimerId = TI_TAF_MTA_WAIT_RRC_NETMON_NCELL_QRY_CNF;
        ulMsgId   = ID_MTA_AT_SET_NETMON_NCELL_CNF;
        PS_MEM_CPY(&stMtaAtInd.stNCellInfo,
                   &pstGsmNetMonCellInfo->u.stNCellinfo,
                   sizeof(RRC_MTA_NETMON_NCELL_INFO_STRU));
    }
    else
    {
        MTA_WARNING_LOG("TAF_MTA_RcvGasNetMonCellQryCnf: WARNING: Celltype error!");
        return;
    }

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(enTimerId))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvGasNetMonCellQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(enTimerId);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(enTimerId);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvGasNetMonCellQryCnf: get command buffer failed!");
        return;
    }

    /* 返回成功的情况下获取相关内容 */
    if (MTA_NETMON_RESULT_NO_ERR == pstGsmNetMonCellInfo->enResult)
    {
        stMtaAtInd.enResult = MTA_AT_RESULT_NO_ERROR;

        /* 判断GSM发来的消息是服务小区信息还是邻区信息 */
        if (MTA_NETMON_SCELL_TYPE == pstGsmNetMonCellInfo->enCelltype)
        {
            /* 给GAS发送消息，获取TA */
            if (VOS_OK == TAF_MTA_SndGasNetMonQryTaReq((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo))
            {
                /* 从等待队列中删除消息 */
                TAF_MTA_DelItemInCmdBufferQueue(enTimerId);

                pstNetMonCellInfo = TAF_MTA_GetNetmonCellInfo();

                /* 保存已有参数 */
                PS_MEM_SET(pstNetMonCellInfo, 0, sizeof(MTA_AT_NETMON_CELL_INFO_STRU));
                PS_MEM_CPY(&pstNetMonCellInfo->unSCellInfo.stGsmSCellInfo.stSCellInfo,
                           &pstGsmNetMonCellInfo->u.stSCellinfo,
                           sizeof(GRR_MTA_NETMON_SCELL_INFO_STRU));

                pstNetMonCellInfo->enResult    = pstGsmNetMonCellInfo->enResult;
                pstNetMonCellInfo->enCellType  = pstGsmNetMonCellInfo->enCelltype;
                pstNetMonCellInfo->enRatType   = MTA_AT_NETMON_CELL_INFO_GSM;

                TAF_MTA_SetNetmonGsmState(MTA_AT_NETMON_GSM_STATTE_WAIT_TA);

                return;
            }
            else
            {
                TAF_MTA_SetNetmonGsmState(MTA_AT_NETMON_GSM_STATE_INIT);

                stMtaAtInd.unSCellInfo.stGsmSCellInfo.bitOpTa = PS_IE_NOT_PRESENT;
                stMtaAtInd.unSCellInfo.stGsmSCellInfo.usTa    = 0xFFFF;
            }
        }
    }
    else
    {
         stMtaAtInd.enResult = MTA_AT_RESULT_ERROR;
    }
    stMtaAtInd.enRatType  = MTA_AT_NETMON_CELL_INFO_GSM;
    stMtaAtInd.enCellType = pstGsmNetMonCellInfo->enCelltype;

    /* 给at回消息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ulMsgId,
                     sizeof(MTA_AT_NETMON_CELL_INFO_STRU),
                     (VOS_UINT8*)&stMtaAtInd);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(enTimerId);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvWrrNetMonCellQryCnf
 功能描述  : MTA收到WRR ID_RRC_MTA_MON_CELL_INFO_CNF消息处理函数
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月19日
    作    者   : zwx247453
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvWrrNetMonCellQryCnf(
    VOS_VOID                           *pMsg
)
{
    RRC_MTA_NETMON_CELL_INFO_QRY_CNF_STRU  *pstUtranNetMonCellInfo = VOS_NULL_PTR;
    TAF_MTA_CMD_BUFFER_STRU                *pstCmdBuf              = VOS_NULL_PTR;
    MTA_AT_NETMON_CELL_INFO_STRU            stMtaAtInd;
    VOS_UINT32                              ulMsgId;
    TAF_MTA_TIMER_ID_ENUM_UINT32            enTimerId;

    pstUtranNetMonCellInfo = (RRC_MTA_NETMON_CELL_INFO_QRY_CNF_STRU *)pMsg;

    PS_MEM_SET(&stMtaAtInd, 0, sizeof(MTA_AT_NETMON_CELL_INFO_STRU));

    if (MTA_NETMON_SCELL_TYPE == pstUtranNetMonCellInfo->enCelltype)
    {
        enTimerId = TI_TAF_MTA_WAIT_RRC_NETMON_SCELL_QRY_CNF;
        ulMsgId   = ID_MTA_AT_SET_NETMON_SCELL_CNF;
        PS_MEM_CPY(&stMtaAtInd.unSCellInfo.stUtranSCellInfo,
                   &pstUtranNetMonCellInfo->u.stSCellinfo,
                   sizeof(RRC_MTA_NETMON_UTRAN_SCELL_INFO_STRU));
    }
    else if (MTA_NETMON_NCELL_TYPE == pstUtranNetMonCellInfo->enCelltype)
    {
        enTimerId = TI_TAF_MTA_WAIT_RRC_NETMON_NCELL_QRY_CNF;
        ulMsgId   = ID_MTA_AT_SET_NETMON_NCELL_CNF;
        PS_MEM_CPY(&stMtaAtInd.stNCellInfo,
                   &pstUtranNetMonCellInfo->u.stNCellinfo,
                   sizeof(RRC_MTA_NETMON_NCELL_INFO_STRU));
    }
    else
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrNetMonCellQryCnf: WARNING: Celltype error!");
        return;
    }

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(enTimerId))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrNetMonCellQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(enTimerId);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(enTimerId);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrNetMonCellQryCnf: get command buffer failed!");
        return;
    }

    /* 填写主动上报的消息内容 */
    if (MTA_NETMON_RESULT_NO_ERR == pstUtranNetMonCellInfo->enResult)
    {
        stMtaAtInd.enResult = MTA_AT_RESULT_NO_ERROR;
    }
    else
    {
        stMtaAtInd.enResult = MTA_AT_RESULT_ERROR;
    }

    stMtaAtInd.enRatType  = MTA_AT_NETMON_CELL_INFO_UTRAN_FDD;
    stMtaAtInd.enCellType = pstUtranNetMonCellInfo->enCelltype;

    /* 给at回消息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ulMsgId,
                     sizeof(stMtaAtInd),
                     (VOS_UINT8*)&stMtaAtInd);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(enTimerId);

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : TAF_MTA_SndLrrcSetNetMonCellReq
 功能描述  : mta给Lrrc发送小区信息查询消息
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月19日
    作    者   : zwx247453
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID TAF_MTA_SndLrrcSetNetMonCellReq(
    VOS_UINT32                          ulMsgName,
    VOS_UINT32                          ulReceiverPid,
    MTA_NETMON_CELL_TYPE_ENUM_UINT32    enCelltype
)
{
    MTA_LRRC_NETMON_CELL_QRY_REQ_STRU  *pstMtaLrrcMonCellReq = VOS_NULL_PTR;

    /* 申请消息结构内存 */
    pstMtaLrrcMonCellReq  = (MTA_LRRC_NETMON_CELL_QRY_REQ_STRU*)TAF_MTA_ALLOC_MSG_WITH_HDR(sizeof(MTA_LRRC_NETMON_CELL_QRY_REQ_STRU));
    if (VOS_NULL_PTR == pstMtaLrrcMonCellReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcSetNetMonCellReq: Alloc msg fail!");
        return ;
    }

    /* 清空消息内容 */
    TAF_MTA_CLR_MSG_ENTITY(pstMtaLrrcMonCellReq);

    /* 填写消息头 */
    TAF_MTA_CFG_MSG_HDR(pstMtaLrrcMonCellReq, ulReceiverPid, ulMsgName);

    /* 填写消息内容 */
    pstMtaLrrcMonCellReq->enCelltype        = enCelltype;

    /* 发送消息到AS */
    TAF_MTA_SEND_MSG(pstMtaLrrcMonCellReq);

    return ;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvLrrcNetMonCellQryCnf
 功能描述  : MTA收到LTE ID_LRRC_MTA_NETMON_CELL_QRY_CNF消息处理函数
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月19日
    作    者   : zwx247453
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvLrrcNetMonCellQryCnf(
    VOS_VOID                            *pMsg
)
{
    LRRC_MTA_NETMON_CELL_INFO_QRY_CNF_STRU       *pstLteNetMonCellInfo = VOS_NULL_PTR;
    TAF_MTA_CMD_BUFFER_STRU                      *pstCmdBuf            = VOS_NULL_PTR;
    VOS_UINT32                                    ulMsgId;
    TAF_MTA_TIMER_ID_ENUM_UINT32                  enTimerId;
    MTA_AT_NETMON_CELL_INFO_STRU                  stMtaAtInd;

    pstLteNetMonCellInfo = (LRRC_MTA_NETMON_CELL_INFO_QRY_CNF_STRU *)pMsg;

    PS_MEM_SET(&stMtaAtInd, 0, sizeof(MTA_AT_NETMON_CELL_INFO_STRU));

    if (MTA_NETMON_SCELL_TYPE == pstLteNetMonCellInfo->enCelltype)
    {
        enTimerId = TI_TAF_MTA_WAIT_RRC_NETMON_SCELL_QRY_CNF;
        ulMsgId   = ID_MTA_AT_SET_NETMON_SCELL_CNF;
        PS_MEM_CPY(&stMtaAtInd.unSCellInfo.stLteSCellInfo,
                   &pstLteNetMonCellInfo->u.stSCellinfo,
                   sizeof(MTA_NETMON_EUTRAN_SCELL_INFO_STRU));
    }
    else if (MTA_NETMON_NCELL_TYPE == pstLteNetMonCellInfo->enCelltype)
    {
        enTimerId = TI_TAF_MTA_WAIT_RRC_NETMON_NCELL_QRY_CNF;
        ulMsgId   = ID_MTA_AT_SET_NETMON_NCELL_CNF;
        PS_MEM_CPY(&stMtaAtInd.stNCellInfo,
                   &pstLteNetMonCellInfo->u.stNCellinfo,
                   sizeof(RRC_MTA_NETMON_NCELL_INFO_STRU));
    }
    else
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcNetMonCellQryCnf: WARNING: Celltype error!");
        return;
    }

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(enTimerId))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcNetMonCellQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(enTimerId);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(enTimerId);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcNetMonCellQryCnf: get command buffer failed!");
        return;
    }

    /* 填写主动上报的消息内容 */
    if (MTA_NETMON_RESULT_NO_ERR == pstLteNetMonCellInfo->enResult)
    {
        stMtaAtInd.enResult = MTA_AT_RESULT_NO_ERROR;
    }
    else
    {
        stMtaAtInd.enResult = MTA_AT_RESULT_ERROR;
    }

    stMtaAtInd.enRatType  = MTA_AT_NETMON_CELL_INFO_LTE;
    stMtaAtInd.enCellType = pstLteNetMonCellInfo->enCelltype;

    /* 给at回消息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ulMsgId,
                     sizeof(stMtaAtInd),
                     (VOS_UINT8*)&stMtaAtInd);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(enTimerId);

    return;

}
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTrrcNetMonCellQryCnf
 功能描述  : MTA收到TRRC ID_RRC_MTA_NETMON_CELL_QRY_CNF消息处理函数
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月19日
    作    者   : zwx247453
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTrrcNetMonCellQryCnf(
    VOS_VOID                           *pMsg
)
{
    RRC_MTA_NETMON_CELL_INFO_QRY_CNF_STRU        *pstUtranNetMonCellInfo = VOS_NULL_PTR;
    TAF_MTA_CMD_BUFFER_STRU                      *pstCmdBuf              = VOS_NULL_PTR;
    VOS_UINT32                                    ulMsgId;
    TAF_MTA_TIMER_ID_ENUM_UINT32                  enTimerId;
    MTA_AT_NETMON_CELL_INFO_STRU                  stMtaAtInd;

    pstUtranNetMonCellInfo = (RRC_MTA_NETMON_CELL_INFO_QRY_CNF_STRU *)pMsg;

    PS_MEM_SET(&stMtaAtInd, 0, sizeof(MTA_AT_NETMON_CELL_INFO_STRU));

    if (MTA_NETMON_SCELL_TYPE == pstUtranNetMonCellInfo->enCelltype)
    {
        enTimerId = TI_TAF_MTA_WAIT_RRC_NETMON_SCELL_QRY_CNF;
        ulMsgId   = ID_MTA_AT_SET_NETMON_SCELL_CNF;
        PS_MEM_CPY(&stMtaAtInd.unSCellInfo.stUtranSCellInfo,
                   &pstUtranNetMonCellInfo->u.stSCellinfo,
                   sizeof(RRC_MTA_NETMON_UTRAN_SCELL_INFO_STRU));
    }
    else if (MTA_NETMON_NCELL_TYPE == pstUtranNetMonCellInfo->enCelltype)
    {
        enTimerId = TI_TAF_MTA_WAIT_RRC_NETMON_NCELL_QRY_CNF;
        ulMsgId   = ID_MTA_AT_SET_NETMON_NCELL_CNF;
        PS_MEM_CPY(&stMtaAtInd.stNCellInfo,
                   &pstUtranNetMonCellInfo->u.stNCellinfo,
                   sizeof(RRC_MTA_NETMON_NCELL_INFO_STRU));
    }
    else
    {
        MTA_WARNING_LOG("TAF_MTA_RcvTrrcNetMonCellQryCnf: WARNING: Celltype error!");
        return;
    }

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(enTimerId))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvTrrcNetMonCellQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(enTimerId);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(enTimerId);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvTrrcNetMonCellQryCnf: get command buffer failed!");
        return;
    }

    /* 填写主动上报的消息内容 */
    if (MTA_NETMON_RESULT_NO_ERR == pstUtranNetMonCellInfo->enResult)
    {
        stMtaAtInd.enResult = MTA_AT_RESULT_NO_ERROR;
    }
    else
    {
        stMtaAtInd.enResult = MTA_AT_RESULT_ERROR;
    }
    stMtaAtInd.enRatType  = MTA_AT_NETMON_CELL_INFO_UTRAN_TDD;
    stMtaAtInd.enCellType = pstUtranNetMonCellInfo->enCelltype;

    /* 给at回消息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ulMsgId,
                     sizeof(stMtaAtInd),
                     (VOS_UINT8*)&stMtaAtInd);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(enTimerId);

    return;
}
#endif

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiWaitGrrNetMonTaQryExpired
 功能描述  : 查询TA消息超时处理
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
  1.日    期   : 2015年10月19日
    作    者   : zwx247453
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitGrrNetMonTaQryExpired(
    VOS_VOID                            *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU             *pstCmdBuf         = VOS_NULL_PTR;
    MTA_AT_NETMON_CELL_INFO_STRU        *pstNetMonCellInfo = VOS_NULL_PTR;

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_GAS_NETMON_TA_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvTiWaitGrrNetMonTaQryExpired: get command buffer failed!");
        return;
    }

    /* 获取TA参数超时，仍然上报其他参数 */
    if (MTA_AT_NETMON_GSM_STATTE_WAIT_TA == TAF_MTA_GetNetmonGsmState())
    {
        TAF_MTA_SetNetmonGsmState(MTA_AT_NETMON_GSM_STATE_INIT);

        pstNetMonCellInfo = TAF_MTA_GetNetmonCellInfo();

        pstNetMonCellInfo->unSCellInfo.stGsmSCellInfo.bitOpTa = PS_IE_NOT_PRESENT;
        pstNetMonCellInfo->unSCellInfo.stGsmSCellInfo.usTa    = 0xFFFF;

        TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                           ID_MTA_AT_SET_NETMON_SCELL_CNF,
                           sizeof(MTA_AT_NETMON_CELL_INFO_STRU),
                           (VOS_UINT8*)pstNetMonCellInfo);
    }

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_GAS_NETMON_TA_QRY_CNF);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiWaitRrcNetMonSCellQryExpired
 功能描述  : MONSC查询服务小区信息超时的处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
  1.日    期   : 2015年10月19日
    作    者   : zwx247453
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitRrcNetMonSCellQryExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf           = VOS_NULL_PTR;
    MTA_AT_NETMON_CELL_INFO_STRU        stQryNetmonCellInfo;

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_RRC_NETMON_SCELL_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    PS_MEM_SET(&stQryNetmonCellInfo, 0x0, sizeof(MTA_AT_NETMON_CELL_INFO_STRU));

    stQryNetmonCellInfo.enResult = MTA_AT_RESULT_ERROR;

    /* 上报给AT模块查询错误 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_SET_NETMON_SCELL_CNF,
                     sizeof(stQryNetmonCellInfo),
                     (VOS_UINT8*)&stQryNetmonCellInfo );

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_RRC_NETMON_SCELL_QRY_CNF);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiWaitRrcNetMonNCellQryExpired
 功能描述  : MONNC查询邻区信息超时的处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
  1.日    期   : 2015年10月19日
    作    者   : zwx247453
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitRrcNetMonNCellQryExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_NETMON_CELL_INFO_STRU        stQryNetmonCellInfo;

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_RRC_NETMON_NCELL_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    PS_MEM_SET(&stQryNetmonCellInfo, 0x0, sizeof(MTA_AT_NETMON_CELL_INFO_STRU));

    stQryNetmonCellInfo.enResult = MTA_AT_RESULT_ERROR;

    /* 上报给AT模块查询错误 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_SET_NETMON_NCELL_CNF,
                     sizeof(MTA_AT_NETMON_CELL_INFO_STRU),
                     (VOS_UINT8*)&stQryNetmonCellInfo );

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_RRC_NETMON_NCELL_QRY_CNF);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtQryAfcAndXoInfoReq
 功能描述  : 查询温补系数的处理
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
  1.日    期   : 2015年12月24日
    作    者   : c00299064
    修改内容   : 新增函数
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtQryAfcAndXoInfoReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                             *pstSetReq = VOS_NULL_PTR;
    MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF_STRU      stQryCnf;

    PS_MEM_SET(&stQryCnf, 0, sizeof(MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF_STRU));

    pstSetReq = (AT_MTA_MSG_STRU*)pMsg;

    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_RCM_AFC_CLK_INFO_QRY_CNF))
    {
        stQryCnf.enResult   =   MTA_AT_RESULT_ERROR;
        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF,
                         sizeof(MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF_STRU),
                         (VOS_UINT8*)&stQryCnf);
        return;
    }

    /* snd rcm the req */
    TAF_MTA_SndRcmAfcClkAndXoCoEfQryReq();

    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_RCM_AFC_CLK_INFO_QRY_CNF,
                       TI_TAF_MTA_WAIT_RCM_AFC_CLK_INFO_TIMER_LEN);

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_RCM_AFC_CLK_INFO_QRY_CNF,
                                    (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiWaitRcmAfcInfoQryExpired
 功能描述  : wait rcm afc info cnf超时的处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
  1.日    期   : 2015年12月24日
    作    者   : c00299064
    修改内容   : 新增函数
*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitRcmAfcInfoQryExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                     *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF_STRU      stQryCnf;

    PS_MEM_SET(&stQryCnf, 0, sizeof(MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF_STRU));

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_RCM_AFC_CLK_INFO_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    stQryCnf.enResult = MTA_AT_RESULT_OPTION_TIMEOUT;

    /* 上报给AT模块查询错误 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF,
                     sizeof(MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF_STRU),
                     (VOS_UINT8*)&stQryCnf );

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_RCM_AFC_CLK_INFO_QRY_CNF);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvRcmAfcInfoCnf
 功能描述  : 收到RCM查询温补系数的CNF的处理
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
  1.日    期   : 2015年12月24日
    作    者   : c00299064
    修改内容   : 新增函数
*****************************************************************************/
VOS_VOID TAF_MTA_RcvRcmAfcInfoCnf(
    VOS_VOID                           *pMsg
)
{
    RCM_MTA_AFC_CLK_INFO_QRY_CNF_STRU          *pstCnf               = VOS_NULL_PTR;
    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf            = VOS_NULL_PTR;
    MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF_STRU     stQryCnf;

    PS_MEM_SET(&stQryCnf, 0, sizeof(MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF_STRU));

    pstCnf      = (RCM_MTA_AFC_CLK_INFO_QRY_CNF_STRU*)pMsg;

    pstCmdBuf   = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_RCM_AFC_CLK_INFO_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvRcmAfcInfoCnf:get appctrl err");
        return;
    }

    /*  停止定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_RCM_AFC_CLK_INFO_QRY_CNF);

    if (MTA_PHY_RESULT_NO_ERROR != pstCnf->enResult)
    {
        stQryCnf.enResult = MTA_AT_RESULT_ERROR;
    }
    else
    {
        stQryCnf.enResult               =  MTA_AT_RESULT_NO_ERROR;

        stQryCnf.enStatus               =  TAF_MTA_GetAfcClkStatus(pstCnf->enStatus);
        stQryCnf.lDeviation             =  pstCnf->lDeviation;
        stQryCnf.sCoeffStartTemp        =  pstCnf->sCoeffStartTemp;
        stQryCnf.sCoeffEndTemp          =  pstCnf->sCoeffEndTemp;

        PS_MEM_CPY(stQryCnf.aulCoeffMantissa,
                   pstCnf->aulCoeffMantissa,
                   sizeof(stQryCnf.aulCoeffMantissa));

        PS_MEM_CPY(stQryCnf.ausCoeffExponent,
                   pstCnf->ausCoeffExponent,
                   sizeof(stQryCnf.ausCoeffExponent));
    }

    /* 发送回复 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU*)pstCmdBuf->pucMsgInfo,
                 ID_MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF,
                 sizeof(MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF_STRU),
                 (VOS_UINT8*)&stQryCnf);


    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_RCM_AFC_CLK_INFO_QRY_CNF);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_GetAfcClkStatus
 功能描述  : 收到RCM查询温补系数的CNF的AFC CLK STATUS 的处理
 输入参数  : PHY_MTA_AFC_CLK_STATUS_ENUM_UINT16  enStatus
 输出参数  : 无
 返 回 值  : AT_MTA_AFC_CLK_STATUS_ENUM_UINT32
 调用函数  :
 被调函数  :
 修改历史  :
  1.日    期   : 2015年12月24日
    作    者   : c00299064
    修改内容   : 新增函数
*****************************************************************************/
AT_MTA_AFC_CLK_STATUS_ENUM_UINT32 TAF_MTA_GetAfcClkStatus(PHY_MTA_AFC_CLK_STATUS_ENUM_UINT16  enStatus)
{
    AT_MTA_AFC_CLK_STATUS_ENUM_UINT32   enAfcClkStatus;

    /* 原因值的转换 */
    switch (enStatus)
    {
        case PHY_MTA_AFC_CLK_UNLOCKED:

            enAfcClkStatus = AT_MTA_AFC_CLK_UNLOCKED;
            break;

        case PHY_MTA_AFC_CLK_LOCKED:

            enAfcClkStatus = AT_MTA_AFC_CLK_LOCKED;
            break;

        default:

            enAfcClkStatus = AT_MTA_AFC_CLK_STATUS_BUTT;
            break;
    }

    return enAfcClkStatus;

}




#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

