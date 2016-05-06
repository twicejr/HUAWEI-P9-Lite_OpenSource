/****************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ****************************************************************************
  文 件 名   : core.c
  版 本 号   : 初稿
  作    者   : w00262566
  生成日期   : 2015年1月27日
  最近修改   :
  功能描述   : 自动化测试公共函数模块
  函数列表   :
              at_core_register_test_case
              at_core_unregister_test_case
              at_core_test_list_start
              at_core_start_test_flow
  修改历史   :
  1.日    期   : 2015年1月27日
    作    者   : w00262566
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include <linux/syscalls.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include "core.h"

#include <linux/err.h>
#include <linux/gfp.h>

/*****************************************************************************
    可维可测信息中包含的C文件编号宏定义
*****************************************************************************/

/*****************************************************************************
  2 全局变量与宏定义定义
*****************************************************************************/
#define DRV_NAME              "at_core"
#define AT_LOG_FILE_PATH      "/data/"
#define AT_LOG_FILE_NAME      "at_log"

static struct at_test_list    *at_case_list_hig;
static struct at_test_list    *at_case_list_nor;
static struct at_test_list    *at_case_list_low;

static struct file            *at_log_file;

int at_core_probe (struct platform_device *pdev);
int at_core_remove(struct platform_device *pdev);

static const struct of_device_id at_core_of_match[] = {
    { .compatible = DRV_NAME, },
    {},
};

static struct platform_driver at_core_driver = {
    .probe      = at_core_probe,
    //.remove     = at_core_remove,
    .driver     = {
        .name   = DRV_NAME,
        .owner  = THIS_MODULE,
        .of_match_table = at_core_of_match,
    },
};

/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : at_core_register_test_case
 功能描述  : 注册测试用例
 输入参数  : struct at_case_type*   测试用例
 输出参数  : 无
 返 回 值  : int   注册结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月27日
    作    者   : w00262566
    修改内容   : 新生成函数

*****************************************************************************/
int at_core_register_test_case(struct at_case_type *test_case)
{
    struct at_test_list *test_list = NULL;

    switch(test_case->test_pri) {
        case AT_CASE_PRI_HIG:
            test_list = at_case_list_hig;
            break;
        case AT_CASE_PRI_NOR:
            test_list = at_case_list_nor;
            break;
        case AT_CASE_PRI_LOW:
            test_list = at_case_list_low;
            break;
        default:
            break;
    }

    if(NULL == test_list){
        return AT_FAILED;
    }

    mutex_lock(&test_list->test_mutex);
    list_add_tail(&test_case->test_node, &test_list->test_list);
    mutex_unlock(&test_list->test_mutex);

    return AT_FAILED;
}


/*****************************************************************************
 函 数 名  : at_core_unregister_test_case
 功能描述  : 注销测试用例
 输入参数  : struct at_case_type*   测试用例
 输出参数  : 无
 返 回 值  : int   注销结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月27日
    作    者   : w00262566
    修改内容   : 新生成函数

*****************************************************************************/
int at_core_unregister_test_case(struct at_case_type *test_case)
{
    struct at_test_list *test_list = NULL;

    if( NULL == test_case){
        return AT_FAILED;
    }

    switch(test_case->test_pri) {
        case AT_CASE_PRI_HIG:
            test_list = at_case_list_hig;
            break;
        case AT_CASE_PRI_NOR:
            test_list = at_case_list_nor;
            break;
        case AT_CASE_PRI_LOW:
            test_list = at_case_list_low;
            break;
        default:
            break;
    }

    mutex_lock(&test_list->test_mutex);
    list_del(&test_case->test_node);
    mutex_unlock(&test_list->test_mutex);

    return AT_SUCCESS;
}
/*****************************************************************************
 函 数 名  : at_core_test_list_start
 功能描述  : 执行测试用例
 输入参数  : struct at_test_list *   测试用例链表
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月27日
    作    者   : w00262566
    修改内容   : 新生成函数

*****************************************************************************/
void at_core_test_list_start (struct at_test_list *test_list)
{
    struct at_case_type *pos;

    mutex_lock(&test_list->test_mutex);
    list_for_each_entry(pos,&test_list->test_list, test_node){
        if(NULL != pos->prepare){
            pos->prepare(pos->test_params);
        }
        if(NULL != pos->begin){
            pos->begin(pos->test_params);
        }
        if(NULL != pos->stop){
            pos->stop(pos->test_params);
        }
    }
    mutex_unlock(&test_list->test_mutex);
}

