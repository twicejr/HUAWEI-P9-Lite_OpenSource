/*----------------------------------------------------------------------------
 *      k3v3 m3 modem cpufreq
 *----------------------------------------------------------------------------
 *      Name:    m3_cpufreq_modem.c
 *----------------------------------------------------------------------------
 *      This code is part of k3v3 modem cpufreq.
 *---------------------------------------------------------------------------*/
#include <ARMCM3.h>
#include <cmsis_os.h>
#include <osl_common.h>
#include <soc_memmap_m3.h>
#include <hi_base.h>
#include <hi_syssc.h>
#include <log.h>
#include <bsp_icc.h>
#include <m3_modem.h>
#include <m3_cpufreq_modem.h>
#include <bsp_reset.h>

__ao_data T_CPUFREQ_ST g_cpufreq;

__ao_data T_CPUFREQ_PROFILE gCpufrqProfile[CPUFREQ_MAX_PROFILE+1] =
    {{0, 0x0010},
     {1, 0x1210},
     {1, 0x0110},
     //{0, 0x1300},
     //{0, 0x1200},
     {0, 0x1100},
     //{0, 0x0300},
     {0, 0x0200},
     //{0, 0x0100},
     {1, 0x2500},
     {1, 0x2400},
     {1, 0x2300},
     {1, 0x1500},
     {1, 0x1400},
     {1, 0x1300},
     {1, 0x0500},
     {1, 0x0400},
     {1, 0x0300}};

/* pll only support 666M and 400M */
__ao_data T_CPUFREQ_PLL_CONFIG gCpufrqPll[CPUFREQ_MAX_PLL + 1] =
     {{0xB03E04, 0x800000},
	  {0xA04504, 0x600000}};

/* dfs */
void pm_dfs_bak(u32 profile)
{
    u32 cur = M3_CUR_CPUFREQ_PROFILE;
    u32 max = M3_MAX_CPUFREQ_PROFILE;

    if(cur < max)
    {
        dfs_config_reg(cur, profile);
        g_cpufreq.curprof = profile;
        M3_CUR_CPUFREQ_PROFILE = profile;
    }
}

void dfs_set_profile(u32 profile)
{
	dfs_config_reg(g_cpufreq.curprof, profile);
}

