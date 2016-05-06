#ifndef __CPUFREQ_API_H__
#define __CPUFREQ_API_H__

#include "osl_types.h"
#include "soc_memmap.h"
#include "soc_clk.h"
#include "soc_interrupts.h"
#include <irq.h>
#include <soc_memmap.h>

#include <bsp_sram.h>

#define CPUFREQ_MAX_PROFILE    8
#define CPUFREQ_MIN_PROFILE    0
#define CPUFREQ_MAX_PLL        3

#define CPUFREQ_DDRC_PACK_BASE_ADDR     0x9004E000
#define CPUFREQ_DDRC_DMC_BASE_ADDR      0x90048000
#define CPUFREQ_DDRC_PHY_ACDX_BASE_ADDR 0x9004F000
#define CPUFREQ_SC_BASE_ADDR            HI_PD_CRG_BASE_ADDR

/* PD_CRG */
#define CPUFREQ_PD_CRG_CLKEN4    0x30
#define CPUFREQ_PD_CRG_CLKDIS4   0x34
#define CPUFREQ_PD_CRG_CLK_SEL2  0x144
#define CPUFREQ_PD_CRG_CLKDIV2   0x104
#define CPUFREQ_CRG_DFS1_CTRL1   0x200
#define CPUFREQ_CRG_DFS1_CTRL2   0x204
#define CPUFREQ_CRG_DFS1_CTRL3   0x208
#define CPUFREQ_DDRC_CTRL_SREF   0x000
#define CPUFREQ_DDRC_CFG_SREF    0x020
#define CPUFREQ_DDRC_CFG_NXT_TIMING0 0x120
#define CPUFREQ_DDRC_CFG_NXT_TIMING1 0x124
#define CPUFREQ_DDRC_CFG_NXT_TIMING2 0x128
#define CPUFREQ_DDRC_CFG_NXT_TIMING3 0x12C
#define CPUFREQ_DDRC_CFG_NXT_TIMING4 0x130
#define CPUFREQ_DDRC_CFG_NXT_TIMING5 0x134
#define CPUFREQ_DDRC_CFG_NXT_TIMING6 0x138
#define CPUFREQ_DDRC_CFG_NXT_TIMING7 0x13C

#define CPUFREQ_PHYINITCTRL      0x004
#define CPUFREQ_PHYCLKGATED      0x000C
#define CPUFREQ_PLLCTRL          0x018
#define CPUFREQ_DRAMTIMER0       0x030
#define CPUFREQ_DRAMTIMER1       0x034
#define CPUFREQ_DRAMTIMER2       0x038
#define CPUFREQ_DRAMTIMER3       0x03C
#define CPUFREQ_DRAMTIMER4       0x040
#define CPUFREQ_DRAMTIMER5       0x0BC

#define CPUFREQ_MISC             0x0070
#define CPUFREQ_RETCTRL0         0x0080
#define CPUFREQ_DMSEL            0x0084
#define CPUFREQ_PHYPLLCTRL_AC    0x98
#define CPUFREQ_PHYPLLCTRL_DX    0x9C

#define CPUFREQ_IOCTL3           0xFF0

#define CPUFREQ_REGBANKCTRL      0x0D8
#define CPUFREQ_ACADDRBDL0       0x140
#define CPUFREQ_ACADDRBDL1       0x144
#define CPUFREQ_ACADDRBDL2       0x148
#define CPUFREQ_ACADDRBDL3       0x14C
#define CPUFREQ_ACADDRBDL4       0x150
#define CPUFREQ_ACPHYCTL0        0x054
#define CPUFREQ_DXNMISCCTRL2     0x248
#define CPUFREQ_DXNDCC           0x250
#define CPUFREQ_ADDRPHBOUND      0x01D4
#define CPUFREQ_LPCTRL           0x01E4
#define CPUFREQ_DXNWDQNBDL0      0x210
#define CPUFREQ_DXNWDQNBDL1      0x214
#define CPUFREQ_DXNWDQNBDL2      0x218
#define CPUFREQ_DXNRDQNBDL0      0x21C
#define CPUFREQ_DXNRDQNBDL1      0x220
#define CPUFREQ_DXNOEBDL         0x228
#define CPUFREQ_DXNRDQSDLY       0x22C
#define CPUFREQ_DXNWDQSDLY       0x230
#define CPUFREQ_DXNWDQDLY        0x234
#define CPUFREQ_DXNWLSL          0x238
#define CPUFREQ_DXNGDS           0x23C
#define CPUFREQ_DXNRDQSGDLY      0x240
#define CPUFREQ_SC_PERI_CTRL4    0x810
#define CPUFREQ_SC_PERI_STAT30   0XA78
#define CPUFREQ_SC_TOP_CTRL21    0X454

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
	s32 ddrvalue;
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
	u32 nxttiming4;
	u32 nxttiming5;
	u32 nxttiming6;
	u32 nxttiming7;
}T_CPUFREQ_DDRC_TIMING;

typedef struct {
	u32	dramtimer0;
	u32 dramtimer1;
	u32 dramtimer2;
	u32 dramtimer3;
	u32 dramtimer4;
	u32 dramtimer5;
	u32 misc;
	u32 dmsel;
	u32 ioctl3;
}T_CPUFREQ_DDRC_TIMER;

extern void dfs_set_profile(u32 profile);
extern u32 dfs_get_profile(void);
extern void dfs_ddrc_calc(void);
extern s32 dfs_get_cur_mode(u32 *cur_ddr);

#endif

