/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : pmicirq_device.c
  版 本 号   : 初稿
  作    者   : fansaihua f00204170
  生成日期   : 2013年3月13日
  最近修改   :
  功能描述   : pmic irq device resource
  函数列表   :
  修改历史   :
  1.日    期   : 2013年3月13日
    作    者   : fansaihua f00204170
    修改内容   : 创建文件

******************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/err.h>
#include <linux/module.h>

#include <mach/irqs.h>

#include "soc_smart_interface.h"
#include "pmic_common.h"
#include "regulator_pmic_info.h"


/*IRQn register addr list*/
PMU_LOCAL BSP_U32 pmic_irqstat_regaddr[PMIC_IRQ_REG_BUTT]={
    SOC_SMART_IRQ1_ADDR(0),
    SOC_SMART_IRQ2_ADDR(0),
    SOC_SMART_IRQ3_ADDR(0),
    SOC_SMART_COUL_IRQ_ADDR(0),/*库伦*/
};

PMU_LOCAL BSP_U32 pmic_status_stat_reg[PMIC_STATUS_REG_BUTT]={
    SOC_SMART_STATUS1_ADDR(0),
    SOC_SMART_STATUS2_ADDR(0),
};

PMU_LOCAL BSP_U32 pmic_record_reg_addr[PMIC_RECORD_REG_BUTT]={
    SOC_SMART_SCP_BUCK_RECORD1_ADDR(0),
    SOC_SMART_OCP_BUCK_RECORD1_ADDR(0),
    SOC_SMART_OCP_LDO1_8_RECORD2_ADDR(0),
    SOC_SMART_OCP_LDO16_9_RECORD3_ADDR(0),
    SOC_SMART_OCP_LDO22_17_RECORD4_ADDR(0),
    SOC_SMART_OCP_CLASSD_LVS2_RECORD5_ADDR(0),
};

PMU_LOCAL BSP_U32 pmic_no_pwr_reg_addr[PMIC_NO_PWR_REG_BUTT]={
    SOC_SMART_NP_IRQ1_RECORD_ADDR(0),
    SOC_SMART_NP_IRQ2_RECORD_ADDR(0),
    SOC_SMART_NP_IRQ3_RECORD_ADDR(0),
    SOC_SMART_NP_SCP_RECORD1_ADDR(0),
    SOC_SMART_NP_OCP_RECORD1_ADDR(0),
    SOC_SMART_NP_OCP_RECORD2_ADDR(0),
    SOC_SMART_NP_OCP_RECORD3_ADDR(0),
    SOC_SMART_NP_OCP_RECORD4_ADDR(0),
    SOC_SMART_NP_OCP_RECORD5_ADDR(0),
};

PMU_LOCAL BSP_U32 pmic_irq_mask_reg[PMIC_IRQ_REG_MASK_BUTT]={
    SOC_SMART_IRQ1_MASK_ADDR(0),
    SOC_SMART_IRQ2_MASK_ADDR(0),
    SOC_SMART_IRQ3_MASK_ADDR(0),
    SOC_SMART_COUL_IRQ_MASK_ADDR(0),
};

PMU_LOCAL PMUIRQ_RES_CTRL  smart_irqres_ctrl =
{
     PMU_REGISTER_DATA_BIT,
    {pmic_irqstat_regaddr,pmic_status_stat_reg,pmic_record_reg_addr,pmic_no_pwr_reg_addr,pmic_irq_mask_reg},
    {PMIC_IRQ_REG_BUTT,PMIC_STATUS_REG_BUTT,PMIC_RECORD_REG_BUTT,PMIC_NO_PWR_REG_BUTT,PMIC_IRQ_REG_MASK_BUTT}
};

static struct platform_device smart_irq_device = {
    .name       = "smartStarIrq",
    .id         = 0,
    .dev.platform_data  = &smart_irqres_ctrl,
};

/* devices we initialise */
static struct platform_device __initdata *smartirq_devs[] = {
    &smart_irq_device,
};

/*****************************************************************************
 函 数 名  : pmic_device_init
 功能描述  : device init
 输入参数  : void
 输出参数  : 无
 返 回 值  : static int __init
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月28日
    作    者   : fansaihua f00204170
    修改内容   : 新生成函数

*****************************************************************************/
static int __init pmicirq_device_init(void)
{
    platform_add_devices(smartirq_devs, ARRAY_SIZE(smartirq_devs));
    printk(KERN_ALERT "smartirq_devs init ok \n");
    return 0;
}

/*pmussi init need time*/
subsys_initcall(pmicirq_device_init);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hisilicon Tech.Co.,Ltd.<fansaihua@huawei.com>");
MODULE_DESCRIPTION(" Hisilicon PMIC IRQ device");

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
