

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
struct kobject *g_sysfs_bfgx_exception = NULL;
struct kobject *g_sysfs_hisi_nfc = NULL;
struct kobject *g_sysfs_hisi_pmdbg = NULL;
int32 g_plat_loglevel = PLAT_LOG_INFO;
int32 g_bug_on_enable = BUG_ON_DISABLE;
int32 g_uart_rx_dump = UART_DUMP_CLOSE;

extern int isAsic(void);

/*****************************************************************************
  3 Function implement
*****************************************************************************/

STATIC ssize_t show_wifi_pmdbg(struct device *dev, struct device_attribute *attr, int8 *buf)
{
   struct wlan_pm_s *pst_wlan_pm = wlan_pm_get_drv();

   return sprintf(buf, "wifi_pm_debug usage: \n"
                       "    1:open wifi     2:close wifi\n"
                       "    3:enable pm     4:disable pm \n"
                       "    5:wakelock      6:wake unlock \n"
                       "    7:dump host info 8:dump device info \n"
                       "    9:debug wakeup cmd 10:debug sleep cmd\n"
                       "    big than 50: set sleep timeout \n"
                       "power:%ld,enable:%ld,dev state:%ld,wakelock_cnt=%lu,wdg_timeout_cnt=%d\n",
                       pst_wlan_pm->ul_wlan_power_state,
                       pst_wlan_pm->ul_wlan_pm_enable,
                       pst_wlan_pm->ul_wlan_dev_state,
                       pst_wlan_pm->pst_sdio->st_sdio_wakelock.lock_count,
                       pst_wlan_pm->ul_wdg_timeout_cnt);
}

STATIC ssize_t store_wifi_pmdbg(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count)
{
    struct wlan_pm_s *pst_wlan_pm = wlan_pm_get_drv();
    int input = oal_atoi(buf);

    if (NULL == pst_wlan_pm)
    {
        OAL_IO_PRINT("pm_data is NULL!\n");
        return -FAILURE;
    }

    switch(input)
    {
       case 1:
        wlan_pm_open();
       break;
       case 2:
        wlan_pm_close();
       break;
       case 3:
        wlan_pm_enable();
       break;
       case 4:
        wlan_pm_disable();
       break;
       case 5:
        wlan_pm_debug_wake_lock();
       break;
       case 6:
        wlan_pm_debug_wake_unlock();
       break;
       case 7:
        wlan_pm_dump_host_info();
       break;
       case 8:
        wlan_pm_dump_device_info();
       break;
      case 9:
        wlan_pm_debug_wakeup();
        break;
       case 10:
         wlan_pm_debug_sleep();
       break;
       default:
       if((input >= 50) && (input < 5000))
        {
           wlan_pm_set_timeout((input/50));
        }
        break;
    }

    return count;
}

STATIC ssize_t show_bfgx_pmdbg(struct device *dev, struct device_attribute *attr, int8 *buf)
{
    PS_PRINT_INFO("%s", __func__);
    return sprintf(buf, "cmd  func\n"
                        "  1  plat pm enable\n  2  plat pm disable\n"
                        "  3   bt  pm enable\n  4   bt  pm disable\n"
                        "  5  gnss pm enable\n  6  gnss pm disable\n"
                        "  7   nfc pm enable\n  8   nfc pm disable\n"
                        "  9  shutdown bcpu \n  0  reset bcpu     \n"
                        "  10 pm ctrl enable\n  11 pm ctrl disable\n");
}

