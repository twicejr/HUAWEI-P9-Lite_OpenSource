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

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
/*lint -save -e322 -e7 -e537 */
#include "bsp_om_api.h"
#include "bsp_om_log.h"
#include "bsp_om.h"
#include "bsp_socp.h"
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/semaphore.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/kthread.h>
#include "osl_sem.h"
#include "bsp_dump_drv.h"
#include "bsp_dump.h"
#include "bsp_ipc.h"
#include "bsp_hardtimer.h"
#include <bsp_modem_log.h>
/*lint -restore*/
#if 0
/*lint --e{750}*/
#define    THIS_MODU_ID        BSP_MODU_LOG
/*lint -restore */
#endif

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
bsp_log_swt_cfg_s  g_mod_peint_level_info[BSP_MODU_MAX]    =
{
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}
};

u32 bsp_log_level_set(bsp_log_level_e log_level);
void bsp_log_show(void);



/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
* 函 数 名  : bsp_log_module_cfg_get
*
* 功能描述  : 查询模块当前设置的打印级别
*
* 输入参数  : mod_id:被查询模块ID
*
* 输出参数  : 无
*
* 返 回 值  : 打印级别
*****************************************************************************/

u32 bsp_log_module_cfg_get(bsp_module_e mod_id)
{
    if(mod_id >= BSP_MODU_MAX )
    {
        return BSP_ERR_LOG_INVALID_MODULE;
    }

    return g_mod_peint_level_info[mod_id].print_level;
}

/*****************************************************************************
* 函 数 名  : bsp_mod_level_set
*
* 功能描述  : 设置单个模块的打印级别
*
* 输入参数  : mod_id:模块ID
*                         print_level: 打印级别
* 输出参数  : 无
*
* 返 回 值  : BSP_OK 设置成功，其他  设置失败
*****************************************************************************/

u32 bsp_mod_level_set(bsp_module_e  mod_id ,u32 print_level)
{
    if(mod_id >= BSP_MODU_MAX )
    {
        return BSP_ERR_LOG_INVALID_MODULE;
    }

    if(print_level >BSP_LOG_LEVEL_MAX)
    {
        return BSP_ERR_LOG_INVALID_LEVEL;
    }

    g_mod_peint_level_info[mod_id].print_level = print_level;

    return BSP_OK;
}

/*****************************************************************************
* 函 数 名  : bsp_log_level_set
*
* 功能描述  : 设置所有模块的打印级别
*
* 输入参数  : print_level: 打印级别
*
* 输出参数  : 无
*
* 返 回 值  : BSP_OK 设置成功，其他  设置失败
*****************************************************************************/

u32 bsp_log_level_set(bsp_log_level_e log_level)
{
    u32 mod_id = 0;

    if(log_level > BSP_LOG_LEVEL_MAX)
    {
        return BSP_ERR_LOG_INVALID_LEVEL;
    }

    for(mod_id = 0; mod_id < BSP_MODU_MAX; mod_id++)
    {
        g_mod_peint_level_info[mod_id].print_level = log_level;
    }

    return BSP_OK;
}


/*****************************************************************************
* 函 数 名  : bsp_log_level_reset
*
* 功能描述  : 将所有模块的打印级别设置为默认值
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : 无
*****************************************************************************/

void bsp_log_level_reset(void)
{
    u32 i;

    for(i = 0; i < BSP_MODU_MAX;i++)
    {
        g_mod_peint_level_info[i].print_level= BSP_LOG_LEVEL_ERROR;
    }

}

/*****************************************************************************
* 函 数 名  : bsp_trace
*
* 功能描述  : 底软打印输出处理接口
*
* 输入参数  :  mod_id: 输出模块
*                           print_level: 打印级别
*                           fmt :打印输入参数
*
* 输出参数  : 无
*
* 返 回 值  : 无
*****************************************************************************/

void bsp_trace(bsp_log_level_e log_level,bsp_module_e mod_id,char *fmt,...)
{
    char    bsp_print_buffer[BSP_PRINT_BUF_LEN] ;
    va_list arglist;

    /*打印级别过滤*/
    if(mod_id >= BSP_MODU_MAX )
    {
        return ;
    }

    if(g_mod_peint_level_info[mod_id].print_level > log_level )
    {
        return ;
    }

    /*lint -save -e530*/
    va_start(arglist, fmt);
    /*lint -restore +e530*/
    vsnprintf(bsp_print_buffer, BSP_PRINT_BUF_LEN, fmt, arglist); /* [false alarm]:屏蔽Fortify错误 */
    va_end(arglist);

    bsp_print_buffer[BSP_PRINT_BUF_LEN - 1] = '\0';

    printk(KERN_ERR"%s", bsp_print_buffer);

    return ;
}
EXPORT_SYMBOL_GPL(bsp_trace);

