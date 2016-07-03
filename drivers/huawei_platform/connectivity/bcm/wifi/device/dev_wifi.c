/*
 * Copyright (c) 2012-2013 Huawei Ltd.
 *
 * Author: 
 *
 * This	program	is free	software; you can redistribute it and/or modify
 * it under	the	terms of the GNU General Public	License	version	2 as
 * published by	the	Free Software Foundation.
 */

/* dev_wifi.c
 */

/*=========================================================================
 *
 * histoty
 *
 *=========================================================================
 */
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/mmc/host.h>
#include <linux/mmc/sdio_ids.h>
#include <linux/err.h>
#include <linux/random.h>
#include <linux/skbuff.h>
#include <linux/wifi_tiwlan.h>
#include <linux/gpio.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/of.h>
#include <linux/of_platform.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/pinctrl/consumer.h>
#include <linux/regulator/consumer.h>
#include <linux/ctype.h>
#include <linux/export.h>
#include <linux/mmc/dw_mmc.h>
#ifdef CONFIG_HWCONNECTIVITY
#include <linux/huawei/hw_connectivity.h>
#endif
#include <huawei_platform/log/hw_log.h>

#include "dev_wifi.h"

#define HW_FAC_GPIO_VAL_LOW     20700
#define HW_FAC_GPIO_VAL_HIG     20701

#define DTS_COMP_WIFI_POWER_NAME "hisilicon,bcm_wifi"
typedef struct wifi_mem_prealloc_struct {
	void *mem_ptr;
	unsigned long size;
} wifi_mem_prealloc_t;

#define HWLOG_TAG       dev_wifi

struct wifi_host_s *wifi_host;
static struct sk_buff *wlan_static_skb[WLAN_SKB_BUF_NUM];
unsigned char g_wifimac[WLAN_MAC_LEN] = {0x00,0x00,0x00,0x00,0x00,0x00};
static wifi_mem_prealloc_t wifi_mem_array[PREALLOC_WLAN_NUMBER_OF_SECTIONS] = {
	{ NULL, (WLAN_SECTION_SIZE_0 + PREALLOC_WLAN_SECTION_HEADER) },
	{ NULL, (WLAN_SECTION_SIZE_1 + PREALLOC_WLAN_SECTION_HEADER) },
	{ NULL, (WLAN_SECTION_SIZE_2 + PREALLOC_WLAN_SECTION_HEADER) },
	{ NULL, (WLAN_SECTION_SIZE_3 + PREALLOC_WLAN_SECTION_HEADER) }
};

HWLOG_REGIST();

/*kmalloc memory for wifi*/
void *wifi_mem_prealloc(int section, unsigned long size)
{
	if (section == PREALLOC_WLAN_NUMBER_OF_SECTIONS)
		return wlan_static_skb;
	if ((section < 0) || (section > PREALLOC_WLAN_NUMBER_OF_SECTIONS)) {
		hwlog_err("%s: is not prealloc(section:%d), use dynamic memory.\n", __func__, section);
		return NULL;
	}
	if (wifi_mem_array[section].size < size) {
		hwlog_err("%s: section:%d prealloc is not enough(size:%lu), use dynamic memory.\n", __func__, section, size);
		return NULL;
	}
	return wifi_mem_array[section].mem_ptr;
}

/*init wifi buf*/
int init_wifi_mem(void)
{
	int i = 0;

	hwlog_info("init_wifi_mem.\n");
	for (i = 0; i < WLAN_SKB_BUF_NUM; i++) {
		if (i < (WLAN_SKB_BUF_NUM / 2))
			wlan_static_skb[i] = dev_alloc_skb(WLAN_SKB_BUF_MIN);
		else
			wlan_static_skb[i] = dev_alloc_skb(WLAN_SKB_BUF_MAX);
		if (wlan_static_skb[i] == NULL) {
			hwlog_err("%s: dev_alloc_skb is error(%d).\n", __func__, i);
			return -ENOMEM;
		}
	}

	for	(i = 0; i < PREALLOC_WLAN_NUMBER_OF_SECTIONS; i++) {
		wifi_mem_array[i].mem_ptr = kzalloc(wifi_mem_array[i].size,
			GFP_KERNEL);
		if (wifi_mem_array[i].mem_ptr == NULL) {
			hwlog_err("%s: alloc mem_ptr is error(%d).\n", __func__, i);
			return -ENOMEM;
		}
	}
	return 0;
}

