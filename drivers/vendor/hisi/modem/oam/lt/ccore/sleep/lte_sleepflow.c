/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : SleepFlow.c
  版 本 号   : 初稿
  作    者   : fuxin 00221597
  生成日期   : 2013年05月20日
  最近修改   :
  功能描述   : 实现 RTT SLEEP 睡眠/唤醒流程驱动
  函数列表   :
  修改历史   :
******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*lint -save -e537*/
#include <lte_sleepflow.h>
#include "msp_errno.h"
#include "msp_sleep.h"

#include "msp_nvim.h"
#include <phyoaminterface.h>

#if (VOS_VXWORKS == VOS_OS_VER)
#include <cacheLib.h>
#endif

/*lint -restore*/

/*用于控制打开关闭MSP部分低功耗*/
#ifndef OPEN_MSP_SLEEP
#define OPEN_MSP_SLEEP
#endif

#ifndef MSP_IN_V9R1
#include <TLPhyInterface.h>
#else
#include <global_sram_map.h>
#endif

/*lint --e{1358, 40, 830, 539, 717, 746, 774, 534}*/

#define    THIS_FILE_ID   (MSP_FILE_ID_LTE_SLEEPFLOW_C)

/*直接获取时间戳前后差值*/
#define msp_get_timer_slice_delta(begin,end) ((end>=begin)?(end-begin):(0xFFFFFFFF-begin+end))

#define TLSLEEP_SAVE_SR_STAMP(a)  (g_modem_stamp->auwMSPSRStamp[a] = mdrv_timer_get_normal_timestamp())

struct msp_power_control g_msp_pwrctrl = {0}; /*lint !e19*/
struct msp_delay_control g_msp_delay = {0, 5};
struct msp_hids_control g_msp_hidsctrl = {0, 0};
DRV_DRX_DELAY_STRU g_msp_drx_delay = {0};
VOS_INT dfs_bus_req_id = 0;
VOS_INT dfs_ddr_req_id = 0;
VOS_INT dfs_ccpu_req_id = 0;

VOS_UINT32 g_ulAddrShrDdr = 0;

TL_SLEEP_NOTIFY_FUNC pSleepFunc = VOS_NULL_PTR;
TL_SLEEP_NOTIFY_FUNC pWakeupFunc = VOS_NULL_PTR;
T_MODEM_SR_STAMP_STRU *g_modem_stamp = VOS_NULL_PTR;
SRAM_SOC_TLDSP_INTERACTION_STRU *g_SocTldspInteraction = VOS_NULL_PTR;

extern VOS_VOID RTTAGENT_EtSignalingInit(VOS_VOID);

/*****************************************************************************
 函 数 名  : TLSLEEP_GetSRDDRAddr
 功能描述  : 获取共享DDR中保存打点信息的地址
*****************************************************************************/
static VOS_INT32 TLSLEEP_GetSRDDRAddr(VOS_VOID)
{
    VOS_INT32 ret = 0;
    BSP_DDR_SECT_QUERY_S modem_sr_sect_query;
    BSP_DDR_SECT_INFO_S modem_sr_sect_info = {BSP_DDR_SECT_TYPE_MODEM_SR_STAMP,};

    modem_sr_sect_query.enSectType = BSP_DDR_SECT_TYPE_MODEM_SR_STAMP;
    ret = mdrv_get_fix_ddr_addr(&modem_sr_sect_query, &modem_sr_sect_info);
    if(ret)
        return (-1);

    g_modem_stamp = (T_MODEM_SR_STAMP_STRU *)((unsigned long)modem_sr_sect_info.pSectVirtAddr);

    return 0;
}

/*****************************************************************************
 函 数 名  : TLSLEEP_NotifyReg
 功能描述  : 为RCM提供的回调注册接口
*****************************************************************************/
VOS_VOID TLSLEEP_NotifyReg(TL_SLEEP_NOTIFY_FUNC pFuncSleep, TL_SLEEP_NOTIFY_FUNC pFuncWakeup)
{
    pSleepFunc = pFuncSleep;
    pWakeupFunc = pFuncWakeup;

    return ;
}


#ifdef OPEN_MSP_SLEEP
/*lint -e409 -e52 -e550 -e701 -e746*/
/*****************************************************************************
 函 数 名  : QueueInit/QueueIn/QueueLoopIn
 功能描述  : 队列操作,为可维可测使用
 输入参数  : void
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
static inline void QueueInit(drx_queue_t *Q, VOS_UINT32 elementNum)
{
    Q->maxNum = elementNum;
    Q->front = 0;
    Q->rear = 0;
    Q->num = 0;
}

static inline VOS_INT32 QueueIn(drx_queue_t *Q, VOS_UINT32 state)
{
    if (Q->num == Q->maxNum)
    {
        return -1;
    }

    Q->data[Q->rear].ulSlice = mdrv_timer_get_normal_timestamp();
    Q->data[Q->rear].ulState = state;

    Q->rear = (Q->rear+1) % Q->maxNum;
    Q->num++;

    return 0;
}

static inline VOS_INT32 QueueLoopIn(drx_queue_t *Q, VOS_UINT32 state)
{
    if (Q->num < Q->maxNum)
    {
        return QueueIn(Q, state);
    }
    else
    {
        Q->data[Q->rear].ulSlice = mdrv_timer_get_normal_timestamp();
        Q->data[Q->rear].ulState = state;

        Q->rear = (Q->rear+1) % Q->maxNum;
        Q->front = (Q->front+1) % Q->maxNum;
    }

    return 0;
}
/*****************************************************************************
 函 数 名  : TLSLEEP_StateRecord
 功能描述  : 记录正常流程中各个阶段的信息
 输入参数  : void
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOS_VOID TLSLEEP_StateRecord(DRX_STATE_SLICE state)
{
    if(VOS_NULL == g_msp_pwrctrl.DrxStateSlice)
    {
        return;
    }
    g_msp_pwrctrl.DrxStateSlice[state].ulCount++;
    g_msp_pwrctrl.DrxStateSlice[state].ulSlice = mdrv_timer_get_normal_timestamp();
}
/*lint +e52 +e550*/
static inline VOS_VOID TLSLEEP_DbgTimeRecord(unsigned int recored)
{
    if(VOS_NULL == g_msp_pwrctrl.time_queue_record)
    {
        return;
    }
    /*为方便做功耗测试在此加延时，由g_msp_delay.delay_control的每一个bit 标志是否进行延时*/
    if(g_msp_delay.delay_control&(1<<recored))
    {
        TLSLEEP_DelayMs(g_msp_delay.delay_ms, 1);
    }
    if(TLSLEEP_DSPHALTISR_0 == recored)
    {
        QueueLoopIn(g_msp_pwrctrl.time_queue_record,0x5a5a5a5a);
    }
    QueueLoopIn(g_msp_pwrctrl.time_queue_record, recored);
    g_msp_pwrctrl.dbg_time_record[recored] = mdrv_timer_get_normal_timestamp();
}
/*****************************************************************************
 函 数 名  : TLSLEEP_DelayMs
 功能描述  : 测试功耗的过程中需要加延时的地方可以用,单位ms
 输入参数  : void
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOS_VOID TLSLEEP_DelayMs(VOS_UINT delay_ms, VOS_UINT flag)
{
    VOS_UINT oldtime = 0;
    VOS_UINT newtime = 0;

    oldtime = mdrv_timer_get_normal_timestamp();
    newtime = mdrv_timer_get_normal_timestamp();
    if(1 == flag)
    {
        while((oldtime + delay_ms*32) >  newtime)
        {
            newtime = mdrv_timer_get_normal_timestamp();
        }
    }
}

VOS_VOID TLSLEEP_RunDsp(VOS_VOID)
{
    VOS_INT32 power_lock = 0;

    power_lock = VOS_SplIMP();
    /*需要在run dsp之前把wakeup和force_awake清掉，否则会概率出现写邮箱强制唤醒dsp的请求被丢弃，导致获取信号量超时异常*/
    clear_power_status_bit(MSP_PWR_WAKEUP);
    clear_power_status_bit( MSP_PWR_FORCE_AWAKE);
    set_power_status_bit(MSP_PWR_WAIT_RESUMER);
    VOS_Splx(power_lock);
    (void)mdrv_dsp_run_bbe();
}


/*****************************************************************************
 函 数 名  : TLSLEEP_PllEnable
 功能描述  : 根据NV项配置进行PLL的使能
 输入参数  : 无
 输出参数  : 无,
 返 回 值  :
*****************************************************************************/
VOS_VOID TLSLEEP_PllEnable(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule)
{
    VOS_INT32 i;
    VOS_UINT16 chan;
    VOS_UINT32 j;

    j = (VOS_UINT32)enCommMode-PWC_COMM_MODE_LTE;

    switch(enCommModule)
    {
        case PWC_COMM_MODULE_RF:
            chan = g_msp_pwrctrl.tlmode_channel[j].rf_clk_id;
            break;

        case PWC_COMM_MODULE_ABB:
            chan = g_msp_pwrctrl.tlmode_channel[j].abb_channel_id;
            break;

        default:
            mspsleep_print_error("check your input enCommMode:%d,  enCommModule: %d\n", enCommMode, enCommModule);
            return ;
    }

    for(i = 0; i < MSP_SLEEP_CHAN_NUM; i++)
    {
        if(chan & (VOS_UINT16)(0x1<<i))
        {
            mdrv_pm_enable_pllclk(enCommMode, enCommModule, PWC_COMM_MODEM_0, (PWC_COMM_CHANNEL_E)i);
        }
    }
}
/*****************************************************************************
 函 数 名  : TLSLEEP_PwrctrlUp
 功能描述  : 根据NV项配置进行上电
 输入参数  : 无
 输出参数  : 无,
 返 回 值  :
*****************************************************************************/
VOS_VOID TLSLEEP_PwrctrlUp(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule)
{
    VOS_INT32 i;
    VOS_UINT16 chan;
    VOS_UINT32 j;

    j = (VOS_UINT32)enCommMode-PWC_COMM_MODE_LTE;

    switch(enCommModule)
    {
#ifdef CONFIG_PASwitch_V7R5
        case PWC_COMM_MODULE_PA:
            chan = g_msp_pwrctrl.tlmode_channel[j].pa_switch_id;
            break;
#endif
        case PWC_COMM_MODULE_RF:
            chan = g_msp_pwrctrl.tlmode_channel[j].rf_channel_id;
            break;

        case PWC_COMM_MODULE_ABB:
            chan = g_msp_pwrctrl.tlmode_channel[j].abb_channel_id;
            break;

        default:
            mspsleep_print_error("check your input enCommMode:%d,  enCommModule: %d\n", enCommMode, enCommModule);
            return ;
    }

    for(i = 0; i < MSP_SLEEP_CHAN_NUM; i++)
    {
        if(chan & (VOS_UINT16)(0x1<<i))
        {
            mdrv_pm_pwrup(enCommMode, enCommModule,  PWC_COMM_MODEM_0, (PWC_COMM_CHANNEL_E)i);
        }
    }
}

/*****************************************************************************
 函 数 名  : TLSLEEP_PllDisable
 功能描述  : 根据NV项配置进行PLL的去使能
 输入参数  : 无
 输出参数  : 无,
 返 回 值  :
*****************************************************************************/
VOS_VOID TLSLEEP_PllDisable(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule)
{
    VOS_INT32 i;
    VOS_UINT16 chan;
    VOS_UINT32 j;

    j = (VOS_UINT32)enCommMode-PWC_COMM_MODE_LTE;

    switch(enCommModule)
    {
        case PWC_COMM_MODULE_RF:
            chan = g_msp_pwrctrl.tlmode_channel[j].rf_clk_id;
            break;

        case PWC_COMM_MODULE_ABB:
            chan = g_msp_pwrctrl.tlmode_channel[j].abb_channel_id;
            break;

        default:
            mspsleep_print_error("check your input enCommMode:%d,  enCommModule: %d\n", enCommMode, enCommModule);
            return ;
    }

    for(i = 0; i < MSP_SLEEP_CHAN_NUM; i++)
    {
        if(chan & (VOS_UINT16)(0x1<<i))
        {
            mdrv_pm_disable_pllclk(enCommMode, enCommModule,  PWC_COMM_MODEM_0, (PWC_COMM_CHANNEL_E)i);
        }
    }
}
/*****************************************************************************
 函 数 名  : TLSLEEP_PwrctrlDown
 功能描述  : 根据NV项配置进行下电
 输入参数  : 无
 输出参数  : 无,
 返 回 值  :
*****************************************************************************/
VOS_VOID TLSLEEP_PwrctrlDown(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule)
{
    VOS_INT32 i;
    VOS_UINT16 chan;
    VOS_UINT32 j;

    j = (VOS_UINT32)enCommMode-PWC_COMM_MODE_LTE;
    switch(enCommModule)
    {
#ifdef CONFIG_PASwitch_V7R5
        case PWC_COMM_MODULE_PA:
            chan = g_msp_pwrctrl.tlmode_channel[j].pa_switch_id;
            break;
#endif

        case PWC_COMM_MODULE_RF:
            chan = g_msp_pwrctrl.tlmode_channel[j].rf_channel_id;
            break;

        case PWC_COMM_MODULE_ABB:
            chan = g_msp_pwrctrl.tlmode_channel[j].abb_channel_id;
            break;

        default:
            mspsleep_print_error("check your input enCommMode:%d,  enCommModule: %d\n", enCommMode, enCommModule);
            return ;
    }

    for(i = 0; i < MSP_SLEEP_CHAN_NUM; i++)
    {
        if(chan & (VOS_UINT16)(0x1<<i))
        {
            mdrv_pm_pwrdown(enCommMode, enCommModule,  PWC_COMM_MODEM_0, (PWC_COMM_CHANNEL_E)i);
        }
    }
}

