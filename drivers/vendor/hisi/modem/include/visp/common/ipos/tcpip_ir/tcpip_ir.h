/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_ir.h
*
*  Project Code:
*   Module Name:
*  Date Created: 2008-06-01
*        Author: wuhailan
*   Description:
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-06-01   wuhailan                Create
*
*******************************************************************************/
#ifndef _TCPIP_IR_H_
#define _TCPIP_IR_H_


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*
    B049 : SOCKADDRIN_S is not required for IPSec-IKE build;
          Only required by product team
*/

#ifndef IR_PRODUCT_BUILD_TYPE
#ifndef _STRUCT_SOCKADDRIN_
#define _STRUCT_SOCKADDRIN_
typedef struct tagSOCKADDRIN
{
    UCHAR   sin_chLen;
    UCHAR   sin_chFamily;
    USHORT  sin_usPort;
    struct  tagINADDR sin_stAddr;
    char    sin_chZero_a[8];
}SOCKADDRIN_S;
#endif
#endif

#include "common/visp/VISP_IR_ACL.h"
#include "common/visp/VISP_IR_ACL6.h"



//#if (VRP_YES == VRP_MODULE_IKE_IPSEC_FOR_AR)
#include "common/ipos/ipsec/ipsec_pub.h"
#include "common/ipos/ike/ike_pub.h"
#include "common/ipos/ipsec/ipsec_pfkey_ike.h"
//#endif

#ifndef IPPROTO_ESP
#define IPPROTO_ESP     50      /* Ip Sec */
#endif
#define ADP_STR_MIN_LEN 1  /*最小字符长度*/
#define ADP_IPSEC_TRANSFORMNAME_LEN 15  /*封装名字长度*/
#define ADP_IPSEC_POLICYNAME_LEN    15  /*策略名字长度*/
#define ADP_IPSEC_INTNAME_LEN       47  /*接口名字长度*/
#define ADP_IKE_ID_LEN              31  /*IKE ID长度*/

/* RLMT-391 : Local name display is not proper */
#define ADP_IKE_LOCAL_ID_LEN       131  /*IKE ID长度*/

#define ADP_IKE_REMOTENAME_LEN      131  /*IKE ID长度*/
#define ADP_IKE_PEERNAME_LEN        15  /*IKE对端实体名字长度*/

/* RLMT-390 : Peer name display is not proper */
#define ADP_IKE_PEER_NAME_LEN        31  /*IKE对端实体名字长度*/
#define ADP_IKE_KEY_LEN             127 /*IKE密钥长度*/
#define ADP_IPSEC_STRKEY_LEN        255 /*IPSEC String KEY 长度*/
#define ADP_IPSEC_POLICY_MAPSEQ     1   /*IPSec策略序列号长度*/

#define ADP_IPSEC_AUTHHEX_KEY_MIN_LEN 16
#define ADP_IPSEC_AUTHHEX_KEY_MAX_LEN 255
#define ADP_IPSEC_ENCRHEX_KEY_MIN_LEN 16
#define ADP_IPSEC_ENCRHEX_KEY_MAX_LEN 64
#define APD_IPSEC_POLICY_SEQ_MIN      1

#define ADP_IKE_TRUST_NAME_MAX_LEN          256

/*S9300 Changed by Prateek*/
#define APD_IPSEC_POLICY_SEQ_MAX      10000

/* RLMT-391 and 390 : Local name and peer name display is not proper */
typedef struct tagADP_IKE_INFO
{
    CHAR    szLocalId[ADP_IKE_LOCAL_ID_LEN+1];        /*01 本端标识*/
    CHAR    szPeerName[ADP_IKE_PEER_NAME_LEN+1]; /*02 对端实体名称*/
    ULONG   ulPeerExchangeMode;                 /*03 交换模式 主模式/野蛮模式*/
    ULONG   ulPeerIdType;                       /*04 验证对端的方式 地址验证/标识验证*/
    CHAR    szPeerKey[ADP_IKE_KEY_LEN+1];       /*05 对端－共享密钥*/
    CHAR    szPeerRemoteName[ADP_IKE_ID_LEN+1]; /*06 对端－远程接入名称*/
    CHAR    szAuthDomain[ADP_IKE_TRUST_NAME_MAX_LEN];     /* */
    ULONG   ulPeerAddress;                      /*07 对端－远程接入地址 主机序*/
    ULONG   ulPeerIsNATTravelsal;               /*08 对端－是否NAT穿透*/
    ULONG   ulIKEProposalNum;                   /*19 IKE提议－号码*/

    UCHAR ucModeCfgType;
    UCHAR ucDpdEnable;
    UCHAR ucDpdMode;
    UCHAR ucReserve;
    ULONG ulDpdIdleTime;
    USHORT usDpdRetransmitInterval;
    USHORT usDpdRetries;

    ULONG   ulIKEProposalAuthMethodType;        /*10 IKE提议－验证类别*/
    ULONG   ulIKEProposalEncryptionType;        /*11 IKE提议－加密算法*/
    ULONG   ulIKEProposalAuthAlgorithmType;     /*12 IKE提议－验证算法*/
    ULONG   ulIKEProposalDHGroupType;           /*13 IKE提议－DH组类型*/
    ULONG   ulIKESALifeTime;                    /*14 IKE提议－SA存活时间*/
/* #if (IKEV2_VERSION_SWITCH == VRP_YES)  */
    ULONG   ulAuthLifeTime;
    USHORT usPrf;
    UCHAR ucNegIkeVersion;
    UCHAR ucConfiguredIkeVer;
/* #endif */
/*#if (IKEV1_VERSION_SWITCH == VRP_YES)*/
    ULONG   ulKeepaliveInterval;                /*15 发送心跳间隔*/
    ULONG   ulKeepaliveTimeout;                 /*16 心跳超时间隔*/
    ULONG   ulNatKeepaliveInterval;             /*17 发送NAT心跳间隔*/
    ULONG   ulLocalIDType;
/*#endif*/

    /* Defect:AC4D06999 */
    USHORT  usEncrKeyLen;

    USHORT  usPad;

    /* vpn */
    ULONG ulVrfIndex;
    ULONG ulIfVrfIndex;
    ULONG ulLocalAddr;

    /*Ipv6: Security Support*/
    IN6ADDR_S stLocalIPv6Addr;
    IN6ADDR_S stPeerIPv6Addr;
    IN6ADDR_S stPeerIPv6EndAddr;

    /* S9300 Changes Merge - DPD Stats: */
    ULONG ulDpdReqSent;
    ULONG ulDpdReplyRecvd;
    ULONG ulDpdFailed;

    /* AP-REQ: Validate Peer auth method */
    ULONG ulRemoteAuthMethod;

    /*Post B039: added for Proposal Initialization*/
    ULONG ulPeerLifeTime;
    ULONG ulPeerReauthLifeTime;
    ULONG ulPeerAuthMethod;
    ULONG ulVerifyType;
    ULONG ulLocalIfnetIndex;
    CHAR  szFQDN[IKE_FQDN_NAME_MAX_LEN + 1];  /* FQDN */
    UCHAR ucFQDNState;
    UCHAR ucPeerVer;
    UCHAR ucUseAllSupportedAlg;
    UCHAR ucRemoteAddrType;
    UCHAR ucPeerType;
    UCHAR ucIsAutoTriggerEnabled;
    UCHAR ucPad[3];
}ADP_IKE_INFO_S;

typedef struct tagADP_IPSEC_INFO
{
    CHAR    szTransformName[ADP_IPSEC_TRANSFORMNAME_LEN+1];/*01 IPSEC提议-名称*/
    ULONG   ulTransformEncapType;                       /*02 IPSEC提议-封装类型 隧道 传输*/
    ULONG   ulTransformProtocolType;                    /*03 IPSEC提议-协议 ESP + AH*/
    ULONG   ulTransformEncryptionType;                  /*04 IPSEC提议-ESP加密算法*/
    ULONG   ulTransformHashMode;                        /*05 IPSEC提议-ESP验证算法*/
    CHAR    szPolicyName[ADP_IPSEC_POLICYNAME_LEN+1];   /*06 IPSEC策略-名称*/
    ULONG   ulPolicyMode;                               /*07 IPSEC策略-模式 手工 动态*/
    ULONG   ulPolicyInboundSpiValue;                    /*08 IPSEC策略-接收SPI*/
    CHAR    szPolicyInboundStringKey[ADP_IPSEC_STRKEY_LEN+1];/*09 IPSEC策略-接收字符KEY*/
    ULONG   ulPolicyOutboundSpiValue;                   /*10 IPSEC策略-发送SPI*/
    CHAR    szPolicyOutboundStringKey[ADP_IPSEC_STRKEY_LEN+1];/*11 IPSEC策略-发送字符KEY*/
    ULONG   ulPolicyTunnelPeerAddress;                  /*12 IPSEC策略-隧道对端地址 主机序*/
    ULONG   ulPolicyTunnelLocalAddress;                 /*13 IPSEC策略-隧道本端地址 主机序*/
    ULONG   ulPolicyACLNumber;                          /*14 IPSEC策略-ACL */
    CHAR    szInterfaceName[ADP_IPSEC_INTNAME_LEN+1];       /*15 IPSEC策略-使能接口名*/

    ULONG ulSALifetimeKilobytes;  /* for ipsec_isakmp */
    ULONG ulSALifetimeSeconds;    /* for ipsec_isakmp */

    UCHAR ucPFS;
    UCHAR ucLifeTimeIsPrivate;    /* the lifetime is private or global value */
    UCHAR ucKilobytesFlag;        /* if is global lifetime */
    UCHAR ucSecondsFlag;          /* if is global lifetime */
    UCHAR ucSaTriggerMode;        /* 0 Auto, 1 traffic based */
    UCHAR ucReserved[3];
//#if (IKEV2_VERSION_SWITCH == VRP_YES)
    ULONG ulTrafficSelect;        /* 0 Diable, 1 Enable */
//#endif
    CHAR szIkePeerName[ADP_IKE_PEERNAME_LEN + 1];
}ADP_IPSEC_INFO_S;

typedef struct tagADP_IPSEC_STATICS
{
    ULONG  ulInboundTocalPakcets;       /*01 SA接收总报文数*/
    ULONG  ulInboundDecapPakcets;       /*02 SA接收解密报文数*/
    ULONG  ulInboundDiscardPakcets;     /*03 SA接收丢弃报文数*/
    ULONG  ulOutboundTocalPakcets;      /*04 SA发送总报文数*/
    ULONG  ulOutboundEncapPakcets;      /*05 SA发送加密报文数*/
    ULONG  ulOutboundDiscardPakcets;    /*06 SA发送丢弃报文数*/
}ADP_IPSEC_STATICS_S;


/* AC4D07629: Updated the API for multiple tunnel requirement */
typedef VOID (*TUNNEL_NOTIFY_STATE) (UCHAR *pucMapName,ULONG ulSequenceNum,
                                     ULONG ulState, ULONG ulModeCfgAddr,
                                     TDB_S *apstSA[], ULONG ulNoOfSAs,
                                     BOOL_T bAppModeCfgSA);

extern VOID TCPIP_IPSEC_Tunnel_Status_Notify (ULONG IfIndex, CHAR *szPolicyName,
                                       ULONG ulSequenceNum, ULONG ulState,
                                       ULONG ulModeCfgAddr, TDB_S *apstSA[],
                                       ULONG ulNoOfSAs, BOOL_T bAppModeCfgSA);



