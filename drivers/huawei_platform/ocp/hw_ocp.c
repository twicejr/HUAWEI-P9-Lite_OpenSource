

#include <linux/module.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <huawei_platform/log/hw_log.h>
#include <linux/of.h>
#include <linux/slab.h>
#include <linux/mfd/hisi_pmic.h>
#if defined (CONFIG_HUAWEI_DSM)
#include <dsm/dsm_pub.h>
#endif
#include <huawei_platform/log/log_exception.h>
#include "hw_ocp.h"
#include <huawei_platform/ocp/hw_ocp_ext.h>

static struct hw_ocp_info g_ocp_info;
static struct hw_ocp_conf *g_ocp_conf = NULL;
static struct hw_ocp_attr g_ocp_attr[] = {
	{"ocp-lcd", hw_ocp_lcd_handler},
	{"ocp-tp", hw_ocp_tp_handler},
};

int hw_ocp_handler(char *name)
{
	int i = 0, ret = 0;
	char *device_name = NULL;
	struct hw_ocp_conf * p_ocp = NULL;

	if (!g_ocp_info.ocp_support) {
		ret = -1;
		HW_OCP_LOG_INFO("don't handler ocp power:%s.\n", name);
		return ret;
	}

	p_ocp = g_ocp_conf;
	for (i = 0;i < g_ocp_info.num; i++) {
		if (!strcmp(name, p_ocp->power_name) && p_ocp->power_support) {
			device_name = p_ocp->device_name;
			break;
		}
		p_ocp++;
	}

	if (i >= g_ocp_info.num) {
		ret = -1;
		HW_OCP_LOG_ERR("not found power:%s.\n", name);
		return ret;
	}

	for (i = 0;i < SIZEOF_ARRAY(g_ocp_attr);i++) {
		if (!strcmp(device_name, g_ocp_attr[i].name)) {
			ret = g_ocp_attr[i].handler(name);
			if (ret) {
				HW_OCP_LOG_ERR("ocp handler error.\n");
				ret = -1;
			}
			break;
		}
	}
	return ret;
}

int hw_ocp_tp_handler(const char *name)
{
	HW_OCP_LOG_INFO("--------TP process function-----%s-----\n", name);
	return 0;
}

int hw_ocp_lcd_handler(const char *name)
{
	static int ocp_count = 0;
	static unsigned long ocp_time_record = 0;
	static int is_first = 0;
	static int count_full_flag = 0;
	unsigned int lcd_is_recover = 0;

	if (!is_first) {
		ocp_time_record = jiffies;
		is_first = 1;
	} else {
		if (jiffies_to_msecs(jiffies - ocp_time_record) < LCD_OCP_TIME_MS) {
			if (ocp_count >= OCP_COUNT_MAX) {
				count_full_flag = 1;
			}
			ocp_count++;
		} else {
			if (!count_full_flag) {
				ocp_count = 0;
			}
		}
		ocp_time_record = jiffies;
	}

	if (ocp_count <= OCP_COUNT_MAX) {
		/*notify lcd recovery*/
		if ((ocp_count >= OCP_COUNT_MAX) ||(!strncmp(name, "ldo4", strlen(name)) && !g_ocp_info.lcd_single_ldo4)) {
			lcd_is_recover = 0;
		} else {
			lcd_is_recover = 1;
		}
		hw_ocp_notifier_call_chain(HW_OCP_LCD_EVENT, &lcd_is_recover);
	}
	HW_OCP_LOG_ERR("%s, %s ocp, ocp_count:%d.\n", __func__, name, ocp_count);
	return 0;
}

