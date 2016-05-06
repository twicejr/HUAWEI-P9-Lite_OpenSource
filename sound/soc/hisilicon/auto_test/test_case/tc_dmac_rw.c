/****************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ****************************************************************************
  文 件 名   : test_asp_dmac_reg.c
  版 本 号   : 初稿
  作    者   : w00262566
  生成日期   : 2015年1月27日
  最近修改   :
  功能描述   : dmac reg 读写测试
  函数列表   :
  修改历史   :
  1.日    期   : 2015年1月27日
    作    者   : w00262566
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include <linux/device.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/of_platform.h>
#include <linux/platform_device.h>
#include "asp_edmac_reg_offset.h"
#include "util.h"
#include "core.h"
#include "asp_cfg.h"
#include "asp_dmac.h"


/*****************************************************************************
  2 全局变量与宏定义定义
*****************************************************************************/
#define DRV_NAME              "tc_dmac_reg"

static int tc_dmac_reg_probe (struct platform_device *pdev);
static int tc_dmac_reg_remove(struct platform_device *pdev);

static struct at_case_type* tc_dmac_reg;

static const struct of_device_id tc_dmac_reg_of_match[] = {
    { .compatible = DRV_NAME, },
    {},
};

static struct platform_driver tc_dmac_reg_driver = {
    .probe      = tc_dmac_reg_probe,
    .remove     = tc_dmac_reg_remove,
    .driver     = {
        .name   = DRV_NAME,
        .owner  = THIS_MODULE,
        .of_match_table = tc_dmac_reg_of_match,
    },
};