/*deinit wifi buf*/
int deinit_wifi_mem(void)
{
	int i = 0;

	hwlog_info("deinit_wifi_mem.\n");
	for (i = 0; i < WLAN_SKB_BUF_NUM; i++) {
		if (wlan_static_skb[i] != NULL) {
			dev_kfree_skb(wlan_static_skb[i]);
			wlan_static_skb[i] = NULL;
		} else
			break;
	}
	for	(i = 0;	i < PREALLOC_WLAN_NUMBER_OF_SECTIONS; i++) {
		if (wifi_mem_array[i].mem_ptr != NULL) {
			kfree(wifi_mem_array[i].mem_ptr);
			wifi_mem_array[i].mem_ptr = NULL;
		} else
			break;
	}
	return 0;
}

static void read_from_global_buf(unsigned char * buf)
{
	memcpy(buf,g_wifimac,WLAN_MAC_LEN);
	hwlog_info("get MAC from g_wifimac: mac=%02x:%02x:**:**:%02x:%02x\n",buf[0],buf[1],buf[4],buf[5]);
	return;
}

static int char2_byte( char* strori, char* outbuf )
{
	int i = 0;
	int temp = 0;
	int sum = 0;
	char *ptemp;
	char tempchar[20]={0};

	ptemp = tempchar;

	for (i = 0; i< WLAN_VALID_SIZE;i++){
		if(strori[i]!=':'){
			*ptemp = strori[i];
			 ptemp++;
		}
	}

	for( i = 0; i < NV_WLAN_VALID_SIZE; i++ ){

		switch (tempchar[i]) {
			case '0' ... '9':
				temp = tempchar[i] - '0';
				break;
			case 'a' ... 'f':
				temp = tempchar[i] - 'a' + 10;
				break;
			case 'A' ... 'F':
				temp = tempchar[i] - 'A' + 10;
				break;
			default:
				return 0;
		}
		sum += temp;
		if( i % 2 == 0 ){
			outbuf[i/2] |= temp << 4;
		}
		else{
			outbuf[i/2] |= temp;
		}
	}
	return sum;
}


static int read_from_mac_file(unsigned char * buf)
{
	struct file* filp = NULL;
	mm_segment_t old_fs;
	int result = 0;
	int sum = 0;
	char buf1[20] = {0};
	char buf2[6] = {0};

	if (NULL == buf) {
		hwlog_err("%s: buf is NULL\n", __func__);
		return -1;
	}

	filp = filp_open(MAC_ADDRESS_FILE, O_RDONLY,0);
	if(IS_ERR(filp)){
		hwlog_err("open mac address file error\n");
		return -1;
	}

	old_fs = get_fs();
	set_fs(KERNEL_DS);
	filp->f_pos = 0;
	result = filp->f_op->read(filp,buf1,WLAN_VALID_SIZE,&filp->f_pos);
	if(WLAN_VALID_SIZE != result){
		hwlog_err("read mac address file error\n");
		set_fs(old_fs);
		filp_close(filp,NULL);
		return -1;
	}

	sum = char2_byte(buf1,buf2);
	if (0 != sum){
		hwlog_err("get MAC from file: mac=%02x:%02x:**:**:%02x:%02x\n",buf2[0],buf2[1],buf2[4],buf2[5]);
		memcpy(buf,buf2,WLAN_MAC_LEN);
	}else{
		set_fs(old_fs);
		filp_close(filp,NULL);
		return -1;
	}

	set_fs(old_fs);
	filp_close(filp,NULL);
	return 0;
}

int bcm_wifi_get_mac_addr(unsigned char *buf)
{
	int ret = -1;

	if (NULL == buf) {
		hwlog_err("%s: k3v2_wifi_get_mac_addr failed\n", __func__);
		return -1;
	}

	memset(buf, 0, WLAN_MAC_LEN);
	if (0 != g_wifimac[0] || 0 != g_wifimac[1] || 0 != g_wifimac[2] || 0 != g_wifimac[3]|| 0 != g_wifimac[4] || 0 != g_wifimac[5]){
		read_from_global_buf(buf);
		return 0;
	}

	ret = read_from_mac_file(buf);
	if(0 == ret){
		hwlog_err("%s:read from mac addr file success \n",__func__);
		memcpy(g_wifimac,buf,WLAN_MAC_LEN);
		return 0;
	}else{
		get_random_bytes(buf,WLAN_MAC_LEN);
		buf[0] = 0x0;
		hwlog_err("get MAC from Random: mac=%02x:%02x:%02x:%02x:%02x:%02x\n",buf[0],buf[1],buf[2],buf[3],buf[4],buf[5]);
		memcpy(g_wifimac,buf,WLAN_MAC_LEN);
	}

	return 0;
}


