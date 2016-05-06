/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  adp_dsp.c
*
*   作    者 :  z00227143
*
*   描    述 :  本文件主要适配GU DSP上移共享数据段的赋值
*
*   修改记录 :  2013年2月2日  v1.00  z00227143  创建
*************************************************************************/

/*lint --e{537} */
#include <stdio.h>
#include <string.h>
#include <product_config.h>
#include <drv_nv_id.h>
#include <drv_nv_def.h>
#include <bsp_nvim.h>
#include <bsp_dsp.h>

#include "mdrv_dsp.h"
#include <bsp_dspload.h>
/*****************************************************************************
 结构名    : PS_PHY_DYN_ADDR_SHARE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 物理层和PS的共享地址，OAM需要获取并传给TTF或者初始化后由PHY读取
*****************************************************************************/
typedef struct
{
    /*物理层初始化,PS只读*/
    unsigned int uwProtectWord1;                      /*0x5a5a5a5a*/
    unsigned int uwPhyGttfShareAddr;                  /* GDSP与GTTF共享内存接口地址,物理层初始化*/

    /*PS负责初始化,PHY只读*/
    unsigned int uwProtectWord2;                      /*0x5a5a5a5a，PS填写*/
    unsigned int uwHsupaUpaccMacePduBaseAddr;         /*HSUPA_UPACC_MACE_PDU_BASE_ADDR*/
    unsigned int uwEcsArmDspBufferSize;               /*ECS_ARM_DSP_BUFFER_SIZE*/
    unsigned int uwSocTimeSliceAddr;                  /*时标读取地址*/

    /*AXI addr*/
    unsigned int uwStatusFlagAddr;                    /*HIFI/DSP STATUS_FLAG_ADDR*/
    unsigned int uwTempratureAddr;                    /*温保*/

    unsigned long uwHsdpaWttfBufAddr;                  /* HSDPA WTTF共享buf地址 */
    /*保留，扩展用。以后可以把平台相关的地址放到这里传递进来*/
    unsigned long uwReserved[15];
}PS_PHY_DYN_ADDR_SHARE_STRU;

/*****************************************************************************
 结构名    : PHY_HIFI_DYN_ADDR_SHARE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 物理层和HIFI的共享地址，OAM需要拷贝到HIFI的BOOT区共享数据中的相应结构体
*****************************************************************************/
typedef struct
{
    unsigned int uwProtectWord;           /*0x5a5a5a5a*/
    unsigned int uwHifiPhyMboxHeadAddr;   /*HIFI和PHY的共享区定义，PHY负责初始化（须静态初始化）*/
    unsigned int uwHifiPhyMboxBodyAddr;
    unsigned int uwPhyHifiMboxHeadAddr;   /*PHY和HIFI的共享区定义，PHY负责初始化（须静态初始化）*/
    unsigned int uwPhyHifiMboxBodyAddr;
    unsigned int uwReserved[3];
}PHY_HIFI_DYN_ADDR_SHARE_STRU;

/*****************************************************************************
 结构名    : PS_PHY_DYN_ADDR_SHARE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DSP上电时OAM需要往DSP的".dsp_share_addr"段写如下结构的数据，起始地址由DRV解析ZSP bin件后传给OAM
*****************************************************************************/
typedef struct
{
    PS_PHY_DYN_ADDR_SHARE_STRU      stPsPhyDynAddr;     /*PS和PHY的共享区定义 */
    PHY_HIFI_DYN_ADDR_SHARE_STRU    stPhyHifiDynAddr;   /*PHY和HIFI的共享区定义 */
}DSP_SHARE_ADDR_STRU;

/************************************************************************
 * FUNCTION
 *       BSP_GUDSP_UpateShareInfo
 * DESCRIPTION
 *       完成DSP共享的动态信息获取和更新功能
 * INPUTS
 *       NONE
 * OUTPUTS
 *       BSP_OK/BSP_ERR
 *************************************************************************/
/*lint -save -e586*/
int mdrv_dsp_update_shareinfo(unsigned long shareAddr)
{
    DSP_SHARE_ADDR_STRU      *pstDspShareInfo = (DSP_SHARE_ADDR_STRU*)shareAddr;

    if(0x5A5A5A5A != pstDspShareInfo->stPsPhyDynAddr.uwProtectWord1)
    {
        (void)printf("\r\n BSP_GUDSP_UpateShareInfo: ZSP Share Info uwProtectWord1 Error.");
        return -1;     /*异常退出后会重启*/
    }

    /*填写L2使用的地址空间大小*/
    pstDspShareInfo->stPsPhyDynAddr.uwHsupaUpaccMacePduBaseAddr   = DDR_UPA_ADDR;
    pstDspShareInfo->stPsPhyDynAddr.uwEcsArmDspBufferSize         = DDR_UPA_SIZE;

    //pstDspShareInfo->stPsPhyDynAddr.uwHsdpaWttfBufAddr            = ECS_ARM_DSP_BUFFER_BASE_ADDR;

    /*当前信息写入完成标志*/
    pstDspShareInfo->stPsPhyDynAddr.uwProtectWord2    = 0x5A5A5A5A;

    return 0;
}

