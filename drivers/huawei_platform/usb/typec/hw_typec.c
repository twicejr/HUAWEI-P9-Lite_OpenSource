/************************************************************
*
* Copyright (C), 1988-1999, Huawei Tech. Co., Ltd.
* FileName: hw_typec.c
* Author: wangjing(00270068)       Version : 0.1      Date:  2015-5-28
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
*  Description:    .c file for type-c core layer which is used to handle
*                  pulic logic management for different chips and to
*                  provide interfaces for exteranl modules.
*  Version:
*  Function List:
*  History:
*  <author>  <time>   <version >   <desc>
***********************************************************/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/jiffies.h>
#include <linux/wakelock.h>
#include <linux/io.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/notifier.h>
#include <linux/mutex.h>
#include <huawei_platform/log/hw_log.h>
#include <huawei_platform/usb/hw_typec_dev.h>
#include <huawei_platform/usb/hw_typec_platform.h>
#include <linux/huawei/usb/hisi_usb.h>
#include "../switch/switch_usb_class.h"
#ifdef CONFIG_DUAL_ROLE_USB_INTF
#include <huawei_platform/usb/class-dual-role.h>
#endif
#ifdef CONFIG_HUAWEI_HW_DEV_DCT
#include <huawei_platform/devdetect/hw_dev_dec.h>
#endif
#define HWLOG_TAG huawei_typec
HWLOG_REGIST();

struct typec_device_info *g_typec_dev = NULL;
struct class *typec_class = NULL;
struct device *typec_dev = NULL;

/**
 * typec_detect_attachment_status() - detect the usb state(attach or detach).
 */
static int typec_detect_attachment_status(void)
{
    struct typec_device_info *di = g_typec_dev;

    if (NULL == di->ops || NULL == di->ops->detect_attachment_status) {
        hwlog_err("%s: NULL pointer!!!\n", __func__);
        return -ENOMEM;
    }

    return di->ops->detect_attachment_status();
}

/**
 * typec_detect_port_mode() - detect port mode as a result of ID detection on cc pins.
 * DFP means host, while UFP means slave. As a distinctive mode of type-c protocol,
 * DRP can switch between DFP and UFP alternatively with the management of driver.
 */
static int typec_detect_port_mode(void)
{
    struct typec_device_info *di = g_typec_dev;

    if (NULL == di->ops || NULL == di->ops->detect_port_mode) {
        hwlog_err("%s: NULL pointer!!!\n", __func__);
        return -ENOMEM;
    }

    return di->ops->detect_port_mode();
}

/**
 * typec_detect_cc_orientation() - detect inserted plug orientation of type-c devices.
 */
int typec_detect_cc_orientation(void)
{
    struct typec_device_info *di = g_typec_dev;

    if (NULL == di->ops || NULL == di->ops->detect_cc_orientation) {
        hwlog_err("%s: NULL pointer!!!\n", __func__);
        return -ENOMEM;
    }

    return di->ops->detect_cc_orientation();
}
EXPORT_SYMBOL_GPL(typec_detect_cc_orientation);

/**
 * typec_current_mode_detect() - detect type-c protocol defined current,
 * which may be called by Charge IC or other related modules.
 */
int typec_current_mode_detect(void)
{
    struct typec_device_info *di = g_typec_dev;

    if (NULL == di->ops || NULL == di->ops->detect_input_current) {
        hwlog_err("%s: NULL pointer!!!\n", __func__);
        return -ENOMEM;
    }

    return di->ops->detect_input_current();
}
EXPORT_SYMBOL_GPL(typec_current_mode_detect);

/**
 * typec_clean_int_mask() - clean interrupt mask and wait for the next interrupt.
 */
static int typec_clean_int_mask(void)
{
    struct typec_device_info *di = g_typec_dev;

    if (NULL == di->ops || NULL == di->ops->clean_int_mask) {
        hwlog_err("%s: NULL pointer!!!\n", __func__);
        return -ENOMEM;
    }

    return di->ops->clean_int_mask();
}

/**
 * typec_open_otg() - start otg work by calling related modules.
 * fsa9685_manual_sw() is to connect USB signal path.
 * hisi_usb_id_change() is to open VBUS to charge slave devices.
 */
static void typec_open_otg(void)
{
    fsa9685_dcd_timeout_enable(true);
    fsa9685_manual_sw(FSA9685_USB1_ID_TO_IDBYPASS);
    mdelay(10);
    hisi_usb_id_change(ID_FALL_EVENT);
}

