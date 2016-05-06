/*
 * Copyright (C) 2010 Trusted Logic S.A.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/i2c.h>
#include <linux/irq.h>
#include <linux/jiffies.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <linux/miscdevice.h>
#include <linux/spinlock.h>
#include <linux/reboot.h>
#include <linux/clk.h>
#include <linux/wakelock.h>
#include <linux/of.h>
#include <linux/of_platform.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/regulator/consumer.h>
#include <dsm/dsm_pub.h>
#include "pn547.h"
#include <linux/mfd/hisi_pmic.h>
//#ifdef CONFIG_V8R2_NFC
//#include "soc_smart_interface.h"
//#endif
#ifdef CONFIG_HUAWEI_HW_DEV_DCT
#include <huawei_platform/devdetect/hw_dev_dec.h>
#endif
#include <huawei_platform/log/hw_log.h>
#define HWLOG_TAG nfc
HWLOG_REGIST();

//#include <hsad/config_mgr.h> //fix udp bug,deleted
//#include <../../../arch/arm/mach-hisi/hisi_udp_board_id.h>
#define MAX_BUFFER_SIZE 512
static int firmware_update = 0;
//static int lcd_status = UNKNOWN_LCD;
static struct wake_lock wlock_read;
#define NFC_GPIO_LEVEL_HIGH 1

static bool ven_felica_status=false;
#define ENABLE_START    0
#define ENABLE_END      1
#define MAX_CONFIG_NAME_SIZE    64
#define _read_sample_test_size      40
#define MAX_NFC_CHIP_TYPE_SIZE   32
#define MAX_NFC_FW_VERSION_SIZE  32
#define MAX_DETECT_SE_SIZE  16

#define NFC_SVDD_SW_ON  1
#define NFC_SVDD_SW_OFF 0

#define SIM1_CARD       1
#define SIM2_CARD       2
#define ESE_CARD         3

#define NFC_CLK_SRC_CPU       0
#define NFC_CLK_SRC_PMU       1

enum NFC_ON_TYPE{
    NFC_ON_BY_GPIO=0,
    NFC_ON_BY_HISI_PMIC,
    NFC_ON_BY_REGULATOR_BULK,
};

static char g_nfc_nxp_config_name[MAX_CONFIG_NAME_SIZE];
static char g_nfc_brcm_conf_name[MAX_CONFIG_NAME_SIZE];
static char g_nfc_chip_type[MAX_NFC_CHIP_TYPE_SIZE];
static char g_nfc_fw_version[MAX_NFC_FW_VERSION_SIZE];
static char g_nfc_detect_se_str[MAX_DETECT_SE_SIZE];
static bool g_nfc_detect_se = false;
static bool g_nfc_ext_gpio = false;//use codec
static bool g_nfc_svdd_sw = false;//use for svdd switch
static int g_nfc_on_type = NFC_ON_BY_REGULATOR_BULK;
static int g_nfcservice_lock = 0;
static int g_nfc_close_type = 0;
static int g_nfc_single_channel = 0;
static int g_nfc_card_num = 0;
/*0 -- hisi cpu(default); 1 -- hisi pmu*/
static int g_nfc_clk_src = NFC_CLK_SRC_CPU;

#ifdef CONFIG_V8R2_NFC
spinlock_t  g_alel21_lock;
#endif

struct pn547_dev {
    wait_queue_head_t    read_wq;
    struct mutex    read_mutex;
    struct i2c_client   *client;
    struct miscdevice   pn547_device;
    struct pinctrl *pctrl;
    struct pinctrl_state *pins_default;
    struct pinctrl_state *pins_idle;
    unsigned int   firm_gpio;
    unsigned int    irq_gpio;
    unsigned int    clkreq_gpio;
    int sim_switch;
    int sim_status;
    int enable_status;
    bool    irq_enabled;
    spinlock_t   irq_enabled_lock;
    struct mutex irq_mutex_lock;
#ifdef CONFIG_V8R2_NFC
    unsigned int ven_gpio;
#else
    unsigned int ven_gpio;
    struct regulator_bulk_data ven_felica;
#endif
    struct clk  *nfc_clk;
};

static  struct pn547_dev* nfcdev;

static struct dsm_dev dsm_nfc = {
    .name = "dsm_nfc",
    .device_name = NULL,
    .ic_name = NULL,
    .module_name = NULL,
    .fops = NULL,
    .buff_size = 1024,
};

static struct dsm_client *nfc_dclient = NULL;

static void hisi_pmic_on(void){
    int ret;

    ret = hisi_pmic_reg_read(0xc3);
    ret |= 0x10;
    hisi_pmic_reg_write(0xc3, ret);
}

static void hisi_pmic_off(void){
    int ret;

    ret = hisi_pmic_reg_read(0xc3);
    ret &= 0x0f;
    hisi_pmic_reg_write(0xc3, ret);
}

static void pmu0_svdd_sel_on(void){
    hwlog_info("%s: in\n", __func__);
    return hisi_pmic_on();
}

static void pmu0_svdd_sel_off(void){
    hwlog_info("%s: in\n", __func__);
    return hisi_pmic_off();
}

static int nfc_get_dts_config_string(const char *node_name,const char *prop_name, char 
    *out_string, int out_string_len)
{
    struct device_node *np=NULL;
    const char *out_value;
    int ret=-1;
    for_each_node_with_property(np, node_name){
        ret = of_property_read_string(np, prop_name, (const char **)&out_value);
        if (ret != 0) {
            hwlog_err("%s: can not get prop values with prop_name: %s\n", __func__,prop_name);
        }
        else{
            if (NULL == out_value){
                hwlog_info("%s: error out_value = NULL\n", __func__);
                ret = -1;
            }else if (strlen (out_value) >= out_string_len){
                hwlog_info("%s: error out_value len :%d >= out_string_len:%d\n", 
                    __func__, strlen(out_value), (int)out_string_len);
                ret = -1;
            }else {
                strncpy(out_string, out_value,  strlen(out_value));
                hwlog_info("%s: =%s\n", __func__,out_string);
            }
        }
    }
    return ret;
}

static int nfc_get_dts_config_u32(const char *node_name,const char *prop_name, u32 *pvalue)
{
    struct device_node *np=NULL;
    int ret=-1;
    for_each_node_with_property(np, node_name){
        ret = of_property_read_u32(np, prop_name, pvalue);
        if (ret != 0) {
            hwlog_err("%s: can not get prop values with prop_name: %s\n", __func__,prop_name);
        }
        else{
            hwlog_info("%s: %s=%d\n", __func__,prop_name,*pvalue);
        }
    }
    return ret;
}

static void get_ext_gpio_type(void){
    char ext_gpio_str[MAX_DETECT_SE_SIZE]={0};
    int ret=-1;

    memset(ext_gpio_str, 0, MAX_DETECT_SE_SIZE);
    ret = nfc_get_dts_config_string("ext_gpio","ext_gpio",
    ext_gpio_str, sizeof(ext_gpio_str));

    if (ret != 0){
        memset(ext_gpio_str, 0, MAX_DETECT_SE_SIZE);
        g_nfc_ext_gpio = false;
        hwlog_err("%s: can't check_ext_gpio\n", __func__);
        return ;
    }else{
        if (!strncasecmp(ext_gpio_str, "true", strlen("true"))){
            g_nfc_ext_gpio = true;
        }else {
            g_nfc_ext_gpio = false;
        }
        hwlog_info("%s: ext_gpio:%s\n", __func__, ext_gpio_str);
    }
    hwlog_info("%s: g_nfc_ext_gpio:%d\n", __func__, g_nfc_ext_gpio);
    return ;
}

static void nfc_gpio_set_value(unsigned int gpio, int val){
    if (g_nfc_ext_gpio){
        hwlog_info("%s: gpio_set_value_cansleep\n", __func__);
        gpio_set_value_cansleep(gpio, val);
    }else{
        hwlog_info("%s: gpio_set_value\n", __func__);
        gpio_set_value(gpio, val);
    }
}

static int nfc_gpio_get_value(unsigned int gpio){
    int ret = -1;

    if (g_nfc_ext_gpio){
        /*hwlog_info("%s: gpio_get_value_cansleep\n", __func__);*/
        ret = gpio_get_value_cansleep(gpio);
    }else{
        /*hwlog_info("%s: gpio_get_value\n", __func__);*/
        ret = gpio_get_value(gpio);
    }
    return ret;
}

static void get_nfc_on_type(void){
    char nfc_on_str[MAX_DETECT_SE_SIZE]={0};
    int ret=-1;

    memset(nfc_on_str, 0, MAX_DETECT_SE_SIZE);
    ret = nfc_get_dts_config_string("nfc_on_type","nfc_on_type",
    nfc_on_str, sizeof(nfc_on_str));

    if (ret != 0){
        memset(nfc_on_str, 0, MAX_DETECT_SE_SIZE);
        g_nfc_on_type = NFC_ON_BY_REGULATOR_BULK;
        hwlog_err("%s: can't check_ext_gpio\n", __func__);
        return ;
    }else{
        if (!strncasecmp(nfc_on_str, "gpio", strlen("gpio"))){
            g_nfc_on_type = NFC_ON_BY_GPIO;
        }else if (!strncasecmp(nfc_on_str, "hisi_pmic", strlen("hisi_pmic"))){
            g_nfc_on_type = NFC_ON_BY_HISI_PMIC;
        }else if (!strncasecmp(nfc_on_str, "regulator_bulk", strlen("regulator_bulk"))){
            g_nfc_on_type = NFC_ON_BY_REGULATOR_BULK;
        }else{
            g_nfc_on_type = NFC_ON_BY_REGULATOR_BULK;
        }
    }
    hwlog_info("%s: g_nfc_on_type:%d\n", __func__, g_nfc_on_type);
    return ;
}

