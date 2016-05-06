/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcFsmInterSysCcoTbl.h
  版 本 号   : 初稿
  作    者   : W00176964
  生成日期   : 2011年07月04日
  最近修改   :
  功能描述   : NasMmcFsmInterSysCcoTbl.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年07月04日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/
#ifndef _NAS_MMC_FSM_INTER_SYS_CCO_TBL_H_
#define _NAS_MMC_FSM_INTER_SYS_CCO_TBL_H_

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
extern NAS_STA_STRU                                     g_astNasMmcInterSysCcoStaTbl[];


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define NAS_MMC_GetInterSysCcoStaTbl()                          (g_astNasMmcInterSysCcoStaTbl)


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : NAS_MMC_INTER_SYS_CCO_STA_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 状态机InterSysCco的状态枚举定义
*****************************************************************************/
enum NAS_MMC_INTER_SYS_CCO_STA_ENUM
{
    /*Cell change order状态机初始化状态*/
    NAS_MMC_INTER_SYS_CCO_STA_INIT                                          =0,

    /*Cell change order过程 等待MM挂起回复*/
    NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP                           =1,

    /*Cell change order状态机 等待接入层的恢复指示*/
    NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_RESUME_IND                            =2,

    /*Cell change order状态机 等待MM恢复回复*/
    NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP                            =3,

    /*Cell change order状态机 等待WAS系统消息*/
    NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND                          =4,

    /*Cell change order状态机 等待GAS系统消息*/
    NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND                          =5,

#if (FEATURE_ON == FEATURE_LTE)
    /*Cell change order状态机 等待L系统消息*/
    NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND                          =6,
#endif

    /*Cell change order状态机 等待建链结果*/
    NAS_MMC_INTER_SYS_CCO_STA_WAIT_EST_IND                                  =7,

    /*Cell change order状态机 等待回退时接入层的挂起指示*/
    NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_SUSPEND_IND_FALLBACK                  =8,

    /*Cell change order状态机 等待回退时MM的挂起回复*/
    NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP_FALLBACK                  =9,

    /*Cell change order状态机 等待回退时接入层的恢复指示*/
    NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_RESUME_IND_FALLBACK                   =10,

    /*Cell change order状态机 等待回退时MM的恢复回复*/
    NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP_FALLBACK                   =11,

    /*Cell change order状态机 等待回退时WAS系统消息*/
    NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND_FALLBACK                 =12,

    /*Cell change order状态机 等待回退时GAS系统消息*/
    NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND_FALLBACK                 =13,

#if (FEATURE_ON == FEATURE_LTE)
    /*Cell change order状态机 等待回退时L系统消息*/
    NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND_FALLBACK                 =14,
#endif

    NAS_MMC_INTER_SYS_CCO_STA_BUTT
};

typedef VOS_UINT32  NAS_MMC_INTER_SYS_CCO_STA_ENUM_UINT32;


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
VOS_UINT32 NAS_MMC_GetInterSysCcoStaTblSize( VOS_VOID  );

NAS_FSM_DESC_STRU * NAS_MMC_GetInterSysCcoFsmDescAddr(VOS_VOID);

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

#endif /* end of NasMmcInterSysCcoFsmTbl.h */



