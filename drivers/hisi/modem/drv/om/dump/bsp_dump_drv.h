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

#ifndef	__BSP_DUMP_DRV_H__
#define __BSP_DUMP_DRV_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include <bsp_memmap.h>
#ifndef __ASSEMBLY__
#include <linux/semaphore.h>
#include "product_config.h"
#include "osl_types.h"
#endif/*#ifndef __ASSEMBLY__*/
#include "bsp_dump_mem.h"

/**************************************************************************
  宏定义
**************************************************************************/
/*APP段内存分配*/
#define DUMP_BASE_INFO_ADDR                 (DUMP_AREA_AP_STATIC_ADDR)
#define DUMP_BASE_INFO_SIZE                 (0x180)
#define DUMP_TASK_SWITCH_ADDR               (DUMP_BASE_INFO_ADDR+DUMP_BASE_INFO_SIZE)
#define DUMP_TASK_SWITCH_SIZE               (0x10000)
#define DUMP_INTLOCK_ADDR                   (DUMP_TASK_SWITCH_ADDR+DUMP_TASK_SWITCH_SIZE)
#define DUMP_INTLOCK_SIZE                   (0x1000)
#define DUMP_TASK_STACK_ADDR                (DUMP_INTLOCK_ADDR+DUMP_INTLOCK_SIZE)
#define DUMP_TASK_STACK_SIZE                (0x2000)
#define DUMP_INT_STACK_ADDR                 (DUMP_TASK_STACK_ADDR+DUMP_TASK_STACK_SIZE)
#define DUMP_INT_STACK_SIZE                 (0x0)
#define DUMP_ALLTASK_ADDR                   (DUMP_INT_STACK_ADDR+DUMP_INT_STACK_SIZE)
#define DUMP_ALLTASK_SIZE                   (0x800)
#define DUMP_ALLTASK_TCB_ADDR               (DUMP_ALLTASK_ADDR+DUMP_ALLTASK_SIZE)
#define DUMP_ALLTASK_TCB_SIZE               (0x10000)
#define DUMP_PRINT_ADDR                     (DUMP_ALLTASK_TCB_ADDR+DUMP_ALLTASK_TCB_SIZE)
#define DUMP_PRINT_SIZE                     (0x4000)
#define DUMP_REGS_ADDR                      (DUMP_PRINT_ADDR+DUMP_PRINT_SIZE)
#define DUMP_REGS_SIZE                      (0x3000)                                     // 待定
#define DUMP_CPUVIEW_ADDR                   (DUMP_REGS_ADDR+DUMP_REGS_SIZE)
#define DUMP_CPUVIEW_SIZE                   (0)
#define DUMP_USER_DATA_ADDR                 (DUMP_CPUVIEW_ADDR+DUMP_CPUVIEW_SIZE)
#define DUMP_USER_DATA_SIZE                 (0x1000)
#define DUMP_RSV_ADDR                       (DUMP_USER_DATA_ADDR+DUMP_USER_DATA_SIZE)
#define DUMP_RSV_SIZE                       (0)

#define DUMP_INIT_FLAG_PHASE1               (0x5B5B0000)
#define DUMP_INIT_FLAG_PHASE2               (0x5B5B0001)
#define DUMP_INIT_FLAG                      (0x5B5B0002)
#define DUMP_INIT_FLAG_WAIT                 (0x5C5C5C5C)

#define DUMP_TASK_JOB_RESET_LOG             (0x00000001)
#define DUMP_TASK_JOB_SAVE                  (0x00000002)
#define DUMP_TASK_JOB_INIT                  (0x00000004)
#define DUMP_TASK_JOB_REBOOT                (0x00000008)
#define DUMP_TASK_JOB_SAVE_INIT             (DUMP_TASK_JOB_SAVE | DUMP_TASK_JOB_INIT)
#define DUMP_TASK_JOB_SAVE_REBOOT           (DUMP_TASK_JOB_SAVE | DUMP_TASK_JOB_REBOOT)

#ifndef __ASSEMBLY__

struct hpm_tem_print
{
    unsigned int hpm_hvt_opc;
	unsigned int hpm_uhvt_opc;
	unsigned int hpm_svt_opc;
	signed int	 temperature;
	unsigned char up_volt;
};

/**************************************************************************
  STRUCT定义
**************************************************************************/
#ifndef FUNC_VOID
typedef void (*func_void_t)(void);
#define FUNC_VOID func_void_t
#endif
//typedef s32 (*FUNCPTR)(void);

typedef struct _dump_ctrl_s
{
    u32 dump_task_id;
    u32 dump_task_job;
    u32 current_task_info;           /*0xA0 */
    struct semaphore sem_dump_task;
}dump_ctrl_s;

typedef struct
{
    u32 wdtSwitch;
    u32 wdtTimerOut;  /*看门狗超时时间，单位ms*/
    u32 sys_view;

    union
    {
        u32 uintValue;
        struct
        {
            u32 sci_switch     : 1; /* 00: excdump, 01: usbdump, 1x: no dump */
            u32 usb_switch     : 1; /* 2 ARM异常检测开关*/
            u32 pmu_switch     : 1; /* 3 堆栈溢出检测开关*/
            u32 sd_switch      : 1; /* 3 堆栈溢出检测开关*/
            u32 icc_switch     : 1; /* 3 堆栈溢出检测开关*/
            u32 ifc_switch     : 1; /* 4 任务切换记录开关*/
            u32 reserved1      : 26;
        } Bits;
    } mod_cfg;
} OM_NV;


/**************************************************************************
  UNION定义
**************************************************************************/

/**************************************************************************
  OTHERS定义
**************************************************************************/
#define dump_debug(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR,   BSP_MODU_DUMP, "[dump]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define dump_warning(fmt, ...)  (bsp_trace(BSP_LOG_LEVEL_WARNING, BSP_MODU_DUMP, "[dump]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define dump_error(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR,   BSP_MODU_DUMP, "[dump]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define dump_fetal(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_FATAL,   BSP_MODU_DUMP, "[dump]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))

/**************************************************************************
  函数声明
**************************************************************************/


#endif/*#ifndef __ASSEMBLY__*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif    /* End #define __BSP_DUMP_H__ */




