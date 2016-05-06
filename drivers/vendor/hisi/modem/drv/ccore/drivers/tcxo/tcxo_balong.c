/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : tcxo_balong.c
  版 本 号   : 初稿
  作    者   : 徐经翠x00221564
  生成日期   : 2013年8月26日
  最近修改   :
  功能描述   : tcxo_balong.c
  函数列表   :
  修改历史   :
  1.日    期   :  徐经翠x00221564
    作    者   : 2013年8月26日
    修改内容   : 创建文件

******************************************************************************/
#include <mdrv_timer.h>
#include <tcxo_balong.h>
#include <bsp_dpm.h>
#include <bsp_abb.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define  adp_dpm_printf(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ADP_DPM, "[tcxo]: <%s> "fmt"", __FUNCTION__, ##__VA_ARGS__))

unsigned int g_stTcxoVoteMap[PWC_TCXO_ID_BUTT] = {0, 0};
unsigned int g_stTcxoInited = PWC_TCXO_UNINITED;

PWC_TCXO_ID_E g_stModemId2TcxoId[PWC_COMM_MODEM_BUTT] = {
    PWC_TCXO_ID_0,
    PWC_TCXO_ID_1
};

struct tcxo_info tcxo_soft_timer[PWC_TCXO_ID_BUTT] = {
        {
            {{NULL, 0, 0}, {NULL, 0, 0}, {NULL, 0, 0}, {NULL, 0, 0}},
            PWC_TCXO_TIMER_STOP,
            PWRCTRL_COMM_ON
        },
        {
            {{NULL, 0, 0}, {NULL, 0, 0}, {NULL, 0, 0}, {NULL, 0, 0}},
            PWC_TCXO_TIMER_STOP,
            PWRCTRL_COMM_OFF
        }
};

/*用于控制PMU TCXO1 EN 和RFIC1同开同关，同时保证和TCXO1开关的重入
*/


struct tcxo_debug_stru{
	unsigned int enable_count[2];                      /*使能次数*/
	unsigned int disable_count[2];                     /*去使能次数*/
	unsigned int valid_enable_count;		     /*有效的开关次数*/
	unsigned int valide_disable_count;
	unsigned int vote;                                  /*[0]:RFIC1, [1]:TCXO1*/
};

static struct tcxo_debug_stru tcxo_debug_info[2] = {
	{{0},{0},0,0,0},
	{{0},{0},0,0,0}
};
unsigned int disable_delta[2];
#ifdef CONFIG_V7R2_CLK_CRG
/***************************************************************************
 函 数 名  : bsp_pmu_tcxo1_en_enable
 功能描述  :使能PMU TCXO1 EN
 调用函数  :
 被调函数  :

 修改历史      :
**************************************************************************/
/*lint --e{718,746}*/
void bsp_pmu_tcxo1_en_enable(PMU_TCXO_EN bit_value)
{
	if(!tcxo_debug_info[0].vote){
		tcxo_debug_info[0].valid_enable_count++;
		hi_pwrctrl_tcxo1_pmu_en_enable();
	}
	if(!(tcxo_debug_info[0].vote & ((unsigned int)0x1 << bit_value))){
		   tcxo_debug_info[0].vote |= ((unsigned int)0x1 << bit_value);
	}
	tcxo_debug_info[0].enable_count[bit_value]++;
	return;
}
/***************************************************************************
 函 数 名  : bsp_pmu_tcxo1_en_disable
 功能描述  :去使能PMU TCXO1 EN
 调用函数  :
 被调函数  :

 修改历史      :
**************************************************************************/
void bsp_pmu_tcxo1_en_disable(PMU_TCXO_EN bit_value)
{
	tcxo_debug_info[0].disable_count[bit_value]++;
	 if(tcxo_debug_info[0].vote & ((unsigned int)0x1 << bit_value)){
			tcxo_debug_info[0].vote &= ~((unsigned int)0x1 << bit_value);
	 }
	  if(!tcxo_debug_info[0].vote){
		tcxo_debug_info[0].valide_disable_count++;
		hi_pwrctrl_tcxo1_pmu_en_disable();
	  }
	  return;
}

/*软件控制打开TCXO1*/
void bsp_tcxo1_enable(void)
{
	hi_pwrctrl_tcxo1_abb_en_enable();
    bsp_pmu_tcxo1_en_enable(TCXO1_ID_1);
	return;
}

