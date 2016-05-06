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
#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/mm.h>
#include <linux/interrupt.h>
#include <linux/kthread.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/timer.h>

#include <linux/workqueue.h>
#include <linux/irq.h>
#include <linux/gpio.h>

#include <RfNvId.h>
#include "bsp_om.h"
#include "bsp_nvim.h"
#include "drv_nv_id.h"
#include "drv_nv_def.h"
#include "bsp_memmap.h"
#include "bsp_icc.h"
#include "hi_anten.h"
/*lint -restore */

#define ANTEN_OK                       (0)
#define ANTEN_ERROR                    (-1)
#define IRQ_TRIGGER_TYPE               (IRQF_SHARED | IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING)
#define ANTEN_MAX_NUM                  (2)
#define DRIVER_NAME                    "anten_balong"

#define anten_print_error(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ANTEN, "[anten]: <%s> <%d> "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__))
#define anten_print_info(fmt, ...)     (bsp_trace(BSP_LOG_LEVEL_ERROR,  BSP_MODU_ANTEN, "[anten]: "fmt, ##__VA_ARGS__))

struct gpio_anten;

struct anten_data
{
    unsigned int modem_id;
    unsigned int gpio;
    unsigned int status;
    unsigned int is_debounce;
    unsigned int timer_debounce;    /* in msecs */

    struct gpio_anten *anten;
    struct timer_list  timer;
};

struct gpio_anten
{
    unsigned int      chan_id;
    unsigned int      n_anten;
    struct anten_data data[0];

};

struct anten_msg_stru
{
    unsigned int modem_id;
    unsigned int status;
};

struct anten_platform_data{

    unsigned int modem_gpio[ANTEN_MAX_NUM];

};

void anten_handle_work(struct anten_data *data)
{
    int len = 0;

    struct gpio_anten *   anten = NULL;
    struct anten_msg_stru anten_msg ;

    anten = data->anten;/*lint !e413*/

    /*lint -save -e413*/
    anten_msg.modem_id = data->modem_id;
    anten_msg.status = data->status;
    anten_print_info("modem id = 0x%x, status = %d.\n", anten_msg.modem_id, anten_msg.status);

    /*通过IFC将消息发出*/
    len = bsp_icc_send(ICC_CPU_MODEM, anten->chan_id, (unsigned char*)&anten_msg, (u32)sizeof(struct anten_msg_stru));
    if(len != sizeof(struct anten_msg_stru))
    {
        anten_print_error("send len(%d) != expected len.\n", len);
        return;
    }
    /*lint -restore*/
}


static void gpio_antens_gpio_timer(unsigned long _data)
{
    struct anten_data *bdata = (struct anten_data *)_data;
    int status = gpio_get_value((unsigned)(bdata->gpio));

    if(((0 == bdata->status) && (1 == status)) || ((1 == bdata->status) && (0 == status)))
    {
        bdata->status = status;
        anten_handle_work(bdata);
    }  
    
    bdata->is_debounce = 0;

}


static irqreturn_t anten_irq_handle(int irq, void *dev_id)
{
    struct anten_data *data = (struct anten_data *)dev_id;
    int status = 0;

    status = gpio_get_value(data->gpio);
    
    if(data->timer_debounce && (data->status != status) && (0 == data->is_debounce))
    {
        data->is_debounce = 1;
        mod_timer(&data->timer, jiffies + msecs_to_jiffies(data->timer_debounce));/*考虑fiffies是否会溢出*/
    }

    return IRQ_HANDLED;
}

static int setup_gpio_anten(RF_ANTEN_DETECT_GPIO_STRU *pdata,
                            unsigned int i,
                            struct anten_data *bdata,
                            struct gpio_anten *anten)
{
    int value = 0;

    if( ANT_DETECT_STUB_GPIO == pdata->anten[i])
    {
        return 0;
    }

    bdata->gpio = pdata->anten[i];
    if(gpio_request(bdata->gpio, DRIVER_NAME))
    {
        anten_print_error("request gpio%d is error!\n", bdata->gpio);
        return -1;
    }

    if(gpio_direction_input(bdata->gpio)){
        anten_print_error("gpio  direction input error!\n");
    }

    bdata->is_debounce = 0;
    bdata->timer_debounce = 20UL;

    value = gpio_get_value(bdata->gpio);
    if (value)
    {
        bdata->status = 1;
    }
    else
    {
        bdata->status = 0;
    }

    bdata->modem_id = i;

    bdata->anten = anten;

    setup_timer(&bdata->timer, gpio_antens_gpio_timer, (unsigned long)bdata);
    
    /*conncet anten interrupt*/
    if(request_irq(gpio_to_irq(bdata->gpio), anten_irq_handle, IRQ_TRIGGER_TYPE, DRIVER_NAME, bdata))
    {
        anten_print_error("request anten gpio irq is error!\n");
        goto irq_error;
    }
    anten_print_error("set up ant dect%d,gpio %d,modem id %d\n",i,bdata->gpio,i);
    return 0;

irq_error:
    gpio_free(bdata->gpio);

    return -1;

}

static int __init hi_anten_init(void)
{
    int ret = 0;
    unsigned int i = 0;

    struct gpio_anten *anten;
    RF_ANTEN_DETECT_GPIO_STRU anten_stru;

    memset((void*)&anten_stru, 0, sizeof(RF_ANTEN_DETECT_GPIO_STRU));

    /* Get ANTEN NV data by id.*/
    ret = bsp_nvm_read(en_NV_Item_RF_ANT_DETECT,(u8*)&anten_stru,sizeof(RF_ANTEN_DETECT_GPIO_STRU));
    if (ret !=  0)
    {
        anten_print_error("anten_gpio read NV=0x%x, ret = %d \n",en_NV_Item_RF_ANT_DETECT, ret);
        return -1;
    }

    anten = kzalloc((size_t)(sizeof(struct gpio_anten) + ANTEN_MAX_NUM * sizeof(struct anten_data)), GFP_KERNEL);
    if(!anten) {
        anten_print_error("no memory for alloc.\n");
        ret = ANTEN_ERROR;
        goto mem_error;
    }

    anten->chan_id = ICC_CHN_IFC << 16 | IFC_RECV_FUNC_ANTEN;

    for(i = 0U;i < ANTEN_MAX_NUM;i++)
    {
        if(0 != setup_gpio_anten(&anten_stru, i, &(anten->data[i]), anten))
        {
            goto setup_error;
        }
    }


    anten_print_info( " anten init over.\n");
    return ANTEN_OK;

setup_error:

    kfree(anten);

mem_error:
    return ret;

}

 
module_init(hi_anten_init);
MODULE_AUTHOR("Hisilicon Drive Group");
MODULE_DESCRIPTION("anten driver for the Hisilicon anten plug in/out");
MODULE_LICENSE("GPL");

