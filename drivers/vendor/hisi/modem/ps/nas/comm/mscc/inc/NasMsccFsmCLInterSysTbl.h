/******************************************************************************

            Copyright 2014, Huawei Technologies Co. Ltd.

 ******************************************************************************
File Name       :   NasMsccFsmCLInterSysTbl.h
Author          :   w00176964
Version         :
Date            :   2015-11-5
Description     :   CL intersys状态机相关的状态定义头文件
Function list   :
History         :
    1) Date :
       Author:
       Modification:
******************************************************************************/


#ifndef _NAS_MSCC_FSM_CL_INTERSYS_TBL_H_
#define _NAS_MSCC_FSM_CL_INTERSYS_TBL_H_

/*****************************************************************************
  1 Inclusing header files
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

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE))

/*****************************************************************************
  1 Global Variales
*****************************************************************************/

extern NAS_STA_STRU                            g_astNasMsccCLInterSysStaTbl[];


/*****************************************************************************
  2 Macro Definitions
*****************************************************************************/
#define NAS_MSCC_GetCLInterSysStaTbl()                   (g_astNasMsccCLInterSysStaTbl)



/*****************************************************************************
  3 Enumerations
*****************************************************************************/


enum NAS_MSCC_CL_INTERSYS_STA_ENUM
{

    NAS_MSCC_CL_INTERSYS_STA_INIT                         = 0x00,

    NAS_MSCC_CL_INTERSYS_STA_WAIT_MMC_POWER_SAVE_CNF,              /* 等待MMC模块的power save 确认 */

    NAS_MSCC_CL_INTERSYS_STA_WAIT_INTERSYS_END_IND,                /* 等待MMC模块或HSD模块的异系统结束指示 */

    NAS_MSCC_CL_INTERSYS_STA_BUTT
};
typedef VOS_UINT32  NAS_MSCC_CL_INTERSYS_STA_ENUM_UINT32;

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
  10 Function declarations
*****************************************************************************/
VOS_UINT32 NAS_MSCC_GetCLInterSysStaTblSize(VOS_VOID);

NAS_FSM_DESC_STRU * NAS_MSCC_GetCLInterSysFsmDescAddr(VOS_VOID);

#endif

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

#endif /* end of NasMsccFsmInterSysTbl.h */