struct at_util_reg_test_type tc_dmac_regs[] = {
    {HI3650_ASP_EDMAC_INT_STAT_0_REG         , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_INT_STAT_1_REG         , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_INT_TC1_0_REG          , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_INT_TC1_1_REG          , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_INT_TC2_0_REG          , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_INT_TC2_1_REG          , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_INT_ERR1_0_REG         , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_INT_ERR1_1_REG         , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_INT_ERR2_0_REG         , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_INT_ERR2_1_REG         , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_INT_ERR3_0_REG         , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_INT_ERR3_1_REG         , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_INT_TC1_MASK_0_REG     , RW, 0x00000000, 0x00000fff, 0x00000fff},
    {HI3650_ASP_EDMAC_INT_TC1_MASK_1_REG     , RW, 0x00000000, 0x00000fff, 0x00000fff},
    {HI3650_ASP_EDMAC_INT_TC2_MASK_0_REG     , RW, 0x00000000, 0x00000fff, 0x00000fff},
    {HI3650_ASP_EDMAC_INT_TC2_MASK_1_REG     , RW, 0x00000000, 0x00000fff, 0x00000fff},
    {HI3650_ASP_EDMAC_INT_ERR1_MASK_0_REG    , RW, 0x00000000, 0x00000fff, 0x00000fff},
    {HI3650_ASP_EDMAC_INT_ERR1_MASK_1_REG    , RW, 0x00000000, 0x00000fff, 0x00000fff},
    {HI3650_ASP_EDMAC_INT_ERR2_MASK_0_REG    , RW, 0x00000000, 0x00000fff, 0x00000fff},
    {HI3650_ASP_EDMAC_INT_ERR2_MASK_1_REG    , RW, 0x00000000, 0x00000fff, 0x00000fff},
    {HI3650_ASP_EDMAC_INT_ERR3_MASK_0_REG    , RW, 0x00000000, 0x00000fff, 0x00000fff},
    {HI3650_ASP_EDMAC_INT_ERR3_MASK_1_REG    , RW, 0x00000000, 0x00000fff, 0x00000fff},
    {HI3650_ASP_EDMAC_INT_TC1_RAW_REG        , RWC,0x00000000, 0x00000fff, 0x00000000},
    {HI3650_ASP_EDMAC_INT_TC2_RAW_REG        , RWC,0x00000000, 0x00000fff, 0x00000000},
    {HI3650_ASP_EDMAC_INT_ERR1_RAW_REG       , RWC,0x00000000, 0x00000fff, 0x00000000},
    {HI3650_ASP_EDMAC_INT_ERR2_RAW_REG       , RWC,0x00000000, 0x00000fff, 0x00000000},
    {HI3650_ASP_EDMAC_INT_ERR3_RAW_REG       , RWC,0x00000000, 0x00000fff, 0x00000000},
    {HI3650_ASP_EDMAC_SREQ_REG               , RW, 0x00000000, 0x00ffffff, 0x00ffffff},
    {HI3650_ASP_EDMAC_LSREQ_REG              , RW, 0x00000000, 0x00ffffff, 0x00ffffff},
    {HI3650_ASP_EDMAC_BREQ_REG               , RW, 0x00000000, 0x00ffffff, 0x00ffffff},
    {HI3650_ASP_EDMAC_LBREQ_REG              , RW, 0x00000000, 0x00ffffff, 0x00ffffff},
    {HI3650_ASP_EDMAC_FREQ_REG               , RW, 0x00000000, 0x00ffffff, 0x00ffffff},
    {HI3650_ASP_EDMAC_LFREQ_REG              , RW, 0x00000000, 0x00ffffff, 0x00ffffff},
   // {HI3650_ASP_EDMAC_CH_PRI_REG             , RW, 0x00000000, 0x00ffffff, 0x00ffffff},
    {HI3650_ASP_EDMAC_CH_STAT_REG            , RO, 0x00000000, 0x00000000, 0x00000000},
    //{HI3650_ASP_EDMAC_SEC_CTRL_REG           , RW, 0x00000000,0x3, 0x3},
    //{HI3650_ASP_EDMAC_DMA_CTRL_REG           , RW, 0x00000000,0x13, 0x13},
    {HI3650_ASP_EDMAC_CX_CURR_CNT1_0_REG     , RO, 0x00000000,0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_CNT1_1_REG     , RO, 0x00000000,0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_CNT1_2_REG     , RO, 0x00000000,0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_CNT1_3_REG     , RO, 0x00000000,0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_CNT1_4_REG     , RO, 0x00000000,0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_CNT1_5_REG     , RO, 0x00000000,0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_CNT1_6_REG     , RO, 0x00000000,0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_CNT1_7_REG     , RO, 0x00000000,0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_CNT1_8_REG     , RO, 0x00000000,0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_CNT1_9_REG     , RO, 0x00000000,0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_CNT1_10_REG     , RO, 0x00000000,0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_CNT1_11_REG     , RO, 0x00000000,0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_CNT0_0_REG     , RO, 0x00000000,0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_CNT0_1_REG     , RO, 0x00000000,0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_CNT0_2_REG     , RO, 0x00000000,0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_CNT0_3_REG     , RO, 0x00000000,0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_CNT0_4_REG     , RO, 0x00000000,0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_CNT0_5_REG     , RO, 0x00000000,0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_CNT0_6_REG     , RO, 0x00000000,0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_CNT0_7_REG     , RO, 0x00000000,0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_CNT0_8_REG     , RO, 0x00000000,0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_CNT0_9_REG     , RO, 0x00000000,0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_CNT0_10_REG     , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_CNT0_11_REG     , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_SRC_ADDR_0_REG  , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_SRC_ADDR_1_REG  , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_SRC_ADDR_2_REG  , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_SRC_ADDR_3_REG  , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_SRC_ADDR_4_REG  , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_SRC_ADDR_5_REG  , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_SRC_ADDR_6_REG  , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_SRC_ADDR_7_REG  , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_SRC_ADDR_8_REG  , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_SRC_ADDR_9_REG  , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_SRC_ADDR_10_REG  , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_SRC_ADDR_11_REG  , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_DES_ADDR_0_REG   , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_DES_ADDR_1_REG   , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_DES_ADDR_2_REG   , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_DES_ADDR_3_REG   , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_DES_ADDR_4_REG   , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_DES_ADDR_5_REG   , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_DES_ADDR_6_REG   , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_DES_ADDR_7_REG   , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_DES_ADDR_8_REG   , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_DES_ADDR_9_REG   , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_DES_ADDR_10_REG   , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_CURR_DES_ADDR_11_REG   , RO, 0x00000000, 0x00000000, 0x00000000},
    {HI3650_ASP_EDMAC_CX_LLI_0_REG           , RW, 0x00000000, 0xFFFFFFE3, 0xFFFFFFE3},
    {HI3650_ASP_EDMAC_CX_LLI_1_REG           , RW, 0x00000000, 0xFFFFFFE3, 0xFFFFFFE3},
    {HI3650_ASP_EDMAC_CX_LLI_2_REG           , RW, 0x00000000, 0xFFFFFFE3, 0xFFFFFFE3},
    {HI3650_ASP_EDMAC_CX_LLI_3_REG           , RW, 0x00000000, 0xFFFFFFE3, 0xFFFFFFE3},
    {HI3650_ASP_EDMAC_CX_LLI_4_REG           , RW, 0x00000000, 0xFFFFFFE3, 0xFFFFFFE3},
    {HI3650_ASP_EDMAC_CX_LLI_5_REG           , RW, 0x00000000, 0xFFFFFFE3, 0xFFFFFFE3},
    {HI3650_ASP_EDMAC_CX_LLI_6_REG           , RW, 0x00000000, 0xFFFFFFE3, 0xFFFFFFE3},
    {HI3650_ASP_EDMAC_CX_LLI_7_REG           , RW, 0x00000000, 0xFFFFFFE3, 0xFFFFFFE3},
    {HI3650_ASP_EDMAC_CX_LLI_8_REG           , RW, 0x00000000, 0xFFFFFFE3, 0xFFFFFFE3},
    {HI3650_ASP_EDMAC_CX_LLI_9_REG           , RW, 0x00000000, 0xFFFFFFE3, 0xFFFFFFE3},
    {HI3650_ASP_EDMAC_CX_LLI_10_REG          , RW, 0x00000000, 0xFFFFFFE3, 0xFFFFFFE3},
    {HI3650_ASP_EDMAC_CX_LLI_11_REG          , RW, 0x00000000, 0xFFFFFFE3, 0xFFFFFFE3},
    {HI3650_ASP_EDMAC_CX_BINDX_0_REG         , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_BINDX_1_REG         , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_BINDX_2_REG         , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_BINDX_3_REG         , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_BINDX_4_REG         , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_BINDX_5_REG         , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_BINDX_6_REG         , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_BINDX_7_REG         , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_BINDX_8_REG         , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_BINDX_9_REG         , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_BINDX_10_REG         , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_BINDX_11_REG        , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_CINDX_0_REG         , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_CINDX_1_REG         , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_CINDX_2_REG         , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_CINDX_3_REG         , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_CINDX_4_REG         , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_CINDX_5_REG         , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_CINDX_6_REG         , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_CINDX_7_REG         , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_CINDX_8_REG         , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_CINDX_9_REG         , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_CINDX_10_REG        , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_CINDX_11_REG        , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_CNT1_0_REG          , RW, 0x00000000, 0x0000ffff, 0x0000ffff},
    {HI3650_ASP_EDMAC_CX_CNT1_1_REG          , RW, 0x00000000, 0x0000ffff, 0x0000ffff},
    {HI3650_ASP_EDMAC_CX_CNT1_2_REG          , RW, 0x00000000, 0x0000ffff, 0x0000ffff},
    {HI3650_ASP_EDMAC_CX_CNT1_3_REG          , RW, 0x00000000, 0x0000ffff, 0x0000ffff},
    {HI3650_ASP_EDMAC_CX_CNT1_4_REG          , RW, 0x00000000, 0x0000ffff, 0x0000ffff},
    {HI3650_ASP_EDMAC_CX_CNT1_5_REG          , RW, 0x00000000, 0x0000ffff, 0x0000ffff},
    {HI3650_ASP_EDMAC_CX_CNT1_6_REG          , RW, 0x00000000, 0x0000ffff, 0x0000ffff},
    {HI3650_ASP_EDMAC_CX_CNT1_7_REG          , RW, 0x00000000, 0x0000ffff, 0x0000ffff},
    {HI3650_ASP_EDMAC_CX_CNT1_8_REG          , RW, 0x00000000, 0x0000ffff, 0x0000ffff},
    {HI3650_ASP_EDMAC_CX_CNT1_9_REG          , RW, 0x00000000, 0x0000ffff, 0x0000ffff},
    {HI3650_ASP_EDMAC_CX_CNT1_10_REG          , RW, 0x00000000, 0x0000ffff, 0x0000ffff},
    {HI3650_ASP_EDMAC_CX_CNT1_11_REG          , RW, 0x00000000, 0x0000ffff, 0x0000ffff},
    {HI3650_ASP_EDMAC_CX_CNT0_0_REG          , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_CNT0_1_REG          , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_CNT0_2_REG          , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_CNT0_3_REG          , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_CNT0_4_REG          , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_CNT0_5_REG          , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_CNT0_6_REG          , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_CNT0_7_REG          , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_CNT0_8_REG          , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_CNT0_9_REG          , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_CNT0_10_REG          , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_CNT0_11_REG          , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_SRC_ADDR_0_REG      , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_SRC_ADDR_1_REG      , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_SRC_ADDR_2_REG      , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_SRC_ADDR_3_REG      , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_SRC_ADDR_4_REG      , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_SRC_ADDR_5_REG      , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_SRC_ADDR_6_REG      , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_SRC_ADDR_7_REG      , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_SRC_ADDR_8_REG      , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_SRC_ADDR_9_REG      , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_SRC_ADDR_10_REG      , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_SRC_ADDR_11_REG      , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_DES_ADDR_0_REG      , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_DES_ADDR_1_REG      , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_DES_ADDR_2_REG      , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_DES_ADDR_3_REG      , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_DES_ADDR_4_REG      , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_DES_ADDR_5_REG      , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_DES_ADDR_6_REG      , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_DES_ADDR_7_REG      , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_DES_ADDR_8_REG      , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_DES_ADDR_9_REG      , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_DES_ADDR_10_REG     , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_DES_ADDR_11_REG     , RW, 0x00000000, 0xffffffff, 0xffffffff},
    {HI3650_ASP_EDMAC_CX_CONFIG_0_REG        , RW, 0x00000000, 0xfff333fe, 0xfff333fe},
    {HI3650_ASP_EDMAC_CX_CONFIG_1_REG        , RW, 0x00000000, 0xfff333fe, 0xfff333fe},
    {HI3650_ASP_EDMAC_CX_CONFIG_2_REG        , RW, 0x00000000, 0xfff333fe, 0xfff333fe},
    {HI3650_ASP_EDMAC_CX_CONFIG_3_REG        , RW, 0x00000000, 0xfff333fe, 0xfff333fe},
    {HI3650_ASP_EDMAC_CX_CONFIG_4_REG        , RW, 0x00000000, 0xfff333fe, 0xfff333fe},
    {HI3650_ASP_EDMAC_CX_CONFIG_5_REG        , RW, 0x00000000, 0xfff333fe, 0xfff333fe},
    {HI3650_ASP_EDMAC_CX_CONFIG_6_REG        , RW, 0x00000000, 0xfff333fe, 0xfff333fe},
    {HI3650_ASP_EDMAC_CX_CONFIG_7_REG        , RW, 0x00000000, 0xfff333fe, 0xfff333fe},
    {HI3650_ASP_EDMAC_CX_CONFIG_8_REG        , RW, 0x00000000, 0xfff333fe, 0xfff333fe},
    {HI3650_ASP_EDMAC_CX_CONFIG_9_REG        , RW, 0x00000000, 0xfff333fe, 0xfff333fe},
    {HI3650_ASP_EDMAC_CX_CONFIG_10_REG        , RW, 0x00000000, 0xfff333fe, 0xfff333fe},
    {HI3650_ASP_EDMAC_CX_CONFIG_11_REG        , RW, 0x00000000, 0xfff333fe, 0xfff333fe},

};

