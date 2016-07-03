#ifndef __HI_PWRCTRL_INTER_H__
#define __HI_PWRCTRL_INTER_H__

#include "hi_base.h"
#include "hi_pwrctrl.h"

#if 0
/*irm 钳位禁使能*/
static __inline__ void set_hi_pwr_ctrl5_irm_iso_dis(unsigned int v)
{
	return set_hi_pwr_ctrl5_irmbbp_iso_ctrl_dis(v);
}

/*irm 钳位使能*/
static __inline__ void set_hi_pwr_ctrl4_irm_iso_en(unsigned int v)
{
	set_hi_pwr_ctrl4_irmbbp_iso_ctrl_en(v);
}

/*irm上电*/
static __inline__ void set_hi_pwr_ctrl6_irm_mtcmos_en(unsigned int v)
{
	set_hi_pwr_ctrl6_irmbbp_mtcmos_ctrl_en(v);
}

/*irm 下电*/
static __inline__ void set_hi_pwr_ctrl7_irm_mtcmos_dis(unsigned int v)
{
	set_hi_pwr_ctrl7_irmbbp_mtcmos_ctrl_dis(v);
}

/*irm 状态查询*/
static __inline__ unsigned int get_hi_pwr_stat1_irm_mtcmos_rdy(void)
{
	return get_hi_pwr_stat1_irmbbp_mtcmos_rdy_stat();
}
#endif

/* for pm */
static __inline__ unsigned int  hi_pwrctrl_get_pwr_ctrl2_abb_ch1_tcxo_en(void){return 0;}
static __inline__ unsigned int  hi_pwrctrl_get_pwr_ctrl2_pmu_ch1_tcxo_en(void){return 0;}

static __inline__ void hi_pwrctrl_set_pwr_ctrl2_abb_ch1_tcxo_en(unsigned int val){};
static __inline__ void hi_pwrctrl_set_pwr_ctrl2_pmu_ch1_tcxo_en(unsigned int val){};

#if 0
static __inline__ unsigned int get_hi_pwr_stat1(void)
{
#if defined(__KERNEL__)
	return readl((const volatile void *)(HI_SYSCRG_BASE_ADDR+HI_PWR_STAT1_OFFSET));
#else
	return readl((HI_SYSCRG_BASE_ADDR+HI_PWR_STAT1_OFFSET));
#endif
}
/* for pm --end */
#endif
#if 0
/******** dsp start ********/
static __inline__ void dsp_bbe_power_on(void)
{
    /* power on BBE16 */
    set_hi_pwr_ctrl6_bbe16_mtcmos_ctrl_en(1);
    while (!get_hi_pwr_stat1_bbe16_mtcmos_rdy_stat()) ;
}

static __inline__ void dsp_iso_clamp_dis(void)
{
    /* disable ISO clamp */
    set_hi_pwr_ctrl5_bbe16_iso_ctrl_dis(1);
}

static __inline__ void dsp_bbe_power_off(void)
{
    /* power down DSP0 */
    set_hi_pwr_ctrl7_bbe16_mtcmos_ctrl_dis(1);
}

static __inline__ void dsp_iso_clamp_en(void)
{
    /* enable ISO clamp */
    set_hi_pwr_ctrl4_bbe16_iso_ctrl_en(1);
}

/******** dsp end *********/
#endif
#endif
