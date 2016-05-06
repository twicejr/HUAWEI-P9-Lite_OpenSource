/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CmmcaRegMgmt.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2014年1月7日
  最近修改   :
  功能描述   : CmmcaRegMgmt.c的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年1月27日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CMMCAREGMGMT_H__
#define __CMMCAREGMGMT_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "CmmcaParseCmd.h"
#include  "TafAppMma.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

#if (FEATURE_ON == FEATURE_CL_INTERWORK)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define CMMCA_INVALID_MCC                                   (0xffffffff)
#define CMMCA_INVALID_MNC                                   (0xffffffff)

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
typedef VOS_VOID (*CMMCA_REG_MMA_EVT_FUNC)(VOS_VOID *pEvtInfo);

/*****************************************************************************
 结构名    : CMMCA_REG_MMA_EVT_FUNC_TBL_STRU
 结构说明  : APS PS域事件处理函数表结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMsgId;
    CMMCA_REG_MMA_EVT_FUNC              pMmaEvtFunc;
}CMMCA_REG_MMA_EVT_FUNC_TBL_STRU;

/*****************************************************************************
 结构名    : CMMCA_RAT_SYS_INFO_STRU
 结构说明  : rat sys info结构
 1.日    期   : 2014年02月12日
   作    者   : s00261364
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
   CMMCA_RAT_GMSS_PRIORITY_CLASS_ENUM_UINT8                 enPriorityClass; /* PLMN priority class */
   VOS_UINT16                                               usEarfcn;        /* EUTRAN channel number */
   VOS_UINT8                                                aucReserved[1];
   VOS_UINT32                                               ulMcc;
   VOS_UINT32                                               ulMnc;
}CMMCA_RAT_SYS_INFO_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID CMMCA_REG_SndNtwIndRpt(
    CMMCA_RAT_SYS_INFO_STRU            *pstRatInfo,
    TAF_MMA_SERVICE_STATUS_IND_STRU    *pstServStatusInd
);
VOS_VOID CMMCA_REG_SndPowerUpRsp(
    CMMCA_MMC_RAT_ID_ENUM_UINT8                             enRatId,
    CMMCA_RAT_POWERUP_RSP_RESULT_ENUM_UINT8                 enResult
);
VOS_VOID CMMCA_REG_SndPowerDownRsp(
    CMMCA_MMC_RAT_ID_ENUM_UINT8     enRatId
);
VOS_VOID CMMCA_REG_SndModeRsp(
    CMMCA_MMC_RAT_ID_ENUM_UINT8                             enRatId,
    CMMCA_MMC_MODE_RSP_RESULT_ENUM_UINT8                    ucResult
);
VOS_VOID CMMCA_REG_SndRegRsp(
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt,
    TAF_MMA_ATTACH_CL_REG_STATUS_ENUM8  enLmmAttachRegStatus,
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16    usCmdId,
    CMMCA_RAT_SYS_INFO_STRU            *pstRatInfo
);
VOS_VOID CMMCA_REG_SndMccSearchRsp(
    CMMCA_MMC_RAT_ID_ENUM_UINT8         enRatId,
    CMMCA_RAT_MMC_RAT_SYS_INFO_STRU    *pstSysInfo
);
VOS_VOID CMMCA_REG_SndPsRegRsp(
    CMMCA_MMC_RAT_ID_ENUM_UINT8         enRatId,
    CMMCA_RAT_REG_RESULT_ENUM_UINT8     enResult,
    CMMCA_RAT_ATTACH_CL_REG_STATUS_ENUM8                    enLmmAttachRegStatus,
    CMMCA_RAT_SYS_INFO_STRU            *pstRatInfo
);
VOS_VOID CMMCA_REG_SndCellInfoPsRegRsp(
    CMMCA_MMC_RAT_ID_ENUM_UINT8                             enRatId,
    CMMCA_RAT_MMC_STATUS_ENUM_UINT8                         enResult,
    CMMCA_RAT_ATTACH_CL_REG_STATUS_ENUM8                    enLmmAttachRegStatus,
    CMMCA_RAT_SYS_INFO_STRU                                *pstRatInfo
);
VOS_VOID CMMCA_REG_SndAcqRsp(
    CMMCA_MMC_RAT_ID_ENUM_UINT8         enRatId,
    CMMCA_RAT_ACQ_RESULT_ENUM_UINT8     enRslt,
    CMMCA_RAT_SYS_INFO_STRU            *pstRatInfo
);
VOS_VOID CMMCA_REG_SndNoServiceRsp(
    CMMCA_MMC_RAT_ID_ENUM_UINT8         enRatId,
    VOS_UINT8                           ucStatus
);
VOS_VOID CMMCA_REG_SndNtwStChgInd(
    CMMCA_MMC_RAT_ID_ENUM_UINT8         enRatId,
    CMMCA_RAT_NOTIFY_CAUSE_ENUM_UINT8   enCause,
    CMMCA_RAT_CPST_ENUM_UINT8           enStatus,
    CMMCA_RAT_SYS_INFO_STRU            *pstRatInfo
);
VOS_VOID CMMCA_REG_SndMmcRejInd(
    CMMCA_MMC_RAT_ID_ENUM_UINT8         enSourceRat,
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16    enApiID,
    CMMCA_RAT_CMD_REJ_REASON_ENUM_UINT8 enCause
);