#ifdef ENABLE_BUILD_OM
/*****************************************************************************
* 函 数 名  : bsp_log_module_cfg_set
*
* 功能描述  : HSO设置底软打印级别处理函数
*
* 输入参数  : log_swt_stru:各个模块的打印级别值
*                         data_len:      参数log_swt_stru的长度
* 输出参数  : 无
*
* 返 回 值  : BSP_OK 成功;其他 失败
*****************************************************************************/

u32 bsp_log_module_cfg_set(bsp_log_swt_cfg_s *log_swt_stru ,u32 data_len)
{
    u32 mod_num = 0;
    u32 i;

    if((NULL == log_swt_stru )||( 0 == data_len)||((data_len % sizeof(bsp_log_swt_cfg_s) != 0)))
    {
        bsp_om_debug(BSP_LOG_LEVEL_ERROR," bsp_log_module_cfg_set error!!  data_len = %d\n",data_len);
       return BSP_ERR_LOG_INVALID_PARAM;
    }

    mod_num = data_len / sizeof(bsp_log_swt_cfg_s);

    if(mod_num > BSP_MODU_MAX )
    {
        bsp_om_debug(BSP_LOG_LEVEL_ERROR," bsp_log_module_cfg_set error!!  mod_num = %d\n",mod_num);
        return BSP_ERR_LOG_INVALID_MODULE;
    }

    for(i = 0; i < mod_num; i++)
    {
        if(log_swt_stru[i].print_level <= BSP_LOG_LEVEL_MAX)
        {
            g_mod_peint_level_info[i].print_level = log_swt_stru[i].print_level;

        }
        else
        {
            bsp_om_debug(BSP_LOG_LEVEL_ERROR," bsp_log_module_cfg_set   log_swt_stru[i].print_level = %d\n",log_swt_stru[i].print_level);
            return BSP_ERR_LOG_INVALID_LEVEL ;
        }

    }

    return BSP_OK;
}

/*debug 接口*/
void bsp_log_show(void)
{
    pr_err("trace level              = %d\n",g_mod_peint_level_info[0].print_level);
}

#define modem_om_log_err(fmt, ...)        pr_err("[om log]: " fmt, ##__VA_ARGS__) 
#define modem_om_log_debug(fmt, ...)      //pr_err("[om log]: " fmt, ##__VA_ARGS__) 

void log_buff_info(void)
{
    log_mem_stru * log = NULL;
    log_mem_stru * m3_log = NULL;

    log    = (log_mem_stru *)bsp_dump_get_field_addr(DUMP_CP_DMESG);
    m3_log = (log_mem_stru *)bsp_dump_get_field_addr(DUMP_M3_LOG);
    if(log != NULL)
    {
        pr_err("CCORE DMESG ADDR: %p\n",   log);
        pr_err("BUFFER MAGIC    : 0x%x\n", log->log_info.magic);
        pr_err("READ POINTER    : 0x%x\n", log->log_info.read);
        pr_err("WRITE POINTER   : 0x%x\n", log->log_info.write);
        pr_err("BUFFER LENGTH   : 0x%x\n", log->log_info.size);
        pr_err("APP STATE       : 0x%x\n", log->log_info.app_is_active);
    }

    if(m3_log != NULL)
    {
        pr_err("M3 LOG ADDR     : %p\n",   m3_log);
        pr_err("BUFFER MAGIC    : 0x%x\n", m3_log->log_info.magic);
        pr_err("READ POINTER    : 0x%x\n", m3_log->log_info.read);
        pr_err("WRITE POINTER   : 0x%x\n", m3_log->log_info.write);
        pr_err("BUFFER LENGTH   : 0x%x\n", m3_log->log_info.size);
        pr_err("APP STATE       : 0x%x\n", m3_log->log_info.app_is_active);
    }
}

struct new_om_log
{
	struct log_usr_info  ccore_log_info;
	struct log_usr_info  mcore_log_info;
};

struct new_om_log g_om_log;

static inline u32 om_log_writable_size_get(u32 write, u32 read, u32 ring_buffer_size)
{
	return (read > write)? (read - write): (ring_buffer_size - write + read); 
}

