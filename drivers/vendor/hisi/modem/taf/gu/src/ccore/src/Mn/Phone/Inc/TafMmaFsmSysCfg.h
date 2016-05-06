/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMmaFsmSysCfg.h
  版 本 号   : 初稿
  作    者   : l00301449
  生成日期   : 2015年4月9日
  最近修改   :
  功能描述   : TafMmaFsmSysCfg.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年4月9日
    作    者   : l00301449
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAF_MMA_FSM_SYS_CFG_H__
#define __TAF_MMA_FSM_SYS_CFG_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "TafMmaCtx.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define TAF_MMA_ONE_RAT_NUM            (1)

#define TAF_MMA_TWO_RAT_NUM            (2)

#define TAF_MMA_THREE_RAT_NUM          (3)



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
 结构名称: TAF_MMA_RAT_CHANGE_OPER_TYPE_STRU
 结构说明: 定义系统配置设置中mode change导致的操作类型
 1.日    期   : 2015年4月9日
   作    者   : y00245242
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDetachOperation;
    VOS_UINT8                           ucAttachOperation;
    VOS_UINT8                           ucSysCfgOperation;
    VOS_UINT8                           ucReserved;
}TAF_MMA_RAT_CHANGE_OPER_TYPE_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : TAF_MMA_GUL_RAT_SUBMODE_TYPE_ENUM
 枚举说明  : GUL RAT类型定义
 1.日    期   : 2015年04月09日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
enum TAF_MMA_GUL_RAT_SUBMODE_TYPE_ENUM
{
    TAF_MMA_GUL_RAT_SUBMODE_G,                      /* G RAT */
    TAF_MMA_GUL_RAT_SUBMODE_U,                      /* U RAT */
    TAF_MMA_GUL_RAT_SUBMODE_L,                      /* L RAT */
    TAF_MMA_GUL_RAT_SUBMODE_GU,                     /* GU RAT */
    TAF_MMA_GUL_RAT_SUBMODE_GL,                     /* GL RAT */
    TAF_MMA_GUL_RAT_SUBMODE_UL,                     /* UL RAT */
    TAF_MMA_GUL_RAT_SUBMODE_GUL,                    /* GUL RAT */

    TAF_MMA_GUL_RAT_SUBMODE_BUTT
};
typedef VOS_UINT8 TAF_MMA_GUL_RAT_SUBMODE_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_MMA_CL_RAT_SUBMODE_TYPE_ENUM
 枚举说明  : CL RAT类型定义
 1.日    期   : 2015年04月09日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
enum TAF_MMA_CL_RAT_SUBMODE_TYPE_ENUM
{
    TAF_MMA_CL_RAT_SUBMODE_1X,                     /* 1X RAT */
    TAF_MMA_CL_RAT_SUBMODE_HRPD,                   /* HRPD RAT */
    TAF_MMA_CL_RAT_SUBMODE_L,                      /* L RAT */
    TAF_MMA_CL_RAT_SUBMODE_C,                      /* 1X&HRPD RAT */
    TAF_MMA_CL_RAT_SUBMODE_1XL,                    /* 1X&L RAT */
    TAF_MMA_CL_RAT_SUBMODE_HRPDL,                  /* HRPD&L_RAT */
    TAF_MMA_CL_RAT_SUBMODE_CL,                     /* C&L_RAT */

    TAF_MMA_CL_RAT_SUBMODE_BUTT
};
typedef VOS_UINT8 TAF_MMA_CL_RAT_SUBMODE_TYPE_ENUM_UINT8;

/* 移当前函数到TafMmaComFunc.c文件 */

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvSysCfgSetReq_SysCfg_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvInterSysCfgSetReq_SysCfg_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvDetachReq_SysCfg_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvAttachReq_SysCfg_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_MMA_RcvAutoAttachSetReq_SysCfg_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvDetachCnf_SysCfg_WaitDetachCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvAttachCnf_SysCfg_WaitAttachCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_MMA_RcvSysCfgCnf_SysCfg_WaitSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_MMA_ReportRslt_SysCfg(
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enAttachRslt,
    VOS_UINT16                          usPhoneError
);


