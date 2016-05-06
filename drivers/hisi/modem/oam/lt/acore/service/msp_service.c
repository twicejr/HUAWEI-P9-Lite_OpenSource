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

#include "msp_errno.h"
#include "SCMProc.h"
#include "diag_common.h"
#include "msp_service.h"

#define    THIS_FILE_ID        MSP_FILE_ID_MSP_SERVICE_C


struct MSP_SERVICE_TABLE
{
    VOS_UINT32          ulSidType;
    MSP_SERVICE_FUNC    fnService;
};

struct MSP_SERVICE_TABLE g_astMspService[MSP_SID_BUTT] = {
    {MSP_SID_DEFAULT,           VOS_NULL},
    {MSP_SID_AT_SERVICE,        VOS_NULL},
    {MSP_SID_DIAG_SERVICE,      VOS_NULL},
    {MSP_SID_DATA_SERVICE,      VOS_NULL},
    {MSP_SID_NV_SERVICE,        VOS_NULL},
    {MSP_SID_USIM_SERVICE,      VOS_NULL},
    {MSP_SID_DM_SERVICE,        VOS_NULL},
    {MSP_SID_CBT_SERVICE,       VOS_NULL}
};


VOS_UINT32 msp_ServiceProc(SOCP_DECODER_DST_ENUM_U32 enChanID,VOS_UINT8 *pucData, VOS_UINT32 ulSize,VOS_UINT8 *pucRBData, VOS_UINT32 ulRBSize)
{
    VOS_UINT32 ulRet = ERR_MSP_INVALID_PARAMETER;
    VOS_UINT32 ulTotalLen = 0;
    VOS_UINT8* pData;
    MSP_SERVICE_HEAD_STRU *pHeader;

    diag_PTR(EN_DIAG_PTR_MSP_SERVICE_1);

    /*入参检查*/
    if(pucData == VOS_NULL)
    {
        diag_PTR(EN_DIAG_PTR_MSP_SERVICE_ERR1);
        return ERR_MSP_INVALID_PARAMETER;
    }

    ulTotalLen = ulSize + ulRBSize;
    if(!ulTotalLen)
    {
        diag_PTR(EN_DIAG_PTR_MSP_SERVICE_ERR2);
        return ERR_MSP_INVALID_PARAMETER;
    }

    pData = VOS_MemAlloc(MSP_PID_DIAG_APP_AGENT, DYNAMIC_MEM_PT, ulTotalLen);
    if(pData == VOS_NULL)
    {
        diag_PTR(EN_DIAG_PTR_MSP_SERVICE_ERR3);
        return ERR_MSP_MALLOC_FAILUE;
    }

    VOS_MemCpy(pData,pucData,ulSize);

    /*回卷指针可能为空*/
    if((VOS_NULL != pucRBData)&&(0 != ulRBSize))
    {
        VOS_MemCpy(pData+ulSize,pucRBData,ulRBSize);
    }

    diag_PTR(EN_DIAG_PTR_MSP_SERVICE_2);

    pHeader = (MSP_SERVICE_HEAD_STRU *)pData;

    if(pHeader->sid8b < MSP_SID_BUTT)
    {
        if(g_astMspService[pHeader->sid8b].fnService)
        {
            ulRet = g_astMspService[pHeader->sid8b].fnService(pHeader);
        }
    }

    VOS_MemFree(MSP_PID_DIAG_APP_AGENT,pData);

    return ulRet;
}


VOS_VOID msp_ServiceInit(VOS_VOID)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    /* register to SCM */
    ret = SCM_RegDecoderDestProc(SOCP_DECODER_DST_LOM,(SCM_DECODERDESTFUCN)msp_ServiceProc);
    if(ret != ERR_MSP_SUCCESS)
    {
    }
    return ;
}


VOS_VOID msp_ServiceProcReg(MSP_SID_TYPE_U32 ulType, MSP_SERVICE_FUNC pServiceFn)
{
    /* coverity[cond_at_most] */
    if(ulType > MSP_SID_BUTT)
    {
        return;
    }

    g_astMspService[ulType].fnService = pServiceFn;
}



#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