static void get_nfc_svdd_sw(void){
    char nfc_svdd_sw_str[MAX_DETECT_SE_SIZE]={0};
    int ret=-1;

    memset(nfc_svdd_sw_str, 0, MAX_DETECT_SE_SIZE);
    ret = nfc_get_dts_config_string("nfc_svdd_sw","nfc_svdd_sw",
        nfc_svdd_sw_str, sizeof(nfc_svdd_sw_str));

    if (ret != 0){
        memset(nfc_svdd_sw_str, 0, MAX_DETECT_SE_SIZE);
        g_nfc_svdd_sw = false;
        hwlog_err("%s: can't get_nfc_svdd_sw\n", __func__);
        return ;
    }else{
        if (!strncasecmp(nfc_svdd_sw_str, "true", strlen("true"))){
            g_nfc_svdd_sw = true;
        }else{
            g_nfc_svdd_sw = false;
        }
    }
    hwlog_info("%s: g_nfc_svdd_sw:%d\n", __func__, g_nfc_svdd_sw);
    return ;
}

void set_nfc_nxp_config_name(void){
    int ret=-1;

    memset(g_nfc_nxp_config_name, 0, MAX_CONFIG_NAME_SIZE);
    ret = nfc_get_dts_config_string("nfc_nxp_name","nfc_nxp_name", 
        g_nfc_nxp_config_name, sizeof(g_nfc_nxp_config_name));

    if (ret != 0){
        memset(g_nfc_nxp_config_name, 0, MAX_CONFIG_NAME_SIZE);
        hwlog_err("%s: can't get nfc nxp config name\n", __func__);
        return ;
    }
    hwlog_info("%s: nfc nxp config name:%s\n", __func__, g_nfc_nxp_config_name);
    return ;
}

void set_nfc_brcm_config_name(void){
    int ret=-1;

    memset(g_nfc_brcm_conf_name, 0, MAX_CONFIG_NAME_SIZE);
    ret = nfc_get_dts_config_string("nfc_brcm_conf_name","nfc_brcm_conf_name", 
        g_nfc_brcm_conf_name, sizeof(g_nfc_brcm_conf_name));

    if (ret != 0){
        memset(g_nfc_brcm_conf_name, 0, MAX_CONFIG_NAME_SIZE);
        hwlog_err("%s: can't get nfc brcm config name\n", __func__);
        return ;
    }
    hwlog_info("%s: nfc brcm config name:%s\n", __func__, g_nfc_brcm_conf_name);
    return ;
}

void set_nfc_single_channel(void){
    int ret=-1;
    char single_channel_dts_str[MAX_CONFIG_NAME_SIZE]={0};

    memset(single_channel_dts_str, 0, MAX_CONFIG_NAME_SIZE);
    ret = nfc_get_dts_config_string("nfc_single_channel","nfc_single_channel",
        single_channel_dts_str, sizeof(single_channel_dts_str));

    if (ret != 0){
        memset(single_channel_dts_str, 0, MAX_CONFIG_NAME_SIZE);
        hwlog_err("%s: can't get nfc single channel dts config\n", __func__);
        g_nfc_single_channel = 0;
        return ;
    }
    if (!strcasecmp(single_channel_dts_str, "true")){
        g_nfc_single_channel = 1;
    }
    hwlog_info("%s: nfc single channel:%d\n", __func__, g_nfc_single_channel);
    return ;
}

void set_nfc_chip_type_name(void){
    int ret = -1;

    memset(g_nfc_chip_type, 0, MAX_NFC_CHIP_TYPE_SIZE);
    ret = nfc_get_dts_config_string("nfc_chip_type","nfc_chip_type",
        g_nfc_chip_type, sizeof(g_nfc_chip_type));

    if(ret != 0)
    {
        memset(g_nfc_chip_type, 0, MAX_NFC_CHIP_TYPE_SIZE);
        hwlog_err("%s: can't get nfc nfc_chip_type, default pn547\n", __func__);
        strcpy(g_nfc_chip_type, "pn547");
    }
    if (g_nfc_detect_se) {
        memset(g_nfc_chip_type, 0, MAX_NFC_CHIP_TYPE_SIZE);
        strcpy(g_nfc_chip_type, "pn66t");
    }
    hwlog_info("%s: nfc chip type name:%s\n", __func__, g_nfc_chip_type);

    return ;
}

void set_nfc_card_num(void){
    int ret=-1;
    ret=nfc_get_dts_config_u32("nfc_card_num","nfc_card_num", &g_nfc_card_num);
    if(ret != 0){
        g_nfc_card_num = UICC_SUPPORT_CARD_EMULATION;
        hwlog_err("%s: can't get nfc card num config!\n", __func__);
    }
    if (g_nfc_detect_se) {
        g_nfc_card_num = 2;
    }
    return ;
}

static int pn547_bulk_enable(struct  pn547_dev *pdev){
    int ret=0;

#ifdef CONFIG_V8R2_NFC
    gpio_set_value(pdev->ven_gpio, 1);
#else
    switch(g_nfc_on_type)
    {
        case NFC_ON_BY_GPIO:
        {
            hwlog_info("%s: Nfc on by GPIO !\n", __func__);
            gpio_set_value(pdev->ven_gpio, 1);
        }
        break;

        case NFC_ON_BY_REGULATOR_BULK:
        {
            hwlog_info("%s: Nfc on by REGULATOR !\n", __func__);
            if (false == ven_felica_status) {
                ret = regulator_bulk_enable(1, &(pdev->ven_felica));
                if (ret < 0)
                    hwlog_err("%s: regulator_enable failed, ret:%d\n", __func__, ret);
                else
                    ven_felica_status = true;
            } else {
                hwlog_err("%s: ven already enable\n", __func__);
            }
        }
        break;

        case NFC_ON_BY_HISI_PMIC:
        {
            hwlog_info("%s: Nfc on by HISI PMIC !\n", __func__);
            hisi_pmic_on();
        }
        break;

        default:
        {
            hwlog_err("%s: Unknown nfc on type !\n", __func__);
        }
        break;
    }
#endif

    return ret;
}

static int  pn547_bulk_disable(struct  pn547_dev *pdev){
    int ret=0;

#ifdef CONFIG_V8R2_NFC
    gpio_set_value(pdev->ven_gpio, 0);
#else
    switch(g_nfc_on_type)
    {
        case NFC_ON_BY_GPIO:
        {
            hwlog_info("%s: Nfc off by GPIO !\n", __func__);
            gpio_set_value(pdev->ven_gpio, 0);
        }
        break;

        case NFC_ON_BY_REGULATOR_BULK:
        {
            hwlog_info("%s: Nfc off by REGULATOR !\n", __func__);
            if (true == ven_felica_status){
                ret = regulator_bulk_disable(1, &(pdev->ven_felica));
                if (ret < 0)
                    hwlog_err("%s: regulator_disable failed, ret:%d\n", __func__, ret);
                else
                    ven_felica_status = false;
            } else {
                hwlog_err("%s: ven already disable\n", __func__);
            }
        }
        break;

        case NFC_ON_BY_HISI_PMIC:
        {
            hwlog_info("%s: Nfc off by HISI PMIC !\n", __func__);
            hisi_pmic_off();
        }
        break;

        default:
        {
            hwlog_err("%s: Unknown nfc off type !\n", __func__);
        }
        break;
    }
#endif

    return ret;
}

static int pn547_enable_clk(struct  pn547_dev *pdev, int enableflg)
{
    int ret = 0;

    if (NFC_CLK_SRC_PMU == g_nfc_clk_src) {
        hwlog_info("%s: pmu clk is controlled by clk_req gpio.\n", __func__);
        return 0;
    }

    if (enableflg) {
        /*enable clock output*/
        hwlog_info("%s: enable clock output\n", __func__);
        ret = pinctrl_select_state(pdev->pctrl, pdev->pins_default);
        if (ret < 0) {
            hwlog_err("%s: unapply new state!\n", __func__);
        }

        ret = clk_prepare_enable(pdev->nfc_clk);
        if (ret < 0) {
            hwlog_err("%s: clk_enable failed, ret:%d\n", __func__, ret);
        }
    } else {
        /*disable clock output*/
        hwlog_info("%s: disable clock output\n", __func__);
        clk_disable_unprepare(pdev->nfc_clk);
        ret = pinctrl_select_state(pdev->pctrl, pdev->pins_idle);
        if (ret < 0) {
            hwlog_err("%s: unapply new state!\n", __func__);
        }
    }

    return ret;
}

static int pn547_enable_nfc(struct  pn547_dev *pdev)
{
    int ret = 0;

    /* enable chip */
    ret = pn547_bulk_enable(pdev);
    msleep(10);
    if (ret < 0)
        return ret;

    ret = pn547_bulk_disable(pdev);
    msleep(10);
    if (ret < 0)
        return ret;

    ret = pn547_bulk_enable(pdev);
    msleep(10);

    return ret;
}

static void pn547_disable_irq(struct pn547_dev *pn547_dev)
{
    unsigned int flags;

    spin_lock_irqsave(&pn547_dev->irq_enabled_lock, flags);
    if (pn547_dev->irq_enabled) {
        disable_irq_nosync(pn547_dev->client->irq);
        pn547_dev->irq_enabled = false;
    }
    spin_unlock_irqrestore(&pn547_dev->irq_enabled_lock, flags);
}

static void pn547_disable_irq_for_ext_gpio(struct pn547_dev *pn547_dev)
{
    mutex_lock(&pn547_dev->irq_mutex_lock);
    if (pn547_dev->irq_enabled) {
        disable_irq_nosync(pn547_dev->client->irq);
        pn547_dev->irq_enabled = false;
    }
    mutex_unlock(&pn547_dev->irq_mutex_lock);
}

static irqreturn_t pn547_dev_irq_handler(int irq, void *dev_id)
{
    struct pn547_dev *pn547_dev = dev_id;

    if (g_nfc_ext_gpio)
    {
        pn547_disable_irq_for_ext_gpio(pn547_dev);
    }
    else
    {
        pn547_disable_irq(pn547_dev);
    }

    /*set a wakelock to avoid entering into suspend */
    wake_lock_timeout(&wlock_read, 1 * HZ);

    /* Wake up waiting readers */
    wake_up(&pn547_dev->read_wq);

    return IRQ_HANDLED;
}

