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

#ifndef __TAF_DIAG_COMM_H__
#define __TAF_DIAG_COMM_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "msp_diag_comm.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名称  : TAF_DIAG_TRANS_MSG_ID_ENUM
 枚举说明  : TAF透传消息枚举,  []
*****************************************************************************/
enum TAF_DIAG_TRANS_MSG_ID_ENUM
{
    /* TAF层分配区间[0xC800,0xCFFF] */

    /* 预留[0xC800,0xC8FF] */

    /* ADS[0xC900,0xC91F] */
    ID_DIAG_ADS_TRANS_MSG_ID_BASE       = 0xC900,
    ID_DIAG_ADS_UL_IPF_PROC_STATS_IND   = 0xC901,
    ID_DIAG_ADS_DL_IPF_PROC_STATS_IND   = 0xC902,
    ID_DIAG_ADS_UL_PKT_PROC_STATS_IND   = 0xC903,
    ID_DIAG_ADS_DL_PKT_PROC_STATS_IND   = 0xC904,
    ID_DIAG_ADS_THROUGHPUT_STATS_IND    = 0xC905,

    /* RINC[0xC920,0xC93F] */
    ID_DIAG_RNIC_TRANS_MSG_ID_BASE      = 0xC920,

    /* SPE[0xC940,0xC95F] */
    ID_DIAG_SPE_TRANS_MSG_ID_BASE       = 0xC940,
    ID_DIAG_SPE_PORT_0_STATS_IND        = 0xC941,
    ID_DIAG_SPE_PORT_1_STATS_IND        = 0xC942,
    ID_DIAG_SPE_PORT_2_STATS_IND        = 0xC943,
    ID_DIAG_SPE_PORT_3_STATS_IND        = 0xC944,
    ID_DIAG_SPE_PORT_4_STATS_IND        = 0xC945,
    ID_DIAG_SPE_PORT_5_STATS_IND        = 0xC946,
    ID_DIAG_SPE_PORT_6_STATS_IND        = 0xC947,
    ID_DIAG_SPE_PORT_7_STATS_IND        = 0xC948,

    /* XXX */
    ID_DIAG_XXX_TRANS_MSG_ID_BASE       = 0xC960,

    TAF_DIAG_TRANS_MSG_ID_BUTT          = 0xCFFF,
};
typedef VOS_UINT32 TAF_DIAG_TRANS_MSG_ID_ENUM_UINT32;


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/



/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/









#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of TafDiagComm.h */
