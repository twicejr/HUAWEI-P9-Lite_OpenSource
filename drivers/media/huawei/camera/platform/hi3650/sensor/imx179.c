 

#include <linux/module.h>
#include <linux/printk.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>
#include <linux/rpmsg.h>

#include "hwsensor.h"
#include "sensor_commom.h"
#include "hw_csi.h"

#define I2S(i) container_of(i, sensor_t, intf)

static hwsensor_vtbl_t s_imx179_vtbl;

static int imx179_config(hwsensor_intf_t* si, void  *argp);

static struct sensor_power_setting imx179_power_setting[] = {
    //disable main camera reset
    {
        .seq_type = SENSOR_SUSPEND,
        .config_val = SENSOR_GPIO_LOW,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 0,
    },

    //enable gpio12 output iovdd 1.8v
    {
        .seq_type = SENSOR_LDO_EN,
        .config_val = SENSOR_GPIO_LOW,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 0,
    },

    //MCAM1 AVDD 2.5V
    {
        .seq_type = SENSOR_AVDD2,
        .data = (void*)"main-sensor-avdd",
        .config_val = LDO_VOLTAGE_V2P8V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 0,
    },

    //MCAM1 DVDD 1.2V
    {
        .seq_type = SENSOR_DVDD2,
        .config_val = LDO_VOLTAGE_V1P1V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 0,
    },
    //SCAM AVDD 2.8V
    {
        .seq_type = SENSOR_AVDD,
        .data = (void*)"slave-sensor-avdd",
        .config_val = LDO_VOLTAGE_V2P8V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 0,
    },

