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

#ifndef __BSP_AMON_H__
#define __BSP_AMON_H__

#ifdef __cplusplus
extern "C" {
#endif


#include "osl_common.h"

#ifdef ENABLE_BUILD_AMON
/* Monitor监控、采集ID最大数目 */
#define AXI_MAX_CONFIG_ID	8
#define AXI_MAX_PORT_CNT    8

#define AMON_SOC_MASK           0x1
#define AMON_CPUFAST_MASK       0x2
#define AMON_ENABLE_MASK        0x4
#define AMON_OPT_READ           0x1
#define AMON_OPT_WRITE          0x2

#ifdef BSP_CONFIG_PHONE_TYPE 
/*PORT总数*/
#define AMON_PORT_MAX           (5)
#endif
typedef struct
{
    u32 hig_count;
    u32 low_count;
}count_stru;
typedef struct
{
    count_stru soc_read_count[AXI_MAX_CONFIG_ID];
    count_stru soc_write_count[AXI_MAX_CONFIG_ID];
    count_stru fast_read_count[AXI_MAX_CONFIG_ID];
    count_stru fast_write_count[AXI_MAX_CONFIG_ID];
	u64			global_access_count;
	u64			monitor_time_delta;
}amon_count_stru;
typedef struct
{
    u32 reset_flag;     /* 复位标志，匹配到监控条件是否复位 */
    u32 opt_type;       /* 监控类型，01:读，10:写，11:读写，其余值:不监控 */
    u32 port;           /* 监控端口 */
    u32 master_id;      /* 监控masterid */
    u32 start_addr;     /* 监控起始地址 */
    u32 end_addr;       /* 监控结束地址 */
} amon_config_t;

typedef struct
{
    u32             en_flag;                            /* 使能标志，00:去使能，01:SOC，10:CPUFAST，11:SOC,CPUFAST */    
    amon_config_t   soc_config[AXI_MAX_CONFIG_ID];      /* SOC配置 */
    amon_config_t   cpufast_config[AXI_MAX_CONFIG_ID];  /* CPUFAST配置 */
} amon_config_stru;
/* AXI配置选择 */
enum axi_config_enum
{
    AXI_CPUFAST_CONFIG,         /* CPUFAST配置 */
    AXI_SOC_CONFIG,             /* SOC配置 */
    AXI_CONFIG_BUTT
};
typedef unsigned int axi_config_enum_uint32;



s32 bsp_amon_init(void);
s32 amon_set_config(amon_config_stru configinfo);
s32 amon_start(axi_config_enum_uint32 config);
s32 amon_stop(axi_config_enum_uint32 config);
s32 amon_get_info(amon_count_stru *count);
#else
static s32 inline bsp_amon_init(void)
{
    return 0;
}

#endif


#ifdef __cplusplus
}
#endif


#endif