static ssize_t pn547_dev_read(struct file *filp, char __user *buf,
        size_t count, loff_t *offset)
{
    struct pn547_dev *pn547_dev = filp->private_data;
    char tmp[MAX_BUFFER_SIZE];
    char *tmpStr = NULL;
    int ret;
    int i;
    int retry;
    bool isSuccess = false;

    if (count > MAX_BUFFER_SIZE)
        count = MAX_BUFFER_SIZE;

    mutex_lock(&pn547_dev->read_mutex);

    if (!nfc_gpio_get_value(pn547_dev->irq_gpio)) {
        if (filp->f_flags & O_NONBLOCK) {
            ret = -EAGAIN;
            goto fail;
        }

        if (g_nfc_ext_gpio)
        {
            pn547_disable_irq_for_ext_gpio(pn547_dev);
        }
        else
        {
            pn547_disable_irq(pn547_dev);
        }

        pn547_dev->irq_enabled = true;
        enable_irq(pn547_dev->client->irq);
        ret = wait_event_interruptible(pn547_dev->read_wq,
        nfc_gpio_get_value(pn547_dev->irq_gpio));
        if (ret)
            goto fail;
    }

    tmpStr = (char *)kzalloc(sizeof(tmp)*2 + 1, GFP_KERNEL);
    if (!tmpStr) {
        hwlog_info("%s:Cannot allocate memory for read tmpStr.\n", __func__);
        ret = -ENOMEM;
        goto fail;
    }

    /* Read data, we have 3 chances */
    for (retry = 0; retry < NFC_TRY_NUM; retry++)
    {
        ret = i2c_master_recv(pn547_dev->client, tmp, (int)count);

        for(i=0; i<count; i++)
        {
            snprintf(&tmpStr[i * 2], 3, "%02X", tmp[i]);
        }

        hwlog_info("%s : retry = %d, ret = %d, count = %3d > %s\n", __func__, retry, ret, (int)count, tmpStr);

        if (ret == (int)count) {
            isSuccess = true;
            break;
        } else {
            hwlog_info("%s : read data try =%d returned %d\n", __func__,retry,ret);
            msleep(1);
            continue;
        }
    }

    kfree(tmpStr);
    if (false == isSuccess) {
        hwlog_err("%s : i2c_master_recv returned %d\n", __func__, ret);
        if(-EOPNOTSUPP==ret){
            if (!dsm_client_ocuppy(nfc_dclient)) {
                dsm_client_record(nfc_dclient,"i2c_master_recv returned %d. Operation not supported on transport endpoint \n",ret);
                dsm_client_notify(nfc_dclient, DSM_NFC_I2C_READ_EOPNOTSUPP_ERROR_NO);
            }
        }
        else if(-EREMOTEIO==ret){
            if (!dsm_client_ocuppy(nfc_dclient)) {
                dsm_client_record(nfc_dclient,"i2c_master_recv returned %d. Remote I/O error \n",ret);
                dsm_client_notify(nfc_dclient, DSM_NFC_I2C_READ_EREMOTEIO_ERROR_NO);
            }
        }
        else{
            if (!dsm_client_ocuppy(nfc_dclient)) {
                dsm_client_record(nfc_dclient,"i2c_master_recv returned %d.\n",ret);
                dsm_client_notify(nfc_dclient, DSM_NFC_I2C_READ_ERROR_NO);
            }
        }
        ret = -EIO;
    }

    mutex_unlock(&pn547_dev->read_mutex);

    if (ret < 0) {
        hwlog_err("%s: i2c_master_recv returned %d\n", __func__, ret);
        return ret;
    }
    if (ret > (int)count) {
        hwlog_err("%s: received too many bytes from i2c (%d)\n",
            __func__, ret);
        return -EIO;
    }
    if (copy_to_user(buf, tmp, ret)) {
        hwlog_err("%s : failed to copy to user space\n", __func__);
        return -EFAULT;
    }
    return (size_t)ret;

fail:
    mutex_unlock(&pn547_dev->read_mutex);
    return (size_t)ret;
}

static ssize_t pn547_dev_write(struct file *filp, const char __user *buf,
        size_t count, loff_t *offset)
{
    struct pn547_dev  *pn547_dev;
    char tmp[MAX_BUFFER_SIZE];
    char *tmpStr = NULL;
    int ret;
    int retry;
    int i;
    bool isSuccess = false;

    pn547_dev = filp->private_data;

    if (count > MAX_BUFFER_SIZE)
        count = MAX_BUFFER_SIZE;

    if (copy_from_user(tmp, buf, count)) {
        hwlog_err("%s : failed to copy from user space\n", __func__);
        return -EFAULT;
    }

    tmpStr = (char *)kzalloc(sizeof(tmp)*2 + 1, GFP_KERNEL);
    if (!tmpStr) {
        hwlog_info("%s:Cannot allocate memory for write tmpStr.\n", __func__);
        return -ENOMEM;
    }

    /* Write data, we have 3 chances */
    for (retry = 0; retry < NFC_TRY_NUM; retry++)
    {
        ret = i2c_master_send(pn547_dev->client, tmp, (int)count);

        for(i=0; i<count; i++)
        {
            snprintf(&tmpStr[i * 2], 3, "%02X", tmp[i]);
        }

        hwlog_info("%s : retry = %d, ret = %d, count = %3d > %s\n", __func__, retry, ret, (int)count, tmpStr);

        if (ret == (int)count) {
            isSuccess = true;
            break;
        } else {
            if (retry > 0) {
                hwlog_info("%s : send data try =%d returned %d\n", __func__,retry,ret);
            }
            msleep(1);
            continue;
        }
    }
    kfree(tmpStr);

    if (false == isSuccess) {
        hwlog_err("%s : i2c_master_send returned %d\n", __func__, ret);
        if(-EOPNOTSUPP==ret){
            if (!dsm_client_ocuppy(nfc_dclient)) {
                dsm_client_record(nfc_dclient,"i2c_master_send returned %d. Operation not supported on transport endpoint \n",ret);
                dsm_client_notify(nfc_dclient, DSM_NFC_I2C_WRITE_EOPNOTSUPP_ERROR_NO);
            }
        }
        else if(-EREMOTEIO==ret){
            if (!dsm_client_ocuppy(nfc_dclient)) {
                dsm_client_record(nfc_dclient,"i2c_master_send returned %d. Remote I/O error \n",ret);
                dsm_client_notify(nfc_dclient, DSM_NFC_I2C_WRITE_EREMOTEIO_ERROR_NO);
            }
        }
        else{
            if (!dsm_client_ocuppy(nfc_dclient)) {
                dsm_client_record(nfc_dclient,"i2c_master_send returned %d.\n",ret);
                dsm_client_notify(nfc_dclient, DSM_NFC_I2C_WRITE_ERROR_NO);
            }
        }
        ret = -EIO;
    }

    return (size_t)ret;
}

static int pn547_dev_open(struct inode *inode, struct file *filp)
{
    struct pn547_dev *pn547_dev = container_of(filp->private_data,
                        struct pn547_dev,
                        pn547_device);

    filp->private_data = pn547_dev;

    hwlog_info("%s : %d,%d\n", __func__, imajor(inode), iminor(inode));

    return 0;
}

static int pn547_dev_ioctl(struct file *filp,
                unsigned int cmd, unsigned int arg)
{
    struct pn547_dev *pn547_dev = filp->private_data;
    int ret  = 0;

    switch(cmd){
    case PN547_SET_PWR:
        if (arg == 2) {
            /* power on with firmware download (requires hw reset)
              */
            hwlog_info("%s power on with firmware\n", __func__);
            ret = pn547_bulk_enable(pn547_dev);
            if (ret < 0) {
                hwlog_err("%s: regulator_enable failed, ret:%d\n", __func__, ret);
                return ret;
            }
            msleep(1);
            nfc_gpio_set_value(pn547_dev->firm_gpio, 1);

            msleep(20);
            ret = pn547_bulk_disable(pn547_dev);
            if (ret < 0) {
                hwlog_err("%s: regulator_disable failed, ret:%d\n", __func__, ret);
                return ret;
            }

            msleep(60);
            ret = pn547_bulk_enable(pn547_dev);
            if (ret < 0) {
                hwlog_err("%s: regulator_enable failed, ret:%d\n", __func__, ret);
                return ret;
            }

            ret = pn547_enable_clk(pn547_dev, 1);
            if (ret < 0) {
                hwlog_err("%s: pn547_enable_clk failed, ret:%d\n", __func__, ret);
            }

            msleep(20);
        } else if (arg == 1) {
            /* power on */
            hwlog_info("%s power on\n", __func__);
            nfc_gpio_set_value(pn547_dev->firm_gpio, 0);
            ret = pn547_bulk_enable(pn547_dev);
            if (ret < 0) {
                hwlog_err("%s: regulator_enable failed, ret:%d\n", __func__, ret);
                return -EINVAL;
            }

            ret = pn547_enable_clk(pn547_dev, 1);
            if (ret < 0) {
                hwlog_err("%s: pn547_enable_clk failed, ret:%d\n", __func__, ret);
            }

            msleep(20);
        } else  if (arg == 0) {
            /* power off */
            hwlog_info("%s power off\n", __func__);
            nfc_gpio_set_value(pn547_dev->firm_gpio, 0);
            ret = pn547_bulk_disable(pn547_dev);
            if (ret < 0) {
                hwlog_err("%s: regulator_disable failed, ret:%d\n", __func__, ret);
                return -EINVAL;
            }
            ret = pn547_enable_clk(pn547_dev, 0);
            if (ret < 0) {
                hwlog_err("%s: pn547_disable_clk failed, ret:%d\n", __func__, ret);
            }

            msleep(60);
        } else {
            hwlog_err("%s bad arg %u\n", __func__, arg);
            return -EINVAL;
        }
        break;
    default:
        hwlog_err("%s bad ioctl %u\n", __func__, cmd);
        return -EINVAL;
    }

    return 0;
}

