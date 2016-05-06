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
	
	LDR R1, = 0x90000468
	LDR R2, = 0xFFFFFFFF
	STR R2, [R1]
	
	LDR R1, = 0x9001000c
	LDR R2, [R1]
	BIC R2, #0x1
	STR R2, [R1]
	
	LDR R1, = 0x90010410
	LDR R2, [R1]
	ORR R2, #0x1
	STR R2, [R1]
	
	LDR R1, = 0x90000C00
	LDR R2, [R1]
	BIC R2, #0x4000
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
	
	ldr  r0, =(HI_SYSSC_BASE_ADDR + HI_CRG_SRSTDIS1_OFFSET)   /* 0x90000064 */
	ldr  r1, =0x4002
	str  r1, [r0]
	bx  lr  /* end of acore_unreset */
	
	.end /* end of file */

