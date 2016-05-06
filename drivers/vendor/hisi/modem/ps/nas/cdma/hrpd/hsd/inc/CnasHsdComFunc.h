/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsdComFunc.h
  版 本 号   : 初稿
  作    者   : h00300778
  生成日期   : 2014年7月3日
  最近修改   :
  功能描述   : CnasHsdComFunc.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月17日
    作    者   : h00300778
    修改内容   : 新生成函数

******************************************************************************/

#ifndef __CNAS_HSD_COM_FUNC_H__
#define __CNAS_HSD_COM_FUNC_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "CnasHsdTimer.h"
#include  "CnasHsdCtx.h"
#include  "cas_hrpd_idlestate_nas_pif.h"
#include  "CnasHsdMntn.h"

#include  "hsd_mscc_pif.h"
#include  "CnasPrlApi.h"
#include  "hsm_hsd_pif.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define CNAS_HSD_OCTET_LOW_FOUR_BITS                     (0x0f)                  /* 获取一个字节中的低4位 */
#define CNAS_HSD_OCTET_HIGH_FOUR_BITS                    (0xf0)                  /* 获取一个字节中的高4位 */
#define CNAS_HSD_OCTET_MOVE_FOUR_BITS                    (0x04)                  /* 将一个字节移动4位 */
#define CNAS_HSD_OCTET_MOVE_EIGHT_BITS                   (0x08)                  /* 将一个字节移动8位 */
#define CNAS_HSD_OCTET_MOVE_TWELVE_BITS                  (0x0C)                  /* 将一个字节移动8位 */
#define CNAS_HSD_OCTET_MOVE_SIXTEEN_BITS                 (0x10)                  /* 将一个字节移动16位 */

#define CNAS_HSD_INVALID_MCC                             (0xFFFFFFFF)
#define CNAS_HSD_MAX_HRPD_OTA_MCC                        (999)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
#ifdef DMT
extern VOS_UINT32                       g_ulHsdCurSlice;
#endif

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
 结构名    : CNAS_HSD_QRY_PREFSUBNET_CTRL_STRU
 结构说明  : 获取高优先级网络的控制结构
 1.日    期   : 2015年04月11日
   作    者   : z00316370
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          ucPriMore;
    VOS_UINT8                          ucCurPrioLvl;
    VOS_UINT8                          ucFirstPrioLvl;
    VOS_UINT8                          ucSecondPrioLvl;
    VOS_UINT8                          ucFirstPriSetFlag;
    VOS_UINT8                          ucSecondPriSetFlag;
    VOS_UINT8                          aucRcv[2];
}CNAS_HSD_QRY_HRPDSYSINFO_CTRL_STRU;

/****************************************************************************
Structure name  :   pCnasHsdGetPriClassFunc
Description     :   获取Pri class的函数表
Modify History:
    1)  Date    :   2015-05-04
        Author  :   z00316370
        Modify content :Create
****************************************************************************/

typedef MSCC_HSD_PRI_CLASS_ENUM_UINT8  (*pCnasHsdGetPriClassFunc)(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstHrpdSys
);

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

extern VOS_VOID CNAS_HSD_StartTimer(
    CNAS_HSD_TIMER_ID_ENUM_UINT32       enTimerId,
    VOS_UINT32                          ulTimerLen
);

extern VOS_VOID CNAS_HSD_StopTimer(
    CNAS_HSD_TIMER_ID_ENUM_UINT32       enTimerId
);

extern CNAS_HSD_AT_STATUS_ENUM_UINT32 CNAS_HSD_TransferCasStatusTypeToHsdFormat(
    HSM_HSD_HRPD_CAS_STATUS_ENUM_UINT16                     enCasStatus
);

extern VOS_UINT32 CNAS_HSD_GetSystemSlice(VOS_VOID);

extern VOS_UINT32 CNAS_HSD_GetSystemSliceNumOfOneSecond(VOS_VOID);

extern VOS_VOID CNAS_HSD_QRY_HrpdSysInfo(
    MSCC_HSD_QRY_HRPD_SYS_INFO_REQ_STRU *pstReqMsg,
    VOS_UINT8                           *pucHrpdSysNum,
    MSCC_HSD_HRPD_SYS_INFO_STRU         *pstHrpdSysInfoList,
    pCnasHsdGetPriClassFunc              pfunc
);

extern VOS_VOID CNAS_HSD_Set_HrpdSysInfo_Invalid(
    MSCC_HSD_HRPD_SYS_INFO_STRU        *pstHrpdSysInfo,
    VOS_UINT8                           ucSysNum
);

extern MSCC_HSD_PRI_CLASS_ENUM_UINT8 CNAS_HSD_GetPriClassWithTypeAI(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstHrpdSys
);

extern MSCC_HSD_PRI_CLASS_ENUM_UINT8 CNAS_HSD_GetPriClassWithTypeHRPD(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstHrpdSys
);

extern VOS_VOID CNAS_HSD_UpdatePrioLvl(
    MSCC_HSD_SYS_TYPE_ENUM_UINT8                            enSysType,
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSysRecord,
    CNAS_HSD_QRY_HRPDSYSINFO_CTRL_STRU                     *pstQryCtrl
);

extern VOS_VOID CNAS_HSD_SetPriorityWithCurrent(
    MSCC_HSD_SYS_TYPE_ENUM_UINT8        enSysType,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord,
    VOS_UINT8                           ucCurPriolvl,
    VOS_UINT8                          *ucPriolvl,
    VOS_UINT8                          *ucPriolvlFlag
);

extern VOS_VOID CNAS_HSD_SetPriClass(
    VOS_UINT8                           ucCurPrioLvl,
    VOS_UINT8                           ucFirstPriolvl,
    VOS_UINT8                           ucSecondPriolvl,
    MSCC_HSD_PRI_CLASS_ENUM_UINT8      *ucPriClass
);

extern VOS_VOID CNAS_HSD_BuildHrpdScanList_CasReq(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32  enSysAcqScene
);

extern VOS_VOID CNAS_HSD_ConvertLmmPlmnToGUNasPlmn(
    VOS_UINT32                          ulLmmPlmnNum,
    CNAS_CAS_HRPD_PLMN_STRU            *pstLmmPlmn,
    NAS_MSCC_PIF_PLMN_ID_STRU          *pstGUNasPlmn
);

extern VOS_VOID  CNAS_HSD_ConvertPlmnToNasPLMN(
    CNAS_CAS_HRPD_PLMN_STRU             *pstLmmPlmn,
    NAS_MSCC_PIF_PLMN_ID_STRU           *pstNasPlmn
);

VOS_UINT32  CNAS_HSD_ConvertHrpdMccToNasMcc(
    VOS_UINT16                          usHrpdMcc
);

extern CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32 CNAS_HSD_CheckHybridMode(
    VOS_UINT8               ucSuppNum,
    VOS_RATMODE_ENUM_UINT32 aenRatMode[VOS_RATMODE_BUTT]
);

extern VOS_UINT32 CNAS_HSD_IsHrpdSysChange(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstCurrHrpdSys,
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstLastHrpdSys
);

extern VOS_VOID  CNAS_HSD_ProcessCTCCCustomize(VOS_VOID);

extern VOS_UINT32 CNAS_HSD_IsMccInOperLockWhiteSidList(
    VOS_UINT16                          usMcc
);

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

#endif /* end of __CNAS_HSD_COM_FUNC_H__ */