VOS_VOID CMMCA_PKT_SndBearDetachRsp(
    CMMCA_MMC_RAT_ID_ENUM_UINT8         enRatId,
    VOS_UINT8                           ucStatus
);

VOS_VOID CMMCA_REG_RcvRatModeReq(
    VOS_VOID                           *pMsg
);
VOS_VOID CMMCA_REG_RcvPowerUpReq(
    VOS_VOID                           *pMsg
);
VOS_VOID CMMCA_REG_RcvPowerDownReq(
    VOS_VOID                           *pMsg
);
VOS_VOID CMMCA_REG_RcvRatAcqReq(
    VOS_VOID                           *pMsg
);
VOS_VOID CMMCA_REG_RcvMccSearchReq(
    VOS_VOID                           *pMsg
);
VOS_VOID CMMCA_REG_RcvPsRegReq(
    VOS_VOID                           *pMsg
);
VOS_VOID CMMCA_REG_RcvCellInfoPsRegReq(
    VOS_VOID                           *pMsg
);
VOS_VOID CMMCA_REG_RcvNoServiceReq(
    VOS_VOID                           *pMsg
);
VOS_VOID CMMCA_REG_RcvPktDataCmdReq(
    VOS_VOID                           *pMsg
);

VOS_VOID CMMCA_REG_RcvBearDetachReq(
    VOS_VOID                           *pMsg
);

VOS_VOID CMMCA_REG_RcvMmaSysCfgCnf(
    VOS_VOID                           *pMsg
);
VOS_VOID CMMCA_REG_RcvMmaPhoneModeSetcnf(
    VOS_VOID                           *pMsg
);
VOS_VOID CMMCA_REG_RcvMmaAcqCnf(
    VOS_VOID                           *pMsg
);
VOS_VOID CMMCA_REG_RcvMmaServiceStateInd(
    VOS_VOID                           *pMsg
);
VOS_VOID CMMCA_REG_RcvMmaAcqInd(
    VOS_VOID                           *pMsg
);
VOS_VOID CMMCA_REG_RcvMmaPowerSaveCnf(
    VOS_VOID                           *pMsg
);
VOS_VOID CMMCA_REG_RcvMmaRegCnf(
    VOS_VOID                           *pMsg
);
VOS_VOID CMMCA_REG_RcvMmaDetachCnf(
    VOS_VOID                           *pMsg
);
VOS_VOID CMMCA_REG_RcvMmaSimStatusInd(
    VOS_VOID                           *pMsg
);
VOS_VOID  CMMCA_REG_RcvMmaSysInfoInd(
    VOS_VOID                           *pMsg
);
VOS_VOID CMMCA_REG_RcvMmaMsg(struct MsgCB *pstMsg);

VOS_VOID CMMCA_REG_SndPktDataCmdRsp(
    CMMCA_MMC_RAT_ID_ENUM_UINT8                             enRatId,
    CMMCA_IRAT_DATA_CONNECT_CMD_RSP_ENUM_UINT8              enCmdRsp
);

CMMCA_RAT_GMSS_PRIORITY_CLASS_ENUM_UINT8 CMMCA_REG_ConvertTafPriToCmmcaPri(
    TAF_MMA_PLMN_PRIORITY_CLASS_ENUM_UINT8      enTafPriClass
);

CMMCA_RAT_ATTACH_CL_REG_STATUS_ENUM8 CMMCA_ConvertLmmAttachRegStatus(
    TAF_MMA_ATTACH_CL_REG_STATUS_ENUM8  enLmmAttachRegStatus
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

#endif /* end of CmmcaRegMgmt.h */
