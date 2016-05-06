/*************************************************************************
*   版权所有(C) 20014-2015, 深圳华为技术有限公司.
*
*   文 件 名 :  cpufreq_balong_reg.c
*
*   作    者 :  y00221789
*
*   描    述 :
*
*   修改记录 :  2015年3月27日  v1.00  y00221789  创建
*************************************************************************/
#include <product_config.h>
#include <securec.h>

#include <osl_malloc.h>
#include <osl_irq.h>
#include <of.h>
#include <bsp_dpm.h>
#include <bsp_sysctrl.h>
#include <bsp_hardtimer.h>
#include "cpufreq_balong.h"

struct phone_ctrl_st
{
    u32 cur_pro;
    u32 dst_clk_div;
};

/*lint --e{525, 539, 830}*/
void cpufreq_config_set_freq(u32 cur, u32 new);
u32 cpufreq_pll_get_profile(void);
extern void cpufreq_config_reg(u32 cur, u32 new);
extern u32 cpufreq_get_cur_profile(void);
extern u32 cpufreq_sysctrl_base_addr;

extern u32 cpufreq_clkdiv2_offset;

extern u32 cpufreq_a9pll_cfg0_offset;

extern u32 cpufreq_a9pll_cfg1_offset;

extern u32 cpufreq_pericrg_base_addr;

extern u32 cpufreq_pericrg_clkdiv12_offset;

extern u32 cpufreq_pericrg_clkdiv13_offset;

extern u32 cpufreq_pericrg_state_offset;

extern u32 cpufreq_max_pll;

extern u32 cpufreq_dpm_get_curpro;

extern T_CPUFREQ_PROFILE *gCpufrqProfile;

/* pll only support 666M and 400M */
extern T_CPUFREQ_PLL_CONFIG *gCpufrqPll;

struct phone_ctrl_st g_phone_ctrl = {0, 0};

u32 cpufreq_pll_get_profile(void)
{
	u32 profile = CPUFREQ_INVALID_PROFILE;
	T_CPUFREQ_PLL_CONFIG curconf;
	u32 invalid = 0xFFFFFFFF;
	u32 curpll = invalid;
	u32 curclkdiv = 0;
	u32 i = 0;
    /*lint --e{801 }*/
	/* find right pll */
	curconf.plldiv13 = readl(cpufreq_pericrg_base_addr + cpufreq_pericrg_clkdiv13_offset);

	for(i = 0;(i < cpufreq_max_pll) && (curconf.plldiv13 & 0x3C0);i++)
	{
    	if((curconf.plldiv13 & 0x3C0) == (gCpufrqPll[i].plldiv13 & 0x3C0))
    	{
    		curpll = i;
    		goto findpll;
    	}
	}
    /* find right pll */
    curconf.a9pllcfg0 = readl(cpufreq_sysctrl_base_addr + cpufreq_a9pll_cfg0_offset);
    curconf.a9pllcfg1 = readl(cpufreq_sysctrl_base_addr + cpufreq_a9pll_cfg1_offset);

    for(i = 0;(i < cpufreq_max_pll) && (!(curconf.plldiv13 & 0x3C0));i++)
    {
        if((curconf.a9pllcfg0&0x3FFFFFC) == gCpufrqPll[i].a9pllcfg0)
        {
            if((curconf.a9pllcfg1&0xFFFFFF) == gCpufrqPll[i].a9pllcfg1)
            {
                curpll = i;
                goto findpll;
            }
        }
    }

findpll:

	if(curpll == invalid)
	{
		cpufreq_err("dfs_get_profile pll error %x\n", curconf.plldiv13);
		return CPUFREQ_INVALID_PROFILE;
	}

	/* find right profile */
	curclkdiv = readl(cpufreq_sysctrl_base_addr + cpufreq_clkdiv2_offset);

	for(i = 0;i <= (u32)BALONG_FREQ_MAX;i++)
	{
		if(curpll == gCpufrqProfile[i].pll)
		{
			if((curclkdiv&0x4000FFF0) == gCpufrqProfile[i].clkdiv)
			{
				profile = i;
				break;
			}
		}
	}
	return profile;
}
/*
该函数是根据芯片流程实现:
如果mcpu_div的分频系数变小，先配置slow_div/fast_div/apb_div,后配置mcpu_div
否则先配置mcpu_div再配置slow_div/fast_div/apb_div.
*/
static inline void cpufreq_set_freqdiv(u32 new_clk_div, u32 cur_clk_div)
{
    u32 tmp = 0;
    if (new_clk_div == cur_clk_div)
        return;
    tmp = readl(cpufreq_sysctrl_base_addr + cpufreq_clkdiv2_offset);
    if ((new_clk_div & 0xF0) < (cur_clk_div & 0xF0))
    {
    	tmp &= 0xBFFF00FF;/* bit[30 15:12  11:8]-->apb fbus glb */
	    tmp |= (new_clk_div & 0x4000FF00);
	    writel(tmp, cpufreq_sysctrl_base_addr + cpufreq_clkdiv2_offset);
	    tmp &= 0xFFFFFF0F;
	    tmp |= (new_clk_div & 0xF0);
	    writel(tmp, cpufreq_sysctrl_base_addr + cpufreq_clkdiv2_offset);
	}
	else
	{
		tmp &= 0xFFFFFF0F;
	    tmp |= (new_clk_div & 0xF0);
	    writel(tmp, cpufreq_sysctrl_base_addr + cpufreq_clkdiv2_offset);

    	tmp &= 0xBFFF00FF;/* bit[30 15:12  11:8]-->apb fbus glb */
	    tmp |= (new_clk_div & 0x4000FF00);
	    writel(tmp, cpufreq_sysctrl_base_addr + cpufreq_clkdiv2_offset);
	}
}