extern int32 execute_download_cmd(int32 cmd_type, uint8 *cmd_name, uint8 *cmd_para);
STATIC ssize_t store_bfgx_pmdbg(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count)
{
    struct ps_core_s *ps_core_d = NULL;
    struct pm_drv_data *pm_data = NULL;
    int32  cmd = 0;
    int32  ret = 0;

    cmd = simple_strtol(buf, NULL, 10);
    PS_PRINT_INFO("cmd:%d", cmd);

    ps_get_core_reference(&ps_core_d);
    if (NULL == ps_core_d)
    {
        PS_PRINT_ERR("ps_core_d is NULL!\n");
        return -FAILURE;
    }

    pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        return ret;
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
        /* case 9 & case 0: shutdown bcpu & reboot bcpu */
        case 9:
            ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_SHUTDOWN_SLP);
            break;
        case 0:
            execute_download_cmd(2, "WRITEM", "2,0x50000094,1");
            break;
        case 10:
            pm_data->bfgx_pm_ctrl_enable = BFGX_PM_ENABLE;
            break;
        case 11:
            pm_data->bfgx_pm_ctrl_enable = BFGX_PM_DISABLE;
            break;

        default:
            break;
    }

    post_to_visit_node(ps_core_d);

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
STATIC ssize_t show_install(struct device *dev, struct device_attribute *attr, int8 *buf)
{
    struct ps_plat_s *pm_data = dev_get_drvdata(&hw_ps_device->dev);
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }
    PS_PRINT_FUNCTION_NAME;
    return sprintf(buf, "%d\n", pm_data->ldisc_install);
}

/* read by octty from hal to decide open which uart */
STATIC ssize_t show_dev_name(struct device *dev, struct device_attribute *attr, int8 *buf)
{
    struct ps_plat_s *pm_data = dev_get_drvdata(&hw_ps_device->dev);
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }
    PS_PRINT_FUNCTION_NAME;
    return sprintf(buf, "%s\n", pm_data->dev_name);
}

/* read by octty from hal to decide what baud rate to use */
STATIC ssize_t show_baud_rate(struct device *dev, struct device_attribute *attr, int8 *buf)
{
    struct ps_plat_s *pm_data = dev_get_drvdata(&hw_ps_device->dev);
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }
    PS_PRINT_FUNCTION_NAME;
    return sprintf(buf, "%ld\n", pm_data->baud_rate);
}

/* read by octty from hal to decide whether or not use flow cntrl */
STATIC ssize_t show_flow_cntrl(struct device *dev, struct device_attribute *attr, int8 *buf)
{
    struct ps_plat_s *pm_data = dev_get_drvdata(&hw_ps_device->dev);
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }
    PS_PRINT_FUNCTION_NAME;
    return sprintf(buf, "%d\n", pm_data->flow_cntrl);
}

STATIC ssize_t gnss_lowpower_state_store(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count)
{
    int flag = 0;

    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -EFAULT;
    }
    PS_PRINT_DBG("gnss_lowpower_state_store!\n");

    flag = simple_strtol(buf, NULL, 10);
    /*gnss write the flag to request sleep*/
    if (1 == flag)
    {
        if (BFGX_PM_DISABLE == pm_data->bfgx_lowpower_enable)
        {
            PS_PRINT_WARNING("gnss low power disabled!\n");
            return -EFAULT;
        }
        if (BFGX_SLEEP == pm_data->ps_pm_interface->bfgx_dev_state_get())
        {
            PS_PRINT_WARNING("gnss proc: dev has been sleep, not allow dev slp\n");
            return -EFAULT;
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
        return -EFAULT;
    }

    return count;
}

/* show curr bfg proto yes or not opened state */
STATIC ssize_t show_bfg_active_state(struct device *dev, struct device_attribute *attr, int8 *buf)
{
    struct ps_plat_s *pm_data = dev_get_drvdata(&hw_ps_device->dev);
    uint8 bt_state   = POWER_STATE_SHUTDOWN;
    uint8 gnss_state = POWER_STATE_SHUTDOWN;
    uint8 fm_state   = POWER_STATE_SHUTDOWN;
    uint8 ir_state   = POWER_STATE_SHUTDOWN;
    uint8 nfc_state  = POWER_STATE_SHUTDOWN;

    PS_PRINT_DBG("%s\n", __func__);
    if (true == atomic_read(&pm_data->core_data->bfgx_info[BFGX_BT].subsys_state))
    {
        bt_state = POWER_STATE_OPEN;
    }
    if (true == atomic_read(&pm_data->core_data->bfgx_info[BFGX_GNSS].subsys_state))
    {
        gnss_state = POWER_STATE_OPEN;
    }
    if (true == atomic_read(&pm_data->core_data->bfgx_info[BFGX_FM].subsys_state))
    {
        fm_state = POWER_STATE_OPEN;
    }
    if (true == atomic_read(&pm_data->core_data->bfgx_info[BFGX_IR].subsys_state))
    {
        ir_state = POWER_STATE_OPEN;
    }
    if (true == atomic_read(&pm_data->core_data->bfgx_info[BFGX_NFC].subsys_state))
    {
        nfc_state = POWER_STATE_OPEN;
    }

    return sprintf(buf, "bt:%d; gnss:%d; fm:%d; ir:%d; nfc:%d;\n", bt_state, gnss_state, fm_state, ir_state, nfc_state);
}

