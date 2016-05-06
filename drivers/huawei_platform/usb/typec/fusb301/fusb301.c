/************************************************************
*
* Copyright (C), 1988-1999, Huawei Tech. Co., Ltd.
* FileName: cc_fusb301.c
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
*  Description:    .c file for Fairchild type-c connector chip
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
#include "fusb301.h"
#include <huawei_platform/usb/hw_typec_dev.h>
#include <linux/reboot.h>

#define HWLOG_TAG fusb301_typec
HWLOG_REGIST();

static struct i2c_driver fusb301_i2c_driver;
static struct notifier_block reboot_nb;
struct typec_device_info *g_fusb301_dev = NULL;

static int fusb301_i2c_read(struct typec_device_info *di, u8 reg)
{
    int ret = 0;
    ret = i2c_smbus_read_byte_data(di->client, reg);
    if (ret < 0) {
        hwlog_err("%s: fusb301_i2c_smbus read byte error %d\n", __func__, ret);
    }

    return ret;
}

static int fusb301_i2c_write(struct typec_device_info *di, u8 reg, u8 val)
{
    int ret = 0;
    ret = i2c_smbus_write_byte_data(di->client, reg, val);
    if (ret < 0) {
        hwlog_err("%s: fusb301_i2c_smbus write byte error %d\n", __func__, ret);
    }

    return ret;
}

static int fusb301_read_reg(u8 reg, u8 *val)
{
    int ret = 0;
    struct typec_device_info *di = g_fusb301_dev;

    ret = fusb301_i2c_read(di, reg);
    if(ret < 0)
        return ret;

    *val = ret;
    return ret;
}

static int fusb301_write_reg(u8 reg, u8 val)
{
    struct typec_device_info *di = g_fusb301_dev;

    return fusb301_i2c_write(di, reg, val);
}

static int fusb301_clean_mask(void)
{
    u8 reg_val;
    int ret;

    ret = fusb301_read_reg(FUSB301_REG_CONTROL, &reg_val);
    if (ret < 0) {
        hwlog_err("%s: fusb301 fusb301_read_reg error %d\n", __func__, ret);
        return ret;
    }

    reg_val &= ~FUSB301_REG_INT_MASK;

    ret = fusb301_write_reg(FUSB301_REG_CONTROL, reg_val);
    if (ret < 0) {
        hwlog_err("%s: fusb301 fusb301_write_reg error %d\n", __func__, ret);
        return ret;
    }

    return ret;
}

static int fusb301_device_check(void)
{
    u8 reg_val;

    return fusb301_read_reg(FUSB301_REG_DEVICE_ID, &reg_val);
}
/* read i2c end */

static int fusb301_host_current_mode(u8 val)
{
    u8 reg_val = 0, current_set_val, mask_val;
    int ret;

    ret = fusb301_read_reg(FUSB301_REG_CONTROL, &reg_val);
    if (ret < 0) {
        hwlog_err("%s: read FUSB301_REG_CONTROL error ret = %d, reg_val = 0x%x\n", __func__, ret, reg_val);
        return ret;
    }

    mask_val = reg_val & (~FUSB301_REG_HOST_CUR_MODE);
    current_set_val = reg_val & FUSB301_REG_HOST_CUR_MODE;

    if (val == current_set_val) {
        hwlog_info("%s: current mode is same as setting\n", __func__);
        return 0;
    }

    val |= mask_val;
    ret = fusb301_write_reg(FUSB301_REG_CONTROL, val);
    if (ret < 0) {
        hwlog_err("%s: write REG_MODE_SET error ret = %d, reg_val = 0x%x\n", __func__, ret, reg_val);
        return ret;
    }

    return 0;
}

static int fusb301_ctrl_output_current(int value)
{
    switch (value) {
        case TYPEC_HOST_CURRENT_DEFAULT:
            hwlog_info("%s: set to default current\n", __func__);
            fusb301_host_current_mode(FUSB301_REG_HOST_CUR_DEFAULT);
            break;
        case TYPEC_HOST_CURRENT_MID:
            hwlog_info("%s: set to medium current\n", __func__);
            fusb301_host_current_mode(FUSB301_REG_HOST_CUR_MID);
            break;
        case TYPEC_HOST_CURRENT_HIGH:
            hwlog_info("%s: set to high current\n", __func__);
            fusb301_host_current_mode(FUSB301_REG_HOST_CUR_HIGH);
            break;
        default:
            hwlog_err("%s: wrong input action!\n", __func__);
            return -1;
    }

    return 0;
}

