/************************************************************
*
* Copyright (C), 1988-1999, Huawei Tech. Co., Ltd.
* FileName: cc_tusb320.c
* Author: wangjing(00270068)       Version : 0.1      Date:  2015-1-12
*
* This software is licensed under the terms of the GNU General Public
* License version 2, as published by the Free Software Foundation, and
* may be copied, distributed, and modified under those terms.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
*  Description:    .c file for TI type-c connector chip
*  Version:
*  Function List:
*  History:
*  <author>  <time>   <version >   <desc>
***********************************************************/

#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/timer.h>
#include <linux/param.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/workqueue.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/of_irq.h>
#include <asm/irq.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <huawei_platform/log/hw_log.h>
#ifdef CONFIG_HUAWEI_HW_DEV_DCT
#include <huawei_platform/devdetect/hw_dev_dec.h>
#endif
#include "tusb320.h"
#include <huawei_platform/usb/hw_typec_dev.h>

#ifdef CONFIG_LLT_TEST
#include "tusb320_static_llt.h"
#endif

#define HWLOG_TAG tusb320_typec
HWLOG_REGIST();

static struct i2c_driver tusb320_i2c_driver;
struct typec_device_info *g_tusb320_dev = NULL;
u8 reg_status_val = 0;

/* read i2c start */
static int tusb320_i2c_read(struct typec_device_info *di,
        char *rxData, int length)
{
    int ret = 0;

    struct i2c_msg msgs[] = {
        {
            .addr = di->client->addr,
            .flags = I2C_M_RD,
            .len = length,
            .buf = rxData,
        },
    };

    ret = i2c_transfer(di->client->adapter, msgs, 1);
    if (ret < 0)
    hwlog_err("%s: transfer error %d\n", __func__, ret);

    return ret;
}

static int tusb320_i2c_write(struct typec_device_info *di,
        char *txData, int length)
{
    int ret = 0;

    struct i2c_msg msg[] = {
        {
            .addr = di->client->addr,
            .flags = 0,
            .len = length,
            .buf = txData,
        },
    };

    ret = i2c_transfer(di->client->adapter, msg, 1);
    if (ret < 0)
        hwlog_err("%s: transfer error %d\n", __func__, ret);

    return ret;
}

static int tusb320_read_reg(u8 reg, u8 *val)
{
    int ret;
    u8 buf[1];
    struct typec_device_info *di = g_tusb320_dev;

    buf[0] = reg;
    ret = tusb320_i2c_write(di, buf, 1);
    if (ret < 0) {
        hwlog_err("%s: tusb320_i2c_write error %d\n", __func__, ret);
        return ret;
    }

    ret = tusb320_i2c_read(di, val, 1);
    if (ret < 0) {
        hwlog_err("%s: tusb320_i2c_read error %d\n", __func__, ret);
        return ret;
    }

    return ret;
}

static int tusb320_write_reg(u8 reg, u8 val)
{
    u8 buf[2];
    struct typec_device_info *di = g_tusb320_dev;

    buf[0] = reg;
    buf[1] = val;

    return tusb320_i2c_write(di, buf, 2);
}

static int tusb320_clean_mask(void)
{
    u8 reg_val;
    int ret;

    ret = tusb320_read_reg(TUSB320_REG_ATTACH_STATUS, &reg_val);
    if (ret < 0) {
        hwlog_err("%s: tusb320 tusb320_read_reg error %d\n", __func__, ret);
        return ret;
    }

    reg_val |= TUSB320_REG_STATUS_INT;

    ret = tusb320_write_reg(TUSB320_REG_ATTACH_STATUS, reg_val);
    if (ret < 0) {
        hwlog_err("%s: tusb320 tusb320_write_reg error %d\n", __func__, ret);
        return ret;
    }

    ret = tusb320_read_reg(TUSB320_REG_ATTACH_STATUS, &reg_val);
    if (ret < 0) {
        hwlog_err("%s: tusb320 tusb320_read_reg 0x09 error %d\n", __func__, ret);
        return ret;
    }

    if(reg_val & TUSB320_REG_STATUS_INT) {
        ret = tusb320_write_reg(TUSB320_REG_ATTACH_STATUS,reg_val);
        if (ret < 0) {
            hwlog_err("%s: tusb320 tusb320_write_reg 0x09 error %d\n", __func__, ret);
            return ret;
        }
    }
    return ret;
}