u32 dfs_get_profile(void)
{
	u32 profile = CPUFREQ_INVALID_PROFILE;
	T_CPUFREQ_PLL_CONFIG curconf;
	u32 invalid = 0xFFFFFFFF;
	u32 curpll = invalid;
	u32 curclkdiv = 0;
	u32 i = 0;

	/* find right pll */
	curconf.a9pllcfg0 = readl(HI_SYSCTRL_BASE_ADDR + HI_CRG_A9PLL_CFG0_OFFSET);
	curconf.a9pllcfg1 = readl(HI_SYSCTRL_BASE_ADDR + HI_CRG_A9PLL_CFG1_OFFSET);

	for(i = 0;i <= CPUFREQ_MAX_PLL;i++)
	{
		if((curconf.a9pllcfg0&0x3FFFFFC) == gCpufrqPll[i].a9pllcfg0)
		{
			if((curconf.a9pllcfg1&0xFFFFFF) == gCpufrqPll[i].a9pllcfg1)
			{
				curpll = i;
				break;
			}
		}
	}
	if(curpll == invalid)
	{
		MODEM_CPUFREQ_PRINT("dfs_get_profile pll error\n");
		return CPUFREQ_INVALID_PROFILE;
	}

	/* find right profile */
	curclkdiv = readl(HI_SYSCTRL_BASE_ADDR + HI_CRG_CLKDIV2_OFFSET);

	for(i = 0;i <= CPUFREQ_MAX_PROFILE;i++)
	{
		if(curpll == gCpufrqProfile[i].pll)
		{
			if((curclkdiv&0x77F0) == gCpufrqProfile[i].clkdiv)
			{
				profile = i;
				break;
			}
		}
	}

	return profile;
}
void dfs_config_reg(u32 cur, u32 new)
{
	u32 tmp = 0;
	u32 curpll = 0;
	u32 newpll = 0;
    u32 flag = 0;

    curpll = gCpufrqProfile[cur].pll;
	newpll = gCpufrqProfile[new].pll;

    if(curpll == newpll)
    {
        flag = 1;
        goto step11;
    }

	/* 1 */
	tmp = readl(HI_SYSCTRL_BASE_ADDR + HI_CRG_CLKDIV2_OFFSET);
	tmp &= ~(0x7<<16);
    tmp |= 0x4<<16;
	writel(tmp, HI_SYSCTRL_BASE_ADDR + HI_CRG_CLKDIV2_OFFSET);

	/* 2 */
	tmp = readl(HI_SYSCTRL_BASE_ADDR + HI_CRG_A9PLL_CFG1_OFFSET);
	tmp &= ~(0x1<<26);
	writel(tmp, HI_SYSCTRL_BASE_ADDR + HI_CRG_A9PLL_CFG1_OFFSET);

	/* 3 */

	/* 4 */
	tmp = readl(HI_SYSCTRL_BASE_ADDR + HI_CRG_A9PLL_CFG0_OFFSET);
	tmp &= ~(0x3);
    tmp |= 0x2;
	writel(tmp, HI_SYSCTRL_BASE_ADDR + HI_CRG_A9PLL_CFG0_OFFSET);

	/* 5 */
    tmp = readl(HI_SYSCTRL_BASE_ADDR + HI_CRG_A9PLL_CFG0_OFFSET);
    tmp &= 0xFC000003;/* bit[25:2] = 0 */
    tmp |= gCpufrqPll[newpll].a9pllcfg0;
    writel(tmp, HI_SYSCTRL_BASE_ADDR + HI_CRG_A9PLL_CFG0_OFFSET);

    tmp = readl(HI_SYSCTRL_BASE_ADDR + HI_CRG_A9PLL_CFG1_OFFSET);
    tmp &= 0xFF000000;/* bit[23:0] = 0 */
    tmp |= gCpufrqPll[newpll].a9pllcfg1;
    writel(tmp, HI_SYSCTRL_BASE_ADDR + HI_CRG_A9PLL_CFG1_OFFSET);

	/* 6 */
    tmp = readl(HI_SYSCTRL_BASE_ADDR + HI_CRG_A9PLL_CFG0_OFFSET);
	tmp &= ~(0x3);
    tmp |= 0x1;
	writel(tmp, HI_SYSCTRL_BASE_ADDR + HI_CRG_A9PLL_CFG0_OFFSET);

	/* 7 */

	/* 8 */
	do
	{
		tmp = readl(HI_SYSCTRL_BASE_ADDR + HI_CRG_A9PLL_CFG0_OFFSET);
		tmp = (tmp >> 26) & 0x1;
	}while(!tmp);

	/* 9 */
	tmp = readl(HI_SYSCTRL_BASE_ADDR + HI_CRG_A9PLL_CFG1_OFFSET);
	tmp |= (0x1<<26);
	writel(tmp, HI_SYSCTRL_BASE_ADDR + HI_CRG_A9PLL_CFG1_OFFSET);

	/* 10 */

	/* 11 */
step11:
    tmp = readl(HI_SYSCTRL_BASE_ADDR + HI_CRG_CLKDIV2_OFFSET);
    tmp &= 0xFFFF880F;/* bit[14:12  10:4] = 0 */
    tmp |= gCpufrqProfile[new].clkdiv;
    writel(tmp, HI_SYSCTRL_BASE_ADDR + HI_CRG_CLKDIV2_OFFSET);
    if(flag == 1)
    {
        return;
    }

	/* 12 */
    tmp = readl(HI_SYSCTRL_BASE_ADDR + HI_CRG_CLKDIV2_OFFSET);
    tmp &= ~(0x7<<16);
    tmp |= 0x1<<16;
    writel(tmp, HI_SYSCTRL_BASE_ADDR + HI_CRG_CLKDIV2_OFFSET);
}


/***********************************************/

osMailQDef(cpufreq_mail, 16, T_CPUFREQ_MAIL);
osMailQId  cpufreq_mail;

osThreadId thread_cpufreq_id;
osThreadDef(thread_cpufreq, osPriorityNormal, 1, 512);

