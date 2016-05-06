/*----------------------------------------------------------------------------
 *      balongv7r2 m3 pm
 *----------------------------------------------------------------------------
 *      Name:    pm.C
 *      Purpose: RTX example program
 *----------------------------------------------------------------------------
 *      This code is part of balongv7r2 PWR.
 *---------------------------------------------------------------------------*/

#include <ARMCM3.h>
#include "console.h"
#include "printk.h"

#include "osl_types.h"
#include "osl_bio.h"
#include "osl_irq.h"

#include "m3_pm.h"
#include "mdrv_ipc.h"
#include "ipc_balong.h"
#include "drv_nv_def.h"
#include "drv_nv_id.h"
#include "bsp_nvim.h"
//#include "bsp_pm_om.h"
#include "m3_cpufreq.h"
#include "bsp_icc.h"
#include "bsp_hardtimer.h"
#include "wdt_balong.h"
#include "m3_dump.h"
/*lint --e{40, 63, 409, 958} */

#ifndef bsp_pm_log_type
#define bsp_pm_log_type(a,b,c,d)
#endif
enum pm_log_type_m3pm
{
    ACORE_WAKE,
    CCORE_WAKE,
    HIFI_WAKE,
    MCORE_WAKE,
};

static void pm_nv_init(void);
static void pm_ipc_init(void);
static void IntIpcAcoreHandler(u32 irq);
static void IntIpcCcoreHandler(u32 irq);
static void IntIpcHiFiHandler(u32 irq);
static void thread_pm (void const *arg);
s32 pm_wsrc_set_init(void);
void pm_wakelock_init(void);


osMailQDef(pm_mail, 32, T_PM_MAIL);	/*lint !e133 !e64*/
osMailQId  pm_mail;

osThreadId thread_pm_id;
osThreadDef(thread_pm, osPriorityHigh, 1, 512);/*lint !e133 */


T_PM_ST gPmSt;
T_PM_BAKEUP_ST gPmBakeupSt;
T_PM_COUNT_ST gPmCountSt;
T_PM_ERROR_ST gPmErrorSt;
DRV_NV_PM_TYPE gPmNvSt;
DRV_DRX_DELAY_STRU gNvDrxDelaySt;

struct m3_pm_stamp g_m3_pm_stamp;

struct m3_pm_stamp *m3_pm_stamps = NULL;
void stamp_value_init()
{

    m3_pm_stamps = &g_m3_pm_stamp;//(struct m3_pm_stamp *)(PWR_SRAM_DEBUG_ADDR);
    if(m3_pm_stamps)
    {
        m3_pm_stamps->magic_asc_m3pm = 0x6D70336D;
        m3_pm_stamps->magic_stamp1 = 0x5A5A5A5A;
        m3_pm_stamps->buck3off.magic_start = 0x5A33335A;
        m3_pm_stamps->buck3off.magic_asc_3off = 0x46464F33;
        m3_pm_stamps->buck3off.magic_stamp = 0x5A33335A;
        m3_pm_stamps->buck3off.magic_go_to_sleep = 0x5A33335A;
        
        m3_pm_stamps->buck3on.magic_start = 0x5A00005A;
        m3_pm_stamps->buck3on.magic_asc_3on = 0x004E4F33;
        m3_pm_stamps->buck3on.magic_stamp = 0x5A00005A;
        m3_pm_stamps->buck3on.magic_go_to_sleep = 0x5A00005A;
    }
}
void pm_init(void)
{
	memset((void*)&gPmSt, 0x0, sizeof(T_PM_ST));
	memset((void*)&gPmBakeupSt, 0x0, sizeof(DRV_NV_PM_TYPE));
	memset((void*)&gPmCountSt, 0x0, sizeof(T_PM_COUNT_ST));
	memset((void*)&gPmErrorSt, 0x0, sizeof(T_PM_ERROR_ST));
	memset((void*)&gPmNvSt, 0x0, sizeof(DRV_NV_PM_TYPE));
	memset((void*)PWR_SRAM_DEBUG_ADDR, 0x0, PWR_SRAM_DEBUG_SIZE);

    stamp_value_init();

	gPmSt.u32SleepFlag = 0;
	pm_wakelock_init();

	pm_nv_init();
	pm_config_init();

	pm_mail = osMailCreate(osMailQ(pm_mail), NULL);

	thread_pm_id = osThreadCreate (osThread (thread_pm), NULL);
	if (thread_pm_id == NULL)
	{
		printk("thread_pm create err\n");
	}
	pm_ipc_init();

	pm_wsrc_init();
    pm_wsrc_set_init();
}

