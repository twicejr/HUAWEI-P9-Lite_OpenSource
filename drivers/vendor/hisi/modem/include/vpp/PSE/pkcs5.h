/*

                Copyright 2005, Huawei Technologies Co. Ltd.
                           ALL RIGHTS RESERVED

------------------------------------------------------------------------------

                              pkcs5.h

  Project Code: SeCertV100R001
  Date Created: 2005-06-30
   Module Name: PKCS5
        Author: Murali Krishna K, Anitha G
        Version      : 1
   @Description: This Module provides implementation of password-based 
		   cryptography,covering key derivation functions, encryption schemes,
		   message-authentication schemes and ASN.1 syntax identifying the
		   techniques.The random key used for Encrypting a given message /
		   Generating Message Authentication Code (MAC) for a given message,is
		   generated using the Password, Salt and Iteration Count.Supported
		   PKCS5 PBE Algorithms are CID_PBE_MD5_CBC & CID_PBE_SHA1WITHDESCBC.
		   Supported PKCS12 PBE Algorithms in PKCS5 module are
		   CID_PBE_SHAWITH128BITRC4,CID_PBE_SHAWITH40BITRC4,
		   CID_PBE_SHAWITH3KEY_TRIPLE_DESCBC,CID_PBE_SHAWITH2KEY_TRIPLE_DESCBC.
		   Supported PKCS5 Symmetric Algorithms are ALGID_DES_CBC &
		   ALGID_DES_EDE3_CBC and ALGID_AES128_CBC and ALGID_AES192_CBC 
		   and  ALGID_AES256_CBC. Suppoted MAC Generation Algorithms are
		   ALGID_HMAC_SHA1 & ALGID_HMAC_MD5 & ALGID_HMAC_SHA224 & 
		   ALGID_HMAC_SHA256 & ALGID_HMAC_SHA384 & ALGID_HMAC_SHA512. 
		   Supported PKCS5 Key Derivation
		   Algorithms are ALGID_HMAC_SHA1 & ALGID_HMAC_MD5 & ALGID_HMAC_SHA224 &
		   ALGID_HMAC_SHA256 & ALGID_HMAC_SHA384 & ALGID_HMAC_SHA512

*/

#include "ipsi_pse_build_conf.h"

#ifndef _IPSI_PKCS5_H_
#define _IPSI_PKCS5_H_

/* SeCert Headers */
#include "asn-types.h"
#include "sec_sys.h"
#include "x509_basictypes.h"
#include "ipsi_types.h"

