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

#ifndef __MDRV_ACORE_CHG_H__
#define __MDRV_ACORE_CHG_H__

#include "mdrv_public.h"
#ifdef __cplusplus
extern "C"
{
#endif

typedef enum CHARGING_STATE_E_tag
{
        CHARGING_INIT = -1,
        NO_CHARGING_UP = 0,  /*开机未充电*/
        CHARGING_UP ,              /*开机正充电*/
        NO_CHARGING_DOWN ,  /*关机未充电*/
        CHARGING_DOWN         /*关机未充电*/
}CHARGING_STATE_E;

typedef enum BATT_LEVEL_E_tag
{
        BATT_INIT = -2,
        BATT_LOW_POWER =-1,    /*电池低电*/
        BATT_LEVEL_0,          /*0格电池电量*/
        BATT_LEVEL_1,          /*1格电池电量*/
        BATT_LEVEL_2,          /*2格电池电量*/
        BATT_LEVEL_3,          /*3格电池电量*/
        BATT_LEVEL_4,          /*4格电池电量*/
        BATT_LEVEL_MAX
}BATT_LEVEL_E;

typedef struct BATT_STATE_tag
{
    CHARGING_STATE_E  charging_state;
    BATT_LEVEL_E      battery_level;
}BATT_STATE_S;

/*****************************************************************************
 函 数 名  : mdrv_misc_get_battery_state
 功能描述  :获取底层电池状态信息
 输入参数  :battery_state 电量信息
 输出参数  :battery_state 电量信息
 返回值：   0 操作成功
                         -1操作失败

*****************************************************************************/
int mdrv_misc_get_battery_state(BATT_STATE_S *battery_state);


/*****************************************************************************
 函 数 名  : mdrv_misc_get_charging_status
 功能描述  :查询目前是否正在充电中
 输入参数  :无
 输出参数  :无
 返回值：   0 未充电
                          1 充电中
*****************************************************************************/
int mdrv_misc_get_charging_status(void);


/*****************************************************************************
 函 数 名  : mdrv_misc_set_charge_state
 功能描述  :使能或者禁止充电
 输入参数  :ulState      0:禁止充电
 						1:使能充电
 输出参数  :无
 返回值：    无
*****************************************************************************/
void mdrv_misc_set_charge_state(unsigned long ulState);

/*****************************************************************************
 函 数 名  : mdrv_misc_get_charge_state
 功能描述  :查询
 输入参数  :
 输出参数  :无
 返回值：    无
*****************************************************************************/
int mdrv_misc_get_charge_state(void);


/*****************************************************************************
 函 数 名  : mdrv_misc_sply_battery
 功能描述  :查询
 输入参数  :
 输出参数  :无
 返回值：    无
*****************************************************************************/
int mdrv_misc_sply_battery(void);


/*****************************************************************************
 函 数 名  : mdrv_misc_get_cbc_state
 功能描述  : 返回电池状态和电量
 输入参数  :pusBcs 0:电池在供电 1:与电池连接电池未供电 2:没有与电池连接
                          pucBcl  0:电量不足或没有与电池连接
 输出参数  : pusBcs 0:电池在供电 1:与电池连接电池未供电 2:没有与电池连接
                          pucBcl  0:电量不足或没有与电池连接
 返回值：   0 操作成功
                         -1操作失败

*****************************************************************************/
int mdrv_misc_get_cbc_state(unsigned char *pusBcs,unsigned char *pucBcl);


#ifdef __cplusplus
}
#endif
#endif

