/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : MmSsInterface.h
  Description : Ss与Mm接口头文件
  History     :
      1. 张志勇      2004.02.27   新版作成
      2.日    期  : 2006年12月4日
        作    者  : luojian id:60022475
        修改内容  : 增加 #pragma pack(4)，问题单号:A32D07779
*******************************************************************************/

#ifndef _MM_SS_INTERFACE_H_
#define _MM_SS_INTERFACE_H_

#include "MmCmInterface.h"
#include "ExtAppCmInterface.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */
#pragma pack(4)

/* 原语类型定义 */

/* MM-->SS */
#define MMSS_EST_CNF                                        1
#define MMSS_EST_IND                                        3
#define MMSS_DATA_IND                                       5
#define MMSS_REL_IND                                        7

/* SS-->MM */
#define MMSS_EST_REQ                                        0
#define MMSS_DATA_REQ                                       2
#define MMSS_REL_REQ                                        4
#define MMSS_ABORT_REQ                                      6

#define MMSS_BEGIN_SESSION_NOTIFY                           (8)
#define MMSS_END_SESSION_NOTIFY                             (10)
#define MMSS_SS_STATUS_NOTIFY                               (12)

/* SS_MSG_STRU结构 */
typedef struct
{
    VOS_UINT32                   ulSsMsgSize;                                        /* [1,MMCC_MAX_SIZE_SS_MSG],Byte           */
    VOS_UINT8                   aucSsMsg[4];                                        /* 消息的前四个字节内容                       */
}SS_MSG_STRU;

/* MMSS_EST_REQ消息结构 */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头                                   */
    VOS_UINT32                          ulTi;                                   /* Transaction Id                          */
    VOS_UINT8                           ucRedialFlg;                            /* 重拨标志 */
    VOS_UINT8                           aucReserve[3];
}MMSS_EST_REQ_STRU;

/* MMSS_EST_CNF消息结构 */
#define     MMSS_EST_SUCCESS     0
#define     MMSS_EST_FAIL        1
typedef struct
{
    MSG_HEADER_STRU       MsgHeader;                                            /* 消息头                                   */
    VOS_UINT32                 ulTi;                                                 /* Transaction Id                          */
    VOS_UINT32                 ulResult;                                             /* 建立结果                                 */
}MMSS_EST_CNF_STRU;

/* MMSS_EST_IND消息结构 */
typedef struct
{
    MSG_HEADER_STRU       MsgHeader;                                            /* 消息头                                  */
    VOS_UINT32                 ulTi;                                                 /* Transaction Id                         */
    SS_MSG_STRU           SsMsg;                                                /* SS空口消息内容                           */
}MMSS_EST_IND_STRU;

/* MMSS_DATA_REQ消息结构 */
typedef struct
{
    MSG_HEADER_STRU       MsgHeader;                                            /* 消息头                                  */
    VOS_UINT32                 ulTi;                                                 /* Transaction Id                         */
    SS_MSG_STRU           SsMsg;                                                /* SS空口消息内容                           */
}MMSS_DATA_REQ_STRU;

/* MMSS_DATA_IND消息结构 */
typedef struct
{
    MSG_HEADER_STRU       MsgHeader;                                            /* 消息头                                  */
    VOS_UINT32                 ulTi;                                                 /* Transaction Id                         */
    SS_MSG_STRU           SsMsg;                                                /* SS空口消息内容                          */
}MMSS_DATA_IND_STRU;

/* MMSS_REL_REQ消息结构 */
typedef struct
{
    MSG_HEADER_STRU       MsgHeader;                                            /* 消息头                                  */
    VOS_UINT32                 ulTi;                                                 /* Transaction Id                         */
}MMSS_REL_REQ_STRU;

/* MMSS_REL_IND消息结构 */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头                                  */
    VOS_UINT32                          ulTi;                                   /* Transaction Id                         */

    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmssRelCause;
}MMSS_REL_IND_STRU;

/*****************************************************************************
 枚举名    : MMSS_SESSION_TYPE_ENUM_UINT8
 枚举说明  : SS域SESSION类型
 1.日    期   : 2014年5月28日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
enum MMSS_SESSION_TYPE_ENUM
{
    MMSS_SESSION_TYPE_MO_SS,
    MMSS_SESSION_TYPE_MT_SS,
    MMSS_SESSION_TYPE_BUTT
};
typedef VOS_UINT8 MMSS_SESSION_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名    : MMSS_BEGIN_SESSION_NOTIFY_STRU
 结构说明  : SESSION开始指示
 1.日    期   : 2014年5月28日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;                /*_H2ASN_Skip*/
    MMSS_SESSION_TYPE_ENUM_UINT8                    enSessionType;
    VOS_UINT8                                       aucReserved[3];
} MMSS_BEGIN_SESSION_NOTIFY_STRU;


/*****************************************************************************
 结构名    : MMSS_END_SESSION_NOTIFY_STRU
 结构说明  : SESSION结束指示
 1.日    期   : 2014年5月28日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;                /*_H2ASN_Skip*/
    MMSS_SESSION_TYPE_ENUM_UINT8                    enSessionType;
    VOS_UINT8                                       aucReserved[3];
} MMSS_END_SESSION_NOTIFY_STRU;



typedef SSA_SS_STATUS_ENUM_UINT8 MMSS_STATUS_ENUM_UINT8;

/*****************************************************************************
 结构名    : MMSS_STATUS_NTY_STRU
 结构说明  : SS建立状态指示
  1.日    期   : 2015年8月18日
    作    者   : s00217060
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;                /*_H2ASN_Skip*/
    MMSS_STATUS_ENUM_UINT8                          enSsStatus;
    VOS_UINT8                                       aucReserved[3];
} MMSS_STATUS_NTY_STRU;

/* 原语MMSS_ABORT_REQ的结构体 */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                    */
    VOS_UINT32                   ulTransactionId;                                    /* TI                                       */
}MMSS_ABORT_REQ_STRU;
#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif                                                                          /* __cpluscplus                             */

#endif