static const struct file_operations pn547_dev_fops = {
    .owner   = THIS_MODULE,
    .llseek   = no_llseek,
    .read     = pn547_dev_read,
    .write    = pn547_dev_write,
    .open    = pn547_dev_open,
    .unlocked_ioctl = pn547_dev_ioctl,
#ifdef CONFIG_COMPAT
    .compat_ioctl        = pn547_dev_ioctl,
#endif
};
static ssize_t pn547_i2c_write(struct  pn547_dev *pdev,const char *buf,int count)
{
    int ret;
    int retry;
    bool isSuccess = false;
    char *tmpStr = NULL;
    char tmp[MAX_BUFFER_SIZE];
    int i;

    tmpStr = (char *)kzalloc(255*2, GFP_KERNEL);
    if (!tmpStr) {
        hwlog_info("%s:Cannot allocate memory for write tmpStr.\n", __func__);
        return -ENOMEM;
    }

    /* Write data, we have 3 chances */
    for (retry = 0; retry < NFC_TRY_NUM; retry++)
    {
        ret = i2c_master_send(pdev->client, buf, (int)count);

        for(i=0; i<count; i++)
        {
            snprintf(&tmpStr[i * 2], 3, "%02X", buf[i]);
        }

        hwlog_info("%s : retry = %d, ret = %d, count = %3d > %s\n", __func__, retry, ret, (int)count, tmpStr);

        if (ret == (int)count) {
            isSuccess = true;
            break;
        } else {
            if (retry > 0) {
                hwlog_info("%s : send data try =%d returned %d\n", __func__,retry,ret);
            }
            msleep(1);
            continue;
        }
    }
    kfree(tmpStr);
    if (false == isSuccess) {
        hwlog_err("%s : i2c_master_send returned %d\n", __func__, ret);
        if(-EOPNOTSUPP==ret){
            if (!dsm_client_ocuppy(nfc_dclient)) {
                dsm_client_record(nfc_dclient,"RD_i2c_master_send returned %d. Operation not supported on transport endpoint \n",ret);
                dsm_client_notify(nfc_dclient, DSM_NFC_RD_I2C_WRITE_EOPNOTSUPP_ERROR_NO);
            }
        }
        else if(-EREMOTEIO==ret){
            if (!dsm_client_ocuppy(nfc_dclient)) {
                dsm_client_record(nfc_dclient,"i2c_master_send returned %d. Remote I/O error \n",ret);
                dsm_client_notify(nfc_dclient, DSM_NFC_RD_I2C_WRITE_EREMOTEIO_ERROR_NO);
            }
        }
        else{
            if (!dsm_client_ocuppy(nfc_dclient)) {
                dsm_client_record(nfc_dclient,"i2c_master_send returned %d.\n",ret);
                dsm_client_notify(nfc_dclient, DSM_NFC_RD_I2C_WRITE_ERROR_NO);
            }
        }
        ret = -EIO;
    }
    return (size_t)ret;
}
static ssize_t pn547_i2c_read(struct  pn547_dev *pdev,char *buf,int count)
{
    int ret;
    int retry;
    bool isSuccess = false;
    char *tmpStr = NULL;
    char tmp[MAX_BUFFER_SIZE];
    int i;

    if (!nfc_gpio_get_value(pdev->irq_gpio)) {
        if (g_nfc_ext_gpio)
        {
            pn547_disable_irq_for_ext_gpio(pdev);
        }
        else
        {
            pn547_disable_irq(pdev);
        }

        pdev->irq_enabled = true;
        enable_irq(pdev->client->irq);
        ret = wait_event_interruptible_timeout(pdev->read_wq,
        nfc_gpio_get_value(pdev->irq_gpio),msecs_to_jiffies(1000));
        if (ret <= 0)
        {
            ret  = -1;
            hwlog_err("%s : wait_event_interruptible_timeout error!\n", __func__);
            goto fail;
        }
    }

    tmpStr = (char *)kzalloc(255*2, GFP_KERNEL);
    if (!tmpStr) {
        hwlog_info("%s:Cannot allocate memory for write tmpStr.\n", __func__);
        return -ENOMEM;
    }

    /* Read data, we have 3 chances */
    for (retry = 0; retry < NFC_TRY_NUM; retry++)
    {
        ret = i2c_master_recv(pdev->client, buf, (int)count);

        for(i=0; i<count; i++)
        {
            snprintf(&tmpStr[i * 2], 3, "%02X", buf[i]);
        }

        hwlog_info("%s : retry = %d, ret = %d, count = %3d > %s\n", __func__, retry, ret, (int)count, tmpStr);

        if (ret == (int)count) {
            isSuccess = true;
            break;
        } else {
            hwlog_err("%s : read data try =%d returned %d\n", __func__,retry,ret);
            msleep(1);
            continue;
        }
    }
    kfree(tmpStr);
    if (false == isSuccess) {
        hwlog_err("%s : i2c_master_recv returned %d\n", __func__, ret);
        if(-EOPNOTSUPP==ret){
            if (!dsm_client_ocuppy(nfc_dclient)) {
                dsm_client_record(nfc_dclient,"RD_i2c_master_recv returned %d. Operation not supported on transport endpoint \n",ret);
                dsm_client_notify(nfc_dclient, DSM_NFC_RD_I2C_READ_EOPNOTSUPP_ERROR_NO);
            }
        }
        else if(-EREMOTEIO==ret){
            if (!dsm_client_ocuppy(nfc_dclient)) {
                dsm_client_record(nfc_dclient,"RD_i2c_master_recv returned %d. Remote I/O error \n",ret);
                dsm_client_notify(nfc_dclient, DSM_NFC_RD_I2C_READ_EREMOTEIO_ERROR_NO);
            }
        }
        else{
            if (!dsm_client_ocuppy(nfc_dclient)) {
                dsm_client_record(nfc_dclient,"RD_i2c_master_recv returned %d.\n",ret);
                dsm_client_notify(nfc_dclient, DSM_NFC_RD_I2C_READ_ERROR_NO);
            }
        }
        ret = -EIO;
    }
    return (size_t)ret;
fail:
    return (size_t)ret;
}
static int check_sim_status(struct i2c_client *client, struct  pn547_dev *pdev)
{
    int ret;

    unsigned char recvBuf[40];
    const  char send_reset[] = {0x20,0x00,0x01,0x01};
    const  char init_cmd[] = {0x20,0x01,0x00};

    const  char read_config[] = {0x2F,0x02,0x00};
    const  char read_config_UICC[] = {0x2F,0x3E,0x01,0x00};         //swp1
    const  char read_config_eSE[] = {0x2F,0x3E,0x01,0x01};           //eSE
    pdev->sim_status = 0;

    /*hardware reset*/
    /* power on */
    nfc_gpio_set_value(pdev->firm_gpio, 0);
    ret = pn547_bulk_enable(pdev);
    if (ret < 0)
    {
        hwlog_err("%s: regulator_enable failed, ret:%d\n", __func__, ret);
        goto failed;
    }
    msleep(20);


    /* power off */
    ret = pn547_bulk_disable(pdev);
    if (ret < 0) {
        hwlog_err("%s: regulator_disable failed, ret:%d\n", __func__, ret);
        goto failed;
    }
    msleep(60);

    /* power on */
    ret = pn547_bulk_enable(pdev);
    if (ret < 0)
    {
        hwlog_err("%s: regulator_enable failed, ret:%d\n", __func__, ret);
        goto failed;
    }
    msleep(20);

    /*write CORE_RESET_CMD*/
    ret=pn547_i2c_write(pdev,send_reset,sizeof(send_reset));
    if(ret < 0)
    {
        hwlog_err("%s: pn547_i2c_write failed, ret:%d\n", __func__, ret);
        goto failed;
    }
    /*read response*/
    ret=pn547_i2c_read(pdev,recvBuf,_read_sample_test_size);
    if(ret < 0)
    {
        hwlog_err("%s: pn547_i2c_read failed, ret:%d\n", __func__, ret);
        goto failed;
    }

    udelay(500);
    /*write CORE_INIT_CMD*/
    ret=pn547_i2c_write(pdev,init_cmd,sizeof(init_cmd));
    if(ret < 0)
    {
        hwlog_err("%s: pn547_i2c_write failed, ret:%d\n", __func__, ret);
        goto failed;
    }
    /*read response*/
    ret=pn547_i2c_read(pdev,recvBuf,_read_sample_test_size);
    if(ret < 0)
    {
        hwlog_err("%s: pn547_i2c_read failed, ret:%d\n", __func__, ret);
        goto failed;
    }

    udelay(500);
    /*write NCI_PROPRIETARY_ACT_CMD*/
    ret=pn547_i2c_write(pdev,read_config,sizeof(read_config));
    if(ret < 0)
    {
        hwlog_err("%s: pn547_i2c_write failed, ret:%d\n", __func__, ret);
        goto failed;
    }
    /*read response*/
    ret=pn547_i2c_read(pdev,recvBuf,_read_sample_test_size);
    if(ret < 0)
    {
        hwlog_err("%s: pn547_i2c_read failed, ret:%d\n", __func__, ret);
        goto failed;
    }

    udelay(500);

    /*write TEST_SWP_CMD UICC*/
    ret=pn547_i2c_write(pdev,read_config_UICC,sizeof(read_config_UICC));
    if(ret < 0)
    {
        hwlog_err("%s: pn547_i2c_write failed, ret:%d\n", __func__, ret);
        goto failed;
    }
    /*read response*/
    ret=pn547_i2c_read(pdev,recvBuf,_read_sample_test_size);
    if(ret < 0)
    {
        hwlog_err("%s: pn547_i2c_read failed, ret:%d\n", __func__, ret);
        goto failed;
    }

    mdelay(10);
    /*read notification*/
    ret=pn547_i2c_read(pdev,recvBuf,_read_sample_test_size);
    if(ret < 0)
    {
        hwlog_err("%s: pn547_i2c_read failed, ret:%d\n", __func__, ret);
        goto failed;
    }

    if(recvBuf[0] == 0x6F && recvBuf[1] == 0x3E && recvBuf[3] == 0x00)
    {
        pdev->sim_status |= UICC_SUPPORT_CARD_EMULATION;
    }

    /*write TEST_SWP_CMD eSE*/
    ret=pn547_i2c_write(pdev,read_config_eSE,sizeof(read_config_eSE));
    if(ret < 0)
    {
        hwlog_err("%s: pn547_i2c_write failed, ret:%d\n", __func__, ret);
        goto failed;
    }
    /*read response*/
    ret=pn547_i2c_read(pdev,recvBuf,_read_sample_test_size);
    if(ret < 0)
    {
        hwlog_err("%s: pn547_i2c_read failed, ret:%d\n", __func__, ret);
        goto failed;
    }

    mdelay(10);
    /*read notification*/
    ret=pn547_i2c_read(pdev,recvBuf,_read_sample_test_size);
    if(ret < 0)
    {
        hwlog_err("%s: pn547_i2c_read failed, ret:%d\n", __func__, ret);
        goto failed;
    }

    if(recvBuf[0] == 0x6F && recvBuf[1] == 0x3E && recvBuf[3] == 0x00)
    {
        pdev->sim_status |= eSE_SUPPORT_CARD_EMULATION;
    }

    return pdev->sim_status;
failed:
    pdev->sim_status = ret;
    return ret;
}