static int fusb301_host_port_mode(u8 val)
{
    u8 reg_val = 0;
    int ret;

    ret = fusb301_read_reg(FUSB301_REG_PORT_MODE, &reg_val);
    if (ret < 0) {
        hwlog_err("%s: read REG_MODE_SET error ret = %d, reg_val = 0x%x\n", __func__, ret, reg_val);
        return ret;
    }

    if (val == reg_val) {
        hwlog_info("%s: port mode is same as setting\n", __func__);
        return 0;
    }

    ret = fusb301_write_reg(FUSB301_REG_PORT_MODE, val);
    if (ret < 0) {
        hwlog_err("%s: write REG_MODE_SET error ret = %d, reg_val = 0x%x\n", __func__, ret, reg_val);
        return ret;
    }

    return 0;
}

static void fusb301_set_port_state(int value)
{
    switch (value) {
        case TYPEC_STATE_UNATTACHED_SINK:
            hwlog_info("%s: set to Unattached.SNK\n", __func__);
            fusb301_write_reg(FUSB301_REG_MANUAL, FUSB301_REG_MANUAL_UNATTACHED_SINK);
            break;
        case TYPEC_STATE_UNATTACHED_SOURCE:
            hwlog_info("%s: set to Unattached.SRC\n", __func__);
            fusb301_write_reg(FUSB301_REG_MANUAL, FUSB301_REG_MANUAL_UNATTACHED_SOURCE);
            break;
        case TYPEC_STATE_UNATTACHED_DISABLED:
            hwlog_info("%s: set to Disabled\n", __func__);
            fusb301_write_reg(FUSB301_REG_MANUAL, FUSB301_REG_MANUAL_UNATTACHED_DISABLED);
            break;
         case TYPEC_STATE_UNATTACHED_ERRORRECOVERY:
             hwlog_info("%s: set to ErrorRecovery\n", __func__);
             fusb301_write_reg(FUSB301_REG_MANUAL, FUSB301_REG_MANUAL_UNATTACHED_ERRORRECOVERY);
             break;
        default:
            hwlog_err("%s: wrong input action!\n", __func__);
    }
}

static int fusb301_ctrl_port_mode(int value)
{
    switch (value) {
        case TYPEC_HOST_PORT_MODE_DFP:
            hwlog_info("%s: set to DFP mode\n", __func__);
            fusb301_host_port_mode(FUSB301_REG_SET_DFP);
            fusb301_set_port_state(TYPEC_STATE_UNATTACHED_SOURCE);
            break;
        case TYPEC_HOST_PORT_MODE_UFP:
            hwlog_info("%s: set to UFP mode\n", __func__);
            fusb301_host_port_mode(FUSB301_REG_SET_UFP);
            fusb301_set_port_state(TYPEC_STATE_UNATTACHED_DISABLED);
            mdelay(DISABLE_DURATION_MS);
            fusb301_host_port_mode(FUSB301_REG_SET_UFP);
            fusb301_set_port_state(TYPEC_STATE_UNATTACHED_SINK);
            break;
        case TYPEC_HOST_PORT_MODE_DRP:
            hwlog_info("%s: set to DRP mode\n", __func__);
            fusb301_host_port_mode(FUSB301_REG_SET_DRP);
            fusb301_set_port_state(TYPEC_STATE_UNATTACHED_DISABLED);
            mdelay(DISABLE_DURATION_MS);
            fusb301_host_port_mode(FUSB301_REG_SET_DRP);
            fusb301_set_port_state(TYPEC_STATE_UNATTACHED_SINK);
            break;
        default:
            hwlog_err("%s: wrong input action!\n", __func__);
            return -1;
    }

    return 0;
}

