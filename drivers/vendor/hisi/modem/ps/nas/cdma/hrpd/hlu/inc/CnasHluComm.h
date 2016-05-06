/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHluComm.h
  版 本 号   : 初稿
  作    者   : s00250401
  生成日期   : 2014年12月18日
  最近修改   :
  功能描述   : CnasHluComm.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月18日
    作    者   : s00250401
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CNAS_HLU_COMM_H__
#define __CNAS_HLU_COMM_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "nas_cttf_hrpd_rsnp_pif.h"

#include "CnasMntn.h"
#include "CnasHluCtx.h"
#include "CnasHluTimerMgmt.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 Marco define
*****************************************************************************/
#define CNAS_HLU_CDMA2000_HRPD_LOC_TYPE      ( 0x01 )
#define CNAS_HLU_CDMA2000_HRPD_LOC_LEN       ( 0x05 )

#define CNAS_HLU_LOC_MSG_PRIORITY            ( 0x28 )


#define CNAS_HLU_CDMA2000_HRPD_LOC_LEN_INV   ( 0x00 )

#define CNAS_HLU_CDMA2000_HRPD_LOC_TYPE_INV  ( 0x00 )
#define CNAS_HLU_CDMA2000_HRPD_BLOB_TYPE_INV ( 0x00 )
#define CNAS_HLU_CDMA2000_HRPD_BLOB_LEN_INV  ( 0x00 )

#define CNAS_HLU_BYTE_LEN                    ( 8 )
#define CNAS_HLU_BYTE_NULL                   ( 0x00 )

#define CNAS_HLU_LOC_REQ_MSG_BIT_LEN         ( 1 * CNAS_HLU_BYTE_LEN )
#define CNAS_HLU_LOC_NOTIF_MSG_BIT_LEN       ( 8 * CNAS_HLU_BYTE_LEN )
#define CNAS_HLU_LOC_ASSIGN_MSG_BIT_LEN      ( 9 * CNAS_HLU_BYTE_LEN )
#define CNAS_HLU_LOC_COMP_MSG_BIT_LEN        ( 2 * CNAS_HLU_BYTE_LEN )
#define CNAS_HLU_NO_LOC_NOTIF_MSG_BIT_LEN    ( 2 * CNAS_HLU_BYTE_LEN )

#define CNAS_HLU_BLOB_TYPE_BIT_LEN           ( 2 * CNAS_HLU_BYTE_LEN )

/* sprint ccf testcase,when LocationType=0, the min length of value is 3 bytes */
#define CNAS_HLU_LOC_ASSIGN_MSG_MIN_BIT_LEN  ( 3 * CNAS_HLU_BYTE_LEN )


/* Defined as per WUEPS_PID_TAF */
#define CNAS_HLU_SID_INVALID            ( 0xFFFF )
#define CNAS_HLU_NID_INVALID            ( 0x00 )
#define CNAS_HLU_PACKET_ZONE_ID_INVALID ( 0xFF )

#define CNAS_HLU_RAN_HANDOFF_IS_SET     ( 1 )
#define CNAS_HLU_RAN_HANDOFF_IS_NOT_SET ( 0 )


/*
C.S0024-A_v3.0_060912.pdf [Section:4.6.4.2.6]
        Field           Length(bits)
    MessageID             8
    StorageBLOBType      16
    StorageBLOBLength     8
    StorageBLOB           0 or 8*StorageBLOBLength
*/
#define CNAS_HLU_BLOB_NOTIF_MSG_BIT_LEN(ucBLOBLen) \
    ( CNAS_HLU_BYTE_LEN \
        + CNAS_HLU_BLOB_TYPE_BIT_LEN \
        + CNAS_HLU_BYTE_LEN \
        + (CNAS_HLU_BYTE_LEN * (ucBLOBLen)))

#define CNAS_HLU_NO_BLOB_NOTIF_MSG_BIT_LEN \
    ( CNAS_HLU_BYTE_LEN + CNAS_HLU_BLOB_TYPE_BIT_LEN + CNAS_HLU_BYTE_LEN )

