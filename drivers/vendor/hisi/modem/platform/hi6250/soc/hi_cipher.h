/******************************************************************************/
/*  Copyright (C), 2007-2014, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name     : hi_cipher.h */
/* Version       : 2.0 */
/* Author        : xxx*/
/* Created       : 2014-10-16*/
/* Last Modified : */
/* Description   :  The C union definition file for the module cipher*/
/* Function List : */
/* History       : */
/* 1 Date        : */
/* Author        : xxx*/
/* Modification  : Create file */
/******************************************************************************/

#ifndef __HI_CIPHER_H__
#define __HI_CIPHER_H__

/*
 * Project: hi
 * Module : cipher
 */
#if 0
#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4)
#endif
#endif
/********************************************************************************/
/*    cipher 寄存器偏移定义（项目名_模块名_寄存器名_OFFSET)        */
/********************************************************************************/
#define    HI_CIPHER_CTRL_OFFSET                             (0x0) /* CIPHER模块控制寄存器 */
#define    HI_CIPHER_PRI_OFFSET                              (0x4) /* CIPHER优先级控制寄存器。 */
#define    HI_TOTAL_BD_NUM_OFFSET                            (0x8) /* 总BD个数 */
#define    HI_INVALID_BD_NUM_OFFSET                          (0xC) /* 非法BD个数 */
#define    HI_DMA_CFG_OFFSET                                 (0x14) /* dma配置寄存器 */
#define    HI_CIPHER_VERSION_OFFSET                          (0x18) /* cipher版本寄存器 */
#define    HI_TEST_REG0_OFFSET                               (0x20) /* 调试寄存器 */
#define    HI_TEST_REG1_OFFSET                               (0x24) /* 调试寄存器 */
#define    HI_TEST_REG2_OFFSET                               (0x28) /* 调试寄存器 */
#define    HI_CIPHER_DEBUG20_OFFSET                          (0x2C) /* debug寄存器 */
#define    HI_CIPHER_DEBUG0_OFFSET                           (0x30) /* debug寄存器 */
#define    HI_CIPHER_DEBUG1_OFFSET                           (0x34) /* debug寄存器 */
#define    HI_CIPHER_DEBUG2_OFFSET                           (0x38) /* debug寄存器 */
#define    HI_CIPHER_DEBUG3_OFFSET                           (0x3C) /* debug寄存器 */
#define    HI_CIPHER_DEBUG4_OFFSET                           (0x40) /* debug寄存器 */
#define    HI_CIPHER_DEBUG5_OFFSET                           (0x44) /* debug寄存器 */
#define    HI_CIPHER_DEBUG6_OFFSET                           (0x48) /* debug寄存器 */
#define    HI_CIPHER_DEBUG7_OFFSET                           (0x4C) /* debug寄存器 */
#define    HI_CIPHER_DEBUG8_OFFSET                           (0x50) /* debug寄存器 */
#define    HI_CIPHER_DEBUG9_OFFSET                           (0x54) /* debug寄存器 */
#define    HI_CIPHER_DEBUG10_OFFSET                          (0x58) /* debug寄存器 */
#define    HI_CIPHER_DEBUG11_OFFSET                          (0x5C) /* debug寄存器 */
#define    HI_CIPHER_DEBUG12_OFFSET                          (0x60) /* debug寄存器 */
#define    HI_CIPHER_DEBUG13_OFFSET                          (0x64) /* debug寄存器 */
#define    HI_CIPHER_DEBUG14_OFFSET                          (0x68) /* debug寄存器 */
#define    HI_CIPHER_DEBUG15_OFFSET                          (0x6C) /* debug寄存器 */
#define    HI_CIPHER_DEBUG16_OFFSET                          (0x70) /* debug寄存器 */
#define    HI_CIPHER_DEBUG17_OFFSET                          (0x74) /* debug寄存器 */
#define    HI_CIPHER_DEBUG18_OFFSET                          (0x78) /* debug寄存器 */
#define    HI_CIPHER_DEBUG19_OFFSET                          (0x7C) /* debug寄存器 */
#define    HI_CH0_SOFTRESET_OFFSET                           (0x80) /* 通道0软复位寄存器 */
#define    HI_CH0_EN_OFFSET                                  (0x84) /* 通道0使能寄存器 */
#define    HI_CH0_CONFIG_OFFSET                              (0x88) /* 通道0配置寄存器 */
#define    HI_CH0_BDQ_BADDR_OFFSET                           (0x8C) /* 通道0 BDQ基地址寄存器 */
#define    HI_CH0_BDQ_SIZE_OFFSET                            (0x90) /* 通道0 BDQ大小寄存器 */
#define    HI_CH0_BDQ_PTR_OFFSET                             (0x94) /* 通道0 BDQ读写指针寄存器。 */
#define    HI_CH0_BDQ_RADDR_OFFSET                           (0x98) /* 通道0 BDQ读地址寄存器。 */
#define    HI_CH0_BDQ_WADDR_OFFSET                           (0x9C) /* 通道0 BDQ写地址寄存器。 */
#define    HI_CH0_BD_NUM_OFFSET                              (0xA0) /* 表示通道0处理的BD总数 */
#define    HI_CH0_INVALID_BD_NUM_OFFSET                      (0xA4) /* 表示通道0处理的无效BD数 */
#define    HI_CH1_SOFTRESET_OFFSET                           (0x100) /* 通道1软复位寄存器 */
#define    HI_CH1_EN_OFFSET                                  (0x104) /* 通道1使能寄存器 */
#define    HI_CH1_CONFIG_OFFSET                              (0x108) /* 通道1配置寄存器 */
#define    HI_CH1_BDQ_BADDR_OFFSET                           (0x10C) /* 通道1 BDQ基地址寄存器 */
#define    HI_CH1_BDQ_SIZE_OFFSET                            (0x110) /* 通道1 BDQ大小寄存器 */
#define    HI_CH1_BDQ_PTR_OFFSET                             (0x114) /* 通道1 BDQ读写指针寄存器。 */
#define    HI_CH1_BDQ_RADDR_OFFSET                           (0x118) /* 通道1 BDQ读地址寄存器。 */
#define    HI_CH1_BDQ_WADDR_OFFSET                           (0x11C) /* 通道1 BDQ写地址寄存器。 */
#define    HI_CH1_BD_NUM_OFFSET                              (0x120) /* 表示通道1处理的BD总数 */
#define    HI_CH1_INVALID_BD_NUM_OFFSET                      (0x124) /* 表示通道1处理的无效BD数 */
#define    HI_CH2_SOFTRESET_OFFSET                           (0x180) /* 通道2软复位寄存器 */
#define    HI_CH2_EN_OFFSET                                  (0x184) /* 通道2使能寄存器 */
#define    HI_CH2_CONFIG_OFFSET                              (0x188) /* 通道2配置寄存器 */
#define    HI_CH2_BDQ_BADDR_OFFSET                           (0x18C) /* 通道2 BDQ基地址寄存器 */
#define    HI_CH2_BDQ_SIZE_OFFSET                            (0x190) /* 通道2 BDQ大小寄存器 */
#define    HI_CH2_BDQ_PTR_OFFSET                             (0x194) /* 通道2 BDQ读写指针寄存器。 */
#define    HI_CH2_BDQ_RADDR_OFFSET                           (0x198) /* 通道2 BDQ读地址寄存器。 */
#define    HI_CH2_BDQ_WADDR_OFFSET                           (0x19C) /* 通道2 BDQ写地址寄存器。 */
#define    HI_CH2_BD_NUM_OFFSET                              (0x1A0) /* 表示通道1处理的BD总数 */
#define    HI_CH2_INVALID_BD_NUM_OFFSET                      (0x1A4) /* 表示通道1处理的无效BD数 */
#define    HI_CH3_SOFTRESET_OFFSET                           (0x200) /* 通道3软复位寄存器 */
#define    HI_CH3_EN_OFFSET                                  (0x204) /* 通道3使能寄存器 */
#define    HI_CH3_CONFIG_OFFSET                              (0x208) /* 通道3配置寄存器 */
#define    HI_CH3_BDQ_BADDR_OFFSET                           (0x20C) /* 通道3 BDQ基地址寄存器 */
#define    HI_CH3_BDQ_SIZE_OFFSET                            (0x210) /* 通道3 BDQ大小寄存器 */
#define    HI_CH3_BDQ_PTR_OFFSET                             (0x214) /* 通道3 BDQ读写指针寄存器。 */
#define    HI_CH3_BDQ_RADDR_OFFSET                           (0x218) /* 通道3 BDQ读地址寄存器。 */
#define    HI_CH3_BDQ_WADDR_OFFSET                           (0x21C) /* 通道3 BDQ写地址寄存器。 */
#define    HI_CH3_BD_NUM_OFFSET                              (0x220) /* 表示通道3处理的BD总数 */
#define    HI_CH3_INVALID_BD_NUM_OFFSET                      (0x224) /* 表示通道3处理的无效BD数 */
#define    HI_CH4_SOFTRESET_OFFSET                           (0x280) /* 通道4软复位寄存器 */
#define    HI_CH4_EN_OFFSET                                  (0x284) /* 通道4使能寄存器 */
#define    HI_CH4_CONFIG_OFFSET                              (0x288) /* 通道4配置寄存器 */
#define    HI_CH4_BDQ_BADDR_OFFSET                           (0x28C) /* 通道4 BDQ基地址寄存器 */
#define    HI_CH4_BDQ_SIZE_OFFSET                            (0x290) /* 通道4 BDQ大小寄存器 */
#define    HI_CH4_BDQ_PTR_OFFSET                             (0x294) /* 通道4 BDQ读写指针寄存器。 */
#define    HI_CH4_BDQ_RADDR_OFFSET                           (0x298) /* 通道4 BDQ读地址寄存器。 */
#define    HI_CH4_BDQ_WADDR_OFFSET                           (0x29C) /* 通道4 BDQ写地址寄存器。 */
#define    HI_CH4_BD_NUM_OFFSET                              (0x2A0) /* 表示通道4处理的BD总数 */
#define    HI_CH4_INVALID_BD_NUM_OFFSET                      (0x2A4) /* 表示通道4处理的无效BD数 */
#define    HI_CH5_SOFTRESET_OFFSET                           (0x300) /* 通道5软复位寄存器 */
#define    HI_CH5_EN_OFFSET                                  (0x304) /* 通道5使能寄存器 */
#define    HI_CH5_CONFIG_OFFSET                              (0x308) /* 通道5配置寄存器 */
#define    HI_CH5_BDQ_BADDR_OFFSET                           (0x30C) /* 通道5 BDQ基地址寄存器 */
#define    HI_CH5_BDQ_SIZE_OFFSET                            (0x310) /* 通道5 BDQ大小寄存器 */
#define    HI_CH5_BDQ_PTR_OFFSET                             (0x314) /* 通道5 BDQ读写指针寄存器。 */
#define    HI_CH5_BDQ_RADDR_OFFSET                           (0x318) /* 通道5 BDQ读地址寄存器。 */
#define    HI_CH5_BDQ_WADDR_OFFSET                           (0x31C) /* 通道5 BDQ写地址寄存器。 */
#define    HI_CH5_BD_NUM_OFFSET                              (0x320) /* 表示通道5处理的BD总数 */
#define    HI_CH5_INVALID_BD_NUM_OFFSET                      (0x324) /* 表示通道5处理的无效BD数 */
#define    HI_CH6_SOFTRESET_OFFSET                           (0x380) /* 通道6软复位寄存器 */
#define    HI_CH6_EN_OFFSET                                  (0x384) /* 通道6使能寄存器 */
#define    HI_CH6_CONFIG_OFFSET                              (0x388) /* 通道6配置寄存器 */
#define    HI_CH6_BDQ_BADDR_OFFSET                           (0x38C) /* 通道6 BDQ基地址寄存器 */
#define    HI_CH6_BDQ_SIZE_OFFSET                            (0x390) /* 通道6 BDQ大小寄存器 */
#define    HI_CH6_BDQ_PTR_OFFSET                             (0x394) /* 通道6 BDQ读写指针寄存器。 */
#define    HI_CH6_BDQ_RADDR_OFFSET                           (0x398) /* 通道6 BDQ读地址寄存器。 */
#define    HI_CH6_BDQ_WADDR_OFFSET                           (0x39C) /* 通道6 BDQ写地址寄存器。 */
#define    HI_CH6_BD_NUM_OFFSET                              (0x3A0) /* 表示通道6处理的BD总数 */
#define    HI_CH6_INVALID_BD_NUM_OFFSET                      (0x3A4) /* 表示通道6处理的无效BD数 */
#define    HI_CH_INT_PKT_INTERVAL_OFFSET                     (0x400) /* 中断包间隔寄存器 */
#define    HI_CIPHER_INT_STATUS_OFFSET                       (0x404) /* cipher中断状态寄存器 */
#define    HI_CIPHER_INT0_STATUS_OFFSET                      (0x408) /* cipher中断寄存器0 */
#define    HI_CIPHER_INT0_MASK_OFFSET                        (0x40C) /* cipher中断屏蔽寄存器0 */
#define    HI_CIPHER_INT0_MSTATUS_OFFSET                     (0x410) /* cipher经过屏蔽之后的中断状态寄存器0 */
#define    HI_CIPHER_INT1_STATUS_OFFSET                      (0x414) /* cipher中断寄存器1 */
#define    HI_CIPHER_INT1_MASK_OFFSET                        (0x418) /* cipher中断屏蔽寄存器1 */
#define    HI_CIPHER_INT1_MSTATUS_OFFSET                     (0x41C) /* cipher经过屏蔽之后的中断状态寄存器1 */
#define    HI_CIPHER_INT2_STATUS_OFFSET                      (0x420) /* cipher中断寄存器2 */
#define    HI_CIPHER_INT2_MASK_OFFSET                        (0x424) /* cipher中断屏蔽寄存器2 */
#define    HI_CIPHER_INT2_MSTATUS_OFFSET                     (0x428) /* cipher经过屏蔽之后的中断状态寄存器2 */
#define    HI_CIPHER_DEBUG21_OFFSET                          (0x42C) /* RD_ADDR */
#define    HI_CIPHER_DEBUG22_OFFSET                          (0x430) /* ICD_ADDR */
#define    HI_CIPHER_DEBUG23_OFFSET                          (0x434) /* OCD_ADDR */
#define    HI_CIPHER_DEBUG24_OFFSET                          (0x438) /* IBUF_ADDR */
#define    HI_CIPHER_DEBUG25_OFFSET                          (0x43C) /* OBUF1_ADDR */
#define    HI_CIPHER_DEBUG26_OFFSET                          (0x440) /* OBUF2_ADDR */
#define    HI_CIPHER_INT3_STATUS_OFFSET                      (0x444) /* cipher中断寄存器3 */
#define    HI_CIPHER_INT3_MASK_OFFSET                        (0x448) /* cipher中断屏蔽寄存器3 */
#define    HI_CIPHER_INT3_MSTATUS_OFFSET                     (0x44C) /* cipher经过屏蔽之后的中断状态寄存器3 */
#define    HI_CIPHER_INT4_STATUS_OFFSET                      (0x450) /* cipher中断寄存器4 */
#define    HI_CIPHER_INT4_MASK_OFFSET                        (0x454) /* cipher中断屏蔽寄存器4 */
#define    HI_CIPHER_INT4_MSTATUS_OFFSET                     (0x458) /* cipher经过屏蔽之后的中断状态寄存器4 */
#define    HI_TIMEOUT_OFFSET                                 (0x45C) /* 中断包间隔寄存器 */
#define    HI_CH0_RDQ_BADDR_OFFSET                           (0x480) /* 通道0 RD队列基地址 */
#define    HI_CH0_RDQ_SIZE_OFFSET                            (0x484) /* 通道0 RD队列大小 */
#define    HI_CH0_RDQ_PTR_OFFSET                             (0x488) /* 通道0 RD队列的读写指针 */
#define    HI_CH0_RDQ_RADDR_OFFSET                           (0x48C) /* 通道0 RD队列的读地址 */
#define    HI_CH0_RDQ_WADDR_OFFSET                           (0x490) /* 通道0 RD队列的写地址 */
#define    HI_CH1_RDQ_BADDR_OFFSET                           (0x500) /* 通道1 RD队列基地址 */
#define    HI_CH1_RDQ_SIZE_OFFSET                            (0x504) /* 通道1 RD队列大小 */
#define    HI_CH1_RDQ_PTR_OFFSET                             (0x508) /* 通道1 RD队列的读写指针 */
#define    HI_CH1_RDQ_RADDR_OFFSET                           (0x50C) /* 通道1 RD队列的读地址 */
#define    HI_CH1_RDQ_WADDR_OFFSET                           (0x510) /* 通道1 RD队列的写地址 */
#define    HI_CH2_RDQ_BADDR_OFFSET                           (0x580) /* 通道2 RD队列基地址 */
#define    HI_CH2_RDQ_SIZE_OFFSET                            (0x584) /* 通道2 RD队列大小 */
#define    HI_CH2_RDQ_PTR_OFFSET                             (0x588) /* 通道2 RD队列的读写指针 */
#define    HI_CH2_RDQ_RADDR_OFFSET                           (0x58C) /* 通道2 RD队列的读地址 */
#define    HI_CH2_RDQ_WADDR_OFFSET                           (0x590) /* 通道2 RD队列的写地址 */
#define    HI_CH3_RDQ_BADDR_OFFSET                           (0x600) /* 通道3 RD队列基地址 */
#define    HI_CH3_RDQ_SIZE_OFFSET                            (0x604) /* 通道3 RD队列大小 */
#define    HI_CH3_RDQ_PTR_OFFSET                             (0x608) /* 通道3 RD队列的读写指针 */
#define    HI_CH3_RDQ_RADDR_OFFSET                           (0x60C) /* 通道3 RD队列的读地址 */
#define    HI_CH3_RDQ_WADDR_OFFSET                           (0x610) /* 通道3 RD队列的写地址 */
#define    HI_CH4_RDQ_BADDR_OFFSET                           (0x680) /* 通道4 RD队列基地址 */
#define    HI_CH4_RDQ_SIZE_OFFSET                            (0x684) /* 通道4 RD队列大小 */
#define    HI_CH4_RDQ_PTR_OFFSET                             (0x688) /* 通道4 RD队列的读写指针 */
#define    HI_CH4_RDQ_RADDR_OFFSET                           (0x68C) /* 通道4 RD队列的读地址 */
#define    HI_CH4_RDQ_WADDR_OFFSET                           (0x690) /* 通道4 RD队列的写地址 */
#define    HI_CH5_RDQ_BADDR_OFFSET                           (0x700) /* 通道5 RD队列基地址 */
#define    HI_CH5_RDQ_SIZE_OFFSET                            (0x704) /* 通道5 RD队列大小 */
#define    HI_CH5_RDQ_PTR_OFFSET                             (0x708) /* 通道5 RD队列的读写指针 */
#define    HI_CH5_RDQ_RADDR_OFFSET                           (0x70C) /* 通道5 RD队列的读地址 */
#define    HI_CH5_RDQ_WADDR_OFFSET                           (0x710) /* 通道5 RD队列的写地址 */
#define    HI_CH6_RDQ_BADDR_OFFSET                           (0x780) /* 通道6 RD队列基地址 */
#define    HI_CH6_RDQ_SIZE_OFFSET                            (0x784) /* 通道6 RD队列大小 */
#define    HI_CH6_RDQ_PTR_OFFSET                             (0x788) /* 通道6 RD队列的读写指针 */
#define    HI_CH6_RDQ_RADDR_OFFSET                           (0x78C) /* 通道6 RD队列的读地址 */
#define    HI_CH6_RDQ_WADDR_OFFSET                           (0x790) /* 通道6 RD队列的写地址 */
#define    HI_KEY_RAM_OFFSET                                 (0x800) /* cipher内部的key ram */

