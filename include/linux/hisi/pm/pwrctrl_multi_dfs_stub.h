#ifndef __PWRCTRL_MULTI_DFS_STUB_H__
#define __PWRCTRL_MULTI_DFS_STUB_H__

/*
 *  Stub Includes
 */
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

/*
 *  Platform Types
 */
#define BSP_NULL               (0)
#define BSP_OK                 (0)
#define BSP_ERR                (-1)

/*
 * Address & Register
 */
extern unsigned int* g_dummy_soc_mem;

#ifdef SOC_SC_ON_BASE_ADDR
#undef SOC_SC_ON_BASE_ADDR
#endif
#define SOC_SC_ON_BASE_ADDR             (unsigned int)(g_dummy_soc_mem)

#ifdef SOC_SC_OFF_BASE_ADDR
#undef SOC_SC_OFF_BASE_ADDR
#endif
#define SOC_SC_OFF_BASE_ADDR             (unsigned int)(g_dummy_soc_mem)

#ifdef SOC_PMCTRL_BASE_ADDR
#undef SOC_PMCTRL_BASE_ADDR
#endif
#define SOC_PMCTRL_BASE_ADDR            (unsigned int)(g_dummy_soc_mem)

#ifdef SOC_DDRC_BASE_ADDR
#undef SOC_DDRC_BASE_ADDR
#endif
#define SOC_DDRC_BASE_ADDR              (unsigned int)(g_dummy_soc_mem)

#ifdef ARM_PMU_ACPU0_ADDR
#undef ARM_PMU_ACPU0_ADDR
#endif
#define ARM_PMU_ACPU0_ADDR              (unsigned int)(g_dummy_soc_mem)

#ifdef ARM_PMU_ACPU1_ADDR
#undef ARM_PMU_ACPU1_ADDR
#endif
#define ARM_PMU_ACPU1_ADDR              (unsigned int)(g_dummy_soc_mem)

#ifdef ARM_PMU_ACPU2_ADDR
#undef ARM_PMU_ACPU2_ADDR
#endif
#define ARM_PMU_ACPU2_ADDR              (unsigned int)(g_dummy_soc_mem)

#ifdef ARM_PMU_ACPU3_ADDR
#undef ARM_PMU_ACPU3_ADDR
#endif
#define ARM_PMU_ACPU3_ADDR              (unsigned int)(g_dummy_soc_mem)

#ifdef ARM_PMU_CCPU0_ADDR
#undef ARM_PMU_CCPU0_ADDR
#endif
#define ARM_PMU_CCPU0_ADDR              (unsigned int)(g_dummy_soc_mem)

#endif