/*软件控制关闭TCXO1*/
void bsp_tcxo1_disable(void)
{
	bsp_pmu_tcxo1_en_disable(TCXO1_ID_1);

    /*延迟4个32K周期*/
    udelay(123);
    hi_pwrctrl_tcxo1_abb_en_disable();
	return;
}

 /*软件配置TCXO1初始化状态*/
 void bsp_tcxo1_init(void)
{
	/*默认关闭PMU TCXO1 EN*/
	hi_pwrctrl_tcxo1_pmu_en_disable();

}
#elif defined(CONFIG_K3V3_CLK_CRG)
unsigned int gTcxo1FirstEnableFlag = 0;

void bsp_pmu_tcxo1_en_enable(PMU_TCXO_EN bit_value)
{
    return;
}
void bsp_pmu_tcxo1_en_disable(PMU_TCXO_EN bit_value)
{
    return;
}

void bsp_tcxo1_set_flag(unsigned int flag)
{
    gTcxo1FirstEnableFlag = flag;
}

unsigned int bsp_tcxo1_get_flag(void)
{
    return gTcxo1FirstEnableFlag;
}

/*软件控制打开TCXO1*/
void bsp_tcxo1_enable(void)
{
    if(bsp_tcxo1_get_flag() == 1)
    {
        bsp_tcxo1_set_flag(0);
        bsp_tcxo1_enable_first();
    }
    else
    {
        (void)bsp_abb_buffer_enable(ABB_BUFFER_ID_1, ABB_BUFFER_VOTE_TCXO);
    }
}

/* C核下电再上电第一次打开TCXO1,  要保证在锁中断的情况下调用*/
void bsp_tcxo1_enable_first(void)
{
	unsigned int regvalue = 0;
	unsigned int tmp = 0;
	unsigned int t1 = 0;
	unsigned int t2 = 0;

	regvalue = readl(HI_AP_SYSCTRL_BASE_ADDR_VIRT + 0x10);

    /*如果TCXO1已经打开，直接返回*/
    if(regvalue & ((unsigned int)0x1 << 7)){
        (void)bsp_abb_buffer_enable(ABB_BUFFER_ID_1, ABB_BUFFER_VOTE_TCXO);

	    tmp = readl(HI_AP_SYSCTRL_BASE_ADDR_VIRT + 0x1C);
		/* 判断打开是否完成 */
		if(tmp & ((unsigned int)0x1 << 13))
		{
		    t1 = bsp_get_slice_value();
			do
		    {
		        tmp = readl(HI_AP_SYSCTRL_BASE_ADDR_VIRT + 0x1C);
			    tmp &= (unsigned int)0x1 << 13;
		    }while(tmp);
			t2 = bsp_get_slice_value();
			adp_dpm_printf("===tcxo=== t1=0x%x,t2=0x%x,t2-t1=0x%x\n", t1, t2, t2-t1, 0, 0, 0);
		}
        tcxo_soft_timer[PWC_TCXO_ID_1].tcxo_status = PWRCTRL_COMM_ON;

    }
	else
	{
        (void)bsp_abb_buffer_enable(ABB_BUFFER_ID_1, ABB_BUFFER_VOTE_TCXO);
	}
}

