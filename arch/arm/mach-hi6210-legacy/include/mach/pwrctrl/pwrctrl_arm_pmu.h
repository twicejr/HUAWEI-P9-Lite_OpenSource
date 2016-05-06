/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : pwc_arm_pmu.h
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

******************************************************************************/

#ifndef _PWC_ARM_PMU_H
#define _PWC_ARM_PMU_H

#include "pwrctrl_common.h"

/**
 *  ACPU ARM PMU APB ADDR.
 */
#ifdef CHIP_BB_HI6210
#define ARM_PMU_ACPU0_ADDR                      (0xF6591000)
#define ARM_PMU_ACPU1_ADDR                      (0xF6593000)
#define ARM_PMU_ACPU2_ADDR                      (0xF6595000)
#define ARM_PMU_ACPU3_ADDR                      (0xF6597000)
#else 
#define ARM_PMU_ACPU0_ADDR                      (0xF6511000)
#define ARM_PMU_ACPU1_ADDR                      (0xF6513000)
#define ARM_PMU_ACPU2_ADDR                      (0xF6515000)
#define ARM_PMU_ACPU3_ADDR                      (0xF6517000)
#endif

#define ARM_PMU_ACPU_SIZE                       (0x2000)
#define ARM_ACPU_CORE_NUM                       (0x4)



// These functions are used to get common cpu load.
// Generally, they are what you really want. : )
extern void arm_cpuload_disable(u32_t pmu_apb_base);
extern void arm_cpuload_enable(u32_t pmu_apb_base);
extern void arm_cpuload_init(u32_t pmu_apb_base);
extern void arm_cpuload_reset(u32_t pmu_apb_base);
// arm_cpuload_read, return: cpu load (>=0) or error (-1).
extern s32_t arm_cpuload_read(u32_t pmu_apb_base, u32_t ccnt);

// Global PMU init. Should be called before doing any PMU operations.
extern void arm_pmu_init(u32_t pmu_apb_base);

// Global PMU enable
// On ARM11 this enables the PMU, and the counters start immediately
// On Cortex this enables the PMU, there are individual enables for the counters
extern void arm_pmu_enable(u32_t pmu_apb_base);

// Global PMU disable
// On Cortex, this overrides the enable state of the individual counters
extern void arm_pmu_disable(u32_t pmu_apb_base);

// Sets the event for a programmable counter to record
// counter = r0 = Which counter to program  (e.g. 0 for PMN0, 1 for PMN1)
// event   = r1 = The event code (from appropiate TRM or ARM Architecture Reference Manual)
extern void arm_pmu_config_pmn(u32_t pmu_apb_base, u32_t counter, u32_t event);

// Enable PMN{n}
// counter = The counter to enable (e.g. 0 for PMN0, 1 for PMN1)
extern void arm_pmu_enable_pmn(u32_t pmu_apb_base, u32_t counter);

// Enable PMN{n}
// counter = The counter to enable (e.g. 0 for PMN0, 1 for PMN1)
extern void arm_pmu_disable_pmn(u32_t pmu_apb_base, u32_t counter);

// Resets the programmable counter
extern void arm_pmu_reset_pmn(u32_t pmu_apb_base, u32_t counter);

// Returns the value of PMN{n}
// counter = The counter to read (e.g. 0 for PMN0, 1 for PMN1)
extern u32_t arm_pmu_read_pmn(u32_t pmu_apb_base, u32_t counter);

// Enable the CCNT
extern void arm_pmu_enable_ccnt(u32_t pmu_apb_base);

// Disable the CCNT
extern void arm_pmu_disable_ccnt(u32_t pmu_apb_base);

// Resets the CCNT
extern void arm_pmu_reset_ccnt(u32_t pmu_apb_base);

// Returns the value of CCNT
extern u32_t arm_pmu_read_ccnt(u32_t pmu_apb_base);

#endif
