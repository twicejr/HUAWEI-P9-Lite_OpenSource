/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : SleepFlow.c
  版 本 号   : 初稿
  作    者   : zuowen
  生成日期   : 2005年3月7日
  最近修改   :
  功能描述   : 实现 SLEEP 睡眠/唤醒流程驱动
  函数列表   :
  修改历史   :

  1.日    期   : 2005年3月7日
    作    者   : zuowen
    修改内容   : 创建文件

  2.日    期   : 2006年1月14日
    作    者   : wangqinghua
    修改内容   : 集成测试后对 SLEEP 模块进行修改
  3.
    日    期   : 2006年4月13日
    作    者   : w45442
    修改内容   : 修改问题单A32D03034

******************************************************************************/

#include "vos.h"
#include "hpacomm.h"
#include "sleepflow.h"
#include "hpaoperatertt.h"
#include "bbp_wcdma_on_interface.h"
#include "bbp_wcdma_interface.h"
#include "bbp_gsm_on_interface.h"
#include "apminterface.h"
#include "OmApi.h"
#include "PamOamSpecTaskDef.h"
#include "TtfOamInterface.h"
#include "NVIM_Interface.h"
#include "DrvNvInterface.h"
#include "v_private.h"
#include "omprivate.h"
#include "PhyNvDefine.h"
#include "apmprocess.h"
#include "mlowpower.h"
#include "msp_diag_comm.h"
#include "psregrpt.h"

#include "product_config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人：h28225；检视人：l46160；原因简述：打点日志文件宏ID定义*/
#define    THIS_FILE_ID        PS_FILE_ID_SLEEP_FLOW_C
/*lint +e767 修改人：h28225；检视人：l46160；*/

#if (FEATURE_GUC_BBP_TRIG == FEATURE_OFF)
extern VOS_UINT32 PsRegGetDmaCaptureStatus(MODEM_ID_ENUM_UINT16 enModemId);
#endif

SLEEP_INFO_STATE_STRU*                  g_pstSleepInfoSlice;

/* 存放GU模当前系统状态 */
SLEEP_MODE_INFO_STRU                    g_astSleepModeInfo[SLEEP_GU_MODE_TYPE_BUTT];

/* 存放C模当前系统状态 */
SLEEP_BBE16_MODE_INFO_STRU              g_astSleepBBE16ModeInfo[SLEEP_C_MODE_TYPE_BUTT];

T_MODEM_SR_STAMP_STRU                  *g_pstSleepWakeSliceAddr = VOS_NULL_PTR;

/* C模OAM和BBE16之间SRAM信息 */
CPHY_OAM_SHARE_INFO_STRU               *g_pstBBE16SleepInfo = VOS_NULL_PTR;

VOS_VOID SHPA_ActivateHw(VOS_VOID)
{
    return;
}

VOS_VOID SHPA_DeactivateHw(VOS_VOID)
{
    return;
}

