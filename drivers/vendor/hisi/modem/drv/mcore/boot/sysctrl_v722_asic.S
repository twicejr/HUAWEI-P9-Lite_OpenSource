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
	LDR R0, =(0x20000000 + 0x41C) /*SC_AO_CTRL7*/
	LDR R1, [R0]
	ORR R1, R1, #0x2
	STR R1, [R0]
	
	/*open watchdog for low temperature load*/
#ifdef CONFIG_WDT_BOOT
	ldr  r0, =0x20001000
	ldr  r1, =0x1ACCE551
	str  r1, [r0, #0xc00]
	ldr  r2, =0x50000 /*10 * 32768*/
	str  r2, [r0]
	mov  r1, #0x3
	str  r1, [r0, #0x8]
	mov  r1, #0
	str  r1, [r0, #0xc00]
#endif

    /* wait for UART0 FIFO empty */
WAIT_FOR_UART0_FIFO_EMPTY:
	ldr r0, =(0x90024000 + 0x018)
	ldr r1, [r0]
	tst r1, #0x80
	beq WAIT_FOR_UART0_FIFO_EMPTY

/**************************************************************
*** set NANDC PWIDTH( V722 NANDC_BASE : 0x9102b0000)
****************************************************************/
	LDR R0, =0x9102b004
	LDR R1, =0x888
	STR R1,[R0]

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

	/* cfg freq div {a9_pll_vco:a17:mdm_a9:fast_bus:slow_bus:apb = 1:2:2:4:4:8}*/
	LDR R0, =(0x90000000 + 0x104) /*PD_CRG_CLKDIV2*/
	LDR R1, =0x70001300
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
	
	/* dsp pll dfs:700MHz*/
	LDR R0, =(0x90000000 + 0x210)
	LDR R2, =0x210C36B
	STR R2, [R0]
	
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

	/*open peri pll foutpost clk out*/
	LDR R0, =(0x90000000 + 0x238) /*CRG_DFS5_CTRL3*/
	LDR R1, [R0]
	ORR R1, R1,#0x200
	STR R1, [R0]

/**************************************************************
*** open a17 clk
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

	/* enable appa9 clk */
	LDR R1, =(0x1<<26)
	LDR R0, =(0x90000000 + 0x020)/* PD_CRG_CLKEN3 */
	STR R1, [R0]

	/* disable appa9 iso */
	LDR R1, =0x1
	LDR R0, =(0x20000000 + 0xC14)/* PWR_CTRL5 */
	STR R1, [R0]

	LDR R0, =(0x90000000 + 0x364)
	LDR R1, =0x4003
	STR R1, [R0]
	bx  lr  /* end of acore_unreset */

	.end /* end of file */

