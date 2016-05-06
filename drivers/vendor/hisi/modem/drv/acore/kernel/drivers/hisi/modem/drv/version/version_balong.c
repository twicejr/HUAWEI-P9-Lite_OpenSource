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

/*lint --e{537}*/
/*lint -save -e958*/

#include <linux/module.h>
#include <linux/string.h>
#include <drv_nv_id.h>
#include <bsp_nvim.h>
#include <bsp_version.h>

PRODUCT_INFO_NV_STRU huawei_product_info = {0};
NV_SW_VER_STRU nv_sw_ver={0};

/*****************************************************************************
* 函 数 名  	: bsp_version_productinfo_init
*
* 功能描述  : 读NV(0xD115)的值到huawei_product_info
*
* 参数说明  : 无
*
*返回值 : VER_ERROR表示读取异常
*                   VER_OK表示读取正常
*****************************************************************************/
static __inline__ int bsp_version_productinfo_init(void)
{
    u32 ret = 0;
    u32 hw_ver = bsp_get_version_info()->board_id;

    /*lint -save -e26 -e119*/
    ret = bsp_nvm_read(NV_ID_DRV_NV_VERSION_INIT,(u8*)&huawei_product_info,sizeof(PRODUCT_INFO_NV_STRU));
    if(NV_OK != ret)
    {
        ver_print_error(" bsp_nvm_read failed!\n");
        return VER_ERROR;
    }

    if(hw_ver!=huawei_product_info.index){
        ver_print_error(" product id(0x%x) is not defined in xml!\n",hw_ver);
        huawei_product_info.index = hw_ver;
        return VER_ERROR;
    }
    /*lint -restore*/

    return VER_OK;
}

/*****************************************************************************
* 函 数 名  	: bsp_version_acore_init
*
* 功能描述  : acore版本号初始化
*
* 参数说明  : 无
*
*返回值 : 无
*****************************************************************************/
int bsp_version_acore_init(void)
{
    int ret = VER_ERROR;
    memset((void *)(&huawei_product_info), 0, sizeof(PRODUCT_INFO_NV_STRU));

    ret = bsp_version_productinfo_init();
    if(VER_ERROR==ret)
        ver_print_error("bsp_version_productinfo_init fail! ");
    else
        ver_print_error("bsp version acore init OK!\n");

    mdrv_ver_init();
    return ret;
}



/*****************************************************************************
*                                                                                                                               *
*            以下接口提供给mdrv接口调用                                                  *
*                                                                                                                               *
******************************************************************************/



/*****************************************************************************
* 函 数	: bsp_version_get_hardware
* 功 能	: 获取硬件版本号(硬件版本名称+ Ver.+硬件子版本号+A)
*****************************************************************************/
char * bsp_version_get_hardware(void)
{
    u32 len;
    static bool b_geted=false;
    static char hardware_version[VERSION_MAX_LEN];
    char hardware_sub_ver = 0;

    if((HW_VER_INVALID == huawei_product_info.index))
    {
        ver_print_error("huawei_product_info.index = HW_VER_INVALID\n");
        return NULL;
    }

    if(!b_geted){
        /*lint -save -e18 -e718 -e746*/
        len = (unsigned int)(strlen(huawei_product_info.hwVer) + strlen(" Ver.X"));
        hardware_sub_ver = (char)huawei_product_info.hwIdSub+'A';
        (void)memset((void *)hardware_version, 0, MemparamType(len));
        /*lint -restore*/
        /* coverity[secure_coding] */
        strncat(strncat(hardware_version, huawei_product_info.hwVer, strlen(huawei_product_info.hwVer)), " Ver.", strlen(" Ver."));
        *((hardware_version + len) - 1) = hardware_sub_ver;
        *(hardware_version + len) = 0;
        b_geted=true;
    }

    return (char *)hardware_version;
}

/*****************************************************************************
* 函 数	: bsp_get_product_inner_name
* 功 能	: 获取内部产品名称(内部产品名+ 内部产品名plus)
*****************************************************************************/
char * bsp_version_get_product_inner_name(void)
{
    unsigned int len;
    static bool b_geted=false;
    static char product_inner_name[VERSION_MAX_LEN];

    if( HW_VER_INVALID == huawei_product_info.index)
    {
        ver_print_error("huawei_product_info.index = HW_VER_INVALID\n");
        return NULL;
    }

    if(!b_geted){
        len = (unsigned int)(strlen(huawei_product_info.name)+ strlen(huawei_product_info.namePlus));
        (void)memset((void*)product_inner_name, 0, MemparamType(len));

        /* coverity[secure_coding] */
        strncat(strncat(product_inner_name,huawei_product_info.name, strlen(huawei_product_info.name)), huawei_product_info.namePlus, strlen(huawei_product_info.namePlus));
        *(product_inner_name+len) = 0;
        b_geted=true;
    }

    return  (char*)product_inner_name;
}

/*****************************************************************************
* 函 数	: bsp_get_product_out_name
* 功 能	: 获取外部产品名称
*****************************************************************************/
char * bsp_version_get_product_out_name(void)
{
    if(HW_VER_INVALID == huawei_product_info.index)
    {
        ver_print_error("huawei_product_info.index = HW_VER_INVALID\n");
        return NULL;
    }

    return (char *)huawei_product_info.productId;
}



/*****************************************************************************
*                                                                                                                               *
*            以下接口提供给dump模块调用                                                 *
*                                                                                                                               *
******************************************************************************/



/*****************************************************************************
* 函 数	: bsp_get_build_date_time
* 功 能	: 获取编译日期和时间
*****************************************************************************/
char * bsp_version_get_build_date_time(void)
{
	static char * build_date   = __DATE__ ", " __TIME__;
	return build_date;
}

