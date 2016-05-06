/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : RabmTafInterface.h
  Description : RABM与TAF接口头文件
  History     :
      1.  张志勇      2003.12.04   新版作成
      2.日    期  : 2006年12月4日
        作    者  : luojian id:60022475
        修改内容  : 增加 #pragma pack(4)，问题单号:A32D07779
*******************************************************************************/

#ifndef _RABM_TAF_INTERFACE_H_
#define _RABM_TAF_INTERFACE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */

#include "TTFMem.h"


#pragma pack(4)
/* 应用层发送给RABM的原语 */
#define TAFRABM_PS_DATA_REQ             0
#define TAFRABM_CS_DATA_REQ             2
/* RABM发送给应用层的原语 */
#define TAFRABM_PS_DATA_CNF             1
#define TAFRABM_CS_DATA_CNF             3
#define TAFRABM_INACTIVE_NSAPI_IND      5
#define TAFRABM_INACTIVE_SI_IND         7
#define TAFRABM_STARTSTOP_IND           9
#define TAFRABM_PS_DATA_IND             11
#define TAFRABM_CS_DATA_IND             13

/*由于TAF层无法区分RABM是发给CALL的还是APS的，因此，目前将消息隔开，
  RABM发给CALL的消息，编号从0x4000开始，目前RABM发给APS的编号，目前是
  从0x0120开始编号*/
#define RABM_CALL_MSG_CLASS_BASE        (0x4000)
#define RABM_CALL_SYNC_IND              (0x4001)

/*MN_CALL通知Rabm是否存在语音业务*/
#define CALL_RABM_VOICEPREFER_CS_EXIST_IND                  (0x4002)

/* 原语TAFRABM_PS_DATA_REQ的结构体 */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                   */
    VOS_UINT32                   ulNsapi;                                            /* 指定的NSAPI                              */
    TTF_MEM_ST              *pData;                                         /* 用户数据地址                             */
}TAFRABM_PS_DATA_REQ_STRU;

/* 原语TAFRABM_PS_DATA_IND的结构体 */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                   */
    VOS_UINT32                   ulDestAddr;                                         /* 指定的TAF地址                            */
    VOS_UINT32                   ulNsapi;                                            /* 指定的NSAPI                              */
    VOS_UINT32                   ulDataLen;                                          /* 用户数据的长度                           */
    VOS_UINT8                   aucData[4];                                         /* 用户数据地址                             */
}TAFRABM_PS_DATA_IND_STRU;

/* 原语TAFRABM_STARTSTOP_IND的结构体 */
typedef struct
{
    MSG_HEADER_STRU        MsgHeader;                                           /* 消息头                                   */

#define  TAF_RABM_MAX_NSAPI_NUM    11
    VOS_UINT32           ulNsapiOrSi;                                                /* RAB ID所对应的NSAPI                      */
    VOS_UINT32           ulStartStopFlag;                                            /* 停止或开始发送数据标志                     */
    VOS_UINT32           ulStartCause;                                               /* 开始发送数据的原因                        */
}TAFRABM_STARTSTOP_IND_STRU;

/* 原语TAFRABM_INACTIVE_NSAPI_IND的结构体 */
typedef struct
{
    MSG_HEADER_STRU        MsgHeader;                                           /* 消息头                                   */
    VOS_UINT32                  ulNsapi;                                             /* 指定的NSAPI                              */
} TAFRABM_INACTIVE_NSAPI_IND_STRU;

/* 原语TAFRABM_CS_DATA_REQ的结构体 */
typedef struct
{
    MSG_HEADER_STRU        MsgHeader;                                           /* 消息头                                   */
    VOS_UINT32                  ulSi;                                                /* 指定的Si                                 */
    VOS_UINT32                  ulAmrFlg ;                                           /* 该数据是否是语音数据
                                                                                 * RABM_TRUE:是;RABM_FALSE:不是             */
    VOS_UINT32                  ulDataLen;                                           /* 用户数据的长度                            */
    VOS_UINT8                  aucData[4];                                          /* 用户数据地址                              */
}TAFRABM_CS_DATA_REQ_STRU;

/* 原语TAFRABM_CS_DATA_IND的结构体 */
typedef struct
{
    MSG_HEADER_STRU        MsgHeader;                                           /* 消息头                                   */

    VOS_UINT32                  ulSi;                                                /* 指定的Si                                 */
    VOS_UINT32                  ulDataLen;                                           /* 用户数据的长度                            */
    VOS_UINT8                  aucData[4];                                          /* 用户数据地址                             */
}TAFRABM_CS_DATA_IND_STRU;

/* 原语TAFRABM_INACTIVE_SI_IND的结构体 */
typedef struct
{
    MSG_HEADER_STRU        MsgHeader;                                           /* 消息头                                   */
    VOS_UINT32                  ulSi;                                                /* 指定的Si                                 */
} TAFRABM_INACTIVE_SI_IND_STRU;

/* 原语TAFRABM_PS_DATA_CNF的结构体 */
typedef struct
{
    MSG_HEADER_STRU        MsgHeader;                                           /* 消息头                                   */
    VOS_UINT32                  ulNsapi;                                             /* 指定的nsapi                              */
} TAFRABM_PS_DATA_CNF_STRU;

/* 原语TAFRABM_CS_DATA_CNF的结构体 */
typedef struct
{
    MSG_HEADER_STRU        MsgHeader;                                           /* 消息头                                   */
    VOS_UINT32                  ulSi;                                                /* specified SI                             */
}TAFRABM_CS_DATA_CNF_STRU;


#define    RABMCALL_RAB_ACTIVE      0
#define    RABMCALL_RAB_INACTIVE    1

#define    RABM_CALL_MAX_RB_NUM_PER_RAB   3
typedef struct
{
    MSG_HEADER_STRU        MsgHeader;                                           /* 消息头                                   */
    VOS_UINT32             ulRabState;                                          /* 0：SI可以使用；1：SI不可以使用             */
    VOS_UINT32             ulRabId;                                             /* 该RAB对应的RAB ID                        */
    VOS_UINT32             ulRbNum;                                             /* 该RAB包含RB数量                          */
    VOS_UINT32             aulRbId[RABM_CALL_MAX_RB_NUM_PER_RAB];                    /* RB ID列表                                */
}RABM_CALL_SYNC_IND_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */
    VOS_UINT32                          ulVoiceFlag;                            /* 0：不存在语音业务；1：存在语音业务 */
    VOS_UINT32                          ulCampMcc;                              /* 当前注册plmn:mcc*/
    VOS_UINT32                          ulCampMnc;                              /* 当前注册plmn:mnc*/
}CALL_RABM_VOICE_PREFER_CS_EXIST_IND_STRU;


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




