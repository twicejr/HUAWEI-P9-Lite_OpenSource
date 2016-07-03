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
/******************************************************************************
  File Name       : loadm.c
  Description     : load modem image(ccore image),run in ccore
  History         :
******************************************************************************/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/err.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <linux/jiffies.h>
#include <linux/kthread.h>

#include "product_config.h"
#include "bsp_memmap.h"
#include <bsp_shared_ddr.h>
#include "load_image.h"

static int __init his_modem_probe(struct platform_device *pdev)
{
    int ret = 0;

    printk(KERN_ERR"his_modem_probe.\n");

	ret = bsp_load_modem_images();
    if(SEC_OK == ret)
    {
        printk(KERN_ERR "load ccore image succeed\n");
    }
    else
    {
        printk(KERN_ERR"load ccore image failed\n");
        return -EAGAIN;
    }

    /*在MBB平台上需要发送复位请求中断*/
    ret = bsp_load_notify_ccpu_start();
    if (ret)
    {
        printk(KERN_ERR"send ipc to unreset ccore failed, ret=0x%x\n", ret);
    }
    else
    {
        printk(KERN_ERR"send ipc to unreset ccore succeed\n");
    }

    return ret;

}

static struct platform_device his_modem_device = {
    .name = "his_modem",
    .id = 0,
    .dev = {
    .init_name = "his_modem",
    },
};
static struct platform_driver his_modem_drv = {
    .probe      = his_modem_probe,
    .driver     = {
        .name     = "his_modem",
        .owner    = THIS_MODULE,
    },
};

static int __init his_modem_init_driver(void)
{
    int ret = 0;

    ret = platform_device_register(&his_modem_device);
    if(ret)
    {
        printk(KERN_ERR"register his_modem device failed\n");
        return ret;
    }

    ret = platform_driver_register(&his_modem_drv);
    if(ret)
    {
        printk(KERN_ERR"register his_modem driver failed\n");
        platform_device_unregister(&his_modem_device);
    }

    return ret;

}

module_init(his_modem_init_driver);
//module_exit(his_modem_exit_driver);

MODULE_DESCRIPTION("HIS Balong  Modem load ");
MODULE_LICENSE("GPL");