/********************************************************************************/
/*    cipher 寄存器定义（项目名_模块名_寄存器名_T)        */
/********************************************************************************/
typedef union
{
    struct
    {
        unsigned int    cipher_srst                : 1; /* [0..0] cipher模块复位。写1复位cipher模块，若此时cipher占有总线，不能立即执行复位，直到cipher释放总线以后才开始复位，复位结束此寄存器自动归0。 */
        unsigned int    cipher_cg_en               : 1; /* [1..1] cipher自动时钟门控使能 */
        unsigned int    reserved                   : 29; /* [30..2] 保留。 */
        unsigned int    cipher_busy                : 1; /* [31..31] cipher模块忙标志。当5个命令通道的任何一个控制寄存器的忙标志为1，这个标志就为1。 */
    } bits;
    unsigned int    u32;
}HI_CIPHER_CTRL_T;    /* CIPHER模块控制寄存器 */

typedef union
{
    struct
    {
        unsigned int    ch0_pri                    : 3; /* [2..0] 通道0的优先级。 */
        unsigned int    reserved_5                 : 1; /* [3..3] 保留 */
        unsigned int    ch1_pri                    : 3; /* [6..4] 通道1的优先级。 */
        unsigned int    reserved_4                 : 1; /* [7..7] 保留 */
        unsigned int    ch2_pri                    : 3; /* [10..8] 通道2的优先级。 */
        unsigned int    reserved_3                 : 1; /* [11..11] 保留 */
        unsigned int    ch3_pri                    : 3; /* [14..12] 通道3的优先级。 */
        unsigned int    reserved_2                 : 5; /* [19..15] 保留 */
        unsigned int    ch5_pri                    : 3; /* [22..20] 通道5的优先级。 */
        unsigned int    reserved_1                 : 1; /* [23..23] 保留 */
        unsigned int    ch6_pri                    : 3; /* [26..24] 通道6的优先级。 */
        unsigned int    reserved_0                 : 5; /* [31..27] 数值越小，优先级越高。如果两个同样优先级的通道同时请求处理，cipher会随机选择一个处理，并且要等到当前通道BD队列处理完毕，才会处理相同优先级的另一个通道的BD。 */
    } bits;
    unsigned int    u32;
}HI_CIPHER_PRI_T;    /* CIPHER优先级控制寄存器。 */

typedef union
{
    struct
    {
        unsigned int    total_bd_num               : 32; /* [31..0] 表示cipher已经处理的BD总数（5个通道的总和）只读，可写清0 */
    } bits;
    unsigned int    u32;
}HI_TOTAL_BD_NUM_T;    /* 总BD个数 */

typedef union
{
    struct
    {
        unsigned int    invalid_bd_num             : 32; /* [31..0] 表示cipher收到的无效BD总数（5个通道的总和）只读，可写清0 */
    } bits;
    unsigned int    u32;
}HI_INVALID_BD_NUM_T;    /* 非法BD个数 */

typedef union
{
    struct
    {
        unsigned int    rd_id                      : 3; /* [2..0] RD回写通道的ID */
        unsigned int    obuf_id                    : 3; /* [5..3] OBUF写通道的ID */
        unsigned int    ocd_id                     : 3; /* [8..6] OCD读通道的ID */
        unsigned int    icd_id                     : 3; /* [11..9] ICD读通道的ID */
        unsigned int    ibuf_id                    : 3; /* [14..12] IBUF读通道的ID */
        unsigned int    reserved_1                 : 1; /* [15..15] 保留 */
        unsigned int    rd_pri                     : 3; /* [18..16] RD回写通道的优先级 */
        unsigned int    obuf_pri                   : 3; /* [21..19] OBUF写通道的优先级 */
        unsigned int    ocd_pri                    : 3; /* [24..22] OCD读通道的优先级 */
        unsigned int    icd_pri                    : 3; /* [27..25] ICD读通道的优先级 */
        unsigned int    ibuf_pri                   : 3; /* [30..28] IBUF读通道的优先级 */
        unsigned int    reserved_0                 : 1; /* [31..31] 保留 */
    } bits;
    unsigned int    u32;
}HI_DMA_CFG_T;    /* dma配置寄存器 */

typedef union
{
    struct
    {
        unsigned int    cipher_version             : 32; /* [31..0] hi6950v100 */
    } bits;
    unsigned int    u32;
}HI_CIPHER_VERSION_T;    /* cipher版本寄存器 */

typedef union
{
    struct
    {
        unsigned int    spram_mem_ctrl             : 16; /* [15..0] cipher内部spram的控制信号 */
        unsigned int    atpram_mem_ctrl            : 16; /* [31..16] cipher内部atpram的控制信号 */
    } bits;
    unsigned int    u32;
}HI_TEST_REG0_T;    /* 调试寄存器 */

typedef union
{
    struct
    {
        unsigned int    aes_key_cov                : 1; /* [0..0] aes运算时，是否需要颠倒key的字序1：表示需要颠倒字序；0：表示不需要颠倒字序。 */
        unsigned int    snow3g_key_cov             : 1; /* [1..1] snow3g运算时，是否需要颠倒key的字序1：表示需要颠倒字序；0：表示不需要颠倒字序。 */
        unsigned int    cipher_dma_ctrl            : 6; /* [7..2] 对于dma的控制信号：[5:4]：表示GM写方向的outstanding深度[3:2]：表示GM读方向的outstanding深度[1]： 1表示读outstanding使能，0表示读outstanding不使能 ；[0]： 1表示写outstanding使能，0表示写outstanding不使能。 */
        unsigned int    zuc_key_cov                : 1; /* [8..8] zuc运算时，是否需要颠倒key的字序1：表示需要颠倒字序；0：表示不需要颠倒字序。 */
        unsigned int    aes_iv_cov                 : 1; /* [9..9] aes运算时，是否需要颠倒iv的字序1：表示需要颠倒字序；0：表示不需要颠倒字序。 */
        unsigned int    snow3g_iv_cov              : 1; /* [10..10] snow3g运算时，是否需要颠倒iv的字序1：表示需要颠倒字序；0：表示不需要颠倒字序。 */
        unsigned int    zuc_iv_cov                 : 1; /* [11..11] zuc运算时，是否需要颠倒iv的字序1：表示需要颠倒字序；0：表示不需要颠倒字序。 */
        unsigned int    reserved_1                 : 4; /* [15..12]  */
        unsigned int    ibuf_dma_len               : 5; /* [20..16] ibuf发读数据请求最大长度限制                支持0~16                               若dma_opt=0，应设置ibuf_dma_req_len<=0x10；                 若dma_opt=1，为了防止AXI总线反压，建议设置ibuf_dma_req_len<=0x0A */
        unsigned int    dma_opt_en                 : 1; /* [21..21] dma优化使能控制位                      1：ibuf发outstanding读操作使能；       0：ibuf发outstanding读操作禁止。 */
        unsigned int    reserved_0                 : 10; /* [31..22] 保留 */
    } bits;
    unsigned int    u32;
}HI_TEST_REG1_T;    /* 调试寄存器 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] 调试寄存器。 */
    } bits;
    unsigned int    u32;
}HI_TEST_REG2_T;    /* 调试寄存器 */