VOS_VOID SLEEP_EnterLowPower(VOS_VOID)
{
    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_EnableDspPll
 功能描述  : 使能DSP PLL
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

*****************************************************************************/
VOS_VOID SLEEP_EnableDspPll(VOS_VOID)
{
    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_ExitLowPower
 功能描述  : 退出搜网低功耗
 输入参数  : void
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID SLEEP_ExitLowPower(SLEEP_MODE_ENUM_UINT32 enMode)
{
    return;
}


/*****************************************************************************
 函 数 名  : SLEEP_IsSleep
 功能描述  : 返回系统的状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年10月22日
    作    者   : g47350
    修改内容   : 新生成函数

*****************************************************************************/
VOS_BOOL SLEEP_IsSleep(VOS_VOID)
{
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : Sleep_ActiveDspPll
 功能描述  : 使能DSP PLL,供HPA调用
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

*****************************************************************************/
VOS_VOID Sleep_ActiveDspPll(VOS_VOID)
{
    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_NotifySndMsg
 功能描述  : 通知SLEEP模块有消息发送到DSP
 输入参数  : pMsgBlock
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID SLEEP_NotifySndMsg(VOS_VOID)
{
    return;
}

/*****************************************************************************
 函 数 名  : GUSLEEP_MasterAwakeSlave
 功能描述  : 主模唤醒GU从模接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID GUSLEEP_MasterAwakeSlave(VOS_VOID)
{
    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_32KIsr
 功能描述  : 处理 32K 时钟中断
 输入参数  : void
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID SLEEP_32KIsr(SLEEP_MODE_ENUM_UINT32 enMode)
{
    if ((SLEEP_NORMAL_STATE == g_astSleepModeInfo[enMode].enSystemState)
        || (SLEEP_MASTER_TEMP_LP_STATE == g_astSleepModeInfo[enMode].enSystemState))
    {
        SLEEP_NOR_STATE_TRACK(enMode, SLEEP_MASTER_BBP_32K);

        SLEEP_WAKE_SLICE_RECORD(0);

        SLEEP_SleepIsrProc(BBP_SLEEP_32K_CLOCK_SWITCH_IND, enMode);
    }
}

/*****************************************************************************
 函 数 名  : SLEEP_NormalClockIsr
 功能描述  : 处理 DRX唤醒后时钟切换到61.44M中断
 输入参数  : void
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID SLEEP_NormalClockIsr(SLEEP_MODE_ENUM_UINT32 enMode)
{
    SLEEP_NOR_STATE_TRACK(enMode, SLEEP_MASTER_BBP_NORMAL);

    if ((SLEEP_TEMP_NORMAL_STATE == g_astSleepModeInfo[enMode].enSystemState)
        || (SLEEP_MASTER_LP_STATE == g_astSleepModeInfo[enMode].enSystemState))
    {
        SLEEP_AwakeIsrProc(BBP_SLEEP_NORMAL_CLOCK_SWITCH_IND, enMode);
    }
}

/*****************************************************************************
 函 数 名  : SLEEP_AwakeIsr
 功能描述  : 处理唤醒中断
 输入参数  : void
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID SLEEP_AwakeIsr(SLEEP_MODE_ENUM_UINT32 enMode)
{
    if (SLEEP_MASTER_LP_STATE == g_astSleepModeInfo[enMode].enSystemState)
    {
        SLEEP_NOR_STATE_TRACK(enMode, SLEEP_MASTER_BBP_WAKE);

        SLEEP_WAKE_SLICE_RECORD(4);

        SLEEP_AwakeIsrProc(BBP_SLEEP_WAKE_IND, enMode);
    }
}

/*****************************************************************************
  2 全局变量声明
*****************************************************************************/

/* PHY发来消息处理表 */
SLEEP_MSG_FUN_STRU g_astSleepPhyMsgFunTbl[] =
{
    {ID_UPHY_OAM_MASTER_SLEEP_IND,      SLEEP_MasterSleepMsgProc},
    {ID_UPHY_OAM_SLAVE_SLEEP_IND,       SLEEP_SlaveSleepMsgProc},
};

/* 中断消息处理表 */
SLEEP_MSG_FUN_STRU g_astSleepIsrMsgFunTbl[] =
{
    {BBP_SLEEP_32K_CLOCK_SWITCH_IND,    SLEEP_32KClkMsgProc},
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    {BBE16_SLEEP_SLEEP_IND,             SLEEP_BBE16HaltMsgProc},
#endif
};

/* AWAKE中断消息处理表 */
SLEEP_MSG_FUN_STRU g_astAwakeIsrMsgFunTbl[] =
{
    {BBP_SLEEP_WAKE_IND,                SLEEP_WakeMasterMsgProc},
    {BBP_SLEEP_NORMAL_CLOCK_SWITCH_IND, SLEEP_NormalClkMsgProc},
    {SLEEP_WAKE_MASTER_GU_IND,          SLEEP_WakeMasterGUProc},
    {SLEEP_WAKE_SLAVE_GU_IND,           SLEEP_WakeSlaveGUProc},
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    {BBE16_SLEEP_AWAKE_IND,             SLEEP_BBE16AwakeMsgProc},
    {BBE16_SLEEP_RESUME_IND,            SLEEP_BBE16ResumeMsgProc},
    {BBE16_SLEEP_MASTER_WAKE_IND,       SLEEP_BBE16MasterForceWakeProc},
    {BBE16_SLEEP_SLAVE_WAKE_IND,        SLEEP_BBE16SlaveForceWakeProc},
#endif
};

/* SLEEP流程记录 */
SLEEP_TRACK_RECORD_STRU                *g_pstSleepTrackRecord   = VOS_NULL_PTR;
SLEEP_NORMAL_STATE_RECORD_STRU         *g_pstSleepNormalState   = VOS_NULL_PTR;

HIFI_STATE_STRU                        *g_pstHifiStateSlice     = VOS_NULL_PTR;
HPA_LOAD_PHY_STATE_STRU                *g_pstLoadPhyState       = VOS_NULL_PTR;

SLEEP_DEVICE_STATE_STRU                *g_pstSleepDeviceState   = VOS_NULL_PTR;

/* 互斥信号量 */
VOS_SEM                                 g_ulSleepSem;

/* TCXO稳定信号量 */
VOS_SEM                                 g_ulSleepTcxoSem;

/* BBP寄存器备份恢复内容 */
VOS_UINT32                              g_ulSleepBBPPosValue    = 0;

VOS_UINT32                              g_ulSleepRusumeTime     = 0;

/* 器件恢复时间 */
WG_DRX_RESUME_TIME_STRU                 g_stSleepDrxResumeTime;

VOS_BOOL                                g_bDrxResetFlag = VOS_FALSE;

/* 注册的PID表，在低功耗状态主动通知该注册PID */
SLEEP_NOTIFY_STATE_REG_PID_STRU         g_stSleepNotifyStateRegPidTbl;

#if (FEATURE_GUC_BBP_TRIG == FEATURE_OFF)
VOS_UINT32                              g_ulIsWaitingDMACap = VOS_FALSE;

/* DMA寄存器捕获信号量 */
VOS_SEM                                 g_ulSleepDMACapSem;
#endif

/* 自旋锁，用来作sleep的临界资源保护 */
VOS_SPINLOCK                            g_stSleepSpinLock;

/* CDMA模式控制信息 */
SLEEP_CDMA_STATE_STRU                   g_stSleepCDMAControl;

SLEEP_BBE16_NORMAL_STATE_RECORD_STRU   *g_pstSleepBBE16NormalState   = VOS_NULL_PTR;

SLEEP_BBE16_CPROC_CTRL_STRU             g_stSleepCprocCtrl[VOS_RATMODE_BUTT];

VOS_UINT32                              g_ulConnectFlag = VOS_FALSE;

UCOM_NV_TRI_MODE_FEM_PROFILE_ID_STRU    g_stChannelModeProfileId;

#if (FEATURE_ON == FEATURE_MODE_FEM_CHAN_EXT)
UCOM_NV_FEM_CHAN_PROFILE_STRU           g_stChannelModeProfile;
#else
UCOM_NV_TRI_MODE_FEM_CHAN_PROFILE_STRU  g_stChannelModeProfile;
#endif

#ifndef SLEEP_BIT_N
#define SLEEP_BIT_N(num)                      (0x01 << (num))
#endif

VOS_UINT32                              g_ulSleepSlaveMsgTrackId = 0;

SLEEP_SLAVE_MSG_TRACK_STRU              g_astSleepSlaveMsgTrack[SLEEP_SLAVE_MSG_TRACK_NUM];

VOS_UINT32                              g_ulSleepNotifyMsgTrackId = 0;

SLEEP_NOTIFY_MSG_TRACK_STRU             g_astSleepNotifyMsgTrack[SLEEP_NOTIFY_MSG_TRACK_NUM];

/* modem0和modem2互斥保护信号量 */
#if defined (INSTANCE_1) || defined (INSTANCE_2)
extern VOS_SEM                          g_ulSleepSlaveSem;
#else
VOS_SEM                                 g_ulSleepSlaveSem;
#endif

VOS_UINT32                              g_ulSleepSlaveSemFlag = VOS_FALSE;


/*****************************************************************************
  3 函数申明
*****************************************************************************/

/*****************************************************************************
 函 数 名  : SLEEP_NotifyStateRegPidTblInit
 功能描述  : 注册PID表的初始化
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月14日
    作    者   : L00256032
    修改内容   : V8R1 LowPower&NV_Expand项目新增

*****************************************************************************/
VOS_VOID SLEEP_NotifyStateRegPidTblInit( VOS_VOID )
{
    VOS_UINT32      ulLoop;

    for (ulLoop = 0; ulLoop < SLEEP_NOTIFY_STATE_REG_PID_MAX; ulLoop++)
    {
        g_stSleepNotifyStateRegPidTbl.aulRegPidTbl[ulLoop] = SLEEP_INVALID_PID;
    }

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_NotifyStateReg
 功能描述  : 低功耗状态通知注册函数，不做PID重复注册的判断，由注册方流程保证
 输入参数  : ulRcvPid:接收状态指示的PID
             VOS_RATMODE_ENUM_UINT32 enRatMode
 输出参数  : 无
 返 回 值  : VOS_OK : 注册成功
             VOS_ERR: 注册失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月14日
    作    者   : L00256032
    修改内容   : V8R1 LowPower&NV_Expand项目新增

*****************************************************************************/
VOS_UINT32 SLEEP_NotifyStateReg(VOS_UINT32 ulRcvPid, VOS_RATMODE_ENUM_UINT32 enRatMode)
{
    VOS_UINT32                          ulLoop;
    VOS_INT32                           lLockKey;
    SLEEP_SYSTEM_STATE_ENUM_UINT32      enState;

    /* 注册PID合法性 */
    if ((ulRcvPid < VOS_PID_DOPRAEND) || (ulRcvPid >= VOS_PID_BUTT))
    {
        /* 异常可维可测打印 */
        PS_LOG(WUEPS_PID_SLEEP, 0, PS_PRINT_WARNING, "SLEEP_NotifyStateReg: register invalid PID.");

        return VOS_ERR;
    }

    /* 关中断 */
    lLockKey = VOS_SplIMP();

    /* 将PID放到注册表中 */
    for (ulLoop = 0; ulLoop < SLEEP_NOTIFY_STATE_REG_PID_MAX; ulLoop++)
    {
        if (ulRcvPid == g_stSleepNotifyStateRegPidTbl.aulRegPidTbl[ulLoop])
        {
            enState = g_astSleepModeInfo[enRatMode].enSystemState;

            /* 开中断 */
            VOS_Splx(lLockKey);

            SLEEP_NotifyStateToRegPid(enRatMode, enState);

            return VOS_OK;
        }
    }

    for (ulLoop = 0; ulLoop < SLEEP_NOTIFY_STATE_REG_PID_MAX; ulLoop++)
    {
        /* 找到空的PID存放位置 */
        if (SLEEP_INVALID_PID == g_stSleepNotifyStateRegPidTbl.aulRegPidTbl[ulLoop])
        {
            /* 存储注册的PID */
            g_stSleepNotifyStateRegPidTbl.aulRegPidTbl[ulLoop] = ulRcvPid;

            enState = g_astSleepModeInfo[enRatMode].enSystemState;

            /* 开中断 */
            VOS_Splx(lLockKey);

            SLEEP_NotifyStateToRegPid(enRatMode, enState);

            return VOS_OK;
        }
    }

    /* 开中断 */
    VOS_Splx(lLockKey);

    /* 找不到空的存放位置，打印可维可测信息 */
    PS_LOG1(WUEPS_PID_SLEEP, 0, PS_PRINT_WARNING, "SLEEP_NotifyStateReg: No empty entry.", (VOS_INT32)ulRcvPid);

    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : SLEEP_NotifyStateUnreg
 功能描述  : 低功耗状态通知去注册函数
 输入参数  : ulRcvPid:不接收状态指示的PID
 输出参数  : 无
 返 回 值  : VOS_OK : 去注册成功
             VOS_ERR: 去注册失败(未找到匹配PID)
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月14日
    作    者   : L00256032
    修改内容   : V8R1 LowPower&NV_Expand项目新增

*****************************************************************************/
VOS_UINT32 SLEEP_NotifyStateUnreg(VOS_UINT32 ulRcvPid)
{
    VOS_UINT32      ulLoop;
    VOS_INT32       lLockKey;

    /* 关中断 */
    lLockKey = VOS_SplIMP();

    /* 判断是否已经注册过该PID */
    for (ulLoop = 0; ulLoop < SLEEP_NOTIFY_STATE_REG_PID_MAX; ulLoop++)
    {
        if (ulRcvPid == g_stSleepNotifyStateRegPidTbl.aulRegPidTbl[ulLoop])
        {
            /* 将该PID从表中去除 */
            g_stSleepNotifyStateRegPidTbl.aulRegPidTbl[ulLoop] = SLEEP_INVALID_PID;

            /* 开中断 */
            VOS_Splx(lLockKey);

            return VOS_OK;
        }
    }

    /* 开中断 */
    VOS_Splx(lLockKey);

    /* 未找到匹配PID，异常打印和记录 */
    PS_LOG1(WUEPS_PID_SLEEP, 0, PS_PRINT_WARNING, "SLEEP_NotifyStateUnreg: PID hasn't been found.", (VOS_INT32)ulRcvPid);

    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : SLEEP_NotifyStateToRegPid
 功能描述  : 通知注册PID相应低功耗状态
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月14日
    作    者   : L00256032
    修改内容   : V8R1 LowPower&NV_Expand项目新增

*****************************************************************************/
VOS_VOID SLEEP_NotifyStateToRegPid(
    VOS_RATMODE_ENUM_UINT32             enRatMode,
    SLEEP_SYSTEM_STATE_ENUM_UINT32      enState)
{
    SLEEP_NOTIFY_STATUS_MSG_STRU       *pstMsg;
    VOS_UINT32                          ucLoop;
    VOS_UINT32                          ulMsgLen;

    for (ucLoop = 0; ucLoop < SLEEP_NOTIFY_STATE_REG_PID_MAX; ucLoop++)
    {
        if (SLEEP_INVALID_PID == g_stSleepNotifyStateRegPidTbl.aulRegPidTbl[ucLoop])
        {
            continue;
        }

        ulMsgLen = sizeof(SLEEP_NOTIFY_STATUS_MSG_STRU) - VOS_MSG_HEAD_LENGTH;

        pstMsg = (SLEEP_NOTIFY_STATUS_MSG_STRU *)VOS_AllocMsg(WUEPS_PID_SLEEP, ulMsgLen);
        if (VOS_NULL_PTR == pstMsg)
        {
            PS_LOG(WUEPS_PID_SLEEP, 0, PS_PRINT_ERROR, "SLEEP_NotifyStateToRegPid: Alloc msg fail.");
            return;
        }

        /* 填充消息内容 */
        pstMsg->ulReceiverPid      = g_stSleepNotifyStateRegPidTbl.aulRegPidTbl[ucLoop];
        pstMsg->enMsgId            = ID_SLEEP_NOTIFY_STATUS_IND;
        pstMsg->enRatMode          = enRatMode;
        pstMsg->enState            = enState;
        if (VOS_TRUE == UPHY_DSDA_GetGsmSlaveDrxFlag(SLEEP_GetModemId()))
        {
            pstMsg->enLPState       = SLEEP_LOWPOWER_STATE_ON;
        }
        else
        {
            pstMsg->enLPState       = SLEEP_LOWPOWER_STATE_OFF;
        }

        g_astSleepNotifyMsgTrack[g_ulSleepNotifyMsgTrackId].ulRegPid    = g_stSleepNotifyStateRegPidTbl.aulRegPidTbl[ucLoop];
        g_astSleepNotifyMsgTrack[g_ulSleepNotifyMsgTrackId].enRatMode   = enRatMode;
        g_astSleepNotifyMsgTrack[g_ulSleepNotifyMsgTrackId].enState     = enState;
        g_astSleepNotifyMsgTrack[g_ulSleepNotifyMsgTrackId].enLPState   = UPHY_DSDA_GetGsmSlaveDrxFlag(SLEEP_GetModemId());
        g_astSleepNotifyMsgTrack[g_ulSleepNotifyMsgTrackId].ulSlice     = OM_GetSlice();

        g_ulSleepNotifyMsgTrackId++;

        if (SLEEP_NOTIFY_MSG_TRACK_NUM == g_ulSleepNotifyMsgTrackId)
        {
            g_ulSleepNotifyMsgTrackId   = 0;
        }

        if (VOS_OK != VOS_SendMsg(WUEPS_PID_SLEEP, pstMsg))
        {
            PS_LOG(WUEPS_PID_SLEEP, 0, PS_PRINT_ERROR, "SLEEP_NotifyStateToRegPid: send msg fail.");
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_GetModemId
 功能描述  : 获取当前所在的Modem ID
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MODEM_ID_ENUM_UINT16
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月14日
    作    者   : L00256032
    修改内容   : V8R1 LowPower&NV_Expand项目新增

*****************************************************************************/
MODEM_ID_ENUM_UINT16 SLEEP_GetModemId(VOS_VOID)
{
#if defined (INSTANCE_2)
    return MODEM_ID_2;
#elif defined (INSTANCE_1)
    return MODEM_ID_1;
#else
    return MODEM_ID_0;
#endif
}

/*****************************************************************************
 函 数 名  : SLEEP_TaskDelay
 功能描述  : 任务延迟接口，CPU循环读取slice值，阻塞性接口
 输入参数  : VOS_UINT32 ulSliceDelay
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月21日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SLEEP_TaskDelay( VOS_UINT32 ulSliceDelay )
{
    VOS_UINT32                          ulSlice;

    ulSlice = OM_GetSlice();

    while((ulSliceDelay) > (OM_GetSlice() - ulSlice))
    {
        ;
    }

    return;
}


/*****************************************************************************
 函 数 名  : SLEEP_IsAwake
 功能描述  : 判断当前是否醒着
 输入参数  : SLEEP_MODE_ENUM_UINT32 enMode
 输出参数  : 无
 返 回 值  : VOS_BOOL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月26日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_BOOL SLEEP_IsAwake( SLEEP_MODE_ENUM_UINT32 enMode )
{
    if ((VOS_RATMODE_GSM == enMode) || (VOS_RATMODE_WCDMA == enMode))
    {
        if (SLEEP_NORMAL_STATE == g_astSleepModeInfo[enMode].enSystemState)
        {
            return VOS_TRUE;
        }
    }
    else if (VOS_RATMODE_1X == enMode)
    {
        if (SLEEP_BBE16_NORMAL_STATE == g_astSleepBBE16ModeInfo[enMode].enSystemState)
        {
            return VOS_TRUE;
        }
    }
    else
    {
        /* error */
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : SLEEP_IsSlaveSleep
 功能描述  : 获取当前模式是否处于从模低功耗状态
 输入参数  : SLEEP_MODE_ENUM_UINT32 enMode  当前模式
 输出参数  : 无
 返 回 值  : VOS_BOOL   VOS_TRUE    当前模式处于从模低功耗态
                        VOS_FALSE   当前模式没有处于从模低功耗状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月30日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_BOOL SLEEP_IsSlaveSleep(SLEEP_MODE_ENUM_UINT32 enMode)
{
    VOS_INT                             lLockLevel;
    VOS_BOOL                            ulRet   = VOS_FALSE;

    lLockLevel = VOS_SplIMP();

    if ((VOS_RATMODE_GSM == enMode) || (VOS_RATMODE_WCDMA == enMode))
    {
        if (SLEEP_SLAVE_LP_STATE == g_astSleepModeInfo[enMode].enSystemState)
        {
            ulRet = VOS_TRUE;
        }
    }
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    else if ((VOS_RATMODE_1X == enMode) || (VOS_RATMODE_HRPD == enMode))
    {
        if ((SLEEP_BBE16_MASTER_LP_STATE == g_astSleepBBE16ModeInfo[VOS_RATMODE_1X].enSystemState)
            ||(SLEEP_BBE16_SLAVE_LP_STATE == g_astSleepBBE16ModeInfo[VOS_RATMODE_1X].enSystemState))
        {
            ulRet = VOS_TRUE;
        }
    }
#endif
    else
    {
    }

    VOS_Splx(lLockLevel);

    return ulRet;
}

/*****************************************************************************
 函 数 名  : SLEEP_AwakeInfoGet
 功能描述  : 获取器件上电流程
 输入参数  : SLEEP_MODE_ENUM_UINT32 enMode  当前模式
             VOS_UINT32 uLen                传入的数组长度
 输出参数  : VOS_UINT32 *pstDrxInfo         上电流程时间信息
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月11日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 SLEEP_AwakeInfoGet( SLEEP_MODE_ENUM_UINT32 enMode, VOS_UINT32 *pstAwakeHWInfo, VOS_UINT32 uLen )
{
    MODEM_ID_ENUM_UINT16                enModem;

    enModem = SLEEP_GetModemId();

    if ( (VOS_NULL_PTR == pstAwakeHWInfo)
        || (enMode > VOS_RATMODE_WCDMA)
        || (uLen < UPHY_OAM_SLEEP_INFO_NUM) )
    {
        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemSet(pstAwakeHWInfo, 0x0, sizeof(VOS_UINT32)*uLen);
    /*lint +e534*/

    pstAwakeHWInfo[0]
        = 0x887755AA;
    pstAwakeHWInfo[1]
        = g_pstSleepNormalState->astRecordItem[enMode][SLEEP_MASTER_BBP_WAKE].aulSlice[g_pstSleepNormalState->astRecordItem[enMode][SLEEP_MASTER_BBP_WAKE].ulCount%SLEEP_RECORD_TRACK_NUM];
    pstAwakeHWInfo[2]
        = g_pstSleepNormalState->astRecordItem[enMode][SLEEP_MASTER_ACTIVATE_START].aulSlice[g_pstSleepNormalState->astRecordItem[enMode][SLEEP_MASTER_ACTIVATE_START].ulCount%SLEEP_RECORD_TRACK_NUM];
    pstAwakeHWInfo[3]
        = g_pstSleepDeviceState->aulDeviceUpSlice[enModem][enMode][PWC_COMM_MODULE_ABB][PWC_COMM_CHANNEL_0];
    pstAwakeHWInfo[4]
        = g_pstSleepDeviceState->aulDeviceUpSlice[enModem][enMode][PWC_COMM_MODULE_BBP_DRX][PWC_COMM_CHANNEL_0];
    pstAwakeHWInfo[5]
        = g_pstSleepDeviceState->aulPLLUpSlice[enModem][enMode][PWC_COMM_MODULE_BBP_DRX][PWC_COMM_CHANNEL_0];
    pstAwakeHWInfo[6]
        = g_pstSleepDeviceState->aulPLLUpSlice[enModem][enMode][PWC_COMM_MODULE_ABB][PWC_COMM_CHANNEL_0];
    pstAwakeHWInfo[7]
        = g_pstSleepDeviceState->aulDeviceUpSlice[enModem][enMode][PWC_COMM_MODULE_RF][PWC_COMM_CHANNEL_0];
    pstAwakeHWInfo[8]
        = g_pstSleepNormalState->astRecordItem[enMode][SLEEP_MASTER_ACTIVATE_END].aulSlice[g_pstSleepNormalState->astRecordItem[enMode][SLEEP_MASTER_ACTIVATE_END].ulCount%SLEEP_RECORD_TRACK_NUM];
    pstAwakeHWInfo[9]
        = g_pstSleepNormalState->astRecordItem[enMode][SLEEP_MASTER_BBP_NORMAL].aulSlice[g_pstSleepNormalState->astRecordItem[enMode][SLEEP_MASTER_BBP_NORMAL].ulCount%SLEEP_RECORD_TRACK_NUM];
    pstAwakeHWInfo[10]
        = g_pstSleepNormalState->astRecordItem[enMode][SLEEP_MASTER_WAKE_PHY_PRE].aulSlice[g_pstSleepNormalState->astRecordItem[enMode][SLEEP_MASTER_WAKE_PHY_PRE].ulCount%SLEEP_RECORD_TRACK_NUM];
    pstAwakeHWInfo[11]
        = g_pstSleepNormalState->astRecordItem[enMode][SLEEP_MASTER_WAKE_PHY].aulSlice[g_pstSleepNormalState->astRecordItem[enMode][SLEEP_MASTER_WAKE_PHY].ulCount%SLEEP_RECORD_TRACK_NUM];
    pstAwakeHWInfo[12]
        = 0xAA557788;

    if ( SLEEP_INFO_RESET_ENABLE == g_bDrxResetFlag )
    {
        VOS_ProtectionReboot(DRX_ACTIVATEHW_ERROR, THIS_FILE_ID, __LINE__, VOS_NULL_PTR, VOS_NULL);
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : SLEEP_VoteLock
 功能描述  : 唤醒投票
 输入参数  : SLEEP_MODE_ENUM_UINT32 enMode
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月30日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SLEEP_VoteLock(SLEEP_MODE_ENUM_UINT32 enMode)
{
#if defined (INSTANCE_2)
    if (VOS_RATMODE_GSM == enMode)
    {
        /*lint -e534*/
        mdrv_pm_wake_lock(PWRCTRL_SLEEP_PS_G2);
        /*lint +e534*/
    }
#elif defined (INSTANCE_1)
    if (VOS_RATMODE_GSM == enMode)
    {
        /*lint -e534*/
        mdrv_pm_wake_lock(PWRCTRL_SLEEP_PS_G1);
        /*lint +e534*/
    }
#else
    if (VOS_RATMODE_GSM == enMode)
    {
        /*lint -e534*/
        mdrv_pm_wake_lock(PWRCTRL_SLEEP_PS_G0);
        /*lint +e534*/
    }
    else if (VOS_RATMODE_WCDMA == enMode)
    {
        /*lint -e534*/
        mdrv_pm_wake_lock(PWRCTRL_SLEEP_PS_W0);
        /*lint +e534*/
    }
    else if (VOS_RATMODE_1X == enMode)
    {
        /*为Austin x模调试打桩，避免modem进入低功耗 */
        /*lint -e534*/
        mdrv_pm_wake_lock(PWRCTRL_SLEEP_1X);
        /*lint +e534*/
    }
    else if (VOS_RATMODE_HRPD == enMode)
    {
        /*为Austin x模调试打桩，避免modem进入低功耗 */
        /*lint -e534*/
        mdrv_pm_wake_lock(PWRCTRL_SLEEP_HRPD);
        /*lint +e534*/
    }
    else
    {
        /* for pclint */
    }
#endif

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_VoteUnlock
 功能描述  : 睡眠投票
 输入参数  : SLEEP_MODE_ENUM_UINT32 enMode
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月30日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SLEEP_VoteUnlock(SLEEP_MODE_ENUM_UINT32 enMode)
{
#if defined (INSTANCE_2)
    if (VOS_RATMODE_GSM == enMode)
    {
        /*lint -e534*/
        mdrv_pm_wake_unlock(PWRCTRL_SLEEP_PS_G2);
        /*lint +e534*/
    }
#elif defined (INSTANCE_1)
    if (VOS_RATMODE_GSM == enMode)
    {
        /*lint -e534*/
        mdrv_pm_wake_unlock(PWRCTRL_SLEEP_PS_G1);
        /*lint +e534*/
    }
#else
    if (VOS_RATMODE_GSM == enMode)
    {
        /*lint -e534*/
        mdrv_pm_wake_unlock(PWRCTRL_SLEEP_PS_G0);
        /*lint +e534*/
    }
    else if (VOS_RATMODE_WCDMA == enMode)
    {
        /*lint -e534*/
        mdrv_pm_wake_unlock(PWRCTRL_SLEEP_PS_W0);
        /*lint +e534*/
    }
    else if (VOS_RATMODE_1X == enMode)
    {
        /*lint -e534*/
        mdrv_pm_wake_unlock(PWRCTRL_SLEEP_1X);
        /*lint +e534*/
    }
    else if (VOS_RATMODE_HRPD == enMode)
    {
        /*lint -e534*/
        mdrv_pm_wake_unlock(PWRCTRL_SLEEP_HRPD);
        /*lint +e534*/
    }
    else
    {
        /* for pclint */
    }
#endif

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_TimeCal
 功能描述  : 获取DRX器件恢复等待时间
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月30日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SLEEP_TimeCal( VOS_VOID )
{
    g_ulSleepRusumeTime = g_stSleepDrxResumeTime.ulAbbPwrRsmTime;

    /* 获取最大时间 */
    if (g_ulSleepRusumeTime < g_stSleepDrxResumeTime.ulBbpPllRsmTime)
    {
        g_ulSleepRusumeTime = g_stSleepDrxResumeTime.ulBbpPllRsmTime;
    }

    if (g_ulSleepRusumeTime < g_stSleepDrxResumeTime.ulRfPwrRsmTime)
    {
        g_ulSleepRusumeTime = g_stSleepDrxResumeTime.ulRfPwrRsmTime;
    }

    if (g_ulSleepRusumeTime < g_stSleepDrxResumeTime.ulPaPwrRsmTime)
    {
        g_ulSleepRusumeTime = g_stSleepDrxResumeTime.ulPaPwrRsmTime;
    }

    /* 换算成Slice单位 */
    g_ulSleepRusumeTime = g_ulSleepRusumeTime/32;

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_TCXOIsrProc
 功能描述  : TCXO定时中断处理函数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月7日
    作    者   : S00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SLEEP_TCXOIsrProc( VOS_VOID )
{
    /*lint -e534*/
    VOS_SmV(g_ulSleepTcxoSem);
    /*lint +e534*/
}

/*****************************************************************************
 函 数 名  : SLEEP_TCXOEnable
 功能描述  : TCXO上电函数
 输入参数  : enMode     :模式，W/G
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月27日
    作    者   : g47350
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SLEEP_TCXOEnable(SLEEP_MODE_ENUM_UINT32 enMode)
{
    VOS_UINT32                          ulTcxoResult;
    VOS_UINT32                          ulTcxoTime;
    VOS_UINT32                          ulTcxoSemTime;

    if ((SLEEP_GU_MODE_TYPE_BUTT <= enMode) || (SLEEP_CHANNEL_BOTH <= SLEEP_TCXO_CHAN(enMode)))
    {
        return;
    }

    /*lint -e534*/
    mdrv_pm_enable_tcxo((PWC_COMM_MODEM_E)SLEEP_TCXO_CHAN(enMode), (PWC_COMM_MODE_E)enMode);
    /*lint +e534*/

    if (PWRCTRL_COMM_OFF == mdrv_pm_get_tcxo_status((PWC_COMM_MODEM_E)SLEEP_TCXO_CHAN(enMode)))
    {
        ulTcxoTime  = g_stSleepDrxResumeTime.ulTcxoRsmTime/1000;

        /* 启动TCXO稳定等待定时器 */
        /*lint -e534*/
        mdrv_pm_start_tcxo_timer((PWC_COMM_MODEM_E)SLEEP_TCXO_CHAN(enMode), (PWC_COMM_MODE_E)enMode,
                                 (PWC_TCXO_FUNCPTR)SLEEP_TCXOIsrProc, VOS_NULL, ulTcxoTime);
        /*lint +e534*/

        /* 等待TCXO稳定,Take信号量最小时间长度必须为1 tick */
        ulTcxoSemTime = (20 < ulTcxoTime) ?
            ulTcxoTime : 20;

        ulTcxoResult    = VOS_SmP(g_ulSleepTcxoSem, ulTcxoSemTime);

        if (VOS_OK != ulTcxoResult)
        {
            /* 异常处理流程 */
            g_pstSleepDeviceState->stDeviceTcxoError.ulCount++;
            g_pstSleepDeviceState->stDeviceTcxoError.ulSlice    = OM_GetSlice();
        }
    }

    /*lint -e534*/
    mdrv_pm_enable_tcxo_rfclk((PWC_COMM_MODEM_E)SLEEP_GetModemId(), (PWC_COMM_MODE_E)enMode, (PWC_COMM_CHANNEL_E)SLEEP_TCXO_CHAN(enMode));
    /*lint +e534*/
    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_TCXODisable
 功能描述  : TCXO下电函数
 输入参数  : enMode     :模式，W/G
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月27日
    作    者   : g47350
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SLEEP_TCXODisable(SLEEP_MODE_ENUM_UINT32 enMode)
{
    if ((SLEEP_GU_MODE_TYPE_BUTT <= enMode) || (SLEEP_CHANNEL_BOTH <= SLEEP_TCXO_CHAN(enMode)))
    {
        return;
    }

    /*lint -e534*/
    mdrv_pm_disable_tcxo_rfclk((PWC_COMM_MODEM_E)SLEEP_GetModemId(), (PWC_COMM_MODE_E)enMode, (PWC_COMM_CHANNEL_E)SLEEP_TCXO_CHAN(enMode));

    /* 关闭TCXO */
    mdrv_pm_disable_tcxo((PWC_COMM_MODEM_E)SLEEP_TCXO_CHAN(enMode), (PWC_COMM_MODE_E)enMode);
    /*lint +e534*/

    return;
}

/*lint -e662 -e661*/

/*****************************************************************************
 函 数 名  : SLEEP_ABBPowerUp
 功能描述  : ABB上电函数
 输入参数  : enMode     :模式，W/G
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月27日
    作    者   : g47350
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SLEEP_ABBPowerUp(SLEEP_MODE_ENUM_UINT32 enMode)
{
#if (FEATURE_ON == FEATURE_MODE_FEM_CHAN_EXT)
    MODEM_ID_ENUM_UINT16                enModem;
    VOS_UINT32                          i;

    enModem = SLEEP_GetModemId();

    if (SLEEP_GU_MODE_TYPE_BUTT <= enMode)
    {
        return;
    }

    for (i = 0; i < PWC_COMM_CHANNEL_BUTT; i++)
    {
        /*lint -e701*/
        if ((SLEEP_BIT_N(i) & SLEEP_ABB_CHAN(enMode)) != VOS_NULL)
        {
            /*lint -e534*/
            SLEEP_DEVICE_POWUP(enModem, enMode, PWC_COMM_MODULE_ABB, i);
            /*lint +e534*/
        }
        /*lint +e701*/
    }
#else
    MODEM_ID_ENUM_UINT16                enModem;

    enModem = SLEEP_GetModemId();

    if ((SLEEP_GU_MODE_TYPE_BUTT <= enMode) || (SLEEP_CHANNEL_BOTH < SLEEP_ABB_CHAN(enMode)))
    {
        return;
    }

    if (SLEEP_CHANNEL_BOTH == SLEEP_ABB_CHAN(enMode))
    {
        /*lint -e534*/
        SLEEP_DEVICE_POWUP(enModem, enMode, PWC_COMM_MODULE_ABB, PWC_COMM_CHANNEL_0);
        SLEEP_DEVICE_POWUP(enModem, enMode, PWC_COMM_MODULE_ABB, PWC_COMM_CHANNEL_1);
        /*lint +e534*/
    }
    else
    {
        /*lint -e534*/
        SLEEP_DEVICE_POWUP(enModem, enMode, PWC_COMM_MODULE_ABB, (PWC_COMM_CHANNEL_E)SLEEP_ABB_CHAN(enMode));
        /*lint +e534*/
    }
#endif

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_ABBPowerDown
 功能描述  : ABB下电函数
 输入参数  : enMode     :模式，W/G
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月27日
    作    者   : g47350
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SLEEP_ABBPowerDown(SLEEP_MODE_ENUM_UINT32 enMode)
{
#if (FEATURE_ON == FEATURE_MODE_FEM_CHAN_EXT)
    MODEM_ID_ENUM_UINT16                enModem;
    VOS_UINT32                          i;

    enModem = SLEEP_GetModemId();

    if (SLEEP_GU_MODE_TYPE_BUTT <= enMode)
    {
        return;
    }

    for (i = 0; i < PWC_COMM_CHANNEL_BUTT; i++)
    {
        /*lint -e701*/
        if ((SLEEP_BIT_N(i) & SLEEP_ABB_CHAN(enMode)) != VOS_NULL)
        {
            /*lint -e534*/
            SLEEP_DEVICE_POWDOWN(enModem, enMode, PWC_COMM_MODULE_ABB, i);
            /*lint +e534*/
        }
        /*lint +e701*/
    }
#else
    MODEM_ID_ENUM_UINT16                enModem;

    enModem = SLEEP_GetModemId();

    if ((SLEEP_GU_MODE_TYPE_BUTT <= enMode) || (SLEEP_CHANNEL_BOTH < SLEEP_ABB_CHAN(enMode)))
    {
        return;
    }

    if (SLEEP_CHANNEL_BOTH == SLEEP_ABB_CHAN(enMode))
    {
        /*lint -e534*/
        SLEEP_DEVICE_POWDOWN(enModem, enMode, PWC_COMM_MODULE_ABB, PWC_COMM_CHANNEL_0);
        SLEEP_DEVICE_POWDOWN(enModem, enMode, PWC_COMM_MODULE_ABB, PWC_COMM_CHANNEL_1);
        /*lint +e534*/
    }
    else
    {
        /*lint -e534*/
        SLEEP_DEVICE_POWDOWN(enModem, enMode, PWC_COMM_MODULE_ABB, (PWC_COMM_CHANNEL_E)SLEEP_ABB_CHAN(enMode));
        /*lint +e534*/
    }
#endif

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_RFPowerUp
 功能描述  : RF上电函数
 输入参数  : enMode     :模式，W/G
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月27日
    作    者   : g47350
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SLEEP_RFPowerUp(SLEEP_MODE_ENUM_UINT32 enMode)
{
#if (FEATURE_ON == FEATURE_MODE_FEM_CHAN_EXT)
    MODEM_ID_ENUM_UINT16                enModem;
    VOS_UINT32                          i;

    enModem = SLEEP_GetModemId();

    if (SLEEP_GU_MODE_TYPE_BUTT <= enMode)
    {
        return;
    }

    for (i = 0; i < PWC_COMM_CHANNEL_BUTT; i++)
    {
        /*lint -e701*/
        if ((SLEEP_BIT_N(i) & SLEEP_RF_CHAN(enMode)) != VOS_NULL)
        {
            /*lint -e534*/
            SLEEP_DEVICE_POWUP(enModem, enMode, PWC_COMM_MODULE_FEM, i);
            SLEEP_DEVICE_POWUP(enModem, enMode, PWC_COMM_MODULE_RF, i);
            /*lint +e534*/
        }
        /*lint +e701*/
    }
#else
    MODEM_ID_ENUM_UINT16                enModem;

    enModem = SLEEP_GetModemId();

    if ((SLEEP_GU_MODE_TYPE_BUTT <= enMode) || (SLEEP_CHANNEL_BOTH < SLEEP_RF_CHAN(enMode)))
    {
        return;
    }

    if (SLEEP_CHANNEL_BOTH == SLEEP_RF_CHAN(enMode))
    {
        /*lint -e534*/
        SLEEP_DEVICE_POWUP(enModem, enMode, PWC_COMM_MODULE_RF, PWC_COMM_CHANNEL_0);
        SLEEP_DEVICE_POWUP(enModem, enMode, PWC_COMM_MODULE_RF, PWC_COMM_CHANNEL_1);
        /*lint +e534*/
    }
    else
    {
        /*lint -e534*/
        SLEEP_DEVICE_POWUP(enModem, enMode, PWC_COMM_MODULE_RF, SLEEP_RF_CHAN(enMode));
        /*lint +e534*/
    }
#endif

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_RFPowerDown
 功能描述  : RF下电函数
 输入参数  : enMode     :模式，W/G
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月27日
    作    者   : g47350
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SLEEP_RFPowerDown(SLEEP_MODE_ENUM_UINT32 enMode)
{
#if (FEATURE_ON == FEATURE_MODE_FEM_CHAN_EXT)
    MODEM_ID_ENUM_UINT16                enModem;
    VOS_UINT32                          i;

    enModem = SLEEP_GetModemId();

    if (SLEEP_GU_MODE_TYPE_BUTT <= enMode)
    {
        return;
    }

    for (i = 0; i < PWC_COMM_CHANNEL_BUTT; i++)
    {
        /*lint -e701*/
        if ((SLEEP_BIT_N(i) & SLEEP_RFCLK_CHAN(enMode)) != VOS_NULL)
        {
            /*lint -e534*/
            SLEEP_DEVICEPLL_POWDOWN((PWC_COMM_MODEM_E)enModem, (PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_RF, i);
            /*lint +e534*/
        }

        if ((SLEEP_BIT_N(i) & SLEEP_RF_CHAN(enMode)) != VOS_NULL)
        {
            /*lint -e534*/
            SLEEP_DEVICE_POWDOWN(enModem, enMode, PWC_COMM_MODULE_RF, i);
            SLEEP_DEVICE_POWDOWN(enModem, enMode, PWC_COMM_MODULE_FEM, i);
            /*lint +e534*/
        }
        /*lint +e701*/
    }
#else
    MODEM_ID_ENUM_UINT16                enModem;

    enModem = SLEEP_GetModemId();

    if ((SLEEP_GU_MODE_TYPE_BUTT <= enMode) || (SLEEP_CHANNEL_BOTH < SLEEP_RF_CHAN(enMode)))
    {
        return;
    }

    if (SLEEP_CHANNEL_BOTH == SLEEP_RF_CHAN(enMode))
    {
        /*lint -e534*/
        SLEEP_DEVICE_POWDOWN(enModem, enMode, PWC_COMM_MODULE_RF, PWC_COMM_CHANNEL_0);
        SLEEP_DEVICE_POWDOWN(enModem, enMode, PWC_COMM_MODULE_RF, PWC_COMM_CHANNEL_1);
        /*lint +e534*/
    }
    else
    {
        /*lint -e534*/
        SLEEP_DEVICE_POWDOWN(enModem, enMode, PWC_COMM_MODULE_RF, (PWC_COMM_CHANNEL_E)SLEEP_RF_CHAN(enMode));
        /*lint +e534*/
    }
#endif

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_RFFECfgPowerUp
 功能描述  : RF上电函数
 输入参数  : enMode     :模式，W/G
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月17日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SLEEP_RFFECfgPowerUp(SLEEP_MODE_ENUM_UINT32 enMode)
{
#if (FEATURE_ON == FEATURE_MODE_FEM_CHAN_EXT)
    MODEM_ID_ENUM_UINT16                enModem;
    VOS_UINT32                          i;

    enModem = SLEEP_GetModemId();

    if (SLEEP_GU_MODE_TYPE_BUTT <= enMode)
    {
        return;
    }

    for (i = 0; i < PWC_COMM_CHANNEL_BUTT; i++)
    {
        /*lint -e701*/
        if ((SLEEP_BIT_N(i) & SLEEP_RFCLK_CHAN(enMode)) != VOS_NULL)
        {
            /*lint -e534*/
            SLEEP_DEVICEPLL_POWUP((PWC_COMM_MODEM_E)enModem, (PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_RF, i);
            /*lint +e534*/
        }

        if ((SLEEP_BIT_N(i) & SLEEP_RF_CHAN(enMode)) != VOS_NULL)
        {
            /*lint -e534*/
            mdrv_rffe_cfg_on_power_up((PWC_COMM_MODE_E)enMode, (PWC_COMM_MODEM_E)enModem, (PWC_COMM_CHANNEL_E)i);
            /*lint +e534*/
        }
        /*lint +e701*/
    }
#else

#endif

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_RFFECfgPowerDown
 功能描述  : RF下电函数
 输入参数  : enMode     :模式，W/G
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月17日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SLEEP_RFFECfgPowerDown(SLEEP_MODE_ENUM_UINT32 enMode)
{
#if (FEATURE_ON == FEATURE_MODE_FEM_CHAN_EXT)
    MODEM_ID_ENUM_UINT16                enModem;
    VOS_UINT32                          i;

    enModem = SLEEP_GetModemId();

    if (SLEEP_GU_MODE_TYPE_BUTT <= enMode)
    {
        return;
    }

    for (i = 0; i < PWC_COMM_CHANNEL_BUTT; i++)
    {
        /*lint -e701*/
        if ((SLEEP_BIT_N(i) & SLEEP_RF_CHAN(enMode)) != VOS_NULL)
        {
            /*lint -e534*/
            mdrv_rffe_cfg_on_power_down((PWC_COMM_MODE_E)enMode, (PWC_COMM_MODEM_E)enModem, (PWC_COMM_CHANNEL_E)i);
            /*lint +e534*/
        }
        /*lint +e701*/
    }
#else

#endif

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_ABBPllEnable
 功能描述  : ABBPLL使能函数
 输入参数  : enMode     :模式，W/G
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月27日
    作    者   : g47350
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SLEEP_ABBPllEnable(SLEEP_MODE_ENUM_UINT32 enMode)
{
#if (FEATURE_ON == FEATURE_MODE_FEM_CHAN_EXT)
    MODEM_ID_ENUM_UINT16                enModem;
    VOS_UINT32                          i;

    enModem = SLEEP_GetModemId();

    if (SLEEP_GU_MODE_TYPE_BUTT <= enMode)
    {
        return;
    }

    for (i = 0; i < PWC_COMM_CHANNEL_BUTT; i++)
    {
        /*lint -e701*/
        if ((SLEEP_BIT_N(i) & SLEEP_ABB_CHAN(enMode)) != VOS_NULL)
        {
            /*lint -e534*/
            SLEEP_DEVICEPLL_POWUP(enModem, enMode, PWC_COMM_MODULE_ABB, i);
            /*lint +e534*/
        }
        /*lint +e701*/
    }
#else
    MODEM_ID_ENUM_UINT16                enModem;

    enModem = SLEEP_GetModemId();

    if ((SLEEP_GU_MODE_TYPE_BUTT <= enMode) || (SLEEP_CHANNEL_BOTH < SLEEP_ABB_CHAN(enMode)))
    {
        return;
    }

    if (SLEEP_CHANNEL_BOTH == SLEEP_ABB_CHAN(enMode))
    {
        /*lint -e534*/
        SLEEP_DEVICEPLL_POWUP(enModem, (PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_ABB, PWC_COMM_CHANNEL_0);
        SLEEP_DEVICEPLL_POWUP(enModem, (PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_ABB, PWC_COMM_CHANNEL_1);
        /*lint +e534*/
    }
    else
    {
        /*lint -e534*/
        SLEEP_DEVICEPLL_POWUP(enModem, (PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_ABB, (PWC_COMM_CHANNEL_E)SLEEP_ABB_CHAN(enMode));
        /*lint +e534*/
    }
#endif

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_ABBPllDisable
 功能描述  : ABBPLL去使能函数
 输入参数  : enMode     :模式，W/G
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月27日
    作    者   : g47350
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SLEEP_ABBPllDisable(SLEEP_MODE_ENUM_UINT32 enMode)
{
#if (FEATURE_ON == FEATURE_MODE_FEM_CHAN_EXT)
    MODEM_ID_ENUM_UINT16                enModem;
    VOS_UINT32                          i;

    enModem = SLEEP_GetModemId();

    if (SLEEP_GU_MODE_TYPE_BUTT <= enMode)
    {
        return;
    }

    for (i = 0; i < PWC_COMM_CHANNEL_BUTT; i++)
    {
        /*lint -e701*/
        if ((SLEEP_BIT_N(i) & SLEEP_ABB_CHAN(enMode)) != VOS_NULL)
        {
            /*lint -e534*/
            SLEEP_DEVICEPLL_POWDOWN(enModem, enMode, PWC_COMM_MODULE_ABB, i);
            /*lint +e534*/
        }
        /*lint +e701*/
    }
#else
    MODEM_ID_ENUM_UINT16                enModem;

    enModem = SLEEP_GetModemId();

    if ((SLEEP_GU_MODE_TYPE_BUTT <= enMode) || (SLEEP_CHANNEL_BOTH < SLEEP_ABB_CHAN(enMode)))
    {
        return;
    }

    if (SLEEP_CHANNEL_BOTH == SLEEP_ABB_CHAN(enMode))
    {
        /*lint -e534*/
        SLEEP_DEVICEPLL_POWDOWN(enModem, (PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_ABB, PWC_COMM_CHANNEL_0);
        SLEEP_DEVICEPLL_POWDOWN(enModem, (PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_ABB, PWC_COMM_CHANNEL_1);
        /*lint +e534*/
    }
    else
    {
        /*lint -e534*/
        SLEEP_DEVICEPLL_POWDOWN(enModem, (PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_ABB, (PWC_COMM_CHANNEL_E)SLEEP_ABB_CHAN(enMode));
        /*lint +e534*/
    }
#endif

    return;
}


VOS_UINT32 SLEEP_GBBPClkSrcSelect(VOS_VOID)
{
    MODEM_ID_ENUM_UINT16                enModem;
    VOS_UINT32                          ulRet = 0;
#if (FEATURE_ON == FEATURE_MODE_FEM_CHAN_EXT)
    VOS_UINT32                          i;
#endif

    enModem = SLEEP_GetModemId();

#if (FEATURE_ON == FEATURE_MODE_FEM_CHAN_EXT)

    for (i = 0; i < PWC_COMM_CHANNEL_BUTT; i++)
    {
        /*lint -e701*/
        if ((SLEEP_BIT_N(i) & SLEEP_ABB_CHAN(PWC_COMM_MODE_GSM)) != VOS_NULL)
        {
            ulRet |= mdrv_pm_gbbp_select_clksrc((PWC_COMM_MODEM_E)enModem, (PWC_COMM_CHANNEL_E)i);
        }
        /*lint +e701*/
    }
#else
    if (SLEEP_CHANNEL_BOTH == SLEEP_ABB_CHAN(PWC_COMM_MODE_GSM))
    {
        ulRet = mdrv_pm_gbbp_select_clksrc((PWC_COMM_MODEM_E)enModem, (PWC_COMM_CHANNEL_E)SLEEP_CHANNEL_ZERO);
        ulRet |= mdrv_pm_gbbp_select_clksrc((PWC_COMM_MODEM_E)enModem, (PWC_COMM_CHANNEL_E)SLEEP_CHANNEL_ONE);
    }
    else
    {
        ulRet = mdrv_pm_gbbp_select_clksrc((PWC_COMM_MODEM_E)enModem, (PWC_COMM_CHANNEL_E)SLEEP_ABB_CHAN(PWC_COMM_MODE_GSM));
    }
#endif

    return ulRet;
}

/*lint +e662 +e661*/

/*****************************************************************************
 函 数 名  : SLEEP_PowerUp
 功能描述  : 上电RTT子系统.
 输入参数  : enMode     :模式，W/G

 输出参数  : 无

 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年07月31日
    作    者   : g47350
    修改内容   : V900R001项目新增函数

*****************************************************************************/
VOS_VOID SLEEP_PowerUp(SLEEP_MODE_ENUM_UINT32 enMode)
{
    MODEM_ID_ENUM_UINT16                enModem;
    VOS_UINT32                          ulSlice;

    enModem = SLEEP_GetModemId();

    /* 打开TXCO */
    SLEEP_TCXOEnable(enMode);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* 加载BBE16 */
    SLEEP_BBE16PowerUp(enMode);
#endif

    /* 上电RF */
    SLEEP_RFPowerUp(enMode);

    /* 上电ABB */
    SLEEP_ABBPowerUp(enMode);

    /* 打开ABB PLL */
    SLEEP_ABBPllEnable(enMode);

    /* V8R1上BBP CS分区电源随外设开关，所以在解复位BBP CS分区前，需要先打开门控和时钟*/
    /* 打开BBP PLL */

    /*lint -e534*/
    SLEEP_DEVICEPLL_POWUP((PWC_COMM_MODEM_E)enModem, (PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_BBP_DRX, PWC_COMM_CHANNEL_0);

    /* 打开BBP外设时钟 */
    mdrv_pm_enable_bbpclk((PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_BBP_DRX, (PWC_COMM_MODEM_E)enModem, PWC_COMM_CHANNEL_0);

    /* 上电BBP */
    SLEEP_DEVICE_POWUP(enModem, enMode, PWC_COMM_MODULE_BBP_DRX, PWC_COMM_CHANNEL_0);
    /*lint +e534*/

    ulSlice = OM_GetSlice();

    /* 换算成Slice等待器件稳定 */
    while((g_ulSleepRusumeTime) > (OM_GetSlice() - ulSlice))
    {
        ;
    }

    SLEEP_RFFECfgPowerUp(enMode);

    if (VOS_RATMODE_WCDMA == enMode)
    {
        HPA_Conncet3GISR();

#if (FEATURE_GUBBP_HANDSHAKE == FEATURE_ON)
        /* 写入握手最大延迟等待时间 */
        HPA_Write32Reg(WBBP_SWITCH_DELAY_MAX_1CARD_ADDR, SLEEP_BBP_HANDSHAKE_MAX_DELAY);
#endif
    }
    else if (VOS_RATMODE_GSM == enMode)
    {
#if defined (INSTANCE_2)
        HPA_Conncet2GISR2();
#elif defined (INSTANCE_1)
        HPA_Conncet2GISR1();
#else
        HPA_Conncet2GISR0();
#endif

#if (FEATURE_GUDRX_NEWVERSION == FEATURE_ON)
        /* 写入握手最大延迟等待时间 */
        HPA_Write32Reg(GBBP_WAIT_MAX_LEN_ADDR, SLEEP_BBP_HANDSHAKE_MAX_DELAY);
#endif
    }
    else if ((VOS_RATMODE_1X == enMode)||(VOS_RATMODE_HRPD == enMode))
    {
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if (VOS_FALSE == g_ulConnectFlag)
        {
            g_ulConnectFlag = VOS_TRUE;

            /* CDMA模式使用 */
            HPA_ConnectCdmaISR();
        }
#endif
    }
    else
    {
        /* for pclint */
    }

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_ReadBaseCntSym
 功能描述  : 读取当前Base Cnt信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月28日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 SLEEP_ReadBaseCntChip( VOS_VOID )
{
    VOS_UINT32                          ulBaseSlot;
    VOS_UINT32                          ulBaseChip;

    /* 读取BBP绝对时刻计数器，第一次读产生获取指令，第二次读为延时，第三次获取最终结果 */
    ulBaseSlot  = HPA_Read32Reg(WBBP_SYS_BASE_CNT_ADDR);
    ulBaseSlot  = HPA_Read32Reg(WBBP_SYS_BASE_CNT_ADDR);
    ulBaseSlot  = HPA_Read32Reg(WBBP_SYS_BASE_CNT_ADDR);

    /* 将绝对时刻换算成CHIP单位 */
    ulBaseChip  = (ulBaseSlot>>16)&0xFFF;
    ulBaseSlot  = (ulBaseSlot>>28)&0xF;
    ulBaseChip  += ulBaseSlot*2560;

    return ulBaseChip;
}

/*****************************************************************************
 函 数 名  : SLEEP_ResumeReg
 功能描述  : BBP上电后，恢复WBBP寄存器内容
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月30日
    作    者   : s00207770
    修改内容   : 新生成函数
  2.日    期   : 2013年10月28日
    作    者   : s00207770
    修改内容   : 规避BBP SFN加减1问题

*****************************************************************************/
VOS_VOID SLEEP_ResumeReg( VOS_VOID )
{
#if (VOS_OS_VER != VOS_WIN32)
    SLEEP_NOR_STATE_TRACK(VOS_RATMODE_WCDMA, SLEEP_MASTER_BBP_RESUME_START);

    /*打开WBBP内部子模块的时钟和解复位*/
    HPA_Write32Reg(WBBP_SYS_RST_CON_W1_ADDR, 0xffff0000);

    /*将WBBP定时切换到CPICH态*/
    HPA_Write32RegMask(WBBP_TIMING_MODE_ADDR, 0x01);
    HPA_Write32RegMask(WBBP_TIMING_CFG_READY_ADDR, 0x01);

    /*恢复定时模块的服务小区CPICH最早径信息*/
    HPA_Write32Reg(WBBP_TRACE_CPI_FRM_POS_ADDR, g_ulSleepBBPPosValue);
    HPA_Write32Reg(WBBP_PATH_CFG_READY_ADDR, 1);

    SLEEP_NOR_STATE_TRACK(VOS_RATMODE_WCDMA, SLEEP_MASTER_BBP_RESUME_END);
#endif
}

#if (FEATURE_GUC_BBP_TRIG == FEATURE_OFF)
/*****************************************************************************
 函 数 名  : SLEEP_ForceWakeProtected
 功能描述  : 判断正常唤醒最近是否到来
 输入参数  : void
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID SLEEP_DMACapRelease( VOS_VOID )
{
    if (VOS_TRUE == g_ulIsWaitingDMACap)
    {
        /*lint -e534*/
        VOS_SmV(g_ulSleepDMACapSem);
        /*lint +e534*/
    }
}
#endif

/*****************************************************************************
 函 数 名  : SLEEP_ForceWakeProtected
 功能描述  : 判断正常唤醒最近是否到来
 输入参数  : void
 输出参数  : 无
 返 回 值  : VOS_OK  - 不会到来，可以正常唤醒BPP
             VOS_ERR - 马上来，不用唤醒BPP
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 SLEEP_ForceWakeProtected(VOS_VOID)
{
    VOS_UINT32  ulWakeSfn;
    VOS_UINT32  ulWakeSlot;
    VOS_UINT32  ulSysSfn;
    VOS_UINT32  ulSysSlot;

    /*当前时刻帧号[11:0]，偏移时隙[31:28]*/
    ulSysSfn  = HPA_Read32Reg(WBBP_SYS_CNT_SLEEP_1CARD_ADDR);
    ulSysSlot  = ulSysSfn>>28;
    ulSysSfn  &= 0xfff;
    ulSysSlot  = (ulSysSfn*SLEEP_SLOT_LEN) + ulSysSlot;

    /*正常唤醒时刻帧号[11:0]*/
    ulWakeSfn = HPA_Read32Reg(WBBP_CK_WAKE_SFN_1CARD_ADDR)&0xfff;
    /*正常唤醒时刻的偏移时隙[19:16]*/
    ulWakeSlot = HPA_Read32Reg(WBBP_CK_WAKE_CNT_1CARD_ADDR);
    ulWakeSlot = (ulWakeSlot>>16)&0xf;
    /*防止在执行该函数期间，正常中断已经来了，故将正常唤醒时刻延后2个时隙*/
    ulWakeSlot = ((ulWakeSfn*SLEEP_SLOT_LEN) + ulWakeSlot) + SLEEP_WAKE_DELAY;

    /*考虑ulWakeCnt反转的情况*/
    if (ulWakeSlot < ulSysSlot)
    {
        ulWakeSlot += SLEEP_SFN_CYCLE_LEN;
    }

    /*判断在4个时隙内是否有正常WAKE中断上报*/
    if ((ulSysSlot + (SLEEP_WAKE_DELAY + SLEEP_WAKE_INTERVAL))
        < ulWakeSlot)
    {
        return VOS_OK;
    }

    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : SLEEP_DeactivateHw
 功能描述  : 下电RTT子系统.
 输入参数  : enMode     :模式，W/G

 输出参数  : 无

 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年07月31日
    作    者   : g47350
    修改内容   : V900R001项目新增函数

*****************************************************************************/
VOS_VOID SLEEP_DeactivateHw(SLEEP_MODE_ENUM_UINT32 enMode)
{
    MODEM_ID_ENUM_UINT16                enModem;
#if (FEATURE_GUC_BBP_TRIG == FEATURE_OFF)
    VOS_INT                             lIntLevel;
#endif

    enModem = SLEEP_GetModemId();

#if (FEATURE_GUC_BBP_TRIG == FEATURE_ON)
    PsRegGUCBBPDbgDisable(enModem, enMode);
#endif

    if (VOS_RATMODE_WCDMA == enMode)
    {
        HPA_3GIsrDisable(enModem);
    }
    else
    {
        HPA_2GIsrDisable(enModem);
    }

#if (FEATURE_GUC_BBP_TRIG == FEATURE_OFF)

    lIntLevel   = VOS_SplIMP();

    if (VOS_TRUE == PsRegGetDmaCaptureStatus(enModem))
    {
        g_ulIsWaitingDMACap = VOS_TRUE;
    }

    VOS_Splx(lIntLevel);

    if (VOS_TRUE == g_ulIsWaitingDMACap)
    {
        if(VOS_OK != VOS_SmP(g_ulSleepDMACapSem, 20))
        {
            g_pstSleepDeviceState->stDMACapError.ulCount++;
            g_pstSleepDeviceState->stDMACapError.ulSlice = OM_GetSlice();
        }

        g_ulIsWaitingDMACap = VOS_FALSE;
    }

#endif

    /* BBP寄存器备份 */
    if (VOS_RATMODE_WCDMA == enMode)
    {
        g_ulSleepBBPPosValue  = HPA_Read32Reg(WBBP_TRACE_CPI_FRM_POS_ADDR);
    }

    /* 下电BBP */
    /*lint -e534*/
    SLEEP_DEVICE_POWDOWN(enModem, enMode, PWC_COMM_MODULE_BBP_DRX, PWC_COMM_CHANNEL_0);

    /* 关闭BBP外设时钟 */
    mdrv_pm_disable_bbpclk((PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_BBP_DRX, (PWC_COMM_MODEM_E)enModem, PWC_COMM_CHANNEL_0);

    /* 关闭BBP PLL */
    SLEEP_DEVICEPLL_POWDOWN((PWC_COMM_MODEM_E)enModem, (PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_BBP_DRX, PWC_COMM_CHANNEL_0);
    /*lint +e534*/

    /* 关闭ABB PLL */
    SLEEP_ABBPllDisable(enMode);

    /* 下电ABB */
    SLEEP_ABBPowerDown(enMode);

    /* 下电RF */
    SLEEP_RFPowerDown(enMode);
    SLEEP_RFFECfgPowerDown(enMode);

    /* 关闭TCXO */
    SLEEP_TCXODisable(enMode);

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_ActivateHw
 功能描述  : 上电RTT子系统.
 输入参数  : enMode     :模式，W/G

 输出参数  : 无

 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年07月31日
    作    者   : g47350
    修改内容   : V900R001项目新增函数

*****************************************************************************/
VOS_VOID SLEEP_ActivateHw(SLEEP_MODE_ENUM_UINT32 enMode)
{
    MODEM_ID_ENUM_UINT16                enModem;
    VOS_UINT32                          ulSlice;

    enModem = SLEEP_GetModemId();

    SLEEP_NOR_STATE_TRACK(enMode, SLEEP_MASTER_ACTIVATE_START);

    /* 打开TCXO */
    SLEEP_TCXOEnable(enMode);

    SLEEP_WAKE_SLICE_RECORD(5);

    /* 上电RF */
    SLEEP_RFPowerUp(enMode);

    SLEEP_WAKE_SLICE_RECORD(6);

    /* 上电ABB */
    SLEEP_ABBPowerUp(enMode);

    /* 打开ABB PLL */
    SLEEP_ABBPllEnable(enMode);

    /* V8R1上BBP CS分区电源随外设开关，所以在解复位BBP CS分区前，需要先打开门控和时钟*/
    /* 打开BBP PLL */
    /*lint -e534*/
    SLEEP_DEVICEPLL_POWUP((PWC_COMM_MODEM_E)enModem, (PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_BBP_DRX, PWC_COMM_CHANNEL_0);

    /* 打开BBP外设时钟 */
    mdrv_pm_enable_bbpclk((PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_BBP_DRX, (PWC_COMM_MODEM_E)enModem, PWC_COMM_CHANNEL_0);

    /* 上电BBP */
    SLEEP_DEVICE_POWUP(enModem, enMode, PWC_COMM_MODULE_BBP_DRX, PWC_COMM_CHANNEL_0);
    /*lint +e534*/

    ulSlice = OM_GetSlice();

    /* 换算成Slice等待器件稳定 */
    while((g_ulSleepRusumeTime) > (OM_GetSlice() - ulSlice))
    {
        ;
    }

    SLEEP_RFFECfgPowerUp(enMode);

    /* BBP寄存器恢复 */
    if (VOS_RATMODE_WCDMA == enMode)
    {
        SLEEP_ResumeReg();
    }

    if (VOS_RATMODE_WCDMA == enMode)
    {
        if (BBP_ERROR_VALUE == HPA_Read32Reg(WBBP_ARM_INT01_MASK_ADDR))
        {
            if (VOS_NULL_PTR != g_pstSleepDeviceState)
            {
                g_pstSleepDeviceState->astDevicePowerError[enMode].ulCount++;
                g_pstSleepDeviceState->astDevicePowerError[enMode].ulSlice  = OM_GetSlice();
            }
        }

        HPA_3GIsrEnable(enModem);
    }
    else
    {
        if (BBP_ERROR_VALUE == HPA_Read32Reg(g_aulGUCBBPRegAddr[INT_MASK][enModem][enMode]))
        {
            ulSlice = OM_GetSlice();

            if (VOS_NULL_PTR != g_pstSleepDeviceState)
            {
                g_pstSleepDeviceState->aulABBState[0]       = ulSlice;
            }

            while (SLEEP_BBP_ERROR_TIMEOUT > (OM_GetSlice() - ulSlice))
            {
                if (BBP_ERROR_VALUE != HPA_Read32Reg(g_aulGUCBBPRegAddr[INT_MASK][enModem][enMode]))
                {
                    break;
                }
            }

            if (VOS_NULL_PTR != g_pstSleepDeviceState)
            {
                g_pstSleepDeviceState->aulABBState[1]   = OM_GetSlice();

                g_pstSleepDeviceState->astDevicePowerError[enMode].ulCount++;
                g_pstSleepDeviceState->astDevicePowerError[enMode].ulSlice  = OM_GetSlice();

                VOS_ProtectionReboot(DRX_REPORT_BBP_READ_ERROR, (VOS_INT32)g_pstSleepDeviceState->aulABBState[0], (VOS_INT32)g_pstSleepDeviceState->aulABBState[1], VOS_NULL_PTR, VOS_NULL);
             }
        }

        HPA_2GIsrEnable(enModem);
    }

    SLEEP_NOR_STATE_TRACK(enMode, SLEEP_MASTER_ACTIVATE_END);

#if (FEATURE_GUC_BBP_TRIG == FEATURE_ON)
    PsRegGUCBBPDbgEnable(enModem, enMode);
#endif

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_WakePhy
 功能描述  : 通过发送消息唤醒GUPHY.
 输入参数  : ulMsgId    :消息ID，区分主模/从模唤醒
             enMode     :唤醒的模式，W/G
             enWakeType :唤醒类型，强制唤醒/正常唤醒

 输出参数  : 无

 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年07月31日
    作    者   : g47350
    修改内容   : V900R001项目新增函数
  2.日    期   : 2014年07月25日
    作    者   : s00207770
    修改内容   : V800R100增加唤醒时间可维可测信息，发送到PC工具侧

*****************************************************************************/
VOS_UINT32 SLEEP_WakePhy(VOS_UINT32 ulMsgId, SLEEP_MODE_ENUM_UINT32 enMode, UPHY_OAM_WAKE_TYPE_ENUM_UINT32 enWakeType)
{
    UPHY_OAM_WAKE_CMD_STRU               *pstPhyMsg;

    /* 申请消息内存 */
    pstPhyMsg = (UPHY_OAM_WAKE_CMD_STRU*)VOS_AllocMsg(WUEPS_PID_AWAKE,
                    sizeof(UPHY_OAM_WAKE_CMD_STRU) + sizeof(SLEEP_NORMAL_STATE_RECORD_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 申请失败 */
    if (VOS_NULL_PTR == pstPhyMsg)
    {
        return VOS_ERR;
    }

    pstPhyMsg->ulReceiverPid = DSP_PID_WAKE;

    pstPhyMsg->enMsgId       = (VOS_UINT16)ulMsgId;
    pstPhyMsg->enModem       = SLEEP_GetModemId();
    pstPhyMsg->enRatMode     = enMode;
    pstPhyMsg->enWakeType    = enWakeType;

    /*lint -e534 -e419*/
    VOS_MemCpy(&(pstPhyMsg->pRecordInfo[0]), (VOS_VOID *)g_pstSleepNormalState, sizeof(SLEEP_NORMAL_STATE_RECORD_STRU));
    /*lint +e534 +e419*/

    /* 发送消息 */
    if (VOS_OK != VOS_SendMsg(WUEPS_PID_AWAKE, pstPhyMsg))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : SLEEP_IsrProc
 功能描述  : 将SLEEP模块中断处理转换为消息交互
 输入参数  : ulMsgId: 消息ID对应不同的中断
             enMode : 模块,W/G

 输出参数  : 无

 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月09日
    作    者   : s00207770
    修改内容   : 低功耗任务优先级拆分项目新增函数

*****************************************************************************/
VOS_VOID SLEEP_AwakeIsrProc(VOS_UINT32 ulMsgId, SLEEP_MODE_ENUM_UINT32 enMode)
{
    VOS_INT                             lLockLevel;
    SLEEP_ISR_MSG_STRU                 *pstIsrMsg;

    lLockLevel = VOS_SplIMP();

    /* 禁止深睡投票 */
    SLEEP_VoteLock(enMode);

    /* 中断序列记录 */
    SLEEP_ISR_RECORD(ulMsgId, enMode);

    /* 分配消息内存 */
    pstIsrMsg = (SLEEP_ISR_MSG_STRU*)VOS_AllocMsg(WUEPS_PID_AWAKE,
                    sizeof(SLEEP_ISR_MSG_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstIsrMsg)
    {
        VOS_Splx(lLockLevel);

        return;
    }

    pstIsrMsg->ulReceiverPid = WUEPS_PID_AWAKE;
    pstIsrMsg->usMsgId       = (VOS_UINT16)ulMsgId;
    pstIsrMsg->enRatMode     = enMode;
    pstIsrMsg->ulSlice       = OM_GetSlice();

    if (VOS_OK != VOS_SendMsg(WUEPS_PID_AWAKE, pstIsrMsg))
    {
        /*; */
    }

    VOS_Splx(lLockLevel);

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_SleepIsrProc
 功能描述  : 将SLEEP模块中断处理转换为消息交互
 输入参数  : ulMsgId: 消息ID对应不同的中断
             enMode : 模块,W/G

 输出参数  : 无

 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年07月31日
    作    者   : g47350
    修改内容   : V900R001项目新增函数
  2.日    期   : 2015年03月09日
    作    者   : s00207770
    修改内容   : 低功耗任务优先级拆分项目修改函数

*****************************************************************************/
VOS_VOID SLEEP_SleepIsrProc(VOS_UINT32 ulMsgId, SLEEP_MODE_ENUM_UINT32 enMode)
{
    VOS_INT                             lLockLevel;
    SLEEP_ISR_MSG_STRU                 *pstIsrMsg;

    lLockLevel = VOS_SplIMP();

    /* 禁止深睡投票 */
    SLEEP_VoteLock(enMode);

    /* 中断序列记录 */
    SLEEP_ISR_RECORD(ulMsgId, enMode);

    /* 分配消息内存 */
    pstIsrMsg = (SLEEP_ISR_MSG_STRU*)VOS_AllocMsg(WUEPS_PID_SLEEP,
                    sizeof(SLEEP_ISR_MSG_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstIsrMsg)
    {
        VOS_Splx(lLockLevel);

        return;
    }

    pstIsrMsg->ulReceiverPid = WUEPS_PID_SLEEP;
    pstIsrMsg->usMsgId       = (VOS_UINT16)ulMsgId;
    pstIsrMsg->enRatMode     = enMode;
    pstIsrMsg->ulSlice       = OM_GetSlice();

    if (VOS_OK != VOS_SendMsg(WUEPS_PID_SLEEP, pstIsrMsg))
    {
        /*; */
    }

    VOS_Splx(lLockLevel);

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_32KClkMsgProc
 功能描述  : 接收到32K时钟切换中断消息处理.
 输入参数  : pstMsg 消息体

 输出参数  : 无

 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年07月31日
    作    者   : g47350
    修改内容   : V900R001项目新增函数

*****************************************************************************/
VOS_VOID SLEEP_32KClkMsgProc(MsgBlock *pstMsg)
{
    UPHY_OAM_SLEEP_IND_STRU             *pstPhyReq;
    SLEEP_MODE_ENUM_UINT32              enMode;
#ifdef FEATURE_DSP2ARM
    VOS_UINT32                          ulQueueSize = 0;
#endif
    MSG_CB                             *pMsg;
    VOS_ULONG                           ulLockLevel;

    pstPhyReq = (UPHY_OAM_SLEEP_IND_STRU*)pstMsg;

    enMode    = pstPhyReq->enRatMode;

    /* 参数检测 */
    if (SLEEP_GU_MODE_TYPE_BUTT <= enMode)
    {
        /* 异常打印和记录 */
        PS_LOG1(WUEPS_PID_SLEEP, 0, PS_PRINT_ERROR, "SLEEP_32KClkMsgProc: Mode para is wrong.", (VOS_INT32)enMode);
        return;
    }

    (VOS_VOID)VOS_SmP(g_ulSleepSem, 0);

    /* 假如当前系统为NORMAL态则切换为主模睡眠暂态 */
    if (SLEEP_NORMAL_STATE == g_astSleepModeInfo[enMode].enSystemState)
    {
        g_astSleepModeInfo[enMode].enSystemState = SLEEP_MASTER_TEMP_LP_STATE;

        /*lint -e534*/
        VOS_SmV(g_ulSleepSem);
        /*lint +e534*/

        return;
    }

    /* 假如当前系统为主模睡眠暂态则切换为主模睡眠态 */
    if (SLEEP_MASTER_TEMP_LP_STATE == g_astSleepModeInfo[enMode].enSystemState)
    {
        SLEEP_WAKE_SLICE_RECORD(2);

        /* 下电RTT子系统 */
        SLEEP_DeactivateHw(enMode);

        SLEEP_NOR_STATE_TRACK(enMode, SLEEP_MASTER_LP);

        g_astSleepModeInfo[enMode].enSystemState = SLEEP_MASTER_LP_STATE;

#ifdef FEATURE_DSP2ARM
        VOS_SpinLockIntLock(&g_stSleepSpinLock, ulLockLevel);

        /* 获取GUPHY消息队列中消息个数 */
        if (VOS_RATMODE_WCDMA == enMode)
        {
            ulQueueSize = VOS_GetQueueSizeFromFid(DSP_FID_WPHY);
        }
        else
        {
            ulQueueSize = VOS_GetQueueSizeFromFid(DSP_FID_GPHY);
        }

        /* 如果消息队列中有消息，则进入强制唤醒流程 */
        if (0 < ulQueueSize)
        {
            if (VOS_RATMODE_WCDMA == enMode)
            {
                pMsg   = (MSG_CB *)VOS_FixedQueueReadMsg(DSP_FID_WPHY);
            }
            else
            {
                pMsg   = (MSG_CB *)VOS_FixedQueueReadMsg(DSP_FID_GPHY);
            }

            if (VOS_NULL_PTR != pMsg)
            {
#if defined (INSTANCE_1)
                if ((DSP_PID_GPHY <= pMsg->ulSenderPid) && (DSP_PID_APM >= pMsg->ulSenderPid))
#else
                if ((DSP_PID_APM <= pMsg->ulSenderPid) && (DSP_PID_IDLE >= pMsg->ulSenderPid))
#endif
                {
                    /*VOS_ProtectionReboot(DRX_PHY_PROTECT_ERROR, VOS_FILE_ID, __LINE__, 0, 0);*/
                }
            }

            VOS_SpinUnlockIntUnlock(&g_stSleepSpinLock, ulLockLevel);

            SLEEP_MasterForceWake(enMode);
        }
        else
#endif
        {
            VOS_SpinUnlockIntUnlock(&g_stSleepSpinLock, ulLockLevel);

            SLEEP_WAKE_SLICE_RECORD(3);

            /* 允许深睡投票 */
            SLEEP_VoteUnlock(enMode);
        }

        /*lint -e534*/
        VOS_SmV(g_ulSleepSem);
        /*lint +e534*/

        return;
    }

    /*lint -e534*/
    VOS_SmV(g_ulSleepSem);
    /*lint +e534*/

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_MasterSleepMsgProc
 功能描述  : 接收到GUPHY进入主模SLEEP态消息处理.
 输入参数  : pstMsg 消息体

 输出参数  : 无

 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年07月31日
    作    者   : g47350
    修改内容   : V900R001项目新增函数

*****************************************************************************/
VOS_VOID SLEEP_MasterSleepMsgProc(MsgBlock *pstMsg)
{
    UPHY_OAM_SLEEP_IND_STRU                 *pstPhyReq;

    pstPhyReq = (UPHY_OAM_SLEEP_IND_STRU*)pstMsg;

    if (VOS_RATMODE_WCDMA == pstPhyReq->enRatMode)
    {
        /* 睡眠前完成SFN、CFN的更新 */
        HPA_ReadCfnSfn();

        /* 睡眠前通知层2判断邮箱数据是否搬完 */
        WTTF_MAC_R99MailBox_ReadForIpcHalt();
    }

    SLEEP_NOR_STATE_TRACK(pstPhyReq->enRatMode, SLEEP_MASTER_PHY_HALT);

    SLEEP_WAKE_SLICE_RECORD(1);

    /* 与32K中断相同的处理流程 */
    SLEEP_32KClkMsgProc(pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_WakeMasterMsgProc
 功能描述  : 接收到WAKE中断消息处理.
 输入参数  : pstMsg 消息体

 输出参数  : 无

 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年07月31日
    作    者   : g47350
    修改内容   : V900R001项目新增函数

*****************************************************************************/
VOS_VOID SLEEP_WakeMasterMsgProc(MsgBlock *pstMsg)
{
    SLEEP_ISR_MSG_STRU                 *pstIsrReq;
    SLEEP_MODE_ENUM_UINT32              enMode;
    VOS_INT32                           lIntLevel;
#if (FEATURE_GUDRX_NEWVERSION == FEATURE_ON)
    MODEM_ID_ENUM_UINT16                enModem;
#endif

    pstIsrReq = (SLEEP_ISR_MSG_STRU*)pstMsg;

    enMode    = pstIsrReq->enRatMode;

    /* 参数检测 */
    if (SLEEP_GU_MODE_TYPE_BUTT <= enMode)
    {
        /* 异常打印和记录 */
        PS_LOG1(WUEPS_PID_AWAKE, 0, PS_PRINT_ERROR, "SLEEP_WakeMasterMsgProc: Mode para is wrong.", (VOS_INT32)enMode);
        return;
    }

#if (FEATURE_GUDRX_NEWVERSION == FEATURE_ON)
    enModem = SLEEP_GetModemId();
#endif

    (VOS_VOID)VOS_SmP(g_ulSleepSem, 0);

    /* 只有系统在主模低功耗状态才能进入到NORMAL暂态 */
    if (SLEEP_MASTER_LP_STATE == g_astSleepModeInfo[enMode].enSystemState)
    {
        /* 上电RTT子系统 */
        SLEEP_ActivateHw(enMode);

        lIntLevel = VOS_SplIMP();

#if (FEATURE_GUBBP_HANDSHAKE == FEATURE_ON)
        /* 配置WBBP握手寄存器 */
        if (VOS_RATMODE_WCDMA == enMode)
        {
            HPA_Write32Reg(WBBP_DSP_READY_IND_1CARD_ADDR, BBP_HANDSHAKE_BIT);

            /* 记录配置次数和Slice值 */
            if (VOS_NULL_PTR != g_pstSleepDeviceState)
            {
                g_pstSleepDeviceState->stHandShakeRecord.ulCount++;
                g_pstSleepDeviceState->stHandShakeRecord.ulSlice = OM_GetSlice();
            }
        }

#if (FEATURE_GUDRX_NEWVERSION == FEATURE_ON)
        if (VOS_RATMODE_GSM == enMode)
        {
            /* 配置GBBP握手寄存器 */
            HPA_Write32Reg(GBBP_GDRX_RDY_IND_ADDR, BBP_HANDSHAKE_BIT);
        }
#endif
#endif

#if (FEATURE_GUDRX_NEWVERSION == FEATURE_OFF)
        if (VOS_RATMODE_GSM == enMode)
        {
            /* 强制唤醒G BBP */
            HPA_Write32RegMask(GBBP_SLEEP_EN_ADDR, BIT_N(2));
        }
#endif

        g_astSleepModeInfo[enMode].enWakeType    = UPHY_OAM_NORMAL_WAKE;
        g_astSleepModeInfo[enMode].enSystemState = SLEEP_TEMP_NORMAL_STATE;

        VOS_Splx(lIntLevel);
    }

    /*lint -e534*/
    VOS_SmV(g_ulSleepSem);
    /*lint +e534*/

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_NormalClkMsgProc
 功能描述  : 接收到时钟切换中断(正常时钟)消息处理.
 输入参数  : pstMsg 消息体

 输出参数  : 无

 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年07月31日
    作    者   : g47350
    修改内容   : V900R001项目新增函数

*****************************************************************************/
VOS_VOID SLEEP_NormalClkMsgProc(MsgBlock *pstMsg)
{
    SLEEP_ISR_MSG_STRU                 *pstIsrReq;
    SLEEP_MODE_ENUM_UINT32              enMode;
#if (FEATURE_GUBBP_HANDSHAKE == FEATURE_ON)
    VOS_UINT32                          ulDeltaSlice;
#endif

    pstIsrReq = (SLEEP_ISR_MSG_STRU*)pstMsg;

    enMode    = pstIsrReq->enRatMode;

    /* 参数检测 */
    if (SLEEP_GU_MODE_TYPE_BUTT <= enMode)
    {
        /* 异常打印和记录 */
        PS_LOG1(WUEPS_PID_AWAKE, 0, PS_PRINT_ERROR, "SLEEP_NormalClkMsgProc: Mode para is wrong.", (VOS_INT32)enMode);
        return;
    }

    SLEEP_NOR_STATE_TRACK(enMode, SLEEP_MASTER_WAKE_PHY_PRE);

    (VOS_VOID)VOS_SmP(g_ulSleepSem, 0);

    /* 记录当前系统状态和Slice值 */

    ;

    /* 只有系统在NORMAL暂态才能进入到NORMAL态 */
    if (SLEEP_TEMP_NORMAL_STATE == g_astSleepModeInfo[enMode].enSystemState)
    {
        /* 发送消息给PHY_IDLE唤醒PHY */
        /*lint -e534*/
        SLEEP_WakePhy(ID_OAM_UPHY_MASTER_WAKE_CMD, enMode, g_astSleepModeInfo[enMode].enWakeType);
        /*lint +e534*/

        SLEEP_NOR_STATE_TRACK(enMode, SLEEP_MASTER_WAKE_PHY);

        SLEEP_WAKE_SLICE_RECORD(7);

        SLEEP_MSG_RECORD(ID_OAM_UPHY_MASTER_WAKE_CMD, DSP_PID_WAKE, g_astSleepModeInfo[enMode].enWakeType);

        g_astSleepModeInfo[enMode].enSystemState = SLEEP_NORMAL_STATE;

#if (FEATURE_GUBBP_HANDSHAKE == FEATURE_ON)
        if (VOS_RATMODE_WCDMA == enMode)
        {
            /* BBP寄存器switch_delay_cnt_1card(0x1CC8)的bit 0~31，获取到"唤醒后时钟切换中断比原来预定的时刻晚了多少32k时钟周期"，并进行相应的处理 */
            ulDeltaSlice = HPA_Read32Reg(WBBP_SWITCH_DELAY_CNT_1CARD_ADDR);
            if ((ulDeltaSlice > 0) && (ulDeltaSlice < SLEEP_BBP_HANDSHAKE_MAX_DELAY))
            {
                /* 记录可维可测，该情况可以继续执行，不做复位 */
                SLEEP_BBP_SWITCH_INT_DELAY_RECORD(ulDeltaSlice);
            }
            else if (ulDeltaSlice >= SLEEP_BBP_HANDSHAKE_MAX_DELAY)
            {
                /* 该情况极端异常(软件未发起握手，或软件异常导致一直未握手)，记录可维可测，并复位 */
                SLEEP_BBP_SWITCH_INT_DELAY_RECORD(ulDeltaSlice);

                VOS_ProtectionReboot(DRX_REPORT_HANDSHAKE_ABNORMAL, THIS_FILE_ID, __LINE__, VOS_NULL_PTR, 0);
            }
            else
            {
                /* 正常情况，无需处理 */
            }
        }
#if (FEATURE_GUDRX_NEWVERSION == FEATURE_ON)
        else if (VOS_RATMODE_GSM == enMode)
        {
            ulDeltaSlice = HPA_Read32Reg(GBBP_DRX_SWITCH_MAX_RPT_ADDR);
            if ((ulDeltaSlice > 0) && (ulDeltaSlice < SLEEP_BBP_HANDSHAKE_MAX_DELAY))
            {
                /* 记录可维可测，该情况可以继续执行，不做复位 */
            }
            else if (ulDeltaSlice >= SLEEP_BBP_HANDSHAKE_MAX_DELAY)
            {
                /* 该情况极端异常(软件未发起握手，或软件异常导致一直未握手)，记录可维可测，并复位 */
            }
            else
            {
                /* 正常情况，无需处理 */
            }
        }
        else
        {
        }
#endif
#endif
    }

    /*lint -e534*/
    VOS_SmV(g_ulSleepSem);
    /*lint +e534*/

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_SlaveSleepMsgProc
 功能描述  : GUPHY通知进入从模的消息处理函数.
 输入参数  : pstMsg 消息体

 输出参数  : 无

 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年07月31日
    作    者   : g47350
    修改内容   : V900R001项目新增函数

*****************************************************************************/
VOS_VOID SLEEP_SlaveSleepMsgProc(MsgBlock *pstMsg)
{
    UPHY_OAM_SLEEP_IND_STRU            *pstPhyReq;
    SLEEP_MODE_ENUM_UINT32              enMode;
#if ((!defined(INSTANCE_1)) && (!defined(INSTANCE_2)))
    VOS_INT32                           lMeansFlag  = VOS_FALSE;
#endif
#ifdef FEATURE_DSP2ARM
    VOS_UINT32                          ulQueueSize = 0;
#endif

    pstPhyReq = (UPHY_OAM_SLEEP_IND_STRU*)pstMsg;

    enMode    = pstPhyReq->enRatMode;

    /* 参数检测 */
    if (SLEEP_GU_MODE_TYPE_BUTT <= enMode)
    {
        /* 异常打印和记录 */
        PS_LOG1(WUEPS_PID_SLEEP, 0, PS_PRINT_ERROR, "SLEEP_SlaveSleepMsgProc: Mode para is wrong.", (VOS_INT32)enMode);
        return;
    }

    (VOS_VOID)VOS_SmP(g_ulSleepSem, 0);

    SLEEP_NOR_STATE_TRACK(enMode, SLEEP_SLAVE_PHY_HALT);

    /* 只有系统在NORMAL态才能进入到从模低功耗 */
    if (SLEEP_NORMAL_STATE == g_astSleepModeInfo[enMode].enSystemState)
    {
        /* 下电RTT */
        SLEEP_DeactivateHw(enMode);

        SLEEP_NOR_STATE_TRACK(enMode, SLEEP_SLAVE_LP);

        g_astSleepModeInfo[enMode].enSystemState = SLEEP_SLAVE_LP_STATE;

        /* 进入从模低功耗状态，通知注册PID */
        SLEEP_NotifyStateToRegPid(enMode, SLEEP_SLAVE_LP_STATE);

#ifdef FEATURE_DSP2ARM
        /* 获取GUPHY消息队列中消息个数 */
        if (VOS_RATMODE_WCDMA == enMode)
        {
            ulQueueSize = VOS_GetQueueSizeFromFid(DSP_FID_WPHY);
        }
        else
        {
            ulQueueSize = VOS_GetQueueSizeFromFid(DSP_FID_GPHY);
        }
#endif

        /*仅主卡需要判断是否有测量标志位*/
#if defined(INSTANCE_1) || defined(INSTANCE_2)
    #ifdef FEATURE_DSP2ARM
        if (0 < ulQueueSize)
        {
            SLEEP_SlaveForceWake(enMode);
        }
        else
    #endif
        {
            /* 允许深睡投票 */
            SLEEP_VoteUnlock(enMode);

        #if defined(INSTANCE_2)
            if (VOS_RATMODE_GSM == enMode)
            {
                if (VOS_TRUE == UPHY_DSDA_GetGsmSlaveDrxFlag(SLEEP_GetModemId()))
                {
                    if (VOS_TRUE == g_ulSleepSlaveSemFlag)
                    {
                        g_pstSleepDeviceState->ulSlaveSEMGiveTimes++;
                        g_pstSleepDeviceState->ulSlaveSEMGiveStartSlice   = OM_GetSlice();

                        g_ulSleepSlaveSemFlag   = VOS_FALSE;

                        /*lint -e534*/
                        VOS_SmV(g_ulSleepSlaveSem);
                        /*lint +e534*/

                        g_pstSleepDeviceState->ulSlaveSEMGiveEndSlice     = OM_GetSlice();
                    }
                }
            }
        #endif
        }
#else
        lMeansFlag = mdrv_bbp_get_measure_flag((PWC_COMM_MODE_E)enMode);

    #ifdef FEATURE_DSP2ARM
        if ((0 < ulQueueSize) || (VOS_TRUE == lMeansFlag))
    #else
        if (VOS_TRUE == lMeansFlag)
    #endif
        {
            SLEEP_SlaveForceWake(enMode);
        }
        else
        {
            /* 允许深睡投票 */
            SLEEP_VoteUnlock(enMode);

            if (VOS_RATMODE_GSM == enMode)
            {
                if (VOS_TRUE == UPHY_DSDA_GetGsmSlaveDrxFlag(SLEEP_GetModemId()))
                {
                    if (VOS_TRUE == g_ulSleepSlaveSemFlag)
                    {
                        g_pstSleepDeviceState->ulSlaveSEMGiveTimes++;
                        g_pstSleepDeviceState->ulSlaveSEMGiveStartSlice   = OM_GetSlice();

                        g_ulSleepSlaveSemFlag   = VOS_FALSE;

                        /*lint -e534*/
                        VOS_SmV(g_ulSleepSlaveSem);
                        /*lint +e534*/

                        g_pstSleepDeviceState->ulSlaveSEMGiveEndSlice     = OM_GetSlice();
                    }
                }
            }
        }
#endif
    }

    /*lint -e534*/
    VOS_SmV(g_ulSleepSem);
    /*lint +e534*/

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_WakeSlaveGUProc
 功能描述  : 异系统测量下TL唤醒GU处理
 输入参数  : pstMsg 消息体


 输出参数  : 无

 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月13日
    作    者   : g47350
    修改内容   : 多模低功耗联调

*****************************************************************************/
VOS_VOID SLEEP_WakeSlaveGUProc(MsgBlock *pstMsg)
{
    SLEEP_ISR_MSG_STRU                 *pstIsrReq;
    SLEEP_MODE_ENUM_UINT32              enMode;
#if defined(INSTANCE_1)
#else
    VOS_INT32                           lLockLevel;
    SLEEP_SYSTEM_STATE_ENUM_UINT32      enSleepState;
#endif

    pstIsrReq = (SLEEP_ISR_MSG_STRU*)pstMsg;

    enMode    = pstIsrReq->enRatMode;

    /* Austin Modem0 & Modem2公用GBBP，GSM上下电流程需要通过硬件锁互斥进行保护 */
#if defined(INSTANCE_1)
#else
    lLockLevel = VOS_SplIMP();

    enSleepState    = g_astSleepModeInfo[enMode].enSystemState;

    VOS_Splx(lLockLevel);

    /* 判断当前是否在从模低功耗状态 */
    if (SLEEP_SLAVE_LP_STATE == enSleepState)
    {
        if (VOS_RATMODE_GSM == enMode)
        {
            if (VOS_TRUE == UPHY_DSDA_GetGsmSlaveDrxFlag(SLEEP_GetModemId()))
            {
                g_pstSleepDeviceState->ulSlaveSEMTakeTimes++;
                g_pstSleepDeviceState->ulSlaveSEMTakeStartSlice   = OM_GetSlice();

                /* 获取IPC硬件锁 */
                if (VOS_OK != VOS_SmP(g_ulSleepSlaveSem, SLEEP_IPC_TIMEOUT))
                {
                    if (0 != g_ulSleepSlaveMsgTrackId)
                    {
                        g_ulSleepSlaveMsgTrackId--;
                    }
                    else
                    {
                        g_ulSleepSlaveMsgTrackId    = SLEEP_SLAVE_MSG_TRACK_NUM-1;
                    }

                    VOS_ProtectionReboot(DRX_SLAVE_WAKE_IPC_ERROR, (VOS_INT)g_astSleepSlaveMsgTrack[g_ulSleepSlaveMsgTrackId].ulSenderPid,
                        (VOS_INT)g_astSleepSlaveMsgTrack[g_ulSleepSlaveMsgTrackId].ulMsgName, 0, 0);
                }

                g_pstSleepDeviceState->ulSlaveSEMTakeEndSlice     = OM_GetSlice();

                g_ulSleepSlaveSemFlag   = VOS_TRUE;
            }
        }
    }
#endif

    (VOS_VOID)VOS_SmP(g_ulSleepSem, 0);

    SLEEP_SlaveForceWake(enMode);

    /*lint -e534*/
    VOS_SmV(g_ulSleepSem);
    /*lint +e534*/

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_WakeMasterGUProc
 功能描述  : 强制唤醒GU处理
 输入参数  : pstMsg 消息体


 输出参数  : 无

 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月26日
    作    者   : s00207770
    修改内容   : 新增接口

*****************************************************************************/
VOS_VOID SLEEP_WakeMasterGUProc(MsgBlock *pstMsg)
{
    SLEEP_ISR_MSG_STRU                 *pstIsrReq;
    SLEEP_MODE_ENUM_UINT32              enMode;

    pstIsrReq = (SLEEP_ISR_MSG_STRU*)pstMsg;

    enMode    = pstIsrReq->enRatMode;

    (VOS_VOID)VOS_SmP(g_ulSleepSem, 0);

    SLEEP_MasterForceWake(enMode);

    /*lint -e534*/
    VOS_SmV(g_ulSleepSem);
    /*lint +e534*/

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_MasterWakeSlave
 功能描述  : GUPHY作为主模唤醒从模函数.
 输入参数  : enRatMode 需要唤醒的模式

 输出参数  : 无

 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年07月31日
    作    者   : g47350
    修改内容   : V900R001项目新增函数

*****************************************************************************/
VOS_UINT32 SLEEP_MasterWakeSlave(SLEEP_MODE_ENUM_UINT32 enRatMode)
{
    VOS_INT32                           lLockLevel;

    switch (enRatMode)
    {
        case VOS_RATMODE_WCDMA:
        case VOS_RATMODE_GSM:
            lLockLevel = VOS_SplIMP();

            if (SLEEP_SLAVE_LP_STATE == g_astSleepModeInfo[enRatMode].enSystemState)
            {
                SLEEP_AwakeIsrProc(SLEEP_WAKE_SLAVE_GU_IND, enRatMode);
            }

            VOS_Splx(lLockLevel);

            break;

        case VOS_RATMODE_LTE:
        case VOS_RATMODE_TDS:
            TLSLEEP_MasterAwakeSlave();

            break;

/* L主模唤醒C从模，共票方案只传1X模式 */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case VOS_RATMODE_1X:
        case VOS_RATMODE_HRPD:
            SLEEP_BBE16ForceWakeProc(VOS_RATMODE_1X);

            break;
#endif

        default:
            return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : SLEEP_MasterForceWake
 功能描述  : 判断是否在主模低功耗下，如果是则强制唤醒GUPHY.
 输入参数  : enMode 模式

 输出参数  : 无

 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年07月31日
    作    者   : g47350
    修改内容   : V900R001项目新增函数

*****************************************************************************/
VOS_VOID SLEEP_MasterForceWake(SLEEP_MODE_ENUM_UINT32 enMode)
{
    VOS_INT32                           lIntLevel;

    if (SLEEP_MASTER_LP_STATE == g_astSleepModeInfo[enMode].enSystemState)
    {
        /* 禁止深睡投票 */
        SLEEP_VoteLock(enMode);

        /* 上电RTT子系统 */
        SLEEP_ActivateHw(enMode);

        SLEEP_NOR_STATE_TRACK(enMode, SLEEP_MASTER_FORCE_WAKE);

        lIntLevel = VOS_SplIMP();

        /*判断最近是否有正常WAKE中断上报*/
        if (VOS_RATMODE_WCDMA == enMode)
        {
            if (VOS_OK != SLEEP_ForceWakeProtected())
            {
                VOS_Splx(lIntLevel);

                return;
            }

            /* 强制唤醒W BBP */
            HPA_Write32RegMask(WBBP_SWITCH_UP_1CARD_ADDR, BBP_AWAKE_BIT);
        }
        else
        {
            /* 强制唤醒G BBP */
            /*lint -e701*/
            HPA_Write32RegMask(GBBP_SLEEP_EN_ADDR, SLEEP_BIT_N(2));
            /*lint +e701*/
        }

        g_astSleepModeInfo[enMode].enWakeType    = UPHY_OAM_FORCE_WAKE;
        g_astSleepModeInfo[enMode].enSystemState = SLEEP_TEMP_NORMAL_STATE;

        VOS_Splx(lIntLevel);
    }

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_SlaveForceWake
 功能描述  : 判断是否在从模低功耗下，如果是则强制唤醒GUPHY.
 输入参数  : enMode 模式

 输出参数  : 无

 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年07月31日
    作    者   : g47350
    修改内容   : V900R001项目新增函数

*****************************************************************************/
VOS_VOID SLEEP_SlaveForceWake(SLEEP_MODE_ENUM_UINT32 enMode)
{
    VOS_UINT32                          ulStartSlice;

    /* 判断当前是否在从模低功耗状态 */
    if (SLEEP_SLAVE_LP_STATE == g_astSleepModeInfo[enMode].enSystemState)
    {
        ulStartSlice    = OM_GetSlice();

        /* 禁止深睡投票 */
        SLEEP_VoteLock(enMode);

        /* 上电RTT */
        SLEEP_ActivateHw(enMode);

        SLEEP_MSG_RECORD(ID_OAM_UPHY_SLAVE_WAKE_CMD, DSP_PID_WAKE, ulStartSlice);

        /* 发送消息给PHY_IDLE唤醒PHY */
        /*lint -e534*/
        SLEEP_WakePhy(ID_OAM_UPHY_SLAVE_WAKE_CMD, enMode, UPHY_OAM_FORCE_WAKE);
        /*lint +e534*/

        SLEEP_NOR_STATE_TRACK(enMode, SLEEP_SLAVE_FORCE_WAKE);

        g_astSleepModeInfo[enMode].enSystemState = SLEEP_NORMAL_STATE;
    }

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_HookMsgProc
 功能描述  : SLEEP注册给OSA的发送消息钩子函数，用来在GUPHY进入SLEEP态，强制唤醒
             GUPHY
 输入参数  : 指向OSA消息体指针

 输出参数  : 无

 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年07月31日
    作    者   : g47350
    修改内容   : V900R001项目新增函数

*****************************************************************************/
VOS_VOID SLEEP_HookMsgProc(MsgBlock *pstMsg)
{
    VOS_INT                             lLockLevel;

    if (VOS_FALSE != VOS_CheckInterrupt())
    {
        return;
    }

    /* 判断是否有消息发送给WPHY */
    if (DSP_PID_WPHY == pstMsg->ulReceiverPid)
    {
        lLockLevel = VOS_SplIMP();

        if (SLEEP_MASTER_LP_STATE == g_astSleepModeInfo[VOS_RATMODE_WCDMA].enSystemState)
        {
            SLEEP_AwakeIsrProc(SLEEP_WAKE_MASTER_GU_IND, VOS_RATMODE_WCDMA);
        }
        else if (SLEEP_SLAVE_LP_STATE == g_astSleepModeInfo[VOS_RATMODE_WCDMA].enSystemState)
        {
            SLEEP_AwakeIsrProc(SLEEP_WAKE_SLAVE_GU_IND, VOS_RATMODE_WCDMA);
        }
        else
        {
        }

        VOS_Splx(lLockLevel);

        return;
    }

    /* 判断是否有消息发送给GPHY */
    if (DSP_PID_GPHY == pstMsg->ulReceiverPid)
    {
        lLockLevel = VOS_SplIMP();

        if (SLEEP_MASTER_LP_STATE == g_astSleepModeInfo[VOS_RATMODE_GSM].enSystemState)
        {
            SLEEP_AwakeIsrProc(SLEEP_WAKE_MASTER_GU_IND, VOS_RATMODE_GSM);
        }
        else if (SLEEP_SLAVE_LP_STATE == g_astSleepModeInfo[VOS_RATMODE_GSM].enSystemState)
        {
            SLEEP_AwakeIsrProc(SLEEP_WAKE_SLAVE_GU_IND, VOS_RATMODE_GSM);

            g_astSleepSlaveMsgTrack[g_ulSleepSlaveMsgTrackId].ulMode      = VOS_RATMODE_GSM;
            g_astSleepSlaveMsgTrack[g_ulSleepSlaveMsgTrackId].ulSenderPid = pstMsg->ulSenderPid;
            g_astSleepSlaveMsgTrack[g_ulSleepSlaveMsgTrackId].ulMsgName   = *((VOS_UINT32 *)(pstMsg->aucValue));
            g_astSleepSlaveMsgTrack[g_ulSleepSlaveMsgTrackId].ulSlice     = OM_GetSlice();

            g_ulSleepSlaveMsgTrackId++;

            if (SLEEP_SLAVE_MSG_TRACK_NUM == g_ulSleepSlaveMsgTrackId)
            {
                g_ulSleepSlaveMsgTrackId = 0;
            }
        }
        else
        {
        }

        VOS_Splx(lLockLevel);

        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_AwakeMsgProc
 功能描述  : AWAKE消息处理函数
 输入参数  : 指向OSA消息体指针

 输出参数  : 无

 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月09日
    作    者   : s00207770
    修改内容   : 低功耗任务优先级拆分项目修改

*****************************************************************************/
VOS_VOID SLEEP_AwakeMsgProc(MsgBlock* pstMsg)
{
    SLEEP_MSG_FUN_STRU                 *pstMsgFun;
    VOS_UINT32                          ulTlbSize;
    VOS_UINT32                          ulIndex;
    UPHY_OAM_SLEEP_IND_STRU            *pstPhyReq;
    VOS_UINT32                          ulStartSlice = 0;

    pstPhyReq = (UPHY_OAM_SLEEP_IND_STRU*)pstMsg;

    /* 中断消息处理 */
    if (WUEPS_PID_AWAKE == pstPhyReq->ulSenderPid)
    {
        pstMsgFun = g_astAwakeIsrMsgFunTbl;
        ulTlbSize = sizeof(g_astAwakeIsrMsgFunTbl)/sizeof(SLEEP_MSG_FUN_STRU);
    }
    else
    {
        /* 未知消息直接返回 */
        /*lint -e534*/
        LogPrint1("SLEEP_AwakeMsgProc: Unknown ulSenderPid:%d.\r\n",
                        (VOS_INT)pstMsg->ulSenderPid);
        /*lint +e534*/

        SLEEP_MSG_RECORD(pstPhyReq->enMsgId, pstPhyReq->ulSenderPid, ulStartSlice);

        return;
    }

    for (ulIndex = 0; ulIndex < ulTlbSize; ulIndex++)
    {
        /* 查找到对应消息ID的处理函数 */
        if (pstPhyReq->enMsgId == (UPHY_OAM_MSG_ID_ENUM_UINT16)pstMsgFun[ulIndex].ulMsgId)
        {
            ulStartSlice = OM_GetSlice();

            pstMsgFun[ulIndex].pMsgFun(pstMsg);

            /* 记录处理的消息 */
            SLEEP_MSG_RECORD(pstPhyReq->enMsgId, pstPhyReq->enRatMode, ulStartSlice);

            return;
        }
    }

    SLEEP_MSG_RECORD(pstPhyReq->enMsgId, pstPhyReq->ulSenderPid, ulStartSlice);

    /* 异常打印和记录 */
    /*lint -e534*/
    LogPrint2("SLEEP_AwakeMsgProc: Unknown Msg, ulSenderPid:%d, enMsgId:%d.\r\n",
                (VOS_INT)pstPhyReq->ulSenderPid, (VOS_INT)pstPhyReq->enMsgId);
    /*lint +e534*/
    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_SleepMsgProc
 功能描述  : SLEEP消息处理函数
 输入参数  : 指向OSA消息体指针

 输出参数  : 无

 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年07月31日
    作    者   : g47350
    修改内容   : V900R001项目新增函数
  2.日    期   : 2015年03月09日
    作    者   : s00207770
    修改内容   : 低功耗任务优先级拆分项目修改

*****************************************************************************/
VOS_VOID SLEEP_SleepMsgProc(MsgBlock* pstMsg)
{
    SLEEP_MSG_FUN_STRU                 *pstMsgFun;
    VOS_UINT32                          ulTlbSize;
    VOS_UINT32                          ulIndex;
    UPHY_OAM_SLEEP_IND_STRU             *pstPhyReq;
    VOS_UINT32                          ulStartSlice = 0;

    pstPhyReq = (UPHY_OAM_SLEEP_IND_STRU*)pstMsg;

    /* 中断消息处理 */
    if (WUEPS_PID_SLEEP == pstPhyReq->ulSenderPid)
    {
        pstMsgFun = g_astSleepIsrMsgFunTbl;
        ulTlbSize = sizeof(g_astSleepIsrMsgFunTbl)/sizeof(SLEEP_MSG_FUN_STRU);
    }
    /* PHY发来消息处理*/
    else if (DSP_PID_SLEEP == pstPhyReq->ulSenderPid)
    {
        pstMsgFun = g_astSleepPhyMsgFunTbl;
        ulTlbSize = sizeof(g_astSleepPhyMsgFunTbl)/sizeof(SLEEP_MSG_FUN_STRU);
    }
    else
    {
        /* 未知消息直接返回 */
        /*lint -e534*/
        LogPrint1("SLEEP_MsgProc: Unknown ulSenderPid:%d.\r\n",
                        (VOS_INT)pstMsg->ulSenderPid);
        /*lint +e534*/

        SLEEP_MSG_RECORD(pstPhyReq->enMsgId, pstPhyReq->ulSenderPid, ulStartSlice);

        return;
    }

    for (ulIndex = 0; ulIndex < ulTlbSize; ulIndex++)
    {
        /* 查找到对应消息ID的处理函数 */
        if (pstPhyReq->enMsgId == (UPHY_OAM_MSG_ID_ENUM_UINT16)pstMsgFun[ulIndex].ulMsgId)
        {
            ulStartSlice = OM_GetSlice();

            pstMsgFun[ulIndex].pMsgFun(pstMsg);

            /* 记录处理的消息 */
            SLEEP_MSG_RECORD(pstPhyReq->enMsgId, pstPhyReq->enRatMode, ulStartSlice);

            return;
        }
    }

    SLEEP_MSG_RECORD(pstPhyReq->enMsgId, pstPhyReq->ulSenderPid, ulStartSlice);

    /* 异常打印和记录 */
    /*lint -e534*/
    LogPrint2("SLEEP_MsgProc: Unknown Msg, ulSenderPid:%d, enMsgId:%d.\r\n",
                (VOS_INT)pstPhyReq->ulSenderPid, (VOS_INT)pstPhyReq->enMsgId);
    /*lint +e534*/
    return;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : SLEEP_BBE16HaltIsr
 功能描述  : BBE16睡眠中断服务程序
 输入参数  : SLEEP_MODE_ENUM_UINT32 enMode
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SLEEP_BBE16HaltIsr( SLEEP_MODE_ENUM_UINT32 enMode )
{
    CPHY_SLEEP_MODE_ENUM_UINT32               enHaltType;

    enHaltType                              = CPHY_SLEEP_MODE_BUTT;

    SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_HALT_INT_TRACE);

    if (SLEEP_BBE16_NORMAL_STATE == g_astSleepBBE16ModeInfo[enMode].enSystemState)
    {

    }
    else
    {
        SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_HALT_INT_NOT_NORMAL_TRACE);
        return;
    }

    /* 指向SRAM的指针为空 */
    if (VOS_NULL_PTR == g_pstBBE16SleepInfo)
    {
        return;
    }

    /* 读取共享内存SRAM，判断当前模式睡眠中断类型，确认进入主模睡眠或者从模睡眠流程 */
    if (VOS_RATMODE_1X == enMode)
    {
        enHaltType = g_pstBBE16SleepInfo->en1xMode;
        g_astSleepBBE16ModeInfo[VOS_RATMODE_1X].enCdmaSleepType = g_pstBBE16SleepInfo->enSleepType;
    }
    else if (VOS_RATMODE_HRPD == enMode)
    {
        enHaltType = g_pstBBE16SleepInfo->enHrpdMode;
        g_astSleepBBE16ModeInfo[VOS_RATMODE_HRPD].enCdmaSleepType = g_pstBBE16SleepInfo->enSleepType;
    }
    else
    {
        return;
    }

    if (CPHY_SLEEP_MODE_MASTER == enHaltType)
    {
        g_astSleepBBE16ModeInfo[enMode].enSystemState = SLEEP_BBE16_MASTER_HALT_STATE;
    }
    else if (CPHY_SLEEP_MODE_SLAVE == enHaltType)
    {
        g_astSleepBBE16ModeInfo[enMode].enSystemState = SLEEP_BBE16_SLAVE_HALT_STATE;
    }
    else
    {
        return;
    }

    SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_HALT_INT_TO_MSG_TRACE);
    SLEEP_BBE16HaltIsrProc(BBE16_SLEEP_SLEEP_IND, enMode);

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_BBE16AwakeIsr
 功能描述  : X模唤醒中断服务程序
             BBP定时中断，只有主模才有，只在低功耗态才进行处理
 输入参数  : SLEEP_MODE_ENUM_UINT32 enMode
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SLEEP_BBE16AwakeIsr( SLEEP_MODE_ENUM_UINT32 enMode )
{
    SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_NORMAL_WAKE_INT_TRACE);

    /* 空指针返回 */
    if (VOS_NULL_PTR == g_pstBBE16SleepInfo)
    {
        return;
    }

    if (VOS_RATMODE_1X == enMode)
    {
        g_pstBBE16SleepInfo->en1xWakeUpType     = CPHY_OAM_NORMAL_WAKE;
    }
    else
    {
        g_pstBBE16SleepInfo->enHrpdWakeUpType   = CPHY_OAM_NORMAL_WAKE;
    }

    if (SLEEP_BBE16_MASTER_LP_STATE == g_astSleepBBE16ModeInfo[enMode].enSystemState)
    {
        g_astSleepBBE16ModeInfo[enMode].enSystemState = SLEEP_BBE16_MASTER_WAKE_STATE;

        SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_NORMAL_WAKE_INT_TO_MSG_TRACE);
        SLEEP_BBE16AwakeIsrProc(BBE16_SLEEP_AWAKE_IND, enMode);
    }
    else
    {
        /*
           唤醒中断时，不考虑HALT态，
           如果是WAKE或TEMP态，表示已经在做唤醒;如果是NORMAL态，表示已经唤醒完成，这时不需再做唤醒
        */
        SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_WAKE_INT_NOT_LP_TRACE);
    }

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_BBE16ResumeIsr
 功能描述  : BBE16唤醒恢复中断服务程序
 输入参数  : SLEEP_MODE_ENUM_UINT32 enMode
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SLEEP_BBE16ResumeIsr( SLEEP_MODE_ENUM_UINT32 enMode )
{
    SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_RESUME_INT_TRACE);

    SLEEP_BBE16ResumeIsrProc(BBE16_SLEEP_RESUME_IND, enMode);

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_BBE16PowerUp
 功能描述  : BBE16上电流程接口
 输入参数  : SLEEP_MODE_ENUM_UINT32 enMode
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月28日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SLEEP_BBE16PowerUp( SLEEP_MODE_ENUM_UINT32 enMode )
{
    if ((VOS_RATMODE_1X == enMode) || (VOS_RATMODE_HRPD == enMode))
    {
        /* 加载BBE16镜像,当前低功耗接口未定义开发，仅使用调试接口，后续待低功耗
           开发时，修改BBE16的上电流程 */
        (VOS_VOID)mdrv_pm_enable_pllclk((PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_CBBE16, (PWC_COMM_MODEM_E)SLEEP_GetModemId(), PWC_COMM_CHANNEL_0);
        /*lint -e534 -e746*/
        (VOS_VOID)mlp_dsp_pwrup(enMode, (PWC_COMM_MODEM_E)SLEEP_GetModemId());
        (VOS_VOID)mlp_dsp_enable_clock(enMode);
        (VOS_VOID)mlp_dsp_unreset(enMode);
        (VOS_VOID)mlp_dsp_load(enMode);
        (VOS_VOID)mlp_dsp_restore(enMode);
        (VOS_VOID)mlp_dsp_stop(enMode);
        (VOS_VOID)mlp_dsp_run(enMode);
        /*lint +e534 +e746*/
    }

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_ReportEvent
 功能描述  : 调用OM提供的上报Event接口
 输入参数  : VOS_UINT16 usEventId
             SLEEP_MODE_ENUM_UINT32 enMode
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月28日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SLEEP_ReportEvent(VOS_UINT16 usEventId, SLEEP_MODE_ENUM_UINT32 enMode)
{
    DIAG_EVENT_IND_STRU                 stEventInd;

    stEventInd.ulModule = DIAG_GEN_MODULE(DIAG_MODEM_0, DIAG_MODE_COMM);
    stEventInd.ulPid    = WUEPS_PID_AWAKE;
    stEventInd.ulEventId= usEventId;
    stEventInd.ulLength = SLEEP_BBE16_NORMAL_BUTT * sizeof(SLEEP_BBE16_RECORD_TRACK_STRU);
    stEventInd.pData    = g_pstSleepBBE16NormalState->astRecordItem[enMode];

    /*lint -e534*/
    (VOS_VOID)DIAG_EventReport(&stEventInd);
    /*lint +e534*/

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_BBE16DeactivateHw
 功能描述  : 下电RTT子系统.
 输入参数  : enMode     :模式，W/G

 输出参数  : 无

 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月31日
    作    者   : x00306642
    修改内容   : x模低功耗新增函数

*****************************************************************************/
VOS_VOID SLEEP_BBE16DeactivateHw(SLEEP_MODE_ENUM_UINT32 enMode)
{
    MODEM_ID_ENUM_UINT16                enModem;

    enModem = SLEEP_GetModemId();

#if (FEATURE_GUC_BBP_TRIG == FEATURE_ON)
    PsRegGUCBBPDbgDisable(enModem, enMode);
#endif

    SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_DEACTIVATE_START);

    /* BBE16操作 */
    /* 1:stop BBE16 */
    (VOS_VOID)mlp_dsp_stop(enMode);

    if (CPHY_SLEEP_TYPE_DEEP == g_astSleepBBE16ModeInfo[enMode].enCdmaSleepType)
    {
        /* 2:备份公共data */
        (VOS_VOID)mlp_dsp_backup(enMode);
    }

    /* 下电BBP */
    /*lint -e534*/
    SLEEP_DEVICE_POWDOWN(enModem, enMode, PWC_COMM_MODULE_BBP_DRX, PWC_COMM_CHANNEL_0);

    /* 关闭BBP外设时钟 */
    mdrv_pm_disable_bbpclk((PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_BBP_DRX, (PWC_COMM_MODEM_E)enModem, PWC_COMM_CHANNEL_0);

    /* 关闭BBP PLL */
    SLEEP_DEVICEPLL_POWDOWN((PWC_COMM_MODEM_E)enModem, (PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_BBP_DRX, PWC_COMM_CHANNEL_0);
    /*lint +e534*/

    /* 关闭ABB PLL */
    SLEEP_ABBPllDisable(enMode);

    /* 下电ABB */
    SLEEP_ABBPowerDown(enMode);

    if (CPHY_SLEEP_TYPE_DEEP == g_astSleepBBE16ModeInfo[enMode].enCdmaSleepType)
    {
        /* 2:等待备份公共data完成 */
        (VOS_VOID)mlp_dsp_wait_backup(enMode);
    }

    /* 3:复位BBE16 */
    (VOS_VOID)mlp_dsp_reset(enMode);

    /* 4:关BBE16钟 */
    (VOS_VOID)mlp_dsp_disable_clock(enMode);

    /* 5:关DRX PLL钟*/
    (VOS_VOID)mdrv_pm_disable_pllclk((PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_CBBE16, (PWC_COMM_MODEM_E)SLEEP_GetModemId(), PWC_COMM_CHANNEL_0);

    if (CPHY_SLEEP_TYPE_DEEP == g_astSleepBBE16ModeInfo[enMode].enCdmaSleepType)
    {
        /* 6:下电BBE16 */
        (VOS_VOID)mlp_dsp_pwrdown(enMode, (PWC_COMM_MODEM_E)SLEEP_GetModemId());
    }

    /* 下电RF */
    SLEEP_RFPowerDown(enMode);
    SLEEP_RFFECfgPowerDown(enMode);

    /* 关闭TCXO */
    SLEEP_TCXODisable(enMode);

    SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_DEACTIVATE_END);

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_BBE16ActivateHw
 功能描述  : 上电RTT子系统.
 输入参数  : enMode     :模式，W/G

 输出参数  : 无

 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月31日
    作    者   : x00306642
    修改内容   : x模低功耗新增函数

*****************************************************************************/
VOS_VOID SLEEP_BBE16ActivateHw(SLEEP_MODE_ENUM_UINT32 enMode)
{
    MODEM_ID_ENUM_UINT16                enModem;
    VOS_UINT32                          ulSlice;

    enModem = SLEEP_GetModemId();

    SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_ACTIVATE_START);

    /* 打开TCXO */
    SLEEP_TCXOEnable(enMode);

    /* 上电RF */
    SLEEP_RFPowerUp(enMode);

    /* BBE16操作 */
    /* 1开DRX PLL钟 */
    (VOS_VOID)mdrv_pm_enable_pllclk((PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_CBBE16, (PWC_COMM_MODEM_E)SLEEP_GetModemId(), PWC_COMM_CHANNEL_0);

    if (CPHY_SLEEP_TYPE_DEEP == g_astSleepBBE16ModeInfo[enMode].enCdmaSleepType)
    {
        /* 2上电BBE16 */
        (VOS_VOID)mlp_dsp_pwrup(enMode, (PWC_COMM_MODEM_E)SLEEP_GetModemId());
    }

    /* 3开BBE16钟 */
    (VOS_VOID)mlp_dsp_enable_clock(enMode);

    /* 4解复位BBE16 */
    (VOS_VOID)mlp_dsp_unreset(enMode);

    if (CPHY_SLEEP_TYPE_DEEP == g_astSleepBBE16ModeInfo[enMode].enCdmaSleepType)
    {
        /* 5恢复公共data */
        (VOS_VOID)mlp_dsp_restore(enMode);
    }

    /* 上电ABB */
    SLEEP_ABBPowerUp(enMode);

    /* 打开ABB PLL */
    SLEEP_ABBPllEnable(enMode);

    /* V8R1上BBP CS分区电源随外设开关，所以在解复位BBP CS分区前，需要先打开门控和时钟*/
    /* 打开BBP PLL */
    /*lint -e534*/
    SLEEP_DEVICEPLL_POWUP((PWC_COMM_MODEM_E)enModem, (PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_BBP_DRX, PWC_COMM_CHANNEL_0);

    /* 打开BBP外设时钟 */
    mdrv_pm_enable_bbpclk((PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_BBP_DRX, (PWC_COMM_MODEM_E)enModem, PWC_COMM_CHANNEL_0);

    /* 上电BBP */
    SLEEP_DEVICE_POWUP(enModem, enMode, PWC_COMM_MODULE_BBP_DRX, PWC_COMM_CHANNEL_0);
    /*lint +e534*/

    ulSlice = OM_GetSlice();

    /* 换算成Slice等待器件稳定 */
    while((g_ulSleepRusumeTime) > (OM_GetSlice() - ulSlice))
    {
        ;
    }

    if (CPHY_SLEEP_TYPE_DEEP == g_astSleepBBE16ModeInfo[enMode].enCdmaSleepType)
    {
        /* 5等待恢复公共data完成 */
        (VOS_VOID)mlp_dsp_wait_restore(enMode);
    }

    /* 6run BBE16 */
    (VOS_VOID)mlp_dsp_run(enMode);

    SLEEP_RFFECfgPowerUp(enMode);

    SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_ACTIVATE_END);

#if (FEATURE_GUC_BBP_TRIG == FEATURE_ON)
    PsRegGUCBBPDbgEnable(enModem, enMode);
#endif

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_BBE16GetTwinMode
 功能描述  : 判断1X/HRPD对应模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : SLEEP_MODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
SLEEP_MODE_ENUM_UINT32 SLEEP_BBE16GetTwinMode( SLEEP_MODE_ENUM_UINT32 enMode )
{
    SLEEP_MODE_ENUM_UINT32              enTwinMode;

    if (VOS_RATMODE_1X == enMode)
    {
        enTwinMode  = VOS_RATMODE_HRPD;
    }
    else if (VOS_RATMODE_HRPD == enMode)
    {
        enTwinMode  = VOS_RATMODE_1X;
    }
    else
    {
        return VOS_RATMODE_BUTT;
    }

    return enTwinMode;
}

/*****************************************************************************
 函 数 名  : SLEEP_BBE16GetTwinState
 功能描述  : 判断1X/HRPD对应模式的低功耗状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : SLEEP_BBE16_SYSTEM_STATE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
SLEEP_BBE16_SYSTEM_STATE_ENUM_UINT32 SLEEP_BBE16GetTwinState( SLEEP_MODE_ENUM_UINT32 enMode )
{
    SLEEP_MODE_ENUM_UINT32              enTwinMode;

    if (VOS_RATMODE_1X == enMode)
    {
        enTwinMode  = VOS_RATMODE_HRPD;
    }
    else if (VOS_RATMODE_HRPD == enMode)
    {
        enTwinMode  = VOS_RATMODE_1X;
    }
    else
    {
        return SLEEP_BBE16_STATE_BUTT;
    }

    return g_astSleepBBE16ModeInfo[enTwinMode].enSystemState;
}

/*****************************************************************************
 函 数 名  : SLEEP_BBE16MailBoxResumeProc
 功能描述  : 封装邮箱提供的resume接口
 输入参数  : enMode     邮箱的模式
 输出参数  : 无
 返 回 值  : enRatMode  转换后的VOS模式
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SLEEP_BBE16MailBoxResumeProc(SLEEP_MODE_ENUM_UINT32 enMode)
{
    XMBX_RATMODE_ENUM_U32               enXmbxMode;

    if (VOS_RATMODE_1X == enMode)
    {
        enXmbxMode = XMBX_MOD_1X;
    }
    else if (VOS_RATMODE_HRPD == enMode)
    {
        /* 共票方案不出现HRPD */
        enXmbxMode = XMBX_MOD_HRPD;
    }
    else
    {
        /* sleep自己调用，自己保证 */
        enXmbxMode = XMBX_MOD_1X;
    }

    /* 底软接口 */
    mdrv_MailBox_CdmaResumeProc(EN_MAILBOX_CALLBACK_DSP_RESUME, enXmbxMode);

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_BBE16IsMailBoxAllowCBBE16Sleep
 功能描述  : 封装邮箱提供的判断邮箱是否有消息接口
 输入参数  : enMode
 输出参数  : 无
 返 回 值  : VOS_FALSE  邮箱无消息
             VOS_TRUE   邮箱有消息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 SLEEP_BBE16IsMailBoxAllowCBBE16Sleep(SLEEP_MODE_ENUM_UINT32 enMode)
{
    XMBX_RATMODE_ENUM_U32               enXmbxMode;

    if (VOS_RATMODE_1X == enMode)
    {
        enXmbxMode = XMBX_MOD_1X;
    }
    else if (VOS_RATMODE_HRPD == enMode)
    {
        /* 共票方案不出现HRPD */
        enXmbxMode = XMBX_MOD_HRPD;
    }
    else
    {
        /* sleep自己调用，自己保证 */
        enXmbxMode = XMBX_MOD_1X;
    }

    /* 底软接口 */
    if (VOS_FALSE == mdrv_Mailbox_IsAllowCdmaSleep(enXmbxMode))
    {
        return VOS_FALSE;
    }

    /* 邮箱标记 */
    if (CPHY_WRITE_MBX_UNCOMPLETED == g_pstBBE16SleepInfo->enCprocWriteMbxState)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : SLEEP_BBE16MailBoxGetDspState
 功能描述  : 封装的邮箱判断DSP状态的API
 输入参数  : enMode
 输出参数  : 无
 返 回 值  : VOS_FALSE  邮箱无消息
             VOS_TRUE   邮箱有消息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 SLEEP_BBE16MailBoxGetDspState(XMBX_RATMODE_ENUM_U32 enMode)
{
    SLEEP_MODE_ENUM_UINT32              enRatMode;
    VOS_UINT32                          ulRet;

    if (XMBX_MOD_1X == enMode)
    {
        enRatMode = VOS_RATMODE_1X;
    }
    else if (XMBX_MOD_HRPD == enMode)
    {
        /* 共票方案不出现HRPD */
        enRatMode = VOS_RATMODE_HRPD;
    }
    else
    {
        /* 其他通道强制转成1X */
        enRatMode = VOS_RATMODE_1X;
    }

    ulRet = SLEEP_BBE16GetLowPowerState(enRatMode);

    return ulRet;
}

/*****************************************************************************
 函 数 名  : SLEEP_BBE16MailBoxForceWakeDsp
 功能描述  : 封装的邮箱强制唤醒DSP的API
 输入参数  : enMode
 输出参数  : 无
 返 回 值  : VOS_FALSE  邮箱无消息
             VOS_TRUE   邮箱有消息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SLEEP_BBE16MailBoxForceWakeDsp(XMBX_RATMODE_ENUM_U32 enMode)
{
    SLEEP_MODE_ENUM_UINT32              enRatMode;

    if (XMBX_MOD_1X == enMode)
    {
        enRatMode = VOS_RATMODE_1X;
    }
    else if (XMBX_MOD_HRPD == enMode)
    {
        /* 共票方案不出现HRPD */
        enRatMode = VOS_RATMODE_HRPD;
    }
    else
    {
        /* 其他通道强制转成1X */
        enRatMode = VOS_RATMODE_1X;
        SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_MBX_OTHER_CHANNEL_TRACE);
    }

    SLEEP_BBE16ForceWakeProc(enRatMode);
}

/*****************************************************************************
 函 数 名  : SLEEP_BBE16GetLowPowerState
 功能描述  : 提供1X/HRPD低功耗状态判断
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32 VOS_TRUE    当前模式处于低功耗态
                        VOS_FALSE   当前模式处于正常状态
                        VOS_ERROR   传入模式错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  SLEEP_BBE16GetLowPowerState(SLEEP_MODE_ENUM_UINT32 enMode)
{
    VOS_UINT32                          ulRet   = VOS_TRUE;

    /* 禁止深睡投票，强制唤醒流程入口 */
    SLEEP_VoteLock(enMode);

    if (SLEEP_BBE16_NORMAL_STATE == g_astSleepBBE16ModeInfo[enMode].enSystemState)
    {
        ulRet   = VOS_FALSE;
    }

    return ulRet;
}

/*****************************************************************************
 函 数 名  : SLEEP_BBE16CprocWakeupProc
 功能描述  : OAM提供注册函数给CPROC注册wakeup proc
 输入参数  : SLEEP_BBE16_CPROC_WAKEUP_FUNC pFun
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月15日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SLEEP_BBE16CprocWakeupProc(SLEEP_BBE16_CPROC_WAKEUP_FUNC pFun, VOS_RATMODE_ENUM_UINT32 enMode, VOS_VOID* pulPara)
{
    if (VOS_NULL_PTR == pFun)
    {
        return;
    }

    g_stSleepCprocCtrl[enMode].pfnCprocWakeupProc   = pFun;
    g_stSleepCprocCtrl[enMode].pulCprocWakeupPara   = pulPara;
    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_BBE16CprocSleepProc
 功能描述  : OAM提供注册函数给CPROC注册sleep proc
 输入参数  : SLEEP_BBE16_CPROC_SLEEP_FUNC pFun
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月15日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SLEEP_BBE16CprocSleepProc(SLEEP_BBE16_CPROC_SLEEP_FUNC pFun, VOS_RATMODE_ENUM_UINT32 enMode, VOS_VOID* pulPara)
{
    if (VOS_NULL_PTR == pFun)
    {
        return;
    }

    g_stSleepCprocCtrl[enMode].pfnCprocSleepProc   = pFun;
    g_stSleepCprocCtrl[enMode].pulCprocSleepPara   = pulPara;

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_BBE16ForceWakeProc
 功能描述  : 邮箱发强制唤醒消息给OAM
 输入参数  : enMode
 输出参数  : 无
 返 回 值  : VOS_UINT32 VOS_TRUE    当前模式处于低功耗态
                        VOS_FALSE   当前模式处于正常状态
                        VOS_ERROR   传入模式错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月15日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  SLEEP_BBE16ForceWakeProc( SLEEP_MODE_ENUM_UINT32 enMode )
{
    if (VOS_RATMODE_1X == enMode)
    {

    }
    else if (VOS_RATMODE_HRPD == enMode)
    {
        /* 共票方案里mode不会是HRPD，如果mode为HRPD则打桩成1x并且记录错误 */
        SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_MASTER_FORCE_WAKE_MODE_ERR_TRACE);
        enMode = VOS_RATMODE_1X;
    }
    else
    {
        return;
    }

    /* 确认是否需要锁中断 */

    /* 在邮箱任务中，判断当前mode的状态不是NORMAL，要等待OAM的状态切换到NORMAL才能继续执行业务
       如果是WAKE或者是TEMP，说明OAM正在执行唤醒流程，这里不需要执行强制唤醒，只要等resume就行了
       如果是LOW_POWER或者是HALT，说明OAM已经睡了或者正在睡，这时要执行强制唤醒，然后等resume */
    if ((SLEEP_BBE16_MASTER_LP_STATE == g_astSleepBBE16ModeInfo[enMode].enSystemState)
        || (SLEEP_BBE16_MASTER_HALT_STATE == g_astSleepBBE16ModeInfo[enMode].enSystemState))
    {
        SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_MASTER_FORCE_WAKE_REQ_TRACE);
        SLEEP_AwakeIsrProc(BBE16_SLEEP_MASTER_WAKE_IND, enMode);
    }
    else if ((SLEEP_BBE16_SLAVE_LP_STATE == g_astSleepBBE16ModeInfo[enMode].enSystemState)
        || (SLEEP_BBE16_SLAVE_HALT_STATE == g_astSleepBBE16ModeInfo[enMode].enSystemState))
    {
        SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_SLAVE_FORCE_WAKE_REQ_TRACE);
        SLEEP_AwakeIsrProc(BBE16_SLEEP_SLAVE_WAKE_IND, enMode);
    }
    else
    {

    }

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_BBE16MasterForceWakeProc
 功能描述  : 邮箱发强制唤醒消息给OAM
 输入参数  : enMode
 输出参数  : 无
 返 回 值  : VOS_UINT32 VOS_TRUE    当前模式处于低功耗态
                        VOS_FALSE   当前模式处于正常状态
                        VOS_ERROR   传入模式错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月15日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  SLEEP_BBE16MasterForceWakeProc(MsgBlock *pstMsg)
{
    SLEEP_ISR_MSG_STRU                 *pstIsrReq;
    SLEEP_MODE_ENUM_UINT32              enMode;

    pstIsrReq = (SLEEP_ISR_MSG_STRU*)pstMsg;
    enMode    = pstIsrReq->enRatMode;

    /* OAM收到强制唤醒消息时，在获取硬件锁之前再判断一次状态
       如果此时不是LOW_POWER或者HALT说明在MailBox发起强制唤醒之后，进入了唤醒中断处理，这时就不需再做处理
       如果是LOW_POWER态则可以直接获取到硬件锁，如果是HALT态则获取硬件锁时会Pending直到睡眠完成
       这里不置WAKE状态，要在拿到锁之后置WAKE状态
    */
    if ((SLEEP_BBE16_MASTER_LP_STATE == g_astSleepBBE16ModeInfo[enMode].enSystemState)
        || (SLEEP_BBE16_MASTER_HALT_STATE == g_astSleepBBE16ModeInfo[enMode].enSystemState))
    {
        SLEEP_BBE16MasterForceWake(enMode);
    }
    else
    {
        /* 其他状态不做处理 */
    }

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_BBE16SlaveForceWakeProc
 功能描述  : 邮箱发强制唤醒消息给OAM
 输入参数  : enMode
 输出参数  : 无
 返 回 值  : VOS_UINT32 VOS_TRUE    当前模式处于低功耗态
                        VOS_FALSE   当前模式处于正常状态
                        VOS_ERROR   传入模式错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月15日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  SLEEP_BBE16SlaveForceWakeProc(MsgBlock *pstMsg)
{
    SLEEP_ISR_MSG_STRU                 *pstIsrReq;
    SLEEP_MODE_ENUM_UINT32              enMode;

    pstIsrReq = (SLEEP_ISR_MSG_STRU*)pstMsg;
    enMode    = pstIsrReq->enRatMode;

    if ((SLEEP_BBE16_SLAVE_LP_STATE == g_astSleepBBE16ModeInfo[enMode].enSystemState)
        || (SLEEP_BBE16_SLAVE_HALT_STATE == g_astSleepBBE16ModeInfo[enMode].enSystemState))
    {
        SLEEP_BBE16SlaveForceWake(enMode);
    }
    else
    {
        /* 其他状态不做处理 */
    }

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_BBE16MasterForceWake
 功能描述  : 判断是否在主模低功耗下，如果是则强制唤醒X模.
 输入参数  : enMode 模式
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月27日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SLEEP_BBE16MasterForceWake( SLEEP_MODE_ENUM_UINT32 enMode )
{
    VOS_INT                             lIntLevel;

    SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_MASTER_FORCE_WAKE_START_TRACE);

    (VOS_VOID)VOS_SmP(g_ulSleepSem, 0);

    SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_MASTER_FORCE_WAKE_SMP_TRACE);

    if (SLEEP_BBE16_MASTER_LP_STATE == g_astSleepBBE16ModeInfo[enMode].enSystemState)
    {
        /* 置WAKE态，如果当前唤醒被暂停，那么在twin模的resume中断里面可以根据WAKE态，继续执行这里的唤醒 */
        lIntLevel   = VOS_SplIMP();
        g_astSleepBBE16ModeInfo[enMode].enSystemState = SLEEP_BBE16_MASTER_WAKE_STATE;
        VOS_Splx(lIntLevel);

        /* 空指针返回 */
        if (VOS_NULL_PTR == g_pstBBE16SleepInfo)
        {
            /*lint -e534*/
            VOS_SmV(g_ulSleepSem);
            /*lint +e534*/
            return;
        }

        /* 如果twin模正在唤醒流程等resume中断时，则暂停当前模式的唤醒流程 */
        if (SLEEP_BBE16_MASTER_TEMP_NORMAL_STATE == SLEEP_BBE16GetTwinState(enMode))
        {

        }
        else
        {
            SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_MASTER_FORCE_WAKE_PROC_TRACE);

            SLEEP_BBE16ActivateHw(enMode);

            lIntLevel   = VOS_SplIMP();
            g_astSleepBBE16ModeInfo[enMode].enSystemState = SLEEP_BBE16_MASTER_TEMP_NORMAL_STATE;
            VOS_Splx(lIntLevel);

            /* 设置唤醒类型标志位,给csdr发送唤醒中断 */
            if (VOS_RATMODE_1X == enMode)
            {
                g_pstBBE16SleepInfo->enWakeUpMode       = CPHY_WAKEUP_MODE_1X;
                g_pstBBE16SleepInfo->en1xWakeUpType     = CPHY_OAM_FORCE_WAKE;

                (VOS_VOID)mdrv_ipc_int_send(IPC_CORE_BBE, IPC_XDSP_INT_SRC_CCPU_1X_WAKE);
            }
            else
            {
                g_pstBBE16SleepInfo->enWakeUpMode       = CPHY_WAKEUP_MODE_HRPD;
                g_pstBBE16SleepInfo->enHrpdWakeUpType   = CPHY_OAM_FORCE_WAKE;

                (VOS_VOID)mdrv_ipc_int_send(IPC_CORE_BBE, IPC_XDSP_INT_SRC_CCPU_HRPD_WAKE);
            }

            /* 延时200us(待确认具体延时时间) */
            SLEEP_TaskDelay(SLEEP_IPC_INT_DELAY_SLICE);
        }
    }
    else
    {
        /* 非预期的状态 */
    }

    /*lint -e534*/
    VOS_SmV(g_ulSleepSem);
    /*lint +e534*/

    SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_MASTER_FORCE_WAKE_END_TRACE);

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_BBE16SlaveForceWake
 功能描述  : 判断是否在从模低功耗下，如果是则强制唤醒X模.
 输入参数  : enMode 模式
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月27日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SLEEP_BBE16SlaveForceWake( SLEEP_MODE_ENUM_UINT32 enMode )
{
    SLEEP_MODE_ENUM_UINT32                                  enTwinMode;
    SLEEP_BBE16_SYSTEM_STATE_ENUM_UINT32                    enTwinState;
    VOS_INT                                                 lIntLevel;

    enTwinMode = SLEEP_BBE16GetTwinMode(enMode);

    SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_SLAVE_FORCE_WAKE_START_TRACE);

    (VOS_VOID)VOS_SmP(g_ulSleepSem, 0);

    SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_SLAVE_FORCE_WAKE_SMP_TRACE);

    if (SLEEP_BBE16_SLAVE_LP_STATE == g_astSleepBBE16ModeInfo[enMode].enSystemState)
    {
        /* 置WAKE态，如果当前唤醒被暂停，那么在twin模的resume中断里面可以根据WAKE态，继续执行这里的唤醒 */
        lIntLevel   = VOS_SplIMP();
        g_astSleepBBE16ModeInfo[enMode].enSystemState = SLEEP_BBE16_SLAVE_WAKE_STATE;
        VOS_Splx(lIntLevel);

        /* 空指针返回 */
        if (VOS_NULL_PTR == g_pstBBE16SleepInfo)
        {
            /*lint -e534*/
            VOS_SmV(g_ulSleepSem);
            /*lint +e534*/
            return;
        }

        /* 从模强制唤醒需要判断另一个模的低功耗状态，确认是否需要处理主模唤醒流程
           如果需要进行主模唤醒处理，暂存从模唤醒行为，等待主模唤醒成功后，继续从模唤醒流程 */
        enTwinState = SLEEP_BBE16GetTwinState(enMode);
        if ((SLEEP_BBE16_MASTER_LP_STATE == enTwinState)
          || (SLEEP_BBE16_MASTER_HALT_STATE == enTwinState))
        {
            /* 进行主模唤醒处理，这里通过发主模强制唤醒消息来实现 */
            SLEEP_AwakeIsrProc(BBE16_SLEEP_MASTER_WAKE_IND, enTwinMode);
        }
        /* 如果twin模正在唤醒流程等resume中断时，则暂停当前模式的唤醒流程 */
        else if ((SLEEP_BBE16_MASTER_TEMP_NORMAL_STATE == enTwinState)
               ||(SLEEP_BBE16_SLAVE_TEMP_NORMAL_STATE == enTwinState))
        {

        }
        else
        {
            SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_SLAVE_FORCE_WAKE_PROC_TRACE);

            SLEEP_BBE16ActivateHw(enMode);

            lIntLevel   = VOS_SplIMP();
            g_astSleepBBE16ModeInfo[enMode].enSystemState = SLEEP_BBE16_SLAVE_TEMP_NORMAL_STATE;
            VOS_Splx(lIntLevel);

            /* 设置唤醒类型标志位,给csdr发送唤醒中断 */
            if (VOS_RATMODE_1X == enMode)
            {
                g_pstBBE16SleepInfo->enWakeUpMode       = CPHY_WAKEUP_MODE_1X;
                g_pstBBE16SleepInfo->en1xWakeUpType     = CPHY_OAM_FORCE_WAKE;

                (VOS_VOID)mdrv_ipc_int_send(IPC_CORE_BBE, IPC_XDSP_INT_SRC_CCPU_1X_WAKE);
            }
            else
            {
                g_pstBBE16SleepInfo->enWakeUpMode       = CPHY_WAKEUP_MODE_HRPD;
                g_pstBBE16SleepInfo->enHrpdWakeUpType   = CPHY_OAM_FORCE_WAKE;

                (VOS_VOID)mdrv_ipc_int_send(IPC_CORE_BBE, IPC_XDSP_INT_SRC_CCPU_HRPD_WAKE);
            }

            /* 延时200us(待确认具体延时时间) */
            SLEEP_TaskDelay(SLEEP_IPC_INT_DELAY_SLICE);

            SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_SLAVE_FORCE_WAKE_END_TRACE);
        }
    }
    else
    {
        /* 非预期的状态 */
    }

    /*lint -e534*/
    VOS_SmV(g_ulSleepSem);
    /*lint +e534*/

    SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_SLAVE_FORCE_WAKE_END_TRACE);
    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_BBE16HaltIsrProc
 功能描述  : 将SLEEP模块中断处理转换为消息交互
 输入参数  : ulMsgId: 消息ID对应不同的中断
             enMode : 模块,1X/HRPD
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SLEEP_BBE16HaltIsrProc( VOS_UINT32 ulMsgId, SLEEP_MODE_ENUM_UINT32 enMode )
{
    VOS_INT                             lLockLevel;
    SLEEP_ISR_MSG_STRU                 *pstIsrMsg;

    lLockLevel = VOS_SplIMP();

    /* 禁止深睡投票 */
    SLEEP_VoteLock(enMode);

    /* 中断序列记录 */
    SLEEP_ISR_RECORD(ulMsgId, enMode);

    /* 分配消息内存 */
    pstIsrMsg = (SLEEP_ISR_MSG_STRU*)VOS_AllocMsg(WUEPS_PID_SLEEP,
                    sizeof(SLEEP_ISR_MSG_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstIsrMsg)
    {
        VOS_Splx(lLockLevel);

        return;
    }

    pstIsrMsg->ulReceiverPid = WUEPS_PID_SLEEP;
    pstIsrMsg->usMsgId       = (VOS_UINT16)ulMsgId;
    pstIsrMsg->enRatMode     = enMode;
    pstIsrMsg->ulSlice       = OM_GetSlice();

    if (VOS_OK != VOS_SendMsg(WUEPS_PID_SLEEP, pstIsrMsg))
    {
        /*; */
    }

    VOS_Splx(lLockLevel);

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_BBE16AwakeIsrProc
 功能描述  : 将SLEEP模块中断处理转换为消息交互
 输入参数  : ulMsgId: 消息ID对应不同的中断
             enMode : 模块,1X/HRPD
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SLEEP_BBE16AwakeIsrProc( VOS_UINT32 ulMsgId, SLEEP_MODE_ENUM_UINT32 enMode )
{
    VOS_INT                             lLockLevel;
    SLEEP_ISR_MSG_STRU                 *pstIsrMsg;

    lLockLevel = VOS_SplIMP();

    /* 禁止深睡投票 */
    SLEEP_VoteLock(enMode);

    /* 中断序列记录 */
    SLEEP_ISR_RECORD(ulMsgId, enMode);

    /* 分配消息内存 */
    pstIsrMsg = (SLEEP_ISR_MSG_STRU*)VOS_AllocMsg(WUEPS_PID_AWAKE,
                    sizeof(SLEEP_ISR_MSG_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstIsrMsg)
    {
        VOS_Splx(lLockLevel);

        return;
    }

    pstIsrMsg->ulReceiverPid = WUEPS_PID_AWAKE;
    pstIsrMsg->usMsgId       = (VOS_UINT16)ulMsgId;
    pstIsrMsg->enRatMode     = enMode;
    pstIsrMsg->ulSlice       = OM_GetSlice();

    if (VOS_OK != VOS_SendMsg(WUEPS_PID_AWAKE, pstIsrMsg))
    {
        /*; */
    }

    VOS_Splx(lLockLevel);

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_BBE16ResumeIsrProc
 功能描述  : 将SLEEP模块中断处理转换为消息交互
 输入参数  : ulMsgId: 消息ID对应不同的中断
             enMode : 模块,1X/HRPD
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SLEEP_BBE16ResumeIsrProc( VOS_UINT32 ulMsgId, SLEEP_MODE_ENUM_UINT32 enMode )
{
    VOS_INT                             lLockLevel;
    SLEEP_ISR_MSG_STRU                 *pstIsrMsg;

    lLockLevel = VOS_SplIMP();

    /* 禁止深睡投票 */
    SLEEP_VoteLock(enMode);

    /* 中断序列记录 */
    SLEEP_ISR_RECORD(ulMsgId, enMode);

    /* 分配消息内存 */
    pstIsrMsg = (SLEEP_ISR_MSG_STRU*)VOS_AllocMsg(WUEPS_PID_AWAKE,
                    sizeof(SLEEP_ISR_MSG_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstIsrMsg)
    {
        VOS_Splx(lLockLevel);

        return;
    }

    pstIsrMsg->ulReceiverPid = WUEPS_PID_AWAKE;
    pstIsrMsg->usMsgId       = (VOS_UINT16)ulMsgId;
    pstIsrMsg->enRatMode     = enMode;
    pstIsrMsg->ulSlice       = OM_GetSlice();

    if (VOS_OK != VOS_SendMsg(WUEPS_PID_AWAKE, pstIsrMsg))
    {
        /*; */
    }

    VOS_Splx(lLockLevel);

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_BBE16HaltMsgProc
 功能描述  : BBE16睡眠请求处理接口
 输入参数  : MsgBlock* pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SLEEP_BBE16HaltMsgProc( MsgBlock* pstMsg )
{
    SLEEP_ISR_MSG_STRU                 *pstIsrReq;
    SLEEP_MODE_ENUM_UINT32              enMode;

    pstIsrReq = (SLEEP_ISR_MSG_STRU*)pstMsg;

    enMode    = pstIsrReq->enRatMode;

    if ((VOS_RATMODE_1X == enMode) || (VOS_RATMODE_HRPD == enMode))
    {

    }
    else
    {
        return;
    }

    SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_HALT_START_TRACE);

    (VOS_VOID)VOS_SmP(g_ulSleepSem, 0);

    SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_HALT_SMP_TRACE);

    /* 睡眠处理前，邮箱状态判断，如果邮箱内还有残存的当前mode的消息待处理，直接唤醒BBE16 */
    if (VOS_FALSE == SLEEP_BBE16IsMailBoxAllowCBBE16Sleep(enMode))
    {
        SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_HALT_WAKE_START_TRACE);

        /* 调用CPROC回调函数，共票方案1X和HRPD都调，当前有几个模CPROC就注册几个模 */
        if (VOS_NULL_PTR != g_stSleepCprocCtrl[VOS_RATMODE_1X].pfnCprocSleepProc)
        {
            SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_HALT_CPROC_1X_SLEEP_TRACE);
            g_stSleepCprocCtrl[VOS_RATMODE_1X].pfnCprocSleepProc(g_stSleepCprocCtrl[VOS_RATMODE_1X].pulCprocSleepPara);
        }

        if (VOS_NULL_PTR != g_stSleepCprocCtrl[VOS_RATMODE_HRPD].pfnCprocSleepProc)
        {
            SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_HALT_CPROC_HRPD_SLEEP_TRACE);
            g_stSleepCprocCtrl[VOS_RATMODE_HRPD].pfnCprocSleepProc(g_stSleepCprocCtrl[VOS_RATMODE_HRPD].pulCprocSleepPara);
        }

        /* 状态切换到TEMP态 */
        if (SLEEP_BBE16_MASTER_HALT_STATE == g_astSleepBBE16ModeInfo[enMode].enSystemState)
        {
            g_astSleepBBE16ModeInfo[enMode].enSystemState = SLEEP_BBE16_MASTER_TEMP_NORMAL_STATE;
        }
        else
        {
            g_astSleepBBE16ModeInfo[enMode].enSystemState = SLEEP_BBE16_SLAVE_TEMP_NORMAL_STATE;
        }

        /* 设置唤醒类型标志位,给csdr发送唤醒中断 */
        if (VOS_RATMODE_1X == enMode)
        {
            g_pstBBE16SleepInfo->enWakeUpMode       = CPHY_WAKEUP_MODE_1X;
            g_pstBBE16SleepInfo->en1xWakeUpType     = CPHY_OAM_FORCE_WAKE;

            (VOS_VOID)mdrv_ipc_int_send(IPC_CORE_BBE, IPC_XDSP_INT_SRC_CCPU_1X_WAKE);
        }
        else
        {
            g_pstBBE16SleepInfo->enWakeUpMode       = CPHY_WAKEUP_MODE_HRPD;
            g_pstBBE16SleepInfo->enHrpdWakeUpType   = CPHY_OAM_FORCE_WAKE;

            (VOS_VOID)mdrv_ipc_int_send(IPC_CORE_BBE, IPC_XDSP_INT_SRC_CCPU_HRPD_WAKE);
        }

        /* 延时200us(待确认具体延时时间) */
        SLEEP_TaskDelay(SLEEP_IPC_INT_DELAY_SLICE);

        /*lint -e534*/
        VOS_SmV(g_ulSleepSem);
        /*lint +e534*/

        SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_HALT_WAKE_END_TRACE);
        return;
    }

    /* 调用CPROC回调函数，共票方案1X和HRPD都调，当前有几个模CPROC就注册几个模 */
    if (VOS_NULL_PTR != g_stSleepCprocCtrl[VOS_RATMODE_1X].pfnCprocSleepProc)
    {
        SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_HALT_CPROC_1X_SLEEP_TRACE);
        g_stSleepCprocCtrl[VOS_RATMODE_1X].pfnCprocSleepProc(g_stSleepCprocCtrl[VOS_RATMODE_1X].pulCprocSleepPara);
    }

    if (VOS_NULL_PTR != g_stSleepCprocCtrl[VOS_RATMODE_HRPD].pfnCprocSleepProc)
    {
        SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_HALT_CPROC_HRPD_SLEEP_TRACE);
        g_stSleepCprocCtrl[VOS_RATMODE_HRPD].pfnCprocSleepProc(g_stSleepCprocCtrl[VOS_RATMODE_HRPD].pulCprocSleepPara);
    }

    /* 执行下电处理 */
    if (SLEEP_BBE16_MASTER_HALT_STATE == g_astSleepBBE16ModeInfo[enMode].enSystemState)
    {
        SLEEP_BBE16DeactivateHw(enMode);

        g_astSleepBBE16ModeInfo[enMode].enSystemState = SLEEP_BBE16_MASTER_LP_STATE;
    }
    else if (SLEEP_BBE16_SLAVE_HALT_STATE == g_astSleepBBE16ModeInfo[enMode].enSystemState)
    {
        SLEEP_BBE16DeactivateHw(enMode);

        g_astSleepBBE16ModeInfo[enMode].enSystemState = SLEEP_BBE16_SLAVE_LP_STATE;
    }
    else
    {
    }

    /*
       在睡眠过程中不考虑收到唤醒中断，但是要考虑收到强制唤醒(OAM切换到HALT态后，邮箱有任务要处理，会强制唤醒)
       收到强制唤醒时，在WAKE任务中，判断当前是HALT态，要去等待睡眠流程执行结束，释放硬件锁之后进行唤醒操作
       获取到硬件锁之后再进行状态切换以及唤醒操作
    */

    /* 允许深睡投票 */
    SLEEP_VoteUnlock(enMode);

    /*lint -e534*/
    VOS_SmV(g_ulSleepSem);
    /*lint +e534*/

    SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_HALT_END_TRACE);

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_BBE16AwakeMsgProc
 功能描述  : BBP定时器唤醒中断转消息后的处理
 输入参数  : MsgBlock* pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SLEEP_BBE16AwakeMsgProc( MsgBlock* pstMsg )
{
    SLEEP_ISR_MSG_STRU                 *pstIsrReq;
    SLEEP_MODE_ENUM_UINT32              enMode;

    pstIsrReq = (SLEEP_ISR_MSG_STRU*)pstMsg;

    enMode    = pstIsrReq->enRatMode;

    if ((VOS_RATMODE_1X == enMode) || (VOS_RATMODE_HRPD == enMode))
    {

    }
    else
    {
        return;
    }

    SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_NORMAL_WAKE_START_TRACE);

    (VOS_VOID)VOS_SmP(g_ulSleepSem, 0);

    SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_NORMAL_WAKE_SMP_TRACE);

    /* 收到唤醒中断时，不考虑正在做睡眠，所以在唤醒中断里面置WAKE态 */
    if (SLEEP_BBE16_MASTER_WAKE_STATE == g_astSleepBBE16ModeInfo[enMode].enSystemState)
    {
        /* 如果twin模正在唤醒流程等resume中断时，则暂停当前模式的唤醒流程 */
        if (SLEEP_BBE16_MASTER_TEMP_NORMAL_STATE == SLEEP_BBE16GetTwinState(enMode))
        {

        }
        else
        {
            SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_NORMAL_WAKE_PROC_TRACE);

            /* 空指针返回 */
            if (VOS_NULL_PTR == g_pstBBE16SleepInfo)
            {
                /*lint -e534*/
                VOS_SmV(g_ulSleepSem);
                /*lint +e534*/
                return;
            }

            /* 执行上电处理 */
            SLEEP_BBE16ActivateHw(enMode);

            g_astSleepBBE16ModeInfo[enMode].enSystemState = SLEEP_BBE16_MASTER_TEMP_NORMAL_STATE;

            /* 设置唤醒类型标志位,给csdr发送唤醒中断 */
            if (VOS_RATMODE_1X == enMode)
            {
                g_pstBBE16SleepInfo->enWakeUpMode       = CPHY_WAKEUP_MODE_1X;
                g_pstBBE16SleepInfo->en1xWakeUpType     = CPHY_OAM_NORMAL_WAKE;

                (VOS_VOID)mdrv_ipc_int_send(IPC_CORE_BBE, IPC_XDSP_INT_SRC_CCPU_1X_WAKE);
            }
            else
            {
                g_pstBBE16SleepInfo->enWakeUpMode       = CPHY_WAKEUP_MODE_HRPD;
                g_pstBBE16SleepInfo->enHrpdWakeUpType   = CPHY_OAM_NORMAL_WAKE;

                (VOS_VOID)mdrv_ipc_int_send(IPC_CORE_BBE, IPC_XDSP_INT_SRC_CCPU_HRPD_WAKE);
            }

            /* 延时200us(待确认具体延时时间) */
            SLEEP_TaskDelay(SLEEP_IPC_INT_DELAY_SLICE);
        }
    }

    /*lint -e534*/
    VOS_SmV(g_ulSleepSem);
    /*lint +e534*/

    SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_NORMAL_WAKE_END_TRACE);

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_BBE16ResumeMsgProc
 功能描述  : BBE16睡眠请求处理接口
 输入参数  : MsgBlock* pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SLEEP_BBE16ResumeMsgProc( MsgBlock* pstMsg )
{
    SLEEP_ISR_MSG_STRU                 *pstIsrReq;
    SLEEP_MODE_ENUM_UINT32              enMode;
    SLEEP_MODE_ENUM_UINT32              enTwinMode;

    pstIsrReq  = (SLEEP_ISR_MSG_STRU*)pstMsg;

    enMode     = pstIsrReq->enRatMode;
    enTwinMode = SLEEP_BBE16GetTwinMode(enMode);

    if ((VOS_RATMODE_1X == enMode) || (VOS_RATMODE_HRPD == enMode))
    {

    }
    else
    {
        return;
    }

    SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_RESUME_START_TRACE);

    (VOS_VOID)VOS_SmP(g_ulSleepSem, 0);

    /* Resume中断不做状态判断，放到任务里判 */
    if ((SLEEP_BBE16_MASTER_TEMP_NORMAL_STATE == g_astSleepBBE16ModeInfo[enMode].enSystemState)
     || (SLEEP_BBE16_SLAVE_TEMP_NORMAL_STATE == g_astSleepBBE16ModeInfo[enMode].enSystemState))
    {

    }
    else
    {
        /*lint -e534*/
        VOS_SmV(g_ulSleepSem);
        /*lint +e534*/

        SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_RESUME_INT_NOT_TEMP_TRACE);
        return;
    }

    g_astSleepBBE16ModeInfo[enMode].enSystemState = SLEEP_BBE16_NORMAL_STATE;

    SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_RESUME_SMP_TRACE);

    /* 调用邮箱接口，通知邮箱resume ind */
    SLEEP_BBE16MailBoxResumeProc(enMode);

    /* 调用CPROC回调函数，共票方案1X和HRPD都调，当前有几个模CPROC就注册几个模 */
    if (VOS_NULL_PTR != g_stSleepCprocCtrl[VOS_RATMODE_1X].pfnCprocWakeupProc)
    {
        SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_RESUME_CPROC_1X_WAKEUP_TRACE);
        g_stSleepCprocCtrl[VOS_RATMODE_1X].pfnCprocWakeupProc(g_stSleepCprocCtrl[VOS_RATMODE_1X].pulCprocWakeupPara);
    }

    if (VOS_NULL_PTR != g_stSleepCprocCtrl[VOS_RATMODE_HRPD].pfnCprocWakeupProc)
    {
        SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_RESUME_CPROC_HRPD_WAKEUP_TRACE);
        g_stSleepCprocCtrl[VOS_RATMODE_HRPD].pfnCprocWakeupProc(g_stSleepCprocCtrl[VOS_RATMODE_HRPD].pulCprocWakeupPara);
    }

    /* 睡眠唤醒流程结束，上报记录信息 */
    SLEEP_ReportEvent((VOS_UINT16)BBE16_SLEEP_TRACE_STACK_IND, enMode);

    /* 判断twin模是否在唤醒状态，如果在唤醒状态，则需要进行twin模的唤醒流程处理 */
    if (SLEEP_BBE16_MASTER_WAKE_STATE == SLEEP_BBE16GetTwinState(enMode))
    {
        /* 空指针返回 */
        if (VOS_NULL_PTR == g_pstBBE16SleepInfo)
        {
            /*lint -e534*/
            VOS_SmV(g_ulSleepSem);
            /*lint +e534*/
            return;
        }

        SLEEP_BBE16ActivateHw(enTwinMode);

        g_astSleepBBE16ModeInfo[enTwinMode].enSystemState = SLEEP_BBE16_MASTER_TEMP_NORMAL_STATE;

        /* 设置唤醒类型标志位,给csdr发送唤醒中断 */
        if (VOS_RATMODE_1X == enTwinMode)
        {
            g_pstBBE16SleepInfo->enWakeUpMode       = CPHY_WAKEUP_MODE_1X;
            g_pstBBE16SleepInfo->en1xWakeUpType     = CPHY_OAM_FORCE_WAKE;

            (VOS_VOID)mdrv_ipc_int_send(IPC_CORE_BBE, IPC_XDSP_INT_SRC_CCPU_1X_WAKE);
        }
        else
        {
            g_pstBBE16SleepInfo->enWakeUpMode       = CPHY_WAKEUP_MODE_HRPD;
            g_pstBBE16SleepInfo->enHrpdWakeUpType   = CPHY_OAM_FORCE_WAKE;

            (VOS_VOID)mdrv_ipc_int_send(IPC_CORE_BBE, IPC_XDSP_INT_SRC_CCPU_HRPD_WAKE);
        }

        /* 延时200us(待确认具体延时时间) */
        SLEEP_TaskDelay(SLEEP_IPC_INT_DELAY_SLICE);
    }
    else if (SLEEP_BBE16_SLAVE_WAKE_STATE == SLEEP_BBE16GetTwinState(enMode))
    {
        SLEEP_BBE16ActivateHw(enTwinMode);

        g_astSleepBBE16ModeInfo[enTwinMode].enSystemState = SLEEP_BBE16_SLAVE_TEMP_NORMAL_STATE;

        /* 设置唤醒类型标志位,给csdr发送唤醒中断 */
        if (VOS_RATMODE_1X == enTwinMode)
        {
            g_pstBBE16SleepInfo->enWakeUpMode       = CPHY_WAKEUP_MODE_1X;

            (VOS_VOID)mdrv_ipc_int_send(IPC_CORE_BBE, IPC_XDSP_INT_SRC_CCPU_1X_WAKE);
        }
        else
        {
            g_pstBBE16SleepInfo->enHrpdWakeUpType   = CPHY_OAM_NORMAL_WAKE;

            (VOS_VOID)mdrv_ipc_int_send(IPC_CORE_BBE, IPC_XDSP_INT_SRC_CCPU_HRPD_WAKE);
        }

        /* 延时200us(待确认具体延时时间) */
        SLEEP_TaskDelay(SLEEP_IPC_INT_DELAY_SLICE);
    }
    else
    {
        /* for pclint */
    }

    /*lint -e534*/
    VOS_SmV(g_ulSleepSem);
    /*lint +e534*/

    SLEEP_BBE16_NOR_STATE_TRACK(enMode, SLEEP_BBE16_RESUME_END_TRACE);

    return;
}

/*****************************************************************************
 函 数 名  : SLEEP_BBE16DbgInit
 功能描述  : 维测信息初始化
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SLEEP_BBE16DbgInit(VOS_VOID)
{
    if (VOS_NULL_PTR == g_pstSleepBBE16NormalState)
    {
        return;
    }

    /* Main Track*/
    /* Halt */
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_HALT_INT_TRACE].pucTrackId                    = "Halt Int";
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_HALT_START_TRACE].pucTrackId                  = "Halt Msg";
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_HALT_END_TRACE].pucTrackId                    = "Halt End";

    /* Normal Wake */
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_NORMAL_WAKE_INT_TRACE].pucTrackId             = "Wake Int";
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_NORMAL_WAKE_START_TRACE].pucTrackId           = "Wake Msg";
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_NORMAL_WAKE_END_TRACE].pucTrackId             = "Wake End";

    /* Master Force Wake */
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_MASTER_FORCE_WAKE_REQ_TRACE].pucTrackId       = "MasteReq";
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_MASTER_FORCE_WAKE_START_TRACE].pucTrackId     = "MasteMsg";
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_MASTER_FORCE_WAKE_END_TRACE].pucTrackId       = "MasteEnd";

    /* Slave Force Wake */
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_SLAVE_FORCE_WAKE_REQ_TRACE].pucTrackId        = "SlaveReq";
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_SLAVE_FORCE_WAKE_START_TRACE].pucTrackId      = "SlaveMsg";
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_SLAVE_FORCE_WAKE_END_TRACE].pucTrackId        = "SlaveEnd";

    /* Resume */
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_RESUME_INT_TRACE].pucTrackId                  = "Rsme Int";
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_RESUME_START_TRACE].pucTrackId                = "Rsme Msg";
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_RESUME_END_TRACE].pucTrackId                  = "Rsme End";

    /* ACT */
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_DEACTIVATE_START].pucTrackId                  = "DeactStr";
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_DEACTIVATE_END].pucTrackId                    = "DeactEnd";
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_ACTIVATE_START].pucTrackId                    = "ActivStr";
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_ACTIVATE_END].pucTrackId                      = "ActivEnd";

    /* Assist Track */
    /* Halt */
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_HALT_INT_TO_MSG_TRACE].pucTrackId             = "Halt IntToMsg";
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_HALT_SMP_TRACE].pucTrackId                    = "Halt  SmpSucc";
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_HALT_WAKE_START_TRACE].pucTrackId             = "Halt  WakeStr";
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_HALT_WAKE_END_TRACE].pucTrackId               = "Halt  WakeEnd";
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_HALT_CPROC_1X_SLEEP_TRACE].pucTrackId         = "Halt  1xSleep";
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_HALT_CPROC_HRPD_SLEEP_TRACE].pucTrackId       = "Halt  DoSleep";

    /* Normal Wake */
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_NORMAL_WAKE_INT_TO_MSG_TRACE].pucTrackId      = "Wake IntToMsg";
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_NORMAL_WAKE_SMP_TRACE].pucTrackId             = "Wake  SmpSucc";
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_NORMAL_WAKE_PROC_TRACE].pucTrackId            = "Wake     Proc";

    /* Master Force Wake */
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_MASTER_FORCE_WAKE_SMP_TRACE].pucTrackId       = "MasterSmpSucc";
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_MASTER_FORCE_WAKE_PROC_TRACE].pucTrackId      = "Master   Proc";

    /* Slave Force Wake */
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_SLAVE_FORCE_WAKE_SMP_TRACE].pucTrackId        = "Slave SmpSucc";
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_SLAVE_FORCE_WAKE_PROC_TRACE].pucTrackId       = "Slave    Proc";

    /* Resume */
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_RESUME_INT_TO_MSG_TRACE].pucTrackId           = "Rsme IntToMsg";
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_RESUME_SMP_TRACE].pucTrackId                  = "Rsme  SmpSucc";
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_RESUME_CPROC_1X_WAKEUP_TRACE].pucTrackId      = "Rsme 1xWakeup";
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_RESUME_CPROC_HRPD_WAKEUP_TRACE].pucTrackId    = "Rsme DoWakeup";

    /* Abnormal Track */
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_HALT_INT_NOT_NORMAL_TRACE].pucTrackId         = "Halt StatuErr";
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_WAKE_INT_NOT_LP_TRACE].pucTrackId             = "Wake StatuErr";
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_RESUME_INT_NOT_TEMP_TRACE].pucTrackId         = "Rsme StatuErr";
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_MASTER_FORCE_WAKE_MODE_ERR_TRACE].pucTrackId  = "Force ModeErr";
    g_pstSleepBBE16NormalState->astRecordItem[VOS_RATMODE_1X][SLEEP_BBE16_MBX_OTHER_CHANNEL_TRACE].pucTrackId           = "Xmbx  Channel";

    return;
}
#endif