static int tusb320_device_check(void)
{
    u8 reg_val;

    return tusb320_read_reg(TUSB320_REG_DEVICE_ID, &reg_val);
}
/* read i2c end */

static int tusb320_host_current_mode(u8 val)
{
    u8 reg_val, current_set_val, mask_val;
    int ret;

    ret = tusb320_read_reg(TUSB320_REG_CURRENT_MODE, &reg_val);
    if (ret < 0) {
        hwlog_err("%s: read TUSB320_REG_CURRENT_MODE error ret = %d, reg_val = 0x%x\n", __func__, ret, reg_val);
        return ret;
    }

    mask_val = reg_val & (~TUSB320_REG_HOST_CUR_MODE);
    current_set_val = reg_val & TUSB320_REG_HOST_CUR_MODE;

    if (val == current_set_val) {
        hwlog_info("%s: current mode is same as setting\n", __func__);
        return 0;
    }

    val |= mask_val;
    ret = tusb320_write_reg(TUSB320_REG_CURRENT_MODE, val);
    if (ret < 0) {
        hwlog_err("%s: write REG_MODE_SET error ret = %d, reg_val = 0x%x\n", __func__, ret, reg_val);
        return ret;
    }

    return 0;
}

static int tusb320_ctrl_output_current(int value)
{
    switch (value) {
        case TYPEC_HOST_CURRENT_DEFAULT:
            hwlog_info("%s: set to default current\n", __func__);
            tusb320_host_current_mode(TUSB320_REG_HOST_CUR_DEFAULT);
            break;
        case TYPEC_HOST_CURRENT_MID:
            hwlog_info("%s: set to medium current\n", __func__);
            tusb320_host_current_mode(TUSB320_REG_HOST_CUR_MID);
            break;
        case TYPEC_HOST_CURRENT_HIGH:
            hwlog_info("%s: set to high current\n", __func__);
            tusb320_host_current_mode(TUSB320_REG_HOST_CUR_HIGH);
            break;
        default:
            hwlog_err("%s: wrong input action!\n", __func__);
            return -1;
    }

    return 0;
}

static void tusb320_soft_reset(void)
{
    u8 reg_val = 0;
    int ret;

    hwlog_info("%s\n", __func__);

    ret = tusb320_read_reg(TUSB320_REG_MODE_SET, &reg_val);
    if (ret < 0) {
        hwlog_err("%s: read REG_MODE_SET error\n", __func__);
    }

    reg_val |= TUSB320_REG_SET_SOFT_RESET;

    ret = tusb320_write_reg(TUSB320_REG_MODE_SET, reg_val);
    if (ret < 0) {
        hwlog_err("%s: write REG_MODE_SET error\n", __func__);
    }
}

static int tusb320_host_port_mode(u8 val)
{
    u8 reg_val, port_set_val, mask_val;
    int ret;

    ret = tusb320_read_reg(TUSB320_REG_MODE_SET, &reg_val);
    if (ret < 0) {
        hwlog_err("%s: read REG_MODE_SET error ret = %d, reg_val = 0x%x\n", __func__, ret, reg_val);
        return ret;
    }

    mask_val = reg_val & (~TUSB320_REG_SET_PORT_MODE);
    port_set_val = reg_val & TUSB320_REG_SET_PORT_MODE;

    if (val == port_set_val) {
        hwlog_info("%s: port mode is same as setting\n", __func__);
        return 0;
    }

    val |= mask_val;
    ret = tusb320_write_reg(TUSB320_REG_MODE_SET, val);
    if (ret < 0) {
        hwlog_err("%s: write REG_MODE_SET error ret = %d, reg_val = 0x%x\n", __func__, ret, reg_val);
        return ret;
    }

    return 0;
}

static void tusb320_rd_rp_disable(int set)
{
    u8 reg_val = 0;
    int ret;

    ret = tusb320_read_reg(TUSB320_REG_DISABLE, &reg_val);
    if (ret < 0) {
        hwlog_err("%s: read REG_DISABLE error\n", __func__);
    }

    if (set == DISABLE_SET) {
        hwlog_info("%s: set\n", __func__);
        reg_val |= TUSB320_REG_SET_DISABLE_RD_RP;
    } else {
        hwlog_info("%s: clear\n", __func__);
        reg_val &= ~((u8) TUSB320_REG_SET_DISABLE_RD_RP);
    }

    ret = tusb320_write_reg(TUSB320_REG_DISABLE, reg_val);
    if (ret < 0) {
        hwlog_err("%s: write REG_DISABLE error\n", __func__);
    }
}

