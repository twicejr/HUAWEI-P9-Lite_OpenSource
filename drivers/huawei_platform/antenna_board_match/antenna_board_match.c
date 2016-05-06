
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <huawei_platform/log/hw_log.h>
#include <huawei_platform/antenna_board_match/antenna_board_match.h>

#define HWLOG_TAG antenna_board_match
HWLOG_REGIST();

struct antenna_device_ops *g_antenna_board_match_ops = NULL;


#define ANTENNA_SYSFS_FIELD(_name, n, m, store)      \
{                                                    \
    .attr = __ATTR(_name, m, antenna_show, store),    \
    .name = ANTENNA_##n,                            \
}

#define ANTENNA_SYSFS_FIELD_RO(_name, n)            \
        ANTENNA_SYSFS_FIELD(_name, n, S_IRUGO, NULL)

static ssize_t antenna_show(struct device *dev,
        struct device_attribute *attr, char *buf);

struct antenna_sysfs_field_info {
    struct device_attribute attr;
    u8 name;
};


static struct antenna_sysfs_field_info antenna_tb[] = {
    ANTENNA_SYSFS_FIELD_RO(antenna_board_match,    BOARD_MATCH),
};

static struct attribute *antenna_sysfs_attrs[ARRAY_SIZE(antenna_tb) + 1];
static const struct attribute_group antenna_sysfs_attr_group = {
    .attrs = antenna_sysfs_attrs,
};
static void antenna_sysfs_init_attrs(void)
{
    int i, limit = ARRAY_SIZE(antenna_tb);

    for (i = 0; i < limit; i++)
    {
        antenna_sysfs_attrs[i] = &antenna_tb[i].attr.attr;
    }
    antenna_sysfs_attrs[limit] = NULL;
}

static struct antenna_sysfs_field_info *antenna_board_lookup(const char *name)
{
    int i, limit = ARRAY_SIZE(antenna_tb);

    for (i = 0; i< limit; i++)
    {
        if (!strncmp(name, antenna_tb[i].attr.attr.name,strlen(name)))
            break;
    }
    if (i >= limit)
        return NULL;
    return &antenna_tb[i];
}

static int antenna_match_sysfs_create_group(struct antenna_device_info *di)
{
    antenna_sysfs_init_attrs();
    return sysfs_create_group(&di->dev->kobj, &antenna_sysfs_attr_group);
}

static inline void antenna_match_sysfs_remove_group(struct antenna_device_info *di)
{
    sysfs_remove_group(&di->dev->kobj, &antenna_sysfs_attr_group);
}

static ssize_t antenna_show(struct device *dev,
         struct device_attribute *attr, char *buf)
{
    int adc_ret = 0;
    struct antenna_sysfs_field_info *info = NULL;
    struct antenna_device_info *di = dev_get_drvdata(dev);

    if (NULL == di) {
        hwlog_err("[%s]di is NULL!\n",__func__);
        return -ENODEV;
    }
    info = antenna_board_lookup(attr->attr.name);
    if (!info)
        return -EINVAL;
    switch(info->name){
        case ANTENNA_BOARD_MATCH:
            adc_ret = di->ops->get_antenna_match_status();
            return snprintf(buf, PAGE_SIZE, "%d\n", adc_ret);
        default:
            hwlog_err("(%s)NODE ERR!!HAVE NO THIS NODE:(%d)\n",__func__,info->name);
            break;
    }
    return 0;
}

static struct class *hw_antenna_class = NULL;
static struct class *antenna_board_match_class = NULL;
struct device * antenna_dev = NULL;

/*get new class*/
struct class *hw_antenna_get_class(void)
{
    if (NULL == hw_antenna_class)
    {
        hw_antenna_class = class_create(THIS_MODULE, "hw_antenna");
        if (NULL == hw_antenna_class)
        {
            hwlog_err("hw_antenna_class create fail");
            return NULL;
        }
    }
    return hw_antenna_class;
}

/**********************************************************
*  Function:       antenna_ops_register
*  Discription:    register the handler ops for diffrent matchion method
*  Parameters:    ops:operations interface of diffrent matchion method
*  return value:  0-sucess or others-fail
**********************************************************/
int antenna_match_ops_register(struct antenna_device_ops *ops)
{
    int ret = 0;

    if(ops != NULL)
    {
        g_antenna_board_match_ops = ops;
    }
    else
    {
        hwlog_err("antenna ops register fail!\n");
        ret = -EPERM;
    }
    return ret;
}