/**
 * typec_close_otg() - stop otg work as a pair of typec_open_otg().
 */
static void typec_close_otg(void)
{
    fsa9685_dcd_timeout_enable(false);
    hisi_usb_id_change(ID_RISE_EVENT);
}

/**
 * typec_output_current_store() - create a device node to control type-c protocol current
 * when as a DFP host, charging the UFP slave one.
 */
static ssize_t typec_output_current_store(struct device *dev,
            struct device_attribute *attr, const char *buf, size_t size)
{
    int value;
    struct typec_device_info *di = g_typec_dev;

    if (NULL == di->ops || NULL == di->ops->ctrl_output_current) {
        hwlog_err("%s: NULL pointer!!!\n", __func__);
        return -ENOMEM;
    }

    if (sscanf(buf, "%d", &value) != 1) {
         hwlog_err("%s: write regs failed, invalid input!\n", __func__);
         return -EINVAL;
    }

    switch (value) {
        case TYPEC_HOST_CURRENT_DEFAULT:
            di->ops->ctrl_output_current(TYPEC_HOST_CURRENT_DEFAULT);
            break;
        case TYPEC_HOST_CURRENT_MID:
            di->ops->ctrl_output_current(TYPEC_HOST_CURRENT_MID);
            break;
        case TYPEC_HOST_CURRENT_HIGH:
            di->ops->ctrl_output_current(TYPEC_HOST_CURRENT_HIGH);
            break;
        default:
            hwlog_err("%s: wrong input action!\n", __func__);
            return -EINVAL;
    }

    return size;
}

/**
 * typec_port_mode_store() - create a device node to control port mode, which can be
 * used to choose host and slave alternatively.
 */
static ssize_t typec_port_mode_store(struct device *dev,
            struct device_attribute *attr, const char *buf, size_t size)
{
    int value;
    struct typec_device_info *di = g_typec_dev;

    if (NULL == di->ops || NULL == di->ops->ctrl_port_mode) {
        hwlog_err("%s: NULL pointer!!!\n", __func__);
        return -ENOMEM;
    }

    if (sscanf(buf, "%d", &value) != 1) {
         hwlog_err("%s: write regs failed, invalid input!\n", __func__);
         return -EINVAL;
    }

    switch (value) {
        case TYPEC_HOST_PORT_MODE_DFP:
            di->ops->ctrl_port_mode(TYPEC_HOST_PORT_MODE_DFP);
            break;
        case TYPEC_HOST_PORT_MODE_UFP:
            di->ops->ctrl_port_mode(TYPEC_HOST_PORT_MODE_UFP);
            break;
        case TYPEC_HOST_PORT_MODE_DRP:
            di->ops->ctrl_port_mode(TYPEC_HOST_PORT_MODE_DRP);
            break;
        default:
            hwlog_err("%s: wrong input action!\n", __func__);
            return -EINVAL;
    }

    return size;
}

/*
 * typec_cc_orientation_show() - create a device node for userspace to check whether cc1 or cc2 has been detected.
 */
static ssize_t typec_cc_orientation_show(struct device *dev, struct device_attribute *attr,
                char *buf)
{
    return scnprintf(buf, PAGE_SIZE, "%d\n", typec_detect_cc_orientation());
}

static DEVICE_ATTR(ctrl_output_current, S_IWUSR, NULL, typec_output_current_store);
static DEVICE_ATTR(ctrl_port_mode, S_IWUSR, NULL, typec_port_mode_store);
static DEVICE_ATTR(cc_orientation, S_IRUGO, typec_cc_orientation_show, NULL);

static struct attribute *typec_ctrl_attributes[] = {
    &dev_attr_ctrl_output_current.attr,
    &dev_attr_ctrl_port_mode.attr,
    &dev_attr_cc_orientation.attr,
    NULL,
};

static const struct attribute_group typec_attr_group = {
    .attrs = typec_ctrl_attributes,
};

/**
 * hw_typec_get_class() - create a class for both core layer and chip layers.
 */
struct class *hw_typec_get_class(void)
{
    if (NULL == typec_class) {
        typec_class = class_create(THIS_MODULE, "hw_typec");
        if (NULL == typec_class) {
            hwlog_err("%s: typec_class create error\n", __func__);
            return NULL;
        }
    }

    return typec_class;
}
EXPORT_SYMBOL_GPL(hw_typec_get_class);

