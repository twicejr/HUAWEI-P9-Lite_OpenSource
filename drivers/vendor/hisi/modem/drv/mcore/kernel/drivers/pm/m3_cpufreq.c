/*----------------------------------------------------------------------------
 *      balongv7r2 m3 pm
 *----------------------------------------------------------------------------
 *      Name:    pm.C
 *      Purpose: RTX example program
 *----------------------------------------------------------------------------
 *      This code is part of balongv7r2 PWR.
 *---------------------------------------------------------------------------*/

#include "cmsis_os.h"

#include "osl_types.h"
#include "osl_bio.h"
#include "osl_irq.h"
#include <osl_malloc.h>

#include "m3_cpufreq.h"
#include "cpufreq_api.h"
#include "bsp_icc.h"
#include "bsp_hardtimer.h"
#include <bsp_nvim.h>
#include <bsp_pm_om.h>
#include <bsp_version.h>
#include <drv_nv_id.h>
#include <drv_nv_def.h>
static void cpufreq_icc_init(void);
static s32 cpufreq_icc_read_cb(u32 id , u32 len, void* context);
static u32 cpufreq_get_cur_profile(void);
static u32 cpufreq_find_profile(u32 core_type, u32 action, u32 profile);
static void cpufreq_recv_mail(T_CPUFREQ_MAIL  *rmail);
static void thread_cpufreq (void const *arg);

/*lint --e{64, 958} */
osMailQDef(cpufreq_mail, 32, T_CPUFREQ_MAIL);/*lint !e133*/
osMailQId  cpufreq_mail;

osThreadId thread_cpufreq_id;
/*lint --e{133} */
osThreadDef(thread_cpufreq, osPriorityNormal, 1, 512);


T_CPUFREQ_ST g_cpufreq;
int g_cpufreq_msg_flag = 0;
u32 g_set_profile = CPUFREQ_MAX_PROFILE;
u32 g_down_flag_num[2] = {0, 0};
static u32 g_log_last_time_slice = 0;
static struct cpufreq_pm_om_dump *cfq_dump = NULL;
/*lint -e64*/
//u8* g_cpufreq_string1[] = {"acore","ccore","mcore"};
//u8* g_cpufreq_string2[] = {"up","up2dst","down","down2dst"};
void cpufreq_fiq_event_init(void)
{
#if 0
    /* ccpu eventi mast for fiq */
    retValue = readl(0x90000410);
    retValue = retValue &(~(0x3<<10)) ;
    retValue = retValue |(0x2<<10);
    writel(retValue ,0x90000410);
    /* acpu eventi mast for fiq */
    retValue = readl(0x9000040c);
    retValue = retValue &(~(0x3<<10));
    retValue = retValue |(0x2<<10);
    writel(retValue ,0x9000040c);
#endif
}
void cpufreq_cti_unlock(u32 base_addr)
{
    writel(0xC5ACCE55, base_addr + 0xFB0);
    do
    {
        ;
    }while(0x2 == (readl(base_addr + 0xFB4) & 0x2));
}
void cpufreq_cti_lock(u32 base_addr)
{
    writel(0x0, base_addr + 0xFB0);
}

void cpufreq_m3_cti_init(void)
{
    u32 cti_base = CPUFREQ_CTI_BASE;
    if (CHIP_V750 != bsp_get_version_info()->chip_type)
    {
        return;
    }
    //uclock
    cpufreq_cti_unlock(cti_base);
    writel(0x0, cti_base + 0x20);
    writel(0x0, cti_base + 0x24);
    writel(0x0, cti_base + 0x28);
    writel(0x0, cti_base + 0x2C);
    writel(0x0, cti_base + 0x30);
    writel(0x0, cti_base + 0x34);
    writel(0x0, cti_base + 0x38);
    writel(0x0, cti_base + 0x3C);
    writel(0x0, cti_base + 0xA0);
    writel(0x0, cti_base + 0xA8);
    writel(0x0, cti_base + 0xAC);
    writel(0x0, cti_base + 0xB0);
    writel(0x0, cti_base + 0xB4);
    writel(0x0, cti_base + 0xB8);
    writel(0x0, cti_base + 0xBC);
    writel(0x1, cti_base + 0x0);
    //lock
    cpufreq_cti_lock(cti_base);
}

