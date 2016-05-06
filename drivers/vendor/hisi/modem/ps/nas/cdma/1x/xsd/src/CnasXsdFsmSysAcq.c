/*******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXsdFsmSysAcq.c
  版 本 号   : 初稿
  作    者   : l60609
  生成日期   : 2014年07月28日
  功能描述   : 1X SD SYSTEM ACQUIRE状态机事件处理函数
  函数列表   :
  修改历史   :
  1.日    期   : 2014年07月28日
    作    者   : l60609
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasCcb.h"
#include  "CnasPrlApi.h"
#include  "CnasXsdComFunc.h"
#include  "CnasXsdSndInternalMsg.h"
#include  "CnasXsdSndMscc.h"
#include  "CnasXsdSndCas.h"
#include  "CnasXsdFsmSysAcq.h"
#include  "CnasXsdFsmSysAcqTbl.h"
#include  "CnasXsdSysAcqStrategy.h"
#include  "CnasMntn.h"
#include  "CnasXsdMntn.h"
#include  "CnasTimerMgmt.h"
#include  "CnasXsdSndXreg.h"

#include "CnasXsdSndXcc.h"

#include "NasMntn.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XSD_FSM_SYS_ACQ_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
EXTERN VOS_UINT32                       g_CtrlCallRelScanList;

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccSysAcqReq_SysAcq_Init
 功能描述  : CNAS_XSD_SYS_ACQ_STA_INIT状态收到ID_MMA_XSD_SYSTEM_ACQUIRE_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月30日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2015年1月05日
    作    者   : y00245242
    修改内容   : 增加OOC搜索策略
  3.日    期   : 2015年12月10日
    作    者   : l00324781
    修改内容   : CL_MUTIMODE_OPTIMIZE修改，增加场景 SWITCH_ON_INIT_SEARCH
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccSysAcqReq_SysAcq_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanList = VOS_NULL_PTR;
    CNAS_PRL_FREQENCY_CHANNEL_STRU      astDstChan[CNAS_CAS_1X_MAX_FREQ_NUM];
    VOS_UINT16                          usCurScanListIndex;
    VOS_UINT16                          usDstChanNum;
    MSCC_XSD_SYSTEM_ACQUIRE_REQ_STRU   *pstSysAcqReq = VOS_NULL_PTR;

    /* 保存入口消息 */
    CNAS_XSD_SaveCurEntryMsg(ulEventType, pstMsg);

    pstScanList = CNAS_XSD_GetScanChanListAddr();

    /* 构造scan list */
    pstSysAcqReq = (MSCC_XSD_SYSTEM_ACQUIRE_REQ_STRU*)pstMsg;

    /* enSysAcqType等于NORMAL，表示是正常驻留请求，否则，是无卡开机的X模初搜，只为了获取当前手机的位置信息
       只同步电信常用频点，到返回频点同步相同后结束，不等待系统消息
    */
    if (MSCC_XSD_SYS_ACQ_TYPE_NORMAL == pstSysAcqReq->enSysAcqType)
    {
        CNAS_XSD_BuildScanChanList(CNAS_XSD_SYS_ACQ_SCENE_SWITCH_ON, 0, VOS_NULL_PTR, pstScanList);
    }
    else
    {
        CNAS_XSD_BuildScanChanList(CNAS_XSD_SYS_ACQ_SCENE_POWER_ON_INIT_SEARCH, 0, VOS_NULL_PTR, pstScanList);
    }

    /* 构造的scan list为空 */
    if (0 == pstScanList->usTotalNum)
    {
        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_XSD_SndSysAcqRslt(CNAS_XSD_SYSTEM_ACQUIRED_RESULT_FAILURE, CNAS_XSD_SYS_ACQ_SCENE_SWITCH_ON,VOS_FALSE);

        /* 退出层二状态机 */
        CNAS_XSD_QuitFsmSysAcq_SysAcq();

        return VOS_TRUE;
    }

    /* 在状态机上下文中初始化available list */

    usCurScanListIndex = CNAS_XSD_GetCurChannelScanIndex();

    usDstChanNum       = 0;

    /* 获取下组可以扫描的频点列表 */
    CNAS_XSD_GetNextScanChanList_SysAcq(usCurScanListIndex, &usDstChanNum, astDstChan, pstScanList);

    /* 给CAS发送ID_CNAS_CAS_1X_SYSTEM_SYNC_REQ */
    CNAS_XSD_SndCasSysSyncReq(usDstChanNum, astDstChan);

    /* 给MSCC发送ID_XSD_MSCC_SYSTEM_ACQUIRE_START_IND */
    CNAS_XSD_SndMsccSysAcqStartInd();

    /* 迁移到 CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态, 并启动保护定时器TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF);

    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF, usDstChanNum * TI_CNAS_XSD_WAIT_CAS_SYNC_ONE_FREQ_LEN + 5);

    CNAS_XSD_SetSystemCampOnFlag(VOS_FALSE);
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvXsdSysAcqReq_SysAcq_Init
 功能描述  : CNAS_XSD_SYS_ACQ_STA_INIT状态收到ID_CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月5日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2015年1月5日
    作    者   : w00176964
    修改内容   : CDMA 1X Iteration 6 Modified

  3.日    期   : 2015年1月08日
    作    者   : y00245242
    修改内容   : 增加OOC搜索策略

  4.日    期   : 2015年7月20日
    作    者   : y00245242
    修改内容   : iteration 17开发

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvXsdSysAcqReq_SysAcq_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ_STRU                  *pstIntSysAcqReq         = VOS_NULL_PTR;
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanList             = VOS_NULL_PTR;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          astDstChan[CNAS_CAS_1X_MAX_FREQ_NUM];
    VOS_UINT16                                              usCurScanListIndex;
    VOS_UINT16                                              usDstChanNum;

    /* 保存入口消息 */
    CNAS_XSD_SaveCurEntryMsg(ulEventType, pstMsg);

    pstIntSysAcqReq   = (CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ_STRU *)pstMsg;
    pstScanList       = CNAS_XSD_GetScanChanListAddr();

    CNAS_XSD_BuildScanChanList(pstIntSysAcqReq->enSysAcqScene, (VOS_UINT16)(pstIntSysAcqReq->ulFreqNum), &pstIntSysAcqReq->astFreq[0], pstScanList);

    /* 构造的scan list为空 */
    if (0 == pstScanList->usTotalNum)
    {
        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_XSD_SndSysAcqRslt(CNAS_XSD_SYSTEM_ACQUIRED_RESULT_FAILURE, pstIntSysAcqReq->enSysAcqScene,CNAS_XSD_IsImmediateSysAcq_SysAcq());


        /* 退出层二状态机 */
        CNAS_XSD_QuitFsmSysAcq_SysAcq();

        return VOS_TRUE;
    }

    /* 在状态机上下文中初始化available list */

    usCurScanListIndex = CNAS_XSD_GetCurChannelScanIndex();
    usDstChanNum       = 0;

    /* 获取下组可以扫描的频点列表 */
    CNAS_XSD_GetNextScanChanList_SysAcq(usCurScanListIndex, &usDstChanNum, astDstChan, pstScanList);


    if (0 == usDstChanNum)
    {
        /* If Scan list is empty, quit the FSM with Fail Result */
        CNAS_XSD_SndSysAcqRslt(CNAS_XSD_SYSTEM_ACQUIRED_RESULT_FAILURE, pstIntSysAcqReq->enSysAcqScene,CNAS_XSD_IsImmediateSysAcq_SysAcq());

        CNAS_XSD_QuitFsmSysAcq_SysAcq();
        return VOS_TRUE;
    }

    /* 给CAS发送ID_CNAS_CAS_1X_SYSTEM_SYNC_REQ */
    CNAS_XSD_SndCasSysSyncReq(usDstChanNum, astDstChan);

    /* 给MSCC发送ID_XSD_MSCC_SYSTEM_ACQUIRE_START_IND */
    CNAS_XSD_SndMsccSysAcqStartInd();

    /* 迁移到 CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态, 并启动保护定时器TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF);

    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF, usDstChanNum * TI_CNAS_XSD_WAIT_CAS_SYNC_ONE_FREQ_LEN + 5);

    CNAS_XSD_SetSystemCampOnFlag(VOS_FALSE);
    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvCasSysSyncCnf_SysAcq_WaitCasSysSyncCnf
 功能描述  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态收到ID_CAS_CNAS_1X_SYSTEM_SYNC_CNF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月30日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2015年7月2日
    作    者   : y00245242
    修改内容   : iteration 17开发

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvCasSysSyncCnf_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf = VOS_NULL_PTR;

    pstSyncCnf = (CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU *)pstMsg;

    /* 停止保护定时器 */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF);

    /* 处理同步确认结果 */
    switch (pstSyncCnf->enSyncRslt)
    {
        case CNAS_CAS_1X_RSLT_FAILURE:
        default:
            CNAS_XSD_ProcCasSyncCnfFail_SysAcq(pstSyncCnf);
            break;

        case CNAS_CAS_1X_RSLT_SUCCESS:
            CNAS_XSD_ProcCasSyncCnfSucc_SysAcq(pstSyncCnf);
            break;

        case CNAS_CAS_1X_RSLT_NO_RF:
            CNAS_XSD_ProcCasSyncCnfNoRf_SysAcq();
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvTiWaitCasSysSyncCnfExpired_SysAcq_WaitCasSysSyncCnf
 功能描述  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态等ID_CAS_CNAS_1X_SYS-
             TEM_SYNC_CNF消息超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiWaitCasSysSyncCnfExpired_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvTiWaitCasSysSyncCnfExpired_SysAcq_WaitCasSysSyncCnf: timer out");

    /* 给CAS发送ID_CNAS_CAS_1X_STOP_SYSTEM_SYNC_REQ消息停止同步 */
    CNAS_XSD_SndCasStopSysSyncReq();

    /* 迁移到 CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF状态, 并启动保护定时器TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF, TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccPowerOffReq_SysAcq_WaitCasSysSyncCnf
 功能描述  : 等待CAS的系统同步回复状态收到关机请求的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月11日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2014年11月18日
    作    者   : c00299063
    修改内容   : 添加清空缓存

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccPowerOffReq_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 清空缓存 */
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-18, begin */
    CNAS_XSD_InitCacheMsgQueue(CNAS_XSD_INIT_CTX_POWEROFF, &(CNAS_XSD_GetXsdCtxAddr()->stCacheMsgQueue));
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-18, end */

    /* 缓存关机请求 */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    CNAS_XSD_StartTimer(TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER, TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvTiPowerOffCampOnProtectTimerExpired_SysAcq_WaitCasSysSyncCnf
 功能描述  : 等待CAS的系统同步回复状态收到关机保护定时器的超时处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月11日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiPowerOffCampOnProtectTimerExpired_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF);

    /* 设置状态机打断标记 */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    /* 给CAS发送ID_CNAS_CAS_1X_STOP_SYSTEM_SYNC_REQ消息停止同步 */
    CNAS_XSD_SndCasStopSysSyncReq();

    /* 迁移到 CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF状态, 并启动保护定时器TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF, TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvTiAvailableTimerExpired_SysAcq_WaitCasSysSyncCnf
 功能描述  : 等待CAS的系统同步回复状态收到收到available定时器超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月4日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiAvailableTimerExpired_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_SetOocWaitSearchFlag(VOS_TRUE);

    return VOS_TRUE;
}



VOS_UINT32 CNAS_XSD_RcvMsccPowerSaveReq_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 清除低优先级打断和之前打断的缓存消息 */
    if (VOS_TRUE == CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_SRV_ACQ_REQ))
    {
        CNAS_XSD_SndMsccSrvAcqCnf(NAS_MSCC_PIF_SRV_ACQ_RESULT_FAIL);

        CNAS_XSD_SetSrvAcqFlg(VOS_FALSE);
    }

    /* 清空缓存 */
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-18, begin */
    CNAS_XSD_InitCacheMsgQueue(CNAS_XSD_INIT_CTX_POWEROFF, &(CNAS_XSD_GetXsdCtxAddr()->stCacheMsgQueue));
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-18, end */

    /* Stop Sync Cnf protect timer */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF);

    /* Save the Power Save Request in cache */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* Set Abort flag to true */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    /* Send Stop Sync Req to CAS */
    CNAS_XSD_SndCasStopSysSyncReq();

    /* Set next State to Wait CAS Stop Sync Cnf and start the protect timer */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF, TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvCasOhmInd_SysAcq_WaitCasOhmInd
 功能描述  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND状态收到ID_CAS_CNAS_1X_OHM_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月31日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2015年7月9日
    作    者   : y00245242
    修改内容   : iteration 17开发

  3.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvCasOhmInd_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_PRL_1X_SYSTEM_STRU             stCurSysInfo;
    VOS_UINT32                          ulIsNegSys;
    CAS_CNAS_1X_OHM_IND_STRU           *pstOhmInd = VOS_NULL_PTR;

    pstOhmInd = (CAS_CNAS_1X_OHM_IND_STRU *)pstMsg;

    /* Stop the Timer */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND);

    stCurSysInfo.stFreq.enBandClass = pstOhmInd->usBandClass;
    stCurSysInfo.stFreq.usChannel   = pstOhmInd->usFreq;
    stCurSysInfo.usSid              = pstOhmInd->usSid;
    stCurSysInfo.usNid              = pstOhmInd->usNid;

    /* 如果不是available系统，刷新overheader上报的频点信息 */
    if (VOS_FALSE == CNAS_XSD_GetAvailSysAcqListFlg_SysAcq())
    {
        /* 更新overheader上报的频点到CCB中 */
        CNAS_CCB_SetCdmaOhmFreq(&(stCurSysInfo.stFreq));
    }

    ulIsNegSys = CNAS_XSD_IsCurSysNotSuitableSys(&stCurSysInfo,
                                                 pstOhmInd->enServiceInfoIncl,
                                                 pstOhmInd->stServiceInfo.usMcc);

    if (VOS_TRUE == ulIsNegSys)
    {
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvCasOhmInd_SysAcq_WaitCasOhmInd: The CAS Ind System is Neg!");
    }

    CNAS_XSD_ProcCasOhmInd(pstOhmInd, ulIsNegSys);

    if(VOS_TRUE == CNAS_XSD_GetAbortFlg_SysAcq())
    {
        CNAS_XSD_SndSysAcqRslt(CNAS_XSD_SYSTEM_ACQUIRED_RESULT_ABORTED,
                               CNAS_XSD_GetCurSysAcqScene_SysAcq(),
                               CNAS_XSD_IsImmediateSysAcq_SysAcq());
    }
    else
    {
        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_XSD_SndSysAcqRslt(CNAS_XSD_SYSTEM_ACQUIRED_RESULT_SUCCESS, CNAS_XSD_GetCurSysAcqScene_SysAcq(), VOS_FALSE);
    }

    /* 退出层二状态机 */
    CNAS_XSD_QuitFsmSysAcq_SysAcq();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvCasSysDeterminInd_SysAcq_WaitCasOhmInd
 功能描述  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND状态收到ID_CAS_CNAS_1X_SYSTEM_DETERMIN_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月13日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2014年12月25日
    作    者   : w00176964
    修改内容   : CDMA Iteration 6 Modified:Add other SD reason
  3.日    期   : 2015年5月20日
    作    者   : h00313353
    修改内容   : DSDS NO RF处理
  4.日    期   : 2015年7月9日
    作    者   : y00245242
    修改内容   : iteration 17开发
  5.日    期   : 2015年9月11日
    作    者   : y00245242
    修改内容   : DTS2015090601618
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvCasSysDeterminInd_SysAcq_WaitCasOhmInd
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd = VOS_NULL_PTR;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreq           = VOS_NULL_PTR;

    pstSysDeterminInd = (CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU *)pstMsg;

    /* 有打断标记需要退出 */
    if (VOS_TRUE == CNAS_XSD_GetAbortFlg_SysAcq())
    {
        /* 停止保护定时器 */
        CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND);

        CNAS_XSD_PerformAbortProcedure_SysAcq();

        return VOS_TRUE;
    }

    if (VOS_TRUE == CNAS_XSD_GetNdssIndFlag())
    {
        CNAS_XSD_SetNdssIndFlag(VOS_FALSE);

        CNAS_XSD_SndXccNdssResultInd(XSD_XCC_NDSS_RESULT_FAILURE);
    }

    /* 获取上次同步成功的频点 */
    pstFreq = CNAS_XSD_GetLastSyncedFreq();

    /***********************************************************************************************
     * 1. 刷新scan list中上次同步成功的频点为搜索不存在
     **********************************************************************************************/
    CNAS_XSD_UpdateChanStatusUponRcvCasDeterminInd_SysAcq(pstFreq);



    /***********************************************************************************************
     * 2. GEO系统记录搜索列表存在时，刷新GEO系统记录搜索列表中的频点为搜索不存在
     **********************************************************************************************/
    if (VOS_NULL_PTR != CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq()->pstAcqSysInfo)
    {
        CNAS_XSD_UpdateGeoSysRecordStatusUponReceivedDeterminInd(pstFreq);
    }

    switch (pstSysDeterminInd->enSdReason)
    {
        case CAS_CNAS_1X_SD_SYS_LOST_IND:
        case CAS_CNAS_1X_SD_NEW_SYSTEM_IND:
        case CAS_CNAS_1X_SD_ABNORMAL_IND:
        case CAS_CNAS_1X_SD_LOCK_IND:
        case CAS_CNAS_1X_SD_UNLOCK_IND:
        case CAS_CNAS_1X_SD_RESCAN_IND:
        case CAS_CNAS_1X_SD_ACQUISITION_FAIL:
            CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND);

            CNAS_XSD_SetRedirectionFlag(VOS_FALSE);

            CNAS_XSD_ContinueSysSync_SysAcq();
            break;

        case CAS_CNAS_1X_SD_PROTO_MISMATCH_IND:
            CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND);

            CNAS_XSD_ProcCasSystemDetermineIndWithProtoMisReason_SysAcq(ulEventType, pstMsg);
            break;

        /* 结果为NO RF的搜网失败的处理 */
        case CAS_CNAS_1X_SD_NO_RF:
            CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND);

            CNAS_XSD_SetRedirectionFlag(VOS_FALSE);

            /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
            CNAS_XSD_SndSysAcqRslt(CNAS_XSD_SYSTEM_ACQUIRED_RESULT_FAILURE, CNAS_XSD_SYS_ACQ_SCENE_NO_RF, VOS_FALSE);

            /* 退出层二状态机 */
            CNAS_XSD_QuitFsmSysAcq_SysAcq();
            break;

        default:

            /* other reasons we think cas will continue send overhead message to us,so we still
               stay on the current state. */
            CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvCasSysDeterminInd_SysAcq_WaitCasOhmInd: unknown reason");
            break;
    }


    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvTiWaitCasOhmIndExpired_SysAcq_WaitCasOhmInd
 功能描述  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND状态等ID_CAS_CNAS_1X_OHM_-
             IND消息超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2015年7月17日
    作    者   : y00245242
    修改内容   : iteration 17开发

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiWaitCasOhmIndExpired_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvTiWaitCasOhmIndExpired_SysAcq_WaitCasOhmInd: timer out");

    /* 不刷新SCAN LIST频点状态 */

    /* 有打断标记需要退出 */
    if (VOS_TRUE == CNAS_XSD_GetAbortFlg_SysAcq())
    {
        CNAS_XSD_PerformAbortProcedure_SysAcq();

        return VOS_TRUE;
    }

    CNAS_XSD_ContinueSysSync_SysAcq();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccPowerOffReq_SysAcq_WaitCasOhmInd
 功能描述  : 等待CAS的系统消息状态收到关机请求的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月11日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2014年11月18日
    作    者   : c00299063
    修改内容   : 添加清空缓存
  3.日    期   : 2015年8月6日
    作    者   : h00313353
    修改内容   : 迭代17 紧急呼
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccPowerOffReq_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_PRL_1X_SYSTEM_ID_STRU         *pstLastSyncedSys       = VOS_NULL_PTR;
    CNAS_PRL_1X_SYSTEM_STRU             st1xSysInfo;

    NAS_MEM_SET_S(&st1xSysInfo, sizeof(st1xSysInfo), 0x00, sizeof(CNAS_PRL_1X_SYSTEM_STRU));
    pstLastSyncedSys                    = CNAS_XSD_GetLastSyncedSys();

    st1xSysInfo.usSid                   = pstLastSyncedSys->usSid;
    st1xSysInfo.usNid                   = pstLastSyncedSys->usNid;
    st1xSysInfo.stFreq                  = CNAS_XSD_GetHistorySyncedSysFreqList()->astFreq[0];

    /* 清空缓存 */
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-18, begin */
    CNAS_XSD_InitCacheMsgQueue(CNAS_XSD_INIT_CTX_POWEROFF, &(CNAS_XSD_GetXsdCtxAddr()->stCacheMsgQueue));
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-18, end */

    /* 缓存关机请求 */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* 若当前系统无效,立即打断 */
    if (VOS_TRUE == CNAS_XSD_IsCurSysNotSuitableSys(&st1xSysInfo, VOS_FALSE, 0))
    {
        CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND);

        CNAS_XSD_SndSysAcqRslt(CNAS_XSD_SYSTEM_ACQUIRED_RESULT_ABORTED,
                               CNAS_XSD_GetCurSysAcqScene_SysAcq(),
                               CNAS_XSD_IsImmediateSysAcq_SysAcq());

        /* 退出层二状态机 */
        CNAS_XSD_QuitFsmSysAcq_SysAcq();

        return VOS_TRUE;
    }

    CNAS_XSD_StartTimer(TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER, TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvTiPowerOffCampOnProtectTimerExpired_SysAcq_WaitCasOhmInd
 功能描述  : 等待CAS的系统消息状态收到关机驻留保护定时器超时的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月11日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2014年10月11日
    作    者   : w00176964
    修改内容   : DTS2015012608600:关机定时器超时不再继续等OHM消息,直接退出处理缓存
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiPowerOffCampOnProtectTimerExpired_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 设置状态机打断标记 */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND);

    CNAS_XSD_PerformAbortProcedure_SysAcq();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvTiAvailableTimerExpired_SysAcq_WaitCasOhmInd
 功能描述  : 等待CAS的系统消息过程中，收到available定时器超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月4日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiAvailableTimerExpired_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_SetOocWaitSearchFlag(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   CNAS_XSD_RcvMsccPowerSaveReq_SysAcq_WaitCasOhmInd
Description     :   The function handles the power save request from MSCC in the wait OHM Ind State.

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - POinter to the message.
Outout parameters:  None
Return Value    :   VOS_TRUE
Modify History:
    1)  Date    :   2014-01-31
        Author  :   a00295761
        Modify content :    Create
    2)  Date    :   2015-05-28
        Author  :   w00176964
        Modify content :DTS2015052903319:power save在等OHM消息时需要延迟打断
