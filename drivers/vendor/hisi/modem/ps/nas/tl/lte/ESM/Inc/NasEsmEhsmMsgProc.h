

#ifndef _NASESMEHSMMSGPROC_H
#define _NASESMEHSMMSGPROC_H



/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include    "vos.h"
#include    "ehsm_esm_pif.h"
#include    "NasEsmPublic.h"


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
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/* ESM管理的EHRPD下的PDN连接信息上限值 */
#define NAS_ESM_EHRPD_PDN_MAX_NUM                                       11

/* ESM在恢复承载过程中第一次发送激活缺省承载失败 */
#define NAS_ESM_FIRST_FAIL_TIME                                         1

/* ESM在EHRPD承载恢复过程中允许激活缺省承载ACP发送失败的最大次数 */
#define NAS_ESM_EHRPD_ALLOW_MAX_SND_FAIL_TIMES                          5

/* 获取EHRPD实体全局变量地址宏定义 */
#define NAS_ESM_GET_EHRPD_ENTITY_ADDR()                     (&g_stEsmEhrpdEntity)

/* 获取和设置EHRPD实体状态 */
#define NAS_ESM_GET_EHRPD_ENTITY_STATE()                    (NAS_ESM_GET_EHRPD_ENTITY_ADDR()->enEntityState)
#define NAS_ESM_SET_EHRPD_ENTITY_STATE(state)               (NAS_ESM_GET_EHRPD_ENTITY_ADDR()->enEntityState = (state))

/* 获取EHRPD实体中正在使用的PDN总数宏定义 */
#define NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM()            (NAS_ESM_GET_EHRPD_ENTITY_ADDR()->ucEhrpdPdnTotalNum)

/* 获取索引为i的EHRPD PDN实体地址 */
#define NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i)                (&(NAS_ESM_GET_EHRPD_ENTITY_ADDR()->astEhrpdPdnEntityList[i]))

/* 获取和设置索引为i的EHRPD PDN实体的attach flag地址 */
#define NAS_ESM_GET_EHRPD_PDN_ENTITY_ATTACH_FLAG(i)                   (NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i)->ucAttachPdnFlag)
#define NAS_ESM_SET_EHRPD_PDN_ENTITY_ATTACH_FLAG(i, ucAttachFlag)     (NAS_ESM_GET_EHRPD_PDN_ENTITY_ATTACH_FLAG(i) = (ucAttachFlag))



/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
 结构名    : NAS_ESM_EHRPD_ENTITY_STATE_ENUM
 结构说明  : ESM的EHRPD实体状态
*****************************************************************************/
enum NAS_ESM_EHRPD_ENTITY_STATE_ENUM
{
    /* 等待恢复态 */
    NAS_ESM_EHRPD_ENTITY_STATE_WAIT_HANDOVER                      = 0x00,

    /* HANDOVER ATTACH的PDN请求未收到网侧响应 */
    NAS_ESM_EHRPD_ENTITY_STATE_ATTACH_PDN_REQ_NOT_RCV_CN_RSP      = 0X01,

    /* 已经收到过网侧的第一条缺省承载激活请求 */
    NAS_ESM_EHRPD_ENTITY_STATE_ALREADY_RCV_FIRST_BEARER_ACT_REQ   = 0x02,

    NAS_ESM_EHRPD_ENTITY_STATE_BUTT
};
typedef VOS_UINT8  NAS_ESM_EHRPD_ENTITY_STATE_ENUM_UINT8;

/*****************************************************************************
 结构名    : NAS_ESM_PDN_RECONNECT_RESULT_ENUM
 结构说明  : ESM的EHRPD PDN连接恢复结果
*****************************************************************************/
enum NAS_ESM_PDN_RECONNECT_RESULT_ENUM
{
    NAS_ESM_PDN_RECONNECT_RESULT_SUCC             = 0x00,   /* 恢复成功 */
    NAS_ESM_PDN_RECONNECT_RESULT_FAIL             = 0x01,   /* 恢复失败 */

    NAS_ESM_PDN_RECONNECT_RESULT_BUTT
};
typedef VOS_UINT8  NAS_ESM_PDN_RECONNECT_RESULT_ENUM_UINT8;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*****************************************************************************
 结构名    : EHSM_ESM_MSG_HEADER_STRU
 结构说明  : EHSM模块发给ESM模块消息头
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    EHSM_ESM_PIF_MSG_TYPE_ENUM_UINT16   enMsgId;
    VOS_UINT16                          usOpId;
} EHSM_ESM_MSG_HEADER_STRU;


/*****************************************************************************
 结构名    : NAS_ESM_EHRPD_NW_MSG_RECORD_STRU
 结构说明  : EHRPD实体记录的发给网络侧空口消息相关信息
*****************************************************************************/
typedef struct
{
    /* SM发给CN的空口消息类型，目前只会记录激活缺省承载ACP，其他类型留作扩展 */
    NAS_ESMCN_MSG_TYPE_ENUM_UINT8       enEsmCnMsgType;
    VOS_UINT8                           ucSendFailTimes;    /* 发送失败次数 */
    VOS_UINT8                           aucRsv[2];          /* 保留 */

    /* L下恢复承载过程中记录发送NW消息的OPID，目前只会记录激活缺省承载ACP的，其他类型留作扩展  */
    VOS_UINT32                          ulNwMsgOpId;

} NAS_ESM_EHRPD_NW_MSG_RECORD_STRU;

/*****************************************************************************
 结构名    : NAS_ESM_EHRPD_PDN_CONTEXT_INFO_STRU
 结构说明  : ESM内部记录的EHRPD下的PDN连接信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpApn          :1;
    VOS_UINT32                          bitOpApnAmbr      :1;
    VOS_UINT32                          bitOpPcoIpv4Item  :1;
    VOS_UINT32                          bitOpPcoIpv6Item  :1;
    VOS_UINT32                          bitOpSpare        :28;

    VOS_UINT32                          ulBitCid;                     /* CID                                   */
    VOS_UINT32                          ulEpsbId;                     /* 承载ID                                */
    EHSM_ESM_PDN_ADDR_STRU              stPdnAddr;
    APP_ESM_APN_INFO_STRU               stApn;                        /* APN格式要注意，此处保存的为ESM内部使用的APN格式 */
    EHSM_ESM_APN_AMBR_STRU              stApnAmbr;
    EHSM_ESM_PCO_IPV4_ITEM_STRU         stPcoIpv4Item;
    EHSM_ESM_PCO_IPV6_ITEM_STRU         stPcoIpv6Item;
} NAS_ESM_EHRPD_PDN_CONTEXT_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_ESM_EHRPD_PDN_ENTITY_STRU
 结构说明  : ESM内部管理每条EHRPD承载的实体结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUsedFlag;         /* 此PDN实体是否被启用: 1启用；0未启用   */
    VOS_UINT8                           ucAttachPdnFlag;    /* 此PDN是否是注册PDN: 1是；0不是        */
    VOS_UINT8                           ucIsOnReconnFlag;   /* 此PDN实体是否处于承载恢复流程中       */
    VOS_UINT8                           ucRsv;

    VOS_UINT32                          ulHandoverEpsbId;   /* L下恢复后网络分配的承载ID             */

    NAS_ESM_EHRPD_NW_MSG_RECORD_STRU    stNwMsgRecord;      /* 空口消息相关记录                      */
    NAS_ESM_TIMER_STRU                  stTimerInfo;        /* 定时器使用信息                        */
    NAS_ESM_EHRPD_PDN_CONTEXT_INFO_STRU stEhPdnContextInfo; /* EHRPD承载上下文信息                   */
} NAS_ESM_EHRPD_PDN_ENTITY_STRU;

/*****************************************************************************
 结构名    : NAS_ESM_EHRPD_ENTITY_STRU
 结构说明  : ESM管理的整个EHRPD实体结构
*****************************************************************************/
typedef struct
{
    NAS_ESM_EHRPD_ENTITY_STATE_ENUM_UINT8         enEntityState;      /* EHRPD实体状态 */

    /* EHRPD实体中记录的PDN总数，此总数仅记录PDN实体列表中有多少个实体被使用
    需注意的是，使用的不一定是前ucEhrpdPdnTotalNum个，这个只是一个总数 */
    VOS_UINT8                                     ucEhrpdPdnTotalNum;
    VOS_UINT8                                     aucRsv[2];          /* 保留                                */

    /* LTE下记录的EHRPD承载实体信息列表 */
    NAS_ESM_EHRPD_PDN_ENTITY_STRU                 astEhrpdPdnEntityList[NAS_ESM_EHRPD_PDN_MAX_NUM];
} NAS_ESM_EHRPD_ENTITY_STRU;


