/******************************************************************************/
/*  Copyright (C), 2007-2014, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name     : hi_psam.h */
/* Version       : 2.0 */
/* Author        : chenchaozhe 228796*/
/* Created       : 2014-08-11*/
/* Last Modified : */
/* Description   :  The C union definition file for the module hi*/
/* Function List : */
/* History       : */
/* 1 Date        : */
/* Author        : chenchaozhe 228796*/
/* Modification  : Create file */
/******************************************************************************/

#ifndef __HI_PSAM_H__
#define __HI_PSAM_H__

/*
 * Project: hi
 * Module : PSAM
 */

#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4)
#endif

/********************************************************************************/
/*    hi 寄存器偏移定义（项目名_模块名_寄存器名_OFFSET)        */
/********************************************************************************/
#define    HI_PSAM_SRST_OFFSET                               (0x0)
#define    HI_PSAM_CONFIG_OFFSET                             (0x4)
#define    HI_PSAM_VERSION_OFFSET                            (0x8)
#define    HI_PSAM_EN_OFFSET                                 (0xC)
#define    HI_PSAM_INT0_STAT_OFFSET                          (0x40)
#define    HI_PSAM_INT1_STAT_OFFSET                          (0x44)
#define    HI_PSAM_INT0_MSTAT_OFFSET                         (0x48)
#define    HI_PSAM_INT1_MSTAT_OFFSET                         (0x4C)
#define    HI_PSAM_INT0_MASK_OFFSET                          (0x50)
#define    HI_PSAM_INT1_MASK_OFFSET                          (0x54)
#define    HI_PSAM_CIPHER_CH_SOFTRESET_OFFSET                (0x80)
#define    HI_PSAM_CIPHER_CH_EN_OFFSET                       (0x84)
#define    HI_PSAM_CBDQ_CONFIG_OFFSET                        (0x88)
#define    HI_PSAM_CBDQ_BADDR_OFFSET                         (0x8C)
#define    HI_PSAM_CBDQ_SIZE_OFFSET                          (0x90)
#define    HI_PSAM_CBDQ_WPTR_OFFSET                          (0x94)
#define    HI_PSAM_CBDQ_STAT_OFFSET                          (0x98)
#define    HI_PSAM_CBDQ_WPTR_ADDR_OFFSET                     (0x9C)
#define    HI_PSAM_CRDQ_CTRL_OFFSET                          (0x100)
#define    HI_PSAM_CRDQ_STAT_OFFSET                          (0x104)
#define    HI_PSAM_CRDQ_PTR_OFFSET                           (0x108)
#define    HI_PSAM_CRDQ_RPTR_ADDR_OFFSET                     (0x10C)
#define    HI_PSAM_IBDQ_STAT_OFFSET                          (0x154)
#define    HI_PSAM_IBDQ_BADDR_OFFSET                         (0x158)
#define    HI_PSAM_IBDQ_SIZE_OFFSET                          (0x15C)
#define    HI_PSAM_IBDQ_WPTR_OFFSET                          (0x160)
#define    HI_PSAM_IBDQ_RPTR_OFFSET                          (0x164)
#define    HI_PSAM_IBDQ_WPTR_ADDR_OFFSET                     (0x168)
#define    HI_PSAM_IBDQ_RPTR_ADDR_OFFSET                     (0x16C)
#define    HI_PSAM_IBDQ_RPTR_TIMER_OFFSET                    (0x170)
#define    HI_PSAM_IBDQ_PKT_CNT_OFFSET                       (0x174)
#define    HI_PSAM_LBDQ_STAT_OFFSET                          (0x254)
#define    HI_PSAM_LBDQ_BADDR_OFFSET                         (0x258)
#define    HI_PSAM_LBDQ_SIZE_OFFSET                          (0x25C)
#define    HI_PSAM_LBDQ_WPTR_OFFSET                          (0x260)
#define    HI_PSAM_LBDQ_RPTR_OFFSET                          (0x264)
#define    HI_PSAM_LBDQ_DEPTH_OFFSET                         (0x268)
#define    HI_PSAM_ADQ_CTRL_OFFSET                           (0x284)
#define    HI_PSAM_ADQ0_BASE_OFFSET                          (0x290)
#define    HI_PSAM_ADQ0_STAT_OFFSET                          (0x294)
#define    HI_PSAM_ADQ0_WPTR_OFFSET                          (0x298)
#define    HI_PSAM_ADQ0_RPTR_OFFSET                          (0x29C)
#define    HI_PSAM_ADQ1_BASE_OFFSET                          (0x2A0)
#define    HI_PSAM_ADQ1_STAT_OFFSET                          (0x2A4)
#define    HI_PSAM_ADQ1_WPTR_OFFSET                          (0x2A8)
#define    HI_PSAM_ADQ1_RPTR_OFFSET                          (0x2AC)
#define    HI_PSAM_ADQ_PADDR_ERR_OFFSET                      (0x2B0)
#define    HI_PSAM_ADQ_FAMA_ATTR_OFFSET                      (0x2B4) /*ADQ FAMA属性寄存器*/
#define    HI_PSAM_ADQ_PADDR_STR0_OFFSET                     (0x300)
#define    HI_PSAM_ADQ_PADDR_END0_OFFSET                     (0x304)
#define    HI_PSAM_ADQ_PADDR_STR1_OFFSET                     (0x308)
#define    HI_PSAM_ADQ_PADDR_END1_OFFSET                     (0x30c)
#define    HI_PSAM_ADQ_PADDR_STR2_OFFSET                     (0x310)
#define    HI_PSAM_ADQ_PADDR_END2_OFFSET                     (0x314)
#define    HI_PSAM_ADQ_PADDR_STR3_OFFSET                     (0x318)
#define    HI_PSAM_ADQ_PADDR_END3_OFFSET                     (0x31c)
#define    HI_PSAM_ADQ_PADDR_CTRL_OFFSET                     (0x320)
#define    HI_PSAM_CBDQ_FAMA_ATTR_OFFSET                     (0x330) /*CBDQ FAMA属性寄存器*/
#define    HI_PSAM_IBDQ_FAMA_ATTR_OFFSET                     (0x334) /*IBDQ FAMA属性寄存器*/
#define    HI_PSAM_LBDQ_FAMA_ATTR_OFFSET                     (0x338) /*LBDQ FAMA属性寄存器*/
#define    HI_PSAM_CRDQ_BADDR_OFFSET                         (0x400)
#define    HI_PSAM_REG_END_OFFSET                         	 (HI_PSAM_LBDQ_FAMA_ATTR_OFFSET + 4)/* 结束地址，加了新的寄存器，这个值需要修改*/


#ifndef __ASSEMBLY__

