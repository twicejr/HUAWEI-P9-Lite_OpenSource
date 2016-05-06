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
#ifndef __HARDTIMER_BALONG_H__
#define __HARDTIMER_BALONG_H__
#include <hi_timer.h>
#include <linux/spinlock.h>
#include <linux/list.h>
#include <drv_comm.h>
#include <bsp_hardtimer.h>
/*lint -e{760}*/

#ifndef SEM_EMPTY
#define SEM_EMPTY 0
#endif

#ifndef SEM_FULL
#define SEM_FULL 1
#endif

#define TIMERS_INTSTATUS(hard_timer_module_addr)                  (hard_timer_module_addr + 0xA0)
#define TIMERS_EOI(hard_timer_module_addr)                        (hard_timer_module_addr+ 0xA4 )
#define TIMERS_RAWINTSTATUS(hard_timer_module_addr)               (hard_timer_module_addr+ 0xA8)
#define TIMER_LOADCOUNT(hard_timer_id_addr)                       (hard_timer_id_addr + HI_TIMER_LOADCOUNT_OFFSET )
#define TIMER_LOADCOUNT_H(hard_timer_id_addr)                     (hard_timer_id_addr + HI_TIMER_LOADCOUNT_H_OFFSET )
#define TIMER_CURRENTVALUE(hard_timer_id_addr)                    (hard_timer_id_addr + HI_TIMER_CURRENTVALUE_OFFSET )
#define TIMER_CURRENTVALUE_H(hard_timer_id_addr)                  (hard_timer_id_addr +  HI_TIMER_CURRENTVALUE_H_OFFSET)
#define TIMER_CONTROLREG(hard_timer_id_addr)                      (hard_timer_id_addr + HI_TIMER_CONTROLREG_OFFSET )
#define TIMER_EOI(hard_timer_id_addr)                             (hard_timer_id_addr +  HI_TIMER_EOI_OFFSET)
#define TIMER_INTSTATUS(hard_timer_id_addr)                       (hard_timer_id_addr + HI_TIMER_INTSTATUS_OFFSET )

#define TIMER_EN_ACK                                 (1<<4)
#define TIMER_INT_MASK                               (1<<2)
#define TIMER_MODE_PERIOD                            (1<<1)
#define HARD_TIMER_ENABLE                             1
#define HARD_TIMER_DISABLE                            0
 

struct timer_device ;

struct timer_core_ops{
	s32 (*timer_init)(struct timer_device  *device);
	s32 (*timer_enable)(struct timer_device  *device);
	s32 (*timer_disable)(struct timer_device  *device);
	void (*timer_mask)(struct timer_device  *device);
	void (*timer_unmask)(struct timer_device  *device);
	u32 (*timer_get_cur_value)(struct timer_device  *device);
	u32 (*timer_int_status)(struct timer_device  *device);
	void (*timer_set_init_value)(struct timer_device  *device,unsigned int value);
	void (*timer_int_clear)(struct timer_device  *device);
	u32 (*check_timer_enabled)(struct timer_device  *device);
	void (*suspend)(struct timer_device  *device);
	void (*resume)(struct timer_device  *device);
};
struct timer_driver {
    struct timer_core_ops	*ops;
    unsigned int periphid;
    const char	 *driver_name;
    struct list_head timer_drivers;
};
struct timer_device {
	char*			name;
    void*        base_addr;		
    unsigned int        irq;			/* irq number */
    unsigned int        clk;	    
    unsigned int        periphid;
	unsigned int 		sr_flag;/*timer suspend flag*/
	spinlock_t 			lock;
	unsigned int 		lp_timer_valuereg;
	unsigned int 		lp_timer_ctrlreg;
    struct timer_driver  *driver;
	struct bsp_hardtimer_control timer_ctrl;
};

void bsp_timer_driver_register(struct timer_driver  *timer_driver);
void synopsis_timer_drviver_init(void);
void arm_timer_drviver_init(void);
extern int set_adp_timer_isr_and_pm(void);

#endif