static int tusb320_ctrl_port_mode(int value)
{
    switch (value) {
        case TYPEC_HOST_PORT_MODE_DFP:
            hwlog_info("%s: set to DFP mode\n", __func__);
            tusb320_host_port_mode(TUSB320_REG_SET_UFP);
            tusb320_rd_rp_disable(DISABLE_SET);
            tusb320_soft_reset();
            mdelay(TUSB320_RESET_DURATION_MS);
            tusb320_host_port_mode(TUSB320_REG_SET_DFP);
            tusb320_rd_rp_disable(DISABLE_CLEAR);
            break;
        case TYPEC_HOST_PORT_MODE_UFP:
            hwlog_info("%s: set to UFP mode\n", __func__);
            tusb320_host_port_mode(TUSB320_REG_SET_UFP);
            tusb320_rd_rp_disable(DISABLE_SET);
            tusb320_soft_reset();
            mdelay(TUSB320_RESET_DURATION_MS);
            tusb320_host_port_mode(TUSB320_REG_SET_UFP);
            tusb320_rd_rp_disable(DISABLE_CLEAR);
            break;
        case TYPEC_HOST_PORT_MODE_DRP:
            hwlog_info("%s: set to DRP mode\n", __func__);
            tusb320_host_port_mode(TUSB320_REG_SET_DRP);
            tusb320_rd_rp_disable(DISABLE_SET);
            tusb320_soft_reset();
            mdelay(TUSB320_RESET_DURATION_MS);
            tusb320_host_port_mode(TUSB320_REG_SET_DRP);
            tusb320_rd_rp_disable(DISABLE_CLEAR);
            break;
        default:
            hwlog_err("%s: wrong input action!\n", __func__);
            return -1;
    }

    return 0;
}

static int tusb320_read_attachment_reg(void)
{
    u8 reg_val;

    tusb320_read_reg(TUSB320_REG_ATTACH_STATUS, &reg_val);
    reg_status_val = reg_val;

    hwlog_info("%s: register value of 09H is 0x%x\n", __func__, reg_status_val);

    return reg_val;
}

static int tusb320_detect_attachment_status(void)
{
    u8 reg_val, mode_val, int_val;
    struct typec_device_info *di = g_tusb320_dev;

    reg_val = tusb320_read_attachment_reg();
    mode_val = reg_val & TUSB320_REG_STATUS_MODE;

    if (mode_val) {
        hwlog_info("%s: tusb320 ATTACH", __func__);
        di->dev_st.attach_status = TYPEC_ATTACH;
    } else {
        hwlog_info("%s: tusb320 DETACH", __func__);
        di->dev_st.attach_status = TYPEC_DETACH;
    }

    return di->dev_st.attach_status;
}

static int tusb320_detect_cc_orientation(void)
{
    u8 reg_val, cc_val;
    struct typec_device_info *di = g_tusb320_dev;

    reg_val = reg_status_val;
    cc_val = reg_val & TUSB320_REG_STATUS_CC;

    if (cc_val) {
        di->dev_st.cc_orient = TYPEC_ORIENT_CC2;
        hwlog_info("%s: CC2 DETECTED, cc_orient = %d\n", __func__, di->dev_st.cc_orient);
    } else {
        di->dev_st.cc_orient = TYPEC_ORIENT_CC1;
        hwlog_info("%s: CC1 DETECTED, cc_orient = %d\n", __func__, di->dev_st.cc_orient);
    }

    return di->dev_st.cc_orient;
}

static int tusb320_detect_port_mode(void)
{
    u8 reg_val, mode_val;
    struct typec_device_info *di = g_tusb320_dev;

    reg_val = reg_status_val;
    mode_val = reg_val & TUSB320_REG_STATUS_MODE;

    if (TUSB320_REG_STATUS_DFP == mode_val) {
        hwlog_info("%s: UFP OTG DETECTED\n", __func__);
        di->dev_st.port_mode = TYPEC_DEV_PORT_MODE_DFP;
    } else if (TUSB320_REG_STATUS_UFP == mode_val) {
        hwlog_info("%s: DFP HOST DETECTED\n", __func__);
        di->dev_st.port_mode = TYPEC_DEV_PORT_MODE_UFP;
    } else {
        hwlog_err("%s: detect port mode error\n", __func__);
        di->dev_st.port_mode = TYPEC_DEV_PORT_MODE_NOT_READY;
    }

    return di->dev_st.port_mode;
}