    //SCAM DVDD1.2V
    {
        .seq_type = SENSOR_DVDD,
        .config_val = LDO_VOLTAGE_1P2V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

    {
        .seq_type = SENSOR_MCLK,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },
    {
        .seq_type = SENSOR_RST,
        .config_val = SENSOR_GPIO_LOW,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },
};

static sensor_t s_imx179 =
{
    .intf = { .vtbl = &s_imx179_vtbl, },
    .power_setting_array = {
            .size = ARRAY_SIZE(imx179_power_setting),
            .power_setting = imx179_power_setting,
     },
};

static const struct of_device_id
s_imx179_dt_match[] =
{
    {
        .compatible = "huawei,imx179",
        .data = &s_imx179.intf,
    },
    {
    },
};

MODULE_DEVICE_TABLE(of, s_imx179_dt_match);

static struct platform_driver
s_imx179_driver =
{
    .driver =
    {
        .name = "huawei,imx179",
        .owner = THIS_MODULE,
        .of_match_table = s_imx179_dt_match,
    },
};

static char const*
imx179_get_name(
        hwsensor_intf_t* si)
{
    sensor_t* sensor = I2S(si);
    return sensor->board_info->name;
}

static int
imx179_power_up(
        hwsensor_intf_t* si)
{
    int ret = 0;
    sensor_t* sensor = NULL;
    sensor = I2S(si);
    cam_info("enter %s. index = %d name = %s", __func__, sensor->board_info->sensor_index, sensor->board_info->name);

    if (hw_is_fpga_board()){
        ret = do_sensor_power_on(sensor->board_info->sensor_index, sensor->board_info->name);
    } else {
        ret = hw_sensor_power_up(sensor);
    }
    if (0 == ret )
    {
        cam_info("%s. power up sensor success.", __func__);
    }
    else
    {
        cam_err("%s. power up sensor fail.", __func__);
    }
    return ret;
}

static int
imx179_power_down(
        hwsensor_intf_t* si)
{
    int ret = 0;
    sensor_t* sensor = NULL;
    sensor = I2S(si);
    cam_info("enter %s. index = %d name = %s", __func__, sensor->board_info->sensor_index, sensor->board_info->name);
    if (hw_is_fpga_board()) {
        ret = do_sensor_power_off(sensor->board_info->sensor_index, sensor->board_info->name);
    } else {
        ret = hw_sensor_power_down(sensor);
    }
    if (0 == ret )
    {
        cam_info("%s. power down sensor success.", __func__);
    }
    else
    {
        cam_err("%s. power down sensor fail.", __func__);
    }
    return ret;
}

static int imx179_csi_enable(hwsensor_intf_t* si)
{
    return 0;
}

static int imx179_csi_disable(hwsensor_intf_t* si)
{
    return 0;
}

static int
imx179_match_id(
        hwsensor_intf_t* si, void * data)
{
    sensor_t* sensor = I2S(si);
    struct sensor_cfg_data *cdata = (struct sensor_cfg_data *)data;
    int32_t module_id = 0;
    char * sensor_name[] = {"IMX179_SUNNY", "IMX179_LITEON"};
    int rc = 0;

    cam_info("%s enter.", __func__);

    cdata->data = SENSOR_INDEX_INVALID;
    memset(cdata->cfg.name, 0, DEVICE_NAME_SIZE);

    if (!strncmp(sensor->board_info->name, "IMX179_VENDOR", strlen("IMX179_VENDOR"))) {
        rc = gpio_request(sensor->board_info->gpios[FSIN].gpio, NULL);
        if(rc < 0) {
            cam_err("%s failed to request gpio[%d]", __func__, sensor->board_info->gpios[FSIN].gpio);
            return rc;
        }

        cam_info("%s gpio[%d].", __func__, sensor->board_info->gpios[FSIN].gpio);

        rc = gpio_direction_input(sensor->board_info->gpios[FSIN].gpio);
        if (rc < 0) {
            cam_err("%s failed to config gpio(%d) input.\n",
                __func__, sensor->board_info->gpios[FSIN].gpio);
        }

        module_id = gpio_get_value_cansleep(sensor->board_info->gpios[FSIN].gpio);
        if (module_id < 0) {
            cam_err("%s failed to get gpio(%d) value(%d).\n",
                    __func__, sensor->board_info->gpios[FSIN].gpio, module_id);
        }

        cam_info("%s module_id = %d", __func__,module_id);

        gpio_free(sensor->board_info->gpios[FSIN].gpio);
        if (0 == module_id) {
            cam_info("%s module_id == 0",__func__);
            strncpy(cdata->cfg.name, sensor_name[0], DEVICE_NAME_SIZE-1);
            cdata->data = sensor->board_info->sensor_index;
        } else {
            cam_info("%s module_id == 1", __func__);
            strncpy(cdata->cfg.name, sensor_name[1], DEVICE_NAME_SIZE-1);
            cdata->data = sensor->board_info->sensor_index;
        }
    } else {
        strncpy(cdata->cfg.name, sensor->board_info->name, DEVICE_NAME_SIZE-1);
        cdata->data = sensor->board_info->sensor_index;
    }
    cam_info("%s TODO. cdata->data=%d,cdata->cfg.name = %s", __func__, cdata->data,cdata->cfg.name);
    return 0;
}

static hwsensor_vtbl_t
s_imx179_vtbl =
{
    .get_name = imx179_get_name,
    .config = imx179_config,
    .power_up = imx179_power_up,
    .power_down = imx179_power_down,
    .match_id = imx179_match_id,
    .csi_enable = imx179_csi_enable,
    .csi_disable = imx179_csi_disable,
    .match_id = imx179_match_id,
};

static int
imx179_config(
        hwsensor_intf_t* si,
        void  *argp)
{
    if (NULL == si || NULL == argp){
        cam_err("%s : si or argp is null", __func__);
        return -1;
    }
    struct sensor_cfg_data *data;

    int ret =0;
    static bool imx179_power_on = false;
    data = (struct sensor_cfg_data *)argp;
    cam_debug("imx179 cfgtype = %d",data->cfgtype);
    switch(data->cfgtype){
        case SEN_CONFIG_POWER_ON:
            if (!imx179_power_on) {
                ret = si->vtbl->power_up(si);
                imx179_power_on = true;
            }
            break;
        case SEN_CONFIG_POWER_OFF:
            if (imx179_power_on) {
                ret = si->vtbl->power_down(si);
                imx179_power_on = false;
            }
            break;
        case SEN_CONFIG_WRITE_REG:
            break;
        case SEN_CONFIG_READ_REG:
            break;
        case SEN_CONFIG_WRITE_REG_SETTINGS:
            break;
        case SEN_CONFIG_READ_REG_SETTINGS:
            break;
        case SEN_CONFIG_ENABLE_CSI:
            //ret = si->vtbl->csi_enable(si);
            break;
        case SEN_CONFIG_DISABLE_CSI:
            //ret = si->vtbl->csi_disable(si);
            break;
        case SEN_CONFIG_MATCH_ID:
            ret = si->vtbl->match_id(si,argp);
            break;
        default:
            cam_err("%s cfgtype(%d) is error", __func__, data->cfgtype);
            break;
    }

    return ret;
}

static int32_t
imx179_platform_probe(
        struct platform_device* pdev)
{
    int rc = 0;
    cam_notice("enter %s",__func__);

    if (pdev->dev.of_node) {
        rc = hw_sensor_get_dt_data(pdev, &s_imx179);
        if (rc < 0) {
            cam_err("%s failed line %d\n", __func__, __LINE__);
            goto imx179_sensor_probe_fail;
        }
    } else {
        cam_err("%s imx179 of_node is NULL.\n", __func__);
        goto imx179_sensor_probe_fail;
    }
    s_imx179.dev = &pdev->dev;
    rc = hwsensor_register(pdev, &s_imx179.intf);
    if (0 != rc){
        cam_err("%s hwsensor_register fail.\n", __func__);
        goto imx179_sensor_probe_fail;
    }
    rc = rpmsg_sensor_register(pdev, (void*)&s_imx179);
    if (0 != rc){
        cam_err("%s rpmsg_sensor_register fail.\n", __func__);
        hwsensor_unregister(&s_imx179.intf);
        goto imx179_sensor_probe_fail;
    }
imx179_sensor_probe_fail:
    return rc;
}

static int __init
imx179_init_module(void)
{
    cam_info("Enter: %s", __func__);
    return platform_driver_probe(&s_imx179_driver,
            imx179_platform_probe);
}

static void __exit
imx179_exit_module(void)
{
    rpmsg_sensor_unregister((void*)&s_imx179);
    hwsensor_unregister(&s_imx179.intf);
    platform_driver_unregister(&s_imx179_driver);
}

module_init(imx179_init_module);
module_exit(imx179_exit_module);
MODULE_DESCRIPTION("imx179");
MODULE_LICENSE("GPL v2");

