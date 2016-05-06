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

#ifndef __SYS_HDLC_H__
#define __SYS_HDLC_H__


//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//#include <gu_busstress_type.h>
#include "baseaddr.h"
#include "basicfunc.h"
#include "mem_fun.h"
#include <sys_bus_pressure.h>
//#include "../dmac.h"
//#include "../dma/dma_reg.h"

#define  HDLC_Test_Num  500

#ifdef _SRAM0_TEST
#define  EXT_FRM_RAW_DATA_ADDR		SRAM0_BASEADDR
#define  EXT_FRM_CHECK_DATA_ADDR		SRAM0_BASEADDR + 0x10000
#define  EXT_FRM_OUT_SPC_ADDR			SRAM0_BASEADDR + 0x20000
#define  EXT_FRM_IN_MAIN_LLI_ADDR		SRAM0_BASEADDR + 0x30000
#define  EXT_FRM_IN_SUB_LLI_ADDR		SRAM0_BASEADDR + 0x34000
#define  EXT_FRM_OUT_LLI_ADDR			SRAM0_BASEADDR + 0x38000
#define  EXT_FRM_RPT_ADDR				SRAM0_BASEADDR + 0x3C000

#define  EXT_DEF_RAW_DATA_ADDR		SRAM0_BASEADDR + 0x40000
#define  EXT_DEF_CHECK_DATA_ADDR		SRAM0_BASEADDR + 0x50000
#define  EXT_DEF_OUT_SPC_ADDR			SRAM0_BASEADDR + 0x60000
#define  EXT_DEF_IN_LLI_ADDR			SRAM0_BASEADDR + 0x70000
#define  EXT_DEF_RPT_ADDR				SRAM0_BASEADDR + 0x74000
#endif


#ifdef _MDDR_TEST
#define  EXT_FRM_RAW_DATA_ADDR		MDDR_BASEADDR
#define  EXT_FRM_CHECK_DATA_ADDR		MDDR_BASEADDR + 0x20000
#define  EXT_FRM_OUT_SPC_ADDR			MDDR_BASEADDR + 0x60000
#define  EXT_FRM_IN_MAIN_LLI_ADDR		MDDR_BASEADDR + 0xa0000
#define  EXT_FRM_IN_SUB_LLI_ADDR		MDDR_BASEADDR + 0xa8000
#define  EXT_FRM_OUT_LLI_ADDR			MDDR_BASEADDR + 0xb0000
#define  EXT_FRM_RPT_ADDR				MDDR_BASEADDR + 0xb8000

#define  EXT_DEF_RAW_DATA_ADDR		MDDR_BASEADDR + 0x100000
#define  EXT_DEF_CHECK_DATA_ADDR		MDDR_BASEADDR + 0x140000
#define  EXT_DEF_OUT_SPC_ADDR			MDDR_BASEADDR + 0x180000
#define  EXT_DEF_IN_LLI_ADDR			MDDR_BASEADDR + 0x1C0000
#define  EXT_DEF_RPT_ADDR				MDDR_BASEADDR + 0x1C8000
#endif
//*******************************
// Define registers' offset
//*******************************
#define BASE_ADDR             	HDLC_BASEADDR

//#ifdef HIHDLCV200
//#define BASE_ADDR          	0x5f0c0000
//#endif

//registers' offset
//general
#define  STATE_SW_RST			BASE_ADDR + 0x00
#define  PRIOR_TIMEOUT_CTRL		BASE_ADDR + 0x04
#define  RD_ERR_CURR_ADDR		BASE_ADDR + 0x08
#define  WR_ERR_CURR_ADDR		BASE_ADDR + 0x0c

//framer
#define  HDLC_FRM_EN			BASE_ADDR + 0x10
#define  HDLC_FRM_RAW_INT		BASE_ADDR + 0x14
#define  HDLC_FRM_INT_STATUS	BASE_ADDR + 0x18
#define  HDLC_FRM_INT_CLR		BASE_ADDR + 0x1c
#define  HDLC_FRM_CFG			BASE_ADDR + 0x20
#define  HDLC_FRM_ACCM			BASE_ADDR + 0x24
#define  HDLC_FRM_STATUS		BASE_ADDR + 0x28
#define  FRM_IN_LLI_ADDR		BASE_ADDR + 0x30
#define  FRM_IN_SUBLLI_ADDR		BASE_ADDR + 0x34
#define  FRM_IN_PKT_LEN			BASE_ADDR + 0x38
#define  FRM_IN_BLK_ADDR		BASE_ADDR + 0x3c
#define  FRM_IN_BLK_LEN			BASE_ADDR + 0x40
#define  FRM_OUT_LLI_ADDR		BASE_ADDR + 0x44
#define  FRM_OUT_SPC_ADDR		BASE_ADDR + 0x48
#define  FRM_OUT_SPC_DEP		BASE_ADDR + 0x4c
#define  FRM_RPT_ADDR			BASE_ADDR + 0x50
#define  FRM_RPT_DEP			BASE_ADDR + 0x54
//deframer
#define  HDLC_DEF_EN			BASE_ADDR + 0x60
#define  HDLC_DEF_RAW_INT		BASE_ADDR + 0x64
#define  HDLC_DEF_INT_STATUS	BASE_ADDR + 0x68
#define  HDLC_DEF_INT_CLR		BASE_ADDR + 0x6c
#define  HDLC_DEF_CFG			BASE_ADDR + 0x70
#define  DEF_UNCOMPLETED_LEN	BASE_ADDR + 0x74
#define  DEF_UNCOMPLETED_PRO	BASE_ADDR + 0x78
#define  DEF_UNCOMPLETED_ADDR	BASE_ADDR + 0x7c
#define  DEF_UNCOMPLETED_ST_AGO	BASE_ADDR + 0x80
#define  HDLC_DEF_GO_ON			BASE_ADDR + 0x84
#define  HDLC_DEF_STATUS		BASE_ADDR + 0x88
#define  DEF_UNCOMPLETED_ST_NOW	BASE_ADDR + 0x8c
#define  DEF_IN_LLI_ADDR		BASE_ADDR + 0x90
#define  DEF_IN_PKT_ADDR		BASE_ADDR + 0x94
#define  DEF_IN_PKT_LEN			BASE_ADDR + 0x98
#define  DEF_IN_PKT_LEN_MAX		BASE_ADDR + 0x9c
#define  DEF_OUT_SPC_ADDR		BASE_ADDR + 0xa0
#define  DEF_OUT_SPC_DEP		BASE_ADDR + 0xa4
#define  DEF_RPT_ADDR			BASE_ADDR + 0xa8
#define  DEF_RPT_DEP			BASE_ADDR + 0xac
#define  HDLC_DEF_ERR_INFO_0	BASE_ADDR + 0xb0
#define  HDLC_DEF_ERR_INFO_1	BASE_ADDR + 0xb4
#define  HDLC_DEF_ERR_INFO_2	BASE_ADDR + 0xb8
#define  HDLC_DEF_ERR_INFO_3	BASE_ADDR + 0xbc
#define  DEF_INFO_FRL_CNT_AGO	BASE_ADDR + 0xc0
#define  DEF_INFO_FRL_CNT_NOW	BASE_ADDR + 0xc4

void sys_hdlc_init(struct master* master);

#endif /* __SYS_HDLC_H__ */