static void pm_nv_init(void)
{
	u32 ret = 0;
	ret = bsp_nvm_read(NV_ID_DRV_PM, (u8 *)&gPmNvSt, sizeof(DRV_NV_PM_TYPE));
	if(ret != NV_OK)
	{
		printk("pm nv err\n");
	}
    ret = bsp_nvm_read(NV_ID_DRV_DRX_DELAY, (u8 *)&gNvDrxDelaySt, sizeof(DRV_DRX_DELAY_STRU));
    if(ret != NV_OK)
    {
        printk("pm delay nv err\n");
        memset((void*)&gNvDrxDelaySt, 0x0, sizeof(DRV_DRX_DELAY_STRU));
    }
}

static void pm_ipc_init(void)
{
	s32 ret = 0;
	s32 err_code = 0;

	ret = bsp_ipc_int_connect(IPC_MCU_INT_SRC_ACPU_PD, IntIpcAcoreHandler, 0);
	if(ret != OK)
	{
		err_code = 0x01;
	}

	ret = bsp_ipc_int_enable(IPC_MCU_INT_SRC_ACPU_PD);
	if(ret != OK)
	{
		err_code |= 0x02;
	}

	ret = bsp_ipc_int_connect(IPC_MCU_INT_SRC_CCPU_PD, IntIpcCcoreHandler, 0);
	if(ret != OK)
	{
		err_code |= 0x04;
	}

	ret = bsp_ipc_int_enable(IPC_MCU_INT_SRC_CCPU_PD);
	if(ret != OK)
	{
		err_code |= 0x08;
	}

	ret = bsp_ipc_int_connect(IPC_MCU_INT_SRC_HIFI_PD, IntIpcHiFiHandler, 0);
	if(ret != OK)
	{
		err_code |= 0x10;
	}

	ret = bsp_ipc_int_enable(IPC_MCU_INT_SRC_HIFI_PD);
	if(ret != OK)
	{
		err_code |= 0x20;
	}

	if (err_code)
	{
		printk("pm_ipc_init_err:0x%x\n", err_code);
	}
}

static void IntIpcAcoreHandler(u32 irq)
{
	T_PM_MAIL  *smail;

	smail = osMailCAlloc(pm_mail, 0);
    if(!smail)
    {
        printk("pm IpcA %s", strMailAllocFail);
        return;
    }
	smail->type = PM_TYEP_ACORE_SLEEP;
	osMailPut(pm_mail, smail);
}

static void IntIpcCcoreHandler(u32 irq)
{
	T_PM_MAIL  *smail;

	smail = osMailCAlloc(pm_mail, 0);
    if(!smail)
    {
        printk("pm IpcC %s", strMailAllocFail);
        return;
    }
	smail->type = PM_TYEP_CCORE_SLEEP;
	osMailPut(pm_mail, smail);
}

static void IntIpcHiFiHandler(u32 irq)
{
	T_PM_MAIL  *smail;

	smail = osMailCAlloc(pm_mail, 0);
    if(!smail)
    {
        printk("pm IpcH %s", strMailAllocFail);
        return;
    }
	smail->type = PM_TYEP_HIFI_SLEEP;
	osMailPut(pm_mail, smail);
}

irqreturn_t IntAcoreHandler(int irq, void* data)
{
	T_PM_MAIL  *smail;
    u32 this_irq = 0;
    this_irq = get_irq();

    dump_int_enter(this_irq);
    gPmCountSt.Acore.WakeIrq = this_irq;

	pm_appa9_nvic_disable();

	if(gPmCountSt.u32PrintIrqWsrcFlag)
	{
	    print_acore_wsrc();
	}

	smail = osMailCAlloc(pm_mail, 0);
    if(!smail)
    {
        printk("pm A wake %s", strMailAllocFail);
        return IRQ_NONE;
    }
	smail->type = PM_TYEP_ACORE_WAKE;
	osMailPut(pm_mail, smail);

    dump_int_exit(this_irq);

	return IRQ_HANDLED;
}

