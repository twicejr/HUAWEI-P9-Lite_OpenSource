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


#include "bsp_cphy_tcm.h"

void om_save_cphy_tcm(char *  dst_path)
{
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
    int fd;
    int ret;
    u8 * data;
    bool flag = false;
    char  file_name[128];
    struct cdsp_dump_proc_flag *c_flag;


    data = (u8 *)ioremap_wc(DDR_CBBE_IMAGE_ADDR,DDR_CBBE_IMAGE_SIZE);

    if (NULL == data)
    {
        dump_fetal("ioremap DDR_CBBE_IMAGE_ADDR fail\n");
        return;
    }

    c_flag = (struct cdsp_dump_proc_flag *)((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_CDSP_FLAG);
    if (SAVE_CBBE_TCM_BEGIN == c_flag->cdsp_dump_flag)
    {
        dump_fetal("carry xdsp tcm to ddr not finished!\n");
        flag = true;
    }
    else if(SAVE_CBBE_TCM_END == c_flag->cdsp_dump_flag)
    {
        flag = true;
    }
    else
    {
        flag = false;
    }

    if (flag == true)
    {
        memset(file_name, 0, sizeof(file_name));
        snprintf(file_name, sizeof(file_name), "%scphy_dtcm.bin", dst_path);
        fd = bsp_open(file_name,RFILE_RDWR|RFILE_CREAT,0660);
        if (fd<0)
        {
            dump_fetal("open %s failed ,save cphy_dtcm failed!\n",file_name);
            iounmap(data);
            return;
        }
        ret = bsp_write(fd,data,CPHY_PUB_DTCM_SIZE);
        if (ret != CPHY_PUB_DTCM_SIZE)
            bsp_close(fd);
  	    dump_fetal("save %s finished!\n",file_name);
  	    bsp_close(fd);

        memset(file_name, 0, sizeof(file_name));
        snprintf(file_name, sizeof(file_name), "%scphy_itcm.bin", dst_path);
        fd = bsp_open(file_name,RFILE_RDWR|RFILE_CREAT,0660);
        if (fd<0)
        {
            dump_fetal("open %s failed ,save cphy_itcm failed!\n",file_name);
            iounmap(data);
            return;
        }
        ret = bsp_write(fd,data+CPHY_PUB_DTCM_SIZE,CPHY_PRV_ITCM_SIZE);
        if (ret != CPHY_PRV_ITCM_SIZE)
            bsp_close(fd);
        dump_fetal("save %s finished!\n",file_name);
        bsp_close(fd);
    }
    else
    {
        memset(file_name, 0, sizeof(file_name));
        snprintf(file_name, sizeof(file_name), "%scphy_ddr.bin", dst_path);

        fd = bsp_open(file_name,RFILE_RDWR|RFILE_CREAT,0660);
        if (fd<0)
        {
            dump_fetal("open %s failed ,save cphy_ddr failed!\n",file_name);
            iounmap(data);
            return;
        }
        ret = bsp_write(fd,data,DDR_CBBE_IMAGE_SIZE);
        if (ret != DDR_CBBE_IMAGE_SIZE)
            bsp_close(fd);
        dump_fetal("save %s finished!\n",file_name);
	    bsp_close(fd);
    }
    c_flag->cdsp_dump_flag = 0;

    iounmap(data);
#endif
    return;
}