/*****************************************************************************
 函 数 名  : LSLEEP_RttForceAwake
 功能描述  : 强制唤醒接口，会释放sleep任务信号量
 输入参数  : void
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOS_VOID TLSLEEP_RttForceAwake(VOS_VOID)
{
    VOS_INT power_lock = 0;

    mspsleep_print_info("force awake");

    power_lock = VOS_SplIMP();

    TLSLEEP_StateRecord(DRX_FORCE_AWAKE_API);

    if((read_power_status_bit(MSP_PWR_FORCE_AWAKE))||(read_power_status_bit(MSP_PWR_WAKEUP))
        ||(read_power_status_bit(MSP_PWR_WAIT_RESUMER)))
    {
        VOS_Splx(power_lock);
        TLSLEEP_StateRecord(DRX_FORCE_AWAKE_NOT_DEAL);
        return;
    }
    else if(read_power_status_bit(MSP_PWR_SYSTEM_RUN))
    {
        VOS_Splx(power_lock);
        BSP_MailBox_DspAwakeProc(EN_MAILBOX_CALLBACK_DSP_RESUME);
        TLSLEEP_StateRecord(DRX_FORCE_AWAKE_RUN_RETURN);
        return;
    }

    set_power_status_bit(MSP_PWR_FORCE_AWAKE);
    VOS_Splx(power_lock);
    VOS_SmV(g_msp_pwrctrl.task_sem);
    return;
}
/*****************************************************************************
 函 数 名  : TLSLEEP_TCXOIsrProc
 功能描述  : 打开TCXO时注册的回调函数
 输入参数  : 无
 输出参数  : 无,
 返 回 值  :
*****************************************************************************/
VOS_VOID TLSLEEP_TCXO0_IsrProc( VOS_VOID )
{
    VOS_SmV(g_msp_pwrctrl.SleepTcxoSem[0]);
}
VOS_VOID TLSLEEP_TCXO1_IsrProc( VOS_VOID )
{
    VOS_SmV(g_msp_pwrctrl.SleepTcxoSem[1]);
}

/*****************************************************************************
 函 数 名  : TLSLEEP_OpenTCXO
 功能描述  : 打开TCXO
 输入参数  : 无
 输出参数  : 无,
 返 回 值  : 无
*****************************************************************************/
VOS_VOID TLSLEEP_OpenTCXO(VOS_VOID )
{
    PWC_COMM_MODEM_E                    enModem = PWC_COMM_MODEM_0;
    VOS_UINT32                          ulTcxoTime = 0;
    VOS_UINT32                          ulTcxoResult = VOS_OK;
    VOS_INT                             ulTcxoStatus[2] = {0};
    VOS_INT                             power_lock = 0;

    TLSLEEP_DbgTimeRecord(TLSLEEP_OPENTCXO_0);

    if(g_msp_pwrctrl.tlmode_channel[0].tcxo_id == 0x3)
    {
        power_lock = VOS_SplIMP();
        ulTcxoStatus[0] = mdrv_pm_get_tcxo_status(PWC_COMM_MODEM_0);
        ulTcxoStatus[1] = mdrv_pm_get_tcxo_status(PWC_COMM_MODEM_1);

		mdrv_pm_enable_tcxo(PWC_COMM_MODEM_0, (PWC_COMM_MODE_E)PWC_COMM_MODE_LTE);
        mdrv_pm_enable_tcxo(PWC_COMM_MODEM_1, (PWC_COMM_MODE_E)PWC_COMM_MODE_LTE);

        TLSLEEP_DbgTimeRecord(TLSLEEP_OPENTCXO_1);

        if ((PWRCTRL_COMM_OFF == ulTcxoStatus[0])||(PWRCTRL_COMM_OFF == ulTcxoStatus[1]))
        {
            ulTcxoTime  = g_msp_pwrctrl.SleepDrxResumeTime.ulTcxoRsmTime/1000;

            /* 启动TCXO稳定等待定时器 */
            mdrv_pm_start_tcxo_timer(PWC_COMM_MODEM_0, (PWC_COMM_MODE_E)PWC_COMM_MODE_LTE, (PWC_TCXO_FUNCPTR)TLSLEEP_TCXO0_IsrProc, VOS_NULL, ulTcxoTime);
            mdrv_pm_start_tcxo_timer(PWC_COMM_MODEM_1, (PWC_COMM_MODE_E)PWC_COMM_MODE_LTE, (PWC_TCXO_FUNCPTR)TLSLEEP_TCXO1_IsrProc, VOS_NULL, ulTcxoTime);
            VOS_Splx(power_lock);
            /* coverity[lock] */
            ulTcxoResult    = VOS_SmP(g_msp_pwrctrl.SleepTcxoSem[0], WAIT_FOR_EVER);
            /* coverity[lock] */
            ulTcxoResult    |= VOS_SmP(g_msp_pwrctrl.SleepTcxoSem[1], WAIT_FOR_EVER);

            TLSLEEP_DbgTimeRecord(TLSLEEP_OPENTCXO_2);
            if (VOS_OK != ulTcxoResult)
            {
                /* 异常处理流程 */
                TLSLEEP_StateRecord(DRX_FAIL_WAIT_TCXO_SEM);
                mspsleep_print_error("tcxo get sem fail");
            }
        }
        else
        {
            VOS_Splx(power_lock);
        }

        TLSLEEP_DbgTimeRecord(TLSLEEP_OPENTCXO_3);
        mdrv_pm_enable_tcxo_rfclk(PWC_COMM_MODEM_0, PWC_COMM_MODE_LTE, PWC_COMM_CHANNEL_0);
        mdrv_pm_enable_tcxo_rfclk(PWC_COMM_MODEM_1, PWC_COMM_MODE_LTE, PWC_COMM_CHANNEL_0);
        TLSLEEP_DbgTimeRecord(TLSLEEP_OPENTCXO_MAX);
    }
    else if(g_msp_pwrctrl.tlmode_channel[0].tcxo_id != 0)
    {
        enModem = (PWC_COMM_MODEM_E)g_msp_pwrctrl.tlmode_channel[0].tcxo_id;
        power_lock = VOS_SplIMP();
        mdrv_pm_enable_tcxo((PWC_COMM_MODEM_E)enModem, (PWC_COMM_MODE_E)PWC_COMM_MODE_LTE);
        TLSLEEP_DbgTimeRecord(TLSLEEP_OPENTCXO_1);
        if (PWRCTRL_COMM_OFF == mdrv_pm_get_tcxo_status((PWC_COMM_MODEM_E)enModem))
        {
            ulTcxoTime  = g_msp_pwrctrl.SleepDrxResumeTime.ulTcxoRsmTime/1000;

            /* 启动TCXO稳定等待定时器 */
            mdrv_pm_start_tcxo_timer(enModem, (PWC_COMM_MODE_E)PWC_COMM_MODE_LTE, (PWC_TCXO_FUNCPTR)TLSLEEP_TCXO0_IsrProc, VOS_NULL, ulTcxoTime);
            VOS_Splx(power_lock);

            /* 等待TCXO稳定,Take信号量最小时间长度必须为1 tick */
            ulTcxoResult = VOS_SmP(g_msp_pwrctrl.SleepTcxoSem[0], WAIT_FOR_EVER);

            TLSLEEP_DbgTimeRecord(TLSLEEP_OPENTCXO_2);
            if (VOS_OK != ulTcxoResult)
            {
                /* 异常处理流程 */
                TLSLEEP_StateRecord(DRX_FAIL_WAIT_TCXO_SEM);
                mspsleep_print_error("tcxo get sem fail");
            }
        }
        else
        {
            VOS_Splx(power_lock);
        }

        TLSLEEP_DbgTimeRecord(TLSLEEP_OPENTCXO_3);
        mdrv_pm_enable_tcxo_rfclk(enModem, PWC_COMM_MODE_LTE, PWC_COMM_CHANNEL_0);
        TLSLEEP_DbgTimeRecord(TLSLEEP_OPENTCXO_MAX);
    }
    else
    {
        /* 单DCXO方案不用控制 */
    }
    /* coverity[missing_unlock] */
}
/*****************************************************************************
 函 数 名  : TLSLEEP_CloseTCXO
 功能描述  : 关闭TCXO
 输入参数  : 无
 输出参数  : 无,
 返 回 值  : 无
*****************************************************************************/
VOS_VOID TLSLEEP_CloseTCXO(VOS_VOID )
{
    VOS_INT32 i;
    VOS_UINT16 chan;

    /* 默认使用LTE的参数 */
    chan = g_msp_pwrctrl.tlmode_channel[0].tcxo_id;

    for(i = 0; i < MSP_SLEEP_TCXO_NUM; i++)
    {
        if(chan & (VOS_UINT16)(0x1<<i))
        {
            mdrv_pm_disable_tcxo_rfclk((PWC_COMM_MODEM_E)i, PWC_COMM_MODE_LTE, PWC_COMM_CHANNEL_0);
            mdrv_pm_disable_tcxo((PWC_COMM_MODEM_E)i, PWC_COMM_MODE_LTE);
        }
    }
}


#if (FEATURE_MULTI_CHANNEL == FEATURE_ON)

VOS_VOID TLSLEEP_EnableRFTCXO(VOS_VOID )
{
    VOS_INT32 i;
    VOS_UINT16 chan;

    TLSLEEP_DbgTimeRecord(TLSLEEP_OPENTCXO_0);

    /* 默认使用LTE的参数 */
    chan = g_msp_pwrctrl.tlmode_channel[0].tcxo_id;

    for(i = 0; i < MSP_SLEEP_TCXO_NUM; i++)
    {
        if(chan & (VOS_UINT16)(0x1<<i))
        {
            mdrv_pm_enable_tcxo_rfclk((PWC_COMM_MODEM_E)i, PWC_COMM_MODE_LTE, PWC_COMM_CHANNEL_0);
        }
    }

    TLSLEEP_DbgTimeRecord(TLSLEEP_OPENTCXO_MAX);
}

VOS_VOID TLSLEEP_DisableRFTCXO(VOS_VOID )
{
    VOS_INT32 i;
    VOS_UINT16 chan;

    /* 默认使用LTE的参数 */
    chan = g_msp_pwrctrl.tlmode_channel[0].tcxo_id;

    for(i = 0; i < MSP_SLEEP_TCXO_NUM; i++)
    {
        if(chan & (VOS_UINT16)(0x1<<i))
        {
            mdrv_pm_disable_tcxo_rfclk((PWC_COMM_MODEM_E)i, PWC_COMM_MODE_LTE, PWC_COMM_CHANNEL_0);
        }
    }
}

/*****************************************************************************
 函 数 名  : TLSLEEP_HwPowerUp
 功能描述  : 为RTT相关器件上电
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ERR_MSP_SUCCESS 成功
*****************************************************************************/
VOS_INT32 TLSLEEP_HwPowerUp(PWC_COMM_MODE_E modeId)
{
    PWC_COMM_MODEM_E                enModem = PWC_COMM_MODEM_0;
    PWC_COMM_CHANNEL_E              enChannel = PWC_COMM_CHANNEL_0;
    VOS_INT32                       ret = 0;
    VOS_INT                         power_lock = 0;

    TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_0);
    TLSLEEP_DelayMs(5, g_msp_drx_delay.msp_0);

    /* DDR和总线频率不需要调，只需要调CCPU频率 */
    ret = TLSLEEP_DfsQosUpdate((VOS_INT32)DFS_QOS_ID_CCPU_MINFREQ_E, dfs_ccpu_req_id,TLSLEEP_DFS_CCPU_600M);
    if(ret)
    {
        power_lock = VOS_SplIMP();/* [false alarm]:屏蔽Fortify */
        set_power_status_bit(MSP_DFS_RUN_UPDATE_FAIL);
        VOS_Splx(power_lock);
    }

    TLSLEEP_DelayMs(5, g_msp_drx_delay.msp_1);
    if(POWER_SAVING_DEEP_SLEEP == g_msp_pwrctrl.dsp_sleep_flag)
    {
        /* V8R1中使用单DCXO，不需要MSP控制TCXO，由底软屏蔽，MSP保持代码的归一 */
        (void)mdrv_pm_pwrup(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBE16, enModem, enChannel);

        /* 先1后2表示深睡流程 */
        TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_1);
        (void)mdrv_pm_enable_pllclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBE16, enModem, enChannel);
        (void)mdrv_pm_enable_pllclk(PWC_COMM_MODE_TDS, PWC_COMM_MODULE_BBE16, enModem, enChannel);
        TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_2);
        if(mdrv_dsp_restore_bbe())
        {
            TLSLEEP_StateRecord(RESTORE_DSP_TCM_FAIL);
            mspsleep_print_error("DSP TCM restore fail");
        }
    }
    else if(POWER_SAVING_SNOOZE == g_msp_pwrctrl.dsp_sleep_flag)
    {
        /* 先2后1表示浅睡流程 */
        TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_2);
        (void)mdrv_dsp_enable_clk();
        TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_1);
        (void)mdrv_dsp_unreset_bbe();
    }
    TLSLEEP_DelayMs(5, g_msp_drx_delay.msp_2);
    /* ABB PLL使能前先上电 */
    TLSLEEP_PwrctrlUp(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_ABB);

    TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_3);

    /* BBP上电给钟前要先使能PLL(PLL处于BBP前端) */
    TLSLEEP_PllEnable(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_ABB);

    TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_4);

    /* V8R1 BBP与ABB共用PLL，此接口在底软中打桩 */
    mdrv_pm_enable_pllclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBP_DRX, enModem, enChannel);

    TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_5);

    /* TDS BBP时钟使能，LTE BBP时钟使能由DSP控制 */
    mdrv_pm_enable_bbpclk(PWC_COMM_MODE_TDS, PWC_COMM_MODULE_BBP_DRX, enModem, enChannel);
    TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_6);

    /* LTE涉及多个时钟源，DSP只控制一部分，需要MSP调用底软接口打开LTE相关所有时钟 */
    mdrv_pm_enable_bbpclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBP_DRX, enModem, enChannel);

    /* TDS BBP上电，LTE BBP上电由DSP控制 */
    (void)mdrv_pm_pwrup(PWC_COMM_MODE_TDS, PWC_COMM_MODULE_BBP_DRX, enModem, enChannel);

    TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_7);
    TLSLEEP_DelayMs(5, g_msp_drx_delay.msp_3);
    /*RF上电*/
    TLSLEEP_PwrctrlUp(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_RF);

    TLSLEEP_EnableRFTCXO();

    TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_8);

    if(g_SocTldspInteraction)
    {
        g_SocTldspInteraction->PstRttSleepInfo.ulRfTime = mdrv_timer_get_normal_timestamp();
    }
    VOS_FlushCpuWriteBuf();
    TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_9);
    if(POWER_SAVING_DEEP_SLEEP == g_msp_pwrctrl.dsp_sleep_flag)
    {
        (void)mdrv_dsp_get_br_status();
    }

    BSP_MailBox_DspAwakeProc(EN_MAILBOX_CALLBACK_DSP_RUN);
    TLSLEEP_DelayMs(5, g_msp_drx_delay.msp_4);
    TLSLEEP_RunDsp();
    TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_MAX);

    return ERR_MSP_SUCCESS;
}