irqreturn_t IntCcoreHandler(int irq, void* data)
{
	T_PM_MAIL  *smail;
    u32 tmp = 0;
    u32 this_irq = 0;
    this_irq = get_irq();

    dump_int_enter(this_irq);
    gPmCountSt.Ccore.WakeIrq = this_irq;

	pm_mdma9_nvic_disable();

	if(gPmCountSt.u32PrintIrqWsrcFlag)
	{
	    print_ccore_wsrc();
	}
    tmp = readl(PM_SHM_TIMESTAMP_ADDR);
    if(tmp == 1)
    {
        writel(m3_pm_stamps->before_dpm_suspend, PM_SHM_TIMESTAMP_ADDR + 0x10);
        writel(m3_pm_stamps->after_dpm_suspend, PM_SHM_TIMESTAMP_ADDR + 0x14);
        writel(m3_pm_stamps->after_dfs_bak, PM_SHM_TIMESTAMP_ADDR + 0x18);
        
        writel(m3_pm_stamps->buck3off.before_sram_retention, PM_SHM_TIMESTAMP_ADDR + 0x1C);
        writel(m3_pm_stamps->buck3off.after_sram_out_retention, PM_SHM_TIMESTAMP_ADDR + 0x20);
        writel(m3_pm_stamps->buck3off.no_boot_not_ddr_restore, PM_SHM_TIMESTAMP_ADDR + 0x24);
        
        writel(m3_pm_stamps->buck3on.before_sram_retention, PM_SHM_TIMESTAMP_ADDR + 0x28);
        writel(m3_pm_stamps->buck3on.after_sram_out_retention, PM_SHM_TIMESTAMP_ADDR + 0x2C);
        writel(m3_pm_stamps->buck3on.no_boot_not_ddr_restore, PM_SHM_TIMESTAMP_ADDR + 0x30);
        
        writel(m3_pm_stamps->before_dpm_resume, PM_SHM_TIMESTAMP_ADDR + 0x34);
        writel(m3_pm_stamps->after_dpm_resume, PM_SHM_TIMESTAMP_ADDR + 0x38);
        writel(bsp_get_slice_value(), PM_SHM_TIMESTAMP_ADDR + 0x3C);
    }

	smail = osMailCAlloc(pm_mail, 0);
    if(!smail)
    {
        printk("pm C wake %s", strMailAllocFail);
        return IRQ_NONE;
    }
	smail->type = PM_TYEP_CCORE_WAKE;
	osMailPut(pm_mail, smail);

    dump_int_exit(this_irq);

	return IRQ_HANDLED;
}

irqreturn_t IntHiFiHandler(int irq, void* data)
{
	T_PM_MAIL  *smail;
    u32 this_irq = 0;
    this_irq = get_irq();

    dump_int_enter(this_irq);
    gPmCountSt.HiFi.WakeIrq = this_irq;

	pm_hifi_nvic_disable();

	if(gPmCountSt.u32PrintIrqWsrcFlag)
	{
		printk("%s irq=%d\n", __FUNCTION__, this_irq);
	}

	smail = osMailCAlloc(pm_mail, 0);
    if(!smail)
    {
        printk("pm H wake %s", strMailAllocFail);
        return IRQ_NONE;
    }
	smail->type = PM_TYEP_HIFI_WAKE;
	osMailPut(pm_mail, smail);

    dump_int_exit(this_irq);

	return IRQ_HANDLED;
}


