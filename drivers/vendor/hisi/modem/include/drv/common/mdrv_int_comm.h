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

#ifndef __MDRV_INT_COMMON_H__
#define __MDRV_INT_COMMON_H__
#ifdef __cplusplus
extern "C"
{
#endif

/*中断类型。*/
typedef enum tagBSP_INT_TYPE_E
{
    BSP_INT_TYPE_RTC = 0,
    BSP_INT_TYPE_WDT,
    BSP_INT_TYPE_USBOTG,
    BSP_INT_TYPE_UICC,
    BSP_INT_TYPE_IPF_C,
    BSP_INT_TYPE_IPF_A,
    BSP_INT_TYPE_SOCP_A,
    BSP_INT_TYPE_SOCP_C,
    BSP_INT_TYPE_CICOM_UL,
    BSP_INT_TYPE_CICOM_DL,
    BSP_INT_TYPE_CICOM1_UL,
    BSP_INT_TYPE_CICOM1_DL,
    BSP_INT_TYPE_HDLC_DEF,
    BSP_INT_TYPE_HDLC_FRM,
    BSP_INT_TYPE_GBBP,
    BSP_INT_TYPE_GBBP_AWAKE,
    BSP_INT_TYPE_GBBP_DSP,
    BSP_INT_TYPE_GBBP_AWAKE_DSP,
    BSP_INT_TYPE_GBBP1,
    BSP_INT_TYPE_GBBP1_AWAKE,
    BSP_INT_TYPE_GBBP1_DSP,
    BSP_INT_TYPE_GBBP1_AWAKE_DSP,
    BSP_INT_TYPE_WBBP_0MS,
    BSP_INT_TYPE_WBBP_AWAKE,
    BSP_INT_TYPE_WBBP_SWITCH,
    BSP_INT_TYPE_WBBP1_0MS,
    BSP_INT_TYPE_WBBP_SEARCH,
    BSP_INT_TYPE_WBBP_RAKE,
    BSP_INT_TYPE_WBBP_DECODE,
    BSP_INT_TYPE_WBBP_TIME,
    BSP_INT_TYPE_WBBP1_TIME,
    BSP_INT_TYPE_WBBP_MULTI_SEARCH,
    BSP_INT_TYPE_WBBP_BBPMST,
    BSP_INT_TYPE_TBBP_AWAKE,
    BSP_INT_TYPE_LBBP_AWAKE,
    BSP_INT_TYPE_UPACC_DSP,
    BSP_INT_TYPE_INT_OSRTC,
    BSP_INT_TYPE_INT_SMIM,
    BSP_INT_TYPE_INT_ZSP_DOG,
    BSP_INT_TYPE_INT_HIFI_DOG,
    BSP_INT_TYPE_INT12_G2,
    BSP_INT_TYPE_ODTOA_INT12,
    BSP_INT_TYPE_CTU_INT_W,
    BSP_INT_TYPE_CTU_INT_G,
    BSP_INT_TYPE_CTU_INT_LTE,
    BSP_INT_TYPE_CTU_INT_TDS,
    BSP_INT_TYPE_UPACC_INTR,
    BSP_INT_TYPE_GBBP_GSML_RESERVED_INTR,
    BSP_INT_TYPE_LTE_CIPHER,
    BSP_INT_TYPE_LTE_APP_ARM_PUB,
    BSP_INT_TYPE_LTE_ARM_POSITIONS,
    BSP_INT_TYPE_LTE_DL_DMA,
    BSP_INT_TYPE_LTE_ARM_POSITION,
    BSP_INT_TYPE_LTE_ARM_DL_DMA,
    BSP_INT_TYPE_LTE_ARM_CLK_SWITCH,
    BSP_INT_TYPE_LTE_ARM_WAKEUP,
    BSP_INT_TYPE_LTE_PUB,
    BSP_INT_TYPE_TDS_STU_ARM1,
    BSP_INT_TYPE_TDS_DRX_ARM1,
    BSP_INT_TYPE_TDS_DRX_ARM2,
    BSP_INT_TYPE_BBE16_GPIO1,
    BSP_INT_TYPE_G2_INT_BBP_TO_CPU_32K,
    BSP_INT_TYPE_G2_INT_BBP_TO_CPU,
    BSP_INT_TYPE_G2_INT_BBP_TO_DSP_32K,
    BSP_INT_TYPE_G2_INT_BBP_TO_DSP,
    BSP_INT_TYPE_GBBP_GSML_NODRX_INTR,
    BSP_INT_TYPE_WBBP_CARD2_0MS_INTR,
    BSP_INT_TYPE_WBBP_SEARCH_INTR,
    BSP_INT_TYPE_WBBP_RAKE_INTR,
    BSP_INT_TYPE_WBBP_DECODE_INTR,
    BSP_INT_TYPE_WBBP_CARD1_TIME_INTR,
    BSP_INT_TYPE_WBBP_CARD2_TIME_INTR,
    BSP_INT_TYPE_WBBP_MULTI_SEARCH_INTR,
    BSP_INT_TYPE_BBPMASTER,
    BSP_INT_TYPE_CBBP_INTR01,         /*CDMA1x或CDMA EVDO睡眠/唤醒中断(32K)*/
    BSP_INT_TYPE_CBBP_INTR02,         /*CDMA1x或CDMA EVDO切换中断(imi时钟)*/
    BSP_INT_TYPE_CBBP_INTR04,         /*CDMA1x或CDMA EVDO定时中断*/
    BSP_INI_TYPE_COMM_32K_INT,        /*用于DSDS的32K公共定时器，按照软件配置的周期产生中断*/
    BSP_INT_TYPE_GUCBBP_AXIMST_ERR0,  /* GUC BBP AXI MST输出的错误中断，上报给ARM CCPU处理，在v7r5落实。xuwenfang,huangqihua确认 */
BSP_INT_TYPE_BUTTOM
} BSP_INT_TYPE_E;

/*****************************************************************************
	 *  函 数 名  : mdrv_int_enable
	 *  功能描述  :  如果输入的中断为VIC的中断号，接口内部调用vic的接口使能；
        *                             如果输入的中断为GIC的中断号，接口内部调用gic的接口使能；
	 *  输入参数  :
	 *
	 *  输出参数  : 无
	 *  返 回 值  :  0	       操作成功。
        *                           其他	操作失败。
     	 *
	 ******************************************************************************/
int  mdrv_int_enable(int ulLev);

/*****************************************************************************
	 *  函 数 名  : mdrv_int_enable
	 *  功能描述  :  如果输入的中断为VIC的中断号，接口内部调用vic的接口去使能；
        *                             如果输入的中断为GIC的中断号，接口内部调用gic的接口去使能；
	 *  输入参数  :
	 *
	 *  输出参数  : 无
	 *  返 回 值  :  0	       操作成功。
        *                           其他	操作失败。
     	 *
	 ******************************************************************************/
int mdrv_int_disable(int ulLev);

/*****************************************************************************
	 *  函 数 名  : mdrv_int_connect
	 *  功能描述  :  如果输入的中断为VIC的中断号，接口内部调用vic的接口挂中断处理函数；
        *                             如果输入的中断为GIC的中断号，接口内部调用gic的接口挂中断处理函数；
	 *  输入参数  :
	 *
	 *  输出参数  : 无
	 *  返 回 值  :  0	       操作成功。
        *                           其他	操作失败。
     	 *
	 ******************************************************************************/
int mdrv_int_connect(int level, VOIDFUNCPTR routine, unsigned int parameter);

/*****************************************************************************
	 *  函 数 名  : mdrv_int_disconnect
	 *  功能描述  :  如果输入的中断为VIC的中断号，接口内部调用vic的接口去除中断处理函数；
        *                             如果输入的中断为GIC的中断号，接口内部调用gic的接口去除中断处理函数；
	 *  输入参数  :
	 *
	 *  输出参数  : 无
	 *  返 回 值  :  0	       操作成功。
        *                           其他	操作失败。
     	 *
	 ******************************************************************************/
int mdrv_int_disconnect(int level, unsigned int parameter);

/*****************************************************************************
	 *  函 数 名  : mdrv_int_get_num
	 *  功能描述  :  中断号查询。
	 *  输入参数  : enIntType: 需要查询的中断类型
	 *
	 *  输出参数  : 无
	 *  返 回 值  :  中断号
        *
     	 *
	 ******************************************************************************/
int mdrv_int_get_num (BSP_INT_TYPE_E enIntType);

/*****************************************************************************
	 *  函 数 名  : mdrv_int_get_num_byname
	 *  功能描述  :  中断号查询。
	 *  输入参数  : 中断号名字，字符串必须以'\0'结束
	 *
	 *  输出参数  : 无
	 *  返 回 值  :  中断号
        *
     	 *
	 ******************************************************************************/
int mdrv_int_get_num_byname(const char * int_name);

#ifdef __cplusplus
}
#endif

#endif

