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

#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/printk.h>
#include <linux/gpio.h>
#include <linux/module.h>
#include <linux/clk.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <linux/regulator/consumer.h>

#include "product_config.h"
#include "osl_bio.h"
#include "osl_sem.h"
#include "osl_thread.h"
#include "osl_wait.h"
#include "osl_spinlock.h"
#include "soc_clk.h"
#include "hi_efuse.h"
#include "bsp_memmap.h"

#include "bsp_icc.h"
#include "bsp_hardtimer.h"
#include "bsp_om.h"
#include "bsp_efuse.h"

#ifdef HI_K3_EFUSE
#include <mdrv.h>
#include "../../adrv/adrv.h"
#endif

struct work_struct efuse_work;

EFUSE_DATA_STRU efuse_msg ;

EFUSE_DEBUG_INFO efuse_debug_info;

int efuse_debug_flag = 0;

void efuse_handle_work(struct work_struct *work)
{
    u32 i = 0;
    int length = 0;
    u32 channel_id = ICC_CHN_IFC << 16 | IFC_RECV_FUNC_EFUSE;
    EFUSE_DATA_STRU *msg = &efuse_msg;

    efuse_debug_info.rw_start_stamp = bsp_get_slice_value();

    if(EFUSE_READ == (u32)msg->opt)
    {
        if(1 == efuse_debug_flag)
        {
            pr_info("efuse read start group %d length %d.\n", msg->start, msg->len);
        }
#ifdef HI_K3_EFUSE
    if (msg->start == EFUSE_GRP_HUK)
        msg->ret = get_efuse_kce_value((unsigned char *)msg->buf, (unsigned int)msg->len * 4, 0);
    else
        msg->ret = -1;
#else
        msg->ret = bsp_efuse_read(msg->buf, msg->start,msg->len);
#endif
        if(1 == efuse_debug_flag)
        {
            pr_info("efuse read end group %d length %d.\n", msg->start, msg->len);
            for(i = 0;i < msg->len;i++)
            {
                pr_info("efuse buf[%d] is 0x%x.\n", i, msg->buf[i]);
            }
            pr_info("efuse read ret %d\n", msg->ret);
        }
    }
    else if(EFUSE_WRITE == (u32)msg->opt)
    {
        if(1 == efuse_debug_flag)
        {
            pr_info("efuse write start group %d length %d.\n", msg->start, msg->len);
            for(i = 0;i < msg->len;i++)
            {
                pr_info("efuse buf[%d] is 0x%x.\n", i, msg->buf[i]);
            }
        }
#ifdef HI_K3_EFUSE
    if (msg->start == EFUSE_GRP_HUK)
        msg->ret = set_efuse_kce_value((unsigned char *)msg->buf, (unsigned int)msg->len * 4, 0);
    else
        msg->ret = -1;
#else
        msg->ret = bsp_efuse_write(msg->buf, msg->start,msg->len);
#endif
        if(1 == efuse_debug_flag)
        {
            pr_info("efuse write ret %d.\n", msg->ret);
        }

    }
    else
    {
        msg->ret = EFUSE_ERROR;
    }

    efuse_debug_info.rw_end_stamp = bsp_get_slice_value();

    length = bsp_icc_send(ICC_CPU_MODEM, channel_id, (unsigned char*)msg, sizeof(EFUSE_DATA_STRU));
    if(length != (int)sizeof(EFUSE_DATA_STRU))
    {
        efuse_print_error("send len(%x) != expected len(%x).\n", length, sizeof(EFUSE_DATA_STRU));
        return;
    }

    efuse_debug_info.icc_send_stamp = bsp_get_slice_value();
}

void bsp_efuse_data_receive(void)
{
    int length = 0;
    u32 channel_id = ICC_CHN_IFC << 16 | IFC_RECV_FUNC_EFUSE;

	length = bsp_icc_read(channel_id, (u8*)&efuse_msg, sizeof(EFUSE_DATA_STRU));
	if(length != (int)sizeof(EFUSE_DATA_STRU))
	{
		efuse_print_error("read len(%x) != expected len(%x).\n", length, sizeof(EFUSE_DATA_STRU));
		return;
	}

    efuse_debug_info.icc_callback_stamp = bsp_get_slice_value();

    schedule_work(&efuse_work);
}

static int __init hi_efuse_comm_init(void)
{
    int ret = 0;
    u32 chan_id = ICC_CHN_IFC << 16 | IFC_RECV_FUNC_EFUSE;

	INIT_WORK(&efuse_work, efuse_handle_work);

    memset((void*)&efuse_debug_info, 0, sizeof(efuse_debug_info));

    ret = bsp_icc_event_register(chan_id, (read_cb_func)bsp_efuse_data_receive, NULL, NULL, NULL);
    if(0 != ret)
    {
        efuse_print_error("efuse icc register is error.\n");
        return EFUSE_ERROR;
    }

    efuse_print_info("efuse comm init ok.\n");

    return EFUSE_OK;

}

static void __exit hi_efuse_comm_exit(void)
{
    /* do nothing */
}

module_init(hi_efuse_comm_init);
module_exit(hi_efuse_comm_exit);
MODULE_AUTHOR("Hisilicon Drive Group");
MODULE_DESCRIPTION("efuse comm driver for the Hisilicon anten plug in/out");
MODULE_LICENSE("GPL");


