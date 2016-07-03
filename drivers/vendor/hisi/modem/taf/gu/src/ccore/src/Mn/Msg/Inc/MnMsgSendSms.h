
#ifndef __MNMSGSENDSMS_H__
#define __MNMSGSENDSMS_H__


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "MnMsgApi.h"
#include  "MnMsgSmCommProc.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 接口函数声明
*****************************************************************************/

VOS_UINT32 MN_MSG_SendSmsRpDataReq(
    MN_MSG_SEND_DOMAIN_ENUM_U8          enSendDomain,
    const VOS_UINT8                     *pucSendMsg ,
    VOS_UINT8                           ucSendLen,
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType
);


extern VOS_VOID MN_MSG_SendSmsCpAckReq(VOS_VOID);


VOS_UINT32 MN_MSG_SendSmsRpReportReq(
    const VOS_UINT8                     *pucSendMsg,
    VOS_UINT8                           ucSendLen,
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType    
);


VOS_UINT32 MN_MSG_SendSmsSmmaReq(
    MN_MSG_SEND_DOMAIN_ENUM_U8          enSendDomain,
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType
);



VOS_VOID  MN_MSG_EncodeRpData(
    const MN_MSG_RP_DATA_STRU           *pstRpData,
    VOS_UINT8                           *pucRpduContent,
    VOS_UINT8                           *pucRpduLen
);


VOS_VOID  MN_MSG_EncodeRpAck(
    const MN_MSG_RP_ACK_STRU            *pstRpAck,
    VOS_UINT8                           *pucRpduContent,
    VOS_UINT8                           *pucRpduLen
);


VOS_VOID  MN_MSG_EncodeRpErr(
    const MN_MSG_RP_ERR_STRU            *pstRpErr,
    VOS_UINT8                           *pucRpduContent,
    VOS_UINT8                           *pucRpduLen
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

#endif /* __MNMSGSENDSMS_H__ */