/*****************************************************************************
 函 数 名  : SLEEP_Init
 功能描述  : SLEEP模块初始化函数
 输入参数  : VOS_VOID

 输出参数  :

 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年07月31日
    作    者   : g47350
    修改内容   : V900R001项目新增函数

*****************************************************************************/
VOS_VOID SLEEP_Init(VOS_VOID)
{
    SLEEP_MODE_ENUM_UINT32              enMode;
    /*lint -e438 屏蔽ulRecordAddr没有使用的错误*/
    VOS_UINT32                          ulRecordAddr;
    UCOM_NV_TRI_MODE_ENABLE_STRU        stRfSwitchFlag;
    BSP_DDR_SECT_QUERY_S                stModemSrSectQuery;
    BSP_DDR_SECT_INFO_S                 stModemSrSectInfo = {BSP_DDR_SECT_TYPE_MODEM_SR_STAMP};

    /* 初始化定位信息 */
    ulRecordAddr = (VOS_UINT32)VOS_EXCH_MEM_MALLOC(VOS_DUMP_MEM_TOTAL_SIZE);

#if defined (INSTANCE_1)
    if (VOS_NULL_PTR != ulRecordAddr)
    {
        ulRecordAddr += sizeof(VOS_UINT32);

        ulRecordAddr += sizeof(SLEEP_TRACK_RECORD_STRU) + sizeof(SLEEP_NORMAL_STATE_RECORD_STRU)
                        + sizeof(SLEEP_DEVICE_STATE_STRU) + sizeof(SLEEP_INFO_STATE_STRU) + sizeof(SLEEP_BBE16_NORMAL_STATE_RECORD_STRU);
    }
#elif defined (INSTANCE_2)
    if (VOS_NULL_PTR != ulRecordAddr)
    {
        ulRecordAddr += 2*sizeof(VOS_UINT32);

        ulRecordAddr += 2*(sizeof(SLEEP_TRACK_RECORD_STRU) + sizeof(SLEEP_NORMAL_STATE_RECORD_STRU)
                        + sizeof(SLEEP_DEVICE_STATE_STRU) + sizeof(SLEEP_INFO_STATE_STRU) + sizeof(SLEEP_BBE16_NORMAL_STATE_RECORD_STRU));
    }
#endif

    if (VOS_NULL_PTR != ulRecordAddr)
    {
        *(VOS_UINT32*)ulRecordAddr = 0x5555aaaa;

        ulRecordAddr += sizeof(VOS_UINT32);

        g_pstSleepTrackRecord = (SLEEP_TRACK_RECORD_STRU*)ulRecordAddr;

        /*lint -e534*/
        VOS_MemSet(g_pstSleepTrackRecord, 0, sizeof(SLEEP_TRACK_RECORD_STRU));
        /*lint +e534*/

        ulRecordAddr += sizeof(SLEEP_TRACK_RECORD_STRU);

        g_pstSleepNormalState = (SLEEP_NORMAL_STATE_RECORD_STRU*)ulRecordAddr;

        /*lint -e534*/
        VOS_MemSet(g_pstSleepNormalState, 0, sizeof(SLEEP_NORMAL_STATE_RECORD_STRU));
        /*lint +e534*/

        ulRecordAddr += sizeof(SLEEP_NORMAL_STATE_RECORD_STRU);

        g_pstSleepDeviceState   = (SLEEP_DEVICE_STATE_STRU *)ulRecordAddr;

        /*lint -e534*/
        VOS_MemSet(g_pstSleepDeviceState,   0, sizeof(SLEEP_DEVICE_STATE_STRU));
        /*lint +e534*/

        ulRecordAddr += sizeof(SLEEP_DEVICE_STATE_STRU);

        g_pstSleepDeviceState->ulDeviceFlag = 0x5A5A5A5A;

        g_pstSleepInfoSlice      = (SLEEP_INFO_STATE_STRU *)ulRecordAddr;

        ulRecordAddr += sizeof(SLEEP_INFO_STATE_STRU);

        g_pstSleepInfoSlice->ulEndFlag   = 0x87878787;

        g_pstSleepBBE16NormalState = (SLEEP_BBE16_NORMAL_STATE_RECORD_STRU*)ulRecordAddr;

        /*lint -e534*/
        VOS_MemSet(g_pstSleepBBE16NormalState, 0, sizeof(SLEEP_BBE16_NORMAL_STATE_RECORD_STRU));
        /*lint +e534*/

        ulRecordAddr += sizeof(SLEEP_BBE16_NORMAL_STATE_RECORD_STRU);
    }

    /* 初始化系统状态 */
    for (enMode = 0; enMode < SLEEP_GU_MODE_TYPE_BUTT; enMode++)
    {
        g_astSleepModeInfo[enMode].enSystemState = SLEEP_NORMAL_STATE;
    }

    for (enMode = 0; enMode < SLEEP_C_MODE_TYPE_BUTT; enMode++)
    {
        g_astSleepBBE16ModeInfo[enMode].enSystemState   = SLEEP_BBE16_NORMAL_STATE;
        g_astSleepBBE16ModeInfo[enMode].enCdmaSleepType = CPHY_SLEEP_TYPE_NONE;
    }

    g_stSleepCDMAControl.ulInfoHeadFlag     = 0x5A5A5A5A;
    g_stSleepCDMAControl.ulBBE16PowerState  = VOS_FALSE;

    if(VOS_OK != VOS_SmMCreate("SLEEP", VOS_SEMA4_PRIOR | VOS_SEMA4_INVERSION_SAFE, &g_ulSleepSem))
    {
        /*lint -e534*/
        LogPrint("SLEEP_Init: Create SLEEP.\r\n");
        /*lint +e534*/
        return;
    }

    if(VOS_OK != VOS_SmCCreate("TCXO", 0, VOS_SEMA4_FIFO, &g_ulSleepTcxoSem))
    {
        /*lint -e534*/
        LogPrint("SLEEP_Init: Create TCXO.\r\n");
        /*lint +e534*/
        return;
    }

#if (FEATURE_GUC_BBP_TRIG == FEATURE_OFF)
    if(VOS_OK != VOS_SmCCreate("DMA", 0, VOS_SEMA4_FIFO, &g_ulSleepDMACapSem))
    {
        /*lint -e534*/
        LogPrint("SLEEP_Init: Create DMA.\r\n");
        /*lint +e534*/
        return;
    }
#endif

#if defined (INSTANCE_1) || defined (INSTANCE_2)
#else
    if(VOS_OK != VOS_SmBCreate("Ssem", VOS_SEM_FULL, VOS_SEMA4_PRIOR | VOS_SEMA4_INVERSION_SAFE, &g_ulSleepSlaveSem))
    {
        /*lint -e534*/
        LogPrint("SLEEP_Init: Create Ssem.\r\n");
        /*lint +e534*/
        return;
    }
#endif

    /* 读取NV器件稳定时间 */
    if(NV_OK != NV_Read(en_NV_Item_WG_DRX_RESUME_TIME, &g_stSleepDrxResumeTime, sizeof(WG_DRX_RESUME_TIME_STRU)))
    {
        /*lint -e534*/
        LogPrint("SLEEP_Init: Read en_NV_Item_WG_DRX_RESUME_TIME Fail.\r\n");
        /*lint +e534*/
        return;
    }

    /* 读取DRX上电流程异常控制使能标志 */
    if(NV_OK != NV_Read(en_NV_Item_DRX_RESET_ENABLE_CFG, &g_bDrxResetFlag, sizeof(NV_SLEEP_DRX_RESET_ENABLE_STRU)))
    {
        /*lint -e534*/
        LogPrint("SLEEP_Init: Read en_NV_Item_DRX_RESET_ENABLE_CFG Fail.\r\n");
        /*lint +e534*/
        return;
    }

    /* 读取全网通Profile Index控制项 */
    if(NV_OK != NV_Read(en_NV_Item_TRI_MODE_FEM_PROFILE_ID, &g_stChannelModeProfileId, sizeof(UCOM_NV_TRI_MODE_FEM_PROFILE_ID_STRU)))
    {
        /*lint -e534*/
        LogPrint("SLEEP_Init: Read en_NV_Item_TRI_MODE_FEM_PROFILE_ID Fail.\r\n");
        /*lint +e534*/

        VOS_ProtectionReboot(DRX_FULLNET_SET_ERROR, VOS_FILE_ID, __LINE__, VOS_NULL_PTR, VOS_NULL);

        return;
    }

    if (g_stChannelModeProfileId.uwProfileId >= UCOM_NV_TRI_MODE_CHAN_PARA_PROFILE_NUM)
    {
        VOS_ProtectionReboot(DRX_FULLNET_SET_ERROR, VOS_FILE_ID, __LINE__, VOS_NULL_PTR, VOS_NULL);
    }

#if (FEATURE_ON == FEATURE_MODE_FEM_CHAN_EXT)
    /* 读取模式通道配置项 */
    if(NV_OK != NV_Read(en_NV_Item_FEM_CHAN_PROFILE, &g_stChannelModeProfile, sizeof(UCOM_NV_FEM_CHAN_PROFILE_STRU)))
    {
        /*lint -e534*/
        LogPrint("SLEEP_Init: Read en_NV_Item_FEM_CHAN_PROFILE Fail.\r\n");
        /*lint +e534*/

        VOS_ProtectionReboot(DRX_FULLNET_SET_ERROR, VOS_FILE_ID, __LINE__, VOS_NULL_PTR, VOS_NULL);

        return;
    }
#else
    /* 读取模式通道配置项 */
    if(NV_OK != NV_Read(en_NV_Item_TRI_MODE_FEM_CHAN_PROFILE, &g_stChannelModeProfile, sizeof(UCOM_NV_TRI_MODE_FEM_CHAN_PROFILE_STRU)))
    {
        /*lint -e534*/
        LogPrint("SLEEP_Init: Read en_NV_Item_TRI_MODE_FEM_CHAN_PROFILE Fail.\r\n");
        /*lint +e534*/

        VOS_ProtectionReboot(DRX_FULLNET_SET_ERROR, VOS_FILE_ID, __LINE__, VOS_NULL_PTR, VOS_NULL);

        return;
    }
#endif

    /* 读取全网通Profile Index控制项 */
    if(NV_OK != NV_Read(en_NV_Item_TRI_MODE_ENABLE, &stRfSwitchFlag, sizeof(UCOM_NV_TRI_MODE_ENABLE_STRU)))
    {
        /*lint -e534*/
        LogPrint("SLEEP_Init: Read en_NV_Item_TRI_MODE_ENABLE Fail.\r\n");
        /*lint +e534*/

        return;
    }

#if defined (INSTANCE_1) || defined (INSTANCE_2)
#else
    if (VOS_TRUE == stRfSwitchFlag.uhwEnable)
    {
        if (VOS_TRUE == g_stChannelModeProfile.astPara[g_stChannelModeProfileId.uwProfileId].uwGpioCtrl)
        {
            /* 全网通功能需要开机时配置射频管脚 */
            if ( VOS_OK != mdrv_fem_ioctrl(CFG_RFFE_GROUP_GPIO_MIPI, UPHY_OAM_NV_INDEX_FULL_NET, 0, VOS_NULL))
            {
                VOS_ProtectionReboot(DRX_FULLNET_SET_ERROR, VOS_FILE_ID, __LINE__, VOS_NULL_PTR, VOS_NULL);

                return;
            }
        }
        else
        {
            /* 全网通功能需要开机时配置射频管脚 */
            if ( VOS_OK != mdrv_fem_ioctrl(CFG_RFFE_GROUP_GPIO_MIPI, UPHY_OAM_NV_INDEX_FULL_NET, 1, VOS_NULL))
            {
                VOS_ProtectionReboot(DRX_FULLNET_SET_ERROR, VOS_FILE_ID, __LINE__, VOS_NULL_PTR, VOS_NULL);

                return;
            }
        }
    }
#endif

    /* 开机时配置底软上下电通道 */
    if ( VOS_OK != SLEEP_GBBPClkSrcSelect() )
    {
        VOS_ProtectionReboot(DRX_FULLNET_SET_ERROR, VOS_FILE_ID, __LINE__, VOS_NULL_PTR, VOS_NULL);

        return;
    }

    stModemSrSectQuery.enSectType   = BSP_DDR_SECT_TYPE_MODEM_SR_STAMP;

    if (VOS_OK == mdrv_get_fix_ddr_addr(&stModemSrSectQuery, &stModemSrSectInfo))
    {
        g_pstSleepWakeSliceAddr  = (T_MODEM_SR_STAMP_STRU *)((VOS_UINT32)stModemSrSectInfo.pSectVirtAddr);
    }

    SLEEP_TimeCal();

    /* 注册SLEEP钩子函数给OSA */
    /*lint -e534*/
    VOS_RegisterAwakeFun(SLEEP_GetModemId(), SLEEP_HookMsgProc);
    /*lint +e534*/

    SLEEP_NotifyStateRegPidTblInit();

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* 全局变量指向SRAM */
    g_pstBBE16SleepInfo = (CPHY_OAM_SHARE_INFO_STRU *)CPHY_SRAM_ADDR;

    if (VOS_NULL_PTR == g_pstBBE16SleepInfo)
    {
        (VOS_VOID)vos_printf("SLEEP get SRAM fail!\r\n");

        return;
    }

    SLEEP_BBE16DbgInit();

    mlp_dsp_init();

    /* 调用邮箱注册接口 注册两个函数 */
    mdrv_MailBox_GetCdmaStatusReg((BSP_xMBX_GET_STATUS_FUNC)SLEEP_BBE16MailBoxGetDspState);
    mdrv_MailBox_CdmaForceAwakeReg((BSP_xMBX_DSP_AWAKE_FUNC)SLEEP_BBE16MailBoxForceWakeDsp);
#endif

    return;
    /*lint +e438 屏蔽ulRecordAddr没有使用的错误*/
}

