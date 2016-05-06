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

#include <bsp_icc.h>

extern unsigned int led_debug_level;    /* just for debug */

/* led ccore and acore icc channel */
#define LED_ICC_CHN_ID                          ((ICC_CHN_IFC << 16) | IFC_RECV_FUNC_LED)
#define LED_TIME_BASE_UNIT                      (100)         /* 三色灯工作的基本时间单位 ms */

/* some value */
#define LED_OK      0
#define LED_ERROR   -1
#define LED_VALUE_INVALID   DR_VALUE_INVALIED

/* for debug */
#define LED_DEBUG_INFO      0x00000001
#define LED_DEBUG_WARNING   0x00000002
#define LED_DEBUG_ERROR     0x00000004
#define LED_DEBUG_ALWAYS    0xFFFFFFF0
#define LED_DEBUG_ALL       0xFFFFFFFF

#define LED_DEBUG_LVL            (LED_DEBUG_ALWAYS | LED_DEBUG_ERROR)
#define LED_DEBUG_LEVEL(LEVEL)   (LED_DEBUG_##LEVEL)

/* trace */
#define LED_TRACE(loglevel, msg, ...)    \
{                                   \
    /*lint -save -e506 -e413 -e774 -e778 -e831 -e944*/                                            \
    if((loglevel & LED_DEBUG_LVL) || (loglevel & led_debug_level))    \
    {                                        \
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_LED, msg, ##__VA_ARGS__);                    \
    }                                       \
    /*lint -restore */                                                  \
}

int bsp_led_init(void);