/*****************************************************************************
  3 函数实现
*****************************************************************************/


/*****************************************************************************
 函 数 名  : tc_dmac_read_write_test
 功能描述  : 测试dmac中的寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月27日
    作    者   : w00262566
    修改内容   : 新生成函数

*****************************************************************************/
void tc_dmac_read_write_test(void)
{

    char* tc_dmac_read_write_test_success = "tc_dmac_read_write_test result success\n";
    char* tc_dmac_read_write_test_failed  = "tc_dmac_read_write_test result faied\n";
    pr_info("Audio: test reg beg\n");

    if(AT_SUCCESS == asp_dmac_reg_rw_test(tc_dmac_regs, sizeof(tc_dmac_regs) / sizeof(tc_dmac_regs[0]))){
        at_util_log(tc_dmac_read_write_test_success,strlen(tc_dmac_read_write_test_success));
    }else {
        at_util_log(tc_dmac_read_write_test_failed,strlen(tc_dmac_read_write_test_failed));
    }

    pr_info("Audio: test reg end\n");
}
EXPORT_SYMBOL(tc_dmac_read_write_test);



/*****************************************************************************
 函 数 名  : tc_dmac_reg_prepare
 功能描述  : 测试前处理
 输入参数  : int 测试参数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月27日
    作    者   : w00262566
    修改内容   : 新生成函数

*****************************************************************************/
int tc_dmac_reg_prepare(int test_pram)
{
    asp_cfg_powerup();
    asp_cfg_ip_init();
    return AT_SUCCESS;
}

