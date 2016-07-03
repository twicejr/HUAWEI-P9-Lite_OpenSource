

/*****************************************************************************
  1 Include Head file
*****************************************************************************/
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include "plat_debug.h"
#include "bfgx_low_power.h"
#include "plat_pm.h"
#include "bfgx_exception_rst.h"
#include "oneimage.h"
#include "oal_kernel_file.h"
#include "oal_sdio_host_if.h"
#include "plat_pm_wlan.h"
#include "hisi_ini.h"
#include "plat_uart.h"

/*****************************************************************************
  2 Define global variable
*****************************************************************************/
struct kobject *g_sysfs_hi110x_bfgx    = NULL;
struct kobject *g_sysfs_hisi_pmdbg     = NULL;

#ifdef PLATFORM_DEBUG_ENABLE
struct kobject *g_sysfs_hi110x_debug   = NULL;
int32 g_uart_rx_dump  = UART_DUMP_CLOSE;
#endif

#ifdef HAVE_HISI_NFC
struct kobject *g_sysfs_hisi_nfc = NULL;
#endif

int32 g_plat_loglevel = PLAT_LOG_INFO;
int32 g_bug_on_enable = BUG_ON_DISABLE;

extern int isAsic(void);

/*****************************************************************************
  3 Function implement
*****************************************************************************/

STATIC ssize_t show_wifi_pmdbg(struct device *dev, struct kobj_attribute *attr, int8 *buf)
{
   struct wlan_pm_s *pst_wlan_pm = wlan_pm_get_drv();
   oal_int32         ret = 0;

   if (NULL == buf)
   {
      PS_PRINT_ERR("buf is NULL\n");
      return -FAILURE;
   }

#ifdef PLATFORM_DEBUG_ENABLE
   ret += snprintf(buf + ret , PAGE_SIZE - ret, "wifi_pm_debug usage: \n"
                       " 1:dump host info 2:dump device info\n"
                       " 3:open wifi      4:close wifi \n"
                       " 5:enable pm      6:disable pm \n");
#else
  ret += snprintf(buf + ret , PAGE_SIZE - ret, "wifi_pm_debug usage: \n"
                       " 1:dump host info 2:dump device info\n");
#endif

   ret += wlan_pm_host_info_print(pst_wlan_pm, buf + ret, PAGE_SIZE - ret);

   return ret;
}

STATIC ssize_t store_wifi_pmdbg(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count)
{
    struct wlan_pm_s *pst_wlan_pm = wlan_pm_get_drv();
    int input = 0;

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    input = oal_atoi(buf);

    if (NULL == pst_wlan_pm)
    {
        OAL_IO_PRINT("pm_data is NULL!\n");
        return -FAILURE;
    }

    switch(input)
    {
       case 1:
        wlan_pm_dump_host_info();
       break;
       case 2:
        wlan_pm_dump_device_info();
       break;
#ifdef PLATFORM_DEBUG_ENABLE
       case 3:
        wlan_pm_open();
       break;
       case 4:
        wlan_pm_close();
       break;
       case 5:
        wlan_pm_enable();
       break;
       case 6:
        wlan_pm_disable();
       break;
#endif
       default:
       break;
    }

    return count;
}

STATIC ssize_t show_bfgx_pmdbg(struct device *dev, struct kobj_attribute *attr, int8 *buf)
{
    PS_PRINT_INFO("%s\n", __func__);

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    return snprintf(buf, SNPRINT_LIMIT_TO_KERNEL, "cmd       func     \n"
                        "  1  plat pm enable\n  2  plat pm disable\n"
                        "  3   bt  pm enable\n  4   bt  pm disable\n"
                        "  5  gnss pm enable\n  6  gnss pm disable\n"
                        "  7   nfc pm enable\n  8   nfc pm disable\n"
                        "  9  pm ctrl enable\n  10 pm ctrl disable\n");
}

STATIC ssize_t store_bfgx_pmdbg(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count)
{
    struct pm_drv_data *pm_data = NULL;
    int32  cmd = 0;

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    cmd = simple_strtol(buf, NULL, 10);
    PS_PRINT_INFO("cmd:%d\n", cmd);

    pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    switch (cmd)
    {
        case 1: /* disable plat lowpower function */
            pm_data->bfgx_lowpower_enable = BFGX_PM_ENABLE;
            break;
        case 2: /* enable plat lowpower function */
            pm_data->bfgx_lowpower_enable = BFGX_PM_DISABLE;
            break;
        case 3: /* enable bt lowpower function */
            pm_data->bfgx_bt_lowpower_enable = BFGX_PM_ENABLE;
            break;
        case 4: /* disable bt lowpower function */
            pm_data->bfgx_bt_lowpower_enable = BFGX_PM_DISABLE;
            break;
        case 5: /* enable gnss lowpower function */
            pm_data->bfgx_gnss_lowpower_enable = BFGX_PM_ENABLE;
            break;
        case 6: /* disable gnss lowpower function */
            pm_data->bfgx_gnss_lowpower_enable = BFGX_PM_DISABLE;
            break;
        case 7: /* enable nfc lowpower function */
            pm_data->bfgx_nfc_lowpower_enable = BFGX_PM_ENABLE;
            break;
        case 8: /* disable nfc lowpower function */
            pm_data->bfgx_nfc_lowpower_enable = BFGX_PM_DISABLE;
            break;
        case 9:
            pm_data->bfgx_pm_ctrl_enable = BFGX_PM_ENABLE;
            break;
        case 10:
            pm_data->bfgx_pm_ctrl_enable = BFGX_PM_DISABLE;
            break;

        default:
            PS_PRINT_ERR("unknown cmd %d\n", cmd);
            break;
    }

    return count;
}

