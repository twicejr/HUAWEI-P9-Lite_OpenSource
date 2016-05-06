/******************************************************************************

                  版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMtaModemInfoQuery.h
  版 本 号   : 初稿
  作    者   : zwx247453
  生成日期   : 2015年10月19日
  最近修改   :
  功能描述   : MTA模块处理AT侧下发查询功能
  函数列表   :
  修改历史   :
  1.日    期   : 2015年10月19日
    作    者   : zwx247453
    修改内容   : Network Monitor新增

******************************************************************************/

#ifndef __TAFMTAMODEMINFOQUERY_H__
#define __TAFMTAMODEMINFOQUERY_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"

#include "MtaRrcInterface.h"
#include "TafMtaPhy.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define TAF_MTA_NETMON_GSM_TA_INVALID_VALUE (255)

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

VOS_VOID TAF_MTA_RcvQryWrrAutotestReq(VOS_VOID *pMsg);
VOS_VOID TAF_MTA_RcvQryWrrCellInfoReq( VOS_VOID *pMsg );
VOS_VOID TAF_MTA_RcvQryWrrMeanrptReq( VOS_VOID  *pMsg );
VOS_VOID TAF_MTA_RcvWrrAutotestQryCnf( VOS_VOID *pWrrCnfMsg );
VOS_VOID TAF_MTA_RcvWrrCellInfoQryCnf( VOS_VOID *pWrrCnfMsg );
VOS_VOID TAF_MTA_RcvWrrMeanrptQryCnf( VOS_VOID *pWrrCnfMsg );
VOS_VOID TAF_MTA_RcvTiReqAutotestQryExpired( VOS_VOID *pMsg );
VOS_VOID TAF_MTA_RcvTiReqCellInfoQryExpired( VOS_VOID *pMsg );
VOS_VOID TAF_MTA_RcvTiReqMeanrptQryExpired( VOS_VOID *pMsg );
VOS_UINT32 TAF_MTA_SndWrrQryAutotestReqMsg( MTA_WRR_AUTOTEST_PARA_STRU  *pAutotestQryPara );
VOS_UINT32 TAF_MTA_SndWrrQryCellinfoReqMsg(
    VOS_UINT32                          ulSetCellInfo
);
VOS_UINT32 TAF_MTA_SndWrrQryMeanrptReqMsg( VOS_VOID );

VOS_VOID TAF_MTA_RcvAtTransModeQryReq(VOS_VOID *pMsg);
#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID TAF_MTA_SndLrrcTransModeQryReq(VOS_VOID);
VOS_VOID TAF_MTA_RcvLrrcTransModeQryCnf(VOS_VOID *pMsg);
VOS_VOID TAF_MTA_RcvTiWaitLrrcTransModeQryExpired(
    VOS_VOID                           *pMsg
);
#endif

VOS_VOID    TAF_MTA_RcvAtSetNetMonSCellReq(
    VOS_VOID                           *pMsg
);
VOS_VOID    TAF_MTA_RcvAtSetNetMonNCellReq(
    VOS_VOID                           *pMsg
);
VOS_VOID    TAF_MTA_SndRrcSetNetMonCellReq(
    VOS_UINT32                          ulMsgName,
    VOS_UINT32                          ulReceiverPid,
    MTA_NETMON_CELL_TYPE_ENUM_UINT32    enCelltype
);
VOS_UINT32  TAF_MTA_SndGasNetMonQryTaReq(
    AT_APPCTRL_STRU                    *pstAppCtrl
);
VOS_VOID    TAF_MTA_RcvGasNetMonTaQryCnf(
    VOS_VOID                           *pMsg
);
VOS_VOID    TAF_MTA_RcvGasNetMonCellQryCnf(
    VOS_VOID                           *pMsg
);
VOS_VOID    TAF_MTA_RcvWrrNetMonCellQryCnf(
    VOS_VOID                           *pMsg
);
VOS_VOID    TAF_MTA_RcvTiWaitGrrNetMonTaQryExpired(
    VOS_VOID                           *pMsg
);
VOS_VOID    TAF_MTA_RcvTiWaitRrcNetMonSCellQryExpired(
    VOS_VOID                           *pMsg
);
VOS_VOID    TAF_MTA_RcvTiWaitRrcNetMonNCellQryExpired(
    VOS_VOID                           *pMsg
);
VOS_UINT32  TAF_MTA_GetNetMonSndMsgInfo(
    VOS_UINT32                         *pulMsgName,
    VOS_UINT32                         *pulReceiverPid
);
#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID    TAF_MTA_SndLrrcSetNetMonCellReq(
    VOS_UINT32                          ulMsgName,
    VOS_UINT32                          ulReceiverPid,
    MTA_NETMON_CELL_TYPE_ENUM_UINT32    enCelltype
);
VOS_VOID    TAF_MTA_RcvLrrcNetMonCellQryCnf(
    VOS_VOID                           *pMsg
);
#endif
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
VOS_VOID    TAF_MTA_RcvTrrcNetMonCellQryCnf(
    VOS_VOID                           *pMsg
);
#endif

VOS_VOID TAF_MTA_RcvAtQryAfcAndXoInfoReq(
    VOS_VOID                           *pMsg
);

VOS_VOID TAF_MTA_RcvTiWaitRcmAfcInfoQryExpired(
    VOS_VOID                           *pMsg
);

VOS_VOID TAF_MTA_RcvRcmAfcInfoCnf(
    VOS_VOID                           *pMsg
);

AT_MTA_AFC_CLK_STATUS_ENUM_UINT32 TAF_MTA_GetAfcClkStatus(PHY_MTA_AFC_CLK_STATUS_ENUM_UINT16  enStatus);



#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

