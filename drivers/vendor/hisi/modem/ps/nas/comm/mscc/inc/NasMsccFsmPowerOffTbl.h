/******************************************************************************

            Copyright 2014, Huawei Technologies Co. Ltd.

 ******************************************************************************
File Name       :   NasMsccFsmPowerOffTbl.h
Author          :   k902809
Version         :
Date            :   2015-01-31
Description     :   Contains interfaces to interact with MSCC Power-off FSM.
Function list   :
History         :
    1) Date :
       Author:
       Modification:
******************************************************************************/


#ifndef _NAS_MSCC_FSM_POWER_OFF_TBL_H_
#define _NAS_MSCC_FSM_POWER_OFF_TBL_H_

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

/*****************************************************************************
  1 Global Variales
*****************************************************************************/

extern NAS_STA_STRU                            g_astNasMsccPowerOffStaTbl[];


/*****************************************************************************
  2 Macro Definitions
*****************************************************************************/
#define NAS_MSCC_GetPowerOffStaTbl()                   (g_astNasMsccPowerOffStaTbl)



/*****************************************************************************
  3 Enumerations
*****************************************************************************/


enum NAS_MSCC_POWER_OFF_STA_ENUM
{

    NAS_MSCC_POWER_OFF_STA_INIT                         = 0x00,

    NAS_MSCC_POWER_OFF_STA_WAIT_MMC_POWER_OFF_CNF,

#if (FEATURE_IMS == FEATURE_ON)

    NAS_MSCC_POWER_OFF_STA_WAIT_IMSA_POWER_OFF_CNF,

#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    NAS_MSCC_POWER_OFF_STA_WAIT_XSD_POWER_OFF_CNF,

    NAS_MSCC_POWER_OFF_STA_WAIT_HSD_POWER_OFF_CNF,

    NAS_MSCC_POWER_OFF_STA_WAIT_CL_POWER_SAVE_CNF,

    NAS_MSCC_POWER_OFF_STA_WAIT_HRPD_LTE_POWER_SAVE_CNF,
#endif

    NAS_MSCC_POWER_OFF_STA_BUTT
};
typedef VOS_UINT32  NAS_MSCC_POWER_OFF_STA_ENUM_UINT32;

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
VOS_UINT32 NAS_MSCC_GetPowerOffStaTblSize(VOS_VOID);

NAS_FSM_DESC_STRU * NAS_MSCC_GetPowerOffFsmDescAddr(VOS_VOID);

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

#endif /* end of NasMsccFsmPowerOffTbl.h */


