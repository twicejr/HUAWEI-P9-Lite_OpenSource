
#ifndef      _PPPC_EAP_AKA_H_
#define      _PPPC_EAP_AKA_H_

#ifdef      __cplusplus
extern "C" {
#endif      /* end of __cplusplus */

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "AtPppInterface.h"
#include "PsCommonDef.h"
#include "product_config.h"
#include "TTFUtil.h"
#include "v_IO.h"
#include "TTFComm.h"
#include "TTFLink.h"
#include "PsTypeDef.h"
#include "UsimPsInterface.h"

#include "TtfDrvInterface.h"
#include "pppc_uim.h"
#include "TtfIpComm.h"
#include "pppc_sha1.h"
#include "pppc_sha256.h"
#include "pppc_aes.h"
#include "pppc_eap_typ.h"
#include "ppp_dbug.h"


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* EAP 消息头部长度 */
#define PPPC_EAP_HEADER_LEN                             (4)

/* EAP-AKA Subtypes "RFC4187 Page671" */
#define PPPC_EAP_AKA_SUBTYPE_CHALLENGE                  (1)
#define PPPC_EAP_AKA_SUBTYPE_AUTHENTICATION_REJECT      (2)
#define PPPC_EAP_AKA_SUBTYPE_SYNCHRONIZATION_FAILURE    (4)
#define PPPC_EAP_AKA_SUBTYPE_IDENTITY                   (5)
#define PPPC_EAP_AKA_SUBTYPE_NOTIFICATION               (12)
#define PPPC_EAP_AKA_SUBTYPE_REAUTHENTICATION           (13)
#define PPPC_EAP_AKA_SUBTYPE_CLIENT_ERROR               (14)


/* EAP-AKA and EAP-AKA' Attributes (0..127 non-skippable) */
#define PPPC_EAP_AKA_AT_RAND                            (1)
#define PPPC_EAP_AKA_AT_AUTN                            (2) /* only AKA */
#define PPPC_EAP_AKA_AT_RES                             (3) /* only AKA, only peer->server */
#define PPPC_EAP_AKA_AT_AUTS                            (4) /* only AKA, only peer->server */
#define PPPC_EAP_AKA_AT_PADDING                         (6) /* only encrypted */
#define PPPC_EAP_AKA_AT_PERMANENT_ID_REQ                (10)
#define PPPC_EAP_AKA_AT_MAC                             (11)
#define PPPC_EAP_AKA_AT_NOTIFICATION                    (12)
#define PPPC_EAP_AKA_AT_ANY_ID_REQ                      (13)
#define PPPC_EAP_AKA_AT_IDENTITY                        (14) /* only send */
#define PPPC_EAP_AKA_AT_FULLAUTH_ID_REQ                 (17)
#define PPPC_EAP_AKA_AT_COUNTER                         (19) /* only encrypted */
#define PPPC_EAP_AKA_AT_COUNTER_TOO_SMALL               (20) /* only encrypted */
#define PPPC_EAP_AKA_AT_NONCE_S                         (21) /* only encrypted */
#define PPPC_EAP_AKA_AT_CLIENT_ERROR_CODE               (22) /* only send */
#define PPPC_EAP_AKA_AT_KDF_INPUT                       (23) /* only AKA' */
#define PPPC_EAP_AKA_AT_KDF                             (24) /* only AKA' */
#define PPPC_EAP_AKA_AT_IV                              (129)
#define PPPC_EAP_AKA_AT_ENCR_DATA                       (130)
#define PPPC_EAP_AKA_AT_NEXT_PSEUDONYM                  (132) /* only encrypted */
#define PPPC_EAP_AKA_AT_NEXT_REAUTH_ID                  (133) /* only encrypted */
#define PPPC_EAP_AKA_AT_CHECKCODE                       (134)
#define PPPC_EAP_AKA_AT_RESULT_IND                      (135)
#define PPPC_EAP_AKA_AT_BIDDING                         (136)


/* AT_NOTIFICATION notification code values */
#define PPPC_EAP_AKA_GENERAL_FAILURE_AFTER_AUTH         (0)
#define PPPC_EAP_AKA_TEMPORARILY_DENIED                 (1026)
#define PPPC_EAP_AKA_NOT_SUBSCRIBED                     (1031)
#define PPPC_EAP_AKA_GENERAL_FAILURE_BEFORE_AUTH        (16384)
#define PPPC_EAP_AKA_SUCCESS                            (32768)

/* EAP-AKA' AT_KDF Key Derivation Function values */
#define PPPC_EAP_AKA_PRIME_KDF                          (1)

/* AT_CLIENT_ERROR_CODE error codes */
#define PPPC_EAP_AKA_UNABLE_TO_PROCESS_PACKET           (0)

/* IK的长度 */
#define PPPC_EAP_AKA_IK_LEN                             (16)

/* CK的长度 */
#define PPPC_EAP_AKA_CK_LEN                             (16)

/* K_encr的长度 */
#define PPPC_EAP_AKA_K_ENCR_LEN                         (16)

/* EAP_AKA中K_aut的长度 */
#define PPPC_EAP_AKA_K_AUT_LEN                          (16)

/* EAP_AKA'中K_aut的长度 */
#define PPPC_EAP_AKA_PRIME_K_AUT_LEN                    (32)

/* EAP_AKA'中K_re的长度 */
#define PPPC_EAP_AKA_PRIME_K_RE_LEN                     (32)

/* MKS的长度 */
#define PPPC_EAP_AKA_MSK_LEN                            (64)

/* EMSK的长度 */
#define PPPC_EAP_AKA_EMSK_LEN                           (64)

/* NONCE_S的长度 */
#define PPPC_EAP_AKA_NONCE_S_LEN                        (16)

/* CHECK CODE的最大长度 */
#define PPPC_EAP_AKA_CHECKCODE_MAX_LEN                  (32)

/* CHECK CODE的最小长度 */
#define PPPC_EAP_AKA_CHECKCODE_MIN_LEN                  (20)

/* AT_NOTIFICATION的value长度 */
#define PPPC_EAP_AKA_AT_NOTIFICATION_VALUE_LEN           (2)

/* AT_COUNTER的value长度 */
#define PPPC_EAP_AKA_AT_COUNTER_VALUE_LEN                (2)

/* AT_KDF的value长度 */
#define PPPC_EAP_AKA_AT_KDF_VALUE_LEN                    (2)

/* AT_RESULT_IND的value长度 */
#define PPPC_EAP_AKA_AT_RESULT_IND_VALUE_LEN             (2)


/*AT_BIDDING的value长度 */
#define PPPC_EAP_AKA_AT_BIDDING_VALUE_LEN                (2)


/* 解AT_ENCR_DATA属性需要用到的中间值 */
#define PPPC_EAP_AKA_16_BYTE                             (16)



/* 网络名称的最大长度 */
#define PPPC_EAP_AKA_NETNAME_MAX_LEN                    (256)

/* MK的长度 */
#define PPPC_EAP_AKA_MK_LEN                             (20)

/* RAND的长度 */
#define PPPC_EAP_AKA_RAND_LEN                           (16)

/* AUTN的长度 */
#define PPPC_EAP_AKA_AUTN_LEN                           (16)

/* AUTS的长度 */
#define PPPC_EAP_AKA_AUTS_LEN                           (14)

/* AT_MAC value的长度 */
#define PPPC_EAP_AKA_MAC_VALUE_LEN                      (16)

/* AT_MAC 总的长度 */
#define PPPC_EAP_AKA_MAC_TOTAL_LEN                      (20)

/* HASH算法算出来的MAC最大长度 */
#define PPPC_EAP_AKA_MAC_MAX_LEN                        (32)

/* AT_IV value的长度 */
#define PPPC_EAP_AKA_IV_LEN                             (16)

/* KDF 的最大个数 */
#define PPPC_EAP_AKA_PRIME_KDF_MAX                      (10)

/**************************************************************************
RFC4282:Support for an NAI length of 253 octets is RECOMMENDED.
RFC1421:This line length is easily printable and is gurateed to satisfy SMTP's
        1000-character transmitted line length limit.
**************************************************************************/
#define PPPC_EAP_AKA_IDENTITY_REC_LEN                   (253)                               /* NAI的推荐长度 */

/* 所有IDENTITY的最大长度, 它是依据PPPC_EAP_AKA_IDENTITY_REC_LEN定义出来的
   本来将其定义为PPPC_EAP_AKA_IDENTITY_REC_LEN的大小就够了, 但考虑使用它时,
   会跟真实长度放在一起, 即出现在结构体中,
   因此IDENTITY占用的空间按照4字节对齐, 就是256 */
#define PPPC_EAP_AKA_IDENTITY_MAX_LEN                   (256)

/* 加密数据的最大长度AT_NEXT_PSEUDONYM(260)+AT_NEXT_REAUTH_ID(260)+AT_COUNTER(4)+AT_NONCE_S(20) */
#define PPPC_EAP_AKA_ENRC_DATA_LEN                      (544)

/* 所有IdMsg消息的最大长度3*(Identity_Request + Identity_Response), 即(260+8)*3 + (4+8)*3 */
#define PPPC_EAP_AKA_ID_MSG_MAX_LEN                     (840)

/* ATTRIBUTE偏移量(指Attribute Type + Length域所占用的字节数) */
#define PPPC_EAP_AKA_ATTRIBUTE_TYPE_VALUE_OFFSET         (2)

/* ATTRIBUTE偏移量的偏移量(有的属性有Rerseved域, 指这个域所占用的字节数) */
#define PPPC_EAP_AKA_ATTRIBUTE_RESERVED_VALUE_OFFSET     (2)

/* AKA CHECKCODE value 长度 */
#define PPPC_EAP_AKA_CHECKCODE_LEN                       (20)

/* AKA’CHECKCODE value 长度 */
#define PPPC_EAP_AKA_PRIME_CHECKCODE_LEN                 (32)

/* AT_PADDING的最大长度 */
#define PPPC_EAP_AKA_PADDING_MAX_LEN                     (12)

/* 最大的EAP报文长度 */
#define PPPC_EAP_MAX_PACKET_LEN                          (512)

/* EAP_AKA'重鉴权中MK的长度 */
#define PPPC_EAP_AKA_REAUTH_MK_LEN                       (128)

/* EAP_AKA'计算MK时"EAP-AKA'"的长度 */
#define PPPC_EAP_AKA_PRF_STR_LEN                          (8)

/* EAP_AKA'重鉴权EAP-AKA' re-auth"的长度 */
#define PPPC_EAP_AKA_REAUTH_PRF_STR_LEN                   (16)

/* EAP_AKA计算Key时Buf的长度 */
#define PPPC_EAP_AKA_BUF_LEN                             (160)

/* SQN的长度 */
#define PPPC_EAP_AKA_SQN_LEN                              (6)

/* IK|CK的长度 */
#define PPPC_EAP_AKA_IK_AND_CK_LEN                        (32)

/* 计算IK',CK'时S中L0,L1的长度 */
#define PPPC_EAP_AKA_S_L_LEN                              (2)

/* AT_COUNTER value所占的字节长度 */
#define PPPC_EAP_AKA_COUNTER_LEN                          (2)

/* EAP_AKA'中MK的长度 */
#define PPPC_EAP_AKA_PRIME_MK_LEN                        (208)

/* Peer允许的快速重鉴权的最大次数 */
#define PPPC_EAP_AKA_MAX_FAST_REAUTHS                    (1000)

/* 清除的NAI标识 */
#define PPPC_EAP_AKA_CLEAR_PSEUDONYM                     (0x01)
#define PPPC_EAP_AKA_CLEAR_REAUTH_ID                     (0x02)
#define PPPC_EAP_AKA_CLEAR_EAP_ID                        (0x04)

/* ulAttrExistCtrlFlag */
#define PPPC_EAP_AKA_RAND_BIT                            (0x00)
#define PPPC_EAP_AKA_AUTN_BIT                            (0x01)
#define PPPC_EAP_AKA_MAC_BIT                             (0x02)
#define PPPC_EAP_AKA_IV_BIT                              (0x03)
#define PPPC_EAP_AKA_ENCR_BIT                            (0x04)
#define PPPC_EAP_AKA_NONCE_S_BIT                         (0x05)
#define PPPC_EAP_AKA_CHECKCODE_BIT                       (0x06)
#define PPPC_EAP_AKA_KDF_BIT                             (0x07)
#define PPPC_EAP_AKA_KDF_INPUT_BIT                       (0x08)
#define PPPC_EAP_AKA_NEXT_PSEUDONYM_BIT                  (0x09)
#define PPPC_EAP_AKA_NEXT_REAUTH_BIT                     (0x0A)
#define PPPC_EAP_AKA_COUNTER_BIT                         (0x0B)
#define PPPC_EAP_AKA_PADDING_BIT                         (0x0C)
#define PPPC_EAP_AKA_PERMANENT_BIT                       (0x0D)
#define PPPC_EAP_AKA_NOTIFICATION_BIT                    (0x0E)
#define PPPC_EAP_AKA_ANY_ID_BIT                          (0x0F)
#define PPPC_EAP_AKA_FULLAUTH_ID_BIT                     (0x10)
#define PPPC_EAP_AKA_RESULT_IND_BIT                      (0x11)
#define PPPC_EAP_AKA_BIDDING_BIT                         (0x12)

/*
   永久NAI中realm包括了三部分固定字符段(e.g., nai.epc.mnc<MNC>.mcc<MCC>.3gppnetwork.org)
   nai.epc.mnc | .mcc | .3gppnetwork.org
*/
#define PPPC_EAP_PERMANENT_NAI_REALM_MAX_PART              (3)

/*
   永久NAI的realm域中各固定字符段, 包含的字符数 的最大值
   max(size(nai.epc.mnc), size(.mcc), size(.3gppnetwork.org))
*/
#define PPPC_EAP_PERMANENT_NAI_REALM_PER_PART_MAX_CHAR_NUM  (16)

#define PPPC_EAP_AKA_NOTIFICATION_P_IS_1                  (0x4000)
#define PPPC_EAP_AKA_NOTIFICATION_INVALID_VALUE           (0xffff)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/** ****************************************************************************
 * Name        : PPPC_EAP_METHOD_TYPE_ENUM_UINT16
 *
 * Description : EAP METHOD TYPE
 *******************************************************************************/
enum PPPC_EAP_METHOD_TYPE_ENUM
{
    PPPC_EAP_METHOD_TYPE_AKA                = 0x0000,
    PPPC_EAP_METHOD_TYPE_AKA_PRIME          = 0x0001,
    PPPC_EAP_METHOD_TYPE_ENUM_BUTT          = 0xFFFF
};
typedef VOS_UINT16 PPPC_EAP_METHOD_TYPE_ENUM_UINT16;

/** ****************************************************************************
 * Name        : PPPC_EAP_AKA_ID_REQ_TYPE_ENUM_UINT16
 *
 * Description : ID REQ TYPE
 *******************************************************************************/
enum PPPC_EAP_AKA_ID_REQ_TYPE_ENUM
{
    PPPC_EAP_AKA_ANY_ID_REQ               = 0x0000,
    PPPC_EAP_AKA_FULLAUTH_ID_REQ          = 0x0001,
    PPPC_EAP_AKA_PERMANENT_ID_REQ         = 0x0002,
    PPPC_EAP_AKA_ID_REQ_BUTT              = 0x0003
};
typedef VOS_UINT16 PPPC_EAP_AKA_ID_REQ_TYPE_ENUM_UINT16;

/** ****************************************************************************
 * Name        : PPPC_EAP_AKA_STATE_ENUM_UINT16
 *
 * Description : EAP-AKA STATE
 *******************************************************************************/
enum PPPC_EAP_AKA_STATE_ENUM
{
    PPPC_EAP_AKA_STATE_CONTINUE             = 0x0000,
    PPPC_EAP_AKA_STATE_RESULT_SUCCESS       = 0x0001,
    PPPC_EAP_AKA_STATE_SUCCESS              = 0x0002,
    PPPC_EAP_AKA_STATE_FAILURE              = 0x0003,
    PPPC_EAP_AKA_STATE_BUTT                 = 0xFFFF
};
typedef VOS_UINT16 PPPC_EAP_AKA_STATE_ENUM_UINT16;

/** ****************************************************************************
 * Name        : PPPC_EAP_PERMANENT_NAI_REALM_PART_ENUM_UINT8
 *
 * Description : 永久NAI的realm域中固定字符段段号(共3段)
 *******************************************************************************/
enum PPPC_EAP_PERMANENT_NAI_REALM_PART_ENUM
{
    PPPC_EAP_PERMANENT_NAI_REALM_PART_ONE      = 0,
    PPPC_EAP_PERMANENT_NAI_REALM_PART_TWO      = 1,
    PPPC_EAP_PERMANENT_NAI_REALM_PART_THREE    = 2,
    PPPC_EAP_PERMANENT_NAI_REALM_PART_ENUM_BUTT
};
typedef VOS_UINT8 PPPC_EAP_PERMANENT_NAI_REALM_PART_ENUM_UINT8;


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/** ****************************************************************************
* Name        : PPPC_EAP_AKA_KEY_DATA_STRU
*
* Description : 存储EAP_AKA/EAP_AKA'运算产生的参数
*******************************************************************************/
typedef struct
{
    VOS_UINT8         aucIK[PPPC_EAP_AKA_IK_LEN];
    VOS_UINT8         aucCK[PPPC_EAP_AKA_CK_LEN];
    VOS_UINT8         aucIKPrime[PPPC_EAP_AKA_IK_LEN];
    VOS_UINT8         aucCKPrime[PPPC_EAP_AKA_CK_LEN];
    VOS_UINT8         aucPrimeK_aut[PPPC_EAP_AKA_PRIME_K_AUT_LEN];
    VOS_UINT8         aucK_aut[PPPC_EAP_AKA_K_AUT_LEN];
    VOS_UINT8         aucK_encr[PPPC_EAP_AKA_K_ENCR_LEN];
    VOS_UINT8         aucK_re[PPPC_EAP_AKA_PRIME_K_RE_LEN]; /* EAP-AKA' only */
    VOS_UINT8         aucMSK[PPPC_EAP_AKA_MSK_LEN];
    VOS_UINT8         aucEMSK[PPPC_EAP_AKA_EMSK_LEN];
    VOS_UINT8         aucMk[PPPC_EAP_AKA_MK_LEN]; /* EAP-AKA only */
    VOS_UINT8         ucRerserve[2];
}PPPC_EAP_AKA_KEY_DATA_STRU;

/** ****************************************************************************
* Name        : PPPC_EAP_AKA_AUTH_PARA_STRU
*
* Description : 存储网侧带过来的，Peer会使用的一些属性参数
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           aucNonce_s[PPPC_EAP_AKA_NONCE_S_LEN];
    VOS_UINT8                           aucRand[PPPC_EAP_AKA_RAND_LEN]; /* 128bits */
    VOS_UINT8                           aucAutn[PPPC_EAP_AKA_AUTN_LEN];
    VOS_UINT8                           aucNetworkName[PPPC_EAP_AKA_NETNAME_MAX_LEN];
    VOS_UINT16                          usCounter;
    VOS_UINT16                          usNetworkNameLen;
    VOS_UINT16                          usKdf;
}PPPC_EAP_AKA_AUTH_PARA_STRU;