/*软件控制关闭TCXO1 要保证在锁中断的情况下调用*/
void bsp_tcxo1_disable(void)
{
    /*正常关闭流程*/
    (void)bsp_abb_buffer_disable(ABB_BUFFER_ID_1, ABB_BUFFER_VOTE_TCXO);
	return;
}
static s32 tcxo1_check_status(struct dpm_device *dev)
{
    unsigned int regvalue = 0;

    /*判断TCXO1的状态*/
    regvalue = readl(HI_AP_SYSCTRL_BASE_ADDR_VIRT + 0x10);
    regvalue &= (unsigned int)0x1 << 7;
    if(regvalue){
         if(g_stTcxoVoteMap[PWC_COMM_MODEM_1]&((unsigned int)0x1 << PWC_COMM_MODE_GSM)){
             adp_dpm_printf("GSM open TCXO1,but no close it,modem can't sleep!\n\n");
         }
         if(g_stTcxoVoteMap[PWC_COMM_MODEM_1]&((unsigned int)0x1 << PWC_COMM_MODE_WCDMA)){
             adp_dpm_printf("WCDMA open TCXO1,but no close it,modem can't sleep!\n\n");
         }
         if(g_stTcxoVoteMap[PWC_COMM_MODEM_1]&((unsigned int)0x1 << PWC_COMM_MODE_LTE)){
             adp_dpm_printf("LTE open TCXO1,but no close it,modem can't sleep!\n\n");
         }
         if(g_stTcxoVoteMap[PWC_COMM_MODEM_1]&((unsigned int)0x1 << PWC_COMM_MODE_TDS)){
             adp_dpm_printf("TDS open TCXO1,but no close it,modem can't sleep!\n\n");
         }
         return -1;
    }
    return 0;
}
static struct dpm_device tcxo1_dpm =
{
	.device_name = "tcxo1 dpm",
	.prepare = tcxo1_check_status,
};

/*软件配置TCXO1初始化状态*/
void bsp_tcxo1_init(void)
{
    unsigned int regvalue = 0;
	s32 ret = 0;

    /*TCXO1由软件控制*/
    regvalue = readl(HI_AP_SYSCTRL_BASE_ADDR_VIRT + 0x10);
    regvalue |= (unsigned int)0x1 << 8;
    writel(regvalue, HI_AP_SYSCTRL_BASE_ADDR_VIRT + 0x10);

    writel(0x5D, HI_AP_SYSCTRL_BASE_ADDR_VIRT + 0x18);

    /*TCXO1默认关闭*/
    regvalue = readl(HI_AP_SYSCTRL_BASE_ADDR_VIRT + 0x10);
    regvalue &= ~((unsigned int)0x1 << 7);
    writel(regvalue, HI_AP_SYSCTRL_BASE_ADDR_VIRT + 0x10);

    /*确认关闭完成*/
    while(!(readl(HI_AP_SYSCTRL_BASE_ADDR_VIRT + 0x1C) & (0x1 << 13))) {
        ;
    }
    ret = bsp_device_pm_add(&tcxo1_dpm);
    if(ret)
    {
        adp_dpm_printf("tcxo1 dpm callback function register fail!\n");
    }
    return;
}

#endif
 /***************************************************************************
 函 数 名  : bsp_tcxo_getstatus
 功能描述  : 获取TCXO状态
 输入参数  :
		           enModemId  Modem ID
 输出参数  : 无
 返 回 值  : PWRCTRL_COMM_ON         使能;
                       PWRCTRL_COMM_OFF        禁止;
                       MDRV_ERROR                          参数异常
 调用函数  :
 被调函数  :

 修改历史      :
**************************************************************************/
int mdrv_pm_get_tcxo_status(PWC_COMM_MODEM_E enModemId)
{
    int ret = PWRCTRL_COMM_ON;
    PWC_TCXO_ID_E tcxoId;
    unsigned long flags = 0;

    /*参数检查，非法返回MDRV_ERROR */
    /* coverity[unsigned_compare] */
    if((enModemId < PWC_COMM_MODEM_0) || (enModemId >= PWC_COMM_MODEM_BUTT))
    {
        adp_dpm_printf("Input param error.enModemId:%d\n", enModemId);
        return MDRV_ERROR;
    }
    if(g_stTcxoInited != PWC_TCXO_INITED)
    {
        adp_dpm_printf("tcxo uninited,becase software uninited!\n");
       return MDRV_ERROR;
    }

     local_irq_save(flags);

    /*V7R2 chanle 0 use tcxo0,always on*/
    tcxoId = g_stModemId2TcxoId[enModemId];
    ret = tcxo_soft_timer[tcxoId].tcxo_status;

     local_irq_restore(flags);
    return ret;
}