static int hw_ocp_parse_dts(struct device_node *np)
{
	int ret = 0;
	int i = 0;
	struct hw_ocp_conf * p_ocp = NULL;

	ret = of_property_read_u32(np, "huawei,ocp-num", &g_ocp_info.num);
	if (ret) {
		HW_OCP_LOG_ERR("g_ocp_info.num = 0.\n");
		return ret;
	}

	g_ocp_conf = (struct hw_ocp_conf *)kmalloc(sizeof(struct hw_ocp_conf) * g_ocp_info.num, GFP_KERNEL);
	memset(g_ocp_conf, 0, sizeof(struct hw_ocp_conf) * g_ocp_info.num);

	p_ocp = g_ocp_conf;
	for (i = 0;i < g_ocp_info.num;i++) {
		ret = of_property_read_string_index(np, "huawei,ocp-power-name", i, &p_ocp->power_name);
		if (ret != 0) {
			HW_OCP_LOG_ERR("parse power-name error.\n");
			return ret;
		}
		ret = of_property_read_string_index(np, "huawei,ocp-device-name", i, &p_ocp->device_name);
		if (ret != 0) {
			HW_OCP_LOG_ERR("parse device-name error.\n");
			return ret;
		}
		ret = of_property_read_u32_index(np, "huawei,ocp-power-support", i, &p_ocp->power_support);
		if (ret != 0) {
			HW_OCP_LOG_ERR("parse power-support error.\n");
			return ret;
		}
		p_ocp++;
	}
	/*parse lcd flag*/
	ret = of_property_read_u32(np, "huawei,lcd-single-ldo4", &g_ocp_info.lcd_single_ldo4);
	if (ret) {
		g_ocp_info.lcd_single_ldo4 = 0;
		HW_OCP_LOG_ERR("parse lcd ldo4 flag error.\n");
		return ret;
	}

	return ret;
}

static int hw_ocp_pmic_register(void)
{
	int ret = 0;
	ret = hisi_pmic_special_ocp_register(SUPPLY_LCD, hw_ocp_handler);
	if (ret) {
		HW_OCP_LOG_ERR("[%s]supply_lcd register error.\n");
		return ret;
	}
	ret = hisi_pmic_special_ocp_register(SUPPLY_TP, hw_ocp_handler);
	if (ret) {
		HW_OCP_LOG_ERR("[%s]supply_tp register error.\n");
		return ret;
	}
	return ret;
}

static int __init hw_ocp_init(void)
{
	struct device_node *np = NULL;
	int ret = -EIO;

	memset(&g_ocp_info, 0, sizeof(struct hw_ocp_info));
	np = of_find_compatible_node(NULL, NULL, DTS_COMP_OCP);
	if (!np) {
		g_ocp_info.ocp_support = 0;
		HW_OCP_LOG_INFO("NOT FOUND device node %s, not support ocp handle!\n", DTS_COMP_OCP);
		goto out;
	}

	ret = of_property_read_u32(np, "huawei,ocp-support", &g_ocp_info.ocp_support);
	if (ret) {
		g_ocp_info.ocp_support = 0;
		HW_OCP_LOG_INFO("not support ocp handle.\n");
		return ret;
	}

	ret = hw_ocp_parse_dts(np);
	if (ret) {
		g_ocp_info.ocp_support = 0;
		HW_OCP_LOG_INFO("Config ocp error, not support ocp handle!\n");
		goto out;
	}
	ret = hw_ocp_pmic_register();
	if (ret) {
		g_ocp_info.ocp_support = 0;
		HW_OCP_LOG_INFO("Register pmic handle error!\n");
		goto out;
	}

	g_ocp_info.lcd_nb.notifier_call= hisi_lcd_ocp_recover;
	hw_ocp_register_notifier(&g_ocp_info.lcd_nb);
out:

	HW_OCP_LOG_DEBUG("%s called, ret %d\n", __func__, ret);
	return ret;
}

static BLOCKING_NOTIFIER_HEAD(hw_ocp_init_notifier_list);
int hw_ocp_register_notifier(struct notifier_block* nb)
{
	return blocking_notifier_chain_register(&hw_ocp_init_notifier_list, nb);
}
EXPORT_SYMBOL_GPL(hw_ocp_register_notifier);
int hw_ocp_unregister_notifier(struct notifier_block* nb)
{
	return blocking_notifier_chain_unregister(&hw_ocp_init_notifier_list, nb);
}
EXPORT_SYMBOL_GPL(hw_ocp_unregister_notifier);
void hw_ocp_notifier_call_chain(unsigned long event, void* data)
{
	blocking_notifier_call_chain(&hw_ocp_init_notifier_list, event, data);
}
EXPORT_SYMBOL_GPL(hw_ocp_notifier_call_chain);
module_init(hw_ocp_init);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Ocp state monitor");
