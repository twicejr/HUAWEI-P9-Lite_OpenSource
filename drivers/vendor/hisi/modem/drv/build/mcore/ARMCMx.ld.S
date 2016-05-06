#include <bsp_dfs_training.h>

/* Configure memory regions */
MEMORY
{
  /* FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 128k */
  RAM  (rwx)            : ORIGIN = 0x10000000, LENGTH = 81k
}


/* Linker script to place sections and symbol values. Should be used together
 * with other linker script that defines memory regions FLASH and RAM.
 * It references following symbols, which must be defined in code:
 *   Reset_Handler : Entry of reset handler
 *
 * It defines following symbols, which code can use without definition:
 *   __exidx_start
 *   __exidx_end
 *   __etext
 *   __data_start__
 *   __preinit_array_start
 *   __preinit_array_end
 *   __init_array_start
 *   __init_array_end
 *   __fini_array_start
 *   __fini_array_end
 *   __data_end__
 *   __bss_start__
 *   __bss_end__
 *   __end__
 *   end
 *   __HeapLimit
 *   __StackLimit
 *   __StackTop
 *   __stack
 */
ENTRY(Reset_Handler)

SECTIONS
{
	.text :
	{
		__text_section_start = .;
		KEEP(*(.isr_vector))
		*(.text*)

		*(.rodata)
	} > RAM

	__etext = .;

	.data :
	{
		. = ALIGN(4);
		__data_start__ = .;
		*(vtable)
		*(.data*)
		__data_end__ = .;

	} > RAM

	.bss :
	{
		. = ALIGN(4);
		__bss_start__ = .;
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		__bss_end__ = .;
	} > RAM
	__file_size = __data_end__ - __text_section_start;
	
	.heap (COPY):
	{
		__end__ = .;
		end = __end__;
		*(.heap*)
		__HeapLimit = .;
	} > RAM

	/* .stack_dummy section doesn't contains any symbols. It is only
	 * used for linker to calculate size of stack sections, and assign
	 * values to stack symbols later */
	.stack_dummy (COPY):
	{
		*(.stack*)
	} > RAM

	/* Set stack top to end of RAM, and stack limit move down by
	 * size of stack_dummy section */
#ifdef DFS_DDR_TRANING_DATA_OFFSET
	__StackTop = ORIGIN(RAM) + LENGTH(RAM);
	/* 检查镜像是否覆盖频点数据 */
	ASSERT(DFS_DDR_TRAINING_DATA_ADDR >= __StackTop, "region RAM overflow DFS_DDR_TRAINING_DATA_ADDR, check product_config.define ")
#else
	__StackTop = ORIGIN(RAM) + 0x10000;
#endif
	__StackLimit = __StackTop - SIZEOF(.stack_dummy);
	PROVIDE(__stack = __StackTop);

	/* Check if data + heap + stack exceeds RAM limit */
	ASSERT(__StackLimit >= __HeapLimit, "region RAM overflowed with stack")
}
/**************************************************************************/