*****************************************************************************/

VOS_UINT32 CNAS_XSD_RcvMsccPowerSaveReq_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_PRL_1X_SYSTEM_ID_STRU         *pstLastSyncedSys       = VOS_NULL_PTR;
    CNAS_PRL_1X_SYSTEM_STRU             st1xSysInfo;

    NAS_MEM_SET_S(&st1xSysInfo, sizeof(st1xSysInfo), 0x00, sizeof(CNAS_PRL_1X_SYSTEM_STRU));
    pstLastSyncedSys                    = CNAS_XSD_GetLastSyncedSys();

    /* 清除低优先级打断和之前打断的缓存消息 */
    if (VOS_TRUE == CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_SRV_ACQ_REQ))
    {
        CNAS_XSD_SndMsccSrvAcqCnf(NAS_MSCC_PIF_SRV_ACQ_RESULT_FAIL);

        CNAS_XSD_SetSrvAcqFlg(VOS_FALSE);
    }

    /* 清空缓存 */
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-18, begin */
    CNAS_XSD_InitCacheMsgQueue(CNAS_XSD_INIT_CTX_POWEROFF, &(CNAS_XSD_GetXsdCtxAddr()->stCacheMsgQueue));
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-18, end */

    st1xSysInfo.usSid                   = pstLastSyncedSys->usSid;
    st1xSysInfo.usNid                   = pstLastSyncedSys->usNid;
    st1xSysInfo.stFreq                  = CNAS_XSD_GetHistorySyncedSysFreqList()->astFreq[0];

    /* 紧急呼流程中，打断处理 */
    /* 缓存业务触发搜网请求 */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* 若当前系统有效，延迟打断 */
    if (VOS_TRUE != CNAS_XSD_IsCurSysNotSuitableSys(&st1xSysInfo, VOS_FALSE, 0))
    {
        /* 设置状态机打断标记 */
        CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

        return VOS_TRUE;
    }

    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND);

    CNAS_XSD_SndSysAcqRslt(CNAS_XSD_SYSTEM_ACQUIRED_RESULT_ABORTED,
                           CNAS_XSD_GetCurSysAcqScene_SysAcq(),
                           CNAS_XSD_IsImmediateSysAcq_SysAcq());

    /* 退出层二状态机 */
    CNAS_XSD_QuitFsmSysAcq_SysAcq();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvCasStopSysSyncCnf_SysAcq_WaitCasStopSysSyncCnf
 功能描述  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF状态收到ID_CAS_CNAS_1X_STOP_SYSTEM_SYNC_CNF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2015年1月05日
    作    者   : y00245242
    修改内容   : 增加OOC搜索策略

  3.日    期   : 2015年7月9日
    作    者   : y00245242
    修改内容   : iteration 17开发

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvCasStopSysSyncCnf_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* 停止保护定时器 */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF);

    /***********************************************************************************************
     * 1. 处理打断流程
     **********************************************************************************************/
    if (VOS_TRUE == CNAS_XSD_GetAbortFlg_SysAcq())
    {
        CNAS_XSD_PerformAbortProcedure_SysAcq();

        return VOS_TRUE;
    }

    /***********************************************************************************************
     * 2. 继续进行同步
     **********************************************************************************************/
    CNAS_XSD_ContinueSysSync_SysAcq();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvTiWaitCasStopSysSyncCnfExpired_SysAcq_WaitCasStopSysSyncCnf
 功能描述  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF状态等ID_CAS_CNAS_1-
             X_STOP_SYSTEM_SYNC_CNF消息超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2015年1月05日
    作    者   : y00245242
    修改内容   : 增加OOC搜索策略

  3.日    期   : 2015年7月9日
    作    者   : y00245242
    修改内容   : iteration 17开发
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiWaitCasStopSysSyncCnfExpired_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvTiWaitCasStopSysSyncCnfExpired_SysAcq_WaitCasStopSysSyncCnf: timer out");

    /***********************************************************************************************
     * 1. 处理打断流程
     **********************************************************************************************/
    if (VOS_TRUE == CNAS_XSD_GetAbortFlg_SysAcq())
    {
        CNAS_XSD_PerformAbortProcedure_SysAcq();

        return VOS_TRUE;
    }

    /***********************************************************************************************
     * 2. 继续进行同步
     **********************************************************************************************/
    CNAS_XSD_ContinueSysSync_SysAcq();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccPowerOffReq_SysAcq_WaitCasStopSysSyncCnf
 功能描述  : 等待CAS的停止系统同步回复状态收到关机请求的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月11日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2014年11月18日
    作    者   : c00299063
    修改内容   : 添加清空缓存

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccPowerOffReq_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 清空缓存 */
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-18, begin */
    CNAS_XSD_InitCacheMsgQueue(CNAS_XSD_INIT_CTX_POWEROFF, &(CNAS_XSD_GetXsdCtxAddr()->stCacheMsgQueue));
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-18, end */

    /* 缓存关机请求 */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    CNAS_XSD_StartTimer(TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER, TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvTiPowerOffProtectTimerExpired_SysAcq_WaitCasStopSysSyncCnf
 功能描述  : 等待CAS的停止系统同步回复状态收到关机保护定时器超时消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月11日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiPowerOffCampOnProtectTimerExpired_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 设置状态机打断标记 */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvTiAvailableTimerExpired_SysAcq_WaitCasStopSysSyncCnf
 功能描述  : 等待CAS的停止系统同步过程中，收到available定时器超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月4日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiAvailableTimerExpired_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_SetOocWaitSearchFlag(VOS_TRUE);

    return VOS_TRUE;
}



VOS_UINT32 CNAS_XSD_RcvMsccPowerSaveReq_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 清除低优先级打断和之前打断的缓存消息 */
    if (VOS_TRUE == CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_SRV_ACQ_REQ))
    {
        CNAS_XSD_SndMsccSrvAcqCnf(NAS_MSCC_PIF_SRV_ACQ_RESULT_FAIL);

        CNAS_XSD_SetSrvAcqFlg(VOS_FALSE);
    }

    /* 清空缓存 */
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-18, begin */
    CNAS_XSD_InitCacheMsgQueue(CNAS_XSD_INIT_CTX_POWEROFF, &(CNAS_XSD_GetXsdCtxAddr()->stCacheMsgQueue));
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-18, end */

    /* Save the Power Save Request in cache */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* Set Abort flag to true */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 FUNCTION NAME    : CNAS_XSD_PerformBestPreferedSystemSelectionAfterSyncSucc_SysAcq
 DESCRIPTION      : process system selection while the acquire mode is best prefered,in this case,we
                    have to find the best prefered system in PRL
 INPUT PARAMETER  : pstSyncCnf  -- 同步确认消息
 OUTPUT PARAMETER : none
 RETURN           : none
 CALLING FUNCTION :
 CALLED FUNCTION  :

 History modification:
  1.DATE         : 21/8/2014
    EDITOR       : y00245242
    MODIFICATION : create

  2.DATE         : 5/1/2015
    EDITOR       : w00176964
    MODIFICATION : CDMA 1X Iteration 6 Modifed:modified the function name

  3.日    期   : 2015年1月12日
    作    者   : y00245242
    修改内容   : 增加OOC搜索策略

  4.日    期   : 2015年7月7日
    作    者   : y00245242
    修改内容   : iteration 17开发
