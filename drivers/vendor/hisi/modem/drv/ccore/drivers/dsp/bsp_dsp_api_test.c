/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  bsp_dsp.c
*
*   作    者 :  z00227143
*
*   描    述 :  本文件主要完成DSP镜像的加载及低功耗处理
*
*   修改记录 :  2013年2月2日  v1.00  z00227143  创建
*************************************************************************/

#include <bsp_om.h>
#include <bsp_dsp.h>
#include <mdrv_dsp.h>


#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 结构名    : PS_PHY_DYN_ADDR_SHARE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 物理层和PS的共享地址，OAM需要获取并传给TTF或者初始化后由PHY读取
*****************************************************************************/
typedef struct
{
    /*物理层初始化,PS只读*/
    unsigned int uwProtectWord1;                      /*0x5a5a5a5a
 */
    unsigned int uwPhyGttfShareAddr;                  /* GDSP与GTTF共享内存接口地址,物理层初始化
 */

    /*PS负责初始化,PHY只读*/
    unsigned int uwProtectWord2;                      /*0x5a5a5a5a，PS填写
 */
    unsigned int uwHsupaUpaccMacePduBaseAddr;         /*HSUPA_UPACC_MACE_PDU_BASE_ADDR
 */
    unsigned int uwEcsArmDspBufferSize;               /*ECS_ARM_DSP_BUFFER_SIZE
 */
    unsigned int uwSocTimeSliceAddr;                  /*时标读取地址
 */

    /*AXI addr*/
    unsigned int uwStatusFlagAddr;                    /*HIFI/DSP STATUS_FLAG_ADDR
 */
    unsigned int uwTempratureAddr;                    /*温保
 */

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
    unsigned int uwProtectWord;           /*0x5a5a5a5a
 */
    unsigned int uwHifiPhyMboxHeadAddr;   /*HIFI和PHY的共享区定义，PHY负责初始化（须静态初始化）
 */
    unsigned int uwHifiPhyMboxBodyAddr;
    unsigned int uwPhyHifiMboxHeadAddr;   /*PHY和HIFI的共享区定义，PHY负责初始化（须静态初始化）
 */
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

int mdrv_dsp_load_bbe_test(void)
{
    int ret = 0;
    bsp_bbe_reset();
    mdrv_dsp_load_bbe();
    ret = bsp_bbe_is_muti_loaded();
    if( 1 == ret )
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp load bbe ok !\n");
        return 0;
    }
    return -1;
}

int mdrv_dsp_run_bbe_test(void)
{
    bsp_bbe_reset();
    bsp_bbe_load_muti();
    mdrv_dsp_run_bbe();
    if(1 == bsp_bbe_is_run())
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp run bbe ok !\n");
        return 0;
    }
    return -1;
}

int mdrv_dsp_backup_bbe_test(void)
{
    mdrv_dsp_backup_bbe();
    if(1 == bsp_msp_bbe_is_stored())
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp backup bbe ok !\n");
        return 0;
    }
    return -1;
}

int mdrv_dsp_restore_bbe_test(void)
{
    mdrv_dsp_restore_bbe();
    if(1 == bsp_msp_bbe_is_restored())
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp restore bbe ok !\n");
        return 0;
    }
    return -1;
}

int mdrv_dsp_get_br_status_test()
{
    mdrv_dsp_get_br_status();
    if(1 == bsp_msp_is_edma_ok())
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp get br status ok !\n");
        return 0;
    }
    return -1;
}

int mdrv_dsp_stop_bbe_test()
{
    bsp_bbe_reset();
    bsp_bbe_load_muti();
    bsp_bbe_run();
    mdrv_dsp_stop_bbe();
    if(0 == bsp_bbe_is_run())
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp stop bbe ok !\n");
        return 0;
    }
    return -1;
}

int mdrv_dsp_unreset_bbe_test()
{
    mdrv_dsp_unreset_bbe();
    if(1 == bsp_bbe_is_unreset())
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp unreset bbe ok !\n");
        return 0;
    }
    return -1;
}

int mdrv_dsp_reset_bbe_test()
{
    mdrv_dsp_reset_bbe();
    if(0 == bsp_bbe_is_unreset())
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp reset bbe ok !\n");
        return 0;
    }
    return -1;
}

int mdrv_dsp_enable_clk_test()
{
    mdrv_dsp_enable_clk();
    if(1 == bsp_bbe_is_clock_enable())
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp enable bbe clk ok !\n");
        return 0;
    }
    return -1;
}

int mdrv_dsp_disable_clk_test()
{
    mdrv_dsp_disable_clk();
    if(0 == bsp_bbe_is_clock_enable())
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp disable bbe clk ok !\n");
        return 0;
    }
    return -1;
}

int mdrv_dsp_update_shareinfo_test(void)
{
    int ret = 0;
    DSP_SHARE_ADDR_STRU str;
    str.stPsPhyDynAddr.uwProtectWord1 = 0x5a5a5a5a;
    ret = mdrv_dsp_update_shareinfo((unsigned long)&str);
    if(0 != ret)
        return -1;
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp update shareinfo ok !\n");
    str.stPsPhyDynAddr.uwProtectWord1 = 0x0;
    ret = mdrv_dsp_update_shareinfo((unsigned long)&str);
    if(-1 != ret)
        return -1; 
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "\ndsp update shareinfo ok !\n");
    return 0;
}

#ifdef __cplusplus
}
#endif