/***************************************************************************
 函 数 名  : bsp_tcxo_enable
 功能描述  : 使能TCXO
 输入参数  : enModemId  Modem ID
	                    enModeType    Mode type
 输出参数  : 无
 返 回 值  : MDRV_OK         成功
                       MDRV_ERROR        失败
 调用函数  :
 被调函数  :

 修改历史      :
**************************************************************************/
int mdrv_pm_enable_tcxo(PWC_COMM_MODEM_E  enModemId, PWC_COMM_MODE_E enModeType)
{
    unsigned long flags = 0;
    int ret = MDRV_OK;
    PWC_TCXO_ID_E tcxoId;

	/*参数检查，非法返回MDRV_ERROR */
	/* coverity[unsigned_compare] */
    if ((enModeType < PWC_COMM_MODE_GSM) || (enModeType >= PWC_COMM_MODE_BUTT)
      ||(enModemId < PWC_COMM_MODEM_0) || (enModemId >= PWC_COMM_MODEM_BUTT))
    {
        adp_dpm_printf("Input param error.\n");
        return MDRV_ERROR;
    }
    if(g_stTcxoInited != PWC_TCXO_INITED)
    {
        adp_dpm_printf("tcxo uninited,becase software uninited!\n");
	 return MDRV_ERROR;
    }

     local_irq_save(flags);

    /*V7R2 chanle 0 use tcxo0,always on*/
    tcxoId = g_stModemId2TcxoId[enModemId];
    if(PWC_TCXO_ID_0 == tcxoId){
        tcxo_soft_timer[tcxoId].tcxo_status = PWRCTRL_COMM_ON;
        ret = MDRV_OK;
        goto out;
    }
    if(g_stTcxoVoteMap[tcxoId] == 0)
    {
        /*open TCXO1*/
        bsp_tcxo1_enable();
    }
    if(g_stTcxoVoteMap[tcxoId] & ((unsigned int)1 << enModeType)){
        adp_dpm_printf("ModeType: %d has enable TCXO1,enable don't match with disable!\n WCDMA: 0 GSM:1 LTE:2 TDS:3\n", enModeType);
    }else{
        g_stTcxoVoteMap[tcxoId] |= ((unsigned int)1 << enModeType);
    }
out:
     local_irq_restore(flags);
     return ret;
}

/***************************************************************************
 函 数 名  : bsp_tcxo_disable
 功能描述  : 关闭TCXO
 输入参数  : enModemId  Modem ID
	         enModeType    Mode type
 输出参数  : 无
 返 回 值  : MDRV_OK         成功
                       MDRV_ERROR        失败
	                 MDRV_ERROR_NOT_FOUND 没有投票使能
 调用函数  :
 被调函数  :

 修改历史      :
**************************************************************************/
int mdrv_pm_disable_tcxo(PWC_COMM_MODEM_E  enModemId, PWC_COMM_MODE_E enModeType)
{
        unsigned long flags = 0;
        int ret = MDRV_OK;
        PWC_TCXO_ID_E tcxoId;

        /* coverity[unsigned_compare] */
        if ((enModeType < PWC_COMM_MODE_GSM) || (enModeType >= PWC_COMM_MODE_BUTT)\
          ||(enModemId < PWC_COMM_MODEM_0) || (enModemId >= PWC_COMM_MODEM_BUTT))
        {
            adp_dpm_printf("Input param error.\n");
            return MDRV_ERROR ;
        }

        if(g_stTcxoInited != PWC_TCXO_INITED)
        {
            adp_dpm_printf("tcxo uninited,becase software uninited!\n");
            return MDRV_ERROR;
        }

         local_irq_save(flags);

         /*V7R2 chanle 0 use tcxo0,always on*/
        tcxoId = g_stModemId2TcxoId[enModemId];
        if(PWC_TCXO_ID_0 == tcxoId){
            tcxo_soft_timer[tcxoId].tcxo_status = PWRCTRL_COMM_OFF;
            ret = MDRV_OK;
            goto out;
        }
        if(g_stTcxoVoteMap[tcxoId] & ((unsigned int)1 << enModeType))
        {
            g_stTcxoVoteMap[tcxoId] &= (~((unsigned int)1 << enModeType));
        }
        if(0 == g_stTcxoVoteMap[tcxoId])
        {
                bsp_tcxo1_disable();
                tcxo_soft_timer[tcxoId].tcxo_status = PWRCTRL_COMM_OFF;
        }
out:
        local_irq_restore(flags);
        return ret;
}

