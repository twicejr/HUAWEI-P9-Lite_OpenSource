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
#ifndef __BSP_OM_VERSION_H__
#define __BSP_OM_VERSION_H__

/* 说明: 本文件除了dump之外，不允许其他模块包含 */
#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    unsigned char   module_name[16];
    unsigned int    module_ver;
} dump_scripts_stru;

/* T32脚本存放及命名规则: 模块名/模块名_版本号.cmm, 以diag为例，在脚本目录中为diag/diag_0000.cmm */
/* 新增模块时，module_name字段内容必须与脚本的模块名保持一致，module_ver高8位为主版本号，低8位为次版本号 */

/* A核模块列表 */
#ifdef __KERNEL__
dump_scripts_stru g_dump_scripts[] = {
    {"diag",        0x0000},
    {"icc",         0x0000},   
    {"lcd",         0x0000},
    {"emi",         0x0000},
    {"loadm",       0x0000},
    {"efuse",       0x0000},
    {"ipc",         0x0000},
    {"clk",         0x0000},
    {"regulator",   0x0000},
    {"cpufreq",     0x0000},
    {"pm",          0x0000},
    {"timer",       0x0000},
    {"ipf",         0x0000},
    {"hkadc",       0x0000},
    {"temp",        0x0000},
    {"version",     0x0000},
    {"gmac",        0x0000},
};
#endif

/* C核模块列表 */
#if defined( __VXWORKS__)||defined(__OS_RTOSCK__)
dump_scripts_stru g_dump_scripts[] = {
    {"diag",        0x0000},
    {"icc",         0x0000},
    {"dsp",         0x0000},
    {"ltesleep",    0x0000},
    {"ipc",         0x0000},
    {"clk",         0x0000},
    {"regulator",   0x0000},
    {"cpufreq",     0x0000},
    {"pm",          0x0000},
    {"timer",       0x0000},
    {"mailbox",     0x0000},
    {"bbp",         0x0000},
	{"ipf", 		0x0000},
    {"abb",         0x0000},
    {"hkadc",       0x0000},
    {"version",     0x0000},
    {"cipher",      0x0000},
    {"cshell",      0x0000},
    {"security",    0x0000},
};
#endif

/* M核模块列表 */
#if defined(__CMSIS_RTOS)
dump_scripts_stru g_dump_scripts[] = {
    {"ipc",         0x0000},
};

#endif

#ifdef __cplusplus
}
#endif

#endif /* __BSP_OM_VERSION_H__ */


