/*
 * hi3630_asp_dma.h -- ALSA SoC HI3630 ASP DMA driver
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __HI3630_DMA_H__
#define __HI3630_DMA_H__

/* HI3630_DMAC base addr */

/******************************************************************************/
#define HI3630_DMAC_INT_STAT_0_REG                   (0x0)
#define HI3630_DMAC_INT_STAT_1_REG                   (0x40)
#define HI3630_DMAC_INT_TC1_0_REG                    (0x4)
#define HI3630_DMAC_INT_TC1_1_REG                    (0x44)
#define HI3630_DMAC_INT_TC2_0_REG                    (0x8)
#define HI3630_DMAC_INT_TC2_1_REG                    (0x48)
#define HI3630_DMAC_INT_ERR1_0_REG                   (0xC)
#define HI3630_DMAC_INT_ERR1_1_REG                   (0x4C)
#define HI3630_DMAC_INT_ERR2_0_REG                   (0x10)
#define HI3630_DMAC_INT_ERR2_1_REG                   (0x50)
#define HI3630_DMAC_INT_ERR3_0_REG                   (0x14)
#define HI3630_DMAC_INT_ERR3_1_REG                   (0x54)
#define HI3630_DMAC_INT_TC1_MASK_0_REG               (0x18)
#define HI3630_DMAC_INT_TC1_MASK_1_REG               (0x58)
#define HI3630_DMAC_INT_TC2_MASK_0_REG               (0x1C)
#define HI3630_DMAC_INT_TC2_MASK_1_REG               (0x5C)
#define HI3630_DMAC_INT_ERR1_MASK_0_REG              (0x20)
#define HI3630_DMAC_INT_ERR1_MASK_1_REG              (0x60)
#define HI3630_DMAC_INT_ERR2_MASK_0_REG              (0x24)
#define HI3630_DMAC_INT_ERR2_MASK_1_REG              (0x64)
#define HI3630_DMAC_INT_ERR3_MASK_0_REG              (0x28)
#define HI3630_DMAC_INT_ERR3_MASK_1_REG              (0x68)
#define HI3630_DMAC_INT_TC1_RAW_REG                  (0x600)
#define HI3630_DMAC_INT_TC2_RAW_REG                  (0x608)
#define HI3630_DMAC_INT_ERR1_RAW_REG                 (0x610)
#define HI3630_DMAC_INT_ERR2_RAW_REG                 (0x618)
#define HI3630_DMAC_INT_ERR3_RAW_REG                 (0x620)
#define HI3630_DMAC_SREQ_REG                         (0x660)
#define HI3630_DMAC_LSREQ_REG                        (0x664)
#define HI3630_DMAC_BREQ_REG                         (0x668)
#define HI3630_DMAC_LBREQ_REG                        (0x66C)
#define HI3630_DMAC_FREQ_REG                         (0x670)
#define HI3630_DMAC_LFREQ_REG                        (0x674)
#define HI3630_DMAC_CH_PRI_REG                       (0x688)
#define HI3630_DMAC_CH_STAT_REG                      (0x690)
#define HI3630_DMAC_SEC_CTRL_REG                     (0x694)
#define HI3630_DMAC_DMA_CTRL_REG                     (0x698)
#define HI3630_DMAC_CX_CURR_CNT1_0_REG               (0x700)
#define HI3630_DMAC_CX_CURR_CNT1_1_REG               (0x710)
#define HI3630_DMAC_CX_CURR_CNT1_2_REG               (0x720)
#define HI3630_DMAC_CX_CURR_CNT1_3_REG               (0x730)
#define HI3630_DMAC_CX_CURR_CNT1_4_REG               (0x740)
#define HI3630_DMAC_CX_CURR_CNT1_5_REG               (0x750)
#define HI3630_DMAC_CX_CURR_CNT1_6_REG               (0x760)
#define HI3630_DMAC_CX_CURR_CNT1_7_REG               (0x770)
#define HI3630_DMAC_CX_CURR_CNT1_8_REG               (0x780)
#define HI3630_DMAC_CX_CURR_CNT1_9_REG               (0x790)
#define HI3630_DMAC_CX_CURR_CNT1_10_REG              (0x7A0)
#define HI3630_DMAC_CX_CURR_CNT1_11_REG              (0x7B0)
#define HI3630_DMAC_CX_CURR_CNT0_0_REG               (0x704)
#define HI3630_DMAC_CX_CURR_CNT0_1_REG               (0x714)
#define HI3630_DMAC_CX_CURR_CNT0_2_REG               (0x724)
#define HI3630_DMAC_CX_CURR_CNT0_3_REG               (0x734)
#define HI3630_DMAC_CX_CURR_CNT0_4_REG               (0x744)
#define HI3630_DMAC_CX_CURR_CNT0_5_REG               (0x754)
#define HI3630_DMAC_CX_CURR_CNT0_6_REG               (0x764)
#define HI3630_DMAC_CX_CURR_CNT0_7_REG               (0x774)
#define HI3630_DMAC_CX_CURR_CNT0_8_REG               (0x784)
#define HI3630_DMAC_CX_CURR_CNT0_9_REG               (0x794)
#define HI3630_DMAC_CX_CURR_CNT0_10_REG              (0x7A4)
#define HI3630_DMAC_CX_CURR_CNT0_11_REG              (0x7B4)
#define HI3630_DMAC_CX_CURR_SRC_ADDR_0_REG           (0x708)
#define HI3630_DMAC_CX_CURR_SRC_ADDR_1_REG           (0x718)
#define HI3630_DMAC_CX_CURR_SRC_ADDR_2_REG           (0x728)
#define HI3630_DMAC_CX_CURR_SRC_ADDR_3_REG           (0x738)
#define HI3630_DMAC_CX_CURR_SRC_ADDR_4_REG           (0x748)
#define HI3630_DMAC_CX_CURR_SRC_ADDR_5_REG           (0x758)
#define HI3630_DMAC_CX_CURR_SRC_ADDR_6_REG           (0x768)
#define HI3630_DMAC_CX_CURR_SRC_ADDR_7_REG           (0x778)
#define HI3630_DMAC_CX_CURR_SRC_ADDR_8_REG           (0x788)
#define HI3630_DMAC_CX_CURR_SRC_ADDR_9_REG           (0x798)
#define HI3630_DMAC_CX_CURR_SRC_ADDR_10_REG          (0x7A8)
#define HI3630_DMAC_CX_CURR_SRC_ADDR_11_REG          (0x7B8)
#define HI3630_DMAC_CX_CURR_DES_ADDR_0_REG           (0x70C)
#define HI3630_DMAC_CX_CURR_DES_ADDR_1_REG           (0x71C)
#define HI3630_DMAC_CX_CURR_DES_ADDR_2_REG           (0x72C)
#define HI3630_DMAC_CX_CURR_DES_ADDR_3_REG           (0x73C)
#define HI3630_DMAC_CX_CURR_DES_ADDR_4_REG           (0x74C)
#define HI3630_DMAC_CX_CURR_DES_ADDR_5_REG           (0x75C)
#define HI3630_DMAC_CX_CURR_DES_ADDR_6_REG           (0x76C)
#define HI3630_DMAC_CX_CURR_DES_ADDR_7_REG           (0x77C)
#define HI3630_DMAC_CX_CURR_DES_ADDR_8_REG           (0x78C)
#define HI3630_DMAC_CX_CURR_DES_ADDR_9_REG           (0x79C)
#define HI3630_DMAC_CX_CURR_DES_ADDR_10_REG          (0x7AC)
#define HI3630_DMAC_CX_CURR_DES_ADDR_11_REG          (0x7BC)
#define HI3630_DMAC_CX_LLI_0_REG                     (0x800)
#define HI3630_DMAC_CX_LLI_1_REG                     (0x840)
#define HI3630_DMAC_CX_LLI_2_REG                     (0x880)
#define HI3630_DMAC_CX_LLI_3_REG                     (0x8C0)
#define HI3630_DMAC_CX_LLI_4_REG                     (0x900)
#define HI3630_DMAC_CX_LLI_5_REG                     (0x940)
#define HI3630_DMAC_CX_LLI_6_REG                     (0x980)
#define HI3630_DMAC_CX_LLI_7_REG                     (0x9C0)
#define HI3630_DMAC_CX_LLI_8_REG                     (0xA00)
#define HI3630_DMAC_CX_LLI_9_REG                     (0xA40)
#define HI3630_DMAC_CX_LLI_10_REG                    (0xA80)
#define HI3630_DMAC_CX_LLI_11_REG                    (0xAC0)
#define HI3630_DMAC_CX_BINDX_0_REG                   (0x804)
#define HI3630_DMAC_CX_BINDX_1_REG                   (0x844)
#define HI3630_DMAC_CX_BINDX_2_REG                   (0x884)
#define HI3630_DMAC_CX_BINDX_3_REG                   (0x8C4)
#define HI3630_DMAC_CX_BINDX_4_REG                   (0x904)
#define HI3630_DMAC_CX_BINDX_5_REG                   (0x944)
#define HI3630_DMAC_CX_BINDX_6_REG                   (0x984)
#define HI3630_DMAC_CX_BINDX_7_REG                   (0x9C4)
#define HI3630_DMAC_CX_BINDX_8_REG                   (0xA04)
#define HI3630_DMAC_CX_BINDX_9_REG                   (0xA44)
#define HI3630_DMAC_CX_BINDX_10_REG                  (0xA84)
#define HI3630_DMAC_CX_BINDX_11_REG                  (0xAC4)
#define HI3630_DMAC_CX_CINDX_0_REG                   (0x808)
#define HI3630_DMAC_CX_CINDX_1_REG                   (0x848)
#define HI3630_DMAC_CX_CINDX_2_REG                   (0x888)
#define HI3630_DMAC_CX_CINDX_3_REG                   (0x8C8)
#define HI3630_DMAC_CX_CINDX_4_REG                   (0x908)
#define HI3630_DMAC_CX_CINDX_5_REG                   (0x948)
#define HI3630_DMAC_CX_CINDX_6_REG                   (0x988)
#define HI3630_DMAC_CX_CINDX_7_REG                   (0x9C8)
#define HI3630_DMAC_CX_CINDX_8_REG                   (0xA08)
#define HI3630_DMAC_CX_CINDX_9_REG                   (0xA48)
#define HI3630_DMAC_CX_CINDX_10_REG                  (0xA88)
#define HI3630_DMAC_CX_CINDX_11_REG                  (0xAC8)
#define HI3630_DMAC_CX_CNT1_0_REG                    (0x80C)
#define HI3630_DMAC_CX_CNT1_1_REG                    (0x84C)
#define HI3630_DMAC_CX_CNT1_2_REG                    (0x88C)
#define HI3630_DMAC_CX_CNT1_3_REG                    (0x8CC)
#define HI3630_DMAC_CX_CNT1_4_REG                    (0x90C)
#define HI3630_DMAC_CX_CNT1_5_REG                    (0x94C)
#define HI3630_DMAC_CX_CNT1_6_REG                    (0x98C)
#define HI3630_DMAC_CX_CNT1_7_REG                    (0x9CC)
#define HI3630_DMAC_CX_CNT1_8_REG                    (0xA0C)
#define HI3630_DMAC_CX_CNT1_9_REG                    (0xA4C)
#define HI3630_DMAC_CX_CNT1_10_REG                   (0xA8C)
#define HI3630_DMAC_CX_CNT1_11_REG                   (0xACC)
#define HI3630_DMAC_CX_CNT0_0_REG                    (0x810)
#define HI3630_DMAC_CX_CNT0_1_REG                    (0x850)
#define HI3630_DMAC_CX_CNT0_2_REG                    (0x890)
#define HI3630_DMAC_CX_CNT0_3_REG                    (0x8D0)
#define HI3630_DMAC_CX_CNT0_4_REG                    (0x910)
#define HI3630_DMAC_CX_CNT0_5_REG                    (0x950)
#define HI3630_DMAC_CX_CNT0_6_REG                    (0x990)
#define HI3630_DMAC_CX_CNT0_7_REG                    (0x9D0)
#define HI3630_DMAC_CX_CNT0_8_REG                    (0xA10)
#define HI3630_DMAC_CX_CNT0_9_REG                    (0xA50)
#define HI3630_DMAC_CX_CNT0_10_REG                   (0xA90)
#define HI3630_DMAC_CX_CNT0_11_REG                   (0xAD0)
#define HI3630_DMAC_CX_SRC_ADDR_0_REG                (0x814)
#define HI3630_DMAC_CX_SRC_ADDR_1_REG                (0x854)
#define HI3630_DMAC_CX_SRC_ADDR_2_REG                (0x894)
#define HI3630_DMAC_CX_SRC_ADDR_3_REG                (0x8D4)
#define HI3630_DMAC_CX_SRC_ADDR_4_REG                (0x914)
#define HI3630_DMAC_CX_SRC_ADDR_5_REG                (0x954)
#define HI3630_DMAC_CX_SRC_ADDR_6_REG                (0x994)
#define HI3630_DMAC_CX_SRC_ADDR_7_REG                (0x9D4)
#define HI3630_DMAC_CX_SRC_ADDR_8_REG                (0xA14)
#define HI3630_DMAC_CX_SRC_ADDR_9_REG                (0xA54)
#define HI3630_DMAC_CX_SRC_ADDR_10_REG               (0xA94)
#define HI3630_DMAC_CX_SRC_ADDR_11_REG               (0xAD4)
#define HI3630_DMAC_CX_DES_ADDR_0_REG                (0x818)
#define HI3630_DMAC_CX_DES_ADDR_1_REG                (0x858)
#define HI3630_DMAC_CX_DES_ADDR_2_REG                (0x898)
#define HI3630_DMAC_CX_DES_ADDR_3_REG                (0x8D8)
#define HI3630_DMAC_CX_DES_ADDR_4_REG                (0x918)
#define HI3630_DMAC_CX_DES_ADDR_5_REG                (0x958)
#define HI3630_DMAC_CX_DES_ADDR_6_REG                (0x998)
#define HI3630_DMAC_CX_DES_ADDR_7_REG                (0x9D8)
#define HI3630_DMAC_CX_DES_ADDR_8_REG                (0xA18)
#define HI3630_DMAC_CX_DES_ADDR_9_REG                (0xA58)
#define HI3630_DMAC_CX_DES_ADDR_10_REG               (0xA98)
#define HI3630_DMAC_CX_DES_ADDR_11_REG               (0xAD8)
#define HI3630_DMAC_CX_CONFIG_0_REG                  (0x81C)
#define HI3630_DMAC_CX_CONFIG_1_REG                  (0x85C)
#define HI3630_DMAC_CX_CONFIG_2_REG                  (0x89C)
#define HI3630_DMAC_CX_CONFIG_3_REG                  (0x8DC)
#define HI3630_DMAC_CX_CONFIG_4_REG                  (0x91C)
#define HI3630_DMAC_CX_CONFIG_5_REG                  (0x95C)
#define HI3630_DMAC_CX_CONFIG_6_REG                  (0x99C)
#define HI3630_DMAC_CX_CONFIG_7_REG                  (0x9DC)
#define HI3630_DMAC_CX_CONFIG_8_REG                  (0xA1C)
#define HI3630_DMAC_CX_CONFIG_9_REG                  (0xA5C)
#define HI3630_DMAC_CX_CONFIG_10_REG                 (0xA9C)
#define HI3630_DMAC_CX_CONFIG_11_REG                 (0xADC)
#define HI3630_DMAC_CX_AXI_CONF_0_REG                (0x820)
#define HI3630_DMAC_CX_AXI_CONF_1_REG                (0x860)
#define HI3630_DMAC_CX_AXI_CONF_2_REG                (0x8A0)
#define HI3630_DMAC_CX_AXI_CONF_3_REG                (0x8E0)
#define HI3630_DMAC_CX_AXI_CONF_4_REG                (0x920)
#define HI3630_DMAC_CX_AXI_CONF_5_REG                (0x960)
#define HI3630_DMAC_CX_AXI_CONF_6_REG                (0x9A0)
#define HI3630_DMAC_CX_AXI_CONF_7_REG                (0x9E0)
#define HI3630_DMAC_CX_AXI_CONF_8_REG                (0xA20)
#define HI3630_DMAC_CX_AXI_CONF_9_REG                (0xA60)
#define HI3630_DMAC_CX_AXI_CONF_10_REG               (0xAA0)
#define HI3630_DMAC_CX_AXI_CONF_11_REG               (0xAE0)