/***************************************************************************
 函 数 名  : tcxo_timer_handle
 功能描述  : TCXO 定时器到时处理函数
 输入参数  : arg     启动定时器时传入的参数
 输出参数  : 无
 返 回 值  : MDRV_OK         成功
                       MDRV_ERROR        失败
 调用函数  :
 被调函数  :

 修改历史      :
**************************************************************************/
static void tcxo_timer_handle(int arg)
{
        unsigned long flags = 0;
        int i = 0;
        PWC_TCXO_ID_E tcxoId;
        PWC_TCXO_FUNCPTR pFuncPtr;
        PWC_COMM_MODEM_E enModemId = (PWC_COMM_MODEM_E)arg;

         local_irq_save(flags);

        /*根据modem id查找到使用的tcxo*/
        tcxoId = g_stModemId2TcxoId[enModemId];

        /*依次调用之前启动tcxo timer的回调函数*/
        for(i = 0; i < PWC_COMM_MODE_BUTT; i++)
        {
            pFuncPtr = tcxo_soft_timer[tcxoId].g_stTcxoTimerStru[i].routine;
            if(pFuncPtr != NULL)
            {   /*lint -e522*/
                pFuncPtr(tcxo_soft_timer[tcxoId].g_stTcxoTimerStru[i].arg);
                tcxo_soft_timer[tcxoId].g_stTcxoTimerStru[i].routine = NULL;
            }
        }
        tcxo_soft_timer[tcxoId].timer_status = PWC_TCXO_TIMER_STOP;
        tcxo_soft_timer[tcxoId].tcxo_status = PWRCTRL_COMM_ON;
	if(0 != mdrv_timer_stop(TIMER_CCPU_DRX1_STABLE_ID)){
		adp_dpm_printf("can't stop TCXO1 hardtimer!\n");
	}
        local_irq_restore(flags);
    	  return;
}

/***************************************************************************
 函 数 名  : bsp_tcxo_timer_start
 功能描述  : TCXO 定时器启动
 输入参数  : enModemId  Modem ID
    	                    enModeType    Mode type
    	                    routine:回调函数  注:回调函数在中断上下文中执行
                          arg:回调参数
                          timerValue:计数值 单位ms
 输出参数  : 无
 返 回 值  : MDRV_OK         成功
                       MDRV_ERROR        失败
 调用函数  :
 被调函数  :

 修改历史      :
**************************************************************************/
int mdrv_pm_start_tcxo_timer(PWC_COMM_MODEM_E  enModemId, PWC_COMM_MODE_E enModeType, PWC_TCXO_FUNCPTR routine,int arg, unsigned int timerValue)
{
        unsigned long flags = 0;
        PWC_TCXO_ID_E tcxoId;
	int ret = 0;

        /*参数检查，非法返回MDRV_ERROR */
	/* coverity[unsigned_compare] */
        if ((enModeType < PWC_COMM_MODE_GSM) || (enModeType >= PWC_COMM_MODE_BUTT)\
          ||(enModemId < PWC_COMM_MODEM_0) || (enModemId >= PWC_COMM_MODEM_BUTT)\
          || (NULL == routine) || (0 == timerValue))
        {
            adp_dpm_printf("Input param error.\n");
            return MDRV_ERROR;
        }
        if(g_stTcxoInited != PWC_TCXO_INITED)
        {
                adp_dpm_printf("Input param error.\n");
              return MDRV_ERROR;
        }
         local_irq_save(flags);

        tcxoId = g_stModemId2TcxoId[enModemId];
        if(PWC_TCXO_ID_0 == tcxoId){
            routine(arg);
            local_irq_restore(flags);
            return MDRV_OK;
        }
        /*记录回调相关信息到g_stTcxoTimerStru ,用于timer到时回调使用*/
        tcxo_soft_timer[tcxoId].g_stTcxoTimerStru[enModeType].routine = routine;
        tcxo_soft_timer[tcxoId].g_stTcxoTimerStru[enModeType].arg = arg;
        tcxo_soft_timer[tcxoId].g_stTcxoTimerStru[enModeType].timerValue = timerValue;

        /*如果timer已启动，释放锁，返回*/
        if(PWC_TCXO_TIMER_RUNNING == tcxo_soft_timer[tcxoId].timer_status)
        {
            local_irq_restore(flags);
            return MDRV_OK;
        }
        else
        {
            tcxo_soft_timer[tcxoId].timer_status = PWC_TCXO_TIMER_RUNNING;
        }
	ret = mdrv_timer_start(TIMER_CCPU_DRX1_STABLE_ID,(FUNCPTR_1)tcxo_timer_handle,(int)enModemId,timerValue,TIMER_ONCE_COUNT,TIMER_UNIT_MS);
	if(ret){
		adp_dpm_printf("DRV_TIMER_START TCXO1 failure!\n");
		tcxo_soft_timer[tcxoId].timer_status = PWC_TCXO_TIMER_STOP;
	}

        local_irq_restore(flags);
        return ret;
}