static int tusb320_detect_input_current(void)
{
    u8 reg_val, current_detect_val;
    struct typec_device_info *di = g_tusb320_dev;

    tusb320_read_reg(TUSB320_REG_CURRENT_MODE, &reg_val);
    current_detect_val = reg_val & TUSB320_REG_DEV_CUR_MODE;

    switch (current_detect_val) {
        case TUSB320_REG_DEV_CUR_HIGH:
            di->dev_st.input_current = TYPEC_DEV_CURRENT_HIGH;
            hwlog_info("%s: detected type c current is 3A, input current = %d\n", __func__, di->dev_st.input_current);
            break;
        case TUSB320_REG_DEV_CUR_MID:
            di->dev_st.input_current = TYPEC_DEV_CURRENT_MID;
            hwlog_info("%s: detected type c current is 1.5A, input current = %d\n", __func__, di->dev_st.input_current);
            break;
        case TUSB320_REG_DEV_CUR_DEFAULT:
            di->dev_st.input_current = TYPEC_DEV_CURRENT_DEFAULT;
            hwlog_info("%s: detected type c current is default, input current = %d\n", __func__, di->dev_st.input_current);
            break;
        default:
            return -1;
    }

    return di->dev_st.input_current;
}

struct typec_device_ops tusb320_ops = {
    .clean_int_mask = tusb320_clean_mask,
    .detect_attachment_status = tusb320_detect_attachment_status,
    .detect_cc_orientation = tusb320_detect_cc_orientation,
    .detect_input_current = tusb320_detect_input_current,
    .detect_port_mode = tusb320_detect_port_mode,
    .ctrl_output_current = tusb320_ctrl_output_current,
    .ctrl_port_mode = tusb320_ctrl_port_mode,
};

static ssize_t dump_regs_show(struct device *dev, struct device_attribute *attr,
                char *buf)
{
    int i;
    u8 reg[TUSB320_REGISTER_NUM] = {0};

    for (i = 8; i < 11; i++) {
        tusb320_read_reg(i, &reg[i]);
    }

    return scnprintf(buf, PAGE_SIZE,
            "0x%02X,0x%02X,0x%02X\n", reg[8], reg[9], reg[10]);
}
static DEVICE_ATTR(dump_regs, S_IRUGO, dump_regs_show, NULL);

static struct attribute *tusb320_attributes[] = {
    &dev_attr_dump_regs.attr,
    NULL,
};

static const struct attribute_group tusb320_attr_group = {
    .attrs = tusb320_attributes,
};

static int tusb320_create_sysfs(void)
{
    int ret = 0;
    struct class *typec_class = NULL;
    struct device *new_dev = NULL;

    typec_class = hw_typec_get_class();
    if (typec_class) {
        new_dev = device_create(typec_class, NULL, 0, NULL, "tusb320");
        ret = sysfs_create_group(&new_dev->kobj, &tusb320_attr_group);
        if (ret) {
            hwlog_err("tusb320 sysfs create error\n");
        }
    }

    return ret;
}

static void tusb320_remove_sysfs(struct typec_device_info *di)
{
    if (NULL == di) {
        hwlog_err("%s: di is NULL when tusb320 remove sysfs\n", __func__);
        return;
    }

    device_remove_file(&di->client->dev, &dev_attr_dump_regs);
}

static irqreturn_t tusb320_irq_handler(int irq, void *dev_id)
{
    int gpio_value_intb = 0;
    struct typec_device_info *di = dev_id;

    hwlog_info("%s: ------entry.\n", __func__);

    gpio_value_intb = gpio_get_value(di->gpio_intb);
    if (1 == gpio_value_intb) {
        hwlog_err("%s: intb high when interrupt occured!!!\n", __func__);
    }

    schedule_work(&di->g_intb_work);

    return IRQ_HANDLED;
}

static void tusb320_initialization(void)
{
    u8 reg_val=0;
    int ret=0;

    ret = tusb320_read_reg(TUSB320_REG_MODE_SET, &reg_val);
    if (ret < 0) {
        hwlog_err("%s: tusb320 tusb320_read_reg error %d\n", __func__, ret);
    }

    reg_val |= TUSB320_REG_SET_SOFT_RESET;

    ret = tusb320_write_reg(TUSB320_REG_MODE_SET, reg_val);
    if (ret < 0) {
        hwlog_err("%s: tusb320 tusb320_write_reg error %d\n", __func__, ret);
    }

    tusb320_host_port_mode(TUSB320_REG_SET_DRP);
}