STATIC struct kobj_attribute wifi_pmdbg =
__ATTR(wifi_pm, 0644, (void *)show_wifi_pmdbg, (void *)store_wifi_pmdbg);

STATIC struct kobj_attribute bfgx_pmdbg =
__ATTR(bfgx_pm, 0644, (void *)show_bfgx_pmdbg, (void *)store_bfgx_pmdbg);

STATIC struct attribute *pmdbg_attrs[] = {
        &wifi_pmdbg.attr,
        &bfgx_pmdbg.attr,
        NULL,
};

STATIC struct attribute_group pmdbg_attr_grp = {
    .attrs = pmdbg_attrs,
};

/* functions called from subsystems */
/* called by octty from hal to decide open or close uart */
STATIC ssize_t show_install(struct device *dev, struct kobj_attribute *attr, int8 *buf)
{
    struct ps_plat_s *pm_data = NULL;

    PS_PRINT_FUNCTION_NAME;

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    pm_data = dev_get_drvdata(&hw_ps_device->dev);
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    return snprintf(buf, SNPRINT_LIMIT_TO_KERNEL, "%d\n", pm_data->ldisc_install);
}

/* read by octty from hal to decide open which uart */
STATIC ssize_t show_dev_name(struct device *dev, struct kobj_attribute *attr, int8 *buf)
{
    struct ps_plat_s *pm_data = NULL;

    PS_PRINT_FUNCTION_NAME;

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    pm_data = dev_get_drvdata(&hw_ps_device->dev);
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    return snprintf(buf, SNPRINT_LIMIT_TO_KERNEL, "%s\n", pm_data->dev_name);
}

/* read by octty from hal to decide what baud rate to use */
STATIC ssize_t show_baud_rate(struct device *dev, struct kobj_attribute *attr, int8 *buf)
{
    struct ps_plat_s *pm_data = NULL;

    PS_PRINT_FUNCTION_NAME;

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    pm_data = dev_get_drvdata(&hw_ps_device->dev);
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    return snprintf(buf, SNPRINT_LIMIT_TO_KERNEL, "%ld\n", pm_data->baud_rate);
}

/* read by octty from hal to decide whether or not use flow cntrl */
STATIC ssize_t show_flow_cntrl(struct device *dev, struct kobj_attribute *attr, int8 *buf)
{
    struct ps_plat_s *pm_data = NULL;

    PS_PRINT_FUNCTION_NAME;

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    pm_data = dev_get_drvdata(&hw_ps_device->dev);
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    return snprintf(buf, SNPRINT_LIMIT_TO_KERNEL, "%d\n", pm_data->flow_cntrl);
}

/* show curr bfgx proto yes or not opened state */
STATIC ssize_t show_bfgx_active_state(struct device *dev, struct kobj_attribute *attr, int8 *buf)
{
    struct ps_plat_s *pm_data = NULL;
    uint8 bt_state   = POWER_STATE_SHUTDOWN;
    uint8 fm_state   = POWER_STATE_SHUTDOWN;
    uint8 gnss_state = POWER_STATE_SHUTDOWN;
#ifdef HAVE_HISI_IR
    uint8 ir_state   = POWER_STATE_SHUTDOWN;
#endif
#ifdef HAVE_HISI_NFC
    uint8 nfc_state  = POWER_STATE_SHUTDOWN;
#endif

    PS_PRINT_DBG("%s\n", __func__);

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    pm_data = dev_get_drvdata(&hw_ps_device->dev);
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -EFAULT;
    }

    if (true == atomic_read(&pm_data->core_data->bfgx_info[BFGX_BT].subsys_state))
    {
        bt_state = POWER_STATE_OPEN;
    }

    if (true == atomic_read(&pm_data->core_data->bfgx_info[BFGX_FM].subsys_state))
    {
        fm_state = POWER_STATE_OPEN;
    }

    if (true == atomic_read(&pm_data->core_data->bfgx_info[BFGX_GNSS].subsys_state))
    {
        gnss_state = POWER_STATE_OPEN;
    }

#ifdef HAVE_HISI_IR
    if (true == atomic_read(&pm_data->core_data->bfgx_info[BFGX_IR].subsys_state))
    {
        ir_state = POWER_STATE_OPEN;
    }
#endif

