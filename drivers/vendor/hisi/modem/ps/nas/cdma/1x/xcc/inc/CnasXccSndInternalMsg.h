

#ifndef __CNAS_XCC_SND_INTERNAL_MSG_H__
#define __CNAS_XCC_SND_INTERNAL_MSG_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "CnasXccCtx.h"
#include "CnasCcb.h"

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

enum CNAS_XCC_INTERNAL_MSG_TYPE_ENUM
{
    ID_CNAS_XCC_XCC_ABORT_REQ                = 0x0000, /* _H2ASN_MsgChoice CNAS_XCC_XCC_ABORT_REQ_STRU */
    ID_CNAS_XCC_XCC_MO_CALLING_RSLT_CNF      = 0x0001, /* _H2ASN_MsgChoice CNAS_XCC_XCC_MO_CALLING_RSLT_CNF_STRU */
    ID_CNAS_XCC_XCC_MT_CALLING_RSLT_CNF      = 0x0002, /* _H2ASN_MsgChoice CNAS_XCC_XCC_MT_CALLING_RSLT_CNF_STRU */
    ID_CNAS_XCC_XCC_POWER_DOWN_IND           = 0x0003, /* _H2ASN_MsgChoice CNAS_XCC_XCC_POWER_DOWN_IND_STRU */
    ID_CNAS_XCC_XCC_NDSS_REDIAL_IND          = 0x0004, /* _H2ASN_MsgChoice CNAS_XCC_XCC_NDSS_REDIAL_IND_STRU */
    ID_CNAS_XCC_XCC_CALL_STATE_IND,                    /* _H2ASN_MsgChoice CNAS_XCC_XCC_CALL_STATE_IND_STRU */

#ifdef DMT
    ID_CNAS_XCC_XCC_TEST_CONFIG_IND,                   /* _H2ASN_MsgChoice CNAS_XCC_XCC_TEST_CONFIG_IND_STRU */
#endif

    ID_CNAS_XCC_XCC_PIF_MSG_TYPE_ENUM_BUTT   = 0xFFFF
};
typedef VOS_UINT16 CNAS_XCC_INTERNAL_MSG_TYPE_ENUM_UINT16;



enum CNAS_XCC_MT_CALLING_RESULT_ENUM
{
    CNAS_XCC_MT_CALLING_RESULT_SUCCESS          = 0x00000000,                   /* 说明电话打通 */
    CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED  = 0x00000001,                   /* 说明电话已经结束 */
    CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING = 0x00000002,                   /* 说明电话在挂断的过程中 */
    CNAS_XCC_MT_CALLING_RESULT_BUTT             = 0x00000003
};
typedef VOS_UINT32 CNAS_XCC_MT_CALLING_RESULT_ENUM_UINT32;


enum CNAS_XCC_MO_CALLING_RESULT_ENUM
{
    CNAS_XCC_MO_CALLING_RESULT_SUCCESS          = 0x00000000,                   /* 说明电话打通 */
    CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED  = 0x00000001,                   /* 说明电话已经结束 */
    CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING = 0x00000002,                   /* 说明电话在挂断的过程中 */
    CNAS_XCC_MO_CALLING_RESULT_BUTT             = 0x00000003
};
typedef VOS_UINT32 CNAS_XCC_MO_CALLING_RESULT_ENUM_UINT32;


enum CNAS_XCC_MO_CALLING_END_REASON_ENUM
{
    CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END      = 0x00000000,                /* 说明电话打通 */
    CNAS_XCC_MO_CALLING_END_REASON_POWER_DOWN_END  = 0x00000001,                /* 说明电话已经结束 */
    CNAS_XCC_MO_CALLING_END_REASON_BUTT            = 0x00000002
};
typedef VOS_UINT8 CNAS_XCC_MO_CALLING_END_REASON_ENUM_UINT8;


