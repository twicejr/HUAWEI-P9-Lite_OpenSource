/*
 * hisi_boost5v_control.c - control boost5v driver
 *
 * Copyright (C) 2012 huawei Ltd.
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License. See the file "COPYING" in the main directory of this
 * archive for more details.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <linux/module.h>
#include <linux/string.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/err.h>
#include <linux/of_irq.h>
#include <linux/of_gpio.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include "hisi_boost5v_control.h"
#include <linux/mutex.h>

struct hisi_boost5v_control_info {
	struct resource *res;
	void __iomem *pmic_reg;
	struct mutex boost5v_control_lock;
	bool flash_led_flag;
	bool headphone_flag;
	bool classd_flag;
	bool hdmi_flag;
	bool denoise_headphone_flag;
};

static struct hisi_boost5v_control_info *g_boost5v_info = NULL;
static int regulator_changed(void);

static void hisi_boost5v_regu_write(unsigned int val, unsigned int reg)
{
	return writel(val, g_boost5v_info->pmic_reg + (reg << 2));
}

static void set_boost5v_voltage_5_v(void)
{
	hisi_boost5v_regu_write(HI6421_BOOST_CTRL2_VALUE1, HI6421_BOOST_CTRL2);
	hisi_boost5v_regu_write(HI6421_BOOST_CTRL3_VALUE1, HI6421_BOOST_CTRL3);
	hisi_boost5v_regu_write(HI6421_BOOST_CTRL4_VALUE1, HI6421_BOOST_CTRL4);
	hisi_boost5v_regu_write(HI6421_BOOST_CTRL5_VALUE1, HI6421_BOOST_CTRL5);
	hisi_boost5v_regu_write(HI6421_BOOST_CTRL6_VALUE1, HI6421_BOOST_CTRL6);
	hisi_boost5v_regu_write(HI6421_BOOST_CTRL7_VALUE1, HI6421_BOOST_CTRL7);
	hisi_boost5v_regu_write(HI6421_BOOST_CTRL8_VALUE1, HI6421_BOOST_CTRL8);

	hisi_boost5v_regu_write(BOOST5V_VALUE_5_V, HI6421_BOOST5V_VOLTAGE_ADDR);
	hisi_boost5v_regu_write(HI6421_BOOST_CTRL10_VALUE1, HI6421_BOOST_CTRL10);
	hisi_boost5v_regu_write(HI6421_BOOST_CTRL11_VALUE1, HI6421_BOOST_CTRL11);
	hisi_boost5v_regu_write(HI6421_BOOST_CTRL14_VALUE1, HI6421_BOOST_CTRL14);

	return;
}

static void set_boost5v_voltage_5_3_v(void)
{
	hisi_boost5v_regu_write(HI6421_BOOST_CTRL2_VALUE1, HI6421_BOOST_CTRL2);
	hisi_boost5v_regu_write(HI6421_BOOST_CTRL3_VALUE2, HI6421_BOOST_CTRL3);
	hisi_boost5v_regu_write(HI6421_BOOST_CTRL4_VALUE2, HI6421_BOOST_CTRL4);
	hisi_boost5v_regu_write(HI6421_BOOST_CTRL5_VALUE2, HI6421_BOOST_CTRL5);
	hisi_boost5v_regu_write(HI6421_BOOST_CTRL6_VALUE2, HI6421_BOOST_CTRL6);
	hisi_boost5v_regu_write(HI6421_BOOST_CTRL7_VALUE2, HI6421_BOOST_CTRL7);
	hisi_boost5v_regu_write(HI6421_BOOST_CTRL8_VALUE2, HI6421_BOOST_CTRL8);

	hisi_boost5v_regu_write(BOOST5V_VALUE_5_3_V, HI6421_BOOST5V_VOLTAGE_ADDR);
	hisi_boost5v_regu_write(HI6421_BOOST_CTRL10_VALUE2, HI6421_BOOST_CTRL10);
	hisi_boost5v_regu_write(HI6421_BOOST_CTRL11_VALUE2, HI6421_BOOST_CTRL11);
	hisi_boost5v_regu_write(HI6421_BOOST_CTRL14_VALUE2, HI6421_BOOST_CTRL14);

	return;
}

static inline void set_boost5v_enable(void)
{
	hisi_boost5v_regu_write(HI6421_BOOST5V_STATE_ENABLE, HI6421_BOOST5V_CONTROL_ADDR);
}

static inline void set_boost5v_disable(void)
{
	hisi_boost5v_regu_write(HI6421_BOOST5V_STATE_DISABLE, HI6421_BOOST5V_CONTROL_ADDR);
}

void boost5v_flash_led_enable(bool enable)
{
	if (NULL == g_boost5v_info)
	{
		return;
	}
	if (true == enable)
		g_boost5v_info->flash_led_flag = true;
	else
		g_boost5v_info->flash_led_flag = false;
	regulator_changed();
	return ;
}

void boost5v_headphone_enable(bool enable)
{
	if (NULL == g_boost5v_info)
	{
		return;
	}
	if (true == enable)
		g_boost5v_info->headphone_flag = true;
	else
		g_boost5v_info->headphone_flag = false;

	regulator_changed();
	return ;
}

void boost5v_classd_enable(bool enable)
{
	if (NULL == g_boost5v_info)
	{
		return;
	}
	if (true == enable)
		g_boost5v_info->classd_flag = true;
	else
		g_boost5v_info->classd_flag = false;

	regulator_changed();
	return ;
}

void boost5v_hdmi_enable(bool enable)
{
	if (NULL == g_boost5v_info)
	{
		return;
	}
	if (true == enable)
		g_boost5v_info->hdmi_flag = true;
	else
		g_boost5v_info->hdmi_flag = false;

	regulator_changed();
	return ;
}

void boost5v_denoise_headphone_enable(bool enable)
{
	if (NULL == g_boost5v_info)
	{
		return;
	}
	if (true == enable)
		g_boost5v_info->denoise_headphone_flag = true;
	else
		g_boost5v_info->denoise_headphone_flag = false;

	regulator_changed();
	return ;
}

static int regulator_changed(void)
{
	mutex_lock(&g_boost5v_info->boost5v_control_lock);
	if (g_boost5v_info->flash_led_flag || g_boost5v_info->classd_flag || g_boost5v_info->hdmi_flag) {
		set_boost5v_voltage_5_v();
		set_boost5v_enable();
		mdelay(3);
	} else if (g_boost5v_info->denoise_headphone_flag || g_boost5v_info->headphone_flag) {
		mdelay(1);
		set_boost5v_voltage_5_3_v();
		set_boost5v_enable();
		mdelay(3);
		hisi_boost5v_regu_write(HI6421_BOOST_CTRL2_VALUE2, HI6421_BOOST_CTRL2);
	} else {
		mdelay(1);
		hisi_boost5v_regu_write(HI6421_BOOST_CTRL2_VALUE1, HI6421_BOOST_CTRL2);
		mdelay(2);
		set_boost5v_disable();
	}

	mutex_unlock(&g_boost5v_info->boost5v_control_lock);
	return 0;
}

static int hisi_boost5v_control_probe(struct platform_device *pdev)
{
	struct hisi_boost5v_control_info *info;
	struct device *dev = NULL;

	if (pdev == NULL) {
		pr_err("[%s]boost5v_control get  platform device para is err!\n", __func__);
		return -EINVAL;
	}

	dev = &pdev->dev;

	info = devm_kzalloc(&pdev->dev, sizeof(*info), GFP_KERNEL);
	if (!info) {
		dev_err(&pdev->dev, "failed to allocate memory\n");
		return -ENOMEM;
	}
	/* get resources */
	info->res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!info->res) {
		dev_err(dev, "platform_get_resource err\n");
		return -ENOENT;
	}

	info->pmic_reg = devm_ioremap(dev, info->res->start,
				  resource_size(info->res));
	if (!info->pmic_reg) {
		dev_err(dev, "cannot map register memory\n");
		return -ENOMEM;
	}
	info->flash_led_flag = false;
	info->headphone_flag = false;
	info->classd_flag = false;
	info->hdmi_flag = false;
	info->denoise_headphone_flag = false;
	mutex_init(&(info->boost5v_control_lock));

	g_boost5v_info = info;
	platform_set_drvdata(pdev, info);

	return 0;
}

