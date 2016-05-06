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
#ifndef __BSP_WP_H__
#define __BSP_WP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "product_config.h"
#include "osl_types.h"
#include "drv_comm.h"

/* Accessor macros for the debug registers. */
#define WP_DBG_READ(M, OP2, VAL) do {\
	asm volatile("mrc p14, 0, %0, c0," #M ", " #OP2 : "=r" (VAL));\
} while (0)

#define WP_DBG_WRITE(M, OP2, VAL) do {\
	asm volatile("mcr p14, 0, %0, c0," #M ", " #OP2 : : "r" (VAL));\
} while (0)

/* DSCR monitor/halting bits. */
#ifndef ARM_DSCR_HDBGEN
#define ARM_DSCR_HDBGEN		(1 << 14)
#endif
#ifndef ARM_DSCR_MDBGEN
#define ARM_DSCR_MDBGEN		(1 << 15)
#endif

/* opcode2 numbers for the co-processor instructions. */
#ifndef ARM_OP2_BVR
#define ARM_OP2_BVR		    4
#endif
#ifndef ARM_OP2_BCR
#define ARM_OP2_BCR		    5
#endif
#ifndef ARM_OP2_WVR
#define ARM_OP2_WVR		    6
#endif
#ifndef ARM_OP2_WCR
#define ARM_OP2_WCR		    7
#endif

/* Base register numbers for the debug registers. */
#ifndef ARM_BASE_WVR
#define ARM_BASE_WVR		96
#endif
#ifndef ARM_BASE_WCR
#define ARM_BASE_WCR		112
#endif

/* DSCR method of entry bits. */
#define DSCR_MOE(x)			((x >> 2) & 0xf)
#ifndef ARM_ENTRY_BREAKPOINT
#define ARM_ENTRY_BREAKPOINT		0x1
#endif
#ifndef ARM_ENTRY_ASYNC_WATCHPOINT
#define ARM_ENTRY_ASYNC_WATCHPOINT	0x2
#endif
#ifndef ARM_ENTRY_SYNC_WATCHPOINT
#define ARM_ENTRY_SYNC_WATCHPOINT	0xa
#endif

/* watchpoint address select */
#define WATCHPOINT_LEN_4    0xf
/* watchpoint match privileged/unprivileged accesses */
#define WATCHPOINT_PRI      0x3