enum CNAS_XCC_MT_CALLING_END_REASON_ENUM
{
    CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END      = 0x00000000,                /* 说明电话正常挂断 */
    CNAS_XCC_MT_CALLING_END_REASON_POWER_DOWN_END  = 0x00000001,                /* 说明关机导致的电话结束 */
    CNAS_XCC_MT_CALLING_END_REASON_BUTT            = 0x00000002
};
typedef VOS_UINT8 CNAS_XCC_MT_CALLING_END_REASON_ENUM_UINT8;

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
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_XCC_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_XCC_MO_CALLING_RESULT_ENUM_UINT32                  enRslt;
    VOS_UINT8                                               ucConnectId;
    CNAS_XCC_MO_CALLING_END_REASON_ENUM_UINT8               enEndReason;
    VOS_UINT8                                               aucReserved[2];
}CNAS_XCC_XCC_MO_CALLING_RSLT_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_XCC_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_XCC_MT_CALLING_RESULT_ENUM_UINT32                  enRslt;
    VOS_UINT8                                               ucConnectId;
    CNAS_XCC_MT_CALLING_END_REASON_ENUM_UINT8               enEndReason;
    VOS_UINT8                                               aucReserved[2];
}CNAS_XCC_XCC_MT_CALLING_RSLT_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                      /* _H2ASN_Skip */
    CNAS_XCC_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId;    /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;

    VOS_UINT32                                              ulEventType; /* 触发该ABORT消息的事件类型 */
    VOS_UINT8                                               ucConnectId;
    VOS_UINT8                                               aucReserved[3];
    TAF_XCC_CAUSE_ENUM_UINT32                               enAbortCause;
}CNAS_XCC_XCC_ABORT_REQ_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                      /* _H2ASN_Skip */
    CNAS_XCC_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId;    /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               ucConnectId;
    VOS_UINT8                                               aucReserved[3];
}CNAS_XCC_XCC_POWER_DOWN_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                      /* _H2ASN_Skip */
    CNAS_XCC_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId;    /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               ucConnectId;
    VOS_UINT8                                               aucReserved[3];
}CNAS_XCC_XCC_NDSS_REDIAL_IND_STRU;

#ifdef DMT

typedef struct
{
    VOS_MSG_HEADER                                                      /* _H2ASN_Skip */
    CNAS_XCC_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId;    /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               ucDisableApsSupsRsp; /* 是否需要disable APS suspend RSP处理 */
    VOS_UINT8                                               aucReserved[3];
}CNAS_XCC_XCC_TEST_CONFIG_IND_STRU;
#endif

typedef struct
{
    VOS_MSG_HEADER                                                      /* _H2ASN_Skip */
    CNAS_XCC_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId;    /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_CCB_1X_CALL_STATE_ENUM_UINT8                       enCallState;
    VOS_UINT8                                               aucRslv[3];
}CNAS_XCC_XCC_CALL_STATE_IND_STRU;
/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    CNAS_XCC_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId;            /* _H2ASN_MsgChoice_Export CNAS_XCC_INTERNAL_MSG_TYPE_ENUM_UINT16 */

    VOS_UINT8                                               aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          CNAS_XCC_INTERNAL_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}CNAS_XCC_INTERNAL_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    CNAS_XCC_INTERNAL_MSG_DATA          stMsgData;
}CNAS_XCC_INTERNAL_MSG;



/*****************************************************************************
  10 函数声明
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID CNAS_XCC_SndMoCallingRslt(
    VOS_UINT8                                               ucConnId,
    CNAS_XCC_MO_CALLING_RESULT_ENUM_UINT32                  enRslt,
    CNAS_XCC_MO_CALLING_END_REASON_ENUM_UINT8               enEndReason
);

VOS_VOID CNAS_XCC_SndMtCallingRslt(
    VOS_UINT8                                               ucConnId,
    CNAS_XCC_MT_CALLING_RESULT_ENUM_UINT32                  enRslt,
    CNAS_XCC_MT_CALLING_END_REASON_ENUM_UINT8               enEndReason
);

VOS_VOID CNAS_XCC_SndXccAbortReq(
    VOS_UINT8                           ucConnId,
    VOS_UINT32                          ulEventType,
    TAF_XCC_CAUSE_ENUM_UINT32           enAbortCause
);

VOS_VOID CNAS_XCC_SndXccPowerDownInd(
    VOS_UINT8                           ucConnId
);

VOS_VOID CNAS_XCC_SndXccNdssRedialInd(
    VOS_UINT8                           ucConnId
);

VOS_VOID CNAS_XCC_SndXcc1xCallStateUpdateInd(
    VOS_VOID
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

#endif /* end of CnasXsdSndInternalMsg.h */
