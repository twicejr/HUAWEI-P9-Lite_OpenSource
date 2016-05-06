/* ssl/ssl3.h */
/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
  All rights reserved.
 
  This package is an SSL implementation written
  by Eric Young (eay@cryptsoft.com).
  The implementation was written so as to conform with Netscapes SSL.
  
  This library is free for commercial and non-commercial use as long as
  the following conditions are aheared to.  The following conditions
  apply to all code found in this distribution, be it the RC4, RSA,
  lhash, DES, etc., code; not just the SSL code.  The SSL documentation
  included with this distribution is covered by the same copyright terms
  except that the holder is Tim Hudson (tjh@cryptsoft.com).
  
  Copyright remains Eric Young's, and as such any Copyright notices in
  the code are not to be removed.
  If this package is used in a product, Eric Young should be given attribution
  as the author of the parts of the library used.
  This can be in the form of a textual message at program startup or
  in documentation (online or textual) provided with the package.
  
  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:
  1. Redistributions of source code must retain the copyright
     notice, this list of conditions and the following disclaimer.
  2. Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
  3. All advertising materials mentioning features or use of this software
     must display the following acknowledgement:
     "This product includes cryptographic software written by
      Eric Young (eay@cryptsoft.com)"
     The word 'cryptographic' can be left out if the rouines from the library
     being used are not cryptographic related :-).
  4. If you include any Windows specific code (or a derivative thereof) from 
     the apps directory (application code) you must include an acknowledgement:
     "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
  
  THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
  OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
  SUCH DAMAGE.
  
  The licence and distribution terms for any publically available version or
  derivative of this code cannot be changed.  i.e. this code cannot simply be
  copied and put under another distribution licence
  [including the GNU Public Licence.]
 */
/* ====================================================================
  Copyright (c) 1998-2002 The OpenSSL Project.  All rights reserved.
 
  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:
 
  1. Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer. 
 
  2. Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
 
  3. All advertising materials mentioning features or use of this
     software must display the following acknowledgment:
     "This product includes software developed by the OpenSSL Project
     for use in the OpenSSL Toolkit. (http://www.openssl.org/)"
 
  4. The names "OpenSSL Toolkit" and "OpenSSL Project" must not be used to
     endorse or promote products derived from this software without
     prior written permission. For written permission, please contact
     openssl-core@openssl.org.
 
  5. Products derived from this software may not be called "OpenSSL"
     nor may "OpenSSL" appear in their names without prior written
     permission of the OpenSSL Project.
 
  6. Redistributions of any form whatsoever must retain the following
     acknowledgment:
     "This product includes software developed by the OpenSSL Project
     for use in the OpenSSL Toolkit (http://www.openssl.org/)"
 
  THIS SOFTWARE IS PROVIDED BY THE OpenSSL PROJECT ``AS IS'' AND ANY
  EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
  PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE OpenSSL PROJECT OR
  ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
  OF THE POSSIBILITY OF SUCH DAMAGE.
  ====================================================================
 
  This product includes cryptographic software written by Eric Young
  (eay@cryptsoft.com).  This product includes software written by Tim
  Hudson (tjh@cryptsoft.com).
 
 */
/* ====================================================================
  Copyright 2002 Sun Microsystems, Inc. ALL RIGHTS RESERVED.
  ECC cipher suite support in OpenSSL originally developed by 
  SUN MICROSYSTEMS, INC., and contributed to the OpenSSL project.
 */


//lint -e958

#include "ipsi_ssl_build_conf.h"

#ifndef _IPSI_HEADER_SSL3_H 
#define _IPSI_HEADER_SSL3_H 


#include "ipsi_types.h"
#include "sec_sys.h"
#include "sec_crypto.h"
#include "sec_list.h"