static int antenna_board_match_probe(struct platform_device *pdev)
{
    int ret;
    struct antenna_device_info *di;

    di = kzalloc(sizeof(*di), GFP_KERNEL);
    if (!di)
    {
        hwlog_err("alloc di failed\n");
        return -ENOMEM;
    }
    di->dev = &pdev->dev;
    di->ops = g_antenna_board_match_ops;

    //match ops
    if( (NULL == di->ops)||(di->ops->get_antenna_match_status == NULL))
    {
        hwlog_err("antenna_board_match ops is NULL!\n");
        goto Antenna_board_failed_0;
    }

    platform_set_drvdata(pdev, di);

    ret = antenna_match_sysfs_create_group(di);
    if (ret) {
        hwlog_err("can't create antenna_match sysfs entries\n");
        goto Antenna_board_failed_0;
    }
    antenna_board_match_class = hw_antenna_get_class();
    if(antenna_board_match_class)
    {
        if(antenna_dev == NULL)
        antenna_dev = device_create(antenna_board_match_class, NULL, 0, NULL,"antenna_board");
        if(IS_ERR(antenna_dev))
        {
            antenna_dev = NULL;
            hwlog_err("create rf_dev failed!\n");
            goto Antenna_board_failed_1;
        }
        ret = sysfs_create_link(&antenna_dev->kobj, &di->dev->kobj, "antenna_board_data");
        if(ret)
        {
            hwlog_err("create link to board_match fail.\n");
            goto Antenna_board_failed_1;
        }
    }else{
        hwlog_err("get antenna_match_class fail.\n");
        goto Antenna_board_failed_1;
    }
    hwlog_info("huawei antenna board match probe ok!\n");
    return 0;

Antenna_board_failed_1:
    antenna_match_sysfs_remove_group(di);
Antenna_board_failed_0:
    platform_set_drvdata(pdev, NULL);
    kfree(di);
    di->ops = NULL;
    di = NULL;
    return -1;
}

/**********************************************************
*  Function:       antenna_board_match_remove
*  Discription:    antenna_board_match module remove
*  Parameters:   pdev:platform_device
*  return value:  0-sucess or others-fail
**********************************************************/
static int antenna_board_match_remove(struct platform_device *pdev)
{
    struct antenna_device_info *di = platform_get_drvdata(pdev);

    if (NULL == di) {
        hwlog_err("[%s]di is NULL!\n",__func__);
        return -ENODEV;
    }

    if (NULL != di->ops)
    {
        di->ops = NULL;
        g_antenna_board_match_ops = NULL;
    }
    kfree(di);
    di = NULL;
    return 0;
}


/*
 *probe match table
*/
static struct of_device_id antenna_board_table[] = {
    {
        .compatible = "huawei,antenna_board_match",
        .data = NULL,
    },
    {},
};

/*
 *antenna board match driver
 */
static struct platform_driver antenna_board_match_driver = {
    .probe = antenna_board_match_probe,
    .remove = antenna_board_match_remove,
    .driver = {
        .name = "huawei,antenna_board_match",
        .owner = THIS_MODULE,
        .of_match_table = of_match_ptr(antenna_board_table),
    },
};
/***************************************************************
 * Function: antenna_board_match_init
 * Description: antenna board match module initialization
 * Parameters:  Null
 * return value: 0-sucess or others-fail
 * **************************************************************/
static int __init antenna_board_match_init(void)
{
    return platform_driver_register(&antenna_board_match_driver);
}
/*******************************************************************
 * Function:       antenna_board_match_exit
 * Description:    antenna board match module exit
 * Parameters:   NULL
 * return value:  NULL
 * *********************************************************/
static void __exit antenna_board_match_exit(void)
{
    platform_driver_unregister(&antenna_board_match_driver);
}
device_initcall_sync(antenna_board_match_init);
module_exit(antenna_board_match_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("huawei antenna board match driver");
MODULE_AUTHOR("HUAWEI Inc");

