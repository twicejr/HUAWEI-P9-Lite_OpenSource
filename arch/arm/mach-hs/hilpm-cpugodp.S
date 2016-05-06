#include <linux/linkage.h>
#include <asm/assembler.h>
#include <asm/cp15.h>
#include "hipm.h"

.extern hs_a9per_va_base
.extern hs_secram_va_base
.extern hs_sctrl_base

/**physical address to virtal or virtual to physical**/
.macro	addr_proc, rx, rxt, p, v
	LDR	\rxt, =\p
	SUB	\rx, \rxt
	LDR	\rxt, =\v
	ADD	\rx, \rxt
.endm

/**physical to virtual**/
.macro	p2v, rx, rxt, p, v
	addr_proc \rx, \rxt, \p, \v
.endm

/**virtual to physical**/
.macro	v2p, rx, rxt, v, p
	addr_proc \rx, \rxt, \v, \p
.endm

/*
 *------------------------------------------------------------------------------
 * Function: hilpm_cpu_godpsleep
 *
 * this function is the low level interface when deep sleep.
 *
 */

ENTRY (hilpm_cpu_godpsleep)
	/* According to Procedure Call Standard for ARM, r0-r3 dont need to
	 * be preserved
	 */
	STMFD 	sp!, {r4-r11, lr}

	LDR    r8, hi_cpu_godpsleep_phybase
				@r8 store the PHY address of stored_ctx
	LDR    r0, =(hs_secram_va_base)
	LDR    r0, [r0]
	LDR    r9, =(A9_PRE_STORE_DATA_ADDR_OFFSET)
	ADD    r9, r9, r0	@r9 store the pre-store address which in securam

	/* Some A9 Contexts need be protected before MMU and cache disabled
	 * r9 store the address in securam, to store some critial cp15
	 * register which has relationship with MMU operation
	 */

	MOV	r1, #0
	MCR	p15, 0, r1, c7, c5, 0	@ Invalidate entire instruction cache
					@ and flush branch predictor arrays
	/* get the CPUID */
	MRC	p15, 0, r0, c0, c0, 5	@ Read CPU MPIDR
	AND	r0, r0, #0x03           @ Mask off, leaving the CPU ID field

save_ctx:

	/* save critial CP15 register before MMU Disabled
	 * CPU_ID save in r0
	 * save CTRL_Register in r1
	 * save Aux_Ctrl_register in r2
	 * TTBR0 in r3
	 * TTBR1 in r4
	 * TTBCR in r5
	 * DAC   in r6
	 */
	mrc     p15, 0, r1, c1, c0, 0	@ sctlr
	mrc     p15, 0, r2, c1, c0, 1	@ actlr
	mrc     p15, 0, r3, c2, c0, 0	@ TTBR0
	mrc     p15, 0, r4, c2, c0, 1	@ TTBR1
	mrc     p15, 0, r5, c2, c0, 2	@ TTBCR
	mrc     p15, 0, r6, c3, c0, 0	@ domain access control reg

	/* Notes: MMU is enabled, using the pre-store addree which stored in R9
	 * r0,[r9]             @offset0 store the CPU_ID
	 * r1,[r9,#0x4]        @CTRL_Register
	 * r2,[r9,#0x8]        @Aux_Ctrl_register
	 * r3,[r9,#0xc]        @TTBR0
	 * r4,[r9,#0x10]       @TTBR1
	 * r5,[r9,#0x14]       @TTBCR
	 * r6,[r9,#0x18]       @DAC
	 */
	STMIA   r9,{r0-r6}

	/* now Clean and Invalid D-Cache, and Disable Cache */
	mov     r0, #0
	mcr     p15, 0, r0, c7, c5, 4   @ Flush prefetch buffer
	mcr     p15, 0, r0, c7, c5, 6   @ Invalidate branch predictor array
	mcr     p15, 0, r0, c8, c5, 0   @ Invalidate instruction TLB
	mcr     p15, 0, r0, c8, c6, 0   @ Invalidate data TLB

	/* protect r9 to r6 while clean and invalid l1-cache
	 * now r9 can be released for free use
	 * r8 is reserved which store the PHY address
	 */
	mov     r6,r9

	/* Flush the entire cache system: Dcache and Icache
	 * Corrupted registers: R0~R3
	 */
	bl	v7_flush_kern_cache_all	@ Flush the entire cache system

	mov     r0, #0
	mcr     p15, 0, r0, c7, c1, 6   @ BPIALLIS
	mcr     p15, 0, r0, c8, c3, 0

	mov	r0, #0
	mcr	p15, 0, r0, c1, c0, 1	    @ A9 exit coherency now

	/* After clean and invalid cache, we need disable
	 * D-Cache immediately
	 */

	/*  Data Cache Disable  */
	mrc	p15, 0, r0, c1, c0, 0
	bic	r0, r0, #(CR_C)		@ Dcache disable
	mcr	p15, 0, r0, c1, c0, 0

	/* save back Secruram stored data address
	 * r10 store the pre-store ctx address in securam
	 * r6 can be releaseed for free use
	 */
	mov	r10, r6

	/* Before MMU is disabled, to
	 * Convert r10 from virtual address to physical address
	 * Note: r10 is the address in SECRAM to save tmp data
	 */
	LDR 	r0, =(hs_secram_va_base)
	LDR 	r0, [r0]
	SUB 	r10, r10, r0 	@ r10 is offset to SECRAM base
	LDR 	r0, =(REG_BASE_SECRAM)
	ADD 	r10, r10, r0 	@ r10 is physical address

	/* write domain access to get the domain access right */
	LDR	r0, =0xFFFFFFFF
	MCR	p15, 0, r0, c3, c0, 0

	/*read TTBCR*/
	mrc	p15, 0, r7, c2, c0, 2
	and	r7, #0x7
	cmp	r7, #0x0
	beq	create_idmap
