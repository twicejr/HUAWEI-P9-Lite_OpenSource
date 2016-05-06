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

/******************************************************************************

              Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File name   : SiTypeDef.h
  Version     : V200R001
  Author      : H59254
  Date        : 2008-10-10
  Description : This file contains general types and macros that are of use
                to all modules.
  History     :
  1.Date         : 2008-10-10
    Author       : H59254
    Modification : Create
******************************************************************************/
#ifndef  SI_TYPE_DEF_H
#define  SI_TYPE_DEF_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/**/
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#pragma pack(4)
#include "v_msg.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*SI API数据类型*/
typedef int                 SI_INT;
typedef signed   char       SI_INT8;
typedef unsigned char       SI_UINT8;

typedef signed   short      SI_INT16;
typedef unsigned short      SI_UINT16;

typedef signed   int        SI_INT32;
typedef unsigned int        SI_UINT32;

typedef char                SI_CHAR;
typedef unsigned char       SI_UCHAR;

typedef void                SI_VOID;

typedef unsigned int        SI_BOOL;

#define  SI_NULL_PTR                   0L                    /* null pointer */

typedef SI_UINT16 SI_CLIENT_ID_T ;


/*******************************************************************************
  3 枚举定义
*******************************************************************************/
enum
{
    SI_FALSE = 0,
    SI_TRUE  = 1
};

enum SI_CLIENT_TYPE_ENUM
{
    SI_APP_CLIENT,
    SI_AT_CLIENT,
    SI_CLIENT_TYPE_BUTT
};
typedef SI_UINT8 SI_CLIENT_TYPE;


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 STRUCT定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32      ulMsgName;
}PS_SI_MSG_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32      ulMsgName;
    VOS_UINT8       aucData[4];
}SI_HOOKMSG_STRU;

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* TAF_TYPE_DEF_H */