void cpufreq_ccore_cti_init(void)
{
    u32 cti_base_mdm = CPUFREQ_CTI_BASE_MDM;
    if (CHIP_V750 != bsp_get_version_info()->chip_type)
    {
        return;
    }

    cpufreq_cti_unlock(cti_base_mdm);
    //ccore cti init
    writel(0x0, cti_base_mdm + 0x20);
    writel(0x0, cti_base_mdm + 0x24);
    writel(0x0, cti_base_mdm + 0x28);
    writel(0x0, cti_base_mdm + 0x2C);
    writel(0x0, cti_base_mdm + 0x30);
    writel(0x0, cti_base_mdm + 0x34);
    writel(0x0, cti_base_mdm + 0x38);
    writel(0x0, cti_base_mdm + 0x3C);
    writel(0x0, cti_base_mdm + 0xA0);
    writel(0x0, cti_base_mdm + 0xA8);
    writel(0x0, cti_base_mdm + 0xAC);
    writel(0x0, cti_base_mdm + 0xB0);
    writel(0x0, cti_base_mdm + 0xB4);
    writel(0x0, cti_base_mdm + 0xB8);
    writel(0x0, cti_base_mdm + 0xBC);
    writel(0x1, cti_base_mdm + 0xA0);
    writel(0x2, cti_base_mdm + 0xBC);
    writel(0xF, cti_base_mdm + 0x140);
    writel(0x1, cti_base_mdm + 0x0);
    //lock
    cpufreq_cti_lock(cti_base_mdm);
}


void cpufreq_acore_cti_init(void)
{
    u32 cti_base_app = CPUFREQ_CTI_BASE_APP;
    if (CHIP_V750 != bsp_get_version_info()->chip_type)
    {
        return;
    }
    //uclock
    cpufreq_cti_unlock(cti_base_app);

    //acore cti init
    writel(0x0, cti_base_app + 0x20);
    writel(0x0, cti_base_app + 0x24);
    writel(0x0, cti_base_app + 0x28);
    writel(0x0, cti_base_app + 0x2C);
    writel(0x0, cti_base_app + 0x30);
    writel(0x0, cti_base_app + 0x34);
    writel(0x0, cti_base_app + 0x38);
    writel(0x0, cti_base_app + 0x3C);
    writel(0x0, cti_base_app + 0xA0);
    writel(0x0, cti_base_app + 0xA8);
    writel(0x0, cti_base_app + 0xAC);
    writel(0x0, cti_base_app + 0xB0);
    writel(0x0, cti_base_app + 0xB4);
    writel(0x0, cti_base_app + 0xB8);
    writel(0x0, cti_base_app + 0xBC);
    writel(0x1, cti_base_app + 0xA0);
    writel(0x2, cti_base_app + 0xBC);
    writel(0xF, cti_base_app + 0x140);
    writel(0x1, cti_base_app + 0x0);

    //lock
    cpufreq_cti_lock(cti_base_app);
}

void cpufreq_cti_init(void)
{
    if (CHIP_V750 != bsp_get_version_info()->chip_type)
    {
        return;
    }
    cpufreq_m3_cti_init();
    cpufreq_acore_cti_init();
}