static int fusb301_detect_attachment_status(void)
{
    int ret = 0;
    u8 reg_val = 0;
    struct typec_device_info *di = g_fusb301_dev;

    ret = fusb301_read_reg(FUSB301_REG_INT, &reg_val);
    if (ret < 0) {
        hwlog_err("%s: read REG_INT error ret = %d, reg_val = 0x%x\n", __func__, ret, reg_val);
        return ret;
    }

    if (reg_val & FUSB301_REG_INT_ATTACH) {
        hwlog_info("%s: fusb301 ATTACH", __func__);
        di->dev_st.attach_status = TYPEC_ATTACH;
    } else if (reg_val & FUSB301_REG_INT_DETACH) {
        hwlog_info("%s: fusb301 DETACH", __func__);
        di->dev_st.attach_status = TYPEC_DETACH;
    } else if (reg_val & FUSB301_REG_INT_CC_CUR_CH) {
        hwlog_info("%s: interrupt of BC_LVL", __func__);
        di->dev_st.attach_status = TYPEC_CUR_CHANGE_FOR_FSC;
    } else if (reg_val & FUSB301_REG_INT_ACC_CH) {
        hwlog_info("%s: interrupt of accessory change", __func__);
        di->dev_st.attach_status = TYPEC_ACC_MODE_CHANGE;
    } else {
        hwlog_err("%s: wrong interrupt!\n", __func__);
        di->dev_st.attach_status = TYPEC_STATUS_NOT_READY;
    }

    return di->dev_st.attach_status;
}

static int fusb301_detect_cc_orientation(void)
{
    int ret = 0;
    u8 reg_val = 0, cc_val;
    struct typec_device_info *di = g_fusb301_dev;

    ret = fusb301_read_reg(FUSB301_REG_STATUS, &reg_val);
    if (ret < 0) {
        hwlog_err("%s: read REG_STATUS error ret = %d, reg_val = 0x%x\n", __func__, ret, reg_val);
        return ret;
    }

    cc_val = reg_val & FUSB301_REG_CC_STATUS;

    if (FUSB301_REG_CC2_DETECTED == cc_val) {
        di->dev_st.cc_orient = TYPEC_ORIENT_CC2;
        hwlog_info("%s: CC2 DETECTED, cc_orient = %d\n", __func__, di->dev_st.cc_orient);
    } else if (FUSB301_REG_CC1_DETECTED == cc_val) {
        di->dev_st.cc_orient = TYPEC_ORIENT_CC1;
        hwlog_info("%s: CC1 DETECTED, cc_orient = %d\n", __func__, di->dev_st.cc_orient);
    } else if (FUSB301_REG_NO_CC_DETECTED == cc_val) {
        di->dev_st.cc_orient = TYPEC_ORIENT_DEFAULT;
        hwlog_info("%s: NO CC has been DETECTED, cc_orient = %d\n", __func__, di->dev_st.cc_orient);
    } else if (FUSB301_REG_CC_FAULT == cc_val) {
        di->dev_st.cc_orient = TYPEC_ORIENT_NOT_READY;
        hwlog_info("%s: There is a CC detection fault!!!, cc_orient = %d\n", __func__, di->dev_st.cc_orient);
    }

    return di->dev_st.cc_orient;
}

static int fusb301_detect_port_mode(void)
{
    int ret = 0;
    u8 reg_val = 0;
    struct typec_device_info *di = g_fusb301_dev;

    ret = fusb301_read_reg(FUSB301_REG_TYPE, &reg_val);
    if (ret < 0) {
        hwlog_err("%s: read REG_STATUS error ret = %d, reg_val = 0x%x\n", __func__, ret, reg_val);
        return ret;
    }

    if (reg_val & FUSB301_REG_STATUS_DFP) {
        hwlog_info("%s: UFP OTG DETECTED\n", __func__);
        di->dev_st.port_mode = TYPEC_DEV_PORT_MODE_DFP;
    } else if (reg_val & FUSB301_REG_STATUS_UFP) {
        hwlog_info("%s: DFP HOST DETECTED\n", __func__);
        di->dev_st.port_mode = TYPEC_DEV_PORT_MODE_UFP;
    } else if (reg_val & FUSB301_REG_STATUS_POWERACC) {
        hwlog_info("%s: POWER ACCESSORY OTG is DETECTED\n", __func__);
        di->dev_st.port_mode = TYPEC_DEV_PORT_MODE_DFP;
    } else if (reg_val & FUSB301_REG_STATUS_DEBUGACC) {
        hwlog_info("%s: DEBUG ACCESSORY is DETECTED\n", __func__);
        di->dev_st.port_mode = TYPEC_DEV_PORT_MODE_DEBUGACC;
    } else if (reg_val & FUSB301_REG_STATUS_AUDIOACC) {
        hwlog_info("%s: AUDIO ACCESSORY is DETECTED\n", __func__);
        di->dev_st.port_mode = TYPEC_DEV_PORT_MODE_AUDIOACC;
    } else {
        hwlog_err("%s: detect port mode error\n", __func__);
        di->dev_st.port_mode = TYPEC_DEV_PORT_MODE_NOT_READY;
    }

    return di->dev_st.port_mode;
}