static ssize_t nfc_fwupdate_store(struct device *dev, struct device_attribute *attr,
            const char *buf, size_t count)
{

    if ('1' == buf[0]) {
        firmware_update = 1;
        hwlog_info("%s:firmware update success\n", __func__);
    }

    return (ssize_t)count;
}

static ssize_t nfc_fwupdate_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return (ssize_t)(snprintf(buf, sizeof(firmware_update)+1, "%d", firmware_update));
}
#if 0
static ssize_t nfc_check_lcd_status_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    hwlog_info("%s:lcd_status = %d\n", __func__,lcd_status);
    return (ssize_t)(snprintf(buf, sizeof(lcd_status)+1, "%d", lcd_status));
}
#endif
static ssize_t nxp_config_name_store(struct device *dev, struct device_attribute *attr,
            const char *buf, size_t count)
{
    return (ssize_t)count;
}

static ssize_t nxp_config_name_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return (ssize_t)(snprintf(buf, strlen(g_nfc_nxp_config_name)+1, "%s", g_nfc_nxp_config_name));
}

static ssize_t nfc_brcm_conf_name_store(struct device *dev, struct device_attribute *attr,
            const char *buf, size_t count)
{
    return (ssize_t)count;
}
static ssize_t nfc_brcm_conf_name_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return (ssize_t)(snprintf(buf, strlen(g_nfc_brcm_conf_name)+1, "%s", g_nfc_brcm_conf_name));
}
/*
    function: check which sim card support card Emulation.
    return value:
        eSE     UICC    value
        0         0          0          (not support)
        0         1          1          (swp1 support)
        1         0          2          (swp2 support)
        1         1          3          (all support)
        <0  :error
*/
static ssize_t nfc_sim_status_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    int status=-1;
    struct i2c_client *i2c_client_dev = container_of(dev, struct i2c_client, dev);
    struct pn547_dev *pn547_dev;
    pn547_dev = i2c_get_clientdata(i2c_client_dev);
    if(pn547_dev == NULL)
    {
        hwlog_err("%s:  pn547_dev == NULL!\n", __func__);
        return status;
    }
    hwlog_info("%s: enter!\n", __func__);
    status = check_sim_status(i2c_client_dev,pn547_dev);
    if(status < 0)
    {
        hwlog_err("%s:  check_sim_status error!\n", __func__);
    }
    hwlog_info("%s: status=%d\n", __func__,status);
    return (ssize_t)(snprintf(buf, MAX_ATTRIBUTE_BUFFER_SIZE-1,"%d\n", status));
}

static ssize_t nfc_sim_switch_store(struct device *dev, struct device_attribute *attr,
            const char *buf, size_t count)
{
    struct i2c_client *i2c_client_dev = container_of(dev, struct i2c_client, dev);
    struct pn547_dev *pn547_dev;
    int val = 0;

    pn547_dev = i2c_get_clientdata(i2c_client_dev);
    if(pn547_dev == NULL)
    {
        hwlog_err("%s:  pn547_dev == NULL!\n", __func__);
        return 0;
    }
    if (sscanf(buf, "%1d", &val) == 1) {
        if (val >=1 && val <= 3)
        {
            pn547_dev->sim_switch = val;
        }
        else
        {
            return -EINVAL;
        }
    }
    else
        return -EINVAL;
    return (ssize_t)count;
}

static ssize_t nfc_sim_switch_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct i2c_client *i2c_client_dev = container_of(dev, struct i2c_client, dev);
    struct pn547_dev *pn547_dev;
    pn547_dev = i2c_get_clientdata(i2c_client_dev);
    if(pn547_dev == NULL)
    {
        hwlog_err("%s:  pn547_dev == NULL!\n", __func__);
        return 0;
    }
    return (ssize_t)(snprintf(buf,  MAX_ATTRIBUTE_BUFFER_SIZE-1, "%d\n", pn547_dev->sim_switch));
}
static ssize_t rd_nfc_sim_status_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    int status=-1;
    struct i2c_client *i2c_client_dev = container_of(dev, struct i2c_client, dev);
    struct pn547_dev *pn547_dev;
    pn547_dev = i2c_get_clientdata(i2c_client_dev);
    if(pn547_dev == NULL)
    {
        hwlog_err("%s:  pn547_dev == NULL!\n", __func__);
        return status;
    }
    return (ssize_t)(snprintf(buf, MAX_ATTRIBUTE_BUFFER_SIZE-1,"%d\n", pn547_dev->sim_status));
}
static ssize_t nfc_enable_status_store(struct device *dev, struct device_attribute *attr,
             const char *buf, size_t count)
{
    struct i2c_client *i2c_client_dev = container_of(dev, struct i2c_client, dev);
    struct pn547_dev *pn547_dev;
    int val = 0;

    pn547_dev = i2c_get_clientdata(i2c_client_dev);
    if(pn547_dev == NULL)
    {
        hwlog_err("%s:  pn547_dev == NULL!\n", __func__);
        return 0;
    }
    if (sscanf(buf, "%1d", &val) == 1) {
        if(val == ENABLE_START){
            pn547_dev->enable_status = ENABLE_START;
        }else if(val == ENABLE_END){
            pn547_dev->enable_status = ENABLE_END;
        }else{
            return -EINVAL;
        }
    }
    else
        return -EINVAL;
    return (ssize_t)count;
}
static ssize_t nfc_enable_status_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct i2c_client *i2c_client_dev = container_of(dev, struct i2c_client, dev);
    struct pn547_dev *pn547_dev;
    pn547_dev = i2c_get_clientdata(i2c_client_dev);
    if(pn547_dev == NULL)
    {
        hwlog_err("%s:  pn547_dev == NULL!\n", __func__);
        return 0;
    }
    return (ssize_t)(snprintf(buf,  MAX_ATTRIBUTE_BUFFER_SIZE-1, "%d\n", pn547_dev->enable_status));
}
static ssize_t nfc_card_num_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return (ssize_t)(snprintf(buf,  MAX_ATTRIBUTE_BUFFER_SIZE-1, "%d\n", (unsigned char)g_nfc_card_num));
}
static ssize_t nfc_fw_version_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    int ret = -1;

    memset(g_nfc_fw_version, 0, MAX_NFC_FW_VERSION_SIZE);
    ret = nfc_get_dts_config_string("nfc_fw_version","nfc_fw_version",
        g_nfc_fw_version, sizeof(g_nfc_fw_version));

    if(ret != 0)
    {
        memset(g_nfc_fw_version, 0, MAX_NFC_FW_VERSION_SIZE);
        hwlog_err("%s: can't get nfc g_nfc_fw_version, default FW 8.1.24\n", __func__);
        strcpy(g_nfc_fw_version, "FW 8.1.24");
    }
    return (ssize_t)(snprintf(buf,  MAX_ATTRIBUTE_BUFFER_SIZE-1, "%s", g_nfc_fw_version));
}
static ssize_t nfc_chip_type_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return (ssize_t)(snprintf(buf,  strlen(g_nfc_chip_type)+1, "%s", g_nfc_chip_type));
}

static ssize_t nfcservice_lock_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return (ssize_t)(snprintf(buf,  MAX_ATTRIBUTE_BUFFER_SIZE-1, "%d", g_nfcservice_lock));
}

static ssize_t nfcservice_lock_store(struct device *dev, struct device_attribute *attr,
             const char *buf, size_t count)
{
    int val = 0;

    if (sscanf(buf, "%1d", &val) == 1) {
        g_nfcservice_lock = val;
    }else{
        hwlog_err("%s: set g_nfcservice_lock error\n", __func__);
        g_nfcservice_lock = 0;
    }
    hwlog_info("%s: g_nfcservice_lock:%d\n", __func__, g_nfcservice_lock);
    return (ssize_t)count;
}

static ssize_t nfc_svdd_sw_store(struct device *dev, struct device_attribute *attr,
             const char *buf, size_t count)
{
    int val = 0;

    if (sscanf(buf, "%1d", &val) == 1) {
        switch(val){
            case NFC_SVDD_SW_OFF:
                pmu0_svdd_sel_off();
                break;
            case NFC_SVDD_SW_ON:
                pmu0_svdd_sel_on();
                break;
            default:
                hwlog_err("%s: svdd switch error, val:%d[0:pulldown, 1:pullup]\n", __func__, val);
                break;
        }
    }else{
        hwlog_err("%s: val len error\n", __func__);
        return (ssize_t)count;
    }
    g_nfc_svdd_sw = val;
    hwlog_info("%s: nfc svdd switch to %d\n", __func__, val);
    return (ssize_t)count;
}

static ssize_t  nfc_svdd_sw_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return (ssize_t)(snprintf(buf,  MAX_ATTRIBUTE_BUFFER_SIZE-1, "%d", g_nfc_svdd_sw ));
}

static ssize_t nfc_close_type_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return (ssize_t)(snprintf(buf,  MAX_ATTRIBUTE_BUFFER_SIZE-1, "%d", g_nfc_close_type));
}

static ssize_t nfc_close_type_store(struct device *dev, struct device_attribute *attr,
             const char *buf, size_t count)
{
    int val = 0;
    if (sscanf(buf, "%1d", &val) == 1) {
        g_nfc_close_type = val;
    }else{
        hwlog_err("%s: set g_nfc_close_type error\n", __func__);
        g_nfc_close_type = 0;
    }
    hwlog_info("%s: g_nfc_close_type:%d\n", __func__, g_nfc_close_type);
    return (ssize_t)count;
}

