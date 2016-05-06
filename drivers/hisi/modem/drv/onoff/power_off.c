/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*lint --e{537} */
#include <hi_gpio.h>
#include <linux/gpio.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/syscalls.h>
#include <linux/errno.h>
#include <linux/err.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/rtc.h>
#ifdef BSP_CONFIG_P532_FPGA
#include <of.h>
#endif

#include <product_config.h>
#include <osl_list.h>
#include <osl_types.h>
#include <osl_spinlock.h>
#include <mdrv_chg.h>
#include <mdrv_sysboot.h>
#include <bsp_pmu.h>
#include <power_com.h>
#include "power_exchange.h"

#include <bsp_reset.h>

#include <bsp_onoff.h>
#include <bsp_sysctrl.h>
#include "mdrv_chg.h"

#include "bsp_dump.h"


struct bsp_onoff_callback {
    struct list_head node;
    void (*fn)(void);
};

static LIST_HEAD(list_callback);
static DEFINE_SPINLOCK(list_spinlock); //lint !e43 !e64 !e120


#ifdef CONFIG_BALONG_ONOFF

#define POWER_OFF_MONOTER_TIMEROUT      (5000)
#define EXCH_RESET_LOG_PATH     "/modem_log/poweroff.txt"

typedef struct
{
    DRV_SHUTDOWN_REASON_E      reason;
    struct rtc_time            time;
	struct softtimer_list      off_timer;
}power_off_ctrl_s;

extern BATT_LEVEL_E chg_get_batt_level(void);

power_off_ctrl_s power_off_ctrl = {DRV_SHUTDOWN_BUTT, {0,0,0,0,0,0,0,0,0}};

/* stub */
BATT_LEVEL_E chg_get_batt_level(void)
{
    return BATT_LEVEL_4;
}

static inline void sysboot_set(void* __virt_addr, u32 __bit_offset, u32 __bit_width, u32 __bit_value)
{
    u32 __value = 0;

    __value = readl(__virt_addr);
    __value &= ~(((1 << __bit_width) - 1) << __bit_offset);
    __value |= (__bit_value << __bit_offset);
    writel(__value, (void*)__virt_addr);
}

/*****************************************************************************
 函 数 名  : power_off_down_operation
 功能描述  : pmu hold 系统下电
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
*****************************************************************************/
LOCAL_1 void power_off_down_operation( void )
{
    int ret = 0;
    u32 dts_info[4];
    struct device_node *dev_node = NULL;

    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ONOFF, "system power down!\n");

    dev_node = of_find_compatible_node(NULL, NULL, "hisilicon,sysboot_balong");
    if (dev_node) {
    } else {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ONOFF, "fail to find sysboot dts node\n");
        goto dead_loop;
    }

    ret = of_property_read_u32_array(dev_node, "power_down", &dts_info[0], sizeof(dts_info)/sizeof(dts_info[0]));
    if (!ret) {
        sysboot_set(bsp_sysctrl_addr_get((void*)dts_info[0]), dts_info[1], dts_info[2], dts_info[3]);
    } else {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ONOFF, "fail to read sysboot dts node, ret = %d\n", ret);
        goto dead_loop;
    }

dead_loop:
    /* coverity[no_escape] */
    for(;;) ;
}

/*****************************************************************************
 函 数 名  : power_off_reboot_operation
 功能描述  : pmu rst 系统重启
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
*****************************************************************************/
LOCAL_1 void power_off_reboot_operation( void )
{
    int ret = 0;
    u32 dts_info[4];
    struct device_node *dev_node = NULL;
#ifdef BSP_CONFIG_P532_FPGA
    struct device_node *fpga_dev = NULL;
    u32 base_addr = 0, off = 0, val = 0;
#endif
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ONOFF, "system reboot!\n");

/* p532_FPGA复位需要同时复位fpga. */
#ifdef BSP_CONFIG_P532_FPGA
    fpga_dev = of_find_compatible_node(NULL, NULL, "hisilicon,fpga_reboot");
    if (!fpga_dev) {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ONOFF, "fail to find fpga reboot dts node\n");
        goto p532_reset;
    }

    base_addr = of_iomap(fpga_dev, 0);
    if(!base_addr) {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ONOFF, "fail to get base addr\n");
        goto p532_reset;
    }

    ret = of_property_read_u32(fpga_dev, "off", &off);
    ret |= of_property_read_u32(fpga_dev, "val", &val);
    if (ret) {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ONOFF, "fail to get reg off and val, ret = %d\n", ret);
        goto p532_reset;
    }

    writel(val, base_addr + off);  