STATIC ssize_t show_uart_rx_dump(struct device *dev, struct device_attribute *attr, int8 *buf)
{
    PS_PRINT_INFO("%s", __func__);
    return sprintf(buf, "curr uart dump status =%d\n no:0\n yes:1\n", g_uart_rx_dump);
}

STATIC ssize_t store_uart_rx_dump(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count)
{
    g_uart_rx_dump = simple_strtol(buf, NULL, 10);
    PS_PRINT_INFO("g_uart_rx_dump aft %d\n", g_uart_rx_dump);
    return count;
}


STATIC ssize_t show_loglevel(struct device *dev, struct device_attribute *attr, int8 *buf)
{
    PS_PRINT_INFO("%s", __func__);
    return sprintf(buf, "curr loglevel=%d, curr bug_on=%d\nalert:0\nerr:1\nwarning:2\nfunc|succ|info:3\ndebug:4\nbug_on enable:b\nbug_on disable:B\n", g_plat_loglevel, g_bug_on_enable);
}

STATIC ssize_t store_loglevel(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count)
{
    int32 loglevel = PLAT_LOG_INFO;

    PS_PRINT_INFO("%s", __func__);

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

STATIC ssize_t show_ir_mode(struct device *dev, struct device_attribute *attr, int8 *buf)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    PS_PRINT_INFO("%s", __func__);

    if (!isAsic())
    {
        PS_PRINT_ERR("HI1102 FPGA VERSION, ir contral gpio not exist\n");
        return -FAILURE;
    }

    return sprintf(buf, "%d\n", gpio_get_value(pm_data->board->bfgn_ir_ctrl));
}

STATIC ssize_t store_ir_mode(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count)
{
    int32 gpio_level;
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    PS_PRINT_INFO("%s", __func__);

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

STATIC ssize_t show_dev_test(struct device *dev, struct device_attribute *attr, int8 *buf)
{
    PS_PRINT_INFO("%s", __func__);
    return sprintf(buf, "cmd  func\n  1  cause bfgx into panic\n  2  enable exception recovery\n  3  enable wifi open bcpu\n"
                                   "  4  pull up power gpio   \n  5  pull down power gpio\n");
}

STATIC ssize_t store_dev_test(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count)
{
    int32 cmd;
    int32 ret;
    struct ps_core_s *ps_core_d = NULL;
    struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return 0;
    }

    PS_PRINT_INFO("%s", __func__);

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
            PS_PRINT_INFO("bfgx test cmd %d, cause device panic\n", cmd);
            ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_DEV_PANIC);
            break;
        case 2:
            PS_PRINT_INFO("cmd %d,enable platform exception recovery\n", cmd);
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

        default:
            break;
    }

    post_to_visit_node(ps_core_d);

    return count;
}

STATIC ssize_t show_ini_file_name(struct device *dev, struct kobj_attribute *attr, char *buf, size_t count)
{
    return snprintf(buf, INI_FILE_PATH_LEN, "%s", g_ini_file_name);
}

