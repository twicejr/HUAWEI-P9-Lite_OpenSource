/*
 * hisi_wifi_power.h
 *
 * Copyright (C) 2010 Texas Instruments Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef _HISI_WIFI_POWER_H
#define _HISI_WIFI_POWER_H

#include <linux/clk.h>
#define PREALLOC_WLAN_NUMBER_OF_SECTIONS (4)
#define PREALLOC_WLAN_SECTION_HEADER     (24)
#ifdef HW_SOFTAP_THROUGHPUT_OPTIMIZE
#define PREALLOC_WLAN_NUMBER_OF_BUFFERS  (320)
#define WLAN_SKB_BUF_MIN                 (8192)
#define WLAN_SKB_BUF_MAX                 (16384)
#else
#define PREALLOC_WLAN_NUMBER_OF_BUFFERS  (160)
#define WLAN_SKB_BUF_MIN                 (4096)
#define WLAN_SKB_BUF_MAX                 (8192)
#endif

#define WLAN_SKB_BUF_NUM                 (16)
#define WLAN_SECTION_SIZE_0     (PREALLOC_WLAN_NUMBER_OF_BUFFERS * 128)
#define WLAN_SECTION_SIZE_1     (PREALLOC_WLAN_NUMBER_OF_BUFFERS * 128)
#define WLAN_SECTION_SIZE_2     (PREALLOC_WLAN_NUMBER_OF_BUFFERS * 512)
#define WLAN_SECTION_SIZE_3     (PREALLOC_WLAN_NUMBER_OF_BUFFERS * 1024)
#define WLAN_MAC_NV_NAME        "MACWLAN"
#define WLAN_MAC_LEN            6
#define NV_WLAN_NUM             193
#define WLAN_VALID_SIZE      17
#define NV_WLAN_VALID_SIZE   12
#define NVRAM_PATH_LEN       (129)

#define MAC_ADDRESS_FILE "/data/misc/wifi/macwifi"
struct wifi_host_s {
	struct regulator *vdd;
	struct clk *clk;
	struct pinctrl *pctrl;					
	struct pinctrl_state *pins_normal;
	struct pinctrl_state *pins_idle;
	char chip_fpga;
	bool bEnable;
	int enable;
	int wifi_wakeup_irq;
	char nvram_path[NVRAM_PATH_LEN];
	unsigned char macAddr[WLAN_MAC_LEN];
};

#ifdef CONFIG_LLT_TEST
struct UT_TEST {
	void (*read_from_global_buf)(unsigned char *);
	int (*char2_byte)( char *, char *);
	int (*read_from_mac_file)(unsigned char *);
	ssize_t (*show_wifi_open_state)(struct device *,struct device_attribute *, char *);

	ssize_t (*restore_wifi_open_state)(struct device *, struct device_attribute *,const char *, size_t );
    ssize_t (*show_wifi_debug_level)(struct device *,struct device_attribute *, char *);
    ssize_t (*restore_wifi_debug_level)(struct device *, struct device_attribute *,const char *, size_t );
    ssize_t (*show_wifi_wrong_action_flag)(struct device *,struct device_attribute *, char *);
	ssize_t (*restore_wifi_arp_timeout)(struct device *, struct device_attribute *,const char *, size_t );
    ssize_t (*restore_wifi_wrong_action_debug)(struct device *, struct device_attribute *,const char *, size_t ) ;
	int (*bcm_wifi_get_nvram_path)(char *, int );
	int (*wifi_power_init)(void);
	int (*bcm_wifi_reset)(int);
};
#endif


#define K3V3_WIFI_VDD_VOLTAGE   1800000

extern int hi_sdio_detectcard_to_core(int val);
extern void hi_sdio_set_power(int val);

#endif /*_K3V2_WIFI_POWER_H*/