typedef VOID (*IPSEC_TUNNEL_STATE_NOTIFY)
                       (IPSEC_TUNNEL_STATUS_INFO_S *pstTunnlInfo, ULONG ulState);

typedef VOID (*IPSEC6_TUNNEL_STATE_NOTIFY)
                       (IPSEC6_TUNNEL_STATUS_INFO_S *pstTunnlInfo, ULONG ulState);

/* Updated the API for multiple tunnel requirement */
typedef VOID (*IPSEC6_TUNNEL_NOTIFY_STATE) (UCHAR *pucMapName,ULONG ulSequenceNum,
                                     ULONG ulState, IN6ADDR_S *pstModeCfgAddr,
                                     TDB_S *apstSA[], ULONG ulNoOfSAs,
                                     BOOL_T bAppModeCfgSA);



extern VOID TCPIP_IPSEC_Indicate_Tunnel_Status(IPSEC_TUNNEL_STATUS_INFO_S *pstTunnlInfo,
                ULONG ulState);


extern ULONG TCPIP_FF_IPSecRegisterFunc(ULONG ulFuncID, VOID *pFunc);

extern VOID TCPIP_EspProtoInput(MBUF_S *pMBuf, ULONG ulIpHLen);
/* HS: Pruned as balong supports only manual ipsec */
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
extern ULONG TCPIP_GetIKEInfo(CHAR *pucIkePeerName, ADP_IKE_INFO_S *pstIKEInfo);
#endif
extern ULONG TCPIP_GetIPSECInfo(UCHAR *pucMapName, ULONG ulSequence,
                        ADP_IPSEC_INFO_S *pstIPSECInfo);
extern ULONG TCPIP_ShowIPSECInfo(CHAR *pucPolicyName, ULONG ulSequence);
extern ULONG TCPIP_GetIPSECStatics(UCHAR *pucMapName, ADP_IPSEC_STATICS_S *pstIPSECStatics);
extern ULONG TCPIP_ClrIPSECStatics();
/* HS: Pruned as balong supports only manual ipsec */
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
extern ULONG TCPIP_IKEv2_GetIKESABrief(ULONG ulWaitListHandle,
                                   IKE_SA_CONTENT_S **ppstIKESAContent,
                                   ULONG *pulIKESASum);
extern ULONG TCPIP_IKEv2_EapComplete (ULONG ulConnId, ULONG ulEAPResult);

extern ULONG TCPIP_IKEv2_NotifyFromEAP (UCHAR *pucEAPMsg, ULONG ulMsgLength,
                                        ULONG ulConnId, ULONG ulTimeOut);

extern ULONG TCPIP_IKEv2_RegisterEAPCallback(IKEv2_EAP_REGISTER_FUNC_S *pstIKEv2EAPCallBack);

extern ULONG TCPIP_IKEv2_SetAsInitiator(ULONG ulOpMode);
extern ULONG TCPIP_IKEv2_SetDelIkePeer(CHAR *pszIkePeerName, ULONG ulOpMode);
extern ULONG TCPIP_IKEv2_SetDelReauthInterval(ULONG ulProposalNum, ULONG ulInterval, ULONG ulOpMode);
extern ULONG TCPIP_IKEv2_SetIDType(CHAR *pszIkePeerName, ULONG ulIdType);

/*B515 LTE Peer ID type control, support */
extern ULONG TCPIP_IKE_SetIDType (CHAR *pszIkePeerName, ULONG ulIdType);


extern ULONG TCPIP_IKEv2_SetPeerIDType(CHAR *pszIkePeerName, ULONG ulIdType);
extern ULONG TCPIP_IKEv2_SetPeerNATTraversal(CHAR *pszIkePeerName, ULONG ulOpMode);
extern ULONG TCPIP_IKEv2_SetPrfNum(ULONG ulProposalNum, ULONG ulPrfType);
extern ULONG TCPIP_IKE_ClearAllSA (VOID);
/*SGSN License implementation - B511*/
extern ULONG TCPIP_IKE_EnableDisableLicense(ULONG ulLicenseFlag);
extern ULONG TCPIP_IKE_GetLicenseStatus_Register (
    IPSECIKE_GET_LICENSE_STATE_CALLBACK_FUNC pfFunc);

/*Kuldeep : B514 Changes*/
extern ULONG TCPIP_IKE_RegisterGetLocalIDForPeerFunc(
                                        IKE_RegFuncGetPeerID_HOOK_FUNC pfFunc);
ULONG TCPIP_IKE_ClearAllSAByIPVersion (UCHAR ucIPVersion);

extern ULONG TCPIP_IKE_GetLicenseStatus(ULONG *pulLicenseStatus);
extern ULONG TCPIP_IKE_ShowLicenseStatus (VOID);
/*AP : Allowing duplicate remote name in different peers*/
extern ULONG TCPIP_IKE_RegisterDuplicateRemoteNameCallback (
	IKE_DUPLICATE_REMOTE_NAME pfFunc);

extern ULONG TCPIP_IKE_DisplayModeCfgAddresses(UCHAR *pucPeerName);
extern ULONG TCPIP_IKE_EnableDisableDpd (CHAR *pszIkePeerName, ULONG ulOpMode, UCHAR ucDpdMode);
extern ULONG TCPIP_IKE_GetBulkSA(ULONG ulWaitListHandle, ULONG ulNumOfSAWanted,
                               ULONG *pulNumOfSAReturn, IKE_SA_CONTENT_S *pstSABuf, UCHAR ucPhase,
                               UCHAR ucIkeVersion);
extern ULONG TCPIP_IKE_GetSAByConnID(ULONG ulConID, IKE_SA_CONTENT_S *pstSAContent);
extern ULONG TCPIP_IKEv2_GetSAByConnID(ULONG ulConID, IKE_SA_CONTENT_S *pstSAContent);
extern ULONG TCPIP_IKE_GetSACont (ULONG *pulCont);
extern ULONG TCPIP_IKE_GetVersion(CHAR *szVer);
extern ULONG TCPIP_IKE_GET_CFG_Attributes(IKE_GET_ATTR_S *pstGetAttr,
                                       IKE_PRODUCT_NOTIFY_S *pstAttrData);
extern ULONG TCPIP_IKE_OpenObjectSa (ULONG *pulWaitListHandle,
                                        UCHAR ucIkeVersion);
extern ULONG TCPIP_IKE_SetDelIkePeer (CHAR *pucIkePeerName, ULONG ulOpMode);

extern ULONG TCPIP_IKE_SetDelKeepaliveInterval (ULONG ulInterval, ULONG ulOpMode);
extern ULONG TCPIP_IKE_SetDelKeepaliveTimeout (ULONG ulTimeout, ULONG ulOpMode);
extern ULONG TCPIP_IKE_SetDelLocalID (CHAR *pucLocalId, ULONG ulOpMode);
extern ULONG TCPIP_IKE_SetDelNatKeepaliveInterval (ULONG ulInterval, ULONG ulOpMode);
extern ULONG TCPIP_IKE_SetDelPeerAddress (CHAR * pucIkePeerName, ULONG ulIpAddress,
                                                    ULONG ulOpMode);

/* Binding the vpn along with the peer remote address is removed from AR Project
onwards. So this api is no longer needed.*/
#if 1
/* B504 Changes - Adding new API to set the Peer address with VRF */
ULONG TCPIP_IKE_SetDelPeerAddressWithVrf (CHAR * pucIkePeerName, ULONG ulIpAddress,
                                   CHAR *szVrfName, ULONG ulOpMode);
#endif

extern ULONG TCPIP_IKE_SetDelPreSharedKey (CHAR *pucIkePeerName, CHAR *pucKeyName, ULONG ulOpMode);
extern ULONG TCPIP_IKE_SetDelProposalLevel (ULONG ulProposalNum, ULONG ulOpMode);
extern ULONG TCPIP_IKE_SetDelRemoteName (CHAR *pucIkePeerName, CHAR *pucRemoteName, ULONG ulOpMode);
extern ULONG TCPIP_IKE_SetDpdHashCalcSequence(CHAR *pszIkePeerName, UCHAR ucHashSeq);
extern ULONG TCPIP_IKE_SetHeartbeatSeqNum(UCHAR ucSeqNumType);
extern ULONG TCPIP_IKE_SetHeartbeatSPIList(ULONG ulOpMode);
extern ULONG TCPIP_IKE_SetISAKMPSALife(ULONG ulProposalNum, ULONG ulLifeTime, ULONG ulOpMode);
extern ULONG TCPIP_IKE_SetModeCfgVID(CHAR *pszIkePeerName, UCHAR ucSetVID, UCHAR *pucVid);
extern ULONG TCPIP_IKE_SetOtpPswdMode(CHAR *pszIkePeerName, UCHAR ucOTPPswdMode);
extern ULONG TCPIP_IKE_SetPeerExchangeMode (CHAR *pucIkePeerName, ULONG ulExchangeMode);
extern ULONG TCPIP_IKE_SetPeerIDType (CHAR *pucIkePeerName, ULONG ulIdType);
extern ULONG TCPIP_IKE_SetPeerNATTraversal (CHAR *pucIkePeerName, ULONG ulOpMode);
extern ULONG TCPIP_IKE_SetPeerProposalNum ( CHAR *pucIkePeerName, ULONG ulProposalNum, ULONG ulOpMode);
extern ULONG TCPIP_IKE_SetPeerXauth(CHAR *pszIkePeerName,UCHAR ucXauthMode, ULONG ulOpMode);
extern ULONG TCPIP_IKE_SetPeerXauthAttributes(CHAR *pszIkePeerName, IKE_XAUTH_ATTR_S *pstIkeXauthAttr, ULONG ulOpMode);
extern ULONG TCPIP_IKE_SetPeerXauthPasscode(CHAR *pszIkePeerName, UCHAR *szPasscode, ULONG ulOpMode);
extern ULONG TCPIP_IKE_SetProposalAuthAlgorithm(ULONG ulProposalNum, ULONG ulAuthAlgorithmType);
extern ULONG TCPIP_IKE_SetProposalAuthMethod( ULONG ulProposalNum, ULONG ulAuthMethodType);
extern ULONG TCPIP_IKE_SetProposalDHGroup (ULONG ulProposalNum, ULONG ulDHGroupType);
extern ULONG TCPIP_IKE_SetProposalEncrAlgorithm( ULONG ulProposalNum, ULONG ulEncryptionType);
extern ULONG TCPIP_IKE_SetRChapHashSeq(CHAR *pszIkePeerName, UCHAR ucHashSeq);
extern ULONG TCPIP_IKE_SetResetDpd(CHAR *pszIkePeerName, ULONG ulIdleTime, USHORT usRetransmitInterval,
                                                USHORT usRetries, ULONG ulOpMode, ULONG ulAttrFlag);
extern ULONG TCPIP_IKE_SetResetXauthType(CHAR *pszIkePeerName, UCHAR ucXauthType, ULONG ulOpMode);
extern ULONG TCPIP_IKE_SetReset_Debug(ULONG ulNoFlag, ULONG ulType);
extern ULONG TCPIP_IKE_ShowDebuggingAPI(ULONG *pulDbgFlg);
extern ULONG TCPIP_IPSEC_ClearAllSA (UCHAR *szMapName, ULONG ulMapSeq ,
                            ULONG ulDestAddr, ULONG ulSpi, ULONG ulProtocol,
                            ULONG ulRemoteIpAddr, ULONG ulMode);

