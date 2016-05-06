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

#ifndef _SCM_SOFTDECODE_H_
#define _SCM_SOFTDECODE_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "omringbuffer.h"
#include "msp_debug.h"


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

/**************************************************************************
  2 宏定义
**************************************************************************/
#define SCM_DATA_RCV_BUFFER_SIZE    (100*1024)      /* SCM数据接收buffer大小 */
#define SCM_DATA_RCV_PKT_SIZE       (8*1024)        /* SCM数据接收PKT大小 */


/**************************************************************************
  3 枚举定义
**************************************************************************/

/**************************************************************************
  4 结构体定义
**************************************************************************/

/*****************************************************************************
结构名    : SCM_DATE_RCV_CTRL_STRU
结构说明  : SCM数据接收的控制结构
*****************************************************************************/
typedef struct
{
    VOS_SEM                     SmID;
    OM_RING_ID                  rngOmRbufId;
    VOS_CHAR                   *pucBuffer;
}SCM_DATA_RCV_CTRL_STRU;

#if 0
/*****************************************************************************
结构名    : SCM_DATA_RCV_HEADER_STRU
结构说明  : SCM数据接收时放入环形缓冲区的数据头
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  ulLen;
}SCM_DATA_RCV_HEADER_STRU;
#endif

/*****************************************************************************
结构名    : SCM_MAINTENANCE_INFO_STRU
结构说明  : SCM软解码模块可维可测信息记录结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDataLen; /* 接收或发送数据长度 */
    VOS_UINT32                          ulNum;     /* 接收或发送数据次数 */
}SCM_MAINTENANCE_INFO_STRU;

typedef struct
{
    VOS_UINT32                          ulSemCreatErr;
    VOS_UINT32                          ulSemGiveErr;
    VOS_UINT32                          ulRingBufferCreatErr;
    VOS_UINT32                          ulTaskIdErr;
    VOS_UINT32                          ulBufferNotEnough;
    VOS_UINT32                          ulRingBufferFlush;
    VOS_UINT32                          ulRingBufferPutErr;
}SCM_SOFTDECODE_RB_INFO_STRU;


/*****************************************************************************
结构名    : OM_ACPU_PC_UE_SUC_STRU
结构说明  : OM模块正常接收可维可测信息记录结构
*****************************************************************************/
typedef struct
{
    SCM_SOFTDECODE_RB_INFO_STRU         stRbInfo;
    SCM_MAINTENANCE_INFO_STRU           stPutInfo;
    SCM_MAINTENANCE_INFO_STRU           stGetInfo;
    SCM_MAINTENANCE_INFO_STRU           stHdlcDecapData;
    VOS_UINT32                          ulFrameDecapErr;
    VOS_UINT32                          ulHdlcInitErr;
    VOS_UINT32                          ulDataTypeErr;
    VOS_UINT32                          ulCpmRegLogicRcvSuc;
}SCM_SOFTDECODE_INFO_STRU;

/**************************************************************************
  6 函数定义
**************************************************************************/

#if ((OSA_CPU_ACPU == VOS_OSA_CPU)|| (VOS_WIN32 == VOS_OS_VER))

VOS_UINT32 SCM_SoftDecodeCfgDataRcv(VOS_UINT8 *pucBuffer, VOS_UINT32 ulLen);

VOS_UINT32 SCM_SoftDecodeDataRcv(VOS_UINT8 *pucBuffer, VOS_UINT32 ulLen);

VOS_UINT32 SCM_SoftDecodeCfgRcvTaskInit(VOS_VOID);

VOS_UINT32 CBTSCM_SoftDecodeReqRcvTaskInit(VOS_VOID);

VOS_VOID   SCM_SoftDecodeCfgRcvSelfTask(
    VOS_UINT32                          ulPara1,
    VOS_UINT32                          ulPara2,
    VOS_UINT32                          ulPara3,
    VOS_UINT32                          ulPara4);

VOS_VOID   CBTSCM_SoftDecodeReqRcvSelfTask(
    VOS_UINT32                          ulPara1,
    VOS_UINT32                          ulPara2,
    VOS_UINT32                          ulPara3,
    VOS_UINT32                          ulPara4);



#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif


