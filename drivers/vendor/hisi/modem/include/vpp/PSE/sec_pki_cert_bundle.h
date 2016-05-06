/*****************************************************************************
                                                                            
                Copyright (C), 2008, Huawei Tech. Co., Ltd.                
                            ALL RIGHTS RESERVED                             
                                                                            
------------------------------------------------------------------------------


FileName     :sec_pki_cert_bundle.h
Author       :
Version      :1
Date         :17-02-10
Description  :Describes the Certificate bundle API(s)
Function List: 
          History:
                    <author>   <date>          <desc>
----------------------------------------------------------------------------
****************************************************************************/
#include "ipsi_pse_build_conf.h"

#ifndef IPSI_SEC_NO_PKI
#ifndef __IPSI_SEC_NO_CERT_BUNDLE__

#ifndef __SEC_PKI_CERT_BUNDLE_H__
#define __SEC_PKI_CERT_BUNDLE_H__

#include "ipsi_types.h"
#include "sec_sys.h"
#include "sec_list.h"
#include "x509_basictypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
Introduction to Certificate bundle:
Certificate bundle is defined in the RFC 4306 as follows

CertificateOrCRL ::= CHOICE 
{
    cert [0] Certificate,
    crl  [1] CertificateList    //It is a CRL 
}

CertificateBundle ::= SEQUENCE OF CertificateOrCRL

*/

/**
* @defgroup CertBundle
* This contains all the certificate bundle APIs
*/
/**
* @defgroup CertBundle_structure
* @ingroup CertBundle
* This contains all the structures
*/
/**
* @defgroup CertBundle_Functions
* @ingroup CertBundle
* This contains all the Functions
*/

/**
* @defgroup SEC_PKI_CERT_BUNDLE_S
* @ingroup CertBundle_structure 
* @par Prototype
* @code
* typedef SEC_List_S SEC_PKI_CERT_BUNDLE_S;
* @endcode
*
* @par Note
* \n
* This structure will contain the sequence of crls and certs.
*/
typedef SEC_List_S SEC_PKI_CERT_BUNDLE_S;



/**
* @defgroup SEC_PKI_createCertBundle
* @ingroup CertBundle_Functions
* @par Prototype
* @code
* SEC_PKI_CERT_BUNDLE_S* SEC_PKI_createCertBundle( X509_CERT_S *pstCert, 
*                                  X509_CRL_S *pstCRL);
* @endcode
* 
* @par Purpose
* This is used to create the certificate bundle.
* 
* @par Description
* SEC_PKI_createCertBundle creates the X509 bundle.
* User can pass either certificate or CRL or both.
* 
* @param[in] pstCert Pointer to Certificate. [NA/NA]
* @param[in] pstCRL Pointer to CRL. [NA/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval SEC_PKI_CERT_BUNDLE_S* In Case of Successful creation of 
* certificate bundle [NA|NA]
* @retval SEC_NULL In case of failure.[NULL|NA]
*
* @par Memory Handling
* \n
* ipsi will allocate memory for SEC_PKI_CERT_BUNDLE_S,
* to free this memory user has to call the SEC_PKI_freeCertBundle function.
*/
PSELINKDLL SEC_PKI_CERT_BUNDLE_S* SEC_PKI_createCertBundle(
                    X509_CERT_S *pstCert, 
                    X509_CRL_S *pstCRL);

/**
* @defgroup SEC_PKI_freeCertBundle
* @ingroup CertBundle_Functions
* @par Prototype
* @code
* SEC_VOID SEC_PKI_freeCertBundle( SEC_PKI_CERT_BUNDLE_S *pstCertBundle);
* @endcode
*
* @par Purpose
* This function is used to free certificate bundle.
*
* @par Description
* SEC_PKI_freeCertBundle function is used to free the certificate bundle
*
* @param[in] pstCertBundle Pointer to SEC_PKI_CERT_BUNDLE_S.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_VOID This function does not return any value.[NA|NA]
*
*/
PSELINKDLL SEC_VOID SEC_PKI_freeCertBundle(
                       SEC_PKI_CERT_BUNDLE_S *pstCertBundle);

/**
* @defgroup SEC_PKI_addCertToCertBundle
* @ingroup CertBundle_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_addCertToCertBundle( SEC_PKI_CERT_BUNDLE_S *pstCertBundle,
*                                  X509_CERT_S *pstCert);
* @endcode
* 
* @par Purpose
* This is used to add a certificate to certificate bundle
* 
* @par Description
* SEC_PKI_X509_addCertToCertBundle adds the X509 certificate to 
* certificate bundle.
* 
* @param[in] pstCertBundle Pointer to certificate Bundle. [NA/NA]
* @param[in] pstCert Pointer to X509 certificate. [NA/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval SEC_INT In case of success [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT In case of failure.[SEC_PKI_ERROR|NA]
* 
*/
PSELINKDLL SEC_INT SEC_PKI_addCertToCertBundle(
                                SEC_PKI_CERT_BUNDLE_S *pstCertBundle,
                                X509_CERT_S *pstCert);

/**
* @defgroup SEC_PKI_addCrlToCertBundle
* @ingroup CertBundle_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_addCrlToCertBundle(
*                                  SEC_PKI_CERT_BUNDLE_S *pstCertBundle,
*                                  X509_CRL_S *pstCrl);
* @endcode
* 
* @par Purpose
* This is used to add the CRL to the certificate bundle
* 
* @par Description
* SEC_PKI_addCrlToCertBundle adds the CRL to the certificate bundle
* 
* @param[in] pstCertBundle Pointer to certificate bundle. [NA/NA]
* @param[in] pstCrl Pointer to Certificate revocation list. [NA/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval SEC_INT In case of success [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT In case of failure.[SEC_PKI_ERROR|NA]
*
*/
PSELINKDLL SEC_INT SEC_PKI_addCrlToCertBundle(
                               SEC_PKI_CERT_BUNDLE_S *pstCertBundle,
                               X509_CRL_S *pstCrl);