/*****************************************************************************
 函 数 名  : TLSLEEP_HwPowerDown
 功能描述  : 为RTT相关器件下电
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ERR_MSP_SUCCESS 成功
*****************************************************************************/
VOS_INT32 TLSLEEP_HwPowerDown(PWC_COMM_MODE_E modeId)
{
    PWC_COMM_MODEM_E                enModem = PWC_COMM_MODEM_0;
    PWC_COMM_CHANNEL_E              enChannel = PWC_COMM_CHANNEL_0;
    VOS_INT32                       ret = 0;
    VOS_INT32                       flag = 0;

    enModem = PWC_COMM_MODEM_0;

    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_0);
    mdrv_dsp_stop_bbe();
    /* DDR和总线频率不需要调，只需要调CCPU频率 */
    ret = TLSLEEP_DfsQosUpdate((VOS_INT32)DFS_QOS_ID_CCPU_MINFREQ_E, dfs_ccpu_req_id, TLSLEEP_DFS_CCPU_150M);
    if(ret)
    {
        flag = VOS_SplIMP();
        set_power_status_bit(MSP_DFS_HALT_UPDATE_FAIL);
        VOS_Splx(flag);
    }

    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_1);

    if(POWER_SAVING_DEEP_SLEEP == g_msp_pwrctrl.dsp_sleep_flag)
    {
        /*必须在DSP上电的时候才能进行保存，否则是不可以走这个流程的*/
        if (mdrv_dsp_backup_bbe())
        {
           TLSLEEP_StateRecord(STORE_DSP_TCM_FAIL);
           mspsleep_print_error("DSP TCM store fail");
        }
    }
    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_2);
    /*RF下电*/
    TLSLEEP_DisableRFTCXO();
    TLSLEEP_PwrctrlDown(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_RF);

    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_3);

    /* TDS BBP下电，LTE BBP下电由DSP控制 */
    mdrv_pm_pwrdown(PWC_COMM_MODE_TDS, PWC_COMM_MODULE_BBP_DRX, enModem, enChannel);
    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_4);

    /* TDS BBP时钟去使能，LTE BBP时钟去使能由DSP控制 */
    mdrv_pm_disable_bbpclk(PWC_COMM_MODE_TDS, PWC_COMM_MODULE_BBP_DRX, enModem, enChannel);
    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_5);

    /* LTE涉及多个时钟源，DSP只控制一部分，需要MSP调用底软接口打开LTE相关所有时钟 */
    (void)mdrv_pm_disable_bbpclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBP_DRX, enModem, enChannel);

    /* BBP PLL关闭(V8R1中但DCXO，BBP的PLL使用ABB中的PLL，此接口底软打桩) */
    (void)mdrv_pm_disable_pllclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBP_DRX, enModem, enChannel);

    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_6);

    /* ABB PLL去使能 */
    TLSLEEP_PllDisable(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_ABB);

    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_7);

    /* ABB PLL下电 */
    TLSLEEP_PwrctrlDown(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_ABB);

    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_8);

    if(POWER_SAVING_DEEP_SLEEP == g_msp_pwrctrl.dsp_sleep_flag)
    {
        TLSLEEP_StateRecord(DSP_DEEP_SLEEP_COUNT);
        (void)mdrv_dsp_get_br_status();
        TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_9);
        mdrv_pm_disable_pllclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBE16, enModem, enChannel);
        mdrv_pm_disable_pllclk(PWC_COMM_MODE_TDS, PWC_COMM_MODULE_BBE16, enModem, enChannel);
        mdrv_pm_pwrdown(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBE16, enModem, enChannel);

        /* V8R1中使用单DCXO，不需要MSP控制TCXO，由底软屏蔽，MSP保持代码的归一 */
    }
    else if(POWER_SAVING_SNOOZE == g_msp_pwrctrl.dsp_sleep_flag)
    {
        TLSLEEP_StateRecord(DSP_LIGHT_SLEEP_COUNT);
        (void)mdrv_dsp_reset_bbe();
        /*BBE16 关钟*/
        (void)mdrv_dsp_disable_clk();
    }
    else
    {
        TLSLEEP_StateRecord(DSP_SLEEP_FLAG_ERROR);
    }
    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_MAX);

    return ERR_MSP_SUCCESS;
}

#else

/*****************************************************************************
 函 数 名  : TLSLEEP_CheckWakeTime
 功能描述  : 检测当前唤醒DSP是否超时,如果超时进行错误处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
*****************************************************************************/
static inline VOS_VOID TLSLEEP_CheckWakeTime()
{
    VOS_UINT32 sleep_time = *(VOS_UINT32*)(HI_BBP_LTEDRX_BASE_ADDR + HI_BBP_LTEDRX_SLP_TIME_CUR_OFFSET);
    VOS_UINT32 wake_time = *(VOS_UINT32*)(HI_BBP_LTEDRX_BASE_ADDR + HI_BBP_LTEDRX_WAKEUP_32K_CNT_OFFSET);
    VOS_UINT32 clk_time = *(VOS_UINT32*)(HI_BBP_LTEDRX_BASE_ADDR + HI_BBP_LTEDRX_SWITCH_32K_CNT_OFFSET);
    VOS_UINT32 i = 0;
    /*如果为主模,而且唤醒超时就进行记录*/
    if(((sleep_time + g_msp_pwrctrl.exc_overtime.timeOut) > (wake_time + clk_time))&&(clk_time > 163)\
        &&(0 == g_msp_pwrctrl.exc_overtime.ulReadMark))
    {
        for(i = TLSLEEP_DSPHALTISR_0; i < TLSLEEP_TIME_RECORD_MAX; i++)
        {
            g_msp_pwrctrl.exc_overtime.ulTime[i] = g_msp_pwrctrl.dbg_time_record[i];
        }
        g_msp_pwrctrl.exc_overtime.ulReadMark = 1;
        VOS_SmV(g_msp_pwrctrl.exc_overtime.time_sem);
    }
    return;
}

VOS_VOID TLSLEEP_DebugRecordTime(VOS_VOID)
{
    int i = 0;
    VOS_UINT32* axi_time = &g_msp_pwrctrl.dbg_time_record[TLSLEEP_AWAKEISR_0];
    VOS_UINT32* ddr_time = 0;

    if(0 == g_ulAddrShrDdr)
    {
        return;
    }

    ddr_time = (VOS_UINT32*)(g_ulAddrShrDdr + 0x200);

    TLSLEEP_CheckWakeTime();

    if((*(VOS_UINT32*)(g_ulAddrShrDdr + 4)) == 1)
    {
        *(VOS_UINT32*)(g_ulAddrShrDdr + 4) = 2;
        *(VOS_UINT32*)(g_ulAddrShrDdr + 8) = 1;
    }
    else
    {
        return;
    }

    /*0x5A5A5A5A~0x5B5B5B5B,为上电过程中的点*/
    *(ddr_time++) = 0x5A5A5A5A;
    for(i = TLSLEEP_AWAKEISR_0; i <= TLSEEP_HWPOWERUP_9; i++)
    {
        *(ddr_time++) = *(axi_time++);
    }
    /*0x5B5B5B5B~0x5C5C5C5C,为下电过程中的点*/
    *(ddr_time++) = 0x5B5B5B5B;
    axi_time =  &g_msp_pwrctrl.dbg_time_record[TLSLEEP_DSPHALTISR_0];
    for(i = TLSLEEP_DSPHALTISR_0; i <= TLSLEEP_RTTSLEEP_INNER_MAX; i++)
    {
        *(ddr_time++) = *(axi_time++);
    }
    *(ddr_time++) = 0x5C5C5C5C;
}

VOS_VOID TLSLEEP_PWRCTRL_PWRUP(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule, PWC_COMM_MODEM_E enModemId)
{
    (void)mdrv_pm_pwrup(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBE16, PWC_COMM_MODEM_0, PWC_COMM_CHANNEL_0);
    mdrv_dsp_enable_clk();
    mdrv_dsp_reset_bbe();
    mdrv_dsp_unreset_bbe();
}

VOS_VOID TLSLEEP_PWRCTRL_PWRDOWN(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule, PWC_COMM_MODEM_E enModemId)
{
    mdrv_dsp_disable_clk();
    (void)mdrv_pm_pwrdown(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBE16, PWC_COMM_MODEM_0, PWC_COMM_CHANNEL_0);
}

/*****************************************************************************
 函 数 名  : TLSLEEP_HwPowerUp
 功能描述  : 为RTT相关器件上电
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ERR_MSP_SUCCESS 成功
*****************************************************************************/
VOS_INT32 TLSLEEP_HwPowerUp(PWC_COMM_MODE_E modeId)
{
    PWC_COMM_MODEM_E       			enModem = PWC_COMM_MODEM_0;
#ifdef CONFIG_DFS_DDR
    VOS_INT32                       ret = 0;
    VOS_INT                         power_lock = 0;
#endif
    VOS_UINT32                          timestamp_begin = 0;
    VOS_UINT32                          timestamp_end = 0;
    TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_0);
    TLSLEEP_DelayMs(5, g_msp_drx_delay.msp_0);

    TLSLEEP_DelayMs(5, g_msp_drx_delay.msp_1);

    /* RF开钟上电 */
    mdrv_pm_pwrup(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_FEM, enModem, PWC_COMM_CHANNEL_0);
    /*RF电源上电要先于RFPLLenable，并且要间隔200us*/
    TLSLEEP_PwrctrlUp(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_RF);
	timestamp_begin = mdrv_timer_get_normal_timestamp();
    if(POWER_SAVING_DEEP_SLEEP == g_msp_pwrctrl.dsp_sleep_flag)
    {
#ifdef CONFIG_DFS_DDR
        ret += TLSLEEP_DfsQosUpdate((VOS_INT32)DFS_QOS_ID_DDR_MINFREQ_E, dfs_ddr_req_id, TLSLEEP_DFS_DDR_240M);/* [false alarm]:屏蔽Fortify */
        if(ret)
        {
            power_lock = VOS_SplIMP();/* [false alarm]:屏蔽Fortify */
            set_power_status_bit(MSP_DFS_RUN_UPDATE_FAIL);
            VOS_Splx(power_lock);
        }
#endif
    	TLSLEEP_OpenTCXO();
        /* 先1后2表示深睡流程 */
        TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_1);
        mdrv_pm_enable_pllclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBE16, enModem, PWC_COMM_CHANNEL_0);
        TLSLEEP_PWRCTRL_PWRUP(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBE16, enModem);
        TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_2);
        TLSLEEP_SAVE_SR_STAMP(TLSLEEP_SR_POWERUP_2);
        if(mdrv_dsp_restore_bbe())
        {
            TLSLEEP_StateRecord(RESTORE_DSP_TCM_FAIL);
            mspsleep_print_error("DSP TCM restore fail");
        }
    }
    else if(POWER_SAVING_SNOOZE == g_msp_pwrctrl.dsp_sleep_flag)
    {
#ifdef CONFIG_DFS_DDR
        ret += TLSLEEP_DfsQosUpdate((VOS_INT32)DFS_QOS_ID_DDR_MINFREQ_E, dfs_ddr_req_id, TLSLEEP_DFS_DDR_120M);/* [false alarm]:屏蔽Fortify */
        if(ret)
        {
            power_lock = VOS_SplIMP();/* [false alarm]:屏蔽Fortify */
            set_power_status_bit(MSP_DFS_RUN_UPDATE_FAIL);
            VOS_Splx(power_lock);
        }
#endif
        /* V7R5/Austin新需求，DSP上下电过程中执行PLL切换(由DSP模块实现) */
        mdrv_pm_enable_pllclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBE16, enModem, PWC_COMM_CHANNEL_0);
        mdrv_dsp_enable_clk();
        /* 先2后1表示浅睡流程 */
        TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_2);
        /*V7R2优化功耗,复位解复位放在一起*/
        mdrv_dsp_reset_bbe();
        mdrv_dsp_unreset_bbe();
        TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_1);
    }
    TLSLEEP_DelayMs(5, g_msp_drx_delay.msp_2);
    TLSLEEP_PwrctrlUp(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_ABB);
    TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_3);
    /*BBP上电*/
    mdrv_pm_pwrup(PWC_COMM_MODE_TDS, PWC_COMM_MODULE_BBP_DRX, enModem, PWC_COMM_CHANNEL_0);
    mdrv_pm_pwrup(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBP_DRX, enModem, PWC_COMM_CHANNEL_0);
    TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_4);
    /*打开TDS 使用的BBP 1A分区时钟*/
    mdrv_pm_enable_bbpclk(PWC_COMM_MODE_TDS, PWC_COMM_MODULE_BBP_DRX, enModem, PWC_COMM_CHANNEL_0);
    mdrv_pm_enable_bbpclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBP_DRX, enModem, PWC_COMM_CHANNEL_0);
    TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_5);
    mdrv_pm_enable_pllclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBP_DRX, enModem, PWC_COMM_CHANNEL_0);
    TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_6);
    /*通过NV控制关闭哪个通道*/
    TLSLEEP_PllEnable(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_ABB);
    TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_7);
    TLSLEEP_DelayMs(5, g_msp_drx_delay.msp_3);

    if(g_SocTldspInteraction)
    {
        g_SocTldspInteraction->PstRttSleepInfo.ulRfTime = mdrv_timer_get_normal_timestamp();
    }
    VOS_FlushCpuWriteBuf();
    TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_8);
    if(POWER_SAVING_DEEP_SLEEP == g_msp_pwrctrl.dsp_sleep_flag)
    {
        mdrv_dsp_get_br_status();
        TLSLEEP_SAVE_SR_STAMP(TLSLEEP_SR_POWERUP_3);
        TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_9);
    }
    TLSLEEP_DebugRecordTime();
    BSP_MailBox_DspAwakeProc(EN_MAILBOX_CALLBACK_DSP_RUN);
    TLSLEEP_DelayMs(5, g_msp_drx_delay.msp_4);
	mdrv_rffe_cfg_on_power_up(PWC_COMM_MODE_LTE, enModem, PWC_COMM_CHANNEL_0);
    /*RF电源上电要先于RFPLLenable，并且要间隔200us*/
    do
    {
        timestamp_end = mdrv_timer_get_normal_timestamp();
    }while((msp_get_timer_slice_delta(timestamp_begin, timestamp_end)) < 7);
    TLSLEEP_PllEnable(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_RF);

#ifdef CONFIG_PASwitch_V7R5
    /*  PA 只针对V7R5，规避总线挂死bug  */
    TLSLEEP_PwrctrlUp(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_PA);
    TLSLEEP_PwrctrlUp(PWC_COMM_MODE_TDS, PWC_COMM_MODULE_PA);
