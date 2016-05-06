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


#ifndef __LUPQUEUE_H__
#define __LUPQUEUE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif


/*****************************************************************************
  2 macro
*****************************************************************************/


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
   5 STRUCT
*****************************************************************************/
typedef struct LUP_QUEUE
{
    VOS_UINT32          ulHead;
    VOS_UINT32          ulTail;
    VOS_UINT32          ulMaxNum;
    VOS_UINT32          ulResv;/*为了与64位OS兼容*/
    VOS_VOID          **pBuff;
}LUP_QUEUE_STRU;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
  说明:
  1、队列用于存放指针
  2、出于通用性考虑，以下函数内存没有互斥操作，
     如果队列用于任务间操作，则由调用者完成互斥操作
*****************************************************************************/
extern VOS_UINT32 LUP_IsQueEmpty(const LUP_QUEUE_STRU *pstQue);
extern VOS_UINT32 LUP_IsQueFull(const LUP_QUEUE_STRU *pstQue);
extern VOS_UINT32 LUP_PeekQueHead(const LUP_QUEUE_STRU *pstQue, VOS_VOID **ppNode);
extern VOS_UINT32 LUP_EnQue(LUP_QUEUE_STRU *pstQue, VOS_VOID *pNode);
extern VOS_UINT32 LUP_DeQue(LUP_QUEUE_STRU *pstQue, VOS_VOID **ppNode);
extern VOS_UINT32 LUP_BatchDeQue(LUP_QUEUE_STRU *pstQue, VOS_VOID **ppBuf,VOS_UINT32 *pulNum);

extern VOS_UINT32 LUP_CreateQue(VOS_UINT32 ulPid, LUP_QUEUE_STRU **ppQue,
                                VOS_UINT32 ulMaxNodeNum);
extern VOS_UINT32 LUP_DestroyQue(VOS_UINT32 ulPid, LUP_QUEUE_STRU **ppQue);
extern VOS_UINT32 LUP_EnQuetoHead(LUP_QUEUE_STRU *pstQue, VOS_VOID *pNode, VOS_VOID** ppTailNode);
extern VOS_UINT32 LUP_QueCnt(const LUP_QUEUE_STRU *pstQue);


/*****************************************************************************
  9 OTHERS
*****************************************************************************/




#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of LUPQueue.h */
