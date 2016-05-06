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

#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/of.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <sys_bus_core.h>
#include <sys_edma.h>
#include <sys_acore.h>
#include <sys_ipf.h>
#include <sys_hdlc/sys_hdlc.h>
#include <sys_socp.h>
#include <sys_bus_pressure.h>
#include <sys_lcd.h>

extern struct sys_bus *g_sysbus;
struct bus_pressure* g_bus_pressure;

static LIST_HEAD(master_head);


static struct of_device_id bus_pressure_ids[] = {

    {.compatible = "bus_pressure, edma", .data = sys_edma_init},
    {.compatible = "bus_pressure, acore", .data = sys_acore_init},
#ifdef CONFIG_FB_EMI_BALONG
	{.compatible = "bus_pressure, lcd", .data = sys_lcd_init},
#endif
	{.compatible = "bus_pressure, ipf", .data = sys_ipf_init},
	{.compatible = "bus_pressure, hdlc", .data = sys_hdlc_init},
    {.compatible = "bus_pressure, socp", .data = sys_socp_init},
    {},
};

typedef void(*master_of_init_fn)(struct master*);

void bus_pressure_init(struct sys_bus *sysbus, struct device_node * pressure_np)
{
    const struct of_device_id *match;
    struct master* master;
    master_of_init_fn init_func;
    struct device_node *np;
    struct bus_pressure* bus_pressure;

    np = pressure_np;
    for_each_matching_node_and_match(np, bus_pressure_ids, &match)
    {
        master = kzalloc(sizeof(struct master), GFP_KERNEL);
        if (!master)
        {
            sys_bus_trace("failed to allocate master!");
            return;
        }
        master->np = np;
        init_func = match->data;
        init_func(master);
        list_add_tail(&master->entry, &master_head);
    }

    bus_pressure = kzalloc(sizeof(struct bus_pressure), GFP_KERNEL);
	if (!bus_pressure)
    {
		sys_bus_trace("failed to allocate bus_pressure!\n");
		return ;
	}

    bus_pressure->of_node = pressure_np;
    bus_pressure->start = bus_pressure_start;
    bus_pressure->stop = bus_pressure_stop;
    bus_pressure->enable = NULL;//bus_pressure_enable;
    bus_pressure->disable = NULL;//bus_pressure_disable;
    bus_pressure->record = bus_pressure_record;
    bus_pressure->report = bus_pressure_report;
    //bus_pressure->result_len = 0;

    sysbus->bus_pressure = (void*)bus_pressure;
    g_bus_pressure = bus_pressure;
}

void bus_pressure_start(void)
{
    struct master *master;

    list_for_each_entry(master, &master_head, entry)
    {
        if (master->start)
            master->start(master);
    }
}
EXPORT_SYMBOL(bus_pressure_start);

void bus_pressure_stop(void)
{
    struct master *master;

    list_for_each_entry(master, &master_head, entry)
    {
        if (master->stop)
            master->stop(master);
    }
}
EXPORT_SYMBOL(bus_pressure_stop);

void bus_pressure_record(void)
{
    struct master *master;

    list_for_each_entry(master, &master_head, entry)
    {
        if (master->record)
            master->record(master);
    }
}
EXPORT_SYMBOL(bus_pressure_record);


void bus_pressure_report(void)
{
    struct master *master;

    list_for_each_entry(master, &master_head, entry)
    {
        if (master->report)
            master->report(master);
    }
}
EXPORT_SYMBOL(bus_pressure_report);