static ssize_t nfc_single_channel_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return (ssize_t)(snprintf(buf,  MAX_ATTRIBUTE_BUFFER_SIZE-1, "%d", g_nfc_single_channel));
}

static struct device_attribute pn547_attr[] ={

    __ATTR(nfc_fwupdate, 0664, nfc_fwupdate_show, nfc_fwupdate_store),
    __ATTR(nxp_config_name, 0664, nxp_config_name_show, nxp_config_name_store),
    __ATTR(nfc_brcm_conf_name, 0664, nfc_brcm_conf_name_show, nfc_brcm_conf_name_store),
    __ATTR(nfc_sim_switch, 0664, nfc_sim_switch_show, nfc_sim_switch_store),
    __ATTR(nfc_sim_status, 0444, nfc_sim_status_show, NULL),
    __ATTR(rd_nfc_sim_status, 0444, rd_nfc_sim_status_show, NULL),
    __ATTR(nfc_enable_status, 0664, nfc_enable_status_show, nfc_enable_status_store),
    //__ATTR(nfc_check_lcd_status, 0444, nfc_check_lcd_status_show, NULL),
    __ATTR(nfc_card_num, 0444, nfc_card_num_show, NULL),
    __ATTR(nfc_chip_type, 0444, nfc_chip_type_show, NULL),
    __ATTR(nfc_fw_version, 0444, nfc_fw_version_show, NULL),
    __ATTR(nfcservice_lock, 0664, nfcservice_lock_show, nfcservice_lock_store),
    __ATTR(nfc_svdd_sw, 0664,nfc_svdd_sw_show, nfc_svdd_sw_store),
    __ATTR(nfc_close_type, 0664, nfc_close_type_show, nfc_close_type_store),
    __ATTR(nfc_single_channel, 0444, nfc_single_channel_show, NULL),
};
static int create_sysfs_interfaces(struct device *dev)
{
    int i;
    for (i = 0; i < ARRAY_SIZE(pn547_attr); i++) {
        if (device_create_file(dev, pn547_attr + i)) {
            goto error;
        }
    }

    return 0;
error:
    for ( ; i >= 0; i--) {
        device_remove_file(dev, pn547_attr + i);
    }

    hwlog_err("%s:pn547 unable to create sysfs interface.\n", __func__ );
    return -1;
}

static int remove_sysfs_interfaces(struct device *dev)
{
    int i;
    for (i = 0; i < ARRAY_SIZE(pn547_attr); i++) {
        device_remove_file(dev, pn547_attr + i);
    }

    return 0;
}
static int nfc_ven_low_beforepwd(struct notifier_block *this, unsigned int code,
                                                                void *unused)
{
    int retval = 0;

    hwlog_info("[%s]: enter!\n", __func__);

    if (g_nfc_svdd_sw == true)
    {
        hwlog_info("[%s]: %s powerdown with current sim_switch value: %d !\n", __func__, g_nfc_chip_type, nfcdev->sim_switch);
        if (nfcdev->sim_switch ==  SIM2_CARD)
        {
            pmu0_svdd_sel_off();
        }
    }

    return retval;
}

static struct notifier_block nfc_ven_low_notifier = {
    .notifier_call = nfc_ven_low_beforepwd,
};

static int check_pn547(struct i2c_client *client, struct  pn547_dev *pdev)
{
    int ret = -1;
    int count = 0;
    const char host_to_pn547[1] = {0x20};
    const char firm_dload_cmd[8]={0x00, 0x04, 0xD0, 0x09, 0x00, 0x00, 0xB1, 0x84};

    ret = pn547_bulk_enable(pdev);
    if (ret < 0) {
        hwlog_err("%s: regulator_enable failed, ret:%d\n", __func__, ret);
        return ret;
    }

    msleep(10);
    ret = pn547_bulk_disable(pdev);
    if (ret < 0) {
        hwlog_err("%s: regulator_disable failed, ret:%d\n", __func__, ret);
        return ret;
    }

    msleep(10);
    ret = pn547_bulk_enable(pdev);
    if (ret < 0) {
        hwlog_err("%s: regulator_enable failed, ret:%d\n", __func__, ret);
        return ret;
    }
    msleep(10);

    do{
        ret = i2c_master_send(client,  host_to_pn547, sizeof(host_to_pn547));
        if (ret < 0) {
            hwlog_err("%s:pn547_i2c_write failed and ret = %d,at %d times\n", __func__,ret,count);
        } else {
            hwlog_info("%s:pn547_i2c_write success and ret = %d,at %d times\n",__func__,ret,count);
            msleep(10);
            ret = pn547_enable_nfc(pdev);
            if (ret < 0) {
                hwlog_err("%s: pn547_enable_nfc exit i2c check failed, ret:%d\n", __func__, ret);
                return ret;
            }
            return ret;
        }
        count++;
        msleep(10);
    }while(count <NFC_TRY_NUM);

    for (count = 0; count < NFC_TRY_NUM;count++)
    {
        nfc_gpio_set_value(pdev->firm_gpio, 1);
        ret = pn547_enable_nfc(pdev);
        if (ret < 0) {
            hwlog_err("%s: pn547_enable_nfc enter firmware failed, ret:%d\n", __func__, ret);
            return ret;
        }

        ret = i2c_master_send(client,  firm_dload_cmd, sizeof(firm_dload_cmd));
        if (ret < 0) {
            hwlog_info("%s:pn547_i2c_write download cmd failed:%d, ret = %d\n", __func__, count, ret);
            nfc_gpio_set_value(pdev->firm_gpio, 0);
            continue;
        }

        nfc_gpio_set_value(pdev->firm_gpio, 0);
        ret = pn547_enable_nfc(pdev);
        if (ret < 0) {
            hwlog_err("%s: pn547_enable_nfc exit firmware failed, ret:%d\n", __func__, ret);
            return ret;
        }
        break;
    }
    return ret;
}
static int pn547_get_resource(struct  pn547_dev *pdev,  struct i2c_client *client)
{
    int ret;

    pdev->irq_gpio = of_get_named_gpio(client->dev.of_node, "pn547,irq", 0);
    hwlog_err("irq_gpio:%u\n", pdev->irq_gpio);
    if (!gpio_is_valid(pdev->irq_gpio)) {
        hwlog_err("failed to get irq!\n");
        return -ENODEV;
    }
    pdev->firm_gpio = of_get_named_gpio(client->dev.of_node, "pn547,dload", 0);
    hwlog_err("firm_gpio:%u\n", pdev->firm_gpio);
    if (!gpio_is_valid(pdev->firm_gpio)) {
        hwlog_err("failed to get firm!\n");
        return -ENODEV;
    }

//#ifndef CONFIG_V8R2_NFC
    pdev->pctrl = devm_pinctrl_get(&client->dev);
    if (IS_ERR(pdev->pctrl)) {
        pdev->pctrl = NULL;
        hwlog_err("failed to get clk pin!\n");
        return -ENODEV;
    }

    //fix udp bug
    pdev->pins_default = pinctrl_lookup_state(pdev->pctrl, "default");
    pdev->pins_idle = pinctrl_lookup_state(pdev->pctrl, "idle");
    ret = pinctrl_select_state(pdev->pctrl, pdev->pins_default);
    if (ret < 0){
        hwlog_err("%s: unapply new state!\n", __func__);
        return -ENODEV;
    }
//#endif

     if (NFC_CLK_SRC_PMU == g_nfc_clk_src) {
         /*use pmu wifibt clk*/
         hwlog_info("%s: config pmu clock in register!\n", __func__);

         /*Register 0x0c5 bit5 = 0 -- not disable wifi_clk_en gpio to control wifi_clk output*/
         ret = hisi_pmic_reg_read(0xc5);
         ret &= (~0x20);
         hisi_pmic_reg_write(0xc5, ret);

         /*Register 0x10A bit2 = 0 -- disable internal register to control wifi_clk output*/
         ret = hisi_pmic_reg_read(0x10A);
         ret &= (~0x4);
         hisi_pmic_reg_write(0x10A, ret);

         /*Register 0x10C bit0 = 0 -- sine wave(default); 1 --  square wave*/
         ret = hisi_pmic_reg_read(0x10C);
         ret |= 0x01;
         hisi_pmic_reg_write(0x10C, ret);

         /*Register 0x109 bit5:bit4 = drive-strength
                                      00 --3pF//100K;
                                      01 --10pF//100K;
                                      10 --16pF//100K;
                                      11 --25pF//100K */
         ret = hisi_pmic_reg_read(0x109);
         ret |= 0x30;
         hisi_pmic_reg_write(0x109, ret);
     } else {
         /*use default soc clk*/
         pdev->nfc_clk = devm_clk_get(&client->dev, NFC_CLK_PIN);
         if (IS_ERR(pdev->nfc_clk )) {
             hwlog_err("failed to get clk out\n");
             return -ENODEV;
         } else {
             ret = clk_set_rate(pdev->nfc_clk , DEFAULT_NFC_CLK_RATE);
             if (ret < 0) {
                 return -EINVAL;
             }
         }
     }

#ifdef CONFIG_V8R2_NFC
    pdev->ven_gpio = of_get_named_gpio(client->dev.of_node, "pn547,ven", 0);
    if (pdev->ven_gpio < 0) {
        hwlog_err( "failed to get \"huawei,nfc_ven\"\n");
        return -ENODEV;
        }
#else
    switch (g_nfc_on_type)
    {
        case NFC_ON_BY_GPIO:
        {
            hwlog_info("Nfc on by gpio!\n");
            pdev->ven_gpio = of_get_named_gpio(client->dev.of_node, "pn547,ven", 0);
            if (pdev->ven_gpio < 0) {
                hwlog_err( "failed to get \"huawei,nfc_ven\"\n");
                return -ENODEV;
            }
        }
        break;

        case NFC_ON_BY_REGULATOR_BULK:
        {
            hwlog_info("Nfc on by regulator bulk!\n");
            pdev->ven_felica.supply =  "pn547ven";
            ret = devm_regulator_bulk_get(&client->dev, 1, &(pdev->ven_felica));
            if (ret) {
                hwlog_err("failed to get ven felica!\n");
                if (pdev->nfc_clk) {
                    clk_put(pdev->nfc_clk);
                    pdev->nfc_clk = NULL;
                }
                return -ENODEV;
            }
        }
        break;

        case NFC_ON_BY_HISI_PMIC:
        {
            hwlog_info("Nfc on by hisi pmic!\n");
        }
        break;

        default:
        {
            hwlog_info("Error nfc on type!\n");
        }
        break;
    }
#endif

    return 0;
}

