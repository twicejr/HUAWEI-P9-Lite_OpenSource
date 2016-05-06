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

#ifndef __MDRV_MISC_COMMON_H__
#define __MDRV_MISC_COMMON_H__
#ifdef __cplusplus
extern "C"
{
#endif

/*IP类型:新增加IP类型必须从后面添加(BSP_IP_TYPE_BUTTOM之前)，
         不允许从中间插入、不允许删除已有类型。*/
typedef enum tagBSP_IP_TYPE_E
{
    BSP_IP_TYPE_SOCP = 0x0,
    BSP_IP_TYPE_CICOM0,
    BSP_IP_TYPE_CICOM1,
    BSP_IP_TYPE_HDLC,
    BSP_IP_TYPE_BBPMASTER,
    BSP_IP_TYPE_ZSP_ITCM,
    BSP_IP_TYPE_ZSP_DTCM,
    BSP_IP_TYPE_AHB,
    BSP_IP_TYPE_WBBP,
    BSP_IP_TYPE_WBBP_DRX,
    BSP_IP_TYPE_GBBP,
    BSP_IP_TYPE_GBBP_DRX,
    BSP_IP_TYPE_GBBP1,
    BSP_IP_TYPE_GBBP1_DRX,
    BSP_IP_TYPE_ZSPDMA,
    BSP_IP_TYPE_SYSCTRL,
    BSP_IP_TYPE_SYSCTRL_PD,
    BSP_IP_TYPE_SYSCTRL_MDM,
    BSP_IP_TYPE_CTU,
    BSP_IP_TYPE_TDSSYS,
    BSP_IP_TYPE_ZSPDHI,
    BSP_IP_TYPE_BBPDMA,
    BSP_IP_TYPE_BBPDBG,
    BSP_IP_TYPE_BBPSRC,
    BSP_IP_TYPE_BBP_COMM,
    BSP_IP_TYPE_BBP_COMM_ON,
    BSP_IP_TYPE_BBP_CDMA,
    BSP_IP_TYPE_BBP_CDMA_ON,
    BSP_IP_TYPE_BBP_GLB_ON,
    BSP_IP_TYPE_BBP_GSDR,
    BSP_IP_TYPE_UPACC,
    BSP_IP_TYPE_HARQ_RAM,
    BSP_IP_TYPE_PERI_SYSCTRL,

    BSP_IP_TYPE_BUTTOM
}BSP_IP_TYPE_E;

/*是否支持模块*/
typedef enum tagBSP_MODULE_SUPPORT_E
{
    BSP_MODULE_SUPPORT     = 0,
    BSP_MODULE_UNSUPPORT   = 1,
    BSP_MODULE_SUPPORT_BUTTOM
}BSP_MODULE_SUPPORT_E;

typedef enum tagESP_MODULE_TYPE_E
{
	BSP_MODULE_TYPE_SD  = 0x0,
	BSP_MODULE_TYPE_CHARGE ,
	BSP_MODULE_TYPE_WIFI ,
	BSP_MODULE_TYPE_OLED ,
	BSP_MODULE_TYPE_HIFI,
	BSP_MODULE_TYPE_POWER_ON_OFF,
	BSP_MODULE_TYPE_HSIC,
	BSP_MODULE_TYPE_HSIC_NCM,
	BSP_MODULE_TYPE_LOCALFLASH,
	BSP_MODULE_TYPE_BOTTOM
}BSP_MODULE_TYPE_E;

/*****************************************************************************
	 *  函 数 名  : mdrv_misc_get_ip_baseaddr
	 *  功能描述  :  IP地址查询。
	 *  输入参数  :
	 *
	 *  输出参数  : 无
	 *  返 回 值  : null
   *         
	 ******************************************************************************/
void* mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_E enIPType);

/*****************************************************************************
	 *  函 数 名  : mdrv_misc_get_ip_baseaddr_byname
	 *  功能描述  :  IP地址查询。
	 *  输入参数  : IP的名字，字符串必须以'\0'结束
	 *
	 *  输出参数  : 无
	 *  返 回 值  : null
   *         
	 ******************************************************************************/
void * mdrv_misc_get_ip_baseaddr_byname(const char * ip_name);

/*****************************************************************************
	 *  函 数 名  : bsp_misc_support_check
	 *  功能描述  : 查询某模块是否支持。
	 *  输入参数  :
	 *
	 *  输出参数  : 无
	 *  返 回 值  :  0	       操作成功。
        *                           其他	操作失败。
     	 *
	 ******************************************************************************/
BSP_MODULE_SUPPORT_E mdrv_misc_support_check (BSP_MODULE_TYPE_E module_type);



#ifdef __cplusplus
}
#endif
#endif