#ifdef HAVE_HISI_NFC
    if (true == atomic_read(&pm_data->core_data->bfgx_info[BFGX_NFC].subsys_state))
    {
        nfc_state = POWER_STATE_OPEN;
    }
#endif

#if ((defined HAVE_HISI_IR) && (defined HAVE_HISI_NFC))
    return snprintf(buf, SNPRINT_LIMIT_TO_KERNEL, "bt:%d; fm:%d; gnss:%d; ir:%d; nfc:%d;\n", bt_state, fm_state, gnss_state, ir_state, nfc_state);
#elif (!(defined HAVE_HISI_IR) && !(defined HAVE_HISI_NFC))
    return snprintf(buf, SNPRINT_LIMIT_TO_KERNEL, "bt:%d; fm:%d; gnss:%d;\n", bt_state, fm_state, gnss_state);
#elif ((defined HAVE_HISI_IR))
    return snprintf(buf, SNPRINT_LIMIT_TO_KERNEL, "bt:%d; fm:%d; gnss:%d; ir:%d;\n", bt_state, fm_state, gnss_state, ir_state);
#else
    return snprintf(buf, SNPRINT_LIMIT_TO_KERNEL, "bt:%d; fm:%d; gnss:%d; nfc:%d;\n", bt_state, fm_state, gnss_state, nfc_state);
#endif
}

STATIC ssize_t show_ini_file_name(struct device *dev, struct kobj_attribute *attr, char *buf)
{
    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    return snprintf(buf, INI_FILE_PATH_LEN, "%s", g_ini_file_name);
}

STATIC ssize_t show_country_code(struct device *dev, struct kobj_attribute *attr, char *buf)
{
    int8 *country_code = NULL;
    int ret;
    int8 ibuf[COUNTRY_CODE_LEN];

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    country_code = hwifi_get_country_code();
    if (strncmp(country_code, "99", strlen("99")) == 0)
    {
        ret = get_cust_conf_string(CUST_MODU_WIFI, "country_code", ibuf, sizeof(ibuf));
        if (ret == INI_SUCC)
        {
            strncpy(buf, ibuf, COUNTRY_CODE_LEN);
            buf[COUNTRY_CODE_LEN-1] = '\0';
            return strlen(buf);
        }
        else
        {
            PS_PRINT_ERR("get dts country_code error\n");
            return 0;
        }
    }
    else
    {
        return snprintf(buf, COUNTRY_CODE_LEN, "%s", country_code);
    }
}

STATIC ssize_t show_bfgx_exception_count(struct device *dev, struct kobj_attribute *attr, int8 *buf)
{
    struct st_exception_info *pst_exception_data = NULL;

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return 0;
    }

    PS_PRINT_DBG("exception debug: bfgx rst count is %d\n", pst_exception_data->bfgx_exception_cnt);
    return snprintf(buf, SNPRINT_LIMIT_TO_KERNEL, "%d\n", pst_exception_data->bfgx_exception_cnt);
}

STATIC ssize_t show_wifi_exception_count(struct device *dev, struct kobj_attribute *attr, int8 *buf)
{
    struct st_exception_info *pst_exception_data = NULL;

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return 0;
    }

    PS_PRINT_DBG("exception debug: wifi rst count is %d\n", pst_exception_data->wifi_exception_cnt);
    return snprintf(buf, SNPRINT_LIMIT_TO_KERNEL, "%d\n", pst_exception_data->wifi_exception_cnt);
}

STATIC ssize_t show_gnss_lowpower_state(struct device *dev, struct kobj_attribute *attr, char *buf, size_t count)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();

    PS_PRINT_DBG("show_gnss_lowpower_state!\n");

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    return snprintf(buf, SNPRINT_LIMIT_TO_KERNEL, "%d\n", atomic_read(&pm_data->gnss_sleep_flag));
}

STATIC ssize_t gnss_lowpower_state_store(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count)
{
    int flag = 0;
    struct pm_drv_data *pm_data = NULL;

    PS_PRINT_DBG("gnss_lowpower_state_store!\n");

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    flag = simple_strtol(buf, NULL, 10);
    /*gnss write the flag to request sleep*/
    if (1 == flag)
    {
        if (BFGX_PM_DISABLE == pm_data->bfgx_lowpower_enable)
        {
            PS_PRINT_WARNING("gnss low power disabled!\n");
            return -FAILURE;
        }
        if (BFGX_SLEEP == pm_data->ps_pm_interface->bfgx_dev_state_get())
        {
            PS_PRINT_WARNING("gnss proc: dev has been sleep, not allow dev slp\n");
            return -FAILURE;
        }
        /*if bt and fm are both shutdown ,we will pull down gpio directly*/
        PS_PRINT_DBG("flag = 1!\n");

        if (!timer_pending(&pm_data->bfg_timer))
        {
            PS_PRINT_SUC("gnss low power request sleep!\n");
            host_allow_bfg_sleep(pm_data->ps_pm_interface->ps_core_data);
        }

        /*set the flag to 1 means gnss request sleep*/
        atomic_set(&pm_data->gnss_sleep_flag, GNSS_AGREE_SLEEP);
    }
    else
    {
        PS_PRINT_ERR("invalid gnss lowpower data!\n");
        return -FAILURE;
    }

    return count;
}