*****************************************************************************/
VOS_VOID CNAS_XSD_PerformBestPreferedSystemSelectionAfterSyncSucc_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
)
{
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList = VOS_NULL_PTR;

    /***********************************************************************************************
     * 1.处理GEO系统记录搜索列表不存在的场景
     **********************************************************************************************/
    pstGeoSysRecSrchList = CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq();

    if (VOS_NULL_PTR == pstGeoSysRecSrchList->pstAcqSysInfo)
    {
        /* GEO系统记录搜索列表不存在的处理 */
        CNAS_XSD_PreformBestPreferedSystemSelectionAndNoGeoSysRecordSearchList_SysAcq(pstSyncCnf);

        return;
    }

    /***********************************************************************************************
     * 2.处理GEO系统记录搜索列表存在的场景
     **********************************************************************************************/
    CNAS_XSD_PreformBestPreferedSystemSelectionAndGeoSysRecordSearchListExist_SysAcq(pstSyncCnf);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_PerformNormalCallRedialSystemSeletion_SysAcq
 功能描述  : Do system selection on normal call redial scene

 输入参数  : pstCurSysInfo  -- the current system synchronized.
             pstGeoListInfo -- GEO list information of the synchronized system

 输出参数  : none

 返 回 值  : VOS_TRUE  -- current system can be camped on
             VOS_FALSE -- current system is not suitable to camp on
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 27/11/2014
    作    者   : y00245242
    修改内容   : create

  2.日    期   : 31/12/2014
    作    者   : y00245242
    修改内容   : add home SID/NID list

  3.日    期   : 2015/7/2
    作    者   : w00242748
    修改内容   : CDMA 1X Iteration 17

*****************************************************************************/
VOS_UINT32 CNAS_XSD_PerformNormalCallRedialSystemSeletion_SysAcq(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysInfo
)
{
    CNAS_PRL_SYS_PRI_TYPE_ENUM_UINT32                       enSysPref;
    CNAS_PRL_SYS_ROAMING_IND_ENUM_UINT8                     enRoamingInd;
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                     stCurSysGeoListInfo;
    CNAS_PRL_1X_SYSTEM_STRU                                *pstOrigSysInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulIsNegSys;

    ulIsNegSys = VOS_FALSE;

    /* reference from chapter 4.7.2 in CDG 143:
       The MS shall only stay and try to place the call on systems that comply with one
       of the following criteria:

       1. Systems that are same or more preferred than the original system;

       2. Systems have a home roaming indicator;

       3. The MS is allowed to place the call on a system from a different GEO (i.e., jump a GEO)
          as long this system meets one of the above criteria.

          Note: The criteria 3 has been included in the aboving criteria 1.
    */

    pstOrigSysInfo = CNAS_XSD_GetCallOrignalSys();

    /* check if the current system is orignal system */
    if (VOS_TRUE == CNAS_PRL_Is1xSysMatched(pstOrigSysInfo, pstCurSysInfo))
    {
        return VOS_TRUE;
    }

    /* check当前系统是否是home系统，不依赖与PRL */
    if (VOS_TRUE == CNAS_XSD_IsCurSysHomeSystemIndependenceOnPrl(pstCurSysInfo))
    {
        return VOS_TRUE;
    }

    /* check if the current system is negative system in PRL system table */
    ulIsNegSys = CNAS_XSD_IsCurSysNotSuitableSys(pstCurSysInfo, VOS_FALSE, 0);

    if (VOS_TRUE == ulIsNegSys)
    {
        return VOS_FALSE;
    }

    ulIsNegSys = CNAS_XSD_IsCurSysNotSuitableSys(pstOrigSysInfo, VOS_FALSE, 0);

    if (VOS_TRUE == ulIsNegSys)
    {
        return VOS_TRUE;
    }

    NAS_MEM_SET_S(&stCurSysGeoListInfo, sizeof(stCurSysGeoListInfo), 0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));

    CNAS_PRL_Get1xSysGeoList(pstCurSysInfo, &stCurSysGeoListInfo);

    /* check if current system is home roaming indicator */
    if (VOS_TRUE == CNAS_PRL_IsCurrentSystemHomeRoamingIndicator(pstCurSysInfo,
                                                                 &stCurSysGeoListInfo,
                                                                 &enRoamingInd))
    {
        return VOS_TRUE;
    }

    /* compare the priority between current system and orignal system */
    enSysPref = CNAS_PRL_CompareSystemPreference(pstCurSysInfo, pstOrigSysInfo);

    if ((CNAS_PRL_SYS_PRI_HIGH == enSysPref)
     || (CNAS_PRL_SYS_PRI_SAME == enSysPref))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_PerformNotLessPrefSystemSelectionAfterSyncSucc_SysAcq
 功能描述  : process system selection while the acquire mode is not less prefer,such as on
             normal call redial scene,in this case,we have to find a system whose pri is same
             or more prefered than the current system
 输入参数  : pstSyncCnf  -- 同步确认消息

 输出参数  : none

 返 回 值  : none
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 27/11/2014
    作    者   : y00245242
    修改内容   : create

  2.日    期   : 2015年1月05日
    作    者   : y00245242
    修改内容   : 增加OOC搜索策略

  3.日    期   : 2015年7月7日
    作    者   : y00245242
    修改内容   : iteration 17开发
*****************************************************************************/
VOS_VOID CNAS_XSD_PerformNotLessPrefSystemSelectionAfterSyncSucc_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU                       *pstSyncCnf
)
{
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          astDstChan[CNAS_CAS_1X_MAX_FREQ_NUM];
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanList = VOS_NULL_PTR;
    VOS_UINT16                                              usDstChanNum;
    VOS_UINT16                                              usCurScanListIndex;
    CNAS_PRL_1X_SYSTEM_STRU                                 stCurSysInfo;

    stCurSysInfo.stFreq.enBandClass = pstSyncCnf->stFreq.usBandClass;
    stCurSysInfo.stFreq.usChannel   = pstSyncCnf->stFreq.usChannel;
    stCurSysInfo.usNid              = pstSyncCnf->stSyncedSysId.usNid;
    stCurSysInfo.usSid              = pstSyncCnf->stSyncedSysId.usSid;

    /* check if orignal system is exist */
    if (VOS_FALSE == CNAS_XSD_GetCallOrigSysExistFlg())
    {
        /* if orignal system is not exist, here use procedure of switch on system selection */
        CNAS_XSD_PerformBestPreferedSystemSelectionAfterSyncSucc_SysAcq(pstSyncCnf);

        return;
    }

    /* check the current system is fit to camp on */
    if (VOS_TRUE == CNAS_XSD_PerformNormalCallRedialSystemSeletion_SysAcq(&stCurSysInfo))
    {
        /* notify CAS to camp on the current system */
        CNAS_XSD_SndCas1xCampSyncedChannelNtf();

        /* transfer to CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND state, start timer */
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND);
        CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND, TI_CNAS_XSD_WAIT_CAS_OHM_IND_LEN);
    }
    else
    {
        /* contine to request CAS synchronize system */
        usDstChanNum       = 0;
        usCurScanListIndex = CNAS_XSD_GetCurChannelScanIndex();
        pstScanList        = CNAS_XSD_GetScanChanListAddr();

        CNAS_XSD_GetNextScanChanList_SysAcq(usCurScanListIndex, &usDstChanNum, astDstChan, pstScanList);

        if (0 == usDstChanNum)
        {
            /* No frequencies need to synchronize */
            CNAS_XSD_ProcScanListSyncComplete_SysAcq();
        }
        else
        {
            /* contine to synchronize the remained frequencies */
            CNAS_XSD_ContinueSyncScanList_SysAcq(usDstChanNum, astDstChan);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_PerformSystemSelectionAfterSyncSucc_SysAcq
 功能描述  : 运行同步成功后的系统选择

 输入参数  : pstCurSysInfo -- the synchronized system

 输出参数  : none

 返 回 值  : none
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 27/11/2014
    作    者   : y00245242
    修改内容   : create
  2.日    期   : 25/12/2014
    作    者   : w00176964
    修改内容   : CDMA Iteration 6 Modified:Add system acquire mode
  3.日    期   : 2015年7月6日
    作    者   : y00245242
    修改内容   : iteration 17开发
  4.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XSD_PerformSystemSelectionAfterSyncSucc_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
)
{
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32                      enScanScene;
    CNAS_XSD_SYSTEM_ACQUIRE_MODE_ENUM_UINT8                 enSysAcqMode;
    VOS_UINT32                                              ulIsAnyCampOnFreq;
    CNAS_CCB_CARD_STATUS_ENUM_UINT8                         enCardStatus;

    enScanScene  = CNAS_XSD_GetCurSysAcqScene_SysAcq();
    enSysAcqMode = CNAS_XSD_GetSysAcqModeOfSpecialAcqScene(enScanScene);

    if (VOS_TRUE == g_CtrlCallRelScanList)
    {
        /* 如果是call release场景，且当前同步成功的频点不是任何系统都可驻留的频点，则按Best Prefer场景
           进行选择:
           由于目前call release后搜网，scan list构表采用一次构表(见call release场景下的scan list构表),
           而呼叫在TCH状态下的频点以及MRU0频点上的系统可以直接驻留，而后续频点需要按BEST PREFER选择，因此
           此处做特殊处理。
         */
        ulIsAnyCampOnFreq = CNAS_XSD_IsCallRelAnyCampOnFreq_SysAcq(&(pstSyncCnf->stFreq));

        if ((CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASED == CNAS_XSD_GetCurSysAcqScene_SysAcq())
         && (VOS_FALSE                            == ulIsAnyCampOnFreq))
        {
            enSysAcqMode = CNAS_XSD_SYSTEM_ACQUIRE_MODE_BEST_PREF;
        }
    }

    enCardStatus = CNAS_CCB_GetCsimCardStatus();

    if (CNAS_CCB_CARD_STATUS_ABSENT == enCardStatus)
    {
        enSysAcqMode = CNAS_XSD_SYSTEM_ACQUIRE_MODE_ANY;
    }

    CNAS_MNTN_LogCommonStatusInfo(UEPS_PID_XSD, (VOS_UINT8)enCardStatus);

    switch (enSysAcqMode)
    {
        case CNAS_XSD_SYSTEM_ACQUIRE_MODE_NOT_LESS_PREF:

            CNAS_XSD_PerformNotLessPrefSystemSelectionAfterSyncSucc_SysAcq(pstSyncCnf);
            break;

        case CNAS_XSD_SYSTEM_ACQUIRE_MODE_ALLOWED:

            CNAS_XSD_PerformAllowedSystemSelectionAfterSyncSucc_SysAcq(pstSyncCnf);
            break;

        case CNAS_XSD_SYSTEM_ACQUIRE_MODE_BEST_PREF:

            CNAS_XSD_PerformBestPreferedSystemSelectionAfterSyncSucc_SysAcq(pstSyncCnf);
            break;

        case CNAS_XSD_SYSTEM_ACQUIRE_MODE_SPECIFIC:

            CNAS_XSD_PerformSpecificSystemSelectionAfterSyncSucc_SysAcq(pstSyncCnf);
            break;

        case CNAS_XSD_SYSTEM_ACQUIRE_MODE_ANY:

            CNAS_XSD_PerformAnySystemSelectionAfterSyncSucc_SysAcq(pstSyncCnf);
            break;

        case CNAS_XSD_SYSTEM_ACQUIRE_MODE_PREFERED:

            CNAS_XSD_PerformPreferedSystemSelectionAfterSyncSucc_SysAcq(pstSyncCnf);
            break;

        default:

            CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_PerformSystemSelectionAfterSyncSucc_SysAcq: unsupported system acquire mode");
            break;
    }
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcCasSyncCnfSucc_SysAcq
 功能描述  : 收到CAS的同步回复成功的处理
 输入参数  : pstSyncCnf----同步回复消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月21日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2015年1月05日
    作    者   : y00245242
    修改内容   : 增加OOC搜索策略
  3.日    期   : 2015年4月20日
    作    者   : w00242748
    修改内容   : DTS2015041609529:插入MRU0后，如果MRU0同步成功，但没办法驻留的
                 情况下会导致死循环搜网。
  4.日    期   : 2015年7月2日
    作    者   : y00245242
    修改内容   : iteration 17开发
  5.日    期   : 2015年9月14日
    作    者   : y00245242
    修改内容   : DTS2015090601618
  6.日    期   : 2015年12月10日
    作    者   : l00324781
    修改内容   : CL_MUTIMODE_OPTIMIZE修改，增加SWITCH_ON_INIT_SEARCH场景处理
*****************************************************************************/
VOS_VOID CNAS_XSD_ProcCasSyncCnfSucc_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
)
{
    /***********************************************************************************************
     * 1. 如果当前RF available为FALSE，通知上层RF available
     **********************************************************************************************/
    if (VOS_FALSE == CNAS_CCB_Get1XRfAvailFlg())
    {
        /* 上报MSCC NO RF消息 */
        CNAS_XSD_SndMsccRfAvailInd(VOS_TRUE);

        /* 设置当前RF可用标记为:RF可用 */
        CNAS_CCB_Set1XRfAvailFlg(VOS_TRUE);
    }

    /***********************************************************************************************
     * 2. 非锁频时，允许操作avoid频点
     **********************************************************************************************/
    if (VOS_FALSE == CNAS_XSD_GetFreqLockMode())
    {
        /* 处理系统同步确认消息中需要被禁的频点 */
        CNAS_XSD_ProcFreqAvoidedInCasSyncCnf(pstSyncCnf);
    }

    /***********************************************************************************************
     * 3. 通知上层当前同步的1X系统的SID信息
     **********************************************************************************************/
    if (pstSyncCnf->stSyncedSysId.usSid != CNAS_XSD_GetLastSyncedSys()->usSid)
    {
        /* 更新上次同步到的系统 */
        CNAS_XSD_UpdateLastSyncedSys((CNAS_PRL_1X_SYSTEM_ID_STRU *)&pstSyncCnf->stSyncedSysId);

        /* 通知MSCC新的SID,NID指示 */
        CNAS_XSD_SndMsccSidNidInd(pstSyncCnf->stSyncedSysId.usSid, pstSyncCnf->stSyncedSysId.usNid);
    }

   /***********************************************************************************************
     * 4. 更新同步到系统到历史同步的系统列表中
     **********************************************************************************************/
    CNAS_XSD_UpdateHistorySyncedSysFreqList((CNAS_PRL_FREQENCY_CHANNEL_STRU *)&(pstSyncCnf->stFreq));

    /***********************************************************************************************
     * 5. 刷新同步成功场景下的scan list中频点状态
     **********************************************************************************************/
    CNAS_XSD_UpdateChanStatusUponRcvCasSyncCnfSucc_SysAcq(pstSyncCnf);

    /***********************************************************************************************
     * 6. 进行根据场景进行系统选择
     **********************************************************************************************/
    CNAS_XSD_PerformSystemSelectionAfterSyncSucc_SysAcq(pstSyncCnf);

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcCasSyncCnfFail_SysAcq
 功能描述  : 收到CAS的同步回复失败的处理
 输入参数  : pstSyncCnf----同步回复消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月21日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2015年1月05日
    作    者   : y00245242
    修改内容   : 增加OOC搜索策略

  3.日    期   : 2015年4月20日
    作    者   : w00242748
    修改内容   : DTS2015041609529:插入MRU0后，如果MRU0同步成功，但没办法驻留的
                 情况下会导致死循环搜网。

  4.日    期   : 2015年7月2日
    作    者   : y00245242
    修改内容   : iteration 17开发

  5.日    期   : 2015年9月14日
    作    者   : y00245242
    修改内容   : DTS2015090601618
*****************************************************************************/
VOS_VOID CNAS_XSD_ProcCasSyncCnfFail_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
)
{
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList = VOS_NULL_PTR;
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstEmcScanChanList   = VOS_NULL_PTR;

    pstEmcScanChanList                  = CNAS_XSD_GetEmcCallRedialScanChanListAddr();

    /***********************************************************************************************
     * 1. 如果当前RF available为FALSE，通知上层RF available
     **********************************************************************************************/
    if (VOS_FALSE == CNAS_CCB_Get1XRfAvailFlg())
    {
        /* 上报MSCC NO RF消息 */
        CNAS_XSD_SndMsccRfAvailInd(VOS_TRUE);

        /* 设置当前RF可用标记为:RF可用 */
        CNAS_CCB_Set1XRfAvailFlg(VOS_TRUE);
    }

    /***********************************************************************************************
     * 2. 非锁频时，允许操作avoid频点
     **********************************************************************************************/
    if (VOS_FALSE == CNAS_XSD_GetFreqLockMode())
    {
        /* 处理系统同步确认消息中需要被禁的频点 */
        CNAS_XSD_ProcFreqAvoidedInCasSyncCnf(pstSyncCnf);
    }

    /***********************************************************************************************
     * 3. 刷新同步失败的频点scan list
     **********************************************************************************************/
    CNAS_XSD_UpdateChanStatusUponRcvCasSyncCnfFail_SysAcq(pstSyncCnf);

    /* 紧急场景的SD搜网，刷新紧急呼的频点列表，避免后续重复搜同步失败的频点 */
    if (VOS_NULL_PTR != pstEmcScanChanList->pstScanChanInfo)
    {
        if (VOS_TRUE == CNAS_XSD_IsEmcSDSysAcq_SysAcq(CNAS_XSD_GetCurSysAcqScene_SysAcq()))
        {
            (VOS_VOID)CNAS_XSD_UpdateSyncFailChanStatus(pstEmcScanChanList->usCurScanIndex,
                                                       (VOS_UINT16)pstSyncCnf->ulSyncFailFreqNum,
                                                        pstSyncCnf->astSyncRsltList,
                                                        pstEmcScanChanList);
        }
    }

    /***********************************************************************************************
     * 4. 处理GEO系统记录搜索列表状态
     **********************************************************************************************/
    pstGeoSysRecSrchList = CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq();

    if (VOS_NULL_PTR != pstGeoSysRecSrchList->pstAcqSysInfo)
    {
        /***********************************************************************************************
         * 4.1. 刷新GEO系统记录搜索列表中的频点为搜索不存在
         **********************************************************************************************/
        CNAS_XSD_UpdateSyncFailFreqStatusInGeoSysRecordSrchList_SysAcq((VOS_UINT16)(pstSyncCnf->ulSyncFailFreqNum),
                                                                       &pstSyncCnf->astSyncRsltList[0]);

        /*******************************************************************************************
         * 4.2. 继续GEO系统记录搜索列表搜索
         ******************************************************************************************/
        CNAS_XSD_ContinueGeoSysRecordSrch();

        return;
    }

    /***********************************************************************************************
     * 5. 调用GEO系统记录搜索list不存在的处理流程
     **********************************************************************************************/
    CNAS_XSD_ProcSyncFailAndNoGeoSysRecorSearchList_SysAcq(pstSyncCnf);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcCasSyncCnfNoRf_SysAcq
 功能描述  : 收到CAS的同步回复为NO RF处理，对于NO RF场景，需要通知上层当前RF不
             可用，且退出当前状态机
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XSD_ProcCasSyncCnfNoRf_SysAcq(VOS_VOID)
{
    /***********************************************************************************************
     * 对于NO RF场景，直接退出当前状态机
     **********************************************************************************************/

    /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
    CNAS_XSD_SndSysAcqRslt(CNAS_XSD_SYSTEM_ACQUIRED_RESULT_FAILURE, CNAS_XSD_SYS_ACQ_SCENE_NO_RF, VOS_FALSE);

    /* 退出层二状态机 */
    CNAS_XSD_QuitFsmSysAcq_SysAcq();
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcScanListSyncComplete_SysAcq
 功能描述  : 处理SCAN LIST已经全部同步完成
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2015年1月5日
    作    者   : w00176964
    修改内容   : CDMA 1X Iteration 6 Modified

  3.日    期   : 2015年7月4日
    作    者   : y00245242
    修改内容   : iteration 17开发

*****************************************************************************/
VOS_VOID CNAS_XSD_ProcScanListSyncComplete_SysAcq(VOS_VOID)
{
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32                      enScanScene;
    VOS_UINT16                                              usFreqNum;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          astFreqList[CNAS_CAS_1X_MAX_FREQ_NUM];

    enScanScene   = CNAS_XSD_GetCurSysAcqScene_SysAcq();

    /***********************************************************************************************
     * 1. 无available系统或不需要同步available系统
     **********************************************************************************************/
    if (VOS_FALSE == CNAS_XSD_IsAcquireAvaialSysNeeded(enScanScene))
    {
        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_XSD_SndSysAcqRslt(CNAS_XSD_SYSTEM_ACQUIRED_RESULT_FAILURE,
                               CNAS_XSD_GetCurSysAcqScene_SysAcq(),
                               CNAS_XSD_IsImmediateSysAcq_SysAcq());

        /* 退出层二状态机 */
        CNAS_XSD_QuitFsmSysAcq_SysAcq();

        return;
    }

    /***********************************************************************************************
     * 2. 同步available系统
     **********************************************************************************************/
    /* 设置标志: 当前捕获频点是来自available system list */
    CNAS_XSD_SetAvailSysAcqListFlg_SysAcq(VOS_TRUE);

    /* 发送同步请求，同步available系统 */
    NAS_MEM_SET_S(&astFreqList[0], sizeof(astFreqList), 0, sizeof(CNAS_CAS_1X_FREQENCY_CHANNEL_STRU) * CNAS_CAS_1X_MAX_FREQ_NUM);

    CNAS_XSD_GetNextAvailSysAcqList_SysAcq(&usFreqNum, &astFreqList[0]);

    CNAS_XSD_ContinueSyncScanList_SysAcq(usFreqNum, &astFreqList[0]);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ContinueSyncScanList_SysAcq
 功能描述  : SCAN LIST继续同步
 输入参数  : VOS_UINT16                          usDstChanNum
             CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstDstChan
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_ContinueSyncScanList_SysAcq(
    VOS_UINT16                          usDstChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstDstChan
)
{
    CNAS_XSD_SndCasSysSyncReq(usDstChanNum, pstDstChan);

    /* 迁移到 CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态, 并启动保护定时器TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF);

    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF, usDstChanNum * TI_CNAS_XSD_WAIT_CAS_SYNC_ONE_FREQ_LEN + 5);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_PeformBestPreferedSystemSelectionUsingNewGeo_SysAcq
 功能描述  : 基于一个新的GEOs进行最优的系统选择
 输入参数  : pstGeoListInfo -- 本次搜索的GEO list信息
             pstCurSysInfo  -- 当前的系统信息
             ulIsNegSys     -- 当前系统是否是negative系统
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月12日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2015年1月05日
    作    者   : y00245242
    修改内容   : 增加OOC搜索策略

  3.日    期   : 2015年7月2日
    作    者   : y00245242
    修改内容   : iteration 17开发
*****************************************************************************/
VOS_VOID CNAS_XSD_PeformBestPreferedSystemSelectionUsingNewGeo_SysAcq(
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo,
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
    VOS_UINT32                                              ulIsNegSys
)
{
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList = VOS_NULL_PTR;
    CNAS_CAS_1X_SYSTEM_IDENTITY_STRU                        stCurrSysId;
    CNAS_CAS_1X_SYNC_RSLT_INFO_STRU                         stSyncFailChan;
    CNAS_CAS_1X_FREQENCY_CHANNEL_STRU                       stFreq;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          astDstChan[CNAS_CAS_1X_MAX_FREQ_NUM];
    VOS_UINT16                                              usDstChanNum;

    /***********************************************************************************************
     * 1. 刷新GEO搜索列表中本次搜索GEO为已搜索
     **********************************************************************************************/
    CNAS_XSD_UpdateGeoListSrchStatus(pstGeoListInfo, VOS_TRUE);

    /***********************************************************************************************
     * 2. 构造新的GEO搜索列表
     **********************************************************************************************/
    pstGeoSysRecSrchList = CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq();

    NAS_MEM_SET_S(pstGeoSysRecSrchList, sizeof(CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU), 0, sizeof(CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU));

    CNAS_XSD_ConstructGeoSysRecordSrchList(pstGeoListInfo, pstCurSysInfo, pstGeoSysRecSrchList);

    if (VOS_NULL_PTR == pstGeoSysRecSrchList->pstAcqSysInfo)
    {
        /* 内存分配失败，直接返回 */
        return;
    }

    CNAS_XSD_LogAcqSystemList(pstGeoSysRecSrchList);

    if (VOS_FALSE == ulIsNegSys)
    {
        stFreq.usBandClass = pstCurSysInfo->stFreq.enBandClass;
        stFreq.usChannel   = pstCurSysInfo->stFreq.usChannel;

        stCurrSysId.usNid  = pstCurSysInfo->usNid;
        stCurrSysId.usSid  = pstCurSysInfo->usSid;

        /* 刷新当前同步成功的频点状态，GEO中系统记录搜索列表中最match的系统频点刷新为搜索存在，
         * 其他系统记录的频点刷新为搜索不存在 */
        CNAS_XSD_UpdateSyncSuccFreqStatusInGeoSysRecordSrchList_SysAcq(&stFreq,
                                                                       &stCurrSysId);
    }
    else
    {
        NAS_MEM_SET_S(&stSyncFailChan, sizeof(stSyncFailChan), 0, sizeof(CNAS_CAS_1X_SYNC_RSLT_INFO_STRU));

        stSyncFailChan.stFreq.usBandClass = pstCurSysInfo->stFreq.enBandClass;
        stSyncFailChan.stFreq.usChannel   = pstCurSysInfo->stFreq.usChannel;

        /* 当前系统是negative系统，刷新GEO中系统记录搜索列表中对应的频点为搜索不存在 */
        CNAS_XSD_UpdateSyncFailFreqStatusInGeoSysRecordSrchList_SysAcq(1, &stSyncFailChan);

        /* 当该系统是neg时，需刷新该频点为不存在，如果不刷新的话，继续同步仍然会同步该频点
           获取下一个同步频点时的逻辑为未同步或者同步存在 */
        CNAS_XSD_UpdateAvailOrNegSystemChanStatusInScanChanList_SysAcq(&pstCurSysInfo->stFreq,
                                                                       CNAS_XSD_GetScanChanListAddr());
    }

    /***********************************************************************************************
     * 3. 如果当前系统就是最高优先级系统，通知接入层驻留
     **********************************************************************************************/
    /* 根据scan list里列表中的频点状态，刷新GEO系统记录搜索列表中的频点状态及下次搜索索引 */
    CNAS_XSD_UpdateGeoSysRecordListInfoAccordingToScanChanList(pstGeoSysRecSrchList);

    if (VOS_TRUE == CNAS_XSD_IsCurrSysMostPref1xSysInGeoSysRecordSrchList(pstCurSysInfo, pstGeoSysRecSrchList))
    {
        /* 先提前通知上层服务状态 */
        CNAS_XSD_ReportSrvAvailableInd_SysAcq(pstCurSysInfo);

        /* 发送ID_CNAS_CAS_1X_CAMP_SYNCED_CHANNEL_NTF */
        CNAS_XSD_SndCas1xCampSyncedChannelNtf();

        /* 迁移到 CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND状态, 并启动保护定时器TI_CNAS_XSD_WAIT_CAS_OHM_IND */
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND);

        /* 启动保护定时器 */
        CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND, TI_CNAS_XSD_WAIT_CAS_OHM_IND_LEN);

        return;
    }

    /*******************************************************************************************
     * 4. 继续GEO系统记录搜索列表搜索
     ******************************************************************************************/
    usDstChanNum = 0;

    NAS_MEM_SET_S(&astDstChan[0], sizeof(astDstChan), 0, sizeof(astDstChan));

    CNAS_XSD_GetNextSysSyncListFromGeoSysRecordSrchList(CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq(),
                                                        &usDstChanNum,
                                                        &astDstChan[0]);

    if (0 != usDstChanNum)
    {
        /* 继续GEO系统记录频点同步操作 */
        CNAS_XSD_ContinueSyncScanList_SysAcq(usDstChanNum, &astDstChan[0]);

        return;
    }

    /*******************************************************************************************
     * 5. 清除GEO搜索列表状态以及释放GEO系统记录搜索列表内存
     ******************************************************************************************/
    /* 先清除GEO搜索列表状态 */
    CNAS_XSD_ClearGeoSrchListStatus();

    /* LOG GEO list搜索状态信息 */
    CNAS_XSD_LogGeoListSrchStatus(CNAS_XSD_GetGeoSrchListInfoAddr());

    /* 释放GEO系统记录搜索列表的内存 */
    if (VOS_NULL_PTR != CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq()->pstAcqSysInfo)
    {
        PS_MEM_FREE(UEPS_PID_XSD, CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq()->pstAcqSysInfo);
        CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq()->pstAcqSysInfo = VOS_NULL_PTR;
    }

    /*******************************************************************************************
     * 6. 继续scan list频点列表搜索
     ******************************************************************************************/
    usDstChanNum = 0;
    NAS_MEM_SET_S(&astDstChan[0], sizeof(astDstChan), 0, sizeof(astDstChan));

    CNAS_XSD_GetNextScanChanList_SysAcq(CNAS_XSD_GetCurChannelScanIndex(),
                                        &usDstChanNum,
                                        astDstChan,
                                        CNAS_XSD_GetScanChanListAddr());

    if (0 != usDstChanNum)
    {
        /* scan list未全部同步完，继续发同步请求 */
        CNAS_XSD_ContinueSyncScanList_SysAcq(usDstChanNum, astDstChan);

        return;
    }

    /*******************************************************************************************
     * 7. 处理scan list同步完成的后续流程
     ******************************************************************************************/
    /* scan list已全部同步完 */
    CNAS_XSD_ProcScanListSyncComplete_SysAcq();
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ContinueSysSync_SysAcq
 功能描述  : 继续系统捕获
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月13日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2015年1月05日
    作    者   : y00245242
    修改内容   : 增加OOC搜索策略

  2.日    期   : 2015年7月4日
    作    者   : y00245242
    修改内容   : iteration 17开发

*****************************************************************************/
VOS_VOID CNAS_XSD_ContinueSysSync_SysAcq(VOS_VOID)
{
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanList          = VOS_NULL_PTR;
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList = VOS_NULL_PTR;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          astDstChan[CNAS_CAS_1X_MAX_FREQ_NUM];
    VOS_UINT16                                              usCurScanListIndex;
    VOS_UINT16                                              usDstChanNum;

    /***********************************************************************************************
     * 1. 如果是available系统同步，继续available系统同步
     **********************************************************************************************/
    if (VOS_TRUE == CNAS_XSD_GetAvailSysAcqListFlg_SysAcq())
    {
        CNAS_XSD_ContinueAvailSysListSrch();

        return;
    }

    /***********************************************************************************************
     * 2. 处理GEO系统记录搜索列表存在的场景
     **********************************************************************************************/
    pstGeoSysRecSrchList = CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq();

    if (VOS_NULL_PTR != pstGeoSysRecSrchList->pstAcqSysInfo)
    {
        CNAS_XSD_ContinueGeoSysRecordSrch();

        return;
    }

    /***********************************************************************************************
     * 3. 继续scan list频点搜索
     **********************************************************************************************/
    usDstChanNum       = 0;
    pstScanList        = CNAS_XSD_GetScanChanListAddr();
    usCurScanListIndex = CNAS_XSD_GetCurChannelScanIndex();

    CNAS_XSD_GetNextScanChanList_SysAcq(usCurScanListIndex, &usDstChanNum, astDstChan, pstScanList);

    if (0 != usDstChanNum)
    {
        CNAS_XSD_ContinueSyncScanList_SysAcq(usDstChanNum, astDstChan);

        return;
    }

    /***********************************************************************************************
     * 4. scan list搜索完成处理
     **********************************************************************************************/
    CNAS_XSD_ProcScanListSyncComplete_SysAcq();

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetCurSysAcqScene_SysAcq
 功能描述  : 返回当前系统捕获场景
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月12日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2014年12月10日
    作    者   : l00324781
    修改内容   : CL_MUTIMODE_OPTIMIZE 增加新场景SWITCH_ON_INIT_SEARCH
*****************************************************************************/
CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32 CNAS_XSD_GetCurSysAcqScene_SysAcq(VOS_VOID)
{
    CNAS_XSD_MSG_STRU                                      *pstEntryMsg  = VOS_NULL_PTR;
    CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ_STRU                  *pstIntSysAcqReq = VOS_NULL_PTR;
    MSCC_XSD_SYSTEM_ACQUIRE_REQ_STRU                       *pstSysAqcReq    = VOS_NULL_PTR;

    /* 获得当前处理CNAS XSD入口消息的缓冲区地址 */
    pstEntryMsg                 = CNAS_XSD_GetCurrFsmEntryMsgAddr();

    if (CNAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_XSD_SYSTEM_ACQUIRE_REQ)
            == pstEntryMsg->ulEventType)
    {
        pstSysAqcReq = (MSCC_XSD_SYSTEM_ACQUIRE_REQ_STRU *)pstEntryMsg->aucMsgBuffer;

        if (MSCC_XSD_SYS_ACQ_TYPE_NORMAL == pstSysAqcReq->enSysAcqType)
        {
            return CNAS_XSD_SYS_ACQ_SCENE_SWITCH_ON;
        }
        else
        {
            return CNAS_XSD_SYS_ACQ_SCENE_POWER_ON_INIT_SEARCH;
        }
    }

    if (CNAS_BuildEventType(UEPS_PID_XSD, ID_CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ)
            == pstEntryMsg->ulEventType)
    {
        pstIntSysAcqReq = (CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ_STRU *)pstEntryMsg->aucMsgBuffer;

        return pstIntSysAcqReq->enSysAcqScene;
    }

    return CNAS_XSD_SYS_ACQ_SCENE_BUTT;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_IsImmediateSysAcq_SysAcq
 功能描述  : 判断当前是否需要立即搜
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2015年7月20日
    作    者   : y00245242
    修改内容   : iteration 17开发

*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsImmediateSysAcq_SysAcq(VOS_VOID)
{
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32  enSysAcqScene;

    enSysAcqScene = CNAS_XSD_GetCurSysAcqScene_SysAcq();

    /* call release场景scan list构表已经修改，采用一次构表(见call release场景下的build scan list函数)
     * 因此失败时，不用立即搜网
     */
    /* call release with redir的场景需要立即搜 */
    if (CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASED_WITH_REDIR == enSysAcqScene)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_IsEmergencySysAcq_SysAcq
 功能描述  : 判断当前是否为紧急呼叫的搜网场景，以下7种情况返回TRUE,其余情况返回FALSE
             CNAS_XSD_SYS_ACQ_SCENE_EMC_CALLBACK_SYSTEM_LOST 紧急呼Call Back搜网
             CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL           紧急呼搜网
             CNAS_XSD_SYS_ACQ_SCENE_EMC_CALL_RELEASED        紧急呼叫释放的搜网
             CNAS_XSD_SYS_ACQ_SCENE_REGIS_REJ_WITH_REDIR_AND_RTF_EMC
             CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_NOT_IN_PRL_OR_NEG_EMC
             CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_IN_PRL_AND_PREF_EMC
             CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_NOT_IN_PRL_EMC

 输入参数  : enSysAcqScene  当前的搜网场景
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月1日
    作    者   : h00313353
    修改内容   : DTS2015101200488

*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsEmergencySysAcq_SysAcq(
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene
)
{
    switch(enSysAcqScene)
    {
        case CNAS_XSD_SYS_ACQ_SCENE_EMC_CALLBACK_SYSTEM_LOST:
        case CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL:
        case CNAS_XSD_SYS_ACQ_SCENE_EMC_CALL_RELEASED:
            return VOS_TRUE;

        default:
            return CNAS_XSD_IsEmcSDSysAcq_SysAcq(enSysAcqScene);
    }
}
/*****************************************************************************
 函 数 名  : CNAS_XSD_IsEmcSDSysAcq_SysAcq
 功能描述  : 判断当前是否为紧急呼叫的搜网场景，以下7种情况返回TRUE,其余情况返回FALSE
             CNAS_XSD_SYS_ACQ_SCENE_REGIS_REJ_WITH_REDIR_AND_RTF_EMC
             CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_NOT_IN_PRL_OR_NEG_EMC
             CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_IN_PRL_AND_PREF_EMC
             CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST_SKIP_MRU0_EMC
             CNAS_XSD_SYS_ACQ_SCENE_REDIRECTION_WITH_INVALID_GSRDM_EMC
             CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_IN_PRL_EMC
             CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_NOT_IN_PRL_EMC

 输入参数  : enSysAcqScene  当前的搜网场景
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月09日
    作    者   : h00313353
    修改内容   : DTS2015120205246

*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsEmcSDSysAcq_SysAcq(
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene
)
{
    switch(enSysAcqScene)
    {
        case CNAS_XSD_SYS_ACQ_SCENE_REGIS_REJ_WITH_REDIR_AND_RTF_EMC:
        case CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_NOT_IN_PRL_OR_NEG_EMC:
        case CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_IN_PRL_AND_PREF_EMC:
        case CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST_SKIP_MRU0_EMC:
        case CNAS_XSD_SYS_ACQ_SCENE_REDIRECTION_WITH_INVALID_GSRDM_EMC:
        case CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_IN_PRL_EMC:
        case CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_NOT_IN_PRL_EMC:
            return VOS_TRUE;

        default:
            return VOS_FALSE;
    }
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetNextAvailSysAcqList_SysAcq
 功能描述  : 获取下一组需要捕获的列表
 输入参数  : pstAcqSysInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月14日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 29/12/2014
    作    者   : w00176964
    修改内容   : CDMA Iteration 6:Move the avail system list to the global variables

  3.日    期   : 2015年7月4日
    作    者   : y00245242
    修改内容   : iteration 17开发
*****************************************************************************/
VOS_VOID CNAS_XSD_GetNextAvailSysAcqList_SysAcq(
    VOS_UINT16                                             *pusFreqNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreqList
)
{
    CNAS_XSD_AVAILABLE_LIST_STRU       *pstAvailSysList = VOS_NULL_PTR;
    VOS_UINT16                          i;

    pstAvailSysList = CNAS_XSD_GetAvailSysFreqListAddr();

    *pusFreqNum = 0;

    for (i = pstAvailSysList->ucNextSrchIndex;
         i < CNAS_MIN(pstAvailSysList->ucAvailSysNum, CNAS_XSD_MAX_AVAILABLE_SYS_NUM);
         i++
         )
    {

        pstFreqList->enBandClass = pstAvailSysList->astAvailSystem[i].stFreq.enBandClass;
        pstFreqList->usChannel   = pstAvailSysList->astAvailSystem[i].stFreq.usChannel;

        pstFreqList++;
        (*pusFreqNum)++;

        if (*pusFreqNum == CNAS_CAS_1X_MAX_FREQ_NUM)
        {
            return;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_UpdateSyncFailFreqStatusInGeoSysRecordSrchList_SysAcq
 功能描述  : 更新捕获失败的系统状态
 输入参数  : usSyncFailChanNum  ------------  同步失败频点个数
             pstSyncFailChanList--------------同步失败的频点列表
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年8月05日
   作    者   : w00176964
   修改内容   : 新生成函数

 2.日    期   : 2015年7月4日
   作    者   : y00245242
   修改内容   : iteration 17开发
*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateSyncFailFreqStatusInGeoSysRecordSrchList_SysAcq(
    VOS_UINT16                          usSyncFailChanNum,
    CNAS_CAS_1X_SYNC_RSLT_INFO_STRU    *pstSyncFailChanList
)
{
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList = VOS_NULL_PTR;
    CNAS_XSD_SCAN_CHAN_STATUS_ENUM_UINT8                    enSysStatus;
    VOS_UINT16                                              i;

    pstGeoSysRecSrchList = CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq();

    enSysStatus   = CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST;

    for (i = 0; i < CNAS_MIN(usSyncFailChanNum, CNAS_CAS_1X_MAX_FREQ_NUM); i++)
    {
        /* 将获取列表中指定频点的对应列表全部刷新为捕获过不存在 */
        CNAS_XSD_UpdateSysFreqStatusByFreqChanInGeoSysRecordSrchList((CNAS_PRL_FREQENCY_CHANNEL_STRU *)&pstSyncFailChanList[i].stFreq,
                                                                     enSysStatus,
                                                                     pstGeoSysRecSrchList);
    }

    CNAS_XSD_LogAcqSystemList(pstGeoSysRecSrchList);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_UpdateSyncSuccFreqStatusInGeoSysRecordSrchList_SysAcq
 功能描述  : 更新GEO系统搜索列表中同步失败的频点状态
 输入参数  : pstFreq        -- 同步成功的频点
             pstSyncedSysId -- 同步到系统

 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年8月05日
   作    者   : w00176964
   修改内容   : 新生成函数

 2.日    期   : 2015年7月4日
   作    者   : y00245242
   修改内容   : iteration 17开发
*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateSyncSuccFreqStatusInGeoSysRecordSrchList_SysAcq(
    CNAS_CAS_1X_FREQENCY_CHANNEL_STRU                      *pstFreq,
    CNAS_CAS_1X_SYSTEM_IDENTITY_STRU                       *pstSyncedSysId
)
{
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList = VOS_NULL_PTR;
    CNAS_PRL_1X_SYSTEM_STRU                                 stAcqSuccSys;
    CNAS_XSD_SCAN_CHAN_STATUS_ENUM_UINT8                    enSysStatus;
    VOS_UINT16                                              i;

    stAcqSuccSys.stFreq.enBandClass = pstFreq->usBandClass;
    stAcqSuccSys.stFreq.usChannel   = pstFreq->usChannel;
    stAcqSuccSys.usNid              = pstSyncedSysId->usNid;
    stAcqSuccSys.usSid              = pstSyncedSysId->usSid;

    pstGeoSysRecSrchList = CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq();
    enSysStatus   = CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_EXIST;

    CNAS_XSD_UpdateSysFreqStatusBySysInGeoSysRecordSrchList(&stAcqSuccSys, enSysStatus, pstGeoSysRecSrchList);

    /* 对于发给AS的相同频点的其他SID+NID,应该是捕获失败的,更新对应的捕获系统状态 */
    enSysStatus   = CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST;
    for (i = 0; i < pstGeoSysRecSrchList->usTotalNum; i++)
    {
        if ((stAcqSuccSys.stFreq.enBandClass == pstGeoSysRecSrchList->pstAcqSysInfo[i].stAcqSys.stFreq.enBandClass)
         && (stAcqSuccSys.stFreq.usChannel   == pstGeoSysRecSrchList->pstAcqSysInfo[i].stAcqSys.stFreq.usChannel))
        {
            /* 捕获成功的系统不刷新状态 */
            if (VOS_FALSE == CNAS_PRL_Is1xSysIdMatched(stAcqSuccSys.usSid,
                                                       stAcqSuccSys.usNid,
                                                       pstGeoSysRecSrchList->pstAcqSysInfo[i].stAcqSys.usSid,
                                                       pstGeoSysRecSrchList->pstAcqSysInfo[i].stAcqSys.usNid))

            {
                pstGeoSysRecSrchList->pstAcqSysInfo[i].enSysStatus = enSysStatus;
            }
        }
    }

    CNAS_XSD_LogAcqSystemList(pstGeoSysRecSrchList);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_QuitFsmSysAcq
 功能描述  : 退出SYSTEM ACQUIRED状态机
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月25日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2014年12月3日
    作    者   : w00176964
    修改内容   : CDMA 1X Iteration 5 Modified
  3.日    期   : 2015年7月9日
    作    者   : y00245242
    修改内容   : iteration 17开发

  4.日    期   : 2015年7月21日
    作    者   : h00313353
    修改内容   : 迭代17 紧急呼
*****************************************************************************/
VOS_VOID CNAS_XSD_QuitFsmSysAcq_SysAcq(VOS_VOID)
{
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstCallRedialScanChanList = VOS_NULL_PTR;
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList           = VOS_NULL_PTR;
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32                      enCurAcqScene;

    enCurAcqScene                       = CNAS_XSD_GetCurSysAcqScene_SysAcq();

    /* 清除GEO搜索状态 */
    CNAS_XSD_ClearGeoSrchListStatus();

    /* LOG GEO list搜索状态信息 */
    CNAS_XSD_LogGeoListSrchStatus(CNAS_XSD_GetGeoSrchListInfoAddr());

    pstScanChanList           = CNAS_XSD_GetScanChanListAddr();
    switch (enCurAcqScene)
    {
        case CNAS_XSD_SYS_ACQ_SCENE_NORMAL_CALL_REDIAL:
            {
                /* for normal call redial scene, update the call redial channle list by the current
                   scan channle list */

                pstCallRedialScanChanList = CNAS_XSD_GetCallRedialScanChanListAddr();

                CNAS_XSD_UpdateScanChanList(pstCallRedialScanChanList, pstScanChanList);

                CNAS_XSD_LogScanChannelList(ID_CNAS_XSD_MNTN_LOG_CALL_REDIAL_SCAN_CHAN_LIST_IND,
                                            pstCallRedialScanChanList);
            }
            break;


        case CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL:
            {
                /* for emc call redial scene, update the call redial channle list by the current
                   scan channle list */
                pstCallRedialScanChanList = CNAS_XSD_GetEmcCallRedialScanChanListAddr();

                CNAS_XSD_UpdateScanChanList(pstCallRedialScanChanList, pstScanChanList);

                CNAS_XSD_LogScanChannelList(ID_CNAS_XSD_MNTN_LOG_EMC_CALL_REDIAL_SCAN_CHAN_LIST_IND,
                                            pstCallRedialScanChanList);
            }
            break;

        case CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASED_WITH_REDIR:
            {
                /* 根据scan list频点状态，刷新redirection频点状态 */
                CNAS_XSD_UpdateRedirectionFreqStatusAccordingToScanChanList(pstScanChanList);
            }
            break;

        default:
            break;
    }

    CNAS_XSD_QuitFsmL2();
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcFreqAvoidedInCasSyncCnf
 功能描述  : 处理CAS SYNC CNF消息中需要被禁的频点
 输入参数  : pstSyncCnf -- 系统同步确认消息指针

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月14日
    作    者   : y00245242
    修改内容   : 新生成函数

  2.日    期   : 2015年7月20日
    作    者   : h00313353
    修改内容   : 迭代17 紧急呼
*****************************************************************************/
VOS_VOID CNAS_XSD_ProcFreqAvoidedInCasSyncCnf(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
)
{
    VOS_UINT8                           i;
    CNAS_PRL_1X_SYSTEM_STRU             stSysInfo;
    VOS_UINT32                          ulIsNegSys;

    ulIsNegSys = VOS_FALSE;

    if (CNAS_CAS_1X_RSLT_SUCCESS == pstSyncCnf->enSyncRslt)
    {
        /* 处理成功的频点 */
        stSysInfo.stFreq.enBandClass = pstSyncCnf->stFreq.usBandClass;
        stSysInfo.stFreq.usChannel   = pstSyncCnf->stFreq.usChannel;

        stSysInfo.usNid  = pstSyncCnf->stSyncedSysId.usNid;
        stSysInfo.usSid  = pstSyncCnf->stSyncedSysId.usSid;

        ulIsNegSys = CNAS_XSD_IsCurSysNotSuitableSys(&stSysInfo, VOS_FALSE, 0);

        /* 如果是negative系统，添加频点进avoid列表中 */
        if (VOS_TRUE == ulIsNegSys)
        {
            if (VOS_TRUE == CNAS_XSD_IsAddInAvoidList(CNAS_XSD_AVOID_SID_NID_IS_REJ_BY_PRL))
            {
                CNAS_XSD_UpdataAvoidListInfo(&(stSysInfo.stFreq), CNAS_XSD_AVOID_SID_NID_IS_REJ_BY_PRL);
            }
        }
    }


    for (i = 0; i < pstSyncCnf->ulSyncFailFreqNum; i++)
    {
        if (CNAS_CAS_1X_SYS_SRCH_SYNC_FAIL_PROTO_MISMATCH != pstSyncCnf->astSyncRsltList[i].enFailReason)
        {
            continue;
        }

        /* 加入avoid列表前，检查slice是否已经到期 */
        stSysInfo.stFreq.enBandClass = pstSyncCnf->astSyncRsltList[i].stFreq.usBandClass;
        stSysInfo.stFreq.usChannel   = pstSyncCnf->astSyncRsltList[i].stFreq.usChannel;

        if (VOS_TRUE == CNAS_XSD_IsAddSyncFailFreqInAvoidList(&(stSysInfo.stFreq),
                                                              pstSyncCnf->astSyncRsltList[i].ulSlice,
                                                              CNAS_XSD_AVOID_P_REV_MISMATCH))
        {
            CNAS_XSD_UpdataAvoidListInfo(&(stSysInfo.stFreq), CNAS_XSD_AVOID_P_REV_MISMATCH);
        }

    }


    /*如果avoid列表中存在禁用标记，表示存在被禁用的频点，启动定时器 */
    if (VOS_TRUE == CNAS_XSD_IsExistAvoidFlagInAvoidlist())
    {
        /* 如果avoid timer未启动，启动avoid timer定时器 */
        if (CNAS_TIMER_STATUS_RUNNING != CNAS_GetSpecifiedTimerStatus(UEPS_PID_XSD,
                                                                      TI_CNAS_XSD_SLICE_REVERSE_PROTECT_TIMER,
                                                                      0))
        {
            CNAS_XSD_StartTimer(TI_CNAS_XSD_SLICE_REVERSE_PROTECT_TIMER,
                                TI_CNAS_XSD_SLICE_REVERSE_PROTECT_TIMER_LEN);
        }
    }

    CNAS_XSD_LogAvoidFreqList(CNAS_XSD_GetAvoidFreqListAddr());
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_PerformAbortProcedure_SysAcq
 功能描述  : 执行状态机打断流程
 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月14日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_PerformAbortProcedure_SysAcq(VOS_VOID)
{
    CNAS_XSD_StopTimer(TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER);

    /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
    CNAS_XSD_SndSysAcqRslt(CNAS_XSD_SYSTEM_ACQUIRED_RESULT_ABORTED,
                           CNAS_XSD_GetCurSysAcqScene_SysAcq(),
                           CNAS_XSD_IsImmediateSysAcq_SysAcq());

    /* 退出层二状态机 */
    CNAS_XSD_QuitFsmSysAcq_SysAcq();

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_SysAcq_WaitCasSysSyncCnf
 功能描述  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态收到ID_MMA_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月18日
    作    者   : c00299063
    修改内容   : 新生成函数

  2.日    期   : 2015年7月20日
    作    者   : h00313353
    修改内容   : 迭代17 紧急呼
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU            *pstCallRedialNtfMsg = VOS_NULL_PTR;
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32                       enCurScene;

    pstCallRedialNtfMsg = (MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU*)pstMsg;

    enCurScene = CNAS_XSD_GetCurSysAcqScene_SysAcq();

    /* 清除低优先级打断和之前打断的缓存消息 */
    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(VOS_PID_TIMER, TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(VOS_PID_TIMER, TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_END_EMC_CALLBACK_NTF);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_MO_CALL_END_NTF);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF);

    /* 若当前存在更高优先级的打断的缓存消息，忽略本消息 */
    if (0 != CNAS_XSD_GetCacheMsgNum())
    {
        return VOS_TRUE;
    }

    CNAS_XSD_SetAbortFlg_SysAcq(VOS_FALSE);

    /* 排除一些需要丢弃消息的场景 */
    /* 紧急呼处理 */
    if (NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_EMC_VOICE_CALL       == pstCallRedialNtfMsg->enCallType)
    {
        if (CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL           == enCurScene)
        {
            /* 当前已经在紧急呼叫重拨搜网，消息丢弃，不处理 */
            return VOS_TRUE;
        }
    }
    /* 普通呼和数据呼处理 */
    else
    {
        if ((CNAS_XSD_SYS_ACQ_SCENE_NORMAL_CALL_REDIAL      == enCurScene)
        ||  (CNAS_XSD_SYS_ACQ_SCENE_SWITCH_ON               == enCurScene))
        {
            /* 当前已经在呼叫重拨搜网，消息丢弃，不处理 */
            return VOS_TRUE;
        }
    }

    /* 若当前不存在更高优先级的缓存消息，进行新的打断 */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF);

    /* 其他搜网场景,设置状态机打断标记 */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    /* 缓存呼叫重拨指示消息 */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* 给CAS发送ID_CNAS_CAS_1X_STOP_SYSTEM_SYNC_REQ消息停止同步 */
    CNAS_XSD_SndCasStopSysSyncReq();

    /* 迁移到 CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF状态, 并启动保护定时器TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF, TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_SysAcq_WaitCasOhmInd
 功能描述  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND状态收到ID_MMA_XSD_CALL_REDIAL_NTF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月18日
    作    者   : c00299063
    修改内容   : 新生成函数

  2.日    期   : 2015年7月20日
    作    者   : h00313353
    修改内容   : 迭代17 紧急呼
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU           *pstCallRedialNtfMsg = VOS_NULL_PTR;
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32                      enCurScene;

    pstCallRedialNtfMsg = (MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU*)pstMsg;

    enCurScene = CNAS_XSD_GetCurSysAcqScene_SysAcq();

    /* 清除低优先级打断和自身的缓存消息 */
    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(VOS_PID_TIMER, TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(VOS_PID_TIMER, TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_END_EMC_CALLBACK_NTF);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_MO_CALL_END_NTF);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF);

    /* 若当前存在更高优先级的打断的缓存消息，忽略本消息 */
    if (0 != CNAS_XSD_GetCacheMsgNum())
    {
        return VOS_TRUE;
    }

    CNAS_XSD_SetAbortFlg_SysAcq(VOS_FALSE);

    /* 排除一些需要丢弃消息的场景 */
    /* 紧急呼处理 */
    if (NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_EMC_VOICE_CALL       == pstCallRedialNtfMsg->enCallType)
    {
        if (CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL           == enCurScene)
        {
            /* 当前已经在紧急呼叫重拨搜网，消息丢弃，不处理 */
            return VOS_TRUE;
        }
    }
    /* 普通呼和数据呼处理 */
    else
    {
        if ((CNAS_XSD_SYS_ACQ_SCENE_NORMAL_CALL_REDIAL      == enCurScene)
        ||  (CNAS_XSD_SYS_ACQ_SCENE_SWITCH_ON               == enCurScene))
        {
            /* 当前已经在呼叫重拨搜网，消息丢弃，不处理 */
            return VOS_TRUE;
        }
    }

    /* 若当前不存在更高优先级的缓存消息，进行新的打断 */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    /* 缓存呼叫重拨指示消息 */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_SysAcq_WaitCasStopSysSyncCnf
 功能描述  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF状态收到ID_MMA_XSD_CALL_REDIAL_NTF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月18日
    作    者   : c00299063
    修改内容   : 新生成函数

  2.日    期   : 2015年7月27日
    作    者   : h00313353
    修改内容   : 迭代17 紧急呼
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU           *pstCallRedialNtfMsg = VOS_NULL_PTR;
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32                      enCurScene;

    pstCallRedialNtfMsg = (MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU*)pstMsg;

    enCurScene = CNAS_XSD_GetCurSysAcqScene_SysAcq();

    /* 清除低优先级打断和自身的缓存消息 */
    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(VOS_PID_TIMER, TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(VOS_PID_TIMER, TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_END_EMC_CALLBACK_NTF);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_MO_CALL_END_NTF);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF);

    /* 若当前存在更高优先级的打断的缓存消息，忽略本消息 */
    if (0 != CNAS_XSD_GetCacheMsgNum())
    {
        return VOS_TRUE;
    }

    CNAS_XSD_SetAbortFlg_SysAcq(VOS_FALSE);

    /* 排除一些需要丢弃消息的场景 */
    /* 紧急呼处理 */
    if (NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_EMC_VOICE_CALL       == pstCallRedialNtfMsg->enCallType)
    {
        if (CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL           == enCurScene)
        {
            /* 当前已经在紧急呼叫重拨搜网，消息丢弃，不处理 */
            return VOS_TRUE;
        }
    }
    /* 普通呼和数据呼处理 */
    else
    {
        if ((CNAS_XSD_SYS_ACQ_SCENE_NORMAL_CALL_REDIAL      == enCurScene)
        ||  (CNAS_XSD_SYS_ACQ_SCENE_SWITCH_ON               == enCurScene))
        {
            /* 当前已经在呼叫重拨搜网，消息丢弃，不处理 */
            return VOS_TRUE;
        }
    }

    /* 若当前不存在更高优先级的缓存消息，进行新的打断 */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    /* 缓存呼叫重拨指示消息 */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    return VOS_TRUE;
}



/*****************************************************************************
 FUNCTION NAME    : CNAS_XSD_PerformAllowedSystemSelectionAfterSyncSucc_SysAcq
 DESCRIPTION      : perfrom system selection with acquire mode is allowed: need not to match the most prefered system in PRL
 INPUT PARAMETER  : pstSyncCnf  -- 同步确认消息
 OUTPUT PARAMETER : none
 RETURN           : none
 CALLING FUNCTION :
 CALLED FUNCTION  :

 History modification:
  1.DATE         : 21/8/2014
    EDITOR       : w00176964
    MODIFICATION : create
  2.日    期   : 2015年7月2日
    作    者   : w00242748
    修改内容   : CDMA 1X Iteration 17 modified
  3.日    期   : 2015年7月7日
    作    者   : y00245242
    修改内容   : iteration 17开发
*****************************************************************************/
VOS_VOID CNAS_XSD_PerformAllowedSystemSelectionAfterSyncSucc_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
)
{
    CNAS_PRL_FREQENCY_CHANNEL_STRU      astDstChan[CNAS_CAS_1X_MAX_FREQ_NUM];
    VOS_UINT16                          usCurScanListIndex;
    VOS_UINT16                          usDstChanNum;
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanList = VOS_NULL_PTR;
    CNAS_PRL_1X_SYSTEM_STRU             stCurSysInfo;
    VOS_UINT32                          ulIsNegSys;

    stCurSysInfo.stFreq.enBandClass = pstSyncCnf->stFreq.usBandClass;
    stCurSysInfo.stFreq.usChannel   = pstSyncCnf->stFreq.usChannel;
    stCurSysInfo.usNid              = pstSyncCnf->stSyncedSysId.usNid;
    stCurSysInfo.usSid              = pstSyncCnf->stSyncedSysId.usSid;

    ulIsNegSys = CNAS_XSD_IsCurSysNotSuitableSys(&stCurSysInfo, VOS_FALSE, 0);

    /* first check the system is allowed or not */
    if (VOS_TRUE == ulIsNegSys)
    {
        usCurScanListIndex = CNAS_XSD_GetCurChannelScanIndex();
        pstScanList        = CNAS_XSD_GetScanChanListAddr();

        usDstChanNum       = 0;
        NAS_MEM_SET_S(astDstChan, sizeof(astDstChan), 0x0, sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * CNAS_CAS_1X_MAX_FREQ_NUM);

        CNAS_XSD_GetNextScanChanList_SysAcq(usCurScanListIndex, &usDstChanNum, astDstChan, pstScanList);

        /* scan list已全部同步完 */
        if (0 == usDstChanNum)
        {
            CNAS_XSD_ProcScanListSyncComplete_SysAcq();
        }
        /* scan list未全部同步完，继续发同步请求 */
        else
        {
            CNAS_XSD_ContinueSyncScanList_SysAcq(usDstChanNum, astDstChan);
        }

        return;
    }

    /* 发送ID_CNAS_CAS_1X_CAMP_SYNCED_CHANNEL_NTF */
    CNAS_XSD_SndCas1xCampSyncedChannelNtf();

    /* 迁移到 CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND状态, 并启动保护定时器TI_CNAS_XSD_WAIT_CAS_OHM_IND */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND);

    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND, TI_CNAS_XSD_WAIT_CAS_OHM_IND_LEN);
}

/*****************************************************************************
 FUNCTION NAME    : CNAS_XSD_PerformAnySystemSelectionAfterSyncSucc_SysAcq
 DESCRIPTION      : perfrom system selection with acq mode is any: could camp on any system while synced successfull expect
                    the user settings
 INPUT PARAMETER  : pstSyncCnf  -- 同步确认消息
 OUTPUT PARAMETER : none
 RETURN           : none
 CALLING FUNCTION :
 CALLED FUNCTION  :

 History modification:
  1.DATE         : 12/1/2015
    EDITOR       : w00176964
    MODIFICATION : create

  2.日    期   : 2015年7月7日
    作    者   : y00245242
    修改内容   : iteration 17开发

  3.日    期   : 2015年7月20日
    作    者   : h00313353
    修改内容   : 迭代17 紧急呼

  4.日    期   : 2015年11月30日
    作    者   : h00313353
    修改内容   : DTS2015101200488
*****************************************************************************/
VOS_VOID CNAS_XSD_PerformAnySystemSelectionAfterSyncSucc_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
)
{
    CNAS_PRL_1X_SYSTEM_STRU            *pstEmcCallOrigSys   = VOS_NULL_PTR;
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32  enCurSysAcqScene;
    CNAS_PRL_1X_SYSTEM_STRU             stCurSysInfo;

    enCurSysAcqScene    = CNAS_XSD_GetCurSysAcqScene_SysAcq();
    NAS_MEM_SET_S(&stCurSysInfo, sizeof(stCurSysInfo), 0x00, sizeof(CNAS_PRL_1X_SYSTEM_STRU));

    if (CNAS_XSD_SYS_ACQ_SCENE_EMC_CALLBACK_SYSTEM_LOST == enCurSysAcqScene)
    {
        pstEmcCallOrigSys   = CNAS_XSD_GetEmcCallOriginalSys();

        if ((pstEmcCallOrigSys->usSid != pstSyncCnf->stSyncedSysId.usSid)
         || (pstEmcCallOrigSys->usNid != pstSyncCnf->stSyncedSysId.usNid))
        {
            CNAS_INFO_LOG4(UEPS_PID_XSD,
                           "CNAS_XSD_PerformAnySystemSelectionAfterSyncSucc_SysAcq:CallBack System Lost Srch Not Match(Req/Rsp):",
                           pstEmcCallOrigSys->usSid,
                           pstEmcCallOrigSys->usNid,
                           pstSyncCnf->stSyncedSysId.usSid,
                           pstSyncCnf->stSyncedSysId.usNid);

            /* 同步成功的系统不符合要求，继续Scan List同步 */
            CNAS_XSD_ContinueSysSync_SysAcq();

            return;
        }
    }

    /* 非紧急呼和紧急呼CallBack场景,若系统为Negative系统，继续同步ScanList剩余频点 */
    if (VOS_FALSE == CNAS_XSD_IsEmergencySysAcq_SysAcq(enCurSysAcqScene))
    {
        stCurSysInfo.stFreq.enBandClass = pstSyncCnf->stFreq.usBandClass;
        stCurSysInfo.stFreq.usChannel   = pstSyncCnf->stFreq.usChannel;
        stCurSysInfo.usNid              = pstSyncCnf->stSyncedSysId.usNid;
        stCurSysInfo.usSid              = pstSyncCnf->stSyncedSysId.usSid;

        if (VOS_TRUE == CNAS_XSD_IsCurSysNotSuitableSys(&stCurSysInfo,
                                                         VOS_FALSE,
                                                         0))
        {
            CNAS_XSD_ContinueSysSync_SysAcq();

            return;
        }
    }

    /* 发送ID_CNAS_CAS_1X_CAMP_SYNCED_CHANNEL_NTF */
    CNAS_XSD_SndCas1xCampSyncedChannelNtf();

    /* 迁移到 CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND状态, 并启动保护定时器TI_CNAS_XSD_WAIT_CAS_OHM_IND */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND);

    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND, TI_CNAS_XSD_WAIT_CAS_OHM_IND_LEN);

    return;
}

/*****************************************************************************
 FUNCTION NAME    : CNAS_XSD_PerformPreferedSystemSelectionAfterSyncSucc_SysAcq
 DESCRIPTION      : perfrom system selection with acq mode is prefered: in this case,
                    we have to find a perfered system in PRL
 INPUT PARAMETER  : pstSyncCnf  -- 同步确认消息
 OUTPUT PARAMETER : none
 RETURN           : none
 CALLING FUNCTION :
 CALLED FUNCTION  :

 History modification:
  1.DATE         : 12/1/2015
    EDITOR       : w00176964
    MODIFICATION : create
  2.日    期   : 2015年4月20日
    作    者   : w00242748
    修改内容   : DTS2015041609529:插入MRU0后，如果MRU0同步成功，但没办法驻留的
                 情况下会导致死循环搜网。
  3.日    期   : 2015年7月7日
    作    者   : y00245242
    修改内容   : iteration 17开发
*****************************************************************************/
VOS_VOID CNAS_XSD_PerformPreferedSystemSelectionAfterSyncSucc_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
)
{
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU stGeoListInfo;
    CNAS_PRL_FREQENCY_CHANNEL_STRU      astDstChan[CNAS_CAS_1X_MAX_FREQ_NUM];
    VOS_UINT16                          usCurScanListIndex;
    VOS_UINT16                          usDstChanNum;
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanList = VOS_NULL_PTR;
    VOS_UINT32                          ulIsNegSys;

    CNAS_PRL_1X_SYSTEM_STRU             stCurSysInfo;

    stCurSysInfo.stFreq.enBandClass = pstSyncCnf->stFreq.usBandClass;
    stCurSysInfo.stFreq.usChannel   = pstSyncCnf->stFreq.usChannel;
    stCurSysInfo.usNid              = pstSyncCnf->stSyncedSysId.usNid;
    stCurSysInfo.usSid              = pstSyncCnf->stSyncedSysId.usSid;


    ulIsNegSys = VOS_FALSE;

    NAS_MEM_SET_S(&stGeoListInfo, sizeof(stGeoListInfo), 0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));

    CNAS_PRL_Get1xSysGeoList(&stCurSysInfo, &stGeoListInfo);

    ulIsNegSys = CNAS_XSD_IsCurSysNotSuitableSys(&stCurSysInfo, VOS_FALSE, 0);

    /* negative system or not in PRL, could not select,should continue sync */
    if ((VOS_TRUE == ulIsNegSys)
     || (0        == stGeoListInfo.ucGeoNum))
    {
        usCurScanListIndex = CNAS_XSD_GetCurChannelScanIndex();
        pstScanList        = CNAS_XSD_GetScanChanListAddr();

        usDstChanNum       = 0;
        NAS_MEM_SET_S(astDstChan, sizeof(astDstChan), 0x0, sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * CNAS_CAS_1X_MAX_FREQ_NUM);
        CNAS_XSD_GetNextScanChanList_SysAcq(usCurScanListIndex,
                                            &usDstChanNum,
                                            astDstChan,
                                            pstScanList);

        /* scan list已全部同步完 */
        if (0 == usDstChanNum)
        {
            CNAS_XSD_ProcScanListSyncComplete_SysAcq();
        }
        /* scan list未全部同步完，继续发同步请求 */
        else
        {
            CNAS_XSD_ContinueSyncScanList_SysAcq(usDstChanNum, astDstChan);
        }

        return;
    }

    /* 发送ID_CNAS_CAS_1X_CAMP_SYNCED_CHANNEL_NTF */
    CNAS_XSD_SndCas1xCampSyncedChannelNtf();

    /* 迁移到 CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND状态, 并启动保护定时器TI_CNAS_XSD_WAIT_CAS_OHM_IND */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND);

    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND, TI_CNAS_XSD_WAIT_CAS_OHM_IND_LEN);
}