#ifdef __cplusplus
extern "C" {
#endif



/** @defgroup pkcs5
* This section contains the pkcs5 Structures, Union, Enums and Functions
*/


/* Default Iteration Count value. If user gives negative or 0 iteration count,
	this default value will be used
 */
#define PKCS5_ITERATION_COUNT_DEFAULT	2048

/* Salt length for PKCS5_PBES1PARAM_S Structure when using PKCS5 PBE algorithms
     and it is default salt length when using PKCS12 PBE algorithms */
#define	PKCS5_PBES1_SALT_LEN			8

/* Default Salt length for PKCS5_PBES2PARAM_S Structure
 */
#define	PKCS5_PBES2_SALT_LEN			8

/* Maximum derived key length for ALGID_MD2 or ALGID_MD5 is 16, 
    used in PKCS5_deriveKey function */
#define PKCS5_MD2_MD5_DKLEN_LEN_MAX		16

/* Maximum derived key length for ALGID_SHA1 is 20,used in 
    PKCS5_deriveKey function*/
#define PKCS5_SHA1_DKLEN_LEN_MAX		20

/* When using PKCS5_PBES1PARAM_S structure in PKCS5_pbeEncrypt and 
    PKCS5_pbeDecrypt functions, Encryption Key Length for CID_PBE_MD5_CBC 
    algorithm or CID_PBE_SHA1WITHDESCBC algorithm is 8*/

#define PKCS5_PBES1_ENC_KEY_LEN			8

/* When using PKCS5_PBES1PARAM_S structure in PKCS5_pbeEncrypt and 
    PKCS5_pbeDecrypt functions, Initialization Vector Length for 
    CID_PBE_MD5_CBCalgorithm or CID_PBE_SHA1WITHDESCBC algorithm is 8 */

#define PKCS5_PBES1_IV_LEN				8

/* When using PKCS5_PBES1PARAM_S structure in PKCS5_pbeEncrypt and 
    PKCS5_pbeDecrypt functions,Derived Key Length for CID_PBE_MD5_CBC algorithm
    or CID_PBE_SHA1WITHDESCBC algorithm is 16. First 8 bytes of Derived Key is 
    used as Encryption Key and next 8 bytes is used as Initialization vector.*/
#define PKCS5_PBES1_DERIVEDKEY_LEN		16

/* Derived Key Length for CID_PBE_SHAWITH40BITRC4 is 5
 */
#define PKCS5_KEY_LEN_40BIT_RC4			5

/* Derived Key Length for CID_PBE_SHAWITH128BITRC4 is 16
 */
#define PKCS5_KEY_LEN_128BIT_RC4		16

/* Derived Key Length for CID_PBE_SHAWITH40BIT_RC2CBC is 5
 */
#define PKCS5_KEY_LEN_40BIT_RC2CBC			5

/* Derived Key Length for CID_PBE_SHAWITH128BIT_RC2CBC is 16
 */
#define PKCS5_KEY_LEN_128BIT_RC2CBC			16

/* When calling PKCS5_p12KeyIVGen function,
    the fallowing three ID's identifies whether output buffer is for 
    encryption key or for IV or for MAC key*/

/* this is used as input for generating encryption key
 */
#define PKCS12_CID_TYPE1 1

/* this is used as input for generating Initialzation Vector
 */
#define PKCS12_CID_TYPE2 2

/* this is used as input for generating Mac Key
 */
#define PKCS12_CID_TYPE3 3

#define PKCS5_RAND_MAX_RANGE 2024

/** @defgroup pkcs5Enums
* @ingroup pkcs5
* This section contains the pkcs5 Enums
*/


/** This Enum is used to identify Specified Salt and Salt from any other source.
	It is used in PKCS5_PBKDF2SALT_S structure
 */
/**
* @defgroup PKCS5_PBKDF2SALT_E
* @ingroup pkcs5Enums
* @par Prototype
* @code
* typedef enum enPKCS5_PBKDF2SALT
* {
*   PKCS5_SALT_SOURCE_SPECIFIED,
*   PKCS5_SALT_SOURCE_OTHER
* } PKCS5_PBKDF2SALT_E;
* @endcode
*
* @datastruct PKCS5_SALT_SOURCE_SPECIFIED Enum for Specified Salt.
* @datastruct PKCS5_SALT_SOURCE_OTHER Enum for Salt from any other Source.
*/
typedef enum enPKCS5_PBKDF2SALT
{
    PKCS5_SALT_SOURCE_SPECIFIED,		/* Enum for Specified Salt */

    PKCS5_SALT_SOURCE_OTHER			/* Enum for Salt from any other Source */

} PKCS5_PBKDF2SALT_E;

/* It is a flag to Identify PKCS5_PBES1PARAM_S and PKCS5_PBES2PARAM_S.If 
    PKCS5_PBES1_TYPE,then PKCS5_deriveKey() is for PKCS5_PBES1PARAM_S.If 
    PKCS5_PBES2_TYPE,then PKCS5_deriveKey() is for PKCS5_PBES2PARAM_S.	If 
    ulKDFAlg in PKCS5_deriveKey() function is ALGID_SHA1 or ALGID_MD5, then 
    enFlag in PKCS5_deriveKey() should be PKCS5_PBES1_TYPE.If ulKDFAlg is 
    ALGID_HMAC_SHA1 or ALGID_HMAC_MD5 or ALGID_HMAC_SHA224 or ALGID_HMAC_SHA256
     or ALGID_HMAC_SHA384 or ALGID_HMAC_SHA512,then enFlag should be
    PKCS5_PBES2_TYPE */
/**
* @defgroup PKCS5_PBE_TYPE_E
* @ingroup pkcs5Enums
* @par Prototype
* @code
* typedef enum enPKCS5_PBE_TYPE
* {
*	PKCS5_PBES1_TYPE,
*	PKCS5_PBES2_TYPE
* } PKCS5_PBE_TYPE_E;
* @endcode
*
* @datastruct PKCS5_PBES1_TYPE To identify PKCS5_PBES1PARAM_S.
* @datastruct PKCS5_PBES2_TYPE To identify PKCS5_PBES2PARAM_S.
*/
typedef enum enPKCS5_PBE_TYPE
{
    PKCS5_PBES1_TYPE,       /* To Identify PKCS5_PBES1PARAM_S */
    PKCS5_PBES2_TYPE        /* To Identify PKCS5_PBES2PARAM_S */
} PKCS5_PBE_TYPE_E;


/**
* @defgroup PKCS5_ENCDEC_E
* @ingroup pkcs5Enums
* @par Prototype
* @code
* typedef enum enPKCS5_ENCDEC
* {
*		PKCS5_ENCRYPT = 1,
*		PKCS5_DECRYPT = 2
* } PKCS5_ENCDEC_E;
* @endcode
*
* @datastruct PKCS5_ENCRYPT Denotes PKCS5 Encryption.
* @datastruct PKCS5_DECRYPT Denotes PKCS5 Decryption.
*/
typedef enum enPKCS5_ENCDEC
{
    PKCS5_ENCRYPT = 1,
    PKCS5_DECRYPT = 2
} PKCS5_ENCDEC_E;


/** @defgroup pkcs5Union
* @ingroup pkcs5
* This section contains the pkcs5 Union
*/

/** Union of Specified Salt and Salt from any other source.
	It is used in PKCS5_PBKDF2SALT_S structure
 */
/**
* @defgroup PKCS5_PBKDF2SALT_U
* @ingroup pkcs5Union
* @par Prototype
* @code
* typedef union unPKCS5_PBKDF2SALT
* {
*   SEC_AsnOcts_S*        pstSpecified;
*   SEC_ALG_IDENTIFIER_S* pstOtherSource;
* } PKCS5_PBKDF2SALT_U;
* @endcode
*
* @datastruct pstSpecified Pointer to SEC_AsnOcts_S structure which 
    holds specified salt.
* @datastruct pstOtherSource Pointer to SEC_ALG_IDENTIFIER_S 
    strcuture which holds Salt from any other source.*/
typedef union unPKCS5_PBKDF2SALT
{

    SEC_AsnOcts_S* pstSpecified; /* Pointer to SEC_AsnOcts_S structure 
                                                which holds specified salt */

    SEC_ALG_IDENTIFIER_S* pstOtherSource; /* Pointer to SEC_ALG_IDENTIFIER_S 
                                            strcuture which holds Salt from 
                                            any other source */
} PKCS5_PBKDF2SALT_U;



/** @defgroup pkcs5Structures
* @ingroup pkcs5
* This section contains the pkcs5 Structures
*/

/** Structure that holds Salt.Salt is an index into a large set of 
    keys derived from the password, and need not be kept secret.Salt may be a
    specified one or it may be from any other source. It is used in 
    PKCS5_PBKDF2PARAM_S structure*/
/**
* @defgroup PKCS5_PBKDF2SALT_S
* @ingroup pkcs5Structures
* @par Prototype
* @code
* typedef struct stPKCS5_PBKDF2SALT
* {
*	PKCS5_PBKDF2SALT_E enSaltType;
*	PKCS5_PBKDF2SALT_U unSalt;
* } PKCS5_PBKDF2SALT_S;
* @endcode
*
* @datastruct enSaltType Enum to choose spcified salt or salt 
    from any other source.
* @datastruct unSalt Union of specified salt and salt from any other source.
*/
typedef struct stPKCS5_PBKDF2SALT			/* CHOICE */
{
    PKCS5_PBKDF2SALT_E enSaltType; /* Enum to choose spcified salt or 
                                                salt from any other source */
    PKCS5_PBKDF2SALT_U unSalt; /* Union of specified salt and salt 
                                                    from any other source */
} PKCS5_PBKDF2SALT_S;


/** Structure that holds Salt,Iteration Count,Derived Key Length and Pseudo 
* Random Function algorithm identifier.
* This structure is used in PKCS5_PBES2PARAM_S structure
*/
/**
* @defgroup PKCS5_PBKDF2PARAM_S
* @ingroup pkcs5Structures
* @par Prototype
* @code
* typedef struct stPKCS5_PBKDF2Param
* {
*	PKCS5_PBKDF2SALT_S*   pstSalt;
*	SEC_INT32             iIter;
*	SEC_INT32*            piKeyLength;
*	SEC_ALG_IDENTIFIER_S* pstPrf;
* } PKCS5_PBKDF2PARAM_S;
* @endcode
*
* @datastruct pstSalt Pointer to PKCS5_PBKDF2SALT_S structure which contains 
* Salt. @datastruct iIter Iteration Count.
* @datastruct piKeyLength Derived Key Length (Optional).
* @datastruct pstPrf Pointer to Pseudo Random Function,Here Pseudo 
* Random Function is underlying hmac function. DEFAULT is ALGID_HMAC_SHA1.
*/
typedef struct stPKCS5_PBKDF2Param			/* SEQUENCE */
{
    PKCS5_PBKDF2SALT_S* pstSalt;/* Pointer to PKCS5_PBKDF2SALT_S 
                                            structure which contains Salt */
    SEC_INT32 iIter;/* Iteration Count */
    SEC_INT32* piKeyLength;/* Derived Key Length (Optional) */
    SEC_ALG_IDENTIFIER_S* pstPrf;/* pointer to Pseudo Random Function,
                                Here Pseudo Random Functionis underlying 
                                hmac function. DEFAULT is ALGID_HMAC_SHA1 */
} PKCS5_PBKDF2PARAM_S;

/** Structure that holds Salt and Iteration Count.An iteration count has 
    traditionally served the purpose of increasing the cost of producing keys 
    from a password,thereby also increasing the difficulty of attack.Salt can 
    be created using Pseudo Ramdom generator.Here API for Pseudo Random 
    Generation is CRYPT_random()*/
/**
* @defgroup PKCS5_PBES1PARAM_S
* @ingroup pkcs5Structures
* @par Prototype
* @code
* typedef struct stPKCS5_PBES1Param
* {
*	SEC_AsnOcts_S salt;
*	SEC_INT32     iIter;
* } PKCS5_PBES1PARAM_S;
* @endcode
*
* @datastruct salt Salt structure containing octet string and octet length.
* @datastruct iIter Iteration Count.
*/
typedef struct stPKCS5_PBES1Param			/* SEQUENCE */
{
    SEC_AsnOcts_S salt;/* Salt structure containing octet string 
                                    and octet length */
    SEC_INT32 iIter;/* Iteration Count */
} PKCS5_PBES1PARAM_S;

/* Stucture that holds Key Derivation function and 
* (Encryption or MAC Generation Algorithm).
* Key Derivation Function inturn contains Salt,Iteration Count,
* Derived Key Length and Pseudo Random Function algorithm.
*/
/**
* @defgroup PKCS5_PBES2PARAM_S
* @ingroup pkcs5Structures
* @par Prototype
* @code
* typedef struct stPKCS5_PBES2Param
* {
*	SEC_ALG_IDENTIFIER_S* pstKDF;
*	SEC_ALG_IDENTIFIER_S* pstAlgScheme;
* } PKCS5_PBES2PARAM_S;
* @endcode
*
* @datastruct pstKDF Pointer to key derivation function.
* @datastruct pstAlgScheme Pointer to (Encryption / MAC generation) 
* Algorithm Scheme. This alg id is either for Encryption or for Mac generation.
*/
typedef struct stPKCS5_PBES2Param   /* SEQUENCE */
{
    SEC_ALG_IDENTIFIER_S* pstKDF;       /*pointer to key derivation function*/

    SEC_ALG_IDENTIFIER_S* pstAlgScheme;    /* Pointer to 
                                    (Encryption / MAC generation) Algorithm 
                                    Scheme.This alg id is either for Encryption
                                    or for Mac generation.*/
} PKCS5_PBES2PARAM_S;


/** @defgroup pkcs5Functions
* @ingroup pkcs5
* This section contains the pkcs5 Functions
*/


/**
* @defgroup PKCS5_genPBES1Param
* @ingroup pkcs5Functions
* @par Prototype
* @code
* PKCS5_PBES1PARAM_S* PKCS5_genPBES1Param(void);
* @endcode
*
* @par Purpose
* To generate Salt and Iteration Count and add them to the 
* PKCS5_PBES1PARAM_S structure.
*
* @par Description
* This function generates Salt and Iteration Count and adds them to 
* the PKCS5_PBES1PARAM_S structure. User can call this function when he 
* does not provide any input for Salt and Iteration Count.
* @param[in] N/A N/A [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS5_PBES1PARAM_S* Pointer to PKCS5_PBES1PARAM_S structure 
* containing Salt and Iteration Count [PKCS5_PBES1PARAM_S*|N/A]
* @retval PKCS5_PBES1PARAM_S* If it failed to generate the random number for 
* iteration or if it failed to generate random number for count salt or if
* memory allocation fails [SEC_NULL|N/A]
* @par Dependency
* pkcs5.h
*
* @par Note
*
* 1) Generated Salt(octet string) is of length 8.\n
* 2) PKCS5_PBES1PARAM_S structure generated can be used as input for 
* PKCS5_pbeEncrypt and PKCS5_pbeDecrypt functions.
* @par Related Topics
* N/A
*
* 
*/

PSELINKDLL PKCS5_PBES1PARAM_S* PKCS5_genPBES1Param(void);


/**
* @defgroup PKCS5_setPBES1Param
* @ingroup pkcs5Functions
* @par Prototype
* @code
* SEC_UINT32 PKCS5_setPBES1Param (
* const SEC_UCHAR* pucSalt, SEC_UINT32 ulSaltLen,
* SEC_INT32 iIter, PKCS5_PBES1PARAM_S* pstPBE1Param);
* @endcode
*
* @par Purpose
* To set Salt and Iteration Count to the PKCS5_PBES1PARAM_S structure.
*
* @par Description
* This function sets Salt and Iteration Count to the PKCS5_PBES1PARAM_S 
* structure.Salt and Iteration Count have to be
* provided as input to this API.First user has to allocate memory for 
* outer structure. that is for PKCS5_PBES1PARAM_S structure.
*
* @param[in] pucSalt Pointer to Salt, which is an octet string [N/A]
* @param[in] ulSaltLen Length of Salt [N/A]
* @param[in] iIter Iteration Count.If it is less than or equal to zero,default 
* value of 2048 will be set as iteration count in PKCS5_PBES1PARAM_S 
* structure [N/A] 
* @param[out] pstPBE1Param Pointer to PKCS5_PBES1PARAM_S. structure 
* that holds Salt and Iteration Count [N/A]
*
* @retval SEC_UINT32 If successfully sets salt and iteration 
* count [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If memory allocation fails [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If one of the argument passed is NULL or invalid
* [SEC_ERR_INVALID_ARG|N/A]
*
* @par Dependency
* pkcs5.h
*
* @par Note
*
* 1) Salt should be of length 8 for CID_PBE_MD5WITHDESCBC,
* CID_PBE_SHA1WITHDESCBC.\n
* 2) Output parameter PKCS5_PBES1PARAM_S* can be used as input for 
* PKCS5_pbeEncrypt and PKCS5_pbeDecrypt functions. PKCS7,PKCS8 and 
* PKCS12 modules also uses this function to set.

* @par Related Topics
* N/A
*
* 
*/

PSELINKDLL SEC_UINT32 PKCS5_setPBES1Param (const SEC_UCHAR* pucSalt,
    SEC_UINT32 ulSaltLen, SEC_INT32 iIter, PKCS5_PBES1PARAM_S* pstPBE1Param);

/**
* @defgroup PKCS5_getSaltFromPBES1Param
* @ingroup pkcs5Functions
* @par Prototype
* @code
* SEC_AsnOcts_S* PKCS5_getSaltFromPBES1Param(PKCS5_PBES1PARAM_S* pstPBE1Param);
* @endcode
*
* @par Purpose
* To retrieve the salt value from the PKCS5_PBES1PARAM_S structure
* and to return pointer to Salt Structure.
*
* @par Description
* This function retrieves the salt value from the PKCS5_PBES1PARAM_S structure
* and returns pointer to Salt Structure(pointer to Structure contaning salt 
* value and salt length that is pointer to SEC_AsnOcts_S).

* @param[in] pstPBE1Param The structure from which the salt must be
* retrieved [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_AsnOcts_S* Salt(Pointer to SEC_AsnOcts_S structure) 
* [SEC_AsnOcts_S*|N/A]
* @retval SEC_AsnOcts_S* If the argument passed is NULL [SEC_NULL|N/A]
*
* @par Dependency
* pkcs5.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_AsnOcts_S* PKCS5_getSaltFromPBES1Param(
                    PKCS5_PBES1PARAM_S* pstPBE1Param);

/**
* @defgroup PKCS5_getIterFromPBES1Param
* @ingroup pkcs5Functions
* @par Prototype
* @code
* SEC_INT32 PKCS5_getIterFromPBES1Param (
* const PKCS5_PBES1PARAM_S* pstPBE1Param);
* @endcode
*
* @par Purpose
* To extract and return the iteration count from PKCS5_PBES1PARAM_S structure.
*
* @par Description
* This function extracts and returns the iteration count from
* PKCS5_PBES1PARAM_S structure.
*
* @param[in] pstPBE1Param The structure from which the iteration count 
* must be retrieved [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_INT32 Iteration Count [SEC_INT32|N/A]
* @retval SEC_INT32 If the argument passed is NULL [SEC_ERROR|N/A]
*
* @par Dependency
* pkcs5.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_INT32 PKCS5_getIterFromPBES1Param (
                    const PKCS5_PBES1PARAM_S* pstPBE1Param);


/**
* @defgroup PKCS5_genPBES2Param
* @ingroup pkcs5Functions
* @par Prototype
* @code
* PKCS5_PBES2PARAM_S* PKCS5_genPBES2Param (
* SEC_UINT32 ulKDFAlgId, SEC_UINT32 ulAlgId);
* @endcode
*
* @par Purpose
* To generate the Salt,Iteration Count and Initialization Vector(IV)
* (IV for PKCS5 Encryption Algorithms)
* and adds them to PKCS5_PBES2PARAM_S structure.
*
* @par Description
* This function generates the Salt,Iteration Count and Initialization 
* Vector(IV)(IV for PKCS5 Encryption Algorithms) and adds them to 
* PKCS5_PBES2PARAM_S structure. This function also adds Derived key length, 
* PRF algorithm,Encryption/MAC generation Algorithm to the 
* PKCS5_PBES2PARAM_S structure.
*
* @param[in] ulKDFAlgId	Key Derivation Algorithm, Possible values are 
    ALGID_HMAC_SHA1 
    ALGID_HMAC_SHA224
    ALGID_HMAC_SHA256
    ALGID_HMAC_SHA384
    ALGID_HMAC_SHA512 and ALGID_HMAC_MD5 [N/A]
* @param[in] ulAlgId Enum for Encryption algorithm or MAC generation algorithm.
* It can be (ALGID_DES_CBC or
* ALGID_DES_EDE3_CBC or ALGID_AES128_CBC or ALGID_AES192_CBC 
* or ALGID_AES256_CBC) If it is for 
* Encryption/Decryption or (ALGID_HMAC_SHA1 or ALGID_HMAC_MD5 or 
* ALGID_HMAC_SHA224
* ALGID_HMAC_SHA256 or ALGID_HMAC_SHA384 or ALGID_HMAC_SHA512) if it is for MAC
* Generation/Verification [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS5_PBES2PARAM_S* Pointer to PKCS5_PBES2PARAM_S* structure 
* [PKCS5_PBES2PARAM_S*|N/A]
* @retval PKCS5_PBES2PARAM_S* If memory allocation fails or if 
* Random Number generation fails.
* (Random Number Generation is for Salt, Iteration Count and IV) [SEC_NULL|N/A]
*
* @par Dependency
* pkcs5.h
*
* @par Note
*
* 1) Supported PRF algorithms are ALGID_HMAC_SHA1 and ALGID_HMAC_MD5 
* and ALGID_HMAC_SHA224 and
* ALGID_HMAC_SHA256 and ALGID_HMAC_SHA384 and ALGID_HMAC_SHA512.\n
* 2) Supported Encryption algorithms are ALGID_DES_CBC and ALGID_DES_EDE3_CBC 
* and ALGID_AES128_CBC
* and ALGID_AES192_CBC and ALGID_AES256_CBC.\n
* 3) Supported MAC generation algorithms are ALGID_HMAC_SHA1 and 
* ALGID_HMAC_MD5 and ALGID_HMAC_SHA224
* ALGID_HMAC_SHA256 and ALGID_HMAC_SHA384 and ALGID_HMAC_SHA512.\n
* 4) Generated Salt(an octet string) is of length 8.\n
* 5) PKCS5_PBES2PARAM_S structure generated can be used as input for 
* PKCS5_pbeEncrypt, PKCS5_pbeDecrypt,
* PKCS5_generateMAC and PKCS5_verifyMAC functions.
*
* @par Related Topics
* N/A
*
* 
*/

PSELINKDLL PKCS5_PBES2PARAM_S* PKCS5_genPBES2Param (SEC_UINT32 ulKDFAlgId,
                                                    SEC_UINT32 ulAlgId);


/**
* @defgroup PKCS5_setPBES2Param
* @ingroup pkcs5Functions
* @par Prototype
* @code
* SEC_UINT32	PKCS5_setPBES2Param(const SEC_UCHAR* pucSalt, 
*SEC_UINT32 ulSaltLen,
* SEC_INT32 iIter, SEC_UINT32 ulDKLen, SEC_UINT32 ulKDFAlgId,
* SEC_UINT32 ulAlgId, PKCS5_PBES2PARAM_S* pstPBES2Param);
* @endcode
*
* @par Purpose
* To set Salt, Iteration Count, derived key length, PRF algorithm and 
*Encryption/MAC generation Algorithm
* to the PKCS5_PBES2PARAM_S structure with the values passed to them as input.
*
* @par Description
* This function sets Salt, Iteration Count, derived key length, PRF algorithm 
*and Encryption/MAC generation Algorithm
* to the PKCS5_PBES2PARAM_S structure with the values passed to them as input.
*This function generates Initialization
* Vector(IV) for PKCS5 Encryption Algorithms and adds it to the 
*PKCS5_PBES2PARAM_S structure.
*
* @param[in] pucSalt The salt which is a set of octets [N/A]
* @param[in] ulSaltLen The length of the salt value [N/A]
* @param[in] iIter The iteration count value,If it is less than or equal 
* to zero,default value of 2048 is to be set in
* PKCS5_PBES2PARAM_S structure [N/A]
* @param[in] ulDKLen (OPTIONAL) The length of the derived key.If user gives 
* invalid input, PKCS5_setPBES2Param function
* sets the actual key length obtained if ulAlgId is Symmetric Algorithm or
* sets the default key length if ulAlgId
* is MAC algorithm.MAC Generation Algorithms ALGID_HMAC_SHA1 and 
* ALGID_HMAC_MD5 and ALGID_HMAC_SHA224 
* and ALGID_HMAC_SHA256 and ALGID_HMAC_SHA384 and ALGID_HMAC_SHA512 
* can have variable key
* lengths.If ulAlgId is any one of ALGID_HMAC_SHA1 and ALGID_HMAC_MD5 and 
* ALGID_HMAC_SHA224 
* and ALGID_HMAC_SHA256 and ALGID_HMAC_SHA384 and ALGID_HMAC_SHA512 
* and if the user gives 0 input for
* ulDKLen,default key length will be set. Default Key Length is calculated 
* using CRYPT_HMAC_size(ulKDFAlgId) [N/A]
* @param[in] ulKDFAlgId	The algorithm that is used to generate a key. 
* Possible valuee are ALGID_HMAC_SHA1 and
* ALGID_HMAC_MD5 and ALGID_HMAC_SHA224 
* and ALGID_HMAC_SHA256 and ALGID_HMAC_SHA384 and ALGID_HMAC_SHA512[N/A]
* @param[in] ulAlgId Encryption Algorithm or Message AuthScheme algorithm.
* It can be (ALGID_DES_CBC or ALGID_DES_EDE3_CBC
* or ALGID_AES128_CBC or ALGID_AES192_CBC or  ALGID_AES256_CBC)
* if it is for encryption or (ALGID_HMAC_SHA1 or ALGID_HMAC_MD5 or 
* ALGID_HMAC_SHA224 
* or ALGID_HMAC_SHA256 or ALGID_HMAC_SHA384 or ALGID_HMAC_SHA512) 
* if it is for MAC generation [N/A]
* @param[out] pstPBES2Param	Pointer to PKCS5_PBES2PARAM_S structure that 
* holds Key Derivation function and Encryption
* Algorithm Identifier/MAC Gegeneration Algorithm Identifier [N/A]
*
* @retval SEC_UINT32 On successfully setting the PKCS5_PBES2PARAM_S 
* structure [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If any of the mandatory input passed is NULL or 
* invalid [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If OID not available for corresponding CID 
* [SEC_ERR_INVALID_CID|N/A]
* @retval SEC_UINT32 If failed to generate the random number for IV 
* [SEC_ERR_RANDOM_FAILED|N/A]
* @retval SEC_UINT32 If passing algorithm is invalid [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 If dup or copy function fails 
* [SEC_ERR_DATA_COPY_FAILED|N/A]
*
* @par Dependency
* pkcs5.h
*
* @par Note
*
* 1) Supported Key Derivation Algorithms are (ALGID_HMAC_SHA1 and 
* ALGID_HMAC_MD5 nd ALGID_HMAC_SHA224 
* and ALGID_HMAC_SHA256 and ALGID_HMAC_SHA384 and ALGID_HMAC_SHA512).\n
* 2) Supported Encryption algorithms are (ALGID_DES_CBC and ALGID_DES_EDE3_CBC 
* and ALGID_AES128_CBC and ALGID_AES192_CBC and  ALGID_AES256_CBC).\n
* 3) Supported MAC generation algorithms are (ALGID_HMAC_SHA1 and 
* ALGID_HMAC_MD5 nd ALGID_HMAC_SHA224 and ALGID_HMAC_SHA256 and 
* ALGID_HMAC_SHA384 and ALGID_HMAC_SHA512).\n
* 4) PKCS5_PBES2PARAM_S structure generated can be used as input for
* PKCS5_pbeEncrypt and PKCS5_pbeDecrypt,
* PKCS5_generateMAC and PKCS5_verifyMAC functions.
*
* @par Related Topics
* N/A
*
* 
*/

PSELINKDLL SEC_UINT32	PKCS5_setPBES2Param(const SEC_UCHAR* pucSalt,
    SEC_UINT32 ulSaltLen, SEC_INT32 iIter, SEC_UINT32 ulDKLen,
    SEC_UINT32 ulKDFAlgId, SEC_UINT32 ulAlgId,
    PKCS5_PBES2PARAM_S* pstPBES2Param);


/**
* @defgroup PKCS5_getSaltFromPBES2Param
* @ingroup pkcs5Functions
* @par Prototype
* @code
* SEC_AsnOcts_S* PKCS5_getSaltFromPBES2Param(
* const PKCS5_PBES2PARAM_S* pstPBES2Param);
* @endcode
*
* @par Purpose
* To retrieve the salt value from the PKCS5_PBES2PARAM_S structure and return
* pointer to Salt Structure.
*
* @par Description
* This function retrieves the salt value from the PKCS5_PBES2PARAM_S structure
* and returns pointer to Salt Structure
* (pointer to Structure contaning salt value and salt length that is pointer
* to SEC_AsnOcts_S).
*
* @param[in] pstPBES2Param The structure from which the salt has 
* to be retrieved [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_AsnOcts_S* SALT(Pointer to SEC_AsnOcts_S structure) 
* [SEC_AsnOcts_S*|N/A]
* @retval SEC_AsnOcts_S* If the argument passed is NULL or invalid 
* [SEC_NULL|N/A]
*
* @par Dependency
* pkcs5.h
*
* @par Note
*
* PKCS5_pbeEncrypt,PKCS5_pbeDecrypt,PKCS5_generateMAC or PKCS5_verifyMAC 
* functions use this function to get Salt from
* PKCS5_PBES2PARAM_S structure.
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_AsnOcts_S* PKCS5_getSaltFromPBES2Param(
                    const PKCS5_PBES2PARAM_S* pstPBES2Param);

/**
* @defgroup PKCS5_getIterFromPBES2Param
* @ingroup pkcs5Functions
* @par Prototype
* @code
* SEC_INT32 PKCS5_getIterFromPBES2Param(
* const PKCS5_PBES2PARAM_S* pstPBES2Param);
* @endcode
*
* @par Purpose
* To extract and return the iteration count from PKCS5_PBES2PARAM_S structure.
*
* @par Description
* This function extracts and returns the iteration count from 
* PKCS5_PBES2PARAM_S structure.
*
* @param[in] pstPBES2Param The structure from which the iteration count 
* must be retrieved [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_INT32 The iteration count [SEC_INT32|N/A]
* @retval SEC_INT32 If the argument passed is NULL or invalid [SEC_ERROR|N/A]
*
* @par Dependency
* pkcs5.h
*
* @par Note
*
* PKCS5_pbeEncrypt,PKCS5_pbeDecrypt,PKCS5_generateMAC and PKCS5_verifyMAC 
* functions uses this function to get
* iteration count from PKCS5_PBES2PARAM_S structure.
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_INT32 PKCS5_getIterFromPBES2Param(
                    const PKCS5_PBES2PARAM_S* pstPBES2Param);


/**
* @defgroup PKCS5_getDKLenFromPBES2Param
* @ingroup pkcs5Functions
* @par Prototype
* @code
* SEC_INT32 PKCS5_getDKLenFromPBES2Param (
* const PKCS5_PBES2PARAM_S* pstPBES2Param);
* @endcode
*
* @par Purpose
* To extract and return the derived key length from 
* PKCS5_PBES2PARAM_S structure.
*
* @par Description
* This function extracts and returns the derived key length from 
* PKCS5_PBES2PARAM_S structure. This expects  Derived KeyLength 
* to be present in PBKDF2 parameter. If it is not, then 
* SEC_ERROR will be returned.
*
* @param[in] pstPBES2Param The structure from which the Derived Key 
* Length must be retrieved [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_INT32 Derived Key Length [SEC_INT32|N/A]
* @retval SEC_INT32 If the argument passed is NULL or invalid [SEC_ERROR|N/A]
*
* @par Dependency
* pkcs5.h
*
* @par Note
*
* PKCS5_pbeEncrypt,PKCS5_pbeDecrypt,PKCS5_generateMAC and PKCS5_verifyMAC 
* functions uses this function to get
* derived key length from PKCS5_PBES2PARAM_S structure.
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_INT32 PKCS5_getDKLenFromPBES2Param (
                    const PKCS5_PBES2PARAM_S* pstPBES2Param);

/**
* @defgroup PKCS5_getPRFOidFromPBES2Param
* @ingroup pkcs5Functions
* @par Prototype
* @code
* SEC_AsnOid_S* PKCS5_getPRFOidFromPBES2Param (
* const PKCS5_PBES2PARAM_S* pstPBES2Param);
* @endcode
*
* @par Purpose
* To extract and return the Oid for Pseudo Random Function(PRF) 
* algorithm used in PKCS5_PBES2PARAM_S Structure.
*
* @par Description
* This function extracts and returns the Oid for Pseudo Random Function(PRF) 
* algorithm used in PKCS5_PBES2PARAM_S Structure.
*
* @param[in] pstPBES2Param The structure from which the PRF Oid has to be 
* retrieved [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_AsnOid_S* Pointer to Pseudo Random Function Oid 
* [SEC_AsnOid_S*|N/A]
* @retval SEC_AsnOid_S* If the argument passed is NULL or invalid [SEC_NULL|N/A]
*
* @par Dependency
* pkcs5.h
*
* @par Note
*
* PKCS5_pbeEncrypt,PKCS5_pbeDecrypt,PKCS5_generateMAC and PKCS5_verifyMAC
* functions uses this function to get
* Oid for PRF algorithm from PKCS5_PBES2PARAM_S structure.
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_AsnOid_S* PKCS5_getPRFOidFromPBES2Param (
                    const PKCS5_PBES2PARAM_S* pstPBES2Param);


/**
* @defgroup PKCS5_getAlgSchemeOidFromPBES2Param
* @ingroup pkcs5Functions
* @par Prototype
* @code
* SEC_AsnOid_S* PKCS5_getAlgSchemeOidFromPBES2Param(
                            const PKCS5_PBES2PARAM_S* pstPBES2Param);
* @endcode
*
* @par Purpose
*To return the Oid for Encryption algorithm or MAC Generation Algorithm used in
* PKCS5_PBES2PARAM_S structure.
*
* @par Description
* This function extracts and returns the Oid for Encryption algorithm or MAC 
* Generation Algorithm used in
* PKCS5_PBES2PARAM_S structure.
*
* @param[in] pstPBES2Param Structure from which the Oid for Encryption 
* Algorithm/MAC Generation algorithm has to be retrieved [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_AsnOid_S*	Pointer to Encryption or MAC Algorithm Oid 
* [SEC_AsnOid_S*|N/A]
* @retval SEC_AsnOid_S* If the argument passed is NULL or invalid [SEC_NULL|N/A]
*
* @par Dependency
* pkcs5.h
*
* @par Note
*
* PKCS5_pbeEncrypt,PKCS5_pbeDecrypt,PKCS5_generateMAC and PKCS5_verifyMAC 
* functions uses this function to get Oid for
* AlgScheme from PKCS5_PBES2PARAM_S structure.
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_AsnOid_S* PKCS5_getAlgSchemeOidFromPBES2Param(
                    const PKCS5_PBES2PARAM_S* pstPBES2Param);




/**
* @defgroup PKCS5_generateMAC
* @ingroup pkcs5Functions
* @par Prototype
* @code
* SEC_UINT32 PKCS5_generateMAC (SEC_UCHAR* pucPassword, SEC_UINT32 ulPwdLen,
* SEC_UCHAR* pucPlainTxt, SEC_UINT32 ulPlainTxtLen, 
* const PKCS5_PBES2PARAM_S* pstPBES2Param,
* SEC_UCHAR* pucMAC,SEC_UINT32* pulMACLen);
* @endcode
*
* @par Purpose
* To generate Message Authentication Code(MAC) for the given message using the
* derived key and message authentication scheme.
*
* @par Description
* This function generates Message Authentication Code(MAC) for the given 
* message using the derived key and message authentication scheme.Here the 
* derived key is generated using Password,Salt and Iteration Count.A message
* authentication code (MAC) is an authentication tag (also called a checksum)
* derived by applying an authentication scheme, together with a 
* secret key, to a message.
*
* @param[in] pucPassword Pointer to password which is used as the base key
* in generating the key [N/A]
* @param[in] ulPwdLen Length of the password [N/A]
* @param[in] pucPlainTxt Pointer to plain text [N/A]
* @param[in] ulPlainTxtLen Length of the plain text [N/A]
* @param[in] pstPBES2Param Pointer to structure that holds Key Derivation 
* Function and MAC Generation Algorithm [N/A]
* @param[out] pucMAC Pointer to Message authentication code [N/A]
* @param[out] pulMACLen The length of Message Authentication Code [N/A]
*
* @retval SEC_UINT32 If successfully generates MAC [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If Salt value retrieved is NULL, when calling get function
* for salt [SEC_PKCS5_ERR_GET_SALT_FAILED|N/A]
* @retval SEC_UINT32 If one of the argument passed is NULL or invalid 
* [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If OID for PRF algorithm or OID for MAC generation 
* algorithm retrieved using get functions is * NULL [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 If CID corresponding to OID is not present 
* [SEC_ERR_INVALID_OID|N/A]
* @retval SEC_UINT32 If the field piKeyLength in PKCS5_PBKDF2PARAM_S of *
* PKCS5_PBES2PARAM_S is not passed, then we take derived key length *
* equal to the key derivation algorithm key size. If it is passed, and *
* its value is zero then an error [SEC_ERR_INVALID_KEY_LEN|N/A] will be *
* returned.(From PKCS #5 v2.0: The maximum key length allowed depends on *
* the implementation; it is expected that implementation profiles may further*
* constrain the bounds).                                                     *
* @retval SEC_UINT32 If context values are not correct 
* [SEC_CRYPT_ERR_INVALID_CTX|N/A]
*
* @par Dependency
* pkcs5.h
*
* @par Note
*
* Supported key derivation algorithms are ALGID_HMAC_SHA1 or ALGID_HMAC_MD5
* and ALGID_HMAC_SHA224 
* and ALGID_HMAC_SHA256 and ALGID_HMAC_SHA384 and ALGID_HMAC_SHA512 
* and Supported MAC generation algorithms are
* ALGID_HMAC_SHA1 or ALGID_HMAC_MD5 and ALGID_HMAC_SHA224 
* and ALGID_HMAC_SHA256 and ALGID_HMAC_SHA384 and ALGID_HMAC_SHA512.
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_UINT32  PKCS5_generateMAC (SEC_UCHAR* pucPassword,
    SEC_UINT32 ulPwdLen, SEC_UCHAR* pucPlainTxt, SEC_UINT32 ulPlainTxtLen,
    const PKCS5_PBES2PARAM_S* pstPBES2Param, SEC_UCHAR* pucMAC, 
    SEC_UINT32* pulMACLen);

/**
* @defgroup PKCS5_verifyMAC
* @ingroup pkcs5Functions
* @par Prototype
* @code
* SEC_UINT32  PKCS5_verifyMAC (SEC_UCHAR* pucPassword,
* SEC_UINT32 ulPwdLen,
* const PKCS5_PBES2PARAM_S* pstPBES2Param,
* SEC_UCHAR* pucPlainTxt,
* SEC_UINT32 ulPlainTxtLen,
* SEC_UCHAR* pucMAC,
* SEC_UINT32 ulMACLen
* );
* @endcode
*
* @par Purpose
* To verify the Message Authentication Code(MAC) for the given message using 
* the derived key and message authentication scheme.
*
* @par Description
* This function verifies the Message Authentication Code(MAC) for 
* the given message using the derived key and
* message authentication scheme.The derived key is generated using Password,
* Salt and Iteration Count.
* PKCS5_generateMAC() generates MAC.This MAC will be given as input to 
* PKCS5_verifyMAC(). PKCS5_verifyMAC()
* internally generates another MAC and compares both MAC's.
*
* @param[in] pucPassword The password which is used as the base key in 
* generating the key [N/A]
* @param[in] ulPwdLen The length of the password [N/A]
* @param[in] pstPBES2Param Pointer to structure that holds the SALT,iteration 
* count, PRF and derived key length [N/A]
* @param[in] pucPlainTxt Pointer to Plain Text [N/A]
* @param[in] ulPlainTxtLen The length of Plain Text [N/A]
* @param[in] pucMAC Pointer to Message authentication code [N/A]
* @param[in] ulMACLen The length of Message Authentication Code [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 If successfully verifies MAC [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If salt obtained is NULL when calling get function for 
* salt [SEC_PKCS5_ERR_GET_SALT_FAILED|N/A]
* @retval SEC_UINT32 If one of the argument passed is NULL or invalid 
* [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If invalid Algorithm Identifier 
* [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 If CID corresponding to OID is not there 
* [SEC_ERR_INVALID_OID|N/A]
* @retval SEC_UINT32 If the field piKeyLength in PKCS5_PBKDF2PARAM_S of *
* PKCS5_PBES2PARAM_S is not passed, then we take derived key length equal *
* to the key derivation algorithm key size. If it is passed, and *
* its value is zero then an error [SEC_ERR_INVALID_KEY_LEN|N/A] will be *
* returned.(From PKCS #5 v2.0: The maximum key length allowed depends on *
* the implementation; it is expected that implementation profiles may  *
* further constrain the bounds).                                        *
* @retval SEC_UINT32 If context values are not correct 
* [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 The generated MAC and input MAC are not same or MAC 
* lengths are not same [SEC_ERR_VERIFY_FAILED|N/A]
*
* @par Dependency
* pkcs5.h
*
* @par Note
*
* Supported key derivation algorithms are ALGID_HMAC_SHA1 and ALGID_HMAC_MD5 
* and ALGID_HMAC_SHA224 
* and ALGID_HMAC_SHA256 and ALGID_HMAC_SHA384 and ALGID_HMAC_SHA512 
* and Supported MAC generation algorithms
* are ALGID_HMAC_SHA1 or ALGID_HMAC_MD5 and ALGID_HMAC_SHA224 
* and ALGID_HMAC_SHA256 and ALGID_HMAC_SHA384 and ALGID_HMAC_SHA512.
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32  PKCS5_verifyMAC (	SEC_UCHAR*	pucPassword,
    SEC_UINT32	ulPwdLen, const PKCS5_PBES2PARAM_S* pstPBES2Param,
    SEC_UCHAR*	pucPlainTxt, SEC_UINT32	ulPlainTxtLen, SEC_UCHAR*	pucMAC,
    SEC_UINT32  ulMACLen);

/**
* @defgroup PKCS5_freePBES1Param
* @ingroup pkcs5Functions
* @par Prototype
* @code
* SEC_VOID PKCS5_freePBES1Param(PKCS5_PBES1PARAM_S* pstPBE);
* @endcode
*
* @par Purpose
* To free the memory allocated by PKCS5_PBES1PARAM_S structure.
*
* @par Description
* This function is used to free the memory allocated by 
* PKCS5_PBES1PARAM_S structure.
*
* @param[in] pstPBE Pointer to PKCS5_PBES1PARAM_S structure [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Dependency
* pkcs5.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_VOID PKCS5_freePBES1Param(PKCS5_PBES1PARAM_S* pstPBE);

/**
* @defgroup PKCS5_freePBES2Param
* @ingroup pkcs5Functions
* @par Prototype
* @code
* SEC_VOID PKCS5_freePBES2Param(PKCS5_PBES2PARAM_S* pstPBES2);
* @endcode
*
* @par Purpose
* To free the memory allocated by PKCS5_PBES2PARAM_S structure.
*
* @par Description
* This function is used to free the memory allocated by 
* PKCS5_PBES2PARAM_S structure.
*
* @param[in] pstPBES2 Pointer to PKCS5_PBES2PARAM_S structure [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Dependency
* pkcs5.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID PKCS5_freePBES2Param(PKCS5_PBES2PARAM_S* pstPBES2);


/**
* @defgroup PKCS5_getIVFromPBES2Param
* @ingroup pkcs5Functions
* @par Prototype
* @code
* SEC_AsnOcts_S* PKCS5_getIVFromPBES2Param(
* const PKCS5_PBES2PARAM_S* pstPBES2Param);
* @endcode
*
* @par Purpose
* To extract and return the Initialization Vector from 
* PKCS5_PBES2PARAM_S structure.
*
* @par Description
* This function extracts and returns the Initialization Vector from 
* PKCS5_PBES2PARAM_S structure.
*
* @param[in] pstPBES2Param The structure from which the 
* Initialization Vector has to be retrieved [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_AsnOcts_S* Pointer to SEC_AsnOcts_S (IV) [SEC_AsnOcts_S*|N/A]
* @retval SEC_AsnOcts_S* If the argument passed is NULL or invalid 
* [SEC_NULL|N/A]
*
* @par Dependency
* pkcs5.h
*
* @par Note
*
* PKCS5_pbeEncrypt and PKCS5_pbeDecrypt functions uses this function to 
* get IV from PKCS5_PBES2PARAM_S structure.
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_AsnOcts_S* PKCS5_getIVFromPBES2Param(
                    const PKCS5_PBES2PARAM_S* pstPBES2Param);

/**
* @defgroup PKCS5_deriveKey
* @ingroup pkcs5Functions
* @par Prototype
* @code
* SEC_UINT32  PKCS5_deriveKey( SEC_UINT32 ulKDFAlg,
* PKCS5_PBE_TYPE_E enFlag,
* SEC_UCHAR* pucPassword,
* SEC_UINT32 ulPwdLen,
* SEC_UCHAR* pucSalt,
* SEC_UINT32 ulSaltLen,
* SEC_INT32 iIter,
* SEC_UINT32 ulDKLen,
* SEC_UCHAR* pucDerivedKey);
* @endcode
*
* @par Purpose
* To generate the derived key for PKCS5 algorithms.
*
* @par Description
* This function generates the derived key for PKCS5 algorithms.The Key is
* derived using Password,Salt and Iteration
* Count.Derived Key can be used to encrypt/decrypt a given message and 
* can also be used to generate MAC for a given
* message.
*
* @param[in] ulKDFAlg For PKCS5_PBES1_TYPE, ulKDFAlg can be 
* MD2(not supported now), ALGID_MD5 and ALGID_SHA1 & For
* PKCS5_PBES2_TYPE, default value of ulKDFAlg is ALGID_HMAC_SHA1.
* Presently it can be ALGID_HMAC_SHA1 or
* ALGID_HMAC_MD5 or ALGID_HMAC_SHA224 or ALGID_HMAC_SHA256 
* or ALGID_HMAC_SHA384 or ALGID_HMAC_SHA512[N/A]
* @param[in] enFlag enFlag is used to identify PKCS5_PBES1PARAM_S &
* PKCS5_PBES2PARAM_S.Possible values are
* PKCS5_PBES1_TYPE and PKCS5_PBES2_TYPE [N/A]
* @param[in] pucPassword The password which is used as the base key 
* in generating the key [N/A]
* @param[in] ulPwdLen Length of the password [N/A]
* @param[in] pucSalt Salt which is a set of octets [N/A]
* @param[in] ulSaltLen Length of the salt value [N/A]
* @param[in] iIter Iteration count value.If user gives zero iteration count,
* the default value of 2048 will be taken [N/A]
* @param[in] ulDKLen Lenth of the derived Key [N/A]
* @param[out] pucDerivedKey Generated derived key [N/A]
*
* @retval SEC_UINT32 On successful generation of the derived key 
* [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If one of the arguments passed is NULL or 
* invalid [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 When key length is more than the specified length.
* This error message is displayed
* if the key length is more than PKCS5_MD2_MD5_DKLEN_LEN_MAX for 
* ALGID_MD5 or if the key length is more than
* PKCS5_SHA1_DKLEN_LEN_MAX for ALGID_SHA1 [SEC_ERR_INVALID_KEY_LEN|N/A]
* Derived Key length of zero value is not allowed    *
* @retval SEC_UINT32 When context values are not correct 
* [SEC_CRYPT_ERR_INVALID_CTX|N/A]
*
* @par Dependency
* pkcs5.h
*
* @par Note
*
* The algorithms those are supported in this function are ALGID_MD5,ALGID_SHA1 
* and ALGID_HMAC_SHA1 or ALGID_HMAC_MD5
* and ALGID_HMAC_SHA224 and ALGID_HMAC_SHA256 and ALGID_HMAC_SHA384 
* and ALGID_HMAC_SHA512.
* PKCS5_pbeEncrypt or PKCS5_pbeDecrypt uses this function to derive Key 
* for PKCS5 algorithms. User should allocate
* memory for pucDerivedKey of size equal to ulDKLen.
* The keys derived by this API are not backward compatible to use
* with old iPSI versions such as V1R1, V1R3, V1R5, V1R6.
*
* @par Related Topics
* N/A
*
* 
*/


PSELINKDLL SEC_UINT32  PKCS5_deriveKey(SEC_UINT32 ulKDFAlg, 
    PKCS5_PBE_TYPE_E enFlag, 
    SEC_UCHAR* pucPassword, 
    SEC_UINT32 ulPwdLen,
    SEC_UCHAR* pucSalt, 
    SEC_UINT32 ulSaltLen, 
    SEC_INT32 iIter,    /* if equal to or less than 0, 
    uses the default value 2048 */
    SEC_UINT32 ulDKLen, SEC_UCHAR* pucDerivedKey);


/**
* @defgroup PKCS5_p12KeyIVGen
* @ingroup pkcs5Functions
* @par Prototype
* @code
* SEC_UINT32 PKCS5_p12KeyIVGen( SEC_UINT32 uiHashAlgId,
* SEC_UCHAR* pucPassWd,
* SEC_UINT32 uiPassLen,
* SEC_UCHAR* pucSalt,
* SEC_UINT32 uiSaltLen,
* SEC_UCHAR cID,
* SEC_UINT32 uiIter,
* SEC_UINT32 uiOutLen,
* SEC_UCHAR* pucOutBuf);
* @endcode
*
* @par Purpose
* To generate the Encryption key or IV for PKCS12 algorithms.
*
* @par Description
* This function generates the Encryption key or IV for PKCS12 algorithms.
* PKCS12 module uses this funtion for generating MAC Key.
*
* @param[in] uiHashAlgId Hash algorithm.Presently it could be ALGID_SHA1 [N/A]
* @param[in] pucPassWd Password that is used as the base key in 
* generating the key [N/A]
* @param[in] uiPassLen Length of the password [N/A]
* @param[in] pucSalt Salt which is a set of octets. [N/A]
* @param[in] uiSaltLen Length of the salt value [N/A]
* @param[in] cID ID to identify encryption key,iv or mac key.Possible values
* are PKCS12_CID_TYPE1,PKCS12_CID_TYPE2 and PKCS12_CID_TYPE3 [N/A]
* @param[in] uiIter If The iteration count value.If user gives zero iteration 
* count,default value of 2048 is taken as iteration count value [N/A]
* @param[in] uiOutLen Length of the derived Key [N/A]
* @param[out] pucOutBuf Generated buffer. This can be used as Encryption 
* Key or IV or MAC Key for PKCS12 algorithms.
* User has to allocate memory for derived key [N/A]
*
* @retval SEC_UINT32 If it successfully generates the pkcs12 key or IV 
* [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If one of the arguments passed is NULL or invalid 
* [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If algorithm passed is invalid [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 If internal function returns NULL [SEC_ERR_NULL_PTR|N/A]
* @retval SEC_UINT32 If context values are not correct
* [SEC_CRYPT_ERR_INVALID_CTX|N/A]
*
* @par Dependency
* pkcs5.h
*
* @par Note
*
* 1) ALGID_SHA1 is the only algorithm that is supported in 
* this function as of now.\n
* 2) PKCS5_pbeEncrypt or PKCS5_pbeDecrypt uses this function to generate 
* Encryption Key and IV for PKCS12 algorithms.\n
* 3) PKCS12 module uses this function to generate MAC Key. User should 
* allocate memory for pucOutBuf of size equal to
* uiOutLen.
*
* @par Related Topics
* N/A
*
* 
*/

PSELINKDLL SEC_UINT32 PKCS5_p12KeyIVGen(SEC_UINT32 uiHashAlgId,
    SEC_UCHAR* pucPassWd, SEC_UINT32 uiPassLen, SEC_UCHAR* pucSalt,
    SEC_UINT32 uiSaltLen, SEC_UCHAR cID, SEC_UINT32 uiIter, SEC_UINT32 uiOutLen,
    SEC_UCHAR* pucOutBuf);



/**
* @defgroup PKCS5_pbeEncrypt
* @ingroup pkcs5Functions
* @par Prototype
* @code
* SEC_UINT32 PKCS5_pbeEncrypt(SEC_UINT32 ulPbeAlg,
* SEC_UCHAR* pucPassword,
* SEC_UINT32 ulPwdLen,
* SEC_UCHAR* pucPlainTxt,
* SEC_UINT32 ulPlainTxtLen,
* SEC_VOID* pstPBEParam,
* SEC_UCHAR* pucCphTxt,
* SEC_UINT32* pulCphLen);
* @endcode
*
* @par Purpose
* To encrypt the given message using the derived key.
*
* @par Description
* This function encrypts the given message using the derived key, 
* The function used to generate the derived key
* is PKCS5_deriveKey or PKCS5_p12KeyIVGen.Password,Salt and 
* Iteration Count are used to derive the key.
*
* @param[in] ulPbeAlg ulPbeAlg can be any value defined for PKCS5_PBES1_TYPE 
* and also can be PKCS5_PBES2_TYPE [N/A]
* @param[in] pucPassword The password which is used as the base key 
* in generating the key [N/A]
* @param[in] ulPwdLen The length of the password [N/A]
* @param[in] pucPlainTxt The plain text that is Encrypted [N/A]
* @param[in] ulPlainTxtLen The length of the plain text [N/A]
* @param[in] pstPBEParam Pointer to SEC_VOID. Type of pstPBEParam is decided
* by ulPbeAlg.If ulPbeAlg is any one of
* CID_PBE_MD5WITHDESCBC,CID_PBE_SHA1WITHDESCBC,	CID_PBE_SHAWITH128BITRC4,
* CID_PBE_SHAWITH40BITRC4,
* CID_PBE_SHAWITH40BIT_RC2CBC, CID_PBE_SHAWITH128BIT_RC2CBC, 
* CID_PBE_SHAWITH3KEY_TRIPLE_DESCBC,
* CID_PBE_SHAWITH2KEY_TRIPLE_DESCBC, then pstPBEParam should be of type
* PKCS5_PBES1PARAM_S. If ulPbeAlg is CID_PBES2, then pstPBEParam should be 
* of type PKCS5_PBES2PARAM_S [N/A]
* @param[out] pucCphTxt The cipher text obtained after encryption of 
* plain text [N/A]
* @param[out] pulCphLen	Pointer to length of the cipher text [N/A]
*
* @retval SEC_UINT32 If successfully encrypts the given text [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If one of the arguments passed is NULL or 
* invalid [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If Passing algorithm is 
* invalid [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 If salt obtained using get function is 
* NULL [SEC_PKCS5_ERR_GET_SALT_FAILED|N/A]
* @retval SEC_UINT32 If IV obtained using get function is
* NULL [SEC_ERR_INVALID_IV|N/A]
* @retval SEC_UINT32 The field piKeyLength in PKCS5_PBKDF2PARAM_S of *
* PKCS5_PBE2PARAM_S is optional. If it is not passed, then it takes  *
* the derived key length = symmetric key length. If it is passed,    *
* then its value should be equal to symmetric key length. Otherwise, *
* an error [SEC_ERR_INVALID_KEY_LEN|N/A] will be returned.           *
* @retval SEC_UINT32 If IV length is invalid for alg mode 
* [SEC_ERR_INVALID_IV_LEN|N/A]
* @retval SEC_UINT32 If the pad bits are incorrect 
* [SEC_CRYPT_ERR_INVALID_PADDING|N/A]
* @retval SEC_UINT32 If invalid context [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If invalid Padding Mode in Context.Padding mode 
* set on Algorithm is not defined [SEC_CRYPT_ERR_UNDEFINED_PADDING|N/A]
* @retval SEC_UINT32 If invalid data length for encryption
* [SEC_ERR_INVALID_DATA_LEN|N/A]
*
* @par Dependency
* pkcs5.h
*
* @par Note
*
* Incase of PKCS5_PBES1PARAM_S structure,ulPbeAlg should be any one of 
* CID_PBE_MD5WITHDESCBC, CID_PBE_SHA1WITHDESCBC, 
* CID_PBE_SHAWITH128BITRC4, CID_PBE_SHAWITH40BITRC4, 
* CID_PBE_SHAWITH3KEY_TRIPLE_DESCBC,CID_PBE_SHAWITH40BIT_RC2CBC,
*  CID_PBE_SHAWITH128BIT_RC2CBC,CID_PBE_SHAWITH2KEY_TRIPLE_DESCBC
* Incase of PKCS5_PBES2PARAM_S structure,ulPbeAlg should be CID_PBES2.
* The PBES2 params encrypted by this API are not backward compatible to decrypt
* with old iPSI versions such as V1R1, V1R3, V1R5, V1R6.
*
* @par Related Topics
* N/A
*
* 
*/

PSELINKDLL SEC_UINT32 PKCS5_pbeEncrypt(SEC_UINT32 ulPbeAlg,
    SEC_UCHAR* pucPassword, SEC_UINT32 ulPwdLen, SEC_UCHAR* pucPlainTxt,
    SEC_UINT32 ulPlainTxtLen, SEC_VOID* pstPBEParam, SEC_UCHAR* pucCphTxt,
    SEC_UINT32* pulCphLen);


/**
* @defgroup PKCS5_pbeDecrypt
* @ingroup pkcs5Functions
* @par Prototype
* @code
* SEC_UINT32  PKCS5_pbeDecrypt ( SEC_UINT32 ulPbeAlg,
* SEC_UCHAR* pucPassword,
* SEC_UINT32 ulPwdLen,
* SEC_UCHAR* pucCphTxt,
* SEC_UINT32 ulCphLen,
* SEC_VOID* pstPBEParam,
* SEC_UCHAR* pucPlainTxt,
* SEC_UINT32* pulPlainTxtLen);
* @endcode
*
* @par Purpose
* To decrypt the given message using the derived key.
*
* @par Description
* This function decrypts the given message using the derived key, 
* which is generated using PKCS5_deriveKey or
* PKCS5_p12KeyIVGen. Password, Salt and Iteration Count 
* are used to derive the key .
*
* @param[in] ulPbeAlg ulPbeAlg can be any value defined for PKCS5_PBES1_TYPE
* and also can be PKCS5_PBES2_TYPE [N/A]
* @param[in] pucPassword The password which is used as the base 
* key in generating the key [N/A]
* @param[in] ulPwdLen The length of the password [N/A]
* @param[in] pucCphTxt The cipher text obtained [N/A]
* @param[in] ulCphLen The length of the cipher text [N/A]
* @param[in] pstPBEParam Pointer to SEC_VOID structure. Type of
* pstPBEParam is decided by ulPbeAlg.If ulPbeAlg is
* any one of these CID_PBE_MD5WITHDESCBC, CID_PBE_SHA1WITHDESCBC, 
* CID_PBE_SHAWITH128BITRC4, CID_PBE_SHAWITH40BITRC4,
*.CID_PBE_SHAWITH40BIT_RC2CBC, CID_PBE_SHAWITH128BIT_RC2CBC,
* CID_PBE_SHAWITH3KEY_TRIPLE_DESCBC,
* CID_PBE_SHAWITH2KEY_TRIPLE_DESCBC, then pstPBEParam should be of type
* PKCS5_PBES1PARAM_S. If ulPbeAlg is CID_PBES2, then pstPBEParam should be 
* of type PKCS5_PBES2PARAM_S [N/A]
* @param[out] pucPlainTxt Pointer to  Plain Text that is decrypted [N/A]
* @param[out] pulPlainTxtLen The length of Plain Text [N/A]
*
* @retval SEC_UINT32 On successfull decryption of the given 
* text [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If one of the arguments passed is NULL or 
* invalid [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If passing algorithm is invalid [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 If salt obtained using get function is 
* NULL [SEC_PKCS5_ERR_GET_SALT_FAILED|N/A]
* @retval SEC_UINT32 If IV obtained using get function is 
* NULL [SEC_ERR_INVALID_IV|N/A]
* @retval SEC_UINT32 The field piKeyLength in PKCS5_PBKDF2PARAM_S of *
* PKCS5_PBE2PARAM_S is optional. If it is not passed, then it takes  *
* the derived key length = symmetric key length. If it is passed,    *
* then its value should be equal to symmetric key length. Otherwise, *
* an error [SEC_ERR_INVALID_KEY_LEN|N/A] will be returned.           *
* @retval SEC_UINT32 If IV length is invalid for alg mode
* [SEC_ERR_INVALID_IV_LEN|N/A]
* @retval SEC_UINT32 If the pad bits are incorrect 
* [SEC_CRYPT_ERR_INVALID_PADDING|N/A]
* @retval SEC_UINT32 If invalid context [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If invalid Padding Mode in Context.
* Padding mode set on Algorithm is not defined
* [SEC_CRYPT_ERR_UNDEFINED_PADDING|N/A]
* @retval SEC_UINT32 If Invalid cipher text length given for decryption 
* (cipher text length was not integralnumber of blocks)
* [SEC_ERR_INVALID_DATA_LEN|N/A]
*
* @par Dependency
* pkcs5.h
*
* @par Note
*
* 1) Incase of PKCS5_PBES1PARAM_S structure, ulPbeAlg should be any 
* one of these CID_PBE_MD5WITHDESCBC,
* CID_PBE_SHA1WITHDESCBC, CID_PBE_SHAWITH128BITRC4, CID_PBE_SHAWITH40BITRC4,
* CID_PBE_SHAWITH3KEY_TRIPLE_DESCBC,
* CID_PBE_SHAWITH40BIT_RC2CBC,CID_PBE_SHAWITH128BIT_RC2CBC, 
* CID_PBE_SHAWITH2KEY_TRIPLE_DESCBC.\n
* 2) Incase of PKCS5_PBES2PARAM_S structure,ulPbeAlg should be CID_PBES2.
*
* @par Related Topics
* N/A
*
* 
*/

PSELINKDLL SEC_UINT32  PKCS5_pbeDecrypt (SEC_UINT32 ulPbeAlg,
    SEC_UCHAR* pucPassword, SEC_UINT32 ulPwdLen, SEC_UCHAR* pucCphTxt,
    SEC_UINT32 ulCphLen, SEC_VOID* pstPBEParam, SEC_UCHAR* pucPlainTxt,
    SEC_UINT32* pulPlainTxtLen);

/**
* @defgroup PKCS5_isValidPBEAlg
* @ingroup pkcs5Functions
* @par Prototype
* @code
* SEC_BOOL PKCS5_isValidPBEAlg(SEC_UINT32 ulAlgId);
* @endcode
*
* @par Purpose
* To check whether passed algorithm is valid PBE algorithm or not.
*
* @par Description
* This function checks whether passed algorithm is valid PBE algorithm or not.
*
* @param[in] ulAlgId The PBE algorithm Id.Here PBE algorithm means 
* combination of digest and symmetric algorithms.
* Possible valid inputs are\n
* CID_PBE_MD5WITHDESCBC,\n
* CID_PBE_SHA1WITHDESCBC,\n
* CID_PBE_SHAWITH128BITRC4,\n
* CID_PBE_SHAWITH40BITRC4,\n
*.CID_PBE_SHAWITH40BIT_RC2CBC\n
*.CID_PBE_SHAWITH128BIT_RC2CBC\n
* CID_PBE_SHAWITH3KEY_TRIPLE_DESCBC,\n
* CID_PBE_SHAWITH2KEY_TRIPLE_DESCBC [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_BOOL If the given algorithm is valid PBE Algorithm[SEC_TRUE|N/A]
* @retval SEC_BOOL If the given algorithm is not a valid 
* PBE Algorithm[SEC_FALSE|N/A]
* @par Dependency
* pkcs5.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_BOOL PKCS5_isValidPBEAlg(SEC_UINT32 ulAlgId);



/**
* @defgroup PKCS5_getDigestAlgFromPBEAlg
* @ingroup pkcs5Functions
* @par Prototype
* @code
* SEC_UINT32 PKCS5_getDigestAlgFromPBEAlg(SEC_UINT32 ulAlgId);
* @endcode
*
* @par Purpose
* To extract the digest algorithm from the PBE algorithm.
*
* @par Description
* This function extracts the digest algorithm from the PBE algorithm.
*
* @param[in] ulAlgId The PBE algorithm Id.Here PBE algorithm means 
* combination of digest and symmetric algorithms.
* Possible valid inputs are CID_PBE_MD5WITHDESCBC, CID_PBE_SHA1WITHDESCBC,
* CID_PBE_SHAWITH128BITRC4, CID_PBE_SHAWITH40BITRC4,
* CID_PBE_SHAWITH40BIT_RC2CBC, CID_PBE_SHAWITH128BIT_RC2CBC, 
* CID_PBE_SHAWITH3KEY_TRIPLE_DESCBC, CID_PBE_SHAWITH2KEY_TRIPLE_DESCBC [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 On successful completion [The Digest AlgId|N/A]
* @retval SEC_UINT32 If the input is invalid [CID_UNKNOWN|N/A]
*
* @par Dependency
* pkcs5.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 PKCS5_getDigestAlgFromPBEAlg(SEC_UINT32 ulAlgId);



/**
* @defgroup PKCS5_getSymAlgFromPBEAlg
* @ingroup pkcs5Functions
* @par Prototype
* @code
* SEC_UINT32 PKCS5_getSymAlgFromPBEAlg(SEC_UINT32 ulAlgId);
* @endcode
*
* @par Purpose
* To extract and return symmetric algorithm from the PBE algorithm.
*
* @par Description
* This function extracts and returns symmetric algorithm from the PBE algorithm.
*
* @param[in] ulAlgId The PBE algorithm Id. Here PBE algorithm means combination
* of digest and symmetric algorithms.
* Possible valid inputs are CID_PBE_MD5WITHDESCBC, CID_PBE_SHA1WITHDESCBC,
* CID_PBE_SHAWITH128BITRC4, CID_PBE_SHAWITH40BIT_RC2CBC, 
* CID_PBE_SHAWITH128BIT_RC2CBC
* CID_PBE_SHAWITH40BITRC4, CID_PBE_SHAWITH3KEY_TRIPLE_DESCBC, 
* CID_PBE_SHAWITH2KEY_TRIPLE_DESCBC [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 On successful completion [The Symmetric AlgId|N/A]
* @retval SEC_UINT32 If the input is invalid [CID_UNKNOWN|N/A]
*
* @par Dependency
* pkcs5.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 PKCS5_getSymAlgFromPBEAlg(SEC_UINT32 ulAlgId);

/**
* @defgroup PKCS5_pbeAlgKeyLen
* @ingroup pkcs5Functions
* @par Prototype
* @code
* SEC_UINT32 PKCS5_pbeAlgKeyLen(SEC_UINT32 ulAlgId);
* @endcode
*
* @par Purpose
* To retrieve the symmetric key length used in the PBE algorithm.
*
* @par Description
* This function retrieves the symmetric key length used in the PBE alg.
*
* @param[in] ulAlgId The PBE algorithm Id. Here PBE algorithm means combination
* of digest and symmetric algorithms.
* Possible valid inputs are CID_PBE_MD5WITHDESCBC, CID_PBE_SHA1WITHDESCBC, 
* CID_PBE_SHAWITH128BITRC4,
* CID_PBE_SHAWITH40BIT_RC2CBC,CID_PBE_SHAWITH128BIT_RC2CBC, 
* CID_PBE_SHAWITH40BITRC4,
* CID_PBE_SHAWITH3KEY_TRIPLE_DESCBC, CID_PBE_SHAWITH2KEY_TRIPLE_DESCBC	[N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 On successful completion [The keylength|N/A]
* @retval SEC_UINT32 If the input is invalid [0|N/A]
*
* @par Dependency
* pkcs5.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 PKCS5_pbeAlgKeyLen(SEC_UINT32 ulAlgId);

/**
* @defgroup PKCS5_pbeAlgBlockSize
* @ingroup pkcs5Functions
* @par Prototype
* @code
* SEC_UINT32 PKCS5_pbeAlgBlockSize(SEC_UINT32 ulAlgId);
* @endcode
*
* @par Purpose
* To retrieve the Block size used in the PBE algorithm.
*
* @par Description
* This function retrieves the Block size used in the PBE alg.
*
* @param[in] ulAlgId The PBE algorithm Id.Here PBE algorithm means 
* combination of digest and symmetric algorithms.
* Possible valid inputs are CID_PBE_MD5WITHDESCBC, CID_PBE_SHA1WITHDESCBC,
* CID_PBE_SHAWITH128BITRC4,
* CID_PBE_SHAWITH40BITRC4, CID_PBE_SHAWITH3KEY_TRIPLE_DESCBC, 
* CID_PBE_SHAWITH40BIT_RC2CBC, CID_PBE_SHAWITH128BIT_RC2CBC, 
* CID_PBE_SHAWITH2KEY_TRIPLE_DESCBC [N/A]
* @param[out] N/A N/A  [N/A]
*
* @retval SEC_UINT32 On successful completion 
* [The Block Size of pbe algorithms|N/A]
* @retval SEC_UINT32 If the input is invalid [0|N/A]
*
* @par Dependency
* pkcs5.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 PKCS5_pbeAlgBlockSize(SEC_UINT32 ulAlgId);


/**
* @defgroup PKCS5_pbeAlgIVLen
* @ingroup pkcs5Functions
* @par Prototype
* @code
* SEC_UINT32 PKCS5_pbeAlgIVLen(SEC_UINT32 ulAlgId);
* @endcode
*
* @par Purpose
* To retrieve the initialization vector(IV) length used in the PBE algorithm.
*
* @par Description
* This function retrieves the initialization vector(IV) length 
* used in the PBE alg.
*
* @param[in] ulAlgId The PBE algorithm Id.Here PBE algorithm means combination
* of digest and symmetric algorithms.
* Possible valid inputs are CID_PBE_MD5WITHDESCBC, CID_PBE_SHA1WITHDESCBC, 
* CID_PBE_SHAWITH3KEY_TRIPLE_DESCBC,
* CID_PBE_SHAWITH2KEY_TRIPLE_DESCBC [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 On successful completion [The IV lengthN/A]
* @retval SEC_UINT32 If the input is invalid [0|N/A]
*
* @par Dependency
* PKCS5.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 PKCS5_pbeAlgIVLen(SEC_UINT32 ulAlgId);

/**
* @defgroup PKCS5_dupPBES1Param
* @ingroup pkcs5Functions
* @par Prototype
* @code
* PKCS5_PBES1PARAM_S* PKCS5_dupPBES1Param(PKCS5_PBES1PARAM_S* pSrc);
* @endcode
*
* @par Purpose
* To take the pointer of PKCS5_PBES1PARAM_S structure to be 
* duplicated and return a pointer to newly created PKCS5_PBES1PARAM_S 
* structure copied with the information passed to the function.
*
* @par Description
* This function takes the pointer of PKCS5_PBES1PARAM_S structure to be 
* duplicated and returns a pointer to  newly created PKCS5_PBES1PARAM_S 
* structure copied with the information passed to the function.
*
* @param[in] pSrc Pointer to PKCS5_PBES1PARAM_S structure [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS5_PBES1PARAM_S* Pointer to PKCS5_PBES1PARAM_S structure 
* [PKCS5_PBES1PARAM_S*|N/A]
* @retval PKCS5_PBES1PARAM_S* If input is invalid [SEC_NULL|N/A]
*
* @par Dependency
* pkcs5.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL PKCS5_PBES1PARAM_S* PKCS5_dupPBES1Param(PKCS5_PBES1PARAM_S* pSrc);

/**
* @defgroup PKCS5_dupPBES2Param
* @ingroup pkcs5Functions
* @par Prototype
* @code
* PKCS5_PBES2PARAM_S* PKCS5_dupPBES2Param(PKCS5_PBES2PARAM_S* pSrc);
* @endcode
*
* @par Purpose
* To take the pointer of PKCS5_PBES2PARAM_S structure to be duplicated
* and return a pointer to  newly created PKCS5_PBES2PARAM_S structure copied
* with the information passed to the function.
*
* @par Description
* This function takes the pointer of PKCS5_PBES2PARAM_S structure to be
* duplicated and returns a pointer to newly created PKCS5_PBES2PARAM_S 
* structure copied with the information passed to the function.
*
* @param[in] pSrc Pointer to PKCS5_PBES2PARAM_S structure [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS5_PBES2PARAM_S* Pointer to PKCS5_PBES2PARAM_S structure 
* [PKCS5_PBES2PARAM_S*|N/A]
* @retval PKCS5_PBES2PARAM_S* If the input is invalid [SEC_NULL|N/A]
*
* @par Dependency
* pkcs5.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL PKCS5_PBES2PARAM_S* PKCS5_dupPBES2Param(PKCS5_PBES2PARAM_S* pSrc);


#ifdef __cplusplus
}

#endif

#endif // _IPSI_PKCS5_H_

/* End of pkcs5.h */
