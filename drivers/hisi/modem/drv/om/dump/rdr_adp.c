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

#ifdef __cplusplus
extern "C"
{
#endif

#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/thread_info.h>
#include <linux/syslog.h>
#include <linux/errno.h>
#include <linux/kthread.h>
#include <linux/semaphore.h>
#include <linux/delay.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include "rdr_adp.h"
#include "bsp_dump.h"
#include "bsp_dump_drv.h"

#ifndef CONFIG_HISI_BB //rdr build config
struct rdr_adp_ctrl_s   g_st_adp_ctrl;
u32 g_ul_adp_init_flag = false;

u32 rdr_register_exception(struct rdr_exception_info_s* e)
{
    return BSP_OK;
}

int rdr_register_module_ops(u64 coreid, struct rdr_module_ops_pub* ops, struct rdr_register_module_result* retinfo)
{
    g_st_adp_ctrl.soc_ops.ops_dump  = ops->ops_dump;
    g_st_adp_ctrl.soc_ops.ops_reset = ops->ops_reset;

    return BSP_OK;
}

void rdr_system_error(u32 modid, u32 arg1, u32 arg2)
{
    if(false == g_ul_adp_init_flag)
    {
        dump_fetal("%s: rdr adp not inited\n", __FUNCTION__);
        return;
    }

    g_st_adp_ctrl.modid = modid;
    up(&g_st_adp_ctrl.adp_task_sem);
    dump_fetal("up sem g_st_adp_ctrl.adp_task_sem\n");

    return;
}

void rdr_adp_cp_dump_done(u32 modid, u64 coreid)
{
    g_st_adp_ctrl.cp_done_flag = true;

    dump_fetal("rdr_adp_cp_dump_done\n");
}

int rdr_adp_task(void * data)
{
    u32 time_start;
    u32 time_cur;

    while(1)
    {
        if(0 != down_interruptible(&g_st_adp_ctrl.adp_task_sem))
        {
            continue;
        }
        else
        {
            dump_fetal("down sem g_st_adp_ctrl.adp_task_sem\n");
        }

        g_st_adp_ctrl.soc_ops.ops_dump(g_st_adp_ctrl.modid, 0, 0, RDR_ADP_LOG_PATH, rdr_adp_cp_dump_done);

        /* 等待dump回调完成，最多等待RDR_ADP_MAX_WAIT_CNT tick */
        time_start = om_timer_tick_get();
        do{
            if(true == g_st_adp_ctrl.cp_done_flag)
            {
                break;
            }

            time_cur = om_timer_tick_get();
            if(RDR_ADP_MAX_WAIT_CNT < time_cur - time_start)
            {
                dump_fetal("%s: wait dump done time out\n", __FUNCTION__);
                break;
            }

            msleep(10);
        }while(1);

        /* 执行reset回调 */
        g_st_adp_ctrl.soc_ops.ops_reset(g_st_adp_ctrl.modid, 0, 0);
    }

    return 0;
}

int rdr_adp_init(void)
{
    struct task_struct * pid;
    struct sched_param  param;

    sema_init(&g_st_adp_ctrl.adp_task_sem, 0);

    pid = (struct task_struct *)kthread_run(rdr_adp_task, 0, "rdr_adp");
    if (IS_ERR((void*)pid))
    {
        printk("%s: create rdr adp task failed! ret=%p\n", __FUNCTION__, pid);
        return BSP_ERROR;
    }

    param.sched_priority = 99;
    if (BSP_OK != sched_setscheduler(pid, SCHED_FIFO, &param))
    {
        printk("%s: sched_setscheduler failed!\n", __FUNCTION__);
        return BSP_ERROR;
    }

    g_st_adp_ctrl.cp_done_flag = false;
    g_ul_adp_init_flag = true;

    printk("rdr adp init ok\n");

    return BSP_OK;
}

unsigned int bbox_check_edition(void)
{
    return EDITION_INTERNAL_BETA;
}

arch_initcall(rdr_adp_init);
#else

#endif //CONFIG_HISI_BB

#ifdef __cplusplus
}
#endif