/*****************************************************************************
 FUNCTION NAME    : CNAS_XSD_PerformSpecificSystemSelectionAfterSyncSucc_SysAcq
 DESCRIPTION      : process system selection for which the SID/NID is known
 INPUT PARAMETER  : pstSyncCnf  -- 同步确认消息
 OUTPUT PARAMETER : none
 RETURN           : none
 CALLING FUNCTION :
 CALLED FUNCTION  :

 History modification:
  1.DATE         : 21/8/2014
    EDITOR       : y00245242
    MODIFICATION : create

  2.日    期   : 2015年7月7日
    作    者   : y00245242
    修改内容   : iteration 17开发
*****************************************************************************/
VOS_VOID CNAS_XSD_PerformSpecificSystemSelectionAfterSyncSucc_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
)
{
    CNAS_XSD_CFREQ_LOCK_SET_PARA_STRU  *pstFreqLockPara;
    VOS_UINT32                          ulRlst;

    /* 获取锁频信息 */
    pstFreqLockPara = CNAS_XSD_GetFreqLockAddr();

    ulRlst = CNAS_PRL_Is1xSysIdMatched(pstSyncCnf->stSyncedSysId.usSid,
                                       pstSyncCnf->stSyncedSysId.usNid,
                                       pstFreqLockPara->usSid,
                                       pstFreqLockPara->usNid);

    if (VOS_TRUE == ulRlst)
    {
        CNAS_XSD_SndCas1xCampSyncedChannelNtf();

        /* 迁移到 CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND状态, 并启动保护定时器TI_CNAS_XSD_WAIT_CAS_OHM_IND */
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND);

        CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND, TI_CNAS_XSD_WAIT_CAS_OHM_IND_LEN);
    }
    else
    {
        CNAS_XSD_ProcScanListSyncComplete_SysAcq();
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcCasSystemDetermineIndWithProtoMisReason_SysAcq
 功能描述  : process system determine indication message with protocol mismatch from CAS in system acquire state machine
 输入参数  : pstSysDeterminInd
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 29/12/2014
    作    者   : w00176964
    修改内容   : Create

  2.日    期   : 2015年7月17日
    作    者   : y00245242
    修改内容   : iteration 17开发
*****************************************************************************/
VOS_UINT32 CNAS_XSD_ProcCasSystemDetermineIndWithProtoMisReason_SysAcq(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd = VOS_NULL_PTR;

    pstSysDeterminInd   = (CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU *)pstMsg;

    CNAS_XSD_ProcRequiredAvoidedFreqByAvoidReason(CNAS_XSD_AVOID_P_REV_MISMATCH,
                                                  (CNAS_PRL_FREQENCY_CHANNEL_STRU *)(&(pstSysDeterminInd->stCurChannelInfo)));

    CNAS_XSD_SetRedirectionFlag(VOS_FALSE);

    /* continue sync */
    CNAS_XSD_ContinueSysSync_SysAcq();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_GetNextScanChanList_SysAcq
 功能描述  : 获取下一个要搜索的scan list
 输入参数  : usCurScanChanIndex----------当前扫描到的频点索引
             pstScanChanList------当前的扫描频点列表
 输出参数  : pusDstChanNum-----------获取到的频点个数
             pstDstChan--------------获取到的频点列表

 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月4日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2015年4月20日
    作    者   : w00242748
    修改内容   : DTS2015041609529:插入MRU0后，如果MRU0同步成功，但没办法驻留的
                 情况下会导致死循环搜网。
*****************************************************************************/
VOS_VOID CNAS_XSD_GetNextScanChanList_SysAcq(
    VOS_UINT16                          usCurScanChanIndex,
    VOS_UINT16                         *pusDstChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstDstChan,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32  enCurAcqScene;
    VOS_UINT32                          ulIsAvoidListEnable;

    enCurAcqScene       = CNAS_XSD_GetCurSysAcqScene_SysAcq();
    ulIsAvoidListEnable = VOS_TRUE;

    if ((CNAS_XSD_SYS_ACQ_SCENE_EMC_CALLBACK_SYSTEM_LOST == enCurAcqScene)
     || (CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL           == enCurAcqScene)
     || (CNAS_XSD_SYS_ACQ_SCENE_EMC_CALL_RELEASED        == enCurAcqScene))
    {
        ulIsAvoidListEnable = VOS_FALSE;
    }

    CNAS_XSD_GetNextScanChanList(usCurScanChanIndex,
                                 pusDstChanNum,
                                 pstDstChan,
                                 pstScanChanList,
                                 ulIsAvoidListEnable);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccSrvAcqReq_SysAcq_WaitCasSysSyncCnf
 功能描述  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态收到ID_MSCC_XSD_SRV_ACQ_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月02日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccSrvAcqReq_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 非紧急呼使用当前的搜网结果 */
    if (NAS_MSCC_PIF_SRV_TYPE_CS_MO_EMERGENCY_CALL != ((MSCC_XSD_SRV_ACQ_REQ_STRU *)pstMsg)->enSrvType)
    {
        return VOS_TRUE;
    }

    /* 清除低优先级打断的缓存消息 */
    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(VOS_PID_TIMER, TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(VOS_PID_TIMER, TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_END_EMC_CALLBACK_NTF);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_MO_CALL_END_NTF);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_SRV_ACQ_REQ);

    /* 若当前存在更高优先级的打断的缓存消息，忽略本消息 */
    if (0 != CNAS_XSD_GetCacheMsgNum())
    {
        return VOS_TRUE;
    }

    /* 如果业务类型是紧急呼，构建紧急呼搜网列表 */
    CNAS_XSD_BuildEmcCallRedialScanChanList();

    /* 若当前不存在更高优先级的缓存消息，进行新的打断 */
    /* 停止同步定时器 */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF);

    /* 发送停止同步请求 */
    CNAS_XSD_SndCasStopSysSyncReq();

    /* 缓存业务触发搜网请求 */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* 缓存中处理，清空业务触发搜网标记 */
    CNAS_XSD_SetSrvAcqFlg(VOS_FALSE);

    /* 设置状态机打断标记 */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    /* 迁状态设置保护定时器 */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF, TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccCallEndNtf_SysAcq_WaitCasSysSyncCnf
 功能描述  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态收到ID_MSCC_XSD_MO_CALL_END_NTF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月02日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccCallEndNtf_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32  enAcqScene;

    enAcqScene                          = CNAS_XSD_GetCurSysAcqScene_SysAcq();

    /* 非紧急呼搜网不打断 */
    if ((VOS_FALSE == CNAS_XSD_IsEmcSDSysAcq_SysAcq(enAcqScene))
     && (CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL != enAcqScene))
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == CNAS_XSD_GetAbortFlg_SysAcq())
    {
        return VOS_TRUE;
    }

    /* 紧急呼流程中，打断处理 */
    /* 停止同步定时器 */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF);

    /* 发送停止同步请求 */
    CNAS_XSD_SndCasStopSysSyncReq();

    /* 缓存业务触发搜网请求 */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* 设置状态机打断标记 */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    /* 迁状态设置保护定时器 */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF, TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvTiEmcCallBackNetWorkSrchTimerExpired_SysAcq_WaitCasSysSyncCnf
 功能描述  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态收到TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月02日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackNetWorkSrchTimerExpired_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_XSD_GetAbortFlg_SysAcq())
    {
        return VOS_TRUE;
    }

    /* 停止同步定时器 */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF);

    /* 发送停止同步请求 */
    CNAS_XSD_SndCasStopSysSyncReq();

    /* 缓存业务触发搜网请求 */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* 设置状态机打断标记 */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    /* 迁状态设置保护定时器 */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF, TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_SysAcq_WaitCasSysSyncCnf
 功能描述  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态收到TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月02日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_XSD_GetAbortFlg_SysAcq())
    {
        return VOS_TRUE;
    }

    /* 停止同步定时器 */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF);

    /* 发送停止同步请求 */
    CNAS_XSD_SndCasStopSysSyncReq();

    /* 缓存业务触发搜网请求 */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* 设置状态机打断标记 */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    /* 迁状态设置保护定时器 */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF, TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccEndEmcCallBackReq_SysAcq_WaitCasSysSyncCnf
 功能描述  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态收到ID_MSCC_XSD_END_EMC_CALLBACK_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月02日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccEndEmcCallBackReq_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_XSD_GetAbortFlg_SysAcq())
    {
        return VOS_TRUE;
    }

    /* 停止同步定时器 */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF);

    /* 发送停止同步请求 */
    CNAS_XSD_SndCasStopSysSyncReq();

    /* 缓存业务触发搜网请求 */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* 设置状态机打断标记 */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    /* 迁状态设置保护定时器 */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF, TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccSrvAcqReq_SysAcq_WaitCasStopSysSyncCnf
 功能描述  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF状态收到ID_MSCC_XSD_SRV_ACQ_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月02日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccSrvAcqReq_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 非紧急呼使用当前的搜网结果 */
    if (NAS_MSCC_PIF_SRV_TYPE_CS_MO_EMERGENCY_CALL != ((MSCC_XSD_SRV_ACQ_REQ_STRU *)pstMsg)->enSrvType)
    {
        return VOS_TRUE;
    }

    /* 清除低优先级打断的缓存消息 */
    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(VOS_PID_TIMER, TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(VOS_PID_TIMER, TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_END_EMC_CALLBACK_NTF);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_MO_CALL_END_NTF);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_SRV_ACQ_REQ);

    /* 若当前存在更高优先级的打断的缓存消息，忽略本消息 */
    if (0 != CNAS_XSD_GetCacheMsgNum())
    {
        return VOS_TRUE;
    }

    /* 如果业务类型是紧急呼，构建紧急呼搜网列表 */
    CNAS_XSD_BuildEmcCallRedialScanChanList();

    /* 若当前不存在更高优先级的缓存消息，进行新的打断 */
    /* 缓存业务触发搜网请求 */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* 缓存中处理消息，清空业务触发搜网标记 */
    CNAS_XSD_SetSrvAcqFlg(VOS_FALSE);

    /* 设置状态机打断标记 */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccCallEndNtf_SysAcq_WaitCasStopSysSyncCnf
 功能描述  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF状态收到ID_MSCC_XSD_MO_CALL_END_NTF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月02日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccCallEndNtf_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32  enAcqScene;

    enAcqScene                          = CNAS_XSD_GetCurSysAcqScene_SysAcq();

    /* 非紧急呼搜网不打断 */
    if ((VOS_FALSE == CNAS_XSD_IsEmcSDSysAcq_SysAcq(enAcqScene))
     && (CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL != enAcqScene))
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == CNAS_XSD_GetAbortFlg_SysAcq())
    {
        return VOS_TRUE;
    }

    /* 紧急呼流程中，打断处理 */
    /* 缓存业务触发搜网请求 */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* 设置状态机打断标记 */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvTiEmcCallBackNetWorkSrchTimerExpired_SysAcq_WaitCasStopSysSyncCnf
 功能描述  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF状态收到TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月02日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackNetWorkSrchTimerExpired_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_XSD_GetAbortFlg_SysAcq())
    {
        return VOS_TRUE;
    }

    /* 缓存业务触发搜网请求 */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* 设置状态机打断标记 */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_SysAcq_WaitCasStopSysSyncCnf
 功能描述  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF状态收到TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月02日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_XSD_GetAbortFlg_SysAcq())
    {
        return VOS_TRUE;
    }

    /* 缓存业务触发搜网请求 */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* 设置状态机打断标记 */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccEndEmcCallBackReq_SysAcq_WaitCasStopSysSyncCnf
 功能描述  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF状态收到ID_MSCC_XSD_END_EMC_CALLBACK_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月02日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccEndEmcCallBackReq_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_XSD_GetAbortFlg_SysAcq())
    {
        return VOS_TRUE;
    }

    /* 缓存业务触发搜网请求 */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* 设置状态机打断标记 */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccSrvAcqReq_SysAcq_WaitCasOhmInd
 功能描述  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND状态收到ID_MSCC_XSD_SRV_ACQ_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月02日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccSrvAcqReq_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 非紧急呼使用当前的搜网结果 */
    if (NAS_MSCC_PIF_SRV_TYPE_CS_MO_EMERGENCY_CALL != ((MSCC_XSD_SRV_ACQ_REQ_STRU *)pstMsg)->enSrvType)
    {
        return VOS_TRUE;
    }

    /* 清除低优先级打断的缓存消息 */
    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(VOS_PID_TIMER, TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(VOS_PID_TIMER, TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_END_EMC_CALLBACK_NTF);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_MO_CALL_END_NTF);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_SRV_ACQ_REQ);

    /* 若当前存在更高优先级的打断的缓存消息，忽略本消息 */
    if (0 != CNAS_XSD_GetCacheMsgNum())
    {
        return VOS_TRUE;
    }

    /* 如果业务类型是紧急呼，构建紧急呼搜网列表 */
    CNAS_XSD_BuildEmcCallRedialScanChanList();

    /* 若当前不存在更高优先级的缓存消息，进行新的打断 */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* 缓存中处理消息，清空业务触发搜网标记 */
    CNAS_XSD_SetSrvAcqFlg(VOS_FALSE);

    /* 设置状态机打断标记 */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccCallEndNtf_SysAcq_WaitCasOhmInd
 功能描述  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND状态收到ID_MSCC_XSD_MO_CALL_END_NTF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月02日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccCallEndNtf_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_PRL_1X_SYSTEM_ID_STRU         *pstLastSyncedSys       = VOS_NULL_PTR;
    CNAS_PRL_1X_SYSTEM_STRU             st1xSysInfo;
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32  enAcqScene;

    enAcqScene                          = CNAS_XSD_GetCurSysAcqScene_SysAcq();
    NAS_MEM_SET_S(&st1xSysInfo, sizeof(st1xSysInfo), 0x00, sizeof(CNAS_PRL_1X_SYSTEM_STRU));
    pstLastSyncedSys                    = CNAS_XSD_GetLastSyncedSys();

    /* 非紧急呼搜网不打断 */
    if ((VOS_FALSE == CNAS_XSD_IsEmcSDSysAcq_SysAcq(enAcqScene))
     && (CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL != enAcqScene))

    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == CNAS_XSD_GetAbortFlg_SysAcq())
    {
        return VOS_TRUE;
    }

    st1xSysInfo.usSid                   = pstLastSyncedSys->usSid;
    st1xSysInfo.usNid                   = pstLastSyncedSys->usNid;
    st1xSysInfo.stFreq                  = CNAS_XSD_GetHistorySyncedSysFreqList()->astFreq[0];

    /* 紧急呼流程中，打断处理 */
    /* 缓存业务触发搜网请求 */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* 若当前系统有效，延迟打断 */
    if (VOS_TRUE != CNAS_XSD_IsCurSysNotSuitableSys(&st1xSysInfo, VOS_FALSE, 0))
    {
        /* 设置状态机打断标记 */
        CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

        return VOS_TRUE;
    }

    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND);

    CNAS_XSD_SndSysAcqRslt(CNAS_XSD_SYSTEM_ACQUIRED_RESULT_ABORTED,
                           CNAS_XSD_GetCurSysAcqScene_SysAcq(),
                           CNAS_XSD_IsImmediateSysAcq_SysAcq());

    /* 退出层二状态机 */
    CNAS_XSD_QuitFsmSysAcq_SysAcq();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvTiEmcCallBackNetWorkSrchTimerExpired_SysAcq_WaitCasOhmInd
 功能描述  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND状态收到TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月02日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackNetWorkSrchTimerExpired_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_XSD_GetAbortFlg_SysAcq())
    {
        return VOS_TRUE;
    }

    /* 缓存业务触发搜网请求 */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* 设置状态机打断标记 */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_SysAcq_WaitCasOhmInd
 功能描述  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND状态收到TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月02日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_XSD_GetAbortFlg_SysAcq())
    {
        return VOS_TRUE;
    }

    /* 缓存业务触发搜网请求 */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* 设置状态机打断标记 */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RcvMsccEndEmcCallBackReq_SysAcq_WaitCasOhmInd
 功能描述  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND状态收到ID_MSCC_XSD_END_EMC_CALLBACK_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月02日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccEndEmcCallBackReq_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_XSD_GetAbortFlg_SysAcq())
    {
        return VOS_TRUE;
    }

    /* 缓存退出CallBack模式请求 */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* 设置状态机打断标记 */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_UpdateScanListChanStatusUponReceivedDeterminInd
 功能描述  : 收到determine ind后, 更新determine ind失败的频点
 输入参数  : usBeginScanListIndex -- 起始索引
             pstFreq              -- 需要刷新的频点
             pstScanChanList      -- 搜索列表
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年7月9日
   作    者   : y00245242
   修改内容   : iteration 17开发

 2.日    期   : 2015年09月09日
   作    者   : y00245242
   修改内容   : DTS2015090601618
