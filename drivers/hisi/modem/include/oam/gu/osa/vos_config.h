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
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: vos_config.h                                                    */
/*                                                                           */
/* Author: Yang Xiangqian                                                    */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2006-10                                                             */
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date:                                                                  */
/*    Author:                                                                */
/*    Modification: Create this file                                         */
/*                                                                           */
/* 2. Date: 2006-10                                                          */
/*    Author: Xu Cheng                                                       */
/*    Modification: Standardize code                                         */
/*                                                                           */
/*****************************************************************************/


#ifndef _V_CONFIG_H
#define _V_CONFIG_H

#include "dopra_def.h"
#include "PsLogdef.h"
#include "product_config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define VOS_PID_TIMER                   1

#define MILLISECONDS_PER_TICK           10 /* 宏值不能为0，否则函数VOS_TmTickToMillSec会出异常 */

#ifndef VOS_OS_VER
#define VOS_OS_VER                      VOS_VXWORKS
#endif

#ifndef VOS_HARDWARE_PLATFORM
#define VOS_HARDWARE_PLATFORM           VOS_ARM
#endif

#ifndef VOS_CPU_TYPE
#define VOS_CPU_TYPE                    VOS_ARM
#endif

#ifndef VOS_MEMORY_CHECK
#define VOS_MEMORY_CHECK                VOS_YES
#endif

#ifndef VOS_MEMORY_COUNT
#define VOS_MEMORY_COUNT                VOS_YES
#endif

#ifndef VOS_TIMER_CHECK
#define VOS_TIMER_CHECK                 VOS_YES
#endif

#ifndef VOS_CHECK_PARA
#define VOS_CHECK_PARA                  VOS_YES
#endif

/*
define the byte order according to the VOS_HARDWARE_PLATFORM
*/
#define VOS_BYTE_ORDER                  VOS_LITTLE_ENDIAN

#ifndef VOS_DOPRA_VER
#define VOS_DOPRA_VER                   VOS_DEBUG
#endif

#define VOS_WATCHDOG_VERSION            VOS_RELEASE

#define HARD_DOG_ENABLE                 VOS_RELEASE

#define VOS_ANALYZE_PID_MEM             VOS_NO

#define VOS_FILE_ID                     THIS_FILE_ID

#define VOS_CHECK_INTLOCK               VOS_RELEASE

#define VOS_CHECK_TASKLOCK              VOS_RELEASE

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _V_CONFIG_H */
