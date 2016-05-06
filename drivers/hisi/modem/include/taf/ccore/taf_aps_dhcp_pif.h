
#ifndef TAF_APS_DHCP_PIF_H
#define TAF_APS_DHCP_PIF_H

/*******************************************************************************
 1. Other files included
*******************************************************************************/

#include "vos.h"
#include "VosPidDef.h"

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */
#pragma pack(4)

/*******************************************************************************
 2. Macro definitions
*******************************************************************************/

#define TAF_APS_DHCP_IPV4_ADDR_LEN                          ( 4 )
#define TAF_APS_DHCP_IPV6_IFID_LEN                          ( 8 )
#define TAF_APS_DHCP_IPV6_ADDR_LEN                          ( 16 )

/*******************************************************************************
 3. Enumerations declarations
*******************************************************************************/

/******************************************************************************
 * Name        : CDATA_DHCP_ADDR_TYPE_ENUM_UINT8
 *
 * Description :
 *******************************************************************************/
enum TAF_APS_DHCP_ADDR_TYPE_ENUM
{
    TAF_APS_DHCP_ADDR_TYPE_IPV4            = 0x01,
    TAF_APS_DHCP_ADDR_TYPE_IPV6            = 0x02,
    TAF_APS_DHCP_ADDR_TYPE_IPV4V6          = 0x03,
    TAF_APS_DHCP_ADDR_TYPE_BUTT            = 0x04
};
typedef VOS_UINT8 TAF_APS_DHCP_ADDR_TYPE_ENUM_UINT8;

/******************************************************************************
 * Name        : TAF_APS_DHCP_PIF_MSG_TYPE_ENUM_UINT16
 *
 * Description :
 *******************************************************************************/
enum TAF_APS_DHCP_PIF_MSG_TYPE_ENUM
{
    ID_APS_DHCP_GET_DNS_IPV4_REQ                            = 0x0000, /* _H2ASN_MsgChoice APS_DHCP_DNS_IPV4_REQ_STRU*/ /***< @sa APS_DHCP_DNS_IPV4_REQ_STRU */
    ID_APS_DHCP_GET_DNS_IPV6_REQ                            = 0X0001, /* _H2ASN_MsgChoice APS_DHCP_DNS_IPV6_REQ_STRU*/ /***< @sa APS_DHCP_DNS_IPV6_REQ_STRU */
    ID_DHCP_APS_GET_DNS_IPV4_CNF                            = 0x0002, /* _H2ASN_MsgChoice DHCP_APS_DNS_IPV4_CNF_STRU*/ /***< @sa DHCP_APS_DNS_IPV4_CNF_STRU */
    ID_DHCP_APS_GET_DNS_IPV6_CNF                            = 0x0003, /* _H2ASN_MsgChoice DHCP_APS_DNS_IPV6_CNF_STRU*/ /***< @sa DHCP_APS_DNS_IPV6_CNF_STRU */
    ID_APS_DHCP_DEACT_IND                                   = 0X0004, /* _H2ASN_MsgChoice APS_DHCP_DEACT_IND_STRU*/ /***< @sa APS_DHCP_DETACH_IND_STRU */
    ID_TAF_APS_DHCP_PIF_MSG_TYPE_ENUM_BUTT                  = 0xFFFF
};
typedef VOS_UINT16 TAF_APS_DHCP_PIF_MSG_TYPE_ENUM_UINT16;

/*******************************************************************************
 4. Message Header declaration
*******************************************************************************/

/*******************************************************************************
 5. Message declaration
*******************************************************************************/

/*******************************************************************************
 6. STRUCT and UNION declaration
*******************************************************************************/

/** ****************************************************************************
 * Name        : APS_DHCP_DNS_IPV4_STRU
 *
 * Description : IPV4 TYPE DNS.
 *******************************************************************************/
typedef struct
{
    VOS_UINT32                                              bitOpIpv4PrimDNS:1;
    VOS_UINT32                                              bitOpIpv4SecDNS:1;
    VOS_UINT32                                              bitOpSpare:30;
    VOS_UINT8                                               aucIpv4PrimDNS[TAF_APS_DHCP_IPV4_ADDR_LEN];
    VOS_UINT8                                               aucIpv4SecDNS[TAF_APS_DHCP_IPV4_ADDR_LEN];
}APS_DHCP_DNS_IPV4_STRU;

/** ****************************************************************************
 * Name        : APS_DHCP_DNS_IPV6_STRU
 *
 * Description : IPV6 TYPE DNS.
 *******************************************************************************/