/********************************************************************************/
/*    reg_design 寄存器定义（项目名_模块名_寄存器名_T)        */
/********************************************************************************/
typedef union
{
    struct
    {
        unsigned int    psam_srst                  : 1; /* [0..0] psam软复位配置寄存器。写1复位psam模块，若此时psam占有总线，不能立即执行复位，直到psam释放总线后才开始复位，复位结束自动清0。软件软复位过程中，先配置该寄存器为1，查询该寄存器的值，当回读值为0时即复位完成。 */
        unsigned int    psam_idle                  : 1; /* [1..1] psam通道空闲指示。 */
        unsigned int    reserved                   : 30; /* [31..2] 保留。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_SRST_T;

typedef union
{
    struct
    {
        unsigned int    psam_rd_pri                : 3; /* [2..0] dma arbiter读优先级设置。 */
        unsigned int    psam_wr_pri                : 3; /* [5..3] dma arbiter写优先级设置。 */
        unsigned int    cbdq_wptr_update_mode      : 1; /* [6..6] cbdq写指针更新模式。配置为1时，开启在回读回写达到阈值后，更新一次cbdq的写指针。 */
        unsigned int    cbdq_wptr_update_num       : 7; /* [13..7] cbdq写指针更新阈值，可配0~127对应1到128的阈值范围。例如，默认值为9，即当回读回写次数大于等于10次即触发一次cbdq的写指针更新。 */
        unsigned int    reserved                   : 2; /* [15..14] 保留。 */
        unsigned int    psam_cfg_rsvd              : 16; /* [31..16] CONFIG保留寄存器。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_CONFIG_T;

typedef union
{
    struct
    {
        unsigned int    psam_version               : 32; /* [31..0] 版本寄存器。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_VERSION_T;

typedef union
{
    struct
    {
        unsigned int    psam_en                    : 1; /* [0..0] psam通道使能。 */
        unsigned int    reserved                   : 31; /* [31..1] 保留。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_EN_T;

typedef union
{
    struct
    {
        unsigned int    adq0_epty_int0             : 1; /* [0..0] ADQ0空中断0。 */
        unsigned int    adq1_epty_int0             : 1; /* [1..1] ADQ1空中断0。 */
        unsigned int    lbdq_epty_int0             : 1; /* [2..2] LBDQ空中断0。 */
        unsigned int    reserved_2                 : 13; /* [15..3] 保留。 */
        unsigned int    rd_wbuf_overflow_int0      : 1; /* [16..16] RD缓存FIFO溢出中断0。 */
        unsigned int    adq0_upoverflow_int0       : 1; /* [17..17] ADQ0上溢出中断0。 */
        unsigned int    adq1_upoverflow_int0       : 1; /* [18..18] ADQ1上溢出中断0。 */
        unsigned int    lbdq_upoverflow_int0       : 1; /* [19..19] LBDQ上溢出中断0。 */
        unsigned int    reserved_1                 : 4; /* [23..20] 保留。 */
        unsigned int    rd_wbuf_full_int0          : 1; /* [24..24] RD缓存FIFO满中断0。 */
        unsigned int    adq0_full_int0             : 1; /* [25..25] ADQ0满中断0。 */
        unsigned int    adq1_full_int0             : 1; /* [26..26] ADQ1满中断0。 */
        unsigned int    lbdq_full_int0             : 1; /* [27..27] LBDQ满中断0。 */
        unsigned int    reserved_0                 : 4; /* [31..28] 保留。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_INT0_STAT_T;

typedef union
{
    struct
    {
        unsigned int    adq0_epty_int1             : 1; /* [0..0] ADQ0空中断1。 */
        unsigned int    adq1_epty_int1             : 1; /* [1..1] ADQ1空中断1。 */
        unsigned int    lbdq_epty_int1             : 1; /* [2..2] LBDQ空中断1。 */
        unsigned int    reserved_2                 : 13; /* [15..3] 保留。 */
        unsigned int    rd_wbuf_overflow_int1      : 1; /* [16..16] RD缓存FIFO溢出中断1。 */
        unsigned int    adq0_upoverflow_int1       : 1; /* [17..17] ADQ0上溢出中断1。 */
        unsigned int    adq1_upoverflow_int1       : 1; /* [18..18] ADQ1上溢出中断1。 */
        unsigned int    lbdq_upoverflow_int1       : 1; /* [19..19] LBDQ上溢出中断1。 */
        unsigned int    reserved_1                 : 4; /* [23..20] 保留。 */
        unsigned int    rd_wbuf_full_int1          : 1; /* [24..24] RD缓存FIFO满中断1。 */
        unsigned int    adq0_full_int1             : 1; /* [25..25] ADQ0满中断1。 */
        unsigned int    adq1_full_int1             : 1; /* [26..26] ADQ1满中断1。 */
        unsigned int    lbdq_full_int1             : 1; /* [27..27] LBDQ满中断1。 */
        unsigned int    reserved_0                 : 4; /* [31..28] 保留。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_INT1_STAT_T;

typedef union
{
    struct
    {
        unsigned int    adq0_epty_mstat0           : 1; /* [0..0] 屏蔽后ADQ0空中断0。 */
        unsigned int    adq1_epty_mstat0           : 1; /* [1..1] 屏蔽后ADQ1空中断0。 */
        unsigned int    lbdq_epty_mstat0           : 1; /* [2..2] 屏蔽后LBDQ空中断0。 */
        unsigned int    reserved_2                 : 13; /* [15..3] 保留。 */
        unsigned int    rd_wbuf_overflow_mstat0    : 1; /* [16..16] 屏蔽后RD缓存FIFO溢出中断0。 */
        unsigned int    adq0_upoverflow_mstat0     : 1; /* [17..17] 屏蔽后ADQ0上溢出中断0。 */
        unsigned int    adq1_upoverflow_mstat0     : 1; /* [18..18] 屏蔽后ADQ1上溢出中断0。 */
        unsigned int    lbdq_upoverflow_mstat0     : 1; /* [19..19] 屏蔽后LBDQ上溢出中断0。 */
        unsigned int    reserved_1                 : 4; /* [23..20] 保留。 */
        unsigned int    rd_wbuf_full_mstat0        : 1; /* [24..24] 屏蔽后RD缓存FIFO满中断0。 */
        unsigned int    adq0_full_mstat0           : 1; /* [25..25] 屏蔽后ADQ0满中断0。 */
        unsigned int    adq1_full_mstat0           : 1; /* [26..26] 屏蔽后ADQ1满中断0。 */
        unsigned int    lbdq_full_mstat0           : 1; /* [27..27] 屏蔽后LBDQ满中断0。 */
        unsigned int    reserved_0                 : 4; /* [31..28] 保留。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_INT0_MSTAT_T;

typedef union
{
    struct
    {
        unsigned int    adq0_epty_mstat1           : 1; /* [0..0] 屏蔽后ADQ0空中断1。 */
        unsigned int    adq1_epty_mstat1           : 1; /* [1..1] 屏蔽后ADQ1空中断1。 */
        unsigned int    lbdq_epty_mstat1           : 1; /* [2..2] 屏蔽后LBDQ空中断1。 */
        unsigned int    reserved_2                 : 13; /* [15..3] 保留。 */
        unsigned int    rd_wbuf_overflow_mstat1    : 1; /* [16..16] 屏蔽后RD缓存FIFO溢出中断1。 */
        unsigned int    adq0_upoverflow_mstat1     : 1; /* [17..17] 屏蔽后ADQ0上溢出中断1。 */
        unsigned int    adq1_upoverflow_mstat1     : 1; /* [18..18] 屏蔽后ADQ1上溢出中断1。 */
        unsigned int    lbdq_upoverflow_mstat1     : 1; /* [19..19] 屏蔽后LBDQ上溢出中断1。 */
        unsigned int    reserved_1                 : 4; /* [23..20] 保留。 */
        unsigned int    rd_wbuf_full_mstat1        : 1; /* [24..24] 屏蔽后RD缓存FIFO满中断1。 */
        unsigned int    adq0_full_mstat1           : 1; /* [25..25] 屏蔽后ADQ0满中断1。 */
        unsigned int    adq1_full_mstat1           : 1; /* [26..26] 屏蔽后ADQ1满中断1。 */
        unsigned int    lbdq_full_mstat1           : 1; /* [27..27] 屏蔽后LBDQ满中断1。 */
        unsigned int    reserved_0                 : 4; /* [31..28] 保留。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_INT1_MSTAT_T;

typedef union
{
    struct
    {
        unsigned int    adq0_epty_mask0            : 1; /* [0..0] ADQ0空中断0屏蔽。 */
        unsigned int    adq1_epty_mask0            : 1; /* [1..1] ADQ1空中断0屏蔽。 */
        unsigned int    lbdq_epty_mask0            : 1; /* [2..2] LBDQ空中断0屏蔽。 */
        unsigned int    reserved_2                 : 13; /* [15..3] 保留。 */
        unsigned int    rd_wbuf_overflow_mask0     : 1; /* [16..16] RD缓存FIFO溢出中断0屏蔽。 */
        unsigned int    adq0_upoverflow_mask0      : 1; /* [17..17] ADQ0上溢出中断0屏蔽。 */
        unsigned int    adq1_upoverflow_mask0      : 1; /* [18..18] ADQ1上溢出中断0屏蔽。 */
        unsigned int    lbdq_upoverflow_mask0      : 1; /* [19..19] LBDQ上溢出中断0屏蔽。 */
        unsigned int    reserved_1                 : 4; /* [23..20] 保留。 */
        unsigned int    rd_wbuf_full_mask0         : 1; /* [24..24] RD缓存FIFO满中断0屏蔽。 */
        unsigned int    adq0_full_mask0            : 1; /* [25..25] ADQ0满中断0屏蔽。 */
        unsigned int    adq1_full_mask0            : 1; /* [26..26] ADQ1满中断0屏蔽。 */
        unsigned int    lbdq_full_mask0            : 1; /* [27..27] LBDQ满中断0屏蔽。 */
        unsigned int    reserved_0                 : 4; /* [31..28] 保留。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_INT0_MASK_T;

typedef union
{
    struct
    {
        unsigned int    adq0_epty_mask1            : 1; /* [0..0] ADQ0空中断1屏蔽。 */
        unsigned int    adq1_epty_mask1            : 1; /* [1..1] ADQ1空中断1屏蔽。 */
        unsigned int    lbdq_epty_mask1            : 1; /* [2..2] LBDQ空中断1屏蔽。 */
        unsigned int    reserved_2                 : 13; /* [15..3] 保留。 */
        unsigned int    rd_wbuf_overflow_mask1     : 1; /* [16..16] RD缓存FIFO溢出中断1屏蔽。 */
        unsigned int    adq0_upoverflow_mask1      : 1; /* [17..17] ADQ0上溢出中断1屏蔽。 */
        unsigned int    adq1_upoverflow_mask1      : 1; /* [18..18] ADQ1上溢出中断1屏蔽。 */
        unsigned int    lbdq_upoverflow_mask1      : 1; /* [19..19] LBDQ上溢出中断1屏蔽。 */
        unsigned int    reserved_1                 : 4; /* [23..20] 保留。 */
        unsigned int    rd_wbuf_full_mask1         : 1; /* [24..24] RD缓存FIFO满中断1屏蔽。 */
        unsigned int    adq0_full_mask1            : 1; /* [25..25] ADQ0满中断1屏蔽。 */
        unsigned int    adq1_full_mask1            : 1; /* [26..26] ADQ1满中断1屏蔽。 */
        unsigned int    lbdq_full_mask1            : 1; /* [27..27] LBDQ满中断1屏蔽。 */
        unsigned int    reserved_0                 : 4; /* [31..28] 保留。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_INT1_MASK_T;

typedef union
{
    struct
    {
        unsigned int    cipher_ch_srst             : 1; /* [0..0] 软复位PSAM中cipher直通相关控制部分。在cipher单独复位后，复位该寄存器，配置1后，模块无总线请求时，复位生效。 */
        unsigned int    reserved                   : 31; /* [31..1] 保留。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_CIPHER_CH_SOFTRESET_T;

typedef union
{
    struct
    {
        unsigned int    cipher_ch_en               : 1; /* [0..0] PSAM中对cipher相关的直通通道区域单独使能配置。默认配置为1，当需要对cipher相关的指针进行回配时，需要先关闭该使能，再进行配置，然后打开使能。 */
        unsigned int    reserved                   : 30; /* [30..1] 保留。 */
        unsigned int    cipher_ch_busy             : 1; /* [31..31] 直通部分逻辑处于工作状态。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_CIPHER_CH_EN_T;

typedef union
{
    struct
    {
        unsigned int    cbd_iv_sel                 : 1; /* [0..0] Cipher 配置项，决定CBD长度。 */
        unsigned int    cbd_iv_num                 : 1; /* [1..1] Cipher 配置项，决定CBD长度。 */
        unsigned int    reserved_3                 : 2; /* [3..2] Cipher寄存器中对应rdq_ctrl配置项，需要每个BD都对应回写RD，在Cipher中应配置2’b01，在PSAM不需配置。 */
        unsigned int    reserved_2                 : 1; /* [4..4] 保留。 */
        unsigned int    reserved_1                 : 2; /* [6..5] Cipher寄存器中对应ufield_len配置项，需要配置3个Userfield，Cipher中应配置2’b11，在PSAM不需配置。 */
        unsigned int    reserved_0                 : 25; /* [31..7] 保留。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_CBDQ_CONFIG_T;

typedef union
{
    struct
    {
        unsigned int    reserved                   : 3; /* [2..0] 低3bit固定为0，基地址64位对齐。 */
        unsigned int    cbdq_base_addr             : 29; /* [31..3] Cipher BDQ 基地址高29位 */
    } bits;
    unsigned int    u32;
}HI_PSAM_CBDQ_BADDR_T;

