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

#ifndef __TAF_APP_PPPOE_H__
#define __TAF_APP_PPPOE_H__


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "TafTypeDef.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/******************APP-API所需数据类型定义开始****************/
#ifndef __VOS_CHANGE_TO_TAF__
#define __VOS_CHANGE_TO_TAF__
#if 0
typedef signed   char       TAF_INT8;
typedef unsigned char       TAF_UINT8;

typedef signed   short      TAF_INT16;
typedef unsigned short      TAF_UINT16;

typedef signed   long       TAF_INT32;
typedef unsigned long       TAF_UINT32;

typedef char                TAF_CHAR;
typedef unsigned char       TAF_UCHAR;

typedef void                TAF_VOID;
#endif
#endif

/******************APP-API所需数据类型定义结束****************/


/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*******************************************************************************
  3 枚举定义
*******************************************************************************/
typedef enum
{
    TAF_PPPOE_CID_DEFAULT,                             /*使用默认CID*/
    TAF_PPPOE_CID_MANUAL_SELECT,                       /*用户自行选择CID*/

    TAF_PPPOE_CID_BUTT
}TAF_PPPOE_CID_SELECT_MODE_ENUM;          /*选择CID的方式*/

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
  9 函数接口定义
*****************************************************************************/
/*****************************************************************************
 Prototype      : Taf_PPPoESetCid
 Description    : 提供给用户的接口，用于设置PPPoE所使用的CID
 Input          : CidSelectMode      选择CID的方式，TAF_PPPOE_CID_DEFAULT方式下，第二个参数ucCid可填任意值。
                  ucCid              用户所指定的CID，取值[0,11],只对TAF_PPPOE_CID_MANUAL_SELECT方式有效
 Output         :
 Return Value   : TAF_SUCCESS        CID设置成功
                  TAF_FAILURE        CID设置失败
 Calls          :
 Called By      : APP

 History        :
  1.Date        : 2006-05-16
    Author      : L47619
    Modification: Created function
*****************************************************************************/
extern TAF_UINT32 Taf_PPPoESetCid(TAF_PPPOE_CID_SELECT_MODE_ENUM CidSelectMode, TAF_UINT8 ucCid);





#if ((TAF_OS_VER == TAF_WIN32) || (TAF_OS_VER == TAF_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of TafAppPPPoE.h*/
