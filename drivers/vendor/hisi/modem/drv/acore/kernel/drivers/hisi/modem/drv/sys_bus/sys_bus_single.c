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
#include <linux/slab.h>
#include <linux/types.h>

#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/debugfs.h>
#include <bsp_icc.h>
#include <sys_bus_core.h>
#include <sys_bus_single.h>

static LIST_HEAD(list_result_head);

struct bus_single *g_bus_single = NULL;

const char * g_bus_single_propname[]= {
    "bus_single_tcm0",
    "bus_single_tcm1",
};

void bus_single_log(struct bus_single *bus_single, const char *fmt, ...)
{
    char* buf = bus_single->result_buf;
    u32 len = bus_single->result_len;
    va_list args;

    va_start(args, fmt);
    len += vsnprintf(buf+len, MAX_SINGLE_BUF_SIZE, fmt, args);
    va_end(args);

    bus_single->result_len = len;
}

void bus_single_msg_handle(struct bus_single *bus_single, void *msg)
{
    struct sys_msg *sysmsg = (struct sys_msg *)msg;
    switch(sysmsg->type)
    {
        case 2://result
            if(sysmsg->len > 0)
            {
                memcpy(bus_single->result_buf, sysmsg->data, sysmsg->len);
                bus_single->result_len += sysmsg->len;
            }
            break;
        default:
            break;
    }
}

void bus_single_app_a9(struct bus_single *bus_single)
{
	struct device_node *np = bus_single->of_node;
    struct single_value value;
    struct single_result* single_result;
    u32 i = 0;
    void __iomem *base = NULL;
    int ret;

    sys_bus_trace("bus single test app_a9 start:\n");
    bus_single_log(bus_single, "bus_single acore:");
    for(i=0;i<(sizeof(g_bus_single_propname)/sizeof(char*));i++)
    {
        ret = of_property_read_u32_array(np, g_bus_single_propname[i], (u32*)&value, 4);
        if(ret)
        {
		    break;
	    }
        single_result = kzalloc(sizeof(struct single_result), GFP_KERNEL);
        if (!single_result)
        {
            sys_bus_trace("kzalloc error\n");
            return;
        }
        single_result->name = (char*)g_bus_single_propname[i];
        base = ioremap(value.start, value.size);
        if (!base)
        {
            sys_bus_trace("%s ioremap error\n", g_bus_single_propname[i]);
            single_result->result = 0;
            kfree(single_result);
    		return;
    	}

        writeb(magic_num_u8, base+value.woffset);
        if(readb(base+value.roffset) != magic_num_u8)
        {
            sys_bus_trace("%s 8bit wr error\n", g_bus_single_propname[i]);
            single_result->result = 0;
            break;
        }
        writew(magic_num_u16, base+value.woffset);
        if(readw(base+value.roffset) != magic_num_u16)
        {
            sys_bus_trace("%s 16bit wr error\n", g_bus_single_propname[i]);
            single_result->result = 0;
            break;
        }
        writel(magic_num_u32, base+value.woffset);
        if(readl(base+value.roffset) != magic_num_u32)
        {
            sys_bus_trace("%s 32bit wr error\n", g_bus_single_propname[i]);
            single_result->result = 0;
            break;
        }
        single_result->result = 1;
        //list_add(&single_result->entry, &list_result_head);
        if(single_result->result == 0)
        {
            //bus_single->result_len += sprintf(bus_single->result_buf+bus_single->result_len, "%s is error\n", single_result->name);
            bus_single_log(bus_single, "%s is error\n", single_result->name);
        }
        else
        {
            //bus_single->result_len += sprintf(bus_single->result_buf+bus_single->result_len, "%s is ok\n", single_result->name);
            bus_single_log(bus_single, "%s is ok\n", single_result->name);
        }
        iounmap(base);
    }
    sys_bus_trace("bus single test app_a9 end\n");
    bus_single_log(bus_single, "\n");
}

void sys_icc_send(struct sys_bus *sys_bus, u32 cpuid, struct sys_msg* msg)
{
	u32 channel_id = sys_bus->channel_id;
	s32 ret = 0;
    u32 msglen = sizeof(msg);

	ret = bsp_icc_send(cpuid, channel_id, (u8*)&msg, msglen);
	if(ret != msglen)
	{
		sys_bus_trace("send_ccore err\n");
		return;
	}
}

void bus_single_mdm_a9(struct bus_single *bus_single)
{
    struct sys_bus *sys_bus = single_to_sys_bus((void*)bus_single);
    struct sys_msg msg;

    msg.module = E_SYS_MODULE_SINGLE;
    msg.type = 1;

    sys_icc_send(sys_bus, ICC_CPU_MODEM, &msg);
}

void bus_single_lpm3(struct bus_single *bus_single)
{
    struct sys_bus *sys_bus = single_to_sys_bus((void*)bus_single);
    struct sys_msg msg;

    msg.module = E_SYS_MODULE_SINGLE;
    msg.type = 1;

    sys_icc_send(sys_bus, ICC_CPU_MCU, &msg);
}

void bus_single_start(struct bus_single *bus_single)
{
    if(bus_single->enflag)
    {
        bus_single_app_a9(bus_single);
        bus_single_mdm_a9(bus_single);
        bus_single_lpm3(bus_single);
    }
}

void bus_single_stop(void)
{
}

void bus_single_enable(struct bus_single *bus_single)
{
    bus_single->enflag = 1;
}

void bus_single_disable(struct bus_single *bus_single)
{
    bus_single->enflag = 0;
}

void bus_single_report(struct bus_single *bus_single)
{
    char* buf = bus_single->result_buf;
    u32 len  = bus_single->result_len;
    buf[len] = '\0';
    printk("%s\n", bus_single->result_buf);
}

void bus_single_init(struct sys_bus *sysbus, struct device_node * single_np)
{
    struct bus_single* bus_single;

    bus_single = kzalloc(sizeof(struct bus_single), GFP_KERNEL);
	if (!bus_single)
    {
		sys_bus_trace("failed to allocate g_sysbus!\n");
		return ;
	}
    bus_single->result_buf = kzalloc(MAX_SINGLE_BUF_SIZE, GFP_KERNEL);
	if (!bus_single->result_buf)
    {
		sys_bus_trace("failed to allocate g_sysbus!\n");
		goto errout1;
	}

    bus_single->of_node = single_np;
    bus_single->start = bus_single_start;
    bus_single->stop = NULL;
    bus_single->enable = bus_single_enable;
    bus_single->disable = bus_single_disable;
    bus_single->record = NULL;
    bus_single->report = bus_single_report;
    bus_single->result_len = 0;

    sysbus->bus_single = (void*)bus_single;
    g_bus_single = bus_single;
    return;

errout1:
    kfree(bus_single);
}