#ifdef  __cplusplus
extern "C" {
#endif
/*forward declaration of cipher structure*/
struct stSSLCipher;
/*forward declaration of compression structure*/
struct stSSLComp;


/* 
  Below given are the ids of cipher suites supported for ssl3.
  The corresponding ids which can be found in draft-freier-ssl-version3-02.txt
  are given alongside
 */

#define SSL3_CK_RSA_NULL_MD5			0x03000001			/*SSL_RSA_WITH_NULL_MD5              */
#define SSL3_CK_RSA_NULL_SHA			0x03000002			/*SSL_RSA_WITH_NULL_SHA              */
#define SSL3_CK_RSA_RC4_40_MD5 			0x03000003			/*SSL_RSA_EXPORT_WITH_RC4_40_MD5     */
#define SSL3_CK_RSA_RC4_128_MD5			0x03000004			/*SSL_RSA_WITH_RC4_128_MD5           */
#define SSL3_CK_RSA_RC4_128_SHA			0x03000005			/*SSL_RSA_WITH_RC4_128_SHA           */
#define SSL3_CK_RSA_DES_40_CBC_SHA		0x03000008			/*SSL_RSA_EXPORT_WITH_DES40_CBC_SHA  */
#define SSL3_CK_RSA_DES_64_CBC_SHA		0x03000009			/*SSL_RSA_WITH_DES_CBC_SHA           */
#define SSL3_CK_RSA_DES_192_CBC3_SHA		0x0300000A		/*SSL_RSA_WITH_3DES_EDE_CBC_SHA      */

#define SSL3_CK_EDH_DSS_DES_40_CBC_SHA		0x03000011		/*SSL_DHE_DSS_EXPORT_WITH_DES40_CBC_SHA */
#define SSL3_CK_EDH_DSS_DES_64_CBC_SHA		0x03000012		/*SSL_DHE_DSS_WITH_DES_CBC_SHA          */
#define SSL3_CK_EDH_DSS_DES_192_CBC3_SHA	0x03000013		/*SSL_DHE_DSS_WITH_3DES_EDE_CBC_SHA     */
#define SSL3_CK_EDH_RSA_DES_40_CBC_SHA		0x03000014		/*SSL_DHE_RSA_EXPORT_WITH_DES40_CBC_SHA */
#define SSL3_CK_EDH_RSA_DES_64_CBC_SHA		0x03000015		/*SSL_DHE_RSA_WITH_DES_CBC_SHA          */
#define SSL3_CK_EDH_RSA_DES_192_CBC3_SHA	0x03000016		/*SSL_DHE_RSA_WITH_3DES_EDE_CBC_SHA     */

#define SSL3_CK_ADH_RC4_40_MD5			0x03000017			/*SSL_DH_anon_EXPORT_WITH_RC4_40_MD5    */
#define SSL3_CK_ADH_RC4_128_MD5			0x03000018			/*SSL_DH_anon_WITH_RC4_128_MD5          */
#define SSL3_CK_ADH_DES_40_CBC_SHA		0x03000019			/*SSL_DH_anon_EXPORT_WITH_DES40_CBC_SHA */
#define SSL3_CK_ADH_DES_64_CBC_SHA		0x0300001A			/*SSL_DH_anon_WITH_DES_CBC_SHA          */
#define SSL3_CK_ADH_DES_192_CBC3_SHA		0x0300001B			/*SSL_DH_anon_WITH_3DES_EDE_CBC_SHA     */

/*#define SSL3_CK_RSA_SCB2_128_CBC_SHA		0x0300001C*/	/*SSL_RSA_WITH_SCB2_SHA           */
/*#define SSL3_CK_RSA_SCB2_256_CBC_SHA    0x0300001D*/

/* The strings for each cipher. IDs can be got by s/TXT/CK/ */
#define SSL3_TXT_RSA_NULL_MD5			"NULL-MD5"
#define SSL3_TXT_RSA_NULL_SHA			"NULL-SHA"
#define SSL3_TXT_RSA_RC4_40_MD5 		"EXP-RC4-MD5"
#define SSL3_TXT_RSA_RC4_128_MD5		"RC4-MD5"
#define SSL3_TXT_RSA_RC4_128_SHA		"RC4-SHA"
#define SSL3_TXT_RSA_DES_40_CBC_SHA		"EXP-DES-CBC-SHA"
#define SSL3_TXT_RSA_DES_64_CBC_SHA		"DES-CBC-SHA"
#define SSL3_TXT_RSA_DES_192_CBC3_SHA		"DES-CBC3-SHA"

#define SSL3_TXT_EDH_DSS_DES_40_CBC_SHA		"EXP-EDH-DSS-DES-CBC-SHA"
#define SSL3_TXT_EDH_DSS_DES_64_CBC_SHA		"EDH-DSS-DES-CBC-SHA"
#define SSL3_TXT_EDH_DSS_DES_192_CBC3_SHA	"EDH-DSS-DES-CBC3-SHA"
#define SSL3_TXT_EDH_RSA_DES_40_CBC_SHA		"EXP-EDH-RSA-DES-CBC-SHA"
#define SSL3_TXT_EDH_RSA_DES_64_CBC_SHA		"EDH-RSA-DES-CBC-SHA"
#define SSL3_TXT_EDH_RSA_DES_192_CBC3_SHA	"EDH-RSA-DES-CBC3-SHA"

#define SSL3_TXT_ADH_RC4_40_MD5			"EXP-ADH-RC4-MD5"
#define SSL3_TXT_ADH_RC4_128_MD5		"ADH-RC4-MD5"
#define SSL3_TXT_ADH_DES_40_CBC_SHA		"EXP-ADH-DES-CBC-SHA"
#define SSL3_TXT_ADH_DES_64_CBC_SHA		"ADH-DES-CBC-SHA"
#define SSL3_TXT_ADH_DES_192_CBC_SHA		"ADH-DES-CBC3-SHA"

/*#define SSL3_TXT_RSA_SCB2_128_CBC_SHA         "SCB2-128-CBC-SHA"*/
/*#define SSL3_TXT_RSA_SCB2_256_CBC_SHA         "SCB2-256-CBC-SHA"*/

#define SSL3_SSL_SESSION_ID_LENGTH		32
#define SSL3_MAX_SSL_SESSION_ID_LENGTH		32

#define SSL3_MASTER_SECRET_SIZE			48
#define SSL3_RANDOM_SIZE			32
#define SSL3_SESSION_ID_SIZE			32
#define SSL3_RT_HEADER_LENGTH			5

/* Due to MS stuffing up, this can change.... */

#define SSL3_RT_MAX_EXTRA			(16384)


/* Maximum plaintext length: defined by SSL/TLS standards */
#define IPSI_SSL3_RT_MAX_PLAIN_LENGTH	 16384

/*TLS_CHANGE- chetna - begin*/

/*TLS_CHANGE- chetna - end*/

/* This is the maximum MAC (digest) size used by the SSL library.
 * Currently maximum of 20 is used by SHA1, but we reserve for
 * future extension for 512-bit hashes.
 */

#define IPSI_SSL3_RT_MAX_MD_SIZE             64

/* Maximum block size used in all ciphersuites. Currently 16 for AES.
 */

#define IPSI_SSL_RT_MAX_CIPHER_BLOCK_SIZE    16


/* Maximum compression overhead: defined by SSL/TLS standards */
#define IPSI_SSL3_RT_MAX_COMPRESSED_OVERHEAD    1024

/* The standards give a maximum encryption overhead of 1024 bytes.
 * In practice the value is lower than this. The overhead is the maximum
 * number of padding bytes (256) plus the mac size.
 */
#define IPSI_SSL3_RT_MAX_ENCRYPTED_OVERHEAD     (256 + IPSI_SSL3_RT_MAX_MD_SIZE)

/* If compression isn't used don't include the compression overhead */

#ifdef SSL_NO_COMP
#define IPSI_SSL3_RT_MAX_COMPRESSED_LENGTH  IPSI_SSL3_RT_MAX_PLAIN_LENGTH
#else
#define IPSI_SSL3_RT_MAX_COMPRESSED_LENGTH (IPSI_SSL3_RT_MAX_PLAIN_LENGTH + IPSI_SSL3_RT_MAX_COMPRESSED_OVERHEAD)
#endif

#define IPSI_SSL3_RT_MAX_ENCRYPTED_LENGTH    (IPSI_SSL3_RT_MAX_ENCRYPTED_OVERHEAD + IPSI_SSL3_RT_MAX_COMPRESSED_LENGTH)


#define SSL3_RT_MAX_DATA_SIZE			(1024*1024)

#define SSL3_MD_CLIENT_FINISHED_CONST	"\x43\x4C\x4E\x54"
#define SSL3_MD_SERVER_FINISHED_CONST	"\x53\x52\x56\x52"

#define SSL3_VERSION			0x0300
#define SSL3_VERSION_MAJOR		0x03
#define SSL3_VERSION_MINOR		0x00

#define SSL3_RT_CHANGE_CIPHER_SPEC	20
#define SSL3_RT_ALERT			21
#define SSL3_RT_HANDSHAKE		22
#define SSL3_RT_APPLICATION_DATA	23

#define SSL3_AL_WARNING			1
#define SSL3_AL_FATAL			2

#define SSL3_AD_CLOSE_NOTIFY		 0
#define SSL3_AD_UNEXPECTED_MESSAGE	10	/* fatal */
#define SSL3_AD_BAD_RECORD_MAC		20	/* fatal */
#define SSL3_AD_DECOMPRESSION_FAILURE	30	/* fatal */
#define SSL3_AD_HANDSHAKE_FAILURE	40	/* fatal */
#define SSL3_AD_NO_CERTIFICATE		41
#define SSL3_AD_BAD_CERTIFICATE		42
#define SSL3_AD_UNSUPPORTED_CERTIFICATE	43
#define SSL3_AD_CERTIFICATE_REVOKED	44
#define SSL3_AD_CERTIFICATE_EXPIRED	45
#define SSL3_AD_CERTIFICATE_UNKNOWN	46
#define SSL3_AD_ILLEGAL_PARAMETER	47	/* fatal */

/* TLS_CHANGE - BEGIN
  Binil 
  Naming convention changes */
/* structure to hold the SSL 3 record */

/**
* @defgroup ssl3
* This section contains ssl3 Structures
*/

/**
* @defgroup ssl3Structures
* @ingroup ssl3
* This section contains the ssl3 Structures.
*/

/**
* @defgroup SSL3_RECORD_S
* @ingroup ssl3Structures
* @par Prototype
* @code
* typedef struct stSSL3Record
* {
*   SEC_INT	   iType;
*   SEC_UINT   uiLength;
*   SEC_UINT   uiOffset;
*   SEC_UCHAR *pucData;
*   SEC_UCHAR *pucInput;
*   SEC_UCHAR *pucComp;
* } SSL3_RECORD_S;
* @endcode
*
* @par Description
* It is a internal structure used by SSL.  Application should not use it normally.
*
* @datastruct iType Type of record.
* @datastruct uiLength How many bytes are available.
* @datastruct uiOffset Read/write offset into 'buf'.
* @datastruct pucData Pointer to the record data.
* @datastruct pucInput Pointer to the decode bytes.
* @datastruct pucComp This is used only used with decompression - malloc()ed.
*/
typedef struct stSSL3Record
{
/*r */	SEC_INT	 iType;			/* Type of record */
/*rw*/	SEC_UINT uiLength;		/* How many bytes are available */
/*r */	SEC_UINT uiOffset;      /* Read/write offset into 'buf' */
/*rw*/	SEC_UCHAR *pucData;		/* Pointer to the record data */
/*rw*/	SEC_UCHAR *pucInput;	/* Pointer to the decode bytes */
/*r */	SEC_UCHAR *pucComp;		/* This is used only used with decompression - malloc()ed */
/*r */  SEC_UINT uiEpoch;    /* epoch number, needed by DTLS1 */
/*r */  SEC_UCHAR ucSeqNum[8]; /* sequence number, needed by DTLS1 */
/*rw */ SEC_UINT uiOrigLen; /* How many bytes were available before padding was removed, 
							this is used to implement the MAC check in constant time for CBC records*/

} SSL3_RECORD_S;

/* Represents the SSLv3 buffer */

/**
* @defgroup SSL3_BUFFER_S
* @ingroup ssl3Structures
* @par Prototype
* @code
* typedef struct stSSL3Buffer
* {
*	SEC_UCHAR *pucBuf;
*	SEC_UINT   uiLen;
*	SEC_INT    iOffset;
*	SEC_INT    iLeft;
* } SSL3_BUFFER_S;
* @endcode
*
* @par Description
* It is a internal structure used by SSL.  Application should not use it normally.
*
* @datastruct pucBuf This should be atleast SSL3_RT_MAX_PACKET_SIZE bytes, see ssl3_setup_buffers().
* @datastruct uiLen Buffer size.
* @datastruct iOffset Where to 'copy from'.
* @datastruct iLeft How many bytes are left to be copied.
*/
typedef struct stSSL3Buffer
{
	SEC_UCHAR *pucBuf;			/* Atleast SSL3_RT_MAX_PACKET_SIZE bytes,
								 * see ssl3_setup_buffers() */
	SEC_UINT uiLen;             /* Buffer size */
	SEC_INT iOffset;             /* Where to 'copy from' */
	SEC_INT iLeft;               /* How many bytes are left */
} SSL3_BUFFER_S;

#define SSL3_CT_RSA_SIGN			1
#define SSL3_CT_DSS_SIGN			2
#define SSL3_CT_RSA_FIXED_DH			3
#define SSL3_CT_DSS_FIXED_DH			4
#define SSL3_CT_RSA_EPHEMERAL_DH		5
#define SSL3_CT_DSS_EPHEMERAL_DH		6
#define SSL3_CT_FORTEZZA_DMS			20
/* SSL3_CT_NUMBER is used to size arrays and it must be large
  enough to contain all of the cert types defined either for
  SSLv3 and TLSv1.
 */
#define SSL3_CT_NUMBER			7


#define SSL3_FLAGS_NO_RENEGOTIATE_CIPHERS	0x0001
#define SSL3_FLAGS_DELAY_CLIENT_FINISHED	0x0002
#define SSL3_FLAGS_POP_BUFFER				0x0004
#define TLS1_FLAGS_TLS_PADDING_BUG			0x0008

/* IPSI_SSL3_FLAGS_SGC_RESTART_DONE is set when we restart a handshake
 * because of MS SGC and so prevents us from restarting the handshake
 * in a loop. It's reset on a renegotiation, so effectively limits 
 * the client to one restart per negotiation. This limits the possibility 
 * of a DoS attack where the client handshakes in a loop using SGC to
 * restart.Servers which permit renegotiation can still be effected,
 * but we can't prevent that.
 */
#define IPSI_SSL3_FLAGS_SGC_RESTART_DONE	 0x0010

#define IPSI_SSL3_FLAGS_CCS_OK               0x00000020
#define IPSI_DISABLE_SSL3_FLAGS_CCS_OK       0x7FFFFFDF


/* Maximum srvr / clnt finished length can be
 * 36 bytes (for SSL3). Allocating 64 bytes for future */
#define IPSI_SSL_MAX_FINISHED_MSG_LEN           64

/* Satish - 2010-02-16 */

typedef struct stIpsiSecureReneg
{
    /* Connection binding to prevent renegotiation attacks */
    SEC_UCHAR aucPrevClntFinished[IPSI_SSL_MAX_FINISHED_MSG_LEN];
    SEC_UINT uiPrevClntFinishedLen;
    SEC_UCHAR aucPrevSrvrFinished[IPSI_SSL_MAX_FINISHED_MSG_LEN];
    SEC_UINT uiPrevSrvrFinishedLen;
    SEC_INT iSendConnectionBinding; /* TODOEKR */
} IPSI_SSL3_SECURE_RENEG_S;




/*
Structure which holds the information related to the connection state of SSLv3 . 
*/ 

/**
* @defgroup SSL3_STATE_S
* @ingroup ssl3Structures
* @par Prototype
* @code
* typedef struct stSSL3State
* {
*   SEC_INT32 lFlags; 
*   SEC_INT iDelayBufPopRet;
*   SEC_UCHAR aucReadSequence[8];
*   SEC_UCHAR aucReadMACSecret[MAX_DIGEST_SIZE];
*   SEC_UCHAR aucWriteSequence[8];
*   SEC_UCHAR aucWriteMACSecret[MAX_DIGEST_SIZE];
*   SEC_UCHAR aucServerRandom[SSL3_RANDOM_SIZE];
*   SEC_UCHAR aucClientRandom[SSL3_RANDOM_SIZE];
*   SEC_INT iNeedEmptyFragments;
*   SEC_INT iEmptyFragmentDone;
*   SSL3_BUFFER_S stRBuf;
*   SSL3_BUFFER_S stWBuf;
*   SSL3_RECORD_S stRRec;
*   SSL3_RECORD_S stWRec;
*   SEC_UCHAR aucAlertFragment[2];
*   SEC_UINT uiAlertFragmentLen;
*   SEC_UCHAR aucHandshakeFragment[4];
*   SEC_UINT uiHandshakeFragmentLen;
*   SEC_UINT uiWnum;
*   SEC_INT iWpendTot;
*   SEC_INT iWpendType;
*   SEC_INT iWpendRet;
*   const SEC_UCHAR *pucWpendBuf;
*   CRYPT_CTX stFinishDgst1;
*   CRYPT_CTX stFinishDgst2;
*   SEC_INT iChangeCipherSpec;
*   SEC_INT iWarnAlert;
*   SEC_INT iFatalAlert;
*   SEC_INT iAlertDispatch;
*   SEC_UCHAR aucSendAlert[2];
*   SEC_INT iRenegotiate;
*   SEC_INT iTotalRenegotiations;
*   SEC_INT iNumRenegotiations;
*   SEC_INT iPeerRenegotiationReqCount;
*   SEC_INT iInReadAppData;
*   struct	
*    {
*      SEC_UCHAR aucCertVerifyMD[MAX_DIGEST_SIZE*2];
*      SEC_UCHAR aucFinishMD[MAX_DIGEST_SIZE*2];
*      SEC_INT iFinishMDLen;
*      SEC_UCHAR aucPeerFinishMD[MAX_DIGEST_SIZE*2];
*      SEC_INT iPeerFinishMDLen;
*      SEC_UINT32 ulMessageSize;
*      SEC_INT iMessageType;
*      struct stSSLCipher *pstNewCipher;
*      #ifndef SSL_NO_DH
*      SEC_PKEY_S *pstDH;
*      #endif
*      SEC_INT iNextState;
*      SEC_INT iReuseMessage;
*      SEC_INT iCertReq;
*      SEC_INT iTypeNum;
*      SEC_CHAR acType[SSL3_CT_NUMBER];
*      SEC_List_S *pCANames;
*      SEC_INT iUseRSATmp;
*      SEC_INT iKeyBlockLength;
*      SEC_UCHAR *pucKeyBlock;
*      SEC_ALGID_E enNewSymEnc;
*      SEC_ALGID_E enNewHash;
*      #ifndef SSL_NO_COMP
*      const struct stSSLComp  *pNewCompression;
*      #else
*      SEC_CHAR *pNewCompression;
*      #endif
*      SEC_INT iCertRequest;
*    } stTmp;
* } SSL3_STATE_S;
* @endcode
*
* @par Description
* It is a internal structure used by SSL.  Application should not use it normally.
*
* @datastruct lFlags Flag which holds SSL3_FLAGS_NO_RENEGOTIATE_CIPHERS, SSL3_FLAGS_DELAY_CLIENT_FINISHED,
* SSL3_FLAGS_POP_BUFFER.
* @datastruct iDelayBufPopRet Delay to pop the buffer.
* @datastruct aucReadSequence[8] Byte sequences that are chosen by the server and client for each connection.
* @datastruct aucReadMACSecret[MAX_DIGEST_SIZE] Holds read MAC secret key.
* @datastruct aucWriteSequence[8] Byte sequences that are chosen by the server and client for each connection.
* @datastruct aucWriteMACSecret[MAX_DIGEST_SIZE] Holds the write MAC secret.
* @datastruct aucServerRandom[SSL3_RANDOM_SIZE] Holds server random characters.
* @datastruct aucClientRandom[SSL3_RANDOM_SIZE] Holds client random characters.
* @datastruct iNeedEmptyFragments Flags for countermeasure against known-IV weakness.
* @datastruct iEmptyFragmentDone Flags for countermeasure against known-IV weakness.
* @datastruct stRBuf Read IO goes into here.
* @datastruct stWBuf Write IO goes into here.
* @datastruct stRRec Each decoded record goes in here.
* @datastruct stWRec Each decoded record goes out from here.
* @datastruct aucAlertFragment[2] Holds the alert fragment.
* @datastruct uiAlertFragmentLen  Holds the Alert fragment length.
* @datastruct aucHandshakeFragment[4] Holds the Handshake data.
* @datastruct uiHandshakeFragmentLen Holds the Handshake data length.
* @datastruct uiWnum Number of bytes sent so far(for Partial write).
* @datastruct iWpendTot Number of bytes written.
* @datastruct iWpendType Pending data length.
* @datastruct iWpendRet Number of bytes submitted.
* @datastruct pucWpendBuf Pending buffer to be written.
* @datastruct stFinishDgst1 Used during startup, digest all incoming/outgoing packets.
* @datastruct stFinishDgst2 Used during startup, digest all incoming/outgoing packets.
* @datastruct iChangeCipherSpec This is set whenever we see a change_cipher_spec message coming in when we are not
* looking for one.
* @datastruct iWarnAlert Holds warning alert message.
* @datastruct iFatalAlert Holds fatal alert message.
* @datastruct iAlertDispatch Alert dispatch flag.
* @datastruct aucSendAlert[2] Holds the alert that has to be sent.
* @datastruct iRenegotiate This is the renegotiate flag which is set when we should renegotiate 
* as soon as possible, basically when there is no more data in the read or write buffers.
* @datastruct iTotalRenegotiations Holds total number of regenetiation allowed.
* @datastruct iNumRenegotiations Holds total number of regenetiation happened.
* @datastruct iPeerRenegotiationReqCount Number of Peer initiated handshake
* @datastruct iInReadAppData Number of application data read.
* @datastruct stTmp Temperuary structure to hold the data received from the peer.
* @datastruct aucCertVerifyMD[MAX_DIGEST_SIZE*2] Actually only needs to be 16+20.
* @datastruct aucFinishMD[MAX_DIGEST_SIZE*2] Holds the finish message digest.
* @datastruct iFinishMDLen Finish message digest length.
* @datastruct aucPeerFinishMD[MAX_DIGEST_SIZE*2] Holds peer finish message digest.
* @datastruct iPeerFinishMDLen Holds peer finish message digest length.
* @datastruct ulMessageSize Holds message size.
* @datastruct iMessageType Holds message type.
* @datastruct pstNewCipher Used to hold the new cipher we are going to use.
* @datastruct pstDH Holds the DH key.
* @datastruct iNextState Holds next state information.
* @datastruct iReuseMessage Reuse message.
* @datastruct iCertReq Used for certificate requests.
* @datastruct iTypeNum Certificate type to return.
* @datastruct acType[SSL3_CT_NUMBER] Certificate type.
* @datastruct pCANames List of CA names.
* @datastruct iUseRSATmp Temperuary RSA to be used.
* @datastruct iKeyBlockLength Length of key block.
* @datastruct pucKeyBlock Key block.
* @datastruct enNewSymEnc New algorithm for symmetric encryption.
* @datastruct enNewHash New algorithm for hashing.
* @datastruct pNewCompression New compression algorithm.
* @datastruct iCertRequest Certificate request flag.
*/
typedef struct stSSL3State
{
	/*Flag which  holds SSL3_FLAGS_NO_RENEGOTIATE_CIPHERS,
	SSL3_FLAGS_DELAY_CLIENT_FINISHED, SSL3_FLAGS_POP_BUFFER*/
	SEC_INT32 lFlags; 
	
	SEC_INT iDelayBufPopRet; /*Delay to pop the buffer*/

	SEC_UCHAR aucReadSequence[8]; /*Byte sequences that are chosen by the server and client for each connection*/
	SEC_UCHAR aucReadMACSecret[MAX_DIGEST_SIZE];/*Holds read MAC secret key */
	SEC_UCHAR aucWriteSequence[8];/*Byte sequences that are chosen by the server and client for each connection*/
	SEC_UCHAR aucWriteMACSecret[MAX_DIGEST_SIZE];/*Holds the write MAC secret */

	SEC_UCHAR aucServerRandom[SSL3_RANDOM_SIZE];/* Holds server random characters */
	SEC_UCHAR aucClientRandom[SSL3_RANDOM_SIZE];/*Holds client random characters */

	/* Flags for countermeasure against known-IV weakness */
	SEC_INT iNeedEmptyFragments;
	SEC_INT iEmptyFragmentDone;

	SSL3_BUFFER_S stRBuf;	/* Read IO goes into here */
	SSL3_BUFFER_S stWBuf;	/* Write IO goes into here */

	SSL3_RECORD_S stRRec;	/* Each decoded record goes in here */
	SSL3_RECORD_S stWRec;	/* Goes out from here */

	/* Storage for Alert/Handshake protocol data received but not
	   yet processed by ssl3_read_bytes: */
	SEC_UCHAR aucAlertFragment[2];/* Holds alert fragment*/
	SEC_UINT uiAlertFragmentLen; /* Alert fragment length*/
	SEC_UCHAR aucHandshakeFragment[4];/* Handshake data*/
	SEC_UINT uiHandshakeFragmentLen; /* Handshake data length */ 

	/* Partial write - check the numbers match */
	SEC_UINT uiWnum;	/* Number of bytes sent so far */
	SEC_INT iWpendTot;		/* Number of bytes written */
	SEC_INT iWpendType; /* Pending data length */ 
	SEC_INT iWpendRet;		/* Number of bytes submitted */
	const SEC_UCHAR *pucWpendBuf; /* Pending buffer to be written*/ 


    /* Used during startup, digest all incoming/outgoing packets */
	CRYPT_CTX stFinishDgst1;
	CRYPT_CTX stFinishDgst2;


	/* This is set whenerver we see a change_cipher_spec message
	  come in when we are not looking for one */
	SEC_INT iChangeCipherSpec;

	SEC_INT iWarnAlert;/* Holds warning alert message*/ 
	SEC_INT iFatalAlert;/*Holds fatal alert message */ 
	/* We allow one fatal and one warning alert to be outstanding,
	  send close alert via the warning alert */
	SEC_INT iAlertDispatch;/* Alert dispatch flag*/ 
	SEC_UCHAR aucSendAlert[2];/* Alert that has to be sent */ 

	/* This flag is set when we should renegotiate ASAP, basically when
	 * there is no more data in the read or write buffers */
	SEC_INT iRenegotiate;/* Renegotiate flag*/ 
	SEC_INT iTotalRenegotiations;/*Holds total number of regenetiation allowed */ 
	SEC_INT iNumRenegotiations;/* Holds total number of regenetiation happened */ 
    SEC_INT iPeerRenegotiationReqCount;

	SEC_INT iInReadAppData;/*Number of application data read*/ 
	/*Temperuary structure to hold the data received from the peer*/
	struct	
	{
		/* Actually only needs to be 16+20 */
		SEC_UCHAR aucCertVerifyMD[MAX_DIGEST_SIZE*2];

		/* actually only need to be 16+20 for SSLv3 and 12 for TLS */
		SEC_UCHAR aucFinishMD[MAX_DIGEST_SIZE*2]; /* holds the finish message digest */
		SEC_INT iFinishMDLen;/* finish message digest length */
		SEC_UCHAR aucPeerFinishMD[MAX_DIGEST_SIZE*2];/* holds peer finish message digest */
		SEC_INT iPeerFinishMDLen;/* holds peer finish message digest length*/
		
		SEC_UINT32 ulMessageSize;/* holds message size*/
		SEC_INT iMessageType;/*holds message type */

		/* used to hold the new cipher we are going to use */
		struct stSSLCipher *pstNewCipher;
#ifndef SSL_NO_DH

        SEC_PKEY_S *pstDH;/* holds DH key*/
#endif

#ifndef SSL_NO_ECDH

#endif

		/* used when SSL_ST_FLUSH_DATA is entered */
		SEC_INT iNextState;			/* holds next state information */

		SEC_INT iReuseMessage;/*reuse message */

		SEC_INT iCertReq;		/* used for certificate requests */
		SEC_INT iTypeNum;/* certificate type to return*/
		SEC_CHAR acType[SSL3_CT_NUMBER]; /* certificate type*/
		/*TLS_CHANGE Sandeep Start Stack replacement */
		/* STACK_OF(X509_NAME) *pCANames;*/
		SEC_List_S *pCANames;/*list of CA names */
		/*TLS_CHANGE Sandeep END */

		SEC_INT iUseRSATmp;/* temperuary RSA to be used*/

		SEC_INT iKeyBlockLength;/*length of key block  */
		SEC_UCHAR *pucKeyBlock;/* key block */


        SEC_ALGID_E enNewSymEnc;/* new algorithm for symmetric encryption*/
		SEC_ALGID_E enNewHash;/* new algorithm for hashing */

#ifndef SSL_NO_COMP
		const struct stSSLComp  *pNewCompression;/* new compression algorithm*/
#else
		SEC_CHAR *pNewCompression;			/* new compression algorithm */
#endif
		SEC_INT iCertRequest;/* certificate request flag */

	} stTmp;

    /* Satish - 2010-02-16 */
    IPSI_SSL3_SECURE_RENEG_S stSecRenegParams;

    /* Satish - 2010-02-16 */

#ifndef IPSI_NO_TLS12 

    CRYPT_CTX stFinishDgstSha224;
    CRYPT_CTX stFinishDgstSha256;
    CRYPT_CTX stFinishDgstSha384;
    CRYPT_CTX stFinishDgstSha512;
#endif

} SSL3_STATE_S;

/* TLS_CHANGE - END */

/* SSLv3 */
/*client */
/* extra state */
#define SSL3_ST_CW_FLUSH			(0x100|SSL_ST_CONNECT)
/* write to server */
#define SSL3_ST_CW_CLNT_HELLO_A		(0x110|SSL_ST_CONNECT)
#define SSL3_ST_CW_CLNT_HELLO_B		(0x111|SSL_ST_CONNECT)
/* read from server */
#define SSL3_ST_CR_SRVR_HELLO_A		(0x120|SSL_ST_CONNECT)
#define SSL3_ST_CR_SRVR_HELLO_B		(0x121|SSL_ST_CONNECT)
#define DTLS1_ST_CR_HELLO_VERIFY_REQUEST_A (0x126|SSL_ST_CONNECT)
#define DTLS1_ST_CR_HELLO_VERIFY_REQUEST_B (0x127|SSL_ST_CONNECT)
#define SSL3_ST_CR_CERT_A			(0x130|SSL_ST_CONNECT)
#define SSL3_ST_CR_CERT_B			(0x131|SSL_ST_CONNECT)
#define SSL3_ST_CR_KEY_EXCH_A		(0x140|SSL_ST_CONNECT)
#define SSL3_ST_CR_KEY_EXCH_B		(0x141|SSL_ST_CONNECT)
#define SSL3_ST_CR_CERT_REQ_A		(0x150|SSL_ST_CONNECT)
#define SSL3_ST_CR_CERT_REQ_B		(0x151|SSL_ST_CONNECT)
#define SSL3_ST_CR_SRVR_DONE_A		(0x160|SSL_ST_CONNECT)
#define SSL3_ST_CR_SRVR_DONE_B		(0x161|SSL_ST_CONNECT)
/* write to server */
#define SSL3_ST_CW_CERT_A			(0x170|SSL_ST_CONNECT)
#define SSL3_ST_CW_CERT_B			(0x171|SSL_ST_CONNECT)
#define SSL3_ST_CW_CERT_C			(0x172|SSL_ST_CONNECT)
#define SSL3_ST_CW_CERT_D			(0x173|SSL_ST_CONNECT)
#define SSL3_ST_CW_KEY_EXCH_A		(0x180|SSL_ST_CONNECT)
#define SSL3_ST_CW_KEY_EXCH_B		(0x181|SSL_ST_CONNECT)
#define SSL3_ST_CW_CERT_VRFY_A		(0x190|SSL_ST_CONNECT)
#define SSL3_ST_CW_CERT_VRFY_B		(0x191|SSL_ST_CONNECT)
#define SSL3_ST_CW_CHANGE_A			(0x1A0|SSL_ST_CONNECT)
#define SSL3_ST_CW_CHANGE_B			(0x1A1|SSL_ST_CONNECT)
#define SSL3_ST_CW_FINISHED_A		(0x1B0|SSL_ST_CONNECT)
#define SSL3_ST_CW_FINISHED_B		(0x1B1|SSL_ST_CONNECT)
/* read from server */
#define SSL3_ST_CR_CHANGE_A			(0x1C0|SSL_ST_CONNECT)
#define SSL3_ST_CR_CHANGE_B			(0x1C1|SSL_ST_CONNECT)
#define SSL3_ST_CR_FINISHED_A		(0x1D0|SSL_ST_CONNECT)
#define SSL3_ST_CR_FINISHED_B		(0x1D1|SSL_ST_CONNECT)

/* server */
/* extra state */
#define SSL3_ST_SW_FLUSH		(0x100|SSL_ST_ACCEPT)
/* read from client */
/* Do not change the number values, they do matter */
#define SSL3_ST_SR_CLNT_HELLO_A		(0x110|SSL_ST_ACCEPT)
#define SSL3_ST_SR_CLNT_HELLO_B		(0x111|SSL_ST_ACCEPT)
#define SSL3_ST_SR_CLNT_HELLO_C		(0x112|SSL_ST_ACCEPT)
/* write to client */
#define DTLS1_ST_SW_HELLO_VERIFY_REQUEST_A (0x113|SSL_ST_ACCEPT)
#define DTLS1_ST_SW_HELLO_VERIFY_REQUEST_B (0x114|SSL_ST_ACCEPT)
#define SSL3_ST_SW_HELLO_REQ_A		(0x120|SSL_ST_ACCEPT)
#define SSL3_ST_SW_HELLO_REQ_B		(0x121|SSL_ST_ACCEPT)
#define SSL3_ST_SW_HELLO_REQ_C		(0x122|SSL_ST_ACCEPT)
#define SSL3_ST_SW_SRVR_HELLO_A		(0x130|SSL_ST_ACCEPT)
#define SSL3_ST_SW_SRVR_HELLO_B		(0x131|SSL_ST_ACCEPT)
#define SSL3_ST_SW_CERT_A			(0x140|SSL_ST_ACCEPT)
#define SSL3_ST_SW_CERT_B			(0x141|SSL_ST_ACCEPT)
#define SSL3_ST_SW_KEY_EXCH_A		(0x150|SSL_ST_ACCEPT)
#define SSL3_ST_SW_KEY_EXCH_B		(0x151|SSL_ST_ACCEPT)
#define SSL3_ST_SW_CERT_REQ_A		(0x160|SSL_ST_ACCEPT)
#define SSL3_ST_SW_CERT_REQ_B		(0x161|SSL_ST_ACCEPT)
#define SSL3_ST_SW_SRVR_DONE_A		(0x170|SSL_ST_ACCEPT)
#define SSL3_ST_SW_SRVR_DONE_B		(0x171|SSL_ST_ACCEPT)
/* read from client */
#define SSL3_ST_SR_CERT_A			(0x180|SSL_ST_ACCEPT)
#define SSL3_ST_SR_CERT_B			(0x181|SSL_ST_ACCEPT)
#define SSL3_ST_SR_KEY_EXCH_A		(0x190|SSL_ST_ACCEPT)
#define SSL3_ST_SR_KEY_EXCH_B		(0x191|SSL_ST_ACCEPT)
#define SSL3_ST_SR_CERT_VRFY_A		(0x1A0|SSL_ST_ACCEPT)
#define SSL3_ST_SR_CERT_VRFY_B		(0x1A1|SSL_ST_ACCEPT)
#define SSL3_ST_SR_CHANGE_A			(0x1B0|SSL_ST_ACCEPT)
#define SSL3_ST_SR_CHANGE_B			(0x1B1|SSL_ST_ACCEPT)
#define SSL3_ST_SR_FINISHED_A		(0x1C0|SSL_ST_ACCEPT)
#define SSL3_ST_SR_FINISHED_B		(0x1C1|SSL_ST_ACCEPT)
/* write to client */
#define SSL3_ST_SW_CHANGE_A			(0x1D0|SSL_ST_ACCEPT)
#define SSL3_ST_SW_CHANGE_B			(0x1D1|SSL_ST_ACCEPT)
#define SSL3_ST_SW_FINISHED_A		(0x1E0|SSL_ST_ACCEPT)
#define SSL3_ST_SW_FINISHED_B		(0x1E1|SSL_ST_ACCEPT)

#define SSL3_MT_HELLO_REQUEST				0
#define SSL3_MT_CLIENT_HELLO				1
#define SSL3_MT_SERVER_HELLO				2
#define SSL3_MT_CERTIFICATE					11
#define SSL3_MT_SERVER_KEY_EXCHANGE			12
#define SSL3_MT_CERTIFICATE_REQUEST			13
#define SSL3_MT_SERVER_DONE					14
#define SSL3_MT_CERTIFICATE_VERIFY			15
#define SSL3_MT_CLIENT_KEY_EXCHANGE			16
#define SSL3_MT_FINISHED					20
#define IPSI_DTLS1_MT_HELLO_VERIFY_REQUEST		3


#define SSL3_MT_CCS							1

/* These are used when changing over to a new cipher */
#define SSL3_CC_READ						0x01
#define SSL3_CC_WRITE						0x02
#define SSL3_CC_CLIENT						0x10
#define SSL3_CC_SERVER						0x20
#define SSL3_CHANGE_CIPHER_CLIENT_WRITE		(SSL3_CC_CLIENT|SSL3_CC_WRITE)	
#define SSL3_CHANGE_CIPHER_SERVER_READ		(SSL3_CC_SERVER|SSL3_CC_READ)
#define SSL3_CHANGE_CIPHER_CLIENT_READ		(SSL3_CC_CLIENT|SSL3_CC_READ)
#define SSL3_CHANGE_CIPHER_SERVER_WRITE		(SSL3_CC_SERVER|SSL3_CC_WRITE)

#ifdef  __cplusplus
}
#endif
#endif // _IPSI_HEADER_SSL3_H


//lint +e958