void cpufreq_init(void)
{
	u32 retValue = 0;
	u32 i = 0;
	ST_PWC_DFS_STRU DfsSwitc_nv = {0};

    amon_init_dfs();

    dfs_ddrc_calc();
	//dfs_to_max();
	memset(&g_cpufreq, 0x0, sizeof(T_CPUFREQ_ST));

	/* 初始化记录的上一次需要调的频率值 */
	g_cpufreq.maxprof = CPUFREQ_MAX_PROFILE;
	g_cpufreq.minprof = CPUFREQ_MIN_PROFILE;
	g_cpufreq.curprof = cpufreq_get_cur_profile();
	for (i = 0; i < CPUFREQ_NUM; i++)
	{
        g_cpufreq.coreminlimit[i] = CPUFREQ_MIN_PROFILE;
	}
    M3_CUR_CPUFREQ_PROFILE = g_cpufreq.curprof;
    M3_MAX_CPUFREQ_PROFILE = g_cpufreq.maxprof;
    M3_MIN_CPUFREQ_PROFILE = g_cpufreq.minprof;
    M3_CPUFREQ_DOWN_FLAG(0) = 0;
    M3_CPUFREQ_DOWN_FLAG(1) = 0;
    cpufreq_cti_init();
	cpufreq_mail = osMailCreate(osMailQ(cpufreq_mail), NULL);

	thread_cpufreq_id = osThreadCreate (osThread (thread_cpufreq), NULL);
	if (thread_cpufreq_id == NULL)
	{
		M3CPUFREQ_PRINT("thread cret err\n");
	}
	/*pm om dump init*/
	cfq_dump = (struct cpufreq_pm_om_dump *)bsp_pm_dump_get(PM_OM_CPUF, sizeof(struct cpufreq_pm_om_dump) * (CPUFREQ_MAX_PROFILE + 1));
	for (retValue = 0; (retValue <= CPUFREQ_MAX_PROFILE) && (NULL != cfq_dump); retValue++)
    {
		cfq_dump[retValue].profile = retValue;
		cfq_dump[retValue].timeslice = 0;
    }
	/* icc channel */
	cpufreq_icc_init();
	
	retValue = bsp_nvm_read(NV_ID_DRV_NV_DFS_SWITCH,(u8*)&DfsSwitc_nv,sizeof(ST_PWC_DFS_STRU));
    if (NV_OK != retValue)
    {
    	M3CPUFREQ_PRINT("read nv failed use def val %d\n", retValue);
		DfsSwitc_nv.reserved = CPUFREQ_MAX_PROFILE;
    }

	g_set_profile = DfsSwitc_nv.reserved;
	g_log_last_time_slice = bsp_get_slice_value();
	M3CPUFREQ_PRINT("dfs init ok\n");
}

inline void cpufreq_dump_pro_timeslice(u32 cur, u32 new)
{
	u32 cur_timer = bsp_get_slice_value();
	/*every profile total timeslice*/
	if ((NULL != cfq_dump) && (cur <= CPUFREQ_MAX_PROFILE) &&(cfq_dump[cur].profile == cur))
	{
		cfq_dump[cur].timeslice += get_timer_slice_delta(g_log_last_time_slice, cur_timer);
		g_log_last_time_slice = cur_timer;
	}
}

static void cpufreq_icc_init(void)
{
	s32 ret;
	u32 channel_id_set = 0;

	/* m3 acore icc */
	channel_id_set = (ICC_CHN_MCORE_ACORE << 16) | MCU_ACORE_CPUFREQ;
	ret = bsp_icc_event_register(channel_id_set, cpufreq_icc_read_cb, NULL, (write_cb_func)NULL, (void *)NULL);
	if(ret != ICC_OK)
	{
		M3CPUFREQ_PRINT("iccinit1err\n");
	}

	channel_id_set = (ICC_CHN_MCORE_CCORE << 16) | MCU_CCORE_CPUFREQ;
	ret = bsp_icc_event_register(channel_id_set, cpufreq_icc_read_cb, NULL, (write_cb_func)NULL, (void *)NULL);
	if(ret != ICC_OK)
	{
		M3CPUFREQ_PRINT("iccinit2err\n");
	}
}

static s32 cpufreq_icc_read_cb(u32 id , u32 len, void* context)
{
	s32 ret = 0;
	u8 data[32];
	T_CPUFREQ_MAIL *smail;

	if((len == 0) || (len > 32))
	{
		M3CPUFREQ_PRINT("readcb len is 0\n");
        return -1;
	}

	ret = bsp_icc_read(id, data, len);
	if(len != ret)/*lint !e737*/
	{
		M3CPUFREQ_PRINT("readcb err\n");
		return -1;
	}
	/*lint --e{569} */
	smail = osMailCAlloc(cpufreq_mail, osWaitForever);
	memcpy(smail, data, len);
	osMailPut(cpufreq_mail, smail);
	
	return 0;
}

static u32 cpufreq_get_cur_profile(void)
{
	u32 tmp = 0;

	tmp = dfs_get_profile();
	if(tmp == CPUFREQ_INVALID_PROFILE)
	{
		M3CPUFREQ_PRINT("cur pro invalid\n");
		return 0;
	}
	return tmp;
}