p532_reset:
#endif

    dev_node = of_find_compatible_node(NULL, NULL, "hisilicon,sysboot_balong");
    if (dev_node) {
    } else {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ONOFF, "fail to find sysboot dts node\n");
        goto dead_loop;
    }

    ret = of_property_read_u32_array(dev_node, "reboot", &dts_info[0], sizeof(dts_info)/sizeof(dts_info[0]));
    if (!ret) {
        sysboot_set(bsp_sysctrl_addr_get((void*)dts_info[0]), dts_info[1], dts_info[2], dts_info[3]);
    } else {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ONOFF, "fail to read sysboot dts node, ret = %d\n", ret);
        goto dead_loop;
    }

dead_loop:
    /* coverity[no_escape] */
    for(;;) ;
}

/*****************************************************************************
 函 数 名  : is_power_key_pressed
 功能描述  : 关机时按键是否按下
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
*****************************************************************************/
LOCAL_1 bool is_power_key_pressed( void )
{
    return bsp_pmu_key_state_get();
}

/*****************************************************************************
 函 数 名  : is_power_off_charge_in
 功能描述  : 关机时充电器是否插入
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
*****************************************************************************/
LOCAL_1 bool is_power_off_charge_in( void )
{
    return bsp_pmu_usb_state_get();
}
/*****************************************************************************
 函 数 名  : power_off_operation
 功能描述  : 执行关机操作
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
*****************************************************************************/
LOCAL_1 void power_off_operation( void )
{
    /* 按键不松开情况下，不允许关机 */
    while( is_power_key_pressed() )
    {
        /* avoid the watchdog reset while polling the power key */
        /* TO DO*/
    }

    pr_dbg("\r\n power_off_operation : the power key is release\r\n" );

    /* shutdown the system. */
    power_off_down_operation();
}

/*****************************************************************************
 函 数 名  : power_off_set_flag_and_reboot
 功能描述  : 执行关机操作
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
*****************************************************************************/
LOCAL_1 void power_off_set_flag_and_reboot( power_off_reboot_flag enRebootFlag )
{
    /*lint --e{*} */
    unsigned long irq_flags = 0;
    struct bsp_onoff_callback *hook = NULL;

    spin_lock_irqsave(&list_spinlock, irq_flags);
    /*coverity[var_deref_op] */
    list_for_each_entry(hook, &list_callback, node)
        /*coverity[var_compare_op] */
        if ((hook) && (hook->fn))
            hook->fn();
    spin_unlock_irqrestore(&list_spinlock, irq_flags);

    power_on_reboot_flag_set( enRebootFlag );
    power_off_reboot_operation();
}

/*****************************************************************************
 函 数 名  : power_off_battery_error_handler
 功能描述  : 电池错误关机处理
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
*****************************************************************************/
LOCAL_1  void power_off_battery_error_handler( void )
{
    if( is_power_off_charge_in() )
    {
        power_off_set_flag_and_reboot( POWER_OFF_REASON_BAD_BATTERY );
    }
    else
    {
        power_off_operation();
    }
}

/*****************************************************************************
 函 数 名  : power_off_battery_low_handler
 功能描述  : 电池低电处理
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
*****************************************************************************/
LOCAL_1 void power_off_battery_low_handler( void )
{
    if( is_power_off_charge_in() )
    {
        power_off_set_flag_and_reboot( POWER_OFF_REASON_LOW_BATTERY );
    }
    else
    {
        power_off_operation();
    }
}

/*****************************************************************************
 函 数 名  : power_off_temp_protect_handler
 功能描述  : 温度保护处理
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
*****************************************************************************/
LOCAL_1 void power_off_temp_protect_handler( void )
{
    if( is_power_off_charge_in() )
    {
        /* The charge is in, can't power off, restart and show the warning */
        power_off_set_flag_and_reboot(POWER_OFF_REASON_OVER_TEMP);
    }
    else
    {
        /* No warning message, power off directly */
        power_off_operation();
    }
}

