/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : ombbpmaster.c
  版 本 号   : 初稿
  作    者   : lixiao 00246515
  生成日期   : 2014年1月13日
  最近修改   :
  功能描述   : BbpMaster IP 软件适配模块，提供读写通道的使能、去使能接口，以及冲突检测
  函数列表   :
              OM_BbpMasterChanCheckDeCfgPara
              OM_BbpMasterChanSendErrorMsg
              OM_BbpMasterInit
              OM_BbpMasterInitLogFile
              OM_BbpMasterIpcIsr
              OM_BbpMasterRdChanCheckCfgPara
              OM_BbpMasterRdChanGive
              OM_BbpMasterRdChanInfoRefresh
              OM_BbpMasterRdChanIpcLock
              OM_BbpMasterRdChanIpcUnLock
              OM_BbpMasterRdChannelConfig
              OM_BbpMasterRdChannelDeConfig
              OM_BbpMasterRdChanTake
              OM_BbpMasterRdErrorInfoSave
              OM_BbpMasterSaveLogFile
              OM_BbpMasterWrChanCheckCfgPara
              OM_BbpMasterWrChanGive
              OM_BbpMasterWrChanInfoRefresh
              OM_BbpMasterWrChanIpcLock
              OM_BbpMasterWrChanIpcUnLock
              OM_BbpMasterWrChannelConfig
              OM_BbpMasterWrChannelDeConfig
              OM_BbpMasterWrChanTake
              OM_BbpMasterWrErrorInfoSave
  修改历史   :
  1.日    期   : 2014年1月13日
    作    者   : lixiao 00246515
    修改内容   : 创建文件

******************************************************************************/
#include "product_config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "apmprocess.h"
#include "ombbpmaster.h"
#include "hpaoperatertt.h"
#include "bbp_gsm_interface.h"
#include "bbp_comm_interface.h"
#include "soc_bbpmaster_interface.h"
#include "mdrv.h"

#if (FEATURE_BBP_MASTER_CHAN_EXTEND == FEATURE_ON)
#include "bbp_guc_bbpmst_interface.h"
#endif

/*lint -e767 修改人:李霄;检视人:徐铖 51137;原因:Log打印 */
#define    THIS_FILE_ID        PS_FILE_ID_OM_BBP_MASTER_C
/*lint +e767 修改人:李霄;检视人:徐铖 51137; */


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
OM_BBPMASTER_UINT32   g_ulOmBbpMasterChipType = OM_BBPMASTER_NO_IP;

BBPMASTER_ENTITY_STRU g_astOmBbpMasterWrEntity[OM_BBPMASTER_MAX_WR_CHAN_CNT];
BBPMASTER_ENTITY_STRU g_astOmBbpMasterRdEntity[OM_BBPMASTER_MAX_RD_CHAN_CNT];

OM_BBPMASTER_UINT32   g_astOmBbpMasterWrChanWM[OM_BBPMASTER_MAX_WR_CHAN_CNT];
OM_BBPMASTER_UINT32   g_astOmBbpMasterRdChanWM[OM_BBPMASTER_MAX_RD_CHAN_CNT];

OM_BBPMASTER_UINT32   g_ulOmBbpMasterTest;

OM_BBPMASTER_UINT32   g_astOmBbpMasterWrChCallCnt[OM_BBPMASTER_MAX_WR_CHAN_CNT];
OM_BBPMASTER_UINT32   g_astOmBbpMasterRdChCallCnt[OM_BBPMASTER_MAX_RD_CHAN_CNT];

OM_BBPMASTER_UINT32   g_astOmBbpMasterWrChIpcCnt[OM_BBPMASTER_MAX_WR_CHAN_CNT];
OM_BBPMASTER_UINT32   g_astOmBbpMasterRdChIpcCnt[OM_BBPMASTER_MAX_RD_CHAN_CNT];

/*****************************************************************************
 函 数 名  : OM_BbpMasterGetV8R1BbitBaseAddr
 功能描述  : 根据PID获取V8R1上FPGA平台BBP Master的基地址;
             V8R1FPGA平台上,W、G1、G2的BBP Master基地址不同，在SFT和ASIC上才归一
 输入参数  : ulPID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   :
    作    者   : l00246515
    修改内容   : 新生成函数
*****************************************************************************/
OM_BBPMASTER_UINT32 OM_BbpMasterGetV8R1BbitBaseAddr(OM_BBPMASTER_UINT32 ulPID)
{
    if (I0_DSP_PID_GPHY == ulPID)
    {
        return SOC_BBP_COMM_BASE_ADDR;
    }
    else if (I1_DSP_PID_GPHY == ulPID)
    {
        return SOC_BBP_GSM1_BASE_ADDR;
    }
    else
    {
        return SOC_BBP_CDMA_BASE_ADDR;
    }
}

/*****************************************************************************
 函 数 名  : OM_BbpMasterGetV7R5BbitBaseAddr
 功能描述  : 根据PID获取V8R1上FPGA平台BBP Master的基地址;
             V7R5FPGA平台上,G1、G2的BBP Master基地址不同，在SFT和ASIC上才归一
 输入参数  : ulPID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   :
    作    者   : l00246515
    修改内容   : 新生成函数
*****************************************************************************/
OM_BBPMASTER_UINT32 OM_BbpMasterGetV7R5BbitBaseAddr(OM_BBPMASTER_UINT32 ulPID)
{
    /* BBIT: 2G 基地址适配 */
    if (I0_DSP_PID_GPHY == ulPID)
    {
        return (SOC_BBP_COMM_BASE_ADDR + 0x800); /* G0偏移地址差 0x800 */
    }
    else if (I1_DSP_PID_GPHY == ulPID)
    {
        return (SOC_BBP_COMM_BASE_ADDR + 0x800); /* G1偏移地址差 0x800 */
    }
    else
    {
        return SOC_BBP_COMM_BASE_ADDR;
    }
}

/*****************************************************************************
 函 数 名  : OM_BbpMasterGetK3V6BaseAddr
 功能描述  : 根据PID获取K3V6上FPGA平台BBP Master的基地址;
             K3V6FPGA平台上,U2的BBP Master基地址不同，在SFT和ASIC上才归一
 输入参数  : ulPID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   :
    作    者   : l00246515
    修改内容   : 新生成函数
*****************************************************************************/
OM_BBPMASTER_UINT32 OM_BbpMasterGetK3V6BbitBaseAddr(OM_BBPMASTER_UINT32 ulPID)
{
    /* U2偏移地址差 -0xC90000，依赖于PID同步上库 */

    return SOC_BBP_COMM_BASE_ADDR;
}

/*****************************************************************************
 函 数 名  : OM_BbpMasterGetBaseAddr
 功能描述  : 根据PID获取BBP Master的基地址;
             V8R1FPGA平台上,W、G1、G2的BBP Master基地址不同，在SFT和ASIC上才归一
 输入参数  : ulPID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   :
    作    者   : l00246515
    修改内容   : 新生成函数
*****************************************************************************/
OM_BBPMASTER_UINT32 OM_BbpMasterGetBaseAddr(OM_BBPMASTER_UINT32 ulPID)
{
#ifndef CSDR_FEATURE_ON
    OM_BBPMASTER_INT    lBoardType;

    lBoardType = VOS_GetBoardType();

    /* SFT & ASIC基地址归一 */
    if ((BOARD_TYPE_ASIC == lBoardType) || (BOARD_TYPE_SFT == lBoardType))
    {
        return SOC_BBP_COMM_BASE_ADDR;
    }

    if (OM_BBPMASTER_IP_V8R1 == g_ulOmBbpMasterChipType)
    {
        return OM_BbpMasterGetV8R1BbitBaseAddr(ulPID);
    }
    else if (OM_BBPMASTER_IP_V7R5 == g_ulOmBbpMasterChipType)
    {
        return OM_BbpMasterGetV7R5BbitBaseAddr(ulPID);
    }
    else if (OM_BBPMASTER_IP_K3V6 == g_ulOmBbpMasterChipType)
    {
        return OM_BbpMasterGetK3V6BbitBaseAddr(ulPID);
    }
    else
    {
        return SOC_BBP_COMM_BASE_ADDR;
    }
#else
    /* C模 各种形态基地址相同 */
    return SOC_BBP_COMM_BASE_ADDR;
#endif
}

