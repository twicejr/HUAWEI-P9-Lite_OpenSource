/***************************************************************************
Copyright (C), 2004, Huawei Tech. Co., Ltd.
FileName: sec_pki_object.h
Version: 1
Author:
Creation Date:
Description: This file contains the identified functions of PKI Object.
Function List:

History: 
<author>   <date>          <desc>

***************************************************************************/
#include "ipsi_pse_build_conf.h"

#ifndef IPSI_SEC_NO_PKI

#ifndef __SEC_PKI_OBJECT_H__
#define __SEC_PKI_OBJECT_H__

#include "ipsi_types.h"
#include "sec_pki_buildconf.h"
#include "sec_sys.h"
#include "sec_list.h"
#include "sec_crypto.h"
#include "x509_basictypes.h"
#include "sec_pki_def.h"
#include "x509v3_extn.h"

#ifdef  __cplusplus
extern "C" {
#endif

/**
* @defgroup PKI
* This section contains all the enums, structures, and functions in the PKI 
* library.
*/

/**
* @defgroup Object_Functions
* @ingroup PKI
* This contains all the identified Object functions of PKI library.
*/

/**
* @defgroup SEC_PKI_objNew
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_PKI_OBJ_S* SEC_PKI_objNew( SEC_PKI_CTX_S *pstContext);
* @endcode
*
* @par Purpose
* This function is used to create a new PKI object.
*
* @par Description
* SEC_PKI_objNew function is used to create the new PKI object. This 
* function extracts the configuration parameters from the PKI context which is 
* passed as a input parameter. Object creation depends on context and if context
* is null it is a failure condition. While creating, the object inherits 
* the local store,preshared peer certificate store, verify parameters 
* and options from the context.
*
* @param[in] pstContext Pointer to SEC_PKI_OBJ_S.[NA/NA]
*
* @retval SEC_PKI_OBJ_S* On successful execution. [New%object|NA]
* @retval SEC_PKI_OBJ_S* On failure conditions. [NULL|NA]

* @par Memory Handling
* \n
* ipsi will allocate memory for SEC_PKI_OBJ_S,
* to free this memory user has to call the SEC_PKI_OBJfree function.
*/
PSELINKDLL SEC_PKI_OBJ_S* SEC_PKI_objNew (SEC_PKI_CTX_S 
                  *pstContext);




/**
* @defgroup SEC_PKI_objSyncWithContext
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objSyncWithContext(SEC_PKI_OBJ_S *pstObject,
                                   SEC_UINT uiSyncType);
* @endcode
*
* @par Purpose
* This function is used to synchronize the parameter specified in the input
* from corresponding context to object.
*
* @par Description
* SEC_PKI_objSyncWithContext function is used to synchronize the parameter
* specified in the input from corresponding context to object.
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[in] uiSyncType Specifies the types of synchronization that can be 
* done.
* Types of synchronizations are:
*	- SEC_PKI_DFLT_LOCAL_CERT - used to synchronize default cert
*	- SEC_PKI_VERIFY_PARAM - used to synchronize verify parameters
*	- SEC_PKI_ALL_LOCAL_CERT - used to synchronize local cert
*	- SEC_PKI_DFLT_PRE_SHARED_CERT - used to synchronize 
* default pre-shared cert
*	- SEC_PKI_ALL_PRE_SHARED_CERT - used to synchronize 
* synchronizing all pre-shared cert
* [1-31/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions [SEC_PKI_ERROR|NA]
*
* @par Note 
* \n
*	- SEC_PKI_SYNC_TYPE_E specifies the parameters that can
* be provided in the input for uiSyncType.
*	- During a PKI object creation the certificates and parameters are shared
* from context. After object creation it can override the certificates 
* and parameters by loading new certificates or setting the verification 
* parameters again. Any new certificates loaded in the context are not 
* shared to object after creation of the object.
*
*/
PSELINKDLL SEC_INT SEC_PKI_objSyncWithContext(SEC_PKI_OBJ_S *pstObject,
                                   SEC_UINT uiSyncType);


/**
* @defgroup SEC_PKI_objFree
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_VOID SEC_PKI_objFree( SEC_PKI_OBJ_S *pstPKIObj);
* @endcode
*
* @par Purpose
* This function is used to free PKI object.
*
* @par Description
* SEC_PKI_objFree function is used to free an PKI object.
*
* @param[in] pstPKIObj Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_VOID This function does not return any value.[NA|NA]
*
*/
PSELINKDLL SEC_VOID SEC_PKI_objFree(SEC_PKI_OBJ_S *pstPKIObj);

/**
* @defgroup SEC_PKI_objSetName
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objSetName( SEC_PKI_OBJ_S *pstObject,
*                       SEC_CHAR *pcName,SEC_UINT ilen);
* @endcode
*
* @par Purpose
* This function is used to set the name for the object.
*
* @par Description
* SEC_PKI_objSetName function is used to set the name for the object.
* If the input name is NULL terminated then, user should pass the 
* length of the name including the NULL character.
*
* @param[in,out] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[in] pcName  The name for pstObject.[NA/NA]
* @param[in] ilen Length of the name. Length can not be more than 
* NAME_MAXLEN (256).[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions [SEC_PKI_ERROR|NA]
*
*/
PSELINKDLL SEC_INT SEC_PKI_objSetName(SEC_PKI_OBJ_S *pstObject,
                       SEC_CHAR *pcName,SEC_UINT ilen);

/**
* @defgroup SEC_PKI_objGetName
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objGetName( SEC_PKI_OBJ_S *pstObject,
*                       SEC_CHAR *pcName,SEC_UINT ilen,
*                       SEC_UINT* pinamelen);
* @endcode
* @par Purpose
* This function is used to get the name of the object.
*
* @par Description
* SEC_PKI_objGetName function is used to get the name associated with the
* object.
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[in] ilen Length of pcName buffer.[NA/NA]
* @param[out] pinamelen Stores length of object name.[NA/NA]
* @param[out] pcName Contains the name associated with the pstObject, else
* contains NULL.[NA/NA]
*
* @retval SEC_INT On successful execution [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions [SEC_PKI_ERROR|NA]
*
* @par Memory Handling
* \n
* ipsi will allocate the memory for the pcName, to free this memory application 
* has to call "ipsi_free"
*
*/
PSELINKDLL SEC_INT SEC_PKI_objGetName(SEC_PKI_OBJ_S *pstObject,
                       SEC_CHAR *pcName,SEC_UINT ilen,
                       SEC_UINT* pinamelen);

/**
* @defgroup SEC_PKI_objLoadDfltLocalCertAndKeyFile
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objLoadDfltLocalCertAndKeyFile (
*                                             const SEC_CHAR *pcCertFile,
*                                             SEC_INT iCertFileType,
*                                             const SEC_CHAR *pcCertPasswd,
*                                             SEC_UINT uCertPwdLen,
*                                             const SEC_CHAR *pcKeyFile,
*                                             SEC_INT iKeyFileType,
*                                             const SEC_CHAR *pcKeyPasswd,
*                                             SEC_UINT uKeyPwdLen,
*                                             const SEC_CHAR *pcURL,
*                                             SEC_UINT uUrlLen);
* @endcode
*
* @par Purpose
* This function is used to load the certificate and key from the file to the 
* default certificate and key of the PKI object. 
*
* @par Description
* SEC_PKI_objLoadDfltLocalCertAndKeyFile function reads a certificate and key 
* file that contains the certificate and key in "PEM","PFX" or "DER" format, and
* adds the certificate and key to the default certificate and key of the PKI 
* object. Certificate password is an optional input but, password is 
* applicable only for PFX format, and key file password is also optional.
* To associate URL for this certificate set pcURL to the appropriate URL but it 
* is an optional input.If SEC_PKI_IGNORE_PVT_KEY_LOAD option is set in the 
* object, then only local certificate will be loaded without the privatekey.  
* Private key parameters will be completely ignored.
*
* @param[in,out] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[in] pcCertFile The name of the file from which the certificate has to 
* be loaded.[NA/NA]
* @param[in] iCertFileType Certificate file type, Mentions the cert file 
* type to be loaded.
* [SEC_PKI_FILETYPE_PFX/SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_ASN1/NA]
* @param[in] pcCertPasswd Password for the Certificate file.[NA/NA]
* @param[in] uCertPwdLen Length of the Password.[NA/NA]
* @param[in] pcKeyFile The File which contains the private key of the 
* Certificate.[NA/NA]
* @param[in] iKeyFileType Key file type, Mentions the key file type to be 
* loaded.
* [SEC_PKI_FILETYPE_PFX/SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_ASN1/NA]
* @param[in] pcKeyPasswd Password of the private key file.[NA/NA]
* @param[in] uKeyPwdLen Length of the password.[0-255/NA]
* @param[in] pcURL URL where this certificate can be downloaded.[NA/NA]
* @param[in] uUrlLen Length of the URL.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* 
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. 
* if the input is invalid (NULL pointer). Or the failure can be when file cannot
* be opened, or decoding of certificate fails. [SEC_PKI_ERROR|NA]
*
* @par Note 
* \n
*	- This function will overwrite the existing default certificate
* for the object.\n
*	- A file can contain both the certificate and key in such a case same file 
* name should be given as input to pcCertFile and pcKeyFile.\n
*	- A file should not contain more than one end entity certificate.\n
*	- Only one url is supported.
*	- Default local cert is a special kind of local cert, where 
* the default certificate is the preferred certificate.
*	- All search on local cert begins with default cert. 
*	- The terms used in PFX format are:
*		- Bag - Contains certificate / crl / key
*		- Baglist - List of bags
*		- Authsafe - List of Baglists
*		- PFX - Encoded authsafe
*		- Mac password - Used for integrity check on the encoded data 
* present in PFX.
*		- Enc password - Used for encrypting the baglist or
* the key before storing into bag. Cert can be encrypted 
* only by encrypting the baglist. But, key can be encrypted 
* by encrypting baglist or storing encrypted key in bag.
*	- In PFX format,the following type of file(s) are supported:
*		-  Same file containing both the certificate and private key 
*    whose encryption and mac passwords are same.
*		- Certificate and keyfiles are different whose mac and encryption 
*         password are also different
*		- If a file has multiple encrypted or unencrypted baglists.
* Then the first certificate from the first encrypted baglist will be taken
* for checking. If the certificate is not present in the first encrypted 
* baglist, then the API returns failure.
*		- If a file has multiple encrypted or unencrypted 
* baglists, the first private key from the first encrypted/unencrypted 
* baglist is taken.
* If the privatekey is not present in the first baglist, then 
* the privatekey is searched in the other baglists. If the 
* private key is not present in any of the baglists,
* then the API returns failure.
*	- For PFX file type, zero password length is not supported.
*	- If the file type is PFX, the PFX file should be created with encrypted
* password mode only.
*	- For the PEM file type, we will not support MIC_CLEAR mode.
*	- The supported key size ranges from 512 to 4096 bits.
*/
PSELINKDLL SEC_INT SEC_PKI_objLoadDfltLocalCertAndKeyFile (
                                             SEC_PKI_OBJ_S *pstObject,
                                             const SEC_CHAR *pcCertFile,
                                             SEC_INT iCertFileType,
                                             const SEC_CHAR *pcCertPasswd,
                                             SEC_UINT uCertPwdLen,
                                             const SEC_CHAR *pcKeyFile,
                                             SEC_INT iKeyFileType,
                                             const SEC_CHAR *pcKeyPasswd,
                                             SEC_UINT uKeyPwdLen,
                                             const SEC_CHAR *pcURL,
                                             SEC_UINT uUrlLen);


/**
* @defgroup SEC_PKI_objLoadDfltLocalCertAndKeyBuffer
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objLoadDfltLocalCertAndKeyBuffer(
*                                             const SEC_CHAR *pcCertBuffer,
*                                             SEC_UINT uCertBufLen,
*                                             SEC_INT iCertType,
*                                             const SEC_CHAR *pcCertPasswd,
*                                             SEC_UINT uCertPwdLen,
*                                             const SEC_CHAR *pcKeyBuffer,
*                                             SEC_UINT uKeyBufLen,
*                                             SEC_INT iKeyType,
*                                             const SEC_CHAR *pcKeyPasswd,
*                                             SEC_UINT uKeyPwdLen,
*                                             const SEC_CHAR *pcURL,
*                                             SEC_UINT uUrlLen);
* @endcode
*
* @par Purpose
* This function is used to load the certificate and key from the file to the 
* default certificate and key of the PKI object.
*
* @par Description
* SEC_PKI_objLoadDfltLocalCertAndKeyBuffer function reads a buffer that
* contains the certificate and key in "PEM","PFX" or "DER" format, and adds the
* certificate and key to the default certificate and key of the PKI object.
* Certificate password is an optional input but, password is applicable only 
* for PFX format, and key password is also optional. To associate URL for this 
* certificate set pcURL to the appropriate URL but, it is an optional Input.
* If SEC_PKI_IGNORE_PVT_KEY_LOAD option is set in the object, then only local 
* certificate will be loaded without the privatekey. Private key parameters will
* be completely ignored.
* 
*
* @param[in,out] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[in] pcCertBuffer The buffer from which the certificate has to be 
* loaded.[NA/NA]
* @param[in] uCertBufLen Length of the certificate Buffer[NA/NA]
* @param[in] iCertFileType Certificate file type, Mentions the cert file 
* type to be loaded.
* [SEC_PKI_FILETYPE_PFX/SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_ASN1/NA]
* @param[in] pcCertPasswd Password for the certificate file.[NA/NA]
* @param[in] uCertPwdLen Length of the Password.[0-255/NA]
* @param[in] pcKeyBuffer The buffer which contains the private key.[NA/NA]
* @param[in] uKeyBufLen Length of the private key buffer.[NA/NA]
* @param[in] iKeyType Mentions the key file type to be loaded.
* [SEC_PKI_FILETYPE_PFX/SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_ASN1/NA]
* @param[in] pcKeyPasswd Password of the private key file.[NA/NA]
* @param[in] uKeyPwdLen Length of the password.[0-255/NA]
* @param[in] pcURL URL where this certificate can be downloaded.[NA/NA]
* @param[in] uUrlLen Length of the URL.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* 
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. If the input is invalid (NULL
* pointer). [SEC_PKI_ERROR|NA]
*
* @par Note 
* \n
*	- This function will overwrite the existing default certificate 
* for the object.\n
*	- A file can contain both the certificate and key, in such a case same file 
*    name should be given as input to pcCertFile and pcKeyFile.\n
*	- A file should not contain more than one end entity certificate.\n
*	- Only one url is supported.
*	- Default local cert is a special kind of local cert, where 
*   the default certificate is the preferred certificate. All search on local 
*   cert begins with default cert.
*	- In case of buffer length, validation is done only for the value of zero.
* (Value zero is considered to be invalid). Any value other than the actual
* buffer length API behavior is undefined.
*	- The terms used in PFX format are:
*		- Bag - Contains certificate / crl / key
*		- Baglist - List of bags
*		- Authsafe - List of Baglists
*		- PFX - Encoded authsafe
*		- Mac password - Used for integrity check on the encoded data 
* present in PFX.
*		- Enc password - Used for encrypting the baglist or 
* the key before storing into bag. Cert can be encrypted 
* only by encrypting the baglist, whereas key can be encrypted 
* by encrypting baglist or storing encrypted key in bag.
*	- In PFX format,the following type of file(s) are supported:
*		-  Same file containing both the certificate and private key 
*    whose encryption and mac passwords are same.
*		- Certificate and keyfiles are different whose mac and encryption 
*         password are also different.
*		- If a file has multiple encrypted or unencrypted baglists.
* Then the first certificate from the first encrypted baglist will be taken
* for checking. If the certificate is not present in the first encrypted 
* baglist, then the API returns failure.
*		- If a file has multiple encrypted or unencrypted 
*    baglists, then the first private key from the first encrypted/unencrypted 
*    baglist is taken.
*    If the privatekey is not present in the first baglist, then 
*    the privatekey is searched in the other baglists. If the 
*    private key is not present in any of the baglists,
*    then the API returns failure.
*	- For PFX file type, zero password length is not supported.
*	- If the file type is PFX, the PFX file should be created with encrypted
*  password mode only.
*	- For the PEM file type, we will not support MIC_CLEAR mode.
*	- The supported key size ranges from 512 to 4096 bits.
*/
PSELINKDLL SEC_INT SEC_PKI_objLoadDfltLocalCertAndKeyBuffer(
                                             SEC_PKI_OBJ_S *pstObject,
                                             const SEC_CHAR *pcCertBuffer,
                                             SEC_UINT uCertBufLen,
                                             SEC_INT iCertType,
                                             const SEC_CHAR *pcCertPasswd,
                                             SEC_UINT uCertPwdLen,
                                             const SEC_CHAR *pcKeyBuffer,
                                             SEC_UINT uKeyBufLen,
                                             SEC_INT iKeyType,
                                             const SEC_CHAR *pcKeyPasswd,
                                             SEC_UINT uKeyPwdLen,
                                             const SEC_CHAR *pcURL,
                                             SEC_UINT uUrlLen);


#ifndef __SEC_PKI_NO_MULTIPLE_LOCAL_CERT__

/**
* @defgroup SEC_PKI_objLoadLocalCertAndKeyFile
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objLoadLocalCertAndKeyFile (
*                                             SEC_PKI_OBJ_S *pstObject,
                                             const SEC_CHAR *pcCertFile,
                                             SEC_INT iCertFileType,
                                             const SEC_CHAR *pcCertPasswd,
                                             SEC_UINT uCertPwdLen,
                                             const SEC_CHAR *pcKeyFile,
                                             SEC_INT iKeyFileType,
                                             const SEC_CHAR *pcKeyPasswd,
                                             SEC_UINT uKeyPwdLen,
                                             const SEC_CHAR *pcURL,
                                             SEC_UINT uUrlLen);
* @endcode
*
* @par Purpose
* This function is used to load the local certificate and key from the file
* to the local certificate and key of the PKI object. 
*
* @par Description
* SEC_PKI_objLoadLocalCertAndKeyFile function reads a certificate and key 
* file that contains the certificate and key in "PEM","PFX", or "DER" format, 
* and adds the certificate and key to the local certificate and key list of the 
*  PKI object. The local certificates are added to the local list and not 
* overridden like default certificate.
* Certificate password is an optional input but, it is 
* applicable only for PFX format, and key file password is also optional.
* To associate URL for this certificate set pcURL to the appropriate URL but it 
* is an optional input.If SEC_PKI_IGNORE_PVT_KEY_LOAD option is set in the 
* object, then only local certificate will be loaded without the privatekey.  
* Private key parameters will be completely ignored.
*
*
* @param[in,out] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[in] pcCertFile The name of the file from which the certificate has to 
* be loaded.[NA/NA]
* @param[in] iCertFileType Certificate file type, mentions the cert file 
* type to be loaded.
* [SEC_PKI_FILETYPE_PFX/SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_ASN1/NA]
* @param[in] pcCertPasswd Password for the certificate file.[NA/NA]
* @param[in] uCertPwdLen Length of the Password.[0-255/NA]
* @param[in] pcKeyFile The file which contains the private key of the 
* certificate.[NA/NA]
* @param[in] iKeyFileType Key file type, mentions the key file type to be 
* loaded.
* [SEC_PKI_FILETYPE_PFX/SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_ASN1/NA]
* @param[in] pcKeyPasswd Password of the private key file.[NA/NA]
* @param[in] uKeyPwdLen Length of the password.[0-255/NA]
* @param[in] pcURL URL where this certificate can be downloaded.[NA/NA]
* @param[in] uUrlLen Length of the URL.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* 
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions [SEC_PKI_ERROR|NA]
*
* @par Note 
* \n
*	- This will add the local certificate and key for the object.\n
*	- A file can contain both the certificate and key in such a case same file 
* name should be given as input to pcCertFile and pcKeyFile.\n
*	- A file should not contain more than one end entity certificate.\n
*	- Only one url is supported per local certificate loaded.\n
*	- The terms used in PFX format are:
*		- Bag - Contains certificate / crl / key
*		- Baglist - List of bags
*		- Authsafe - List of Baglists
*		- PFX - Encoded authsafe
*		- Mac password - Used for integrity check on the encoded data 
* present in PFX.
*		- Enc password - Used for encrypting the baglist or
* the key before storing into bag. Cert can be encrypted 
* only by encrypting the baglist. But, key can be encrypted 
* by encrypting baglist or storing encrypted key in bag.
*	- In PFX format,the following type of file(s) are supported:
*		-  Same file containing both the certificate and private key 
* whose encryption and mac passwords are same.
*		- Certificate and keyfiles are different whose mac and encryption 
* password are also different
*		- If a file has multiple encrypted or unencrypted baglists.
* Then the first certificate from the first encrypted baglist will be taken
* for checking. If the certificate is not present in the first encrypted 
* baglist, then the API returns failure.
*		- If a file has multiple encrypted or unencrypted 
* baglists, then the first private key from the first encrypted/unencrypted 
* baglist is taken.
* If the privatekey is not present in the first baglist, then 
* the privatekey is searched in the other baglists. If the 
* private key is not present in any of the baglists,
* then the API returns failure.
*	- For PFX file type, zero password length is not supported.
*	- If the file type is PFX, the PFX file should be created with encrypted
* password mode only.
*	- For the PEM file type, we will not support MIC_CLEAR mode.
*	- The supported key size ranges from 512 to 4096 bits.
*/
PSELINKDLL SEC_INT SEC_PKI_objLoadLocalCertAndKeyFile (
                                             SEC_PKI_OBJ_S *pstObject,
                                             const SEC_CHAR *pcCertFile,
                                             SEC_INT iCertFileType,
                                             const SEC_CHAR *pcCertPasswd,
                                             SEC_UINT uCertPwdLen,
                                             const SEC_CHAR *pcKeyFile,
                                             SEC_INT iKeyFileType,
                                             const SEC_CHAR *pcKeyPasswd,
                                             SEC_UINT uKeyPwdLen,
                                             const SEC_CHAR *pcURL,
                                             SEC_UINT uUrlLen);


/**
* @defgroup SEC_PKI_objLoadLocalCertAndKeyBuffer
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objLoadLocalCertAndKeyBuffer(
*                                             SEC_PKI_OBJ_S *pstObject,
*                                             const SEC_CHAR *pcCertBuffer,
*                                             SEC_UINT uCertBufLen,
*                                             SEC_INT iCertType,
*                                             const SEC_CHAR *pcCertPasswd,
*                                             SEC_UINT uCertPwdLen,
*                                             const SEC_CHAR *pcKeyBuffer,
*                                             SEC_UINT uKeyBufLen,
*                                             SEC_INT iKeyType,
*                                             const SEC_CHAR *pcKeyPasswd,
*                                             SEC_UINT uKeyPwdLen,
*                                             const SEC_CHAR *pcURL,
*                                             SEC_UINT uUrlLen);
* @endcode
*
* @par Purpose
* This function is used to load the local certificate and key from the file 
* to the local certificate and key list of the PKI object.
*
* @par Description
* SEC_PKI_objLoadLocalCertAndKeyBuffer function reads a buffer that contains 
* the certificate and key in "PEM","PFX", or "DER" format and adds the
* certificate and key to the default certificate and key of the PKI object.
* The local certificates are added to the local list and not overridden like
* default certificate.
* Certificate password is an optional input but, password is applicable only 
* for PFX format and key password is also optional. To associate URL for this 
* certificate set pcURL to the appropriate URL but, it is an optional Input.
* If SEC_PKI_IGNORE_PVT_KEY_LOAD option is set in the object, then only local 
* certificate will be loaded without the privatekey. Private key parameters will
* be completely ignored.
* 
*
* @param[in,out] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[in] pcCertBuffer The buffer from which the certificate has to be 
* loaded.[NA/NA]
* @param[in] uCertBufLen Length of the certificate Buffer.[NA/NA]
* @param[in] iCertFileType Certificate file type, mentions the cert file 
* type to be loaded.
* [SEC_PKI_FILETYPE_PFX/SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_ASN1/NA]
* @param[in] pcCertPasswd Password for the certificate file.[NA/NA]
* @param[in] uCertPwdLen Length of the Password.[0-255/NA]
* @param[in] pcKeyBuffer The buffer which contains the private key.[NA/NA]
* @param[in] uKeyBufLen Length of the private key buffer.[NA/NA]
* @param[in] iKeyType Mentions the key file type to be loaded.
* [SEC_PKI_FILETYPE_PFX/SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_ASN1/NA]
* @param[in] pcKeyPasswd Password of the private key file.[NA/NA]
* @param[in] uKeyPwdLen Length of the password.[0-255/NA]
* @param[in] pcURL URL where this certificate can be downloaded.[NA/NA]
* @param[in] uUrlLen Length of the URL.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* 
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions [SEC_PKI_ERROR|NA]
*
* @par Note 
* \n
*	- This will add the local certificate and key for the object.\n
*	- A file can contain both the certificate and key, in such a case same file 
*    name should be given as input to pcCertFile and pcKeyFile.\n
*	- A file should not contain more than one end entity certificate.\n
*	- Only one url is supported per local certificate loaded.\n
*	- In case of buffer length, validation is done only for the value of zero.
* (Value zero is considered to be invalid). If any value other than the actual
* buffer length, API behaviour is undefined.
*   - The terms used in PFX format are:
*		- Bag - Contains certificate / crl / key
*		- Baglist - List of bags
*		- Authsafe - List of Baglists
*		- PFX - Encoded authsafe
*		- Mac password - Used for integrity check on the encoded data 
* present in PFX.
*		- Enc password - Used for encrypting the baglist or 
* the key before storing into bag. Hence cert can be encrypted 
* only by encrypting the baglist. But, key can be encrypted 
* by encrypting baglist or storing encrypted key in bag.
*	- In PFX format,the following type of file(s) are supported:
*		-  Same file containing both the certificate and private key 
*    whose encryption and mac passwords are same.
*		- Certificate and keyfiles are different whose mac and encryption 
*         password are also different
*		- If a file has multiple encrypted or unencrypted baglists.
*    Then the first certificate from the first encrypted baglist will be taken
*    for checking. If the certificate is not present in the first encrypted 
*    baglist, then the API returns failure.
*		- If a file has multiple encrypted or unencrypted 
*    baglists, the first private key from the first encrypted/unencrypted 
*    baglist is taken.
*    If the privatekey is not present in the first baglist, then 
*    the privatekey is searched in the other baglists. If the 
*    private key is not present in any of the baglists,
*    then the API returns failure.
*	- For PFX file type, zero password length is not supported.
*	- If the file type is PFX, the PFX file should be created with encrypted
*  password mode only.
*	- For the PEM file type, we will not support MIC_CLEAR mode.
*	- The supported key size ranges from 512 to 4096 bits.
*/
PSELINKDLL SEC_INT SEC_PKI_objLoadLocalCertAndKeyBuffer(
                                             SEC_PKI_OBJ_S *pstObject,
                                             const SEC_CHAR *pcCertBuffer,
                                             SEC_UINT uCertBufLen,
                                             SEC_INT iCertType,
                                             const SEC_CHAR *pcCertPasswd,
                                             SEC_UINT uCertPwdLen,
                                             const SEC_CHAR *pcKeyBuffer,
                                             SEC_UINT uKeyBufLen,
                                             SEC_INT iKeyType,
                                             const SEC_CHAR *pcKeyPasswd,
                                             SEC_UINT uKeyPwdLen,
                                             const SEC_CHAR *pcURL,
                                             SEC_UINT uUrlLen);

#endif


/**
* @defgroup SEC_PKI_objSetVerifyDepth
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objSetVerifyDepth ( SEC_PKI_OBJ_S *pstObject,
*                                SEC_INT iDepth);
* @endcode
*
* @par Purpose
* This function is used to set verification depth in the object.
*
* @par Description
* SEC_PKI_objSetVerifyDepth function sets verification depth in the object,
* and the certificate validation has to be performed until this depth. 
* Verification depth [iDepth] value should be grater than or equal to 0, 
* otherwise API returns error.
*
* @param[in,out] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[in] iDepth Depth of the certificate validation.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions.[SEC_PKI_ERROR|NA]
*
* @par Note
* \n
* - Depth used in OCSP responder certifcate validation is the same depth set by
* SEC_PKI_objSetVerifyDepth
*/
PSELINKDLL SEC_INT SEC_PKI_objSetVerifyDepth (SEC_PKI_OBJ_S *pstObject,
                               SEC_INT iDepth);

/**
* @defgroup SEC_PKI_objGetVerifyDepth
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objGetVerifyDepth ( SEC_PKI_OBJ_S *pstObject,
*                                SEC_INT *piDepth);
* @endcode
*
* @par Purpose
* This function is used to get verification depth of the pstObject.
*
* @par Description
* SEC_PKI_objGetVerifyDepth function gets verification depth of the pstObject,
* and the certificate validation has to be performed until this depth. 
* If this API is called before calling the set depth then API returns error.
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[out] piDepth Depth of the certificate validation.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
* If the verification depth is not set, (Depth is not set in context 
* and object), and SEC_PKI_objValidateCertChain API is called,
* then depth value of zero will be considered.
*
*/
PSELINKDLL SEC_INT SEC_PKI_objGetVerifyDepth (SEC_PKI_OBJ_S *pstObject,
                               SEC_INT *piDepth);


/**
* @defgroup SEC_PKI_objSetVerifyParam
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objSetVerifyParam( SEC_PKI_OBJ_S *pstObject,
*                                           SEC_UINT  verifyFlags);
* @endcode
*
* @par Purpose
* This function is used to set the verify parameter in to object.
*
* @par Description
* SEC_PKI_objSetVerifyParam function sets the verify parameter into object. Each
* new flag passed is ORed with existing flags. While creation of the object it
* will copy the verify parameters set in the context to object. Calls to this
* API will not clear the previously existing flags, input flags will be ORed
* with the existing flags.
* 
* @param[in,out] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[in] verifyFlags Verify paramerter flags to be set.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
* Setting of the CRL flags and OCSP flags results in the API failure.
* 
* The following CRL flags (SEC_PKI_CHECK_CRL | SEC_PKI_CHECK_CRL_ALL 
* | SEC_PKI_CHECK_DELTA_CRL | SEC_PKI_CHECK_CRL_CROSS_CA | 
* SEC_PKI_EXTENDED_CRL_SUPPORT | SEC_PKI_OBJ_CRL_SUPPORT) conflict
* with the OCSP flags (SEC_PKI_CHECK_OCSP | SEC_PKI_CHECK_OCSP_ALL 
* | SEC_PKI_OCSP_RESPONDER_CHECK_CRL | SEC_PKI_OCSP_RESPONDER_CHECK_DELTA_CRL | 
* SEC_PKI_OCSP_TRUST_RESPONDER_CERTS_IN_MSG | SEC_PKI_OBJ_OCSP_SUPPORT)
*/
PSELINKDLL SEC_INT SEC_PKI_objSetVerifyParam(SEC_PKI_OBJ_S *pstObject,
                                           SEC_UINT  verifyFlags);


/**
* @defgroup SEC_PKI_objGetVerifyParam
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objGetVerifyParam( SEC_PKI_OBJ_S *pstObject,
*                             SEC_UINT *pVerifyFlags);
* @endcode
*
* @par Purpose
* This function is used to get the Verify Parameter set in the object.
*
* @par Description
* SEC_PKI_objGetVerifyParam function gets Verify Parameter set in the object.
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[out] pVerifyFlags Contains the verify paramerter flags.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
* If no flags are set, then the function will return an error.
*
*/
PSELINKDLL SEC_INT SEC_PKI_objGetVerifyParam(SEC_PKI_OBJ_S *pstObject,
                             SEC_UINT *pVerifyFlags);


/**
* @defgroup SEC_PKI_objClearVerifyParam
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objClearVerifyParam( SEC_PKI_OBJ_S *pstObject,
*                                          SEC_UINT  verifyFlags);
* @endcode
*
* @par Purpose
* This function is used to clear the verify parameter set in the object.
*
* @par Description
* SEC_PKI_objClearVerifyParam function clears the verify parameter set in
* the object.
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[in] verifyFlags Verify paramerter flags to be reset.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
*/
PSELINKDLL SEC_INT SEC_PKI_objClearVerifyParam(SEC_PKI_OBJ_S *pstObject,
                                           SEC_UINT  verifyFlags);


/**
* @defgroup SEC_PKI_objSetTime
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objSetTime( SEC_PKI_OBJ_S *pstObject,
*                       const DATETIME_S * pstTime);
* @endcode
*
* @par Purpose
* This function is used to set time in the Object.
*
* @par Description
* SEC_PKI_objSetTime function sets the time to the Object. This time is used for
* checking the certificate and CRL validity period.
*
* @param[in,out] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[in] pstTime Time to be set.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
*	- The ucUTCSign, ucUTCHour, ucUTCMinute and uwMillSecond fields of 
* DATETIME_S
* structure will not be used by our functionality and hence these fields
* are not considered and validated.
* \n
*	- On windows the input time is considered valid, if it can be converted to a
* calendar value using mktime.
* \n
*	- Dopra's value of uwYear field in DATETIME_S structure can 
* be in the range from 1970 to 2134.
*  - Time used in OCSP responder certifcate validation is the same time set by
* SEC_PKI_objSetTime
*
*/
PSELINKDLL SEC_INT SEC_PKI_objSetTime(SEC_PKI_OBJ_S *pstObject,
                       const DATETIME_S * pstTime);

/**
* @defgroup SEC_PKI_objGetTime
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objGetTime( SEC_PKI_OBJ_S *pstObject,
*                DATETIME_S **dpstTime);
* @endcode
*
* @par Purpose
* This function is used to get the time set in the object.
*
* @par Description
* SEC_PKI_objGetTime function gets the time set in the object,
* this time is used for checking the Certificate/CRL validity period.
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param [out] dpstTime Contains the time set in the object.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
*	- This function internally allocates memory for the time structure.\n
*	- The memory allocated can be freed using ipsi_free function.
* \n
*	- If time is not set, then the function will return an error.
* \n
*	- The ucUTCSign, ucUTCHour, ucUTCMinute and uwMillSecond fields of 
* DATETIME_S
* structure are not used by our functionality and hence whatever time has been
* set will be provided as the output, without giving any importance to check
* if these fields are valid.
*
*/
PSELINKDLL SEC_INT SEC_PKI_objGetTime(
                SEC_PKI_OBJ_S *pstObject,
                DATETIME_S **dpstTime);

/**
* @defgroup SEC_PKI_objGetVerifyResult
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objGetVerifyResult( const SEC_PKI_OBJ_S *pstObject);
* @endcode
*
* @par Purpose
* This function is used to get the verification results.
*
* @par Description
* SEC_PKI_objGetVerifyResult function returns the certificate chain validation
* result before calling this API validation of the cert chain 
* must have done by using the SEC_PKI_objValidateCertChain API.
*
 
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT previous validation was successful [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT Previous validation was failure (due to internal error)
* [SEC_PKI_ERROR|NA]
* @retval SEC_INT On all failure conditions related to certificate 
* validation. [NA]
*
*/
PSELINKDLL SEC_INT SEC_PKI_objGetVerifyResult(SEC_PKI_OBJ_S *pstObject);



/**
* @defgroup SEC_PKI_objGetCtxCACertReq
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objGetCtxCACertReq( SEC_PKI_OBJ_S *pstObject,
*                            SEC_PKI_PARAMETER_E enId,
*                            SEC_List_S **dpOutList);
* @endcode
*
* @par Purpose
* This function is used to get the list of hash, 
* encoded subject name, or certificates,
* of CA's from CA request list using the object pointer.
*
* @par Description
* SEC_PKI_objGetCtxCACertReq function gets the CA Certificate(s) or CA 
* Certificate(s) information (hash of the public key info/encoded
* subject name) based on the input parameter type enId, and provide
* the required output list in dpOutList.
* The requested data will be extracted from the trust store of CA certs
* which are indicated to be part of cert request list while loading of 
* the CA certificate(S).
* 
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[in] enId parameter type 
* [SEC_PKI_CAPUBLICKEY/SEC_PKI_CASUBJECT/SEC_PKI_CACERT/NA]
* @param[out] dpOutList List which contains output list. 
*	- If the SEC_PKI_PARAMETER_E is SEC_PKI_CAPUBLICKEY or
* SEC_PKI_CASUBJECT then the dpOutList contains the elements 
* of type SEC_PKI_DATA_BUF_S.\n
*	- If the SEC_PKI_PARAMETER_E is SEC_PKI_CACERT
* then the dpOutList contains the elements of type X509_CERT_S.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions [SEC_PKI_ERROR|NA]
*
* @par Memory Handling
*\n
* This function will allocate the memory for dpOutList (the list may
* contain one or more entries), to free this memory application has to
* call SEC_LIST_FREE, with the free function as SEC_PKI_freeDataBuf.\n
* If the SEC_PKI_PARAMETER_E is SEC_PKI_CAPUBLICKEY or SEC_PKI_CASUBJECT
* else with the free function X509_freeCert if the SEC_PKI_PARAMETER_E is
* SEC_PKI_CACERT.
*
* @par Note
* \n
*	- Output Subject Name will be provided in encoded DER format.
*	- Output hash will be of type SHA1.
*
*/
PSELINKDLL SEC_INT SEC_PKI_objGetCtxCACertReq(SEC_PKI_OBJ_S *pstObject,
                            SEC_PKI_PARAMETER_E enId,
                            SEC_List_S **dpOutList);


/**
* @defgroup SEC_PKI_objGetDfltLocalCert
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objGetDfltLocalCert( SEC_PKI_OBJ_S *pstObject,
*                               X509_CERT_S  **pstCert);
* @endcode
*
* @par Purpose
* This function is used to get the default local cert.
*
* @par Description
* SEC_PKI_objGetDfltLocalCert function gets the default local cert associated
* with the object. If the default local cert is not loaded before calling this 
* API then the output pstCert contains NULL.
* 
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[out] pstCert Contains the default local cert associated with the
* context. pstCert Contains NULL if default cert is not 
* loaded to context.[NA/NA]
*
* @retval SEC_INT On successful execution [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions [SEC_PKI_ERROR|NA]
*
* @par Memory Handling
* \n
* ipsi will allocate the memory for the pstCert, to free this memory 
* application has to call the "X509_freeCert".
*
*/
PSELINKDLL SEC_INT SEC_PKI_objGetDfltLocalCert(SEC_PKI_OBJ_S *pstObject,
                               X509_CERT_S  **pstCert);


/**
* @defgroup SEC_PKI_objGetAllLocalCert
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objGetAllLocalCert( SEC_PKI_OBJ_S *pstObject,
*                                SEC_List_S **dpOutCertList);
* @endcode
*
* @par Purpose
* This function is used to get all Certificates from local store 
* of the passed object.
*
* @par Description
* SEC_PKI_objGetAllLocalCert function gets all Certificates from local store, 
* the default local certificate is also included in the output list.
*
* 
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA] 
* @param[out] dpOutCertList List which contains all the certs.
* dpOutCertList is a list which holds elements of type X509_CERT_S.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Memory Handling
* On success this function will allocate the memory for the dpOutCertList
* (the list may contain one or more entries), to free this memory 
* application has to call SEC_LIST_FREE, with the free function as
* X509_freeCert.
*
* @par Note
* \n
* The dpOutCertList contains only the certificates stored in the local store.
* If the multiple local certificates is tailored to be not supported,then it 
* will give a list containing only default certificate.
*/
PSELINKDLL SEC_INT SEC_PKI_objGetAllLocalCert(SEC_PKI_OBJ_S *pstObject,
                               SEC_List_S **dpOutCertList);

/**
* @defgroup SEC_PKI_objGetAllLocalCertChain
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objGetAllLocalCertChain( SEC_PKI_OBJ_S *pstObject,
                                    SEC_List_S **dpOutCertChainList);
* @endcode
*
* @par Purpose
* This function is used to get the list of certificate chains for all
* the certificates stored in the local store of the object.
*
* @par Description
* SEC_PKI_objGetAllLocalCertChain function gets the certificate chain for all
* local certificates which are in local store. First it will get all the local
* certificates and forms the chain for each of these local certificates with
* the help of certificates stored in trust store and returns this list
* [multiple chain list] to the user. Default local is also included.
* 
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA] 
* @param[out] dpOutCertChainList Output list of local certificate chains.
* dpOutCertChainList is a list which holds elements of type SEC_List_S which
* in turn holds elements of type X509_CERT_S.[NA/NA]
*
* @retval SEC_INT On successful execution [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions [SEC_PKI_ERROR|NA]

* @par Memory Handling
* \n
* On success function will allocate the memory for the dpOutCertChainList
* (the list may contain one or more entries), to free this memory application
* has to call SEC_PKI_freeCertChainList function.
* 
* @par Note
* \n
*	- The first element in each and every certificate chain is the
* local certificate.
*	- Possible certificate chain that can be built for the local certificate
* using the trust store will only be considered. 
*	- If the issuer certificate or local certificate is not found in the 
* trust store, then the local certificate will be considered in the chain. 
* Hence the chain obtained in the output for the local certificate can be
* incomplete.
*	- Only basic validation is done to construct the certificate chain.
* 
*/
PSELINKDLL SEC_INT SEC_PKI_objGetAllLocalCertChain(SEC_PKI_OBJ_S *pstObject,
                                    SEC_List_S **dpOutCertChainList);


/**
* @defgroup SEC_PKI_objGetLocalCertChainByCert
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objGetLocalCertChainByCert ( SEC_PKI_OBJ_S *pstObject,
*                                         X509_CERT_S *pstCert,
*                                         SEC_List_S **dpOutCertChain);
* @endcode
*
* @par Purpose
* This function is used to get cert Chain from the trust store for the 
* input certificate
*
* @par Description
* SEC_PKI_objGetLocalCertChainByCert function forms the certificate
* chain from the trust store for the input cert and corresponding chain
* will be returned in output list.
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA] 
* @param[in] pstCert Input certificate.[NA/NA]
* @param[out] dpOutCertChain Output certificate chain.
* dpOutCertChain is a list which holds elements of type X509_CERT_S.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Memory Handling
* \n
* On success this function will allocate the memory for the dpOutCertChain
* (the list may contain one or more entries) to free this memory 
* application has to call SEC_LIST_FREE, with the free function as
* X509_freeCert.
*
* @par Note
* \n
*	- The first element in the output certificate chain is the
* input certificate.
* \n
*	- Possible certificate chain that can be built for the input certificate
* using the trust store will only be considered, if the issuer certificate
* for input certificate is not found in the trust store, then only input
* certificate will be considered in the output chain. Hence the chain
* obtained in the output for the input certificate, can be incomplete.
* \n
*	- No check is done to check whether the input certificate is present in
* local store.
* \n
*	- Only basic validation is done to construct the certificate chain.
*/
PSELINKDLL SEC_INT SEC_PKI_objGetLocalCertChainByCert (
                                        SEC_PKI_OBJ_S *pstObject,
                                        X509_CERT_S *pstCert,
                                        SEC_List_S **dpOutCertChain);

/**
* @defgroup SEC_PKI_objGetAllCertChainByCAPubKeyHash
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objGetAllCertChainByCAPubKeyHash (
*                                              SEC_PKI_OBJ_S *pstObject,
*                                              SEC_UINT uAlgType,
*                                              SEC_CHAR *pcHash,
*                                              SEC_UINT ulen,
*                                              SEC_List_S **pOutCertList);
* @endcode
*
* @par Purpose
* This function is used to build the single or multiple cert chain and returns 
* the chain to the user.
*
* @par Description
* SEC_PKI_objGetAllCertChainByCAPubKeyHash function 
* builds the chain dynamically with respect to hash of the CA public key and 
* return the list. If it fails to build the chain then the pOutCertList 
* contains NULL.
*
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[in] uAlgType Hash Algorithm, SHA1(SEC_ALG_SHA1) is the supported 
* algorithm. [NA/NA]
* @param[in] pcHash Hash of the CA public key to match.[NA/NA]
* @param[in] ulen Length of the hash.[NA/NA]
* @param[out] pOutCertList List of certificate chains.
* pOutCertList is a list which holds elements of type SEC_List_S which
* in turn holds elements of type X509_CERT_S.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Memory Handling
* \n
* On success function will allocate the memory for the pOutCertList
* (the list may contain one or more entries), to free this memory, application
* has to call SEC_PKI_freeCertChainList function.
* @par Note
* \n
*	- If there are multiple end entity certificates signed by the same CA then 
* their is possibility of multiple chain returning the multiple
* chain.\n
*	- Chain building is done by considering subject name and issuer name .AKID
*  and SKID will be considered, if present.\n
* Example: TrustStore contains->ca-ca1-ca2, where ca has issued ca1 and ca1 has 
* issued ca2, local certificate contains->e1,e2 which have been issued by ca2.
* If the pcHash is the hash of the "ca" then the output contains two 
* list e1-ca2-ca1 and e2-ca2-ca1
*	- The certificate corresponding to public key info hash should be present
* in the trust store.
*/
PSELINKDLL SEC_INT SEC_PKI_objGetAllCertChainByCAPubKeyHash (
                                              SEC_PKI_OBJ_S *pstObject,
                                              SEC_UINT uAlgType,
                                              SEC_CHAR *pcHash,
                                              SEC_UINT ulen,
                                              SEC_List_S **pOutCertList);

/**
* @defgroup SEC_PKI_objGetAllCertChainByCASubName
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objGetAllCertChainByCASubName (
*                                           SEC_PKI_OBJ_S *pstObject,
*                                           SEC_CHAR *pcSubName,
*                                           SEC_UINT len,
*                                           SEC_List_S **pOutCertList);
* @endcode
*
* @par Purpose
* This function is used to build the single or multiple cert chain 
* and returns the chain to the user.
*
* @par Description
* SEC_PKI_objGetAllCertChainByCASubName function builds the chain dynamically
* with respect to subject name of the CA and return the list. If it fails to 
* build the chain then the pOutCertList contains the NULL.
*
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[in] pcSubName Subject name of the CA, The name passed is expected to
* be in DER encoded format [NA/NA]
* @param[in] ulen Length of the Subject name.[NA/NA]
* @param[out] pOutCertList List of certificate chains.
* pOutCertList is a list which holds elements of type SEC_List_S which
* in turn holds elements of type X509_CERT_S.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions [SEC_PKI_ERROR|NA]
*
* @par Memory Handling
* \n
* On success function will allocate the memory for the pOutCertList
* (the list may contain one or more entries), to free this memory application
* has to call SEC_PKI_freeCertChainList function.
*
* @par Note
* \n
*	- If there are multiple end entity certificates signed by the same CA then 
* their is possibility of multiple chain returning the multiple
* chain.\n
*	- Chain building is done by considering subject name and issuer name. AKID 
* and SKID will be considered if present.\n
*	- Example: trustStore contains-> ca-ca1-ca2, where ca has issued ca1 
* and ca1 has issued ca2, local certificate contains-> e1, e2 which have
* been issued by ca2. if the pcSubName is subject name of the "ca" 
* then the output contains two list e1-ca2-ca1 and e2-ca2-ca1.
*	- The certificate corresponding to subject name may or may not be present
* in the trust store.
*/
PSELINKDLL SEC_INT SEC_PKI_objGetAllCertChainByCASubName (
                                           SEC_PKI_OBJ_S *pstObject,
                                           SEC_CHAR *pcSubName,
                                           SEC_UINT len,
                                           SEC_List_S **pOutCertList);


/**
* @defgroup SEC_PKI_objGetPvtKeyByCert
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objGetPvtKeyByCert( SEC_PKI_OBJ_S *pstObject,
*                                 X509_CERT_S *pstCert,
*                                 SEC_PKEY_S **pstPvtKey);
* @endcode
*
* @par Purpose
* This function is used to get private key corresponding to the input
* certificate.
*
* @par Description
* SEC_PKI_objGetPvtKeyByCert function gets private key corresponding to the 
* input certificate from the local store.
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[in] X509_CERT_S Input certificate.[NA/NA]
* @param[out] pstPvtKey Private key associated with the 
* input certificate.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Memory Handling
* \n
* ipsi will allocate the memory for the pstPvtKey, to free this memory
* application has to call the "CRYPT_PKEY_free".
*
*/
PSELINKDLL SEC_INT SEC_PKI_objGetPvtKeyByCert (SEC_PKI_OBJ_S *pstObject,
                                X509_CERT_S *pstCert,
                                SEC_PKEY_S **pstPvtKey);




/**
* @defgroup SEC_PKI_objValidateCertChain
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objValidateCertChain ( SEC_PKI_OBJ_S *pstObject,
*                                SEC_List_S *pCertList,
*                                SEC_UINT verifyType);
* @endcode
*
* @par Purpose
* This function is used to validate the input cert chain based on the verify
* type. 
*
* @par Description
* SEC_PKI_validateCertChain function validates the input certificate or Cert
* chain based on the verify type "verifyType" passed as input, if the
* "verifyType" is 0 then it will use the verify type which is previously set (in
* object or in context). If the validation is successful and if the cert chain 
* is not present in the peer cache store, it will be added to peer cache.
* And also it will be updated to the peer cache of the context. The peer cache 
* list default size is 10, which can be changed using the API 
* SEC_PKI_ctxResizePeerCache
*
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[in] pCertList Input cert chain to be validated.
* pCertList is a list which holds elements of type X509_CERT_S[NA/NA]
* @param[in] verifyType Type of validation[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
*	- This API will only verify the first end entity cert even there are 
*    multiple end entity cert in the pCertList.\n
*	- The input to this API is one entity certificate with chain 
*    or a single end entity cert.\n
*	- If the verify type passed is 0 then this will use the verification type
*    set in the object.
*	- Use the System Time only if the verifyType passed doesn't contain 
*    SEC_PKI_CHECK_TIME in it.
*	- If the verifyType passed or set through API is SEC_PKI_CHECK_TIME, 
*    use the time in Verify Param Structure of Object 
*    whether it is set by user or not.
*	- If the verify type is passed as SEC_PKI_CHECK_CRL_ALL,
*   then CRL checking will not happen because SEC_PKI_CHECK_CRL
*   flag should also be set.
*	- If the verify type is set as SEC_PKI_CHECK_CROSS_CA, then cross
*   CA certificates will be considered while building the certificate path.
*	- If the verify type is passed as
*   SEC_PKI_CHECK_CROSS_CA|SEC_PKI_CHECK_CRL_CROSS_CA,
*   then CRL checking will not happen because SEC_PKI_CHECK_CRL
*   flag should also be set.
*   SEC_PKI_CHECK_CRL flag has to be set to check the CRL for the first
*   certificate within the input list.
*	- SEC_PKI_CHECK_CRL|SEC_PKI_CHECK_CRL_ALL
*   to check CRL for all certificates.
*       SEC_PKI_CHECK_CROSS_CA| SEC_PKI_CHECK_CRL 
*   |SEC_PKI_CHECK_CRL_CROSS_CA to check CRL for the first
*   certificate within the input list and to check CRL for the cross CA
*   certificate.
*	- (SEC_PKI_CHECK_CRL | SEC_PKI_CHECK_DELTA_CRL) to check delta CRL
*   for the CRL.
*	- (SEC_PKI_CHECK_CRL | SEC_PKI_EXTENDED_CRL_SUPPORT) to support
*   extended CRL support i,e to support reason codes or indirect CRLs.
*	- For all CRL processing, SEC_PKI_CHECK_CRL type has to be set.
*   - If SEC_PKI_OBJ_CRL_SUPPORT type is set, then the object inband CRLs
*   will be given first priority for all CRL processing.
*   - SEC_PKI_CHECK_OCSP has to be set to check the OCSP status for the
*   first certificate within the input list.
*	- SEC_PKI_CHECK_OCSP|SEC_PKI_CHECK_OCSP_ALL
*   to check OCSP status for all certificates in the input list.
*   - If SEC_PKI_OBJ_OCSP_SUPPORT flag is set along with SEC_PKI_CHECK_OCSP, 
*   then the object inband OCSP status will be given first priority 
*   for all OCSP status processing.
*   - SEC_PKI_OCSP_RESPONDER_CHECK_CRL flag has to be set along with 
*   SEC_PKI_CHECK_OCSP, to check the CRL for the OCSP responder certificate.
*   - SEC_PKI_OCSP_RESPONDER_CHECK_DELTA_CRL flag has to be set along with 
*   (SEC_PKI_CHECK_OCSP | SEC_PKI_OCSP_RESPONDER_CHECK_CRL), to check 
*   delta CRL for the CRL.
*   - SEC_PKI_OCSP_TRUST_RESPONDER_CERTS_IN_MSG flag has to be set along with 
*   SEC_PKI_CHECK_OCSP, to enable to use the OCSP responder certificate
*   available in the message.
*   - Passing any of CRL flags combined with OCSP flags results in API failure.
*   - The producedAt field of OCSP response will not get processed
*     during OCSP response validation.
*	- SEC_PKI_objSetVerifyDepth should be called for setting depth
*   otherwise the depth value of zero will be considered.
*	- Once SEC_PKI_objValidateCertChain successful,
*   first cert from the list(pCertList) will be stored as 
*   peer cert in use.
*	- If SEC_PKI_objValidateCertChain fails,peer cert in use
*   should not be overwritten.
*
* @par Related Topics
* SEC_PKI_ctxResizePeerCache\n
* SEC_PKI_ctxGetPeerCacheSize\n
* SEC_PKI_objGetPeerCertInUse\n
* SEC_PKI_objGetCtxPeerCertByHash
*/
PSELINKDLL SEC_INT SEC_PKI_objValidateCertChain (SEC_PKI_OBJ_S *pstObject,
                                  SEC_List_S *pCertList,
                                  SEC_UINT verifyType);

#ifndef __SEC_PKI_NO_PEER_CACHE__

/**
* @defgroup SEC_PKI_objGetPeerCertInUse
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objGetPeerCertInUse ( SEC_PKI_OBJ_S *pstObject,
*                                   X509_CERT_S **pstCert);
* @endcode
* @par Purpose
* This function is used to get the peer certificate which is currently in use.
*
* @par Description
* SEC_PKI_objGetPeerCertInUse function gets the peer certificate which is 
* currently in use. After successful validation of the peer cert chain the end
* entity certificate is extracted and it is set as the peer certificate in use 
* internally. The same certificate will be returned by this API.
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[out] pstCert The Peer certificate which is currently in use.[NA/NA]
*
* @retval SEC_INT If any unknown error occurs which cannot be handled by 
* user. [SEC_PKI_ERROR|NA]
* @retval SEC_INT On successful execution. [SEC_PKI_ERROR|NA]
* @par Note
* \n
* Memory for pstCert will be allocated inside the library and
* needs to be freed by X509_freeCert.
*/
PSELINKDLL SEC_INT SEC_PKI_objGetPeerCertInUse (SEC_PKI_OBJ_S *pstObject,
                                  X509_CERT_S **pstCert);

#endif

/**
* @defgroup SEC_PKI_verifyResultDescString
* @ingroup Object_Functions
* @par Prototype
* @code
* const SEC_CHAR *SEC_PKI_verifyResultDescString(
* SEC_INT32 iValue);
* @endcode
* @par Purpose
* This is used to get message strings about certificate verification result.
*
* @par Description
* SEC_PKI_verifyResultDescString function gets 
* message strings about certificate verification result.
*
* @param[in] iValue Certificate verification result value [NA/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval SEC_CHAR* Returns the message strings about 
* certificate verification result [certificate validation result|NA]
* @retval SEC_CHAR* If input is invalid. [error number iValue|NA]
*/
PSELINKDLL const SEC_CHAR *SEC_PKI_verifyResultDescString(
SEC_INT32 iValue);





/**
* @defgroup SEC_PKI_setCAKeyUsageMandatoryCheck
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_VOID SEC_PKI_setCAKeyUsageMandatoryCheck(
* SEC_INT iEnable);
* @endcode
*
* @par Purpose
* This is used to set or reset the mandatory key usage extension checking.
*
* @par Description
* SEC_PKI__setCAKeyUsageMandatoryCheck function sets or resets
* the mandatory key usage extension checking for a CA certificate.
*
* @param[in] iEnable 1 is passed to enable the check and 
* 0 to disable the check. [0-1/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval SEC_VOID This function does not return any value. [NA|NA]
*
*/
PSELINKDLL SEC_VOID SEC_PKI_setCAKeyUsageMandatoryCheck(
SEC_INT iEnable);

/**
* @defgroup SEC_PKI_setKeyUsageCheck
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_VOID  SEC_PKI_setKeyUsageCheck( SEC_INT iEnable);
* @endcode
* 
* @par Purpose
* This is used to set or reset the Key Usage extension check.
* 
* @par Description
* SEC_PKI_setKeyUsageCheck function sets or resets 
* the key usage extension checking for a certificate.
* 
* @param[in] iEnable 1 is passed to enable the check and 0 to disable the check
* [0-1/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval SEC_VOID This function does not return any value. [NA|NA]
* 
* @par Note
* \n
* If the checking is enabled, then the key usage extension will be checked.
* If this extension is present in the
* certificate. The setting is global to PKI for that application.
* The default is disabled.
*
* @par Related Topics
* SEC_PKI_setCAKeyUsageMandatoryCheck
*/


PSELINKDLL SEC_VOID  SEC_PKI_setKeyUsageCheck(SEC_INT iEnable);


/**
* @defgroup SEC_PKI_objSetVerify
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objSetVerify( SEC_PKI_OBJ_S *pstObject, 
*                            SEC_INT (*pfCallback) (SEC_INT iVerifyResult,
*                            SEC_VOID *pstStoreCtx,SEC_VOID *pAppData));
* @endcode
* 
* @par Purpose
* This is used to set the callback function to the PKI object.
* 
* @par Description
* SEC_PKI_objSetVerify function sets the error verify callback 
* function Pointer to SEC_PKI_OBJ_S.

* @param[in,out] pstObject Pointer to SEC_PKI_OBJ_S in which 
* pfVerify_cb fields are set. [NA/NA]
* @param[in] pfCallback Function pointer callback 
* to verify the certificates and crls 
* during verification of certificate chain. [NA/NA]
* @param[in] pAppData void pointer contains application data. [NA/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval SEC_INT On success. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT If the input is invalid 
* (NULL Pointer is passed). [SEC_PKI_ERROR|NA]
* @par Note
* \n
* pfCallback - callback function takes 3 arguments
* iVerifyResult result of certificate validation 
* iVerifyResult can have following values when callback function is called
* SEC_PKI_CB_ERROR if any error occurs during certificate validation.
* SEC_PKI_CB_SUCCESS if individual certificate validation is successful.
* pstStoreCtx void pointer contains information of store context.
* pAppData void pointer which contains application data.
*	- In the call back function (pfCallback) use the following PKI functions:\n
*		- SEC_PKI_X509_storeCtxGetError\n
*		- SEC_PKI_X509_storeCtxGetErrorDepth\n
*		- SEC_PKI_X509_storeCtxGetCurrentCert\n
*	- call back function should return any one of the following value:
*		- SEC_PKI_CB_SUCCESS if call back function success
*		- SEC_PKI_CB_ERROR if call back function fails
*/

PSELINKDLL SEC_INT SEC_PKI_objSetVerify(SEC_PKI_OBJ_S *pstObject,
                SEC_INT (*pfCallback) (SEC_INT iVerifyResult,
                SEC_VOID *pstStoreCtx,SEC_VOID *pAppData),
                SEC_VOID *pAppData);


/**
* @defgroup SEC_PKI_X509_storeCtxGetError
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_X509_storeCtxGetError( SEC_VOID *pstStoreCtx);
* @endcode
* 
* @par Purpose
* This is used to get errors in SEC_PKI_X509_STORE_CTX_S structure.
* 
* @par Description
* SEC_PKI_X509_storeCtxGetError function can be used to get the errors 
* in case of certificates chains verification.
* Example: If it is returned X509_V_ERR_UNABLE_TO_GET_CRL_ISSUER 
* means unable to get the crl issuer and the respective error depth can 
* be obtained using the function SEC_PKI_X509_storeCtxGetError.

* @param[in] pstStoreCtx void pointer [NA/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval SEC_INT Returns the value of Error. [Error|NA]
* 
* @par Related Topics
* SEC_PKI_X509_storeCtxGetErrorDepth.
*/
PSELINKDLL SEC_INT SEC_PKI_X509_storeCtxGetError(SEC_VOID *pstStoreCtx);

/**
* @defgroup SEC_PKI_X509_storeCtxGetErrorDepth
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_X509_storeCtxGetErrorDepth( SEC_VOID *pstStoreCtx);
* @endcode
* 
* @par Purpose
* This is used to get Error Depth in the certificate chain.
* 
* @par Description
* In case of certificate chains verification this function can be 
* used to get the error depth. Error depth shows which certificate 
* in the chain as an error and the respective error 
* can be obtained using the function SEC_PKI_X509_storeCtxGetErrorDepth.
* 
* @param[in] pstStoreCtx void pointer. [NA/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval SEC_INT Returns the value of Error Depth. [Error%Depth|NA]
* @retval SEC_INT SEC_PKI_ERROR Is returned 
* if ptr passed is NULL. [SEC_PKI_ERROR|NA]
* 
*
* @par Related Topics
* SEC_PKI_X509_storeCtxGetError
*/
PSELINKDLL SEC_INT SEC_PKI_X509_storeCtxGetErrorDepth
(SEC_VOID *pstStoreCtx);

/**
* @defgroup SEC_PKI_X509_storeCtxGetCrossCaPos
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_X509_storeCtxGetCrossCaPos( SEC_VOID *pstStoreCtx);
* @endcode
* 
* @par Purpose
* This is used to get the position of cross CA in the certificate chain.
* 
* @par Description
* In case of certificate chains verification this function can be 
* used to get the position of cross CA in the certificate chain.
* If the cross CA position obtained using SEC_PKI_X509_storeCtxGetCrossCaPos
* and the error depth obtained using SEC_PKI_X509_storeCtxGetErrorDepth
* are same then the error is applicable for the cross CA formed in the chain.
* 
* @param[in] pstStoreCtx void pointer. [NA/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval SEC_INT Returns the position of cross CA. [Error%Depth|NA]
* @retval SEC_INT SEC_PKI_ERROR is returned if cross CA is not found
* in the chain formed till now or if input pointer is NULL.
* [SEC_PKI_ERROR|NA]
* 
*
* @par Related Topics
* SEC_PKI_X509_storeCtxGetErrorDepth
*/
PSELINKDLL SEC_INT SEC_PKI_X509_storeCtxGetCrossCaPos(
SEC_VOID *pstStoreCtx);


/**
* @defgroup SEC_PKI_X509_storeCtxGetCurrentCert
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_PKI_X509_CERT_EXTENDED_S *SEC_PKI_X509_storeCtxGetCurrentCert(
                    SEC_VOID *pstStoreCtx);
* @endcode
* 
* @par Purpose
* This is used to get current SEC_PKI_X509_CERT_EXTENDED_S certificate.
* 
* @par Description
* SEC_PKI_X509_storeCtxGetCurrentCert function gets the current 
* SEC_PKI_X509_CERT_EXTENDED_S certificate from pointer.
* 
* @param[in] pstStoreCtx void pointer. [NA/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval SEC_PKI_X509_CERT_EXTENDED_S* In Case of Success 
* SEC_PKI_X509_CERT_EXTENDED_S certificate is returned .
* [Pointer%to%SEC_PKI_X509_CERT_EXTENDED_S|NA]
* @retval SEC_PKI_X509_CERT_EXTENDED_S* In Case of failure,
* SEC_NULL is returned failure occurs in case of input pointer is
* SEC_NULL. [SEC_NULL|Do%not%pass%SEC_NULL]
* @par Note
* \n
* Do not manipulate anything to return pointer as it will be used in library.
*
*/
PSELINKDLL 
SEC_PKI_X509_CERT_EXTENDED_S *SEC_PKI_X509_storeCtxGetCurrentCert(
                    SEC_VOID *pstStoreCtx);


/**
* @defgroup SEC_PKI_X509_storeCtxGetCurrentBaseCRL
* @ingroup Object_Functions
* @par Prototype
* @code
* X509_CRL_S  *SEC_PKI_X509_storeCtxGetCurrentBaseCRL(SEC_VOID *pstStoreCtx);
* @endcode
* 
* @par Purpose
* This is used to get current Base CRL.
* 
* @par Description
* SEC_PKI_X509_storeCtxGetCurrentBaseCRL function gets the 
* Base CRL crosspending to certificate which is being currently validated.
* 
* @param[in] pstStoreCtx void pointer. [NA/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval X509_CRL_S* In Case of Success 
* X509_CRL_S CRL is returned .
* [Pointer%to%X509_CRL_S|NA]
* @retval X509_CRL_S* In Case of failure,
* SEC_NULL is returned failure occurs in case of input pointer is
* SEC_NULL. [SEC_NULL|Do%not%pass%SEC_NULL]
* @par Note
* \n
* Do not manipulate anything to return pointer as it will be used in library.
*
*/
PSELINKDLL
X509_CRL_S  *SEC_PKI_X509_storeCtxGetCurrentBaseCRL(SEC_VOID *pstStoreCtx);

/**
* @defgroup SEC_PKI_objSetlocalCertInUse
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objSetlocalCertInUse( SEC_PKI_OBJ_S *pstObject,
*                                    X509_CERT_S *pstCert);
* @endcode
* @par Purpose
* This function sets the pstCert as the certificate which is currently in use.
*
* @par Description
* SEC_PKI_objSetlocalCertInUse sets the input certificate as the certificate 
* in use. In some scenarios we do some operation like get all local cert 
* by same public key. In this case we do not know which is the certificate to 
* use. This can be determined after exchanging few messages with the peer 
* and this certificate can be set as the certificate in 
* use for later. So that user can avoid determining which certificate to use.
*
* @param[in,out] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[in] pstCert The local certificate which is currently in use.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions.[SEC_PKI_ERROR|NA]
*
* @par Memory Handling
* \n
* ipsi will allocate the memory for the pstCert, to free this memory 
* application has to call X509_freeCert.
*
*/
PSELINKDLL SEC_INT SEC_PKI_objSetlocalCertInUse  (SEC_PKI_OBJ_S *pstObject,
                                   X509_CERT_S *pstCert);


/**
* @defgroup SEC_PKI_objGetlocalCertInUse
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objGetlocalCertInUse( SEC_PKI_OBJ_S *pstObject,
*                                    X509_CERT_S **pstCert);
* @endcode
* @par Purpose
* This function gets the certificate which is currently in use.
*
* @par Description
* SEC_PKI_objGetlocalCertInUse gets the certificate which is currently in use.
* The certificate which is set 
* using  SEC_PKI_objSetlocalCertInUse API will be returned, if no certificate is
* set NULL will be returned.
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[out] pstCert The local certificate which is currently in use.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions.[SEC_PKI_ERROR|NA]
*
*
* @par Memory Handling
* \n
* ipsi will allocate the memory for the pstCert, to free this memory 
* application has to call X509_freeCert.
*
*/
PSELINKDLL SEC_INT SEC_PKI_objGetlocalCertInUse  (SEC_PKI_OBJ_S *pstObject,
                                   X509_CERT_S **pstCert);

#ifndef __SEC_PKI_NO_MULTIPLE_LOCAL_CERT__

/**
* @defgroup SEC_PKI_objRemoveLocalCert
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objRemoveLocalCert( SEC_PKI_OBJ_S *pstObject,
*                                               SEC_NAME_S *pstIssuerName,
*                                               SEC_BIGINT_S *pstSerialNum);
* @endcode
*
* @par Purpose
* This function is used to remove the local cert and key from the local store.
*
* @par Description
* SEC_PKI_objRemoveLocalCert removes the local cert and all the 
* information associated with the local cert like private key and URL 
* information. Default local certificate details can also be removed using 
* this function.
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S.
* Issuer name and serial number are unique identifier in RFC.[NA/NA]
* @param[in] pstIssuerName Issuer name of the certificate.[NA/NA]
* @param[in] pstSerialNum Serial number of the certificate.[NA/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions.[SEC_PKI_ERROR|NA]
*
*/
PSELINKDLL SEC_INT SEC_PKI_objRemoveLocalCert(SEC_PKI_OBJ_S *pstObject,
                                               SEC_NAME_S *pstIssuerName,
                                               SEC_BIGINT_S *pstSerialNum);

#endif

/**
* @defgroup SEC_PKI_objRemovePreSharedPeerCert
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objRemovePreSharedPeerCert( SEC_PKI_OBJ_S *pstObject,
*                                               SEC_NAME_S *pstIssuerName,
*                                               SEC_BIGINT_S *pstSerialNum);
* @endcode
*
* @par Purpose
* This function is used to remove the preshared peer cert from the local store.
*
* @par Description
* SEC_PKI_objRemovePreSharedPeerCert removes the local cert based on the 
* issuer name and serial number.
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S.
* Issuer name and serial number are unique identifier in RFC.[NA/NA]
* @param[in] pstIssuerName Issuer name of the certificate.[NA/NA]
* @param[in] pstSerialNum Serial number of the certificate.[NA/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions.[SEC_PKI_ERROR|NA]
*
*/
PSELINKDLL SEC_INT SEC_PKI_objRemovePreSharedPeerCert(SEC_PKI_OBJ_S *pstObject,
                                               SEC_NAME_S *pstIssuerName,
                                               SEC_BIGINT_S *pstSerialNum);



/**
* @defgroup SEC_PKI_objRemoveDefaultCert
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objRemoveDefaultCert( SEC_PKI_OBJ_S *pstObject);
* @endcode
*
* @par Purpose
* This function removes the default certificate from the object
*
* @par Description
* SEC_PKI_objRemoveDefaultCert removes the default certificate from the object.
* When certificate is removed the corresponding private key is also removed.
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions.[SEC_PKI_ERROR|NA]
*
* @par Note
* \n
* If the default certificate is not present then also this API will
* return SEC_SUCCESS.
*
*/
PSELINKDLL SEC_INT SEC_PKI_objRemoveDefaultCert(SEC_PKI_OBJ_S *pstObject);


#ifndef __SEC_PKI_NO_PEER_CACHE__

/**
* @defgroup SEC_PKI_objGetCtxPeerCertByHash
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objGetCtxPeerCertByHash( const SEC_PKI_OBJ_S *pstObject,
*                                         SEC_UINT uAlgType,
*                                         const SEC_UCHAR *pucHash,
*                                         SEC_UINT len,
*                                         X509_CERT_S **pstCert);
* @endcode
*
* @par Purpose
* This function get the peer cert from the cache, corresponding to public key
* hash
*
* @par Description
* SEC_PKI_objGetCtxPeerCertByHash get the peer cert from the cache,
* corresponding to the hash which is passed as argument.
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[in] uAlgType Hash Algorithm.[NA/NA]
* @param[in] pcHash Hash of the certificate.[NA/NA]
* @param[in] len Hash length.[NA/20]
* @param[out] pstCert Contains the matching certificate.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions.[SEC_PKI_ERROR|NA]
*
* @par Note
* \n
* Memory for pstCert will be allocated inside the library and
* needs to be freed by X509_freeCert.
* Only SHA1 hash algorithm is supported.
*
* @par Related Topics
* SEC_PKI_ctxGetPeerCacheSize\n
* SEC_PKI_ctxResizePeerCache
*
*/
PSELINKDLL SEC_INT SEC_PKI_objGetCtxPeerCertByHash(
                                               const SEC_PKI_OBJ_S *pstObject,
                                               SEC_UINT uAlgType,
                                               const SEC_UCHAR *pucHash,
                                               SEC_UINT len,
                                               X509_CERT_S **pstCert);

#endif

#ifndef __SEC_PKI_NO_PRESHARED_PEER_CERT__

/**
* @defgroup SEC_PKI_objLoadPreSharedPeerCertFile
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objLoadPreSharedPeerCertFile( SEC_PKI_OBJ_S *pstObject,
*                                          const SEC_CHAR *pcCertFile,
*                                          SEC_INT iCertFieType,
*                                          const SEC_CHAR *pcCertPasswd,
*                                          const SEC_UINT uCertPwdLen)
* @endcode
*
* @par Purpose
* This function loads the peer certificate(s) from the file to the peer cert 
* list of the PKI object. 
* 
* @par Description
* SEC_PKI_objLoadPreSharedPeerCertFile function reads a certificate(s) file
* that contains the certificate(s) in "PEM","PFX", or "DER" format and adds the 
* certificate to the preshared peer certificate list of the object. 
* Certificate password is an optional input but it is applicable only
* for PFX format. 
*
* @param[in,out] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[in] pcCertFile The name of the file from which the certificate has to
* be loaded.[NA/NA]
* @param[in] iCertFileType certificate file type, mentions the type of file to 
* be loaded.
* [SEC_PKI_FILETYPE_PFX/SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_ASN1/NA]
* @param[in] pcCertPasswd Password for the certificate file.[NA/NA]
* @param[in] uCertPwdLen Length of the password.[0-225/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Note
*	- A file can contain more than one end entity certificate.
*	- For PFX file type, zero password length is not supported.
*	- If the file type is PFX, the PFX file should be created with encrypted
* password mode only.
*	- For the PEM file type, MIC_CLEAR mode not supported .
*/
PSELINKDLL SEC_INT SEC_PKI_objLoadPreSharedPeerCertFile (
                                          SEC_PKI_OBJ_S *pstObject,
                                          const SEC_CHAR *pcCertFile,
                                          SEC_INT iCertFileType,
                                          const SEC_CHAR *pcCertPasswd,
                                          const SEC_UINT uCertPwdLen);

/**
* @defgroup SEC_PKI_objLoadPreSharedPeerCertBuffer
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objLoadPreSharedPeerCertBuffer( SEC_PKI_OBJ_S *pstObject,
*                                             const SEC_CHAR *pcCertBuffer,
*                                             SEC_UINT uCertBufLen, 
*                                             SEC_INT iCertFieType,
*                                             SEC_CHAR *pcCertPasswd,
*                                             SEC_UINT uCertPwdLen);
* @endcode
*
* @par Purpose
* This function loads the peer certificate(s) from the buffer to the peer cert 
* list of the PKI object.
*
* @par Description
* SEC_PKI_objLoadPreSharedPeerCertBuffer function reads a certificate(s) buffer 
* That contains the certificate(s) in "PEM","PFX", or "DER" format and adds the 
* Certificate to the preshared peer cert list of the context. For Certificate 
* Password is an optional input but password is applicable only for PFX format. 
*
* @param[in,out] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[in] pcCertBuffer The buffer that contains the certificate.[NA/NA]
* @param[in] uCertBufLen Length of the certificate buffer.[NA/NA]
* @param[in] iCertFileType certificate file type, mentions the type of file to 
* be loaded.
* [SEC_PKI_FILETYPE_PFX/SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_ASN1/NA]
* @param[in] pcCertPasswd password for the certificate buffer.[NA/NA]
* @param[in] uCertPwdLen Length of the Password.[0-255/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Note
*	- A buffer can contain more than one end entity certificate.\n
*	- In case of buffer length, validation is done only for the value of zero.
* (Value zero is considered to be invalid). If any value other than the actual
*  buffer length API behaviour is undefined.
*	- For PFX file type, zero password length is not supported.
*	- If the file type is PFX, the PFX file should be created with encrypted
* password mode only.
*	- For the PEM file type, we will not support MIC_CLEAR mode.
*/
PSELINKDLL SEC_INT SEC_PKI_objLoadPreSharedPeerCertBuffer (
                                            SEC_PKI_OBJ_S *pstObject,
                                            const SEC_CHAR *pcCertBuffer,
                                            SEC_UINT uCertBufLen,
                                            SEC_INT iCertFileType,
                                            const SEC_CHAR *pcCertPasswd,
                                            const SEC_UINT uCertPwdLen);

/**
* @defgroup SEC_PKI_objLoadDfltPreSharedPeerCertFile
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objLoadDfltPreSharedPeerCertFile( SEC_PKI_OBJ_S *pstObject,
*                                                const SEC_CHAR *pcCertFile,
*                                                SEC_INT iCertFileType,
*                                                const SEC_CHAR *pcCertPasswd,
*                                                SEC_UINT uCertPwdLen);
* @endcode
*
* @par Purpose
* This function is used to load the default preshared peer certificate in 
* the object.
*
* @par Description
* SEC_PKI_objLoadDfltPreSharedPeerCertFile function is used to load
* the default preshared peer certificate in the object.
* Certificate password is an optional input but, applicable 
* only for PFX format.
*
* @param[in,out] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[in] pcCertFile The name of the file from which the certificate has to
* be loaded.[NA/NA]
* @param[in] iCertFileType certificate file type, mentions the type of file to 
* be loaded.
* [SEC_PKI_FILETYPE_PFX/SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_ASN1/NA]
* @param[in] pcCertPasswd password for the certificate file.[NA/NA]
* @param[in] uCertPwdLen Length of the password.[0-255/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Note
*	- A file should not contain more than one end entity certificate.
*	- In case of file having multiple certificates, first certificate will be
*  considered as end entity certificate.
*	- For PFX file type, zero password length is not supported.
*	- If the file type is PFX, the PFX file should be created only with 
* encrypted password mode .
*	- For the PEM file type, we will not support MIC_CLEAR mode.
*
*/
PSELINKDLL SEC_INT SEC_PKI_objLoadDfltPreSharedPeerCertFile(
                                                SEC_PKI_OBJ_S *pstObject,
                                                const SEC_CHAR *pcCertFile,
                                                SEC_INT iCertFileType,
                                                const SEC_CHAR *pcCertPasswd,
                                                SEC_UINT uCertPwdLen);


/**
* @defgroup SEC_PKI_objLoadDfltPreSharedPeerCertBuffer
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objLoadDfltPreSharedPeerCertBuffer( SEC_PKI_OBJ_S *pstObject,
*                                            const SEC_CHAR *pcCertBuffer,
*                                            SEC_UINT uCertBufLen, 
*                                            SEC_INT iCertFieType,
*                                            const SEC_CHAR *pcCertPasswd,
*                                            SEC_UINT uCertPwdLen);
* @endcode
*
* @par Purpose
* This function loads the default certificate in the object.
*
* @par Description
* SEC_PKI_objLoadDfltPreSharedPeerCertBuffer function is used to load
* the default certificate in the object.
*
* @param[in,out] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[in] pcCertBuffer The buffer that contains the certificate.[NA/NA]
* @param[in] uCertBufLen Length of the certificate buffer.[NA/NA]
* @param[in] iCertFileType certificate file type, mentions the type of file to 
* be loaded.
* [SEC_PKI_FILETYPE_PFX/
* SEC_PKI_FILETYPE_PEM/
* SEC_PKI_FILETYPE_ASN1/NA]
* @param[in] pcCertPasswd Password for the certificate buffer.[NA/NA]
* @param[in] uCertPwdLen Length of the password.[0-255/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Note
*	- A buffer should not contain more than one end entity certificate.
*	- In case of buffer length, validation is done only for the value of zero.
* (Value zero is considered to be invalid). If any value other than the actual
*  buffer length API behaviour is undefined.
*	- In case of buffer having multiple certificates first certificate will be
*  considered as end entity certificate.
*	- For PFX file type, zero password length is not supported.
*	- If the file type is PFX, the PFX file should be created with encrypted
* password mode only.
*	- For the PEM file type, MIC_CLEAR mode not supported .
*
*/
PSELINKDLL SEC_INT SEC_PKI_objLoadDfltPreSharedPeerCertBuffer(
                                                 SEC_PKI_OBJ_S *pstObject,
                                                 const SEC_CHAR *pcCertBuffer,
                                                 SEC_UINT uCertBufLen,
                                                 SEC_INT iCertFieType,
                                                 const SEC_CHAR *pcCertPasswd,
                                                 SEC_UINT uCertPwdLen);



/**
* @defgroup SEC_PKI_objGetDfltPreSharedPeerCert
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objGetDfltPreSharedPeerCert( SEC_PKI_OBJ_S *pstObject,
*                                           X509_CERT_S **pstCert);
* @endcode
* @par Purpose
* This function is used to get the default preshared peer certificate 
* from the object.
*
* @par Description
* SEC_PKI_objGetDfltPreSharedPeerCert function is used to get
* the default preshared peer certificate from the object.
* If the default preshared peer cert is not loaded before calling this
* API then the output pstCert contains NULL.
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[out] pstCert Default certificate.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
* ipsi will allocate the memory for the pstCert, to free this memory 
* application has to call the X509_freeCert.
*/
PSELINKDLL SEC_INT SEC_PKI_objGetDfltPreSharedPeerCert(
                                               SEC_PKI_OBJ_S *pstObject,
                                               X509_CERT_S **pstCert);


/**
* @defgroup SEC_PKI_objGetPreSharedPeerCertByGenName
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objGetPreSharedPeerCertByGenName (
                                         SEC_PKI_OBJ_S *pstObject,
                                         SEC_GEN_NAME_S  *pstGenName,
                                         X509_CERT_S *pstOutCert);
* @endcode
*
* @par Purpose
* This function is used to get the pre shared certificate based on the 
* generalName passed.
* @par Description
* It will return the certificate  from pre shared store matching the
* general Name
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[in] pstGenName Pointer to SEC_GEN_NAME_S.[NA/NA]
* @param[out] pstOutCert  x509 certificate[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions[SEC_PKI_ERROR|NA]
*
* @par Memory Handling
* On success this function will allocate the memory for the pstOutCert
* To free this memory pplication has to call X509_freeCert.
* @par Note
* \n
* First element in the list is a certificate which matches the general name
*
*/
PSELINKDLL SEC_INT SEC_PKI_objGetPreSharedPeerCertByGenName (
                         SEC_PKI_OBJ_S *pstObject,
                         SEC_GEN_NAME_S  *pstGenName,
                         X509_CERT_S **pstOutCert);
#endif

/**
* @defgroup SEC_PKI_objGetURLByCert
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objGetURLByCert( SEC_PKI_OBJ_S *pstObject,
*                                 X509_CERT_S *pstCert,
*                                 SEC_PKI_DATA_BUF_S **pstURL);
* @endcode
*
* @par Purpose
* This function is used to get URL corresponding to the input
* certificate.
*
* @par Description
* SEC_PKI_objGetURLByCert function gets URL corresponding to the 
* input certificate from the local store.
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[in] pstCert Input certificate.[NA/NA]
* @param[out] pstURL URL associated with the 
* input certificate.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Memory Handling
* ipsi will allocate the memory for the "pstURL" to free this memory
* application has to call the SEC_PKI_freeDataBuf.
*
*/
PSELINKDLL SEC_INT SEC_PKI_objGetURLByCert (SEC_PKI_OBJ_S *pstObject,
                                X509_CERT_S *pstCert,
                                SEC_PKI_DATA_BUF_S **pstURL);

#ifndef __SEC_PKI_NO_PEER_CACHE__

/**
* @defgroup SEC_PKI_objGetAllCtxPeerCerts
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_List_S * SEC_PKI_objGetAllCtxPeerCerts(
* SEC_PKI_OBJ_S *pstObject,SEC_List_S **dpOutCertList);
* @endcode
*
* @par Purpose
* This function is used to get all peer certificate in object.
*
* @par Description
*  SEC_PKI_objGetAllCtxPeerCerts used to get all peer certificate 
* from the peer cache from the context using the object.
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[out] dpOutCertList List which contains all the certs.
* dpOutCertList is a list which holds elements of type X509_CERT_S.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Memory Handling
* ipsi will allocate the memory for the dpOutCertList 
* (the list may contain one or more entries) to free this memory 
* application has to call the SEC_LIST_FREE,with the 
* free function as X509_freeCert.
*
*/
PSELINKDLL SEC_INT SEC_PKI_objGetAllCtxPeerCerts(
    SEC_PKI_OBJ_S *pstObject,SEC_List_S **dpOutCertList);

#endif

#ifndef __SEC_PKI_NO_PRESHARED_PEER_CERT__

/**
* @defgroup SEC_PKI_objGetAllPreSharedPeerCert
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objGetAllPreSharedPeerCert( SEC_PKI_OBJ_S *pstObject,
*                                            SEC_List_S **dpOutCertList)
* @endcode
*
* @par Purpose
* This function is used to get all certificates from the preshared 
* peer store of the passed Object.
*
* @par Description
* SEC_PKI_objGetAllPreSharedPeerCert function is used to get all certificates
* from the preShared peer store of the passed Object.
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[out] dpOutCertList List which contains all the certs.
* dpOutCertList is a list which holds elements of type X509_CERT_S.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Memory Handling
* On success this function will allocate the memory for the dpOutCertList
* (the list may contain one or more entries). To free this memory 
* application has to call SEC_LIST_FREE with the free function as
* X509_freeCert.
*
*/
PSELINKDLL SEC_INT SEC_PKI_objGetAllPreSharedPeerCert(
    SEC_PKI_OBJ_S *pstObject,SEC_List_S **dpOutCertList);



/**
* @defgroup SEC_PKI_objRemoveDfltPreSharedPeerCert
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objRemoveDfltPreSharedPeerCert( SEC_PKI_OBJ_S *pstObject);
* @endcode
*
* @par Purpose
* This function is used to remove the default preshared peer 
* certificate from the object.
*
* @par Description
* SEC_PKI_objRemoveDfltPreSharedPeerCert function removes the default preshared 
* peer certificate from the object.
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions[SEC_PKI_ERROR|NA]
*
* @par Note
* \n
* If the default preshared peer certificate is not present then also this API 
* will return SEC_SUCCESS.
*
*/
PSELINKDLL SEC_INT SEC_PKI_objRemoveDfltPreSharedPeerCert(SEC_PKI_OBJ_S 
                                                          *pstObject);

#endif

/**
* @defgroup SEC_PKI_objLoadCrlBuffer
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objLoadCrlBuffer( SEC_PKI_OBJ_S *pstObject,
*                               SEC_CHAR *pcCrlBuffer,
*                               SEC_UINT uCrlBufLen,
*                               SEC_INT type);
* @endcode
*
* @par Purpose
* This function is used to load the CRL from the buffer to store.
*
* @par Description
* SEC_PKI_objLoadCrlBuffer function decodes buffer that contains a CRL 
* (Certificate Revocation List) in "PEM" or "DER" format, and adds the CRL 
* to the store.
*
* @param[in,out] pstObject Pointer to SEC_PKI_OBJ_S. [NA/NA]
* @param[in] pcCrlBuffer CRL buffer.[NA/NA]
* @param[in] uCrlBufLen CRL buffer length.[NA/NA]
* @param[in] iType Mentions the file type to be loaded.
* [SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_ASN1/NA]
* @param[out] NA NA [NA/NA]
*
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. If the input is invalid 
* (NULL pointer)or decoding of CRL fails. [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
*	- It is recommended that crl dates are verified before loading the same.\n
*	- In case of buffer length, validation is done only for the value of zero.
*    [Value zero is considered to be invalid].Any value other than the actual
*    buffer length ,API behavioris undefined.
*	- If the same crl already exist in the store then error will be returned.
*/
PSELINKDLL SEC_INT SEC_PKI_objLoadCrlBuffer(SEC_PKI_OBJ_S *pstObject,
                             SEC_CHAR *pcCrlBuffer,
                             SEC_UINT uCrlBufLen,
                             SEC_INT iType);


/**
* @defgroup SEC_PKI_objGetAllCRL
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objGetAllCRL( SEC_PKI_OBJ_S *pstObject,
*                               SEC_List_S **dpOutCRLList);
* @endcode
*
* @par Purpose
* This function is used to get all CRL from object inband CRL store.
*
* @par Description
* SEC_PKI_objGetAllCRL function gets all CRL from store.
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[out] dpOutCRLList List which contains all the CRLs.
* dpOutCRLList is a list which holds elements of type X509_CRL_S.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Memory Handling
* ipsi will allocate the memory for the dpOutCRLList (the list may contain one
* or more entries) to free this memory application as to call the
* SEC_LIST_FREE, with the free function as X509CRL_free.
*/
PSELINKDLL SEC_INT SEC_PKI_objGetAllCRL(SEC_PKI_OBJ_S *pstObject,
                         SEC_List_S **dpOutCRLList);


/**
* @defgroup SEC_PKI_objRemoveCrl
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objRemoveCrl(SEC_PKI_OBJ_S *pstObject,
*                               SEC_NAME_S *pstIssuerName,
*                               SEC_BIGINT_S *pstExtnCRLNum);
* @endcode
* @par Purpose
* This function is used to remove the CRL from the inband CRL store.
*
* @par Description
* SEC_PKI_objRemoveCrl function removes the CRL  for which the 
* input issuer name and CRL number matches from the object inband CRL store.
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[in] pstIssuerName Issuer name of the CRL.[NA/NA]
* @param[in] pstExtnCRLNum Extension CRL number of the CRL.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
*	- If the user inputs only Issuer Name then all the matching CRL(S) 
* and Delta CRL(S) will be removed.
*	- If the user inputs both the Issuer Name and the CRL number then all 
* the matching CRL(S) and Delta CRL(S) will be removed from object CRL store.
*/
PSELINKDLL SEC_INT SEC_PKI_objRemoveCrl(SEC_PKI_OBJ_S *pstObject,
                         SEC_NAME_S *pstIssuerName,
                         SEC_BIGINT_S *pstExtnCRLNum);


/**
* @defgroup SEC_PKI_objRemoveAllCrl
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objRemoveAllCrl(SEC_PKI_OBJ_S *pstObject)
* @endcode
* @par Purpose
* This function is used to removes the inband CRL store of the object.
*
* @par Description
* SEC_PKI_objRemoveAllCrl function removes the object CRL list completely.
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*/
PSELINKDLL SEC_INT SEC_PKI_objRemoveAllCrl(SEC_PKI_OBJ_S *pstObject);


/**
* @defgroup SEC_PKI_objGetLocalCertChainByGenName
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objGetLocalCertChainByGenName (
					      SEC_PKI_OBJ_S *pstObject,
                                         SEC_GEN_NAME_S  *pstGenName,
                                         SEC_List_S **dpOutCertChain);
* @endcode
*
* @par Purpose
* This function is used to get the certificate chain from the pki object 
* store on the basis of the generalName passed.
* @par Description
* It will return the certificate chain from the trust store if generalName
* is matched.
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[in] pstGenName Pointer to SEC_GEN_NAME_S.[NA/NA]
* @param[out] dpOutCertChain List of cert chain[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions[SEC_PKI_ERROR|NA]
*
* @par Memory Handling
* On success this function will allocate the memory for the dpOutCertList
* (the list may contain one or more entries). To free this memory 
* application has to call SEC_LIST_FREE with the free function as
* X509_freeCert.
* @par Note
* \n
* 1. First element in the list is a certificate which matches the general name
* 2. Possible certificate chain that can be built for the input certificate
*    using the trust store will only be considered, if the issuer certificate
*    for matched certificate is not found in the trust store, then only the 
*    matched certificate will be considered in the output chain. Hence the 
*	 chain obtained in the output for the input certificate, can be incomplete.
* 3. Only basic validation is done to construct the certificate chain.i.e the 
*    certificate is obtained from store only on the basis of the generalName
*	 & then its certificate chain is returned.
*
*/

PSELINKDLL SEC_INT SEC_PKI_objGetLocalCertChainByGenName (
                          SEC_PKI_OBJ_S *pstObject,
                                         SEC_GEN_NAME_S  *pstGenName,
                                         SEC_List_S **dpOutCertChain);


#ifndef __IPSI_SEC_NO_OBJ_GET_CERT_CRL__

/**
* @defgroup SEC_PKI_objGetCtxBaseCRLbyCert
* @ingroup Object_Functions
* @par Prototype
* @code
* X509_CRL_S* SEC_PKI_objGetCtxBaseCRLbyCert(
                                        SEC_PKI_OBJ_S *pstObject,
                                        X509_CERT_S *pstCert);
* @endcode
*
* @par Purpose
* This function is used for getting the base crl for the certificate 
* from the context crl store of the object.
*
* @par Description
* SEC_PKI_objGetCtxBaseCRLbyCert function gets the 
* base crl for the certificate from the context crl store of the object.
*
* @param[in] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[in] pstCert Pointer to X509_CERT_S.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval X509_CRL_S* On successful execution. [NA|NA]
* @retval NULL On all failure conditions. [NULL|NA]
*
* @par Note
* \n
*	- If user loads more than one base crl into the context crl store of object,
* then this API will return the appropriate base crl suitable for the
* certificate passed.
*
*	- Finding of the appropriate CRL based on the following checks:
* Time, AKID, IDP Reasons, Direct/Indirect CRL, and Criticality extensions.
*/
PSELINKDLL X509_CRL_S* SEC_PKI_objGetCtxBaseCRLbyCert(
                                        SEC_PKI_OBJ_S *pstObject,
                                        X509_CERT_S *pstCert);


/**
* @defgroup SEC_PKI_objGetCtxDeltaCRLbyCert
* @ingroup Object_Functions
* @par Prototype
* @code
* X509_CRL_S* SEC_PKI_objGetCtxDeltaCRLbyCert(
                                         SEC_PKI_OBJ_S *pstObject,
                                         X509_CERT_S *pstCert);
* @endcode
*
* @par Purpose
* This function is used for getting the delta crl for the certificate 
* from the context crl store of the object.
*
* @par Description
* SEC_PKI_objGetCtxDeltaCRLbyCert function gets the 
* delta crl for the certificate from the context crl store of the object.
*
* @param[in] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[in] pstCert Pointer to X509_CERT_S.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval X509_CRL_S* On successful execution. [NA|NA]
* @retval NULL On all failure conditions[NULL|NA]
*
* @par Note
* \n
*	- If user loads more than one base crl and more than one delta crl
* for the corresponding base crls in the context crl store of object, then 
* this API will return the appropriate delta crl corresponding to the 
* appropriate base crl for the certificate passed.
*
*	- Finding of the appropriate CRL based on the following checks:
* Time, AKID, IDP Reasons, Direct/Indirect CRL, Criticality extensions.
*
*/
PSELINKDLL X509_CRL_S* SEC_PKI_objGetCtxDeltaCRLbyCert(
                                         SEC_PKI_OBJ_S *pstObject,
                                         X509_CERT_S *pstCert);


/**
* @defgroup SEC_PKI_objGetBaseCRLbyCert
* @ingroup Object_Functions
* @par Prototype
* @code
* X509_CRL_S* SEC_PKI_objGetBaseCRLbyCert(
                                        SEC_PKI_OBJ_S *pstObject,
                                        X509_CERT_S *pstCert);
* @endcode
*
* @par Purpose
* This function is used for getting the base crl for the certificate 
* from the object crl store.
*
* @par Description
* SEC_PKI_objGetBaseCRLbyCert function gets the 
* base crl for the certificate from the object crl store.
*
* @param[in] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[in] pstCert Pointer to X509_CERT_S.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval X509_CRL_S* On successful execution. [NA|NA]
* @retval NULL On all failure conditions.[NULL|NA]
*
* @par Note
* \n
*- If user loads more than one base crl in the object crl store, then
* this API will return the appropriate base crl suitable for the 
* certificate passed.
*
*	- Finding of the appropriate CRL based on the following checks:
* Time, AKID, IDP Reasons, Direct/Indirect CRL, and Criticality extensions.
*/
PSELINKDLL X509_CRL_S* SEC_PKI_objGetBaseCRLbyCert(
                                        SEC_PKI_OBJ_S *pstObject,
                                        X509_CERT_S *pstCert);


/**
* @defgroup SEC_PKI_objGetDeltaCRLbyCert
* @ingroup Object_Functions
* @par Prototype
* @code
* X509_CRL_S* SEC_PKI_objGetDeltaCRLbyCert(
                                         SEC_PKI_OBJ_S *pstObject,
                                         X509_CERT_S *pstCert);
* @endcode
*
* @par Purpose
* This function is used for getting the delta crl for the certificate 
* from the object crl store.
*
* @par Description
* SEC_PKI_objGetDeltaCRLbyCert function gets the 
* delta crl for the certificate from the object crl store.
*
* @param[in] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[in] pstCert Pointer to X509_CERT_S.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval X509_CRL_S* On successful execution. [NA|NA]
* @retval NULL On all failure conditions. [NULL|NA]
*
* @par Note
* \n
*	- If user loads more than one base crl and more than one delta crl
* for the corresponding base crls in the object crl store, then this API
* will return the appropriate delta crl corresponding to the appropriate 
* base crl for the certificate passed.
*
*	- Finding of the appropriate CRL based on the following checks:
* Time, AKID, IDP Reasons, Direct/Indirect CRL, Criticality extensions.
*
*/
PSELINKDLL X509_CRL_S* SEC_PKI_objGetDeltaCRLbyCert(
                                         SEC_PKI_OBJ_S *pstObject,
                                         X509_CERT_S *pstCert);


#endif





/**
* @defgroup SEC_PKI_objSetHandle
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objSetHandle( SEC_PKI_OBJ_S *pstObject,
*                       SEC_VOID * pHandle);
* @endcode
*
* @par Purpose
* This function is used to set the connection handle in the object.
*
* @par Description
* SEC_PKI_objSetHandle function is used to set the connection handle 
* in the object. NULL can be passed to reset the connection handle
* in the object.
*
* @param[in,out] pstObject Pointer to SEC_PKI_OBJ_S [NA/NA]
* @param[in] pHandle The connection handle [NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions [SEC_PKI_ERROR|NA]
*
*/
PSELINKDLL SEC_INT SEC_PKI_objSetHandle(SEC_PKI_OBJ_S *pstObject,
                                        SEC_VOID * pHandle);


/**
* @defgroup SEC_PKI_objGetHandle
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_VOID * SEC_PKI_objGetHandle( SEC_PKI_OBJ_S *pstObject);
* @endcode
* @par Purpose
* This function is used to get the connection handle from the object.
*
* @par Description
* SEC_PKI_objGetHandle function is used to get the connection handle 
* associated with the object. If the user frees the memory that is returned,
* then connection handle should be explicitly reset to NULL in the object.
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S [NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution [SEC_VOID *|NA]
* @retval SEC_INT On all failure conditions [SEC_NULL|NA]
*
*/
PSELINKDLL SEC_VOID * SEC_PKI_objGetHandle(SEC_PKI_OBJ_S *pstObject);


/**
* @defgroup SEC_PKI_X509_storeCtxGetObjHandle
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_VOID * SEC_PKI_X509_storeCtxGetObjHandle( SEC_VOID *pstStoreCtx);
* @endcode
* 
* @par Purpose
* This is used to get connection handle in SEC_PKI_X509_STORE_CTX_S structure.
* 
* @par Description
* SEC_PKI_X509_storeCtxGetObjHandle function can be used to get the connection 
* handle in case of certificate chain verification.
*
* @param[in] pstStoreCtx void pointer [NA/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval SEC_VOID* In Case of Success 
* connection handle is returned [SEC_VOID *|NA]
* @retval SEC_NULL In Case of failure or if the connection handle is not set,
* failure occurs when input pointer is SEC_NULL 
* [SEC_NULL|Do%not%pass%SEC_NULL]
*/
PSELINKDLL SEC_VOID * SEC_PKI_X509_storeCtxGetObjHandle(SEC_VOID *pstStoreCtx);



/**
* @defgroup SEC_PKI_objSetOptions
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objSetOptions
* ( 
*      SEC_PKI_OBJ_S *pstObject,
*      SEC_UINT uiOptions
* );
* @endcode
*
* @par Purpose
* This function is used to set the PKI options for the object.
*
* @par Description
* SEC_PKI_objSetOptions function is used to set the PKI options for the object.
* Each new option will be ORed with the existing option.The option flags should 
* be of type SEC_PKI_OPTIONS_E. By passing zero, the options in the object
* can be reset.
*
* @param[in,out] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[in] uiOptions PKI Option flags to be set. <b> Default value is 0. </b>
* [0-Maximum.of.SEC_UINT]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Dependency
* sec_pki_def.h  \n
* sec_pki_object.h
*
* @attribute Yes No
*
* @par Note
*
* None
*
* @par Example
* None
*
* @par Related Topics
* SEC_PKI_objGetOptions
*/
PSELINKDLL SEC_INT SEC_PKI_objSetOptions(SEC_PKI_OBJ_S *pstObject,
                       SEC_UINT uiOptions);


/**
* @defgroup SEC_PKI_objGetOptions
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objGetOptions
* ( 
*      SEC_PKI_OBJ_S *pstObject,
*      SEC_UINT *puiOptions
* );
* @endcode
*
* @par Purpose
* This function is used to get the PKI option flags from the object.
*
* @par Description
* SEC_PKI_objGetOptions is used to get the PKI option flags associated 
* with the object.It will give the ORed value of the PKI option flags
* that are set in the object. If no option is set, zero is returned or
* else while creating object if any of the options are inherited from the
* context, those will be returned.
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[out] puiOptions Contains the option flags. <b> Default value is 0. </b>
* [0-Maximum.of.SEC_UINT]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Memory Handling
* \n
* Application should pass the address of an unsigned integer variable.
*
* @par Dependency
* sec_pki_def.h  \n
* sec_pki_object.h
*
* @attribute Yes No
*
* @par Note
*
* None
*
* @par Example
* None
*
* @par Related Topics
* SEC_PKI_objSetOptions
*/
PSELINKDLL SEC_INT SEC_PKI_objGetOptions(SEC_PKI_OBJ_S *pstObject,
                       SEC_UINT *puiOptions);



/**
* @defgroup SEC_PKI_X509_storeCtxSetAppError
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_X509_storeCtxSetAppError(SEC_VOID *pstStoreCtx, SEC_INT iAppErrCode);
* @endcode
*
* @par Purpose
* This function can be used by the application to set it's specific error code to the store context
* in the PKI certificate verification callback.
*
* @par Description
* SEC_PKI_X509_storeCtxSetAppError can be used by the application to set it's specific error code to the store context
* in the PKI certificate verification callback. The error code set here will be provided back to the application
* when they invoke SEC_PKI_objGetAppVerifyResult API.
*
* @param[in] pstStoreCtx Pointer to store context passed to the callback.[NA/NA]
* @param[in] iAppErrCode Error code which application wants to set.
* No validation will be done by API for this parameter.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Memory Handling
* \n
* NA
*
* @par Dependency
* sec_pki_def.h  \n
* sec_pki_object.h
*
* @attribute Yes No
*
* @par Note
*
* None
*
* @par Example
* None
*
* @par Related Topics
* SEC_PKI_objGetAppVerifyResult\n
* SEC_PKI_objSetVerify
*/
PSELINKDLL SEC_INT SEC_PKI_X509_storeCtxSetAppError(SEC_VOID *pstStoreCtx, SEC_INT iAppErrCode);


/**
* @defgroup SEC_PKI_objGetAppVerifyResult
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_objGetAppVerifyResult(SEC_PKI_OBJ_S *pstObj, SEC_INT *piAppErr);
* @endcode
*
* @par Purpose
* This function is used to retrieve the error code set by application in PKI certificate verification callback by
* using API "SEC_PKI_X509_storeCtxSetAppError".
*
* @par Description
* This function is used to retrieve the error code set by application in PKI certificate verification callback by
* using API "SEC_PKI_X509_storeCtxSetAppError".
*
* @param[in] pstObj Pointer to PKI Object.[NA/NA]
* @param[out] piAppErr Variable to hold the output error code.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Memory Handling
* \n
* Application should pass the address of an signed integer variable for iAppErrCode.
*
* @par Dependency
* sec_pki_def.h  \n
* sec_pki_object.h
*
* @attribute Yes No
*
* @par Note
*
* None
*
* @par Example
* None
*
* @par Related Topics
* SEC_PKI_X509_storeCtxSetAppError\n
* SEC_PKI_objSetVerify
*/
PSELINKDLL SEC_INT SEC_PKI_objGetAppVerifyResult(SEC_PKI_OBJ_S *pstObj, SEC_INT *piAppErr);


#ifdef  __cplusplus
}
#endif

#endif /*__SEC_PKI_OBJECT_H__*/

#endif // IPSI_SEC_NO_PKI

