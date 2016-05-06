/************************************************************************
 *
 *    Copyright 2003, Huawei Technologies Co. Ltd  India Institute  
 *                     ALL RIGHTS RESERVED                           
 *                                                 
 *----------------------------------------------------------------------*
 *
 *                             Natpt_alg.h
 *
 *  Project Code:       VRPv5 
 *  Create Date:        2003-7-15
 *  Author:             Desh   (VRPv5 IPv6 Team) 
 *  Document:          include file for the ALG frame work
 *  Function Description:
 *  
 *----------------------------------------------------------------------*
 *  Modification History 
 *  DATE        NAME             DESCRIPTION
 *  2003-07-15  Desh              created
 *  
 ************************************************************************/




#ifndef _NATPT_ALG_H
#define _NATPT_ALG_H

#ifdef  __cplusplus
extern  "C"{
#endif


/*----------------------------------------------*
 * Header Files                
 *----------------------------------------------*/

/*----------------------------------------------*
 * External Variables            
 *----------------------------------------------*/

/*----------------------------------------------*
 * Global Variables    
 *----------------------------------------------*/

/*----------------------------------------------*
 * External Functions
 *----------------------------------------------*/
   extern ULONG NATPT_DNS_ALG_IPv4toIPv6(MBUF_S *pstMBufIn, MBUF_S **pstMBufOut, VOID* pstHash,USHORT ulHdrLen,UCHAR ucProtocol) ;
   extern ULONG NATPT_DNS_ALG_IPv6toIPv4(MBUF_S *pstMBufIn, MBUF_S **pstMBufOut, VOID* pstHash,USHORT ulHdrLen,UCHAR ucProtocol) ;
/*----------------------------------------------*
/*----------------------------------------------*
 * Macro
 *----------------------------------------------*/
#define NATPT_ALG_MAX_PROTOHASH  128    /*Max No. of Hash indices. */
#define NATPT_UDP_DNS_PORT  53  /*UDP port number for DNS.*/
#define NATPT_NO_PORT   0      /*No port number */

#define NATPT_ALG_HASH_FOR_PROTO(x)  (ULONG)(((x) & 0x000003ff)%128)

 /* ICMP ALG related Macro's */

#define ICMP_PARAMPROB_BADHEADER 0 /* Not defined by ICMP(code 0 of type 12) */
#define NATPT_ICMP_ALG_ERRMSG    2
#define NUM_OF_PLATEAU_ENTRIES   11

/*Desh : this structure might be placed later in natpt_type.h*/

typedef struct tagNATPT_ALGProtocolHash
{
    UCHAR     ucProtocol ; /*Protocol. TCP or UDP*/
    UCHAR     ucFlag;  /*Flag*/
    USHORT    usPort;  /*Port number of the application*/
    struct tagNATPT_ALGProtocolHash   *pNext ;  /*Pointer to next node*/
    ULONG (*pfIPv4toIPv6) (MBUF_S *pstMBufIn, MBUF_S **pstMBufOut, VOID* pstHash,USHORT ulHdrLen,UCHAR ucProtocol   ) ; /*Packet processing function pointer for a packet coming IPv4 & going to IPv6*/
    ULONG (*pfIPv6toIPv4) (MBUF_S *pstMBufIn, MBUF_S **pstMBufOut, VOID* pstHash,USHORT ulHdrLen,UCHAR ucProtocol   ) ; /*Packet processing function pointer for a packet coming IPv6 & going to IPv4*/
} NATPT_ALG_PROTOCOLHASH_S ;


extern VOID NATPT_AdjustChecksum (UCHAR *pucChksum, 
                                          UCHAR *pucOldData,
                                          LONG lOldLen,
                                          UCHAR *pucNewData, 
                                          LONG lNewLen);


/* ICMP ALG related Prototypes */
ULONG NATPT_ICMP_ALG_Process_ICMPv6(
                                    MBUF_S *pstMBufIn,
                                    MBUF_S **ppstMBufOut,
                                    VOID* pstHash,
                                    USHORT usHLen,
                                    UCHAR ucProtocol);

ULONG NATPT_ICMP_ALG_Translate_ICMPv6_Dgram(ICMP6_S *pstICMP6);

ULONG NATPT_ICMP_ALG_Translate_Inner_IPv6(
                                          MBUF_S *pstMBufIn,
                                          USHORT usHLen);

ULONG NATPT_ICMP_ALG_Process_ICMPv4(
                                    MBUF_S *pstMBufIn, 
                                    MBUF_S **ppstMBufOut,
                                    VOID* pstHash,
                                    USHORT usHLen,
                                    UCHAR ucProtocol);

ULONG NATPT_ICMP_ALG_Translate_ICMPv4_Dgram(ICMP_S *pstICMP);

ULONG NATPT_ICMP_ALG_Translate_Inner_IPv4(MBUF_S *pstMBufIn,
                                          USHORT usHLen);
ULONG NATPT_ALG_RegAppProtocol ( NATPT_ALG_PROTOCOLHASH_S stAlgProtoHash);    

#ifdef  __cplusplus
}
#endif

#endif

