/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXregRegingProcTbl.h
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年7月3日
  最近修改   :
  功能描述   : CnasXregRegingProcTbl.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年7月3日
    作    者   : y00245242
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CNAS_XREG_REGING_PROC_TBL_H__
#define __CNAS_XREG_REGING_PROC_TBL_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "NasFsm.h"
#include  "cas_1x_access_ctrl_proc_nas_pif.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 全局变量声明
*****************************************************************************/
extern NAS_STA_STRU     g_astCnasXsdSwitchOnStaTbl[];

extern NAS_STA_STRU     g_astCnasXregRegingStaTbl[];

/*****************************************************************************
  3 宏定义
*****************************************************************************/
#define CNAS_XREG_GetRegingStaTbl()                        (g_astCnasXregRegingStaTbl)

/*****************************************************************************
  4 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : CNAS_XREG_REGING_STA_ENUM_UINT32
 枚举说明  : 开机状态机ID枚举定义
 1.日    期   : 2014年07月03日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
enum CNAS_XREG_REGING_STA_ENUM
{
    /* 注册中状态机，初始状态 */
    CNAS_XREG_REGING_STA_INIT                = 0x00,

    /* 注册中状态机，等待注册回复状态 */
    CNAS_XREG_REGING_WAIT_EST_CNF            = 0x01,

    /* 注册中状态机，等待终止回复状态 */
    CNAS_XREG_REGING_WAIT_ABORT_IND          = 0x02,

    CNAS_XREG_REGING_STA_BUTT
};
typedef VOS_UINT32 CNAS_XREG_REGING_STA_ENUM_UINT32;

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
extern VOS_UINT32  CNAS_XREG_RcvRegReq_Reging_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32  CNAS_XREG_RcvAbortFsm_Reging_WaitEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32  CNAS_XREG_RcvEstCnf_Reging_WaitEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32  CNAS_XREG_RcvAbortInd_Reging_WaitEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32  CNAS_XREG_RcvTimeOut_Reging_WaitEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32  CNAS_XREG_RcvAbotInd_Reging_WaitAbortInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32  CNAS_XREG_RcvTimeOut_Reging_WaitAbortInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XSD_GetSwitchOnStaTblSize(VOS_VOID);

extern NAS_FSM_DESC_STRU * CNAS_XREG_GetRegingFsmDescAddr(VOS_VOID);

extern VOS_UINT32 CNAS_XREG_GetRegingStaTblSize(VOS_VOID);

extern NAS_FSM_DESC_STRU * CNAS_XSD_GetSwitchOnFsmDescAddr(VOS_VOID);

extern VOS_UINT32  CNAS_XREG_RcvAbortInd_Reging_WaitAbortInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32  CNAS_XREG_PostProcessMsg_Reging(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
extern VOS_UINT32 CNAS_XREG_IsNeedNotifyApsRegBegin(
    CAS_CNAS_1X_REGISTRATION_TYPE_ENUM_UINT8                enRegType
);

extern VOS_UINT32  CNAS_XREG_RcvPwrOffTimeOut_Reging_WaitEstCnf(
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

#endif /* end of CnasXsdFsmSwitchOnTbl.h */