#endif
    if(POWER_SAVING_DEEP_SLEEP == g_msp_pwrctrl.dsp_sleep_flag)
    {
        /*全系统初始化上电进行ET初始化*/
        RTTAGENT_EtSignalingInit();
    }
    TLSLEEP_RunDsp();
    TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_MAX);
    TLSLEEP_SAVE_SR_STAMP(TLSLEEP_SR_POWERUP_4);

    return ERR_MSP_SUCCESS;
}
/*****************************************************************************
 函 数 名  : TLSLEEP_HwPowerDown
 功能描述  : 为RTT相关器件下电
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ERR_MSP_SUCCESS 成功
*****************************************************************************/
VOS_INT32 TLSLEEP_HwPowerDown(PWC_COMM_MODE_E modeId)
{
    PWC_COMM_MODEM_E       			enModem = PWC_COMM_MODEM_0;
#ifdef CONFIG_DFS_DDR
    VOS_INT32                       ret = 0;
#endif
	enModem = PWC_COMM_MODEM_0;

    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_0);

#ifdef CONFIG_PASwitch_V7R5
    /*  PA 只针对V7R5，规避总线挂死bug  */
    TLSLEEP_PwrctrlDown(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_PA);
    TLSLEEP_PwrctrlDown(PWC_COMM_MODE_TDS, PWC_COMM_MODULE_PA);
#endif
    mdrv_dsp_stop_bbe();
    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_1);
    TLSLEEP_SAVE_SR_STAMP(TLSLEEP_SR_POWERDOWN_2);
    if(POWER_SAVING_DEEP_SLEEP == g_msp_pwrctrl.dsp_sleep_flag)
    {
        /*必须在DSP上电的时候才能进行保存，否则是不可以走这个流程的*/
        if (mdrv_dsp_backup_bbe())
        {
           TLSLEEP_StateRecord(STORE_DSP_TCM_FAIL);
           mspsleep_print_error("DSP TCM store fail");
        }
    }
    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_2);
    /* RF下电关钟 */
    TLSLEEP_PwrctrlDown(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_RF);
    mdrv_pm_pwrdown(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_FEM, enModem, PWC_COMM_CHANNEL_0);
    TLSLEEP_PllDisable(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_RF);
	mdrv_rffe_cfg_on_power_down(PWC_COMM_MODE_LTE, enModem, PWC_COMM_CHANNEL_0);

    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_3);
    TLSLEEP_PllDisable(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_ABB);
    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_4);
    /*BBP时钟关闭*/
    mdrv_pm_disable_pllclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBP_DRX, enModem, PWC_COMM_CHANNEL_0);
    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_5);
    /*关闭TDS 使用的BBP 1A分区时钟*/
    mdrv_pm_disable_bbpclk(PWC_COMM_MODE_TDS, PWC_COMM_MODULE_BBP_DRX, enModem, PWC_COMM_CHANNEL_0);
    mdrv_pm_disable_bbpclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBP_DRX, enModem, PWC_COMM_CHANNEL_0);
    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_6);
    /*BBP下电*/
    mdrv_pm_pwrdown(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBP_DRX, enModem, PWC_COMM_CHANNEL_0);
    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_7);
    mdrv_pm_pwrdown(PWC_COMM_MODE_TDS, PWC_COMM_MODULE_BBP_DRX, enModem, PWC_COMM_CHANNEL_0);
    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_8);
    TLSLEEP_PwrctrlDown(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_ABB);
    if(POWER_SAVING_DEEP_SLEEP == g_msp_pwrctrl.dsp_sleep_flag)
    {
        TLSLEEP_StateRecord(DSP_DEEP_SLEEP_COUNT);
        mdrv_dsp_get_br_status();
        TLSLEEP_SAVE_SR_STAMP(TLSLEEP_SR_POWERDOWN_3);
        TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_9);
        TLSLEEP_PWRCTRL_PWRDOWN(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBE16, enModem);
        mdrv_pm_disable_pllclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBE16, enModem, PWC_COMM_CHANNEL_0);
        TLSLEEP_CloseTCXO();
    }
    else if(POWER_SAVING_SNOOZE == g_msp_pwrctrl.dsp_sleep_flag)
    {
        TLSLEEP_StateRecord(DSP_LIGHT_SLEEP_COUNT);
        /*BBE16 关钟*/
        mdrv_dsp_disable_clk();
        /* V7R5/Austin新需求，DSP上下电过程中执行PLL切换(由DSP模块实现) */
        mdrv_pm_disable_pllclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBE16, enModem, PWC_COMM_CHANNEL_0);
    }
    else
    {
        TLSLEEP_StateRecord(DSP_SLEEP_FLAG_ERROR);
    }

#ifdef CONFIG_DFS_DDR
    ret = TLSLEEP_DfsQosUpdate((VOS_INT32)DFS_QOS_ID_DDR_MINFREQ_E, dfs_ddr_req_id, 0);
    if(ret)
    {
        mspsleep_print_error("MSP vote TLSLEEP_DFS_DDR_0M failed!\n");
    }
#endif

    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_MAX);
    TLSLEEP_SAVE_SR_STAMP(TLSLEEP_SR_POWERDOWN_4);

    return ERR_MSP_SUCCESS;
}

#endif
/*****************************************************************************
 函 数 名  : TLSLEEP_IsSlaveSleep
 功能描述  : 查询TLdsp低功耗状态。给uphy_init调用，在初始化时用于判断当前TL是否
             进入从模低功耗状态。只有返回true，uphy_init才会继续对X模进行初始化
             如果返回false，uphy_init会定时再次查询。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 1:已经进入低功耗状态
             0:未进入低功耗状态
*****************************************************************************/
int TLSLEEP_IsSlaveSleep(void)
{       
    if(g_msp_pwrctrl.DspLowPowerFlag != MSP_TLPHY_IN_LOW_POWER)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/*****************************************************************************
 函 数 名  : TLSLEEP_RttForceAwake_Inner
 功能描述  : 唤醒过程
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOS_INT32 TLSLEEP_RttForceAwake_Inner(VOS_VOID)
{
    /* 按DSP/RCM要求，唤醒前回调RCM */
    if(pWakeupFunc)
    {
        TLSLEEP_DbgTimeRecord(TLSLEEP_AWAKE_CB_0);
        pWakeupFunc();
        TLSLEEP_DbgTimeRecord(TLSLEEP_AWAKE_CB_1);
    }

    /*投票不能进入睡眠*/
    mdrv_pm_wake_lock(PWRCTRL_SLEEP_TLPS);
    if(0 != ((g_msp_delay.delay_control)&DELAY_CTRL_BEFOR_WAKE))
    {
        TLSLEEP_DelayMs(g_msp_delay.delay_ms, 1);
    }
    mspsleep_print_info("start wake");
    TLSLEEP_DbgTimeRecord(TLSLEEP_FORCE_AWAKE_INNER_0);
    TLSLEEP_SAVE_SR_STAMP(TLSLEEP_SR_POWERUP_1);

    if(TLSLEEP_HwPowerUp((PWC_COMM_MODE_E)PWC_COMM_MODE_LTE))
    {
        mspsleep_print_error("sleep power up failed!");
        return MSP_SLEEP_ERROR;
    }
    if(0 != ((g_msp_delay.delay_control)&DELAY_CTRL_AFTER_SLEEP))
    {
        TLSLEEP_DelayMs(g_msp_delay.delay_ms, 1);
    }
    TLSLEEP_DbgTimeRecord(TLSLEEP_FORCE_AWAKE_INNER_1);

    mspsleep_print_info("Complete wake");
    return ERR_MSP_SUCCESS;
}
/*****************************************************************************
 函 数 名  : TLSLEEP_RttSleep_Inner
 功能描述  : 唤醒流程
 输入参数  :
 输出参数  :
 返 回 值  :  VOS_VOID
*****************************************************************************/
VOS_VOID TLSLEEP_RttSleep_Inner(VOS_VOID)
{
    /*lint -save -e958*/
    VOS_BOOL bMeasFlag = VOS_FALSE;
    VOS_INT power_lock = 0;

    /*lint -restore*/
    if(0 != ((g_msp_delay.delay_control)&DELAY_CTRL_BEFOR_SLEEP))
    {
        TLSLEEP_DelayMs(g_msp_delay.delay_ms, 1);
    }
    mspsleep_print_info("start sleep");
    TLSLEEP_DbgTimeRecord(TLSLEEP_RTTSLEEP_INNER_0);

    /*检查邮箱是否允许睡眠，如果邮箱不允许睡眠则不进行睡眠和下电，直接解复位DSP*/
    /*TRUE-allow;FALSE-forbid true为1 false 为false*/
    power_lock = VOS_SplIMP();
    bMeasFlag = (VOS_BOOL)BSP_MailBox_IsAllowDspSleep();
    g_msp_pwrctrl.ForbidDspSleepValue= (read_power_status_bit(MSP_PWR_FORCE_AWAKE))|(read_power_status_bit(MSP_PWR_WAKEUP))| (!bMeasFlag); /*lint !e514*/
    TLSLEEP_DbgTimeRecord(TLSLEEP_RTTSLEEP_INNER_1);
    if(g_msp_pwrctrl.ForbidDspSleepValue)
    {
        clear_power_status_bit(MSP_PWR_WAKEUP);
        clear_power_status_bit(MSP_PWR_FORCE_AWAKE);
        clear_power_status_bit(MSP_PWR_HALT_INT);
        clear_power_status_bit(MSP_PWR_SYSTEM_RUN);
        clear_power_status_bit(MSP_PWR_WAIT_RESUMER);
        TLSLEEP_ResumeDsp();
        TLSLEEP_StateRecord(SLEEP_TASK_NOT_NEED_DEAL);
        VOS_Splx(power_lock);
        mspsleep_print_info("Resme dsp");
        return;
    }
    else
    {
        VOS_Splx(power_lock);
    }
    TLSLEEP_HwPowerDown(PWC_COMM_MODE_LTE);
    TLSLEEP_DbgTimeRecord(TLSLEEP_RTTSLEEP_INNER_2);

    power_lock = VOS_SplIMP();
    clear_power_status_bit(MSP_PWR_HALT_INT);
    clear_power_status_bit(MSP_PWR_SYSTEM_RUN);
    clear_power_status_bit(MSP_PWR_WAIT_RESUMER);
    if((!read_power_status_bit(MSP_PWR_FORCE_AWAKE))&&(!read_power_status_bit(MSP_PWR_WAKEUP)))
    {
        VOS_Splx(power_lock);

        /*投票睡眠*/
        if(0 != ((g_msp_delay.delay_control)&DELAY_CTRL_AFTER_SLEEP))
        {
            TLSLEEP_DelayMs(g_msp_delay.delay_ms, 1);
        }
#ifndef MSP_IN_V9R1
        if(((ENUM_YES_VOTE_SLEEP == (VOS_INT)g_msp_pwrctrl.SleepDrxResumeTime.ulVoteSwitch)
            &&(POWER_SAVING_SNOOZE == g_msp_pwrctrl.dsp_sleep_flag))
			||(POWER_SAVING_DEEP_SLEEP == g_msp_pwrctrl.dsp_sleep_flag))
#endif
        {
            mdrv_pm_wake_unlock(PWRCTRL_SLEEP_TLPS);
	        TLSLEEP_StateRecord(SLEEP_VOTE_UNLOCK);
        }
    }
    else
    {
        VOS_Splx(power_lock);
    }
    TLSLEEP_DbgTimeRecord(TLSLEEP_RTTSLEEP_INNER_MAX);
    mspsleep_print_info("Complete sleep");

    /* 按DSP/RCM要求，睡眠后回调RCM */
    if(pSleepFunc)
    {
        TLSLEEP_DbgTimeRecord(TLSLEEP_SLEEP_CB_0);
        pSleepFunc();
        TLSLEEP_DbgTimeRecord(TLSLEEP_SLEEP_CB_1);
    }
}

/* 构造消息包，上报可维可测信息到工具侧 */
VOS_VOID TLSLEEP_ReportMntn()
{
    MSP_SLEEP_MNTN_MSG_STRU* pSleepMsg = NULL;

    pSleepMsg = (MSP_SLEEP_MNTN_MSG_STRU*)VOS_AllocMsg(MSP_PID_DRX, sizeof(MSP_SLEEP_MNTN_MSG_STRU) -VOS_MSG_HEAD_LENGTH);

    if (pSleepMsg)
    {
        pSleepMsg->ulReceiverPid    = MSP_PID_DRX;
        pSleepMsg->ulMsgId          = ID_MSG_SLEEP_WAKEUP_SLICE_MNTN;
        pSleepMsg->ulHalt           = g_msp_pwrctrl.DrxStateSlice[DRX_HALT_INT].ulSlice;
        pSleepMsg->ulSleepStart     = g_msp_pwrctrl.DrxStateSlice[DRX_SLEEP_START].ulSlice;
        pSleepMsg->ulSleepEnd       = g_msp_pwrctrl.DrxStateSlice[DRX_SLEEP_END].ulSlice;
        pSleepMsg->ulWakeup         = g_msp_pwrctrl.DrxStateSlice[DRX_WAKEUP_INT].ulSlice;
        pSleepMsg->ulForceAwake     = g_msp_pwrctrl.DrxStateSlice[DRX_FORCE_AWAKE_API].ulSlice;
        pSleepMsg->ulWakeupStart    = g_msp_pwrctrl.DrxStateSlice[DRX_WAKEUP_START].ulSlice;
        pSleepMsg->ulAwake_CB_0     = g_msp_pwrctrl.dbg_time_record[TLSLEEP_AWAKE_CB_0];
        pSleepMsg->ulAwake_CB_1     = g_msp_pwrctrl.dbg_time_record[TLSLEEP_AWAKE_CB_1];
        pSleepMsg->ulFORCE_AWAKE_INNER_0 = g_msp_pwrctrl.dbg_time_record[TLSLEEP_FORCE_AWAKE_INNER_0];
        pSleepMsg->ulHWPOWERUP_0    = g_msp_pwrctrl.dbg_time_record[TLSEEP_HWPOWERUP_0];
        pSleepMsg->ulHWPOWERUP_1    = g_msp_pwrctrl.dbg_time_record[TLSEEP_HWPOWERUP_1];
        pSleepMsg->ulHWPOWERUP_2    = g_msp_pwrctrl.dbg_time_record[TLSEEP_HWPOWERUP_2];
        pSleepMsg->ulHWPOWERUP_3    = g_msp_pwrctrl.dbg_time_record[TLSEEP_HWPOWERUP_3];
        pSleepMsg->ulHWPOWERUP_4    = g_msp_pwrctrl.dbg_time_record[TLSEEP_HWPOWERUP_4];
        pSleepMsg->ulHWPOWERUP_5    = g_msp_pwrctrl.dbg_time_record[TLSEEP_HWPOWERUP_5];
        pSleepMsg->ulHWPOWERUP_6    = g_msp_pwrctrl.dbg_time_record[TLSEEP_HWPOWERUP_6];
        pSleepMsg->ulHWPOWERUP_7    = g_msp_pwrctrl.dbg_time_record[TLSEEP_HWPOWERUP_7];
        pSleepMsg->ulHWPOWERUP_8    = g_msp_pwrctrl.dbg_time_record[TLSEEP_HWPOWERUP_8];
        pSleepMsg->ulHWPOWERUP_9    = g_msp_pwrctrl.dbg_time_record[TLSEEP_HWPOWERUP_9];
        pSleepMsg->ulHWPOWERUP_MAX  = g_msp_pwrctrl.dbg_time_record[TLSEEP_HWPOWERUP_MAX];
        pSleepMsg->ulFORCE_AWAKE_INNER_1 = g_msp_pwrctrl.dbg_time_record[TLSLEEP_FORCE_AWAKE_INNER_1];
        pSleepMsg->ulWakeupEnd      = g_msp_pwrctrl.DrxStateSlice[DRX_WAKEUP_END].ulSlice;
        pSleepMsg->ulResume         = g_msp_pwrctrl.DrxStateSlice[DRX_RESUME_INT].ulSlice;

        DIAG_TraceReport(pSleepMsg);

        VOS_FreeMsg(MSP_PID_DRX, pSleepMsg);
    }
}

