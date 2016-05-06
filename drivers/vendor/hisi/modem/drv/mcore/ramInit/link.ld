SECTIONS
{
	ENTRY(main)
	. = 0x00;
	__file_start = .;
	.text : {
		*(header)
		*(.text)
		*(.rodata*)
		}
	.data : {
		*(.data)
		*(.got*)
		}	
	__file_size = . - __file_start;
	.bss : {
		*(.bss)
		}
}