/*****************************************************************************
 函 数 名  : at_core_start_test_flow
 功能描述  : 执行所有测试用例
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
void at_core_start_test_flow (void)
{
    pr_info("%s.list_hig start \n",__FUNCTION__);
    at_core_test_list_start(at_case_list_hig);
    pr_info("%s.list_hig end \n",__FUNCTION__);
    at_core_test_list_start(at_case_list_nor);
    pr_info("%s.list_nor end \n",__FUNCTION__);
    at_core_test_list_start(at_case_list_low);
    pr_info("%s.list_low end \n",__FUNCTION__);
}


EXPORT_SYMBOL(at_core_register_test_case);
EXPORT_SYMBOL(at_core_unregister_test_case);
EXPORT_SYMBOL(at_core_start_test_flow);
EXPORT_SYMBOL(at_core_test_list_start);


/*****************************************************************************
 函 数 名  : at_core_probe
 功能描述  : asp core 驱动初始化
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
int at_core_probe(struct platform_device *pdev)
{

    pr_info("%s.\n",__FUNCTION__);

    at_case_list_hig = kmalloc(sizeof(struct at_test_list), GFP_KERNEL);
	//at_case_list_hig = devm_kmalloc(&pdev->dev,sizeof(struct at_test_list), GFP_ATOMIC);
    if(NULL == at_case_list_hig) {
        return -ENOMEM;
    }

    at_case_list_nor = devm_kmalloc(&pdev->dev,sizeof(struct at_test_list), GFP_ATOMIC);
    if(NULL == at_case_list_hig) {
        return -ENOMEM;
    }

    at_case_list_low = devm_kmalloc(&pdev->dev,sizeof(struct at_test_list), GFP_ATOMIC);
    if(NULL == at_case_list_hig) {
        return -ENOMEM;
    }

    mutex_init(&at_case_list_hig->test_mutex);
    mutex_init(&at_case_list_nor->test_mutex);
    mutex_init(&at_case_list_low->test_mutex);


    INIT_LIST_HEAD(&at_case_list_hig->test_list);
    INIT_LIST_HEAD(&at_case_list_nor->test_list);
    INIT_LIST_HEAD(&at_case_list_low->test_list);

    at_log_file = at_util_log_file_open(AT_LOG_FILE_PATH, AT_LOG_FILE_NAME);

    return 0;
}

/*****************************************************************************
 函 数 名  : at_core_remove
 功能描述  : asp core 驱动移除
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
int at_core_remove(struct platform_device *pdev)
{
    pr_info("%s\n",__FUNCTION__);

    return 0;
}

/*****************************************************************************
 函 数 名  : at_core_init
 功能描述  : asp core 模块初始化
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
static int __init at_core_init( void )
{
    pr_info("%s \n",__FUNCTION__);

    platform_device_register_simple(DRV_NAME,0,NULL,0);

    return platform_driver_register(&at_core_driver);

 }
/*****************************************************************************
 函 数 名  : at_core_exit
 功能描述  : asp core 模块初始化
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
static void __exit  at_core_exit( void )
{
    if(NULL != at_case_list_hig) {
        kfree (at_case_list_hig);
    }
    if(NULL != at_case_list_nor) {
        kfree (at_case_list_nor);
    }
    if(NULL != at_case_list_low) {
        kfree (at_case_list_low);
    }

    platform_driver_unregister(&at_core_driver);
}

module_init(at_core_init);
module_exit(at_core_exit);


MODULE_AUTHOR("wangbingda 00262566");
MODULE_DESCRIPTION("hisilicon driver");
MODULE_LICENSE("Dual BSD/GPL");

