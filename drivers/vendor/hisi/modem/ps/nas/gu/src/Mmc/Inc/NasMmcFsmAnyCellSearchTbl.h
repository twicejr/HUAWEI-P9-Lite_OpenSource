/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcFsmAnyCellSearchTbl.h
  版 本 号   : 初稿
  作    者   : likelai /l00130025
  生成日期   : 2011年07月19日
  最近修改   :
  功能描述   : NasMmcFsmAnyCellSearchTbl.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年07月19日
    作    者   : likelai /00130025
    修改内容   : Added for V7R1 phase II

******************************************************************************/
#ifndef _NAS_MMC_FSM_ANYCELL_SEARCH_TBL_H_
#define _NAS_MMC_FSM_ANYCELL_SEARCH_TBL_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "NasFsm.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  1 全局变量定义
*****************************************************************************/
extern NAS_STA_STRU                                   g_astNasMmcAnyCellSearchStaTbl[];


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define NAS_MMC_GetAnyCellSearchStaTbl()              (g_astNasMmcAnyCellSearchStaTbl)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : NAS_MMC_ANYCELL_SEARCH_STA_ENUM
 枚举说明  : 状态机AnycellPlmnSearch的状态枚举定义
 修改历史   :
 1.日    期   : 2011年12月2日
   作    者   : w00167002
   修改内容   : DTS2011112804719:anycel成功后没有发SUITABLECELL给接入层
                 修改方案:在ANYCELL状态机增加等待系统消息的状态，若收到了
                 接入层上报的系统消息，且当前网路为可用网络，则通知接入层
                 重选类型为RESEL_SUITABLE。
*****************************************************************************/
enum NAS_MMC_ANYCELL_SEARCH_STA_ENUM
{
    NAS_MMC_ANYCELL_SEARCH_STA_INIT                                             = 0,

    /* 等待W模上报搜网结果 */
    NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_PLMN_SEARCH_CNF                         = 1,

    /* 等待G模上报搜网结果 */
    NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_PLMN_SEARCH_CNF                         = 2,

    /* 等待L模上报搜网结果 */
    NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_PLMN_SEARCH_CNF                         = 3,

    /* 等待W模上报挂起结果 */
    NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_SUSPEND_CNF                             = 4,

    /* 等待G模上报挂起结果 */
    NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_SUSPEND_CNF                             = 5,

    /* 等待L模上报挂起结果 */
    NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_SUSPEND_CNF                             = 6,

    /* 等待W模上报停止搜网结果 */
    NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_PLMN_STOP_CNF                           = 7,

    /* 等待G模上报停止搜网结果 */
    NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_PLMN_STOP_CNF                           = 8,

    /* 等待L模上报停止搜网结果 */
    NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_PLMN_STOP_CNF                           = 9,


    /* ANYCELL搜网成功后等待W模上报系统消息 */
    NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_SYSINFO_IND                             = 10,

    /* ANYCELL搜网成功后等待G模上报系统消息 */
    NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_SYSINFO_IND                             = 11,

    /* ANYCELL搜网成功后等待L模上报系统消息 */
    NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_SYSINFO_IND                             = 12,
    
    NAS_MMC_ANYCELL_SEARCH_STA_BUTT

};
typedef VOS_UINT32  NAS_MMC_ANYCELL_SEARCH_STA_ENUM_UINT32;



/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


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
VOS_UINT32 NAS_MMC_GetAnyCellSearchStaTblSize(VOS_VOID);

NAS_FSM_DESC_STRU * NAS_MMC_GetAnyCellSearchFsmDescAddr(VOS_VOID);


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

#endif /* end of NasMmcFsmAnyCellSearchTbl.h */
