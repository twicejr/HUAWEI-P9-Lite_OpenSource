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

//#include <bsp_shared_ddr.h>
#include "mdrv_temp_cfg.h"
#include "bsp_memmap.h"
#include "mdrv_temp_cfg.h"
#include "bsp_nvim.h"
#include "drv_nv_id.h"
#include "drv_nv_def.h"
#include "bsp_om.h"
#include "bsp_temperature.h"

void tem_volt_get_test(void);
void tem_phy_logic(void);
void tem_battery_show(void);
void tem_config_show(void);
void tem_volt_null_test(void);
void tem_output_show(void);

void drv_hkadc_get_temp_debug(HKADC_TEMP_PROTECT_E mode);

extern unsigned int chan_error_num[HKADC_TEMP_BUTT];

void tem_volt_null_test(void)
{
    unsigned short volt = 0;
    short temp = 0;

    if(TEMPERATURE_OK != drv_hkadc_get_temp(0,NULL,&temp, HKADC_CONV_DELAY))
    {
        tem_print_error("volt null is fail.\n");
    }
    if(TEMPERATURE_OK != drv_hkadc_get_temp(0,&volt,NULL, HKADC_CONV_DELAY))
    {
        tem_print_error("tem volt null is fail.\n");
    }
}


void tem_volt_get_test(void)
{
    unsigned short volt = 0;
    short temp = 0;

    int i = 0;

    for(i = 0; i < HKADC_TEMP_BUTT; i++)
    {
        if(TEMPERATURE_OK == drv_hkadc_get_temp(i, &volt, &temp, HKADC_CONV_DELAY))
        {
            tem_print_info("volt = %d, tem = %d.\n", volt, temp);

        }

    }
}

/* 温度保护DEBUG函数 */
void tem_phy_logic(void)
{
    int i = 0;

    DRV_HKADC_DATA_AREA *p_area = (DRV_HKADC_DATA_AREA *)TEMPERATURE_VIRT_ADDR;

    tem_print_info("-------------TEMPERATURE PHYSICAL LOGFIC TABLE  ------------\n");
    for(i = 0; i < HKADC_LOGIC_CHAN_MAX; i++)
    {
        tem_print_info("logic num = %d ,phy num = %d.\n", i, p_area->phy_tbl[i]);
    }
    tem_print_info("-------------------------------------------------------------\n");

}

void tem_battery_show(void)
{
    DRV_HKADC_DATA_AREA *p_area = (DRV_HKADC_DATA_AREA *)TEMPERATURE_VIRT_ADDR;

    tem_print_info("-------------BATTERY TEMPERATURE PROTECT CONFIG------------\n");
    tem_print_info("high tem protect:        %s\n", p_area->sys_temp_cfg.enable & 0x1 ? "yes" : "no"); /* bit0：高温保护使能；bit1：低温保护使能 */
    tem_print_info("low tem protect:         %s\n", p_area->sys_temp_cfg.enable & 0x2 ? "yes" : "no");

    tem_print_info("hkadc count is:          %d\n", p_area->sys_temp_cfg.hkadc_id);          /* 高低温保护的hkadc通道ID */
    tem_print_info("high tem gate is:        %d\n", p_area->sys_temp_cfg.high_thres);        /* 高温保护的阀值 */
    tem_print_info("high gate count is:      %d\n", p_area->sys_temp_cfg.high_count);        /* 高温保护次数门限，到达该次数后系统关机 */

    tem_print_info("low tem gate is:         %d\n", p_area->sys_temp_cfg.low_thres);         /* 低温保护的阀值 */
    tem_print_info("low gate count is:       %d\n", p_area->sys_temp_cfg.low_count);         /* 低温保护次数门限，到达该次数后系统关机 */

    tem_print_info("-------------------------------------------------------------\n");

}

void tem_config_show(void)
{
    int i = 0;

    DRV_HKADC_DATA_AREA *p_area = (DRV_HKADC_DATA_AREA *)TEMPERATURE_VIRT_ADDR;

    tem_print_info("  channel \t  enable \t period \t table len\n");
    tem_print_info("  ------- \t  ------ \t ------ \t -------\n");
    for(i = 0;i < HKADC_CHAN_MAX;i++)
    {
        tem_print_info("%6d\t%6d\t       %6d\t       %6d\n", i, p_area->chan_cfg[i].outcfg.out_config, p_area->chan_cfg[i].out_peroid, p_area->chan_cfg[i].temp_data_len);
    }
    tem_print_info("  ------- \t  ------ \t ------ \t -------\n");

    tem_print_info("\n");
}

void tem_table_show(void)
{
    int i = 0;
    int j = 0;

    DRV_HKADC_DATA_AREA *p_area = (DRV_HKADC_DATA_AREA *)TEMPERATURE_VIRT_ADDR;

    for(i = 0;i < HKADC_CHAN_MAX;i++)
    {
        tem_print_info("channel number is %d\n", i);

        tem_print_info("  volt \t   tem  \n");
        tem_print_info("  ---- \t -------\n");

        for(j = 0;j < p_area->chan_cfg[i].temp_data_len;j++)
        {
            tem_print_info("%6d \t %6d\n", p_area->chan_cfg[i].temp_table[j].volt, p_area->chan_cfg[i].temp_table[j].temp);
        }

        tem_print_info("  ---- \t -------\n");

        tem_print_info("\n");
    }

}



void drv_hkadc_get_temp_debug(HKADC_TEMP_PROTECT_E mode)
{
    short psTemp = 0;
    unsigned short pusVolt = 0;

    if(TEMPERATURE_OK == drv_hkadc_get_temp(mode, &pusVolt, &psTemp, HKADC_CONV_DELAY))
    {
        tem_print_info("mode = %d volt = %d tem = %d.\n", mode, pusVolt, psTemp);
    }

}

void tem_output_show(void)
{
    int i = 0;

    DRV_HKADC_DATA_AREA *p_area = (DRV_HKADC_DATA_AREA *)TEMPERATURE_VIRT_ADDR;

    tem_print_info(" channel \t   volt  \t   tem  \n");
    tem_print_info(" ------- \t ------- \t -------\n");
    for(i = 0;i < HKADC_CHAN_MAX;i++)
    {
        tem_print_info("%6d \t %6d \t %6d\n", i, p_area->chan_out[i].volt_l,p_area->chan_out[i].temp_l);
    }
    tem_print_info(" ------- \t ------- \t -------\n");

    tem_print_info("\n");

    tem_print_info(" channel \t reverse volt \t reverse tem\n");
    tem_print_info(" ------- \t ------------ \t -----------\n");
    for(i = 0;i < HKADC_CHAN_MAX;i++)
    {
        tem_print_info("%6d \t %6d \t %6d \n", i, p_area->chan_out[i].volt_r,p_area->chan_out[i].temp_r);

    }
    tem_print_info(" ------- \t ------------ \t -----------\n");

}