/*****************************************************************************
 函 数 名  : tc_dmac_reg_beg
 功能描述  : 测试处理
 输入参数  : int 测试参数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月27日
    作    者   : w00262566
    修改内容   : 新生成函数

*****************************************************************************/
int tc_dmac_reg_beg(int test_pram)
{
    tc_dmac_read_write_test();
    return AT_SUCCESS;
}

/*****************************************************************************
 函 数 名  : tc_dmac_reg_stop
 功能描述  : 测试后处理
 输入参数  : int 测试参数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月27日
    作    者   : w00262566
    修改内容   : 新生成函数

*****************************************************************************/
int tc_dmac_reg_stop(int test_pram)
{
    return AT_SUCCESS;
}


/*****************************************************************************
 函 数 名  : tc_dmac_reg_read_write_test_individual
 功能描述  : 测试cfg中的寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月27日
    作    者   : w00262566
    修改内容   : 新生成函数

*****************************************************************************/
void tc_dmac_reg_read_write_test_individual(void)
{
    pr_info("Audio: tc_dmac_reg_read_write_test_individual beg\n");
    char* tc_dmac_read_log_beg = "tc_dmac_read_write_test_individual beg\n";
    char* tc_dmac_read_log_end = "tc_dmac_read_write_test_individual end\n";
    at_util_log(tc_dmac_read_log_beg,strlen(tc_dmac_read_log_beg));
    tc_dmac_reg_prepare(0);
    tc_dmac_reg_beg(0);
    tc_dmac_reg_stop(0);
    at_util_log(tc_dmac_read_log_end,strlen(tc_dmac_read_log_end));
    pr_info("Audio: tc_dmac_reg_read_write_test_individual end\n");
}
EXPORT_SYMBOL(tc_dmac_reg_read_write_test_individual);

/*****************************************************************************
 函 数 名  : tc_dmac_reg_probe
 功能描述  : tc dmac reg 驱动初始化
 输入参数  : struct platform_device* 设备指针
 输出参数  : 无
 返 回 值  : 初始化结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月27日
    作    者   : w00262566
    修改内容   : 新生成函数

*****************************************************************************/
static int tc_dmac_reg_probe(struct platform_device *pdev)
{
    pr_info("%s.\n",__FUNCTION__);

    tc_dmac_reg = devm_kmalloc(&pdev->dev,sizeof(struct at_case_type), GFP_ATOMIC);
    if(NULL == tc_dmac_reg){
         return -ENOMEM;
    }

    tc_dmac_reg->test_name   = "tc_dmac_reg";
    tc_dmac_reg->test_params = 0;
    tc_dmac_reg->test_pri    = AT_CASE_PRI_HIG;
    tc_dmac_reg->prepare     = tc_dmac_reg_prepare;
    tc_dmac_reg->begin       = tc_dmac_reg_beg;
    tc_dmac_reg->stop        = tc_dmac_reg_stop;

   // at_core_register_test_case(tc_dmac_reg);

    return 0;
}

/*****************************************************************************
 函 数 名  : tc_dmac_reg_remove
 功能描述  : tc dmac reg 驱动移除
 输入参数  : struct platform_device* 设备指针
 输出参数  : 无
 返 回 值  : 驱动移除结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月26日
    作    者   : w00262566
    修改内容   : 新生成函数

*****************************************************************************/
static int tc_dmac_reg_remove(struct platform_device *pdev)
{
    pr_info("%s\n",__FUNCTION__);

    at_core_unregister_test_case(tc_dmac_reg);
    kfree(tc_dmac_reg);
    return 0;
}

/*****************************************************************************
 函 数 名  : tc_dmac_reg_init
 功能描述  : tc dmac reg 模块初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 模块初始化结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月26日
    作    者   : w00262566
    修改内容   : 新生成函数

*****************************************************************************/
static int __init tc_dmac_reg_init(void)
{
    pr_info("%s \n",__FUNCTION__);

    platform_device_register_simple(DRV_NAME,0,NULL,0);

    return platform_driver_register(&tc_dmac_reg_driver);
}
module_init(tc_dmac_reg_init);


/*****************************************************************************
 函 数 名  : tc_dmac_reg_exit
 功能描述  : tc dmac reg 模块退出
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 模块退出结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月26日
    作    者   : w00262566
    修改内容   : 新生成函数

*****************************************************************************/
static void __exit tc_dmac_reg_exit(void)
{
    pr_info("%s\n",__FUNCTION__);
    platform_driver_unregister(&tc_dmac_reg_driver);
}
module_exit(tc_dmac_reg_exit);


MODULE_AUTHOR("wangbingda 00262566");
MODULE_DESCRIPTION("hisilicon driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRV_NAME);