int bcm_wifi_power(int on)
{
	int ret = 0;
	hwlog_info("%s: on:%d\n", __func__, on);
	if (wifi_host->chip_fpga) {
		if (NULL == wifi_host) {
			hwlog_err("%s: wifi_host is null\n", __func__);
			return -1;
		}
	}

	if (on) {

		if (wifi_host->bEnable) {
			hwlog_err("%s: wifi had power on.\n", __func__);
			return ret;
		}
#if defined(CONFIG_MMC_DW_HI6XXX) || defined(CONFIG_MMC_DW_HI3XXX)
                /* set LowerPower mode*/
                if (!(IS_ERR(wifi_host->pctrl)||IS_ERR(wifi_host->pins_idle))){
                        ret = pinctrl_select_state(wifi_host->pctrl, wifi_host->pins_idle);
                        if(ret)
                            hwlog_err("%s: set LOWPOWER mode failed, ret:%d\n", __func__, ret);
                }
#endif
	       #if 1
		ret = clk_prepare_enable(wifi_host->clk);

		if (ret < 0) {
		    hwlog_err("%s: clk_enable failed, ret:%d\n", __func__, ret);
		    return ret;
		}
	       #endif
           
		gpio_set_value(wifi_host->enable, 0);
		msleep(10);
		gpio_set_value(wifi_host->enable, 1);
		msleep(100);
#if defined(CONFIG_MMC_DW_HI6XXX) || defined(CONFIG_MMC_DW_HI3XXX)
                /* set Normal mode*/
                if (!(IS_ERR(wifi_host->pctrl)||IS_ERR(wifi_host->pins_normal))){
                    ret = pinctrl_select_state(wifi_host->pctrl, wifi_host->pins_normal);
                    if(ret)
                        hwlog_err("%s: set NORMAL mode failed, ret:%d\n", __func__, ret);
                }
#endif
		wifi_host->bEnable = true;
		//hi_sdio_set_power(on); 
	} else {
		//hi_sdio_set_power(on);
		//dump_stack();
#if defined(CONFIG_MMC_DW_HI6XXX) || defined(CONFIG_MMC_DW_HI3XXX)
		/* set LowerPower mode*/
		if (!(IS_ERR(wifi_host->pctrl)||IS_ERR(wifi_host->pins_idle))){
                    pinctrl_select_state(wifi_host->pctrl, wifi_host->pins_idle);
                    if(ret)
                        hwlog_err("%s: set LOWPOWER mode failed, ret:%d\n", __func__, ret);
                }

               msleep(10);
#endif
		gpio_set_value(wifi_host->enable, 0);
		msleep(10);
		#if 1
			clk_disable_unprepare(wifi_host->clk);
		#endif
			wifi_host->bEnable = false;

	}
	
	return ret;
}

static int bcm_wifi_reset(int on)
{
	hwlog_info("%s: on:%d.\n", __func__, on);
	if (on) {
		gpio_set_value(wifi_host->enable, 1);
	}
	else {
		gpio_set_value(wifi_host->enable, 0);
	}
	return 0;
}

static int bcm_wifi_get_nvram_path(char *val, int len)
{
    hwlog_info("%s: len:%d, val=%s.\n", __func__, len, val);
    if ( val == NULL || len <= 0 ) {
        hwlog_err("%s:val is null or len is invalid.\n", __func__);
        return -1;
    }

    strncpy(val, wifi_host->nvram_path, len);
    return 0;
}

extern void dw_mci_sdio_card_detect_change(void);

int hi_sdio_detectcard_to_core(int val)
{
    dw_mci_sdio_card_detect_change();
    hwlog_err("dw_mci_sdio_card_detect %d", val);

    return 0;
}
extern int dhd_msg_level;