//******************************************************************************
//REG FIELD
//******************************************************************************
#define ASP_DMAC_INT_STAT_LEN    12
#define ASP_DMAC_INT_STAT_OFFSET 0

#define ASP_DMAC_INT_TC1_LEN    12
#define ASP_DMAC_INT_TC1_OFFSET 0

#define ASP_DMAC_INT_TC2_LEN    12
#define ASP_DMAC_INT_TC2_OFFSET 0

#define ASP_DMAC_INT_ERR1_LEN    12
#define ASP_DMAC_INT_ERR1_OFFSET 0

#define ASP_DMAC_INT_ERR2_LEN    12
#define ASP_DMAC_INT_ERR2_OFFSET 0

#define ASP_DMAC_INT_ERR3_LEN    12
#define ASP_DMAC_INT_ERR3_OFFSET 0
#define ASP_DMAC_INT_TC1_MASK_LEN    12
#define ASP_DMAC_INT_TC1_MASK_OFFSET 0

#define ASP_DMAC_INT_TC2_MASK_LEN    12
#define ASP_DMAC_INT_TC2_MASK_OFFSET 0

#define ASP_DMAC_INT_ERR1_MASK_LEN    12
#define ASP_DMAC_INT_ERR1_MASK_OFFSET 0

#define ASP_DMAC_INT_ERR2_MASK_LEN    12
#define ASP_DMAC_INT_ERR2_MASK_OFFSET 0