/*****************************************************************************
 函 数 名  : OM_BbpMasterV7R5RWInt0ChanIsr
 功能描述  : OM BbpMaster适配模块的写通道中断响应处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   :
    作    者   : l00246515
    修改内容   : 新生成函数
*****************************************************************************/
OM_BBPMASTER_VOID OM_BbpMasterV7R5RWInt0ChanIsr(OM_BBPMASTER_VOID)
{
#if ( VOS_WIN32 != VOS_OS_VER )
#if (BBP_MASTER_INT_MODE == FEATURE_ON)
#ifndef CSDR_FEATURE_ON
    OM_BBPMASTER_UINT32          i;
    OM_BBPMASTER_UINT32          ulWrIntSta;
    OM_BBPMASTER_UINT32          ulRdIntSta;

    /*lint -e662 -e661*/
    mdrv_int_disable(mdrv_int_get_num(BSP_INT_TYPE_GUCBBP_AXIMST_ERR0));
    /*lint +e662 +e661*/

    /* [5:0]：分别对应各个物理写通道中断的中断标志。[11:8]：分别对应各个物理读通道中断的中断标志。 */
    ulWrIntSta  = OM_BBPMASTER_READ_REG(BBPCOMM_BBPMST_INT0_STATE_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(I0_DSP_PID_GPHY));
    ulWrIntSta |= OM_BBPMASTER_READ_REG(BBPCOMM_BBPMST_INT0_STATE_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(I1_DSP_PID_GPHY));
    ulWrIntSta |= OM_BBPMASTER_READ_REG(BBPCOMM_BBPMST_INT0_STATE_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(DSP_PID_WPHY));

    OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_CLR_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(I0_DSP_PID_GPHY), ulWrIntSta);
    OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_CLR_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(I1_DSP_PID_GPHY), ulWrIntSta);
    OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_CLR_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(DSP_PID_WPHY), ulWrIntSta);

    ulRdIntSta = ulWrIntSta;

    /* 遍历所有写通道，查询对应的Status Reg，如果有中断上报，则调用对应的中断处理函数，执行完成后，屏蔽对应的中断处理函数 */
    for (i = 0 ; i < OM_BBPMASTER_V7R5_WR_CHAN_CNT; i++)
    {
        if(0 == (ulWrIntSta & 0x1))
        {
            ulWrIntSta = ulWrIntSta >> 1;
            continue;
        }

        if (OM_BBPMASTER_NULL_PTR == g_astOmBbpMasterWrEntity[i].pfnIntFunc)
        {
            ulWrIntSta = ulWrIntSta >> 1;
            continue;
        }

        g_astOmBbpMasterWrEntity[i].pfnIntFunc();
        ulWrIntSta = ulWrIntSta >> 1;
    }

    ulRdIntSta = ulRdIntSta >> 8;

    for (i = 0 ; i < OM_BBPMASTER_V7R5_RD_CHAN_CNT; i++)
    {
        if(0 == (ulRdIntSta & 0x1))
        {
            ulRdIntSta = ulRdIntSta >> 1;
            continue;
        }

        if (OM_BBPMASTER_NULL_PTR == g_astOmBbpMasterRdEntity[i].pfnIntFunc)
        {
            ulRdIntSta = ulRdIntSta >> 1;
            continue;
        }

        g_astOmBbpMasterRdEntity[i].pfnIntFunc();
        ulRdIntSta = ulRdIntSta >> 1;
    }

    /*lint -e662 -e661*/
    mdrv_int_enable(mdrv_int_get_num(BSP_INT_TYPE_GUCBBP_AXIMST_ERR0));
    /*lint +e662 +e661*/

#endif
#endif
#endif
}

/*****************************************************************************
 函 数 名  : OM_BbpMasterV8R5RWInt0ChanIsr
 功能描述  : OM BbpMaster适配模块的写通道中断响应处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   :
    作    者   : l00246515
    修改内容   : 新生成函数
*****************************************************************************/
OM_BBPMASTER_VOID OM_BbpMasterV8R5RWInt0ChanIsr(OM_BBPMASTER_VOID)
{
#if ( VOS_WIN32 != VOS_OS_VER )
#if (BBP_MASTER_INT_MODE == FEATURE_ON)
#ifndef CSDR_FEATURE_ON
    OM_BBPMASTER_UINT32          i;
    OM_BBPMASTER_UINT32          ulWrIntSta;
    OM_BBPMASTER_UINT32          ulRdIntSta;

    /*lint -e662 -e661*/
    mdrv_int_disable(mdrv_int_get_num(BSP_INT_TYPE_GUCBBP_AXIMST_ERR0));
    /*lint +e662 +e661*/

    /* [15:0]：分别对应各个物理写通道中断的中断标志。[31:16]：分别对应各个物理读通道中断的中断标志。 */
    ulWrIntSta  = OM_BBPMASTER_READ_REG(BBPCOMM_BBPMST_INT0_STATE_ADDR);
    OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_CLR_ADDR, ulWrIntSta);

    ulRdIntSta  = ulWrIntSta;

    /* 遍历所有写通道，查询对应的Status Reg，如果有中断上报，则调用对应的中断处理函数，执行完成后，屏蔽对应的中断处理函数 */
    for (i = 0 ; i < OM_BBPMASTER_V8R5_WR_CHAN_CNT; i++)
    {
        if(0 == (ulWrIntSta & 0x1))
        {
            ulWrIntSta = ulWrIntSta >> 1;
            continue;
        }

        if (OM_BBPMASTER_NULL_PTR == g_astOmBbpMasterWrEntity[i].pfnIntFunc)
        {
            ulWrIntSta = ulWrIntSta >> 1;
            continue;
        }

        g_astOmBbpMasterWrEntity[i].pfnIntFunc();
        ulWrIntSta = ulWrIntSta >> 1;
    }

    ulRdIntSta = ulRdIntSta >> OM_BBP_MASTER_CHAN_REG_WIDTH;

    for (i = 0 ; i < OM_BBPMASTER_V8R5_RD_CHAN_CNT; i++)
    {
        if(0 == (ulRdIntSta & 0x1))
        {
            ulRdIntSta = ulRdIntSta >> 1;
            continue;
        }

        if (OM_BBPMASTER_NULL_PTR == g_astOmBbpMasterRdEntity[i].pfnIntFunc)
        {
            ulRdIntSta = ulRdIntSta >> 1;
            continue;
        }

        g_astOmBbpMasterRdEntity[i].pfnIntFunc();
        ulRdIntSta = ulRdIntSta >> 1;
    }

    /*lint -e662 -e661*/
    mdrv_int_enable(mdrv_int_get_num(BSP_INT_TYPE_GUCBBP_AXIMST_ERR0));
    /*lint +e662 +e661*/
#endif
#endif
#endif
}

/*****************************************************************************
 函 数 名  : OM_BbpMasterV8R5RWInt0ChanIsr
 功能描述  : OM BbpMaster适配模块的写通道中断响应处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   :
    作    者   : l00246515
    修改内容   : 新生成函数
*****************************************************************************/
OM_BBPMASTER_VOID OM_BbpMasterK3V6RWInt0ChanIsr(OM_BBPMASTER_VOID)
{
#if ( VOS_WIN32 != VOS_OS_VER )
#if (BBP_MASTER_INT_MODE == FEATURE_ON)
#ifndef CSDR_FEATURE_ON
    OM_BBPMASTER_UINT32          i;
    OM_BBPMASTER_UINT32          ulWrIntStaLow;
    OM_BBPMASTER_UINT32          ulWrIntStHigh;
    OM_BBPMASTER_UINT32          ulRdIntSta;

    ulWrIntStHigh = 0;

    /*lint -e662 -e661*/
    mdrv_int_disable(mdrv_int_get_num(BSP_INT_TYPE_GUCBBP_AXIMST_ERR0));
    /*lint +e662 +e661*/

    /* [15:0]：分别对应各个物理写通道中断的中断标志。[31:16]：分别对应各个物理读通道中断的中断标志。 */
    ulWrIntStaLow = OM_BBPMASTER_READ_REG(BBPCOMM_BBPMST_INT0_STATE_ADDR);
    OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_CLR_ADDR, ulWrIntStaLow);

    if (OM_BBPMASTER_DBG_ON == g_ulOmBbpMasterTest)
    {
        LogPrint1("StaLow 0x%x\n", (int)ulWrIntStaLow);
    }

#if (FEATURE_BBP_MASTER_CHAN_U2 == FEATURE_ON)
    ulWrIntStHigh = OM_BBPMASTER_READ_REG(BBPCOMM_BBPMST_INT0_STATE2_ADDR);
    OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_CLR2_ADDR, ulWrIntStHigh);
