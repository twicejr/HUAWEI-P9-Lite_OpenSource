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
	ldr r0, =(0x20000000 + 0x404) /*SC_AO_CTRL1*/
	ldr r1, [r0]
	orr r1, r1, #0x2
	str r1, [r0]

    /* wait for UART0 FIFO empty */
WAIT_FOR_UART0_FIFO_EMPTY:
	ldr r0, =(0x90024000 + 0x018)
    ldr r1, [r0]
    tst r1, #0x80
    beq WAIT_FOR_UART0_FIFO_EMPTY

/**************************************************************
*** set NANDC PWIDTH( V7R5 NANDC_BASE : 0x9102b0000)
****************************************************************/
	LDR R0, =0x9102b004
	LDR R1, =0xbbb
	STR R1,[R0]

/**************************************************************
*** open all clk (for V7R5： PD, AO, MDM)
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
	LDR R1, =(0x20000000 + 0x000) /*AO_CRG_CLKEN1*/
	STR R0, [R1]
	LDR R1, =(0x80200000 + 0x000) /*MDM_CRG_CLKEN0*/
	STR R0, [R1]
	LDR R1, =(0x80200000 + 0x010) /*MDM_CRG_CLKEN1*/
	STR R0, [R1]

	/*set ldo30 to 0.9v*/
	LDR R0, =0xb
	LDR R1, =(0x9001a000 + 0x24c) 
	STR R0, [R1]

	/* check version if(version == LDO32_DDRPHY_IO) */
	LDR R0, =(0x9001a000 + (0x5<<2)) /* pmu version: v520=0x20 */
	LDR R0, [R0]
	CMP  R0,#0x20

	/* pmu version need ldo32 1.2v for ddrphy_io */
	BEQ  open_ldo32_1_2v

	/* pmu version don't need ldo32 for ddrphy_io */
	LDR R0, =0x1
	B   loop_130us

open_ldo32_1_2v:
	/*set ldo32 to 1.2v*/
	LDR R0, =0x7
	LDR R1, =(0X9001a000 + 0x25c)
	STR R0, [R1]
	/*open ldo32*/
	LDR R0, =0x2
	LDR R1, =(0X9001a000 + 0x258)
	STR R0, [R1]
    /*130us*/
    LDR R0, =0xF49

loop_130us:
    SUB  R0,R0, #0x1
    CMP  R0,#0
    BNE  loop_130us


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

	/* cfg freq div {a9_pll:app_a9:mdm_a9:fast_bus:slow_bus:apb = 1:2:2:4:4:8}*/
	LDR R0, =(0x90000000 + 0x104) /*PD_CRG_CLKDIV2*/
	LDR R1, =0x40001300
	STR R1, [R0]

	/* enable a9 dfs; a9_pll_postdiv: 1066m */
	/* a9:1066m ; fast(ddr):533m ; slow:266m; apb_pd:133m  */
	LDR R0, =(0x90000000 + 0x208) /*CRG_DFS1_CTRL3*/
	LDR R2, [R0]
	BIC R2, #0x3E00
	STR R2, [R0]
	LDR R1, =0x855555
	LDR R2, =0x1101037
	LDR R0, =(0x90000000 + 0x200) /*CRG_DFS1_CTRL1*/
	STMIA R0, {R1-R2}
	LDR R0, =(0x90000000 + 0x208) /*CRG_DFS1_CTRL3*/
	LDR R1, =0x28
	STR R1, [R0]

	/* enalbe peri dfs; peri_pll_postdiv: 960m */
	LDR R0, =(0x90000000 + 0x238) /*CRG_DFS5_CTRL3*/
	LDR R2, [R0]
	BIC R2, #0x3E00
	STR R2, [R0]
	LDR R1, =0x2c
	STR R1, [R0]

	/* enable dsp dfs; dsp_pll_postdiv: 450m */
	LDR R0, =0x0
	LDR R1, =(0x90000000 + 0x20c) 
	STR R0, [R1]
	LDR R0, =0x03101046
	LDR R1, =(0x90000000 + 0x210) 
	STR R0, [R1]

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

  /* enable hifi dfs; hifi_pll_postdiv: 786.4m */
	LDR R0, =(0x90000000 + 0x220) /*CRG_DFS3_CTRL3*/
	LDR R2, [R0]
	BIC R2, #0x3E00
	STR R2, [R0]
	LDR R1, =0x28
	STR R1, [R0]
WAIT_HIFIPLL_LOCK:
	LDR R1, [R0]
	TST R1, #0x80000000
	BEQ WAIT_HIFIPLL_LOCK

	/* enable usb dfs; usb_pll_postdiv: 500m */
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
	ldr r0, =(0x20000000 + 0xC00) /*PWR_CTRL0*/
	ldr r1, [r0]
	bic r1, r1, #0x7
	orr r1, r1, #0x4
	str r1, [r0]
WAIT_ARM_NORMAL:
	ldr r1, [r0]
	and r1, r1, #0x78
	cmp r1, #0x20
	bne WAIT_ARM_NORMAL

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

  /*open hifi pll foutpost clk out*/
	LDR R0, =(0x90000000 + 0x220) /*CRG_DFS3_CTRL3*/
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
    *** V7R5芯片防挂死默认会打开，在onchiprom启动时，由于读nand的时间比较长，
    *** 挂死寄存器会有值，需要在M3boot作一个清除，否则后面有真挂死，无法纪录。
    ****************************************************************/
    LDR R0, =(0x90000000 + 0x848) /*SC_PERI_CTRL18*/
    LDR R1, [R0]
    ORR R1, R1, #0x80
    STR R1, [R0]

    /*acc width regulate enable to 32bit*/
    LDR R0, =(0x90000000 + 0x800) /*SC_PERI_CTRL0*/
    LDR R1, [R0]
    ORR R1, R1, #0x1
    STR R1, [R0]

	ldr  r0, =(0x90000000 + 0x400)
	ldr  r1, =RUN_BASE_ADDR_APPA9
	str  r1, [r0]

	/* enable appa9 mtcmos */
	LDR R1, =0x1
	LDR R0, =(0x20000000 + 0xC18)/* PWR_CTRL6 */
	STR R1, [R0]

#if (!defined(BSP_CONFIG_EMU_PALADIN) && !defined(BSP_CONFIG_EMU_ZEBU))
	/* wait appa9 mtcmos enable*/
	LDR R0, =(0x20000000 + 0xE04)/* PWR_STAT1 */
WAIT_A9_MTCMOS_RDY:
	LDR R1, [R0]
	TST R1, #0x1
	BEQ WAIT_A9_MTCMOS_RDY
#endif

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

	ldr  r0, =(0x90000000 + 0x064)
	ldr  r1, =0x4003
	str  r1, [r0]
	bx  lr  /* end of acore_unreset */

	.end /* end of file */