/*****************************************************************************
 函 数 名  : TLSLEEP_SleepTask
 功能描述  : msp睡眠任务的入口函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOS_VOID TLSLEEP_SleepTask(VOS_UINT32 Para0, VOS_UINT32 Para1,
                                VOS_UINT32 Para2, VOS_UINT32 Para3 )
{
    VOS_INT power_lock = 0;

    for (;;)
    {
        /* coverity[lock] */
        if(VOS_OK != VOS_SmP(g_msp_pwrctrl.task_sem, WAIT_FOR_EVER))
        {
            mspsleep_print_error("take task sem error!");
            /* coverity[missing_unlock] */
            return;
        }

        TLSLEEP_StateRecord(DRX_SLEEP_TASK);
        power_lock = VOS_SplIMP();
        /*如果当前有halt 中断*/
        if(read_power_status_bit(MSP_PWR_HALT_INT))
        {
            VOS_Splx(power_lock);
            TLSLEEP_StateRecord(DRX_SLEEP_START);
            TLSLEEP_RttSleep_Inner();
            TLSLEEP_StateRecord(DRX_SLEEP_END);
            g_msp_pwrctrl.DspLowPowerFlag = MSP_TLPHY_IN_LOW_POWER;
        }
        else if(read_power_status_bit(MSP_PWR_FORCE_AWAKE)||read_power_status_bit(MSP_PWR_WAKEUP))
        {
            VOS_Splx(power_lock);
            g_msp_pwrctrl.DspLowPowerFlag = 0;
            TLSLEEP_StateRecord(DRX_WAKEUP_START);
            TLSLEEP_RttForceAwake_Inner();
            TLSLEEP_StateRecord(DRX_WAKEUP_END);
            TLSLEEP_ReportMntn();
        }
        else
        {
            VOS_Splx(power_lock);
            mspsleep_print_debug("the status is 0x%x", g_msp_pwrctrl.pwr_status);
        }
    }
}

/*****************************************************************************
 函 数 名  : TLSLEEP_MasterWakeSlave
 功能描述  : TL作为主模，唤醒从模接口
 输入参数  : void
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
static VOS_VOID TLSLEEP_MasterWakeSlave(VOS_UINT param)
{
    VOS_UINT32 slavemode = 0;
    VOS_UINT32 i = 0, j = 0;
    
    TLSLEEP_StateRecord(DRX_MASTER_WAKE_REQ_INT);
    for(i = 0; i < MASTER_MODE_BUTT; i++)
        for(j = 0; j < SLAVE_MODE_BUTT; j++)
        {
            if(g_SocTldspInteraction->AwakeFlag.SlaveAwakeFlag[i][j] == 1)
            {
                (VOS_VOID)SLEEP_MasterWakeSlave(j);              
                g_SocTldspInteraction->AwakeFlag.SlaveAwakeFlag[i][j] = 0;
                slavemode = j + DRX_MASTER_WAKE_GSM;
                TLSLEEP_StateRecord((DRX_STATE_SLICE)slavemode);
            }
        }
}

/*****************************************************************************
 函 数 名  : TLSLEEP_DspHaltIsr
 功能描述  : 响应DSP halt中断，释放信号量开始sleep任务，使进入睡眠
 输入参数  : void
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOS_VOID TLSLEEP_DspHaltIsr(VOS_UINT param)
{
    VOS_INT flag = 0;
    /*这里是个可维可测,DSP在开始运行的第一时间置为1,*/
    if(g_SocTldspInteraction)
    {
        g_SocTldspInteraction->PstRttSleepInfo.dspState = ENUM_DSP_IS_SLEEP;
    }
    VOS_FlushCpuWriteBuf();
    flag = VOS_SplIMP();
    if(FIRST_HALT_INT == g_msp_pwrctrl.DspHaltIntMark )
    {
        mdrv_bbp_clear_wakeup_intr(PWC_COMM_MODE_LTE);
        mdrv_bbp_clear_wakeup_intr(PWC_COMM_MODE_TDS);
        mdrv_bbp_enable_wakeup_intr(PWC_COMM_MODE_LTE);
        mdrv_bbp_enable_wakeup_intr(PWC_COMM_MODE_TDS);
        g_msp_pwrctrl.DspHaltIntMark = HAD_HALT_INT;
    }
    if(read_power_status_bit(MSP_PWR_HALT_INT))
    {
        set_power_status_bit(MSP_REPEAT_HALT_ERROR);
        VOS_Splx(flag);
        return;
    }
    TLSLEEP_DbgTimeRecord(TLSLEEP_DSPHALTISR_0);
    clear_power_status_bit(MSP_PWR_SYSTEM_RUN);
    set_power_status_bit(MSP_PWR_HALT_INT);
    if(g_SocTldspInteraction)
    {
        g_msp_pwrctrl.dsp_sleep_flag = (LPHY_RTT_LPC_MODE_ENUM)(g_SocTldspInteraction->PstRttSleepInfo.ulLightSleepFlag);
    }

    TLSLEEP_StateRecord(DRX_HALT_INT);
    if(ENUM_NO_UP_DOWN_DSP == g_msp_pwrctrl.SleepDrxResumeTime.ulPowerSwich)
    {
        TLSLEEP_RttForceAwake();
    }
    else
    {
        VOS_SmV(g_msp_pwrctrl.task_sem);
    }

    TLSLEEP_SAVE_SR_STAMP(TLSLEEP_SR_POWERDOWN_1);

    VOS_Splx(flag);
}
/*****************************************************************************
 函 数 名  : TLSLEEP_DspResumeIsr
 功能描述  : 响应DSP RESUMER中断，通知邮箱DSP唤醒了
 输入参数  : void
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOS_VOID TLSLEEP_DspResumeIsr(VOS_UINT param)
{
    VOS_INT status_lock = 0;
#ifdef CONFIG_DFS_DDR
    VOS_INT ret = 0;
#endif

    status_lock = VOS_SplIMP();
    TLSLEEP_StateRecord(DRX_RESUME_INT);
    TLSLEEP_DbgTimeRecord(TLSLEEP_DSPRESUMERISR_0);
#ifdef CONFIG_DFS_DDR
    ret = TLSLEEP_DfsQosUpdate((VOS_INT32)DFS_QOS_ID_DDR_MINFREQ_E, dfs_ddr_req_id, TLSLEEP_DFS_DDR_120M);
    if(ret)
    {
        mspsleep_print_error("MSP vote TLSLEEP_DFS_DDR_120M failed!\n");
    }
#endif

    /*判断当前接收到DSP Resume中断在唤醒流程中是否正常*/
    if (read_power_status_bit(MSP_PWR_WAIT_RESUMER))
    {
        clear_power_status_bit(MSP_PWR_WAIT_RESUMER);
        if(read_power_status_bit(MSP_PWR_HALT_INT))
        {
            TLSLEEP_RttForceAwake();
            TLSLEEP_StateRecord(DRX_HALT_RESUME_CONFLICT);
        }
        else
        {
            set_power_status_bit(MSP_PWR_SYSTEM_RUN);

            /*调用邮箱驱动接口通知邮箱唤醒已经完成*/
            BSP_MailBox_DspAwakeProc(EN_MAILBOX_CALLBACK_DSP_RESUME);
            TLSLEEP_StateRecord(RESUME_NOTIFY_MAILBOX);
        }
		VOS_Splx(status_lock);
        return;
    }
    else
    {
        mspsleep_print_error("dsp resumer int is error");
        mspsleep_print_error("pwr_status = %x", g_msp_pwrctrl.pwr_status);
    }
    VOS_Splx(status_lock);
    return;
}
/*****************************************************************************
 函 数 名  : LSLEEP_RttIsSleep
 功能描述  : 查询当前TL是唤醒还是睡眠状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:当前为睡眠状态
             VOS_FALSE:当前不是睡眠状态
*****************************************************************************/
VOS_BOOL TLSLEEP_RttIsSleep(VOS_VOID)
{
    VOS_INT power_lock = 0;
    power_lock = VOS_SplIMP();
    /*lint -e514*/
    g_msp_pwrctrl.RttIsSleepValue = (read_power_status_bit(MSP_PWR_HALT_INT))\
                    |(read_power_status_bit(MSP_PWR_WAIT_RESUMER))\
                    |(!read_power_status_bit(MSP_PWR_SYSTEM_RUN));
    /*lint +e514*/
    /*TLSLEEP_StateRecord(DRX_CHECK_DSP_STATUS);*/
    if(g_msp_pwrctrl.RttIsSleepValue)
    {
        VOS_Splx(power_lock);
        return VOS_TRUE;
    }
    VOS_Splx(power_lock);
    return VOS_FALSE;
}


typedef struct
{
    VOS_UINT32      ulMspPowerup;
    VOS_UINT32      ulDspTcmResume;
    VOS_UINT32      ulInterval;

    VOS_UINT32      ulPtrWake;
    VOS_UINT32      ulPtrTimer;

    VOS_UINT32      ulSwitchLen[100];
    VOS_UINT32      ulDelay[100];
    VOS_UINT32      ulSliceWakeup[100];

    VOS_UINT32      ulSliceTimeout[100];
}TL_SLEEP_SWITCH_TIME_STRU;

TL_SLEEP_SWITCH_TIME_STRU g_stSleepSwitch = {0};

VOS_VOID TLSLEEP_ShowSleepSwitch(VOS_VOID)
{
    VOS_UINT32 i,j;

    vos_printf("ulMspPowerup %d, ulDspTcmResume %d, ulInterval %d.\n", g_stSleepSwitch.ulMspPowerup, g_stSleepSwitch.ulDspTcmResume, g_stSleepSwitch.ulInterval);

    for(i = 0; i < 25; i++)
    {
        for(j = 0; j < 4; j++)
        {
            vos_printf("ulSwitchLen %d, ulDelay %d | ", g_stSleepSwitch.ulSwitchLen[4*i+j], g_stSleepSwitch.ulDelay[4*i+j]);
        }
        vos_printf("\n");
    }

    for(i = 0; i < 10; i++)
    {
        for(j = 0; j < 10; j++)
        {
            vos_printf("ulSliceWakeup 0x%x, ulSliceTimeout 0x%x | ", g_stSleepSwitch.ulSliceWakeup[10*i+j], g_stSleepSwitch.ulSliceTimeout[10*i+j]);
        }
        vos_printf("\n");
    }

}

VOS_INT TLSLEEP_TimerIsr(VOS_INT lPara);
VOS_INT TLSLEEP_TimerIsr(VOS_INT lPara)
{
    VOS_INT power_lock = 0;

    (VOS_VOID)mdrv_timer_stop((VOS_UINT32)lPara);

    g_stSleepSwitch.ulSliceTimeout[g_stSleepSwitch.ulPtrTimer] = VOS_GetSlice();
    g_stSleepSwitch.ulPtrTimer = (g_stSleepSwitch.ulPtrTimer+1)%100;

    power_lock = VOS_SplIMP();

    if(read_power_status_bit(MSP_PWR_WAKEUP)||read_power_status_bit(MSP_PWR_FORCE_AWAKE)
      ||read_power_status_bit(MSP_PWR_SYSTEM_RUN)|| read_power_status_bit(MSP_PWR_WAIT_RESUMER))
    {
        VOS_Splx(power_lock);
        TLSLEEP_StateRecord(DRX_INVALID_WAKEUP_INT);
        return ERR_MSP_SUCCESS;
    }
    TLSLEEP_DbgTimeRecord(TLSLEEP_AWAKEISR_0);
    TLSLEEP_StateRecord(DRX_WAKEUP_INT);

    set_power_status_bit(MSP_PWR_WAKEUP);
    VOS_SmV(g_msp_pwrctrl.task_sem);

    TLSLEEP_DbgTimeRecord(TLSLEEP_AWAKEISR_1);
    VOS_Splx(power_lock);
    return ERR_MSP_SUCCESS;
}