#endif

    if (OM_BBPMASTER_DBG_ON == g_ulOmBbpMasterTest)
    {
        LogPrint1("StaHigh 0x%x\n", (int)ulWrIntStHigh);
    }

    ulRdIntSta    = ulWrIntStaLow;

    /* 遍历 0:15 写通道，查询对应的Status Reg，如果有中断上报，则调用对应的中断处理函数，执行完成后，屏蔽对应的中断处理函数 */
    for (i = 0 ; i < OM_BBP_MASTER_CHAN_REG_WIDTH; i++)
    {
        if(0 == (ulWrIntStaLow & 0x1))
        {
            ulWrIntStaLow = ulWrIntStaLow >> 1;
            continue;
        }

        if (OM_BBPMASTER_NULL_PTR == g_astOmBbpMasterWrEntity[i].pfnIntFunc)
        {
            ulWrIntStaLow = ulWrIntStaLow >> 1;
            continue;
        }

        g_astOmBbpMasterWrEntity[i].pfnIntFunc();
        ulWrIntStaLow = ulWrIntStaLow >> 1;
    }

    ulRdIntSta = ulRdIntSta >> OM_BBP_MASTER_CHAN_REG_WIDTH;

    if (OM_BBPMASTER_DBG_ON == g_ulOmBbpMasterTest)
    {
        LogPrint1("RdIntSta 0x%x\n", (int)ulRdIntSta);
    }

    for (i = 0 ; i < OM_BBPMASTER_K3V6_RD_CHAN_CNT; i++)
    {
        if(0 == (ulRdIntSta & 0x1))
        {
            ulRdIntSta = ulRdIntSta >> 1;
            continue;
        }

        if (OM_BBPMASTER_NULL_PTR == g_astOmBbpMasterRdEntity[i].pfnIntFunc)
        {
            ulRdIntSta = ulRdIntSta >> 1;
            continue;
        }

        g_astOmBbpMasterRdEntity[i].pfnIntFunc();
        ulRdIntSta = ulRdIntSta >> 1;
    }

    if (OM_BBPMASTER_DBG_ON == g_ulOmBbpMasterTest)
    {
        LogPrint("RdInt Finish\n");
    }

    /* BBPMST_INT0_MASK2是中断0的写通道23~写通道16的中断mask配置寄存器 */
    for (i = 0 ; i < (OM_BBPMASTER_K3V6_WR_CHAN_CNT - OM_BBP_MASTER_CHAN_REG_WIDTH); i++)
    {
        if(0 == (ulWrIntStHigh & 0x1))
        {
            ulWrIntStHigh = ulWrIntStHigh >> 1;
            continue;
        }

        if (OM_BBPMASTER_NULL_PTR == g_astOmBbpMasterWrEntity[i+OM_BBP_MASTER_CHAN_REG_WIDTH].pfnIntFunc)
        {
            ulWrIntStHigh = ulWrIntStHigh >> 1;
            continue;
        }

        g_astOmBbpMasterWrEntity[i+OM_BBP_MASTER_CHAN_REG_WIDTH].pfnIntFunc();
        ulWrIntStHigh = ulWrIntStHigh >> 1;
    }

    if (OM_BBPMASTER_DBG_ON == g_ulOmBbpMasterTest)
    {
        LogPrint("IntStHigh Finish\n");
    }

    /*lint -e662 -e661*/
    mdrv_int_enable(mdrv_int_get_num(BSP_INT_TYPE_GUCBBP_AXIMST_ERR0));
    /*lint +e662 +e661*/
#endif
#endif
#endif
}