static int fusb301_detect_input_current(void)
{
    int ret = 0;
    u8 reg_val = 0, current_detect_val;
    struct typec_device_info *di = g_fusb301_dev;

    ret = fusb301_read_reg(FUSB301_REG_STATUS, &reg_val);
    if (ret < 0) {
        hwlog_err("%s: read REG_STATUS error ret = %d, reg_val = 0x%x\n", __func__, ret, reg_val);
        return ret;
    }

    current_detect_val = reg_val & FUSB301_REG_DEV_CUR_MODE;

    switch (current_detect_val) {
        case FUSB301_REG_DEV_CUR_HIGH:
            di->dev_st.input_current = TYPEC_DEV_CURRENT_HIGH;
            hwlog_info("%s: detected type c current is 3A, input current = %d\n", __func__, di->dev_st.input_current);
            break;
        case FUSB301_REG_DEV_CUR_MID:
            di->dev_st.input_current = TYPEC_DEV_CURRENT_MID;
            hwlog_info("%s: detected type c current is 1.5A, input current = %d\n", __func__, di->dev_st.input_current);
            break;
        case FUSB301_REG_DEV_CUR_DEFAULT:
            di->dev_st.input_current = TYPEC_DEV_CURRENT_DEFAULT;
            hwlog_info("%s: detected type c current is default, input current = %d\n", __func__, di->dev_st.input_current);
            break;
        default:
            hwlog_err("%s: detect typec c current error!!!, reg_val = 0x%x\n", __func__, reg_val);
            return -1;
    }

    return di->dev_st.input_current;
}

struct typec_device_ops fusb301_ops = {
    .clean_int_mask = fusb301_clean_mask,
    .detect_attachment_status = fusb301_detect_attachment_status,
    .detect_cc_orientation = fusb301_detect_cc_orientation,
    .detect_input_current = fusb301_detect_input_current,
    .detect_port_mode = fusb301_detect_port_mode,
    .ctrl_output_current = fusb301_ctrl_output_current,
    .ctrl_port_mode = fusb301_ctrl_port_mode,
};

static ssize_t dump_regs_show(struct device *dev, struct device_attribute *attr,
                char *buf)
{
    int i, index;
    u8 reg_val = 0;
    const int regaddr[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x10, 0x11, 0x12, 0x13};
    const char str[] = "0123456789abcdef";

    /* If there is no register value, replace it with xx */
    for (i = 0; i < 3 * FUSB301_REGISTER_NUM; i++) {
        if (2 == (i % 3))
            buf[i] = ' ';
        else
            buf[i] = 'x';
    }

    buf[0x2f] = '\n';   //change line for better print type
    buf[0x5f] = '\0';

    for (i = 0; i < ARRAY_SIZE(regaddr); i++) {
        index = regaddr[i];
        fusb301_read_reg(index, &reg_val);
        buf[3 * index] = str[(reg_val & 0xf0) >> 4];
        buf[3 * index + 1] = str[reg_val & 0x0f];
        buf[3 * index + 2] = ' ';
    }

    return 0x60;
}
static DEVICE_ATTR(dump_regs, S_IRUGO, dump_regs_show, NULL);

static struct attribute *fusb301_attributes[] = {
    &dev_attr_dump_regs.attr,
    NULL,
};

static const struct attribute_group fusb301_attr_group = {
    .attrs = fusb301_attributes,
};