#define CNAS_HLU_BLOB_ASSG_MSG_BIT_LEN(ucBLOBLen) \
    ( CNAS_HLU_BYTE_LEN \
        + CNAS_HLU_BYTE_LEN \
        + CNAS_HLU_BLOB_TYPE_BIT_LEN \
        + CNAS_HLU_BYTE_LEN \
        + (CNAS_HLU_BYTE_LEN * (ucBLOBLen)))

#define CNAS_HLU_BLOB_COMP_MSG_BIT_LEN  ( 2 * CNAS_HLU_BYTE_LEN )


/* BYTES, Max len of param LocationValue = 8*LocationLength bits,
   where LocationLength = 0x05 is fixed in valid scenario. */
#define CNAS_HLU_LOCATION_MAX_LEN       ( 0x05 )


#define CNAS_HLU_NTOHS(x)               ((((x) & 0x00ff) << 8) \
                                        | (((x) & 0xff00) >> 8))

#define CNAS_HLU_HTONS(x)               ((((x) & 0x00ff) << 8) \
                                        | (((x) & 0xff00) >> 8))

#define CNAS_HLU_STORE_SID_NTOH_S(pusSid, pucLocData) \
{ \
    *(pusSid) = (((*((pucLocData) + 4)) << 8) | (*((pucLocData) + 5))); \
}

#define CNAS_HLU_STORE_NID_NTOH_S(pusNID, pucLocData) \
{ \
    *(pusNID) = (((*((pucLocData) + 6)) << 8) | (*((pucLocData) + 7))); \
}


 /* 记录是否需要进行回复的标识,需根据接口文件进行修改 */
#define CNAS_HLU_FILL_SNP_REQ_MSG(pstSnpDataReq, pstMsgTxInfo, enProtType) \
{ \
    (pstSnpDataReq)->enMsgId            = ID_CNAS_CTTF_HRPD_SNP_DATA_REQ; \
    (pstSnpDataReq)->enProtocolType     = enProtType; \
    (pstSnpDataReq)->enInstanceType     = CTTF_HRPD_INSTANCE_INUSE; \
    (pstSnpDataReq)->enAddressType      = (pstMsgTxInfo)->enAddressType; \
    (pstSnpDataReq)->enChannelType      = (pstMsgTxInfo)->enChannelType; \
    (pstSnpDataReq)->enDeliveryType     = (pstMsgTxInfo)->enDeliveryType; \
    (pstSnpDataReq)->ucPriority         = (pstMsgTxInfo)->ucPriority; \
    (pstSnpDataReq)->enNeedRslt         = CTTF_HRPD_BEST_EFFORT_NEED_RSLT; \
}

#define CNAS_HLU_FILL_MSG_HDR(pstMsg, ulSendrPid, ulRecvrPId) \
{ \
    (pstMsg)->ulSenderCpuId             = VOS_LOCAL_CPUID; \
    (pstMsg)->ulSenderPid               = (ulSendrPid); \
    (pstMsg)->ulReceiverCpuId           = VOS_LOCAL_CPUID; \
    (pstMsg)->ulReceiverPid             = (ulRecvrPId); \
}

#define CNAS_HLU_IS_VALID_PTR(x)        ((x) != VOS_NULL_PTR)
#define CNAS_HLU_IS_NULL_PTR(x)         ((x) == VOS_NULL_PTR)
#define CNAS_HLU_IS_EQUAL(x, y)         ((x) == (y))




/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum CNAS_HLU_LOC_MSG_ID_ENUM
{
    CNAS_HLU_HRPD_LOC_REQUEST                = 0x03,    /* _H2ASN_MsgChoice CNAS_HLU_HRPD_MSG_TYPE_STRU*/
    CNAS_HLU_HRPD_LOC_NOTIFICATION           = 0x04,    /* _H2ASN_MsgChoice CNAS_HLU_HRPD_LOC_NOTF_STRU*/
    CNAS_HLU_HRPD_LOC_ASSIGNMENT             = 0x05,    /* _H2ASN_MsgChoice CNAS_HLU_HRPD_LOC_ASSG_STRU*/
    CNAS_HLU_HRPD_LOC_COMPLETE               = 0x06,    /* _H2ASN_MsgChoice CNAS_HLU_HRPD_MSG_TYPE_STRU*/

    CNAS_HLU_HRPD_BLOB_REQUEST               = 0x10,    /* _H2ASN_MsgChoice CNAS_HLU_HRPD_MSG_TYPE_STRU*/
    CNAS_HLU_HRPD_BLOB_NOTIFICATION          = 0x11,    /* _H2ASN_MsgChoice CNAS_HLU_HRPD_BLOB_NOTF_STRU*/
    CNAS_HLU_HRPD_BLOB_ASSIGNMENT            = 0x12,    /* _H2ASN_MsgChoice CNAS_HLU_HRPD_BLOB_ASSG_STRU*/
    CNAS_HLU_HRPD_BLOB_COMPLETE              = 0x13,    /* _H2ASN_MsgChoice CNAS_HLU_HRPD_MSG_TYPE_STRU*/

    CNAS_HLU_LOC_BUTT
};

