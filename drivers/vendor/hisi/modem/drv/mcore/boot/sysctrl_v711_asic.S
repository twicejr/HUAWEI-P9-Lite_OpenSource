#include "m3boot.h"
#include <soc_onchiprom.h>
#include <hi_syscrg.h>
#include <hi_syssc.h>
#include <hi_pwrctrl.h>
#include <product_config.h>

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

/**************************************************************
*** close lbbp/g1/g2/irm bbp clk
****************************************************************/
	LDR R0, =0xFC
	LDR R1, =(HI_SYSCRG_BASE_ADDR + HI_CRG_CLKDIS5_OFFSET)
	STR R0, [R1]

	/* deassert dsp0 subsystem reset */
	ldr r0, =(HI_SYSCRG_BASE_ADDR + HI_CRG_SRSTDIS2_OFFSET)
	ldr r1, =0x1
	str r1,[r0]

	/* deassert abb&BBP_COMMON/BBP_CRG reset */
	ldr r0, =(HI_SYSCRG_BASE_ADDR + HI_CRG_SRSTDIS3_OFFSET)
	ldr r1, =0x80000003
	str r1,[r0]

	/* close peri/dsp0/hifi/bbp pll postdiv/fout */
	ldr r0, =(HI_SYSCRG_BASE_ADDR + HI_CRG_PLLLOCK_CTRL_OFFSET)
	ldr r1, =0x80000fff
	str r1,[r0]

	/*ÉèÖÃNANDC Âö¿í*/
	ldr r0, =0x900a4004
	ldr r1, =0x888
	str r1,[r0]

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

	/* cfg freq div {a9_pll:app_a9:mdm_a9:fast_bus:slow_bus:apb = 1:2:2:4:4:8}*/
	/* a9:300m ; fast(ddr):150m ;slow:75m */
	ldr r0, =(HI_SYSCRG_BASE_ADDR + HI_CRG_CLKDIV2_OFFSET)    /* 0x0x90000104 */
	ldr r1, =0x40001300
	str r1, [r0]

      ldr r0, =(HI_SYSCRG_BASE_ADDR + HI_CRG_CLK_SEL1_OFFSET)
      ldr r1, [r0]
      orr r1, r1, #0xA0000000
      str r1, [r0]

	/* enable a9 dfs; a9_pll=300m, vco=1200m */
	LDR R1, =0x800000
	LDR R2, =0x410103E
	LDR R0, =(HI_SYSCRG_BASE_ADDR + HI_CRG_DFS1_CTRL1_OFFSET)
	STMIA R0, {R1-R2}

	LDR R1, =0x28
	LDR R0, =(HI_SYSCRG_BASE_ADDR + HI_CRG_DFS1_CTRL3_OFFSET)
	STR R1, [R0]

	/* enable dsp0 dfs; dsp0:400m */
	LDR R1, =0x20
	LDR R0, =(HI_SYSCRG_BASE_ADDR + HI_CRG_DFS2_CTRL3_OFFSET)
	STR R1, [R0]
	/* enable usb dfs; usb:500m,SC_CRG_DFS6_CTRL3:0x90000244 */
	LDR R1, =0x20
	LDR R0, =(HI_SYSCRG_BASE_ADDR + HI_CRG_DFS6_CTRL3_OFFSET)
	STR R1, [R0]
	
#ifdef CONFIG_DIALUP_HSUART_REVISE
	LDR R0, =(HI_SYSCRG_BASE_ADDR + HI_CRG_DFS5_CTRL2_OFFSET)
	LDR R1, [R0]
	LDR R2, =0xFFF
	BIC R1, R1, R2
	ORR R1, R1, #0x2E
	STR R1, [R0]
#endif
	
	LDR R1, =0x20
	LDR R0, =(HI_SYSCRG_BASE_ADDR + HI_CRG_DFS5_CTRL3_OFFSET)
	STR R1, [R0]

	/* cfg to normal */
	ldr r0, =(HI_PWRCTRL_BASE_ADDR + HI_PWR_CTRL0_OFFSET)
	ldr r1, [r0]
	bic r1, r1, #0x7
	orr r1, r1, #0x4
	str r1, [r0]

	LDR R0, =(HI_SYSCRG_BASE_ADDR + HI_CRG_DFS2_CTRL3_OFFSET)
WAIT_DSP0PLL_LOCK:
	LDR R1, [R0]
	TST R1, #0x80000000
	BEQ WAIT_DSP0PLL_LOCK

	LDR R0, =(HI_SYSCRG_BASE_ADDR + HI_CRG_DFS6_CTRL3_OFFSET)
WAIT_USBPLL_LOCK:
	LDR R1, [R0]
	TST R1, #0x80000000
	BEQ WAIT_USBPLL_LOCK

	ldr r0, =(HI_PWRCTRL_BASE_ADDR + HI_PWR_CTRL0_OFFSET)
WAIT_ARM_NORMAL:
	ldr r1, [r0]
	and r1, r1, #0x78
	cmp r1, #0x20
	bne WAIT_ARM_NORMAL

	/* open peri/dsp0/hifipostdiv/fout */
      /* dsp clk is need to cfg bbp pll*/
	ldr r0, =(HI_SYSCRG_BASE_ADDR + HI_CRG_PLLLOCK_CTRL_OFFSET)
	ldr r1, =0xbf7f0fff
	str r1,[r0]

      /*enable bbp pll:to output 245.768M:cfg abb reg*/
      LDR  R0, =0x20F8C340
      LDR  R1, [R0]
      BIC  R1, #0x8
      STR  R1, [R0]

#if 0
      LDR R0, = 0x20F8C36C
WAIT_BBPPLL_LOCK:
	LDR R1, [R0]
      TST R1, #0x80
      BEQ WAIT_BBPPLL_LOCK
#endif
      /*2us*/
	LDR R0, =0x500
loop_2us:
    SUB  R0,R0, #0x1
	CMP  R0,#0
	BNE  loop_2us
    /* open peri/dsp0/hifipostdiv/fout */
      /* dsp clk is need to cfg bbp pll*/
	ldr r0, =(HI_SYSCRG_BASE_ADDR + HI_CRG_PLLLOCK_CTRL_OFFSET)
	ldr r1, =0xffff0fff
	str r1,[r0]

        /*open g1bbp/g2bbp/irm clk*/
	LDR R0, =0xFC
	LDR R1, =(HI_SYSCRG_BASE_ADDR + HI_CRG_CLKEN5_OFFSET)
	STR R0, [R1]

	/* deassert BBP reset */
	ldr r0, =(HI_SYSCRG_BASE_ADDR + HI_CRG_SRSTDIS3_OFFSET)
	ldr r1, =0x7fffffff
	str r1,[r0]

	/*follow code is used to define mmc/cipher clk*/
	/*this should be defined in ip driver*/
	/* MMC */
	ldr r0, =(HI_SYSCRG_BASE_ADDR + HI_CRG_CLKDIV3_OFFSET)    /* 0x0x90000108 */
	ldr r1, =0x31101103
	str r1, [r0]

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