STATIC ssize_t show_country_code(struct device *dev, struct kobj_attribute *attr, char *buf, size_t count)
{
    int8 *country_code = NULL;
    int32 len;
    int ret;
    int8 ibuf[COUNTRY_CODE_LEN];

    country_code = hwifi_get_country_code();
    len = strlen(country_code) + 1;
    if (strncmp(country_code, "99", strlen("99")) == 0)
    {
        ret = get_cust_conf_string(CUST_MODU_WIFI, "country_code", ibuf);
        if (ret == INI_SUCC && count >= COUNTRY_CODE_LEN)
        {
            strncpy(buf, ibuf, 3);
            buf[COUNTRY_CODE_LEN-1] = '\0';
            return strlen(buf);
        }
        else
        {
            PS_PRINT_ERR("get dts country_code error");
            return 0;
        }
    }
    else if (count >= len)
    {
        return snprintf(buf, COUNTRY_CODE_LEN, "%s", country_code);
    }
    else
    {
        PS_PRINT_ERR("get wifi country_code error");
        return 0;
    }
}

STATIC ssize_t show_wifi_mem_dump(struct device *dev, struct device_attribute *attr, int8 *buf)
{
    PS_PRINT_INFO("%s", __func__);
    return sprintf(buf, "cmd  func\n  1  uart halt wcpu         \n  2  uart read wifi pub reg\n  3  uart read wifi priv reg\n"
                                   "  4  uart read wifi mem     \n  5  equal cmd 1+2+3+4\n");
}

STATIC ssize_t store_wifi_mem_dump(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count)
{
    int32 cmd;
    int32 ret;
    struct ps_core_s *ps_core_d = NULL;
    struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return 0;
    }

    PS_PRINT_INFO("%s", __func__);

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

STATIC ssize_t show_uart_test(struct device *dev, struct device_attribute *attr, int8 *buf)
{
    PS_PRINT_INFO("%s", __func__);
    return sprintf(buf, "cmd  func\n  1  open uart         \n  2  close uart\n"
                                   "  3  open bt         \n");
}

STATIC ssize_t store_uart_test(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count)
{
    int32 cmd;
    struct ps_core_s *ps_core_d = NULL;

    PS_PRINT_INFO("%s", __func__);

    ps_get_core_reference(&ps_core_d);    //no check out return
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    cmd = simple_strtol(buf, NULL, 10);
    switch (cmd)
    {
        case 1:
            PS_PRINT_INFO("uart test cmd %d: open uart\n", cmd);
            open_tty_drv(ps_core_d->pm_data);       //no check out return
            break;
        case 2:
            PS_PRINT_INFO("uart test cmd %d: close uart\n", cmd);
            release_tty_drv(ps_core_d->pm_data);    //no check out return
            break;
        case 3:
            PS_PRINT_INFO("uart test cmd %d: open bt\n", cmd);
            ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_OPEN_BT);
            break;

        default:
            PS_PRINT_ERR("error cmd:[%d]\n", cmd);
            break;
    }

    return count;
}
/*****************************************************************************
 函 数 名  : show_bfgx_dump
 功能描述  : 显示SDIO上报BFGX的reg
 输入参数  :
 输出参数  :
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月2日
    作    者   : c00351912
    修改内容   : 新生成函数

*****************************************************************************/
STATIC ssize_t show_bfgx_dump(struct device *dev, struct device_attribute *attr, int8 *buf)
{
    PS_PRINT_INFO("%s", __func__);
    return sprintf(buf, "cmd  func\n  1  sdio read bcpu pub reg \n  2  sdio read bcpu priv reg \n  3 sdio read bcpu mem\n"
                                                                   "4  equal cmd 1+2+3\n");
}
/*****************************************************************************
 函 数 名  : store_bfgx_reg_and_reg_dump
 功能描述  : SDIO上报BFGX的reg
 输入参数  :

 输出参数  :
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月2日
    作    者   : c00351912
    修改内容   : 新生成函数

*****************************************************************************/
STATIC ssize_t store_bfgx_reg_and_reg_dump(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count)
{
    int32 cmd;
    int32 ret;
    struct ps_core_s *ps_core_d = NULL;
    struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return 0;
    }

    PS_PRINT_INFO("%s", __func__);

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
/* structures specific for sysfs entries */
STATIC struct kobj_attribute ldisc_install =
__ATTR(install, 0444, (void *)show_install, NULL);