/*****************************************************************************
 函 数 名  : bsp_dsp_is_hifi_exist
 功能描述  : 获取CODEC功能状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 1:  CODEC存在
             0：CODEC 不存在
*****************************************************************************/
int bsp_dsp_is_hifi_exist(void)
{
    int ret = 0;
    DRV_MODULE_SUPPORT_STRU   stSupportNv = {0};

    ret = (int)bsp_nvm_read(NV_ID_DRV_MODULE_SUPPORT, (u8*)&stSupportNv, sizeof(DRV_MODULE_SUPPORT_STRU));
    if (ret)
        ret = 0;
    else
        ret = (int)stSupportNv.hifi;

    return ret;
}


int mdrv_dsp_load_bbe(void)
{
    return bsp_bbe_load_muti();
}

int mdrv_dsp_run_bbe(void)
{
    return bsp_bbe_run();
}

int mdrv_dsp_stop_bbe(void)
{
    return bsp_bbe_stop();
}

int mdrv_dsp_unreset_bbe(void)
{
    return bsp_bbe_unreset();
}

int mdrv_dsp_reset_bbe(void)
{
    return bsp_bbe_reset();
}

int mdrv_dsp_enable_clk(void)
{
    return bsp_bbe_clock_enable();
}

int mdrv_dsp_disable_clk(void)
{
    return bsp_bbe_clock_disable();
}

int mdrv_dsp_backup_bbe(void)
{
    return bsp_msp_bbe_store();
}
int mdrv_dsp_restore_bbe(void)
{
    return bsp_msp_bbe_restore();
}

int mdrv_dsp_get_br_status(void)
{
    return bsp_msp_wait_edma_ok();
}

#ifdef CONFIG_CBBE

int mdrv_dsp_load(BSP_DSP_TYPE_E edsptype)
{
    return bsp_bbe_load(edsptype);
}

int mdrv_dsp_run(BSP_DSP_TYPE_E edsptype)
{
    return bsp_bbe_run_ex(edsptype);
}

int mdrv_dsp_stop(BSP_DSP_TYPE_E edsptype)
{
    return bsp_bbe_stop_ex(edsptype);
}

int mdrv_dsp_unreset(BSP_DSP_TYPE_E edsptype)
{
    return bsp_bbe_unreset_ex(edsptype);
}

int mdrv_dsp_reset(BSP_DSP_TYPE_E edsptype)
{
    return bsp_bbe_reset_ex(edsptype);
}

int mdrv_dsp_enable_clock(BSP_DSP_TYPE_E edsptype)
{
    return bsp_bbe_clk_enable(edsptype);
}

int mdrv_dsp_disable_clock(BSP_DSP_TYPE_E edsptype)
{
    return bsp_bbe_clk_disable(edsptype);
}

int mdrv_dsp_backup(BSP_DSP_TYPE_E edsptype)
{
    return bsp_dsp_store_dtcm_normal(edsptype);
}

int mdrv_dsp_restore(BSP_DSP_TYPE_E edsptype)
{
    return bsp_dsp_restore_tcm_normal(edsptype);
}

int mdrv_dsp_wait_backup_over(BSP_DSP_TYPE_E edsptype)
{
    return bsp_dsp_wait_store_over_normal(edsptype);
}

int mdrv_dsp_wait_restore_over(BSP_DSP_TYPE_E edsptype)
{
    return bsp_dsp_wait_restore_over_normal(edsptype);
}

int mdrv_dsp_get_addr_info(BSP_DSP_TYPE_E edsptype, BSP_DSP_ADDR_INFO_STRU *pAddrInfo)
{
    return bsp_dsp_get_addr_info(edsptype, pAddrInfo);
}

#else
int mdrv_dsp_load(BSP_DSP_TYPE_E edsptype)
{
    (void)printf("\r\n error : not support X DSP.\r\n ");
    return 0;
}

int mdrv_dsp_run(BSP_DSP_TYPE_E edsptype)
{
    return 0;
}

int mdrv_dsp_stop(BSP_DSP_TYPE_E edsptype)
{
    return 0;
}

int mdrv_dsp_unreset(BSP_DSP_TYPE_E edsptype)
{
    return 0;
}

int mdrv_dsp_reset(BSP_DSP_TYPE_E edsptype)
{
    return 0;
}

int mdrv_dsp_enable_clock(BSP_DSP_TYPE_E edsptype)
{
    return 0;
}

int mdrv_dsp_disable_clock(BSP_DSP_TYPE_E edsptype)
{
    return 0;
}

int mdrv_dsp_backup(BSP_DSP_TYPE_E edsptype)
{
    return 0;
}

int mdrv_dsp_restore(BSP_DSP_TYPE_E edsptype)
{
    return 0;
}

int mdrv_dsp_wait_backup_over(BSP_DSP_TYPE_E edsptype)
{
    return 0;
}

int mdrv_dsp_wait_restore_over(BSP_DSP_TYPE_E edsptype)
{
    return 0;
}

int mdrv_dsp_get_addr_info(BSP_DSP_TYPE_E edsptype, BSP_DSP_ADDR_INFO_STRU *pAddrInfo)
{
    return 1;
}

#endif



