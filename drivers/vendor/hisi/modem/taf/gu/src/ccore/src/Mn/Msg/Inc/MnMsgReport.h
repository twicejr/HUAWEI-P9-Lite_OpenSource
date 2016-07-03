
#ifndef __MNMSGREPORT_H__
#define __MNMSGREPORT_H__


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "MnMsgApi.h"
#include  "TafCbsInterface.h"
#include "NasSms.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 接口函数声明
*****************************************************************************/

VOS_VOID MN_MSG_ReportResult(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_UINT32                          ulEventType,
    VOS_UINT32                          ulErrorCode
);


VOS_VOID MN_MSG_ReportRcvMsgEvent(
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_DELIVER_EVT_INFO_STRU  *pstDeliverEvt
);


VOS_VOID MN_MSG_ReportSmChanged(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_BOOL                            bBroadCast,
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
);


VOS_VOID MN_MSG_ReportMemExceed(
    MN_OPERATION_ID_T                   opId,
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
);


VOS_VOID MN_MSG_ReportSrvParmChanged(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
);


VOS_VOID MN_MSG_ReportDeliverErr(TAF_MSG_ERROR_ENUM_UINT32 enErrorCode);


VOS_VOID MN_MSG_ReportLinkCtrl(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_UINT32                          ulEventType,
    VOS_UINT32                          ulErrorCode,
    MN_MSG_LINK_CTRL_U8                 enLinkCtrl
);


VOS_VOID MN_MSG_ReportSentEvent(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_MSG_SENDMSG_EVT_INFO_STRU        *pstSendMsgEvt,
    VOS_UINT32                          ulEventType
);


VOS_VOID MN_MSG_ReportSubmitRptEvent(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_MSG_SUBMIT_RPT_EVT_INFO_STRU     *pstSubmitRptEvt,
    VOS_UINT32                          ulEventType
);


VOS_VOID MN_MSG_ReportRcvPathEvent(
    MN_CLIENT_ID_T                         clientId,
    MN_OPERATION_ID_T                      opId,
    VOS_BOOL                               bBroadCast,
    const MN_MSG_RCVMSG_PATH_EVT_INFO_STRU *pRcvPathEvt,
    VOS_UINT32                             ulEventType
);


VOS_VOID MN_MSG_ReportDeleteEvent(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_DELETE_EVT_INFO_STRU   *pstDeleteEvt,
    VOS_UINT32                          ulEventType
);


VOS_VOID MN_MSG_ReportDeleteTestEvent(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_DELETE_TEST_EVT_INFO_STRU *pstDeleteTestEvt,
    VOS_UINT32                          ulEventType
);


VOS_VOID MN_MSG_ReportWriteEvent(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_WRITE_EVT_INFO_STRU    *pstWriteEvt,
    VOS_UINT32                          ulEventType
);


VOS_VOID MN_MSG_ReportReadEvent(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_READ_EVT_INFO_STRU     *pReadEvt,
    VOS_UINT32                          ulEventType
);


VOS_VOID MN_MSG_ReportMemStatustEvent(
    MN_CLIENT_ID_T                       clientId,
    MN_OPERATION_ID_T                    opId,
    VOS_BOOL                             bBroadCast,
    const MN_MSG_MEMSTATUS_EVT_INFO_STRU *pstMemStatusEvt,
    VOS_UINT32                           ulEventType
);


VOS_VOID MN_MSG_ReportListEvent(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_LIST_EVT_INFO_STRU     *pListEvt,
    VOS_UINT32                          ulEventType
);



VOS_VOID MN_MSG_ReportModifyEvent(
    MN_CLIENT_ID_T                           clientId,
    MN_OPERATION_ID_T                        opId,
    const MN_MSG_MODIFY_STATUS_EVT_INFO_STRU *pModifyStatusEvt,
    VOS_UINT32                               ulEventType
);


VOS_VOID MN_MSG_ReportSrvParmEvent(
    MN_CLIENT_ID_T                       clientId,
    MN_OPERATION_ID_T                    opId,
    const MN_MSG_SRV_PARM_EVT_INFO_STRU *pstSrvParmEvt,
    VOS_UINT32                           ulEventType
);


VOS_VOID MN_MSG_SmInitFinish(
    MN_CLIENT_ID_T                      clientId
);


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

#endif /* __MNMSGREPORT_H__*/