/*****************************************************************************
 函 数 名  : power_off_power_key_handler
 功能描述  : 按键关机处理, 在关机充电模式下按键，进入正常工作模式
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
*****************************************************************************/
LOCAL_1 void power_off_power_key_handler( void )
{
    if( DRV_START_MODE_CHARGING == bsp_start_mode_get() )
    {
        /* reboot and enter normal mode; */
        power_off_set_flag_and_reboot( POWER_OFF_REASON_NORMAL );
    }
    else /* normal mode */
    {
        /* if charge is in, will power on again and enter charge mode. */
        power_off_operation();
    }
}

/*****************************************************************************
 函 数 名  : power_off_update_handler
 功能描述  : 升级关机处理，软复位进入recovery模式
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
*****************************************************************************/
LOCAL_1 void power_off_update_handler( void )
{
    /* reboot and enter update mode */
    power_off_set_flag_and_reboot( POWER_OFF_REASON_UPDATE );
}

/*****************************************************************************
 函 数 名  : power_off_charge_remove_handler
 功能描述  : 充电器移除处理
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
*****************************************************************************/
LOCAL_1 void power_off_charge_remove_handler( void )
{
    if( DRV_START_MODE_CHARGING == bsp_start_mode_get() )
    {
        power_off_set_flag_and_reboot( POWER_OFF_REASON_RM_CHARGE );
        power_off_operation();  /* 关机充电时，拔除充电器，单板直接下电 */
    }
    else
    {
        /* Normal mode, nothing need to do. */
    }
}

/*****************************************************************************
 函 数 名  : power_off_reset_handler
 功能描述  : 系统复位操作，直接复位，不用检查charger状态
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
*****************************************************************************/
void power_off_reset_handler( void )
{
    /* Needn't check charge status */
    power_off_set_flag_and_reboot( POWER_OFF_REASON_NORMAL );
}

/*****************************************************************************
 函 数 名  : power_off_reset_handler
 功能描述  : 系统复位操作，直接复位，不用检查charger状态
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
*****************************************************************************/
LOCAL_1 void power_off_excecute( DRV_SHUTDOWN_REASON_E enShutdownReason )
{
	unsigned long flags = 0;

	local_irq_save(flags);

    switch( enShutdownReason )
    {
    case DRV_SHUTDOWN_RESET:
        power_off_set_flag_and_reboot( POWER_OFF_REASON_NORMAL );
        break;
    case DRV_SHUTDOWN_BATTERY_ERROR:
        power_off_battery_error_handler();
        break;
    case DRV_SHUTDOWN_LOW_BATTERY:
        power_off_battery_low_handler();
        break;
    case DRV_SHUTDOWN_TEMPERATURE_PROTECT:
        power_off_temp_protect_handler();
        break;
    case DRV_SHUTDOWN_POWER_KEY:
        power_off_power_key_handler();
        break;
    case DRV_SHUTDOWN_UPDATE:
        power_off_update_handler();
        break;
    case DRV_SHUTDOWN_CHARGE_REMOVE:
        power_off_charge_remove_handler( );
        break;
    default:
        power_off_operation();
        break;
    }

    /* Woulnd't reach here ! */
    local_irq_restore( flags );
}

/*****************************************************************************
 函 数 名  : power_on_mode_get
 功能描述  : 获取开机模式
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
*****************************************************************************/
unsigned int power_off_reason_get( void )
{
    power_off_reboot_flag reboot_reason = (power_off_reboot_flag)(power_off_ctrl.reason) ;
    DRV_SHUTDOWN_REASON_E rb = DRV_SHUTDOWN_BUTT;

    switch(reboot_reason)
    {
    case POWER_OFF_REASON_NORMAL:
        rb = DRV_SHUTDOWN_POWER_KEY;
        break;
    case POWER_OFF_REASON_BAD_BATTERY:
        rb = DRV_SHUTDOWN_BATTERY_ERROR;
        break;
    case POWER_OFF_REASON_LOW_BATTERY:
        rb = DRV_SHUTDOWN_LOW_BATTERY;
        break;
    case POWER_OFF_REASON_OVER_TEMP:
        rb = DRV_SHUTDOWN_TEMPERATURE_PROTECT;
        break;
    case POWER_OFF_REASON_RM_CHARGE:
        rb = DRV_SHUTDOWN_CHARGE_REMOVE;
        break;
    case POWER_OFF_REASON_UPDATE:
        rb = DRV_SHUTDOWN_UPDATE;
        break;
    case POWER_OFF_REASON_RESET:
        rb = DRV_SHUTDOWN_RESET;
        break;
    default:
        rb = DRV_SHUTDOWN_BUTT;
        break;
    }

    return rb;

}