int mdrv_pm_get_tcxo_rfclk_status(PWC_COMM_CHANNEL_E enChannel)
{
    return 0;
}
int mdrv_pm_enable_tcxo_rfclk(PWC_COMM_MODEM_E  enModemId, PWC_COMM_MODE_E enModeType, PWC_COMM_CHANNEL_E enChannel)
{
    return 0;
}
int mdrv_pm_disable_tcxo_rfclk(PWC_COMM_MODEM_E  enModemId, PWC_COMM_MODE_E enModeType, PWC_COMM_CHANNEL_E enChannel)
{
    return 0;
}
/* ccore should close auxiliary-tcxo before sleep,
 or usb can not wakeup mcore from deepsleep */
/*set pwrctrl2  bit 21 bit23  zero*/

struct tcxo_suspend_ctrl
{
    u32 tcxo_is_suspended;
    u32 pwc2_abb_ch1_tcxo_en;
    u32 pwc2_pmu_ch1_tcxo_en;
};

static struct tcxo_suspend_ctrl tcxo_ctrl = {0};

void tcxo_suspend(void)
{
    if(1==*(u32*)SRAM_RTT_SLEEP_FLAG_ADDR)
    { /*if dsp light sleep, auxiliary-tcxo should not be suspended*/
        tcxo_ctrl.tcxo_is_suspended = false;
        return;
    }
    else
    {
        tcxo_ctrl.tcxo_is_suspended = true;
        /*save pwrctrl2 and set bit 21 bit23  zero*/
        tcxo_ctrl.pwc2_abb_ch1_tcxo_en = hi_pwrctrl_get_pwr_ctrl2_abb_ch1_tcxo_en();
        tcxo_ctrl.pwc2_pmu_ch1_tcxo_en = hi_pwrctrl_get_pwr_ctrl2_pmu_ch1_tcxo_en();
        hi_pwrctrl_set_pwr_ctrl2_abb_ch1_tcxo_en(0);
        hi_pwrctrl_set_pwr_ctrl2_pmu_ch1_tcxo_en(0);
    }
}
void tcxo_resume(void)
{
    if(false == tcxo_ctrl.tcxo_is_suspended)
    {
        return;
    }
    else
    {
        /*resume pwrctrl2 --- bit 21 bit23 */
        hi_pwrctrl_set_pwr_ctrl2_abb_ch1_tcxo_en(tcxo_ctrl.pwc2_abb_ch1_tcxo_en);
        hi_pwrctrl_set_pwr_ctrl2_pmu_ch1_tcxo_en(tcxo_ctrl.pwc2_pmu_ch1_tcxo_en);
    }
}