#define ASP_DMAC_INT_ERR3_MASK_LEN    12
#define ASP_DMAC_INT_ERR3_MASK_OFFSET 0

#define ASP_DMAC_INT_TC1_RAW_LEN    12
#define ASP_DMAC_INT_TC1_RAW_OFFSET 0
#define ASP_DMAC_INT_TC2_RAW_LEN    12
#define ASP_DMAC_INT_TC2_RAW_OFFSET 0
#define ASP_DMAC_INT_ERR1_RAW_LEN    12
#define ASP_DMAC_INT_ERR1_RAW_OFFSET 0
#define ASP_DMAC_INT_ERR2_RAW_LEN    12
#define ASP_DMAC_INT_ERR2_RAW_OFFSET 0
#define ASP_DMAC_INT_ERR3_RAW_LEN    12
#define ASP_DMAC_INT_ERR3_RAW_OFFSET 0

#define ASP_DMAC_SREQ_LEN    24
#define ASP_DMAC_SREQ_OFFSET 0
#define ASP_DMAC_LSREQ_LEN    24
#define ASP_DMAC_LSREQ_OFFSET 0
#define ASP_DMAC_BREQ_LEN    24
#define ASP_DMAC_BREQ_OFFSET 0
#define ASP_DMAC_LBREQ_LEN    24
#define ASP_DMAC_LBREQ_OFFSET 0
#define ASP_DMAC_FREQ_LEN    24
#define ASP_DMAC_FREQ_OFFSET 0
#define ASP_DMAC_LFREQ_LEN    24
#define ASP_DMAC_LFREQ_OFFSET 0
#define ASP_DMAC_CH11_PRI_LEN    2
#define ASP_DMAC_CH11_PRI_OFFSET 22
#define ASP_DMAC_CH10_PRI_LEN    2
#define ASP_DMAC_CH10_PRI_OFFSET 20
#define ASP_DMAC_CH9_PRI_LEN    2
#define ASP_DMAC_CH9_PRI_OFFSET 18
#define ASP_DMAC_CH8_PRI_LEN    2
#define ASP_DMAC_CH8_PRI_OFFSET 16
#define ASP_DMAC_CH7_PRI_LEN    2
#define ASP_DMAC_CH7_PRI_OFFSET 14
#define ASP_DMAC_CH6_PRI_LEN    2
#define ASP_DMAC_CH6_PRI_OFFSET 12
#define ASP_DMAC_CH5_PRI_LEN    2
#define ASP_DMAC_CH5_PRI_OFFSET 10
#define ASP_DMAC_CH4_PRI_LEN    2
#define ASP_DMAC_CH4_PRI_OFFSET 8
#define ASP_DMAC_CH3_PRI_LEN    2
#define ASP_DMAC_CH3_PRI_OFFSET 6
#define ASP_DMAC_CH2_PRI_LEN    2
#define ASP_DMAC_CH2_PRI_OFFSET 4
#define ASP_DMAC_CH1_PRI_LEN    2
#define ASP_DMAC_CH1_PRI_OFFSET 2
#define ASP_DMAC_CH0_PRI_LEN    2
#define ASP_DMAC_CH0_PRI_OFFSET 0
#define ASP_DMAC_CH_STAT_LEN    12
#define ASP_DMAC_CH_STAT_OFFSET 0