ttbr_error:
	@TTBR1 not supports
	b	ttbr_error

create_idmap:
	/**read TTBR0 registers**/
	mrc	p15, 0, r2, c2, c0, 0	@ r2: translation table base register 0
	ldr	r5, =TTBRBIT_MASK   	@ 0xFFFFC000, high 18 bits
	and	r2, r5			@ r2 = TTBR0's high 18 bits
	ldr	r4, =(hisi_v2p(disable_mmu))	@ r4, pa(disable_mmu)
	ldr	r5, =TABLE_INDEX_MASK		@ 0xFFF00000, top 12 bits.
						@ why not 14?
	and	r4, r5			@ r4 = keeps the top 12 bits.
	ldr	r1, =TABLE_ENTRY
				@ r1 = 0x00000C02
				@ why 0x0C02? these are ttb property bits.
				@ any change in v3.8?
	add	r1, r1, r4	@ r1 = top 12 bits of pa(disable_mmu) | 0x0C02
	lsr	r4, #18		@ r4 = r4 >> 18
	add	r2, r4		@ r2 = r2 + r4, TTBR0's high 18 bits +
				@   r4's top 14 bits (shifted to low 14 bits)

	/**r2 virtual addr for TLB**/
	p2v r2, r4, K3_PLAT_PHYS_OFFSET, PAGE_OFFSET

	@ now, r2 is the virtual address of disable_mmu() code part.
	@ what if disable_mmu() code part cross two or
	@ more translation table section?
	@ /* TODO: need manual checking now. should be fixed in future */

	/**read the TLB**/
	LDR	r7, [r2]

	/**config the identy mapping**/
	STR	r1, [r2]	@ change the TLB its to it's physical address.

	/**r9 virtual addr for tlb**/
	mov	r9, r2

	/**r11 virtual addr of the enable_mmu**/
	ADR     r11, mmu_enalbed
	NOP
	NOP
	NOP

	LDR	r6, =(hisi_v2p(ready_to_store))
	LDR	pc, =(hisi_v2p(disable_mmu))

disable_mmu:
	instr_sync

	/*disable MMU*/
	MRC  p15, 0, r0, c1, c0, 0
	BIC  r0, r0, #(CR_M | CR_C)	@ MMU disable, Dcache disable
	MCR  p15, 0, r0, c1, c0, 0

	/*  invalidate I & D TLBs */
	LDR  r0,=0x0
	MCR  p15, 0, r0, c8, c7, 0
	instr_sync

	MOV  pc, r6

	/* From this scratch , MMU is Disabled */
ready_to_store:
	/* move critical data from securam to DDR (L1/l2 unaccessable)
	 * r0,[r10]         offset0 store the Slave CPU Return Addres
	 * 		 if offset0 is 0, that means this cpu has
	 *		 not booted up yet
	 * r1,[r10,#0x4]	@CTRL_Register
	 * r2,[r10,#0x8]	@Aux_Ctrl_register
	 * r3,[r10,#0xC]	@TTBR0
	 * r4,[r10,#0x10]	@TTBR1
	 * r5,[r10,#0x14]	@TTBCR
	 * r6,[r10,#0x18]	@DAC
	 * r7,[r10,#0x1C]  direct mapping first level descriptor
	 * r9,[r10,#0x20]  virtual addr for the first level descriptor
	 * r11,[r10, #0x24]  enable_mmu virtual addr
	 */

	/* r10 is physical address of SECURAM to save tmp data
	 * Note: Converted before MMU is disabled
	 */
	LDMIA   r10, {r0-r6}

	mrc     p15, 0, r3, c2, c0, 0	@ TTBR0
	mrc     p15, 0, r4, c2, c0, 1	@ TTBR1
	mrc     p15, 0, r5, c2, c0, 2	@ TTBCR

	/* r8 is addr to store data in ddr */
	STMIA   r8, {r0-r7, r9, r11}

