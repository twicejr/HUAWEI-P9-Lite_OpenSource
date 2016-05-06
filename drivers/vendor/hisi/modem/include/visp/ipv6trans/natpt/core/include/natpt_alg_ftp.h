/************************************************************************
 *
 *    Copyright 2003, Huawei Technologies Co. Ltd  India Institute  
 *                     ALL RIGHTS RESERVED                           
 *                                                 
 *----------------------------------------------------------------------*
 *
 *                             natpt_alg_ftp.h
 *
 *  Project Code:       VRPv5 
 *  Create Date:        2004-03-10
 *  Author:             Desh   (VRPv5 IPv6 Team) 
 *  Document:          This file contains all the definitions for the DNS ALG
 *  Function Description:
 *  
 *----------------------------------------------------------------------*
 *  Modification History 
 *  DATE        NAME             DESCRIPTION
 *  
 *  
 ************************************************************************/

/* Modified by usha for defect BYAD11228 */
#ifndef _NATPT_ALG_FTP_H
#define _NATPT_ALG_FTP_H
/* End of modification by usha */


#ifdef  __cplusplus
extern  "C"{
#endif

#define NATPT_FTP_V6OFFSET 1
#define NATPT_FTP_V4OFFSET 2

#define NATPT_FTP_MAX_EPRT_CMD_LEN    55/* EPRT |2|1111:1111:1111:1111:1111:1111:1111:1111|51200\r\n*/
#define NATPT_FTP_MIN_EPRT_CMD_LEN    16/*EPRT |2|1::1|5\r\n*/
#define NATPT_FTP_CMD_STRING_CNT      5
#define NATPT_FTP_NUMOFCOMMA          4
#define NATPT_FTP_MINPORTCMDLEN       18/*PORT 1,1,1,1,1,1\r\n*/
#define NATPT_FTP_MAXPORTCMDLEN       30/*PORT 255,255,255,255,255,255\r\n*/
#define NATPT_FTP_MIN227CMDLEN        41/*227 Entering Passive Mode (1,1,1,1,1,1)\r\n*/
#define NATPT_FTP_MAX227CMDLEN        55/*227 Entering Passive Mode (255,255,255,255,255,255)\r\n*/
#define NATPT_FTP_MIN229CMDLEN        42/*229 Entering extended passive mode |||1|\r\n*/
#define NATPT_FTP_MAX229CMDLEN        46/*229 Entering extended passive mode |||12222|\r\n*/

#define NATPT_FTP_MAX_EPSV_CMD_LEN    10/*"EPSV 2\r\n"*/
#define NATPT_FTP_PASV_CMD_LEN        6
#define NATPT_FTP_200CMD_STR_LEN      4
#define NATPT_FTP_229CMD_STR_LEN      4
#define NATPT_FTP_EPSV_CMD_LEN        8
#define NATPT_FTP_GENERAL_CMD_STRLEN  10
#define NATPT_FTP_OUPUT_CMD_STRLEN    100

/*----------------------------------------------*
 * Header Files                
 *----------------------------------------------*/

ULONG NATPT_FTP_ALG_IPv4toIPv6(MBUF_S *pstMBufIn, MBUF_S **ppstMBufOut, VOID* pstHash,USHORT usHdrLen,UCHAR ucProtocol);
ULONG NATPT_FTP_ALG_IPv6toIPv4(MBUF_S *pstMBufIn, MBUF_S **ppstMBufOut, VOID* pstHash,USHORT usHdrLen,UCHAR ucProtocol);

ULONG NATPT_FTPALG_Translate_EPRT(IP6_S *pstIP6,TCPHDR_S* pstTCPHdr, UCHAR* pucFtpData, USHORT usFtpDataLen, 
                                  NATPT_PKTCHAR_S *pstPktChar,UCHAR* pucFtpDataOut,SHORT* psPayloadLenDiff);
ULONG NATPT_FTP_ALG_Translate_EPSV (IP6_S *pstIP6,TCPHDR_S *pstTcpHdr,USHORT usFtpDataLen,NATPT_PKTCHAR_S *pstPktChar, UCHAR* pucFtpDataOut,SHORT* psPayloadLenDiff);
ULONG NATPT_FTP_ALG_Translate_229 (IP6_S* pstIP6,TCPHDR_S* pstTCPHdr,UCHAR* pucFtpData,USHORT usFtpDataLen,
                                      NATPT_PKTCHAR_S *pstPktChar, UCHAR* pucFtpDataOut, SHORT* psPayloadLenDiff);
ULONG NATPT_FTP_ALG_Translate_V6ToV4_200 (TCPHDR_S* pstTCPHdr,UCHAR* pucFtpData,NATPT_PKTCHAR_S *pstPktChar);
 
ULONG NATPT_FTP_ALG_Translate_PORT (IP_S *pstIpHdr , TCPHDR_S *pstTcpHdr,UCHAR  *pucFtpCommand, USHORT usFtpDataLen,
                                    NATPT_PKTCHAR_S *pstPktChar, UCHAR* pucFtpDataOut, SHORT *psPayloadLenOffset);
ULONG NATPT_FTP_ALG_Translate_227 (IP_S *pstIpHdr , TCPHDR_S *pstTcpHdr,UCHAR  *pucFtpCommand, USHORT usFtpDataLen,
                                    NATPT_PKTCHAR_S *pstPktChar, UCHAR* pucFtpDataOut, SHORT *psPayloadLenOffset);
ULONG NATPT_FTP_ALG_Translate_PASV (IP_S *pstIpHdr,TCPHDR_S *pstTcpHdr,USHORT usFtpDataLen,
                                    NATPT_PKTCHAR_S *pstPktChar,UCHAR* pucFtpDataOut, SHORT *psPayloadLenOffset);
ULONG NATPT_FTP_ALG_Translate_V4ToV6_200 (TCPHDR_S* pstTCPHdr,UCHAR* pucFtpData, NATPT_PKTCHAR_S *pstPktChar);
ULONG NATPT_FTP_ALG_WriteDataInMBuf(MBUF_S *pstMBufIn, TCPHDR_S *pstTcpHdr,UCHAR  *pucFtpCommand,USHORT usFtpDataLen,
                                     UCHAR *pucNewFtpCommand, SHORT  sPayloadLenOffset, USHORT usHdrLen, UCHAR ucDirection);

ULONG NATPT_FTP_Amend_SequenceNumber (NATPT_PKTCHAR_S *pstPktchar, LONG lPayloadOffset, UCHAR ucDirection, LONG *plNewDataOffset);
ULONG NATPT_FTP_Retrieve_Sequence_Number_Offset (NATPT_PKTCHAR_S *pstPktchar, UCHAR ucPktDirection, UCHAR ucOffsetDir, LONG *plDataOffset);



#ifdef  __cplusplus
}
#endif

#endif