#define ASP_DMAC_INTR_SEC_CTRL_LEN    1
#define ASP_DMAC_INTR_SEC_CTRL_OFFSET 1
#define ASP_DMAC_GLOBAL_SEC_LEN    1
#define ASP_DMAC_GLOBAL_SEC_OFFSET 0

#define ASP_DMAC_CONF_OUT4_LEN    1
#define ASP_DMAC_CONF_OUT4_OFFSET 4
#define ASP_DMAC_HALT_REQ_LEN    1
#define ASP_DMAC_HALT_REQ_OFFSET 1
#define ASP_DMAC_HALT_ACK_LEN    1
#define ASP_DMAC_HALT_ACK_OFFSET 0

#define ASP_DMAC_CURR_C_COUNT_LEN    16
#define ASP_DMAC_CURR_C_COUNT_OFFSET 0

#define ASP_DMAC_CURR_B_COUNT_LEN    16
#define ASP_DMAC_CURR_B_COUNT_OFFSET 16
#define ASP_DMAC_CURR_A_COUNT_LEN    16
#define ASP_DMAC_CURR_A_COUNT_OFFSET 0

#define ASP_DMAC_CURR_SRC_ADDR_LEN    32
#define ASP_DMAC_CURR_SRC_ADDR_OFFSET 0