#ifdef CONFIG_DUAL_ROLE_USB_INTF
static enum dual_role_property fusb_drp_properties[] = {
	DUAL_ROLE_PROP_MODE,
	DUAL_ROLE_PROP_PR,
	DUAL_ROLE_PROP_DR,
};

 /* Callback for "cat /sys/class/dual_role_usb/otg_default/<property>" */
static int dual_role_get_local_prop(struct dual_role_phy_instance *dual_role,
				    enum dual_role_property prop,
				    unsigned int *val)
{
    struct typec_device_info *di = dual_role_get_drvdata(dual_role);
    int port_mode;

    if (!di)
        return -EINVAL;

    port_mode = typec_detect_port_mode();

    if (port_mode == TYPEC_DEV_PORT_MODE_DFP) {
        if (prop == DUAL_ROLE_PROP_MODE)
            *val = DUAL_ROLE_PROP_MODE_DFP;
        else if (prop == DUAL_ROLE_PROP_PR)
            *val = DUAL_ROLE_PROP_PR_SRC;
        else if (prop == DUAL_ROLE_PROP_DR)
            *val = DUAL_ROLE_PROP_DR_HOST;
        else
            return -EINVAL;
    } else if (port_mode == TYPEC_DEV_PORT_MODE_UFP) {
        if (prop == DUAL_ROLE_PROP_MODE)
            *val = DUAL_ROLE_PROP_MODE_UFP;
        else if (prop == DUAL_ROLE_PROP_PR)
            *val = DUAL_ROLE_PROP_PR_SNK;
        else if (prop == DUAL_ROLE_PROP_DR)
            *val = DUAL_ROLE_PROP_DR_DEVICE;
        else
            return -EINVAL;
     } else {
        if (prop == DUAL_ROLE_PROP_MODE)
            *val = DUAL_ROLE_PROP_MODE_NONE;
        else if (prop == DUAL_ROLE_PROP_PR)
            *val = DUAL_ROLE_PROP_PR_NONE;
        else if (prop == DUAL_ROLE_PROP_DR)
            *val = DUAL_ROLE_PROP_DR_NONE;
        else
            return -EINVAL;
    }

    return 0;
}

/* Decides whether userspace can change a specific property */
static int dual_role_is_writeable(struct dual_role_phy_instance *drp,
				  enum dual_role_property prop)
{
    if (prop == DUAL_ROLE_PROP_MODE)
        return 1;
    else
        return 0;
}

/* 1. Check to see if current attached_state is same as requested state
 * if yes, then, return.
 * 2. Disonect current session
 * 3. Set approrpriate mode (dfp or ufp)
 * 4. wait for 1.5 secs to see if we get into the corresponding target state
 * if yes, return
 * 5. if not, fallback to Try.SNK
 * 6. wait for 1.5 secs to see if we get into one of the attached states
 * 7. return -EIO
 * Also we have to fallback to Try.SNK state machine on cable disconnect
 */
