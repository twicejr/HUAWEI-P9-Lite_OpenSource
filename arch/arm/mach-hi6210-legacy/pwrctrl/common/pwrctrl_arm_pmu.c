/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : pwrctrl_arm_pmu.h
  版 本 号   : 初稿
  作    者   : 黄星宇 212111
  生成日期   : 2012年8月2日
  最近修改   :
  功能描述   : ARMv7 PMU(Performance Monitoring Unit) APB Debug接口驱动
  函数列表   :
  修改历史   :
  1.日    期   : 2012年8月2日
    作    者   : 黄星宇 212111
    修改内容   : 创建文件

  2.日    期   : 2012年12月11日
    作    者   : 黄星宇 212111
    修改内容   : 添加cpuload接口
******************************************************************************/

#include <mach/pwrctrl/pwrctrl_arm_pmu.h>

/**
 *  ARM PMU registers APB address table.
 */
#define ARM_PMU_REG_EVT_CNT0      0x000
#define ARM_PMU_REG_EVT_CNT1      0x004
#define ARM_PMU_REG_EVT_CNT2      0x008
#define ARM_PMU_REG_EVT_CNT3      0x00C
#define ARM_PMU_REG_EVT_CNT4      0x010
#define ARM_PMU_REG_EVT_CNT5      0x014
#define ARM_PMU_REG_PMCCNTR       0x07C
#define ARM_PMU_REG_PMEVTYPER0    0x400
#define ARM_PMU_REG_PMEVTYPER1    0x404
#define ARM_PMU_REG_PMEVTYPER2    0x408
#define ARM_PMU_REG_PMEVTYPER3    0x40C
#define ARM_PMU_REG_PMEVTYPER4    0x410
#define ARM_PMU_REG_PMEVTYPER5    0x414
#define ARM_PMU_REG_PMCNTENSET    0xC00
#define ARM_PMU_REG_PMCNTENCLR    0xC20
#define ARM_PMU_REG_PMINTENSET    0xC40
#define ARM_PMU_REG_PMINTENCLR    0xC60
#define ARM_PMU_REG_PMOVSR        0xC80
#define ARM_PMU_REG_PMSWINC       0xCA0
#define ARM_PMU_REG_PMCR          0xE04
#define ARM_PMU_REG_PMUSERENR     0xE08
#define ARM_PMU_REG_PMITCTRL      0xF00
#define ARM_PMU_REG_PMCLAIMSET    0xFA0
#define ARM_PMU_REG_PMCLAIMCLR    0xFA4
#define ARM_PMU_REG_PMLAR         0xFB0
#define ARM_PMU_REG_PMLSR         0xFB4
#define ARM_PMU_REG_PMDEVID       0xFC8
#define ARM_PMU_REG_PMDEVTYPE     0xFCC
#define ARM_PMU_REG_EVT_CNT(x)    (ARM_PMU_REG_EVT_CNT0   + x * 0x4)
#define ARM_PMU_REG_PMEVTYPER(x)  (ARM_PMU_REG_PMEVTYPER0 + x * 0x4)

/**
 *  ARM PMU Operations.
 */
void arm_pmu_init(u32_t pmu_apb_base)
{
    // Check Debug register writes is permitted(locked)?
    if(pwrctrl_is_bits_set(pmu_apb_base + ARM_PMU_REG_PMLSR, BIT(1)))
    {
        // Write access if locked.
        pwrctrl_write_reg32(pmu_apb_base + ARM_PMU_REG_PMLAR, 0xC5ACCE55);
    }
}

void arm_pmu_enable(u32_t pmu_apb_base)
{
    pwrctrl_set_bits(pmu_apb_base + ARM_PMU_REG_PMCR, BIT(0));
}

void arm_pmu_disable(u32_t pmu_apb_base)
{
    pwrctrl_clr_bits(pmu_apb_base + ARM_PMU_REG_PMCR, BIT(0));
}

void arm_pmu_reset(u32_t pmu_apb_base)
{
    // Reset ccnt & pmn counters to zero.
    pwrctrl_set_bits(pmu_apb_base + ARM_PMU_REG_PMCR, BIT(1) | BIT(2));

    // Reset ccnt & pmn counters overflow flags to zero. (write 1 means clear)
    pwrctrl_write_reg32(pmu_apb_base + ARM_PMU_REG_PMOVSR, 0xFFFFFFFF);
}

void arm_pmu_config_pmn(u32_t pmu_apb_base, u32_t counter, u32_t event)
{
    pwrctrl_write_reg32(pmu_apb_base + ARM_PMU_REG_PMEVTYPER(counter), event);
}