/*****************************************************************************
 函 数 名  : WuepsAwakePidInit
 功能描述  : Awake 模块 PID 的初始化函数
 输入参数  : ip: 初始化步骤

 输出参数  :

 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月09日
    作    者   : s00207770
    修改内容   : 低功耗任务优先级拆分项目新增函数

*****************************************************************************/
VOS_UINT32 WuepsAwakePidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    switch( ip )
    {
        case VOS_IP_LOAD_CONFIG:
            break;

        default:
            break;
    }

    return VOS_OK;
}

VOS_UINT32 WuepsAwakeFidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32                          ulRslt;

    switch( ip )
    {
        case VOS_IP_LOAD_CONFIG:
        {
            ulRslt = VOS_RegisterPIDInfo(WUEPS_PID_AWAKE,
                                        (Init_Fun_Type)WuepsAwakePidInit,
                                        (Msg_Fun_Type)SLEEP_AwakeMsgProc);

            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterTaskPrio(WUEPS_FID_AWAKE, COMM_AWAKE_TASK_PRIO);

            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            break;
        }

        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : WuepsSleepPidInit
 功能描述  : SLEEP 模块 PID 的初始化函数
 输入参数  : ip: 初始化步骤

 输出参数  :

 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年07月31日
    作    者   : g47350
    修改内容   : V900R001项目新增函数

*****************************************************************************/
VOS_UINT32 WuepsSleepPidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    switch( ip )
    {
        case VOS_IP_LOAD_CONFIG:
            break;

        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : WuepsSleepFidInit
 功能描述  : SLEEP 模块 FID 的初始化函数
 输入参数  : enum VOS_INIT_PHASE_DEFINE ip
 输出参数  : 无
 返 回 值  : VOS_UINT32 FID 初始化结果
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 WuepsSleepFidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32                          ulRslt;

    switch( ip )
    {
        case VOS_IP_LOAD_CONFIG:
        {
            ulRslt = VOS_RegisterPIDInfo(WUEPS_PID_SLEEP,
                                        (Init_Fun_Type)WuepsSleepPidInit,
                                        (Msg_Fun_Type)SLEEP_SleepMsgProc);

            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterTaskPrio(WUEPS_FID_SLEEP, COMM_SLEEP_TASK_PRIO);

            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            SLEEP_Init();

            break;
        }

        default:
            break;
    }

    return VOS_OK;
}

VOS_VOID SLEEP_GUChannelShow(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_MODE_FEM_CHAN_EXT)
    /*lint -e534*/
    vos_printf("\r\n FEATURE_MODE_FEM_CHAN_EXT ON Channel\r\n");

    vos_printf("GSM ABB   CHAN is %d\r\n", SLEEP_ABB_CHAN(VOS_RATMODE_GSM));
    vos_printf("GSM RF    CHAN is %d\r\n", SLEEP_RF_CHAN(VOS_RATMODE_GSM));
    vos_printf("GSM TCXO  CHAN is %d\r\n", SLEEP_TCXO_CHAN(VOS_RATMODE_GSM));
    vos_printf("GSM RFCLK CHAN is %d\r\n", SLEEP_RFCLK_CHAN(VOS_RATMODE_GSM));

    vos_printf("WCDMA ABB   CHAN is %d\r\n", SLEEP_ABB_CHAN(VOS_RATMODE_WCDMA));
    vos_printf("WCDMA RF    CHAN is %d\r\n", SLEEP_RF_CHAN(VOS_RATMODE_WCDMA));
    vos_printf("WCDMA TCXO  CHAN is %d\r\n", SLEEP_TCXO_CHAN(VOS_RATMODE_WCDMA));
    vos_printf("WCDMA RFCLK CHAN is %d\r\n", SLEEP_RFCLK_CHAN(VOS_RATMODE_WCDMA));
    /*lint +e534*/
#else
    /*lint -e534*/
    vos_printf("\r\n FEATURE_MODE_FEM_CHAN_EXT OFF Channel\r\n");

    vos_printf("GSM ABB   CHAN is %d\r\n", SLEEP_ABB_CHAN(VOS_RATMODE_GSM));
    vos_printf("GSM RF    CHAN is %d\r\n", SLEEP_RF_CHAN(VOS_RATMODE_GSM));
    vos_printf("GSM TCXO  CHAN is %d\r\n", SLEEP_TCXO_CHAN(VOS_RATMODE_GSM));

    vos_printf("WCDMA ABB   CHAN is %d\r\n", SLEEP_ABB_CHAN(VOS_RATMODE_WCDMA));
    vos_printf("WCDMA RF    CHAN is %d\r\n", SLEEP_RF_CHAN(VOS_RATMODE_WCDMA));
    vos_printf("WCDMA TCXO  CHAN is %d\r\n", SLEEP_TCXO_CHAN(VOS_RATMODE_WCDMA));
    /*lint +e534*/
#endif
}

/*****************************************************************************
 函 数 名  : SLEEP_WakeSliceShow
 功能描述  : 唤醒时刻打点显示
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月24日
    作    者   : S00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SLEEP_WakeSliceShow( VOS_VOID )
{
    VOS_UINT32                          i;

    if (VOS_NULL_PTR != g_pstSleepWakeSliceAddr)
    {
        for (i = 0; i < 8; i++)
        {
            /*lint -e534*/
            vos_printf("SLEEP Wake Slice[%d] is %x\r\n", i, g_pstSleepWakeSliceAddr->auwCommSRStamp[i]);
            /*lint +e534*/
        }
    }
}

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif

