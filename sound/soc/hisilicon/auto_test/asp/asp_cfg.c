/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : asp_cfg.c
  版 本 号   : 初稿
  作    者   : w00262566
  生成日期   : 2015年1月26日
  最近修改   :
  功能描述   : asp cfg 模块
  函数列表   :

  修改历史   :
  1.日    期   : 2015年1月26日
    作    者   : w00262566
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include <linux/device.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/of_platform.h>
#include <linux/platform_device.h>
#include <linux/regmap.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/regulator/consumer.h>
#include "asp_cfg_reg_offset.h"
#include "asp_cfg.h"
#include "util.h"


/*****************************************************************************
    可维可测信息中包含的C文件编号宏定义
*****************************************************************************/


/*****************************************************************************
  2 全局变量与宏定义定义
*****************************************************************************/
#define DRV_NAME                    "asp_cfg"
#define BASE_ADDR_ASP_CFG           0xE804E000
#define BASE_ADDR_ASP_CFG_SIZE      0x400

#define SCTRL_BASE_ADDR             (0xFFF0A000)
#define PERI_CRG                    (0xFFF35000)

static void*                g_cfg_base_addr  = 0;
static struct regulator    *asp_cfg_regu_asp = NULL;

static const struct of_device_id asp_cfg_of_match[] = {
    { .compatible = DRV_NAME, },
    {},
};

static int asp_cfg_probe (struct platform_device *pdev);
static int asp_cfg_remove(struct platform_device *pdev);

static struct platform_driver asp_cfg_driver = {
    .probe      = asp_cfg_probe,
    .remove     = asp_cfg_remove,
    .driver     = {
        .name   = DRV_NAME,
        .owner  = THIS_MODULE,
        .of_match_table = asp_cfg_of_match,
    },
};


/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : asp_cfg_reg_read
 功能描述  : 寄存器读函数
 输入参数  : unsigned int reg   寄存器偏移
 输出参数  : 无
 返 回 值  : int                寄存器值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月26日
    作    者   : w00262566
    修改内容   : 新生成函数

*****************************************************************************/
int asp_cfg_reg_read(unsigned int reg)
{
    volatile unsigned int ret = 0;
    pr_info("%s.\n",__FUNCTION__);

    ret = readl(g_cfg_base_addr + reg);
    return ret;
}

/*****************************************************************************
 函 数 名  : asp_cfg_reg_write
 功能描述  : 寄存器写函数
 输入参数  : unsigned int reg   寄存器偏移
             unsigned int value 寄存器写入值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月26日
    作    者   : w00262566
    修改内容   : 新生成函数

*****************************************************************************/
void asp_cfg_reg_write(unsigned int reg, unsigned int value)
{
    pr_info("%s.\n",__FUNCTION__);

    writel(value, g_cfg_base_addr + reg);
    return;
}

/*****************************************************************************
 函 数 名  : asp_cfg_powerup
 功能描述  : asp 上电
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月26日
    作    者   : w00262566
    修改内容   : 新生成函数

*****************************************************************************/
void asp_cfg_powerup(void)
{
    int ret = -1;
    unsigned int val;
    pr_info("%s.\n",__FUNCTION__);

#ifndef LPM3_PREPARE

    ret = regulator_enable(asp_cfg_regu_asp);
    if (0 != ret) {
        pr_info("couldn't enable regulators %d\n", ret);
    }

#else
    /*Access PERI_CRG */
    unsigned int p_peri_cfg_mem    = (unsigned int)PERI_CRG;
    /*Access SCTRL */
    unsigned int p_sctrl_mem       = (unsigned int)SCTRL_BASE_ADDR;
    /*step1-模块打开电源*/
    at_util_reg_write_u32(p_sctrl_mem + 0x0d0, 0x00000001);
    /*audio子系统电源使能*/
    msleep(1000);
    pr_info("%s step1\n", __func__);
    /*step2-模块打开时钟*/
    at_util_reg_write_u32(p_peri_cfg_mem + 0xf4, 0x80008000);
    at_util_reg_write_u32(p_sctrl_mem + 0x108, 0x00010001);
    at_util_reg_write_u32(p_sctrl_mem + 0x030, 0x0c000000);
    at_util_reg_write_u32(p_peri_cfg_mem + 0x050, 0x00000080);
    at_util_reg_write_u32(p_sctrl_mem + 0x040, 0x0000000F);
    pr_info("%s step2\n", __func__);
    /*step3-模块关闭时钟*/
    at_util_reg_write_u32(p_sctrl_mem + 0x44, 0x0000000F);
    at_util_reg_write_u32(p_sctrl_mem + 0x34, 0x0C000000);
    at_util_reg_write_u32(p_peri_cfg_mem + 0x054, 0x00000080);
    at_util_reg_write_u32(p_sctrl_mem + 0x108, 0x00010000);
    at_util_reg_write_u32(p_peri_cfg_mem + 0x0F4, 0x80000000);
    pr_info("%s step3\n", __func__);
    /*step4-模块去ISO*/
    at_util_reg_write_u32(p_sctrl_mem + 0x0C4, 0x00000001);
    pr_info("%s step4\n", __func__);
    /*step5-存储修复*/
    /*step6-模块解复位*/
    at_util_reg_write_u32(p_sctrl_mem + 0xa54, 0x00000001);
    at_util_reg_write_u32(p_sctrl_mem + 0x084, 0x00000780);
    pr_info("%s step6\n", __func__);
    /*step7-模块打开时钟*/
    at_util_reg_write_u32(p_peri_cfg_mem + 0xf4, 0x80008000);
    at_util_reg_write_u32(p_sctrl_mem + 0x108, 0x00010001);
    at_util_reg_write_u32(p_sctrl_mem + 0x030, 0x0c000000);
    at_util_reg_write_u32(p_peri_cfg_mem + 0x050, 0x00000080);
    at_util_reg_write_u32(p_sctrl_mem + 0x040, 0x0000000F);
    pr_info("%s step7\n", __func__);
    /*step8-总线idle清除*/
    at_util_reg_write_u32(p_sctrl_mem + 0x270, 0x00040000);
    /*请求ASP_SUBSYS退出低功耗模式*/
    do    {
        val = at_util_reg_read_u32(p_sctrl_mem + 0x234);
        val &= (0x01<<5);
    }while(val);
    /*查询退出请求是否被响应*/
    do{
    val = at_util_reg_read_u32(p_sctrl_mem + 0x234);
    val &= (0x01<<8);
    }while(val);
    /*确认ASP_SUBSYS已退出低功耗模式*/
    pr_info("%s step8\n", __func__);
    at_util_reg_write_u32(0xE804E000 + 0x104, 0x0);
    /*ASP IP初始化*/
    asp_cfg_reg_write (0x4,  0x1FFFFF);
    asp_cfg_reg_write (0xc,  0xffffffff);
    asp_cfg_reg_write (0x38, 0xffff001f);
    pr_info("%s step9\n", __func__);
    pr_info("%s: success\n", __func__);
#endif

 }