/*****************************************************************************
 结构名    : NAS_ESM_OM_EHRPD_PDN_ENTITY_STRU
 结构说明  : ESM向OM输出的可维可测的PDN实体信息
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                               stMsgHeader;        /*_H2ASN_Skip*/

    NAS_ESM_EHRPD_ENTITY_STATE_ENUM_UINT8         enEntityState;      /* EHRPD实体状态 */
    VOS_UINT8                                     ucEntityIndex;      /* 此PDN实体的索引号，范围0-10 */
    VOS_UINT8                                     ucRsv[2];
    /* LTE下记录的EHRPD承载实体 */
    NAS_ESM_EHRPD_PDN_ENTITY_STRU                 stEhPdnEntityInfo;
} NAS_ESM_OM_EHRPD_PDN_ENTITY_STRU;

/*****************************************************************************
 结构名    : NAS_ESM_OM_EHRPD_PDN_ENTITY_NUM_STRU
 结构说明  : ESM向OM输出的可维可测的PDN实体数量信息
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                               stMsgHeader;        /*_H2ASN_Skip*/

    VOS_UINT32                                    ulEhrpdPdnTotalNum;
} NAS_ESM_OM_EHRPD_PDN_ENTITY_NUM_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

extern NAS_ESM_EHRPD_ENTITY_STRU        g_stEsmEhrpdEntity;


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

extern VOS_VOID NAS_ESM_EhsmMsgDistr(
    VOS_VOID                           *pRcvMsg
);
extern VOS_VOID NAS_ESM_InitEhrpdEntity(VOS_VOID);
extern VOS_VOID NAS_ESM_EhsmSyncPdnInfoMsgProc(
    VOS_VOID                           *pRcvMsg
);
extern VOS_VOID NAS_ESM_EhsmClearAllBearerNotifyMsgProc(
    VOS_VOID                           *pRcvMsg
);
extern VOS_VOID NAS_ESM_EhsmSyncPdnInfoConnectedProc(
    EHSM_ESM_SYNC_PDN_INFO_IND_STRU    *pEhsmMsg
);
extern VOS_VOID NAS_ESM_EhsmSyncPdnInfoModifiedProc(
    EHSM_ESM_SYNC_PDN_INFO_IND_STRU    *pEhsmMsg
);
extern VOS_VOID NAS_ESM_EhsmSyncPdnInfoDisconnectedProc(
    EHSM_ESM_SYNC_PDN_INFO_IND_STRU    *pEhsmMsg
);
extern VOS_VOID NAS_ESM_ClearAllLteDefaultBearerInfoNotInformApsProc(VOS_VOID);
extern VOS_VOID NAS_ESM_ClearAllEhrpdPdnInfoProc(VOS_VOID);
extern VOS_UINT32 NAS_ESM_AllocPdnIndexInEhrpdEntity(
    VOS_UINT32                         *pulIndex
);
extern VOS_VOID NAS_ESM_SaveEhrpdPdnInfo(
    VOS_UINT32                          ulIndex,
    EHSM_ESM_SYNC_PDN_INFO_IND_STRU    *pEhsmMsg
);
extern VOS_VOID NAS_ESM_DeleteEhrpdPdnEntityInfo(
    VOS_UINT32                          ulIndex
);
extern VOS_UINT32 NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId(
    VOS_UINT32                          ulEpsbId,
    VOS_UINT32                         *pulIndex
);
extern VOS_UINT32 NAS_ESM_GetEhrpdPdnEntityIndexBasedCid(
    VOS_UINT32                          ulCid,
    VOS_UINT32                         *pulIndex
);
extern VOS_UINT32 NAS_ESM_GetEhrpdPdnEntityIndexBasedApn(
    const APP_ESM_APN_INFO_STRU        *pstApn,
    VOS_UINT32                         *pulIndex
);
extern VOS_UINT32 NAS_ESM_GetEhrpdPdnEntityIndexBasedOpId(
    VOS_UINT32                          ulOpId,
    VOS_UINT32                         *pulIndex
);
extern VOS_UINT32 NAS_ESM_GetAttachPdnInEhrpdEntity(
    VOS_UINT32                         *pulIndex
);
extern VOS_UINT32 NAS_ESM_GetAttachCidInEhrpdEntity(
    VOS_UINT32                         *pulCid
);
extern VOS_UINT32 NAS_ESM_GetNextReconnectEhrpdPdn(
    VOS_UINT32                         *pulIndex
);
extern VOS_UINT32 NAS_ESM_PerformEhrpdPdnReconnect(
    VOS_UINT32                          ulIndex
);
extern VOS_VOID NAS_ESM_SetEhrpdPdnInfoToSdf(
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara,
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity
);
extern VOS_VOID NAS_ESM_SetEhrpdPdnInfoToSyncPdnInfoMsg
(
    const NAS_ESM_EPSB_CNTXT_INFO_STRU *pstEpsbCntxtInfo,
    ESM_EHSM_SYNC_PDN_INFO_IND_STRU    *pstPdnInfoInd
);
extern VOS_UINT32 NAS_ESM_ConvertBitCidToCid(
    VOS_UINT32                          ulBitCid
);
extern VOS_UINT32 NAS_ESM_IsBackOffAllowedToReconn(
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity
);
extern VOS_UINT32 NAS_ESM_CheckAllowedPdnEntityToReconnect(
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity
);
extern VOS_VOID NAS_ESM_EhrpdPdnConnectHandOverSuccProc(
    VOS_UINT32                          ulIndex
);
extern VOS_VOID NAS_ESM_EhrpdPdnConnectHandOverFailProc(
    VOS_UINT32                          ulIndex
);
extern VOS_VOID NAS_ESM_EhrpdEntityProcEmmSendDataReqSucc(
    VOS_UINT32                          ulOpId
);

