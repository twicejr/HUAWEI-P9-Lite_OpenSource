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

#include <bsp_shared_ddr.h>
#include "mdrv_temp_cfg.h"
#include "bsp_memmap.h"
#include "mdrv_temp_cfg.h"
#include "bsp_nvim.h"
#include "drv_nv_id.h"
#include "drv_nv_def.h"
#include "bsp_om.h"
#include "bsp_temperature.h"

unsigned int chan_error_num[HKADC_TEMP_BUTT]= {0};

#ifdef CONFIG_TEMPERATURE_PROTECT
int phy_chan_num_get(int logic)
{
    DRV_HKADC_DATA_AREA *p_area = (DRV_HKADC_DATA_AREA *)TEMPERATURE_VIRT_ADDR;
    unsigned char *phy_tbl = p_area->phy_tbl;

    if(logic < 0 || logic >= HKADC_LOGIC_CHAN_MAX || phy_tbl[logic] == (unsigned char)-1)
    {
        return TEMPERATURE_ERROR;
    }

    return phy_tbl[logic];
}
EXPORT_SYMBOL(phy_chan_num_get);

s32 drv_hkadc_get_temp(HKADC_TEMP_PROTECT_E enMode, unsigned short* pusVolt, short* psTemp, HKADC_CONV_MODE_E ulMode)
{

    short tem    = 0;
    unsigned short volt   = 0;
    //short tem_r  = 0;
    //unsigned short volt_r = 0;
    unsigned int ret = 0;
    int phy_chan = -1;

    DRV_HKADC_DATA_AREA *p_area = (DRV_HKADC_DATA_AREA *)TEMPERATURE_VIRT_ADDR;

    if(TEMPERATURE_MAGIC_DATA != p_area->magic_start || (TEMPERATURE_MAGIC_DATA != p_area->magic_end))
    {
        tem_print_error("tem mem is writed by others.\n");
        return TEMPERATURE_ERROR;
    }

    phy_chan = phy_chan_num_get(enMode);

    if(TEMPERATURE_ERROR == phy_chan)
    {
        ++(chan_error_num[enMode]);
        if(chan_error_num[enMode] > ERROR_CHAN_MAX)
        {
            return TEMPERATURE_ERROR;
        }

        if(0 != (ret = bsp_nvm_read(NV_ID_DRV_TEMP_CHAN_MAP, (u8*)(p_area->phy_tbl), sizeof(TEMP_HKADC_PHY_LOGIC_ARRAY))))
        {
            tem_print_error("bsp_nvm_read is error, ret is 0x%x.\n" , ret);
            return TEMPERATURE_ERROR;
        }

        phy_chan = phy_chan_num_get(enMode);

        if(TEMPERATURE_ERROR == phy_chan)
        {
            return TEMPERATURE_ERROR;
        }

    }

    tem    = p_area->chan_out[phy_chan].temp_l;
    //tem_r  = p_area->chan_out[phy_chan].temp_r;

    volt   = p_area->chan_out[phy_chan].volt_l;
    //volt_r = p_area->chan_out[phy_chan].volt_r;

    /*取反校验暂时不判断*/
    if(NULL != pusVolt)
    {
        *pusVolt = volt;
    }
    if(NULL != psTemp)
    {
        *psTemp = tem;
    }

    return TEMPERATURE_OK;
}

#else

s32 drv_hkadc_get_temp(HKADC_TEMP_PROTECT_E enMode, unsigned short* pusVolt, short* psTemp, HKADC_CONV_MODE_E ulMode)
{
    if((HKADC_TEMP_PA0 == enMode || (HKADC_TEMP_PA1 == enMode)) && (NULL != psTemp))
    {
        *psTemp = 260;
        return TEMPERATURE_OK;
    }

	if(HKADC_TEMP_XO0 == enMode)
	{
		if(NULL != psTemp)
		{
			*psTemp = 300;
		}
		if(NULL != pusVolt)
		{
			*pusVolt = 796;
		}
        return TEMPERATURE_OK;
	}
	return TEMPERATURE_OK;
}

#endif

int mdrv_hkadc_get_temp (HKADC_TEMP_PROTECT_E enMode, unsigned short* pusVolt, short* psTemp, HKADC_CONV_MODE_E ulMode)
{
    return drv_hkadc_get_temp(enMode, pusVolt, psTemp,ulMode);
}
EXPORT_SYMBOL(mdrv_hkadc_get_temp);