/*****************************************************************************
 函 数 名  : OM_BbpMasterInitChipType
 功能描述  : 初始化BBP MASTER的类型
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月1日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
OM_BBPMASTER_VOID OM_BbpMasterInitChipType( OM_BBPMASTER_VOID )
{
#if (FEATURE_BBP_MASTER == FEATURE_ON)
    g_ulOmBbpMasterChipType = OM_BBPMASTER_IP_V8R1;
#endif

#if (BBP_MASTER_INT_MODE == FEATURE_ON)
    g_ulOmBbpMasterChipType = OM_BBPMASTER_IP_V7R5;
#endif

#if (FEATURE_BBP_MASTER_CHAN_EXTEND == FEATURE_ON)
#if (FEATURE_BBP_MASTER_CHAN_U2 == FEATURE_ON)
    g_ulOmBbpMasterChipType = OM_BBPMASTER_IP_K3V6;
#else
    g_ulOmBbpMasterChipType = OM_BBPMASTER_IP_V8R5;
#endif
#endif

    return;
}

/*****************************************************************************
 函 数 名  : OM_BbpMasterInitBaseAddr
 功能描述  : 初始化BBP访问的基地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月1日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
OM_BBPMASTER_VOID OM_BbpMasterInitBaseAddr( OM_BBPMASTER_VOID )
{
    if (OM_BBPMASTER_NO_IP == g_ulOmBbpMasterChipType )
    {
        return;
    }

    /* 写通道地址初始化 */
    g_astOmBbpMasterWrChanWM[0]  = (BBPCOMM_BBPMST_WR_CH0_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[1]  = (BBPCOMM_BBPMST_WR_CH1_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[2]  = (BBPCOMM_BBPMST_WR_CH2_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[3]  = (BBPCOMM_BBPMST_WR_CH3_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[4]  = (BBPCOMM_BBPMST_WR_CH4_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);

    /* V7R5增加了一个写通道地址 */
#if (BBP_MASTER_INT_MODE == FEATURE_ON)
    g_astOmBbpMasterWrChanWM[5]  = (BBPCOMM_BBPMST_WR_CH5_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
#endif

    /* V8R5增加了8个写通道地址 */
#if (FEATURE_BBP_MASTER_CHAN_EXTEND == FEATURE_ON)
    g_astOmBbpMasterWrChanWM[6]  = (BBPCOMM_BBPMST_WR_CH6_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[7]  = (BBPCOMM_BBPMST_WR_CH7_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[8]  = (BBPCOMM_BBPMST_WR_CH8_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[9]  = (BBPCOMM_BBPMST_WR_CH9_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[10] = (BBPCOMM_BBPMST_WR_CH10_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[11] = (BBPCOMM_BBPMST_WR_CH11_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[12] = (BBPCOMM_BBPMST_WR_CH12_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[13] = (BBPCOMM_BBPMST_WR_CH13_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
#endif

    /* K3V5增加了10个写通道地址 */
#if (FEATURE_BBP_MASTER_CHAN_U2 == FEATURE_ON)
    g_astOmBbpMasterWrChanWM[14] = (BBPCOMM_BBPMST_WR_CH14_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[15] = (BBPCOMM_BBPMST_WR_CH15_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[16] = (BBPCOMM_BBPMST_WR_CH16_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[17] = (BBPCOMM_BBPMST_WR_CH17_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[18] = (BBPCOMM_BBPMST_WR_CH18_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[19] = (BBPCOMM_BBPMST_WR_CH19_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[20] = (BBPCOMM_BBPMST_WR_CH20_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[21] = (BBPCOMM_BBPMST_WR_CH21_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[22] = (BBPCOMM_BBPMST_WR_CH22_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[23] = (BBPCOMM_BBPMST_WR_CH23_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
#endif

    /* 读取通道地址初始化 */
    g_astOmBbpMasterRdChanWM[0]  = (BBPCOMM_BBPMST_RD_CH0_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterRdChanWM[1]  = (BBPCOMM_BBPMST_RD_CH1_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterRdChanWM[2]  = (BBPCOMM_BBPMST_RD_CH2_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterRdChanWM[3]  = (BBPCOMM_BBPMST_RD_CH3_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);

    /* V8R5增加了7个写通道地址 */
#if (FEATURE_BBP_MASTER_CHAN_EXTEND == FEATURE_ON)
    g_astOmBbpMasterRdChanWM[4]  = (BBPCOMM_BBPMST_RD_CH4_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterRdChanWM[5]  = (BBPCOMM_BBPMST_RD_CH5_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterRdChanWM[6]  = (BBPCOMM_BBPMST_RD_CH6_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterRdChanWM[7]  = (BBPCOMM_BBPMST_RD_CH7_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterRdChanWM[8]  = (BBPCOMM_BBPMST_RD_CH8_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterRdChanWM[9]  = (BBPCOMM_BBPMST_RD_CH9_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterRdChanWM[10] = (BBPCOMM_BBPMST_RD_CH10_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
#endif

    /* K3V5增加了5个读通道地址 */
#if (FEATURE_BBP_MASTER_CHAN_U2 == FEATURE_ON)
    g_astOmBbpMasterRdChanWM[11] = (BBPCOMM_BBPMST_RD_CH11_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterRdChanWM[12] = (BBPCOMM_BBPMST_RD_CH12_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterRdChanWM[13] = (BBPCOMM_BBPMST_RD_CH13_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterRdChanWM[14] = (BBPCOMM_BBPMST_RD_CH14_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterRdChanWM[15] = (BBPCOMM_BBPMST_RD_CH15_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
#endif

    return;
}

/*****************************************************************************
 函 数 名  : OM_BbpMasterGetIpInfo
 功能描述  : 获取BBP Master的IP类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OM_BBPMASTER_NO_IP/OM_BBPMASTER_OLD_IP/OM_BBPMASTER_NEW_IP
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   :
    作    者   : l00246515
    修改内容   : 新生成函数
*****************************************************************************/
OM_BBPMASTER_UINT32 OM_BbpMasterGetIpInfo( OM_BBPMASTER_VOID )
{
    return g_ulOmBbpMasterChipType;
}

/*****************************************************************************
 函 数 名  : OM_BbpMasterInitV8R1Entity
 功能描述  : 初始化V8R1 BBP Master的读写实体
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月1日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
OM_BBPMASTER_VOID OM_BbpMasterInitV8R1Entity( OM_BBPMASTER_VOID )
{
    OM_BBPMASTER_UINT32 i;

    for ( i = 0 ; i < OM_BBPMASTER_V8R1_WR_CHAN_CNT; i++ )
    {
        g_astOmBbpMasterWrEntity[i].ulShared    = OM_BBPMASTER_YES;
        g_astOmBbpMasterWrEntity[i].pfnIntFunc  = OM_BBPMASTER_NULL_PTR;

        g_astOmBbpMasterWrChCallCnt[i]          = 0;
        g_astOmBbpMasterWrChIpcCnt[i]           = 0;
    }

    /*  针对V8R1,2G相关写通道去掉互斥保护 */
    g_astOmBbpMasterWrEntity[3].ulShared        = OM_BBPMASTER_NO;
    g_astOmBbpMasterWrEntity[4].ulShared        = OM_BBPMASTER_NO;

    for ( i = 0 ; i < OM_BBPMASTER_V8R1_RD_CHAN_CNT; i++ )
    {
        g_astOmBbpMasterRdEntity[i].ulShared    = OM_BBPMASTER_YES;
        g_astOmBbpMasterRdEntity[i].pfnIntFunc  = OM_BBPMASTER_NULL_PTR;

        g_astOmBbpMasterRdChCallCnt[i]          = 0;
        g_astOmBbpMasterRdChIpcCnt[i]           = 0;
    }

   /*  针对V8R1,2G相关读通道去掉互斥保护 */
    g_astOmBbpMasterRdEntity[2].ulShared        = OM_BBPMASTER_NO;
    g_astOmBbpMasterRdEntity[3].ulShared        = OM_BBPMASTER_NO;

}

/*****************************************************************************
 函 数 名  : OM_BbpMasterInitV7R5Entity
 功能描述  : 初始化V7R5 BBP Master的读写实体
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月1日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
OM_BBPMASTER_VOID OM_BbpMasterInitV7R5Entity( OM_BBPMASTER_VOID )
{
    OM_BBPMASTER_UINT32 i;

    for ( i = 0 ; i < OM_BBPMASTER_V7R5_WR_CHAN_CNT; i++ )
    {
        g_astOmBbpMasterWrEntity[i].ulShared    = OM_BBPMASTER_YES;
        g_astOmBbpMasterWrEntity[i].pfnIntFunc  = OM_BBPMASTER_NULL_PTR;

        g_astOmBbpMasterWrChCallCnt[i]          = 0;
        g_astOmBbpMasterWrChIpcCnt[i]           = 0;
    }

    /*  针对V7R5,2G相关写通道去掉互斥保护 */
    g_astOmBbpMasterWrEntity[0].ulShared        = OM_BBPMASTER_NO;
    g_astOmBbpMasterWrEntity[1].ulShared        = OM_BBPMASTER_NO;
    g_astOmBbpMasterWrEntity[4].ulShared        = OM_BBPMASTER_NO;
    g_astOmBbpMasterWrEntity[5].ulShared        = OM_BBPMASTER_NO;

    for ( i = 0 ; i < OM_BBPMASTER_V7R5_RD_CHAN_CNT; i++ )
    {
        g_astOmBbpMasterRdEntity[i].ulShared    = OM_BBPMASTER_YES;
        g_astOmBbpMasterRdEntity[i].pfnIntFunc  = OM_BBPMASTER_NULL_PTR;

        g_astOmBbpMasterRdChCallCnt[i]          = 0;
        g_astOmBbpMasterRdChIpcCnt[i]           = 0;
    }

    /*  针对V7R5,2G相关读通道去掉互斥保护 */
    g_astOmBbpMasterRdEntity[0].ulShared        = OM_BBPMASTER_NO;
    g_astOmBbpMasterRdEntity[3].ulShared        = OM_BBPMASTER_NO;

#if (BBP_MASTER_INT_MODE == FEATURE_ON)
#ifndef CSDR_FEATURE_ON
    /* 使能ARM上BBP Mater读写通道完成中断，但保持Mask位为默认值(屏蔽),在配置通道时使能Mask位 */
    OM_BBPMASTER_WRITE_REG((BBPCOMM_BBPMST_INT0_EN_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(I0_DSP_PID_GPHY)), 1);
    OM_BBPMASTER_WRITE_REG((BBPCOMM_BBPMST_INT0_EN_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(I1_DSP_PID_GPHY)), 1);
    OM_BBPMASTER_WRITE_REG((BBPCOMM_BBPMST_INT0_EN_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(DSP_PID_WPHY)), 1);

    mdrv_int_connect(mdrv_int_get_num(BSP_INT_TYPE_GUCBBP_AXIMST_ERR0),
                       (VOIDFUNCPTR)OM_BbpMasterV7R5RWInt0ChanIsr,
                        0);

    mdrv_int_enable(mdrv_int_get_num(BSP_INT_TYPE_GUCBBP_AXIMST_ERR0));
#endif
#endif

    return;

}

/*****************************************************************************
 函 数 名  : OM_BbpMasterInitV8R5Entity
 功能描述  : 初始化V8R5 BBP Master的读写实体
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月1日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
OM_BBPMASTER_VOID OM_BbpMasterInitV8R5Entity( OM_BBPMASTER_VOID )
{
    OM_BBPMASTER_UINT32 i;

    for ( i = 0 ; i < OM_BBPMASTER_V8R5_WR_CHAN_CNT; i++ )
    {
        g_astOmBbpMasterWrEntity[i].ulShared    = OM_BBPMASTER_NO;
        g_astOmBbpMasterWrEntity[i].pfnIntFunc  = OM_BBPMASTER_NULL_PTR;

        g_astOmBbpMasterWrChCallCnt[i]          = 0;
        g_astOmBbpMasterWrChIpcCnt[i]           = 0;
    }

    for ( i = 0 ; i < OM_BBPMASTER_V8R5_RD_CHAN_CNT; i++ )
    {
        g_astOmBbpMasterRdEntity[i].ulShared    = OM_BBPMASTER_NO;
        g_astOmBbpMasterRdEntity[i].pfnIntFunc  = OM_BBPMASTER_NULL_PTR;

        g_astOmBbpMasterRdChCallCnt[i]          = 0;
        g_astOmBbpMasterRdChIpcCnt[i]           = 0;
    }

#if (BBP_MASTER_INT_MODE == FEATURE_ON)
#ifndef CSDR_FEATURE_ON
    /* 使能ARM上BBP Mater读、写通道完成中断，但保持Mask位为默认值(屏蔽),在配置通道时使能Mask位 */
    OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_EN_ADDR, 1);

    mdrv_int_connect(mdrv_int_get_num(BSP_INT_TYPE_GUCBBP_AXIMST_ERR0),
                       (VOIDFUNCPTR)OM_BbpMasterV8R5RWInt0ChanIsr,
                        0);

    mdrv_int_enable(mdrv_int_get_num(BSP_INT_TYPE_GUCBBP_AXIMST_ERR0));
#endif
#endif

    return;
}

/*****************************************************************************
 函 数 名  : OM_BbpMasterInitV8R5Entity
 功能描述  : 初始化V8R5 BBP Master的读写实体
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月1日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
OM_BBPMASTER_VOID OM_BbpMasterInitK3V6Entity( OM_BBPMASTER_VOID )
{
    OM_BBPMASTER_UINT32 i;

    for ( i = 0 ; i < OM_BBPMASTER_K3V6_WR_CHAN_CNT; i++ )
    {
        g_astOmBbpMasterWrEntity[i].ulShared    = OM_BBPMASTER_NO;
        g_astOmBbpMasterWrEntity[i].pfnIntFunc  = OM_BBPMASTER_NULL_PTR;

        g_astOmBbpMasterWrChCallCnt[i]          = 0;
        g_astOmBbpMasterWrChIpcCnt[i]           = 0;
    }

    for ( i = 0 ; i < OM_BBPMASTER_K3V6_RD_CHAN_CNT; i++ )
    {
        g_astOmBbpMasterRdEntity[i].ulShared    = OM_BBPMASTER_NO;
        g_astOmBbpMasterRdEntity[i].pfnIntFunc  = OM_BBPMASTER_NULL_PTR;

        g_astOmBbpMasterRdChCallCnt[i]          = 0;
        g_astOmBbpMasterRdChIpcCnt[i]           = 0;
    }

#if (BBP_MASTER_INT_MODE == FEATURE_ON)
#ifndef CSDR_FEATURE_ON
    /* 使能ARM上BBP Mater读、写通道完成中断，但保持Mask位为默认值(屏蔽),在配置通道时使能Mask位 */
    OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_EN_ADDR, 1);

    mdrv_int_connect(mdrv_int_get_num(BSP_INT_TYPE_GUCBBP_AXIMST_ERR0),
                       (VOIDFUNCPTR)OM_BbpMasterK3V6RWInt0ChanIsr,
                        0);

    mdrv_int_enable(mdrv_int_get_num(BSP_INT_TYPE_GUCBBP_AXIMST_ERR0));
#endif
#endif

    return;
}

/*****************************************************************************
 函 数 名  : OM_BbpMasterInitEntity
 功能描述  : 初始化BBP Master的读写实体
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月1日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
OM_BBPMASTER_VOID OM_BbpMasterInitEntity( OM_BBPMASTER_VOID )
{
    g_ulOmBbpMasterTest = 0;

    switch (g_ulOmBbpMasterChipType)
    {
        case OM_BBPMASTER_IP_V8R1:
            OM_BbpMasterInitV8R1Entity();
            break;

        case OM_BBPMASTER_IP_V7R5:
            OM_BbpMasterInitV7R5Entity();
            break;

        case OM_BBPMASTER_IP_V8R5:
            OM_BbpMasterInitV8R5Entity();
            break;

        case OM_BBPMASTER_IP_K3V6:
            OM_BbpMasterInitK3V6Entity();
            break;

        default:
            break;
    }
}

/*****************************************************************************
 函 数 名  : OM_BbpMasterInit
 功能描述  : OM BbpMaster适配模块初始化函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   :
    作    者   : l00246515
    修改内容   : 新生成函数
*****************************************************************************/
OM_BBPMASTER_UINT32 OM_BbpMasterInit( OM_BBPMASTER_VOID )
{
    OM_BbpMasterInitChipType();

    OM_BbpMasterInitBaseAddr();

    OM_BbpMasterInitEntity();

    return OM_BBPMASTER_OK;
}

/*****************************************************************************
 函 数 名  : OM_BbpMasterWrChanIpcLock
 功能描述  : OM BbpMaster适配模块写通道的IPC资源锁申请函数
 输入参数  : ulChanId
 输出参数  : 无
 返 回 值  : VOS_YES、VOS_NO
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   :
    作    者   : l00246515
    修改内容   : 新生成函数
*****************************************************************************/
OM_BBPMASTER_UINT32 OM_BbpMasterWrChanIpcLock( OM_BBPMASTER_UINT32 ulChanId )
{
#if (FEATURE_BBP_MASTER == FEATURE_ON)
    OM_BBPMASTER_UINT32             u32SignalNum;

    /* 通道属性不需要通过资源锁互斥 */
    if (OM_BBPMASTER_NO == g_astOmBbpMasterWrEntity[ulChanId].ulShared)
    {
        if (OM_BBPMASTER_DBG_ON == g_ulOmBbpMasterTest)
        {
            /*lint -e534*/
            LogPrint1("OM_BbpMasterWrChanIpcLock Chan Id: %d Need not IPC\n", (int)ulChanId);
            /*lint +e534*/
        }

        return OM_BBPMASTER_YES;
    }

    g_astOmBbpMasterWrChIpcCnt[ulChanId]++;

    /* 底软的写通道IPC资源锁号对应写通道ID + IPC_SEM_BBPMASTER_0 */
    u32SignalNum = ulChanId + IPC_SEM_BBPMASTER_0;

#ifdef CSDR_FEATURE_ON
#else
    if (VOS_OK == mdrv_ipc_spin_trylock(u32SignalNum))
    {
        if (OM_BBPMASTER_DBG_ON == g_ulOmBbpMasterTest)
        {
            /*lint -e534*/
            LogPrint1("OM_BbpMasterWrChanIpcLock mdrv_ipc_spin_trylock u32SignalNum: %d\n", (int)u32SignalNum);
            /*lint +e534*/
        }

        return OM_BBPMASTER_YES;
    }
#endif
#endif

    return OM_BBPMASTER_NO;
}

/*****************************************************************************
 函 数 名  : OM_BbpMasterWrChanIpcUnLock
 功能描述  : OM BbpMaster适配模块写通道的IPC资源锁释放函数
 输入参数  : ulChanId
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   :
    作    者   : l00246515
    修改内容   : 新生成函数
*****************************************************************************/
OM_BBPMASTER_VOID OM_BbpMasterWrChanIpcUnLock( OM_BBPMASTER_UINT32 ulChanId )
{
#if (FEATURE_BBP_MASTER == FEATURE_ON)
    OM_BBPMASTER_UINT32                          u32SignalNum;

    /* 通道属性不需要通过资源锁互斥 */
    if (OM_BBPMASTER_NO == g_astOmBbpMasterWrEntity[ulChanId].ulShared)
    {
        if (OM_BBPMASTER_DBG_ON == g_ulOmBbpMasterTest)
        {
            /*lint -e534*/
            LogPrint1("OM_BbpMasterWrChanIpcUnLock Chan Id: %d Need not IPC\n", (int)ulChanId);
            /*lint +e534*/
        }

        return;
    }

    /* 多余的Unlock不统计 */
    if (0 < g_astOmBbpMasterWrChIpcCnt[ulChanId])
    {
        g_astOmBbpMasterWrChIpcCnt[ulChanId]--;
    }

    /* 底软的写通道IPC资源锁号对应写通道ID + IPC_SEM_BBPMASTER_0 */
    u32SignalNum = ulChanId + IPC_SEM_BBPMASTER_0;

#ifdef CSDR_FEATURE_ON
#else
    mdrv_ipc_spin_unlock(u32SignalNum);

    if (OM_BBPMASTER_DBG_ON == g_ulOmBbpMasterTest)
    {
        /*lint -e534*/
        LogPrint1("OM_BbpMasterWrChanIpcUnLock mdrv_ipc_spin_unlock u32SignalNum: %d\n", (int)u32SignalNum);
        /*lint +e534*/
    }
#endif
#endif

    return;
}

/*****************************************************************************
 函 数 名  : OM_BbpMasterRdChanIpcLock
 功能描述  : OM BbpMaster适配模块读通道的IPC资源锁申请函数
 输入参数  : ulChanId
 输出参数  : 无
 返 回 值  : VOS_YES、VOS_NO
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   :
    作    者   : l00246515
    修改内容   : 新生成函数
*****************************************************************************/
OM_BBPMASTER_UINT32 OM_BbpMasterRdChanIpcLock(OM_BBPMASTER_UINT32 ulChanId)
{
#if (FEATURE_BBP_MASTER == FEATURE_ON)
    OM_BBPMASTER_UINT32                          u32SignalNum;

    /* 通道属性不需要通过资源锁互斥 */
    if ( OM_BBPMASTER_NO == g_astOmBbpMasterRdEntity[ulChanId].ulShared )
    {
        if (OM_BBPMASTER_DBG_ON == g_ulOmBbpMasterTest)
        {
            /*lint -e534*/
            LogPrint1("OM_BbpMasterRdChanIpcLock Chan Id: %d Need not IPC\n", (int)ulChanId);
            /*lint +e534*/
        }

        return OM_BBPMASTER_YES;
    }

    g_astOmBbpMasterRdChIpcCnt[ulChanId]++;

    /* 底软的读通道IPC资源锁号对应读通道ID + IPC_SEM_BBPMASTER_5 */
    u32SignalNum = ulChanId + IPC_SEM_BBPMASTER_5;

#ifdef CSDR_FEATURE_ON
#else
    if (VOS_OK == mdrv_ipc_spin_trylock(u32SignalNum))
    {
        if (OM_BBPMASTER_DBG_ON == g_ulOmBbpMasterTest)
        {
            /*lint -e534*/
            LogPrint1("OM_BbpMasterRdChanIpcLock mdrv_ipc_spin_trylock u32SignalNum: %d\n", (int)u32SignalNum);
            /*lint +e534*/
        }

        return VOS_YES;
    }
#endif
#endif

    return VOS_NO;
}

/*****************************************************************************
 函 数 名  : OM_BbpMasterRdChanIpcUnLock
 功能描述  : OM BbpMaster适配模块读通道的IPC资源锁释放函数
 输入参数  : ulChanId
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   :
    作    者   : l00246515
    修改内容   : 新生成函数
*****************************************************************************/
OM_BBPMASTER_VOID OM_BbpMasterRdChanIpcUnLock( OM_BBPMASTER_UINT32 ulChanId )
{
#if (FEATURE_BBP_MASTER == FEATURE_ON)
    OM_BBPMASTER_UINT32                              u32SignalNum;

    /* 通道属性不需要通过资源锁互斥 */
    if ( OM_BBPMASTER_NO == g_astOmBbpMasterRdEntity[ulChanId].ulShared )
    {
        if (OM_BBPMASTER_DBG_ON == g_ulOmBbpMasterTest)
        {
            /*lint -e534*/
            LogPrint1("OM_BbpMasterRdChanIpcUnLock Chan Id: %d Need not IPC\n", (int)ulChanId);
            /*lint +e534*/
        }

        return;
    }

    /* 多余的Unlock不统计 */
    if (0 < g_astOmBbpMasterRdChIpcCnt[ulChanId])
    {
        g_astOmBbpMasterRdChIpcCnt[ulChanId]--;
    }

    /* 底软的读通道IPC资源锁号对应读通道ID + IPC_SEM_BBPMASTER_5 */
    u32SignalNum = ulChanId + IPC_SEM_BBPMASTER_5;

#ifdef CSDR_FEATURE_ON
#else
    mdrv_ipc_spin_unlock(u32SignalNum);

    if (OM_BBPMASTER_DBG_ON == g_ulOmBbpMasterTest)
    {
        /*lint -e534*/
        LogPrint1("OM_BbpMasterRdChanIpcUnLock mdrv_ipc_spin_unlock u32SignalNum: %d\n", (int)u32SignalNum);
        /*lint +e534*/
    }

#endif
#endif

    return;
}

/*****************************************************************************
 函 数 名  : OM_BbpMasterWrChanTake
 功能描述  : OM BbpMaster写通道使能配置，参数使用上层透传形式。
 输入参数  : ulChanId
             pstWrChanCfg
       V7R5: [5:0]：分别为各个物理写通道对应中断的屏蔽位，1表示屏蔽。
              [11:8]：分别为各个物理读通道对应中断的屏蔽位，1表示屏蔽。
              [21:16]：分别为各个物理写通道屏蔽位的写使能。
              [27:24]：分别为各个物理读通道屏蔽位的写使能。

       V8R5: [15:0]：分别为各个物理写通道对应中断的屏蔽位，1表示屏蔽。
              [31:16]：分别为各个物理写通道屏蔽位的写使能。

       K3V6: INT_MASK [15:0]：分别为各个物理写通道(0~15)对应中断的屏蔽位，1表示屏蔽。
                       [31:16]：分别为各个物理写通道(0~15)屏蔽位的写使能。

             INT_MASK2 [15:0]：分别为各个物理写通道(16~24)对应中断的屏蔽位，1表示屏蔽。
                        [31:16]：分别为各个物理写通道(16~24)屏蔽位的写使能。
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   :
    作    者   : l00246515
    修改内容   : 新生成函数
*****************************************************************************/
OM_BBPMASTER_VOID OM_BbpMasterWrChanTake(OM_BBPMASTER_UINT32 ulPID,
                                             OM_BBPMASTER_UINT32 ulChanId,
                                             BBPMASTER_WR_CHANNEL_CONFIG_STRU *pstWrChanCfg)
{
    if (OM_BBPMASTER_NULL_PTR == pstWrChanCfg)
    {
        return;
    }

#if ( VOS_WIN32 != VOS_OS_VER )
    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterWrChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_WR_MODE_OFFSET),
                                                pstWrChanCfg->ulWorkMode);

    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterWrChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_WR_CLK_SEL_OFFSET),
                                                pstWrChanCfg->ulClockSel);

    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterWrChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_WR_BASE_ADDR_OFFSET),
                                                pstWrChanCfg->ulStartAddr);

    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterWrChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_WR_END_ADDR_OFFSET),
                                                pstWrChanCfg->ulEndAddr);

    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterWrChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_WR_BURST_BEAT_OFFSET),
                                                pstWrChanCfg->ulBurstLen);

    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterWrChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_WR_AXI_SEL_OFFSET),
                                                pstWrChanCfg->ulAxiSel);

#if (BBP_MASTER_INT_MODE == FEATURE_ON)
#ifndef CSDR_FEATURE_ON
    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterWrChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_WR_INTR_MODE_OFFSET),
                                                pstWrChanCfg->ulIntMode);

    /* 使能ARM上BBP Mater读写通道完成中断 */
    if (OM_BBPMASTER_IP_V7R5 == g_ulOmBbpMasterChipType)
    {
        OM_BBPMASTER_WRITE_REG((BBPCOMM_BBPMST_INT0_EN_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(I0_DSP_PID_GPHY)), 1);
        OM_BBPMASTER_WRITE_REG((BBPCOMM_BBPMST_INT0_EN_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(I1_DSP_PID_GPHY)), 1);
        OM_BBPMASTER_WRITE_REG((BBPCOMM_BBPMST_INT0_EN_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(DSP_PID_WPHY)), 1);

        OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_MASK_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(ulPID),
            (VOS_UINT32)((VOS_UINT32)OM_BBPMASTER_MASK_BIT_16 << ulChanId));
    }
    else /* Mask(0~15) & Mask2(16~23) */
    {
        OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_EN_ADDR, 1);

        if (OM_BBP_MASTER_CHAN_REG_WIDTH > ulChanId)
        {
            OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_MASK_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(ulPID),
                (VOS_UINT32)((VOS_UINT32)OM_BBPMASTER_MASK_BIT_16 << ulChanId));
        }
        else
        {
#if (FEATURE_BBP_MASTER_CHAN_U2 == FEATURE_ON)
            OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_MASK2_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(ulPID),
                (VOS_UINT32)((VOS_UINT32)OM_BBPMASTER_MASK_BIT_16 << (ulChanId - OM_BBP_MASTER_CHAN_REG_WIDTH)));
#endif
        }
    }

    g_astOmBbpMasterWrEntity[ulChanId].pfnIntFunc = pstWrChanCfg->pfnIntFunc;
#endif
#endif
#endif
}

/*****************************************************************************
 函 数 名  : OM_BbpMasterWrChanGive
 功能描述  : OM BbpMaster写通道去使能配置，参数使用上层透传形式。
 输入参数  : ulChanId
             pstWrChanDeCfg
 输出参数  : 无

     V7R5: [5:0]：分别为各个物理写通道对应中断的屏蔽位，1表示屏蔽。
                  [11:8]：分别为各个物理读通道对应中断的屏蔽位，1表示屏蔽。
                  [21:16]：分别为各个物理写通道屏蔽位的写使能。
                  [27:24]：分别为各个物理读通道屏蔽位的写使能。

    V8R5: [15:0]：分别为各个物理写通道对应中断的屏蔽位，1表示屏蔽。
              [31:16]：分别为各个物理写通道屏蔽位的写使能。

    K3V6: [15:0]：分别为各个物理写通道(0~15)对应中断的屏蔽位，1表示屏蔽。
             [31:16]：分别为各个物理写通道(0~15)屏蔽位的写使能。
           [15:0]：分别为各个物理写通道(16~24)对应中断的屏蔽位，1表示屏蔽。
                  [31:16]：分别为各个物理写通道(16~24)屏蔽位的写使能。

 返 回 值  : 无
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   :
    作    者   : l00246515
    修改内容   : 新生成函数
*****************************************************************************/
OM_BBPMASTER_VOID OM_BbpMasterWrChanGive(OM_BBPMASTER_UINT32 ulPID,
                                             OM_BBPMASTER_UINT32 ulChanId,
                                             BBPMASTER_CHANNEL_DECONFIG_STRU *pstWrChanDeCfg)
{
    if (OM_BBPMASTER_NULL_PTR == pstWrChanDeCfg)
    {
        return;
    }

#if ( VOS_WIN32 != VOS_OS_VER )
    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterWrChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_WR_MODE_OFFSET),
                                                pstWrChanDeCfg->ulWorkMode);

    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterWrChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_WR_CLK_SEL_OFFSET),
                                                pstWrChanDeCfg->ulClockSel);

#if (BBP_MASTER_INT_MODE == FEATURE_ON)
#ifndef CSDR_FEATURE_ON

    /* Mask(0~15) & Mask2(16~23) */
    if (OM_BBP_MASTER_CHAN_REG_WIDTH > ulChanId)
    {
        OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_MASK_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(ulPID),
                            (VOS_UINT32)((VOS_UINT32)(OM_BBPMASTER_MASK_BIT_0 | OM_BBPMASTER_MASK_BIT_16) << ulChanId));
    }
    else
    {
#if (FEATURE_BBP_MASTER_CHAN_U2 == FEATURE_ON)
        OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_MASK2_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(ulPID),
                            (VOS_UINT32)((VOS_UINT32)(OM_BBPMASTER_MASK_BIT_0 | OM_BBPMASTER_MASK_BIT_16) << (ulChanId - OM_BBP_MASTER_CHAN_REG_WIDTH)));
#endif
    }

    g_astOmBbpMasterWrEntity[ulChanId].pfnIntFunc = OM_BBPMASTER_NULL_PTR;
#endif
#endif
#endif
}

/*****************************************************************************
 函 数 名  : OM_BbpMasterWrChanGive
 功能描述  : OM BbpMaster写通道去使能配置，参数使用上层透传形式。
 输入参数  : ulChanId
             pstWrChanDeCfg
 输出参数  : 无

    V7R5: [5:0]：分别为各个物理写通道对应中断的屏蔽位，1表示屏蔽。
                  [11:8]：分别为各个物理读通道对应中断的屏蔽位，1表示屏蔽。
                  [21:16]：分别为各个物理写通道屏蔽位的写使能。
                  [27:24]：分别为各个物理读通道屏蔽位的写使能。

    V8R5: [15:0]：分别为各个物理写通道对应中断的屏蔽位，1表示屏蔽。
              [31:16]：分别为各个物理写通道屏蔽位的写使能。

    K3V6: INT_MASK [15:0]：分别为0~15物理写通道对应中断的屏蔽位，1表示屏蔽。
                       [31:16]：分别为0~15物理写通道屏蔽位的写使能。
             INT_MASK2 [15:0]：分别为0~15物理写通道对应中断的屏蔽位，1表示屏蔽。
                       [31:16]：分别为0~15物理写通道屏蔽位的写使能。
 返 回 值  : 无
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   :
    作    者   : l00246515
    修改内容   : 新生成函数
*****************************************************************************/
OM_BBPMASTER_VOID OM_BbpMasterRdChanTake(OM_BBPMASTER_UINT32 ulPID,
                                             OM_BBPMASTER_UINT32 ulChanId,
                                             BBPMASTER_RD_CHANNEL_CONFIG_STRU *pstRdChanCfg)
{
    if (OM_BBPMASTER_NULL_PTR == pstRdChanCfg)
    {
        return;
    }


#if ( VOS_WIN32 != VOS_OS_VER )
    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterRdChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_RD_MODE_OFFSET),
                                                pstRdChanCfg->ulWorkMode);

    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterRdChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_RD_CLK_SEL_OFFSET),
                                                pstRdChanCfg->ulClockSel);

    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterRdChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_RD_INIT_ADDR_OFFSET),
                                                pstRdChanCfg->ulStartAddr);

    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterRdChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_RD_BURST_BEAT_OFFSET),
                                                pstRdChanCfg->ulBurstLen);

    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterRdChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_RD_AXI_SEL_OFFSET),
                                                pstRdChanCfg->ulAxiSel);

    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterRdChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_RD_INTR_MODE_OFFSET),
                                                pstRdChanCfg->ulIntMode);

    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterRdChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_RD_BIT_WIDTH_IND_OFFSET),
                                                pstRdChanCfg->ulValidLen);