typedef union
{
    struct
    {
        unsigned int    dma_rd_gnt                 : 1; /* [0..0] rd的dma请求被响应 */
        unsigned int    dma_ocd_gnt                : 1; /* [1..1] ocd的dma请求被响应 */
        unsigned int    dma_icd_gnt                : 1; /* [2..2] icd的dma请求被响应 */
        unsigned int    dma_obuf_gnt               : 1; /* [3..3] obuf的dma请求被响应 */
        unsigned int    dma_ibuf_gnt               : 1; /* [4..4] ibuf的dma请求被响应 */
        unsigned int    reserved_3                 : 3; /* [7..5]  */
        unsigned int    dma_rd_req                 : 1; /* [8..8] rd进行dma请求 */
        unsigned int    dma_ocd_req                : 1; /* [9..9] ocd进行dma请求 */
        unsigned int    dma_icd_req                : 1; /* [10..10] icd进行dma请求 */
        unsigned int    dma_obuf_req               : 1; /* [11..11] obuf进行dma请求 */
        unsigned int    dma_ibuf_req               : 1; /* [12..12] ibuf进行dma请求 */
        unsigned int    reserved_2                 : 3; /* [15..13]  */
        unsigned int    dma_rd_idle                : 1; /* [16..16] rd没有进行dma操作，现在处于空闲状态 */
        unsigned int    dma_ocd_idle               : 1; /* [17..17] ocd没有进行dma操作，现在处于空闲状态 */
        unsigned int    dma_icd_idle               : 1; /* [18..18] icd没有进行dma操作，现在处于空闲状态 */
        unsigned int    dma_obuf_idle              : 1; /* [19..19] obuf没有进行dma操作，现在处于空闲状态 */
        unsigned int    dma_ibuf_idle              : 1; /* [20..20] ibuf没有进行dma操作，现在处于空闲状态 */
        unsigned int    reserved_1                 : 3; /* [23..21]  */
        unsigned int    dma_rd_trans_end           : 1; /* [24..24] rd每次dma交易的最后一个数据 */
        unsigned int    dma_ocd_last_read          : 1; /* [25..25] ocd每次dma交易的最后一个数据 */
        unsigned int    dma_icd_last_read          : 1; /* [26..26] icd每次dma交易的最后一个数据 */
        unsigned int    dma_obuf_trans_end         : 1; /* [27..27] obuf每次dma交易的最后一个数据 */
        unsigned int    dma_ibuf_last_read         : 1; /* [28..28] ibuf每次dma交易的最后一个数据 */
        unsigned int    reserved_0                 : 3; /* [31..29] 保留 */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG20_T;    /* debug寄存器 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] bd_mem[0]: cipher_config */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG0_T;    /* debug寄存器 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] bd_mem[1]: ptr_attri, bd_in_len */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG1_T;    /* debug寄存器 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] bd_mem[2]: out_len, out_offset */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG2_T;    /* debug寄存器 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] bd_mem[3]: ptr_in */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG3_T;    /* debug寄存器 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] bd_mem[4]: ptr_out */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG4_T;    /* debug寄存器 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] bd_mem[5]: iv */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG5_T;    /* debug寄存器 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] bd_mem[6] */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG6_T;    /* debug寄存器 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] bd_mem[7] */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG7_T;    /* debug寄存器 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] bd_mem[8] */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG8_T;    /* debug寄存器 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] bd_mem[9] */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG9_T;    /* debug寄存器 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] bd_mem[10] */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG10_T;    /* debug寄存器 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] bd_mem[11] */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG11_T;    /* debug寄存器 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] bd_mem[12] */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG12_T;    /* debug寄存器 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] bd_mem[13] */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG13_T;    /* debug寄存器 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] bd_mem[14] */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG14_T;    /* debug寄存器 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] bd_mem[15] */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG15_T;    /* debug寄存器 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] bd_mem[16] */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG16_T;    /* debug寄存器 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] 7'b0,rd_wr_en,3'b0,bd_rcvd,3'b0,bd_rcvd_valid, 3'b0, kdf_end, 3'b0, cipher_end, 3'b0, rd_wr_end, 3'b0,pkt_in_end */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG17_T;    /* debug寄存器 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] total_o_len, total_i_len */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG18_T;    /* debug寄存器 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] 6'b0, kdf_o_len, 5'b0, kdf_i_len */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG19_T;    /* debug寄存器 */

typedef union
{
    struct
    {
        unsigned int    ch_srst                    : 1; /* [0..0] 写1复位通道，若此时通道占有总线，不能立即执行复位，直到本通道释放总线以后才开始复位，复位结束此寄存器自动归0。 */
        unsigned int    ch_bdq_clear               : 1; /* [1..1] 写1请求复位BD对列，若此时通道正busy，则等到当前BD处理完毕后，清空BD对列，同时该位自动归零。 */
        unsigned int    ch_rdq_clear               : 1; /* [2..2] 写1请求复位RD对列，若此时通道正busy，则等到当前BD处理完毕后，清空RD对列，同时该位自动归零。 */
        unsigned int    reserved                   : 29; /* [31..3] 域说明。 */
    } bits;
    unsigned int    u32;
}HI_CH0_SOFTRESET_T;    /* 通道0软复位寄存器 */

typedef union
{
    struct
    {
        unsigned int    ch_en                      : 1; /* [0..0] 1表示通道使能，0表示通道禁止。 */
        unsigned int    reserved                   : 29; /* [29..1]  */
        unsigned int    pack_en                    : 1; /* [30..30] 此寄存器初始值为1，当为1时，表示本次组包任务完成，可以开始下一次，否则表示本次组包任务正在进行。与配合软件配合过程如下：当cipher配合进行上行组包时，首先查询此寄存器，若为1，表示可以开始组包，软件将此bit置0，且软件把本次组包的最后一个BD中的gen_bd_int置为有效，当cipher完成这最后一个BD任务后，把此寄存器置为1，通知软件可以开始下一次组包任务。 */
        unsigned int    ch_busy                    : 1; /* [31..31] 1表示通道工作，0表示通道暂停。 */
    } bits;
    unsigned int    u32;
}HI_CH0_EN_T;    /* 通道0使能寄存器 */

typedef union
{
    struct
    {
        unsigned int    iv_sel                     : 1; /* [0..0] 本通道完整性参数、IV随BD还是都由芯片自动产生。0：完整性参数、IV由芯片根据参数自动产生；1：完整性参数、IV随包或随BD。 */
        unsigned int    iv_num                     : 1; /* [1..1] 本通道BD中含有的IV个数。只有当iv_sel为1时有意义。0：一个IV，此时BD长度固定是；1：两个IV，其中一个IV可以是无效IV，但仍需占用内存。 */
        unsigned int    rdq_ctrl                   : 2; /* [3..2] RDQ对列维护方式。当RDQ满且有需要回写的RD时，Cipher等待直到RDQ不满；00：不回写RD；01：每个BD都对应回写RD。others：RD是否回写由BD配置决定，只在BD中的gen_rd_en有效时回写RD。 */
        unsigned int    reserved_1                 : 1; /* [4..4] 保留。 */
        unsigned int    ufield_len                 : 2; /* [6..5] BD中userfield字段的长度，单位是32bit。 */
        unsigned int    reserved_0                 : 25; /* [31..7] 保留。 */
    } bits;
    unsigned int    u32;
}HI_CH0_CONFIG_T;    /* 通道0配置寄存器 */

typedef union
{
    struct
    {
        unsigned int    base_addr_l                : 3; /* [2..0] 通道0 BD队列基地址低3bit，固定为0。即要求基址64位对齐。 */
        unsigned int    base_addr                  : 29; /* [31..3] 通道0 BD队列基地址高29位 */
    } bits;
    unsigned int    u32;
}HI_CH0_BDQ_BADDR_T;    /* 通道0 BDQ基地址寄存器 */

typedef union
{
    struct
    {
        unsigned int    size                       : 10; /* [9..0] 通道0 BD Queue大小，以描述符个数为单位。0：表示队列大小为11023：表示队列大小为1024 */
        unsigned int    reserved                   : 22; /* [31..10] 成员说明。 */
    } bits;
    unsigned int    u32;
}HI_CH0_BDQ_SIZE_T;    /* 通道0 BDQ大小寄存器 */

typedef union
{
    struct
    {
        unsigned int    wptr                       : 10; /* [9..0] BD队列写指针。可被软复位 */
        unsigned int    reserved_1                 : 6; /* [15..10] 保留 */
        unsigned int    rptr                       : 10; /* [25..16] BD队列读指针。可被软复位。 */
        unsigned int    reserved_0                 : 4; /* [29..26] 保留 */
        unsigned int    ch_bdq_empty               : 1; /* [30..30] BD队列空 */
        unsigned int    ch_bdq_full                : 1; /* [31..31] BD队列满 */
    } bits;
    unsigned int    u32;
}HI_CH0_BDQ_PTR_T;    /* 通道0 BDQ读写指针寄存器。 */

typedef union
{
    struct
    {
        unsigned int    addr                       : 32; /* [31..0] 通道0 BD队列读地址。可被软复位 */
    } bits;
    unsigned int    u32;
}HI_CH0_BDQ_RADDR_T;    /* 通道0 BDQ读地址寄存器。 */

typedef union
{
    struct
    {
        unsigned int    addr                       : 32; /* [31..0] 通道0 BD队列写地址。可被软复位 */
    } bits;
    unsigned int    u32;
}HI_CH0_BDQ_WADDR_T;    /* 通道0 BDQ写地址寄存器。 */

typedef union
{
    struct
    {
        unsigned int    ch0_bd_num                 : 32; /* [31..0] 表示通道0已经处理的BD总数可以写清零 */
    } bits;
    unsigned int    u32;
}HI_CH0_BD_NUM_T;    /* 表示通道0处理的BD总数 */

typedef union
{
    struct
    {
        unsigned int    ch0_invalid_bd_num         : 32; /* [31..0] 表示通道0已经处理的无效BD总数可以写清零 */
    } bits;
    unsigned int    u32;
}HI_CH0_INVALID_BD_NUM_T;    /* 表示通道0处理的无效BD数 */

typedef union
{
    struct
    {
        unsigned int    ch_srst                    : 1; /* [0..0] 写1复位通道，若此时通道占有总线，不能立即执行复位，直到本通道释放总线以后才开始复位，复位结束此寄存器自动归0。 */
        unsigned int    ch_bdq_clear               : 1; /* [1..1] 写1请求复位BD对列，若此时通道正busy，则等到当前BD处理完毕后，清空BD对列，同时该位自动归零。 */
        unsigned int    ch_rdq_clear               : 1; /* [2..2] 写1请求复位RD对列，若此时通道正busy，则等到当前BD处理完毕后，清空RD对列，同时该位自动归零。 */
        unsigned int    reserved                   : 29; /* [31..3] 域说明。 */
    } bits;
    unsigned int    u32;
}HI_CH1_SOFTRESET_T;    /* 通道1软复位寄存器 */

typedef union
{
    struct
    {
        unsigned int    ch_en                      : 1; /* [0..0] 1表示通道使能，0表示通道禁止。 */
        unsigned int    reserved                   : 29; /* [29..1]  */
        unsigned int    pack_en                    : 1; /* [30..30] 此寄存器初始值为1，当为1时，表示本次组包任务完成，可以开始下一次，否则表示本次组包任务正在进行。与配合软件配合过程如下：当cipher配合进行上行组包时，首先查询此寄存器，若为1，表示可以开始组包，软件将此bit置0，且软件把本次组包的最后一个BD中的gen_bd_int置为有效，当cipher完成这最后一个BD任务后，把此寄存器置为1，通知软件可以开始下一次组包任务。 */
        unsigned int    ch_busy                    : 1; /* [31..31] 1表示通道工作，0表示通道暂停。 */
    } bits;
    unsigned int    u32;
}HI_CH1_EN_T;    /* 通道1使能寄存器 */

typedef union
{
    struct
    {
        unsigned int    iv_sel                     : 1; /* [0..0] 本通道完整性参数、IV随BD还是都由芯片自动产生。0：完整性参数、IV由芯片根据参数自动产生；1：完整性参数、IV随包或随BD。 */
        unsigned int    iv_num                     : 1; /* [1..1] 本通道BD中含有的IV个数。只有当iv_sel为1时有意义。0：一个IV，此时BD长度固定是；1：两个IV，其中一个IV可以是无效IV，但仍需占用内存。 */
        unsigned int    rdq_ctrl                   : 2; /* [3..2] RDQ对列维护方式。当RDQ满且有需要回写的RD时，Cipher等待直到RDQ不满；00：不回写RD；01：每个BD都对应回写RD。others：RD是否回写由BD配置决定，只在BD中的gen_rd_en有效时回写RD。 */
        unsigned int    reserved_1                 : 1; /* [4..4] 保留。 */
        unsigned int    ufield_len                 : 2; /* [6..5] BD中userfield字段的长度，单位是32bit。 */
        unsigned int    reserved_0                 : 25; /* [31..7] 保留。 */
    } bits;
    unsigned int    u32;
}HI_CH1_CONFIG_T;    /* 通道1配置寄存器 */

typedef union
{
    struct
    {
        unsigned int    base_addr_l                : 3; /* [2..0] 通道0 BD队列基地址低3bit，固定为0。即要求基址64位对齐。 */
        unsigned int    base_addr                  : 29; /* [31..3] 通道1 BD队列基地址高29位 */
    } bits;
    unsigned int    u32;
}HI_CH1_BDQ_BADDR_T;    /* 通道1 BDQ基地址寄存器 */

typedef union
{
    struct
    {
        unsigned int    size                       : 10; /* [9..0] 通道0 BD Queue大小，以描述符个数为单位。0：表示队列大小为11023：表示队列大小为1024 */
        unsigned int    reserved                   : 22; /* [31..10] 成员说明。 */
    } bits;
    unsigned int    u32;
}HI_CH1_BDQ_SIZE_T;    /* 通道1 BDQ大小寄存器 */

typedef union
{
    struct
    {
        unsigned int    wptr                       : 10; /* [9..0] BD队列写指针。可被软复位 */
        unsigned int    reserved_1                 : 6; /* [15..10] 保留 */
        unsigned int    rptr                       : 10; /* [25..16] BD队列读指针。可被软复位。 */
        unsigned int    reserved_0                 : 4; /* [29..26] 保留 */
        unsigned int    ch1_bdq_empty              : 1; /* [30..30] B队列空 */
        unsigned int    ch1_bdq_full               : 1; /* [31..31] BD队列满 */
    } bits;
    unsigned int    u32;
}HI_CH1_BDQ_PTR_T;    /* 通道1 BDQ读写指针寄存器。 */

typedef union
{
    struct
    {
        unsigned int    addr                       : 32; /* [31..0] 通道1 BD队列读地址。可被软复位。 */
    } bits;
    unsigned int    u32;
}HI_CH1_BDQ_RADDR_T;    /* 通道1 BDQ读地址寄存器。 */

typedef union
{
    struct
    {
        unsigned int    addr                       : 32; /* [31..0] 通道1 BD队列写地址。可被软复位。 */
    } bits;
    unsigned int    u32;
}HI_CH1_BDQ_WADDR_T;    /* 通道1 BDQ写地址寄存器。 */

typedef union
{
    struct
    {
        unsigned int    ch1_bd_num                 : 32; /* [31..0] 表示通道1已经处理的BD总数只读，可以写清零 */
    } bits;
    unsigned int    u32;
}HI_CH1_BD_NUM_T;    /* 表示通道1处理的BD总数 */

typedef union
{
    struct
    {
        unsigned int    ch1_invalid_bd_num         : 32; /* [31..0] 表示通道1已经处理的无效BD总数只读，可以写清零 */
    } bits;
    unsigned int    u32;
}HI_CH1_INVALID_BD_NUM_T;    /* 表示通道1处理的无效BD数 */

typedef union
{
    struct
    {
        unsigned int    ch_srst                    : 1; /* [0..0] 写1复位通道，若此时通道占有总线，不能立即执行复位，直到本通道释放总线以后才开始复位，复位结束此寄存器自动归0。 */
        unsigned int    ch_bdq_clear               : 1; /* [1..1] 写1请求复位BD对列，若此时通道正busy，则等到当前BD处理完毕后，清空BD对列，同时该位自动归零。 */
        unsigned int    ch_rdq_clear               : 1; /* [2..2] 写1请求复位RD对列，若此时通道正busy，则等到当前BD处理完毕后，清空RD对列，同时该位自动归零。 */
        unsigned int    reserved                   : 29; /* [31..3] 域说明。 */
    } bits;
    unsigned int    u32;
}HI_CH2_SOFTRESET_T;    /* 通道2软复位寄存器 */

typedef union
{
    struct
    {
        unsigned int    ch_en                      : 1; /* [0..0] 1表示通道使能，0表示通道禁止。 */
        unsigned int    reserved                   : 29; /* [29..1]  */
        unsigned int    pack_en                    : 1; /* [30..30] 此寄存器初始值为1，当为1时，表示本次组包任务完成，可以开始下一次，否则表示本次组包任务正在进行。与配合软件配合过程如下：当cipher配合进行上行组包时，首先查询此寄存器，若为1，表示可以开始组包，软件将此bit置0，且软件把本次组包的最后一个BD中的gen_bd_int置为有效，当cipher完成这最后一个BD任务后，把此寄存器置为1，通知软件可以开始下一次组包任务。 */
        unsigned int    ch_busy                    : 1; /* [31..31] 1表示通道工作，0表示通道暂停。 */
    } bits;
    unsigned int    u32;
}HI_CH2_EN_T;    /* 通道2使能寄存器 */

typedef union
{
    struct
    {
        unsigned int    iv_sel                     : 1; /* [0..0] 本通道完整性参数、IV随BD还是都由芯片自动产生。0：完整性参数、IV由芯片根据参数自动产生；1：完整性参数、IV随包或随BD。 */
        unsigned int    iv_num                     : 1; /* [1..1] 本通道BD中含有的IV个数。只有当iv_sel为1时有意义。0：一个IV，此时BD长度固定是；1：两个IV，其中一个IV可以是无效IV，但仍需占用内存。 */
        unsigned int    rdq_ctrl                   : 2; /* [3..2] RDQ对列维护方式。当RDQ满且有需要回写的RD时，Cipher等待直到RDQ不满；00：不回写RD；01：每个BD都对应回写RD。others：RD是否回写由BD配置决定，只在BD中的gen_rd_en有效时回写RD。 */
        unsigned int    reserved_1                 : 1; /* [4..4] 保留。 */
        unsigned int    ufield_len                 : 2; /* [6..5] BD中userfield字段的长度，单位是32bit。 */
        unsigned int    reserved_0                 : 25; /* [31..7] 保留。 */
    } bits;
    unsigned int    u32;
}HI_CH2_CONFIG_T;    /* 通道2配置寄存器 */

typedef union
{
    struct
    {
        unsigned int    base_addr_l                : 3; /* [2..0] 通道0 BD队列基地址低3bit，固定为0。即要求基址64位对齐。 */
        unsigned int    base_addr                  : 29; /* [31..3] 通道2 BD队列基地址高29位 */
    } bits;
    unsigned int    u32;
}HI_CH2_BDQ_BADDR_T;    /* 通道2 BDQ基地址寄存器 */

typedef union
{
    struct
    {
        unsigned int    size                       : 10; /* [9..0] 通道0 BD Queue大小，以描述符个数为单位。0：表示队列大小为11023：表示队列大小为1024 */
        unsigned int    reserved                   : 22; /* [31..10] 成员说明。 */
    } bits;
    unsigned int    u32;
}HI_CH2_BDQ_SIZE_T;    /* 通道2 BDQ大小寄存器 */

typedef union
{
    struct
    {
        unsigned int    wptr                       : 10; /* [9..0] BD队列写指针。可被软复位 */
        unsigned int    reserved_1                 : 6; /* [15..10] 保留 */
        unsigned int    rptr                       : 10; /* [25..16] BD队列读指针。可被软复位。 */
        unsigned int    reserved_0                 : 4; /* [29..26] 保留 */
        unsigned int    ch2_bdq_empty              : 1; /* [30..30] BD队列空 */
        unsigned int    ch2_bdq_full               : 1; /* [31..31] BD队列满 */
    } bits;
    unsigned int    u32;
}HI_CH2_BDQ_PTR_T;    /* 通道2 BDQ读写指针寄存器。 */

typedef union
{
    struct
    {
        unsigned int    addr                       : 32; /* [31..0] 通道2 BD队列读地址。可被软复位 */
    } bits;
    unsigned int    u32;
}HI_CH2_BDQ_RADDR_T;    /* 通道2 BDQ读地址寄存器。 */

typedef union
{
    struct
    {
        unsigned int    addr                       : 32; /* [31..0] 通道2 BD队列写地址。可被软复位 */
    } bits;
    unsigned int    u32;
}HI_CH2_BDQ_WADDR_T;    /* 通道2 BDQ写地址寄存器。 */

typedef union
{
    struct
    {
        unsigned int    ch2_bd_num                 : 32; /* [31..0] 表示通道2已经处理的BD总数只读，可以写清零 */
    } bits;
    unsigned int    u32;
}HI_CH2_BD_NUM_T;    /* 表示通道1处理的BD总数 */

typedef union
{
    struct
    {
        unsigned int    ch2_invalid_bd_num         : 32; /* [31..0] 表示通道2已经处理的无效BD总数只读，可以写清零 */
    } bits;
    unsigned int    u32;
}HI_CH2_INVALID_BD_NUM_T;    /* 表示通道1处理的无效BD数 */

typedef union
{
    struct
    {
        unsigned int    ch_srst                    : 1; /* [0..0] 写1复位通道，若此时通道占有总线，不能立即执行复位，直到本通道释放总线以后才开始复位，复位结束此寄存器自动归0。 */
        unsigned int    ch_bdq_clear               : 1; /* [1..1] 写1请求复位BD对列，若此时通道正busy，则等到当前BD处理完毕后，清空BD对列，同时该位自动归零。 */
        unsigned int    ch_rdq_clear               : 1; /* [2..2] 写1请求复位RD对列，若此时通道正busy，则等到当前BD处理完毕后，清空RD对列，同时该位自动归零。 */
        unsigned int    reserved                   : 29; /* [31..3] 域说明。 */
    } bits;
    unsigned int    u32;
}HI_CH3_SOFTRESET_T;    /* 通道3软复位寄存器 */

typedef union
{
    struct
    {
        unsigned int    ch_en                      : 1; /* [0..0] 1表示通道使能，0表示通道禁止。 */
        unsigned int    reserved                   : 29; /* [29..1]  */
        unsigned int    pack_en                    : 1; /* [30..30] 此寄存器初始值为1，当为1时，表示本次组包任务完成，可以开始下一次，否则表示本次组包任务正在进行。与配合软件配合过程如下：当cipher配合进行上行组包时，首先查询此寄存器，若为1，表示可以开始组包，软件将此bit置0，且软件把本次组包的最后一个BD中的gen_bd_int置为有效，当cipher完成这最后一个BD任务后，把此寄存器置为1，通知软件可以开始下一次组包任务。 */
        unsigned int    ch_busy                    : 1; /* [31..31] 1表示通道工作，0表示通道暂停。 */
    } bits;
    unsigned int    u32;
}HI_CH3_EN_T;    /* 通道3使能寄存器 */

typedef union
{
    struct
    {
        unsigned int    iv_sel                     : 1; /* [0..0] 本通道完整性参数、IV随BD还是都由芯片自动产生。0：完整性参数、IV由芯片根据参数自动产生；1：完整性参数、IV随包或随BD。 */
        unsigned int    iv_num                     : 1; /* [1..1] 本通道BD中含有的IV个数。只有当iv_sel为1时有意义。0：一个IV，此时BD长度固定是；1：两个IV，其中一个IV可以是无效IV，但仍需占用内存。 */
        unsigned int    rdq_ctrl                   : 2; /* [3..2] RDQ对列维护方式。当RDQ满且有需要回写的RD时，Cipher等待直到RDQ不满；00：不回写RD；01：每个BD都对应回写RD。others：RD是否回写由BD配置决定，只在BD中的gen_rd_en有效时回写RD。 */
        unsigned int    reserved_1                 : 1; /* [4..4] 保留。 */
        unsigned int    ufield_len                 : 2; /* [6..5] BD中userfield字段的长度，单位是32bit。 */
        unsigned int    reserved_0                 : 25; /* [31..7] 保留。 */
    } bits;
    unsigned int    u32;
}HI_CH3_CONFIG_T;    /* 通道3配置寄存器 */

typedef union
{
    struct
    {
        unsigned int    base_addr_l                : 3; /* [2..0] 通道0 BD队列基地址低3bit，固定为0。即要求基址64位对齐。 */
        unsigned int    base_addr                  : 29; /* [31..3] 通道3 BD队列基地址高29位 */
    } bits;
    unsigned int    u32;
}HI_CH3_BDQ_BADDR_T;    /* 通道3 BDQ基地址寄存器 */

typedef union
{
    struct
    {
        unsigned int    size                       : 10; /* [9..0] 通道0 BD Queue大小，以描述符个数为单位。0：表示队列大小为11023：表示队列大小为1024 */
        unsigned int    reserved                   : 22; /* [31..10] 成员说明。 */
    } bits;
    unsigned int    u32;
}HI_CH3_BDQ_SIZE_T;    /* 通道3 BDQ大小寄存器 */

typedef union
{
    struct
    {
        unsigned int    wptr                       : 10; /* [9..0] BD队列写指针。可被软复位 */
        unsigned int    reserved_1                 : 6; /* [15..10] 保留 */
        unsigned int    rptr                       : 10; /* [25..16] BD队列读指针。可被软复位。 */
        unsigned int    reserved_0                 : 4; /* [29..26] 保留 */
        unsigned int    ch3_bdq_empty              : 1; /* [30..30] BD队列空 */
        unsigned int    ch3_bdq_full               : 1; /* [31..31] BD队列满 */
    } bits;
    unsigned int    u32;
}HI_CH3_BDQ_PTR_T;    /* 通道3 BDQ读写指针寄存器。 */

typedef union
{
    struct
    {
        unsigned int    addr                       : 32; /* [31..0] 通道3 BD队列读地址。可被软复位 */
    } bits;
    unsigned int    u32;
}HI_CH3_BDQ_RADDR_T;    /* 通道3 BDQ读地址寄存器。 */

typedef union
{
    struct
    {
        unsigned int    addr                       : 32; /* [31..0] 通道3 BD队列写地址。可被软复位 */
    } bits;
    unsigned int    u32;
}HI_CH3_BDQ_WADDR_T;    /* 通道3 BDQ写地址寄存器。 */

typedef union
{
    struct
    {
        unsigned int    ch3_bd_num                 : 32; /* [31..0] 表示通道3已经处理的BD总数只读，可以写清零 */
    } bits;
    unsigned int    u32;
}HI_CH3_BD_NUM_T;    /* 表示通道3处理的BD总数 */

typedef union
{
    struct
    {
        unsigned int    ch3_invalid_bd_num         : 32; /* [31..0] 表示通道3已经处理的无效BD总数只读，可以写清零 */
    } bits;
    unsigned int    u32;
}HI_CH3_INVALID_BD_NUM_T;    /* 表示通道3处理的无效BD数 */

typedef union
{
    struct
    {
        unsigned int    ch_srst                    : 1; /* [0..0] 写1复位通道，若此时通道占有总线，不能立即执行复位，直到本通道释放总线以后才开始复位，复位结束此寄存器自动归0。 */
        unsigned int    ch_bdq_clear               : 1; /* [1..1] 写1请求复位BD对列，若此时通道正busy，则等到当前BD处理完毕后，清空BD对列，同时该位自动归零。 */
        unsigned int    ch_rdq_clear               : 1; /* [2..2] 写1请求复位RD对列，若此时通道正busy，则等到当前BD处理完毕后，清空RD对列，同时该位自动归零。 */
        unsigned int    reserved                   : 29; /* [31..3] 域说明。 */
    } bits;
    unsigned int    u32;
}HI_CH4_SOFTRESET_T;    /* 通道4软复位寄存器 */

typedef union
{
    struct
    {
        unsigned int    ch_en                      : 1; /* [0..0] 1表示通道使能，0表示通道禁止。 */
        unsigned int    reserved                   : 29; /* [29..1]  */
        unsigned int    pack_en                    : 1; /* [30..30] 此寄存器初始值为1，当为1时，表示本次组包任务完成，可以开始下一次，否则表示本次组包任务正在进行。与配合软件配合过程如下：当cipher配合进行上行组包时，首先查询此寄存器，若为1，表示可以开始组包，软件将此bit置0，且软件把本次组包的最后一个BD中的gen_bd_int置为有效，当cipher完成这最后一个BD任务后，把此寄存器置为1，通知软件可以开始下一次组包任务。 */
        unsigned int    ch_busy                    : 1; /* [31..31] 1表示通道工作，0表示通道暂停。 */
    } bits;
    unsigned int    u32;
}HI_CH4_EN_T;    /* 通道4使能寄存器 */

typedef union
{
    struct
    {
        unsigned int    iv_sel                     : 1; /* [0..0] 本通道完整性参数、IV随BD还是都由芯片自动产生。0：完整性参数、IV由芯片根据参数自动产生；1：完整性参数、IV随包或随BD。 */
        unsigned int    iv_num                     : 1; /* [1..1] 本通道BD中含有的IV个数。只有当iv_sel为1时有意义。0：一个IV，此时BD长度固定是；1：两个IV，其中一个IV可以是无效IV，但仍需占用内存。 */
        unsigned int    rdq_ctrl                   : 2; /* [3..2] RDQ对列维护方式。当RDQ满且有需要回写的RD时，Cipher等待直到RDQ不满；00：不回写RD；01：每个BD都对应回写RD。others：RD是否回写由BD配置决定，只在BD中的gen_rd_en有效时回写RD。 */
        unsigned int    reserved_1                 : 1; /* [4..4] 保留。 */
        unsigned int    ufield_len                 : 2; /* [6..5] BD中userfield字段的长度，单位是32bit。 */
        unsigned int    reserved_0                 : 25; /* [31..7] 保留。 */
    } bits;
    unsigned int    u32;
}HI_CH4_CONFIG_T;    /* 通道4配置寄存器 */

typedef union
{
    struct
    {
        unsigned int    base_addr_l                : 3; /* [2..0] 通道0 BD队列基地址低3bit，固定为0。即要求基址64位对齐。 */
        unsigned int    base_addr                  : 29; /* [31..3] 通道4 BD队列基地址高29位 */
    } bits;
    unsigned int    u32;
}HI_CH4_BDQ_BADDR_T;    /* 通道4 BDQ基地址寄存器 */

typedef union
{
    struct
    {
        unsigned int    size                       : 10; /* [9..0] 通道0 BD Queue大小，以描述符个数为单位。0：表示队列大小为1255：表示队列大小为256 */
        unsigned int    reserved                   : 22; /* [31..10] 成员说明。 */
    } bits;
    unsigned int    u32;
}HI_CH4_BDQ_SIZE_T;    /* 通道4 BDQ大小寄存器 */

typedef union
{
    struct
    {
        unsigned int    wptr                       : 10; /* [9..0] BD队列写指针。可被软复位 */
        unsigned int    reserved_1                 : 6; /* [15..10] 保留 */
        unsigned int    rptr                       : 10; /* [25..16] BD队列读指针。可被软复位。 */
        unsigned int    reserved_0                 : 4; /* [29..26] 保留 */
        unsigned int    ch4_bdq_empty              : 1; /* [30..30] BD队列空 */
        unsigned int    ch4_bdq_full               : 1; /* [31..31] BD队列满 */
    } bits;
    unsigned int    u32;
}HI_CH4_BDQ_PTR_T;    /* 通道4 BDQ读写指针寄存器。 */

typedef union
{
    struct
    {
        unsigned int    addr                       : 32; /* [31..0] 通道4 BD队列读地址。可被软复位 */
    } bits;
    unsigned int    u32;
}HI_CH4_BDQ_RADDR_T;    /* 通道4 BDQ读地址寄存器。 */

typedef union
{
    struct
    {
        unsigned int    addr                       : 32; /* [31..0] 通道4 BD队列写地址。可被软复位。 */
    } bits;
    unsigned int    u32;
}HI_CH4_BDQ_WADDR_T;    /* 通道4 BDQ写地址寄存器。 */

typedef union
{
    struct
    {
        unsigned int    ch4_bd_num                 : 32; /* [31..0] 表示通道4已经处理的BD总数只读，可以写清零 */
    } bits;
    unsigned int    u32;
}HI_CH4_BD_NUM_T;    /* 表示通道4处理的BD总数 */

typedef union
{
    struct
    {
        unsigned int    ch4_invalid_bd_num         : 32; /* [31..0] 表示通道4已经处理的无效BD总数只读，可以写清零 */
    } bits;
    unsigned int    u32;
}HI_CH4_INVALID_BD_NUM_T;    /* 表示通道4处理的无效BD数 */

typedef union
{
    struct
    {
        unsigned int    ch_srst                    : 1; /* [0..0] 写1复位通道，若此时通道占有总线，不能立即执行复位，直到本通道释放总线以后才开始复位，复位结束此寄存器自动归0。 */
        unsigned int    ch_bdq_clear               : 1; /* [1..1] 写1请求复位BD对列，若此时通道正busy，则等到当前BD处理完毕后，清空BD对列，同时该位自动归零。 */
        unsigned int    ch_rdq_clear               : 1; /* [2..2] 写1请求复位RD对列，若此时通道正busy，则等到当前BD处理完毕后，清空RD对列，同时该位自动归零。 */
        unsigned int    reserved                   : 29; /* [31..3] 域说明。 */
    } bits;
    unsigned int    u32;
}HI_CH5_SOFTRESET_T;    /* 通道5软复位寄存器 */

typedef union
{
    struct
    {
        unsigned int    ch_en                      : 1; /* [0..0] 1表示通道使能，0表示通道禁止。 */
        unsigned int    reserved                   : 29; /* [29..1]  */
        unsigned int    pack_en                    : 1; /* [30..30] 此寄存器初始值为1，当为1时，表示本次组包任务完成，可以开始下一次，否则表示本次组包任务正在进行。与配合软件配合过程如下：当cipher配合进行上行组包时，首先查询此寄存器，若为1，表示可以开始组包，软件将此bit置0，且软件把本次组包的最后一个BD中的gen_bd_int置为有效，当cipher完成这最后一个BD任务后，把此寄存器置为1，通知软件可以开始下一次组包任务。 */
        unsigned int    ch_busy                    : 1; /* [31..31] 1表示通道工作，0表示通道暂停。 */
    } bits;
    unsigned int    u32;
}HI_CH5_EN_T;    /* 通道5使能寄存器 */

typedef union
{
    struct
    {
        unsigned int    iv_sel                     : 1; /* [0..0] 本通道完整性参数、IV随BD还是都由芯片自动产生。0：完整性参数、IV由芯片根据参数自动产生；1：完整性参数、IV随包或随BD。 */
        unsigned int    iv_num                     : 1; /* [1..1] 本通道BD中含有的IV个数。只有当iv_sel为1时有意义。0：一个IV，此时BD长度固定是；1：两个IV，其中一个IV可以是无效IV，但仍需占用内存。 */
        unsigned int    rdq_ctrl                   : 2; /* [3..2] RDQ对列维护方式。当RDQ满且有需要回写的RD时，Cipher等待直到RDQ不满；00：不回写RD；01：每个BD都对应回写RD。others：RD是否回写由BD配置决定，只在BD中的gen_rd_en有效时回写RD。 */
        unsigned int    reserved_1                 : 1; /* [4..4] 保留。 */
        unsigned int    ufield_len                 : 2; /* [6..5] BD中userfield字段的长度，单位是32bit。 */
        unsigned int    reserved_0                 : 25; /* [31..7] 保留。 */
    } bits;
    unsigned int    u32;
}HI_CH5_CONFIG_T;    /* 通道5配置寄存器 */

typedef union
{
    struct
    {
        unsigned int    base_addr_l                : 3; /* [2..0] 通道0 BD队列基地址低3bit，固定为0。即要求基址64位对齐。 */
        unsigned int    base_addr                  : 29; /* [31..3] 通道5 BD队列基地址高29位 */
    } bits;
    unsigned int    u32;
}HI_CH5_BDQ_BADDR_T;    /* 通道5 BDQ基地址寄存器 */

typedef union
{
    struct
    {
        unsigned int    size                       : 10; /* [9..0] 通道0 BD Queue大小，以描述符个数为单位。0：表示队列大小为11023：表示队列大小为1024 */
        unsigned int    reserved                   : 22; /* [31..10] 成员说明。 */
    } bits;
    unsigned int    u32;
}HI_CH5_BDQ_SIZE_T;    /* 通道5 BDQ大小寄存器 */

typedef union
{
    struct
    {
        unsigned int    wptr                       : 10; /* [9..0] BD队列写指针。可被软复位 */
        unsigned int    reserved_1                 : 6; /* [15..10] 保留 */
        unsigned int    rptr                       : 10; /* [25..16] BD队列读指针。可被软复位。 */
        unsigned int    reserved_0                 : 4; /* [29..26] 保留 */
        unsigned int    ch_bdq_empty               : 1; /* [30..30] BD队列空 */
        unsigned int    ch_bdq_full                : 1; /* [31..31] BD队列满 */
    } bits;
    unsigned int    u32;
}HI_CH5_BDQ_PTR_T;    /* 通道5 BDQ读写指针寄存器。 */

typedef union
{
    struct
    {
        unsigned int    addr                       : 32; /* [31..0] 通道5 BD队列读地址。可被软复位 */
    } bits;
    unsigned int    u32;
}HI_CH5_BDQ_RADDR_T;    /* 通道5 BDQ读地址寄存器。 */

typedef union
{
    struct
    {
        unsigned int    addr                       : 32; /* [31..0] 通道5 BD队列写地址。可被软复位 */
    } bits;
    unsigned int    u32;
}HI_CH5_BDQ_WADDR_T;    /* 通道5 BDQ写地址寄存器。 */

typedef union
{
    struct
    {
        unsigned int    ch_bd_num                  : 32; /* [31..0] 表示通道5已经处理的BD总数只读，可以写清零 */
    } bits;
    unsigned int    u32;
}HI_CH5_BD_NUM_T;    /* 表示通道5处理的BD总数 */

typedef union
{
    struct
    {
        unsigned int    ch_invalid_bd_num          : 32; /* [31..0] 表示通道5已经处理的无效BD总数只读，可以写清零 */
    } bits;
    unsigned int    u32;
}HI_CH5_INVALID_BD_NUM_T;    /* 表示通道5处理的无效BD数 */

typedef union
{
    struct
    {
        unsigned int    ch_srst                    : 1; /* [0..0] 写1复位通道，若此时通道占有总线，不能立即执行复位，直到本通道释放总线以后才开始复位，复位结束此寄存器自动归0。 */
        unsigned int    ch_bdq_clear               : 1; /* [1..1] 写1请求复位BD对列，若此时通道正busy，则等到当前BD处理完毕后，清空BD对列，同时该位自动归零。 */
        unsigned int    ch_rdq_clear               : 1; /* [2..2] 写1请求复位RD对列，若此时通道正busy，则等到当前BD处理完毕后，清空RD对列，同时该位自动归零。 */
        unsigned int    reserved                   : 29; /* [31..3] 域说明。 */
    } bits;
    unsigned int    u32;
}HI_CH6_SOFTRESET_T;    /* 通道6软复位寄存器 */

typedef union
{
    struct
    {
        unsigned int    ch_en                      : 1; /* [0..0] 1表示通道使能，0表示通道禁止。 */
        unsigned int    reserved                   : 29; /* [29..1]  */
        unsigned int    pack_en                    : 1; /* [30..30] 此寄存器初始值为1，当为1时，表示本次组包任务完成，可以开始下一次，否则表示本次组包任务正在进行。与配合软件配合过程如下：当cipher配合进行上行组包时，首先查询此寄存器，若为1，表示可以开始组包，软件将此bit置0，且软件把本次组包的最后一个BD中的gen_bd_int置为有效，当cipher完成这最后一个BD任务后，把此寄存器置为1，通知软件可以开始下一次组包任务。 */
        unsigned int    ch_busy                    : 1; /* [31..31] 1表示通道工作，0表示通道暂停。 */
    } bits;
    unsigned int    u32;
}HI_CH6_EN_T;    /* 通道6使能寄存器 */

typedef union
{
    struct
    {
        unsigned int    iv_sel                     : 1; /* [0..0] 本通道完整性参数、IV随BD还是都由芯片自动产生。0：完整性参数、IV由芯片根据参数自动产生；1：完整性参数、IV随包或随BD。 */
        unsigned int    iv_num                     : 1; /* [1..1] 本通道BD中含有的IV个数。只有当iv_sel为1时有意义。0：一个IV，此时BD长度固定是；1：两个IV，其中一个IV可以是无效IV，但仍需占用内存。 */
        unsigned int    rdq_ctrl                   : 2; /* [3..2] RDQ对列维护方式。当RDQ满且有需要回写的RD时，Cipher等待直到RDQ不满；00：不回写RD；01：每个BD都对应回写RD。others：RD是否回写由BD配置决定，只在BD中的gen_rd_en有效时回写RD。 */
        unsigned int    reserved_1                 : 1; /* [4..4] 保留。 */
        unsigned int    ufield_len                 : 2; /* [6..5] BD中userfield字段的长度，单位是32bit。 */
        unsigned int    reserved_0                 : 25; /* [31..7] 保留。 */
    } bits;
    unsigned int    u32;
}HI_CH6_CONFIG_T;    /* 通道6配置寄存器 */

typedef union
{
    struct
    {
        unsigned int    base_addr_l                : 3; /* [2..0] 通道0 BD队列基地址低3bit，固定为0。即要求基址64位对齐。 */
        unsigned int    base_addr                  : 29; /* [31..3] 通道6 BD队列基地址高29位 */
    } bits;
    unsigned int    u32;
}HI_CH6_BDQ_BADDR_T;    /* 通道6 BDQ基地址寄存器 */

typedef union
{
    struct
    {
        unsigned int    size                       : 10; /* [9..0] 通道0 BD Queue大小，以描述符个数为单位。0：表示队列大小为11023：表示队列大小为1024 */
        unsigned int    reserved                   : 22; /* [31..10] 成员说明。 */
    } bits;
    unsigned int    u32;
}HI_CH6_BDQ_SIZE_T;    /* 通道6 BDQ大小寄存器 */

typedef union
{
    struct
    {
        unsigned int    wptr                       : 10; /* [9..0] BD队列写指针。可被软复位 */
        unsigned int    reserved_1                 : 6; /* [15..10] 保留 */
        unsigned int    rptr                       : 10; /* [25..16] BD队列读指针。可被软复位。 */
        unsigned int    reserved_0                 : 4; /* [29..26] 保留 */
        unsigned int    ch6_bdq_empty              : 1; /* [30..30] BD队列空 */
        unsigned int    ch6_bdq_full               : 1; /* [31..31] BD队列满 */
    } bits;
    unsigned int    u32;
}HI_CH6_BDQ_PTR_T;    /* 通道6 BDQ读写指针寄存器。 */

typedef union
{
    struct
    {
        unsigned int    addr                       : 32; /* [31..0] 通道6 BD队列读地址。可被软复位 */
    } bits;
    unsigned int    u32;
}HI_CH6_BDQ_RADDR_T;    /* 通道6 BDQ读地址寄存器。 */

typedef union
{
    struct
    {
        unsigned int    addr                       : 32; /* [31..0] 通道6 BD队列写地址。可被软复位 */
    } bits;
    unsigned int    u32;
}HI_CH6_BDQ_WADDR_T;    /* 通道6 BDQ写地址寄存器。 */

typedef union
{
    struct
    {
        unsigned int    ch6_bd_num                 : 32; /* [31..0] 表示通道6已经处理的BD总数只读，可以写清零 */
    } bits;
    unsigned int    u32;
}HI_CH6_BD_NUM_T;    /* 表示通道6处理的BD总数 */

typedef union
{
    struct
    {
        unsigned int    ch6_invalid_bd_num         : 32; /* [31..0] 表示通道6已经处理的无效BD总数只读，可以写清零 */
    } bits;
    unsigned int    u32;
}HI_CH6_INVALID_BD_NUM_T;    /* 表示通道6处理的无效BD数 */

typedef union
{
    struct
    {
        unsigned int    ch0_pkt_num                : 4; /* [3..0] 通道0 BD DONE中断包间隔数。0：5个数据包；1：10个数据包；n：10*（n+1）个数据包 */
        unsigned int    ch1_pkt_num                : 4; /* [7..4] 通道1 BD DONE中断包间隔数。0：5个数据包；1：10个数据包；n：10*（n+1）个数据包 */
        unsigned int    ch2_pkt_num                : 4; /* [11..8] 通道2 BD DONE中断包间隔数。0：5个数据包；1：10个数据包；n：10*（n+1）个数据包 */
        unsigned int    ch3_pkt_num                : 4; /* [15..12] 通道3 BD DONE中断包间隔数。0：5个数据包；1：10个数据包；n：10*（n+1）个数据包 */
        unsigned int    ch5_pkt_num                : 4; /* [19..16] 通道5 BD DONE中断包间隔数。0：5个数据包；1：10个数据包；n：10*（n+1）个数据包 */
        unsigned int    ch6_pkt_num                : 4; /* [23..20] 通道6 BD DONE中断包间隔数。0：5个数据包；1：10个数据包；n：10*（n+1）个数据包 */
        unsigned int    ch4_pkt_num                : 4; /* [27..24] 通道4 BD DONE中断包间隔数。0：5个数据包；1：10个数据包；n：10*（n+1）个数据包 */
        unsigned int    reserved                   : 4; /* [31..28] 保留。 */
    } bits;
    unsigned int    u32;
}HI_CH_INT_PKT_INTERVAL_T;    /* 中断包间隔寄存器 */

typedef union
{
    struct
    {
        unsigned int    cipher_int0                : 1; /* [0..0] CIPHER_INT0_STATUS中断寄存器中的中断是否有中断侵请求。可被软复位 */
        unsigned int    cipher_int1                : 1; /* [1..1] CIPHER_INT1_STATUS中断寄存器中的中断是否有中断侵请求。可被软复位 */
        unsigned int    cipher_int2                : 1; /* [2..2] CIPHER_INT2_STATUS中断寄存器中的中断是否有中断侵请求。可被软复位 */
        unsigned int    cipher_int3                : 1; /* [3..3] CIPHER_INT3_STATUS中断寄存器中的中断是否有中断侵请求。可被软复位 */
        unsigned int    cipher_int4                : 1; /* [4..4] CIPHER_INT4_STATUS中断寄存器中的中断是否有中断侵请求。可被软复位 */
        unsigned int    reserved                   : 27; /* [31..5] 保留。 */
    } bits;
    unsigned int    u32;
}HI_CIPHER_INT_STATUS_T;    /* cipher中断状态寄存器 */

typedef union
{
    struct
    {
        unsigned int    ch0_bdq_full               : 1; /* [0..0] 通道0 BDQ满中断。当BDQ满时发起此中断。 */
        unsigned int    ch0_rdq_full               : 1; /* [1..1] 通道0 RDQ满中断。当RDQ满时发起此中断。 */
        unsigned int    ch0_nbd_done               : 1; /* [2..2] 通道0处理完给定数目N个BD之后产生此中断。N的值见CH0_INT_PKT_INTERVAL。 */
        unsigned int    ch0_bd_done                : 1; /* [3..3] 通道0当BD中gen_int_en为1时，在当前BD的操作完成后产生此中断。 */
        unsigned int    ch0_allbd_done             : 1; /* [4..4] 通道0在BDQ中最后一个BD操作完成后产生此中断。 */
        unsigned int    ch0_integrity_err          : 1; /* [5..5] 通道0完整性检查错误中断。 */
        unsigned int    reserved_3                 : 2; /* [7..6]  */
        unsigned int    ch1_bdq_full               : 1; /* [8..8] 通道1 BDQ满中断。当BDQ满时发起此中断。 */
        unsigned int    ch1_rdq_full               : 1; /* [9..9] 通道1 RDQ满中断。当RDQ满时发起此中断。 */
        unsigned int    ch1_nbd_done               : 1; /* [10..10] 通道1处理完给定数目N个BD之后产生此中断。N的值见CH0_INT_PKT_INTERVAL。 */
        unsigned int    ch1_bd_done                : 1; /* [11..11] 通道1当BD中gen_int_en为1时，在当前BD的操作完成后产生此中断。 */
        unsigned int    ch1_allbd_done             : 1; /* [12..12] 通道1在BDQ中最后一个BD操作完成后产生此中断。 */
        unsigned int    ch1_integrity_err          : 1; /* [13..13] 通道1完整性检查错误中断。 */
        unsigned int    reserved_2                 : 2; /* [15..14]  */
        unsigned int    ch2_bdq_full               : 1; /* [16..16] 通道2 BDQ满中断。当BDQ满时发起此中断。 */
        unsigned int    ch2_rdq_full               : 1; /* [17..17] 通道2 RDQ满中断。当RDQ满时发起此中断。 */
        unsigned int    ch2_nbd_done               : 1; /* [18..18] 通道2处理完给定数目N个BD之后产生此中断。N的值见CH0_INT_PKT_INTERVAL。 */
        unsigned int    ch2_bd_done                : 1; /* [19..19] 通道2当BD中gen_int_en为1时，在当前BD的操作完成后产生此中断。 */
        unsigned int    ch2_allbd_done             : 1; /* [20..20] 通道2在BDQ中最后一个BD操作完成后产生此中断。 */
        unsigned int    ch2_integrity_err          : 1; /* [21..21] 通道2完整性检查错误中断。 */
        unsigned int    reserved_1                 : 2; /* [23..22]  */
        unsigned int    ch3_bdq_full               : 1; /* [24..24] 通道3 BDQ满中断。当BDQ满时发起此中断。 */
        unsigned int    ch3_rdq_full               : 1; /* [25..25] 通道3 RDQ满中断。当RDQ满时发起此中断。 */
        unsigned int    ch3_nbd_done               : 1; /* [26..26] 通道3处理完给定数目N个BD之后产生此中断。N的值见CH0_INT_PKT_INTERVAL。 */
        unsigned int    ch3_bd_done                : 1; /* [27..27] 通道3当BD中gen_int_en为1时，在当前BD的操作完成后产生此中断。写1清中断 */
        unsigned int    ch3_allbd_done             : 1; /* [28..28] 通道3在BDQ中最后一个BD操作完成后产生此中断。写1清中断 */
        unsigned int    ch3_integrity_err          : 1; /* [29..29] 通道3完整性检查错误中断。写1清中断。 */
        unsigned int    reserved_0                 : 2; /* [31..30] 保留。该状态寄存器可被软复位 */
    } bits;
    unsigned int    u32;
}HI_CIPHER_INT0_STATUS_T;    /* cipher中断寄存器0 */

typedef union
{
    struct
    {
        unsigned int    int0_mask                  : 32; /* [31..0] 与cipher_int0_status各位对应的中断屏蔽寄存器 */
    } bits;
    unsigned int    u32;
}HI_CIPHER_INT0_MASK_T;    /* cipher中断屏蔽寄存器0 */

typedef union
{
    struct
    {
        unsigned int    int0_mstatus               : 32; /* [31..0] 经过屏蔽之后的中断状态，写1清除对应bit。可被软复位。 */
    } bits;
    unsigned int    u32;
}HI_CIPHER_INT0_MSTATUS_T;    /* cipher经过屏蔽之后的中断状态寄存器0 */

typedef union
{
    struct
    {
        unsigned int    ch0_bdq_empty              : 1; /* [0..0] 通道0 BDQ空中断。当BDQ空且所有BD已处理完时发起此中断。 */
        unsigned int    ch0_rdq_empty              : 1; /* [1..1] 通道0 RDQ空中断。当RDQ空时发起此中断。 */
        unsigned int    ch0_timeout                : 1; /* [2..2] cipher一直忙且一直没有BD处理完成。该状态表明cipher出现故障，需要软件处理（复位）。 */
        unsigned int    reserved_3                 : 5; /* [7..3]  */
        unsigned int    ch1_bdq_empty              : 1; /* [8..8] 通道1 BDQ空中断。当BDQ空且所有BD已处理完时发起此中断。 */
        unsigned int    ch1_rdq_empty              : 1; /* [9..9] 通道1 RDQ空中断。当RDQ空时发起此中断。 */
        unsigned int    ch1_timeout                : 1; /* [10..10] cipher一直忙且一直没有BD处理完成。该状态表明cipher出现故障，需要软件处理（复位）。 */
        unsigned int    reserved_2                 : 5; /* [15..11]  */
        unsigned int    ch2_bdq_empty              : 1; /* [16..16] 通道2 BDQ空中断。当BDQ空且所有BD已处理完时发起此中断。 */
        unsigned int    ch2_rdq_empty              : 1; /* [17..17] 通道2 RDQ空中断。当RDQ空时发起此中断。 */
        unsigned int    ch2_timeout                : 1; /* [18..18] cipher一直忙且一直没有BD处理完成。该状态表明cipher出现故障，需要软件处理（复位）。 */
        unsigned int    reserved_1                 : 5; /* [23..19]  */
        unsigned int    ch3_bdq_empty              : 1; /* [24..24] 通道3 BDQ空中断。当BDQ空且所有BD已处理完时发起此中断。 */
        unsigned int    ch3_rdq_empty              : 1; /* [25..25] 通道3 RDQ空中断。当RDQ空时发起此中断。 */
        unsigned int    ch3_timeout                : 1; /* [26..26] cipher一直忙且一直没有BD处理完成。该状态表明cipher出现故障，需要软件处理（复位）。 */
        unsigned int    reserved_0                 : 5; /* [31..27] 保留。该状态寄存器可被软复位 */
    } bits;
    unsigned int    u32;
}HI_CIPHER_INT1_STATUS_T;    /* cipher中断寄存器1 */

typedef union
{
    struct
    {
        unsigned int    int1_mask                  : 32; /* [31..0] 与cipher_int1_status各位对应的中断屏蔽寄存器 */
    } bits;
    unsigned int    u32;
}HI_CIPHER_INT1_MASK_T;    /* cipher中断屏蔽寄存器1 */

typedef union
{
    struct
    {
        unsigned int    int1_mstatus               : 32; /* [31..0] 经过屏蔽之后的中断状态，写1清除对应bit。可被软复位。 */
    } bits;
    unsigned int    u32;
}HI_CIPHER_INT1_MSTATUS_T;    /* cipher经过屏蔽之后的中断状态寄存器1 */

typedef union
{
    struct
    {
        unsigned int    ch4_bdq_full               : 1; /* [0..0] 通道4 BDQ满中断。当BDQ满时发起此中断。 */
        unsigned int    ch4_rdq_full               : 1; /* [1..1] 通道4 RDQ满中断。当RDQ满时发起此中断。 */
        unsigned int    ch4_nbd_done               : 1; /* [2..2] 通道4处理完给定数目N个BD之后产生此中断。N的值见CH0_INT_PKT_INTERVAL。 */
        unsigned int    ch4_bd_done                : 1; /* [3..3] 通道4当BD中gen_int_en为1时，在当前BD的操作完成后产生此中断。 */
        unsigned int    ch4_allbd_done             : 1; /* [4..4] 通道4在BDQ中最后一个BD操作完成后产生此中断。 */
        unsigned int    ch4_bdq_empty              : 1; /* [5..5] 通道4 BDQ空中断。当BDQ空且所有BD已处理完时发起此中断。 */
        unsigned int    ch4_rdq_empty              : 1; /* [6..6] 通道4 RDQ空中断。当RDQ空时发起此中断。 */
        unsigned int    ch4_timeout                : 1; /* [7..7] cipher一直忙且一直没有BD处理完成。该状态表明cipher出现故障，需要软件处理（复位）。 */
        unsigned int    reserved                   : 24; /* [31..8] 保留。该状态寄存器可被软复位 */
    } bits;
    unsigned int    u32;
}HI_CIPHER_INT2_STATUS_T;    /* cipher中断寄存器2 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] 与cipher_int2_status各位对应的中断屏蔽寄存器 */
    } bits;
    unsigned int    u32;
}HI_CIPHER_INT2_MASK_T;    /* cipher中断屏蔽寄存器2 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] 经过屏蔽之后的中断状态，写1清除对应bit。可被软复位。 */
    } bits;
    unsigned int    u32;
}HI_CIPHER_INT2_MSTATUS_T;    /* cipher经过屏蔽之后的中断状态寄存器2 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0]  */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG21_T;    /* RD_ADDR */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0]  */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG22_T;    /* ICD_ADDR */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0]  */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG23_T;    /* OCD_ADDR */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0]  */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG24_T;    /* IBUF_ADDR */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0]  */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG25_T;    /* OBUF1_ADDR */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0]  */
    } bits;
    unsigned int    u32;
}HI_CIPHER_DEBUG26_T;    /* OBUF2_ADDR */