/******************************************************************************
*  Function:  power_off_timeout_isr
*  Description: 如果应用没有一定时间内关机，底层直接关机
*  Input:
*         None
*  Output:
*         None
*  Return:
*         None
*  Note  :
********************************************************************************/
static int power_off_timeout_isr( void )
{
    pr_dbg("power_off_timeout_isr, reason :%d\n ",power_off_ctrl.reason);

    (void)bsp_softtimer_free(&power_off_ctrl.off_timer);

    power_off_excecute(power_off_ctrl.reason);

    return 0;
}

/******************************************************************************
*  Function:  drv_power_off
*  Description: 直接关机接口，不记录关机事件
*  Input:
*         None
*  Output:
*         None
*  Return:
*         None
*  Note  :
********************************************************************************/
LOCAL_1 void drv_power_off( void )
{
    /*
       If the shutdown reason has been set, do it.
       If not, it is invalid one and will shutdown
    */
    power_off_excecute(power_off_ctrl.reason);
}
#endif

void bsp_reboot_callback_register(void (*hook)(void))
{
    /*lint --e{*} */
    unsigned long flags = 0;

    struct bsp_onoff_callback *callback =
        (struct bsp_onoff_callback *)kmalloc(sizeof(struct bsp_onoff_callback), GFP_KERNEL);
    if (NULL == callback)
    {
        pr_dbg("fail to malloc struct bsp_onoff_callback \n");
        return;
    }

    callback->fn = hook;

    spin_lock_irqsave(&list_spinlock, flags);
    list_add(&callback->node, &list_callback);
    spin_unlock_irqrestore(&list_spinlock, flags);
    /*coverity[leaked_storage] */
}

/******************************************************************************
*  Function:  drv_shut_down
*  Description: start the power off process.
*  Input:
*         eReason : shutdown reason.
*  Output:
*         None
*  Return:
*         None
*  Note  : 底层调用关机接口，启用定时器，上报事件给应用。
*          超时时间内应用不关机，由底层强制关机。
********************************************************************************/
void drv_shut_down( DRV_SHUTDOWN_REASON_E enReason )
{
#ifdef CONFIG_BALONG_ONOFF
	power_off_ctrl.off_timer.func = (softtimer_func)power_off_timeout_isr;
    if( DRV_SHUTDOWN_CHARGE_REMOVE == enReason )
    {
        if( DRV_START_MODE_NORMAL == bsp_start_mode_get() )
        {
            /* In normal mode, don't handle the charge remove message */
            return ;
        }
    }

    if( DRV_SHUTDOWN_BUTT == enReason )
    {
        return ; /* the shutdown been handled, ignore this call */
    }

    /* save the reason and drv_power_off need it */
    power_off_ctrl.reason = enReason;

	power_off_ctrl.off_timer.para = (u32)0;
	power_off_ctrl.off_timer.timeout = POWER_OFF_MONOTER_TIMEROUT;
	power_off_ctrl.off_timer.wake_type = SOFTTIMER_WAKE;

    if (bsp_softtimer_create(&power_off_ctrl.off_timer))
    {
        pr_dbg("create softtimer failed \n");
    }

    bsp_softtimer_add(&power_off_ctrl.off_timer);

    /* 针对由底层上报关机事件，由应用执行关机的场景 */
    /* TO DO */

    //power_off_log_save();
#else
    if (DRV_SHUTDOWN_RESET == enReason)
    {
        pr_dbg("drv_shut_down is called, modem reset...");

        system_error(DRV_ERROR_USER_RESET, 0, 0, NULL, 0);
    }
#endif
    /* Notify the monitor task */
}

/******************************************************************************
*  Function:  bsp_drv_power_off
*  Description: same as drv_power_off, the public API
*  Input:
*         None
*  Output:
*         None
*  Return:
*         None
*  Note  : 应用调用关机时调用，at+cfun=8
********************************************************************************/
void bsp_drv_power_off( void )
{
#ifdef CONFIG_BALONG_ONOFF
    if(power_off_ctrl.reason == DRV_SHUTDOWN_BUTT)
    {
        /*Set shutdown reason to Power_key.*/
        power_off_ctrl.reason = DRV_SHUTDOWN_POWER_KEY;

        pr_dbg( "power off process triggered by a-cpu with power_key\n");
        //power_off_log_save();
    }

    drv_power_off();
#else
    printk(KERN_ERR"we will do nothing...\n");
#endif
}