/***************************************************************************
 函 数 名  : tcxo_init_configure
 功能描述  : 根据NV项值初始化TCXO通道配置
 输入参数  :
 输出参数  : 无
 返 回 值  : MDRV_OK         成功
             MDRV_ERROR        失败
 调用函数  :
 被调函数  :

 修改历史      :
**************************************************************************/
int tcxo_init_configure(void)
{
	unsigned int regvalue = 0;
	NV_TLMODE_BASIC_PARA_STRU tl_mode_nv[2];
    NV_TLMODE_BASIC_PARA_STRU gu_mode_nv[2];
    /*使用V7R2默认配置*/
    g_stModemId2TcxoId[PWC_COMM_MODEM_0] = PWC_TCXO_ID_0;
    g_stModemId2TcxoId[PWC_COMM_MODEM_1] = PWC_TCXO_ID_1;

    /*标记TCXO配置软件已经初始化*/
    g_stTcxoInited = PWC_TCXO_INITED;

    if(NV_OK != bsp_nvm_read(NV_ID_DRV_GUMODE_CHAN_PARA, (u8 *)gu_mode_nv, 2 * sizeof(NV_TLMODE_BASIC_PARA_STRU))){
        adp_dpm_printf("en_NV_Item_GUMODE_CHAN_PARA:0x138 read failure!\n");
        return 0;
    }
    if(NV_OK != bsp_nvm_read(NV_ID_DRV_TLMODE_CHAN_PARA_STRU, (u8 *)tl_mode_nv, 2 * sizeof(NV_TLMODE_BASIC_PARA_STRU))){
        adp_dpm_printf("NV_ID_TLMODE_CHAN_PARA_STRU:0xD01B read failure!\n");
        return 0;
    }
#ifdef CONFIG_V7R2_CLK_CRG
    /*根据NVID=0XD01B选择 BBP PLL时钟源*/
	if(tl_mode_nv[0].ucTCXOSwitch == 1){
		regvalue = readl(HI_SYSCRG_BASE_ADDR_VIRT + HI_CRG_CLK_SEL3_OFFSET);
        regvalue |= (unsigned int)0x1 << 1;
        writel(regvalue, HI_SYSCRG_BASE_ADDR_VIRT + HI_CRG_CLK_SEL3_OFFSET);
		adp_dpm_printf("BBP PLL come from ABB CH1!\n");
	}else{
		regvalue = readl(HI_SYSCRG_BASE_ADDR_VIRT + HI_CRG_CLK_SEL3_OFFSET);
        regvalue &= ~((unsigned int)0x1 << 1);
        writel(regvalue, HI_SYSCRG_BASE_ADDR_VIRT + HI_CRG_CLK_SEL3_OFFSET);
		adp_dpm_printf("BBP PLL come from ABB CH0!\n");
    }
    /*根据NVID=138选择G1BBP_104M G2BBP_104M时钟源*/
	if(gu_mode_nv[0].ucABBSwitch == 1){
		regvalue = readl(HI_SYSCRG_BASE_ADDR_VIRT + HI_CRG_CLK_SEL3_OFFSET);
        regvalue |= (unsigned int)0x1 << 5;
        regvalue &= ~((unsigned int)0x1 << 6);
        writel(regvalue, HI_SYSCRG_BASE_ADDR_VIRT + HI_CRG_CLK_SEL3_OFFSET);
		adp_dpm_printf("G1BBP_104M come from ABB CH1,G2BBP_104M come from ABB CH0!\n");
	}else{
		regvalue = readl(HI_SYSCRG_BASE_ADDR_VIRT + HI_CRG_CLK_SEL3_OFFSET);
        regvalue &= ~((unsigned int)0x1 << 5);
        regvalue |= (unsigned int)0x1 << 6;
        writel(regvalue, HI_SYSCRG_BASE_ADDR_VIRT + HI_CRG_CLK_SEL3_OFFSET);
		adp_dpm_printf("G1BBP_104M come from ABB CH0,G2BBP_104M come from ABB CH1!\n");
    }
#elif defined(CONFIG_K3V3_CLK_CRG)
    /*根据NVID=0XD01B选择 BBP PLL时钟源*/
    if(tl_mode_nv[0].ucTCXOSwitch == 1){
        regvalue = readl(HI_SYSCRG_BASE_ADDR_VIRT + HI_CRG_CLK_SEL3_OFFSET);
        regvalue |= (unsigned int)0x1 << 1;
        writel(regvalue, HI_SYSCRG_BASE_ADDR_VIRT + HI_CRG_CLK_SEL3_OFFSET);
        adp_dpm_printf("BBP PLL come from ABB CH1!\n");
    }else{
        regvalue = readl(HI_SYSCRG_BASE_ADDR_VIRT + HI_CRG_CLK_SEL3_OFFSET);
        regvalue &= ~((unsigned int)0x1 << 1);
        writel(regvalue, HI_SYSCRG_BASE_ADDR_VIRT + HI_CRG_CLK_SEL3_OFFSET);
        adp_dpm_printf("BBP PLL come from ABB CH0!\n");
    }
    /*根据NVID=138选择G1BBP_104M G2BBP_104M时钟源*/
    if(gu_mode_nv[0].ucABBSwitch == 1){
        regvalue = readl(HI_SYSCRG_BASE_ADDR_VIRT + HI_CRG_CLK_SEL3_OFFSET);
        regvalue |= (unsigned int)0x1 << 5;
        regvalue &= ~((unsigned int)0x1 << 6);
        writel(regvalue, HI_SYSCRG_BASE_ADDR_VIRT + HI_CRG_CLK_SEL3_OFFSET);
        adp_dpm_printf("G1BBP_104M come from ABB CH1,G2BBP_104M come from ABB CH0!\n");
    }else{
        regvalue = readl(HI_SYSCRG_BASE_ADDR_VIRT + HI_CRG_CLK_SEL3_OFFSET);
        regvalue &= ~((unsigned int)0x1 << 5);
        regvalue |= (unsigned int)0x1 << 6;
        writel(regvalue, HI_SYSCRG_BASE_ADDR_VIRT + HI_CRG_CLK_SEL3_OFFSET);
        adp_dpm_printf("G1BBP_104M come from ABB CH0,G2BBP_104M come from ABB CH1!\n");
    }
#endif
    /*软件配置TCXO1初始化状态*/
    bsp_tcxo1_init();
    adp_dpm_printf("tcxo init success!\n");
    return 0;
}
/***************************************************************************
 函 数 名  : debug tcxo
**************************************************************************/