typedef union
{
    struct
    {
        unsigned int    cbdq_size                  : 10; /* [9..0] CBDQ大小，可配1~1024。. */
        unsigned int    reserved                   : 22; /* [31..10] 保留。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_CBDQ_SIZE_T;

typedef union
{
    struct
    {
        unsigned int    cbdq_wptr                  : 10; /* [9..0] Cipher直通通道BDQ写指针，软件配置BDQ写指针到PSAM，再由PSAM控制配置到Cipher中，而非软件直接配置到Cipher。 */
        unsigned int    reserved                   : 22; /* [31..10] 保留。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_CBDQ_WPTR_T;

typedef union
{
    struct
    {
        unsigned int    local_cbdq_wptr            : 10; /* [9..0] 内部回写指针。（在逻辑cbdq_ctl处于idle时，可恢复配置，否则配置操作无效） */
        unsigned int    cbdq_wptr_invalid          : 1; /* [10..10] 非法写指针，指针大于CBDQ深度。 */
        unsigned int    reserved_1                 : 5; /* [15..11] 保留。 */
        unsigned int    local_cbdq_rptr            : 10; /* [25..16] 内部回读指针。（在逻辑cbdq_ctl处于idle时，可恢复配置，否则配置操作无效） */
        unsigned int    reserved_0                 : 6; /* [31..26] 保留。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_CBDQ_STAT_T;

typedef union
{
    struct
    {
        unsigned int    cbdq_wptr_addr             : 32; /* [31..0] Cipher直通通道BDQ写指针寄存器地址，软件配置BDQ写指针到PSAM，再由PSAM控制配置到Cipher中，而非软件直接配置到Cipher。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_CBDQ_WPTR_ADDR_T;

typedef union
{
    struct
    {
        unsigned int    fc_head                    : 3; /* [2..0] 直通RD转BD，fc_head可配值。 */
        unsigned int    reserved                   : 29; /* [31..3] 保留。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_CRDQ_CTRL_T;

typedef union
{
    struct
    {
        unsigned int    crd_wbuf1_full             : 1; /* [0..0] 下行直通RD暂存FIFO满。 */
        unsigned int    crd_wbuf1_epty             : 1; /* [1..1] 下行直通RD暂存FIFO空。 */
        unsigned int    crd_wbuf2_full             : 1; /* [2..2] 下行直通RD暂存FIFO满。 */
        unsigned int    crd_wbuf2_epty             : 1; /* [3..3] 下行直通RD暂存FIFO空。 */
        unsigned int    crd_wbuf3_full             : 1; /* [4..4] 下行直通RD暂存FIFO满。 */
        unsigned int    crd_wbuf3_epty             : 1; /* [5..5] 下行直通RD暂存FIFO空。 */
        unsigned int    crd_wbuf4_full             : 1; /* [6..6] 下行直通RD暂存FIFO满。 */
        unsigned int    crd_wbuf4_epty             : 1; /* [7..7] 下行直通RD暂存FIFO空。 */
        unsigned int    crd_wbuf5_full             : 1; /* [8..8] 下行直通RD暂存FIFO满。 */
        unsigned int    crd_wbuf5_epty             : 1; /* [9..9] 下行直通RD暂存FIFO空。 */
        unsigned int    reserved                   : 22; /* [31..10] 保留。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_CRDQ_STAT_T;

typedef union
{
    struct
    {
        unsigned int    local_crdq_wptr            : 2; /* [1..0] PSAM内计算的CRDQ写指针。（在逻辑crdq_ctl处于idle时，可恢复配置，否则配置操作无效） */
        unsigned int    reserved_1                 : 14; /* [15..2] 保留。 */
        unsigned int    local_crdq_rptr            : 2; /* [17..16] PSAM内计算的CRDQ读指针。（在逻辑crdq_ctl处于idle时，可恢复配置，否则配置操作无效） */
        unsigned int    reserved_0                 : 14; /* [31..18] 保留。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_CRDQ_PTR_T;

typedef union
{
    struct
    {
        unsigned int    crdq_rptr_addr             : 32; /* [31..0] Cipher的RDQ读指针寄存器地址。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_CRDQ_RPTR_ADDR_T;

typedef union
{
    struct
    {
        unsigned int    last_lbd_ibdq_wptr         : 8; /* [7..0] 最后的非直通BD在IBDQ中的写指针。 */
        unsigned int    last_lbd_lbdq_rptr         : 8; /* [15..8] 最后的非直通BD在LBDQ中的读指针。 */
        unsigned int    need_to_update             : 1; /* [16..16] 是否需要更新LBDQ读指针。 */
        unsigned int    reserved                   : 15; /* [31..17] 保留。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_IBDQ_STAT_T;

typedef union
{
    struct
    {
        unsigned int    reserved                   : 3; /* [2..0] 低3bit固定为0，基地址64位对齐。 */
        unsigned int    ibdq_addr                  : 29; /* [31..3] 下行通道IBDQ基地址。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_IBDQ_BADDR_T;

typedef union
{
    struct
    {
        unsigned int    ibdq_size                  : 8; /* [7..0] 下行IBDQ深度。 */
        unsigned int    reserved                   : 24; /* [31..8] 保留。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_IBDQ_SIZE_T;

typedef union
{
    struct
    {
        unsigned int    ibdq_wptr                  : 8; /* [7..0] 下行通道IBDQ写指针寄存器，反映已配入IPF。 */
        unsigned int    reserved                   : 24; /* [31..8] 保留。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_IBDQ_WPTR_T;

typedef union
{
    struct
    {
        unsigned int    ibdq_rptr                  : 8; /* [7..0] 下行通道IBDQ读指针寄存器，反映已从IPF读出的BDQ读指针。 */
        unsigned int    reserved                   : 24; /* [31..8] 保留。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_IBDQ_RPTR_T;

typedef union
{
    struct
    {
        unsigned int    ibdq_wptr_addr             : 32; /* [31..0] IPF BDQ的写指针存放地址。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_IBDQ_WPTR_ADDR_T;

typedef union
{
    struct
    {
        unsigned int    ibdq_rptr_addr             : 32; /* [31..0] IPF BDQ的读指针存放地址。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_IBDQ_RPTR_ADDR_T;

typedef union
{
    struct
    {
        unsigned int    ibdq_rptr_timer            : 16; /* [15..0] 下行通道IBDQ读指针刷新定时器。单位为时钟周期。 */
        unsigned int    reserved                   : 16; /* [31..16] 保留。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_IBDQ_RPTR_TIMER_T;

typedef union
{
    struct
    {
        unsigned int    ibdq_pkt_cnt               : 32; /* [31..0] 经过IBDQ的描述符个数，32bit回环计数。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_IBDQ_PKT_CNT_T;

typedef union
{
    struct
    {
        unsigned int    lbdq_epty                  : 1; /* [0..0] LBDQ空。 */
        unsigned int    lbdq_full                  : 1; /* [1..1] LBDQ满。 */
        unsigned int    lbd_rbuf_epty              : 1; /* [2..2] LBDQ空。 */
        unsigned int    lbd_rbuf_full              : 1; /* [3..3] LBDQ满。 */
        unsigned int    reserved_1                 : 12; /* [15..4] 保留。 */
        unsigned int    lbdq_wptr_invalid          : 1; /* [16..16] 非法写指针，指针大于IBDQ深度。 */
        unsigned int    reserved_0                 : 7; /* [23..17] 保留。 */
        unsigned int    local_lbdq_rptr            : 8; /* [31..24] 内部记录的LBDQ读指针。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_LBDQ_STAT_T;

typedef union
{
    struct
    {
        unsigned int    reserved                   : 3; /* [2..0] 低3bit固定为0，基地址64位对齐。 */
        unsigned int    lbdq_addr                  : 29; /* [31..3] 非直通下行通道LBDQ基地址。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_LBDQ_BADDR_T;

typedef union
{
    struct
    {
        unsigned int    lbdq_size                  : 8; /* [7..0] 非直通下行LBDQ深度。 */
        unsigned int    reserved                   : 24; /* [31..8] 保留。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_LBDQ_SIZE_T;

typedef union
{
    struct
    {
        unsigned int    lbdq_wptr                  : 8; /* [7..0] 下行通道LBDQ写指针寄存器，配置不能大于LBDQ深度。 */
        unsigned int    reserved                   : 24; /* [31..8] 保留。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_LBDQ_WPTR_T;

typedef union
{
    struct
    {
        unsigned int    real_lbdq_rptr             : 8; /* [7..0] 下行通道LBDQ读指针寄存器。 */
        unsigned int    reserved                   : 24; /* [31..8] 保留。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_LBDQ_RPTR_T;

typedef union
{
    struct
    {
        unsigned int    lbdq_depth                 : 9; /* [8..0] 下行BDQ当前深度寄存器,表示BDQ中BD的个数.等于0表示空,等于lbdq_size表示满（满时有一个bdq空间未利用。当lbdq_size为0时，做了特殊处理，lbdq_depth为1表示满） */
        unsigned int    reserved                   : 23; /* [31..9] 保留。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_LBDQ_DEPTH_T;

typedef union
{
    struct
    {
        unsigned int    reserved_1                 : 1; /* [0..0] 保留。 */
        unsigned int    adq_en                     : 1; /* [1..1] 下行通道ADQ0使能。0：表示下行通道使用ADQ0；1：表示下行通道使用ADQ0和ADQ1； */
        unsigned int    adq0_size_sel              : 2; /* [3..2] ADQ0大小选择寄存器。00：表示ADQ0的大小为32；01：表示ADQ0的大小为64；10：表示ADQ0的大小为128；11：表示ADQ0的大小为256； */
        unsigned int    adq1_size_sel              : 2; /* [5..4] ADQ1大小选择寄存器。00：表示ADQ1的大小为32；01：表示ADQ1的大小为64；10：表示ADQ1的大小为128；11：表示ADQ1的大小为256； */
        unsigned int    reserved_0                 : 10; /* [15..6] 保留。 */
        unsigned int    adq_plen_th                : 16; /* [31..16] 下行通道数据长短包区分包长阈值。当下行通道两个adq都开启时，如果当前数据包长小于阈值，使用adq0的AD；否则使用adq1的AD。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_ADQ_CTRL_T;

typedef union
{
    struct
    {
        unsigned int    reserved                   : 3; /* [2..0] 低3bit固定为0，基地址64位对齐。 */
        unsigned int    adq0_base                  : 29; /* [31..3] PSAM 短包ADQ 基地址配置。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_ADQ0_BASE_T;

typedef union
{
    struct
    {
        unsigned int    adq0_epty                  : 1; /* [0..0] 下行ADQ0空状态指示寄存器。 */
        unsigned int    adq0_full                  : 1; /* [1..1] 下行ADQ0满状态指示寄存器。 */
        unsigned int    ad0_buf_epty               : 1; /* [2..2] 下行ADQ0暂存fifo空状态指示寄存器。 */
        unsigned int    ad0_buf_full               : 1; /* [3..3] 下行ADQ0暂存fifo满状态指示寄存器。 */
        unsigned int    adq0_rptr_invalid          : 1; /* [4..4] 下行ADQ0读指针无效。 */
        unsigned int    adq0_wptr_invalid          : 1; /* [5..5] 下行ADQ0写指针无效。 */
        unsigned int    reserved                   : 26; /* [31..6] 保留。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_ADQ0_STAT_T;

typedef union
{
    struct
    {
        unsigned int    adq0_wptr                  : 8; /* [7..0] 下行通道ADQ0写指针。 */
        unsigned int    reserved                   : 24; /* [31..8] 保留。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_ADQ0_WPTR_T;

typedef union
{
    struct
    {
        unsigned int    adq0_rptr                  : 8; /* [7..0] 下行通道ADQ0读指针。 */
        unsigned int    reserved                   : 24; /* [31..8] 保留。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_ADQ0_RPTR_T;

typedef union
{
    struct
    {
        unsigned int    reserved                   : 3; /* [2..0] 低3bit固定为0，基地址64位对齐。 */
        unsigned int    adq1_base                  : 29; /* [31..3] PSAM 长包ADQ 基地址配置。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_ADQ1_BASE_T;

typedef union
{
    struct
    {
        unsigned int    adq1_epty                  : 1; /* [0..0] 下行ADQ1空状态指示寄存器。 */
        unsigned int    adq1_full                  : 1; /* [1..1] 下行ADQ1满状态指示寄存器。 */
        unsigned int    ad1_buf_epty               : 1; /* [2..2] 下行ADQ1暂存fifo空状态指示寄存器。 */
        unsigned int    ad1_buf_full               : 1; /* [3..3] 下行ADQ1暂存fifo满状态指示寄存器。 */
        unsigned int    adq1_rptr_invalid          : 1; /* [4..4] 下行ADQ1读指针无效。 */
        unsigned int    adq1_wptr_invalid          : 1; /* [5..5] 下行ADQ1写指针无效。 */
        unsigned int    reserved                   : 26; /* [31..6] 保留。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_ADQ1_STAT_T;

typedef union
{
    struct
    {
        unsigned int    adq1_wptr                  : 8; /* [7..0] 下行通道ADQ1写指针。 */
        unsigned int    reserved                   : 24; /* [31..8] 保留。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_ADQ1_WPTR_T;

typedef union
{
    struct
    {
        unsigned int    adq1_rptr                  : 8; /* [7..0] 下行通道ADQ1读指针。 */
        unsigned int    reserved                   : 24; /* [31..8] 保留。 */
    } bits;
    unsigned int    u32;
}HI_PSAM_ADQ1_RPTR_T;