typedef union
{
    struct
    {
        unsigned int    ch5_bdq_full               : 1; /* [0..0] 通道5 BDQ满中断。当BDQ满时发起此中断。 */
        unsigned int    ch5_rdq_full               : 1; /* [1..1] 通道5 RDQ满中断。当RDQ满时发起此中断。 */
        unsigned int    ch5_nbd_done               : 1; /* [2..2] 通道5处理完给定数目N个BD之后产生此中断。N的值见CH0_INT_PKT_INTERVAL。 */
        unsigned int    ch5_bd_done                : 1; /* [3..3] 通道5当BD中gen_int_en为1时，在当前BD的操作完成后产生此中断。 */
        unsigned int    ch5_allbd_done             : 1; /* [4..4] 通道5在BDQ中最后一个BD操作完成后产生此中断。 */
        unsigned int    ch5_integrity_err          : 1; /* [5..5] 通道5完整性检查错误中断。 */
        unsigned int    reserved_1                 : 2; /* [7..6]  */
        unsigned int    ch6_bdq_full               : 1; /* [8..8] 通道6 BDQ满中断。当BDQ满时发起此中断。 */
        unsigned int    ch6_rdq_full               : 1; /* [9..9] 通道6 RDQ满中断。当RDQ满时发起此中断。 */
        unsigned int    ch6_nbd_done               : 1; /* [10..10] 通道6处理完给定数目N个BD之后产生此中断。N的值见CH0_INT_PKT_INTERVAL。 */
        unsigned int    ch6_bd_done                : 1; /* [11..11] 通道6当BD中gen_int_en为1时，在当前BD的操作完成后产生此中断。 */
        unsigned int    ch6_allbd_done             : 1; /* [12..12] 通道6在BDQ中最后一个BD操作完成后产生此中断。 */
        unsigned int    ch6_integrity_err          : 1; /* [13..13] 通道6完整性检查错误中断。 */
        unsigned int    reserved_0                 : 18; /* [31..14] 保留。该状态寄存器可被软复位 */
    } bits;
    unsigned int    u32;
}HI_CIPHER_INT3_STATUS_T;    /* cipher中断寄存器3 */

