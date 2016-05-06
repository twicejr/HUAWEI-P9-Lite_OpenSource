/*******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsdFsmSysAcq.c
  版 本 号   : 初稿
  作    者   : h00300778
  生成日期   : 2014年07月28日
  功能描述   : Evdo SD SYSTEM ACQUIRE状态机事件处理函数
  函数列表   :
  修改历史   :
  1.日    期   : 2014年07月28日
    作    者   : h00300778
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasHsdCtx.h"
#include  "CnasCcb.h"
#include  "CnasPrlApi.h"
#include  "CnasHsdComFunc.h"
#include  "CnasHsdSndInternalMsg.h"
#include  "CnasHsdSndMscc.h"
#include  "CnasHsdSndCas.h"
#include  "CnasHsdFsmSysAcq.h"
#include  "CnasHsdFsmSysAcqTbl.h"
#include  "CnasHsdSysAcqStrategy.h"
#include  "CnasHsdAvoidStrategy.h"
#include  "CnasMntn.h"
#include  "CnasHsdMntn.h"
#include  "cas_hrpd_overheadmsg_nas_pif.h"
#include  "CnasHsdSndHsm.h"
#include  "CnasHsdFsmMainTbl.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_FSM_SYS_ACQ_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* 定义当前在混合模式下收到MMA搜网和1X搜网结果上报的状态 */
CNAS_HSD_SYS_ACQ_STATUS_ENUM_UINT32                     g_enSysAcqStatus = 0;

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_HSD_SndSysAcqAbortRlst
 功能描述  : 发送ABORT结果给层一状态机
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月5日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SndSysAcqAbortRlst(VOS_VOID)
{
    if (CNAS_HSD_ABORT_REASON_DATA_CALL == CNAS_HSD_GetAbortReason_SysAcq())
    {
        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_ABORTED,
                               CNAS_HSD_GetCurSysAcqScene_SysAcq(),
                               CNAS_HSD_SYS_ACQ_FAIL_ACT_ACQ_IMMEDIATE);
    }
    else
    {
        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_ABORTED,
                               CNAS_HSD_GetCurSysAcqScene_SysAcq(),
                               CNAS_HSD_SYS_ACQ_FAIL_ACT_WAIT_TIMEOUT);
    }
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvCasOverheadInd_SysAcq_WaitCasInd
 功能描述  : CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_IND状态收到ID_CNAS_HRDP_OVERHEAD_MSG_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月17日
    作    者   : h00300778
    修改内容   : 新生成函数
  2.日    期   : 2015年07月37日
    作    者   : x00306642
    修改内容   : MCC白皮书判断

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasOverheadInd_SysAcq_WaitCasInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_PRL_HRPD_SYSTEM_STRU                              *pstHrpdSys;
    CAS_CNAS_HRPD_OVERHEAD_MSG_IND_STRU                    *pstCasOhmMsg;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          astFreqList[CNAS_CAS_HRPD_MAX_FREQ_NUM];
    VOS_UINT32                                              ulFreqNum;
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene;
    VOS_UINT32                                              ulMccFlg;

    PS_MEM_SET(astFreqList, 0, sizeof(astFreqList));

    /* 停止保护定时器 */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_CAS_OHM_IND);

    pstCasOhmMsg = (CAS_CNAS_HRPD_OVERHEAD_MSG_IND_STRU *)pstMsg;

    pstHrpdSys   = CNAS_HSD_GetCasOhmHrpdSysAddr();

    pstHrpdSys->stFreq.enBandClass = pstCasOhmMsg->usBandClass;
    pstHrpdSys->stFreq.usChannel   = pstCasOhmMsg->usFreq;
    pstHrpdSys->ucSubnetMask       = pstCasOhmMsg->ucSubNetMask;
    PS_MEM_CPY(pstHrpdSys->aucSubnet, pstCasOhmMsg->aucSectorId, CNAS_PRL_BYTES_IN_SUBNET);

    ulMccFlg = CNAS_HSD_IsMccInOperLockWhiteSidList(pstCasOhmMsg->usCountryCode);

    /* 重新发起搜网 */
    if ((VOS_FALSE == CNAS_HSD_IsCurrFreqStay(pstHrpdSys))
     || (VOS_FALSE == ulMccFlg))
    {
        if (VOS_TRUE == CNAS_HSD_GetAbortFlg_SysAcq())
        {
            CNAS_HSD_SndSysAcqAbortRlst();

            /* 退出层二状态机 */
            CNAS_HSD_QuitFsmSysAcq_SysAcq();

            return VOS_TRUE;
        }

        ulFreqNum = CNAS_HSD_GetScanListSameLevelFreq(CNAS_CAS_HRPD_MAX_FREQ_NUM, astFreqList);
        if (0 == ulFreqNum)
        {
            /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
            CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_FAILURE,
                                   CNAS_HSD_GetCurSysAcqScene_SysAcq(),
                                   CNAS_HSD_SYS_ACQ_FAIL_ACT_WAIT_TIMEOUT);

            /* 退出层二状态机 */
            CNAS_HSD_QuitFsmSysAcq_SysAcq();
        }
        else
        {
            /* 给CAS发送ID_CNAS_CAS_HRPD_SYSTEM_SYNC_REQ */
            CNAS_HSD_SndCasSysSyncReq(ulFreqNum, astFreqList);;

            /* 迁移到 CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态, 并启动保护定时器TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF */
            CNAS_HSD_SetCurrFsmState(CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF);

            CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF, TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF_LEN);
        }
    }
    else
    {
        /* avoid模块处理 */
        CNAS_HSD_ProcAvoidEventInSubnetIdChange(pstHrpdSys);

        /* 更新history list */
        CNAS_HSD_UpdateHistorySysList(pstHrpdSys);

        /* Pilot search时成功等到ohm消息即可结束流程  */
        enSysAcqScene = CNAS_HSD_GetCurSysAcqScene_SysAcq();

        if (CNAS_HSD_SYS_ACQ_SCENE_PILOT_SEARCH == enSysAcqScene)
        {
            /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
            CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_SUCCESS,
                                   CNAS_HSD_SYS_ACQ_SCENE_PILOT_SEARCH,
                                   CNAS_HSD_SYS_ACQ_FAIL_ACT_BUTT);

            /* 退出层二状态机 */
            CNAS_HSD_QuitFsmSysAcq_SysAcq();

            return VOS_TRUE;
        }


        /* HSD收到CAS的overhead消息时，要给HSM转发overhead消息 */
        CNAS_HSD_SndHsmOverheadMsgInd(pstCasOhmMsg);

        CNAS_HSD_SndMsccOverheadMsgInd(pstCasOhmMsg,pstHrpdSys);

        /* 迁移到 CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SESSION_IND状态, 并启动保护定时器TI_CNAS_HSD_WAIT_SESSION_NEG_RSLT_IND */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_SYS_ACQ_STA_WAIT_SESSION_NEG_RSLT_IND);
        CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_SESSION_NEG_RSLT_IND, TI_CNAS_HSD_WAIT_SESSION_NEG_RSLT_IND_LEN);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvTiWaitCasOhmIndExpired_SysAcq_WaitCasOhmInd
 功能描述  : CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND状态等TI_CNAS_HSD_WAIT_CAS_OHM_IND消息超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月08日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvTiWaitCasOhmIndExpired_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_PRL_FREQENCY_CHANNEL_STRU      astFreqList[CNAS_CAS_HRPD_MAX_FREQ_NUM];
    VOS_UINT32                          ulFreqNum;

    CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_RcvTiWaitCasOhmIndExpired_SysAcq_WaitCasOhmInd: timer out");

    /* 判断当前是否有打断，如果有则退出搜网流程 */
    if (VOS_TRUE == CNAS_HSD_GetAbortFlg_SysAcq())
    {
        CNAS_HSD_SndSysAcqAbortRlst();

        /* 退出层二状态机 */
        CNAS_HSD_QuitFsmSysAcq_SysAcq();

        return VOS_TRUE;
    }
    PS_MEM_SET(astFreqList, 0, sizeof(astFreqList));

    ulFreqNum = CNAS_HSD_GetScanListSameLevelFreq(CNAS_CAS_HRPD_MAX_FREQ_NUM, astFreqList);
    if (0 == ulFreqNum)
    {
        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_FAILURE,
                               CNAS_HSD_GetCurSysAcqScene_SysAcq(),
                               CNAS_HSD_SYS_ACQ_FAIL_ACT_WAIT_TIMEOUT);

        /* 退出层二状态机 */
        CNAS_HSD_QuitFsmSysAcq_SysAcq();
    }
    else
    {
        /* 给CAS发送ID_CNAS_CAS_HRPD_SYSTEM_SYNC_REQ */
        CNAS_HSD_SndCasSysSyncReq(ulFreqNum, astFreqList);

        /* 迁移到 CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态, 并启动保护定时器TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF);

        CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF, TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF_LEN);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvCasRedirectionInd_SysAcq_WaitCasInd
 功能描述  : CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_IND状态收到ID_CNAS_HRDP_REDIRECTION_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月17日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasRedirectionInd_SysAcq_WaitCasInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_NETWORK_LOST_IND_STRU                    *pstCasRedirMsg;
    CNAS_HSD_REDIRECTION_STRU                              *pstRedirection;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          astFreqList[CNAS_CAS_HRPD_MAX_FREQ_NUM];
    VOS_UINT32                                              ulFreqNum;

    PS_MEM_SET(astFreqList, 0, sizeof(astFreqList));

    pstCasRedirMsg = (CAS_CNAS_HRPD_NETWORK_LOST_IND_STRU*)pstMsg;

    if (0 != pstCasRedirMsg->ucChanNum)
    {
        pstRedirection = CNAS_HSD_GetRedirectionFreqAddr();

        /* 收到的频点加入全局变量中用于构造搜网列表 */
        pstRedirection->ucChanNum = pstCasRedirMsg->ucChanNum;

        PS_MEM_CPY(pstRedirection->aulChannel,
                   pstCasRedirMsg->aulChannel,
                   sizeof(CAS_CNAS_HRPD_DERECTION_CHANNEL_STRU) * pstCasRedirMsg->ucChanNum);

        /* 打印收到的频点信息 */
        CNAS_HSD_LogRedirectionFreqList(pstRedirection);

        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_REDIRECTION,
                               CNAS_HSD_GetCurSysAcqScene_SysAcq(),
                               CNAS_HSD_SYS_ACQ_FAIL_ACT_WAIT_TIMEOUT);

        /* 退出层二状态机 */
        CNAS_HSD_QuitFsmSysAcq_SysAcq();

        return VOS_TRUE;

    }

    ulFreqNum = CNAS_HSD_GetScanListSameLevelFreq(CNAS_CAS_HRPD_MAX_FREQ_NUM, astFreqList);

    /* 构造的scan list为空 */
    if (0 == ulFreqNum)
    {

        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_FAILURE,
                               CNAS_HSD_GetCurSysAcqScene_SysAcq(),
                               CNAS_HSD_SYS_ACQ_FAIL_ACT_WAIT_TIMEOUT);

        /* 退出层二状态机 */
        CNAS_HSD_QuitFsmSysAcq_SysAcq();

        return VOS_TRUE;
    }

    /* 给CAS发送ID_CNAS_CAS_HRPD_SYSTEM_SYNC_REQ */
    CNAS_HSD_SndCasSysSyncReq(ulFreqNum, astFreqList);

    /* 迁移到 CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态, 并启动保护定时器TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF);

    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF, TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvCasNoRf_SysAcq_WaitCasInd
 功能描述  : CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_IND状态收到ID_CNAS_HRDP_NETWORK_LOST_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月17日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasNoRf_SysAcq_WaitCasInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT16                          usCurIndex = 0;

    /* 如果当前index 大于等于1 将当前位置减1 (为了重新搜SYNC CNF SUCC的那个频点) */
    usCurIndex = CNAS_HSD_GetCurScanFreqIndex();

    if (1 <= usCurIndex)
    {
        CNAS_HSD_SetCurScanFreqIndex(usCurIndex - 1);
    }

    /* 停止保护定时器 */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_CAS_OHM_IND);

    /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
    CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_NORF,
                           CNAS_HSD_GetCurSysAcqScene_SysAcq(),
                           CNAS_HSD_SYS_ACQ_FAIL_ACT_WAIT_TIMEOUT);

    /* 退出层二状态机 */
    CNAS_HSD_QuitFsmSysAcq_SysAcq();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvCasNetworkLost_SysAcq_WaitCasInd
 功能描述  : CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_IND状态收到ID_CNAS_HRDP_NETWORK_LOST_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月17日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasNetworkLost_SysAcq_WaitCasInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_PRL_FREQENCY_CHANNEL_STRU      astFreqList[CNAS_CAS_HRPD_MAX_FREQ_NUM];
    VOS_UINT32                          ulFreqNum;

    PS_MEM_SET(astFreqList, 0, sizeof(astFreqList));

    ulFreqNum = CNAS_HSD_GetScanListSameLevelFreq(CNAS_CAS_HRPD_MAX_FREQ_NUM, astFreqList);
    /* 已经没有频点要搜 */
    if (0 == ulFreqNum)
    {
        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_FAILURE,
                                CNAS_HSD_GetCurSysAcqScene_SysAcq(),
                               CNAS_HSD_SYS_ACQ_FAIL_ACT_WAIT_TIMEOUT);

        /* 退出层二状态机 */
        CNAS_HSD_QuitFsmSysAcq_SysAcq();
    }
    /* 继续给接入层发搜网请求 */
    else
    {
        /* 给CAS发送ID_CNAS_CAS_HRPD_SYSTEM_SYNC_REQ */
        CNAS_HSD_SndCasSysSyncReq(ulFreqNum, astFreqList);

        /* 迁移到 CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态, 并启动保护定时器TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF);

        CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF, TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF_LEN);
    }

    return VOS_TRUE;
}

/*****************************************************************************

 函 数 名  : CNAS_HSD_RcvTiAvailableTimerExpired_WaitMru0
 功能描述  : MRUO搜网过程中，收到available定时器超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月15日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvTiAvailableTimerExpired_WaitMru0(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSD_SetOocWaitSearchFlag(VOS_TRUE);

    return VOS_TRUE;
}


/*****************************************************************************

 函 数 名  : CNAS_HSD_RcvCasNetworkLost_SysAcq_WaitCasIndProc
 功能描述  : CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_IND状态收到ID_CNAS_HRDP_NETWORK_LOST_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月13日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasNetworkLost_SysAcq_WaitCasIndProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_NETWORK_LOST_IND_STRU                    *pstCasNetworkLostMsg;

    pstCasNetworkLostMsg = (CAS_CNAS_HRPD_NETWORK_LOST_IND_STRU*)pstMsg;

    if (CAS_CNAS_HRPD_NETWORK_LOST_REASON_ENUM_BUTT <= pstCasNetworkLostMsg->enNetworkLostReason)
    {
        return VOS_TRUE;
    }

    /* 停止保护定时器 */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_CAS_OHM_IND);

    if (CAS_CNAS_HRPD_NETWORK_LOST_NO_RF == pstCasNetworkLostMsg->enNetworkLostReason)
    {
        if (CNAS_HSD_ABORT_REASON_DATA_CALL == CNAS_HSD_GetAbortReason_SysAcq())
        {
            CNAS_HSD_InitCacheMsgQueue(&(CNAS_HSD_GetHsdCtxAddr()->stCacheMsgQueue), CNAS_HSD_INIT_CTX_POWEROFF);

            CNAS_HSD_SndMsccDataCallRedialSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_NO_RF);
        }

        CNAS_HSD_RcvCasNoRf_SysAcq_WaitCasInd(ulEventType, pstMsg);

        return VOS_TRUE;
    }

    /* 判断当前是否有打断，如果有则退出搜网流程 */
    if (VOS_TRUE == CNAS_HSD_GetAbortFlg_SysAcq())
    {
        CNAS_HSD_SndSysAcqAbortRlst();

        /* 退出层二状态机 */
        CNAS_HSD_QuitFsmSysAcq_SysAcq();

        return VOS_TRUE;
    }

    if (CAS_CNAS_HRPD_NETWORK_LOST_REDIRECT == pstCasNetworkLostMsg->enNetworkLostReason)
    {
        /* 重定向消息指示 */
        CNAS_HSD_RcvCasRedirectionInd_SysAcq_WaitCasInd(ulEventType, pstMsg);
    }
    else
    {
        CNAS_HSD_RcvCasNetworkLost_SysAcq_WaitCasInd(ulEventType, pstMsg);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvMsccSysAcqReq_SysAcq_Init
 功能描述  : CNAS_HSD_SYS_ACQ_STA_INIT状态收到ID_MMA_HSD_SYSTEM_ACQUIRE_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月17日
    作    者   : h00300778
    修改内容   : 新生成函数
  2.日    期   : 2015年04月07日
    作    者   : z00316370
    修改内容   : 增加搜网场景判断

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccSysAcqReq_SysAcq_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_PRL_FREQENCY_CHANNEL_STRU      astFreqList[CNAS_CAS_HRPD_MAX_FREQ_NUM];
    VOS_UINT32                          ulFreqNum;
    MSCC_HSD_SYSTEM_ACQUIRE_REQ_STRU   *pstSysAcqReq;

    pstSysAcqReq    = (MSCC_HSD_SYSTEM_ACQUIRE_REQ_STRU *)pstMsg;

    if (MSCC_HSD_ACQUIRE_REASON_POWER_UP == pstSysAcqReq->enReason)
    {
        PS_MEM_SET(astFreqList, 0, sizeof(astFreqList));

        /* 保存入口消息 */
        CNAS_HSD_SaveCurEntryMsg(ulEventType, pstMsg);

        /* 构造scan list */
        CNAS_HSD_BuildHrpdScanList(CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON);

        ulFreqNum = CNAS_HSD_GetScanListSameLevelFreq(CNAS_CAS_HRPD_MAX_FREQ_NUM, astFreqList);

        /* 构造的scan list为空 */
        if (0 == ulFreqNum)
        {
            /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
            CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_FAILURE,
                                   CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON,
                                   CNAS_HSD_SYS_ACQ_FAIL_ACT_WAIT_TIMEOUT);

            /* 退出层二状态机 */
            CNAS_HSD_QuitFsmSysAcq_SysAcq();

            return VOS_TRUE;
        }

        /* 给CAS发送ID_CNAS_CAS_HRPD_SYSTEM_SYNC_REQ */
        CNAS_HSD_SndCasSysSyncReq(ulFreqNum, astFreqList);

        /* 给MMA发送ID_HSD_MMA_SYSTEM_ACQUIRE_START_IND */
        CNAS_HSD_SndMsccSysAcqStartInd();

        /* 迁移到 CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态, 并启动保护定时器TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF);
        CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF, TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF_LEN);

        /* 清除当前驻留的Hrpd信息 */
        CNAS_HSD_ClearHrpdSysInfo();
    }
    else
    {
        ;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvHsdSysAcqReq_SysAcq_Init
 功能描述  : CNAS_HSD_SYS_ACQ_STA_INIT状态收到ID_CNAS_HSD_HSD_SYSTEM_ACQUIRED_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月17日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvHsdSysAcqReq_SysAcq_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32  enSysAcqScene;
    CNAS_PRL_FREQENCY_CHANNEL_STRU      astFreqList[CNAS_CAS_HRPD_MAX_FREQ_NUM];
    VOS_UINT32                          ulFreqNum;

    PS_MEM_SET(astFreqList, 0, sizeof(astFreqList));

    /* 保存入口消息 */
    CNAS_HSD_SaveCurEntryMsg(ulEventType, pstMsg);

    enSysAcqScene = CNAS_HSD_GetCurSysAcqScene_SysAcq();

    if (CNAS_HSD_SYS_ACQ_SCENE_NO_RF_RESUME == enSysAcqScene)
    {
        /* 继续搜之前的频点，不重新建表 */
         ulFreqNum = CNAS_HSD_GetScanListSameLevelFreq(CNAS_CAS_HRPD_MAX_FREQ_NUM, astFreqList);
    }
    else
    {
        /* 构造scan list */
        CNAS_HSD_BuildHrpdScanList(enSysAcqScene);

        ulFreqNum = CNAS_HSD_GetScanListSameLevelFreq(CNAS_CAS_HRPD_MAX_FREQ_NUM, astFreqList);
    }

    /* 构造的scan list为空 */
    if (0 == ulFreqNum)
    {
        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_FAILURE,
                               CNAS_HSD_GetCurSysAcqScene_SysAcq(),
                               CNAS_HSD_SYS_ACQ_FAIL_ACT_WAIT_TIMEOUT);

        /* 退出层二状态机 */
        CNAS_HSD_QuitFsmSysAcq_SysAcq();

        return VOS_TRUE;
    }

    /* 给CAS发送ID_CNAS_CAS_HRPD_SYSTEM_SYNC_REQ */
    CNAS_HSD_SndCasSysSyncReq(ulFreqNum, astFreqList);

    /* 给MMA发送ID_HSD_MMA_SYSTEM_ACQUIRE_START_IND */
    CNAS_HSD_SndMsccSysAcqStartInd();

    /* 迁移到 CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态, 并启动保护定时器TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF);
    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF, TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF_LEN);

    /* 清除当前驻留的Hrpd信息 */
    CNAS_HSD_ClearHrpdSysInfo();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvCasSysSyncCnf_SysAcq_WaitCasSysSyncCnf
 功能描述  : CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态收到ID_CAS_CNAS_1X_SYSTEM_SYNC_CNF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月30日
    作    者   : h00300778
    修改内容   : 新生成函数
  2.日    期   : 2015年1月12日
    作    者   : d00212987
    修改内容   : 新增重定向流程判断
  3.日    期   : 2015年07月13日
    作    者   : z00316370
    修改内容   : 清TQE,对ulFreqNum增加判断
  4.日    期   : 2015年08月02日
     作    者   : x00306642
     修改内容   : 打包成api
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasSysSyncCnf_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_SYSTEM_SYNC_CNF_STRU *pstSyncCnf;

    pstSyncCnf                  = (CAS_CNAS_HRPD_SYSTEM_SYNC_CNF_STRU *)pstMsg;

    /* 停止保护定时器 */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF);
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF);

    /* 处理同步确认结果 */
    switch (pstSyncCnf->enSyncRslt)
    {
        case CNAS_CAS_HRPD_RSLT_SUCCESS:
            CNAS_HSD_ProcCasSyncCnfSucc_SysAcq(pstSyncCnf);
            break;

        case CNAS_CAS_HRPD_RSLT_NO_RF:
            CNAS_HSD_ProcCasSyncCnfNoRf_SysAcq(pstSyncCnf);
            break;

        case CNAS_CAS_HRPD_RSLT_FAILURE:
        default:
            CNAS_HSD_ProcCasSyncCnfFail_SysAcq(pstSyncCnf);
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvTiWaitCasSysSyncCnfExpired_SysAcq_WaitCasSysSyncCnf
 功能描述  : CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态等ID_CAS_CNAS_HRPD_SYSTEM_SYNC_CNF消息超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvTiWaitCasSysSyncCnfExpired_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_RcvTiWaitCasSysSyncCnfExpired_SysAcq_WaitCasSysSyncCnf: timer out");

    /* 给CAS发送ID_CNAS_CAS_HRPD_STOP_SYSTEM_SYNC_REQ消息停止同步 */
    CNAS_HSD_SndCasStopSysSyncReq();

    /* 迁移到 CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF状态, 并启动保护定时器TI_CNAS_HSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF);
    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF, TI_CNAS_HSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvCasStopSysSyncCnf_SysAcq_WaitCasStopSysSyncCnf
 功能描述  : CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF状态收到ID_CAS_CNAS_HRPD_STOP_SYSTEM_SYNC_CNF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月17日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasStopSysSyncCnf_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_PRL_FREQENCY_CHANNEL_STRU      astFreqList[CNAS_CAS_HRPD_MAX_FREQ_NUM];
    VOS_UINT32                          ulFreqNum;
    CAS_CNAS_HRPD_STOP_SYSTEM_SYNC_CNF_STRU                *pstStopCnf;

    pstStopCnf  = (CAS_CNAS_HRPD_STOP_SYSTEM_SYNC_CNF_STRU*)pstMsg;

    PS_MEM_SET(astFreqList, 0, sizeof(astFreqList));

    /* 停止保护定时器 */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF);

    /* 跳过已经失败的频点 */
    CNAS_HSD_RefreshScanListIndex((VOS_UINT16)pstStopCnf->ulSyncFailFreqNum);

    /* 判断是否在打断流程中 */
    if (VOS_TRUE == CNAS_HSD_GetAbortFlg_SysAcq())
    {
        CNAS_HSD_SndSysAcqAbortRlst();

        /* 退出层二状态机 */
        CNAS_HSD_QuitFsmSysAcq_SysAcq();

        return VOS_TRUE;
    }

    ulFreqNum = CNAS_HSD_GetScanListSameLevelFreq(CNAS_CAS_HRPD_MAX_FREQ_NUM, astFreqList);

    if (0 == ulFreqNum)
    {
        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_FAILURE,
                               CNAS_HSD_GetCurSysAcqScene_SysAcq(),
                               CNAS_HSD_SYS_ACQ_FAIL_ACT_WAIT_TIMEOUT);

        /* 退出层二状态机 */
        CNAS_HSD_QuitFsmSysAcq_SysAcq();
    }
    else
    {
        /* 给CAS发送ID_CNAS_CAS_HRPD_SYSTEM_SYNC_REQ */
        CNAS_HSD_SndCasSysSyncReq(ulFreqNum, astFreqList);

        /* 迁移到 CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态, 并启动保护定时器TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF);
        CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF, TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF_LEN);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvTiWaitCasStopSysSyncCnfExpired_SysAcq_WaitCasStopSysSyncCnf
 功能描述  : CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF状态收到TI_CNAS_HSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF消息超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月17日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvTiWaitCasStopSysSyncCnfExpired_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_PRL_FREQENCY_CHANNEL_STRU      astFreqList[CNAS_CAS_HRPD_MAX_FREQ_NUM];
    VOS_UINT32                          ulFreqNum;

    PS_MEM_SET(astFreqList, 0, sizeof(astFreqList));

    /* 判断是否在打断流程中 */
    if (VOS_TRUE == CNAS_HSD_GetAbortFlg_SysAcq())
    {
        CNAS_HSD_SndSysAcqAbortRlst();

        /* 退出层二状态机 */
        CNAS_HSD_QuitFsmSysAcq_SysAcq();

        return VOS_TRUE;
    }

    ulFreqNum = CNAS_HSD_GetScanListSameLevelFreq(CNAS_CAS_HRPD_MAX_FREQ_NUM, astFreqList);

    if (0 == ulFreqNum)
    {
        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_FAILURE,
                               CNAS_HSD_GetCurSysAcqScene_SysAcq(),
                               CNAS_HSD_SYS_ACQ_FAIL_ACT_WAIT_TIMEOUT);

        /* 退出层二状态机 */
        CNAS_HSD_QuitFsmSysAcq_SysAcq();
    }
    else
    {
        /* 给CAS发送ID_CNAS_CAS_HRPD_SYSTEM_SYNC_REQ */
        CNAS_HSD_SndCasSysSyncReq(ulFreqNum, astFreqList);

        /* 迁移到 CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态, 并启动保护定时器TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF);
        CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF, TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF_LEN);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_QuitFsmSysAcq
 功能描述  : 退出SYSTEM ACQUIRED状态机
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月25日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_QuitFsmSysAcq_SysAcq(VOS_VOID)
{
#if 0
    CNAS_HSD_ACQUIRE_SYSTEM_LIST_STRU  *pstAcqSysList = VOS_NULL_PTR;

    pstAcqSysList = CNAS_HSD_GetSysAcqListAddr_SysAcq();

    /* 释放系统捕获列表的内存 */
    if (VOS_NULL_PTR != pstAcqSysList->pstAcqSysInfo)
    {
        PS_MEM_FREE(UEPS_PID_HSD, pstAcqSysList->pstAcqSysInfo);
        pstAcqSysList->pstAcqSysInfo = VOS_NULL_PTR;
    }
#endif
    CNAS_HSD_QuitFsmL2();

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_HSD_SetSysAcqStatusByBit
 功能描述  : 设置当前搜网状态:收到MMA搜网请求或收到XSD的1X的搜网消息
 输入参数  : ulBit:对应的BIT值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : h00300778
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SetSysAcqStatusByBit(VOS_UINT32 ulBit)
{
    g_enSysAcqStatus |= BIT_N(ulBit);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetSysAcqStatus
 功能描述  : 获取当前搜网状态:收到MMA搜网请求或收到XSD的1X的搜网消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 获取当前搜网状态
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : h00300778
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_HSD_SYS_ACQ_STATUS_ENUM_UINT32 CNAS_HSD_GetSysAcqStatus(VOS_VOID)
{
    return g_enSysAcqStatus;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_CleanSysAcqStatus
 功能描述  : 清除当前搜网状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : h00300778
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  CNAS_HSD_CleanSysAcqStatus(VOS_VOID)
{
    g_enSysAcqStatus = CNAS_HSD_SYS_ACQ_NULL;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_ClearSysAcqStatusBit
 功能描述  : 清除当前搜网状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : h00300778
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  CNAS_HSD_ClearSysAcqStatusBit(VOS_UINT32 ulBit)
{
    CNAS_HSD_SYS_ACQ_STATUS_ENUM_UINT32 enSysAcqStatus;

    enSysAcqStatus      = BIT_N(ulBit);

    g_enSysAcqStatus    = (g_enSysAcqStatus & (~enSysAcqStatus));

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_ClearHrpdSysAcqStatusBits
 功能描述  : 清除当前hrpd搜网状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2016年01月09日
   作    者   : z00316370
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  CNAS_HSD_ClearHrpdSysAcqStatusBits(VOS_VOID)
{
    CNAS_HSD_ClearSysAcqStatusBit(CNAS_HSD_POWER_ON_SYS_ACQ);
    CNAS_HSD_ClearSysAcqStatusBit(CNAS_HSD_HIGH_PRI_SYS_ACQ);
    CNAS_HSD_ClearSysAcqStatusBit(CNAS_HSD_OTHER_SYS_ACQ);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetCurSysAcqScene_SysAcq
 功能描述  : 返回当前搜网场景
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32 CNAS_HSD_GetCurSysAcqScene_SysAcq(VOS_VOID)
{
    CNAS_HSD_MSG_STRU                                      *pstEntryMsg;
    CNAS_HSD_HSD_SYSTEM_ACQUIRED_REQ_STRU                  *pstIntSysAcqReq;

    /* 获得当前处理CNAS HSD入口消息的缓冲区地址 */
    pstEntryMsg                 = CNAS_HSD_GetCurrFsmEntryMsgAddr();

    if (CNAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_HSD_SYSTEM_ACQUIRE_REQ)
            == pstEntryMsg->ulEventType)
    {
        return CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON;
    }

    if (CNAS_BuildEventType(UEPS_PID_HSD, ID_CNAS_HSD_HSD_SYSTEM_ACQUIRED_REQ)
            == pstEntryMsg->ulEventType)
    {
        pstIntSysAcqReq = (CNAS_HSD_HSD_SYSTEM_ACQUIRED_REQ_STRU *)pstEntryMsg->aucMsgBuffer;

        return pstIntSysAcqReq->enSysAcqScene;
    }

    return CNAS_HSD_SYS_ACQ_SCENE_BUTT;
}


/*****************************************************************************
 函 数 名  : CNAS_HSD_CasSysAcqVaildFreqCheck
 功能描述  : 判断CAS返回的频点是否与下发的一致
 输入参数  : pstSyncCnf:接入层上报的消息
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_CasSysAcqVaildFreqCheck(CAS_CNAS_HRPD_SYSTEM_SYNC_CNF_STRU *pstSyncCnf)
{
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstSrcFreq;
    CNAS_PRL_FREQENCY_CHANNEL_STRU      stDstFreq;
    VOS_UINT16                          usIndex;
    VOS_UINT16                          i;

    usIndex = CNAS_HSD_GetCurScanFreqIndex();

    for (i = 0; i < pstSyncCnf->ulSyncFailFreqNum; i++)
    {
        stDstFreq.enBandClass   = pstSyncCnf->astSyncRsltList[i].stFreq.usBandClass;
        stDstFreq.usChannel     = pstSyncCnf->astSyncRsltList[i].stFreq.usChannel;

        pstSrcFreq = CNAS_HSD_GetScanFreqByIndex(usIndex + i);

        if (VOS_NULL_PTR == pstSrcFreq)
        {
            return VOS_ERR;
        }

        if (VOS_FALSE == CNAS_PRL_CmpFreqValue(pstSrcFreq, &stDstFreq))
        {
            return VOS_ERR;
        }
    }

    if (CNAS_CAS_HRPD_RSLT_SUCCESS == pstSyncCnf->enSyncRslt)
    {
        stDstFreq.enBandClass   = pstSyncCnf->stFreq.usBandClass;
        stDstFreq.usChannel     = pstSyncCnf->stFreq.usChannel;

        pstSrcFreq = CNAS_HSD_GetScanFreqByIndex((VOS_UINT16)(usIndex + pstSyncCnf->ulSyncFailFreqNum));

        if (VOS_NULL_PTR == pstSrcFreq)
        {
            return VOS_ERR;
        }

        if (VOS_FALSE == CNAS_PRL_CmpFreqValue(pstSrcFreq, &stDstFreq))
        {
            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvMsccPowerOffReq_SysAcq_WaitCasSysSyncCnf
 功能描述  : CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态收到ID_MMA_HSD_POWER_OFF_REQ消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月13日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccPowerOffReq_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止保护定时器 */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF);

    (VOS_VOID)CNAS_HSD_SetAbortFlg_SysAcq(VOS_TRUE, CNAS_HSD_ABORT_REASON_POWER_OFF);

    /* 缓存关机请求 */
    CNAS_HSD_SaveCacheMsg(ulEventType, pstMsg);

    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF, TI_CNAS_HSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN);

    /* 给CAS发送ID_CNAS_CAS_HRPD_STOP_SYSTEM_SYNC_REQ消息停止同步 */
    CNAS_HSD_SndCasStopSysSyncReq();

    CNAS_HSD_SetCurrFsmState(CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvMsccPowerOffReq_SysAcq_WaitCasStopSysSyncCnf
 功能描述  : CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF状态收到ID_MMA_HSD_POWER_OFF_REQ消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月13日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccPowerOffReq_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 需要先将DataCall消息回复 */
    if (CNAS_HSD_ABORT_REASON_DATA_CALL == CNAS_HSD_GetAbortReason_SysAcq())
    {
        CNAS_HSD_SndMsccDataCallRedialSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_ABORTED);
    }

    /* 上层会对POWEROFF合POWERSAVE进行控制，假如已经发送过POWERSAVE，则丢弃直接处理POWEROFF消息 */
    if (VOS_TRUE == CNAS_HSD_SetAbortFlg_SysAcq(VOS_TRUE, CNAS_HSD_ABORT_REASON_POWER_OFF))
    {
        /* 清空缓存 */
        CNAS_HSD_InitCacheMsgQueue(&(CNAS_HSD_GetHsdCtxAddr()->stCacheMsgQueue), CNAS_HSD_INIT_CTX_POWEROFF);

        /* 缓存关机请求 */
        CNAS_HSD_SaveCacheMsg(ulEventType, pstMsg);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvMsccPowerOffReq_SysAcq_WaitCasInd
 功能描述  : CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_IND状态收到ID_MMA_HSD_POWER_OFF_REQ消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月13日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccPowerOffReq_SysAcq_WaitCasInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
        /* 需要先将DataCall消息回复 */
    if (CNAS_HSD_ABORT_REASON_DATA_CALL == CNAS_HSD_GetAbortReason_SysAcq())
    {
        CNAS_HSD_SndMsccDataCallRedialSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_ABORTED);
    }

    /* 上层会对POWEROFF合POWERSAVE进行控制，假如已经发送过POWEROFF，则丢弃POWERSAVE消息 */
    if (VOS_TRUE == CNAS_HSD_SetAbortFlg_SysAcq(VOS_TRUE, CNAS_HSD_ABORT_REASON_POWER_OFF))
    {
        /* 停止保护定时器 */
        CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_CAS_OHM_IND);

        /* 清空缓存 */
        CNAS_HSD_InitCacheMsgQueue(&(CNAS_HSD_GetHsdCtxAddr()->stCacheMsgQueue), CNAS_HSD_INIT_CTX_POWEROFF);

        /* 缓存关机请求 */
        CNAS_HSD_SaveCacheMsg(ulEventType, pstMsg);

        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_ABORTED,
                               CNAS_HSD_GetCurSysAcqScene_SysAcq(),
                               CNAS_HSD_SYS_ACQ_FAIL_ACT_WAIT_TIMEOUT);

        /* 退出层二状态机 */
        CNAS_HSD_QuitFsmSysAcq_SysAcq();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvMsccDataCallReq_SysAcq_WaitCasInd
 功能描述  : CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_IND状态收到ID_MMA_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月5日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccDataCallReq_SysAcq_WaitCasInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 当前已经存在data call打断，直接返回 */
    if (VOS_TRUE == CNAS_HSD_IsCurAbortFlgSet_SysAcq(CNAS_HSD_ABORT_REASON_DATA_CALL))
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_RcvMsccDataCallReq_SysAcq_WaitCasInd: Data call abort is set.");

        return VOS_TRUE;
    }

    /* 当前已经是快搜场景，不再响应后续快搜 */
    if (CNAS_HSD_SYS_ACQ_SCENE_DATA_CALL_QUICK == CNAS_HSD_GetCurSysAcqScene_SysAcq())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_RcvMsccDataCallReq_SysAcq_WaitSessionInd: current srch scene is  quick srch.");

        return VOS_TRUE;
    }

    if (VOS_TRUE == CNAS_HSD_SetAbortFlg_SysAcq(VOS_TRUE, CNAS_HSD_ABORT_REASON_DATA_CALL))
    {
        /* 缓存Data Call请求 */
        CNAS_HSD_SaveCacheMsg(ulEventType, pstMsg);
    }
    else
    {
        CNAS_HSD_SndMsccDataCallRedialSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_FAIL);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvCasPilotSearchStopInd_SysAcq_WaitCasSysSyncCnf
 功能描述  : CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态收到ID_CAS_CNAS_HRPD_PILOT_SEARCH_STOP_IND消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月13日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasPilotSearchStopInd_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 如果是pilot search的场景，直接退出。如果是其他场景，该消息认作无效 */
    /* 遗留问题:失败时L1如何处理? */
    if (CNAS_HSD_SYS_ACQ_SCENE_PILOT_SEARCH == CNAS_HSD_GetCurSysAcqScene_SysAcq())
    {
        /* 停止保护定时器 */
        CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF);

        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_FAILURE,
                               CNAS_HSD_SYS_ACQ_SCENE_PILOT_SEARCH,
                               CNAS_HSD_SYS_ACQ_FAIL_ACT_WAIT_TIMEOUT);

        /* 退出层二状态机 */
        CNAS_HSD_QuitFsmSysAcq_SysAcq();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvCasPilotSearchStopInd_SysAcq_WaitCasStopSysSyncCnf
 功能描述  : CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_IND状态收到ID_CAS_CNAS_HRPD_PILOT_SEARCH_STOP_IND消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月13日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasPilotSearchStopInd_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 如果是pilot search的场景，直接退出。如果是其他场景，该消息认作无效 */
    if (CNAS_HSD_SYS_ACQ_SCENE_PILOT_SEARCH == CNAS_HSD_GetCurSysAcqScene_SysAcq())
    {
        /* 停止保护定时器 */
        CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF);

        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_FAILURE,
                               CNAS_HSD_SYS_ACQ_SCENE_PILOT_SEARCH,
                               CNAS_HSD_SYS_ACQ_FAIL_ACT_WAIT_TIMEOUT);

        /* 退出层二状态机 */
        CNAS_HSD_QuitFsmSysAcq_SysAcq();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvMsccDataCallReq_SysAcq_WaitCasStopSysSyncCnf
 功能描述  : CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_IND状态收到ID_MMA_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月5日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccDataCallReq_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 当前已经存在data call打断，直接返回 */
    if (VOS_TRUE == CNAS_HSD_IsCurAbortFlgSet_SysAcq(CNAS_HSD_ABORT_REASON_DATA_CALL))
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_RcvMsccDataCallReq_SysAcq_WaitCasStopSysSyncCnf: Data call abort is set.");

        return VOS_TRUE;
    }

    /* 当前已经是快搜场景，不再响应后续快搜 */
    if (CNAS_HSD_SYS_ACQ_SCENE_DATA_CALL_QUICK == CNAS_HSD_GetCurSysAcqScene_SysAcq())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_RcvMsccDataCallReq_SysAcq_WaitCasStopSysSyncCnf: current srch scene is  quick srch.");

        return VOS_TRUE;
    }

    if (VOS_TRUE == CNAS_HSD_SetAbortFlg_SysAcq(VOS_TRUE, CNAS_HSD_ABORT_REASON_DATA_CALL))
    {
        /* 缓存Data Call请求 */
        CNAS_HSD_SaveCacheMsg(ulEventType, pstMsg);
    }
    else
    {
        CNAS_HSD_SndMsccDataCallRedialSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_FAIL);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvCasPilotSearchStopInd_SysAcq_WaitCasInd
 功能描述  : CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF状态收到ID_CAS_CNAS_HRPD_PILOT_SEARCH_STOP_IND消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月13日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasPilotSearchStopInd_SysAcq_WaitCasInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 如果是pilot search的场景，直接退出。如果是其他场景，该消息认作无效 */
    if (CNAS_HSD_SYS_ACQ_SCENE_PILOT_SEARCH == CNAS_HSD_GetCurSysAcqScene_SysAcq())
    {
        /* 停止保护定时器 */
        CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_CAS_OHM_IND);

        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_FAILURE,
                               CNAS_HSD_SYS_ACQ_SCENE_PILOT_SEARCH,
                               CNAS_HSD_SYS_ACQ_FAIL_ACT_WAIT_TIMEOUT);

        /* 退出层二状态机 */
        CNAS_HSD_QuitFsmSysAcq_SysAcq();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvMsccDataCallReq_SysAcq_WaitCasSysSyncCnf
 功能描述  : CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF状态收到ID_MMA_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月5日
    作    者   : d00212987
    修改内容   : 新生成函数
  2.日    期   : 2015年04月15日
    作    者   : z00316370
    修改内容   : 不在power off/save流程中，才处理此消息，否则丢弃此消息
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccDataCallReq_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 当前已经是快搜场景，不再响应后续快搜 */
    if (CNAS_HSD_SYS_ACQ_SCENE_DATA_CALL_QUICK == CNAS_HSD_GetCurSysAcqScene_SysAcq())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_RcvMsccDataCallReq_SysAcq_WaitCasSysSyncCnf: current srch scene is  quick srch.");

        return VOS_TRUE;
    }

    /* 停止保护定时器 */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF);

    /* 判断是否在打断流程中,不在打断流程中，才处理此条消息 */
    (VOS_VOID)CNAS_HSD_SetAbortFlg_SysAcq(VOS_TRUE, CNAS_HSD_ABORT_REASON_DATA_CALL);

    /* 缓存Data Call请求 */
    CNAS_HSD_SaveCacheMsg(ulEventType, pstMsg);

    /* 给CAS发送ID_CNAS_CAS_HRPD_STOP_SYSTEM_SYNC_REQ消息停止同步 */
    CNAS_HSD_SndCasStopSysSyncReq();

    CNAS_HSD_SetCurrFsmState(CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF);

    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF, TI_CNAS_HSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvMsccPowerSaveReq_SysAcq_WaitCasSysSyncCnf
 功能描述  : CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态收到ID_MSCC_HSD_POWER_SAVE_REQ消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月03日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccPowerSaveReq_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止保护定时器 */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF);

    /* 设置打断标记 */
    (VOS_VOID)CNAS_HSD_SetAbortFlg_SysAcq(VOS_TRUE, CNAS_HSD_ABORT_REASON_POWER_SAVE);

    /* 缓存POWER SAVE请求 */
    CNAS_HSD_SaveCacheMsg(ulEventType, pstMsg);

    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF, TI_CNAS_HSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN);

    /* 给CAS发送ID_CNAS_CAS_HRPD_STOP_SYSTEM_SYNC_REQ消息停止同步 */
    CNAS_HSD_SndCasStopSysSyncReq();

    CNAS_HSD_SetCurrFsmState(CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvMsccPowerSaveReq_SysAcq_WaitCasStopSysSyncCnf
 功能描述  : CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF状态收到ID_MSCC_HSD_POWER_SAVE_REQ消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月03日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccPowerSaveReq_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 需要先将DataCall消息回复 */
    if (CNAS_HSD_ABORT_REASON_DATA_CALL == CNAS_HSD_GetAbortReason_SysAcq())
    {
        CNAS_HSD_SndMsccDataCallRedialSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_ABORTED);
    }

    /* 上层会对POWEROFF合POWERSAVE进行控制，假如已经发送过POWEROFF，则丢弃POWERSAVE消息 */
    if (VOS_TRUE == CNAS_HSD_SetAbortFlg_SysAcq(VOS_TRUE, CNAS_HSD_ABORT_REASON_POWER_SAVE))
    {
        /* 清空缓存 */
        CNAS_HSD_InitCacheMsgQueue(&(CNAS_HSD_GetHsdCtxAddr()->stCacheMsgQueue), CNAS_HSD_INIT_CTX_POWEROFF);

        /* 缓存PowerSave请求 */
        CNAS_HSD_SaveCacheMsg(ulEventType, pstMsg);
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvMsccPowerSaveReq_SysAcq_WaitCasInd
 功能描述  : CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_IND状态收到ID_MSCC_HSD_POWER_SAVE_REQ消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月03日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccPowerSaveReq_SysAcq_WaitCasInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 需要先将DataCall消息回复 */
    if (CNAS_HSD_ABORT_REASON_DATA_CALL == CNAS_HSD_GetAbortReason_SysAcq())
    {
        CNAS_HSD_SndMsccDataCallRedialSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_ABORTED);
    }

    /* 上层会对POWEROFF合POWERSAVE进行控制，假如已经发送过POWEROFF，则丢弃POWERSAVE消息 */
    if (VOS_TRUE == CNAS_HSD_SetAbortFlg_SysAcq(VOS_TRUE, CNAS_HSD_ABORT_REASON_POWER_SAVE))
    {
        /* 停止保护定时器 */
        CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_CAS_OHM_IND);

        /* 清空缓存 */
        CNAS_HSD_InitCacheMsgQueue(&(CNAS_HSD_GetHsdCtxAddr()->stCacheMsgQueue), CNAS_HSD_INIT_CTX_POWEROFF);

        /* 缓存PowerSave请求 */
        CNAS_HSD_SaveCacheMsg(ulEventType, pstMsg);

        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_ABORTED,
                               CNAS_HSD_GetCurSysAcqScene_SysAcq(),
                               CNAS_HSD_SYS_ACQ_FAIL_ACT_WAIT_TIMEOUT);

        /* 退出层二状态机 */
        CNAS_HSD_QuitFsmSysAcq_SysAcq();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvSessionNegRsltInd_SysAcq_WaitSessionInd
 功能描述  : CNAS_HSD_SYS_ACQ_STA_WAIT_SESSION_NEG_RSLT_IND状态收到ID_HSM_HSD_SESSION_NEG_RESULT_IND消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月03日
    作    者   : z00316370
    修改内容   : 新生成函数
  2.日    期   : 2015年06月03日
    作    者   : l00324781
    修改内容   : Iteration 12:CNAS_HSD_SndMsccSessionNegRsltInd增加参数
  3.日    期   : 2015年10月26日
    作    者   : z00316370
    修改内容   : 驻留后将sync的频点保存到MRU中
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvSessionNegRsltInd_SysAcq_WaitSessionInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSM_HSD_SESSION_NEG_RESULT_IND_STRU                    *pstSessionNegRlstInd;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          stFreq;
    CNAS_HSD_REACQ_FALG_ENUM_UINT32                         enReAcqFlag;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          astFreqList[CNAS_CAS_HRPD_MAX_FREQ_NUM];
    VOS_UINT32                                              ulFreqNum;
    CNAS_PRL_HRPD_SYSTEM_STRU                              *pstHrpdSys;
    CNAS_PRL_HRPD_SYSTEM_STRU                               stMru;

    /* 停止保护定时器 */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_SESSION_NEG_RSLT_IND);

    PS_MEM_SET(&stMru, 0, sizeof(CNAS_PRL_HRPD_SYSTEM_STRU));

    pstHrpdSys   = CNAS_HSD_GetCasOhmHrpdSysAddr();

    PS_MEM_SET(astFreqList, 0, sizeof(astFreqList));

    pstSessionNegRlstInd = (HSM_HSD_SESSION_NEG_RESULT_IND_STRU*)pstMsg;
    stFreq.enBandClass   = CNAS_HSD_GetHistorySysList()->stCampedHrpdSysInfo[0].stFreq.enBandClass;
    stFreq.usChannel     = CNAS_HSD_GetHistorySysList()->stCampedHrpdSysInfo[0].stFreq.usChannel;
    enReAcqFlag          = CNAS_HSD_NOT_NEED_REACQ;

    /* avoid模块处理 */
    CNAS_HSD_ProcAvoidEventInSessionNegRlstInd(pstSessionNegRlstInd, &stFreq, &enReAcqFlag);

    /* 搜网成功 */
    if (HSM_HSD_SESSION_NEG_RSLT_SUCCESS == pstSessionNegRlstInd->enNegResult)
    {
        /* 更新Hrpd驻留信息 */
        CNAS_HSD_UpdateHrpdSysInfo(pstHrpdSys);

        /* 将注留的网络保存到MRU */
        if (VOS_FALSE == CNAS_HSD_GetFreqLockMode())
        {
            stMru.stFreq.enBandClass = CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stSyncFreq.enBandClass;
            stMru.stFreq.usChannel   = CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stSyncFreq.usChannel;
            stMru.ucSubnetMask       = pstHrpdSys->ucSubnetMask;
            PS_MEM_CPY(stMru.aucSubnet, pstHrpdSys->aucSubnet, CNAS_PRL_BYTES_IN_SUBNET);
            CNAS_HSD_UpdateMru0(&stMru);
        }

        CNAS_HSD_SndMsccSessionNegRsltInd(pstSessionNegRlstInd->enNegResult,
                                          pstSessionNegRlstInd->ucIsNewSession,
                                          pstSessionNegRlstInd->enSessionRelType,
                                          pstSessionNegRlstInd->ucIsEhrpdSupport);

        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_SUCCESS,
                               CNAS_HSD_GetCurSysAcqScene_SysAcq(),
                               CNAS_HSD_SYS_ACQ_FAIL_ACT_BUTT);

        /* 退出层二状态机 */
        CNAS_HSD_QuitFsmSysAcq_SysAcq();
    }
    else if (HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE != pstSessionNegRlstInd->enNegResult)
    {
        /* 判断当前是否有打断，如果有则退出搜网流程 */
        if (VOS_TRUE == CNAS_HSD_GetAbortFlg_SysAcq())
        {
            CNAS_HSD_SndSysAcqAbortRlst();

            /* 退出层二状态机 */
            CNAS_HSD_QuitFsmSysAcq_SysAcq();

            return VOS_TRUE;
        }

        ulFreqNum = CNAS_HSD_GetScanListSameLevelFreq(CNAS_CAS_HRPD_MAX_FREQ_NUM, astFreqList);

        if (0 == ulFreqNum)
        {
            /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
            CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_FAILURE,
                                   CNAS_HSD_GetCurSysAcqScene_SysAcq(),
                                   CNAS_HSD_SYS_ACQ_FAIL_ACT_WAIT_TIMEOUT);

            /* 退出层二状态机 */
            CNAS_HSD_QuitFsmSysAcq_SysAcq();
        }
        else
        {
            /* 给CAS发送ID_CNAS_CAS_HRPD_SYSTEM_SYNC_REQ */
            CNAS_HSD_SndCasSysSyncReq(ulFreqNum, astFreqList);;

            /* 迁移到 CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态, 并启动保护定时器TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF */
            CNAS_HSD_SetCurrFsmState(CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF);

            CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF, TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF_LEN);
        }
    }
    /* 掉网之后若HRPD变更会首先发送session close然后然重新发起session，因而会收到两次session ind */
    else
    {
        CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_SESSION_NEG_RSLT_IND, TI_CNAS_HSD_WAIT_SESSION_NEG_RSLT_IND_LEN);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvTiWaitSessionNegIndExpired_SysAcq_WaitSessionNegInd
 功能描述  : CNAS_HSD_SYS_ACQ_STA_WAIT_SESSION_NEG_RSLT_IND状态等ID_CAS_CNAS_HRPD_SYSTEM_SYNC_CNF消息超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月08日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvTiWaitSessionNegIndExpired_SysAcq_WaitSessionNegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_PRL_FREQENCY_CHANNEL_STRU      astFreqList[CNAS_CAS_HRPD_MAX_FREQ_NUM];
    VOS_UINT32                          ulFreqNum;

    CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_RcvTiWaitSessionNegIndExpired_SysAcq_WaitSessionNegInd: timer out");

    /* 判断当前是否有打断，如果有则退出搜网流程 */
    if (VOS_TRUE == CNAS_HSD_GetAbortFlg_SysAcq())
    {
        CNAS_HSD_SndSysAcqAbortRlst();

        /* 退出层二状态机 */
        CNAS_HSD_QuitFsmSysAcq_SysAcq();

        return VOS_TRUE;
    }

    PS_MEM_SET(astFreqList, 0, sizeof(astFreqList));

    ulFreqNum = CNAS_HSD_GetScanListSameLevelFreq(CNAS_CAS_HRPD_MAX_FREQ_NUM, astFreqList);
    if (0 == ulFreqNum)
    {
        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_FAILURE,
                               CNAS_HSD_GetCurSysAcqScene_SysAcq(),
                               CNAS_HSD_SYS_ACQ_FAIL_ACT_WAIT_TIMEOUT);

        /* 退出层二状态机 */
        CNAS_HSD_QuitFsmSysAcq_SysAcq();
    }
    else
    {
        /* 给CAS发送ID_CNAS_CAS_HRPD_SYSTEM_SYNC_REQ */
        CNAS_HSD_SndCasSysSyncReq(ulFreqNum, astFreqList);

        /* 迁移到 CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态, 并启动保护定时器TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF);

        CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF, TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF_LEN);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvMsccPowerOffReq_SysAcq_WaitSessionInd
 功能描述  : CNAS_HSD_SYS_ACQ_STA_WAIT_Session_Neg_Rslt_Ind状态收到ID_MMA_HSD_POWER_OFF_REQ消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月03日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccPowerOffReq_SysAcq_WaitSessionInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 需要先将DataCall消息回复 */
    if (CNAS_HSD_ABORT_REASON_DATA_CALL == CNAS_HSD_GetAbortReason_SysAcq())
    {
        CNAS_HSD_SndMsccDataCallRedialSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_ABORTED);
    }

    /* 上层会对POWEROFF合POWERSAVE进行控制，假如已经发送过POWEROFF，则丢弃POWERSAVE消息 */
    if (VOS_TRUE == CNAS_HSD_SetAbortFlg_SysAcq(VOS_TRUE, CNAS_HSD_ABORT_REASON_POWER_OFF))
    {
        /* 停止保护定时器 */
        CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_SESSION_NEG_RSLT_IND);

        /* 清空缓存 */
        CNAS_HSD_InitCacheMsgQueue(&(CNAS_HSD_GetHsdCtxAddr()->stCacheMsgQueue), CNAS_HSD_INIT_CTX_POWEROFF);

        /* 缓存PowerSave请求 */
        CNAS_HSD_SaveCacheMsg(ulEventType, pstMsg);

        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_ABORTED,
                               CNAS_HSD_GetCurSysAcqScene_SysAcq(),
                               CNAS_HSD_SYS_ACQ_FAIL_ACT_WAIT_TIMEOUT);

        /* 退出层二状态机 */
        CNAS_HSD_QuitFsmSysAcq_SysAcq();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvMsccPowerSaveReq_SysAcq_WaitSessionInd
 功能描述  : CNAS_HSD_SYS_ACQ_STA_WAIT_Session_Neg_Rslt_Ind状态收到ID_MSCC_HSD_POWER_SAVE_REQ消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月03日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccPowerSaveReq_SysAcq_WaitSessionInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 需要先将DataCall消息回复 */
    if (CNAS_HSD_ABORT_REASON_DATA_CALL == CNAS_HSD_GetAbortReason_SysAcq())
    {
        CNAS_HSD_SndMsccDataCallRedialSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_ABORTED);
    }

    /* 上层会对POWEROFF合POWERSAVE进行控制，假如已经发送过POWEROFF，则丢弃POWERSAVE消息 */
    if (VOS_TRUE == CNAS_HSD_SetAbortFlg_SysAcq(VOS_TRUE, CNAS_HSD_ABORT_REASON_POWER_SAVE))
    {
        /* 停止保护定时器 */
        CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_SESSION_NEG_RSLT_IND);

        /* 清空缓存 */
        CNAS_HSD_InitCacheMsgQueue(&(CNAS_HSD_GetHsdCtxAddr()->stCacheMsgQueue), CNAS_HSD_INIT_CTX_POWEROFF);

        /* 缓存PowerSave请求 */
        CNAS_HSD_SaveCacheMsg(ulEventType, pstMsg);

        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_ABORTED,
                               CNAS_HSD_GetCurSysAcqScene_SysAcq(),
                               CNAS_HSD_SYS_ACQ_FAIL_ACT_WAIT_TIMEOUT);

        /* 退出层二状态机 */
        CNAS_HSD_QuitFsmSysAcq_SysAcq();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvMsccDataCallReq_SysAcq_WaitSessionInd
 功能描述  : CNAS_HSD_SYS_ACQ_STA_WAIT_Session_Neg_Rslt_Ind状态收到ID_MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月17日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccDataCallReq_SysAcq_WaitSessionInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 当前已经存在data call打断，直接返回 */
    if (VOS_TRUE == CNAS_HSD_IsCurAbortFlgSet_SysAcq(CNAS_HSD_ABORT_REASON_DATA_CALL))
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_RcvMsccDataCallReq_SysAcq_WaitSessionInd: Data call abort is set.");

        return VOS_TRUE;
    }

    /* 当前已经是快搜场景，不再响应后续快搜 */
    if (CNAS_HSD_SYS_ACQ_SCENE_DATA_CALL_QUICK == CNAS_HSD_GetCurSysAcqScene_SysAcq())
    {
        /* 异常事件 */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_RcvMsccDataCallReq_SysAcq_WaitSessionInd: current srch scene is  quick srch.");

        return VOS_TRUE;
    }

    if (VOS_TRUE == CNAS_HSD_SetAbortFlg_SysAcq(VOS_TRUE, CNAS_HSD_ABORT_REASON_DATA_CALL))
    {
        /* 缓存Data Call请求 */
        CNAS_HSD_SaveCacheMsg(ulEventType, pstMsg);
    }
    else
    {
        CNAS_HSD_SndMsccDataCallRedialSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_FAIL);
    }

    return VOS_TRUE;
}

