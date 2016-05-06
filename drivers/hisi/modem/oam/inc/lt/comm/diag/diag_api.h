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


#ifndef __DIAG_API_H__
#define __DIAG_API_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"
#include  "msp_diag.h"
#pragma pack(4)

/*****************************************************************************
  2 macro
*****************************************************************************/

/* diag初始化成功且HSO连接上 */
#define  DIAG_IS_CONN_ON            ((g_ulDiagCfgInfo & (DIAG_CFG_INIT | DIAG_CFG_CONN )) == (DIAG_CFG_INIT | DIAG_CFG_CONN ))

/* 允许LT 空口上报 */
#define  DIAG_IS_LT_AIR_ON          ((g_ulDiagCfgInfo & (DIAG_CFG_INIT | DIAG_CFG_CONN | DIAG_CFG_LT_AIR)) == (DIAG_CFG_INIT | DIAG_CFG_CONN | DIAG_CFG_LT_AIR))

/* 允许GU 空口上报 */
#define  DIAG_IS_GU_AIR_ON          ((g_ulDiagCfgInfo & (DIAG_CFG_INIT | DIAG_CFG_CONN | DIAG_CFG_GU_AIR)) == (DIAG_CFG_INIT | DIAG_CFG_CONN | DIAG_CFG_GU_AIR))

/* 允许事件上报 */
#define  DIAG_IS_EVENT_ON           ((g_ulDiagCfgInfo & (DIAG_CFG_INIT | DIAG_CFG_CONN | DIAG_CFG_EVT)) == (DIAG_CFG_INIT | DIAG_CFG_CONN | DIAG_CFG_EVT))


#define DIAG_GET_MODEM_ID(id)               (id >> 24)
#define DIAG_GET_MODE_ID(id)                ((id & 0x000F0000)>>16)
#define DIAG_GET_PRINTF_LEVEL(id)           ((id & 0x0000F000)>>12)
#define DIAG_GET_GROUP_ID(id)               ((id & 0x00000F00)>>8)
#define DIAG_GET_MODULE_ID(id)              ( id & 0x00000FFF)

/* 日志类型定义*/
#define DIAG_CMD_LOG_CATETORY_PRINT_ID              (1<<15)
#define DIAG_CMD_LOG_CATETORY_EVENT_ID              (1<<14)
#define DIAG_CMD_LOG_CATETORY_AIR_ID                (1<<13)
#define DIAG_CMD_LOG_CATETORY_LAYER_ID              (1<<12)
#define DIAG_CMD_LOG_CATETORY_MSG_ID                (1<<10)
#define DIAG_CMD_LOG_CATETORY_USERPLANE_ID          (1<<9)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
   5 STRUCT
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulPrintNum;
    VOS_UINT32 ulAirNum;
    VOS_UINT32 ulVoLTENum;
    VOS_UINT32 ulLayerNum;
    VOS_UINT32 ulUserNum;
    VOS_UINT32 ulEventNum;
    VOS_UINT32 ulTransNum;

    VOS_SPINLOCK    ulPrintLock;
    VOS_SPINLOCK    ulAirLock;
    VOS_SPINLOCK    ulVoLTELock;
    VOS_SPINLOCK    ulLayerLock;
    VOS_SPINLOCK    ulUserLock;
    VOS_SPINLOCK    ulEventLock;
    VOS_SPINLOCK    ulTransLock;
} DIAG_LOG_PKT_NUM_ACC_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern VOS_UINT32 g_ulTransId;
extern DIAG_LOG_PKT_NUM_ACC_STRU g_DiagLogPktNum;

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_CHAR * diag_GetFileNameFromPath(VOS_CHAR* pcFileName);


/*****************************************************************************
  9 OTHERS
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

#endif /* end of diag_api.h */

