/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcFsmPLmnSelectionTbl.h
  版 本 号   : 初稿
  作    者   : sunxibo /46746
  生成日期   : 2011年07月04日
  最近修改   :
  功能描述   : NasMmcFsmPLmnSelectionTbl.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年07月04日
    作    者   : sunxibo /46746
    修改内容   : Added for V7R1 phase II

******************************************************************************/
#ifndef _NAS_MMC_FSM_PLMN_SELECTION_TBL_H_
#define _NAS_MMC_FSM_PLMN_SELECTION_TBL_H_

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
extern NAS_STA_STRU                                         g_astNasMmcPlmnSelectionStaTbl[];

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define NAS_MMC_GetPlmnSelectionStaTbl()                    (g_astNasMmcPlmnSelectionStaTbl)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : NAS_MMC_PLMN_SELECTION_STA_ENUM
 枚举说明  : 状态机PLMN SELECTION的状态枚举定义
 1.日    期   : 2011年07月04日
   作    者   : sunxibo /46746
   修改内容   : Added for V7R1 phase II
 2.日    期   : 2012年05月28日
   作    者   : sunxibo /46746
   修改内容   : Added for V7R1 C50 CS/PS mode 1
 3.日    期   : 2014年1月28日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加获取和注册请求的处理
*****************************************************************************/
enum NAS_MMC_PLMN_SELECTION_STA_ENUM
{
    /* 自动搜网状态机等待消息状态 */
    NAS_MMC_PLMN_SELECTION_STA_INIT                         =0,

    /*  等待W模上报搜网结果 */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_PLMN_SEARCH_CNF     =1,

    /*  等待G模上报搜网结果 */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_PLMN_SEARCH_CNF     =2,

    /*  等待L模上报搜网结果 */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF     =3,

    /*  等待W模上报挂起结果 */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF         =4,

    /*  等待G模上报挂起结果 */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SUSPEND_CNF         =5,

    /*  等待L模上报挂起结果 */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SUSPEND_CNF         =6,

    /*  等待W模上报停止搜网结果 */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF       =7,

    /*  等待G模上报停止搜网结果 */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_PLMN_STOP_CNF       =8,

    /*  等待L模上报停止搜网结果 */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_STOP_CNF       =9,

    /*  等待W模上报系统消息*/
    NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SYSINFO_IND         =10,

    /*  等待G模上报系统消息*/
    NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SYSINFO_IND         =11,

    /*  等待L模上报系统消息*/
    NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SYSINFO_IND         =12,

    /*  等待CS+PS域的注册结果*/
    NAS_MMC_PLMN_SELECTION_STA_WAIT_CSPS_REG_IND            =13,

    /*  等待EPS域的注册结果 */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND             =14,

    /*  等待GU链接释放 */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_RRC_CONN_REL_IND        =15,

    /*  等待EPS域的链接释放结果 */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_CONN_REL_IND        =16,


    /*  CS/PS mode 1重回L模等待W模上报挂起结果 */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_CSPSMODE1_RECAMP_LTE        =17,

    /*  CS/PS mode 1重回L模等待G模上报挂起结果 */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SUSPEND_CNF_CSPSMODE1_RECAMP_LTE        =18,

    /*  CS/PS mode 1重回L模等待L模上报搜网结果 */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF_CSPSMODE1_RECAMP_LTE    =19,

    /*  CS/PS mode 1重回L模等待L模上报停止搜网结果 */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_STOP_CNF_CSPSMODE1_RECAMP_LTE      =20,

    /*  CS/PS mode 1重回L模等待L模上报系统消息 */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SYSINFO_IND_CSPSMODE1_RECAMP_LTE        =21,

    /*  CS/PS mode 1重回L模等待EPS域的注册结果 */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND_CSPSMODE1_RECAMP_LTE            =22,

    /*  CS/PS mode 1重回L模等待EPS连接释放 */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REL_IND_CSPSMODE1_RECAMP_LTE            =23,

    /* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
    /*  等待MSCC的注册请求 */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_MSCC_REG_REQ                                 =24,
    /* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

    NAS_MMC_PLMN_SELECTION_STA_BUTT
};
typedef VOS_UINT32  NAS_MMC_PLMN_SELECTION_STA_ENUM_U32;


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
VOS_UINT32 NAS_MMC_GetPlmnSelectionStaTblSize(VOS_VOID);

NAS_FSM_DESC_STRU * NAS_MMC_GetPlmnSelectionFsmDescAddr(VOS_VOID);


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

#endif /* end of NasMmcFsmPLmnSelectionTbl.h */
