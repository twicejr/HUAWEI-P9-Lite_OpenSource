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
	/* remap_clear */
	LDR R1, =0x1
	LDR R0, =(0x20000000 + 0x400) /*SC_AO_CTRL0*/
	STR R1, [R0]

	/* pmu hold clear */
	LDR R0, =(0x20000000 + 0x404) /*SC_AO_CTRL1*/
	LDR R1, [R0]
	ORR R1, R1, #0x2
	STR R1, [R0]

/**************************************************************
*** set NANDC PWIDTH( V722 NANDC_BASE : 0x9102b0000)
****************************************************************/
	LDR R0, =0x9102b004
	LDR R1, =0x888
	STR R1,[R0]

/**************************************************************
*** open all clk (for V722： PD, AO, MDM)
****************************************************************/
	LDR R0, =0xFFFFFFFF
	LDR R1, =(0x90000000 + 0x000) /*PD_CRG_CLKEN1*/
	STR R0, [R1]
	LDR R1, =(0x90000000 + 0x010) /*PD_CRG_CLKEN2*/
	STR R0, [R1]
	LDR R1, =(0x90000000 + 0x020) /*PD_CRG_CLKEN3*/
	STR R0, [R1]
	LDR R1, =(0x90000000 + 0x030) /*PD_CRG_CLKEN4*/
	STR R0, [R1]
	LDR R1, =(0x90000000 + 0x300) /*PD_CRG_SCLKEN1*/
	STR R0, [R1]
	LDR R1, =(0x20000000 + 0x000) /*AO_CRG_CLKEN1*/
	STR R0, [R1]
	LDR R1, =(0x20000000 + 0x000) /*AO_CRG_SCLKEN1*/
	STR R0, [R1]
	LDR R1, =(0x80200000 + 0x000) /*MDM_CRG_CLKEN0*/
	STR R0, [R1]
	LDR R1, =(0x80200000 + 0x010) /*MDM_CRG_CLKEN1*/
	STR R0, [R1]

/**************************************************************
*** clk init  configuration, must do in ASIC
****************************************************************/
	/*cfg system to slow state*/
	LDR R0, =(0x20000000 + 0xC00) /*PWR_CTRL0*/
	LDR R1, [R0]
	BIC R1, R1, #0x7
	ORR R1, R1, #0x2
	STR R1, [R0]
WAIT_ARM_SLOW:
	LDR R1, [R0]
	AND R1, R1, #0x78
	CMP R1, #0x10
	BNE WAIT_ARM_SLOW

	/* cfg freq div {a9_pll_vco:app_a17:mdm_a9:fast_bus:slow_bus:apb = 1:2:2:4:4:8}*/
	LDR R0, =(0x90000000 + 0x104) /*PD_CRG_CLKDIV2*/
	LDR R1, =0x40001300
	STR R1, [R0]

	/* enable a9 dfs; a9_pll_vco: 1332m */
	/* a9_pll_postdiv:666m ; a17:666m ; mdma9:666m ; fast(ddr):333m ; slow:166m; apb_pd:83m */
	LDR R0, =(0x90000000 + 0x208) /*CRG_DFS1_CTRL3*/
	LDR R2, [R0]
	BIC R2, #0x3E00
	STR R2, [R0]
	LDR R1, =0x6d5555
	LDR R2, =0x2101045
	LDR R0, =(0x90000000 + 0x200) /*CRG_DFS1_CTRL1*/
	STMIA R0, {R1-R2}    
	LDR R0, =(0x90000000 + 0x208) /*CRG_DFS1_CTRL3*/
	LDR R1, =0x28
	STR R1, [R0]
	
	/* enalbe peri dfs; peri_pll_postdiv: */
	LDR R0, =(0x90000000 + 0x238) /*CRG_DFS5_CTRL3*/
	LDR R2, [R0]
	BIC R2, #0x3E00
	STR R2, [R0]
	LDR R1, =0x2c
	STR R1, [R0]

	/* enable dsp dfs; dsp_pll_postdiv: */
	LDR R0, =(0x90000000 + 0x214) /*CRG_DFS2_CTRL3*/
	LDR R2, [R0]
	BIC R2, #0x3E00
	STR R2, [R0]
	LDR R1, =0x28
	STR R1, [R0]
WAIT_DSPPLL_LOCK:
	LDR R1, [R0]
	TST R1, #0x80000000
	BEQ WAIT_DSPPLL_LOCK

	/* enable usb dfs; usb_pll_postdiv: */
	LDR R0, =(0x90000000 + 0x244) /*CRG_DFS6_CTRL3*/
	LDR R2, [R0]
	BIC R2, #0x3E00
	STR R2, [R0]
	LDR R1, =0x2c
	STR R1, [R0]
WAIT_USBPLL_LOCK:
	LDR R1, [R0]
	TST R1, #0x80000000
	BEQ WAIT_USBPLL_LOCK

	/* cfg system state to normal */
	LDR R0, =(0x20000000 + 0xC00) /*PWR_CTRL0*/
	LDR R1, [R0]
	BIC R1, R1, #0x7
	ORR R1, R1, #0x4
	STR R1, [R0]