typedef union
{
    struct
    {
        unsigned int    psam_crdq_baddr            : 32; /* [31..0] PSAM中的地址空间0x0400~0x045C对应着CipherRDQ的空间，需要在Cipher中下行直通寄存器RDQ_BADDR中配置该寄存器的实际地址（PSAM基地址+0x00000400） */
    } bits;
    unsigned int    u32;
}HI_PSAM_CRDQ_BADDR_T;

#if 0

/********************************************************************************/
/*    hi 函数（项目名_模块名_寄存器名_成员名_set)        */
/********************************************************************************/
HI_SET_GET(hi_psam_srst_psam_srst,psam_srst,HI_PSAM_SRST_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_SRST_OFFSET)
HI_SET_GET(hi_psam_srst_psam_idle,psam_idle,HI_PSAM_SRST_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_SRST_OFFSET)
HI_SET_GET(hi_psam_srst_reserved,reserved,HI_PSAM_SRST_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_SRST_OFFSET)
HI_SET_GET(hi_psam_config_psam_rd_pri,psam_rd_pri,HI_PSAM_CONFIG_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CONFIG_OFFSET)
HI_SET_GET(hi_psam_config_psam_wr_pri,psam_wr_pri,HI_PSAM_CONFIG_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CONFIG_OFFSET)
HI_SET_GET(hi_psam_config_cbdq_wptr_update_mode,cbdq_wptr_update_mode,HI_PSAM_CONFIG_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CONFIG_OFFSET)
HI_SET_GET(hi_psam_config_cbdq_wptr_update_num,cbdq_wptr_update_num,HI_PSAM_CONFIG_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CONFIG_OFFSET)
HI_SET_GET(hi_psam_config_reserved,reserved,HI_PSAM_CONFIG_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CONFIG_OFFSET)
HI_SET_GET(hi_psam_config_psam_cfg_rsvd,psam_cfg_rsvd,HI_PSAM_CONFIG_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CONFIG_OFFSET)
HI_SET_GET(hi_psam_version_psam_version,psam_version,HI_PSAM_VERSION_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_VERSION_OFFSET)
HI_SET_GET(hi_psam_en_psam_en,psam_en,HI_PSAM_EN_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_EN_OFFSET)
HI_SET_GET(hi_psam_en_reserved,reserved,HI_PSAM_EN_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_EN_OFFSET)
HI_SET_GET(hi_psam_int0_stat_adq0_epty_int0,adq0_epty_int0,HI_PSAM_INT0_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_STAT_OFFSET)
HI_SET_GET(hi_psam_int0_stat_adq1_epty_int0,adq1_epty_int0,HI_PSAM_INT0_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_STAT_OFFSET)
HI_SET_GET(hi_psam_int0_stat_lbdq_epty_int0,lbdq_epty_int0,HI_PSAM_INT0_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_STAT_OFFSET)
HI_SET_GET(hi_psam_int0_stat_reserved_2,reserved_2,HI_PSAM_INT0_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_STAT_OFFSET)
HI_SET_GET(hi_psam_int0_stat_rd_wbuf_overflow_int0,rd_wbuf_overflow_int0,HI_PSAM_INT0_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_STAT_OFFSET)
HI_SET_GET(hi_psam_int0_stat_adq0_upoverflow_int0,adq0_upoverflow_int0,HI_PSAM_INT0_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_STAT_OFFSET)
HI_SET_GET(hi_psam_int0_stat_adq1_upoverflow_int0,adq1_upoverflow_int0,HI_PSAM_INT0_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_STAT_OFFSET)
HI_SET_GET(hi_psam_int0_stat_lbdq_upoverflow_int0,lbdq_upoverflow_int0,HI_PSAM_INT0_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_STAT_OFFSET)
HI_SET_GET(hi_psam_int0_stat_reserved_1,reserved_1,HI_PSAM_INT0_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_STAT_OFFSET)
HI_SET_GET(hi_psam_int0_stat_rd_wbuf_full_int0,rd_wbuf_full_int0,HI_PSAM_INT0_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_STAT_OFFSET)
HI_SET_GET(hi_psam_int0_stat_adq0_full_int0,adq0_full_int0,HI_PSAM_INT0_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_STAT_OFFSET)
HI_SET_GET(hi_psam_int0_stat_adq1_full_int0,adq1_full_int0,HI_PSAM_INT0_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_STAT_OFFSET)
HI_SET_GET(hi_psam_int0_stat_lbdq_full_int0,lbdq_full_int0,HI_PSAM_INT0_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_STAT_OFFSET)
HI_SET_GET(hi_psam_int0_stat_reserved_0,reserved_0,HI_PSAM_INT0_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_STAT_OFFSET)
HI_SET_GET(hi_psam_int1_stat_adq0_epty_int1,adq0_epty_int1,HI_PSAM_INT1_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_STAT_OFFSET)
HI_SET_GET(hi_psam_int1_stat_adq1_epty_int1,adq1_epty_int1,HI_PSAM_INT1_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_STAT_OFFSET)
HI_SET_GET(hi_psam_int1_stat_lbdq_epty_int1,lbdq_epty_int1,HI_PSAM_INT1_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_STAT_OFFSET)
HI_SET_GET(hi_psam_int1_stat_reserved_2,reserved_2,HI_PSAM_INT1_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_STAT_OFFSET)
HI_SET_GET(hi_psam_int1_stat_rd_wbuf_overflow_int1,rd_wbuf_overflow_int1,HI_PSAM_INT1_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_STAT_OFFSET)
HI_SET_GET(hi_psam_int1_stat_adq0_upoverflow_int1,adq0_upoverflow_int1,HI_PSAM_INT1_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_STAT_OFFSET)
HI_SET_GET(hi_psam_int1_stat_adq1_upoverflow_int1,adq1_upoverflow_int1,HI_PSAM_INT1_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_STAT_OFFSET)
HI_SET_GET(hi_psam_int1_stat_lbdq_upoverflow_int1,lbdq_upoverflow_int1,HI_PSAM_INT1_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_STAT_OFFSET)
HI_SET_GET(hi_psam_int1_stat_reserved_1,reserved_1,HI_PSAM_INT1_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_STAT_OFFSET)
HI_SET_GET(hi_psam_int1_stat_rd_wbuf_full_int1,rd_wbuf_full_int1,HI_PSAM_INT1_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_STAT_OFFSET)
HI_SET_GET(hi_psam_int1_stat_adq0_full_int1,adq0_full_int1,HI_PSAM_INT1_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_STAT_OFFSET)
HI_SET_GET(hi_psam_int1_stat_adq1_full_int1,adq1_full_int1,HI_PSAM_INT1_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_STAT_OFFSET)
HI_SET_GET(hi_psam_int1_stat_lbdq_full_int1,lbdq_full_int1,HI_PSAM_INT1_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_STAT_OFFSET)
HI_SET_GET(hi_psam_int1_stat_reserved_0,reserved_0,HI_PSAM_INT1_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_STAT_OFFSET)
HI_SET_GET(hi_psam_int0_mstat_adq0_epty_mstat0,adq0_epty_mstat0,HI_PSAM_INT0_MSTAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_MSTAT_OFFSET)
HI_SET_GET(hi_psam_int0_mstat_adq1_epty_mstat0,adq1_epty_mstat0,HI_PSAM_INT0_MSTAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_MSTAT_OFFSET)
HI_SET_GET(hi_psam_int0_mstat_lbdq_epty_mstat0,lbdq_epty_mstat0,HI_PSAM_INT0_MSTAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_MSTAT_OFFSET)
HI_SET_GET(hi_psam_int0_mstat_reserved_2,reserved_2,HI_PSAM_INT0_MSTAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_MSTAT_OFFSET)
HI_SET_GET(hi_psam_int0_mstat_rd_wbuf_overflow_mstat0,rd_wbuf_overflow_mstat0,HI_PSAM_INT0_MSTAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_MSTAT_OFFSET)
HI_SET_GET(hi_psam_int0_mstat_adq0_upoverflow_mstat0,adq0_upoverflow_mstat0,HI_PSAM_INT0_MSTAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_MSTAT_OFFSET)
HI_SET_GET(hi_psam_int0_mstat_adq1_upoverflow_mstat0,adq1_upoverflow_mstat0,HI_PSAM_INT0_MSTAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_MSTAT_OFFSET)
HI_SET_GET(hi_psam_int0_mstat_lbdq_upoverflow_mstat0,lbdq_upoverflow_mstat0,HI_PSAM_INT0_MSTAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_MSTAT_OFFSET)
HI_SET_GET(hi_psam_int0_mstat_reserved_1,reserved_1,HI_PSAM_INT0_MSTAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_MSTAT_OFFSET)
HI_SET_GET(hi_psam_int0_mstat_rd_wbuf_full_mstat0,rd_wbuf_full_mstat0,HI_PSAM_INT0_MSTAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_MSTAT_OFFSET)
HI_SET_GET(hi_psam_int0_mstat_adq0_full_mstat0,adq0_full_mstat0,HI_PSAM_INT0_MSTAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_MSTAT_OFFSET)
HI_SET_GET(hi_psam_int0_mstat_adq1_full_mstat0,adq1_full_mstat0,HI_PSAM_INT0_MSTAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_MSTAT_OFFSET)
HI_SET_GET(hi_psam_int0_mstat_lbdq_full_mstat0,lbdq_full_mstat0,HI_PSAM_INT0_MSTAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_MSTAT_OFFSET)
HI_SET_GET(hi_psam_int0_mstat_reserved_0,reserved_0,HI_PSAM_INT0_MSTAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_MSTAT_OFFSET)
HI_SET_GET(hi_psam_int1_mstat_adq0_epty_mstat1,adq0_epty_mstat1,HI_PSAM_INT1_MSTAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_MSTAT_OFFSET)
HI_SET_GET(hi_psam_int1_mstat_adq1_epty_mstat1,adq1_epty_mstat1,HI_PSAM_INT1_MSTAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_MSTAT_OFFSET)
HI_SET_GET(hi_psam_int1_mstat_lbdq_epty_mstat1,lbdq_epty_mstat1,HI_PSAM_INT1_MSTAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_MSTAT_OFFSET)
HI_SET_GET(hi_psam_int1_mstat_reserved_2,reserved_2,HI_PSAM_INT1_MSTAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_MSTAT_OFFSET)
HI_SET_GET(hi_psam_int1_mstat_rd_wbuf_overflow_mstat1,rd_wbuf_overflow_mstat1,HI_PSAM_INT1_MSTAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_MSTAT_OFFSET)
HI_SET_GET(hi_psam_int1_mstat_adq0_upoverflow_mstat1,adq0_upoverflow_mstat1,HI_PSAM_INT1_MSTAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_MSTAT_OFFSET)
HI_SET_GET(hi_psam_int1_mstat_adq1_upoverflow_mstat1,adq1_upoverflow_mstat1,HI_PSAM_INT1_MSTAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_MSTAT_OFFSET)
HI_SET_GET(hi_psam_int1_mstat_lbdq_upoverflow_mstat1,lbdq_upoverflow_mstat1,HI_PSAM_INT1_MSTAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_MSTAT_OFFSET)
HI_SET_GET(hi_psam_int1_mstat_reserved_1,reserved_1,HI_PSAM_INT1_MSTAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_MSTAT_OFFSET)
HI_SET_GET(hi_psam_int1_mstat_rd_wbuf_full_mstat1,rd_wbuf_full_mstat1,HI_PSAM_INT1_MSTAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_MSTAT_OFFSET)
HI_SET_GET(hi_psam_int1_mstat_adq0_full_mstat1,adq0_full_mstat1,HI_PSAM_INT1_MSTAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_MSTAT_OFFSET)
HI_SET_GET(hi_psam_int1_mstat_adq1_full_mstat1,adq1_full_mstat1,HI_PSAM_INT1_MSTAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_MSTAT_OFFSET)
HI_SET_GET(hi_psam_int1_mstat_lbdq_full_mstat1,lbdq_full_mstat1,HI_PSAM_INT1_MSTAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_MSTAT_OFFSET)
HI_SET_GET(hi_psam_int1_mstat_reserved_0,reserved_0,HI_PSAM_INT1_MSTAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_MSTAT_OFFSET)
HI_SET_GET(hi_psam_int0_mask_adq0_epty_mask0,adq0_epty_mask0,HI_PSAM_INT0_MASK_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_MASK_OFFSET)
HI_SET_GET(hi_psam_int0_mask_adq1_epty_mask0,adq1_epty_mask0,HI_PSAM_INT0_MASK_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_MASK_OFFSET)
HI_SET_GET(hi_psam_int0_mask_lbdq_epty_mask0,lbdq_epty_mask0,HI_PSAM_INT0_MASK_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_MASK_OFFSET)
HI_SET_GET(hi_psam_int0_mask_reserved_2,reserved_2,HI_PSAM_INT0_MASK_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_MASK_OFFSET)
HI_SET_GET(hi_psam_int0_mask_rd_wbuf_overflow_mask0,rd_wbuf_overflow_mask0,HI_PSAM_INT0_MASK_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_MASK_OFFSET)
HI_SET_GET(hi_psam_int0_mask_adq0_upoverflow_mask0,adq0_upoverflow_mask0,HI_PSAM_INT0_MASK_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_MASK_OFFSET)
HI_SET_GET(hi_psam_int0_mask_adq1_upoverflow_mask0,adq1_upoverflow_mask0,HI_PSAM_INT0_MASK_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_MASK_OFFSET)
HI_SET_GET(hi_psam_int0_mask_lbdq_upoverflow_mask0,lbdq_upoverflow_mask0,HI_PSAM_INT0_MASK_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_MASK_OFFSET)
HI_SET_GET(hi_psam_int0_mask_reserved_1,reserved_1,HI_PSAM_INT0_MASK_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_MASK_OFFSET)
HI_SET_GET(hi_psam_int0_mask_rd_wbuf_full_mask0,rd_wbuf_full_mask0,HI_PSAM_INT0_MASK_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_MASK_OFFSET)
HI_SET_GET(hi_psam_int0_mask_adq0_full_mask0,adq0_full_mask0,HI_PSAM_INT0_MASK_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_MASK_OFFSET)
HI_SET_GET(hi_psam_int0_mask_adq1_full_mask0,adq1_full_mask0,HI_PSAM_INT0_MASK_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_MASK_OFFSET)
HI_SET_GET(hi_psam_int0_mask_lbdq_full_mask0,lbdq_full_mask0,HI_PSAM_INT0_MASK_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_MASK_OFFSET)
HI_SET_GET(hi_psam_int0_mask_reserved_0,reserved_0,HI_PSAM_INT0_MASK_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT0_MASK_OFFSET)
HI_SET_GET(hi_psam_int1_mask_adq0_epty_mask1,adq0_epty_mask1,HI_PSAM_INT1_MASK_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_MASK_OFFSET)
HI_SET_GET(hi_psam_int1_mask_adq1_epty_mask1,adq1_epty_mask1,HI_PSAM_INT1_MASK_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_MASK_OFFSET)
HI_SET_GET(hi_psam_int1_mask_lbdq_epty_mask1,lbdq_epty_mask1,HI_PSAM_INT1_MASK_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_MASK_OFFSET)
HI_SET_GET(hi_psam_int1_mask_reserved_2,reserved_2,HI_PSAM_INT1_MASK_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_MASK_OFFSET)
HI_SET_GET(hi_psam_int1_mask_rd_wbuf_overflow_mask1,rd_wbuf_overflow_mask1,HI_PSAM_INT1_MASK_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_MASK_OFFSET)
HI_SET_GET(hi_psam_int1_mask_adq0_upoverflow_mask1,adq0_upoverflow_mask1,HI_PSAM_INT1_MASK_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_MASK_OFFSET)
HI_SET_GET(hi_psam_int1_mask_adq1_upoverflow_mask1,adq1_upoverflow_mask1,HI_PSAM_INT1_MASK_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_MASK_OFFSET)
HI_SET_GET(hi_psam_int1_mask_lbdq_upoverflow_mask1,lbdq_upoverflow_mask1,HI_PSAM_INT1_MASK_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_MASK_OFFSET)
HI_SET_GET(hi_psam_int1_mask_reserved_1,reserved_1,HI_PSAM_INT1_MASK_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_MASK_OFFSET)
HI_SET_GET(hi_psam_int1_mask_rd_wbuf_full_mask1,rd_wbuf_full_mask1,HI_PSAM_INT1_MASK_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_MASK_OFFSET)
HI_SET_GET(hi_psam_int1_mask_adq0_full_mask1,adq0_full_mask1,HI_PSAM_INT1_MASK_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_MASK_OFFSET)
HI_SET_GET(hi_psam_int1_mask_adq1_full_mask1,adq1_full_mask1,HI_PSAM_INT1_MASK_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_MASK_OFFSET)
HI_SET_GET(hi_psam_int1_mask_lbdq_full_mask1,lbdq_full_mask1,HI_PSAM_INT1_MASK_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_MASK_OFFSET)
HI_SET_GET(hi_psam_int1_mask_reserved_0,reserved_0,HI_PSAM_INT1_MASK_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_INT1_MASK_OFFSET)
HI_SET_GET(hi_psam_cipher_ch_softreset_cipher_ch_srst,cipher_ch_srst,HI_PSAM_CIPHER_CH_SOFTRESET_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CIPHER_CH_SOFTRESET_OFFSET)
HI_SET_GET(hi_psam_cipher_ch_softreset_reserved,reserved,HI_PSAM_CIPHER_CH_SOFTRESET_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CIPHER_CH_SOFTRESET_OFFSET)
HI_SET_GET(hi_psam_cipher_ch_en_cipher_ch_en,cipher_ch_en,HI_PSAM_CIPHER_CH_EN_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CIPHER_CH_EN_OFFSET)
HI_SET_GET(hi_psam_cipher_ch_en_reserved,reserved,HI_PSAM_CIPHER_CH_EN_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CIPHER_CH_EN_OFFSET)
HI_SET_GET(hi_psam_cipher_ch_en_cipher_ch_busy,cipher_ch_busy,HI_PSAM_CIPHER_CH_EN_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CIPHER_CH_EN_OFFSET)
HI_SET_GET(hi_psam_cbdq_config_cbd_iv_sel,cbd_iv_sel,HI_PSAM_CBDQ_CONFIG_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CBDQ_CONFIG_OFFSET)
HI_SET_GET(hi_psam_cbdq_config_cbd_iv_num,cbd_iv_num,HI_PSAM_CBDQ_CONFIG_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CBDQ_CONFIG_OFFSET)
HI_SET_GET(hi_psam_cbdq_config_reserved_3,reserved_3,HI_PSAM_CBDQ_CONFIG_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CBDQ_CONFIG_OFFSET)
HI_SET_GET(hi_psam_cbdq_config_reserved_2,reserved_2,HI_PSAM_CBDQ_CONFIG_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CBDQ_CONFIG_OFFSET)
HI_SET_GET(hi_psam_cbdq_config_reserved_1,reserved_1,HI_PSAM_CBDQ_CONFIG_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CBDQ_CONFIG_OFFSET)
HI_SET_GET(hi_psam_cbdq_config_reserved_0,reserved_0,HI_PSAM_CBDQ_CONFIG_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CBDQ_CONFIG_OFFSET)
HI_SET_GET(hi_psam_cbdq_baddr_reserved,reserved,HI_PSAM_CBDQ_BADDR_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CBDQ_BADDR_OFFSET)
HI_SET_GET(hi_psam_cbdq_baddr_cbdq_base_addr,cbdq_base_addr,HI_PSAM_CBDQ_BADDR_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CBDQ_BADDR_OFFSET)
HI_SET_GET(hi_psam_cbdq_size_cbdq_size,cbdq_size,HI_PSAM_CBDQ_SIZE_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CBDQ_SIZE_OFFSET)
HI_SET_GET(hi_psam_cbdq_size_reserved,reserved,HI_PSAM_CBDQ_SIZE_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CBDQ_SIZE_OFFSET)
HI_SET_GET(hi_psam_cbdq_wptr_cbdq_wptr,cbdq_wptr,HI_PSAM_CBDQ_WPTR_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CBDQ_WPTR_OFFSET)
HI_SET_GET(hi_psam_cbdq_wptr_reserved,reserved,HI_PSAM_CBDQ_WPTR_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CBDQ_WPTR_OFFSET)
HI_SET_GET(hi_psam_cbdq_stat_local_cbdq_wptr,local_cbdq_wptr,HI_PSAM_CBDQ_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CBDQ_STAT_OFFSET)
HI_SET_GET(hi_psam_cbdq_stat_cbdq_wptr_invalid,cbdq_wptr_invalid,HI_PSAM_CBDQ_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CBDQ_STAT_OFFSET)
HI_SET_GET(hi_psam_cbdq_stat_reserved_1,reserved_1,HI_PSAM_CBDQ_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CBDQ_STAT_OFFSET)
HI_SET_GET(hi_psam_cbdq_stat_local_cbdq_rptr,local_cbdq_rptr,HI_PSAM_CBDQ_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CBDQ_STAT_OFFSET)
HI_SET_GET(hi_psam_cbdq_stat_reserved_0,reserved_0,HI_PSAM_CBDQ_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CBDQ_STAT_OFFSET)
HI_SET_GET(hi_psam_cbdq_wptr_addr_cbdq_wptr_addr,cbdq_wptr_addr,HI_PSAM_CBDQ_WPTR_ADDR_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CBDQ_WPTR_ADDR_OFFSET)
HI_SET_GET(hi_psam_crdq_ctrl_fc_head,fc_head,HI_PSAM_CRDQ_CTRL_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CRDQ_CTRL_OFFSET)
HI_SET_GET(hi_psam_crdq_ctrl_reserved,reserved,HI_PSAM_CRDQ_CTRL_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CRDQ_CTRL_OFFSET)
HI_SET_GET(hi_psam_crdq_stat_crd_wbuf1_full,crd_wbuf1_full,HI_PSAM_CRDQ_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CRDQ_STAT_OFFSET)
HI_SET_GET(hi_psam_crdq_stat_crd_wbuf1_epty,crd_wbuf1_epty,HI_PSAM_CRDQ_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CRDQ_STAT_OFFSET)
HI_SET_GET(hi_psam_crdq_stat_crd_wbuf2_full,crd_wbuf2_full,HI_PSAM_CRDQ_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CRDQ_STAT_OFFSET)
HI_SET_GET(hi_psam_crdq_stat_crd_wbuf2_epty,crd_wbuf2_epty,HI_PSAM_CRDQ_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CRDQ_STAT_OFFSET)
HI_SET_GET(hi_psam_crdq_stat_crd_wbuf3_full,crd_wbuf3_full,HI_PSAM_CRDQ_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CRDQ_STAT_OFFSET)
HI_SET_GET(hi_psam_crdq_stat_crd_wbuf3_epty,crd_wbuf3_epty,HI_PSAM_CRDQ_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CRDQ_STAT_OFFSET)
HI_SET_GET(hi_psam_crdq_stat_crd_wbuf4_full,crd_wbuf4_full,HI_PSAM_CRDQ_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CRDQ_STAT_OFFSET)
HI_SET_GET(hi_psam_crdq_stat_crd_wbuf4_epty,crd_wbuf4_epty,HI_PSAM_CRDQ_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CRDQ_STAT_OFFSET)
HI_SET_GET(hi_psam_crdq_stat_crd_wbuf5_full,crd_wbuf5_full,HI_PSAM_CRDQ_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CRDQ_STAT_OFFSET)
HI_SET_GET(hi_psam_crdq_stat_crd_wbuf5_epty,crd_wbuf5_epty,HI_PSAM_CRDQ_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CRDQ_STAT_OFFSET)
HI_SET_GET(hi_psam_crdq_stat_reserved,reserved,HI_PSAM_CRDQ_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CRDQ_STAT_OFFSET)
HI_SET_GET(hi_psam_crdq_ptr_local_crdq_wptr,local_crdq_wptr,HI_PSAM_CRDQ_PTR_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CRDQ_PTR_OFFSET)
HI_SET_GET(hi_psam_crdq_ptr_reserved_1,reserved_1,HI_PSAM_CRDQ_PTR_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CRDQ_PTR_OFFSET)
HI_SET_GET(hi_psam_crdq_ptr_local_crdq_rptr,local_crdq_rptr,HI_PSAM_CRDQ_PTR_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CRDQ_PTR_OFFSET)
HI_SET_GET(hi_psam_crdq_ptr_reserved_0,reserved_0,HI_PSAM_CRDQ_PTR_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CRDQ_PTR_OFFSET)
HI_SET_GET(hi_psam_crdq_rptr_addr_crdq_rptr_addr,crdq_rptr_addr,HI_PSAM_CRDQ_RPTR_ADDR_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CRDQ_RPTR_ADDR_OFFSET)
HI_SET_GET(hi_psam_ibdq_stat_last_lbd_ibdq_wptr,last_lbd_ibdq_wptr,HI_PSAM_IBDQ_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_IBDQ_STAT_OFFSET)
HI_SET_GET(hi_psam_ibdq_stat_last_lbd_lbdq_rptr,last_lbd_lbdq_rptr,HI_PSAM_IBDQ_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_IBDQ_STAT_OFFSET)
HI_SET_GET(hi_psam_ibdq_stat_need_to_update,need_to_update,HI_PSAM_IBDQ_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_IBDQ_STAT_OFFSET)
HI_SET_GET(hi_psam_ibdq_stat_reserved,reserved,HI_PSAM_IBDQ_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_IBDQ_STAT_OFFSET)
HI_SET_GET(hi_psam_ibdq_baddr_reserved,reserved,HI_PSAM_IBDQ_BADDR_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_IBDQ_BADDR_OFFSET)
HI_SET_GET(hi_psam_ibdq_baddr_ibdq_addr,ibdq_addr,HI_PSAM_IBDQ_BADDR_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_IBDQ_BADDR_OFFSET)
HI_SET_GET(hi_psam_ibdq_size_ibdq_size,ibdq_size,HI_PSAM_IBDQ_SIZE_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_IBDQ_SIZE_OFFSET)
HI_SET_GET(hi_psam_ibdq_size_reserved,reserved,HI_PSAM_IBDQ_SIZE_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_IBDQ_SIZE_OFFSET)
HI_SET_GET(hi_psam_ibdq_wptr_ibdq_wptr,ibdq_wptr,HI_PSAM_IBDQ_WPTR_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_IBDQ_WPTR_OFFSET)
HI_SET_GET(hi_psam_ibdq_wptr_reserved,reserved,HI_PSAM_IBDQ_WPTR_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_IBDQ_WPTR_OFFSET)
HI_SET_GET(hi_psam_ibdq_rptr_ibdq_rptr,ibdq_rptr,HI_PSAM_IBDQ_RPTR_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_IBDQ_RPTR_OFFSET)
HI_SET_GET(hi_psam_ibdq_rptr_reserved,reserved,HI_PSAM_IBDQ_RPTR_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_IBDQ_RPTR_OFFSET)
HI_SET_GET(hi_psam_ibdq_wptr_addr_ibdq_wptr_addr,ibdq_wptr_addr,HI_PSAM_IBDQ_WPTR_ADDR_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_IBDQ_WPTR_ADDR_OFFSET)
HI_SET_GET(hi_psam_ibdq_rptr_addr_ibdq_rptr_addr,ibdq_rptr_addr,HI_PSAM_IBDQ_RPTR_ADDR_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_IBDQ_RPTR_ADDR_OFFSET)
HI_SET_GET(hi_psam_ibdq_rptr_timer_ibdq_rptr_timer,ibdq_rptr_timer,HI_PSAM_IBDQ_RPTR_TIMER_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_IBDQ_RPTR_TIMER_OFFSET)
HI_SET_GET(hi_psam_ibdq_rptr_timer_reserved,reserved,HI_PSAM_IBDQ_RPTR_TIMER_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_IBDQ_RPTR_TIMER_OFFSET)
HI_SET_GET(hi_psam_ibdq_pkt_cnt_ibdq_pkt_cnt,ibdq_pkt_cnt,HI_PSAM_IBDQ_PKT_CNT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_IBDQ_PKT_CNT_OFFSET)
HI_SET_GET(hi_psam_lbdq_stat_lbdq_epty,lbdq_epty,HI_PSAM_LBDQ_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_LBDQ_STAT_OFFSET)
HI_SET_GET(hi_psam_lbdq_stat_lbdq_full,lbdq_full,HI_PSAM_LBDQ_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_LBDQ_STAT_OFFSET)
HI_SET_GET(hi_psam_lbdq_stat_lbd_rbuf_epty,lbd_rbuf_epty,HI_PSAM_LBDQ_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_LBDQ_STAT_OFFSET)
HI_SET_GET(hi_psam_lbdq_stat_lbd_rbuf_full,lbd_rbuf_full,HI_PSAM_LBDQ_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_LBDQ_STAT_OFFSET)
HI_SET_GET(hi_psam_lbdq_stat_reserved_1,reserved_1,HI_PSAM_LBDQ_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_LBDQ_STAT_OFFSET)
HI_SET_GET(hi_psam_lbdq_stat_lbdq_wptr_invalid,lbdq_wptr_invalid,HI_PSAM_LBDQ_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_LBDQ_STAT_OFFSET)
HI_SET_GET(hi_psam_lbdq_stat_reserved_0,reserved_0,HI_PSAM_LBDQ_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_LBDQ_STAT_OFFSET)
HI_SET_GET(hi_psam_lbdq_stat_local_lbdq_rptr,local_lbdq_rptr,HI_PSAM_LBDQ_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_LBDQ_STAT_OFFSET)
HI_SET_GET(hi_psam_lbdq_baddr_reserved,reserved,HI_PSAM_LBDQ_BADDR_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_LBDQ_BADDR_OFFSET)
HI_SET_GET(hi_psam_lbdq_baddr_lbdq_addr,lbdq_addr,HI_PSAM_LBDQ_BADDR_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_LBDQ_BADDR_OFFSET)
HI_SET_GET(hi_psam_lbdq_size_lbdq_size,lbdq_size,HI_PSAM_LBDQ_SIZE_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_LBDQ_SIZE_OFFSET)
HI_SET_GET(hi_psam_lbdq_size_reserved,reserved,HI_PSAM_LBDQ_SIZE_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_LBDQ_SIZE_OFFSET)
HI_SET_GET(hi_psam_lbdq_wptr_lbdq_wptr,lbdq_wptr,HI_PSAM_LBDQ_WPTR_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_LBDQ_WPTR_OFFSET)
HI_SET_GET(hi_psam_lbdq_wptr_reserved,reserved,HI_PSAM_LBDQ_WPTR_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_LBDQ_WPTR_OFFSET)
HI_SET_GET(hi_psam_lbdq_rptr_real_lbdq_rptr,real_lbdq_rptr,HI_PSAM_LBDQ_RPTR_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_LBDQ_RPTR_OFFSET)
HI_SET_GET(hi_psam_lbdq_rptr_reserved,reserved,HI_PSAM_LBDQ_RPTR_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_LBDQ_RPTR_OFFSET)
HI_SET_GET(hi_psam_lbdq_depth_lbdq_depth,lbdq_depth,HI_PSAM_LBDQ_DEPTH_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_LBDQ_DEPTH_OFFSET)
HI_SET_GET(hi_psam_lbdq_depth_reserved,reserved,HI_PSAM_LBDQ_DEPTH_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_LBDQ_DEPTH_OFFSET)
HI_SET_GET(hi_psam_adq_ctrl_reserved_1,reserved_1,HI_PSAM_ADQ_CTRL_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_ADQ_CTRL_OFFSET)
HI_SET_GET(hi_psam_adq_ctrl_adq_en,adq_en,HI_PSAM_ADQ_CTRL_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_ADQ_CTRL_OFFSET)
HI_SET_GET(hi_psam_adq_ctrl_adq0_size_sel,adq0_size_sel,HI_PSAM_ADQ_CTRL_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_ADQ_CTRL_OFFSET)
HI_SET_GET(hi_psam_adq_ctrl_adq1_size_sel,adq1_size_sel,HI_PSAM_ADQ_CTRL_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_ADQ_CTRL_OFFSET)
HI_SET_GET(hi_psam_adq_ctrl_reserved_0,reserved_0,HI_PSAM_ADQ_CTRL_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_ADQ_CTRL_OFFSET)
HI_SET_GET(hi_psam_adq_ctrl_adq_plen_th,adq_plen_th,HI_PSAM_ADQ_CTRL_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_ADQ_CTRL_OFFSET)
HI_SET_GET(hi_psam_adq0_base_reserved,reserved,HI_PSAM_ADQ0_BASE_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_ADQ0_BASE_OFFSET)
HI_SET_GET(hi_psam_adq0_base_adq0_base,adq0_base,HI_PSAM_ADQ0_BASE_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_ADQ0_BASE_OFFSET)
HI_SET_GET(hi_psam_adq0_stat_adq0_epty,adq0_epty,HI_PSAM_ADQ0_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_ADQ0_STAT_OFFSET)
HI_SET_GET(hi_psam_adq0_stat_adq0_full,adq0_full,HI_PSAM_ADQ0_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_ADQ0_STAT_OFFSET)
HI_SET_GET(hi_psam_adq0_stat_ad0_buf_epty,ad0_buf_epty,HI_PSAM_ADQ0_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_ADQ0_STAT_OFFSET)
HI_SET_GET(hi_psam_adq0_stat_ad0_buf_full,ad0_buf_full,HI_PSAM_ADQ0_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_ADQ0_STAT_OFFSET)
HI_SET_GET(hi_psam_adq0_stat_adq0_rptr_invalid,adq0_rptr_invalid,HI_PSAM_ADQ0_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_ADQ0_STAT_OFFSET)
HI_SET_GET(hi_psam_adq0_stat_adq0_wptr_invalid,adq0_wptr_invalid,HI_PSAM_ADQ0_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_ADQ0_STAT_OFFSET)
HI_SET_GET(hi_psam_adq0_stat_reserved,reserved,HI_PSAM_ADQ0_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_ADQ0_STAT_OFFSET)
HI_SET_GET(hi_psam_adq0_wptr_adq0_wptr,adq0_wptr,HI_PSAM_ADQ0_WPTR_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_ADQ0_WPTR_OFFSET)
HI_SET_GET(hi_psam_adq0_wptr_reserved,reserved,HI_PSAM_ADQ0_WPTR_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_ADQ0_WPTR_OFFSET)
HI_SET_GET(hi_psam_adq0_rptr_adq0_rptr,adq0_rptr,HI_PSAM_ADQ0_RPTR_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_ADQ0_RPTR_OFFSET)
HI_SET_GET(hi_psam_adq0_rptr_reserved,reserved,HI_PSAM_ADQ0_RPTR_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_ADQ0_RPTR_OFFSET)
HI_SET_GET(hi_psam_adq1_base_reserved,reserved,HI_PSAM_ADQ1_BASE_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_ADQ1_BASE_OFFSET)
HI_SET_GET(hi_psam_adq1_base_adq1_base,adq1_base,HI_PSAM_ADQ1_BASE_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_ADQ1_BASE_OFFSET)
HI_SET_GET(hi_psam_adq1_stat_adq1_epty,adq1_epty,HI_PSAM_ADQ1_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_ADQ1_STAT_OFFSET)
HI_SET_GET(hi_psam_adq1_stat_adq1_full,adq1_full,HI_PSAM_ADQ1_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_ADQ1_STAT_OFFSET)
HI_SET_GET(hi_psam_adq1_stat_ad1_buf_epty,ad1_buf_epty,HI_PSAM_ADQ1_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_ADQ1_STAT_OFFSET)
HI_SET_GET(hi_psam_adq1_stat_ad1_buf_full,ad1_buf_full,HI_PSAM_ADQ1_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_ADQ1_STAT_OFFSET)
HI_SET_GET(hi_psam_adq1_stat_adq1_rptr_invalid,adq1_rptr_invalid,HI_PSAM_ADQ1_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_ADQ1_STAT_OFFSET)
HI_SET_GET(hi_psam_adq1_stat_adq1_wptr_invalid,adq1_wptr_invalid,HI_PSAM_ADQ1_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_ADQ1_STAT_OFFSET)
HI_SET_GET(hi_psam_adq1_stat_reserved,reserved,HI_PSAM_ADQ1_STAT_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_ADQ1_STAT_OFFSET)
HI_SET_GET(hi_psam_adq1_wptr_adq1_wptr,adq1_wptr,HI_PSAM_ADQ1_WPTR_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_ADQ1_WPTR_OFFSET)
HI_SET_GET(hi_psam_adq1_wptr_reserved,reserved,HI_PSAM_ADQ1_WPTR_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_ADQ1_WPTR_OFFSET)
HI_SET_GET(hi_psam_adq1_rptr_adq1_rptr,adq1_rptr,HI_PSAM_ADQ1_RPTR_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_ADQ1_RPTR_OFFSET)
HI_SET_GET(hi_psam_adq1_rptr_reserved,reserved,HI_PSAM_ADQ1_RPTR_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_ADQ1_RPTR_OFFSET)
HI_SET_GET(hi_psam_crdq_baddr_psam_crdq_baddr,psam_crdq_baddr,HI_PSAM_CRDQ_BADDR_T,HI_REG_DESIGN_BASE_ADDR, HI_PSAM_CRDQ_BADDR_OFFSET)
#endif
#endif

#endif // __HI_PSAM_H__