#endif

#if (IPSEC_YES == IPSEC_IPV6)
/* HS: Pruned as balong dont supports API*/
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
/*Ipv6: Security Support*/
extern ULONG TCPIP_IPSEC6_ClearAllSA_str(UCHAR *szMapName, ULONG ulMapSeq,
                     CHAR *szDestIPv6Addr, ULONG ulSpi, ULONG ulProtocol,
                     CHAR *szRemoteIPv6Addr, ULONG ulMode);
ULONG TCPIP_IPSEC6_ClearAllSA(UCHAR *szMapName, ULONG ulMapSeq, IN6ADDR_S *pstDestIPv6Addr,
                                ULONG ulSpi, ULONG ulProtocol, IN6ADDR_S *pstRemoteIPv6Addr, ULONG ulMode);
#endif
/*Ipv6: Security Support*/
/*Added for ipv6 support*/
VOID TCPIP_IPSEC6_SH_ShowCryptoIpsecSa_Brief();
VOID TCPIP_IPSEC6_SH_ShowCryptoIpsecSa_Map (CHAR *szMapName,ULONG ulMapSeq,
                                                CHAR *pzIPSec6PeerAddr);
/* HS: Pruned as balong supports only manual ipsec */
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
ULONG TCPIP_IPSEC6_DisplayAllPeers();
#endif

/*Ipv6: Security Support*/
VOID TCPIP_IPSEC6_SH_ShowCryptoIpsecSa_Brief();
VOID TCPIP_IPSEC6_SH_ShowCryptoIpsecSa_Map (CHAR *szMapName,ULONG ulMapSeq,
                                                CHAR *pzIPSec6PeerAddr);

ULONG TCPIP_IPSEC6_SetDelTunnelLocalAddress_str(UCHAR *pucMapName, ULONG ulSeqNo,
                                                    CHAR *pucIpv6Address, ULONG ulOpMode);
ULONG TCPIP_IPSEC6_SetDelTunnelLocalAddress(UCHAR *pucMapName, ULONG ulSeqNo,
                                             IN6ADDR_S *pstIPv6Addr, ULONG ulOpMode);

ULONG TCPIP_IPSEC6_SetDelTunnelRemoteAddress(UCHAR *pucMapName, ULONG ulSeqNo,
                                              IN6ADDR_S *pstIPv6Addr, ULONG ulOpMode);

ULONG TCPIP_IPSEC6_CreateDelPolicy (UCHAR *pucMapName,ULONG ulSeqNo,
                                           ULONG ulPolicyMode,ULONG ulOpMode);
ULONG TCPIP_IPSEC6_MapInterface(ULONG ulIfIndex,CHAR* szMapName,
                                                 ULONG ulOpMode);

ULONG TCPIP_IPSEC6_GetDelIPSECSAStat(IPSEC_IPV6_AHSTAT_S *pstALLAHStat,
                                        IPSEC_IPV6_ESPSTAT_S *pstALLESPStat,
                                        IPSEC_STAT_S *pstIPSECStat,
                                        ULONG ulOpMode);

ULONG TCPIP_IPSEC6_ShowIPSECStatistics();
ULONG TCPIP_IPSEC6_DelIPSECStatistics();

/*Ipv6: Security Support*/
ULONG TCPIP_IPSEC6_CreatePolicyByTemplate(UCHAR *pucMapName,
                                            UCHAR *pucDynaMapName,
                                            ULONG ulSeqNo);
ULONG TCPIP_IPSEC6_Register();
/* Functions to initialize the registration functions of IPSEC6/IKE6 */
VOID TCPIP_IKE_IPv6_RegisterToComn();
VOID TCPIP_IPSEC_IPv6_RegisterToComn();
ULONG TCPIP_IPSEC6_CreateDelPolicyTemplate (CHAR *szTemplateName,
                                           ULONG ulSeqNumber, ULONG ulOpMode);
ULONG TCPIP_IPSEC6_SetDelACL(UCHAR *pucMapName, ULONG ulSeqNo, ULONG ulACLNumber, UCHAR ucACLVer, ULONG ulOpMode);
ULONG TCPIP_IPSEC6_GetFirst_SAIfHandle(IPSEC_SHOW_SAINFO_S *pstSAInfo, IPSEC_SHOWSA_HANDLE_S *pstHandles,
                                        IPSEC_SHOW_INTERFACE_S *pstInterface);
#if (IPSEC_GENERIC_HW_SUPPORT == IPSEC_YES)
/* Added for HW stats by r72335 */
VOID TCPIP_IPSEC6_GetDeleteHwStats(ULONG ulOpMode);
ULONG TCPIP_IPSEC6_GetDeleteHwStats_InBuffer(IPSEC_GEN_HW_STAT_S *pstHwSaStat,
                                                                ULONG ulOpMode);
#endif
VOID TCPIP_IPSEC6_DisplayPeerStats(VOID);
/* HS: Pruned as balong supports only manual ipsec */
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
ULONG TCPIP_IKEIPSEC6_Register();
#endif
ULONG TCPIP_IPSEC6_GetIPSECStatistics(IPSEC_STAT_S *pstIPSECStatics);
ULONG TCPIP_IPSEC6_RegisterTunnelStatusNotification(IPSEC6_TUNNEL_STATE_NOTIFY pfNotifyFun, ULONG ulAppId);

ULONG TCPIP_IPSEC6_EncryptNAPackets(ULONG ulOpMode);
ULONG TCPIP_IPSEC6_SetDelV4CtrlTrafficOnV6(UCHAR *pucMapName, ULONG ulOpMode);
ULONG TCPIP_IPSEC6_SH_DisplayCryptoIpsecSa_Map (IPSEC_SHOW_SAINFO_S *pstSAInfo, ULONG ulShowSa, ULONG ulRevLen, UCHAR* pucFlag,
                                          UCHAR *pucShowBuf);
VOID TCPIP_IPSEC6_SH_ShowCryptoIpsecSaBriefToBuf(IPSEC_SA_CONTENT_S **ppstIPsecSAContent);

ULONG TCPIP_IKE6v1_ClearAllSASync();
ULONG TCPIP_IKE6v2_ClearPh1Ph2ByPeerAddressSync(IN6ADDR_S *pstIPv6Address);
ULONG TCPIP_IKE6_ClearPh1Ph2ByPeerAddressSync(IN6ADDR_S *pstIPv6Address);
ULONG TCPIP_IPSEC6_HW_NotifyReceive (ULONG ulNotifyType, IPSEC6_HW_COMMON_S *pstCommNotifyInfo,
                                        VOID* pvPacketInfo, IPSEC6_TdbIndex_S *pstTdbIndex);
#endif
ULONG TCPIP_IPSEC_CheckPolicyBindUnbind(ULONG ulIfIndex, CHAR* szMapName, UCHAR ucAddrType, ULONG ulOpMode);
extern ULONG TCPIP_IPSEC_CreateDelPolicy(UCHAR *pucMapName,
                                   ULONG ulPolicyMode ,ULONG ulOpMode);
extern ULONG TCPIP_IPSEC_CreateDelProposal(CHAR *szTransformName, ULONG ulOpMode);
extern TDB_S ** TCPIP_IPSEC_GetSharedSAInfo(ULONG ulDirection);
extern ULONG TCPIP_IPSEC_MapInterface(ULONG ulIfIndex,CHAR *szMapName, ULONG ulOpMode);
extern ULONG TCPIP_IPSEC_SetDelACL(UCHAR *pucMapName, ULONG ulACLNumber,ULONG ulOpMode);
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
extern ULONG TCPIP_IPSEC_SetDelPolicyIKEPeer(UCHAR *pucMapName,CHAR *szIKEPeerName,
                                      ULONG ulOpMode);
#endif
extern ULONG TCPIP_IPSEC_SetDelPolicyProposal(UCHAR *pucMapName, CHAR *szTransformName ,
                                       ULONG ulOpMode);
extern ULONG TCPIP_IPSEC_SetDelSaAuthStringKey (UCHAR *pucMapName, ULONG ulFlag,
                                         UCHAR *pucStringKey, ULONG ulOpMode);
extern ULONG TCPIP_IPSEC_SetDelSaAuthStringKey_SeqNo (UCHAR *pucMapName, ULONG ulSeqNo,
                                               ULONG ulFlag, UCHAR *pucStringKey,
                                               ULONG ulOpMode);
extern ULONG TCPIP_IPSEC_SetDelSaSPI (UCHAR *pucMapName, ULONG ulFlag, ULONG ulSpiValue,
                                ULONG ulOpMode);
extern ULONG TCPIP_IPSEC_SetDelSaSPI_SeqNo (UCHAR *pucMapName, ULONG ulSeqNo,
                                     ULONG ulFlag, ULONG ulSpiValue,
                                     ULONG ulOpMode);
extern ULONG TCPIP_IPSEC_SetDelTunnelLocalAddress (UCHAR *pucMapName,ULONG ulLocalAddress,
                                            ULONG ulOpMode);
extern ULONG TCPIP_IPSEC_SetDelTunnelLocalAddress_SeqNo (UCHAR *pucMapName, ULONG ulSeqNo,
                                                  ULONG ulLocalAddress,ULONG ulOpMode);
extern ULONG TCPIP_IPSEC_SetDelTunnelPeerAddress(UCHAR *pucMapName,ULONG ulPeerAddress,
                                          ULONG ulOpMode);
extern ULONG TCPIP_IPSEC_SetDelTunnelPeerAddress_SeqNo(UCHAR *pucMapName, ULONG ulSeqNo,
                                                ULONG ulPeerAddress, ULONG ulOpMode);
extern ULONG TCPIP_IPSEC_SetEncapsulationMode(CHAR *szTransformName, ULONG ulEncapType);
extern ULONG TCPIP_IPSEC_SetESPAlgorithm( CHAR *szTransformName, ULONG ulHashMode);
#if (IPSEC_YES == IPSEC_AH_SUPPORT)
extern ULONG TCPIP_IPSEC_SetAHAlgorithm (CHAR *szTransformName, ULONG ulHashAlgorithm);
#endif
extern ULONG TCPIP_IPSEC_SetESPEncryption(CHAR *szTransformName, ULONG ulEncryptionType);
extern ULONG TCPIP_IPSEC_SetTransformProtocol(CHAR *szTransformName, ULONG ulProtocolType);
extern ULONG TCPIP_TunnelNotifyRegister(TUNNEL_NOTIFY_STATE pfNotifyFun);
extern ULONG TCPIP_RegisterTunnelStatusNotification(IPSEC_TUNNEL_STATE_NOTIFY pfNotifyFun,
                                                                                ULONG ulAppId);


extern ULONG TCPIP_ShowIPSECStatics(CHAR *pucPolicyName);
/* HS: Pruned as balong supports only manual ipsec */
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
extern ULONG TCPIP_ShowIKEInfo(CHAR *pucIkePeerName);
ULONG TCPIP_IKE_QuickModeDrop(ULONG ulValue);