int tcxo_count = 0;
static void debug_timer_callback(void)
{
     tcxo_count = (int)bsp_get_slice_value();
    adp_dpm_printf("timer stamp 2 = %d\n", bsp_get_slice_value());
    adp_dpm_printf("soft timer call back ok");
}
void debug_tcxo_function(PWC_COMM_MODEM_E  tcxoId, PWC_COMM_MODE_E enModeType)
{
    int ret = 0;/* [false alarm]:误报 */
    ret = bsp_tcxo_disable(tcxoId, enModeType);
    ret = bsp_tcxo_getstatus(tcxoId);
    adp_dpm_printf("tcxoID:%d,status = 0x%x\n", tcxoId, ret);/* [false alarm]:误报 */
    ret = bsp_tcxo_enable(tcxoId, enModeType);/* [false alarm]:误报 */
    ret = bsp_tcxo_timer_start(tcxoId, enModeType, (PWC_TCXO_FUNCPTR)debug_timer_callback, 0, 3);
    adp_dpm_printf("timer stamp 1 = %d\n", bsp_get_slice_value());
    ret = bsp_tcxo_getstatus(tcxoId);
    adp_dpm_printf("tcxoID:%d,status = 0x%x\n", tcxoId, ret);
}
void debug_tcxo(void)
{
	    unsigned int vote = g_stTcxoVoteMap[PWC_TCXO_ID_1];
	    adp_dpm_printf("************tcxo1 vote map**********\n");
	    adp_dpm_printf("vote map: WCDMA: %d,GSM: %d,LTE: %d,TDS: %d\n", vote&((unsigned int)1 << PWC_COMM_MODE_WCDMA),\
	         (vote >> PWC_COMM_MODE_GSM)&(unsigned int)0x1, (vote >> PWC_COMM_MODE_LTE)&(unsigned int)0x1, (vote >> PWC_COMM_MODE_TDS)&(unsigned int)0x1);

	   adp_dpm_printf("pmu_tcxo1 _en: RFIC1 enable count: %d, RFIC1 diable count: %d\n", tcxo_debug_info[0].enable_count[0], tcxo_debug_info[0].disable_count[0]);
	   adp_dpm_printf("pmu_tcxo1 _en: TCXO1 enable count: %d, TCXO1 diable count: %d\n", tcxo_debug_info[0].enable_count[1], tcxo_debug_info[0].disable_count[1]);
	   adp_dpm_printf("pmu_tcxo1 _en: valid enable count: %d, valid diable count: %d\n", tcxo_debug_info[0].valid_enable_count, tcxo_debug_info[0].valide_disable_count);
	   adp_dpm_printf("pmu_tcxo1 _en: RFIC1 VOTE STATUS : %d, TCXO1 VOTE STATUS : %d\n", (tcxo_debug_info[0].vote & 0x1), ((tcxo_debug_info[0].vote >> 1) & (unsigned int)0x1));

	   adp_dpm_printf("tcxo_count= %d\n",tcxo_count);
   }
#ifdef __cplusplus
#if __cplusplus
        }
#endif
#endif