/*****************************************************************************
 函 数 名  : LSLEEP_AwakeIsr
 功能描述  : 初始化
 输入参数  : void
 输出参数  : 无
 返 回 值  : ERR_MSP_INIT_FAILURE:初始化失败
             ERR_MSP_SUCCESS: 初始化成功
*****************************************************************************/
VOS_INT TLSLEEP_AwakeIsr(VOS_INT enMode)
{
    VOS_INT power_lock = 0;
    VOS_UINT32 ulSwitchLen;
    VOS_UINT32 ulDelay;

    /*清BBP唤醒中断*/
    mdrv_bbp_clear_wakeup_intr((PWC_COMM_MODE_E)enMode);

    ulSwitchLen = mdrv_bbp_get_wakeup_time((PWC_COMM_MODE_E)enMode);

    g_stSleepSwitch.ulDelay[g_stSleepSwitch.ulPtrWake] = 0xffffffff;

    if((0xffffffff != ulSwitchLen)
        && (0 != g_msp_pwrctrl.SleepDrxResumeTime.ulMspPowerup)
        && (0 != g_msp_pwrctrl.SleepDrxResumeTime.ulDspTcmResume)
        && (0 != g_msp_pwrctrl.SleepDrxResumeTime.ulInterval))
    {
        if(POWER_SAVING_DEEP_SLEEP == g_msp_pwrctrl.dsp_sleep_flag)
        {
            ulDelay = (g_msp_pwrctrl.SleepDrxResumeTime.ulMspPowerup + g_msp_pwrctrl.SleepDrxResumeTime.ulDspTcmResume + g_msp_pwrctrl.SleepDrxResumeTime.ulInterval);
        }
        else
        {
            ulDelay = (g_msp_pwrctrl.SleepDrxResumeTime.ulInterval);
        }

        if((ulSwitchLen > ulDelay) && ((ulSwitchLen - ulDelay) > 32))
        {
            ulDelay = ulSwitchLen - ulDelay;

            g_stSleepSwitch.ulDelay[g_stSleepSwitch.ulPtrWake] = ulDelay;

            if ( VOS_OK == mdrv_timer_start(TIMER_DSP_SWITCH_DELAY_ID, (FUNCPTR_1)TLSLEEP_TimerIsr, TIMER_DSP_SWITCH_DELAY_ID, ulDelay, TIMER_ONCE_COUNT,TIMER_UNIT_NONE) )
            {
                g_stSleepSwitch.ulSliceWakeup[g_stSleepSwitch.ulPtrWake] = VOS_GetSlice();
                g_stSleepSwitch.ulSwitchLen[g_stSleepSwitch.ulPtrWake] = ulSwitchLen;
                g_stSleepSwitch.ulPtrWake = (g_stSleepSwitch.ulPtrWake+1)%100;

                /*投票不能进入睡眠*/
                mdrv_pm_wake_lock(PWRCTRL_SLEEP_TLPS);
                return ERR_MSP_SUCCESS;
            }
        }
    }

    g_stSleepSwitch.ulSliceWakeup[g_stSleepSwitch.ulPtrWake] = VOS_GetSlice();
    g_stSleepSwitch.ulSwitchLen[g_stSleepSwitch.ulPtrWake] = ulSwitchLen;
    g_stSleepSwitch.ulPtrWake = (g_stSleepSwitch.ulPtrWake+1)%100;

    power_lock = VOS_SplIMP();

    if(read_power_status_bit(MSP_PWR_WAKEUP)||read_power_status_bit(MSP_PWR_FORCE_AWAKE)
      ||read_power_status_bit(MSP_PWR_SYSTEM_RUN)|| read_power_status_bit(MSP_PWR_WAIT_RESUMER))
    {
        VOS_Splx(power_lock);
        TLSLEEP_StateRecord(DRX_INVALID_WAKEUP_INT);
        return ERR_MSP_SUCCESS;
    }
    TLSLEEP_DbgTimeRecord(TLSLEEP_AWAKEISR_0);
    TLSLEEP_StateRecord(DRX_WAKEUP_INT);

    set_power_status_bit(MSP_PWR_WAKEUP);
    VOS_SmV(g_msp_pwrctrl.task_sem);

    TLSLEEP_DbgTimeRecord(TLSLEEP_AWAKEISR_1);
    VOS_Splx(power_lock);
    return ERR_MSP_SUCCESS;
}


/*****************************************************************************
 函 数 名  : TLSLEEP_SetChanel
 功能描述  : 兼容旧版本，设置通道信息(旧版本中最多只支持两个通道)
*****************************************************************************/
VOS_VOID TLSLEEP_SetChanel(NV_TLMODE_BASIC_PARA_STRU astChan[2])
{
    VOS_UINT32 i;

    for(i = 0; i < 2; i++)
    {
        /* 设置TCXO使用的ID */
        if(astChan[i].ucABBSwitch >= 2)
        {
            g_msp_pwrctrl.tlmode_channel[i].abb_channel_id = 0x3;
        }
        else
        {
            g_msp_pwrctrl.tlmode_channel[i].abb_channel_id = (VOS_UINT16)(0x1 << astChan[i].ucABBSwitch);
        }

        /* 设置RF使用的通道 */
        if(astChan[i].ucRFSwitch >= 2)
        {
            g_msp_pwrctrl.tlmode_channel[i].rf_channel_id = 0x3;
        }
        else
        {
            g_msp_pwrctrl.tlmode_channel[i].rf_channel_id = (VOS_UINT16)(0x1 << astChan[i].ucRFSwitch);
        }

        /* 设置TCXO使用的ID */
        if(astChan[i].ucTCXOSwitch >= 2)
        {
            g_msp_pwrctrl.tlmode_channel[i].tcxo_id = 0x3;
        }
        else
        {
            g_msp_pwrctrl.tlmode_channel[i].tcxo_id = (VOS_UINT16)(0x1 << astChan[i].ucTCXOSwitch);
        }

        g_msp_pwrctrl.tlmode_channel[i].rf_clk_id = 0;
    }
}
VOS_VOID TLSLEEP_ExcTimeTask(VOS_UINT32 Para0, VOS_UINT32 Para1,
                                VOS_UINT32 Para2, VOS_UINT32 Para3 )
{
    VOS_CHAR                  acLogPath[] = "/modem_log/msp_sleep.txt";
    FILE                      *logfp = NULL;
    VOS_UINT                  count = 0;
    VOS_CHAR                  auLogBuf[40] = {0};

    logfp = mdrv_file_open(acLogPath, "w+");
    if (VOS_NULL_PTR == logfp)
    {
        return;
    }
    mdrv_file_close(logfp);
    /*lint -save -e716*/
    while(1)
    {
    /*lint -restore*/
        if(VOS_OK != VOS_SmP(g_msp_pwrctrl.exc_overtime.time_sem, WAIT_FOR_EVER))
        {
            mspsleep_print_error("take task sem error!");
        }

        /*向文件系统中写入数据*/
        if((1 == g_msp_pwrctrl.exc_overtime.ulReadMark)&&(g_msp_pwrctrl.exc_overtime.current_count < 8))
        {
            logfp = mdrv_file_open(acLogPath, "a+");
            VOS_sprintf(auLogBuf, "< %d >\r\n", g_msp_pwrctrl.exc_overtime.current_count);
            mdrv_file_write(auLogBuf, sizeof(VOS_CHAR), sizeof(auLogBuf), logfp);
            (g_msp_pwrctrl.exc_overtime.current_count)++;
            for(count = TLSLEEP_DSPHALTISR_0; count <= TLSEEP_HWPOWERUP_MAX; count++)
            {
                VOS_MemSet((VOS_VOID*)auLogBuf, 0, 40);
                VOS_sprintf(auLogBuf, "0x%x  ", g_msp_pwrctrl.exc_overtime.ulTime[count]);
                mdrv_file_write(auLogBuf, sizeof(VOS_CHAR), 12, logfp);
                if(0 == (count + 1)%8)
                {
                    mdrv_file_write("\r\n", sizeof(VOS_CHAR), 2,logfp);
                }
            }
            mdrv_file_write("\r\n", sizeof(VOS_CHAR), 2 ,logfp);
            mdrv_file_close(logfp);
            g_msp_pwrctrl.exc_overtime.ulReadMark= 0;
        }
        else
        {
            return;
        }
    }
}

VOS_VOID TLSLEEP_GetChannelInfo()
{
    VOS_INT status_flag = 0;
    VOS_UINT32 ret;

#if (FEATURE_MODE_FEM_CHAN_EXT == FEATURE_ON)
    UCOM_NV_FEM_CHAN_PROFILE_STRU astChan;   /*lint !e813*/

    UCOM_NV_TRI_MODE_FEM_PROFILE_ID_STRU stProfile = {0};

    ret = NVM_Read(en_NV_Item_TRI_MODE_FEM_PROFILE_ID, &stProfile, sizeof(UCOM_NV_TRI_MODE_FEM_PROFILE_ID_STRU));
    ret |= NVM_Read(en_NV_Item_FEM_CHAN_PROFILE, &astChan, sizeof(UCOM_NV_FEM_CHAN_PROFILE_STRU));

    /* 拷贝LTE和TDS的通道信息到本地 */
    if(0 == ret)
    {
        VOS_MemCpy(g_msp_pwrctrl.tlmode_channel,
                    &astChan.astPara[stProfile.uwProfileId].stModeBasicPara[PWC_COMM_MODE_LTE],
                    sizeof(g_msp_pwrctrl.tlmode_channel));
    }

#else
    NV_TLMODE_BASIC_PARA_STRU astChan[2];

    ret = NVM_Read(NV_ID_MSP_TLMODE_CHAN_PARA_STRU, astChan, 2*sizeof(NV_TLMODE_BASIC_PARA_STRU));

    if(0 == ret)
    {
        TLSLEEP_SetChanel(astChan);
    }

#endif

    if(ret)
    {
        /* coverity[lock_acqire] */
        msp_set_error_bit(status_flag, MSP_READ_NV_FAIL);
        mspsleep_print_error("Read NV: channel Data Fail.");
    }
}