/*freq_div_reg 为写入寄存器中的值*/
static inline void cpufreq_set_pll_div(u32 freq_div_reg)
{
    u32 tmp = 0;
    writel(freq_div_reg & 0x3C003C0, cpufreq_pericrg_base_addr + cpufreq_pericrg_clkdiv13_offset);
    do{
        tmp = readl(cpufreq_pericrg_base_addr + cpufreq_pericrg_state_offset);
        tmp = (tmp >> 29) & 0x1;
    }while(tmp != 0x1);
}

static inline void cpufreq_set_new_pll0(u32 cur, u32 new)
{
    u32 tmp = 0;
    u32 curpll = 0;
	u32 newpll = 0;
    u32 curmaxpro = 0;
    
    curpll = gCpufrqProfile[cur].pll;
    newpll = gCpufrqProfile[new].pll;

    curmaxpro = gCpufrqPll[curpll].maxpro;
    //666 666 166 83
    cpufreq_config_set_freq(cur, curmaxpro);
    //ap pll div 2分频
    cpufreq_set_pll_div(0x3C00040);
    //333 333 66 66
    cpufreq_set_freqdiv(0x0400, gCpufrqProfile[curmaxpro].clkdiv);
    //div 3分频
    cpufreq_set_pll_div(0x3C00080);
    //切pll0
    writel(gCpufrqPll[newpll].plldiv12, cpufreq_pericrg_base_addr + cpufreq_pericrg_clkdiv12_offset);
    writel(gCpufrqPll[newpll].plldiv13 & 0xC000C00, cpufreq_pericrg_base_addr + cpufreq_pericrg_clkdiv13_offset);

    /* 4 close pll4*/
	tmp = readl(cpufreq_sysctrl_base_addr + cpufreq_a9pll_cfg0_offset);
	tmp &= ~(0x3);
    tmp |= 0x2;
	writel(tmp, cpufreq_sysctrl_base_addr + cpufreq_a9pll_cfg0_offset);
}
static inline void cpufreq_set_new_pll4(u32 cur, u32 new)
{
    u32 tmp = 0;
    u32 curpll = 0;
	u32 newpll = 0;
	u32 curmaxpro = 0;
	u32 newmaxpro = 0;
	curpll = gCpufrqProfile[cur].pll;
	newpll = gCpufrqProfile[new].pll;
    curmaxpro = gCpufrqPll[curpll].maxpro;
    newmaxpro = gCpufrqPll[newpll].maxpro;
    
    /* open pll4*/
    tmp = readl(cpufreq_sysctrl_base_addr + cpufreq_a9pll_cfg0_offset);
	tmp &= ~(0x3);
    tmp |= 0x1;
	writel(tmp, cpufreq_sysctrl_base_addr + cpufreq_a9pll_cfg0_offset);
    /*wait pll4 lock*/
	do
	{
		tmp = readl(cpufreq_sysctrl_base_addr + cpufreq_a9pll_cfg0_offset);
		tmp = (tmp >> 26) & 0x1;
	}while(!tmp);
    //先将频率配置为pll0支持的最高profile: mcpu:480 fbus:480 glb:96 apb:96
    //此时，ap pll div为3
    cpufreq_config_set_freq(cur, gCpufrqPll[PPLL0_DIV3].maxpro);
    //切pll4
    writel(gCpufrqPll[newpll].plldiv13 & 0xC000C00, cpufreq_pericrg_base_addr + cpufreq_pericrg_clkdiv13_offset);
    writel(gCpufrqPll[newpll].plldiv12, cpufreq_pericrg_base_addr + cpufreq_pericrg_clkdiv12_offset);
    
    // ap pll div 2分频
    cpufreq_set_pll_div(0x3C00040);
    //[mcpu fbus glb apb]: 333 333 83 41，此时将apb:glb=2:1
    cpufreq_set_freqdiv(gCpufrqProfile[newmaxpro].clkdiv, gCpufrqProfile[curmaxpro].clkdiv);
    // ap pll div 1分频
    cpufreq_set_pll_div(0x3C00000);
}
static inline void cpufreq_config_reg_ppll0(u32 cur, u32 new)
{
    u32 curpll = 0;
	u32 newpll = 0;
	u32 curmaxpro = 0;
	u32 newmaxpro = 0;
    u32 curclkdiv = gCpufrqProfile[cur].clkdiv;
    curpll = gCpufrqProfile[cur].pll;
	newpll = gCpufrqProfile[new].pll;
    /*lint --e{801 }*/
	if(curpll == newpll)
    {
        goto setclkdiv;
    }
    curmaxpro = gCpufrqPll[curpll].maxpro;
    newmaxpro = gCpufrqPll[newpll].maxpro;

    //先临时切到当前pll输出的最高频，以便后续切频满足apb限制(38.4<apb<=111)
    cpufreq_set_freqdiv(gCpufrqProfile[curmaxpro].clkdiv, gCpufrqProfile[cur].clkdiv);
    //newpll 360
    if (PPLL0_DIV4 == newpll)
    {
        //ap pll div 4分频
        cpufreq_set_pll_div(gCpufrqPll[newpll].plldiv13);
        cpufreq_set_freqdiv(gCpufrqProfile[newmaxpro].clkdiv, gCpufrqProfile[curmaxpro].clkdiv);
    }
    else if(PPLL0_DIV3 == newpll)//new pll 480
    {
        //配置pll输出为360时的中间频率，mcpu:360,fbus:360,glb:72,apb:72,保证到480时apb不会超出限制
        cpufreq_set_freqdiv(gCpufrqProfile[newmaxpro].clkdiv, gCpufrqProfile[curmaxpro].clkdiv);
         //ap pll div 3分频
        cpufreq_set_pll_div(gCpufrqPll[newpll].plldiv13);
     }
     curclkdiv = gCpufrqProfile[newmaxpro].clkdiv;
setclkdiv:
    cpufreq_set_freqdiv(gCpufrqProfile[new].clkdiv, curclkdiv);
}
static inline void cpufreq_config_reg_ppll4(u32 cur, u32 new)
{
    cpufreq_config_reg(cur, new);
}