static int tusb320_probe(
        struct i2c_client *client, const struct i2c_device_id *id)
{
    int ret = 0;
    int gpio_enb_val = 1;
    struct typec_device_info *di = NULL;
    struct typec_device_info *pdi = NULL;
    struct device_node *node;
    int typec_trigger_otg = 0;
    int mdelay = 0;

    di = devm_kzalloc(&client->dev, sizeof(*di), GFP_KERNEL);
    if (!di) {
       hwlog_err("%s: alloc di error!\n", __func__);
       return -ENOMEM;
    }

    g_tusb320_dev = di;
    di->dev = &client->dev;
    di->client = client;
    node = di->dev->of_node;
    i2c_set_clientdata(client, di);

    di->gpio_enb = of_get_named_gpio(node, "tusb320_typec,gpio_enb", 0);
    if (!gpio_is_valid(di->gpio_enb)) {
        hwlog_err("%s: of_get_named_gpio-enb error!!! ret=%d, gpio_enb=%d.\n", __func__, ret, di->gpio_enb);
        ret = -EINVAL;
        goto err_i2c_check_functionality_0;
    }

    ret = gpio_request(di->gpio_enb, "tusb320_en");
    if (ret < 0) {
        hwlog_err("%s: gpio_request error!!! ret=%d. gpio=%d.\n", __func__, ret, di->gpio_enb);
        ret = -ENOMEM;
        goto err_i2c_check_functionality_0;
    }

    ret = of_property_read_u32(node, "tusb320_gpio_enb", &gpio_enb_val);
    if (ret) {
        hwlog_err("%s: read gpio dts value ret=%d. gpio enb=%d.\n", __func__, ret, gpio_enb_val);
        ret = -EINVAL;
        goto err_gpio_enb_request_1;
    }

    hwlog_info("%s: read gpio dts value gpio enb=%d.\n", __func__, gpio_enb_val);
    ret = gpio_direction_output(di->gpio_enb, gpio_enb_val);
    if (ret < 0) {
        hwlog_err("%s: gpio_direction_input error!!! ret=%d. gpio=%d.\n", __func__, ret, di->gpio_enb);
        goto err_gpio_enb_request_1;
    }

    /* T_I2C_EN in the SPEC, time from enable signal active to I2C access available */
    ret = of_property_read_u32(node, "tusb320_mdelay", &mdelay);
    if (ret) {
        hwlog_err("%s: get mdelay error\n", __func__);
        mdelay = 0;
    }

    if(mdelay)
    {
        hwlog_info("%s: wait for %d ms before i2c access\n", __func__, mdelay);
        msleep(mdelay);
    }

    ret = tusb320_device_check();
    if (ret < 0) {
        hwlog_err("%s: the chip is not tusb320!!!\n", __func__);
        goto err_gpio_enb_request_1;
    }

    of_property_read_u32(node, "typec_trigger_otg", &typec_trigger_otg);
    di->typec_trigger_otg = !!typec_trigger_otg;
    hwlog_info("%s: typec_trigger_otg = %d\n", __func__, typec_trigger_otg);

    pdi = typec_chip_register(di, &tusb320_ops, THIS_MODULE);
    if (NULL == pdi) {
        hwlog_err("%s: typec register chip error!\n", __func__);
        ret = -EINVAL;
        goto err_gpio_enb_request_1;
    }

    di->gpio_intb = of_get_named_gpio(node, "tusb320_typec,gpio_intb", 0);
    if (!gpio_is_valid(di->gpio_intb)) {
        hwlog_err("%s: of_get_named_gpio-intb error!!! ret=%d, gpio_intb=%d.\n", __func__, ret, di->gpio_intb);
        ret = -EINVAL;
        goto err_gpio_enb_request_1;
    }

    ret = gpio_request(di->gpio_intb, "tusb320_int");
    if (ret < 0) {
        hwlog_err("%s: gpio_request error!!! ret=%d. gpio_intb=%d.\n", __func__, ret, di->gpio_intb);
        ret = -ENOMEM;
        goto err_gpio_enb_request_1;
    }