/*****************************************************************************
 函 数 名  : LSLEEP_Init
 功能描述  : 初始化
 输入参数  : void
 输出参数  : 无
 返 回 值  : ERR_MSP_INIT_FAILURE:初始化失败
             ERR_MSP_SUCCESS: 初始化成功
*****************************************************************************/
VOS_UINT32 TLSLEEP_Init(VOS_VOID)
{
    VOS_UINT32 Argument[VOS_TARG_NUM];
    VOS_UINT32 ExcArgument[VOS_TARG_NUM];
    int status_flag = 0;
	int lte_int_num = 0, tds_int_num = 0, ret = 0;
    unsigned int debug_len = 0;
    VOS_UINT_PTR realAddr = 0;
    VOS_UINT32 ulSize;

#ifndef MSP_IN_V9R1
    g_msp_pwrctrl.dump_len = 0x1000;
    g_msp_pwrctrl.dump_base = (VOS_VOID * )mdrv_om_register_field(OM_CP_MSP_SLEEP, "tl_sleep", (void*)0, (void*)0, 0x1000, 0);

    if(VOS_NULL == g_msp_pwrctrl.dump_base)
    {
        mspsleep_print_error("get exc buffer error,module id = %d", OM_CP_MSP_SLEEP);
        g_msp_pwrctrl.dump_base = (VOS_VOID * )VOS_UnCacheMemAlloc(g_msp_pwrctrl.dump_len, &realAddr);
    }
#else
    {
        g_msp_pwrctrl.dump_len = 0x1000;
        g_msp_pwrctrl.dump_base = (VOS_VOID * )VOS_UnCacheMemAlloc(g_msp_pwrctrl.dump_len, &realAddr);
    }
#endif
    ret = TLSLEEP_GetSRDDRAddr();
    if(ret)
    {
        mspsleep_print_error("Get DDR_SR_STAMP_ADDR failed!\n");
    }

    if(VOS_NULL != g_msp_pwrctrl.dump_base)
    {
        VOS_MemSet((void *)g_msp_pwrctrl.dump_base, 0, g_msp_pwrctrl.dump_len);
        /*初始化可维可测*/
        debug_len = (VOS_UINT)MSP_EXC_RECORED_TIME_SIZE;
        g_msp_pwrctrl.time_queue_record = (drx_queue_t*)(MSP_EXC_RECORED_TIME_OFFSET);
        QueueInit(g_msp_pwrctrl.time_queue_record, (debug_len - 0x10)/sizeof(DRX_RECORD_STRU));
        g_msp_pwrctrl.DrxStateSlice = (SLEEP_RECORD_STRU*)(MSP_EXC_STATE_SLICE_OFFSET);
        g_msp_pwrctrl.DrxStateEnd = MSP_EXC_STATE_SLICE_OFFSET + MSP_EXC_STATE_SLICE_SIZE;
        g_msp_pwrctrl.dsp_state = (DspState *)MSP_EXC_DSP_STATE_OFFSET;
    }
    g_msp_pwrctrl.exc_overtime.timeOut = 45;

    g_msp_pwrctrl.pwr_status = 0;

    if(VOS_OK != VOS_SmBCreate("EXC", 0, VOS_SEMA4_FIFO, &g_msp_pwrctrl.exc_overtime.time_sem))
    {
        mspsleep_print_error("SLEEP_Init: Create EXC SEM Fail.");
        return ERR_MSP_INIT_FAILURE;
    }

    if(VOS_OK != VOS_SmBCreate("TC_0", 0, VOS_SEMA4_FIFO, &g_msp_pwrctrl.SleepTcxoSem[0]))
    {
        msp_set_error_bit(status_flag, MSP_CREATE_TCXO0_SEM_FAIL);
        mspsleep_print_error("SLEEP_Init: Create TCXO 0 Fail.");
        return ERR_MSP_INIT_FAILURE;
    }
    if(VOS_OK != VOS_SmBCreate("TC_1", 0, VOS_SEMA4_FIFO, &g_msp_pwrctrl.SleepTcxoSem[1]))
    {
        msp_set_error_bit(status_flag, MSP_CREATE_TCXO1_SEM_FAIL);
        mspsleep_print_error("SLEEP_Init: Create TCXO 1 Fail.");
        return ERR_MSP_INIT_FAILURE;
    }
#ifndef MSP_IN_V9R1
    /* 读取delay nv */
    if(NVM_Read(NV_ID_DRV_DRX_DELAY, &g_msp_drx_delay, sizeof(DRV_DRX_DELAY_STRU)))
    {
        memset(&g_msp_drx_delay, 0x0, sizeof(DRV_DRX_DELAY_STRU));
    }
#endif
    /* 读取NV器件稳定时间 */
    if(NVM_Read(NV_ID_MSP_TL_DRX_RESUME_TIME, &g_msp_pwrctrl.SleepDrxResumeTime, sizeof(NV_TL_DRX_RESUME_TIME_STRU)))
    {
        g_msp_pwrctrl.SleepDrxResumeTime.ulTcxoRsmTime = 3000;
        g_msp_pwrctrl.SleepDrxResumeTime.ulMspPowerup = 0;
        g_msp_pwrctrl.SleepDrxResumeTime.ulDspTcmResume = 0;
        g_msp_pwrctrl.SleepDrxResumeTime.ulInterval = 0;
        /* coverity[lock_acqire] */
        msp_set_error_bit(status_flag, MSP_READ_NV_FAIL);
        mspsleep_print_error("Read NV: 0x%x Data Fail.", NV_ID_MSP_TL_DRX_RESUME_TIME);
    }
    else
    {
        g_stSleepSwitch.ulMspPowerup = g_msp_pwrctrl.SleepDrxResumeTime.ulMspPowerup;
        g_stSleepSwitch.ulDspTcmResume = g_msp_pwrctrl.SleepDrxResumeTime.ulDspTcmResume;
        g_stSleepSwitch.ulInterval = g_msp_pwrctrl.SleepDrxResumeTime.ulInterval;
    }

    TLSLEEP_GetChannelInfo();

    /*任务信号量初始化*/
    if(VOS_SmBCreate( "SLEEP", 0, VOS_SEMA4_FIFO , &g_msp_pwrctrl.task_sem))
    {
        msp_set_error_bit(status_flag, MSP_CREATE_TASK_SEM_FAIL);
        mspsleep_print_error("create task sem failed");
        return ERR_MSP_INIT_FAILURE;
    }
    /* 初始化exc任务用于在唤醒超时的时候向文件系统中写入唤醒的时间记录*/
    /* coverity[sleep] */
	if(VOS_CreateTask("mspExcTask", &g_msp_pwrctrl.exc_overtime.timeTaskId, TLSLEEP_ExcTimeTask, MSP_EXC_TASK_PRI, 2048, ExcArgument))
	{
		mspsleep_print_error("create Exc task failed");
	}
    /* 初始化睡眠任务*/
    /* coverity[sleep] */
	if(VOS_CreateTask("mspSleepTask", &g_msp_pwrctrl.task_id, TLSLEEP_SleepTask, MSP_SLEEP_TASK_PRI, 32768, Argument))
	{
        msp_set_error_bit(status_flag, MSP_CREATE_TASK_FAIL);
		mspsleep_print_error("create msp task failed");
	}

    /*调用邮箱注册接口注册检查当前是允许睡眠和注册强制唤醒接口函数*/
    BSP_MailBox_GetDspStatusReg((BSP_MBX_GET_STATUS_FUNC)TLSLEEP_RttIsSleep);
    BSP_MailBox_DspForceAwakeReg(TLSLEEP_RttForceAwake);
#ifdef CONFIG_DFS_DDR
    /*为了提高dsp镜像恢复速度，austin版本增加对DDR的调频功能*/
    ret  = TLSLEEP_DfsQosRequest((VOS_INT32)DFS_QOS_ID_DDR_MINFREQ_E, TLSLEEP_DFS_DDR_75M, &dfs_ddr_req_id);
    if(ret)
    {
        set_power_status_bit(MSP_DFS_REQUEST_FAIL);/* [false alarm]:屏蔽Fortify */
        mspsleep_print_error("request dfs fai, ret = %d\n", ret);
    }
#endif

#ifdef MSP_IN_V9R1
    ret += TLSLEEP_DfsQosRequest((VOS_INT32)DFS_QOS_ID_BUS_MINFREQ_E, TLSLEEP_DFS_BUS_75M, &dfs_bus_req_id);
    ret += TLSLEEP_DfsQosRequest((VOS_INT32)DFS_QOS_ID_DDR_MINFREQ_E, TLSLEEP_DFS_DDR_75M, &dfs_ddr_req_id);
    ret += TLSLEEP_DfsQosRequest((VOS_INT32)DFS_QOS_ID_CCPU_MINFREQ_E, TLSLEEP_DFS_CCPU_150M, &dfs_ccpu_req_id);/* [false alarm]:屏蔽Fortify */
    if(ret)
    {
        set_power_status_bit(MSP_DFS_REQUEST_FAIL);/* [false alarm]:屏蔽Fortify */
        mspsleep_print_error("request dfs fai, ret = %d\n", ret);
    }
#endif
    mdrv_bbp_clear_wakeup_intr(PWC_COMM_MODE_LTE);
    mdrv_bbp_clear_wakeup_intr(PWC_COMM_MODE_TDS);
    mdrv_bbp_disable_wakeup_intr(PWC_COMM_MODE_LTE);
    mdrv_bbp_disable_wakeup_intr(PWC_COMM_MODE_TDS);
	lte_int_num = mdrv_int_get_num(BSP_INT_TYPE_LBBP_AWAKE);
	tds_int_num = mdrv_int_get_num(BSP_INT_TYPE_TBBP_AWAKE);

    ret =  mdrv_int_connect(lte_int_num, (VOIDFUNCPTR)TLSLEEP_AwakeIsr, (VOS_INT)PWC_COMM_MODE_LTE);
    ret += mdrv_int_connect(tds_int_num, (VOIDFUNCPTR)TLSLEEP_AwakeIsr, (VOS_INT)PWC_COMM_MODE_TDS);

    ret += mdrv_ipc_int_connect((IPC_INT_LEV_E)IPC_INT_DSP_HALT, TLSLEEP_DspHaltIsr, 0);
    ret += mdrv_ipc_int_connect((IPC_INT_LEV_E)IPC_INT_DSP_RESUME, TLSLEEP_DspResumeIsr, 0);
    ret += mdrv_ipc_int_connect((IPC_INT_LEV_E)IPC_INT_WAKE_SLAVE, (VOIDFUNCPTR)TLSLEEP_MasterWakeSlave, 0);
    if(ret)
    {
        msp_set_error_bit(status_flag, MSP_INT_CONNECT_FAIL);
		mspsleep_print_error("int connect fail!");
		return ERR_MSP_INIT_FAILURE;
    }
    ret = mdrv_int_enable(lte_int_num);
    ret += mdrv_int_enable(tds_int_num);
    ret += mdrv_ipc_int_enable(IPC_INT_DSP_HALT);
    ret += mdrv_ipc_int_enable(IPC_INT_DSP_RESUME);
    ret += mdrv_ipc_int_enable(IPC_INT_WAKE_SLAVE);
    if(ret)
    {
        msp_set_error_bit(status_flag, MSP_INT_ENABLE_FAIL);
		mspsleep_print_error("int connect fail!");
		return ERR_MSP_INIT_FAILURE;
    }

    ret = mdrv_getmeminfo(BSP_DDR_TYPE_SRAM_TLDSP_SHARED, (VOS_UINT32 *)(&g_SocTldspInteraction), &ulSize);
    if(ret)
    {
		mspsleep_print_error("mdrv_getmeminfo BSP_DDR_TYPE_SRAM_TLDSP_SHARED fail!");
		return ERR_MSP_INIT_FAILURE;
    }

    VOS_MemSet((void *)g_SocTldspInteraction, 0, ulSize);    

    ret = mdrv_getmeminfo(BSP_DDR_TYPE_SHM_TIMESTAMP, &g_ulAddrShrDdr, &ulSize);
    if(ret)
    {
		mspsleep_print_error("mdrv_getmeminfo BSP_DDR_TYPE_SHM_TIMESTAMP fail!");
		return ERR_MSP_INIT_FAILURE;
    }

    /*初始化和DSP之间的标志，CCPU上下电要判定这个标志决定是否给TCXO上下电*/
    g_SocTldspInteraction->PstRttSleepInfo.ulLightSleepFlag = POWER_SAVING_NULL;
    VOS_FlushCpuWriteBuf();

    mspsleep_print_error("msp sleep init OK!");

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : bsp_mailbox_init
 功能描述  : 主模唤醒从模的接口,L为从模，由GU唤醒,msp提供,oam调用
 输入参数  : None
 输出参数  : None
 返 回 值  : None
*****************************************************************************/
VOS_VOID TLSLEEP_MasterAwakeSlave(VOS_VOID)
{
    TLSLEEP_StateRecord(DRX_SLAVE_WAKE_INT);
    TLSLEEP_RttForceAwake();
}

/*****************************************************************************
 函 数 名  : TLSLEEP_InitPowerUp
 功能描述  : 提供给协议栈调用，用于在DSP加载之前调用，下面这些物理上默认是上电的
             需要软件设置为上电状态
 输入参数  : None
 输出参数  : None
 返 回 值  : None
*****************************************************************************/
VOS_VOID TLSLEEP_ActivateHw(PWC_COMM_MODE_E modeId)
{
    PWC_COMM_MODEM_E                    enModem = PWC_COMM_MODEM_0;
#if (FEATURE_MULTI_CHANNEL == FEATURE_ON)
    PWC_COMM_CHANNEL_E                  enChannel = PWC_COMM_CHANNEL_0;
#endif
    VOS_INT32                           ret = 0;
    VOS_INT                             flag = 0;
    VOS_UINT32                          timestamp_begin = 0;
    VOS_UINT32                          timestamp_end = 0;
	enModem = PWC_COMM_MODEM_0;

    TLSLEEP_OpenTCXO();
    g_msp_pwrctrl.DspLowPowerFlag = 0;
#if (FEATURE_MULTI_CHANNEL == FEATURE_ON)

    ret = TLSLEEP_DfsQosUpdate((VOS_INT32)DFS_QOS_ID_CCPU_MINFREQ_E, dfs_ccpu_req_id,TLSLEEP_DFS_CCPU_600M);/* [false alarm]:屏蔽Fortify */
    if(ret)
    {
        set_power_status_bit(MSP_DFS_HW_UPDATE_FAIL);/* [false alarm]:屏蔽Fortify */
    }

    TLSLEEP_PwrctrlUp(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_ABB);
    /* 协议栈开机时，先使能PLL，再给BBP上电、开钟 */
    mdrv_pm_enable_pllclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBP_DRX, enModem, enChannel);
    TLSLEEP_PllEnable(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_ABB);

    /* TDS的BBP上电接口中同时给CS/PS两个分区上电，LTE分区的电由DSP控制 */
    /* LTE模式也依赖CS/PS分区，所以CS/PS分区LTE单模也必须上电 */
    mdrv_pm_pwrup(PWC_COMM_MODE_TDS, PWC_COMM_MODULE_BBP_DRX, enModem, enChannel);

    /*打开TDS 使用的BBP 1A分区时钟*/
    mdrv_pm_enable_bbpclk(PWC_COMM_MODE_TDS, PWC_COMM_MODULE_BBP_DRX, enModem, enChannel);

    /* LTE涉及多个时钟源，DSP只控制一部分，需要MSP调用底软接口打开LTE相关所有时钟 */
    mdrv_pm_enable_bbpclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBP_DRX, enModem, enChannel);

    TLSLEEP_PwrctrlUp(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_RF);

#else

#ifdef MSP_IN_V9R1
    /*DDR和总线频率最小值为150M,V9R1使用*/
    ret += TLSLEEP_DfsQosUpdate((VOS_INT32)DFS_QOS_ID_BUS_MINFREQ_E, dfs_bus_req_id, TLSLEEP_DFS_BUS_150M);
    ret += TLSLEEP_DfsQosUpdate((VOS_INT32)DFS_QOS_ID_DDR_MINFREQ_E, dfs_ddr_req_id, TLSLEEP_DFS_DDR_150M);
    ret += TLSLEEP_DfsQosUpdate((VOS_INT32)DFS_QOS_ID_CCPU_MINFREQ_E, dfs_ccpu_req_id,TLSLEEP_DFS_CCPU_600M);
    if(ret)
    {
        set_power_status_bit(MSP_DFS_HW_UPDATE_FAIL);
    }
#endif
	/*RF电源上电要先于RFPLLenable，并且要间隔200us*/
    TLSLEEP_PwrctrlUp(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_RF);
    timestamp_begin = mdrv_timer_get_normal_timestamp();
    ret = mdrv_pm_enable_pllclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBE16, enModem, PWC_COMM_CHANNEL_0);
    if(ret)
    {
        mspsleep_print_error("bbe16 pll_enable fail!");
    }
    TLSLEEP_PwrctrlUp(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_ABB);
    ret = mdrv_pm_pwrup(PWC_COMM_MODE_TDS, PWC_COMM_MODULE_BBP_DRX, enModem, PWC_COMM_CHANNEL_0);
    ret += mdrv_pm_pwrup(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBP_DRX, enModem, PWC_COMM_CHANNEL_0);
    if(ret)
    {
        mspsleep_print_error("bbp powerup fail!");
    }
    /*打开TDS 使用的BBP 1A分区时钟*/
    ret = mdrv_pm_enable_bbpclk(PWC_COMM_MODE_TDS, PWC_COMM_MODULE_BBP_DRX, enModem, PWC_COMM_CHANNEL_0);
    ret += mdrv_pm_enable_bbpclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBP_DRX, enModem, PWC_COMM_CHANNEL_0);
    ret += mdrv_pm_enable_pllclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBP_DRX, enModem, PWC_COMM_CHANNEL_0);
    if(ret)
    {
        mspsleep_print_error("bbp_pllclk_enable fail!");
    }

    TLSLEEP_PllEnable(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_ABB);

    ret = mdrv_pm_pwrup(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_FEM, enModem, PWC_COMM_CHANNEL_0);
    if(ret)
    {
        mspsleep_print_error("FEM powerup fail!");
    }

#ifdef CONFIG_PASwitch_V7R5

    /*  PA 只针对V7R5，规避总线挂死bug  */
    TLSLEEP_PwrctrlUp(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_PA);
    TLSLEEP_PwrctrlUp(PWC_COMM_MODE_TDS, PWC_COMM_MODULE_PA);
#endif
    /*RF电源上电要先于RFPLLenable，并且要间隔200us*/
    do
    {
        timestamp_end = mdrv_timer_get_normal_timestamp();
    }while((msp_get_timer_slice_delta(timestamp_begin, timestamp_end)) < 7);

    TLSLEEP_PllEnable(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_RF);

    /*全系统初始化上电进行ET初始化*/
    RTTAGENT_EtSignalingInit();
#endif
    flag = VOS_SplIMP();
    set_power_status_bit(MSP_PWR_SYSTEM_RUN);
    VOS_Splx(flag);

    return;
}

VOS_VOID TLSLEEP_ResumeDsp(VOS_VOID)
{
    mdrv_dsp_stop_bbe();
    mdrv_dsp_reset_bbe();
    mdrv_dsp_unreset_bbe();
    TLSLEEP_RunDsp();
}