extern ULONG TCPIP_IKE_CloseObjectSa(ULONG *pulWaitListHandle);
extern ULONG TCPIP_IKE_SetDelModeCfg(CHAR *pszIkePeerName, ULONG ulOpMode);
extern ULONG TCPIP_IPSEC_SetSaLifetime(UCHAR *pucMapName,  ULONG ulPeriodsType,
                                ULONG ulPeriods, ULONG ulOpMode);
extern ULONG TCPIP_IPSEC_SetSaLifetimeGlobal(ULONG ulPeriodsType, ULONG ulPeriods,
                                ULONG ulOpMode);
extern ULONG TCPIP_IPSEC_SetSATriggerMode(UCHAR *pucMapName,  ULONG ucOpMode);
extern ULONG TCPIP_IPSEC_EnableDisableTrafficSelector(UCHAR *pucMapName, UCHAR ucOpMode);
extern ULONG TCPIP_IPSEC_EnableDisableTrafficSelector_SeqNo(UCHAR *pucMapName,
                                                     ULONG ulSeqNo,
                                                     UCHAR ucOpMode);
extern ULONG TCPIP_IPSEC_SetSaLifetime_SeqNo(UCHAR *pucMapName, ULONG ulSeqNo,
                                      ULONG ulPeriodsType, ULONG ulPeriods,
                                      ULONG ulOpMode);
extern ULONG TCPIP_IKE_ResetStatistics (VOID);
extern ULONG TCPIP_IKE_BindSaVPN (CHAR *pszIkePeerName, CHAR *szVPNName, ULONG ulOpMode);
extern ULONG TCPIP_IKE_SetSockPriority(UCHAR ucOpmode, ULONG ulPriorityLevel);
extern ULONG TCPIP_IKE_GetSockPriority();
extern ULONG TCPIP_IKE_SetPeerIDKeyID (CHAR *pszIkePeerName,UCHAR *szGrpName);
extern ULONG TCPIP_IKE_ClearSA (ULONG ulConnectionID, CHAR *szIfname);
extern ULONG TCPIP_IKEV1V2_SetDelIkePeer (CHAR *pszIkePeerName, ULONG ulOpMode,
                                          ULONG ulVersion);
extern ULONG TCPIP_IKE_ClearPh1Ph2ByPeerAddress(ULONG ulPeerIpAddress,
                                                ULONG ulNotify);

extern ULONG TCPIP_IKEv2_ClearPh1Ph2ByPeerAddressSync (ULONG ulIpAddr);


/*Kuldeep : B513 Changes*/

/*SGSN CR:201002270076 Delete SA's by IP address and VRF Name*/
extern ULONG TCPIP_IKE_ClearSAByPeerAddrAndVRFName(ULONG ulIpAddr, CHAR *pszVRFName,
    ULONG ulPhase, ULONG ulNotify);


/*Ike stats */
extern ULONG TCPIP_IKE_GetIkeMsgStats();
extern ULONG TCPIP_SPL_GetStatistics(IKE_IPSEC_SPLFEATURESTAT *pstSplStats);
extern ULONG TCPIP_SPL_ShowStatistics(VOID);
extern ULONG TCPIP_IKE_DeleteIkeMsgStats();
#endif
#if (IPSEC_YES == IPSEC_AH_SUPPORT)
extern VOID TCPIP_IPSEC_AHProtoInput (MBUF_S *pMBuf, ULONG ulIpHLen);
#endif
extern ULONG TCPIP_IPSEC_CreateDelPolicyTemplate (CHAR *szTemplateName,
                                           ULONG ulSeqNumber, ULONG ulOpMode);
extern ULONG TCPIP_IPSEC_BindSaVPN (IPSEC_POLICY_S *pstPolicy,
                             CHAR *szVPNName, ULONG ulOpMode);
extern ULONG TCPIP_IPSEC_SetDelSaAuthHEXKey (UCHAR *pucMapName, ULONG ulSeqNo,
                                      ULONG ulFlag, UCHAR *pucAuthHexKey,
                                      ULONG ulOpMode);
extern ULONG TCPIP_IPSEC_SetDelSaEncrHEXKey (UCHAR *pucMapName, ULONG ulSeqNo,
                                      ULONG ulFlag, UCHAR *pucEncrHexKey,
                                      ULONG ulOpMode);
extern ULONG TCPIP_IPSEC_PFS (CHAR *szMapName, ULONG ulMapSeq, ULONG ulPFSType);
extern ULONG TCPIP_IPSEC_SetDebug (ULONG ulSet, ULONG ulDebugType);
extern ULONG TCPIP_IPSEC_SetPacketDebugOnMap (ULONG ulSet, CHAR *szMapName,
                                       ULONG ulSequence);
extern ULONG TCPIP_IPSEC_SetPacketDebugOnTernaryOperator (ULONG ulSet, ULONG ulAddress,
                                                  ULONG ulSpi, UCHAR ucProto);

extern ULONG TCPIP_IPSEC_CreateDelPolicy_SeqNo(UCHAR *pucMapName, ULONG ulSeqNo,
                                        ULONG ulPolicyMode, ULONG ulOpMode);
extern ULONG TCPIP_IPSEC_SetDelACL_SeqNo(UCHAR *pucMapName, ULONG ulSeqNo,
                                         ULONG ulACLNumber,ULONG ulOpMode);
extern ULONG TCPIP_IPSEC_SetDelPolicyProposal_SeqNo(UCHAR *pucMapName,
                                             ULONG ulSeqNo,
                                             CHAR *szTransformName,
                                             ULONG ulOpMode);
VOID TCPIP_IPSEC_UnregisterWaitlistForSA (IPSEC_SHOWSA_HANDLE_S *pstHandles);

VOID TCPIP_IPSEC_SH_ShowCryptoIpsecSaByTdbEntryToBuf(UCHAR *pucSABuf,
                                                  ULONG ulNoOfEntries);
/* HS: Pruned as balong supports only manual ipsec */
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
#if (IKE_YES == IKE_IPV6)
ULONG TCPIP_IKE6_SetDelPeerAddress (CHAR *szIkePeerName, IN6ADDR_S *pstIpv6Address,
                                            ULONG ulOpMode);
extern ULONG TCPIP_IKE_Display_All_V6Peers ();
ULONG TCPIP_IKE6_SetDelIkePeer(CHAR *szIkePeerName, ULONG ulOpMode, ULONG ulVersion);
ULONG TCPIP_IKE6_GetPeerIpByConnID (ULONG ulConnId, IN6ADDR_S *pstPeerIpAddr);
ULONG TCPIP_IKE6_SetDelPeerLocalAddr(CHAR *szIkePeerName, IN6ADDR_S *pstLocalAddress, ULONG ulOpMode);
ULONG TCPIP_IKE6_GetBulkSA(ULONG ulWaitListHandle, ULONG ulNumOfSAWanted,
                              ULONG *pulNumOfSAReturn, IKE_SA_CONTENT_S *pstSABuf,
                              UCHAR ucPhase, UCHAR ucIkeVersion);
ULONG TCPIP_IKE6_ShowSA(ULONG ulDisplayType, UCHAR ucPhase);
ULONG TCPIP_IKE6_ClearAllSA(VOID);
ULONG TCPIP_IKE6_ClearPh1Ph2ByPeerAddress (IN6ADDR_S *pstIPv6Address, ULONG ulNotify);

ULONG TCPIP_IKE6_SetSockPriority(UCHAR ucOpmode, ULONG ulPriorityLevel);
ULONG TCPIP_IKE6_GetSockPriority();
#endif
#endif


/* HS: Pruned as balong supports only manual ipsec */
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
extern ULONG TCPIP_IPSEC_SetSATriggerMode_SeqNo(UCHAR *pucMapName, ULONG ulSeqNo,
                                         ULONG ucOpMode);
extern ULONG TCPIP_IPSEC_SetDelPolicyIKEPeer_SeqNo(UCHAR *pucMapName, ULONG ulSeqNo,
                                        CHAR *szIKEPeerName, ULONG ulOpMode);
extern ULONG TCPIP_IKE_ShowSA (ULONG ulDisplayType, UCHAR ucPhase);
extern ULONG TCPIP_IKE_Display_All_Proposals ();
extern ULONG TCPIP_IKE_Display_All_Peers ();
extern ULONG TCPIP_IKE_Display_All_V4Peers ();
#endif
extern VOID TCPIP_IPSEC_SH_ShowCryptoIpsecSa_Brief();

extern VOID TCPIP_IPSEC_SH_ShowCryptoIpsecSa_Map (CHAR *szMapName,
                                        ULONG ulMapSeq, ULONG ulPeerAddress);
extern ULONG TCPIP_IPSEC_GetSecuredCacheEntries();
extern VOID TCPIP_Show_SPDS_Cache_Entries();
extern ULONG TCPIP_IPSEC_GetUnsecuredCacheEntries();
extern VOID TCPIP_IPSEC_GetDeleteCacheStats(UCHAR ucOpmode, UCHAR ucCacheType);
extern VOID TCPIP_IPSEC_IKE_ShowVersion();
/* HS: Pruned as balong supports only manual ipsec */
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
VOID TCPIP_IPSEC_IKE_DumpConfig(CHAR *szIkePeerName, CHAR *szIpsecPolicyName, ULONG ulSubSeqNo);
#endif
extern const CHAR *TCPIP_IPSEC_GetMTVersion();

extern ULONG TCPIP_IPSEC_RegisterGenHwCbk(
                IPSEC_GEN_HARD_CALLBACK_S *pfGenHardCallBackSet);
#if (IPSEC_GENERIC_HW_SUPPORT == IPSEC_YES)
extern ULONG TCPIP_IPSEC_HW_NotifyReceive(ULONG ulNotifyType,
                                IPSEC_HW_COMMON_S *pstCommNotifyInfo,
                                VOID* pvPacketInfo,
                                IPSEC_TdbIndex_S *pstTdbIndex);
#endif
/* HS: Pruned as balong supports only manual ipsec */
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
extern ULONG TCPIP_IKE_ShowV1SA (ULONG ulDisplayType, UCHAR ucPhase);

/*Ipv6: Security Support*/
extern ULONG TCPIP_IKE_ShowV1SAByIPVersion (ULONG ulDisplayType, UCHAR ucPhase,
                                                        UCHAR ucIPAddrType);

extern ULONG TCPIP_IKE_ShowV2SA (ULONG ulDisplayType, UCHAR ucPhase);
/*Ipv6: Security Support*/
extern ULONG TCPIP_IKE_ShowV2SAByIPVersion (ULONG ulDisplayType, UCHAR ucPhase,
                                                        UCHAR ucIPAddrType);

extern ULONG TCPIP_IKE_DisplaySA (ULONG ulDisplayType, UCHAR ucPhase,
                                    UCHAR ucIkeVersion);
/*Ipv6: Security Support*/
extern ULONG TCPIP_IKE_DisplaySAByIPVersion(ULONG ulDisplayType, UCHAR ucPhase,
                                    UCHAR ucIkeVersion, UCHAR ucIPAddrType);

extern ULONG TCPIP_IKE_ShowLocalID ();

extern VOID TCPIP_IKE_FillPorposal (
                    IKE_PROPOSAL_CONTENT_S *pstIKEProposalContent);
#endif
#if (IPSEC_YES == IPSEC_AH_SUPPORT)
extern ULONG TCPIP_IPSEC_SetAHAlgorithm (CHAR *szTransformName,
                                            ULONG ulHashAlgorithm);