#define ASP_DMAC_CURR_DES_ADDR_LEN    32
#define ASP_DMAC_CURR_DES_ADDR_OFFSET 0

#define ASP_DMAC_LLI_LEN    27
#define ASP_DMAC_LLI_OFFSET 5
#define ASP_DMAC_CHAIN_EN_LEN    2
#define ASP_DMAC_CHAIN_EN_OFFSET 0

#define ASP_DMAC_SRC_CSIGN_LEN    1
#define ASP_DMAC_SRC_CSIGN_OFFSET 31
#define ASP_DMAC_SRC_CINDX_LEN    15
#define ASP_DMAC_SRC_CINDX_OFFSET 16
#define ASP_DMAC_DES_CSIGN_LEN    1
#define ASP_DMAC_DES_CSIGN_OFFSET 15
#define ASP_DMAC_DES_CINDX_LEN    15
#define ASP_DMAC_DES_CINDX_OFFSET 0

#define ASP_DMAC_C_COUNT_LEN    16
#define ASP_DMAC_C_COUNT_OFFSET 0

#define ASP_DMAC_B_COUNT_MASK   0xffff0000
#define ASP_DMAC_B_COUNT_LEN    16
#define ASP_DMAC_B_COUNT_OFFSET 16

#define ASP_DMAC_A_COUNT_MASK   0xffff
#define ASP_DMAC_A_COUNT_LEN    16
#define ASP_DMAC_A_COUNT_OFFSET 0