void cpufreq_config_set_freq(u32 cur, u32 new)
{
	u32 curpll = 0;
	u32 newpll = 0;
	
    curpll = gCpufrqProfile[cur].pll;
	newpll = gCpufrqProfile[new].pll;

	curpll = gCpufrqPll[curpll].ppll;
	newpll = gCpufrqPll[newpll].ppll;
    /*lint --e{801 }*/
    if(curpll == newpll && 0 == newpll)
    {
		cpufreq_config_reg_ppll0(cur, new);
	}
	else if(curpll == newpll && 4 == newpll)
	{
		cpufreq_config_reg_ppll4(cur, new);
    }
	else if(curpll != newpll && 0 == newpll)
    {
		//将频率调整到pll0支持的最大profile
		cpufreq_set_new_pll0(cur, new);
		cur = gCpufrqPll[PPLL0_DIV3].maxpro;
		cpufreq_config_reg_ppll0(cur, new);
	}
	else if(curpll != newpll && 4 == newpll)
	{
		//将频率调整到pll4支持的最大profile
		cpufreq_set_new_pll4(cur, new);
		cur = gCpufrqPll[PPLL4_DIV1].maxpro;
		cpufreq_config_reg_ppll4(cur, new);
    }
}

/* guoliang给的进入流程配置3次 */
static inline void cpufreq_enter_phone_idle_cfg(u32 curpll, u32 new_clk_div, u32 cur_clk_div)
{
    if (!new_clk_div)
        return;
    switch(curpll)
    {
        case 0:
            //666 666 111 111 cpu fbus glb apb
            cpufreq_set_freqdiv(0x0500, cur_clk_div);
            // 333 333 111 111 
            cpufreq_set_freqdiv(0x0210, 0x0500);
            //166 166 166 83
            cpufreq_set_freqdiv(0x40000030, 0x0210);
            cpufreq_set_freqdiv(new_clk_div, 0x40000030);
            break;
        case 1:
            //240 240 80 80
            cpufreq_set_freqdiv(0x0210, cur_clk_div);
            //120 120 60 60
            cpufreq_set_freqdiv(0x0130, 0x0210);
            // 96 96 96 96 
            cpufreq_set_freqdiv(0x0040, 0x0130);
            cpufreq_set_freqdiv(new_clk_div, 0x0040);   
            break;
        case 2:
            //180 180 90 90
            cpufreq_set_freqdiv(0x0110, cur_clk_div);
            //90 90 90 90
            cpufreq_set_freqdiv(0x0030, 0x0110);
            cpufreq_set_freqdiv(new_clk_div, 0x0030);
            break;
        default:
            break;
    }
}