static ssize_t show_wifi_debug_level(struct device *dev,
        struct device_attribute *attr, char *buf) {
    return sprintf(buf, "%d\n", dhd_msg_level);
}
static ssize_t restore_wifi_debug_level(struct device *dev, struct device_attribute *attr,
        const char *buf, size_t size) {
    int value;
    if (sscanf(buf, "%d\n", &value) == 1) {
#ifdef WL_CFG80211
        hwlog_err("restore_wifi_debug_level\n");
		/* Enable DHD and WL logs in oneshot */
		if (value & DHD_WL_VAL2)
			wl_cfg80211_enable_trace(TRUE, value & (~DHD_WL_VAL2));
		else if (value & DHD_WL_VAL)
			wl_cfg80211_enable_trace(FALSE, WL_DBG_DBG);
		if (!(value & DHD_WL_VAL2))
#endif /* WL_CFG80211 */
        dhd_msg_level = value;
        return size;
    }
    return -1;
}

extern int wl_get_wrong_action_flag(void);
extern int wl_trigger_disable_nmode(void);

static ssize_t show_wifi_wrong_action_flag(struct device *dev,
        struct device_attribute *attr, char *buf) {
    int has_wrong_action = wl_get_wrong_action_flag();
    hwlog_info("%s has wrong action %d\n", __func__, has_wrong_action);
    return sprintf(buf, "%d\n", has_wrong_action);
}

static ssize_t restore_wifi_arp_timeout(struct device *dev, struct device_attribute *attr,
        const char *buf, size_t size) {
    int value;
    if (sscanf(buf, "%d\n", &value) == 1) {
        if(value == 1) {
            hwlog_info("%s enter should invoke wrong action handler\n", __func__);
            wl_trigger_disable_nmode();
        }
        return size;
    }
    return -1;
}

static ssize_t restore_wifi_wrong_action_debug(struct device *dev, struct device_attribute *attr,
        const char *buf, size_t size) {
    int value;
    if (sscanf(buf, "%d\n", &value) == 1) {
        if(value == 1) {
            hwlog_info("%s enter should invoke wrong action handler\n", __func__);
            wl_trigger_disable_nmode();
        }
        return size;
    }
    return -1;
}

static DEVICE_ATTR(wifi_debug_level, S_IRUGO | S_IWUSR | S_IWGRP,
        show_wifi_debug_level, restore_wifi_debug_level);

static DEVICE_ATTR(wifi_wrong_action_flag, S_IRUGO,
        show_wifi_wrong_action_flag, NULL);

static DEVICE_ATTR(wifi_arp_timeout, S_IWUSR | S_IWGRP,
        NULL, restore_wifi_arp_timeout);

static DEVICE_ATTR(wifi_wrong_action_debug, S_IWUSR | S_IWGRP,
        NULL, restore_wifi_wrong_action_debug);

static struct attribute *attr_debug_attributes[] = {
    &dev_attr_wifi_debug_level.attr,
    NULL
};

static struct attribute *attr_arp_attributes[] = {
    &dev_attr_wifi_wrong_action_flag.attr,
    &dev_attr_wifi_arp_timeout.attr,
    &dev_attr_wifi_wrong_action_debug.attr,
    NULL
};

static const struct attribute_group attrgroup_debug_level = {
    .attrs = attr_debug_attributes,
};

static const struct attribute_group attrgroup_arp_timeout = {
	.attrs = attr_arp_attributes,
};

static int wifi_open_err_code = 0;
static ssize_t show_wifi_open_state(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", wifi_open_err_code);
}
static ssize_t restore_wifi_open_state(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t size)
{
	int value;
	if (sscanf(buf, "%d\n", &value) == 1) {
		wifi_open_err_code = value;
		return size;
	}
	return -1;
}

static ssize_t restore_wifi_factory_dbg(struct device *dev, struct device_attribute *attr,
        const char *buf, size_t size) {
    int value = 0;
    int ret = -1;
    if (NULL == wifi_host) {
        hwlog_err("restore_wifi_factory_dbg: wifi_host is null\n");
        return ret;
    }

    if (sscanf(buf, "%d\n", &value) == 1) {
        if (HW_FAC_GPIO_VAL_LOW == value) {
            ret = bcm_wifi_power(0);
        } else if (HW_FAC_GPIO_VAL_HIG == value) {
            ret = bcm_wifi_power(1);
        } else {
            hwlog_err("restore_wifi_factory_dbg: value: %d\n", value);
        }
    }
    return ((ret >= 0) ? size: -1);
}

void set_wifi_open_err_code(int err_num)
{
    wifi_open_err_code = err_num;
}

