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

#ifndef __TTFDRVINTERFACE_H__
#define __TTFDRVINTERFACE_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "TtfLinkInterface.h"

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
enum TTF_BLK_MEM_STATE_ENUM
{
    TTF_BLK_MEM_STATE_FREE,       /*该内存未申请过或已释放*/
    TTF_BLK_MEM_STATE_ALLOC,      /*该内存已申请*/

    TTF_BLK_MEM_STATE_BUTT
};
typedef unsigned int TTF_BLK_MEM_STATE_ENUM_UINT32;

enum TTF_PS_DATA_PRIORITY_ENUM
{
    TTF_PS_DATA_PRIORITY_NORMAL = 0,
    TTF_PS_DATA_PRIORITY_MIDDLE,
    TTF_PS_DATA_PRIORITY_HIGH,
    TTF_PS_DATA_PRIORITY_BUTT,
};
typedef unsigned char TTF_PS_DATA_PRIORITY_ENUM_UINT8;

typedef struct
{
    TTF_BLK_MEM_STATE_ENUM_UINT32   enMemStateFlag;
    unsigned int                    ulAllocTick;        /* CPU tick when alloc or free */
    unsigned short                  usAllocFileId;      /* File ID when alloc or free */
    unsigned short                  usAllocLineNum;     /* File Line when alloc or free */
    unsigned short                  usTraceFileId;      /* File ID when traced */
    unsigned short                  usTraceLineNum;     /* File Line when traced */
    unsigned int                    ulTraceTick;        /* CPU tick when traced */
} TTF_BLK_MEM_DEBUG_ST;

typedef struct
{
    unsigned int    aulGroupCnt[4];    /* 将 TTF_BLK_MEM_CNT 片 TTF_MEM 内存均分为 4 份,
                                        分别记录当前块数落在 [0, TTF_BLK_MEM_CNT/4-1],
                                        [TTF_BLK_MEM_CNT/4, TTF_BLK_MEM_CNT/2-1],
                                        [TTF_BLK_MEM_CNT/2, 3*TTF_BLK_MEM_CNT/4-1],
                                        [3*TTF_BLK_MEM_CNT/4, TTF_BLK_MEM_CNT] 范围的次数 */
    unsigned int    ulMaxCnt;    /* 记录使用的 TTF_MEM 峰值 */
} TTF_BLK_MEM_CNT_ST;

typedef struct _TTF_MEM_ST
{
    TTF_NODE_ST                     stNode;
    unsigned char                   ucPoolId;       /*本内存属于哪一个内存池 */
    unsigned char                   ucClusterId;    /*本内存是属于哪一个级别*/
    TTF_PS_DATA_PRIORITY_ENUM_UINT8 ucDataPriority;
    unsigned char                   ucReserve;
    struct _TTF_MEM_ST             *pNext;          /* 该数据的下一段 */
    unsigned short                  usType;         /* 内存类型，DYN、BLK、EXT类型 */
    unsigned short                  usLen;          /* 申请数据的总长度，但不一定全部被使用 */
    unsigned short                  usUsed;         /* 已经使用的数据长度   */
    unsigned short                  usApp;          /* 使用者可以使用的区域 */

    TTF_BLK_MEM_DEBUG_ST           *pstDbgInfo;

    unsigned char                  *pOrigData;      /* 记录数据的原始指针 */
    unsigned char                  *pData;          /* 存放数据的指针，物理上指向结构体的连续内存 */
    void                           *pExtBuffAddr;   /* 保存extern类型的内存地址用于释放 */
    unsigned int                    ulForCds[1];    /*预留给CDS使用，GU模不用初始化*/

#if( FEATURE_LTE == FEATURE_ON )
    unsigned int                    ulForLte[6];    /*预留给LTE使用，GU模不用初始化*/
#endif
} TTF_MEM_ST;


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

#endif /* end of TtfDrvInterface.h */

