/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsFsmCdataDiscing.h
  版 本 号   : 初稿
  作    者   : h00246512
  生成日期   : 2014年10月17日
  最近修改   :
  功能描述   : TafApsFsmCdataDiscing.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月17日
    作    者   : h00246512
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAFAPSFSMCDATADISCING_H__
#define __TAFAPSFSMCDATADISCING_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "TafApsApi.h"


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

VOS_UINT32  TAF_APS_RcvApsInternEndCdmaCallReq_CdataDiscing_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  TAF_APS_RcvPsCallEndReq_CdataDiscing_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  TAF_APS_RcvPsCallEnterDormantInd_CdataDiscing_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  TAF_APS_RcvPppDeactCnf_CdataDiscing_WaitPppDeactCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  TAF_APS_RcvPppDeactInd_CdataDiscing_WaitPppDeactCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  TAF_APS_RcvTiPppDeactCnfExpired_CdataDiscing_WaitPppDeactCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_WaitXccHangUpDataCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  TAF_APS_RcvXccHangUpDataCnf_CdataDiscing_WaitXccHangUpDataCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  TAF_APS_RcvXccDataCallDiscInd_CdataDiscing_WaitXccHangUpDataCallCnf(
        VOS_UINT32                          ulEventType,
        struct MsgCB                       *pstMsg
);
VOS_UINT32  TAF_APS_RcvXccDataCallDiscInd_CdataDiscing_WaitPppDeactCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvHsmDiscInd_CdataDiscing_WaitPppDeactCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  TAF_APS_RcvPppReConnInd_CdataDiscing_WaitPppDeactCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_APS_ProcHrpdOrigDataCall_CdataDiscing_HybridMode(
    VOS_UINT8                           ucPdpId,
    VOS_UINT32                          ulNeedSearchSys
);

VOS_UINT32 TAF_APS_Proc1xOrigDataCall_CdataDiscing_1XMode(
    VOS_UINT8                           ucIsDormDataCall,
    VOS_UINT8                           ucDrsFlg,
    VOS_UINT8                           ucHrpdHandOff1xFlg
);

VOS_UINT32 TAF_APS_RcvXccOrigDataCallCnf_CdataDiscing_WaitXccOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPppDeactCnf_CdataDiscing_WaitXccOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  TAF_APS_RcvPppDeactInd_CdataDiscing_WaitXccOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiPppDeactCnfExpired_CdataDiscing_WaitXccOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvHsmOrigCnf_CdataDiscing_WaitHsmOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPppDeactCnf_CdataDiscing_WaitHsmOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  TAF_APS_RcvPppDeactInd_CdataDiscing_WaitHsmOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiPppDeactCnfExpired_CdataDiscing_WaitHsmOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvXccDataServiceConnInd_CdataDiscing_WaitXccSoConnected(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvXccDataCallDiscInd_CdataDiscing_WaitXccSoConnected(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPppDeactCnf_CdataDiscing_WaitXccSoConnected(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPppDeactInd_CdataDiscing_WaitXccSoConnected(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiPppDeactCnfExpired_CdataDiscing_WaitXccSoConnected(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiRedialIntervalExpired_CdataDiscing_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPppDeactCnf_CdataDiscing_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPppDeactInd_CdataDiscing_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiPppDeactCnfExpired_CdataDiscing_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32  TAF_APS_RcvPsCallEndReq_CdataDiscing_WaitXccHangUpDataCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  TAF_APS_RcvTiWaitHangUpCnfExpired_CdataDiscing_WaitXccHangUpDataCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  TAF_APS_RcvPsInterEpdszidReOrigReq_CdataDiscing_WaitXccHangUpDataCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  TAF_APS_RcvPppDeactNtf_CdataDiscing_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32  TAF_APS_ProcCdataDisc_CdataDiscing(
    TAF_PS_CAUSE_ENUM_UINT32                enCause
);

VOS_UINT32  TAF_APS_RcvHsmDiscCnf_CdataDiscing_WaitHsmDiscCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_WaitHsmDiscCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  TAF_APS_RcvPsCallEndReq_CdataDiscing_WaitHsmDiscCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  TAF_APS_RcvHsmDiscInd_CdataDiscing_WaitHsmDiscCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);



VOS_UINT32  TAF_APS_RcvEhsmPdnDeactCnf_CdataDiscing_WaitEhsmPdnDeactCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  TAF_APS_RcvEhsmPdnDeactInd_CdataDiscing_WaitEhsmPdnDeactCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_WaitEhsmPdnDeactCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  TAF_APS_RcvEsmSmEpsBearerInfoInd_CdataDiscing_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  TAF_APS_RcvPsInterSrvStaChangeInd_CdataDiscing_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPsInterSrvStaChangeInd_CdataDiscing_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  TAF_APS_RcvEhsmApsLteHandoverToEhrpdInd_CdataDiscing_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
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

#endif /* end of TafApsFsmCdataDiscing.h */