void cpufreq_init(void)
{
    u32 ret;
	u32 channel_id_set = 0;
    u32 flag = 0;

    if(get_modem_init_flag() == MODEM_ALREADY_INIT_MAGIC)
    {
        flag = 1;
    }

    if(flag == 0)
    {
    	/* 初始化记录的上一次需要调的频率值 */
    	g_cpufreq.maxprof = CPUFREQ_MAX_PROFILE;
    	g_cpufreq.minprof = CPUFREQ_MIN_PROFILE;
    	g_cpufreq.curprof = cpufreq_get_cur_profile();
        g_cpufreq.ccorelockflag = 0;
        M3_CUR_CPUFREQ_PROFILE = g_cpufreq.curprof;
        M3_MAX_CPUFREQ_PROFILE = g_cpufreq.maxprof;
        M3_MIN_CPUFREQ_PROFILE = g_cpufreq.minprof;
        MODEM_CPUFREQ_PRINT("CUR_PROF addr=0x%x\n", &(M3_CUR_CPUFREQ_PROFILE));
        MODEM_CPUFREQ_PRINT("MAX_PROF addr=0x%x\n", &(M3_MAX_CPUFREQ_PROFILE));
        MODEM_CPUFREQ_PRINT("MIN_PROF addr=0x%x\n", &(M3_MIN_CPUFREQ_PROFILE));
    }

	cpufreq_mail = osMailCreate(osMailQ(cpufreq_mail), NULL);

	thread_cpufreq_id = osThreadCreate (osThread (thread_cpufreq), NULL);
	if (thread_cpufreq_id == NULL)
	{
		MODEM_CPUFREQ_PRINT("thread create err\n");
	}

	/* icc channel */
	channel_id_set = (ICC_CHN_MCORE_CCORE << 16) | MCU_CCORE_CPUFREQ;
	ret = bsp_icc_event_register(channel_id_set, cpufreq_icc_read_cb, NULL, (write_cb_func)NULL, (void *)NULL);
	if(ret != ICC_OK)
	{
		MODEM_CPUFREQ_PRINT("icc register err\n");
	}

    if(flag == 0)
    {
        MODEM_CPUFREQ_PRINT("init ok\n");
    }
}

s32 cpufreq_icc_read_cb(u32 id , u32 len, void* context)
{
	s32 ret = 0;
	T_CPUFREQ_MAIL data;
	T_CPUFREQ_MAIL *smail;

	if((len == 0) || (len > sizeof(T_CPUFREQ_MAIL)))
	{
		MODEM_CPUFREQ_PRINT("readcb len is err\n");
        return -1;
	}

	ret = bsp_icc_read(id, (u8*)&data, len);
	if(len != ret)
	{
		MODEM_CPUFREQ_PRINT("readcb err\n");
		return -1;
	}

    if(data.msgtype == 6)
    {
        ret = modem_request_ddr(data.profile);
        if(ret != 0)
        {
            MODEM_CPUFREQ_PRINT("mdm_request_ddr err\n");
            return -1;
        }
    }
    else
    {
    	smail = osMailCAlloc(cpufreq_mail, osWaitForever);
    	memcpy(smail, (const void*)&data, len);
    	osMailPut(cpufreq_mail, smail);
    }

	return 0;
}

u32 cpufreq_get_cur_profile(void)
{
	s32 tmp = 0;

	tmp = dfs_get_profile();
	if(tmp == CPUFREQ_INVALID_PROFILE)
	{
		MODEM_CPUFREQ_PRINT("cur profile invalid\n");
		return 0;
	}
	return tmp;
}

