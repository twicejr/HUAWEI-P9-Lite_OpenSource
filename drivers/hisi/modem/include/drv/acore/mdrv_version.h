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

#ifndef _MDRV_ACORE_VERSION_H_
#define _MDRV_ACORE_VERSION_H_

#ifdef _cplusplus
extern "C"
{
#endif

#define BUILD_DATE_LEN  12
#define BUILD_TIME_LEN  12

/*memVersionCtrl接口操作类型*/
#define VERIONREADMODE                  0
#define VERIONWRITEMODE                1



typedef enum{
	 BOARD_TYPE_BBIT    = 0,
	 BOARD_TYPE_SFT,
	 BOARD_TYPE_ASIC,
	 BOARD_TYPE_MAX
}BOARD_ACTUAL_TYPE_E;

typedef enum{
     PV500_CHIP             = 0,
     V7R1_CHIP              = 1,
     PV500_PILOT_CHIP,
     V7R1_PILOT_CHIP,
     V7R2_CHIP              = 5,
     V8R1_PILOT_CHIP        = 0x8,
}BSP_CHIP_TYPE_E;

typedef struct  tagMPRODUCT_INFO_S
{
	unsigned char *  productname;  /*芯片名称 */ /* BSP*/
	unsigned int   productnamelen;
	BSP_CHIP_TYPE_E echiptype;  /* PV500_CHIP V7R1_CHIP? */
	unsigned int  platforminfo ;     /* FPGA ASIC?*/
	BOARD_ACTUAL_TYPE_E eboardatype;   /*BBIT SFT ASIC FOR */
} MPRODUCT_INFO_S;

/* 芯片Modem 的软件版本信息*/
typedef  struct  tagMSW_VER_INFO_S
{
	unsigned short  ulVVerNO;
	unsigned short  ulRVerNO;
	unsigned short  ulCVerNO;
	unsigned short  ulBVerNO;
	unsigned short  ulSpcNO;
	unsigned short  ulCustomNOv;
	unsigned int    ulProductNo;
	unsigned char  acBuildDate[BUILD_DATE_LEN];
	unsigned char  acBuildTime[BUILD_TIME_LEN];
} MSW_VER_INFO_S;

typedef  struct  tagMHW_VER_INFO_S
{
	int  hwindex;  /* HKADC检测到的硬件ID号(板级）*/
	unsigned int  hwidsub;  /* HKADC检测到的子版本号*/
	unsigned char *  hwfullver;  /* 硬件版本信息 MBB使用 */
	unsigned int  hwfullverlen;
	unsigned char *  hwname;  /* 外部产品名称  MBB使用 CPE? */
	unsigned int  hwnamelen;
	unsigned char *  hwinname;  /* 内部产品名称  MBB使用*/
	unsigned int  hwinnamelen;
} MHW_VER_INFO_S;

typedef struct  tagMODEM_VER_INFO_S
{
	MPRODUCT_INFO_S  stproductinfo;
	MSW_VER_INFO_S  stswverinfo;
	MHW_VER_INFO_S  sthwverinfo;
} MODEM_VER_INFO_S;

typedef enum
{
	VER_BOOTLOAD = 0,
	VER_BOOTROM = 1,
	VER_NV = 2,
	VER_VXWORKS = 3,
	VER_DSP = 4,
	VER_PRODUCT_ID = 5,
	VER_WBBP = 6,
	VER_PS = 7,
	VER_OAM = 8,
	VER_GBBP = 9,
	VER_SOC = 10,
	VER_HARDWARE = 11,
	VER_SOFTWARE = 12,
	VER_MEDIA = 13,
	VER_APP = 14,
	VER_ASIC = 15,
	VER_RF = 16,
	VER_PMU = 17,
	VER_PDM = 18,
	VER_PRODUCT_INNER_ID = 19,
	VER_INFO_NUM = 20
} COMP_TYPE_E;



/*****************************************************************************
 函 数 名  : mdrv_ver_get_info
 功能描述  : 返回modem版本信息
****************************************************************************/
const MODEM_VER_INFO_S * mdrv_ver_get_info(void);



#ifdef _cplusplus
}
#endif
#endif