/*****************************************************************************
* 函 数 名  : do_read_data_to_user
*
* 功能描述  : 拷贝数据至用户态
*
* 输入参数  : char * src, 数据源buffer
*             char * dst，数据目的buffer
*             u32 len, 期望读取的数据长度
*
* 输出参数  : 无
*
* 返 回 值  : 实际读取的数据长度
*****************************************************************************/
int do_read_data_to_user(char * src, char * dst, u32 len)
{
    u32 ret;

    /* 返回未能拷贝的数据长度 */
    ret = (u32)copy_to_user(dst, src, len);

    return (int)(len - ret);
}

int om_log_open(struct log_usr_info *usr_info)
{
    DUMP_SAVE_MOD_ENUM mod_id;
    u8 * addr = NULL;
	log_mem_stru *dump_mem = NULL;

    if(!strncmp(usr_info->dev_name, CCORE_LOG_DEV_NAME, sizeof(CCORE_LOG_DEV_NAME)))
    {
        mod_id = DUMP_CP_DMESG;
    }
    else if(!strncmp(usr_info->dev_name, MCORE_LOG_DEV_NAME, sizeof(MCORE_LOG_DEV_NAME)))
    {
        mod_id = DUMP_M3_LOG;
    }
    else
    {
        /* invalid mod id */
        mod_id = DUMP_AP_FIELD_END;
    }

    addr = bsp_dump_get_field_addr(mod_id);
    if(addr == NULL)
    {
		modem_om_log_debug("%s get memory fail\n", __func__);
        return -1;
    }

	dump_mem            = (log_mem_stru *)addr;
    usr_info->mem       = &dump_mem->log_info;
	usr_info->ring_buf  = (char *)(dump_mem) + sizeof(log_mem_stru);
	usr_info->mem_is_ok = 1;
	modem_om_log_debug("%s entry\n", __func__);

	return 0;
}

int om_log_read(struct log_usr_info *usr_info, char *buf, u32 count)
{
	s32 ret     = 0;
	u32 msg_len = 0;
	u32 write_p = usr_info->mem->write;
	u32 read_p  = usr_info->mem->read;

    if(om_log_writable_size_get(write_p, read_p, usr_info->mem->size) <= LOG_BUFFER_FULL_THRESHOLD)
    {
        usr_info->mem->read = usr_info->mem->write;
        msg_len = (u32)strlen(LOG_DROPPED_MESSAGE);
        count   = min(msg_len, count);
        ret     = do_read_data_to_user(LOG_DROPPED_MESSAGE, buf, count);
		modem_om_log_debug("%s entry\n", __func__);
	}
	return ret;
}

void om_log_dump_handle(void)
{
    bsp_modem_log_fwrite_trigger(&g_om_log.ccore_log_info);
    bsp_modem_log_fwrite_trigger(&g_om_log.mcore_log_info);
}

static int modem_om_log_init(void)
{
	s32 ret = 0;
    if(DUMP_MBB == dump_get_product_type())
    {
		memset((void *)&g_om_log, 0, sizeof(g_om_log));

        /* ccore device */
		g_om_log.ccore_log_info.dev_name = CCORE_LOG_DEV_NAME;
		g_om_log.ccore_log_info.mem      = NULL;
		g_om_log.ccore_log_info.read_func = (USR_READ_FUNC)om_log_read;
		g_om_log.ccore_log_info.open_func = (USR_OPEN_FUNC)om_log_open;
		ret = bsp_modem_log_register(&g_om_log.ccore_log_info);
        if(ret)
        {
            modem_om_log_err("log_ccore register fail\n");
            return BSP_ERROR;
        }

        /* mcore device */
		g_om_log.mcore_log_info.dev_name = MCORE_LOG_DEV_NAME;
		g_om_log.mcore_log_info.mem      = NULL;
		g_om_log.mcore_log_info.read_func = (USR_READ_FUNC)om_log_read;
		g_om_log.mcore_log_info.open_func = (USR_OPEN_FUNC)om_log_open;
		ret = bsp_modem_log_register(&g_om_log.mcore_log_info);
        if(ret)
        {
            modem_om_log_err("log_mcore register fail\n");
            return BSP_ERROR;
        }

        ret= bsp_dump_register_hook("KERNEL_LOG", om_log_dump_handle);
        if(BSP_ERROR == ret)
        {
            modem_om_log_err("register to dump failed!\n");
            return BSP_ERROR;
        }

        modem_om_log_err("init ok\n");
    }

	return 0;
}

EXPORT_SYMBOL_GPL(bsp_log_level_set);
module_init(modem_om_log_init);
#endif

