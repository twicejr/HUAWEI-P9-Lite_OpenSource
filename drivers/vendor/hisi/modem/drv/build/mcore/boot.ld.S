#include <product_config.h>

SECTIONS
{
    .text 0x00000000 : AT (0x00000000)
    {
        _text = .;
        KEEP(*(.isr_vector))
        *(.text*)
        *(.rodata*)
    }
    _etext = .;

    .data 0x00000000 + SIZEOF(.text) : AT (SIZEOF(.text))
    {
        _data = .;
        *(.data*)
    }
    _edata = .;

    .bss 0x00000000 + SIZEOF(.text) + SIZEOF(.data) : AT (ADDR(.data) + SIZEOF(.data))
    {
        _bss = .;
        *(.bss*)
        *(COMMON)
    }
    _ebss = .;

    . = ALIGN(4); 
     __file_size = . - _text;
#ifdef DFS_DDR_TRANING_DATA_OFFSET
     /* for v7r5 ddr dfs training data only */
     .ddr_training_data DFS_DDR_TRANING_DATA_OFFSET : AT (DFS_DDR_TRANING_DATA_OFFSET)
     {
          __ddr_training_data_start = .;
          *(.ddr_training)
     }
#endif
}
