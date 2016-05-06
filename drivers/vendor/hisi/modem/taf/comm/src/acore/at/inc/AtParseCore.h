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

#ifndef __ATPARSECORE_H__
#define __ATPARSECORE_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "hi_list.h"

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


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern VOS_UINT8 AT_BlockCmdCheck(VOS_VOID);
extern VOS_VOID AT_PendClientProc(VOS_UINT8 ucIndex, VOS_UINT8 *pData, VOS_UINT16 usLen);
extern VOS_VOID AT_HoldBlockCmd(VOS_UINT8 ucIndex, VOS_UINT8 *pData, VOS_UINT16 usLen);
extern VOS_UINT32 AT_ParseCmdIsComb(VOS_UINT8 ucIndex, VOS_UINT8 *pData, VOS_UINT16 usLen);
extern VOS_UINT32 AT_ParseCmdIsPend(VOS_UINT8 ucIndex, VOS_UINT8 *pData, VOS_UINT16 usLen);
extern VOS_VOID AT_ResetParseVariable(VOS_VOID);
extern VOS_UINT32 At_MatchSmsCmdName(VOS_UINT8 ucIndex, VOS_CHAR *pszCmdName);
extern VOS_UINT32 ParseParam(AT_PAR_CMD_ELEMENT_STRU* pstCmdElement);
extern AT_RRETURN_CODE_ENUM_UINT32 fwCmdTestProc(VOS_UINT8 ucIndex, AT_PAR_CMD_ELEMENT_STRU* pstCmdElement);
extern VOS_UINT32 LimitedCmdProc(VOS_UINT8 ucClientId, VOS_UINT8 *pData, VOS_UINT16 usLen, AT_PAR_CMD_ELEMENT_STRU* pstCmdElement);
extern VOS_VOID RepeatCmdProc(AT_PARSE_CONTEXT_STRU* pstClientContext);
extern VOS_VOID SaveRepeatCmd(AT_PARSE_CONTEXT_STRU* pstClientContext, VOS_UINT8 *pData, VOS_UINT16 usLen);
extern VOS_UINT32 ScanDelChar( VOS_UINT8 *pData, VOS_UINT16 *pLen, VOS_UINT8 AtS5);
extern VOS_UINT32 ScanCtlChar( VOS_UINT8 *pData, VOS_UINT16 *pLen);
extern VOS_UINT32 ScanBlankChar( VOS_UINT8 *pData, VOS_UINT16 *pLen);
extern VOS_UINT32 FormatCmdStr (VOS_UINT8 *pData, VOS_UINT16 *pLen, VOS_UINT8 AtS3);
extern VOS_UINT32 CmdStringFormat(VOS_UINT8 ucClientId, VOS_UINT8 *pData,VOS_UINT16* pusLen);
extern VOS_VOID atCmdMsgProc(VOS_UINT8 ucIndex, VOS_UINT8 *pData, VOS_UINT16 usLen);

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

#endif /* end of AtParseCore.h */
