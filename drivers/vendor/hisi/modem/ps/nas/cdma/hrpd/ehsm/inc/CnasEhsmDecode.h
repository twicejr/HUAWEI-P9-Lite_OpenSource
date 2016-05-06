

#ifndef __CNAS_EHSM_DECODE_H__
#define __CNAS_EHSM_DECODE_H__

/*****************************************************************************
  1 The Include of the header file
*****************************************************************************/
#include "vos.h"
#include "cnas_cttf_ehrpd_ehsm_ppp_pif.h"
#include "ehsm_aps_pif.h"
#include "CnasEhsmSndInternalMsg.h"
#include "CnasEhsmCtx.h"
#include "CnasEhsmEncode.h"
#include "CnasEhsmComFunc.h"

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
#define CNAS_EHSM_MSG_PD                   (0x02)              /*ESM 消息的PD(低4位)为0010*/
#define CNAS_EHSM_MAX_PCO_BYTE             (251)
/*****************************************************************************
  3 The Enumeration Define
*****************************************************************************/

/*****************************************************************************
    枚举名    : CNAS_EHSM_NW_LOCAL_IP_CAP_ENUM
    枚举说明  : 网侧是否支持LOCAL IP
*****************************************************************************/
enum    CNAS_EHSM_NW_LOCAL_IP_CAP_ENUM
{
    CNAS_EHSM_NW_LOCAL_IP_CAP_UNSUPPORT                = 0x00,
    CNAS_EHSM_NW_LOCAL_IP_CAP_SUPPORT,

    CNAS_EHSM_NW_LOCAL_IP_CAP_BUTT
};
typedef VOS_UINT32   CNAS_EHSM_NW_LOCAL_IP_CAP_ENUM_UINT32;


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

typedef struct
{
    VOS_UINT8                           aucIpV4Addr[CNAS_EHSM_IPV4_ADDR_LEN];
}CNAS_EHSM_IPV4_ADDR_STRU;

typedef struct
{
    VOS_UINT8                           aucIpV6Addr[CNAS_EHSM_IPV6_ADDR_LEN];
}CNAS_EHSM_IPV6_ADDR_STRU;