typedef union
{
    struct
    {
        unsigned int    int0_mask                  : 32; /* [31..0] 与cipher_int3_status各位对应的中断屏蔽寄存器 */
    } bits;
    unsigned int    u32;
}HI_CIPHER_INT3_MASK_T;    /* cipher中断屏蔽寄存器3 */

typedef union
{
    struct
    {
        unsigned int    int0_mstatus               : 32; /* [31..0] 经过屏蔽之后的中断状态，写1清除对应bit。可被软复位。 */
    } bits;
    unsigned int    u32;
}HI_CIPHER_INT3_MSTATUS_T;    /* cipher经过屏蔽之后的中断状态寄存器3 */

typedef union
{
    struct
    {
        unsigned int    ch5_bdq_empty              : 1; /* [0..0] 通道5 BDQ空中断。当BDQ空且所有BD已处理完时发起此中断。 */
        unsigned int    ch5_rdq_empty              : 1; /* [1..1] 通道5 RDQ空中断。当RDQ空时发起此中断。 */
        unsigned int    ch5_timeout                : 1; /* [2..2] cipher一直忙且一直没有BD处理完成。该状态表明cipher出现故障，需要软件处理（复位）。 */
        unsigned int    reserved_1                 : 5; /* [7..3]  */
        unsigned int    ch6_bdq_empty              : 1; /* [8..8] 通道6 BDQ空中断。当BDQ空且所有BD已处理完时发起此中断。 */
        unsigned int    ch6_rdq_empty              : 1; /* [9..9] 通道6 RDQ空中断。当RDQ空时发起此中断。 */
        unsigned int    ch6_timeout                : 1; /* [10..10] cipher一直忙且一直没有BD处理完成。该状态表明cipher出现故障，需要软件处理（复位）。 */
        unsigned int    reserved_0                 : 21; /* [31..11] 保留。该状态寄存器可被软复位 */
    } bits;
    unsigned int    u32;
}HI_CIPHER_INT4_STATUS_T;    /* cipher中断寄存器4 */

typedef union
{
    struct
    {
        unsigned int    int1_mask                  : 32; /* [31..0] 与cipher_int1_status各位对应的中断屏蔽寄存器 */
    } bits;
    unsigned int    u32;
}HI_CIPHER_INT4_MASK_T;    /* cipher中断屏蔽寄存器4 */

typedef union
{
    struct
    {
        unsigned int    int1_mstatus               : 32; /* [31..0] 经过屏蔽之后的中断状态，写1清除对应bit。可被软复位。 */
    } bits;
    unsigned int    u32;
}HI_CIPHER_INT4_MSTATUS_T;    /* cipher经过屏蔽之后的中断状态寄存器4 */

typedef union
{
    struct
    {
        unsigned int    timeout_time               : 8; /* [7..0] 超时中断阈值，7个通道共用。单位是20us。 */
        unsigned int    reserved                   : 24; /* [31..8] 保留。 */
    } bits;
    unsigned int    u32;
}HI_TIMEOUT_T;    /* 中断包间隔寄存器 */

typedef union
{
    struct
    {
        unsigned int    base_addr_l                : 3; /* [2..0] 通道0 RD队列基地址低3bit，固定为0。即要求基址64位对齐。 */
        unsigned int    base_addr                  : 29; /* [31..3] 通道0 RD队列基地址高29位 */
    } bits;
    unsigned int    u32;
}HI_CH0_RDQ_BADDR_T;    /* 通道0 RD队列基地址 */

typedef union
{
    struct
    {
        unsigned int    size                       : 10; /* [9..0] 通道0 RD Queue大小，以描述符个数为单位。其中0：表示队列大小为11023：表示队列大小为1024 */
        unsigned int    reserved                   : 22; /* [31..10] 成员说明。 */
    } bits;
    unsigned int    u32;
}HI_CH0_RDQ_SIZE_T;    /* 通道0 RD队列大小 */

typedef union
{
    struct
    {
        unsigned int    wptr                       : 10; /* [9..0] RD队列写指针。可被软复位 */
        unsigned int    reserved_1                 : 6; /* [15..10] 保留 */
        unsigned int    rptr                       : 10; /* [25..16] RD队列读指针。可被软复位 */
        unsigned int    reserved_0                 : 6; /* [31..26] 保留。 */
    } bits;
    unsigned int    u32;
}HI_CH0_RDQ_PTR_T;    /* 通道0 RD队列的读写指针 */

typedef union
{
    struct
    {
        unsigned int    raddr                      : 32; /* [31..0] 通道0 RD队列读地址。可被软复位 */
    } bits;
    unsigned int    u32;
}HI_CH0_RDQ_RADDR_T;    /* 通道0 RD队列的读地址 */

typedef union
{
    struct
    {
        unsigned int    waddr                      : 32; /* [31..0] 通道0 RD队列写地址。可被软复位 */
    } bits;
    unsigned int    u32;
}HI_CH0_RDQ_WADDR_T;    /* 通道0 RD队列的写地址 */

typedef union
{
    struct
    {
        unsigned int    base_addr_l                : 3; /* [2..0] 通道0 RD队列基地址低3bit，固定为0。即要求基址64位对齐。 */
        unsigned int    base_addr                  : 29; /* [31..3] 通道1 RD队列基地址高29位 */
    } bits;
    unsigned int    u32;
}HI_CH1_RDQ_BADDR_T;    /* 通道1 RD队列基地址 */

typedef union
{
    struct
    {
        unsigned int    size                       : 10; /* [9..0] 通道0 RD Queue大小，以描述符个数为单位。其中0：表示队列大小为11023：表示队列大小为1024 */
        unsigned int    reserved                   : 22; /* [31..10] 成员说明。 */
    } bits;
    unsigned int    u32;
}HI_CH1_RDQ_SIZE_T;    /* 通道1 RD队列大小 */

typedef union
{
    struct
    {
        unsigned int    wptr                       : 10; /* [9..0] RD队列写指针。可被软复位 */
        unsigned int    reserved_1                 : 6; /* [15..10] 保留 */
        unsigned int    rptr                       : 10; /* [25..16] RD队列读指针。可被软复位 */
        unsigned int    reserved_0                 : 6; /* [31..26] 保留。 */
    } bits;
    unsigned int    u32;
}HI_CH1_RDQ_PTR_T;    /* 通道1 RD队列的读写指针 */

typedef union
{
    struct
    {
        unsigned int    raddr                      : 32; /* [31..0] 通道1 RD队列读地址。可被软复位 */
    } bits;
    unsigned int    u32;
}HI_CH1_RDQ_RADDR_T;    /* 通道1 RD队列的读地址 */

typedef union
{
    struct
    {
        unsigned int    waddr                      : 32; /* [31..0] 通道1 RD队列写地址。可被软复位 */
    } bits;
    unsigned int    u32;
}HI_CH1_RDQ_WADDR_T;    /* 通道1 RD队列的写地址 */

typedef union
{
    struct
    {
        unsigned int    base_addr_l                : 3; /* [2..0] 通道0 RD队列基地址低3bit，固定为0。即要求基址64位对齐。 */
        unsigned int    base_addr                  : 29; /* [31..3] 通道2 RD队列基地址高29位 */
    } bits;
    unsigned int    u32;
}HI_CH2_RDQ_BADDR_T;    /* 通道2 RD队列基地址 */

typedef union
{
    struct
    {
        unsigned int    size                       : 10; /* [9..0] 通道0 RD Queue大小，以描述符个数为单位。其中0：表示队列大小为11023：表示队列大小为1024 */
        unsigned int    reserved                   : 22; /* [31..10] 成员说明。 */
    } bits;
    unsigned int    u32;
}HI_CH2_RDQ_SIZE_T;    /* 通道2 RD队列大小 */

typedef union
{
    struct
    {
        unsigned int    wptr                       : 10; /* [9..0] RD队列写指针。可被软复位 */
        unsigned int    reserved_1                 : 6; /* [15..10] 保留 */
        unsigned int    rptr                       : 10; /* [25..16] RD队列读指针。可被软复位 */
        unsigned int    reserved_0                 : 6; /* [31..26] 保留。 */
    } bits;
    unsigned int    u32;
}HI_CH2_RDQ_PTR_T;    /* 通道2 RD队列的读写指针 */

typedef union
{
    struct
    {
        unsigned int    raddr                      : 32; /* [31..0] 通道2 RD队列读地址。可被软复位 */
    } bits;
    unsigned int    u32;
}HI_CH2_RDQ_RADDR_T;    /* 通道2 RD队列的读地址 */

typedef union
{
    struct
    {
        unsigned int    waddr                      : 32; /* [31..0] 通道2 RD队列写地址。可被软复位 */
    } bits;
    unsigned int    u32;
}HI_CH2_RDQ_WADDR_T;    /* 通道2 RD队列的写地址 */

typedef union
{
    struct
    {
        unsigned int    base_addr_l                : 3; /* [2..0] 通道0 RD队列基地址低3bit，固定为0。即要求基址64位对齐。 */
        unsigned int    base_addr                  : 29; /* [31..3] 通道3 RD队列基地址高29位 */
    } bits;
    unsigned int    u32;
}HI_CH3_RDQ_BADDR_T;    /* 通道3 RD队列基地址 */

typedef union
{
    struct
    {
        unsigned int    size                       : 10; /* [9..0] 通道0 RD Queue大小，以描述符个数为单位。其中0：表示队列大小为11023：表示队列大小为1024 */
        unsigned int    reserved                   : 22; /* [31..10] 成员说明。 */
    } bits;
    unsigned int    u32;
}HI_CH3_RDQ_SIZE_T;    /* 通道3 RD队列大小 */

typedef union
{
    struct
    {
        unsigned int    wptr                       : 10; /* [9..0] RD队列写指针。可被软复位 */
        unsigned int    reserved_1                 : 6; /* [15..10] 保留 */
        unsigned int    rptr                       : 10; /* [25..16] RD队列读指针。可被软复位 */
        unsigned int    reserved_0                 : 6; /* [31..26] 保留。 */
    } bits;
    unsigned int    u32;
}HI_CH3_RDQ_PTR_T;    /* 通道3 RD队列的读写指针 */

typedef union
{
    struct
    {
        unsigned int    raddr                      : 32; /* [31..0] 通道3 RD队列读地址。可被软复位。 */
    } bits;
    unsigned int    u32;
}HI_CH3_RDQ_RADDR_T;    /* 通道3 RD队列的读地址 */