u32 cpufreq_find_profile(u32 action, u32 profile)
{
	u32 curprof = CPUFREQ_INVALID_PROFILE;
	u32 dstprof = CPUFREQ_INVALID_PROFILE;

	curprof = cpufreq_get_cur_profile();
	switch(action)
	{
		case 0://升
            profile = curprof + 1;
		case 1://升目标
			if((curprof < profile) && (profile <= g_cpufreq.maxprof))
			{
				dstprof = profile;
			}
			else
			{
				MODEM_CPUFREQ_PRINT("cpufreq up  dst: %d, cur:%d, max: %d\n", profile, curprof, g_cpufreq.maxprof);
				dstprof = CPUFREQ_INVALID_PROFILE;/* invalid or not change*/
			}
			break;
		case 2://降
            profile = (curprof > 0)?(curprof - 1) : 0;
		case 3://降目标
			if((profile < curprof) && (profile >= g_cpufreq.minprof))
			{
				dstprof = profile;
			}
			else
			{
				MODEM_CPUFREQ_PRINT("cpufreq down  dst:%d, cur:%d, min:%d\n", profile, curprof, g_cpufreq.minprof);
				dstprof = CPUFREQ_INVALID_PROFILE;/* invalid or not change*/
			}
			break;
		case 4://设置最小profile
			if(profile > g_cpufreq.maxprof)
			{
                MODEM_CPUFREQ_PRINT("1 profile not in the range\n");
			}
            else if(profile == g_cpufreq.minprof)
            {
                MODEM_CPUFREQ_PRINT("minprof is the same\n");
            }
			else
			{
				g_cpufreq.minprof = profile;
                M3_MIN_CPUFREQ_PROFILE = profile;
				if(curprof < profile)
				{
					dstprof = profile;
				}
				else
				{
					dstprof = CPUFREQ_INVALID_PROFILE;
				}
			}
			break;
		case 5://设置最大profile
			if((profile > CPUFREQ_MAX_PROFILE)||(profile < g_cpufreq.minprof))
			{
                MODEM_CPUFREQ_PRINT("2 profile not in the range\n");
			}
            else if(profile == g_cpufreq.maxprof)
            {
                MODEM_CPUFREQ_PRINT("maxprof is the same\n");
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

static s32 cpufreq_icc_send_ccore(T_CPUFREQ_MAIL *msg)
{
	u32 channel_id = (ICC_CHN_MCORE_CCORE << 16) | MCU_CCORE_CPUFREQ;
	s32 ret = 0;
	u32 msglen = sizeof(T_CPUFREQ_MAIL);

	ret = bsp_icc_send(ICC_CPU_MODEM, channel_id, (u8*)msg, msglen);
	if(ret != msglen)
	{
		MODEM_CPUFREQ_PRINT("send_ccore err\n");
		return -1;
	}
    return 0;
}

static void cpufreq_recv_mail(T_CPUFREQ_MAIL  *rmail)
{
	int irqlock = 0;
	u32 dstprof = 0;
	T_CPUFREQ_MAIL msgsend;

	if(rmail == NULL)
	{
		MODEM_CPUFREQ_PRINT("recv_mail input err\n");
		return;
	}

    if(rmail->coretype != CPUFREAQ_CCORE)
    {
        MODEM_CPUFREQ_PRINT("rmail->coretype err=%d\n", rmail->coretype);
        return;
    }

    //MODEM_CPUFREQ_PRINT(" msgtype:%d action:%d profile=%d\n", rmail->msgtype, rmail->action, rmail->profile);
	switch(rmail->msgtype)
	{
		case 1:
			local_irq_save(irqlock);
			if(!g_cpufreq.ccorelockflag)
			{
				dstprof = cpufreq_find_profile(rmail->action, rmail->profile);
				if(dstprof != CPUFREQ_INVALID_PROFILE)
				{
					dfs_set_profile(dstprof);
					g_cpufreq.curprof = dstprof;
                    M3_CUR_CPUFREQ_PROFILE = dstprof;
				}
			}
            else
            {
                MODEM_CPUFREQ_PRINT("cpufreq lock\n");
            }
			local_irq_restore(irqlock);
			break;
		case 3:
			msgsend.msgtype = 4;
			msgsend.coretype = CPUFREAQ_MCORE;
			msgsend.profile = cpufreq_get_cur_profile();
			cpufreq_icc_send_ccore(&msgsend);
			break;
        case 5:
            cpufreq_set_ccorelockflag(rmail->action);
            break;
		default:
			MODEM_CPUFREQ_PRINT("msgtype err\n");
			break;
	}
}

void thread_cpufreq (void const *arg)
{
	T_CPUFREQ_MAIL  *rmail = NULL;
	osEvent  evt;

	for(;;)
	{
		evt = osMailGet(cpufreq_mail, osWaitForever);
		if (evt.status == osEventMail)
		{
            if(1 == bsp_reset_ccpu_status_get())
            {
			    rmail = evt.value.p;
			    cpufreq_recv_mail(rmail);
            }
			osMailFree(cpufreq_mail, rmail);
		}
	}
}

void cpufreq_suspend(void)
{
}

void cpufreq_resume(void)
{
    g_cpufreq.maxprof = CPUFREQ_MAX_PROFILE;
	g_cpufreq.minprof = CPUFREQ_MIN_PROFILE;
    g_cpufreq.curprof = CPUFREQ_MAX_PROFILE;
    M3_CUR_CPUFREQ_PROFILE = g_cpufreq.curprof;
    M3_MAX_CPUFREQ_PROFILE = g_cpufreq.maxprof;
    M3_MIN_CPUFREQ_PROFILE = g_cpufreq.minprof;
}

void cpufreq_print_debug(void)
{
	MODEM_CPUFREQ_PRINT("default max prof:%d\n", CPUFREQ_MAX_PROFILE);
	MODEM_CPUFREQ_PRINT("default min prof:%d\n", CPUFREQ_MIN_PROFILE);
	MODEM_CPUFREQ_PRINT("current max prof:%d\n", g_cpufreq.maxprof);
	MODEM_CPUFREQ_PRINT("current min prof:%d\n", g_cpufreq.minprof);
	MODEM_CPUFREQ_PRINT("current prof:%d\n", g_cpufreq.curprof);
    MODEM_CPUFREQ_PRINT("ccorelockflag:%d\n", g_cpufreq.ccorelockflag);
}


