/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXregProProcTbl.h
  版 本 号   : 初稿
  作    者   : zhuli
  生成日期   : 2014年8月3日
  最近修改   :
  功能描述   : CnasXregPreProc.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年8月3日
    作    者   : zhuli
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CNAS_XREG_PRE_PROC_TBL_H__
#define __CNAS_XREG_PRE_PROC_TBL_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "PsCommonDef.h"
#include  "NasFsm.h"

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
extern NAS_STA_STRU        g_astCnasXregPreProcessFsmTbl[];

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

extern VOS_UINT32 CNAS_XREG_RcvSysInfo_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg);

extern VOS_UINT32 CNAS_XREG_RcvPowerOffReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XREG_RcvXsdDeregisterInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XREG_RcvXsdRedirInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XREG_RcvNotCurrInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XREG_RcvXsdStateInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


extern VOS_UINT32 CNAS_XREG_RcvOrderRegDataInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


extern VOS_UINT32 CNAS_XREG_RcvT57TimeOut_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XREG_RcvPrdRegTimeout_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XREG_RcvTMSITimeOut_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XREG_RcvZoneListTimeout_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XREG_GetPreProcessStaTblSize(VOS_VOID);

extern NAS_FSM_DESC_STRU * CNAS_XREG_GetPreFsmDescAddr(VOS_VOID);

extern VOS_UINT32 CNAS_XREG_RcvProVerInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XREG_RcvStatusInd_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XREG_RcvOmRegReportReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XREG_RcvUsimRefreshInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XREG_RcvUsimReadFileCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
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

#endif /* end of CnasXregSndCas.h */
