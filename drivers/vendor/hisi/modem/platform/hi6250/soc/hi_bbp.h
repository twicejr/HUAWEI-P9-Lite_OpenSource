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

#ifndef __HI_BBP_H__
#define __HI_BBP_H__

#include "mdrv_public.h"


#ifdef __cplusplus
extern "C" {
#endif

/*各芯片平台都需要提供*/
#define BBP_CLK_MIN 0/*所有时钟阈的id*/
#define BBP_CLK_MAX 40/*所有时钟阈的id*/
#define BBP_PWR_MIN 0/*所有电源阈的id*/
#define BBP_PWR_MAX 7/*所有电源阈的id*/

#define BBP_VOTE_CLK_MIN 0   /*参与低功耗上下电的clk id*/
#define BBP_VOTE_CLK_MAX 40/*参与低功耗上下电的clk id*/
#define BBP_VOTE_PWR_MIN 0/*参与低功耗上下电的pwr id*/
#define BBP_VOTE_PWR_MAX 3/*参与低功耗上下电的pwr id*/

#define BBP_PWC_MODULE_MIN   PWC_COMM_MODULE_BBP_DRX
#define BBP_PWC_MODULE_MAX   PWC_COMM_MODULE_BBP_DBG
#define BBP_PWC_MODEM_MIN    PWC_COMM_MODEM_0
#define BBP_PWC_MODEM_MAX    PWC_COMM_MODEM_1
#define BBP_PWC_MODE_MIN     PWC_COMM_MODE_GSM
#define BBP_PWC_MODE_MAX     PWC_COMM_MODE_CDMA_HRPD

#define BBP_PWR_NUM      (BBP_PWR_MAX-BBP_PWR_MIN+1)
#define BBP_CLK_NUM      (BBP_CLK_MAX-BBP_CLK_MIN+1)
#define BBP_VOTE_PWR_NUM (BBP_VOTE_PWR_MAX-BBP_VOTE_PWR_MIN+1)
#define BBP_VOTE_CLK_NUM (BBP_VOTE_CLK_MAX-BBP_VOTE_CLK_MIN+1)
#define BBP_MODULE_NUM   (BBP_PWC_MODULE_MAX-BBP_PWC_MODULE_MIN+1)
#define BBP_MODEM_NUM    (BBP_PWC_MODEM_MAX-BBP_PWC_MODEM_MIN+1)
#define BBP_MODE_NUM     (BBP_PWC_MODE_MAX-BBP_PWC_MODE_MIN+1)

#ifdef __cplusplus
}
#endif

#endif