static int fusb301_create_sysfs(void)
{
    int ret = 0;
    struct class *typec_class = NULL;
    struct device *new_dev = NULL;

    typec_class = hw_typec_get_class();
    if (typec_class) {
        new_dev = device_create(typec_class, NULL, 0, NULL, "fusb301");
        ret = sysfs_create_group(&new_dev->kobj, &fusb301_attr_group);
        if (ret) {
            hwlog_err("fusb301 sysfs create error\n");
        }
    }

    return ret;
}

static void fusb301_remove_sysfs(struct typec_device_info *di)
{
    if (NULL == di) {
        hwlog_err("%s: di is NULL when fusb301 remove sysfs\n", __func__);
        return;
    }

    device_remove_file(&di->client->dev, &dev_attr_dump_regs);
}

static irqreturn_t fusb301_irq_handler(int irq, void *dev_id)
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

static void fusb301_initialization(void)
{
    int attach_status;
    /* read FUSB301_REG_INT register to clear the irq first */
    attach_status = fusb301_detect_attachment_status();
    fusb301_ctrl_port_mode(TYPEC_HOST_PORT_MODE_DRP);
    fusb301_clean_mask();
}

static int fusb301_shutdown_prepare(struct notifier_block *nb, unsigned long event, void *_data)
{
    switch (event)
    {
        case SYS_DOWN:
        case SYS_HALT:
        case SYS_POWER_OFF:
            hwlog_err("fusb301 prepare to shutdown, event = %ld\n",event);
            fusb301_ctrl_port_mode(TYPEC_HOST_PORT_MODE_UFP);
            break;
        default:
            hwlog_err("error event, fusb301 ignore, event = %ld\n",event);
            break;
    }
    return NOTIFY_OK;
}

static int fusb301_probe(
        struct i2c_client *client, const struct i2c_device_id *id)
{
    int ret = 0;
    int gpio_enb_val = 1;
    struct typec_device_info *di = NULL;
    struct typec_device_info *pdi = NULL;
    struct device_node *node;
    int typec_trigger_otg = 0;
    reboot_nb.notifier_call = NULL;

    di = devm_kzalloc(&client->dev, sizeof(*di), GFP_KERNEL);
    if (!di) {
       hwlog_err("%s: alloc di error!\n", __func__);
       return -ENOMEM;
    }

    g_fusb301_dev = di;
    di->dev = &client->dev;
    di->client = client;
    node = di->dev->of_node;
    i2c_set_clientdata(client, di);

    if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA)) {
        hwlog_err("%s: i2c_check_functionality checkfailed\n", __func__);
        goto err_i2c_check_functionality_0;
    }

    di->gpio_enb = of_get_named_gpio(node, "fusb301_typec,gpio_enb", 0);
    if (!gpio_is_valid(di->gpio_enb)) {
        hwlog_err("%s: of_get_named_gpio-enb error!!! ret=%d, gpio_enb=%d.\n", __func__, ret, di->gpio_enb);
        ret = -EINVAL;
        goto err_i2c_check_functionality_0;
    }

    ret = gpio_request(di->gpio_enb, "fusb301_en");
    if (ret < 0) {
        hwlog_err("%s: gpio_request error!!! ret=%d. gpio=%d.\n", __func__, ret, di->gpio_enb);
        ret = -ENOMEM;
        goto err_i2c_check_functionality_0;
    }

    ret = of_property_read_u32(node, "fusb301_gpio_enb", &gpio_enb_val);
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

    ret = fusb301_device_check();
    if (ret < 0) {
        hwlog_err("%s: the chip is not fusb301!!!\n", __func__);
        goto err_gpio_enb_request_1;
    }

    reboot_nb.notifier_call = fusb301_shutdown_prepare;
    register_reboot_notifier(&reboot_nb);

    of_property_read_u32(node, "typec_trigger_otg", &typec_trigger_otg);
    di->typec_trigger_otg = !!typec_trigger_otg;
    hwlog_info("%s: typec_trigger_otg = %d\n", __func__, typec_trigger_otg);

    pdi = typec_chip_register(di, &fusb301_ops, THIS_MODULE);
    if (NULL == pdi) {
        hwlog_err("%s: typec register chip error!\n", __func__);
        ret = -EINVAL;
        goto err_gpio_enb_request_1;
    }

    di->gpio_intb = of_get_named_gpio(node, "fusb301_typec,gpio_intb", 0);
    if (!gpio_is_valid(di->gpio_intb)) {
        hwlog_err("%s: of_get_named_gpio-intb error!!! ret=%d, gpio_intb=%d.\n", __func__, ret, di->gpio_intb);
        ret = -EINVAL;
        goto err_gpio_enb_request_1;
    }

    ret = gpio_request(di->gpio_intb, "fusb301_int");
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
               fusb301_irq_handler,
               IRQF_NO_SUSPEND | IRQF_TRIGGER_FALLING,
               "fusb301_int", pdi);
    if (ret) {
        hwlog_err("%s: request_irq error!!! ret=%d.\n", __func__, ret);
        di->irq_intb = -1;
        goto err_gpio_intb_request_2;
    }

    ret = fusb301_create_sysfs();
    if (ret < 0) {
        hwlog_err("%s: create sysfs error %d\n", __func__, ret);
        goto err_irq_request_3;
    }

    fusb301_initialization();