STATIC struct kobj_attribute uart_dev_name =
__ATTR(dev_name, 0444, (void *)show_dev_name, NULL);

STATIC struct kobj_attribute uart_baud_rate =
__ATTR(baud_rate, 0444, (void *)show_baud_rate, NULL);

STATIC struct kobj_attribute uart_flow_cntrl =
__ATTR(flow_cntrl, 0444, (void *)show_flow_cntrl, NULL);

STATIC struct kobj_attribute gnss_lowpower_cntrl =
__ATTR(gnss_lowpower_state, 0644, NULL, (void *)gnss_lowpower_state_store);

STATIC struct kobj_attribute bfg_active_state =
__ATTR(bfg_state, 0444, (void *)show_bfg_active_state, NULL);

STATIC struct kobj_attribute bfgx_loglevel =
__ATTR(loglevel, 0664, (void *)show_loglevel, (void *)store_loglevel);

STATIC struct kobj_attribute uart_dumpctrl =
__ATTR(uart_rx_dump, 0664, (void *)show_uart_rx_dump, (void *)store_uart_rx_dump);


STATIC struct kobj_attribute bfgx_ir_ctrl =
__ATTR(ir_ctrl, 0664, (void *)show_ir_mode, (void *)store_ir_mode);

STATIC struct kobj_attribute bfgx_dev_test =
__ATTR(bfgx_test, 0664, (void *)show_dev_test, (void *)store_dev_test);

STATIC struct kobj_attribute ini_file_name =
__ATTR(ini_file_name, 0644, (void *)show_ini_file_name, NULL);

STATIC struct kobj_attribute country_code =
__ATTR(country_code, 0644, (void *)show_country_code, NULL);

STATIC struct kobj_attribute wifi_mem_dump =
__ATTR(wifi_mem, 0664, (void *)show_wifi_mem_dump, (void *)store_wifi_mem_dump);

STATIC struct kobj_attribute bfgx_uart_test =
__ATTR(uart_test, 0664, (void *)show_uart_test, (void *)store_uart_test);

STATIC struct kobj_attribute bfgx_mem_and_reg_dump=
__ATTR(bfgx_dump, 0664, (void *)show_bfgx_dump, (void *)store_bfgx_reg_and_reg_dump);


STATIC struct attribute *bfgx_attrs[] = {
        &ldisc_install.attr,
        &uart_dev_name.attr,
        &uart_baud_rate.attr,
        &uart_flow_cntrl.attr,
        &gnss_lowpower_cntrl.attr,
        &bfg_active_state.attr,
        &bfgx_loglevel.attr,
        &uart_dumpctrl.attr,
        &bfgx_ir_ctrl.attr,
        &bfgx_dev_test.attr,
        &ini_file_name.attr,
        &country_code.attr,
        &wifi_mem_dump.attr,
        &bfgx_uart_test.attr,
        &bfgx_mem_and_reg_dump.attr,

        NULL,
};

STATIC struct attribute_group bfgx_attr_grp = {
    .attrs = bfgx_attrs,
};

STATIC ssize_t show_bfgx_exception_count(struct device *dev, struct device_attribute *attr, int8 *buf)
{
    struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return 0;
    }

    PS_PRINT_DBG("exception debug: bfgx rst count is %d\n", pst_exception_data->bfgx_exception_cnt);
    return sprintf(buf, "%d\n", pst_exception_data->bfgx_exception_cnt);
}

STATIC ssize_t show_wifi_exception_count(struct device *dev, struct device_attribute *attr, int8 *buf)
{
    struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return 0;
    }

    PS_PRINT_DBG("exception debug: wifi rst count is %d\n", pst_exception_data->wifi_exception_cnt);
    return sprintf(buf, "%d\n", pst_exception_data->wifi_exception_cnt);
}

STATIC ssize_t show_exception_dbg(struct device *dev, struct device_attribute *attr, int8 *buf)
{
    PS_PRINT_INFO("%s", __func__);
    return sprintf(buf, "cmd  func\n"
                        "  1  close bt    \n  2  set beat flat to 0\n");
}