all_to_store:

	/* R6/R10 can be release now
	 * R9/R8 is reserved
	 */
	add r9, r8, #SUSPEND_STORE_RESEVED_UNIT

	/* save CP15 register */
	mrc p15, 2, r0, c0, c0, 0  @ csselr
	mrc p15, 0, r4, c15, c0, 0 @ pctlr
	stmia r9!, {r0, r4}

	mrc p15, 0, r0, c15, c0, 1 @ diag
	mrc p15, 0, r1, c1, c0, 2  @ cpacr
	stmia	r9!, {r0-r1}
	mrc p15, 0, r4, c7, c4, 0  @ PAR
	mrc p15, 0, r5, c10, c2, 0 @ PRRR
	mrc p15, 0, r6, c10, c2, 1 @ NMRR
	mrc p15, 0, r7, c12, c0, 0 @ VBAR
	stmia r9!, {r4-r7}

	mrc p15, 0, r0, c13, c0, 1 @ CONTEXTIDR
	mrc p15, 0, r1, c13, c0, 2 @ TPIDRURW
	mrc p15, 0, r2, c13, c0, 3 @ TPIDRURO
	mrc p15, 0, r3, c13, c0, 4 @ TPIDRPRW
	stmia r9!, {r0-r3}

	/* to save normal register which including R9,so
	 * use R0 as stack pointer
	 */
	MOV  r0,r9

	/**
	save 7 modes programmable registers
	save svc mode registers
	enter svc mode, no interrupts
	**/

	MOV     r2, #MODE_SVC | I_BIT | F_BIT
	MSR     cpsr_c, r2
	MRS     r1, spsr
	STMIA   r0!, {r1, r13, r14}

	/**
	save fiq mode registers
	enter fiq mode, no interrupts
	**/
	MOV     r2, #MODE_FIQ | I_BIT | F_BIT
	MSR     cpsr_c, r2
	MRS     r1,spsr
	STMIA   r0!, {r1, r8-r14}

	/**
	save irq mode registers
	enter irq mode, no interrupts
	**/
	MOV     r2, #MODE_IRQ | I_BIT | F_BIT
	MSR     cpsr_c, r2
	MRS     r1,spsr
	STMIA   r0!, {r1, r13, r14}

	/**
	save undefine mode registers
	enter undefine mode, no interrupts
	**/
	MOV     r2, #MODE_UND | I_BIT | F_BIT
	MSR     cpsr_c, r2
	MRS     r1,spsr
	STMIA   r0!, {r1, r13, r14}

	/**
	save abort mode registers
	enter abort mode, no interrupts
	**/
	MOV     r2, #MODE_ABT | I_BIT | F_BIT
	MSR     cpsr_c, r2
	MRS     r1,spsr
	STMIA   r0!, {r1, r13, r14}

	/**
	save system mode registers
	enter system mode, no interrupts
	**/
	MOV     r2, #MODE_SYS | I_BIT | F_BIT
	MSR     cpsr_c, r2
	STMIA   r0!, {r13, r14}

	/** back to SVC mode, no interrupts **/
	MOV     r2, #MODE_SVC | I_BIT | F_BIT
	MSR     cpsr_c, r2

	/** save the private timer  **/