/*****************************************************************************
 函 数 名  : TLSLEEP_GetPreSfn
 功能描述  : 此接口用于读取DSP在进入睡眠前锁存的TDS的子贞号，目前是所存在了低功耗所使用的SRAM空间中
 输入参数  : VOS_VOID
 输出参数  : DSP在进入睡眠前锁存的TDS的子贞号,PS调用
 返 回 值  : DSP在进入睡眠前锁存的TDS的子贞号,PS调用
*****************************************************************************/
VOS_UINT32 TLSLEEP_GetPreSfn(VOS_VOID)
{
    VOS_INT32 ret;
    VOS_UINT32 ulSize;
    SRAM_SOC_TLDSP_INTERACTION_STRU *SocTldspInteraction = 0;

    if(VOS_NULL_PTR == g_SocTldspInteraction)
    {
        ret = mdrv_getmeminfo(BSP_DDR_TYPE_SRAM_TLDSP_SHARED, (VOS_UINT32 *)SocTldspInteraction, &ulSize);
        if(ret)
        {
            return 0;
        }
    }
    else
    {
        SocTldspInteraction = g_SocTldspInteraction;
    }

    if(VOS_NULL_PTR == SocTldspInteraction)
    {
        return 0;
    }

    return SocTldspInteraction->PstRttSleepInfo.ulTdsPreSfn;
}
/*****************************************************************************
 函 数 名  : LSLEEP_ShowStat
 功能描述  :
 输入参数  : void
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID TLSLEEP_ShowStat(VOS_UINT32 ulIndex)
{
    VOS_UINT i = 0, bbp_pll = 0, bbp_ldo = 0;
    PWC_COMM_MODEM_E                    enModem = PWC_COMM_MODEM_0;
    PWC_COMM_CHANNEL_E                  enChannel = PWC_COMM_CHANNEL_0;
    VOS_INT                             ulTcxoStatus[2] = {0};
    VOS_UINT32                          abb_pll[2] = {0};
    VOS_UINT32                          rf_ldo[2] = {0};
	enModem = PWC_COMM_MODEM_0;
    bbp_pll = (VOS_UINT)mdrv_pm_get_pllclk_status(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBP_DRX, enModem, enChannel);
    abb_pll[0] = (VOS_UINT32)mdrv_pm_get_pllclk_status(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_ABB, PWC_COMM_MODEM_0, enChannel);
    abb_pll[1] = (VOS_UINT32)mdrv_pm_get_pllclk_status(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_ABB, PWC_COMM_MODEM_1, enChannel);

    rf_ldo[0] = (VOS_UINT32)mdrv_pm_get_pwrstatus(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_RF, PWC_COMM_MODEM_0, enChannel);
    rf_ldo[1] = (VOS_UINT32)mdrv_pm_get_pwrstatus(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_RF, PWC_COMM_MODEM_1, enChannel);
    bbp_ldo = (VOS_UINT)mdrv_pm_get_pwrstatus(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBP_DRX, enModem, enChannel);
    ulTcxoStatus[0] = mdrv_pm_get_tcxo_status(PWC_COMM_MODEM_0);
    ulTcxoStatus[1] = mdrv_pm_get_tcxo_status(PWC_COMM_MODEM_1);
    /*lint -save -e713 -e574*/
    vos_printf("RTT SLEEP Show Statistics Info:\n");

    vos_printf("Sleep system state: 0x%x\n", read_power_status_bit(MSP_PWR_SYSTEM_RUN));
    vos_printf("BBP Pll state:      0x%x\n", bbp_pll);
    vos_printf("ABB CHN0 Pll state: 0x%x\n", abb_pll[0]);
    vos_printf("ABB CHN1 Pll state: 0x%x\n", abb_pll[1]);

    vos_printf("RF LDO0 state:       0x%x\n",rf_ldo[0]);
    vos_printf("RF LDO1 state:       0x%x\n",rf_ldo[1]);

    vos_printf("BBP LDO state:      0x%x\n",bbp_ldo);
    vos_printf("TCXO 0 state :      0x%x\n",ulTcxoStatus[0]);
    vos_printf("TCXO 1 state:      0x%x\n",ulTcxoStatus[1]);
    vos_printf("\n");

    vos_printf("Sleep Cmd mask:     0x%x\n",g_msp_pwrctrl.pwr_status);
    vos_printf("Deep Sleep Flag:     0x%x\n",g_msp_pwrctrl.dsp_sleep_flag);
    vos_printf("Last is sleep value: 0x%x\n", g_msp_pwrctrl.RttIsSleepValue);
    vos_printf("Forbid Dsp value: 0x%x\n", g_msp_pwrctrl.ForbidDspSleepValue);

    vos_printf("\n");
    if(VOS_NULL != g_msp_pwrctrl.DrxStateSlice)
    {
    vos_printf("DSP Halt Int:       Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DRX_HALT_INT].ulCount,g_msp_pwrctrl.DrxStateSlice[DRX_HALT_INT].ulSlice);
    vos_printf("SLEEP task:         Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DRX_SLEEP_TASK].ulCount,g_msp_pwrctrl.DrxStateSlice[DRX_SLEEP_TASK].ulSlice);
    vos_printf("Sleep NeedNot Deal: Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[SLEEP_TASK_NOT_NEED_DEAL].ulCount,g_msp_pwrctrl.DrxStateSlice[SLEEP_TASK_NOT_NEED_DEAL].ulSlice);
    vos_printf("DSP deep sleep:     Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DSP_DEEP_SLEEP_COUNT].ulCount,g_msp_pwrctrl.DrxStateSlice[DSP_DEEP_SLEEP_COUNT].ulSlice);
    vos_printf("DSP liaght sleep:   Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DSP_LIGHT_SLEEP_COUNT].ulCount,g_msp_pwrctrl.DrxStateSlice[DSP_LIGHT_SLEEP_COUNT].ulSlice);
	vos_printf("Store DspMem Fail:  Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[STORE_DSP_TCM_FAIL].ulCount,g_msp_pwrctrl.DrxStateSlice[STORE_DSP_TCM_FAIL].ulSlice);
    vos_printf("Vote sleep:         Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[SLEEP_VOTE_UNLOCK].ulCount,g_msp_pwrctrl.DrxStateSlice[SLEEP_VOTE_UNLOCK].ulSlice);
    vos_printf("Invalid Wake Int:   Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DRX_INVALID_WAKEUP_INT].ulCount,g_msp_pwrctrl.DrxStateSlice[DRX_INVALID_WAKEUP_INT].ulSlice);
    vos_printf("Wake Int:           Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DRX_WAKEUP_INT].ulCount,g_msp_pwrctrl.DrxStateSlice[DRX_WAKEUP_INT].ulSlice);
	vos_printf("Restore DspMem Fail Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[RESTORE_DSP_TCM_FAIL].ulCount,g_msp_pwrctrl.DrxStateSlice[RESTORE_DSP_TCM_FAIL].ulSlice);
    vos_printf("Force Awake API:    Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DRX_FORCE_AWAKE_API].ulCount,g_msp_pwrctrl.DrxStateSlice[DRX_FORCE_AWAKE_API].ulSlice);
    vos_printf("Force Not Nedd Deal   Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DRX_FORCE_AWAKE_NOT_DEAL].ulCount,g_msp_pwrctrl.DrxStateSlice[DRX_FORCE_AWAKE_NOT_DEAL].ulSlice);
    vos_printf("Force Awake Dsp Run:Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DRX_FORCE_AWAKE_RUN_RETURN].ulCount,g_msp_pwrctrl.DrxStateSlice[DRX_FORCE_AWAKE_RUN_RETURN].ulSlice);
    vos_printf("Wait Tcxo Sem Fail: Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DRX_FAIL_WAIT_TCXO_SEM].ulCount,g_msp_pwrctrl.DrxStateSlice[DRX_FAIL_WAIT_TCXO_SEM].ulSlice);
    vos_printf("Resume Notify Mail: Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[RESUME_NOTIFY_MAILBOX].ulCount,g_msp_pwrctrl.DrxStateSlice[RESUME_NOTIFY_MAILBOX].ulSlice);
    vos_printf("DSP Resume Int:     Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DRX_RESUME_INT].ulCount,g_msp_pwrctrl.DrxStateSlice[DRX_RESUME_INT].ulSlice);
	vos_printf("SLAVE Wake Int:     Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DRX_SLAVE_WAKE_INT].ulCount,g_msp_pwrctrl.DrxStateSlice[DRX_SLAVE_WAKE_INT].ulSlice);
	vos_printf("Check Dsp Status:   Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DRX_CHECK_DSP_STATUS].ulCount,g_msp_pwrctrl.DrxStateSlice[DRX_CHECK_DSP_STATUS].ulSlice);
	vos_printf("Sleep Flag Error:   Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DSP_SLEEP_FLAG_ERROR].ulCount,g_msp_pwrctrl.DrxStateSlice[DSP_SLEEP_FLAG_ERROR].ulSlice);
	vos_printf("Halt Resume Conflict:Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DRX_HALT_RESUME_CONFLICT].ulCount,g_msp_pwrctrl.DrxStateSlice[DRX_HALT_RESUME_CONFLICT].ulSlice);
    vos_printf("Master Wake Req Int: Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DRX_MASTER_WAKE_REQ_INT].ulCount,g_msp_pwrctrl.DrxStateSlice[DRX_MASTER_WAKE_REQ_INT].ulSlice);
    vos_printf("Master Wake GSM: Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DRX_MASTER_WAKE_GSM].ulCount,g_msp_pwrctrl.DrxStateSlice[DRX_MASTER_WAKE_GSM].ulSlice);
    vos_printf("Master Wake WCDMA: Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DRX_MASTER_WAKE_WCDMA].ulCount,g_msp_pwrctrl.DrxStateSlice[DRX_MASTER_WAKE_WCDMA].ulSlice);
    vos_printf("Master Wake LTE: Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DRX_MASTER_WAKE_LTE].ulCount,g_msp_pwrctrl.DrxStateSlice[DRX_MASTER_WAKE_LTE].ulSlice);
    vos_printf("Master Wake TDS: Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DRX_MASTER_WAKE_TDS].ulCount,g_msp_pwrctrl.DrxStateSlice[DRX_MASTER_WAKE_TDS].ulSlice);
    vos_printf("Master Wake CDMA_1X: Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DRX_MASTER_WAKE_CDMA_1X].ulCount,g_msp_pwrctrl.DrxStateSlice[DRX_MASTER_WAKE_CDMA_1X].ulSlice);
    vos_printf("Master Wake CDMA_HRPD: Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DRX_MASTER_WAKE_CDMA_HRPD].ulCount,g_msp_pwrctrl.DrxStateSlice[DRX_MASTER_WAKE_CDMA_HRPD].ulSlice);
    }
    if (0 != ulIndex)
    {
        vos_printf("\n");
        vos_printf("==========================================================\n");
        vos_printf("Time Record: count 0x%x position %d\n",g_msp_pwrctrl.SleepTimeRecord.ulCount,((g_msp_pwrctrl.SleepTimeRecord.ulCount-1)%SLEEP_RECORD_NUM));
        vos_printf("Num   Type               Time\n");
        for (i=0; i<(g_msp_pwrctrl.SleepTimeRecord.ulCount < SLEEP_RECORD_NUM ? g_msp_pwrctrl.SleepTimeRecord.ulCount : SLEEP_RECORD_NUM); i++)
        {
            vos_printf("%03d   %16s   0x%08x\n",i ,(VOS_INT)g_msp_pwrctrl.SleepTimeRecord.astRecord[i].acType, g_msp_pwrctrl.SleepTimeRecord.astRecord[i].ulTime);
        }
    }
    vos_printf("dbg time record addr = 0x%08x\r\n", (VOS_UINT)g_msp_pwrctrl.dbg_time_record);
    vos_printf("queue time record addr = 0x%08x\r\n", (VOS_UINT)g_msp_pwrctrl.time_queue_record->data);
    vos_printf("drx state slice addr = 0x%08x\r\n", (VOS_UINT)g_msp_pwrctrl.DrxStateSlice);
    vos_printf("timestamp shared memory address = 0x%08x\r\n", g_ulAddrShrDdr);
    /*lint -restore*/

}

/*****************************************************************************
 函 数 名  : TLSLEEP_ShowDebugTime
 功能描述  :
 输入参数  : void
 输出参数  : 无
 返 回 值  : 可维可测函数用于打印上下电过程中的时间点
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID TLSLEEP_ShowDebugTime(VOS_INT mode)
{
    EN_SLEEP_TIME_RECORD i = TLSLEEP_RTTSLEEP_INNER_0;
    VOS_UINT32 count = 0;

    vos_printf("%s:\n", "sleep:", 0, 0, 0, 0, 0);
    for(i = TLSLEEP_DSPHALTISR_0; i <= TLSLEEP_RTTSLEEP_INNER_MAX; i++)
    {
        vos_printf("%08x  ", g_msp_pwrctrl.dbg_time_record[i], 0, 0, 0, 0, 0);
    }
    vos_printf("\n%s:\n", "wake", 0, 0, 0, 0, 0);/* [false alarm]:屏蔽Fortify */
    for(i = TLSLEEP_AWAKEISR_0, count = 0; i <= TLSLEEP_DSPRESUMERISR_MAX; i++)
    {
        vos_printf("%08x  ", g_msp_pwrctrl.dbg_time_record[i], 0, 0, 0, 0, 0);
        count++;
        if(count%8 == 0)
        {
            vos_printf("\n", 0, 0, 0, 0, 0, 0);
        }
    }
}


VOS_VOID TLSLEEP_ShowPowerTime(VOS_VOID);

VOS_VOID TLSLEEP_ShowPowerTime(VOS_VOID)
{
    VOS_UINT32 i = 0;
    VOS_UINT32 start = 0, end = 0;

    mdrv_pm_wake_lock(PWRCTRL_SLEEP_TLPS);

    for(i = 0; i < ((VOS_UINT)MSP_EXC_RECORED_TIME_SIZE / sizeof(DRX_RECORD_STRU)); i++)
    {
        if(g_msp_pwrctrl.time_queue_record->data[i].ulState < TLSLEEP_FORCE_AWAKE_INNER_0)
        {
            continue;
        }

        if(TLSLEEP_FORCE_AWAKE_INNER_0 == g_msp_pwrctrl.time_queue_record->data[i].ulState)
        {
            start = g_msp_pwrctrl.time_queue_record->data[i].ulSlice;
            vos_printf("\n %08x      ", g_msp_pwrctrl.time_queue_record->data[i].ulSlice);
        }
        else if(g_msp_pwrctrl.time_queue_record->data[i].ulState < TLSLEEP_FORCE_AWAKE_INNER_1)
        {
            vos_printf("%08x      ", g_msp_pwrctrl.time_queue_record->data[i].ulSlice);
        }
        else if(TLSLEEP_FORCE_AWAKE_INNER_1 == g_msp_pwrctrl.time_queue_record->data[i].ulState)
        {
            end = g_msp_pwrctrl.time_queue_record->data[i].ulSlice;
            vos_printf("%08x     (%08x)\n", g_msp_pwrctrl.time_queue_record->data[i].ulSlice, (end - start));
        }
        else
        {
            continue;
        }
    }

    mdrv_pm_wake_unlock(PWRCTRL_SLEEP_TLPS);

    return;
}


#else
int TLSEEP_IsSlaveSleep(void)
{
    return 1;
}
VOS_UINT32 TLSLEEP_Init(VOS_VOID)
{
    return VOS_OK;
}
VOS_BOOL TLSLEEP_RttIsSleep(VOS_VOID)
{
    return VOS_FALSE;
}
VOS_VOID TLSLEEP_RttForceAwake(VOS_VOID)
{
}

VOS_VOID TLSLEEP_MasterAwakeSlave(VOS_VOID)
{
}

VOS_VOID TLSLEEP_ActivateHw(PWC_COMM_MODE_E modeId)
{
}

VOS_UINT32 TLSLEEP_GetPreSfn(VOS_VOID)
{
    return 0;
}

#endif
/*lint +e409*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


