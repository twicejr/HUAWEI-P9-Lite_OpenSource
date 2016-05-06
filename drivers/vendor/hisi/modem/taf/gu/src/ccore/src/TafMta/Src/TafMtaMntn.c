/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMtaMntn.c
  版 本 号   : 初稿
  作    者   : m00217266
  生成日期   : 2012年12月31日
  最近修改   :
  功能描述   : MTA模块处理可维可测功能
  函数列表   :
  修改历史   :
  1.日    期   : 2012年12月31日
    作    者   : m00217266
    修改内容   : DSDA C核项目新增

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "TafMtaMntn.h"
#include "AtMtaInterface.h"
#include "TafSdcLib.h"
#include "TafMtaTimerMgmt.h"
#include "TafMtaMain.h"
#include "TafMtaCtx.h"
#include "TafMtaComm.h"
#include "mdrv.h"
#include "NasOmInterface.h"
#include "TafAgentInterface.h"
#include "mdrv.h"

#if (FEATURE_ON == FEATURE_PTM)
#include "NasErrorLog.h"
#endif

#include "NasComm.h"

#include "NasMtaInterface.h"

#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
#include "nascbtinterface.h"
#include "NasDynLoadApi.h"
#endif

#include "NasUtranCtrlInterface.h"

/*lint -e958*/

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 */
#define    THIS_FILE_ID                 PS_FILE_ID_TAF_MTA_MNTN_C
/*lint +e767 */

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvSetWrrFreqlockReq
 功能描述  : MTA处理^FREQLOCK命令，设置锁频信息
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
VOS_VOID TAF_MTA_RcvSetWrrFreqlockReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstQryReq       = VOS_NULL_PTR;
    MTA_AT_WRR_FREQLOCK_CTRL_STRU      *pstRrcAtSetPara = VOS_NULL_PTR;
    MTA_AT_WRR_FREQLOCK_SET_CNF_STRU    stQryCnf;
    VOS_UINT32                          ulResult;
    /* 不用UtranMode判断是否给was发送消息，改为平台支持FDD，都给WAS发送消息 */

    pstQryReq          = (AT_MTA_MSG_STRU *)pMsg;
    pstRrcAtSetPara    = (MTA_AT_WRR_FREQLOCK_CTRL_STRU *)pstQryReq->aucContent;
    ulResult           = VOS_ERR;

    /* 如果当前定时器已启动，则返回失败 */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_FREQLOCK_SET_CNF))
    {
        PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));
        stQryCnf.ulResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                      ID_MTA_AT_WRR_FREQLOCK_SET_CNF,
                      sizeof(stQryCnf),
                      (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* 如果平台支持W模，则发送请求给as，否则给at回复失败 */
    if ( VOS_TRUE == TAF_SDC_IsPlatformSupportUtranFdd() )
    {
        /* 收到at命令请求，发请求消息通知as */
        ulResult = TAF_MTA_SndWrrSetFreqlockReqMsg((MTA_WRR_FREQLOCK_CTRL_STRU *)pstRrcAtSetPara);
    }

    if (ulResult != VOS_OK)
    {
        /* 消息发送失败，给at回复失败*/
        PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));
        stQryCnf.ulResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                         ID_MTA_AT_WRR_FREQLOCK_SET_CNF,
                         sizeof(stQryCnf),
                         (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* 启动保护定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_WRR_FREQLOCK_SET_CNF,
                                 TI_TAF_MTA_WAIT_WRR_FREQLOCK_SET_CNF_TIMER_LEN);

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_FREQLOCK_SET_CNF,
                                     (VOS_UINT8*)&pstQryReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvSetWrrRrcVersionReq
 功能描述  : MTA处理^HSPA命令，设置RRCVERSION信息
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
VOS_VOID TAF_MTA_RcvSetWrrRrcVersionReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                                        *pstSetReq = VOS_NULL_PTR;
    MTA_AT_WRR_RRC_VERSION_SET_CNF_STRU                     stSetCnf;
    VOS_UINT32                                              ulResult;
    /* 不用UtranMode判断是否给was发送消息，改为平台支持FDD，都给WAS发送消息 */

    pstSetReq = (AT_MTA_MSG_STRU *)pMsg;
    ulResult  = VOS_ERR;

    /* 如果当前定时器已启动，则返回失败 */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_RRC_VERSION_SET_CNF))
    {
        PS_MEM_SET(&stSetCnf, 0x0, sizeof(stSetCnf));
        stSetCnf.ulResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                      ID_MTA_AT_WRR_RRC_VERSION_SET_CNF,
                      sizeof(stSetCnf),
                      (VOS_UINT8*)&stSetCnf );
        return;
    }

    /* 如果平台支持W模，则发送请求给as，否则给at回复失败 */
    if ( VOS_TRUE == TAF_SDC_IsPlatformSupportUtranFdd() )
    {
        /* 收到at命令请求，发请求消息通知as */
        ulResult = TAF_MTA_SndWrrSetVersionReqMsg(pstSetReq->aucContent[0]);
    }

    if (ulResult != VOS_OK)
    {
        /* 消息发送失败，给at回复失败*/
        PS_MEM_SET(&stSetCnf, 0x0, sizeof(stSetCnf));
        stSetCnf.ulResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_WRR_RRC_VERSION_SET_CNF,
                         sizeof(stSetCnf),
                         (VOS_UINT8*)&stSetCnf );
        return;
    }

    /* 启动保护定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_WRR_RRC_VERSION_SET_CNF,
                                 TI_TAF_MTA_WAIT_WRR_RRC_VERSION_SET_CNF_TIMER_LEN);

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_RRC_VERSION_SET_CNF,
                                     (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}




/*****************************************************************************
 函 数 名  : TAF_MTA_RcvSetWrrCellsrhReq
 功能描述  : MTA处理^CELLSRCH命令，设置是否使用先验信息进行小区搜索
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
    修改内容   : DTS2013031800705：关机状态下发CWAS回复ERRORs

*****************************************************************************/
VOS_VOID TAF_MTA_RcvSetWrrCellsrhReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                                        *pstSetReq = VOS_NULL_PTR;
    MTA_AT_WRR_CELLSRH_SET_CNF_STRU                         stSetCnf;
    VOS_UINT32                                              ulResult;
    /* 不用UtranMode判断是否给was发送消息，改为平台支持FDD，都给WAS发送消息 */

    pstSetReq = (AT_MTA_MSG_STRU *)pMsg;
    ulResult  = VOS_ERR;

    /* 如果当前定时器已启动，则返回失败 */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_CELLSRH_SET_CNF))
    {
        PS_MEM_SET(&stSetCnf, 0x0, sizeof(stSetCnf));
        stSetCnf.ulResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                      ID_MTA_AT_WRR_CELLSRH_SET_CNF,
                      sizeof(stSetCnf),
                      (VOS_UINT8*)&stSetCnf );
        return;
    }

    /* 如果平台支持W模，则发送请求给as，否则给at回复失败 */
    if ( VOS_TRUE == TAF_SDC_IsPlatformSupportUtranFdd() )
    {
        /* 收到at命令请求，发请求消息通知as */
        ulResult = TAF_MTA_SndWrrSetCellsrhReqMsg(pstSetReq->aucContent[0]);
    }

    if (ulResult != VOS_OK)
    {
        /* 消息发送失败，给at回复失败*/
        PS_MEM_SET(&stSetCnf, 0x0, sizeof(stSetCnf));
        stSetCnf.ulResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_WRR_CELLSRH_SET_CNF,
                         sizeof(stSetCnf),
                         (VOS_UINT8*)&stSetCnf );
        return;
    }

    /* 启动保护定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_WRR_CELLSRH_SET_CNF,
                                 TI_TAF_MTA_WAIT_WRR_CELLSRH_SET_CNF_TIMER_LEN);

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_CELLSRH_SET_CNF,
                                     (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MTA_RcvQryWrrFreqlockReq
 功能描述  : MTA处理^FREQLOCK命令，查询锁频信息
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
VOS_VOID TAF_MTA_RcvQryWrrFreqlockReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstQryReq = VOS_NULL_PTR;
    MTA_AT_WRR_FREQLOCK_QRY_CNF_STRU    stQryCnf;
    VOS_UINT32                          ulResult;
    /* 不用UtranMode判断是否给was发送消息，改为平台支持FDD，都给WAS发送消息 */

    pstQryReq          = (AT_MTA_MSG_STRU *)pMsg;
    ulResult           = VOS_ERR;

    /* 如果当前定时器已启动，则返回失败 */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_FREQLOCK_QRY_CNF))
    {
        PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));
        stQryCnf.ulResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                      ID_MTA_AT_WRR_FREQLOCK_QRY_CNF,
                      sizeof(stQryCnf),
                      (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* 如果平台支持W模，则发送请求给as，否则给at回复失败 */
    if ( VOS_TRUE == TAF_SDC_IsPlatformSupportUtranFdd() )
    {
        /* 收到at命令请求，发请求消息通知as */
        ulResult = TAF_MTA_SndWrrQryFreqlockReqMsg();
    }

    if (ulResult != VOS_OK)
    {
        /* 消息发送失败，给at回复失败*/
        PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));
        stQryCnf.ulResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                         ID_MTA_AT_WRR_FREQLOCK_QRY_CNF,
                         sizeof(stQryCnf),
                         (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* 启动保护定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_WRR_FREQLOCK_QRY_CNF,
                                 TI_TAF_MTA_WAIT_WRR_FREQLOCK_QRY_CNF_TIMER_LEN);

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_FREQLOCK_QRY_CNF,
                                     (VOS_UINT8*)&pstQryReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvQryWrrRrcVersionReq
 功能描述  : MTA处理^HSPA命令, 查询RRC VERSION信息
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
VOS_VOID TAF_MTA_RcvQryWrrRrcVersionReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                                        *pstQryVersionReq = VOS_NULL_PTR;
    MTA_AT_WRR_RRC_VERSION_QRY_CNF_STRU                     stQryCnf;
    VOS_UINT32                                              ulResult;
    /* 不用UtranMode判断是否给was发送消息，改为平台支持FDD，都给WAS发送消息 */

    pstQryVersionReq = (AT_MTA_MSG_STRU *)pMsg;
    ulResult         = VOS_ERR;

    PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));

    /* 如果当前定时器已启动，则给AT回复查询失败 */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_RRC_VERSION_QRY_CNF))
    {
        stQryCnf.ulResult = VOS_ERR;
        TAF_MTA_SndAtMsg(&pstQryVersionReq->stAppCtrl,
                      ID_MTA_AT_WRR_RRC_VERSION_QRY_CNF,
                      sizeof(stQryCnf),
                      (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* 如果平台支持W模，则发送请求给as，否则给at回复失败 */
    if ( VOS_TRUE == TAF_SDC_IsPlatformSupportUtranFdd() )
    {
        ulResult = TAF_MTA_SndWrrQryRrcVersionReqMsg();
    }

    /* 如果当前的Utran模式不是FDD模式,ulResult为VOS_ERR，
       或者给接入层发送消息失败,ulResult也为VOS_ERR，给AT回复查询失败 */
    if (VOS_OK != ulResult)
    {
        /* 消息发送失败，给at回复失败*/
        stQryCnf.ulResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstQryVersionReq->stAppCtrl,
                         ID_MTA_AT_WRR_RRC_VERSION_QRY_CNF,
                         sizeof(stQryCnf),
                         (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* 启动保护定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_WRR_RRC_VERSION_QRY_CNF, TI_TAF_MTA_WAIT_WRR_RRC_VERSION_QRY_CNF_TIMER_LEN);

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_RRC_VERSION_QRY_CNF,
                                     (VOS_UINT8*)&pstQryVersionReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}



/*****************************************************************************
 函 数 名  : TAF_MTA_RcvQryWrrCellsrhReq
 功能描述  : MTA处理^CELLSRCH命令,查询是否使用先验信息进行小区搜索
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
VOS_VOID TAF_MTA_RcvQryWrrCellsrhReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                                        *pstQryVersionReq = VOS_NULL_PTR;
    MTA_AT_WRR_CELLSRH_QRY_CNF_STRU                         stQryCnf;
    VOS_UINT32                                              ulResult;
    /* 不用UtranMode判断是否给was发送消息，改为平台支持FDD，都给WAS发送消息 */

    pstQryVersionReq = (AT_MTA_MSG_STRU *)pMsg;
    ulResult         = VOS_ERR;

    PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));

    /* 如果当前定时器已启动，则给AT回复查询失败 */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_CELLSRH_QRY_CNF))
    {
        stQryCnf.ulResult = VOS_ERR;
        TAF_MTA_SndAtMsg(&pstQryVersionReq->stAppCtrl,
                      ID_MTA_AT_WRR_CELLSRH_QRY_CNF,
                      sizeof(stQryCnf),
                      (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* 如果平台支持W模，则发送请求给as，否则给at回复失败 */
    if ( VOS_TRUE == TAF_SDC_IsPlatformSupportUtranFdd() )
    {
        ulResult = TAF_MTA_SndWrrQryCellsrhReqMsg();
    }

    /* 如果当前的Utran模式不是FDD模式,ulResult为VOS_ERR，
       或者给接入层发送消息失败,ulResult也为VOS_ERR，给AT回复查询失败 */
    if (VOS_OK != ulResult)
    {
        /* 消息发送失败，给at回复失败*/
        stQryCnf.ulResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstQryVersionReq->stAppCtrl,
                         ID_MTA_AT_WRR_CELLSRH_QRY_CNF,
                         sizeof(stQryCnf),
                         (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* 启动保护定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_WRR_CELLSRH_QRY_CNF, TI_TAF_MTA_WAIT_WRR_CELLSRH_QRY_CNF_TIMER_LEN);

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_CELLSRH_QRY_CNF,
                                     (VOS_UINT8*)&pstQryVersionReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtSetNCellMonitorReq
 功能描述  : MTA处理^NCELLMONITOR命令，设置TD/LTE邻小区是否主动上报
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtSetNCellMonitorReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                            *pstSetReq = VOS_NULL_PTR;
    AT_MTA_NCELL_MONITOR_SET_REQ_STRU          *pstSetRptReq = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                      stSetCnf;
    MTA_AT_RESULT_ENUM_UINT32                   enResult;

    pstSetReq    = (AT_MTA_MSG_STRU *)pMsg;
    pstSetRptReq = (AT_MTA_NCELL_MONITOR_SET_REQ_STRU *)pstSetReq->aucContent;
    enResult     = MTA_AT_RESULT_ERROR;

    /* 如果当前定时器已启动，则返回失败 */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_SET_CNF))
    {
        PS_MEM_SET(&stSetCnf, 0x0, sizeof(stSetCnf));
        stSetCnf.enResult = MTA_AT_RESULT_ERROR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                      ID_MTA_AT_NCELL_MONITOR_SET_CNF,
                      sizeof(stSetCnf),
                      (VOS_UINT8*)&stSetCnf );
        return;
    }

    /* 如果平台支持G模，则发送请求给as，否则给at回复失败 */
    if ( VOS_TRUE == TAF_SDC_IsPlatformSupportGsm() )
    {
        /* 收到at命令请求，发请求消息通知as */
        enResult = TAF_MTA_SndGrrNCellMonitorSetReq(pstSetRptReq->ucSwitch);
    }

    if (MTA_AT_RESULT_NO_ERROR != enResult)
    {
        /* 消息发送失败，给at回复失败*/
        PS_MEM_SET(&stSetCnf, 0x0, sizeof(stSetCnf));
        stSetCnf.enResult = MTA_AT_RESULT_ERROR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_NCELL_MONITOR_SET_CNF,
                         sizeof(stSetCnf),
                         (VOS_UINT8*)&stSetCnf );
        return;
    }

    /* 启动保护定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_SET_CNF,
                                 TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_SET_CNF_TIMER_LEN);

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_SET_CNF,
                                     (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtQryNCellMonitorReq
 功能描述  : MTA处理^NCELLMONITOR命令，查询TD/LTE邻小区是否主动上报及邻区状态
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtQryNCellMonitorReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                            *pstQryReq = VOS_NULL_PTR;
    MTA_AT_NCELL_MONITOR_QRY_CNF_STRU           stQryCnf;
    MTA_AT_RESULT_ENUM_UINT32                   enResult;

    pstQryReq    = (AT_MTA_MSG_STRU *)pMsg;
    enResult     = MTA_AT_RESULT_ERROR;

    /* 如果当前定时器已启动，则返回失败 */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_QRY_CNF))
    {
        PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));
        stQryCnf.enResult = MTA_AT_RESULT_ERROR;

        TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                      ID_MTA_AT_NCELL_MONITOR_QRY_CNF,
                      sizeof(stQryCnf),
                      (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* 如果平台支持G模，则发送请求给as，否则给at回复失败 */
    if ( VOS_TRUE == TAF_SDC_IsPlatformSupportGsm() )
    {
        /* 收到at命令请求，发请求消息通知as */
        enResult = TAF_MTA_SndGrrNCellMonitorQryReq();
    }

    if (MTA_AT_RESULT_NO_ERROR != enResult)
    {
        /* 消息发送失败，给at回复失败*/
        PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));
        stQryCnf.enResult = MTA_AT_RESULT_ERROR;

        TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                         ID_MTA_AT_NCELL_MONITOR_QRY_CNF,
                         sizeof(stQryCnf),
                         (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* 启动保护定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_QRY_CNF,
                                 TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_QRY_CNF_TIMER_LEN);

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_QRY_CNF,
                                     (VOS_UINT8*)&pstQryReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtSetJamDetectReq
 功能描述  : 处理at下发的设置Jamming Detection Report命令
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月4日
    作    者   : g00261581
    修改内容   : 新建