static struct of_device_id pn547_i2c_dt_ids[] = {
    {.compatible = "hisilicon,pn547_nfc" },
    {}
};

static bool get_detect_se(void)
{
    int ret = -1;

    memset(g_nfc_detect_se_str, 0, MAX_DETECT_SE_SIZE);
    ret = nfc_get_dts_config_string("detect_se","detect_se", 
        g_nfc_detect_se_str, sizeof(g_nfc_detect_se_str));

    if(ret != 0)
    {
        memset(g_nfc_detect_se_str, 0, MAX_DETECT_SE_SIZE);
        hwlog_err("%s: can't get nfc detect_se\n", __func__);
        return false;
    }else{
        hwlog_info("%s: g_nfc_detect_se_str:%s\n", __func__, g_nfc_detect_se_str);
    }

    if (!strcasecmp(g_nfc_detect_se_str, "true"))
        return true;
    return false;
}

static int detect_se(struct i2c_client *client, struct  pn547_dev *pdev)
{
    int ret=-1;

    unsigned char recvBuf[40];
    const  char send_reset[] = {0x20,0x00,0x01,0x01};
    const  char init_cmd[] = {0x20,0x01,0x00};

    const  char read_config[] = {0x2F,0x02,0x00};
    const  char read_config_eSE[] = {0x2F,0x3E,0x01,0x01};              //eSE
    pdev->sim_status = 0;

    /*hardware reset*/
    /* power on */
    nfc_gpio_set_value(pdev->firm_gpio, 0);
    if (pn547_enable_nfc(pdev)){
        hwlog_err("%s: out reset chip fail\n", __func__);
    }

    /*write CORE_RESET_CMD*/
    ret=pn547_i2c_write(pdev,send_reset,sizeof(send_reset));
    if(ret < 0)
    {
        hwlog_err("%s: pn547_i2c_write failed, ret:%d\n", __func__, ret);
        goto failed;
    }
    /*read response*/
    ret=pn547_i2c_read(pdev,recvBuf,_read_sample_test_size);
    if(ret < 0)
    {
        hwlog_err("%s: pn547_i2c_read failed, ret:%d\n", __func__, ret);
        goto failed;
    }

    udelay(500);
    /*write CORE_INIT_CMD*/
    ret=pn547_i2c_write(pdev,init_cmd,sizeof(init_cmd));
    if(ret < 0)
    {
        hwlog_err("%s: pn547_i2c_write failed, ret:%d\n", __func__, ret);
        goto failed;
    }
    /*read response*/
    ret=pn547_i2c_read(pdev,recvBuf,_read_sample_test_size);
    if(ret < 0)
    {
        hwlog_err("%s: pn547_i2c_read failed, ret:%d\n", __func__, ret);
        goto failed;
    }

    udelay(500);
    /*write NCI_PROPRIETARY_ACT_CMD*/
    ret=pn547_i2c_write(pdev,read_config,sizeof(read_config));
    if(ret < 0)
    {
        hwlog_err("%s: pn547_i2c_write failed, ret:%d\n", __func__, ret);
        goto failed;
    }
    /*read response*/
    ret=pn547_i2c_read(pdev,recvBuf,_read_sample_test_size);
    if(ret < 0)
    {
        hwlog_err("%s: pn547_i2c_read failed, ret:%d\n", __func__, ret);
        goto failed;
    }

    udelay(500);

    /*write TEST_SWP_CMD eSE*/
    ret=pn547_i2c_write(pdev,read_config_eSE,sizeof(read_config_eSE));
    if(ret < 0)
    {
        hwlog_err("%s: pn547_i2c_write failed, ret:%d\n", __func__, ret);
        goto failed;
    }
    /*read response*/
    ret=pn547_i2c_read(pdev,recvBuf,_read_sample_test_size);
    if(ret < 0)
    {
        hwlog_err("%s: pn547_i2c_read failed, ret:%d\n", __func__, ret);
        goto failed;
    }

    mdelay(10);
    /*read notification*/
    ret=pn547_i2c_read(pdev,recvBuf,_read_sample_test_size);
    if(ret < 0)
    {
        hwlog_err("%s: pn547_i2c_read failed, ret:%d\n", __func__, ret);
        goto failed;
    }

    if(recvBuf[0] == 0x6F && recvBuf[1] == 0x3E && recvBuf[3] == 0x00)
    {
        hwlog_err("%s: find se, ret:%d\n", __func__, ret);
        g_nfc_detect_se = true;
    }

    if (pn547_enable_nfc(pdev)){
        hwlog_err("%s: out reset chip fail\n", __func__);
    }

    return ret;
failed:
    return ret;

}

static int pn547_probe(struct i2c_client *client,
        const struct i2c_device_id *id)
{
    int ret;
    struct pn547_dev *pn547_dev;
    char *nfc_clk_status = NULL;
#ifdef CONFIG_V8R2_NFC
    unsigned char clk_control_value = 0;
    unsigned int flags;
#endif

    hwlog_info("[%s,%d]: probe start !\n", __FUNCTION__, __LINE__);
    if (!of_match_device(pn547_i2c_dt_ids, &client->dev)) {
        hwlog_err("[%s,%d]: pn547 NFC match fail !\n", __FUNCTION__, __LINE__);
        return -ENODEV;
    }
    if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
        hwlog_err("[%s,%d]: need I2C_FUNC_I2C\n", __func__, __LINE__);
        return  -ENODEV;
    }

    if (!nfc_dclient) {
        nfc_dclient = dsm_register_client(&dsm_nfc);
    }

    get_ext_gpio_type();
    get_nfc_on_type();
    get_nfc_svdd_sw();
    if (g_nfc_svdd_sw == true)
    {
        pmu0_svdd_sel_on();
    }

    ret=of_property_read_string(client->dev.of_node, "clk_status", (const char **)&nfc_clk_status);
    if (ret) {
        hwlog_err("[%s,%d]:read clk status fail\n",__func__, __LINE__);
        return -ENODEV;
    } else if (!strcmp(nfc_clk_status, "pmu")) {
        hwlog_info("[%s,%d]:clock source is pmu\n",__func__, __LINE__);
        g_nfc_clk_src = NFC_CLK_SRC_PMU;
    } else {
        hwlog_info("[%s,%d]:clock source is cpu by default\n",__func__, __LINE__);
        g_nfc_clk_src = NFC_CLK_SRC_CPU;
    }

    ret = create_sysfs_interfaces(&client->dev);
    if (ret < 0) {
        hwlog_err("[%s,%d]:Failed to create_sysfs_interfaces\n", __func__, __LINE__);
        return -ENODEV;
    }
    ret = sysfs_create_link(NULL,&client->dev.kobj,"nfc");
    if(ret < 0) {
        hwlog_err("[%s,%d]:Failed to sysfs_create_link\n", __func__, __LINE__);
        return -ENODEV;
    }

    pn547_dev = kzalloc(sizeof(*pn547_dev), GFP_KERNEL);
    if (pn547_dev == NULL) {
        hwlog_err("[%s,%d]:failed to allocate memory for module data\n", __func__, __LINE__);
        ret = -ENOMEM;
        goto err_exit;
    }
    /* get clk ,gpio,supply resource from dts*/
    ret = pn547_get_resource(pn547_dev, client);
    if (ret < 0) {
        hwlog_err("[%s,%d]: pn547 probe get resource failed \n",__func__, __LINE__);
        goto err_pn547_get_resource;
    }

    ret = gpio_request(pn547_dev->firm_gpio,NULL);
    if (ret < 0) {
        hwlog_err("[%s,%d]: gpio_request failed, firm_gpio:%u, ret:%d.\n", __func__, __LINE__,
            pn547_dev->firm_gpio, ret);
        goto err_firm_gpio_request;
    }

    ret = gpio_direction_output(pn547_dev->firm_gpio,0);
    if ( ret < 0 )
    {
        hwlog_err("[%s,%d]: Fail set gpio as output, firm_gpio:%d.\n", __func__, __LINE__,
            pn547_dev->firm_gpio);
        goto err_ven_gpio_request;
    }

#ifdef CONFIG_V8R2_NFC
    ret = gpio_request(pn547_dev->ven_gpio,NULL);
    if (ret < 0) {
        hwlog_err("%s: gpio_request failed, ret:%d.\n", __func__,
            pn547_dev->ven_gpio);
        goto err_ven_gpio_request;
    }

    ret = gpio_direction_output(pn547_dev->ven_gpio,0);
    if ( ret < 0 )
    {
        hwlog_err("%s: Fail set gpio as output, ven_gpio:%d.\n", __func__,
        pn547_dev->ven_gpio);
        goto err_check_pn547;
    }
