/******************************************************************************/
/*  Copyright (C), 2007-2013, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name     : hi_nandc.h */
/* Version       : 2.0 */
/* Author        : xxx*/
/* Created       : 2013-02-24*/
/* Last Modified : */
/* Description   :  The C union definition file for the module nandc*/
/* Function List : */
/* History       : */
/* 1 Date        : */
/* Author        : xxx*/
/* Modification  : Create file */
/******************************************************************************/

#ifndef __HI_NANDC_H__
#define __HI_NANDC_H__

/*
 * Project: hi
 * Module : nandc
 */

#include <bsp_memmap.h>

#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4)
#endif

/********************************************************************************/
/*    nandc 寄存器偏移定义（项目名_模块名_寄存器名_OFFSET)        */
/********************************************************************************/
#define    HI_NFC_CON_OFFSET                                 (0x0) /* NANDC配置寄存器。 */
#define    HI_NFC_PWIDTH_OFFSET                              (0x4) /* 读写脉冲宽度配置寄存器。 */
#define    HI_NFC_OPIDLE_OFFSET                              (0x8) /* 操作间隔配置寄存器。 */
#define    HI_NFC_CMD_OFFSET                                 (0xC) /* 命令字配置寄存器。 */
#define    HI_NFC_ADDRL_OFFSET                               (0x10) /* 地位地址配置寄存器。 */
#define    HI_NFC_ADDRH_OFFSET                               (0x14) /* 高位地址配置寄存器。 */
#define    HI_NFC_DATA_NUM_OFFSET                            (0x18) /* 读写数据数目配置寄存器。 */
#define    HI_NFC_OP_OFFSET                                  (0x1C) /* 操作寄存器。 */
#define    HI_NFC_STATUS_OFFSET                              (0x20) /* 状态寄存器。 */
#define    HI_NFC_INTEN_OFFSET                               (0x24) /* 中断使能寄存器。 */
#define    HI_NFC_INTS_OFFSET                                (0x28) /* 中断状态寄存器。 */
#define    HI_NFC_INTCLR_OFFSET                              (0x2C) /* 中断清除寄存器。 */
#define    HI_NFC_LOCK_OFFSET                                (0x30) /* 锁地址配置寄存器。 */
#define    HI_NFC_LOCK_SA0_OFFSET                            (0x34) /* 锁起始地址0配置寄存器。 */
#define    HI_NFC_LOCK_SA1_OFFSET                            (0x38) /* 锁起始地址1配置寄存器。 */
#define    HI_NFC_LOCK_SA2_OFFSET                            (0x3C) /* 锁起始地址2配置寄存器。 */
#define    HI_NFC_LOCK_SA3_OFFSET                            (0x40) /* 锁起始地址3配置寄存器。 */
#define    HI_NFC_LOCK_EA0_OFFSET                            (0x44) /* 锁结束地址0配置寄存器。 */
#define    HI_NFC_LOCK_EA1_OFFSET                            (0x48) /* 锁结束地址1配置寄存器。 */
#define    HI_NFC_LOCK_EA2_OFFSET                            (0x4C) /* 锁结束地址2配置寄存器。 */
#define    HI_NFC_LOCK_EA3_OFFSET                            (0x50) /* 锁结束地址3配置寄存器。 */
#define    HI_NFC_EXPCMD_OFFSET                              (0x54) /* 扩展页命令寄存器。 */
#define    HI_NFC_EXBCMD_OFFSET                              (0x58) /* 扩展块命令寄存器。 */
#define    HI_NFC_ECC_TEST_OFFSET                            (0x5C) /* ECC测试寄存器。 */
#define    HI_NFC_DMA_CTRL_OFFSET                            (0x60) /* DMA控制寄存器。 */
#define    HI_NFC_BADDR_D_OFFSET                             (0x64) /* 传送数据区的基地址寄存器。 */
#define    HI_NFC_BADDR_OOB_OFFSET                           (0x68) /* 传送OOB区的基地址寄存器。 */
#define    HI_NFC_DMA_LEN_OFFSET                             (0x6C) /* 传送长度寄存器。 */
#define    HI_NFC_OP_PARA_OFFSET                             (0x70) /* 操作参数寄存器。 */
#define    HI_NFC_VERSION_OFFSET                             (0x74) /* nandc版本寄存器。 */
#define    HI_NFC_SEGMENT_ID_OFFSET                          (0x84) /* DMA读写nandflash的数据段ID寄存器。 */
#define    HI_NFC_FIFO_EMPTY_OFFSET                          (0x90) /* 内部fifo状态寄存器。 */
#define    HI_NFC_BOOT_SET_OFFSET                            (0x94) /* boot参数设定寄存器。 */
#define    HI_NF_LP_CTRL_OFFSET                              (0x9C) /* nandc 的低功耗控制寄存器。 */
#define    HI_NFC_ERR_NUM0_BUF0_OFFSET                       (0xA0) /* nandflash 第一次buffer纠错统计寄存器0 */
#define    HI_NFC_ERR_NUM1_BUF0_OFFSET                       (0xA4) /* nandflash 第一次buffer纠错统计寄存器1 */
#define    HI_NFC_ERR_NUM0_BUF1_OFFSET                       (0xA8) /* nandflash 第二次buffer纠错统计寄存器0 */
#define    HI_NFC_ERR_NUM1_BUF1_OFFSET                       (0xAC) /* nandflash 第二次buffer纠错统计寄存器1 */
#define    HI_NF_RB_MODE_OFFSET                              (0xB0) /* nandflash 的ready_busy模式寄存器。 */
#define    HI_NFC_BADDR_D1_OFFSET                            (0xB4) /* 传送数据区的基地址寄存器1。 */
#define    HI_NFC_BADDR_D2_OFFSET                            (0xB8) /* 传送数据区的基地址寄存器2。 */
#define    HI_NFC_BADDR_D3_OFFSET                            (0xBC) /* 传送数据区的基地址寄存器3。 */
#define    HI_NFC_BOOT_CFG_OFFSET                            (0xC4) /* nandflash 的boot配置寄存器 */
#define    HI_NFC_OOB_SEL_OFFSET                             (0xC8) /* 16bit ECC，OOB区长度选择寄存器 */
#define    HI_NFC_MEM_CTRL_OFFSET                            (0xCC) /* 例化mem管理 */
#define    HI_NFC_SYNC_TIMING_OFFSET                         (0xD0) /* 同步NAND读写时序参数 */
#define    HI_NFC_DLL_CONTROL_OFFSET                         (0xD4) /* DLL模块配置信息 */
#define    HI_NFC_DLL_STATUS_OFFSET                          (0xD8) /* DLL模块状态信息 */

