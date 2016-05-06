#include "m3boot.h"
#include <soc_onchiprom.h>
#include <hi_syscrg.h>
#include <hi_syssc.h>
#include <hi_pwrctrl.h>

	.syntax unified
	.thumb
	.text


/**************************************************************
*** sysctrl init  configuration
****************************************************************/
	.align 1
	.thumb_func
	.type    sysctrl_init, %function
	.global  sysctrl_init
sysctrl_init:
	/* pmu hold clear */
	ldr r0, =(HI_SYSSC_BASE_ADDR + HI_SC_CTRL1_OFFSET)
	ldr r1, [r0]
	orr r1, r1, #0x2
	str r1, [r0]

/**************************************************************
*** open all clk
****************************************************************/
	LDR R0, =0xFFFFFFFF
	LDR R1, =(HI_SYSCRG_BASE_ADDR + HI_CRG_CLKEN1_OFFSET)
	STR R0, [R1]
	LDR R1, =(HI_SYSCRG_BASE_ADDR + HI_CRG_CLKEN2_OFFSET)
	STR R0, [R1]
	LDR R1, =(HI_SYSCRG_BASE_ADDR + HI_CRG_CLKEN3_OFFSET)
	STR R0, [R1]
	LDR R1, =(HI_SYSCRG_BASE_ADDR + HI_CRG_CLKEN4_OFFSET)
	STR R0, [R1]
	LDR R1, =(HI_SYSCRG_BASE_ADDR + HI_CRG_CLKEN5_OFFSET)
	STR R0, [R1]
	LDR R0, =0x18
	LDR R1, =(HI_SYSCRG_BASE_ADDR + HI_CRG_CLKDIS5_OFFSET)
	STR R0, [R1]

/**************************************************************
*** clk init  configuration,must do in ASIC
****************************************************************/
	/*cfg system to slow state*/
	LDR R0, =(HI_PWRCTRL_BASE_ADDR + HI_PWR_CTRL0_OFFSET)
	LDR R1, [R0]
	BIC R1, R1, #0x7
	ORR R1, R1, #0x2
	STR R1, [R0]
WAIT_ARM_SLOW:
	LDR R1, [R0]
	AND R1, R1, #0x78
	CMP R1, #0x10
	BNE WAIT_ARM_SLOW

	/*ÉèÖÃNANDC Âö¿í*/
	ldr r0, =0x900a4004
	ldr r1, =0x888
	str r1,[r0]
	
	/* close peri/dsp0/hifi/bbp pll postdiv/fout */
	ldr r0, =(HI_SYSCRG_BASE_ADDR + HI_CRG_PLLLOCK_CTRL_OFFSET)
	ldr r1, =0x80000fff
	str r1,[r0]

	/* cfg freq div {a9_pll:app_a9:mdm_a9:fast_bus:slow_bus:apb = 1:2:2:4:4:8}*/
	/* a9:666m ; fast(ddr):333m ;slow:166m */
	ldr r0, =(HI_SYSCRG_BASE_ADDR + HI_CRG_CLKDIV2_OFFSET)    /* 0x0x90000104 */
	ldr r1, =0x40007733
	str r1, [r0]

	/* cfg cipher_clk div to 7 (cipher_clk = 960M/7 = 137M) */
	ldr r0, =(HI_SYSCRG_BASE_ADDR + HI_CRG_CLKDIV3_OFFSET)    /* 0x0x90000108 */ 
	ldr r1, =0x50104104
	str r1, [r0]
	
	/* MMC */
	ldr r0, =(HI_SYSCRG_BASE_ADDR + HI_CRG_MMC_CTRL_OFFSET)    /* 0x0x90000114 */ 
	ldr r1, =0x30022
	str r1, [r0]
	
	/* cfg a9_pll=667m, vco=1332m */
	ldr r1, =0x600000
	ldr r2, =0x2101045
	ldr r0, =(HI_SYSCRG_BASE_ADDR + HI_CRG_DFS1_CTRL1_OFFSET) /* 0x0x90000200 */
	stmia r0, {r1-r2}

	/* enable a9 dfs */
	ldr r1, =0x28
	ldr r0, =(HI_SYSCRG_BASE_ADDR + HI_CRG_DFS1_CTRL3_OFFSET) /* 0x0x90000208 */
	str r1, [r0]

	/* enable dsp0 dfs; dsp0:400m*/
	/* first cfg dsp0pll pd*/
	LDR R1, =0x21
	LDR R0, =(HI_SYSCRG_BASE_ADDR + HI_CRG_DFS2_CTRL3_OFFSET)
	STR R1, [R0]
	/* then recfg dsp0pll para*/
	LDR R1, =0x800000
	LDR R2, =0x310103E
	LDR R0, =(HI_SYSCRG_BASE_ADDR + HI_CRG_DFS2_CTRL1_OFFSET)
	STMIA R0, {R1-R2}
	LDR R1, =0x20
	LDR R0, =(HI_SYSCRG_BASE_ADDR + HI_CRG_DFS2_CTRL3_OFFSET)
	STR R1, [R0]