#define ASP_DMAC_SRC_ADDR_LEN    32
#define ASP_DMAC_SRC_ADDR_OFFSET 0

#define ASP_DMAC_DES_ADDR_LEN    32
#define ASP_DMAC_DES_ADDR_OFFSET 0

#define ASP_DMAC_SI_LEN    1
#define ASP_DMAC_SI_OFFSET 31
#define ASP_DMAC_DI_LEN    1
#define ASP_DMAC_DI_OFFSET 30
#define ASP_DMAC_SMODE_LEN    1
#define ASP_DMAC_SMODE_OFFSET 29
#define ASP_DMAC_DMODE_LEN    1
#define ASP_DMAC_DMODE_OFFSET 28

#define ASP_DMAC_SL_MASK 0xf000000
#define ASP_DMAC_SL_LEN    4
#define ASP_DMAC_SL_OFFSET 24

#define ASP_DMAC_DL_MASK 0xf00000
#define ASP_DMAC_DL_LEN    4
#define ASP_DMAC_DL_OFFSET 20

#define ASP_DMAC_SW_MASK 0x70000
#define ASP_DMAC_SW_LEN    3
#define ASP_DMAC_SW_OFFSET 16

#define ASP_DMAC_DW_MASK 0x7000
#define ASP_DMAC_DW_LEN    3
#define ASP_DMAC_DW_OFFSET 12