STATIC ssize_t show_loglevel(struct device *dev, struct kobj_attribute *attr, int8 *buf)
{
    PS_PRINT_INFO("%s\n", __func__);

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    return snprintf(buf, SNPRINT_LIMIT_TO_KERNEL, "curr loglevel=%d, curr bug_on=%d\nalert:0\nerr:1\nwarning:2\nfunc|succ|info:3\ndebug:4\nbug_on enable:b\nbug_on disable:B\n", g_plat_loglevel, g_bug_on_enable);
}

STATIC ssize_t store_loglevel(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count)
{
    int32 loglevel = PLAT_LOG_INFO;

    PS_PRINT_INFO("%s\n", __func__);

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    /*bug on set*/
    if ('b' == *buf)
    {
        g_bug_on_enable = BUG_ON_ENABLE;
        PS_PRINT_INFO("BUG_ON enable sucess, g_bug_on_enable = %d\n", g_bug_on_enable);
        return count;
    }
    else if ('B' == *buf)
    {
        g_bug_on_enable = BUG_ON_DISABLE;
        PS_PRINT_INFO("BUG_ON disable sucess, g_bug_on_enable = %d\n", g_bug_on_enable);
        return count;
    }

    loglevel = simple_strtol(buf, NULL, 10);
    if(PLAT_LOG_ALERT > loglevel)
    {
        g_plat_loglevel = PLAT_LOG_ALERT;
    }
    else if(PLAT_LOG_DEBUG < loglevel)
    {
        g_plat_loglevel = PLAT_LOG_DEBUG;
    }
    else
    {
        g_plat_loglevel = loglevel;
    }

    return count;
}

#ifdef HAVE_HISI_IR
STATIC ssize_t show_ir_mode(struct device *dev, struct kobj_attribute *attr, int8 *buf)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();

    PS_PRINT_INFO("%s\n", __func__);

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    if (!isAsic())
    {
        PS_PRINT_ERR("HI1102 FPGA VERSION, ir contral gpio not exist\n");
        return -FAILURE;
    }

    return snprintf(buf, SNPRINT_LIMIT_TO_KERNEL, "%d\n", gpio_get_value(pm_data->board->bfgn_ir_ctrl));
}

STATIC ssize_t store_ir_mode(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count)
{
    int32 gpio_level;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    PS_PRINT_INFO("%s\n", __func__);

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    if (!isAsic())
    {
        PS_PRINT_ERR("HI1102 FPGA VERSION, ignore ir contral gpio\n");
        return count;
    }

    gpio_level = simple_strtol(buf, NULL, 10);
    if (GPIO_LOWLEVEL == gpio_level)
    {
        gpio_direction_output(pm_data->board->bfgn_ir_ctrl, GPIO_LOWLEVEL);
    }
    else if (GPIO_HIGHLEVEL == gpio_level)
    {
        gpio_direction_output(pm_data->board->bfgn_ir_ctrl, GPIO_HIGHLEVEL);
    }
    else
    {
        PS_PRINT_ERR("gpio level should be 0 or 1, cur value is [%d]\n", gpio_level);
    }

    return count;
}
#endif

STATIC ssize_t bfgx_sleep_state_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    return snprintf(buf, SNPRINT_LIMIT_TO_KERNEL, "%d\n", pm_data->bfgx_dev_state);
}

STATIC ssize_t bfgx_wkup_host_count_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    return snprintf(buf, SNPRINT_LIMIT_TO_KERNEL, "%d\n", pm_data->bfg_wakeup_host);
}

/* structures specific for sysfs entries */
STATIC struct kobj_attribute ldisc_install =
__ATTR(install, 0444, (void *)show_install, NULL);

STATIC struct kobj_attribute uart_dev_name =
__ATTR(dev_name, 0444, (void *)show_dev_name, NULL);

STATIC struct kobj_attribute uart_baud_rate =
__ATTR(baud_rate, 0444, (void *)show_baud_rate, NULL);

STATIC struct kobj_attribute uart_flow_cntrl =
__ATTR(flow_cntrl, 0444, (void *)show_flow_cntrl, NULL);

STATIC struct kobj_attribute bfgx_active_state =
__ATTR(bfgx_state, 0444, (void *)show_bfgx_active_state, NULL);

STATIC struct kobj_attribute ini_file_name =
__ATTR(ini_file_name, 0444, (void *)show_ini_file_name, NULL);

STATIC struct kobj_attribute country_code =
__ATTR(country_code, 0444, (void *)show_country_code, NULL);

STATIC struct kobj_attribute bfgx_rst_count =
__ATTR(bfgx_rst_count, 0444, (void *)show_bfgx_exception_count, NULL);