typedef VOS_UINT16   CNAS_HLU_LOC_MSG_ID_ENUM_UINT16;


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
    CTTF_HRPD_CHANNEL_TYPE_ENUM_UINT8   enChannelType;
    CTTF_HRPD_DELLIVERY_TYPE_ENUM_UINT8 enDeliveryType;
    CTTF_HRPD_ADDRESS_TYPE_ENUM_UINT8   enAddressType;
    VOS_UINT8                           ucPriority;
}CNAS_HLU_MSG_TX_OPTION_INFO;



typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    CNAS_HLU_LOC_MSG_ID_ENUM_UINT16     enMsgId;            /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;
}CNAS_HLU_HRPD_MSG_TYPE_STRU;


typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    CNAS_HLU_LOC_MSG_ID_ENUM_UINT16     enMsgId;            /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;
    CNAS_HLU_LOC_STRU                   stLocInfo;
}CNAS_HLU_HRPD_LOC_NOTF_STRU;

typedef CNAS_HLU_HRPD_LOC_NOTF_STRU     CNAS_HLU_HRPD_LOC_ASSG_STRU;


typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    CNAS_HLU_LOC_MSG_ID_ENUM_UINT16     enMsgId;            /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;
    CNAS_HLU_BLOB_STRU                  stBlob;
}CNAS_HLU_HRPD_BLOB_NOTF_STRU;

typedef CNAS_HLU_HRPD_BLOB_NOTF_STRU     CNAS_HLU_HRPD_BLOB_ASSG_STRU;

/** ****************************************************************************
 * Name        : HLU_MNTN_MSG_DATA
 * Description : H2ASN top level message structure definition
 *******************************************************************************/
typedef struct
{
    CNAS_HLU_LOC_MSG_ID_ENUM_UINT16     enMsgId;            /* _H2ASN_MsgChoice_Export CNAS_HLU_LOC_MSG_ID_ENUM_UINT16 */
    VOS_UINT8                           aucMsgBlock[2];

    /* _H2ASN_MsgChoice_When_Comment CNAS_HLU_LOC_MSG_ID_ENUM_UINT16 */
}HLU_MNTN_MSG_DATA;

/* _H2ASN_Length UINT32*/
/** ****************************************************************************
 * Name        : HLU_MNTN_MSG
 * Description : H2ASN top level message structure definition
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    HLU_MNTN_MSG_DATA                stMsgData;
}HLU_MNTN_MSG;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_UINT32 CNAS_HLU_DecodeLoc
(
    VOS_UINT8                          *pucData
);

VOS_UINT32 CNAS_HLU_DecodeBLOB
(
    VOS_UINT8                          *pucData
);

VOS_VOID CNAS_HLU_ProcSnpDataInd
(
    SNPITF_MSG_DATA_STRU               *pstMsgData
);

VOS_VOID CNAS_HLU_SndFsig
(
    VOS_UINT8                           ucMsgId
);



VOS_VOID CNAS_HLU_ClearBitInDByte(
    VOS_UINT16                         *usByte,
    VOS_UINT8                           ucBitNo
);

VOS_VOID CNAS_HLU_StartTimer(
    CNAS_HLU_TIMER_ID_ENUM_UINT32       enTimerId,
    VOS_UINT32                          ulTimerLen
);

VOS_VOID CNAS_HLU_StopTimer(
    CNAS_HLU_TIMER_ID_ENUM_UINT32       enTimerId
);

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

#endif /* end of CnasHluCtx.h */