*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateScanListChanStatusUponReceivedDeterminInd(
    VOS_UINT16                                              usBeginScanListIndex,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreq,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList
)
{
    VOS_UINT16                          usCurFreqIndex;

    usCurFreqIndex = usBeginScanListIndex;

    if (usCurFreqIndex > 0)
    {
        usCurFreqIndex--;
    }

    /* 如果不是OOC场景下的MRU0插入频点，从scan list当前索引开始查找，直到找到该频点刷新为同步不存在 */
    if (VOS_FALSE == CNAS_XSD_IsMru0FreqInOocScene(pstFreq))
    {
        CNAS_XSD_UpdateChanStatusInScanChanList(usCurFreqIndex,
                                                pstFreq,
                                                CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST,
                                                pstScanChanList);

        return;
    }

    /* 如果是OOC场景下的MRU0插入频点，只能从scan list起始位置0到当前索引查找，后续的频点不要刷新 */
    CNAS_XSD_UpdateFreqStatusBeforeCurIndexInScanChanList(CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST,
                                                          usCurFreqIndex,
                                                          pstFreq,
                                                          pstScanChanList);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_UpdateGeoSysRecordStatusUponReceivedDeterminInd
 功能描述  : 收到determine ind后, 更新GEO系统记录搜索状态
 输入参数  : pstFreq              -- 需要刷新的频点

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年7月9日
   作    者   : y00245242
   修改内容   : iteration 17开发
*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateGeoSysRecordStatusUponReceivedDeterminInd(
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreq
)
{
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList = VOS_NULL_PTR;

    pstGeoSysRecSrchList = CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq();

    /* TO DO: 这块的原因后续是否需要区分，遗留 */
    CNAS_XSD_UpdateSysFreqStatusByFreqChanInGeoSysRecordSrchList(pstFreq,
                                                                 CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST,
                                                                 pstGeoSysRecSrchList);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_IsCurGeoListSrchedInGeoListSrchInfo
 功能描述  : check当前GEO list在GEO list搜索信息是否已经搜索过
 输入参数  : pstGeoListInfo -- match的GEO list信息

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : y00245242
    修改内容   : iteration 17开发
*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsCurGeoListSrchedInGeoListSrchInfo(
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo
)
{
    CNAS_XSD_GEO_LIST_SRCH_INFO_STRU   *pstGeoListSrchInfo = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT32                          j;

    pstGeoListSrchInfo = CNAS_XSD_GetGeoSrchListInfoAddr();

    for (i = 0; i< pstGeoListInfo->ucGeoNum; i++)
    {
        for (j = 0; j < pstGeoListSrchInfo->usGeoNum; j++)
        {
            if (pstGeoListInfo->astGeoInfoList[i].usGeoFirstSysRecIndex == pstGeoListSrchInfo->pstGeoSrchInfo[j].usGeoBeginIndex)
            {
                /* 只要发现任何一个GEO未搜索过，都认为未搜索过 */
                if (VOS_FALSE == pstGeoListSrchInfo->pstGeoSrchInfo[j].usGeoSrchStatus)
                {
                    return VOS_FALSE;
                }
            }
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetMostMatched1xGeoList
 功能描述  : 获取最match的GEO list
 输入参数  : pstCurSysInfo ----当前系统信息

 输出参数  : pstMostMatchGeoListInfo ----最match的GEO list信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月9日
    作    者   : y00245242
    修改内容   : iteration 17开发
*****************************************************************************/
VOS_VOID CNAS_XSD_GetMostMatched1xGeoList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstMostMatchGeoListInfo
)
{
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                     stGeoListInfo;

    /* 获取所有匹配的GEO list */
    NAS_MEM_SET_S(&stGeoListInfo, sizeof(stGeoListInfo), 0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));

    CNAS_PRL_Get1xSysGeoList(pstCurSysInfo, &stGeoListInfo);

    /* 从GEO list中最match的GEO list */
    CNAS_PRL_GetAllMostMatched1xGeoFrom1xGeoList(pstCurSysInfo, &stGeoListInfo, pstMostMatchGeoListInfo);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ConstructGeoSysRecordSrchList
 功能描述  : 构造GEO搜索列表
 输入参数  : pstGeoListInfo----GEO list信息
             pstCurSysInfo ----当前系统信息

 输出参数  : pstSysAcqList ----捕获表list
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : y00245242
    修改内容   : iteration 17开发
  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XSD_ConstructGeoSysRecordSrchList(
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo,
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
)
{
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord        = VOS_NULL_PTR;
    VOS_UINT16                          usMorePrefSysNum;
    VOS_UINT16                          usMaxSysRecNum;
    VOS_UINT16                          usSysRecNum;
    VOS_UINT32                          i;

    usSysRecNum        = 0;
    usMorePrefSysNum = 0;
    usMaxSysRecNum     = 0;

    /* 计算所有GEO列表中包含的系统记录个数 */
    for (i = 0; i < pstGeoListInfo->ucGeoNum; i++)
    {
        usMaxSysRecNum += pstGeoListInfo->astGeoInfoList[i].usGeoSysRecNum;
    }

    /* 分配内存空间 */
    pstSysRecord = (CNAS_PRL_EXT_SYS_RECORD_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                                usMaxSysRecNum * sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU));

    if (VOS_NULL_PTR == pstSysRecord)
    {
        return;
    }

    CNAS_XSD_BuildCompsiteGeoFromMostMatchedGeoList(pstGeoListInfo,
                                                    &usSysRecNum,
                                                    pstSysRecord,
                                                    &usMorePrefSysNum);

    /* 构造系统捕获列表 */
    CNAS_XSD_BuildGeoSysRecordSrchList(pstCurSysInfo,
                                       usSysRecNum,
                                       pstSysRecord,
                                       pstGeoSysRecSrchList,
                                       usMorePrefSysNum);

    /* 记录本次GEO系统记录搜索列表中由哪些多少个GEO组成及他们的首个索引 */
    if (VOS_NULL_PTR != pstGeoSysRecSrchList->pstAcqSysInfo)
    {

        /* 当前搜索级别设置为GEO系统记录搜索列表中首个系统记录索引 */
        pstGeoSysRecSrchList->usCurSrchLevel            = pstGeoSysRecSrchList->pstAcqSysInfo[0].usLevel;

        pstGeoSysRecSrchList->stCurSyncGeoInfo.usGeoNum = pstGeoListInfo->ucGeoNum;

        for (i = 0; i < pstGeoListInfo->ucGeoNum; i++)
        {
            pstGeoSysRecSrchList->stCurSyncGeoInfo.ausGeoFirstIndex[i] = pstGeoListInfo->astGeoInfoList[i].usGeoFirstSysRecIndex;
        }
    }

    /* 需要释放CNAS_PRL_BuildGeoSysRecList中构造的system record */
    PS_MEM_FREE(UEPS_PID_XSD, pstSysRecord);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ContinueGeoSysRecordSrch
 功能描述  : 继续GEO系统记录列表中的频点搜索
 输入参数  : 无

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : y00245242
    修改内容   : iteration 17开发
*****************************************************************************/
VOS_VOID CNAS_XSD_ContinueGeoSysRecordSrch(VOS_VOID)
{
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanList = VOS_NULL_PTR;
    CNAS_PRL_FREQENCY_CHANNEL_STRU      astDstChan[CNAS_CAS_1X_MAX_FREQ_NUM];
    VOS_UINT16                          usDstChanNum;

    /*******************************************************************************************
     * 1. 继续GEO系统记录频点列表搜索
     ******************************************************************************************/
    usDstChanNum = 0;

    NAS_MEM_SET_S(&astDstChan[0], sizeof(astDstChan), 0, sizeof(astDstChan));

    CNAS_XSD_GetNextSysSyncListFromGeoSysRecordSrchList(CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq(),
                                                        &usDstChanNum,
                                                        &astDstChan[0]);

    if (0 != usDstChanNum)
    {
        /* 继续GEO系统记录频点同步操作 */
        CNAS_XSD_ContinueSyncScanList_SysAcq(usDstChanNum, &astDstChan[0]);

        return;
    }

    /*******************************************************************************************
     * 2. 清除GEO搜索列表状态以及释放GEO系统记录搜索列表内存
     ******************************************************************************************/
    /* 先清除GEO搜索列表状态 */
    CNAS_XSD_ClearGeoSrchListStatus();

    /* 释放GEO系统记录搜索列表的内存 */
    if (VOS_NULL_PTR != CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq()->pstAcqSysInfo)
    {
        PS_MEM_FREE(UEPS_PID_XSD, CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq()->pstAcqSysInfo);
        CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq()->pstAcqSysInfo = VOS_NULL_PTR;
    }

    /*******************************************************************************************
     * 3. 继续scan list频点列表搜索
     ******************************************************************************************/
    pstScanList        = CNAS_XSD_GetScanChanListAddr();

    CNAS_XSD_GetNextScanChanList_SysAcq(CNAS_XSD_GetCurChannelScanIndex(),
                                        &usDstChanNum,
                                        astDstChan,
                                        pstScanList);

    if (0 != usDstChanNum)
    {
        /* scan list未全部同步完，继续发同步请求 */
        CNAS_XSD_ContinueSyncScanList_SysAcq(usDstChanNum, astDstChan);

        return;
    }

    /*******************************************************************************************
     * 4. 处理scan list同步完成的后续流程
     ******************************************************************************************/
    /* scan list已全部同步完 */
    CNAS_XSD_ProcScanListSyncComplete_SysAcq();

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ContinueAvailSysListSrch
 功能描述  : 继续available系统列表搜索
 输入参数  : 无

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : y00245242
    修改内容   : iteration 17开发
*****************************************************************************/
VOS_VOID CNAS_XSD_ContinueAvailSysListSrch(VOS_VOID)
{
    CNAS_PRL_FREQENCY_CHANNEL_STRU      astDstChan[CNAS_CAS_1X_MAX_FREQ_NUM];
    VOS_UINT16                          usDstChanNum;

    usDstChanNum = 0;

    NAS_MEM_SET_S(&astDstChan[0], sizeof(astDstChan), 0, sizeof(astDstChan));

    /***********************************************************************************************
     * 1. 继续available list同步
     **********************************************************************************************/
    /* 获取下次同步available系统 */
    CNAS_XSD_GetNextAvailSysAcqList_SysAcq(&usDstChanNum, &astDstChan[0]);

    if (0 != usDstChanNum)
    {
        /* 继续available system list频点同步 */
        CNAS_XSD_ContinueSyncScanList_SysAcq(usDstChanNum, &astDstChan[0]);

        return;
    }

    /***********************************************************************************************
     * 2. available system list已没有需要同步的频点，退出L2状态机
     **********************************************************************************************/
    /* 退出状态机时清空available list */
    CNAS_XSD_InitAvailSysList(CNAS_XSD_INIT_CTX_STARTUP, CNAS_XSD_GetAvailSysFreqListAddr());

    /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
    CNAS_XSD_SndSysAcqRslt(CNAS_XSD_SYSTEM_ACQUIRED_RESULT_FAILURE,
                           CNAS_XSD_GetCurSysAcqScene_SysAcq(),
                           CNAS_XSD_IsImmediateSysAcq_SysAcq());

    /* 退出层二状态机 */
    CNAS_XSD_QuitFsmSysAcq_SysAcq();

}

/*****************************************************************************
 函 数 名  : CNAS_XSD_IsCurrSysMostPref1xSysInGeoSysRecordSrchList
 功能描述  : check当前系统是否是GEO系统记录搜索列表中最优先的系统

             注: 在调用该函数之前，需要check系统是否是negative系统，否则negative
                 系统可能会被选择!!!

 输入参数  : pstCurSysInfo        -- 同步到系统信息
             pstGeoSysRecSrchList -- GEO系统记录搜索列表

 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 是目前GEO中最优的系统
             VOS_FALSE -- 不是目前GEO中最优的系统
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : y00245242
    修改内容   : iteration 17开发
*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsCurrSysMostPref1xSysInGeoSysRecordSrchList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
)
{
    VOS_UINT16                          i;

    /***********************************************************************************************
     * 注: 该函数里面不需要再判断是否是negative系统了，因为在调用该函数前，已经判断了系统是否是
     *     negative系统。
     *     调用该函数前，必须提前check系统是否是negative系统，否则negative系统可能会被选择!!!
     **********************************************************************************************/

#if 0
    /* 当前系统的SID不在SID白名单中，则不认为是优先的系统 */
    if (VOS_FALSE == CNAS_XSD_IsSidInOperLockWhiteSidList(pstCurSysInfo->usSid))
    {
        return VOS_FALSE;
    }
#endif

    /* 如果当前同步到的系统与当前level中的系统匹配，则可以驻留 */
    for (i = 0; i < pstGeoSysRecSrchList->usTotalNum; i++ )
    {
        /* 跳过与当前同步的level不同的系统 */
        if (pstGeoSysRecSrchList->usCurSrchLevel != pstGeoSysRecSrchList->pstAcqSysInfo[i].usLevel)
        {
            continue;
        }

        /* 跳过同步不存在的频点 */
        if (CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST == pstGeoSysRecSrchList->pstAcqSysInfo[i].enSysStatus)
        {
            continue;
        }

        /* 跳过当前频点与系统SID/NID不匹配的系统 */
        if (VOS_FALSE == CNAS_PRL_Is1xSysMatched(pstCurSysInfo,
                                                 &(pstGeoSysRecSrchList->pstAcqSysInfo[i].stAcqSys)))
        {
            continue;
        }

#if 0
        /* 当前系统是优先的系统 */
        if (CNAS_PRL_PREF_NEG_SYS_PREF == pstGeoSysRecSrchList->pstAcqSysInfo[i].enPrefNegSys)
        {
            return VOS_TRUE;
        }

        /* 如果是negative系统，但在home SID/NID列表中，仍然当作是一个pref系统处理 */
        if (VOS_TRUE == CNAS_PRL_IsCurrentSystemInHomeSidNidList(pstCurSysInfo))
        {
            return VOS_TRUE;
        }
#endif

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_IsCurSysInGeoSysRecordSrchList
 功能描述  : check当前系统是否在GEO系统记录搜索列表中
 输入参数  : pstCurSysInfo -- 同步到系统信息
             pstSysAcqList -- GEO系统记录搜索列表

 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 是目前GEO中最优的系统
             VOS_FALSE -- 不是目前GEO中最优的系统
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : y00245242
    修改内容   : iteration 17开发
*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsCurSysInGeoSysRecordSrchList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
)
{
    VOS_UINT16                          i;

    for (i = 0; i < pstGeoSysRecSrchList->usTotalNum; i++ )
    {
        /* 跳过当前频点与系统SID/NID不匹配的系统 */
        if (VOS_TRUE == CNAS_PRL_Is1xSysMatched(pstCurSysInfo,
                                                &(pstGeoSysRecSrchList->pstAcqSysInfo[i].stAcqSys)))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_IsCurSysGeoListSameAsCurSyncGeoInfo
 功能描述  : check当前系统是否在GEO系统记录搜索列表中
 输入参数  : pstGeoListInfo -- 当前系统同步到的GEO信息
             pstSysAcqList  -- GEO系统记录搜索列表

 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 是目前GEO中最优的系统
             VOS_FALSE -- 不是目前GEO中最优的系统
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : y00245242
    修改内容   : iteration 17开发
*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsCurSysGeoListSameAsCurSyncGeoInfo(
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
)
{
    VOS_UINT32                          i;

    if (pstGeoListInfo->ucGeoNum != pstGeoSysRecSrchList->stCurSyncGeoInfo.usGeoNum)
    {
        return VOS_FALSE;
    }

    for (i = 0; i < pstGeoListInfo->ucGeoNum; i++)
    {
        if (pstGeoListInfo->astGeoInfoList[i].usGeoFirstSysRecIndex != pstGeoSysRecSrchList->stCurSyncGeoInfo.ausGeoFirstIndex[i])
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_PreformBestPreferedSystemSelectionAndNoGeoSysRecordSearchList_SysAcq
 功能描述  : 进行最优先的系统选择，且GEO系统记录搜索列表不存在
 输入参数  : pstSyncCnf----同步回复消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : y00245242
    修改内容   : iteration 17开发

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity
*****************************************************************************/
VOS_VOID CNAS_XSD_PreformBestPreferedSystemSelectionAndNoGeoSysRecordSearchList_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
)
{
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          astDstChan[CNAS_CAS_1X_MAX_FREQ_NUM];
    VOS_UINT16                                              usDstChanNum;
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                     stGeoListInfo;
    VOS_UINT16                                              usCurScanListIndex;
    CNAS_PRL_1X_SYSTEM_STRU                                 stCurSysInfo;
    VOS_UINT32                                              ulIsNegSys;
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanList = VOS_NULL_PTR;

    /***********************************************************************************************
     * 1. 刷新available系统下次搜索索引，并通知接入层驻留当前同步到的系统
     **********************************************************************************************/
    if (VOS_TRUE == CNAS_XSD_GetAvailSysAcqListFlg_SysAcq())
    {
        usCurScanListIndex = CNAS_XSD_GetAvailSysFreqListNextSrchIndex();

        /* 跳过失败的频点个数以及当前成功的频点个数 */
        CNAS_XSD_SetAvailSysFeqListNextSrchIndex((VOS_UINT8)(usCurScanListIndex + pstSyncCnf->ulSyncFailFreqNum + 1));

        /* 如果该系统在SID白名单中，则可以直接驻留 */
        if (VOS_TRUE == CNAS_XSD_IsSidInOperLockSysWhiteList(pstSyncCnf->stSyncedSysId.usSid))
        {
            /* 发送ID_CNAS_CAS_1X_CAMP_SYNCED_CHANNEL_NTF */
            CNAS_XSD_SndCas1xCampSyncedChannelNtf();

            /* 迁移到 CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND状态, 并启动保护定时器TI_CNAS_XSD_WAIT_CAS_OHM_IND */
            CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND);

            /* 启动保护定时器 */
            CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND, TI_CNAS_XSD_WAIT_CAS_OHM_IND_LEN);

            return;
        }

        /* 继续available系统搜索 */
        CNAS_XSD_ContinueAvailSysListSrch();

        return;
    }

    /***********************************************************************************************
     * 2. 当前系统在PRL表中处理
     **********************************************************************************************/
    stCurSysInfo.stFreq.enBandClass = pstSyncCnf->stFreq.usBandClass;
    stCurSysInfo.stFreq.usChannel   = pstSyncCnf->stFreq.usChannel;
    stCurSysInfo.usNid              = pstSyncCnf->stSyncedSysId.usNid;
    stCurSysInfo.usSid              = pstSyncCnf->stSyncedSysId.usSid;

    NAS_MEM_SET_S(&stGeoListInfo, sizeof(stGeoListInfo), 0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));

    CNAS_XSD_GetMostMatched1xGeoList(&stCurSysInfo, &stGeoListInfo);

    if (0 != stGeoListInfo.ucGeoNum)
    {

        ulIsNegSys = CNAS_XSD_IsCurSysNotSuitableSys(&stCurSysInfo, VOS_FALSE, 0);

        if (VOS_TRUE == ulIsNegSys)
        {
            CNAS_WARNING_LOG(UEPS_PID_XSD,
                             "CNAS_XSD_PreformBestPreferedSystemSelectionAndNoGeoSysRecordSearchList_SysAcq: Curr System is Neg!")
        }

        /* 使用一个新的GEO进行最优的系统选择 */
        CNAS_XSD_PeformBestPreferedSystemSelectionUsingNewGeo_SysAcq(&stGeoListInfo,
                                                                     &stCurSysInfo,
                                                                     ulIsNegSys);

        return;
    }

    /***********************************************************************************************
     * 3. 如果当前系统不在PRL表中，但系统是home系统，则捕获该系统
     **********************************************************************************************/
    if (VOS_TRUE == CNAS_XSD_IsCurSysHomeSystemIndependenceOnPrl(&stCurSysInfo))
    {
        /* 先提前通知上层服务状态 */
        CNAS_XSD_ReportSrvAvailableInd_SysAcq(&stCurSysInfo);

        /* 发送ID_CNAS_CAS_1X_CAMP_SYNCED_CHANNEL_NTF */
        CNAS_XSD_SndCas1xCampSyncedChannelNtf();

        /* 迁移到 CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND状态, 并启动保护定时器TI_CNAS_XSD_WAIT_CAS_OHM_IND */
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND);

        /* 启动保护定时器 */
        CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND, TI_CNAS_XSD_WAIT_CAS_OHM_IND_LEN);

        return;
    }

    /***********************************************************************************************
     * 4. 同步到的系统是available系统，这里把scan list中对应频点状态再次刷为不存在，避免后续会继续同步
     **********************************************************************************************/
    pstScanList = CNAS_XSD_GetScanChanListAddr();

    usCurScanListIndex = pstScanList->usCurScanIndex;

    CNAS_XSD_UpdateAvailOrNegSystemChanStatusInScanChanList_SysAcq((CNAS_PRL_FREQENCY_CHANNEL_STRU *)&(pstSyncCnf->stFreq),
                                                                   pstScanList);

    /***********************************************************************************************
     * 5. 如果当前系统是available系统，上报服务信息；同时刷新available list
     **********************************************************************************************/
    if (VOS_FALSE == CNAS_PRL_GetPrefOnlyFlg())
    {
        /* check当前available系统是否在白名单，在白名单中，则添加到available系统中，上报服务可用 */
        if (VOS_TRUE == CNAS_XSD_IsSidInOperLockSysWhiteList(pstSyncCnf->stSyncedSysId.usSid))
        {
             /* 通知服务可获得指示 */
            CNAS_XSD_ReportSrvAvailableInd_SysAcq(&stCurSysInfo);

            /* 刷新available list */
            CNAS_XSD_AddAvailSysFreqList(&(stCurSysInfo.stFreq));
        }
    }

    /***********************************************************************************************
     * 6. 继续scan list频点列表搜索
     **********************************************************************************************/
    usDstChanNum       = 0;

    NAS_MEM_SET_S(&astDstChan[0], sizeof(astDstChan), 0, sizeof(astDstChan));

    CNAS_XSD_GetNextScanChanList_SysAcq(usCurScanListIndex, &usDstChanNum, astDstChan, pstScanList);

    if (0 != usDstChanNum)
    {
        /* 继续scan list同步操作 */
        CNAS_XSD_ContinueSyncScanList_SysAcq(usDstChanNum, astDstChan);

        return;
    }

    /*******************************************************************************************
     * 7. 处理scan list同步完成的后续流程
     ******************************************************************************************/
    CNAS_XSD_ProcScanListSyncComplete_SysAcq();

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_PreformBestPreferedSystemSelectionAndGeoSysRecorSearchListExist_SysAcq
 功能描述  : 进行最优先的系统选择，且GEO系统记录搜索列表存在
 输入参数  : pstSyncCnf----同步回复消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : y00245242
    修改内容   : iteration 17开发

  2.日    期   : 2015年9月11日
    作    者   : y00245242
    修改内容   : DTS2015090601618
*****************************************************************************/
VOS_VOID CNAS_XSD_PreformBestPreferedSystemSelectionAndGeoSysRecordSearchListExist_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
)
{
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                     stGeoListInfo;
    CNAS_PRL_1X_SYSTEM_STRU                                 stCurSysInfo;
    VOS_UINT32                                              ulIsNegSys;
    CNAS_CAS_1X_SYNC_RSLT_INFO_STRU                         stSyncFailChan;
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList = VOS_NULL_PTR;

    /***********************************************************************************************
     * 1. 刷新GEO系统记录搜索列表
     *    注: negative系统不需要刷新scan list中的频点，因为negative系统已经在之前加到avoid列表中了，
     *        在下一次同步请求时，会被过滤掉
     **********************************************************************************************/
    stCurSysInfo.stFreq.enBandClass = pstSyncCnf->stFreq.usBandClass;
    stCurSysInfo.stFreq.usChannel   = pstSyncCnf->stFreq.usChannel;
    stCurSysInfo.usNid              = pstSyncCnf->stSyncedSysId.usNid;
    stCurSysInfo.usSid              = pstSyncCnf->stSyncedSysId.usSid;

    ulIsNegSys = CNAS_XSD_IsCurSysNotSuitableSys(&stCurSysInfo, VOS_FALSE, 0);

    if (VOS_FALSE == ulIsNegSys)
    {
        /* 刷新当前同步成功的频点状态，GEO中系统记录搜索列表中最match的系统频点刷新为搜索存在，其他为搜索不存在 */
        CNAS_XSD_UpdateSyncSuccFreqStatusInGeoSysRecordSrchList_SysAcq(&(pstSyncCnf->stFreq),
                                                                       &(pstSyncCnf->stSyncedSysId));
    }
    else
    {
        stSyncFailChan.stFreq.usBandClass = pstSyncCnf->stFreq.usBandClass;
        stSyncFailChan.stFreq.usChannel   = pstSyncCnf->stFreq.usChannel;

        /* 当前系统是negative系统，刷新状态为搜索不存在 */
        CNAS_XSD_UpdateSyncFailFreqStatusInGeoSysRecordSrchList_SysAcq(1, &stSyncFailChan);

        /* 当该系统是neg时，需刷新该频点为不存在，如果不刷新的话，继续同步仍然会同步该频点
           获取下一个同步频点时的逻辑为未同步或者同步存在 */
        CNAS_XSD_UpdateAvailOrNegSystemChanStatusInScanChanList_SysAcq(&stCurSysInfo.stFreq,
                                                                       CNAS_XSD_GetScanChanListAddr());
    }

    /* 刷新当前同步失败的频点 */
    CNAS_XSD_UpdateSyncFailFreqStatusInGeoSysRecordSrchList_SysAcq((VOS_UINT16)pstSyncCnf->ulSyncFailFreqNum,
                                                                   &(pstSyncCnf->astSyncRsltList[0]));

    /***********************************************************************************************
     * 2. 当前系统在PRL表中处理
     **********************************************************************************************/
    NAS_MEM_SET_S(&stGeoListInfo, sizeof(stGeoListInfo), 0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));

    CNAS_XSD_GetMostMatched1xGeoList(&stCurSysInfo, &stGeoListInfo);

    if (0 != stGeoListInfo.ucGeoNum)
    {
        /***********************************************************************************************
         * 1.1. 当前系统在GEO系统搜索列表中处理
         **********************************************************************************************/
        pstGeoSysRecSrchList = CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq();

        if (VOS_TRUE == CNAS_XSD_IsCurSysInGeoSysRecordSrchList(&stCurSysInfo, pstGeoSysRecSrchList))
        {
            /***************************************************************************************
             * i 当前系统可以直接驻留处理
             **************************************************************************************/
            /* 根据scan list里列表中的频点状态，刷新GEO系统记录搜索列表中的频点状态及下次搜索索引 */
            CNAS_XSD_UpdateGeoSysRecordListInfoAccordingToScanChanList(pstGeoSysRecSrchList);

            /* 当前系统是高优先级系统 */
            if (VOS_TRUE == CNAS_XSD_IsCurrSysMostPref1xSysInGeoSysRecordSrchList(&stCurSysInfo, pstGeoSysRecSrchList))
            {
                /* 先提前通知上层服务状态 */
                CNAS_XSD_ReportSrvAvailableInd_SysAcq(&stCurSysInfo);

                /* 发送ID_CNAS_CAS_1X_CAMP_SYNCED_CHANNEL_NTF */
                CNAS_XSD_SndCas1xCampSyncedChannelNtf();

                /* 迁移到 CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND状态, 并启动保护定时器TI_CNAS_XSD_WAIT_CAS_OHM_IND */
                CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND);

                /* 启动保护定时器 */
                CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND, TI_CNAS_XSD_WAIT_CAS_OHM_IND_LEN);

                return;
            }

            /***************************************************************************************
             * ii 继续GEO系统记录搜索列表搜索
             **************************************************************************************/
            CNAS_XSD_ContinueGeoSysRecordSrch();
            return;
        }

        /*******************************************************************************************
         * 1.2 当前同步到的系统是GEO系统搜索列表中的低优先级系统, 继续GEO系统记录搜索列表搜索
         *     注: GEO系统记录搜索列表在构造时，仅存放了当前同步到系统以及在GEO中比它优先级高的系统，
                   低优先级系统并没有放到GEO系统搜索列表中。因此在判断当前系统是否是GEO系统记录搜索
                   列表中的低优先级系统，原则如下:
                   1. 当前同步到的系统不在GEO系统记录搜索列表中；且
                   2. 当前同步到的系统在PRL表中的GEO与当前正在同步的GEO信息一致
                   满足上述条件，则认为是GEO中低优先级系统，程序将继续当前的GEO系统记录搜索列表中高
                   优先频点同步
         *******************************************************************************************/
        if (VOS_TRUE == CNAS_XSD_IsCurSysGeoListSameAsCurSyncGeoInfo(&stGeoListInfo, pstGeoSysRecSrchList))
        {
            CNAS_XSD_ContinueGeoSysRecordSrch();

            return;
        }

        /*******************************************************************************************
         * 1.3 当前系统是新的GEO，且已经搜索过,处理如下:
         *     i)  如果是negative系统，则当前继续GEO搜索，否则
         *     ii) 直接驻留当前系统
         *******************************************************************************************/
        /* 如果这是个新的GEO，且新的GEO已经搜索过，直接驻留当前系统，避免程序死循环 */
        if (VOS_TRUE == CNAS_XSD_IsCurGeoListSrchedInGeoListSrchInfo(&stGeoListInfo))
        {
            if (VOS_TRUE == ulIsNegSys)
            {
                CNAS_XSD_ContinueGeoSysRecordSrch();

                return;
            }

            /* 先提前通知上层服务状态 */
            CNAS_XSD_ReportSrvAvailableInd_SysAcq(&stCurSysInfo);

            /* 发送ID_CNAS_CAS_1X_CAMP_SYNCED_CHANNEL_NTF */
            CNAS_XSD_SndCas1xCampSyncedChannelNtf();

            /* 迁移到 CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND状态, 并启动保护定时器TI_CNAS_XSD_WAIT_CAS_OHM_IND */
            CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND);

            /* 启动保护定时器 */
            CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND, TI_CNAS_XSD_WAIT_CAS_OHM_IND_LEN);

            return;
        }

        /*******************************************************************************************
         * 1.4. 这是未搜索过的新的GEO，释放老的GEO系统记录搜索列表，继续新的GEO进行系统选择
         ******************************************************************************************/
        /* 释放当前的GEO系统记录搜索列表 */
        PS_MEM_FREE(UEPS_PID_XSD, pstGeoSysRecSrchList->pstAcqSysInfo);
        pstGeoSysRecSrchList->pstAcqSysInfo = VOS_NULL_PTR;

        /* 使用一个新的GEO进行最优的系统选择 */
        CNAS_XSD_PeformBestPreferedSystemSelectionUsingNewGeo_SysAcq(&stGeoListInfo,
                                                                     &stCurSysInfo,
                                                                     ulIsNegSys);

        return;
    }

    /***********************************************************************************************
     * 3. 如果当前系统不在PRL表中，但系统是home系统，则捕获该系统
     **********************************************************************************************/
    if (VOS_TRUE == CNAS_XSD_IsCurSysHomeSystemIndependenceOnPrl(&stCurSysInfo))
    {
        /* 先提前通知上层服务状态 */
        CNAS_XSD_ReportSrvAvailableInd_SysAcq(&stCurSysInfo);

        /* 发送ID_CNAS_CAS_1X_CAMP_SYNCED_CHANNEL_NTF */
        CNAS_XSD_SndCas1xCampSyncedChannelNtf();

        /* 迁移到 CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND状态, 并启动保护定时器TI_CNAS_XSD_WAIT_CAS_OHM_IND */
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND);

        /* 启动保护定时器 */
        CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND, TI_CNAS_XSD_WAIT_CAS_OHM_IND_LEN);

        return;
    }

    /***********************************************************************************************
     * 4. 同步到的系统是available系统，这里把scan list中对应频点状态再次刷为不存在
     **********************************************************************************************/
    CNAS_XSD_UpdateAvailOrNegSystemChanStatusInScanChanList_SysAcq(&stCurSysInfo.stFreq,
                                                                   CNAS_XSD_GetScanChanListAddr());

    /***********************************************************************************************
     * 5. 如果当前系统是available系统，上报服务信息；同时刷新available list
     **********************************************************************************************/
    if (VOS_FALSE == CNAS_PRL_GetPrefOnlyFlg())
    {
        /* check当前available系统是否在白名单，在白名单中，则添加到available系统中，上报服务可用 */
        if (VOS_TRUE == CNAS_XSD_IsSidInOperLockSysWhiteList(pstSyncCnf->stSyncedSysId.usSid))
        {
            /* 先提前通知上层服务状态 */
            CNAS_XSD_ReportSrvAvailableInd_SysAcq(&stCurSysInfo);

            /* 刷新available list */
            CNAS_XSD_AddAvailSysFreqList(&(stCurSysInfo.stFreq));
        }
    }

    /***********************************************************************************************
     * 6. 继续GEO系统记录搜索列表搜索
     **********************************************************************************************/
    CNAS_XSD_ContinueGeoSysRecordSrch();

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcSyncFailAndNoGeoSysRecorSearchList_SysAcq
 功能描述  : 收到CAS的同步回复失败，且无GEO系统记录搜索list
 输入参数  : pstSyncCnf -- 系统同步结果
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : y00245242
    修改内容   : iteration 17开发