WAIT_ARM_NORMAL:
	LDR R1, [R0]
	AND R1, R1, #0x78
	CMP R1, #0x20
	BNE WAIT_ARM_NORMAL

	/*open a9 pll foutpost clk out*/
	LDR R0, =(0x90000000 + 0x208) /*CRG_DFS1_CTRL3*/
	LDR R1, [R0]
	ORR R1, R1,#0x200
	STR R1, [R0]
	
	/*open dsp pll foutpost clk out*/
	LDR R0, =(0x90000000 + 0x214) /*CRG_DFS2_CTRL3*/
	LDR R1, [R0]
	ORR R1, R1,#0x200
	STR R1, [R0]
	

	/*open peri pll foutpost clk out*/
	LDR R0, =(0x90000000 + 0x238) /*CRG_DFS5_CTRL3*/
	LDR R1, [R0]
	ORR R1, R1,#0x200
	STR R1, [R0]

  /*open usb pll foutpost clk out*/
	LDR R0, =(0x90000000 + 0x244) /*CRG_DFS6_CTRL3*/
	LDR R1, [R0]
	ORR R1, R1,#0x200
	STR R1, [R0]

/**************************************************************
*** open a9 clk
****************************************************************/
	LDR R0, =0x04800000
	LDR R1, =(0x90000000 + 0x20)
	STR R0, [R1]

	bx   lr  /* end of sysctrl_init */

/**************************************************************
* unreset acore
****************************************************************/
	.align 1
	.thumb_func
	.type    acore_unreset, %function
	.global  acore_unreset

acore_unreset:
	/**************************************************************
	*** V722芯片防挂死默认会打开，在onchiprom启动时，由于读nand的时间比较长，
	*** 挂死寄存器会有值，需要在M3boot作一个清除，否则后面有真挂死，无法纪录。
	****************************************************************/
	LDR R0, =(0x90000000 + 0x874) /*SC_PERI_CTRL29*/
	LDR R1, [R0]
	ORR R1, R1, #0x80
	STR R1, [R0]

	/*acc width regulate enable to 32bit*/
	LDR R0, =(0x90000000 + 0x800) /*SC_PERI_CTRL0*/
	LDR R1, [R0]
	ORR R1, R1, #0x1
	STR R1, [R0]

	LDR R0, =(0x90000000 + 0x400)
	LDR R1, =RUN_BASE_ADDR_APPA9
	STR R1, [r0]

	/* enable appa9 mtcmos */
	LDR R1, =0x1
	LDR R0, =(0x20000000 + 0xC18)/* PWR_CTRL6 */
	STR R1, [R0]

	/* wait appa9 mtcmos enable*/
	LDR R0, =(0x20000000 + 0xE04)/* PWR_STAT1 */
WAIT_A9_MTCMOS_RDY:
	LDR R1, [R0]
	TST R1, #0x1
	BEQ WAIT_A9_MTCMOS_RDY

	/*30us*/
	LDR R0, =0x387
loop_30us:
	SUB  R0,R0, #0x1
	CMP  R0,#0
	BNE  loop_30us

sec_config:
	/* sysctrl ao */
	LDR R1, = 0x4BFFEC
	LDR R0, =(0x20000000 + 0x500)
	STR R1, [R0]

	LDR R1, = 0x2
	LDR R0, =(0x20000000 + 0x504)
	STR R1, [R0]

	/* sysctrl pd */
	LDR R1, = 0x2
	LDR R0, =(0x90000000 + 0x900)
	STR R1, [R0]

	LDR R1, = 0xAE94
	LDR R0, =(0x90000000 + 0x904)
	STR R1, [R0]

	LDR R1, = 0xBFFEF784
	LDR R0, =(0x90000000 + 0x908)
	STR R1, [R0]

	LDR R1, = 0x1
	LDR R0, =(0x90000000 + 0x90C)
	STR R1, [R0]

	LDR R1, = 0xF0202
	LDR R0, =(0x90000000 + 0x910)
	STR R1, [R0]

	/* sysctrl pcie */
	LDR R1, = 0x6
	LDR R0, =(0x90100000 + 0xD00)
	STR R1, [R0]

	LDR R1, = 0x9
	LDR R0, =(0x90100000 + 0xD04)
	STR R1, [R0]

	LDR R1, = 0xE
	LDR R0, =(0x90100000 + 0xD08)
	STR R1, [R0]

	LDR R1, = 0x2
	LDR R0, =(0x90100000 + 0xD0C)
	STR R1, [R0]

	LDR R1, = 0xF
	LDR R0, =(0x90100000 + 0xD10)
	STR R1, [R0]

	/* enable appa9 clk */
	LDR R1, =(0x1<<26)
	LDR R0, =(0x90000000 + 0x020)/* PD_CRG_CLKEN3 */
	STR R1, [R0]

	/* disable appa9 iso */
	LDR R1, =0x1
	LDR R0, =(0x20000000 + 0xC14)/* PWR_CTRL5 */
	STR R1, [R0]

	LDR R0, =(0x90000000 + 0x364)
	LDR R1, =0x4001
	STR R1, [R0]
	bx  lr  /* end of acore_unreset */

	.end /* end of file */

