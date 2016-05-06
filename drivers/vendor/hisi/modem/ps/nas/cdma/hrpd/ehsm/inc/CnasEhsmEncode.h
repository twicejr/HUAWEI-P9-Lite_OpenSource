

#ifndef __CNAS_EHSM_ENCODE_H__
#define __CNAS_EHSM_ENCODE_H__

/*****************************************************************************
  1 The Include of the header file
*****************************************************************************/
#include "vos.h"
#include "TafMd5.h"
#include "cnas_cttf_ehrpd_ehsm_ppp_pif.h"
#include "ehsm_aps_pif.h"
#include "CnasEhsmSndInternalMsg.h"
#include "CnasEhsmCtx.h"

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

#define CNAS_EHSM_MSG_PACKET_HEAD          0x7E

#define CNAS_EHSM_HIGH_BYTE                0xFF00
#define CNAS_EHSM_LOW_BYTE                 0x00FF
#define APP_APN_NULL_APN_LEN               1

#define CNAS_EHSM_PCO_ITEM_LEN_OFFSET                         (3)
#define CNAS_EHSM_PCO_LEN_ONLY_CONFIGURAION_PROTOCOL          (1)
#define CNAS_EHSM_SUM_LEN_OF_ID_LEN                           (3)
#define CNAS_EHSM_MAX_PCSCF_NUM           (3)
#define CNAS_EHSM_MAX_DNS_SERVER_NUM      (2)
#define CNAS_EHSM_MAX_NBNS_NUM            (2)
#define CNAS_EHSM_PCO_OFF                 (0)
#define CNAS_EHSM_PCO_ON                  (1)
#define CNAS_EHSM_PCO_CONFIG_PROTOCOL     (0x80)

#define CNAS_EHSM_LEN_IE_OCTETS           (1)

#define CNAS_EHSM_IPCP_PACKET_HEAD_LEN     (4)
#define CNAS_EHSM_IPCP_OPTION_DNS_LEN      (6)
#define CNAS_EHSM_IPCP_OPTION_HEAD_LEN     (2)

#define CNAS_EHSM_IPV6_IF_OFFSET           (8)
#define CNAS_EHSM_IPV6_IF_LEN              (8)

#define CNAS_EHSM_APN_LABEL_INTERVAL_CHARACTER                (46)    /* 字符'.' */

#define CNAS_EHSM_PAP_REQ                  (0x01)
#define CNAS_EHSM_PAP_ACK                  (0x02)
#define CNAS_EHSM_PAP_NAK                  (0x03)

#define CNAS_EHSM_CHAP_CHALLENGE           (0x01)
#define CNAS_EHSM_CHAP_RESPONSE            (0x02)
#define CNAS_EHSM_CHAP_SUCCESS             (0x03)
#define CNAS_EHSM_CHAP_FAILURE             (0x04)

#define CNAS_EHSM_CHAP_CHALLENGE_LEN       (16)
#define CNAS_EHSM_CHAP_MD5_LEN             (16)

#define CNAS_EHSM_IPCP_REQ_ID_LEN          \
        (sizeof(CNAS_EHSM_CONFIG_HEAD_STRU) + CNAS_EHSM_IPCP_PRIMARY_DNS_LEN + CNAS_EHSM_IPCP_SECONDARY_DNS_LEN)

#define CNAS_EHSM_IPCP_PRIMARY_DNS_LEN     (6)
#define CNAS_EHSM_IPCP_SECONDARY_DNS_LEN   (6)
#define CNAS_EHSM_IPCP_REQ_ID              (1)

#define CNAS_EHSM_PCO_ITEM_TYPE_DNS_SERVER_IPV4_LEN   (0)
#define CNAS_EHSM_PCO_ITEM_TYPE_DNS_SERVER_IPV6_LEN   (0)
#define CNAS_EHSM_PCO_ITEM_TYPE_NAS_SIGNALING_LEN     (0)

/* Converts host-to-network short integer  */
#define HOST_TO_NETWORK(x) (((((VOS_UINT16)(x) & 0x00FF) << 8) | (((VOS_UINT16)(x) & 0xFF00) >> 8)))





/*****************************************************************************
  3 The Enumeration Define
*****************************************************************************/



/*****************************************************************************
 结构名称   : SM_ESM_BCM_ENUM_UINT8
 协议表格   :
 ASN.1 描述 :
 结构说明   : BEARER CONTROL MODE枚举
*****************************************************************************/
enum CNAS_EHSM_BCM_ENUM
{
    CNAS_EHSM_BCM_MS_ONLY                  = 0x01,
    CNAS_EHSM_BCM_MS_NW                    = 0x02,

    CNAS_EHSM_BCM_BUTT
};
typedef VOS_UINT8 CNAS_EHSM_BCM_ENUM_UINT8;

enum CNAS_EHSM_PCO_ITEM_TYPE_ENUM
{
    CNAS_EHSM_PCO_ITEM_TYPE_PAP                       = 0xC023,
    CNAS_EHSM_PCO_ITEM_TYPE_CHAP                      = 0xC223,
    CNAS_EHSM_PCO_ITEM_TYPE_IPCP                      = 0x8021,
    CNAS_EHSM_PCO_ITEM_TYPE_PCSCF_IPV6                = 0x0001,
    CNAS_EHSM_PCO_ITEM_TYPE_IM_CN_SIGNAL_FLAG         = 0x0002,
    CNAS_EHSM_PCO_ITEM_TYPE_DNS_SERVER_IPV6           = 0x0003,
    CNAS_EHSM_PCO_ITEM_TYPE_BCM                       = 0x0005,
    CNAS_EHSM_PCO_ITEM_TYPE_NAS_SIGNALING             = 0x000A,
    CNAS_EHSM_PCO_ITEM_TYPE_PCSCF_IPV4                = 0x000C,
    CNAS_EHSM_PCO_ITEM_TYPE_DNS_SERVER_IPV4           = 0x000D,
    CNAS_EHSM_PCO_ITEM_TYPE_LOCAL_ADDRESS             = 0x0011,

    CNAS_EHSM_PCO_ITEM_TYPE_BUTT
};
typedef VOS_UINT16  CNAS_EHSM_PCO_ITEM_TYPE_ENUM16;

/*rfc 1661 and rfc 1332*/
enum CNAS_EHSM_IPCP_MSG_TYPE_ENUM
{
    CNAS_EHSM_IPCP_MSG_TYPE_CONFIGURE_REQ             = 1,
    CNAS_EHSM_IPCP_MSG_TYPE_CONFIGURE_ACK             ,
    CNAS_EHSM_IPCP_MSG_TYPE_CONFIGURE_NAK             ,
    CNAS_EHSM_IPCP_MSG_TYPE_CONFIGURE_REJ             ,

    CNAS_EHSM_IPCP_MSG_TYPE_BUTT
};
typedef VOS_UINT8  CNAS_EHSM_IPCP_MSG_TYPE_ENUM8;

enum CNAS_EHSM_IPCP_OPTIONS_ENUM
{
    CNAS_EHSM_IPCP_OPTIONS_PRI_DNS_ADDR               = 0x81,
    CNAS_EHSM_IPCP_OPTIONS_SEC_DNS_ADDR               = 0x83,

    CNAS_EHSM_IPCP_OPTIONS_BUTT
};
typedef VOS_UINT8  CNAS_EHSM_IPCP_OPTIONS_ENUM8;

enum CNAS_EHSM_APN_VERIFY_CHARACTER_TYPE_ENUM
{
    CNAS_EHSM_APN_VERIFY_CHARACTER_TYPE_BEGIN         = 0x01 ,
    CNAS_EHSM_APN_VERIFY_CHARACTER_TYPE_END           = 0x02,
    CNAS_EHSM_APN_VERIFY_CHARACTER_TYPE_MIDDLE        = 0x03,

    CNAS_EHSM_APN_VERIFY_CHARACTER_TYPE_BUTT
};
typedef VOS_UINT8  CNAS_EHSM_APN_VERIFY_CHARACTER_TYPE_ENUM_UINT8;


/*****************************************************************************
 结构名称   : CNAS_EHSM_CONFIG_HEAD_STRU
 协议表格   :

 结构说明   : Config Packet Header
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCode;                                 /* Request code */
    VOS_UINT8                           ucIdentifier;                           /* Identification */
    VOS_UINT16                          usLength;                               /* Length of packet */
} CNAS_EHSM_CONFIG_HEAD_STRU;

/*****************************************************************************
 结构名称   : CNAS_EHSM_CONFIG_OPTION_HEAD_STRU
 协议表格   :

 结构说明   : Config Packet option Header
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           uctype;                                 /* Request code */
    VOS_UINT8                           ucLength;                               /* Length of packet */
} CNAS_EHSM_CONFIG_OPTION_HEAD_STRU;
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


#if 0
VOS_VOID  CNAS_EHSM_EncodeIpcpContent
(
    CNAS_CTTF_EHRPD_PDN_TYPE_ENUM_UINT8                     enPdnType,
    VOS_UINT8                                              *pucSendMsg,
    VOS_UINT32                                             *pulLength
);
VOS_VOID  CNAS_EHSM_EncodeIpv4AllocMode
(
    CNAS_CTTF_EHRPD_PDN_TYPE_ENUM_UINT8                     enPdnType,
    VOS_UINT8                                              *pucSendMsg,
    VOS_UINT32                                             *pulLength
);
VOS_VOID  CNAS_EHSM_EncodePcoBcm
(
    VOS_UINT8                          *pSendMsg,
    VOS_UINT32                         *pulLength
);

VOS_VOID  CNAS_EHSM_EncodeIpv4DnsReq
(
    CNAS_CTTF_EHRPD_PDN_TYPE_ENUM_UINT8                     enPdnType,
    VOS_UINT8                                              *pucSendMsg,
    VOS_UINT32                                             *pulLength
);

VOS_VOID  CNAS_EHSM_EncodeIpv6DnsReq
(
    CNAS_CTTF_EHRPD_PDN_TYPE_ENUM_UINT8                     enPdnType,
    VOS_UINT8                                              *pucSendMsg,
    VOS_UINT32                                             *pulLength
);
#endif

VOS_VOID CNAS_EHSM_RandomBytes(
    VOS_UINT8                          *pucBuf,
    VOS_UINT8                           usLen
);

VOS_UINT32 CNAS_EHSM_EncodePco
(
    CNAS_CTTF_EHRPD_PDN_TYPE_ENUM_UINT8                     enPdnType,
    VOS_UINT8                                               ucPdnId,
    VOS_UINT8                                              *pucSendMsg,
    VOS_UINT32                                             *pulLength
);

VOS_UINT32 CNAS_EHSM_EncodeNwPDNValue
(
    CNAS_EHSM_PDN_ADDR_STRU            *pstPdnAdrrInfo,
    CNAS_CTTF_EHRPD_PDN_ADDRESS_STRU   *pstSendMsg
);

VOS_VOID CNAS_EHSM_EncodeApn(
    CONST CNAS_EHSM_APN_STRU           *pstApn,
    VOS_UINT8                          *pucApn,
    VOS_UINT8                          *pucApnLen
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

#endif /* end of CnasEhsmSndPpp.h */