#define ASP_DMAC_PERI_MASK 0x3f0
#define ASP_DMAC_PERI_LEN    6
#define ASP_DMAC_PERI_OFFSET 4

#define ASP_DMAC_FLOW_CTRL_MASK 0xc
#define ASP_DMAC_FLOW_CTRL_LEN    2
#define ASP_DMAC_FLOW_CTRL_OFFSET 2

#define ASP_DMAC_ITC_EN_LEN    1
#define ASP_DMAC_ITC_EN_OFFSET 1
#define ASP_DMAC_CH_EN_LEN    1
#define ASP_DMAC_CH_EN_OFFSET 0

#define ASP_DMAC_AWCACHE_LEN    4
#define ASP_DMAC_AWCACHE_OFFSET 20
#define ASP_DMAC_AWPROT_LEN    3
#define ASP_DMAC_AWPROT_OFFSET 17
#define ASP_DMAC_AWUSER_LEN    5
#define ASP_DMAC_AWUSER_OFFSET 12
#define ASP_DMAC_ARCACHE_LEN    4
#define ASP_DMAC_ARCACHE_OFFSET 8
#define ASP_DMAC_ARPROT_LEN    3
#define ASP_DMAC_ARPROT_OFFSET 5
#define ASP_DMAC_ARUSER_LEN    5
#define ASP_DMAC_ARUSER_OFFSET 0

#define BASE_ADDR_SIO_AUDIO                   0xe804e800
#define BASE_ADDR_SIO_VOICE                   0xe804ec00
#define HI3630_SIO_I2S_RX_CHN_REG               0xa0
#define HI3630_SIO_I2S_TX_CHN_REG               0xc0

#define HI3630_MIN_STOP_DMA_TIME_US 1000
#define HI3630_MAX_STOP_DMA_TIME_US 2000

#define CH_0_UNMASK_BIT 0x0
#define CH_0_UNMASK 0x1
#define CH_0_INT_CLR 0x1
#define DMA_ENABLE_BIT 0

#define DMA_LLI_NUM 2

/* dma config cb*/
/* #define CONFIG_SI		(0x0 << ASP_DMAC_SI_OFFSET) */
/* #define CONFIG_DI		(0x1 << ASP_DMAC_DI_OFFSET) */

/* dma config pb*/
#define CONFIG_SI		(0x1 << ASP_DMAC_SI_OFFSET)
#define CONFIG_DI		(0x0 << ASP_DMAC_DI_OFFSET)

#define CONFIG_SMODE		(0x0 << ASP_DMAC_SMODE_OFFSET)
#define CONFIG_DMODE		(0x0 << ASP_DMAC_DMODE_OFFSET)
/* burst length is 4 */
#define CONFIG_SL		(0x3 << ASP_DMAC_SL_OFFSET)
#define CONFIG_DL		(0x3 << ASP_DMAC_DL_OFFSET)
#define CONFIG_SW		(0x2 << ASP_DMAC_SW_OFFSET)
#define CONFIG_DW		(0x2 << ASP_DMAC_DW_OFFSET)
/* for audio */
// #define CONFIG_PERI		(0x16 << ASP_DMAC_PERI_OFFSET)
/* for voice cp*/
/* #define CONFIG_PERI		(0x14 << ASP_DMAC_PERI_OFFSET) */
/* for voice pb*/
#define CONFIG_PERI		(0x15 << ASP_DMAC_PERI_OFFSET)
#define CONFIG_FLOW_CTRL	(0x1 << ASP_DMAC_FLOW_CTRL_OFFSET)
#define CONFIG_ITC_EN		(0x1 << ASP_DMAC_ITC_EN_OFFSET)
#define CONFIG_CH_EN		(0x0 << ASP_DMAC_CH_EN_OFFSET)

#define DMA_CONFIG	(CONFIG_SI | CONFIG_DI | CONFIG_SMODE | \
			CONFIG_DMODE | CONFIG_SL | CONFIG_DL | 	\
			CONFIG_SW | CONFIG_DW | CONFIG_PERI | 	\
			CONFIG_FLOW_CTRL | CONFIG_ITC_EN | CONFIG_CH_EN)

#define DMA_LLI_ENABLE 	0x2

#endif