static u32 cpufreq_down_1_step(u32 curprof, u32 core_type)
{
    u32 i = 0;
    u32 dstprof = CPUFREQ_INVALID_PROFILE;

    if(curprof <= g_cpufreq.minprof)
	{
		M3CPUFREQ_PRINT("already min pro\n");
		g_cpufreq.todo[core_type].flag = 0;
		M3_CPUFREQ_DOWN_FLAG(core_type) = 0;
       return dstprof;
	}
	else
	{
		g_cpufreq.todo[core_type].flag = 1;
		M3_CPUFREQ_DOWN_FLAG(core_type) = 1;
		g_cpufreq.todo[core_type].profile = curprof - 1;
		M3_CPUFREQ_DOWN_PROFILE(core_type) = curprof - 1;
		for(i = 0; i < CPUFREQ_NUM; i++)
		{
            /* 没有降频需求且没有睡眠，频率降不了 */
			if((g_cpufreq.todo[i].flag == 0)&&(g_cpufreq.todo[i].sleepflag == 0))
			{
				return dstprof;
			}
		}
		dstprof = curprof - 1;
		for(i = 0; i < CPUFREQ_NUM; i++)
		{
            /* 频率降到目标及以下 或者睡眠了，降频需求清空*/
			if((dstprof <= g_cpufreq.todo[i].profile)||(g_cpufreq.todo[i].sleepflag == 1))
			{
				g_cpufreq.todo[i].flag = 0;
				M3_CPUFREQ_DOWN_FLAG(i) = 0;
			}
		}
	}
    return dstprof;
}
static u32 cpufreq_down_to_dst(u32 profile, u32 curprof, u32 core_type)
{
    u32 i = 0;
    u32 tmp = 0;
    u32 dstprof = CPUFREQ_INVALID_PROFILE;

    if((profile < g_cpufreq.minprof) || (curprof <= profile))
	{
		M3CPUFREQ_PRINT("cpufreq down  dst: %d, cur:%d, max: %d\n", profile, curprof, g_cpufreq.maxprof);
		g_cpufreq.todo[core_type].flag = 0;
		M3_CPUFREQ_DOWN_FLAG(core_type) = 0;
		return dstprof;
	}
	else
	{
		g_cpufreq.todo[core_type].flag = 1;
		M3_CPUFREQ_DOWN_FLAG(core_type) = 1;
		g_cpufreq.todo[core_type].profile = profile;
		M3_CPUFREQ_DOWN_PROFILE(core_type) = profile;
		for(i = 0; i < CPUFREQ_NUM; i++)
		{
			/* 没有降频需求且没有睡眠，频率降不了 */
			if((g_cpufreq.todo[i].flag == 0)&&(g_cpufreq.todo[i].sleepflag == 0))
			{
				return dstprof;
			}
		}
		for(i = 0; i < CPUFREQ_NUM; i++)
		{
			if((tmp < g_cpufreq.todo[i].profile)&&(g_cpufreq.todo[i].sleepflag == 0))
			{
				tmp  = g_cpufreq.todo[i].profile;
			}
		}
		dstprof = tmp;
		for(i = 0; i < CPUFREQ_NUM; i++)
		{
			/* 频率降到目标及以下 或者睡眠了，降频需求清空*/
			if((dstprof <= g_cpufreq.todo[i].profile)||(g_cpufreq.todo[i].sleepflag == 1))
			{
				g_cpufreq.todo[i].flag = 0;
				M3_CPUFREQ_DOWN_FLAG(i) = 0;
			}
		}
	}
    return dstprof;
}

static u32 cpufreq_get_min_limit_pro(u32 core_type, u32 profile)
{
    u32 i = 0;
    u32 max_pro = 0;
    g_cpufreq.coreminlimit[core_type] = profile;
	for(i = 0; i < CPUFREQ_NUM; i++)
	{
		if (g_cpufreq.coreminlimit[i] > max_pro)
		{
		    max_pro = g_cpufreq.coreminlimit[i];
	    }
	}
    return max_pro;
}

