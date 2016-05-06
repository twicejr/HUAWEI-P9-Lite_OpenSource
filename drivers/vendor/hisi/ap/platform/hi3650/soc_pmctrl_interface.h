/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_pmctrl_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-04-15 11:18:17
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年4月15日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_PMCTRL.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_PMCTRL_INTERFACE_H__
#define __SOC_PMCTRL_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) register_define
 ****************************************************************************/
/* 寄存器说明：PMC中断使能寄存器。
   位域定义UNION结构:  SOC_PMCTRL_PMCINTEN_UNION */
#define SOC_PMCTRL_PMCINTEN_ADDR(base)                ((base) + (0x000))

/* 寄存器说明：PMC中断状态寄存器。
   位域定义UNION结构:  SOC_PMCTRL_PMCINTSTAT_UNION */
#define SOC_PMCTRL_PMCINTSTAT_ADDR(base)              ((base) + (0x004))

/* 寄存器说明：PMC中断清除寄存器。
   位域定义UNION结构:  SOC_PMCTRL_PMCINTCLR_UNION */
#define SOC_PMCTRL_PMCINTCLR_ADDR(base)               ((base) + (0x008))

/* 寄存器说明：PMC状态寄存器。
   位域定义UNION结构:  SOC_PMCTRL_PMCSTATUS_UNION */
#define SOC_PMCTRL_PMCSTATUS_ADDR(base)               ((base) + (0x00C))

/* 寄存器说明：APLL0控制寄存器0。
   位域定义UNION结构:  SOC_PMCTRL_APLL0CTRL0_UNION */
#define SOC_PMCTRL_APLL0CTRL0_ADDR(base)              ((base) + (0x010))

/* 寄存器说明：APLL0控制寄存器1。
   位域定义UNION结构:  SOC_PMCTRL_APLL0CTRL1_UNION */
#define SOC_PMCTRL_APLL0CTRL1_ADDR(base)              ((base) + (0x014))

/* 寄存器说明：APLL1控制寄存器0。
   位域定义UNION结构:  SOC_PMCTRL_APLL1CTRL0_UNION */
#define SOC_PMCTRL_APLL1CTRL0_ADDR(base)              ((base) + (0x018))

/* 寄存器说明：APLL1控制寄存器1。
   位域定义UNION结构:  SOC_PMCTRL_APLL1CTRL1_UNION */
#define SOC_PMCTRL_APLL1CTRL1_ADDR(base)              ((base) + (0x01C))

/* 寄存器说明：APLL2控制寄存器0。
   位域定义UNION结构:  SOC_PMCTRL_APLL2CTRL0_UNION */
#define SOC_PMCTRL_APLL2CTRL0_ADDR(base)              ((base) + (0x020))

/* 寄存器说明：APLL2控制寄存器1。
   位域定义UNION结构:  SOC_PMCTRL_APLL2CTRL1_UNION */
#define SOC_PMCTRL_APLL2CTRL1_ADDR(base)              ((base) + (0x024))

/* 寄存器说明：PPLL1控制寄存器0。
   位域定义UNION结构:  SOC_PMCTRL_PPLL1CTRL0_UNION */
#define SOC_PMCTRL_PPLL1CTRL0_ADDR(base)              ((base) + (0x038))

/* 寄存器说明：PPLL1控制寄存器1。
   位域定义UNION结构:  SOC_PMCTRL_PPLL1CTRL1_UNION */
#define SOC_PMCTRL_PPLL1CTRL1_ADDR(base)              ((base) + (0x03C))

/* 寄存器说明：PPLL2控制寄存器0。
   位域定义UNION结构:  SOC_PMCTRL_PPLL2CTRL0_UNION */
#define SOC_PMCTRL_PPLL2CTRL0_ADDR(base)              ((base) + (0x040))

/* 寄存器说明：PPLL2控制寄存器1。
   位域定义UNION结构:  SOC_PMCTRL_PPLL2CTRL1_UNION */
#define SOC_PMCTRL_PPLL2CTRL1_ADDR(base)              ((base) + (0x044))

/* 寄存器说明：PPLL3控制寄存器0。
   位域定义UNION结构:  SOC_PMCTRL_PPLL3CTRL0_UNION */
#define SOC_PMCTRL_PPLL3CTRL0_ADDR(base)              ((base) + (0x048))

/* 寄存器说明：PPLL3控制寄存器1。
   位域定义UNION结构:  SOC_PMCTRL_PPLL3CTRL1_UNION */
#define SOC_PMCTRL_PPLL3CTRL1_ADDR(base)              ((base) + (0x04C))

/* 寄存器说明：APLL0 SSC控制寄存器。
   位域定义UNION结构:  SOC_PMCTRL_APLL0SSCCTRL_UNION */
#define SOC_PMCTRL_APLL0SSCCTRL_ADDR(base)            ((base) + (0x070))

/* 寄存器说明：APLL1 SSC控制寄存器。
   位域定义UNION结构:  SOC_PMCTRL_APLL1SSCCTRL_UNION */
#define SOC_PMCTRL_APLL1SSCCTRL_ADDR(base)            ((base) + (0x074))

/* 寄存器说明：APLL2 SSC控制寄存器。
   位域定义UNION结构:  SOC_PMCTRL_APLL2SSCCTRL_UNION */
#define SOC_PMCTRL_APLL2SSCCTRL_ADDR(base)            ((base) + (0x078))

/* 寄存器说明：PPLL1 SSC控制寄存器。
   位域定义UNION结构:  SOC_PMCTRL_PPLL1SSCCTRL_UNION */
#define SOC_PMCTRL_PPLL1SSCCTRL_ADDR(base)            ((base) + (0x084))

/* 寄存器说明：PPLL2 SSC控制寄存器。
   位域定义UNION结构:  SOC_PMCTRL_PPLL2SSCCTRL_UNION */
#define SOC_PMCTRL_PPLL2SSCCTRL_ADDR(base)            ((base) + (0x088))

/* 寄存器说明：PPLL3 SSC控制寄存器。
   位域定义UNION结构:  SOC_PMCTRL_PPLL3SSCCTRL_UNION */
#define SOC_PMCTRL_PPLL3SSCCTRL_ADDR(base)            ((base) + (0x08C))

/* 寄存器说明：PMU供电模式寄存器。
   位域定义UNION结构:  SOC_PMCTRL_PMUMOD_UNION */
#define SOC_PMCTRL_PMUMOD_ADDR(base)                  ((base) + (0x094))

/* 寄存器说明：A53_CPU DVFS模式寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPUDVFSMOD_UNION */
#define SOC_PMCTRL_A53_CPUDVFSMOD_ADDR(base)          ((base) + (0x098))

/* 寄存器说明：A53_CPU 时钟来源选择寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPUCLKSEL_UNION */
#define SOC_PMCTRL_A53_CPUCLKSEL_ADDR(base)           ((base) + (0x09C))

/* 寄存器说明：A53_CPU DVFS使能寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPUDVFSEN_UNION */
#define SOC_PMCTRL_A53_CPUDVFSEN_ADDR(base)           ((base) + (0x0A0))

/* 寄存器说明：A53_CPU PLL选择寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPUPLLSEL_UNION */
#define SOC_PMCTRL_A53_CPUPLLSEL_ADDR(base)           ((base) + (0x0A4))

/* 寄存器说明：A53_CPU时钟分频寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPUCLKDIV_UNION */
#define SOC_PMCTRL_A53_CPUCLKDIV_ADDR(base)           ((base) + (0x0A8))

/* 寄存器说明：A53_CPU DVFS启动寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPUDVFSSTART_UNION */
#define SOC_PMCTRL_A53_CPUDVFSSTART_ADDR(base)        ((base) + (0x0AC))

/* 寄存器说明：A53_CPU频率Profile寄存器0。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPUCLKPROFILE0_UNION */
#define SOC_PMCTRL_A53_CPUCLKPROFILE0_ADDR(base)      ((base) + (0x0B0))

/* 寄存器说明：A53_CPU频率Profile寄存器0_1。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPUCLKPROFILE0_1_UNION */
#define SOC_PMCTRL_A53_CPUCLKPROFILE0_1_ADDR(base)    ((base) + (0x0B4))

/* 寄存器说明：A53_CPU频率Profile寄存器1
   位域定义UNION结构:  SOC_PMCTRL_A53_CPUCLKPROFILE1_UNION */
#define SOC_PMCTRL_A53_CPUCLKPROFILE1_ADDR(base)      ((base) + (0x0B8))

/* 寄存器说明：A53_CPU DVFS时调压模式寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPUVOLMOD_UNION */
#define SOC_PMCTRL_A53_CPUVOLMOD_ADDR(base)           ((base) + (0x0BC))

/* 寄存器说明：A53_CPU电压Profile寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPUVOLPROFILE_UNION */
#define SOC_PMCTRL_A53_CPUVOLPROFILE_ADDR(base)       ((base) + (0x0C0))

/* 寄存器说明：A53_CPU DVFS时的相位模式寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPUPHASEMOD_UNION */
#define SOC_PMCTRL_A53_CPUPHASEMOD_ADDR(base)         ((base) + (0xC8))

/* 寄存器说明：A53_CPU相位Profile寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPUPHASEPROFILE_UNION */
#define SOC_PMCTRL_A53_CPUPHASEPROFILE_ADDR(base)     ((base) + (0x0CC))

/* 寄存器说明：A53_CPU电压/相位配置先后选择寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPUVOLPHASESEL_UNION */
#define SOC_PMCTRL_A53_CPUVOLPHASESEL_ADDR(base)      ((base) + (0x0D0))

/* 寄存器说明：A53_电压上升一档稳定步长时间寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A53_VOLUPSTEPTIME_UNION */
#define SOC_PMCTRL_A53_VOLUPSTEPTIME_ADDR(base)       ((base) + (0x0D4))

/* 寄存器说明：A53_电压下降一档稳定步长时间寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A53_VOLDNSTEPTIME_UNION */
#define SOC_PMCTRL_A53_VOLDNSTEPTIME_ADDR(base)       ((base) + (0x0D8))

/* 寄存器说明：A53_ DVFS时改变电压相位的上升稳定时间寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A53_PHASEUPTIME_UNION */
#define SOC_PMCTRL_A53_PHASEUPTIME_ADDR(base)         ((base) + (0x0DC))

/* 寄存器说明：A53_ DVFS时改变电压相位的下降稳定时间寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A53_PHASEDNTIME_UNION */
#define SOC_PMCTRL_A53_PHASEDNTIME_ADDR(base)         ((base) + (0x0E0))

/* 寄存器说明：A53_电压稳定时间裕量寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A53_PMUHOLDTIME_UNION */
#define SOC_PMCTRL_A53_PMUHOLDTIME_ADDR(base)         ((base) + (0x0E4))

/* 寄存器说明：A53_PMU选择寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A53_PMUSEL_UNION */
#define SOC_PMCTRL_A53_PMUSEL_ADDR(base)              ((base) + (0x0E8))

/* 寄存器说明：A53_CPU AVS使能寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPUAVSEN_UNION */
#define SOC_PMCTRL_A53_CPUAVSEN_ADDR(base)            ((base) + (0x0F0))

/* 寄存器说明：A53_CPU AVS参数模式寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPUAVSPARAMOD_UNION */
#define SOC_PMCTRL_A53_CPUAVSPARAMOD_ADDR(base)       ((base) + (0x0F4))

/* 寄存器说明：A53_CPU AVS参数寄存器0。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPUAVSPARA0_UNION */
#define SOC_PMCTRL_A53_CPUAVSPARA0_ADDR(base)         ((base) + (0x0F8))

/* 寄存器说明：A53_CPU AVS参数寄存器1。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPUAVSPARA1_UNION */
#define SOC_PMCTRL_A53_CPUAVSPARA1_ADDR(base)         ((base) + (0x0FC))

/* 寄存器说明：A53_CPU AVS参数寄存器2。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPUAVSPARA2_UNION */
#define SOC_PMCTRL_A53_CPUAVSPARA2_ADDR(base)         ((base) + (0x100))

/* 寄存器说明：A53_CPU AVS参数寄存器3。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPUAVSPARA3_UNION */
#define SOC_PMCTRL_A53_CPUAVSPARA3_ADDR(base)         ((base) + (0x104))

/* 寄存器说明：A53_CPU AVS参数寄存器4。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPUAVSPARA4_UNION */
#define SOC_PMCTRL_A53_CPUAVSPARA4_ADDR(base)         ((base) + (0x108))

/* 寄存器说明：A53_CPU AVS参数寄存器5。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPUAVSPARA5_UNION */
#define SOC_PMCTRL_A53_CPUAVSPARA5_ADDR(base)         ((base) + (0x10C))

/* 寄存器说明：A53_CPU AVS使能寄存器6。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPUAVSPARA6_UNION */
#define SOC_PMCTRL_A53_CPUAVSPARA6_ADDR(base)         ((base) + (0x110))

/* 寄存器说明：A53_CPU HPM类型选择寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPUHPMTYP_UNION */
#define SOC_PMCTRL_A53_CPUHPMTYP_ADDR(base)           ((base) + (0x114))

/* 寄存器说明：A53_CPU01 HPM使能寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPU01HPMEN_UNION */
#define SOC_PMCTRL_A53_CPU01HPMEN_ADDR(base)          ((base) + (0x118))

/* 寄存器说明：A53_CPU01 HPMX使能寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPU01HPMXEN_UNION */
#define SOC_PMCTRL_A53_CPU01HPMXEN_ADDR(base)         ((base) + (0x11C))

/* 寄存器说明：A53_CPU01 HPM OPC有效寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPU01HPMOPCVALID_UNION */
#define SOC_PMCTRL_A53_CPU01HPMOPCVALID_ADDR(base)    ((base) + (0x120))

/* 寄存器说明：A53_CPU01 HPM OPC寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPU01HPMOPC_UNION */
#define SOC_PMCTRL_A53_CPU01HPMOPC_ADDR(base)         ((base) + (0x124))

/* 寄存器说明：A53_CPU01 HPMX OPC寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPU01HPMXOPC_UNION */
#define SOC_PMCTRL_A53_CPU01HPMXOPC_ADDR(base)        ((base) + (0x128))

/* 寄存器说明：A53_CPU01 HPM PC寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPU01HPMPC_UNION */
#define SOC_PMCTRL_A53_CPU01HPMPC_ADDR(base)          ((base) + (0x12C))

/* 寄存器说明：A53_CPU23 HPM使能寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPU23HPMEN_UNION */
#define SOC_PMCTRL_A53_CPU23HPMEN_ADDR(base)          ((base) + (0x134))

/* 寄存器说明：A53_CPU23 HPMX使能寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPU23HPMXEN_UNION */
#define SOC_PMCTRL_A53_CPU23HPMXEN_ADDR(base)         ((base) + (0x138))

/* 寄存器说明：A53_CPU23 HPM OPC有效寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPU23HPMOPCVALID_UNION */
#define SOC_PMCTRL_A53_CPU23HPMOPCVALID_ADDR(base)    ((base) + (0x13C))

/* 寄存器说明：A53_CPU23 HPM OPC寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPU23HPMOPC_UNION */
#define SOC_PMCTRL_A53_CPU23HPMOPC_ADDR(base)         ((base) + (0x140))

/* 寄存器说明：A53_CPU23 HPMX OPC寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPU23HPMXOPC_UNION */
#define SOC_PMCTRL_A53_CPU23HPMXOPC_ADDR(base)        ((base) + (0x144))

/* 寄存器说明：A53_CPU23 HPM PC寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPU23HPMPC_UNION */
#define SOC_PMCTRL_A53_CPU23HPMPC_ADDR(base)          ((base) + (0x148))

/* 寄存器说明：A53_CPU HPM时钟分频寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPUHPMCLKDIV_UNION */
#define SOC_PMCTRL_A53_CPUHPMCLKDIV_ADDR(base)        ((base) + (0x150))

/* 寄存器说明：A53_CPU AVS电压控制寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A53_CPUAVSVOLIDX_UNION */
#define SOC_PMCTRL_A53_CPUAVSVOLIDX_ADDR(base)        ((base) + (0x154))

/* 寄存器说明：A57_CPU DVFS模式寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPUDVFSMOD_UNION */
#define SOC_PMCTRL_A57_CPUDVFSMOD_ADDR(base)          ((base) + (0x158))

/* 寄存器说明：A57_CPU 时钟来源选择寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPUCLKSEL_UNION */
#define SOC_PMCTRL_A57_CPUCLKSEL_ADDR(base)           ((base) + (0x15C))

/* 寄存器说明：A57_CPU DVFS使能寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPUDVFSEN_UNION */
#define SOC_PMCTRL_A57_CPUDVFSEN_ADDR(base)           ((base) + (0x160))

/* 寄存器说明：A57_CPU PLL选择寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPUPLLSEL_UNION */
#define SOC_PMCTRL_A57_CPUPLLSEL_ADDR(base)           ((base) + (0x164))

/* 寄存器说明：A57_CPU时钟分频寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPUCLKDIV_UNION */
#define SOC_PMCTRL_A57_CPUCLKDIV_ADDR(base)           ((base) + (0x168))

/* 寄存器说明：A57_CPU DVFS启动寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPUDVFSSTART_UNION */
#define SOC_PMCTRL_A57_CPUDVFSSTART_ADDR(base)        ((base) + (0x16C))

/* 寄存器说明：A57_CPU频率Profile寄存器0。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPUCLKPROFILE0_UNION */
#define SOC_PMCTRL_A57_CPUCLKPROFILE0_ADDR(base)      ((base) + (0x170))

/* 寄存器说明：A57_CPU频率Profile寄存器0_1。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPUCLKPROFILE0_1_UNION */
#define SOC_PMCTRL_A57_CPUCLKPROFILE0_1_ADDR(base)    ((base) + (0x174))

/* 寄存器说明：A57_CPU频率Profile寄存器1。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPUCLKPROFILE1_UNION */
#define SOC_PMCTRL_A57_CPUCLKPROFILE1_ADDR(base)      ((base) + (0x178))

/* 寄存器说明：A57_CPU DVFS时的调压模式寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPUVOLMOD_UNION */
#define SOC_PMCTRL_A57_CPUVOLMOD_ADDR(base)           ((base) + (0x17C))

/* 寄存器说明：A57_CPU电压Profile寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPUVOLPROFILE_UNION */
#define SOC_PMCTRL_A57_CPUVOLPROFILE_ADDR(base)       ((base) + (0x180))

/* 寄存器说明：A57_CPU DVFS时的相位模式寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPUPHASEMOD_UNION */
#define SOC_PMCTRL_A57_CPUPHASEMOD_ADDR(base)         ((base) + (0x188))

/* 寄存器说明：A57_CPU相位Profile寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPUPHASEPROFILE_UNION */
#define SOC_PMCTRL_A57_CPUPHASEPROFILE_ADDR(base)     ((base) + (0x18C))

/* 寄存器说明：A57_CPU电压/相位配置选择寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPUVOLPHASESEL_UNION */
#define SOC_PMCTRL_A57_CPUVOLPHASESEL_ADDR(base)      ((base) + (0x190))

/* 寄存器说明：A57_电压上升一档稳定步长时间寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A57_VOLUPSTEPTIME_UNION */
#define SOC_PMCTRL_A57_VOLUPSTEPTIME_ADDR(base)       ((base) + (0x194))

/* 寄存器说明：A57_电压下降一档稳定步长时间寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A57_VOLDNSTEPTIME_UNION */
#define SOC_PMCTRL_A57_VOLDNSTEPTIME_ADDR(base)       ((base) + (0x198))

/* 寄存器说明：A57_ DVFS时改变电压相位的上升稳定时间寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A57_PHASEUPTIME_UNION */
#define SOC_PMCTRL_A57_PHASEUPTIME_ADDR(base)         ((base) + (0x19C))

/* 寄存器说明：A57_ DVFS时改变电压相位的下降稳定时间寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A57_PHASEDNTIME_UNION */
#define SOC_PMCTRL_A57_PHASEDNTIME_ADDR(base)         ((base) + (0x1A0))

/* 寄存器说明：A57_电压稳定时间裕量寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A57_PMUHOLDTIME_UNION */
#define SOC_PMCTRL_A57_PMUHOLDTIME_ADDR(base)         ((base) + (0x1A4))

/* 寄存器说明：A57_PMU选择寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A57_PMUSEL_UNION */
#define SOC_PMCTRL_A57_PMUSEL_ADDR(base)              ((base) + (0x1A8))

/* 寄存器说明：A57_CPU AVS使能寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPUAVSEN_UNION */
#define SOC_PMCTRL_A57_CPUAVSEN_ADDR(base)            ((base) + (0x1B0))

/* 寄存器说明：A57_CPU AVS参数模式寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPUAVSPARAMOD_UNION */
#define SOC_PMCTRL_A57_CPUAVSPARAMOD_ADDR(base)       ((base) + (0x1B4))

/* 寄存器说明：A57_CPU AVS参数寄存器0。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPUAVSPARA0_UNION */
#define SOC_PMCTRL_A57_CPUAVSPARA0_ADDR(base)         ((base) + (0x1B8))

/* 寄存器说明：A57_CPU AVS参数寄存器1。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPUAVSPARA1_UNION */
#define SOC_PMCTRL_A57_CPUAVSPARA1_ADDR(base)         ((base) + (0x1BC))

/* 寄存器说明：A57_CPU AVS参数寄存器2。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPUAVSPARA2_UNION */
#define SOC_PMCTRL_A57_CPUAVSPARA2_ADDR(base)         ((base) + (0x1C0))

/* 寄存器说明：A57_CPU AVS参数寄存器3。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPUAVSPARA3_UNION */
#define SOC_PMCTRL_A57_CPUAVSPARA3_ADDR(base)         ((base) + (0x1C4))

/* 寄存器说明：A57_CPU AVS参数寄存器4。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPUAVSPARA4_UNION */
#define SOC_PMCTRL_A57_CPUAVSPARA4_ADDR(base)         ((base) + (0x1C8))

/* 寄存器说明：A57_CPU AVS参数寄存器5。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPUAVSPARA5_UNION */
#define SOC_PMCTRL_A57_CPUAVSPARA5_ADDR(base)         ((base) + (0x1CC))

/* 寄存器说明：A57_CPU AVS使能寄存器6。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPUAVSPARA6_UNION */
#define SOC_PMCTRL_A57_CPUAVSPARA6_ADDR(base)         ((base) + (0x1D0))

/* 寄存器说明：A57_CPU01 HPM类型选择寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPUHPMTYP_UNION */
#define SOC_PMCTRL_A57_CPUHPMTYP_ADDR(base)           ((base) + (0x1D4))

/* 寄存器说明：A57_CPU01 HPM使能寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPU01HPMEN_UNION */
#define SOC_PMCTRL_A57_CPU01HPMEN_ADDR(base)          ((base) + (0x1D8))

/* 寄存器说明：A57_CPU01 HPMX使能寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPU01HPMXEN_UNION */
#define SOC_PMCTRL_A57_CPU01HPMXEN_ADDR(base)         ((base) + (0x1DC))

/* 寄存器说明：A57_CPU01 HPM OPC有效寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPU01HPMOPCVALID_UNION */
#define SOC_PMCTRL_A57_CPU01HPMOPCVALID_ADDR(base)    ((base) + (0x1E0))

/* 寄存器说明：A57_CPU01 HPM OPC寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPU01HPMOPC_UNION */
#define SOC_PMCTRL_A57_CPU01HPMOPC_ADDR(base)         ((base) + (0x1E4))

/* 寄存器说明：A57_CPU01 HPMX OPC寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPU01HPMXOPC_UNION */
#define SOC_PMCTRL_A57_CPU01HPMXOPC_ADDR(base)        ((base) + (0x1E8))

/* 寄存器说明：A57_CPU HPM PC寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPU01HPMPC_UNION */
#define SOC_PMCTRL_A57_CPU01HPMPC_ADDR(base)          ((base) + (0x1EC))

/* 寄存器说明：A57_CPU23 HPM使能寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPU23HPMEN_UNION */
#define SOC_PMCTRL_A57_CPU23HPMEN_ADDR(base)          ((base) + (0x1F4))

/* 寄存器说明：A57_CPU23 HPMX使能寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPU23HPMXEN_UNION */
#define SOC_PMCTRL_A57_CPU23HPMXEN_ADDR(base)         ((base) + (0x1F8))

/* 寄存器说明：A57_CPU23 HPM OPC有效寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPU23HPMOPCVALID_UNION */
#define SOC_PMCTRL_A57_CPU23HPMOPCVALID_ADDR(base)    ((base) + (0x1FC))

/* 寄存器说明：A57_CPU23 HPM OPC寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPU23HPMOPC_UNION */
#define SOC_PMCTRL_A57_CPU23HPMOPC_ADDR(base)         ((base) + (0x200))

/* 寄存器说明：A57_CPU23 HPMX OPC寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPU23HPMXOPC_UNION */
#define SOC_PMCTRL_A57_CPU23HPMXOPC_ADDR(base)        ((base) + (0x204))

/* 寄存器说明：A57_CPU HPM PC寄存器1。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPU23HPMPC_UNION */
#define SOC_PMCTRL_A57_CPU23HPMPC_ADDR(base)          ((base) + (0x208))

/* 寄存器说明：A57_CPU HPM时钟分频寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPUHPMCLKDIV_UNION */
#define SOC_PMCTRL_A57_CPUHPMCLKDIV_ADDR(base)        ((base) + (0x210))

/* 寄存器说明：A57_CPU AVS电压控制寄存器。
   位域定义UNION结构:  SOC_PMCTRL_A57_CPUAVSVOLIDX_UNION */
#define SOC_PMCTRL_A57_CPUAVSVOLIDX_ADDR(base)        ((base) + (0x214))

/* 寄存器说明：G3D AXI时钟选择寄存器。
   位域定义UNION结构:  SOC_PMCTRL_G3DCLKSEL_UNION */
#define SOC_PMCTRL_G3DCLKSEL_ADDR(base)               ((base) + (0x220))

/* 寄存器说明：G3D AXI时钟分频寄存器。
   位域定义UNION结构:  SOC_PMCTRL_G3DCLKDIV_UNION */
#define SOC_PMCTRL_G3DCLKDIV_ADDR(base)               ((base) + (0x224))

/* 寄存器说明：G3D DVFS使能寄存器。
   位域定义UNION结构:  SOC_PMCTRL_G3DDVFSEN_UNION */
#define SOC_PMCTRL_G3DDVFSEN_ADDR(base)               ((base) + (0x228))

/* 寄存器说明：G3D DVFS启动寄存器。
   位域定义UNION结构:  SOC_PMCTRL_G3DDVFSSTART_UNION */
#define SOC_PMCTRL_G3DDVFSSTART_ADDR(base)            ((base) + (0x22C))

/* 寄存器说明：G3D频率Profile寄存器。
   位域定义UNION结构:  SOC_PMCTRL_G3DCLKPROFILE_UNION */
#define SOC_PMCTRL_G3DCLKPROFILE_ADDR(base)           ((base) + (0x230))

/* 寄存器说明：G3D DVFS调压模式寄存器。
   位域定义UNION结构:  SOC_PMCTRL_G3DVOLMOD_UNION */
#define SOC_PMCTRL_G3DVOLMOD_ADDR(base)               ((base) + (0x234))

/* 寄存器说明：G3D电压Profile寄存器。
   位域定义UNION结构:  SOC_PMCTRL_G3DVOLPROFILE_UNION */
#define SOC_PMCTRL_G3DVOLPROFILE_ADDR(base)           ((base) + (0x238))

/* 寄存器说明：G3D DVFS改变电压相位模式寄存器。
   位域定义UNION结构:  SOC_PMCTRL_G3DPHASEMOD_UNION */
#define SOC_PMCTRL_G3DPHASEMOD_ADDR(base)             ((base) + (0x240))

/* 寄存器说明：G3D相位Profile寄存器。
   位域定义UNION结构:  SOC_PMCTRL_G3DPHASEPROFILE_UNION */
#define SOC_PMCTRL_G3DPHASEPROFILE_ADDR(base)         ((base) + (0x244))

/* 寄存器说明：G3D电压/相位配置选择寄存器。
   位域定义UNION结构:  SOC_PMCTRL_G3DVOLPHASESEL_UNION */
#define SOC_PMCTRL_G3DVOLPHASESEL_ADDR(base)          ((base) + (0x248))

/* 寄存器说明：G3D输出PMU选择寄存器。
   位域定义UNION结构:  SOC_PMCTRL_G3DPMUSEL_UNION */
#define SOC_PMCTRL_G3DPMUSEL_ADDR(base)               ((base) + (0x24C))

/* 寄存器说明：G3D电压上升一档稳定步长时间寄存器。
   位域定义UNION结构:  SOC_PMCTRL_G3DVOLUPSTEPTIME_UNION */
#define SOC_PMCTRL_G3DVOLUPSTEPTIME_ADDR(base)        ((base) + (0x250))

/* 寄存器说明：G3D电压下降一档稳定步长时间寄存器。
   位域定义UNION结构:  SOC_PMCTRL_G3DVOLDNSTEPTIME_UNION */
#define SOC_PMCTRL_G3DVOLDNSTEPTIME_ADDR(base)        ((base) + (0x254))

/* 寄存器说明：G3D DVFS时改变电压相位的上升稳定时间寄存器。
   位域定义UNION结构:  SOC_PMCTRL_G3DPHASEUPTIME_UNION */
#define SOC_PMCTRL_G3DPHASEUPTIME_ADDR(base)          ((base) + (0x258))

/* 寄存器说明：G3D DVFS时改变电压相位的下降稳定时间寄存器。
   位域定义UNION结构:  SOC_PMCTRL_G3DPHASEDNTIME_UNION */
#define SOC_PMCTRL_G3DPHASEDNTIME_ADDR(base)          ((base) + (0x25C))

/* 寄存器说明：G3D电压稳定时间裕量寄存器。
   位域定义UNION结构:  SOC_PMCTRL_G3DPMUHOLDTIME_UNION */
#define SOC_PMCTRL_G3DPMUHOLDTIME_ADDR(base)          ((base) + (0x260))

/* 寄存器说明：G3D HPM硬件控制bypass寄存器。
   位域定义UNION结构:  SOC_PMCTRL_G3DHPMBYPASS_UNION */
#define SOC_PMCTRL_G3DHPMBYPASS_ADDR(base)            ((base) + (0x264))

/* 寄存器说明：G3D自动分频bypass控制寄存器。
   位域定义UNION结构:  SOC_PMCTRL_G3DAUTOCLKDIVBYPASS_UNION */
#define SOC_PMCTRL_G3DAUTOCLKDIVBYPASS_ADDR(base)     ((base) + (0x268))

/* 寄存器说明：G3D AVS使能寄存器。
   位域定义UNION结构:  SOC_PMCTRL_G3DAVSEN_UNION */
#define SOC_PMCTRL_G3DAVSEN_ADDR(base)                ((base) + (0x270))

/* 寄存器说明：G3D AVS参数模式寄存器。
   位域定义UNION结构:  SOC_PMCTRL_G3DAVSPARAMOD_UNION */
#define SOC_PMCTRL_G3DAVSPARAMOD_ADDR(base)           ((base) + (0x274))

/* 寄存器说明：G3D AVS参数寄存器0。
   位域定义UNION结构:  SOC_PMCTRL_G3DAVSPARA0_UNION */
#define SOC_PMCTRL_G3DAVSPARA0_ADDR(base)             ((base) + (0x278))

/* 寄存器说明：G3D AVS参数寄存器1。
   位域定义UNION结构:  SOC_PMCTRL_G3DAVSPARA1_UNION */
#define SOC_PMCTRL_G3DAVSPARA1_ADDR(base)             ((base) + (0x27C))

/* 寄存器说明：G3D AVS参数寄存器2。
   位域定义UNION结构:  SOC_PMCTRL_G3DAVSPARA2_UNION */
#define SOC_PMCTRL_G3DAVSPARA2_ADDR(base)             ((base) + (0x280))

/* 寄存器说明：G3D AVS参数寄存器3。
   位域定义UNION结构:  SOC_PMCTRL_G3DAVSPARA3_UNION */
#define SOC_PMCTRL_G3DAVSPARA3_ADDR(base)             ((base) + (0x284))

/* 寄存器说明：G3D AVS参数寄存器4。
   位域定义UNION结构:  SOC_PMCTRL_G3DAVSPARA4_UNION */
#define SOC_PMCTRL_G3DAVSPARA4_ADDR(base)             ((base) + (0x288))

/* 寄存器说明：G3D AVS参数寄存器5。
   位域定义UNION结构:  SOC_PMCTRL_G3DAVSPARA5_UNION */
#define SOC_PMCTRL_G3DAVSPARA5_ADDR(base)             ((base) + (0x28C))

/* 寄存器说明：G3D AVS参数寄存器6。
   位域定义UNION结构:  SOC_PMCTRL_G3DAVSPARA6_UNION */
#define SOC_PMCTRL_G3DAVSPARA6_ADDR(base)             ((base) + (0x290))

/* 寄存器说明：G3D HPM类型选择寄存器。
   位域定义UNION结构:  SOC_PMCTRL_G3DHPMTYP_UNION */
#define SOC_PMCTRL_G3DHPMTYP_ADDR(base)               ((base) + (0x294))

/* 寄存器说明：G3D HPM使能寄存器。
   位域定义UNION结构:  SOC_PMCTRL_G3DHPMEN_UNION */
#define SOC_PMCTRL_G3DHPMEN_ADDR(base)                ((base) + (0x298))

/* 寄存器说明：G3D HPMX使能寄存器。
   位域定义UNION结构:  SOC_PMCTRL_G3DHPMXEN_UNION */
#define SOC_PMCTRL_G3DHPMXEN_ADDR(base)               ((base) + (0x29C))

/* 寄存器说明：G3D HPM OPC有效寄存器。
   位域定义UNION结构:  SOC_PMCTRL_G3DHPMOPCVALID_UNION */
#define SOC_PMCTRL_G3DHPMOPCVALID_ADDR(base)          ((base) + (0x2A0))

/* 寄存器说明：G3D HPM OPC寄存器。
   位域定义UNION结构:  SOC_PMCTRL_G3DHPMOPC_UNION */
#define SOC_PMCTRL_G3DHPMOPC_ADDR(base)               ((base) + (0x2A4))

/* 寄存器说明：G3D HPMX OPC寄存器。
   位域定义UNION结构:  SOC_PMCTRL_G3DHPMXOPC_UNION */
#define SOC_PMCTRL_G3DHPMXOPC_ADDR(base)              ((base) + (0x2A8))

/* 寄存器说明：G3D HPM PC寄存器。
   位域定义UNION结构:  SOC_PMCTRL_G3DHPMPC_UNION */
#define SOC_PMCTRL_G3DHPMPC_ADDR(base)                ((base) + (0x2AC))

/* 寄存器说明：G3D HPM使能寄存器1。
   位域定义UNION结构:  SOC_PMCTRL_G3DHPMEN1_UNION */
#define SOC_PMCTRL_G3DHPMEN1_ADDR(base)               ((base) + (0x2B4))

/* 寄存器说明：G3D HPMX使能寄存器1。
   位域定义UNION结构:  SOC_PMCTRL_G3DHPMXEN1_UNION */
#define SOC_PMCTRL_G3DHPMXEN1_ADDR(base)              ((base) + (0x2B8))

/* 寄存器说明：G3D HPM OPC有效寄存器1。
   位域定义UNION结构:  SOC_PMCTRL_G3DHPMOPCVALID1_UNION */
#define SOC_PMCTRL_G3DHPMOPCVALID1_ADDR(base)         ((base) + (0x2BC))

/* 寄存器说明：G3D HPM OPC寄存器1。
   位域定义UNION结构:  SOC_PMCTRL_G3DHPMOPC1_UNION */
#define SOC_PMCTRL_G3DHPMOPC1_ADDR(base)              ((base) + (0x2C0))

/* 寄存器说明：G3D HPMX OPC寄存器1。
   位域定义UNION结构:  SOC_PMCTRL_G3DHPMXOPC1_UNION */
#define SOC_PMCTRL_G3DHPMXOPC1_ADDR(base)             ((base) + (0x2C4))

/* 寄存器说明：G3D HPM PC寄存器1。
   位域定义UNION结构:  SOC_PMCTRL_G3DHPMPC1_UNION */
#define SOC_PMCTRL_G3DHPMPC1_ADDR(base)               ((base) + (0x2C8))

/* 寄存器说明：G3D HPM屏蔽状态寄存器。
   位域定义UNION结构:  SOC_PMCTRL_G3DHPMMASKSTAT_UNION */
#define SOC_PMCTRL_G3DHPMMASKSTAT_ADDR(base)          ((base) + (0x2E8))

/* 寄存器说明：G3D HPM时钟分频寄存器。
   位域定义UNION结构:  SOC_PMCTRL_G3DHPMCLKDIV_UNION */
#define SOC_PMCTRL_G3DHPMCLKDIV_ADDR(base)            ((base) + (0x2EC))

/* 寄存器说明：G3D AVS电压控制寄存器。
   位域定义UNION结构:  SOC_PMCTRL_G3DAVSVOLIDX_UNION */
#define SOC_PMCTRL_G3DAVSVOLIDX_ADDR(base)            ((base) + (0x2F0))

/* 寄存器说明：DDRC LP控制寄存器。
   位域定义UNION结构:  SOC_PMCTRL_DDRLPCTRL_UNION */
#define SOC_PMCTRL_DDRLPCTRL_ADDR(base)               ((base) + (0x30C))

/* 寄存器说明：PLL Lock稳定时间寄存器。
   位域定义UNION结构:  SOC_PMCTRL_PLLLOCKTIME_UNION */
#define SOC_PMCTRL_PLLLOCKTIME_ADDR(base)             ((base) + (0x320))

/* 寄存器说明：PLL稳定模式寄存器。
   位域定义UNION结构:  SOC_PMCTRL_PLLLOCKMOD_UNION */
#define SOC_PMCTRL_PLLLOCKMOD_ADDR(base)              ((base) + (0x324))

/* 寄存器说明：AVS运行轮数寄存器。
   位域定义UNION结构:  SOC_PMCTRL_AVSRUNROUND_UNION */
#define SOC_PMCTRL_AVSRUNROUND_ADDR(base)             ((base) + (0x32C))

/* 寄存器说明：PMUSSI AVS使能信号寄存器。
   位域定义UNION结构:  SOC_PMCTRL_PMUSSIAVSEN_UNION */
#define SOC_PMCTRL_PMUSSIAVSEN_ADDR(base)             ((base) + (0x330))

/* 寄存器说明：外设通用控制寄存器0。
   位域定义UNION结构:  SOC_PMCTRL_PERI_CTRL0_UNION */
#define SOC_PMCTRL_PERI_CTRL0_ADDR(base)              ((base) + (0x340))

/* 寄存器说明：外设通用控制寄存器1。
   位域定义UNION结构:  SOC_PMCTRL_PERI_CTRL1_UNION */
#define SOC_PMCTRL_PERI_CTRL1_ADDR(base)              ((base) + (0x344))

/* 寄存器说明：外设通用控制寄存器2。
   位域定义UNION结构:  SOC_PMCTRL_PERI_CTRL2_UNION */
#define SOC_PMCTRL_PERI_CTRL2_ADDR(base)              ((base) + (0x348))

/* 寄存器说明：外设通用控制寄存器3。
   位域定义UNION结构:  SOC_PMCTRL_PERI_CTRL3_UNION */
#define SOC_PMCTRL_PERI_CTRL3_ADDR(base)              ((base) + (0x34C))

/* 寄存器说明：外设通用控制寄存器4。
   位域定义UNION结构:  SOC_PMCTRL_PERI_CTRL4_UNION */
#define SOC_PMCTRL_PERI_CTRL4_ADDR(base)              ((base) + (0x350))

/* 寄存器说明：外设通用控制寄存器5。
   位域定义UNION结构:  SOC_PMCTRL_PERI_CTRL5_UNION */
#define SOC_PMCTRL_PERI_CTRL5_ADDR(base)              ((base) + (0x354))

/* 寄存器说明：外设通用控制寄存器6。
   位域定义UNION结构:  SOC_PMCTRL_PERI_CTRL6_UNION */
#define SOC_PMCTRL_PERI_CTRL6_ADDR(base)              ((base) + (0x358))

/* 寄存器说明：外设通用控制寄存器7。
   位域定义UNION结构:  SOC_PMCTRL_PERI_CTRL7_UNION */
#define SOC_PMCTRL_PERI_CTRL7_ADDR(base)              ((base) + (0x35C))

/* 寄存器说明：外设通用状态寄存器0。
   位域定义UNION结构:  SOC_PMCTRL_PERI_STAT0_UNION */
#define SOC_PMCTRL_PERI_STAT0_ADDR(base)              ((base) + (0x360))

/* 寄存器说明：外设通用状态寄存器1。
   位域定义UNION结构:  SOC_PMCTRL_PERI_STAT1_UNION */
#define SOC_PMCTRL_PERI_STAT1_ADDR(base)              ((base) + (0x364))

/* 寄存器说明：外设通用状态寄存器2。
   位域定义UNION结构:  SOC_PMCTRL_PERI_STAT2_UNION */
#define SOC_PMCTRL_PERI_STAT2_ADDR(base)              ((base) + (0x368))

/* 寄存器说明：外设通用状态寄存器3。
   位域定义UNION结构:  SOC_PMCTRL_PERI_STAT3_UNION */
#define SOC_PMCTRL_PERI_STAT3_ADDR(base)              ((base) + (0x36C))

/* 寄存器说明：外设通用状态寄存器4。
   位域定义UNION结构:  SOC_PMCTRL_PERI_STAT4_UNION */
#define SOC_PMCTRL_PERI_STAT4_ADDR(base)              ((base) + (0x370))

/* 寄存器说明：外设通用状态寄存器5。
   位域定义UNION结构:  SOC_PMCTRL_PERI_STAT5_UNION */
#define SOC_PMCTRL_PERI_STAT5_ADDR(base)              ((base) + (0x374))

/* 寄存器说明：外设通用状态寄存器6。
   位域定义UNION结构:  SOC_PMCTRL_PERI_STAT6_UNION */
#define SOC_PMCTRL_PERI_STAT6_ADDR(base)              ((base) + (0x378))

/* 寄存器说明：外设通用状态寄存器7。
   位域定义UNION结构:  SOC_PMCTRL_PERI_STAT7_UNION */
#define SOC_PMCTRL_PERI_STAT7_ADDR(base)              ((base) + (0x37C))

/* 寄存器说明：NOC低功耗请求信号寄存器。
   位域定义UNION结构:  SOC_PMCTRL_NOC_POWER_IDLEREQ_UNION */
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_ADDR(base)       ((base) + (0x380))

/* 寄存器说明：NOC低功耗响应寄存器。
   位域定义UNION结构:  SOC_PMCTRL_NOC_POWER_IDLEACK_UNION */
#define SOC_PMCTRL_NOC_POWER_IDLEACK_ADDR(base)       ((base) + (0x384))

/* 寄存器说明：NOC低功耗状态寄存器。
   位域定义UNION结构:  SOC_PMCTRL_NOC_POWER_IDLE_UNION */
#define SOC_PMCTRL_NOC_POWER_IDLE_ADDR(base)          ((base) + (0x388))

/* 寄存器说明：外设中断屏蔽寄存器0。
   位域定义UNION结构:  SOC_PMCTRL_PERI_INT0_MASK_UNION */
#define SOC_PMCTRL_PERI_INT0_MASK_ADDR(base)          ((base) + (0x3A0))

/* 寄存器说明：外设中断状态寄存器0。
   位域定义UNION结构:  SOC_PMCTRL_PERI_INT0_STAT_UNION */
#define SOC_PMCTRL_PERI_INT0_STAT_ADDR(base)          ((base) + (0x3A4))

/* 寄存器说明：外设中断屏蔽寄存器1。
   位域定义UNION结构:  SOC_PMCTRL_PERI_INT1_MASK_UNION */
#define SOC_PMCTRL_PERI_INT1_MASK_ADDR(base)          ((base) + (0x3A8))

/* 寄存器说明：外设中断状态寄存器1。
   位域定义UNION结构:  SOC_PMCTRL_PERI_INT1_STAT_UNION */
#define SOC_PMCTRL_PERI_INT1_STAT_ADDR(base)          ((base) + (0x3AC))

/* 寄存器说明：外设中断屏蔽寄存器2。
   位域定义UNION结构:  SOC_PMCTRL_PERI_INT2_MASK_UNION */
#define SOC_PMCTRL_PERI_INT2_MASK_ADDR(base)          ((base) + (0x3B0))

/* 寄存器说明：外设中断状态寄存器2。
   位域定义UNION结构:  SOC_PMCTRL_PERI_INT2_STAT_UNION */
#define SOC_PMCTRL_PERI_INT2_STAT_ADDR(base)          ((base) + (0x3B4))

/* 寄存器说明：外设中断屏蔽寄存器3。
   位域定义UNION结构:  SOC_PMCTRL_PERI_INT3_MASK_UNION */
#define SOC_PMCTRL_PERI_INT3_MASK_ADDR(base)          ((base) + (0x3B8))

/* 寄存器说明：外设中断状态寄存器3。
   位域定义UNION结构:  SOC_PMCTRL_PERI_INT3_STAT_UNION */
#define SOC_PMCTRL_PERI_INT3_STAT_ADDR(base)          ((base) + (0x3BC))

/* 寄存器说明：Vsensor控制使能寄存器。
   位域定义UNION结构:  SOC_PMCTRL_VSENSOR_CTRL_EN_1_UNION */
#define SOC_PMCTRL_VSENSOR_CTRL_EN_1_ADDR(base)       ((base) + (0x3D0))

/* 寄存器说明：Vsensor bypass寄存器。
   位域定义UNION结构:  SOC_PMCTRL_VSENSOR_CTRL_BYPASS_1_UNION */
#define SOC_PMCTRL_VSENSOR_CTRL_BYPASS_1_ADDR(base)   ((base) + (0x3D4))

/* 寄存器说明：Vsensor控制配置寄存器。
   位域定义UNION结构:  SOC_PMCTRL_VSENSOR_CTRL_1_UNION */
#define SOC_PMCTRL_VSENSOR_CTRL_1_ADDR(base)          ((base) + (0x3D8))

/* 寄存器说明：Vsensor计数控制寄存器。
   位域定义UNION结构:  SOC_PMCTRL_VSENSOR_CNT_1_UNION */
#define SOC_PMCTRL_VSENSOR_CNT_1_ADDR(base)           ((base) + (0x3DC))

/* 寄存器说明：Vsensor参考码字寄存器。
   位域定义UNION结构:  SOC_PMCTRL_VSENSOR_REF_CODE_1_UNION */
#define SOC_PMCTRL_VSENSOR_REF_CODE_1_ADDR(base)      ((base) + (0x3E0))

/* 寄存器说明：Vsensor抽头控制寄存器。
   位域定义UNION结构:  SOC_PMCTRL_VSENSOR_CALI_CODE_1_UNION */
#define SOC_PMCTRL_VSENSOR_CALI_CODE_1_ADDR(base)     ((base) + (0x3E4))

/* 寄存器说明：Vsensor码字寄存器。
   位域定义UNION结构:  SOC_PMCTRL_VSENSOR_CODE_1_UNION */
#define SOC_PMCTRL_VSENSOR_CODE_1_ADDR(base)          ((base) + (0x3E8))

/* 寄存器说明：Vsensor中断状态寄存器。
   位域定义UNION结构:  SOC_PMCTRL_VSENSOR_INTSTAT_1_UNION */
#define SOC_PMCTRL_VSENSOR_INTSTAT_1_ADDR(base)       ((base) + (0x3EC))

/* 寄存器说明：Vsensor中断状态寄存器。
   位域定义UNION结构:  SOC_PMCTRL_VSENSOR_D_RATE_1_UNION */
#define SOC_PMCTRL_VSENSOR_D_RATE_1_ADDR(base)        ((base) + (0x3F0))

/* 寄存器说明：Vsensor控制使能寄存器。
   位域定义UNION结构:  SOC_PMCTRL_VSENSOR_CTRL_EN_0_UNION */
#define SOC_PMCTRL_VSENSOR_CTRL_EN_0_ADDR(base)       ((base) + (0x3F4))

/* 寄存器说明：Vsensor bypass寄存器。
   位域定义UNION结构:  SOC_PMCTRL_VSENSOR_CTRL_BYPASS_0_UNION */
#define SOC_PMCTRL_VSENSOR_CTRL_BYPASS_0_ADDR(base)   ((base) + (0x3F8))

/* 寄存器说明：Vsensor控制配置寄存器。
   位域定义UNION结构:  SOC_PMCTRL_VSENSOR_CTRL_0_UNION */
#define SOC_PMCTRL_VSENSOR_CTRL_0_ADDR(base)          ((base) + (0x3FC))

/* 寄存器说明：Vsensor计数控制寄存器。
   位域定义UNION结构:  SOC_PMCTRL_VSENSOR_CNT_0_UNION */
#define SOC_PMCTRL_VSENSOR_CNT_0_ADDR(base)           ((base) + (0x400))

/* 寄存器说明：Vsensor参考码字寄存器。
   位域定义UNION结构:  SOC_PMCTRL_VSENSOR_REF_CODE_0_UNION */
#define SOC_PMCTRL_VSENSOR_REF_CODE_0_ADDR(base)      ((base) + (0x404))

/* 寄存器说明：Vsensor抽头控制寄存器。
   位域定义UNION结构:  SOC_PMCTRL_VSENSOR_CALI_CODE_0_UNION */
#define SOC_PMCTRL_VSENSOR_CALI_CODE_0_ADDR(base)     ((base) + (0x408))

/* 寄存器说明：Vsensor码字寄存器。
   位域定义UNION结构:  SOC_PMCTRL_VSENSOR_CODE_0_UNION */
#define SOC_PMCTRL_VSENSOR_CODE_0_ADDR(base)          ((base) + (0x40C))

/* 寄存器说明：Vsensor中断状态寄存器。
   位域定义UNION结构:  SOC_PMCTRL_VSENSOR_INTSTAT_0_UNION */
#define SOC_PMCTRL_VSENSOR_INTSTAT_0_ADDR(base)       ((base) + (0x410))

/* 寄存器说明：Vsensor中断状态寄存器。
   位域定义UNION结构:  SOC_PMCTRL_VSENSOR_D_RATE_0_UNION */
#define SOC_PMCTRL_VSENSOR_D_RATE_0_ADDR(base)        ((base) + (0x414))

/* 寄存器说明：PERI HPM使能寄存器。
   位域定义UNION结构:  SOC_PMCTRL_PERIHPMEN_UNION */
#define SOC_PMCTRL_PERIHPMEN_ADDR(base)               ((base) + (0x430))

/* 寄存器说明：PERI HPMX使能寄存器。
   位域定义UNION结构:  SOC_PMCTRL_PERIHPMXEN_UNION */
#define SOC_PMCTRL_PERIHPMXEN_ADDR(base)              ((base) + (0x434))

/* 寄存器说明：PERI HPM OPC有效寄存器。
   位域定义UNION结构:  SOC_PMCTRL_PERIHPMOPCVALID_UNION */
#define SOC_PMCTRL_PERIHPMOPCVALID_ADDR(base)         ((base) + (0x438))

/* 寄存器说明：PERI HPM OPC寄存器。
   位域定义UNION结构:  SOC_PMCTRL_PERIHPMOPC_UNION */
#define SOC_PMCTRL_PERIHPMOPC_ADDR(base)              ((base) + (0x43C))

/* 寄存器说明：PERI HPM时钟分频寄存器。
   位域定义UNION结构:  SOC_PMCTRL_PERIHPMCLKDIV_UNION */
#define SOC_PMCTRL_PERIHPMCLKDIV_ADDR(base)           ((base) + (0x440))

/* 寄存器说明：BOOTROM FLAG寄存器。
   位域定义UNION结构:  SOC_PMCTRL_BOOTROMFLAG_UNION */
#define SOC_PMCTRL_BOOTROMFLAG_ADDR(base)             ((base) + (0x460))

/* 寄存器说明：Vsensor控制使能寄存器。
   位域定义UNION结构:  SOC_PMCTRL_VSENSOR_CTRL_EN_2_UNION */
#define SOC_PMCTRL_VSENSOR_CTRL_EN_2_ADDR(base)       ((base) + (0x464))

/* 寄存器说明：Vsensor bypass寄存器。
   位域定义UNION结构:  SOC_PMCTRL_VSENSOR_CTRL_BYPASS_2_UNION */
#define SOC_PMCTRL_VSENSOR_CTRL_BYPASS_2_ADDR(base)   ((base) + (0x468))

/* 寄存器说明：Vsensor控制配置寄存器。
   位域定义UNION结构:  SOC_PMCTRL_VSENSOR_CTRL_2_UNION */
#define SOC_PMCTRL_VSENSOR_CTRL_2_ADDR(base)          ((base) + (0x46C))

/* 寄存器说明：Vsensor计数控制寄存器。
   位域定义UNION结构:  SOC_PMCTRL_VSENSOR_CNT_2_UNION */
#define SOC_PMCTRL_VSENSOR_CNT_2_ADDR(base)           ((base) + (0x470))

/* 寄存器说明：Vsensor参考码字寄存器。
   位域定义UNION结构:  SOC_PMCTRL_VSENSOR_REF_CODE_2_UNION */
#define SOC_PMCTRL_VSENSOR_REF_CODE_2_ADDR(base)      ((base) + (0x474))

/* 寄存器说明：Vsensor抽头控制寄存器。
   位域定义UNION结构:  SOC_PMCTRL_VSENSOR_CALI_CODE_2_UNION */
#define SOC_PMCTRL_VSENSOR_CALI_CODE_2_ADDR(base)     ((base) + (0x478))

/* 寄存器说明：Vsensor码字寄存器。
   位域定义UNION结构:  SOC_PMCTRL_VSENSOR_CODE_2_UNION */
#define SOC_PMCTRL_VSENSOR_CODE_2_ADDR(base)          ((base) + (0x47C))

/* 寄存器说明：Vsensor中断状态寄存器。
   位域定义UNION结构:  SOC_PMCTRL_VSENSOR_INTSTAT_2_UNION */
#define SOC_PMCTRL_VSENSOR_INTSTAT_2_ADDR(base)       ((base) + (0x480))

/* 寄存器说明：Vsensor中断状态寄存器。
   位域定义UNION结构:  SOC_PMCTRL_VSENSOR_D_RATE_2_UNION */
#define SOC_PMCTRL_VSENSOR_D_RATE_2_ADDR(base)        ((base) + (0x484))





/*****************************************************************************
  3 枚举定义
*****************************************************************************/



/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/



/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/



/*****************************************************************************
  7 UNION定义
*****************************************************************************/

/****************************************************************************
                     (1/1) register_define
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_PMCTRL_PMCINTEN_UNION
 结构说明  : PMCINTEN 寄存器结构定义。地址偏移量:0x000，初值:0x00000000，宽度:32
 寄存器说明: PMC中断使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_a53_cpu_dvfs_en       : 1;  /* bit[0-0]  : A53_ DVFS完成中断使能。
                                                                     0：中断屏蔽；
                                                                     1：中断使能。 */
        unsigned int  int_a53_cpu_avs_ok_en     : 1;  /* bit[1-1]  : A53 AVS电压OK中断使能。
                                                                     0：中断屏蔽；
                                                                     1：中断使能。 */
        unsigned int  int_a53_cpu_avs_up_err_en : 1;  /* bit[2-2]  : A53 AVS提升电压错误中断使能。
                                                                     0：中断屏蔽；
                                                                     1：中断使能。 */
        unsigned int  int_a53_cpu_avs_dn_err_en : 1;  /* bit[3-3]  : A53 AVS降低电压错误中断使能。
                                                                     0：中断屏蔽；
                                                                     1：中断使能。 */
        unsigned int  int_a53_cpu_avs_pc_vld_en : 1;  /* bit[4-4]  : A53 AVS输出PC中断使能。
                                                                     0：中断屏蔽；
                                                                     1：中断使能。 */
        unsigned int  int_a53_cpu_avs_idle_en   : 1;  /* bit[5-5]  : A53 CPU AVS IDLE中断使能。
                                                                     0：中断屏蔽；
                                                                     1：中断使能。 */
        unsigned int  int_a57_cpu_dvfs_en       : 1;  /* bit[6-6]  : A57_ DVFS完成中断使能。
                                                                     0：中断屏蔽；
                                                                     1：中断使能。 */
        unsigned int  int_a57_cpu_avs_ok_en     : 1;  /* bit[7-7]  : A57 AVS电压OK中断使能。
                                                                     0：中断屏蔽；
                                                                     1：中断使能。 */
        unsigned int  int_a57_cpu_avs_up_err_en : 1;  /* bit[8-8]  : A57 AVS提升电压错误中断使能。
                                                                     0：中断屏蔽；
                                                                     1：中断使能。 */
        unsigned int  int_a57_cpu_avs_dn_err_en : 1;  /* bit[9-9]  : A57 AVS降低电压错误中断使能。
                                                                     0：中断屏蔽；
                                                                     1：中断使能。 */
        unsigned int  int_a57_cpu_avs_pc_vld_en : 1;  /* bit[10-10]: A57 AVS输出PC中断使能。
                                                                     0：中断屏蔽；
                                                                     1：中断使能。 */
        unsigned int  int_a57_cpu_avs_idle_en   : 1;  /* bit[11-11]: A57 CPU AVS IDLE中断使能。
                                                                     0：中断屏蔽；
                                                                     1：中断使能。 */
        unsigned int  int_g3d_dvfs_en           : 1;  /* bit[12-12]: G3D DVFS完成中断使能。
                                                                     0：中断屏蔽；
                                                                     1：中断使能。 */
        unsigned int  int_g3d_avs_ok_en         : 1;  /* bit[13-13]: G3D AVS电压OK中断使能。
                                                                     0：中断屏蔽；
                                                                     1：中断使能。 */
        unsigned int  int_g3d_avs_up_err_en     : 1;  /* bit[14-14]: G3D AVS提升电压错误中断使能。
                                                                     0：中断屏蔽；
                                                                     1：中断使能。 */
        unsigned int  int_g3d_avs_dn_err_en     : 1;  /* bit[15-15]: G3D AVS降低电压错误中断使能。
                                                                     0：中断屏蔽；
                                                                     1：中断使能。 */
        unsigned int  int_g3d_avs_pc_vld_en     : 1;  /* bit[16-16]: G3D AVS输出PC中断使能。
                                                                     0：中断屏蔽；
                                                                     1：中断使能。 */
        unsigned int  int_g3d_avs_idle_en       : 1;  /* bit[17-17]: G3D AVS IDLE中断使能。
                                                                     0：中断屏蔽；
                                                                     1：中断使能。 */
        unsigned int  reserved                  : 14; /* bit[18-31]: 保留 */
    } reg;
} SOC_PMCTRL_PMCINTEN_UNION;
#endif
#define SOC_PMCTRL_PMCINTEN_int_a53_cpu_dvfs_en_START        (0)
#define SOC_PMCTRL_PMCINTEN_int_a53_cpu_dvfs_en_END          (0)
#define SOC_PMCTRL_PMCINTEN_int_a53_cpu_avs_ok_en_START      (1)
#define SOC_PMCTRL_PMCINTEN_int_a53_cpu_avs_ok_en_END        (1)
#define SOC_PMCTRL_PMCINTEN_int_a53_cpu_avs_up_err_en_START  (2)
#define SOC_PMCTRL_PMCINTEN_int_a53_cpu_avs_up_err_en_END    (2)
#define SOC_PMCTRL_PMCINTEN_int_a53_cpu_avs_dn_err_en_START  (3)
#define SOC_PMCTRL_PMCINTEN_int_a53_cpu_avs_dn_err_en_END    (3)
#define SOC_PMCTRL_PMCINTEN_int_a53_cpu_avs_pc_vld_en_START  (4)
#define SOC_PMCTRL_PMCINTEN_int_a53_cpu_avs_pc_vld_en_END    (4)
#define SOC_PMCTRL_PMCINTEN_int_a53_cpu_avs_idle_en_START    (5)
#define SOC_PMCTRL_PMCINTEN_int_a53_cpu_avs_idle_en_END      (5)
#define SOC_PMCTRL_PMCINTEN_int_a57_cpu_dvfs_en_START        (6)
#define SOC_PMCTRL_PMCINTEN_int_a57_cpu_dvfs_en_END          (6)
#define SOC_PMCTRL_PMCINTEN_int_a57_cpu_avs_ok_en_START      (7)
#define SOC_PMCTRL_PMCINTEN_int_a57_cpu_avs_ok_en_END        (7)
#define SOC_PMCTRL_PMCINTEN_int_a57_cpu_avs_up_err_en_START  (8)
#define SOC_PMCTRL_PMCINTEN_int_a57_cpu_avs_up_err_en_END    (8)
#define SOC_PMCTRL_PMCINTEN_int_a57_cpu_avs_dn_err_en_START  (9)
#define SOC_PMCTRL_PMCINTEN_int_a57_cpu_avs_dn_err_en_END    (9)
#define SOC_PMCTRL_PMCINTEN_int_a57_cpu_avs_pc_vld_en_START  (10)
#define SOC_PMCTRL_PMCINTEN_int_a57_cpu_avs_pc_vld_en_END    (10)
#define SOC_PMCTRL_PMCINTEN_int_a57_cpu_avs_idle_en_START    (11)
#define SOC_PMCTRL_PMCINTEN_int_a57_cpu_avs_idle_en_END      (11)
#define SOC_PMCTRL_PMCINTEN_int_g3d_dvfs_en_START            (12)
#define SOC_PMCTRL_PMCINTEN_int_g3d_dvfs_en_END              (12)
#define SOC_PMCTRL_PMCINTEN_int_g3d_avs_ok_en_START          (13)
#define SOC_PMCTRL_PMCINTEN_int_g3d_avs_ok_en_END            (13)
#define SOC_PMCTRL_PMCINTEN_int_g3d_avs_up_err_en_START      (14)
#define SOC_PMCTRL_PMCINTEN_int_g3d_avs_up_err_en_END        (14)
#define SOC_PMCTRL_PMCINTEN_int_g3d_avs_dn_err_en_START      (15)
#define SOC_PMCTRL_PMCINTEN_int_g3d_avs_dn_err_en_END        (15)
#define SOC_PMCTRL_PMCINTEN_int_g3d_avs_pc_vld_en_START      (16)
#define SOC_PMCTRL_PMCINTEN_int_g3d_avs_pc_vld_en_END        (16)
#define SOC_PMCTRL_PMCINTEN_int_g3d_avs_idle_en_START        (17)
#define SOC_PMCTRL_PMCINTEN_int_g3d_avs_idle_en_END          (17)


/*****************************************************************************
 结构名    : SOC_PMCTRL_PMCINTSTAT_UNION
 结构说明  : PMCINTSTAT 寄存器结构定义。地址偏移量:0x004，初值:0x00000000，宽度:32
 寄存器说明: PMC中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_a53_cpu_dvfs_stat       : 1;  /* bit[0-0]  : A53_ DVFS完成中断。
                                                                       0：中断无效；
                                                                       1：中断有效。 */
        unsigned int  int_a53_cpu_avs_ok_stat     : 1;  /* bit[1-1]  : A53 AVS电压OK中断。
                                                                       0：中断无效；
                                                                       1：中断有效。 */
        unsigned int  int_a53_cpu_avs_up_err_stat : 1;  /* bit[2-2]  : A53 AVS提升电压错误中断。
                                                                       0：中断无效；
                                                                       1：中断有效。 */
        unsigned int  int_a53_cpu_avs_dn_err_stat : 1;  /* bit[3-3]  : A53 AVS降低电压错误中断。
                                                                       0：中断无效；
                                                                       1：中断有效。 */
        unsigned int  int_a53_cpu_avs_pc_vld_stat : 1;  /* bit[4-4]  : A53 AVS输出PC中断。
                                                                       0：中断无效；
                                                                       1：中断有效。 */
        unsigned int  int_a53_cpu_avs_idle_stat   : 1;  /* bit[5-5]  : A53 CPU AVS IDLE中断。
                                                                       0：中断无效；
                                                                       1：中断有效。 */
        unsigned int  int_a57_cpu_dvfs_stat       : 1;  /* bit[6-6]  : A57_ DVFS完成中断。
                                                                       0：中断无效；
                                                                       1：中断有效。 */
        unsigned int  int_a57_cpu_avs_ok_stat     : 1;  /* bit[7-7]  : A57 AVS电压OK中断。
                                                                       0：中断无效；
                                                                       1：中断有效。 */
        unsigned int  int_a57_cpu_avs_up_err_stat : 1;  /* bit[8-8]  : A57 AVS提升电压错误中断。
                                                                       0：中断无效；
                                                                       1：中断有效。 */
        unsigned int  int_a57_cpu_avs_dn_err_stat : 1;  /* bit[9-9]  : A57 AVS降低电压错误中断。
                                                                       0：中断无效；
                                                                       1：中断有效。 */
        unsigned int  int_a57_cpu_avs_pc_vld_stat : 1;  /* bit[10-10]: A57 AVS输出PC中断。
                                                                       0：中断无效；
                                                                       1：中断有效。 */
        unsigned int  int_a57_cpu_avs_idle_stat   : 1;  /* bit[11-11]: A57 CPU AVS IDLE中断。
                                                                       0：中断无效；
                                                                       1：中断有效。 */
        unsigned int  int_g3d_dvfs_stat           : 1;  /* bit[12-12]: G3D DVFS完成中断。
                                                                       0：中断无效；
                                                                       1：中断有效。 */
        unsigned int  int_g3d_avs_ok_stat         : 1;  /* bit[13-13]: G3D AVS电压OK中断。
                                                                       0：中断无效；
                                                                       1：中断有效。 */
        unsigned int  int_g3d_avs_up_err_stat     : 1;  /* bit[14-14]: G3D AVS提升电压错误中断。
                                                                       0：中断无效；
                                                                       1：中断有效。 */
        unsigned int  int_g3d_avs_dn_err_stat     : 1;  /* bit[15-15]: G3D AVS降低电压错误中断。
                                                                       0：中断无效；
                                                                       1：中断有效。 */
        unsigned int  int_g3d_avs_pc_vld_stat     : 1;  /* bit[16-16]: G3D AVS输出PC中断。
                                                                       0：中断无效；
                                                                       1：中断有效。 */
        unsigned int  int_g3d_avs_idle_stat       : 1;  /* bit[17-17]: G3D AVS IDLE中断。
                                                                       0：中断无效；
                                                                       1：中断有效。 */
        unsigned int  reserved                    : 14; /* bit[18-31]: 保留 */
    } reg;
} SOC_PMCTRL_PMCINTSTAT_UNION;
#endif
#define SOC_PMCTRL_PMCINTSTAT_int_a53_cpu_dvfs_stat_START        (0)
#define SOC_PMCTRL_PMCINTSTAT_int_a53_cpu_dvfs_stat_END          (0)
#define SOC_PMCTRL_PMCINTSTAT_int_a53_cpu_avs_ok_stat_START      (1)
#define SOC_PMCTRL_PMCINTSTAT_int_a53_cpu_avs_ok_stat_END        (1)
#define SOC_PMCTRL_PMCINTSTAT_int_a53_cpu_avs_up_err_stat_START  (2)
#define SOC_PMCTRL_PMCINTSTAT_int_a53_cpu_avs_up_err_stat_END    (2)
#define SOC_PMCTRL_PMCINTSTAT_int_a53_cpu_avs_dn_err_stat_START  (3)
#define SOC_PMCTRL_PMCINTSTAT_int_a53_cpu_avs_dn_err_stat_END    (3)
#define SOC_PMCTRL_PMCINTSTAT_int_a53_cpu_avs_pc_vld_stat_START  (4)
#define SOC_PMCTRL_PMCINTSTAT_int_a53_cpu_avs_pc_vld_stat_END    (4)
#define SOC_PMCTRL_PMCINTSTAT_int_a53_cpu_avs_idle_stat_START    (5)
#define SOC_PMCTRL_PMCINTSTAT_int_a53_cpu_avs_idle_stat_END      (5)
#define SOC_PMCTRL_PMCINTSTAT_int_a57_cpu_dvfs_stat_START        (6)
#define SOC_PMCTRL_PMCINTSTAT_int_a57_cpu_dvfs_stat_END          (6)
#define SOC_PMCTRL_PMCINTSTAT_int_a57_cpu_avs_ok_stat_START      (7)
#define SOC_PMCTRL_PMCINTSTAT_int_a57_cpu_avs_ok_stat_END        (7)
#define SOC_PMCTRL_PMCINTSTAT_int_a57_cpu_avs_up_err_stat_START  (8)
#define SOC_PMCTRL_PMCINTSTAT_int_a57_cpu_avs_up_err_stat_END    (8)
#define SOC_PMCTRL_PMCINTSTAT_int_a57_cpu_avs_dn_err_stat_START  (9)
#define SOC_PMCTRL_PMCINTSTAT_int_a57_cpu_avs_dn_err_stat_END    (9)
#define SOC_PMCTRL_PMCINTSTAT_int_a57_cpu_avs_pc_vld_stat_START  (10)
#define SOC_PMCTRL_PMCINTSTAT_int_a57_cpu_avs_pc_vld_stat_END    (10)
#define SOC_PMCTRL_PMCINTSTAT_int_a57_cpu_avs_idle_stat_START    (11)
#define SOC_PMCTRL_PMCINTSTAT_int_a57_cpu_avs_idle_stat_END      (11)
#define SOC_PMCTRL_PMCINTSTAT_int_g3d_dvfs_stat_START            (12)
#define SOC_PMCTRL_PMCINTSTAT_int_g3d_dvfs_stat_END              (12)
#define SOC_PMCTRL_PMCINTSTAT_int_g3d_avs_ok_stat_START          (13)
#define SOC_PMCTRL_PMCINTSTAT_int_g3d_avs_ok_stat_END            (13)
#define SOC_PMCTRL_PMCINTSTAT_int_g3d_avs_up_err_stat_START      (14)
#define SOC_PMCTRL_PMCINTSTAT_int_g3d_avs_up_err_stat_END        (14)
#define SOC_PMCTRL_PMCINTSTAT_int_g3d_avs_dn_err_stat_START      (15)
#define SOC_PMCTRL_PMCINTSTAT_int_g3d_avs_dn_err_stat_END        (15)
#define SOC_PMCTRL_PMCINTSTAT_int_g3d_avs_pc_vld_stat_START      (16)
#define SOC_PMCTRL_PMCINTSTAT_int_g3d_avs_pc_vld_stat_END        (16)
#define SOC_PMCTRL_PMCINTSTAT_int_g3d_avs_idle_stat_START        (17)
#define SOC_PMCTRL_PMCINTSTAT_int_g3d_avs_idle_stat_END          (17)


/*****************************************************************************
 结构名    : SOC_PMCTRL_PMCINTCLR_UNION
 结构说明  : PMCINTCLR 寄存器结构定义。地址偏移量:0x008，初值:0x00000000，宽度:32
 寄存器说明: PMC中断清除寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_a53_cpu_dvfs_clr       : 1;  /* bit[0-0]  : A53_ DVFS完成中断清除。
                                                                      0：无效；
                                                                      1：清除中断。 */
        unsigned int  int_a53_cpu_avs_ok_clr     : 1;  /* bit[1-1]  : A53 AVS电压OK中断清除。
                                                                      0：无效；
                                                                      1：清除中断。 */
        unsigned int  int_a53_cpu_avs_up_err_clr : 1;  /* bit[2-2]  : A53 AVS提升电压错误中断清除。
                                                                      0：无效；
                                                                      1：清除中断。 */
        unsigned int  int_a53_cpu_avs_dn_err_clr : 1;  /* bit[3-3]  : A53 AVS降低电压错误中断清除。
                                                                      0：无效；
                                                                      1：清除中断。 */
        unsigned int  int_a53_cpu_avs_pc_vld_clr : 1;  /* bit[4-4]  : A53 AVS输出PC中断清除。
                                                                      0：无效；
                                                                      1：清除中断。 */
        unsigned int  int_a53_cpu_avs_idle_clr   : 1;  /* bit[5-5]  : A53 CPU AVS IDLE中断清除。
                                                                      0：无效；
                                                                      1：清除中断。 */
        unsigned int  int_a57_cpu_dvfs_clr       : 1;  /* bit[6-6]  : A57_ DVFS完成中断清除。
                                                                      0：无效；
                                                                      1：清除中断。 */
        unsigned int  int_a57_cpu_avs_ok_clr     : 1;  /* bit[7-7]  : A57 AVS电压OK中断清除。
                                                                      0：无效；
                                                                      1：清除中断。 */
        unsigned int  int_a57_cpu_avs_up_err_clr : 1;  /* bit[8-8]  : A57 AVS提升电压错误中断清除。
                                                                      0：无效；
                                                                      1：清除中断。 */
        unsigned int  int_a57_cpu_avs_dn_err_clr : 1;  /* bit[9-9]  : A57 AVS降低电压错误中断清除。
                                                                      0：无效；
                                                                      1：清除中断。 */
        unsigned int  int_a57_cpu_avs_pc_vld_clr : 1;  /* bit[10-10]: A57 AVS输出PC中断清除。
                                                                      0：无效；
                                                                      1：清除中断。 */
        unsigned int  int_a57_cpu_avs_idle_clr   : 1;  /* bit[11-11]: A57 CPU AVS IDLE中断清除。
                                                                      0：无效；
                                                                      1：清除中断。 */
        unsigned int  int_g3d_dvfs_clr           : 1;  /* bit[12-12]: G3D DVFS完成中断清除。
                                                                      0：无效；
                                                                      1：清除中断。 */
        unsigned int  int_g3d_avs_ok_clr         : 1;  /* bit[13-13]: G3D AVS电压OK中断清除。
                                                                      0：无效；
                                                                      1：清除中断。 */
        unsigned int  int_g3d_avs_up_err_clr     : 1;  /* bit[14-14]: G3D AVS提升电压错误中断清除。
                                                                      0：无效；
                                                                      1：清除中断。 */
        unsigned int  int_g3d_avs_dn_err_clr     : 1;  /* bit[15-15]: G3D AVS降低电压错误中断清除。
                                                                      0：无效；
                                                                      1：清除中断。 */
        unsigned int  int_g3d_avs_pc_vld_clr     : 1;  /* bit[16-16]: G3D AVS输出PC中断清除。
                                                                      0：无效；
                                                                      1：清除中断。 */
        unsigned int  int_g3d_avs_idle_clr       : 1;  /* bit[17-17]: G3D AVS IDLE中断清除。
                                                                      0：无效；
                                                                      1：清除中断。 */
        unsigned int  reserved                   : 14; /* bit[18-31]: 保留 */
    } reg;
} SOC_PMCTRL_PMCINTCLR_UNION;
#endif
#define SOC_PMCTRL_PMCINTCLR_int_a53_cpu_dvfs_clr_START        (0)
#define SOC_PMCTRL_PMCINTCLR_int_a53_cpu_dvfs_clr_END          (0)
#define SOC_PMCTRL_PMCINTCLR_int_a53_cpu_avs_ok_clr_START      (1)
#define SOC_PMCTRL_PMCINTCLR_int_a53_cpu_avs_ok_clr_END        (1)
#define SOC_PMCTRL_PMCINTCLR_int_a53_cpu_avs_up_err_clr_START  (2)
#define SOC_PMCTRL_PMCINTCLR_int_a53_cpu_avs_up_err_clr_END    (2)
#define SOC_PMCTRL_PMCINTCLR_int_a53_cpu_avs_dn_err_clr_START  (3)
#define SOC_PMCTRL_PMCINTCLR_int_a53_cpu_avs_dn_err_clr_END    (3)
#define SOC_PMCTRL_PMCINTCLR_int_a53_cpu_avs_pc_vld_clr_START  (4)
#define SOC_PMCTRL_PMCINTCLR_int_a53_cpu_avs_pc_vld_clr_END    (4)
#define SOC_PMCTRL_PMCINTCLR_int_a53_cpu_avs_idle_clr_START    (5)
#define SOC_PMCTRL_PMCINTCLR_int_a53_cpu_avs_idle_clr_END      (5)
#define SOC_PMCTRL_PMCINTCLR_int_a57_cpu_dvfs_clr_START        (6)
#define SOC_PMCTRL_PMCINTCLR_int_a57_cpu_dvfs_clr_END          (6)
#define SOC_PMCTRL_PMCINTCLR_int_a57_cpu_avs_ok_clr_START      (7)
#define SOC_PMCTRL_PMCINTCLR_int_a57_cpu_avs_ok_clr_END        (7)
#define SOC_PMCTRL_PMCINTCLR_int_a57_cpu_avs_up_err_clr_START  (8)
#define SOC_PMCTRL_PMCINTCLR_int_a57_cpu_avs_up_err_clr_END    (8)
#define SOC_PMCTRL_PMCINTCLR_int_a57_cpu_avs_dn_err_clr_START  (9)
#define SOC_PMCTRL_PMCINTCLR_int_a57_cpu_avs_dn_err_clr_END    (9)
#define SOC_PMCTRL_PMCINTCLR_int_a57_cpu_avs_pc_vld_clr_START  (10)
#define SOC_PMCTRL_PMCINTCLR_int_a57_cpu_avs_pc_vld_clr_END    (10)
#define SOC_PMCTRL_PMCINTCLR_int_a57_cpu_avs_idle_clr_START    (11)
#define SOC_PMCTRL_PMCINTCLR_int_a57_cpu_avs_idle_clr_END      (11)
#define SOC_PMCTRL_PMCINTCLR_int_g3d_dvfs_clr_START            (12)
#define SOC_PMCTRL_PMCINTCLR_int_g3d_dvfs_clr_END              (12)
#define SOC_PMCTRL_PMCINTCLR_int_g3d_avs_ok_clr_START          (13)
#define SOC_PMCTRL_PMCINTCLR_int_g3d_avs_ok_clr_END            (13)
#define SOC_PMCTRL_PMCINTCLR_int_g3d_avs_up_err_clr_START      (14)
#define SOC_PMCTRL_PMCINTCLR_int_g3d_avs_up_err_clr_END        (14)
#define SOC_PMCTRL_PMCINTCLR_int_g3d_avs_dn_err_clr_START      (15)
#define SOC_PMCTRL_PMCINTCLR_int_g3d_avs_dn_err_clr_END        (15)
#define SOC_PMCTRL_PMCINTCLR_int_g3d_avs_pc_vld_clr_START      (16)
#define SOC_PMCTRL_PMCINTCLR_int_g3d_avs_pc_vld_clr_END        (16)
#define SOC_PMCTRL_PMCINTCLR_int_g3d_avs_idle_clr_START        (17)
#define SOC_PMCTRL_PMCINTCLR_int_g3d_avs_idle_clr_END          (17)


/*****************************************************************************
 结构名    : SOC_PMCTRL_PMCSTATUS_UNION
 结构说明  : PMCSTATUS 寄存器结构定义。地址偏移量:0x00C，初值:0x00000000，宽度:32
 寄存器说明: PMC状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cpu_dvfs_stat : 4;  /* bit[0-3]  : A53_ CPU DVFS状态机当前状态 */
        unsigned int  a53_cpu_avs_stat  : 6;  /* bit[4-9]  : A53 CPU AVS状态机当前状态 */
        unsigned int  a57_cpu_dvfs_stat : 4;  /* bit[10-13]: A57_ CPU DVFS状态机当前状态 */
        unsigned int  a57_cpu_avs_stat  : 6;  /* bit[14-19]: A57 CPU AVS状态机当前状态 */
        unsigned int  g3d_dvfs_stat     : 4;  /* bit[20-23]: G3D DVFS状态机当前状态 */
        unsigned int  g3d_avs_stat      : 6;  /* bit[24-29]: G3D AVS状态机当前状态 */
        unsigned int  reserved          : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_PMCTRL_PMCSTATUS_UNION;
#endif
#define SOC_PMCTRL_PMCSTATUS_a53_cpu_dvfs_stat_START  (0)
#define SOC_PMCTRL_PMCSTATUS_a53_cpu_dvfs_stat_END    (3)
#define SOC_PMCTRL_PMCSTATUS_a53_cpu_avs_stat_START   (4)
#define SOC_PMCTRL_PMCSTATUS_a53_cpu_avs_stat_END     (9)
#define SOC_PMCTRL_PMCSTATUS_a57_cpu_dvfs_stat_START  (10)
#define SOC_PMCTRL_PMCSTATUS_a57_cpu_dvfs_stat_END    (13)
#define SOC_PMCTRL_PMCSTATUS_a57_cpu_avs_stat_START   (14)
#define SOC_PMCTRL_PMCSTATUS_a57_cpu_avs_stat_END     (19)
#define SOC_PMCTRL_PMCSTATUS_g3d_dvfs_stat_START      (20)
#define SOC_PMCTRL_PMCSTATUS_g3d_dvfs_stat_END        (23)
#define SOC_PMCTRL_PMCSTATUS_g3d_avs_stat_START       (24)
#define SOC_PMCTRL_PMCSTATUS_g3d_avs_stat_END         (29)


/*****************************************************************************
 结构名    : SOC_PMCTRL_APLL0CTRL0_UNION
 结构说明  : APLL0CTRL0 寄存器结构定义。地址偏移量:0x010，初值:0x00B03E06，宽度:32
 寄存器说明: APLL0控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  apll0_en       : 1;  /* bit[0-0]  : APLL0 PowerDown控制。
                                                          0：关闭；
                                                          1：使能。 */
        unsigned int  apll0_bp       : 1;  /* bit[1-1]  : APLL0 Bypass控制。
                                                          0：正常工作；
                                                          1：Bypass。 */
        unsigned int  apll0_refdiv   : 6;  /* bit[2-7]  : APLL0输入时钟分频器。 */
        unsigned int  apll0_fbdiv    : 12; /* bit[8-19] : APLL0反馈时钟整数分频器。 */
        unsigned int  apll0_postdiv1 : 3;  /* bit[20-22]: APLL0输出时钟分频器1。 */
        unsigned int  apll0_postdiv2 : 3;  /* bit[23-25]: APLL0输出时钟分频器2。 */
        unsigned int  apll0_lock     : 1;  /* bit[26-26]: APLL0 Lock指示。
                                                          0：无效；
                                                          1：APLL0 Lock。 */
        unsigned int  reserved       : 5;  /* bit[27-31]: 保留 */
    } reg;
} SOC_PMCTRL_APLL0CTRL0_UNION;
#endif
#define SOC_PMCTRL_APLL0CTRL0_apll0_en_START        (0)
#define SOC_PMCTRL_APLL0CTRL0_apll0_en_END          (0)
#define SOC_PMCTRL_APLL0CTRL0_apll0_bp_START        (1)
#define SOC_PMCTRL_APLL0CTRL0_apll0_bp_END          (1)
#define SOC_PMCTRL_APLL0CTRL0_apll0_refdiv_START    (2)
#define SOC_PMCTRL_APLL0CTRL0_apll0_refdiv_END      (7)
#define SOC_PMCTRL_APLL0CTRL0_apll0_fbdiv_START     (8)
#define SOC_PMCTRL_APLL0CTRL0_apll0_fbdiv_END       (19)
#define SOC_PMCTRL_APLL0CTRL0_apll0_postdiv1_START  (20)
#define SOC_PMCTRL_APLL0CTRL0_apll0_postdiv1_END    (22)
#define SOC_PMCTRL_APLL0CTRL0_apll0_postdiv2_START  (23)
#define SOC_PMCTRL_APLL0CTRL0_apll0_postdiv2_END    (25)
#define SOC_PMCTRL_APLL0CTRL0_apll0_lock_START      (26)
#define SOC_PMCTRL_APLL0CTRL0_apll0_lock_END        (26)


/*****************************************************************************
 结构名    : SOC_PMCTRL_APLL0CTRL1_UNION
 结构说明  : APLL0CTRL1 寄存器结构定义。地址偏移量:0x014，初值:0x06F80000，宽度:32
 寄存器说明: APLL0控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  apll0_fracdiv : 24; /* bit[0-23] : APLL0反馈时钟分数分频器。 */
        unsigned int  apll0_int_mod : 1;  /* bit[24-24]: APLL0整数分频模式。
                                                         0：分数分频模式；
                                                         1：整数分频模式。
                                                         注意：本PLL支持分数分频和整数分频模式，但在SSC打开时，要求软件只使用分数分频模式。 */
        unsigned int  apll0_cfg_vld : 1;  /* bit[25-25]: APLL0配置有效标志。
                                                         0：配置无效；
                                                         1：配置有效。 */
        unsigned int  gt_clk_apll0  : 1;  /* bit[26-26]: APLL0门控信号。
                                                         0：APLL0输出时钟门控；
                                                         1：APLL0输出时钟不门控。（等待PLL稳定后才能配置该bit） */
        unsigned int  reserved      : 5;  /* bit[27-31]: 保留 */
    } reg;
} SOC_PMCTRL_APLL0CTRL1_UNION;
#endif
#define SOC_PMCTRL_APLL0CTRL1_apll0_fracdiv_START  (0)
#define SOC_PMCTRL_APLL0CTRL1_apll0_fracdiv_END    (23)
#define SOC_PMCTRL_APLL0CTRL1_apll0_int_mod_START  (24)
#define SOC_PMCTRL_APLL0CTRL1_apll0_int_mod_END    (24)
#define SOC_PMCTRL_APLL0CTRL1_apll0_cfg_vld_START  (25)
#define SOC_PMCTRL_APLL0CTRL1_apll0_cfg_vld_END    (25)
#define SOC_PMCTRL_APLL0CTRL1_gt_clk_apll0_START   (26)
#define SOC_PMCTRL_APLL0CTRL1_gt_clk_apll0_END     (26)


/*****************************************************************************
 结构名    : SOC_PMCTRL_APLL1CTRL0_UNION
 结构说明  : APLL1CTRL0 寄存器结构定义。地址偏移量:0x018，初值:0x00B03E06，宽度:32
 寄存器说明: APLL1控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  apll1_en       : 1;  /* bit[0-0]  : APLL1 PowerDown控制。
                                                          0：关闭；
                                                          1：使能。 */
        unsigned int  apll1_bp       : 1;  /* bit[1-1]  : APLL1 Bypass控制。
                                                          0：正常工作；
                                                          1：Bypass。 */
        unsigned int  apll1_refdiv   : 6;  /* bit[2-7]  : APLL1输入时钟分频器。 */
        unsigned int  apll1_fbdiv    : 12; /* bit[8-19] : APLL1反馈时钟整数分频器。 */
        unsigned int  apll1_postdiv1 : 3;  /* bit[20-22]: APLL1输出时钟分频器1。 */
        unsigned int  apll1_postdiv2 : 3;  /* bit[23-25]: APLL1输出时钟分频器2。 */
        unsigned int  apll1_lock     : 1;  /* bit[26-26]: APLL1 Lock指示。
                                                          0：无效；
                                                          1：APLL1 Lock。 */
        unsigned int  reserved       : 5;  /* bit[27-31]: 保留 */
    } reg;
} SOC_PMCTRL_APLL1CTRL0_UNION;
#endif
#define SOC_PMCTRL_APLL1CTRL0_apll1_en_START        (0)
#define SOC_PMCTRL_APLL1CTRL0_apll1_en_END          (0)
#define SOC_PMCTRL_APLL1CTRL0_apll1_bp_START        (1)
#define SOC_PMCTRL_APLL1CTRL0_apll1_bp_END          (1)
#define SOC_PMCTRL_APLL1CTRL0_apll1_refdiv_START    (2)
#define SOC_PMCTRL_APLL1CTRL0_apll1_refdiv_END      (7)
#define SOC_PMCTRL_APLL1CTRL0_apll1_fbdiv_START     (8)
#define SOC_PMCTRL_APLL1CTRL0_apll1_fbdiv_END       (19)
#define SOC_PMCTRL_APLL1CTRL0_apll1_postdiv1_START  (20)
#define SOC_PMCTRL_APLL1CTRL0_apll1_postdiv1_END    (22)
#define SOC_PMCTRL_APLL1CTRL0_apll1_postdiv2_START  (23)
#define SOC_PMCTRL_APLL1CTRL0_apll1_postdiv2_END    (25)
#define SOC_PMCTRL_APLL1CTRL0_apll1_lock_START      (26)
#define SOC_PMCTRL_APLL1CTRL0_apll1_lock_END        (26)


/*****************************************************************************
 结构名    : SOC_PMCTRL_APLL1CTRL1_UNION
 结构说明  : APLL1CTRL1 寄存器结构定义。地址偏移量:0x01C，初值:0x06F80000，宽度:32
 寄存器说明: APLL1控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  apll1_fracdiv : 24; /* bit[0-23] : APLL1反馈时钟分数分频器。 */
        unsigned int  apll1_int_mod : 1;  /* bit[24-24]: APLL1整数分频模式。
                                                         0：分数分频模式；
                                                         1：整数分频模式。
                                                         注意：本PLL支持分数分频和整数分频模式，但在SSC打开时，要求软件只使用分数分频模式。 */
        unsigned int  apll1_cfg_vld : 1;  /* bit[25-25]: APLL1配置有效标志。
                                                         0：配置无效；
                                                         1：配置有效。 */
        unsigned int  gt_clk_apll1  : 1;  /* bit[26-26]: APLL1门控信号。
                                                         0：APLL1输出时钟门控；
                                                         1：APLL1输出时钟不门控。（等待PLL稳定后才能配置该bit） */
        unsigned int  reserved      : 5;  /* bit[27-31]: 保留 */
    } reg;
} SOC_PMCTRL_APLL1CTRL1_UNION;
#endif
#define SOC_PMCTRL_APLL1CTRL1_apll1_fracdiv_START  (0)
#define SOC_PMCTRL_APLL1CTRL1_apll1_fracdiv_END    (23)
#define SOC_PMCTRL_APLL1CTRL1_apll1_int_mod_START  (24)
#define SOC_PMCTRL_APLL1CTRL1_apll1_int_mod_END    (24)
#define SOC_PMCTRL_APLL1CTRL1_apll1_cfg_vld_START  (25)
#define SOC_PMCTRL_APLL1CTRL1_apll1_cfg_vld_END    (25)
#define SOC_PMCTRL_APLL1CTRL1_gt_clk_apll1_START   (26)
#define SOC_PMCTRL_APLL1CTRL1_gt_clk_apll1_END     (26)


/*****************************************************************************
 结构名    : SOC_PMCTRL_APLL2CTRL0_UNION
 结构说明  : APLL2CTRL0 寄存器结构定义。地址偏移量:0x020，初值:0x00B03E06，宽度:32
 寄存器说明: APLL2控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  apll2_en       : 1;  /* bit[0-0]  : APLL2 PowerDown控制。
                                                          0：关闭；
                                                          1：使能。 */
        unsigned int  apll2_bp       : 1;  /* bit[1-1]  : APLL2 Bypass控制。
                                                          0：正常工作；
                                                          1：Bypass。 */
        unsigned int  apll2_refdiv   : 6;  /* bit[2-7]  : APLL2输入时钟分频器。 */
        unsigned int  apll2_fbdiv    : 12; /* bit[8-19] : APLL2反馈时钟整数分频器。 */
        unsigned int  apll2_postdiv1 : 3;  /* bit[20-22]: APLL2输出时钟分频器1。 */
        unsigned int  apll2_postdiv2 : 3;  /* bit[23-25]: APLL2输出时钟分频器2。 */
        unsigned int  apll2_lock     : 1;  /* bit[26-26]: APLL2 Lock指示。
                                                          0：无效；
                                                          1：APLL2 Lock。 */
        unsigned int  reserved       : 5;  /* bit[27-31]: 保留 */
    } reg;
} SOC_PMCTRL_APLL2CTRL0_UNION;
#endif
#define SOC_PMCTRL_APLL2CTRL0_apll2_en_START        (0)
#define SOC_PMCTRL_APLL2CTRL0_apll2_en_END          (0)
#define SOC_PMCTRL_APLL2CTRL0_apll2_bp_START        (1)
#define SOC_PMCTRL_APLL2CTRL0_apll2_bp_END          (1)
#define SOC_PMCTRL_APLL2CTRL0_apll2_refdiv_START    (2)
#define SOC_PMCTRL_APLL2CTRL0_apll2_refdiv_END      (7)
#define SOC_PMCTRL_APLL2CTRL0_apll2_fbdiv_START     (8)
#define SOC_PMCTRL_APLL2CTRL0_apll2_fbdiv_END       (19)
#define SOC_PMCTRL_APLL2CTRL0_apll2_postdiv1_START  (20)
#define SOC_PMCTRL_APLL2CTRL0_apll2_postdiv1_END    (22)
#define SOC_PMCTRL_APLL2CTRL0_apll2_postdiv2_START  (23)
#define SOC_PMCTRL_APLL2CTRL0_apll2_postdiv2_END    (25)
#define SOC_PMCTRL_APLL2CTRL0_apll2_lock_START      (26)
#define SOC_PMCTRL_APLL2CTRL0_apll2_lock_END        (26)


/*****************************************************************************
 结构名    : SOC_PMCTRL_APLL2CTRL1_UNION
 结构说明  : APLL2CTRL1 寄存器结构定义。地址偏移量:0x024，初值:0x06F80000，宽度:32
 寄存器说明: APLL2控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  apll2_fracdiv : 24; /* bit[0-23] : APLL2反馈时钟分数分频器。 */
        unsigned int  apll2_int_mod : 1;  /* bit[24-24]: APLL2整数分频模式。
                                                         0：分数分频模式；
                                                         1：整数分频模式。
                                                         注意：本PLL支持分数分频和整数分频模式，但在SSC打开时，要求软件只使用分数分频模式。 */
        unsigned int  apll2_cfg_vld : 1;  /* bit[25-25]: APLL2配置有效标志。
                                                         0：配置无效；
                                                         1：配置有效。 */
        unsigned int  gt_clk_apll2  : 1;  /* bit[26-26]: APLL2门控信号。
                                                         0：APLL2输出时钟门控；
                                                         1：APLL2输出时钟不门控。（等待PLL稳定后才能配置该bit） */
        unsigned int  reserved      : 5;  /* bit[27-31]: 保留 */
    } reg;
} SOC_PMCTRL_APLL2CTRL1_UNION;
#endif
#define SOC_PMCTRL_APLL2CTRL1_apll2_fracdiv_START  (0)
#define SOC_PMCTRL_APLL2CTRL1_apll2_fracdiv_END    (23)
#define SOC_PMCTRL_APLL2CTRL1_apll2_int_mod_START  (24)
#define SOC_PMCTRL_APLL2CTRL1_apll2_int_mod_END    (24)
#define SOC_PMCTRL_APLL2CTRL1_apll2_cfg_vld_START  (25)
#define SOC_PMCTRL_APLL2CTRL1_apll2_cfg_vld_END    (25)
#define SOC_PMCTRL_APLL2CTRL1_gt_clk_apll2_START   (26)
#define SOC_PMCTRL_APLL2CTRL1_gt_clk_apll2_END     (26)


/*****************************************************************************
 结构名    : SOC_PMCTRL_PPLL1CTRL0_UNION
 结构说明  : PPLL1CTRL0 寄存器结构定义。地址偏移量:0x038，初值:0x00904B06，宽度:32
 寄存器说明: PPLL1控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ppll1_en       : 1;  /* bit[0-0]  : PPLL1 PowerDown控制。
                                                          0：关闭；
                                                          1：使能。 */
        unsigned int  ppll1_bp       : 1;  /* bit[1-1]  : PPLL1 Bypass控制。
                                                          0：正常工作；
                                                          1：Bypass。 */
        unsigned int  ppll1_refdiv   : 6;  /* bit[2-7]  : PPLL1输入时钟分频器。 */
        unsigned int  ppll1_fbdiv    : 12; /* bit[8-19] : PPLL1反馈时钟整数分频器。 */
        unsigned int  ppll1_postdiv1 : 3;  /* bit[20-22]: PPLL1输出时钟分频器1。 */
        unsigned int  ppll1_postdiv2 : 3;  /* bit[23-25]: PPLL1输出时钟分频器2。 */
        unsigned int  ppll1_lock     : 1;  /* bit[26-26]: PPLL1 Lock指示。
                                                          0：无效；
                                                          1：PPLL1 Lock。 */
        unsigned int  reserved       : 5;  /* bit[27-31]: 保留 */
    } reg;
} SOC_PMCTRL_PPLL1CTRL0_UNION;
#endif
#define SOC_PMCTRL_PPLL1CTRL0_ppll1_en_START        (0)
#define SOC_PMCTRL_PPLL1CTRL0_ppll1_en_END          (0)
#define SOC_PMCTRL_PPLL1CTRL0_ppll1_bp_START        (1)
#define SOC_PMCTRL_PPLL1CTRL0_ppll1_bp_END          (1)
#define SOC_PMCTRL_PPLL1CTRL0_ppll1_refdiv_START    (2)
#define SOC_PMCTRL_PPLL1CTRL0_ppll1_refdiv_END      (7)
#define SOC_PMCTRL_PPLL1CTRL0_ppll1_fbdiv_START     (8)
#define SOC_PMCTRL_PPLL1CTRL0_ppll1_fbdiv_END       (19)
#define SOC_PMCTRL_PPLL1CTRL0_ppll1_postdiv1_START  (20)
#define SOC_PMCTRL_PPLL1CTRL0_ppll1_postdiv1_END    (22)
#define SOC_PMCTRL_PPLL1CTRL0_ppll1_postdiv2_START  (23)
#define SOC_PMCTRL_PPLL1CTRL0_ppll1_postdiv2_END    (25)
#define SOC_PMCTRL_PPLL1CTRL0_ppll1_lock_START      (26)
#define SOC_PMCTRL_PPLL1CTRL0_ppll1_lock_END        (26)


/*****************************************************************************
 结构名    : SOC_PMCTRL_PPLL1CTRL1_UNION
 结构说明  : PPLL1CTRL1 寄存器结构定义。地址偏移量:0x03C，初值:0x06000000，宽度:32
 寄存器说明: PPLL1控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ppll1_fracdiv : 24; /* bit[0-23] : PPLL1反馈时钟分数分频器。 */
        unsigned int  ppll1_int_mod : 1;  /* bit[24-24]: PPLL1整数分频模式。
                                                         0：分数分频模式；
                                                         1：整数分频模式。
                                                         注意：本PLL支持分数分频和整数分频模式，但在SSC打开时，要求软件只使用分数分频模式。 */
        unsigned int  ppll1_cfg_vld : 1;  /* bit[25-25]: PPLL1配置有效标志。
                                                         0：配置无效；
                                                         1：配置有效。 */
        unsigned int  gt_clk_ppll1  : 1;  /* bit[26-26]: PPLL1门控信号。
                                                         0：PPLL1输出时钟门控；
                                                         1：PPLL1输出时钟不门控。（等待PLL稳定后才能配置该bit） */
        unsigned int  reserved      : 5;  /* bit[27-31]: 保留 */
    } reg;
} SOC_PMCTRL_PPLL1CTRL1_UNION;
#endif
#define SOC_PMCTRL_PPLL1CTRL1_ppll1_fracdiv_START  (0)
#define SOC_PMCTRL_PPLL1CTRL1_ppll1_fracdiv_END    (23)
#define SOC_PMCTRL_PPLL1CTRL1_ppll1_int_mod_START  (24)
#define SOC_PMCTRL_PPLL1CTRL1_ppll1_int_mod_END    (24)
#define SOC_PMCTRL_PPLL1CTRL1_ppll1_cfg_vld_START  (25)
#define SOC_PMCTRL_PPLL1CTRL1_ppll1_cfg_vld_END    (25)
#define SOC_PMCTRL_PPLL1CTRL1_gt_clk_ppll1_START   (26)
#define SOC_PMCTRL_PPLL1CTRL1_gt_clk_ppll1_END     (26)


/*****************************************************************************
 结构名    : SOC_PMCTRL_PPLL2CTRL0_UNION
 结构说明  : PPLL2CTRL0 寄存器结构定义。地址偏移量:0x040，初值:0x00A03D06，宽度:32
 寄存器说明: PPLL2控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ppll2_en       : 1;  /* bit[0-0]  : PPLL2 PowerDown控制。
                                                          0：关闭；
                                                          1：使能。 */
        unsigned int  ppll2_bp       : 1;  /* bit[1-1]  : PPLL2 Bypass控制。
                                                          0：正常工作；
                                                          1：Bypass。 */
        unsigned int  ppll2_refdiv   : 6;  /* bit[2-7]  : PPLL2输入时钟分频器。 */
        unsigned int  ppll2_fbdiv    : 12; /* bit[8-19] : PPLL2反馈时钟整数分频器。 */
        unsigned int  ppll2_postdiv1 : 3;  /* bit[20-22]: PPLL2输出时钟分频器1。 */
        unsigned int  ppll2_postdiv2 : 3;  /* bit[23-25]: PPLL2输出时钟分频器2。 */
        unsigned int  ppll2_lock     : 1;  /* bit[26-26]: PPLL2 Lock指示。
                                                          0：无效；
                                                          1：PPLL2 Lock。 */
        unsigned int  reserved       : 5;  /* bit[27-31]: 保留 */
    } reg;
} SOC_PMCTRL_PPLL2CTRL0_UNION;
#endif
#define SOC_PMCTRL_PPLL2CTRL0_ppll2_en_START        (0)
#define SOC_PMCTRL_PPLL2CTRL0_ppll2_en_END          (0)
#define SOC_PMCTRL_PPLL2CTRL0_ppll2_bp_START        (1)
#define SOC_PMCTRL_PPLL2CTRL0_ppll2_bp_END          (1)
#define SOC_PMCTRL_PPLL2CTRL0_ppll2_refdiv_START    (2)
#define SOC_PMCTRL_PPLL2CTRL0_ppll2_refdiv_END      (7)
#define SOC_PMCTRL_PPLL2CTRL0_ppll2_fbdiv_START     (8)
#define SOC_PMCTRL_PPLL2CTRL0_ppll2_fbdiv_END       (19)
#define SOC_PMCTRL_PPLL2CTRL0_ppll2_postdiv1_START  (20)
#define SOC_PMCTRL_PPLL2CTRL0_ppll2_postdiv1_END    (22)
#define SOC_PMCTRL_PPLL2CTRL0_ppll2_postdiv2_START  (23)
#define SOC_PMCTRL_PPLL2CTRL0_ppll2_postdiv2_END    (25)
#define SOC_PMCTRL_PPLL2CTRL0_ppll2_lock_START      (26)
#define SOC_PMCTRL_PPLL2CTRL0_ppll2_lock_END        (26)


/*****************************************************************************
 结构名    : SOC_PMCTRL_PPLL2CTRL1_UNION
 结构说明  : PPLL2CTRL1 寄存器结构定义。地址偏移量:0x044，初值:0x06E00000，宽度:32
 寄存器说明: PPLL2控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ppll2_fracdiv : 24; /* bit[0-23] : PPLL2反馈时钟分数分频器。 */
        unsigned int  ppll2_int_mod : 1;  /* bit[24-24]: PPLL2整数分频模式。
                                                         0：分数分频模式；
                                                         1：整数分频模式。
                                                         注意：本PLL支持分数分频和整数分频模式，但在SSC打开时，要求软件只使用分数分频模式。 */
        unsigned int  ppll2_cfg_vld : 1;  /* bit[25-25]: PPLL2配置有效标志。
                                                         0：配置无效；
                                                         1：配置有效。 */
        unsigned int  gt_clk_ppll2  : 1;  /* bit[26-26]: PPLL2门控信号。
                                                         0：PPLL2输出时钟门控；
                                                         1：PPLL2输出时钟不门控。（等待PLL稳定后才能配置该bit） */
        unsigned int  reserved      : 5;  /* bit[27-31]: 保留 */
    } reg;
} SOC_PMCTRL_PPLL2CTRL1_UNION;
#endif
#define SOC_PMCTRL_PPLL2CTRL1_ppll2_fracdiv_START  (0)
#define SOC_PMCTRL_PPLL2CTRL1_ppll2_fracdiv_END    (23)
#define SOC_PMCTRL_PPLL2CTRL1_ppll2_int_mod_START  (24)
#define SOC_PMCTRL_PPLL2CTRL1_ppll2_int_mod_END    (24)
#define SOC_PMCTRL_PPLL2CTRL1_ppll2_cfg_vld_START  (25)
#define SOC_PMCTRL_PPLL2CTRL1_ppll2_cfg_vld_END    (25)
#define SOC_PMCTRL_PPLL2CTRL1_gt_clk_ppll2_START   (26)
#define SOC_PMCTRL_PPLL2CTRL1_gt_clk_ppll2_END     (26)


/*****************************************************************************
 结构名    : SOC_PMCTRL_PPLL3CTRL0_UNION
 结构说明  : PPLL3CTRL0 寄存器结构定义。地址偏移量:0x048，初值:0x00905306，宽度:32
 寄存器说明: PPLL3控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ppll3_en       : 1;  /* bit[0-0]  : PPLL3 PowerDown控制。
                                                          0：关闭；
                                                          1：使能。 */
        unsigned int  ppll3_bp       : 1;  /* bit[1-1]  : PPLL3 Bypass控制。
                                                          0：正常工作；
                                                          1：Bypass。 */
        unsigned int  ppll3_refdiv   : 6;  /* bit[2-7]  : PPLL3输入时钟分频器。 */
        unsigned int  ppll3_fbdiv    : 12; /* bit[8-19] : PPLL3反馈时钟整数分频器。 */
        unsigned int  ppll3_postdiv1 : 3;  /* bit[20-22]: PPLL3输出时钟分频器1。 */
        unsigned int  ppll3_postdiv2 : 3;  /* bit[23-25]: PPLL3输出时钟分频器2。 */
        unsigned int  ppll3_lock     : 1;  /* bit[26-26]: PPLL3 Lock指示。
                                                          0：无效；
                                                          1：PPLL3 Lock。 */
        unsigned int  reserved       : 5;  /* bit[27-31]: 保留 */
    } reg;
} SOC_PMCTRL_PPLL3CTRL0_UNION;
#endif
#define SOC_PMCTRL_PPLL3CTRL0_ppll3_en_START        (0)
#define SOC_PMCTRL_PPLL3CTRL0_ppll3_en_END          (0)
#define SOC_PMCTRL_PPLL3CTRL0_ppll3_bp_START        (1)
#define SOC_PMCTRL_PPLL3CTRL0_ppll3_bp_END          (1)
#define SOC_PMCTRL_PPLL3CTRL0_ppll3_refdiv_START    (2)
#define SOC_PMCTRL_PPLL3CTRL0_ppll3_refdiv_END      (7)
#define SOC_PMCTRL_PPLL3CTRL0_ppll3_fbdiv_START     (8)
#define SOC_PMCTRL_PPLL3CTRL0_ppll3_fbdiv_END       (19)
#define SOC_PMCTRL_PPLL3CTRL0_ppll3_postdiv1_START  (20)
#define SOC_PMCTRL_PPLL3CTRL0_ppll3_postdiv1_END    (22)
#define SOC_PMCTRL_PPLL3CTRL0_ppll3_postdiv2_START  (23)
#define SOC_PMCTRL_PPLL3CTRL0_ppll3_postdiv2_END    (25)
#define SOC_PMCTRL_PPLL3CTRL0_ppll3_lock_START      (26)
#define SOC_PMCTRL_PPLL3CTRL0_ppll3_lock_END        (26)


/*****************************************************************************
 结构名    : SOC_PMCTRL_PPLL3CTRL1_UNION
 结构说明  : PPLL3CTRL1 寄存器结构定义。地址偏移量:0x04C，初值:0x06555555，宽度:32
 寄存器说明: PPLL3控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ppll3_fracdiv : 24; /* bit[0-23] : PPLL3反馈时钟分数分频器。 */
        unsigned int  ppll3_int_mod : 1;  /* bit[24-24]: PPLL3整数分频模式。
                                                         0：分数分频模式；
                                                         1：整数分频模式。
                                                         注意：本PLL支持分数分频和整数分频模式，但在SSC打开时，要求软件只使用分数分频模式。 */
        unsigned int  ppll3_cfg_vld : 1;  /* bit[25-25]: PPLL3配置有效标志。
                                                         0：配置无效；
                                                         1：配置有效。 */
        unsigned int  gt_clk_ppll3  : 1;  /* bit[26-26]: PPLL3门控信号。
                                                         0：PPLL3输出时钟门控；
                                                         1：PPLL3输出时钟不门控。（等待PLL稳定后才能配置该bit） */
        unsigned int  reserved      : 5;  /* bit[27-31]: 保留 */
    } reg;
} SOC_PMCTRL_PPLL3CTRL1_UNION;
#endif
#define SOC_PMCTRL_PPLL3CTRL1_ppll3_fracdiv_START  (0)
#define SOC_PMCTRL_PPLL3CTRL1_ppll3_fracdiv_END    (23)
#define SOC_PMCTRL_PPLL3CTRL1_ppll3_int_mod_START  (24)
#define SOC_PMCTRL_PPLL3CTRL1_ppll3_int_mod_END    (24)
#define SOC_PMCTRL_PPLL3CTRL1_ppll3_cfg_vld_START  (25)
#define SOC_PMCTRL_PPLL3CTRL1_ppll3_cfg_vld_END    (25)
#define SOC_PMCTRL_PPLL3CTRL1_gt_clk_ppll3_START   (26)
#define SOC_PMCTRL_PPLL3CTRL1_gt_clk_ppll3_END     (26)


/*****************************************************************************
 结构名    : SOC_PMCTRL_APLL0SSCCTRL_UNION
 结构说明  : APLL0SSCCTRL 寄存器结构定义。地址偏移量:0x070，初值:0x0000019F，宽度:32
 寄存器说明: APLL0 SSC控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  apll0_ssc_reset      : 1;  /* bit[0]    : 复位信号，高有效。
                                                                0：复位取消
                                                                1：复位有效
                                                                注：不能在PLL工作过程中复位，否则会导致PLL失锁。 */
        unsigned int  apll0_ssc_disable    : 1;  /* bit[1]    : Bypass the modulator，高有效。
                                                                0：正常工作
                                                                1：bypass */
        unsigned int  apll0_ssc_downspread : 1;  /* bit[2]    : 选择center spread或down spread
                                                                0：Center Spread
                                                                1：Down Spread */
        unsigned int  apll0_ssc_spread     : 3;  /* bit[3-5]  : 设置调制深度(spread%)
                                                                3'b000 = 0
                                                                3'b001 = 0.049%
                                                                3'b010 = 0.098%
                                                                3'b011 = 0.195%
                                                                3'b100 = 0.391%
                                                                3'b101 = 0.781%
                                                                3'b110 = 1.563%
                                                                3'b111 = 3.125% */
        unsigned int  apll0_ssc_divval     : 4;  /* bit[6-9]  : 设置频谱调制的频率，一般约为32KHz；
                                                                freq=(CLKSSCG / (DIVVAL * #points))，其中points为128；当REFDIV=1时，CLKSSCG=FREF。 */
        unsigned int  reserved             : 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_PMCTRL_APLL0SSCCTRL_UNION;
#endif
#define SOC_PMCTRL_APLL0SSCCTRL_apll0_ssc_reset_START       (0)
#define SOC_PMCTRL_APLL0SSCCTRL_apll0_ssc_reset_END         (0)
#define SOC_PMCTRL_APLL0SSCCTRL_apll0_ssc_disable_START     (1)
#define SOC_PMCTRL_APLL0SSCCTRL_apll0_ssc_disable_END       (1)
#define SOC_PMCTRL_APLL0SSCCTRL_apll0_ssc_downspread_START  (2)
#define SOC_PMCTRL_APLL0SSCCTRL_apll0_ssc_downspread_END    (2)
#define SOC_PMCTRL_APLL0SSCCTRL_apll0_ssc_spread_START      (3)
#define SOC_PMCTRL_APLL0SSCCTRL_apll0_ssc_spread_END        (5)
#define SOC_PMCTRL_APLL0SSCCTRL_apll0_ssc_divval_START      (6)
#define SOC_PMCTRL_APLL0SSCCTRL_apll0_ssc_divval_END        (9)


/*****************************************************************************
 结构名    : SOC_PMCTRL_APLL1SSCCTRL_UNION
 结构说明  : APLL1SSCCTRL 寄存器结构定义。地址偏移量:0x074，初值:0x0000019F，宽度:32
 寄存器说明: APLL1 SSC控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  apll1_ssc_reset      : 1;  /* bit[0]    : 复位信号，高有效。
                                                                0：复位取消
                                                                1：复位有效
                                                                注：不能在PLL工作过程中复位，否则会导致PLL失锁。 */
        unsigned int  apll1_ssc_disable    : 1;  /* bit[1]    : Bypass the modulator，高有效。
                                                                0：正常工作
                                                                1：bypass */
        unsigned int  apll1_ssc_downspread : 1;  /* bit[2]    : 选择center spread或down spread
                                                                0：Center Spread
                                                                1：Down Spread */
        unsigned int  apll1_ssc_spread     : 3;  /* bit[3-5]  : 设置调制深度(spread%)
                                                                3'b000 = 0
                                                                3'b001 = 0.049%
                                                                3'b010 = 0.098%
                                                                3'b011 = 0.195%
                                                                3'b100 = 0.391%
                                                                3'b101 = 0.781%
                                                                3'b110 = 1.563%
                                                                3'b111 = 3.125% */
        unsigned int  apll1_ssc_divval     : 4;  /* bit[6-9]  : 设置频谱调制的频率，一般约为32KHz；
                                                                freq=(CLKSSCG / (DIVVAL * #points))，其中points为128；当REFDIV=1时，CLKSSCG=FREF。 */
        unsigned int  reserved             : 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_PMCTRL_APLL1SSCCTRL_UNION;
#endif
#define SOC_PMCTRL_APLL1SSCCTRL_apll1_ssc_reset_START       (0)
#define SOC_PMCTRL_APLL1SSCCTRL_apll1_ssc_reset_END         (0)
#define SOC_PMCTRL_APLL1SSCCTRL_apll1_ssc_disable_START     (1)
#define SOC_PMCTRL_APLL1SSCCTRL_apll1_ssc_disable_END       (1)
#define SOC_PMCTRL_APLL1SSCCTRL_apll1_ssc_downspread_START  (2)
#define SOC_PMCTRL_APLL1SSCCTRL_apll1_ssc_downspread_END    (2)
#define SOC_PMCTRL_APLL1SSCCTRL_apll1_ssc_spread_START      (3)
#define SOC_PMCTRL_APLL1SSCCTRL_apll1_ssc_spread_END        (5)
#define SOC_PMCTRL_APLL1SSCCTRL_apll1_ssc_divval_START      (6)
#define SOC_PMCTRL_APLL1SSCCTRL_apll1_ssc_divval_END        (9)


/*****************************************************************************
 结构名    : SOC_PMCTRL_APLL2SSCCTRL_UNION
 结构说明  : APLL2SSCCTRL 寄存器结构定义。地址偏移量:0x078，初值:0x0000019F，宽度:32
 寄存器说明: APLL2 SSC控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  apll2_ssc_reset      : 1;  /* bit[0]    : 复位信号，高有效。
                                                                0：复位取消
                                                                1：复位有效
                                                                注：不能在PLL工作过程中复位，否则会导致PLL失锁。 */
        unsigned int  apll2_ssc_disable    : 1;  /* bit[1]    : Bypass the modulator，高有效。
                                                                0：正常工作
                                                                1：bypass */
        unsigned int  apll2_ssc_downspread : 1;  /* bit[2]    : 选择center spread或down spread
                                                                0：Center Spread
                                                                1：Down Spread */
        unsigned int  apll2_ssc_spread     : 3;  /* bit[3-5]  : 设置调制深度(spread%)
                                                                3'b000 = 0
                                                                3'b001 = 0.049%
                                                                3'b010 = 0.098%
                                                                3'b011 = 0.195%
                                                                3'b100 = 0.391%
                                                                3'b101 = 0.781%
                                                                3'b110 = 1.563%
                                                                3'b111 = 3.125% */
        unsigned int  apll2_ssc_divval     : 4;  /* bit[6-9]  : 设置频谱调制的频率，一般约为32KHz；
                                                                freq=(CLKSSCG / (DIVVAL * #points))，其中points为128；当REFDIV=1时，CLKSSCG=FREF。 */
        unsigned int  reserved             : 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_PMCTRL_APLL2SSCCTRL_UNION;
#endif
#define SOC_PMCTRL_APLL2SSCCTRL_apll2_ssc_reset_START       (0)
#define SOC_PMCTRL_APLL2SSCCTRL_apll2_ssc_reset_END         (0)
#define SOC_PMCTRL_APLL2SSCCTRL_apll2_ssc_disable_START     (1)
#define SOC_PMCTRL_APLL2SSCCTRL_apll2_ssc_disable_END       (1)
#define SOC_PMCTRL_APLL2SSCCTRL_apll2_ssc_downspread_START  (2)
#define SOC_PMCTRL_APLL2SSCCTRL_apll2_ssc_downspread_END    (2)
#define SOC_PMCTRL_APLL2SSCCTRL_apll2_ssc_spread_START      (3)
#define SOC_PMCTRL_APLL2SSCCTRL_apll2_ssc_spread_END        (5)
#define SOC_PMCTRL_APLL2SSCCTRL_apll2_ssc_divval_START      (6)
#define SOC_PMCTRL_APLL2SSCCTRL_apll2_ssc_divval_END        (9)


/*****************************************************************************
 结构名    : SOC_PMCTRL_PPLL1SSCCTRL_UNION
 结构说明  : PPLL1SSCCTRL 寄存器结构定义。地址偏移量:0x084，初值:0x0000019F，宽度:32
 寄存器说明: PPLL1 SSC控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ppll1_ssc_reset      : 1;  /* bit[0]    : 复位信号，高有效。
                                                                0：复位取消
                                                                1：复位有效
                                                                注：不能在PLL工作过程中复位，否则会导致PLL失锁。 */
        unsigned int  ppll1_ssc_disable    : 1;  /* bit[1]    : Bypass the modulator，高有效。
                                                                0：正常工作
                                                                1：bypass */
        unsigned int  ppll1_ssc_downspread : 1;  /* bit[2]    : 选择center spread或down spread
                                                                0：Center Spread
                                                                1：Down Spread */
        unsigned int  ppll1_ssc_spread     : 3;  /* bit[3-5]  : 设置调制深度(spread%)
                                                                3'b000 = 0
                                                                3'b001 = 0.049%
                                                                3'b010 = 0.098%
                                                                3'b011 = 0.195%
                                                                3'b100 = 0.391%
                                                                3'b101 = 0.781%
                                                                3'b110 = 1.563%
                                                                3'b111 = 3.125% */
        unsigned int  ppll1_ssc_divval     : 4;  /* bit[6-9]  : 设置频谱调制的频率，一般约为32KHz；
                                                                freq=(CLKSSCG / (DIVVAL * #points))，其中points为128；当REFDIV=1时，CLKSSCG=FREF。 */
        unsigned int  reserved             : 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_PMCTRL_PPLL1SSCCTRL_UNION;
#endif
#define SOC_PMCTRL_PPLL1SSCCTRL_ppll1_ssc_reset_START       (0)
#define SOC_PMCTRL_PPLL1SSCCTRL_ppll1_ssc_reset_END         (0)
#define SOC_PMCTRL_PPLL1SSCCTRL_ppll1_ssc_disable_START     (1)
#define SOC_PMCTRL_PPLL1SSCCTRL_ppll1_ssc_disable_END       (1)
#define SOC_PMCTRL_PPLL1SSCCTRL_ppll1_ssc_downspread_START  (2)
#define SOC_PMCTRL_PPLL1SSCCTRL_ppll1_ssc_downspread_END    (2)
#define SOC_PMCTRL_PPLL1SSCCTRL_ppll1_ssc_spread_START      (3)
#define SOC_PMCTRL_PPLL1SSCCTRL_ppll1_ssc_spread_END        (5)
#define SOC_PMCTRL_PPLL1SSCCTRL_ppll1_ssc_divval_START      (6)
#define SOC_PMCTRL_PPLL1SSCCTRL_ppll1_ssc_divval_END        (9)


/*****************************************************************************
 结构名    : SOC_PMCTRL_PPLL2SSCCTRL_UNION
 结构说明  : PPLL2SSCCTRL 寄存器结构定义。地址偏移量:0x088，初值:0x0000019F，宽度:32
 寄存器说明: PPLL2 SSC控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ppll2_ssc_reset      : 1;  /* bit[0]    : 复位信号，高有效。
                                                                0：复位取消
                                                                1：复位有效
                                                                注：不能在PLL工作过程中复位，否则会导致PLL失锁。 */
        unsigned int  ppll2_ssc_disable    : 1;  /* bit[1]    : Bypass the modulator，高有效。
                                                                0：正常工作
                                                                1：bypass */
        unsigned int  ppll2_ssc_downspread : 1;  /* bit[2]    : 选择center spread或down spread
                                                                0：Center Spread
                                                                1：Down Spread */
        unsigned int  ppll2_ssc_spread     : 3;  /* bit[3-5]  : 设置调制深度(spread%)
                                                                3'b000 = 0
                                                                3'b001 = 0.049%
                                                                3'b010 = 0.098%
                                                                3'b011 = 0.195%
                                                                3'b100 = 0.391%
                                                                3'b101 = 0.781%
                                                                3'b110 = 1.563%
                                                                3'b111 = 3.125% */
        unsigned int  ppll2_ssc_divval     : 4;  /* bit[6-9]  : 设置频谱调制的频率，一般约为32KHz；
                                                                freq=(CLKSSCG / (DIVVAL * #points))，其中points为128；当REFDIV=1时，CLKSSCG=FREF。 */
        unsigned int  reserved             : 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_PMCTRL_PPLL2SSCCTRL_UNION;
#endif
#define SOC_PMCTRL_PPLL2SSCCTRL_ppll2_ssc_reset_START       (0)
#define SOC_PMCTRL_PPLL2SSCCTRL_ppll2_ssc_reset_END         (0)
#define SOC_PMCTRL_PPLL2SSCCTRL_ppll2_ssc_disable_START     (1)
#define SOC_PMCTRL_PPLL2SSCCTRL_ppll2_ssc_disable_END       (1)
#define SOC_PMCTRL_PPLL2SSCCTRL_ppll2_ssc_downspread_START  (2)
#define SOC_PMCTRL_PPLL2SSCCTRL_ppll2_ssc_downspread_END    (2)
#define SOC_PMCTRL_PPLL2SSCCTRL_ppll2_ssc_spread_START      (3)
#define SOC_PMCTRL_PPLL2SSCCTRL_ppll2_ssc_spread_END        (5)
#define SOC_PMCTRL_PPLL2SSCCTRL_ppll2_ssc_divval_START      (6)
#define SOC_PMCTRL_PPLL2SSCCTRL_ppll2_ssc_divval_END        (9)


/*****************************************************************************
 结构名    : SOC_PMCTRL_PPLL3SSCCTRL_UNION
 结构说明  : PPLL3SSCCTRL 寄存器结构定义。地址偏移量:0x08C，初值:0x0000019F，宽度:32
 寄存器说明: PPLL3 SSC控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ppll3_ssc_reset      : 1;  /* bit[0]    : 复位信号，高有效。
                                                                0：复位取消
                                                                1：复位有效
                                                                注：不能在PLL工作过程中复位，否则会导致PLL失锁。 */
        unsigned int  ppll3_ssc_disable    : 1;  /* bit[1]    : Bypass the modulator，高有效。
                                                                0：正常工作
                                                                1：bypass */
        unsigned int  ppll3_ssc_downspread : 1;  /* bit[2]    : 选择center spread或down spread
                                                                0：Center Spread
                                                                1：Down Spread */
        unsigned int  ppll3_ssc_spread     : 3;  /* bit[3-5]  : 设置调制深度(spread%)
                                                                3'b000 = 0
                                                                3'b001 = 0.049%
                                                                3'b010 = 0.098%
                                                                3'b011 = 0.195%
                                                                3'b100 = 0.391%
                                                                3'b101 = 0.781%
                                                                3'b110 = 1.563%
                                                                3'b111 = 3.125% */
        unsigned int  ppll3_ssc_divval     : 4;  /* bit[6-9]  : 设置频谱调制的频率，一般约为32KHz；
                                                                freq=(CLKSSCG / (DIVVAL * #points))，其中points为128；当REFDIV=1时，CLKSSCG=FREF。 */
        unsigned int  reserved             : 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_PMCTRL_PPLL3SSCCTRL_UNION;
#endif
#define SOC_PMCTRL_PPLL3SSCCTRL_ppll3_ssc_reset_START       (0)
#define SOC_PMCTRL_PPLL3SSCCTRL_ppll3_ssc_reset_END         (0)
#define SOC_PMCTRL_PPLL3SSCCTRL_ppll3_ssc_disable_START     (1)
#define SOC_PMCTRL_PPLL3SSCCTRL_ppll3_ssc_disable_END       (1)
#define SOC_PMCTRL_PPLL3SSCCTRL_ppll3_ssc_downspread_START  (2)
#define SOC_PMCTRL_PPLL3SSCCTRL_ppll3_ssc_downspread_END    (2)
#define SOC_PMCTRL_PPLL3SSCCTRL_ppll3_ssc_spread_START      (3)
#define SOC_PMCTRL_PPLL3SSCCTRL_ppll3_ssc_spread_END        (5)
#define SOC_PMCTRL_PPLL3SSCCTRL_ppll3_ssc_divval_START      (6)
#define SOC_PMCTRL_PPLL3SSCCTRL_ppll3_ssc_divval_END        (9)


/*****************************************************************************
 结构名    : SOC_PMCTRL_PMUMOD_UNION
 结构说明  : PMUMOD 寄存器结构定义。地址偏移量:0x094，初值:0x00000000，宽度:32
 寄存器说明: PMU供电模式寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pmu_mod  : 1;  /* bit[0-0] : PMU供电模式选择。
                                                   0：统一供电模式；
                                                   1：单独供电模式； */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_PMCTRL_PMUMOD_UNION;
#endif
#define SOC_PMCTRL_PMUMOD_pmu_mod_START   (0)
#define SOC_PMCTRL_PMUMOD_pmu_mod_END     (0)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPUDVFSMOD_UNION
 结构说明  : A53_CPUDVFSMOD 寄存器结构定义。地址偏移量:0x098，初值:0x00000000，宽度:32
 寄存器说明: A53_CPU DVFS模式寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cpu_dvfs_mod : 1;  /* bit[0-0] : A53 DVFS模式选择。
                                                           0：切换APLL模式；
                                                           1：缓调频模式（固定APLL）；
                                                           当配置为缓调频模式时，PLL Lock Mod必须配置为等待超时模式 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_CPUDVFSMOD_UNION;
#endif
#define SOC_PMCTRL_A53_CPUDVFSMOD_a53_cpu_dvfs_mod_START  (0)
#define SOC_PMCTRL_A53_CPUDVFSMOD_a53_cpu_dvfs_mod_END    (0)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPUCLKSEL_UNION
 结构说明  : A53_CPUCLKSEL 寄存器结构定义。地址偏移量:0x09C，初值:0x00000002，宽度:32
 寄存器说明: A53_CPU 时钟来源选择寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_clk_sel : 2;  /* bit[0-1] : A53_时钟选择哪个时钟来源。
                                                      00：A53_时钟选择480Mhz；
                                                      01：A53_时钟选择19.2MHz；
                                                      1X：A53_时钟选择APLL。 */
        unsigned int  reserved    : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_CPUCLKSEL_UNION;
#endif
#define SOC_PMCTRL_A53_CPUCLKSEL_a53_clk_sel_START  (0)
#define SOC_PMCTRL_A53_CPUCLKSEL_a53_clk_sel_END    (1)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPUDVFSEN_UNION
 结构说明  : A53_CPUDVFSEN 寄存器结构定义。地址偏移量:0x0A0，初值:0x00000000，宽度:32
 寄存器说明: A53_CPU DVFS使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cpu_dvfs_en : 1;  /* bit[0-0] : A53_ DVFS使能。
                                                          0：A53_ DVFS功能关闭；
                                                          1：A53_ DVFS功能开启。 */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_CPUDVFSEN_UNION;
#endif
#define SOC_PMCTRL_A53_CPUDVFSEN_a53_cpu_dvfs_en_START  (0)
#define SOC_PMCTRL_A53_CPUDVFSEN_a53_cpu_dvfs_en_END    (0)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPUPLLSEL_UNION
 结构说明  : A53_CPUPLLSEL 寄存器结构定义。地址偏移量:0x0A4，初值:0x00000010，宽度:32
 寄存器说明: A53_CPU PLL选择寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_apll_sel   : 2;  /* bit[0-1] : A53_时钟选择哪个PLL。
                                                         00：A53_时钟选择APLL0；
                                                         01：A53_时钟选择APLL1；
                                                         1X：A53_时钟选择APLL2。 */
        unsigned int  a53_pll_sw_ack : 5;  /* bit[2-6] : 当前A53_时钟选择哪个时钟的状态指示。
                                                         00001：A53_时钟选择480Mhz；
                                                         00010：A53_时钟选择19.2MHz；
                                                         00100：A53_时钟选择APLL0。
                                                         01000：A53_时钟选择APLL1。
                                                         10000：A53_时钟选择APLL2。 */
        unsigned int  reserved       : 25; /* bit[7-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_CPUPLLSEL_UNION;
#endif
#define SOC_PMCTRL_A53_CPUPLLSEL_a53_apll_sel_START    (0)
#define SOC_PMCTRL_A53_CPUPLLSEL_a53_apll_sel_END      (1)
#define SOC_PMCTRL_A53_CPUPLLSEL_a53_pll_sw_ack_START  (2)
#define SOC_PMCTRL_A53_CPUPLLSEL_a53_pll_sw_ack_END    (6)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPUCLKDIV_UNION
 结构说明  : A53_CPUCLKDIV 寄存器结构定义。地址偏移量:0x0A8，初值:0x000000A1，宽度:32
 寄存器说明: A53_CPU时钟分频寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_pclkendbg_sel : 2;  /* bit[0-1] : A53_ DebugAPB接口时钟频率比选择
                                                            000:1:2 001:1:4 010:1:6 011:1:8 */
        unsigned int  a53_atclken_sel   : 2;  /* bit[2-3] : A53_ ATB接口时钟频率比选择
                                                            000:1:2 001:1:4 010:1:6 011:1:8 */
        unsigned int  a53_aclkenm_sel   : 3;  /* bit[4-6] : A53_ ACE master接口时钟频率比选择
                                                            000:1:1 001:1:2 010:1:3 011:1:4
                                                            100:1:5 101:1:6 110:1:7 111:1:8 */
        unsigned int  a53_atclken_l_sel : 1;  /* bit[7-7] : A53_ trace时钟二级频率比选择
                                                            0:1:2 1:1:4 */
        unsigned int  reserved          : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_CPUCLKDIV_UNION;
#endif
#define SOC_PMCTRL_A53_CPUCLKDIV_a53_pclkendbg_sel_START  (0)
#define SOC_PMCTRL_A53_CPUCLKDIV_a53_pclkendbg_sel_END    (1)
#define SOC_PMCTRL_A53_CPUCLKDIV_a53_atclken_sel_START    (2)
#define SOC_PMCTRL_A53_CPUCLKDIV_a53_atclken_sel_END      (3)
#define SOC_PMCTRL_A53_CPUCLKDIV_a53_aclkenm_sel_START    (4)
#define SOC_PMCTRL_A53_CPUCLKDIV_a53_aclkenm_sel_END      (6)
#define SOC_PMCTRL_A53_CPUCLKDIV_a53_atclken_l_sel_START  (7)
#define SOC_PMCTRL_A53_CPUCLKDIV_a53_atclken_l_sel_END    (7)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPUDVFSSTART_UNION
 结构说明  : A53_CPUDVFSSTART 寄存器结构定义。地址偏移量:0x0AC，初值:0x00000000，宽度:32
 寄存器说明: A53_CPU DVFS启动寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cpu_profile_updn : 1;  /* bit[0-0] : A53_ DVFS启动。
                                                               0：A53_ DVFS降低Profile启动；
                                                               1：A53_ DVFS提升Profile启动。 */
        unsigned int  reserved             : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_CPUDVFSSTART_UNION;
#endif
#define SOC_PMCTRL_A53_CPUDVFSSTART_a53_cpu_profile_updn_START  (0)
#define SOC_PMCTRL_A53_CPUDVFSSTART_a53_cpu_profile_updn_END    (0)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPUCLKPROFILE0_UNION
 结构说明  : A53_CPUCLKPROFILE0 寄存器结构定义。地址偏移量:0x0B0，初值:0x002C0F81，宽度:32
 寄存器说明: A53_CPU频率Profile寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_apll_refdiv    : 6;  /* bit[0-5]  : APLL输入时钟分频参数。 */
        unsigned int  a53_apll_fbdiv     : 12; /* bit[6-17] : APLL反馈时钟整数分频参数。 */
        unsigned int  a53_apll_postdiv1  : 3;  /* bit[18-20]: APLL输出时钟分频参数1。 */
        unsigned int  a53_apll_postdiv2  : 3;  /* bit[21-23]: APLL输出时钟分频参数2。 */
        unsigned int  a53_apll_sw_target : 2;  /* bit[24-25]: APLL跳转目标。 */
        unsigned int  reserved           : 6;  /* bit[26-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_CPUCLKPROFILE0_UNION;
#endif
#define SOC_PMCTRL_A53_CPUCLKPROFILE0_a53_apll_refdiv_START     (0)
#define SOC_PMCTRL_A53_CPUCLKPROFILE0_a53_apll_refdiv_END       (5)
#define SOC_PMCTRL_A53_CPUCLKPROFILE0_a53_apll_fbdiv_START      (6)
#define SOC_PMCTRL_A53_CPUCLKPROFILE0_a53_apll_fbdiv_END        (17)
#define SOC_PMCTRL_A53_CPUCLKPROFILE0_a53_apll_postdiv1_START   (18)
#define SOC_PMCTRL_A53_CPUCLKPROFILE0_a53_apll_postdiv1_END     (20)
#define SOC_PMCTRL_A53_CPUCLKPROFILE0_a53_apll_postdiv2_START   (21)
#define SOC_PMCTRL_A53_CPUCLKPROFILE0_a53_apll_postdiv2_END     (23)
#define SOC_PMCTRL_A53_CPUCLKPROFILE0_a53_apll_sw_target_START  (24)
#define SOC_PMCTRL_A53_CPUCLKPROFILE0_a53_apll_sw_target_END    (25)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPUCLKPROFILE0_1_UNION
 结构说明  : A53_CPUCLKPROFILE0_1 寄存器结构定义。地址偏移量:0x0B4，初值:0x02F80000，宽度:32
 寄存器说明: A53_CPU频率Profile寄存器0_1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_apll_fracdiv : 24; /* bit[0-23] : APLL反馈时钟分数分频器。 */
        unsigned int  a53_apll_int_mod : 1;  /* bit[24-24]: APLL整数分频模式。
                                                            0：分数分频模式；
                                                            1：整数分频模式。
                                                            注意：本PLL要求软件只使用分数分频模式 */
        unsigned int  a53_apll_cfg_vld : 1;  /* bit[25-25]: APLL配置有效标志。
                                                            0：配置无效；
                                                            1：配置有效。 */
        unsigned int  reserved         : 6;  /* bit[26-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_CPUCLKPROFILE0_1_UNION;
#endif
#define SOC_PMCTRL_A53_CPUCLKPROFILE0_1_a53_apll_fracdiv_START  (0)
#define SOC_PMCTRL_A53_CPUCLKPROFILE0_1_a53_apll_fracdiv_END    (23)
#define SOC_PMCTRL_A53_CPUCLKPROFILE0_1_a53_apll_int_mod_START  (24)
#define SOC_PMCTRL_A53_CPUCLKPROFILE0_1_a53_apll_int_mod_END    (24)
#define SOC_PMCTRL_A53_CPUCLKPROFILE0_1_a53_apll_cfg_vld_START  (25)
#define SOC_PMCTRL_A53_CPUCLKPROFILE0_1_a53_apll_cfg_vld_END    (25)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPUCLKPROFILE1_UNION
 结构说明  : A53_CPUCLKPROFILE1 寄存器结构定义。地址偏移量:0x0B8，初值:0x000000A1，宽度:32
 寄存器说明: A53_CPU频率Profile寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_pclkendbg_prof   : 2;  /* bit[0-1] : A53_ DebugAPB接口时钟频率比选择
                                                               000:1:2 001:1:4 010:1:6 011:1:8 */
        unsigned int  a53_atclken_sel_prof : 2;  /* bit[2-3] : A53_ ATB接口时钟频率比选择参数 */
        unsigned int  a53_aclkenm_sel_prof : 3;  /* bit[4-6] : A53_ ACE master接口时钟频率比选择参数 */
        unsigned int  a53_atclken_l_prof   : 1;  /* bit[7-7] : A53_ trace时钟二级频率比选择
                                                               0:1:2 1:1:4 */
        unsigned int  reserved             : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_CPUCLKPROFILE1_UNION;
#endif
#define SOC_PMCTRL_A53_CPUCLKPROFILE1_a53_pclkendbg_prof_START    (0)
#define SOC_PMCTRL_A53_CPUCLKPROFILE1_a53_pclkendbg_prof_END      (1)
#define SOC_PMCTRL_A53_CPUCLKPROFILE1_a53_atclken_sel_prof_START  (2)
#define SOC_PMCTRL_A53_CPUCLKPROFILE1_a53_atclken_sel_prof_END    (3)
#define SOC_PMCTRL_A53_CPUCLKPROFILE1_a53_aclkenm_sel_prof_START  (4)
#define SOC_PMCTRL_A53_CPUCLKPROFILE1_a53_aclkenm_sel_prof_END    (6)
#define SOC_PMCTRL_A53_CPUCLKPROFILE1_a53_atclken_l_prof_START    (7)
#define SOC_PMCTRL_A53_CPUCLKPROFILE1_a53_atclken_l_prof_END      (7)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPUVOLMOD_UNION
 结构说明  : A53_CPUVOLMOD 寄存器结构定义。地址偏移量:0x0BC，初值:0x00000000，宽度:32
 寄存器说明: A53_CPU DVFS时调压模式寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cpu_vol_mod         : 1;  /* bit[0-0] : A53_ DVFS时，是否需要调压。
                                                                  0：A53_ DVFS时，不需要调压；
                                                                  1：A53_ DVFS时，需要调压。 */
        unsigned int  a53_cpu_clk_off_vol_mod : 1;  /* bit[1-1] : A53_调压时，A53_时钟是否关闭。
                                                                  0：A53_调压时，A53_时钟保持打开；
                                                                  1：A53_调压时，A53_时钟要求关闭。 */
        unsigned int  reserved                : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_CPUVOLMOD_UNION;
#endif
#define SOC_PMCTRL_A53_CPUVOLMOD_a53_cpu_vol_mod_START          (0)
#define SOC_PMCTRL_A53_CPUVOLMOD_a53_cpu_vol_mod_END            (0)
#define SOC_PMCTRL_A53_CPUVOLMOD_a53_cpu_clk_off_vol_mod_START  (1)
#define SOC_PMCTRL_A53_CPUVOLMOD_a53_cpu_clk_off_vol_mod_END    (1)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPUVOLPROFILE_UNION
 结构说明  : A53_CPUVOLPROFILE 寄存器结构定义。地址偏移量:0x0C0，初值:0x00000000，宽度:32
 寄存器说明: A53_CPU电压Profile寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cpu_vol_idx : 8;  /* bit[0-7] : A53_电压Profile参数。 */
        unsigned int  reserved        : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_CPUVOLPROFILE_UNION;
#endif
#define SOC_PMCTRL_A53_CPUVOLPROFILE_a53_cpu_vol_idx_START  (0)
#define SOC_PMCTRL_A53_CPUVOLPROFILE_a53_cpu_vol_idx_END    (7)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPUPHASEMOD_UNION
 结构说明  : A53_CPUPHASEMOD 寄存器结构定义。地址偏移量:0xC8，初值:0x00000000，宽度:32
 寄存器说明: A53_CPU DVFS时的相位模式寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cpu_phase_mod         : 1;  /* bit[0-0] : A53_ DVFS时，是否改变相位。
                                                                    0：A53_ DVFS时，不改变相位；
                                                                    1：A53_ DVFS时，改变相位。 */
        unsigned int  a53_cpu_clk_off_phase_mod : 1;  /* bit[1-1] : A53_ DVFS改变相位时是否关闭A53_时钟。
                                                                    0：A53_改变相位时，A53_时钟保持打开；
                                                                    1：A53_改变相位时，A53_时钟关闭。 */
        unsigned int  reserved                  : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_CPUPHASEMOD_UNION;
#endif
#define SOC_PMCTRL_A53_CPUPHASEMOD_a53_cpu_phase_mod_START          (0)
#define SOC_PMCTRL_A53_CPUPHASEMOD_a53_cpu_phase_mod_END            (0)
#define SOC_PMCTRL_A53_CPUPHASEMOD_a53_cpu_clk_off_phase_mod_START  (1)
#define SOC_PMCTRL_A53_CPUPHASEMOD_a53_cpu_clk_off_phase_mod_END    (1)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPUPHASEPROFILE_UNION
 结构说明  : A53_CPUPHASEPROFILE 寄存器结构定义。地址偏移量:0x0CC，初值:0x00000000，宽度:32
 寄存器说明: A53_CPU相位Profile寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cpu_phase_idx : 8;  /* bit[0-7] : A53_相位Profile参数。 */
        unsigned int  reserved          : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_CPUPHASEPROFILE_UNION;
#endif
#define SOC_PMCTRL_A53_CPUPHASEPROFILE_a53_cpu_phase_idx_START  (0)
#define SOC_PMCTRL_A53_CPUPHASEPROFILE_a53_cpu_phase_idx_END    (7)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPUVOLPHASESEL_UNION
 结构说明  : A53_CPUVOLPHASESEL 寄存器结构定义。地址偏移量:0x0D0，初值:0x00000000，宽度:32
 寄存器说明: A53_CPU电压/相位配置先后选择寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cpu_vol_phase_sel : 1;  /* bit[0-0] : A53_电压/相位信号输出选择
                                                                0：DVFS时先调相位再调电压，配置profile寄存器。时不需要改变；
                                                                1：DVFS先调电压在调相位，配置profile寄存器。时需要改变（电压profile寄存器。控制相位，相位profile寄存器。控制电压）。 */
        unsigned int  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_CPUVOLPHASESEL_UNION;
#endif
#define SOC_PMCTRL_A53_CPUVOLPHASESEL_a53_cpu_vol_phase_sel_START  (0)
#define SOC_PMCTRL_A53_CPUVOLPHASESEL_a53_cpu_vol_phase_sel_END    (0)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_VOLUPSTEPTIME_UNION
 结构说明  : A53_VOLUPSTEPTIME 寄存器结构定义。地址偏移量:0x0D4，初值:0x00000000，宽度:32
 寄存器说明: A53_电压上升一档稳定步长时间寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_vol_up_step_time : 13; /* bit[0-12] : A53_ CPU电压上升稳定步长时间。 */
        unsigned int  reserved             : 19; /* bit[13-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_VOLUPSTEPTIME_UNION;
#endif
#define SOC_PMCTRL_A53_VOLUPSTEPTIME_a53_vol_up_step_time_START  (0)
#define SOC_PMCTRL_A53_VOLUPSTEPTIME_a53_vol_up_step_time_END    (12)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_VOLDNSTEPTIME_UNION
 结构说明  : A53_VOLDNSTEPTIME 寄存器结构定义。地址偏移量:0x0D8，初值:0x00000000，宽度:32
 寄存器说明: A53_电压下降一档稳定步长时间寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_vol_dn_step_time : 13; /* bit[0-12] : A53_ CPU电压下降稳定步长时间。 */
        unsigned int  reserved             : 19; /* bit[13-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_VOLDNSTEPTIME_UNION;
#endif
#define SOC_PMCTRL_A53_VOLDNSTEPTIME_a53_vol_dn_step_time_START  (0)
#define SOC_PMCTRL_A53_VOLDNSTEPTIME_a53_vol_dn_step_time_END    (12)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_PHASEUPTIME_UNION
 结构说明  : A53_PHASEUPTIME 寄存器结构定义。地址偏移量:0x0DC，初值:0x00000000，宽度:32
 寄存器说明: A53_ DVFS时改变电压相位的上升稳定时间寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_dvfs_phase_up_time : 20; /* bit[0-19] : A53_ DVFS时，改变电压相位的上升稳定时间。 */
        unsigned int  reserved               : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_PHASEUPTIME_UNION;
#endif
#define SOC_PMCTRL_A53_PHASEUPTIME_a53_dvfs_phase_up_time_START  (0)
#define SOC_PMCTRL_A53_PHASEUPTIME_a53_dvfs_phase_up_time_END    (19)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_PHASEDNTIME_UNION
 结构说明  : A53_PHASEDNTIME 寄存器结构定义。地址偏移量:0x0E0，初值:0x00000000，宽度:32
 寄存器说明: A53_ DVFS时改变电压相位的下降稳定时间寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_dvfs_phase_dn_time : 20; /* bit[0-19] : A53_ DVFS时，改变电压相位的下降稳定时间。 */
        unsigned int  reserved               : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_PHASEDNTIME_UNION;
#endif
#define SOC_PMCTRL_A53_PHASEDNTIME_a53_dvfs_phase_dn_time_START  (0)
#define SOC_PMCTRL_A53_PHASEDNTIME_a53_dvfs_phase_dn_time_END    (19)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_PMUHOLDTIME_UNION
 结构说明  : A53_PMUHOLDTIME 寄存器结构定义。地址偏移量:0x0E4，初值:0x00000000，宽度:32
 寄存器说明: A53_电压稳定时间裕量寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_pmu_vol_hold_time : 20; /* bit[0-19] : A53_调压时，由于端口传输时间而增加的电压稳定时间 */
        unsigned int  reserved              : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_PMUHOLDTIME_UNION;
#endif
#define SOC_PMCTRL_A53_PMUHOLDTIME_a53_pmu_vol_hold_time_START  (0)
#define SOC_PMCTRL_A53_PMUHOLDTIME_a53_pmu_vol_hold_time_END    (19)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_PMUSEL_UNION
 结构说明  : A53_PMUSEL 寄存器结构定义。地址偏移量:0x0E8，初值:0x00000000，宽度:32
 寄存器说明: A53_PMU选择寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_pmu_sel : 1;  /* bit[0-0] : A53_输出PMU选择
                                                      0：A53_输出的信号给PMUSSI；
                                                      1：A53_输出的信号给PMUI2C。（只能静态配置） */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_PMUSEL_UNION;
#endif
#define SOC_PMCTRL_A53_PMUSEL_a53_pmu_sel_START  (0)
#define SOC_PMCTRL_A53_PMUSEL_a53_pmu_sel_END    (0)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPUAVSEN_UNION
 结构说明  : A53_CPUAVSEN 寄存器结构定义。地址偏移量:0x0F0，初值:0x00000000，宽度:32
 寄存器说明: A53_CPU AVS使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cpu_avs_en        : 1;  /* bit[0-0] : A53_ AVS使能。
                                                                0：A53_ AVS功能关闭；
                                                                1：A53_ AVS功能开启。 */
        unsigned int  a53_cpu_avs_pwctrl_en : 1;  /* bit[1-1] : A53_ AVS调压使能。
                                                                0：A53_ AVS调压功能关闭；
                                                                1：A53_ AVS调压功能开启。 */
        unsigned int  reserved              : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_CPUAVSEN_UNION;
#endif
#define SOC_PMCTRL_A53_CPUAVSEN_a53_cpu_avs_en_START         (0)
#define SOC_PMCTRL_A53_CPUAVSEN_a53_cpu_avs_en_END           (0)
#define SOC_PMCTRL_A53_CPUAVSEN_a53_cpu_avs_pwctrl_en_START  (1)
#define SOC_PMCTRL_A53_CPUAVSEN_a53_cpu_avs_pwctrl_en_END    (1)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPUAVSPARAMOD_UNION
 结构说明  : A53_CPUAVSPARAMOD 寄存器结构定义。地址偏移量:0x0F4，初值:0x00000000，宽度:32
 寄存器说明: A53_CPU AVS参数模式寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cpu_avspara_mod : 1;  /* bit[0-0] : A53_ AVS参数实时更新控制。
                                                              通常，A53_ AVS参数在A53_ DVFS运行之后更新；如果对这个寄存器。写1，AVS参数立即更新；如果对这个寄存器。写0，无效。 */
        unsigned int  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_CPUAVSPARAMOD_UNION;
#endif
#define SOC_PMCTRL_A53_CPUAVSPARAMOD_a53_cpu_avspara_mod_START  (0)
#define SOC_PMCTRL_A53_CPUAVSPARAMOD_a53_cpu_avspara_mod_END    (0)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPUAVSPARA0_UNION
 结构说明  : A53_CPUAVSPARA0 寄存器结构定义。地址偏移量:0x0F8，初值:0x00000000，宽度:32
 寄存器说明: A53_CPU AVS参数寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0             : 2;  /* bit[0-1]  : 保留 */
        unsigned int  a53_cpu_avs_opc_offset : 10; /* bit[2-11] : A53_ AVS原始性能码偏移。 */
        unsigned int  a53_cpu_avs_rcc        : 5;  /* bit[12-16]: A53_ AVS参考校准码。 */
        unsigned int  a53_cpu_avs_irgap      : 5;  /* bit[17-21]: A53_ AVS IRDrop裕量。 */
        unsigned int  a53_cpu_avs_opc_mod    : 2;  /* bit[22-23]: A53_ AVS中同一个HPM OPC值的多次采样如何处理。
                                                                  00：OPC取均值；
                                                                  01：OPC取最小值；
                                                                  10：OPC取最大值；
                                                                  11：保留。 */
        unsigned int  a53_cpu_avs_hpm_sel    : 4;  /* bit[24-27]: A53_ AVS中多个HPM的PC值如何处理。
                                                                  0000：取CPU0 HPM的PC值；
                                                                  0001：取CPU1 HPM的PC值；
                                                                  0010：取CPU2 HPM的PC值；
                                                                  0011：取CPU3 HPM的PC值；
                                                                  0100：取SCU0 HPM的PC值；
                                                                  0101：取CPU4 HPM的PC值；
                                                                  0110：取CPU5 HPM的PC值；
                                                                  0111：取CPU6 HPM的PC值；
                                                                  1000：取CPU7 HPM的PC值；
                                                                  1001：取SCU1 HPM的PC值；
                                                                  1010：取HPM中的最小值；
                                                                  其他：取HPM中的最大值； */
        unsigned int  a53_cpu_avs_opc_shift  : 3;  /* bit[28-30]: A53_ AVS原始性能码移位。 */
        unsigned int  reserved_1             : 1;  /* bit[31-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_CPUAVSPARA0_UNION;
#endif
#define SOC_PMCTRL_A53_CPUAVSPARA0_a53_cpu_avs_opc_offset_START  (2)
#define SOC_PMCTRL_A53_CPUAVSPARA0_a53_cpu_avs_opc_offset_END    (11)
#define SOC_PMCTRL_A53_CPUAVSPARA0_a53_cpu_avs_rcc_START         (12)
#define SOC_PMCTRL_A53_CPUAVSPARA0_a53_cpu_avs_rcc_END           (16)
#define SOC_PMCTRL_A53_CPUAVSPARA0_a53_cpu_avs_irgap_START       (17)
#define SOC_PMCTRL_A53_CPUAVSPARA0_a53_cpu_avs_irgap_END         (21)
#define SOC_PMCTRL_A53_CPUAVSPARA0_a53_cpu_avs_opc_mod_START     (22)
#define SOC_PMCTRL_A53_CPUAVSPARA0_a53_cpu_avs_opc_mod_END       (23)
#define SOC_PMCTRL_A53_CPUAVSPARA0_a53_cpu_avs_hpm_sel_START     (24)
#define SOC_PMCTRL_A53_CPUAVSPARA0_a53_cpu_avs_hpm_sel_END       (27)
#define SOC_PMCTRL_A53_CPUAVSPARA0_a53_cpu_avs_opc_shift_START   (28)
#define SOC_PMCTRL_A53_CPUAVSPARA0_a53_cpu_avs_opc_shift_END     (30)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPUAVSPARA1_UNION
 结构说明  : A53_CPUAVSPARA1 寄存器结构定义。地址偏移量:0x0FC，初值:0x00000000，宽度:32
 寄存器说明: A53_CPU AVS参数寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cpu_avs_vol_up_gain1 : 4;  /* bit[0-3]  : A53_ AVS升压增益。 */
        unsigned int  a53_cpu_avs_vol_up_gain2 : 4;  /* bit[4-7]  : A53_ AVS升压增益。 */
        unsigned int  a53_cpu_avs_vol_up_gain3 : 4;  /* bit[8-11] : A53_ AVS升压增益。 */
        unsigned int  a53_cpu_avs_vol_up_gain4 : 4;  /* bit[12-15]: A53_ AVS升压增益。 */
        unsigned int  a53_cpu_avs_vol_up_gain5 : 4;  /* bit[16-19]: A53_ AVS升压增益。 */
        unsigned int  a53_cpu_avs_vol_up_gain6 : 4;  /* bit[20-23]: A53_ AVS升压增益。 */
        unsigned int  a53_cpu_avs_vol_up_gain7 : 4;  /* bit[24-27]: A53_ AVS升压增益。 */
        unsigned int  a53_cpu_avs_vol_up_gain8 : 4;  /* bit[28-31]: A53_ AVS升压增益。 */
    } reg;
} SOC_PMCTRL_A53_CPUAVSPARA1_UNION;
#endif
#define SOC_PMCTRL_A53_CPUAVSPARA1_a53_cpu_avs_vol_up_gain1_START  (0)
#define SOC_PMCTRL_A53_CPUAVSPARA1_a53_cpu_avs_vol_up_gain1_END    (3)
#define SOC_PMCTRL_A53_CPUAVSPARA1_a53_cpu_avs_vol_up_gain2_START  (4)
#define SOC_PMCTRL_A53_CPUAVSPARA1_a53_cpu_avs_vol_up_gain2_END    (7)
#define SOC_PMCTRL_A53_CPUAVSPARA1_a53_cpu_avs_vol_up_gain3_START  (8)
#define SOC_PMCTRL_A53_CPUAVSPARA1_a53_cpu_avs_vol_up_gain3_END    (11)
#define SOC_PMCTRL_A53_CPUAVSPARA1_a53_cpu_avs_vol_up_gain4_START  (12)
#define SOC_PMCTRL_A53_CPUAVSPARA1_a53_cpu_avs_vol_up_gain4_END    (15)
#define SOC_PMCTRL_A53_CPUAVSPARA1_a53_cpu_avs_vol_up_gain5_START  (16)
#define SOC_PMCTRL_A53_CPUAVSPARA1_a53_cpu_avs_vol_up_gain5_END    (19)
#define SOC_PMCTRL_A53_CPUAVSPARA1_a53_cpu_avs_vol_up_gain6_START  (20)
#define SOC_PMCTRL_A53_CPUAVSPARA1_a53_cpu_avs_vol_up_gain6_END    (23)
#define SOC_PMCTRL_A53_CPUAVSPARA1_a53_cpu_avs_vol_up_gain7_START  (24)
#define SOC_PMCTRL_A53_CPUAVSPARA1_a53_cpu_avs_vol_up_gain7_END    (27)
#define SOC_PMCTRL_A53_CPUAVSPARA1_a53_cpu_avs_vol_up_gain8_START  (28)
#define SOC_PMCTRL_A53_CPUAVSPARA1_a53_cpu_avs_vol_up_gain8_END    (31)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPUAVSPARA2_UNION
 结构说明  : A53_CPUAVSPARA2 寄存器结构定义。地址偏移量:0x100，初值:0x00000000，宽度:32
 寄存器说明: A53_CPU AVS参数寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cpu_avs_vol_up_gain9  : 4;  /* bit[0-3]  : A53_ AVS升压增益。 */
        unsigned int  a53_cpu_avs_vol_up_gain10 : 4;  /* bit[4-7]  : A53_ AVS升压增益。 */
        unsigned int  a53_cpu_avs_vol_up_gain11 : 4;  /* bit[8-11] : A53_ AVS升压增益。 */
        unsigned int  a53_cpu_avs_vol_up_gain12 : 4;  /* bit[12-15]: A53_ AVS升压增益。 */
        unsigned int  a53_cpu_avs_vol_up_gain13 : 4;  /* bit[16-19]: A53_ AVS升压增益。 */
        unsigned int  a53_cpu_avs_vol_up_gain14 : 4;  /* bit[20-23]: A53_ AVS升压增益。 */
        unsigned int  a53_cpu_avs_vol_up_gain15 : 7;  /* bit[24-30]: A53_ AVS升压增益。 */
        unsigned int  reserved                  : 1;  /* bit[31-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_CPUAVSPARA2_UNION;
#endif
#define SOC_PMCTRL_A53_CPUAVSPARA2_a53_cpu_avs_vol_up_gain9_START   (0)
#define SOC_PMCTRL_A53_CPUAVSPARA2_a53_cpu_avs_vol_up_gain9_END     (3)
#define SOC_PMCTRL_A53_CPUAVSPARA2_a53_cpu_avs_vol_up_gain10_START  (4)
#define SOC_PMCTRL_A53_CPUAVSPARA2_a53_cpu_avs_vol_up_gain10_END    (7)
#define SOC_PMCTRL_A53_CPUAVSPARA2_a53_cpu_avs_vol_up_gain11_START  (8)
#define SOC_PMCTRL_A53_CPUAVSPARA2_a53_cpu_avs_vol_up_gain11_END    (11)
#define SOC_PMCTRL_A53_CPUAVSPARA2_a53_cpu_avs_vol_up_gain12_START  (12)
#define SOC_PMCTRL_A53_CPUAVSPARA2_a53_cpu_avs_vol_up_gain12_END    (15)
#define SOC_PMCTRL_A53_CPUAVSPARA2_a53_cpu_avs_vol_up_gain13_START  (16)
#define SOC_PMCTRL_A53_CPUAVSPARA2_a53_cpu_avs_vol_up_gain13_END    (19)
#define SOC_PMCTRL_A53_CPUAVSPARA2_a53_cpu_avs_vol_up_gain14_START  (20)
#define SOC_PMCTRL_A53_CPUAVSPARA2_a53_cpu_avs_vol_up_gain14_END    (23)
#define SOC_PMCTRL_A53_CPUAVSPARA2_a53_cpu_avs_vol_up_gain15_START  (24)
#define SOC_PMCTRL_A53_CPUAVSPARA2_a53_cpu_avs_vol_up_gain15_END    (30)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPUAVSPARA3_UNION
 结构说明  : A53_CPUAVSPARA3 寄存器结构定义。地址偏移量:0x104，初值:0x00000000，宽度:32
 寄存器说明: A53_CPU AVS参数寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cpu_avs_vol_dn_gain1 : 4;  /* bit[0-3]  : A53_ AVS降压增益。 */
        unsigned int  a53_cpu_avs_vol_dn_gain2 : 4;  /* bit[4-7]  : A53_ AVS降压增益。 */
        unsigned int  a53_cpu_avs_vol_dn_gain3 : 4;  /* bit[8-11] : A53_ AVS降压增益。 */
        unsigned int  a53_cpu_avs_vol_dn_gain4 : 4;  /* bit[12-15]: A53_ AVS降压增益。 */
        unsigned int  a53_cpu_avs_vol_dn_gain5 : 4;  /* bit[16-19]: A53_ AVS降压增益。 */
        unsigned int  a53_cpu_avs_vol_dn_gain6 : 4;  /* bit[20-23]: A53_ AVS降压增益。 */
        unsigned int  a53_cpu_avs_vol_dn_gain7 : 4;  /* bit[24-27]: A53_ AVS降压增益。 */
        unsigned int  a53_cpu_avs_vol_dn_gain8 : 4;  /* bit[28-31]: A53_ AVS降压增益。 */
    } reg;
} SOC_PMCTRL_A53_CPUAVSPARA3_UNION;
#endif
#define SOC_PMCTRL_A53_CPUAVSPARA3_a53_cpu_avs_vol_dn_gain1_START  (0)
#define SOC_PMCTRL_A53_CPUAVSPARA3_a53_cpu_avs_vol_dn_gain1_END    (3)
#define SOC_PMCTRL_A53_CPUAVSPARA3_a53_cpu_avs_vol_dn_gain2_START  (4)
#define SOC_PMCTRL_A53_CPUAVSPARA3_a53_cpu_avs_vol_dn_gain2_END    (7)
#define SOC_PMCTRL_A53_CPUAVSPARA3_a53_cpu_avs_vol_dn_gain3_START  (8)
#define SOC_PMCTRL_A53_CPUAVSPARA3_a53_cpu_avs_vol_dn_gain3_END    (11)
#define SOC_PMCTRL_A53_CPUAVSPARA3_a53_cpu_avs_vol_dn_gain4_START  (12)
#define SOC_PMCTRL_A53_CPUAVSPARA3_a53_cpu_avs_vol_dn_gain4_END    (15)
#define SOC_PMCTRL_A53_CPUAVSPARA3_a53_cpu_avs_vol_dn_gain5_START  (16)
#define SOC_PMCTRL_A53_CPUAVSPARA3_a53_cpu_avs_vol_dn_gain5_END    (19)
#define SOC_PMCTRL_A53_CPUAVSPARA3_a53_cpu_avs_vol_dn_gain6_START  (20)
#define SOC_PMCTRL_A53_CPUAVSPARA3_a53_cpu_avs_vol_dn_gain6_END    (23)
#define SOC_PMCTRL_A53_CPUAVSPARA3_a53_cpu_avs_vol_dn_gain7_START  (24)
#define SOC_PMCTRL_A53_CPUAVSPARA3_a53_cpu_avs_vol_dn_gain7_END    (27)
#define SOC_PMCTRL_A53_CPUAVSPARA3_a53_cpu_avs_vol_dn_gain8_START  (28)
#define SOC_PMCTRL_A53_CPUAVSPARA3_a53_cpu_avs_vol_dn_gain8_END    (31)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPUAVSPARA4_UNION
 结构说明  : A53_CPUAVSPARA4 寄存器结构定义。地址偏移量:0x108，初值:0x00000000，宽度:32
 寄存器说明: A53_CPU AVS参数寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cpu_avs_vol_dn_gain9  : 4;  /* bit[0-3]  : A53_ AVS降压增益。 */
        unsigned int  a53_cpu_avs_vol_dn_gain10 : 4;  /* bit[4-7]  : A53_ AVS降压增益。 */
        unsigned int  a53_cpu_avs_vol_dn_gain11 : 4;  /* bit[8-11] : A53_ AVS降压增益。 */
        unsigned int  a53_cpu_avs_vol_dn_gain12 : 4;  /* bit[12-15]: A53_ AVS降压增益。 */
        unsigned int  a53_cpu_avs_vol_dn_gain13 : 4;  /* bit[16-19]: A53_ AVS降压增益。 */
        unsigned int  a53_cpu_avs_vol_dn_gain14 : 4;  /* bit[20-23]: A53_ AVS降压增益。 */
        unsigned int  a53_cpu_avs_vol_dn_gain15 : 7;  /* bit[24-30]: A53_ AVS降压增益。 */
        unsigned int  reserved                  : 1;  /* bit[31-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_CPUAVSPARA4_UNION;
#endif
#define SOC_PMCTRL_A53_CPUAVSPARA4_a53_cpu_avs_vol_dn_gain9_START   (0)
#define SOC_PMCTRL_A53_CPUAVSPARA4_a53_cpu_avs_vol_dn_gain9_END     (3)
#define SOC_PMCTRL_A53_CPUAVSPARA4_a53_cpu_avs_vol_dn_gain10_START  (4)
#define SOC_PMCTRL_A53_CPUAVSPARA4_a53_cpu_avs_vol_dn_gain10_END    (7)
#define SOC_PMCTRL_A53_CPUAVSPARA4_a53_cpu_avs_vol_dn_gain11_START  (8)
#define SOC_PMCTRL_A53_CPUAVSPARA4_a53_cpu_avs_vol_dn_gain11_END    (11)
#define SOC_PMCTRL_A53_CPUAVSPARA4_a53_cpu_avs_vol_dn_gain12_START  (12)
#define SOC_PMCTRL_A53_CPUAVSPARA4_a53_cpu_avs_vol_dn_gain12_END    (15)
#define SOC_PMCTRL_A53_CPUAVSPARA4_a53_cpu_avs_vol_dn_gain13_START  (16)
#define SOC_PMCTRL_A53_CPUAVSPARA4_a53_cpu_avs_vol_dn_gain13_END    (19)
#define SOC_PMCTRL_A53_CPUAVSPARA4_a53_cpu_avs_vol_dn_gain14_START  (20)
#define SOC_PMCTRL_A53_CPUAVSPARA4_a53_cpu_avs_vol_dn_gain14_END    (23)
#define SOC_PMCTRL_A53_CPUAVSPARA4_a53_cpu_avs_vol_dn_gain15_START  (24)
#define SOC_PMCTRL_A53_CPUAVSPARA4_a53_cpu_avs_vol_dn_gain15_END    (30)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPUAVSPARA5_UNION
 结构说明  : A53_CPUAVSPARA5 寄存器结构定义。地址偏移量:0x10C，初值:0x00000000，宽度:32
 寄存器说明: A53_CPU AVS参数寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cpu_avs_max_vol : 7;  /* bit[0-6]  : A53_ AVS最大电压限制。 */
        unsigned int  a53_cpu_avs_min_vol : 7;  /* bit[7-13] : A53_ AVS最小电压限制。 */
        unsigned int  reserved            : 18; /* bit[14-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_CPUAVSPARA5_UNION;
#endif
#define SOC_PMCTRL_A53_CPUAVSPARA5_a53_cpu_avs_max_vol_START  (0)
#define SOC_PMCTRL_A53_CPUAVSPARA5_a53_cpu_avs_max_vol_END    (6)
#define SOC_PMCTRL_A53_CPUAVSPARA5_a53_cpu_avs_min_vol_START  (7)
#define SOC_PMCTRL_A53_CPUAVSPARA5_a53_cpu_avs_min_vol_END    (13)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPUAVSPARA6_UNION
 结构说明  : A53_CPUAVSPARA6 寄存器结构定义。地址偏移量:0x110，初值:0x00000000，宽度:32
 寄存器说明: A53_CPU AVS使能寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cpu_avs_sample_num : 22; /* bit[0-21] : A53_ AVS性能码采样次数。配置值必须是2的N次方。 */
        unsigned int  reserved               : 10; /* bit[22-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_CPUAVSPARA6_UNION;
#endif
#define SOC_PMCTRL_A53_CPUAVSPARA6_a53_cpu_avs_sample_num_START  (0)
#define SOC_PMCTRL_A53_CPUAVSPARA6_a53_cpu_avs_sample_num_END    (21)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPUHPMTYP_UNION
 结构说明  : A53_CPUHPMTYP 寄存器结构定义。地址偏移量:0x114，初值:0x000007C0，宽度:32
 寄存器说明: A53_CPU HPM类型选择寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cpu_hpm_type  : 1;  /* bit[0]    : AVS选择使用CPU HPM类型。
                                                             0：AVS选择使用标准HPM；
                                                             1：AVS选择使用X型HPM。 */
        unsigned int  a53_cpu0_hpm_mask : 1;  /* bit[1]    : AVS控制是否屏蔽CPU0 HPM。
                                                             0：不屏蔽；
                                                             1：屏蔽。 */
        unsigned int  a53_cpu1_hpm_mask : 1;  /* bit[2]    : AVS控制是否屏蔽CPU1 HPM。
                                                             0：不屏蔽；
                                                             1：屏蔽。 */
        unsigned int  a53_cpu2_hpm_mask : 1;  /* bit[3]    : AVS控制是否屏蔽CPU2 HPM。
                                                             0：不屏蔽；
                                                             1：屏蔽。 */
        unsigned int  a53_cpu3_hpm_mask : 1;  /* bit[4]    : AVS控制是否屏蔽CPU3 HPM。
                                                             0：不屏蔽；
                                                             1：屏蔽。 */
        unsigned int  a53_scu0_hpm_mask : 1;  /* bit[5]    : AVS控制是否屏蔽SCU0 HPM。
                                                             0：不屏蔽；
                                                             1：屏蔽。 */
        unsigned int  a53_cpu4_hpm_mask : 1;  /* bit[6]    : AVS控制是否屏蔽CPU4 HPM。
                                                             0：不屏蔽；
                                                             1：屏蔽。 */
        unsigned int  a53_cpu5_hpm_mask : 1;  /* bit[7]    : AVS控制是否屏蔽CPU5 HPM。
                                                             0：不屏蔽；
                                                             1：屏蔽。 */
        unsigned int  a53_cpu6_hpm_mask : 1;  /* bit[8]    : AVS控制是否屏蔽CPU6 HPM。
                                                             0：不屏蔽；
                                                             1：屏蔽。 */
        unsigned int  a53_cpu7_hpm_mask : 1;  /* bit[9]    : AVS控制是否屏蔽CPU7 HPM。
                                                             0：不屏蔽；
                                                             1：屏蔽。 */
        unsigned int  a53_scu1_hpm_mask : 1;  /* bit[10]   : AVS控制是否屏蔽SCU1 HPM。
                                                             0：不屏蔽；
                                                             1：屏蔽。 */
        unsigned int  reserved          : 5;  /* bit[11-15]: 保留 */
        unsigned int  biten             : 16; /* bit[16-31]: 每个比特位的使能位：
                                                             只有当biten对应的比特位为1'b1，相应的比特位才起作用。biten[0]就是bit 0的使能位。写1有效。 */
    } reg;
} SOC_PMCTRL_A53_CPUHPMTYP_UNION;
#endif
#define SOC_PMCTRL_A53_CPUHPMTYP_a53_cpu_hpm_type_START   (0)
#define SOC_PMCTRL_A53_CPUHPMTYP_a53_cpu_hpm_type_END     (0)
#define SOC_PMCTRL_A53_CPUHPMTYP_a53_cpu0_hpm_mask_START  (1)
#define SOC_PMCTRL_A53_CPUHPMTYP_a53_cpu0_hpm_mask_END    (1)
#define SOC_PMCTRL_A53_CPUHPMTYP_a53_cpu1_hpm_mask_START  (2)
#define SOC_PMCTRL_A53_CPUHPMTYP_a53_cpu1_hpm_mask_END    (2)
#define SOC_PMCTRL_A53_CPUHPMTYP_a53_cpu2_hpm_mask_START  (3)
#define SOC_PMCTRL_A53_CPUHPMTYP_a53_cpu2_hpm_mask_END    (3)
#define SOC_PMCTRL_A53_CPUHPMTYP_a53_cpu3_hpm_mask_START  (4)
#define SOC_PMCTRL_A53_CPUHPMTYP_a53_cpu3_hpm_mask_END    (4)
#define SOC_PMCTRL_A53_CPUHPMTYP_a53_scu0_hpm_mask_START  (5)
#define SOC_PMCTRL_A53_CPUHPMTYP_a53_scu0_hpm_mask_END    (5)
#define SOC_PMCTRL_A53_CPUHPMTYP_a53_cpu4_hpm_mask_START  (6)
#define SOC_PMCTRL_A53_CPUHPMTYP_a53_cpu4_hpm_mask_END    (6)
#define SOC_PMCTRL_A53_CPUHPMTYP_a53_cpu5_hpm_mask_START  (7)
#define SOC_PMCTRL_A53_CPUHPMTYP_a53_cpu5_hpm_mask_END    (7)
#define SOC_PMCTRL_A53_CPUHPMTYP_a53_cpu6_hpm_mask_START  (8)
#define SOC_PMCTRL_A53_CPUHPMTYP_a53_cpu6_hpm_mask_END    (8)
#define SOC_PMCTRL_A53_CPUHPMTYP_a53_cpu7_hpm_mask_START  (9)
#define SOC_PMCTRL_A53_CPUHPMTYP_a53_cpu7_hpm_mask_END    (9)
#define SOC_PMCTRL_A53_CPUHPMTYP_a53_scu1_hpm_mask_START  (10)
#define SOC_PMCTRL_A53_CPUHPMTYP_a53_scu1_hpm_mask_END    (10)
#define SOC_PMCTRL_A53_CPUHPMTYP_biten_START              (16)
#define SOC_PMCTRL_A53_CPUHPMTYP_biten_END                (31)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPU01HPMEN_UNION
 结构说明  : A53_CPU01HPMEN 寄存器结构定义。地址偏移量:0x118，初值:0x00000000，宽度:32
 寄存器说明: A53_CPU01 HPM使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cpu0_hpm_en : 1;  /* bit[0-0] : CPU0 HPM使能。
                                                          HPM使能控制除了软件可以置位或清除，在AVS流程中也会被AVS主控逻辑自动置位或清除。 */
        unsigned int  a53_cpu1_hpm_en : 1;  /* bit[1-1] : CPU1 HPM使能。
                                                          HPM使能控制除了软件可以置位或清除，在AVS流程中也会被AVS主控逻辑自动置位或清除。 */
        unsigned int  a53_scu_hpm_en  : 1;  /* bit[2-2] : SCU HPM使能。
                                                          HPM使能控制除了软件可以置位或清除，在AVS流程中也会被AVS主控逻辑自动置位或清除。 */
        unsigned int  reserved        : 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_CPU01HPMEN_UNION;
#endif
#define SOC_PMCTRL_A53_CPU01HPMEN_a53_cpu0_hpm_en_START  (0)
#define SOC_PMCTRL_A53_CPU01HPMEN_a53_cpu0_hpm_en_END    (0)
#define SOC_PMCTRL_A53_CPU01HPMEN_a53_cpu1_hpm_en_START  (1)
#define SOC_PMCTRL_A53_CPU01HPMEN_a53_cpu1_hpm_en_END    (1)
#define SOC_PMCTRL_A53_CPU01HPMEN_a53_scu_hpm_en_START   (2)
#define SOC_PMCTRL_A53_CPU01HPMEN_a53_scu_hpm_en_END     (2)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPU01HPMXEN_UNION
 结构说明  : A53_CPU01HPMXEN 寄存器结构定义。地址偏移量:0x11C，初值:0x00000000，宽度:32
 寄存器说明: A53_CPU01 HPMX使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cpu0_hpmx_en : 1;  /* bit[0-0] : CPU0 HPMX使能。
                                                           HPMX使能控制除了软件可以置位或清除，在AVS流程中也会被AVS主控逻辑自动置位或清除。 */
        unsigned int  a53_cpu1_hpmx_en : 1;  /* bit[1-1] : CPU1 HPMX使能。
                                                           HPMX使能控制除了软件可以置位或清除，在AVS流程中也会被AVS主控逻辑自动置位或清除。 */
        unsigned int  a53_scu_hpmx_en  : 1;  /* bit[2-2] : SCU HPMX使能。
                                                           HPMX使能控制除了软件可以置位或清除，在AVS流程中也会被AVS主控逻辑自动置位或清除。 */
        unsigned int  reserved         : 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_CPU01HPMXEN_UNION;
#endif
#define SOC_PMCTRL_A53_CPU01HPMXEN_a53_cpu0_hpmx_en_START  (0)
#define SOC_PMCTRL_A53_CPU01HPMXEN_a53_cpu0_hpmx_en_END    (0)
#define SOC_PMCTRL_A53_CPU01HPMXEN_a53_cpu1_hpmx_en_START  (1)
#define SOC_PMCTRL_A53_CPU01HPMXEN_a53_cpu1_hpmx_en_END    (1)
#define SOC_PMCTRL_A53_CPU01HPMXEN_a53_scu_hpmx_en_START   (2)
#define SOC_PMCTRL_A53_CPU01HPMXEN_a53_scu_hpmx_en_END     (2)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPU01HPMOPCVALID_UNION
 结构说明  : A53_CPU01HPMOPCVALID 寄存器结构定义。地址偏移量:0x120，初值:0x00000000，宽度:32
 寄存器说明: A53_CPU01 HPM OPC有效寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cpu0_hpm_opc_vld  : 1;  /* bit[0-0] : CPU0 HPM原始性能码有效的状态指示。 */
        unsigned int  a53_cpu1_hpm_opc_vld  : 1;  /* bit[1-1] : CPU1 HPM原始性能码有效的状态指示。 */
        unsigned int  a53_scu_hpm_opc_vld   : 1;  /* bit[2-2] : SCU HPM原始性能码有效的状态指示。 */
        unsigned int  a53_cpu0_hpmx_opc_vld : 1;  /* bit[3-3] : CPU0 HPMX原始性能码有效的状态指示。 */
        unsigned int  a53_cpu1_hpmx_opc_vld : 1;  /* bit[4-4] : CPU1 HPMX原始性能码有效的状态指示。 */
        unsigned int  a53_scu_hpmx_opc_vld  : 1;  /* bit[5-5] : SCU HPMX原始性能码有效的状态指示。 */
        unsigned int  reserved              : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_CPU01HPMOPCVALID_UNION;
#endif
#define SOC_PMCTRL_A53_CPU01HPMOPCVALID_a53_cpu0_hpm_opc_vld_START   (0)
#define SOC_PMCTRL_A53_CPU01HPMOPCVALID_a53_cpu0_hpm_opc_vld_END     (0)
#define SOC_PMCTRL_A53_CPU01HPMOPCVALID_a53_cpu1_hpm_opc_vld_START   (1)
#define SOC_PMCTRL_A53_CPU01HPMOPCVALID_a53_cpu1_hpm_opc_vld_END     (1)
#define SOC_PMCTRL_A53_CPU01HPMOPCVALID_a53_scu_hpm_opc_vld_START    (2)
#define SOC_PMCTRL_A53_CPU01HPMOPCVALID_a53_scu_hpm_opc_vld_END      (2)
#define SOC_PMCTRL_A53_CPU01HPMOPCVALID_a53_cpu0_hpmx_opc_vld_START  (3)
#define SOC_PMCTRL_A53_CPU01HPMOPCVALID_a53_cpu0_hpmx_opc_vld_END    (3)
#define SOC_PMCTRL_A53_CPU01HPMOPCVALID_a53_cpu1_hpmx_opc_vld_START  (4)
#define SOC_PMCTRL_A53_CPU01HPMOPCVALID_a53_cpu1_hpmx_opc_vld_END    (4)
#define SOC_PMCTRL_A53_CPU01HPMOPCVALID_a53_scu_hpmx_opc_vld_START   (5)
#define SOC_PMCTRL_A53_CPU01HPMOPCVALID_a53_scu_hpmx_opc_vld_END     (5)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPU01HPMOPC_UNION
 结构说明  : A53_CPU01HPMOPC 寄存器结构定义。地址偏移量:0x124，初值:0x00000000，宽度:32
 寄存器说明: A53_CPU01 HPM OPC寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cpu0_hpm_opc : 10; /* bit[0-9]  : CPU0 HPM原始性能码。 */
        unsigned int  a53_cpu1_hpm_opc : 10; /* bit[10-19]: CPU1 HPM原始性能码。 */
        unsigned int  a53_scu_hpm_opc  : 10; /* bit[20-29]: SCU HPM原始性能码。 */
        unsigned int  reserved         : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_CPU01HPMOPC_UNION;
#endif
#define SOC_PMCTRL_A53_CPU01HPMOPC_a53_cpu0_hpm_opc_START  (0)
#define SOC_PMCTRL_A53_CPU01HPMOPC_a53_cpu0_hpm_opc_END    (9)
#define SOC_PMCTRL_A53_CPU01HPMOPC_a53_cpu1_hpm_opc_START  (10)
#define SOC_PMCTRL_A53_CPU01HPMOPC_a53_cpu1_hpm_opc_END    (19)
#define SOC_PMCTRL_A53_CPU01HPMOPC_a53_scu_hpm_opc_START   (20)
#define SOC_PMCTRL_A53_CPU01HPMOPC_a53_scu_hpm_opc_END     (29)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPU01HPMXOPC_UNION
 结构说明  : A53_CPU01HPMXOPC 寄存器结构定义。地址偏移量:0x128，初值:0x00000000，宽度:32
 寄存器说明: A53_CPU01 HPMX OPC寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cpu0_hpmx_opc : 10; /* bit[0-9]  : CPU0 HPMX原始性能码。 */
        unsigned int  a53_cpu1_hpmx_opc : 10; /* bit[10-19]: CPU1 HPMX原始性能码。 */
        unsigned int  a53_scu_hpmx_opc  : 10; /* bit[20-29]: SCU HPMX原始性能码。 */
        unsigned int  reserved          : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_CPU01HPMXOPC_UNION;
#endif
#define SOC_PMCTRL_A53_CPU01HPMXOPC_a53_cpu0_hpmx_opc_START  (0)
#define SOC_PMCTRL_A53_CPU01HPMXOPC_a53_cpu0_hpmx_opc_END    (9)
#define SOC_PMCTRL_A53_CPU01HPMXOPC_a53_cpu1_hpmx_opc_START  (10)
#define SOC_PMCTRL_A53_CPU01HPMXOPC_a53_cpu1_hpmx_opc_END    (19)
#define SOC_PMCTRL_A53_CPU01HPMXOPC_a53_scu_hpmx_opc_START   (20)
#define SOC_PMCTRL_A53_CPU01HPMXOPC_a53_scu_hpmx_opc_END     (29)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPU01HPMPC_UNION
 结构说明  : A53_CPU01HPMPC 寄存器结构定义。地址偏移量:0x12C，初值:0x00000000，宽度:32
 寄存器说明: A53_CPU01 HPM PC寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cpu0_hpm_pc_avs : 10; /* bit[0-9]  : CPU0 HPM性能码。 */
        unsigned int  a53_cpu1_hpm_pc_avs : 10; /* bit[10-19]: CPU1 HPM性能码。 */
        unsigned int  a53_scu_hpm_pc_avs  : 10; /* bit[20-29]: SCU HPM性能码。 */
        unsigned int  reserved            : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_CPU01HPMPC_UNION;
#endif
#define SOC_PMCTRL_A53_CPU01HPMPC_a53_cpu0_hpm_pc_avs_START  (0)
#define SOC_PMCTRL_A53_CPU01HPMPC_a53_cpu0_hpm_pc_avs_END    (9)
#define SOC_PMCTRL_A53_CPU01HPMPC_a53_cpu1_hpm_pc_avs_START  (10)
#define SOC_PMCTRL_A53_CPU01HPMPC_a53_cpu1_hpm_pc_avs_END    (19)
#define SOC_PMCTRL_A53_CPU01HPMPC_a53_scu_hpm_pc_avs_START   (20)
#define SOC_PMCTRL_A53_CPU01HPMPC_a53_scu_hpm_pc_avs_END     (29)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPU23HPMEN_UNION
 结构说明  : A53_CPU23HPMEN 寄存器结构定义。地址偏移量:0x134，初值:0x00000000，宽度:32
 寄存器说明: A53_CPU23 HPM使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cpu2_hpm_en : 1;  /* bit[0-0] : CPU2 HPM使能。
                                                          HPM使能控制除了软件可以置位或清除，在AVS流程中也会被AVS主控逻辑自动置位或清除。 */
        unsigned int  a53_cpu3_hpm_en : 1;  /* bit[1-1] : CPU3 HPM使能。
                                                          HPM使能控制除了软件可以置位或清除，在AVS流程中也会被AVS主控逻辑自动置位或清除。 */
        unsigned int  reserved        : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_CPU23HPMEN_UNION;
#endif
#define SOC_PMCTRL_A53_CPU23HPMEN_a53_cpu2_hpm_en_START  (0)
#define SOC_PMCTRL_A53_CPU23HPMEN_a53_cpu2_hpm_en_END    (0)
#define SOC_PMCTRL_A53_CPU23HPMEN_a53_cpu3_hpm_en_START  (1)
#define SOC_PMCTRL_A53_CPU23HPMEN_a53_cpu3_hpm_en_END    (1)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPU23HPMXEN_UNION
 结构说明  : A53_CPU23HPMXEN 寄存器结构定义。地址偏移量:0x138，初值:0x00000000，宽度:32
 寄存器说明: A53_CPU23 HPMX使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cpu2_hpmx_en : 1;  /* bit[0-0] : CPU2 HPMX使能。
                                                           HPMX使能控制除了软件可以置位或清除，在AVS流程中也会被AVS主控逻辑自动置位或清除。 */
        unsigned int  a53_cpu3_hpmx_en : 1;  /* bit[1-1] : CPU3 HPMX使能。
                                                           HPMX使能控制除了软件可以置位或清除，在AVS流程中也会被AVS主控逻辑自动置位或清除。 */
        unsigned int  reserved         : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_CPU23HPMXEN_UNION;
#endif
#define SOC_PMCTRL_A53_CPU23HPMXEN_a53_cpu2_hpmx_en_START  (0)
#define SOC_PMCTRL_A53_CPU23HPMXEN_a53_cpu2_hpmx_en_END    (0)
#define SOC_PMCTRL_A53_CPU23HPMXEN_a53_cpu3_hpmx_en_START  (1)
#define SOC_PMCTRL_A53_CPU23HPMXEN_a53_cpu3_hpmx_en_END    (1)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPU23HPMOPCVALID_UNION
 结构说明  : A53_CPU23HPMOPCVALID 寄存器结构定义。地址偏移量:0x13C，初值:0x00000000，宽度:32
 寄存器说明: A53_CPU23 HPM OPC有效寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cpu2_hpm_opc_vld  : 1;  /* bit[0-0] : CPU2 HPM原始性能码有效的状态指示。 */
        unsigned int  a53_cpu3_hpm_opc_vld  : 1;  /* bit[1-1] : CPU3 HPM原始性能码有效的状态指示。 */
        unsigned int  a53_cpu2_hpmx_opc_vld : 1;  /* bit[2-2] : CPU2 HPMX原始性能码有效的状态指示。 */
        unsigned int  a53_cpu3_hpmx_opc_vld : 1;  /* bit[3-3] : CPU3 HPMX原始性能码有效的状态指示。 */
        unsigned int  reserved              : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_CPU23HPMOPCVALID_UNION;
#endif
#define SOC_PMCTRL_A53_CPU23HPMOPCVALID_a53_cpu2_hpm_opc_vld_START   (0)
#define SOC_PMCTRL_A53_CPU23HPMOPCVALID_a53_cpu2_hpm_opc_vld_END     (0)
#define SOC_PMCTRL_A53_CPU23HPMOPCVALID_a53_cpu3_hpm_opc_vld_START   (1)
#define SOC_PMCTRL_A53_CPU23HPMOPCVALID_a53_cpu3_hpm_opc_vld_END     (1)
#define SOC_PMCTRL_A53_CPU23HPMOPCVALID_a53_cpu2_hpmx_opc_vld_START  (2)
#define SOC_PMCTRL_A53_CPU23HPMOPCVALID_a53_cpu2_hpmx_opc_vld_END    (2)
#define SOC_PMCTRL_A53_CPU23HPMOPCVALID_a53_cpu3_hpmx_opc_vld_START  (3)
#define SOC_PMCTRL_A53_CPU23HPMOPCVALID_a53_cpu3_hpmx_opc_vld_END    (3)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPU23HPMOPC_UNION
 结构说明  : A53_CPU23HPMOPC 寄存器结构定义。地址偏移量:0x140，初值:0x00000000，宽度:32
 寄存器说明: A53_CPU23 HPM OPC寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cpu2_hpm_opc : 10; /* bit[0-9]  : CPU2 HPM原始性能码。 */
        unsigned int  a53_cpu3_hpm_opc : 10; /* bit[10-19]: CPU3 HPM原始性能码。 */
        unsigned int  reserved         : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_CPU23HPMOPC_UNION;
#endif
#define SOC_PMCTRL_A53_CPU23HPMOPC_a53_cpu2_hpm_opc_START  (0)
#define SOC_PMCTRL_A53_CPU23HPMOPC_a53_cpu2_hpm_opc_END    (9)
#define SOC_PMCTRL_A53_CPU23HPMOPC_a53_cpu3_hpm_opc_START  (10)
#define SOC_PMCTRL_A53_CPU23HPMOPC_a53_cpu3_hpm_opc_END    (19)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPU23HPMXOPC_UNION
 结构说明  : A53_CPU23HPMXOPC 寄存器结构定义。地址偏移量:0x144，初值:0x00000000，宽度:32
 寄存器说明: A53_CPU23 HPMX OPC寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cpu2_hpmx_opc : 10; /* bit[0-9]  : CPU2 HPMX原始性能码。 */
        unsigned int  a53_cpu3_hpmx_opc : 10; /* bit[10-19]: CPU3 HPMX原始性能码。 */
        unsigned int  reserved          : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_CPU23HPMXOPC_UNION;
#endif
#define SOC_PMCTRL_A53_CPU23HPMXOPC_a53_cpu2_hpmx_opc_START  (0)
#define SOC_PMCTRL_A53_CPU23HPMXOPC_a53_cpu2_hpmx_opc_END    (9)
#define SOC_PMCTRL_A53_CPU23HPMXOPC_a53_cpu3_hpmx_opc_START  (10)
#define SOC_PMCTRL_A53_CPU23HPMXOPC_a53_cpu3_hpmx_opc_END    (19)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPU23HPMPC_UNION
 结构说明  : A53_CPU23HPMPC 寄存器结构定义。地址偏移量:0x148，初值:0x00000000，宽度:32
 寄存器说明: A53_CPU23 HPM PC寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cpu2_hpm_pc_avs : 10; /* bit[0-9]  : CPU2 HPM性能码。 */
        unsigned int  a53_cpu3_hpm_pc_avs : 10; /* bit[10-19]: CPU3 HPM性能码。 */
        unsigned int  reserved            : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_CPU23HPMPC_UNION;
#endif
#define SOC_PMCTRL_A53_CPU23HPMPC_a53_cpu2_hpm_pc_avs_START  (0)
#define SOC_PMCTRL_A53_CPU23HPMPC_a53_cpu2_hpm_pc_avs_END    (9)
#define SOC_PMCTRL_A53_CPU23HPMPC_a53_cpu3_hpm_pc_avs_START  (10)
#define SOC_PMCTRL_A53_CPU23HPMPC_a53_cpu3_hpm_pc_avs_END    (19)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPUHPMCLKDIV_UNION
 结构说明  : A53_CPUHPMCLKDIV 寄存器结构定义。地址偏移量:0x150，初值:0x00000001，宽度:32
 寄存器说明: A53_CPU HPM时钟分频寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cpu_avs_hpm_div : 6;  /* bit[0-5] : A53 HPM时钟分频器。 */
        unsigned int  reserved            : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_CPUHPMCLKDIV_UNION;
#endif
#define SOC_PMCTRL_A53_CPUHPMCLKDIV_a53_cpu_avs_hpm_div_START  (0)
#define SOC_PMCTRL_A53_CPUHPMCLKDIV_a53_cpu_avs_hpm_div_END    (5)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A53_CPUAVSVOLIDX_UNION
 结构说明  : A53_CPUAVSVOLIDX 寄存器结构定义。地址偏移量:0x154，初值:0x00000000，宽度:32
 寄存器说明: A53_CPU AVS电压控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cpu_avs_vol_idx    : 8;  /* bit[0-7] : A53 AVS当前电压值。该值可以通过软件配置。如果配置该寄存器。时bit 8不写1，则需要软件配置该寄存器。值与PMU电压值相同 */
        unsigned int  a53_cpu_vol_chg_sftreq : 1;  /* bit[8-8] : A53 CPU电压改变软件请求信号。
                                                                 写1：请求改变电压，电压值为bit 7:0值
                                                                 写0：无效果 */
        unsigned int  reserved               : 23; /* bit[9-31]: 保留 */
    } reg;
} SOC_PMCTRL_A53_CPUAVSVOLIDX_UNION;
#endif
#define SOC_PMCTRL_A53_CPUAVSVOLIDX_a53_cpu_avs_vol_idx_START     (0)
#define SOC_PMCTRL_A53_CPUAVSVOLIDX_a53_cpu_avs_vol_idx_END       (7)
#define SOC_PMCTRL_A53_CPUAVSVOLIDX_a53_cpu_vol_chg_sftreq_START  (8)
#define SOC_PMCTRL_A53_CPUAVSVOLIDX_a53_cpu_vol_chg_sftreq_END    (8)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPUDVFSMOD_UNION
 结构说明  : A57_CPUDVFSMOD 寄存器结构定义。地址偏移量:0x158，初值:0x00000000，宽度:32
 寄存器说明: A57_CPU DVFS模式寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_cpu_dvfs_mod : 1;  /* bit[0-0] : A57 DVFS模式选择。
                                                           0：切换APLL模式；
                                                           1：缓调频模式（固定APLL）；
                                                           当配置为缓调频模式时，PLL Lock Mod必须配置为等待超时模式 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_CPUDVFSMOD_UNION;
#endif
#define SOC_PMCTRL_A57_CPUDVFSMOD_a57_cpu_dvfs_mod_START  (0)
#define SOC_PMCTRL_A57_CPUDVFSMOD_a57_cpu_dvfs_mod_END    (0)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPUCLKSEL_UNION
 结构说明  : A57_CPUCLKSEL 寄存器结构定义。地址偏移量:0x15C，初值:0x00000002，宽度:32
 寄存器说明: A57_CPU 时钟来源选择寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_clk_sel : 2;  /* bit[0-1] : A57_时钟选择哪个时钟来源。
                                                      00：A57_时钟选择480Mhz；
                                                      01：A57_时钟选择19.2MHz；
                                                      1X：A57_时钟选择APLL。 */
        unsigned int  reserved    : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_CPUCLKSEL_UNION;
#endif
#define SOC_PMCTRL_A57_CPUCLKSEL_a57_clk_sel_START  (0)
#define SOC_PMCTRL_A57_CPUCLKSEL_a57_clk_sel_END    (1)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPUDVFSEN_UNION
 结构说明  : A57_CPUDVFSEN 寄存器结构定义。地址偏移量:0x160，初值:0x00000000，宽度:32
 寄存器说明: A57_CPU DVFS使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_cpu_dvfs_en : 1;  /* bit[0-0] : A57_ DVFS使能。
                                                          0：A57_ DVFS功能关闭；
                                                          1：A57_ DVFS功能开启。 */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_CPUDVFSEN_UNION;
#endif
#define SOC_PMCTRL_A57_CPUDVFSEN_a57_cpu_dvfs_en_START  (0)
#define SOC_PMCTRL_A57_CPUDVFSEN_a57_cpu_dvfs_en_END    (0)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPUPLLSEL_UNION
 结构说明  : A57_CPUPLLSEL 寄存器结构定义。地址偏移量:0x164，初值:0x00000021，宽度:32
 寄存器说明: A57_CPU PLL选择寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_apll_sel   : 2;  /* bit[0-1] : A57_时钟选择哪个PLL。
                                                         00：A57_时钟选择APLL0；
                                                         01：A57_时钟选择APLL1；
                                                         1X：A57_时钟选择APLL2。 */
        unsigned int  a57_pll_sw_ack : 5;  /* bit[2-6] : 当前A57_时钟选择哪个时钟的状态指示。
                                                         00001：A57_时钟选择480Mhz；
                                                         00010：A57_时钟选择19.2MHz；
                                                         00100：A57_时钟选择APLL0。
                                                         01000：A57_时钟选择APLL1。
                                                         10000：A57_时钟选择APLL2。 */
        unsigned int  reserved       : 25; /* bit[7-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_CPUPLLSEL_UNION;
#endif
#define SOC_PMCTRL_A57_CPUPLLSEL_a57_apll_sel_START    (0)
#define SOC_PMCTRL_A57_CPUPLLSEL_a57_apll_sel_END      (1)
#define SOC_PMCTRL_A57_CPUPLLSEL_a57_pll_sw_ack_START  (2)
#define SOC_PMCTRL_A57_CPUPLLSEL_a57_pll_sw_ack_END    (6)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPUCLKDIV_UNION
 结构说明  : A57_CPUCLKDIV 寄存器结构定义。地址偏移量:0x168，初值:0x000000A0，宽度:32
 寄存器说明: A57_CPU时钟分频寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0        : 2;  /* bit[0-1] : 保留 */
        unsigned int  a57_atclken_sel   : 2;  /* bit[2-3] : A57_ ATB接口时钟频率比选择
                                                            000:1:2 001:1:4 010:1:6 011:1:8 */
        unsigned int  a57_aclkenm_sel   : 3;  /* bit[4-6] : A57_ ACE master接口时钟频率比选择
                                                            000:1:1 001:1:2 010:1:3 011:1:4
                                                            100:1:5 101:1:6 110:1:7 111:1:8 */
        unsigned int  a57_atclken_l_sel : 1;  /* bit[7-7] : A57_ trace时钟二级频率比选择
                                                            0:1:2 1:1:4 */
        unsigned int  reserved_1        : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_CPUCLKDIV_UNION;
#endif
#define SOC_PMCTRL_A57_CPUCLKDIV_a57_atclken_sel_START    (2)
#define SOC_PMCTRL_A57_CPUCLKDIV_a57_atclken_sel_END      (3)
#define SOC_PMCTRL_A57_CPUCLKDIV_a57_aclkenm_sel_START    (4)
#define SOC_PMCTRL_A57_CPUCLKDIV_a57_aclkenm_sel_END      (6)
#define SOC_PMCTRL_A57_CPUCLKDIV_a57_atclken_l_sel_START  (7)
#define SOC_PMCTRL_A57_CPUCLKDIV_a57_atclken_l_sel_END    (7)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPUDVFSSTART_UNION
 结构说明  : A57_CPUDVFSSTART 寄存器结构定义。地址偏移量:0x16C，初值:0x00000000，宽度:32
 寄存器说明: A57_CPU DVFS启动寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_cpu_profile_updn : 1;  /* bit[0-0] : A57_ DVFS启动。
                                                               0：A57_ DVFS降低Profile启动；
                                                               1：A57_ DVFS提升Profile启动。 */
        unsigned int  reserved             : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_CPUDVFSSTART_UNION;
#endif
#define SOC_PMCTRL_A57_CPUDVFSSTART_a57_cpu_profile_updn_START  (0)
#define SOC_PMCTRL_A57_CPUDVFSSTART_a57_cpu_profile_updn_END    (0)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPUCLKPROFILE0_UNION
 结构说明  : A57_CPUCLKPROFILE0 寄存器结构定义。地址偏移量:0x170，初值:0x002C0F81，宽度:32
 寄存器说明: A57_CPU频率Profile寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_apll_refdiv    : 6;  /* bit[0-5]  : APLL输入时钟分频参数。 */
        unsigned int  a57_apll_fbdiv     : 12; /* bit[6-17] : APLL反馈时钟整数分频参数。 */
        unsigned int  a57_apll_postdiv1  : 3;  /* bit[18-20]: APLL输出时钟分频参数1。 */
        unsigned int  a57_apll_postdiv2  : 3;  /* bit[21-23]: APLL输出时钟分频参数2。 */
        unsigned int  a57_apll_sw_target : 2;  /* bit[24-25]: APLL跳转目标。 */
        unsigned int  reserved           : 6;  /* bit[26-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_CPUCLKPROFILE0_UNION;
#endif
#define SOC_PMCTRL_A57_CPUCLKPROFILE0_a57_apll_refdiv_START     (0)
#define SOC_PMCTRL_A57_CPUCLKPROFILE0_a57_apll_refdiv_END       (5)
#define SOC_PMCTRL_A57_CPUCLKPROFILE0_a57_apll_fbdiv_START      (6)
#define SOC_PMCTRL_A57_CPUCLKPROFILE0_a57_apll_fbdiv_END        (17)
#define SOC_PMCTRL_A57_CPUCLKPROFILE0_a57_apll_postdiv1_START   (18)
#define SOC_PMCTRL_A57_CPUCLKPROFILE0_a57_apll_postdiv1_END     (20)
#define SOC_PMCTRL_A57_CPUCLKPROFILE0_a57_apll_postdiv2_START   (21)
#define SOC_PMCTRL_A57_CPUCLKPROFILE0_a57_apll_postdiv2_END     (23)
#define SOC_PMCTRL_A57_CPUCLKPROFILE0_a57_apll_sw_target_START  (24)
#define SOC_PMCTRL_A57_CPUCLKPROFILE0_a57_apll_sw_target_END    (25)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPUCLKPROFILE0_1_UNION
 结构说明  : A57_CPUCLKPROFILE0_1 寄存器结构定义。地址偏移量:0x174，初值:0x02F80000，宽度:32
 寄存器说明: A57_CPU频率Profile寄存器0_1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_apll_fracdiv : 24; /* bit[0-23] : APLL反馈时钟分数分频器。 */
        unsigned int  a57_apll_int_mod : 1;  /* bit[24-24]: APLL整数分频模式。
                                                            0：分数分频模式；
                                                            1：整数分频模式。
                                                            注意：本PLL要求软件只使用分数分频模式 */
        unsigned int  a57_apll_cfg_vld : 1;  /* bit[25-25]: APLL配置有效标志。
                                                            0：配置无效；
                                                            1：配置有效。 */
        unsigned int  reserved         : 6;  /* bit[26-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_CPUCLKPROFILE0_1_UNION;
#endif
#define SOC_PMCTRL_A57_CPUCLKPROFILE0_1_a57_apll_fracdiv_START  (0)
#define SOC_PMCTRL_A57_CPUCLKPROFILE0_1_a57_apll_fracdiv_END    (23)
#define SOC_PMCTRL_A57_CPUCLKPROFILE0_1_a57_apll_int_mod_START  (24)
#define SOC_PMCTRL_A57_CPUCLKPROFILE0_1_a57_apll_int_mod_END    (24)
#define SOC_PMCTRL_A57_CPUCLKPROFILE0_1_a57_apll_cfg_vld_START  (25)
#define SOC_PMCTRL_A57_CPUCLKPROFILE0_1_a57_apll_cfg_vld_END    (25)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPUCLKPROFILE1_UNION
 结构说明  : A57_CPUCLKPROFILE1 寄存器结构定义。地址偏移量:0x178，初值:0x000000A0，宽度:32
 寄存器说明: A57_CPU频率Profile寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0           : 2;  /* bit[0-1] : 保留 */
        unsigned int  a57_atclken_sel_prof : 2;  /* bit[2-3] : A57_ ATB接口时钟频率比选择参数 */
        unsigned int  a57_aclkenm_sel_prof : 3;  /* bit[4-6] : A57_ ACE master接口时钟频率比选择参数 */
        unsigned int  a57_atclken_l_prof   : 1;  /* bit[7-7] : A57_ trace时钟二级频率比选择
                                                               0:1:2 1:1:4 */
        unsigned int  reserved_1           : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_CPUCLKPROFILE1_UNION;
#endif
#define SOC_PMCTRL_A57_CPUCLKPROFILE1_a57_atclken_sel_prof_START  (2)
#define SOC_PMCTRL_A57_CPUCLKPROFILE1_a57_atclken_sel_prof_END    (3)
#define SOC_PMCTRL_A57_CPUCLKPROFILE1_a57_aclkenm_sel_prof_START  (4)
#define SOC_PMCTRL_A57_CPUCLKPROFILE1_a57_aclkenm_sel_prof_END    (6)
#define SOC_PMCTRL_A57_CPUCLKPROFILE1_a57_atclken_l_prof_START    (7)
#define SOC_PMCTRL_A57_CPUCLKPROFILE1_a57_atclken_l_prof_END      (7)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPUVOLMOD_UNION
 结构说明  : A57_CPUVOLMOD 寄存器结构定义。地址偏移量:0x17C，初值:0x00000000，宽度:32
 寄存器说明: A57_CPU DVFS时的调压模式寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_cpu_vol_mod         : 1;  /* bit[0-0] : A57_ DVFS时，是否需要调压。
                                                                  0：A57_ DVFS时，不需要调压；
                                                                  1：A57_ DVFS时，需要调压。 */
        unsigned int  a57_cpu_clk_off_vol_mod : 1;  /* bit[1-1] : A57_调压时，A57_时钟是否关闭。
                                                                  0：A57_调压时，A57_时钟保持打开；
                                                                  1：A57_调压时，A57_时钟要求关闭。 */
        unsigned int  reserved                : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_CPUVOLMOD_UNION;
#endif
#define SOC_PMCTRL_A57_CPUVOLMOD_a57_cpu_vol_mod_START          (0)
#define SOC_PMCTRL_A57_CPUVOLMOD_a57_cpu_vol_mod_END            (0)
#define SOC_PMCTRL_A57_CPUVOLMOD_a57_cpu_clk_off_vol_mod_START  (1)
#define SOC_PMCTRL_A57_CPUVOLMOD_a57_cpu_clk_off_vol_mod_END    (1)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPUVOLPROFILE_UNION
 结构说明  : A57_CPUVOLPROFILE 寄存器结构定义。地址偏移量:0x180，初值:0x00000000，宽度:32
 寄存器说明: A57_CPU电压Profile寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_cpu_vol_idx : 8;  /* bit[0-7] : A57_电压Profile参数。 */
        unsigned int  reserved        : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_CPUVOLPROFILE_UNION;
#endif
#define SOC_PMCTRL_A57_CPUVOLPROFILE_a57_cpu_vol_idx_START  (0)
#define SOC_PMCTRL_A57_CPUVOLPROFILE_a57_cpu_vol_idx_END    (7)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPUPHASEMOD_UNION
 结构说明  : A57_CPUPHASEMOD 寄存器结构定义。地址偏移量:0x188，初值:0x00000000，宽度:32
 寄存器说明: A57_CPU DVFS时的相位模式寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_cpu_phase_mod         : 1;  /* bit[0-0] : A57_ DVFS时，是否改变相位。
                                                                    0：A57_ DVFS时，不改变相位；
                                                                    1：A57_ DVFS时，改变相位。 */
        unsigned int  a57_cpu_clk_off_phase_mod : 1;  /* bit[1-1] : A57_ DVFS改变相位时是否关闭A57_时钟。
                                                                    0：A57_改变相位时，A57_时钟保持打开；
                                                                    1：A57_改变相位时，A57_时钟关闭。 */
        unsigned int  reserved                  : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_CPUPHASEMOD_UNION;
#endif
#define SOC_PMCTRL_A57_CPUPHASEMOD_a57_cpu_phase_mod_START          (0)
#define SOC_PMCTRL_A57_CPUPHASEMOD_a57_cpu_phase_mod_END            (0)
#define SOC_PMCTRL_A57_CPUPHASEMOD_a57_cpu_clk_off_phase_mod_START  (1)
#define SOC_PMCTRL_A57_CPUPHASEMOD_a57_cpu_clk_off_phase_mod_END    (1)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPUPHASEPROFILE_UNION
 结构说明  : A57_CPUPHASEPROFILE 寄存器结构定义。地址偏移量:0x18C，初值:0x00000000，宽度:32
 寄存器说明: A57_CPU相位Profile寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_cpu_phase_idx : 8;  /* bit[0-7] : A57_相位Profile参数。 */
        unsigned int  reserved          : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_CPUPHASEPROFILE_UNION;
#endif
#define SOC_PMCTRL_A57_CPUPHASEPROFILE_a57_cpu_phase_idx_START  (0)
#define SOC_PMCTRL_A57_CPUPHASEPROFILE_a57_cpu_phase_idx_END    (7)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPUVOLPHASESEL_UNION
 结构说明  : A57_CPUVOLPHASESEL 寄存器结构定义。地址偏移量:0x190，初值:0x00000000，宽度:32
 寄存器说明: A57_CPU电压/相位配置选择寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_cpu_vol_phase_sel : 1;  /* bit[0-0] : A57_电压/相位信号输出选择
                                                                0：DVFS时先调相位再调电压，配置profile寄存器。时不需要改变；
                                                                1：DVFS先调电压在调相位，配置profile寄存器。时需要改变（电压profile寄存器。控制相位，相位profile寄存器。控制电压）。 */
        unsigned int  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_CPUVOLPHASESEL_UNION;
#endif
#define SOC_PMCTRL_A57_CPUVOLPHASESEL_a57_cpu_vol_phase_sel_START  (0)
#define SOC_PMCTRL_A57_CPUVOLPHASESEL_a57_cpu_vol_phase_sel_END    (0)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_VOLUPSTEPTIME_UNION
 结构说明  : A57_VOLUPSTEPTIME 寄存器结构定义。地址偏移量:0x194，初值:0x00000000，宽度:32
 寄存器说明: A57_电压上升一档稳定步长时间寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_vol_up_step_time : 13; /* bit[0-12] : A57_ CPU电压上升稳定步长时间。 */
        unsigned int  reserved             : 19; /* bit[13-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_VOLUPSTEPTIME_UNION;
#endif
#define SOC_PMCTRL_A57_VOLUPSTEPTIME_a57_vol_up_step_time_START  (0)
#define SOC_PMCTRL_A57_VOLUPSTEPTIME_a57_vol_up_step_time_END    (12)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_VOLDNSTEPTIME_UNION
 结构说明  : A57_VOLDNSTEPTIME 寄存器结构定义。地址偏移量:0x198，初值:0x00000000，宽度:32
 寄存器说明: A57_电压下降一档稳定步长时间寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_vol_dn_step_time : 13; /* bit[0-12] : A57_ CPU电压下降稳定步长时间。 */
        unsigned int  reserved             : 19; /* bit[13-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_VOLDNSTEPTIME_UNION;
#endif
#define SOC_PMCTRL_A57_VOLDNSTEPTIME_a57_vol_dn_step_time_START  (0)
#define SOC_PMCTRL_A57_VOLDNSTEPTIME_a57_vol_dn_step_time_END    (12)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_PHASEUPTIME_UNION
 结构说明  : A57_PHASEUPTIME 寄存器结构定义。地址偏移量:0x19C，初值:0x00000000，宽度:32
 寄存器说明: A57_ DVFS时改变电压相位的上升稳定时间寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_dvfs_phase_up_time : 20; /* bit[0-19] : A57_ DVFS时，改变电压相位的上升稳定时间。 */
        unsigned int  reserved               : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_PHASEUPTIME_UNION;
#endif
#define SOC_PMCTRL_A57_PHASEUPTIME_a57_dvfs_phase_up_time_START  (0)
#define SOC_PMCTRL_A57_PHASEUPTIME_a57_dvfs_phase_up_time_END    (19)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_PHASEDNTIME_UNION
 结构说明  : A57_PHASEDNTIME 寄存器结构定义。地址偏移量:0x1A0，初值:0x00000000，宽度:32
 寄存器说明: A57_ DVFS时改变电压相位的下降稳定时间寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_dvfs_phase_dn_time : 20; /* bit[0-19] : A57_ DVFS时，改变电压相位的下降稳定时间。 */
        unsigned int  reserved               : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_PHASEDNTIME_UNION;
#endif
#define SOC_PMCTRL_A57_PHASEDNTIME_a57_dvfs_phase_dn_time_START  (0)
#define SOC_PMCTRL_A57_PHASEDNTIME_a57_dvfs_phase_dn_time_END    (19)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_PMUHOLDTIME_UNION
 结构说明  : A57_PMUHOLDTIME 寄存器结构定义。地址偏移量:0x1A4，初值:0x00000000，宽度:32
 寄存器说明: A57_电压稳定时间裕量寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_pmu_vol_hold_time : 20; /* bit[0-19] : A57_调压时，由于端口传输时间而增加的电压稳定时间 */
        unsigned int  reserved              : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_PMUHOLDTIME_UNION;
#endif
#define SOC_PMCTRL_A57_PMUHOLDTIME_a57_pmu_vol_hold_time_START  (0)
#define SOC_PMCTRL_A57_PMUHOLDTIME_a57_pmu_vol_hold_time_END    (19)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_PMUSEL_UNION
 结构说明  : A57_PMUSEL 寄存器结构定义。地址偏移量:0x1A8，初值:0x00000000，宽度:32
 寄存器说明: A57_PMU选择寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_pmu_sel : 1;  /* bit[0-0] : A57_输出PMU选择
                                                      0：A57_输出的信号给PMUSSI；
                                                      1：A57_输出的信号给PMUI2C。（只能静态配置） */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_PMUSEL_UNION;
#endif
#define SOC_PMCTRL_A57_PMUSEL_a57_pmu_sel_START  (0)
#define SOC_PMCTRL_A57_PMUSEL_a57_pmu_sel_END    (0)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPUAVSEN_UNION
 结构说明  : A57_CPUAVSEN 寄存器结构定义。地址偏移量:0x1B0，初值:0x00000000，宽度:32
 寄存器说明: A57_CPU AVS使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_cpu_avs_en        : 1;  /* bit[0-0] : A57_ AVS使能。
                                                                0：A57_ AVS功能关闭；
                                                                1：A57_ AVS功能开启。 */
        unsigned int  a57_cpu_avs_pwctrl_en : 1;  /* bit[1-1] : A57_ AVS调压使能。
                                                                0：A57_ AVS调压功能关闭；
                                                                1：A57_ AVS调压功能开启。 */
        unsigned int  reserved              : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_CPUAVSEN_UNION;
#endif
#define SOC_PMCTRL_A57_CPUAVSEN_a57_cpu_avs_en_START         (0)
#define SOC_PMCTRL_A57_CPUAVSEN_a57_cpu_avs_en_END           (0)
#define SOC_PMCTRL_A57_CPUAVSEN_a57_cpu_avs_pwctrl_en_START  (1)
#define SOC_PMCTRL_A57_CPUAVSEN_a57_cpu_avs_pwctrl_en_END    (1)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPUAVSPARAMOD_UNION
 结构说明  : A57_CPUAVSPARAMOD 寄存器结构定义。地址偏移量:0x1B4，初值:0x00000000，宽度:32
 寄存器说明: A57_CPU AVS参数模式寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_cpu_avspara_mod : 1;  /* bit[0-0] : A57_ AVS参数实时更新控制。
                                                              通常，A57_ AVS参数在A57_ DVFS运行之后更新；如果对这个寄存器。写1，AVS参数立即更新；如果对这个寄存器。写0，无效。 */
        unsigned int  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_CPUAVSPARAMOD_UNION;
#endif
#define SOC_PMCTRL_A57_CPUAVSPARAMOD_a57_cpu_avspara_mod_START  (0)
#define SOC_PMCTRL_A57_CPUAVSPARAMOD_a57_cpu_avspara_mod_END    (0)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPUAVSPARA0_UNION
 结构说明  : A57_CPUAVSPARA0 寄存器结构定义。地址偏移量:0x1B8，初值:0x00000000，宽度:32
 寄存器说明: A57_CPU AVS参数寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0             : 2;  /* bit[0-1]  : 保留 */
        unsigned int  a57_cpu_avs_opc_offset : 10; /* bit[2-11] : A57_ AVS原始性能码偏移。 */
        unsigned int  a57_cpu_avs_rcc        : 5;  /* bit[12-16]: A57_ AVS参考校准码。 */
        unsigned int  a57_cpu_avs_irgap      : 5;  /* bit[17-21]: A57_ AVS IRDrop裕量。 */
        unsigned int  a57_cpu_avs_opc_mod    : 2;  /* bit[22-23]: A57_ AVS中同一个HPM OPC值的多次采样如何处理。
                                                                  00：OPC取均值；
                                                                  01：OPC取最小值；
                                                                  10：OPC取最大值；
                                                                  11：保留。 */
        unsigned int  a57_cpu_avs_hpm_sel    : 4;  /* bit[24-27]: A57_ AVS中多个HPM的PC值如何处理。
                                                                  0000：取CPU0 HPM的PC值；
                                                                  0001：取CPU1 HPM的PC值；
                                                                  0010：取CPU2 HPM的PC值；
                                                                  0011：取CPU3 HPM的PC值；
                                                                  0100：取SCU0 HPM的PC值；
                                                                  0101：reserved；
                                                                  0110：reserved；
                                                                  0111：reserved；
                                                                  1000：reserved；
                                                                  1001：reserved；
                                                                  1010：取HPM中的最小值；
                                                                  其他：取HPM中的最大值； */
        unsigned int  a57_cpu_avs_opc_shift  : 3;  /* bit[28-30]: A57_ AVS原始性能码移位。 */
        unsigned int  reserved_1             : 1;  /* bit[31-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_CPUAVSPARA0_UNION;
#endif
#define SOC_PMCTRL_A57_CPUAVSPARA0_a57_cpu_avs_opc_offset_START  (2)
#define SOC_PMCTRL_A57_CPUAVSPARA0_a57_cpu_avs_opc_offset_END    (11)
#define SOC_PMCTRL_A57_CPUAVSPARA0_a57_cpu_avs_rcc_START         (12)
#define SOC_PMCTRL_A57_CPUAVSPARA0_a57_cpu_avs_rcc_END           (16)
#define SOC_PMCTRL_A57_CPUAVSPARA0_a57_cpu_avs_irgap_START       (17)
#define SOC_PMCTRL_A57_CPUAVSPARA0_a57_cpu_avs_irgap_END         (21)
#define SOC_PMCTRL_A57_CPUAVSPARA0_a57_cpu_avs_opc_mod_START     (22)
#define SOC_PMCTRL_A57_CPUAVSPARA0_a57_cpu_avs_opc_mod_END       (23)
#define SOC_PMCTRL_A57_CPUAVSPARA0_a57_cpu_avs_hpm_sel_START     (24)
#define SOC_PMCTRL_A57_CPUAVSPARA0_a57_cpu_avs_hpm_sel_END       (27)
#define SOC_PMCTRL_A57_CPUAVSPARA0_a57_cpu_avs_opc_shift_START   (28)
#define SOC_PMCTRL_A57_CPUAVSPARA0_a57_cpu_avs_opc_shift_END     (30)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPUAVSPARA1_UNION
 结构说明  : A57_CPUAVSPARA1 寄存器结构定义。地址偏移量:0x1BC，初值:0x00000000，宽度:32
 寄存器说明: A57_CPU AVS参数寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_cpu_avs_vol_up_gain1 : 4;  /* bit[0-3]  : A57_ AVS升压增益。 */
        unsigned int  a57_cpu_avs_vol_up_gain2 : 4;  /* bit[4-7]  : A57_ AVS升压增益。 */
        unsigned int  a57_cpu_avs_vol_up_gain3 : 4;  /* bit[8-11] : A57_ AVS升压增益。 */
        unsigned int  a57_cpu_avs_vol_up_gain4 : 4;  /* bit[12-15]: A57_ AVS升压增益。 */
        unsigned int  a57_cpu_avs_vol_up_gain5 : 4;  /* bit[16-19]: A57_ AVS升压增益。 */
        unsigned int  a57_cpu_avs_vol_up_gain6 : 4;  /* bit[20-23]: A57_ AVS升压增益。 */
        unsigned int  a57_cpu_avs_vol_up_gain7 : 4;  /* bit[24-27]: A57_ AVS升压增益。 */
        unsigned int  a57_cpu_avs_vol_up_gain8 : 4;  /* bit[28-31]: A57_ AVS升压增益。 */
    } reg;
} SOC_PMCTRL_A57_CPUAVSPARA1_UNION;
#endif
#define SOC_PMCTRL_A57_CPUAVSPARA1_a57_cpu_avs_vol_up_gain1_START  (0)
#define SOC_PMCTRL_A57_CPUAVSPARA1_a57_cpu_avs_vol_up_gain1_END    (3)
#define SOC_PMCTRL_A57_CPUAVSPARA1_a57_cpu_avs_vol_up_gain2_START  (4)
#define SOC_PMCTRL_A57_CPUAVSPARA1_a57_cpu_avs_vol_up_gain2_END    (7)
#define SOC_PMCTRL_A57_CPUAVSPARA1_a57_cpu_avs_vol_up_gain3_START  (8)
#define SOC_PMCTRL_A57_CPUAVSPARA1_a57_cpu_avs_vol_up_gain3_END    (11)
#define SOC_PMCTRL_A57_CPUAVSPARA1_a57_cpu_avs_vol_up_gain4_START  (12)
#define SOC_PMCTRL_A57_CPUAVSPARA1_a57_cpu_avs_vol_up_gain4_END    (15)
#define SOC_PMCTRL_A57_CPUAVSPARA1_a57_cpu_avs_vol_up_gain5_START  (16)
#define SOC_PMCTRL_A57_CPUAVSPARA1_a57_cpu_avs_vol_up_gain5_END    (19)
#define SOC_PMCTRL_A57_CPUAVSPARA1_a57_cpu_avs_vol_up_gain6_START  (20)
#define SOC_PMCTRL_A57_CPUAVSPARA1_a57_cpu_avs_vol_up_gain6_END    (23)
#define SOC_PMCTRL_A57_CPUAVSPARA1_a57_cpu_avs_vol_up_gain7_START  (24)
#define SOC_PMCTRL_A57_CPUAVSPARA1_a57_cpu_avs_vol_up_gain7_END    (27)
#define SOC_PMCTRL_A57_CPUAVSPARA1_a57_cpu_avs_vol_up_gain8_START  (28)
#define SOC_PMCTRL_A57_CPUAVSPARA1_a57_cpu_avs_vol_up_gain8_END    (31)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPUAVSPARA2_UNION
 结构说明  : A57_CPUAVSPARA2 寄存器结构定义。地址偏移量:0x1C0，初值:0x00000000，宽度:32
 寄存器说明: A57_CPU AVS参数寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_cpu_avs_vol_up_gain9  : 4;  /* bit[0-3]  : A57_ AVS升压增益。 */
        unsigned int  a57_cpu_avs_vol_up_gain10 : 4;  /* bit[4-7]  : A57_ AVS升压增益。 */
        unsigned int  a57_cpu_avs_vol_up_gain11 : 4;  /* bit[8-11] : A57_ AVS升压增益。 */
        unsigned int  a57_cpu_avs_vol_up_gain12 : 4;  /* bit[12-15]: A57_ AVS升压增益。 */
        unsigned int  a57_cpu_avs_vol_up_gain13 : 4;  /* bit[16-19]: A57_ AVS升压增益。 */
        unsigned int  a57_cpu_avs_vol_up_gain14 : 4;  /* bit[20-23]: A57_ AVS升压增益。 */
        unsigned int  a57_cpu_avs_vol_up_gain15 : 7;  /* bit[24-30]: A57_ AVS升压增益。 */
        unsigned int  reserved                  : 1;  /* bit[31-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_CPUAVSPARA2_UNION;
#endif
#define SOC_PMCTRL_A57_CPUAVSPARA2_a57_cpu_avs_vol_up_gain9_START   (0)
#define SOC_PMCTRL_A57_CPUAVSPARA2_a57_cpu_avs_vol_up_gain9_END     (3)
#define SOC_PMCTRL_A57_CPUAVSPARA2_a57_cpu_avs_vol_up_gain10_START  (4)
#define SOC_PMCTRL_A57_CPUAVSPARA2_a57_cpu_avs_vol_up_gain10_END    (7)
#define SOC_PMCTRL_A57_CPUAVSPARA2_a57_cpu_avs_vol_up_gain11_START  (8)
#define SOC_PMCTRL_A57_CPUAVSPARA2_a57_cpu_avs_vol_up_gain11_END    (11)
#define SOC_PMCTRL_A57_CPUAVSPARA2_a57_cpu_avs_vol_up_gain12_START  (12)
#define SOC_PMCTRL_A57_CPUAVSPARA2_a57_cpu_avs_vol_up_gain12_END    (15)
#define SOC_PMCTRL_A57_CPUAVSPARA2_a57_cpu_avs_vol_up_gain13_START  (16)
#define SOC_PMCTRL_A57_CPUAVSPARA2_a57_cpu_avs_vol_up_gain13_END    (19)
#define SOC_PMCTRL_A57_CPUAVSPARA2_a57_cpu_avs_vol_up_gain14_START  (20)
#define SOC_PMCTRL_A57_CPUAVSPARA2_a57_cpu_avs_vol_up_gain14_END    (23)
#define SOC_PMCTRL_A57_CPUAVSPARA2_a57_cpu_avs_vol_up_gain15_START  (24)
#define SOC_PMCTRL_A57_CPUAVSPARA2_a57_cpu_avs_vol_up_gain15_END    (30)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPUAVSPARA3_UNION
 结构说明  : A57_CPUAVSPARA3 寄存器结构定义。地址偏移量:0x1C4，初值:0x00000000，宽度:32
 寄存器说明: A57_CPU AVS参数寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_cpu_avs_vol_dn_gain1 : 4;  /* bit[0-3]  : A57_ AVS降压增益。 */
        unsigned int  a57_cpu_avs_vol_dn_gain2 : 4;  /* bit[4-7]  : A57_ AVS降压增益。 */
        unsigned int  a57_cpu_avs_vol_dn_gain3 : 4;  /* bit[8-11] : A57_ AVS降压增益。 */
        unsigned int  a57_cpu_avs_vol_dn_gain4 : 4;  /* bit[12-15]: A57_ AVS降压增益。 */
        unsigned int  a57_cpu_avs_vol_dn_gain5 : 4;  /* bit[16-19]: A57_ AVS降压增益。 */
        unsigned int  a57_cpu_avs_vol_dn_gain6 : 4;  /* bit[20-23]: A57_ AVS降压增益。 */
        unsigned int  a57_cpu_avs_vol_dn_gain7 : 4;  /* bit[24-27]: A57_ AVS降压增益。 */
        unsigned int  a57_cpu_avs_vol_dn_gain8 : 4;  /* bit[28-31]: A57_ AVS降压增益。 */
    } reg;
} SOC_PMCTRL_A57_CPUAVSPARA3_UNION;
#endif
#define SOC_PMCTRL_A57_CPUAVSPARA3_a57_cpu_avs_vol_dn_gain1_START  (0)
#define SOC_PMCTRL_A57_CPUAVSPARA3_a57_cpu_avs_vol_dn_gain1_END    (3)
#define SOC_PMCTRL_A57_CPUAVSPARA3_a57_cpu_avs_vol_dn_gain2_START  (4)
#define SOC_PMCTRL_A57_CPUAVSPARA3_a57_cpu_avs_vol_dn_gain2_END    (7)
#define SOC_PMCTRL_A57_CPUAVSPARA3_a57_cpu_avs_vol_dn_gain3_START  (8)
#define SOC_PMCTRL_A57_CPUAVSPARA3_a57_cpu_avs_vol_dn_gain3_END    (11)
#define SOC_PMCTRL_A57_CPUAVSPARA3_a57_cpu_avs_vol_dn_gain4_START  (12)
#define SOC_PMCTRL_A57_CPUAVSPARA3_a57_cpu_avs_vol_dn_gain4_END    (15)
#define SOC_PMCTRL_A57_CPUAVSPARA3_a57_cpu_avs_vol_dn_gain5_START  (16)
#define SOC_PMCTRL_A57_CPUAVSPARA3_a57_cpu_avs_vol_dn_gain5_END    (19)
#define SOC_PMCTRL_A57_CPUAVSPARA3_a57_cpu_avs_vol_dn_gain6_START  (20)
#define SOC_PMCTRL_A57_CPUAVSPARA3_a57_cpu_avs_vol_dn_gain6_END    (23)
#define SOC_PMCTRL_A57_CPUAVSPARA3_a57_cpu_avs_vol_dn_gain7_START  (24)
#define SOC_PMCTRL_A57_CPUAVSPARA3_a57_cpu_avs_vol_dn_gain7_END    (27)
#define SOC_PMCTRL_A57_CPUAVSPARA3_a57_cpu_avs_vol_dn_gain8_START  (28)
#define SOC_PMCTRL_A57_CPUAVSPARA3_a57_cpu_avs_vol_dn_gain8_END    (31)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPUAVSPARA4_UNION
 结构说明  : A57_CPUAVSPARA4 寄存器结构定义。地址偏移量:0x1C8，初值:0x00000000，宽度:32
 寄存器说明: A57_CPU AVS参数寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_cpu_avs_vol_dn_gain9  : 4;  /* bit[0-3]  : A57_ AVS降压增益。 */
        unsigned int  a57_cpu_avs_vol_dn_gain10 : 4;  /* bit[4-7]  : A57_ AVS降压增益。 */
        unsigned int  a57_cpu_avs_vol_dn_gain11 : 4;  /* bit[8-11] : A57_ AVS降压增益。 */
        unsigned int  a57_cpu_avs_vol_dn_gain12 : 4;  /* bit[12-15]: A57_ AVS降压增益。 */
        unsigned int  a57_cpu_avs_vol_dn_gain13 : 4;  /* bit[16-19]: A57_ AVS降压增益。 */
        unsigned int  a57_cpu_avs_vol_dn_gain14 : 4;  /* bit[20-23]: A57_ AVS降压增益。 */
        unsigned int  a57_cpu_avs_vol_dn_gain15 : 7;  /* bit[24-30]: A57_ AVS降压增益。 */
        unsigned int  reserved                  : 1;  /* bit[31-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_CPUAVSPARA4_UNION;
#endif
#define SOC_PMCTRL_A57_CPUAVSPARA4_a57_cpu_avs_vol_dn_gain9_START   (0)
#define SOC_PMCTRL_A57_CPUAVSPARA4_a57_cpu_avs_vol_dn_gain9_END     (3)
#define SOC_PMCTRL_A57_CPUAVSPARA4_a57_cpu_avs_vol_dn_gain10_START  (4)
#define SOC_PMCTRL_A57_CPUAVSPARA4_a57_cpu_avs_vol_dn_gain10_END    (7)
#define SOC_PMCTRL_A57_CPUAVSPARA4_a57_cpu_avs_vol_dn_gain11_START  (8)
#define SOC_PMCTRL_A57_CPUAVSPARA4_a57_cpu_avs_vol_dn_gain11_END    (11)
#define SOC_PMCTRL_A57_CPUAVSPARA4_a57_cpu_avs_vol_dn_gain12_START  (12)
#define SOC_PMCTRL_A57_CPUAVSPARA4_a57_cpu_avs_vol_dn_gain12_END    (15)
#define SOC_PMCTRL_A57_CPUAVSPARA4_a57_cpu_avs_vol_dn_gain13_START  (16)
#define SOC_PMCTRL_A57_CPUAVSPARA4_a57_cpu_avs_vol_dn_gain13_END    (19)
#define SOC_PMCTRL_A57_CPUAVSPARA4_a57_cpu_avs_vol_dn_gain14_START  (20)
#define SOC_PMCTRL_A57_CPUAVSPARA4_a57_cpu_avs_vol_dn_gain14_END    (23)
#define SOC_PMCTRL_A57_CPUAVSPARA4_a57_cpu_avs_vol_dn_gain15_START  (24)
#define SOC_PMCTRL_A57_CPUAVSPARA4_a57_cpu_avs_vol_dn_gain15_END    (30)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPUAVSPARA5_UNION
 结构说明  : A57_CPUAVSPARA5 寄存器结构定义。地址偏移量:0x1CC，初值:0x00000000，宽度:32
 寄存器说明: A57_CPU AVS参数寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_cpu_avs_max_vol : 7;  /* bit[0-6]  : A57_ AVS最大电压限制。 */
        unsigned int  a57_cpu_avs_min_vol : 7;  /* bit[7-13] : A57_ AVS最小电压限制。 */
        unsigned int  reserved            : 18; /* bit[14-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_CPUAVSPARA5_UNION;
#endif
#define SOC_PMCTRL_A57_CPUAVSPARA5_a57_cpu_avs_max_vol_START  (0)
#define SOC_PMCTRL_A57_CPUAVSPARA5_a57_cpu_avs_max_vol_END    (6)
#define SOC_PMCTRL_A57_CPUAVSPARA5_a57_cpu_avs_min_vol_START  (7)
#define SOC_PMCTRL_A57_CPUAVSPARA5_a57_cpu_avs_min_vol_END    (13)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPUAVSPARA6_UNION
 结构说明  : A57_CPUAVSPARA6 寄存器结构定义。地址偏移量:0x1D0，初值:0x00000000，宽度:32
 寄存器说明: A57_CPU AVS使能寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_cpu_avs_sample_num : 22; /* bit[0-21] : A57_ AVS性能码采样次数。配置值必须是2的N次方。 */
        unsigned int  reserved               : 10; /* bit[22-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_CPUAVSPARA6_UNION;
#endif
#define SOC_PMCTRL_A57_CPUAVSPARA6_a57_cpu_avs_sample_num_START  (0)
#define SOC_PMCTRL_A57_CPUAVSPARA6_a57_cpu_avs_sample_num_END    (21)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPUHPMTYP_UNION
 结构说明  : A57_CPUHPMTYP 寄存器结构定义。地址偏移量:0x1D4，初值:0x00000000，宽度:32
 寄存器说明: A57_CPU01 HPM类型选择寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_cpu_hpm_type  : 1;  /* bit[0-0]  : AVS选择使用CPU HPM类型。
                                                             0：AVS选择使用标准HPM；
                                                             1：AVS选择使用X型HPM。 */
        unsigned int  a57_cpu0_hpm_mask : 1;  /* bit[1-1]  : AVS控制是否屏蔽CPU0 HPM。
                                                             0：不屏蔽；
                                                             1：屏蔽。 */
        unsigned int  a57_cpu1_hpm_mask : 1;  /* bit[2-2]  : AVS控制是否屏蔽CPU1 HPM。
                                                             0：不屏蔽；
                                                             1：屏蔽。 */
        unsigned int  a57_cpu2_hpm_mask : 1;  /* bit[3-3]  : AVS控制是否屏蔽CPU2 HPM。
                                                             0：不屏蔽；
                                                             1：屏蔽。 */
        unsigned int  a57_cpu3_hpm_mask : 1;  /* bit[4-4]  : AVS控制是否屏蔽CPU3 HPM。
                                                             0：不屏蔽；
                                                             1：屏蔽。 */
        unsigned int  a57_scu_hpm_mask  : 1;  /* bit[5-5]  : AVS控制是否屏蔽SCU HPM。
                                                             0：不屏蔽；
                                                             1：屏蔽。 */
        unsigned int  reserved          : 10; /* bit[6-15] : 保留 */
        unsigned int  biten             : 16; /* bit[16-31]: 每个比特位的使能位：
                                                             只有当biten对应的比特位为1'b1，相应的比特位才起作用。biten[0]就是bit 0的使能位。写1有效。 */
    } reg;
} SOC_PMCTRL_A57_CPUHPMTYP_UNION;
#endif
#define SOC_PMCTRL_A57_CPUHPMTYP_a57_cpu_hpm_type_START   (0)
#define SOC_PMCTRL_A57_CPUHPMTYP_a57_cpu_hpm_type_END     (0)
#define SOC_PMCTRL_A57_CPUHPMTYP_a57_cpu0_hpm_mask_START  (1)
#define SOC_PMCTRL_A57_CPUHPMTYP_a57_cpu0_hpm_mask_END    (1)
#define SOC_PMCTRL_A57_CPUHPMTYP_a57_cpu1_hpm_mask_START  (2)
#define SOC_PMCTRL_A57_CPUHPMTYP_a57_cpu1_hpm_mask_END    (2)
#define SOC_PMCTRL_A57_CPUHPMTYP_a57_cpu2_hpm_mask_START  (3)
#define SOC_PMCTRL_A57_CPUHPMTYP_a57_cpu2_hpm_mask_END    (3)
#define SOC_PMCTRL_A57_CPUHPMTYP_a57_cpu3_hpm_mask_START  (4)
#define SOC_PMCTRL_A57_CPUHPMTYP_a57_cpu3_hpm_mask_END    (4)
#define SOC_PMCTRL_A57_CPUHPMTYP_a57_scu_hpm_mask_START   (5)
#define SOC_PMCTRL_A57_CPUHPMTYP_a57_scu_hpm_mask_END     (5)
#define SOC_PMCTRL_A57_CPUHPMTYP_biten_START              (16)
#define SOC_PMCTRL_A57_CPUHPMTYP_biten_END                (31)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPU01HPMEN_UNION
 结构说明  : A57_CPU01HPMEN 寄存器结构定义。地址偏移量:0x1D8，初值:0x00000000，宽度:32
 寄存器说明: A57_CPU01 HPM使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_cpu0_hpm_en : 1;  /* bit[0-0] : CPU0 HPM使能。
                                                          HPM使能控制除了软件可以置位或清除，在AVS流程中也会被AVS主控逻辑自动置位或清除。 */
        unsigned int  a57_cpu1_hpm_en : 1;  /* bit[1-1] : CPU1 HPM使能。
                                                          HPM使能控制除了软件可以置位或清除，在AVS流程中也会被AVS主控逻辑自动置位或清除。 */
        unsigned int  a57_scu_hpm_en  : 1;  /* bit[2-2] : SCU HPM使能。
                                                          HPM使能控制除了软件可以置位或清除，在AVS流程中也会被AVS主控逻辑自动置位或清除。 */
        unsigned int  reserved        : 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_CPU01HPMEN_UNION;
#endif
#define SOC_PMCTRL_A57_CPU01HPMEN_a57_cpu0_hpm_en_START  (0)
#define SOC_PMCTRL_A57_CPU01HPMEN_a57_cpu0_hpm_en_END    (0)
#define SOC_PMCTRL_A57_CPU01HPMEN_a57_cpu1_hpm_en_START  (1)
#define SOC_PMCTRL_A57_CPU01HPMEN_a57_cpu1_hpm_en_END    (1)
#define SOC_PMCTRL_A57_CPU01HPMEN_a57_scu_hpm_en_START   (2)
#define SOC_PMCTRL_A57_CPU01HPMEN_a57_scu_hpm_en_END     (2)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPU01HPMXEN_UNION
 结构说明  : A57_CPU01HPMXEN 寄存器结构定义。地址偏移量:0x1DC，初值:0x00000000，宽度:32
 寄存器说明: A57_CPU01 HPMX使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_cpu0_hpmx_en : 1;  /* bit[0-0] : CPU0 HPMX使能。
                                                           HPMX使能控制除了软件可以置位或清除，在AVS流程中也会被AVS主控逻辑自动置位或清除。 */
        unsigned int  a57_cpu1_hpmx_en : 1;  /* bit[1-1] : CPU1 HPMX使能。
                                                           HPMX使能控制除了软件可以置位或清除，在AVS流程中也会被AVS主控逻辑自动置位或清除。 */
        unsigned int  a57_scu_hpmx_en  : 1;  /* bit[2-2] : SCU HPMX使能。
                                                           HPMX使能控制除了软件可以置位或清除，在AVS流程中也会被AVS主控逻辑自动置位或清除。 */
        unsigned int  reserved         : 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_CPU01HPMXEN_UNION;
#endif
#define SOC_PMCTRL_A57_CPU01HPMXEN_a57_cpu0_hpmx_en_START  (0)
#define SOC_PMCTRL_A57_CPU01HPMXEN_a57_cpu0_hpmx_en_END    (0)
#define SOC_PMCTRL_A57_CPU01HPMXEN_a57_cpu1_hpmx_en_START  (1)
#define SOC_PMCTRL_A57_CPU01HPMXEN_a57_cpu1_hpmx_en_END    (1)
#define SOC_PMCTRL_A57_CPU01HPMXEN_a57_scu_hpmx_en_START   (2)
#define SOC_PMCTRL_A57_CPU01HPMXEN_a57_scu_hpmx_en_END     (2)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPU01HPMOPCVALID_UNION
 结构说明  : A57_CPU01HPMOPCVALID 寄存器结构定义。地址偏移量:0x1E0，初值:0x00000000，宽度:32
 寄存器说明: A57_CPU01 HPM OPC有效寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_cpu0_hpm_opc_vld  : 1;  /* bit[0-0] : CPU0 HPM原始性能码有效的状态指示。 */
        unsigned int  a57_cpu1_hpm_opc_vld  : 1;  /* bit[1-1] : CPU1 HPM原始性能码有效的状态指示。 */
        unsigned int  a57_scu_hpm_opc_vld   : 1;  /* bit[2-2] : SCU HPM原始性能码有效的状态指示。 */
        unsigned int  a57_cpu0_hpmx_opc_vld : 1;  /* bit[3-3] : CPU0 HPMX原始性能码有效的状态指示。 */
        unsigned int  a57_cpu1_hpmx_opc_vld : 1;  /* bit[4-4] : CPU1 HPMX原始性能码有效的状态指示。 */
        unsigned int  a57_scu_hpmx_opc_vld  : 1;  /* bit[5-5] : SCU HPMX原始性能码有效的状态指示。 */
        unsigned int  reserved              : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_CPU01HPMOPCVALID_UNION;
#endif
#define SOC_PMCTRL_A57_CPU01HPMOPCVALID_a57_cpu0_hpm_opc_vld_START   (0)
#define SOC_PMCTRL_A57_CPU01HPMOPCVALID_a57_cpu0_hpm_opc_vld_END     (0)
#define SOC_PMCTRL_A57_CPU01HPMOPCVALID_a57_cpu1_hpm_opc_vld_START   (1)
#define SOC_PMCTRL_A57_CPU01HPMOPCVALID_a57_cpu1_hpm_opc_vld_END     (1)
#define SOC_PMCTRL_A57_CPU01HPMOPCVALID_a57_scu_hpm_opc_vld_START    (2)
#define SOC_PMCTRL_A57_CPU01HPMOPCVALID_a57_scu_hpm_opc_vld_END      (2)
#define SOC_PMCTRL_A57_CPU01HPMOPCVALID_a57_cpu0_hpmx_opc_vld_START  (3)
#define SOC_PMCTRL_A57_CPU01HPMOPCVALID_a57_cpu0_hpmx_opc_vld_END    (3)
#define SOC_PMCTRL_A57_CPU01HPMOPCVALID_a57_cpu1_hpmx_opc_vld_START  (4)
#define SOC_PMCTRL_A57_CPU01HPMOPCVALID_a57_cpu1_hpmx_opc_vld_END    (4)
#define SOC_PMCTRL_A57_CPU01HPMOPCVALID_a57_scu_hpmx_opc_vld_START   (5)
#define SOC_PMCTRL_A57_CPU01HPMOPCVALID_a57_scu_hpmx_opc_vld_END     (5)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPU01HPMOPC_UNION
 结构说明  : A57_CPU01HPMOPC 寄存器结构定义。地址偏移量:0x1E4，初值:0x00000000，宽度:32
 寄存器说明: A57_CPU01 HPM OPC寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_cpu0_hpm_opc : 10; /* bit[0-9]  : CPU0 HPM原始性能码。 */
        unsigned int  a57_cpu1_hpm_opc : 10; /* bit[10-19]: CPU1 HPM原始性能码。 */
        unsigned int  a57_scu_hpm_opc  : 10; /* bit[20-29]: SCU HPM原始性能码。 */
        unsigned int  reserved         : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_CPU01HPMOPC_UNION;
#endif
#define SOC_PMCTRL_A57_CPU01HPMOPC_a57_cpu0_hpm_opc_START  (0)
#define SOC_PMCTRL_A57_CPU01HPMOPC_a57_cpu0_hpm_opc_END    (9)
#define SOC_PMCTRL_A57_CPU01HPMOPC_a57_cpu1_hpm_opc_START  (10)
#define SOC_PMCTRL_A57_CPU01HPMOPC_a57_cpu1_hpm_opc_END    (19)
#define SOC_PMCTRL_A57_CPU01HPMOPC_a57_scu_hpm_opc_START   (20)
#define SOC_PMCTRL_A57_CPU01HPMOPC_a57_scu_hpm_opc_END     (29)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPU01HPMXOPC_UNION
 结构说明  : A57_CPU01HPMXOPC 寄存器结构定义。地址偏移量:0x1E8，初值:0x00000000，宽度:32
 寄存器说明: A57_CPU01 HPMX OPC寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_cpu0_hpmx_opc : 10; /* bit[0-9]  : CPU0 HPMX原始性能码。 */
        unsigned int  a57_cpu1_hpmx_opc : 10; /* bit[10-19]: CPU1 HPMX原始性能码。 */
        unsigned int  a57_scu_hpmx_opc  : 10; /* bit[20-29]: SCU HPMX原始性能码。 */
        unsigned int  reserved          : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_CPU01HPMXOPC_UNION;
#endif
#define SOC_PMCTRL_A57_CPU01HPMXOPC_a57_cpu0_hpmx_opc_START  (0)
#define SOC_PMCTRL_A57_CPU01HPMXOPC_a57_cpu0_hpmx_opc_END    (9)
#define SOC_PMCTRL_A57_CPU01HPMXOPC_a57_cpu1_hpmx_opc_START  (10)
#define SOC_PMCTRL_A57_CPU01HPMXOPC_a57_cpu1_hpmx_opc_END    (19)
#define SOC_PMCTRL_A57_CPU01HPMXOPC_a57_scu_hpmx_opc_START   (20)
#define SOC_PMCTRL_A57_CPU01HPMXOPC_a57_scu_hpmx_opc_END     (29)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPU01HPMPC_UNION
 结构说明  : A57_CPU01HPMPC 寄存器结构定义。地址偏移量:0x1EC，初值:0x00000000，宽度:32
 寄存器说明: A57_CPU HPM PC寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_cpu0_hpm_pc_avs : 10; /* bit[0-9]  : CPU0 HPM性能码。 */
        unsigned int  a57_cpu1_hpm_pc_avs : 10; /* bit[10-19]: CPU1 HPM性能码。 */
        unsigned int  a57_scu_hpm_pc_avs  : 10; /* bit[20-29]: SCU HPM性能码。 */
        unsigned int  reserved            : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_CPU01HPMPC_UNION;
#endif
#define SOC_PMCTRL_A57_CPU01HPMPC_a57_cpu0_hpm_pc_avs_START  (0)
#define SOC_PMCTRL_A57_CPU01HPMPC_a57_cpu0_hpm_pc_avs_END    (9)
#define SOC_PMCTRL_A57_CPU01HPMPC_a57_cpu1_hpm_pc_avs_START  (10)
#define SOC_PMCTRL_A57_CPU01HPMPC_a57_cpu1_hpm_pc_avs_END    (19)
#define SOC_PMCTRL_A57_CPU01HPMPC_a57_scu_hpm_pc_avs_START   (20)
#define SOC_PMCTRL_A57_CPU01HPMPC_a57_scu_hpm_pc_avs_END     (29)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPU23HPMEN_UNION
 结构说明  : A57_CPU23HPMEN 寄存器结构定义。地址偏移量:0x1F4，初值:0x00000000，宽度:32
 寄存器说明: A57_CPU23 HPM使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_cpu2_hpm_en : 1;  /* bit[0-0] : CPU2 HPM使能。
                                                          HPM使能控制除了软件可以置位或清除，在AVS流程中也会被AVS主控逻辑自动置位或清除。 */
        unsigned int  a57_cpu3_hpm_en : 1;  /* bit[1-1] : CPU3 HPM使能。
                                                          HPM使能控制除了软件可以置位或清除，在AVS流程中也会被AVS主控逻辑自动置位或清除。 */
        unsigned int  reserved        : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_CPU23HPMEN_UNION;
#endif
#define SOC_PMCTRL_A57_CPU23HPMEN_a57_cpu2_hpm_en_START  (0)
#define SOC_PMCTRL_A57_CPU23HPMEN_a57_cpu2_hpm_en_END    (0)
#define SOC_PMCTRL_A57_CPU23HPMEN_a57_cpu3_hpm_en_START  (1)
#define SOC_PMCTRL_A57_CPU23HPMEN_a57_cpu3_hpm_en_END    (1)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPU23HPMXEN_UNION
 结构说明  : A57_CPU23HPMXEN 寄存器结构定义。地址偏移量:0x1F8，初值:0x00000000，宽度:32
 寄存器说明: A57_CPU23 HPMX使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_cpu2_hpmx_en : 1;  /* bit[0-0] : CPU2 HPMX使能。
                                                           HPMX使能控制除了软件可以置位或清除，在AVS流程中也会被AVS主控逻辑自动置位或清除。 */
        unsigned int  a57_cpu3_hpmx_en : 1;  /* bit[1-1] : CPU3 HPMX使能。
                                                           HPMX使能控制除了软件可以置位或清除，在AVS流程中也会被AVS主控逻辑自动置位或清除。 */
        unsigned int  reserved         : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_CPU23HPMXEN_UNION;
#endif
#define SOC_PMCTRL_A57_CPU23HPMXEN_a57_cpu2_hpmx_en_START  (0)
#define SOC_PMCTRL_A57_CPU23HPMXEN_a57_cpu2_hpmx_en_END    (0)
#define SOC_PMCTRL_A57_CPU23HPMXEN_a57_cpu3_hpmx_en_START  (1)
#define SOC_PMCTRL_A57_CPU23HPMXEN_a57_cpu3_hpmx_en_END    (1)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPU23HPMOPCVALID_UNION
 结构说明  : A57_CPU23HPMOPCVALID 寄存器结构定义。地址偏移量:0x1FC，初值:0x00000000，宽度:32
 寄存器说明: A57_CPU23 HPM OPC有效寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_cpu2_hpm_opc_vld  : 1;  /* bit[0-0] : CPU2 HPM原始性能码有效的状态指示。 */
        unsigned int  a57_cpu3_hpm_opc_vld  : 1;  /* bit[1-1] : CPU3 HPM原始性能码有效的状态指示。 */
        unsigned int  a57_cpu2_hpmx_opc_vld : 1;  /* bit[2-2] : CPU2 HPMX原始性能码有效的状态指示。 */
        unsigned int  a57_cpu3_hpmx_opc_vld : 1;  /* bit[3-3] : CPU3 HPMX原始性能码有效的状态指示。 */
        unsigned int  reserved              : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_CPU23HPMOPCVALID_UNION;
#endif
#define SOC_PMCTRL_A57_CPU23HPMOPCVALID_a57_cpu2_hpm_opc_vld_START   (0)
#define SOC_PMCTRL_A57_CPU23HPMOPCVALID_a57_cpu2_hpm_opc_vld_END     (0)
#define SOC_PMCTRL_A57_CPU23HPMOPCVALID_a57_cpu3_hpm_opc_vld_START   (1)
#define SOC_PMCTRL_A57_CPU23HPMOPCVALID_a57_cpu3_hpm_opc_vld_END     (1)
#define SOC_PMCTRL_A57_CPU23HPMOPCVALID_a57_cpu2_hpmx_opc_vld_START  (2)
#define SOC_PMCTRL_A57_CPU23HPMOPCVALID_a57_cpu2_hpmx_opc_vld_END    (2)
#define SOC_PMCTRL_A57_CPU23HPMOPCVALID_a57_cpu3_hpmx_opc_vld_START  (3)
#define SOC_PMCTRL_A57_CPU23HPMOPCVALID_a57_cpu3_hpmx_opc_vld_END    (3)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPU23HPMOPC_UNION
 结构说明  : A57_CPU23HPMOPC 寄存器结构定义。地址偏移量:0x200，初值:0x00000000，宽度:32
 寄存器说明: A57_CPU23 HPM OPC寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_cpu2_hpm_opc : 10; /* bit[0-9]  : CPU2 HPM原始性能码。 */
        unsigned int  a57_cpu3_hpm_opc : 10; /* bit[10-19]: CPU3 HPM原始性能码。 */
        unsigned int  reserved         : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_CPU23HPMOPC_UNION;
#endif
#define SOC_PMCTRL_A57_CPU23HPMOPC_a57_cpu2_hpm_opc_START  (0)
#define SOC_PMCTRL_A57_CPU23HPMOPC_a57_cpu2_hpm_opc_END    (9)
#define SOC_PMCTRL_A57_CPU23HPMOPC_a57_cpu3_hpm_opc_START  (10)
#define SOC_PMCTRL_A57_CPU23HPMOPC_a57_cpu3_hpm_opc_END    (19)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPU23HPMXOPC_UNION
 结构说明  : A57_CPU23HPMXOPC 寄存器结构定义。地址偏移量:0x204，初值:0x00000000，宽度:32
 寄存器说明: A57_CPU23 HPMX OPC寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_cpu2_hpmx_opc : 10; /* bit[0-9]  : CPU2 HPMX原始性能码。 */
        unsigned int  a57_cpu3_hpmx_opc : 10; /* bit[10-19]: CPU3 HPMX原始性能码。 */
        unsigned int  reserved          : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_CPU23HPMXOPC_UNION;
#endif
#define SOC_PMCTRL_A57_CPU23HPMXOPC_a57_cpu2_hpmx_opc_START  (0)
#define SOC_PMCTRL_A57_CPU23HPMXOPC_a57_cpu2_hpmx_opc_END    (9)
#define SOC_PMCTRL_A57_CPU23HPMXOPC_a57_cpu3_hpmx_opc_START  (10)
#define SOC_PMCTRL_A57_CPU23HPMXOPC_a57_cpu3_hpmx_opc_END    (19)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPU23HPMPC_UNION
 结构说明  : A57_CPU23HPMPC 寄存器结构定义。地址偏移量:0x208，初值:0x00000000，宽度:32
 寄存器说明: A57_CPU HPM PC寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_cpu2_hpm_pc_avs : 10; /* bit[0-9]  : CPU2 HPM性能码。 */
        unsigned int  a57_cpu3_hpm_pc_avs : 10; /* bit[10-19]: CPU3 HPM性能码。 */
        unsigned int  reserved            : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_CPU23HPMPC_UNION;
#endif
#define SOC_PMCTRL_A57_CPU23HPMPC_a57_cpu2_hpm_pc_avs_START  (0)
#define SOC_PMCTRL_A57_CPU23HPMPC_a57_cpu2_hpm_pc_avs_END    (9)
#define SOC_PMCTRL_A57_CPU23HPMPC_a57_cpu3_hpm_pc_avs_START  (10)
#define SOC_PMCTRL_A57_CPU23HPMPC_a57_cpu3_hpm_pc_avs_END    (19)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPUHPMCLKDIV_UNION
 结构说明  : A57_CPUHPMCLKDIV 寄存器结构定义。地址偏移量:0x210，初值:0x00000001，宽度:32
 寄存器说明: A57_CPU HPM时钟分频寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_cpu_avs_hpm_div : 6;  /* bit[0-5] : A57 HPM时钟分频器。 */
        unsigned int  reserved            : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_CPUHPMCLKDIV_UNION;
#endif
#define SOC_PMCTRL_A57_CPUHPMCLKDIV_a57_cpu_avs_hpm_div_START  (0)
#define SOC_PMCTRL_A57_CPUHPMCLKDIV_a57_cpu_avs_hpm_div_END    (5)


/*****************************************************************************
 结构名    : SOC_PMCTRL_A57_CPUAVSVOLIDX_UNION
 结构说明  : A57_CPUAVSVOLIDX 寄存器结构定义。地址偏移量:0x214，初值:0x00000000，宽度:32
 寄存器说明: A57_CPU AVS电压控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_cpu_avs_vol_idx    : 8;  /* bit[0-7] : A57 AVS当前电压值。该值可以通过软件配置。如果配置该寄存器。时bit 8不写1，则需要软件配置该寄存器。值与PMU电压值相同 */
        unsigned int  a57_cpu_vol_chg_sftreq : 1;  /* bit[8-8] : A57 CPU电压改变软件请求信号。
                                                                 写1：请求改变电压，电压值为bit 7:0值
                                                                 写0：无效果 */
        unsigned int  reserved               : 23; /* bit[9-31]: 保留 */
    } reg;
} SOC_PMCTRL_A57_CPUAVSVOLIDX_UNION;
#endif
#define SOC_PMCTRL_A57_CPUAVSVOLIDX_a57_cpu_avs_vol_idx_START     (0)
#define SOC_PMCTRL_A57_CPUAVSVOLIDX_a57_cpu_avs_vol_idx_END       (7)
#define SOC_PMCTRL_A57_CPUAVSVOLIDX_a57_cpu_vol_chg_sftreq_START  (8)
#define SOC_PMCTRL_A57_CPUAVSVOLIDX_a57_cpu_vol_chg_sftreq_END    (8)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DCLKSEL_UNION
 结构说明  : G3DCLKSEL 寄存器结构定义。地址偏移量:0x220，初值:0x00000003，宽度:32
 寄存器说明: G3D AXI时钟选择寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3da_sw     : 1;  /* bit[0-0] : G3D AXI时钟选择哪路时钟。
                                                      0：G3D AXI时钟由0路时钟驱动；
                                                      1：G3D AXI时钟由1路时钟驱动。 */
        unsigned int  g3da_sw_ack : 1;  /* bit[1-1] : 当前G3D AXI时钟选择哪路时钟的状态指示。
                                                      0：G3D AXI时钟由0路时钟驱动；
                                                      1：G3D AXI时钟由1路时钟驱动。 */
        unsigned int  reserved    : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DCLKSEL_UNION;
#endif
#define SOC_PMCTRL_G3DCLKSEL_g3da_sw_START      (0)
#define SOC_PMCTRL_G3DCLKSEL_g3da_sw_END        (0)
#define SOC_PMCTRL_G3DCLKSEL_g3da_sw_ack_START  (1)
#define SOC_PMCTRL_G3DCLKSEL_g3da_sw_ack_END    (1)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DCLKDIV_UNION
 结构说明  : G3DCLKDIV 寄存器结构定义。地址偏移量:0x224，初值:0x7DF31F1F，宽度:32
 寄存器说明: G3D AXI时钟分频寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3da_clk_div0     : 8;  /* bit[0-7]  : G3D AXI时钟分频器0，高3bit为PLL选择，选择PPLL0~4和APLL2，低5bit为分频系数 */
        unsigned int  g3da_clk_div1     : 8;  /* bit[8-15] : G3D AXI时钟分频器1，高3bit为PLL选择，选择PPLL0~4和APLL2，低5bit为分频系数 */
        unsigned int  g3da_clk_div0_ack : 1;  /* bit[16-16]: G3D AXI时钟分频器0切换完成标志。 */
        unsigned int  g3da_clk_div1_ack : 1;  /* bit[17-17]: G3D AXI时钟分频器1切换完成标志。 */
        unsigned int  reserved          : 2;  /* bit[18-19]: 保留 */
        unsigned int  g3da_clk_div0_mux : 6;  /* bit[20-25]: 0路时钟当前正在运行的分频状态； */
        unsigned int  g3da_clk_div1_mux : 6;  /* bit[26-31]: 1路时钟当前正在运行的分频状态； */
    } reg;
} SOC_PMCTRL_G3DCLKDIV_UNION;
#endif
#define SOC_PMCTRL_G3DCLKDIV_g3da_clk_div0_START      (0)
#define SOC_PMCTRL_G3DCLKDIV_g3da_clk_div0_END        (7)
#define SOC_PMCTRL_G3DCLKDIV_g3da_clk_div1_START      (8)
#define SOC_PMCTRL_G3DCLKDIV_g3da_clk_div1_END        (15)
#define SOC_PMCTRL_G3DCLKDIV_g3da_clk_div0_ack_START  (16)
#define SOC_PMCTRL_G3DCLKDIV_g3da_clk_div0_ack_END    (16)
#define SOC_PMCTRL_G3DCLKDIV_g3da_clk_div1_ack_START  (17)
#define SOC_PMCTRL_G3DCLKDIV_g3da_clk_div1_ack_END    (17)
#define SOC_PMCTRL_G3DCLKDIV_g3da_clk_div0_mux_START  (20)
#define SOC_PMCTRL_G3DCLKDIV_g3da_clk_div0_mux_END    (25)
#define SOC_PMCTRL_G3DCLKDIV_g3da_clk_div1_mux_START  (26)
#define SOC_PMCTRL_G3DCLKDIV_g3da_clk_div1_mux_END    (31)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DDVFSEN_UNION
 结构说明  : G3DDVFSEN 寄存器结构定义。地址偏移量:0x228，初值:0x00000000，宽度:32
 寄存器说明: G3D DVFS使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_dvfs_en : 1;  /* bit[0-0] : G3D DVFS使能。
                                                      0：G3D DVFS功能关闭；
                                                      1：G3D DVFS功能开启。 */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DDVFSEN_UNION;
#endif
#define SOC_PMCTRL_G3DDVFSEN_g3d_dvfs_en_START  (0)
#define SOC_PMCTRL_G3DDVFSEN_g3d_dvfs_en_END    (0)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DDVFSSTART_UNION
 结构说明  : G3DDVFSSTART 寄存器结构定义。地址偏移量:0x22C，初值:0x00000000，宽度:32
 寄存器说明: G3D DVFS启动寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_profile_updn : 1;  /* bit[0-0] : G3D DVFS启动。
                                                           0：G3D DVFS降低Profile启动；
                                                           1：G3D DVFS提升Profile启动。 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DDVFSSTART_UNION;
#endif
#define SOC_PMCTRL_G3DDVFSSTART_g3d_profile_updn_START  (0)
#define SOC_PMCTRL_G3DDVFSSTART_g3d_profile_updn_END    (0)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DCLKPROFILE_UNION
 结构说明  : G3DCLKPROFILE 寄存器结构定义。地址偏移量:0x230，初值:0x00000000，宽度:32
 寄存器说明: G3D频率Profile寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3da_clk_div : 8;  /* bit[0-7] : G3D AXI时钟分频参数，高3bit为PLL选择，选择PPLL0~4和APLL2，低5bit为分频系数 */
        unsigned int  g3da_clk_sel : 1;  /* bit[8-8] : G3D AXI时钟选择参数，选择DIV0还是DIV1，每次DVFS需要切换DIV。 */
        unsigned int  reserved     : 23; /* bit[9-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DCLKPROFILE_UNION;
#endif
#define SOC_PMCTRL_G3DCLKPROFILE_g3da_clk_div_START  (0)
#define SOC_PMCTRL_G3DCLKPROFILE_g3da_clk_div_END    (7)
#define SOC_PMCTRL_G3DCLKPROFILE_g3da_clk_sel_START  (8)
#define SOC_PMCTRL_G3DCLKPROFILE_g3da_clk_sel_END    (8)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DVOLMOD_UNION
 结构说明  : G3DVOLMOD 寄存器结构定义。地址偏移量:0x234，初值:0x00000000，宽度:32
 寄存器说明: G3D DVFS调压模式寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_vol_mod         : 1;  /* bit[0-0] : G3D DVFS时，是否需要调压。
                                                              0：G3D DVFS时，不需要调压；
                                                              1：G3D DVFS时，需要调压。 */
        unsigned int  g3d_clk_off_vol_mod : 1;  /* bit[1-1] : G3D时钟是否关闭。
                                                              0：G3D时钟保持打开；
                                                              1：G3D时钟要求关闭。 */
        unsigned int  reserved            : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DVOLMOD_UNION;
#endif
#define SOC_PMCTRL_G3DVOLMOD_g3d_vol_mod_START          (0)
#define SOC_PMCTRL_G3DVOLMOD_g3d_vol_mod_END            (0)
#define SOC_PMCTRL_G3DVOLMOD_g3d_clk_off_vol_mod_START  (1)
#define SOC_PMCTRL_G3DVOLMOD_g3d_clk_off_vol_mod_END    (1)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DVOLPROFILE_UNION
 结构说明  : G3DVOLPROFILE 寄存器结构定义。地址偏移量:0x238，初值:0x00000000，宽度:32
 寄存器说明: G3D电压Profile寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_vol_idx : 8;  /* bit[0-7] : G3D电压Profile参数。 */
        unsigned int  reserved    : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DVOLPROFILE_UNION;
#endif
#define SOC_PMCTRL_G3DVOLPROFILE_g3d_vol_idx_START  (0)
#define SOC_PMCTRL_G3DVOLPROFILE_g3d_vol_idx_END    (7)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DPHASEMOD_UNION
 结构说明  : G3DPHASEMOD 寄存器结构定义。地址偏移量:0x240，初值:0x00000000，宽度:32
 寄存器说明: G3D DVFS改变电压相位模式寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_phase_mod         : 1;  /* bit[0-0] : G3D DVFS时，是否改变电压相位。
                                                                0：G3D DVFS时，不改变电压相位；
                                                                1：G3D DVFS时，改变电压相位。 */
        unsigned int  g3d_clk_off_phase_mod : 1;  /* bit[1-1] : G3D DVFS改变电压相位时是否关闭G3D时钟。
                                                                0：G3D改变电压相位时，G3D时钟保持打开；
                                                                1：G3D改变电压相位时，G3D时钟关闭。 */
        unsigned int  reserved              : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DPHASEMOD_UNION;
#endif
#define SOC_PMCTRL_G3DPHASEMOD_g3d_phase_mod_START          (0)
#define SOC_PMCTRL_G3DPHASEMOD_g3d_phase_mod_END            (0)
#define SOC_PMCTRL_G3DPHASEMOD_g3d_clk_off_phase_mod_START  (1)
#define SOC_PMCTRL_G3DPHASEMOD_g3d_clk_off_phase_mod_END    (1)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DPHASEPROFILE_UNION
 结构说明  : G3DPHASEPROFILE 寄存器结构定义。地址偏移量:0x244，初值:0x00000000，宽度:32
 寄存器说明: G3D相位Profile寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_phase_idx : 8;  /* bit[0-7] : G3D相位Profile参数。 */
        unsigned int  reserved      : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DPHASEPROFILE_UNION;
#endif
#define SOC_PMCTRL_G3DPHASEPROFILE_g3d_phase_idx_START  (0)
#define SOC_PMCTRL_G3DPHASEPROFILE_g3d_phase_idx_END    (7)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DVOLPHASESEL_UNION
 结构说明  : G3DVOLPHASESEL 寄存器结构定义。地址偏移量:0x248，初值:0x00000000，宽度:32
 寄存器说明: G3D电压/相位配置选择寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_vol_phase_sel : 1;  /* bit[0-0] : G3D电压/相位信号输出选择
                                                            0：DVFS时先调相位再调电压，配置profile寄存器。时不需要改变；
                                                            1：DVFS先调电压在调相位，配置profile寄存器。时需要改变（电压profile寄存器。控制相位，相位profile寄存器。控制电压）。 */
        unsigned int  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DVOLPHASESEL_UNION;
#endif
#define SOC_PMCTRL_G3DVOLPHASESEL_g3d_vol_phase_sel_START  (0)
#define SOC_PMCTRL_G3DVOLPHASESEL_g3d_vol_phase_sel_END    (0)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DPMUSEL_UNION
 结构说明  : G3DPMUSEL 寄存器结构定义。地址偏移量:0x24C，初值:0x00000000，宽度:32
 寄存器说明: G3D输出PMU选择寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_pmu_sel : 1;  /* bit[0-0] : G3D输出PMU选择
                                                      0：G3D输出的信号给PMUSSI；
                                                      1：G3D输出的信号给PMUI2C。（只能静态配置） */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DPMUSEL_UNION;
#endif
#define SOC_PMCTRL_G3DPMUSEL_g3d_pmu_sel_START  (0)
#define SOC_PMCTRL_G3DPMUSEL_g3d_pmu_sel_END    (0)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DVOLUPSTEPTIME_UNION
 结构说明  : G3DVOLUPSTEPTIME 寄存器结构定义。地址偏移量:0x250，初值:0x00000000，宽度:32
 寄存器说明: G3D电压上升一档稳定步长时间寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_vol_up_step_time : 13; /* bit[0-12] : G3D电压上升稳定步长时间。 */
        unsigned int  reserved             : 19; /* bit[13-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DVOLUPSTEPTIME_UNION;
#endif
#define SOC_PMCTRL_G3DVOLUPSTEPTIME_g3d_vol_up_step_time_START  (0)
#define SOC_PMCTRL_G3DVOLUPSTEPTIME_g3d_vol_up_step_time_END    (12)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DVOLDNSTEPTIME_UNION
 结构说明  : G3DVOLDNSTEPTIME 寄存器结构定义。地址偏移量:0x254，初值:0x00000000，宽度:32
 寄存器说明: G3D电压下降一档稳定步长时间寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_vol_dn_step_time : 13; /* bit[0-12] : G3D电压下降稳定步长时间。 */
        unsigned int  reserved             : 19; /* bit[13-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DVOLDNSTEPTIME_UNION;
#endif
#define SOC_PMCTRL_G3DVOLDNSTEPTIME_g3d_vol_dn_step_time_START  (0)
#define SOC_PMCTRL_G3DVOLDNSTEPTIME_g3d_vol_dn_step_time_END    (12)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DPHASEUPTIME_UNION
 结构说明  : G3DPHASEUPTIME 寄存器结构定义。地址偏移量:0x258，初值:0x00000000，宽度:32
 寄存器说明: G3D DVFS时改变电压相位的上升稳定时间寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_dvfs_phase_up_time : 20; /* bit[0-19] : G3D DVFS时，改变电压相位的上升稳定时间。 */
        unsigned int  reserved               : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DPHASEUPTIME_UNION;
#endif
#define SOC_PMCTRL_G3DPHASEUPTIME_g3d_dvfs_phase_up_time_START  (0)
#define SOC_PMCTRL_G3DPHASEUPTIME_g3d_dvfs_phase_up_time_END    (19)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DPHASEDNTIME_UNION
 结构说明  : G3DPHASEDNTIME 寄存器结构定义。地址偏移量:0x25C，初值:0x00000000，宽度:32
 寄存器说明: G3D DVFS时改变电压相位的下降稳定时间寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_dvfs_phase_dn_time : 20; /* bit[0-19] : G3D DVFS时，改变电压相位的下降稳定时间。 */
        unsigned int  reserved               : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DPHASEDNTIME_UNION;
#endif
#define SOC_PMCTRL_G3DPHASEDNTIME_g3d_dvfs_phase_dn_time_START  (0)
#define SOC_PMCTRL_G3DPHASEDNTIME_g3d_dvfs_phase_dn_time_END    (19)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DPMUHOLDTIME_UNION
 结构说明  : G3DPMUHOLDTIME 寄存器结构定义。地址偏移量:0x260，初值:0x00000000，宽度:32
 寄存器说明: G3D电压稳定时间裕量寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_pmu_vol_hold_time : 20; /* bit[0-19] : G3D调压时，由于端口传输时间而增加的电压稳定时间 */
        unsigned int  reserved              : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DPMUHOLDTIME_UNION;
#endif
#define SOC_PMCTRL_G3DPMUHOLDTIME_g3d_pmu_vol_hold_time_START  (0)
#define SOC_PMCTRL_G3DPMUHOLDTIME_g3d_pmu_vol_hold_time_END    (19)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DHPMBYPASS_UNION
 结构说明  : G3DHPMBYPASS 寄存器结构定义。地址偏移量:0x264，初值:0x03F100FF，宽度:32
 寄存器说明: G3D HPM硬件控制bypass寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_hpm0_bypass        : 1;  /* bit[0-0]  : G3D HPM0是否有G3D硬件状态机控制。
                                                                  0：控制；
                                                                  1：不控制。 */
        unsigned int  g3d_hpm1_bypass        : 1;  /* bit[1-1]  : G3D HPM1是否有G3D硬件状态机控制。
                                                                  0：控制；
                                                                  1：不控制。 */
        unsigned int  g3d_hpm2_bypass        : 1;  /* bit[2-2]  : G3D HPM2是否有G3D硬件状态机控制。
                                                                  0：控制；
                                                                  1：不控制。 */
        unsigned int  g3d_hpm3_bypass        : 1;  /* bit[3-3]  : G3D HPM3是否有G3D硬件状态机控制。
                                                                  0：控制；
                                                                  1：不控制。 */
        unsigned int  g3d_hpm_dly_cnt        : 12; /* bit[4-15] : G3D shader掉电再上电后HPM可用的等待时间。
                                                                  单位为PMCTRL工作频率。 */
        unsigned int  g3d_idle_clkdiv_bypass : 1;  /* bit[16-16]: G3D子系统IDLE时自动降频功能。
                                                                  0：生效；
                                                                  1：不生效。 */
        unsigned int  reserved_0             : 3;  /* bit[17-19]: 保留 */
        unsigned int  g3d_idle_clk_div       : 6;  /* bit[20-25]: G3D IDLE时自动降频的分频比。 */
        unsigned int  reserved_1             : 6;  /* bit[26-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DHPMBYPASS_UNION;
#endif
#define SOC_PMCTRL_G3DHPMBYPASS_g3d_hpm0_bypass_START         (0)
#define SOC_PMCTRL_G3DHPMBYPASS_g3d_hpm0_bypass_END           (0)
#define SOC_PMCTRL_G3DHPMBYPASS_g3d_hpm1_bypass_START         (1)
#define SOC_PMCTRL_G3DHPMBYPASS_g3d_hpm1_bypass_END           (1)
#define SOC_PMCTRL_G3DHPMBYPASS_g3d_hpm2_bypass_START         (2)
#define SOC_PMCTRL_G3DHPMBYPASS_g3d_hpm2_bypass_END           (2)
#define SOC_PMCTRL_G3DHPMBYPASS_g3d_hpm3_bypass_START         (3)
#define SOC_PMCTRL_G3DHPMBYPASS_g3d_hpm3_bypass_END           (3)
#define SOC_PMCTRL_G3DHPMBYPASS_g3d_hpm_dly_cnt_START         (4)
#define SOC_PMCTRL_G3DHPMBYPASS_g3d_hpm_dly_cnt_END           (15)
#define SOC_PMCTRL_G3DHPMBYPASS_g3d_idle_clkdiv_bypass_START  (16)
#define SOC_PMCTRL_G3DHPMBYPASS_g3d_idle_clkdiv_bypass_END    (16)
#define SOC_PMCTRL_G3DHPMBYPASS_g3d_idle_clk_div_START        (20)
#define SOC_PMCTRL_G3DHPMBYPASS_g3d_idle_clk_div_END          (25)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DAUTOCLKDIVBYPASS_UNION
 结构说明  : G3DAUTOCLKDIVBYPASS 寄存器结构定义。地址偏移量:0x268，初值:0x000F3F15，宽度:32
 寄存器说明: G3D自动分频bypass控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_auto_clkdiv_bypass : 1;  /* bit[0-0]  : G3D shader上下电时硬件自动分频功能bypass控制。
                                                                  0：G3D 自动分频功能开启；
                                                                  1：G3D 自动分频功能关闭。 */
        unsigned int  g3d_auto_clkdiv_time   : 7;  /* bit[1-7]  : G3D自动分频后稳定时间。
                                                                  计数单位是PMCTRL工作时钟。 */
        unsigned int  g3d_pwr_dly_cnt        : 8;  /* bit[8-15] : G3D pwr_updn_ack持续的周期数。
                                                                  计数单位是PMCTRL工作时钟。 */
        unsigned int  g3d_auto_clk_div       : 2;  /* bit[16-17]: G3D shader上下电时硬件自动分频参数； */
        unsigned int  g3d_div_debounce       : 6;  /* bit[18-23]: G3D shader上下电时自动降频请求的防抖周期数； */
        unsigned int  reserved               : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DAUTOCLKDIVBYPASS_UNION;
#endif
#define SOC_PMCTRL_G3DAUTOCLKDIVBYPASS_g3d_auto_clkdiv_bypass_START  (0)
#define SOC_PMCTRL_G3DAUTOCLKDIVBYPASS_g3d_auto_clkdiv_bypass_END    (0)
#define SOC_PMCTRL_G3DAUTOCLKDIVBYPASS_g3d_auto_clkdiv_time_START    (1)
#define SOC_PMCTRL_G3DAUTOCLKDIVBYPASS_g3d_auto_clkdiv_time_END      (7)
#define SOC_PMCTRL_G3DAUTOCLKDIVBYPASS_g3d_pwr_dly_cnt_START         (8)
#define SOC_PMCTRL_G3DAUTOCLKDIVBYPASS_g3d_pwr_dly_cnt_END           (15)
#define SOC_PMCTRL_G3DAUTOCLKDIVBYPASS_g3d_auto_clk_div_START        (16)
#define SOC_PMCTRL_G3DAUTOCLKDIVBYPASS_g3d_auto_clk_div_END          (17)
#define SOC_PMCTRL_G3DAUTOCLKDIVBYPASS_g3d_div_debounce_START        (18)
#define SOC_PMCTRL_G3DAUTOCLKDIVBYPASS_g3d_div_debounce_END          (23)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DAVSEN_UNION
 结构说明  : G3DAVSEN 寄存器结构定义。地址偏移量:0x270，初值:0x00000000，宽度:32
 寄存器说明: G3D AVS使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_avs_en        : 1;  /* bit[0-0] : G3D AVS使能。
                                                            0：G3D AVS功能关闭；
                                                            1：G3D AVS功能开启。 */
        unsigned int  g3d_avs_pwctrl_en : 1;  /* bit[1-1] : G3D AVS调压使能。
                                                            0：G3D AVS调压功能关闭；
                                                            1：G3D AVS调压功能开启。 */
        unsigned int  reserved          : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DAVSEN_UNION;
#endif
#define SOC_PMCTRL_G3DAVSEN_g3d_avs_en_START         (0)
#define SOC_PMCTRL_G3DAVSEN_g3d_avs_en_END           (0)
#define SOC_PMCTRL_G3DAVSEN_g3d_avs_pwctrl_en_START  (1)
#define SOC_PMCTRL_G3DAVSEN_g3d_avs_pwctrl_en_END    (1)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DAVSPARAMOD_UNION
 结构说明  : G3DAVSPARAMOD 寄存器结构定义。地址偏移量:0x274，初值:0x00000000，宽度:32
 寄存器说明: G3D AVS参数模式寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_avspara_mod : 1;  /* bit[0-0] : G3D AVS参数实时更新控制。
                                                          通常，G3D AVS参数在G3D DVFS运行之后更新；如果对这个寄存器。写1，AVS参数立即更新；如果对这个寄存器。写0，无效。 */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DAVSPARAMOD_UNION;
#endif
#define SOC_PMCTRL_G3DAVSPARAMOD_g3d_avspara_mod_START  (0)
#define SOC_PMCTRL_G3DAVSPARAMOD_g3d_avspara_mod_END    (0)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DAVSPARA0_UNION
 结构说明  : G3DAVSPARA0 寄存器结构定义。地址偏移量:0x278，初值:0x00000000，宽度:32
 寄存器说明: G3D AVS参数寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0         : 2;  /* bit[0-1]  : 保留 */
        unsigned int  g3d_avs_opc_offset : 10; /* bit[2-11] : G3D AVS原始性能码偏移。 */
        unsigned int  g3d_avs_rcc        : 5;  /* bit[12-16]: G3D AVS参考校准码。 */
        unsigned int  g3d_avs_irgap      : 5;  /* bit[17-21]: G3D AVS IRDrop裕量。 */
        unsigned int  g3d_avs_opc_mod    : 2;  /* bit[22-23]: G3D AVS中同一个HPM OPC值的多次采样如何处理。
                                                              00：OPC取均值；
                                                              01：OPC取最小值；
                                                              10：OPC取最大值；
                                                              11：保留。 */
        unsigned int  g3d_avs_hpm_sel    : 3;  /* bit[24-26]: G3D AVS中多个HPM的PC值如何处理。
                                                              000：取G3D HPM0的PC值；
                                                              001：取G3D HPM1的PC值；
                                                              010：取G3D HPM2的PC值；
                                                              011：取G3D HPM3的PC值；
                                                              100：取G3D global HPM的PC值；
                                                              101：取HPM中的最小值；
                                                              110：取HPM中的最大值；
                                                              其他：保留。 */
        unsigned int  g3d_avs_opc_shift  : 3;  /* bit[27-29]: G3D AVS原始性能码移位。 */
        unsigned int  reserved_1         : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DAVSPARA0_UNION;
#endif
#define SOC_PMCTRL_G3DAVSPARA0_g3d_avs_opc_offset_START  (2)
#define SOC_PMCTRL_G3DAVSPARA0_g3d_avs_opc_offset_END    (11)
#define SOC_PMCTRL_G3DAVSPARA0_g3d_avs_rcc_START         (12)
#define SOC_PMCTRL_G3DAVSPARA0_g3d_avs_rcc_END           (16)
#define SOC_PMCTRL_G3DAVSPARA0_g3d_avs_irgap_START       (17)
#define SOC_PMCTRL_G3DAVSPARA0_g3d_avs_irgap_END         (21)
#define SOC_PMCTRL_G3DAVSPARA0_g3d_avs_opc_mod_START     (22)
#define SOC_PMCTRL_G3DAVSPARA0_g3d_avs_opc_mod_END       (23)
#define SOC_PMCTRL_G3DAVSPARA0_g3d_avs_hpm_sel_START     (24)
#define SOC_PMCTRL_G3DAVSPARA0_g3d_avs_hpm_sel_END       (26)
#define SOC_PMCTRL_G3DAVSPARA0_g3d_avs_opc_shift_START   (27)
#define SOC_PMCTRL_G3DAVSPARA0_g3d_avs_opc_shift_END     (29)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DAVSPARA1_UNION
 结构说明  : G3DAVSPARA1 寄存器结构定义。地址偏移量:0x27C，初值:0x00000000，宽度:32
 寄存器说明: G3D AVS参数寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_avs_vol_up_gain1 : 4;  /* bit[0-3]  : G3D AVS升压增益。 */
        unsigned int  g3d_avs_vol_up_gain2 : 4;  /* bit[4-7]  : G3D AVS升压增益。 */
        unsigned int  g3d_avs_vol_up_gain3 : 4;  /* bit[8-11] : G3D AVS升压增益。 */
        unsigned int  g3d_avs_vol_up_gain4 : 4;  /* bit[12-15]: G3D AVS升压增益。 */
        unsigned int  g3d_avs_vol_up_gain5 : 4;  /* bit[16-19]: G3D AVS升压增益。 */
        unsigned int  g3d_avs_vol_up_gain6 : 4;  /* bit[20-23]: G3D AVS升压增益。 */
        unsigned int  g3d_avs_vol_up_gain7 : 4;  /* bit[24-27]: G3D AVS升压增益。 */
        unsigned int  g3d_avs_vol_up_gain8 : 4;  /* bit[28-31]: G3D AVS升压增益。 */
    } reg;
} SOC_PMCTRL_G3DAVSPARA1_UNION;
#endif
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_vol_up_gain1_START  (0)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_vol_up_gain1_END    (3)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_vol_up_gain2_START  (4)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_vol_up_gain2_END    (7)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_vol_up_gain3_START  (8)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_vol_up_gain3_END    (11)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_vol_up_gain4_START  (12)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_vol_up_gain4_END    (15)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_vol_up_gain5_START  (16)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_vol_up_gain5_END    (19)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_vol_up_gain6_START  (20)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_vol_up_gain6_END    (23)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_vol_up_gain7_START  (24)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_vol_up_gain7_END    (27)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_vol_up_gain8_START  (28)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_vol_up_gain8_END    (31)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DAVSPARA2_UNION
 结构说明  : G3DAVSPARA2 寄存器结构定义。地址偏移量:0x280，初值:0x00000000，宽度:32
 寄存器说明: G3D AVS参数寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_avs_vol_up_gain9  : 4;  /* bit[0-3]  : G3D AVS升压增益。 */
        unsigned int  g3d_avs_vol_up_gain10 : 4;  /* bit[4-7]  : G3D AVS升压增益。 */
        unsigned int  g3d_avs_vol_up_gain11 : 4;  /* bit[8-11] : G3D AVS升压增益。 */
        unsigned int  g3d_avs_vol_up_gain12 : 4;  /* bit[12-15]: G3D AVS升压增益。 */
        unsigned int  g3d_avs_vol_up_gain13 : 4;  /* bit[16-19]: G3D AVS升压增益。 */
        unsigned int  g3d_avs_vol_up_gain14 : 4;  /* bit[20-23]: G3D AVS升压增益。 */
        unsigned int  g3d_avs_vol_up_gain15 : 7;  /* bit[24-30]: G3D AVS升压增益。 */
        unsigned int  reserved              : 1;  /* bit[31-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DAVSPARA2_UNION;
#endif
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain9_START   (0)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain9_END     (3)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain10_START  (4)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain10_END    (7)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain11_START  (8)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain11_END    (11)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain12_START  (12)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain12_END    (15)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain13_START  (16)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain13_END    (19)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain14_START  (20)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain14_END    (23)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain15_START  (24)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain15_END    (30)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DAVSPARA3_UNION
 结构说明  : G3DAVSPARA3 寄存器结构定义。地址偏移量:0x284，初值:0x00000000，宽度:32
 寄存器说明: G3D AVS参数寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_avs_vol_dn_gain1  : 4;  /* bit[0-3]  : G3D AVS降压增益。 */
        unsigned int  g3d_avs_vol_dn_gain2  : 4;  /* bit[4-7]  : G3D AVS降压增益。 */
        unsigned int  g3d_avs_vol_dn_gain3  : 4;  /* bit[8-11] : G3D AVS降压增益。 */
        unsigned int  g3d_avs_vol_dn_gain4  : 4;  /* bit[12-15]: G3D AVS降压增益。 */
        unsigned int  g3d_avs_vol_dn_gain5  : 4;  /* bit[16-19]: G3D AVS降压增益。 */
        unsigned int  g3d_avs_vol_dn_gain6  : 4;  /* bit[20-23]: G3D AVS降压增益。 */
        unsigned int  g3d_avs_vol_dn_gain7  : 4;  /* bit[24-27]: G3D AVS降压增益。 */
        unsigned int  g3dc_avs_vol_dn_gain8 : 4;  /* bit[28-31]: G3D AVS降压增益。 */
    } reg;
} SOC_PMCTRL_G3DAVSPARA3_UNION;
#endif
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_dn_gain1_START   (0)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_dn_gain1_END     (3)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_dn_gain2_START   (4)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_dn_gain2_END     (7)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_dn_gain3_START   (8)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_dn_gain3_END     (11)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_dn_gain4_START   (12)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_dn_gain4_END     (15)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_dn_gain5_START   (16)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_dn_gain5_END     (19)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_dn_gain6_START   (20)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_dn_gain6_END     (23)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_dn_gain7_START   (24)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_dn_gain7_END     (27)
#define SOC_PMCTRL_G3DAVSPARA3_g3dc_avs_vol_dn_gain8_START  (28)
#define SOC_PMCTRL_G3DAVSPARA3_g3dc_avs_vol_dn_gain8_END    (31)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DAVSPARA4_UNION
 结构说明  : G3DAVSPARA4 寄存器结构定义。地址偏移量:0x288，初值:0x00000000，宽度:32
 寄存器说明: G3D AVS参数寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_avs_vol_dn_gain9  : 4;  /* bit[0-3]  : G3D AVS降压增益。 */
        unsigned int  g3d_avs_vol_dn_gain10 : 4;  /* bit[4-7]  : G3D AVS降压增益。 */
        unsigned int  g3d_avs_vol_dn_gain11 : 4;  /* bit[8-11] : G3D AVS降压增益。 */
        unsigned int  g3d_avs_vol_dn_gain12 : 4;  /* bit[12-15]: G3D AVS降压增益。 */
        unsigned int  g3d_avs_vol_dn_gain13 : 4;  /* bit[16-19]: G3D AVS降压增益。 */
        unsigned int  g3d_avs_vol_dn_gain14 : 4;  /* bit[20-23]: G3D AVS降压增益。 */
        unsigned int  g3d_avs_vol_dn_gain15 : 7;  /* bit[24-30]: G3D AVS降压增益。 */
        unsigned int  reserved              : 1;  /* bit[31-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DAVSPARA4_UNION;
#endif
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain9_START   (0)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain9_END     (3)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain10_START  (4)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain10_END    (7)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain11_START  (8)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain11_END    (11)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain12_START  (12)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain12_END    (15)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain13_START  (16)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain13_END    (19)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain14_START  (20)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain14_END    (23)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain15_START  (24)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain15_END    (30)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DAVSPARA5_UNION
 结构说明  : G3DAVSPARA5 寄存器结构定义。地址偏移量:0x28C，初值:0x00000000，宽度:32
 寄存器说明: G3D AVS参数寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_avs_max_vol : 7;  /* bit[0-6]  : G3D AVS最高电压限制。 */
        unsigned int  g3d_avs_min_vol : 7;  /* bit[7-13] : G3D AVS最低电压限制。 */
        unsigned int  reserved        : 18; /* bit[14-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DAVSPARA5_UNION;
#endif
#define SOC_PMCTRL_G3DAVSPARA5_g3d_avs_max_vol_START  (0)
#define SOC_PMCTRL_G3DAVSPARA5_g3d_avs_max_vol_END    (6)
#define SOC_PMCTRL_G3DAVSPARA5_g3d_avs_min_vol_START  (7)
#define SOC_PMCTRL_G3DAVSPARA5_g3d_avs_min_vol_END    (13)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DAVSPARA6_UNION
 结构说明  : G3DAVSPARA6 寄存器结构定义。地址偏移量:0x290，初值:0x00000000，宽度:32
 寄存器说明: G3D AVS参数寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_avs_sample_num : 22; /* bit[0-21] : G3D AVS性能码采样次数。配置值必须是2的N次方。 */
        unsigned int  reserved           : 10; /* bit[22-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DAVSPARA6_UNION;
#endif
#define SOC_PMCTRL_G3DAVSPARA6_g3d_avs_sample_num_START  (0)
#define SOC_PMCTRL_G3DAVSPARA6_g3d_avs_sample_num_END    (21)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DHPMTYP_UNION
 结构说明  : G3DHPMTYP 寄存器结构定义。地址偏移量:0x294，初值:0x00000000，宽度:32
 寄存器说明: G3D HPM类型选择寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_hpm_type   : 1;  /* bit[0-0]  : AVS选择使用G3D HPM类型。
                                                          0：AVS选择使用标准HPM；
                                                          1：AVS选择使用X型HPM。 */
        unsigned int  g3ds_hpm0_mask : 1;  /* bit[1-1]  : AVS控制是否屏蔽HPM0。
                                                          0：不屏蔽；
                                                          1：屏蔽。 */
        unsigned int  g3ds_hpm1_mask : 1;  /* bit[2-2]  : AVS控制是否屏蔽HPM1。
                                                          0：不屏蔽；
                                                          1：屏蔽。 */
        unsigned int  g3ds_hpm2_mask : 1;  /* bit[3-3]  : AVS控制是否屏蔽HPM2。
                                                          0：不屏蔽；
                                                          1：屏蔽。 */
        unsigned int  g3ds_hpm3_mask : 1;  /* bit[4-4]  : AVS控制是否屏蔽HPM3。
                                                          0：不屏蔽；
                                                          1：屏蔽。 */
        unsigned int  g3dg_hpm_mask  : 1;  /* bit[5-5]  : AVS控制是否屏蔽global HPM。
                                                          0：不屏蔽；
                                                          1：屏蔽。 */
        unsigned int  reserved       : 10; /* bit[6-15] : 保留 */
        unsigned int  biten          : 16; /* bit[16-31]: 每个比特位的使能位：
                                                          只有当biten对应的比特位为1'b1，相应的比特位才起作用。biten[0]就是bit 0的使能位。写1有效。 */
    } reg;
} SOC_PMCTRL_G3DHPMTYP_UNION;
#endif
#define SOC_PMCTRL_G3DHPMTYP_g3d_hpm_type_START    (0)
#define SOC_PMCTRL_G3DHPMTYP_g3d_hpm_type_END      (0)
#define SOC_PMCTRL_G3DHPMTYP_g3ds_hpm0_mask_START  (1)
#define SOC_PMCTRL_G3DHPMTYP_g3ds_hpm0_mask_END    (1)
#define SOC_PMCTRL_G3DHPMTYP_g3ds_hpm1_mask_START  (2)
#define SOC_PMCTRL_G3DHPMTYP_g3ds_hpm1_mask_END    (2)
#define SOC_PMCTRL_G3DHPMTYP_g3ds_hpm2_mask_START  (3)
#define SOC_PMCTRL_G3DHPMTYP_g3ds_hpm2_mask_END    (3)
#define SOC_PMCTRL_G3DHPMTYP_g3ds_hpm3_mask_START  (4)
#define SOC_PMCTRL_G3DHPMTYP_g3ds_hpm3_mask_END    (4)
#define SOC_PMCTRL_G3DHPMTYP_g3dg_hpm_mask_START   (5)
#define SOC_PMCTRL_G3DHPMTYP_g3dg_hpm_mask_END     (5)
#define SOC_PMCTRL_G3DHPMTYP_biten_START           (16)
#define SOC_PMCTRL_G3DHPMTYP_biten_END             (31)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DHPMEN_UNION
 结构说明  : G3DHPMEN 寄存器结构定义。地址偏移量:0x298，初值:0x00000000，宽度:32
 寄存器说明: G3D HPM使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3ds_hpm0_en : 1;  /* bit[0-0] : G3D HPM使能。
                                                       HPM使能控制除了软件可以置位或清除，在AVS流程中也会被AVS主控逻辑自动置位或清除。 */
        unsigned int  g3ds_hpm1_en : 1;  /* bit[1-1] : G3D HPM使能。
                                                       HPM使能控制除了软件可以置位或清除，在AVS流程中也会被AVS主控逻辑自动置位或清除。 */
        unsigned int  g3dg_hpm_en  : 1;  /* bit[2-2] : G3D global HPM使能。
                                                       HPM使能控制除了软件可以置位或清除，在AVS流程中也会被AVS主控逻辑自动置位或清除。 */
        unsigned int  reserved     : 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DHPMEN_UNION;
#endif
#define SOC_PMCTRL_G3DHPMEN_g3ds_hpm0_en_START  (0)
#define SOC_PMCTRL_G3DHPMEN_g3ds_hpm0_en_END    (0)
#define SOC_PMCTRL_G3DHPMEN_g3ds_hpm1_en_START  (1)
#define SOC_PMCTRL_G3DHPMEN_g3ds_hpm1_en_END    (1)
#define SOC_PMCTRL_G3DHPMEN_g3dg_hpm_en_START   (2)
#define SOC_PMCTRL_G3DHPMEN_g3dg_hpm_en_END     (2)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DHPMXEN_UNION
 结构说明  : G3DHPMXEN 寄存器结构定义。地址偏移量:0x29C，初值:0x00000000，宽度:32
 寄存器说明: G3D HPMX使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3ds_hpmx0_en : 1;  /* bit[0-0] : G3D HPMX使能。
                                                        HPMX使能控制除了软件可以置位或清除，在AVS流程中也会被AVS主控逻辑自动置位或清除。 */
        unsigned int  g3ds_hpmx1_en : 1;  /* bit[1-1] : G3D HPMX使能。
                                                        HPMX使能控制除了软件可以置位或清除，在AVS流程中也会被AVS主控逻辑自动置位或清除。 */
        unsigned int  g3dg_hpmx_en  : 1;  /* bit[2-2] : G3D global HPMX使能。
                                                        HPM使能控制除了软件可以置位或清除，在AVS流程中也会被AVS主控逻辑自动置位或清除。 */
        unsigned int  reserved      : 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DHPMXEN_UNION;
#endif
#define SOC_PMCTRL_G3DHPMXEN_g3ds_hpmx0_en_START  (0)
#define SOC_PMCTRL_G3DHPMXEN_g3ds_hpmx0_en_END    (0)
#define SOC_PMCTRL_G3DHPMXEN_g3ds_hpmx1_en_START  (1)
#define SOC_PMCTRL_G3DHPMXEN_g3ds_hpmx1_en_END    (1)
#define SOC_PMCTRL_G3DHPMXEN_g3dg_hpmx_en_START   (2)
#define SOC_PMCTRL_G3DHPMXEN_g3dg_hpmx_en_END     (2)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DHPMOPCVALID_UNION
 结构说明  : G3DHPMOPCVALID 寄存器结构定义。地址偏移量:0x2A0，初值:0x00000000，宽度:32
 寄存器说明: G3D HPM OPC有效寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3ds_hpm0_opc_vld  : 1;  /* bit[0-0] : G3D HPM原始性能码有效的状态指示。 */
        unsigned int  g3ds_hpm1_opc_vld  : 1;  /* bit[1-1] : G3D HPM原始性能码有效的状态指示。 */
        unsigned int  g3dg_hpm_opc_vld   : 1;  /* bit[2-2] : G3D global HPM原始性能码有效的状态指示。 */
        unsigned int  g3ds_hpmx0_opc_vld : 1;  /* bit[3-3] : G3D HPMX原始性能码有效的状态指示。 */
        unsigned int  g3ds_hpmx1_opc_vld : 1;  /* bit[4-4] : G3D HPMX原始性能码有效的状态指示。 */
        unsigned int  g3dg_hpmx_opc_vld  : 1;  /* bit[5-5] : G3D global HPMX原始性能码有效的状态指示。 */
        unsigned int  reserved           : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DHPMOPCVALID_UNION;
#endif
#define SOC_PMCTRL_G3DHPMOPCVALID_g3ds_hpm0_opc_vld_START   (0)
#define SOC_PMCTRL_G3DHPMOPCVALID_g3ds_hpm0_opc_vld_END     (0)
#define SOC_PMCTRL_G3DHPMOPCVALID_g3ds_hpm1_opc_vld_START   (1)
#define SOC_PMCTRL_G3DHPMOPCVALID_g3ds_hpm1_opc_vld_END     (1)
#define SOC_PMCTRL_G3DHPMOPCVALID_g3dg_hpm_opc_vld_START    (2)
#define SOC_PMCTRL_G3DHPMOPCVALID_g3dg_hpm_opc_vld_END      (2)
#define SOC_PMCTRL_G3DHPMOPCVALID_g3ds_hpmx0_opc_vld_START  (3)
#define SOC_PMCTRL_G3DHPMOPCVALID_g3ds_hpmx0_opc_vld_END    (3)
#define SOC_PMCTRL_G3DHPMOPCVALID_g3ds_hpmx1_opc_vld_START  (4)
#define SOC_PMCTRL_G3DHPMOPCVALID_g3ds_hpmx1_opc_vld_END    (4)
#define SOC_PMCTRL_G3DHPMOPCVALID_g3dg_hpmx_opc_vld_START   (5)
#define SOC_PMCTRL_G3DHPMOPCVALID_g3dg_hpmx_opc_vld_END     (5)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DHPMOPC_UNION
 结构说明  : G3DHPMOPC 寄存器结构定义。地址偏移量:0x2A4，初值:0x00000000，宽度:32
 寄存器说明: G3D HPM OPC寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3ds_hpm0_opc : 10; /* bit[0-9]  : G3D HPM原始性能码。 */
        unsigned int  g3ds_hpm1_opc : 10; /* bit[10-19]: G3D HPM原始性能码。 */
        unsigned int  g3dg_hpm_opc  : 10; /* bit[20-29]: G3D global HPM原始性能码。 */
        unsigned int  reserved      : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DHPMOPC_UNION;
#endif
#define SOC_PMCTRL_G3DHPMOPC_g3ds_hpm0_opc_START  (0)
#define SOC_PMCTRL_G3DHPMOPC_g3ds_hpm0_opc_END    (9)
#define SOC_PMCTRL_G3DHPMOPC_g3ds_hpm1_opc_START  (10)
#define SOC_PMCTRL_G3DHPMOPC_g3ds_hpm1_opc_END    (19)
#define SOC_PMCTRL_G3DHPMOPC_g3dg_hpm_opc_START   (20)
#define SOC_PMCTRL_G3DHPMOPC_g3dg_hpm_opc_END     (29)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DHPMXOPC_UNION
 结构说明  : G3DHPMXOPC 寄存器结构定义。地址偏移量:0x2A8，初值:0x00000000，宽度:32
 寄存器说明: G3D HPMX OPC寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3ds_hpmx0_opc : 10; /* bit[0-9]  : G3D HPMX原始性能码。 */
        unsigned int  g3ds_hpmx1_opc : 10; /* bit[10-19]: G3D HPMX原始性能码。 */
        unsigned int  g3dg_hpmx_opc  : 10; /* bit[20-29]: G3D global HPMX原始性能码。 */
        unsigned int  reserved       : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DHPMXOPC_UNION;
#endif
#define SOC_PMCTRL_G3DHPMXOPC_g3ds_hpmx0_opc_START  (0)
#define SOC_PMCTRL_G3DHPMXOPC_g3ds_hpmx0_opc_END    (9)
#define SOC_PMCTRL_G3DHPMXOPC_g3ds_hpmx1_opc_START  (10)
#define SOC_PMCTRL_G3DHPMXOPC_g3ds_hpmx1_opc_END    (19)
#define SOC_PMCTRL_G3DHPMXOPC_g3dg_hpmx_opc_START   (20)
#define SOC_PMCTRL_G3DHPMXOPC_g3dg_hpmx_opc_END     (29)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DHPMPC_UNION
 结构说明  : G3DHPMPC 寄存器结构定义。地址偏移量:0x2AC，初值:0x00000000，宽度:32
 寄存器说明: G3D HPM PC寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3ds_hpm0_pc_avs : 10; /* bit[0-9]  : G3D HPM性能码。 */
        unsigned int  g3ds_hpm1_pc_avs : 10; /* bit[10-19]: G3D HPM性能码。 */
        unsigned int  g3dg_hpm_pc_avs  : 10; /* bit[20-29]: G3D global HPM性能码。 */
        unsigned int  reserved         : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DHPMPC_UNION;
#endif
#define SOC_PMCTRL_G3DHPMPC_g3ds_hpm0_pc_avs_START  (0)
#define SOC_PMCTRL_G3DHPMPC_g3ds_hpm0_pc_avs_END    (9)
#define SOC_PMCTRL_G3DHPMPC_g3ds_hpm1_pc_avs_START  (10)
#define SOC_PMCTRL_G3DHPMPC_g3ds_hpm1_pc_avs_END    (19)
#define SOC_PMCTRL_G3DHPMPC_g3dg_hpm_pc_avs_START   (20)
#define SOC_PMCTRL_G3DHPMPC_g3dg_hpm_pc_avs_END     (29)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DHPMEN1_UNION
 结构说明  : G3DHPMEN1 寄存器结构定义。地址偏移量:0x2B4，初值:0x00000000，宽度:32
 寄存器说明: G3D HPM使能寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3ds_hpm2_en : 1;  /* bit[0-0] : G3D HPM使能。
                                                       HPM使能控制除了软件可以置位或清除，在AVS流程中也会被AVS主控逻辑自动置位或清除。 */
        unsigned int  g3ds_hpm3_en : 1;  /* bit[1-1] : G3D HPM使能。
                                                       HPM使能控制除了软件可以置位或清除，在AVS流程中也会被AVS主控逻辑自动置位或清除。 */
        unsigned int  reserved     : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DHPMEN1_UNION;
#endif
#define SOC_PMCTRL_G3DHPMEN1_g3ds_hpm2_en_START  (0)
#define SOC_PMCTRL_G3DHPMEN1_g3ds_hpm2_en_END    (0)
#define SOC_PMCTRL_G3DHPMEN1_g3ds_hpm3_en_START  (1)
#define SOC_PMCTRL_G3DHPMEN1_g3ds_hpm3_en_END    (1)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DHPMXEN1_UNION
 结构说明  : G3DHPMXEN1 寄存器结构定义。地址偏移量:0x2B8，初值:0x00000000，宽度:32
 寄存器说明: G3D HPMX使能寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3ds_hpmx2_en : 1;  /* bit[0-0] : G3D HPMX使能。
                                                        HPMX使能控制除了软件可以置位或清除，在AVS流程中也会被AVS主控逻辑自动置位或清除。 */
        unsigned int  g3ds_hpmx3_en : 1;  /* bit[1-1] : G3D HPMX使能。
                                                        HPMX使能控制除了软件可以置位或清除，在AVS流程中也会被AVS主控逻辑自动置位或清除。 */
        unsigned int  reserved      : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DHPMXEN1_UNION;
#endif
#define SOC_PMCTRL_G3DHPMXEN1_g3ds_hpmx2_en_START  (0)
#define SOC_PMCTRL_G3DHPMXEN1_g3ds_hpmx2_en_END    (0)
#define SOC_PMCTRL_G3DHPMXEN1_g3ds_hpmx3_en_START  (1)
#define SOC_PMCTRL_G3DHPMXEN1_g3ds_hpmx3_en_END    (1)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DHPMOPCVALID1_UNION
 结构说明  : G3DHPMOPCVALID1 寄存器结构定义。地址偏移量:0x2BC，初值:0x00000000，宽度:32
 寄存器说明: G3D HPM OPC有效寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3ds_hpm2_opc_vld  : 1;  /* bit[0-0] : G3D HPM原始性能码有效的状态指示。 */
        unsigned int  g3ds_hpm3_opc_vld  : 1;  /* bit[1-1] : G3D HPM原始性能码有效的状态指示。 */
        unsigned int  g3ds_hpmx2_opc_vld : 1;  /* bit[2-2] : G3D HPMX原始性能码有效的状态指示。 */
        unsigned int  g3ds_hpmx3_opc_vld : 1;  /* bit[3-3] : G3D HPMX原始性能码有效的状态指示。 */
        unsigned int  reserved           : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DHPMOPCVALID1_UNION;
#endif
#define SOC_PMCTRL_G3DHPMOPCVALID1_g3ds_hpm2_opc_vld_START   (0)
#define SOC_PMCTRL_G3DHPMOPCVALID1_g3ds_hpm2_opc_vld_END     (0)
#define SOC_PMCTRL_G3DHPMOPCVALID1_g3ds_hpm3_opc_vld_START   (1)
#define SOC_PMCTRL_G3DHPMOPCVALID1_g3ds_hpm3_opc_vld_END     (1)
#define SOC_PMCTRL_G3DHPMOPCVALID1_g3ds_hpmx2_opc_vld_START  (2)
#define SOC_PMCTRL_G3DHPMOPCVALID1_g3ds_hpmx2_opc_vld_END    (2)
#define SOC_PMCTRL_G3DHPMOPCVALID1_g3ds_hpmx3_opc_vld_START  (3)
#define SOC_PMCTRL_G3DHPMOPCVALID1_g3ds_hpmx3_opc_vld_END    (3)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DHPMOPC1_UNION
 结构说明  : G3DHPMOPC1 寄存器结构定义。地址偏移量:0x2C0，初值:0x00000000，宽度:32
 寄存器说明: G3D HPM OPC寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3ds_hpm2_opc : 10; /* bit[0-9]  : G3D HPM原始性能码。 */
        unsigned int  g3ds_hpm3_opc : 10; /* bit[10-19]: G3D HPM原始性能码。 */
        unsigned int  reserved      : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DHPMOPC1_UNION;
#endif
#define SOC_PMCTRL_G3DHPMOPC1_g3ds_hpm2_opc_START  (0)
#define SOC_PMCTRL_G3DHPMOPC1_g3ds_hpm2_opc_END    (9)
#define SOC_PMCTRL_G3DHPMOPC1_g3ds_hpm3_opc_START  (10)
#define SOC_PMCTRL_G3DHPMOPC1_g3ds_hpm3_opc_END    (19)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DHPMXOPC1_UNION
 结构说明  : G3DHPMXOPC1 寄存器结构定义。地址偏移量:0x2C4，初值:0x00000000，宽度:32
 寄存器说明: G3D HPMX OPC寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3ds_hpmx2_opc : 10; /* bit[0-9]  : G3D HPMX原始性能码。 */
        unsigned int  g3ds_hpmx3_opc : 10; /* bit[10-19]: G3D HPMX原始性能码。 */
        unsigned int  reserved       : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DHPMXOPC1_UNION;
#endif
#define SOC_PMCTRL_G3DHPMXOPC1_g3ds_hpmx2_opc_START  (0)
#define SOC_PMCTRL_G3DHPMXOPC1_g3ds_hpmx2_opc_END    (9)
#define SOC_PMCTRL_G3DHPMXOPC1_g3ds_hpmx3_opc_START  (10)
#define SOC_PMCTRL_G3DHPMXOPC1_g3ds_hpmx3_opc_END    (19)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DHPMPC1_UNION
 结构说明  : G3DHPMPC1 寄存器结构定义。地址偏移量:0x2C8，初值:0x00000000，宽度:32
 寄存器说明: G3D HPM PC寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3ds_hpm2_pc_avs : 10; /* bit[0-9]  : G3D HPM性能码。 */
        unsigned int  g3ds_hpm3_pc_avs : 10; /* bit[10-19]: G3D HPM性能码。 */
        unsigned int  reserved         : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DHPMPC1_UNION;
#endif
#define SOC_PMCTRL_G3DHPMPC1_g3ds_hpm2_pc_avs_START  (0)
#define SOC_PMCTRL_G3DHPMPC1_g3ds_hpm2_pc_avs_END    (9)
#define SOC_PMCTRL_G3DHPMPC1_g3ds_hpm3_pc_avs_START  (10)
#define SOC_PMCTRL_G3DHPMPC1_g3ds_hpm3_pc_avs_END    (19)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DHPMMASKSTAT_UNION
 结构说明  : G3DHPMMASKSTAT 寄存器结构定义。地址偏移量:0x2E8，初值:0x00000000，宽度:32
 寄存器说明: G3D HPM屏蔽状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3ds_hpm0_mask_stat : 1;  /* bit[0-0] : G3D HPM0 屏蔽状态：
                                                              0：G3D HPM0没有被屏蔽；
                                                              1：G3D HPM0被屏蔽。 */
        unsigned int  g3ds_hpm1_mask_stat : 1;  /* bit[1-1] : G3D HPM1 屏蔽状态：
                                                              0：G3D HPM1没有被屏蔽；
                                                              1：G3D HPM1被屏蔽。 */
        unsigned int  g3ds_hpm2_mask_stat : 1;  /* bit[2-2] : G3D HPM2 屏蔽状态：
                                                              0：G3D HPM2没有被屏蔽；
                                                              1：G3D HPM2被屏蔽。 */
        unsigned int  g3ds_hpm3_mask_stat : 1;  /* bit[3-3] : G3D HPM3 屏蔽状态：
                                                              0：G3D HPM3没有被屏蔽；
                                                              1：G3D HPM3被屏蔽。 */
        unsigned int  g3dg_hpm_mask_stat  : 1;  /* bit[4-4] : G3D global HPM 屏蔽状态：
                                                              0：G3D global HPM没有被屏蔽；
                                                              1：G3D global HPM被屏蔽。 */
        unsigned int  reserved            : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DHPMMASKSTAT_UNION;
#endif
#define SOC_PMCTRL_G3DHPMMASKSTAT_g3ds_hpm0_mask_stat_START  (0)
#define SOC_PMCTRL_G3DHPMMASKSTAT_g3ds_hpm0_mask_stat_END    (0)
#define SOC_PMCTRL_G3DHPMMASKSTAT_g3ds_hpm1_mask_stat_START  (1)
#define SOC_PMCTRL_G3DHPMMASKSTAT_g3ds_hpm1_mask_stat_END    (1)
#define SOC_PMCTRL_G3DHPMMASKSTAT_g3ds_hpm2_mask_stat_START  (2)
#define SOC_PMCTRL_G3DHPMMASKSTAT_g3ds_hpm2_mask_stat_END    (2)
#define SOC_PMCTRL_G3DHPMMASKSTAT_g3ds_hpm3_mask_stat_START  (3)
#define SOC_PMCTRL_G3DHPMMASKSTAT_g3ds_hpm3_mask_stat_END    (3)
#define SOC_PMCTRL_G3DHPMMASKSTAT_g3dg_hpm_mask_stat_START   (4)
#define SOC_PMCTRL_G3DHPMMASKSTAT_g3dg_hpm_mask_stat_END     (4)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DHPMCLKDIV_UNION
 结构说明  : G3DHPMCLKDIV 寄存器结构定义。地址偏移量:0x2EC，初值:0x00000001，宽度:32
 寄存器说明: G3D HPM时钟分频寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_avs_hpm_div : 6;  /* bit[0-5] : G3D HPM时钟分频器。 */
        unsigned int  reserved        : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DHPMCLKDIV_UNION;
#endif
#define SOC_PMCTRL_G3DHPMCLKDIV_g3d_avs_hpm_div_START  (0)
#define SOC_PMCTRL_G3DHPMCLKDIV_g3d_avs_hpm_div_END    (5)


/*****************************************************************************
 结构名    : SOC_PMCTRL_G3DAVSVOLIDX_UNION
 结构说明  : G3DAVSVOLIDX 寄存器结构定义。地址偏移量:0x2F0，初值:0x00000000，宽度:32
 寄存器说明: G3D AVS电压控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_avs_vol_idx    : 8;  /* bit[0-7] : G3D AVS当前电压值。该值可以通过软件配置。如果配置该寄存器。时bit 8不写1，则需要软件配置该寄存器。值与PMU电压值相同 */
        unsigned int  g3d_vol_chg_sftreq : 1;  /* bit[8-8] : G3D电压改变软件请求信号。
                                                             写1：请求改变电压，电压值为bit 7:0值
                                                             写0：无效果 */
        unsigned int  reserved           : 23; /* bit[9-31]: 保留 */
    } reg;
} SOC_PMCTRL_G3DAVSVOLIDX_UNION;
#endif
#define SOC_PMCTRL_G3DAVSVOLIDX_g3d_avs_vol_idx_START     (0)
#define SOC_PMCTRL_G3DAVSVOLIDX_g3d_avs_vol_idx_END       (7)
#define SOC_PMCTRL_G3DAVSVOLIDX_g3d_vol_chg_sftreq_START  (8)
#define SOC_PMCTRL_G3DAVSVOLIDX_g3d_vol_chg_sftreq_END    (8)


/*****************************************************************************
 结构名    : SOC_PMCTRL_DDRLPCTRL_UNION
 结构说明  : DDRLPCTRL 寄存器结构定义。地址偏移量:0x30C，初值:0x000000F0，宽度:32
 寄存器说明: DDRC LP控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ddrc_a_csysreq : 1;  /* bit[0-0] : 请求DDRC A通道进入低功耗模式。
                                                         0：请求DDRC进入低功耗模式；
                                                         1：请求DDRC退出低功耗模式。 */
        unsigned int  ddrc_b_csysreq : 1;  /* bit[1-1] : 请求DDRC B通道进入低功耗模式。
                                                         0：请求DDRC进入低功耗模式；
                                                         1：请求DDRC退出低功耗模式。 */
        unsigned int  ddrc_c_csysreq : 1;  /* bit[2-2] : 请求DDRC C通道进入低功耗模式。
                                                         0：请求DDRC进入低功耗模式；
                                                         1：请求DDRC退出低功耗模式。 */
        unsigned int  ddrc_d_csysreq : 1;  /* bit[3-3] : 请求DDRC D通道进入低功耗模式。
                                                         0：请求DDRC进入低功耗模式；
                                                         1：请求DDRC退出低功耗模式。 */
        unsigned int  ddrc_a_csysack : 1;  /* bit[4-4] : DDRC A通道对于请求的响应。
                                                         0：对于请求DDRC进入低功耗模式的响应；
                                                         1：对于请求DDRC退出低功耗模式的响应。 */
        unsigned int  ddrc_b_csysack : 1;  /* bit[5-5] : DDRC B通道进入低功耗模式的状态指示。
                                                         0：DDRC进入低功耗模式；
                                                         1：DDRC退出低功耗模式。 */
        unsigned int  ddrc_c_csysack : 1;  /* bit[6-6] : DDRC C通道对于请求的响应。
                                                         0：对于请求DDRC进入低功耗模式的响应；
                                                         1：对于请求DDRC退出低功耗模式的响应。 */
        unsigned int  ddrc_d_csysack : 1;  /* bit[7-7] : DDRC D通道进入低功耗模式的状态指示。
                                                         0：DDRC进入低功耗模式；
                                                         1：DDRC退出低功耗模式。 */
        unsigned int  reserved       : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_PMCTRL_DDRLPCTRL_UNION;
#endif
#define SOC_PMCTRL_DDRLPCTRL_ddrc_a_csysreq_START  (0)
#define SOC_PMCTRL_DDRLPCTRL_ddrc_a_csysreq_END    (0)
#define SOC_PMCTRL_DDRLPCTRL_ddrc_b_csysreq_START  (1)
#define SOC_PMCTRL_DDRLPCTRL_ddrc_b_csysreq_END    (1)
#define SOC_PMCTRL_DDRLPCTRL_ddrc_c_csysreq_START  (2)
#define SOC_PMCTRL_DDRLPCTRL_ddrc_c_csysreq_END    (2)
#define SOC_PMCTRL_DDRLPCTRL_ddrc_d_csysreq_START  (3)
#define SOC_PMCTRL_DDRLPCTRL_ddrc_d_csysreq_END    (3)
#define SOC_PMCTRL_DDRLPCTRL_ddrc_a_csysack_START  (4)
#define SOC_PMCTRL_DDRLPCTRL_ddrc_a_csysack_END    (4)
#define SOC_PMCTRL_DDRLPCTRL_ddrc_b_csysack_START  (5)
#define SOC_PMCTRL_DDRLPCTRL_ddrc_b_csysack_END    (5)
#define SOC_PMCTRL_DDRLPCTRL_ddrc_c_csysack_START  (6)
#define SOC_PMCTRL_DDRLPCTRL_ddrc_c_csysack_END    (6)
#define SOC_PMCTRL_DDRLPCTRL_ddrc_d_csysack_START  (7)
#define SOC_PMCTRL_DDRLPCTRL_ddrc_d_csysack_END    (7)


/*****************************************************************************
 结构名    : SOC_PMCTRL_PLLLOCKTIME_UNION
 结构说明  : PLLLOCKTIME 寄存器结构定义。地址偏移量:0x320，初值:0x000FFAEB，宽度:32
 寄存器说明: PLL Lock稳定时间寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pll_lock_time : 20; /* bit[0-19] : PLL Lock稳定时间。 */
        unsigned int  reserved      : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_PMCTRL_PLLLOCKTIME_UNION;
#endif
#define SOC_PMCTRL_PLLLOCKTIME_pll_lock_time_START  (0)
#define SOC_PMCTRL_PLLLOCKTIME_pll_lock_time_END    (19)


/*****************************************************************************
 结构名    : SOC_PMCTRL_PLLLOCKMOD_UNION
 结构说明  : PLLLOCKMOD 寄存器结构定义。地址偏移量:0x324，初值:0x00000001，宽度:32
 寄存器说明: PLL稳定模式寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pll_lock_mod : 1;  /* bit[0-0] : PLL 稳定模式。
                                                       0：使用PLL的Lock标志来表示PLL的稳定；
                                                       1：使用PLL的稳定超时来表示PLL的稳定。 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_PMCTRL_PLLLOCKMOD_UNION;
#endif
#define SOC_PMCTRL_PLLLOCKMOD_pll_lock_mod_START  (0)
#define SOC_PMCTRL_PLLLOCKMOD_pll_lock_mod_END    (0)


/*****************************************************************************
 结构名    : SOC_PMCTRL_AVSRUNROUND_UNION
 结构说明  : AVSRUNROUND 寄存器结构定义。地址偏移量:0x32C，初值:0x00000000，宽度:32
 寄存器说明: AVS运行轮数寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cpu_avs_round : 8;  /* bit[0-7]  : A53_ AVS运行轮数。
                                                             A53_ AVS每运行一轮，则计数加1。
                                                             当A53_ AVS电压OK中断有效时，计数维持不变，以便软件读取。
                                                             当A53_ AVS电压OK中断清除时，计数清0，重新开始。 */
        unsigned int  a57_cpu_avs_round : 8;  /* bit[8-15] : A57_ AVS运行轮数。
                                                             A57_ AVS每运行一轮，则计数加1。
                                                             当A57_ AVS电压OK中断有效时，计数维持不变，以便软件读取。
                                                             当A57_ AVS电压OK中断清除时，计数清0，重新开始。 */
        unsigned int  g3d_avs_round     : 8;  /* bit[16-23]: G3D Core AVS运行轮数。
                                                             G3D Core AVS每运行一轮，则计数加1。
                                                             当G3D Core AVS电压OK中断有效时，计数维持不变，以便软件读取。
                                                             当G3D Core AVS电压OK中断清除时，计数清0，重新开始。 */
        unsigned int  reserved          : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_PMCTRL_AVSRUNROUND_UNION;
#endif
#define SOC_PMCTRL_AVSRUNROUND_a53_cpu_avs_round_START  (0)
#define SOC_PMCTRL_AVSRUNROUND_a53_cpu_avs_round_END    (7)
#define SOC_PMCTRL_AVSRUNROUND_a57_cpu_avs_round_START  (8)
#define SOC_PMCTRL_AVSRUNROUND_a57_cpu_avs_round_END    (15)
#define SOC_PMCTRL_AVSRUNROUND_g3d_avs_round_START      (16)
#define SOC_PMCTRL_AVSRUNROUND_g3d_avs_round_END        (23)


/*****************************************************************************
 结构名    : SOC_PMCTRL_PMUSSIAVSEN_UNION
 结构说明  : PMUSSIAVSEN 寄存器结构定义。地址偏移量:0x330，初值:0x00000000，宽度:32
 寄存器说明: PMUSSI AVS使能信号寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  avs_en_ssi : 1;  /* bit[0-0] : PMUSSI AVS使能信号，当该信号为1'b1时，PMUSSI接收PMC的调压操作，将其转换为SSI时序信号给PMU。
                                                     软件配置该信号的顺序为：当需要硬件调压（DVFS或AVS）之前，将该信号配置有效；当不需要硬件调压或软件需要配置PMU时，等待当前调压操作结束，再将该信号配置无效。 */
        unsigned int  reserved   : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_PMCTRL_PMUSSIAVSEN_UNION;
#endif
#define SOC_PMCTRL_PMUSSIAVSEN_avs_en_ssi_START  (0)
#define SOC_PMCTRL_PMUSSIAVSEN_avs_en_ssi_END    (0)


/*****************************************************************************
 结构名    : SOC_PMCTRL_PERI_CTRL0_UNION
 结构说明  : PERI_CTRL0 寄存器结构定义。地址偏移量:0x340，初值:0x00000000，宽度:32
 寄存器说明: 外设通用控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_ctrl_ddrc  : 1;  /* bit[0-0] : debug控制信号 */
        unsigned int  dbg_ctrl_cssys : 1;  /* bit[1-1] : debug控制信号 */
        unsigned int  dbg_ctrl_ssi   : 1;  /* bit[2-2] : debug控制信号 */
        unsigned int  dbg_ctrl_i2c   : 1;  /* bit[3-3] : debug控制信号 */
        unsigned int  dbg_ctrl_ssi1  : 1;  /* bit[4-4] : debug控制信号 */
        unsigned int  reserved       : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_PMCTRL_PERI_CTRL0_UNION;
#endif
#define SOC_PMCTRL_PERI_CTRL0_dbg_ctrl_ddrc_START   (0)
#define SOC_PMCTRL_PERI_CTRL0_dbg_ctrl_ddrc_END     (0)
#define SOC_PMCTRL_PERI_CTRL0_dbg_ctrl_cssys_START  (1)
#define SOC_PMCTRL_PERI_CTRL0_dbg_ctrl_cssys_END    (1)
#define SOC_PMCTRL_PERI_CTRL0_dbg_ctrl_ssi_START    (2)
#define SOC_PMCTRL_PERI_CTRL0_dbg_ctrl_ssi_END      (2)
#define SOC_PMCTRL_PERI_CTRL0_dbg_ctrl_i2c_START    (3)
#define SOC_PMCTRL_PERI_CTRL0_dbg_ctrl_i2c_END      (3)
#define SOC_PMCTRL_PERI_CTRL0_dbg_ctrl_ssi1_START   (4)
#define SOC_PMCTRL_PERI_CTRL0_dbg_ctrl_ssi1_END     (4)


/*****************************************************************************
 结构名    : SOC_PMCTRL_PERI_CTRL1_UNION
 结构说明  : PERI_CTRL1 寄存器结构定义。地址偏移量:0x344，初值:0x00000000，宽度:32
 寄存器说明: 外设通用控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 保留 */
    } reg;
} SOC_PMCTRL_PERI_CTRL1_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_PMCTRL_PERI_CTRL2_UNION
 结构说明  : PERI_CTRL2 寄存器结构定义。地址偏移量:0x348，初值:0x00000000，宽度:32
 寄存器说明: 外设通用控制寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pmu_vol_addr0 : 10; /* bit[0-9]  : PMUSSI配置地址，对应A53_调相操作 */
        unsigned int  reserved_0    : 6;  /* bit[10-15]: 保留 */
        unsigned int  pmu_vol_addr1 : 10; /* bit[16-25]: PMUSSI配置地址，对应A53_调压操作 */
        unsigned int  reserved_1    : 6;  /* bit[26-31]: 保留 */
    } reg;
} SOC_PMCTRL_PERI_CTRL2_UNION;
#endif
#define SOC_PMCTRL_PERI_CTRL2_pmu_vol_addr0_START  (0)
#define SOC_PMCTRL_PERI_CTRL2_pmu_vol_addr0_END    (9)
#define SOC_PMCTRL_PERI_CTRL2_pmu_vol_addr1_START  (16)
#define SOC_PMCTRL_PERI_CTRL2_pmu_vol_addr1_END    (25)


/*****************************************************************************
 结构名    : SOC_PMCTRL_PERI_CTRL3_UNION
 结构说明  : PERI_CTRL3 寄存器结构定义。地址偏移量:0x34C，初值:0x00000000，宽度:32
 寄存器说明: 外设通用控制寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pmu_vol_addr2 : 10; /* bit[0-9]  : PMUSSI配置地址，对应G3D调相操作 */
        unsigned int  reserved_0    : 6;  /* bit[10-15]: 保留 */
        unsigned int  pmu_vol_addr3 : 10; /* bit[16-25]: PMUSSI配置地址，对应G3D调压操作 */
        unsigned int  reserved_1    : 6;  /* bit[26-31]: 保留 */
    } reg;
} SOC_PMCTRL_PERI_CTRL3_UNION;
#endif
#define SOC_PMCTRL_PERI_CTRL3_pmu_vol_addr2_START  (0)
#define SOC_PMCTRL_PERI_CTRL3_pmu_vol_addr2_END    (9)
#define SOC_PMCTRL_PERI_CTRL3_pmu_vol_addr3_START  (16)
#define SOC_PMCTRL_PERI_CTRL3_pmu_vol_addr3_END    (25)


/*****************************************************************************
 结构名    : SOC_PMCTRL_PERI_CTRL4_UNION
 结构说明  : PERI_CTRL4 寄存器结构定义。地址偏移量:0x350，初值:0x00000000，宽度:32
 寄存器说明: 外设通用控制寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 16; /* bit[0-15] : 保留 */
        unsigned int  reserved_1: 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_PMCTRL_PERI_CTRL4_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_PMCTRL_PERI_CTRL5_UNION
 结构说明  : PERI_CTRL5 寄存器结构定义。地址偏移量:0x354，初值:0x00000000，宽度:32
 寄存器说明: 外设通用控制寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 保留 */
    } reg;
} SOC_PMCTRL_PERI_CTRL5_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_PMCTRL_PERI_CTRL6_UNION
 结构说明  : PERI_CTRL6 寄存器结构定义。地址偏移量:0x358，初值:0x00000000，宽度:32
 寄存器说明: 外设通用控制寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 保留 */
    } reg;
} SOC_PMCTRL_PERI_CTRL6_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_PMCTRL_PERI_CTRL7_UNION
 结构说明  : PERI_CTRL7 寄存器结构定义。地址偏移量:0x35C，初值:0x00000000，宽度:32
 寄存器说明: 外设通用控制寄存器7。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 保留 */
    } reg;
} SOC_PMCTRL_PERI_CTRL7_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_PMCTRL_PERI_STAT0_UNION
 结构说明  : PERI_STAT0 寄存器结构定义。地址偏移量:0x360，初值:0x00000000，宽度:32
 寄存器说明: 外设通用状态寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_info_ddrc : 32; /* bit[0-31]: debug状态 */
    } reg;
} SOC_PMCTRL_PERI_STAT0_UNION;
#endif
#define SOC_PMCTRL_PERI_STAT0_dbg_info_ddrc_START  (0)
#define SOC_PMCTRL_PERI_STAT0_dbg_info_ddrc_END    (31)


/*****************************************************************************
 结构名    : SOC_PMCTRL_PERI_STAT1_UNION
 结构说明  : PERI_STAT1 寄存器结构定义。地址偏移量:0x364，初值:0x00000000，宽度:32
 寄存器说明: 外设通用状态寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_info_cssys : 32; /* bit[0-31]: debug状态 */
    } reg;
} SOC_PMCTRL_PERI_STAT1_UNION;
#endif
#define SOC_PMCTRL_PERI_STAT1_dbg_info_cssys_START  (0)
#define SOC_PMCTRL_PERI_STAT1_dbg_info_cssys_END    (31)


/*****************************************************************************
 结构名    : SOC_PMCTRL_PERI_STAT2_UNION
 结构说明  : PERI_STAT2 寄存器结构定义。地址偏移量:0x368，初值:0x00000000，宽度:32
 寄存器说明: 外设通用状态寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_info_ssi : 32; /* bit[0-31]: debug状态 */
    } reg;
} SOC_PMCTRL_PERI_STAT2_UNION;
#endif
#define SOC_PMCTRL_PERI_STAT2_dbg_info_ssi_START  (0)
#define SOC_PMCTRL_PERI_STAT2_dbg_info_ssi_END    (31)


/*****************************************************************************
 结构名    : SOC_PMCTRL_PERI_STAT3_UNION
 结构说明  : PERI_STAT3 寄存器结构定义。地址偏移量:0x36C，初值:0x00000000，宽度:32
 寄存器说明: 外设通用状态寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_info_i2c : 32; /* bit[0-31]: debug状态 */
    } reg;
} SOC_PMCTRL_PERI_STAT3_UNION;
#endif
#define SOC_PMCTRL_PERI_STAT3_dbg_info_i2c_START  (0)
#define SOC_PMCTRL_PERI_STAT3_dbg_info_i2c_END    (31)


/*****************************************************************************
 结构名    : SOC_PMCTRL_PERI_STAT4_UNION
 结构说明  : PERI_STAT4 寄存器结构定义。地址偏移量:0x370，初值:0x00000000，宽度:32
 寄存器说明: 外设通用状态寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_info_ssi1 : 32; /* bit[0-31]: debug状态 */
    } reg;
} SOC_PMCTRL_PERI_STAT4_UNION;
#endif
#define SOC_PMCTRL_PERI_STAT4_dbg_info_ssi1_START  (0)
#define SOC_PMCTRL_PERI_STAT4_dbg_info_ssi1_END    (31)


/*****************************************************************************
 结构名    : SOC_PMCTRL_PERI_STAT5_UNION
 结构说明  : PERI_STAT5 寄存器结构定义。地址偏移量:0x374，初值:0x00000000，宽度:32
 寄存器说明: 外设通用状态寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  svfd_test_out_0     : 4;  /* bit[0-3]  : 预留测试输出 */
        unsigned int  svfd_test_out_1     : 4;  /* bit[4-7]  : 预留测试输出 */
        unsigned int  svfd_test_out_2     : 4;  /* bit[8-11] : 预留测试输出 */
        unsigned int  svfd_match_result_0 : 1;  /* bit[12-12]: 匹配检测结果，1为通过，用于DFT量产筛选 */
        unsigned int  svfd_match_result_1 : 1;  /* bit[13-13]: 匹配检测结果，1为通过，用于DFT量产筛选 */
        unsigned int  svfd_match_result_2 : 1;  /* bit[14-14]: 匹配检测结果，1为通过，用于DFT量产筛选 */
        unsigned int  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} SOC_PMCTRL_PERI_STAT5_UNION;
#endif
#define SOC_PMCTRL_PERI_STAT5_svfd_test_out_0_START      (0)
#define SOC_PMCTRL_PERI_STAT5_svfd_test_out_0_END        (3)
#define SOC_PMCTRL_PERI_STAT5_svfd_test_out_1_START      (4)
#define SOC_PMCTRL_PERI_STAT5_svfd_test_out_1_END        (7)
#define SOC_PMCTRL_PERI_STAT5_svfd_test_out_2_START      (8)
#define SOC_PMCTRL_PERI_STAT5_svfd_test_out_2_END        (11)
#define SOC_PMCTRL_PERI_STAT5_svfd_match_result_0_START  (12)
#define SOC_PMCTRL_PERI_STAT5_svfd_match_result_0_END    (12)
#define SOC_PMCTRL_PERI_STAT5_svfd_match_result_1_START  (13)
#define SOC_PMCTRL_PERI_STAT5_svfd_match_result_1_END    (13)
#define SOC_PMCTRL_PERI_STAT5_svfd_match_result_2_START  (14)
#define SOC_PMCTRL_PERI_STAT5_svfd_match_result_2_END    (14)


/*****************************************************************************
 结构名    : SOC_PMCTRL_PERI_STAT6_UNION
 结构说明  : PERI_STAT6 寄存器结构定义。地址偏移量:0x378，初值:0x00000000，宽度:32
 寄存器说明: 外设通用状态寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cpm_data  : 16; /* bit[0-15] : A53的cpm 码字 */
        unsigned int  maia_cpm_data : 16; /* bit[16-31]: MAIA的cpm 码字 */
    } reg;
} SOC_PMCTRL_PERI_STAT6_UNION;
#endif
#define SOC_PMCTRL_PERI_STAT6_a53_cpm_data_START   (0)
#define SOC_PMCTRL_PERI_STAT6_a53_cpm_data_END     (15)
#define SOC_PMCTRL_PERI_STAT6_maia_cpm_data_START  (16)
#define SOC_PMCTRL_PERI_STAT6_maia_cpm_data_END    (31)


/*****************************************************************************
 结构名    : SOC_PMCTRL_PERI_STAT7_UNION
 结构说明  : PERI_STAT7 寄存器结构定义。地址偏移量:0x37C，初值:0x00000000，宽度:32
 寄存器说明: 外设通用状态寄存器7。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  maia_cpm_data_vld       : 1;  /* bit[0-0]  : MAIA cpm码字的VLD信号； */
        unsigned int  a53_cpm_data_vld        : 1;  /* bit[1-1]  : A53 cpm码字的VLD信号； */
        unsigned int  g3d_cpm_data_vld        : 1;  /* bit[2-2]  : GPU cpm码字的VLD信号； */
        unsigned int  reserved_0              : 1;  /* bit[3-3]  : 保留 */
        unsigned int  maia_svfd_glitch_result : 1;  /* bit[4-4]  : MAIA svfd glitch检测结果； */
        unsigned int  a53_svfd_glitch_result  : 1;  /* bit[5-5]  : A53 svfd glitch检测结果； */
        unsigned int  g3d_svfd_glitch_result  : 1;  /* bit[6-6]  : GPU svfd glitch检测结果； */
        unsigned int  reserved_1              : 9;  /* bit[7-15] : 保留 */
        unsigned int  g3d_cpm_data            : 16; /* bit[16-31]: GPU的cpm 码字 */
    } reg;
} SOC_PMCTRL_PERI_STAT7_UNION;
#endif
#define SOC_PMCTRL_PERI_STAT7_maia_cpm_data_vld_START        (0)
#define SOC_PMCTRL_PERI_STAT7_maia_cpm_data_vld_END          (0)
#define SOC_PMCTRL_PERI_STAT7_a53_cpm_data_vld_START         (1)
#define SOC_PMCTRL_PERI_STAT7_a53_cpm_data_vld_END           (1)
#define SOC_PMCTRL_PERI_STAT7_g3d_cpm_data_vld_START         (2)
#define SOC_PMCTRL_PERI_STAT7_g3d_cpm_data_vld_END           (2)
#define SOC_PMCTRL_PERI_STAT7_maia_svfd_glitch_result_START  (4)
#define SOC_PMCTRL_PERI_STAT7_maia_svfd_glitch_result_END    (4)
#define SOC_PMCTRL_PERI_STAT7_a53_svfd_glitch_result_START   (5)
#define SOC_PMCTRL_PERI_STAT7_a53_svfd_glitch_result_END     (5)
#define SOC_PMCTRL_PERI_STAT7_g3d_svfd_glitch_result_START   (6)
#define SOC_PMCTRL_PERI_STAT7_g3d_svfd_glitch_result_END     (6)
#define SOC_PMCTRL_PERI_STAT7_g3d_cpm_data_START             (16)
#define SOC_PMCTRL_PERI_STAT7_g3d_cpm_data_END               (31)


/*****************************************************************************
 结构名    : SOC_PMCTRL_NOC_POWER_IDLEREQ_UNION
 结构说明  : NOC_POWER_IDLEREQ 寄存器结构定义。地址偏移量:0x380，初值:0x00006C38，宽度:32
 寄存器说明: NOC低功耗请求信号寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ddrphy_bypass_mode               : 1;  /* bit[0-0]  : DDRPHY工作模式
                                                                            0：非bypass模式；
                                                                            1：bypass模式； */
        unsigned int  noc_mmc0bus_power_idlereq        : 1;  /* bit[1-1]  : noc低功耗请求信号
                                                                            0：请求noc退出低功耗模式；
                                                                            1：请求noc进入低功耗模式。 */
        unsigned int  noc_mmc1bus_power_idlereq        : 1;  /* bit[2-2]  : noc低功耗请求信号
                                                                            0：请求noc退出低功耗模式；
                                                                            1：请求noc进入低功耗模式。 */
        unsigned int  noc_modem_power_idlereq          : 1;  /* bit[3-3]  : noc低功耗请求信号
                                                                            0：请求noc退出低功耗模式；
                                                                            1：请求noc进入低功耗模式。 */
        unsigned int  noc_vcodec_power_idlereq         : 1;  /* bit[4-4]  : noc低功耗请求信号
                                                                            0：请求noc退出低功耗模式；
                                                                            1：请求noc进入低功耗模式。 */
        unsigned int  noc_isp_power_idlereq            : 1;  /* bit[5-5]  : noc低功耗请求信号
                                                                            0：请求noc退出低功耗模式；
                                                                            1：请求noc进入低功耗模式。 */
        unsigned int  noc_sysbus_power_idlereq         : 1;  /* bit[6-6]  : noc低功耗请求信号
                                                                            0：请求noc退出低功耗模式；
                                                                            1：请求noc进入低功耗模式。 */
        unsigned int  noc_cfgbus_power_idlereq         : 1;  /* bit[7-7]  : noc低功耗请求信号
                                                                            0：请求noc退出低功耗模式；
                                                                            1：请求noc进入低功耗模式。 */
        unsigned int  noc_dmabus_power_idlereq         : 1;  /* bit[8-8]  : noc低功耗请求信号
                                                                            0：请求noc退出低功耗模式；
                                                                            1：请求noc进入低功耗模式。 */
        unsigned int  noc_dbgbus_power_idlereq         : 1;  /* bit[9-9]  : noc低功耗请求信号
                                                                            0：请求noc退出低功耗模式；
                                                                            1：请求noc进入低功耗模式。 */
        unsigned int  noc_vdec_power_idlereq           : 1;  /* bit[10-10]: noc低功耗请求信号
                                                                            0：请求noc退出低功耗模式；
                                                                            1：请求noc进入低功耗模式。 */
        unsigned int  noc_venc_power_idlereq           : 1;  /* bit[11-11]: noc低功耗请求信号
                                                                            0：请求noc退出低功耗模式；
                                                                            1：请求noc进入低功耗模式。 */
        unsigned int  reserved_0                       : 1;  /* bit[12-12]: reserved */
        unsigned int  noc_dss_power_idlereq            : 1;  /* bit[13-13]: noc低功耗请求信号
                                                                            0：请求noc退出低功耗模式；
                                                                            1：请求noc进入低功耗模式。 */
        unsigned int  noc_ivp32_peri_bus_power_idlereq : 1;  /* bit[14-14]: noc低功耗请求信号
                                                                            0：请求noc退出低功耗模式；
                                                                            1：请求noc进入低功耗模式。 */
        unsigned int  reserved_1                       : 1;  /* bit[15-15]: reserved */
        unsigned int  biten                            : 16; /* bit[16-31]: 每个比特位的使能位：
                                                                            只有当biten对应的比特位为1'b1，相应的比特位才起作用。biten[0]就是bit 0的使能位。写1有效。 */
    } reg;
} SOC_PMCTRL_NOC_POWER_IDLEREQ_UNION;
#endif
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_ddrphy_bypass_mode_START                (0)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_ddrphy_bypass_mode_END                  (0)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_mmc0bus_power_idlereq_START         (1)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_mmc0bus_power_idlereq_END           (1)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_mmc1bus_power_idlereq_START         (2)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_mmc1bus_power_idlereq_END           (2)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_modem_power_idlereq_START           (3)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_modem_power_idlereq_END             (3)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_vcodec_power_idlereq_START          (4)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_vcodec_power_idlereq_END            (4)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_isp_power_idlereq_START             (5)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_isp_power_idlereq_END               (5)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_sysbus_power_idlereq_START          (6)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_sysbus_power_idlereq_END            (6)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_cfgbus_power_idlereq_START          (7)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_cfgbus_power_idlereq_END            (7)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_dmabus_power_idlereq_START          (8)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_dmabus_power_idlereq_END            (8)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_dbgbus_power_idlereq_START          (9)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_dbgbus_power_idlereq_END            (9)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_vdec_power_idlereq_START            (10)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_vdec_power_idlereq_END              (10)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_venc_power_idlereq_START            (11)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_venc_power_idlereq_END              (11)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_dss_power_idlereq_START             (13)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_dss_power_idlereq_END               (13)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_ivp32_peri_bus_power_idlereq_START  (14)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_ivp32_peri_bus_power_idlereq_END    (14)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_biten_START                             (16)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_biten_END                               (31)


/*****************************************************************************
 结构名    : SOC_PMCTRL_NOC_POWER_IDLEACK_UNION
 结构说明  : NOC_POWER_IDLEACK 寄存器结构定义。地址偏移量:0x384，初值:0x00000000，宽度:32
 寄存器说明: NOC低功耗响应寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                       : 1;  /* bit[0-0]  : reserved */
        unsigned int  noc_mmc0bus_power_idleack        : 1;  /* bit[1-1]  : noc对于低功耗请求的响应。
                                                                            0：对于请求noc退出低功耗模式的响应；
                                                                            1：对于请求noc进入低功耗模式的响应。 */
        unsigned int  noc_mmc1bus_power_idleack        : 1;  /* bit[2-2]  : noc对于低功耗请求的响应。
                                                                            0：对于请求noc退出低功耗模式的响应；
                                                                            1：对于请求noc进入低功耗模式的响应。 */
        unsigned int  noc_modem_power_idleack          : 1;  /* bit[3-3]  : noc对于低功耗请求的响应。
                                                                            0：对于请求noc退出低功耗模式的响应；
                                                                            1：对于请求noc进入低功耗模式的响应。 */
        unsigned int  noc_vcodec_power_idleack         : 1;  /* bit[4-4]  : noc对于低功耗请求的响应。
                                                                            0：对于请求noc退出低功耗模式的响应；
                                                                            1：对于请求noc进入低功耗模式的响应。 */
        unsigned int  noc_isp_power_idleack            : 1;  /* bit[5-5]  : noc对于低功耗请求的响应。
                                                                            0：对于请求noc退出低功耗模式的响应；
                                                                            1：对于请求noc进入低功耗模式的响应。 */
        unsigned int  noc_sysbus_power_idleack         : 1;  /* bit[6-6]  : noc对于低功耗请求的响应。
                                                                            0：对于请求noc退出低功耗模式的响应；
                                                                            1：对于请求noc进入低功耗模式的响应。 */
        unsigned int  noc_cfgbus_power_idleack         : 1;  /* bit[7-7]  : noc对于低功耗请求的响应。
                                                                            0：对于请求noc退出低功耗模式的响应；
                                                                            1：对于请求noc进入低功耗模式的响应。 */
        unsigned int  noc_dmabus_power_idleack         : 1;  /* bit[8-8]  : noc对于低功耗请求的响应。
                                                                            0：对于请求noc退出低功耗模式的响应；
                                                                            1：对于请求noc进入低功耗模式的响应。 */
        unsigned int  noc_dbgbus_power_idleack         : 1;  /* bit[9-9]  : noc对于低功耗请求的响应。
                                                                            0：对于请求noc退出低功耗模式的响应；
                                                                            1：对于请求noc进入低功耗模式的响应。 */
        unsigned int  noc_vdec_power_idleack           : 1;  /* bit[10-10]: noc对于低功耗请求的响应。
                                                                            0：对于请求noc退出低功耗模式的响应；
                                                                            1：对于请求noc进入低功耗模式的响应。 */
        unsigned int  noc_venc_power_idleack           : 1;  /* bit[11-11]: noc对于低功耗请求的响应。
                                                                            0：对于请求noc退出低功耗模式的响应；
                                                                            1：对于请求noc进入低功耗模式的响应。 */
        unsigned int  reserved_1                       : 1;  /* bit[12-12]: reserved */
        unsigned int  noc_dss_power_idleack            : 1;  /* bit[13-13]: noc对于低功耗请求的响应。
                                                                            0：对于请求noc退出低功耗模式的响应；
                                                                            1：对于请求noc进入低功耗模式的响应。 */
        unsigned int  noc_ivp32_peri_bus_power_idleack : 1;  /* bit[14-14]: noc对于低功耗请求的响应。
                                                                            0：对于请求noc退出低功耗模式的响应；
                                                                            1：对于请求noc进入低功耗模式的响应。 */
        unsigned int  reserved_2                       : 17; /* bit[15-31]: 保留 */
    } reg;
} SOC_PMCTRL_NOC_POWER_IDLEACK_UNION;
#endif
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_mmc0bus_power_idleack_START         (1)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_mmc0bus_power_idleack_END           (1)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_mmc1bus_power_idleack_START         (2)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_mmc1bus_power_idleack_END           (2)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_modem_power_idleack_START           (3)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_modem_power_idleack_END             (3)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_vcodec_power_idleack_START          (4)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_vcodec_power_idleack_END            (4)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_isp_power_idleack_START             (5)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_isp_power_idleack_END               (5)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_sysbus_power_idleack_START          (6)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_sysbus_power_idleack_END            (6)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_cfgbus_power_idleack_START          (7)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_cfgbus_power_idleack_END            (7)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_dmabus_power_idleack_START          (8)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_dmabus_power_idleack_END            (8)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_dbgbus_power_idleack_START          (9)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_dbgbus_power_idleack_END            (9)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_vdec_power_idleack_START            (10)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_vdec_power_idleack_END              (10)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_venc_power_idleack_START            (11)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_venc_power_idleack_END              (11)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_dss_power_idleack_START             (13)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_dss_power_idleack_END               (13)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_ivp32_peri_bus_power_idleack_START  (14)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_ivp32_peri_bus_power_idleack_END    (14)


/*****************************************************************************
 结构名    : SOC_PMCTRL_NOC_POWER_IDLE_UNION
 结构说明  : NOC_POWER_IDLE 寄存器结构定义。地址偏移量:0x388，初值:0x00000000，宽度:32
 寄存器说明: NOC低功耗状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                    : 1;  /* bit[0-0]  : reserved */
        unsigned int  noc_mmc0bus_power_idle        : 1;  /* bit[1-1]  : noc进入低功耗模式的状态指示。
                                                                         0：对于请求noc退出低功耗模式的状态指示；
                                                                         1：对于请求noc进入低功耗模式的状态指示。 */
        unsigned int  noc_mmc1bus_power_idle        : 1;  /* bit[2-2]  : noc进入低功耗模式的状态指示。
                                                                         0：对于请求noc退出低功耗模式的状态指示；
                                                                         1：对于请求noc进入低功耗模式的状态指示。 */
        unsigned int  noc_modem_power_idle          : 1;  /* bit[3-3]  : noc进入低功耗模式的状态指示。
                                                                         0：对于请求noc退出低功耗模式的状态指示；
                                                                         1：对于请求noc进入低功耗模式的状态指示。 */
        unsigned int  noc_vcodec_power_idle         : 1;  /* bit[4-4]  : noc进入低功耗模式的状态指示。
                                                                         0：对于请求noc退出低功耗模式的状态指示；
                                                                         1：对于请求noc进入低功耗模式的状态指示。 */
        unsigned int  noc_isp_power_idle            : 1;  /* bit[5-5]  : noc进入低功耗模式的状态指示。
                                                                         0：对于请求noc退出低功耗模式的状态指示；
                                                                         1：对于请求noc进入低功耗模式的状态指示。 */
        unsigned int  noc_sysbus_power_idle         : 1;  /* bit[6-6]  : noc进入低功耗模式的状态指示。
                                                                         0：对于请求noc退出低功耗模式的状态指示；
                                                                         1：对于请求noc进入低功耗模式的状态指示。 */
        unsigned int  noc_cfgbus_power_idle         : 1;  /* bit[7-7]  : noc进入低功耗模式的状态指示。
                                                                         0：对于请求noc退出低功耗模式的状态指示；
                                                                         1：对于请求noc进入低功耗模式的状态指示。 */
        unsigned int  noc_dmabus_power_idle         : 1;  /* bit[8-8]  : noc进入低功耗模式的状态指示。
                                                                         0：对于请求noc退出低功耗模式的状态指示；
                                                                         1：对于请求noc进入低功耗模式的状态指示。 */
        unsigned int  noc_dbgbus_power_idle         : 1;  /* bit[9-9]  : noc进入低功耗模式的状态指示。
                                                                         0：对于请求noc退出低功耗模式的状态指示；
                                                                         1：对于请求noc进入低功耗模式的状态指示。 */
        unsigned int  noc_vdec_power_idle           : 1;  /* bit[10-10]: noc进入低功耗模式的状态指示。
                                                                         0：对于请求noc退出低功耗模式的状态指示；
                                                                         1：对于请求noc进入低功耗模式的状态指示。 */
        unsigned int  noc_venc_power_idle           : 1;  /* bit[11-11]: noc进入低功耗模式的状态指示。
                                                                         0：对于请求noc退出低功耗模式的状态指示；
                                                                         1：对于请求noc进入低功耗模式的状态指示。 */
        unsigned int  reserved_1                    : 1;  /* bit[12-12]: reserved */
        unsigned int  noc_dss_power_idle            : 1;  /* bit[13-13]: noc进入低功耗模式的状态指示。
                                                                         0：对于请求noc退出低功耗模式的状态指示；
                                                                         1：对于请求noc进入低功耗模式的状态指示。 */
        unsigned int  noc_ivp32_peri_bus_power_idle : 1;  /* bit[14-14]: noc进入低功耗模式的状态指示。
                                                                         0：对于请求noc退出低功耗模式的状态指示；
                                                                         1：对于请求noc进入低功耗模式的状态指示。 */
        unsigned int  reserved_2                    : 17; /* bit[15-31]: 保留 */
    } reg;
} SOC_PMCTRL_NOC_POWER_IDLE_UNION;
#endif
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_mmc0bus_power_idle_START         (1)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_mmc0bus_power_idle_END           (1)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_mmc1bus_power_idle_START         (2)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_mmc1bus_power_idle_END           (2)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_modem_power_idle_START           (3)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_modem_power_idle_END             (3)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_vcodec_power_idle_START          (4)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_vcodec_power_idle_END            (4)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_isp_power_idle_START             (5)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_isp_power_idle_END               (5)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_sysbus_power_idle_START          (6)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_sysbus_power_idle_END            (6)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_cfgbus_power_idle_START          (7)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_cfgbus_power_idle_END            (7)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_dmabus_power_idle_START          (8)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_dmabus_power_idle_END            (8)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_dbgbus_power_idle_START          (9)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_dbgbus_power_idle_END            (9)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_vdec_power_idle_START            (10)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_vdec_power_idle_END              (10)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_venc_power_idle_START            (11)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_venc_power_idle_END              (11)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_dss_power_idle_START             (13)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_dss_power_idle_END               (13)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_ivp32_peri_bus_power_idle_START  (14)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_ivp32_peri_bus_power_idle_END    (14)


/*****************************************************************************
 结构名    : SOC_PMCTRL_PERI_INT0_MASK_UNION
 结构说明  : PERI_INT0_MASK 寄存器结构定义。地址偏移量:0x3A0，初值:0x00000000，宽度:32
 寄存器说明: 外设中断屏蔽寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  noc_maintimeout_mask : 25; /* bit[0-24] : NOC target端口计数超时屏蔽信号：
                                                                0：不屏蔽计数超时信号；
                                                                1：屏蔽计数超时信号。 */
        unsigned int  reserved             : 7;  /* bit[25-31]: 保留 */
    } reg;
} SOC_PMCTRL_PERI_INT0_MASK_UNION;
#endif
#define SOC_PMCTRL_PERI_INT0_MASK_noc_maintimeout_mask_START  (0)
#define SOC_PMCTRL_PERI_INT0_MASK_noc_maintimeout_mask_END    (24)


/*****************************************************************************
 结构名    : SOC_PMCTRL_PERI_INT0_STAT_UNION
 结构说明  : PERI_INT0_STAT 寄存器结构定义。地址偏移量:0x3A4，初值:0x00000000，宽度:32
 寄存器说明: 外设中断状态寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  noc_gic_t_maintimeout               : 1;  /* bit[0-0]  : NOC target端口计数超时信号，当超时信号为高时，表示master访问slaver没有应答，slaver已挂死。 */
        unsigned int  noc_hkadc_ssi_t_maintimeout         : 1;  /* bit[1-1]  : NOC target端口计数超时信号，当超时信号为高时，表示master访问slaver没有应答，slaver已挂死。 */
        unsigned int  reserved_0                          : 1;  /* bit[2-2]  : 保留 */
        unsigned int  noc_lpm3_slv_t_maintimeout          : 1;  /* bit[3-3]  : NOC target端口计数超时信号，当超时信号为高时，表示master访问slaver没有应答，slaver已挂死。 */
        unsigned int  noc_sys_peri0_cfg_t_maintimeout     : 1;  /* bit[4-4]  : NOC target端口计数超时信号，当超时信号为高时，表示master访问slaver没有应答，slaver已挂死。 */
        unsigned int  noc_sys_peri1_cfg_t_maintimeout     : 1;  /* bit[5-5]  : NOC target端口计数超时信号，当超时信号为高时，表示master访问slaver没有应答，slaver已挂死。 */
        unsigned int  noc_sys_peri2_cfg_t_maintimeout     : 1;  /* bit[6-6]  : NOC target端口计数超时信号，当超时信号为高时，表示master访问slaver没有应答，slaver已挂死。 */
        unsigned int  noc_sys_peri3_cfg_t_maintimeout     : 1;  /* bit[7-7]  : NOC target端口计数超时信号，当超时信号为高时，表示master访问slaver没有应答，slaver已挂死。 */
        unsigned int  reserved_1                          : 1;  /* bit[8-8]  : 保留 */
        unsigned int  noc_dmac_cfg_t_maintimeout          : 1;  /* bit[9-9]  : NOC target端口计数超时信号，当超时信号为高时，表示master访问slaver没有应答，slaver已挂死。 */
        unsigned int  reserved_2                          : 2;  /* bit[10-11]: 保留 */
        unsigned int  noc_socp_cfg_t_maintimeout          : 1;  /* bit[12-12]: NOC target端口计数超时信号，当超时信号为高时，表示master访问slaver没有应答，slaver已挂死。 */
        unsigned int  noc_top_cssys_slv_cfg_t_maintimeout : 1;  /* bit[13-13]: NOC target端口计数超时信号，当超时信号为高时，表示master访问slaver没有应答，slaver已挂死。 */
        unsigned int  reserved_3                          : 1;  /* bit[14-14]: 保留 */
        unsigned int  noc_modem_bus_cfg_t_maintimeout     : 1;  /* bit[15-15]: NOC target端口计数超时信号，当超时信号为高时，表示master访问slaver没有应答，slaver已挂死。 */
        unsigned int  noc_usb3_cfg_t_maintimeout          : 1;  /* bit[16-16]: NOC target端口计数超时信号，当超时信号为高时，表示master访问slaver没有应答，slaver已挂死。 */
        unsigned int  noc_emmc0_cfg_t_maintimeout         : 1;  /* bit[17-17]: NOC target端口计数超时信号，当超时信号为高时，表示master访问slaver没有应答，slaver已挂死。 */
        unsigned int  noc_emmc0bus_apb_cfg_t_maintimeout  : 1;  /* bit[18-18]: NOC target端口计数超时信号，当超时信号为高时，表示master访问slaver没有应答，slaver已挂死。 */
        unsigned int  noc_ivp32_cfg_t_maintimeout         : 1;  /* bit[19-19]: NOC target端口计数超时信号，当超时信号为高时，表示master访问slaver没有应答，slaver已挂死。 */
        unsigned int  noc_sys2hkmem_t_maintimeout         : 1;  /* bit[20-20]: NOC target端口计数超时信号，当超时信号为高时，表示master访问slaver没有应答，slaver已挂死。 */
        unsigned int  noc_emmc1bus_apb_cfg_t_maintimeout  : 1;  /* bit[21-21]: NOC target端口计数超时信号，当超时信号为高时，表示master访问slaver没有应答，slaver已挂死。 */
        unsigned int  reserved_4                          : 1;  /* bit[22-22]: 保留 */
        unsigned int  noc_cfg2vivo_t_maintimeout          : 1;  /* bit[23-23]: NOC target端口计数超时信号，当超时信号为高时，表示master访问slaver没有应答，slaver已挂死。 */
        unsigned int  noc_debug_apb_cfg_t_maintimeout     : 1;  /* bit[24-24]: NOC target端口计数超时信号，当超时信号为高时，表示master访问slaver没有应答，slaver已挂死。 */
        unsigned int  reserved_5                          : 7;  /* bit[25-31]: 保留 */
    } reg;
} SOC_PMCTRL_PERI_INT0_STAT_UNION;
#endif
#define SOC_PMCTRL_PERI_INT0_STAT_noc_gic_t_maintimeout_START                (0)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_gic_t_maintimeout_END                  (0)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_hkadc_ssi_t_maintimeout_START          (1)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_hkadc_ssi_t_maintimeout_END            (1)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_lpm3_slv_t_maintimeout_START           (3)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_lpm3_slv_t_maintimeout_END             (3)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_sys_peri0_cfg_t_maintimeout_START      (4)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_sys_peri0_cfg_t_maintimeout_END        (4)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_sys_peri1_cfg_t_maintimeout_START      (5)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_sys_peri1_cfg_t_maintimeout_END        (5)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_sys_peri2_cfg_t_maintimeout_START      (6)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_sys_peri2_cfg_t_maintimeout_END        (6)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_sys_peri3_cfg_t_maintimeout_START      (7)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_sys_peri3_cfg_t_maintimeout_END        (7)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_dmac_cfg_t_maintimeout_START           (9)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_dmac_cfg_t_maintimeout_END             (9)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_socp_cfg_t_maintimeout_START           (12)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_socp_cfg_t_maintimeout_END             (12)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_top_cssys_slv_cfg_t_maintimeout_START  (13)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_top_cssys_slv_cfg_t_maintimeout_END    (13)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_modem_bus_cfg_t_maintimeout_START      (15)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_modem_bus_cfg_t_maintimeout_END        (15)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_usb3_cfg_t_maintimeout_START           (16)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_usb3_cfg_t_maintimeout_END             (16)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_emmc0_cfg_t_maintimeout_START          (17)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_emmc0_cfg_t_maintimeout_END            (17)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_emmc0bus_apb_cfg_t_maintimeout_START   (18)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_emmc0bus_apb_cfg_t_maintimeout_END     (18)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_ivp32_cfg_t_maintimeout_START          (19)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_ivp32_cfg_t_maintimeout_END            (19)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_sys2hkmem_t_maintimeout_START          (20)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_sys2hkmem_t_maintimeout_END            (20)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_emmc1bus_apb_cfg_t_maintimeout_START   (21)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_emmc1bus_apb_cfg_t_maintimeout_END     (21)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_cfg2vivo_t_maintimeout_START           (23)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_cfg2vivo_t_maintimeout_END             (23)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_debug_apb_cfg_t_maintimeout_START      (24)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_debug_apb_cfg_t_maintimeout_END        (24)


/*****************************************************************************
 结构名    : SOC_PMCTRL_PERI_INT1_MASK_UNION
 结构说明  : PERI_INT1_MASK 寄存器结构定义。地址偏移量:0x3A8，初值:0x00000000，宽度:32
 寄存器说明: 外设中断屏蔽寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 保留 */
    } reg;
} SOC_PMCTRL_PERI_INT1_MASK_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_PMCTRL_PERI_INT1_STAT_UNION
 结构说明  : PERI_INT1_STAT 寄存器结构定义。地址偏移量:0x3AC，初值:0x00000000，宽度:32
 寄存器说明: 外设中断状态寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 保留 */
    } reg;
} SOC_PMCTRL_PERI_INT1_STAT_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_PMCTRL_PERI_INT2_MASK_UNION
 结构说明  : PERI_INT2_MASK 寄存器结构定义。地址偏移量:0x3B0，初值:0x00000000，宽度:32
 寄存器说明: 外设中断屏蔽寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 保留 */
    } reg;
} SOC_PMCTRL_PERI_INT2_MASK_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_PMCTRL_PERI_INT2_STAT_UNION
 结构说明  : PERI_INT2_STAT 寄存器结构定义。地址偏移量:0x3B4，初值:0x00000000，宽度:32
 寄存器说明: 外设中断状态寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 保留 */
    } reg;
} SOC_PMCTRL_PERI_INT2_STAT_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_PMCTRL_PERI_INT3_MASK_UNION
 结构说明  : PERI_INT3_MASK 寄存器结构定义。地址偏移量:0x3B8，初值:0x00000000，宽度:32
 寄存器说明: 外设中断屏蔽寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 保留 */
    } reg;
} SOC_PMCTRL_PERI_INT3_MASK_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_PMCTRL_PERI_INT3_STAT_UNION
 结构说明  : PERI_INT3_STAT 寄存器结构定义。地址偏移量:0x3BC，初值:0x00000000，宽度:32
 寄存器说明: 外设中断状态寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 保留 */
    } reg;
} SOC_PMCTRL_PERI_INT3_STAT_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_PMCTRL_VSENSOR_CTRL_EN_1_UNION
 结构说明  : VSENSOR_CTRL_EN_1 寄存器结构定义。地址偏移量:0x3D0，初值:0x00000000，宽度:32
 寄存器说明: Vsensor控制使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vs_ctrl_en_1 : 1;  /* bit[0-0] : A53 Vsensor控制使能：
                                                       0：Vsensor不使能；
                                                       1：Vsensor使能 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_PMCTRL_VSENSOR_CTRL_EN_1_UNION;
#endif
#define SOC_PMCTRL_VSENSOR_CTRL_EN_1_vs_ctrl_en_1_START  (0)
#define SOC_PMCTRL_VSENSOR_CTRL_EN_1_vs_ctrl_en_1_END    (0)


/*****************************************************************************
 结构名    : SOC_PMCTRL_VSENSOR_CTRL_BYPASS_1_UNION
 结构说明  : VSENSOR_CTRL_BYPASS_1 寄存器结构定义。地址偏移量:0x3D4，初值:0x00000001，宽度:32
 寄存器说明: Vsensor bypass寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vs_ctrl_bypass_1 : 1;  /* bit[0-0] : A53 Vsensor bypass信号：
                                                           0：Vsensor控制逻辑输出门控信号控制ICG；
                                                           1：Vsensor控制逻辑bypass，门控信号一直为1 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_PMCTRL_VSENSOR_CTRL_BYPASS_1_UNION;
#endif
#define SOC_PMCTRL_VSENSOR_CTRL_BYPASS_1_vs_ctrl_bypass_1_START  (0)
#define SOC_PMCTRL_VSENSOR_CTRL_BYPASS_1_vs_ctrl_bypass_1_END    (0)


/*****************************************************************************
 结构名    : SOC_PMCTRL_VSENSOR_CTRL_1_UNION
 结构说明  : VSENSOR_CTRL_1 寄存器结构定义。地址偏移量:0x3D8，初值:0x00000000，宽度:32
 寄存器说明: Vsensor控制配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vs_mod_a53              : 1;  /* bit[0-0]  : A53 Vsensor模式：
                                                                   0：非中断模式
                                                                   1：中断模式 */
        unsigned int  a53_cpu0_wfi_wfe_bypass : 1;  /* bit[1-1]  : CPU0 WFI/WFE主动防御的bypass
                                                                   1'b1:bypass;
                                                                   1'b0:使能 */
        unsigned int  a53_cpu1_wfi_wfe_bypass : 1;  /* bit[2-2]  : CPU1 WFI/WFE主动防御的bypass
                                                                   1'b1:bypass;
                                                                   1'b0:使能 */
        unsigned int  a53_cpu2_wfi_wfe_bypass : 1;  /* bit[3-3]  : CPU2 WFI/WFE主动防御的bypass
                                                                   1'b1:bypass;
                                                                   1'b0:使能 */
        unsigned int  a53_cpu3_wfi_wfe_bypass : 1;  /* bit[4-4]  : CPU3 WFI/WFE主动防御的bypass
                                                                   1'b1:bypass;
                                                                   1'b0:使能 */
        unsigned int  a53_l2_idle_div_mod     : 2;  /* bit[5-6]  : l2 idle自动降频分频模式：
                                                                   00:4分频
                                                                   01:8分频
                                                                   10:16分频
                                                                   11:32分频 */
        unsigned int  reserved                : 1;  /* bit[7-7]  : 保留 */
        unsigned int  svfd_test_in_1          : 4;  /* bit[8-11] : 预留测试输入 */
        unsigned int  svfd_ulvt_ll_1          : 4;  /* bit[12-15]: ULVT长线级联，级数配置PIN */
        unsigned int  svfd_ulvt_sl_1          : 4;  /* bit[16-19]: ULVT短线级联，级数配置PIN */
        unsigned int  svfd_lvt_ll_1           : 4;  /* bit[20-23]: LVT长线级联，级数配置PIN */
        unsigned int  svfd_lvt_sl_1           : 4;  /* bit[24-27]: LVT短线级联，级数配置PIN */
        unsigned int  svfd_vdm_mode_1         : 2;  /* bit[28-29]: 电压检测模式选择：
                                                                   00 :reserve 
                                                                   01 : IP内部电压检测(CPM)
                                                                   10 : IP外部电压检测(VDM)
                                                                   11 :VDM+CPM */
        unsigned int  svfd_match_detect_1     : 1;  /* bit[30-30]: 匹配达标检测使能，1有效；
                                                                   工作状态，要保持为0；
                                                                   用于DFT量产筛选 */
        unsigned int  svfd_trim_1             : 1;  /* bit[31-31]: 保留 */
    } reg;
} SOC_PMCTRL_VSENSOR_CTRL_1_UNION;
#endif
#define SOC_PMCTRL_VSENSOR_CTRL_1_vs_mod_a53_START               (0)
#define SOC_PMCTRL_VSENSOR_CTRL_1_vs_mod_a53_END                 (0)
#define SOC_PMCTRL_VSENSOR_CTRL_1_a53_cpu0_wfi_wfe_bypass_START  (1)
#define SOC_PMCTRL_VSENSOR_CTRL_1_a53_cpu0_wfi_wfe_bypass_END    (1)
#define SOC_PMCTRL_VSENSOR_CTRL_1_a53_cpu1_wfi_wfe_bypass_START  (2)
#define SOC_PMCTRL_VSENSOR_CTRL_1_a53_cpu1_wfi_wfe_bypass_END    (2)
#define SOC_PMCTRL_VSENSOR_CTRL_1_a53_cpu2_wfi_wfe_bypass_START  (3)
#define SOC_PMCTRL_VSENSOR_CTRL_1_a53_cpu2_wfi_wfe_bypass_END    (3)
#define SOC_PMCTRL_VSENSOR_CTRL_1_a53_cpu3_wfi_wfe_bypass_START  (4)
#define SOC_PMCTRL_VSENSOR_CTRL_1_a53_cpu3_wfi_wfe_bypass_END    (4)
#define SOC_PMCTRL_VSENSOR_CTRL_1_a53_l2_idle_div_mod_START      (5)
#define SOC_PMCTRL_VSENSOR_CTRL_1_a53_l2_idle_div_mod_END        (6)
#define SOC_PMCTRL_VSENSOR_CTRL_1_svfd_test_in_1_START           (8)
#define SOC_PMCTRL_VSENSOR_CTRL_1_svfd_test_in_1_END             (11)
#define SOC_PMCTRL_VSENSOR_CTRL_1_svfd_ulvt_ll_1_START           (12)
#define SOC_PMCTRL_VSENSOR_CTRL_1_svfd_ulvt_ll_1_END             (15)
#define SOC_PMCTRL_VSENSOR_CTRL_1_svfd_ulvt_sl_1_START           (16)
#define SOC_PMCTRL_VSENSOR_CTRL_1_svfd_ulvt_sl_1_END             (19)
#define SOC_PMCTRL_VSENSOR_CTRL_1_svfd_lvt_ll_1_START            (20)
#define SOC_PMCTRL_VSENSOR_CTRL_1_svfd_lvt_ll_1_END              (23)
#define SOC_PMCTRL_VSENSOR_CTRL_1_svfd_lvt_sl_1_START            (24)
#define SOC_PMCTRL_VSENSOR_CTRL_1_svfd_lvt_sl_1_END              (27)
#define SOC_PMCTRL_VSENSOR_CTRL_1_svfd_vdm_mode_1_START          (28)
#define SOC_PMCTRL_VSENSOR_CTRL_1_svfd_vdm_mode_1_END            (29)
#define SOC_PMCTRL_VSENSOR_CTRL_1_svfd_match_detect_1_START      (30)
#define SOC_PMCTRL_VSENSOR_CTRL_1_svfd_match_detect_1_END        (30)
#define SOC_PMCTRL_VSENSOR_CTRL_1_svfd_trim_1_START              (31)
#define SOC_PMCTRL_VSENSOR_CTRL_1_svfd_trim_1_END                (31)


/*****************************************************************************
 结构名    : SOC_PMCTRL_VSENSOR_CNT_1_UNION
 结构说明  : VSENSOR_CNT_1 寄存器结构定义。地址偏移量:0x3DC，初值:0x00000000，宽度:32
 寄存器说明: Vsensor计数控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vs_cnt_quit_1  : 16; /* bit[0-15] : 退出门控延时，每次进入门控后，会等待相应时间后再次进行电压判断（非中断模式有用） */
        unsigned int  vs_cnt_enter_1 : 16; /* bit[16-31]: 进入门控延时，每次退出门控后，会等待相应时间后再次进行电压判断 */
    } reg;
} SOC_PMCTRL_VSENSOR_CNT_1_UNION;
#endif
#define SOC_PMCTRL_VSENSOR_CNT_1_vs_cnt_quit_1_START   (0)
#define SOC_PMCTRL_VSENSOR_CNT_1_vs_cnt_quit_1_END     (15)
#define SOC_PMCTRL_VSENSOR_CNT_1_vs_cnt_enter_1_START  (16)
#define SOC_PMCTRL_VSENSOR_CNT_1_vs_cnt_enter_1_END    (31)


/*****************************************************************************
 结构名    : SOC_PMCTRL_VSENSOR_REF_CODE_1_UNION
 结构说明  : VSENSOR_REF_CODE_1 寄存器结构定义。地址偏移量:0x3E0，初值:0x00000000，宽度:32
 寄存器说明: Vsensor参考码字寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_vs_ref_code_l             : 6;  /* bit[0-5]  : A53进入门控码字 */
        unsigned int  a53_vs_ref_code_h             : 6;  /* bit[6-11] : A53退出门控码字 */
        unsigned int  a53_cfg_cnt_cpu_wake_quit     : 8;  /* bit[12-19]: A53 WFI/WFE主动防御退出超时；计数周期为VDM工作时钟； */
        unsigned int  a53_cfg_cnt_cpu_l2_idle_quit  : 8;  /* bit[20-27]: A53 L2 IDLE主动防御退出超时；计数周期为VDM工作时钟； */
        unsigned int  a53_cpu_wake_up_mode          : 2;  /* bit[28-29]: A53 WFI/WFE主动防御模式；
                                                                         2'b00:一个或一个以上退出WFI/WFE,进入主动防御;
                                                                         2'b01:两个或两个以上退出WFI/WFE,进入主动防御;
                                                                         2'b10:三个或三个以上退出WFI/WFE,进入主动防御;
                                                                         2'b11:四个同时退出WFI/WFE,进入主动防御; */
        unsigned int  a53_cpu_l2_idle_switch_bypass : 1;  /* bit[30-30]: A53 退出L2主动防御功能bypass；
                                                                         1'b1:bypass;
                                                                         1'b0:使能 */
        unsigned int  a53_cpu_l2_idle_gt_en         : 1;  /* bit[31-31]: A53 进入L2 IDLE后自动降频功能使能信号；
                                                                         1'b0:不使能;
                                                                         1'b1:使能，进入L2 IDLE后，主频自动变为原来的64分频 */
    } reg;
} SOC_PMCTRL_VSENSOR_REF_CODE_1_UNION;
#endif
#define SOC_PMCTRL_VSENSOR_REF_CODE_1_a53_vs_ref_code_l_START              (0)
#define SOC_PMCTRL_VSENSOR_REF_CODE_1_a53_vs_ref_code_l_END                (5)
#define SOC_PMCTRL_VSENSOR_REF_CODE_1_a53_vs_ref_code_h_START              (6)
#define SOC_PMCTRL_VSENSOR_REF_CODE_1_a53_vs_ref_code_h_END                (11)
#define SOC_PMCTRL_VSENSOR_REF_CODE_1_a53_cfg_cnt_cpu_wake_quit_START      (12)
#define SOC_PMCTRL_VSENSOR_REF_CODE_1_a53_cfg_cnt_cpu_wake_quit_END        (19)
#define SOC_PMCTRL_VSENSOR_REF_CODE_1_a53_cfg_cnt_cpu_l2_idle_quit_START   (20)
#define SOC_PMCTRL_VSENSOR_REF_CODE_1_a53_cfg_cnt_cpu_l2_idle_quit_END     (27)
#define SOC_PMCTRL_VSENSOR_REF_CODE_1_a53_cpu_wake_up_mode_START           (28)
#define SOC_PMCTRL_VSENSOR_REF_CODE_1_a53_cpu_wake_up_mode_END             (29)
#define SOC_PMCTRL_VSENSOR_REF_CODE_1_a53_cpu_l2_idle_switch_bypass_START  (30)
#define SOC_PMCTRL_VSENSOR_REF_CODE_1_a53_cpu_l2_idle_switch_bypass_END    (30)
#define SOC_PMCTRL_VSENSOR_REF_CODE_1_a53_cpu_l2_idle_gt_en_START          (31)
#define SOC_PMCTRL_VSENSOR_REF_CODE_1_a53_cpu_l2_idle_gt_en_END            (31)


/*****************************************************************************
 结构名    : SOC_PMCTRL_VSENSOR_CALI_CODE_1_UNION
 结构说明  : VSENSOR_CALI_CODE_1 寄存器结构定义。地址偏移量:0x3E4，初值:0x00000000，宽度:32
 寄存器说明: Vsensor抽头控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_vs_cali_code       : 7;  /* bit[0-6]  : A53 Vsensor抽头校准码字 */
        unsigned int  reserved_0             : 1;  /* bit[7-7]  : 保留 */
        unsigned int  a53_svfd_off_mode      : 1;  /* bit[8-8]  : 1'b0：直接降频；
                                                                  1'b1：逐级降频； */
        unsigned int  a53_svfd_div64_en      : 1;  /* bit[9-9]  : 使能信号，工作模式不翻转 */
        unsigned int  a53_svfd_vdm_period    : 1;  /* bit[10-10]: 电压检测采样周期
                                                                  1'b0：1cycle；
                                                                  1'b1：2cycle； */
        unsigned int  a53_svfd_edge_sel      : 1;  /* bit[11-11]: 1'b0：上升沿检测； 
                                                                  1'b1：双沿检测（上升沿+下降沿） */
        unsigned int  a53_svfd_cmp_data_mode : 2;  /* bit[12-13]: CPM码字的输出模式：
                                                                  00：直接输出
                                                                  01：最小值输出
                                                                  10：最大值输出
                                                                  11：不翻转 */
        unsigned int  a53_svfd_data_limit_e  : 1;  /* bit[14-14]: 极限值输出状态下，使能信号；
                                                                  1'b0：清除前一次求值；
                                                                  1'b1：使能极限求值； */
        unsigned int  a53_svfd_glitch_test   : 1;  /* bit[15-15]: Glitch测试使能; */
        unsigned int  a53_svfd_out_div_sel   : 4;  /* bit[16-19]: CPM码字分频输出选择 */
        unsigned int  reserved_1             : 1;  /* bit[20-20]: 保留 */
        unsigned int  sel_ckmux_a53_icg      : 1;  /* bit[21-21]: 时钟选择源头：
                                                                  1'b0：CRG直接输出的时钟
                                                                  1'b1：SVFD输出的时钟 */
        unsigned int  reserved_2             : 1;  /* bit[22-22]: 保留 */
        unsigned int  a53_ext_ref_code       : 7;  /* bit[23-29]: a53 ref_code的高bit，配合ref_code_h和ref_code_l一起使用，与采样累加次数相关 */
        unsigned int  a53_compare_mod        : 2;  /* bit[30-31]: A53数据比较模式：
                                                                  00：采样后的数据直接与ref_code比较
                                                                  01：采样后32次累加数据与ref_code比较
                                                                  10：采样后64次累加数据与ref_code比较
                                                                  11：采样后128次累加数据与ref_code比较 */
    } reg;
} SOC_PMCTRL_VSENSOR_CALI_CODE_1_UNION;
#endif
#define SOC_PMCTRL_VSENSOR_CALI_CODE_1_a53_vs_cali_code_START        (0)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_1_a53_vs_cali_code_END          (6)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_1_a53_svfd_off_mode_START       (8)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_1_a53_svfd_off_mode_END         (8)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_1_a53_svfd_div64_en_START       (9)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_1_a53_svfd_div64_en_END         (9)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_1_a53_svfd_vdm_period_START     (10)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_1_a53_svfd_vdm_period_END       (10)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_1_a53_svfd_edge_sel_START       (11)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_1_a53_svfd_edge_sel_END         (11)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_1_a53_svfd_cmp_data_mode_START  (12)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_1_a53_svfd_cmp_data_mode_END    (13)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_1_a53_svfd_data_limit_e_START   (14)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_1_a53_svfd_data_limit_e_END     (14)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_1_a53_svfd_glitch_test_START    (15)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_1_a53_svfd_glitch_test_END      (15)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_1_a53_svfd_out_div_sel_START    (16)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_1_a53_svfd_out_div_sel_END      (19)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_1_sel_ckmux_a53_icg_START       (21)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_1_sel_ckmux_a53_icg_END         (21)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_1_a53_ext_ref_code_START        (23)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_1_a53_ext_ref_code_END          (29)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_1_a53_compare_mod_START         (30)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_1_a53_compare_mod_END           (31)


/*****************************************************************************
 结构名    : SOC_PMCTRL_VSENSOR_CODE_1_UNION
 结构说明  : VSENSOR_CODE_1 寄存器结构定义。地址偏移量:0x3E8，初值:0x00000000，宽度:32
 寄存器说明: Vsensor码字寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_vs_code : 6;  /* bit[0-5] : A53 Vsensor码字 */
        unsigned int  reserved    : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_PMCTRL_VSENSOR_CODE_1_UNION;
#endif
#define SOC_PMCTRL_VSENSOR_CODE_1_a53_vs_code_START  (0)
#define SOC_PMCTRL_VSENSOR_CODE_1_a53_vs_code_END    (5)


/*****************************************************************************
 结构名    : SOC_PMCTRL_VSENSOR_INTSTAT_1_UNION
 结构说明  : VSENSOR_INTSTAT_1 寄存器结构定义。地址偏移量:0x3EC，初值:0x00000000，宽度:32
 寄存器说明: Vsensor中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intr_vdm_stat_1 : 1;  /* bit[0-0] : Vsensor中断状态，写该寄存器。可清除VDM中的intr_vdm */
        unsigned int  dll_lock_1      : 1;  /* bit[1-1] : DLL lock指示寄存器。 */
        unsigned int  reserved        : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_PMCTRL_VSENSOR_INTSTAT_1_UNION;
#endif
#define SOC_PMCTRL_VSENSOR_INTSTAT_1_intr_vdm_stat_1_START  (0)
#define SOC_PMCTRL_VSENSOR_INTSTAT_1_intr_vdm_stat_1_END    (0)
#define SOC_PMCTRL_VSENSOR_INTSTAT_1_dll_lock_1_START       (1)
#define SOC_PMCTRL_VSENSOR_INTSTAT_1_dll_lock_1_END         (1)


/*****************************************************************************
 结构名    : SOC_PMCTRL_VSENSOR_D_RATE_1_UNION
 结构说明  : VSENSOR_D_RATE_1 寄存器结构定义。地址偏移量:0x3F0，初值:0x00000000，宽度:32
 寄存器说明: Vsensor中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  svfd_d_rate_1 : 2;  /* bit[0-1] : A53 DLL调相速率
                                                        00 : 10%
                                                        01 : 20%
                                                        10 : 30%
                                                        11 : reseved */
        unsigned int  reserved      : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_PMCTRL_VSENSOR_D_RATE_1_UNION;
#endif
#define SOC_PMCTRL_VSENSOR_D_RATE_1_svfd_d_rate_1_START  (0)
#define SOC_PMCTRL_VSENSOR_D_RATE_1_svfd_d_rate_1_END    (1)


/*****************************************************************************
 结构名    : SOC_PMCTRL_VSENSOR_CTRL_EN_0_UNION
 结构说明  : VSENSOR_CTRL_EN_0 寄存器结构定义。地址偏移量:0x3F4，初值:0x00000000，宽度:32
 寄存器说明: Vsensor控制使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vs_ctrl_en_0 : 1;  /* bit[0-0] : maya Vsensor控制使能：
                                                       0：Vsensor不使能；
                                                       1：Vsensor使能 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_PMCTRL_VSENSOR_CTRL_EN_0_UNION;
#endif
#define SOC_PMCTRL_VSENSOR_CTRL_EN_0_vs_ctrl_en_0_START  (0)
#define SOC_PMCTRL_VSENSOR_CTRL_EN_0_vs_ctrl_en_0_END    (0)


/*****************************************************************************
 结构名    : SOC_PMCTRL_VSENSOR_CTRL_BYPASS_0_UNION
 结构说明  : VSENSOR_CTRL_BYPASS_0 寄存器结构定义。地址偏移量:0x3F8，初值:0x00000001，宽度:32
 寄存器说明: Vsensor bypass寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vs_ctrl_bypass_0 : 1;  /* bit[0-0] : maya Vsensor bypass信号：
                                                           0：Vsensor控制逻辑输出门控信号控制ICG；
                                                           1：Vsensor控制逻辑bypass，门控信号一直为1 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_PMCTRL_VSENSOR_CTRL_BYPASS_0_UNION;
#endif
#define SOC_PMCTRL_VSENSOR_CTRL_BYPASS_0_vs_ctrl_bypass_0_START  (0)
#define SOC_PMCTRL_VSENSOR_CTRL_BYPASS_0_vs_ctrl_bypass_0_END    (0)


/*****************************************************************************
 结构名    : SOC_PMCTRL_VSENSOR_CTRL_0_UNION
 结构说明  : VSENSOR_CTRL_0 寄存器结构定义。地址偏移量:0x3FC，初值:0x00000000，宽度:32
 寄存器说明: Vsensor控制配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vs_mod_maia              : 1;  /* bit[0]    : maia Vsensor模式：
                                                                    0：非中断模式
                                                                    1：中断模式 */
        unsigned int  maia_cpu0_wfi_wfe_bypass : 1;  /* bit[1-1]  : CPU0 WFI/WFE主动防御的bypass
                                                                    1'b1:bypass;
                                                                    1'b0:使能 */
        unsigned int  maia_cpu1_wfi_wfe_bypass : 1;  /* bit[2-2]  : CPU1 WFI/WFE主动防御的bypass
                                                                    1'b1:bypass;
                                                                    1'b0:使能 */
        unsigned int  maia_cpu2_wfi_wfe_bypass : 1;  /* bit[3-3]  : CPU2 WFI/WFE主动防御的bypass
                                                                    1'b1:bypass;
                                                                    1'b0:使能 */
        unsigned int  maia_cpu3_wfi_wfe_bypass : 1;  /* bit[4-4]  : CPU3 WFI/WFE主动防御的bypass
                                                                    1'b1:bypass;
                                                                    1'b0:使能 */
        unsigned int  maia_l2_idle_div_mod     : 2;  /* bit[5-6]  : l2 idle自动降频分频模式：
                                                                    00:4分频
                                                                    01:8分频
                                                                    10:16分频
                                                                    11:32分频 */
        unsigned int  reserved                 : 1;  /* bit[7-7]  : 保留 */
        unsigned int  svfd_test_in_0           : 4;  /* bit[8-11] : 预留测试输入PIN */
        unsigned int  svfd_ulvt_ll_0           : 4;  /* bit[12-15]: ULVT长线级联，级数配置PIN */
        unsigned int  svfd_ulvt_sl_0           : 4;  /* bit[16-19]: ULVT短线级联，级数配置PIN */
        unsigned int  svfd_lvt_ll_0            : 4;  /* bit[20-23]: LVT长线级联，级数配置PIN */
        unsigned int  svfd_lvt_sl_0            : 4;  /* bit[24-27]: LVT短线级联，级数配置PIN */
        unsigned int  svfd_vdm_mode_0          : 2;  /* bit[28-29]: 电压检测模式选择：
                                                                    00 :reserve 
                                                                    01 : IP内部电压检测(CPM)
                                                                    10 : IP外部电压检测(VDM)
                                                                    11 :VDM+CPM */
        unsigned int  svfd_match_detect_0      : 1;  /* bit[30-30]: 匹配达标检测使能，1有效；
                                                                    工作状态，要保持为0；
                                                                    用于DFT量产筛选 */
        unsigned int  svfd_trim_0              : 1;  /* bit[31-31]: 保留 */
    } reg;
} SOC_PMCTRL_VSENSOR_CTRL_0_UNION;
#endif
#define SOC_PMCTRL_VSENSOR_CTRL_0_vs_mod_maia_START               (0)
#define SOC_PMCTRL_VSENSOR_CTRL_0_vs_mod_maia_END                 (0)
#define SOC_PMCTRL_VSENSOR_CTRL_0_maia_cpu0_wfi_wfe_bypass_START  (1)
#define SOC_PMCTRL_VSENSOR_CTRL_0_maia_cpu0_wfi_wfe_bypass_END    (1)
#define SOC_PMCTRL_VSENSOR_CTRL_0_maia_cpu1_wfi_wfe_bypass_START  (2)
#define SOC_PMCTRL_VSENSOR_CTRL_0_maia_cpu1_wfi_wfe_bypass_END    (2)
#define SOC_PMCTRL_VSENSOR_CTRL_0_maia_cpu2_wfi_wfe_bypass_START  (3)
#define SOC_PMCTRL_VSENSOR_CTRL_0_maia_cpu2_wfi_wfe_bypass_END    (3)
#define SOC_PMCTRL_VSENSOR_CTRL_0_maia_cpu3_wfi_wfe_bypass_START  (4)
#define SOC_PMCTRL_VSENSOR_CTRL_0_maia_cpu3_wfi_wfe_bypass_END    (4)
#define SOC_PMCTRL_VSENSOR_CTRL_0_maia_l2_idle_div_mod_START      (5)
#define SOC_PMCTRL_VSENSOR_CTRL_0_maia_l2_idle_div_mod_END        (6)
#define SOC_PMCTRL_VSENSOR_CTRL_0_svfd_test_in_0_START            (8)
#define SOC_PMCTRL_VSENSOR_CTRL_0_svfd_test_in_0_END              (11)
#define SOC_PMCTRL_VSENSOR_CTRL_0_svfd_ulvt_ll_0_START            (12)
#define SOC_PMCTRL_VSENSOR_CTRL_0_svfd_ulvt_ll_0_END              (15)
#define SOC_PMCTRL_VSENSOR_CTRL_0_svfd_ulvt_sl_0_START            (16)
#define SOC_PMCTRL_VSENSOR_CTRL_0_svfd_ulvt_sl_0_END              (19)
#define SOC_PMCTRL_VSENSOR_CTRL_0_svfd_lvt_ll_0_START             (20)
#define SOC_PMCTRL_VSENSOR_CTRL_0_svfd_lvt_ll_0_END               (23)
#define SOC_PMCTRL_VSENSOR_CTRL_0_svfd_lvt_sl_0_START             (24)
#define SOC_PMCTRL_VSENSOR_CTRL_0_svfd_lvt_sl_0_END               (27)
#define SOC_PMCTRL_VSENSOR_CTRL_0_svfd_vdm_mode_0_START           (28)
#define SOC_PMCTRL_VSENSOR_CTRL_0_svfd_vdm_mode_0_END             (29)
#define SOC_PMCTRL_VSENSOR_CTRL_0_svfd_match_detect_0_START       (30)
#define SOC_PMCTRL_VSENSOR_CTRL_0_svfd_match_detect_0_END         (30)
#define SOC_PMCTRL_VSENSOR_CTRL_0_svfd_trim_0_START               (31)
#define SOC_PMCTRL_VSENSOR_CTRL_0_svfd_trim_0_END                 (31)


/*****************************************************************************
 结构名    : SOC_PMCTRL_VSENSOR_CNT_0_UNION
 结构说明  : VSENSOR_CNT_0 寄存器结构定义。地址偏移量:0x400，初值:0x00000000，宽度:32
 寄存器说明: Vsensor计数控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vs_cnt_quit_0  : 16; /* bit[0-15] : 退出门控延时，每次进入门控后，会等待相应时间后再次进行电压判断（非中断模式有用） */
        unsigned int  vs_cnt_enter_0 : 16; /* bit[16-31]: 进入门控延时，每次退出门控后，会等待相应时间后再次进行电压判断 */
    } reg;
} SOC_PMCTRL_VSENSOR_CNT_0_UNION;
#endif
#define SOC_PMCTRL_VSENSOR_CNT_0_vs_cnt_quit_0_START   (0)
#define SOC_PMCTRL_VSENSOR_CNT_0_vs_cnt_quit_0_END     (15)
#define SOC_PMCTRL_VSENSOR_CNT_0_vs_cnt_enter_0_START  (16)
#define SOC_PMCTRL_VSENSOR_CNT_0_vs_cnt_enter_0_END    (31)


/*****************************************************************************
 结构名    : SOC_PMCTRL_VSENSOR_REF_CODE_0_UNION
 结构说明  : VSENSOR_REF_CODE_0 寄存器结构定义。地址偏移量:0x404，初值:0x00000000，宽度:32
 寄存器说明: Vsensor参考码字寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  maia_vs_ref_code_l             : 6;  /* bit[0-5]  : MAIA进入门控码字 */
        unsigned int  maia_vs_ref_code_h             : 6;  /* bit[6-11] : MAIA退出门控码字 */
        unsigned int  maia_cfg_cnt_cpu_wake_quit     : 8;  /* bit[12-19]: MAIA WFI/WFE主动防御退出超时；计数周期为VDM工作时钟； */
        unsigned int  maia_cfg_cnt_cpu_l2_idle_quit  : 8;  /* bit[20-27]: MAIA L2 IDLE主动防御退出超时；计数周期为VDM工作时钟； */
        unsigned int  maia_cpu_wake_up_mode          : 2;  /* bit[28-29]: MAIA WFI/WFE主动防御模式；
                                                                          2'b00:一个或一个以上退出WFI/WFE,进入主动防御;
                                                                          2'b01:两个或两个以上退出WFI/WFE,进入主动防御;
                                                                          2'b10:三个或三个以上退出WFI/WFE,进入主动防御;
                                                                          2'b11:四个同时退出WFI/WFE,进入主动防御; */
        unsigned int  maia_cpu_l2_idle_switch_bypass : 1;  /* bit[30-30]: MAIA 退出L2主动防御功能bypass；
                                                                          1'b1:bypass;
                                                                          1'b0:使能 */
        unsigned int  maia_cpu_l2_idle_gt_en         : 1;  /* bit[31-31]: MAIA进入L2 IDLE后自动降频功能使能信号；
                                                                          1'b0:不使能;
                                                                          1'b1:使能，进入L2 IDLE后，主频自动变为原来的64分频 */
    } reg;
} SOC_PMCTRL_VSENSOR_REF_CODE_0_UNION;
#endif
#define SOC_PMCTRL_VSENSOR_REF_CODE_0_maia_vs_ref_code_l_START              (0)
#define SOC_PMCTRL_VSENSOR_REF_CODE_0_maia_vs_ref_code_l_END                (5)
#define SOC_PMCTRL_VSENSOR_REF_CODE_0_maia_vs_ref_code_h_START              (6)
#define SOC_PMCTRL_VSENSOR_REF_CODE_0_maia_vs_ref_code_h_END                (11)
#define SOC_PMCTRL_VSENSOR_REF_CODE_0_maia_cfg_cnt_cpu_wake_quit_START      (12)
#define SOC_PMCTRL_VSENSOR_REF_CODE_0_maia_cfg_cnt_cpu_wake_quit_END        (19)
#define SOC_PMCTRL_VSENSOR_REF_CODE_0_maia_cfg_cnt_cpu_l2_idle_quit_START   (20)
#define SOC_PMCTRL_VSENSOR_REF_CODE_0_maia_cfg_cnt_cpu_l2_idle_quit_END     (27)
#define SOC_PMCTRL_VSENSOR_REF_CODE_0_maia_cpu_wake_up_mode_START           (28)
#define SOC_PMCTRL_VSENSOR_REF_CODE_0_maia_cpu_wake_up_mode_END             (29)
#define SOC_PMCTRL_VSENSOR_REF_CODE_0_maia_cpu_l2_idle_switch_bypass_START  (30)
#define SOC_PMCTRL_VSENSOR_REF_CODE_0_maia_cpu_l2_idle_switch_bypass_END    (30)
#define SOC_PMCTRL_VSENSOR_REF_CODE_0_maia_cpu_l2_idle_gt_en_START          (31)
#define SOC_PMCTRL_VSENSOR_REF_CODE_0_maia_cpu_l2_idle_gt_en_END            (31)


/*****************************************************************************
 结构名    : SOC_PMCTRL_VSENSOR_CALI_CODE_0_UNION
 结构说明  : VSENSOR_CALI_CODE_0 寄存器结构定义。地址偏移量:0x408，初值:0x00000000，宽度:32
 寄存器说明: Vsensor抽头控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  maia_vs_cali_code       : 7;  /* bit[0-6]  : maia Vsensor抽头校准码字 */
        unsigned int  reserved_0              : 1;  /* bit[7-7]  : 保留 */
        unsigned int  maia_svfd_off_mode      : 1;  /* bit[8-8]  : 1'b0：直接降频；
                                                                   1'b1：逐级降频； */
        unsigned int  maia_svfd_div64_en      : 1;  /* bit[9-9]  : 使能信号，工作模式不翻转 */
        unsigned int  maia_svfd_vdm_period    : 1;  /* bit[10-10]: 电压检测采样周期
                                                                   1'b0：1cycle；
                                                                   1'b1：2cycle； */
        unsigned int  maia_svfd_edge_sel      : 1;  /* bit[11-11]: 1'b0：上升沿检测； 
                                                                   1'b1：双沿检测（上升沿+下降沿） */
        unsigned int  maia_svfd_cmp_data_mode : 2;  /* bit[12-13]: CPM码字的输出模式：
                                                                   00：直接输出
                                                                   01：最小值输出
                                                                   10：最大值输出
                                                                   11：不翻转 */
        unsigned int  maia_svfd_data_limit_e  : 1;  /* bit[14-14]: 极限值输出状态下，使能信号；
                                                                   1'b0：清除前一次求值；
                                                                   1'b1：使能极限求值； */
        unsigned int  maia_svfd_glitch_test   : 1;  /* bit[15-15]: Glitch测试使能; */
        unsigned int  maia_svfd_out_div_sel   : 4;  /* bit[16-19]: CPM码字分频输出选择 */
        unsigned int  reserved_1              : 1;  /* bit[20-20]: 保留 */
        unsigned int  sel_ckmux_maia_icg      : 1;  /* bit[21-21]: 时钟选择源头：
                                                                   1'b0：CRG直接输出的时钟
                                                                   1'b1：SVFD输出的时钟 */
        unsigned int  reserved_2              : 1;  /* bit[22-22]: 保留 */
        unsigned int  maia_ext_ref_code       : 7;  /* bit[23-29]: maia ref_code的高bit，配合ref_code_h和ref_code_l一起使用，与采样累加次数相关 */
        unsigned int  maia_compare_mod        : 2;  /* bit[30-31]: A53数据比较模式：
                                                                   00：采样后的数据直接与ref_code比较
                                                                   01：采样后32次累加数据与ref_code比较
                                                                   10：采样后64次累加数据与ref_code比较
                                                                   11：采样后128次累加数据与ref_code比较 */
    } reg;
} SOC_PMCTRL_VSENSOR_CALI_CODE_0_UNION;
#endif
#define SOC_PMCTRL_VSENSOR_CALI_CODE_0_maia_vs_cali_code_START        (0)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_0_maia_vs_cali_code_END          (6)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_0_maia_svfd_off_mode_START       (8)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_0_maia_svfd_off_mode_END         (8)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_0_maia_svfd_div64_en_START       (9)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_0_maia_svfd_div64_en_END         (9)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_0_maia_svfd_vdm_period_START     (10)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_0_maia_svfd_vdm_period_END       (10)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_0_maia_svfd_edge_sel_START       (11)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_0_maia_svfd_edge_sel_END         (11)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_0_maia_svfd_cmp_data_mode_START  (12)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_0_maia_svfd_cmp_data_mode_END    (13)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_0_maia_svfd_data_limit_e_START   (14)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_0_maia_svfd_data_limit_e_END     (14)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_0_maia_svfd_glitch_test_START    (15)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_0_maia_svfd_glitch_test_END      (15)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_0_maia_svfd_out_div_sel_START    (16)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_0_maia_svfd_out_div_sel_END      (19)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_0_sel_ckmux_maia_icg_START       (21)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_0_sel_ckmux_maia_icg_END         (21)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_0_maia_ext_ref_code_START        (23)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_0_maia_ext_ref_code_END          (29)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_0_maia_compare_mod_START         (30)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_0_maia_compare_mod_END           (31)


/*****************************************************************************
 结构名    : SOC_PMCTRL_VSENSOR_CODE_0_UNION
 结构说明  : VSENSOR_CODE_0 寄存器结构定义。地址偏移量:0x40C，初值:0x00000000，宽度:32
 寄存器说明: Vsensor码字寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  maia_vs_code : 6;  /* bit[0-5] : maia Vsensor码字 */
        unsigned int  reserved     : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_PMCTRL_VSENSOR_CODE_0_UNION;
#endif
#define SOC_PMCTRL_VSENSOR_CODE_0_maia_vs_code_START  (0)
#define SOC_PMCTRL_VSENSOR_CODE_0_maia_vs_code_END    (5)


/*****************************************************************************
 结构名    : SOC_PMCTRL_VSENSOR_INTSTAT_0_UNION
 结构说明  : VSENSOR_INTSTAT_0 寄存器结构定义。地址偏移量:0x410，初值:0x00000000，宽度:32
 寄存器说明: Vsensor中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intr_vdm_stat_0 : 1;  /* bit[0-0] : Vsensor中断状态，写该寄存器。可清除VDM中的intr_vdm */
        unsigned int  dll_lock_0      : 1;  /* bit[1-1] : DLL lock指示寄存器。 */
        unsigned int  reserved        : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_PMCTRL_VSENSOR_INTSTAT_0_UNION;
#endif
#define SOC_PMCTRL_VSENSOR_INTSTAT_0_intr_vdm_stat_0_START  (0)
#define SOC_PMCTRL_VSENSOR_INTSTAT_0_intr_vdm_stat_0_END    (0)
#define SOC_PMCTRL_VSENSOR_INTSTAT_0_dll_lock_0_START       (1)
#define SOC_PMCTRL_VSENSOR_INTSTAT_0_dll_lock_0_END         (1)


/*****************************************************************************
 结构名    : SOC_PMCTRL_VSENSOR_D_RATE_0_UNION
 结构说明  : VSENSOR_D_RATE_0 寄存器结构定义。地址偏移量:0x414，初值:0x00000000，宽度:32
 寄存器说明: Vsensor中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  svfd_d_rate_0 : 2;  /* bit[0-1] : maia DLL调相速率
                                                        00 : 10%
                                                        01 : 20%
                                                        10 : 30%
                                                        11 : reseved */
        unsigned int  reserved      : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_PMCTRL_VSENSOR_D_RATE_0_UNION;
#endif
#define SOC_PMCTRL_VSENSOR_D_RATE_0_svfd_d_rate_0_START  (0)
#define SOC_PMCTRL_VSENSOR_D_RATE_0_svfd_d_rate_0_END    (1)


/*****************************************************************************
 结构名    : SOC_PMCTRL_PERIHPMEN_UNION
 结构说明  : PERIHPMEN 寄存器结构定义。地址偏移量:0x430，初值:0x00000000，宽度:32
 寄存器说明: PERI HPM使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_hpm_en : 1;  /* bit[0-0] : PERI HPM使能。 */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_PMCTRL_PERIHPMEN_UNION;
#endif
#define SOC_PMCTRL_PERIHPMEN_peri_hpm_en_START  (0)
#define SOC_PMCTRL_PERIHPMEN_peri_hpm_en_END    (0)


/*****************************************************************************
 结构名    : SOC_PMCTRL_PERIHPMXEN_UNION
 结构说明  : PERIHPMXEN 寄存器结构定义。地址偏移量:0x434，初值:0x00000000，宽度:32
 寄存器说明: PERI HPMX使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_hpmx_en : 1;  /* bit[0-0] : PERI HPMX使能。 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_PMCTRL_PERIHPMXEN_UNION;
#endif
#define SOC_PMCTRL_PERIHPMXEN_peri_hpmx_en_START  (0)
#define SOC_PMCTRL_PERIHPMXEN_peri_hpmx_en_END    (0)


/*****************************************************************************
 结构名    : SOC_PMCTRL_PERIHPMOPCVALID_UNION
 结构说明  : PERIHPMOPCVALID 寄存器结构定义。地址偏移量:0x438，初值:0x00000000，宽度:32
 寄存器说明: PERI HPM OPC有效寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_hpm_opc_vld  : 1;  /* bit[0-0] : PERI HPM原始性能码有效的状态指示。 */
        unsigned int  peri_hpmx_opc_vld : 1;  /* bit[1-1] : PERI HPMX原始性能码有效的状态指示。 */
        unsigned int  reserved          : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_PMCTRL_PERIHPMOPCVALID_UNION;
#endif
#define SOC_PMCTRL_PERIHPMOPCVALID_peri_hpm_opc_vld_START   (0)
#define SOC_PMCTRL_PERIHPMOPCVALID_peri_hpm_opc_vld_END     (0)
#define SOC_PMCTRL_PERIHPMOPCVALID_peri_hpmx_opc_vld_START  (1)
#define SOC_PMCTRL_PERIHPMOPCVALID_peri_hpmx_opc_vld_END    (1)


/*****************************************************************************
 结构名    : SOC_PMCTRL_PERIHPMOPC_UNION
 结构说明  : PERIHPMOPC 寄存器结构定义。地址偏移量:0x43C，初值:0x00000000，宽度:32
 寄存器说明: PERI HPM OPC寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_hpm_opc  : 10; /* bit[0-9]  : PERI HPM原始性能码。 */
        unsigned int  peri_hpmx_opc : 10; /* bit[10-19]: PERI HPMX原始性能码。 */
        unsigned int  reserved      : 12; /* bit[20-31]: 保留 */
    } reg;
} SOC_PMCTRL_PERIHPMOPC_UNION;
#endif
#define SOC_PMCTRL_PERIHPMOPC_peri_hpm_opc_START   (0)
#define SOC_PMCTRL_PERIHPMOPC_peri_hpm_opc_END     (9)
#define SOC_PMCTRL_PERIHPMOPC_peri_hpmx_opc_START  (10)
#define SOC_PMCTRL_PERIHPMOPC_peri_hpmx_opc_END    (19)


/*****************************************************************************
 结构名    : SOC_PMCTRL_PERIHPMCLKDIV_UNION
 结构说明  : PERIHPMCLKDIV 寄存器结构定义。地址偏移量:0x440，初值:0x00000001，宽度:32
 寄存器说明: PERI HPM时钟分频寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_hpm_clk_div : 6;  /* bit[0-5] : PERI HPM时钟分频器。 */
        unsigned int  reserved         : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_PMCTRL_PERIHPMCLKDIV_UNION;
#endif
#define SOC_PMCTRL_PERIHPMCLKDIV_peri_hpm_clk_div_START  (0)
#define SOC_PMCTRL_PERIHPMCLKDIV_peri_hpm_clk_div_END    (5)


/*****************************************************************************
 结构名    : SOC_PMCTRL_BOOTROMFLAG_UNION
 结构说明  : BOOTROMFLAG 寄存器结构定义。地址偏移量:0x460，初值:0x00000000，宽度:32
 寄存器说明: BOOTROM FLAG寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bootrom_flag : 1;  /* bit[0-0] : BOOTROM启动时，每一次指令操作翻转该bit，用于test输出。 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_PMCTRL_BOOTROMFLAG_UNION;
#endif
#define SOC_PMCTRL_BOOTROMFLAG_bootrom_flag_START  (0)
#define SOC_PMCTRL_BOOTROMFLAG_bootrom_flag_END    (0)


/*****************************************************************************
 结构名    : SOC_PMCTRL_VSENSOR_CTRL_EN_2_UNION
 结构说明  : VSENSOR_CTRL_EN_2 寄存器结构定义。地址偏移量:0x464，初值:0x00000000，宽度:32
 寄存器说明: Vsensor控制使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vs_ctrl_en_2 : 1;  /* bit[0-0] : G3D Vsensor控制使能：
                                                       0：Vsensor不使能；
                                                       1：Vsensor使能 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_PMCTRL_VSENSOR_CTRL_EN_2_UNION;
#endif
#define SOC_PMCTRL_VSENSOR_CTRL_EN_2_vs_ctrl_en_2_START  (0)
#define SOC_PMCTRL_VSENSOR_CTRL_EN_2_vs_ctrl_en_2_END    (0)


/*****************************************************************************
 结构名    : SOC_PMCTRL_VSENSOR_CTRL_BYPASS_2_UNION
 结构说明  : VSENSOR_CTRL_BYPASS_2 寄存器结构定义。地址偏移量:0x468，初值:0x00000001，宽度:32
 寄存器说明: Vsensor bypass寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vs_ctrl_bypass_2 : 1;  /* bit[0-0] : G3D Vsensor bypass信号：
                                                           0：Vsensor控制逻辑输出门控信号控制ICG；
                                                           1：Vsensor控制逻辑bypass，门控信号一直为1 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_PMCTRL_VSENSOR_CTRL_BYPASS_2_UNION;
#endif
#define SOC_PMCTRL_VSENSOR_CTRL_BYPASS_2_vs_ctrl_bypass_2_START  (0)
#define SOC_PMCTRL_VSENSOR_CTRL_BYPASS_2_vs_ctrl_bypass_2_END    (0)


/*****************************************************************************
 结构名    : SOC_PMCTRL_VSENSOR_CTRL_2_UNION
 结构说明  : VSENSOR_CTRL_2 寄存器结构定义。地址偏移量:0x46C，初值:0x00000000，宽度:32
 寄存器说明: Vsensor控制配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vs_mod_g3d          : 1;  /* bit[0-0]  : G3D Vsensor模式：
                                                               0：非中断模式
                                                               1：中断模式 */
        unsigned int  g3d_pwrdiv_bypass   : 1;  /* bit[1-1]  : G3D主动防御的bypass
                                                               1'b1:bypass;
                                                               1'b0:使能 */
        unsigned int  reserved            : 6;  /* bit[2-7]  : 保留 */
        unsigned int  svfd_test_in_2      : 4;  /* bit[8-11] : 预留测试输入PIN */
        unsigned int  svfd_ulvt_ll_2      : 4;  /* bit[12-15]: ULVT长线级联，级数配置PIN */
        unsigned int  svfd_ulvt_sl_2      : 4;  /* bit[16-19]: ULVT短线级联，级数配置PIN */
        unsigned int  svfd_lvt_ll_2       : 4;  /* bit[20-23]: LVT长线级联，级数配置PIN */
        unsigned int  svfd_lvt_sl_2       : 4;  /* bit[24-27]: LVT短线级联，级数配置PIN */
        unsigned int  svfd_vdm_mode_2     : 2;  /* bit[28-29]: 电压检测模式选择：
                                                               00 :reserve 
                                                               01 : IP内部电压检测(CPM)
                                                               10 : IP外部电压检测(VDM)
                                                               11 :VDM+CPM */
        unsigned int  svfd_match_detect_2 : 1;  /* bit[30-30]: 匹配达标检测使能，1有效；
                                                               工作状态，要保持为0；
                                                               用于DFT量产筛选 */
        unsigned int  svfd_trim_2         : 1;  /* bit[31-31]: 保留 */
    } reg;
} SOC_PMCTRL_VSENSOR_CTRL_2_UNION;
#endif
#define SOC_PMCTRL_VSENSOR_CTRL_2_vs_mod_g3d_START           (0)
#define SOC_PMCTRL_VSENSOR_CTRL_2_vs_mod_g3d_END             (0)
#define SOC_PMCTRL_VSENSOR_CTRL_2_g3d_pwrdiv_bypass_START    (1)
#define SOC_PMCTRL_VSENSOR_CTRL_2_g3d_pwrdiv_bypass_END      (1)
#define SOC_PMCTRL_VSENSOR_CTRL_2_svfd_test_in_2_START       (8)
#define SOC_PMCTRL_VSENSOR_CTRL_2_svfd_test_in_2_END         (11)
#define SOC_PMCTRL_VSENSOR_CTRL_2_svfd_ulvt_ll_2_START       (12)
#define SOC_PMCTRL_VSENSOR_CTRL_2_svfd_ulvt_ll_2_END         (15)
#define SOC_PMCTRL_VSENSOR_CTRL_2_svfd_ulvt_sl_2_START       (16)
#define SOC_PMCTRL_VSENSOR_CTRL_2_svfd_ulvt_sl_2_END         (19)
#define SOC_PMCTRL_VSENSOR_CTRL_2_svfd_lvt_ll_2_START        (20)
#define SOC_PMCTRL_VSENSOR_CTRL_2_svfd_lvt_ll_2_END          (23)
#define SOC_PMCTRL_VSENSOR_CTRL_2_svfd_lvt_sl_2_START        (24)
#define SOC_PMCTRL_VSENSOR_CTRL_2_svfd_lvt_sl_2_END          (27)
#define SOC_PMCTRL_VSENSOR_CTRL_2_svfd_vdm_mode_2_START      (28)
#define SOC_PMCTRL_VSENSOR_CTRL_2_svfd_vdm_mode_2_END        (29)
#define SOC_PMCTRL_VSENSOR_CTRL_2_svfd_match_detect_2_START  (30)
#define SOC_PMCTRL_VSENSOR_CTRL_2_svfd_match_detect_2_END    (30)
#define SOC_PMCTRL_VSENSOR_CTRL_2_svfd_trim_2_START          (31)
#define SOC_PMCTRL_VSENSOR_CTRL_2_svfd_trim_2_END            (31)


/*****************************************************************************
 结构名    : SOC_PMCTRL_VSENSOR_CNT_2_UNION
 结构说明  : VSENSOR_CNT_2 寄存器结构定义。地址偏移量:0x470，初值:0x00000000，宽度:32
 寄存器说明: Vsensor计数控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vs_cnt_quit_2  : 16; /* bit[0-15] : 退出门控延时，每次进入门控后，会等待相应时间后再次进行电压判断（非中断模式有用） */
        unsigned int  vs_cnt_enter_2 : 16; /* bit[16-31]: 进入门控延时，每次退出门控后，会等待相应时间后再次进行电压判断。 */
    } reg;
} SOC_PMCTRL_VSENSOR_CNT_2_UNION;
#endif
#define SOC_PMCTRL_VSENSOR_CNT_2_vs_cnt_quit_2_START   (0)
#define SOC_PMCTRL_VSENSOR_CNT_2_vs_cnt_quit_2_END     (15)
#define SOC_PMCTRL_VSENSOR_CNT_2_vs_cnt_enter_2_START  (16)
#define SOC_PMCTRL_VSENSOR_CNT_2_vs_cnt_enter_2_END    (31)


/*****************************************************************************
 结构名    : SOC_PMCTRL_VSENSOR_REF_CODE_2_UNION
 结构说明  : VSENSOR_REF_CODE_2 寄存器结构定义。地址偏移量:0x474，初值:0x00000000，宽度:32
 寄存器说明: Vsensor参考码字寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_vs_ref_code_l         : 6;  /* bit[0-5]  : G3D进入门控码字 */
        unsigned int  g3d_vs_ref_code_h         : 6;  /* bit[6-11] : G3D退出门控码字 */
        unsigned int  g3d_cfg_cnt_cpu_wake_quit : 8;  /* bit[12-19]: G3D主动防御退出超时；计数周期为VDM工作时钟； */
        unsigned int  reserved_0                : 8;  /* bit[20-27]: 保留 */
        unsigned int  g3d_wake_up_mode          : 2;  /* bit[28-29]: G3D主动防御模式；
                                                                     2'b00:开启主动防御;
                                                                     其他:关闭主动防御; */
        unsigned int  reserved_1                : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_PMCTRL_VSENSOR_REF_CODE_2_UNION;
#endif
#define SOC_PMCTRL_VSENSOR_REF_CODE_2_g3d_vs_ref_code_l_START          (0)
#define SOC_PMCTRL_VSENSOR_REF_CODE_2_g3d_vs_ref_code_l_END            (5)
#define SOC_PMCTRL_VSENSOR_REF_CODE_2_g3d_vs_ref_code_h_START          (6)
#define SOC_PMCTRL_VSENSOR_REF_CODE_2_g3d_vs_ref_code_h_END            (11)
#define SOC_PMCTRL_VSENSOR_REF_CODE_2_g3d_cfg_cnt_cpu_wake_quit_START  (12)
#define SOC_PMCTRL_VSENSOR_REF_CODE_2_g3d_cfg_cnt_cpu_wake_quit_END    (19)
#define SOC_PMCTRL_VSENSOR_REF_CODE_2_g3d_wake_up_mode_START           (28)
#define SOC_PMCTRL_VSENSOR_REF_CODE_2_g3d_wake_up_mode_END             (29)


/*****************************************************************************
 结构名    : SOC_PMCTRL_VSENSOR_CALI_CODE_2_UNION
 结构说明  : VSENSOR_CALI_CODE_2 寄存器结构定义。地址偏移量:0x478，初值:0x00000000，宽度:32
 寄存器说明: Vsensor抽头控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_vs_cali_code       : 7;  /* bit[0-6]  : G3D Vsensor抽头校准码字。 */
        unsigned int  reserved_0             : 1;  /* bit[7-7]  : 保留 */
        unsigned int  g3d_svfd_off_mode      : 1;  /* bit[8-8]  : 1'b0：直接降频；
                                                                  1'b1：逐级降频； */
        unsigned int  g3d_svfd_div64_en      : 1;  /* bit[9-9]  : 使能信号，工作模式不翻转 */
        unsigned int  g3d_svfd_vdm_period    : 1;  /* bit[10-10]: 电压检测采样周期
                                                                  1'b0：1cycle；
                                                                  1'b1：2cycle； */
        unsigned int  g3d_svfd_edge_sel      : 1;  /* bit[11-11]: 1'b0：上升沿检测； 
                                                                  1'b1：双沿检测（上升沿+下降沿） */
        unsigned int  g3d_svfd_cmp_data_mode : 2;  /* bit[12-13]: CPM码字的输出模式：
                                                                  00：直接输出
                                                                  01：最小值输出
                                                                  10：最大值输出
                                                                  11：不翻转 */
        unsigned int  g3d_svfd_data_limit_e  : 1;  /* bit[14-14]: 极限值输出状态下，使能信号；
                                                                  1'b0：清除前一次求值；
                                                                  1'b1：使能极限求值； */
        unsigned int  g3d_svfd_glitch_test   : 1;  /* bit[15-15]: Glitch测试使能; */
        unsigned int  g3d_svfd_out_div_sel   : 4;  /* bit[16-19]: CPM码字分频输出选择 */
        unsigned int  reserved_1             : 1;  /* bit[20-20]: 保留 */
        unsigned int  sel_ckmux_gpu_icg      : 1;  /* bit[21-21]: 时钟选择源头：
                                                                  1'b0：CRG直接输出的时钟
                                                                  1'b1：SVFD输出的时钟 */
        unsigned int  reserved_2             : 10; /* bit[22-31]: 保留 */
    } reg;
} SOC_PMCTRL_VSENSOR_CALI_CODE_2_UNION;
#endif
#define SOC_PMCTRL_VSENSOR_CALI_CODE_2_g3d_vs_cali_code_START        (0)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_2_g3d_vs_cali_code_END          (6)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_2_g3d_svfd_off_mode_START       (8)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_2_g3d_svfd_off_mode_END         (8)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_2_g3d_svfd_div64_en_START       (9)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_2_g3d_svfd_div64_en_END         (9)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_2_g3d_svfd_vdm_period_START     (10)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_2_g3d_svfd_vdm_period_END       (10)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_2_g3d_svfd_edge_sel_START       (11)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_2_g3d_svfd_edge_sel_END         (11)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_2_g3d_svfd_cmp_data_mode_START  (12)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_2_g3d_svfd_cmp_data_mode_END    (13)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_2_g3d_svfd_data_limit_e_START   (14)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_2_g3d_svfd_data_limit_e_END     (14)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_2_g3d_svfd_glitch_test_START    (15)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_2_g3d_svfd_glitch_test_END      (15)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_2_g3d_svfd_out_div_sel_START    (16)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_2_g3d_svfd_out_div_sel_END      (19)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_2_sel_ckmux_gpu_icg_START       (21)
#define SOC_PMCTRL_VSENSOR_CALI_CODE_2_sel_ckmux_gpu_icg_END         (21)


/*****************************************************************************
 结构名    : SOC_PMCTRL_VSENSOR_CODE_2_UNION
 结构说明  : VSENSOR_CODE_2 寄存器结构定义。地址偏移量:0x47C，初值:0x00000000，宽度:32
 寄存器说明: Vsensor码字寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_vs_code : 6;  /* bit[0-5] : G3D Vsensor码字。 */
        unsigned int  reserved    : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_PMCTRL_VSENSOR_CODE_2_UNION;
#endif
#define SOC_PMCTRL_VSENSOR_CODE_2_g3d_vs_code_START  (0)
#define SOC_PMCTRL_VSENSOR_CODE_2_g3d_vs_code_END    (5)


/*****************************************************************************
 结构名    : SOC_PMCTRL_VSENSOR_INTSTAT_2_UNION
 结构说明  : VSENSOR_INTSTAT_2 寄存器结构定义。地址偏移量:0x480，初值:0x00000000，宽度:32
 寄存器说明: Vsensor中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intr_vdm_stat_2 : 1;  /* bit[0-0] : Vsensor中断状态，写该寄存器。可清除VDM中的intr_vdm。 */
        unsigned int  dll_lock_2      : 1;  /* bit[1-1] : DLL lock指示寄存器。 */
        unsigned int  reserved        : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_PMCTRL_VSENSOR_INTSTAT_2_UNION;
#endif
#define SOC_PMCTRL_VSENSOR_INTSTAT_2_intr_vdm_stat_2_START  (0)
#define SOC_PMCTRL_VSENSOR_INTSTAT_2_intr_vdm_stat_2_END    (0)
#define SOC_PMCTRL_VSENSOR_INTSTAT_2_dll_lock_2_START       (1)
#define SOC_PMCTRL_VSENSOR_INTSTAT_2_dll_lock_2_END         (1)


/*****************************************************************************
 结构名    : SOC_PMCTRL_VSENSOR_D_RATE_2_UNION
 结构说明  : VSENSOR_D_RATE_2 寄存器结构定义。地址偏移量:0x484，初值:0x00000000，宽度:32
 寄存器说明: Vsensor中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  svfd_d_rate_2 : 2;  /* bit[0-1] : G3D DLL调相速率。
                                                        00 : 10%
                                                        01 : 20%
                                                        10 : 30%
                                                        11 : reseved */
        unsigned int  reserved      : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_PMCTRL_VSENSOR_D_RATE_2_UNION;
#endif
#define SOC_PMCTRL_VSENSOR_D_RATE_2_svfd_d_rate_2_START  (0)
#define SOC_PMCTRL_VSENSOR_D_RATE_2_svfd_d_rate_2_END    (1)






/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/



/*****************************************************************************
  9 全局变量声明
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of soc_pmctrl_interface.h */
