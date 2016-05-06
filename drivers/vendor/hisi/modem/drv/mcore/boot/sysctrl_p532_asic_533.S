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
	ldr r0, =(HI_SYSCTRL_AO_REG_BASE_ADDR + HI_SC_AO_CTRL1_OFFSET)
	ldr r1, [r0]
	orr r1, r1, #0x2
	str r1, [r0]

/**************************************************************
*** open all clk
****************************************************************/
	LDR R0, =0xFFFFFFFF
	LDR R1, =(HI_PD_CRG_BASE_ADDR + HI_CRG_CLKEN1_OFFSET)
	STR R0, [R1]
	LDR R1, =(HI_PD_CRG_BASE_ADDR + HI_CRG_CLKEN2_OFFSET)
	STR R0, [R1]
	LDR R1, =(HI_PD_CRG_BASE_ADDR + HI_CRG_CLKEN3_OFFSET)
	STR R0, [R1]
	LDR R1, =(HI_PD_CRG_BASE_ADDR + HI_CRG_CLKEN4_OFFSET)
	STR R0, [R1]
	LDR R1, =(HI_PD_CRG_BASE_ADDR + HI_CRG_CLKEN5_OFFSET)
	STR R0, [R1]
	LDR R1, =(HI_AO_CRG_REG_BASE_ADDR + HI_AO_CRG_CLKEN1_OFFSET)
	STR R0, [R1]

	
/**************************************************************
*** set NANDC PWIDTH
****************************************************************/
	LDR R0, =0x900a4004
	LDR R1, =0x888
	STR R1,[R0]

/**************************************************************
*** clk init  configuration,must do in ASIC
****************************************************************/
	/*cfg system to slow state*/
	LDR R0, =(HI_SYSCTRL_AO_REG_BASE_ADDR + HI_PWR_CTRL0_OFFSET)
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
	LDR R0, =(HI_PD_CRG_BASE_ADDR + HI_CRG_CLKDIV2_OFFSET)
	LDR R1, =0x40001300
	STR R1, [R0]
	
	/* cfg cipher_clk div to 7 (cipher_clk = 960M/7 = 137M) */
    LDR	R0, =(HI_PD_CRG_BASE_ADDR + HI_CRG_CLKDIV3_OFFSET)
	LDR R2, [R0]
	BIC R2, #0xF0000000
	ORR R2, #0x70000000
	STR R2, [R0]
	
	/* enable a9 dfs */
	/* a9pll_vco=1066m, a9pll_postdiv=1066m */
	/* a9:1066m ; fast(ddr):533m ; slow:266m; apb_pd:133m  */
	LDR R1, =0x855555
	LDR R2, =0x1101037
	LDR R0, =(HI_PD_CRG_BASE_ADDR + HI_CRG_DFS1_CTRL1_OFFSET)
	STMIA R0, {R1-R2}    
    LDR R0, =(HI_PD_CRG_BASE_ADDR + HI_CRG_DFS1_CTRL3_OFFSET)
	LDR R2, [R0]
	BIC R2, #0x3E00
	STR R2, [R0]	 
	LDR R1, =0x28
	STR R1, [R0]

	/* enalbe peri dfs */
    LDR R0, =(HI_PD_CRG_BASE_ADDR + HI_CRG_DFS5_CTRL3_OFFSET)
	LDR R2, [R0]
	BIC R2, #0x3E00
	STR R2, [R0]	 
	LDR R1, =0x20
	STR R1, [R0]
	
	/* enable dsp0 dfs; dsp0:450m */
	LDR R0, =(HI_PD_CRG_BASE_ADDR + HI_CRG_DFS2_CTRL1_OFFSET)
	LDR R1, =0xE00000
	STR R1, [R0]
	LDR R0, =(HI_PD_CRG_BASE_ADDR + HI_CRG_DFS2_CTRL2_OFFSET)
	LDR R1, =0x210102E
	STR R1, [R0]
    LDR R0, =(HI_PD_CRG_BASE_ADDR + HI_CRG_DFS2_CTRL3_OFFSET)
	LDR R2, [R0]
	BIC R2, #0x3E00
	STR R2, [R0]	 
	LDR R1, =0x20
	STR R1, [R0]
WAIT_DSP0PLL_LOCK:
	LDR R1, [R0]
	TST R1, #0x80000000
	BEQ WAIT_DSP0PLL_LOCK