#endif
extern ULONG TCPIP_GetIPSECIKECompInfo();

/*Added for B109*/
extern VOID TCPIP_IPSEC_SH_DisplayProposalAll();
extern ULONG TCPIP_IPSEC_ShowSaLifetimeGlobal();

ULONG TCPIP_IPSEC_SH_GetIpsecSaByMapSeq (CHAR *szMapName, ULONG ulMapSeq,
                                        IPSEC_SHOW_TDBENTRY_S *pstTdbEntryBuf,
                                        IPSEC_SHOW_TDB_S *pstSABuf,
                                        ULONG *pulSaCount);

extern ULONG TCPIP_IPSEC_StartIpsecSaRekey (CHAR *szMapName, ULONG ulMapSeq,
                                     ULONG ulIfIdx);

extern ULONG TCPIP_IPSEC_SetOnDemandHardExpTimeout(ULONG ulTimeOut,
                                                    ULONG ulOpMode);

extern ULONG TCPIP_IPSEC_GetInterfacesUsedByPolicy();

/* HS: Pruned as balong supports only manual ipsec */
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
extern ULONG TCPIP_RegIkeIpsecWarnOutputHook();

/* Post B111*/
extern ULONG TCPIP_IKE_Register_Attr_Notify_Func(ULONG (*pstFuncPtr)(
                                                ULONG ulPeerAddr,
                                                ULONG ulIdentifier,
                                                IKE_PRODUCT_NOTIFY_S *pstData,
                                                ULONG ulError),
                                              ULONG *pulHandle);

extern ULONG TCPIP_IKE_Register_Attr_Notify_Func_New(ULONG (*pstFuncPtr)(IKE_PRODUCT_NOTIFY_PARA_S *pstPara,
                                    ULONG ulIdentifier, IKE_PRODUCT_NOTIFY_S *pstData,
                                    ULONG ulError),
                                    ULONG *pulHandle);
#endif

/*IPSec statistics APIs*/
extern VOID TCPIP_IPSEC_GetDeleteSaStats(ULONG ulOpMode);

extern VOID TCPIP_IPSEC_GetDeleteHwStats(ULONG ulOpMode);
/* HS: Pruned as balong supports only manual ipsec */
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
/* Added for B112 release */
extern ULONG TCPIP_IKE_SetDelPeerLocalAddr (CHAR *pucIkePeerName,
                                            ULONG ulIpAddress, ULONG ulOpMode);
/* Post B113 release */
extern ULONG TCPIP_IKEv2_SetReset_Debug(ULONG ulNoFlag, ULONG ulType);
#endif

/*Kuldeep : B513 Changes*/
extern ULONG TCPIP_IPSEC_GetAllPolicyNames();

/* To MODE-CFG, sometime product malloc memory and IKE to free it, extern
   sometime IKE malloc a memory and product to free it. But the malloc and free
   need to call visp function. so we have to provide id to product.*/
#define SID_IKE_BASE_S              0x700
#define IKE_MODULE_ID               MID_COMP_IKE
#define SID_IKE_MODECFG             (SID_IKE_BASE_S + 29)

ULONG TCPIP_IPSEC_RegNPDownloadFailureCallbackAPI(
                            NPDOWNLOADFAILURENOTIFY *pfNPDownloadFailureNotify);

/* AC4D07629: Add API to support multiple tunnel requirement */
extern ULONG TCPIP_IPSEC_SetModeCFG_SuggestionAddr (CHAR *szMap, ULONG ulSeq,
                                       ULONG ulModeCfgSugAddress, ULONG ulMask);

#if(IPSEC_YES == IPSEC_MODECFG)
extern TDB_S *TCPIP_IPSEC_GetModeCFG_SA (CHAR *szMap, ULONG ulSeq,
                                         ULONG ulDirection, ULONG ulIfIndex,
                                         ULONG ulModeCfgAddress);
#endif
/* HS: Pruned as balong supports only manual ipsec */

#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
/* AC4D07706 : New requirement to delete IKEv1 ready/non-ready state SA's */
ULONG TCPIP_IKEv1_ClearAllSASync();
/*B500*/
extern ULONG TCPIP_IKE_Config_Peer(IKE_PEER_CONFIG_S *pstIkePeerConfig);
extern ULONG TCPIP_IKE_Get_Peer(CHAR *szIkePeerName, IKE_PEER_CONFIG_S *pstIkePeer);
extern ULONG TCPIP_IKE_Config_Peer_Dpd(IKE_DPD_CONFIG_S *pstIkeDpdConfig);
extern ULONG TCPIP_IKE_Get_Peer_Dpd(CHAR * szIkePeerName, IKE_DPD_CONFIG_S *pstIkeDpdConfig);
extern ULONG TCPIP_IKE_Config_Peer_Xauth (IKE_XAUTH_CONFIG_S * pstIkeXauthConfig);
extern ULONG TCPIP_IKE_Get_Peer_Xauth (CHAR *szIkePeerName,
                                    IKE_XAUTH_CONFIG_S *pstIkeXauthConfig);

extern ULONG TCPIP_IKE_Config_Proposal (IKE_PROPOSAL_CONFIG_S *pstIkeProposal);
extern ULONG TCPIP_IKE_Get_Proposal (ULONG ulProposalNum,
                            IKE_PROPOSAL_CONFIG_S *pstIkeProposal);
#endif

extern ULONG TCPIP_IPSEC_Get_Manual_Policy(CHAR *pszMapName, ULONG ulMapSeq,
                                IPSEC_POLICY_MANUAL_S *pstIpsecManualPolicy);
extern ULONG TCPIP_IPSEC_Config_Manual_Policy (
                                IPSEC_POLICY_MANUAL_S *pstIpsecManualPolicy);

extern ULONG TCPIP_IPSEC_Get_IsakmpModecfg_Policy (CHAR *pszMapName,
                            ULONG ulMapSeq,
                            IPSEC_POLICY_ISAKMPMODECFG_S *pstIpsecPolicy);

extern ULONG TCPIP_IPSEC_Config_IsakmpModecfg_Policy (
                                IPSEC_POLICY_ISAKMPMODECFG_S *pstIpsecPolicy);

extern ULONG TCPIP_IPSEC_Get_Proposal (CHAR *pszTransformName,
                                    IPSEC_PROPOSAL_CONFIG_S *pstIpsecProposal);

extern ULONG TCPIP_IPSEC_Config_Proposal (IPSEC_PROPOSAL_CONFIG_S *pstIpsecProposal);

#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
extern const CHAR *TCPIP_IKE_GetMTVersion();


extern ULONG TCPIP_IKE_EnableDisablePacketTrace(ULONG ulSetReset);

VOID TCPIP_IKEv2_DisplayNotifyBuf (IKEV2_NOTIFY_STAT_S *pstNotifyStat);

extern ULONG TCPIP_IKEv2_DisplaySendNotifyStatistics (CHAR *pszPeerName);

extern ULONG TCPIP_IKEv2_DisplayRecvNotifyStatistics (CHAR *pszPeerName);
extern ULONG TCPIP_IKE_PKI_SetResetPkiObj (CHAR *szInputIkePeerName,
                                                CHAR *pszObj, ULONG ulOpMode);

extern ULONG TCPIP_IKE_PKI_SetResetIdentityValidation (CHAR *szInputIkePeerName,
                                                ULONG ulOpMode);

extern ULONG TCPIP_IKE_PKI_SetResetUseDefaultCert (CHAR *szInputIkePeerName,
                                                ULONG ulOpMode);

extern ULONG TCPIP_IKE_PKI_CheckObjectIsInUse (CHAR *pszObjectName);

extern ULONG TCPIP_IKE_PKI_CRLDownloadComplete (ULONG ulReqIdentifier,
                                                ULONG ulFlag);

extern ULONG TCPIP_IKE_PKI_RegisterPKICallback (IKE_PKI_REGISTER_FUNC_S *pstIkePkiCallBack);

extern ULONG TCPIP_IKE_PKI_CertDownloadComplete (ULONG ulReqIdentifer,
                            ULONG ulFlag, UCHAR *pucCertBuf, ULONG ulCertLen);

extern ULONG TCPIP_IKE_PKI_DisplayPkiStatistics ();
extern ULONG TCPIP_IKE_PKI_ResetPkiStatistics ();
#endif

/*[Defect:AC4D07930] AutoTrigger Parameters setting*/
extern ULONG TCPIP_IPSEC_EnableDisableWindowSizeOneSupport(ULONG ulOpMode);

extern ULONG TCPIP_IPSEC_DisplayAutoTrigParam();

/*[B118]Added by Prateek for AP C02 requirement*/
ULONG TCPIP_IPSEC_InboundDpdProcessingBySA(TDB_S *pstTdb);
ULONG TCPIP_IPSEC_OnDemandDpdProcessingBySA(TDB_S *pstTdb);
#if (IPSEC_GENERIC_HW_SUPPORT == IPSEC_YES)
ULONG TCPIP_IPSEC_HW_SATrafficExpire(IPSEC_TdbIndex_S *pstTdbIndex,
                                       UCHAR ucExpirationType);
#endif

#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
/* AC4D07928 [B116] : Support Tunnel UP/DOWN notification */
ULONG TCPIP_IKE_TunnelNotifyRegister (IKE_TUNNEL_STATUS_CALLBACK pfNotifyFun);


/* C99 Added APIs */
ULONG TCPIP_IKE_GetObjectNameByPeer  (CHAR *pszPeerName, CHAR *pszObjName);
ULONG TCPIP_IKEv2_GetDefaultValues (IKEV2_DEFAULT_S *pstIKEv2Default);
ULONG TCPIP_IKEv1_GetDefaultValues (IKEV1_DEFAULT_S *pstIKEv1Default);
#endif

/* IPSEC6_Changes Sanjit C06 Changes API not used */
/*ULONG TCPIP_IKEv1_DelAllPh1sa ();*/

/*Iteration2-Story3-IpsecPeerHash*/
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
ULONG TCPIP_IPSEC_DisplayDynaPeers(CHAR *pcPeerName);
ULONG TCPIP_IPSEC_ShowPeer(CHAR *pcPeerName);

ULONG TCPIP_IPSEC_DisplayAllPeers();
#endif
VOID TCPIP_IPSEC_ShowDynaPeer(CHAR *pcBuffer, ULONG ulFetchCount);
VOID TCPIP_IPSEC_ShowPeerBuf(IPSEC_PEER_S *pstPeer);
VOID TCPIP_IPSEC_DisplayPeerStats();

#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
/*S9300 Added By Prateek*/
ULONG TCPIP_IKE_GetGlobalInfo (IKE_GLOBAL_CONTENT_S *pstIKEGlobalContent);

ULONG TCPIP_IKE_GetPeerInfoByName(CHAR *szInputPeerName,
                                       IKE_PEER_CONTENT_S *pstPeerContent);

ULONG TCPIP_IKE_GetProposalByNumber(ULONG ulIKEProposalNum,
                                IKE_PROPOSAL_CONTENT_S *pstIKEProposalContent);

ULONG TCPIP_IKE_RegisterWarningAPI (pfIKE_WarningOut pfFunc);