save_prv_timer:
	LDR     r4,= A9_PRV_TIMER_BASE
	LDR	r2, [r4, #TIMER_LD]   @timer load
	LDR	r3, [r4, #TIMER_CTL]  @timer control
	STMIA   r0!, {r2-r3}

	/**
	Now Master CPU protect the Global timer.
	save the 64bit timer
	**/
	LDR r1,= A9_GLB_TIMER_BASE
	LDR r2, [r1, #TIM64_CTL]  @64-bit timer control
	BIC	r3, r2, #0xF
	STR	r3, [r1, #TIM64_CTL]  @disable the features

	/** the registers are now frozen for the context save  **/
	LDR	r3, [r1, #TIM64_AUTOINC] @Autoincrement register
	LDR	r4, [r1, #TIM64_CMPLO]   @comparator - lo word
	LDR	r5, [r1, #TIM64_CMPHI]   @comparator - hi word
	STMIA	r0!, {r2-r5}

	LDR	r2, [r1, #TIM64_CNTLO] @counter - lo word
	LDR	r3, [r1, #TIM64_CNTHI] @counter - hi word
	STMIA	r0!, {r2-r3}


#ifdef CONFIG_CACHE_L2X0
	/**
	save L2CC Configuration
	**/
	dsb

	ldr     r6, =REG_BASE_L2CC
	ldr     r2, [r6, #L2X0_AUX_CTRL]
	ldr     r3, [r6, #L2X0_TAG_LATENCY_CTRL]
	ldr     r4, [r6, #L2X0_DATA_LATENCY_CTRL]
	ldr     r5, [r6, #L2X0_PREFETCH_OFFSET]
	stmia   r0!, {r2-r5}
#endif
	/** save SCU Configruation  **/
	LDR    r1,=A9_SCU_BASE
	LDR    r2,[r1,#SCU_FILTER_START_OFFSET]
	LDR    r3,[r1,#SCU_FILTER_END_OFFSET]
	LDR    r4,[r1,#SCU_ACCESS_CONTROL_OFFSET]
	LDR    r5,[r1,#SCU_NONSEC_CONTROL_OFFSET]
	LDR    r6,[r1,#SCU_CONTROL_OFFSET]
	LDR    r7,[r1,#SCU_POWER_STATE_OFFSET]
	STMIA  r0!,{r2-r7}

	/*
	Protect the NAND Configuration
	Since it is a risk to read NAND register when
	we do not konw its clock and reset status
	so left this work to NAND driver.
	*/
	/*
	LDR r4,=NAND_CTRLOR_BASE
	LDR r1,[r4,#0x0]
	LDR r2,[r4,#0x10]
	LDR r3,[r4,#0x14]
	STMIA  r0!,{r1-r3}
        */

	/**
	Need not protect the eMMC Configuration
	eMMC will re enumation
	**/

SKIP_MASTER_CPU_OPRATORATION:

	str  r0,[r8,#SUSPEND_STACK_ADDR]  @store the stack_top

	/* Jump to SecuRAM to execute
	 * r6: load return address in r6. But, in normal case, Securam code
	 * will stop in WFI, and never return.
	 *
	 * When system resume, fastboot will jump to (MASTER_SR_BACK_PHY_ADDR)
	 */
	LDR     r7, =(MASTER_SR_BACK_PHY_ADDR)
	LDR     r6, [r7]

	LDR 	r0, =(REG_BASE_SECRAM)
	LDR 	r1, =(DPSLEEP_CODE_ADDR_OFFSET)
	ADD 	r0, r0, r1
	MOV     PC, r0	@ Jump to the SECRAM address
			@ Goto hs_finish_suspend to read the code

/*
 * Function: master_cpu_resume()
 *
 * Resume entry point of Master CPU. Physical address of this function is
 * stored in MASTER_SR_BACK_PHY_ADDR. During resume, fastboot code fetches
 * from MASTER_SR_BACK_PHY_ADDR, and jump.
 *
 * At the end of this function, it returns to the C world where
 * hilpm_cpu_godpsleep() is called.
 */
ENTRY (master_cpu_resume)
	/* write domain access to get the domain access right */
	LDR	r0, =0xFFFFFFFF
	MCR     p15, 0, r0, c3, c0, 0

	mov     r0, #0
	mcr     p15, 0, r0, c7, c5, 4   @ Flush prefetch buffer
	mcr     p15, 0, r0, c7, c5, 6   @ Invalidate branch predictor array
	mcr     p15, 0, r0, c8, c5, 0   @ Invalidate instruction TLB
	mcr     p15, 0, r0, c8, c6, 0   @ Invalidate data TLB

	mov     r10, #0                 @ swith back to cache level 0
	mcr     p15, 2, r10, c0, c0, 0  @ select current cache level in cssr
	dsb
	isb
	mov     r0, #0
	mcr     p15, 0, r0, c7, c1, 0   @ ICIALLUIS
	mcr     p15, 0, r0, c7, c1, 6   @ BPIALLIS
	mcr     p15, 0, r0, c8, c3, 0

	/**
	restore_data
	R10 is reserved to store the PHY address of A9 stored_ctx
	**/
	LDR     r10, hi_cpu_godpsleep_phybase

	mov     r1, #0
	mcr	p15, 0, r1, c7, c5, 0	@ Invalidate entire instruction cache
				@ and flush branch predictor arrays

master_start_load_ctx:

	/*  R0 is reserved to stored_ctx stack pointer  */
	LDR     r0, [r10, #SUSPEND_STACK_ADDR]

	/**
	Resume the NAND Configuration
	Since it is a risk to read NAND register when
	we do not konw its clock and reset status
	so left this work to NAND driver.
	**/
	/*
	LDMDB   r0!, {r1-r3}
	LDR     r4,=REG_BASE_NANDC_CFG
	STR     r3,[r4,#0x14]
	STR     r2,[r4,#0x10]
	STR     r1,[r4,#0x0]
        */

	/*  Restore SCU Configruation  **/
	LDMDB   r0!, {r2-r7}
	LDR     r1,=A9_SCU_BASE
	STR     r2,[r1,#SCU_FILTER_START_OFFSET]
	STR     r3,[r1,#SCU_FILTER_END_OFFSET]
	STR     r4,[r1,#SCU_ACCESS_CONTROL_OFFSET]
	STR     r5,[r1,#SCU_NONSEC_CONTROL_OFFSET]

	LDR     r8, =0xFFFF
	/*  invalidate the duplicate TAG store */
	STR     r8, [r1, #SCU_SEC_INVALID_REG_OFFSET]

	STR     r6,[r1,#SCU_CONTROL_OFFSET]
	STR     r7,[r1,#SCU_POWER_STATE_OFFSET]    @restore CPU power statue

#ifdef CONFIG_CACHE_L2X0
	/* restore l2-cache configuration  */
	ldr     r6, =REG_BASE_L2CC
	LDMDB   r0!, {r2-r5}
	str     r3, [r6, #L2X0_TAG_LATENCY_CTRL]
	str     r4, [r6, #L2X0_DATA_LATENCY_CTRL]
	str     r5, [r6, #L2X0_PREFETCH_OFFSET]
	str     r2, [r6, #L2X0_AUX_CTRL]
#endif

	/*  restore 64bit global timer  */
	LDR r1, =A9_GLB_TIMER_BASE
	LDMDB	r0!, {r2-r3}
	STR	r2, [r1, #TIM64_CNTLO]   @counter - lo word
	STR	r3, [r1, #TIM64_CNTHI]   @counter - hi word

	LDMDB	r0!, {r2-r5}
	STR	r3, [r1, #TIM64_AUTOINC] @Autoincrement register
	STR	r4, [r1, #TIM64_CMPLO]   @comparator - lo word
	STR	r5, [r1, #TIM64_CMPHI]   @comparator - hi word
	STR	r2, [r1, #TIM64_CTL]     @restore the control last

slave_start_load_ctx:
	/* restore private timer  */
	LDR     r1, =A9_PRV_TIMER_BASE
	LDMDB	r0!, {r2-r3}
	STR	r2, [r1, #TIMER_LD]   @timer load
	STR	r3, [r1, #TIMER_CTL]  @timer control

	/**
	resume system mode registers
	enter system mode, no interrupts
	**/
	MOV     r2, #MODE_SYS | I_BIT | F_BIT
	MSR     cpsr_c, r2
	LDMDB   r0!, {r13, r14}

	/**
	resume abort mode registers
	enter abort mode, no interrupts
	**/
	MOV     r2, #MODE_ABT | I_BIT | F_BIT
	MSR     cpsr_c, r2
	LDMDB   r0!, {r1, r13, r14}
	MSR     spsr_c, r1

	/**
	resume undefine mode registers
	enter undefine mode, no interrupts
	**/
	MOV     r2, #MODE_UND | I_BIT | F_BIT
	MSR     cpsr_c, r2
	LDMDB   r0!, {r1, r13, r14}
	MSR     spsr_c, r1

	/**
	resume irq mode registers
	enter irq mode, no interrupts
	**/
	MOV     r2, #MODE_IRQ | I_BIT | F_BIT
	MSR     cpsr_c, r2
	LDMDB   r0!, {r1, r13, r14}
	MSR     spsr_c, r1

	/**
	resume fiq mode registers
	enter fiq mode, no interrupts
	**/
	MOV     r2, #MODE_FIQ | I_BIT | F_BIT
	MSR     cpsr_c, r2
	LDMDB   r0!, {r1, r8-r14}
	MSR     spsr_c, r1

	/**
	resume svc mode registers
	enter svc mode, no interrupts
	**/
	MOV     r2, #MODE_SVC | I_BIT | F_BIT
	MSR     cpsr_c, r2
	LDMDB   r0!, {r1, r13, r14}
	MSR     spsr_c, r1

	/* Restore CP15 register, need use r0 register
	 * use R8 replace R0 to save Stack_pointer
	 */
	MOV     r8,r0


	/** restore CP15 register **/
	LDMDB	r8!, {r0-r3}
	mcr	p15, 0, r0, c13, c0, 1	@ CONTEXTIDR
	mcr	p15, 0, r1, c13, c0, 2	@ TPIDRURW
	mcr	p15, 0, r2, c13, c0, 3	@ TPIDRURO
	mcr	p15, 0, r3, c13, c0, 4	@ TPIDRPRW

	LDMDB	r8!, {r4-r7}
	mcr	p15, 0, r4, c7, c4, 0	@ PAR
	mcr	p15, 0, r5, c10, c2, 0	@ PRRR
	mcr	p15, 0, r6, c10, c2, 1	@ NMRR
	mcr	p15, 0, r7, c12, c0, 0	@ VBAR

	LDMDB	r8!, {r0,r1}
	mcr	p15, 0, r0, c15, c0, 1	@ diag
	mcr	p15, 0, r1, c1, c0, 2	@ cpacr

	LDMDB	r8!, {r0, r4}
	mcr	p15, 2, r0, c0, c0, 0	@ csselr
	mcr	p15, 0, r4, c15, c0, 0	@ pctlr

	/* Invalid L1-Cache */
	mov     r3,#0x0
	mcr     p15, 2, r3, c0, c0, 0    @ select L1 Data-cache
	mrc     p15, 1, r3, c0, c0, 0    @ Read Current Cache Size-
					 @	Identification Register

	ldr     r1,=0x1ff
	and     r3, r1, r3, LSR #13      @r3 = number of sets in cache
	mov     r0,#0x0
way_loop:
	mov     r1, #0x0                 @r1 -> set counter
set_loop:
	mov     r2, r0, LSL #30
	orr     r2, r1, LSL #5           @r2->set/way cache-op format
	mcr     p15, 0, r2, c7, c6, 2    @Invalid Line descript by r2
	add     r1, r1, #1               @increment set counter

	cmp     r1, r3                   @check if last set is reached...
	ble     set_loop                 @if not continue set_loop
	add     r0,r0, #1                @else increment way counter

	cmp     r0,#4                    @check if last way is reached
	blt     way_loop                 @if not,continue way_loop

	/**
	now restore the critial P15 register
	restore critial P15 register before MMU Enabled
	save CTRL_Register in r0
	save Aux_Ctrl_register in r1
	TTBR0 in r2
	TTBR1 in r3
	TTBCR in r4
	DAC   in R5
	**/

	ADD	r10,r10,#0x4

	LDMIA	r10, {r0-r5, r7-r9}

	MCR	p15, 0, r2, c2, c0, 0	@ TTBR0
	MCR	p15, 0, r3, c2, c0, 1	@ TTBR1
	MCR	p15, 0, r4, c2, c0, 2	@ TTBCR

	/**
	r0 store the Stored Control register value
	**/
	MCR    p15, 0, r0, c1, c0, 0 	@ turn on MMU, I-cache, etc
	instr_sync
	mov	pc, r9

mmu_enalbed:
	str	r7, [r8]

	mcr	p15, 0, r1, c1, c0, 1	@ actlr
	mcr	p15, 0, r5, c3, c0, 0	@ domain access control reg

	LDMFD   sp!, {r4-r11, pc}
ENDPROC (master_cpu_resume)


/* Function: hs_finish_suspend()
 *
 * This code is copied to Securam for execution, because DDR is set to
 * self-refresh mode. Here, final steps before setting master CPU to
 * deepsleep are included.
 *
 * After WFI, master CPU enters deepsleep. All codes after WFI is not
 * executed. When master CPU is waken up, master_cpu_resume() will be
 * called. Please read description there.
 */
	.align 3
ENTRY (hs_finish_suspend)
	instr_sync
	/**
	STEP1: Protect the DDR Train Address and Traning Data into Syscontrol
	We need not do it, it will be config in fastboot
	**/

	/**
	config DDR enter self-refresh state
	**/
	LDR r0,	=DDR_CTRLOR_BASE
	LDR r1,	=0x01
	STR r1,	[r0,#0x4]

	/* check DDR self-fresh status */
CheckDDREnterSF:
	LDR	r1, [r0, #0x0]
	TST	r1, #0x04
	BEQ	CheckDDREnterSF

	/**
	config DDR PHY enter CKE-Retention status
	fastboot code will do opposition relevent operations.
	**/
	LDR  r4,=REG_BASE_SCTRL
	LDR  r1,[r4,#0x20C]   @SCTRL SCPERCTRL3 register
	ORR  r1,r1,#0x3       @set sc_ddr_ret_en bit[1:0] to 0x3
	STR  r1,[r4,#0x20C]

	/**
	Set MDDRC's clock to DDRPHY's input clock
	fastboot code will do opposition relevent operations.
	**/
	LDR    r4,=REG_BASE_PMCTRL
	LDR    r1,=0x0
	STR    r1,[r4,#0xA8] @DDRCLKSEL

r_wait_mddrc_clk:
	LDR    r1,[r4,#0xA8]
	TST    r1,#0x2
	BNE    r_wait_mddrc_clk

	/*set ddr clk div*/		@360M
	LDR	r1, = 0x03
	STR	r1, [r4, #0x0AC]
r_waite_mddr_div:
	LDR	r1, [r4, #0x0AC]
	TST	r1, #0x20
	BEQ	r_waite_mddr_div

	/*ddr clk change to peri PLL*/
	MOV	r2, #0x0
	LDR	r1, =0x00
	STR	r1, [r4, #0x030]
r_wait_ddrcclk_sw:
	ADD	r2, r2, #0x1
	CMP	r2, #0x1000
	BEQ	r_wait_ddrcclk_ok
	LDR	r1, [r4, #0x30]
	CMP	r1, #0x00
	BNE	r_wait_ddrcclk_sw

r_wait_ddrcclk_ok:

	/*close GPU PLL*/
	LDR	r1, =0x00
	STR	r1, [r4, #0x028]

	/**
	Close LD03
	**/

	/*enable pmuspi*/
	/*pmuspi clk div 4*/
	LDR	r1, =REG_BASE_PCTRL
	LDR     r4, =0xFF0003
	STR	r4, [r1, #0x8]

	/*enable clk*/
	LDR	r1, =REG_BASE_SCTRL
	LDR	r4, =0x2
	STR	r4, [r1, #0x40]

	/*undo reset*/
	LDR	r4, =0x2
	STR	r4, [r1, #0x9C]

	/*close LDO3*/
	LDR	r1, =REG_BASE_PMUSPI
	LDR	r4, [r1, #0x8C]
	BIC	r4, #0x10
	STR	r4, [r1, #0x8C]

	/*disable pmuspi*/
	/*reset*/
	LDR	r1, =REG_BASE_SCTRL
	LDR	r4, =0x2
	STR	r4, [r1, #0x98]

	/*disable clk*/
	LDR	r4, =0x2
	STR	r4, [r1, #0x44]


	/**
	STEP2. Clear intr response mode status register
	Try clear intr response mode status first
	if the status is cleared, means there has no
	intr pending, go dpsleep, else do not configuration
	any dpsleep register and go back
	**/
	LDR   r4,=REG_BASE_SCTRL
	LDR   r1,=0x0
	STR   r1,[r4,#0xc]  @clear intr status register
	NOP
	NOP
	/* check if we are still in intr response status */
	/* 2012-2-14 do not care about wakeup intr*/
	@LDR   r1,[r4,#0xc]
	@TST   r1,#0x01
	@BNE   Back_from_WFI  @go directly to  Resume

	/* exit intr response mode */
	LDR r2,[r4,#8]
	BIC r2,#1
	STR r2,[r4,#8]

	/**
	STEP3 Protect EMMC/NAND Component IO, config WP to LOW CLOSE eMMC/NAND Component LDO
	NOW EMMC/NAND Driver do the protection operation, we do nothing here
	**/

	/**
	STEP4 config dpsleep register
	**/
	LDR   r4,=REG_BASE_SCTRL
	LDR   r1,[r4]
	LDR   r2,=0x01000007  @BIT24: Enable DpSleep Mode, BIT2|BIT1|BIT0 = 7
	BIC   r1,r1,r2        @clear first
	LDR   r2,=0x01000000  @BIT24: Enable DpSleep Mod=1,
			      @modctrl(BIT2|BIT1|BIT0) = 000 (Sleep)
	ORR   r1,r1,r2        @Enable DpSleep Mode,ModeCtrl=sleep
	STR   r1,[r4]

	/* STEP5 CHIP required, config L2CC for LOWPOWER */
	LDR   r4,=REG_BASE_L2CC
	LDR   r2,[r4,#0xF80]
	ORR   r1,r2,#0x1
	STR   r1,[r4,#0xF80]

	/**
	STEP6. CHIP required, configure SCU power status register
	       cause if we back from wfi, scu power status must be
	       restore back, we protect the data into r11
	**/
	LDR   r4,=REG_BASE_A9PER
	LDR   r11,[r4,#0x08]  @protect the SCU  power status to r11
	LDR   r1,=0x03030303  @all CPU to Power-off Mode
	STR   r1,[r4,#0x08]

	/**
	  STEP7. configure SCU Standby EN
	  CAUSTION: this configuration suggest to be set before the whole
		     system start
	**/
	LDR   R4,=REG_BASE_A9PER
	LDR   r1,[r4]
	ORR   r1,r1,#0x20
	STR   r1,[r4]

	/**
	  STEP9  to enable ACP''s clock as a must for SCUIDLE
	**/
	LDR     R4, =REG_BASE_SCTRL
	MOV     R1, #0x10000000  @BIT28 for ACP clock enable control
	STR     R1, [R4,#0x30] @Register SCPEREN1


	/**
	 STEP10  clear ScuRAM Ready FLAG,please refer to OnChipROM Design
	 FIXME: the FLAG also including the optional information
		 (Refer to OnChipROM design)
	**/
	LDR r4,=SECURAM_CODE_READY_FLAG
	LDR r1,=0x0
	STR r1,[r4,#0x0]

	/**
	 STEP11 Enter WFI
	 **/
	DSB
	WFI

	NOP
	NOP
	NOP
	NOP

Back_from_WFI:
	/**
	 We are draged back from an interrupt
	 Caustion: R6 is reserved to store the go-back PHY address

	STEP1: Restore the IO/LDO Configuration of EMMC/NAND Component
	WE DO Nothing here
	**/

	/* STEP2: Restore the Securam_CODE_READY FLAG.
	 * Refer to OnChipROM Design
	 */
	LDR	r4,=SECURAM_CODE_READY_FLAG
	LDR	r1,[r4]
	LDR	r2,=0xFFFF
	BIC	r1,r1,r2
	LDR 	r2,=0xBEEF  @0xBEEF is the SECURAM_CODE_READY_FLAG
	ORR 	r1,r1,r2
	STR 	r1,[r4,#0x0]

	/**
	 STEP3: make Sure system in Normal state
	 if system in SLOW mode, configuration to NORMAL mode
	 FIXME: Coding here if needed
	 **/
	LDR	r2, =REG_BASE_SCTRL
	LDR	r1, [r2]
	AND	r4, r1, #0x4
	CMP 	r4, #0x4
	BEQ	cpunormal
	ORR	r1, r1, #0x4
	STR	r1, [r2]
normalwait:
	LDR	r1, [r2]
	AND	r1, r1, #0x78
	CMP	r1, #0x20
	BNE	normalwait

cpunormal:

	/**
	 STEP4: Restore DDR Configuration to Normal
	 Restore DDR PHY CLK, exit CKE-Retention mode
	 **/

	/** change DDR PHY CLK to output mode **/
	/**
	FIXME: Remove the comments when fastboot add the
	relevent operations.
	**/
	LDR    r4,=REG_BASE_PMCTRL
	LDR    r1,=0x1
	STR    r1,[r4,#0xA8] @DDRCLKSEL

	/** exit CKE retention mode **/
	LDR  r4,=REG_BASE_SCTRL
	LDR  r1,[r4,#0x20C]   @SCTRL SCPERCTRL3 register
	BIC  r1,r1,#0x3       @set sc_ddr_ret_en bit[1:0] to 0x0
	STR  r1,[r4,#0x20C]

	/**
	Open LD03
	**/

	/*enable pmuspi*/
	/*pmuspi clk div 4*/
	LDR	r1, =REG_BASE_PCTRL
	LDR     r4, =0xFF0003
	STR	r4, [r1, #0x8]

	/*enable clk*/
	LDR	r1, =REG_BASE_SCTRL
	LDR	r4, =0x2
	STR	r4, [r1, #0x40]

	/*undo reset*/
	LDR	r4, =0x2
	STR	r4, [r1, #0x9C]

	/*open LDO3*/
	LDR	r1, =REG_BASE_PMUSPI
	LDR	r4, [r1, #0x8C]
	ORR	r4, #0x10
	STR	r4, [r1, #0x8C]

	/*disable pmuspi*/
	/*reset*/
	/*LDR	r1, =REG_BASE_SCTRL*/
	/*LDR	r4, =0x2*/
	/*STR	r4, [r1, #0x98]*/

	/*disable clk*/
	/*LDR	r4, =0x2*/
	/*STR	r4, [r1, #0x44]*/

	/*about 100ms*/
	LDR	r4, =0x2625A00
ldo3delay:
	SUBS	r4, r4, #0x1
	BNE	ldo3delay

	/** Config DDR leave self-refresh mode **/
	LDR r0,=DDR_CTRLOR_BASE
	LDR r1,=0x00
	STR r1,[r0,#0x4]

	/** check DDR self-refresh status **/
CheckDDRLeaveSF:
	LDR    r1, [r0, #0x0]
	TST    r1, #0x04
	BNE    CheckDDRLeaveSF

	/** STEP5 restore SCU CPU power states, which restore in r11 before **/
	LDR   r4,=REG_BASE_A9PER
	STR   r11,[r4,#0x08]  @restore the SCU  power status from r11

	/** STEP6 go Back to DDR Address Store in R6 **/
	MOV    pc, r6

ENDPROC (hs_finish_suspend)

	.ltorg

.global hi_cpu_godpsleep_ddrbase
hi_cpu_godpsleep_ddrbase:
	.word   hi_cpu_godpsleep_ddrbase

.global hi_cpu_godpsleep_phybase
hi_cpu_godpsleep_phybase:
	.word   hi_cpu_godpsleep_phybase