STATIC struct kobj_attribute wifi_rst_count =
__ATTR(wifi_rst_count, 0444, (void *)show_wifi_exception_count, NULL);

STATIC struct kobj_attribute gnss_lowpower_cntrl =
__ATTR(gnss_lowpower_state, 0644, (void *)show_gnss_lowpower_state, (void *)gnss_lowpower_state_store);

STATIC struct kobj_attribute bfgx_loglevel =
__ATTR(loglevel, 0664, (void *)show_loglevel, (void *)store_loglevel);

#ifdef HAVE_HISI_IR
STATIC struct kobj_attribute bfgx_ir_ctrl =
__ATTR(ir_ctrl, 0664, (void *)show_ir_mode, (void *)store_ir_mode);
#endif

#ifdef CONFIG_HI1102_PLAT_HW_CHR
extern ssize_t show_chr_log_switch(struct device *dev, struct kobj_attribute *attr, int8 *buf);
extern ssize_t store_chr_log_switch(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count);
static struct kobj_attribute chr_log_switch =
    __ATTR(chr_log_switch, 0644, (void *)show_chr_log_switch, (void *)store_chr_log_switch);

extern ssize_t show_chr_log_stat_info(struct device *dev, struct kobj_attribute *attr, int8 *buf);
static struct kobj_attribute chr_log_stat =
    __ATTR(chr_log_stat, 0444, (void *)show_chr_log_stat_info, (void *)0);
#endif

STATIC struct kobj_attribute bfgx_sleep_attr =
__ATTR(bfgx_sleep_state, 0444, (void *)bfgx_sleep_state_show, NULL);

STATIC struct kobj_attribute bfgx_wkup_host_count_attr =
__ATTR(bfgx_wkup_host_count, 0444, (void *)bfgx_wkup_host_count_show, NULL);

STATIC struct attribute *bfgx_attrs[] = {
        &ldisc_install.attr,
        &uart_dev_name.attr,
        &uart_baud_rate.attr,
        &uart_flow_cntrl.attr,
        &bfgx_active_state.attr,
        &ini_file_name.attr,
        &country_code.attr,
        &bfgx_rst_count.attr,
        &wifi_rst_count.attr,
        &gnss_lowpower_cntrl.attr,
        &bfgx_loglevel.attr,
#ifdef HAVE_HISI_IR
        &bfgx_ir_ctrl.attr,
#endif
#ifdef CONFIG_HI1102_PLAT_HW_CHR
        &chr_log_switch.attr,
        &chr_log_stat.attr,
#endif
        &bfgx_sleep_attr.attr,
        &bfgx_wkup_host_count_attr.attr,
        NULL,
};

STATIC struct attribute_group bfgx_attr_grp = {
    .attrs = bfgx_attrs,
};

#ifdef PLATFORM_DEBUG_ENABLE
STATIC ssize_t show_exception_dbg(struct device *dev, struct kobj_attribute *attr, int8 *buf)
{
    PS_PRINT_INFO("%s\n", __func__);

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    return snprintf(buf, SNPRINT_LIMIT_TO_KERNEL, "cmd  func             \n"
                        " 1  close bt          \n"
                        " 2  set beat flat to 0\n");
}

STATIC ssize_t store_exception_dbg(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count)
{
    int32  cmd = 0;
    int32  ret = 0;
    struct ps_core_s *ps_core_d = NULL;
    struct st_exception_info *pst_exception_data = NULL;

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return 0;
    }

    ps_get_core_reference(&ps_core_d);
    if (NULL == ps_core_d)
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return 0;
    }

    cmd = simple_strtol(buf, NULL, 10);
    PS_PRINT_INFO("cmd:%d\n", cmd);

    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        return ret;
    }

    switch (cmd)
    {
        case 1:
            PS_PRINT_INFO("exception debug test: close BT\n");
            ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_CLOSE_BT);
            break;

        case 2:
            PS_PRINT_INFO("exception: set debug beat flag to 0\n");
            pst_exception_data->debug_beat_flag = 0;
            break;

        default:
            PS_PRINT_ERR("unknown cmd %d\n", cmd);
            break;
    }

    post_to_visit_node(ps_core_d);

    return count;
}

STATIC ssize_t show_uart_rx_dump(struct device *dev, struct kobj_attribute *attr, int8 *buf)
{
    PS_PRINT_INFO("%s\n", __func__);

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    return snprintf(buf, SNPRINT_LIMIT_TO_KERNEL, "curr uart dump status =%d\n no:0\n yes:1\n", g_uart_rx_dump);
}

STATIC ssize_t store_uart_rx_dump(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count)
{
    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    g_uart_rx_dump = simple_strtol(buf, NULL, 10);
    PS_PRINT_INFO("g_uart_rx_dump aft %d\n", g_uart_rx_dump);
    return count;
}

STATIC ssize_t show_dev_test(struct device *dev, struct kobj_attribute *attr, int8 *buf)
{
    PS_PRINT_INFO("%s\n", __func__);

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    return snprintf(buf, SNPRINT_LIMIT_TO_KERNEL, "cmd  func\n  1  cause bfgx into panic\n  2  enable exception recovery\n  3  enable wifi open bcpu\n"
                                   "  4  pull up power gpio   \n  5  pull down power gpio     \n  6  uart loop test       \n");
}