ULONG TCPIP_IKE_OpenObject_Peer(ULONG *pulWaitListHandle);
ULONG TCPIP_IKE_CloseObject_Peer(ULONG *pulWaitListHandle);
ULONG TCPIP_IKE_GetBulkPeer(ULONG ulWaitListHandle, ULONG ulNumOfPeerWanted,
                             ULONG *pulNumOfPeerReturn,
                             IKE_PEER_CONTENT_S *pstPeerBuf);

ULONG TCPIP_IKE_OpenObject_Proposal(ULONG *pulWaitListHandle);
ULONG TCPIP_IKE_CloseObject_Proposal(ULONG *pulWaitListHandle);
ULONG TCPIP_IKE_GetBulkProposal(ULONG ulWaitListHandle,
                                   ULONG ulNumOfProposalWanted,
                                   ULONG *pulNumOfPropReturn,
                                   IKE_PROPOSAL_CONTENT_S *pstProposalBuf);
ULONG TCPIP_IKE_OpenObjectSa (ULONG *pulWaitListHandle, UCHAR ucIkeVersion);
ULONG TCPIP_IKE_CloseObjectSa(ULONG *pulWaitListHandle);
ULONG TCPIP_IKE_GetBulkSA(ULONG ulWaitListHandle, ULONG ulNumOfSAWanted,
                          ULONG *pulNumOfSAReturn, IKE_SA_CONTENT_S *pstSABuf,
                          UCHAR ucPhase, UCHAR ucIkeVersion);

/*S9300 - Added by Nagendra*/
ULONG TCPIP_IKE_GetIkeMsgStats_InBuffer(IKE_MSG_STAT_S *pstIkeMsgStat);
ULONG TCPIP_IKE_GetIkeStats_InBuffer(IKE_STATS_CONTENT_S *pstIkeStat);
#endif

extern ULONG TCPIP_IPSEC_EnableDisableAntiReplay(UCHAR ucOpMode);

/*S9300 -Added by Prateek*/
ULONG TCPIP_IPSEC_GetSinglePolicy (CHAR *szPolicyName, ULONG ulSequenceNumber,
                                    IPSEC_CryptoMap_Info_S *pstPolicyInfo);
ULONG TCPIP_IPSEC_GetSingleTransForDisplay (CHAR *szTransformName,
                                     IPSEC_CryptoTransform_S *pstTransform);

VOID TCPIP_IPSEC_GetDefaultParameters (IPSEC_DEFAULT_PARAMETERS_S
                                            *pstIPSEC_Default);

/*Added for Warning messages in IPOS.*/
ULONG TCPIP_IPSEC_RegisterWarningAPI(pfIPSEC_WarningOut pfFunc);

ULONG TCPIP_IPSEC_GetProposalSum(ULONG  *pulProposalSum);
ULONG TCPIP_IPSEC_OpenObject_Transform(ULONG *pulWaitListHandle);
ULONG TCPIP_IPSEC_CloseObject_Transform(ULONG *pulWaitListHandle);
ULONG TCPIP_IPSEC_GetBulkTransform(ULONG ulWaitListHandle,
                                    ULONG ulNumOfTransWanted,
                                     ULONG *pulNumOfTransReturn,
                                     IPSEC_CryptoTransform_S *pTransBuf);
ULONG TCPIP_IPSEC_GetFirst_PolicyGroup(ULONG *pulWaitListHandle,
                                        ULONG *pulNumberOfPolicies,
                                        IPSEC_MapGroupHead_S *pstMapHead);
ULONG TCPIP_IPSEC_GetNext_PolicyGroup(ULONG *pulWaitListHandle,
        ULONG *pulNumberOfPolicies, IPSEC_MapGroupHead_S *pstMapHead);
ULONG TCPIP_IPSEC_GetFirst_MapifIndex_ByMapName(ULONG *pulWaitListHdlr,
                                                          CHAR *szMapName,
                                                          CHAR *szIfnetName);
ULONG TCPIP_IPSEC_GetNext_MapifIndex_ByMapName(ULONG ulWaitListHdlr,
                                                CHAR *szMapName,
                                                 CHAR *szIfnetName);
ULONG TCPIP_IPSEC_GetFirst_SAIfHandle(IPSEC_SHOW_SAINFO_S *pstSAInfo,
                                IPSEC_SHOWSA_HANDLE_S *pstHandles,
                                IPSEC_SHOW_INTERFACE_S *pstInterface);
ULONG TCPIP_IPSEC_GetBulkSA(IPSEC_SHOW_SAINFO_S *pstSAInfo,
                               IPSEC_SHOWSA_HANDLE_S *pstHandles,
                               UCHAR *pucShowBuf, ULONG *pulRevLen);
ULONG TCPIP_IPSEC_GetNext_SAIfHandle(IPSEC_SHOW_SAINFO_S *pstSAInfo,
                                        IPSEC_SHOWSA_HANDLE_S *pstHandles,
                                        IPSEC_SHOW_INTERFACE_S *pstInterface);
ULONG TCPIP_IPSEC_GetDelIPSECSAStat(IPSEC_AHSTAT_S *pstALLAHStat,
                              IPSEC_ESPSTAT_S *pstALLESPStat,
                              IPSEC_STAT_S *pstIPSECStat,
                              ULONG ulOpMode);
ULONG TCPIP_IPSEC_GetSaLifetimeGlobal(ULONG *pulTime, ULONG *pulTraffic);


ULONG TCPIP_IPSEC_GetFirstPolicyOfPolGroup(CHAR *szPolicyGroupName,
                                            ULONG *pulWaitListHandle,
                                        IPSEC_CryptoMap_Info_S *pstPolicyInfo);

ULONG TCPIP_IPSEC_GetNextPolicyOfPolGroup(ULONG ulWaitListHandle,
                                        IPSEC_CryptoMap_Info_S *pstPolicyInfo);

ULONG TCPIP_IPSEC_CreatePolicyByTemplate(UCHAR *pucMapName,
                                            UCHAR *pucDynaMapName,
                                            ULONG ulSeqNo);

ULONG TCPIP_IPSEC_GetNext_DynaPolicyGroup(ULONG *pulWaitListHandle,
                                    ULONG *pulNumberOfPolTems,
                                    IPSEC_MapGroupHead_S *pstMapHead);
ULONG TCPIP_IPSEC_GetFirst_DynaPolicyGroup(ULONG *pulWaitListHandle,
                                     ULONG *pulNumberOfPolTems,
                                     IPSEC_MapGroupHead_S *pstMapHead);

ULONG TCPIP_IPSEC_GetDeleteSaExpStats_InBuffer(IPSEC_SA_EXP_S *pstSAExpStats, ULONG ulOpMode);

ULONG TCPIP_IPSEC_GetDeleteHwStats_InBuffer(IPSEC_GEN_HW_STAT_S *pstSaStat, ULONG ulOpMode);

ULONG TCPIP_IPSEC_GetAntiReplayFlag();

ULONG TCPIP_IPSEC_IKE_GetVersion(CHAR *szVersion);

ULONG TCPIP_IPSEC_GetCryptoMapCount();



/*Iteration2: Story12: Maintainance*/
VOID TCPIP_IPSEC_GetPfkeyv2Stats();
VOID TCPIP_IPSEC_GetPfkeyv2FailStats();
VOID TCPIP_IPSEC_ResetPfkeyv2Stats();

#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
VOID TCPIP_IKE_GetPfkeyv2Stats();
VOID TCPIP_IKE_GetPfkeyv2FailStats();
VOID TCPIP_IKE_ResetPfkeyv2Stats();

ULONG TCPIP_IKE_EnableDisableDhHwApis (ULONG ulEnable,
                                IKE_DH_HW_REG_FUNC *pstDHHwRegFuncs);

VOID TCPIP_IKE_DH1Pool_init(ULONG ulEnable, ULONG ulPoolSize);
VOID TCPIP_IKE_DH2Pool_init(ULONG ulEnable, ULONG ulPoolSize);

/*PKI alarm for CERT expiration*/
ULONG TCPIP_IKE_GetPeerIpByConnID (ULONG ulConnId, ULONG *pulPeerIpAddr);
#endif

ULONG TCPIP_IPSEC_GetPfkeyv2MapStats(CHAR *szMapName, ULONG ulSequence,
                                 ULONG ulIfIndex);

ULONG TCPIP_IPSEC_ResetPfkeyv2MapStats(CHAR *szMapName, ULONG ulSequence,
                                 ULONG ulIfIndex);

#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
ULONG TCPIP_IKE_PKI_SetResetInBandExchange (CHAR *szInputIkePeerName,
                                        ULONG ulType, ULONG ulOpMode);

ULONG TCPIP_IKE_SetDelRemoteAuthMethod (CHAR * pucIkePeerName,
                                        ULONG ulRemoteAuthMethod,
                                        ULONG ulOpMode);
ULONG TCPIP_IKE_ClearSAByPeerName (CHAR *pszIkePeerName, ULONG ulNotifyFlag);
ULONG TCPIP_IKE_GetPeerNameByConnID (ULONG ulConnId, UCHAR *pucPeerName);
#endif

ULONG TCPIP_IPSEC_SetCoreTriggerParams(ULONG ulIPSecMaxAutoTriggerDef,
                                        ULONG ulIPSecMaxPending);
/*Kuldeep : B513 Changes*/
ULONG TCPIP_IPSEC_GetCryptoMapCount();

#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
ULONG TCPIP_IKEv2_StartReauth(UCHAR *pucPeerName, ULONG ulHardTimeOut);
ULONG TCPIP_IKEv1_StartPh1SaRekey(UCHAR *pucPeerName, ULONG ulHardTimeout);

ULONG IKEv1_GetSupportedAlgorithm(IKEV1_SA_PARAM_S *pstSaParam);

ULONG TCPIP_IKEv2_SetResetSupportedAlgorithm (IKEV2_SA_PARAM_S *pstSaParam,
                                                            ULONG ulOpMode);
ULONG TCPIP_IKEv1_SetResetSupportedAlgorithm (IKEV1_SA_PARAM_S *pstSaParam,
                                                            ULONG ulOpMode);
/*Post B039: Proposal Initialization*/
ULONG TCPIP_IKEv2_GetSupportedAlgorithm(IKEV2_SA_PARAM_S *pstSaParam);
ULONG TCPIP_IKEv2_DisplaySupportedAlgorithm();
ULONG TCPIP_IKEv1_DisplaySupportedAlgorithm();
ULONG TCPIP_IKE_SetDelUseAllSupportedAlgs (CHAR* szInputIkePeerName,
                                        ULONG ulOpMode);

ULONG TCPIP_IKE_SetDelPeerLifeTime (CHAR* szInputIkePeerName,
                                                ULONG ulTime, ULONG ulOpMode);

ULONG TCPIP_IKEv2_SetDelPeerReauthLifeTime (CHAR* szInputIkePeerName,
                                                ULONG ulTime, ULONG ulOpMode);

ULONG TCPIP_IKE_SetDelPeerPriorityAuthMethod (CHAR* szInputIkePeerName,
                                            ULONG ulAuthMethod);

ULONG TCPIP_IKEv1_GetSupportedAlgorithm(IKEV1_SA_PARAM_S *pstSaParam);
#endif

/* B044 : Added to set max SA, peer and proposal number */
ULONG TCPIP_IPSEC_SetMaxPolicyProposal(ULONG ulMaxPolicy,
                                            ULONG ulMaxProposal);
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
ULONG TCPIP_IKE_SetMaxPeerProposalNum(ULONG ulMaxPeerNum, ULONG ulMaxPropNum,
                                        ULONG ulMaxSaNum);