static int dual_role_set_mode_prop(struct dual_role_phy_instance *dual_role,
				   enum dual_role_property prop,
				   const unsigned int *val)
{
    struct typec_device_info *di = dual_role_get_drvdata(dual_role);
    int port_mode;
    int timeout = 0;
    int ret = 0;

    if (!di)
        return -EINVAL;

    if (*val != DUAL_ROLE_PROP_MODE_DFP && *val != DUAL_ROLE_PROP_MODE_UFP)
        return -EINVAL;

    port_mode = typec_detect_port_mode();

    if (port_mode != TYPEC_DEV_PORT_MODE_DFP
            && port_mode != TYPEC_DEV_PORT_MODE_UFP)
        return 0;

    if (port_mode == TYPEC_DEV_PORT_MODE_DFP
            && *val == DUAL_ROLE_PROP_MODE_DFP)
        return 0;

    if (port_mode == TYPEC_DEV_PORT_MODE_UFP
            && *val == DUAL_ROLE_PROP_MODE_UFP)
        return 0;

    hwlog_err("%s: start\n", __func__);

    mutex_lock(&di->typec_lock);

    /* AS DFP now, try reversing, form Source to Sink */
    if (port_mode == TYPEC_DEV_PORT_MODE_DFP) {

        hwlog_err("%s: try reversing, form Source to Sink\n", __func__);

        disable_irq(di->irq_intb);

        di->reverse_state = REVERSE_ATTEMPT;
        di->sink_attached = 0;

        /* turns off VBUS first */
        typec_close_otg();

        di->ops->ctrl_port_mode(TYPEC_HOST_PORT_MODE_UFP);

        enable_irq(di->irq_intb);

	/* AS UFP now, try reversing, form Sink to Source */
    } else if (port_mode == TYPEC_DEV_PORT_MODE_UFP) {

        hwlog_err("%s: try reversing, form Sink to Source\n", __func__);

        /* reverse to DFP, from Sink to Source  */
        disable_irq(di->irq_intb);

        di->reverse_state = REVERSE_ATTEMPT;
        /* set current advertisement to default */
        di->ops->ctrl_output_current(TYPEC_HOST_CURRENT_DEFAULT);

        di->ops->ctrl_port_mode(TYPEC_HOST_PORT_MODE_DFP);

        enable_irq(di->irq_intb);
    }

    mutex_unlock(&di->typec_lock);

    INIT_COMPLETION(di->reverse_completion);
    timeout =
        wait_for_completion_timeout(&di->reverse_completion,
                msecs_to_jiffies(DUAL_ROLE_SET_MODE_WAIT_MS));
    if (!timeout) {
        hwlog_err("%s: reverse failed, set mode to DRP\n", __func__);

        disable_irq(di->irq_intb);

        /* set mode to DRP */
        di->ops->ctrl_port_mode(TYPEC_HOST_PORT_MODE_DRP);
        di->reverse_state = 0;

        enable_irq(di->irq_intb);

        hwlog_err("%s: wait for the attached state\n", __func__);
        INIT_COMPLETION(di->reverse_completion);
        wait_for_completion_timeout(&di->reverse_completion,
                msecs_to_jiffies(DUAL_ROLE_SET_MODE_WAIT_MS));

        ret = -EIO;
    }

    hwlog_err("%s: end ret = %d\n", __func__, ret);

    return ret;
}

/* Callback for "echo <value> >
 *                      /sys/class/dual_role_usb/<name>/<property>"
 * Block until the entire final state is reached.
 * Blocking is one of the better ways to signal when the operation
 * is done.
 * This function tries to switch to Attached.SRC or Attached.SNK
 * by forcing the mode into SRC or SNK.
 * On failure, we fall back to Try.SNK state machine.
 */
static int dual_role_set_prop(struct dual_role_phy_instance *dual_role,
			      enum dual_role_property prop,
			      const unsigned int *val)
{
    if (prop == DUAL_ROLE_PROP_MODE)
        return dual_role_set_mode_prop(dual_role, prop, val);
    else
        return -EINVAL;
}

static void typec_wdog_work(struct work_struct *w)
{
    struct typec_device_info *di = container_of(w, struct typec_device_info, g_wdog_work.work);

    hwlog_info("%s: start\n", __func__);

    di->ops->ctrl_port_mode(TYPEC_HOST_PORT_MODE_DRP);

    /* to notify userspace that the state might have changed */
    if (di->dual_role) {
        dual_role_instance_changed(di->dual_role);
    }
    hwlog_info("%s: end\n", __func__);
}
#endif