/** ****************************************************************************
* Name        : PPPC_EAP_AKA_ID_INFO_STRU
*
* Description : 存储EAP-AKA的Identity信息
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPermenentId[PPPC_EAP_AKA_IDENTITY_MAX_LEN];
    VOS_UINT16                          usPermenentIdLen;
    VOS_UINT8                           aucPseudonym[PPPC_EAP_AKA_IDENTITY_MAX_LEN];
    VOS_UINT16                          usPseudonymLen;
    VOS_UINT8                           aucReauthId[PPPC_EAP_AKA_IDENTITY_MAX_LEN];
    VOS_UINT16                          usReauthIdLen;
    VOS_UINT8                           aucLastEapIdentity[PPPC_EAP_AKA_IDENTITY_MAX_LEN];
    VOS_UINT16                          usLastEapIdentityLen;
}PPPC_EAP_AKA_ID_INFO_STRU;

/** ****************************************************************************
* Name        : PPPC_eap_aka_data
*
* Description : EAP-AKA的实体信息
*******************************************************************************/
typedef struct
{
    PPPC_EAP_METHOD_TYPE_ENUM_UINT16    enEapMethod;        /* EAP-AKA or EAP-AKA' */
    PPPC_EAP_AKA_STATE_ENUM_UINT16      enEapAkaState;      /* EAP AKA STATE */
    PS_BOOL_ENUM_UINT8                  enReauth;           /* PS_TRUE: Re-auth, PS_FALSE: Full-auth */
    PS_BOOL_ENUM_UINT8                  enKdfNegotiation;
    VOS_UINT8                           ucNumNotification;  /* 对收到的notification的计数 */
    VOS_UINT8                           ucNumIdReq;         /* 对收到Identification消息的计数 */
    VOS_UINT16                          usPrevId;          /* 上一条消息的ID */
    VOS_UINT8                           ucIdMsgs[PPPC_EAP_AKA_ID_MSG_MAX_LEN];         /* EAP-AKA/Identification消息*/
    VOS_UINT16                          usIdMsgLen;         /* Id_Msg的字节长度 */
    VOS_UINT8                           aucPppcInputMsg[PPPC_EAP_MAX_PACKET_LEN]; /* 保存Eap递过来的报文 */
    VOS_UINT16                          usInputMsgLen;   /* Eap递过来的报文长度 */
    PS_BOOL_ENUM_UINT8                  enResultInd; /* AKA-Challenge or AKA-Reauthentication will include AT_Result_Ind */
    VOS_UINT8                           aucReserved[3];
    VOS_UINT16                          usCounterTooSmall;
    PPPC_EAP_AKA_KEY_DATA_STRU          stEapAkaKey;        /* EAP-AKA鉴权过程中的Key信息 */
    PPPC_EAP_AKA_AUTH_PARA_STRU         stEapAkaAuthPara;   /* 鉴权的一些参数信息 */
    PPPC_EAP_AKA_ID_INFO_STRU           stEapAkaIdInfo;     /* ID信息 */
}PPPC_EAP_AKA_DATA_INFO_STRU;

