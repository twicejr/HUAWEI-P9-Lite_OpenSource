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

#ifndef __MDRV_COMMON_PM_H__
#define __MDRV_COMMON_PM_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "mdrv_om_common.h"

struct mdrv_pm_profile
{
	unsigned int max_profile;
	unsigned int min_profile;
};
typedef enum tagPWC_COMM_MODEM_E
{
    PWC_COMM_MODEM_0 = 0,
    PWC_COMM_MODEM_1 = 1,
    PWC_COMM_MODEM_2 = 2,
    PWC_COMM_MODEM_BUTT
}PWC_COMM_MODEM_E;

typedef enum tagPWC_COMM_MODE_E
{
    PWC_COMM_MODE_GSM=0,
    PWC_COMM_MODE_WCDMA=1,
    PWC_COMM_MODE_LTE=2,
    PWC_COMM_MODE_TDS=3,
    PWC_COMM_MODE_CDMA_1X=4,
    PWC_COMM_MODE_CDMA_HRPD=5,
    PWC_COMM_MODE_NUMBER,
    PWC_COMM_MODE_LCIPHER=PWC_COMM_MODE_NUMBER,
	PWC_COMM_MODE_REMOTE_CLK_W,
	PWC_COMM_MODE_REMOTE_CLK_G,
    PWC_COMM_MODE_BUTT
}PWC_COMM_MODE_E;
/*注意:枚举扩充时，若PWC_COMM_MODEM_BUTT*PWC_COMM_MODE_BUTT > 32时需要知会各投票组件修改投票代码
       不要在PWC_COMM_MODE_CDMA_HRPD之前插入其他外设*/

enum PM_MOD_ID_ENUM
{
    PM_MOD_AP_OSA  =  OM_AP_OSA,
    PM_MOD_CP_OSA  =  OM_CP_OSA,
    PM_MOD_CP_MSP  =  OM_CP_MSP_SLEEP,
};

/*****************************************************************************
* 函 数 名  : mdrv_pm_log
*
* 功能描述  : 输出流程信息到log区
*
* 输入参数  : mod_id	模块id，使用enum OM_FIELD_ID_ENUM枚举类型定义的值
*            data_len	输出数据长度
*            data 		输出数据
* 输出参数  :
*
* 返 回 值  : 0，执行成功；1，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_pm_log(int mod_id,  unsigned int data_len , void *data);

#ifdef __cplusplus
}
#endif
#endif
