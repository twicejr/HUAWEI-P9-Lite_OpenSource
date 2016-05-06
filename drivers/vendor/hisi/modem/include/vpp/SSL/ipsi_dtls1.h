/*****************************************************************************
                                                                            
                Copyright (C), 2008, Huawei Tech. Co., Ltd.                
                            ALL RIGHTS RESERVED                             
                                                                            
------------------------------------------------------------------------------


FileName     :ipsi_dtls1.h 
Author       :V. S. Vinoth Kumar.
Version      :1
Date         :17-07-09
Description  :Describes macros, structures and functions used required for dtls
Function List: 


          History:
                    <author>   <date>          <desc>
----------------------------------------------------------------------------
****************************************************************************/
#include "ipsi_ssl_build_conf.h"

#ifndef HEADER_IPSI_DTLS1_H 
#define HEADER_IPSI_DTLS1_H

#include "ipsi_types.h"
#include "sec_sys.h"
#include "sec_crypto.h"
#include "ssl.h"
#include "ssl3.h"
#include "ipsi_aio.h"

#ifdef  __cplusplus
extern "C" {
#endif

/* DTLS1 Version value */
#define IPSI_DTLS1_VERSION            0xFEFF

#define IPSI_DTLS_MAX_VERSION         IPSI_DTLS1_VERSION

/* Macro for DTLS1 bad version number */
#define IPSI_DTLS1_BAD_VER           0x0100

/* DTLS cookie length */
#define IPSI_DTLS1_COOKIE_LENGTH                     32

/* DTLS1 record Type header length */
#define IPSI_DTLS1_RT_HEADER_LENGTH                  13

/* DTLS1 Handshake Message header length */
#define IPSI_DTLS1_HM_HEADER_LENGTH                  12

/* DTLS1 Handshake Message bad fragment */
#define IPSI_DTLS1_HM_BAD_FRAGMENT                   -2

/* DTLS1 Handshake Message fragment retry */
#define IPSI_DTLS1_HM_FRAGMENT_RETRY                 -3

/* DTLS Change Cipher Spec header length */
#define IPSI_DTLS1_CCS_HEADER_LENGTH                  1

#ifdef IPSI_DTLS1_AD_MISSING_HANDSHAKE_MESSAGE
#define IPSI_DTLS1_AL_HEADER_LENGTH                   7
#else
#define IPSI_DTLS1_AL_HEADER_LENGTH                   2
#endif

#define IPSI_DTLS1_DEFAULT_MTU                        1472

/* Set write AIO */
#define IPSI_SET_WRITE_AIO                    56

/* Get write AIO */
#define IPSI_GET_WRITE_AIO                    57

/* Set read AIO */
#define IPSI_SET_READ_AIO                    58

/* Get read AIO */
#define IPSI_GET_READ_AIO                    59

/*DTLS1 Ciphers*/
#define DTLS1_CK_RSA_NULL_MD5                        SSL3_CK_RSA_NULL_MD5   
#define DTLS1_CK_RSA_NULL_SHA                        SSL3_CK_RSA_NULL_SHA
#define DTLS1_CK_RSA_DES_64_CBC_SHA             SSL3_CK_RSA_DES_64_CBC_SHA 
#define DTLS1_CK_RSA_DES_192_CBC3_SHA         SSL3_CK_RSA_DES_192_CBC3_SHA
#define DTLS1_CK_EDH_DSS_DES_64_CBC_SHA     SSL3_CK_EDH_DSS_DES_64_CBC_SHA 
#define DTLS1_CK_EDH_DSS_DES_192_CBC3_SHA SSL3_CK_EDH_DSS_DES_192_CBC3_SHA
#define DTLS1_CK_EDH_RSA_DES_64_CBC_SHA     SSL3_CK_EDH_RSA_DES_64_CBC_SHA  
#define DTLS1_CK_EDH_RSA_DES_192_CBC3_SHA SSL3_CK_EDH_RSA_DES_192_CBC3_SHA
#define DTLS1_CK_ADH_DES_64_CBC_SHA            SSL3_CK_ADH_DES_64_CBC_SHA    
#define DTLS1_CK_ADH_DES_192_CBC3_SHA         SSL3_CK_ADH_DES_192_CBC3_SHA

/* AES ciphersuites from RFC3268 */
#define DTLS1_CK_RSA_WITH_AES_128_SHA            TLS1_CK_RSA_WITH_AES_128_SHA  
#define DTLS1_CK_DHE_DSS_WITH_AES_128_SHA TLS1_CK_DHE_DSS_WITH_AES_128_SHA
#define DTLS1_CK_DHE_RSA_WITH_AES_128_SHA TLS1_CK_DHE_RSA_WITH_AES_128_SHA 
#define DTLS1_CK_ADH_WITH_AES_128_SHA        TLS1_CK_ADH_WITH_AES_128_SHA

#define DTLS1_CK_RSA_WITH_AES_256_SHA            TLS1_CK_RSA_WITH_AES_256_SHA
#define DTLS1_CK_DHE_DSS_WITH_AES_256_SHA TLS1_CK_DHE_DSS_WITH_AES_256_SHA
#define DTLS1_CK_DHE_RSA_WITH_AES_256_SHA TLS1_CK_DHE_RSA_WITH_AES_256_SHA
#define DTLS1_CK_ADH_WITH_AES_256_SHA            TLS1_CK_ADH_WITH_AES_256_SHA   

/* PSK cipher suites */
#ifndef SSL_NO_PSK
#define DTLS1_CK_PSK_NULL_SHA                    TLS1_CK_PSK_NULL_SHA    
#define DTLS1_CK_PSK_3DES_EDE_CBC_SHA            TLS1_CK_PSK_3DES_EDE_CBC_SHA
#define DTLS1_CK_PSK_AES_128_CBC_SHA             TLS1_CK_PSK_AES_128_CBC_SHA
#define DTLS1_CK_PSK_AES_256_CBC_SHA             TLS1_CK_PSK_AES_256_CBC_SHA
#endif

#ifndef SSL_NO_DH_PSK
#define DTLS1_CK_DHE_PSK_NULL_SHA                TLS1_CK_DHE_PSK_NULL_SHA
#define DTLS1_CK_DHE_PSK_3DES_EDE_CBC_SHA TLS1_CK_DHE_PSK_3DES_EDE_CBC_SHA
#define DTLS1_CK_DHE_PSK_AES_128_CBC_SHA   TLS1_CK_DHE_PSK_AES_128_CBC_SHA
#define DTLS1_CK_DHE_PSK_AES_256_CBC_SHA   TLS1_CK_DHE_PSK_AES_256_CBC_SHA 
#endif


/* The strings for each cipher. IDs can be got by s/TXT/CK/ */
#define DTLS1_TXT_RSA_NULL_MD5                   SSL3_TXT_RSA_NULL_MD5
#define DTLS1_TXT_RSA_NULL_SHA                  SSL3_TXT_RSA_NULL_SHA
#define DTLS1_TXT_RSA_DES_64_CBC_SHA             SSL3_TXT_RSA_DES_64_CBC_SHA
#define DTLS1_TXT_RSA_DES_192_CBC3_SHA           SSL3_TXT_RSA_DES_192_CBC3_SHA
#define DTLS1_TXT_EDH_DSS_DES_64_CBC_SHA    SSL3_TXT_EDH_DSS_DES_64_CBC_SHA
#define DTLS1_TXT_EDH_DSS_DES_192_CBC3_SHA\
                        SSL3_TXT_EDH_DSS_DES_192_CBC3_SHA
#define DTLS1_TXT_EDH_RSA_DES_64_CBC_SHA    SSL3_TXT_EDH_RSA_DES_64_CBC_SHA
#define DTLS1_TXT_EDH_RSA_DES_192_CBC3_SHA\
                                            SSL3_TXT_EDH_RSA_DES_192_CBC3_SHA
#define DTLS1_TXT_ADH_DES_64_CBC_SHA             SSL3_TXT_ADH_DES_64_CBC_SHA
#define DTLS1_TXT_ADH_DES_192_CBC_SHA            SSL3_TXT_ADH_DES_192_CBC_SHA

/* AES ciphersuites from RFC3268 */
#define DTLS1_TXT_RSA_WITH_AES_128_SHA           TLS1_TXT_RSA_WITH_AES_128_SHA
#define DTLS1_TXT_DHE_DSS_WITH_AES_128_SHA\
                                           TLS1_TXT_DHE_DSS_WITH_AES_128_SHA
#define DTLS1_TXT_DHE_RSA_WITH_AES_128_SHA\
                                            TLS1_TXT_DHE_RSA_WITH_AES_128_SHA
#define DTLS1_TXT_ADH_WITH_AES_128_SHA           TLS1_TXT_ADH_WITH_AES_128_SHA

#define DTLS1_TXT_RSA_WITH_AES_256_SHA           TLS1_TXT_RSA_WITH_AES_256_SHA
#define DTLS1_TXT_DHE_DSS_WITH_AES_256_SHA\
                                             TLS1_TXT_DHE_DSS_WITH_AES_256_SHA
#define DTLS1_TXT_DHE_RSA_WITH_AES_256_SHA\
                                             TLS1_TXT_DHE_RSA_WITH_AES_256_SHA
#define DTLS1_TXT_ADH_WITH_AES_256_SHA           TLS1_TXT_ADH_WITH_AES_256_SHA

#ifndef  SSL_NO_PSK
#define DTLS1_TXT_PSK_NULL_SHA                 TLS1_TXT_PSK_NULL_SHA
#define DTLS1_TXT_PSK_3DES_EDE_CBC_SHA            TLS1_TXT_PSK_3DES_EDE_CBC_SHA 
#define DTLS1_TXT_PSK_AES_128_CBC_SHA            TLS1_TXT_PSK_AES_128_CBC_SHA
#define DTLS1_TXT_PSK_AES_256_CBC_SHA            TLS1_TXT_PSK_AES_256_CBC_SHA
#endif

#ifndef SSL_NO_DH_PSK
#define DTLS1_TXT_DHE_PSK_NULL_SHA         TLS1_TXT_DHE_PSK_NULL_SHA
#define DTLS1_TXT_DHE_PSK_3DES_EDE_CBC_SHA\
                                             TLS1_TXT_DHE_PSK_3DES_EDE_CBC_SHA
#define DTLS1_TXT_DHE_PSK_AES_128_CBC_SHA  TLS1_TXT_DHE_PSK_AES_128_CBC_SHA
#define DTLS1_TXT_DHE_PSK_AES_256_CBC_SHA  TLS1_TXT_DHE_PSK_AES_256_CBC_SHA
#endif

/**/

/*Structure which holds the information related to the connection state of
DTLSv1 Cookies*/ 

/**
* @defgroup IPSI_DTLS1_COOKIES_S
* @ingroup dtls1Structures
* @par Prototype
* @code
* typedef struct stIpsiDTLS1Cookies
* {
*   unsigned int sndCookie;
*   unsigned char cookie[IPSI_DTLS1_COOKIE_LENGTH];
*   unsigned char rcvdCookie[IPSI_DTLS1_COOKIE_LENGTH];
*   unsigned int cookieLen;
* } IPSI_DTLS1_COOKIES_S;
* @endcode
*
* @par Description
* It is a internal structure used by DTLS.Application should
* not use it normally.
*
* @datastruct sndCookie Flag to indicate the cookie exchange.
* @datastruct cookie[DTLS1_COOKIE_LENGTH] Buffer to hold the cookie 
*             exchnage message.
* @datastruct rcvdCookie[DTLS1_COOKIE_LENGTH] Buffer to hold the received
*               cookie exchange message.
* @datastruct cookieLen Holds cookie length 
*.Max value for cookieLen is IPSI_DTLS1_COOKIE_LENGTH
*/
typedef struct stIpsiDTLS1Cookies
{
    unsigned int sndCookie;
    unsigned char cookie[IPSI_DTLS1_COOKIE_LENGTH];
    unsigned char rcvdCookie[IPSI_DTLS1_COOKIE_LENGTH];
    unsigned int cookieLen;

} IPSI_DTLS1_COOKIES_S;


/*Structure which holds the information related to the connection state of 
DTLSv1 Fragment */ 

/**
* @defgroup IPSI_DTLS1_FRAGMENT_S
* @ingroup dtls1Structures
* @par Prototype
* @code
* typedef struct stIpsiDTLS1Fragment
* {
*    unsigned char alrtFrag[IPSI_DTLS1_AL_HEADER_LENGTH];
*    unsigned int alrtFragLen;
*    unsigned char hsFrag[IPSI_DTLS1_HM_HEADER_LENGTH];
*    unsigned int hsFragLen;
* } IPSI_DTLS1_FRAGMENT_S;
* @endcode
*
* @par Description
* It is a internal structure used by DTLS.Application 
* should not use it normally.
* @datastruct alrtFrag Buffer to hold alert fragment.
* @datastruct alrtFragLen Alert fragment length.
* @datastruct hsFrag Buffer to hold handshake fragment.
* @datastruct hsFragLen Handshake fragment length.
*/
typedef struct stIpsiDTLS1Fragment
{

    /* storage for Alert/Handshake protocol data received but not
     * yet processed by ssl3_read_bytes: */
    unsigned char alrtFrag[IPSI_DTLS1_AL_HEADER_LENGTH];
#ifdef IPSI_4BYTE_STRUCT_ALIGNMENT    
    unsigned char ucPadding[2];
#endif
    unsigned int alrtFragLen;
    unsigned char hsFrag[IPSI_DTLS1_HM_HEADER_LENGTH];
    unsigned int hsFragLen;

    /* Holds the fragment offset when the handshake message is split into fragments for write operation. */
    /* This variable is introduced to handle write failure for fragmented handshake messages */
    unsigned int uiFragOffSet;

    /* Holds the updated value of ssl->iInitNum for fragmented packets, used in ipsi_dtls1_retransmit_message only */
    /* during wirte non block failure happened for fragmented packets */
    int iInitNum;

} IPSI_DTLS1_FRAGMENT_S;


/*Structure which holds the information related to the read/write seq*/

/**
* @defgroup IPSI_DTLS1_HANDSHAKERDWRSEQ_S
* @ingroup dtls1Structures
* @par Prototype
* @code
* typedef struct  stIpsiDTLS1HandshakeRdWrSeq
* {
*    unsigned short hsWRSeq;		 
*    unsigned short nxtHsWRSeq;
*    unsigned short hsRdSeq;		 
*    unsigned char lastWriteSeq[8];	
* } IPSI_DTLS1_HANDSHAKERDWRSEQ_S;
* @endcode
* @datastruct hsWRSeq Flag to indicate handshake message write seq.
* @datastruct nxtHsWRSeq Flag to indicate next handshake message 
*           sequence number.
* @datastruct hsRdSeq Flag to indicate handshake message read seq.
* @datastruct lastWriteSeq saves last sequence number for retransmissions.
* @par Description
* It is a internal structure used by DTLS.Application
* should not use it normally.
*/

typedef struct  stIpsiDTLS1HandshakeRdWrSeq
{
    /* handshake message numbers */
    unsigned short hsWRSeq;		 
    unsigned short nxtHsWRSeq;
    unsigned short hsRdSeq;		 
#ifdef IPSI_4BYTE_STRUCT_ALIGNMENT
    unsigned short usPadding;
#endif
    /* save last sequence number for retransmissions */
    unsigned char lastWriteSeq[8];	

} IPSI_DTLS1_HANDSHAKERDWRSEQ_S;

/*Structure which holds the information related to the ctx variables of 
DTLSv1 */ 

/**
* @defgroup 
* @ingroup dtls1Structures
* @par Prototype
* @code
*struct stIpsiDTLS1CtxInfo
* {
*    SEC_INT (*pfappGenerateCookie_cb) (struct stSSL *ssl, 
        unsigned char *cookie, unsigned int *cookie_len, void *pUserData);
*    SEC_INT (*pfappVerifyCookie_cb)(struct stSSL *ssl, unsigned char *cookie, 
        unsigned int cookie_len, void *PUserData);
* };
* @endcode
*
* @par Description
* It is a internal structure used by DTLS.Application should
* not use it normally.
* @datastruct pfappGenerateCookie_cb - cookie generate callback.
* @datastruct pfappVerifyCookie_cb - cookie verify callback.
*/

struct stIpsiDTLS1CtxInfo
{

    /* cookie generate callback */
    SEC_INT (*pfappGenerateCookie_cb) (SSL_S *ssl, 
        unsigned char *cookie, unsigned int *cookie_len, void *pUserData);

    /* verify cookie callback */
    SEC_INT (*pfappVerifyCookie_cb)(SSL_S *ssl, unsigned char *cookie, 
        unsigned int cookie_len, void *PUserData);


};

//typedef struct stIpsiPqueue IPSI_PQUEUE_S;

/**
* @defgroup dtls1Structures
* This section contains all the dtls Structures and Functions.
*/

/*
Structure to hold DTLSv1 bitmap operations
*/ 

/**
* @defgroup IPSI_DTLS1_BITMAP_S
* @ingroup dtls1Structures
* @par Prototype
* @code
* typedef struct stIpsiDTLSBitmap
* {
*   unsigned long map;
*   unsigned char max_seq_num[8];
* } IPSI_DTLS1_BITMAP_S;
* @endcode
*
* @par Description
* It is a internal structure used by DTLS. Application 
* should not use it normally.
*
* @datastruct map Size of bitmap in bits.
* @datastruct max_seq_num Maximum record number seen so far.

*/

typedef struct stIpsiDTLSBitmap
{
    unsigned long map;		/* track 32 packets on 32-bit systems
    				   and 64 - on 64-bit systems */
    unsigned char max_seq_num[8];	/* max record number seen so far,
    				   64-bit value in big-endian
    				   encoding */
} IPSI_DTLS1_BITMAP_S;


#ifndef SSL_NO_COMP
    typedef COMP_CTX_S IPSI_DTLS1_COMP_CTX_STRUCTURE;
#else
    typedef char IPSI_DTLS1_COMP_CTX_STRUCTURE;
#endif


/**
* @defgroup dtls1Structures
* This section contains all the dtls Structures and Functions.
*/

/*
Structure to hold DTLSv1 bitmap operations
*/ 

/**
* @defgroup IPSI_DTLS1_RETRANSMIT_STATE_S
* @ingroup dtls1Structures
* @par Prototype
* @code
* typedef struct dtls1_retransmit_state
* {
*    CRYPT_CTX *enc_write_ctx;
*    SEC_ALGID_E write_hash;
*    IPSI_DTLS1_COMP_CTX_STRUCTURE *compress;
*    SSL_SESSION_S *session;
*    unsigned short epoch;
* }IPSI_DTLS1_RETRANSMIT_STATE_S;
* @endcode
*
* @par Description
* It is a internal structure used by DTLS. Application 
* should not use it normally.
*
* @datastruct enc_write_ctx Context to maintain cryptographic state.
* @datastruct write_hash Flag to indicate write hash.
* @datastruct compress Compression method used
* @datastruct session Pointer to SSL session
* @datastruct epoch Indicates epoch value for retransmission
*/

typedef struct dtls1_retransmit_state
{
    CRYPT_CTX *enc_write_ctx;	/* cryptographic state */
    SEC_ALGID_E write_hash;			/* used for mac generation */
    IPSI_DTLS1_COMP_CTX_STRUCTURE *compress;    /* compression */
    SSL_SESSION_S *session;
    unsigned short epoch;
#ifdef IPSI_4BYTE_STRUCT_ALIGNMENT
    unsigned short usPadding;
#endif 
    SEC_UCHAR aucWriteMACSecret[MAX_DIGEST_SIZE];
    SEC_ALGID_E EncAlgid;   
}IPSI_DTLS1_RETRANSMIT_STATE_S;

/**
* @defgroup IPSI_DTLS1_HM_HDR_REC_S
* @ingroup dtls1Structures
* @par Prototype
* @code
* typedef struct stIPSIDTLS1HmHdrRec
* {
*    unsigned char type;
*    unsigned long msgLen;
*    unsigned short seq;
*    unsigned long frgOff;
*    unsigned long frgLen;
* }IPSI_DTLS1_HM_HDR_REC_S;
* @endcode
*
* @par Description
* It is a internal structure used by DTLS. Application 
* should not use it normally.
*
* @datastruct type Record Header Type
* @datastruct msgLen Message Length
* @datastruct seq Record Sequencec Number
* @datastruct frgOff Record Fragment offset
* @datastruct frgLen Record Fragment Length
*/

typedef struct stIPSIDTLS1HmHdrRec
{
    unsigned char type;
#ifdef IPSI_4BYTE_STRUCT_ALIGNMENT
    unsigned char ucPadding1;
    unsigned char ucPadding2;
    unsigned char ucPadding3;
#endif
    unsigned long msgLen;
    unsigned short seq;
#ifdef IPSI_4BYTE_STRUCT_ALIGNMENT
    unsigned short usPadding4;
#endif
    unsigned long frgOff;
    unsigned long frgLen;
}IPSI_DTLS1_HM_HDR_REC_S;


/**
* @defgroup IPSIDTLS1HMHEADER_S
* @ingroup dtls1Structures
* @par Prototype
* @code
* typedef struct stIpsiDTLS1HmHeader
* {
*    IPSI_DTLS1_HM_HDR_REC_S hdrRec;
*    unsigned int is_ccs;
*    IPSI_DTLS1_RETRANSMIT_STATE_S savedRetransState;
* } IPSIDTLS1HMHEADER_S;
* @endcode
*
* @par Description
* It is a internal structure used by DTLS. Application 
* should not use it normally.
*
* @datastruct hdrRec Record Header Data Structure
* @datastruct is_ccs Indicate whether a 
* change cipher spec message
* @datastruct savedRetransState 
* Save Retransmit State
*/
typedef struct stIpsiDTLS1HmHeader
{

    IPSI_DTLS1_HM_HDR_REC_S hdrRec;
    
    unsigned int is_ccs;
    IPSI_DTLS1_RETRANSMIT_STATE_S savedRetransState;
} IPSIDTLS1HMHEADER_S;


/*
Structure to hold DTLSv1 Change Cipher Spec states
*/ 

/**
* @defgroup IPSI_DTLS1_CCS_HEADER_S
* @ingroup dtls1Structures
* @par Prototype
* @code
* typedef struct stDTLS1CcsHeader
* {
*   unsigned char type;
*   unsigned short seq;
* }IPSI_DTLS1_CCS_HEADER_S;
* @endcode
*
* @par Description
* It is a internal structure used by DTLS. Application 
* should not use it normally.
*
* @datastruct type Type of message Handshake or Application data.
* @datastruct seq Sequence number.

*/

typedef struct stIpsiDTLS1CcsHeader
{
    unsigned char type;
#ifdef IPSI_4BYTE_STRUCT_ALIGNMENT
    unsigned char ucPadding1;
    unsigned char ucPadding2;
    unsigned char ucPadding3;
#endif
    unsigned short seq;
}IPSI_DTLS1_CCS_HEADER_S;

/*
Structure to hold DTLSv1 messages time out state
*/ 

/**
* @defgroup IPSI_DTLS1_TIMEOUT_S
* @ingroup dtls1Structures
* @par Prototype
* @code
* typedef struct stIpsiDTLS1Timeout
* {
*   unsigned int read_timeouts;
*   unsigned int write_timeouts;
*   unsigned int num_alerts;
* }IPSI_DTLS1_TIMEOUT_S;
* @endcode
*
* @par Description
* It is a internal structure used by DTLS. Application 
* should not use it normally.
*
* @datastruct read_timeouts Number of read timeouts so far.
* @datastruct write_timeouts Number of write timeouts so far.
* @datastruct num_alerts Number of alerts received so far.

*/

typedef struct stIpsiDTLS1Timeout
{
    /* Number of read timeouts so far */
    unsigned int rdTmOuts;

    /* Number of write timeouts so far */
    unsigned int wrTmOuts;

    /* Indicates when the last handshake msg sent will timeout */
    //Moved to dtls time out structure from Dtls state structure

    //struct timeval nxtTmOut;
    long nxtTmOut;

    /* Timeout duration */
    //Moved to dtls time out structure from Dtls state structure
    long tmOutDur;

    /* Number of alerts received so far */
    unsigned int numAlrts;
}IPSI_DTLS1_TIMEOUT_S;


/*Structure which holds the information related to the 
  record priority queue */ 

/**
* @defgroup IPSI_DTLS1_RECORD_PQUEUE_S
* @ingroup dtls1Structures
* @par Prototype
* @code
* typedef struct stIpsiDTLS1RecordPqueue
* {
*    unsigned short epoch;
*    struct stIpsiPqueue *q;
* } IPSI_DTLS1_RECORD_PQUEUE_S;
* @endcode
*
* @par Description
* It is a internal structure used by DTLS.Application should not
* use it normally.
* @datastruct epoch Epoch Value of the Record Message
* @datastruct q Priority Queue.
*/
typedef struct stIpsiDTLS1RecordPqueue
{
    unsigned short epoch;
#ifdef IPSI_4BYTE_STRUCT_ALIGNMENT
    unsigned short usPadding;
#endif
    struct stIpsiPqueue *q;
} IPSI_DTLS1_RECORD_PQUEUE_S;

/*Structure which holds the information related to the 
  DTLS handshake message fragment */ 

/**
* @defgroup IPSI_DTLS1_HM_FRAGMENT_S
* @ingroup dtls1Structures
* @par Prototype
* @code
* typedef struct stDTLS1HmFragment
* {
*    IPSIDTLS1HMHEADER_S msgHdr;
*    unsigned char *frag;
* } IPSI_DTLS1_HM_FRAGMENT_S;
* @endcode
*
* @par Description
* It is a internal structure used by DTLS.Application should
* not use it normally.
* @datastruct msgHdr Message Header Data struct
* @datastruct frag A individual record fragment 
*/
typedef struct stDTLS1HmFragment
{
    IPSIDTLS1HMHEADER_S msgHdr;
    unsigned char *frag;
    unsigned char *reassembly;
} IPSI_DTLS1_HM_FRAGMENT_S;

/*
Structure to hold DTLSv1 record
*/ 

/**
* @defgroup IPSI_DTLS1_RECORD_DATA_S
* @ingroup dtls1Structures
* @par Prototype
* @code
* typedef struct stDTLS1RecordData
* {
*   unsigned char *packet;
*   unsigned int   packet_length;
*   SSL3_BUFFER_S    rbuf;
*   SSL3_RECORD_S    rrec;
} DTLS1_RECORD_DATA_S;
* @endcode
*
* @par Description
* It is a internal structure used by DTLS. Application 
* should not use it normally.
*
* @datastruct packet Pointer to the packet.
* @datastruct packet_length Length of the packet.
* @datastruct rbuf Read IO goes into here.
* @datastruct rrec Each decoded record goes into here.

*/
typedef struct stIpsiDTLS1RecordData
{
    unsigned char *pkt;
    unsigned int   pktLen;
    SSL3_BUFFER_S    rbuf;
    SSL3_RECORD_S    rrec;
} IPSI_DTLS1_RECORD_DATA_S;


/* Timeout multipliers */
#define IPSI_DTLS1_TMO_READ_COUNT                      2
#define IPSI_DTLS1_TMO_WRITE_COUNT                     2

#define IPSI_DTLS1_TMO_ALERT_COUNT                     12


/*
Structure to hold DTLSv1 bitmap
*/ 

/**
* @defgroup IPSI_DTLS1_STATE_BITMAP_S
* @ingroup dtls1Structures
* @par Prototype
* @code
* typedef struct stDTLS1Bitmaps
* {
*    IPSI_DTLS1_BITMAP_S bmp;	
*    IPSI_DTLS1_BITMAP_S nxtBmp;
* } IPSI_DTLS1_STATE_BITMAP_S;
* @endcode
*
* @par Description
* It is a internal structure used by DTLS. Application 
* should not use it normally.
*
* @datastruct bmp Bitmap to hold records of all received Records.
* @datastruct nxtBmp Bitmap for Renegotiation to hold records
* of all received Records.
*/
typedef struct stDTLS1Bitmaps
{
    /* records being received in the current epoch */
    IPSI_DTLS1_BITMAP_S bmp;	

    /* renegotiation starts a new set of sequence numbers */
    IPSI_DTLS1_BITMAP_S nxtBmp;

} IPSI_DTLS1_STATE_BITMAP_S;


/*Structure which holds the information related to the connection state of
DTLSv1 Epoch */ 

/**
* @defgroup IPSI_DTLS1_EPOCH_S
* @ingroup dtls1Structures
* @par Prototype
* @code
* typedef struct stIpsiDTLS1Epoch
* {
*    unsigned short r_epoch;
*    unsigned short w_epoch;
* } IPSI_DTLS1_EPOCH_S;
* @endcode
*
* @par Description
* It is a internal structure used by DTLS.Application should
* not use it normally.
* @datastruct r_epoch Current data and handshake read epoch.Initially undefined
*        Starts will zero once initial handshake is completed.
* @datastruct w_epoch Current data and handshake write epoch. Initially 
*       undefined. Starts will zero once initial handshake is completed.
*/
typedef struct stDTLS1Epoch
{
    /* 
     * The current data and handshake epoch.  This is initially
     * undefined, and starts at zero once the initial handshake is
     * completed 
     */
    unsigned short rEpoch;
    unsigned short wEpoch;
}IPSI_DTLS1_STATE_EPOCH_S;

/*Structure which holds the information related to the connection state of
DTLSv1 Epoch and DTLS handshake read/write sequence */ 

/**
* @defgroup IPSI_DTLS1_STATE_EPOCH_AND_SEQ_S
* @ingroup dtls1Structures
* @par Prototype
* @code
* typedef struct stDTLS1EpochAndSeq
* {
*    IPSI_DTLS1_STATE_EPOCH_S stD1Epochs;
*    IPSI_DTLS1_HANDSHAKERDWRSEQ_S stD1HsRdWrSeq;
* } IPSI_DTLS1_STATE_EPOCH_AND_SEQ_S;
* @endcode
*
* @par Description
* It is a internal structure used by DTLS.Application should 
* not use it normally.
* @datastruct stD1Epochs read and write epoch structure
* @datastruct stD1HsRdWrSeq  Handshake read/write
* sequence values.
*/
typedef struct stDTLS1EpochAndSeq
{
    IPSI_DTLS1_STATE_EPOCH_S stD1Epochs;
    IPSI_DTLS1_HANDSHAKERDWRSEQ_S stD1HsRdWrSeq;
}
IPSI_DTLS1_STATE_EPOCH_AND_SEQ_S;


/*Structure which holds the information related to the 
  DTLS read and write message header */ 

/**
* @defgroup IPSI_DTLS1_STATE_MSG_HDR_S
* @ingroup dtls1Structures
* @par Prototype
* @code
* typedef struct stDTLS1MsgHdr
* {
*    IPSIDTLS1HMHEADER_S wMsgHdr;
*    IPSIDTLS1HMHEADER_S rMsgHdr;
* }IPSI_DTLS1_STATE_MSG_HDR_S;
* @endcode
*
* @par Description
* It is a internal structure used by DTLS.Application
* should not use it normally.
* @datastruct wMsgHdr Write Message header
* @datastruct rMsgHdr Read Message Header
*/
typedef struct stDTLS1MsgHdr
{
    IPSIDTLS1HMHEADER_S wMsgHdr;
    IPSIDTLS1HMHEADER_S rMsgHdr;

}IPSI_DTLS1_STATE_MSG_HDR_S;


/*Structure which holds the information related to the 
  all DTLS queues */ 

/**
* @defgroup IPSI_DTLS_STATE_QUEUES_S
* @ingroup dtls1Structures
* @par Prototype
* @code
* typedef struct stDTLS1Queues
* {
*    IPSI_DTLS1_RECORD_PQUEUE_S unProcRcds;
*    IPSI_DTLS1_RECORD_PQUEUE_S procRcds;
*    struct stIpsiPqueue *bufMsg;
*    struct stIpsiPqueue *sntMsg;  
*    IPSI_DTLS1_RECORD_PQUEUE_S bufAppData;
* }IPSI_DTLS_STATE_QUEUES_S;
* @endcode
*
* @par Description
* It is a internal structure used by DTLS.Application should
* not use it normally.
* @datastruct unProcRcds Queue for UnProcessed Records
* @datastruct procRcds Queue for Processed Records
* @datastruct bufMsg Queue for receive buffered Messages.
* @datastruct sntMsg Queue for send messages
* @datastruct bufAppData Queue for Buffering App Data.
*/
typedef struct stDTLS1Queues
{
    /* Received handshake records (processed and unprocessed) */
    IPSI_DTLS1_RECORD_PQUEUE_S unProcRcds;
    IPSI_DTLS1_RECORD_PQUEUE_S procRcds;

    /* Buffered handshake messages */
    struct stIpsiPqueue *bufMsg;

    /* Buffered (sent) handshake records */
    struct stIpsiPqueue *sntMsg;  

    /* Buffered application records.
     * Only for records between CCS and Finished
     * to prevent either protocol violation or
     * unnecessary message loss.
     */
    IPSI_DTLS1_RECORD_PQUEUE_S bufAppData;

    SEC_VOID *stRetransIter;

}IPSI_DTLS_STATE_QUEUES_S;


/*Structure which holds the information related to the 
  all fragments and messages */ 

/**
* @defgroup IPSI_DTLS1_STATE_FRAG_MSG_S
* @ingroup dtls1Structures
* @par Prototype
* @code
* typedef struct stFragAndMsgs
* {	
*    IPSI_DTLS_STATE_QUEUES_S stD1Ques;
*    IPSI_DTLS1_STATE_MSG_HDR_S stD1MsgHdrs;
*    IPSI_DTLS1_FRAGMENT_S stD1Frags;
* } IPSI_DTLS1_STATE_FRAG_MSG_S;
* @endcode
*
* @par Description
* It is a internal structure used by DTLS.Application should
* not use it normally.
* @datastruct stD1Ques Structure for all Priority Queues
* @datastruct stD1MsgHdrs Structure for all Message Headers
* @datastruct stD1Frags Structure for all fragments
*/

typedef struct stFragAndMsgs
{	
    IPSI_DTLS_STATE_QUEUES_S stD1Ques;
    IPSI_DTLS1_STATE_MSG_HDR_S stD1MsgHdrs;

    IPSI_DTLS1_FRAGMENT_S stD1Frags;

} IPSI_DTLS1_STATE_FRAG_MSG_S;

/*Structure which holds the information related to the 
  DTLS state variables */ 

/**
* @defgroup IPSI_DTLS1_STATE_VAR_S
* @ingroup dtls1Structures
* @par Prototype
* @code
* typedef struct stStateVariable
* {
*    IPSI_DTLS1_TIMEOUT_S timeout;	
*    unsigned int uiRetrans;
*    unsigned int ccs_ok;
*    unsigned int max_num_retries;
*    unsigned int uiRetransLastFlight;
*    unsigned int received_client_cert_msg;
* }IPSI_DTLS1_STATE_VAR_S;
* @endcode
*
* @par Description
* It is a internal structure used by DTLS.Application 
* should not use it normally.
* @datastruct timeout structure for timeout variables
* @datastruct uiRetrans whether retransmitting
* @datastruct ccs_ok change cipher spec ok
* @datastruct max_num_retries max number of 
* @datastruct uiRetransLastFlight flag to track retransmit failure of last flight in SSL_read()
* @datastruct received_client_cert_msg flag to track client authentication
* retries in case of retransmission
*/

typedef struct stStateVariable
{
    IPSI_DTLS1_TIMEOUT_S timeout;	

    unsigned int uiRetrans;

    unsigned int ccs_ok;

    unsigned int max_num_retries;

    unsigned int uiRetransLastFlight;

    unsigned int received_client_cert_msg;

}IPSI_DTLS1_STATE_VAR_S;


/*Structure which holds the information related to the 
  DTLS state */ 

/**
* @defgroup IPSI_DTLS1_STATE_S
* @ingroup dtls1Structures
* @par Prototype
* @code
* typedef struct stIpsiDTLS1State
* {	
*    IPSI_DTLS1_COOKIES_S stD1Cookies;
*    IPSI_DTLS1_STATE_BITMAP_S stD1Bitmaps;
*    IPSI_DTLS1_STATE_EPOCH_AND_SEQ_S  stEpochSeq;
*    IPSI_DTLS1_STATE_FRAG_MSG_S stFragMsgs;
*    IPSI_DTLS1_STATE_VAR_S stD1Vars;
* } IPSI_DTLS1_STATE_S;
* @endcode
*
* @par Description
* It is a internal structure used by DTLS.Application 
* should not use it normally.
* @datastruct stD1Cookies Structure for Holding cookies
* @datastruct stD1Bitmaps Structure for Holding Bitmaps
* @datastruct stEpochSeq Structure for Holding Epoch and 
* sequence numbers
* @datastruct stFragMsgs Structure related to fragments and 
* messages.
* @datastruct stD1Vars Other DTLS1 variables
*/

typedef struct stIpsiDTLS1State
{	
    IPSI_DTLS1_COOKIES_S stD1Cookies;

    IPSI_DTLS1_STATE_BITMAP_S stD1Bitmaps;

    IPSI_DTLS1_STATE_EPOCH_AND_SEQ_S  stEpochSeq;

    IPSI_DTLS1_STATE_FRAG_MSG_S stFragMsgs;

    IPSI_DTLS1_STATE_VAR_S stD1Vars;
} IPSI_DTLS1_STATE_S;


/* The maximum record overhead for DTLS */
#define IPSI_DTLS1_MAX_RECORD_OVERHEAD 65





#ifdef  __cplusplus
}
#endif

#endif