/*****************************************************************************
 函 数 名  : asp_cfg_reg_rw_test
 功能描述  : asp cfg 模块寄存器读写测试
 输入参数  : struct at_util_reg_test_type 寄存器测试数组
             int                          寄存器测试数组大小
 输出参数  : 无
 返 回 值  : int 返回测试结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月26日
    作    者   : w00262566
    修改内容   : 新生成函数

*****************************************************************************/
int asp_cfg_reg_rw_test(struct at_util_reg_test_type regs[], int size)
{
    return at_util_reg_test (regs, size, asp_cfg_reg_read, asp_cfg_reg_write);
}

/*****************************************************************************
 函 数 名  : asp_cfg_ip_init
 功能描述  : asp cfg 模块内部IP初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月26日
    作    者   : w00262566
    修改内容   : 新生成函数

*****************************************************************************/
void asp_cfg_ip_init(void)
{
    /* 外设软复位撤离 */
    asp_cfg_reg_write(HI3650_ASP_CFG_R_RST_CTRLDIS_REG, 0x1FFFFF);

    /* 时钟使能 */
    asp_cfg_reg_write(HI3650_ASP_CFG_R_GATE_EN_REG, 0xffffffff);

    /* 时钟选择 */
    asp_cfg_reg_write(HI3650_ASP_CFG_R_CLK_SEL_REG, 0xffff001f);
}


/*****************************************************************************
 函 数 名  : asp_cfg_probe
 功能描述  : asp cfg 驱动初始化
 输入参数  : struct platform_device* 设备指针
 输出参数  : 无
 返 回 值  : 初始化结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月26日
    作    者   : w00262566
    修改内容   : 新生成函数

*****************************************************************************/
static int asp_cfg_probe(struct platform_device *pdev)
{
    pr_info("%s.\n",__FUNCTION__);

    g_cfg_base_addr = ioremap(BASE_ADDR_ASP_CFG, BASE_ADDR_ASP_CFG_SIZE);
    if (!g_cfg_base_addr) {
        pr_info("cannot map register memory\n");
        return -ENOMEM;
    }

    asp_cfg_regu_asp = devm_regulator_get(&pdev->dev,"asp");
    if (IS_ERR(asp_cfg_regu_asp)) {
        pr_info( "couldn't get regulators \n");
        return -ENOENT;
    }

    return 0;
}

/*****************************************************************************
 函 数 名  : asp_cfg_remove
 功能描述  : asp cfg 驱动移除
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
static int asp_cfg_remove(struct platform_device *pdev)
{
    pr_info("%s\n",__FUNCTION__);

    if(NULL != g_cfg_base_addr){
        iounmap(g_cfg_base_addr);
    }

    return 0;
}


/*****************************************************************************
 函 数 名  : asp_cfg_init
 功能描述  : asp cfg 模块初始化
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
static int __init asp_cfg_init(void)
{
    pr_info("%s \n",__FUNCTION__);

    platform_device_register_simple(DRV_NAME,0,NULL,0);

    return platform_driver_register(&asp_cfg_driver);
}
module_init(asp_cfg_init);

/*****************************************************************************
 函 数 名  : asp_cfg_exit
 功能描述  : asp cfg 模块移除
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 模块移除结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月26日
    作    者   : w00262566
    修改内容   : 新生成函数

*****************************************************************************/
static void __exit asp_cfg_exit(void)
{
    pr_info("%s\n",__FUNCTION__);
    platform_driver_unregister(&asp_cfg_driver);
}
module_exit(asp_cfg_exit);

EXPORT_SYMBOL(asp_cfg_reg_read);
EXPORT_SYMBOL(asp_cfg_reg_write);
EXPORT_SYMBOL(asp_cfg_reg_rw_test);
EXPORT_SYMBOL(asp_cfg_ip_init);
EXPORT_SYMBOL(asp_cfg_powerup);




MODULE_AUTHOR("wangbingda 00262566");
MODULE_DESCRIPTION("hisilicon driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRV_NAME);