VOS_UINT32 TAF_MMA_RcvTiWaitDetachCnfExpired_SysCfg_WaitDetachCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvTiWaitAttachCnfExpired_SysCfg_WaitAttachCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvAbortInd_SysCfg_WaitDetachCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvAbortInd_SysCfg_WaitAttachCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvAbortInd_SysCfg_WaitSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvTiWaitSysCfgCnfExpired_SysCfg_WaitSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

TAF_MMA_DETACH_TYPE_ENUM_UINT8 TAF_MMA_GetDetachTypeFromSysCfgOperType_SysCfg(
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
);

TAF_MMA_ATTACH_TYPE_ENUM_UINT8 TAF_MMA_GetAttachTypeFromSysCfgOperType_SysCfg(
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
);

VOS_UINT32  TAF_MMA_GetCurrFsmEntryMsgId_SysCfg(VOS_VOID);

TAF_CS_SERVICE_ENUM_UINT32  TAF_MMA_GetCsStateFromSyscfgOperType_SysCfg(
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
);

VOS_UINT8 TAF_MMA_IsOnlyRoamParaChangeFlgFromSysCfgOperType_SysCfg(
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
);

VOS_UINT8 TAF_MMA_IsNeedAttachPsFlgFromSysCfgOperType_SysCfg(
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
);

VOS_VOID TAF_MMA_NotifyCsServiceChange_SysCfg(
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
);

VOS_VOID TAF_MMA_GetSysCfgOperType_SysCfg(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfg,
    TAF_MMA_SYS_CFG_OPER_TYPE          *pusOperType,
    TAF_MMA_DETACH_CAUSE_ENUM_UINT8    *penDetachReason
);


VOS_VOID TAF_MMA_ProcInterSysCfgCnfFail_SysCfg(VOS_VOID);

VOS_VOID TAF_MMA_ProcSysCfgOper_SysCfg(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfg,
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType,
    TAF_MMA_DETACH_CAUSE_ENUM_UINT8     enDetachReason
);

VOS_VOID TAF_MMA_GetAttachOperType_SysCfg(
    TAF_MMA_ATTACH_TYPE_ENUM_UINT8                          enAttachType,
    TAF_MMA_SYS_CFG_OPER_TYPE                              *pusOperType
);
TAF_MMA_SYS_CFG_OPER_TYPE TAF_MMA_GetDetachOperType_SysCfg(
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8                       enDetachDomain
);

VOS_VOID TAF_MMA_GetAttachRsltFromServiceStatus_SysCfg(
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8                       enCsSrvStatus,
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8                       enPsSrvStatus,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32                    *penAttachRslt,
    VOS_UINT16                                             *pusPhoneError
);

VOS_VOID TAF_MMA_WritePrioAccessModeToNvim(VOS_VOID);

VOS_VOID TAF_MMA_UpdatePrioAccessMode(
    TAF_MMA_SYS_CFG_PARA_STRU                              *pstCurrSysCfg,
    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU                    *pstLastSysCfg
);

VOS_UINT32 TAF_MMA_IsLteExistInBothCurSysCfgAndOldSysCfg(
    TAF_MMA_SYS_CFG_PARA_STRU           *pstCurSysCfg,
    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU *pstOldSyscfg
);

VOS_UINT32 TAF_MMA_IsNeedAttachAfterSyscfgSet_SysCfg(
    NAS_MSCC_PIF_SYS_CFG_SET_RESULT_ENUM_UINT32             enRst,
    TAF_MMA_ATTACH_TYPE_ENUM_UINT8                         *penAttachType,
    TAF_PH_MS_CLASS_TYPE                                   *pucClassType,
    TAF_MMA_SYS_CFG_OPER_TYPE                              *pusOperType
);

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

#endif /* end of TafMmaFsmSysCfg.h */

