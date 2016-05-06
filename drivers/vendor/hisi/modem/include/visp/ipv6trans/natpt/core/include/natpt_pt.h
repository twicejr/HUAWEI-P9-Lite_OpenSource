/************************************************************************
 *
 *    Copyright 2003, Huawei Technologies Co. Ltd  India Institute  
 *                     ALL RIGHTS RESERVED                           
 *                                                 
 *----------------------------------------------------------------------*
 *
 *                             Natpt_PT.h
 *
 *  Project Code:       VRPv5 
 *  Create Date:        2003-7-15
 *  Author:             usha   (VRPv5 IPv6 Team) 
 *  Document:
 *  Function Description:
 *  
 *----------------------------------------------------------------------*
 *  Modification History 
 *  DATE        NAME             DESCRIPTION
 *  
 *  
 ************************************************************************/




#ifndef _NATPT_PT_H
#define _NATPT_PT_H



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

/*----------------------------------------------*
 * Functions
 *----------------------------------------------*/




#define NATPT_IP_HDRLEN   5                       /* Standard IP hdr length in 32 bit word */
#define NATPT_GET_IP_HLEN(pip) ( (pip->ip_chHLen & 0xff) << 2 ) /* Returns header value in bytes */
#define NATPT_NO_IDENTIFICATION_ID 0x0000
#define NATPT_NO_FRAG_OFFSET  0x0000
#define NATPT_PT 1 


ULONG NATPT_CreateV4HdrAndCalcChecksum (MBUF_S *pstMBuf,
                                        NATPT_PKTCHAR_S *pstPktChar);

VOID NATPT_DropV6OptionalHdr (MBUF_S *pstMBuf,
                               ULONG ulOptHdrLen);
ULONG NATPT_CalcTCPV4Checksum (TCPHDR_S *pstTcpHdr,
                               NATPT_PKTCHAR_S *pstPktChar);
ULONG NATPT_CalcUDPV4Checksum (UDPHDR_S *pstUdpHdr,
                               NATPT_PKTCHAR_S *pstPktChar);
ULONG NATPT_CreateV4Header (UCHAR *pstV4Hdr,
                            NATPT_PKTCHAR_S *pstPktChar);

ULONG NATPT_CreateV6HdrAndCalcChecksum (MBUF_S *pstMBuf,
                                        NATPT_PKTCHAR_S *pstPktChar);
ULONG  NATPT_CalcICMPV4Checksum (ICMP_S *pstIcmpHdr,
                               NATPT_PKTCHAR_S *pstPktChar);

ULONG  NATPT_CalcTCPV6Checksum (TCPHDR_S *pstTcpHdr,
                               NATPT_PKTCHAR_S *pstPktChar);

ULONG  NATPT_CalcUDPV6Checksum (UDPHDR_S *pstUdpHdr,
                                NATPT_PKTCHAR_S *pstPktChar);


ULONG NATPT_ProcessV6PktInALG (MBUF_S *pstMBuf,
                               MBUF_S **ppstMBufALG, USHORT usPort, NATPT_PKTCHAR_S *pstPktChar);

ULONG NATPT_ProcessV4PktInALG(MBUF_S *pstMBuf,
                              MBUF_S **ppstMBufALG,
                              USHORT usPort,
                              NATPT_PKTCHAR_S *pstPktChar);

#ifdef  __cplusplus
}
#endif

#endif

