

#ifndef __NAS_USIMM_API_MNTN_H__
#define __NAS_USIMM_API_MNTN_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "siappstk.h"
#include "UsimPsInterface.h"
#include "siapppb.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)



/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define NAS_USIMM_AUTN_RANDLEN          (17)
#define NAS_USIMM_AUTN_AUTHLEN          (17)
#define NAS_USIMM_AUTH_RAND_LENGTH      (16)
#define NAS_USIMM_AUTH_AUTN_LENGTH      (16)
#define NAS_MO_CTRL_LAI_LEN             (0xf)
#define NAS_USSD_STR_MAX_LEN            (256)
#define NAS_MAX_USIM_FILE_MAX_RECORD    (255)


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum NAS_USIMM_API_MNTN_MSG_ID_ENUM
{
    NAS_LOG_USIMM_API_SET_FILE_REQ                       = 0x2000, /*_H2ASN_MsgChoice NAS_LOG_USIMM_API_SET_FILE_REQ_STRU */
    NAS_LOG_USIMM_API_GET_FILE_REQ                               , /*_H2ASN_MsgChoice NAS_LOG_USIMM_API_GET_FILE_REQ_STRU */
    NAS_LOG_USIMM_API_AUTH_REQ                                   , /*_H2ASN_MsgChoice NAS_LOG_USIMM_API_AUTH_REQ_STRU */
    NAS_LOG_USIMM_API_PIN_REQ                                    , /*_H2ASN_MsgChoice NAS_LOG_USIMM_API_PIN_REQ_STRU */
    NAS_LOG_USIMM_API_MAX_EFRECORD_NUM_REQ                       , /*_H2ASN_MsgChoice NAS_LOG_USIMM_API_MAX_EFRECORD_NUM_REQ_STRU*/
    NAS_LOG_USIMM_API_IS_TEST_CARD                               , /*_H2ASN_MsgChoice NAS_LOG_USIMM_API_IS_TEST_CARD_STRU */
    NAS_LOG_USIMM_API_GET_PIN_STATUS                             , /*_H2ASN_MsgChoice NAS_LOG_USIMM_API_GET_PIN_STATUS_STRU */
    NAS_LOG_USIMM_API_GET_CARD_TYPE                              , /*_H2ASN_MsgChoice NAS_LOG_USIMM_API_GET_CARD_TYPE_STRU */
    NAS_LOG_USIMM_API_GET_CACHED_FILE                            , /*_H2ASN_MsgChoice NAS_LOG_USIMM_API_GET_CACHED_FILE_STRU */
    NAS_LOG_USIMM_API_IS_SERVICE_AVAILABLE                       , /*_H2ASN_MsgChoice NAS_LOG_USIMM_API_IS_SERVICE_AVAILABLE_STRU */
    NAS_LOG_USIMM_API_GET_CARD_IMSI                              , /*_H2ASN_MsgChoice NAS_LOG_USIMM_API_GET_CARD_IMSI_STRU */
    NAS_LOG_USIMM_API_BDN_QUERY                                  , /*_H2ASN_MsgChoice NAS_LOG_USIMM_API_BDN_QUERY_STRU */
    NAS_LOG_USIMM_API_FDN_QUERY                                  , /*_H2ASN_MsgChoice NAS_LOG_USIMM_API_FDN_QUERY_STRU */
    NAS_LOG_USIMM_API_GET_PIN_REMAIN_TIME                        , /*_H2ASN_MsgChoice NAS_LOG_USIMM_API_GET_PIN_REMAIN_TIME_STRU */
    NAS_LOG_USIMM_API_DEACTIVE_CARD_REQ                          , /*_H2ASN_MsgChoice NAS_LOG_USIMM_API_DEACTIVE_CARD_REQ_STRU */
    NAS_LOG_PIH_API_REG_USIM_CARD_STATUS_IND                     , /*_H2ASN_MsgChoice NAS_LOG_PIH_API_REG_USIM_CARD_STATUS_IND_STRU */
    NAS_LOG_PIH_API_DEREG_USIM_CARD_STATUS_IND                   , /*_H2ASN_MsgChoice NAS_LOG_PIH_API_REG_USIM_CARD_STATUS_IND_STRU*/
    NAS_LOG_PIH_API_REG_CARD_REFRESH_IND                         , /*_H2ASN_MsgChoice NAS_LOG_PIH_API_REG_CARD_REFRESH_IND_STRU */
    NAS_LOG_PIH_API_DEREG_CARD_REFRESH_IND                       , /*_H2ASN_MsgChoice NAS_LOG_PIH_API_REG_CARD_REFRESH_IND_STRU */
    NAS_LOG_PB_API_GET_ECC_NUM                                   , /*_H2ASN_MsgChoice NAS_LOG_PB_API_GET_ECC_NUMBER_STRU */
    NAS_LOG_STK_API_MT_CALL_EVENT                                , /*_H2ASN_MsgChoice NAS_LOG_STK_API_MT_CALL_CALL_EVENT_STRU */
    NAS_LOG_STK_API_CALL_CONNECT_EVENT                           , /*_H2ASN_MsgChoice NAS_LOG_STK_API_CALL_CONNECT_EVENT_STRU */
    NAS_LOG_STK_API_CALL_DISCONNECT_EVENT                        , /*_H2ASN_MsgChoice NAS_LOG_STK_API_CALL_DISCONNECT_EVENT_STRU*/
    NAS_LOG_STK_API_LOCI_EVENT                                   , /*_H2ASN_MsgChoice NAS_LOG_STK_API_LOCIS_EVENT_STRU */
    NAS_LOG_STK_API_ACC_CHANGE_EVENT                             , /*_H2ASN_MsgChoice NAS_LOG_STK_API_ACC_CHANGE_EVENT_STRU*/
    NAS_LOG_STK_API_NET_SEARCH_CHANGE_EVENT                      , /*_H2ASN_MsgChoice NAS_LOG_STK_API_NET_SEARCH_CHANGE_EVENT_STRU */
    NAS_LOG_PB_API_FDN_NUM_CHECK                                 , /*_H2ASN_MsgChoice NAS_LOG_PB_API_FDN_NUM_CHECK_STRU */
    NAS_LOG_STK_API_ENVELOP_RSP_DECODE                           , /*_H2ASN_MsgChoice NAS_LOG_STK_API_ENVELOP_RSP_DECODE_STRU */
    NAS_LOG_STK_API_ENVELOP_RSP_DATA_FREE                        , /*_H2ASN_MsgChoice NAS_LOG_STK_API_ENVELOP_RSP_DATA_FREE_STRU */
    NAS_LOG_STK_API_ENVELOP_DOWNLOAD                             , /*_H2ASN_MsgChoice NAS_LOG_STK_API_ENVELOP_DOWNLOAD_STRU */
    NAS_LOG_STK_API_CC_RESULT_IND                                , /*_H2ASN_MsgChoice NAS_LOG_STK_API_CC_RESULT_IND_STRU */
    NAS_LOG_STK_API_SMS_CTRL_RESULT_IND                          , /*_H2ASN_MsgChoice NAS_LOG_STK_API_SMS_CTRL_RESULT_IND_STRU */
    NAS_LOG_VSIM_CTRL_INFO                                       , /*_H2ASN_MsgChoice TAF_SDC_VSIM_CTRL_INFO_STRU */
    NAS_LOG_PB_API_QRY_ECALL_NUM                                 , /*_H2ASN_MsgChoice NAS_LOG_PB_API_QRY_ECALL_NUM_STRU */
    NAS_LOG_STK_API_ENVELOP_DOWN_CODE                            ,
    NAS_LOG_PB_API_GET_XECC_NUM                                  ,

    NAS_LOG_USIMM_API_BUTT
};
typedef VOS_UINT32 NAS_USIMM_API_MNTN_MSG_ID_ENUM_UINT32;


