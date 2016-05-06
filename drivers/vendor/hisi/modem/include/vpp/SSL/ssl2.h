/* ssl/ssl2.h */
/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * This package is an SSL implementation written
 * by Eric Young (eay@cryptsoft.com).
 * The implementation was written so as to conform with Netscapes SSL.
 * 
 * This library is free for commercial and non-commercial use as long as
 * the following conditions are aheared to.  The following conditions
 * apply to all code found in this distribution, be it the RC4, RSA,
 * lhash, DES, etc., code; not just the SSL code.  The SSL documentation
 * included with this distribution is covered by the same copyright terms
 * except that the holder is Tim Hudson (tjh@cryptsoft.com).
 * 
 * Copyright remains Eric Young's, and as such any Copyright notices in
 * the code are not to be removed.
 * If this package is used in a product, Eric Young should be given attribution
 * as the author of the parts of the library used.
 * This can be in the form of a textual message at program startup or
 * in documentation (online or textual) provided with the package.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    "This product includes cryptographic software written by
 *     Eric Young (eay@cryptsoft.com)"
 *    The word 'cryptographic' can be left out if the rouines from the library
 *    being used are not cryptographic related :-).
 * 4. If you include any Windows specific code (or a derivative thereof) from 
 *    the apps directory (application code) you must include an acknowledgement:
 *    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
 * 
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * 
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.  i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.]
 */

#include "ipsi_ssl_build_conf.h"

#ifndef _IPSI_HEADER_SSL2_H 
#define _IPSI_HEADER_SSL2_H 

#include "ipsi_types.h"

