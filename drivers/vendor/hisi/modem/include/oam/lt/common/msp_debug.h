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


#ifndef __MSP_DEBUG_H__
#define __MSP_DEBUG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "product_config.h"
#include  "vos.h"

#pragma pack(4)


#define DIAG_DEBUG_START        (0xaaaa5555)
#define DIAG_DEBUG_END          (0x5555aaaa)

/* debug版本 V1.00 */
#define DIAG_DEBUG_VERSION      (0x00010000)

/* debug提示信息的长度 */
#define DIAG_DEBUG_INFO_LEN     (32)

/* 两次数据采集的时间间隔 */
#define DIAG_DEBUG_DEALAY       (5000)

/* 复杂的数据结构，存储信息前先存储信息长度，高8位是0xa5，低24位是数据长度 */
#define DIAG_DEBUG_SIZE_FLAG    (0xa5000000)


/* PTR ***********************************************************************/
#if((VOS_OS_VER == VOS_LINUX) || (VOS_OS_VER == VOS_WIN32))

/*
初步估计每个诊断命令由10-20个点能覆盖整个处理流程，
1000个点能缓存50-100个诊断命令的处理流程
*/
#define DIAG_PTR_NUMBER             (1000)

typedef enum
{
    EN_DIAG_PTR_BEGIN = 0,
    EN_DIAG_PTR_PPM_READDATA,
    EN_DIAG_PTR_CPM_COMRCV,
    EN_DIAG_PTR_SCM_SOFTDECODE,
    EN_DIAG_PTR_SCM_SELFTASK,
    EN_DIAG_PTR_SCM_RCVDATA,
    EN_DIAG_PTR_SCM_RCVDATA_SUCCESS,
    EN_DIAG_PTR_SCM_DISPATCH,
    EN_DIAG_PTR_MSP_SERVICE_1,
    EN_DIAG_PTR_MSP_SERVICE_2,
    EN_DIAG_PTR_SERVICE_IN,
    EN_DIAG_PTR_SERVICE_1,
    EN_DIAG_PTR_MESSAGE_IN,
    EN_DIAG_PTR_MESSAGE_PROC,
    EN_DIAG_PTR_MSGMSP_IN,
    EN_DIAG_PTR_MSGMSP_TRANS,
    EN_DIAG_PTR_MSGMSP_PS_IN,
    EN_DIAG_PTR_MSGMSP_PS_OUT,
    EN_DIAG_PTR_MSGMSP_CONN_IN,
    EN_DIAG_PTR_MSGMSP_DISCONN_IN,
    EN_DIAG_PTR_MESSAGE_REPORT,
    EN_DIAG_PTR_SERVICE_PACKETDATA,
    EN_DIAG_PTR_SEND_CODER_SRC,
    EN_DIAG_PTR_SCM_CODER_SRC,
    EN_DIAG_PTR_SCM_CODER_DST_CB,
    EN_DIAG_PTR_SCM_SENDTOUDI,
    EN_DIAG_PTR_CPM_COMSEND,
    EN_DIAG_PTR_PPM_PORTSEND,

    /* 失败流程的点 */
    EN_DIAG_PTR_ERR_BEGIN = 0x100,
    EN_DIAG_PTR_PPM_ERR1,
    EN_DIAG_PTR_PPM_ERR2,
    EN_DIAG_PTR_CPM_ERR1,
    EN_DIAG_PTR_CPM_ERR2,
    EN_DIAG_PTR_CPM_ERR3,
    EN_DIAG_PTR_SCM_ERR1,
    EN_DIAG_PTR_SCM_ERR2,
    EN_DIAG_PTR_SCM_ERR3,
    EN_DIAG_PTR_MSP_SERVICE_ERR1,
    EN_DIAG_PTR_MSP_SERVICE_ERR2,
    EN_DIAG_PTR_MSP_SERVICE_ERR3,
    EN_DIAG_PTR_DIAG_SERVICE_ERR1,
    EN_DIAG_PTR_DIAG_SERVICE_ERR2,
    EN_DIAG_PTR_DIAG_SERVICE_ERR3,
    EN_DIAG_PTR_DIAG_BUFFER_ERR1,
    EN_DIAG_PTR_DIAG_BUFFER_ERR2,
    EN_DIAG_PTR_MAX
} DIAG_PTR_ID_ENUM;

typedef struct
{
    DIAG_PTR_ID_ENUM    enStep;
    VOS_UINT32          ulTime;
} DIAG_PTR_ELEMENT_STRU;

typedef struct
{
    VOS_UINT32              ulCur;
    DIAG_PTR_ELEMENT_STRU   stPtr[DIAG_PTR_NUMBER];
} DIAG_PTR_INFO_STRU;

extern VOS_VOID diag_PTR(DIAG_PTR_ID_ENUM enType);

extern VOS_VOID DIAG_DebugCommon(VOS_VOID);

#endif

extern VOS_UINT32 DIAG_DebugFileHeader(void *pFile);
extern VOS_VOID DIAG_DebugFileTail(void *pFile, VOS_CHAR *FilePath);
extern VOS_VOID DIAG_DebugNoIndLog(VOS_VOID);
extern VOS_VOID diag_numberinfo(void *pFile);


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

#endif /* end of diag_Debug.h */