enum NAS_USIMM_API_TYPE_ENUM
{
    NAS_USIMM_API_TYPE_WITH_INSTANCE,                                           /* 调用带INSTANCE的API */
    NAS_USIMM_API_TYPE_WITHOUT_INSTANCE,                                        /* 调用不带INSTANCE的API */
    NAS_USIMM_API_TYPE_BUTT
};
typedef VOS_UINT8 NAS_USIMM_API_TYPE_ENUM_UINT8;

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
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */        /*_H2ASN_Skip*/
    VOS_UINT32                          ulVsimModem;
    VOS_UINT8                           ucVsimCtrlFlg;
    VOS_UINT8                           aucReserved1[3];
}NAS_LOG_VSIM_CTRL_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucPinType;                              /* PIN类型 */
    VOS_UINT8                           ucPinBeEnable;                          /* PIN是否开启 */
    VOS_UINT8                           ucPinBeNeed;                            /* PIN是否需要 */
    VOS_UINT8                           ucPinRemainNum;                         /* PIN剩余次数 */
}NAS_PIN_STATUS_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserved[3];
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    VOS_UINT16                          usFileID;
    VOS_UINT16                          usDataLen;
    VOS_UINT8                           ucRecordNum;
    VOS_UINT8                           aucContent[3];
}NAS_LOG_USIMM_API_SET_FILE_REQ_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserved[3];
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    VOS_UINT16                          usEfId;
    VOS_UINT16                          usRev;
}NAS_LOG_USIMM_API_MAX_EFRECORD_NUM_REQ_STRU;




typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserved[3];
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    VOS_UINT16                          usFileID;
    VOS_UINT8                           ucRecordNum;
    VOS_UINT8                           ucReserved;
}NAS_LOG_USIMM_API_GET_FILE_REQ_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserved[3];
    USIMM_AUTH_TYPE_ENUM_UINT32         enChallengeType;
    VOS_UINT8                           aucRand[NAS_USIMM_AUTN_RANDLEN];
    VOS_UINT8                           aucReserved1[3];
    VOS_UINT8                           aucAUTN[NAS_USIMM_AUTN_AUTHLEN];
    VOS_UINT8                           aucReserved2[3];
}NAS_LOG_USIMM_API_AUTH_REQ_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
    NAS_PIN_STATUS_STRU                 stPinStatus;
}NAS_LOG_USIMM_API_GET_PIN_STATUS_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           ucCardStatus;
    VOS_UINT16                          usCardType;
}NAS_LOG_USIMM_API_GET_CARD_TYPE_STRU;



typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头                                   */ /*_H2ASN_Skip*/
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulUsimState;
    VOS_UINT32                          ulCsimState;
}NAS_LOG_USIMM_API_BDN_QUERY_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
    USIMM_PIN_REMAIN_STRU               stRemainTime;
}NAS_LOG_USIMM_API_GET_PIN_REMAIN_TIME_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulRegPID;
}NAS_LOG_PIH_API_REG_USIM_CARD_STATUS_IND_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
}NAS_LOG_USIMM_API_IS_TEST_CARD_STRU;


typedef struct
{
    USIMM_PIN_CMD_TYPE_ENUM_UINT32      enCmdType;
    USIMM_PIN_TYPE_ENUM_UINT32          enPINType;
    VOS_UINT8                           aucOldPIN[USIMM_PINNUMBER_LEN];
    VOS_UINT8                           aucNewPIN[USIMM_PINNUMBER_LEN];
}NAS_LOG_USIMM_PIN_INFO_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
    NAS_LOG_USIMM_PIN_INFO_STRU         stPinInfo;
}NAS_LOG_USIMM_API_PIN_REQ_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucRsv[3];
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    VOS_UINT16                          usFileID;
    VOS_UINT16                          usDataLen;
    VOS_UINT8                           aucContent[4];
}NAS_LOG_USIMM_API_GET_CACHED_FILE_STRU;


typedef struct
{
    VOS_UINT16                          usFileID;
    VOS_UINT32                          ulDataLen;
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    VOS_UINT8                           aucContent[4];
}NAS_LOG_CACHED_FILE_INFO_STRU;


typedef NAS_LOG_USIMM_API_BDN_QUERY_STRU                NAS_LOG_USIMM_API_FDN_QUERY_STRU;
typedef NAS_LOG_PIH_API_REG_USIM_CARD_STATUS_IND_STRU   NAS_LOG_PIH_DEREG_USIM_CARD_STATUS_IND_STRU;



typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulRegPID;
}NAS_LOG_PIH_API_REG_CARD_REFRESH_IND_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulDeregPID;
}NAS_LOG_PIH_API_DEREG_CARD_REFERESH_IND_STRU;



typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
    SI_PB_ECC_DATA_STRU                 stEccData;
}NAS_LOG_PB_API_GET_ECC_NUMBER_STRU;


