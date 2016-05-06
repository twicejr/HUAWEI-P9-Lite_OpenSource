

#ifndef __CNAS_EHSM_MNTN_H__
#define __CNAS_EHSM_MNTN_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "PsLogdef.h"
#include  "CnasEhsmCtx.h"
#include  "CnasMntn.h"
#include  "CnasCcb.h"

/* Determine if a C++ compiler is being used.  If so, ensure that standard
   C is used to process the API information.  */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* #if __cplusplus */
#endif /* #ifdef __cplusplus */

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define CNAS_EHSM_MSG_ID_BASE          (0x0100)
/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/* 以下消息可维可测[0x0100, 0x0199] */

enum CNAS_EHSM_MNTN_MSG_ID_ENUM
{
    ID_CNAS_EHSM_MNTN_LOG_FSM_INFO_IND                  = CNAS_EHSM_MSG_ID_BASE + 0X0000,     /*_H2ASN_MsgChoice  CNAS_EHSM_MNTN_LOG_FSM_INFO_STRU */

    ID_CNAS_EHSM_MNTN_LOG_TIMER_INFO_IND                = CNAS_EHSM_MSG_ID_BASE + 0X0001,     /*_H2ASN_MsgChoice  CNAS_EHSM_MNTN_LOG_TIMER_INFO_IND_STRU */

    ID_CNAS_EHSM_MNTN_LOG_BUFFER_MSG_INFO_IND           = CNAS_EHSM_MSG_ID_BASE + 0X0002,     /*_H2ASN_MsgChoice  CNAS_EHSM_MNTN_LOG_BUFFER_MSG_INFO_STRU */

    ID_CNAS_EHSM_MNTN_LOG_CTX_INFO_IND                  = CNAS_EHSM_MSG_ID_BASE + 0X0003,     /*_H2ASN_MsgChoice  CNAS_EHSM_MNTN_LOG_CTX_INFO_STRU */

    ID_CNAS_EHSM_MNTN_MSG_ID_BUTT
};
typedef VOS_UINT32 CNAS_EHSM_MNTN_MSG_ID_ENUM_UINT32;

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
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    CNAS_EHSM_MNTN_MSG_ID_ENUM_UINT32                       enMsgId;            /* _H2ASN_Skip */
    VOS_UINT32                                              ulCurFsmId;
    VOS_UINT32                                              ulCurFsmState;
}CNAS_EHSM_MNTN_LOG_FSM_INFO_STRU;


typedef struct
{
    VOS_UINT8                                               ucPdnId;
    VOS_UINT8                                               ucInUsed;
    VOS_UINT8                                               ucCid;
    VOS_UINT8                                               ucIsPdnActive;
    VOS_UINT32                                              ulEpsbId;
    CNAS_EHSM_ATTACH_TYPE_ENUM_UINT8                        enAttachType;
    CNAS_EHSM_PDN_TYPE_ENUM_UINT8                           enPdnType;      /**< to indicate IPv4 or v6, or both */
    VOS_UINT8                                               aucReserved[2];
}CNAS_EHSM_MNTN_EHRPD_PDN_BEAR_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucInUsed;
    VOS_UINT8                           ucCid;
    CNAS_EHSM_PDN_TYPE_ENUM_UINT8       enPdnType;                                                     /**< to indicate IPv4 or v6, or both */
    VOS_UINT8                           aucReserved[1];
    VOS_UINT32                          ulEpsbId;
}CNAS_EHSM_MNTN_LTE_PDN_BEAR_INFO_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    CNAS_EHSM_MNTN_MSG_ID_ENUM_UINT32                       enMsgId;            /* _H2ASN_Skip */
    CNAS_EHSM_EHRPD_STA_ENUM_UINT32                         enEhrpdState;                                /* 0:inactive 1:active 2:dormant 3:suspend(activating/deactivating/interwork)*/
    EHSM_HSM_SESSION_TYPE_ENUM_UINT32                       enSessionType;
    VOS_UINT32                                              ulAirLinkExist;
    CNAS_EHSM_RETRY_CONN_EST_INFO_STRU                      stRetryConnEstInfo;                     /* Contains the details about common conn est retry information */
    CNAS_EHSM_RETRY_PDN_SETUP_INFO_STRU                     stRetryPdnSetupInfo;    /* 0: air link not exist 1: air link exist */
    CNAS_EHSM_MNTN_EHRPD_PDN_BEAR_INFO_STRU                 astLocalPdnBearInfo[CNAS_EHSM_MAX_PDN_NUM];
    CNAS_EHSM_MNTN_LTE_PDN_BEAR_INFO_STRU                   astLtePdnBearInfo[CNAS_EHSM_MAX_PDN_NUM];
}CNAS_EHSM_MNTN_LOG_CTX_INFO_STRU;



typedef struct
{
    VOS_MSG_HEADER                                       	/* _H2ASN_Skip */
    CNAS_EHSM_MNTN_MSG_ID_ENUM_UINT32   enMsgId;            /* _H2ASN_Skip */
    VOS_UINT32                          ulFullFlg;
    CNAS_EHSM_CACHE_MSG_QUEUE_STRU      stMsgQueue;
}CNAS_EHSM_MNTN_LOG_BUFFER_MSG_INFO_STRU;



typedef struct
{
    CNAS_EHSM_MNTN_MSG_ID_ENUM_UINT32   enMsgId;            /* _H2ASN_MsgChoice_Export CNAS_EHSM_MNTN_MSG_ID_ENUM_UINT32 */
    VOS_UINT8                           aucMsgBlock[4];

    /* _H2ASN_MsgChoice_When_Comment CNAS_EHSM_MNTN_MSG_ID_ENUM_UINT32 */

}CNAS_EHSM_MNTN_DATA;

/* _H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    CNAS_EHSM_MNTN_DATA                 stMsgData;
}CNAS_EHSM_MNTN_MSG;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/


VOS_VOID CNAS_EHSM_MNTN_LogFsmInfo(
    VOS_UINT32                          ulFsmId,
    VOS_UINT32                          ulFsmState
);

VOS_VOID  CNAS_EHSM_MNTN_LogBufferQueueMsg(
    VOS_UINT32                          ulFullFlg
);

VOS_VOID CNAS_EHSM_MNTN_LogCtxInfo(VOS_VOID);


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif                                                                                 /* __cpluscplus                              */

#endif