/*****************************************************************************
* 函 数	: bsp_get_chip_version
* 功 能	: 获取芯片版本号
*****************************************************************************/
char * bsp_version_get_chip(void)
{
	return (char *)PRODUCT_CFG_CHIP_SOLUTION_NAME;
}

/*****************************************************************************
* 函 数	: bsp_get_firmware_version
* 功 能	: 获取软件版本号
*****************************************************************************/
char * bsp_version_get_firmware(void)
{
    u32 ret = VER_OK;

    /*lint -save -e26 -e119*/
    ret=bsp_nvm_read(NV_ID_DRV_NV_DRV_VERSION_REPLACE_I, (u8 *)&nv_sw_ver, sizeof(NV_SW_VER_STRU));
    if(NV_OK != ret){
        ver_print_error("get NV_SW_VERSION_REPLACE failed!\n");
        return (char*)PRODUCT_DLOAD_SOFTWARE_VER;
    }
    else if(0 == nv_sw_ver.nvStatus){
        return (char*)PRODUCT_DLOAD_SOFTWARE_VER;
    }
    /*lint -restore*/

    return (char *)nv_sw_ver.nv_version_info;
}

/*****************************************************************************
* 函 数	: bsp_version_get_release
* 功 能	: 获取全版本号
*****************************************************************************/
char * bsp_version_get_release(void)
{
    return PRODUCT_FULL_VERSION_STR;
}



/*****************************************************************************
* 函 数 名  	: bsp_get_version_info
*
* 功能描述  : 为其他模块提供各种版本号信息
*
* 参数说明  : 无
*
*返回值 : version的共享内存数据结构体的地址
*****************************************************************************/
const BSP_VERSION_INFO_S* bsp_get_version_info(void)
{
	return (BSP_VERSION_INFO_S *)(SHM_BASE_ADDR + SHM_OFFSET_VERSION);
}

/*****************************************************************************
* 函 数	: bsp_version_debug
* 功 能	: 用于调试查看版本号相关信息
*****************************************************************************/
int bsp_version_debug(void)
{
    if(huawei_product_info.index == HW_VER_INVALID){
        ver_print_error("huawei_product_info.index = HW_VER_INVALID\n");
        return VER_ERROR;
    }

    ver_print_error("\n\n1 . the element value of nv(0xd115):\n");
    ver_print_error("Hardware index :0x%x\n",huawei_product_info.index);
    ver_print_error("hw_Sub_ver     :0x%x\n",huawei_product_info.hwIdSub);
    ver_print_error("Inner name     :%s\n",huawei_product_info.name);
    ver_print_error("name plus      :%s\n",huawei_product_info.namePlus);
    ver_print_error("HardWare ver   :%s\n",huawei_product_info.hwVer);
    ver_print_error("DLOAD_ID       :%s\n",huawei_product_info.dloadId);
    ver_print_error("Out name       :%s\n",huawei_product_info.productId);

    ver_print_error("\n\n2 . the element value of nv(0xc362):\n");
    ver_print_error("nvStatus       :0x%x\n",nv_sw_ver.nvStatus);
    ver_print_error("nv_version_info:%s\n",nv_sw_ver.nv_version_info);

    ver_print_error("\n\n3 . get from func(bsp_version_get_xxx):\n");
    ver_print_error("HardWare ver   :%s\n",bsp_version_get_hardware());
    ver_print_error("Inner name     :%s\n",bsp_version_get_product_inner_name());
    ver_print_error("Out name       :%s\n",bsp_version_get_product_out_name());
    ver_print_error("Build_time     :%s\n",bsp_version_get_build_date_time());
    ver_print_error("Chip_ver       :%s\n",bsp_version_get_chip());
    ver_print_error("Firmware       :%s\n",bsp_version_get_firmware());
    ver_print_error("Release_ver    :%s\n",bsp_version_get_release());

    ver_print_error("\n\n4 . get from bsp_get_version_info:\n");
    ver_print_error("board_id            :0x%x\n",bsp_get_version_info()->board_id);
    ver_print_error("board_id_udp_masked :0x%x\n",bsp_get_version_info()->board_id_udp_masked);
    ver_print_error("chip_version        :0x%x\n",bsp_get_version_info()->chip_version);
    ver_print_error("chip_type           :0x%x\n",bsp_get_version_info()->chip_type);
    ver_print_error("plat_type           :0x%x  (0:asic a:fpga e:emu)\n",bsp_get_version_info()->plat_type);
    ver_print_error("board_type(for drv) :0x%x  (0:bbit 1:sft 2:asic 3:soc)\n",bsp_get_version_info()->board_type);
    ver_print_error("board_type(for mdrv):0x%x  (0:bbit 1:sft 2:asic)\n",(BOARD_ACTUAL_TYPE_E)bsp_get_version_info()->board_type);
    ver_print_error("bbit_type           :0x%x  (1:dallas 2:722 3:chicago)\n",bsp_get_version_info()->bbit_type);
    ver_print_error("product_type        :0x%x  (0:mbb 1:phone)\n",bsp_get_version_info()->product_type);
    ver_print_error("product_name        :0x%x\n",bsp_get_version_info()->product_name);

    return VER_OK;
}

/*注意:需在nv模块初始化之后*/
module_init(bsp_version_acore_init);

EXPORT_SYMBOL_GPL(huawei_product_info);
EXPORT_SYMBOL_GPL(bsp_version_acore_init);
EXPORT_SYMBOL_GPL(bsp_version_get_hardware);
EXPORT_SYMBOL_GPL(bsp_version_get_product_out_name);
EXPORT_SYMBOL_GPL(bsp_version_get_product_inner_name);
EXPORT_SYMBOL_GPL(bsp_get_version_info);
EXPORT_SYMBOL_GPL(bsp_version_debug);

/*lint -restore*/

