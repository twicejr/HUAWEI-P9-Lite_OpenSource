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

#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/kthread.h>
#include <linux/slab.h>

#include <DrvInterface.h>
#include <hifidrvinterface.h>

#include <bsp_ipc.h>
#include <bsp_icc.h>
#include <bsp_dump.h>
#include <bsp_dsp.h>
#include <bsp_reset.h>
#include "reset_balong.h"

void show_reset_control(void)
{
	struct modem_reset_ctrl *reset_control = bsp_reset_control_get();

	if(NULL == reset_control)
	{
		reset_print_err("null pointer\n");
		return;
	}

	printk("**********************************\n");
	printk("boot_mode:            0x%x\n", reset_control->boot_mode);
	printk("modem_action:         0x%x\n", reset_control->modem_action);
	printk("multicore_msg_switch: 0x%x\n", reset_control->multicore_msg_switch);
}

void show_cb_list(void)
{
	struct modem_reset_ctrl *reset_control = NULL;
	struct reset_cb_list *p = NULL;
	u32 i = 0;

	reset_control = bsp_reset_control_get();
	if(NULL != reset_control)
	{
		p = reset_control->list_head;
	}
	else
	{
	}

	while (NULL != p)
    {
		printk("****************node%d****************\n", i++);
        printk("name: %s\n", p->cb_info.name);
		printk("prio: 0x%x\n", p->cb_info.priolevel);
		printk("func: 0x%x\n", (u32)p->cb_info.cbfun);
		printk("data: 0x%x\n", p->cb_info.userdata);
        p = p->next;
    }
}

s32 drv_reset_cb_test (DRV_RESET_CALLCBFUN_MOMENT stage, int userdata)
{
	reset_print_err("this is just stub at stage%d, userdata=0x%d\n", stage, userdata);
	return RESET_OK;
}

s32 oam_reset_cb_test (DRV_RESET_CALLCBFUN_MOMENT stage, int userdata)
{
	reset_print_err("this is just stub at stage%d, userdata=0x%d\n", stage, userdata);
	return RESET_OK;
}

s32 ttf_reset_cb_test (DRV_RESET_CALLCBFUN_MOMENT stage, int userdata)
{
	reset_print_err("this is just stub at stage%d, userdata=0x%d\n", stage, userdata);
	return RESET_OK;
}

s32 reset_test_reg_cb_001(void)
{
	struct modem_reset_ctrl *reset_control = bsp_reset_control_get();
	s32 ret = 1;

	reset_control->list_head = NULL;

	ret = bsp_reset_cb_func_register("error", NULL, 0, 7);
	if(ret !=  RESET_OK)
	{
		show_cb_list();
		return 0;
	}

	return 1;
}

s32 reset_test_reg_cb_002(void)
{
	struct modem_reset_ctrl *reset_control = bsp_reset_control_get();
	s32 ret = 1;

	reset_control->list_head = NULL;

	ret = bsp_reset_cb_func_register("drv", drv_reset_cb_test, 0, 7);
	if (ret !=  RESET_OK)
	{
		show_cb_list();
		return 0;
	}

	ret = bsp_reset_cb_func_register("error", oam_reset_cb_test, 0, 55);
	if (ret !=  RESET_OK)
	{
		show_cb_list();
		if (NULL == reset_control->list_head)
		{
			return 1;
		}
		return 0;
	}

	show_cb_list();
	return 0;
}

s32 reset_test_reg_cb_003(void)
{
	s32 ret = 1;

	ret = bsp_reset_cb_func_register("drv", drv_reset_cb_test, 0, 7);
	if(ret !=  RESET_OK)
	{
		show_cb_list();
		return 1;
	}
	
	ret = bsp_reset_cb_func_register("oam", oam_reset_cb_test, 0, 20);
	if(ret !=  RESET_OK)
	{
		show_cb_list();
		return 2;
	}

	ret = bsp_reset_cb_func_register("ttf", ttf_reset_cb_test, 0, 9);
	if(ret !=  RESET_OK)
	{
		show_cb_list();
		return 1;
	}

	show_cb_list();
	return 0;
}

void sim_recv_reply1(void)
{
	struct modem_reset_ctrl *reset_control = bsp_reset_control_get();
	if(NULL != reset_control)
	{
		osl_sem_up(&(reset_control->wait_mcore_reply_sem));
		osl_sem_up(&(reset_control->wait_hifi_reply_sem));
	}
	else
	{
		reset_print_err("reset_control pointer is null\n");
	}
}

void sim_recv_reply2(void)
{
	struct modem_reset_ctrl *reset_control = bsp_reset_control_get();
	if(NULL != reset_control)
	{
		osl_sem_up(&(reset_control->wait_ccore_reset_ok_sem));
	}
	else
	{
		reset_print_err("reset_control pointer is null\n");
	}
}

void work_queue_test(void)
{
	bsp_modem_reset();
	bsp_modem_power_off();
	bsp_modem_power_on();
}

void work_queue_test2(void)
{
	bsp_modem_power_off();
	bsp_modem_power_off();
	bsp_modem_power_off();
}

void work_queue_test3(void)
{
	bsp_modem_power_on();
	bsp_modem_power_on();
	bsp_modem_power_on();
}

void work_queue_test4(void)
{
	bsp_modem_reset();
	bsp_modem_reset();
	bsp_modem_reset();
}

void work_queue_test5(void)
{
	bsp_modem_power_off();
	bsp_modem_power_off();
	bsp_modem_power_off();
	bsp_modem_power_on();
}

void work_queue_test6(void)
{
	bsp_modem_power_off();
	bsp_modem_power_on();
	bsp_modem_power_on();
	bsp_modem_power_on();
}

extern void ccore_ipc_enable(void);
extern void ccore_ipc_disable(void);
extern void bsp_ipc_int_mask_status_dump(void);
extern s32 invoke_reset_cb(DRV_RESET_CALLCBFUN_MOMENT stage);
extern struct modem_reset_ctrl g_modem_reset_ctrl;
extern void let_modem_master_in_idle(void);
extern void master_in_ile_timestamp_dump(void);
extern s32 send_msg_to_hifi(DRV_RESET_CALLCBFUN_MOMENT stage);
void test_in_idle(void)
{
	u32 ret = RESET_ERROR;

	ccore_ipc_disable();
	bsp_ipc_int_mask_status_dump();
	/* 设置启动模式为C核单独复位 */
	bsp_reset_bootflag_set(CCORE_IS_REBOOT);
	g_modem_reset_ctrl.boot_mode = readl((volatile const void *)SCBAKDATA13);
	reset_print_debug("(%d) set boot mode:0x%x\n", ++g_reset_debug.main_stage, g_modem_reset_ctrl.boot_mode);

	/* 唤醒ccore */
	ret = bsp_ipc_int_send(IPC_CORE_CCORE, g_modem_reset_ctrl.ipc_send_irq_wakeup_ccore);
	if(ret != 0)
	{
		reset_print_err("wakeup ccore failt\n");
	}

	/* 复位前各组件回调 */
	ret = invoke_reset_cb(DRV_RESET_CALLCBFUN_RESET_BEFORE);
	if(ret < 0)
	{
		return ;
	}

	/* 阻止核间通信 */
	ccore_msg_switch_off(g_modem_reset_ctrl.multicore_msg_switch, CCORE_STATUS);
	reset_print_debug("(%d) switch off msg connect:%d\n", ++g_reset_debug.main_stage, g_modem_reset_ctrl.multicore_msg_switch);

	/* 通知hifi，停止与modem交互 */
	ret = send_msg_to_hifi(DRV_RESET_CALLCBFUN_RESET_BEFORE);
	if(ret < 0)
	{
		reset_print_err("send_msg_to_hifi=0x%x fail\n", ret);
		return ;
	}
	/*  等待hifi处理完成 */
	if (osl_sem_downtimeout(&(g_modem_reset_ctrl.wait_hifi_reply_sem), msecs_to_jiffies((u32)RESET_WAIT_RESP_TIMEOUT)))/*lint !e713 */
	{
		reset_print_err("waiting the reply from hifi timeout(%d)!\n", RESET_WAIT_RESP_TIMEOUT);
		return ;
	}
	reset_print_debug("(%d) has received the reply from hifi\n", ++g_reset_debug.main_stage);

	/* 通知modem master进idle态,并等待ccore回复 */
	let_modem_master_in_idle();
	ret = osl_sem_downtimeout(&(g_modem_reset_ctrl.wait_modem_master_in_idle_sem), 
		msecs_to_jiffies(RESET_WAIT_MODEM_IN_IDLE_TIMEOUT));/*lint !e713 */
	if (ret)
	{
		reset_print_debug("(%d) let modem master in idle timeout\n", ++g_reset_debug.main_stage);
		master_in_ile_timestamp_dump();
	}
	else
	{
		reset_print_debug("(%d) let modem master in idle successfully\n", ++g_reset_debug.main_stage);
	}
}

#ifdef CONFIG_HISI_RPROC

void test_ap_ipc_send(void)
{
	s32 ret = 0;
	u32 ack_val = -1;
	u32 msg = 0;
	msg = RESET_INFO_MAKEUP(0x02, 0x78);
	ret = send_sync_msg_to_mcore(msg, &ack_val);
	printk("ret=0x%x, ack_val=0x%x\n", ret, ack_val);
}

#endif