*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtSetJamDetectReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstSetReq       = VOS_NULL_PTR;
    AT_MTA_SET_JAM_DETECT_REQ_STRU     *pstJamDetectReq = VOS_NULL_PTR;
    MTA_AT_SET_JAM_DETECT_CNF_STRU      stQryCnf;
    VOS_UINT32                          ulResult;

    pstSetReq         = (AT_MTA_MSG_STRU *)pMsg;
    pstJamDetectReq   = (AT_MTA_SET_JAM_DETECT_REQ_STRU *)(pstSetReq->aucContent);
    ulResult          = VOS_ERR;
    stQryCnf.enResult = MTA_AT_RESULT_ERROR;

    /* 如果当前定时器已启动，则返回失败 */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_JAM_DETECT_SET_CNF))
    {
        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_SET_JAM_DETECT_CNF,
                         sizeof(stQryCnf),
                         (VOS_UINT8*)&stQryCnf);
        return;
    }

    /* 如果平台支持G模，则发送请求给as，否则给at回复失败 */
    if (VOS_TRUE == TAF_SDC_IsPlatformSupportGsm())
    {
        /* 收到at命令请求，发请求消息通知as */
        ulResult = TAF_MTA_SndGrrSetJamDetectReq(pstJamDetectReq);
    }

    if (VOS_OK != ulResult)
    {
        /* 消息发送失败，给at回复失败*/
        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_SET_JAM_DETECT_CNF,
                         sizeof(stQryCnf),
                         (VOS_UINT8*)&stQryCnf);
        return;
    }

    /* 启动保护定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_JAM_DETECT_SET_CNF,
                                 TI_TAF_MTA_WAIT_JAM_DETECT_SET_CNF_TIMER_LEN);

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_JAM_DETECT_SET_CNF,
                                    (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtPhyInitReq
 功能描述  : MTA模块收到AT发来的ID_AT_MTA_PHY_INIT_REQ请求消息的处理函数
 输入参数  : pMsg   -- AT发送的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月25日
    作    者   : y00176023
    修改内容   : 新增^PHYINIT命令
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtPhyInitReq(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                                        *pstAtMtaReqMsg     = VOS_NULL_PTR;
    MTA_UPHY_START_UPHY_REQ_STRU                           *pstPhyStartReq     = VOS_NULL_PTR;
    MTA_AT_PHY_INIT_CNF_STRU                                stSndAtPhyInitCnf;
    TAF_MTA_TIMER_STATUS_ENUM_UINT8                         enPhyInitTiStatus;

    pstAtMtaReqMsg = (AT_MTA_MSG_STRU*)pMsg;


    /* 消息空间申请 */
    pstPhyStartReq = (MTA_UPHY_START_UPHY_REQ_STRU *)PS_ALLOC_MSG( UEPS_PID_MTA,
                                                      sizeof(MTA_UPHY_START_UPHY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstPhyStartReq)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvAtPhyInitReq: alloc msg fail!");

        /* 消息内容重置 */
        PS_MEM_SET(&stSndAtPhyInitCnf, 0x0, sizeof(MTA_AT_PHY_INIT_CNF_STRU));
        stSndAtPhyInitCnf.enResult = MTA_AT_RESULT_ERROR;

        /* 给AT模块发送失败消息 */
        TAF_MTA_SndAtMsg(&pstAtMtaReqMsg->stAppCtrl,
                      ID_MTA_AT_PHY_INIT_CNF,
                      sizeof(stSndAtPhyInitCnf),
                      (VOS_UINT8*)&stSndAtPhyInitCnf );

        return;
    }


    /* 如果当前定时器已启动，则返回失败 */
    enPhyInitTiStatus  = TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_DSP_INIT_CNF);
    if (TAF_MTA_TIMER_STATUS_RUNING == enPhyInitTiStatus)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvAtPhyInitReq: alloc msg fail!");

        /* 消息内容重置 */
        PS_MEM_SET(&stSndAtPhyInitCnf, 0x0, sizeof(MTA_AT_PHY_INIT_CNF_STRU));
        stSndAtPhyInitCnf.enResult = MTA_AT_RESULT_ERROR;

        /* 给AT模块发送失败消息 */
        TAF_MTA_SndAtMsg(&pstAtMtaReqMsg->stAppCtrl,
                      ID_MTA_AT_PHY_INIT_CNF,
                      sizeof(stSndAtPhyInitCnf),
                      (VOS_UINT8*)&stSndAtPhyInitCnf);

        PS_MEM_FREE(UEPS_PID_MTA, pstPhyStartReq);
        return;
    }

    /* 消息初始化 */
    PS_MEM_SET( ((VOS_UINT8*)pstPhyStartReq + VOS_MSG_HEAD_LENGTH), 0,
                sizeof(MTA_UPHY_START_UPHY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填消息包 */
    pstPhyStartReq->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstPhyStartReq->ulSenderCpuId         = VOS_LOCAL_CPUID;
    pstPhyStartReq->ulSenderPid           = UEPS_PID_MTA;
    pstPhyStartReq->ulReceiverPid         = DSP_PID_STARTUP;
    pstPhyStartReq->usMsgID               = ID_MTA_UPHY_START_UPHY_REQ;

    /* 发送消息到DSP_PID_STARTUP模块 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstPhyStartReq))
    {
        MTA_ERROR_LOG("TAF_MTA_RcvAtPhyInitReq()--PS_SEND_MSG():WARNING:SEND MSG FIAL");

        /* 消息内容重置 */
        PS_MEM_SET(&stSndAtPhyInitCnf, 0x0, sizeof(MTA_AT_PHY_INIT_CNF_STRU));
        stSndAtPhyInitCnf.enResult = MTA_AT_RESULT_ERROR;

        /* 给AT模块发送失败消息 */
        TAF_MTA_SndAtMsg(&pstAtMtaReqMsg->stAppCtrl,
                      ID_MTA_AT_PHY_INIT_CNF,
                      sizeof(stSndAtPhyInitCnf),
                      (VOS_UINT8*)&stSndAtPhyInitCnf );

        return;
    }

    /* 启动保护定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_DSP_INIT_CNF, TI_TAF_MTA_WAIT_DSP_INIT_CNF_TIMER_LEN);

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_DSP_INIT_CNF,
                                     (VOS_UINT8*)&pstAtMtaReqMsg->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtSetFreqLockReq
 功能描述  : 处理at下发的设置FREQ LOCK命令
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月11日
    作    者   : g00261581
    修改内容   : 新建
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtSetFreqLockReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstSetReq         = VOS_NULL_PTR;
    AT_MTA_SET_FREQ_LOCK_REQ_STRU      *pstSetFreqLockReq = VOS_NULL_PTR;
    MTA_AT_SET_FREQ_LOCK_CNF_STRU       stSetFreqLockCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulLength;

    pstSetReq                 = (AT_MTA_MSG_STRU *)pMsg;
    pstSetFreqLockReq         = (AT_MTA_SET_FREQ_LOCK_REQ_STRU *)(pstSetReq->aucContent);
    stSetFreqLockCnf.enResult = MTA_AT_RESULT_ERROR;

    /* 如果当前定时器已启动，则返回失败 */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_CHECK_FREQ_VALIDITY_CNF))
    {
        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_SET_FREQ_LOCK_CNF,
                         sizeof(stSetFreqLockCnf),
                         (VOS_UINT8*)&stSetFreqLockCnf);
        return;
    }

    ulResult = TAF_MTA_SndRrcSetFreqLockReq(pstSetFreqLockReq);

    if (VOS_OK != ulResult)
    {
        /* 消息发送失败，给at回复失败*/
        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_SET_FREQ_LOCK_CNF,
                         sizeof(stSetFreqLockCnf),
                         (VOS_UINT8*)&stSetFreqLockCnf);
        return;
    }

    /* 启动保护定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_CHECK_FREQ_VALIDITY_CNF,
                                 TI_TAF_MTA_WAIT_CHECK_FREQ_VALIDITY_CNF_TIMER_LEN);

    ulLength = (sizeof(AT_MTA_MSG_STRU) + sizeof(AT_MTA_SET_FREQ_LOCK_REQ_STRU)) - 4;

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_CHECK_FREQ_VALIDITY_CNF,
                                    (VOS_UINT8*)pstSetReq,
                                     ulLength);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvWrrFreqlockSetCnf
 功能描述  : MTA收到设置锁频信息结结果
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
VOS_VOID TAF_MTA_RcvWrrFreqlockSetCnf(
    VOS_VOID                           *pWrrCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf            = VOS_NULL_PTR;
    WRR_MTA_FREQLOCK_SET_CNF_STRU      *pstRcvWrrFreqlockCnf = VOS_NULL_PTR;
    MTA_AT_WRR_FREQLOCK_SET_CNF_STRU    stSndAtFreqlockCnf;

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_FREQLOCK_SET_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrFreqlockSetCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_WRR_FREQLOCK_SET_CNF);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_FREQLOCK_SET_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrFreqlockSetCnf: get command buffer failed!");
        return;
    }

    pstRcvWrrFreqlockCnf        = (WRR_MTA_FREQLOCK_SET_CNF_STRU *)pWrrCnfMsg;
    stSndAtFreqlockCnf.ulResult = pstRcvWrrFreqlockCnf->ulResult;

    /* 给at回消息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_FREQLOCK_SET_CNF,
                     sizeof(stSndAtFreqlockCnf),
                     (VOS_UINT8*)&stSndAtFreqlockCnf );

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_FREQLOCK_SET_CNF);
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvWrrVersionSetCnf
 功能描述  : MTA收到设置RRC VERSION回复消息
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
VOS_VOID TAF_MTA_RcvWrrVersionSetCnf(
    VOS_VOID                           *pWrrCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                                *pstCmdBuf              = VOS_NULL_PTR;
    WRR_MTA_RRC_VERSION_SET_CNF_STRU                       *pstRcvWrrVersionSetCnf = VOS_NULL_PTR;
    MTA_AT_WRR_RRC_VERSION_SET_CNF_STRU                     stSndAtVersionSetCnf;

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_RRC_VERSION_SET_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrVersionSetCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_WRR_RRC_VERSION_SET_CNF);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_RRC_VERSION_SET_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrVersionSetCnf: get command buffer failed!");
        return;
    }

    pstRcvWrrVersionSetCnf        = (WRR_MTA_RRC_VERSION_SET_CNF_STRU *)pWrrCnfMsg;
    stSndAtVersionSetCnf.ulResult = pstRcvWrrVersionSetCnf->ulResult;

    /* 给at回消息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_RRC_VERSION_SET_CNF,
                     sizeof(stSndAtVersionSetCnf),
                     (VOS_UINT8*)&stSndAtVersionSetCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_RRC_VERSION_SET_CNF);
    return;
}



/*****************************************************************************
 函 数 名  : TAF_MTA_RcvWrrCellsrhSetCnf
 功能描述  : MTA收到设置CellSrh回复消息
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
VOS_VOID TAF_MTA_RcvWrrCellsrhSetCnf(
    VOS_VOID                           *pWrrCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                                *pstCmdBuf              = VOS_NULL_PTR;
    WRR_MTA_CELLSRH_SET_CNF_STRU                           *pstRcvWrrCellsrhSetCnf = VOS_NULL_PTR;
    MTA_AT_WRR_CELLSRH_SET_CNF_STRU                         stSndAtCellsrhSetCnf;

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_CELLSRH_SET_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrCellsrhSetCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_WRR_CELLSRH_SET_CNF);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_CELLSRH_SET_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrCellsrhSetCnf: get command buffer failed!");
        return;
    }

    pstRcvWrrCellsrhSetCnf            = (WRR_MTA_CELLSRH_SET_CNF_STRU *)pWrrCnfMsg;
    stSndAtCellsrhSetCnf.ulResult     = pstRcvWrrCellsrhSetCnf->ulResult;

    /* 给at回消息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_CELLSRH_SET_CNF,
                     sizeof(stSndAtCellsrhSetCnf),
                     (VOS_UINT8*)&stSndAtCellsrhSetCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_CELLSRH_SET_CNF);
    return;
}



/*****************************************************************************
 函 数 名  : TAF_MTA_RcvWrrFreqlockQryCnf
 功能描述  : MTA收到查询锁频信息的回复消息
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
VOS_VOID TAF_MTA_RcvWrrFreqlockQryCnf(
    VOS_VOID                           *pWrrCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf            = VOS_NULL_PTR;
    WRR_MTA_FREQLOCK_QRY_CNF_STRU      *pstRcvWrrFreqlockCnf = VOS_NULL_PTR;
    MTA_AT_WRR_FREQLOCK_QRY_CNF_STRU    stSndAtFreqlockCnf;

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_FREQLOCK_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrFreqlockQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_WRR_FREQLOCK_QRY_CNF);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_FREQLOCK_QRY_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrFreqlockQryCnf: get command buffer failed!");
        return;
    }

    pstRcvWrrFreqlockCnf              = (WRR_MTA_FREQLOCK_QRY_CNF_STRU *)pWrrCnfMsg;
    stSndAtFreqlockCnf.ulResult       = pstRcvWrrFreqlockCnf->ulResult;
    stSndAtFreqlockCnf.stFreqLockInfo.ucFreqLockEnable = pstRcvWrrFreqlockCnf->stFreqLockInfo.ucFreqLockEnable;
    stSndAtFreqlockCnf.stFreqLockInfo.usLockedFreq     = pstRcvWrrFreqlockCnf->stFreqLockInfo.usLockedFreq;
    PS_MEM_SET(stSndAtFreqlockCnf.stFreqLockInfo.aucReserved, 0, sizeof(stSndAtFreqlockCnf.stFreqLockInfo.aucReserved));

    /* 给at回消息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_FREQLOCK_QRY_CNF,
                     sizeof(stSndAtFreqlockCnf),
                     (VOS_UINT8*)&stSndAtFreqlockCnf );

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_FREQLOCK_QRY_CNF);
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvWrrVersionQryCnf
 功能描述  : 收到查询RRCVERION回复消息
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
VOS_VOID TAF_MTA_RcvWrrVersionQryCnf(
    VOS_VOID                           *pWrrCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf              = VOS_NULL_PTR;
    WRR_MTA_RRC_VERSION_QRY_CNF_STRU   *pstRcvWrrVersionQryCnf = VOS_NULL_PTR;
    MTA_AT_WRR_RRC_VERSION_QRY_CNF_STRU stSndAtVersionQryCnf;

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_RRC_VERSION_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrVersionQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_WRR_RRC_VERSION_QRY_CNF);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_RRC_VERSION_QRY_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrVersionQryCnf: get command buffer failed!");
        return;
    }

    pstRcvWrrVersionQryCnf            = (WRR_MTA_RRC_VERSION_QRY_CNF_STRU *)pWrrCnfMsg;
    stSndAtVersionQryCnf.ulResult     = pstRcvWrrVersionQryCnf->ulResult;
    stSndAtVersionQryCnf.ucRrcVersion = pstRcvWrrVersionQryCnf->ucRrcVersion;
    PS_MEM_SET((stSndAtVersionQryCnf.aucReserved), 0, sizeof(stSndAtVersionQryCnf.aucReserved));

    /* 给at回消息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_RRC_VERSION_QRY_CNF,
                     sizeof(stSndAtVersionQryCnf),
                     (VOS_UINT8*)&stSndAtVersionQryCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_RRC_VERSION_QRY_CNF);
    return;
}



/*****************************************************************************
 函 数 名  : TAF_MTA_RcvWrrCellsrhQryCnf
 功能描述  : 收到查询cellsrh回复消息
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
VOS_VOID TAF_MTA_RcvWrrCellsrhQryCnf(
    VOS_VOID                           *pWrrCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf              = VOS_NULL_PTR;
    WRR_MTA_CELLSRH_QRY_CNF_STRU       *pstRcvWrrCellsrhQryCnf = VOS_NULL_PTR;
    MTA_AT_WRR_CELLSRH_QRY_CNF_STRU     stSndAtCellsrhQryCnf;

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_CELLSRH_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrCellsrhQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_WRR_CELLSRH_QRY_CNF);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_CELLSRH_QRY_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrCellsrhQryCnf: get command buffer failed!");
        return;
    }

    pstRcvWrrCellsrhQryCnf                = (WRR_MTA_CELLSRH_QRY_CNF_STRU *)pWrrCnfMsg;
    stSndAtCellsrhQryCnf.ulResult         = pstRcvWrrCellsrhQryCnf->ulResult;
    stSndAtCellsrhQryCnf.ucCellSearchType = pstRcvWrrCellsrhQryCnf->ucCellSearchType;
    PS_MEM_SET((stSndAtCellsrhQryCnf.aucReserve), 0, sizeof(stSndAtCellsrhQryCnf.aucReserve));

    /* 给at回消息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_CELLSRH_QRY_CNF,
                     sizeof(stSndAtCellsrhQryCnf),
                     (VOS_UINT8*)&stSndAtCellsrhQryCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_CELLSRH_QRY_CNF);
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvRrcSetNCellMonitorCnf
 功能描述  : mta收到gas ID_GRR_MTA_NCELL_MONITOR_SET_CNF消息处理函数
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : s00217060
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvRrcSetNCellMonitorCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                                *pstCmdBuf       = VOS_NULL_PTR;
    GRR_MTA_NCELL_MONITOR_SET_CNF_STRU                     *pstGrrMtaSetCnf = VOS_NULL_PTR;
    MTA_AT_UNSOLICITED_RPT_SET_CNF_STRU                     stMtaAtSetCnf;

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_SET_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvRrcSetNCellMonitorCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_SET_CNF);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_SET_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvRrcSetNCellMonitorCnf: get command buffer failed!");
        return;
    }

    PS_MEM_SET(&stMtaAtSetCnf, 0, sizeof(stMtaAtSetCnf));
    pstGrrMtaSetCnf        = (GRR_MTA_NCELL_MONITOR_SET_CNF_STRU *)pMsg;

    if (VOS_OK == pstGrrMtaSetCnf->ulResult)
    {
        stMtaAtSetCnf.enResult = MTA_AT_RESULT_NO_ERROR;
    }
    else
    {
        stMtaAtSetCnf.enResult = MTA_AT_RESULT_ERROR;
    }

    /* 给at回消息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_NCELL_MONITOR_SET_CNF,
                     sizeof(stMtaAtSetCnf),
                     (VOS_UINT8*)&stMtaAtSetCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_SET_CNF);
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvRrcQryNCellMonitorCnf
 功能描述  : mta收到gas ID_GRR_MTA_NCELL_MONITOR_QRY_CNF消息处理函数
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : s00217060
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvRrcQryNCellMonitorCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                                *pstCmdBuf       = VOS_NULL_PTR;
    GRR_MTA_NCELL_MONITOR_QRY_CNF_STRU                     *pstGrrMtaQryCnf = VOS_NULL_PTR;
    MTA_AT_NCELL_MONITOR_QRY_CNF_STRU                       stMtaAtQryCnf;

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvRrcQryNCellMonitorCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_QRY_CNF);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_QRY_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvRrcQryNCellMonitorCnf: get command buffer failed!");
        return;
    }

    PS_MEM_SET(&stMtaAtQryCnf, 0, sizeof(stMtaAtQryCnf));
    pstGrrMtaQryCnf            = (GRR_MTA_NCELL_MONITOR_QRY_CNF_STRU *)pMsg;
    stMtaAtQryCnf.enResult     = pstGrrMtaQryCnf->ulResult;
    stMtaAtQryCnf.ucSwitch     = pstGrrMtaQryCnf->ucSwitch;
    stMtaAtQryCnf.ucNcellState = pstGrrMtaQryCnf->enNcellState;

    /* 给at回消息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_NCELL_MONITOR_QRY_CNF,
                     sizeof(stMtaAtQryCnf),
                     (VOS_UINT8*)&stMtaAtQryCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_QRY_CNF);
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvPhyInitCnf
 功能描述  : MTA模块收到PHY发来的ID_UPHY_MTA_START_UPHY_CNF结果确认消息的处理函数
 输入参数  : pMsg   -- PHY发送的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月25日
    作    者   : y00176023
    修改内容   : 新增^PHYINIT命令
*****************************************************************************/
VOS_VOID TAF_MTA_RcvPhyInitCnf(VOS_VOID *pMsg)
{
    MTA_AT_RESULT_ENUM_UINT32                               enResult;
    MTA_AT_PHY_INIT_CNF_STRU                                stSndAtPhyInitCnf;
    UPHY_MTA_START_UPHY_CNF_STRU                           *pstPhyStartCnf     = VOS_NULL_PTR;
    TAF_MTA_CMD_BUFFER_STRU                                *pstCmdBuf          = VOS_NULL_PTR;

    pstPhyStartCnf = (UPHY_MTA_START_UPHY_CNF_STRU*)pMsg;

    /* 重置结构体 */
    PS_MEM_SET(&stSndAtPhyInitCnf, 0, sizeof(MTA_AT_PHY_INIT_CNF_STRU));

    /* 查看timer状态 */
    if (TAF_MTA_TIMER_STATUS_RUNING != TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_DSP_INIT_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvPhyInitCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 停止定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_DSP_INIT_CNF);

    /* 获取命令buff */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_DSP_INIT_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    /* phy结果转换 */
    if (MTA_UPHY_INIT_STATUS_SUCCESS == pstPhyStartCnf->enInitStatus)
    {
        enResult = MTA_AT_RESULT_NO_ERROR;
    }
    else
    {
        enResult = MTA_AT_RESULT_ERROR;
    }

    /* 填写消息结构 */
    stSndAtPhyInitCnf.enResult = enResult;

    /* 给AT模块发送ID_MTA_AT_PHY_INIT_CNF消息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_PHY_INIT_CNF,
                     sizeof(stSndAtPhyInitCnf),
                     (VOS_UINT8*)&stSndAtPhyInitCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvRrcNCellMonitorInd
 功能描述  : mta收到gas ID_GRR_MTA_NCELL_MONITOR_IND消息处理函数
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvRrcNCellMonitorInd(
    VOS_VOID                           *pMsg
)
{
    GRR_MTA_NCELL_MONITOR_IND_STRU                     *pstGrrMtaQryCnf = VOS_NULL_PTR;
    MTA_AT_NCELL_MONITOR_IND_STRU                       stMtaAtInd;
    AT_APPCTRL_STRU                                     stAppCtrl;

    /* 填写主动上报的消息内容 */
    PS_MEM_SET(&stMtaAtInd, 0, sizeof(stMtaAtInd));
    pstGrrMtaQryCnf        = (GRR_MTA_NCELL_MONITOR_IND_STRU *)pMsg;
    stMtaAtInd.ucNcellState = pstGrrMtaQryCnf->enNcellState;

    /* 填写消息头，上报类型为广播事件 */
    PS_MEM_SET(&stAppCtrl, 0, sizeof(stAppCtrl));
    stAppCtrl.usClientId = MTA_CLIENTID_BROADCAST;
    stAppCtrl.ucOpId     = MTA_INVALID_TAB_INDEX;

    /* 给at回消息 */
    TAF_MTA_SndAtMsg(&stAppCtrl,
                     ID_MTA_AT_NCELL_MONITOR_IND,
                     sizeof(stMtaAtInd),
                     (VOS_UINT8*)&stMtaAtInd);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MTA_RcvRrcJamDetectCnf
 功能描述  : MTA收到GAS ID_RRC_MTA_JAM_DETECT_CNF消息处理函数
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月4日
    作    者   : g00261581
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvRrcJamDetectCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf       = VOS_NULL_PTR;
    RRC_MTA_JAM_DETECT_CNF_STRU        *pstGrrMtaSetCnf = VOS_NULL_PTR;
    MTA_AT_SET_JAM_DETECT_CNF_STRU      stMtaAtSetCnf;

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_JAM_DETECT_SET_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvRrcJamDetectCnf: Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_JAM_DETECT_SET_CNF);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_JAM_DETECT_SET_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvRrcJamDetectCnf: get command buffer failed!");
        return;
    }

    pstGrrMtaSetCnf = (RRC_MTA_JAM_DETECT_CNF_STRU *)pMsg;

    PS_MEM_SET(&stMtaAtSetCnf, 0, sizeof(stMtaAtSetCnf));

    if (MTA_RRC_RESULT_NO_ERROR == pstGrrMtaSetCnf->enResult)
    {
        stMtaAtSetCnf.enResult = MTA_AT_RESULT_NO_ERROR;
    }
    else
    {
        stMtaAtSetCnf.enResult = MTA_AT_RESULT_ERROR;
    }

    /* 给at回消息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_SET_JAM_DETECT_CNF,
                     sizeof(stMtaAtSetCnf),
                     (VOS_UINT8*)&stMtaAtSetCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_JAM_DETECT_SET_CNF);
    return;

}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvRrcJamDetectInd
 功能描述  : MTA收到GAS ID_RRC_MTA_JAM_DETECT_IND消息处理函数
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月4日
    作    者   : g00261581
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvRrcJamDetectInd(
    VOS_VOID                           *pMsg
)
{
    RRC_MTA_JAM_DETECT_IND_STRU        *pstJamDetectInd = VOS_NULL_PTR;
    MTA_AT_JAM_DETECT_IND_STRU          stMtaAtInd;
    AT_APPCTRL_STRU                     stAppCtrl;
    NV_NAS_JAM_DETECT_CFG_STRU          stNvJamDetect;

    /* 初始化消息变量 */
    PS_MEM_SET(&stNvJamDetect, 0x0, sizeof(stNvJamDetect));

    pstJamDetectInd = (RRC_MTA_JAM_DETECT_IND_STRU *)pMsg;

    /* 填写主动上报的消息内容 */
    PS_MEM_SET(&stMtaAtInd, 0, sizeof(stMtaAtInd));
    stMtaAtInd.enJamResult = (MTA_AT_JAM_RESULT_ENUM_UINT32)pstJamDetectInd->enResult;

    /* 填写消息头，上报类型为广播事件 */
    PS_MEM_SET(&stAppCtrl, 0, sizeof(stAppCtrl));
    stAppCtrl.usClientId = MTA_CLIENTID_BROADCAST;
    stAppCtrl.ucOpId     = MTA_INVALID_TAB_INDEX;

    /* 通过读取NV来获取Jam Detect当前配置值 */
    if (NV_OK != NV_Read(en_NV_Item_JAM_DETECT_CFG,
                         &stNvJamDetect,
                         sizeof(NV_NAS_JAM_DETECT_CFG_STRU)))
    {
        MTA_ERROR_LOG("TAF_MTA_RcvRrcJamDetectInd: NV_Read en_NV_Item_JAM_DETECT_CFG fail!");
        return;
    }

    /* 如果jam detect功能未使能，即使收到GAS消息，也不再上报 */
    if (VOS_FALSE == stNvJamDetect.ucMode)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvRrcJamDetectInd: Jam Detect function is disabled!");
        return ;
    }

    /* 给at回消息 */
    TAF_MTA_SndAtMsg(&stAppCtrl,
                     ID_MTA_AT_JAM_DETECT_IND,
                     sizeof(stMtaAtInd),
                     (VOS_UINT8*)&stMtaAtInd);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvRrcCheckFreqValidityCnf
 功能描述  : MTA收到各个接入层发送来的ID_RRC_MTA_CHECK_FREQ_VALIDITY_CNF消息处理函数
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月12日
    作    者   : g00261581
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvRrcCheckFreqValidityCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                                *pstCmdBuf         = VOS_NULL_PTR;
    AT_MTA_MSG_STRU                                        *pstAtMtaMsgBuf    = VOS_NULL_PTR;
    RRC_MTA_CHECK_FREQ_VALIDITY_CNF_STRU                   *pstCheckCnf       = VOS_NULL_PTR;
    MTA_AT_SET_FREQ_LOCK_CNF_STRU                           stMtaAtSetCnf;

    /* 初始化消息变量 */
    stMtaAtSetCnf.enResult = MTA_AT_RESULT_ERROR;

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_CHECK_FREQ_VALIDITY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvRrcCheckFreqValidityCnf:Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_CHECK_FREQ_VALIDITY_CNF);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_CHECK_FREQ_VALIDITY_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvRrcCheckFreqValidityCnf: get command buffer failed!");
        return;
    }

    /* 取出之前保存的锁频命令配置参数 */
    pstAtMtaMsgBuf = (AT_MTA_MSG_STRU *)pstCmdBuf->pucMsgInfo;

    /* 只有频点有效而且写NV成功后，才会继续上报AT正确结果 */
    pstCheckCnf    = (RRC_MTA_CHECK_FREQ_VALIDITY_CNF_STRU *)pMsg;

    if (MTA_RRC_RESULT_NO_ERROR == pstCheckCnf->enResult)
    {
        if (NV_OK == NV_Write(en_NV_Item_FREQ_LOCK_CFG,
                              pstAtMtaMsgBuf->aucContent,
                              sizeof(AT_MTA_SET_FREQ_LOCK_REQ_STRU)))
        {
            stMtaAtSetCnf.enResult = MTA_AT_RESULT_NO_ERROR;
        }
    }

    /* 给at回消息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)&(pstAtMtaMsgBuf->stAppCtrl),
                     ID_MTA_AT_SET_FREQ_LOCK_CNF,
                     sizeof(stMtaAtSetCnf),
                     (VOS_UINT8*)&stMtaAtSetCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_CHECK_FREQ_VALIDITY_CNF);
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiReqFreqlockSetExpired
 功能描述  : 设置^FREQLOCK命令执行超时
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
VOS_VOID TAF_MTA_RcvTiReqFreqlockSetExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_WRR_FREQLOCK_SET_CNF_STRU    stSetFreqlockCnf;

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_FREQLOCK_SET_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        /*定时器超时log*/
        MTA_ERROR_LOG("TAF_MTA_RcvTiReqFreqlockSetExpired: get command buffer failed!");
        return;
    }

    PS_MEM_SET(&stSetFreqlockCnf, 0x0, sizeof(stSetFreqlockCnf));

    stSetFreqlockCnf.ulResult = VOS_ERR;

    /* 上报给AT模块错误信息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_FREQLOCK_SET_CNF,
                     sizeof(stSetFreqlockCnf),
                     (VOS_UINT8*)&stSetFreqlockCnf );


    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiReqRrcVersionSetExpired
 功能描述  : RRC VERSION设置超时处理
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
VOS_VOID TAF_MTA_RcvTiReqRrcVersionSetExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                                *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_WRR_RRC_VERSION_SET_CNF_STRU                     stVersionSetCnf;

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_RRC_VERSION_SET_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        /*定时器超时log*/
        MTA_ERROR_LOG("TAF_MTA_RcvTiReqRrcVersionSetExpired: get command buffer failed!");
        return;
    }

    PS_MEM_SET(&stVersionSetCnf, 0x0, sizeof(stVersionSetCnf));

    stVersionSetCnf.ulResult = VOS_ERR;

    /* 上报给AT模块错误信息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_RRC_VERSION_SET_CNF,
                     sizeof(stVersionSetCnf),
                     (VOS_UINT8*)&stVersionSetCnf );


    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;

}



/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiReqCellsrhSetExpired
 功能描述  : CELLSRH设置超时处理
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
VOS_VOID TAF_MTA_RcvTiReqCellsrhSetExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                                *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_WRR_CELLSRH_SET_CNF_STRU                         stCellsrhSetCnf;

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_CELLSRH_SET_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        /*定时器超时log*/
        MTA_ERROR_LOG("TAF_MTA_RcvTiReqCellsrhSetExpired: get command buffer failed!");
        return;
    }

    PS_MEM_SET(&stCellsrhSetCnf, 0x0, sizeof(stCellsrhSetCnf));

    stCellsrhSetCnf.ulResult = VOS_ERR;

    /* 上报给AT模块错误信息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_CELLSRH_SET_CNF,
                     sizeof(stCellsrhSetCnf),
                     (VOS_UINT8*)&stCellsrhSetCnf );


    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;

}


/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiReqFreqlockQryExpired
 功能描述  : 查询FREQLOCK超时处理
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
VOS_VOID TAF_MTA_RcvTiReqFreqlockQryExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_WRR_FREQLOCK_QRY_CNF_STRU    stQryFreqlockCnf;

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_FREQLOCK_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        /*定时器超时log*/
        MTA_ERROR_LOG("TAF_MTA_RcvTiReqFreqlockQryExpired: get command buffer failed!");
        return;
    }

    PS_MEM_SET(&stQryFreqlockCnf, 0x0, sizeof(stQryFreqlockCnf));

    stQryFreqlockCnf.ulResult = VOS_ERR;

    /* 上报给AT模块错误信息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_FREQLOCK_QRY_CNF,
                     sizeof(stQryFreqlockCnf),
                     (VOS_UINT8*)&stQryFreqlockCnf );


    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiReqRrcVersionQryExpired
 功能描述  : 查询RRC VERSION超时处理
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
VOS_VOID TAF_MTA_RcvTiReqRrcVersionQryExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                                *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_WRR_RRC_VERSION_QRY_CNF_STRU                     stVersionQryCnf;

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_RRC_VERSION_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        /*定时器超时log*/
        MTA_ERROR_LOG("TAF_MTA_RcvTiReqRrcVersionQryExpired: get command buffer failed!");
        return;
    }

    PS_MEM_SET(&stVersionQryCnf, 0x0, sizeof(stVersionQryCnf));

    stVersionQryCnf.ulResult = VOS_ERR;

    /* 上报给AT模块错误信息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_RRC_VERSION_QRY_CNF,
                     sizeof(stVersionQryCnf),
                     (VOS_UINT8*)&stVersionQryCnf );


    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;

}



/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiReqCellsrhQryExpired
 功能描述  : 查询CELLSRH超时处理
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
VOS_VOID TAF_MTA_RcvTiReqCellsrhQryExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                                *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_WRR_CELLSRH_QRY_CNF_STRU                         stCellsrhQryCnf;

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_CELLSRH_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        /*定时器超时log*/
        MTA_ERROR_LOG("TAF_MTA_RcvTiReqCellsrhQryExpired: get command buffer failed!");
        return;
    }

    PS_MEM_SET(&stCellsrhQryCnf, 0x0, sizeof(stCellsrhQryCnf));

    stCellsrhQryCnf.ulResult = VOS_ERR;

    /* 上报给AT模块错误信息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_CELLSRH_QRY_CNF,
                     sizeof(stCellsrhQryCnf),
                     (VOS_UINT8*)&stCellsrhQryCnf );


    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;

}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiWaitGrrSetNCellMonitorExpired
 功能描述  : 等待GAS设置邻区主动上报开启/关闭回复保护定时器超时的处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
  1.日    期   : 2013年06月04日
    作    者   : s00217060
    修改内容   :支持^NCELLMONITOR新增函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitGrrSetNCellMonitorExpired(VOS_VOID *pMsg)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf   = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU              stSetCnf;

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_SET_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    PS_MEM_SET(&stSetCnf, 0x0, sizeof(stSetCnf));

    stSetCnf.enResult = MTA_AT_RESULT_ERROR;

    /* 上报给AT模块设置错误 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_NCELL_MONITOR_SET_CNF,
                     sizeof(stSetCnf),
                     (VOS_UINT8*)&stSetCnf );

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_SET_CNF);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiWaitGrrQryNCellMonitorExpired
 功能描述  : 等待GAS查询邻区主动上报回复保护定时器超时的处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
  1.日    期   : 2013年06月04日
    作    者   : s00217060
    修改内容   :支持^NCELLMONITOR新增函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitGrrQryNCellMonitorExpired(VOS_VOID *pMsg)
{
    TAF_MTA_CMD_BUFFER_STRU                *pstCmdBuf   = VOS_NULL_PTR;
    MTA_AT_NCELL_MONITOR_QRY_CNF_STRU       stQryCnf;

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));

    stQryCnf.enResult = MTA_AT_RESULT_ERROR;

    /* 上报给AT模块查询错误 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_NCELL_MONITOR_QRY_CNF,
                     sizeof(stQryCnf),
                     (VOS_UINT8*)&stQryCnf );

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_QRY_CNF);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiWaitGrrSetJamDetectExpired
 功能描述  : 设置JDR超时的处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
  1.日    期   : 2014年05月04日
    作    者   : g00261581
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitGrrSetJamDetectExpired(VOS_VOID *pMsg)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf   = VOS_NULL_PTR;
    MTA_AT_SET_JAM_DETECT_CNF_STRU      stQryCnf;

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_JAM_DETECT_SET_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));

    stQryCnf.enResult = MTA_AT_RESULT_ERROR;

    /* 上报给AT模块查询错误 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_SET_JAM_DETECT_CNF,
                     sizeof(stQryCnf),
                     (VOS_UINT8*)&stQryCnf );

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_JAM_DETECT_SET_CNF);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtPhyInitReq
 功能描述  : MTA模块收到AT发来的ID_AT_MTA_PHY_INIT_REQ请求消息的处理函数
 输入参数  : pMsg   -- AT发送的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月25日
    作    者   : y00176023
    修改内容   : 新增^PHYINIT命令
*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiPhyInitExpired(VOS_VOID *pMsg)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf;
    MTA_AT_PHY_INIT_CNF_STRU            stSndAtPhyInitCnf;

    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_DSP_INIT_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvTiPhyInitExpired: WARNING: buffer is null!");
        return;
    }

    /* 消息内容重置 */
    PS_MEM_SET(&stSndAtPhyInitCnf, 0x0, sizeof(MTA_AT_PHY_INIT_CNF_STRU));
    stSndAtPhyInitCnf.enResult = MTA_AT_RESULT_OPTION_TIMEOUT;

    /* 给AT模块发送失败消息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                  ID_MTA_AT_PHY_INIT_CNF,
                  sizeof(stSndAtPhyInitCnf),
                  (VOS_UINT8*)&stSndAtPhyInitCnf );


    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiWaitRrcCheckFreqValidityExpired
 功能描述  : 设置Freq Lock超时的处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
  1.日    期   : 2014年06月12日
    作    者   : g00261581
    修改内容   : 新增函数
*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitRrcCheckFreqValidityExpired(VOS_VOID *pMsg)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf      = VOS_NULL_PTR;
    AT_MTA_MSG_STRU                    *pstAtMtaMsgBuf = VOS_NULL_PTR;
    MTA_AT_SET_FREQ_LOCK_CNF_STRU       stSetCnf;

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_CHECK_FREQ_VALIDITY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    pstAtMtaMsgBuf = (AT_MTA_MSG_STRU *)pstCmdBuf->pucMsgInfo;

    stSetCnf.enResult = MTA_AT_RESULT_ERROR;

    /* 上报给AT模块查询错误 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)&(pstAtMtaMsgBuf->stAppCtrl),
                     ID_MTA_AT_SET_FREQ_LOCK_CNF,
                     sizeof(stSetCnf),
                     (VOS_UINT8*)&stSetCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_CHECK_FREQ_VALIDITY_CNF);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndWrrSetFreqlockReqMsg
 功能描述  : 给AS发送设置frelock消息
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
VOS_UINT32 TAF_MTA_SndWrrSetFreqlockReqMsg(
    MTA_WRR_FREQLOCK_CTRL_STRU         *pFreqlockCtrlPara
)
{
    VOS_UINT32                          ulLength;
    MTA_WRR_FREQLOCK_SET_REQ_STRU      *pstMtaWrrSetReq = VOS_NULL_PTR;

    /* 申请消息结构内存 */
    ulLength              = sizeof(MTA_WRR_FREQLOCK_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaWrrSetReq       = (MTA_WRR_FREQLOCK_SET_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaWrrSetReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrSetFreqlockReqMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    /* 构造消息结构体 */
    pstMtaWrrSetReq->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMtaWrrSetReq->ulSenderPid       = UEPS_PID_MTA;
    pstMtaWrrSetReq->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMtaWrrSetReq->ulReceiverPid     = WUEPS_PID_WRR;
    pstMtaWrrSetReq->ulMsgName         = ID_MTA_WRR_FREQLOCK_SET_REQ;

    /* 传递给消息包内容 */
    PS_MEM_CPY(&(pstMtaWrrSetReq->stFrelock), pFreqlockCtrlPara, sizeof(MTA_WRR_FREQLOCK_CTRL_STRU));

    /* 发送消息到AS */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaWrrSetReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrSetFreqlockReqMsg: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndWrrSetVersionReqMsg
 功能描述  : 给AS发送设置RRC VERSION 消息
 输入参数  : ucRrcVersion:设置版本
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月31日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndWrrSetVersionReqMsg(
    VOS_UINT8                           ucRrcVersion
)
{
    VOS_UINT32                          ulLength;
    MTA_WRR_RRC_VERSION_SET_REQ_STRU   *pstMtaWrrSetReq = VOS_NULL_PTR;

    /* 申请消息结构内存 */
    ulLength              = sizeof(MTA_WRR_RRC_VERSION_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaWrrSetReq       = (MTA_WRR_RRC_VERSION_SET_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaWrrSetReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrSetVersionReqMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    /* 构造消息结构体 */
    pstMtaWrrSetReq->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMtaWrrSetReq->ulSenderPid       = UEPS_PID_MTA;
    pstMtaWrrSetReq->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMtaWrrSetReq->ulReceiverPid     = WUEPS_PID_WRR;
    pstMtaWrrSetReq->ulMsgName         = ID_MTA_WRR_RRC_VERSION_SET_REQ;
    pstMtaWrrSetReq->ucRRCVersion      = ucRrcVersion;

    /* 传递给消息包内容 */
    PS_MEM_SET((pstMtaWrrSetReq->aucReserv), 0, sizeof(pstMtaWrrSetReq->aucReserv));

    /* 发送消息到AS */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaWrrSetReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrSetVersionReqMsg: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndWrrSetCellsrhReqMsg
 功能描述  : 给was发送设置Cellsrh消息
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
VOS_UINT32 TAF_MTA_SndWrrSetCellsrhReqMsg(
    VOS_UINT8                           ucCellSrh
)
{
    VOS_UINT32                          ulLength;
    MTA_WRR_CELLSRH_SET_REQ_STRU       *pstMtaWrrSetReq = VOS_NULL_PTR;

    /* 申请消息结构内存 */
    ulLength              = sizeof(MTA_WRR_CELLSRH_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaWrrSetReq       = (MTA_WRR_CELLSRH_SET_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaWrrSetReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrSetCellsrhReqMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    /* 构造消息结构体 */
    pstMtaWrrSetReq->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMtaWrrSetReq->ulSenderPid       = UEPS_PID_MTA;
    pstMtaWrrSetReq->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMtaWrrSetReq->ulReceiverPid     = WUEPS_PID_WRR;
    pstMtaWrrSetReq->ulMsgName         = ID_MTA_WRR_CELLSRH_SET_REQ;
    pstMtaWrrSetReq->ucCellSrh         = ucCellSrh;

    /* 传递给消息包内容 */
    PS_MEM_SET((pstMtaWrrSetReq->aucReserve), 0, sizeof(pstMtaWrrSetReq->aucReserve));

    /* 发送消息到AS */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaWrrSetReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrSetCellsrhReqMsg: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : TAF_MTA_SndWrrQryFreqlockReqMsg
 功能描述  : 给was发送查询锁频信息的消息
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
VOS_UINT32 TAF_MTA_SndWrrQryFreqlockReqMsg(VOS_VOID)
{

    VOS_UINT32                          ulLength;
    MTA_WRR_FREQLOCK_QRY_REQ_STRU      *pstMtaWrrQryReq = VOS_NULL_PTR;

    /* 申请消息结构内存 */
    ulLength              = sizeof(MTA_WRR_FREQLOCK_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaWrrQryReq       = (MTA_WRR_FREQLOCK_QRY_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaWrrQryReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrQryFreqlockReqMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    /* 构造消息结构体 */
    pstMtaWrrQryReq->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMtaWrrQryReq->ulSenderPid       = UEPS_PID_MTA;
    pstMtaWrrQryReq->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMtaWrrQryReq->ulReceiverPid     = WUEPS_PID_WRR;
    pstMtaWrrQryReq->ulMsgName         = ID_MTA_WRR_FREQLOCK_QRY_REQ;

    /* 发送消息到AS */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaWrrQryReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrQryFreqlockReqMsg: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndWrrQryRrcVersionReqMsg
 功能描述  : 给WAS发送查询RRC VERDION消息请求
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
VOS_UINT32 TAF_MTA_SndWrrQryRrcVersionReqMsg( VOS_VOID )
{
    VOS_UINT32                          ulLength;
    MTA_WRR_RRC_VERSION_QRY_REQ_STRU   *pstMtaWrrQryVersionReq = VOS_NULL_PTR;

    /* 申请消息结构内存 */
    ulLength                    = sizeof(MTA_WRR_RRC_VERSION_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaWrrQryVersionReq      = (MTA_WRR_RRC_VERSION_QRY_REQ_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);
    if (VOS_NULL_PTR == pstMtaWrrQryVersionReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrQryRrcVersionReqMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    /* 构造消息结构体 */
    pstMtaWrrQryVersionReq->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMtaWrrQryVersionReq->ulSenderPid       = UEPS_PID_MTA;
    pstMtaWrrQryVersionReq->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMtaWrrQryVersionReq->ulReceiverPid     = WUEPS_PID_WRR;
    pstMtaWrrQryVersionReq->ulMsgName         = ID_MTA_WRR_RRC_VERSION_QRY_REQ;

    /* 发送消息到AS */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaWrrQryVersionReq))
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrQryRrcVersionReqMsg: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}



/*****************************************************************************
 函 数 名  : TAF_MTA_SndWrrQryCellsrhReqMsg
 功能描述  : 给Was发送查询cellsrh消息请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月31日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndWrrQryCellsrhReqMsg( VOS_VOID )
{
    VOS_UINT32                          ulLength;
    MTA_WRR_CELLSRH_QRY_REQ_STRU       *pstMtaWrrQryCellsrhReq = VOS_NULL_PTR;

    /* 申请消息结构内存 */
    ulLength                    = sizeof(MTA_WRR_CELLSRH_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaWrrQryCellsrhReq      = (MTA_WRR_CELLSRH_QRY_REQ_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);
    if (VOS_NULL_PTR == pstMtaWrrQryCellsrhReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrQryCellsrhReqMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    /* 构造消息结构体 */
    pstMtaWrrQryCellsrhReq->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMtaWrrQryCellsrhReq->ulSenderPid       = UEPS_PID_MTA;
    pstMtaWrrQryCellsrhReq->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMtaWrrQryCellsrhReq->ulReceiverPid     = WUEPS_PID_WRR;
    pstMtaWrrQryCellsrhReq->ulMsgName         = ID_MTA_WRR_CELLSRH_QRY_REQ;

    /* 发送消息到AS */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaWrrQryCellsrhReq))
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrQryCellsrhReqMsg: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndGrrNCellMonitorSetReq
 功能描述  : mta给gas发送LTE/TD邻区是否主动上报设置消息函数
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月1日
    作    者   : s00217060
    修改内容   : 新增函数

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndGrrNCellMonitorSetReq(
    VOS_UINT8                         ucRptCmdStatus
)
{
    MTA_GRR_NCELL_MONITOR_SET_REQ_STRU          *pstNCellMonitorSetReq  = VOS_NULL_PTR;

    /* 分配内存 */
    pstNCellMonitorSetReq = (MTA_GRR_NCELL_MONITOR_SET_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA,
                                                              sizeof(MTA_GRR_NCELL_MONITOR_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 内存分配异常处理 */
    if (VOS_NULL_PTR == pstNCellMonitorSetReq)
    {
        MTA_WARNING_LOG("TAF_MTA_SndGrrNCellMonitorSetReq:alloc msg failed.");
        return VOS_ERR;
    }

    /* 填写新消息内容 */
    PS_MEM_SET(pstNCellMonitorSetReq, 0, sizeof(MTA_GRR_NCELL_MONITOR_SET_REQ_STRU));
    pstNCellMonitorSetReq->ulSenderPid      = UEPS_PID_MTA;
    pstNCellMonitorSetReq->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstNCellMonitorSetReq->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstNCellMonitorSetReq->ulReceiverPid    = UEPS_PID_GAS;
    pstNCellMonitorSetReq->ulMsgName        = ID_MTA_GRR_NCELL_MONITOR_SET_REQ;
    pstNCellMonitorSetReq->ulLength         = sizeof(MTA_GRR_NCELL_MONITOR_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstNCellMonitorSetReq->ucSwitch         = ucRptCmdStatus;

    /* 发送消息异常处理 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstNCellMonitorSetReq))
    {
        MTA_WARNING_LOG("TAF_MTA_SndGrrNCellMonitorSetReq: PS_SEND_MSG ERROR");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndGrrNCellMonitorQryReq
 功能描述  : mta给gas发送查询LTE/TD邻区消息函数
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月1日
    作    者   : s00217060
    修改内容   : 新增函数

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndGrrNCellMonitorQryReq(VOS_VOID)
{
    MTA_GRR_NCELL_MONITOR_QRY_REQ_STRU          *pstNCellMonitorQryReq  = VOS_NULL_PTR;

    /* 分配内存 */
    pstNCellMonitorQryReq = (MTA_GRR_NCELL_MONITOR_QRY_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA,
                                                              sizeof(MTA_GRR_NCELL_MONITOR_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 内存分配异常处理 */
    if (VOS_NULL_PTR == pstNCellMonitorQryReq)
    {
        MTA_WARNING_LOG("TAF_MTA_SndGrrNCellMonitorQryReq:alloc msg failed.");
        return VOS_ERR;
    }

    /* 填写新消息内容 */
    PS_MEM_SET(pstNCellMonitorQryReq, 0, sizeof(MTA_GRR_NCELL_MONITOR_QRY_REQ_STRU));
    pstNCellMonitorQryReq->ulSenderPid      = UEPS_PID_MTA;
    pstNCellMonitorQryReq->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstNCellMonitorQryReq->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstNCellMonitorQryReq->ulReceiverPid    = UEPS_PID_GAS;
    pstNCellMonitorQryReq->ulMsgName        = ID_MTA_GRR_NCELL_MONITOR_QRY_REQ;
    pstNCellMonitorQryReq->ulLength         = sizeof(MTA_GRR_NCELL_MONITOR_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 发送消息异常处理 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstNCellMonitorQryReq))
    {
        MTA_WARNING_LOG("TAF_MTA_SndGrrNCellMonitorQryReq: PS_SEND_MSG ERROR");
        return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : TAF_MTA_SndGrrSetJamDetectReq
 功能描述  : mta给gas发送干扰检查设置请求消息
 输入参数  : AT_MTA_SET_JAM_DETECT_REQ_STRU     *pstSetJdrReq
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月5日
    作    者   : g00261581
    修改内容   : 新增函数

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndGrrSetJamDetectReq(
    AT_MTA_SET_JAM_DETECT_REQ_STRU     *pstSetJdrReq
)
{
    VOS_UINT32                          ulLength;
    MTA_RRC_JAM_DETECT_REQ_STRU        *pstMtaGrrJamDetectReq = VOS_NULL_PTR;

    /* 申请消息结构内存 */
    ulLength              = sizeof(MTA_RRC_JAM_DETECT_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaGrrJamDetectReq = (MTA_RRC_JAM_DETECT_REQ_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);
    if (VOS_NULL_PTR == pstMtaGrrJamDetectReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndGrrSetJamDetectReq: Alloc msg fail!");
        return VOS_ERR;
    }

    /* 构造消息结构体 */
    pstMtaGrrJamDetectReq->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMtaGrrJamDetectReq->stMsgHeader.ulSenderPid       = UEPS_PID_MTA;
    pstMtaGrrJamDetectReq->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMtaGrrJamDetectReq->stMsgHeader.ulReceiverPid     = UEPS_PID_GAS;
    pstMtaGrrJamDetectReq->stMsgHeader.ulLength          = ulLength;
    pstMtaGrrJamDetectReq->stMsgHeader.ulMsgName         = ID_MTA_RRC_JAM_DETECT_REQ;

    pstMtaGrrJamDetectReq->enMode      = (MTA_RRC_JAM_MODE_ENUM_UINT8)pstSetJdrReq->ucFlag;
    pstMtaGrrJamDetectReq->ucMethod    = pstSetJdrReq->ucMethod;
    pstMtaGrrJamDetectReq->ucThreshold = pstSetJdrReq->ucThreshold;
    pstMtaGrrJamDetectReq->ucFreqNum   = pstSetJdrReq->ucFreqNum;

    /* 发送消息到AS */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaGrrJamDetectReq))
    {
        MTA_ERROR_LOG("TAF_MTA_SndGrrSetJamDetectReq: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndRrcSetFreqLockReq
 功能描述  : mta给各个接入层检查频点有效性请求消息
 输入参数  : AT_MTA_SET_FREQ_LOCK_REQ_STRU     *pstSetFreqLockReq
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月12日
    作    者   : g00261581
    修改内容   : 新增函数
*****************************************************************************/
VOS_UINT32 TAF_MTA_SndRrcSetFreqLockReq(
    AT_MTA_SET_FREQ_LOCK_REQ_STRU      *pstSetFreqLockReq
)
{
    MTA_RRC_CHECK_FREQ_VALIDITY_REQ_STRU   *pstMtaRrcCheckFreqReq = VOS_NULL_PTR;
    VOS_UINT32                              ulReceiverPid;
    VOS_UINT32                              ulLength;

    /* 解析出ReceiverPid */
    switch (pstSetFreqLockReq->enRatMode)
    {
        case AT_MTA_FREQLOCK_RATMODE_GSM:
            ulReceiverPid = UEPS_PID_GAS;
            break;

        case AT_MTA_FREQLOCK_RATMODE_WCDMA:
            ulReceiverPid = WUEPS_PID_WRR;
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case AT_MTA_FREQLOCK_RATMODE_LTE:
            ulReceiverPid = PS_PID_ERRC;
            break;
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
        case AT_MTA_FREQLOCK_RATMODE_TD:
            ulReceiverPid = TPS_PID_RRC;
            break;
#endif

        default:
            MTA_ERROR_LOG("TAF_MTA_SndRrcSetFreqLockReq: RatMode not support");
            return VOS_ERR;
    }

    /* 申请消息结构内存 */
    ulLength              = sizeof(MTA_RRC_CHECK_FREQ_VALIDITY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaRrcCheckFreqReq = (MTA_RRC_CHECK_FREQ_VALIDITY_REQ_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);
    if (VOS_NULL_PTR == pstMtaRrcCheckFreqReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndRrcSetFreqLockReq: Alloc msg fail!");
        return VOS_ERR;
    }

    pstMtaRrcCheckFreqReq->stMsgHeader.ulReceiverPid = ulReceiverPid;
    pstMtaRrcCheckFreqReq->stMsgHeader.ulMsgName     = ID_MTA_RRC_CHECK_FREQ_VALIDITY_REQ;
    pstMtaRrcCheckFreqReq->usFreq                    = pstSetFreqLockReq->usLockedFreq;
    pstMtaRrcCheckFreqReq->enBand                    = (MTA_RRC_GSM_BAND_ENUM_UINT16)pstSetFreqLockReq->enBand;

    /* 发送消息到AS */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaRrcCheckFreqReq))
    {
        MTA_ERROR_LOG("TAF_MTA_SndRrcSetFreqLockReq: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvNasAreaLostInd
 功能描述  : mta收到MMA发的丢网指示
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月19日
    作    者   : z60575
    修改内容   : 新增函数

  2.日    期   : 2015年5月29日
    作    者   : l00198894
    修改内容   : TSTS
*****************************************************************************/
VOS_VOID TAF_MTA_RcvNasAreaLostInd(
    VOS_VOID                           *pMsg
)
{
    VOS_INT32                           lRslt;

    /* 调用底软接口，如果返回0，表示PA正常，不做任何操作。返回非0表示PA异常，则进行钩包 */
#if defined(INSTANCE_1)
    lRslt = mdrv_pmu_check_pastar((PWC_COMM_MODEM_E)MODEM_ID_1);
#elif defined(INSTANCE_2)
    lRslt = mdrv_pmu_check_pastar((PWC_COMM_MODEM_E)MODEM_ID_2);
#else
    lRslt = mdrv_pmu_check_pastar((PWC_COMM_MODEM_E)MODEM_ID_0);
#endif

    if (VOS_OK == lRslt)
    {
        return;
    }

    NAS_EventReport(UEPS_PID_MTA,
                    NAS_OM_EVENT_PA_STAR_ABNORMAL,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTafAgentGetAntStateReq
 功能描述  : mta收到AT发的查询天线状态请求
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月2日
    作    者   : z60575
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTafAgentGetAntStateReq(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT                                ulAntState;
    MODEM_ID_ENUM_UINT16                    enModemId;
    TAFAGENT_MTA_GET_ANT_STATE_CNF_STRU    *pstMsg= VOS_NULL_PTR;

    enModemId   = VOS_GetModemIDFromPid(UEPS_PID_MTA);
    ulAntState  = 0;

    pstMsg = (TAFAGENT_MTA_GET_ANT_STATE_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA,
                                                                 sizeof(TAFAGENT_MTA_GET_ANT_STATE_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvTafAgentGetAntStateReq:alloc msg failed.");

        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH), 0, (sizeof(TAFAGENT_MTA_GET_ANT_STATE_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 消息头 */
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_MTA;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_TAFAGENT;
    pstMsg->enMsgId         = ID_TAFAGENT_MTA_GET_ANT_STATE_CNF;
    pstMsg->ulRslt          = VOS_ERR;
    pstMsg->usAntState      = 0;

    /* 调用底软接口获取天线状态 */
    if (VOS_OK == mdrv_anten_get_lockstate((PWC_COMM_MODEM_E)enModemId, &ulAntState))
    {
        pstMsg->ulRslt      = VOS_OK;
        pstMsg->usAntState  = (VOS_UINT16)ulAntState;
    }

    /* 给TAFAGENT发送查询回复 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMsg))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvTafAgentGetAntStateReq:send msg failed.");

        return;
    }

    return;
}

#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 函 数 名  : TAF_MTA_SndAcpuOmErrLogRptCnf
 功能描述  : 发送ID_OM_ERR_LOG_REPORT_CNF消息给ACPU OM
 输入参数  : pbuffer:数据内容
             ulBufUseLen:数据长度
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月23日
    作    者   : f00179208
    修改内容   : 商用ErrLog上报及工程模式扩展目新增函数
*****************************************************************************/
VOS_VOID TAF_MTA_SndAcpuOmErrLogRptCnf(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulBufUseLen
)
{
    OM_ERR_LOG_REPORT_CNF_STRU         *pstQryCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLen;

    /* 上报的消息总长度 */
    ulMsgLen  = ((sizeof(OM_ERR_LOG_REPORT_CNF_STRU) - VOS_MSG_HEAD_LENGTH) - 4) + ulBufUseLen;

    /* 消息空间申请 */
    pstQryCnf = (OM_ERR_LOG_REPORT_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulMsgLen);
    if (VOS_NULL_PTR == pstQryCnf)
    {
        MTA_ERROR_LOG("TAF_MTA_SndAcpuOmErrLogRptCnf: alloc msg fail!");
        return;
    }

    pstQryCnf->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstQryCnf->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstQryCnf->ulReceiverPid    = MSP_PID_DIAG_APP_AGENT;
    pstQryCnf->ulSenderPid      = UEPS_PID_MTA;
    pstQryCnf->ulMsgName        = ID_OM_ERR_LOG_REPORT_CNF;
    pstQryCnf->ulMsgType        = OM_ERR_LOG_MSG_ERR_REPORT;
    pstQryCnf->ulMsgSN          = 0;
    pstQryCnf->ulRptlen         = ulBufUseLen;

    /* buffer不为空时，len也是不会为空的 */
    if (VOS_NULL_PTR != pbuffer)
    {
        PS_MEM_CPY(pstQryCnf->aucContent, pbuffer, ulBufUseLen);
    }

    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstQryCnf))
    {
        MTA_ERROR_LOG("TAF_MTA_SndAcpuOmErrLogRptCnf: SEND MSG FAIL");
    }

    return;

}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAcpuOmErrLogRptReq
 功能描述  : MTA处理Acpu om发来的ERROR LOG故障上报请求
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月23日
    作    者   : f00179208
    修改内容   : 商用ErrLog上报及工程模式扩展目新增函数
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAcpuOmErrLogRptReq(
    VOS_VOID                           *pMsg
)
{
    VOS_CHAR                           *pbuffer   = VOS_NULL_PTR;
    VOS_UINT32                          ulBufUseLen;
    VOS_UINT32                          ulRealLen;
    VOS_UINT32                          ulTotalLen;
    NAS_ERR_LOG_MNTN_EVENT_STRU         stNasErrLogMntnEvent;

    /* 查询一下RING BUFFER中有多少数据，以便分配内存 */
    ulBufUseLen = TAF_SDC_GetErrLogRingBufferUseBytes();
    ulTotalLen = ulBufUseLen + sizeof(NAS_ERR_LOG_MNTN_EVENT_STRU);

    pbuffer = (VOS_CHAR *)PS_MEM_ALLOC(UEPS_PID_MTA, ulTotalLen);
    if (VOS_NULL_PTR == pbuffer)
    {
        /* 发送ID_OM_ERR_LOG_REPORT_CNF内容为空的消息给OM */
        TAF_MTA_SndAcpuOmErrLogRptCnf(VOS_NULL_PTR, 0);
        return;
    }

    PS_MEM_SET(pbuffer, 0, ulTotalLen);

    /* 获取RING BUFFER的内容 */
    ulRealLen = TAF_SDC_GetErrLogRingBufContent(pbuffer, ulBufUseLen);
    if (ulRealLen != ulBufUseLen)
    {
        /* 发送ID_OM_ERR_LOG_REPORT_CNF内容为空的消息给OM */
        TAF_MTA_SndAcpuOmErrLogRptCnf(VOS_NULL_PTR, 0);
        PS_MEM_FREE(UEPS_PID_MTA, pbuffer);
        return;
    }

    /* 将缓冲区溢出次数信息追加在RingBuf后面 */
    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stNasErrLogMntnEvent.stHeader,
                                      VOS_GetModemIDFromPid(UEPS_PID_MTA),
                                      NAS_ERR_LOG_ALM_MNTN,
                                      NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_MNTN),
                                      VOS_GetSlice(),
                                      (sizeof(NAS_ERR_LOG_MNTN_EVENT_STRU) - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stNasErrLogMntnEvent.ulCount = TAF_SDC_GetErrlogOverflowCnt();

    PS_MEM_CPY(pbuffer + ulBufUseLen, &stNasErrLogMntnEvent, sizeof(stNasErrLogMntnEvent));

    /* 获取完了后需要将RINGBUFFER清空 */
    TAF_SDC_CleanErrLogRingBuf();

    /* 重置溢出计数 */
    TAF_SDC_SetErrlogOverflowCnt(0);

    /* 可维可测BUF溢出的勾包 */
    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_MNTN,
                           UEPS_PID_MTA,
                           (VOS_UINT8 *)&stNasErrLogMntnEvent,
                           sizeof(stNasErrLogMntnEvent));

    /* 发送ID_OM_ERR_LOG_REPORT_CNF消息给ACPU OM */
    TAF_MTA_SndAcpuOmErrLogRptCnf(pbuffer, ulTotalLen);

    PS_MEM_FREE(UEPS_PID_MTA, pbuffer);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAcpuOmErrLogCtrlInd
 功能描述  : MTA处理Acpu om发来的ERROR LOG控制指示
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月23日
    作    者   : f00179208
    修改内容   : 商用ErrLog上报及工程模式扩展目新增函数
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAcpuOmErrLogCtrlInd(
    VOS_VOID                           *pMsg
)
{
    OM_ERROR_LOG_CTRL_IND_STRU         *pstRcvMsg = VOS_NULL_PTR;

    pstRcvMsg = (OM_ERROR_LOG_CTRL_IND_STRU*)pMsg;

    /* 更新ERRLOG控制标识 */
    if ((VOS_FALSE == pstRcvMsg->ucAlmStatus)
     || (VOS_TRUE  == pstRcvMsg->ucAlmStatus))
    {
        TAF_SDC_SetErrlogCtrlFlag(pstRcvMsg->ucAlmStatus);
    }

    if ((pstRcvMsg->ucAlmLevel >= NAS_ERR_LOG_CTRL_LEVEL_CRITICAL)
     && (pstRcvMsg->ucAlmLevel <= NAS_ERR_LOG_CTRL_LEVEL_WARNING))
    {
        TAF_SDC_SetErrlogAlmLevel(pstRcvMsg->ucAlmLevel);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndAcpuOmInfoCltRptCnf
 功能描述  : 发送ID_OM_INFO_CLT_REPORT_CNF消息给ACPU OM
 输入参数  : pMsg:数据内容
             ulLength:数据长度
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月15日
    作    者   : y00270069
    修改内容   : 云通信频点采集项目新增函数
*****************************************************************************/
VOS_VOID TAF_MTA_SndAcpuOmInfoCltRptCnf(
    VOS_VOID                           *pMsg,
    VOS_UINT32                          ulLength
)
{
    OM_INFO_CLT_REPORT_CNF_STRU        *pstQryCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLen;

    /* 上报的消息总长度 */
    ulMsgLen  = (sizeof(OM_INFO_CLT_REPORT_CNF_STRU) - 4) + ulLength;

    /* 申请消息结构内存 */
    pstQryCnf = (OM_INFO_CLT_REPORT_CNF_STRU *)TAF_MTA_ALLOC_MSG_WITH_HDR(ulMsgLen);

    if (VOS_NULL_PTR == pstQryCnf)
    {
        MTA_ERROR_LOG("TAF_MTA_SndAcpuOmInfoCltRptCnf: Alloc msg fail!");
        return;
    }

    /* 清空消息内容 */
    TAF_MTA_CLR_MSG_ENTITY(pstQryCnf);

    /* 填写消息头 */
    TAF_MTA_CFG_MSG_HDR(pstQryCnf, MSP_PID_DIAG_APP_AGENT, ID_OM_INFO_CLT_REPORT_CNF);

    /* 填写消息内容 */
    pstQryCnf->ulMsgType        = OM_ERR_LOG_MSG_INFO_CLT_CNF;
    pstQryCnf->ulMsgSN          = 0;
    pstQryCnf->ulRptLen         = ulLength;

    /* 消息不为空时，len也是不会为空的 */
    if (VOS_NULL_PTR != pMsg)
    {
        PS_MEM_CPY(pstQryCnf->aucContent, pMsg, ulLength);
    }

    /* 发送消息 */
    TAF_MTA_SEND_MSG(pstQryCnf);

    return;

}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAcpuOmInfoCltRptReq
 功能描述  : MTA处理Acpu om发来的信息采集上报请求
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月15日
    作    者   : y00270069
    修改内容   : 云通信频点采集项目新增函数
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAcpuOmInfoCltRptReq(
    VOS_VOID                           *pMsg
)
{
    OM_INFO_CLT_REPORT_REQ_STRU        *pstRcvMsg = VOS_NULL_PTR;

    /* 局部变量初始化 */
    pstRcvMsg = (OM_INFO_CLT_REPORT_REQ_STRU *)pMsg;

    switch (pstRcvMsg->enSceneType)
    {
        /* 判断当前请求类型为云通信信息采集 */
        case OM_INFO_CLT_SCENE_TYPE_FREQ_BAND:
            TAF_MTA_RcvAcpuOmFreqBandQryReq((VOS_VOID *)pstRcvMsg);
            break;

        /* 判断当前请求类型为上行发射功率采集 */
        case OM_INFO_CLT_SCENE_TYPE_NETWORK_INFO:

            TAF_MTA_RcvAcpuOmNetworkInfoQryReq((VOS_VOID *)pstRcvMsg);
            break;

        default:
            /* 发送ID_OM_INFO_CLT_REPORT_CNF内容为空的消息给OM */
            TAF_MTA_SndAcpuOmInfoCltRptCnf(VOS_NULL_PTR, 0);

            MTA_ERROR_LOG("TAF_MTA_RcvAcpuOmInfoCltRptReq: Scense type error!");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndAcpuOmFreqBandQryCnf
 功能描述  : 给ACPU OM回复频点频段收集信息
 输入参数  : enCltResult 收集结果
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月15日
    作    者   : y00270069
    修改内容   : 云通信频点采集项目新增函数
*****************************************************************************/
VOS_VOID TAF_MTA_SndAcpuOmFreqBandQryCnf(
    TAF_MTA_INFO_CLT_RESULT_ENUM_U32    enCltResult
)
{
    TAF_MTA_INFO_CLT_CTX_STRU                      *pstInfoCltCtx = VOS_NULL_PTR;
    NAS_INFO_CLT_CLOUD_FREQ_BAND_EVENT_STRU        *pstFreqInfo   = VOS_NULL_PTR;
    TAF_SDC_PLMN_ID_STRU                           *pstCurrPlmn   = VOS_NULL_PTR;
    VOS_UINT32                                      ulLength;

    /* 局部变量初始化 */

    /* 获取MTA上下文中保存云通信频点采集上下文 */
    pstInfoCltCtx = TAF_MTA_GetInfoCltAddr();
    pstFreqInfo   = pstInfoCltCtx->pstFreqInfoCltCtx;

    /* 云通信频点相关其他消息填充 */
    if (TAF_MTA_INFO_CLT_RESULT_SUCC == enCltResult)
    {
        pstCurrPlmn = TAF_SDC_GetCurrCampPlmnId();

        pstFreqInfo->enNetMode      = TAF_SDC_GetSysMode();
        pstFreqInfo->stPlmn.ulMcc   = pstCurrPlmn->ulMcc;
        pstFreqInfo->stPlmn.ulMnc   = pstCurrPlmn->ulMnc;
        pstFreqInfo->ucRac          = TAF_SDC_GetCurrCampRac();
        pstFreqInfo->usLac          = TAF_SDC_GetCurrCampLac();
        pstFreqInfo->ulCellId       = TAF_SDC_GetCurrCampCellId();

        ulLength = sizeof(NAS_INFO_CLT_CLOUD_FREQ_BAND_EVENT_STRU) - sizeof(OM_INFO_CLT_HEADER_STRU);

        NAS_COMM_BULID_INFOCLT_HEADER_INFO(&pstFreqInfo->stHeader,
                                          VOS_GetModemIDFromPid(UEPS_PID_MTA),
                                          OM_INFO_CLT_SCENE_TYPE_FREQ_BAND,
                                          ulLength);

        TAF_MTA_SndAcpuOmInfoCltRptCnf((VOS_VOID *)pstFreqInfo,
                                       sizeof(NAS_INFO_CLT_CLOUD_FREQ_BAND_EVENT_STRU));
    }
    else
    {
        /* 发送ID_OM_INFO_CLT_REPORT_CNF的消息给OM */
        TAF_MTA_SndAcpuOmInfoCltRptCnf(VOS_NULL_PTR, 0);
    }

    /* 发送完频点信息后需要释放频点信息的上下文 */
    TAF_MMA_FreeFreqInfoCltCtx();

    return;

}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAcpuOmFreqBandQryReq
 功能描述  : 收到频点频段信息采集请求
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月15日
    作    者   : y00270069
    修改内容   : 云通信频点采集项目新增函数
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAcpuOmFreqBandQryReq(
    VOS_VOID                           *pMsg
)
{
    OM_INFO_CLT_REPORT_REQ_STRU        *pstRcvMsg = VOS_NULL_PTR;
    MNTN_PLMN_ID_STRU                  *pstPlmnId = VOS_NULL_PTR;
    TAF_MTA_INFO_CLT_PLMN_LIST_STRU     stInfoCltPlmnList;

    /* 局部变量初始化 */
    pstRcvMsg   = (OM_INFO_CLT_REPORT_REQ_STRU*)pMsg;
    pstPlmnId   = (MNTN_PLMN_ID_STRU *)pstRcvMsg->aucContent;

    /* 检查下发的PLMN是否合法 */
    if (sizeof(MNTN_PLMN_ID_STRU) != pstRcvMsg->ulMsgLen)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvAcpuOmFreqBandQryReq: Receive PLMN Length is Invalid!");
        TAF_MTA_SndAcpuOmFreqBandQryCnf(TAF_MTA_INFO_CLT_RESULT_FAIL);
        return;
    }

    if (VOS_FALSE == TAF_SDC_IsPlmnIdValid((TAF_SDC_PLMN_ID_STRU *)pstPlmnId))
    {
        MTA_ERROR_LOG("TAF_MTA_RcvAcpuOmFreqBandQryReq: Receive PLMN Value is Invalid!");
        TAF_MTA_SndAcpuOmFreqBandQryCnf(TAF_MTA_INFO_CLT_RESULT_FAIL);
        return;
    }

    /* 目前只支持一个PLMN的查询功能 */
    PS_MEM_SET(&stInfoCltPlmnList, 0, sizeof(TAF_MTA_INFO_CLT_PLMN_LIST_STRU));
    stInfoCltPlmnList.ucPlmnNum = 1;
    PS_MEM_CPY(&stInfoCltPlmnList.astPlmnInfo[0], pstPlmnId, sizeof(MNTN_PLMN_ID_STRU));

    /* 分配频点收集的上下文 */
    TAF_MMA_AllocFreqInfoCltCtx();

    /* 如果平台支持GSM，则到GAS去获取频点信息 */
    if (VOS_TRUE == TAF_SDC_IsPlatformSupportGsm())
    {
        TAF_MTA_SndRrcPlmnFreqQryReq(&stInfoCltPlmnList, UEPS_PID_GAS);

        TAF_MTA_SetWaitFreqCltCnfFlag(TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_GAS);
    }

    /* 如果平台支持WCDMA，则到WAS去获取频点信息 */
    if (VOS_TRUE == TAF_SDC_IsPlatformSupportUtranFdd())
    {
        TAF_MTA_SndRrcPlmnFreqQryReq(&stInfoCltPlmnList, WUEPS_PID_WRR);

        TAF_MTA_SetWaitFreqCltCnfFlag(TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_WAS);
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* 如果平台支持LTE，则到LRRC去获取频点信息 */
    if (VOS_TRUE == TAF_SDC_IsPlatformSupportLte())
    {
        TAF_MTA_SndRrcPlmnFreqQryReq(&stInfoCltPlmnList, PS_PID_ERRC);

        TAF_MTA_SetWaitFreqCltCnfFlag(TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_LRRC);
    }
#endif

    /* 启动保护定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_FREQ_CLT_QRY_CNF,
                                 TI_TAF_MTA_WAIT_FREQ_CLT_QRY_CNF_TIMER_LEN);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MTA_SndRrcPlmnFreqQryReq
 功能描述  : MTA向RRC发送信息采集请求
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月15日
    作    者   : y00270069
    修改内容   : 云通信频点采集项目新增函数
*****************************************************************************/
VOS_VOID TAF_MTA_SndRrcPlmnFreqQryReq(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulReceiverPid
)
{
    TAF_MTA_INFO_CLT_PLMN_LIST_STRU    *pstPlmnList = VOS_NULL_PTR;
    MTA_RRC_PLMN_FREQ_QRY_REQ_STRU     *pstMsg      = VOS_NULL_PTR;

    /* 局部变量初始化 */
    pstPlmnList                  = (TAF_MTA_INFO_CLT_PLMN_LIST_STRU *)pData;

    /* 申请消息结构内存 */
    pstMsg = (MTA_RRC_PLMN_FREQ_QRY_REQ_STRU *)TAF_MTA_ALLOC_MSG_WITH_HDR(sizeof(MTA_RRC_PLMN_FREQ_QRY_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        MTA_ERROR_LOG("TAF_MTA_SndRrcPlmnFreqQryReq: Alloc msg fail!");
        return;
    }

    /* 清空消息内容 */
    TAF_MTA_CLR_MSG_ENTITY(pstMsg);

    /* 填写消息头 */
    TAF_MTA_CFG_MSG_HDR(pstMsg, ulReceiverPid, ID_MTA_RRC_PLMN_FREQ_QRY_REQ);

    /* 填写消息内容 */
    if (0 == pstPlmnList->ucPlmnNum)
    {
        pstMsg->enQueryType             = MTA_RRC_FREQ_QRY_TYPE_ALL_PLMN;
        pstMsg->ucPlmnIdNum             = 0;
    }
    else
    {
        pstMsg->enQueryType             = MTA_RRC_FREQ_QRY_TYPE_SPEC_PLMN;
        pstMsg->ucPlmnIdNum             = pstPlmnList->ucPlmnNum;
        PS_MEM_CPY(pstMsg->astPlmnIdList,
                   pstPlmnList->astPlmnInfo,
                   MTA_RRC_MAX_PLMN_NUM * sizeof(MNTN_PLMN_ID_STRU));
    }

    pstMsg->aucRsv[0]                   = 0;
    pstMsg->aucRsv[1]                   = 0;

    /* 发送消息 */
    TAF_MTA_SEND_MSG(pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvGasPlmnFreqQryCnf
 功能描述  : mta收到gas ID_RRC_MTA_PLMN_FREQ_QRY_CNF消息处理函数
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月15日
    作    者   : y00270069
    修改内容   : 云通信频点采集项目新增函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvGasPlmnFreqQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_INFO_CLT_CTX_STRU                              *pstInfoCltCtx           = VOS_NULL_PTR;
    RRC_MTA_PLMN_FREQ_QRY_CNF_STRU                         *pstRrcMtaPlmnFreqQryCnf = VOS_NULL_PTR;
    NAS_INFO_CLT_CLOUD_FREQ_BAND_EVENT_STRU                *pstFreqInfoClt          = VOS_NULL_PTR;
    RRC_MTA_GSM_PLMN_FREQ_LIST_STRU                        *pstGsmFreqList          = VOS_NULL_PTR;

    /* 局部变量初始化 */
    pstRrcMtaPlmnFreqQryCnf           = (RRC_MTA_PLMN_FREQ_QRY_CNF_STRU*)pMsg;

    /* 获取MTA上下文中保存云通信频点采集上下文 */
    pstInfoCltCtx  = TAF_MTA_GetInfoCltAddr();
    pstFreqInfoClt = pstInfoCltCtx->pstFreqInfoCltCtx;

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_FREQ_CLT_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvGasPlmnFreqQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 存贮GAS云通信频点信息 */
    pstGsmFreqList = &pstRrcMtaPlmnFreqQryCnf->u.stGsmFreqList;

    if (0 < pstGsmFreqList->ucPlmnNum)
    {
        /* 目前只支持单个PLMN频点采集 */
        pstFreqInfoClt->stGFreqList.stPlmnId.ulMcc = pstGsmFreqList->astPlmnFreqList[0].stPlmnId.ulMcc;
        pstFreqInfoClt->stGFreqList.stPlmnId.ulMnc = pstGsmFreqList->astPlmnFreqList[0].stPlmnId.ulMnc;

        if (0 < pstGsmFreqList->astPlmnFreqList[0].usFreqNum)
        {
            if (NAS_INFO_CLT_MAX_GSM_FREQ_NUM >= pstGsmFreqList->astPlmnFreqList[0].usFreqNum)
            {
                pstFreqInfoClt->stGFreqList.usFreqNum = pstGsmFreqList->astPlmnFreqList[0].usFreqNum;
            }
            else
            {
                pstFreqInfoClt->stGFreqList.usFreqNum = NAS_INFO_CLT_MAX_GSM_FREQ_NUM;
            }

            PS_MEM_CPY(&pstFreqInfoClt->stGFreqList.astFreqInfo[0],
                       &pstGsmFreqList->astPlmnFreqList[0].astFreqList[0],
                       sizeof(NAS_INFO_CLT_GU_FREQ_INFO_STRU) * pstFreqInfoClt->stGFreqList.usFreqNum);
        }
    }

    /*  更新信息采集标识 */
    TAF_MTA_ClrWaitFreqCltCnfFlag(TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_GAS);

    /* 判断信息采集是否完成 */
    if (TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_NULL != TAF_MTA_GetWaitFreqCltCnfFlag())
    {
        return;
    }

    /* 发云通信频点信息给OM */
    TAF_MTA_SndAcpuOmFreqBandQryCnf(TAF_MTA_INFO_CLT_RESULT_SUCC);

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_FREQ_CLT_QRY_CNF);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvWrrPlmnFreqQryCnf
 功能描述  : mta收到WAS ID_RRC_MTA_PLMN_FREQ_QRY_CNF消息处理函数
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月15日
    作    者   : y00270069
    修改内容   : 云通信频点采集项目新增函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvWrrPlmnFreqQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_INFO_CLT_CTX_STRU                              *pstInfoCltCtx           = VOS_NULL_PTR;
    RRC_MTA_PLMN_FREQ_QRY_CNF_STRU                         *pstRrcMtaPlmnFreqQryCnf = VOS_NULL_PTR;
    NAS_INFO_CLT_CLOUD_FREQ_BAND_EVENT_STRU                *pstFreqInfoClt          = VOS_NULL_PTR;
    RRC_MTA_WCDMA_PLMN_FREQ_LIST_STRU                      *pstWcdmaFreqList        = VOS_NULL_PTR;

    /* 局部变量初始化 */
    pstRrcMtaPlmnFreqQryCnf           = (RRC_MTA_PLMN_FREQ_QRY_CNF_STRU*)pMsg;

    /* 获取MTA上下文中保存云通信频点采集上下文 */
    pstInfoCltCtx  = TAF_MTA_GetInfoCltAddr();
    pstFreqInfoClt = pstInfoCltCtx->pstFreqInfoCltCtx;

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_FREQ_CLT_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrPlmnFreqQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 存贮WRR云通信频点信息 */
    pstWcdmaFreqList = &pstRrcMtaPlmnFreqQryCnf->u.stWcdmaFreqList;

    if (0 < pstWcdmaFreqList->ucPlmnNum)
    {
        /* 目前只支持单个PLMN频点采集 */
        pstFreqInfoClt->stWFreqList.stPlmnId.ulMcc = pstWcdmaFreqList->astPlmnFreqList[0].stPlmnId.ulMcc;
        pstFreqInfoClt->stWFreqList.stPlmnId.ulMnc = pstWcdmaFreqList->astPlmnFreqList[0].stPlmnId.ulMnc;

        if (0 < pstWcdmaFreqList->astPlmnFreqList[0].usFreqNum)
        {
            if (NAS_INFO_CLT_MAX_WCDMA_FREQ_NUM >= pstWcdmaFreqList->astPlmnFreqList[0].usFreqNum)
            {
                pstFreqInfoClt->stWFreqList.usFreqNum = pstWcdmaFreqList->astPlmnFreqList[0].usFreqNum;
            }
            else
            {
                pstFreqInfoClt->stWFreqList.usFreqNum = NAS_INFO_CLT_MAX_WCDMA_FREQ_NUM;
            }

            PS_MEM_CPY(&pstFreqInfoClt->stWFreqList.astFreqInfo[0],
                       &pstWcdmaFreqList->astPlmnFreqList[0].astFreqList[0],
                       sizeof(NAS_INFO_CLT_GU_FREQ_INFO_STRU) * pstFreqInfoClt->stWFreqList.usFreqNum);
        }
    }

    /*  更新信息采集标识 */
    TAF_MTA_ClrWaitFreqCltCnfFlag(TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_WAS);

    /* 判断信息采集是否完成 */
    if (TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_NULL != TAF_MTA_GetWaitFreqCltCnfFlag())
    {
        return;
    }

    /* 发云通信频点信息给OM */
    TAF_MTA_SndAcpuOmFreqBandQryCnf(TAF_MTA_INFO_CLT_RESULT_SUCC);

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_FREQ_CLT_QRY_CNF);

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : TAF_MTA_RcvLrrcPlmnFreqQryCnf
 功能描述  : mta收到Lrrc ID_RRC_MTA_PLMN_FREQ_QRY_CNF消息处理函数
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月15日
    作    者   : y00270069
    修改内容   : 云通信频点采集项目新增函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvLrrcPlmnFreqQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_INFO_CLT_CTX_STRU                              *pstInfoCltCtx           = VOS_NULL_PTR;
    RRC_MTA_PLMN_FREQ_QRY_CNF_STRU                         *pstRrcMtaPlmnFreqQryCnf = VOS_NULL_PTR;
    NAS_INFO_CLT_CLOUD_FREQ_BAND_EVENT_STRU                *pstFreqInfoClt          = VOS_NULL_PTR;
    RRC_MTA_LTE_PLMN_FREQ_LIST_STRU                        *pstLteFreqList          = VOS_NULL_PTR;

    /* 局部变量初始化 */
    pstRrcMtaPlmnFreqQryCnf           = (RRC_MTA_PLMN_FREQ_QRY_CNF_STRU*)pMsg;

    /* 获取MTA上下文中保存云通信频点采集上下文 */
    pstInfoCltCtx  = TAF_MTA_GetInfoCltAddr();
    pstFreqInfoClt = pstInfoCltCtx->pstFreqInfoCltCtx;

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_FREQ_CLT_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcPlmnFreqQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 存贮LRRC云通信频点信息 */
    pstLteFreqList = &pstRrcMtaPlmnFreqQryCnf->u.stLteFreqList;

    if (0 < pstLteFreqList->ucPlmnNum)
    {
        /* 目前只支持单个PLMN频点采集 */
        pstFreqInfoClt->stLFreqList.stPlmnId.ulMcc = pstLteFreqList->astPlmnFreqList[0].stPlmnId.ulMcc;
        pstFreqInfoClt->stLFreqList.stPlmnId.ulMnc = pstLteFreqList->astPlmnFreqList[0].stPlmnId.ulMnc;

        if (0 < pstLteFreqList->astPlmnFreqList[0].usFreqNum)
        {
            if (NAS_INFO_CLT_MAX_LTE_FREQ_NUM >= pstLteFreqList->astPlmnFreqList[0].usFreqNum)
            {
                pstFreqInfoClt->stLFreqList.usFreqNum = pstLteFreqList->astPlmnFreqList[0].usFreqNum;
            }
            else
            {
                pstFreqInfoClt->stLFreqList.usFreqNum = NAS_INFO_CLT_MAX_LTE_FREQ_NUM;
            }

            PS_MEM_CPY(&pstFreqInfoClt->stLFreqList.astFreqInfo[0],
                       &pstLteFreqList->astPlmnFreqList[0].astFreqList[0],
                       sizeof(NAS_INFO_CLT_LTE_FREQ_INFO_STRU) * pstFreqInfoClt->stLFreqList.usFreqNum);
        }
    }

    /*  更新信息采集标识 */
    TAF_MTA_ClrWaitFreqCltCnfFlag(TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_LRRC);

    /* 判断信息采集是否完成 */
    if (TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_NULL != TAF_MTA_GetWaitFreqCltCnfFlag())
    {
        return;
    }

    /* 发云通信频点信息给OM */
    TAF_MTA_SndAcpuOmFreqBandQryCnf(TAF_MTA_INFO_CLT_RESULT_SUCC);

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_FREQ_CLT_QRY_CNF);

    return;
}
#endif

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiWaitFreqCltQryCnfExpired
 功能描述  : MTA收到定时器超时消息处理函数
 输入参数  : pstMsg  -- 消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月15日
    作    者   : y00270069
    修改内容   : 云通信频点采集项目新增函数
*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitFreqCltQryCnfExpired(
    VOS_VOID                           *pstMsg
)
{
    /* 发云通信频点信息给OM */
    TAF_MTA_SndAcpuOmFreqBandQryCnf(TAF_MTA_INFO_CLT_RESULT_SUCC);

    /* 清除所有的频点收集回复标识 */
    TAF_MTA_ClrAllWaitFreqCltCnfFlag();

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAcpuOmNetworkInfoQryReq
 功能描述  : 收到网络信息采集请求
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月19日
    作    者   : 张义芳 z00328328
    修改内容   : 上行发射功率采集项目新增函数
  2.日    期   : 2015年12月01日
    作    者   : 高亮亮 g00322017
    修改内容   : 网络信息采集项目
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAcpuOmNetworkInfoQryReq(
    VOS_VOID                           *pMsg
)
{
    TAF_SDC_SYS_MODE_ENUM_UINT8         enRatType;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranctrlMode;

    /* 获取当前接入技术 */
    enRatType                           = TAF_SDC_GetSysMode();
    enUtranctrlMode                     = NAS_UTRANCTRL_GetCurrUtranMode();

    /* 如果当期制式是GSM, WCDMA，则到GWPHY去获取物理层信息 */
    if ((TAF_SDC_SYS_MODE_GSM == enRatType)
     || ((TAF_SDC_SYS_MODE_WCDMA       == enRatType)
      && (NAS_UTRANCTRL_UTRAN_MODE_FDD == enUtranctrlMode)))
    {
        TAF_MTA_SndPhyChrInfoQryReq(DSP_PID_APM);
        TAF_MTA_SetWaitNetworkInfoCnfFlag(TAF_MTA_WAIT_NETWORK_INFO_CNF_FLAG_PHY);
    }
    /* 如果当期制式是TDS, LTE，则到TLPHY去获取物理层信息 */
    else if ((TAF_SDC_SYS_MODE_LTE == enRatType)
          || ((TAF_SDC_SYS_MODE_WCDMA == enRatType)
           && (NAS_UTRANCTRL_UTRAN_MODE_TDD == enUtranctrlMode)))
    {
        TAF_MTA_SndPhyChrInfoQryReq(TLPHY_PID_RTTAGENT);
        TAF_MTA_SetWaitNetworkInfoCnfFlag(TAF_MTA_WAIT_NETWORK_INFO_CNF_FLAG_PHY);
    }
    else
    {
        /* 其余不支持的制式则直接返回失败 */
        TAF_MTA_SndAcpuOmNetworkInfoQryCnf(TAF_MTA_INFO_CLT_RESULT_FAIL);
        return;
    }

    TAF_MTA_SndNasChrInfoQryReq(WUEPS_PID_MMC);
    TAF_MTA_SetWaitNetworkInfoCnfFlag(TAF_MTA_WAIT_NETWORK_INFO_CNF_FLAG_NAS);

    /* 启动保护定时器，等待物理层和NAS回复消息 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_NETWORK_INFO_QRY_CNF,
                                 TI_TAF_MTA_WAIT_NETWORK_INFO_QRY_CNF_TIMER_LEN);


    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndAcpuOmNetworkInfoQryCnf
 功能描述  : 给ACPU OM回复网络信息收集信息
 输入参数  : enCltResult 收集结果
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月19日
    作    者   : 张义芳 z00328328
    修改内容   : 上行物理层信息采集项目新增函数
  2.日    期   : 2015年12月01日
    作    者   : 高亮亮 g00322017
    修改内容   : 网络信息采集项目
**************************************
*****************************************************************************/
VOS_VOID TAF_MTA_SndAcpuOmNetworkInfoQryCnf(
    TAF_MTA_INFO_CLT_RESULT_ENUM_U32    enCltResult
)
{
    NAS_INFO_CLT_NETWORK_INFO_EVENT_STRU                    stNetworkInfo;
    VOS_UINT32                                              ulLength;
    TAF_NETWORK_INFO_CLT_CTX_STRU                          *pstNetworkInfoCtx = VOS_NULL_PTR;
    TAF_MTA_INFO_CLT_CTX_STRU                              *pstInfoCltCtx     = VOS_NULL_PTR;

    if (TAF_MTA_INFO_CLT_RESULT_FAIL == enCltResult)
    {
        TAF_MTA_SndAcpuOmInfoCltRptCnf(VOS_NULL_PTR, 0);
        return;
    }

    pstInfoCltCtx     = TAF_MTA_GetInfoCltAddr();
    pstNetworkInfoCtx = &(pstInfoCltCtx->stNetworkInfo);

    /* 局部变量初始化 */
    PS_MEM_SET(&stNetworkInfo, 0, sizeof(NAS_INFO_CLT_NETWORK_INFO_EVENT_STRU));

    stNetworkInfo.usCellid         = pstNetworkInfoCtx->usCellid;
    stNetworkInfo.usDlFreqInfo     = pstNetworkInfoCtx->usDlFreqInfo;
    stNetworkInfo.usUlFreqInfo     = pstNetworkInfoCtx->usUlFreqInfo;
    stNetworkInfo.usBandInfo       = pstNetworkInfoCtx->usBandInfo;
    stNetworkInfo.sRxPower         = pstNetworkInfoCtx->sRxPower;
    stNetworkInfo.sChanelQuality   = pstNetworkInfoCtx->sChanelQuality;
    stNetworkInfo.ucIsExsitRrcConn = pstNetworkInfoCtx->ucIsExsitRrcConn;
    stNetworkInfo.lTxPwr           = pstNetworkInfoCtx->lTxPwr;
    stNetworkInfo.ulSavedSlice     = pstNetworkInfoCtx->ulSavedSlice;
    stNetworkInfo.enNetMode        = TAF_MTA_GetNetMode();

    ulLength = sizeof(NAS_INFO_CLT_NETWORK_INFO_EVENT_STRU) - sizeof(OM_INFO_CLT_HEADER_STRU);

    NAS_COMM_BULID_INFOCLT_HEADER_INFO(&(stNetworkInfo.stHeader),
                                       VOS_GetModemIDFromPid(UEPS_PID_MTA),
                                       OM_INFO_CLT_SCENE_TYPE_NETWORK_INFO,
                                       ulLength);
    TAF_MTA_SndAcpuOmInfoCltRptCnf((VOS_VOID *)(&stNetworkInfo),
                                   sizeof(NAS_INFO_CLT_NETWORK_INFO_EVENT_STRU));

    TAF_MMA_ClearNetworkInfo();

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MTA_SndPhyChrInfoQryReq
 功能描述  : MTA向PHY发送信息采集请求
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月20日
    作    者   : 张义芳 z00328328
    修改内容   : 物理层信息采集项目新增函数
*****************************************************************************/
VOS_VOID TAF_MTA_SndPhyChrInfoQryReq(
    VOS_UINT32                          ulReceiverPid
)
{
    MTA_PHY_CHR_INFO_QRY_REQ_STRU      *pstMsg              = VOS_NULL_PTR;
    MTA_PHY_MSG_TYPE_ENUM_UINT16        enMsgId;

    /* 检查PID */
    if (TLPHY_PID_RTTAGENT == ulReceiverPid)
    {
        enMsgId = ID_MTA_TLPHY_GET_PHY_CHR_INFO_REQ;
    }
    else if (DSP_PID_APM == ulReceiverPid)
    {
        enMsgId = ID_MTA_APM_GET_PHY_CHR_INFO_REQ;
    }
    else
    {
        MTA_ERROR_LOG("TAF_MTA_SndPhyChrInfoQryReq: PID is not allowed!");
        return;
    }

    /* 申请消息结构内存 */
    pstMsg = (MTA_PHY_CHR_INFO_QRY_REQ_STRU *)TAF_MTA_ALLOC_MSG_WITH_HDR(sizeof(MTA_PHY_CHR_INFO_QRY_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        MTA_ERROR_LOG("TAF_MTA_SndPhyChrInfoQryReq: Alloc msg fail!");
        return;
    }

    /* 清空消息内容 */
    TAF_MTA_CLR_MSG_ENTITY(pstMsg);

    /* 填写消息头 */
    TAF_MTA_CFG_MSG_HDR(pstMsg, ulReceiverPid, enMsgId);

    /* 发送消息 */
    TAF_MTA_SEND_MSG(pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndNasChrInfoQryReq
 功能描述  : MTA向MMC发送NAS CHR信息采集请求
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月1日
    作    者   : 高亮亮 g00322017
    修改内容   : 网络信息采集项目新增函数
*****************************************************************************/
VOS_VOID TAF_MTA_SndNasChrInfoQryReq(
    VOS_UINT32                          ulReceiverPid
)
{
    MTA_NAS_CHR_INFO_QRY_REQ_STRU      *pstMsg = VOS_NULL_PTR;

    /* 申请消息结构内存 */
    pstMsg = (MTA_NAS_CHR_INFO_QRY_REQ_STRU *)TAF_MTA_ALLOC_MSG_WITH_HDR(sizeof(MTA_NAS_CHR_INFO_QRY_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        MTA_ERROR_LOG("TAF_MTA_SndNasChrInfoQryReq: Alloc msg fail!");
        return;
    }

    /* 清空消息内容 */
    TAF_MTA_CLR_MSG_ENTITY(pstMsg);

    /* 填写消息头 */
    TAF_MTA_CFG_MSG_HDR(pstMsg, ulReceiverPid, ID_MTA_MMC_GET_NAS_CHR_INFO_REQ);

    /* 发送消息 */
    TAF_MTA_SEND_MSG(pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvPhyChrInfoQryCnf
 功能描述  : mta收到WPHY TAF_MTA_RcvPhyInfoChrQryCnf消息处理函数
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月20日
    作    者   : 张义芳 z00328328
    修改内容   : 上行发射功率采集项目新增函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvPhyChrInfoQryCnf(
    VOS_VOID                           *pMsg
)
{
    PHY_MTA_PHY_CHR_INFO_QRY_CNF_STRU  *pstMtaPhyChrInfoQryCnf   = VOS_NULL_PTR;
    TAF_NETWORK_INFO_CLT_CTX_STRU      *pstNetworkInfo        = VOS_NULL_PTR;
    TAF_MTA_INFO_CLT_CTX_STRU          *pstInfoCltCtx         = VOS_NULL_PTR;

    pstMtaPhyChrInfoQryCnf         = (PHY_MTA_PHY_CHR_INFO_QRY_CNF_STRU *)pMsg;
    pstInfoCltCtx                  = TAF_MTA_GetInfoCltAddr();
    pstNetworkInfo                 = &(pstInfoCltCtx->stNetworkInfo);

    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_NETWORK_INFO_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvPhyChrInfoQryCnf: WARNING: Timer was already stop!");
        return;
    }

    pstNetworkInfo->usCellid       = pstMtaPhyChrInfoQryCnf->usCellid;
    pstNetworkInfo->usDlFreqInfo   = pstMtaPhyChrInfoQryCnf->usDlFreqInfo;
    pstNetworkInfo->usUlFreqInfo   = pstMtaPhyChrInfoQryCnf->usUlFreqInfo;
    pstNetworkInfo->usBandInfo     = pstMtaPhyChrInfoQryCnf->usBandInfo;
    pstNetworkInfo->sRxPower       = pstMtaPhyChrInfoQryCnf->sRxPower;
    pstNetworkInfo->sChanelQuality = pstMtaPhyChrInfoQryCnf->sChanelQuality;
    pstNetworkInfo->lTxPwr         = pstMtaPhyChrInfoQryCnf->lTxPwr;
    pstNetworkInfo->ulSavedSlice   = pstMtaPhyChrInfoQryCnf->ulSavedSlice;

    TAF_MTA_ClrWaitNetworkInfoCnfFlag(TAF_MTA_WAIT_NETWORK_INFO_CNF_FLAG_PHY);

    if (TAF_MTA_WAIT_NETWORK_INFO_CNF_FLAG_NULL != TAF_MTA_GetWaitNetworkInfoCnfFlag())
    {
        return;
    }

    TAF_MTA_SndAcpuOmNetworkInfoQryCnf(TAF_MTA_INFO_CLT_RESULT_SUCC);
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_NETWORK_INFO_QRY_CNF);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvNasGetNasChrInfoCnf
 功能描述  : mta收到MMC ID_MMC_MTA_GET_NAS_CHR_INFO_CNF消息处理函数
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月1日
    作    者   : 高亮亮 g00322017
    修改内容   : 网络信息采集项目新增函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvNasGetNasChrInfoCnf(
    VOS_VOID                           *pMsg
)
{
    MMC_MTA_NAS_CHR_INFO_CNF_STRU      *pstMtaNasInfoCnf   = VOS_NULL_PTR;
    TAF_MTA_INFO_CLT_CTX_STRU          *pstInfoCltCtx      = VOS_NULL_PTR;
    TAF_NETWORK_INFO_CLT_CTX_STRU      *pstNetworkInfo     = VOS_NULL_PTR;

    pstInfoCltCtx    = TAF_MTA_GetInfoCltAddr();
    pstNetworkInfo   = &(pstInfoCltCtx->stNetworkInfo);
    pstMtaNasInfoCnf = (MMC_MTA_NAS_CHR_INFO_CNF_STRU *)pMsg;

    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_NETWORK_INFO_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvNasGetNasChrInfoCnf: WARNING: Timer was already stop!");
        return;
    }

    pstNetworkInfo->ucIsExsitRrcConn      = pstMtaNasInfoCnf->ucIsExsitRrcConn;

    TAF_MTA_ClrWaitNetworkInfoCnfFlag(TAF_MTA_WAIT_NETWORK_INFO_CNF_FLAG_NAS);

    if (TAF_MTA_WAIT_NETWORK_INFO_CNF_FLAG_NULL != TAF_MTA_GetWaitNetworkInfoCnfFlag())
    {
        return;
    }

    TAF_MTA_SndAcpuOmNetworkInfoQryCnf(TAF_MTA_INFO_CLT_RESULT_SUCC);
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_NETWORK_INFO_QRY_CNF);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiWaitPhyInfoQryCnfExpired
 功能描述  : MTA收到定时器超时消息处理函数
 输入参数  : pstMsg  -- 消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : 张义芳 z00328328
    修改内容   : 上行发射功率采集项目新增函数
*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitNetworkInfoQryCnfExpired(
    VOS_VOID                           *pstMsg
)
{
    /* 超时, 发送空消息给OM避免上层错误 */
    TAF_MTA_SndAcpuOmNetworkInfoQryCnf(TAF_MTA_INFO_CLT_RESULT_FAIL);

    /* 清除所有的网络信息收集回复标识 */
    TAF_MTA_ClrAllWaitNetworkInfoCnfFlag();

    return;
}

#endif

#if ( (FEATURE_ON == FEATURE_LTE) || (FEATURE_ON == FEATURE_UE_MODE_TDS) )
/*****************************************************************************
 函 数 名  : TAF_MTA_SndTLrrcSetDpdtTestFlagNtfMsg
 功能描述  : MTA发送Set Dpdt Flag请求消息到LRRC
 输入参数  : AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU  *pstSetDpdtFlagReq
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月4日
    作    者   : g00261581
    修改内容   : 新建

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndTLrrcSetDpdtTestFlagNtfMsg(
    AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU  *pstSetDpdtFlagReq
)
{
    MTA_TLRRC_SET_DPDTTEST_FLAG_NTF_STRU   *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                              ulLength;

    /* 申请消息结构内存 */
    ulLength    = sizeof(MTA_TLRRC_SET_DPDTTEST_FLAG_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg      = (MTA_TLRRC_SET_DPDTTEST_FLAG_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        MTA_ERROR_LOG("TAF_MTA_SndTLrrcSetDpdtTestFlagNtfMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0, ulLength);

    /* 填写新消息内容 */
    pstMsg->ulSenderCpuId           = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid             = UEPS_PID_MTA;
    pstMsg->ulReceiverCpuId         = VOS_LOCAL_CPUID;
    pstMsg->ulLength                = ulLength;
    pstMsg->ulMsgName               = ID_MTA_TLRRC_SET_DPDTTEST_FLAG_NTF;
    pstMsg->ucFlag                  = pstSetDpdtFlagReq->ucFlag;

    /* Modify by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
    if (AT_MTA_CMD_RATMODE_LTE == pstSetDpdtFlagReq->enRatMode)
    {
        pstMsg->ulReceiverPid           = PS_PID_ERRC;
    }
    else
    {
        pstMsg->ulReceiverPid           = TPS_PID_RRC;
    }
    /* Modify by j00174725 for K3V3 多模多天线特性, 2014-06-16, End */

    /* 发送消息到TLRRC */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMsg))
    {
        MTA_ERROR_LOG("TAF_MTA_SndTLrrcSetDpdtTestFlagNtfMsg: PS_SEND_MSG fail.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndTLrrcSetDpdtValueNtfMsg
 功能描述  : MTA发送Set Dpdt Value请求消息到LRRC
 输入参数  : AT_MTA_SET_DPDT_VALUE_REQ_STRU  *pstSetDpdtReq
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
VOS_UINT32 TAF_MTA_SndTLrrcSetDpdtValueNtfMsg(
    AT_MTA_SET_DPDT_VALUE_REQ_STRU  *pstSetDpdtReq
)
{
    MTA_TLRRC_SET_DPDT_VALUE_NTF_STRU  *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    /* 申请消息结构内存 */
    ulLength    = sizeof(MTA_TLRRC_SET_DPDT_VALUE_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg      = (MTA_TLRRC_SET_DPDT_VALUE_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        MTA_ERROR_LOG("TAF_MTA_SndTLrrcSetDpdtValueNtfMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0, ulLength);

    /* 填写新消息内容 */
    pstMsg->ulSenderCpuId           = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid             = UEPS_PID_MTA;
    pstMsg->ulReceiverCpuId         = VOS_LOCAL_CPUID;
    pstMsg->ulLength                = ulLength;
    pstMsg->ulMsgName               = ID_MTA_TLRRC_SET_DPDT_VALUE_NTF;
    pstMsg->ulDpdtValue             = pstSetDpdtReq->ulDpdtValue;

    /* Modify by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
    if (AT_MTA_CMD_RATMODE_LTE == pstSetDpdtReq->enRatMode)
    {
        pstMsg->ulReceiverPid           = PS_PID_ERRC;
    }
    else
    {
        pstMsg->ulReceiverPid           = TPS_PID_RRC;
    }
    /* Modify by j00174725 for K3V3 多模多天线特性, 2014-06-16, End */

    /* 发送消息到LRRC */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMsg))
    {
        MTA_ERROR_LOG("TAF_MTA_SndTLrrcSetDpdtValueNtfMsg: PS_SEND_MSG fail.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndTLrrcQryDpdtValueReqMsg
 功能描述  : MTA发送Qry Dpdt Value请求消息到LRRC
 输入参数  : AT_MTA_QRY_DPDT_VALUE_REQ_STRU  *pstSetDpdtReq
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
VOS_UINT32 TAF_MTA_SndTLrrcQryDpdtValueReqMsg(
    AT_MTA_QRY_DPDT_VALUE_REQ_STRU     *pstSetDpdtReq
)
{
    MTA_TLRRC_QRY_DPDT_VALUE_REQ_STRU   *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    /* 申请消息结构内存 */
    ulLength    = sizeof(MTA_TLRRC_QRY_DPDT_VALUE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg      = (MTA_TLRRC_QRY_DPDT_VALUE_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        MTA_ERROR_LOG("TAF_MTA_SndTLrrcQryDpdtValueReqMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0, ulLength);

    /* 填写新消息内容 */
    pstMsg->ulSenderCpuId           = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid             = UEPS_PID_MTA;
    pstMsg->ulReceiverCpuId         = VOS_LOCAL_CPUID;
    pstMsg->ulLength                = ulLength;
    pstMsg->ulMsgName               = ID_MTA_TLRRC_QRY_DPDT_VALUE_REQ;

    /* Modify by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
    if (AT_MTA_CMD_RATMODE_LTE == pstSetDpdtReq->enRatMode)
    {
        pstMsg->ulReceiverPid           = PS_PID_ERRC;
    }
    else
    {
        pstMsg->ulReceiverPid           = TPS_PID_RRC;
    }
    /* Modify by j00174725 for K3V3 多模多天线特性, 2014-06-16, End */

    /* 发送消息到LRRC */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMsg))
    {
        MTA_ERROR_LOG("TAF_MTA_SndTLrrcQryDpdtValueReqMsg: PS_SEND_MSG fail.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTLrrcDpdtValueQryCnf
 功能描述  : MTA收到LTE接入层DPDT Value查询回复消息处理函数
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
VOS_VOID TAF_MTA_RcvTLrrcDpdtValueQryCnf(VOS_VOID *pMsg)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf        = VOS_NULL_PTR;
    TLRRC_MTA_QRY_DPDT_VALUE_CNF_STRU  *pstLrrcMtaQryCnf = VOS_NULL_PTR;
    MTA_AT_QRY_DPDT_VALUE_CNF_STRU      stMtaAtQryCnf;
    TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId;

    /* 局部变量初始化 */
    pstLrrcMtaQryCnf = (TLRRC_MTA_QRY_DPDT_VALUE_CNF_STRU *)pMsg;
    enTimerId = TI_TAF_MTA_WAIT_DPDT_VALUE_QRY_CNF;

    if (TAF_MTA_TIMER_STATUS_RUNING != TAF_MTA_GetTimerStatus(enTimerId))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvTLrrcDpdtValueQryCnf: WARNING: Timer was already stop!");
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
    if (MTA_RRC_RESULT_NO_ERROR == pstLrrcMtaQryCnf->enResult)
    {
        stMtaAtQryCnf.enResult = MTA_AT_RESULT_NO_ERROR;
        stMtaAtQryCnf.ulDpdtValue = pstLrrcMtaQryCnf->ulDpdtValue;
    }
    else
    {
        stMtaAtQryCnf.enResult = MTA_AT_RESULT_ERROR;
        stMtaAtQryCnf.ulDpdtValue = 0;
    }

    /* 发送消息给AT模块 */
    TAF_MTA_SndAtMsg( (AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                      ID_MTA_AT_QRY_DPDT_VALUE_CNF,
                      sizeof(MTA_AT_QRY_DPDT_VALUE_CNF_STRU),
                      (VOS_UINT8 *)&stMtaAtQryCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndLrrcSetFrReqMsg
 功能描述  : 向LRRC发送ID_MTA_LRRC_SET_FR_REQ
 输入参数  : pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月03日
    作    者   : wx270776
    修改内容   : 新建函数

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndLrrcSetFrReqMsg(
    struct MsgCB                       *pstMsg
)
{
    MN_APP_REQ_MSG_STRU                *pstAtMtaSetFrReq = VOS_NULL_PTR;
    MTA_LRRC_SET_FR_REQ_STRU           *pstMtaLrrcSetFrReq = VOS_NULL_PTR;
    AT_MTA_SET_FR_REQ_STRU              stAtMtaSetFrReq;
    VOS_UINT32                          ulLength;

    PS_MEM_SET(&stAtMtaSetFrReq, 0, sizeof(AT_MTA_SET_FR_REQ_STRU));

    pstAtMtaSetFrReq   = (MN_APP_REQ_MSG_STRU*)pstMsg;
    PS_MEM_CPY(&stAtMtaSetFrReq, pstAtMtaSetFrReq->aucContent, sizeof(AT_MTA_SET_FR_REQ_STRU));

    /* 申请消息结构内存 */
    ulLength           = sizeof(MTA_LRRC_SET_FR_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaLrrcSetFrReq = (MTA_LRRC_SET_FR_REQ_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaLrrcSetFrReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcSetFrReqMsg: Alloc msg fail!");

        return VOS_ERR;
    }

    /* 填充消息体 */
    pstMtaLrrcSetFrReq->stMsgHeader.ulSenderPid     = UEPS_PID_MTA;
    pstMtaLrrcSetFrReq->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMtaLrrcSetFrReq->stMsgHeader.ulReceiverPid   = PS_PID_ERRC;
    pstMtaLrrcSetFrReq->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMtaLrrcSetFrReq->stMsgHeader.ulLength        = ulLength;
    pstMtaLrrcSetFrReq->stMsgHeader.ulMsgName       = ID_MTA_LRRC_SET_FR_REQ;
    pstMtaLrrcSetFrReq->enActFrFlag                 = stAtMtaSetFrReq.enActFrFlag;
    pstMtaLrrcSetFrReq->aucRsv[0]                   = 0;
    pstMtaLrrcSetFrReq->aucRsv[1]                   = 0;
    pstMtaLrrcSetFrReq->aucRsv[2]                   = 0;

    /* 发送消息到LRRC */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaLrrcSetFrReq))
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcSetFrReqMsg: Send msg fail!");

        return VOS_ERR;
    }

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtSetFrReq
 功能描述  : MTA收到AT发来的ID_AT_MTA_SET_FR_REQ消息处理函数
 输入参数  : pstMsg  -- 消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月01日
    作    者   : wx270776
    修改内容   : 新建
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtSetFrReq(
    VOS_VOID                           *pstMsg
)
{
    AT_MTA_MSG_STRU                    *pstAtMtaMsg      = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    MTA_AT_SET_FR_CNF_STRU              stMtaAtSetFrCnf;

    /* 局部变量初始化 */
    pstAtMtaMsg                       = (AT_MTA_MSG_STRU*)pstMsg;
    ulResult                          = VOS_ERR;
    PS_MEM_SET(&stMtaAtSetFrCnf, 0, sizeof(MTA_AT_SET_FR_CNF_STRU));

    /* 如果当前定时器已启动，则直接返回失败 */
    if (TAF_MTA_TIMER_STATUS_STOP != TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_SET_FR_CNF))
    {
        stMtaAtSetFrCnf.enRslt        = MTA_AT_RESULT_ERROR;

        TAF_MTA_SndAtMsg(&pstAtMtaMsg->stAppCtrl,
                         ID_MTA_AT_SET_FR_CNF,
                         sizeof(MTA_AT_SET_FR_CNF_STRU),
                         (VOS_UINT8*)&stMtaAtSetFrCnf );
        return;
    }

    /* 收到at的Set Fr设置请求，发ID_MTA_LRRC_SET_FR_REQ消息通知LRRC */
    ulResult = TAF_MTA_SndLrrcSetFrReqMsg(pstMsg);

    /* 消息发送失败，给AT回复ERROR */
    if (VOS_OK != ulResult)
    {
        stMtaAtSetFrCnf.enRslt = MTA_AT_RESULT_ERROR;

        TAF_MTA_SndAtMsg(&pstAtMtaMsg->stAppCtrl,
                          ID_MTA_AT_SET_FR_CNF,
                          sizeof(MTA_AT_SET_FR_CNF_STRU),
                          (VOS_UINT8*)&stMtaAtSetFrCnf );
        return;
    }

    /* 启动保护定时器 */
    if (TAF_MTA_TIMER_START_FAILURE == TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_SET_FR_CNF, TI_TAF_MTA_WAIT_SET_FR_CNF_TIMER_LEN))
    {
        MTA_WARNING_LOG("TAF_MMA_RcvAtSetFrReq: WARNING: Start Timer failed!");
    }

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_SET_FR_CNF,
                                     (VOS_UINT8*)&pstAtMtaMsg->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_RcvLrrcSetFrCnf
 功能描述  : MTA收到LRRC发来的ID_MTA_AT_SET_FR_CNF消息处理函数
 输入参数  : pstMsg  -- 消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月01日
    作    者   : wx270776
    修改内容   : 新建
*****************************************************************************/
VOS_VOID TAF_MTA_RcvLrrcSetFrCnf(
    VOS_VOID                           *pstMsg
)
{
    LRRC_MTA_SET_FR_CNF_STRU           *pstLrrcMtaSetFrCnf = VOS_NULL_PTR;
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_SET_FR_CNF_STRU              stMtaAtSetFrCnf;

    /* 初始化局部变量 */
    pstLrrcMtaSetFrCnf                = (LRRC_MTA_SET_FR_CNF_STRU*)pstMsg;
    PS_MEM_SET(&stMtaAtSetFrCnf, 0, sizeof(MTA_AT_SET_FR_CNF_STRU));

    if (TAF_MTA_TIMER_STATUS_RUNING != TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_SET_FR_CNF))
    {
        MTA_WARNING_LOG("TAF_MMA_RcvLrrcSetFrCnf: WARNING: Timer was already stop!");

        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_SET_FR_CNF);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_SET_FR_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    /* 填充消息体 */
    if ( MTA_RRC_RESULT_NO_ERROR == pstLrrcMtaSetFrCnf->enRslt )
    {
        stMtaAtSetFrCnf.enRslt        = MTA_AT_RESULT_NO_ERROR;
    }
    else
    {
        stMtaAtSetFrCnf.enRslt        = MTA_AT_RESULT_ERROR;
    }

    /* 发送消息给AT模块 */
    TAF_MTA_SndAtMsg( (AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                      ID_MTA_AT_SET_FR_CNF,
                      sizeof(MTA_AT_SET_FR_CNF_STRU),
                      (VOS_UINT8 *)&stMtaAtSetFrCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiWaitLrrcSetFrCnfExpired
 功能描述  : MTA收到定时器超时消息处理函数
 输入参数  : pstMsg  -- 消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月01日
    作    者   : wx270776
    修改内容   : 新建
*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitLrrcSetFrCnfExpired(
    VOS_VOID                           *pstMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf       = VOS_NULL_PTR;
    AT_APPCTRL_STRU                    *pstAppCtrl      = VOS_NULL_PTR;
    MTA_AT_SET_FR_CNF_STRU              stMtaAtSetFrCnf;

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_SET_FR_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    pstAppCtrl = (AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo;

    stMtaAtSetFrCnf.enRslt = MTA_AT_RESULT_ERROR;

    /* 上报给AT模块查询错误 */
    TAF_MTA_SndAtMsg(pstAppCtrl,
                     ID_MTA_AT_SET_FR_CNF,
                     sizeof(stMtaAtSetFrCnf),
                     (VOS_UINT8*)&stMtaAtSetFrCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_SET_FR_CNF);

    return;

}

#endif

/*****************************************************************************
 函 数 名  : TAF_MTA_SndGasSetFreqLockReq
 功能描述  : MTA给GAS下发锁频率请求消息
 输入参数  : AT_MTA_SET_GSM_FREQLOCK_REQ_STRU     *pstSetGFreqLockReq
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年08月05日
    作    者   : j00174725
    修改内容   : 新增函数
*****************************************************************************/
VOS_UINT32 TAF_MTA_SndGasSetFreqLockReq(
    AT_MTA_SET_GSM_FREQLOCK_REQ_STRU   *pstSetGFreqLockReq
)
{
    MTA_GRR_FREQLOCK_SET_REQ_STRU      *pstSetGFreqReq = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    /* 申请消息结构内存 */
    ulLength              = sizeof(MTA_GRR_FREQLOCK_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSetGFreqReq        = (MTA_GRR_FREQLOCK_SET_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);
    if (VOS_NULL_PTR == pstSetGFreqReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndGasSetFreqLockReq: Alloc msg fail!");
        return VOS_ERR;
    }

    pstSetGFreqReq->stMsgHeader.ulReceiverPid   = UEPS_PID_GAS;
    pstSetGFreqReq->stMsgHeader.ulMsgName       = ID_MTA_GRR_FREQLOCK_SET_REQ;
    pstSetGFreqReq->enLockFlg                   = pstSetGFreqLockReq->enableFlag;
    pstSetGFreqReq->usFreq                      = pstSetGFreqLockReq->usFreq;
    pstSetGFreqReq->aucReserved[0]              = 0;
    pstSetGFreqReq->aucReserved[1]              = 0;
    pstSetGFreqReq->aucReserved[2]              = 0;
    pstSetGFreqReq->enBand                      = (MTA_RRC_GSM_BAND_ENUM_UINT16)pstSetGFreqLockReq->enBand;

    /* 发送消息到AS */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstSetGFreqReq))
    {
        MTA_ERROR_LOG("TAF_MTA_SndGasSetFreqLockReq: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtSetGFreqLockReq
 功能描述  : 处理AT下发的设置GFREQLOCK命令
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年08月05日
    作    者   : j00174725
    修改内容   : 新建
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtSetGFreqLockReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstSetReq           = VOS_NULL_PTR;
    AT_MTA_SET_GSM_FREQLOCK_REQ_STRU   *pstSetGFreqLockReq  = VOS_NULL_PTR;
    MTA_AT_SET_GSM_FREQLOCK_CNF_STRU    stSetGFreqLockCnf;
    VOS_UINT32                          ulResult;

    pstSetReq                   = (AT_MTA_MSG_STRU *)pMsg;
    pstSetGFreqLockReq          = (AT_MTA_SET_GSM_FREQLOCK_REQ_STRU *)(pstSetReq->aucContent);
    stSetGFreqLockCnf.enResult  = MTA_AT_RESULT_ERROR;

    /* 如果当前定时器已启动，则返回失败 */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_SET_GSM_FREQLOCK_CNF))
    {
        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_SET_GSM_FREQLOCK_CNF,
                         sizeof(stSetGFreqLockCnf),
                         (VOS_UINT8*)&stSetGFreqLockCnf);
        return;
    }

    ulResult = TAF_MTA_SndGasSetFreqLockReq(pstSetGFreqLockReq);

    if (VOS_OK != ulResult)
    {
        /* 消息发送失败，给at回复失败*/
        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_SET_GSM_FREQLOCK_CNF,
                         sizeof(stSetGFreqLockCnf),
                         (VOS_UINT8*)&stSetGFreqLockCnf);
        return;
    }

    /* 启动保护定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_SET_GSM_FREQLOCK_CNF,
                       TI_TAF_MTA_WAIT_SET_GSM_FREQLOCK_CNF_TIMER_LEN);

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_SET_GSM_FREQLOCK_CNF,
                                    (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvGasSetFreqLockCnf
 功能描述  : MTA收到Gas发送来的ID_GRR_MTA_FREQLOCK_SET_CNF消息处理函数
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年08月05日
    作    者   : j00174725
    修改内容   : 新增函数
*****************************************************************************/
VOS_VOID TAF_MTA_RcvGasSetFreqLockCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf       = VOS_NULL_PTR;
    AT_APPCTRL_STRU                    *pstAppCtrl      = VOS_NULL_PTR;
    GRR_MTA_FREQLOCK_SET_CNF_STRU      *pstSetCnf       = VOS_NULL_PTR;
    MTA_AT_SET_GSM_FREQLOCK_CNF_STRU    stMtaAtSetCnf;

    /* 初始化消息变量 */
    stMtaAtSetCnf.enResult = MTA_AT_RESULT_ERROR;

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_SET_GSM_FREQLOCK_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvGasSetFreqLockCnf:Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_SET_GSM_FREQLOCK_CNF);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_SET_GSM_FREQLOCK_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvGasSetFreqLockCnf: get command buffer failed!");
        return;
    }

    /* 取出之前保存的锁频消息 */
    pstAppCtrl = (AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo;

    /* 获取设置结果，上报AT结果 */
    pstSetCnf    = (GRR_MTA_FREQLOCK_SET_CNF_STRU *)pMsg;

    if (MTA_RRC_RESULT_NO_ERROR == pstSetCnf->enResult)
    {
        stMtaAtSetCnf.enResult = MTA_AT_RESULT_NO_ERROR;
    }

    /* 给at回消息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstAppCtrl,
                     ID_MTA_AT_SET_GSM_FREQLOCK_CNF,
                     sizeof(stMtaAtSetCnf),
                     (VOS_UINT8*)&stMtaAtSetCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_SET_GSM_FREQLOCK_CNF);
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiWaitGasSetGFreqLockExpired
 功能描述  : 设置GFREQLOCK超时的处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
  1.日    期   : 2014年08月05日
    作    者   : j00174725
    修改内容   : 新增函数
*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitGasSetGFreqLockExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf       = VOS_NULL_PTR;
    AT_APPCTRL_STRU                    *pstAppCtrl      = VOS_NULL_PTR;
    MTA_AT_SET_GSM_FREQLOCK_CNF_STRU    stSetCnf;

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_SET_GSM_FREQLOCK_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    pstAppCtrl = (AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo;

    stSetCnf.enResult = MTA_AT_RESULT_ERROR;

    /* 上报给AT模块查询错误 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstAppCtrl,
                     ID_MTA_AT_SET_GSM_FREQLOCK_CNF,
                     sizeof(stSetCnf),
                     (VOS_UINT8*)&stSetCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_SET_GSM_FREQLOCK_CNF);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MTA_RcvGphyXpassInfoInd
 功能描述  : 处理gphy上报的xpass信息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月25日
    作    者   : m00217266
    修改内容   : 新建
*****************************************************************************/
VOS_VOID TAF_MTA_RcvGphyXpassInfoInd(VOS_VOID *pMsg)
{
    GPHY_MTA_XPASS_INFO_IND_STRU       *pstGphyXpassInfo = VOS_NULL_PTR;
    MTA_AT_XPASS_INFO_IND_STRU          stXpassInfoInd;
    AT_APPCTRL_STRU                     stAppCtrl;
    VOS_UINT32                          ulChkCurcRptFlg;

    PS_MEM_SET(&stXpassInfoInd, 0x0, sizeof(stXpassInfoInd));

    /* 填写消息头，上报类型为广播事件 */
    PS_MEM_SET(&stAppCtrl, 0, sizeof(stAppCtrl));
    stAppCtrl.usClientId = MTA_CLIENTID_BROADCAST;
    stAppCtrl.ucOpId     = MTA_INVALID_TAB_INDEX;

    pstGphyXpassInfo = (GPHY_MTA_XPASS_INFO_IND_STRU *)pMsg;

    stXpassInfoInd.enWphyXpassMode = PHY_MTA_WPHY_HIGHWAY_MODE_DISABLE;
    stXpassInfoInd.enGphyXpassMode = pstGphyXpassInfo->enXpassMode;

    /* 判断当前主动上报是否关闭 */
    ulChkCurcRptFlg = TAF_MTA_GetXpassInfoRptCtl();
    if (VOS_FALSE == ulChkCurcRptFlg)
    {
        return;
    }

    TAF_MTA_SndAtMsg(&stAppCtrl,
                     ID_MTA_AT_XPASS_INFO_IND,
                     sizeof(stXpassInfoInd),
                     (VOS_UINT8*)&stXpassInfoInd );

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvWphyXpassInfoInd
 功能描述  : 处理gphy上报的xpass信息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月25日
    作    者   : m00217266
    修改内容   : 新建
*****************************************************************************/
VOS_VOID TAF_MTA_RcvWphyXpassInfoInd(VOS_VOID *pMsg)
{
    WPHY_MTA_XPASS_INFO_IND_STRU       *pstWphyXpassInfo = VOS_NULL_PTR;
    MTA_AT_XPASS_INFO_IND_STRU          stXpassInfoInd;
    AT_APPCTRL_STRU                     stAppCtrl;
    VOS_UINT32                          ulChkCurcRptFlg;

    PS_MEM_SET(&stXpassInfoInd, 0x0, sizeof(stXpassInfoInd));

    /* 填写消息头，上报类型为广播事件 */
    PS_MEM_SET(&stAppCtrl, 0, sizeof(stAppCtrl));
    stAppCtrl.usClientId = MTA_CLIENTID_BROADCAST;
    stAppCtrl.ucOpId     = MTA_INVALID_TAB_INDEX;

    pstWphyXpassInfo = (WPHY_MTA_XPASS_INFO_IND_STRU *)pMsg;

    stXpassInfoInd.enGphyXpassMode = PHY_MTA_GPHY_XPASS_MODE_DISABLE;
    stXpassInfoInd.enWphyXpassMode = pstWphyXpassInfo->enHighwayMode;

    /* 判断当前主动上报是否关闭 */
    ulChkCurcRptFlg = TAF_MTA_GetXpassInfoRptCtl();
    if (VOS_FALSE == ulChkCurcRptFlg)
    {
        return;
    }

    TAF_MTA_SndAtMsg(&stAppCtrl,
                     ID_MTA_AT_XPASS_INFO_IND,
                     sizeof(stXpassInfoInd),
                     (VOS_UINT8*)&stXpassInfoInd );

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_GetXpassInfoRptCtl
 功能描述  : 获取XpassReselect主动上报控制
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月25日
    作    者   : m00217266
    修改内容   : Xpass reselect新增
*****************************************************************************/
VOS_UINT32 TAF_MTA_GetXpassInfoRptCtl(VOS_VOID)
{
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl      = VOS_NULL_PTR;
    VOS_UINT32                          ulChkCurcRptFlg;

    /* 判断当前主动上报是否关闭 */
    pstCurcRptCtrl  = TAF_SDC_GetCurcRptCtrl();
    ulChkCurcRptFlg = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                                TAF_SDC_RPT_CMD_XPASSINFO);

    return ulChkCurcRptFlg;
}
/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtSetFemctrlReq
 功能描述  : 处理AT下发的设置FEMCTRL命令
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月11日
    作    者   : m00217266
    修改内容   : 新建
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtSetFemctrlReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstSetReq       = VOS_NULL_PTR;
    MTA_AT_SET_FEMCTRL_CNF_STRU         stSetCnf;
    AT_MTA_SET_FEMCTRL_REQ_STRU        *pstFemctrl;
    VOS_INT32                          lResult;

    pstSetReq          = (AT_MTA_MSG_STRU *)pMsg;
    lResult           = MTA_AT_RESULT_ERROR;
    pstFemctrl         = (AT_MTA_SET_FEMCTRL_REQ_STRU *)pstSetReq->aucContent;
    PS_MEM_SET(&stSetCnf, 0x0, sizeof(stSetCnf));

    /* 调用底软的设置gpio和mipi函数 */
    lResult = mdrv_fem_ioctrl((FEMIO_CTRL_TYPE)pstFemctrl->ulCtrlType, pstFemctrl->ulPara1, pstFemctrl->ulPara2, pstFemctrl->ulPara3);

    if (lResult == VOS_OK)
    {
        stSetCnf.enResult = MTA_AT_RESULT_NO_ERROR;
    }

    TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                     ID_AT_MTA_SET_FEMCTRL_CNF,
                     sizeof(stSetCnf),
                     (VOS_UINT8*)&stSetCnf );

    return;
}
/*lint +e958*/

#if(FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : TAF_MTA_SndLrrcSetLteLowPowerConsumptionReqMsg
 功能描述  : 给lrrc发送设置低功耗消息
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
VOS_VOID TAF_MTA_SndLrrcSetLowPowerConsumptionReqMsg(
    VOS_UINT8                           ucLowPowerConsumption
)
{
    MTA_LRRC_LOW_POWER_CONSUMPTION_SET_REQ_STRU    *pstMtaLrrcSetReq = VOS_NULL_PTR;
    VOS_UINT32                                      ulLength;

    /* 申请消息结构内存 */
    ulLength              = sizeof(MTA_LRRC_LOW_POWER_CONSUMPTION_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaLrrcSetReq      = (MTA_LRRC_LOW_POWER_CONSUMPTION_SET_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaLrrcSetReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcSetLowPowerConsumptionReqMsg: Alloc msg fail!");
        return;
    }

    /* 构造消息结构体 */
    MTA_FILL_MSG_HEADER(&pstMtaLrrcSetReq->stMsgHeader, PS_PID_ERRC);
    pstMtaLrrcSetReq->stMsgHeader.ulMsgName         = ID_MTA_LRRC_LOW_POWER_CONSUMPTION_SET_REQ;
    pstMtaLrrcSetReq->bLowPowerFlg                  = (VOS_BOOL)ucLowPowerConsumption;

    /* 发送消息到LRRC */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaLrrcSetReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcSetsLowPowerConsumptionReqMsg: Send msg fail!");
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtLteLowPowerConsumptionSetReq
 功能描述  : MTA处理^LTELOWPOWER命令，设置低功耗请求
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
VOS_VOID TAF_MTA_RcvAtLteLowPowerConsumptionSetReq(
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
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_LOW_POWER_CONSUMPTION_SET_CNF))
    {
        ulResult  = VOS_ERR;
    }

    if (ulResult != VOS_OK)
    {
        /* 消息发送失败，给at回复失败*/
        PS_MEM_SET(&stSetCnf, 0x0, sizeof(stSetCnf));
        stSetCnf.enResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_LTE_LOW_POWER_SET_CNF,
                         sizeof(stSetCnf),
                         (VOS_UINT8*)&stSetCnf );
        return;
    }

    /* 收到at命令请求，发请求消息通知as */
    TAF_MTA_SndLrrcSetLowPowerConsumptionReqMsg(pstSetReq->aucContent[0]);

    /* 启动保护定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_LRRC_LOW_POWER_CONSUMPTION_SET_CNF,
                       TI_TAF_MTA_WAIT_SET_LOW_POWER_CONSUMPTION_CNF_TIMER_LEN);

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_LOW_POWER_CONSUMPTION_SET_CNF,
                                     (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvLrrcLowPowerConsumptionSetCnf
 功能描述  : MTA收到LRRC设置低功耗结果
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
VOS_VOID TAF_MTA_RcvLrrcLowPowerConsumptionSetCnf(
    VOS_VOID                           *pLrrcCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                        *pstCmdBuf               = VOS_NULL_PTR;
    LRRC_MTA_LOW_POWER_CONSUMPTION_SET_CNF_STRU    *pstRcvLrrcCnf           = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                          stSndAtCnf;

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_LOW_POWER_CONSUMPTION_SET_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcLowPowerConsumptionSetCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_LRRC_LOW_POWER_CONSUMPTION_SET_CNF);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_LOW_POWER_CONSUMPTION_SET_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcLowPowerConsumptionSetCnf: get command buffer failed!");
        return;
    }

    pstRcvLrrcCnf           = (LRRC_MTA_LOW_POWER_CONSUMPTION_SET_CNF_STRU *)pLrrcCnfMsg;
    stSndAtCnf.enResult     = pstRcvLrrcCnf->enResult;

    /* 给at回消息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_LTE_LOW_POWER_SET_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf );

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_LOW_POWER_CONSUMPTION_SET_CNF);
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiWaitLrrcSetLowPowerConsumption
 功能描述  : 设置低功耗超时的处理函数
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
VOS_VOID TAF_MTA_RcvTiWaitLrrcSetLowPowerConsumption(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf       = VOS_NULL_PTR;
    AT_APPCTRL_STRU                            *pstAppCtrl      = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                      stSndAtCnf;

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_LOW_POWER_CONSUMPTION_SET_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    pstAppCtrl          = (AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo;

    stSndAtCnf.enResult = MTA_AT_RESULT_OPTION_TIMEOUT;

    /* 上报给AT模块查询错误 */
    TAF_MTA_SndAtMsg(pstAppCtrl,
                     ID_MTA_AT_LTE_LOW_POWER_SET_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_LOW_POWER_CONSUMPTION_SET_CNF);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndLrrcSetIsmCoexReqMsg
 功能描述  : 给lrrc发送设置命令^SIMCOEX
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
VOS_VOID TAF_MTA_SndLrrcSetIsmCoexReqMsg(
    AT_MTA_LTE_WIFI_COEX_SET_REQ_STRU  *pstCoexPara
)
{
    MTA_LRRC_LTE_WIFI_COEX_SET_REQ_STRU            *pstMtaLrrcSetReq = VOS_NULL_PTR;
    VOS_UINT32                                      ulLength;
    VOS_UINT32                                      ulCoexParaPtr;

    /* 申请消息结构内存 */
    ulLength              = sizeof(pstCoexPara->astCoexPara) + sizeof(MTA_LRRC_LTE_WIFI_COEX_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH - 4;
    pstMtaLrrcSetReq      = (MTA_LRRC_LTE_WIFI_COEX_SET_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaLrrcSetReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcSetIsmCoexReqMsg: Alloc msg fail!");
        return;
    }

    /* 构造消息结构体 */
    MTA_FILL_MSG_HEADER(&pstMtaLrrcSetReq->stMsgHeader, PS_PID_ERRC);
    pstMtaLrrcSetReq->stMsgHeader.ulMsgName         = ID_MTA_LRRC_LTE_WIFI_COEX_SET_REQ;
    pstMtaLrrcSetReq->usCoexParaNum                 = pstCoexPara->usCoexParaNum;
    pstMtaLrrcSetReq->usCoexParaSize                = pstCoexPara->usCoexParaSize;
    ulCoexParaPtr                                   = (VOS_UINT32)pstMtaLrrcSetReq->aucCoexPara;
    PS_MEM_CPY((VOS_UINT8 *)ulCoexParaPtr, pstCoexPara->astCoexPara, sizeof(pstCoexPara->astCoexPara));

    /* 发送消息到LRRC */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaLrrcSetReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcSetIsmCoexReqMsg: Send msg fail!");
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvLrrcIsmCoexSetCnf
 功能描述  : MTA收到LRRC ^ISMCOEX设置结果
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
VOS_VOID TAF_MTA_RcvLrrcIsmCoexSetCnf(
    VOS_VOID                           *pLrrcCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                        *pstCmdBuf               = VOS_NULL_PTR;
    LRRC_MTA_LTE_WIFI_COEX_SET_CNF_STRU            *pstRcvLrrcCnf           = VOS_NULL_PTR;
    AT_MTA_MSG_STRU                                *pstMsg                  = VOS_NULL_PTR;
    AT_MTA_COEX_PARA_STRU                          *pstCoexPara             = VOS_NULL_PTR;
    AT_MTA_LTE_WIFI_COEX_SET_REQ_STRU              *pstBufferCoex           = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                          stSndAtCnf;
    VOS_UINT32                                      i;

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LTE_WIFI_COEX_SET_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcIsmCoexSetCnf: WARNING: Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_LTE_WIFI_COEX_SET_CNF);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LTE_WIFI_COEX_SET_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcIsmCoexSetCnf: get command buffer failed!");
        return;
    }

    pstRcvLrrcCnf           = (LRRC_MTA_LTE_WIFI_COEX_SET_CNF_STRU *)pLrrcCnfMsg;
    stSndAtCnf.enResult     = pstRcvLrrcCnf->enResult;

    pstMsg                  = (AT_MTA_MSG_STRU *)pstCmdBuf->pucMsgInfo;

    /* 更新IsmCoex列表 */
    if (VOS_OK == stSndAtCnf.enResult)
    {
        pstCoexPara     = TAF_MTA_GetIsmCoexAddr();
        pstBufferCoex   = (AT_MTA_LTE_WIFI_COEX_SET_REQ_STRU *)pstMsg->aucContent;
        for ( i = 0; i < TAF_MTA_ISMCOEX_BANDWIDTH_NUM; i++)
        {
            PS_MEM_CPY(pstCoexPara + i, &pstBufferCoex->astCoexPara[i], sizeof(TAF_MTA_COEX_PARA_STRU));
        }
    }

    /* 给at回消息 */
    TAF_MTA_SndAtMsg(&pstMsg->stAppCtrl,
                     ID_MTA_AT_LTE_WIFI_COEX_SET_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf );

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LTE_WIFI_COEX_SET_CNF);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtIsmCoexQryReq
 功能描述  : MTA处理^ISMCOEX?
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
VOS_VOID TAF_MTA_RcvAtIsmCoexQryReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstSetReq               = VOS_NULL_PTR;
    TAF_MTA_COEX_PARA_STRU             *pstCoexPara             = VOS_NULL_PTR;
    MTA_AT_LTE_WIFI_COEX_QRY_CNF_STRU   stCoexCnf;
    VOS_UINT32                          i;

    pstSetReq = (AT_MTA_MSG_STRU *)pMsg;
    pstCoexPara = TAF_MTA_GetIsmCoexAddr();
    PS_MEM_SET(&stCoexCnf, 0x00, sizeof(MTA_AT_LTE_WIFI_COEX_QRY_CNF_STRU));

    for (i = 0; i < TAF_MTA_ISMCOEX_BANDWIDTH_NUM; i++)
    {
        PS_MEM_CPY(&stCoexCnf.astCoexPara[i], pstCoexPara + i, sizeof(TAF_MTA_COEX_PARA_STRU));
    }

    /* 给at回消息 */
    TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                     ID_MTA_AT_LTE_WIFI_COEX_QRY_CNF,
                     sizeof(stCoexCnf),
                     (VOS_UINT8*)&stCoexCnf );

    return;
}
#endif

#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
/*****************************************************************************
 函 数 名  : TAF_MTA_SndCcbtLoadPsRrcCnf
 功能描述  : MTA给CCBT发送的ID_MTA_CCBT_LOAD_PS_RRC_CNF
 输入参数  : pstMsg
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月26日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MTA_SndCcbtLoadPsRrcCnf(
    CCBT_MTA_LOAD_PS_RRC_REQ_STRU      *pstLoadReq,
    VOS_UINT32                          ulIsLoad
)
{
    MTA_CCBT_LOAD_PS_RRC_CNF_STRU      *pstLoadCnf = VOS_NULL_PTR;

    pstLoadCnf = (MTA_CCBT_LOAD_PS_RRC_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA,
                                                              sizeof(MTA_CCBT_LOAD_PS_RRC_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstLoadCnf)
    {
        MTA_ERROR_LOG("TAF_MTA_SndCcbtLoadPsRrcCnf: Alloc msg fail!");
        return;
    }

    PS_MEM_SET(pstLoadCnf, 0x00, sizeof(MTA_CCBT_LOAD_PS_RRC_CNF_STRU));

    /* 构造消息结构体 */
    pstLoadCnf->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstLoadCnf->ulSenderPid       = UEPS_PID_MTA;
    pstLoadCnf->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstLoadCnf->ulReceiverPid     = CCPU_PID_CBT;
    pstLoadCnf->ulLength          = sizeof(MTA_CCBT_LOAD_PS_RRC_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstLoadCnf->enMsgId           = ID_MTA_CCBT_LOAD_PS_RRC_CNF;

    pstLoadCnf->usOpId            = pstLoadReq->usOpId;
    pstLoadCnf->usTransPrimId     = 0x6001;
    pstLoadCnf->enRatType         = pstLoadReq->enRatType;
    pstLoadCnf->ulIsLoaded        = ulIsLoad;

    PS_SEND_MSG(UEPS_PID_MTA, pstLoadCnf);

    NAS_TRACE_HIGH("TAF_MTA_SndCcbtLoadPsRrcCnf!\r\n");

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvCcbtLoadPsRrcReq
 功能描述  : MTA处理CCBT发送的ID_CCBT_MTA_LOAD_PS_RRC_REQ
 输入参数  : pstMsg
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月26日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvCcbtLoadPsRrcReq(
    VOS_VOID                           *pstMsg
)
{
    CCBT_MTA_LOAD_PS_RRC_REQ_STRU      *pstLoadReq = VOS_NULL_PTR;

    pstLoadReq = (CCBT_MTA_LOAD_PS_RRC_REQ_STRU *)pstMsg;

    NAS_TRACE_HIGH("TAF_MTA_RcvCcbtLoadPsRrcReq!, enLoadRatMod=%d\r\n", pstLoadReq->enRatType);

    (VOS_VOID)NAS_DYNLOAD_LoadAS(NAS_DYNLOAD_LOAD_RATCOMB_TYPE_T_W, pstLoadReq->enRatType);

    TAF_MTA_SndCcbtLoadPsRrcCnf(pstLoadReq, VOS_OK);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndCcbtLoadPsRrcCnf
 功能描述  : MTA给CCBT发送的ID_MTA_CCBT_LOAD_PS_RRC_CNF
 输入参数  : pstMsg
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月26日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MTA_SndCcbtQryPsRrcLoadStatusCnf(
    CCBT_MTA_QRY_PS_RRC_LOAD_STATUS_REQ_STRU                   *pstQryReq,
    VOS_UINT32                                                  ulIsLoad
)
{
    MTA_CCBT_QRY_PS_RRC_LOAD_STATUS_CNF_STRU               *pstQryCnf = VOS_NULL_PTR;

    pstQryCnf = (MTA_CCBT_QRY_PS_RRC_LOAD_STATUS_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA,
                                                              sizeof(MTA_CCBT_QRY_PS_RRC_LOAD_STATUS_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstQryCnf)
    {
        MTA_ERROR_LOG("TAF_MTA_SndCcbtLoadPsRrcCnf: Alloc msg fail!");
        return;
    }

    PS_MEM_SET(pstQryCnf, 0x00, sizeof(MTA_CCBT_LOAD_PS_RRC_CNF_STRU));

    /* 构造消息结构体 */
    pstQryCnf->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstQryCnf->ulSenderPid       = UEPS_PID_MTA;
    pstQryCnf->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstQryCnf->ulReceiverPid     = CCPU_PID_CBT;
    pstQryCnf->ulLength          = sizeof(MTA_CCBT_LOAD_PS_RRC_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstQryCnf->enMsgId           = ID_MTA_CCBT_QRY_PS_RRC_LOAD_STATUS_CNF;

    pstQryCnf->usOpId            = pstQryReq->usOpId;
    pstQryCnf->usTransPrimId     = 0x6001;
    pstQryCnf->enRatType         = pstQryReq->enRatType;
    pstQryCnf->ulIsLoaded        = ulIsLoad;

    PS_SEND_MSG(UEPS_PID_MTA, pstQryCnf);

    NAS_TRACE_HIGH("TAF_MTA_RcvCcbtQryPsRrcLoadStatusReq!\r\n");

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvCcbtQryPsRrcLoadStatusReq
 功能描述  : MTA处理CCBT发送的ID_CCBT_MTA_QRY_PS_RRC_LOAD_STATUS_REQ
 输入参数  : pstMsg
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月26日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvCcbtQryPsRrcLoadStatusReq(
    VOS_VOID                           *pstMsg
)
{
    CCBT_MTA_QRY_PS_RRC_LOAD_STATUS_REQ_STRU               *pstQryReq = VOS_NULL_PTR;
    VOS_UINT32                                              ulIsLoad;

    NAS_TRACE_HIGH("TAF_MTA_RcvCcbtQryPsRrcLoadStatusReq!\r\n");

    pstQryReq = (CCBT_MTA_QRY_PS_RRC_LOAD_STATUS_REQ_STRU *)pstMsg;

    ulIsLoad = VOS_ERR;

    if (VOS_RATMODE_TDS == NAS_DYNLOAD_GetCurRatInCached(NAS_DYNLOAD_LOAD_RATCOMB_TYPE_T_W))
    {
        ulIsLoad = VOS_OK;
    }

    TAF_MTA_SndCcbtQryPsRrcLoadStatusCnf(pstQryReq, ulIsLoad);

    return;
}

#endif

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtUECenterSetReq
 功能描述  : MTA收到ID_AT_MTA_UECENTER_SET_REQ消息处理函数
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 日    期   : 2015年7月30日
 作    者   : lwx277467
 修改内容   : +CEUS新增函数
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtUECenterSetReq(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                    *pstUECenterSetReq      = VOS_NULL_PTR;
    AT_MTA_SET_UE_CENTER_REQ_STRU      *pstAtMtaUECenterSetReq = VOS_NULL_PTR;
    MTA_AT_SET_UE_CENTER_CNF_STRU       stMtaAtUECenterSetCnf;

    PS_MEM_SET(&stMtaAtUECenterSetCnf, 0x0, sizeof(stMtaAtUECenterSetCnf));

    pstUECenterSetReq      = (AT_MTA_MSG_STRU *)pMsg;
    pstAtMtaUECenterSetReq = (AT_MTA_SET_UE_CENTER_REQ_STRU *)(pstUECenterSetReq->aucContent);

    /* 如果当前定时器已启动，则返回失败 */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_UE_CENTER_SET_CNF))
    {
        stMtaAtUECenterSetCnf.enResult = MTA_AT_RESULT_ERROR;

        TAF_MTA_SndAtMsg(&pstUECenterSetReq->stAppCtrl,
                        ID_MTA_AT_UE_CENTER_SET_CNF,
                        sizeof(MTA_AT_SET_UE_CENTER_CNF_STRU),
                        (VOS_UINT8*)&stMtaAtUECenterSetCnf);
        return;
    }

    TAF_MTA_SndLnasUECenterSetReq(pstAtMtaUECenterSetReq);

    /* 启动保护定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_UE_CENTER_SET_CNF, TI_TAF_MTA_WAIT_UE_CENTER_SET_CNF_TIMER_LEN);

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_UE_CENTER_SET_CNF,
                                     (VOS_UINT8*)&pstUECenterSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndLnasUECenterSetReq
 功能描述  : MTA发消息给LNAS设置UE模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月30日
    作    者   : lwx277467
    修改内容   : 新增+CEUS命令
*****************************************************************************/
VOS_VOID TAF_MTA_SndLnasUECenterSetReq(AT_MTA_SET_UE_CENTER_REQ_STRU *pstAtMtaUECenterSetReq)
{
    MTA_LNAS_SET_UE_CENTER_REQ_STRU     *pstUECenterSetReq = VOS_NULL_PTR;

    /* 申请消息结构内存 */
    pstUECenterSetReq = (MTA_LNAS_SET_UE_CENTER_REQ_STRU *)TAF_MTA_ALLOC_MSG_WITH_HDR(sizeof(MTA_LNAS_SET_UE_CENTER_REQ_STRU));
    if (VOS_NULL_PTR == pstUECenterSetReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLnasUECenterSetReq: Alloc msg fail!");
        return;
    }

    TAF_MTA_CLR_MSG_ENTITY(pstUECenterSetReq);

    /* 构造消息结构体 */
    pstUECenterSetReq->enUeCenter = pstAtMtaUECenterSetReq->enUeCenter;
    TAF_MTA_CFG_MSG_HDR(pstUECenterSetReq,PS_PID_MM,ID_MTA_LNAS_SET_UE_CENTER_REQ);

    /* 发送消息到LTE */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstUECenterSetReq))
    {
        MTA_ERROR_LOG("TAF_MTA_SndLnasUECenterSetReq(): Send MSG Fail!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvLnasUECenterSetCnf
 功能描述  : MTA收到LNAS设置UE模式消息回复处理函数
 输入参数  : pMsg  -- 消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月30日
    作    者   : lwx277467
    修改内容   : 新增+CEUS命令
*****************************************************************************/
VOS_VOID TAF_MTA_RcvLnasUECenterSetCnf(VOS_VOID *pMsg)
{
    TAF_MTA_CMD_BUFFER_STRU             *pstCmdBuf              = VOS_NULL_PTR;
    LNAS_MTA_SET_UE_CENTER_CNF_STRU     *pstUECenterSetCnf      = VOS_NULL_PTR;
    MTA_AT_SET_UE_CENTER_CNF_STRU        stMtaAtUECenterSetCnf;

    PS_MEM_SET(&stMtaAtUECenterSetCnf, 0x0, sizeof(stMtaAtUECenterSetCnf));

    pstUECenterSetCnf = (LNAS_MTA_SET_UE_CENTER_CNF_STRU *)pMsg;

    /* 如果当前定时器不为运行状态 */
    if (TAF_MTA_TIMER_STATUS_RUNING != TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_UE_CENTER_SET_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLnasUECenterSetCnf: Timer was already stoped!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_UE_CENTER_SET_CNF);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_UE_CENTER_SET_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvLnasUECenterSetCnf: No Buffer!");
        return;
    }

    if (MTA_LMM_RESULT_NO_ERROR != pstUECenterSetCnf->ulRslt)
    {
        stMtaAtUECenterSetCnf.enResult= MTA_AT_RESULT_ERROR;
    }
    else
    {
        stMtaAtUECenterSetCnf.enResult= MTA_AT_RESULT_NO_ERROR;
    }

    TAF_MTA_SndAtMsg( (AT_APPCTRL_STRU *)(pstCmdBuf->pucMsgInfo),
                      ID_MTA_AT_UE_CENTER_SET_CNF,
                      sizeof(MTA_AT_SET_UE_CENTER_CNF_STRU),
                      (VOS_UINT8*)&stMtaAtUECenterSetCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiWaitLnasUECenterSetExpired
 功能描述  : 设置UE模式超时处理函数
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
VOS_VOID TAF_MTA_RcvTiWaitLnasUECenterSetExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_SET_UE_CENTER_CNF_STRU       stMtaAtUECenterSetCnf;

    PS_MEM_SET(&stMtaAtUECenterSetCnf, 0x0, sizeof(stMtaAtUECenterSetCnf));

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_UE_CENTER_SET_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        /*定时器超时log*/
        MTA_ERROR_LOG("TAF_MTA_RcvTiWaitLnasUECenterSetExpired: get command buffer failed!");
        return;
    }

    stMtaAtUECenterSetCnf.enResult = VOS_ERR;

    /* 上报给AT模块错误信息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_UE_CENTER_SET_CNF,
                     sizeof(MTA_AT_SET_UE_CENTER_CNF_STRU),
                     (VOS_UINT8*)&stMtaAtUECenterSetCnf);


    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtUECenterQryReq
 功能描述  : MTA收到ID_AT_MTA_UECENTER_QRY_REQ消息处理函数
 输入参数  : VOS_VOID *pMsg  --消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 日    期   : 2015年7月30日
 作    者   : lwx277467
 修改内容   : +CEUS新增函数
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtUECenterQryReq(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                    *pstUECenterQryReq = VOS_NULL_PTR;
    MTA_AT_QRY_UE_CENTER_CNF_STRU       stMtaAtUECenterQryCnf;

    PS_MEM_SET(&stMtaAtUECenterQryCnf, 0x0, sizeof(stMtaAtUECenterQryCnf));

    pstUECenterQryReq      = (AT_MTA_MSG_STRU *)pMsg;

    /* 如果当前定时器已启动，则返回失败 */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_UE_CENTER_QRY_CNF))
    {
        stMtaAtUECenterQryCnf.enResult = MTA_AT_RESULT_ERROR;

        TAF_MTA_SndAtMsg(&pstUECenterQryReq->stAppCtrl,
                      ID_MTA_AT_UE_CENTER_QRY_CNF,
                      sizeof(MTA_AT_QRY_UE_CENTER_CNF_STRU),
                      (VOS_UINT8*)&stMtaAtUECenterQryCnf);
        return;
    }

    TAF_MTA_SndLnasUECenterQryReq();

    /* 启动保护定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_UE_CENTER_QRY_CNF, TI_TAF_MTA_WAIT_UE_CENTER_QRY_CNF_TIMER_LEN);

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_UE_CENTER_QRY_CNF,
                                     (VOS_UINT8*)&pstUECenterQryReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndLnasUECenterSetReq
 功能描述  : MTA发消息给LNAS查询UE模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月30日
    作    者   : lwx277467
    修改内容   : 新增+CEUS命令
*****************************************************************************/
VOS_VOID TAF_MTA_SndLnasUECenterQryReq(VOS_VOID)
{
    MTA_LNAS_QRY_UE_CENTER_REQ_STRU     *pstUECenterQryReq = VOS_NULL_PTR;

    /* 申请消息结构内存 */
    pstUECenterQryReq = (MTA_LNAS_QRY_UE_CENTER_REQ_STRU *)TAF_MTA_ALLOC_MSG_WITH_HDR(sizeof(MTA_LNAS_QRY_UE_CENTER_REQ_STRU));

    if (VOS_NULL_PTR == pstUECenterQryReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLnasUECenterQryReq: Alloc msg fail!");
        return;
    }

    TAF_MTA_CLR_MSG_ENTITY(pstUECenterQryReq);

    /* 构造消息结构体 */
    TAF_MTA_CFG_MSG_HDR(pstUECenterQryReq,PS_PID_MM,ID_MTA_LNAS_QRY_UE_CENTER_REQ);

    /* 发送消息到LTE */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstUECenterQryReq))
    {
        MTA_ERROR_LOG("TAF_MTA_SndLnasUECenterSetReq(): Send MSG Fail!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvLnasUECenterSetCnf
 功能描述  : MTA收到LNAS设置UE模式消息回复处理函数
 输入参数  : pMsg  -- 消息数据结构首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月30日
    作    者   : lwx277467
    修改内容   : 新增+CEUS命令
*****************************************************************************/
VOS_VOID TAF_MTA_RcvLnasUECenterQryCnf(VOS_VOID *pMsg)
{
    TAF_MTA_CMD_BUFFER_STRU             *pstCmdBuf         = VOS_NULL_PTR;
    LNAS_MTA_QRY_UE_CENTER_CNF_STRU     *pstUECenterQryCnf = VOS_NULL_PTR;
    MTA_AT_QRY_UE_CENTER_CNF_STRU       stMtaAtUECenterQryCnf;

    PS_MEM_SET(&stMtaAtUECenterQryCnf, 0x0, sizeof(stMtaAtUECenterQryCnf));

    pstUECenterQryCnf = (LNAS_MTA_QRY_UE_CENTER_CNF_STRU *)pMsg;

    /* 如果当前定时器不为运行状态 */
    if (TAF_MTA_TIMER_STATUS_RUNING != TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_UE_CENTER_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLnasUECenterSetCnf: Timer was already stoped!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_UE_CENTER_QRY_CNF);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_UE_CENTER_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvLnasUECenterSetCnf: No Buffer!");
        return;
    }

    if (MTA_LMM_RESULT_NO_ERROR != pstUECenterQryCnf->enResult)
    {
        stMtaAtUECenterQryCnf.enResult      = MTA_AT_RESULT_ERROR;
    }
    else
    {
        stMtaAtUECenterQryCnf.enResult      = MTA_AT_RESULT_NO_ERROR;
        stMtaAtUECenterQryCnf.enUeCenter    = pstUECenterQryCnf->enUeCenter;
    }

    TAF_MTA_SndAtMsg( (AT_APPCTRL_STRU *)(pstCmdBuf->pucMsgInfo),
                      ID_MTA_AT_UE_CENTER_QRY_CNF,
                      sizeof(MTA_AT_QRY_UE_CENTER_CNF_STRU),
                      (VOS_UINT8*)&stMtaAtUECenterQryCnf);

    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiWaitLnasUECenterSetExpired
 功能描述  : 设置UE模式超时处理函数
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
VOS_VOID TAF_MTA_RcvTiWaitLnasUECenterQryExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_QRY_UE_CENTER_CNF_STRU       stMtaAtUECenterQryCnf;

    PS_MEM_SET(&stMtaAtUECenterQryCnf, 0x0, sizeof(stMtaAtUECenterQryCnf));

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_UE_CENTER_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        /*定时器超时log*/
        MTA_ERROR_LOG("TAF_MTA_RcvTiWaitLnasUECenterSetExpired: get command buffer failed!");
        return;
    }

    stMtaAtUECenterQryCnf.enResult = VOS_ERR;

    /* 上报给AT模块错误信息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_UE_CENTER_QRY_CNF,
                     sizeof(MTA_AT_QRY_UE_CENTER_CNF_STRU),
                     (VOS_UINT8*)&stMtaAtUECenterQryCnf);


    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

