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

#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/wait.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/semaphore.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/clk.h>
#include <linux/skbuff.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/of_platform.h>
#include <linux/debugfs.h>
#include <linux/netlink.h>

#include <bsp_icc.h>
#include <sys_bus_single.h>
#include <sys_bus_pressure.h>
#include <sys_bus_core.h>
#include <sys_bus_api.h>

struct sys_bus *g_sysbus = NULL;

typedef void(*sysbus_of_init_fn)(struct sys_bus *, struct device_node *);

static struct of_device_id sys_bus_of_device_ids[] = {
	{.compatible = "sys_bus, bus_single", .data = bus_single_init},
	{.compatible = "sys_bus, bus_pressure",	.data = bus_pressure_init},
	{},
};

void sys_bus_start(void)
{
    struct bus_single* bus_single = (struct bus_single*)g_sysbus->bus_single;
    if(bus_single->start)
    {
        bus_single->start(bus_single);
    }

    //bus_pressure_start();
}

void sys_bus_stop(void)
{


    //bus_pressure_stop();
}

void sys_bus_enable(void)
{
    struct bus_single* bus_single = (struct bus_single*)g_sysbus->bus_single;
    if(bus_single->enable)
    {
        bus_single->enable(bus_single);
    }
}

void sys_bus_disable(void)
{
    struct bus_single* bus_single = (struct bus_single*)g_sysbus->bus_single;
    if(bus_single->disable)
    {
        bus_single->disable(bus_single);
    }
}

void sys_bus_report(void)
{
    struct bus_single* bus_single = (struct bus_single*)g_sysbus->bus_single;

    if(bus_single->report)
    {
        bus_single->report(bus_single);
    }
}

s32 sys_bus_read_cb(u32 id , u32 len, void* context)
{
	s32 ret = 0;
    //unsigned long flags;
    struct sk_buff *skb;
    struct sys_bus *sysbus = (struct sys_bus *)context;

	if(len == 0)
	{
		sys_bus_trace("readcb len is err\n");
        return -1;
	}

    skb = alloc_skb(len, GFP_ATOMIC);
    if(!skb)
    {
        sys_bus_trace("allocate failed\n");
        return -1;
    }

	ret = bsp_icc_read(id, skb->data, len);
	if(len != ret)
	{
		sys_bus_trace("readcb err\n");
		goto errout;
	}

    //spin_lock_irqsave(&sysbus->lock, flags);
    skb_queue_tail(sysbus->skb_head, skb);
    //spin_unlock_irqrestore(&sysbus->lock, flags);
    up(&sysbus->tsk_sema);
    return 0;

errout:
    kfree_skb(skb);
    return -1;

}

void sys_bus_thread(struct sys_bus *sysbus)
{
    struct sk_buff *skb;
    struct sys_msg* msg;
    //unsigned long flags;

    do
    {
        down(&sysbus->tsk_sema);
        //spin_lock_irqsave(&sysbus->lock, flags);
        skb = skb_dequeue(sysbus->skb_head);
        //spin_unlock_irqrestore(&sysbus->lock, flags);
        while(!skb)
        {
            msg = (struct sys_msg*)skb->data;
            switch(msg->module)
            {
                case E_SYS_MODULE_SINGLE:
                    bus_single_msg_handle((struct bus_single *)sysbus->bus_single, (void*)msg);
                    break;
                case E_SYS_MODULE_PRESSURE:
                    break;
                default:
                    break;
            }

        }

    }while(1);
}
static int sys_bus_device_probe(struct platform_device *pdev)
{
	//const struct of_device_id *of_id;
	struct device_node *node = pdev->dev.of_node;
	struct sys_bus *sysbus;
    u32 channel_id = ICC_CHN_IFC << 16 | IFC_RECV_FUNC_SYS_BUS;
    sysbus_of_init_fn init_fn = NULL;
    const struct of_device_id *match;
    struct device_node *np;
	s32 ret = 0;

    sysbus = kzalloc(sizeof(struct sys_bus), GFP_KERNEL);
	if (!sysbus)
    {
		sys_bus_trace("failed to allocate sysbus!\n");
        ret = -1;
	    goto out_free;
	}
    sysbus->skb_head = (struct sk_buff_head *)kzalloc(sizeof(struct sk_buff_head), GFP_ATOMIC);
    if(!sysbus->skb_head)
    {
        sys_bus_trace("alloc skb_head failed\n");
        ret = -1;
        goto errout1;
    }
    skb_queue_head_init(sysbus->skb_head);
    spin_lock_init(&sysbus->lock);
    sema_init(&sysbus->tsk_sema, 0);
	sysbus->tsk =  kthread_run((void*)sys_bus_thread, (void*)sysbus, "sys_bus");
	if (IS_ERR(sysbus->tsk))
	{
		sysbus->tsk = NULL;
		sys_bus_trace("cannot start sys_bus thread\n");
        ret = -1;
		goto errout1;
	}

	ret = bsp_icc_event_register(channel_id, sys_bus_read_cb, (void*)sysbus, (write_cb_func)NULL, (void *)NULL);
	if(ret != ICC_OK)
	{
		sys_bus_trace("icc register error\n");
        ret = -1;
        goto errout2;
	}
    sysbus->channel_id = channel_id;
    np = node;
    for_each_matching_node_and_match(np, sys_bus_of_device_ids, &match)
    {
		init_fn = (sysbus_of_init_fn)match->data;
		init_fn(sysbus, np);
	}

    g_sysbus = sysbus;
	sysbus->plat_device = pdev;
    sys_bus_trace(" ok!\n");
	return 0;

errout2:
    kfree(sysbus->skb_head);
errout1:
    kfree(sysbus);
out_free:
	return ret;
}


static const struct of_device_id sys_bus_dt_match[] = {
	{ .compatible = "hisilicon,sys_bus" },
	{},
};
MODULE_DEVICE_TABLE(of, sys_bus_dt_match);


static struct platform_driver sys_bus_driver = {
	.driver		= {
		.name	= "sys_bus",
		.of_match_table = sys_bus_dt_match,
	},
	.probe		= sys_bus_device_probe,
};

static int __init register_sysbus_driver(void)
{
	int err;

	err = platform_driver_register(&sys_bus_driver);
	if (err)
    {
        printk(KERN_ERR "platform_driver_register err = %d\n", err);
        return err;
	}

	return 0;
}
late_initcall(register_sysbus_driver);