extern VOS_VOID NAS_ESM_EhrpdEntityProcEmmSendDataReqFail(
    const EMM_ESM_DATA_CNF_STRU        *pEmmEsmDataCnfMsg
);
extern VOS_VOID NAS_ESM_PerformNextEhrpdPdnReconnectProc(VOS_VOID);
extern VOS_VOID NAS_ESM_WaitHandoverEhrpdPdnRcvApsPdpReleaseProc(
    const APP_ESM_PDP_RELEASE_REQ_STRU *pstAppEsmPdpRelReqMsg,
    VOS_UINT32                          ulIndex
);
extern VOS_VOID NAS_ESM_EhrpdPdnHandoverSuccRcvApsPdpReleaseProc(
    const APP_ESM_PDP_RELEASE_REQ_STRU *pstAppEsmPdpRelReqMsg,
    VOS_UINT32                          ulIndex
);

extern VOS_VOID NAS_ESM_SndEhsmSyncPdnInfoConnIndMsg(
    VOS_UINT32                          ulEpsbId
);

extern VOS_VOID NAS_ESM_SndEhsmSyncPdnInfoModIndMsg(
    VOS_UINT32                          ulEpsbId
);
extern VOS_VOID NAS_ESM_SndEhsmSyncPdnInfoDisconnIndMsg(
    VOS_UINT32                          ulEpsbId
);
extern VOS_VOID NAS_ESM_SndEhsmClearAllBearerNotifyMsg(VOS_VOID);
extern VOS_VOID NAS_ESM_SndApsEhrpdPdnReconnSuccMsg(
    VOS_UINT32                          ulIndex
);
extern VOS_VOID NAS_ESM_SndApsEhrpdPdnReconnFailMsg(
    VOS_UINT32                          ulIndex
);
extern VOS_VOID NAS_ESM_SndApsEhrpdPdnReconnectResultMsg(
    VOS_UINT32                                    ulIndex,
    NAS_ESM_PDN_RECONNECT_RESULT_ENUM_UINT8       enResult
);
extern VOS_VOID NAS_ESM_SndEmmClLocalDetachNotifyMsg(VOS_VOID);
extern VOS_VOID NAS_ESM_SndOmEhrpdUsedPdnEntityNum(VOS_VOID);
extern VOS_VOID NAS_ESM_SndOmEhrpdUsedPdnEntityStateInfo(VOS_VOID);

/*****************************************************************************
  9 OTHERS
*****************************************************************************/
#endif


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

#endif