/* pmÁ÷³Ì */
static void thread_pm (void const *arg)
{
	T_PM_MAIL  *rmail;
	osEvent  evt;
	int irqlock;
    
    /* coverity[INFINITE_LOOP] */
    /* coverity[no_escape] */
	for(;;)
	{
		/*lint --e{569 } */
		evt = osMailGet(pm_mail, osWaitForever);        // wait for mail
		if (evt.status == osEventMail)
		{
      	    rmail = evt.value.p;
			local_irq_save(irqlock);

			/* votemap bit 1:no sleep     0:sleep */
			//printk("\r\nthread_pm get mail : 0x%x\n", rmail->type);
			switch(rmail->type)
			{
				case PM_TYEP_ACORE_SLEEP:
					if(pm_is_wake_lock(PM_PWR_VOTE_ACORE))
					{
						pm_wake_unlock(PM_PWR_VOTE_ACORE);
                        pm_acore_sleep();
					}
					break;
				case PM_TYEP_CCORE_SLEEP:
					if(pm_is_wake_lock(PM_PWR_VOTE_CCORE))
					{
						pm_wake_unlock(PM_PWR_VOTE_CCORE);
						pm_ccore_sleep();
					}
					break;
				case PM_TYEP_HIFI_SLEEP:
					if(pm_is_wake_lock(PM_PWR_VOTE_HIFI))
					{
						pm_wake_unlock(PM_PWR_VOTE_HIFI);
                        pm_hifi_sleep();
					}
					break;
#if 0
				case PM_TYEP_ASET_WSRC:
					/*pm_appa9_wsrc_set(rmail->addr);*/
					break;
#endif
				case PM_TYEP_CSET_WSRC:
					pm_mdma9_wsrc_set(rmail->addr);
					break;
				case PM_TYEP_ACORE_WAKE:
					if(!(pm_is_wake_lock(PM_PWR_VOTE_ACORE)) )
					{
						pm_wake_lock(PM_PWR_VOTE_ACORE);
                        pm_acore_wake();
					}
					break;
				case PM_TYEP_CCORE_WAKE:
					if(!(pm_is_wake_lock(PM_PWR_VOTE_CCORE)) )
					{
					    pm_dfs_bak();
						pm_wake_lock(PM_PWR_VOTE_CCORE);
                        pm_ccore_wake();
					}
					break;
				case PM_TYEP_HIFI_WAKE:
					if(!(pm_is_wake_lock(PM_PWR_VOTE_HIFI)) )
					{
						pm_wake_lock(PM_PWR_VOTE_HIFI);
                        pm_hifi_wake();
					}
					break;
#if 0
				case PM_TYEP_AUNSET_WSRC:
					/*pm_appa9_wsrc_unset(rmail->addr);*/
					break;
#endif
				case PM_TYEP_CUNSET_WSRC:
					pm_mdma9_wsrc_unset(rmail->addr);
					break;
				default:
					break;
			}
			local_irq_restore(irqlock);
			osMailFree(pm_mail, rmail);                      // free memory allocated for mail
		}
		else
		{
			printk("thread_pm no mail\n");
		}
	}
}
void pm_wakelock_init(void)
{
	gPmSt.u32VoteMap = 0xFFFFFFFF;
	gPmSt.u32VoteMask = PM_SLEEP_VOTE_MASK;
}
void pm_wake_lock(T_PM_PWR_VOTE vote)
{
    gPmSt.u32VoteMap |= (0x1 << vote);
}
void pm_wake_unlock(T_PM_PWR_VOTE vote)
{
    gPmSt.u32VoteMap &= ~(0x1 << vote);
}
u32 pm_is_wake_lock(T_PM_PWR_VOTE vote)
{
    return gPmSt.u32VoteMap & (0x1 << vote);
}