typedef NAS_LOG_PB_API_GET_ECC_NUMBER_STRU NAS_LOG_PB_API_GET_XECC_NUMBER_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头 */        /*_H2ASN_Skip*/
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
    SI_STK_MT_CALL_EVENT_STRU           stCallEvent;
}NAS_LOG_STK_API_MT_CALL_CALL_EVENT_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头 */        /*_H2ASN_Skip*/
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           ucSDId;
    VOS_UINT8                           aucReserve[2];
    SI_STK_CALL_CONNECTED_EVENT_STRU    stCallConnectedEvent;
}NAS_LOG_STK_API_CALL_CONNECT_EVENT_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头 */        /*_H2ASN_Skip*/
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           ucSDId;
    VOS_UINT8                           aucReserve[2];
    SI_STK_CALL_DISCONNECTED_EVENT_STRU stCallDisconnectedEvent;
}NAS_LOG_STK_API_CALL_DISCONNECT_EVENT_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头 */        /*_H2ASN_Skip*/
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
}NAS_LOG_STK_API_LOCIS_EVENT_STRU;


typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;
    NAS_USIMM_API_TYPE_ENUM_UINT8                           enApiType;
    VOS_UINT8                                               aucReserve[3];
    SI_STK_ACCESS_TECHNOLOGY_CHANGE_EVENT_STRU              stSTKAccTCHangeEvent;
}NAS_LOG_STK_API_ACC_CHANGE_EVENT_STRU;


typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;        /* 消息头 */        /*_H2ASN_Skip*/
    NAS_USIMM_API_TYPE_ENUM_UINT8                           enApiType;
    VOS_UINT8                                               aucReserve[3];
    SI_STK_NETWORK_SEARCH_MODE_CHANGE_EVENT_STRU            stNetSearchModeEvent;
}NAS_LOG_STK_API_NET_SEARCH_CHANGE_EVENT_STRU;


typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;        /* 消息头 */        /*_H2ASN_Skip*/
    NAS_USIMM_API_TYPE_ENUM_UINT8                           enApiType;
    VOS_UINT8                                               aucReserve1[3];
    VOS_UINT32                                              ulRslt;
    VOS_UINT8                                               aucImsi[USIMM_EF_IMSI_LEN];
    VOS_UINT8                                               aucReserv2[3];
}NAS_LOG_USIMM_API_GET_CARD_IMSI_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头                                   */ /*_H2ASN_Skip*/
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
    UICC_SERVICES_TYPE_ENUM_UINT32      enService;
    VOS_UINT32                          ulRslt;
}NAS_LOG_USIMM_API_IS_SERVICE_AVAILABLE_STRU;



typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
    SI_PB_FDN_NUM_STRU                  stFdnNum;
}NAS_LOG_PB_API_FDN_NUM_CHECK_STRU;



typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucRsv[3];
    SI_PB_STORATE_TYPE                  enPbType;
    VOS_UINT8                           ucListLen;
    VOS_UINT8                           aucList[NAS_MAX_USIM_FILE_MAX_RECORD];
}NAS_LOG_PB_API_QRY_ECALL_NUM_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头                                   */ /*_H2ASN_Skip*/
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
    SI_STK_ENVELOPE_RSP_STRU            stEvelopRsp;
}NAS_LOG_STK_API_ENVELOP_RSP_DATA_FREE_STRU;



typedef struct
{
    VOS_UINT8                           ucTag;
    VOS_UINT8                           ucLen;
    VOS_UINT8                           aucRsv[2];
    VOS_UINT8                           aucSpecialData[NAS_USSD_STR_MAX_LEN];
}NAS_CALL_CTRL_SPECIAL_STRU;


typedef struct
{
    VOS_UINT32                          ulLen;
    VOS_UINT8                           aucATSLI[NAS_MO_CTRL_LAI_LEN];
    VOS_UINT8                           aucRsv[3];
}NAS_LOCATION_INFO_STRU;



typedef struct
{
    VOS_UINT32                          OP_Capability1:1;
    VOS_UINT32                          OP_Subaddr:1;
    VOS_UINT32                          OP_LocInfo:1;
    VOS_UINT32                          OP_Capability2:1;
    VOS_UINT32                          OP_BCRepInd:1;
    VOS_UINT32                          OP_SepcialData:1;
    VOS_UINT32                          OP_Reserved:26;

    NAS_LOCATION_INFO_STRU              stLocInfo;
    NAS_CALL_CTRL_SPECIAL_STRU          stSpecialData;
}NAS_CALL_CONTROL_STRU;



typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulSendPara;
    NAS_CALL_CONTROL_STRU               stCallCtrl;
    SI_STK_ENVELOPE_TYPE_UINT32         enEnvelopeType;
    SI_STK_DEVICE_IDENTITIES_STRU       stDeviceId;
    VOS_UINT8                           aucData[SI_STK_DATA_MAX_LEN];
}NAS_LOG_STK_API_ENVELOP_DOWNLOAD_STRU;


typedef struct
{
    VOS_UINT32                          OP_CCP1:1;
    VOS_UINT32                          OP_SubAddr:1;
    VOS_UINT32                          OP_Alaph:1;
    VOS_UINT32                          OP_BCRepInd:1;
    VOS_UINT32                          OP_CCP2:1;
    VOS_UINT32                          OP_SepcialData:1;
    VOS_UINT32                          OP_Reserved:26;

    NAS_CALL_CTRL_SPECIAL_STRU          stSpecialData;
}NAS_CALL_CTRL_RSP_STRU;



typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
    NAS_CALL_CTRL_RSP_STRU              stCallCtrlRslt;
    SI_STK_ENVELOPE_TYPE_UINT32         enEnvelopeType;
    VOS_UINT32                          ulResult;
}NAS_LOG_STK_API_ENVELOP_RSP_DECODE_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT8                           aucEvent[256];
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulOffSet;
}NAS_LOG_STK_API_ENVELOP_DOWN_CODE_STRU;



typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
}NAS_LOG_USIMM_API_DEACTIVE_CARD_REQ_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头                                   */ /*_H2ASN_Skip*/
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
    SI_STK_ENVELOPE_RSP_STRU            stRspData;
}NAS_LOG_STK_API_CC_RESULT_IND_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头                                   */ /*_H2ASN_Skip*/
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
    SI_STK_ENVELOPE_RSP_STRU            stRspData;
}NAS_LOG_STK_API_SMS_CTRL_RESULT_IND_STRU;

typedef struct
{
    USIMM_CARDAPP_ENUM_UINT32   enAppType;      /* 应用类型 */
    VOS_UINT16                  usEfId;         /* 文件ID */
    VOS_UINT8                   ucRecordNum;    /* 文件记录号，二进制文件填0 */
    VOS_UINT8                   ucRsv;          /* 保留 */
}NAS_USIMM_MNTN_GETFILE_INFO_STRU;


typedef struct
{
    USIMM_CARDAPP_ENUM_UINT32   enAppType;      /* 应用类型 */
    VOS_UINT16                  usEfId;         /* 文件ID */
    VOS_UINT8                   ucRecordNum;    /* 文件记录号，二进制文件填0 */
    VOS_UINT8                   ucRsv;          /* 保留 */
    VOS_UINT32                  ulEfLen;        /* 更新数据长度 */
    VOS_UINT8                  *pucEfContent;   /* 更新数据内容 */
}NAS_USIMM_MNTN_SETFILE_INFO_STRU;

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
    NAS_USIMM_API_MNTN_MSG_ID_ENUM_UINT32      enMsgId;                         /* _H2ASN_MsgChoice_Export NAS_USIMM_API_MNTN_MSG_ID_ENUM_UINT32 */
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          NAS_USIMM_API_MNTN_MSG_ID_ENUM_UINT32
    ****************************************************************************/
} NAS_USIMM_API_MNTN_MSG_DATA;
/* _H2ASN_Length UINT32 */

typedef struct
{
    VOS_MSG_HEADER
    NAS_USIMM_API_MNTN_MSG_DATA         stMsgData;
} NasUsimmApiMntn_MSG;



/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern VOS_VOID DIAG_TraceReport(VOS_VOID *pMsg);