typedef union
{
    struct
    {
        unsigned int    waddr                      : 32; /* [31..0] 通道3 RD队列写地址。可被软复位。 */
    } bits;
    unsigned int    u32;
}HI_CH3_RDQ_WADDR_T;    /* 通道3 RD队列的写地址 */

typedef union
{
    struct
    {
        unsigned int    base_addr_l                : 3; /* [2..0] 通道0 RD队列基地址低3bit，固定为0。即要求基址64位对齐。 */
        unsigned int    base_addr                  : 29; /* [31..3] 通道4 RD队列基地址高29位 */
    } bits;
    unsigned int    u32;
}HI_CH4_RDQ_BADDR_T;    /* 通道4 RD队列基地址 */

typedef union
{
    struct
    {
        unsigned int    size                       : 10; /* [9..0] 通道0 RD Queue大小，以描述符个数为单位。其中0：表示队列大小为11023：表示队列大小为1024 */
        unsigned int    reserved                   : 22; /* [31..10] 成员说明。 */
    } bits;
    unsigned int    u32;
}HI_CH4_RDQ_SIZE_T;    /* 通道4 RD队列大小 */

typedef union
{
    struct
    {
        unsigned int    wptr                       : 10; /* [9..0] RD队列写指针。可被软复位 */
        unsigned int    reserved_1                 : 6; /* [15..10] 保留 */
        unsigned int    rptr                       : 10; /* [25..16] RD队列读指针。可被软复位 */
        unsigned int    reserved_0                 : 6; /* [31..26] 保留。 */
    } bits;
    unsigned int    u32;
}HI_CH4_RDQ_PTR_T;    /* 通道4 RD队列的读写指针 */

typedef union
{
    struct
    {
        unsigned int    raddr                      : 32; /* [31..0] 通道4 RD队列读地址。可被软复位 */
    } bits;
    unsigned int    u32;
}HI_CH4_RDQ_RADDR_T;    /* 通道4 RD队列的读地址 */

typedef union
{
    struct
    {
        unsigned int    waddr                      : 32; /* [31..0] 通道4 RD队列写地址。可被软复位 */
    } bits;
    unsigned int    u32;
}HI_CH4_RDQ_WADDR_T;    /* 通道4 RD队列的写地址 */

typedef union
{
    struct
    {
        unsigned int    base_addr_l                : 3; /* [2..0] 通道0 RD队列基地址低3bit，固定为0。即要求基址64位对齐。 */
        unsigned int    base_addr                  : 29; /* [31..3] 通道5 RD队列基地址高29位 */
    } bits;
    unsigned int    u32;
}HI_CH5_RDQ_BADDR_T;    /* 通道5 RD队列基地址 */

typedef union
{
    struct
    {
        unsigned int    size                       : 10; /* [9..0] 通道0 RD Queue大小，以描述符个数为单位。其中0：表示队列大小为11023：表示队列大小为1024 */
        unsigned int    reserved                   : 22; /* [31..10] 成员说明。 */
    } bits;
    unsigned int    u32;
}HI_CH5_RDQ_SIZE_T;    /* 通道5 RD队列大小 */

typedef union
{
    struct
    {
        unsigned int    wptr                       : 10; /* [9..0] RD队列写指针。可被软复位 */
        unsigned int    reserved_1                 : 6; /* [15..10] 保留 */
        unsigned int    rptr                       : 10; /* [25..16] RD队列读指针。可被软复位 */
        unsigned int    reserved_0                 : 6; /* [31..26] 保留。 */
    } bits;
    unsigned int    u32;
}HI_CH5_RDQ_PTR_T;    /* 通道5 RD队列的读写指针 */

typedef union
{
    struct
    {
        unsigned int    raddr                      : 32; /* [31..0] 通道5 RD队列读地址。可被软复位。 */
    } bits;
    unsigned int    u32;
}HI_CH5_RDQ_RADDR_T;    /* 通道5 RD队列的读地址 */

typedef union
{
    struct
    {
        unsigned int    waddr                      : 32; /* [31..0] 通道5 RD队列写地址。可被软复位。 */
    } bits;
    unsigned int    u32;
}HI_CH5_RDQ_WADDR_T;    /* 通道5 RD队列的写地址 */

typedef union
{
    struct
    {
        unsigned int    base_addr_l                : 3; /* [2..0] 通道0 RD队列基地址低3bit，固定为0。即要求基址64位对齐。 */
        unsigned int    base_addr                  : 29; /* [31..3] 通道6 RD队列基地址高29位 */
    } bits;
    unsigned int    u32;
}HI_CH6_RDQ_BADDR_T;    /* 通道6 RD队列基地址 */

typedef union
{
    struct
    {
        unsigned int    size                       : 10; /* [9..0] 通道0 RD Queue大小，以描述符个数为单位。其中0：表示队列大小为11023：表示队列大小为1024 */
        unsigned int    reserved                   : 22; /* [31..10] 成员说明。 */
    } bits;
    unsigned int    u32;
}HI_CH6_RDQ_SIZE_T;    /* 通道6 RD队列大小 */

typedef union
{
    struct
    {
        unsigned int    wptr                       : 10; /* [9..0] RD队列写指针。可被软复位 */
        unsigned int    reserved_1                 : 6; /* [15..10] 保留 */
        unsigned int    rptr                       : 10; /* [25..16] RD队列读指针。可被软复位 */
        unsigned int    reserved_0                 : 6; /* [31..26] 保留。 */
    } bits;
    unsigned int    u32;
}HI_CH6_RDQ_PTR_T;    /* 通道6 RD队列的读写指针 */

typedef union
{
    struct
    {
        unsigned int    raddr                      : 32; /* [31..0] 通道6 RD队列读地址。可被软复位 */
    } bits;
    unsigned int    u32;
}HI_CH6_RDQ_RADDR_T;    /* 通道6 RD队列的读地址 */

typedef union
{
    struct
    {
        unsigned int    waddr                      : 32; /* [31..0] 通道6 RD队列写地址。可被软复位 */
    } bits;
    unsigned int    u32;
}HI_CH6_RDQ_WADDR_T;    /* 通道6 RD队列的写地址 */

typedef union
{
    struct
    {
        unsigned int    key                        : 32; /* [31..0] cipher内部的key ram */
    } bits;
    unsigned int    u32;
}HI_KEY_RAM_T;    /* cipher内部的key ram */

