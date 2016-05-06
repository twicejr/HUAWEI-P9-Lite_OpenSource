/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXsdProcNvim.h
  版 本 号   : 初稿
  作    者   : h00246512
  生成日期   : 2014年7月8日
  最近修改   :
  功能描述   : CnasXsdProcNvim.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年7月8日
    作    者   : h00246512
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CNAS_XSD_PROC_NVIM_H__
#define __CNAS_XSD_PROC_NVIM_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "CnasXsdCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/


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
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID CNAS_XSD_ReadMruNvim(VOS_VOID);


VOS_VOID CNAS_XSD_WriteMruNvim(
    CNAS_XSD_MRU_LIST_STRU             *pstMruList
);

VOS_VOID CNAS_XSD_ReadPrlNvim(VOS_VOID);

VOS_VOID CNAS_XSD_ReadBandClassNvim(VOS_VOID);

VOS_VOID CNAS_XSD_ReadHomeSidNidNvim(VOS_VOID);
VOS_VOID CNAS_XSD_ReadSearchIntervalNvim(VOS_VOID);
VOS_VOID CNAS_XSD_ReadChanRepeatScanScheduleConfigNvim(VOS_VOID);

VOS_VOID CNAS_XSD_ReadTestConfigNvim(VOS_VOID);

VOS_VOID CNAS_XSD_ReadAddAvoidListCfgNvim(VOS_VOID);

VOS_VOID CNAS_XSD_ReadNegPrefSysCmpCtrlNvim(VOS_VOID);

VOS_VOID CNAS_XSD_ReadCallBackCfgNvim( VOS_VOID );

VOS_VOID CNAS_XSD_ReadCdmaStandardChannelsNvim(VOS_VOID);

VOS_VOID CNAS_XSD_ReadHomeSidNidDependOnCfgNvim(VOS_VOID);

VOS_VOID CNAS_XSD_ReadOperLockSysWhiteListInfoNvim(VOS_VOID);

VOS_VOID CNAS_XSD_ReadCTCCCustomizeFreqNvim(VOS_VOID);

VOS_UINT32 CNAS_XSD_WriteOperLockWhiteSidListInfoNvim(
    MSCC_XSD_OPER_LOCK_SYS_WHITE_STRU  *pstOPerLockWhiteSid
);

VOS_VOID CNAS_XSD_ReadCdma1XCustomPrefChannelsNvim( VOS_VOID );

VOS_VOID CNAS_XSD_Read1xSupportBandClassMaskNvim(VOS_VOID);

VOS_VOID CNAS_XSD_ReadNoCardModeCfgNvim(VOS_VOID);

VOS_VOID CNAS_XSD_ReadEmcRedialSysAcqCfgNvim(VOS_VOID);

VOS_VOID CNAS_XSD_Read1xAvoidScheduleInfoNvim(VOS_VOID);

VOS_VOID CNAS_XSD_Read1xPowerOffCampOnCtrlFlgNvim(VOS_VOID);


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

#endif /* end of CnasXsdProcNvim.h */
