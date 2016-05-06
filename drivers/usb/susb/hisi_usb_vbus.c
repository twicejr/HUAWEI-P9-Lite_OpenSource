#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of_irq.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include <linux/huawei/usb/hisi_usb.h>
#include <huawei_platform/log/log_jank.h>

irqreturn_t charger_connect_interrupt(int irq, void *p)
{
	LOG_JANK_D(JLID_USBCHARGING_START, "JL_USBCHARGING_START");
	hisi_usb_otg_event(CHARGER_CONNECT_EVENT);
	return IRQ_HANDLED;
}

irqreturn_t charger_disconnect_interrupt(int irq, void *p)
{
	LOG_JANK_D(JLID_USBCHARGING_END, "JL_USBCHARGING_END");
	hisi_usb_otg_event(CHARGER_DISCONNECT_EVENT);
	return IRQ_HANDLED;
}

int vbus_connect_irq, vbus_disconnect_irq;

static int hisi_usb_vbus_probe(struct platform_device *pdev)
{
	int ret = 0;
	printk("[%s]+\n", __func__);

	vbus_connect_irq = platform_get_irq_byname(pdev, "connect");
	if (0 == vbus_connect_irq) {
		dev_err(&pdev->dev, "failed to get connect irq\n");
		return -ENOENT;
	}
	vbus_disconnect_irq = platform_get_irq_byname(pdev, "disconnect");
	if (0 == vbus_disconnect_irq) {
		dev_err(&pdev->dev, "failed to get disconnect irq\n");
		return -ENOENT;
	}

	pr_info("vbus_connect_irq: %d, vbus_disconnect_irq: %d\n",
			vbus_connect_irq, vbus_disconnect_irq);

	ret = request_irq(vbus_connect_irq, charger_connect_interrupt,
			  IRQF_NO_SUSPEND, "hiusb_in_interrupt", pdev);
	if (ret) {
		pr_err("request charger connect irq failed, irq: %d!\n",
			vbus_connect_irq);
		return ret;
	}

	ret = request_irq(vbus_disconnect_irq, charger_disconnect_interrupt,
			  IRQF_NO_SUSPEND, "hiusb_in_interrupt", pdev);
	if (ret) {
		free_irq(vbus_disconnect_irq, pdev);
		pr_err("request charger connect irq failed, irq: %d!\n",
			vbus_disconnect_irq);
	}
	printk("[%s]-\n", __func__);

	return ret;
}

static int hisi_usb_vbus_remove(struct platform_device *pdev)
{
	free_irq(vbus_connect_irq, pdev);
	free_irq(vbus_disconnect_irq, pdev);
	return 0;
}

static struct of_device_id hisi_usb_vbus_of_match[] = {
	{ .compatible = "hisilicon,usbvbus", },
	{ },
};

static struct platform_driver hisi_usb_vbus_drv = {
	.probe		= hisi_usb_vbus_probe,
	.remove		= hisi_usb_vbus_remove,
	.driver		= {
		.owner		= THIS_MODULE,
		.name		= "hisi_usb_vbus",
		.of_match_table	= hisi_usb_vbus_of_match,
	},
};
module_platform_driver(hisi_usb_vbus_drv);

MODULE_AUTHOR("l00196665");
MODULE_DESCRIPTION("This module detect USB VBUS connection/disconnection");
MODULE_LICENSE("GPL v2");
