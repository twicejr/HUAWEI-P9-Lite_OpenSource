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

#ifndef __AT_CSIMAGENT_H__
#define __AT_CSIMAGENT_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*******************************************************************************
  3 枚举定义
*******************************************************************************/
/*****************************************************************************
 枚举名    :AT_CSIMA_MSGID_ENUM
 结构说明  :AT和CSIMA内部消息ID枚举
*****************************************************************************/
enum AT_CSIMA_MSGID_ENUM
{
    AT_CSIMA_RESET_IND_MSG              = 0,    /* AT通知CSIMA复位状态 */

    AT_CSIMA_MSGID_BUTT
};
typedef VOS_UINT16     AT_CSIMA_MSGID_ENUM_UINT32;

/*****************************************************************************
 枚举名    : CBP_MODEM_RESET_STATUS_ENUM
 结构说明  : CBP Modem 复位状态枚举
*****************************************************************************/
enum CBP_MODEM_RESET_STATUS_ENUM
{
    CBP_MODEM_RESET_BEGIN            = 0x00,    /* CBP Modem开始复位 */
    CBP_MODEM_RESET_SUCC             = 0x01,    /* CBP Modem复位成功结束 */
    CBP_MODEM_RESET_FAIL             = 0x02,    /* CBP Modem复位失败 */
    CBP_MODEM_RESET_BUTT
};
typedef VOS_UINT32     CBP_MODEM_RESET_STATUS_ENUM_UINT32;

/*****************************************************************************
 结构名    :AT_CSIMA_RESET_STATUS_IND_MSG_STRU
 结构说明  :AT通知CSIMA VIA Modem复位状态消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                               ulMsgId;                     /* 消息ID */
    CBP_MODEM_RESET_STATUS_ENUM_UINT32       enVIAModemStatus;            /* 当前复位Modem状态: 0：开始复位 1：复位成功结束2：复位失败 */

}AT_CSIMA_RESET_STATUS_IND_MSG_STRU;



/*****************************************************************************
  4 函数声明
*****************************************************************************/




/*****************************************************************************
  5 全局变量声明
*****************************************************************************/


/*****************************************************************************
  6 OTHERS定义
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

#endif /* end of AtCsimagent.h*/