ULONG TCPIP_IKE_GetSAConnIDByPeerName(UCHAR *pucPeerName, ULONG *pulConnID);

extern ULONG TCPIP_IKE_Display_PeersByVersion (UCHAR ucIPVersion);


extern ULONG TCPIP_IKE_PROF_Display_SpokePeers (UCHAR *pucProfileName, UCHAR ucIPVersion);
#endif

/*B049: API to display multiple SA under a policy (Multiple ACL/SA)*/
ULONG TCPIP_IPSEC_GetIpsecSaByBatch (IPSEC_SHOW_TDBENTRY_S *pstTdbEntryBuf,
                                        IPSEC_SHOW_TDB_S *pstSABuf,
                                        IPSEC_SHOWSA_HANDLE_S *pstHandles,
                                        IPSEC_SHOW_SAINFO_S *pstSAInfo,
                                        ULONG *pulTdbEntryCount);

ULONG TCPIP_IPSEC_ShowIpsecSaByBatchBrief(CHAR *szMapName, ULONG ulMapSeq);



ULONG TCPIP_IPSEC_SetCoreTriggerParams(ULONG ulIPSecMaxAutoTriggerDef,
                                        ULONG ulIPSecMaxPending);

/*Sanjit C06 Changes*/
#if ((IPSEC_YES == IPSEC_GGSN) && (IPSEC_YES == IPSEC_GGSN_WVISP_SUPPORT))
ULONG TCPIP_IPSEC_ApplyOnGlobal(CHAR *szMapName, ULONG ulOpMode);
#endif

#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
ULONG TCPIP_IPSEC_DiagnosticTool();
ULONG TCPIP_IKE_PacketInput (IKE_PACKET_INFO_S *pstPktInfo,
                                        UCHAR *pucMsgBuf, ULONG  ulMsgBufLen);

ULONG TCPIP_IKE_IPSEC_RegisterGgsnCbk (CMN_GGSN_API_CALLBACK_S *g_pstGgsnCbk);

ULONG TCPIP_IKE_DelSaAfterTimeout (ULONG ulConnectionID, UCHAR *pucIKEInitSpi,
            UCHAR *pucIKERespSpi, UCHAR ucInitAndRespSpiLen, ULONG ulTimeout);

    /* Mode CFG server side Implementation */
ULONG TCPIP_IKE_RegisterModeCFGServerCallback(IKE_MODECFGSERVER_REGISTER_FUNC_S
                                *pstIkeModeCFGServerCallBack);

ULONG TCPIP_IKE_SetModeCfgAttribute(IKE_AAA_ID_INFO_S *pstIDInfo,
                                IKE_AAA_MODECFG_ATTR_S *pstModeCfgAttr);

ULONG TCPIP_IKEv2_GenericEapComplete (IKE_AAA_ID_INFO_S *pstIDInfo,
                                ULONG ulEAPResult, ULONG ulMskLength,
                                UCHAR *pucMSK, ULONG ulMskLifeTime);

ULONG TCPIP_IKEv2_EapComplete (ULONG ulConnId, ULONG ulEAPResult);

ULONG TCPIP_IKEv2_RegisterEapGenericCallback (IKEV2_EAPGENERIC_REGISTER_FUNC_S
                                                *pstIkev2EAPServerCallBack);

ULONG TCPIP_IKEv2_GenericNotifyFromEAP (IKE_AAA_ID_INFO_S *pstIDInfo,
                                    ULONG ulMsgLength, UCHAR *pucEAPMsg,
                                    ULONG ulTimeOut);

ULONG TCPIP_IKE_RegisterIDValidationCallback (IKE_IDVALIDATIONCALLBACK_S
                                          *pstIkeIdValidationCallBack);

ULONG TCPIP_IKE_GetBulkSAByType(ULONG ulWaitListHandle, ULONG ulNumOfSAWanted,
                          ULONG *pulNumOfSAReturn, IKE_SA_CONTENT_S *pstSABuf,
                          UCHAR ucPhase, UCHAR ucIkeVersion,
                          IKE_DISPLAY_TYPE_S *pstDispType);

ULONG TCPIP_IKE_DisplaySAByType(ULONG ulDisplayType, UCHAR ucPhase,
                            UCHAR ucIkeVersion, IKE_DISPLAY_TYPE_S *pstDispType);

ULONG TCPIP_IKE_ShowSAByRemoteIpaddr(ULONG ulDisplayType, UCHAR ucPhase, ULONG ulRemoteIpaddr);

ULONG TCPIP_IKE_ShowSAByNAT(ULONG ulDisplayType, UCHAR ucPhase);

ULONG TCPIP_IKE_ShowNonReadySA(ULONG ulDisplayType, UCHAR ucPhase);

ULONG TCPIP_IKE_GetGgsnStats();

ULONG TCPIP_IKE_SetDelRemoteAuthMethod (CHAR * pucIkePeerName,
                                        ULONG ulRemoteAuthMethod,
                                        ULONG ulOpMode);

ULONG TCPIP_IKE_SetResetGlobalAuthMethod (UCHAR ulAuthMethod, UCHAR ucOpMode);

ULONG TCPIP_IKEv2_SetEAPServerTimeout (USHORT usTimeout);

ULONG TCPIP_IKEv2_ShowSADeleteStats();

ULONG TCPIP_IKE_ShowHAStats ();
#endif

/* Post B049: API already exist, added prototype in .h */
ULONG TCPIP_IPSEC_GetSACountFromSABuf (IPSEC_SHOW_TDB_S *pstSaBuf);
VOID TCPIP_IPSEC_UnregisterWaitlistForSA (IPSEC_SHOWSA_HANDLE_S *pstHandles);

/* B050: Added for Peer reliability requirement */
//ULONG TCPIP_IPSEC_SetGWState(ULONG ulPeerIP, ULONG ulVRF, ULONG ulSet);
#if (IPSEC_YES == IPSEC_PROFILE_SUPPORT)
ULONG TCPIP_IPSEC_PROF_CreateOrDelete(UCHAR *pucProfileName, ULONG ulOpMode);
ULONG TCPIP_IPSEC_PROF_SetDelOnInterface(ULONG ulIfIndex, UCHAR *pucProfileName, ULONG ulOpMode);
ULONG TCPIP_IPSEC_PROF_SetDelIpsecProp(UCHAR *pucProfileName, UCHAR *pucTransformName, ULONG ulOpMode);
ULONG TCPIP_IPSEC_PROF_SetSALifetime(UCHAR *pucProfileName, ULONG ulPeriodsType,
                                    ULONG ulPeriods, ULONG ulOpMode);
ULONG TCPIP_IPSEC_PROF_DisplayAll();
ULONG TCPIP_IPSEC_EasyVPN_DisplayAll();

ULONG TCPIP_IPSEC_PROF_DisplayByName(UCHAR *ucProfileName);
ULONG TCPIP_IPSEC_PROF_SetDelPFS(UCHAR *pucProfileName, ULONG ulPFSType);
ULONG TCPIP_IPSEC_PROF_SetDelPeerName(UCHAR *pucProfileName, UCHAR *pucInputIkePeerName, ULONG ulOpMode);
ULONG TCPIP_IPSEC_PROF_SetMax(ULONG ulMaxProfile);

ULONG TCPIP_IPSEC_PROF_GetCryptoMapCount();
ULONG TCPIP_IPSEC_PROF_CopyToDisplayBuff(IPSEC_PROFILE_INFO_S *pstProfile, UCHAR *pucDispStr);
ULONG TCPIP_IPSEC_EasyVPN_CopyToDispBuff(IPSEC_PROFILE_INFO_S *pstProfile, UCHAR *pucDispStr);
ULONG TCPIP_IPSEC_PROF_DeleteSA (UCHAR *pucProfileName);

ULONG TCPIP_IPSEC_PROF_AddSpoke (ULONG ulIfIndex, ULONG ulDestIP,
                                        VOID *pvFutureUse);

ULONG TCPIP_IPSEC_PROF_DelSpokeByDestAddr (ULONG ulIfIndex, ULONG ulDestAddress);

/* Sanjit C06 Changes API not used*/
/*ULONG TCPIP_IKE_ResetPeerAuthDomain (CHAR *pszPeerName, CHAR *pszAuthDomain,
                                            UCHAR ucOpMode);*/

ULONG TCPIP_IPSEC_PROF_GetTotalCount(VOID);

ULONG TCPIP_IPSEC_PROF_OpenObject(ULONG *pulHandle);

ULONG TCPIP_IPSEC_PROF_CloseObject(ULONG *pulHandle);

ULONG TCPIP_IPSEC_PROF_GetInfoStruct(UCHAR *ucProfileName,
                                            IPSEC_PROFILE_INFO_S *pstProfInfo);

ULONG TCPIP_IPSEC_PROF_GetIKEVersionByProfileName (CHAR *pszProfileName,
                                                    UCHAR *pucIKEVersion);
#endif

/*Sanjit C06 Changes This API not used
ULONG TCPIP_TUNNEL_RegisterToIPSec(VOID);*/

#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
ULONG TCPIP_IKE_SetMaxPeerProposalNum(ULONG ulMaxPeerNum, ULONG ulMaxPropNum,
                                        ULONG ulMaxSaNum);

ULONG TCPIP_IKE_ClearPh1Ph2ByPeerAddressSync (ULONG ulIpAddr);
#endif

ULONG TCPIP_IPSEC_SetMaxPolicyProposal(ULONG ulMaxPolicy, ULONG ulMaxProposal);

/* Sanjit C06 Changes API not used Stubs, Remove once available */
/*ULONG TCPIP_TUNNEL_Config(UCHAR ucMode, ULONG ulTunnelSrc, ULONG ulTunnelDst, ULONG ulVrfIndex);*/

ULONG TCPIP_IPSEC_GetCryptoMapCount();



ULONG TCPIP_IPSEC_TUNNEL_RegCallbackAPI(IPSEC_TUNNEL_CALLBACKAPI_S *pstTUNNELCallbackAPI);



#if (IPSEC_YES == IPSEC_IKE_SUPPORT)

ULONG TCPIP_IKE_PROF_ShowSA (UCHAR *pszProfileName, ULONG ulDisplayType,
                                    UCHAR ucPhase);

ULONG TCPIP_IKE_RegisterTunnelInterfaceSupportCallback (IKETUNNELINTERFACE_S
                                                            *pstTunnelInterfaceCallback);

ULONG TCPIP_IKE_PROF_GetBulkSAByProfile (ULONG ulWaitListHandle, ULONG ulNumOfSAWanted,
                                            ULONG *pulNumOfSAReturn, IKE_SA_CONTENT_S *pstSABuf,
                                            UCHAR ucPhase, CHAR *pszProfileName);
#endif

#if (IPSEC_YES == IPSEC_AUTO_SUPPORT)
/* Added for Auto-Config */
ULONG TCPIP_IPSEC_SetResetSupportedIPSecAlg (IPSEC_PROP_PARAM_S *pstPropParam, ULONG ulOpMode);
ULONG TCPIP_IPSEC_SetResetSupportedAlgorithmStub (USHORT ustransform, UCHAR ucTransformMode,
                            ULONG ulAuth, ULONG ulEnc, ULONG ulOpMode);