STATIC ssize_t store_exception_dbg(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count)
{
    int32  cmd = 0;
    int32  ret = 0;
    struct ps_core_s *ps_core_d = NULL;
    struct st_exception_info *pst_exception_data = NULL;

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
    PS_PRINT_INFO("cmd:%d", cmd);

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
            break;
    }

    post_to_visit_node(ps_core_d);

    return count;
}

STATIC struct kobj_attribute bfgx_exception_count =
__ATTR(bfgx_rst_count, 0444, (void *)show_bfgx_exception_count, NULL);

STATIC struct kobj_attribute wifi_exception_count =
__ATTR(wifi_rst_count, 0444, (void *)show_wifi_exception_count, NULL);

STATIC struct kobj_attribute plat_exception_dbg =
__ATTR(exception_dbg, 0644, (void *)show_exception_dbg, (void *)store_exception_dbg);

STATIC struct attribute *exception_attrs[] = {
        &bfgx_exception_count.attr,
        &wifi_exception_count.attr,
        &plat_exception_dbg.attr,
        NULL,
};

STATIC struct attribute_group exception_attr_grp = {
    .attrs = exception_attrs,
};

STATIC ssize_t show_hisi_nfc_conf_name(struct device *dev, struct device_attribute *attr, int8 *buf)
{
    char hisi_nfc_conf_name[BUFF_LEN] = {0};
    int32 ret = 0;

    ret = read_nfc_conf_name_from_dts(hisi_nfc_conf_name, sizeof(hisi_nfc_conf_name),
                                       DTS_COMP_HISI_NFC_NAME, DTS_COMP_HW_HISI_NFC_CONFIG_NAME);
    if (ret < 0)
    {
        PS_PRINT_ERR("read_nfc_conf_name_from_dts %s,ret = %d\n", DTS_COMP_HW_HISI_NFC_CONFIG_NAME, ret);
        return ret;
    }

    return snprintf(buf, sizeof(hisi_nfc_conf_name), "%s", hisi_nfc_conf_name);
}

STATIC ssize_t show_brcm_nfc_conf_name(struct device *dev, struct device_attribute *attr, int8 *buf)
{
    char brcm_nfc_conf_name[BUFF_LEN] = {0};
    int32 ret = 0;

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

    g_sysfs_bfgx_exception = kobject_create_and_add("hi110x_exception", NULL);
    if (NULL == g_sysfs_bfgx_exception)
    {
        PS_PRINT_ERR("Failed to creat g_sysfs_bfgx_exception !!!\n ");
        goto fail_g_sysfs_bfgx_exception;
    }

    status = sysfs_create_group(g_sysfs_bfgx_exception, &exception_attr_grp);
    if (status)
    {
		PS_PRINT_ERR("failed to create g_sysfs_bfgx_exception sysfs entries\n");
		goto fail_create_exception_group;
    }

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

    return 0;

fail_create_hisi_nfc_group:
    kobject_put(g_sysfs_hisi_nfc);
fail_g_sysfs_hisi_nfc:
    sysfs_remove_group(g_sysfs_bfgx_exception, &exception_attr_grp);
fail_create_exception_group:
    kobject_put(g_sysfs_bfgx_exception);
fail_g_sysfs_bfgx_exception:
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
    if (is_my_nfc_chip())
    {
        sysfs_remove_group(g_sysfs_hisi_nfc, &hisi_nfc_attr_grp);
        kobject_put(g_sysfs_hisi_nfc);
    }

	sysfs_remove_group(g_sysfs_bfgx_exception, &exception_attr_grp);
	kobject_put(g_sysfs_bfgx_exception);

	sysfs_remove_group(g_sysfs_hi110x_bfgx, &bfgx_attr_grp);
	kobject_put(g_sysfs_hi110x_bfgx);

	sysfs_remove_group(g_sysfs_hisi_pmdbg, &pmdbg_attr_grp);
	kobject_put(g_sysfs_hisi_pmdbg);
}

