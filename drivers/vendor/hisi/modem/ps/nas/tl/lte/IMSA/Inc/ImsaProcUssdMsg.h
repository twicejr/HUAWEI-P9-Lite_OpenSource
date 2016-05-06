/******************************************************************************


        @(#)Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : ImsaProcUssdMsg.h
    Description : ImsaProcUssdMsg.c头文件
    History     :
      1.leili 00132387    2013-12-27  Draft Enact


******************************************************************************/

#ifndef __IMSAPROCUSSDMSG_H__
#define __IMSAPROCUSSDMSG_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include "vos.h"
#include "SpmImsaInterface.h"
#include "ImsaImsEvent.h"
//#include "TafAppSSa.h"


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
#pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
#define IMSA_USSD_TIMER_WAIT_NET_RSP_LENGTH     150000
#define IMSA_USSD_TIMER_WAIT_APP_RSP_LENGTH     150000



/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/




/*****************************************************************************
  5 STRUCT
*****************************************************************************/


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID IMSA_USSD_Init(VOS_VOID);
extern VOS_VOID IMSA_USSD_ClearResource(VOS_VOID);
extern VOS_VOID IMSA_USSD_ProcTimerMsgWaitNetRsp(const VOS_VOID *pRcvMsg);
extern VOS_VOID IMSA_USSD_ProcTimerMsgWaitAppRsp(const VOS_VOID *pRcvMsg);

extern VOS_UINT32 IMSA_SsProcSpmMsgProcessUssdReq(VOS_VOID *pMsg);
extern VOS_UINT32 IMSA_SsProcSpmMsgReleaseReq(VOS_VOID *pMsg);

extern VOS_VOID IMSA_USSD_SndImsUssdReqMsg
(
    IMSA_IMS_USSD_ENCTYPE_ENUM_UINT8   encType,
    VOS_UINT16   usLength,
    const VOS_UINT8   *pucMessage
);
extern VOS_VOID IMSA_USSD_SndImsUssdDisconnectMsg
(
    VOS_VOID
);
extern VOS_UINT32 IMSA_SendImsaSpmSsMsg
(
    const TAF_SS_CALL_INDEPENDENT_EVENT_STRU  *pEvtData,
    VOS_UINT16 usLen
);

extern VOS_UINT32 IMSA_SendSpmUssdDataSndEvt
(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);
extern VOS_UINT32 IMSA_SendSpmUssdReqIndEvt
(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucEncType,
    const TAF_SS_USSD_STRING_STRU             *pstUssdString
);

extern VOS_UINT32 IMSA_SendSpmUssdNotifyIndEvt
(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucEncType,
    const TAF_SS_USSD_STRING_STRU       *pstUssdString
);
extern VOS_UINT32 IMSA_SendSpmUssdRelCompleteIndEvt
(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);
extern VOS_UINT32 IMSA_SendSpmUssdReqCnfEvt
(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT16                           usError
);
extern VOS_UINT32 IMSA_SendSpmUssdErrorEvt
(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT16                          usError
);


/*****************************************************************************
  9 OTHERS
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
            }
    #endif
#endif

#endif /* end of ImsaProcSmsMsg.h */