/* guoliang给的退出流程配置4次 */
static inline void cpufreq_exit_phone_idle_cfg(u32 curpll, u32 new_clk_div, u32 cur_clk_div)
{
    if(!cur_clk_div)
        return;
	switch(curpll)
    {
        case 0:
            //166 166 166 83
            cpufreq_set_freqdiv(0x40000030, cur_clk_div);
            // 333 333 111 111 
            cpufreq_set_freqdiv(0x0210, 0x40000030);
            //666 666 111 111 cpu fbus glb apb
            cpufreq_set_freqdiv(0x0500, 0x0210);
            cpufreq_set_freqdiv(new_clk_div, 0x0500);
            break;
        case 1:
            // 96 96 96 96 
            cpufreq_set_freqdiv(0x0040, cur_clk_div);
            //120 120 60 60
            cpufreq_set_freqdiv(0x0130, 0x0040);
            //240 240 80 80
            cpufreq_set_freqdiv(0x0210, 0x0130);
            cpufreq_set_freqdiv(new_clk_div, 0x0210);
            break;
        case 2:
            //90 90 90 90
            cpufreq_set_freqdiv(0x0030, cur_clk_div);
            //180 180 90 90
            cpufreq_set_freqdiv(0x0110, 0x0030);
            cpufreq_set_freqdiv(new_clk_div, 0x0110);
            break;
        default:
            break;
    }
}
static inline u32 cpufreq_get_dst_glb_div(u32 cur_pro)
{
    u32 pll_freq = 0;
    u32 max_busfreq = 222;
    u32 min_busfreq = 40;
    u32 request_bus_freq = g_cpufreq_core_ctrl.g_bus_total_freq;

    pll_freq = gCpufrqProfile[cur_pro].pll;
    max_busfreq = gCpufrqPll[pll_freq].max_glb;
    min_busfreq = gCpufrqPll[pll_freq].min_glb;
    request_bus_freq = (request_bus_freq > max_busfreq) ? max_busfreq : request_bus_freq;
    request_bus_freq = (request_bus_freq < min_busfreq) ? min_busfreq : request_bus_freq;
    pll_freq = gCpufrqPll[pll_freq].pll_freq;
    return (pll_freq/request_bus_freq) - 1;
}
static inline u32 cpufreq_get_dst_clk_div(u32 cur_pro, u32 cur_clk_div)
{
    u32 cur_glb_div = 0;
    u32 dst_glb_div = 0;
    u32 cur_cpu_div = 0;
    u32 dst_clk_div = 0;

    cur_cpu_div = ((cur_clk_div >> 4) & 0xF) + 1;
    cur_glb_div = ((cur_clk_div >> 8) & 0xF) + 1;
    cur_glb_div = (cur_cpu_div * cur_glb_div) -1;
    dst_glb_div = cpufreq_get_dst_glb_div(cur_pro);
    dst_glb_div = (dst_glb_div < cur_glb_div) ? 0 : dst_glb_div;
    if (dst_glb_div < cur_glb_div)
        return 0;
    dst_clk_div = (dst_glb_div << 0x4) | (0 << 0x8) | (0 << 0xC);
    dst_clk_div |= (cur_clk_div & 0x40000000);

    return dst_clk_div;
}
static inline void cpufreq_enter_phone_idle(void)
{
    u32 cur_pro = 0;
    u32 cur_clk_div = 0;
    u32 dst_clk_div = 0;
    unsigned long irqlock = 0;
    /*lint --e{63}*/
    
    if (g_cpufreq_core_ctrl.g_cpufreq_bus_vote_valid && g_cpufreq_core_ctrl.g_bus_total_freq)
    {
        local_irq_save(irqlock);
        //9-10us
        cur_pro = cpufreq_dpm_get_curpro ? (u32)BALONG_FREQ_MAX : cpufreq_get_cur_profile();
        g_phone_ctrl.cur_pro = cur_pro;
        cur_clk_div = gCpufrqProfile[cur_pro].clkdiv;
        dst_clk_div = cpufreq_get_dst_clk_div(cur_pro, cur_clk_div);
        g_phone_ctrl.dst_clk_div = dst_clk_div;
        //62us/87us
        cpufreq_enter_phone_idle_cfg(gCpufrqProfile[cur_pro].pll, dst_clk_div, cur_clk_div);

        local_irq_restore(irqlock);
    }
}

static inline void cpufreq_exit_phone_idle(void)
{
    u32 cur_pro = 0;
    unsigned long irqlock = 0;
    if (g_cpufreq_core_ctrl.g_cpufreq_bus_vote_valid)
    {
        /*lint --e{63}*/
        local_irq_save(irqlock);
        //change bus
        cur_pro = g_phone_ctrl.cur_pro;
        cpufreq_exit_phone_idle_cfg(gCpufrqProfile[cur_pro].pll, gCpufrqProfile[cur_pro].clkdiv, g_phone_ctrl.dst_clk_div);
        local_irq_restore(irqlock);
    }
}

struct cpufreq_reg_ops cpufreq_ops_pll40 = {
        .ops_id = 6250,
        .get_cur_pro = cpufreq_pll_get_profile,
        .set_freq = cpufreq_config_set_freq,
        .enter_idle = cpufreq_enter_phone_idle,
        .exit_idle = cpufreq_exit_phone_idle,
};