/** ****************************************************************************
* Name        : PPPC_EAP_AKA_ATTRS_STRU
*
* Description : 从EAP数据包里解出来的属性信息
*******************************************************************************/
typedef struct
{
    /*ulAttrExistCtrlFlag has 32bits
      bit0:enExistRand,  bit1:enExistRutn,  bit2:enExistMac,  bit3:enExistIv,
      bit4:enExistEncrData,  bit5:enExistNonce_s,  bit6:enExistCheckCode,  bit7:enExistKdf,
      bit8:enExistKdfInput,  bit9:enExistNextPseudonym,  bit10:enExistNextReauthId,  bit11:enExistCounter
    */
    VOS_UINT32                              ulAttrExistCtrlFlag;
    VOS_UINT8                               aucRand[PPPC_EAP_AKA_RAND_LEN]; /* 128bits */
    VOS_UINT8                               aucAutn[PPPC_EAP_AKA_AUTN_LEN];
    VOS_UINT8                               aucMac[PPPC_EAP_AKA_MAC_VALUE_LEN];
    VOS_UINT8                               aucIv[PPPC_EAP_AKA_IV_LEN];
    VOS_UINT8                               aucEncrData[PPPC_EAP_AKA_ENRC_DATA_LEN];
    VOS_UINT16                              usEncrDataLen;
    VOS_UINT8                               aucNonce_s[PPPC_EAP_AKA_NONCE_S_LEN];
    VOS_UINT8                               aucCheckCode[PPPC_EAP_AKA_CHECKCODE_MAX_LEN]; /* EAP-AKA:20bytes, EAP-AKA':32bytes */
    VOS_UINT16                              usCheckCodeLen;
    VOS_UINT16                              ausKdf[PPPC_EAP_AKA_PRIME_KDF_MAX];
    VOS_UINT16                              usKdfCount;
    VOS_UINT8                               aucKdfInput[PPPC_EAP_AKA_NETNAME_MAX_LEN];
    VOS_UINT16                              usKdfInputLen;
    VOS_UINT8                               aucNextPseudonym[PPPC_EAP_AKA_IDENTITY_MAX_LEN];
    VOS_UINT16                              usNextPseudonymLen;
    VOS_UINT8                               aucNextReauthId[PPPC_EAP_AKA_IDENTITY_MAX_LEN];
    VOS_UINT16                              usNextReauthIdLen;
    PS_BOOL_ENUM_UINT8                      enResultInd;
    VOS_UINT8                               aucRerserve1[1];
    VOS_UINT16                              usNotification;
    VOS_UINT16                              usCounter;
    PPPC_EAP_AKA_ID_REQ_TYPE_ENUM_UINT16    enEapAkaIdReqType;
    VOS_UINT16                              usBidding;
    VOS_UINT8                               aucRerserve2[2];
}PPPC_EAP_AKA_ATTRS_STRU;

