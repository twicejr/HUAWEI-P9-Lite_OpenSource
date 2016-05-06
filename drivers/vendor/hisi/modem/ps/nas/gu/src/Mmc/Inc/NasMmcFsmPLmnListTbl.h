/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasFsmPlmnListTbl.h
  版 本 号   : 初稿
  作    者   : W00176964
  生成日期   : 2011年07月04日
  最近修改   :
  功能描述   : plmn list状态机状态转移表
  函数列表   :
  修改历史   :
  1.日    期   : 2011年07月04日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/
#ifndef _NAS_MMC_FSM_PLMN_LIST_TBL_H_
#define _NAS_MMC_FSM_PLMN_LIST_TBL_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#include  "vos.h"
#include  "PsTypeDef.h"
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
extern NAS_STA_STRU                                     g_astNasMmcPlmnListStaTbl[];

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define NAS_MMC_GetPlmnListStaTbl()                     (g_astNasMmcPlmnListStaTbl)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : NAS_MMC_PLMN_LIST_STA_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 列表搜网状态机状态枚举定义
*****************************************************************************/
enum NAS_MMC_PLMN_LIST_STA_ENUM
{
    /*Plmn List状态机初始化状态*/
    NAS_MMC_PLMN_LIST_STA_INIT                             =0,

    /*Plmn List状态机 等待RRC链路释放*/
    NAS_MMC_PLMN_LIST_STA_WAIT_RRC_CONN_REL_IND            =1,

    /*Plmn List状态机 等待WAS的系统消息 */
    NAS_MMC_PLMN_LIST_STA_WAIT_WAS_SYS_INFO_IND            =2,

    /*Plmn List状态机 等待GAS的系统消息 */
    NAS_MMC_PLMN_LIST_STA_WAIT_GAS_SYS_INFO_IND            =3,

    /*Plmn List状态机 等待CS/SP的注册结果 */
    NAS_MMC_PLMN_LIST_STA_WAIT_CSPS_REG_IND                =4,

    /*Plmn List状态机,等待WAS搜网结果*/
    NAS_MMC_PLMN_LIST_STA_WAIT_WAS_PLMN_SEARCH_CNF         =5,

    /*Plmn List状态机,等待GAS搜网结果*/
    NAS_MMC_PLMN_LIST_STA_WAIT_GAS_PLMN_SEARCH_CNF         =6,

    /*Plmn List状态机,等待WAS挂起回复*/
    NAS_MMC_PLMN_LIST_STA_WAIT_WAS_SUSPEND_CNF             =7,

    /*Plmn List状态机,等待GAS挂起回复*/
    NAS_MMC_PLMN_LIST_STA_WAIT_GAS_SUSPEND_CNF             =8,

    /*Plmn List状态机,等待WAS停止搜网回复*/
    NAS_MMC_PLMN_LIST_STA_WAIT_WAS_PLMN_SEARCH_STOP_CNF    =9,

    /*Plmn List状态机,等待GAS停止搜网回复*/
    NAS_MMC_PLMN_LIST_STA_WAIT_GAS_PLMN_SEARCH_STOP_CNF    =10,

#if (FEATURE_ON == FEATURE_LTE)

    /*Plmn List状态机 等待EPS链路释放*/
    NAS_MMC_PLMN_LIST_STA_WAIT_EPS_CONN_REL_IND            =11,

    /* plmn list状态机等待EPS注册结果*/
    NAS_MMC_PLMN_LIST_STA_WAIT_EPS_REG_IND                 =12, 
    
    /*Plmn List状态机 等待LMM搜网结果 */
    NAS_MMC_PLMN_LIST_STA_WAIT_LMM_PLMN_SEARCH_CNF         =13,

    /*Plmn List状态机 等待LMM挂起回复*/
    NAS_MMC_PLMN_LIST_STA_WAIT_LMM_SUSPEND_CNF             =14,

    /*Plmn List状态机 等待LMM停止搜网回复 */
    NAS_MMC_PLMN_LIST_STA_WAIT_LMM_PLMN_SEARCH_STOP_CNF    =15,

#endif

#if (FEATURE_ON == FEATURE_CSG)
    /* CSG Plmn List状态机，等待LMM CSG 列表搜网回复 */
    NAS_MMC_CSG_LIST_STA_WAIT_LMM_CSG_LIST_SEARCH_CNF       =16,

    /* CSG Plmn List状态机 等待LMM停止CSG List搜网停止回复 */
    NAS_MMC_CSG_LIST_STA_WAIT_LMM_CSG_LIST_SEARCH_STOP_CNF  =17,

    /* CSG Plmn List状态机,等待WAS CSG LIST搜网结果*/
    NAS_MMC_CSG_LIST_STA_WAIT_WAS_CSG_LIST_SEARCH_CNF       =18,

    /* CSG Plmn List状态机,等待GAS CSG LIST搜网结果*/
    NAS_MMC_CSG_LIST_STA_WAIT_GAS_CSG_LIST_SEARCH_CNF       =19,

    /* CSG Plmn List状态机,等待WAS挂起回复*/
    NAS_MMC_CSG_LIST_STA_WAIT_WAS_SUSPEND_CNF               =20,

    /* CSG Plmn List状态机,等待GAS挂起回复*/
    NAS_MMC_CSG_LIST_STA_WAIT_GAS_SUSPEND_CNF               =21,

    /* CSG Plmn List状态机,等待WAS停止CSG LIST搜网回复*/
    NAS_MMC_CSG_LIST_STA_WAIT_WAS_CSG_LIST_SEARCH_STOP_CNF  =22,

    /* CSG Plmn List状态机,等待GAS停止CSG LIST搜网回复*/
    NAS_MMC_CSG_LIST_STA_WAIT_GAS_CSG_LIST_SEARCH_STOP_CNF  =23,
#endif

   NAS_MMC_PLMN_LIST_STA_BUTT
};

typedef VOS_UINT32  NAS_MMC_PLMN_LIST_STA_ENUM_UINT32;


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
VOS_UINT32 NAS_MMC_GetPlmnListStaTblSize( VOS_VOID  );

NAS_FSM_DESC_STRU * NAS_MMC_GetPlmnListFsmDescAddr(VOS_VOID);


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

#endif /* end of NasMmcPlmnListFsmTbl.h */

