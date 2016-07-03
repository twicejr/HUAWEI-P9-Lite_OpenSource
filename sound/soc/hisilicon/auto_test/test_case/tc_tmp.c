

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




static int tc_dmac_move_line_probe(struct platform_device *pdev)
{
    pr_info("%s.\n",__FUNCTION__);

    tc_tmp = kmalloc(sizeof(struct at_case_type), GFP_ATOMIC);
    if(NULL == tc_tmp){
         return -ENOMEM;
    }


    return 0;
}


static int tc_tc_tmp_remove(struct platform_device *pdev)
{
    pr_info("%s\n",__FUNCTION__);


    kfree(tc_tmp);
    return 0;
}


static int __init tc_tc_tmp_init(void)
{
    pr_info("%s \n",__FUNCTION__);

    platform_device_register_simple(DRV_NAME,0,NULL,0);

    return platform_driver_register(&tc_tmp_driver);
}
module_init(tc_tc_tmp_init);



static void __exit tc_tmp_exit(void)
{
    pr_info("%s\n",__FUNCTION__);
    platform_driver_unregister(&tc_tmp_driver);
}
module_exit(tc_tmp_exit);


MODULE_AUTHOR("wangbingda 00262566");
MODULE_DESCRIPTION("hisilicon driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRV_NAME);
