/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMsccFsmBsrTbl.h
  版 本 号   : 初稿
  作    者   : y00307564
  生成日期   : 2015年04月02日
  最近修改   :
  功能描述   : NasMsccFsmBsrTbl.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年04月02日
    作    者   : y00307564
    修改内容   : 创建文件

******************************************************************************/

#ifndef __NAS_MSCC_FSM_BSR_TBL_H__
#define __NAS_MSCC_FSM_BSR_TBL_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "NasFsm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量声明
*****************************************************************************/
extern NAS_STA_STRU                                         g_astNasMsccBsrStaTbl[];

/*****************************************************************************
  3 宏定义
*****************************************************************************/
#define NAS_MSCC_GetBsrStaTbl()                             (g_astNasMsccBsrStaTbl)


/*****************************************************************************
  4 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : NAS_MSCC_BSR_STA_ENUM
 枚举说明  : BSR状态机ID枚举定义
 1.日    期   : 2015年04月02日
   作    者   : y00307564
   修改内容   : 新建
*****************************************************************************/
enum NAS_MSCC_BSR_STA_ENUM
{
    NAS_MSCC_BSR_STA_INIT                                     = 0x00,

    NAS_MSCC_BSR_STA_WAIT_HSD_BG_SEARCH_CNF,

    NAS_MSCC_BSR_STA_WAIT_HSD_STOP_BG_SEARCH_CNF,

    NAS_MSCC_BSR_STA_WAIT_MMC_QRY_PLMN_PRI_CLASS_CNF,

    NAS_MSCC_BSR_STA_WAIT_HSD_POWER_SAVE_CNF,

    NAS_MSCC_BSR_STA_WAIT_MMC_PLMN_SEARCH_CNF,

    NAS_MSCC_BSR_STA_WAIT_MMC_POWER_SAVE_CNF_REACQ_HRPD,

    NAS_MSCC_BSR_STA_WAIT_HSD_SYSTEM_ACQUIRE_CNF_REACQ_HRPD,

    NAS_MSCC_BSR_STA_WAIT_MMC_BG_SEARCH_CNF,

    NAS_MSCC_BSR_STA_WAIT_MMC_STOP_BG_SEARCH_CNF,

    NAS_MSCC_BSR_STA_WAIT_HSD_QRY_HRPD_SYS_INFO_CNF,

    NAS_MSCC_BSR_STA_WAIT_MMC_POWER_SAVE_CNF,

    NAS_MSCC_BSR_STA_WAIT_HSD_SYSTEM_ACQUIRE_CNF,

    NAS_MSCC_BSR_STA_WAIT_HSD_POWER_SAVE_CNF_REACQ_LTE,

    NAS_MSCC_BSR_STA_WAIT_MMC_PLMN_SEARCH_CNF_REACQ_LTE,

    NAS_MSCC_BSR_STA_BUTT
};
typedef VOS_UINT32 NAS_MSCC_BSR_STA_ENUM_UINT32;


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_UINT32 NAS_MSCC_GetBsrStaTblSize(VOS_VOID);

NAS_FSM_DESC_STRU *NAS_MSCC_GetBsrFsmDescAddr(VOS_VOID);

#endif /***********end of FEATURE_UE_MODE_CDMA*******************/

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasMsccFsmMainTbl.h */