static void typec_attach(struct typec_device_info *di)
{
    int port_mode, input_current, cc_orient;
    port_mode = typec_detect_port_mode();

    /* Type-C attached as DFP */
    if (TYPEC_DEV_PORT_MODE_DFP == port_mode) {

        if(di->typec_trigger_otg) {
#ifdef CONFIG_DUAL_ROLE_USB_INTF
            hwlog_info("%s: attached as DFP/Source\n", __func__);
            if (REVERSE_ATTEMPT == di->reverse_state) {

                hwlog_info("%s: reversed success, Sink detected\n", __func__);

                di->reverse_state = REVERSE_COMPLETE;
                di->sink_attached = 1;

                /* turn on VBUS */
                typec_open_otg();

                /* notify the attached state */
                complete(&di->reverse_completion);
            } else if (di->trysnk_attempt) {
                hwlog_info("%s: TrySNK fail, Sink detected again\n", __func__);

                /* TryNK has been attempted, clear the flag */
                di->trysnk_attempt = 0;

                /* turn on VBUS */
                di->sink_attached = 1;
                typec_open_otg();

                /* notify the attached state */
                complete(&di->reverse_completion);
            } else {
                hwlog_info("%s: Sink detected, perform TrySNK\n", __func__);
                di->trysnk_attempt = 1;
                /* set current advertisement to default */
                di->ops->ctrl_output_current(TYPEC_HOST_CURRENT_DEFAULT);
                di->ops->ctrl_port_mode(TYPEC_HOST_PORT_MODE_UFP);
                schedule_delayed_work(&di->g_wdog_work, msecs_to_jiffies(TRYSNK_TIMEOUT_MS));
            }
#else
            hwlog_info("%s: UFP OTG detected\n", __func__);
            di->sink_attached = true;
            typec_open_otg();
#endif
        }
    /* Type-C attached as UFP */
    } else if (TYPEC_DEV_PORT_MODE_UFP == port_mode) {

#ifdef CONFIG_DUAL_ROLE_USB_INTF
        hwlog_info("%s: attached as UFP/Sink\n", __func__);
        /*
         * exception handling:
         * if CC pin is not stable, the state transition may from
         * AS DFP to AS UFP direct, VBUS should be turned off first
         */
        if (di->sink_attached) {
            hwlog_info("%s: remove Sink first\n", __func__);
            typec_close_otg();
            di->reverse_state = 0;
            di->trysnk_attempt = 0;
            di->sink_attached = 0;
        }

        if (REVERSE_ATTEMPT == di->reverse_state) {
            hwlog_info("%s: reversed success, Source and VBUS detected\n",__func__);
            di->reverse_state = REVERSE_COMPLETE;
        }

        if (di->trysnk_attempt) {
            hwlog_info("%s: TrySNK success, Source and VBUS detected\n",__func__);
            di->trysnk_attempt = 0;
            /* cancel watch dog work */
            cancel_delayed_work(&di->g_wdog_work);
        }

        /* notify the attached state */
        complete(&di->reverse_completion);
#else
        hwlog_info("%s: DFP HOST detected\n", __func__);
#endif
        input_current = typec_current_mode_detect();
        if (TYPEC_DEV_CURRENT_HIGH == input_current) {
            hwlog_info("%s: detected type c current is 3A\n", __func__);
        } else if (TYPEC_DEV_CURRENT_MID == input_current) {
            hwlog_info("%s: detected type c current is 1.5A\n", __func__);
        } else if (TYPEC_DEV_CURRENT_DEFAULT == input_current) {
            hwlog_info("%s: detected type c current is default\n", __func__);
        } else {
            hwlog_err("%s: cannot detect a correct input current\n", __func__);
        }

    } else {
        hwlog_err("%s: cannot detect a correct port mode\n", __func__);
    }

    cc_orient = typec_detect_cc_orientation();
    if (TYPEC_ORIENT_CC1 == cc_orient) {
        hwlog_info("%s: CC1 detected\n", __func__);
    } else if (TYPEC_ORIENT_CC2 == cc_orient) {
        hwlog_info("%s: CC2 detected\n", __func__);
    } else {
        hwlog_err("%s: cannot detect a cc orientation\n", __func__);
    }

}

static void typec_detach(struct typec_device_info *di)
{
    hwlog_info("%s: typec detach\n", __func__);
#ifdef CONFIG_DUAL_ROLE_USB_INTF
    /* set current advertisement to high when detach*/
    di->ops->ctrl_output_current(TYPEC_HOST_CURRENT_HIGH);
    /* turn off VBUS when unattached */
    if (di->sink_attached) {
        hwlog_info("%s: Sink removed\n", __func__);
        typec_close_otg();
    }

    /* clear flags and make sure set the port mode back to DRP when unattached */
    di->reverse_state = 0;
    di->trysnk_attempt = 0;
    di->sink_attached = 0;
    di->ops->ctrl_port_mode(TYPEC_HOST_PORT_MODE_DRP);
#else
    if (di->sink_attached) {
        hwlog_info("%s: UFP OTG detach\n", __func__);
        di->sink_attached = false;
        typec_close_otg();
    }
#endif
}

/**
 * typec_intb_work() - handle the public interrupt work which is triggered by interrupts from type-c chips.
 */