static DEVICE_ATTR(wifi_open_state, S_IRUGO | S_IWUSR,
				   show_wifi_open_state, restore_wifi_open_state);

static DEVICE_ATTR(wifi_factory_dbg, S_IWUSR,
        NULL, restore_wifi_factory_dbg);

static struct attribute *wifi_state_attributes[] = {
	&dev_attr_wifi_open_state.attr,
    &dev_attr_wifi_factory_dbg.attr,
	NULL
};
static const struct attribute_group wifi_state = {
	.attrs = wifi_state_attributes,
};

struct wifi_platform_data bcm_wifi_control = {
	.set_power = bcm_wifi_power,
	.set_reset = bcm_wifi_reset,
	.set_carddetect = hi_sdio_detectcard_to_core,
	.get_mac_addr = bcm_wifi_get_mac_addr,
	.mem_prealloc = wifi_mem_prealloc,
	.get_nvram_path = bcm_wifi_get_nvram_path,
};

static struct resource bcm_wifi_resources[] = {
	[0] = {
	.name  = "bcmdhd_wlan_irq",
	.flags = IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHLEVEL
			| IRQF_NO_SUSPEND,
	},
};

static struct platform_device bcm_wifi_device = {
	.name = "bcmdhd_wlan",
	.id = 1,
	.num_resources = ARRAY_SIZE(bcm_wifi_resources),
	.resource = bcm_wifi_resources,
	.dev = {
		.platform_data = &bcm_wifi_control,
	},
};


int  wifi_power_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct device_node *np;
	enum of_gpio_flags gpio_flags;
	const char *nvpath = NULL;
	bool ext_gpio_type = 0;

	np = of_find_compatible_node(NULL, NULL, DTS_COMP_WIFI_POWER_NAME);	// should be the same as dts node compatible property
	if (np == NULL) {
		hwlog_err("Unable to find wifi_power\n");
		return -ENOENT;
	}

	ret = init_wifi_mem();
	if (ret) {
		hwlog_err("%s: init_wifi_mem failed.\n", __func__);
		goto err_malloc_wifi_host;
	}
	
	wifi_host = kzalloc(sizeof(struct wifi_host_s), GFP_KERNEL);
	if (!wifi_host) {
		hwlog_err("%s: malloc wifi_host failed.\n", __func__);
		ret = -ENOMEM;
		goto err_malloc_wifi_host;
	}

	memset((void*)wifi_host, 0, sizeof(struct wifi_host_s));
	wifi_host->bEnable = false;

#if defined(CONFIG_BCM4343)
	wifi_host->clk = devm_clk_get(&pdev->dev, "CK32B");
#else
	wifi_host->clk = devm_clk_get(&pdev->dev, "clk_pmu32kb");
#endif
	if (IS_ERR(wifi_host->clk)) {
		dev_err(&pdev->dev, "Get wifi 32k clk failed\n");
		ret = -1;
		goto err_clk_get;
       }


#if 0
	wifi_host->vdd = regulator_get(&pdev->dev,"wifiio-vcc");
	if (IS_ERR(wifi_host->vdd)) {
	    dev_err(&pdev->dev, "regulator_get failed\n");
           ret = -1;
	    goto err_regulator_get; 
	}
#endif

#if defined(CONFIG_MMC_DW_HI6XXX) || defined(CONFIG_MMC_DW_HI3XXX)
	wifi_host->pctrl = devm_pinctrl_get(&pdev->dev);
	if (IS_ERR(wifi_host->pctrl))
	{
		hwlog_err("%s: iomux_lookup_block failed, and the value of wifi_host->pctrl is %lx\n", __func__,(unsigned long)wifi_host->pctrl);
		ret = -1;
		goto err_pinctrl_get;
	}

	wifi_host->pins_normal = pinctrl_lookup_state(wifi_host->pctrl, "default");
	if (IS_ERR(wifi_host->pins_normal))
	{
		hwlog_err("%s: pinctrl_lookup_state default failed, and the value of wifi_host->pins_normal is%lx\n", __func__,(unsigned long)wifi_host->pins_normal);
		ret = -1;
		goto err_pinctrl_get;
	}

	wifi_host->pins_idle = pinctrl_lookup_state(wifi_host->pctrl, "idle");
	if (IS_ERR(wifi_host->pins_idle))
	{
		hwlog_err("%s: pinctrl_lookup_state idle failed, and the value of wifi_host->pins_idle is %lx\n", __func__,(unsigned long)wifi_host->pins_idle);
		ret = -1;
		goto err_pinctrl_get;
	}

	ret = pinctrl_select_state(wifi_host->pctrl, wifi_host->pins_normal);
	if (ret <0) {
		hwlog_err("%s: pinctrl_select_state failed.\n", __func__);
		goto err_pinctrl_get;
	}
