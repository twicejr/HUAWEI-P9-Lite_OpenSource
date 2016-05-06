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
	ldr r0, =(0x20000000 + 0x404)
	ldr r1, [r0]
	orr r1, r1, #0x2
	str r1, [r0]

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
	LDR R0, =0x4B00
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