/** ****************************************************************************
* Name        : PPPC_EAP_AKA_ATTR_INFO_STRU
*
* Description : EAP-AKA属性信息
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAttrId;
    VOS_UINT8                           aucRerserve1[3];
    VOS_UINT16                          usValue;
    VOS_UINT16                          usDataLen;    /* 单位: 字节 */
    VOS_UINT8                          *pData;
}PPPC_EAP_AKA_ATTR_INFO_STRU;

/** ****************************************************************************
* Name        : PPPC_EAP_PERMANENT_NAI_REALM_PART_INFO_STRU
*
* Description : 永久NAI的realm域中各固定字符段的描述结构
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPartCharNum;    /* 固定字符段中字符长度 */
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucPartChar[PPPC_EAP_PERMANENT_NAI_REALM_PER_PART_MAX_CHAR_NUM];
}PPPC_EAP_PERMANENT_NAI_REALM_PART_INFO_STRU;

/** ****************************************************************************
* Name        : PPPC_EAP_AKA_ATT_WALKER_STRU
*
* Description : 解属性需要的一些中间变量
******************************************************************************/
typedef struct
{
    VOS_UINT8                       *pucAttPos;
    VOS_UINT16                       usAttrLen;
    VOS_UINT8                        aucReserved[1];
    PS_BOOL_ENUM_UINT8               enEncr;
    PPPC_EAP_AKA_ATTRS_STRU         *pstPppcEapAkaPktAttrInfo;
} PPPC_EAP_AKA_ATT_WALKER_STRU;

