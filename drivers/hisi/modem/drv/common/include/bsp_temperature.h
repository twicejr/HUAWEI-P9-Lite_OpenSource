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

#ifndef __BSP_TEMPERATURE_H__
#define __BSP_TEMPERATURE_H__

#include <mdrv_hkadc_common.h>
#include <bsp_om.h>

#define TEMPERATURE_OK                   0
#define TEMPERATURE_ERROR                -1

/*ÎÂ¶ÈÄ§»ÃÊý*/
#define TEMPERATURE_MAGIC_DATA           0x5A5A5A5A

#define  tem_print_error(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR,  BSP_MODU_TEMPERATURE, "[tem]: <%s> <%d> "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__))
#define  tem_print_info(fmt, ...)     (bsp_trace(BSP_LOG_LEVEL_ERROR,  BSP_MODU_TEMPERATURE, "[tem]: "fmt, ##__VA_ARGS__))

/* TEMPERATURE SHARED MEM VIRT ADDR */
#define TEMPERATURE_VIRT_ADDR  ((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_TEMPERATURE)

#define ERROR_CHAN_MAX 2

typedef enum
{
    NORMAL_TEMPERATURE  = 0,
    HIGH_TEMPERATURE    = 1,
    LOW_TEMPERATURE     = 2,
    BUTT_TEMPERATURE
}TEMPERATURE_TYPE;

typedef enum
{
    TSENS_START       = 0,
    TSENS_TSENS       = TSENS_START,
    TSENS_A9          = 1,
    TSENS_DDR         = 2,
    TSENS_END         = TSENS_DDR,

    HKADC_START       = 3,
    HKADC_LCD         = HKADC_START,
    HKADC_BATTERY     = 4,
    HKADC_SIM         = 5, /*5*/
    HKADC_END         = HKADC_SIM,

    MAX_REGION
}TEMPERATURE_REGION;

struct tem_msg_stru
{
    unsigned int id;
    unsigned int region;
    unsigned int status;
};

s32 drv_hkadc_get_temp(HKADC_TEMP_PROTECT_E enMode, unsigned short* pusVolt, short* psTemp, HKADC_CONV_MODE_E ulMode);
#ifdef __FASTBOOT__
void bsp_temperature_init(void);
#endif

#ifdef __KERNEL__
typedef void (*TEM_FUNCPTR)(unsigned int device_id, unsigned int event_id);
s32 bsp_tem_protect_callback_register(TEM_FUNCPTR p);
#endif
#endif
