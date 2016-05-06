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



#ifndef __CPM_H__
#define __CPM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "omnvinterface.h"
#include "msp_debug.h"


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define CPM_LOGIC_PHY_PORT(enLogicPort)     (g_astCPMLogicPortCfg[enLogicPort].enPhyPort)
#define CPM_LOGIC_SEND_FUNC(enLogicPort)    (g_astCPMLogicPortCfg[enLogicPort].pSendFunc)
#define CPM_LOGIC_RCV_FUNC(enLogicPort)     (g_astCPMLogicPortCfg[enLogicPort].pRcvFunc)

#define CPM_PHY_SEND_FUNC(enPhyPort)        (g_astCPMPhyPortCfg[enPhyPort].pSendFunc)
#define CPM_PHY_RCV_FUNC(enPhyPort)         (g_astCPMPhyPortCfg[enPhyPort].pRcvFunc)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum
{
    CPM_AT_COMM,
    CPM_OM_IND_COMM,        /* OM可维可测端口 */
    CPM_OM_CFG_COMM,        /* OM配置端口 */
    CPM_DIAG_COMM,
    CPM_PCVOICE_COMM,
    CPM_COMM_BUTT
};
typedef VOS_UINT32  CPM_LOGIC_PORT_ENUM_UINT32;

enum
{
    CPM_SEND_OK,
    CPM_SEND_FUNC_NULL,
    CPM_SEND_PARA_ERR,
    CPM_SEND_ERR,
    CPM_SEND_AYNC,
    CPM_SEND_BUTT
};
typedef VOS_UINT32 CPM_SEND_RESULT_ENUM_UINT32;

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
typedef VOS_UINT32 (*CPM_RCV_FUNC)(VOS_UINT8 *pucData, VOS_UINT32 ulLen);

typedef VOS_UINT32 (*CPM_SEND_FUNC)(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulLen);

/* 保存物理通道的属性 */
typedef struct
{
    CPM_SEND_FUNC               pSendFunc;
    CPM_RCV_FUNC                pRcvFunc;
}CPM_PHY_PORT_CFG_STRU;

/* 保存逻辑通道的属性 */
typedef struct
{
    CPM_PHY_PORT_ENUM_UINT32    enPhyPort;
    CPM_SEND_FUNC               pSendFunc;
    CPM_RCV_FUNC                pRcvFunc;
}CPM_LOGIC_PORT_CFG_STRU;


typedef struct
{
    VOS_UINT32                  ulParaErr;
    VOS_UINT32                  ulNullPtr;
}CPM_COM_PORT_ERR_INFO_STRU;

/* 物理端口接收错误统计 */
typedef struct
{
    VOS_UINT32                          ulPortErr;
    CPM_COM_PORT_ERR_INFO_STRU          astCPMRcvErrInfo[CPM_PORT_BUTT - CPM_IND_PORT];
}CPM_COM_PORT_RCV_ERR_INFO_STRU;


/* 逻辑端口发送错误统计 */
typedef struct
{
    VOS_UINT32                          ulPortErr;
    CPM_COM_PORT_ERR_INFO_STRU          astCPMSndErrInfo[CPM_COMM_BUTT];
}CPM_COM_PORT_SND_ERR_INFO_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID   CPM_PhySendReg(CPM_PHY_PORT_ENUM_UINT32 enPhyPort, CPM_SEND_FUNC pSendFunc);
VOS_VOID   CPM_LogicRcvReg(CPM_LOGIC_PORT_ENUM_UINT32 enLogicPort, CPM_RCV_FUNC pRcvFunc);
CPM_PHY_PORT_ENUM_UINT32 CPM_QueryPhyPort(CPM_LOGIC_PORT_ENUM_UINT32 enLogicPort);
VOS_VOID   CPM_ConnectPorts(CPM_PHY_PORT_ENUM_UINT32 enPhyPort, CPM_LOGIC_PORT_ENUM_UINT32 enLogicPort);
VOS_VOID   CPM_DisconnectPorts(CPM_PHY_PORT_ENUM_UINT32 enPhyPort, CPM_LOGIC_PORT_ENUM_UINT32 enLogicPort);
VOS_UINT32 CBTCPM_NotifyChangePort(AT_PHY_PORT_ENUM_UINT32 enPhyPort);
VOS_VOID CPM_PnpAppPortCB(CPM_PHY_PORT_ENUM_UINT32 enPhyPort, VOS_BOOL bPortState);
VOS_UINT32 CPM_PortAssociateInit(VOS_VOID);
VOS_UINT32 CPM_ComSend(CPM_LOGIC_PORT_ENUM_UINT32 enLogicPort, VOS_UINT8 *pucVirData, VOS_UINT8 *pucPHYData, VOS_UINT32 ulLen);
VOS_UINT32 CPM_ComRcv(CPM_PHY_PORT_ENUM_UINT32 enPhyPort, VOS_UINT8 *pucData, VOS_UINT32 ulLen);

/*AT提供给OM注册端口接收函数的接口*/
extern VOS_VOID AT_RcvFuncReg(AT_PHY_PORT_ENUM_UINT32 ulPhyPort, CPM_RCV_FUNC pRcvFunc);

/*AT提供给OM查询发送数据的函数接口*/
extern CPM_SEND_FUNC AT_QuerySndFunc(AT_PHY_PORT_ENUM_UINT32 ulPhyPort);

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

#endif /* end of cpm.h */