/*****************************************************************************

 函 数 名  : CNAS_HSD_RcvCasNetworkLost_SysAcq_WaitSessionIndProc
 功能描述  : CNAS_HSD_SYS_ACQ_STA_WAIT_Session_Neg_Rslt_Ind状态收到ID_CNAS_HRDP_NETWORK_LOST_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月17日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasNetworkLost_SysAcq_WaitSessionIndProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_NETWORK_LOST_IND_STRU                    *pstCasNetworkLostMsg;

    pstCasNetworkLostMsg = (CAS_CNAS_HRPD_NETWORK_LOST_IND_STRU*)pstMsg;

    if (CAS_CNAS_HRPD_NETWORK_LOST_REASON_ENUM_BUTT <= pstCasNetworkLostMsg->enNetworkLostReason)
    {
        return VOS_TRUE;
    }

    /* 停止保护定时器 */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_SESSION_NEG_RSLT_IND);

    /* NORF场景需要单独处理 */
    if (CAS_CNAS_HRPD_NETWORK_LOST_NO_RF == pstCasNetworkLostMsg->enNetworkLostReason)
    {
        if (CNAS_HSD_ABORT_REASON_DATA_CALL == CNAS_HSD_GetAbortReason_SysAcq())
        {
            CNAS_HSD_InitCacheMsgQueue(&(CNAS_HSD_GetHsdCtxAddr()->stCacheMsgQueue), CNAS_HSD_INIT_CTX_POWEROFF);

            CNAS_HSD_SndMsccDataCallRedialSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_NO_RF);
        }

        CNAS_HSD_RcvCasNoRf_SysAcq_WaitSessionInd(ulEventType, pstMsg);

        return VOS_TRUE;
    }

    /* 判断当前是否有打断，如果有则退出搜网流程 */
    if (VOS_TRUE == CNAS_HSD_GetAbortFlg_SysAcq())
    {
        CNAS_HSD_SndSysAcqAbortRlst();

        /* 退出层二状态机 */
        CNAS_HSD_QuitFsmSysAcq_SysAcq();

        return VOS_TRUE;
    }

    if (CAS_CNAS_HRPD_NETWORK_LOST_REDIRECT == pstCasNetworkLostMsg->enNetworkLostReason)
    {
        /* 重定向消息指示 */
        CNAS_HSD_RcvCasRedirectionInd_SysAcq_WaitSessionInd(ulEventType, pstMsg);
    }
    else
    {
        CNAS_HSD_RcvCasNetworkLost_SysAcq_WaitSessionInd(ulEventType, pstMsg);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvCasRedirectionInd_SysAcq_WaitSessionInd
 功能描述  : CNAS_HSD_SYS_ACQ_STA_WAIT_SESSION_IND状态收到ID_CNAS_HRDP_REDIRECTION_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月20日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasRedirectionInd_SysAcq_WaitSessionInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_NETWORK_LOST_IND_STRU                    *pstCasRedirMsg;
    CNAS_HSD_REDIRECTION_STRU                              *pstRedirection;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          astFreqList[CNAS_CAS_HRPD_MAX_FREQ_NUM];
    VOS_UINT32                                              ulFreqNum;

    PS_MEM_SET(astFreqList, 0, sizeof(astFreqList));

    pstCasRedirMsg = (CAS_CNAS_HRPD_NETWORK_LOST_IND_STRU*)pstMsg;


    if (0 != pstCasRedirMsg->ucChanNum)
    {
        pstRedirection = CNAS_HSD_GetRedirectionFreqAddr();

        /* 收到的频点加入全局变量中用于构造搜网列 */
        pstRedirection->ucChanNum = pstCasRedirMsg->ucChanNum;

        PS_MEM_CPY(pstRedirection->aulChannel,
                   pstCasRedirMsg->aulChannel,
                   sizeof(CAS_CNAS_HRPD_DERECTION_CHANNEL_STRU) * pstCasRedirMsg->ucChanNum);

        /* 打印收到的频点信息 */
        CNAS_HSD_LogRedirectionFreqList(pstRedirection);

        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_REDIRECTION,
                               CNAS_HSD_GetCurSysAcqScene_SysAcq(),
                               CNAS_HSD_SYS_ACQ_FAIL_ACT_WAIT_TIMEOUT);

        /* 退出层二状态机 */
        CNAS_HSD_QuitFsmSysAcq_SysAcq();

        return VOS_TRUE;

    }

    ulFreqNum = CNAS_HSD_GetScanListSameLevelFreq(CNAS_CAS_HRPD_MAX_FREQ_NUM, astFreqList);

    /* 构造的scan list为空 */
    if (0 == ulFreqNum)
    {

        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_FAILURE,
                               CNAS_HSD_GetCurSysAcqScene_SysAcq(),
                               CNAS_HSD_SYS_ACQ_FAIL_ACT_WAIT_TIMEOUT);

        /* 退出层二状态机 */
        CNAS_HSD_QuitFsmSysAcq_SysAcq();

        return VOS_TRUE;
    }

    /* 给CAS发送ID_CNAS_CAS_HRPD_SYSTEM_SYNC_REQ */
    CNAS_HSD_SndCasSysSyncReq(ulFreqNum, astFreqList);

    /* 迁移到 CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态, 并启动保护定时器TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF);

    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF, TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvCasNoRf_SysAcq_WaitSessionInd
 功能描述  : CNAS_HSD_SYS_ACQ_STA_WAIT_SESSION_IND状态收到ID_CNAS_HRDP_NETWORK_LOST_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月20日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasNoRf_SysAcq_WaitSessionInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT16                          usCurIndex = 0;

    /* 如果当前index 大于等于1 将当前位置减1 (为了重新搜SYNC CNF SUCC的那个频点) */
    usCurIndex = CNAS_HSD_GetCurScanFreqIndex();

    if (1 <= usCurIndex)
    {
        CNAS_HSD_SetCurScanFreqIndex(usCurIndex - 1);
    }
    /* 停止保护定时器 */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_SESSION_NEG_RSLT_IND);

    /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
    CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_NORF,
                           CNAS_HSD_GetCurSysAcqScene_SysAcq(),
                           CNAS_HSD_SYS_ACQ_FAIL_ACT_WAIT_TIMEOUT);

    /* 退出层二状态机 */
    CNAS_HSD_QuitFsmSysAcq_SysAcq();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvCasNetworkLost_SysAcq_WaitSessionInd
 功能描述  : CNAS_HSD_SYS_ACQ_STA_WAIT_SESSION_IND状态收到ID_CNAS_HRDP_NETWORK_LOST_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月20日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasNetworkLost_SysAcq_WaitSessionInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_PRL_FREQENCY_CHANNEL_STRU      astFreqList[CNAS_CAS_HRPD_MAX_FREQ_NUM];
    VOS_UINT32                          ulFreqNum;

    PS_MEM_SET(astFreqList, 0, sizeof(astFreqList));



    ulFreqNum = CNAS_HSD_GetScanListSameLevelFreq(CNAS_CAS_HRPD_MAX_FREQ_NUM, astFreqList);
    /* 已经没有频点要搜 */
    if (0 == ulFreqNum)
    {
        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_FAILURE,
                                CNAS_HSD_GetCurSysAcqScene_SysAcq(),
                               CNAS_HSD_SYS_ACQ_FAIL_ACT_WAIT_TIMEOUT);

        /* 退出层二状态机 */
        CNAS_HSD_QuitFsmSysAcq_SysAcq();
    }
    /* 继续给接入层发搜网请求 */
    else
    {
        /* 给CAS发送ID_CNAS_CAS_HRPD_SYSTEM_SYNC_REQ */
        CNAS_HSD_SndCasSysSyncReq(ulFreqNum, astFreqList);

        /* 迁移到 CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态, 并启动保护定时器TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF);

        CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF, TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF_LEN);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvCasOhmInd_SysAcq_WaitSessionInd
 功能描述  : CNAS_HSD_SYS_ACQ_STA_WAIT_SESSION_NEG_RSLT_IND状态收到ID_CNAS_HRDP_OVERHEAD_MSG_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月30日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasOhmInd_SysAcq_WaitSessionInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_PRL_HRPD_SYSTEM_STRU                              *pstHrpdSys;
    CAS_CNAS_HRPD_OVERHEAD_MSG_IND_STRU                    *pstCasOhmMsg;

    pstCasOhmMsg = (CAS_CNAS_HRPD_OVERHEAD_MSG_IND_STRU *)pstMsg;

    pstHrpdSys   = CNAS_HSD_GetCasOhmHrpdSysAddr();

    pstHrpdSys->stFreq.enBandClass = pstCasOhmMsg->usBandClass;
    pstHrpdSys->stFreq.usChannel   = pstCasOhmMsg->usFreq;
    pstHrpdSys->ucSubnetMask       = pstCasOhmMsg->ucSubNetMask;
    PS_MEM_CPY(pstHrpdSys->aucSubnet, pstCasOhmMsg->aucSectorId, CNAS_PRL_BYTES_IN_SUBNET);

    /* avoid模块处理 */
    CNAS_HSD_ProcAvoidEventInSubnetIdChange(pstHrpdSys);

    /* 更新history list */
    CNAS_HSD_UpdateHistorySysList(pstHrpdSys);

    /* HSD收到CAS的overhead消息时，要给HSM转发overhead消息 */
    CNAS_HSD_SndHsmOverheadMsgInd(pstCasOhmMsg);

    CNAS_HSD_SndMsccOverheadMsgInd(pstCasOhmMsg,pstHrpdSys);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_HSD_ProcCasSyncCnfSucc_SysAcq
 功能描述  : 收到CAS的同步回复Succ的处理
 输入参数  : pstSyncCnf----同步回复消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月30日
    作    者   : h00300778
    修改内容   : 新生成函数
  2.日    期   : 2015年1月12日
    作    者   : d00212987
    修改内容   : 新增重定向流程判断
  3.日    期   : 2015年07月13日
    作    者   : z00316370
    修改内容   : 清TQE,对ulFreqNum增加判断
  4.日    期   : 2015年07月17日
    作    者   : x00306642
    修改内容   : evdo pilot iteration 1
*****************************************************************************/
VOS_VOID CNAS_HSD_ProcCasSyncCnfSucc_SysAcq(
    CAS_CNAS_HRPD_SYSTEM_SYNC_CNF_STRU *pstSyncCnf
)
{
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          astFreqList[CNAS_CAS_HRPD_MAX_FREQ_NUM];
    VOS_UINT32                                              ulFreqNum;
    VOS_UINT32                                              ulSynFailFreqNum;
    HSD_HSM_SYSTEM_ACQUIRE_TYPE_ENUM_UINT8                  enSysAcqType;

    PS_MEM_SET(astFreqList, 0, sizeof(astFreqList));

    /***********************************************************************************************
     * 1. 如果当前RF available为FALSE，通知上层RF available
     **********************************************************************************************/
    if (VOS_FALSE == CNAS_HSD_GetHrpdRfAvailFlg())
    {
        /* 上报MSCC NO RF消息 */
        CNAS_HSD_SndMsccRfAvailInd(VOS_TRUE);

        /* 设置当前RF可用标记为:RF可用 */
        CNAS_HSD_SetHrpdRfAvailFlg(VOS_TRUE);
    }

    /***********************************************************************************************
     * 2. 检查频点是否一致
     **********************************************************************************************/
    /* 检查CAS上报的频点与下发的频点是否一致，如不一致重新发频点搜网 */
    if (VOS_OK != CNAS_HSD_CasSysAcqVaildFreqCheck(pstSyncCnf))
    {
        ulFreqNum = CNAS_HSD_GetScanListSameLevelFreq(CNAS_CAS_HRPD_MAX_FREQ_NUM, astFreqList);

        /* 剩余的scan list为空 */
        if (0 == ulFreqNum)
        {
            /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
            CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_FAILURE,
                                   CNAS_HSD_GetCurSysAcqScene_SysAcq(),
                                   CNAS_HSD_SYS_ACQ_FAIL_ACT_WAIT_TIMEOUT);

            /* 退出层二状态机 */
            CNAS_HSD_QuitFsmSysAcq_SysAcq();
        }
        else
        {
            /* 给CAS发送ID_CNAS_CAS_HRPD_SYSTEM_SYNC_REQ */
            CNAS_HSD_SndCasSysSyncReq(ulFreqNum, astFreqList);

            /* 迁移到 CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态, 并启动保护定时器TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF */
            CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF, TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF_LEN);
        }

        return;
    }

    /***********************************************************************************************
     * 3. 非锁频时，允许操作avoid频点
     **********************************************************************************************/
    /* 处理avoid事件 */
    if (VOS_FALSE == CNAS_HSD_GetFreqLockMode())
    {
        CNAS_HSD_ProcAvoidEventInCasSysSyncCnf(pstSyncCnf);
    }

    /***********************************************************************************************
     * 4. 刷新index
     **********************************************************************************************/
    ulSynFailFreqNum = pstSyncCnf->ulSyncFailFreqNum;

    CNAS_HSD_RefreshScanListIndex((VOS_UINT16)(ulSynFailFreqNum + 1));

    /***********************************************************************************************
     * 5. 更新Sync Info
     **********************************************************************************************/
    CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stSyncFreq.enBandClass = pstSyncCnf->stFreq.usBandClass;
    CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stSyncFreq.usChannel   = pstSyncCnf->stFreq.usChannel;

    /***********************************************************************************************
     * 6. 结果报给HSM和MSCC
     **********************************************************************************************/
    /* Abnormal引起的搜网，只在第一次成功时上报abnormal模式 */
    if (VOS_TRUE == CNAS_HSD_GetAbnormalLostFlag())
    {
        enSysAcqType = HSD_HSM_SYSTEM_ACQUIRE_TYPE_ABNORMAL;

        CNAS_HSD_SetAbnormalLostFlag(VOS_FALSE);
    }
    else
    {
        enSysAcqType = HSD_HSM_SYSTEM_ACQUIRE_TYPE_NORMAL;
    }

    CNAS_HSD_SndHsmSysAcqSuccInd(pstSyncCnf->aulSystemTime, enSysAcqType);

    /* 同步成功后给MSCC上报SYNC IND */
    CNAS_HSD_SndMsccSystemSyncInd();

    /* 迁移到 CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态, 并启动保护定时器TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_IND);
    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_OHM_IND, TI_CNAS_HSD_WAIT_CAS_OHM_IND_LEN);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_ProcCasSyncCnfFail_SysAcq
 功能描述  : 收到CAS的同步回复Fail的处理
 输入参数  : pstSyncCnf----同步回复消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月30日
    作    者   : h00300778
    修改内容   : 新生成函数
  2.日    期   : 2015年1月12日
    作    者   : d00212987
    修改内容   : 新增重定向流程判断
  3.日    期   : 2015年07月13日
    作    者   : z00316370
    修改内容   : 清TQE,对ulFreqNum增加判断
  4.日    期   : 2015年07月17日
    作    者   : x00306642
    修改内容   : evdo pilot iteration 1
*****************************************************************************/
VOS_VOID CNAS_HSD_ProcCasSyncCnfFail_SysAcq(
    CAS_CNAS_HRPD_SYSTEM_SYNC_CNF_STRU *pstSyncCnf
)
{
    CNAS_PRL_FREQENCY_CHANNEL_STRU      astFreqList[CNAS_CAS_HRPD_MAX_FREQ_NUM];
    VOS_UINT32                          ulFreqNum;
    VOS_UINT32                          ulSynFailFreqNum;

    PS_MEM_SET(astFreqList, 0, sizeof(astFreqList));

    /***********************************************************************************************
     * 1. 如果当前RF available为FALSE，通知上层RF available
     **********************************************************************************************/
    if (VOS_FALSE == CNAS_HSD_GetHrpdRfAvailFlg())
    {
        /* 上报MSCC NO RF消息 */
        CNAS_HSD_SndMsccRfAvailInd(VOS_TRUE);

        /* 设置当前RF可用标记为:RF可用 */
        CNAS_HSD_SetHrpdRfAvailFlg(VOS_TRUE);
    }

    /***********************************************************************************************
     * 2. 检查频点是否一致
     **********************************************************************************************/
    /* 检查CAS上报的频点与下发的频点是否一致，如不一致重新发频点搜网 */
    if (VOS_OK != CNAS_HSD_CasSysAcqVaildFreqCheck(pstSyncCnf))
    {
        ulFreqNum = CNAS_HSD_GetScanListSameLevelFreq(CNAS_CAS_HRPD_MAX_FREQ_NUM, astFreqList);

        /* 剩余的scan list为空 */
        if (0 == ulFreqNum)
        {
            /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
            CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_FAILURE,
                                   CNAS_HSD_GetCurSysAcqScene_SysAcq(),
                                   CNAS_HSD_SYS_ACQ_FAIL_ACT_WAIT_TIMEOUT);

            /* 退出层二状态机 */
            CNAS_HSD_QuitFsmSysAcq_SysAcq();
        }
        else
        {
            /* 给CAS发送ID_CNAS_CAS_HRPD_SYSTEM_SYNC_REQ */
            CNAS_HSD_SndCasSysSyncReq(ulFreqNum, astFreqList);

            /* 迁移到 CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态, 并启动保护定时器TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF */
            CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF, TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF_LEN);
        }

        return;
    }

    /***********************************************************************************************
     * 3. 非锁频时，允许操作avoid频点
     **********************************************************************************************/
    /* 处理avoid事件 */
    if (VOS_FALSE == CNAS_HSD_GetFreqLockMode())
    {
        CNAS_HSD_ProcAvoidEventInCasSysSyncCnf(pstSyncCnf);
    }

    /***********************************************************************************************
     * 4. 刷新index
     **********************************************************************************************/
    ulSynFailFreqNum = pstSyncCnf->ulSyncFailFreqNum;

    CNAS_HSD_RefreshScanListIndex((VOS_UINT16)ulSynFailFreqNum);

    /***********************************************************************************************
     * 5. 结果报给HSM和MSCC
     **********************************************************************************************/
    ulFreqNum = CNAS_HSD_GetScanListSameLevelFreq(CNAS_CAS_HRPD_MAX_FREQ_NUM, astFreqList);
    if (0 == ulFreqNum)
    {
        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_FAILURE,
                               CNAS_HSD_GetCurSysAcqScene_SysAcq(),
                               CNAS_HSD_SYS_ACQ_FAIL_ACT_WAIT_TIMEOUT);

        /* 退出层二状态机 */
        CNAS_HSD_QuitFsmSysAcq_SysAcq();

        return;
    }

    /* 给CAS发送ID_CNAS_CAS_HRPD_SYSTEM_SYNC_REQ */
    CNAS_HSD_SndCasSysSyncReq(ulFreqNum, astFreqList);

    /* 迁移到 CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态, 并启动保护定时器TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF */
    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF, TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF_LEN);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_ProcCasSyncCnfNoRf_SysAcq
 功能描述  : 收到CAS的同步回复为NO RF处理，对于NO RF场景，需要通知上层当前RF不
             可用，且退出当前状态机
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月17日
    作    者   : x00306642
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HSD_ProcCasSyncCnfNoRf_SysAcq(CAS_CNAS_HRPD_SYSTEM_SYNC_CNF_STRU *pstSyncCnf)
{
    /***********************************************************************************************
     * 对于NO RF场景，直接退出当前状态机
     **********************************************************************************************/
    /* 1.0 判断失败频点是否在搜网列表中 如果存在，增加搜网列表指针 */
    if (VOS_OK == CNAS_HSD_CasSysAcqVaildFreqCheck(pstSyncCnf))
    {
        CNAS_HSD_RefreshScanListIndex((VOS_UINT16)(pstSyncCnf->ulSyncFailFreqNum));

    }

    /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
    CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_NORF,
                           CNAS_HSD_GetCurSysAcqScene_SysAcq(),
                           CNAS_HSD_SYS_ACQ_FAIL_ACT_WAIT_TIMEOUT);

    /* 退出层二状态机 */
    CNAS_HSD_QuitFsmSysAcq_SysAcq();

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvCasNetworkLost_SysAcq_WaitCasSysSyncCnf
 功能描述  : CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态收到ID_CAS_CNAS_HRPD_NETWORK_LOST_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月18日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasNetworkLost_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_PRL_FREQENCY_CHANNEL_STRU      astFreqList[CNAS_CAS_HRPD_MAX_FREQ_NUM];
    VOS_UINT32                          ulFreqNum;

    PS_MEM_SET(astFreqList, 0, sizeof(astFreqList));

    /* 停止保护定时器 */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF);

    ulFreqNum = CNAS_HSD_GetScanListSameLevelFreq(CNAS_CAS_HRPD_MAX_FREQ_NUM, astFreqList);

    if (0 == ulFreqNum)
    {
        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_FAILURE,
                               CNAS_HSD_GetCurSysAcqScene_SysAcq(),
                               CNAS_HSD_SYS_ACQ_FAIL_ACT_WAIT_TIMEOUT);

        /* 退出层二状态机 */
        CNAS_HSD_QuitFsmSysAcq_SysAcq();
    }
    else
    {
        /* 给CAS发送ID_CNAS_CAS_HRPD_SYSTEM_SYNC_REQ */
        CNAS_HSD_SndCasSysSyncReq(ulFreqNum, astFreqList);

        /* 迁移到 CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态, 并启动保护定时器TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF);
        CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF, TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF_LEN);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvCasNetworkLost_SysAcq_WaitCasStopSysSyncCnf
 功能描述  : CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF状态收到ID_CAS_CNAS_HRPD_NETWORK_LOST_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月18日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasNetworkLost_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_PRL_FREQENCY_CHANNEL_STRU      astFreqList[CNAS_CAS_HRPD_MAX_FREQ_NUM];
    VOS_UINT32                          ulFreqNum;

    PS_MEM_SET(astFreqList, 0, sizeof(astFreqList));

    /* 停止保护定时器 */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF);

    /* 判断是否在打断流程中 */
    if (VOS_TRUE == CNAS_HSD_GetAbortFlg_SysAcq())
    {
        CNAS_HSD_SndSysAcqAbortRlst();

        /* 退出层二状态机 */
        CNAS_HSD_QuitFsmSysAcq_SysAcq();

        return VOS_TRUE;
    }

    ulFreqNum = CNAS_HSD_GetScanListSameLevelFreq(CNAS_CAS_HRPD_MAX_FREQ_NUM, astFreqList);

    if (0 == ulFreqNum)
    {
        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_FAILURE,
                               CNAS_HSD_GetCurSysAcqScene_SysAcq(),
                               CNAS_HSD_SYS_ACQ_FAIL_ACT_WAIT_TIMEOUT);

        /* 退出层二状态机 */
        CNAS_HSD_QuitFsmSysAcq_SysAcq();
    }
    else
    {
        /* 给CAS发送ID_CNAS_CAS_HRPD_SYSTEM_SYNC_REQ */
        CNAS_HSD_SndCasSysSyncReq(ulFreqNum, astFreqList);

        /* 迁移到 CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态, 并启动保护定时器TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF);
        CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF, TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF_LEN);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvCasSyncCnf_SysAcq_WaitCasStopSysSyncCnf
 功能描述  : CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF状态收到ID_CAS_CNAS_HRPD_SYSTEM_SYNC_CNF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月17日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasSyncCnf_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_PRL_FREQENCY_CHANNEL_STRU      astFreqList[CNAS_CAS_HRPD_MAX_FREQ_NUM];
    VOS_UINT32                          ulFreqNum;
    CAS_CNAS_HRPD_SYSTEM_SYNC_CNF_STRU                *pstSyncCnf;

    pstSyncCnf  = (CAS_CNAS_HRPD_SYSTEM_SYNC_CNF_STRU*)pstMsg;

    PS_MEM_SET(astFreqList, 0, sizeof(astFreqList));

    /* 停止保护定时器 */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF);

    /* 跳过已经失败的频点 */
    CNAS_HSD_RefreshScanListIndex((VOS_UINT16)pstSyncCnf->ulSyncFailFreqNum);

    /* 判断是否在打断流程中 */
    if (VOS_TRUE == CNAS_HSD_GetAbortFlg_SysAcq())
    {
        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_ABORTED,
                               CNAS_HSD_GetCurSysAcqScene_SysAcq(),
                               CNAS_HSD_SYS_ACQ_FAIL_ACT_WAIT_TIMEOUT);

        /* 退出层二状态机 */
        CNAS_HSD_QuitFsmSysAcq_SysAcq();

        return VOS_TRUE;
    }

    ulFreqNum = CNAS_HSD_GetScanListSameLevelFreq(CNAS_CAS_HRPD_MAX_FREQ_NUM, astFreqList);

    if (0 == ulFreqNum)
    {
        /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
        CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_FAILURE,
                               CNAS_HSD_GetCurSysAcqScene_SysAcq(),
                               CNAS_HSD_SYS_ACQ_FAIL_ACT_WAIT_TIMEOUT);

        /* 退出层二状态机 */
        CNAS_HSD_QuitFsmSysAcq_SysAcq();
    }
    else
    {
        /* 给CAS发送ID_CNAS_CAS_HRPD_SYSTEM_SYNC_REQ */
        CNAS_HSD_SndCasSysSyncReq(ulFreqNum, astFreqList);

        /* 迁移到 CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态, 并启动保护定时器TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF);
        CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF, TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF_LEN);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RcvHsmConnOpenInd_WaitSessionInd
 功能描述  : 收到CAS_CNAS_HRPD_ACCESS_RLST_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年01月11日
    作    者   : z00316370
    修改内容   : 新增

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvHsmConnOpenInd_WaitSessionInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSM_HSD_CONN_OPEN_IND_STRU         *pstOpenInd;
    CNAS_PRL_FREQENCY_CHANNEL_STRU      stFreq;
    CNAS_HSD_REACQ_FALG_ENUM_UINT32     enReAcqFlag;
    VOS_UINT32                          ulFreqNum;
    CNAS_PRL_FREQENCY_CHANNEL_STRU      astFreqList[CNAS_CAS_HRPD_MAX_FREQ_NUM];

    pstOpenInd          = (HSM_HSD_CONN_OPEN_IND_STRU *)pstMsg;
    stFreq.enBandClass  = CNAS_HSD_GetHistorySysList()->stCampedHrpdSysInfo[0].stFreq.enBandClass;
    stFreq.usChannel    = CNAS_HSD_GetHistorySysList()->stCampedHrpdSysInfo[0].stFreq.usChannel;
    enReAcqFlag         = CNAS_HSD_NOT_NEED_REACQ;

    /* avoid模块处理 */
    CNAS_HSD_ProcAvoidEventInAccessRlstInd(pstOpenInd, &stFreq, &enReAcqFlag);

    /* 是否需要重新搜网 */
    if (CNAS_HSD_NEED_REACQ == enReAcqFlag)
    {
        /* 停止保护定时器 */
        CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_SESSION_NEG_RSLT_IND);

        /* 判断当前是否有打断，如果有则退出搜网流程 */
        if (VOS_TRUE == CNAS_HSD_GetAbortFlg_SysAcq())
        {
            CNAS_HSD_SndSysAcqAbortRlst();

            /* 退出层二状态机 */
            CNAS_HSD_QuitFsmSysAcq_SysAcq();

            return VOS_TRUE;
        }

        ulFreqNum = CNAS_HSD_GetScanListSameLevelFreq(CNAS_CAS_HRPD_MAX_FREQ_NUM, astFreqList);

        if (0 == ulFreqNum)
        {
            /* 将层二运行结果通知层一，层一收到此消息后进行层一状态的迁移 */
            CNAS_HSD_SndSysAcqRslt(CNAS_HSD_SYSTEM_ACQUIRED_RESULT_FAILURE,
                                   CNAS_HSD_GetCurSysAcqScene_SysAcq(),
                                   CNAS_HSD_SYS_ACQ_FAIL_ACT_WAIT_TIMEOUT);

            /* 退出层二状态机 */
            CNAS_HSD_QuitFsmSysAcq_SysAcq();
        }
        else
        {
            /* 给CAS发送ID_CNAS_CAS_HRPD_SYSTEM_SYNC_REQ */
            CNAS_HSD_SndCasSysSyncReq(ulFreqNum, astFreqList);;

            /* 迁移到 CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF状态, 并启动保护定时器TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF */
            CNAS_HSD_SetCurrFsmState(CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF);

            CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF, TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF_LEN);
        }
    }

    return VOS_TRUE;
}
/*lint -restore*/

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