extern int32 uart_loop_test(void);
STATIC ssize_t store_dev_test(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count)
{
    int32 cmd;
    int32 ret;
    struct ps_core_s *ps_core_d = NULL;
    struct st_exception_info *pst_exception_data = NULL;

    PS_PRINT_INFO("%s\n", __func__);

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return 0;
    }

    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    cmd = simple_strtol(buf, NULL, 10);
    switch (cmd)
    {
        case 1:
            ret = prepare_to_visit_node(ps_core_d);
            if (ret < 0)
            {
                PS_PRINT_ERR("prepare work FAIL\n");
                return ret;
            }

            PS_PRINT_INFO("bfgx test cmd %d, cause device panic\n", cmd);
            ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_DEV_PANIC);

            post_to_visit_node(ps_core_d);
            break;
        case 2:
            PS_PRINT_INFO("cmd %d,enable platform dfr\n", cmd);
            pst_exception_data->exception_reset_enable = PLAT_EXCEPTION_ENABLE;
            break;
        case 3:
            PS_PRINT_INFO("cmd %d,enable wifi open bcpu\n", cmd);
            wifi_open_bcpu_set(1);
            break;
        case 4:
            PS_PRINT_INFO("cmd %d,test pull up power gpio\n", cmd);
            board_power_on();
            break;
        case 5:
            PS_PRINT_INFO("cmd %d,test pull down power gpio\n", cmd);
            board_power_off();
            break;
        case 6:
            PS_PRINT_INFO("cmd %d,start uart loop test\n", cmd);
            uart_loop_test();
            break;

        default:
            PS_PRINT_ERR("unknown cmd %d\n", cmd);
            break;
    }

    return count;
}

STATIC ssize_t show_wifi_mem_dump(struct device *dev, struct kobj_attribute *attr, int8 *buf)
{
    PS_PRINT_INFO("%s\n", __func__);

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    return snprintf(buf, SNPRINT_LIMIT_TO_KERNEL, "cmd         func             \n"
                        " 1    uart halt wcpu         \n"
                        " 2    uart read wifi pub reg \n"
                        " 3    uart read wifi priv reg\n"
                        " 4    uart read wifi mem     \n"
                        " 5    equal cmd 1+2+3+4      \n");
}

STATIC ssize_t store_wifi_mem_dump(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count)
{
    int32 cmd;
    int32 ret;
    struct ps_core_s *ps_core_d = NULL;
    struct st_exception_info *pst_exception_data = NULL;

    PS_PRINT_INFO("%s\n", __func__);

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return 0;
    }

    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        return ret;
    }

    cmd = simple_strtol(buf, NULL, 10);
    switch (cmd)
    {
        case 1:
            PS_PRINT_INFO("wifi mem dump cmd %d, halt wcpu\n", cmd);
            uart_halt_wcpu();
            break;
        case 2:
            PS_PRINT_INFO("wifi mem dump cmd %d, read wifi public register\n", cmd);
            uart_read_wifi_mem(WIFI_PUB_REG);
            break;
        case 3:
            PS_PRINT_INFO("wifi mem dump cmd %d, read wifi priv register\n", cmd);
            uart_read_wifi_mem(WIFI_PRIV_REG);
            break;
        case 4:
            PS_PRINT_INFO("wifi mem dump cmd %d, read wifi mem\n", cmd);
            uart_read_wifi_mem(WIFI_MEM);
            break;
        case 5:
            PS_PRINT_INFO("wifi mem dump cmd %d\n", cmd);
            debug_uart_read_wifi_mem(1);
            break;

        default:
            PS_PRINT_ERR("error cmd:[%d]\n", cmd);
            break;
    }

    post_to_visit_node(ps_core_d);

    return count;
}


STATIC ssize_t show_bfgx_dump(struct device *dev, struct kobj_attribute *attr, int8 *buf)
{
    PS_PRINT_INFO("%s\n", __func__);

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    return snprintf(buf,SNPRINT_LIMIT_TO_KERNEL, "cmd           func            \n"
                        " 1    sdio read bcpu pub reg  \n"
                        " 2    sdio read bcpu priv reg \n"
                        " 3    sdio read bcpu mem      \n"
                        " 4    equal cmd 1+2+3         \n");
}

