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

#ifndef	__BSP_OM_SAVE_H__
#define __BSP_OM_SAVE_H__

#include "product_config.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */


/**************************************************************************
  宏定义
**************************************************************************/
#define OM_ROOT_DIR             "/modem_log/"
#define OM_LOG_PATH             "/modem_log/log/"
#define OM_DUMP_PATH            "/modem_log/dump/"
#define OM_RESET_LOG            "/modem_log/dump/reset.log"
#define OM_ERROR_LOG            "/modem_log/log/error.log"
#define OM_TASK_NAME            "/modem_log/log/task_name.log"

#define OM_RESET_LOG_MAX        2048
#define OM_ERROR_LOG_MAX        4096
#define OM_PRINT_LOG_MAX        (4096*24)

#define OM_DUMP_FILE_MAX_NUM        3
#define OM_DUMP_FILE_NAME_LENGTH    100
#define OM_SYSCTRL_MAGIC        0x5B5C5C5B

/**************************************************************************
  STRUCT定义
**************************************************************************/

/**************************************************************************
  UNION定义
**************************************************************************/
typedef enum
{
    OM_ACORE,
    OM_CCORE,
    OM_CORE_BUTT
} om_core_opt_t;

/**************************************************************************
  OTHERS定义
**************************************************************************/


/**************************************************************************
  函数声明
**************************************************************************/
void bsp_om_save_loop_file(char * dir_name, u32 nve_value, u32 type);
void bsp_om_save_dump_backup(char * dir_name, u8 * addr, u32 len, u32 type);
int  bsp_om_debug_init(void);
int  bsp_om_save_file(char *filename, void * address, u32 length, u32 mode);
int  bsp_om_append_file(char *filename, void * address, u32 length, u32 max_size);
bool bsp_om_fs_check(void);
void bsp_om_record_resetlog(u8 * dump_addr);
void bsp_om_save_resetlog(void);
void om_save_sysctrl(void);
void dump_rm_old_dir(void);
void om_get_reset_info(char * reset_info, u32 size);
void dump_memmap_modem_ddr(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif    /* End #define __BSP_OM_SAVE_H__ */





