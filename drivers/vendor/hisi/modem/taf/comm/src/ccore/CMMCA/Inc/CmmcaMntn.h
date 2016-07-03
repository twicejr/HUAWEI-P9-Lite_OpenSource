

#ifndef __CMMCAMNTN_H__
#define __CMMCAMNTN_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "CmmcaCmdComm.h"
#include "TafLog.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#if (VOS_WIN32 == VOS_OS_VER)
#define CMMCA_WARNING_LOG(string)                           vos_printf("%s \r\n", string)
#define CMMCA_WARNING1_LOG(string, para1)                   vos_printf("%s %d.\r\n", string, para1)
#define CMMCA_WARNING2_LOG(string, para1, para2)            vos_printf("%s %d, %d.\r\n", string, para1, para2)

#define CMMCA_ERROR_LOG(string)                             vos_printf("%s \r\n", string)
#define CMMCA_ERROR1_LOG(string, para1)                     vos_printf("%s %d.\r\n", string, para1)
#define CMMCA_ERROR2_LOG(string, para1, para2)              vos_printf("%s %d, %d.\r\n", string, para1, para2)
#else
#define CMMCA_WARNING_LOG(string)                           TAF_LOG(WUEPS_PID_CMMCA, 0, PS_LOG_LEVEL_WARNING,  string)
#define CMMCA_WARNING1_LOG(string, para1)                   TAF_LOG1(WUEPS_PID_CMMCA, 0, PS_LOG_LEVEL_WARNING,  string, (VOS_INT32)para1)
#define CMMCA_WARNING2_LOG(string, para1, para2)            TAF_LOG2(WUEPS_PID_CMMCA, 0, PS_LOG_LEVEL_WARNING,  string, (VOS_INT32)para1, (VOS_INT32)para2)

#define CMMCA_ERROR_LOG(string)                             TAF_LOG(WUEPS_PID_CMMCA, 0, PS_LOG_LEVEL_ERROR,  string)
#define CMMCA_ERROR1_LOG(string, para1)                     TAF_LOG1(WUEPS_PID_CMMCA, 0, PS_LOG_LEVEL_ERROR,  string, (VOS_INT32)para1)
#define CMMCA_ERROR2_LOG(string, para1, para2)              TAF_LOG2(WUEPS_PID_CMMCA, 0, PS_LOG_LEVEL_ERROR,  string, (VOS_INT32)para1, (VOS_INT32)para2)
#endif

#define CMMCA_DEBUG_MSG_RECORD_NUM                          (10)

/* 封装可维可测事件消息头 */
#define CMMCA_DEBUG_CFG_MSG_HDR(pstMsg, SenderPid, ReceiverPid, ulLen)\
                (pstMsg)->ulSenderCpuId   = VOS_LOCAL_CPUID;\
                (pstMsg)->ulSenderPid     = SenderPid;\
                (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                (pstMsg)->ulReceiverPid   = ReceiverPid;\
                (pstMsg)->ulLength        = (ulLen)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum CMMCA_MNTN_MSG_ID_ENUM
{
    CMMCA_MNTN_BUFF_FULL_IND            = 0x0,                                  /*_H2ASN_MsgChoice CMMCA_MNTN_BUFF_FULL_IND_STRU */
    CMMCA_MNTN_MSG_RECORD_IND,                                                  /* _H2ASN_MsgChoice CMMCA_MNTN_MSG_RECORD_IND_STRU */
    CMMCA_MNTN_MSG_ID_BUT
};
typedef VOS_UINT32 CMMCA_MNTN_MSG_ID_ENUM_UINT32;


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
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    CMMCA_MNTN_MSG_ID_ENUM_UINT32       enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
}CMMCA_MNTN_BUFF_FULL_IND_STRU;


typedef struct
{
    VOS_UINT32                          ulSendPid;
    VOS_UINT32                          ulMsgId;
    VOS_UINT32                          ulRcvTime;
}CMMCA_MNTN_MSG_RECORD_STRU;


typedef struct
{
    VOS_UINT32                          ulIndex;
    CMMCA_MNTN_MSG_RECORD_STRU          astMsgRecord[CMMCA_DEBUG_MSG_RECORD_NUM];
}CMMCA_MNTN_MSG_RECORD_INFO_STRU;


typedef struct
{
    CMMCA_MNTN_MSG_RECORD_INFO_STRU     stMsgRecordInfo;
}CMMCA_MNTN_CTX_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    CMMCA_MNTN_MSG_ID_ENUM_UINT32       enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    CMMCA_MNTN_MSG_RECORD_INFO_STRU     stMsgRecordInfo;
}CMMCA_MNTN_MSG_RECORD_IND_STRU;



/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID CMMCA_Debug_SetParseDbg(VOS_UINT8 ucParseDbg);

VOS_VOID CMMCA_Debug_PrintPdnId(VOS_UINT8 ucPdnId);

VOS_VOID CMMCA_Debug_PrintPdnType(VOS_UINT8 ucPdnType);

VOS_VOID CMMCA_Debug_PrintApn(
    VOS_UINT8                          *pucApn,
    VOS_UINT16                          usApnLen
);

VOS_VOID CMMCA_Debug_PrintRatId(
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16    enCmdId,
    CMMCA_MMC_RAT_ID_ENUM_UINT8         enRatId
);

VOS_VOID CMMCA_Debug_PrintDataIndLenErr(
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16    enCmdId,
    VOS_UINT32                          ulDataLen
);

VOS_VOID  CMMCA_LogBuffFullInd(VOS_VOID);

extern VOS_VOID DIAG_TraceReport(VOS_VOID *pMsg);

VOS_VOID CMMCA_DEBUG_InitCtx(VOS_VOID);

CMMCA_MNTN_MSG_RECORD_INFO_STRU* CMMCA_DEBUG_GetMsgRecoredInfoAddr(VOS_VOID);

VOS_VOID CMMCA_DEBUG_RecordMsgInfo(VOS_UINT32 ulSendPid, VOS_UINT32 ulMsgId);

VOS_VOID CMMCA_DEBUG_TraceEvent(VOS_VOID *pMsg);

VOS_VOID CMMCA_DEBUG_TraceMsgRecordInfo(VOS_VOID);

VOS_VOID CMMCA_Debug_PrintPdnAuthTypeErr(
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16    enCmdId,
    VOS_UINT8                           ucAuthType
);



typedef struct
{
    CMMCA_MNTN_MSG_ID_ENUM_UINT32       enMsgID;                                /*_H2ASN_MsgChoice_Export CMMCA_MNTN_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
/***************************************************************************
_H2ASN_MsgChoice_When_Comment          CMMCA_MNTN_MSG_ID_ENUM_UINT32
****************************************************************************/
}CMMCA_MNTN_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    CMMCA_MNTN_MSG_DATA                 stMsgData;
}CmmcaMntn_MSG;



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

#endif /* end of CmmcaMntn.h */