#define WP_READ_REG_CASE(OP2, M, VAL)  \
	case ((OP2 << 4) + M):			   \
		WP_DBG_READ(c ## M, OP2, VAL); \
		break

#define WP_WRITE_REG_CASE(OP2, M, VAL) \
	case ((OP2 << 4) + M):			   \
		WP_DBG_WRITE(c ## M, OP2, VAL);\
		break

#define GEN_WP_READ_REG_CASES(OP2, VAL)	\
	WP_READ_REG_CASE(OP2, 0, VAL);		\
	WP_READ_REG_CASE(OP2, 1, VAL);		\
	WP_READ_REG_CASE(OP2, 2, VAL);		\
	WP_READ_REG_CASE(OP2, 3, VAL);		\
	WP_READ_REG_CASE(OP2, 4, VAL);		\
	WP_READ_REG_CASE(OP2, 5, VAL);		\
	WP_READ_REG_CASE(OP2, 6, VAL);		\
	WP_READ_REG_CASE(OP2, 7, VAL);		\
	WP_READ_REG_CASE(OP2, 8, VAL);		\
	WP_READ_REG_CASE(OP2, 9, VAL);		\
	WP_READ_REG_CASE(OP2, 10, VAL);		\
	WP_READ_REG_CASE(OP2, 11, VAL);		\
	WP_READ_REG_CASE(OP2, 12, VAL);		\
	WP_READ_REG_CASE(OP2, 13, VAL);		\
	WP_READ_REG_CASE(OP2, 14, VAL);		\
	WP_READ_REG_CASE(OP2, 15, VAL)

#define GEN_WP_WRITE_REG_CASES(OP2, VAL)\
	WP_WRITE_REG_CASE(OP2, 0, VAL);		\
	WP_WRITE_REG_CASE(OP2, 1, VAL);		\
	WP_WRITE_REG_CASE(OP2, 2, VAL);		\
	WP_WRITE_REG_CASE(OP2, 3, VAL);		\
	WP_WRITE_REG_CASE(OP2, 4, VAL);		\
	WP_WRITE_REG_CASE(OP2, 5, VAL);		\
	WP_WRITE_REG_CASE(OP2, 6, VAL);		\
	WP_WRITE_REG_CASE(OP2, 7, VAL);		\
	WP_WRITE_REG_CASE(OP2, 8, VAL);		\
	WP_WRITE_REG_CASE(OP2, 9, VAL);		\
	WP_WRITE_REG_CASE(OP2, 10, VAL);	\
	WP_WRITE_REG_CASE(OP2, 11, VAL);	\
	WP_WRITE_REG_CASE(OP2, 12, VAL);	\
	WP_WRITE_REG_CASE(OP2, 13, VAL);	\
	WP_WRITE_REG_CASE(OP2, 14, VAL);	\
	WP_WRITE_REG_CASE(OP2, 15, VAL)

enum
{
    WATCHPOINT_DISABLE = 0,
    WATCHPOINT_ENABLE  = 1,
};

enum
{
    WATCHPOINT_R    = 1,
    WATCHPOINT_W    = 2,
    WATCHPOINT_RW   = WATCHPOINT_R | WATCHPOINT_W,
};

typedef struct
{
    u32 reserved1	: 3;
    u32 addr_range	: 5;
    u32 reserved2	: 11;
    u32	len		    : 8;
	u32	type		: 2;
    u32	privilege	: 2;
	u32	enabled		: 1;
}watchpoint_ctrl;

typedef struct
{
    u32     enable;     /* watchpoint使能标志, 1:register之后立即使能，0:register不使能，等待主动调用enable接口 */
    u32     type;       /* watchpoint类型，1:读，2:写，3:读写 */
    u32     start_addr; /* 监控起始地址，地址需要4字节对齐 */
    u32     end_addr;   /* 监控结束地址, 监控单个地址，end_addr可填0 */
}wp_cfg_t;


#ifdef CONFIG_WATCHPOINT
/* 注册watchpoint做地址范围监控时，需要选择合适的范围，由于watchpoint实现机制限制，通常会扩大监控范围
 * watchpoint匹配规则: 满足(访问地址 & ~mask == 监控起始地址 & ~mask), 则触发watchpoint异常
 * mask计算规则: start_addr与end_addr二进制表示的公共前缀长度为n，mask = (1 << (32 - n)) - 1
 * 示例: start_addr = 0x55600014, end_addr = 0x55600028, mask = 0b111111，实际监控范围为0x55600000~0x55600040
 */

/*lint -save -e830 */
s32 bsp_wp_register(wp_cfg_t * cfg);
s32 bsp_wp_enable(s32 wp_id);
s32 bsp_wp_disable(s32 wp_id);
s32 bsp_wp_unregister(s32 wp_id);
/*lint -restore +e830*/
s32 bsp_wp_init(void);
/* 侵入内核修改 begin */
s32 wp_callback(u32 addr, u32 dscr, void * regs);
/* 侵入内核修改 end */
#else
static s32 inline bsp_wp_register(wp_cfg_t * cfg)
{
    return BSP_OK;
}

static s32 inline bsp_wp_enable(s32 wp_id)
{
    return BSP_OK;
}

static s32 inline bsp_wp_disable(s32 wp_id)
{
    return BSP_OK;
}

static s32 inline bsp_wp_unregister(s32 wp_id)
{
    return BSP_OK;
}

static s32 inline bsp_wp_init(void)
{
    return BSP_OK;
}

/* 侵入内核修改 begin */
static s32 inline wp_callback(u32 addr, u32 dscr, void * regs)
{
    return BSP_ERROR;
}
/* 侵入内核修改 end */

#endif

#ifdef __cplusplus
}
#endif

#endif //__BSP_WP_H__

