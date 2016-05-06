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

#ifndef __MDRV_HKADC_COMMON_H__
#define __MDRV_HKADC_COMMON_H__
#ifdef __cplusplus
extern "C"
{
#endif

/*HKADC延时转换模式*/
typedef enum tagHKADC_CONV_MODE_E
{
    HKADC_CONV_DELAY =0,
    HKADC_CONV_NO_DELAY,
    HKADC_CONV_BUTT
}HKADC_CONV_MODE_E;

typedef enum HKADC_TEMP_PROTECT_E
{
    HKADC_TEMP_TOP = 0,
    HKADC_TEMP_BATTERY = HKADC_TEMP_TOP,     /*0*/
    HKADC_TEMP_PA0,                          /*1*/
    HKADC_TEMP_PA1,                          /*2*/
    HKADC_TEMP_XO0,                        /*3*/
    HKADC_TEMP_XO0_LOW,                    /*4*/
    HKADC_TEMP_XO1,                        /*5*/
    HKADC_TEMP_XO1_LOW,                    /*6*/
    HKADC_TEMP_LCD,                          /*7*/
    HKADC_TEMP_SIM_CARD,                     /*8*/
    HKADC_TEMP_SYSTEMH,                      /*9*/
    HKADC_TEMP_SYSTEML,                      /*10*/
    HKADC_TEMP_BATT_ID,                      /*11*/
    HKADC_TEMP_CAMERA0_ID,                   /*12*/
    HKADC_TEMP_CAMERA1_ID,                   /*13*/
    HKADC_TEMP_CODEC,                        /*14*/
    HKADC_TEMP_CHARGER_ID,                   /*15*/
    HKADC_TEMP_BAT_ET,						 /*16*/
    HKADC_TEMP_BUTT
}HKADC_TEMP_PROTECT_E;


/*****************************************************************************
     *  函 数 名  : mdrv_hkadc_get_temp
     *  功能描述  :  获取HKADC通道的电压和温度值。
     *  输入参数  :
     *
     *  输出参数  : 无
     *  返 回 值  :  0         操作成功。
        *                           其他    操作失败。
         *
     ******************************************************************************/
int mdrv_hkadc_get_temp (HKADC_TEMP_PROTECT_E enMode, unsigned short* pusVolt, short* psTemp, HKADC_CONV_MODE_E ulMode);

/*****************************************************************************
* 函 数 名  : mdrv_hkadc_get_phy_temp
* 功能描述  : 获取HKADC物理通道usPhyChannel表征的温度、电压
* 输入参数  : usPhyChannel: hkadc的物理通道
*			  ulMode: 转换模式
* 输出参数  : *pusVolt: 存储电压值
*			  *pstTemp: 存储温度值
* 返 回 值  : 成功返回0，失败返回非0
* 其它说明  : 无
*****************************************************************************/
signed int mdrv_hkadc_get_phy_temp(unsigned short usPhyChannel, unsigned short *pusVolt, short *pstTemp, HKADC_CONV_MODE_E ulMode);

#ifdef __cplusplus
}
#endif
#endif