/**
* @defgroup SEC_PKI_encodeCertBundle
* @ingroup CertBundle_Functions
* @par Prototype
* @code
* SEC_UCHAR* SEC_PKI_encodeCertBundle(
*                                  SEC_PKI_CERT_BUNDLE_S *pstCertBundle, 
*                                  SEC_UINT32* puiEncodedLen);
* @endcode
* 
* @par Purpose
* This is used to encode the input certificate bundle
* 
* @par Description
* SEC_PKI_encodeCertBundle encodes the input certificate bundle
* 
* @param[in] pstCertBundle Certificate Bundle. [NA/NA]
* @param[out] puiEncodedLen Encoded Length. [NA/NA]
* 
* @retval SEC_UCHAR* In case of success.[NA|NA]
* @retval SEC_NULL In case of failure.[Null|NA]
* @par Memory Handling
* \n
* ipsi will allocate the memory for the encoded buffer output, to free this 
* memory user should use the ipsi_free function.
*/
PSELINKDLL SEC_UCHAR* SEC_PKI_encodeCertBundle(
        SEC_PKI_CERT_BUNDLE_S *pstCertBundle, 
        SEC_UINT32* puiEncodedLen);

/**
* @defgroup SEC_PKI_decodeCertBundle
* @ingroup CertBundle_Functions
* @par Prototype
* @code
* SEC_PKI_CERT_BUNDLE_S *SEC_PKI_decodeCertBundle(
*                                 SEC_CHAR* pucEncodedCertBundle,
*                                 SEC_UINT32 uiEncodedLength,
*                                 SEC_UINT32* puiDecodedLength);
* @endcode
* 
* @par Purpose
* This is used to decode the encoded certificate bundle
* 
* @par Description
* SEC_PKI_decodeCertBundle decodes the input certificate bundle
* 
* @param[in] pucEncodedCertBundle Encoded certificate bundle. [NA/NA]
* @param[in] uiEncodedLength Encoded Length. [NA/NA]
* @param[out] puiDecodedLength Contains the decoded length [NA/NA]
* 
* @retval SEC_PKI_CERT_BUNDLE_S* Certificate bundle in case of success[NA|NA].
* @retval SEC_NULL In case of failures.[Null|NA]
* @par Memory Handling
* \n
* ipsi will allocate the ouput certificate bundle, user should call the 
* SEC_PKI_freeCertBundle function to free the output
*/
PSELINKDLL SEC_PKI_CERT_BUNDLE_S * SEC_PKI_decodeCertBundle(
    SEC_CHAR* pucEncodedCertBundle,
    SEC_UINT32 uiEncodedLength,
    SEC_UINT32* puiDecodedLength);

/**
* @defgroup SEC_PKI_GetCertsFromCertBundle
* @ingroup CertBundle_Functions
* @par Prototype
* @code
* SEC_List_S * SEC_PKI_GetCertsFromCertBundle(
*                                 SEC_PKI_CERT_BUNDLE_S* pstCertBundle);
* @endcode
* 
* @par Purpose
* This is used get all the certificates from the certificate bundle.
* 
* @par Description
* SEC_PKI_GetCertsFromCertBundle extracts all the certificates from the 
* certificate bundle
* 
* @param[in] pstCertBundle Pointer to SEC_PKI_CERT_BUNDLE_S. [NA/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval SEC_List_S* List of the certificates in case of success [NA|NA]
* @retval SEC_NULL In case of failure. [NULL|NA]
* @par Note
* \n
* Output contains the List of X509_CERT_S* elements
* @par Memory Handling
* \n
* ipsi will allocate the memory for the ouput structure and all the elements
* inside the list, to free this list user should call the SEC_LIST_FREE with 
* X509_freeCert as free function
*/
PSELINKDLL SEC_List_S * SEC_PKI_GetCertsFromCertBundle(
                                  SEC_PKI_CERT_BUNDLE_S *pstBundle);

/**
* @defgroup SEC_PKI_GetCrlsFromCertBundle
* @ingroup CertBundle_Functions
* @par Prototype
* @code
* SEC_List_S * SEC_PKI_GetCrlsFromCertBundle(
*                                 SEC_PKI_CERT_BUNDLE_S* pstCertBundle);
* @endcode
* 
* @par Purpose
* This is used get all the crls from the certificate bundle.
* 
* @par Description
* SEC_PKI_GetCrlsFromCertBundle extracts all the crls from the 
* certificate bundle
* 
* @param[in] pstCertBundle Certificate Bundle. [NA/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval SEC_List_S* List of the crls in case of success [NA|NA]
* @retval SEC_NULL In case of failure. [NULL|NA]
* @par Note
* \n
* Output contains the List of X509_CRL_S* elements
* @par Memory Handling
* \n
* ipsi will allocate the memory for the ouput structure and all the elements
* inside the list, to free this list user should call the SEC_LIST_FREE with 
* X509CRL_free as free function
*/
PSELINKDLL SEC_List_S * SEC_PKI_GetCrlsFromCertBundle(
                      SEC_PKI_CERT_BUNDLE_S *pstBundle);


#ifdef  __cplusplus
}
#endif

#endif //__SEC_PKI_CERT_BUNDLE_H__

#endif // __IPSI_SEC_NO_CERT_BUNDLE__
#endif // IPSI_SEC_NO_PKI

