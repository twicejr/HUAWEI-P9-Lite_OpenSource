/*
                                                                              
                Copyright 2003, Huawei Technologies Co. Ltd.                  
                            ALL RIGHTS RESERVED                               
                                                                              
------------------------------------------------------------------------------
                                                                              
                              tls_extension.h                                 
                                                                              
  Project Code: SeCert                                                        
   Module Name: TLS Extension                                                 
  Date Created: 2006-01-09                                                    
        Author: Mayur Navadia                                                 
   @brief: Contains structures and functions Exported to the user              
               required for TLS Extensions      							  
------------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
  --------------------------------------------------------------------------  
  YYYY-MM-DD                                                                  
                                                                              
*/

// #ifndef SSL_NO_TLSEXT Commented by Satish - 2010-04-10

#include "ipsi_ssl_build_conf.h"

#ifndef __IPSI_TLS_EXTENS_H__
#define __IPSI_TLS_EXTENS_H__

#include "ipsi_types.h"
#include "sec_sys.h"
#include "sec_list.h"
#include "asn-types.h"
#include "x509_basictypes.h"
#include "x509.h"
#include "ssl.h"


#ifdef	 __cplusplus
extern	"C"{
#endif

#ifndef SSL_NO_TLSEXT

typedef SEC_AsnOcts_S           TLS_SERVERNAME_S;
typedef SEC_AsnOcts_S           TLS_CAIDENTIFIER_S;
typedef SEC_AsnOcts_S           TLS_RESPONDERID_S;
typedef SEC_AsnOcts_S           TLS_OCSPEXTN_S;
typedef SEC_AsnOcts_S           TLS_OCSPRESP_S;


/*Below are the extension defines, which are used to enable the each type of TLS Extension*/
/*It sets the bit to enable the server_name extension flag*/
#define TLS_SERVER_NAME_EXTN        0x0001
/*It sets the bit to enable the max_fragment_len extension flag*/
#define TLS_MAX_FRAG_LEN_EXTN        0x0002
/*It sets the bit to enable the client_cert_url extension flag*/
#define TLS_CLIENT_CERT_URL_EXTN    0x0004
/*It sets the bit to enable the trusted_ca extension flag*/
#define TLS_TRUSTED_CA_EXTN         0x0008
/*It sets the bit to enable the truncated_hmac extension flag*/
#define TLS_TRUNCATED_HMAC_EXTN     0x0010
/*It sets the bit to enable the status_request extension flag*/
#define TLS_STATUS_REQUEST_EXTN     0x0020

/* This is the TLS Extensions mask used to check for presence of extensions.
	Defect A75D00945 Fix */
#define TLS_EXTNS_MASK	(0x3F)

/** @defgroup tls1_extns
* This section describes the Enums and Functions in tls1_extns.
*/

/** @defgroup tls1_extnsEnums
* @ingroup tls1_extns
* This section contains the Enums of tls1_extns.
*/

/** @defgroup tls1_extnsFunctions
* @ingroup tls1_extns
* This sections contains the Functions in tls_extns.
*/


/*
Enum which defines the Extension data for "max_fragment_length" extension type
Extension data for this extensions contains One of the
{2^9(1), 2^10(2), 2^11(3), 2^12(4)}
*/

/**
* @defgroup TLS_EXTN_FRAG_LEN_E
* @ingroup tls1_extnsEnums
*
* @par Prototype
* @code
* typedef enum enTLSFragmentLen
* {
*  TLS_FRAG_LEN_2P14=0,
*  TLS_FRAG_LEN_2P9 =1,
*  TLS_FRAG_LEN_2P10,
*  TLS_FRAG_LEN_2P11,
*  TLS_FRAG_LEN_2P12,
*  TLS_FRAG_LEN_UNKNOWN = 255
* }TLS_EXTN_FRAG_LEN_E;
* @endcode
* @par Description 
* This enum defines the Extension data for "max_fragment_length" extension type. Extension data for this extensions
* contains one of the following:\n
* {2^9(1), 2^10(2), 2^11(3), 2^12(4),2^14(0)}
*
* @datastruct TLS_FRAG_LEN_2P14 Fragment Length Value 2^14(0).
* @datastruct TLS_FRAG_LEN_2P9 Fragment Length Value 2^9(1).
* @datastruct TLS_FRAG_LEN_2P10 Fragment Length Value 2^10(2).
* @datastruct TLS_FRAG_LEN_2P11 Fragment Length Value 2^11(3).
* @datastruct TLS_FRAG_LEN_2P12 Fragment Length Value 2^12(4).
* @datastruct TLS_FRAG_LEN_UNKNOWN Unknown Fragment Length Value.
*/
typedef enum enTLSFragmentLen
{
	TLS_FRAG_LEN_2P14=0,
     /*Fragment Length Value 2^9(1)*/
    TLS_FRAG_LEN_2P9 =1,
    /*Fragment Length Value 2^10(2)*/
    TLS_FRAG_LEN_2P10,
    /*Fragment Length Value 2^11(3)*/
    TLS_FRAG_LEN_2P11,
    /*Fragment Length Value 2^12(4)*/
    TLS_FRAG_LEN_2P12,
    /*Unknown Fragment Length Value*/
    TLS_FRAG_LEN_UNKNOWN = 255
}TLS_EXTN_FRAG_LEN_E;

/*
Enum which defines the ServerName Type. 
Currently RFC support only one name type hostname(0), but in the future there may
be more than one type. 
*/

/**
* @defgroup TLS_EXTN_SERVERNAME_TYPE_E
* @ingroup tls1_extnsEnums
* @par Prototype
* @code
* typedef enum enTLSServerNameType
* {
*  TLS_HOST_NAME = 0
* }TLS_EXTN_SERVERNAME_TYPE_E;
* @endcode
*
* @par Description 
* This enum defines the ServerName Type. Currently RFC support only one name type hostname(0), but in the future there
* may be more than one type.
*
* @datastruct TLS_HOST_NAME ServerName Type host_name(0).
*/
typedef enum enTLSServerNameType
{
    /*ServerName Type host_name(0)*/
    TLS_HOST_NAME = 0
}TLS_EXTN_SERVERNAME_TYPE_E;


/*
Client asks server for server's Certificate status. Client sends the request to get
the Server's Certificate status in the particular status type. Right now only 
OCSP Status type is supported.
*/

/**
* @defgroup TLS_EXTN_STATUS_TYPE_E
* @ingroup tls1_extnsEnums
* @par Prototype
* @code
* typedef enum enTLSStatusType
* {
*  TLS_STATUS_OCSP = 1
* }TLS_EXTN_STATUS_TYPE_E;
* @endcode
*
* @par Description  
* Client asks server for server's Certificate status. Client sends the request to get the Server's Certificate status in
* the particular status type. Right now only OCSP Status type is supported.
*
* @datastruct TLS_STATUS_OCSP States type ocsp(1).
*/
typedef enum enTLSStatusType
{
    /* States type ocsp(1)*/
    TLS_STATUS_OCSP = 1
}TLS_EXTN_STATUS_TYPE_E;

/*
    Enum for CA root key Identifiers types. According the Identifier Types
    Identifier Data contains different types of data.
    Identifier types can be one of the           
    pre_agreed(0),key_sha1_hash(1),x509_name(2),cert_sha1_hash(3)
*/

/**
* @defgroup TLS_EXTN_CA_IDENTIFIER_E
* @ingroup tls1_extnsEnums
* @par Prototype
* @code
* typedef enum enTLSCAIdentifier
* {
*  TLS_PRE_AGREED = 0,
*  TLS_KEY_SHA1_HASH,
*  TLS_X509_DN,
*  TLS_CERT_SHA1_HASH
* }TLS_EXTN_CA_IDENTIFIER_E;
* @endcode
*
* @par Description  
* Enum for CA root key Identifiers types. According the Identifier Types, Identifier Data contains different types of
* data. Identifier types can be one of the pre_agreed(0),key_sha1_hash(1),x509_name(2),cert_sha1_hash(3).
*
* @datastruct TLS_PRE_AGREED No CA root key identity supplied. Server and client have pre-agreed trusted CAs.
* @datastruct TLS_KEY_SHA1_HASH Identifier data contains the SHA-1 hash of the CA root key.
* @datastruct TLS_X509_DN Identifier data contains the DER-Encoded X509 DN of the CA.
* @datastruct TLS_CERT_SHA1_HASH Identifier data contains the SHA-1 hash of the Der-Encoded certificate.
* containing the CA root key.
*/
typedef enum enTLSCAIdentifier
{
    /*pre_agreed(0) : no CA root key identity supplied. Server and client 
    have pre-agreed trusted CAs*/
    TLS_PRE_AGREED = 0,
    /*key_sha1_hash(1) : identifier data contains the SHA-1 hash of the CA root key*/
    TLS_KEY_SHA1_HASH,
    /*x509_name(2) : identifier data contains the DER-Encoded X509 DN of the CA*/
    TLS_X509_DN,
    /*cert_sha1_hash(3) : identifier data contains the SHA-1 hash of the Der-Encoded
                           certificate containing the CA root key*/
    TLS_CERT_SHA1_HASH
}TLS_EXTN_CA_IDENTIFIER_E;


#ifndef IPSI_SSL_NO_SSL

/*
    Func Name : SSL_ctxExNew
*/
/**
* @defgroup SSL_ctxExNew
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* SSL_CTX_S * SSL_ctxExNew(SSL_METHOD_S *meth);
* @endcode
* 
* @par Purpose
* This is used to create new SSL_CTX_S when application supports extension.
* 
* @par Description
* SSL_ctxExNew function is called by the application when it supports the extension. This function is doing same as
* SSL_ctxNew function, further it allocates the memory for TLS Extensions structure and initializes the Extension
* data with default values. 
*
* @param[in] *meth SSL Methods. Only TLSv1, TLSv11 & TLSv1.2 version supports the extensions. [N/A]
* 
* @retval SSL_CTX_S* SSL_CTX_S pointer, with default value of extensions. [Pointer to SSL_CTX_S|N/A]
* @retval SSL_CTX_S* If SSL is not initialized or method is not of TLSv1, TLSv11 or TLSv12 version. [NULL|N/A]
* 
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n
* N/A
*
* @par Related Topics
* SSL_ctxFree,\n
* SSL_ctxNew,\n
* SSL_new,\n
* TLSv1_method,\n
* TLSv1_serverMethod,\n
* TLSv1_clientMethod,\n
* TLSv11_method,\n
* TLSv11_serverMethod,\n
* TLSv11_clientMethod,\n
* SSL_method,\n
* SSL_serverMethod,\n
* SSL_clientMethod,\n
* TLSv12_method,\n
* TLSv12_serverMethod,\n
* TLSv12_clientMethod
*/

SSLLINKDLL SSL_CTX_S * SSL_ctxExNew(SSL_METHOD_S *meth);

/*
    Func Name : SSL_ctxEnableExtns
*/

/**
* @defgroup SSL_ctxEnableExtns
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxEnableExtns(SSL_CTX_S* pstCTX, const SEC_UINT32 uiExtension);
* @endcode
* 
* @par Purpose
* This is used to enable Extension.
* 
* @par Description
* SSL_ctxEnableExtns function enables the extensions at SSL_CTX_S level, which are to be supported by clients/server.
* Following are the extensions supported by the SDK.\n
* TLS_SERVER_NAME_EXTN\n
* TLS_MAX_FRAG_LENEXTN\n
* TLS_CLIENT_CERT_URL_EXTN\n
* TLS_TRUSTED_CA_EXTN\n
* TLS_TRUNCATED_HMAC_EXTN\n
* TLS_STATUS_REQUEST_EXTN\n
* If the user wants to use more than one extension at a time user can pass the extension value using OR operator, that is,
* if user wants servername and trusted ca extension, user can pass the value TLS_SERVER_NAME_EXTN | TLS_TRUSTED_CA_EXTN.\n
* It sets this value at the SSL_CTX_S level.\n
* 1. At the client side : When ever new SSL_S object is created for that application this extension value is copied in
*    to the SSL_S level structure. If user wants to update the default extension level value for some SSL_S objects user
*    can do it by calling SSL_enableExtns function.\n
* 2. At server side : This value is used to indicate the extensions supported by the server. When the extended client
*    hello is received a subset of these extensions can be negotiated.
*
* @param[in] uiExtension Extensions to be enabled. [N/A]
* @param[in] pstCTX SSL_CTX_S structure in which Extension value is set. [N/A]
* 
* @retval SEC_INT Extensions are successfully updated at SSL_CTX_S structure. [TLS_SUCCESS|N/A]
* @retval SEC_INT Input extensions value not set at SSL_CTX_S structure. [SEC_FALSE|N/A]
* 
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n 
* 1. If user has already set the mandatory extensions, user must have to enable all the mandatory extensions.\n\n
* 2. If user does not want to enable all mandatory extensions user has to first disable that mandatory extensions.
*
* @par Related Topics
* SSL_ctxGetExtns,\n
* SSL_ctxSetMandatoryExtn,\n
* SSL_ctxGetMandatoryExtn,\n
* SSL_enableExtns,\n
* SSL_getExtns,\n
* SSL_setMandatoryExtn,\n
* SSL_getMandatoryExtn.
*/

SSLLINKDLL SEC_INT SSL_ctxEnableExtns(SSL_CTX_S* pstCTX, 
                             const SEC_UINT32 uiExtension);

/*
    Func Name : SSL_ctxGetExtns
*/

/**
* @defgroup SSL_ctxGetExtns
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* SEC_UINT32 SSL_ctxGetExtns(const SSL_CTX_S* pstCTX);
* @endcode
* 
* @par Purpose
* This is used to get TLS Extensions set by the user using SSL_ctxEnableExtns.
* 
* @par Description
* SSL_ctxGetExtns function returns the TLS Extensions set by the user using SSL_ctxEnableExtns.
* 
* @param[in] pstCTX Pointer to SSL_CTX_S. [N/A]
* 
* @retval SEC_UINT32 It returns TLS Extensions value. [TLS Extensions value|N/A]
* @retval SEC_UINT32 If no extension is enabled it returns SEC_NULL. [SEC_NULL|N/A]
* 
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n
* It also returns 0 in case of failure.
*
* @par Related Topics
* SSL_ctxEnableExtns,\n
* SSL_ctxSetMandatoryExtn,\n
* SSL_ctxGetMandatoryExtn,\n
* SSL_enableExtns,\n
* SSL_getExtns,\n
* SSL_setMandatoryExtn,\n
* SSL_getMandatoryExtn.
*/

SSLLINKDLL SEC_UINT32 SSL_ctxGetExtns(const SSL_CTX_S* pstCTX);


/*
    Func Name : SSL_ctxSetMandatoryExtn
*/

/**
* @defgroup SSL_ctxSetMandatoryExtn
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxSetMandatoryExtn(SSL_CTX_S* pstCTX, const SEC_UINT32 uiExtensionMode);
* @endcode
* 
* @par Purpose
* This is used to get mandatory extensions.
* 
* @par Description
* Client user sets the extension in the SSL_CTX_S Structure using SSL_ctxEnableExtns function for which negotiation has
* to be done with server. There may be the case that Server does not agree to support some of the requested extensions.
* Certain clients may not be able to work without some extensions. These mandatory extensions can be set using this
* function. If any mandatory extension is not negotiated by the server during handshake client abort the handshake
* process.\n
* The value for the mandatory extension is same as for the extension types.\n
* TLS_SERVER_NAME_EXTN\n
* TLS_MAX_FRAG_LENEXTN\n
* TLS_CLIENT_CERT_URL_EXTN\n
* TLS_TRUSTED_CA_EXTN\n
* TLS_TRUNCATED_HMAC_EXTN\n
* TLS_STATUS_REQUEST_EXTN\n
* If more than one extension is mandatory user provides the value by OR operator. It sets this value at the SSL_CTX_S
* level. When ever new SSL_S object is created for that user this mandatory
* extension value is copied into the SSL_S structure. If user wants to update the default mandatory extension value at
* the SSL_S level user can do it by calling SSL_setMandatoryExtn() function.
*
* @param[in] pstCTX Mandatory Extension value is updated in this SSL_CTX_S Structure. [N/A] 
* @param[in] uiExtensionMode Mandatory Extension value. If more than one extension is mandatory it is the OR. [N/A]
* 
* @retval SEC_INT Mandatory Extension value is successfully updated in SSL_CTX_S Structure. [TLS_SUCCESS|N/A]
* @retval SEC_INT If mandatory Extension contains invalid value. [SEC_NULL|N/A]
* 
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n
* If user tries to set the mandatory extension for extension which is not enable this function returns 0. This function
* is applicable at the client side only. On Server side this function does not have any effect.
* 
* @par Related Topics
* SSL_ctxEnableExtns,\n
* SSL_ctxGetExtns,\n
* SSL_ctxGetMandatoryExtn,\n
* SSL_enableExtns,\n
* SSL_getExtns,\n
* SSL_setMandatoryExtn,\n
* SSL_getMandatoryExtn.
*/

SSLLINKDLL SEC_INT SSL_ctxSetMandatoryExtn(SSL_CTX_S* pstCTX,
                              const SEC_UINT32 uiExtensionMode);


/*
    Func Name : SSL_ctxGetMandatoryExtn
*/

/**
* @defgroup SSL_ctxGetMandatoryExtn
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* SEC_UINT32 SSL_ctxGetMandatoryExtn(const SSL_CTX_S* pstCTX);
* @endcode
* 
* @par Purpose
* This is used to get Mandatory extensions.
* 
* @par Description
* SSL_ctxGetMandatoryExtn function returns the TLS Mandatory Extensions set by the user using SSL_ctxSetMandatoryExtn.
* 
* @param[in] pstCTX Pointer to SSL_CTX_S. [N/A]
* 
* @retval SEC_UINT32 Mandatory Extensions value is returned. [Mandatory Extension Value|N/A]
* @retval SEC_UINT32 If no Mandatory Extensions is enabled, it returns 0. [0|N/A]
* 
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n
* It also returns 0 if input is invalid.
*
* @par Related Topics
* SSL_ctxEnableExtns,\n
* SSL_ctxGetExtns,\n
* SSL_ctxSetMandatoryExtn,\n
* SSL_enableExtns,\n
* SSL_getExtns,\n
* SSL_setMandatoryExtn,\n
* SSL_getMandatoryExtn.
*/

SSLLINKDLL SEC_UINT32 SSL_ctxGetMandatoryExtn(const SSL_CTX_S* pstCTX);

/*
    Func Name : SSL_enableExtns                                             
*/

/**
* @defgroup SSL_enableExtns
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* SEC_INT SSL_enableExtns(SSL_S* pstSSL,
* const SEC_UINT32 uiExtension);
* @endcode
* 
* @par Purpose
* This is used to enable the extensions passed.
* 
* @par Description
* SSL_enableExtns function sets the Extensions which are supported by client/server.
* Following are the extensions supported by the SDK:\n
* TLS_SERVER_NAME_EXTN\n
* TLS_MAX_FRAG_LENEXTN\n
* TLS_CLIENT_CERT_URL_EXTN\n
* TLS_TRUSTED_CA_EXTN\n
* TLS_TRUNCATED_HMAC_EXTN\n
* TLS_STATUS_REQUEST_EXTN\n
* If the user wants to use more than one extension at time user can pass the extension value using OR, that is, if
* user wants servername and trusted ca extension he can pass the value TLS_SERVER_NAME_EXTN | TLS_TRUSTED_CA_EXTN.\n
* Default value for this extensions are the same value as the SSL_CTX_S structure. If user wants to modify the default
* extension value, user call this function.\n
* 1. At the client side this extension value is used to negotiate the extension with server.\n
* 2. At the server side this extension value is used to validate the extensions of the extended client hello message.  
* 
* @param[in] uiExtension Extension value. If more than one extension is there, it is the OR. [N/A]
* @param[in] pstSSL SSL_S Structure in which the extensions are updated. [N/A]
* 
* @retval SEC_INT Extensions are successfully updated at SSL_S structure. [TLS_SUCCESS|N/A]
* @retval SEC_INT If extensions contains the invalid value. [SEC_NULL|N/A]
* 
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n
* 1. If user has already set the mandatory extensions, user must have to enable all the mandatory extensions.\n\n
* 2. If user does not want to enable all mandatory extensions user has to first disable that mandatory extensions.
* 
* @par Related Topics
* SSL_ctxEnableExtns,\n
* SSL_ctxGetExtns,\n
* SSL_ctxSetMandatoryExtn,\n
* SSL_ctxGetMandatoryExtn,\n
* SSL_getExtns,\n
* SSL_setMandatoryExtn,\n
* SSL_getMandatoryExtn.
*/

SSLLINKDLL SEC_INT SSL_enableExtns(SSL_S* pstSSL,
                             const SEC_UINT32 uiExtension);


/*
    Func Name : SSL_getExtns
*/

/**
* @defgroup SSL_getExtns
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* SEC_UINT32 SSL_getExtns(const SSL_S* pstSSL);
* @endcode
* 
* @par Purpose
* This is used to get the Extensions set.
* 
* @par Description
* SSL_getExtns function returns the TLS Extensions set by the user using SSL_enableExtns.
* 
* @param[in] pstSSL Pointer to SSL structure. [N/A]
* 
* @retval SEC_UINT32 TLS Extension value is returned. [TLS Extension value|N/A]
* @retval SEC_UINT32 If no extension is enabled, it returns 0. [0|N/A]
* 
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n
* It also returns 0 if input is invalid.
* 
* @par Related Topics
* SSL_ctxEnableExtns,\n
* SSL_ctxGetExtns,\n
* SSL_ctxSetMandatoryExtn,\n
* SSL_ctxGetMandatoryExtn,\n
* SSL_enableExtns,\n
* SSL_setMandatoryExtn,\n
* SSL_getMandatoryExtn.
*/
SSLLINKDLL SEC_UINT32 SSL_getExtns(const SSL_S* pstSSL); 

/*
    Func Name:  SSL_setMandatoryExtn
*/

/**
* @defgroup SSL_setMandatoryExtn
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* SEC_INT SSL_setMandatoryExtn(SSL_S* pstSSL, const SEC_UINT32 uiExtensionMode);
* @endcode
* 
* @par Purpose
* This is used to set mandatory extensions.
* 
* @par Description
* Client user sets the extension in the SSL_S structure using SSL_enableExtns function for which negotiation has to be
* done with server. There may be a case that Server does not agree to negotiate for some extensions which are mandatory
* for user. Without this mandatory extensions user may not be able to process further.\n
* Value of the mandatory extensions are set by this function. The value for the mandatory extension is same as for the
* extension types.\n
* TLS_SERVER_NAME_EXTN\n
* TLS_MAX_FRAG_LENEXTN\n
* TLS_CLIENT_CERT_URL_EXTN\n
* TLS_TRUSTED_CA_EXTN\n
* TLS_TRUNCATED_HMAC_EXTN\n
* TLS_STATUS_REQUEST_EXTN\n
* If more than one extension is mandatory, user provides the value by OR.\n
* Default value for mandatory extensions are the same value as the SSL_CTX_S structure. If user wants to modify the
* default mandatory extension value, user calls this function.
* 
* @param[in] uiExtensionMode Mandatory Extension value. If more than one extension is mandatory there, it is the OR. [N/A]
* @param[in] pstSSL Mandatory Extension value is updated in the SSL_S Structure. [N/A]
* 
* @retval SEC_INT Mandatory Extension value is successfully updated in SSL_S Structure. [TLS_SUCCESS|N/A]
* @retval SEC_INT If mandatory Extension contains invalid value. [SEC_NULL|N/A]
* 
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n
* If user tries to set the mandatory extension for extension which is not enabled, this function returns 0. This function
* is applicable at the client side only. On server side this function does not have any effect.
* 
* @par Related Topics
* SSL_ctxEnableExtns,\n
* SSL_ctxGetExtns,\n
* SSL_ctxSetMandatoryExtn,\n
* SSL_ctxGetMandatoryExtn,\n
* SSL_enableExtns,\n
* SSL_getMandatoryExtn.
*/

SSLLINKDLL SEC_INT SSL_setMandatoryExtn(SSL_S* pstSSL,
                             const SEC_UINT32 uiExtensionMode);

/*
    Func Name : SSL_getMandatoryExtn
*/

/**
* @defgroup SSL_getMandatoryExtn
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* SEC_UINT32 SSL_getMandatoryExtn(const SSL_S* pstSSL);
* @endcode
* 
* @par Purpose
* This is used to get mandatory extensions.
* 
* @par Description
* SSL_getMandatoryExtn function returns the TLS Mandatory Extensions set by the user using SSL_setMandatoryExtn.
* 
* @param[in] pstSSL Pointer to SSL_S structure. [N/A]
* 
* @retval SEC_UINT32 Mandatory Extension value is returned. [Mandatory Extension value|N/A]
* @retval SEC_UINT32 If no Mandatory Extension is enabled or invalid input parameters, it returns SEC_NULL. [SEC_NULL|N/A]
* 
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n
* It also returns 0 if input is invalid.
* 
* @par Related Topics
* SSL_ctxEnableExtns,\n
* SSL_ctxGetExtns,\n
* SSL_ctxSetMandatoryExtn,\n
* SSL_ctxGetMandatoryExtn,\n
* SSL_enableExtns,\n
* SSL_setMandatoryExtn.
*/

SSLLINKDLL SEC_UINT32 SSL_getMandatoryExtn(const SSL_S* pstSSL);
  
/*
    Func Name:SSL_ctxSetFragmentLen
*/

/**
* @defgroup SSL_ctxSetFragmentLen
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxSetFragmentLen(SSL_CTX_S* pstCTX, const TLS_EXTN_FRAG_LEN_E enFragLen);
* @endcode
* 
* @par Purpose
* This is used to set max fragment length at client side.
* 
* @par Description
* SSL_ctxSetFragmentLen function is used to set the maximum fragmentation length at the client side. This new
* fragmentation length is used to negotiate the fragmentation length value if the max_fragment_length extension is
* enabled. If this extension is successfully negotiated, client/server immediately use this new value in the record
* layer for fragmenting the message.\n
* It sets this value at the SSL_CTX_S level. When ever new SSL_S object is created for that user, this fragmentation
* value is copied into the SSL_S structure.
* 
* @param[in] enFragLen Enum for the new Maximum Fragment Length that can be used. The value for it can be one of the
* following:\n
* TLS_FRAG_LEN_2P9,\n
* TLS_FRAG_LEN_2P10,\n
* FRAG_LEN_2P11,\n
* TLS_FRAG_LEN_2P12. [N/A]
* @param[in] pstCTX New Fragmentation Length is updated to the SSL_CTX_S Structure. [N/A]
* 
* @retval SEC_INT New value is successfully updated in the SSL_CTX_S Structure. [TLS_SUCCESS|N/A]
* @retval SEC_INT If input fragmentation length value is not valid or\n Input parameters are invalid. [SEC_NULL|N/A]
* 
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n
* This function is applicable at the client side only. On server side this function does not have any effect.\n
* Server always supports all the fragmentation length value.
* 
* @par Related Topics
* SSL_ctxGetFragmentLen.
*/

SSLLINKDLL SEC_INT SSL_ctxSetFragmentLen(SSL_CTX_S* pstCTX,
                               const TLS_EXTN_FRAG_LEN_E enFragLen);

/*
    Func Name : SSL_ctxGetFragmentLen
*/

/**
* @defgroup SSL_ctxGetFragmentLen
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* TLS_EXTN_FRAG_LEN_E SSL_ctxGetFragmentLen(const SSL_CTX_S* pstCTX);
* @endcode
* 
* @par Purpose
* This is used to get max fragment length.
* 
* @par Description
* SSL_ctxGetFragmentLen function returns the Fragmentation Length value set by the user using SSL_ctxSetFragmentLen.
* 
* @param[in] pstCTX Pointer to SSL_CTX_S structure. [N/A]
* 
* @retval TLS_EXTN_FRAG_LEN_E Fragmentation Length Value Enum [Fragment length value|N/A]
* @retval TLS_EXTN_FRAG_LEN_E If input is invalid TLS_FRAG_LEN_UNKNOWN is returned. It may also return this value at
* server side though all inputs are valid, because this function is applicable to only client side.
* [TLS_FRAG_LEN_UNKNOWN|Do no pass NULL value and do not use in at server side]
* 
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n
* N/A
* 
* 
* @par Related Topics
* SSL_ctxSetFragmentLen.
*/

SSLLINKDLL TLS_EXTN_FRAG_LEN_E SSL_ctxGetFragmentLen(const SSL_CTX_S* pstCTX);

#endif // IPSI_SSL_NO_SSL


/*
    Func Name: SSL_addServerName
*/

/**
* @defgroup SSL_addServerName
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* SEC_INT SSL_addServerName(SSL_S* pstSSL,
* const TLS_EXTN_SERVERNAME_TYPE_E enType,
* const TLS_SERVERNAME_S* pstServerName);
* @endcode
* 
* @par Purpose
* This is used to set the server name to which client wants to connect.
* 
* @par Description
* SSL_addServerName function sets the server name to which client wants to connect. This servername facilitates the
* secure connections to servers that host multiple 'virtual' server at a single underlying network address. This data
* is used in the extended client hello message if the server_name extension is enabled.
* 
* @param[in] pstServerName Fully qualified DNS ServerName. Length of the servername is <1...2^16-1>Bytes. [N/A]
* @param[in] enType Server Name Type. Currently only one type(TLS_HOST_NAME) is supported. [N/A]
* @param[in] pstSSL ServerName value is added in the SSL_S structure. [N/A]
* 
* @retval SEC_INT If servername successfully added to the input structure. [TLS_SUCCESS |N/A]
* @retval SEC_INT If ServerName is invalid or Memory allocation fails OR enType does not have valid value. [SEC_NULL|N/A]
* 
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n
* 1. This API is applicable at client side only.\n\n
* 2. Function which calls this function has to take care of the following things:\n
*    a) Input Server name should be qualified DNSHostName.\n
*    b) It must not be IPv4 and IPv6.\n
*    c) If ServerName labels contain only US-ASCII characters then the labels are separated only by the byte 0x2E.
* 
* @par Related Topics
* SSL_getServerNameCount,\n
* SSL_getServerName,\n
* SSL_deleteServerName.
*/

SSLLINKDLL SEC_INT SSL_addServerName(SSL_S* pstSSL,
                          const TLS_EXTN_SERVERNAME_TYPE_E enType,
                          const TLS_SERVERNAME_S* pstServerName);

/*
    Func Name : SSL_getServerNameCount
*/

/**
* @defgroup SSL_getServerNameCount
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* SEC_UINT32 SSL_getServerNameCount(const SSL_S * pstSSL);
* @endcode
* 
* @par Purpose
* This is used to get number of server name stored in SSL_S.
* 
* @par Description
* SSL_getServerNameCount function returns the number of server name stored in the SSL_S.\n
* (1) At client side it returns the number of server name, which are added by the SSL_addServerName.\n
* (2) At server side this function returns the number of server name, stored in the SSL_S structure from the
* Extended client hello message.\n
* This function is called from the pfCtxServerCheckName_cb/pfCtxServerCert_cb callback function.
* 
* @param[in] pstSSL Pointer to SSL_S structure. [N/A]
* 
* @retval SEC_UINT32 Total number of server names is returned. [Total number of server names|N/A]
* @retval SEC_UINT32 If Input is Invalid. [SEC_NULL|N/A]
* 
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_addServerName,\n
* SSL_getServerName,\n
* SSL_deleteServerName.
*/
SSLLINKDLL SEC_UINT32 SSL_getServerNameCount(const SSL_S * pstSSL);


/*
    Func Name : SSL_getServerName
*/

/**
* @defgroup SSL_getServerName
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* const TLS_SERVERNAME_S* SSL_getServerName(const SSL_S * pstSSL,
* const SEC_UINT32 uiIndex,
* TLS_EXTN_SERVERNAME_TYPE_E* pucType);
* @endcode
* 
* @par Purpose
* This is used to get server name.
* 
* @par Description
* SSL_getServerName function returns the servername from servername list stored in the SSL_S.\n
* (1) At client side it returns the server name, which is added by the SSL_addServerName.\n
* (2) At server side this function returns the server name, stored in the SSL_S structure from the Extended client
* hello message.\n
* This function is called from the pfCtxServerCheckName_cb/pfCtxServerCert_cb callback function.
* 
* @param[in] pstSSL Pointer to SSL_S structure. [N/A]
* @param[in] uiIndex SSL_S Stored the list of servername. User has to pass the list index, to get the servername from
* that list. Index starts with 0. [N/A]
* @param[out] pucType Type of the server name. Currently only (HOST_NAME) is supported. [N/A]
* 
* @retval TLS_SERVERNAME_S* Server Name [TLS_SERVERNAME_S*|N/A]
* @retval TLS_SERVERNAME_S* If input is invalid. [SEC_NULL|N/A]
* 
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_addServerName,\n
* SSL_getServerNameCount,\n
* SSL_deleteServerName,\n
* SSL_deleteURLAndHash.
*/

SSLLINKDLL const TLS_SERVERNAME_S* SSL_getServerName(const SSL_S * pstSSL,
                                     const SEC_UINT32 uiIndex,
                                     TLS_EXTN_SERVERNAME_TYPE_E* pucType);

/*
    Func Name : SSL_deleteServerName
*/

/**
* @defgroup SSL_deleteServerName
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* SEC_INT32 SSL_deleteServerName(SSL_S * pstSSL,
* const SEC_UINT32 uiIndex);
* @endcode
* 
* @par Purpose
* This is used to delete server name.
* 
* @par Description
* SSL_deleteServerName function deletes the servername from servername list stored in the SSL_S.
* 
* @param[in] pstSSL Pointer to SSL_S structure. [N/A]
* @param[in] uiIndex SSL_S Stored the list of servername. User has to pass the list index, to delete the servername
* from that list. Index starts with 0. [N/A]
* 
* @retval SEC_INT32 On deleting the server name successfully. [TLS_SUCCESS|N/A]
* @retval SEC_INT32 Input is invalid. [SEC_NULL|N/A]
* 
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n
* This API is applicable to only at Client side.
* 
* @par Related Topics
* SSL_addServerName,\n
* SSL_getServerNameCount,\n
* SSL_getServerName.
*/
SSLLINKDLL SEC_INT32 SSL_deleteServerName(SSL_S * pstSSL, const SEC_UINT32 uiIndex);


/*
    Func Name : SSL_addURLandHash
*/

/**
* @defgroup SSL_addURLandHash
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* SEC_INT SSL_addURLandHash(SEC_List_S* pListURLandHash, 
* const SEC_CHAR* pcURL,
* const SEC_UCHAR* pucSHA1Hash,
* const SEC_UINT32 uiSHA1HashLen);
* @endcode
* 
* @par Purpose
* This is used to add certificate URL and Hash.
* 
* @par Description
* SSL_addURLandHash function adds the Certificate URL and optional Hash into the input list. This function is called
* by the application through pfCtxClientCertUrl_cb callback function.
* 
* @param[in] pListURLandHash list to which URL and Hash is to be added [N/A].
* @param[in] pcURL URL refers to a single DER-Encoded X509V3 Certificate or DER-encoded
* certificate chain.Length of URL is <1...2^16-1>Bytes [N/A]
* @param[in] pucSHA1Hash It is the SHA1 hash of the corresponding certificate to which URL refers.
* This field is optional. If hash is not present value of this field is SEC_NULL.[N/A]
* @param[in] uiSHA1HashLen If pucSHA1Hash is not SEC_NULL, it contains the Length of the SHA1HASH. 
* SHA1 hash length value is fixed 20 bytes. [N/A]
*
* @retval SEC_INT TLS_SUCCESS is returned If URL and Hash is successfully added to the list.[TLS_SUCCESS|N/A]
* @retval SEC_INT  0 is returned if any input variable is invalid or memory allocation fails. 
* [SEC_NULL|pass input values correctly]
* 
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getURLAndHashCount,\n
* SSL_getURL,\n
* SSL_getHash,\n
* SSL_deleteURLAndHash.
*/
SSLLINKDLL SEC_INT SSL_addURLandHash(SEC_List_S* pListURLandHash, 
                             const SEC_CHAR* pcURL,
                             const SEC_UCHAR* pucSHA1Hash,
                             const SEC_UINT32 uiSHA1HashLen);

/*
    Func Name : SSL_getURLAndHashCount
*/

/**
* @defgroup SSL_getURLAndHashCount
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* SEC_UINT32 SSL_getURLAndHashCount(const SEC_List_S* pListURLandHash);
* @endcode
* 
* @par Purpose
* This is used to get the number of URLs stored.
* 
* @par Description
* SSL_getURLAndHashCount function returns the number of URLs stored in the List added using SSL_addURLandHash function.\n
* 1. On client side this function returns the number of URLs stored in the list by the SSL_addURLandHash function.
*    This function can be called from the pfCtxClientCertUrl_cb callback function.\n
* 2. On server side this function returns the number of URLs stored in the SSL_S structure from the certificate url
*    message. This function can be called from the pfCtxServerRetriveCertFromUrl_cb callback function.
* 
* @param[in] pListURLandHash URL and Hash List. [N/A]
* 
* @retval SEC_UINT32 Number of URLs stored in the list is returned. [Number of URLs stored in the list|N/A]
* @retval SEC_UINT32 If list is empty. [SEC_NULL|N/A]
* 
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_addURLandHash,\n
* SSL_getURL,\n
* SSL_getHash,\n
* SSL_deleteURLAndHash.
*/
SSLLINKDLL SEC_UINT32 SSL_getURLAndHashCount(const SEC_List_S* pListURLandHash);

/*
    Func Name : SSL_getURL
*/

/**
* @defgroup SSL_getURL
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* const SEC_CHAR* SSL_getURL(const SEC_List_S* pListURLandHash, 
* const SEC_UINT32 uiIndex);
* @endcode
* 
* @par Purpose
* This is used to get URL.
* 
* @par Description
* SSL_getURL function returns the URL from the List of URL and Hash added using SSL_addURLandHash function.\n
* 1. On client side this function can be called from the pfCtxClientCertUrl_cb callback function.\n
* 2. On server side this function returns the URLs stored in the SSL_S structure from the certificate url message.
* This function can be called from the pfCtxServerRetriveCertFromUrl_cb callback function.
* 
* @param[in] pListURLandHash URL and Hash List. [N/A]
* @param[in] uiIndex URL Index number of the input list. Index starts with 0. [N/A]
* 
* @retval SEC_CHAR* Null terminated URL String. [SEC_CHAR*|N/A]
* @retval SEC_CHAR* Input parameters are invalid. [SEC_NULL|N/A]
* 
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_addURLandHash,\n
* SSL_getURLAndHashCount,\n
* SSL_getHash,\n
* SSL_deleteURLAndHash.
*/

SSLLINKDLL const SEC_CHAR* SSL_getURL(const SEC_List_S* pListURLandHash, 
                           const SEC_UINT32 uiIndex);

/*
    Func Name : SSL_getHash
*/

/**
* @defgroup SSL_getHash
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* const SEC_UCHAR* SSL_getHash(const SEC_List_S* pListURLandHash, const SEC_UINT32 uiIndex);
* @endcode
* 
* @par Purpose
* This is used to get Hash.
* 
* @par Description
* SSL_getHash function returns the HASH from the list of the URL and Hash added using SSL_addURLandHash function.\n
* 1. On client side this function can be called from the pfCtxClientCertUrl_cb callback function.\n
* 2. On server side this function returns the Hash stored in the SSL_S structure from the certificate url message.
* This function can be called from the pfCtxServerRetriveCertFromUrl_cb callback function.
* 
* @param[in] pListURLandHash URL and Hash List. [N/A]
* @param[in] uiIndex HASH Index number of the input list.Index starts with 0. [N/A]
* 
* @retval SEC_UCHAR* If hash is present 20 bytes unsigned char array is returned else SEC_NULL is returned. [SEC_UCHAR*|N/A]
* @retval SEC_UCHAR* Input parameters are invalid. [SEC_NULL|N/A]
* 
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_addURLandHash,\n
* SSL_getURLAndHashCount,\n
* SSL_getURL,\n
* SSL_deleteURLAndHash.
*/

SSLLINKDLL const SEC_UCHAR* SSL_getHash(const SEC_List_S* pListURLandHash, 
                             const SEC_UINT32 uiIndex);

/*
    Func Name : SSL_deleteURLAndHash
*/

/**
* @defgroup SSL_deleteURLAndHash
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* SEC_INT SSL_deleteURLAndHash(SEC_List_S* pListURLandHash, const SEC_UINT32 uiIndex);
* @endcode
* 
* @par Purpose
* This is used to delete URL and Hash.
* 
* @par Description
* SSL_deleteURLAndHash function deletes the URLandHash node from the input list.
* 
* @param[in] uiIndex Index of the node which has to be deleted from the list. Index starts with 0. [N/A]
* @param[in] pListURLandHash the list from which Node of URLandHash is deleted. [N/A]
* 
* @retval SEC_INT URLAndHash node deleted successfully. [TLS_SUCCESS|N/A]
* @retval SEC_INT Input parameters are invalid. [SEC_NULL|N/A]
* 
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_addURLandHash,\n
* SSL_getURLAndHashCount,\n
* SSL_getURL,\n
* SSL_getHash.
*/
SSLLINKDLL SEC_INT SSL_deleteURLAndHash(SEC_List_S* pListURLandHash, 
                             const SEC_UINT32 uiIndex);

/*
   Func Name:  SSL_ctxAddOCSPRespInfo
*/

/**
* @defgroup SSL_ctxAddOCSPRespInfo
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxAddOCSPRespInfo(SSL_CTX_S* pstCTX,
* const TLS_RESPONDERID_S* pstRespID,
* const X509_CERT_S * pstOCSPCert);
* @endcode
* 
* @par Purpose
* This is used to add a trusted OCSP responder ID and the corresponding OCSP certificate.
* 
* @par Description
* SSL_ctxAddOCSPRespInfo function adds a trusted OCSP responder ID and the corresponding OCSP certificate to the
* SSL_CTX_S structure. OCSP Responder ID is DER encoded of ASN.1 type.
* 
* @param[in] pstRespID DER-Encoded OCSP Responder ID. [N/A]
* @param[in] pstOCSPCert OCSP server's Certificate. [N/A]
* @param[in] pstCTX SSL_CTX_S structure in which Responder ID and OCSP certificate are added. [N/A]
* 
* @retval SEC_INT OCSP Responder ID & certificate are successfully added to SSL_CTX_S structure. [TLS_SUCCESS|N/A]
* @retval SEC_INT On failure. [SEC_NULL|N/A]
* 
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n
* This function is applicable at the client side only.
* 
* @par Related Topics
* SSL_ctxGetOCSPRespIDCount,\n
* SSL_ctxGetOCSPRespID,\n
* SSL_ctxGetOCSPCert,\n
* SSL_ctxDeleteOCSPRespInfo,\n
* SSL_ctxSetOCSPExtn,\n
* SSL_ctxGetOCSPExtn,\n
* SSL_getOCSPRespIDCount,\n
* SSL_getOCSPRespID,\n
* SSL_getOCSPExtn.
*/

SSLLINKDLL SEC_INT SSL_ctxAddOCSPRespInfo(SSL_CTX_S* pstCTX,
                            const TLS_RESPONDERID_S* pstRespID,
                            const X509_CERT_S * pstOCSPCert);

/*
    Func Name : SSL_ctxGetOCSPRespIDCount
*/

/**
* @defgroup SSL_ctxGetOCSPRespIDCount
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* SEC_UINT32 SSL_ctxGetOCSPRespIDCount(const SSL_CTX_S *pstCTX);
* @endcode
* 
* @par Purpose
* This is used to get number of OCSP ResponderID stored.
* 
* @par Description
* SSL_ctxGetOCSPRespIDCount function returns the number of OCSP ResponderID stored in the SSL_CTX_S structure.
* 
* @param[in] pstCTX SSL_CTX_S structure where OCSP Responder ID is available. [N/A]
* 
* @retval SEC_UINT32 Number of OCSP Responder ID stored in the SSL_CTX_S structure is returned. [Number of OCSP
* Responder ID stored in the SSL_CTX_S structure|N/A]
* @retval SEC_UINT32 Input parameter is invalid. [SEC_NULL|N/A]
* 
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n
* This function is applicable at the client side only.
* 
* @par Related Topics
* SSL_ctxAddOCSPRespInfo,\n
* SSL_ctxGetOCSPRespID,\n
* SSL_ctxGetOCSPCert,\n
* SSL_ctxDeleteOCSPRespInfo,\n
* SSL_ctxSetOCSPExtn,\n
* SSL_ctxGetOCSPExtn,\n
* SSL_getOCSPRespIDCount,\n
* SSL_getOCSPRespID,\n
* SSL_getOCSPExtn.
*/
SSLLINKDLL SEC_UINT32 SSL_ctxGetOCSPRespIDCount(const  SSL_CTX_S *pstCTX);

/*
    Func Name : SSL_ctxGetOCSPRespID
*/

/**
* @defgroup SSL_ctxGetOCSPRespID
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* const TLS_RESPONDERID_S* SSL_ctxGetOCSPRespID(const SSL_CTX_S *pstCTX, const SEC_UINT32 uiIndex);
* @endcode
* 
* @par Purpose
* This is used to get stored OCSP Responder.
* 
* @par Description
* SSL_ctxGetOCSPRespID function returns the OCSP Responder ID stored in the SSL_CTX_S structure.
* 
* @param[in] pstCTX SSL_CTX_S structure where OCSP Responder ID is stored. [N/A]
* @param[in] uiIndex Index of the list of OCSP responder ID. [N/A]
* 
* @retval TLS_RESPONDERID_S* Pointer to OCSP Responder ID. [TLS_RESPONDERID_S*|N/A]
* @retval TLS_RESPONDERID_S* Input parameters are invalid. [SEC_NULL|N/A]
* 
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n
* This function is applicable at the client side only.
* 
* @par Related Topics
* SSL_ctxAddOCSPRespInfo,\n
* SSL_ctxGetOCSPRespIDCount,\n
* SSL_ctxGetOCSPCert,\n
* SSL_ctxDeleteOCSPRespInfo,\n
* SSL_ctxSetOCSPExtn,\n
* SSL_ctxGetOCSPExtn,\n
* SSL_getOCSPRespIDCount,\n
* SSL_getOCSPRespID,\n
* SSL_getOCSPExtn.
*/
SSLLINKDLL const TLS_RESPONDERID_S* SSL_ctxGetOCSPRespID(const SSL_CTX_S *pstCTX,
                                               const SEC_UINT32 uiIndex);

/*
    Func Name : SSL_ctxGetOCSPCert
*/

/**
* @defgroup SSL_ctxGetOCSPCert
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* const X509_CERT_S * SSL_ctxGetOCSPCert(const SSL_CTX_S *pstCTX,
* const TLS_RESPONDERID_S * pRespId);
* @endcode
* 
* @par Purpose
* This is used to get OCSP certificate.
* 
* @par Description
* SSL_ctxGetOCSPCert function returns the OCSP Certificate stored in the SSL_CTX_S structure corresponding to the
* input OCSP responder ID. 
* 
* @param[in] pstCTX SSL_CTX_S structure where OCSP Responder ID & Certificate is stored. [N/A]
* @param[in] pRespId Pointer to OCSP Responder ID. [N/A]
* 
* @retval X509_CERT_S* Pointer to OCSP Certificate. [Pointer to X509_CERT_S|N/A]
* @retval X509_CERT_S* Input parameters are invalid/ Responder id not found. [SEC_NULL|N/A]
* 
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n
* This function is applicable at the client side only.
* 
* @par Related Topics
* SSL_ctxAddOCSPRespInfo,\n
* SSL_ctxGetOCSPRespIDCount,\n
* SSL_ctxGetOCSPRespID,\n
* SSL_ctxDeleteOCSPRespInfo,\n
* SSL_ctxSetOCSPExtn,\n
* SSL_ctxGetOCSPExtn,\n
* SSL_getOCSPRespIDCount,\n
* SSL_getOCSPRespID,\n
* SSL_getOCSPExtn.
*/
SSLLINKDLL const X509_CERT_S * SSL_ctxGetOCSPCert(const SSL_CTX_S *pstCTX,
                                          const TLS_RESPONDERID_S * pRespId);


/*
    Func Name : SSL_ctxDeleteOCSPRespInfo
*/

/**
* @defgroup SSL_ctxDeleteOCSPRespInfo
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxDeleteOCSPRespInfo(SSL_CTX_S * pstCTX, const SEC_UINT32 uiIndex);
* @endcode
* 
* @par Purpose
* This is used to delete OCSP responder ID and certificate.
* 
* @par Description
* SSL_ctxDeleteOCSPRespInfo function deletes the OCSP Responder ID & certificate from the SSL_CTX_S structure.
* 
* @param[in] pstCTX SSL_CTX_S structure where OCSP Responder Info is stored. [N/A]
* @param[in] uiIndex Position of the responder id which has to be deleted, in the list of OCSP Responder Info. [N/A]
* 
* @retval SEC_INT OCSP Responder Info is successfully deleted from SSL_CTX_S structure. [TLS_SUCCESS|N/A]
* @retval SEC_INT Input parameters are invalid. [SEC_NULL|N/A]
* 
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n
* This function is applicable at the client side only.
* 
* @par Related Topics
* SSL_ctxAddOCSPRespInfo,\n
* SSL_ctxGetOCSPRespIDCount,\n
* SSL_ctxGetOCSPRespID,\n
* SSL_ctxGetOCSPCert,\n
* SSL_ctxSetOCSPExtn,\n
* SSL_ctxGetOCSPExtn,\n
* SSL_getOCSPRespIDCount,\n
* SSL_getOCSPRespID,\n
* SSL_getOCSPExtn.
*/
SSLLINKDLL SEC_INT SSL_ctxDeleteOCSPRespInfo(SSL_CTX_S * pstCTX,
                                 const SEC_UINT32 uiIndex);

/*
    Func Name : SSL_ctxSetOCSPExtn
*/

/**
* @defgroup SSL_ctxSetOCSPExtn
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxSetOCSPExtn(SSL_CTX_S* pstCTX,
* const TLS_OCSPEXTN_S* pstOCSPExtn);
* @endcode
* 
* @par Purpose
* This is used to set the OCSP Request Extensions.
* 
* @par Description
* SSL_ctxSetOCSPExtn function sets the OCSP Request Extensions to the SSL_CTX_S structure.
* 
* @param[in] pstOCSPExtn Pointer to OCSP Request Extensions. [N/A]
* @param[in] pstCTX OCSP Extensions are to be set in the SSL_CTX_S structure. [N/A]
* 
* @retval SEC_INT OCSP Extensions are successfully set in the SSL_CTX_S structure. [TLS_SUCCESS|N/A]
* @retval SEC_INT Input Parameters are invalid. Memory allocation fails. [SEC_NULL|N/A]
* 
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n
* This function is applicable at the client side only.  On server side this function does not have any effect.
* 
* @par Related Topics
* SSL_ctxAddOCSPRespInfo\n
* SSL_ctxGetOCSPRespIDCount,\n
* SSL_ctxGetOCSPRespID,\n
* SSL_ctxGetOCSPCert,\n
* SSL_ctxDeleteOCSPRespInfo,\n
* SSL_ctxGetOCSPExtn,\n
* SSL_getOCSPRespIDCount,\n
* SSL_getOCSPRespID,\n
* SSL_getOCSPExtn.
*/
SSLLINKDLL SEC_INT SSL_ctxSetOCSPExtn(SSL_CTX_S* pstCTX,
                            const TLS_OCSPEXTN_S* pstOCSPExtn);

/*
    Func Name:SSL_ctxGetOCSPExtn
*/

/**
* @defgroup SSL_ctxGetOCSPExtn
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* const TLS_OCSPEXTN_S* SSL_ctxGetOCSPExtn(const SSL_CTX_S* pstCTX);
* @endcode
* 
* @par Purpose
* This is used to get stored OCSP Request Extensions.
* 
* @par Description
* SSL_ctxGetOCSPExtn function returns the OCSP Request Extensions stored in the SSL_CTX_S structure.
* 
* @param[in] pstCTX SSL_CTX_S structure where OCSP Request Extensions is stored. [N/A]
* 
* @retval TLS_OCSPEXTN_S* Pointer to OCSP Extension. [TLS_OCSPEXTN_S*|N/A]
* @retval TLS_OCSPEXTN_S* SEC_NULL is return if invalid input parameter [SEC_NULL|provide correct input parameter]
*
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n
* This function is applicable at the client side only.
* 
* @par Related Topics
* SSL_ctxAddOCSPRespInfo,\n
* SSL_ctxGetOCSPRespIDCount,\n
* SSL_ctxGetOCSPRespID,\n
* SSL_ctxGetOCSPCert,\n
* SSL_ctxDeleteOCSPRespInfo,\n
* SSL_ctxSetOCSPExtn,\n
* SSL_getOCSPRespIDCount,\n
* SSL_getOCSPRespID,\n
* SSL_getOCSPExtn.
*/
SSLLINKDLL const TLS_OCSPEXTN_S* SSL_ctxGetOCSPExtn(const SSL_CTX_S* pstCTX);

/*
    Func Name : SSL_getOCSPRespIDCount
*/

/**
* @defgroup SSL_getOCSPRespIDCount
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* SEC_UINT32 SSL_getOCSPRespIDCount(const  SSL_S *pstSSL);
* @endcode
* 
* @par Purpose
* This is used to get the total number of OCSP Responder ID client trusted.
* 
* @par Description
* SSL_getOCSPRespIDCount function is used at the server side to get the total number of OCSP Responder ID client trusted.
* This function is called from the pfCtxServerCertStatus_cb callback function.
* 
* @param[in] pstSSL pointer to the SSL object [N/A]
* 
* @retval SEC_UINT32 Number of OCSP Responder ID client trusted is returned. [Number of OCSP Responder ID client
* trusted|N/A]
* @retval SEC_UINT32 Input parameter is invalid. [SEC_NULL|N/A]
* 
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n
* This function is applicable at the server side only.
* 
* @par Related Topics
* SSL_ctxAddOCSPRespInfo,\n
* SSL_ctxGetOCSPRespIDCount,\n
* SSL_ctxGetOCSPRespID,\n
* SSL_ctxGetOCSPCert,\n
* SSL_ctxDeleteOCSPRespInfo,\n
* SSL_ctxSetOCSPExtn,\n
* SSL_getOCSPRespID,\n
* SSL_getOCSPExtn.
*/
SSLLINKDLL SEC_UINT32 SSL_getOCSPRespIDCount(const  SSL_S *pstSSL);

/*
    Func Name : SSL_getOCSPRespID
*/

/**
* @defgroup SSL_getOCSPRespID
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* const TLS_RESPONDERID_S* SSL_getOCSPRespID(const SSL_S *pstSSL,
* const SEC_UINT32 uiIndex);
* @endcode
* 
* @par Purpose
* This is used to get the OCSP ResponderID.
* 
* @par Description
* SSL_getOCSPRespID function is used at the server side to get the OCSP ResponderID from the SSL_S structure.
* This function is called from the pfCtxServerCertStatus_cb callback function.
* 
* @param[in] pstSSL SSL_S structure where List of OCSP Responder ID is stored. [N/A]
* @param[in] uiIndex Index of Responder ID in the list. [N/A]
* 
* @retval TLS_RESPONDERID_S* OCSP Responder ID client trusted. [TLS_RESPONDERID_S*|N/A]
* @retval TLS_RESPONDERID_S* Input parameters are invalid. [SEC_NULL|N/A]
* 
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n
* This function is applicable only for the server.
* 
* @par Related Topics
* SSL_ctxAddOCSPRespInfo,\n
* SSL_ctxGetOCSPRespIDCount,\n
* SSL_ctxGetOCSPRespID,\n
* SSL_ctxGetOCSPCert,\n
* SSL_ctxDeleteOCSPRespInfo,\n
* SSL_ctxSetOCSPExtn,\n
* SSL_getOCSPRespIDCount,\n
* SSL_getOCSPExtn.
*/

SSLLINKDLL const TLS_RESPONDERID_S* SSL_getOCSPRespID(const  SSL_S *pstSSL,
                                               const SEC_UINT32 uiIndex);

/*
    Func Name : SSL_getOCSPExtn
*/

/**
* @defgroup SSL_getOCSPExtn
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* const TLS_OCSPEXTN_S* SSL_getOCSPExtn(const SSL_S * pstSSL);
* @endcode
* 
* @par Purpose
* This is used to get the OCSP Request Extensions.
* 
* @par Description
* SSL_getOCSPExtn function is used at the server side to get the OCSP Request Extensions from the SSL_S structure.
* This function is called from the pfCtxServerCertStatus_cb callback function.
* 
* @param[in] pstSSL SSL_S structure where OCSP request Extensions are stored. [N/A]
* 
* @retval TLS_OCSPEXTN_S* OCSP Request Extensions to be used to while requesting for the server certificates
* OCSP status. [TLS_OCSPEXTN_S*|N/A]
* @retval TLS_OCSPEXTN_S* If OCSP Request Extension is not available. Input parameters is Invalid. [SEC_NULL|N/A]
* 
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n
* This function is applicable only for the server.
* 
* @par Related Topics
* SSL_ctxAddOCSPRespInfo\n
* SSL_ctxGetOCSPRespIDCount,\n
* SSL_ctxGetOCSPRespID,\n
* SSL_ctxGetOCSPCert,\n
* SSL_ctxDeleteOCSPRespInfo,\n
* SSL_ctxSetOCSPExtn,\n
* SSL_getOCSPRespIDCount,\n
* SSL_getOCSPRespID.
*/

SSLLINKDLL const TLS_OCSPEXTN_S* SSL_getOCSPExtn(const SSL_S * pstSSL);

/*
    Func Name : SSL_ctxAddTrustedCA
*/

/**
* @defgroup SSL_ctxAddTrustedCA
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxAddTrustedCA(SSL_CTX_S* pstCTX,
* const TLS_EXTN_CA_IDENTIFIER_E enIdentifierType,
* const TLS_CAIDENTIFIER_S* pstCAIdentifier);
* @endcode
* 
* @par Purpose
* This is used to add the CA root key identifier.
* 
* @par Description
* SSL_ctxAddTrustedCA function is used to add the CA root key identifier to the SSL_CTX_S structure. This functions
* takes the input CAIdentifier type and identifier data according to the type. Identifier can be of the four types:\n
* PRE_AGREED,\n
* KEY_SHA1_HASH,\n
* X509_DN,\n
* CERT_SHA1_HASH.\n
* CAIdentifier data is different for each identifier type.\n
* For PRE_AGREED type identifier data is NULL. This type allows the client to indicate the possession of some
* pre-defined set of CA root key.\n
* For KEY_SHA1_HASH type identifier data is SHA-1 hash of the CA root key.\n
* For X509_DN type identifier data is DER-Encoded X509 DN of the CA.\n
* For CERT_SHA1_HASH type identifier data is SHA-1 hash of the Der-Encoded certificate containing root CA key.
* 
* @param[in] enIdentifierType CA Identifier type. The types can be\n
* PRE_AGREED\n
* KEY_SHA1_HASH\n
* X509_DN\n
* CERT_SHA1_HASH [N/A]
* @param[in] pstCAIdentifier CA Identifier data. [N/A]
* @param[in] pstCTX New trusted CA identifier is added to the list of trusted CA identifiers stored in SSL_CTX_S. [N/A]
* 
* @retval SEC_INT If input is invalid. [SEC_NULL|N/A]
* @retval SEC_INT Trusted CA Extension is successfully added to the SSL_CTX_S structure. [TLS_SUCCESS|N/A]
* 
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n
* This function is applicable at the client side only. On the server side, this function does not have any effect.
* 
* @par Related Topics
* SSL_ctxGetTrustedCACount,\n
* SSL_ctxGetTrustedCA,\n
* SSL_ctxDeleteTrustedCA,\n
* SSL_getTrustedCACount,\n
* SSL_getTrustedCA.
*/

SSLLINKDLL SEC_INT SSL_ctxAddTrustedCA(SSL_CTX_S* pstCTX,
                             const TLS_EXTN_CA_IDENTIFIER_E enIdentifierType,
                             const TLS_CAIDENTIFIER_S* pstCAIdentifier);

/*
    Func Name : SSL_ctxGetTrustedCACount
*/

/**
* @defgroup SSL_ctxGetTrustedCACount
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* SEC_UINT32 SSL_ctxGetTrustedCACount(const SSL_CTX_S* pstCTX);
* @endcode
* 
* @par Purpose
* This is used to get the total number of CA Trusted Identifier stored.
* 
* @par Description
* SSL_ctxGetTrustedCACount function gets the total number of CA Trusted Identifier stored in the SSL_CTX_S structure.
* 
* @param[in] pstCTX SSL_CTX_S structure where Trusted CA Identifier is stored. [N/A]
* 
* @retval SEC_UINT32 Number of Trusted CA Identifiers stored in the SSL_CTX_S structure.
* [Number of Trusted CA Identifiers|N/A]
* @retval SEC_UINT32 Input parameter is invalid. [SEC_NULL|N/A]
* 
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n
* This function is applicable at the client side only.
* 
* @par Related Topics
* SSL_ctxAddTrustedCA,\n
* SSL_ctxGetTrustedCA,\n
* SSL_ctxDeleteTrustedCA,\n
* SSL_getTrustedCACount,\n
* SSL_getTrustedCA.
*/
SSLLINKDLL SEC_UINT32 SSL_ctxGetTrustedCACount(const SSL_CTX_S* pstCTX);


/*
    Func Name: SSL_ctxGetTrustedCA
*/

/**
* @defgroup SSL_ctxGetTrustedCA
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* const TLS_CAIDENTIFIER_S* SSL_ctxGetTrustedCA(const SSL_CTX_S* pstCTX,
* const SEC_UINT32 uiIndex,
* TLS_EXTN_CA_IDENTIFIER_E * peCAIdentifierType);
* @endcode
* 
* @par Purpose
* This is used to get Trusted CA Identifier stored.
* 
* @par Description
* SSL_ctxGetTrustedCA function returns the Trusted CA Identifier stored in the SSL_CTX_S structure.
* 
* @param[in] pstCTX SSL_CTX_S structure where Trusted CA Identifier stored. [N/A]
* @param[in] uiIndex Index of the Trusted CA identifier stored in the SSL_CTX_S structure. [N/A]
* @param[out] peCAIdentifierType CA identifier type. [N/A]
* 
* @retval TLS_CAIDENTIFIER_S* Trusted CA identifier. [Pointer to TLS_CAIDENTIFIER_S|N/A]
* 
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n
* This function is applicable at the client side only.
* 
* @par Related Topics
* SSL_ctxAddTrustedCA,\n
* SSL_ctxGetTrustedCACount,\n
* SSL_ctxDeleteTrustedCA,\n
* SSL_getTrustedCACount,\n
* SSL_getTrustedCA.
*/

SSLLINKDLL const TLS_CAIDENTIFIER_S* SSL_ctxGetTrustedCA(const SSL_CTX_S* pstCTX,
                                               const SEC_UINT32 uiIndex,
                                               TLS_EXTN_CA_IDENTIFIER_E * peCAIdentifierType);
/*
    Func Name : SSL_ctxDeleteTrustedCA
*/

/**
* @defgroup SSL_ctxDeleteTrustedCA
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* SEC_INT32 SSL_ctxDeleteTrustedCA(SSL_CTX_S* pstCTX,
* const SEC_UINT32 uiIndex);
* @endcode
* 
* @par Purpose
* This is used to delete the trusted CA Identifier data.
* 
* @par Description
* SSL_ctxDeleteTrustedCA function deletes the trusted CA Identifier data from the SSL_CTX_S structure.
* 
* @param[in] uiIndex Index of the Trusted CA identifier stored in the SSL_CTX_S structure. [N/A]
* @param[in] pstCTX SSL_CTX_S structure from which indexed trusted CA Identifier data is deleted . [N/A]
* 
* @retval SEC_INT32 Indexed trusted CA Identifier data deleted successfully. [TLS_SUCCESS|N/A]
* @retval SEC_INT32 Input parameters are invalid. [SEC_NULL|N/A]
* 
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n
* This function is applicable at the client side only.
* 
* @par Related Topics
* SSL_ctxAddTrustedCA,\n
* SSL_ctxGetTrustedCACount,\n
* SSL_ctxGetTrustedCA,\n
* SSL_getTrustedCACount,\n
* SSL_getTrustedCA.
*/
SSLLINKDLL SEC_INT32 SSL_ctxDeleteTrustedCA(SSL_CTX_S* pstCTX , const SEC_UINT32 uiIndex);


/*
    Func Name : SSL_getTrustedCACount
*/

/**
* @defgroup SSL_getTrustedCACount
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* SEC_UINT32 SSL_getTrustedCACount(const SSL_S* pstSSL);
* @endcode
* 
* @par Purpose
* This is use dto get the number of the trusted CA Identifiers stored.
* 
* @par Description
* SSL_getTrustedCACount function returns the number of the trusted CA Identifiers stored in the SSL structure. At server
* side this function is called from the pfCtxServerCert_cb callback function.
* 
* @param[in] pstSSL SSL structure where CA identifier data is stored. [N/A]
* 
* @retval SEC_UINT32 Number of trusted CA identifiers is returned. [Number of trusted CA identifiers|N/A]
* @retval SEC_UINT32 Input parameter is invalid. [SEC_NULL|N/A]
* 
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n
* This function is applicable only for the server.
* 
* @par Related Topics
* SSL_ctxAddTrustedCA,\n
* SSL_ctxGetTrustedCACount,\n
* SSL_ctxGetTrustedCA,\n
* SSL_ctxDeleteTrustedCA,\n
* SSL_getTrustedCA.
*/
SSLLINKDLL SEC_UINT32 SSL_getTrustedCACount(const SSL_S* pstSSL);
/*
    Func Name : SSL_getTrustedCA
*/

/**
* @defgroup SSL_getTrustedCA
* @ingroup tls1_extnsFunctions
* @par Prototype
* @code
* const TLS_CAIDENTIFIER_S* SSL_getTrustedCA(const SSL_S* pstSSL,
* const SEC_UINT32 uiIndex,
* TLS_EXTN_CA_IDENTIFIER_E * peCAIdentifierType);
* @endcode
* 
* @par Purpose
* This is used to get rusted CA Identifiers stored.
* 
* @par Description
* SSL_getTrustedCA function returns the trusted CA Identifiers stored in the SSL structure. At server side this function
* is called from the pfCtxServerCert_cb callback function.
* 
* @param[in] pstSSL SSL structure where CA identifier data is stored. [N/A]
* @param[in] uiIndex Index of the Trusted CA identifier stored in the SSL structure. [N/A]
* @param[out] peCAIdentifierType CA identifier type. [N/A]
* 
* @retval TLS_CAIDENTIFIER_S* Trusted CA identifier. [Pointer to TLS_CAIDENTIFIER_S|N/A]
* @retval TLS_CAIDENTIFIER_S* If input parameters are invalid. [SEC_NULL|N/A]
* 
* @par Required Header File
* tls1_extns.h
* 
* @par Note
* \n
* This function is applicable only for the server.
* 
* @par Related Topics
* SSL_ctxAddTrustedCA,\n
* SSL_ctxGetTrustedCACount,\n
* SSL_ctxGetTrustedCA,\n
* SSL_ctxDeleteTrustedCA,\n
* SSL_getTrustedCACount.
*/

SSLLINKDLL const TLS_CAIDENTIFIER_S* SSL_getTrustedCA(const SSL_S* pstSSL,
                                           const SEC_UINT32 uiIndex,
                                           TLS_EXTN_CA_IDENTIFIER_E * peCAIdentifierType);

#endif


/* Satish - 2010-02-16 */
/* It sets the bit to enable the secure renegotiation extension flag */
#define TLS_SECURE_RENEGOTIATION_EXTN     0x0040

/* Satish - 2010-02-16 */

#ifndef IPSI_NO_TLS12 

#define TLS_SIGN_HASH_EXTN    0x0080
#endif

#ifdef	__cplusplus
}
#endif /* end of __cplusplus */


#endif /* __IPSI_TLS_EXTENS_H__*/

// #endif Commented by Satish - 2010-04-10