*****************************************************************************/
VOS_VOID CNAS_XSD_ProcSyncFailAndNoGeoSysRecorSearchList_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
)
{
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanList = VOS_NULL_PTR;
    CNAS_PRL_FREQENCY_CHANNEL_STRU      astDstChan[CNAS_CAS_1X_MAX_FREQ_NUM];
    VOS_UINT16                          usCurScanListIndex;
    VOS_UINT16                          usDstChanNum;

    /***********************************************************************************************
     * 1. 继续available系统频点同步
     **********************************************************************************************/
    if (VOS_TRUE == CNAS_XSD_GetAvailSysAcqListFlg_SysAcq())
    {
        /* 更新available系统下次搜索索引 */
        usCurScanListIndex = CNAS_XSD_GetAvailSysFreqListNextSrchIndex();

        CNAS_XSD_SetAvailSysFeqListNextSrchIndex((VOS_UINT8)(usCurScanListIndex + pstSyncCnf->ulSyncFailFreqNum));

        CNAS_XSD_ContinueAvailSysListSrch();

        return;
    }

    /*******************************************************************************************
     * 2. 继续scan list同步
     ******************************************************************************************/
    usDstChanNum       = 0;

    NAS_MEM_SET_S(&astDstChan[0], sizeof(astDstChan), 0, sizeof(astDstChan));

    pstScanList = CNAS_XSD_GetScanChanListAddr();

    CNAS_XSD_GetNextScanChanList_SysAcq(CNAS_XSD_GetCurChannelScanIndex(),
                                        &usDstChanNum,
                                        astDstChan,
                                        pstScanList);

    if (0 != usDstChanNum)
    {
        /* scan list未全部同步完，继续发同步请求 */
        CNAS_XSD_ContinueSyncScanList_SysAcq(usDstChanNum, astDstChan);

        return;
    }

    /*******************************************************************************************
     * 3. 继续scan list同步完的后续处理流程
     ******************************************************************************************/
    /* scan list已全部同步完 */
    CNAS_XSD_ProcScanListSyncComplete_SysAcq();

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ReportSrvAvailableInd_SysAcq
 功能描述  : 上报服务状态获得指示
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : y00245242
    修改内容   : iteration 17开发
*****************************************************************************/
VOS_VOID CNAS_XSD_ReportSrvAvailableInd_SysAcq(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo
)
{
    XSD_MSCC_SYNC_SERVICE_AVAILABLE_IND_STRU                stSrvAvailableInd;
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32                 enServiceStatus;
    CNAS_XSD_SERVICE_STATUS_ENUM_UINT32                     enXsdCurSrvStatus;
    CNAS_CCB_CARD_STATUS_ENUM_UINT8                         enCardStatus;

    /* 当前服务状态就是normal service，则不需要上报服务状态 */
    if (CNAS_XSD_SERVICE_STATUS_NORMAL_SERVICE == CNAS_XSD_GetCurSrvStatus())
    {
        return;
    }

    enCardStatus = CNAS_CCB_GetCsimCardStatus();

    if ( CNAS_CCB_CARD_STATUS_ABSENT == enCardStatus )
    {
        enXsdCurSrvStatus = CNAS_XSD_SERVICE_STATUS_LIMITED_SERVICE;
        enServiceStatus   = NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE;
    }
    else
    {
        enXsdCurSrvStatus = CNAS_XSD_SERVICE_STATUS_NORMAL_SERVICE;
        enServiceStatus   = NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE;
    }

    /* 更新当前的服务状态为normal service */
    CNAS_XSD_SetCurSrvStatus(enXsdCurSrvStatus);

    NAS_MEM_SET_S(&stSrvAvailableInd, sizeof(stSrvAvailableInd), 0, sizeof(XSD_MSCC_SYNC_SERVICE_AVAILABLE_IND_STRU));

    stSrvAvailableInd.usFreq          = pstCurSysInfo->stFreq.usChannel;
    stSrvAvailableInd.usBandClass     = pstCurSysInfo->stFreq.enBandClass;
    stSrvAvailableInd.usNid           = pstCurSysInfo->usNid;
    stSrvAvailableInd.usSid           = pstCurSysInfo->usSid;
    stSrvAvailableInd.enServiceStatus = enServiceStatus;
    stSrvAvailableInd.ucRoamingInd    = CNAS_XSD_GetCurrentSystemRoamingInd(pstCurSysInfo);

    CNAS_XSD_SndMsccSyncServiceAvailableInd(&stSrvAvailableInd);
    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_IsCallRelAnyCampOnFreq_SysAcq
 功能描述  : 上报服务状态获得指示
 输入参数  : pstFreq -- 当前同步成功的频点
 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 是首次同步的频点
             VOS_FALSE -- 非首次同步的频点
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : y00245242
    修改内容   : iteration 17开发
*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsCallRelAnyCampOnFreq_SysAcq(
    CNAS_CAS_1X_FREQENCY_CHANNEL_STRU                      *pstFreq
)
{
    CNAS_XSD_CALL_REL_ANY_CAMP_ON_FREQ_STRU                *pstCallRelAnyCampOnFreq = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    pstCallRelAnyCampOnFreq = CNAS_XSD_GetCallRelAnyCampOnFreqListAddr();

    for (i = 0; i < (VOS_UINT32)CNAS_MIN(pstCallRelAnyCampOnFreq->usChanNum, CNAS_XSD_CALL_REL_SYNC_MAX_FREQ_NUM); i++)
    {
        if ((pstFreq->usBandClass == pstCallRelAnyCampOnFreq->astFreq[i].enBandClass)
         && (pstFreq->usChannel   == pstCallRelAnyCampOnFreq->astFreq[i].usChannel))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_UpdateSyncSuccChanStatus_SysAcq
 功能描述  : 更新扫描成功的频点状态
 输入参数  : VOS_UINT16                                     usBeginScanListIndex
             CNAS_PRL_FREQENCY_CHANNEL_STRU                *pstChannel
             CNAS_XSD_SCAN_CHANNEL_LIST_STRU               *pstScanChanList
             CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU        *pstGeoSysRecSrchList
 输出参数  : 无
 返 回 值  : VOS_UINT16 -- 返回当前同步成功的频点在scan list中的索引
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月8日
    作    者   : y00245242
    修改内容   : DTS2015090601618
*****************************************************************************/
VOS_UINT16 CNAS_XSD_UpdateSyncSuccChanStatus_SysAcq(
    VOS_UINT16                                              usBeginScanListIndex,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstChannel,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
)
{
    VOS_UINT16                                              usCurFreqIndex;

    /***********************************************************************************************
       同步成功的频点处理：
       i） 如果是GEO同步，如果是OOC场景下的MRU0插入频点，则不刷新；否则需要从scan list当前索引往后
           刷新该频点；

       ii）如果不是GEO同步，则从scan list当前索引往后查找刷新该频点
     **********************************************************************************************/

    usCurFreqIndex = usBeginScanListIndex;

    if (VOS_NULL_PTR != pstGeoSysRecSrchList->pstAcqSysInfo)
    {
        if (VOS_TRUE == CNAS_XSD_IsMru0FreqInOocScene(pstChannel))
        {
            return usCurFreqIndex;
        }
    }

    usCurFreqIndex = CNAS_XSD_UpdateChanStatusInScanChanList(usBeginScanListIndex,
                                                             pstChannel,
                                                             CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_EXIST,
                                                             pstScanChanList);

    return usCurFreqIndex;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_UpdateSyncFailChanStatus_SysAcq
 功能描述  : 更新扫描失败的频点状态
 输入参数  : usBeginScanListIndex ------------开始搜索频点的index
             usSyncFailChanNum ---------------同步失败的频点个数
             pstSyncFailChanList ------------ 同步失败的频点列表
             pstScanChanList -----------------当前的频点扫描列表
             pstGeoSysRecSrchList-------------GEO场景下的搜索列表信息地址
 输出参数  : 无
 返 回 值  : VOS_UINT16 -- 返回当前刷新的最后一个失败频点在scan list中的索引
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年9月9日
   作    者   : y00245242
   修改内容   : DTS2015090601618
*****************************************************************************/
VOS_UINT16 CNAS_XSD_UpdateSyncFailChanStatus_SysAcq(
    VOS_UINT16                                              usBeginScanListIndex,
    VOS_UINT16                                              usSyncFailChanNum,
    CNAS_CAS_1X_SYNC_RSLT_INFO_STRU                        *pstSyncFailChanList,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
)
{
    VOS_UINT16                                              i;
    VOS_UINT16                                              usCurFreqIndex;
    CNAS_PRL_1X_SYSTEM_STRU                                 stMru0SysId;
    VOS_UINT16                                              ulMru0FreqIndex;


    /***********************************************************************************************
       a. 同步失败的频点处理：
          i)  如果是GEO同步，如果不是MRU0插入频点，则需要从scan list当前索引往后刷新失败的频点；否
              则需要从scan list头部到当前索引查找所有MRU0频点刷新为同步不存在，确保状态一致性；
          ii）如果不是GEO同步，从scan list当前索引往后查找刷新失败的频点；
     **********************************************************************************************/

    usCurFreqIndex = usBeginScanListIndex;

    /* GEO同步场景 */
    if (VOS_NULL_PTR != pstGeoSysRecSrchList->pstAcqSysInfo)
    {
        ulMru0FreqIndex = CNAS_XSD_INVAILD_SCAN_LIST_FREQ_INDEX;

        /* 如果不是OOC场景，或没有MRU0频点插入场景 */
        if (VOS_FALSE == CNAS_XSD_IsOocSceneAndRepeatMru0FreqSrchExist(&stMru0SysId))
        {
            ulMru0FreqIndex = CNAS_XSD_INVAILD_SCAN_LIST_FREQ_INDEX;
        }
        else
        {
            /* check同步结果中是否有MRU0频点存在 */
            for (i = 0; i < usSyncFailChanNum; i++)
            {
                if ((stMru0SysId.stFreq.enBandClass == pstSyncFailChanList[i].stFreq.usBandClass)
                 && (stMru0SysId.stFreq.usChannel   == pstSyncFailChanList[i].stFreq.usChannel))
                {
                    ulMru0FreqIndex = i;

                    break;
                }
            }
        }

        if (0xFFFF == ulMru0FreqIndex)
        {
            /* 不是OOC场景下的MRU0频点，从scan list当前索引往后查找刷新失败的频点； */
            usCurFreqIndex = CNAS_XSD_UpdateSyncFailChanStatus(usBeginScanListIndex,
                                                               usSyncFailChanNum,
                                                               pstSyncFailChanList,
                                                               pstScanChanList);

            return usCurFreqIndex;
        }

        for (i = 0; i < usSyncFailChanNum; i++)
        {
            /* 跳过MRU0的频点, 不刷新MRU0频点 */
            if (i == ulMru0FreqIndex)
            {
                continue;
            }

            usCurFreqIndex =
                CNAS_XSD_UpdateChanStatusInScanChanList(usBeginScanListIndex,
                                                        (CNAS_PRL_FREQENCY_CHANNEL_STRU *)&pstSyncFailChanList[i].stFreq,
                                                        CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST,
                                                        pstScanChanList);
        }

        /* 对于MRU0的频点，需要从scan list头部到当前索引查找所有MRU0频点刷新为同步不存在，确保状态一致性； */
        CNAS_XSD_UpdateFreqStatusBeforeCurIndexInScanChanList(CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST,
                                                              usBeginScanListIndex,
                                                              &(stMru0SysId.stFreq),
                                                              pstScanChanList);

        return usCurFreqIndex;
    }

    /* 这里只刷新同步存在的或未同步的频点频点状态为同步不存在 */
    for (i = 0; i < usSyncFailChanNum; i++)
    {
        usCurFreqIndex =
            CNAS_XSD_UpdateNoSyncedOrSyncSuccScanChanInScanChanList(CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST,
                                                                    usBeginScanListIndex,
                                                                    (CNAS_PRL_FREQENCY_CHANNEL_STRU *)&(pstSyncFailChanList[i].stFreq),
                                                                    pstScanChanList);

    }

    return usCurFreqIndex;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_UpdateChanStatusUponRcvCasSyncCnfSucc_SysAcq
 功能描述  : 收到CAS同步成功时，更新频点状态
 输入参数  : pstSyncCnf -- 同步成功的确认消息

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年9月9日
   作    者   : y00245242
   修改内容   : DTS2015090601618
*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateChanStatusUponRcvCasSyncCnfSucc_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
)
{
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList = VOS_NULL_PTR;
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanList          = VOS_NULL_PTR;
    VOS_UINT16                                              usCurScanListIndex;
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstEmcScanChanList   = VOS_NULL_PTR;

    pstEmcScanChanList                  = CNAS_XSD_GetEmcCallRedialScanChanListAddr();

    /***********************************************************************************************
     * 1. 如果是available系统同步，则不对scan list做操作；
     **********************************************************************************************/
    if (VOS_TRUE == CNAS_XSD_GetAvailSysAcqListFlg_SysAcq())
    {
        return;
    }

    pstScanList          = CNAS_XSD_GetScanChanListAddr();

    pstGeoSysRecSrchList = CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq();

    /***********************************************************************************************
     * 2. 同步失败的频点处理
     **********************************************************************************************/
    if (0 != pstSyncCnf->ulSyncFailFreqNum)
    {
        /* 处理同步失败的频点刷新 */
        usCurScanListIndex = CNAS_XSD_UpdateSyncFailChanStatus_SysAcq(pstScanList->usCurScanIndex,
                                                                      (VOS_UINT16)pstSyncCnf->ulSyncFailFreqNum,
                                                                      &pstSyncCnf->astSyncRsltList[0],
                                                                      pstScanList,
                                                                      pstGeoSysRecSrchList);

        /* GEO不存在时，更新当前scan list搜索索引，加快同步成功频点的刷新 */
        if (VOS_NULL_PTR == pstGeoSysRecSrchList->pstAcqSysInfo)
        {
            CNAS_XSD_SetCurChannelScanIndex(usCurScanListIndex + 1);
        }

        /* 紧急场景的SD搜网，刷新紧急呼的频点列表，避免后续重复搜同步失败的频点 */
        if (VOS_NULL_PTR != pstEmcScanChanList->pstScanChanInfo)
        {
            if (VOS_TRUE == CNAS_XSD_IsEmcSDSysAcq_SysAcq(CNAS_XSD_GetCurSysAcqScene_SysAcq()))
            {
                (VOS_VOID)CNAS_XSD_UpdateSyncFailChanStatus(pstEmcScanChanList->usCurScanIndex,
                                                           (VOS_UINT16)pstSyncCnf->ulSyncFailFreqNum,
                                                            pstSyncCnf->astSyncRsltList,
                                                            pstEmcScanChanList);
            }
        }
    }

    /***********************************************************************************************
     * 3. 同步成功的频点处理
     **********************************************************************************************/
    usCurScanListIndex = CNAS_XSD_UpdateSyncSuccChanStatus_SysAcq(pstScanList->usCurScanIndex,
                                                                  (CNAS_PRL_FREQENCY_CHANNEL_STRU *)&(pstSyncCnf->stFreq),
                                                                  pstScanList,
                                                                  pstGeoSysRecSrchList);

    /***********************************************************************************************
     * 4. 如果不是GEO同步，且同步成功的频点是插入的MRU0频点；则从scan list头部到当前索引（即指向scan
     *    list中本次同步成功的MRU0的频点索引），查找所有MRU0频点刷新为同步存在，确保状态一致性；
     **********************************************************************************************/
    if (VOS_NULL_PTR == pstGeoSysRecSrchList->pstAcqSysInfo)
    {
        /* 再次更新下次scan list搜索索引 */
        CNAS_XSD_SetCurChannelScanIndex(usCurScanListIndex + 1);


        /* 由于OOC场景下，会出现插入MRU0频点，为了确保之前搜索该频点与本次搜到的频点状态一致，这里把
         * 之前的频点也刷成同步成功
         */
        if (VOS_TRUE == CNAS_XSD_IsMru0FreqInOocScene((CNAS_PRL_FREQENCY_CHANNEL_STRU *)&(pstSyncCnf->stFreq)))
        {
            CNAS_XSD_UpdateFreqStatusBeforeCurIndexInScanChanList(CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_EXIST,
                                                                  usCurScanListIndex,
                                                                  (CNAS_PRL_FREQENCY_CHANNEL_STRU *)&(pstSyncCnf->stFreq),
                                                                  pstScanList);
        }

        /* log scan list搜索状态 */
        CNAS_XSD_LogScanChannelList(ID_CNAS_XSD_MNTN_LOG_SCAN_CHAN_LIST_IND, pstScanList);

    }
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_UpdateChanStatusUponRcvCasSyncCnfFail_SysAcq
 功能描述  : 收到CAS同步失败时，更新频点状态
 输入参数  : pstSyncCnf -- 同步失败的确认消息

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年9月9日
   作    者   : y00245242
   修改内容   : DTS2015090601618
*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateChanStatusUponRcvCasSyncCnfFail_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
)
{
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList = VOS_NULL_PTR;
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanList          = VOS_NULL_PTR;
    VOS_UINT16                                              usCurScanListIndex;

    /***********************************************************************************************
     * 1 如果是available系统同步，则不对scan list做操作；否则，
     **********************************************************************************************/
    /* available系统同步，跳过 */
    if (VOS_TRUE == CNAS_XSD_GetAvailSysAcqListFlg_SysAcq())
    {
        return;
    }

    pstScanList          = CNAS_XSD_GetScanChanListAddr();

    pstGeoSysRecSrchList = CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq();


    /***********************************************************************************************
     * 2 如果是GEO同步，如果不是MRU0插入频点，则需要从scan list当前索引往后刷新失败的频点；否则需要从
     *   scan list头部到当前索引查找所有MRU0频点刷新为同步不存在，确保状态一致性；
    **********************************************************************************************/
    usCurScanListIndex = CNAS_XSD_UpdateSyncFailChanStatus_SysAcq(pstScanList->usCurScanIndex,
                                                                  (VOS_UINT16)pstSyncCnf->ulSyncFailFreqNum,
                                                                  &pstSyncCnf->astSyncRsltList[0],
                                                                  pstScanList,
                                                                  pstGeoSysRecSrchList);


    /***********************************************************************************************
     * 3 如果不是GEO同步，则需要从scan list当前索引往后刷新失败的频点；
     **********************************************************************************************/
    if (VOS_NULL_PTR == pstGeoSysRecSrchList->pstAcqSysInfo)
    {
        CNAS_XSD_SetCurChannelScanIndex(usCurScanListIndex + 1);

        /* log scan list搜索状态 */
        CNAS_XSD_LogScanChannelList(ID_CNAS_XSD_MNTN_LOG_SCAN_CHAN_LIST_IND, pstScanList);
    }
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_UpdateChanStatusUponRcvCasDeterminInd_SysAcq
 功能描述  : 收到CAS determine ind时，更新频点状态
 输入参数  : pstDetermineInd -- determine ind消息

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年9月9日
   作    者   : y00245242
   修改内容   : DTS2015090601618
 2.日    期   : 2015年10月8日
   作    者   : c00299063
   修改内容   : DTS2015090601618
*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateChanStatusUponRcvCasDeterminInd_SysAcq(
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstTempFreq
)
{
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanList = VOS_NULL_PTR;

    /***********************************************************************************************
     * 1 如果是available系统同步，则不对scan list做操作；否则，
     **********************************************************************************************/
    /* available系统同步，跳过 */
    if (VOS_TRUE == CNAS_XSD_GetAvailSysAcqListFlg_SysAcq())
    {
        return;
    }

    pstScanList = CNAS_XSD_GetScanChanListAddr();

    /***********************************************************************************************
     * 2 如果当前失败的频点是MRU0的频点，则需要从scan list头部到当前索引查找所有MRU0频点刷新为同步不存
     *   在；否则从scan list头部到当前索引，查找到失败的频点后，跳出循环；
     **********************************************************************************************/
    if (VOS_TRUE == CNAS_XSD_IsMru0FreqInOocScene(pstTempFreq))
    {
        CNAS_XSD_UpdateFreqStatusBeforeCurIndexInScanChanList(CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST,
                                                              pstScanList->usCurScanIndex,
                                                              pstTempFreq,
                                                              pstScanList);
    }
    else
    {

        (VOS_VOID)CNAS_XSD_UpdateChanStatusInScanChanList(0,
                                                          pstTempFreq,
                                                          CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST,
                                                          pstScanList);

    }

    /* log scan list搜索状态 */
    CNAS_XSD_LogScanChannelList(ID_CNAS_XSD_MNTN_LOG_SCAN_CHAN_LIST_IND, pstScanList);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_UpdateAvailOrNegSystemChanStatusInScanChanList_SysAcq
 功能描述  : 更新available或negative系统频点状态
 输入参数  : pstChannel -- available系统频点

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年9月9日
   作    者   : y00245242
   修改内容   : DTS2015090601618
*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateAvailOrNegSystemChanStatusInScanChanList_SysAcq(
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreq,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList
)
{
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanList = VOS_NULL_PTR;

    pstScanList = CNAS_XSD_GetScanChanListAddr();

    /***********************************************************************************************
     * i) 如果是OOC场景下的MRU0插入频点，同步到的MRU0频点是negative系统或available系统，则scan list列
     * 表中所有插入的MRU0都刷新为不存在；否则，
     * ii) 从scan list当前开始查找，刷新该频点为搜索不存在
     **********************************************************************************************/
    if (VOS_TRUE == CNAS_XSD_IsMru0FreqInOocScene(pstFreq))
    {
        CNAS_XSD_UpdateFreqStatusBeforeCurIndexInScanChanList(CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST,
                                                              pstScanChanList->usTotalNum,
                                                              pstFreq,
                                                              pstScanChanList);
    }
    else
    {
        (VOS_VOID)CNAS_XSD_UpdateChanStatusInScanChanList(0,
                                                          pstFreq,
                                                          CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST,
                                                          pstScanList);
    }
}

/*lint -restore*/

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