static u32 cpufreq_find_profile(u32 core_type, u32 action, u32 profile)
{
	u32 curprof = CPUFREQ_INVALID_PROFILE;
	u32 dstprof = CPUFREQ_INVALID_PROFILE;

	curprof = cpufreq_get_cur_profile();
	switch(action)
	{
		case 0://升
			g_cpufreq.todo[core_type].flag = 0;
			M3_CPUFREQ_DOWN_FLAG(core_type) = 0;
			if(curprof < g_cpufreq.maxprof)
			{
				dstprof = curprof + 1;
			}
			else
			{
				M3CPUFREQ_PRINT("already max pro\n");
				dstprof = CPUFREQ_INVALID_PROFILE;/* invalid */
			}
			break;
		case 1://升目标
			g_cpufreq.todo[core_type].flag = 0;
			M3_CPUFREQ_DOWN_FLAG(core_type) = 0;
			if((curprof < profile) && (profile <= g_cpufreq.maxprof))
			{
				dstprof = profile;
			}
			else
			{
				M3CPUFREQ_PRINT("cpufreq up  dst: %d, cur:%d, max: %d\n", profile, curprof, g_cpufreq.maxprof);
				dstprof = CPUFREQ_INVALID_PROFILE;/* invalid or not change*/
			}
			break;
		case 2://降
			dstprof = cpufreq_down_1_step(curprof, core_type);
			break;
		case 3:
			dstprof = cpufreq_down_to_dst(profile, curprof, core_type);
			break;
		case 4:
			if(profile > g_cpufreq.maxprof)
			{
                M3CPUFREQ_PRINT("1pro not in the range\n");

			}
			else
			{
				g_cpufreq.minprof = cpufreq_get_min_limit_pro(core_type, profile);
                M3_MIN_CPUFREQ_PROFILE = g_cpufreq.minprof;
				if(curprof < g_cpufreq.minprof)
				{
					dstprof = g_cpufreq.minprof;
				}
				else
				{
					dstprof = CPUFREQ_INVALID_PROFILE;
				}
			}
			break;
		case 5:
			if((profile > CPUFREQ_MAX_PROFILE)||(profile < g_cpufreq.minprof))
			{
                M3CPUFREQ_PRINT("2pro not in the range\n");
			}
			else
			{
				g_cpufreq.maxprof = profile;
                M3_MAX_CPUFREQ_PROFILE = profile;
				if(curprof > profile)
				{
					dstprof = profile;
				}
				else
				{
					dstprof = CPUFREQ_INVALID_PROFILE;
				}
			}
			break;
		default :
			break;
	}
	return dstprof;
}
#if 0
static void cpufreq_set_profile_debug(u32 action, u32 profile)
{
	int irqlock = 0;
	u32 i = 0;

	local_irq_save(irqlock);
	switch(action)
	{
		case 0:
			if((profile > g_cpufreq.maxprof) || (profile < g_cpufreq.minprof) || (profile == g_cpufreq.curprof))
			{
				M3CPUFREQ_PRINT("case 0 input error\n");
				local_irq_restore(irqlock);
				return;
			}
			if((!g_cpufreq.debuglockflag)&&(!g_cpufreq.ccorelockflag))
        	{
        		dfs_set_profile(profile);
        		g_cpufreq.curprof = profile;
                M3_CUR_CPUFREQ_PROFILE = profile;
        	}
            else
            {
                M3CPUFREQ_PRINT("case 0 cpufreq lock\n");
            }
			break;
		case 1:
			for(i = 0; i < CPUFREQ_NUM; i++)
			{
				g_cpufreq.todo[i].flag = 0;
				M3_CPUFREQ_DOWN_FLAG(i) = 0;
			}
			g_cpufreq.debuglockflag = 1;
			break;
		case 2:
			for(i = 0; i < CPUFREQ_NUM; i++)
			{
				g_cpufreq.todo[i].flag = 0;
				M3_CPUFREQ_DOWN_FLAG(i) = 0;
			}
			g_cpufreq.debuglockflag = 0;
			break;
		default:
			break;
	}
	local_irq_restore(irqlock);
}
#endif

static void cpufreq_set_ccorelockflag(u32 action)
{
    int irqlock = 0;

    local_irq_save(irqlock);
    switch(action)
	{
        case 0:
            g_cpufreq.ccorelockflag = 1;
            break;
        case 1:
            g_cpufreq.ccorelockflag = 0;
            break;
        default:
            break;
    }
    local_irq_restore(irqlock);
}

