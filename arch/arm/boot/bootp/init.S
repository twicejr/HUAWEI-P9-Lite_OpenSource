
		.section .start,#alloc,#execinstr
		.type	_start, #function
		.globl	_start

_start:		add	lr, pc, #-0x8		@ lr = current load addr
		adr	r13, data
		ldmia	r13!, {r4-r6}		@ r5 = dest, r6 = length
		add	r4, r4, lr		@ r4 = initrd_start + load addr
		bl	move			@ move the initrd

/*
 * Setup the initrd parameters to pass to the kernel.  This can only be
 * passed in via the tagged list.
 */
		ldmia	r13, {r5-r9}		@ get size and addr of initrd
						@ r5 = ATAG_CORE
						@ r6 = ATAG_INITRD2
						@ r7 = initrd start
						@ r8 = initrd end
						@ r9 = param_struct address

		ldr	r10, [r9, #4]		@ get first tag
		teq	r10, r5			@ is it ATAG_CORE?
/*
 * If we didn't find a valid tag list, create a dummy ATAG_CORE entry.
 */
		movne	r10, #0			@ terminator
		movne	r4, #2			@ Size of this entry (2 words)
		stmneia	r9, {r4, r5, r10}	@ Size, ATAG_CORE, terminator


taglist:	ldr	r10, [r9, #0]		@ tag length
		teq	r10, #0			@ last tag (zero length)?
		addne	r9, r9, r10, lsl #2
		bne	taglist

		mov	r5, #4			@ Size of initrd tag (4 words)
		stmia	r9, {r5, r6, r7, r8, r10}
		b	kernel_start		@ call kernel

/*
 * Move the block of memory length r6 from address r4 to address r5
 */
move:		ldmia	r4!, {r7 - r10}		@ move 32-bytes at a time
		stmia	r5!, {r7 - r10}
		ldmia	r4!, {r7 - r10}
		stmia	r5!, {r7 - r10}
		subs	r6, r6, #8 * 4
		bcs	move
		mov	pc, lr

		.size	_start, . - _start

		.align

		.type	data,#object
data:		.word	initrd_start		@ source initrd address
		.word	initrd_phys		@ destination initrd address
		.word	initrd_size		@ initrd size

		.word	0x54410001		@ r5 = ATAG_CORE
		.word	0x54420005		@ r6 = ATAG_INITRD2
		.word	initrd_phys		@ r7
		.word	initrd_size		@ r8
		.word	params_phys		@ r9
		.size	data, . - data