VOS_VOID  NAS_LogUsimmApiSetFileReq(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    NAS_USIMM_MNTN_SETFILE_INFO_STRU   *pstSetFileInfo
);
VOS_VOID  NAS_LogUsimmApiGetFileReq(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    NAS_USIMM_MNTN_GETFILE_INFO_STRU   *pstGetFileInfo
);
VOS_VOID  NAS_LogUsimmApiAuthReq(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    VOS_UINT8                           ucChallengeType,
    VOS_UINT8                          *pucRand,
    VOS_UINT8                          *pucAutn
);
VOS_VOID  NAS_LogUsimmApiPinReq(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    NAS_LOG_USIMM_PIN_INFO_STRU        *pstPinInfo
);
VOS_VOID  NAS_LogUsimmApiMaxEFRecordNumReq(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT16                          usEFid
);
VOS_VOID  NAS_LogUsimmApiIsTestCard(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType
);
VOS_VOID  NAS_LogUsimmApiGetPinStatus(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    NAS_PIN_STATUS_STRU                *pstPinStatus
);

VOS_VOID  NAS_LogUsimmApiIsServiceAvailable(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    UICC_SERVICES_TYPE_ENUM_UINT32      enService
);


VOS_VOID  NAS_LogUsimmApiGetCachedFile(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                         **ppucData
);
VOS_VOID  NAS_LogUsimmApiGetCardIMSI(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    VOS_UINT8                          *pucImsi
);

VOS_VOID  NAS_LogUsimmApiGetCardType(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    VOS_UINT8                           ucCardStatus,
    VOS_UINT16                          ucCardType
);

VOS_VOID  NAS_LogUsimmApiBdnQuery(
    VOS_UINT32                          ulState,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType
);
VOS_VOID  NAS_LogUsimmApiFdnQuery(
    VOS_UINT32                          ulUsimState,
    VOS_UINT32                          ulCsimState,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType
);

VOS_VOID  NAS_LogUsimmApiGetPinRemainTime(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    USIMM_PIN_REMAIN_STRU              *pstRemainTime
);
VOS_VOID  NAS_LogPihApiRegUsimCardStatusInd(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    VOS_UINT32                          ulRegPid
);

VOS_VOID  NAS_LogPihApiDeregUsimCardStatusInd(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    VOS_UINT32                          ulDeregId
);

VOS_VOID  NAS_LogPihApiRegCardRefreshInd(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    VOS_UINT32                          ulRegId
);

VOS_VOID  NAS_LogPihApiDeregCardRefreshInd(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    VOS_UINT32                          ulDeregPID
);

VOS_VOID  NAS_LogPbApiGetEccNumber(
    VOS_UINT32                           ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    SI_PB_ECC_DATA_STRU                *pstEccData
);


VOS_VOID  NAS_LogPbApiGetXeccNumber(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    SI_PB_ECC_DATA_STRU                *pstEccData
);

VOS_VOID  NAS_LogPbApiFdnNumCheck(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    SI_PB_FDN_NUM_STRU                 *pstFdnNum
);

VOS_VOID  NAS_LogStkApiEnvelopRspDecode(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    SI_STK_ENVELOPE_RSP_STRU           *pstEnvelopeRsp
);

VOS_VOID  NAS_LogStkApiEnvelopReqCode(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    VOS_UINT8                          *pucEvent,
    VOS_UINT32                          ulDataLen,
    VOS_UINT32                          ulOffSet
);

VOS_VOID  NAS_LogStkApiEnvelopRspDataFree(
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    SI_STK_ENVELOPE_RSP_STRU           *pstEnvelopeRsp
);

VOS_VOID  NAS_LogStkApiEnvelopDownload(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    VOS_UINT32                          ulSendPara,
    SI_STK_ENVELOPE_STRU               *pstENStru
);

VOS_VOID  NAS_LogUsimmApiDeactiveCardReq(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType
);

VOS_VOID  NAS_LogSTKApiCCResultInd(
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    SI_STK_ENVELOPE_RSP_STRU           *pstRspData
);


VOS_VOID  NAS_LogSTKApiSMSCtrlResultInd(
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    SI_STK_ENVELOPE_RSP_STRU           *pstRspData
);

VOS_VOID NAS_LogVsimIsRequireVsimCtrl(
    VOS_UINT32                          ulVsimModem,
    VOS_UINT8                           ucVsimCtrlFlg
);

VOS_VOID  NAS_LogPbApiQryEcallNumber(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    SI_PB_STORATE_TYPE                  enPbType,
    VOS_UINT8                           ucListLen,
    VOS_UINT8                          *pucList
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

#endif /* end of TafSpmMntn.h */