#if (BBP_MASTER_INT_MODE == FEATURE_ON)
#ifndef CSDR_FEATURE_ON
    if (OM_BBPMASTER_IP_V7R5 == g_ulOmBbpMasterChipType)
    {
        OM_BBPMASTER_WRITE_REG((BBPCOMM_BBPMST_INT0_EN_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(I0_DSP_PID_GPHY)), 1);
        OM_BBPMASTER_WRITE_REG((BBPCOMM_BBPMST_INT0_EN_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(I1_DSP_PID_GPHY)), 1);
        OM_BBPMASTER_WRITE_REG((BBPCOMM_BBPMST_INT0_EN_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(DSP_PID_WPHY)), 1);

        OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_MASK_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(ulPID),
                    (VOS_UINT32)((VOS_UINT32)OM_BBPMASTER_MASK_BIT_24 << ulChanId));
    }
    else
    {
#if (FEATURE_BBP_MASTER_CHAN_EXTEND == FEATURE_ON)
        OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_EN_ADDR, 1);
        /*lint -e701*/
        OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_MASK_R_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(ulPID),
                    (OM_BBPMASTER_MASK_BIT_16 << ulChanId));
        /*lint +e701*/
#endif
    }

    g_astOmBbpMasterRdEntity[ulChanId].pfnIntFunc = pstRdChanCfg->pfnIntFunc;
