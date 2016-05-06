/*

                Copyright 2003, Huawei Technologies Co. Ltd.
                            ALL RIGHTS RESERVED

------------------------------------------------------------------------------

                              sec_common.h

  Project Code: SeCert
   Module Name: Common Module
  Date Created: 2005-07-04
        Author: Sanjay Vasudevan
   @brief: Contains structures and functions required in two or more
   modules.
------------------------------------------------------------------------------
*/
#include "ipsi_pse_build_conf.h"

#ifndef  _SEC_COMMON_H_
#define   _SEC_COMMON_H_

#include "ipsi_types.h"
#include "sec_sys.h"

#include "sec_log.h"

#include "asn-types.h"

#ifdef	 __cplusplus
extern	"C"{
#endif


#define PSE_VERSION "1.1"  /* This is Version 1 Release 1 of PSE lib*/

/** @defgroup sec_common
* This section contains the sec_common Functions and Enums
*/

/* enumeration to hold Certificate type: used in PKCS12,SCEP*/

/** @defgroup sec_commonEnum
* @ingroup sec_common
* This section contains the sec_common Enum
*/

/**
* @defgroup SEC_CertType_E
* @ingroup sec_commonEnum
* @par Prototype
* @code
* typedef enum enSEC_CertType
* {
* 	CERT_UNKNOWN = 0,
* 	CERT_X509    = 1,
* 	CERT_SDSI    = 2
* } SEC_CertType_E;
*
* @endcode
*
* @datastruct CERT_UNKNOWN=0 Unknown certificate type.
* @datastruct CERT_X509=1 x509 certificate.
* @datastruct CERT_SDSI=2 SDSI (Simple Distributed Security Infrastructure) certificate.
*/
typedef enum enSEC_CertType
{
	CERT_UNKNOWN = 0,  /*Unknown certificate type*/
	CERT_X509 = 1,     /*x509 certificate*/
	CERT_SDSI = 2      /*SDSI (Simple Distributed Security Infrastructure) certificate*/
} SEC_CertType_E;
/* end of certtype */


/** @defgroup sec_commonFunctions
* @ingroup sec_common
* This section contains the sec_common Functions
*/



/**
* @defgroup SEC_getPSEVersion
* @ingroup sec_commonFunctions
* @par Prototype
* @code
* SEC_CHAR* SEC_getPSEVersion();
* @endcode
*
* @par Purpose
* To get the version of the PSE Library.
*
* @par Description
* This function gets the version of the PSE library.
*
* @param[in] N/A N/A [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_CHAR* The version of PSE library [SEC_CHAR*|N/A]
*
* @par Dependency
* sec_common.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_CHAR* SEC_getPSEVersion();




/**
* @defgroup SEC_displayPSEVersion
* @ingroup sec_commonFunctions
* @par Prototype
* @code
* SEC_VOID SEC_displayPSEVersion();
* @endcode
*
* @par Purpose
* To display(print) the version of the PSE Library.
*
* @par Description
* This function displays the version of the PSE library.
*
* @param[in] N/A N/A [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value [N/A|N/A]
*
* @par Dependency
* sec_common.h
*
* @par Note
*
* This function internally uses printf to print the PSE Version to the console. Users are advised NOT to
* use this function in C++ based adapter codes as it may have a conflict with std::cout.
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID SEC_displayPSEVersion();




/**
* @defgroup SEC_getCID
* @ingroup sec_commonFunctions
* @par Prototype
* @code
* SEC_UINT32 SEC_getCID (SEC_AsnOid_S* pAsnOid);
* @endcode
*
* @par Purpose
* To get the common ID of a given OID.
*
* @par Description
* This function returns the commmon ID of an OID. It uses the OID table.
*
* @param[in] pAsnOid The input OID [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 On Success [The Common ID (CID)|N/A]
* @retval SEC_UINT32 In case of\n
* 1. Error (like invalid Oid)\n
* 2. NULL pointer input\n
* 3. Empty OID [0(CID_UNKNOWN)|N/A]
*
* @par Dependency
* sec_common.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

//This function is used by SSL. Hence import define added here
PSELINKDLL SEC_UINT32 SEC_getCID (SEC_AsnOid_S* pAsnOid);




/**
* @defgroup SEC_getOID
* @ingroup sec_commonFunctions
* @par Prototype
* @code
* SEC_AsnOid_S* SEC_getOID (SEC_UINT32 ulCID);
* @endcode
*
* @par Purpose
* To get the OID corresponding to a common ID.
*
* @par Description
* This function returns the OID to a commmon id.  It uses the OID table. The
* returned pointer is a pointer into the existing OID table and should not be freed by
* caller.
*
* @param[in] ulCID The input Common ID [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_AsnOid_S* The equivalent OID [SEC_AsnOid_S*|N/A]
*
* @par Dependency
* sec_common.h
*
* @par Note
*
* The returned OID pointer should not be freed by the user.
*
* @par Related Topics
* N/A
*/

/* gets the AsnOid for a Common ID */
PSELINKDLL SEC_AsnOid_S* SEC_getOID (SEC_UINT32 ulCID);




/**
* @defgroup SEC_getCIDFromLongOIDName
* @ingroup sec_commonFunctions
* @par Prototype
* @code
* SEC_UINT32 SEC_getCIDFromLongOIDName (SEC_CHAR* pucLongOIDName);
* @endcode
*
* @par Purpose
* To get the CID corresponding to an OID Long name.
*
* @par Description
* This function returns the commmon id of an OID given its Longname.  It uses
* the OID table.
*
* @param[in] pucLongOIDName The Long name of OID [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 The Common ID (CID) [SEC_UNIT32|N/A]
* @retval SEC_UINT32 If unsuccessful [0 (CID_UNKNOWN)|N/A]
*
* @par Dependency
* sec_common.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 SEC_getCIDFromLongOIDName (SEC_CHAR* pucLongOIDName);



/**
* @defgroup SEC_getLongOIDName
* @ingroup sec_commonFunctions
* @par Prototype
* @code
* SEC_CHAR* SEC_getLongOIDName (SEC_UINT32 ulCID);
* @endcode
*
* @par Purpose
* To get the OID Long name corresponding to a common ID.
*
* @par Description
* This function returns the Long OID Name corresponding to a commmon id. It
* uses the OID table. The  returned pointer is a pointer to the OID
* table and should not be freed by the caller.
*
* @param[in] ulCID The input Common ID [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_CHAR* The equivalent Long name [SEC_CHAR*|N/A]
* @retval SEC_CHAR* If unsuccessful [SEC_NULL|N/A]
*
* @par Dependency
* sec_common.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_CHAR* SEC_getLongOIDName (SEC_UINT32 ulCID);



/**
* @defgroup SEC_getCIDFromShortOIDName
* @ingroup sec_commonFunctions
* @par Prototype
* @code
* SEC_UINT32 SEC_getCIDFromShortOIDName (SEC_CHAR* pucShortOIDName);
* @endcode
*
* @par Purpose
* To get the CID corresponding to an OID short name.
*
* @par Description
* This function returns the commmon ID of an OID given its short name. It
* uses the OID table.
*
* @param[in] pucShortOIDName The short name of OID [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 The common ID (CID) [any of the values SEC_CID_E |N/A]
* @retval SEC_UINT32 If unsuccessful [0 (CID_UNKNOWN)|N/A]
*
* @par Dependency
* sec_common.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 SEC_getCIDFromShortOIDName (SEC_CHAR* pucShortOIDName);



/**
* @defgroup SEC_getShortOIDName
* @ingroup sec_commonFunctions
* @par Prototype
* @code
* SEC_CHAR* SEC_getShortOIDName (SEC_UINT32 ulCID);
* @endcode
*
* @par Purpose
* To get the OID short name corresponding to a common ID.
*
* @par Description
* This function returns the short OID Name corresponding to a commmon id. It
* uses the OIDtable. The  returned pointer is a pointer into OID
* table and should not be freed by caller.
*
* @param[in] ulCID The input Common ID [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_CHAR* The equivalent short OID Name [SEC_CHAR*|N/A]
* @retval SEC_CHAR* If unsuccessful [SEC_NULL|N/A]
*
* @par Dependency
* sec_common.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_CHAR* SEC_getShortOIDName (SEC_UINT32 ulCID);




/**
* @defgroup SEC_compareDates
* @ingroup sec_commonFunctions
* @par Prototype
* @code
* DATE_COMPARE_E SEC_compareDates(DATETIME_S* pDateA, DATETIME_S* pDateB, SEC_UINT32 *pulDiffSeconds);
* @endcode
*
* @par Purpose
* To compare two DATETIME_S structures.
*
* @par Description
* This function reads in two DATETIME_S structures and compares them.  It
* specifies whether first date is BEFORE,AFTER or SAME as the
* second date. It also gives the difference between the two
* dates.
*
* @param[in] pDateA The first date [N/A]
* @param[in] pDateB The second date [N/A]
* @param[out] pulDiffSeconds The difference between the two
*					 dates in seconds [N/A]
*
* @retval DATE_COMPARE_E Error in comparison [ERROR_CMP|N/A]
* @retval DATE_COMPARE_E The two dates are same [EQUAL_DATE|N/A]
* @retval DATE_COMPARE_E First date is before second date [BEFORE_DATE|N/A]
* @retval DATE_COMPARE_E First date is after second date [AFTER_DATE|N/A]
*
* @par Dependency
* sec_common.h
*
* @par Note
* The ucUTCSign,ucUTCHour,ucUTCMinute fields of DATETIME_S are
* not considered in this function.
*
* @par Related Topics
* N/A
*/


//This function is used by SSL.Hence import define has been added.
PSELINKDLL DATE_COMPARE_E SEC_compareDates(DATETIME_S* pDateA, DATETIME_S* pDateB, SEC_UINT32 *pulDiffSeconds);



/**
* @defgroup SEC_compareDates_ex
* @ingroup sec_commonFunctions
* @par Prototype
* @code
* DATE_COMPARE_E SEC_compareDates_ex(DATETIME_S* pDateA, DATETIME_S* pDateB, SEC_TIME_T *pDiffSeconds);
* @endcode
*
* @par Purpose
* To compare two DATETIME_S structures.
*
* @par Description
* This function reads in two DATETIME_S structures and compares them. It
* specifies whether first date is BEFORE,AFTER or SAME as the
* second date. It also gives the difference between the two
* dates.
*
* @param[in] pDateA The first date [N/A]
* @param[in] pDateB The second date [N/A]
* @param[out] pDiffSeconds The difference between the two
*					 dates in seconds as SEC_TIME_T[N/A]
*
* @retval DATE_COMPARE_E Error in comparison [ERROR_CMP|N/A]
* @retval DATE_COMPARE_E The two dates are same [EQUAL_DATE|N/A]
* @retval DATE_COMPARE_E First date is before second date [BEFORE_DATE|N/A]
* @retval DATE_COMPARE_E First date is after second date [AFTER_DATE|N/A]
*
* @par Dependency
* sec_common.h
*
* @par Note
* \n
* The ucUTCSign,ucUTCHour,ucUTCMinute fields of DATETIME_S are
* not considered in this function.
*
* @par Related Topics
* N/A
*/


//This function is used by SSL.Hence import define has been added.
PSELINKDLL DATE_COMPARE_E SEC_compareDates_ex(DATETIME_S* pDateA, DATETIME_S* pDateB, SEC_TIME_T *pDiffSeconds);

/**
* @defgroup SEC_sysTime
* @ingroup sec_commonFunctions
* @par Prototype
* @code
* DATETIME_S* SEC_sysTime();
* @endcode
*
* @par Purpose
* To get the present system time.
*
* @par Description
* This function obtains the current system time in DATETIME_S structure. It
* uses Dopra function/ system call to get the current system time in
* (DATE_T & TIME_T) or time_t structure and then converts that to DATETIME_S format.
* In case of Dopra usage, it allocates the memory for the DATE_T & TIME_T structure.
*
* @param[in] N/A N/A [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval DATETIME_S* The current system time [DATETIME_S*|N/A]
*
* @par Dependency
* sec_common.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

//This function is used by SSL.Hence import define has been added.
PSELINKDLL DATETIME_S* SEC_sysTime(SEC_VOID);






/**
* @defgroup SEC_saveDERCodeToFile
* @ingroup sec_commonFunctions
* @par Prototype
* @code
* SEC_UINT32 SEC_saveDERCodeToFile (SEC_CHAR* pszDERCode, SEC_UINT32 ulDERCodelen, SEC_CHAR* pszFileName);
* @endcode
*
* @par Purpose
* To save DER code into a file.
*
* @par Description
* This function writes the DER code from the given buffer into a file.
*
* @param[in] pszDERCode The buffer containing the DER code which is to be written into a file. [N/A]
* @param[in] ulDERCodelen The length of the der code [N/A]
* @param[in] pszFileName The file name to which the DER code will be written to [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 On successful operation [The number of bytes written into the file|N/A]
* @retval SEC_UNIT32 On failure [0|N/A]
*
* @par Dependency
* sec_common.h
*
* @par Note
* \n
* This API just opens the file specified by pszFileName in write mode and writes the contents specified by 
* pszDERCode into it. If the file doesn't exist, it may be created newly, but *No* specific access 
* permissions are set to the file by this API. Only default permissions as supported by the system API 
* will be set. If user wishes to save the contents of pszDERCode into a file with specific access permissions,
* then they can directly save pszDERCode into a file of their choice with required access permissions. 
*
* This API also doesn't do any validation of the pszFileName argument apart from normal NULL check. Any path 
* canonicalization, path and file name validations should be done by the user before passing to this API.
*
*
* This API doesn't do any additional activity apart from opening a file and saving the contents of pszDERCode to it. 
* It is suggested that users can use filesystem APIs directly than using this API. This API is supported only
* for historical reasons and backward compatibility. Users wanting to save sensitive data to a file should NOT use
* this API.
* \n
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UINT32 SEC_saveDERCodeToFile (SEC_CHAR* pszDERCode, SEC_UINT32 ulDERCodelen, SEC_CHAR* pszFileName);



/**
* @defgroup SEC_readDERCodeFromFile
* @ingroup sec_commonFunctions
* @par Prototype
* @code
* SEC_UINT32 SEC_readDERCodeFromFile (SEC_CHAR** pszDERCode,SEC_CHAR* pszFileName);
* @endcode
*
* @par Purpose
* To read DER code from a file.
*
* @par Description
* This function reads a DER code from a specified file and stores it into the given buffer.
*
* @param[in] pszFileName The file from which the DER code is to be read [N/A]
* @param[in] pszDERCode The buffer to store the DER code [N/A]
*
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 On successful operation [The number of bytes read from the file|N/A]
* @retval SEC_UNIT32 On failure [0|N/A]
*
* @par Dependency
* sec_common.h
*
* @par Note
*\n
* This API will allocate memory for the buffer which is storing the file content.
* The memory should be freed by using function "ipsi_free".
*
* @par Related Topics
* N/A
*/

//This function is used by SSL. Hence import define added here
PSELINKDLL SEC_UINT32 SEC_readDERCodeFromFile (SEC_CHAR** pszDERCode,SEC_CHAR* pszFileName);



/**
* @defgroup SEC_encodeBase64
* @ingroup sec_commonFunctions
* @par Prototype
* @code
* SEC_CHAR* SEC_encodeBase64 (SEC_CHAR* pucInBuf, SEC_UINT32 ulInBufLen );
* @endcode
*
* @par Purpose
* To encode the given DER code to base 64 format.
*
* @par Description
* This function converts the given DER code to base 64 format.
*
* @param[in] pucInBuf Input buffer [N/A]
* @param[in] ulInBufLen Length of input buffer [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_CHAR* On successful completion [Output buffer containg the data in base 64 format|N/A]
* @retval SEC_CHAR* On failure [SEC_NULL|N/A]
*
* @par Dependency
* sec_common.h
*
* @par Note
*\n
* The buffer allocated by this API for return value should be freed by using function "ipsi_free".
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_CHAR*  SEC_encodeBase64 (SEC_CHAR* pucInBuf,
								  SEC_UINT32 ulInBufLen );





/**
* @defgroup SEC_decodeBase64
* @ingroup sec_commonFunctions
* @par Prototype
* @code
* SEC_CHAR*  SEC_decodeBase64(SEC_CHAR*  pucInBuf, SEC_UINT32* pulOutBufLen );
* @endcode
*
* @par Purpose
* To decode from base64 to DER format.
*
* @par Description
* This function is used to decode from base 64 to DER format.
* In PEM_decode it is used for decoding the object from PEM to the desired format.
*
* @param[in] pucInBuf Input buffer [N/A]
* @param[out] pulOutBufLen buffer length [N/A]
*
* @retval SEC_CHAR* On successful completion [Output buffer containg the decoded data|N/A]
* @retval SEC_CHAR* In case of error [SEC_NULL|N/A]
*
* @par Dependency
* sec_common.h
*
* @par Note
*\n
* The buffer allocated by this API for return value should be freed by using function "ipsi_free".
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_CHAR*  SEC_decodeBase64(SEC_CHAR*  pucInBuf, SEC_UINT32* pulOutBufLen );


#ifdef	__cplusplus
}
#endif /* end of __cplusplus */

#endif /* end of _SEC_COMMON_H */

