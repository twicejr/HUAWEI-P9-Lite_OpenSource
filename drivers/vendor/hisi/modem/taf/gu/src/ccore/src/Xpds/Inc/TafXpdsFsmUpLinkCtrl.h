

#ifndef __TAF_XPDS_FSMLINKCTRL_H__
#define __TAF_XPDS_FSMLINKCTRL_H__

/*****************************************************************************
  1 The Include of the header file
*****************************************************************************/
#include "vos.h"
#include "TafXpdsFsmUpLinkCtrlTbl.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*****************************************************************************
  2 The Macro Define
*****************************************************************************/

/*****************************************************************************
  3 The Enumeration Define
*****************************************************************************/
/*****************************************************************************
枚举名    : TAF_XPDS_SERVER_BIND_TYPE_ENUM_UINT8
枚举说明  : 指示对MPC/PDE Server的操作

  1.日    期   : 2015年8月20日
    作    者   : g00261581
    修改内容   : 新增枚举
*****************************************************************************/

enum TAF_XPDS_SERVER_BIND_TYPE_ENUM
{
    TAF_XPDS_SERVER_BIND_TYPE_OPEN_MPC_SOCKET = 0x01,
    TAF_XPDS_SERVER_BIND_TYPE_OPEN_PDE_SOCKET,
    TAF_XPDS_SERVER_BIND_TYPE_CLOSE_MPC_SOCKET,
    TAF_XPDS_SERVER_BIND_TYPE_CLOSE_PDE_SOCKET,
    TAF_XPDS_SERVER_BIND_TYPE_NO_ACT,

    TAF_XPDS_SERVER_BIND_TYPE_BUTT
};
typedef VOS_UINT8 TAF_XPDS_SERVER_BIND_TYPE_ENUM_UINT8;


/*****************************************************************************
  4 The Declaration Of The Gloabal Variable
*****************************************************************************/


/*****************************************************************************
  5 The Define Of the Message Header
*****************************************************************************/


/*****************************************************************************
  6 The Define of the Message Name
*****************************************************************************/


/*****************************************************************************
  7 The Struct Define
*****************************************************************************/


/*****************************************************************************
  8 The Union Define
*****************************************************************************/


/*****************************************************************************
  9 Other Defines
*****************************************************************************/


/*****************************************************************************
  10 The Declaration Of The Function
*****************************************************************************/
TAF_XPDS_SERVER_BIND_TYPE_ENUM_UINT8 TAF_XPDS_GetServerBindOperType(
    TAF_XPDS_SERVER_BIND_OPER_ENUM_UINT8                    enMpcBindOper,
    TAF_XPDS_SERVER_BIND_OPER_ENUM_UINT8                    enPdeBindOper
);

VOS_VOID TAF_XPDS_UpLinkCtrlServerBindProc(
    TAF_XPDS_SERVER_BIND_TYPE_ENUM_UINT8    enBindType
);

VOS_UINT32  TAF_XPDS_RcvXpdsServerBindReq_UpLinkCtrl_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvAtApDataCallStatusInd_UpLinkCtrl_WaitDataCallConnCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvAtApBindServerStatusInd_UpLinkCtrl_WaitOpenMpcSocket(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvAtApBindServerStatusInd_UpLinkCtrl_WaitCloseMpcSocket(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvAtApBindServerStatusInd_UpLinkCtrl_WaitOpenPdeSocket(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvAtApBindServerStatusInd_UpLinkCtrl_WaitClosePdeSocket(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvTiWaitDataCallIndExpired_UpLinkCtrl_WaitDataCallConnCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvTiWaitOpenMpcSocketExpired_UpLinkCtrl_WaitOpenMpcSocket(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvTiWaitCloseMpcSocketExpired_UpLinkCtrl_WaitCloseMpcSocket(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvTiWaitOpenPdeSocketExpired_UpLinkCtrl_WaitOpenPdeSocket(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvTiWaitClosePdeSocketExpired_UpLinkCtrl_WaitClosePdeSocket(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvXpdsAbortAgpsSessionInd_L2UpLink(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#endif /* FEATURE_UE_MODE_CDMA */

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

#endif /* end of TafXpdsFsmLinkCtrl.h */