#endif
    if (NFC_ON_BY_GPIO == g_nfc_on_type){
        ret = gpio_request(pn547_dev->ven_gpio,NULL);
        if (ret < 0) {
            hwlog_err("%s: gpio_request failed, ret:%d.\n", __func__,
                    pn547_dev->ven_gpio);
            goto err_ven_gpio_request;
        }

        ret = gpio_direction_output(pn547_dev->ven_gpio,0);
        if ( ret < 0 )
        {
            hwlog_err("%s: Fail set gpio as output, ven_gpio:%d.\n", __func__,
                    pn547_dev->ven_gpio);
            goto err_check_pn547;
        }
    }

    /*using i2c to find nfc device */
    ret = check_pn547(client, pn547_dev);
    if(ret < 0){
        hwlog_err("[%s,%d]: pn547 probe failed \n",__func__, __LINE__);
        goto err_check_pn547;
    }

    ret = pn547_bulk_disable(pn547_dev);
    if (ret < 0) {
        hwlog_err("[%s,%d]:pn547_bulk_disable failed; ret:%d\n", __func__, __LINE__, ret);
    }

    pn547_dev->client   = client;
    /* init mutex and queues */
    init_waitqueue_head(&pn547_dev->read_wq);
    mutex_init(&pn547_dev->read_mutex);
    spin_lock_init(&pn547_dev->irq_enabled_lock);

    mutex_init(&pn547_dev->irq_mutex_lock);
    
    /* Initialize wakelock*/
    wake_lock_init(&wlock_read, WAKE_LOCK_SUSPEND, "nfc_read");
    /*register pn544 char device*/
    pn547_dev->pn547_device.minor = MISC_DYNAMIC_MINOR;
    pn547_dev->pn547_device.name = "pn544";
    pn547_dev->pn547_device.fops = &pn547_dev_fops;
    ret = misc_register(&pn547_dev->pn547_device);
    if (ret) {
        hwlog_err("[%s,%d]: misc_register failed\n", __func__, __LINE__);
        goto err_misc_register;
    }

    /* request irq.  the irq is set whenever the chip has data available
      * for reading.  it is cleared when all data has been read.
      */
    pn547_dev->irq_enabled = true;
    ret = gpio_request(pn547_dev->irq_gpio,NULL);
    if (ret < 0) {
        hwlog_err("[%s,%d]: gpio_request failed, ret:%d.\n", __func__, __LINE__,
            pn547_dev->irq_gpio);
        goto err_misc_register;
    }
    ret = gpio_direction_input(pn547_dev->irq_gpio);
    if ( ret < 0 )
    {
        hwlog_err("[%s,%d]: Fail set gpio as input, irq_gpio:%d.\n", __func__, __LINE__,
            pn547_dev->irq_gpio);
        goto err_request_irq_failed;
    }
    if (g_nfc_ext_gpio){
        client->irq = gpio_to_irq(pn547_dev->irq_gpio);
        ret = request_threaded_irq(client->irq, NULL,
                pn547_dev_irq_handler,
                IRQF_TRIGGER_HIGH | IRQF_NO_SUSPEND, client->name, pn547_dev);
        if (0 > ret){
            hwlog_err("[%s,%d]:ext gpio request_irq client->irq=%d failed,ret=%d\n", __func__, __LINE__, client->irq, ret);
            goto err_request_irq_failed;
        }
        hwlog_err("[%s,%d]:request_irq client->irq=%d success,ret=%d\n", __func__, __LINE__, client->irq, ret);
        pn547_disable_irq_for_ext_gpio(pn547_dev);
    }else{
        client->irq = gpio_to_irq(pn547_dev->irq_gpio);
        ret = request_irq(client->irq, pn547_dev_irq_handler,
                IRQF_TRIGGER_HIGH | IRQF_NO_SUSPEND, client->name, pn547_dev);
        if (ret) {
            hwlog_err("[%s,%d]:soc gpio request_irq client->irq=%d failed,ret=%d\n", __func__, __LINE__, client->irq, ret);
            goto err_request_irq_failed;
        }
        pn547_disable_irq(pn547_dev);
    }
    /*sim_select = 1,UICC select*/
    pn547_dev->sim_switch = CARD1_SELECT;
    pn547_dev->sim_status = CARD_UNKNOWN;

    pn547_dev->enable_status = ENABLE_START;
    /* set device data to client devices*/
    i2c_set_clientdata(client, pn547_dev);

    nfcdev = pn547_dev;
    /*notifier for supply shutdown*/
    register_reboot_notifier(&nfc_ven_low_notifier);
    /*enbale the 19.2M clk*/
#if 0
    ret = clk_prepare_enable(pn547_dev->nfc_clk);
    if (ret) {
        hwlog_err("[%s,%d]:Enable NFC clk failed, ret=%d\n", __func__, __LINE__, ret);
        if (!dsm_client_ocuppy(nfc_dclient)) {
            dsm_client_record(nfc_dclient,"Enable NFC clk failed, ret=%d.\n",ret);
            dsm_client_notify(nfc_dclient, DSM_NFC_CLK_ENABLE_ERROR_NO);
        }
        goto err_request_irq_failed;
    }
#endif
/*#ifdef CONFIG_V8R2_NFC
    spin_lock_init(&g_alel21_lock);
    spin_lock_irqsave(&g_alel21_lock, flags);
    clk_control_value = hi6xxx_pmic_reg_read(SOC_SMART_CLK_TOP3_ADDR(0));
    clk_control_value = (clk_control_value & 0xf3) | 0x04;
    hi6xxx_pmic_reg_write(SOC_SMART_CLK_TOP3_ADDR(0),clk_control_value);
    spin_unlock_irqrestore(&g_alel21_lock, flags);
#endif*/
#ifdef CONFIG_HUAWEI_HW_DEV_DCT
    /* detect current device successful, set the flag as present */
    set_hw_dev_flag(DEV_I2C_NFC);
#endif

    set_nfc_nxp_config_name();
    set_nfc_brcm_config_name();
    set_nfc_chip_type_name();
    set_nfc_single_channel();
    set_nfc_card_num();

    //lcd_status = read_lcd_type();
    if (get_detect_se())
        detect_se(client, pn547_dev);
    hwlog_info("[%s,%d]: probe end !\n", __FUNCTION__, __LINE__);

    return 0;

err_request_irq_failed:
    gpio_free(pn547_dev->irq_gpio);
err_misc_register:
    misc_deregister(&pn547_dev->pn547_device);
    wake_lock_destroy(&wlock_read);
    mutex_destroy(&pn547_dev->read_mutex);
err_check_pn547:
#ifdef CONFIG_V8R2_NFC
    gpio_free(pn547_dev->ven_gpio);
#endif
    if (NFC_ON_BY_GPIO == g_nfc_on_type)
        gpio_free(pn547_dev->ven_gpio);
err_ven_gpio_request:
    gpio_free(pn547_dev->firm_gpio);
err_firm_gpio_request:
    if(pn547_dev->nfc_clk)
    {
        clk_put(pn547_dev->nfc_clk);
        pn547_dev->nfc_clk = NULL;
//#ifndef CONFIG_V8R2_NFC
        ret = pinctrl_select_state(pn547_dev->pctrl, pn547_dev->pins_idle);
        if (ret < 0){
            hwlog_err("[%s,%d]:unapply new state!\n", __func__, __LINE__);
        }
//#endif
    }
err_pn547_get_resource:
    kfree(pn547_dev);
err_exit:
    remove_sysfs_interfaces(&client->dev);
    return ret;
}

static int pn547_remove(struct i2c_client *client)
{
    struct pn547_dev *pn547_dev;
    int ret = 0;

    hwlog_info("[%s]: %s removed !\n", __func__, g_nfc_chip_type);

    unregister_reboot_notifier(&nfc_ven_low_notifier);
    pn547_dev = i2c_get_clientdata(client);
    if(pn547_dev == NULL)
    {
        hwlog_err("%s:  pn547_dev == NULL!\n", __func__);
        goto out;
    }
    free_irq(client->irq, pn547_dev);
    misc_deregister(&pn547_dev->pn547_device);
    wake_lock_destroy(&wlock_read);
    mutex_destroy(&pn547_dev->read_mutex);
    gpio_free(pn547_dev->irq_gpio);
    gpio_free(pn547_dev->firm_gpio);
    remove_sysfs_interfaces(&client->dev);
    if(pn547_dev->nfc_clk)
    {
        clk_put(pn547_dev->nfc_clk);
        pn547_dev->nfc_clk = NULL;
//#ifndef CONFIG_V8R2_NFC
        ret = pinctrl_select_state(pn547_dev->pctrl, pn547_dev->pins_idle);
        if (ret < 0){
            hwlog_err("%s: unapply new state!\n", __func__);
        }
//#endif
    }
    kfree(pn547_dev);
out:
    return 0;
}

static const struct i2c_device_id pn547_id[] = {
    { "pn547", 0 },
    { }
};

#ifdef CONFIG_PM
static int pn547_suspend(struct i2c_client *client, pm_message_t mesg)
{
//  struct pn547_dev *pn547_dev;
//  int ret = 0;

    hwlog_info("[%s] +\n", __func__);

#if 0
    pn547_dev = i2c_get_clientdata(client);

    clk_disable_unprepare(pn547_dev->nfc_clk);
    ret = pinctrl_select_state(pn547_dev->pctrl, pn547_dev->pins_idle);
    if (ret < 0){
        hwlog_err("%s: unapply new state!\n", __func__);
    }
#endif
    hwlog_info("[%s] -\n", __func__);

    return 0;
}
static int pn547_resume(struct i2c_client *client)
{
//  int ret = -1;
//  struct pn547_dev *pn547_dev;

    hwlog_info("[%s] +\n", __func__);

#if 0
    pn547_dev = i2c_get_clientdata(client);

    ret = pinctrl_select_state(pn547_dev->pctrl, pn547_dev->pins_default);
    if (ret < 0){
        hwlog_err("%s: unapply new state!\n", __func__);
    }

    ret = clk_prepare_enable(pn547_dev->nfc_clk);
    if (ret < 0) {
        hwlog_info("%s: clk_enable failed, ret:%d\n", __func__, ret);
    }
#endif

    hwlog_info("[%s] -\n", __func__);

    return 0;
}
#else
#define pn547_suspend      NULL
#define pn547_resume       NULL
#endif /* CONFIG_PM */

MODULE_DEVICE_TABLE(of, pn547_i2c_dt_ids);
static struct i2c_driver pn547_driver = {
    .id_table     = pn547_id,
    .probe        = pn547_probe,
    .remove     = pn547_remove,
    .suspend    = pn547_suspend,
    .resume     = pn547_resume,
    .driver        = {
        .owner   = THIS_MODULE,
        .name    = "pn544",
        .of_match_table = of_match_ptr(pn547_i2c_dt_ids),
    },
};
/*
 * module load/unload record keeping
 */
module_i2c_driver(pn547_driver);
MODULE_AUTHOR("Sylvain Fonteneau");
MODULE_DESCRIPTION("NFC pn547 driver");
MODULE_LICENSE("GPL");