static int hisi_boost5v_control_remove(struct platform_device *pdev)
{
	struct hisi_boost5v_control_info *info;

	info = platform_get_drvdata(pdev);
	if (NULL == info) {
		pr_err("%s %d platform_get_drvdata NULL\n", __func__, __LINE__);
		return -1;
	}

	mutex_destroy(&info->boost5v_control_lock);

	return 0;
}

static struct of_device_id hisi_boost5v_control_of_match[] = {
	 { .compatible = "hisilicon,boost5v_control", },
	{ },
};
MODULE_DEVICE_TABLE(of, hisi_boost5v_control_of_match);

static struct platform_driver hisi_boost5v_control_driver = {
	.probe		= hisi_boost5v_control_probe,
	.remove		= hisi_boost5v_control_remove,
	.driver		= {
		.owner		= THIS_MODULE,
		.name		= "boost5v-control",
		.of_match_table	= hisi_boost5v_control_of_match,
	},
};

int __init hisi_boost5v_control_init(void)
{
	return platform_driver_register(&hisi_boost5v_control_driver);
}

static void __exit hisi_boost5v_control_exit(void)
{
	platform_driver_unregister(&hisi_boost5v_control_driver);
}

fs_initcall(hisi_boost5v_control_init);
module_exit(hisi_boost5v_control_exit);

MODULE_DESCRIPTION("Boost5v control driver");
MODULE_LICENSE("GPL v2");