STATIC ssize_t store_bfgx_reg_and_reg_dump(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count)
{
    int32 cmd;
    int32 ret;
    struct ps_core_s *ps_core_d = NULL;
    struct st_exception_info *pst_exception_data = NULL;

    PS_PRINT_INFO("%s\n", __func__);

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return 0;
    }

    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        return ret;
    }

    cmd = simple_strtol(buf, NULL, 10);
    switch (cmd)
    {
        case 1:
            PS_PRINT_INFO("bfgx mem dump cmd %d,sdio read bcpu pub reg\n", cmd);
            debug_sdio_read_bfgx_reg_and_mem(BFGX_PUB_REG);
            break;
        case 2:
            PS_PRINT_INFO("bfgx mem dump cmd %d, sdio read bcpu priv reg\n", cmd);
            debug_sdio_read_bfgx_reg_and_mem(BFGX_PRIV_REG);
            break;
        case 3:
            PS_PRINT_INFO("bfgx mem dump cmd %d, sdio read bcpu mem\n", cmd);
            debug_sdio_read_bfgx_reg_and_mem(BFGX_MEM);
            break;
        case 4:
            PS_PRINT_INFO("bfgx mem dump cmd %d, sdio read bcpu reg and mem\n", cmd);
            debug_sdio_read_bfgx_reg_and_mem(SDIO_BFGX_MEM_DUMP_BOTTOM);
            break;
        default:
            PS_PRINT_ERR("error cmd:[%d]\n", cmd);
            break;
    }

    post_to_visit_node(ps_core_d);

    return count;
}

STATIC struct kobj_attribute plat_exception_dbg =
__ATTR(exception_dbg, 0644, (void *)show_exception_dbg, (void *)store_exception_dbg);

STATIC struct kobj_attribute uart_dumpctrl =
__ATTR(uart_rx_dump, 0664, (void *)show_uart_rx_dump, (void *)store_uart_rx_dump);

STATIC struct kobj_attribute bfgx_dev_test =
__ATTR(bfgx_test, 0664, (void *)show_dev_test, (void *)store_dev_test);

STATIC struct kobj_attribute wifi_mem_dump =
__ATTR(wifi_mem, 0664, (void *)show_wifi_mem_dump, (void *)store_wifi_mem_dump);

STATIC struct kobj_attribute bfgx_mem_and_reg_dump=
__ATTR(bfgx_dump, 0664, (void *)show_bfgx_dump, (void *)store_bfgx_reg_and_reg_dump);

STATIC struct attribute *hi110x_debug_attrs[] = {
        &plat_exception_dbg.attr,
        &uart_dumpctrl.attr,
        &bfgx_dev_test.attr,
        &wifi_mem_dump.attr,
        &bfgx_mem_and_reg_dump.attr,
        NULL,
};

STATIC struct attribute_group hi110x_debug_attr_grp = {
    .attrs = hi110x_debug_attrs,
};
#endif

#ifdef HAVE_HISI_NFC
STATIC ssize_t show_hisi_nfc_conf_name(struct device *dev, struct kobj_attribute *attr, int8 *buf)
{
    char hisi_nfc_conf_name[BUFF_LEN] = {0};
    int32 ret = 0;

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    ret = read_nfc_conf_name_from_dts(hisi_nfc_conf_name, sizeof(hisi_nfc_conf_name),
                                       DTS_COMP_HISI_NFC_NAME, DTS_COMP_HW_HISI_NFC_CONFIG_NAME);
    if (ret < 0)
    {
        PS_PRINT_ERR("read_nfc_conf_name_from_dts %s,ret = %d\n", DTS_COMP_HW_HISI_NFC_CONFIG_NAME, ret);
        return ret;
    }

    return snprintf(buf, sizeof(hisi_nfc_conf_name), "%s", hisi_nfc_conf_name);
}

STATIC ssize_t show_brcm_nfc_conf_name(struct device *dev, struct kobj_attribute *attr, int8 *buf)
{
    char brcm_nfc_conf_name[BUFF_LEN] = {0};
    int32 ret = 0;

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    ret = read_nfc_conf_name_from_dts(brcm_nfc_conf_name, sizeof(brcm_nfc_conf_name),
                                       DTS_COMP_HISI_NFC_NAME, DTS_COMP_HW_BRCM_NFC_CONFIG_NAME);
    if (ret < 0)
    {
        PS_PRINT_ERR("read_nfc_conf_name_from_dts %s,ret = %d\n", DTS_COMP_HW_BRCM_NFC_CONFIG_NAME, ret);
        return ret;
    }

    return snprintf(buf, sizeof(brcm_nfc_conf_name), "%s", brcm_nfc_conf_name);
}

STATIC struct kobj_attribute hisi_nfc_conf =
__ATTR(nxp_config_name, 0444, (void *)show_hisi_nfc_conf_name, NULL);

STATIC struct kobj_attribute brcm_nfc_conf =
__ATTR(nfc_brcm_conf_name, 0444, (void *)show_brcm_nfc_conf_name, NULL);

STATIC struct attribute *hisi_nfc_attrs[] = {
        &hisi_nfc_conf.attr,
        &brcm_nfc_conf.attr,
        NULL,
};

STATIC struct attribute_group hisi_nfc_attr_grp = {
    .attrs = hisi_nfc_attrs,
};
#endif

