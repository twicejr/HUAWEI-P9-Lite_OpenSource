/*
 * huawei Gadget Driver for Android
 *
 * Copyright (C) 2015 Huawei, Company.
 * Author: NA
 *
 * In order to ensure the production line to automatic gold cite port production
 * and increase the PC USB driver send customized production Switched 
 * Port instruction. 
 * At the bottom of the mobile phone USB driver, when receiving instructions 
 * from a port switching can automatically switch to the production of port. 
 * This file is the bottom of the USB drive received to the PC to a switching 
 * instruction, forwarded to the HAL layer and finally completed 
 * port switching function.
 *
 */
#include <linux/workqueue.h>
#include <linux/mutex.h>
#include <chipset_common/hwusb/hw_usb_rwswitch.h>
#include <linux/platform_device.h>


/* 0: no usb port switch request has been sent
 * 1: one usb port switch request has already been sent at least
 */
static int switch_request = 0;
static int port_mode = 0;
static bool switch_done = false;
static struct device *hw_usb_device = NULL;

/*========================================================================
FUNCTION       hw_usb_get_device

DESCRIPTION  : Get usb gadget device.

PARAM: struct device *dev:usb gadget device.
RETURN VALUE : void

DEPENDENCIES : NA
=========================================================================*/
void hw_usb_get_device(struct device *dev)
{
    hw_usb_device = dev;
}
EXPORT_SYMBOL(hw_usb_get_device);
static int usb_port_switch(int usb_switch)
{
	int ret = 0;
	char event_buf[32];
	char *envp[2] = {event_buf, NULL};

	snprintf(event_buf, sizeof(event_buf),"HW_USB_PORT_SWITCH=%d", usb_switch);
	if (hw_usb_device == NULL) {
		pr_info("%s: hw_usb_device is NULL\n", __func__);
		return ret;
	}
	if (&hw_usb_device->kobj == NULL) {
		pr_info("%s: &hw_usb_device->kobj is NULL\n", __func__);
		return ret;
	}
	ret= kobject_uevent_env(&hw_usb_device->kobj, KOBJ_CHANGE, envp);
	if (ret < 0) {
		pr_info("%s: uevent HW_USB_PORT_SWITCH=%d sending OK\n", __func__, usb_switch);
	} else {
		pr_err("%s: uevent HW_USB_PORT_SWITCH=%d sending failed %d\n", __func__, usb_switch, ret);
	}

	return ret;
}
static void usb_port_switch_wq(struct work_struct *data)
{
	usb_port_switch(switch_request);
}
DECLARE_WORK(usb_port_switch_work, usb_port_switch_wq);

/*========================================================================
FUNCTION       hw_usb_port_switch_request

DESCRIPTION  : submit usb switch request by sending uevent.

PARAM: int usb_switch_index:0x0E is factory port mode.

RETURN VALUE :return -1 is exception,other is normal.

DEPENDENCIES : NA
=========================================================================*/
int hw_usb_port_switch_request(int usb_switch_index)
{
	if (0 == usb_switch_index) {    //No switch
		pr_info("%s: uevent HW_USB_PORT_SWITCH=%d not send\n", __func__, usb_switch_index);
		return -1;
	}

	switch_request = usb_switch_index;

	if (in_interrupt())
		schedule_work(&usb_port_switch_work);
	else
		return usb_port_switch(switch_request);

	return 0;
}
EXPORT_SYMBOL(hw_usb_port_switch_request);

static ssize_t switch_request_show(struct device *pdev, struct device_attribute *attr,
			   char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%d\n", switch_done ? switch_request : 0);
}

static ssize_t switch_request_store(struct device *pdev, struct device_attribute *attr,
			    const char *buff, size_t size)
{
	char event_buf[32];
	char *envp[2] = {event_buf, NULL};

	snprintf(event_buf, sizeof(event_buf),"USB_PORT_SWITCH_DONE=%d", switch_request);
	if (hw_usb_device == NULL) {
		pr_info("%s: hw_usb_device is NULL\n", __func__);
		return 0;
	}
	if (&hw_usb_device->kobj == NULL) {
		pr_info("%s: &hw_usb_device->kobj is NULL\n", __func__);
		return 0;
	}

	kobject_uevent_env(&hw_usb_device->kobj, KOBJ_CHANGE, envp);

	switch_done = true;

	return size;
}

static ssize_t port_mode_show(struct device *pdev, struct device_attribute *attr,
			   char *buf)
{
    return snprintf(buf, PAGE_SIZE, "%d\n", port_mode);
}
static ssize_t port_mode_store(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t size)
{
	pr_info("%s: port_mode buf=\"%s\", size=%d\n", __func__, buf, (int)size);

	if (sscanf(buf, "%2d", &port_mode) == 1) {
		return strlen(buf);
	}

	return -1;
}
/*========================================================================
FUNCTION       hw_usb_port_mode_get

DESCRIPTION  : get usb port mode.

PARAM: void

RETURN VALUE :usb port mode index.

DEPENDENCIES : NA
=========================================================================*/
int hw_usb_port_mode_get(void)
{
	return port_mode;
}

static ssize_t switch_index_show(struct device *pdev, struct device_attribute *attr,
			   char *buf)
{
    return snprintf(buf, PAGE_SIZE, "%d\n", switch_request);
}
DEVICE_ATTR(switch_request, S_IRUGO | S_IWUSR, switch_request_show, switch_request_store);
DEVICE_ATTR(switch_index, S_IRUGO, switch_index_show, NULL);
DEVICE_ATTR(port_mode, 0660, port_mode_show, port_mode_store);

struct device_attribute *huawei_usb_attributes[] = {
    &dev_attr_switch_request,
    &dev_attr_port_mode,
    &dev_attr_switch_index,
    NULL
};
/*========================================================================
FUNCTION       hw_rwswitch_create_device

DESCRIPTION  : Initialize the data structure and Create a file read 
and write nodes.

PARAM: struct device *dev:usb gadget device.
struct class * usb_class:usb class.

RETURN VALUE :return 0 is normal,other is error.

DEPENDENCIES : NA
=========================================================================*/
int hw_rwswitch_create_device(struct device *dev,struct class * usb_class)
{
    struct device_attribute **attrs = huawei_usb_attributes;
    struct device_attribute *attr;
    int err;
    
    while ((attr = *attrs++)) {
        err = device_create_file(dev, attr);
        if (err) {
            device_destroy(usb_class, dev->devt);
            return err;
        }
    }
    return 0;
}
EXPORT_SYMBOL(hw_rwswitch_create_device);

