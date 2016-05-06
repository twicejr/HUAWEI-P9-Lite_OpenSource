

#ifndef __CNAS_EHSM_SND_INTERNAL_MSG_H__
#define __CNAS_EHSM_SND_INTERNAL_MSG_H__

/*****************************************************************************
  1 The Include of the header file
*****************************************************************************/
#include "vos.h"
#include "ehsm_aps_pif.h"

/* To Do: Need to add interface file */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 The Macro Define
*****************************************************************************/


/*****************************************************************************
  3 The Enumeration Define
*****************************************************************************/

enum CNAS_EHSM_INTERNAL_MSG_TYPE_ENUM
{
    ID_CNAS_EHSM_EHSM_ATTACH_REQ            = 0x0000,    /* _H2ASN_MsgChoice CNAS_EHSM_EHSM_ATTACH_REQ_STRU */
    ID_CNAS_EHSM_EHSM_ACTIVATING_RSLT_CNF   = 0x0001,    /* _H2ASN_MsgChoice CNAS_EHSM_EHSM_ACTIVATING_RSLT_CNF_STRU */
    ID_CNAS_EHSM_EHSM_DEACTIVATING_RSLT_CNF = 0x0002,    /* _H2ASN_MsgChoice CNAS_EHSM_EHSM_DEACTIVATING_RSLT_CNF_STRU */
    ID_CNAS_EHSM_EHSM_PDN_RE_ESTABLISH_REQ  = 0x0003,    /* _H2ASN_MsgChoice CNAS_EHSM_EHSM_PDN_RE_ESTABLISH_REQ_STRU */
    ID_CNAS_EHSM_EHSM_ABORT_REQ             = 0x0004,    /* _H2ASN_MsgChoice CNAS_EHSM_EHSM_ABORT_REQ_STRU */
    ID_CNAS_EHSM_EHSM_LOCAL_DETACH_ALL_REQ  = 0x0005,    /* _H2ASN_MsgChoice CNAS_EHSM_EHSM_LOCAL_DETACH_ALL_REQ_STRU */
    ID_CNAS_EHSM_EHSM_ENUM_MSG_BUTT         = 0xFFFF

};

typedef VOS_UINT32 CNAS_EHSM_INTERNAL_MSG_TYPE_ENUM_UINT32;





enum CNAS_EHSM_ACTIVATING_RESULT_ENUM
{
    CNAS_EHSM_ACTIVATING_RESULT_SUCCESS                 = 0x0000,
    CNAS_EHSM_ACTIVATING_RESULT_FAILURE                 = 0x0001,

    CNAS_EHSM_ACTIVATING_RESULT_BUTT                    = 0x0003
};
typedef VOS_UINT32 CNAS_EHSM_ACTIVATING_RESULT_ENUM_UINT32;


enum CNAS_EHSM_ABORT_REASON_ENUM
{
    CNAS_EHSM_ABORT_REASON_POWER_OFF               = 0x0000,
    CNAS_EHSM_ABORT_REASON_BUTT                    = 0x0001
};
typedef VOS_UINT32 CNAS_EHSM_ABORT_REASON_ENUM_UINT32;



enum CNAS_EHSM_ATTACH_REASON_ENUM
{
    CNAS_EHSM_ATTACH_REASON_INITIAL_ATTACH          = 0x0000,
    CNAS_EHSM_ATTACH_REASON_HANDOVER_ATTACH         = 0x0001,
    CNAS_EHSM_ATTACH_REASON_BUTT                    = 0x0002
};
typedef VOS_UINT32 CNAS_EHSM_ATTACH_REASON_ENUM_UINT32;

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

typedef struct
{
    VOS_MSG_HEADER                                               /* _H2ASN_Skip */
    CNAS_EHSM_INTERNAL_MSG_TYPE_ENUM_UINT32             enMsgId; /* _H2ASN_Skip */
    CNAS_EHSM_ACTIVATING_RESULT_ENUM_UINT32             enRslt;
    VOS_UINT8                                           ucIsPermanentFail;
    VOS_UINT8                                           aucReserved[3];
}CNAS_EHSM_EHSM_ACTIVATING_RSLT_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER                                               /* _H2ASN_Skip */
    CNAS_EHSM_INTERNAL_MSG_TYPE_ENUM_UINT32             enMsgId; /* _H2ASN_Skip */
    VOS_UINT8                                           aucReserved[4];
}CNAS_EHSM_EHSM_DEACTIVATING_RSLT_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER                                               /* _H2ASN_Skip */
    CNAS_EHSM_INTERNAL_MSG_TYPE_ENUM_UINT32             enMsgId; /* _H2ASN_Skip */
    VOS_UINT32                                          ulLtePdnIndex;
}CNAS_EHSM_EHSM_PDN_RE_ESTABLISH_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                               /* _H2ASN_Skip */
    CNAS_EHSM_INTERNAL_MSG_TYPE_ENUM_UINT32             enMsgId; /* _H2ASN_Skip */
    VOS_UINT32                                          ulEventType;
}CNAS_EHSM_EHSM_ABORT_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                               /* _H2ASN_Skip */
    CNAS_EHSM_INTERNAL_MSG_TYPE_ENUM_UINT32             enMsgId; /* _H2ASN_Skip */
    EHSM_APS_CAUSE_ENUM_UINT32                          enCause;
}CNAS_EHSM_EHSM_LOCAL_DETACH_ALL_REQ_STRU;




typedef struct
{
    VOS_MSG_HEADER                                               /* _H2ASN_Skip */
    CNAS_EHSM_INTERNAL_MSG_TYPE_ENUM_UINT32             enMsgId; /* _H2ASN_Skip */
    CNAS_EHSM_ATTACH_REASON_ENUM_UINT32                 enAttachReason;
}CNAS_EHSM_EHSM_ATTACH_REQ_STRU;


/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    CNAS_EHSM_INTERNAL_MSG_TYPE_ENUM_UINT32   ulMsgId;                                /*_H2ASN_MsgChoice_Export CNAS_EHSM_INTERNAL_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          CNAS_EHSM_INTERNAL_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}CNAS_EHSM_INTERNAL_MSG_TYPE_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    CNAS_EHSM_INTERNAL_MSG_TYPE_DATA          stMsgReq;
}CnasEhsmSndInternalMsg_MSG;

/*****************************************************************************
  8 The Union Define
*****************************************************************************/


/*****************************************************************************
  9 Other Defines
*****************************************************************************/


/*****************************************************************************
  10 The Declaration Of The Function
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID CNAS_EHSM_SndDeactivatingRslt(VOS_VOID);

/* To Do: Need to include prototypes for sending internal messages from EHSM to EHSM */
VOS_VOID CNAS_EHSM_SndActivatingRslt(
    VOS_UINT32                          ulResult,
    VOS_UINT8                           ucIsPermanentFail
);

VOS_VOID CNAS_EHSM_SndInternalAttachReq(
    CNAS_EHSM_ATTACH_REASON_ENUM_UINT32                 enAttachReason
);

VOS_VOID CNAS_EHSM_SndPdnSetupReq(
    VOS_UINT32                          ulLtePdnIndex
);

VOS_VOID CNAS_EHSM_SndInternalAbortReq(
    VOS_UINT32                          ulEventType
);
VOS_VOID CNAS_EHSM_SndLocalDetachAllReq(
    EHSM_APS_CAUSE_ENUM_UINT32                          enCause
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

#endif /* end of CnasEhsmSndInternalMsg.h */