#endif
#endif
#endif
    return;
}

/*****************************************************************************
 函 数 名  : OM_BbpMasterWrChanGive
 功能描述  : OM BbpMaster写通道去使能配置，参数使用上层透传形式。
 输入参数  : ulChanId
             pstWrChanDeCfg
 输出参数  : 无
     V7R5: [5:0]：分别为各个物理写通道对应中断的屏蔽位，1表示屏蔽。
           [11:8]：分别为各个物理读通道对应中断的屏蔽位，1表示屏蔽。
           [21:16]：分别为各个物理写通道屏蔽位的写使能。
           [27:24]：分别为各个物理读通道屏蔽位的写使能。

    V8R5: [15:0]：分别为各个物理写通道对应中断的屏蔽位，1表示屏蔽。
          [31:16]：分别为各个物理写通道屏蔽位的写使能。
 返 回 值  : 无
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   :
    作    者   : l00246515
    修改内容   : 新生成函数
*****************************************************************************/
OM_BBPMASTER_VOID OM_BbpMasterRdChanGive(OM_BBPMASTER_UINT32 ulPID,
                                             OM_BBPMASTER_UINT32 ulChanId,
                                             BBPMASTER_CHANNEL_DECONFIG_STRU *pstRdChanDeCfg)
{
    if (OM_BBPMASTER_NULL_PTR == pstRdChanDeCfg)
    {
        return;
    }

#if ( VOS_WIN32 != VOS_OS_VER )
    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterRdChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_RD_MODE_OFFSET),
                                                pstRdChanDeCfg->ulWorkMode);

    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterRdChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_RD_CLK_SEL_OFFSET),
                                                pstRdChanDeCfg->ulClockSel);