    di->irq_intb = gpio_to_irq(di->gpio_intb);
    if (di->irq_intb < 0) {
        hwlog_err("%s: gpio_to_irq error!!! ret=%d, gpio_intb=%d, irq_intb=%d.\n", __func__, ret, di->gpio_intb, di->irq_intb);
        goto err_gpio_intb_request_2;
    }

    ret = gpio_direction_input(di->gpio_intb);
    if (ret < 0) {
        hwlog_err("%s: gpio_direction_input error!!! ret=%d. gpio_intb=%d.\n", __func__, ret, di->gpio_intb);
        goto err_gpio_intb_request_2;
    }

    ret = request_irq(di->irq_intb,
               tusb320_irq_handler,
               IRQF_NO_SUSPEND | IRQF_TRIGGER_FALLING,
               "tusb320_int", pdi);
    if (ret) {
        hwlog_err("%s: request_irq error!!! ret=%d.\n", __func__, ret);
        di->irq_intb = -1;
        goto err_gpio_intb_request_2;
    }

    ret = tusb320_clean_mask();
    if (ret < 0) {
        hwlog_err("%s: clear interrupt mask error %d\n", __func__, ret);
        goto err_gpio_intb_request_2;
    }

    ret = tusb320_create_sysfs();
    if (ret < 0) {
        hwlog_err("%s: create sysfs error %d\n", __func__, ret);
        goto err_irq_request_3;
    }

#ifdef CONFIG_HUAWEI_HW_DEV_DCT
    /* detect current device successful, set the flag as present */
    set_hw_dev_flag(DEV_I2C_TYPEC);
#endif

    tusb320_initialization();

#ifdef CONFIG_DUAL_ROLE_USB_INTF
    /* set current advertisement to high */
    tusb320_ctrl_output_current(TYPEC_HOST_CURRENT_HIGH);
#endif

    hwlog_info("%s: ------end.\n", __func__);
    return ret;

err_irq_request_3:
    tusb320_remove_sysfs(di);
    free_irq(di->gpio_intb, di);
err_gpio_intb_request_2:
    gpio_free(di->gpio_intb);
err_gpio_enb_request_1:
    gpio_free(di->gpio_enb);
err_i2c_check_functionality_0:
    g_tusb320_dev = NULL;
    devm_kfree(&client->dev, di);
    di = NULL;

    hwlog_err("%s: ------FAIL!!! end. ret = %d.\n", __func__, ret);
    return ret;
}

static int tusb320_remove(struct i2c_client *client)
{
    struct typec_device_info *di = i2c_get_clientdata(client);

    tusb320_remove_sysfs(di);
    free_irq(di->irq_intb, di);
    gpio_set_value(di->gpio_enb, 1);
    gpio_free(di->gpio_enb);
    gpio_free(di->gpio_intb);
    g_tusb320_dev = NULL;
    devm_kfree(&client->dev, di);
    di = NULL;

    return 0;
}

static const struct of_device_id typec_tusb320_ids[] = {
    { .compatible = "huawei,tusb320" },
    {},
};
MODULE_DEVICE_TABLE(of, typec_tusb320_ids);

static const struct i2c_device_id tusb320_i2c_id[] = {
    { "tusb320", 0 },
    { }
};

static struct i2c_driver tusb320_i2c_driver = {
    .driver = {
        .name = "tusb320",
        .owner = THIS_MODULE,
        .of_match_table = of_match_ptr(typec_tusb320_ids),
    },
    .probe = tusb320_probe,
    .remove = tusb320_remove,
    .id_table = tusb320_i2c_id,
};

static __init int tusb320_i2c_init(void)
{
    int ret = 0;

    ret = i2c_add_driver(&tusb320_i2c_driver);
    if (ret) {
        hwlog_err("%s: i2c_add_driver error!!!\n", __func__);
    }

    hwlog_info("%s: ------end.\n", __func__);
    return ret;
}

static __exit void tusb320_i2c_exit(void)
{
    i2c_del_driver(&tusb320_i2c_driver);
}

#ifdef CONFIG_LLT_TEST
#include "tusb320_static_llt.c"
#endif

module_init(tusb320_i2c_init);
module_exit(tusb320_i2c_exit);

MODULE_AUTHOR("WangJing<wangjing6@huawei.com>");
MODULE_DESCRIPTION("I2C bus driver for tusb320 type c connector");
MODULE_LICENSE("GPL v2");
