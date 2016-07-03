

#ifndef __TAFAPSSNDXCC_H__
#define __TAFAPSSNDXCC_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "xcc_aps_pif.h"



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

VOS_VOID TAF_APS_SndXccDataCallSuspendRsp(
    VOS_UINT8                           ucConnectId
);

VOS_VOID TAF_APS_SndXccHangUpDataCallReq(
    VOS_UINT8                           ucCallId,
    TAF_XCC_END_REASON_ENUM_UINT8       enEndReason
);

VOS_VOID TAF_APS_SndXccOrigDataCallReq(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucHrpdHandOff1xFlg
);

VOS_VOID TAF_APS_SndXccIncomingCallRsp(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucConnectId,
    XCC_APS_RESULT_ENUM_UINT32          enRslt
);

VOS_VOID TAF_APS_SndXccAnswerDataCallReq(
    VOS_UINT8                           ucPdpId
);

VOS_VOID TAF_APS_SndXccPzidInfoNtf(
    XCC_APS_SO_CTRL_MSG_IND_STRU       *pstSoCtrlMsgInd
);
VOS_VOID TAF_APS_SndXccReserveSrIdNtf(
    VOS_UINT8                           ucSrId,
    VOS_UINT8                           ucCallId,
    VOS_UINT16                          usSo
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

#endif /* end of TafApsSndXcc.h */