#if (BBP_MASTER_INT_MODE == FEATURE_ON)
#ifndef CSDR_FEATURE_ON
    if (OM_BBPMASTER_IP_V7R5 == g_ulOmBbpMasterChipType)
    {
        OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_MASK_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(ulPID),
                    (VOS_UINT32)((VOS_UINT32)(OM_BBPMASTER_MASK_BIT_24 | OM_BBPMASTER_MASK_BIT_8) << ulChanId));
    }
    else
    {
#if (FEATURE_BBP_MASTER_CHAN_EXTEND == FEATURE_ON)
        /*lint -e701*/
        OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_MASK_R_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(ulPID),
                    ((OM_BBPMASTER_MASK_BIT_16 | OM_BBPMASTER_MASK_BIT_0) << ulChanId));
        /*lint +e701*/
#endif
    }

    g_astOmBbpMasterRdEntity[ulChanId].pfnIntFunc = OM_BBPMASTER_NULL_PTR;
#endif
#endif
#endif
}

/*****************************************************************************
 函 数 名  : OM_BbpMasterWrChannelConfig
 功能描述  : OM BbpMaster写通道使能配置接口
 输入参数  : ulPID,
             ulChanId
             pstWrChanCfg
 输出参数  : 无
 返 回 值  : 配置结果错误码
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   :
    作    者   : l00246515
    修改内容   : 新生成函数
*****************************************************************************/
OM_BBPMASTER_CFG_DECFG_TYPE_ENUM_UINT32 OM_BbpMasterWrChannelConfig(OM_BBPMASTER_UINT32 ulPID,
                                                               OM_BBPMASTER_UINT32 ulChanId,
                                                               BBPMASTER_WR_CHANNEL_CONFIG_STRU *pstWrChanCfg)
{
#if (FEATURE_BBP_MASTER == FEATURE_ON)
    if (OM_BBPMASTER_NULL_PTR == pstWrChanCfg)
    {
        return OM_BBPMASTER_PARA_CFG_NULL;
    }

    if (OM_BBPMASTER_MAX_WR_CHAN_CNT <= ulChanId)
    {
        return OM_BBPMASTER_PARA_CHANID_INVALID;
    }

    g_astOmBbpMasterWrChCallCnt[ulChanId]++;

    if (OM_BBPMASTER_DBG_ON == g_ulOmBbpMasterTest)
    {
        /*lint -e534*/
        LogPrint2("OM_BbpMasterWrChannelConfig PID: %d, Chan Id: %d\n", (int)ulPID, (int)ulChanId);
        /*lint +e534*/
    }

    if (OM_BBPMASTER_YES != OM_BbpMasterWrChanIpcLock(ulChanId))
    {
#ifdef CSDR_FEATURE_ON
        CSDR_MNTN_LogError2(ulPID, ulChanId);
#else
        /*lint -e534*/
        LogPrint2("OM_BbpMasterWrChannelConfig OM_BBPMASTER_LOCK_IPC_FAIL: PID: %d, Chan Id: %d\n",
                (int)ulPID, (int)ulChanId);
        /*lint +e534*/
#endif
        return OM_BBPMASTER_LOCK_IPC_FAIL;
    }

    /* 配置通道成功，更新可谓可测通道信息 */
    OM_BbpMasterWrChanTake(ulPID, ulChanId, pstWrChanCfg);

#else
    /*lint -e534*/
    LogPrint("\r\n OM_BbpMasterWrChannelConfig: no support BbpMaster!!!");
    /*lint +e534*/
#endif

    return OM_BBPMASTER_CONFIG_SUCC;
}

