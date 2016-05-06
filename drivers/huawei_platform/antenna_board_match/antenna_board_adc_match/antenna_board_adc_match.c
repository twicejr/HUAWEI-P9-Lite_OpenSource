
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/huawei/hisi_adc.h>
#include <huawei_platform/log/hw_log.h>
#include <huawei_platform/antenna_board_match/antenna_board_match.h>
#include "antenna_board_adc_match.h"

#define HWLOG_TAG antenna_board_adc_match
HWLOG_REGIST();


static int board_adc_channel = DEFAULT_ANTENNA_BOARD_ADC_CHANNEL;
static int antenna_adc_match_range[2] = {820,975};//ADC match range,[820,975] is default range provided by hardware


/*********************************************************
*  Function:       check_match_by_adc
*  Discription:    check if main board is match with the rf board
*  Parameters:     none
*  Return value:   0-not match or 1-match
*********************************************************/
int check_match_by_adc()
{
    int ret = 0;
    int rf_voltage = 0;

    rf_voltage = hisi_adc_get_value(board_adc_channel);
    hwlog_info("Antenna board adc voltage = %d\n", rf_voltage);

    if(rf_voltage >= antenna_adc_match_range[0] && rf_voltage <= antenna_adc_match_range[1]){
        ret = 1;
    }else{
        hwlog_err("adc voltage is not in range, Antenna_board_match error!\n");
        ret = 0;
    }

    return ret;
}

static void parse_dts(struct antenna_adc_match_info *di)
{
    int ret;
    struct device_node* np;

    np = di->dev->of_node;
    if(NULL == np){
        hwlog_err("%s np is null!\n",__FUNCTION__);
        return;
    }

    //adc channel
    if (of_property_read_u32(np, "antenna_board_adc_channel",&board_adc_channel)){
        hwlog_err("dts:can not get antenna board adc channel,use default channel: %d!\n",board_adc_channel);
    }
    hwlog_info("get antenna board adc channel = %d! \n",board_adc_channel);

    //match range
    if(of_property_read_u32_array(np, "antenna_board_match_range", antenna_adc_match_range, 2))
    {
        hwlog_err("%s, antenna_board_match_range not exist, use default array!\n", __func__);
    }
    hwlog_info("antenna_adc_match_range: min = %d,max = %d\n",antenna_adc_match_range[0],antenna_adc_match_range[1]);
}

struct antenna_device_ops adc_match_ops = {
    .get_antenna_match_status = check_match_by_adc,
};

static int antenna_board_adc_probe(struct platform_device *pdev)
{
    int ret;
    struct antenna_adc_match_info *di;

    di = kzalloc(sizeof(*di), GFP_KERNEL);
    if (!di)
    {
        hwlog_err("alloc di failed\n");
        return -ENOMEM;
    }
    di->dev = &pdev->dev;

    /*get dts data*/
    parse_dts(di);

    //register ops
    ret = antenna_match_ops_register(&adc_match_ops);
    if(ret)
    {
        hwlog_err("register antenna_match ops failed!\n");
        goto adc_match_fail0;
    }

    hwlog_info("huawei antenna_board_adc_match probe ok!\n");
    return 0;

adc_match_fail0:
    kfree(di);
    di = NULL;
    return -1;
}

/*
 *probe match table
*/
static struct of_device_id antenna_board_adc_table[] = {
    {
        .compatible = "huawei,antenna_board_adc_match",
        .data = NULL,
    },
    {},
};

/*
 *antenna board match driver
 */
static struct platform_driver antenna_board_adc_driver = {
    .probe = antenna_board_adc_probe,
    .driver = {
        .name = "huawei,antenna_board_adc_match",
        .owner = THIS_MODULE,
        .of_match_table = of_match_ptr(antenna_board_adc_table),
    },
};
/***************************************************************
 * Function: antenna_board_match_init
 * Description: antenna board match module initialization
 * Parameters:  Null
 * return value: 0-sucess or others-fail
 * **************************************************************/
static int __init antenna_board_adc_init(void)
{
    return platform_driver_register(&antenna_board_adc_driver);
}
/*******************************************************************
 * Function:       antenna_board_match_exit
 * Description:    antenna board match module exit
 * Parameters:   NULL
 * return value:  NULL
 * *********************************************************/
static void __exit antenna_board_adc_exit(void)
{
    platform_driver_unregister(&antenna_board_adc_driver);
}
module_init(antenna_board_adc_init);
module_exit(antenna_board_adc_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("huawei antenna board adc driver");
MODULE_AUTHOR("HUAWEI Inc");