#if 0
/********************************************************************************/
/*    cipher 函数（项目名_模块名_寄存器名_成员名_set)        */
/********************************************************************************/
HI_SET_GET(hi_cipher_ctrl_cipher_srst,cipher_srst,HI_CIPHER_CTRL_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_CTRL_OFFSET)
HI_SET_GET(hi_cipher_ctrl_cipher_cg_en,cipher_cg_en,HI_CIPHER_CTRL_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_CTRL_OFFSET)
HI_SET_GET(hi_cipher_ctrl_reserved,reserved,HI_CIPHER_CTRL_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_CTRL_OFFSET)
HI_SET_GET(hi_cipher_ctrl_cipher_busy,cipher_busy,HI_CIPHER_CTRL_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_CTRL_OFFSET)
HI_SET_GET(hi_cipher_pri_ch0_pri,ch0_pri,HI_CIPHER_PRI_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_PRI_OFFSET)
HI_SET_GET(hi_cipher_pri_reserved_5,reserved_5,HI_CIPHER_PRI_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_PRI_OFFSET)
HI_SET_GET(hi_cipher_pri_ch1_pri,ch1_pri,HI_CIPHER_PRI_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_PRI_OFFSET)
HI_SET_GET(hi_cipher_pri_reserved_4,reserved_4,HI_CIPHER_PRI_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_PRI_OFFSET)
HI_SET_GET(hi_cipher_pri_ch2_pri,ch2_pri,HI_CIPHER_PRI_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_PRI_OFFSET)
HI_SET_GET(hi_cipher_pri_reserved_3,reserved_3,HI_CIPHER_PRI_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_PRI_OFFSET)
HI_SET_GET(hi_cipher_pri_ch3_pri,ch3_pri,HI_CIPHER_PRI_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_PRI_OFFSET)
HI_SET_GET(hi_cipher_pri_reserved_2,reserved_2,HI_CIPHER_PRI_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_PRI_OFFSET)
HI_SET_GET(hi_cipher_pri_ch5_pri,ch5_pri,HI_CIPHER_PRI_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_PRI_OFFSET)
HI_SET_GET(hi_cipher_pri_reserved_1,reserved_1,HI_CIPHER_PRI_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_PRI_OFFSET)
HI_SET_GET(hi_cipher_pri_ch6_pri,ch6_pri,HI_CIPHER_PRI_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_PRI_OFFSET)
HI_SET_GET(hi_cipher_pri_reserved_0,reserved_0,HI_CIPHER_PRI_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_PRI_OFFSET)
HI_SET_GET(hi_total_bd_num_total_bd_num,total_bd_num,HI_TOTAL_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_TOTAL_BD_NUM_OFFSET)
HI_SET_GET(hi_invalid_bd_num_invalid_bd_num,invalid_bd_num,HI_INVALID_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_INVALID_BD_NUM_OFFSET)
HI_SET_GET(hi_dma_cfg_rd_id,rd_id,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_dma_cfg_obuf_id,obuf_id,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_dma_cfg_ocd_id,ocd_id,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_dma_cfg_icd_id,icd_id,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_dma_cfg_ibuf_id,ibuf_id,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_dma_cfg_reserved_1,reserved_1,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_dma_cfg_rd_pri,rd_pri,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_dma_cfg_obuf_pri,obuf_pri,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_dma_cfg_ocd_pri,ocd_pri,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_dma_cfg_icd_pri,icd_pri,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_dma_cfg_ibuf_pri,ibuf_pri,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_dma_cfg_reserved_0,reserved_0,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_cipher_version_cipher_version,cipher_version,HI_CIPHER_VERSION_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_VERSION_OFFSET)
HI_SET_GET(hi_test_reg0_spram_mem_ctrl,spram_mem_ctrl,HI_TEST_REG0_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG0_OFFSET)
HI_SET_GET(hi_test_reg0_atpram_mem_ctrl,atpram_mem_ctrl,HI_TEST_REG0_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG0_OFFSET)
HI_SET_GET(hi_test_reg1_aes_key_cov,aes_key_cov,HI_TEST_REG1_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG1_OFFSET)
HI_SET_GET(hi_test_reg1_snow3g_key_cov,snow3g_key_cov,HI_TEST_REG1_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG1_OFFSET)
HI_SET_GET(hi_test_reg1_cipher_dma_ctrl,cipher_dma_ctrl,HI_TEST_REG1_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG1_OFFSET)
HI_SET_GET(hi_test_reg1_zuc_key_cov,zuc_key_cov,HI_TEST_REG1_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG1_OFFSET)
HI_SET_GET(hi_test_reg1_aes_iv_cov,aes_iv_cov,HI_TEST_REG1_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG1_OFFSET)
HI_SET_GET(hi_test_reg1_snow3g_iv_cov,snow3g_iv_cov,HI_TEST_REG1_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG1_OFFSET)
HI_SET_GET(hi_test_reg1_zuc_iv_cov,zuc_iv_cov,HI_TEST_REG1_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG1_OFFSET)
HI_SET_GET(hi_test_reg1_reserved_1,reserved_1,HI_TEST_REG1_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG1_OFFSET)
HI_SET_GET(hi_test_reg1_ibuf_dma_len,ibuf_dma_len,HI_TEST_REG1_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG1_OFFSET)
HI_SET_GET(hi_test_reg1_dma_opt_en,dma_opt_en,HI_TEST_REG1_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG1_OFFSET)
HI_SET_GET(hi_test_reg1_reserved_0,reserved_0,HI_TEST_REG1_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG1_OFFSET)
HI_SET_GET(hi_test_reg2_reserved,reserved,HI_TEST_REG2_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG2_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_rd_gnt,dma_rd_gnt,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_ocd_gnt,dma_ocd_gnt,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_icd_gnt,dma_icd_gnt,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_obuf_gnt,dma_obuf_gnt,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_ibuf_gnt,dma_ibuf_gnt,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_reserved_3,reserved_3,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_rd_req,dma_rd_req,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_ocd_req,dma_ocd_req,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_icd_req,dma_icd_req,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_obuf_req,dma_obuf_req,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_ibuf_req,dma_ibuf_req,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_reserved_2,reserved_2,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_rd_idle,dma_rd_idle,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_ocd_idle,dma_ocd_idle,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_icd_idle,dma_icd_idle,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_obuf_idle,dma_obuf_idle,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_ibuf_idle,dma_ibuf_idle,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_reserved_1,reserved_1,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_rd_trans_end,dma_rd_trans_end,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_ocd_last_read,dma_ocd_last_read,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_icd_last_read,dma_icd_last_read,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_obuf_trans_end,dma_obuf_trans_end,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_ibuf_last_read,dma_ibuf_last_read,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_reserved_0,reserved_0,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug0_reserved,reserved,HI_CIPHER_DEBUG0_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG0_OFFSET)
HI_SET_GET(hi_cipher_debug1_reserved,reserved,HI_CIPHER_DEBUG1_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG1_OFFSET)
HI_SET_GET(hi_cipher_debug2_reserved,reserved,HI_CIPHER_DEBUG2_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG2_OFFSET)
HI_SET_GET(hi_cipher_debug3_reserved,reserved,HI_CIPHER_DEBUG3_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG3_OFFSET)
HI_SET_GET(hi_cipher_debug4_reserved,reserved,HI_CIPHER_DEBUG4_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG4_OFFSET)
HI_SET_GET(hi_cipher_debug5_reserved,reserved,HI_CIPHER_DEBUG5_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG5_OFFSET)
HI_SET_GET(hi_cipher_debug6_reserved,reserved,HI_CIPHER_DEBUG6_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG6_OFFSET)
HI_SET_GET(hi_cipher_debug7_reserved,reserved,HI_CIPHER_DEBUG7_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG7_OFFSET)
HI_SET_GET(hi_cipher_debug8_reserved,reserved,HI_CIPHER_DEBUG8_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG8_OFFSET)
HI_SET_GET(hi_cipher_debug9_reserved,reserved,HI_CIPHER_DEBUG9_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG9_OFFSET)
HI_SET_GET(hi_cipher_debug10_reserved,reserved,HI_CIPHER_DEBUG10_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG10_OFFSET)
HI_SET_GET(hi_cipher_debug11_reserved,reserved,HI_CIPHER_DEBUG11_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG11_OFFSET)
HI_SET_GET(hi_cipher_debug12_reserved,reserved,HI_CIPHER_DEBUG12_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG12_OFFSET)
HI_SET_GET(hi_cipher_debug13_reserved,reserved,HI_CIPHER_DEBUG13_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG13_OFFSET)
HI_SET_GET(hi_cipher_debug14_reserved,reserved,HI_CIPHER_DEBUG14_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG14_OFFSET)
HI_SET_GET(hi_cipher_debug15_reserved,reserved,HI_CIPHER_DEBUG15_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG15_OFFSET)
HI_SET_GET(hi_cipher_debug16_reserved,reserved,HI_CIPHER_DEBUG16_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG16_OFFSET)
HI_SET_GET(hi_cipher_debug17_reserved,reserved,HI_CIPHER_DEBUG17_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG17_OFFSET)
HI_SET_GET(hi_cipher_debug18_reserved,reserved,HI_CIPHER_DEBUG18_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG18_OFFSET)
HI_SET_GET(hi_cipher_debug19_reserved,reserved,HI_CIPHER_DEBUG19_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG19_OFFSET)
HI_SET_GET(hi_ch0_softreset_ch_srst,ch_srst,HI_CH0_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH0_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch0_softreset_ch_bdq_clear,ch_bdq_clear,HI_CH0_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH0_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch0_softreset_ch_rdq_clear,ch_rdq_clear,HI_CH0_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH0_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch0_softreset_reserved,reserved,HI_CH0_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH0_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch0_en_ch_en,ch_en,HI_CH0_EN_T,HI_CIPHER_BASE_ADDR, HI_CH0_EN_OFFSET)
HI_SET_GET(hi_ch0_en_reserved,reserved,HI_CH0_EN_T,HI_CIPHER_BASE_ADDR, HI_CH0_EN_OFFSET)
HI_SET_GET(hi_ch0_en_pack_en,pack_en,HI_CH0_EN_T,HI_CIPHER_BASE_ADDR, HI_CH0_EN_OFFSET)
HI_SET_GET(hi_ch0_en_ch_busy,ch_busy,HI_CH0_EN_T,HI_CIPHER_BASE_ADDR, HI_CH0_EN_OFFSET)
HI_SET_GET(hi_ch0_config_iv_sel,iv_sel,HI_CH0_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH0_CONFIG_OFFSET)
HI_SET_GET(hi_ch0_config_iv_num,iv_num,HI_CH0_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH0_CONFIG_OFFSET)
HI_SET_GET(hi_ch0_config_rdq_ctrl,rdq_ctrl,HI_CH0_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH0_CONFIG_OFFSET)
HI_SET_GET(hi_ch0_config_reserved_1,reserved_1,HI_CH0_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH0_CONFIG_OFFSET)
HI_SET_GET(hi_ch0_config_ufield_len,ufield_len,HI_CH0_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH0_CONFIG_OFFSET)
HI_SET_GET(hi_ch0_config_reserved_0,reserved_0,HI_CH0_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH0_CONFIG_OFFSET)
HI_SET_GET(hi_ch0_bdq_baddr_base_addr_l,base_addr_l,HI_CH0_BDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch0_bdq_baddr_base_addr,base_addr,HI_CH0_BDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch0_bdq_size_size,size,HI_CH0_BDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch0_bdq_size_reserved,reserved,HI_CH0_BDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch0_bdq_ptr_wptr,wptr,HI_CH0_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch0_bdq_ptr_reserved_1,reserved_1,HI_CH0_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch0_bdq_ptr_rptr,rptr,HI_CH0_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch0_bdq_ptr_reserved_0,reserved_0,HI_CH0_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch0_bdq_ptr_ch_bdq_empty,ch_bdq_empty,HI_CH0_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch0_bdq_ptr_ch_bdq_full,ch_bdq_full,HI_CH0_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch0_bdq_raddr_addr,addr,HI_CH0_BDQ_RADDR_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_RADDR_OFFSET)
HI_SET_GET(hi_ch0_bdq_waddr_addr,addr,HI_CH0_BDQ_WADDR_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_WADDR_OFFSET)
HI_SET_GET(hi_ch0_bd_num_ch0_bd_num,ch0_bd_num,HI_CH0_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_CH0_BD_NUM_OFFSET)
HI_SET_GET(hi_ch0_invalid_bd_num_ch0_invalid_bd_num,ch0_invalid_bd_num,HI_CH0_INVALID_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_CH0_INVALID_BD_NUM_OFFSET)
HI_SET_GET(hi_ch1_softreset_ch_srst,ch_srst,HI_CH1_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH1_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch1_softreset_ch_bdq_clear,ch_bdq_clear,HI_CH1_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH1_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch1_softreset_ch_rdq_clear,ch_rdq_clear,HI_CH1_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH1_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch1_softreset_reserved,reserved,HI_CH1_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH1_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch1_en_ch_en,ch_en,HI_CH1_EN_T,HI_CIPHER_BASE_ADDR, HI_CH1_EN_OFFSET)
HI_SET_GET(hi_ch1_en_reserved,reserved,HI_CH1_EN_T,HI_CIPHER_BASE_ADDR, HI_CH1_EN_OFFSET)
HI_SET_GET(hi_ch1_en_pack_en,pack_en,HI_CH1_EN_T,HI_CIPHER_BASE_ADDR, HI_CH1_EN_OFFSET)
HI_SET_GET(hi_ch1_en_ch_busy,ch_busy,HI_CH1_EN_T,HI_CIPHER_BASE_ADDR, HI_CH1_EN_OFFSET)
HI_SET_GET(hi_ch1_config_iv_sel,iv_sel,HI_CH1_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH1_CONFIG_OFFSET)
HI_SET_GET(hi_ch1_config_iv_num,iv_num,HI_CH1_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH1_CONFIG_OFFSET)
HI_SET_GET(hi_ch1_config_rdq_ctrl,rdq_ctrl,HI_CH1_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH1_CONFIG_OFFSET)
HI_SET_GET(hi_ch1_config_reserved_1,reserved_1,HI_CH1_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH1_CONFIG_OFFSET)
HI_SET_GET(hi_ch1_config_ufield_len,ufield_len,HI_CH1_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH1_CONFIG_OFFSET)
HI_SET_GET(hi_ch1_config_reserved_0,reserved_0,HI_CH1_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH1_CONFIG_OFFSET)
HI_SET_GET(hi_ch1_bdq_baddr_base_addr_l,base_addr_l,HI_CH1_BDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch1_bdq_baddr_base_addr,base_addr,HI_CH1_BDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch1_bdq_size_size,size,HI_CH1_BDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch1_bdq_size_reserved,reserved,HI_CH1_BDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch1_bdq_ptr_wptr,wptr,HI_CH1_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch1_bdq_ptr_reserved_1,reserved_1,HI_CH1_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch1_bdq_ptr_rptr,rptr,HI_CH1_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch1_bdq_ptr_reserved_0,reserved_0,HI_CH1_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch1_bdq_ptr_ch1_bdq_empty,ch1_bdq_empty,HI_CH1_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch1_bdq_ptr_ch1_bdq_full,ch1_bdq_full,HI_CH1_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch1_bdq_raddr_addr,addr,HI_CH1_BDQ_RADDR_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_RADDR_OFFSET)
HI_SET_GET(hi_ch1_bdq_waddr_addr,addr,HI_CH1_BDQ_WADDR_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_WADDR_OFFSET)
HI_SET_GET(hi_ch1_bd_num_ch1_bd_num,ch1_bd_num,HI_CH1_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_CH1_BD_NUM_OFFSET)
HI_SET_GET(hi_ch1_invalid_bd_num_ch1_invalid_bd_num,ch1_invalid_bd_num,HI_CH1_INVALID_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_CH1_INVALID_BD_NUM_OFFSET)
HI_SET_GET(hi_ch2_softreset_ch_srst,ch_srst,HI_CH2_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH2_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch2_softreset_ch_bdq_clear,ch_bdq_clear,HI_CH2_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH2_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch2_softreset_ch_rdq_clear,ch_rdq_clear,HI_CH2_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH2_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch2_softreset_reserved,reserved,HI_CH2_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH2_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch2_en_ch_en,ch_en,HI_CH2_EN_T,HI_CIPHER_BASE_ADDR, HI_CH2_EN_OFFSET)
HI_SET_GET(hi_ch2_en_reserved,reserved,HI_CH2_EN_T,HI_CIPHER_BASE_ADDR, HI_CH2_EN_OFFSET)
HI_SET_GET(hi_ch2_en_pack_en,pack_en,HI_CH2_EN_T,HI_CIPHER_BASE_ADDR, HI_CH2_EN_OFFSET)
HI_SET_GET(hi_ch2_en_ch_busy,ch_busy,HI_CH2_EN_T,HI_CIPHER_BASE_ADDR, HI_CH2_EN_OFFSET)
HI_SET_GET(hi_ch2_config_iv_sel,iv_sel,HI_CH2_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH2_CONFIG_OFFSET)
HI_SET_GET(hi_ch2_config_iv_num,iv_num,HI_CH2_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH2_CONFIG_OFFSET)
HI_SET_GET(hi_ch2_config_rdq_ctrl,rdq_ctrl,HI_CH2_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH2_CONFIG_OFFSET)
HI_SET_GET(hi_ch2_config_reserved_1,reserved_1,HI_CH2_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH2_CONFIG_OFFSET)
HI_SET_GET(hi_ch2_config_ufield_len,ufield_len,HI_CH2_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH2_CONFIG_OFFSET)
HI_SET_GET(hi_ch2_config_reserved_0,reserved_0,HI_CH2_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH2_CONFIG_OFFSET)
HI_SET_GET(hi_ch2_bdq_baddr_base_addr_l,base_addr_l,HI_CH2_BDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch2_bdq_baddr_base_addr,base_addr,HI_CH2_BDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch2_bdq_size_size,size,HI_CH2_BDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch2_bdq_size_reserved,reserved,HI_CH2_BDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch2_bdq_ptr_wptr,wptr,HI_CH2_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch2_bdq_ptr_reserved_1,reserved_1,HI_CH2_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch2_bdq_ptr_rptr,rptr,HI_CH2_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch2_bdq_ptr_reserved_0,reserved_0,HI_CH2_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch2_bdq_ptr_ch2_bdq_empty,ch2_bdq_empty,HI_CH2_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch2_bdq_ptr_ch2_bdq_full,ch2_bdq_full,HI_CH2_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch2_bdq_raddr_addr,addr,HI_CH2_BDQ_RADDR_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_RADDR_OFFSET)
HI_SET_GET(hi_ch2_bdq_waddr_addr,addr,HI_CH2_BDQ_WADDR_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_WADDR_OFFSET)
HI_SET_GET(hi_ch2_bd_num_ch2_bd_num,ch2_bd_num,HI_CH2_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_CH2_BD_NUM_OFFSET)
HI_SET_GET(hi_ch2_invalid_bd_num_ch2_invalid_bd_num,ch2_invalid_bd_num,HI_CH2_INVALID_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_CH2_INVALID_BD_NUM_OFFSET)
HI_SET_GET(hi_ch3_softreset_ch_srst,ch_srst,HI_CH3_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH3_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch3_softreset_ch_bdq_clear,ch_bdq_clear,HI_CH3_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH3_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch3_softreset_ch_rdq_clear,ch_rdq_clear,HI_CH3_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH3_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch3_softreset_reserved,reserved,HI_CH3_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH3_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch3_en_ch_en,ch_en,HI_CH3_EN_T,HI_CIPHER_BASE_ADDR, HI_CH3_EN_OFFSET)
HI_SET_GET(hi_ch3_en_reserved,reserved,HI_CH3_EN_T,HI_CIPHER_BASE_ADDR, HI_CH3_EN_OFFSET)
HI_SET_GET(hi_ch3_en_pack_en,pack_en,HI_CH3_EN_T,HI_CIPHER_BASE_ADDR, HI_CH3_EN_OFFSET)
HI_SET_GET(hi_ch3_en_ch_busy,ch_busy,HI_CH3_EN_T,HI_CIPHER_BASE_ADDR, HI_CH3_EN_OFFSET)
HI_SET_GET(hi_ch3_config_iv_sel,iv_sel,HI_CH3_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH3_CONFIG_OFFSET)
HI_SET_GET(hi_ch3_config_iv_num,iv_num,HI_CH3_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH3_CONFIG_OFFSET)
HI_SET_GET(hi_ch3_config_rdq_ctrl,rdq_ctrl,HI_CH3_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH3_CONFIG_OFFSET)
HI_SET_GET(hi_ch3_config_reserved_1,reserved_1,HI_CH3_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH3_CONFIG_OFFSET)
HI_SET_GET(hi_ch3_config_ufield_len,ufield_len,HI_CH3_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH3_CONFIG_OFFSET)
HI_SET_GET(hi_ch3_config_reserved_0,reserved_0,HI_CH3_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH3_CONFIG_OFFSET)
HI_SET_GET(hi_ch3_bdq_baddr_base_addr_l,base_addr_l,HI_CH3_BDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch3_bdq_baddr_base_addr,base_addr,HI_CH3_BDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch3_bdq_size_size,size,HI_CH3_BDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch3_bdq_size_reserved,reserved,HI_CH3_BDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch3_bdq_ptr_wptr,wptr,HI_CH3_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch3_bdq_ptr_reserved_1,reserved_1,HI_CH3_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch3_bdq_ptr_rptr,rptr,HI_CH3_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch3_bdq_ptr_reserved_0,reserved_0,HI_CH3_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch3_bdq_ptr_ch3_bdq_empty,ch3_bdq_empty,HI_CH3_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch3_bdq_ptr_ch3_bdq_full,ch3_bdq_full,HI_CH3_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch3_bdq_raddr_addr,addr,HI_CH3_BDQ_RADDR_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_RADDR_OFFSET)
HI_SET_GET(hi_ch3_bdq_waddr_addr,addr,HI_CH3_BDQ_WADDR_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_WADDR_OFFSET)
HI_SET_GET(hi_ch3_bd_num_ch3_bd_num,ch3_bd_num,HI_CH3_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_CH3_BD_NUM_OFFSET)
HI_SET_GET(hi_ch3_invalid_bd_num_ch3_invalid_bd_num,ch3_invalid_bd_num,HI_CH3_INVALID_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_CH3_INVALID_BD_NUM_OFFSET)
HI_SET_GET(hi_ch4_softreset_ch_srst,ch_srst,HI_CH4_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH4_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch4_softreset_ch_bdq_clear,ch_bdq_clear,HI_CH4_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH4_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch4_softreset_ch_rdq_clear,ch_rdq_clear,HI_CH4_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH4_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch4_softreset_reserved,reserved,HI_CH4_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH4_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch4_en_ch_en,ch_en,HI_CH4_EN_T,HI_CIPHER_BASE_ADDR, HI_CH4_EN_OFFSET)
HI_SET_GET(hi_ch4_en_reserved,reserved,HI_CH4_EN_T,HI_CIPHER_BASE_ADDR, HI_CH4_EN_OFFSET)
HI_SET_GET(hi_ch4_en_pack_en,pack_en,HI_CH4_EN_T,HI_CIPHER_BASE_ADDR, HI_CH4_EN_OFFSET)
HI_SET_GET(hi_ch4_en_ch_busy,ch_busy,HI_CH4_EN_T,HI_CIPHER_BASE_ADDR, HI_CH4_EN_OFFSET)
HI_SET_GET(hi_ch4_config_iv_sel,iv_sel,HI_CH4_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH4_CONFIG_OFFSET)
HI_SET_GET(hi_ch4_config_iv_num,iv_num,HI_CH4_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH4_CONFIG_OFFSET)
HI_SET_GET(hi_ch4_config_rdq_ctrl,rdq_ctrl,HI_CH4_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH4_CONFIG_OFFSET)
HI_SET_GET(hi_ch4_config_reserved_1,reserved_1,HI_CH4_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH4_CONFIG_OFFSET)
HI_SET_GET(hi_ch4_config_ufield_len,ufield_len,HI_CH4_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH4_CONFIG_OFFSET)
HI_SET_GET(hi_ch4_config_reserved_0,reserved_0,HI_CH4_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH4_CONFIG_OFFSET)
HI_SET_GET(hi_ch4_bdq_baddr_base_addr_l,base_addr_l,HI_CH4_BDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch4_bdq_baddr_base_addr,base_addr,HI_CH4_BDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch4_bdq_size_size,size,HI_CH4_BDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch4_bdq_size_reserved,reserved,HI_CH4_BDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch4_bdq_ptr_wptr,wptr,HI_CH4_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch4_bdq_ptr_reserved_1,reserved_1,HI_CH4_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch4_bdq_ptr_rptr,rptr,HI_CH4_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch4_bdq_ptr_reserved_0,reserved_0,HI_CH4_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch4_bdq_ptr_ch4_bdq_empty,ch4_bdq_empty,HI_CH4_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch4_bdq_ptr_ch4_bdq_full,ch4_bdq_full,HI_CH4_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch4_bdq_raddr_addr,addr,HI_CH4_BDQ_RADDR_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_RADDR_OFFSET)
HI_SET_GET(hi_ch4_bdq_waddr_addr,addr,HI_CH4_BDQ_WADDR_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_WADDR_OFFSET)
HI_SET_GET(hi_ch4_bd_num_ch4_bd_num,ch4_bd_num,HI_CH4_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_CH4_BD_NUM_OFFSET)
HI_SET_GET(hi_ch4_invalid_bd_num_ch4_invalid_bd_num,ch4_invalid_bd_num,HI_CH4_INVALID_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_CH4_INVALID_BD_NUM_OFFSET)
HI_SET_GET(hi_ch5_softreset_ch_srst,ch_srst,HI_CH5_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH5_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch5_softreset_ch_bdq_clear,ch_bdq_clear,HI_CH5_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH5_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch5_softreset_ch_rdq_clear,ch_rdq_clear,HI_CH5_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH5_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch5_softreset_reserved,reserved,HI_CH5_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH5_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch5_en_ch_en,ch_en,HI_CH5_EN_T,HI_CIPHER_BASE_ADDR, HI_CH5_EN_OFFSET)
HI_SET_GET(hi_ch5_en_reserved,reserved,HI_CH5_EN_T,HI_CIPHER_BASE_ADDR, HI_CH5_EN_OFFSET)
HI_SET_GET(hi_ch5_en_pack_en,pack_en,HI_CH5_EN_T,HI_CIPHER_BASE_ADDR, HI_CH5_EN_OFFSET)
HI_SET_GET(hi_ch5_en_ch_busy,ch_busy,HI_CH5_EN_T,HI_CIPHER_BASE_ADDR, HI_CH5_EN_OFFSET)
HI_SET_GET(hi_ch5_config_iv_sel,iv_sel,HI_CH5_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH5_CONFIG_OFFSET)
HI_SET_GET(hi_ch5_config_iv_num,iv_num,HI_CH5_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH5_CONFIG_OFFSET)
HI_SET_GET(hi_ch5_config_rdq_ctrl,rdq_ctrl,HI_CH5_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH5_CONFIG_OFFSET)
HI_SET_GET(hi_ch5_config_reserved_1,reserved_1,HI_CH5_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH5_CONFIG_OFFSET)
HI_SET_GET(hi_ch5_config_ufield_len,ufield_len,HI_CH5_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH5_CONFIG_OFFSET)
HI_SET_GET(hi_ch5_config_reserved_0,reserved_0,HI_CH5_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH5_CONFIG_OFFSET)
HI_SET_GET(hi_ch5_bdq_baddr_base_addr_l,base_addr_l,HI_CH5_BDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH5_BDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch5_bdq_baddr_base_addr,base_addr,HI_CH5_BDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH5_BDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch5_bdq_size_size,size,HI_CH5_BDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH5_BDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch5_bdq_size_reserved,reserved,HI_CH5_BDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH5_BDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch5_bdq_ptr_wptr,wptr,HI_CH5_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH5_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch5_bdq_ptr_reserved_1,reserved_1,HI_CH5_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH5_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch5_bdq_ptr_rptr,rptr,HI_CH5_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH5_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch5_bdq_ptr_reserved_0,reserved_0,HI_CH5_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH5_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch5_bdq_ptr_ch_bdq_empty,ch_bdq_empty,HI_CH5_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH5_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch5_bdq_ptr_ch_bdq_full,ch_bdq_full,HI_CH5_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH5_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch5_bdq_raddr_addr,addr,HI_CH5_BDQ_RADDR_T,HI_CIPHER_BASE_ADDR, HI_CH5_BDQ_RADDR_OFFSET)
HI_SET_GET(hi_ch5_bdq_waddr_addr,addr,HI_CH5_BDQ_WADDR_T,HI_CIPHER_BASE_ADDR, HI_CH5_BDQ_WADDR_OFFSET)
HI_SET_GET(hi_ch5_bd_num_ch_bd_num,ch_bd_num,HI_CH5_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_CH5_BD_NUM_OFFSET)
HI_SET_GET(hi_ch5_invalid_bd_num_ch_invalid_bd_num,ch_invalid_bd_num,HI_CH5_INVALID_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_CH5_INVALID_BD_NUM_OFFSET)
HI_SET_GET(hi_ch6_softreset_ch_srst,ch_srst,HI_CH6_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH6_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch6_softreset_ch_bdq_clear,ch_bdq_clear,HI_CH6_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH6_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch6_softreset_ch_rdq_clear,ch_rdq_clear,HI_CH6_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH6_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch6_softreset_reserved,reserved,HI_CH6_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH6_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch6_en_ch_en,ch_en,HI_CH6_EN_T,HI_CIPHER_BASE_ADDR, HI_CH6_EN_OFFSET)
HI_SET_GET(hi_ch6_en_reserved,reserved,HI_CH6_EN_T,HI_CIPHER_BASE_ADDR, HI_CH6_EN_OFFSET)
HI_SET_GET(hi_ch6_en_pack_en,pack_en,HI_CH6_EN_T,HI_CIPHER_BASE_ADDR, HI_CH6_EN_OFFSET)
HI_SET_GET(hi_ch6_en_ch_busy,ch_busy,HI_CH6_EN_T,HI_CIPHER_BASE_ADDR, HI_CH6_EN_OFFSET)
HI_SET_GET(hi_ch6_config_iv_sel,iv_sel,HI_CH6_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH6_CONFIG_OFFSET)
HI_SET_GET(hi_ch6_config_iv_num,iv_num,HI_CH6_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH6_CONFIG_OFFSET)
HI_SET_GET(hi_ch6_config_rdq_ctrl,rdq_ctrl,HI_CH6_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH6_CONFIG_OFFSET)
HI_SET_GET(hi_ch6_config_reserved_1,reserved_1,HI_CH6_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH6_CONFIG_OFFSET)
HI_SET_GET(hi_ch6_config_ufield_len,ufield_len,HI_CH6_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH6_CONFIG_OFFSET)
HI_SET_GET(hi_ch6_config_reserved_0,reserved_0,HI_CH6_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH6_CONFIG_OFFSET)
HI_SET_GET(hi_ch6_bdq_baddr_base_addr_l,base_addr_l,HI_CH6_BDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH6_BDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch6_bdq_baddr_base_addr,base_addr,HI_CH6_BDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH6_BDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch6_bdq_size_size,size,HI_CH6_BDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH6_BDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch6_bdq_size_reserved,reserved,HI_CH6_BDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH6_BDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch6_bdq_ptr_wptr,wptr,HI_CH6_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH6_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch6_bdq_ptr_reserved_1,reserved_1,HI_CH6_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH6_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch6_bdq_ptr_rptr,rptr,HI_CH6_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH6_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch6_bdq_ptr_reserved_0,reserved_0,HI_CH6_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH6_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch6_bdq_ptr_ch6_bdq_empty,ch6_bdq_empty,HI_CH6_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH6_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch6_bdq_ptr_ch6_bdq_full,ch6_bdq_full,HI_CH6_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH6_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch6_bdq_raddr_addr,addr,HI_CH6_BDQ_RADDR_T,HI_CIPHER_BASE_ADDR, HI_CH6_BDQ_RADDR_OFFSET)
HI_SET_GET(hi_ch6_bdq_waddr_addr,addr,HI_CH6_BDQ_WADDR_T,HI_CIPHER_BASE_ADDR, HI_CH6_BDQ_WADDR_OFFSET)
HI_SET_GET(hi_ch6_bd_num_ch6_bd_num,ch6_bd_num,HI_CH6_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_CH6_BD_NUM_OFFSET)
HI_SET_GET(hi_ch6_invalid_bd_num_ch6_invalid_bd_num,ch6_invalid_bd_num,HI_CH6_INVALID_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_CH6_INVALID_BD_NUM_OFFSET)
HI_SET_GET(hi_ch_int_pkt_interval_ch0_pkt_num,ch0_pkt_num,HI_CH_INT_PKT_INTERVAL_T,HI_CIPHER_BASE_ADDR, HI_CH_INT_PKT_INTERVAL_OFFSET)
HI_SET_GET(hi_ch_int_pkt_interval_ch1_pkt_num,ch1_pkt_num,HI_CH_INT_PKT_INTERVAL_T,HI_CIPHER_BASE_ADDR, HI_CH_INT_PKT_INTERVAL_OFFSET)
HI_SET_GET(hi_ch_int_pkt_interval_ch2_pkt_num,ch2_pkt_num,HI_CH_INT_PKT_INTERVAL_T,HI_CIPHER_BASE_ADDR, HI_CH_INT_PKT_INTERVAL_OFFSET)
HI_SET_GET(hi_ch_int_pkt_interval_ch3_pkt_num,ch3_pkt_num,HI_CH_INT_PKT_INTERVAL_T,HI_CIPHER_BASE_ADDR, HI_CH_INT_PKT_INTERVAL_OFFSET)
HI_SET_GET(hi_ch_int_pkt_interval_ch5_pkt_num,ch5_pkt_num,HI_CH_INT_PKT_INTERVAL_T,HI_CIPHER_BASE_ADDR, HI_CH_INT_PKT_INTERVAL_OFFSET)
HI_SET_GET(hi_ch_int_pkt_interval_ch6_pkt_num,ch6_pkt_num,HI_CH_INT_PKT_INTERVAL_T,HI_CIPHER_BASE_ADDR, HI_CH_INT_PKT_INTERVAL_OFFSET)
HI_SET_GET(hi_ch_int_pkt_interval_ch4_pkt_num,ch4_pkt_num,HI_CH_INT_PKT_INTERVAL_T,HI_CIPHER_BASE_ADDR, HI_CH_INT_PKT_INTERVAL_OFFSET)
HI_SET_GET(hi_ch_int_pkt_interval_reserved,reserved,HI_CH_INT_PKT_INTERVAL_T,HI_CIPHER_BASE_ADDR, HI_CH_INT_PKT_INTERVAL_OFFSET)
HI_SET_GET(hi_cipher_int_status_cipher_int0,cipher_int0,HI_CIPHER_INT_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int_status_cipher_int1,cipher_int1,HI_CIPHER_INT_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int_status_cipher_int2,cipher_int2,HI_CIPHER_INT_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int_status_cipher_int3,cipher_int3,HI_CIPHER_INT_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int_status_cipher_int4,cipher_int4,HI_CIPHER_INT_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int_status_reserved,reserved,HI_CIPHER_INT_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch0_bdq_full,ch0_bdq_full,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch0_rdq_full,ch0_rdq_full,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch0_nbd_done,ch0_nbd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch0_bd_done,ch0_bd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch0_allbd_done,ch0_allbd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch0_integrity_err,ch0_integrity_err,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_reserved_3,reserved_3,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch1_bdq_full,ch1_bdq_full,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch1_rdq_full,ch1_rdq_full,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch1_nbd_done,ch1_nbd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch1_bd_done,ch1_bd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch1_allbd_done,ch1_allbd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch1_integrity_err,ch1_integrity_err,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_reserved_2,reserved_2,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch2_bdq_full,ch2_bdq_full,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch2_rdq_full,ch2_rdq_full,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch2_nbd_done,ch2_nbd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch2_bd_done,ch2_bd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch2_allbd_done,ch2_allbd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch2_integrity_err,ch2_integrity_err,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_reserved_1,reserved_1,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch3_bdq_full,ch3_bdq_full,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch3_rdq_full,ch3_rdq_full,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch3_nbd_done,ch3_nbd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch3_bd_done,ch3_bd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch3_allbd_done,ch3_allbd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch3_integrity_err,ch3_integrity_err,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_reserved_0,reserved_0,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_mask_int0_mask,int0_mask,HI_CIPHER_INT0_MASK_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_MASK_OFFSET)
HI_SET_GET(hi_cipher_int0_mstatus_int0_mstatus,int0_mstatus,HI_CIPHER_INT0_MSTATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_MSTATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch0_bdq_empty,ch0_bdq_empty,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch0_rdq_empty,ch0_rdq_empty,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch0_timeout,ch0_timeout,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_reserved_3,reserved_3,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch1_bdq_empty,ch1_bdq_empty,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch1_rdq_empty,ch1_rdq_empty,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch1_timeout,ch1_timeout,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_reserved_2,reserved_2,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch2_bdq_empty,ch2_bdq_empty,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch2_rdq_empty,ch2_rdq_empty,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch2_timeout,ch2_timeout,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_reserved_1,reserved_1,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch3_bdq_empty,ch3_bdq_empty,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch3_rdq_empty,ch3_rdq_empty,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch3_timeout,ch3_timeout,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_reserved_0,reserved_0,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_mask_int1_mask,int1_mask,HI_CIPHER_INT1_MASK_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_MASK_OFFSET)
HI_SET_GET(hi_cipher_int1_mstatus_int1_mstatus,int1_mstatus,HI_CIPHER_INT1_MSTATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_MSTATUS_OFFSET)
HI_SET_GET(hi_cipher_int2_status_ch4_bdq_full,ch4_bdq_full,HI_CIPHER_INT2_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT2_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int2_status_ch4_rdq_full,ch4_rdq_full,HI_CIPHER_INT2_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT2_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int2_status_ch4_nbd_done,ch4_nbd_done,HI_CIPHER_INT2_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT2_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int2_status_ch4_bd_done,ch4_bd_done,HI_CIPHER_INT2_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT2_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int2_status_ch4_allbd_done,ch4_allbd_done,HI_CIPHER_INT2_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT2_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int2_status_ch4_bdq_empty,ch4_bdq_empty,HI_CIPHER_INT2_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT2_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int2_status_ch4_rdq_empty,ch4_rdq_empty,HI_CIPHER_INT2_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT2_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int2_status_ch4_timeout,ch4_timeout,HI_CIPHER_INT2_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT2_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int2_status_reserved,reserved,HI_CIPHER_INT2_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT2_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int2_mask_reserved,reserved,HI_CIPHER_INT2_MASK_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT2_MASK_OFFSET)
HI_SET_GET(hi_cipher_int2_mstatus_reserved,reserved,HI_CIPHER_INT2_MSTATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT2_MSTATUS_OFFSET)
HI_SET_GET(hi_cipher_debug21_reserved,reserved,HI_CIPHER_DEBUG21_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG21_OFFSET)
HI_SET_GET(hi_cipher_debug22_reserved,reserved,HI_CIPHER_DEBUG22_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG22_OFFSET)
HI_SET_GET(hi_cipher_debug23_reserved,reserved,HI_CIPHER_DEBUG23_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG23_OFFSET)
HI_SET_GET(hi_cipher_debug24_reserved,reserved,HI_CIPHER_DEBUG24_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG24_OFFSET)
HI_SET_GET(hi_cipher_debug25_reserved,reserved,HI_CIPHER_DEBUG25_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG25_OFFSET)
HI_SET_GET(hi_cipher_debug26_reserved,reserved,HI_CIPHER_DEBUG26_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG26_OFFSET)
HI_SET_GET(hi_cipher_int3_status_ch5_bdq_full,ch5_bdq_full,HI_CIPHER_INT3_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT3_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int3_status_ch5_rdq_full,ch5_rdq_full,HI_CIPHER_INT3_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT3_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int3_status_ch5_nbd_done,ch5_nbd_done,HI_CIPHER_INT3_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT3_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int3_status_ch5_bd_done,ch5_bd_done,HI_CIPHER_INT3_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT3_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int3_status_ch5_allbd_done,ch5_allbd_done,HI_CIPHER_INT3_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT3_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int3_status_ch5_integrity_err,ch5_integrity_err,HI_CIPHER_INT3_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT3_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int3_status_reserved_1,reserved_1,HI_CIPHER_INT3_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT3_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int3_status_ch6_bdq_full,ch6_bdq_full,HI_CIPHER_INT3_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT3_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int3_status_ch6_rdq_full,ch6_rdq_full,HI_CIPHER_INT3_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT3_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int3_status_ch6_nbd_done,ch6_nbd_done,HI_CIPHER_INT3_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT3_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int3_status_ch6_bd_done,ch6_bd_done,HI_CIPHER_INT3_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT3_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int3_status_ch6_allbd_done,ch6_allbd_done,HI_CIPHER_INT3_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT3_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int3_status_ch6_integrity_err,ch6_integrity_err,HI_CIPHER_INT3_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT3_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int3_status_reserved_0,reserved_0,HI_CIPHER_INT3_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT3_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int3_mask_int0_mask,int0_mask,HI_CIPHER_INT3_MASK_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT3_MASK_OFFSET)
HI_SET_GET(hi_cipher_int3_mstatus_int0_mstatus,int0_mstatus,HI_CIPHER_INT3_MSTATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT3_MSTATUS_OFFSET)
HI_SET_GET(hi_cipher_int4_status_ch5_bdq_empty,ch5_bdq_empty,HI_CIPHER_INT4_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT4_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int4_status_ch5_rdq_empty,ch5_rdq_empty,HI_CIPHER_INT4_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT4_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int4_status_ch5_timeout,ch5_timeout,HI_CIPHER_INT4_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT4_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int4_status_reserved_1,reserved_1,HI_CIPHER_INT4_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT4_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int4_status_ch6_bdq_empty,ch6_bdq_empty,HI_CIPHER_INT4_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT4_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int4_status_ch6_rdq_empty,ch6_rdq_empty,HI_CIPHER_INT4_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT4_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int4_status_ch6_timeout,ch6_timeout,HI_CIPHER_INT4_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT4_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int4_status_reserved_0,reserved_0,HI_CIPHER_INT4_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT4_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int4_mask_int1_mask,int1_mask,HI_CIPHER_INT4_MASK_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT4_MASK_OFFSET)
HI_SET_GET(hi_cipher_int4_mstatus_int1_mstatus,int1_mstatus,HI_CIPHER_INT4_MSTATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT4_MSTATUS_OFFSET)
HI_SET_GET(hi_timeout_timeout_time,timeout_time,HI_TIMEOUT_T,HI_CIPHER_BASE_ADDR, HI_TIMEOUT_OFFSET)
HI_SET_GET(hi_timeout_reserved,reserved,HI_TIMEOUT_T,HI_CIPHER_BASE_ADDR, HI_TIMEOUT_OFFSET)
HI_SET_GET(hi_ch0_rdq_baddr_base_addr_l,base_addr_l,HI_CH0_RDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH0_RDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch0_rdq_baddr_base_addr,base_addr,HI_CH0_RDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH0_RDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch0_rdq_size_size,size,HI_CH0_RDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH0_RDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch0_rdq_size_reserved,reserved,HI_CH0_RDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH0_RDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch0_rdq_ptr_wptr,wptr,HI_CH0_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH0_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch0_rdq_ptr_reserved_1,reserved_1,HI_CH0_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH0_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch0_rdq_ptr_rptr,rptr,HI_CH0_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH0_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch0_rdq_ptr_reserved_0,reserved_0,HI_CH0_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH0_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch0_rdq_raddr_raddr,raddr,HI_CH0_RDQ_RADDR_T,HI_CIPHER_BASE_ADDR, HI_CH0_RDQ_RADDR_OFFSET)
HI_SET_GET(hi_ch0_rdq_waddr_waddr,waddr,HI_CH0_RDQ_WADDR_T,HI_CIPHER_BASE_ADDR, HI_CH0_RDQ_WADDR_OFFSET)
HI_SET_GET(hi_ch1_rdq_baddr_base_addr_l,base_addr_l,HI_CH1_RDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH1_RDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch1_rdq_baddr_base_addr,base_addr,HI_CH1_RDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH1_RDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch1_rdq_size_size,size,HI_CH1_RDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH1_RDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch1_rdq_size_reserved,reserved,HI_CH1_RDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH1_RDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch1_rdq_ptr_wptr,wptr,HI_CH1_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH1_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch1_rdq_ptr_reserved_1,reserved_1,HI_CH1_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH1_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch1_rdq_ptr_rptr,rptr,HI_CH1_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH1_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch1_rdq_ptr_reserved_0,reserved_0,HI_CH1_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH1_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch1_rdq_raddr_raddr,raddr,HI_CH1_RDQ_RADDR_T,HI_CIPHER_BASE_ADDR, HI_CH1_RDQ_RADDR_OFFSET)
HI_SET_GET(hi_ch1_rdq_waddr_waddr,waddr,HI_CH1_RDQ_WADDR_T,HI_CIPHER_BASE_ADDR, HI_CH1_RDQ_WADDR_OFFSET)
HI_SET_GET(hi_ch2_rdq_baddr_base_addr_l,base_addr_l,HI_CH2_RDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH2_RDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch2_rdq_baddr_base_addr,base_addr,HI_CH2_RDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH2_RDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch2_rdq_size_size,size,HI_CH2_RDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH2_RDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch2_rdq_size_reserved,reserved,HI_CH2_RDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH2_RDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch2_rdq_ptr_wptr,wptr,HI_CH2_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH2_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch2_rdq_ptr_reserved_1,reserved_1,HI_CH2_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH2_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch2_rdq_ptr_rptr,rptr,HI_CH2_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH2_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch2_rdq_ptr_reserved_0,reserved_0,HI_CH2_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH2_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch2_rdq_raddr_raddr,raddr,HI_CH2_RDQ_RADDR_T,HI_CIPHER_BASE_ADDR, HI_CH2_RDQ_RADDR_OFFSET)
HI_SET_GET(hi_ch2_rdq_waddr_waddr,waddr,HI_CH2_RDQ_WADDR_T,HI_CIPHER_BASE_ADDR, HI_CH2_RDQ_WADDR_OFFSET)
HI_SET_GET(hi_ch3_rdq_baddr_base_addr_l,base_addr_l,HI_CH3_RDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH3_RDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch3_rdq_baddr_base_addr,base_addr,HI_CH3_RDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH3_RDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch3_rdq_size_size,size,HI_CH3_RDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH3_RDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch3_rdq_size_reserved,reserved,HI_CH3_RDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH3_RDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch3_rdq_ptr_wptr,wptr,HI_CH3_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH3_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch3_rdq_ptr_reserved_1,reserved_1,HI_CH3_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH3_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch3_rdq_ptr_rptr,rptr,HI_CH3_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH3_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch3_rdq_ptr_reserved_0,reserved_0,HI_CH3_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH3_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch3_rdq_raddr_raddr,raddr,HI_CH3_RDQ_RADDR_T,HI_CIPHER_BASE_ADDR, HI_CH3_RDQ_RADDR_OFFSET)
HI_SET_GET(hi_ch3_rdq_waddr_waddr,waddr,HI_CH3_RDQ_WADDR_T,HI_CIPHER_BASE_ADDR, HI_CH3_RDQ_WADDR_OFFSET)
HI_SET_GET(hi_ch4_rdq_baddr_base_addr_l,base_addr_l,HI_CH4_RDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH4_RDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch4_rdq_baddr_base_addr,base_addr,HI_CH4_RDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH4_RDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch4_rdq_size_size,size,HI_CH4_RDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH4_RDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch4_rdq_size_reserved,reserved,HI_CH4_RDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH4_RDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch4_rdq_ptr_wptr,wptr,HI_CH4_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH4_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch4_rdq_ptr_reserved_1,reserved_1,HI_CH4_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH4_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch4_rdq_ptr_rptr,rptr,HI_CH4_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH4_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch4_rdq_ptr_reserved_0,reserved_0,HI_CH4_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH4_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch4_rdq_raddr_raddr,raddr,HI_CH4_RDQ_RADDR_T,HI_CIPHER_BASE_ADDR, HI_CH4_RDQ_RADDR_OFFSET)
HI_SET_GET(hi_ch4_rdq_waddr_waddr,waddr,HI_CH4_RDQ_WADDR_T,HI_CIPHER_BASE_ADDR, HI_CH4_RDQ_WADDR_OFFSET)
HI_SET_GET(hi_ch5_rdq_baddr_base_addr_l,base_addr_l,HI_CH5_RDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH5_RDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch5_rdq_baddr_base_addr,base_addr,HI_CH5_RDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH5_RDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch5_rdq_size_size,size,HI_CH5_RDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH5_RDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch5_rdq_size_reserved,reserved,HI_CH5_RDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH5_RDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch5_rdq_ptr_wptr,wptr,HI_CH5_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH5_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch5_rdq_ptr_reserved_1,reserved_1,HI_CH5_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH5_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch5_rdq_ptr_rptr,rptr,HI_CH5_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH5_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch5_rdq_ptr_reserved_0,reserved_0,HI_CH5_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH5_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch5_rdq_raddr_raddr,raddr,HI_CH5_RDQ_RADDR_T,HI_CIPHER_BASE_ADDR, HI_CH5_RDQ_RADDR_OFFSET)
HI_SET_GET(hi_ch5_rdq_waddr_waddr,waddr,HI_CH5_RDQ_WADDR_T,HI_CIPHER_BASE_ADDR, HI_CH5_RDQ_WADDR_OFFSET)
HI_SET_GET(hi_ch6_rdq_baddr_base_addr_l,base_addr_l,HI_CH6_RDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH6_RDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch6_rdq_baddr_base_addr,base_addr,HI_CH6_RDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH6_RDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch6_rdq_size_size,size,HI_CH6_RDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH6_RDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch6_rdq_size_reserved,reserved,HI_CH6_RDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH6_RDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch6_rdq_ptr_wptr,wptr,HI_CH6_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH6_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch6_rdq_ptr_reserved_1,reserved_1,HI_CH6_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH6_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch6_rdq_ptr_rptr,rptr,HI_CH6_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH6_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch6_rdq_ptr_reserved_0,reserved_0,HI_CH6_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH6_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch6_rdq_raddr_raddr,raddr,HI_CH6_RDQ_RADDR_T,HI_CIPHER_BASE_ADDR, HI_CH6_RDQ_RADDR_OFFSET)
HI_SET_GET(hi_ch6_rdq_waddr_waddr,waddr,HI_CH6_RDQ_WADDR_T,HI_CIPHER_BASE_ADDR, HI_CH6_RDQ_WADDR_OFFSET)
HI_SET_GET(hi_key_ram_key,key,HI_KEY_RAM_T,HI_CIPHER_BASE_ADDR, HI_KEY_RAM_OFFSET)
#endif
#endif // __HI_CIPHER_H__