/*define a function pointer to register a func to match muxtype1 header info*/
typedef VOS_UINT32 (*PPPC_EAP_AKA_MATCH_FUNC)(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);

/** ****************************************************************************
* Name        : PPPC_EAP_AKA_ATTRIBUTE_DATA_STRU
*
* Description : 存储ATTRIBUTE类型和对应处理函数指针
*******************************************************************************/
typedef struct
{
    VOS_UINT8                                          aucAttributeType;
    VOS_UINT8                                          aucReserved[3];
    PPPC_EAP_AKA_MATCH_FUNC                            pfuncMatchHead;
}PPPC_EAP_AKA_ATTRIBUTE_DATA_STRU;


/** ****************************************************************************
* Name        : PPPC_EAP_AKA_TRACE_INFO_STRU
*
* Description : EAP_AKA Trace Info
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    PPPC_TRACE_MSG_TYPE_ENUM_UINT16     enMsgId;            /* Trace Msg Type */
    VOS_UINT16                          usVersion;          /* Trace Version */
    PPPC_EAP_AKA_AUTH_PARA_STRU         stEapAkaAuthPara;   /* 鉴权的一些参数信息 */
    PPPC_EAP_AKA_KEY_DATA_STRU          stEapAkaKey;        /* EAP-AKA鉴权过程中的K信息 */
}PPPC_EAP_AKA_TRACE_INFO_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_Init
(
    PPPC_EAP_METHODS_TYPE_ENUM_UINT8    enMethodType
);
VOS_VOID PPPC_EAP_AKA_InitState(VOS_VOID);
VOS_VOID PPPC_EAP_AKA_NotifyResult(VOS_UINT32 ulRes);
VOS_VOID PPPC_EAP_AKA_ProcessPkt
(
    PPPC_EAP_METHOD_OUTPUT_STRU        *pstEAPMethodOutput,
    PPPC_EAP_METHOD_INPUT_STRU         *pstEAPMethodInputs
);
VOS_UINT32 PPPC_EAP_GetIdentity
(
    PPPC_EAP_METHODS_TYPE_ENUM_UINT8    enMethodType,
    VOS_UINT8                           aucIdentity[],
    VOS_UINT16                         *pusIdentityLen
);
VOS_UINT32 PPPC_EAP_AKA_AttRandParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttAutnParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttPaddingParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttPermanentParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttMacParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttNotificationParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttAnyParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttFullauthParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttCounterParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttNonceSParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttKdfInputParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttKdfParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttIvParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttEncrParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttNextPseudonymParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttNextReauthParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttCheckcodeParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttResultParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttBiddingParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_VOID PPPC_EAP_AKA_ReciveAuthRes
(
    PPPC_EAP_AUTH_RESULT_STRU           *pstResult
);
PS_BOOL_ENUM_UINT8 PPPC_EAP_AKA_PreProcessPkt
(
    PPPC_EAP_METHOD_INPUT_STRU         *pstEAPMethodInput
);

#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _PPP_VAR_H_ */



