/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcFsmInterSysCellReselTbl.h
  版 本 号   : 初稿
  作    者   : W00176964
  生成日期   : 2011年07月04日
  最近修改   :
  功能描述   : NasMmcFsmInterSysCellReselTbl.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年07月04日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/
#ifndef _NAS_MMC_FSM_INTER_SYS_CELLRESEL_TBL_H_
#define _NAS_MMC_FSM_INTER_SYS_CELLRESEL_TBL_H_

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
extern NAS_STA_STRU                            g_astNasMmcInterSysCellReselStaTbl[];



/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define NAS_MMC_GetInterSysCellReselStaTbl()                      (g_astNasMmcInterSysCellReselStaTbl)



/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : NAS_MMC_INTER_SYS_CELLRESEL_STA_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 状态机InterSysCellResel的状态枚举定义
*****************************************************************************/
enum NAS_MMC_INTER_SYS_CELLRESEL_STA_ENUM
{
    /* 接入层发起的异系统重选过程中的初始化状态*/
    NAS_MMC_INTER_SYS_CELLRESEL_STA_INIT                                     =0,

    /* 接入层发起的异系统重选过程中等待MM的挂起 */
    NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_SUSPEND_RSP                      =1,

    /* 接入层发起的异系统重选过程中等待接入层的恢复 */
    NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND                       =2,

    /* 接入层发起的异系统重选过程中等待MM的恢复 */
    NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP                       =3,

    /* 接入层发起的异系统重选过程中等待WAS系统消息 */
    NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND                     =4,

    /* 接入层发起的异系统重选过程中等待GAS系统消息 */
    NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SYSINFO_IND                     =5,

#if (FEATURE_ON == FEATURE_LTE)
    /* 接入层发起的异系统重选过程中等待L系统消息 */
    NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SYSINFO_IND                     =6,
    NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SUSPEND_REL_CNF                 =7,
#endif

    NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SUSPEND_REL_CNF                 =8,

    NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SUSPEND_REL_CNF                 =9,

    NAS_MMC_INTER_SYS_CELLRESEL_BUTT
};

typedef VOS_UINT32  NAS_MMC_INTER_SYS_CELLRESEL_STA_ENUM_UINT32;


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
VOS_UINT32 NAS_MMC_GetInterSysCellReselStaTblSize( VOS_VOID  );

NAS_FSM_DESC_STRU * NAS_MMC_GetInterSysCellReselFsmDescAddr(VOS_VOID);



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

#endif /* end of NasMmcInterSysCellReselFsmTbl.h */