void cpufreq_change_ccorelockflag(u32 flag)
{
    g_cpufreq.ccorelockflag = flag;
}

void cpufreq_set_sleepflag(u32 core_type, u32 flag)
{
    g_cpufreq.todo[core_type].sleepflag = flag;
    g_cpufreq.todo[core_type].flag = flag;
    
    if (M3_CPUFREQ_DOWN_FLAG(0))
    {
		g_down_flag_num[0]++;
    }
 	 M3_CPUFREQ_DOWN_FLAG(0) = 0;
     if (M3_CPUFREQ_DOWN_FLAG(1))
    {
		g_down_flag_num[1]++;
    }
    M3_CPUFREQ_DOWN_FLAG(1) = 0;
}

static void cpufreq_recv_mail(T_CPUFREQ_MAIL  *rmail)
{
	int irqlock = 0;
	u32 dstprof = 0;
	struct cpufreq_pm_om_log cfq_log = {0};
	if(rmail == NULL)
	{
		M3CPUFREQ_PRINT("rmail input error\n");
		return;
	}
	if (g_cpufreq_msg_flag)
    	M3CPUFREQ_PRINT("mtype:%d core:%d act:%d pro=%d\n", rmail->msgtype, rmail->coretype, rmail->action, rmail->profile);
	bsp_pm_log_type(PM_OM_CPUF, 1, sizeof(T_CPUFREQ_MAIL), rmail);
	switch(rmail->msgtype)
	{
		case 1:
			local_irq_save(irqlock);
			if((!g_cpufreq.debuglockflag)&&(!g_cpufreq.ccorelockflag))
			{
				dstprof = cpufreq_find_profile(rmail->coretype, rmail->action, rmail->profile);
				if(dstprof != CPUFREQ_INVALID_PROFILE)
				{
					cfq_log.cur_profile = g_cpufreq.curprof;
					cfq_log.target_profile = dstprof;
					cfq_log.cur_timeslice = bsp_get_slice_value();
					
					dfs_set_profile(dstprof);
					g_cpufreq.curprof = dstprof;
                    M3_CUR_CPUFREQ_PROFILE = dstprof;

					cfq_log.dst_timeslice = bsp_get_slice_value();
					cfq_log.max_limit = g_cpufreq.maxprof;
					cfq_log.min_limit = g_cpufreq.minprof;
                    bsp_pm_log_type(PM_OM_CPUF, 0, sizeof(struct cpufreq_pm_om_log), &cfq_log);
				}
			}
            else
            {
                M3CPUFREQ_PRINT("cpufreq lock\n");
            }
			local_irq_restore(irqlock);
			break;
#if 0
		case 2:
			cpufreq_set_profile_debug(rmail->action, rmail->profile);
			break;
#endif
        case 5:
            cpufreq_set_ccorelockflag(rmail->action);
            break;
		default:
			M3CPUFREQ_PRINT("msgtype error\n");
			break;
	}
}

static void thread_cpufreq (void const *arg)
{
	T_CPUFREQ_MAIL  *rmail = NULL;
	osEvent  evt;
    /* coverity[INFINITE_LOOP] */
    /* coverity[no_escape] */
	for(;;)
	{
		/*lint --e{569} */
		evt = osMailGet(cpufreq_mail, osWaitForever);
		if (evt.status == osEventMail)
		{
			rmail = evt.value.p;
			cpufreq_recv_mail(rmail);
			osMailFree(cpufreq_mail, rmail);
		}
	}
}
void cpufreq_print_debug(int flag)
{
	g_cpufreq_msg_flag = flag;
	printk("def max pro:%d\n", CPUFREQ_MAX_PROFILE);
	printk("def min pro:%d\n", CPUFREQ_MIN_PROFILE);
	printk("cur max pro:%d\n", g_cpufreq.maxprof);
	printk("cur min pro:%d\n", g_cpufreq.minprof);
	printk("acpu min pro:%d, ccpu min pro:%d\n", 
	g_cpufreq.coreminlimit[CPUFREAQ_ACORE],g_cpufreq.coreminlimit[CPUFREAQ_CCORE]);
	printk("cur pro:%d\n", g_cpufreq.curprof);
}