int32 bfgx_user_ctrl_init(void)
{
    int status;
    struct kobject *pst_root_object = NULL;

    pst_root_object = oal_get_sysfs_root_object();
    if(NULL == pst_root_object)
    {
        PS_PRINT_ERR("[E]get root sysfs object failed!\n");
        return -EFAULT;
    }

    g_sysfs_hisi_pmdbg = kobject_create_and_add("pmdbg", pst_root_object);
    if (NULL == g_sysfs_hisi_pmdbg)
    {
        PS_PRINT_ERR("Failed to creat g_sysfs_hisi_pmdbg !!!\n ");
		goto fail_g_sysfs_hisi_pmdbg;
    }

    status = sysfs_create_group(g_sysfs_hisi_pmdbg, &pmdbg_attr_grp);
    if (status)
    {
		PS_PRINT_ERR("failed to create g_sysfs_hisi_pmdbg sysfs entries\n");
		goto fail_create_pmdbg_group;
    }

    g_sysfs_hi110x_bfgx = kobject_create_and_add("hi110x_ps", NULL);
    if (NULL == g_sysfs_hi110x_bfgx)
    {
        PS_PRINT_ERR("Failed to creat g_sysfs_hi110x_ps !!!\n ");
		goto fail_g_sysfs_hi110x_bfgx;
    }

    status = sysfs_create_group(g_sysfs_hi110x_bfgx, &bfgx_attr_grp);
    if (status)
    {
		PS_PRINT_ERR("failed to create g_sysfs_hi110x_bfgx sysfs entries\n");
		goto fail_create_bfgx_group;
    }

#ifdef PLATFORM_DEBUG_ENABLE
    g_sysfs_hi110x_debug = kobject_create_and_add("hi110x_debug", NULL);
    if (NULL == g_sysfs_hi110x_debug)
    {
        PS_PRINT_ERR("Failed to creat g_sysfs_hi110x_debug !!!\n ");
        goto fail_g_sysfs_hi110x_debug;
    }

    status = sysfs_create_group(g_sysfs_hi110x_debug, &hi110x_debug_attr_grp);
    if (status)
    {
        PS_PRINT_ERR("failed to create g_sysfs_hi110x_debug sysfs entries\n");
        goto fail_create_hi110x_debug_group;
    }
#endif

#ifdef HAVE_HISI_NFC
    if (!is_my_nfc_chip())
    {
        PS_PRINT_ERR("cfg dev board nfc chip type is not match, skip driver init\n");
    }
    else
    {
        PS_PRINT_INFO("cfg dev board nfc type is matched with hisi_nfc, continue\n");
        g_sysfs_hisi_nfc = kobject_create_and_add("nfc", NULL);
        if (NULL == g_sysfs_hisi_nfc)
        {
            PS_PRINT_ERR("Failed to creat g_sysfs_hisi_nfc !!!\n ");
            goto fail_g_sysfs_hisi_nfc;
        }

        status = sysfs_create_group(g_sysfs_hisi_nfc, &hisi_nfc_attr_grp);
        if (status)
        {
            PS_PRINT_ERR("failed to create g_sysfs_hisi_nfc sysfs entries\n");
            goto fail_create_hisi_nfc_group;
        }
    }
#endif

    return 0;

#ifdef HAVE_HISI_NFC
fail_create_hisi_nfc_group:
    kobject_put(g_sysfs_hisi_nfc);
fail_g_sysfs_hisi_nfc:
#endif
#ifdef PLATFORM_DEBUG_ENABLE
    sysfs_remove_group(g_sysfs_hi110x_debug, &hi110x_debug_attr_grp);
fail_create_hi110x_debug_group:
    kobject_put(g_sysfs_hi110x_debug);
fail_g_sysfs_hi110x_debug:
#endif
    sysfs_remove_group(g_sysfs_hi110x_bfgx, &bfgx_attr_grp);
fail_create_bfgx_group:
    kobject_put(g_sysfs_hi110x_bfgx);
fail_g_sysfs_hi110x_bfgx:
    sysfs_remove_group(g_sysfs_hisi_pmdbg, &pmdbg_attr_grp);
fail_create_pmdbg_group:
    kobject_put(g_sysfs_hisi_pmdbg);
fail_g_sysfs_hisi_pmdbg:
    return -EFAULT;
}

void bfgx_user_ctrl_exit(void)
{
#ifdef HAVE_HISI_NFC
    if (is_my_nfc_chip())
    {
        sysfs_remove_group(g_sysfs_hisi_nfc, &hisi_nfc_attr_grp);
        kobject_put(g_sysfs_hisi_nfc);
    }
#endif

#ifdef PLATFORM_DEBUG_ENABLE
	sysfs_remove_group(g_sysfs_hi110x_debug, &hi110x_debug_attr_grp);
	kobject_put(g_sysfs_hi110x_debug);
#endif

	sysfs_remove_group(g_sysfs_hi110x_bfgx, &bfgx_attr_grp);
	kobject_put(g_sysfs_hi110x_bfgx);

	sysfs_remove_group(g_sysfs_hisi_pmdbg, &pmdbg_attr_grp);
	kobject_put(g_sysfs_hisi_pmdbg);
}

