
#ifndef _TAF_SPM_SND_INTERNAL_MSG_H_
#define _TAF_SPM_SND_INTERNAL_MSG_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "TafSpmCtx.h"
#include "TafSpmServiceDomainSelProc.h"
#include "TafInternalInterface.h"

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

enum TAF_SPM_SERVICE_CTRL_RESULT_ENUM
{
    TAF_SPM_SERVICE_CTRL_SUCC                                   = 0,
    TAF_SPM_SERVICE_CTRL_FAIL                                   = 1,
    TAF_SPM_SERVICE_CTRL_BUTT
};
typedef VOS_UINT32 TAF_SPM_SERVICE_CTRL_RESULT_ENUM_UINT32;


enum TAF_SPM_INTERNAL_MSG_ID_ENUM
{
    TAF_SPM_INTERNAL_SERVICE_CTRL_RESULT_IND               = ID_TAF_MNTN_MSG_SPM_BASE +0x100, /*_H2ASN_MsgChoice TAF_SPM_SERVICE_CTRL_RSLT_STRU */

    TAF_SPM_INTERNAL_DOMAIN_SEL_IND,                                                          /*_H2ASN_MsgChoice TAF_SPM_DOMAIN_SEL_IND_STRU */

    TAF_SPM_INTERNAL_MSG_BUTT
};
typedef VOS_UINT32 TAF_SPM_INTERNAL_MSG_ID_ENUM_UINT32;


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

typedef struct
{
    MSG_HEADER_STRU                             MsgHeader;                              /* 消息头 */
    TAF_SPM_SERVICE_CTRL_RESULT_ENUM_UINT32     enResult;                               /* SERVICE CTRL结果 */
    VOS_UINT32                                  ulCause;                                /* 失败时携带的原因值 */
    VOS_UINT16                                  usClientId;                             /* 对应的client id */
    VOS_UINT8                                   aucRsv[2];
    TAF_SPM_ENTRY_MSG_STRU                      stEntryMsg;                             /* at或STK向SS发送的消息 */
} TAF_SPM_SERVICE_CTRL_RSLT_STRU;

/* 放到IMS宏开关外面公共使用 */

typedef struct
{
    MSG_HEADER_STRU                             MsgHeader;
} TAF_SPM_DOMAIN_SEL_IND_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID TAF_SPM_SndServiceCtrlRsltInd(
        TAF_SPM_SERVICE_CTRL_RESULT_ENUM_UINT32                 enRslt,
        VOS_UINT32                                              ulCause,
        VOS_UINT16                                              usClientId,
        TAF_SPM_ENTRY_MSG_STRU                                 *pstEntryMsg
);

#if (FEATURE_IMS == FEATURE_ON)
VOS_VOID TAF_SPM_SendMsgSmmaRsp(
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType,
    struct MsgCB                       *pstMsg
);
#endif

/* 放到IMS宏开关外面公共使用 */
VOS_VOID TAF_SPM_SndInternalDomainSelectionInd(VOS_VOID);


#if (FEATURE_ON == FEATURE_ECALL)
VOS_VOID TAF_SPM_SndTafRelCallReq(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    TAF_CALL_REL_CALL_TYPE_ENUM_UINT8   enRelType
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

#endif