#endif

#if defined(CONFIG_BCM4343)
	wifi_host->enable = of_get_gpio_by_prop(np , "wlan-on,gpio-enable" , 0 , 0 , &gpio_flags);
	if (wifi_host->enable<0)
	{
		ret = -1;
		goto err_gpio_get;
	}

	wifi_host->wifi_wakeup_irq= of_get_gpio_by_prop(np , "wlan-irq,gpio-irq" , 0 , 0 , &gpio_flags);
	if (wifi_host->wifi_wakeup_irq<0)
	{
		ret = -1;
		goto err_gpio_get;
	}
#else
	wifi_host->enable = of_get_named_gpio(pdev->dev.of_node, "wlan-on,gpio-enable", 0);
	hwlog_err("%s: wifi_host->enable %d\n", __func__, wifi_host->enable);
	if (wifi_host->enable<0) {
		ret = -1;
		goto err_gpio_get;
	}

	wifi_host->wifi_wakeup_irq= of_get_named_gpio(pdev->dev.of_node, "wlan-irq,gpio-irq", 0);
	hwlog_err("%s: wifi_host->wifi_wakeup_irq %d\n", __func__, wifi_host->wifi_wakeup_irq);
	if (wifi_host->wifi_wakeup_irq<0) {
		ret = -1;
		goto err_gpio_get;
	}

	/* udp board doesn't have vio */
	bool udp = of_property_read_bool(pdev->dev.of_node,"udp_board");
	int vio_enable;
	if(!udp){
		hwlog_err("%s: not udp board, set vio.\n", __func__);
		vio_enable = of_get_named_gpio(pdev->dev.of_node, "wlan_enable,gpio_vio", 0);
		if (vio_enable<0) {
			hwlog_err("%s: get vio_enable (%d) failed.\n", __func__, vio_enable);
			ret = -1;
			goto err_gpio_get;
		}
		ext_gpio_type = of_property_read_bool(pdev->dev.of_node, "ext_type");
		ret = gpio_request(vio_enable, NULL);
		if (ret < 0) {
			hwlog_err("%s: vio gpio_request failed, ret:%d.\n", __func__, ret);
			goto err_vio_gpio_request;
		}

		gpio_direction_output(vio_enable, 1);
		if(!ext_gpio_type) {
			ret = gpio_get_value(vio_enable);
		} else {
			ret = gpio_get_value_cansleep(vio_enable);
		}
		if(ret <= 0) {
			hwlog_err("%s: gpio_get_value, vio_enable, ret:%d, pull on.\n", __func__, ret);
			if(!ext_gpio_type) {
				gpio_set_value(vio_enable, 1);
			} else {
				gpio_set_value_cansleep(vio_enable, 1);
			}
		} else {
			hwlog_err("%s: gpio_get_value, vio already on.\n", __func__);
		}
		gpio_free(vio_enable);
	} else {
		hwlog_err("%s: udp board doesn't have vio, do nothing.\n", __func__);
	}