/******************************************************************************
*  Function:  bsp_drv_power_reboot
*  Description: same as drv_power_off, the public API
*  Input:
*         None
*  Output:
*         None
*  Return:
*         None
*  Note  : 应用调用重启时调用，at+cfun=6
********************************************************************************/
void bsp_drv_power_reboot( void )
{
#ifdef CONFIG_BALONG_ONOFF
    /*Set shutdown reason to reset.*/
    power_off_ctrl.reason = DRV_SHUTDOWN_RESET;

    pr_dbg( "power reboot process triggered \n");
    //power_off_log_save();

    power_on_wdt_cnt_set();

    power_off_set_flag_and_reboot((power_off_reboot_flag)(power_off_ctrl.reason));
#else
    printk(KERN_ERR"bsp_drv_power_reboot is called, modem reset...\n");

    system_error(DRV_ERROR_USER_RESET, 0, 0, NULL, 0);
#endif
}

void mdrv_sysboot_restart(void)
{
	bsp_om_save_reboot_log(__FUNCTION__, __builtin_return_address(0));
	bsp_drv_power_reboot();
}


/******************************************************************************
*  Function:  bsp_drv_power_reboot_direct
*  Description:
*  Input:
*         None
*  Output:
*         None
*  Return:
*         None
*  Note  : 直接重启
********************************************************************************/
void bsp_drv_power_reboot_direct( void )
{
#ifdef CONFIG_BALONG_ONOFF
    power_off_reboot_operation();
#else
    printk(KERN_ERR"bsp_drv_power_reboot_direct is called, modem reset...\n");

    system_error(DRV_ERROR_USER_RESET, 0, 0, NULL, 0);
#endif
}

/******************************************************************************
*  Function:  balong_power_restart
*  Description: same as bsp_drv_power_reboot, 系统调用时使用
*  Input:
*         None
*  Output:
*         None
*  Return:
*         None
*  Note  :android_reboot(ANDROID_RB_RESTART, 0, 0);
********************************************************************************/
/*lint -save -e958 */
void balong_power_restart(char mode, const char *cmd)
{
	bsp_om_save_reboot_log(__FUNCTION__, __builtin_return_address(0));
    bsp_drv_power_reboot();
}
EXPORT_SYMBOL_GPL(balong_power_restart);
/*lint -restore */

/******************************************************************************
*  Function:  balong_power_off
*  Description: same as bsp_drv_power_off, 系统调用时使用
*  Input:
*         None
*  Output:
*         None
*  Return:
*         None
*  Note  :android_reboot(ANDROID_RB_POWER_OFF, 0, 0);
********************************************************************************/
void balong_power_off( void )
{
	bsp_om_save_reboot_log(__FUNCTION__, __builtin_return_address(0));
	bsp_drv_power_off();
}
EXPORT_SYMBOL_GPL(balong_power_off);

#ifdef CONFIG_BALONG_ONOFF
/******************************************************************************
*  Function:  debug命令
*  Description: 内部调试时使用
*  Input:
*         None
*  Output:
*         None
*  Return:
*         None
*  Note  :
********************************************************************************/
void bsp_power_reboot_boot( void )
{
   power_reboot_cmd_set(POWER_REBOOT_CMD_BOOTLOADER);
   power_off_set_flag_and_reboot(POWER_OFF_REASON_RESET);
}

void bsp_power_reboot_recovery( void )
{
   power_reboot_cmd_set(POWER_REBOOT_CMD_RECOVERY);
   power_off_set_flag_and_reboot(POWER_OFF_REASON_RESET);
}

void bsp_power_reboot_warm( void )
{
   power_reboot_cmd_set(POWER_REBOOT_CMD_WARMRESET);
   power_off_set_flag_and_reboot(POWER_OFF_REASON_RESET);
}
#endif


void mdrv_sysboot_shutdown(void)
{
	bsp_om_save_reboot_log(__FUNCTION__, __builtin_return_address(0));
	drv_shut_down(DRV_SHUTDOWN_TEMPERATURE_PROTECT);
}



