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

/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2015, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: v_private.c                                                     */
/*                                                                           */
/* Author: dongtinghuan                                                      */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2014-11                                                             */
/*                                                                           */
/* Description: 对底软接口的私有封装                                         */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date:                                                                  */
/*    Author:                                                                */
/*    Modification: Create this file                                         */
/*                                                                           */
/*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include "v_typdef.h"
#include "v_IO.h"
#include "v_int.h"
#include "vos_Id.h"
#include "v_sem.h"
#include "v_private.h"
#include "mdrv.h"

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_V_PRIVATE_C

/*****************************************************************************
 Function   : VOS_GetDrvVerInfo
 Description: 获取单板版本信息
 Input      : enVerInfo -- 获取类型
 Return     : VOS_INT   -- 获取类型值
 Other      :
 *****************************************************************************/
VOS_INT VOS_GetDrvVerInfo(VOS_GET_DRV_VER_INFO_ENUM_UINT32 enVerInfo)
{
    const MODEM_VER_INFO_S             *pstModemVerInfo;

    pstModemVerInfo = mdrv_ver_get_info();

    if ((VOS_NULL_PTR == pstModemVerInfo)||(VOS_GET_DRV_VER_INFO_BUTT <= enVerInfo))
    {
        VOS_ProtectionReboot(VOS_GET_DRV_VER_INFO_ERROR, (VOS_INT)PS_FILE_ID_V_PRIVATE_C,
                             (VOS_INT)enVerInfo,(VOS_CHAR *)VOS_NULL_PTR, 0);
        return VOS_ERROR;
    }

    if (VOS_GET_DRV_BOARD_PRODUCT_ID == enVerInfo)
    {
        return pstModemVerInfo->sthwverinfo.hwindex;
    }
    else
    {
    }

    return pstModemVerInfo->stproductinfo.eboardatype;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

