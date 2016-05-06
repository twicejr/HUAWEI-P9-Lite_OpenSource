
/*************************************************************************
*   版权所有(C) 1987-2020, 深圳华为技术有限公司.
*
*   文 件 名 :  product_version_info.c
*
*   作    者 :  zuofenghua
*
*   描    述 :  用于维护硬件版本号相关信息
*
*   修改记录 :  2013年2月23日  v1.00  zuofenghua  创建
*
*************************************************************************/

/*lint --e{537}*/
/*lint -save -e958*/

#include <string.h>
#include "securec.h"
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
* 函 数 名  	: bsp_version_ccore_init
*
* 功能描述  : ccore版本号初始化
*
* 参数说明  : 无
*
*返回值 : 无
*****************************************************************************/
int bsp_version_ccore_init(void)
{
    int ret = VER_ERROR;
    (void)memset_s((void *)(&huawei_product_info), sizeof(PRODUCT_INFO_NV_STRU), 0, sizeof(PRODUCT_INFO_NV_STRU));

    ret = bsp_version_productinfo_init();
    if(VER_ERROR==ret)
        ver_print_error("bsp_version_productinfo_init fail! ");
    else
        ver_print_error("bsp version ccore init OK!\n");

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
        /*lint -save -e18 -e718 -e746 -e732*/
        len = (unsigned int)(strlen(huawei_product_info.hwVer) + strlen(" Ver.X"));
        hardware_sub_ver = (char)huawei_product_info.hwIdSub+'A';
        (void)memset_s((void *)hardware_version, VERSION_MAX_LEN, 0, MemparamType(len));
        /*lint -restore*/
        /* coverity[secure_coding] */
        (void)strncat_s((char *)strncat_s(hardware_version, VERSION_MAX_LEN, huawei_product_info.hwVer, 
        strlen(huawei_product_info.hwVer)), VERSION_MAX_LEN, " Ver.", strlen(" Ver."));
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
        /*lint -save -e732*/
        (void)memset_s((void*)product_inner_name, VERSION_MAX_LEN, 0, MemparamType(len));
        /*lint -restore*/
        /* coverity[secure_coding] */
        (void)strncat_s((char *)strncat_s(product_inner_name, VERSION_MAX_LEN, huawei_product_info.name, strlen(huawei_product_info.name)), VERSION_MAX_LEN, huawei_product_info.namePlus, strlen(huawei_product_info.namePlus));
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
    /*lint -save -e124*/
	return (BSP_VERSION_INFO_S *)(SHM_BASE_ADDR + SHM_OFFSET_VERSION);
    /*lint -restore*/
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

/*lint -restore*/