/*****************************************************************************
 函 数 名  : OM_BbpMasterWrChannelDeConfig
 功能描述  : OM BbpMaster写通道去使能配置接口
 输入参数  : ulPID,
             ulChanId
             pstChanDeCfg
 输出参数  : 无
 返 回 值  : 配置结果错误码
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   :
    作    者   : l00246515
    修改内容   : 新生成函数
*****************************************************************************/
OM_BBPMASTER_CFG_DECFG_TYPE_ENUM_UINT32 OM_BbpMasterWrChannelDeConfig(OM_BBPMASTER_UINT32 ulPID,
                                                               OM_BBPMASTER_UINT32 ulChanId,
                                                               BBPMASTER_CHANNEL_DECONFIG_STRU *pstChanDeCfg)
{
#if (FEATURE_BBP_MASTER == FEATURE_ON)
    if (OM_BBPMASTER_NULL_PTR == pstChanDeCfg)
    {
        return OM_BBPMASTER_PARA_CFG_NULL;
    }

    if (OM_BBPMASTER_MAX_WR_CHAN_CNT <= ulChanId)
    {
        return OM_BBPMASTER_PARA_CHANID_INVALID;
    }

    if (OM_BBPMASTER_DBG_ON == g_ulOmBbpMasterTest)
    {
        /*lint -e534*/
        LogPrint2("OM_BbpMasterWrChannelDeConfig PID: %d, Chan Id: %d\n", (int)ulPID, (int)ulChanId);
        /*lint +e534*/
    }

    /* 多余的Unlock不统计 */
    if (0 < g_astOmBbpMasterWrChCallCnt[ulChanId])
    {
        g_astOmBbpMasterWrChCallCnt[ulChanId]--;
    }

    OM_BbpMasterWrChanGive(ulPID, ulChanId, pstChanDeCfg);

    OM_BbpMasterWrChanIpcUnLock(ulChanId);
#else
    /*lint -e534*/
    LogPrint("OM_BbpMasterWrChannelDeConfig: no use now!!!\r\n");
    /*lint +e534*/
#endif

    return OM_BBPMASTER_CONFIG_SUCC;
}

/*****************************************************************************
 函 数 名  : OM_BbpMasterRdChannelConfig
 功能描述  : OM BbpMaster读通道使能配置接口
 输入参数  : ulPID,
             ulChanId
             pstRdChanCfg
 输出参数  : 无
 返 回 值  : 配置结果错误码
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   :
    作    者   : l00246515
    修改内容   : 新生成函数
*****************************************************************************/
OM_BBPMASTER_CFG_DECFG_TYPE_ENUM_UINT32 OM_BbpMasterRdChannelConfig(OM_BBPMASTER_UINT32 ulPID,
                                                               OM_BBPMASTER_UINT32 ulChanId,
                                                               BBPMASTER_RD_CHANNEL_CONFIG_STRU *pstRdChanCfg)
{
#if (FEATURE_BBP_MASTER == FEATURE_ON)
    if (OM_BBPMASTER_NULL_PTR == pstRdChanCfg)
    {
        return OM_BBPMASTER_PARA_CFG_NULL;
    }

    if (OM_BBPMASTER_MAX_RD_CHAN_CNT <= ulChanId)
    {
        return OM_BBPMASTER_PARA_CHANID_INVALID;
    }

    g_astOmBbpMasterRdChCallCnt[ulChanId]++;

    if (OM_BBPMASTER_DBG_ON == g_ulOmBbpMasterTest)
    {
        /*lint -e534*/
        LogPrint2("OM_BbpMasterRdChannelConfig PID: %d, Chan Id: %d\n", (int)ulPID, (int)ulChanId);
        /*lint +e534*/
    }

    if (OM_BBPMASTER_YES != OM_BbpMasterRdChanIpcLock(ulChanId))
    {
#ifdef CSDR_FEATURE_ON
        CSDR_MNTN_LogError2(ulPID, ulChanId);
#else
        /*lint -e534*/
        LogPrint2("OM_BbpMasterRdChannelConfig OM_BBPMASTER_LOCK_IPC_FAIL: PID: %d, Chan Id: %d\n",
                (int)ulPID, (int)ulChanId);
        /*lint +e534*/
#endif
        return OM_BBPMASTER_LOCK_IPC_FAIL;
    }

    /* 配置通道成功，更新可维可测通道信息 */
    OM_BbpMasterRdChanTake(ulPID, ulChanId, pstRdChanCfg);
#else
    /*lint -e534*/
    LogPrint("OM_BbpMasterRdChannelConfig: no use now!!!\r\n");
    /*lint +e534*/
#endif

    return OM_BBPMASTER_CONFIG_SUCC;
}

/*****************************************************************************
 函 数 名  : OM_BbpMasterRdChannelDeConfig
 功能描述  : OM BbpMaster读通道去使能配置接口
 输入参数  : ulPID,
             ulChanId
             pstChanDeCfg
 输出参数  : 无
 返 回 值  : 配置结果错误码
 调用函数  :
 被调函数  :

  修改历史      :
  1.日    期   :
    作    者   : l00246515
    修改内容   : 新生成函数
*****************************************************************************/
OM_BBPMASTER_CFG_DECFG_TYPE_ENUM_UINT32 OM_BbpMasterRdChannelDeConfig(OM_BBPMASTER_UINT32 ulPID,
                                                               OM_BBPMASTER_UINT32 ulChanId,
                                                               BBPMASTER_CHANNEL_DECONFIG_STRU *pstChanDeCfg)
{
#if (FEATURE_BBP_MASTER == FEATURE_ON)
    if (OM_BBPMASTER_NULL_PTR == pstChanDeCfg)
    {
        return OM_BBPMASTER_PARA_CFG_NULL;
    }

    if (OM_BBPMASTER_MAX_RD_CHAN_CNT <= ulChanId)
    {
        return OM_BBPMASTER_PARA_CHANID_INVALID;
    }

    if (OM_BBPMASTER_DBG_ON == g_ulOmBbpMasterTest)
    {
        /*lint -e534*/
        LogPrint2("OM_BbpMasterRdChannelDeConfig PID: %d, Chan Id: %d\n", (int)ulPID, (int)ulChanId);
        /*lint +e534*/
    }

    /* 多余的Unlock不统计 */
    if (0 < g_astOmBbpMasterRdChCallCnt[ulChanId])
    {
        g_astOmBbpMasterRdChCallCnt[ulChanId]--;
    }

    OM_BbpMasterRdChanGive(ulPID, ulChanId, pstChanDeCfg);

    OM_BbpMasterRdChanIpcUnLock(ulChanId);
#else
    /*lint -e534*/
    LogPrint("OM_BbpMasterRdChannelDeConfig: no use now!!!\r\n");
    /*lint +e534*/
#endif

    return OM_BBPMASTER_CONFIG_SUCC;
}

OM_BBPMASTER_VOID OM_BbpMasterChannelInfoShow(OM_BBPMASTER_VOID)
{
#ifndef CSDR_FEATURE_ON
    OM_BBPMASTER_UINT32 i;

    /*lint -e534*/
    for (i = 0; i < OM_BBPMASTER_MAX_WR_CHAN_CNT; i++)
    {
        LogPrint3("OM_BbpMaster Wr Channel %d Call Count: %d, IPC Count: %d\n", (int)i, (int)g_astOmBbpMasterWrChCallCnt[i], (int)g_astOmBbpMasterWrChIpcCnt[i]);
    }

    for (i = 0; i < OM_BBPMASTER_MAX_RD_CHAN_CNT; i++)
    {
        LogPrint3("OM_BbpMaster Rd Channel %d Call Count: %d, IPC Count: %d\n", (int)i, (int)g_astOmBbpMasterRdChCallCnt[i], (int)g_astOmBbpMasterRdChIpcCnt[i]);
    }
    /*lint +e534*/
#endif
    return;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