void typec_intb_work(struct work_struct *work)
{
    int attach_status;
    struct typec_device_info *di = container_of(work, struct typec_device_info, g_intb_work);

    mutex_lock(&di->typec_lock);

    attach_status = typec_detect_attachment_status();

    if (TYPEC_ATTACH == attach_status) {
        hwlog_info("%s: typec attach\n", __func__);
        typec_attach(di);
    } else if (TYPEC_DETACH == attach_status) {
        hwlog_info("%s: typec detach\n", __func__);
        typec_detach(di);
    } else if (TYPEC_CUR_CHANGE_FOR_FSC == attach_status) {
        hwlog_info("%s: cc current change interrupt\n", __func__);
    } else if (TYPEC_ACC_MODE_CHANGE == attach_status) {
        hwlog_info("%s: accessory mode change interrupt\n", __func__);
    } else {
        hwlog_err("%s: cannot detect a correct attachment status\n", __func__);
    }

    mutex_unlock(&di->typec_lock);

#ifdef CONFIG_DUAL_ROLE_USB_INTF
    /* to notify userspace that the state might have changed */
    if (di->dual_role)
        dual_role_instance_changed(di->dual_role);
#endif

    typec_clean_int_mask();
}

/**
 * typec_chip_register() - register ops pointer for chip layer.
 * So the external modules can operate chips directly from core layer.
 * Return value is a struct pointer to deliver interrupt message.
 */
struct typec_device_info *typec_chip_register(struct typec_device_info *device_info,
            struct typec_device_ops *ops, struct module *owner)
{
    int ret = 0;
    struct typec_device_info *di = g_typec_dev;

#ifdef CONFIG_DUAL_ROLE_USB_INTF
    struct dual_role_phy_desc *desc;
    struct dual_role_phy_instance *dual_role;

    if(!ops || !ops->clean_int_mask || !ops->detect_attachment_status
    || !ops->detect_cc_orientation || !ops->detect_input_current
    || !ops->detect_port_mode || !ops->ctrl_output_current
    || !ops->ctrl_port_mode) {
        hwlog_err("%s: ops is NULL\n", __func__);
        return NULL;
    }
#endif

    di->ops = ops;
    di->owner = owner;
    di->typec_trigger_otg = device_info->typec_trigger_otg;

    mutex_init(&di->typec_lock);
    INIT_WORK(&di->g_intb_work, typec_intb_work);

#ifdef CONFIG_DUAL_ROLE_USB_INTF
    INIT_DELAYED_WORK(&di->g_wdog_work, typec_wdog_work);
    init_completion(&di->reverse_completion);

    desc =
        devm_kzalloc(device_info->dev,
            sizeof(struct dual_role_phy_desc), GFP_KERNEL);
    if (!desc) {
        hwlog_err("unable to allocate dual role descriptor\n");
        return NULL;
    }

    desc->name = "otg_default";
    desc->supported_modes = DUAL_ROLE_SUPPORTED_MODES_DFP_AND_UFP;
    desc->get_property = dual_role_get_local_prop;
    desc->set_property = dual_role_set_prop;
    desc->properties = fusb_drp_properties;
    desc->num_properties = ARRAY_SIZE(fusb_drp_properties);
    desc->property_is_writeable = dual_role_is_writeable;
    dual_role =
        devm_dual_role_instance_register(device_info->dev, desc);
    dual_role->drv_data = di;
    di->dual_role = dual_role;
    di->desc = desc;
#endif

    //only after the register, can the device nodes be created.
    if (typec_class) {
        typec_dev = device_create(typec_class, NULL, 0, NULL, "typec");
        ret = sysfs_create_group(&typec_dev->kobj, &typec_attr_group);
        if (ret) {
            hwlog_err("%s: typec sysfs group create error\n", __func__);
            goto typec_create_sysfs_fail;
        }
    }

    return di;

typec_create_sysfs_fail:
    sysfs_remove_group(&typec_dev->kobj, &typec_attr_group);
    return NULL;
}
EXPORT_SYMBOL_GPL(typec_chip_register);

static int __init typec_init(void)
{
    struct typec_device_info *di;

    di = kzalloc(sizeof(*di), GFP_KERNEL);
    if (!di) {
        hwlog_err("%s: alloc di failed\n", __func__);
        return -ENOMEM;
    }

    g_typec_dev = di;

    typec_class = class_create(THIS_MODULE, "hw_typec");
    if (IS_ERR(typec_class)) {
        hwlog_err("%s: cannot create class\n", __func__);
        return PTR_ERR(typec_class);
    }

    return 0;
}

static void __exit typec_exit(void)
{
    class_destroy(typec_class);
    sysfs_remove_group(&typec_dev->kobj, &typec_attr_group);
}

subsys_initcall(typec_init);
module_exit(typec_exit);
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("huawei typec core");
MODULE_AUTHOR("WangJing<wangjing6@huawei.com>");
