/****************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ****************************************************************************
  文 件 名   : tc_tmp.c
  版 本 号   : 初稿
  作    者   : w00262566
  生成日期   : 2015年1月27日
  最近修改   :
  功能描述   : 
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

static void *tc_tmp = NULL;


/*****************************************************************************
  2 全局变量与宏定义定义
*****************************************************************************/
#define DRV_NAME              "tc_tmp"

static int tc_tmp_probe (struct platform_device *pdev);
static int tc_tmp_remove(struct platform_device *pdev);


static const struct of_device_id tc_tmp_of_match[] = {
    { .compatible = DRV_NAME, },
    {},
};

static struct platform_driver tc_tmp_driver = {
    .probe      = tc_tmp_probe,
    .remove     = tc_tmp_remove,
    .driver     = {
        .name   = DRV_NAME,
        .owner  = THIS_MODULE,
        .of_match_table = tc_tmp_of_match,
    },
};



/*****************************************************************************
 函 数 名  : tc_dmac_move_line_probe
 功能描述  : tc dmac move line 驱动初始化
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
static int tc_tmp_probe(struct platform_device *pdev)
{
    pr_info("%s.\n",__FUNCTION__);

    tc_tmp = devm_kmalloc(&pdev->device,sizeof(struct platform_device), GFP_ATOMIC);
    if(NULL == tc_tmp){
         return -ENOMEM;
    }


    return 0;
}

/*****************************************************************************
 函 数 名  : tc_dmac_move_line_remove
 功能描述  : tc dmac move line 驱动移除
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
static int tc_tmp_remove(struct platform_device *pdev)
{
    pr_info("%s\n",__FUNCTION__);


    kfree(tc_tmp);
    return 0;
}

/*****************************************************************************
 函 数 名  : tc_dmac_move_line_init
 功能描述  : tc dmac move line 模块初始化
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
static int __init tc_tmp_init(void)
{
    pr_info("%s \n",__FUNCTION__);

    platform_device_register_simple(DRV_NAME,0,NULL,0);

    return platform_driver_register(&tc_tmp_driver);
}
module_init(tc_tmp_init);


/*****************************************************************************
 函 数 名  : tc_dmac_move_line_exit
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
static void __exit tc_tmp_exit(void)
{
    pr_info("%s\n",__FUNCTION__);
    platform_driver_unregister(&tc_tmp_driver);
}
module_exit(tc_tmp_exit);


MODULE_AUTHOR("wangbingda 00262566");
MODULE_DESCRIPTION("hisilicon driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