WAIT_DSP0PLL_LOCK:
	LDR R1, [R0]
	TST R1, #0x80000000
	BEQ WAIT_DSP0PLL_LOCK

	/* enable hifi dfs; hifi:400m */
	LDR R1, =0x20
	LDR R0, =(HI_SYSCRG_BASE_ADDR + HI_CRG_DFS3_CTRL3_OFFSET)
	STR R1, [R0]
WAIT_HIFIPLL_LOCK:
	LDR R1, [R0]
	TST R1, #0x80000000
	BEQ WAIT_HIFIPLL_LOCK

	/* enable bbp dfs */
	LDR R1, =0x20
	LDR R0, =(HI_SYSCRG_BASE_ADDR + HI_CRG_DFS4_CTRL3_OFFSET)
	STR R1, [R0]
WAIT_BBPPLL_LOCK:
	LDR R1, [R0]
	TST R1, #0x80000000
	BEQ WAIT_BBPPLL_LOCK

	/* enalbe peri dfs */
	ldr r1, =0x20
	ldr r0, =(HI_SYSCRG_BASE_ADDR + HI_CRG_DFS5_CTRL3_OFFSET) /* 0x0x90000238 */
	str r1, [r0]

	/* cfg to normal */
	ldr r0, =(HI_PWRCTRL_BASE_ADDR + HI_PWR_CTRL0_OFFSET)
	ldr r1, [r0]
	bic r1, r1, #0x7
	orr r1, r1, #0x4
	str r1, [r0]

WAIT_ARM_NORMAL:
	ldr r1, [r0]
	and r1, r1, #0x78
	cmp r1, #0x20
	bne WAIT_ARM_NORMAL
	
	/* open peri/dsp0/hifi/bbp pll postdiv/fout */
	ldr r0, =(HI_SYSCRG_BASE_ADDR + HI_CRG_PLLLOCK_CTRL_OFFSET)
	ldr r1, =0xffff0fff
	str r1,[r0]
	
	/* deassert dsp0 subsystem reset */
	ldr r0, =(HI_SYSCRG_BASE_ADDR + HI_CRG_SRSTDIS2_OFFSET)
	ldr r1, =0x1
	str r1,[r0]
	
	/* deassert abb&BBP reset */
	ldr r0, =(HI_SYSCRG_BASE_ADDR + HI_CRG_SRSTDIS3_OFFSET)
	ldr r1, =0xffffffff
	str r1,[r0]
	
	bx   lr  /* end of sysctrl_init */


/**************************************************************
* unreset acore
****************************************************************/
	.align 1
	.thumb_func
	.type    acore_unreset, %function
	.global  acore_unreset
acore_unreset:
	ldr  r0, =(HI_SYSSC_BASE_ADDR + HI_SC_CTRL5_OFFSET)
	ldr  r1, =RUN_BASE_ADDR_APPA9
	str  r1, [r0]

	ldr  r0, =(HI_SYSSC_BASE_ADDR + HI_CRG_SRSTDIS1_OFFSET)   /* 0x90000064 */
	ldr  r1, =0x4002
	str  r1, [r0]
	bx  lr  /* end of acore_unreset */

	.end /* end of file */