#ifdef CONFIG_HUAWEI_HW_DEV_DCT
    /* detect current device successful, set the flag as present */
    set_hw_dev_flag(DEV_I2C_TYPEC);
#endif

#ifdef CONFIG_DUAL_ROLE_USB_INTF
    /* set current advertisement to high */
    fusb301_ctrl_output_current(TYPEC_HOST_CURRENT_HIGH);
#endif

    hwlog_info("%s: ------end.\n", __func__);
    return ret;

err_irq_request_3:
    fusb301_remove_sysfs(di);
    free_irq(di->gpio_intb, di);
err_gpio_intb_request_2:
    gpio_free(di->gpio_intb);
err_gpio_enb_request_1:
    if(NULL != reboot_nb.notifier_call)
    {
        unregister_reboot_notifier(&reboot_nb);
    }
    gpio_free(di->gpio_enb);
err_i2c_check_functionality_0:
    g_fusb301_dev = NULL;
    devm_kfree(&client->dev, di);
    di = NULL;

    hwlog_err("%s: ------FAIL!!! end. ret = %d.\n", __func__, ret);
    return ret;
}

static int fusb301_remove(struct i2c_client *client)
{
    struct typec_device_info *di = i2c_get_clientdata(client);

    fusb301_remove_sysfs(di);
    free_irq(di->irq_intb, di);
    gpio_set_value(di->gpio_enb, 1);
    gpio_free(di->gpio_enb);
    gpio_free(di->gpio_intb);
    g_fusb301_dev = NULL;
    devm_kfree(&client->dev, di);
    di = NULL;

    return 0;
}

static const struct of_device_id typec_fusb301_ids[] = {
    { .compatible = "huawei,fusb301" },
    {},
};
MODULE_DEVICE_TABLE(of, typec_fusb301_ids);

static const struct i2c_device_id fusb301_i2c_id[] = {
    { "fusb301", 0 },
    { }
};

static struct i2c_driver fusb301_i2c_driver = {
    .driver = {
        .name = "fusb301",
        .owner = THIS_MODULE,
        .of_match_table = of_match_ptr(typec_fusb301_ids),
    },
    .probe = fusb301_probe,
    .remove = fusb301_remove,
    .id_table = fusb301_i2c_id,
};

static __init int fusb301_i2c_init(void)
{
    int ret = 0;

    ret = i2c_add_driver(&fusb301_i2c_driver);
    if (ret) {
        hwlog_err("%s: i2c_add_driver error!!!\n", __func__);
    }

    hwlog_info("%s: ------end.\n", __func__);
    return ret;
}

static __exit void fusb301_i2c_exit(void)
{
    i2c_del_driver(&fusb301_i2c_driver);
}

module_init(fusb301_i2c_init);
module_exit(fusb301_i2c_exit);

MODULE_AUTHOR("WangJing<wangjing6@huawei.com>");
MODULE_DESCRIPTION("I2C bus driver for fusb301 type c connector");
MODULE_LICENSE("GPL v2");
