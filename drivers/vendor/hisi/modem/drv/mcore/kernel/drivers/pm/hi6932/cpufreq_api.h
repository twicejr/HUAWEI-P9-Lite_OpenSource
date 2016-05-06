#ifndef __CPUFREQ_API_H__
#define __CPUFREQ_API_H__

#include "osl_types.h"
#include "soc_memmap.h"
#include "soc_clk.h"
#include "soc_interrupts.h"
#include <irq.h>
#include <soc_memmap.h>

#include <bsp_sram.h>

#define CPUFREQ_MAX_PROFILE    7
#define CPUFREQ_MIN_PROFILE    0
#define CPUFREQ_MAX_PLL        1

#define HI_CM3_LP_PWRCTRL0       (0xE0044020)
#define HI_CM3_DDRC_BASE_ADDR    (0xE0046000)
#define HI_CM3_CRG_BASE_ADDR     (0xE0045000)
#define HI_CRG_BASE_ADDR         (0x90000000)


#define HI_MDDRC_SREFCTRL_OFFSET        (0x4)
#define HI_CRG_CLKDIV2_OFFSET           (0x104)
#define HI_CRG_CLKEN4_OFFSET            (0x30)
#define HI_CRG_CLK_SEL2_OFFSET          (0x144)
#define HI_CRG_DFS1_CTRL3_OFFSET        (0x208)
#define HI_CRG_DFS1_CTRL1_OFFSET        (0x200)
#define HI_CRG_DFS1_CTRL2_OFFSET        (0x204)
#define HI_CRG_CLKDIS4_OFFSET           (0x34)
#define HI_CRG_SSRSTEN1_OFFSET           (0x360)
#define HI_CRG_SSRSTDIS1_OFFSET          (0x364)

enum ddr_mode{
    bypass_mode = 0,    /* ddr <= 400M */
    mission_mode = 1,
};

/* ddr freq = fast bus freq 
    ddr freq <=400   bypass mode
    ddr freq > 400   mission mode
*/

typedef struct {
	u32	pll;
	u32 clkdiv;
}T_CPUFREQ_PROFILE;

typedef struct {
	u32	dfs1ctrl1;
	u32 dfs1ctrl2;
}T_CPUFREQ_PLL_CONFIG;


typedef struct {
	u32	nxttiming0;
	u32 nxttiming1;
	u32 nxttiming2;
	u32 nxttiming3;
}T_CPUFREQ_DDRC_TIMING;

typedef struct {
	u32 ddr_reg_83c;
	u32 ddr_reg_abc;
	u32 ddr_reg_b3c;
	u32 ddr_reg_bbc;
	u32 ddr_reg_c3c;
}T_CPUFREQ_DDRC_CALC;

void dfs_set_profile(u32 profile);
u32 dfs_get_profile(void);
void dfs_ddrc_calc(void);
s32 dfs_get_cur_mode(u32 *cur_ddr);


#endif