/* enable hifi dfs; hifi:400m */
    LDR R0, =(HI_PD_CRG_BASE_ADDR + HI_CRG_DFS3_CTRL3_OFFSET)
	LDR R2, [R0]
	BIC R2, #0x3E00
	STR R2, [R0]	 
	LDR R1, =0x20
	STR R1, [R0]
WAIT_HIFIPLL_LOCK:
	LDR R1, [R0]
	TST R1, #0x80000000
	BEQ WAIT_HIFIPLL_LOCK

	/* enable bbp dfs */
    LDR R0, =(HI_PD_CRG_BASE_ADDR + HI_CRG_DFS4_CTRL3_OFFSET)
	LDR R2, [R0]
	BIC R2, #0x3E00
	STR R2, [R0]	 
	LDR R1, =0x20
	STR R1, [R0]
WAIT_BBPPLL_LOCK:
	LDR R1, [R0]
	TST R1, #0x80000000
	BEQ WAIT_BBPPLL_LOCK

	/* enable usb dfs; usb:500m,SC_CRG_DFS6_CTRL3:0x9001B244 */
    LDR R0, =(HI_PD_CRG_BASE_ADDR + HI_CRG_DFS6_CTRL3_OFFSET)
	LDR R2, [R0]
	BIC R2, #0x3E00
	STR R2, [R0]	 
	LDR R1, =0x20
	STR R1, [R0]
WAIT_USBPLL_LOCK:
	LDR R1, [R0]
	TST R1, #0x80000000
	BEQ WAIT_USBPLL_LOCK

	/* cfg to normal */
	ldr r0, =(HI_SYSCTRL_AO_REG_BASE_ADDR + HI_PWR_CTRL0_OFFSET)
	ldr r1, [r0]
	bic r1, r1, #0x7
	orr r1, r1, #0x4
	str r1, [r0]
WAIT_ARM_NORMAL:
	ldr r1, [r0]
	and r1, r1, #0x78
	cmp r1, #0x20
	bne WAIT_ARM_NORMAL

    /*open a9 pll foutpost/fout clk out*/
    LDR R0, =(HI_PD_CRG_BASE_ADDR + HI_CRG_DFS1_CTRL3_OFFSET)
	LDR R1, [R0]
	ORR R1, R1,#0x3e00
	STR R1, [R0]
	
    /*open peri dsp0 foutpost/fout clk out*/	
    LDR R0, =(HI_PD_CRG_BASE_ADDR + HI_CRG_DFS2_CTRL3_OFFSET)
	LDR R1, [R0]
	ORR R1, R1,#0x3e00
	STR R1, [R0]	
	
    /*open peri hifi foutpost/fout clk out*/	
    LDR R0, =(HI_PD_CRG_BASE_ADDR + HI_CRG_DFS3_CTRL3_OFFSET)
	LDR R1, [R0]
	ORR R1, R1,#0x3e00
	STR R1, [R0]	

    /*open peri bbp foutpost/fout clk out*/	
    LDR R0, =(HI_PD_CRG_BASE_ADDR + HI_CRG_DFS4_CTRL3_OFFSET)
	LDR R1, [R0]
	ORR R1, R1,#0x3e00
	STR R1, [R0]	
	
    /*open peri peri foutpost/fout clk out*/	
    LDR R0, =(HI_PD_CRG_BASE_ADDR + HI_CRG_DFS5_CTRL3_OFFSET)
	LDR R1, [R0]
	ORR R1, R1,#0x3e00
	STR R1, [R0]		

    /*open peri usb foutpost/fout clk out*/	
    LDR R0, =(HI_PD_CRG_BASE_ADDR + HI_CRG_DFS6_CTRL3_OFFSET)
	LDR R1, [R0]
	ORR R1, R1,#0x3e00
	STR R1, [R0]		

	bx   lr  /* end of sysctrl_init */


/**************************************************************
* unreset acore
****************************************************************/
	.align 1
	.thumb_func
	.type    acore_unreset, %function
	.global  acore_unreset
acore_unreset:
	ldr  r0, =(HI_SYSCTRL_PD_REG_BASE_ADDR + HI_SC_TOP_CTRL0_OFFSET)
	ldr  r1, =RUN_BASE_ADDR_APPA9
	str  r1, [r0]

	ldr  r0, =(HI_PD_CRG_BASE_ADDR + HI_CRG_SRSTDIS1_OFFSET)   /* 0x9001B064 */
	ldr  r1, =0x4002
	str  r1, [r0]
	bx  lr  /* end of acore_unreset */

	.end /* end of file */