u32 pm_get_deepsleep_status(void)
{
    if((!(gPmSt.u32VoteMap & gPmSt.u32VoteMask)) && (1 == gPmNvSt.deepsleep_flag))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void pm_print_debug(void)
{

	printk("m3_pm_stamps:0x%x\n", (u32)m3_pm_stamps);
	printk("SHM_SYS_BAK:0x%x\n", SHM_BASE_ADDR + SHM_OFFSET_M3PM);

	printk("[flags]\n");
	printk("wfi:%d, sleep:%d\n", gPmNvSt.normalwfi_flag, gPmNvSt.deepsleep_flag);
	printk("buckoff:%d, peridown:%d\n", gPmNvSt.buck3off_flag, gPmNvSt.peridown_flag);
    printk("buckflag a[0x%x]:%d, c[0x%x]:%d\n",&ACORE_BUCK3_ONOFF_FLAG,ACORE_BUCK3_ONOFF_FLAG,&CCORE_BUCK3_ONOFF_FLAG,CCORE_BUCK3_ONOFF_FLAG);
	printk("PwrRegbak:%d\n", gPmCountSt.u32PwrRegbakFlag);
	printk("WakeupDebug:%d\n", gPmCountSt.u32WakeupDebugFlag);
	printk("PrintIrqWsrc:%d\n", gPmCountSt.u32PrintIrqWsrcFlag);
	printk("DebugSleepTime:%d\n", gPmCountSt.u32DebugCanSleepTime);
    printk("RTT_SLEEP[0x%x]:%d\n",(SRAM_BASE_ADDR + SRAM_OFFSET_TLDSP_SHARED),(*(u32*)(SRAM_BASE_ADDR + SRAM_OFFSET_TLDSP_SHARED)));

	printk("[cnt]\n");
	printk("wfi:%d,deep_sleep:%d,McuTimerInt:%d\n", gPmCountSt.u32NormalWfiTimes,
        gPmCountSt.u32DeepSleepTimes, gPmCountSt.u32McuTimerIntTimes);
    printk("buckoff:%d,no_sm:%d, buckon:%d,,no_sm:%d \n", m3_pm_stamps->buck3off.buck3off_cnt, m3_pm_stamps->buck3off.no_sm_cnt,
        m3_pm_stamps->buck3on.buck3on_cnt, m3_pm_stamps->buck3on.no_sm_cnt);
	printk("sleep a:%d,c:%d,hifi:%d,\n", gPmCountSt.Acore.SleepTimes,\
        gPmCountSt.Ccore.SleepTimes, gPmCountSt.HiFi.SleepTimes);
    printk("m3_wakesrc:%d\n", gPmCountSt.Mcore.SleepTimes);

	printk("[err_cnt]\n");
	printk("Dpm_S:%d,Dpm_R:%d\n", gPmErrorSt.u32DpmSuspendErrTimes, gPmErrorSt.u32DpmResumeErrTimes);
	printk("AxiBakeup:%d,AxiRestore:%d\n", gPmErrorSt.u32AxiBakeupErrTimes, gPmErrorSt.u32AxiRestoreErrTimes);

	if(pm_is_wake_lock(PM_PWR_VOTE_ACORE))
	{
		printk("a wake\n");
	}
	else
	{
		printk("a sleep\n");
	}

	if(pm_is_wake_lock(PM_PWR_VOTE_CCORE))
	{
		printk("c wake\n");
	}
	else
	{
		printk("c sleep\n");
	}

	if(pm_is_wake_lock(PM_PWR_VOTE_HIFI))
	{
		printk("h wake\n");
	}
	else
	{
		printk("h sleep\n");
	}

	//pm_print_wsrc();
}

/* wakeup for debug */
/* flag -   0 : send icc to acore, acore lock pm_lock
            1 : send icc to acore, acore unlock
*/
s32 pm_wakeup_acore(enum debug_wake_type flag)
{
	u32 channel_id;
	s32 ret;
    u32 pm_msg;
    u32 msglen;
    
    channel_id = (ICC_CHN_MCORE_ACORE << 16) | MCORE_ACORE_FUNC_WAKEUP;
    pm_msg = flag;
	msglen = sizeof(pm_msg);

	ret = bsp_icc_send(ICC_CPU_APP, channel_id, (u8*)(&pm_msg), msglen);
	if(ret != msglen)/*lint !e737*/
	{
		//printk("PM icc_send_acore error\n");
		return -1;
	}
    return 0;
}
/* flag -   0 : send icc to ccore, ccore lock 
            1 : send icc to ccore, ccore unlock
*/

s32 pm_wakeup_ccore(enum debug_wake_type flag)
{
	u32 channel_id;
	s32 ret;
    u32 pm_msg;
    u32 msglen;
    
    channel_id = (ICC_CHN_MCORE_CCORE << 16) | MCORE_CCORE_FUNC_WAKEUP;
    pm_msg = flag;
	msglen = sizeof(pm_msg);

	ret = bsp_icc_send(ICC_CPU_MODEM, channel_id, (u8*)(&pm_msg), msglen);
	if(ret != msglen)/*lint !e737*/
	{
		return -1;
	}
    return 0;
}

static s32 pm_wsrc_icc_read(u32 id , u32 len, void* context)
{
	s32 ret = 0;
	u8 data[32];
	T_PM_MAIL *smail;

    if(len > 32)
	{
        printk("pm_wsrc_icc_read len err\n");
		return -1;
	}
	
	ret = bsp_icc_read(id, data, len);
	if(len != ret)/*lint !e737*/
	{
		return -1;
	}
	/*lint --e{569 } */
	smail = osMailCAlloc(pm_mail, osWaitForever);
	memcpy(smail, data, len);
	osMailPut(pm_mail, smail);

	return 0;
}


s32 pm_wsrc_set_init(void)
{
	s32 ret;
	u32 channel_id_set = 0;

	/* m3 acore icc */
	channel_id_set = (ICC_CHN_MCORE_ACORE << 16) | MCU_ACORE_WSRC;
	ret = bsp_icc_event_register(channel_id_set, pm_wsrc_icc_read, NULL, (write_cb_func)NULL, (void *)NULL);
	if(ret != ICC_OK)/*lint !e737*/
	{
		return -1;
	}

	/* m3 ccore icc */
	channel_id_set = (ICC_CHN_MCORE_CCORE << 16) | MCU_CCORE_WSRC;
	ret = bsp_icc_event_register(channel_id_set, pm_wsrc_icc_read, NULL, (write_cb_func)NULL, (void *)NULL);
	if(ret != ICC_OK)/*lint !e737*/
	{
		return -1;
	}
	return 0;
}