/* EHSM上下文的PCO的结构体 */
/*typedef APP_ESM_PCO_INFO_STRU CNAS_EHSM_CONTEXT_PCO_STRU;*/
/*****************************************************************************
 结构名    : CNAS_EHSM_CONTEXT_PCO_STRU
 结构说明  : 译码后的PCO参数
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpBcm        : 1;
    VOS_UINT32                          bitOpImsCnSignalFlag :1;
    VOS_UINT32                          bitOpNwLocalIpCap :1;
    VOS_UINT32                          bitOpSpare      : 29;
    CNAS_EHSM_BCM_ENUM_UINT8            enBcm;
    VOS_UINT8                           ucIpv4DnsSerNum;
    VOS_UINT8                           ucIpv4PcscfNum;
    VOS_UINT8                           ucIpv6DnsSerNum;
    VOS_UINT8                           ucIpv6PcscfNum;
    VOS_UINT8                           ucIpv4NbnsNum;
    VOS_UINT8                           ucReserved[2];
    CNAS_EHSM_IPV4_ADDR_STRU            astIpv4DnsServer[CNAS_EHSM_MAX_DNS_SERVER_NUM];
    CNAS_EHSM_IPV4_ADDR_STRU            astIpv4Pcscf[CNAS_EHSM_MAX_PCSCF_NUM];
    CNAS_EHSM_IPV4_ADDR_STRU            astIpv4Nbns[CNAS_EHSM_MAX_NBNS_NUM];
    CNAS_EHSM_IPV6_ADDR_STRU            astIpv6DnsServer[CNAS_EHSM_MAX_DNS_SERVER_NUM];
    CNAS_EHSM_IPV6_ADDR_STRU            astIpv6Pcscf[CNAS_EHSM_MAX_PCSCF_NUM];
    CNAS_EHSM_NW_LOCAL_IP_CAP_ENUM_UINT32 enNwLocalIPCap;
}CNAS_EHSM_CONTEXT_PCO_STRU;


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

CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_DecodePcoIpv4Item
(
    VOS_UINT8                          *pucMsg,
    CNAS_EHSM_IPV4_ADDR_STRU           *pstIpAddr
);
CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_DecodePcoIpv6Item
(
    VOS_UINT8                          *pucMsg,
    CNAS_EHSM_IPV6_ADDR_STRU           *pstIpAddr
);
CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_DecodePcoIpv6Dns
(
    VOS_UINT8                          *pucTmpMsg,
    CNAS_EHSM_CONTEXT_PCO_STRU         *pstPco,
    VOS_UINT32                         *pulSum,
    CNAS_EHSM_IPV6_ADDR_STRU           *pstEmptyIpv6Addr
);
CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_DecodePcoIpv4Dns
(
    VOS_UINT8                          *pucTmpMsg,
    CNAS_EHSM_CONTEXT_PCO_STRU         *pstPco,
    VOS_UINT32                         *pulSum,
    CNAS_EHSM_IPV4_ADDR_STRU           *pstEmptyIpv4Addr
);
CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_DecodePcoIpv4Pcscf
(
    VOS_UINT8                          *pucTmpMsg,
    CNAS_EHSM_CONTEXT_PCO_STRU         *pstPco,
    VOS_UINT32                         *pulSum,
    CNAS_EHSM_IPV4_ADDR_STRU           *pstEmptyIpv4Addr
);
CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_DecodePcoIpv6Pcscf
(
     VOS_UINT8                         *pucTmpMsg,
    CNAS_EHSM_CONTEXT_PCO_STRU         *pstPco,
    VOS_UINT32                         *pulSum,
     CNAS_EHSM_IPV6_ADDR_STRU          *pstEmptyIpv6Addr
);
CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_DecodeLocalAddress
(
    VOS_UINT8                          *pucTmpMsg,
    CNAS_EHSM_CONTEXT_PCO_STRU         *pstPco,
    VOS_UINT32                         *pulSum
);
VOS_VOID  CNAS_EHSM_DecodePcoBcm
(
    VOS_UINT8                          *pucMsg,
    CNAS_EHSM_CONTEXT_PCO_STRU         *pstPco
);
CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_ValidateIpcpLen
(
     VOS_UINT8                         *pucMsg
);

VOS_UINT8 CNAS_EHSM_CheckIpv4AddrIsEmpty( CNAS_EHSM_IPV4_ADDR_STRU *pstIpAddr);
VOS_VOID CNAS_EHSM_OptimizeDnsServer
(
    CNAS_EHSM_CONTEXT_PCO_STRU         *pstPco
);
CNAS_EHSM_CAUSE_ENUM_UINT8 CNAS_EHSM_DecodeIpcpOptionContent
(
    VOS_UINT8                          *pucMsg,
    VOS_UINT32                         *pulSum,
    CNAS_EHSM_CONTEXT_PCO_STRU         *pstPco
);
CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_DecodeIpcpContent
(
    VOS_UINT8                          *pucMsg,
    CNAS_EHSM_CONTEXT_PCO_STRU         *pstPco
);
CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_ValidatePcoLen
(
    VOS_UINT8                          *pucMsg,
    VOS_UINT8                           ucPcoLength,
    VOS_UINT16                         *pusDecodeLen
);
CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_DecodePcoContent
(
    VOS_UINT16                          usMsgLen,
     VOS_UINT8                         *pucMsg,
    CNAS_EHSM_CONTEXT_PCO_STRU         *pstMsgIE
);
CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_DecodePco
(
    VOS_UINT16                          usMsgLen,
     VOS_UINT8                         *pucMsg,
    CNAS_EHSM_CONTEXT_PCO_STRU         *pstMsgIE
);

CNAS_EHSM_CAUSE_ENUM_UINT8 CNAS_EHSM_DecodeNwPDNValue
(
    VOS_UINT16                          usMsgLen,
    VOS_UINT8                          *pucMsg,
    CNAS_EHSM_PDN_ADDR_STRU            *pstMsgIE
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

#endif