typedef struct
{
    VOS_UINT32                                              bitOpIpv6PrimDNS:1;
    VOS_UINT32                                              bitOpIpv6SecDNS:1;
    VOS_UINT32                                              bitOpSpare:30;
    VOS_UINT8                                               aucIpv6PrimDNS[TAF_APS_DHCP_IPV6_ADDR_LEN];
    VOS_UINT8                                               aucIpv6SecDNS[TAF_APS_DHCP_IPV6_ADDR_LEN];
}APS_DHCP_DNS_IPV6_STRU;

/******************************************************************************
 * Name        : APS_DHCP_DNS_IPV4_REQ_STRU
 *
 * Description : After traffic channel is connected in CDMA mode, Aps notify
 * DHCP to negotiate,.
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                       /* _H2ASN_Skip */
    TAF_APS_DHCP_PIF_MSG_TYPE_ENUM_UINT16                   enMsgId;     /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               ucRabId;
    VOS_UINT8                                               aucReserved[3];
    VOS_UINT8                                               aucIpv4Addr[TAF_APS_DHCP_IPV4_ADDR_LEN];
} APS_DHCP_DNS_IPV4_REQ_STRU;

/******************************************************************************
 * Name        : APS_DHCP_DNS_IPV6_REQ_STRU
 *
 * Description : After traffic channel is connected in CDMA mode, Aps notify
 * DHCP to negotiate,.
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                       /* _H2ASN_Skip */
    TAF_APS_DHCP_PIF_MSG_TYPE_ENUM_UINT16                   enMsgId;     /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               ucRabId;
    VOS_UINT8                                               aucReserved[3];
    /* IPV6 interface identifier, IPV6µØÖ·ºó8Î»   */
    VOS_UINT8                                               aucIdentifierId[TAF_APS_DHCP_IPV6_IFID_LEN];
} APS_DHCP_DNS_IPV6_REQ_STRU;

/******************************************************************************
 * Name        : DHCP_APS_DNS_IPV4_CNF_STRU
 *
 * Description : DHCP send result of DHCP Ipv4 negotiation to Aps.
                 Result is VOS_OK(0),  or VOS_ERR(1).
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAF_APS_DHCP_PIF_MSG_TYPE_ENUM_UINT16                   enMsgId;            /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT32                                              ulResult;           /* VOS_OK(0) or VOS_ERR(1) */
    VOS_UINT8                                               ucRabId;
    VOS_UINT8                                               aucReserved[3];
    APS_DHCP_DNS_IPV4_STRU                                  stIpv4Dns;
}DHCP_APS_DNS_IPV4_CNF_STRU;

/******************************************************************************
 * Name        : DHCP_APS_DNS_IPV6_CNF_STRU
 *
 * Description : DHCP send result of DHCP Ipv6 negotiation to Aps.
                 Result is VOS_OK(0),  or VOS_ERR(1).
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAF_APS_DHCP_PIF_MSG_TYPE_ENUM_UINT16                   enMsgId;            /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT32                                              ulResult;           /* VOS_OK(0) or VOS_ERR(1) */
    VOS_UINT8                                               ucRabId;
    VOS_UINT8                                               aucReserved[3];
    APS_DHCP_DNS_IPV6_STRU                                  stIpv6Dns;
}DHCP_APS_DNS_IPV6_CNF_STRU;

/******************************************************************************
 * Name        : APS_DHCP_DETACH_IND_STRU
 *
 * Description : After traffic channel is connected in CDMA mode,
                 Aps notify DHCP stop negotiate,.
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                       /* _H2ASN_Skip */
    TAF_APS_DHCP_PIF_MSG_TYPE_ENUM_UINT16                   enMsgId;     /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               ucRabId;
    TAF_APS_DHCP_ADDR_TYPE_ENUM_UINT8                       enPdnType;
    VOS_UINT8                                               aucReserved[2];
} APS_DHCP_DEACT_IND_STRU;

/*******************************************************************************
 7. OTHER declarations
*******************************************************************************/

/** ****************************************************************************
 * Name        : TAF_APS_DHCP_PIF_MSG_DATA
 *
 * Description : H2ASN top level message structure definition
 *******************************************************************************/
typedef struct
{
    TAF_APS_DHCP_PIF_MSG_TYPE_ENUM_UINT16                   enMsgId;     /* _H2ASN_MsgChoice_Export TAF_APS_DHCP_PIF_MSG_TYPE_ENUM_UINT16 */
    VOS_UINT8                                               aucMsgBlock[2];

    /* _H2ASN_MsgChoice_When_Comment TAF_APS_DHCP_PIF_MSG_TYPE_ENUM_UINT16 */
}TAF_APS_DHCP_PIF_MSG_DATA;

/* _H2ASN_Length UINT32*/
/** ****************************************************************************
 * Name        : TAF_APS_DHCP_PIF
 *
 * Description : H2ASN top level message structure definition
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_APS_DHCP_PIF_MSG_DATA                               stMsgData;
}Taf_aps_dhcp_pif_MSG;

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif
