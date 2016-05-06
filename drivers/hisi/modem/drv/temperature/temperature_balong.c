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
/*lint -save -e537*/
#include <linux/errno.h>
#include <linux/spinlock.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/irq.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/power_supply.h>
#include <bsp_shared_ddr.h>

#include "osl_common.h"

#include "bsp_icc.h"
#include "mdrv_temp_cfg.h"
#include "bsp_hardtimer.h"
#include "bsp_temperature.h"
/*lint -restore */

#define DEVICE_ID_TEMP                   10

/* typedef void (*TEM_FUNCPTR)(unsigned int device_id, unsigned int event_id); */

TEM_FUNCPTR p_tem_fun = NULL;

DRV_HKADC_DATA_AREA *g_temperature_data;

s32 bsp_tem_protect_callback_register(TEM_FUNCPTR p)
{
    if(NULL == p)
    {
        tem_print_error("TEM_FUNCPTR is null.\n");
        return TEMPERATURE_ERROR;
    }

    p_tem_fun = p;

    return TEMPERATURE_OK;
}
EXPORT_SYMBOL_GPL(bsp_tem_protect_callback_register);
s32 bsp_tem_data_receive(void)
{
    int len = 0;
    unsigned status = 0;
    unsigned region = 0;

    struct tem_msg_stru msg = {0};
    u32 channel_id = ICC_CHN_MCORE_ACORE << 16 | MCORE_ACORE_FUNC_TEMPERATURE;

	len = bsp_icc_read(channel_id, (u8*)&msg, sizeof(struct tem_msg_stru));
	if(len != (int)sizeof(struct tem_msg_stru))
	{
		tem_print_error("read len(%x) != expected len(%x).\n", len, sizeof(struct tem_msg_stru));
		return TEMPERATURE_ERROR;
	}

    if(msg.id != channel_id)
    {
		tem_print_error("msg id(%d) != expected channel_id(%d).\n", msg.id, channel_id);
		return TEMPERATURE_ERROR;
    }

	region = msg.region;
	status = msg.status;

    tem_print_info("temperature region = %d, status = %d.\n", region, status);

    /*POWER_SUPPLY数据上报*/
    if(HKADC_BATTERY == region && (HIGH_TEMPERATURE == status) && (NULL != p_tem_fun))
    {
        (*p_tem_fun)(DEVICE_ID_TEMP, POWER_SUPPLY_HEALTH_DEAD);
    }
    else if(HKADC_BATTERY == region && (LOW_TEMPERATURE == status) && (NULL != p_tem_fun))
    {
        (*p_tem_fun)(DEVICE_ID_TEMP, POWER_SUPPLY_HEALTH_COLD);
    }


    return TEMPERATURE_OK;
}


/*****************************************************************************
 * 函 数 名  :bsp_temperature_init
 *
 * 功能描述  : 温度保护核间通信，A核初始化函数
 *
 * 输入参数  : 无
 * 输出参数  : 无
 *
 * 返 回 值  : TEMPERATURE_OK:    操作成功
 *             TEMPERATURE_ERROR: 操作失败
 *
 * 其它说明  : 无
 *
 *****************************************************************************/
static int __init bsp_temperature_init(void)
{
    int ret = 0;
    u32 chan_id = ICC_CHN_MCORE_ACORE << 16 | MCORE_ACORE_FUNC_TEMPERATURE;
    g_temperature_data = (DRV_HKADC_DATA_AREA *)TEMPERATURE_VIRT_ADDR;

    //printk("acore tem time %d.\n", bsp_get_elapse_ms());

    ret = bsp_icc_event_register(chan_id, (read_cb_func)bsp_tem_data_receive, NULL, NULL, NULL);
    if(0 != ret)
    {
        tem_print_error("register is error, %d.\n", ret);
        return TEMPERATURE_ERROR;
    }

    tem_print_info("temperature init is ok.\n");

    return TEMPERATURE_OK;
}

#if 0
static void __exit bsp_temperature_exit(void)
{
    tem_print_info("temperature exit is ok.\n");
}
module_exit(bsp_temperature_exit);

#endif
module_init(bsp_temperature_init);
MODULE_AUTHOR("Hisilicon Drive Group");
MODULE_DESCRIPTION("temperature driver for the Hisilicon");
MODULE_LICENSE("GPL");

