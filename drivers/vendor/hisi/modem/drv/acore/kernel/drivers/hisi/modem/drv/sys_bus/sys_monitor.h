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

#ifndef __C_SYS_MONITOR_H__
#define __C_SYS_MONITOR_H__

#define MAX_SYS_CHAN_NUM    8
#define MAX_SYS_PORT_NUM    8


#define CNT_STATE_INT  0x8
#define PORT_SEL       0x1C
#define CNT_ID         0x100
#define ID_ADDR_DES    0x104
#define ID_ADDR_DES_M  0x108
#define READ_BYTES_ID  0x1E8
#define WRITE_BYTES_ID 0x1F0

struct sys_monitor{
    struct device_node  *of_node;
    u32 base_addr;
    u64 totaltime;
    u64 start_t;
    u64 end_t;
};

struct sys_amon_chan{
    const char* name;
    u32 chan_id;        /* chan id 指示用于监控的资源号 */
    u32 use_flag;       /* 指示当前chan是否可使用 */
    u32 reset_flag;     /* 复位标志，匹配到监控条件是否复位 */
    u32 opt_type;       /* 监控类型，01:读，10:写，11:读写，其余值:不监控 */
    u32 port;           /* 监控端口 */
    u32 id_enable;      /* 是否id 使能*/
    u32 cnt_id;
    u32 cnt_id_mask;
    u32 adr_enable;     /* 是否addresss使能*/
    u32 start_addr;     /* 监控起始地址 */
    u32 end_addr;       /* 监控结束地址 */
    u32 read_bytes[2];
    u32 write_bytes[2];
};

enum sys_amon_enable{
    SYS_AMON_ID_ENABLE = 0,
    SYS_AMON_ADR_ENABLE = 1,
    SYS_AMON_BOTH_ENABLE = 2,
    SYS_AMON_NONE_ENABLE = 3
};

int sys_monitor_init(void);
void sys_mon_help(void);
u32 sys_mon_config_id(u32 id, u32 enable, u32 start_addr, u32 end_addr);
u32 sys_mon_config_port(u32 port, u32 start_addr, u32 end_addr);
void sys_mon_one_free(u32 chan);
void sys_mon_all_free(void);
void sys_mon_result(void);
void sys_mon_result_and_start(void);
void sys_mon_start(void);
void sys_mon_chan_info(void);

#endif /* __C_SYS_EDMA_H__ */
