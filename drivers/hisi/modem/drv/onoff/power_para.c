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

#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/io.h>
#include <linux/string.h>
#include <linux/init.h>
#include "bsp_onoff.h"

#define HEX_STRING_MAX          (10)
#define TRANSFER_BASE           (16)

static unsigned int pd_charge_flag = NORMAL_CHARGING_MODE;
static unsigned int reset_mode_flag = NORMAL_RESET_FLAG;
static unsigned int soft_ver_type = NORMAL_VERTYPE_FLAG;
static unsigned int soft_run_mode = RUN_MODE_NORMAL;

/*****************************************************************************
 函 数 名  : early_parse_pdcharge_cmdline
 功能描述  : parse powerdown charge cmdline which is configured in fastboot
 输入参数  : char *p
 输出参数  : 无
 返 回 值  : ok/error
 调用函数  : pd_charge=0 or 1    1:pw charge 0:normal charge
 被调函数  :
*****************************************************************************/
static int __init early_parse_pdcharge_cmdline(char * p)
{
	char pd_charge[HEX_STRING_MAX + 1];
	char *endptr = NULL;

	memset(pd_charge, 0, HEX_STRING_MAX + 1);

	memcpy(pd_charge, p, HEX_STRING_MAX);
	pd_charge[HEX_STRING_MAX] = '\0';

	pd_charge_flag = simple_strtoull(pd_charge, &endptr, TRANSFER_BASE);

	printk(KERN_DEBUG "power down charge p:%s, pd_charge_flag :%d\n", p, pd_charge_flag);

	return 0;
}
early_param("pd_charge", early_parse_pdcharge_cmdline);

/*****************************************************************************
 函 数 名  : get_pd_charge_flag
 功能描述  : 是否为正常开机版本
 输入参数  : 无
 输出参数  : 无
 返 回 值  : DRV_CHARGING_MODE 版本类型
 调用函数  :
 被调函数  :
*****************************************************************************/
DRV_CHARGING_MODE get_pd_charge_flag(void)
{
    if(pd_charge_flag >= INVALID_CHARGING_MODE){
        printk("invalid charging mode \n");
        return NORMAL_CHARGING_MODE;
    }

	return pd_charge_flag;
}
EXPORT_SYMBOL(get_pd_charge_flag);

/*****************************************************************************
 函 数 名  : early_parse_softver_cmdline
 功能描述  : parse runmode cmdline which is configured in fastboot.
 输入参数  : char *p
 输出参数  : 无
 返 回 值  : ok/error
 调用函数  : swtype=0 or 1  1:factory 0:normal version
 被调函数  :
*****************************************************************************/
static int __init early_parse_softver_cmdline(char * p)
{
	if(p){
        if (!strcmp(p,"factory"))
        	soft_ver_type = FACTORY_VERTYPE_FLAG;

        printk(KERN_DEBUG "softver is %s, softver_factory = %d\n", p, soft_ver_type);
	}

	return 0;
}
early_param("androidboot.swtype", early_parse_softver_cmdline);

/*****************************************************************************
 函 数 名  : ver_type_is_factory
 功能描述  : 判断是否为工厂版本
 输入参数  : 无
 输出参数  : 无
 返 回 值  : DRV_SOFT_VER_TYPE 版本类型
 调用函数  :
 被调函数  :
*****************************************************************************/
DRV_SOFT_VER_TYPE get_version_type(void)
{
    if(soft_ver_type >= INVALID_VERTYPE_FLAG){
        printk(KERN_ERR "running version is invalid\n");
        return INVALID_VERTYPE_FLAG;
    }

	return soft_ver_type;
}
EXPORT_SYMBOL(get_version_type);

/*****************************************************************************
 函 数 名  : early_parse_reset_cmdline
 功能描述  : parse runmode cmdline which is configured in fastboot.
 输入参数  : char *p
 输出参数  : 无
 返 回 值  : ok/error
 调用函数  : reset_type=0 or 1  1:abnormal reset 0:normal reset
 被调函数  :
*****************************************************************************/
static int __init early_parse_reset_cmdline(char * p)
{
	if(p){
        if (!strcmp(p,"normal")){
        	reset_mode_flag = NORMAL_RESET_FLAG;
        }
        else if(!strcmp(p,"abnormal")){
        	reset_mode_flag = ABNORMAL_RESET_FLAG;
        }

        printk(KERN_DEBUG "reset type is %s, reset_mode_flag = %d\n", p, reset_mode_flag);
	}

	return 0;
}
early_param("reset_type", early_parse_reset_cmdline);

/*****************************************************************************
 函 数 名  : get_reset_reason
 功能描述  : 判断是否为异常复位
 输入参数  : 无
 输出参数  : 无
 返 回 值  : DRV_RESET_TYPE 复位类型
 调用函数  :
 被调函数  :
*****************************************************************************/
DRV_RESET_TYPE get_reset_reason(void)
{
    if(reset_mode_flag >= INVALID_RESET_FLAG){
        printk(KERN_ERR "invalid reset flag\n");
        return NORMAL_RESET_FLAG;
    }

	return reset_mode_flag;
}
EXPORT_SYMBOL(get_reset_reason);

/*****************************************************************************
 函 数 名  : early_parse_pwmode_cmdline
 功能描述  : parse runmode cmdline which is configured in fastboot.
 输入参数  : char *p
 输出参数  : 无
 返 回 值  : ok/error
 调用函数  : power_mode=0 or 1  0:normal 1:recovery
 被调函数  :
*****************************************************************************/
static int __init early_parse_pwmode_cmdline(char * p)
{
	if(p){
        if (!strcmp(p,"recovery")){
        	soft_run_mode = RUN_MODE_RECOVERY;
        }
        else if(!strcmp(p,"normal")){
        	soft_run_mode = RUN_MODE_NORMAL;
        }
        else{
        	soft_run_mode = RUN_MODE_INVALID;
        }

        printk(KERN_DEBUG "run mode is %s, soft_run_mode = %d\n", p, soft_run_mode);
	}

	return 0;
}
early_param("power_mode", early_parse_pwmode_cmdline);

/*****************************************************************************
 函 数 名  : get_run_mode
 功能描述  : 判断是否为异常复位
 输入参数  : 无
 输出参数  : 无
 返 回 值  : DRV_RESET_TYPE 复位类型
 调用函数  :
 被调函数  :
*****************************************************************************/
DRV_RUN_MODE get_run_mode(void)
{
    if(soft_run_mode >= RUN_MODE_INVALID){
        printk(KERN_ERR "invalid reset flag\n");
        return RUN_MODE_NORMAL;
    }

	return soft_run_mode;
}
EXPORT_SYMBOL(get_run_mode);