void arm_pmu_enable_pmn(u32_t pmu_apb_base, u32_t counter)
{
    pwrctrl_set_bits(pmu_apb_base + ARM_PMU_REG_PMCNTENSET, BIT(counter));
}

void arm_pmu_disable_pmn(u32_t pmu_apb_base, u32_t counter)
{
    pwrctrl_set_bits(pmu_apb_base + ARM_PMU_REG_PMCNTENCLR, BIT(counter));
}

void arm_pmu_reset_pmn(u32_t pmu_apb_base, u32_t counter)
{
    // Reset pmn counter to 0. (not reset all pmn counter)
    pwrctrl_write_reg32(pmu_apb_base + ARM_PMU_REG_EVT_CNT(counter), 0);

    // Reset pmn counter overflow flag. (write 1 means clear)
    pwrctrl_set_bits(pmu_apb_base + ARM_PMU_REG_PMOVSR, BIT(counter));
}

u32_t arm_pmu_read_pmn(u32_t pmu_apb_base, u32_t counter)
{
    return pwrctrl_read_reg32(pmu_apb_base + ARM_PMU_REG_EVT_CNT(counter));
}

void arm_pmu_enable_ccnt(u32_t pmu_apb_base)
{
    pwrctrl_set_bits(pmu_apb_base + ARM_PMU_REG_PMCNTENSET, BIT(31));
}

void arm_pmu_disable_ccnt(u32_t pmu_apb_base)
{
    pwrctrl_set_bits(pmu_apb_base + ARM_PMU_REG_PMCNTENCLR, BIT(31));
}

void arm_pmu_reset_ccnt(u32_t pmu_apb_base)
{
    // Reset ccnt.
    pwrctrl_set_bits(pmu_apb_base + ARM_PMU_REG_PMCR, BIT(2));

    // Reset ccnt overflow flag. (write 1 means clear)
    pwrctrl_set_bits(pmu_apb_base + ARM_PMU_REG_PMOVSR, BIT(31));
}

u32_t arm_pmu_read_ccnt(u32_t pmu_apb_base)
{
    return pwrctrl_read_reg32(pmu_apb_base + ARM_PMU_REG_PMCCNTR);
}

/*
 * General CPU load functions.
 */
void arm_cpuload_init(u32_t pmu_apb_base)
{
    /* Init PMU */
    arm_pmu_init(pmu_apb_base);

    /* Config PMN. */
    arm_pmu_config_pmn(pmu_apb_base, 0, 0x8A);
    arm_pmu_config_pmn(pmu_apb_base, 1, 0x8B);
}

void arm_cpuload_enable(u32_t pmu_apb_base)
{
    /* Enable CCNT. */
    arm_pmu_enable_ccnt(pmu_apb_base);

    /* Enable PMN. */
    arm_pmu_enable_pmn(pmu_apb_base, 0);
    arm_pmu_enable_pmn(pmu_apb_base, 1);

    /* Enable PMU. */
    arm_pmu_enable(pmu_apb_base);
}

void arm_cpuload_disable(u32_t pmu_apb_base)
{
    /* Disable PMU. */
    arm_pmu_disable(pmu_apb_base);

    /* Disable PMN. */
    arm_pmu_disable_pmn(pmu_apb_base, 0);
    arm_pmu_disable_pmn(pmu_apb_base, 1);

    /* Disable CCNT. */
    arm_pmu_disable_ccnt(pmu_apb_base);
}

void arm_cpuload_reset(u32_t pmu_apb_base)
{
    /* Reset PMN. */
    arm_pmu_reset_pmn(pmu_apb_base, 0);
    arm_pmu_reset_pmn(pmu_apb_base, 1);

    /* Reset CCNT. */
    arm_pmu_reset_ccnt(pmu_apb_base);

    /* Reset All for safe. */
    arm_pmu_reset(pmu_apb_base);
}

s32_t arm_cpuload_read(u32_t pmu_apb_base, u32_t ccnt)
{
    u32_t pmn0 = 0;
    u32_t pmn1 = 0;

    pmn0 = arm_pmu_read_pmn(pmu_apb_base, 0);
    pmn1 = arm_pmu_read_pmn(pmu_apb_base, 1);
    //ccnt = arm_pmu_read_ccnt(pmu_apb_base);

    if(ccnt == 0)
        return -1;

    /* WARNING: The variable could be overflow when sampling rate > 2.6s (core
                rate: 1.5Ghz). Resolve this problem by check PMU overflow bit or
                enable 64 times per cycle function. */
    //return (s32_t)(10 * (pmn0 * 9 + pmn1 * 1) / ccnt);
    return (s32_t)(100 * (pmn0 + pmn1) / ccnt);
}