#endif

    /* set power gpio */
	ret = gpio_request(wifi_host->enable, "wifi_en_gpio");
	if (ret < 0) {
		hwlog_err("%s: gpio_request failed, ret:%d.\n", __func__,
			wifi_host->enable);
		goto err_enable_gpio_request;
	}
	gpio_direction_output(wifi_host->enable, 0);

	/* set apwake gpio */
	ret = gpio_request(wifi_host->wifi_wakeup_irq, "wifi_irq_gpio");
	if (ret < 0) {
		hwlog_err("%s: gpio_request failed, ret:%d.\n", __func__,
			wifi_host->wifi_wakeup_irq);
		goto err_irq_gpio_request;
	}
	gpio_direction_input(wifi_host->wifi_wakeup_irq);

	bcm_wifi_resources[0].start = gpio_to_irq(wifi_host->wifi_wakeup_irq);
	bcm_wifi_resources[0].end = gpio_to_irq(wifi_host->wifi_wakeup_irq) ;

	memset(wifi_host->nvram_path, 0x0, sizeof(wifi_host->nvram_path));
	ret = of_property_read_string(pdev->dev.of_node, "wifi_nvram_name", &nvpath );
	if ( ret < 0 || nvpath == NULL) {
		hwlog_err("%s: get nvrame_name failed, ret:%d.\n", __func__, ret);
	}
	else {
		hwlog_err("%s:  nvrame_name :%s.\n", __func__, nvpath);
		strncpy(wifi_host->nvram_path, nvpath, sizeof(wifi_host->nvram_path)-1);
	}

	ret = platform_device_register(&bcm_wifi_device);
	if (ret) {
		hwlog_err("%s: platform_device_register failed, ret:%d.\n",
			__func__, ret);
		goto err_platform_device_register;
	}
	ret = sysfs_create_group(&bcm_wifi_device.dev.kobj, &attrgroup_debug_level);
	if (ret) {
		hwlog_err("wifi_power_probe create debug level error ret =%d", ret);
	}

	ret = sysfs_create_group(&bcm_wifi_device.dev.kobj, &attrgroup_arp_timeout);
	if (ret) {
		hwlog_err("wifi_power_probe create arp trigger error ret =%d", ret);
	}

	ret = sysfs_create_group(&bcm_wifi_device.dev.kobj, &wifi_state);
	if (ret) {
		hwlog_err("wifi_power_probe sysfs_create_group error ret =%d", ret);
	}

	return 0;
err_platform_device_register:
	gpio_free(wifi_host->wifi_wakeup_irq);
err_irq_gpio_request:
	gpio_free(wifi_host->enable);
err_vio_gpio_request:
err_enable_gpio_request:
err_gpio_get:
#if defined(CONFIG_MMC_DW_HI6XXX) || defined(CONFIG_MMC_DW_HI3XXX)
err_pinctrl_get:
	pinctrl_put(wifi_host->pctrl);
#endif
#if 0
err_regulator_get:
#endif
err_clk_get:
	kfree(wifi_host);
	wifi_host = NULL;
err_malloc_wifi_host:
	deinit_wifi_mem();
	return ret;
}



static struct of_device_id wifi_power_match_table[] = {
	{ .compatible = DTS_COMP_WIFI_POWER_NAME, 
		.data = NULL,
        	},
	{ },
};

static struct platform_driver wifi_power_driver = {
	.driver		= {
		.name		= "bcm4334_power",
		.owner = THIS_MODULE,
	       	.of_match_table	= wifi_power_match_table,
	},
	.probe          = wifi_power_probe,
	
	
};

static int __init wifi_power_init(void)
{
	int ret;

#ifdef CONFIG_HWCONNECTIVITY
    //For OneTrack, we need check it's the right chip type or not.
    //If it's not the right chip type, don't init the driver
    if (!isMyConnectivityChip(CHIP_TYPE_BCM)) {
        hwlog_err("wifi chip type is not match, skip driver init\n");
        return -EINVAL;
    } else {
        hwlog_info("wifi chip type is matched with Broadcom, continue\n");
    }
#endif

	ret = platform_driver_register(&wifi_power_driver);
	if (ret)
		hwlog_err("%s: platform_driver_register failed, ret:%d.\n",
			__func__, ret);
	return ret;
}

static void __exit wifi_power_exit(void)
{
	platform_driver_unregister(&wifi_power_driver);
}
device_initcall(wifi_power_init);

#ifdef CONFIG_LLT_TEST

struct UT_TEST UT_dev_wifi = {
	.read_from_global_buf = read_from_global_buf,
	.char2_byte = char2_byte,
	.read_from_mac_file = read_from_mac_file,
	.show_wifi_open_state = show_wifi_open_state,
	.restore_wifi_open_state = restore_wifi_open_state,
	.show_wifi_debug_level = show_wifi_debug_level,
	.restore_wifi_debug_level = restore_wifi_debug_level,
	.show_wifi_wrong_action_flag = show_wifi_wrong_action_flag,
	.restore_wifi_arp_timeout = restore_wifi_arp_timeout,
	.restore_wifi_wrong_action_debug = restore_wifi_wrong_action_debug,
	.wifi_power_init = wifi_power_init,
	.bcm_wifi_get_nvram_path = bcm_wifi_get_nvram_path,
	.bcm_wifi_reset = bcm_wifi_reset,

};
int Get_wifi_open_err_code()
{
	return wifi_open_err_code;
}

#endif