#ifdef  __cplusplus
extern "C" {
#endif

/* Protocol Version Codes */
#define SSL2_VERSION							0x0002
#define SSL2_VERSION_MAJOR						0x00
#define SSL2_VERSION_MINOR						0x02

/* Protocol Message Codes */
#define SSL2_MT_ERROR							0
#define SSL2_MT_CLIENT_HELLO					1
#define SSL2_MT_CLIENT_MASTER_KEY				2
#define SSL2_MT_CLIENT_FINISHED					3
#define SSL2_MT_SERVER_HELLO					4
#define SSL2_MT_SERVER_VERIFY					5
#define SSL2_MT_SERVER_FINISHED					6
#define SSL2_MT_REQUEST_CERTIFICATE				7
#define SSL2_MT_CLIENT_CERTIFICATE				8

/* Error Message Codes */
#define SSL2_PE_UNDEFINED_ERROR					0x0000
#define SSL2_PE_NO_CIPHER						0x0001
#define SSL2_PE_NO_CERTIFICATE					0x0002
#define SSL2_PE_BAD_CERTIFICATE					0x0004
#define SSL2_PE_UNSUPPORTED_CERTIFICATE_TYPE	0x0006

/* Cipher Kind Values */
#define SSL2_CK_RC4_128_WITH_MD5				0x02010080
#define SSL2_CK_RC4_128_EXPORT40_WITH_MD5		0x02020080
#define SSL2_CK_DES_64_CBC_WITH_MD5				0x02060040
#define SSL2_CK_DES_192_EDE3_CBC_WITH_MD5		0x020700c0

 
#define SSL2_TXT_RC4_128_WITH_MD5				"RC4-MD5"
#define SSL2_TXT_RC4_128_EXPORT40_WITH_MD5		"EXP-RC4-MD5"
#define SSL2_TXT_DES_64_CBC_WITH_MD5			"DES-CBC-MD5"
#define SSL2_TXT_DES_192_EDE3_CBC_WITH_MD5		"DES-CBC3-MD5"


/* Flags for the SSL_CIPHER.algorithm2 field */
#define SSL2_CF_5_BYTE_ENC						0x01
#define SSL2_CF_8_BYTE_ENC						0x02

/* Certificate Type Codes */
#define SSL2_CT_X509_CERTIFICATE				0x01

/* Authentication Type Code */
#define SSL2_AT_MD5_WITH_RSA_ENCRYPTION			0x01

#define SSL2_MAX_SSL_SESSION_ID_LENGTH			32

/* Upper/Lower Bounds */
#define SSL2_MAX_MASTER_KEY_LENGTH_IN_BITS		256

#define SSL2_MAX_RECORD_LENGTH_2_BYTE_HEADER	32767u  /* 2^15-1 */


#define SSL2_MAX_RECORD_LENGTH_3_BYTE_HEADER	16383	/* 2^14-1 */

#define SSL2_CHALLENGE_LENGTH					16
/*#define SSL2_CHALLENGE_LENGTH					32 */
#define SSL2_MIN_CHALLENGE_LENGTH				16
#define SSL2_MAX_CHALLENGE_LENGTH				32
#define SSL2_CONNECTION_ID_LENGTH				16
#define SSL2_MAX_CONNECTION_ID_LENGTH			16
#define SSL2_SSL_SESSION_ID_LENGTH				16
#define SSL2_MAX_CERT_CHALLENGE_LENGTH			32
#define SSL2_MIN_CERT_CHALLENGE_LENGTH			16
#define SSL2_MAX_KEY_MATERIAL_LENGTH			24

/**
* @defgroup ssl2
* This section contains ssl2 Structure
*/

/**
* @defgroup ssl2Structure
* @ingroup ssl2
* This section contains the ssl2 Structure.
*/


/*
#ifndef HEADER_SSL_LOCL_H
#define  CERT		char
#endif
*/

/*
Structure which holds the information related to the connection state of SSLv2 . 
*/ 

/**
* @defgroup SSL2_STATE_S
* @ingroup ssl2Structure
* @par Prototype
* @code
* typedef struct stSSL2State
* {
*  SEC_INT iThreeByteHeader;
*  SEC_INT iClearText;
*  SEC_INT iEscape;
*  SEC_INT iSSL2Rollback;
*  SEC_UINT uiWnum;
*  SEC_INT iWpendTotal;
*  const SEC_UCHAR *pucWpendBuf;
*  SEC_INT iWpendOffset;
*  SEC_INT iWpendLength;
*  SEC_INT iWpendReturn;
*  SEC_INT iRbufLeft;
*  SEC_INT iRbufOffset;
*  SEC_UCHAR *pucRBuffer;
*  SEC_UCHAR *pucWBuffer;
*  SEC_UCHAR *pucWritePtr;
*  SEC_UINT uiPadding;
*  SEC_UINT uiRlength;
*  SEC_INT	 iRActualDataLength;
*  SEC_UINT uiWLength;
*  SEC_INT  iWActualDataLength;
*  SEC_UCHAR *pucRActData;
*  SEC_UCHAR *pucWActData;
*  SEC_UCHAR *pucMACData;
*  SEC_UCHAR *pucReadKey;
*  SEC_UCHAR *pucWriteKey;
*  SEC_UINT uiChallengeLength;
*  SEC_UCHAR aucChallenge [SSL2_MAX_CHALLENGE_LENGTH];
*  SEC_UINT uiConnectionIdLength;
*  SEC_UCHAR aucConnectionId [SSL2_MAX_CONNECTION_ID_LENGTH];
*  SEC_UINT uiKeyMaterialLength;
*  SEC_UCHAR aucKeyMaterial [SSL2_MAX_KEY_MATERIAL_LENGTH*2];
*  SEC_UINT32 ulReadSequence;
*  SEC_UINT32 ulWriteSequence;
*  struct	
*  {
*   SEC_UINT uiConnIDLength;
*   SEC_UINT uiCertType;
*   SEC_UINT uiCertLength;
*   SEC_UINT uiCSL;
*   SEC_UINT uiClear;
*   SEC_UINT uiEnc;
*   SEC_UCHAR aucCCL [SSL2_MAX_CERT_CHALLENGE_LENGTH];
*   SEC_UINT uiCipherSpecLength;
*   SEC_UINT uiSessionIdLength;
*   SEC_UINT uiCLen;
*   SEC_UINT uiRLen;
*  } stTemp;
* } SSL2_STATE_S;
* @endcode
*
* @par Description
* It is a internal structure used by SSL. Application should not use it normally. 
*
* @datastruct iThreeByteHeader Flag to determine whether it has 2 byte / 3 byte header.
* @datastruct iClearText flag to determine whether it has 2 byte / 3 byte header : whether Clear text(cleartext is the form of a message or data which is in a form that is immediately comprehensible to a human being without additional processing)
* @datastruct iEscape Not used in SSLv2..
* @datastruct iSSL2Rollback flag to determine whether it has 2 byte / 3 byte header : Used if SSLv23 rolled back to SSLv2.
* @datastruct uiWnum  	Non-blocking io info, used to make sure the same args were passed:Number of bytes sent so far.
* @datastruct iWpendTotal  Non-blocking io info, used to make sure the same args were passed:Total number of bytes to be written.
* @datastruct pucWpendBuf  Non-blocking io info, used to make sure the same args were passed : Number of bytes pending in buffer.
* @datastruct iWpendOffset  Non-blocking io info, used to make sure the same args were passed : Offset to data to write.
* @datastruct iWpendLength  	Non-blocking io info, used to make sure the same args were passed : Number of bytes passed to write.
* @datastruct iWpendReturn  	Non-blocking io info, used to make sure the same args were passed : Number of bytes to return to caller.
* @datastruct iRbufLeft Buffer raw data: Number of bytes left that has to be read.
* @datastruct iRbufOffset Buffer raw data: Offset to read buffer.
* @datastruct pucRBuffer Buffer raw data: Read buffer.
* @datastruct pucWBuffer Buffer raw data: Write buffer.
* @datastruct pucWritePtr Buffer raw data: Used to point to the start due to 2/3 byte header.
* @datastruct uiPadding Buffer raw data: Padding.
* @datastruct uiRlength Buffer raw data: decrypt length
* @datastruct iRActualDataLength Buffer raw data: Set when things are encrypted.
* @datastruct uiWLength Buffer raw data: Encrypt length
* @datastruct iWActualDataLength Buffer raw data: Set when things are decrypted.
* @datastruct pucRActData Buffer raw data: Read data.
* @datastruct pucWActData Buffer raw data: Write data.
* @datastruct pucMACData Buffer raw data: MAC data.
* @datastruct pucReadKey Buffer raw data: Read key.
* @datastruct pucWriteKey Buffer raw data: Write key.
* @datastruct uiChallengeLength Stuff specifically to do with this SSL session: challenge data length.
* @datastruct aucChallenge [SSL2_MAX_CHALLENGE_LENGTH] Stuff specifically to do with this SSL session: challege data.
* @datastruct uiConnectionIdLength Stuff specifically to do with this SSL session: connection id len.
* @datastruct aucConnectionId [SSL2_MAX_CONNECTION_ID_LENGTH] Stuff specifically to do with this SSL session:
* Connection ID.
* @datastruct uiKeyMaterialLength Stuff specifically to do with this SSL session: Key material length.
* @datastruct aucKeyMaterial [SSL2_MAX_KEY_MATERIAL_LENGTH*2] Stuff specifically to do with this SSL session: key material.
* @datastruct ulReadSequence Stuff specifically to do with this SSL session: Holds read sequence.
* @datastruct ulWriteSequence Stuff specifically to do with this SSL session: Holds write sequence.
* @datastruct stTemp Temprovery structure to hold the data received from the peer.
* @datastruct uiConnIDLength Connection ID length.
* @datastruct uiCertType Certificate type.
* @datastruct uiCertLength Cert length.
* @datastruct uiCSL Cipher list.
* @datastruct uiClear Flag to clear the data.
* @datastruct uiEnc Encryption flag.
* @datastruct aucCCL [SSL2_MAX_CERT_CHALLENGE_LENGTH] Cert challenge data.
* @datastruct uiCipherSpecLength Length of cipher spec.
* @datastruct uiSessionIdLength Session id length.
* @datastruct uiCLen Certificate length.
* @datastruct uiRLen certificate request length.
*/
typedef struct stSSL2State
{
	/*flag to determine whether it has 2 byte / 3 byte header. */
	SEC_INT iThreeByteHeader;
	
	/*flag to determine whether it has 2 byte / 3 byte header. */
	SEC_INT iClearText;					/* clear text */
	SEC_INT iEscape;					/* not used in SSLv2 */
	SEC_INT iSSL2Rollback;				/* used if SSLv23 rolled back to SSLv2 */

	/* non-blocking io info, used to make sure the same args were passed */
	SEC_UINT uiWnum;					/* number of bytes sent so far */
	SEC_INT iWpendTotal;			/* total number of bytes to be written*/
	const SEC_UCHAR *pucWpendBuf; /* number of bytes pending in buffer */

	SEC_INT iWpendOffset;					/* offset to data to write */
	SEC_INT iWpendLength; 					/* number of bytes passwd to write */
	SEC_INT iWpendReturn; 					/* number of bytes to return to caller */

	/* buffer raw data */
	SEC_INT iRbufLeft; /*number of bytes to left that has to be read*/
	SEC_INT iRbufOffset;/* offset to read buffer*/
	SEC_UCHAR *pucRBuffer; /* read buffer */
	SEC_UCHAR *pucWBuffer;/* write buffer*/

	SEC_UCHAR *pucWritePtr;					/* used to point to the start due to 2/3 byte header. */

	SEC_UINT uiPadding;/*padding */
	SEC_UINT uiRlength;						/* passed to ssl2_enc */
	SEC_INT	 iRActualDataLength;			/* Set when things are encrypted. */
	SEC_UINT uiWLength;						/* passed to ssl2_enc */
	SEC_INT  iWActualDataLength;			/* Set when things are decrypted. */
	SEC_UCHAR *pucRActData;/* read data*/
	SEC_UCHAR *pucWActData;/* write data */
	SEC_UCHAR *pucMACData; /* MAC data*/

	SEC_UCHAR *pucReadKey;/* read key*/
	SEC_UCHAR *pucWriteKey;/* write key*/

	/* Stuff specifically to do with this SSL session */
	SEC_UINT uiChallengeLength; /* challenge data length*/
	SEC_UCHAR aucChallenge [SSL2_MAX_CHALLENGE_LENGTH]; /*challege data */
	SEC_UINT uiConnectionIdLength; /* connection id len */
	SEC_UCHAR aucConnectionId [SSL2_MAX_CONNECTION_ID_LENGTH]; /*connection ID */ 
	SEC_UINT uiKeyMaterialLength; /* key material length */
	SEC_UCHAR aucKeyMaterial [SSL2_MAX_KEY_MATERIAL_LENGTH*2]; /* key material */

	SEC_UINT32 ulReadSequence;/* holds read sequence */
	SEC_UINT32 ulWriteSequence;/* holds write sequence*/
/* temprovery structure to hold the data received from the peer */

	struct	
	{
		SEC_UINT uiConnIDLength; /* connection ID length */
		SEC_UINT uiCertType;	/* certificate type */
		SEC_UINT uiCertLength;/* cert length */
		SEC_UINT uiCSL; /* cipher list*/
		SEC_UINT uiClear;/* flag to clear the data  */
		SEC_UINT uiEnc; /* encryption flag*/
		SEC_UCHAR aucCCL [SSL2_MAX_CERT_CHALLENGE_LENGTH]; /* cert challenge data*/
		SEC_UINT uiCipherSpecLength;/* length of cipher spec*/
		SEC_UINT uiSessionIdLength;/* session id length*/
		SEC_UINT uiCLen;/* certificate length */
		SEC_UINT uiRLen;/* certificate request length*/
	} stTemp;

} SSL2_STATE_S;

/* SSLv2 Client */
#define SSL2_ST_SEND_CLIENT_HELLO_A			(0x10|SSL_ST_CONNECT)
#define SSL2_ST_SEND_CLIENT_HELLO_B			(0x11|SSL_ST_CONNECT)
#define SSL2_ST_GET_SERVER_HELLO_A			(0x20|SSL_ST_CONNECT)
#define SSL2_ST_GET_SERVER_HELLO_B			(0x21|SSL_ST_CONNECT)
#define SSL2_ST_SEND_CLIENT_MASTER_KEY_A	(0x30|SSL_ST_CONNECT)
#define SSL2_ST_SEND_CLIENT_MASTER_KEY_B	(0x31|SSL_ST_CONNECT)
#define SSL2_ST_SEND_CLIENT_FINISHED_A		(0x40|SSL_ST_CONNECT)
#define SSL2_ST_SEND_CLIENT_FINISHED_B		(0x41|SSL_ST_CONNECT)
#define SSL2_ST_SEND_CLIENT_CERTIFICATE_A	(0x50|SSL_ST_CONNECT)
#define SSL2_ST_SEND_CLIENT_CERTIFICATE_B	(0x51|SSL_ST_CONNECT)
#define SSL2_ST_SEND_CLIENT_CERTIFICATE_C	(0x52|SSL_ST_CONNECT)
#define SSL2_ST_SEND_CLIENT_CERTIFICATE_D	(0x53|SSL_ST_CONNECT)
#define SSL2_ST_GET_SERVER_VERIFY_A			(0x60|SSL_ST_CONNECT)
#define SSL2_ST_GET_SERVER_VERIFY_B			(0x61|SSL_ST_CONNECT)
#define SSL2_ST_GET_SERVER_FINISHED_A		(0x70|SSL_ST_CONNECT)
#define SSL2_ST_GET_SERVER_FINISHED_B		(0x71|SSL_ST_CONNECT)
#define SSL2_ST_CLIENT_START_ENCRYPTION		(0x80|SSL_ST_CONNECT)
#define SSL2_ST_X509_GET_CLIENT_CERTIFICATE	(0x90|SSL_ST_CONNECT)

/* SSLv2 Server */
#define SSL2_ST_GET_CLIENT_HELLO_A			(0x10|SSL_ST_ACCEPT)
#define SSL2_ST_GET_CLIENT_HELLO_B			(0x11|SSL_ST_ACCEPT)
#define SSL2_ST_GET_CLIENT_HELLO_C			(0x12|SSL_ST_ACCEPT)
#define SSL2_ST_SEND_SERVER_HELLO_A			(0x20|SSL_ST_ACCEPT)
#define SSL2_ST_SEND_SERVER_HELLO_B			(0x21|SSL_ST_ACCEPT)
#define SSL2_ST_GET_CLIENT_MASTER_KEY_A		(0x30|SSL_ST_ACCEPT)
#define SSL2_ST_GET_CLIENT_MASTER_KEY_B		(0x31|SSL_ST_ACCEPT)
#define SSL2_ST_SEND_SERVER_VERIFY_A		(0x40|SSL_ST_ACCEPT)
#define SSL2_ST_SEND_SERVER_VERIFY_B		(0x41|SSL_ST_ACCEPT)
#define SSL2_ST_SEND_SERVER_VERIFY_C		(0x42|SSL_ST_ACCEPT)
#define SSL2_ST_GET_CLIENT_FINISHED_A		(0x50|SSL_ST_ACCEPT)
#define SSL2_ST_GET_CLIENT_FINISHED_B		(0x51|SSL_ST_ACCEPT)
#define SSL2_ST_SEND_SERVER_FINISHED_A		(0x60|SSL_ST_ACCEPT)
#define SSL2_ST_SEND_SERVER_FINISHED_B		(0x61|SSL_ST_ACCEPT)
#define SSL2_ST_SEND_REQUEST_CERTIFICATE_A	(0x70|SSL_ST_ACCEPT)
#define SSL2_ST_SEND_REQUEST_CERTIFICATE_B	(0x71|SSL_ST_ACCEPT)
#define SSL2_ST_SEND_REQUEST_CERTIFICATE_C	(0x72|SSL_ST_ACCEPT)
#define SSL2_ST_SEND_REQUEST_CERTIFICATE_D	(0x73|SSL_ST_ACCEPT)
#define SSL2_ST_SERVER_START_ENCRYPTION		(0x80|SSL_ST_ACCEPT)
#define SSL2_ST_X509_GET_SERVER_CERTIFICATE	(0x90|SSL_ST_ACCEPT)

#ifdef  __cplusplus
}
#endif

#endif // _IPSI_HEADER_SSL2_H

