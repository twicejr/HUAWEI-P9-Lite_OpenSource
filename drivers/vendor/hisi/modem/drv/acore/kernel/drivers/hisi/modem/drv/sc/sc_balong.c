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
#endif
#endif


/*lint -save -e322 -e7 -e537*/
#include <stdarg.h>
#include <linux/err.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/mtd/mtd.h>
#include <mdrv.h>
#include "../../adrv/adrv.h"
#include "bsp_misc.h"
#include "sc_balong.h"
#include "nv_ctrl.h"
/*lint -restore +e322 +e7 +e537*/

/*lint -save -e438 -e530 -e713 -e830 -e529*/
char g_sc_area_name[64] = {};

/* func type */
s32  sc_bakup(s8 *pdata, u32 len);
s32  sc_restore(s8 *pdata, u32 len);


/*
* Function   : sc_bakup
* Discription: c core nv init,this phase build upon the a core kernel init,
*              this phase after icc init,this phase ensure to use all nv api normal
*              start at this phase ,ops global ddr need spinlock
* Parameter  : none
* Output     : result
* History    :
*/
s32  sc_bakup(s8 *pdata, u32 len)
{
    s32 wlen        = 0;
    u32 sc_mtd_len  = 0;
    struct mtd_info* mtd;

    if((NULL == pdata)||(0 == len))
    {
        sc_error_printf("pdata is NULL\n");
        return BSP_ERR_SC_INVALID_PARAM;
    }

    mtd = get_mtd_device_nm((char*)g_sc_area_name);
    if (IS_ERR(mtd))
    {
        sc_error_printf("get mtd device err!\n");
        return BSP_ERR_READ_MTD_FAIL;
    }
    sc_mtd_len = mtd->size;
    sc_debug_printf("mtd len: 0x%x\n",sc_mtd_len);
    put_mtd_device(mtd);

    if((sc_mtd_len < SC_MTD_PTABLE_OFFSET) || (len >= SC_MTD_PTABLE_OFFSET))
    {
        sc_error_printf("mtd length err! sc_mtd_len: 0x%x, len: 0x%x\n",sc_mtd_len, len);
        return BSP_ERR_READ_LGTH_FAIL;
    }

    wlen = bsp_nand_write((char*)g_sc_area_name, (sc_mtd_len - SC_MTD_PTABLE_OFFSET), pdata, len);
    if(wlen != BSP_OK)
    {
        sc_error_printf("mtd length err! wlen 0x%x, len is 0x%x\n",wlen,len);
        return BSP_ERR_SC_WRITE_FILE_FAIL;
    }

    sc_debug_printf("sc write to nand ok, len is 0x%x!\n",(u32)(wlen));
    return SC_OK;
}

/*
* Function   : sc_restore
* Discription: c core nv init,this phase build upon the a core kernel init,
*              this phase after icc init,this phase ensure to use all nv api normal
*              start at this phase ,ops global ddr need spinlock
* Parameter  : none
* Output     : result
* History    :
*/
s32  sc_restore(s8 *pdata, u32 len)
{
    s32 rlen        = 0;
    u32 sc_mtd_len  = 0;
    struct mtd_info* mtd;

    if((NULL == pdata)||(0 == len))
    {
        sc_error_printf("pdata is NULL\n");
        return BSP_ERR_SC_INVALID_PARAM;
    }

    mtd = get_mtd_device_nm((char*)g_sc_area_name);
    if (IS_ERR(mtd))
    {
        sc_error_printf("get mtd device err! %s\n",g_sc_area_name);
        return BSP_ERR_READ_MTD_FAIL;
    }
    sc_mtd_len = mtd->size;
    put_mtd_device(mtd);

    if((sc_mtd_len < SC_MTD_PTABLE_OFFSET) || (len >= SC_MTD_PTABLE_OFFSET))
    {
        sc_error_printf("mtd length err! size 0x%x\n",mtd->size);
        return BSP_ERR_READ_LGTH_FAIL;
    }

    rlen = bsp_nand_read((char*)g_sc_area_name, (sc_mtd_len - SC_MTD_PTABLE_OFFSET), pdata, len, NULL);
    if(rlen != BSP_OK)
    {
        sc_error_printf("mtd length err! read_ret 0x%x, len is 0x%x\n",rlen,len);
        return BSP_ERR_SC_READ_FILE_FAIL;
    }
    else
    {
        sc_debug_printf("mtd length read ok len is 0x%x\n",rlen);
    }

    return SC_OK;
}

/*
* Function   : bsp_sc_kernel_init
* Discription: c core nv init,this phase build upon the a core kernel init,
*              this phase after icc init,this phase ensure to use all nv api normal
*              start at this phase ,ops global ddr need spinlock
* Parameter  : none
* Output     : result
* History    :
*/
s32 bsp_sc_kernel_init(void)
{
    s32 ret = SC_ERROR;
    char result[64] = "block2mtd: ";

    ret = flash_find_ptn((const char*)PARTITION_MODEM_NVDEFAULT_NAME, g_sc_area_name);
    if(ret)
    {
        sc_error_printf("find %s fail, ret = 0x%x\n", PARTITION_MODEM_NVDEFAULT_NAME, ret);
        return BSP_ERR_SC_FIND_FAIL;
    }
    else
    {
        sc_error_printf("%s name: %s\n", PARTITION_MODEM_NVDEFAULT_NAME, g_sc_area_name);
    }
    strncpy(result, "block2mtd: ", sizeof("block2mtd: "));
    strncat(result, g_sc_area_name, sizeof(g_sc_area_name));
    strncpy(g_sc_area_name, result, strlen(result));


    sc_printf("[SC]: init success.\n");
    return SC_OK;
}


/* module init */
module_init(bsp_sc_kernel_init);

/*
* Function   : bsp_sc_restore
* Parameter  : none
* Output     : result
* History    :
*/
s32 bsp_sc_restore(u8* pRamAddr,u32 len)
{
    return sc_restore((s8 *)pRamAddr,len);
}

/*
* Function   : bsp_sc_backup
* Parameter  : none
* Output     : result
* History    :
*/
s32 bsp_sc_backup(u8* pRamAddr,u32 len)
{
    return sc_bakup((s8 *)pRamAddr,len);
}

EXPORT_SYMBOL(bsp_sc_restore);
EXPORT_SYMBOL(bsp_sc_backup);
/*lint -restore*/
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif



