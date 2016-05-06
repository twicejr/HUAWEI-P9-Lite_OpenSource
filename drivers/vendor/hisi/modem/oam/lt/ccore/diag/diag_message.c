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


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include "diag_common.h"
#include "SCMProc.h"
#include "diag_api.h"
#include "diag_cfg.h"

#define    THIS_FILE_ID        MSP_FILE_ID_DIAG_MESSAGE_C

#if (VOS_OS_VER == VOS_LINUX)

struct DIAG_MESSAGE_PROC_STRU
{
    DIAG_MESSAGE_TYPE_U32   ulMsgType;
    DIAG_MESSAGE_FUNC       fnMsgProc;
};


/******************************************************************************
MSP----connect/disconnect
      |
      |-C_reset/get timestamp
      |
      |-LAYER/MSG/PRINT/AIR/USERPLANE/EVENT/Trans/L1 cfg

PS-----trans
      |
      |-PS_REPLAY
      |
      |-MMA鉴权
      |
      |-RTT GTR

PHY----TL trans
      |
      |-W trans
      |
      |-G trans

LBBP---GEN_REQ/ADDR_REQ/CHNSIZE_REQ/GET_VERSION_REQ/ABLE_CHN_REQ

BSP----Read NV/Write NV/NV_IMPORT/NV_EXPORT/GetNvIdList/BackupNv/NVID filterlist
      |
      |-FS_QUERY_DIR/FS_SCAN_DIR/FS_MAKE_DIR/FS_OPEN/FS_IMPORTFS_EXPORT/FS_DELETE/FS_SPACE
      |
      |-SYSVIEW_SWT/SYSVIEW_IND/AXI_DATA_CFG/AXI_REG_CFG/AXI_DATA_CTRL/AXI_MON_CFG/AXI_MON_START/AXI_MON_TERMINATE/UTRACE_START/UTRACE_TERMINATE/CPU_SWT

GUBBP---BBP dump/配置BBP数采/停止BBP数采/配置BBP上报/配置BBP收到EDMA错误消息后通知PC
******************************************************************************/

struct DIAG_MESSAGE_PROC_STRU g_aFnMsgTbl[DIAG_MSG_TYPE_BUTT] =
{
    {DIAG_MSG_TYPE_RSV,     VOS_NULL},
    {DIAG_MSG_TYPE_MSP,     VOS_NULL},
    {DIAG_MSG_TYPE_PS,      VOS_NULL},
    {DIAG_MSG_TYPE_PHY,     VOS_NULL},
    {DIAG_MSG_TYPE_BBP,     VOS_NULL},
    {DIAG_MSG_TYPE_HSO,     VOS_NULL},
    {DIAG_MSG_TYPE_RSV,     VOS_NULL},  /* reserve */
    {DIAG_MSG_TYPE_RSV,     VOS_NULL},  /* reserve */
    {DIAG_MSG_TYPE_RSV,     VOS_NULL},  /* reserve */
    {DIAG_MSG_TYPE_BSP,     VOS_NULL},
    {DIAG_MSG_TYPE_ISP,     VOS_NULL}
};

VOS_UINT32 diag_MessageProc(DIAG_FRAME_INFO_STRU *pData);


/*****************************************************************************
 Function Name   : diag_MessageInit
 Description     : DIAG message层初始化接口

 History         :
    1.c64416         2014-11-18  Draft Enact

*****************************************************************************/
VOS_VOID diag_MessageInit(VOS_VOID)
{
    diag_ServiceProcReg(diag_MessageProc);
}


/*****************************************************************************
 Function Name   : diag_MessageProc
 Description     : DIAG message层处理接口

 History         :
    1.c64416         2014-11-18  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_MessageProc(DIAG_FRAME_INFO_STRU *pData)
{
    VOS_UINT32 ulRet = VOS_ERR;
    DIAG_MESSAGE_TYPE_U32 ulMsgType;

    diag_PTR(EN_DIAG_PTR_MESSAGE_IN);

    if(VOS_NULL_PTR == pData)
    {
        return VOS_ERR;
    }

    ulMsgType = pData->stID.pri4b;

    if((ulMsgType < DIAG_MSG_TYPE_BUTT) && (g_aFnMsgTbl[ulMsgType].fnMsgProc))
    {
        diag_PTR(EN_DIAG_PTR_MESSAGE_PROC);
        ulRet = g_aFnMsgTbl[ulMsgType].fnMsgProc(pData);
    }

    return ulRet;
}


/*****************************************************************************
 Function Name   : DIAG_MsgProcReg
 Description     : 诊断命令解包回调注册接口

 History         :
    1.c64416         2014-11-18  Draft Enact

*****************************************************************************/
VOS_UINT32 DIAG_MsgProcReg (DIAG_MESSAGE_TYPE_U32 ulMsgType, DIAG_MESSAGE_FUNC pMsgfn)
{
    if((ulMsgType >= DIAG_MSG_TYPE_BUTT) || (VOS_NULL_PTR == pMsgfn))
    {
        return VOS_ERR;
    }

    g_aFnMsgTbl[ulMsgType].fnMsgProc = pMsgfn;

    return VOS_OK;
}
#endif

/*****************************************************************************
 Function Name   : DIAG_MsgReport
 Description     : DIAG message 层上报接口

 History         :
    1.c64416         2014-11-18  Draft Enact

*****************************************************************************/
VOS_UINT32 DIAG_MsgReport (MSP_DIAG_CNF_INFO_STRU *pstDiagInfo, VOS_VOID *pstData, VOS_UINT32 ulLen)
{
    DIAG_MSG_REPORT_HEAD_STRU stDiagHead;

#if(VOS_OS_VER == VOS_LINUX)
    diag_PTR(EN_DIAG_PTR_MESSAGE_REPORT);
#endif

    /*检查DIAG是否初始化且HSO是否连接上*/
    if(!DIAG_IS_CONN_ON)
    {
        return ERR_MSP_NO_INITILIZATION;
    }

    if((VOS_NULL_PTR == pstDiagInfo) || (VOS_NULL_PTR == pstData) || (0 == ulLen))
    {
        diag_printf("%s,%d.\n",__FUNCTION__,__LINE__);
        return VOS_ERR;
    }

    (VOS_VOID)VOS_MemSet(&stDiagHead, 0, sizeof(DIAG_MSG_REPORT_HEAD_STRU));

    stDiagHead.u.stID.pri4b     = (pstDiagInfo->ulMsgType & 0xf);
    stDiagHead.u.stID.mode4b    = (pstDiagInfo->ulMode & 0xf);
    stDiagHead.u.stID.sec5b     = (pstDiagInfo->ulSubType & 0x1f);
    stDiagHead.u.stID.cmdid19b  = (pstDiagInfo->ulMsgId & 0x7ffff);
    stDiagHead.ulSsid           = pstDiagInfo->ulSSId;
    stDiagHead.ulModemId        = pstDiagInfo->ulModemid;
    stDiagHead.ulDirection      = pstDiagInfo->ulDirection;
    stDiagHead.ulMsgTransId     = pstDiagInfo->ulTransId;
    stDiagHead.ulChanId         = SCM_CODER_SRC_LOM_CNF;
    stDiagHead.ulDataSize       = ulLen;
    stDiagHead.pData            = pstData;

    diag_LNR(EN_DIAG_LNR_CCORE_MSG, stDiagHead.u.ulID, VOS_GetSlice());

    (VOS_VOID)diag_ServicePackData(&stDiagHead);

    return VOS_OK;
}



#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


