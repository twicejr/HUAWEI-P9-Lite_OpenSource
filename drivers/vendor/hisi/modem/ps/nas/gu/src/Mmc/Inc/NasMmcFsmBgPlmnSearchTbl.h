/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcFsmBgPlmnSearchTbl.h
  版 本 号   : 初稿
  作    者   : z00161729
  生成日期   : 2011年09月08日
  最近修改   :
  功能描述   : NasMmcFsmBgPlmnSearchTbl.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年09月08日
    作    者   : z00161729
    修改内容   : Added for V7R1 phase II

******************************************************************************/
#ifndef _NAS_MMC_FSM_BG_PLMN_SEARCH_TBL_H_
#define _NAS_MMC_FSM_BG_PLMN_SEARCH_TBL_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#include  "vos.h"
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
extern NAS_STA_STRU                                         g_astNasMmcFsmBgPlmnSearchStaTbl[];

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define NAS_MMC_GetBgPlmnSearchStaTbl()                     (g_astNasMmcFsmBgPlmnSearchStaTbl)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : NAS_MMC_BG_PLMN_SEARCH_STA_ENUM
 枚举说明  : 状态机BG PLMN SEARCH的状态枚举定义
 1.日    期   : 2011年09月04日
   作    者   : z00161729
   修改内容   : Added for V7R1 phase II
*****************************************************************************/
enum NAS_MMC_BG_PLMN_SEARCH_STA_ENUM
{
    /* 高优先级搜网状态机等待消息状态 */
    NAS_MMC_BG_PLMN_SEARCH_STA_INIT                                  =0,

    /*  等待W模上报BG搜网结果 */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_BG_PLMN_SEARCH_CNF           =1,

    /*  等待G模上报BG搜网结果 */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_BG_PLMN_SEARCH_CNF           =2,

    /*  等待W模上报挂起结果 */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_SUSPEND_CNF                  =3,

    /*  等待G模上报挂起结果 */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_SUSPEND_CNF                  =4,

    /*  等待W模上报停止BG搜网结果 */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_BG_PLMN_STOP_CNF             =5,

    /*  等待G模上报停止BG搜网结果 */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_BG_PLMN_STOP_CNF             =6,

    /*  等待W模上报停止快速指定搜网结果 */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_FAST_PLMN_STOP_CNF           =7,

    /*  等待G模上报停止快速指定搜网结果 */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_FAST_PLMN_STOP_CNF           =8,

    /*  等待W模上报快速指定搜网结果 */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_PLMN_FAST_SEARCH_CNF         =9,

    /*  等待G模上报快速指定搜网结果 */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_PLMN_FAST_SEARCH_CNF         =10,

    /*  等待W模上报系统消息*/
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_SYSINFO_IND                  =11,

    /*  等待G模上报系统消息*/
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_SYSINFO_IND                  =12,

    /*  等待CS+PS域的注册结果*/
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_CSPS_REG_IND                     =13,

    /*  等待GU链接释放 */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_RRC_CONN_REL_IND                 =14,

    /*  回VPLMN时等待W模上报挂起结果 */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_SUSPEND_CNF_RECAMP_VPLMN     =15,

    /*  回VPLMN时等待G模上报挂起结果 */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_SUSPEND_CNF_RECAMP_VPLMN     =16,

    /*  回VPLMN时等待W模上报指定搜网结果 */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_PLMN_SEARCH_CNF_RECAMP_VPLMN =17,

    /*  回VPLMN时等待G模上报指定搜网结果 */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_PLMN_SEARCH_CNF_RECAMP_VPLMN =18,

    /*  回VPLMN时等待W模上报停止指定搜网结果 */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_PLMN_STOP_CNF_RECAMP_VPLMN   =19,

    /*  回VPLMN时等待G模上报停止指定搜网结果 */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_PLMN_STOP_CNF_RECAMP_VPLMN   =20,

    /*  回VPLMN时等待W模上报系统消息*/
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_SYSINFO_IND_RECAMP_VPLMN     =21,

    /*  回VPLMN时等待G模上报系统消息*/
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_SYSINFO_IND_RECAMP_VPLMN     =22,

    /* 等待L模上报挂起结果 */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_SUSPEND_CNF                  =23,

    /* 等待L模上报系统消息结果 */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_SYSINFO_IND                  =24,

    /* 等待eps注册结果 */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_REG_IND                      =25,

    /* 等待L模链接释放结果 */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_CONN_REL_IND                 =26,

    /* 回VPLMN时等待L模上报搜网结果 */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_PLMN_SEARCH_CNF_RECAMP_VPLMN =27,

    /* 回VPLMN时等待L模上报挂起结果 */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_SUSPEND_CNF_RECAMP_VPLMN     =28,

    /* 回VPLMN时等待L模上报停止搜网结果 */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_PLMN_STOP_CNF_RECAMP_VPLMN   =29,

    /* 回VPLMN时等待L模上报系统消息结果 */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_SYSINFO_IND_RECAMP_VPLMN     =30,

    /* 等待L模上报BG搜网结果 */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_BG_PLMN_SEARCH_CNF           =31,

    /*  等待L模上报停止BG搜网结果 */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_BG_PLMN_STOP_CNF             =32,

    /*  等待L模上报快速指定搜网结果 */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_PLMN_FAST_SEARCH_CNF         =33,

    /*  等待L模上报停止快速指定搜网结果 */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_FAST_PLMN_STOP_CNF           =34,

    NAS_MMC_BG_PLMN_SEARCH_STA_BUTT
};
typedef VOS_UINT32  NAS_MMC_BG_PLMN_SEARCH_STA_ENUM_U32;


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
VOS_UINT32 NAS_MMC_GetBgPlmnSearchStaTblSize(VOS_VOID);

NAS_FSM_DESC_STRU * NAS_MMC_GetBgPlmnSearchFsmDescAddr(VOS_VOID);


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

#endif