/********************************************************************************/
/*    nandc 寄存器定义（项目名_模块名_寄存器名_T)        */
/********************************************************************************/
typedef union
{
    struct
    {
        unsigned int    op_mode                    : 1; /* [0..0] NANDC操作模式配置。0：NANDC处于boot模式；1：NANDC处于normal模式。 */
        unsigned int    pagesize                   : 3; /* [3..1] NAND Flash的页大小。000：保留；001：2KByte；010：4KByte；011：8KByte；100：16KByte；101~111：保留。复位值由管脚NFC_PAGE_SIZE决定。 */
        unsigned int    bus_width                  : 1; /* [4..4] NAND Flash的数据线宽度。0：8bit；1：16bit。复位值由管脚NFC_BUS_WIDE决定。 */
        unsigned int    reserved_2                 : 2; /* [6..5] 保留。 */
        unsigned int    cs_ctrl                    : 1; /* [7..7] 片选控制。0：在NAND Flash为busy时，保持片选信号为0；1：在NAND Flash为busy时，把片选信号置位1。该模式对应NAND Flash的cs do not care模式。 */
        unsigned int    rb_sel                     : 1; /* [8..8] 当外接多个NANDFlash器件（多个片选）时有效。0：NAND Flash器件共用同一个ready/busy信号；1：NAND Flash器件使用各自独立的ready/busy信号。当只接一个NAND Flash器件时，只用片选信号ce0和ready_busy0。 */
        unsigned int    ecc_type                   : 3; /* [11..9] ECC模式选择。000：无ECC。001：1bit 模式；010：4bit模式；011：16bit模式；100：24bits 模式 for 1KB；101：40bits模式；110: 64bits模式；111：保留。复位值由管脚NFC_ECC_TYPE决定。 */
        unsigned int    reserved_1                 : 1; /* [12..12] 保留。 */
        unsigned int    randomizer_en              : 1; /* [13..13] randomizer功能。0：不打开randomizer功能；1：打开randomizer功能。 */
        unsigned int    nf_mode                    : 2; /* [15..14] NAND Flash接口类型选择。00：异步nand接口；01：toggle nand接口；10：onfi2.3 nand接口；11：onfi3.0 nand接口。 */
        unsigned int    reserved_0                 : 16; /* [31..16] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NFC_CON_T;    /* NANDC配置寄存器。 */

typedef union
{
    struct
    {
        unsigned int    w_lcnt                     : 4; /* [3..0] NAND Flash写信号低电平宽度。0x1～0xF：2～16个接口时钟周期。 */
        unsigned int    r_lcnt                     : 4; /* [7..4] NAND Flash读信号低电平宽度。0x2～0xF：3～16个接口时钟周期。 */
        unsigned int    rw_hcnt                    : 4; /* [11..8] NAND Flash读/写信号高电平宽度。0x1～0xF：2～16个接口时钟周期。 */
        unsigned int    reserved                   : 20; /* [31..12] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NFC_PWIDTH_T;    /* 读写脉冲宽度配置寄存器。 */

typedef union
{
    struct
    {
        unsigned int    wait_ready_wait            : 4; /* [3..0] NAND Flash的ready信号变高之后，延时一段时间,之后才能发出读信号读数据。延时的周期数为：frb_idle*8。 */
        unsigned int    cmd2_wait                  : 4; /* [7..4] 发送完command2之后的等待周期数。0000～1111：1～16个接口时钟周期。 */
        unsigned int    rsv                        : 4; /* [11..8] 保留。 */
        unsigned int    addr_wait                  : 4; /* [15..12] 发送完address之后的等待周期数。0000～1111：配置值。延时的接口时钟周期数为：addr_wait*8。 */
        unsigned int    cmd1_wait                  : 4; /* [19..16] 发送完command1之后的等待周期数。0000～1111：1～16个接口时钟周期。 */
        unsigned int    frb_wait                   : 4; /* [23..20] 发出读写命令后，先延时一段时间，然后再检测ready信号是否变为高电平。延时的接口时钟周期数为：frb_wait*8。 */
        unsigned int    reserved                   : 8; /* [31..24] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NFC_OPIDLE_T;    /* 操作间隔配置寄存器。 */

typedef union
{
    struct
    {
        unsigned int    cmd1                       : 8; /* [7..0] Controller发给NAND Flash的第1个命令。 */
        unsigned int    cmd2                       : 8; /* [15..8] Controller发给NAND Flash的第2个命令。 */
        unsigned int    read_status_cmd            : 8; /* [23..16] Read status命令字 */
        unsigned int    reserved                   : 8; /* [31..24] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NFC_CMD_T;    /* 命令字配置寄存器。 */

typedef union
{
    struct
    {
        unsigned int    addr_l                     : 32; /* [31..0] NAND Flash低32bit地址。 */
    } bits;
    unsigned int    u32;
}HI_NFC_ADDRL_T;    /* 地位地址配置寄存器。 */

typedef union
{
    struct
    {
        unsigned int    addr_h                     : 8; /* [7..0] NAND Flash高8bit地址。 */
        unsigned int    reserved                   : 24; /* [31..8] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NFC_ADDRH_T;    /* 高位地址配置寄存器。 */

typedef union
{
    struct
    {
        unsigned int    nfc_data_num               : 14; /* [13..0] 配置NANDC随机读写的数据个数，最大9120字节。只在ecc_type等于00时有效。 */
        unsigned int    reserved                   : 18; /* [31..14] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NFC_DATA_NUM_T;    /* 读写数据数目配置寄存器。 */

typedef union
{
    struct
    {
        unsigned int    read_status_en             : 1; /* [0..0] 该标志为1时，使能向NAND发出读status的0x70命令，并从NAND Flash读取状态数据，返回的数据写入NANDC状态寄存器的nf_status域中（而不写入内部buffer）。0：禁止；1：使能。 */
        unsigned int    read_data_en               : 1; /* [1..1] 启动读状态机，从NAND Flash读数据使能。read_data_en和write_data_en不能同时为1。0：禁止；1：使能。 */
        unsigned int    wait_ready_en              : 1; /* [2..2] 等待ready/busy信号变高使能。0：禁止；1：使能。 */
        unsigned int    cmd2_en                    : 1; /* [3..3] 发command2命令使能。0：禁止；1：使能。 */
        unsigned int    write_data_en              : 1; /* [4..4] 向NAND Flash写数据使能。read_data_en和write_data_en 不能同时为1。0：禁止；1：使能。 */
        unsigned int    addr_en                    : 1; /* [5..5] 向NAND写操作地址使能 。 0：禁止；1：使能。 */
        unsigned int    cmd1_en                    : 1; /* [6..6] 发command1命令使能。0：禁止；1：使能。 */
        unsigned int    nf_cs                      : 2; /* [8..7] 选择操作的NAND Flash器件：00：cs0；  01：cs1；10：cs2；  11：cs3。 */
        unsigned int    address_cycles             : 3; /* [11..9] 发给NAND Flash的地址周期数。 */
        unsigned int    read_id_en                 : 1; /* [12..12] 对于toggle nand，该标志为一指示器件进行读状态寄存器操作。0：非读ID操作；1：读ID操作。 */
        unsigned int    rw_reg_en                  : 1; /* [13..13] 对于同步nand进行读写寄存器操作。0：读写数据操作；1：读写寄存器操作。 */
        unsigned int    reserved                   : 18; /* [31..14] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NFC_OP_T;    /* 操作寄存器。 */

typedef union
{
    struct
    {
        unsigned int    nfc_ready                  : 1; /* [0..0] 指示控制器进行一次操作当前所处的状态。0：controller正在进行操作；1：操作完成，可以接收下一次命令。当写operation寄存器启动nandc操作时，该位自动清零。 */
        unsigned int    nf0_ready                  : 1; /* [1..1] 片选0对应的nand器件的ready/busy信号状态。当外接两多个flash器件且使用各自独立的ready_busy信号时有效。因为默认两多个nandFlash器件共用同一个ready/busy信号，该bit复位值为0。 */
        unsigned int    nf1_ready                  : 1; /* [2..2] 片选1对应的nand器件的ready/busy信号状态。当外接两多个flash器件且使用各自独立的ready_busy信号时有效。因为默认两多个nandFlash器件共用同一个ready/busy信号，该bit复位值为0。 */
        unsigned int    nf2_ready                  : 1; /* [3..3] 片选2对应的nand器件的ready/busy信号状态。当外接两多个flash器件且使用各自独立的ready_busy信号时有效。因为默认两多个nandFlash器件共用同一个ready/busy信号，该bit复位值为0。 */
        unsigned int    nf3_ready                  : 1; /* [4..4] 片选3对应的nand器件的ready/busy信号状态。当外接两多个flash器件且使用各自独立的ready_busy信号时有效。因为默认两多个nandFlash器件共用同一个ready/busy信号，该bit复位值为0。 */
        unsigned int    reserved_1                 : 3; /* [7..5] 保留。 */
        unsigned int    nf_status                  : 8; /* [15..8] 从Flash读回的NAND Flash的status数据。只在operation寄存器的read_status标志为1，且该寄存器的nandc_ready标志为1时有效。 */
        unsigned int    nfc_ecc_type               : 3; /* [18..16] NAND控制器内部使用的ecc纠错信息。读取出来的值含义和nfc_con寄存器ecc_type相同。 */
        unsigned int    nfc_randomizer_en          : 1; /* [19..19] NAND控制器内部使用randomizer状态。0：禁止；1：使能。 */
        unsigned int    reserved_0                 : 12; /* [31..20] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NFC_STATUS_T;    /* 状态寄存器。 */

typedef union
{
    struct
    {
        unsigned int    op_done_en                 : 1; /* [0..0] Nfc本次操作结束中断。0：禁止；1：使能。 */
        unsigned int    cs0_done_en                : 1; /* [1..1] 片选cs0对应的ready busy信号由低变高，产生中断。0：禁止；1：使能。 */
        unsigned int    cs1_done_en                : 1; /* [2..2] 片选cs1对应的ready busy信号由低变高，产生中断。0：禁止；1：使能。 */
        unsigned int    cs2_done_en                : 1; /* [3..3] 片选cs2对应的ready busy信号由低变高，产生中断。0：禁止；1：使能。 */
        unsigned int    cs3_done_en                : 1; /* [4..4] 片选cs3对应的ready busy信号由低变高，产生中断。0：禁止；1：使能。 */
        unsigned int    err_valid_en               : 1; /* [5..5] 可纠正的错误，产生中断。0：禁止；1：使能。 */
        unsigned int    err_invalid_en             : 1; /* [6..6] 不可纠正错误，产生中断。0：禁止；1：使能。 */
        unsigned int    ahb_op_en                  : 1; /* [7..7] Nfc读写flash数据期间，cpu读写nfc buffer错误中断使能。0：禁止；1：使能。 */
        unsigned int    wr_lock_en                 : 1; /* [8..8] 对lock地址进行写操作错误中断使能0：禁止；1：使能。 */
        unsigned int    dma_done_en                : 1; /* [9..9] dma传输完成中断使能。0：禁止；1：使能。 */
        unsigned int    dma_err_en                 : 1; /* [10..10] dma传输总线出现错误中断使能。0：禁止；1：使能。 */
        unsigned int    reserved                   : 21; /* [31..11] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NFC_INTEN_T;    /* 中断使能寄存器。 */

typedef union
{
    struct
    {
        unsigned int    op_done                    : 1; /* [0..0] controller本次操作结束中断。写operation寄存器后，该标志自动清零。0：无中断；1：有中断。 */
        unsigned int    cs0_done                   : 1; /* [1..1] 片选cs0对应的 ready busy信号由低变高，产生中断。当外接两个flash器件，同时两个器件使用各自独立的ready_busy信号时有效。否则，该bit一直保持为0；0：无中断；1：有中断。 */
        unsigned int    cs1_done                   : 1; /* [2..2] 片选cs1对应的 ready busy信号由低变高，产生中断。当外接两个flash器件，同时两个器件使用各自独立的ready_busy信号时有效。否则，该bit一直保持为0；0：无中断；1：有中断。 */
        unsigned int    cs2_done                   : 1; /* [3..3] 片选cs2对应的 ready busy信号由低变高，产生中断。当外接两个flash器件，同时两个器件使用各自独立的ready_busy信号时有效。否则，该bit一直保持为0；0：无中断；1：有中断。 */
        unsigned int    cs3_done                   : 1; /* [4..4] 片选cs3对应的 ready busy信号由低变高，产生中断。当外接两个flash器件，同时两个器件使用各自独立的ready_busy信号时有效。否则，该bit一直保持为0；0：无中断；1：有中断。 */
        unsigned int    err_valid                  : 1; /* [5..5] 可纠正的错误。1bit纠错模式下，校验512byte数据中出现1it错误，产生中断。4bit纠错模式下，ecc校验1024byte数据中出现1－8bit错误，产生中断。8bit纠错模式下，校验1024byte数据出现1 —16bit以上错误，产生中断。24bit纠错模式下，校验1024byte数据中出现1－24bit错误，产生中断。40bit纠错模式下，校验1024byte数据中出现1－40bit错误，产生中断。64bit纠错模式下，校验1024byte数据中出现1－64bit错误，产生中断。0：无中断；1：有中断。 */
        unsigned int    err_invalid                : 1; /* [6..6] 不可纠正的错误。1bit纠错模式下，校验512byte数据中出现2bit以上错误，产生中断。4bit纠错模式下，校验1024byte数据中出现8bit以上错误，产生中断。8bit纠错模式下，校验1024byte数据中出现16bit以上错误，产生中断。24bit纠错模式下，校验1024byte数据中出现24bit以上错误，产生中断。40bit纠错模式下，校验1024byte数据中出现40bit以上错误，产生中断。64bit纠错模式下，校验1024byte数据中出现64bit以上错误，产生中断。0：无中断；1：有中断。 */
        unsigned int    ahb_op_err                 : 1; /* [7..7] Nfc对flash进行数据操作期间，cpu读写nfc buffer。0：无中断；1：有中断。 */
        unsigned int    wr_lock_err                : 1; /* [8..8] 对lock地址进行写操作。0：无中断；1：有中断。 */
        unsigned int    dma_done                   : 1; /* [9..9] dma传输完成中断。0：无中断；1：有中断。 */
        unsigned int    dma_err                    : 1; /* [10..10] dma传输总线出现错误中断。0：无中断；1：有中断。 */
        unsigned int    reserved                   : 21; /* [31..11] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NFC_INTS_T;    /* 中断状态寄存器。 */

typedef union
{
    struct
    {
        unsigned int    op_done_clr                : 1; /* [0..0] 清除op_done中断，写1清除。 */
        unsigned int    cs0_done_clr               : 1; /* [1..1] 清除cs0_done中断，写1清除。 */
        unsigned int    cs1_done_clr               : 1; /* [2..2] 清除cs1_done中断，写1清除。 */
        unsigned int    cs2_done_clr               : 1; /* [3..3] 清除cs2_done中断，写1清除。 */
        unsigned int    cs3_done_clr               : 1; /* [4..4] 清除cs3_done中断，写1清除。 */
        unsigned int    err_valid_clr              : 1; /* [5..5] 清除err_valid中断，写1清除。 */
        unsigned int    err_invalid_clr            : 1; /* [6..6] 清除err_invalid中断，写1清除。 */
        unsigned int    ahb_op_err_clr             : 1; /* [7..7] 清除ahb_op_err 中断，写1清除。 */
        unsigned int    wr_lock_err_clr            : 1; /* [8..8] 清除wr_lock_err中断，写1清除。 */
        unsigned int    dma_done_clr               : 1; /* [9..9] 清除dma_done，写1清除。 */
        unsigned int    dma_err_clr                : 1; /* [10..10] 清除dma传输总线错误中断，写1清除。 */
        unsigned int    reserved                   : 21; /* [31..11] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NFC_INTCLR_T;    /* 中断清除寄存器。 */

typedef union
{
    struct
    {
        unsigned int    lock_down                  : 1; /* [0..0] Flash lock模式。1：lock-down模式，一次性写1，只有硬件reset才能对该位写0；0：lock模式。 */
        unsigned int    global_lock_en             : 1; /* [1..1] Flash全局lock使能。1：使能；0：禁止。 */
        unsigned int    lock_en                    : 1; /* [2..2] Flash lock使能。1：使能；0：禁止。 */
        unsigned int    lock_excmd_en              : 1; /* [3..3] 针对扩展写命令（新器件有可能添加的新命令），对保护地址进行写保护使能。1：使能；0：禁止。 */
        unsigned int    reserved                   : 28; /* [31..4] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NFC_LOCK_T;    /* 锁地址配置寄存器。 */

typedef union
{
    struct
    {
        unsigned int    flash_lock_addr0           : 19; /* [18..0] 锁存首地址0，最低位对应flash row addr[5]。 */
        unsigned int    flash_lock_cs              : 2; /* [20..19] 锁存首地址0对应的片选。00：片选0；01：片选1；10：片选2；11：片选3。 */
        unsigned int    reserved                   : 11; /* [31..21] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NFC_LOCK_SA0_T;    /* 锁起始地址0配置寄存器。 */

typedef union
{
    struct
    {
        unsigned int    flash_lock_addr1           : 19; /* [18..0] 锁存首地址1，最低位对应flash row addr[5]。 */
        unsigned int    flash_lock_cs              : 2; /* [20..19] 锁存首地址1对应的片选。00：片选0；01：片选1；10：片选2；11：片选3。 */
        unsigned int    reserved                   : 11; /* [31..21] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NFC_LOCK_SA1_T;    /* 锁起始地址1配置寄存器。 */

typedef union
{
    struct
    {
        unsigned int    flash_lock_addr2           : 19; /* [18..0] 锁存首地址2，最低位对应flash row addr[5]。 */
        unsigned int    flash_lock_cs              : 2; /* [20..19] 锁存首地址2对应的片选。00：片选0；01：片选1；10：片选2；11：片选3。 */
        unsigned int    reserved                   : 11; /* [31..21] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NFC_LOCK_SA2_T;    /* 锁起始地址2配置寄存器。 */

typedef union
{
    struct
    {
        unsigned int    flash_lock_addr3           : 19; /* [18..0] 锁存首地址3，最低位对应flash row addr[5]。 */
        unsigned int    flash_lock_cs              : 2; /* [20..19] 锁存首地址3对应的片选。00：片选0；01：片选1；10：片选2；11：片选3。 */
        unsigned int    reserved                   : 11; /* [31..21] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NFC_LOCK_SA3_T;    /* 锁起始地址3配置寄存器。 */

typedef union
{
    struct
    {
        unsigned int    flash_lock_eaddr0          : 19; /* [18..0] 锁存结束地址0，最低位对应flash row addr[5]。 */
        unsigned int    flash_lock_cs              : 2; /* [20..19] 锁存结束地址0对应的片选。00：片选0；01：片选1；10：片选2；11：片选3。 */
        unsigned int    reserved                   : 11; /* [31..21] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NFC_LOCK_EA0_T;    /* 锁结束地址0配置寄存器。 */

typedef union
{
    struct
    {
        unsigned int    flash_lock_eaddr1          : 19; /* [18..0] 锁存结束地址1，最低位对应flash row addr[5]。 */
        unsigned int    flash_lock_cs              : 2; /* [20..19] 锁存结束地址1对应的片选。00：片选0；01：片选1；10：片选2；11：片选3。 */
        unsigned int    reserved                   : 11; /* [31..21] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NFC_LOCK_EA1_T;    /* 锁结束地址1配置寄存器。 */

typedef union
{
    struct
    {
        unsigned int    flash_lock_eaddr2          : 19; /* [18..0] 锁存结束地址2，最低位对应flash row addr[5]。 */
        unsigned int    flash_lock_cs              : 2; /* [20..19] 锁存结束地址2对应的片选。00：片选0；01：片选1；10：片选2；11：片选3。 */
        unsigned int    reserved                   : 11; /* [31..21] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NFC_LOCK_EA2_T;    /* 锁结束地址2配置寄存器。 */

typedef union
{
    struct
    {
        unsigned int    flash_lock_eaddr3          : 19; /* [18..0] 锁存结束地址3，最低位对应flash row addr[5]。 */
        unsigned int    flash_lock_cs              : 2; /* [20..19] 锁存结束地址3对应的片选。00：片选001：片选110：片选211：片选3 */
        unsigned int    reserved                   : 11; /* [31..21] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NFC_LOCK_EA3_T;    /* 锁结束地址3配置寄存器。 */

typedef union
{
    struct
    {
        unsigned int    ex_pcmd0                   : 8; /* [7..0] Flash扩展页写操作命令0。 */
        unsigned int    ex_pcmd1                   : 8; /* [15..8] Flash扩展页写操作命令1。 */
        unsigned int    ex_pcmd2                   : 8; /* [23..16] Flash扩展页写操作命令2。 */
        unsigned int    ex_pcmd3                   : 8; /* [31..24] Flash扩展页写操作命令3 */
    } bits;
    unsigned int    u32;
}HI_NFC_EXPCMD_T;    /* 扩展页命令寄存器。 */

typedef union
{
    struct
    {
        unsigned int    ex_bcmd0                   : 8; /* [7..0] Flash扩展块写操作命令0。 */
        unsigned int    ex_bcmd1                   : 8; /* [15..8] Flash扩展块写操作命令1。 */
        unsigned int    reserved                   : 16; /* [31..16] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NFC_EXBCMD_T;    /* 扩展块命令寄存器。 */

typedef union
{
    struct
    {
        unsigned int    enc_only                   : 1; /* [0..0] 只编码使能。向该寄存器位写1时，启动ECC编码，但不启动读写NAND Flash；读该寄存器位时，返回值含义：1：ECC编解码结束；0：正在编解码。 */
        unsigned int    dec_only                   : 1; /* [1..1] 只解码使能。向该寄存器位写1时，启动ECC解码，但不启动读写NAND Flash；读该寄存器位时，返回0。 */
        unsigned int    ecc_mask                   : 1; /* [2..2] ECC功能掩码。1：不进行ecc校验和纠错。但读写NANDFlash数据结构仍按照ecc_type的格式进行转换；0：按ecc_type的值决定是否进行校验和纠错。 */
        unsigned int    reserved_1                 : 1; /* [3..3] 保留。 */
        unsigned int    bb_err                     : 1; /* [4..4] 因为bad_block，boot失败。0：不是坏块，可boot；1：坏块，boot失败； */
        unsigned int    reserved_0                 : 27; /* [31..5] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NFC_ECC_TEST_T;    /* ECC测试寄存器。 */

typedef union
{
    struct
    {
        unsigned int    dma_start                  : 1; /* [0..0] 启动dma操作。向该bit写1启动DMA操作，该bit保持为1，直到dma操作结束。向该bit写0无效。启动dma操作后，读该bit如果返回0，表示dma操作结束。 */
        unsigned int    dma_wr_en                  : 1; /* [1..1] DMA读写使能。0：读；1：写。 */
        unsigned int    reserved_1                 : 2; /* [3..2] 保留。 */
        unsigned int    burst4_en                  : 1; /* [4..4] burst4使能。0：禁止；1：使能。 */
        unsigned int    burst8_en                  : 1; /* [5..5] burst8使能。0：禁止；1：使能。 */
        unsigned int    burst16_en                 : 1; /* [6..6] burst16使能。0：禁止；1：使能。 */
        unsigned int    dma_addr_num               : 1; /* [7..7] 地址数。0：5个地址；1：4个地址。 */
        unsigned int    dma_nf_cs                  : 2; /* [9..8] 选择DMA操作的NAND Flash器件。00：cs0；  01：cs1。10：cs2；  11：cs3。 */
        unsigned int    rsv                        : 1; /* [10..10] 保留。 */
        unsigned int    wr_cmd_disable             : 1; /* [11..11] 选择DMA写操作时，是否发出写命令。0：NANDC发起完整的写NAND Flash时序；1：NANDC只发起写数据的时序，不发起写命令时序。只在DMA写NAND Flash时有效。 */
        unsigned int    dma_rd_oob                 : 1; /* [12..12] DMA读操作时，选择是只读OOB还是整个page读。0：读整个page；1：只读OOB操作。 */
        unsigned int    reserved_0                 : 19; /* [31..13] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NFC_DMA_CTRL_T;    /* DMA控制寄存器。 */

typedef union
{
    struct
    {
        unsigned int    base_addr_d                : 32; /* [31..0] 读写DDR数据区的基地址。 */
    } bits;
    unsigned int    u32;
}HI_NFC_BADDR_D_T;    /* 传送数据区的基地址寄存器。 */

typedef union
{
    struct
    {
        unsigned int    base_addr_oob              : 32; /* [31..0] 读OOB区数据的DDR基地址。 */
    } bits;
    unsigned int    u32;
}HI_NFC_BADDR_OOB_T;    /* 传送OOB区的基地址寄存器。 */

typedef union
{
    struct
    {
        unsigned int    reserved_1                 : 16; /* [15..0] 保留。 */
        unsigned int    len_oob                    : 12; /* [27..16] DMA写nandflash时OOB区的长度,需要长字(4byte)对齐。(只在ECC0模式下有效,在其他ECC模式下，oob的长度是固定的） */
        unsigned int    reserved_0                 : 4; /* [31..28] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NFC_DMA_LEN_T;    /* 传送长度寄存器。 */

typedef union
{
    struct
    {
        unsigned int    data_rw_en                 : 1; /* [0..0] NAND Flash数据区读写使能。0：禁止；1：使能。 */
        unsigned int    oob_rw_en                  : 1; /* [1..1] NAND Flash冗余区读写使能。0：禁止；1：使能。 */
        unsigned int    data_edc_en                : 1; /* [2..2] 校验使能。0：禁止；1：使能。编程模式下，生成ECC码使能。读数据模式下，进行校验使能。 */
        unsigned int    oob_edc_en                 : 1; /* [3..3] oob区校验使能。0：禁止；1：使能。编程模式下，对oob区生成ECC码使能。读数据模式下，对oob区进行校验使能。 */
        unsigned int    reserved                   : 28; /* [31..4] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NFC_OP_PARA_T;    /* 操作参数寄存器。 */

typedef union
{
    struct
    {
        unsigned int    version                    : 12; /* [11..0] 版本号。 */
        unsigned int    reserved                   : 20; /* [31..12] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NFC_VERSION_T;    /* nandc版本寄存器。 */

typedef union
{
    struct
    {
        unsigned int    last_flag                  : 1; /* [0..0] 由于内部buffer一次操作只有8K，对于page size为16K的器件，通过此寄存器来表示是否传输到最后一个8KB数据。0:当前读写不是最后一个8K数据段。1:当前读写是最后一个8K数据段。 */
        unsigned int    reserved                   : 31; /* [31..1] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NFC_SEGMENT_ID_T;    /* DMA读写nandflash的数据段ID寄存器。 */

typedef union
{
    struct
    {
        unsigned int    empty_dbg                  : 24; /* [23..0] 内部FIFO的empty信号状态。仅供调试用。 */
        unsigned int    reserved                   : 8; /* [31..24] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NFC_FIFO_EMPTY_T;    /* 内部fifo状态寄存器。 */

typedef union
{
    struct
    {
        unsigned int    block_size                 : 2; /* [1..0] Boot时，NAND Flash器件的总线宽度。00：64 page；01：128page；10：256 page；11：512 page。复位后的值由管脚NFC_BLOCK_SIZE决定。 */
        unsigned int    addr_num                   : 1; /* [2..2] Boot时，NANDC发给NAND Flash器件的地址数目。0：4个地址周期；1：5个地址周期。复位后的值由管脚NFC_ADDR_NUM决定。 */
        unsigned int    rsv                        : 29; /* [31..3] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NFC_BOOT_SET_T;    /* boot参数设定寄存器。 */

typedef union
{
    struct
    {
        unsigned int    clk_gate_en                : 1; /* [0..0] 时钟门控选择。0：时钟全部使能。1：根据ecc_type值，关闭不使用的模块时钟。 */
        unsigned int    reserved                   : 31; /* [31..1] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NF_LP_CTRL_T;    /* nandc 的低功耗控制寄存器。 */

typedef union
{
    struct
    {
        unsigned int    err_num0_buf0              : 32; /* [31..0] 对于2KB，4KB，8KB及16KB pagesize第一次buffer操作，前4KB数据错误统计寄存器。bit[31:24]：第四KB数据纠错，错误数据统计寄存器。bit[23:16]：第三KB数据纠错，错误数据统计寄存器。bit[15:8]：第二KB数据纠错，错误数据统计寄存器。bit[7:0]：第一KB数据纠错，错误数据统计寄存器。 */
    } bits;
    unsigned int    u32;
}HI_NFC_ERR_NUM0_BUF0_T;    /* nandflash 第一次buffer纠错统计寄存器0 */

typedef union
{
    struct
    {
        unsigned int    err_num1_buf0              : 32; /* [31..0] 对于8KB及16KB pagesize第一次buffer操作，后4KB数据错误统计寄存器。bit[31:24]：第八KB数据纠错，错误数据统计寄存器。bit[23:16]：第七KB数据纠错，错误数据统计寄存器。bit[15:8]：第六KB数据纠错，错误数据统计寄存器。bit[7:0]：第五KB数据纠错，错误数据统计寄存器。 */
    } bits;
    unsigned int    u32;
}HI_NFC_ERR_NUM1_BUF0_T;    /* nandflash 第一次buffer纠错统计寄存器1 */

typedef union
{
    struct
    {
        unsigned int    err_num0_buf1              : 32; /* [31..0] 对于16KB pagesize，第二次buffer操作，错误数统计寄存器0。bit[31:24]：第四KB数据纠错，错误数据统计寄存器。bit[23:16]：第三KB数据纠错，错误数据统计寄存器。bit[15:8]：第二KB数据纠错，错误数据统计寄存器。bit[7:0]：第一KB数据纠错，错误数据统计寄存器。 */
    } bits;
    unsigned int    u32;
}HI_NFC_ERR_NUM0_BUF1_T;    /* nandflash 第二次buffer纠错统计寄存器0 */

typedef union
{
    struct
    {
        unsigned int    err_num1_buf1              : 32; /* [31..0] 对于16KB pagesize，第二次buffer操作，错误数统计寄存器1。bit[31:24]：第八KB数据纠错，错误数据统计寄存器。bit[23:16]：第七KB数据纠错，错误数据统计寄存器。bit[15:8]：第六KB数据纠错，错误数据统计寄存器。bit[7:0]：第五KB数据纠错，错误数据统计寄存器。 */
    } bits;
    unsigned int    u32;
}HI_NFC_ERR_NUM1_BUF1_T;    /* nandflash 第二次buffer纠错统计寄存器1 */

typedef union
{
    struct
    {
        unsigned int    status                     : 1; /* [0..0] ready_busy模式寄存器。0：传统的ready信号；1：micron的enhanced clear nand信号。 */
        unsigned int    reserved                   : 31; /* [31..1] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NF_RB_MODE_T;    /* nandflash 的ready_busy模式寄存器。 */

typedef union
{
    struct
    {
        unsigned int    base_addr_d1               : 32; /* [31..0] 读写DDR数据区的基地址一。 */
    } bits;
    unsigned int    u32;
}HI_NFC_BADDR_D1_T;    /* 传送数据区的基地址寄存器1。 */

typedef union
{
    struct
    {
        unsigned int    base_addr_d2               : 32; /* [31..0] 读写DDR数据区的基地址二。 */
    } bits;
    unsigned int    u32;
}HI_NFC_BADDR_D2_T;    /* 传送数据区的基地址寄存器2。 */

typedef union
{
    struct
    {
        unsigned int    base_addr_d3               : 32; /* [31..0] 读写DDR数据区的基地址三。 */
    } bits;
    unsigned int    u32;
}HI_NFC_BADDR_D3_T;    /* 传送数据区的基地址寄存器3。 */

typedef union
{
    struct
    {
        unsigned int    randomizer_pad             : 1; /* [0..0] 硬件启动时randomizer使能情况。0：不使能；1：使能。 */
        unsigned int    page_size_pad              : 3; /* [3..1] NAND Flash的页大小。000：保留；001：2KByte；010：4KByte；011：8KByte；100：16KByte；101~111：保留。复位值由管脚NFC_PAGE_SIZE决定。 */
        unsigned int    ecc_type_pad               : 3; /* [6..4] ECC模式选择。000：无ECC。001：1bit 模式；010：4bit模式；011：16bit模式；100：24bits 模式 for 1KB；101：40bits模式；110: 64bits模式；111：保留。复位值由管脚NFC_ECC_TYPE决定。 */
        unsigned int    block_size_pad             : 2; /* [8..7] Boot时，NAND Flash器件的block块大小。00：64 page；01：128page；10：256 page；11：512 page。复位后的值由管脚NFC_BLOCK_SIZE决定。 */
        unsigned int    addr_num_pad               : 1; /* [9..9] 地址数。0：4个地址；1：5个地址。 */
        unsigned int    bus_width_pad              : 1; /* [10..10] NAND Flash的数据线宽度。0：8bit；1：16bit。复位值由管脚NFC_BUS_WIDE决定。 */
        unsigned int    sync_nand_pad              : 1; /* [11..11] 是否同步启动。0：异步启动；1：同步启动； */
        unsigned int    reserved                   : 20; /* [31..12] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NFC_BOOT_CFG_T;    /* nandflash 的boot配置寄存器 */

typedef union
{
    struct
    {
        unsigned int    oob_len_sel                : 1; /* [0..0] 对于8bit ECC，选择OOB区长度。0：对于2KB pagesize，OOB长度为8byte，对于4KB pagesize情况，OOB区长度为16byte。1：OOB区长度为32byte */
        unsigned int    reserved                   : 31; /* [31..1] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NFC_OOB_SEL_T;    /* 16bit ECC，OOB区长度选择寄存器 */

typedef union
{
    struct
    {
        unsigned int    mem_ctrl                   : 5; /* [4..0] 例化mem控制EMA和EMAW管脚值。[4:1]：控制EMA管脚值。[0]]：控制EMAW管脚值。 */
        unsigned int    reserved                   : 27; /* [31..5] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NFC_MEM_CTRL_T;    /* 例化mem管理 */

typedef union
{
    struct
    {
        unsigned int    rw_psth                    : 4; /* [3..0] toggle器件读写操作dqs无效到nf_ce_n无效时间间隔。0x0～0xF：1～16个器件时钟周期。 */
        unsigned int    post_wdqs                  : 4; /* [7..4] 读数据nf_dqs后导后导时间。0x0～0xF：1～16个器件时钟周期。 */
        unsigned int    pre_wdqs                   : 4; /* [11..8] 写操作nf_dqs前导时间。0x0～0xF：1～16个器件时钟周期。要求必须大于40ns。 */
        unsigned int    post_rdqs                  : 4; /* [15..12] toggle读数据nf_re_n后导后导时间。onfi读数据后dqs拉低至到三态时间。0x0～0xF：1～16个器件时钟周期。 */
        unsigned int    pre_rdqs                   : 4; /* [19..16] toggle读操作nf_re_n前导时间。0x0～0xF：1～16个器件时钟周期。要求必须大于40ns。 */
        unsigned int    t_dqz                      : 4; /* [23..20] onfi2器件，dqs无效到再次传输的时间间隔。0x0～0xF：1～16个器件时钟周期。 */
        unsigned int    t_cad                      : 4; /* [27..24] onfi2器件，nf_ale和nf_cle拉高前延迟时间。0x0～0xF：1～16个器件时钟周期。 */
        unsigned int    reserved                   : 4; /* [31..28] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NFC_SYNC_TIMING_T;    /* 同步NAND读写时序参数 */

typedef union
{
    struct
    {
        unsigned int    dll_bypass                 : 1; /* [0..0] DLL的bypass状态，判断是否进行相移。0：进行移相处理；1：bypass。 */
        unsigned int    dll_stop                   : 1; /* [1..1] dll是否停止计算参考时钟周期。1：使能；0：禁止。 */
        unsigned int    dll_slave_en               : 1; /* [2..2] slave是否跟踪master变化使能。0：禁止；1：使能。 */
        unsigned int    dll_mode                   : 1; /* [3..3] DLL工作模式配置。0：正常工作模式；1：Direct配置模式，Slave DLL的延时级数由寄存器配置得到。 */
        unsigned int    dll_tune                   : 4; /* [7..4] 正常工作前扫描配置。配置的tune[3]为1时减去 tune[2:0]；为0时加上 tune[2:0] */
        unsigned int    dll_ssel                   : 8; /* [15..8] DLL的延时级数。当dllmode=1时有效。 */
        unsigned int    reserved                   : 16; /* [31..16] 保留。 */
    } bits;
    unsigned int    u32;
}HI_NFC_DLL_CONTROL_T;    /* DLL模块配置信息 */

typedef union
{
    struct
    {
        unsigned int    dll_ready                  : 1; /* [0..0] Slave DLL移相完成。0：没完成；1：完成。 */
        unsigned int    dll_overflow               : 1; /* [1..1] DLL溢出指示。0：不溢出；1：溢出。 */
        unsigned int    dll_lockrd                 : 1; /* [2..2] DLL锁定指示。0：未锁定；1：锁定。 */
        unsigned int    reserved_1                 : 1; /* [3..3] 保留 */
        unsigned int    mdly_tap                   : 8; /* [11..4] Master DLL的延时级数状态。 */
        unsigned int    reserved_0                 : 20; /* [31..12] 保留 */
    } bits;
    unsigned int    u32;
}HI_NFC_DLL_STATUS_T;    /* DLL模块状态信息 */


/********************************************************************************/
/*    nandc 函数（项目名_模块名_寄存器名_成员名_set)        */
/********************************************************************************/
HI_SET_GET(hi_nfc_con_op_mode,op_mode,HI_NFC_CON_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CON_OFFSET)
HI_SET_GET(hi_nfc_con_pagesize,pagesize,HI_NFC_CON_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CON_OFFSET)
HI_SET_GET(hi_nfc_con_bus_width,bus_width,HI_NFC_CON_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CON_OFFSET)
HI_SET_GET(hi_nfc_con_reserved_2,reserved_2,HI_NFC_CON_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CON_OFFSET)
HI_SET_GET(hi_nfc_con_cs_ctrl,cs_ctrl,HI_NFC_CON_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CON_OFFSET)
HI_SET_GET(hi_nfc_con_rb_sel,rb_sel,HI_NFC_CON_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CON_OFFSET)
HI_SET_GET(hi_nfc_con_ecc_type,ecc_type,HI_NFC_CON_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CON_OFFSET)
HI_SET_GET(hi_nfc_con_reserved_1,reserved_1,HI_NFC_CON_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CON_OFFSET)
HI_SET_GET(hi_nfc_con_randomizer_en,randomizer_en,HI_NFC_CON_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CON_OFFSET)
HI_SET_GET(hi_nfc_con_nf_mode,nf_mode,HI_NFC_CON_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CON_OFFSET)
HI_SET_GET(hi_nfc_con_reserved_0,reserved_0,HI_NFC_CON_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CON_OFFSET)
HI_SET_GET(hi_nfc_pwidth_w_lcnt,w_lcnt,HI_NFC_PWIDTH_T,HI_NANDC_REGBASE_ADDR, HI_NFC_PWIDTH_OFFSET)
HI_SET_GET(hi_nfc_pwidth_r_lcnt,r_lcnt,HI_NFC_PWIDTH_T,HI_NANDC_REGBASE_ADDR, HI_NFC_PWIDTH_OFFSET)
HI_SET_GET(hi_nfc_pwidth_rw_hcnt,rw_hcnt,HI_NFC_PWIDTH_T,HI_NANDC_REGBASE_ADDR, HI_NFC_PWIDTH_OFFSET)
HI_SET_GET(hi_nfc_pwidth_reserved,reserved,HI_NFC_PWIDTH_T,HI_NANDC_REGBASE_ADDR, HI_NFC_PWIDTH_OFFSET)
HI_SET_GET(hi_nfc_opidle_wait_ready_wait,wait_ready_wait,HI_NFC_OPIDLE_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OPIDLE_OFFSET)
HI_SET_GET(hi_nfc_opidle_cmd2_wait,cmd2_wait,HI_NFC_OPIDLE_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OPIDLE_OFFSET)
HI_SET_GET(hi_nfc_opidle_rsv,rsv,HI_NFC_OPIDLE_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OPIDLE_OFFSET)
HI_SET_GET(hi_nfc_opidle_addr_wait,addr_wait,HI_NFC_OPIDLE_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OPIDLE_OFFSET)
HI_SET_GET(hi_nfc_opidle_cmd1_wait,cmd1_wait,HI_NFC_OPIDLE_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OPIDLE_OFFSET)
HI_SET_GET(hi_nfc_opidle_frb_wait,frb_wait,HI_NFC_OPIDLE_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OPIDLE_OFFSET)
HI_SET_GET(hi_nfc_opidle_reserved,reserved,HI_NFC_OPIDLE_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OPIDLE_OFFSET)
HI_SET_GET(hi_nfc_cmd_cmd1,cmd1,HI_NFC_CMD_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CMD_OFFSET)
HI_SET_GET(hi_nfc_cmd_cmd2,cmd2,HI_NFC_CMD_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CMD_OFFSET)
HI_SET_GET(hi_nfc_cmd_read_status_cmd,read_status_cmd,HI_NFC_CMD_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CMD_OFFSET)
HI_SET_GET(hi_nfc_cmd_reserved,reserved,HI_NFC_CMD_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CMD_OFFSET)
HI_SET_GET(hi_nfc_addrl_addr_l,addr_l,HI_NFC_ADDRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ADDRL_OFFSET)
HI_SET_GET(hi_nfc_addrh_addr_h,addr_h,HI_NFC_ADDRH_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ADDRH_OFFSET)
HI_SET_GET(hi_nfc_addrh_reserved,reserved,HI_NFC_ADDRH_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ADDRH_OFFSET)
HI_SET_GET(hi_nfc_data_num_nfc_data_num,nfc_data_num,HI_NFC_DATA_NUM_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DATA_NUM_OFFSET)
HI_SET_GET(hi_nfc_data_num_reserved,reserved,HI_NFC_DATA_NUM_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DATA_NUM_OFFSET)
HI_SET_GET(hi_nfc_op_read_status_en,read_status_en,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_op_read_data_en,read_data_en,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_op_wait_ready_en,wait_ready_en,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_op_cmd2_en,cmd2_en,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_op_write_data_en,write_data_en,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_op_addr_en,addr_en,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_op_cmd1_en,cmd1_en,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_op_nf_cs,nf_cs,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_op_address_cycles,address_cycles,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_op_read_id_en,read_id_en,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_op_rw_reg_en,rw_reg_en,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_op_reserved,reserved,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_status_nfc_ready,nfc_ready,HI_NFC_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_STATUS_OFFSET)
HI_SET_GET(hi_nfc_status_nf0_ready,nf0_ready,HI_NFC_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_STATUS_OFFSET)
HI_SET_GET(hi_nfc_status_nf1_ready,nf1_ready,HI_NFC_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_STATUS_OFFSET)
HI_SET_GET(hi_nfc_status_nf2_ready,nf2_ready,HI_NFC_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_STATUS_OFFSET)
HI_SET_GET(hi_nfc_status_nf3_ready,nf3_ready,HI_NFC_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_STATUS_OFFSET)
HI_SET_GET(hi_nfc_status_reserved_1,reserved_1,HI_NFC_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_STATUS_OFFSET)
HI_SET_GET(hi_nfc_status_nf_status,nf_status,HI_NFC_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_STATUS_OFFSET)
HI_SET_GET(hi_nfc_status_nfc_ecc_type,nfc_ecc_type,HI_NFC_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_STATUS_OFFSET)
HI_SET_GET(hi_nfc_status_nfc_randomizer_en,nfc_randomizer_en,HI_NFC_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_STATUS_OFFSET)
HI_SET_GET(hi_nfc_status_reserved_0,reserved_0,HI_NFC_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_STATUS_OFFSET)
HI_SET_GET(hi_nfc_inten_op_done_en,op_done_en,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_inten_cs0_done_en,cs0_done_en,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_inten_cs1_done_en,cs1_done_en,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_inten_cs2_done_en,cs2_done_en,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_inten_cs3_done_en,cs3_done_en,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_inten_err_valid_en,err_valid_en,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_inten_err_invalid_en,err_invalid_en,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_inten_ahb_op_en,ahb_op_en,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_inten_wr_lock_en,wr_lock_en,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_inten_dma_done_en,dma_done_en,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_inten_dma_err_en,dma_err_en,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_inten_reserved,reserved,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_ints_op_done,op_done,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_ints_cs0_done,cs0_done,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_ints_cs1_done,cs1_done,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_ints_cs2_done,cs2_done,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_ints_cs3_done,cs3_done,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_ints_err_valid,err_valid,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_ints_err_invalid,err_invalid,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_ints_ahb_op_err,ahb_op_err,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_ints_wr_lock_err,wr_lock_err,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_ints_dma_done,dma_done,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_ints_dma_err,dma_err,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_ints_reserved,reserved,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_intclr_op_done_clr,op_done_clr,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_intclr_cs0_done_clr,cs0_done_clr,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_intclr_cs1_done_clr,cs1_done_clr,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_intclr_cs2_done_clr,cs2_done_clr,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_intclr_cs3_done_clr,cs3_done_clr,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_intclr_err_valid_clr,err_valid_clr,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_intclr_err_invalid_clr,err_invalid_clr,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_intclr_ahb_op_err_clr,ahb_op_err_clr,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_intclr_wr_lock_err_clr,wr_lock_err_clr,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_intclr_dma_done_clr,dma_done_clr,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_intclr_dma_err_clr,dma_err_clr,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_intclr_reserved,reserved,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_lock_lock_down,lock_down,HI_NFC_LOCK_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_OFFSET)
HI_SET_GET(hi_nfc_lock_global_lock_en,global_lock_en,HI_NFC_LOCK_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_OFFSET)
HI_SET_GET(hi_nfc_lock_lock_en,lock_en,HI_NFC_LOCK_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_OFFSET)
HI_SET_GET(hi_nfc_lock_lock_excmd_en,lock_excmd_en,HI_NFC_LOCK_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_OFFSET)
HI_SET_GET(hi_nfc_lock_reserved,reserved,HI_NFC_LOCK_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_OFFSET)
HI_SET_GET(hi_nfc_lock_sa0_flash_lock_addr0,flash_lock_addr0,HI_NFC_LOCK_SA0_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA0_OFFSET)
HI_SET_GET(hi_nfc_lock_sa0_flash_lock_cs,flash_lock_cs,HI_NFC_LOCK_SA0_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA0_OFFSET)
HI_SET_GET(hi_nfc_lock_sa0_reserved,reserved,HI_NFC_LOCK_SA0_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA0_OFFSET)
HI_SET_GET(hi_nfc_lock_sa1_flash_lock_addr1,flash_lock_addr1,HI_NFC_LOCK_SA1_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA1_OFFSET)
HI_SET_GET(hi_nfc_lock_sa1_flash_lock_cs,flash_lock_cs,HI_NFC_LOCK_SA1_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA1_OFFSET)
HI_SET_GET(hi_nfc_lock_sa1_reserved,reserved,HI_NFC_LOCK_SA1_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA1_OFFSET)
HI_SET_GET(hi_nfc_lock_sa2_flash_lock_addr2,flash_lock_addr2,HI_NFC_LOCK_SA2_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA2_OFFSET)
HI_SET_GET(hi_nfc_lock_sa2_flash_lock_cs,flash_lock_cs,HI_NFC_LOCK_SA2_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA2_OFFSET)
HI_SET_GET(hi_nfc_lock_sa2_reserved,reserved,HI_NFC_LOCK_SA2_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA2_OFFSET)
HI_SET_GET(hi_nfc_lock_sa3_flash_lock_addr3,flash_lock_addr3,HI_NFC_LOCK_SA3_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA3_OFFSET)
HI_SET_GET(hi_nfc_lock_sa3_flash_lock_cs,flash_lock_cs,HI_NFC_LOCK_SA3_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA3_OFFSET)
HI_SET_GET(hi_nfc_lock_sa3_reserved,reserved,HI_NFC_LOCK_SA3_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA3_OFFSET)
HI_SET_GET(hi_nfc_lock_ea0_flash_lock_eaddr0,flash_lock_eaddr0,HI_NFC_LOCK_EA0_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA0_OFFSET)
HI_SET_GET(hi_nfc_lock_ea0_flash_lock_cs,flash_lock_cs,HI_NFC_LOCK_EA0_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA0_OFFSET)
HI_SET_GET(hi_nfc_lock_ea0_reserved,reserved,HI_NFC_LOCK_EA0_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA0_OFFSET)
HI_SET_GET(hi_nfc_lock_ea1_flash_lock_eaddr1,flash_lock_eaddr1,HI_NFC_LOCK_EA1_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA1_OFFSET)
HI_SET_GET(hi_nfc_lock_ea1_flash_lock_cs,flash_lock_cs,HI_NFC_LOCK_EA1_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA1_OFFSET)
HI_SET_GET(hi_nfc_lock_ea1_reserved,reserved,HI_NFC_LOCK_EA1_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA1_OFFSET)
HI_SET_GET(hi_nfc_lock_ea2_flash_lock_eaddr2,flash_lock_eaddr2,HI_NFC_LOCK_EA2_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA2_OFFSET)
HI_SET_GET(hi_nfc_lock_ea2_flash_lock_cs,flash_lock_cs,HI_NFC_LOCK_EA2_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA2_OFFSET)
HI_SET_GET(hi_nfc_lock_ea2_reserved,reserved,HI_NFC_LOCK_EA2_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA2_OFFSET)
HI_SET_GET(hi_nfc_lock_ea3_flash_lock_eaddr3,flash_lock_eaddr3,HI_NFC_LOCK_EA3_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA3_OFFSET)
HI_SET_GET(hi_nfc_lock_ea3_flash_lock_cs,flash_lock_cs,HI_NFC_LOCK_EA3_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA3_OFFSET)
HI_SET_GET(hi_nfc_lock_ea3_reserved,reserved,HI_NFC_LOCK_EA3_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA3_OFFSET)
HI_SET_GET(hi_nfc_expcmd_ex_pcmd0,ex_pcmd0,HI_NFC_EXPCMD_T,HI_NANDC_REGBASE_ADDR, HI_NFC_EXPCMD_OFFSET)
HI_SET_GET(hi_nfc_expcmd_ex_pcmd1,ex_pcmd1,HI_NFC_EXPCMD_T,HI_NANDC_REGBASE_ADDR, HI_NFC_EXPCMD_OFFSET)
HI_SET_GET(hi_nfc_expcmd_ex_pcmd2,ex_pcmd2,HI_NFC_EXPCMD_T,HI_NANDC_REGBASE_ADDR, HI_NFC_EXPCMD_OFFSET)
HI_SET_GET(hi_nfc_expcmd_ex_pcmd3,ex_pcmd3,HI_NFC_EXPCMD_T,HI_NANDC_REGBASE_ADDR, HI_NFC_EXPCMD_OFFSET)
HI_SET_GET(hi_nfc_exbcmd_ex_bcmd0,ex_bcmd0,HI_NFC_EXBCMD_T,HI_NANDC_REGBASE_ADDR, HI_NFC_EXBCMD_OFFSET)
HI_SET_GET(hi_nfc_exbcmd_ex_bcmd1,ex_bcmd1,HI_NFC_EXBCMD_T,HI_NANDC_REGBASE_ADDR, HI_NFC_EXBCMD_OFFSET)
HI_SET_GET(hi_nfc_exbcmd_reserved,reserved,HI_NFC_EXBCMD_T,HI_NANDC_REGBASE_ADDR, HI_NFC_EXBCMD_OFFSET)
HI_SET_GET(hi_nfc_ecc_test_enc_only,enc_only,HI_NFC_ECC_TEST_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ECC_TEST_OFFSET)
HI_SET_GET(hi_nfc_ecc_test_dec_only,dec_only,HI_NFC_ECC_TEST_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ECC_TEST_OFFSET)
HI_SET_GET(hi_nfc_ecc_test_ecc_mask,ecc_mask,HI_NFC_ECC_TEST_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ECC_TEST_OFFSET)
HI_SET_GET(hi_nfc_ecc_test_reserved_1,reserved_1,HI_NFC_ECC_TEST_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ECC_TEST_OFFSET)
HI_SET_GET(hi_nfc_ecc_test_bb_err,bb_err,HI_NFC_ECC_TEST_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ECC_TEST_OFFSET)
HI_SET_GET(hi_nfc_ecc_test_reserved_0,reserved_0,HI_NFC_ECC_TEST_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ECC_TEST_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_dma_start,dma_start,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_dma_wr_en,dma_wr_en,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_reserved_1,reserved_1,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_burst4_en,burst4_en,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_burst8_en,burst8_en,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_burst16_en,burst16_en,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_dma_addr_num,dma_addr_num,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_dma_nf_cs,dma_nf_cs,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_rsv,rsv,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_wr_cmd_disable,wr_cmd_disable,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_dma_rd_oob,dma_rd_oob,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_reserved_0,reserved_0,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_baddr_d_base_addr_d,base_addr_d,HI_NFC_BADDR_D_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BADDR_D_OFFSET)
HI_SET_GET(hi_nfc_baddr_oob_base_addr_oob,base_addr_oob,HI_NFC_BADDR_OOB_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BADDR_OOB_OFFSET)
HI_SET_GET(hi_nfc_dma_len_reserved_1,reserved_1,HI_NFC_DMA_LEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_LEN_OFFSET)
HI_SET_GET(hi_nfc_dma_len_len_oob,len_oob,HI_NFC_DMA_LEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_LEN_OFFSET)
HI_SET_GET(hi_nfc_dma_len_reserved_0,reserved_0,HI_NFC_DMA_LEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_LEN_OFFSET)
HI_SET_GET(hi_nfc_op_para_data_rw_en,data_rw_en,HI_NFC_OP_PARA_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_PARA_OFFSET)
HI_SET_GET(hi_nfc_op_para_oob_rw_en,oob_rw_en,HI_NFC_OP_PARA_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_PARA_OFFSET)
HI_SET_GET(hi_nfc_op_para_data_edc_en,data_edc_en,HI_NFC_OP_PARA_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_PARA_OFFSET)
HI_SET_GET(hi_nfc_op_para_oob_edc_en,oob_edc_en,HI_NFC_OP_PARA_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_PARA_OFFSET)
HI_SET_GET(hi_nfc_op_para_reserved,reserved,HI_NFC_OP_PARA_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_PARA_OFFSET)
HI_SET_GET(hi_nfc_version_version,version,HI_NFC_VERSION_T,HI_NANDC_REGBASE_ADDR, HI_NFC_VERSION_OFFSET)
HI_SET_GET(hi_nfc_version_reserved,reserved,HI_NFC_VERSION_T,HI_NANDC_REGBASE_ADDR, HI_NFC_VERSION_OFFSET)
HI_SET_GET(hi_nfc_segment_id_last_flag,last_flag,HI_NFC_SEGMENT_ID_T,HI_NANDC_REGBASE_ADDR, HI_NFC_SEGMENT_ID_OFFSET)
HI_SET_GET(hi_nfc_segment_id_reserved,reserved,HI_NFC_SEGMENT_ID_T,HI_NANDC_REGBASE_ADDR, HI_NFC_SEGMENT_ID_OFFSET)
HI_SET_GET(hi_nfc_fifo_empty_empty_dbg,empty_dbg,HI_NFC_FIFO_EMPTY_T,HI_NANDC_REGBASE_ADDR, HI_NFC_FIFO_EMPTY_OFFSET)
HI_SET_GET(hi_nfc_fifo_empty_reserved,reserved,HI_NFC_FIFO_EMPTY_T,HI_NANDC_REGBASE_ADDR, HI_NFC_FIFO_EMPTY_OFFSET)
HI_SET_GET(hi_nfc_boot_set_block_size,block_size,HI_NFC_BOOT_SET_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BOOT_SET_OFFSET)
HI_SET_GET(hi_nfc_boot_set_addr_num,addr_num,HI_NFC_BOOT_SET_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BOOT_SET_OFFSET)
HI_SET_GET(hi_nfc_boot_set_rsv,rsv,HI_NFC_BOOT_SET_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BOOT_SET_OFFSET)
HI_SET_GET(hi_nf_lp_ctrl_clk_gate_en,clk_gate_en,HI_NF_LP_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NF_LP_CTRL_OFFSET)
HI_SET_GET(hi_nf_lp_ctrl_reserved,reserved,HI_NF_LP_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NF_LP_CTRL_OFFSET)
HI_SET_GET(hi_nfc_err_num0_buf0_err_num0_buf0,err_num0_buf0,HI_NFC_ERR_NUM0_BUF0_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ERR_NUM0_BUF0_OFFSET)
HI_SET_GET(hi_nfc_err_num1_buf0_err_num1_buf0,err_num1_buf0,HI_NFC_ERR_NUM1_BUF0_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ERR_NUM1_BUF0_OFFSET)
HI_SET_GET(hi_nfc_err_num0_buf1_err_num0_buf1,err_num0_buf1,HI_NFC_ERR_NUM0_BUF1_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ERR_NUM0_BUF1_OFFSET)
HI_SET_GET(hi_nfc_err_num1_buf1_err_num1_buf1,err_num1_buf1,HI_NFC_ERR_NUM1_BUF1_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ERR_NUM1_BUF1_OFFSET)
HI_SET_GET(hi_nf_rb_mode_status,status,HI_NF_RB_MODE_T,HI_NANDC_REGBASE_ADDR, HI_NF_RB_MODE_OFFSET)
HI_SET_GET(hi_nf_rb_mode_reserved,reserved,HI_NF_RB_MODE_T,HI_NANDC_REGBASE_ADDR, HI_NF_RB_MODE_OFFSET)
HI_SET_GET(hi_nfc_baddr_d1_base_addr_d1,base_addr_d1,HI_NFC_BADDR_D1_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BADDR_D1_OFFSET)
HI_SET_GET(hi_nfc_baddr_d2_base_addr_d2,base_addr_d2,HI_NFC_BADDR_D2_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BADDR_D2_OFFSET)
HI_SET_GET(hi_nfc_baddr_d3_base_addr_d3,base_addr_d3,HI_NFC_BADDR_D3_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BADDR_D3_OFFSET)
HI_SET_GET(hi_nfc_boot_cfg_randomizer_pad,randomizer_pad,HI_NFC_BOOT_CFG_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BOOT_CFG_OFFSET)
HI_SET_GET(hi_nfc_boot_cfg_page_size_pad,page_size_pad,HI_NFC_BOOT_CFG_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BOOT_CFG_OFFSET)
HI_SET_GET(hi_nfc_boot_cfg_ecc_type_pad,ecc_type_pad,HI_NFC_BOOT_CFG_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BOOT_CFG_OFFSET)
HI_SET_GET(hi_nfc_boot_cfg_block_size_pad,block_size_pad,HI_NFC_BOOT_CFG_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BOOT_CFG_OFFSET)
HI_SET_GET(hi_nfc_boot_cfg_addr_num_pad,addr_num_pad,HI_NFC_BOOT_CFG_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BOOT_CFG_OFFSET)
HI_SET_GET(hi_nfc_boot_cfg_bus_width_pad,bus_width_pad,HI_NFC_BOOT_CFG_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BOOT_CFG_OFFSET)
HI_SET_GET(hi_nfc_boot_cfg_sync_nand_pad,sync_nand_pad,HI_NFC_BOOT_CFG_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BOOT_CFG_OFFSET)
HI_SET_GET(hi_nfc_boot_cfg_reserved,reserved,HI_NFC_BOOT_CFG_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BOOT_CFG_OFFSET)
HI_SET_GET(hi_nfc_oob_sel_oob_len_sel,oob_len_sel,HI_NFC_OOB_SEL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OOB_SEL_OFFSET)
HI_SET_GET(hi_nfc_oob_sel_reserved,reserved,HI_NFC_OOB_SEL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OOB_SEL_OFFSET)
HI_SET_GET(hi_nfc_mem_ctrl_mem_ctrl,mem_ctrl,HI_NFC_MEM_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_MEM_CTRL_OFFSET)
HI_SET_GET(hi_nfc_mem_ctrl_reserved,reserved,HI_NFC_MEM_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_MEM_CTRL_OFFSET)
HI_SET_GET(hi_nfc_sync_timing_rw_psth,rw_psth,HI_NFC_SYNC_TIMING_T,HI_NANDC_REGBASE_ADDR, HI_NFC_SYNC_TIMING_OFFSET)
HI_SET_GET(hi_nfc_sync_timing_post_wdqs,post_wdqs,HI_NFC_SYNC_TIMING_T,HI_NANDC_REGBASE_ADDR, HI_NFC_SYNC_TIMING_OFFSET)
HI_SET_GET(hi_nfc_sync_timing_pre_wdqs,pre_wdqs,HI_NFC_SYNC_TIMING_T,HI_NANDC_REGBASE_ADDR, HI_NFC_SYNC_TIMING_OFFSET)
HI_SET_GET(hi_nfc_sync_timing_post_rdqs,post_rdqs,HI_NFC_SYNC_TIMING_T,HI_NANDC_REGBASE_ADDR, HI_NFC_SYNC_TIMING_OFFSET)
HI_SET_GET(hi_nfc_sync_timing_pre_rdqs,pre_rdqs,HI_NFC_SYNC_TIMING_T,HI_NANDC_REGBASE_ADDR, HI_NFC_SYNC_TIMING_OFFSET)
HI_SET_GET(hi_nfc_sync_timing_t_dqz,t_dqz,HI_NFC_SYNC_TIMING_T,HI_NANDC_REGBASE_ADDR, HI_NFC_SYNC_TIMING_OFFSET)
HI_SET_GET(hi_nfc_sync_timing_t_cad,t_cad,HI_NFC_SYNC_TIMING_T,HI_NANDC_REGBASE_ADDR, HI_NFC_SYNC_TIMING_OFFSET)
HI_SET_GET(hi_nfc_sync_timing_reserved,reserved,HI_NFC_SYNC_TIMING_T,HI_NANDC_REGBASE_ADDR, HI_NFC_SYNC_TIMING_OFFSET)
HI_SET_GET(hi_nfc_dll_control_dll_bypass,dll_bypass,HI_NFC_DLL_CONTROL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_CONTROL_OFFSET)
HI_SET_GET(hi_nfc_dll_control_dll_stop,dll_stop,HI_NFC_DLL_CONTROL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_CONTROL_OFFSET)
HI_SET_GET(hi_nfc_dll_control_dll_slave_en,dll_slave_en,HI_NFC_DLL_CONTROL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_CONTROL_OFFSET)
HI_SET_GET(hi_nfc_dll_control_dll_mode,dll_mode,HI_NFC_DLL_CONTROL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_CONTROL_OFFSET)
HI_SET_GET(hi_nfc_dll_control_dll_tune,dll_tune,HI_NFC_DLL_CONTROL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_CONTROL_OFFSET)
HI_SET_GET(hi_nfc_dll_control_dll_ssel,dll_ssel,HI_NFC_DLL_CONTROL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_CONTROL_OFFSET)
HI_SET_GET(hi_nfc_dll_control_reserved,reserved,HI_NFC_DLL_CONTROL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_CONTROL_OFFSET)
HI_SET_GET(hi_nfc_dll_status_dll_ready,dll_ready,HI_NFC_DLL_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_STATUS_OFFSET)
HI_SET_GET(hi_nfc_dll_status_dll_overflow,dll_overflow,HI_NFC_DLL_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_STATUS_OFFSET)
HI_SET_GET(hi_nfc_dll_status_dll_lockrd,dll_lockrd,HI_NFC_DLL_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_STATUS_OFFSET)
HI_SET_GET(hi_nfc_dll_status_reserved_1,reserved_1,HI_NFC_DLL_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_STATUS_OFFSET)
HI_SET_GET(hi_nfc_dll_status_mdly_tap,mdly_tap,HI_NFC_DLL_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_STATUS_OFFSET)
HI_SET_GET(hi_nfc_dll_status_reserved_0,reserved_0,HI_NFC_DLL_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_STATUS_OFFSET)

#endif // __HI_NANDC_H__

