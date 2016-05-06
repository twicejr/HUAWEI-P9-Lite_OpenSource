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
/* pll icg off before stable */
	LDR R1, =(HI_SYSCRG_BASE_ADDR + HI_CRG_CTRL42_OFFSET)
	LDR R2, [R1]
	BIC R2, R2, #0xFF
	STR R2, [R1]

/* cfg mode to slow */
	LDR R1, = 0x22222
	LDR R0, =(HI_SYSSC_BASE_ADDR + HI_CRG_CTRL18_OFFSET)
	STR R1, [R0]
	NOP
	NOP
	NOP
	LDR R0, =(HI_PWRCTRL_BASE_ADDR + HI_PWR_CTRL0_OFFSET)
	LDR R1, [R0]
	BIC R1, R1, #0x7
	ORR R1, R1, #0x2
	STR R1, [R0]
WAIT_ARM_SLOW:
	LDR R1, [R0]
	AND R1, R1,#0x78
	CMP R1, #0x10
	BNE WAIT_ARM_SLOW

/*A9 PLL CFG ; a9_dfs_foutpostdiv:667M*/
	LDR R1, = 0x600000
	LDR R2, = 0x2101045
	LDR R0, = (HI_SYSCRG_BASE_ADDR + HI_CRG_CTRL20_OFFSET)
	STMIA R0, {R1-R2}
	LDR R1, = 0x28
	LDR R0, = (HI_SYSCRG_BASE_ADDR + HI_CRG_CTRL22_OFFSET)
	STR R1, [R0]

	/*PERI PLL CFG ; peri_dfs_foutpostdiv:960M*/
	LDR R1, = 0x20
	LDR R0, = (HI_SYSCRG_BASE_ADDR + HI_CRG_CTRL34_OFFSET)
	STR R1, [R0]
WAIT_PERIPLL_LOCK:
	LDR R1, [R0]
	TST R1, #0x80000000
	BEQ WAIT_PERIPLL_LOCK

	/*DSP PLL CFG ; peri_dfs_foutpostdiv:960M*/
	LDR R1, = 0x20
	LDR R0, = (HI_SYSCRG_BASE_ADDR + HI_CRG_CTRL25_OFFSET)
	STR R1, [R0]
WAIT_DSP_LOCK:
	LDR R1, [R0]
	TST R1, #0x80000000
	BEQ WAIT_DSP_LOCK


	/*A15 PLL CFG ; peri_dfs_foutpostdiv:960M*/
      LDR R1, = 0xE00000
      LDR R0, = (HI_SYSCRG_BASE_ADDR + HI_CRG_CTRL26_OFFSET)
      STR R1, [R0]
      LDR R1, = 0x110102E
      LDR R0, = (HI_SYSCRG_BASE_ADDR + HI_CRG_CTRL27_OFFSET)
      	LDR R1, = 0x0
	LDR R0, = (HI_SYSCRG_BASE_ADDR + HI_CRG_CTRL28_OFFSET)
	STR R1, [R0]
WAIT_A15_LOCK:
	LDR R1, [R0]
	TST R1, #0x80000000
	BEQ WAIT_A15_LOCK

/*CFG SYS CLK DIV ; a9:333M/fast:167M/slow:167M/hifi:167M*/
	LDR R1, = 0x22222
	LDR R0, = (HI_SYSCRG_BASE_ADDR + HI_CRG_CTRL18_OFFSET)
	STR R1, [R0]
	NOP
	NOP
	NOP
	LDR R0, = (HI_SYSCRG_BASE_ADDR + HI_CRG_CTRL18_OFFSET)
	//LDR R1, = 0x44422  // a9:333M fast:167M hifi:167M
	//LDR R1, =0x22422  //a9:333M fast:333M hifi:333M
	//LDR R1, =0x88844  //a9:333M fast:83M hifi:83M
	LDR R1, =0x22411  //a9:666M fast:333M slow:167 hifi:333M
	LDR R2, [R0]
	BIC R2, #0xFF
	BIC R2, #0xFF00
	BIC R2, #0x30000
	ADD R2, R1,R2
	STR R2, [R0]

	/*CFG TO NORMAL*/
	LDR R0, = (HI_PWRCTRL_BASE_ADDR + HI_PWR_CTRL0_OFFSET)
	LDR R1, [R0]
	BIC R1, R1, #0x7
	ORR R1, R1, #0x4
	STR R1, [R0]
WAIT_ARM_NORMAL:
	LDR R1, [R0]
	AND R1, R1,#0x78
	CMP R1, #0x20
	BNE WAIT_ARM_NORMAL

	/* pll icg on after stable */
	LDR R1, = (HI_SYSCRG_BASE_ADDR + HI_CRG_CTRL42_OFFSET)
	LDR R2, [R1]
	ORR R2, #0xFF
	STR R2, [R1]

	/* close memory repair */
	LDR R1, = HI_SC_CTRL127_OFFSET
	LDR R2, = HI_SYSCTRL_BASE_ADDR
	ADD R1, R1, R2
	MOV R2, #0x0
	STR R2, [R1]

	bx  lr

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
	
	ldr  r0, =(HI_SYSSC_BASE_ADDR + HI_CRG_CTRL14_OFFSET)   /* 0x90000038 */
	ldr  r1, [r0]
	ldr  r2, =0x1001 /* 1bit/12bit clr to zero */
	bic  r1, r2
	str  r1, [r0]
	bx  lr  /* end of acore_unreset */

	.end /* end of file */