ULONG TCPIP_IPSEC_DisplaySupportedAlgorithms(VOID);
#endif

/* Sanjit C06 Changes as IPSEC_FQDN_SUPPORT is disabled in LTE*/
#if (IPSEC_YES == IKE_FQDN_SUPPORT)
ULONG TCPIP_IKE_DNSReturnResolvedIP (CHAR *pszFqdn, ULONG *pulIpAddr, ULONG ulNumOfAddress, VOID *pvHandle);

ULONG TCPIP_IKE_SetDelPeerFQDN(UCHAR *pucIkePeerName,
                                        UCHAR *pucRemoteName, ULONG ulOpMode);
#endif

#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
ULONG TCPIP_IKE_IPSEC_RegisterSPLFeatureCbk(IKE_IPSEC_SPLFEATURECBK *pstCbk);
#endif

#if (IPSEC_YES == IPSEC_RRI_SUPPORT)

ULONG TCPIP_IPSEC_EnableDisableReverseRoute (CHAR *pszPolName, ULONG ulPolSeqNo,
                                                UCHAR ucRouteInjectionMode,
                                                ULONG  ulPreference, UCHAR ucOpMode);
#endif
ULONG TCPIP_IPSEC_IntfStateNotification (ULONG ulIfIndex, ULONG ulIfState);

/* HS: Pruned as balong supports only manual ipsec */
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
ULONG TCPIP_IKE_RegisterGetModecfgAttrCallback(IKE_MODECFG_ATTRMASK_S *pstModeCfgGetAttrCallBack);

ULONG TCPIP_IKE_SetDelOCSPServerTimeout (ULONG ulTimeOut, ULONG ulOpMode);
ULONG TCPIP_IKE_SetDelModeCfgServerTimeout (USHORT usTimeOut, ULONG ulOpMode);
#endif

#if (IPSEC_GENERIC_HW_SUPPORT == IPSEC_YES)
ULONG TCPIP_IPSEC_PROF_GetTunnelStatus(ULONG ulIfIndex, ULONG ulVrfIndex,
                                    ULONG ulTunnelLocalAddr,
                                    ULONG ulTunnelDestAddr);
#endif
/* HS: Pruned as balong supports only manual ipsec */
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
ULONG TCPIP_IPSEC_MapInfoForSAFail();
/*B058 : stats improvement for IKEv2 exchange*/
ULONG TCPIP_IKE_GetIKEV2ExchStats ();
ULONG TCPIP_IKE_GetIKEV2ExchStats_Buffer (IKE_V2EXCHANGE_STATS_S *pstIkev2ExchStat);
ULONG TCPIP_IKE_DeleteIKEv2ExchStats();
ULONG TCPIP_IKE_DeleteIKEv1ExchStats();
ULONG TCPIP_IKE_GetIKEV1ExchStats();
ULONG TCPIP_IKE_GetIKEV1ExchStats_Buffer (IKE_V1EXCHANGE_STATS_S *pstIkev1ExchStat);
/*B057: key deletion from IKE/IPSEC after SA establishment*/
ULONG TCPIP_IKE_EnableKeyDeletion  (ULONG ulOpMode);
#endif

/*B058: Set Window Size for anti Replay*/
ULONG TCPIP_IPSEC_SetDelPolicyWindowSize_SeqNo(UCHAR *pucMapName, ULONG ulSeqNo,
                                                 ULONG ulWindowSize,
                                                 ULONG ulOpMode);

ULONG TCPIP_IPSEC_GetDeleteSaStatsInBuff(IPSEC_SA_STAT_S *pstSaStat, ULONG ulOpMode);

/*B057: key deletion from IKE/IPSEC after SA establishment*/
ULONG TCPIP_IPSEC_EnableKeyDeletion (ULONG ulOpMode);

#if (IPSEC_YES == IPSEC_PROFILE_SUPPORT)
ULONG TCPIP_IPSEC_EasyVPN_CreateOrDelete(UCHAR *pucEasyVpnName, ULONG ulEasyVpnMode, ULONG ulOpMode);
ULONG TCPIP_IPSEC_EasyVPN_SetDelIkePeer(UCHAR *pucEasyVpnName, ULONG ulIkeVersion,
                                                ULONG ulOpMode);
ULONG TCPIP_IPSEC_EasyVPN_SetDelVrf(UCHAR *pucEasyVpnName, CHAR *pszVPNName, ULONG ulOpMode);
ULONG TCPIP_IPSEC_EasyVPN_SetDelPeerRemoteName(UCHAR *pucEasyVpnName, UCHAR *pszRemoteName,
                                                    ULONG ulOpMode);

ULONG TCPIP_IPSEC_EasyVPN_SetDelPeerLocalAddress(UCHAR *pucEasyVpnName, ULONG ulLocalAddr,
                                                ULONG ulOpMode);

ULONG TCPIP_IPSEC_EasyVPN_SetDelAclNo(UCHAR *pucEasyVpnName, ULONG ulACLNumber, ULONG ulOpMode);
ULONG TCPIP_IPSEC_EasyVPN_SetAuthenticationMethod(UCHAR *pucEasyVpnName, ULONG ulAuthMethod, ULONG ulOpMode);
ULONG TCPIP_IPSEC_EasyVPN_SetDelPreSharedKey(UCHAR *pucEasyVpnName, CHAR* pucPreSharedKey,
                                                ULONG ulOpMode);
ULONG TCPIP_IPSEC_EasyVPN_SetResetPkiObj(UCHAR *pucEasyVpnName, CHAR *pszObj,
                                                ULONG ulOpMode);
ULONG TCPIP_IPSEC_EasyVPN_SetMax(ULONG ulMaxEasyVPN);

ULONG TCPIP_IPSEC_EasyVPN_SetDelIkePeerAddr(UCHAR *pucEasyVpnName, ULONG ulIpAddress,
                                            ULONG ulOpMode);
ULONG TCPIP_IPSEC_EasyVPN_SetDelIkePeerFqdn(UCHAR *pucEasyVpnName, UCHAR *pszFqdn,
                                            ULONG ulOpMode);
ULONG TCPIP_IPSEC_EasyVPN_SetDelOnInterface (ULONG ulIfIndex, UCHAR *pucEasyVPNName, ULONG ulOpMode);
#endif
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
ULONG TCPIP_IKEv2_SetDelDefaultEzVpnIkePeer(CHAR *pszIkePeerName, ULONG ulOpMode);
ULONG TCPIP_IKEv1_SetDelDefaultEzVpnIkePeer(CHAR *pszIkePeerName, ULONG ulOpMode);
#endif
#if (IPSEC_YES == IPSEC_PROFILE_SUPPORT)
ULONG TCPIP_IPSEC_EasyVPN_OpenObject(ULONG *pulHandle);
ULONG TCPIP_IPSEC_EasyVPN_CloseObject(ULONG *pulHandle);
ULONG TCPIP_IPSEC_EasyVPN_GetBulk(ULONG ulEasyVPNWaitListHandle,
                            ULONG ulNumOfEasyVPNWanted,
                            ULONG *pulNumOfEasyVPNReturn,
                            IPSEC_PROFILE_INFO_S *pstEasyVPNInfoBuf);


ULONG TCPIP_IPSEC_EasyVPN_SetDelLocalIDType(UCHAR *pucEasyVpnName, ULONG ulLocalIDType);

ULONG TCPIP_IPSEC_EasyVPN_GetTotalCount(VOID);
ULONG TCPIP_IPSEC_PROF_GetBulk(ULONG ulEasyVPNWaitListHandle,
                            ULONG ulNumOfEasyVPNWanted,
                            ULONG *pulNumOfEasyVPNReturn,
                            IPSEC_PROFILE_INFO_S *pstEasyVPNInfoBuf);

ULONG TCPIP_IPSEC_EasyVPN_GetInfoStruct(UCHAR *ucEasyVPNName,
                                            IPSEC_PROFILE_INFO_S *pstEasyVPNInfo);

ULONG TCPIP_IPSEC_EasyVPN_DisplayByName(UCHAR *ucEasyVPNName);

ULONG TCPIP_IPSEC_EasyVPN_SetResetInBandExchange(UCHAR *pucEasyVpnName, ULONG ulType, ULONG ulOpMode);
#endif
ULONG TCPIP_IPSEC_TemplateKickSaWithSameFlow(ULONG ulSetOrUndo);
ULONG TCPIP_IPSEC_GetTemplateKickSaWithSameFlow();
ULONG TCPIP_IPSEC_ShowTemplateKickSaWithSameFlow();

#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
ULONG TCPIP_IKE_GetWarningString(IKE_WARNING_ID_E ulWarningType, ULONG ulSubWarningType, CHAR **ppucOutWarnString);
ULONG TCPIP_IKEv2_SetPropPriority (IKE_PROP_PRIO_S *pstIkePropPri, ULONG ulNumIkeProp, ULONG ulOpMode);
ULONG TCPIP_IKEv2_ShowPropPriority ();

ULONG TCPIP_IKEv1_SetPropPriority (IKEV1_PROP_PRIO_S *pstIkePropPri, ULONG ulNumIkeProp, ULONG ulOpMode);
ULONG TCPIP_IKEv1_ShowPropPriority ();
#endif

ULONG TCPIP_IPSEC_GetWarningString(IPSEC_WARNING_TYPE_E ulWarningType, ULONG ulSubWarningType, CHAR **ppucOutWarnString);

/*HERT 3.4 DO requirement*/
ULONG TCPIP_IPSEC_GetIPSECDoStats (ULONG ulOperType);

#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
/* Added by s72138 for PRS: Requirement for pvt key removal*/
ULONG TCPIP_IKE_RegisterPkiCryptSignFunc_Callback(
                            IKE_SHELL_CALLBACK_PKI_CRYPT_SIGN_S *pstIkeCallbackPKICryptSign);

/* Function to enable/disable the parsing of invalid packets */
ULONG TCPIP_IKE_EnableInvalidPktParsing (ULONG ulEnable);

/* Multi-SeGw Feature */
ULONG TCPIP_IKE_SetResetLocalBackupPeer (UCHAR *pucPeerName, UCHAR ucIsLocalPeer,
                                            UCHAR *pucMasterPeerName, ULONG ulOpMode);
ULONG TCPIP_IKE_StartBackupNegotiation (UCHAR *pucBackupPeerName);
ULONG TCPIP_IKE_StopBackupNegotiation (UCHAR *pucBackupPeerName);
ULONG TCPIP_IKE_StartMasterNegotiation (UCHAR *pucMasterPeerName);
ULONG TCPIP_IKE_StopMasterNegotiation (UCHAR *pucMasterPeerName);
#endif

#if (IPSEC_GENERIC_HW_SUPPORT == IPSEC_YES)
ULONG TCPIP_IPSEC_SetDel_MasSlv_Policy(IPSEC_POLICY_RELATION_BIND_S  *pstMsPolInfo,
                                        ULONG ulOper);
#endif

#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
ULONG TCPIP_IKE_SetSwitchBack (UCHAR *pucPeerName, UCHAR ucFlag);

/*HERT3.3 DH HW Support*/
ULONG TCPIP_IKE_RegisterHWAPIForDH(IKE_DH_HW_CBK_S *pstHwRegAPIs);
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /* _TCPIP_IR_H_ */
