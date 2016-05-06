

#ifndef _IPSI_SEC_CRYPTO_H
#define _IPSI_SEC_CRYPTO_H

#ifdef __cplusplus
extern  "C" {
#endif

#include "ipsi_crypto_buildconf.h"
#include "sec_sys.h"
#include "sec_util.h"


#define ALGID_UNKNOWN   0

/* identifies the RC4 algorithm */

#define ALGID_RC4                       CID_RC4       

/* The following Symmetric Block algorithms belong to the four modes
    ECB - Electronic Code Book
    CBC - Cipher Block Chaining
    OFB - Output FeedBack
    CFB - Cipher FeedBack
*/

/* identifies DES algorithm in ECB mode */

#define ALGID_DES_ECB  CID_DES_ECB 

/* identifies DES algorithm in CBC mode */

#define ALGID_DES_CBC  CID_DES_CBC

/* identifies DES algorithm in OFB mode */

#define ALGID_DES_OFB  CID_DES_OFB

/* identifies DES algorithm in CFB mode */

#define ALGID_DES_CFB  CID_DES_CFB 

/* ID's for supporting SSX31B HW Now in crypto
scb2 algo is not supported.All scb2 symbols we keep because these 
symbols are used in pse and ssl*/
/* identifies SCB2-128 algorithm in ECB mode */
#define ALGID_SCB2_128_ECB CID_SCB2_128_ECB

/* identifies SCB2-128 algorithm in CBC mode */
#define ALGID_SCB2_128_CBC CID_SCB2_128_CBC

/* identifies SCB2-256 algorithm in ECB mode */
#define ALGID_SCB2_256_ECB CID_SCB2_256_ECB

/* identifies SCB2-256 algorithm in CBC mode */
#define ALGID_SCB2_256_CBC CID_SCB2_256_CBC

/* identifies 2 key triple DES algorithm in ECB mode */

#define ALGID_DES_EDE_ECB               CID_DES_EDE_ECB   

/* identifies 2 key triple DES algorithm in CBC mode */

#define ALGID_DES_EDE_CBC               CID_DES_EDE_CBC   

/* identifies 2 key triple DES algorithm in OFB mode */

#define ALGID_DES_EDE_OFB               CID_DES_EDE_OFB   

/* identifies 2 key triple DES algorithm in CFB mode */

#define ALGID_DES_EDE_CFB               CID_DES_EDE_CFB  

/* identifies 3 key triple DES algorithm in ECB mode */

#define ALGID_DES_EDE3_ECB              CID_DES_EDE3_ECB   

/* identifies 3 key triple DES algorithm in CBC mode */

#define ALGID_DES_EDE3_CBC              CID_DES_EDE3_CBC   

/* identifies 3 key triple DES algorithm in OFB mode */

#define ALGID_DES_EDE3_OFB              CID_DES_EDE3_OFB   

/* identifies 3 key triple DES algorithm in CFB mode */

#define ALGID_DES_EDE3_CFB              CID_DES_EDE3_CFB   

/* identifies AES-128 algorithm in ECB mode */

#define ALGID_AES128_ECB                CID_AES128_ECB  

/* identifies AES-128 algorithm in CBC mode */

#define ALGID_AES128_CBC                CID_AES128_CBC   

/* identifies AES-128 algorithm in OFB mode */

#define ALGID_AES128_OFB                CID_AES128_OFB   

/* identifies AES-128 algorithm in CFB mode */

#define ALGID_AES128_CFB                CID_AES128_CFB    

/* identifies AES-192 algorithm in ECB mode */

#define ALGID_AES192_ECB                CID_AES192_ECB  

/* identifies AES-192 algorithm in CBC mode */

#define ALGID_AES192_CBC                CID_AES192_CBC  

/* identifies AES-192 algorithm in OFB mode */

#define ALGID_AES192_OFB                CID_AES192_OFB  

/* identifies AES-192 algorithm in CFB mode */

#define ALGID_AES192_CFB                CID_AES192_CFB    

/* identifies AES-256 algorithm in ECB mode */

#define ALGID_AES256_ECB                CID_AES256_ECB   

/* identifies AES-256 algorithm in CBC mode */

#define ALGID_AES256_CBC                CID_AES256_CBC     

/* identifies AES-256 algorithm in OFB mode */

#define ALGID_AES256_OFB                CID_AES256_OFB  

/* identifies AES-256 algorithm in CFB mode */

#define ALGID_AES256_CFB                CID_AES256_CFB   

/* identifies Kasumi algorithm in ECB mode */

#define ALGID_KASUMI_ECB                CID_KASUMI_ECB   

/* identifies Kasumi algorithm in CBC mode */

#define ALGID_KASUMI_CBC                CID_KASUMI_CBC    

/* identifies Kasumi algorithm in CFB mode */

#define ALGID_KASUMI_CFB                CID_KASUMI_CFB  

/* identifies Kasumi algorithm in OFB mode */

#define ALGID_KASUMI_OFB                CID_KASUMI_OFB  

/* identifies RC2 algorithm in ECB mode */

#define ALGID_RC2_ECB                CID_RC2_ECB

/* identifies RC2 algorithm in CBC mode */

#define ALGID_RC2_CBC                CID_RC2_CBC

/* identifies RC2 algorithm in OFB mode */

#define ALGID_RC2_OFB                CID_RC2_OFB

/* identifies RC2 algorithm in CFB mode */

#define ALGID_RC2_CFB                CID_RC2_CFB

/* identifies Blowfish algorithm in ECB mode */
#define ALGID_BF_ECB			CID_BF_ECB

/* identifies Blowfish algorithm in CBC mode */
#define ALGID_BF_CBC			CID_BF_CBC

/* identifies Blowfish algorithm in CFB mode */
#define ALGID_BF_CFB			CID_BF_CFB

/* identifies Blowfish algorithm in OFB mode */
#define ALGID_BF_OFB			CID_BF_OFB





#define LAST_SYM_ALG CID_RC2_CFB

//to ensure if new sym algorithms are added after RC2 then 
//g_AlgTable array and ipsi_algid_to_g_AlgTable_idx should be modified


/* identifies the RSA algorithm */

#define ALGID_RSA                       CID_RSA       

/* identifies the DSA algorithm */

#define ALGID_DSA                       CID_DSA      

/* identifies the ECDSA algorithm */

#define ALGID_ECDSA                     CID_ECDSA   

/* identifies the Diffie-Hellman algorithm */

#define ALGID_DH                        CID_DH     

/* identifies the EC Diffie-Hellman algorithm */

#define ALGID_ECDH                      CID_ECDH   


#define ALGID_MD4                       CID_MD4     

/* identifies MD4 hash algorithm */

#define ALGID_MD5                       CID_MD5     

/* identifies the MD5 hash algorithm */

#define ALGID_SHA1                      CID_SHA1    

/* identifies the SHA1 hash algorithm */

#define ALGID_SHA224                    CID_SHA224   

/* identifies the SHA224 hash algorithm */

#define ALGID_SHA256                    CID_SHA256   

/* identifies the SHA256 hash algorithm */

#define ALGID_SHA384                    CID_SHA384    

/* identifies the SHA384 hash algorithm */

#define ALGID_SHA512                    CID_SHA512   

/* identifies the SHA512 hash algorithm */

#define ALGID_HMAC_MD4                  CID_HMAC_MD4    

/* identifies hmac with MD4 */

#define ALGID_HMAC_MD5                  CID_HMAC_MD5   

/* identifies hmac with MD5 */

#define ALGID_HMAC_SHA1                 CID_HMAC_SHA1    

/* identifies hmac with SHA1 */

#define ALGID_HMAC_SHA224               CID_HMAC_SHA224  

/* identifies hmac with SHA224 */

#define ALGID_HMAC_SHA256               CID_HMAC_SHA256  

/* identifies hmac with SHA256 */

#define ALGID_HMAC_SHA384               CID_HMAC_SHA384   

/* identifies hmac with SHA384 */

#define ALGID_HMAC_SHA512               CID_HMAC_SHA512  

/* identifies hmac with SHA512 */

#define ALGID_CMAC_AES                  CID_CMAC_AES   

/* identifies CMAC-AES*/


#define ALGID_XCBC_AES                  CID_XCBC_AES   

/* identifies XCBC-MAC-AES*/

#define ALGID_CMAC_TDES                 CID_CMAC_TDES    

/* identifies CMAC-Triple DES*/

#define ALGID_RNG_HW                    CID_RNG_HW      

/* identifies TRNG */

#define ALGID_RNG_SW                    CID_RNG_SW   

/* identifies PRNG*/

/* Following ALGIDs are used by the SSL library */
#define ALGID_MD5WITHRSA                CID_MD5WITHRSA   

/* identifies signature using MD5 and RSA */

#define ALGID_SHA1WITHRSA               CID_SHA1WITHRSA   

/* identifies signature using SHA1 and RSA */

#define ALGID_SHA1WITHRSAOLD            CID_SHA1WITHRSAOLD 

/* identifies signature using SHA1 and RSA (coresponds to old Oid)*/

#define ALGID_DSA_WITH_SHA1             CID_DSAWITHSHA1    

/* identifies signature using SHA1 and DSA */

#define ALGID_DSAWITHSHA1_2             CID_DSAWITHSHA1_2  

/* identifies signature using SHA1 and DSA */

#define ALGID_ECDSA_WITH_SHA1           CID_ECDSAWITHSHA1  

/* identifies signature using SHA1 and ECDSA */

#define ALGID_ECDSA_WITH_SHA224           CID_ECDSAWITHSHA224  

/* identifies signature using SHA224 and ECDSA */

#define ALGID_ECDSA_WITH_SHA256           CID_ECDSAWITHSHA256  

/* identifies signature using SHA256 and ECDSA */

#define ALGID_ECDSA_WITH_SHA384           CID_ECDSAWITHSHA384

/* identifies signature using SHA384 and ECDSA */

#define ALGID_ECDSA_WITH_SHA512           CID_ECDSAWITHSHA512

/* identifies signature using SHA512 and ECDSA */

#define ALGID_ECDSA192_WITH_SHA256          CID_ECDSA192WITHSHA256  

/* identifies signature using SHA1 and ECDSA192 */

#define ALGID_SHA256WITHRSAENCRYPTION   CID_SHA256WITHRSAENCRYPTION

/* identifies signature using SHA256 and RSA */

#define ALGID_SHA384WITHRSAENCRYPTION   CID_SHA384WITHRSAENCRYPTION 

/* identifies signature using SHA384 and RSA */

#define ALGID_SHA512WITHRSAENCRYPTION   CID_SHA512WITHRSAENCRYPTION 

/* identifies signature using SHA512 and RSA */

#define ALGID_MD5_SHA1                       CID_MD5_SHA1

/* identifies special case in which hash info is not considered in sign
and verification */

#define ALGID_SM3               CID_SM3

/* identifies the SM3 hash algorithm */

#define ALGID_HMAC_SM3      CID_HMAC_SM3

/* identifies hmac with SM3 */

#define ALGID_SM2DSA            CID_SM2DSA

/*Identifies SM2 Digital Signature Algorithm*/

#define ALGID_SM2DSA_WITH_SM3            CID_SM2DSAWITHSM3

/*Identifies signature using SM2DSA with SM3*/

#define ALGID_SM2DSA_WITH_SHA1            CID_SM2DSAWITHSHA1

/*Identifies signature using SM2DSA with SHA1*/

#define ALGID_SM2DSA_WITH_SHA256            CID_SM2DSAWITHSHA256

/*Identifies signature using SM2DSA with SHA256*/

#define ALGID_SM2KEP            CID_SM2KEP

/*Identifies SM2 Key Exchange Protocol algorithm*/

#define ALGID_SM2PKEA            CID_SM2PKEA

/*Identifies SM2 Public Key Encryption Algorithm*/

#define ALGID_ECKEY            ALGID_ECDSA

/*Identifies the EC Key, which can be used with various ECC algorithms*/

#define ALGID_AES128_GCM                    CID_AES128_GCM
#define ALGID_AES192_GCM                    CID_AES192_GCM
#define ALGID_AES256_GCM                    CID_AES256_GCM

#define ALGID_AES128_CTR                    CID_AES128_CTR
#define ALGID_AES192_CTR                    CID_AES192_CTR
#define ALGID_AES256_CTR                    CID_AES256_CTR

#define CRYPT_MASK_PAD(x)       ((SEC_UINT32)((x) & 0xFFFF))

/* Macro to mask out the pad info to get alg_id */

#define CRYPT_SET_PAD_MODE(a,m) ((a) |= (((SEC_UINT32)(m))<<16))

/* Macros to get & set the pad mode of a symmetric algorithm 
 the parameter 'a' must be an l-value */
 
#define CRYPT_RESET_PAD_MODE(a) ((a) &= 0x0000ffff) 

/* Macro to reset padding mode*/

#define CRYPT_GET_PAD_MODE(a)   (((SEC_UINT32)(a)) >> 16) 

/* Macro to get padding mode from alg */ 


/* Specifies the result of a comparison operation */
#define SEC_CRYPT_MATCH     0UL     

/* compared values match when comparison function returns SEC_CRYPT_MATCH */

#define SEC_CRYPT_NO_MATCH  1UL     

/* compared values do not match when comparison function
returns SEC_CRYPT_MATCH */

/* The maximum size of a digest */
#define MAX_DIGEST_SIZE     64UL    

/* Maximum possible size of a digest, same as size of SHA512 digest */

#define MAX_KEY_LENGTH      32UL  

/* The maximum size of a symmetric alg key */

#define MAX_BLOCK_LENGTH    16UL    

/* The maximum size of a symmetric alg block */

#define MAX_IV_LENGTH       MAX_BLOCK_LENGTH   

/* The maximum size of a symmetric alg IV */


/* Operating modes for symmetric algorithm */
#define SYMALG_STREAM_CIPHER    0x0UL
#define SYMALG_ECB_MODE         0x1UL
#define SYMALG_CBC_MODE         0x2UL
#define SYMALG_CFB_MODE         0x3UL
#define SYMALG_OFB_MODE         0x4UL
#define INVALID_SYMALG_MODE     0x5UL

#define SYMALG_GCM_MODE         0x6UL
#define SYMALG_CTR_MODE         0x7UL

/* algorithm type */

/* Block cipher padding types */
#define BLOCK_PADDING_ONEZERO   0x0L    

/* Add a 1 followed by 0  or many 0 */

#define BLOCK_PADDING_NORMAL    0x1L    

/* Add n to construct a whole block */

#define BLOCK_PADDING_NONE      0x2L    

/* No padding */


#ifdef RSA_DEFAULT_PADDING
#undef RSA_DEFAULT_PADDING
#endif

#ifdef RSA_NO_PADDING
#undef RSA_NO_PADDING
#endif

#ifdef RSA_PKCS1_PADDING
#undef RSA_PKCS1_PADDING
#endif

#ifdef RSA_SSLV23_PADDING
#undef RSA_SSLV23_PADDING
#endif

#ifdef RSA_PKCS1_OAEP_PADDING
#undef RSA_PKCS1_OAEP_PADDING
#endif


/* RSA padding type */
#define RSA_DEFAULT_PADDING     0x0L

/* default type of padding mode */

#define RSA_NO_PADDING          0x1L

/* no padding */

#define RSA_PKCS1_PADDING       0x2L

/* pad with random bytes containing no 0 */

#define RSA_SSLV23_PADDING      0x4L

/* pad with random bytes containing no 0 and 8 LSB of pad set to 3 - TLSv1 */

#define RSA_PKCS1_OAEP_PADDING  0x8L

/* OAEP padding as in PKCS1 */


/*
  The below GROUPID macros identify CURVEs defined by X9.62 
  standard Appendix J  optimal basis is not supported
 
  The macros should be used as arguments to the 
  CRYPT_createECParamsById function
  The Group IDs defined to be zero are 
  standard vectors with point decompression which are currently not supported
*/
#define GROUPID_X9_62_C2PNB163V1        1
#define GROUPID_X9_62_C2PNB163V2        2
#define GROUPID_X9_62_C2PNB163V3        3
#define GROUPID_X9_62_C2PNB176W1        0
#define GROUPID_X9_62_C2TNB191V1        4
#define GROUPID_X9_62_C2TNB191V2        5
#define GROUPID_X9_62_C2TNB191V3        6
#define GROUPID_X9_62_C2ONB191V4        0
#define GROUPID_X9_62_C2ONB191V5        0

#define GROUPID_X9_62_C2PNB208W1        0
#define GROUPID_X9_62_C2TNB239V1        7
#define GROUPID_X9_62_C2TNB239V2        8
#define GROUPID_X9_62_C2TNB239V3        9
#define GROUPID_X9_62_C2ONB239V4        0
#define GROUPID_X9_62_C2ONB239V5        0

#define GROUPID_X9_62_C2PNB272W1        0
#define GROUPID_X9_62_C2PNB304W1        0
#define GROUPID_X9_62_C2TNB359V1        10
#define GROUPID_X9_62_C2PNB368W1        0
#define GROUPID_X9_62_C2TNB431R1        11

#define GROUPID_X9_62_PRIME192V1        12
#define GROUPID_X9_62_PRIME192V2        13
#define GROUPID_X9_62_PRIME192V3        14
#define GROUPID_X9_62_PRIME239V1        15
#define GROUPID_X9_62_PRIME239V2        16
#define GROUPID_X9_62_PRIME239V3        17
#define GROUPID_X9_62_PRIME256V1        18
#define GROUPID_X9_62_WAPIPRIME192V3        19

/*
  The below GROUPID macros identify CURVEs defined by SM2  standard 
 */
#define GROUPID_SM2_PRIME256    20

/*
 SEC 2 Curves
 */
#define GROUPID_SEC_P256R1      18
#define GROUPID_SEC_P384R1      21
#define GROUPID_SEC_P521R1      22


// Backward compatibility macros
#define SEC_SHA384_BACK_COMP 1
#define SEC_SHA512_BACK_COMP 2


#define SEC_UNCOMPRESSED_CIPHER 0
#define SEC_COMPRESSED_CIPHER 1


/* NOTE for internal use: The below value should be 
in sync with (MAX_IPSI_BN_DIGITS<<3) */

#define MAX_INT_DIGITS  (516UL) 

/* Max size of big integers supported in crypto module */

/* NOTE for internal use: The below value must be in sync 
with GLOBAL_RNG_STATE_OCTS */

#define PRNG_STATE_OCTS (262UL)

/* Size of the random number generator state */

/*
  The context that will be used for symmetric 
  encrypt/decrypt/open/seal/hash/sign operations.
  For all operations, this context has to be initialized 
  with a call to the appropriate Init function.
*/
typedef SEC_VOID* CRYPT_CTX;

/*
The context that will be used for AEAD encrypt/decrypt operations.
*/
typedef SEC_VOID* CRYPT_AEAD_CTX;

/*
This type defines the context that will be used for SM2 key exchange protocol operation.
*/
typedef SEC_VOID* CRYPT_SM2_KEP_CTX;

/*
The context that will be used for sym encrypt/decrypt operations.
*/
typedef SEC_VOID* CRYPT_SYM_CTX;

/** @defgroup sec_crypto
* This section contains sec_crypto, Structures and Functions.
*/

/** @defgroup sec_cryptoEnum
* @ingroup sec_crypto
* This section contains the sec_crypto Enum.
*/


/** @defgroup sec_cryptoStructures
* @ingroup sec_crypto
* This section contains the sec_crypto Structures.
*/


/** @defgroup sec_cryptoFunctions
* @ingroup sec_crypto
* This section contains the sec_crypto Functions.
*/


/**
* @defgroup HLF High Level Functions
* @ingroup sec_cryptoFunctions
* This section contains high level crypto functions
*/


/**
* @defgroup LLF Low Level Functions
* @ingroup sec_cryptoFunctions
* This section contains low level crypto functions
*/

/* The big integer representation */

/**
* @defgroup SEC_BIGINT_S
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct stBIGINT
* {
*  SEC_UINT32 uiLength;
*  SEC_INT8   aVal[MAX_INT_DIGITS];
* }SEC_BIGINT_S;
* @endcode
*
* @datastruct uiLength Number of valid octets which are 
stored below in aVal.
* @datastruct aVal[MAX_INT_DIGITS] Holds the value of big 
integer with MSB @ aVal[0].
*/

typedef struct stBIGINT
{
    SEC_UINT32      uiLength;               

    /* number of valid octets which are stored below in aVal */
    
    SEC_INT8        aVal[MAX_INT_DIGITS];  

    /* holds the value of big integer with MSB @ aVal[0] */
    
} SEC_BIGINT_S;

/* RSA parameter structure with length and public Exponent */

/**
* @defgroup RSA_PARA_S
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct stRSA_PARA
* {
*  SEC_UINT32   uiBits;
*  SEC_BIGINT_S stPubExp;
* }RSA_PARA_S;
* @endcode
*
* @datastruct uiBits Number of bits in the rsa modulus.
* @datastruct stPubExp Octets of public exponent.
*/

typedef struct stRSA_PARA
{
    SEC_UINT32      uiBits;     /* Number of bits in the rsa modulus */
    SEC_BIGINT_S    stPubExp;   /* octets of public exponent */
} RSA_PARA_S;

/* DSA parameter struct with P, Q, G */

/**
* @defgroup DSA_PARA_S
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct stDSA_PARA
* {
*  SEC_BIGINT_S stP;
*  SEC_BIGINT_S stQ;
*  SEC_BIGINT_S stG;
* }DSA_PARA_S;
* @endcode
*
* @datastruct stP Prime number which is divisible by q-1.
* @datastruct stQ Prime number, 2^159<q<2^160 which 
determines the order of the cyclic group.
* @datastruct stG An element in Z*(p) used to create generator.
*/

typedef struct stDSA_PARA
{
    SEC_BIGINT_S    stP;                    

    /* prime number which is divisible by q-1 */
    
    SEC_BIGINT_S    stQ;                    

    /* prime number, 2^159<q<2^160 which determines the order 
    of the cyclic group */
    
    SEC_BIGINT_S    stG;                    

    /* An element in Z*(p) used to create generator */
    
} DSA_PARA_S;

/* DH parameter struct with P, G, Q */

/**
* @defgroup DH_PARA_S
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct stDH_PARA
* {
* SEC_BIGINT_S stP;
* SEC_BIGINT_S stG;
* SEC_BIGINT_S stQ;
* }DH_PARA_S;
* @endcode
*
* @datastruct stP The prime defining the Galois field.
* @datastruct stG The generator of the multiplicative
subgroup of order q.
* @datastruct stQ The prime factor of p-1.
*/

typedef struct stDH_PARA
{
    SEC_BIGINT_S    stP;                    

    /* The prime defining the Galois field */
    
    SEC_BIGINT_S    stG;                    

    /* The generator of the multiplicative subgroup of order q */
    
    SEC_BIGINT_S    stQ;                    

    /* The prime factor of p-1 */
    
} DH_PARA_S;

/* Representation of a Elliptic Curve Point (x,y) 
in compressed or normal form */

/**
* @defgroup EC_POINT_S
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct stEC_POINT
* {
*  SEC_BIGINT_S stX;
*  SEC_BIGINT_S stY;
*  SEC_BOOL     bYCompress;
* }EC_POINT_S;
* @endcode
*
* @datastruct stX Variable represents big interger.
* @datastruct stY Variable represents big interger.
* @datastruct bYCompress If true, stY = {1, {1}} or {1, {0}}.
*/

typedef struct stEC_POINT
{
    SEC_BIGINT_S    stX; /* variable represents big interger */
    SEC_BIGINT_S    stY; /* variable represents big interger */
    SEC_BOOL        bYCompress; /* if true, stY = {1, {1}} or {1, {0}} */
} EC_POINT_S;

/* Parameter for a prime field - a prime number */
typedef struct stBIGINT EC_PRIME_S;

/* Trinomial with MSB & LSB set. k is power of 2^k */

/**
* @defgroup EC_BASIS_TRI_S
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct stEC_BASIS_TRI
* {
*  SEC_UINT k;
* }EC_BASIS_TRI_S;
* @endcode
*
* @datastruct k k is power of 2.
*/

typedef struct stEC_BASIS_TRI
{
    SEC_UINT k; /* k is power of 2 */
} EC_BASIS_TRI_S;

/* Pentanomial with MSB & LSB set. k1, k2, k3 represents 2^k1+2^k2+2^k3 */

/**
* @defgroup EC_BASIS_PENT_S
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct stEC_BASIS_PENT
* {
*  SEC_UINT k1;
*  SEC_UINT k2;
*  SEC_UINT k3;
* }EC_BASIS_PENT_S;
* @endcode
*
* @datastruct k1 k1 is power of 2.
* @datastruct k2 k2 is power of 2.
* @datastruct k3 k3 is power of 2.
*/

typedef struct stEC_BASIS_PENT
{
    SEC_UINT k1;  /* k1 is power of 2 */
    SEC_UINT k2;  /* k2 is power of 2 */
    SEC_UINT k3;  /* k3 is power of 2 */
} EC_BASIS_PENT_S;

/* Parameter for a Binary field - can be a trinomial or pentanomial */

/**
* @defgroup EC_BINARY_S
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct stEC_BINARY
* {
*  SEC_UINT32 degree;
*  SEC_UINT32 basisType;
*  union 
*      {
*       EC_BASIS_TRI_S  stTri;
*       EC_BASIS_PENT_S stPenta;
*      }Basis;
* }EC_BINARY_S;
* @endcode
*
* @datastruct degree Degree of the polynomial.
* @datastruct basisType Determines whether Basis is trinomial or pentanomial.
* @datastruct stTri Trinomial with MSB & LSB set.
* @datastruct stPenta Pentanomial with MSB & LSB set.
* @datastruct Basis Holds the polynomial's non-zero terms.
*/

typedef struct stEC_BINARY
{
    SEC_UINT32      degree;             /* degree of the polynomial */
    SEC_UINT32      basisType;          

    /* determines whether Basis is trinomial or pentanomial */
    
    union 
    {
        EC_BASIS_TRI_S      stTri;   /* Trinomial with MSB & LSB set */
        EC_BASIS_PENT_S     stPenta;  /* Pentanomial with MSB & LSB set */
    } Basis;                            

    /* holds the polynomial's non-zero terms */
    
} EC_BINARY_S;

/* parameters for a Ellitic curve algorithm */

/**
* @defgroup EC_PARA_S
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct stEC_PARA
* {
*  SEC_UINT32 fieldType;
*  SEC_UINT32 paramId;
*  union
*      {
*       EC_PRIME_S  stPrime;
*       EC_BINARY_S stBinary;
*      }fieldParam;
*  SEC_BIGINT_S stCoefA;
*  SEC_BIGINT_S stCoefB;
*  EC_POINT_S   stBase;
*  SEC_BIGINT_S stOrder;
*  SEC_BIGINT_S* pCoFactor;
* }EC_PARA_S;
* @endcode
*
* @datastruct fieldType Determines whether field is prime or binary.
* @datastruct paramId Contains the curve id if this is a set of
parameters from X.9-62.
* @datastruct stPrime Parameter for a prime field - a prime number.
* @datastruct stBinary Parameter for a binary field - can be a 
trinomial or pentanomial.
* @datastruct fieldParam Holds the polynomial or prime 
describing the field.
* @datastruct stCoefA Coefficient 'a' of the curve equation.
* @datastruct stCoefB Coefficient 'b' of the curve equation.
* @datastruct stBase The base point of the Curve.
* @datastruct stOrder The order of the base point.
* @datastruct pCoFactor Optional field, The integer h = #E(Fq)/n,
can be left NULL.
*/

typedef struct stEC_PARA
{
    SEC_UINT32      fieldType;          

    /* determines whether field is prime or binary */
    
    SEC_UINT32      paramId;            

    /* contains the curve id if this is a set of parameters from X.9-62 */
    
    union
    {
        EC_PRIME_S      stPrime;        

        /*parameter for a prime field - a prime number*/
        
        EC_BINARY_S stBinary;           

        /*parameter for a binary field - can be a trinomial or pentanomial*/
        
    } fieldParam;                       

    /* Holds the polynomial or prime describing the field */
    
    SEC_BIGINT_S    stCoefA;            

    /* Coefficient 'a' of the curve equation */
    
    SEC_BIGINT_S    stCoefB;            

    /* Coefficient 'b' of the curve equation */
    
    EC_POINT_S      stBase;             

    /* The base point of the Curve */
    
    SEC_BIGINT_S    stOrder;            

    /* The order of the base point */
    
    SEC_BIGINT_S*   pCoFactor;          

    /* Optional field, The integer h = #E(Fq)/n, can be left NULL */
    
} EC_PARA_S;

/* Generic structure to pass parameters for key generation */

/**
* @defgroup ALG_PARA_S
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct stALG_PARA
* {
*  SEC_UINT32 uiAlgId;
*  union
*      {
*       RSA_PARA_S* rsa;
*       DSA_PARA_S* dsa;
*       EC_PARA_S*  ec;
*       DH_PARA_S*  dh;
*      }para;
* }ALG_PARA_S;
* @endcode
*
* @datastruct uiAlgId Algorithm id for which parameters are passed.
* @datastruct rsa RSA parameter structure.
* @datastruct dsa DSA parameter structure.
* @datastruct ec EC parameter structure.
* @datastruct dh DH parameter structure.
* @datastruct para Holds the algorithm specific parameter structure.
*/

typedef struct stALG_PARA
{
    SEC_UINT32      uiAlgId;  

    /* Algorithm id for which parameters are passed */
    
    union
    {
        RSA_PARA_S*     rsa;  /* RSA parameter structure */
        DSA_PARA_S*     dsa;  /* DSA parameter structure */
        EC_PARA_S*      ec;   /* EC parameter structure */
        DH_PARA_S*      dh;   /* DH parameter structure */
    } para;         /* Holds the algorithm specific parameter structure */
} ALG_PARA_S;

/* The crypto key struct for asymmetric algorithms */

/**
* @defgroup SEC_PKEY_S
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct stSEC_PKEY 
* {
*  SEC_INT32 type;
*  SEC_VOID* pKey;
*  SEC_INT references;
* }SEC_PKEY_S;
* @endcode
*
* @datastruct type Contains algorithm id - 
do not manipulate fields directly.
* @datastruct pKey Points to the key structure.
* @datastruct references Reference count. Object 
is freed only if reference drops to 0.
*/

typedef struct stSEC_PKEY 
{
    SEC_INT32       type;               

    /* Contains algorithm id - don't manipulate fields directly */
    
    SEC_VOID*       pKey;               

    /* Points to the key struct */
    
    SEC_INT         references;         

    /* Reference count, object is freed only if ref drops to 0 */
    
} SEC_PKEY_S;


/* Asymmetric KEY type, public or private */
#define CRYPT_PKEY_UNKNOWN      0UL         /* key type is unknown */
#define CRYPT_PKEY_PUBLIC       0x1UL       /* key type is public */
#define CRYPT_PKEY_PRIVATE      0x2UL       /* key type is private */
#define CRYPT_PKEY_PAIR         (CRYPT_PKEY_PUBLIC | CRYPT_PKEY_PRIVATE)    

/* key type is key-pair */

/* Macro to check key type - public or private */
#define CRYPT_IS_PKEY_PUBLIC(x)     ((x) & CRYPT_PKEY_PUBLIC)
#define CRYPT_IS_PKEY_PRIVATE(x)    ((x) & CRYPT_PKEY_PRIVATE)
#define CRYPT_IS_PKEY_PAIR(x)       ((x) & CRYPT_PKEY_PAIR)
#define CRYPT_IS_PKEY_UNDEF(x)      (((x) == CRYPT_PKEY_UNKNOWN) || \
                    ((x) & ~(CRYPT_PKEY_PUBLIC|CRYPT_PKEY_PRIVATE)))

/* Identifies type of field for Elliptic curve algorithms */
#define CRYPT_EC_FIELD_PRIME        (0x1UL)         /* Prime field */
#define CRYPT_EC_FIELD_C2_POLY      (0x2UL)         /* Binary field */

/* Identifies type of polynomial for a binary field elliptic curve */
#define CRYPT_EC_C2_BASIS_TRI       (0x1UL)         /* Trinomial */
#define CRYPT_EC_C2_BASIS_PENTA     (0x2UL)         /* Pentanomial */

/* Default key length for RC2 block cipher */
#define RC2_DEFAULT_KEYLEN      16

/* Default key length for RC4 stream cipher */
#define RC4_DEFAULT_KEYLEN      16  

/* Default key length for Blowfish block cipher */
#define BF_DEFAULT_KEYLEN      16 

/* for undef */
#define UNDEF                  (-1)
#define MODE_SOFT               0
#define MODE_SSX31B_LINUX       1
#define MODE_SSX31B_VXWORKS     2
#define MODE_WIN32_USBKEY       3


extern SEC_INT  g_modeFlag; 

/* Global flag to denote ssx31B device is being used */


/* Class of cryptographic algorithms supported. 
Used to check for a valid crypto algorithm */

/**
* @defgroup SEC_ALG_CATEGORY_E
* @ingroup sec_cryptoEnum
* @par Prototype
* @code
* typedef enum
* {
*  CRYPT_ALG,
*  CRYPT_SYM,
*  CRYPT_ASYM,
*  CRYPT_DIGEST,
*  CRYPT_SIGN
* }SEC_ALG_CATEGORY_E;
* @endcode
*
* @datastruct CRYPT_ALG Identifies any crypto algorithm, 
sym, asym, hash or sign.
* @datastruct CRYPT_SYM Identifies a symmetric algorithm.
* @datastruct CRYPT_ASYM Identifies an asymmetric algorithm.
* @datastruct CRYPT_DIGEST Identifies a hash algorithm.
* @datastruct CRYPT_SIGN Identifies a sign algorithm.
*/

typedef enum
{
    CRYPT_ALG,                          

    /* identifies any crypto algorithm, sym, asym, hash or sign */
    
    CRYPT_SYM,         /* identifies a symmetric algorithm */
    CRYPT_ASYM,      /* identifies an asymmetric algorithm */
    CRYPT_DIGEST,        /* identifies a hash algorithm */
    CRYPT_SIGN       /* identifies a sign algorithm */
} SEC_ALG_CATEGORY_E;


#ifndef __IPSI_NO_DH_PARA__

/**
* @defgroup SEC_DH_PRIME_E
* @ingroup sec_cryptoEnum
* @par Prototype
* @code
* typedef enum
* {
*    GROUPID_RFC2409_1 = 0,
*    GROUPID_RFC2409_2,
*    GROUPID_RFC3256_5,
*    GROUPID_RFC3526_14,
*    GROUPID_RFC3526_15,
*    GROUPID_RFC3526_16,
*    SEC_RFC_PRIME_MAX
* }SEC_DH_PRIME_E;
*
* @endcode
*
* @datastruct GROUPID_RFC2409_1=0 Identifies prime of bit length 768
* defined in rfc 2409
* @datastruct GROUPID_RFC2409_2 Identifies prime of bit length 1024
* defined in rfc 2409
* @datastruct GROUPID_RFC3256_5 Identifies prime of bit length 1536 
* defined in rfc 3526
* @datastruct GROUPID_RFC3526_14 Identifies prime of bit length 2048
* defined in rfc 3526
* @datastruct GROUPID_RFC3526_15 Identifies prime of bit length 3072 
* defined in rfc 3526
* @datastruct GROUPID_RFC3526_16 Identifies prime of bit length 4096 
* defined in rfc 3526
* @datastruct SEC_RFC_PRIME_MAX This is the upper limit of SEC_RFC_DH_PRIME_E.
* In future if, any new prime added in this enum 
* should be defined above SEC_RFC_PRIME_MAX 
*/

typedef enum
{
    //DH Group 1
    //768 Bit
    GROUPID_RFC2409_1 = 0,

    //DH Group 2
    //1024 Bit
    GROUPID_RFC2409_2,

    //DH Group 5
    //1536 Bit
    GROUPID_RFC3256_5,

    //DH Group 14
    //2048 Bit
    GROUPID_RFC3526_14,

    //DH Group 15
    //3072 Bit
    GROUPID_RFC3526_15,

    //DH Group 16
    //4096 Bit
    GROUPID_RFC3526_16,
    SEC_RFC_PRIME_MAX
}SEC_DH_PRIME_E;

#endif

/**
* @defgroup IPSI_ECDH_PRIMITIVE_E
* @ingroup sec_cryptoEnum
* @par Prototype
* @code
* typedef enum
* {
*    IPSI_EC_STANDARD_DH_PRIMITIVE,
*    IPSI_EC_COFACTOR_DH_PRIMITIVE
* } IPSI_ECDH_PRIMITIVE_E;
*
* @endcode
*
* @dataenum IPSI_EC_STANDARD_DH_PRIMITIVE=0 Identifies ecdh shared key generation without cofactor
* @dataenum IPSI_EC_COFACTOR_DH_PRIMITIVE Identifies ecdh shared key generation with cofactor muliplication
*/
typedef enum
{
    IPSI_EC_STANDARD_DH_PRIMITIVE,
    IPSI_EC_COFACTOR_DH_PRIMITIVE
} IPSI_ECDH_PRIMITIVE_E;

/*
  Enum to identify the hash operation to be considered during SM2 KEP operation.
*/

/**
* @defgroup IPSI_SM2_KEP_HASHTYPE_E
* @ingroup sec_cryptoEnum
* @par Prototype
* @code
* typedef enum
* {
*    IPSI_SM2_HASH_SB,
*    IPSI_SM2_HASH_S1,
*    IPSI_SM2_HASH_SA,
*    IPSI_SM2_HASH_S2
* } IPSI_SM2_KEP_HASHTYPE_E;
*
* @endcode
*
* @dataenum IPSI_SM2_HASH_SB Identifies hash type Sb
* @dataenum IPSI_SM2_HASH_S1 Identifies hash type S1
* @dataenum IPSI_SM2_HASH_SA Identifies hash type Sa
* @dataenum IPSI_SM2_HASH_S2 Identifies hash type S2
*/
typedef enum
{
    IPSI_SM2_HASH_SB,
    IPSI_SM2_HASH_S1,
    IPSI_SM2_HASH_SA,
    IPSI_SM2_HASH_S2
} IPSI_SM2_KEP_HASHTYPE_E;


/*
  stores the state of the random number generator - this 
  can be used for serializing the
  state of the rng generator
*/

/**
* @defgroup PRNG_STATE_S
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct stPRNG_STATE
* {
*  SEC_INT8 aState[PRNG_STATE_OCTS];
* }PRNG_STATE_S;
* @endcode
*
* @datastruct aState[PRNG_STATE_OCTS] Holds the state as a series of octets.
*/

typedef struct stPRNG_STATE
{
    SEC_INT8 aState[PRNG_STATE_OCTS];   

    /* Holds the state as a series of octets */
    
} PRNG_STATE_S;


/*
  This type defines the structure which store Z and lenght of Z 
*/

/**
* @defgroup IPSI_SM2_Z_S
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct stSM2Z
* {
*  SEC_UCHAR *pucZ;
*  SEC_UINT32 uiZLen;
* }IPSI_SM2_Z_S;

* @endcode
*
* @datastruct pucZ Hold the Z value of specific user
* @datastruct uiZLen Length of Z value
*/

typedef struct stSM2Z
{
    SEC_UCHAR *pucZ;
    SEC_UINT32 uiZLen;
}IPSI_SM2_Z_S;

/*
  This type defines the structure which lists the different items 
  that is requried in the CRYPT_sm2KEPGenKey function. 
*/

/**
* @defgroup IPSI_SM2_KEP_GENKEY_OP_DATA_S
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct stSM2KEPGenKeyOpData
* {
*  CRYPT_SM2_KEP_CTX ctx;
*  IPSI_SM2_Z_S stZA;
*  IPSI_SM2_Z_S stZB;
*  SEC_PKEY_S *pRemotePubKey;
*  EC_POINT_S *pRemoteR;
* }IPSI_SM2_KEP_GENKEY_OP_DATA_S;
* @endcode
*
* @datastruct ctx SM2 key exchange protocol context
* @datastruct pstZA User identifier ZA as per standard. 
*  Here ZA is the identifier of the peer who initiates the key exchange protocol
* @datastruct pstZB User identifier ZB as per standard.
*  Here ZB is the identifier of the peer who receives EC point R and
*  public key first during the key exchange protocol.
* @datastruct pRemotePubKey Contains the EC public key from the remote side
* @datastruct pRemoteR Contains the EC point R received from the remote side
*/
typedef struct stSM2KEPGenKeyOpData
{
    CRYPT_SM2_KEP_CTX ctx;
    IPSI_SM2_Z_S stZA;
    IPSI_SM2_Z_S stZB;
    SEC_PKEY_S *pRemotePubKey;
    EC_POINT_S *pRemoteR;
}IPSI_SM2_KEP_GENKEY_OP_DATA_S;



/*
    Func Name:  CRYPT_encryptInit
*/

/** 
* @defgroup CRYPT_encryptInit
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_encryptInit(
* CRYPT_CTX* pCtx,
* SEC_UINT32 ulAlgId,
* SEC_UCHAR* pucKey,
* SEC_UINT32 ulKeyLen,
* SEC_UCHAR* pucIV,
* SEC_UINT32 ulIVLen);
* @endcode
*
* @par Purpose
* This is used to create symmetric context for encryption.
*
* @par Description
* CRYPT_encryptInit function initializes the  
symmetric context structure for symmetric encryption. Key length, blocksize,
* encryption, and decryption function  pointers
are initialized using the Symg_aAlgTable. CarryBlock is allocated memory.
* Feedback is also allocated memory if needed.
*
* @param[in] ulAlgId The algorithm Id [N/A]
* @param[in] pucKey The key value to be used [N/A]
* @param[in] ulKeyLen The length of the key [N/A]
* @param[in] pucIV InitializationVector(CBC, CFB, OFB algorithm modes) [N/A]
* @param[in] ulIVLen Length of IV. 0 if no IV [N/A]
* @param[out] pCtx Address of the context to be initialized [N/A]
*
* @retval SEC_UINT32 Invalid argument [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Invalid Algorithm Id [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 Invalid Padding Mode. Padding mode set on Algorithm
is not defined
* [SEC_CRYPT_ERR_UNDEFINED_PADDING|N/A]
* @retval SEC_UINT32 Invalid Keylength for alg [SEC_ERR_INVALID_KEY_LEN|N/A]
* @retval SEC_UINT32 Invalid IVlength for alg [SEC_ERR_INVALID_IV_LEN|N/A]
* @retval SEC_UINT32 On success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 On error [SEC_ERR|N/A]
*
* @par Required Header File
* sec_crupto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_encryptInit(
    CRYPT_CTX*      pCtx,
    SEC_UINT32      ulAlgId,
    SEC_UCHAR*      pucKey,
    SEC_UINT32      ulKeyLen,
    SEC_UCHAR*      pucIV,
    SEC_UINT32      ulIVLen);

/*
    Func Name:  CRYPT_encryptUpdate
*/
/** 
* @defgroup CRYPT_encryptUpdate
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_encryptUpdate (
* CRYPT_CTX   ctx,
* SEC_UCHAR*  pucPlainText,
* SEC_UINT32  ulPlainLen,
* SEC_UCHAR*  pucCipherText,
* SEC_UINT32* pulCLen);
* @endcode
*
* @par Purpose
* This is used to encrypt plain text to cipher text 
using encryption algorithm.
*
* @par Description
* CRYPT_encryptUpdate function uses the initialized
symmetric context to encrypt plaintext to get ciphertext. It uses
* symmetric encryption. If plain text length is less 
than block size of encryption algorithm it carry forwards to
* CRYPT_encryptFinal. If plain text length is greater 
than block size of encryption algorithm then multiple block size
* of plain text encrypts and rest carry forward to final block.
*
* @param[in] ctx The context to be used [N/A]
* @param[in] pucPlainText Plaintext to be encrypted [N/A]
* @param[in] ulPlainLen Length of plaintext [N/A]
* @param[out] pucCipherText Encrypted ciphertext [N/A]
* @param[out] pulCLen Length of encrypted ciphertext [N/A]
*
* @retval SEC_UINT32 If invalid argument [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If invalid context [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 On successful return [Success|N/A]
* @retval SEC_UINT32 On other error [SEC_ERR|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_encryptUpdate (
    CRYPT_CTX       ctx,
    SEC_UCHAR*      pucPlainText,
    SEC_UINT32      ulPlainLen,
    SEC_UCHAR*      pucCipherText,
    SEC_UINT32*     pulCLen);

/*
    Func Name:  CRYPT_encryptFinal
*/
/** 
* @defgroup CRYPT_encryptFinal
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_encryptFinal (
* CRYPT_CTX*  pCtx,
* SEC_UCHAR*  pucCipherText,
* SEC_UINT32* pulCLen);
* @endcode
*
* @par Purpose
* This is used to encrypt only last block of plain text to
cipher text using encryption algorithm.
*
* @par Description
* CRYPT_encryptFinal function completes a symmetric
encryption operation. It frees the symmetric context and outputs
* the last block in case of block ciphers.
If encryptinit succeeds, encryptfinal must be called to free the context.
*
* @param[in] pCtx Address of the context to be used [N/A]
* @param[out] pucCipherText Last Encrypted ciphertext of the session [N/A]
* @param[out] pulCLen Length of last encrypted ciphertext [N/A]
*
* @retval SEC_UINT32 If invalid argument [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If invalid context [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 Invalid pad mode in context 
[SEC_CRYPT_ERR_INVALID_PADDING|N/A]
* @retval SEC_UINT32 Invalid plaintext length given 
for encryption in update and padding_mode = BLOCK_PADDING_NONE.
* plaintext length was not integral number of blocks)
[SEC_ERR_INVALID_DATA_LEN|N/A]
* @retval SEC_UINT32 On successful return [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 On other error [SEC_ERR|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_encryptFinal (
    CRYPT_CTX*      pCtx,
    SEC_UCHAR*      pucCipherText,
    SEC_UINT32*     pulCLen);

/*
    Func Name:  CRYPT_encrypt
*/

/** 
* @defgroup CRYPT_encrypt
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_encrypt (
* SEC_UINT32 ulAlgId,
* SEC_UCHAR* pucKey,
* SEC_UINT32 ulKeyLen,
* SEC_UCHAR* pucIV,
* SEC_UINT32 ulIVLen,
* SEC_UCHAR* pucPlainText,
* SEC_UINT32 ulPlainLen,
* SEC_UCHAR* pucCipherText,
* SEC_UINT32* pulCLen);
* @endcode
*
* @par Purpose
* This is used to encrypt plain text to cipher text 
using encryption algorithm.
*
* @par Description
* CRYPT_encrypt function encrypts plain text to cipher text 
using encryption algorithm. It creates symmetric context by
* creating algorithm object, padding object, opmode object.
After encryption, symmetric context needs to be freed.
*
* @param[in] ulAlgId The algorithm Id [N/A]
* @param[in] pucKey The key value to be used [N/A]
* @param[in] ulKeyLen The length of the key [N/A]
* @param[in] pucIV InitializationVector(CBC,CFB,OFB 
algorithm modes) [N/A]
* @param[in] ulIVLen Length of IV. pass 0 if no IV [N/A]
* @param[in] pucPlainText Plaintext to be encrypted [N/A]
* @param[in] ulPlainLen Length of plaintext [N/A]
* @param[out] pucCipherText Encrypted ciphertext [N/A]
* @param[out] pulCLen Length of encrypted ciphertext [N/A]
*
* @retval SEC_UINT32 On Memory allocation failure 
[SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If invalid Algorithm Id [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 If invalid Padding Mode.
Padding mode set on Algorithm is not defined
* [SEC_CRYPT_ERR_UNDEFINED_PADDING |N/A]
* @retval SEC_UINT32 If invalid Keylength for
algorithm [SEC_ERR_INVALID_KEY_LEN|N/A]
* @retval SEC_UINT32 If invalid IVlength for 
algorithm [SEC_ERR_INVALID_IV_LEN|N/A]
* @retval SEC_UINT32 If invalid plaintext length 
given for encryption and padding_mode = BLOCK_PADDING_NONE.
* (plaintext length was not integral no. of blocks) 
[SEC_ERR_INVALID_DATA_LEN|N/A]
* @retval SEC_UINT32 On successful return [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 On other error [SEC_ERR|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/



CRYPTOLINKDLL SEC_UINT32 CRYPT_encrypt (
    SEC_UINT32      ulAlgId,
    SEC_UCHAR*      pucKey,
    SEC_UINT32      ulKeyLen,
    SEC_UCHAR*      pucIV,
    SEC_UINT32      ulIVLen,
    SEC_UCHAR*      pucPlainText,
    SEC_UINT32      ulPlainLen,
    SEC_UCHAR*      pucCipherText,
    SEC_UINT32*     pulCLen);

/*
    Func Name:  CRYPT_decryptInit
*/
/** 
* @defgroup CRYPT_decryptInit
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_decryptInit (
* CRYPT_CTX*       pCtx,
* SEC_UINT32       ulAlgId,
* const SEC_UCHAR* pucKey,
* SEC_UINT32       ulKeyLen,
* const SEC_UCHAR* pucIV,
* SEC_UINT32       ulIVLen);
* @endcode
*
* @par Purpose
* This is used to create symmetric context for decryption.
*
* @par Description
* CRYPT_decryptInit function initializes the  
symmetric context structure for symmetric decryption. 
Key length, blocksize,
* decryption, decryption function pointers are 
initialized using the Symg_aAlgTable. CarryBlock is allocated memory.
* Feedback is also allocated memory if needed.
*
* @param[in] ulAlgId The algorithm Id [N/A]
* @param[in] pucKey The key value to be used [N/A]
* @param[in] ulKeyLen The length of the key [N/A]
* @param[in] pucIV InitializationVector(CBC, CFB, 
OFB algorithm modes) [N/A]
* @param[in] ulIVLen Length of IV. pass 0 if no IV [N/A]
* @param[out] pCtx Address of the context to be initialized [N/A]
*
* @retval SEC_INT32 If invalid argument [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_INT32 If invalid Algorithm Id [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_INT32 If invalid Padding Mode. 
Padding mode set on Algorithm is not defined
* [SEC_CRYPT_ERR_UNDEFINED_PADDING|N/A]
* @retval SEC_INT32 If invalid Keylength for
algorithm [SEC_ERR_INVALID_KEY_LEN|N/A]
* @retval SEC_INT32 If invalid IVlength for 
algorithm [SEC_ERR_INVALID_IV_LEN|N/A]
* @retval SEC_INT32 On successful return [SEC_SUCCESS|N/A]
* @retval SEC_INT32 On other error [SEC_ERR|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_decryptInit (
    CRYPT_CTX*      pCtx,
    SEC_UINT32      ulAlgId,
    const SEC_UCHAR* pucKey,
    SEC_UINT32      ulKeyLen,
    const SEC_UCHAR* pucIV,
    SEC_UINT32      ulIVLen);

/*
    Func Name:  CRYPT_decryptUpdate
*/

/** 
* @defgroup CRYPT_decryptUpdate
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_decryptUpdate (
* CRYPT_CTX   ctx,
* SEC_UCHAR*  pucCipherText,
* SEC_UINT32  ulCLen,
* SEC_UCHAR*  pucPlainText,
* SEC_UINT32* pulPLen);
* @endcode
*
* @par Purpose
* This is used to decrypt cipher text to plain 
text using decryption algorithm.
*
* @par Description
* CRYPT_decryptUpdate function uses the initialized 
symmetric context to decrypt ciphertext to get plaintext.
It uses
* symmetric decryption. If cipher text length is 
less than or equal to block size of decryption 
algorithm, it carry
* forwards to CRYPT_decryptFinal. If cipher text 
length is greater than block size of decryption algorithm then multiple
* block size of cipher text decrypts and rest are 
carry forward to final block.
*
* @param[in] ctx The context to be used [N/A]
* @param[in] pucCipherText Encrypted ciphertext [N/A]
* @param[in] ulCLen Ciphertext Length [N/A]
* @param[out] pucPlainText Decrypted plaintext [N/A]
* @param[out] pulPLen Length of decrypted plaintext [N/A]
*
* @retval SEC_UINT32 If invalid argument [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If invalid context [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 On successful return [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 On other error [SEC_ERR|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/


CRYPTOLINKDLL SEC_UINT32 CRYPT_decryptUpdate (
    CRYPT_CTX       ctx,
    SEC_UCHAR*      pucCipherText,
    SEC_UINT32      ulCLen,
    SEC_UCHAR*      pucPlainText,
    SEC_UINT32*     pulPLen);


/*
    Func Name:  CRYPT_decryptFinal
*/

/** 
* @defgroup CRYPT_decryptFinal
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_decryptFinal (
* CRYPT_CTX*  pCtx,
* SEC_UCHAR*  pucPlainText,
* SEC_UINT32* pulPLen);
* @endcode
*
* @par Purpose
* This is used to decrypt only last block of cipher 
text to plain text using decryption algorithm.
*
* @par Description
* CRYPT_decryptFinal function completes one symmetric 
decryption operation. It frees the context. In case of block ciphers
* the remaining of the decrypted plaintext is the output. 
In stream ciphers, as all the plaintext would have been
* output in decryptupdate, there will not be any plantext
output. If decryptinit succeeds, decryptfinal must be called
* to free the context.
*
* @param[in] pCtx Address of The context to be used [N/A]
* @param[out] pucPlainText Final decrypted plaintext [N/A]
* @param[out] pulPLen Length of last decrypted plaintext [N/A]
*
* @retval SEC_UINT32 If invalid argument [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If invalid context [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If invalid pad mode in context
[SEC_CRYPT_ERR_UNDEFINED_PADDING|N/A]
* @retval SEC_UINT32 The pad bits are incorrect. 
When after decrypting the padding bits dont match the pad mode. 
It can be
* due to incorrect Key or IV as that will produce junk
plaintext with random padding bits, which dont match the padding
* mode. [SEC_CRYPT_ERR_INVALID_PADDING|N/A]
* @retval SEC_UINT32 If invalid ciphertext length given for 
decryption. (ciphertext length was not integral no. of blocks)
* [SEC_ERR_INVALID_DATA_LEN|N/A]
* @retval SEC_UINT32 On successful return [SEC_SUCCESS|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_decryptFinal (
    CRYPT_CTX* pCtx,
    SEC_UCHAR * pucPlainText,
    SEC_UINT32 * pulPLen);

/*
    Func Name:  CRYPT_decrypt
*/

/** 
* @defgroup CRYPT_decrypt
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_decrypt (
* SEC_UINT32       ulAlgId,
* const SEC_UCHAR* pucKey,
* SEC_UINT32       ulKeyLen,
* const SEC_UCHAR* pucIV,
* SEC_UINT32       ulIVLen,
* SEC_UCHAR*       pucCipherText,
* SEC_UINT32       ulCLen,
* SEC_UCHAR*       pucPlainText,
* SEC_UINT32*      pulPLen);
* @endcode
*
* @par Purpose
* This is used to decrypt cipher text to plain text 
using decryption algorithm.
*
* @par Description
* CRYPT_decrypt function decrypts cipher text to plain
text using decryption algorithm. It creates 
symmetric context by
* creating algorithm object, padding object,
opmode object. After decryption, symmetric context needs to be freed.
*
* @param[in] ulAlgId The algorithm Id [N/A]
* @param[in] pucKey The key value to be used [N/A]
* @param[in] ulKeyLen The length of the key [N/A]
* @param[in] pucIV InitializationVector(CBC FB,OFB modes) [N/A]
* @param[in] pucCipherText To be decrypted ciphertext [N/A]
* @param[in] ulCLen Length of ciphertext [N/A]
* @param[in] ulIVLen Length of IV. pass 0 if no IV [N/A]
* @param[out] pucPlainText Decrypted Plaintext [N/A]
* @param[out] pulPLen Length of plaintext [N/A]
*
* @retval SEC_UINT32 If invalid Algorithm Id 
[SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 If invalid Padding Mode. 
Padding mode set on Algorithm is not defined
* [SEC_CRYPT_ERR_UNDEFINED_PADDING|N/A]
* @retval SEC_UINT32 The pad bits are incorrect. 
When after decrypting, the padding bits does not match the pad mode.
* It can be due to incorrect Key or IV as that will
produce junk plaintext with random padding bits, which does not match
* the padding mode [SEC_CRYPT_ERR_INVALID_PADDING|N/A]
* @retval SEC_UINT32 If invalid Keylength for algprithm 
[SEC_ERR_INVALID_KEY_LEN|N/A]
* @retval SEC_UINT32 If invalid IVlength for algorithm 
[SEC_ERR_INVALID_IV_LEN|N/A]
* @retval SEC_UINT32 Invalid ciphertext length given 
for decryption in update. (ciphertext length was not integral number
* of blocks) [SEC_ERR_INVALID_DATA_LEN|N/A]
* @retval SEC_UINT32 On successful return [SEC_SUCCESS|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_decrypt (
    SEC_UINT32 ulAlgId,
    const SEC_UCHAR * pucKey,
    SEC_UINT32 ulKeyLen,
    const SEC_UCHAR * pucIV,
    SEC_UINT32 ulIVLen,
    SEC_UCHAR * pucCipherText,
    SEC_UINT32 ulCLen,
    SEC_UCHAR * pucPlainText,
    SEC_UINT32 * pulPLen);

/*
    Func Name:  CRYPT_digestInit
*/

/** 
* @defgroup CRYPT_digestInit
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_digestInit (
* CRYPT_CTX* pCtx,
* SEC_UINT32 ulAlgType);
* @endcode
*
* @par Purpose
* This is used to initialize the context for a digest operation.
*
* @par Description
* CRYPT_digestInit function initializes the context for
a digest operation. This function must be called before any
* Update or Final operations. This method of digesting
is used when data is present in multiple buffers or not available
* all at once.
*
* @param[in] ulAlgType The algorithm id for digest [N/A]
* @param[out] pCtx The context which will be filled [N/A]
*
* @retval SEC_UINT32 If context is initialized [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If algorithm undefined [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 If memory alloc for 
context failed [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If arguments are missing [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_digestInit (
    CRYPT_CTX* pCtx,
    SEC_UINT32 ulAlgType);

/*
    Func Name:  CRYPT_digestUpdate
*/
/** 
* @defgroup CRYPT_digestUpdate
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_digestUpdate (
* CRYPT_CTX  ctx,
* SEC_UCHAR* pucData,
* SEC_UINT32 ulDataLen);
* @endcode
*
* @par Purpose
* This is used to perform digest operation on chunks of data.
*
* @par Description
* CRYPT_digestUpdate function performs digest operation on 
chunks of data. This method of digesting is used when data is
* present in multiple buffers or not available all at once.  
A digestInit must have been called before calling this
* function.
*
* @param[in] ctx The context for digest [N/A]
* @param[in] pucData The input data [N/A]
* @param[in] ulDataLen The input data length [N/A]
*
* @retval SEC_UINT32 If partial digest is calculated [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If context values are not correct 
[SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If arguments are missing [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_digestUpdate (
    CRYPT_CTX ctx,
    SEC_UCHAR * pucData,
    SEC_UINT32 ulDataLen);

/*
    Func Name:  CRYPT_digestFinal
*/
/** 
* @defgroup CRYPT_digestFinal
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_digestFinal (
* CRYPT_CTX*  pCtx,
* SEC_UCHAR*  pucDigest,
* SEC_UINT32* pulDigestLen);
* @endcode
*
* @par Purpose
* This is used to complete digest operation on remaining data, and is
called at the end of digest operation.
*
* @par Description
* CRYPT_digestFinal function completes digest operation on remaining data, and
is called at the end of digest operation.
* A digestInit must have been called before calling this function. This 
function calculates the digest and frees the
* context. The memory for digest must already have been allocated.
*
* @param[in] pCtx The context for digest [N/A]
* @param[out] pucDigest The digest [N/A]
* @param[out] pulDigestLen The digest length [N/A]
*
* @retval SEC_UINT32 If digest is calculated [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If context values are not correct 
[SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If arguments are invalid[SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_digestFinal (
    CRYPT_CTX* pCtx,
    SEC_UCHAR * pucDigest,
    SEC_UINT32 * pulDigestLen);

/*
    Func Name:  CRYPT_digest
*/

/** 
* @defgroup CRYPT_digest
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_digest (
* SEC_UINT32  ulAlgType,
* SEC_UCHAR*  pucData,
* SEC_UINT32  ulDataLen,
* SEC_UCHAR*  pucDigest,
* SEC_UINT32* pulDigestLen);
* @endcode
*
* @par Purpose
* This is used to compute digest of a given data block.
*
* @par Description
* CRYPT_digest function computes digest of a given data block. Calls init,
update, and final. This function is used when
* data is present all at once. There is no need of calling Init, Update, 
Final and digest can be calculated in one go.
* Also, context is not required.
*
* @param[in] ulAlgType Digest algorithm [N/A]
* @param[in] pucData The data [N/A]
* @param[in] ulDataLen The data length [N/A]
* @param[out] pucDigest The digest [N/A]
* @param[out] pulDigestLen The digest length [N/A]
*
* @retval SEC_UINT32 If digest is calculated [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If context values got corrupted internally 
[SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If arguments are missing [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If algorithm undefined [SEC_ERR_INVALID_ALGID|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_digest (
    SEC_UINT32 ulAlgType,
    SEC_UCHAR * pucData,
    SEC_UINT32 ulDataLen,
    SEC_UCHAR * pucDigest,
    SEC_UINT32 * pulDigestLen);

/*
    Func Name:  CRYPT_hmacInit
*/

/** 
* @defgroup CRYPT_hmacInit
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_hmacInit (
* CRYPT_CTX* pCtx,
* SEC_UINT32 ulAlgType,
* const SEC_UCHAR * pucKey,
* SEC_UINT32 ulKlen);
* @endcode
*
* @par Purpose
* This is used to initialize the context for a hmac operation.
*
* @par Description
* CRYPT_hmacInit function initializes the context for a hmac operation. 
This function must be called before any Update
* or Final operations. This method of MACing is used when data is present
in multiple buffers or not available all at once.
*
* @param[in] ulAlgType The algorithm id for HMAC [N/A]
* @param[in] pucKey Key for hmac [N/A]
* @param[in] ulKlen Key length [N/A]
* @param[out] pCtx The context which will be filled [N/A]
*
* @retval SEC_UINT32 If context is initialized [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If algorithm undefined [SEC_ERR_INVALID_ALGID|n/A]
* @retval SEC_UINT32 If memory alloc for context failed 
[SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If arguments are missing [SEC_ERR_INVALID_ARG|N/A] 
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_hmacInit (
    CRYPT_CTX* pCtx,
    SEC_UINT32 ulAlgType,
    const SEC_UCHAR * pucKey,
    SEC_UINT32 ulKlen);

/*
    Func Name:  CRYPT_cmacInit
*/

/** 
* @defgroup CRYPT_cmacInit
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_cmacInit (
* CRYPT_CTX* pCtx,
* SEC_UINT32 ulAlgType,
* const SEC_UCHAR * pucKey,
* SEC_UINT32 ulKlen);
* @endcode
*
* @par Purpose
* This is used to initialize the context for a cmac operation.
*
* @par Description
* CRYPT_cmacInit function initializes the context for a cmac operation.
This function must be called before any Update
* or Final operations. This method of MACing is used when data is
present in multiple buffers or not available all at once.
*
* @param[in] ulAlgType The algorithm id for CMAC [N/A]
* @param[in] pucKey Key for cmac [N/A]
* @param[in] ulKlen Key length [N/A]
* @param[out] pCtx The context which will be filled [N/A]
*
* @retval SEC_UINT32 If context is initialized [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If algorithm undefined [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 If memory alloc for context 
failed [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If arguments are missing [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If the key length is invalid [SEC_ERR_INVALID_KEY_LEN|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_cmacInit (
    CRYPT_CTX* pCtx,
    SEC_UINT32 ulAlgType,
    const SEC_UCHAR * pucKey,
    SEC_UINT32 ulKlen);

/*
    Func Name:  CRYPT_hmacUpdate
*/
/** 
* @defgroup CRYPT_hmacUpdate
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_hmacUpdate (
* CRYPT_CTX ctx,
* SEC_UCHAR * pucData,
* SEC_UINT32 ulDataLen);
* @endcode
*
* @par Purpose
* This is used to perform hmac operation on chunks of data.
*
* @par Description
* CRYPT_hmacUpdate function performs hmac operation on 
chunks of data. This method of MACing is used when data is present
* in multiple buffers or not available all at once. 
A hmacInit must have been called before calling this function.
*
* @param[in] ctx The context for HMAC [N/A]
* @param[in] pucData The input data [N/A]
* @param[in] ulDataLen The input data length [N/A]
*
* @retval SEC_UINT32 If partial digest is calculated 
[SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If context values are not correct 
[SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If arguments are missing [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_hmacUpdate (
    CRYPT_CTX ctx,
    SEC_UCHAR * pucData,
    SEC_UINT32 ulDataLen);

/*
    Func Name:  CRYPT_cmacUpdate
*/

/** 
* @defgroup CRYPT_cmacUpdate
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_cmacUpdate (
* CRYPT_CTX ctx,
* SEC_UCHAR * pucData,
* SEC_UINT32 ulDataLen);
* @endcode
*
* @par Purpose
* This is used to perform cmac operation on chunks of data.
*
* @par Description
* CRYPT_cmacUpdate function performs cmac operation on chunks of data.
This method of MACing is used when data is present
* in multiple buffers or not available all at once. A cmacInit must 
have been called before calling this function.
*
* @param[in] ctx The context for CMAC [N/A]
* @param[in] pucData The input data [N/A]
* @param[in] ulDataLen The input data length [N/A]
*
* @retval SEC_UINT32 If partial digest is calculated [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If context values are not 
correct [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If arguments are missing [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_cmacUpdate (
    CRYPT_CTX ctx,
    SEC_UCHAR * pucData,
    SEC_UINT32 ulDataLen);

/*
    Func Name:  CRYPT_hmacFinal
*/

/** 
* @defgroup CRYPT_hmacFinal
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_hmacFinal (
* CRYPT_CTX*  pCtx,
* SEC_UCHAR*  pucMAC,
* SEC_UINT32* pulMACLen);
* @endcode
*
* @par Purpose
* This is used to complete hmac operation on remaining data. 
Called at the end of MAC operation.
*
* @par Description
* CRYPT_hmacFinal function completes hmac operation on 
remaining data. It is called at the end of MAC operation. A hmacInit
* must have been called before calling this function. 
This function calculates the MAC and frees the context. The memory
* for MAC must have already been allocated.
*
* @param[in] pCtx The context for digest [N/A]
* @param[out] pucMAC The hashed MAC [N/A]
* @param[out] pulMACLen The MAC length [N/A]
*
* @retval SEC_UINT32 If digest is calculated [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If context values are not correct
[SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If arguments are missing [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_hmacFinal (
    CRYPT_CTX* pCtx,
    SEC_UCHAR * pucMAC,
    SEC_UINT32 * pulMACLen);

/*
    Func Name:  CRYPT_cmacFinal
*/

/** 
* @defgroup CRYPT_cmacFinal
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_cmacFinal (
* CRYPT_CTX* pCtx,
* SEC_UCHAR* pucMAC,
* SEC_UINT32* pulMACLen);
* @endcode
*
* @par Purpose
* This is used to complete cmac operation on remaining data. 
Called at the end of MAC operation.
*
* @par Description
* CRYPT_cmacFinal function completes cmac operation on 
remaining data. It is called at the end of MAC operation. A cmacInit
* must have been called before calling this function. 
This function calculates the MAC and frees the context. The memory
* for MAC must have already been allocated.
*
* @param[in] pCtx The context for digest [N/A]
* @param[out] pucMAC The hashed MAC [N/A]
* @param[out] pulMACLen The MAC length [N/A]
*
* @retval SEC_UINT32 If digest is calculated [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If context values are not 
correct [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If arguments are missing [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_cmacFinal (
    CRYPT_CTX* pCtx,
    SEC_UCHAR * pucMAC,
    SEC_UINT32 * pulMACLen);

/*
    Func Name:  CRYPT_hmac
*/

/** 
* @defgroup CRYPT_hmac
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_hmac (
* SEC_UINT32 ulAlgType,
* const SEC_UCHAR * pucKey,
* SEC_UINT32 ulKeyLen,
* SEC_UCHAR * pucData,
* SEC_UINT32 ulDataLen,
* SEC_UCHAR * pucMAC,
* SEC_UINT32 * pulMACLen);
* @endcode
*
* @par Purpose
* This is used to compute hmac of a given data block.
*
* @par Description
* CRYPT_hmac function computes hmac of a given data block. 
Calls init, update, and final. This function is used when
* data is present all at once. There is no need of calling 
Init, Update, Final and MAC can be calculated in one go.
* Context is not needed here.
*
* @param[in] ulAlgType HMAC algorithm [N/A]
* @param[in] pucKey The key [N/A]
* @param[in] ulKeyLen The key length [N/A]
* @param[in] pucData The data [N/A]
* @param[in] ulDataLen The data length [N/A]
* @param[out] pucMAC The hashed MAC [N/A]
* @param[out] pulMACLen The digest length [N/A]
*
* @retval SEC_UINT32 If digest is calculated [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If context values are not correct 
[SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If arguments are missing [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory alloc for context
failed [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If algorithm undefined [SEC_ERR_INVALID_ALGID|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_hmac (
    SEC_UINT32 ulAlgType,
    const SEC_UCHAR * pucKey,
    SEC_UINT32 ulKeyLen,
    SEC_UCHAR * pucData,
    SEC_UINT32 ulDataLen,
    SEC_UCHAR * pucMAC,
    SEC_UINT32 * pulMACLen);

/*
    Func Name:  CRYPT_cmac
*/

/** 
* @defgroup CRYPT_cmac
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_cmac (
* SEC_UINT32 ulAlgType,
* const SEC_UCHAR* pucKey,
* SEC_UINT32  ulKeyLen,
* SEC_UCHAR*  pucData,
* SEC_UINT32  ulDataLen,
* SEC_UCHAR*  pucMAC,
* SEC_UINT32* pulMACLen);
* @endcode
*
* @par Purpose
* This is used to compute cmac of a given data block.
*
* @par Description
* CRYPT_cmac function computes cmac  of a given data block.
Calls init, update, and final. This function is used when
* data is present all at once. There is no need of calling 
Init, Update, Final and MAC can be calculated in one go.
* Context is not needed here.
*
* @param[in] ulAlgType CMAC algorithm [N/A]
* @param[in] pucKey The key [N/A]
* @param[in] ulKeyLen The key length [N/A]
* @param[in] pucData The data [N/A]
* @param[in] ulDataLen The data length [N/A]
* @param[out] pucMAC The hashed MAC [N/A]
* @param[out] pulMACLen The digest length [N/A]
*
* @retval SEC_UINT32 If digest is calculated [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If context values are not correct 
[SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If arguments are missing [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory alloc for context 
failed [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If algorithm undefined [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 If the key length is invalid
[SEC_ERR_INVALID_KEY_LEN|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_cmac (
    SEC_UINT32 ulAlgType,
    const SEC_UCHAR * pucKey,
    SEC_UINT32 ulKeyLen,
    SEC_UCHAR * pucData,
    SEC_UINT32 ulDataLen,
    SEC_UCHAR * pucMAC,
    SEC_UINT32 * pulMACLen);


#ifndef __IPSI_NO_AES_XCBC__

/*
    Func Name:  CRYPT_xcbcInit
*/

/** 
* @defgroup CRYPT_xcbcInit
* @ingroup HLF High Level Functions 
* @par Prototype
* @code
* SEC_UINT32 CRYPT_xcbcInit (
*                            CRYPT_CTX* pCtx,
*                            const SEC_UINT32 ulAlgType,
*                            const SEC_UCHAR * pucKey,
*                            const SEC_UINT32 ulKlen);
* @endcode
*
* @par Purpose
* This is used to initialize the context for a xcbc MAC operation.
*
* @par Description
* CRYPT_xcbcInit function initializes the context for a xcbc MAC operation.
* This function must be called before any Update
* or Final operations. This method of MACing is used when data is
* present in multiple buffers or not available all at once.
*
* @param[in] ulAlgType The algorithm id for XCBC MAC [N/A]
* @param[in] pucKey Key for XCBC MAC [N/A]
* @param[in] ulKlen Key length [N/A]
* @param[out] pCtx The context which will be filled [N/A]
*
* @retval SEC_UINT32 If context is initialized [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If algorithm
* undefined [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 If memory alloc 
* for context failed [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If arguments 
* are missing [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If the key length is invalid 
* [SEC_ERR_INVALID_KEY_LEN|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_xcbcInit (CRYPT_CTX* pCtx,
                                            const SEC_UINT32 ulAlgType,
                                            const SEC_UCHAR * pucKey,
                                            const SEC_UINT32 ulKlen);

/*
    Func Name:  CRYPT_xcbcUpdate
*/

/** 
* @defgroup CRYPT_xcbcUpdate
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_xcbcUpdate (
*                              CRYPT_CTX ctx,
*                              SEC_UCHAR * pucData,
*                              SEC_UINT32 ulDataLen);
* @endcode
*
* @par Purpose
* This is used to perform xcbc MAC operation on chunks of data.
*
* @par Description
* CRYPT_xcbcUpdate function performs xcbc MAC operation on chunks of 
* data. This method of MACing is used when data is present
* in multiple buffers or not available all at once. A xcbcInit must 
* have been called before calling this function.
*
* @param[in] ctx The context for xcbc mac [N/A]
* @param[in] pucData The input data [N/A]
* @param[in] ulDataLen The input data length [N/A]
*
* @retval SEC_UINT32 If partial MAC is calculated [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If context values are 
* not correct [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If arguments 
* are missing [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 CRYPT_xcbcUpdate (CRYPT_CTX ctx,
                                            SEC_UCHAR * pucData,
                                            SEC_UINT32 ulDataLen);


/*
    Func Name:  CRYPT_xcbcFinal
*/

/** 
* @defgroup CRYPT_xcbcFinal
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_xcbcFinal (
*                           CRYPT_CTX* pCtx,
*                           SEC_UCHAR* pucMAC,
*                           SEC_UINT32* pulMACLen);
* @endcode
*
* @par Purpose
* This is used to complete xcbc MAC operation on remaining data. 
* Called at the end of MAC operation.
*
* @par Description
* CRYPT_xcbcFinal function completes xcbc MAC operation on 
* remaining data. It is called at the end of MAC operation. A xcbcInit
* must have been called before calling this function. 
* This function calculates the MAC and frees the context. The memory
* for MAC must have already been allocated.
*
* @param[in] pCtx The context for xcbc mac [N/A]
* @param[out] pucMAC The XCBC MAC [N/A]
* @param[out] pulMACLen The MAC length [N/A]
*

* @retval SEC_UINT32 If MAC is calculated [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If context values are 
* not correct [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If arguments 
* are missing [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_xcbcFinal (CRYPT_CTX* pCtx,
                                            SEC_UCHAR* pucMAC,
                                            SEC_UINT32* pulMACLen);

/*
    Func Name:  CRYPT_xcbc
*/

/** 
* @defgroup CRYPT_xcbc
* @ingroup HLF High Level Functions 
* @par Prototype
* @code
* SEC_UINT32 CRYPT_xcbc (SEC_UINT32 ulAlgType,
*                        const SEC_UCHAR* pucKey,
*                        SEC_UINT32 upucKeyLen,
*                        SEC_UCHAR * pucData,
*                        SEC_UINT32 ulDataLen, 
*                        SEC_UCHAR * pucMAC,
*                        SEC_UINT32 * pulMACLen);

* @endcode
*
* @par Purpose
* This is used to compute aes xcbc mac of a given data block.
*
* @par Description
* CRYPT_xcbc function computes aes xcbc mac of a given data 
* block. Calls init, update, and final. This function is used when
* data is present all at once. There is no need of calling 
* Init, Update, Final and XCBC MAC can be calculated in one go.
* Context is not needed here. The MAC generated will be of length 128 bits.
*
* @param[in] ulAlgType XCBC MAC algorithm [N/A]
* @param[in] pucKey The key [N/A]
* @param[in] upucKeyLen The key length [N/A]
* @param[in] pucData The data [N/A]
* @param[in] ulDataLen The data length [N/A]
* @param[out] pucMAC The XCBC MAC [N/A]
* @param[out] pulMACLen The MAC length [N/A]
*
* @retval SEC_UINT32 If MAC is calculated [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If context values are 
* not correct [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If arguments 
* are missing [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory alloc for context 
* failed [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If algorithm 
* undefined [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 If the key length 
* is invalid [SEC_ERR_INVALID_KEY_LEN|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* Only AES algorithm is supported.
* This API can be used for AES-XCBC-MAC-96 algorithm. It will
* generate XCBC MAC of 128 bits. Leftmost 96 bits will be taken for 
* XCBC-MAC-96
* 
* @par Related Topics
* N/A
*/


CRYPTOLINKDLL SEC_UINT32 CRYPT_xcbc (SEC_UINT32 ulAlgType,
                                                    const SEC_UCHAR* pucKey,
                                                    SEC_UINT32 upucKeyLen,
                                                    SEC_UCHAR * pucData,
                                                    SEC_UINT32 ulDataLen, 
                                                    SEC_UCHAR * pucMAC,
                                                    SEC_UINT32 * pulMACLen);

/*
    Func Name:  CRYPT_XCBC_size
*/

/**
* @defgroup CRYPT_XCBC_size 
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_XCBC_size(
* SEC_UINT32 ulAlgType);
* @endcode
*
* @par Purpose
* This is used to retrieve the size of the XCBC MAC output for an algorithm.
*
* @par Description
* CRYPT_XCBC_size function retrieves the size of the XCBC MAC output 
* for an algorithm.
*
* @param[in] ulAlgType Algorithm ID for XCBC MAC [N/A]
*
* @retval SEC_UINT32 If valid algorithm [Size of the XCBC MAC|N/A]
* @retval SEC_UINT32 If Undefined algorithm [0|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_XCBC_size(SEC_UINT32 ulAlgType);

#endif





/*
    Func Name:  CRYPT_pubKeyEncrypt
*/

/** 
* @defgroup CRYPT_pubKeyEncrypt
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_pubKeyEncrypt(
* SEC_PKEY_S* pkey,
* SEC_UCHAR*  pucPlainText,
* SEC_UINT32  ulPlainLen,
* SEC_UINT32  ulPadding,
* SEC_UCHAR*  pucCipherText,
* SEC_UINT32* pulCLen);
* @endcode
*
* @par Purpose
* This is used to perform a public key encryption operation.
*
* @par Description
* CRYPT_pubKeyEncrypt function performs a public key 
encryption operation. The key passed to the function must be a
* public key or a key pair. The data size must not e
xceed size of key and for padding modes DEFAULT, PKCS1 and SSLv23,
* data size must be < (key size - 11 bytes), and for OAEP,
data size must be < (key size - 41 bytes).
*
* @param[in] pKey Public key to be used [N/A]
* @param[in] pucPlainText Data buffer [N/A]
* @param[in] ulPlainLen Data buffer length [N/A]
* @param[in] ulPadding Padding mode used [N/A]
* @param[out] pucCipherText Encrypted data buffer [N/A]
* @param[out] pulCLen Encrypted data buffer length [N/A]
*
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid Arguments [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Key size not supported [SEC_ERR_INVALID_KEY_LEN|N/A]
* @retval SEC_UINT32 Invalid Key [SEC_CRYPT_ERR_INVALID_PKEY|N/A]
* @retval SEC_UINT32 Key is neither Pair nor public
[SEC_CRYPT_ERR_INVALID_PKEY_TYPE|N/A]
* @retval SEC_UINT32 Data size larger than key 
[SEC_CRYPT_ERR_LARGE_DATA_SIZE|N/A]
* @retval SEC_UINT32 Undefined padding mode 
[SEC_CRYPT_ERR_UNDEFINED_PADDING|N/A]
* @retval SEC_UINT32 If operation cannot be
performed on key [SEC_CRYPT_ERR_UNDEFINED_KEY_OPERATION|N/A]
* @retval SEC_UINT32 Library not initialized [SEC_ERR_INITLIB|N/A]
* @retval SEC_UINT32 Incorrect Algorithm ID [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 On Failure [SEC_ERR|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* - pucCipherText buffer size should be equal to or greater than the key size in bytes.
*    CRYPT_PKEY_size can be used to get the key size.
* - In case of no padding, if the data size is less than the key size then zero will be prepended to the data 
      to create the data size equal to key size.
* - It is recommended that RSA_SSLV23_PADDING should be used only with SSL protocol.
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_pubKeyEncrypt(
    SEC_PKEY_S*     pkey,
    SEC_UCHAR*      pucPlainText,
    SEC_UINT32      ulPlainLen,
    SEC_UINT32      ulPadding,
    SEC_UCHAR*      pucCipherText,
    SEC_UINT32*     pulCLen);

/*
    Func Name:  CRYPT_privKeyDecrypt
*/

/** 
* @defgroup CRYPT_privKeyDecrypt
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_privKeyDecrypt (
* SEC_PKEY_S* pkey,
* SEC_UCHAR*  pucCipherText,
* SEC_UINT32  ulCipherLen,
* SEC_UINT32  ulPadding,
* SEC_UCHAR*  pucPlainText,
* SEC_UINT32* pulPLen);
* @endcode
*
* @par Purpose
* This is used to perform a private key decryption operation.
*
* @par Description
* CRYPT_privKeyDecrypt function performs a private key 
decryption operation. The key must be a private key or a key pair.
*
* @param[in] pKey Private key to be used [N/A]
* @param[in] pucCipherText Cipher buffer [N/A]
* @param[in] ulCipherLen Cipher buffer length [N/A]
* @param[in] ulPadding Padding mode used [N/A]
* @param[out] pucPlainText Data buffer [N/A]
* @param[out] pulPLen Data buffer length [N/A]
*
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid Arguments [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Key size not supported [SEC_ERR_INVALID_KEY_LEN|N/A]
* @retval SEC_UINT32 Invalid Key [SEC_CRYPT_ERR_INVALID_PKEY|N/A]
* @retval SEC_UINT32 Key is neither Pair nor Private
[SEC_CRYPT_ERR_INVALID_PKEY_TYPE|N/A]
* @retval SEC_UINT32 Data size larger than key 
[SEC_CRYPT_ERR_LARGE_DATA_SIZE|N/A]
* @retval SEC_UINT32 Undefined padding mode 
[SEC_CRYPT_ERR_UNDEFINED_PADDING|N/A]
* @retval SEC_UINT32 If operation cannot be
performed on key [SEC_CRYPT_ERR_UNDEFINED_KEY_OPERATION|N/A]
* @retval SEC_UINT32 Library not initialized [SEC_ERR_INITLIB|N/A]
* @retval SEC_UINT32 Incorrect Algorithm ID [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 On Failure [SEC_ERR|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* - pucPlainText buffer size should be equal to or greater than the key size in bytes.
*    CRYPT_PKEY_size can be used to get the key size.
* - In case of no padding, the zero bytes are prepended during CRYPT_pubKeyEncrypt will not be removed.
* - It is recommended that RSA_SSLV23_PADDING should be used only with SSL protocol.
*
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_privKeyDecrypt (
    SEC_PKEY_S*     pkey,
    SEC_UCHAR*      pucCipherText,
    SEC_UINT32      ulCipherLen,
    SEC_UINT32      ulPadding,
    SEC_UCHAR*      pucPlainText,
    SEC_UINT32*     pulPLen);

/*
    Func Name:  CRYPT_signInit
*/

/** 
* @defgroup CRYPT_signInit
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_signInit(
* CRYPT_CTX*  pCtx,
* SEC_PKEY_S* pKey,
* SEC_UINT32  ulAlgType);
* @endcode
*
* @par Purpose
* This is used to initialize the context for a sign operation.
*
* @par Description
* CRYPT_signInit function initializes the context for a sign
operation. This function must be called before any Update
* or Final operation. This method of signing is used when 
data is present in multiple buffers or not available all at
* once. The key must be a private key or a key pair.
*
* @param[in] ulAlgType The algorithm id for digest [N/A]
* @param[in] pKey The private key for signing [N/A]
* @param[out] pCtx The context which will be filled [N/A]
*
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid Arguments [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Invalid Key [SEC_CRYPT_ERR_INVALID_PKEY|N/A]
* @retval SEC_UINT32 Unsupported Key [SEC_CRYPT_ERR_UNDEFINED_KEY_OPERATION|N/A]
* @retval SEC_UINT32 Memory allocation failure [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 Library not initialized [SEC_ERR_INITLIB|N/A]
* @retval SEC_UINT32 Incorrect Algorithm ID [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 On Failure [SEC_ERR|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* - SM2 Signing is not supported by this API
*
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_signInit (
    CRYPT_CTX*      pCtx,
    SEC_PKEY_S*     pKey,
    SEC_UINT32      ulAlgType);

/*
    Func Name:  CRYPT_signUpdate
*/

/** 
* @defgroup CRYPT_signUpdate
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_signUpdate(
* CRYPT_CTX  ctx,
* SEC_UCHAR* pucData,
* SEC_UINT32 ulDataLen);
* @endcode
*
* @par Purpose
* This is used to perform sign operation on chunks of data.
*
* @par Description
* CRYPT_signUpdate function performs sign operation on chunks 
of data. This method of signing is used when data is
* present in multiple buffers or not available all at once. 
A signInit must have been called before calling this function.
*
* @param[in] ctx The context for signing [N/A]
* @param[in] pucData The input data [N/A]
* @param[in] ulDataLen The input data length [N/A]
*
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid Arguments [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Incorrect context [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 On Failure [SEC_ERR|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* - SM2 Signing is not supported by this API
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_signUpdate(
    CRYPT_CTX       ctx,
    SEC_UCHAR*      pucData,
    SEC_UINT32      ulDataLen);

/*
    Func Name:  CRYPT_signFinal
*/

/** 
* @defgroup CRYPT_signFinal
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_signFinal(
* CRYPT_CTX*  pCtx,
* SEC_UCHAR*  pucSig,
* SEC_UINT32* pulSigLen);
* @endcode
*
* @par Purpose
* This is used to complete sign operation on remaining data, 
performs sign. Called at the end of sign operation.
*
* @par Description
* CRYPT_signFinal function completes sign operation on remaining 
data, performs sign. Called at the end of sign operation.
* A signInit must have been called before calling this function. 
This function calculates the signature and frees the
* context. The memory for the signature must have been already 
allocated.
*
* @param[in] pCtx The context for sign [N/A]
* @param[out] pucSig The signed hash [N/A]
* @param[out] pulSigLen The Sign length [N/A]
*
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid Arguments [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Incorrect context [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 Memory allocation failure [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If operation cannot be performed on key 
[SEC_CRYPT_ERR_UNDEFINED_KEY_OPERATION|N/A]
* @retval SEC_UINT32 Key size not supported [SEC_ERR_INVALID_KEY_LEN|N/A]
* @retval SEC_UINT32 Library not initialized [SEC_ERR_INITLIB|N/A]
* @retval SEC_UINT32 Incorrect Algorithm ID [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 On Failure [SEC_ERR|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* - pucSign buffer size should be equal to or greater than the key size in bytes.
*    CRYPT_PKEY_size can be used to get the key size.
*
* - SM2 Signing is not supported by this API
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_signFinal(
    CRYPT_CTX*      pCtx,
    SEC_UCHAR*      pucSig,
    SEC_UINT32*     pulSigLen);


/*
    Func Name:  CRYPT_sign
*/

/** 
* @defgroup CRYPT_sign
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_sign(
* SEC_UINT32  ulAlg,
* SEC_PKEY_S* pKey,
* SEC_UCHAR*  pucData,
* SEC_UINT32  ulDataLen,
* SEC_UCHAR*  pucSign,
* SEC_UINT32* pulSignLen);
* @endcode
*
* @par Purpose
* This is used to compute sign of a given data block.
*
* @par Description
* CRYPT_sign function computes sign of a given data block. 
* Calls init, update, and final. This function is used when data
* is present all at once. There is no need of calling Init, 
* Update, Final and signature can be calculated in one go.
* Context is not needed here.
*
* @param[in] ulAlg Digest algorithm [N/A]
* @param[in] pKey The private key [N/A]
* @param[in] pucData The data [N/A]
* @param[in] ulDataLen The data length [N/A]
* @param[out] pucSign The signature [N/A]
* @param[out] pulSignLen The sign length [N/A]
*
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid Arguments [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Memory allocation failure [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If operation cannot be performed on key
* [SEC_CRYPT_ERR_UNDEFINED_KEY_OPERATION|N/A]
* @retval SEC_UINT32 Invalid Key [SEC_CRYPT_ERR_INVALID_PKEY|N/A]
* @retval SEC_UINT32 Key size not supported [SEC_ERR_INVALID_KEY_LEN|N/A]
* @retval SEC_UINT32 Library not initialized [SEC_ERR_INITLIB|N/A]
* @retval SEC_UINT32 Incorrect Algorithm ID [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 On Failure [SEC_ERR|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* - pucSign buffer size should be equal to or greater than the key size in bytes.
*    CRYPT_PKEY_size can be used to get the key size.
*
* - If the signing is done using the library version V3R3 or later, using the
*   hash algorithm SHA384 and SHA512, then verification done by
*   the older version (version before V3R3) will fail. The problem in hash
*   info of SHA384 and SHA512 in the older version is fixed in V3R3.
*
* - SM2 Signing is not supported by this API
*
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_sign(
    SEC_UINT32      ulAlg,
    SEC_PKEY_S*     pKey,
    SEC_UCHAR*      pucData,
    SEC_UINT32      ulDataLen,
    SEC_UCHAR*      pucSign,
    SEC_UINT32*     pulSignLen);

/** 
* @defgroup CRYPT_signDec
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_signDec(
* SEC_UCHAR *pucSgn,
* SEC_UINT32 pulSgnLen,
* SEC_UCHAR *pulSgnR,
* SEC_UINT32 *pulSgnRLen,
* SEC_UCHAR *pulSgnS,
* SEC_UINT32 *pulSgnSLen);
* @endcode
*
* @par Purpose
* This is used to Decode the Encoded DSA/ECDSA/SM2DSA Signature 
*                      buffer into r and s values.
* @par Description
* CRYPT_signDec function Decode the Encoded DSA/ECDSA/SM2DSA Signature buffer into 
* corresponding r and s value
*
* @param[in] pucSgn The signature [N/A]
* @param[in] pulSgnLen The sign length [N/A]
* @param[out] pulSgnR The r value [N/A]
* @param[out] pulSgnRLen The length of r value [N/A]
* @param[out] pulSgnS The s value [N/A]
* @param[out] pulSgnSLen The length of s value [N/A]
*
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid Arguments [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 On Failure [SEC_ERR|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_signDec(
    SEC_UCHAR *pucSgn,
    SEC_UINT32 pulSgnLen,
    SEC_UCHAR *pulSgnR,
    SEC_UINT32 *pulSgnRLen,
    SEC_UCHAR *pulSgnS,
    SEC_UINT32 *pulSgnSLen
);

/** 
* @defgroup CRYPT_signEnc
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_signEnc(
* SEC_UCHAR *pucSgn,
* SEC_UINT32 *pulSgnLen,
* SEC_UCHAR *pulSgnR,
* SEC_UINT32 pulSgnRLen,
* SEC_UCHAR *pulSgnS,
* SEC_UINT32 pulSgnSLen);
* @endcode
*
* @par Purpose
* This is used to Encode DSA/ECDSA/SM2DSA r and s signature values.
*
* @par Description
* CRYPT_signEnc function Encodes the DSA/ECDSA/SM2DSA r and s signature values 
* into Signature buffer
*
* @param[out] pucSgn The signature [N/A]
* @param[out] pulSgnLen The sign length [N/A]
* @param[in] pulSgnR The r value [N/A]
* @param[in] pulSgnRLen The length of r value [N/A]
* @param[in] pulSgnS The s value [N/A]
* @param[in] pulSgnSLen The length of s value [N/A]
*
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid Arguments [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 On Memory allocation failure [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 On Failure [SEC_ERR|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_signEnc(
    SEC_UCHAR *pucSgn,
    SEC_UINT32 *pulSgnLen,
    SEC_UCHAR *pulSgnR,
    SEC_UINT32 pulSgnRLen,
    SEC_UCHAR *pulSgnS,
    SEC_UINT32 pulSgnSLen
);

/*
    Func Name:  CRYPT_verifyInit
*/

/** 
* @defgroup CRYPT_verifyInit
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_verifyInit(
* CRYPT_CTX*  pCtx,
* SEC_PKEY_S* pKey,
* SEC_UINT32  ulAlg);
* @endcode
*
* @par Purpose
* This is used to initialize the context for a sign verification operation.
*
* @par Description
* CRYPT_verifyInit function initializes the context for a 
sign verification operation. This function must be called before
* any Update or Final operations. This method of verification
is used when data is present in multiple buffers or not
* available all at once. The key must be a public key or a key pair.
*
* @param[in] ulAlg The algorithm id for digest [N/A]
* @param[in] pKey The public key [N/A]
* @param[out] pCtx The context which will be filled [N/A]
*
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid Arguments [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Invalid Key [SEC_CRYPT_ERR_INVALID_PKEY|N/A]
* @retval SEC_UINT32 Memory allocation failure [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 Library not initialized [SEC_ERR_INITLIB|N/A]
* @retval SEC_UINT32 Incorrect Algorithm ID [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 On Failure [SEC_ERR|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* - SM2 Verification is not supported by this API
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_verifyInit(
    CRYPT_CTX*      pCtx,
    SEC_PKEY_S*     pKey,
    SEC_UINT32      ulAlg);

/*
    Func Name:  CRYPT_verifyUpdate
*/

/** 
* @defgroup CRYPT_verifyUpdate
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_verifyUpdate(
* CRYPT_CTX ctx,
* SEC_UCHAR* pucData,
* SEC_UINT32 ulDtaLen);
* @endcode
*
* @par Purpose
* This is used to perform sign verification operation on chunks of data.
*
* @par Description
* CRYPT_verifyUpdate function performs sign verification
operation on chunks of data. This method of verification is
* used when data is present in multiple buffers or not 
available all at once. A verifyInit should have been called
* before calling this function.
*
* @param[in] ctx The context for verification [N/A]
* @param[in] pucData The input data [N/A]
* @param[in] ulDtaLen The input data length [N/A]
*
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid Arguments [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Incorrect context [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 On Failure [SEC_ERR|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* - SM2 Verification is not supported by this API
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_verifyUpdate(
    CRYPT_CTX       ctx,
    SEC_UCHAR*      pucData,
    SEC_UINT32      ulDtaLen);


/*
    Func Name:  CRYPT_verifyFinal
*/

/** 
* @defgroup CRYPT_verifyFinal
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_verifyFinal(
* CRYPT_CTX* pCtx,
* SEC_UCHAR* pucSig,
* SEC_UINT32 pulSigLen);
* @endcode
*
* @par Purpose
* This is used to complete sign verification operation on 
data and is called at the end of verify operation.
*
* @par Description
* CRYPT_verifyFinal function completes sign verification 
operation on data and is called at the end of verify operation.
* A verifyInit must have been called before calling this 
function. This function checks the signature and frees the
* context.
*
* @param[in] pCtx The context for verification [N/A]
* @param[in] pucSig The signed hash [N/A]
* @param[in] pulSigLen The Sign length [N/A]
*
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid Arguments [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Incorrect context [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 Memory allocation failure [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If operation cannot be performed on key 
[SEC_CRYPT_ERR_UNDEFINED_KEY_OPERATION|N/A]
* @retval SEC_UINT32 Key size not supported [SEC_ERR_INVALID_KEY_LEN|N/A]
* @retval SEC_UINT32 Library not initialized [SEC_ERR_INITLIB|N/A]
* @retval SEC_UINT32 Incorrect Algorithm ID [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 On Failure [SEC_ERR|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* - SM2 Verification is not supported by this API
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_verifyFinal(
    CRYPT_CTX*      pCtx,
    SEC_UCHAR*      pucSig,
    SEC_UINT32      pulSigLen);

/*
    Func Name:  CRYPT_verify
*/

/** 
* @defgroup CRYPT_verify
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_verify(
* SEC_UINT32 ulAlg,
* SEC_PKEY_S* pKey,
* SEC_UCHAR* pucDta,
* SEC_UINT32 ulDtaLen,
* SEC_UCHAR* pucSig,
* SEC_UINT32 ulSigLen);
* @endcode
*
* @par Purpose
* This is used to compare sign on a given data block. Calls 
init, update, final.
*
* @par Description
* CRYPT_verify function compares sign on a given data block. 
Calls init, update, final. This function is used when data
* is present all at once. There is no need of calling Init, 
Update, Final and verification can be done in one go.
* Context is not needed here.
*
* @param[in] ulAlg Digest algorithm [N/A]
* @param[in] pKey The public key [N/A]
* @param[in] pucDta The data [N/A]
* @param[in] ulDtaLen The data length [N/A]
* @param[in] pucSig The signature [N/A]
* @param[in] ulSigLen The sign length [N/A]
*
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid Arguments [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Invalid Key [SEC_CRYPT_ERR_INVALID_PKEY|N/A]
* @retval SEC_UINT32 Memory allocation failure [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If operation cannot be performed on key 
[SEC_CRYPT_ERR_UNDEFINED_KEY_OPERATION|N/A]
* @retval SEC_UINT32 Key size not supported [SEC_ERR_INVALID_KEY_LEN|N/A]
* @retval SEC_UINT32 Library not initialized [SEC_ERR_INITLIB|N/A]
* @retval SEC_UINT32 Incorrect Algorithm ID [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 On Failure [SEC_ERR|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* 
* - If the signing is done using the library version V3R3 or later, using the
* hash algorithm SHA384 and SHA512, then verification done by
* the older version (version before V3R3) will fail. Their is problem in hash
* info of SHA384 and SHA512 in the older version is fixed in V3R3.
*
* - SM2 Sign Verification is not supported by this API
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 CRYPT_verify(
    SEC_UINT32      ulAlg,
    SEC_PKEY_S*     pKey,
    SEC_UCHAR*      pucDta,
    SEC_UINT32      ulDtaLen,
    SEC_UCHAR*      pucSig,
    SEC_UINT32      ulSigLen);

/*
    Func Name:  CRYPT_sealInit
*/

/** 
* @defgroup CRYPT_sealInit
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_sealInit(
* CRYPT_CTX* pCtx,
* SEC_UINT32 ulAlgId,
* SEC_UINT32 uiKeyArrLen,
* SEC_PKEY_S* aPubKey[],
* SEC_UCHAR* pucIV,
* SEC_UINT32 ulIVLen,
* SEC_CHAR* aCEKey[],
* SEC_UINT32 aCEKeyLen[]);
* @endcode
*
* @par Purpose
* This is used to encrypt symmetric key with asymmetric key.
*
* @par Description
* CRYPT_sealInit function generates a random key for the 
symmetric algorithm. Then it encrypts the symmetric key with
* each of the asymmetric keys passed in the aPubKey array. 
The encrypted symmetric key is put in the array aCEKey and
* the length of the encrypted key is put in aCEKeyLen array.
It then initializes the symmetric context structure as in
* CRYPT_encryptinit.
*
* @param[in] ulAlgId The algorithm Id [N/A]
* @param[in] uiKeyArrLen Length of the 3 arrays [N/A]
* @param[in] aPubKey[] Array of public keys of asymmetric algorithms [N/A]
* @param[in] pucIV InitializationVector(CBC,CFB*,OFB algorithm modes) [N/A]
* @param[in] ulIVLen Length of IV. pass 0 if no IV [N/A]
* @param[out] pCtx Address of The context to be initialized [N/A]
* @param[out] aCEKey[] Array of encrypted the symmetric key. 
This has to be freed by the user using ipsi_free() [N/A]
* @param[out] aCEKeyLen[] Array of length of encrypted key [N/A] 
*
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid Arguments [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Memory allocation failure [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 Incorrect Algorithm ID [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 Invalid Padding Mode. Padding mode set 
on Algorithm is not defined
* [SEC_CRYPT_ERR_UNDEFINED_PADDING|N/A]
* @retval SEC_UINT32 Invalid IV length [SEC_ERR_INVALID_IV_LEN|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* As memory allocation for aCEKey is done inside the library 
user is responsible for freeing the memory using ipsi_free().
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_sealInit(
    CRYPT_CTX*      pCtx,
    SEC_UINT32      ulAlgId,
    SEC_UINT32      uiKeyArrLen,
    SEC_PKEY_S*     aPubKey[],
    SEC_UCHAR*      pucIV,
    SEC_UINT32      ulIVLen,
    SEC_CHAR*       aCEKey[],
    SEC_UINT32      aCEKeyLen[]);

/*
    Func Name:  CRYPT_sealUpdate
*/

/** 
* @defgroup CRYPT_sealUpdate
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_sealUpdate(
* CRYPT_CTX ctx,
* SEC_UCHAR * pucPlainText,
* SEC_UINT32 ulPlainLen,
* SEC_UCHAR * pucCipherText,
* SEC_UINT32 * pulCLen);
* @endcode
*
* @par Purpose
* This uses the initialized context to encrypt plaintext to 
get ciphertext using symmetric encryption.
*
* @par Description
* CRYPT_sealUpdate function uses the initialized context to 
encrypt plaintext to get ciphertext using symmetric encryption.
* Please refer to CRYPT_encryptUpadte function.
*
* @param[in] ctx The context to be used [N/A]
* @param[in] pucPlainText Plaintext to be encrypted [N/A]
* @param[in] ulPlainLen Length of plaintext [N/A]
* @param[out] pucCipherText Encrypted ciphertext [N/A]
* @param[out] pulCLen Length of encrypted ciphertext [N/A]
*
* @retval SEC_UINT32 Invalid context [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 On successful return [SEC_SUCCESS|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_sealUpdate(
    CRYPT_CTX ctx,
    SEC_UCHAR * pucPlainText,
    SEC_UINT32 ulPlainLen,
    SEC_UCHAR * pucCipherText,
    SEC_UINT32 * pulCLen);

/*
    Func Name:  CRYPT_sealFinal
*/

/** 
* @defgroup CRYPT_sealFinal
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_sealFinal(
* CRYPT_CTX* pCtx,
* SEC_UCHAR* pucCphrTxt,
* SEC_UINT32* pulCphrTxtLen);
* @endcode
*
* @par Purpose
* This is used to complete the seal operation.
*
* @par Description
* CRYPT_sealFinal function completes the seal operation. 
It frees the symmetric context. In case of block ciphers, the
* output of this function is the last block. If sealinit 
succeeds, sealfinal must be called to free the context.
*
* @param[in] pCtx Address of Context to be used [N/A]
* @param[out] pucCphrTxt Final encrypted ciphertext [N/A]
* @param[out] pulCphrTxtLen Length of the last encrypted ciphertext [N/A]
*
* @retval SEC_UINT32 Invalid context [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 Invalid pad mode in context 
[SEC_CRYPT_ERR_UNDEFINED_PADDING|N/A]
* @retval SEC_UINT32 Invalid plaintext length given 
for encryption in update and padding_mode = BLOCK_PADDING_NONE.
* (plaintext length was not integral no. of blocks) 
[SEC_ERR_INVALID_DATA_LEN|N/A]
* @retval SEC_UINT32 On successful return [SEC_UINT32 SEC_SUCCESS|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_sealFinal(
    CRYPT_CTX* pCtx,
    SEC_UCHAR * pucCphrTxt,
    SEC_UINT32 * pulCphrTxtLen);

/*
    Func Name:  CRYPT_seal
*/

/** 
* @defgroup CRYPT_seal
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_seal(
* SEC_UINT32 ulAlgId,
* SEC_UINT32 uiKeyArrLen,
* SEC_PKEY_S* aPubKey[],
* SEC_UCHAR* pucIV,
* SEC_UINT32 ulIVLen,
* SEC_UCHAR* pucPlainText,
* SEC_UINT32 ulPlainLen,
* SEC_UCHAR* pucCipherText,
* SEC_UINT32* pulCLen,
* SEC_CHAR*  aCEKey[],
* SEC_UINT32 aCEKeyLen[]);
* @endcode
*
* @par Purpose
* This is used to generate a random key for symmetric algorithm.
*
* @par Description
* CRYPT_seal function generates a random key for symmetric algorithm.
Then, it encrypts the symmetric key with each of
* the asymmetric keys passed in the aPubKey array. 
The encrypted symmetric key is added to the aCEKey array and the length
* of the encrypted key is added to the aCEKeyLen array. 
It then encrypts the plaintext using the generated of the
* symmetric key to obtain the ciphertext using symmetric encryption.
*
* @param[in] ulAlgId Algorithm ID [N/A]
* @param[in] uiKeyArrLen Length of the three arrays (aPubKey,
aCEKey, and aCEKeyLen) [N/A]
* @param[in] aPubKey[] Array of public keys of asymmetric algorithms [N/A]
* @param[in] pucIV Initialization Vector(CBC,CFB,OFB modes) [N/A]
* @param[in] ulIVLen Length of IV (0 if IV is not present) [N/A]
* @param[in] pucPlainText Plaintext to be encrypted [N/A]
* @param[in] ulPlainLen Length of plaintext [N/A]
* @param[out] pucCipherText Encrypted ciphertext [N/A]
* @param[out] pulCLen Length of encrypted ciphertext [N/A]
* @param[out] aCEKey[] Array of encrypted symmetric key.
This has to be freed by the user using ipsi_free() [N/A]
* @param[out] aCEKeyLen[] Array of encrypted key length [N/A]
*
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid Arguments [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Memory allocation failure [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 Incorrect Algorithm ID [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 Invalid Padding Mode. Padding mode set on
Algorithm is not defined
* [SEC_CRYPT_ERR_UNDEFINED_PADDING|N/A]
* @retval SEC_UINT32 Invalid IV length [SEC_ERR_INVALID_IV_LEN|N/A]
* @retval SEC_UINT32 Invalid plaintext length given for 
encryption and padding_mode = BLOCK_PADDING_NONE.
* (plaintext length was not integral no. of blocks) 
[SEC_ERR_INVALID_DATA_LEN|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* As memory allocation for aCEKey is done inside the 
library, user is responsible for freeing the memory using ipsi_free().
*       
* @par Related Topics
* N/A
*/


CRYPTOLINKDLL SEC_UINT32 CRYPT_seal(
    SEC_UINT32      ulAlgId,
    SEC_UINT32      uiKeyArrLen,
    SEC_PKEY_S*     aPubKey[],
    SEC_UCHAR*      pucIV,
    SEC_UINT32      ulIVLen,
    SEC_UCHAR*      pucPlainText,
    SEC_UINT32      ulPlainLen,
    SEC_UCHAR*      pucCipherText,
    SEC_UINT32*     pulCLen,
    SEC_CHAR*       aCEKey[],
    SEC_UINT32      aCEKeyLen[]);

/*
    Func Name:  CRYPT_openInit
*/

/** 
* @defgroup CRYPT_openInit
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_openInit(
* CRYPT_CTX* pCtx,
* SEC_UINT32 ulAlgId,
* SEC_PKEY_S* pstPvtKey,
* SEC_UCHAR* pucCEKey,
* SEC_UINT32 ulCEKeyLen,
* SEC_UCHAR* pucIV,
* SEC_UINT32 ulIVLen);
* @endcode
*
* @par Purpose
* This is used to decrypt the encrypted symmetric key.
*
* @par Description
* CRYPT_openInit function decrypts the encrypted symmetric key. 
The decrypted symmetric key is used to initialize the
* context for further decryption. It initializes  the symmetric 
context structure as in decryptinit for symmetric
* decryption.
*
* @param[in] ulAlgId Algorithm ID [N/A]
* @param[in] pstPvtKey Private key of asymmetric algorithm [N/A]
* @param[in] pucCEKey Encrypted symmetric key [N/A]
* @param[in] ulCEKeyLen Length of encrypted symmetric key [N/A]
* @param[in] pucIV InitializationVector(CBC,CFB,OFB modes) [N/A]
* @param[in] ulIVLen Length of IV (0 if IV is not present) [N/A]
* @param[out] pCtx Address of Context to be initialized [N/A]
*
* @retval SEC_UINT32 Memory allocation failure [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 Invalid Algorithm Id [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 Invalid Padding Mode. Padding mode set on 
Algorithm is not defined
* [SEC_CRYPT_ERR_UNDEFINED_PADDING|N/A]
* @retval SEC_UINT32 Invalid Keylength for algorithm 
[SEC_ERR_INVALID_KEY_LEN|N/A] 
* @retval SEC_UINT32 Invalid Argument [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Invalid IV length [SEC_ERR_INVALID_IV_LEN|N/A]
* @retval SEC_UINT32 On successful return [SEC_SUCCESS|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_openInit(
    CRYPT_CTX* pCtx,
    SEC_UINT32 ulAlgId,
    SEC_PKEY_S * pstPvtKey,
    SEC_UCHAR * pucCEKey,
    SEC_UINT32 ulCEKeyLen,
    SEC_UCHAR * pucIV,
    SEC_UINT32 ulIVLen);

/*
    Func Name:  CRYPT_openUpdate
*/

/** 
* @defgroup CRYPT_openUpdate
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_openUpdate(
* CRYPT_CTX ctx,
* SEC_UCHAR* pucCipherText,
* SEC_UINT32 pulCLen,
* SEC_UCHAR* pucPlainText,
* SEC_UINT32* pulPLen);
* @endcode
*
* @par Purpose
* This uses the initialized context to decrypt ciphertext
into plaintext for symmetric decryption.
*
* @par Description
* CRYPT_openUpdate function uses the initialized context to 
decrypt ciphertext into plaintext for symmetric decryption.
* Please refer to CRYPT_decryptUpdate function.
*
* @param[in] ctx Context to be used [N/A]
* @param[in] pucCipherText Encrypted ciphertext [N/A]
* @param[in] pulCLen length of Encrypted ciphertext [N/A]
* @param[out] pucPlainText Decrypted plaintext [N/A]
* @param[out] pulPLen Length of decrypted plaintext [N/A]
*
* @retval SEC_UINT32 Invalid context [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 Invalid Argument [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Invalid IV length [SEC_ERR_INVALID_IV_LEN|N/A]
* @retval SEC_UINT32 On successful return [SEC_SUCCESS|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/


CRYPTOLINKDLL SEC_UINT32 CRYPT_openUpdate(
    CRYPT_CTX ctx,
    SEC_UCHAR * pucCipherText,
    SEC_UINT32 pulCLen,
    SEC_UCHAR * pucPlainText,
    SEC_UINT32 * pulPLen);

/*
    Func Name:  CRYPT_openFinal
*/

/** 
* @defgroup CRYPT_openFinal
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_openFinal(
* CRYPT_CTX* pCtx,
* SEC_UCHAR* pucPlainText,
* SEC_UINT32* pulPLen);
* @endcode
*
* @par Purpose
* This is used to complete open operation.

* @par Description
* CRYPT_openFinal function completes one open operation. 
It frees the symmetric context. In case of block ciphers, the
* output of this function is the last block. If openinit succeeds, 
openfinal must be called to free the context.
*               
* @param[in] pCtx Address of Context to be used [N/A]
* @param[out] pucPlainText Final decrypted plaintext [N/A]
* @param[out] pulPLen Length of final decrypted plaintext [N/A]
*
* @retval SEC_UINT32 Invalid context [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 Invalid pad mode in context 
[SEC_CRYPT_ERR_UNDEFINED_PADDING|N/A]
* @retval SEC_UINT32 When pad bits are incorrect that is after decrypting,
if the padding bits dont match the pad mode.
* It can be due to incorrect Key or IV as that will produce junk 
plaintext with random padding bits, which do not
* match the padding mode [SEC_CRYPT_ERR_INVALID_PADDING|N/A]
* @retval SEC_UINT32 Invalid ciphertext length given for decryption
in update.  
* (ciphertext length was not integral no. of blocks)
[SEC_ERR_INVALID_DATA_LEN|N/A]
* @retval SEC_UINT32 On successful return [SEC_SUCCESS|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_openFinal(
    CRYPT_CTX* pCtx,
    SEC_UCHAR * pucPlainText,
    SEC_UINT32 * pulPLen);

/*
    Func Name:  CRYPT_open
*/

/** 
* @defgroup CRYPT_open
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_open(
* SEC_UINT32 ulAlgId,
* SEC_PKEY_S* pstPvtKey,
* SEC_UCHAR* pucCEKey,
* SEC_UINT32 ulCEKeyLen,
* SEC_UCHAR* pucIV,
* SEC_UINT32 ulIVLen,
* SEC_UCHAR* pucCipherText,
* SEC_UINT32 pulCLen,
* SEC_UCHAR* pucPlainText,
* SEC_UINT32* pulPLen);
* @endcode
*
* @par Purpose
* This is used to decrypt the encrypted symmetric key.
It then uses the decrypted symmetric key to decrypt the ciphertext
* into plaintext using symmetric decryption.
*
* @par Description
* CRYPT_open function decrypts the encrypted symmetric key.
It then uses the decrypted symmetric key to decrypt the
* ciphertext into plaintext using symmetric decryption.
*
* @param[in] ulAlgId Algorithm ID [N/A]
* @param[in] pstPvtKey Private key of asymmetric algorithm [N/A]
* @param[in] pucCEKey Encrypted symmetric key [N/A]
* @param[in] ulCEKeyLen Length of encrypted symmetric key [N/A]
* @param[in] pucIV InitializationVector(CBC,CFB,OFB modes) [N/A]
* @param[in] ulIVLen Length of IV. pass 0 if no IV [N/A]
* @param[in] pucCipherText Ciphertext to be decrypted [N/A]
* @param[in] pulCLen Length of  ciphertext [N/A]
* @param[out] pucPlainText Decrypted Plaintext [N/A]]
* @param[out] pulPLen Length of plaintext [N/A]
*
* @retval SEC_UINT32 If Memory allocation fails [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If invalid Algorithm Id [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 Invalid Padding Mode. Padding mode set on
Algorithm is not defined
* [SEC_CRYPT_ERR_UNDEFINED_PADDING|N/A]
* @retval SEC_UINT32 The pad bits are incorrect. When after 
decrypting the padding bits dont match the pad mode. It can
* be due to incorrect Key or IV as that will produce junk 
plaintext with random padding bits, which do not match the
* padding mode [SEC_CRYPT_ERR_INVALID_PADDING|N/A]
* @retval SEC_UINT32 Invalid ciphertext length given for 
decryption (ciphertext length was not integral number of blocks)
* [SEC_ERR_INVALID_DATA_LEN|N/A]
* @retval SEC_UINT32 Invalid Keylength for algorithm 
[SEC_ERR_INVALID_KEY_LEN|N/A]
* @retval SEC_UINT32 Invalid Argument [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Invalid IV length [SEC_ERR_INVALID_IV_LEN|N/A]
* @retval SEC_UINT32 On successful return [SEC_SUCCESS|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_open(
    SEC_UINT32 ulAlgId,
    SEC_PKEY_S * pstPvtKey,
    SEC_UCHAR *pucCEKey,
    SEC_UINT32 ulCEKeyLen,
    SEC_UCHAR * pucIV,
    SEC_UINT32 ulIVLen,
    SEC_UCHAR * pucCipherText,
    SEC_UINT32 pulCLen,
    SEC_UCHAR * pucPlainText,
    SEC_UINT32 * pulPLen);


/*
    Func Name:  CRYPT_random
*/

/** 
* @defgroup CRYPT_random
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_random(
* SEC_UCHAR* pBuf,
* SEC_UINT32 ulLen);
* @endcode
*
* @par Purpose
* This is used to generate a random number.
*
* @par Description
* CRYPT_random function generates a random number and stores it 
into the supplied buffer.
*
* @param[in] ulLen Size of the buffer in bytes [N/A]
* @param[out] pBuf Buffer to hold the random number [N/A]
*
* @retval SEC_UINT32 On successful return [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If pBuf is NULL or ulLen is 0 [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_random(
    SEC_UCHAR*      pBuf,
    SEC_UINT32      ulLen);

/*
    Func Name:  CRYPT_randRange
*/

/** 
* @defgroup CRYPT_randRange
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT CRYPT_randRange (
* SEC_BIGINT_S* limit0,
* SEC_BIGINT_S* limit1,
* SEC_BIGINT_S* num);
* @endcode
*
* @par Purpose
* This is used to generate a random number and stores it 
into the supplied Big Integer structure.
*
* @par Description
* CRYPT_randRange function generates a random number and 
stores it into the supplied Big Integer structure. The random
* number will lie between the two limits supplied, where 
limit1 != limit0.
*
* @param[in] limit0 One of the limits between which the 
random number should lie [N/A]
* @param[in] limit1 One of the limits between which the 
random number should lie [N/A]
* @param[out] num The generated random number [N/A]
*
* @retval SEC_UINT On successful generation [SEC_SUCCESS|N/A]
* @retval SEC_UINT If input pointers are NULL or one of the 
limits have length 0 or if limit1 == limit0
* [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT CRYPT_randRange (
    SEC_BIGINT_S* limit0,
    SEC_BIGINT_S* limit1,
    SEC_BIGINT_S* num);

/*
    Func Name:  SEC_Rand
*/

/** 
* @defgroup SEC_Rand
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 SEC_Rand(SEC_UINT32 ulRange);
* @endcode
*
* @par Purpose
* This is used to generate a random integer in a given range.
*
* @par Description
* SEC_Rand function generates a random integer in a given range.
The random integer generated is in between 0 and user
* input value.
*
* @param[in] ulRange Upper range [N/A]
*
* @retval SEC_UINT32 Generates random integer in a given range 
[Random integer|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 SEC_Rand(SEC_UINT32 ulRange);

/*
    Func Name:  CRYPT_getRandState
*/

/** 
* @defgroup CRYPT_getRandState
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* PRNG_STATE_S *CRYPT_getRandState ();
* @endcode
*
* @par Purpose
* This is used to retrieve the internal state of the random number generator.
*
* @par Description
* CRYPT_getRandState function retrieves the internal state of the 
random number generator so that it may be stored in
* a file.
*
* @par Parameters
* N/A
*
* @retval PRNG_STATE_S* On Success [The internal state of the 
random number generator|N/A]
* @retval PRNG_STATE_S* If the hardware mode is set [SEC_NULL|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL PRNG_STATE_S *CRYPT_getRandState ();

/*
    Func Name:  CRYPT_setRandState
*/

/** 
* @defgroup CRYPT_setRandState
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT CRYPT_setRandState (
* PRNG_STATE_S* pState);
* @endcode
*
* @par Purpose
* This is used to set the internal state of the random number generator.
*
* @par Description
* CRYPT_setRandState function sets the internal state of the
random number generator so that a saved state may be restored.
*
* @param[in] pState The state which is to be restored [N/A]
*
* @retval SEC_UINT After successful set [SEC_SUCCESS|N/A]
* @retval SEC_UINT If argument is NULL [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT If the hardware mode is set 
[SEC_HW_ERR_INVALID_OPERATION|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT CRYPT_setRandState (
    PRNG_STATE_S* pState);

/*
    Func Name:  CRYPT_genKeyPair
*/

/** 
* @defgroup CRYPT_genKeyPair
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_genKeyPair(
* ALG_PARA_S* algInfo,
* SEC_PKEY_S* pKeyPair);
* @endcode
*
* @par Purpose
* This is used to generate a key pair for a given asymmetric algorithm.
*
* @par Description
* CRYPT_genKeyPair function generates a key pair for a given
asymmetric algorithm. The structure must be added with
* parameters appropriate for the algorithm to be used. 
The key structure must be allocated earlier using CRYPT_PKEY_new
* function.
*
* @param[in] algInfo Algorithm information structure [N/A]
* @param[out] pKeyPair The generated key pair structure [N/A]
*
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid Arguments [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation failure [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If key size not supported [SEC_ERR_INVALID_KEY_LEN|N/A]
* @retval SEC_UINT32 If library is not initialized [SEC_ERR_INITLIB|N/A]
* @retval SEC_UINT32 Incorrect Algorithm ID [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 On Failure [SEC_ERR_KEY_GEN_FAILED|N/A]
* @retval SEC_UINT32 On other errors [SEC_ERR|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* 1. RSA key pair generation involves finding large prime factors.
*    So this would be slower and as the modulus size increases it will take
*    more time. And the CPU might be hogged during RSA key pair generation.
*    In product scenario where the RSA keys are not generated offline
*    then it advised to use CRYPT_genKeyPair_ex.
* \n\n
* 2. CRYPT_genKeyPair_ex extends CRYPT_genKeyPair functionality.
*    This additionally invokes the callback function set, periodically after the
*    configured time. In the call back function product can clear the watch dog
*    so that the timer starts from the beginning and will avoid reboot of system.
*    Or in the call back function product can relinquish the CPU by having
*    appropriate task_delay.
* \n
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_genKeyPair(
    ALG_PARA_S*     algInfo,
    SEC_PKEY_S*     pKeyPair);


#ifndef IPSI_RSA_NOEXTENDEDKEYPAIR__

/**
* @defgroup IPSI_GEN_KPAIR_CTX_S
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef SEC_VOID IPSI_GEN_KPAIR_CTX_S;
* @endcode
*
* @par Description
* This is the keypair context which is to be passed as first parameter to
* IPSI_GEN_KEYPAIR_TIME_CB callback. Currently NULL is passed
* , This Reserved for future use.
*/
typedef SEC_VOID IPSI_GEN_KPAIR_CTX_S;

/*
    Func Name:  IPSI_GEN_KEYPAIR_TIME_CB
*/

/** 
* @defgroup IPSI_GEN_KEYPAIR_TIME_CB
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* typedef SEC_INT32 (*IPSI_GEN_KEYPAIR_TIME_CB)(
*    IPSI_GEN_KPAIR_CTX_S *, SEC_VOID *);
*
* @endcode
*
* @par Purpose
* Callback function called from CRYPT_genKeyPair_ex and CRYPT_genKeyPair_ex2.
*
* @par Description
* This function is called from CRYPT_genKeyPair_ex and CRYPT_genKeyPair_ex2 function after 
* the configured number of seconds or CPU ticks (according to the  API) elapses.
* When the callback function is called the Application data that is set is
* passed back as second parameter to the callback. 
* The first parameter to callback function is 
* reserved for future use. Currently the return value from the callback function
* is ignored and intended only for future use.
* 
*
* @retval SEC_INT32 Currently Nothing to be returned [N/A|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* 
* @par Related Topics
* N/A
*/
typedef SEC_INT32 (*IPSI_GEN_KEYPAIR_TIME_CB)(
    IPSI_GEN_KPAIR_CTX_S *, SEC_VOID *);

/*
    Func Name:  CRYPT_genKeyPair_ex
*/

/** 
* @defgroup CRYPT_genKeyPair_ex
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_genKeyPair_ex (
*     ALG_PARA_S *pAlgInfo, SEC_PKEY_S *pKeyPair, 
*     IPSI_GEN_KEYPAIR_TIME_CB pfGenKeyPairCb,
*     SEC_UINT32 uTimeSec, SEC_VOID * pvAppData);
*
* @endcode
*
* @par Purpose
* This extends CRYPT_genKeyPair functionality. This additionally invokes 
* the callback function set, periodically after the configured time.
*
* @par Description
* CRYPT_genKeyPair_ex function generates a key pair for a given
* asymmetric algorithm. The structure must be added with
* parameters appropriate for the algorithm to be used. 
* The key structure must be allocated earlier using CRYPT_PKEY_new
* function. This function also calls the set callback function after 
* the configured number of seconds elapses.
* When the callback function is called the Application data that is set is
* passed back as Second parameter to the callback. 
* The First Parameter to callback function is 
* reserved for future use. Currently the return value from the callback function
* is ignored and intended only for future use.
* 
*
* @param[in] pAlgInfo Algorithm information structure [N/A]
* @param[out] pKeyPair The generated key pair struct [N/A]
* @param[in] pfGenKeyPairCb Callback function 
* which wil be called after timeSec seconds[N/A]
* @param[in] pvAppData Application data passed back 
* to the callback function [N/A]
* @param[in] utimeSec Time after which the callback function will be 
* called in seconds.
*
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid Arguments [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation failure [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If key size not supported [SEC_ERR_INVALID_KEY_LEN|N/A]
* @retval SEC_UINT32 If library is not initialized [SEC_ERR_INITLIB|N/A]
* @retval SEC_UINT32 Incorrect Algorithm ID [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 On Failure [SEC_ERR_KEY_GEN_FAILED|N/A]
* @retval SEC_UINT32 On other errors [SEC_ERR|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* 1. It is recommended that the uTimeSec should be set to 1 or more second
*    lesser than the time required by the application.
* \n\n
* 2. Currently this api can be used only for RSA key pair.
* \n\n
* 3. RSA key pair generation involves finding large prime factors.
*    So this would be slower and as the modulus size increases it will take more time.
*    And the CPU might be hogged during RSA key pair generation. In product scenario
*    where the RSA keys are not generated offline then it advised
*    to use CRYPT_genKeyPair_ex.
* \n\n
* 4. CRYPT_genKeyPair_ex extends CRYPT_genKeyPair functionality.
*    This additionally invokes the callback function set, periodically after
*    the configured time. In the call back function product can clear the watch
*    dog so that the timer starts from the beginning and will avoid reboot
*    of system. Or in the call back function product can relinquish the CPU
*    by having appropriate task_delay.
* \n
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 CRYPT_genKeyPair_ex (
    ALG_PARA_S *pAlgInfo, SEC_PKEY_S *pKeyPair, 
    IPSI_GEN_KEYPAIR_TIME_CB pfGenKeyPairCb,
    SEC_UINT32 uTimeSec, SEC_VOID * pvAppData);

/*
    Func Name:  CRYPT_genKeyPair_ex2
*/

/** 
* @defgroup CRYPT_genKeyPair_ex2
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_genKeyPair_ex2 (
*     ALG_PARA_S *pAlgInfo, SEC_PKEY_S *pKeyPair, 
*     IPSI_GEN_KEYPAIR_TIME_CB pfGenKeyPairCb,
*     SEC_UINT32 uTimeTick, SEC_VOID * pvAppData);
*
* @endcode
*
* @par Purpose
* This extends CRYPT_genKeyPair functionality. This additionally invokes 
* the callback function set, periodically after the configured time in cpu tick.
*
* @par Description
* CRYPT_genKeyPair_ex2 function generates a key pair for a given
* asymmetric algorithm. The structure must be added with
* parameters appropriate for the algorithm to be used. 
* The key structure must be allocated earlier using CRYPT_PKEY_new
* function. This function also calls the set callback function after 
* the configured number of cpu ticks.
* When the callback function is called the Application data that is set is
* passed back as second parameter to the callback. 
* The First Parameter to callback function is 
* reserved for future use. Currently the return value from the callback function
* is ignored and intended only for future use.
* 
*
* @param[in] pAlgInfo Algorithm information structure [N/A]
* @param[out] pKeyPair The generated key pair struct [N/A]
* @param[in] pfGenKeyPairCb Callback function 
* which wil be called after uTimeTick CPU ticks[N/A]
* @param[in] pvAppData Application data passed back 
* to the callback function [N/A]
* @param[in] uTimeTick CPU tick Time after which the callback function will be 
* called in cputicks.
*
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid Arguments [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation failure [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If key size not supported [SEC_ERR_INVALID_KEY_LEN|N/A]
* @retval SEC_UINT32 If library is not initialized [SEC_ERR_INITLIB|N/A]
* @retval SEC_UINT32 Incorrect Algorithm ID [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 On Failure [SEC_ERR_KEY_GEN_FAILED|N/A]
* @retval SEC_UINT32 On other errors [SEC_ERR|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* 1. It is recommended that the application passes a slightly reduced time input than what is needed
* (For Ex: If the total wait time needed is 5 seconds, application may pass 4 seconds, 
* in the case of this API, equivalent ticks should be passed).
* \n\n
* 2. Currently this api can be used only for RSA key pair.
* \n\n
* 3. RSA key pair generation involves finding large prime factors.
*    So this would be slower and as the modulus size increases it will take more time.
*    And the CPU might be hogged during RSA key pair generation. In product scenario
*    where the RSA keys are not generated offline then it advised
*    to use CRYPT_genKeyPair_ex2 or CRYPT_genKeyPair_ex.
* \n\n
* 4. CRYPT_genKeyPair_ex2 extends CRYPT_genKeyPair functionality.
*    This additionally invokes the callback function set, periodically after
*    the configured time. In the call back function product can clear the watch
*    dog so that the timer starts from the beginning and will avoid reboot
*    of system. Or in the call back function product can relinquish the CPU
*    by having appropriate task_delay.
* \n
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_genKeyPair_ex2 (
    ALG_PARA_S *pAlgInfo, SEC_PKEY_S *pKeyPair, 
    IPSI_GEN_KEYPAIR_TIME_CB pfGenKeyPairCb,
    SEC_UINT32 uTimeTick, SEC_VOID * pvAppData);


#endif

/*
    Func Name:  CRYPT_genKey
*/

/** 
* @defgroup CRYPT_genKey
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_genKey(
* SEC_UINT32 ulAlg,
* SEC_UCHAR* pucKey);
* @endcode
*
* @par Purpose
* This is used to generate a random key for the given symmetric algorithm.
*
* @par Description
* CRYPT_genKey function generates a random key for the 
given symmetric algorithm. The memory for the key must be allocated
* before calling this function. For RC4 algorithm, the
* keylength will be RC4_DEFAULT_KEYLEN. For RC2 algorithm, the keylength 
* will be RC2_DEFAULT_KEYLEN. For other symmetric
* algorithms,it will be their respective keylength.
*
*
* @param[in] ulAlg Symmetric algorithm [N/A]
* @param[out] pucKey Generated random key [N/A]
*
* @retval SEC_UINT32 Invalid Symmetric Algorithm Id [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 On successful return [SEC_SUCCESS|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_genKey(
    SEC_UINT32 ulAlg,
    SEC_UCHAR * pucKey);

/*
    Func Name:  CRYPT_randSeed
*/

/** 
* @defgroup CRYPT_randSeed
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_randSeed(
* SEC_UCHAR * pSeed,
* SEC_UINT32 ulLen);
* @endcode
*
* @par Purpose
* This is used to set the given seed to the random number generator.
*
* @par Description
* CRYPT_randSeed function sets the given seed to the
random number generator and uses it for random number generation.
*
* @param[in] pSeed Buffer to hold the random seed [N/A]
* @param[in] ulLen The size of the buffer [N/A]
*
* @retval SEC_UINT32 On successful set of seed [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If pSeed was NULL or ulLen was 0
[SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If the hardware mode is set
[SEC_HW_ERR_INVALID_OPERATION|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_randSeed(
    SEC_UCHAR * pSeed,
    SEC_UINT32 ulLen);

/*
   Func Name:  CRYPT_addEntropy
*/

/**
* @defgroup CRYPT_addEntropy 
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_addEntropy(
* const SEC_UCHAR* pucEntropyBuf,
* SEC_UINT32 ulLen);
* @endcode
*
* @par Purpose
* This is used to add the given entropy data to the random pool.
*
* @par Description
* CRYPT_addEntropy function adds the given entropy data to the random pool.
*
* @param[in] pucEntropyBuf Buffer to hold the entropy [N/A]
* @param[in] ulLen The size of the buffer [N/A]
*
* @retval SEC_UINT32 On successful set of seed [SEC_SUCCESS|N/A].   
* @retval SEC_UINT32 If pucEntropyBuf is NULL or ulLen is 0 
[SEC_ERR_INVALID_ARG|N/A].          
* @retval SEC_UINT32 If the hardware mode is set 
[SEC_HW_ERR_INVALID_OPERATION|N/A].
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/                  
CRYPTOLINKDLL SEC_UINT32 CRYPT_addEntropy(
    const SEC_UCHAR* pucEntropyBuf,
    SEC_UINT32 ulLen);

/*
   Func Name: CRYPT_testRand
*/

/**
* @defgroup CRYPT_testRand   
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_testRand (
* SEC_UCHAR* nums,
* SEC_UINT32 len);
* @endcode
*
* @par Purpose
* This is used to test the randomness of a number.
*
* @par Description 
* CRYPT_testRand function tests the randomness of a number.
*
* @param[in] nums The number whose randomness is to be tested [N/A]
* @param[in] len The size of the number in bytes [N/A]
*
* @retval SEC_UINT32 If randomness is sufficient [SEC_SUCCESS|N/A]  
* @retval SEC_UINT32 If randomness is insufficient 
or any other error [SEC_ERROR|N/A]                                           
* @retval SEC_UINT32 If the hardware mode is set 
[SEC_HW_ERR_INVALID_OPERATION|N/A] 
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/                              
CRYPTOLINKDLL SEC_UINT32 CRYPT_testRand (SEC_UCHAR *nums, SEC_UINT32 len);

/*
   Func Name: CRYPT_SYM_keyLen
*/

/**
* @defgroup CRYPT_SYM_keyLen  
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_SYM_keyLen(
* SEC_UINT32 ulAlgId);
* @endcode
*
* @par Purpose
* This is used to retrieve the key length of an algorithm
*
* @par Description
* CRYPT_SYM_keyLen function retrieves the key length of
an algorithm. If the given algorithm type
* is not supported, it returns 0.
*
* @param[in] ulAlgId Symmetric algorithm id [N/A]
*
* @retval SEC_UINT32 Key length [N/A|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A            
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_SYM_keyLen(
    SEC_UINT32 ulAlgId);

/*
    Func Name: CRYPT_SYM_blockSize
*/

/**
* @defgroup CRYPT_SYM_blockSize
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_SYM_blockSize(
* SEC_UINT32 ulAlgId);
* @endcode
*
* @par Purpose
* This is used to retrieve the block size of an algorithm.
*
* @par Description
* CRYPT_SYM_blockSize function retrieves the block size of
an algorithm. If the given algorithm type is not supported,
* it returns 0.
*
* @param[in] ulAlgId Symmetric algorithm ID [N/A]
*
* @retval SEC_UINT32 Block size of algorithm [Block size|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_SYM_blockSize(SEC_UINT32 ulAlgId);

/*
    Func Name:  CRYPT_SYM_ivLen
*/

/**
* @defgroup CRYPT_SYM_ivLen
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_SYM_ivLen(
* SEC_UINT32 ulAlgId);
* @endcode
*
* @par Purpose
* This is used to retrieve the IV length of an algorithm.
*
* @par Description
* CRYPT_SYM_ivLen function retrieves the IV length of an algorithm.
If the given algorithm type is not supported, it
* returns 0.
*
* @param[in] ulAlgId Symmetric algorithm ID [N/A]
*
* @retval SEC_UINT32 IV length of algorithm [IV length|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n 
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_SYM_ivLen(
    SEC_UINT32 ulAlgId);

/*
    Func Name:  CRYPT_SYM_padType
*/

/**
* @defgroup CRYPT_SYM_padType
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_SYM_padType(
* SEC_UINT32 ulAlgId);
* @endcode
*
* @par Purpose
* This is used to retrieve the Padding type used by an algorithm.
*
* @par Description
* CRYPT_SYM_padType function retrieves the Padding type used by an 
algorithm. This function returns the symmetric padding
* type. If the given algorithm type is not supported, it returns 0.
*
* @param[in] ulAlgId Symmetric algorithm ID. The padding type is
written on the higher 16 bytes of the algorithm [N/A]
*
* @retval SEC_UINT32 If invalid algorithm ID [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 If undefined padding 
[SEC_CRYPT_ERR_UNDEFINED_PADDING|N/A]
* @retval SEC_UINT32 If algorithm doesnot support padding [0|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/


CRYPTOLINKDLL SEC_UINT32 CRYPT_SYM_padType(
    SEC_UINT32 ulAlgId);

/*
    Func Name:  CRYPT_setFeedbackSize
*/

/**
* @defgroup CRYPT_setFeedbackSize
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_setFeedbackSize (
* CRYPT_CTX ctx,
* SEC_UINT32 ulFeedbackSize);
* @endcode
*
* @par Purpose
* This is used to set the feedback length.
*
* @par Description
* CRYPT_setFeedbackSize function sets the feedback length in bytes.
It is used in CFB and OFB modes.
*
* @param[in] ulFeedbackSize The feedback length to be set [N/A]
* @param[out] ctx Initialized symmetric context [N/A]
*
* @retval SEC_UINT32 On successful return [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 On failure [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_setFeedbackSize (CRYPT_CTX ctx, 
SEC_UINT32 ulFeedbackSize);

/*
    Func Name:  CRYPT_getFeedbackSize
*/

/**
* @defgroup CRYPT_getFeedbackSize
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_getFeedbackSize (CRYPT_CTX ctx);
* @endcode
*
* @par Purpose
* This is used to get the feedback length.
*
* @par Description
* CRYPT_getFeedbackSize function retrieves the segment size,
which is used for feedback, in bytes. It is used in CFB
* and OFB modes.
*
* @param[in] ctx Initialized symmetric context [N/A]
*
* @retval SEC_UINT32 When used for OFB and CFB modes [Feedbacksize|N/A]
* @retval SEC_UINT32 When used for CBC and ECB modes [0|N/A]
* @retval SEC_UINT32 On failure [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_getFeedbackSize (CRYPT_CTX ctx);

/*
    Func Name:  CRYPT_setEffectiveKeyBits
*/

/** 
* @defgroup CRYPT_setEffectiveKeyBits
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_setEffectiveKeyBits(
* CRYPT_CTX ctx,
* SEC_INT iEffKeyBits,
* SEC_UCHAR * pucKey,
* SEC_UINT32 ulKeyLen);
* @endcode
*
* @par Purpose
*   Currently sets the Effective Key bits for only RC2 block cipher and 
*    generates a new Key based on the effective key bits set.
*
* @par Description
* CRYPT_setEffectiveKeyBits function currently sets the Effective Key bits
*                 for only RC2 block cipher and generates a new Key based on 
*                 the effective key bits set. For RC2, if the Effective key 
*                 bits set by the user is more than 1024 or less than zero or 
*                 equal to zero then the Effective Key bits will be 
*                 considered as equal to 1024. This API should be called
*                 once the CRYPT_encryptInit or CRYPT_decryptInit is called.
*
* @param[in] pucKey The key value to be used [N/A]
* @param[in] ulKeyLen The length of the key [N/A]
* @param[out] ctx Address of the context in which the new Key will be set[N/A]
* @param[out] iEffKeyBits The effective key bits need to be set[N/A]
*
* @retval SEC_UINT32 Invalid argument [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Invalid Keylength for alg [SEC_ERR_INVALID_KEY_LEN|N/A]
* @retval SEC_UINT32 Malloc failure [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 On success [SEC_SUCCESS|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 CRYPT_setEffectiveKeyBits(
        CRYPT_CTX ctx,
        SEC_INT iEffKeyBits,
        SEC_UCHAR * pucKey,
        SEC_UINT32 ulKeyLen);

/*
    Func Name:  CRYPT_SYM_mode
*/

/**
* @defgroup CRYPT_SYM_mode
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_SYM_mode(
* SEC_UINT32 ulAlgId);
* @endcode
*
* @par Purpose
* This is used to get mode which is used in algorithm.
*
* @par Description
* CRYPT_SYM_mode function gets working mode(ECB,CBC,OFB,CFB) 
for symmetric algorithm.If given algorithm type is not
* supported, return INVALID_SYMALG_MODE.
*
* @param[in] ulAlgId Symmetric algorithm ID [N/A]
*
* @retval SEC_UINT32 If algorithm Id is valid 
[Symmetric working mode(CBC, ECB, CFB, OFB)|N/A]
* @retval SEC_UINT32 If algorithm Id is invalid [INVALID_SYMALG_MODE|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 CRYPT_SYM_mode(
    SEC_UINT32 ulAlgId);

/*
    Func Name:  CRYPT_name
*/

/**
* @defgroup CRYPT_name
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_CHAR* CRYPT_name(
* SEC_UINT32 ulAlgId);
* @endcode
*
* @par Purpose
* This is used to get name of algorithm.
*
* @par Description
* CRYPT_name function gets name of  algorithm on the basis of algorithm Id.
*
* @param[in] ulAlgId The algorithm Id [N/A]
*
* @retval SEC_CHAR* If Invalid algorithm Id [SEC_NULL|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_CHAR *CRYPT_name(
    SEC_UINT32 ulAlgId);

/*
    Func Name:  CRYPT_MD_size
*/

/**
* @defgroup CRYPT_MD_size
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_MD_size(
* SEC_UINT32 ulAlgType);
* @endcode
*
* @par Purpose
* This is used to retrieve the size of the hash output for an algorithm.
*
* @par Description
* CRYPT_MD_size function retrieves the size of the hash
output for an algorithm.
*
* @param[in] ulAlgType Algorithm ID for digest [N/A]
*
* @retval SEC_UINT32 If valid algorithm Id [Size of the digest|N/A]
* @retval SEC_UINT32 If undefined algorithm [0|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
*
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 CRYPT_MD_size(
    SEC_UINT32 ulAlgType);

/*
    Func Name:  CRYPT_MD_blockSize
*/

/**
* @defgroup CRYPT_MD_blockSize
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_MD_blockSize(
* SEC_UINT32 ulAlgType);
* @endcode
*
* @par Purpose
* This is used to retrieve the block size of the hash algorithm.
*
* @par Description
* CRYPT_MD_blockSize function retrieves the block size of the hash algorithm.
*
* @param[in] ulAlgType Algorithm ID for Digest [N/A]
*
* @retval SEC_UINT32 If algorithm is valid [Block size of the algorithm|N/A]
* @retval SEC_UINT32 If undefined algorithm [0|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_MD_blockSize(
    SEC_UINT32 ulAlgType);


/*
    Func Name:  CRYPT_HMAC_hashType
*/

/**
* @defgroup CRYPT_HMAC_hashType
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_HMAC_hashType(
* SEC_UINT32 ulAlgType);
* @endcode
*
* @par Purpose
* This is used to retrieve the hash algorithm used with the HMAC.
*
* @par Description
* CRYPT_HMAC_hashType function retrieves the hash algorithm used with the HMAC.
*
* @param[in] ulAlgType Algorithm ID for HMAC [N/A]
*
* @retval SEC_UINT32 If algorithm is valid [Algorithm ID of hash algorithm|N/A]
* @retval SEC_UINT32 If undefined algorithm [ALGID_UNKNOWN|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/


CRYPTOLINKDLL SEC_UINT32 CRYPT_HMAC_hashType(
    SEC_UINT32 ulAlgType);

/*
    Func Name:  CRYPT_HMAC_size
*/

/**
* @defgroup CRYPT_HMAC_size
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_HMAC_size(
* SEC_UINT32 ulAlgType);
* @endcode
*
* @par Purpose
* This is used to retrieve the size of the MAC output for an algorithm.
*
* @par Description
* CRYPT_HMAC_size function retrieves the size of the MAC output
for an algorithm.
*
* @param[in] ulAlgType Algorithm ID for HMAC [N/A]
*
* @retval SEC_UINT32 If valid algorithm [Size of the MAC|N/A]
* @retval SEC_UINT32 If Undefined algorithm [0|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_HMAC_size(
    SEC_UINT32 ulAlgType);

/*
    Func Name:  CRYPT_CMAC_size
*/

/**
* @defgroup CRYPT_CMAC_size
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_CMAC_size(
* SEC_UINT32 ulAlgType);
* @endcode
*
* @par Purpose
* This is used to retrieve the size of the MAC output for an algorithm.
*
* @par Description
* CRYPT_CMAC_size function retrieves the size of the MAC output 
for an algorithm.
*
* @param[in] ulAlgType Algorithm ID for CMAC [N/A]
*
* @retval SEC_UINT32 If valid algorithm [Size of the MAC|N/A]
* @retval SEC_UINT32 If Undefined algorithm [0|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_CMAC_size(
    SEC_UINT32 ulAlgType);

/*
    Func Name:  CRYPT_getHashFromSignId
*/

/**
* @defgroup CRYPT_getHashFromSignId
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT CRYPT_getHashFromSignId (
* SEC_UINT uiSignAlg);
* @endcode
*
* @par Purpose
* This is used to extract the Hash algorithm AlgId corresponding 
to a given signing AlgId.
*
* @par Description
* CRYPT_getHashFromSignId function extracts the Hash algorithm 
AlgId corresponding to a given signing AlgId.
*
* @param[in] uiSignAlg The signing Algorithm Id [N/A]
*
* @retval SEC_UINT If sign algorithm is valid [The hash algorithm 
id corresponding to the signing id|N/A]
* @retval SEC_UINT If unknown algorithm id [ALGID_UNKNOWN|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* This function is used by the SSL library.
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT CRYPT_getHashFromSignId (
    SEC_UINT        uiSignAlg);

/*
    Func Name:  CRYPT_getAsymFromSignId
*/

/**
* @defgroup CRYPT_getAsymFromSignId
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT CRYPT_getAsymFromSignId (
* SEC_UINT uiSignAlg);
* @endcode
*
* @par Purpose
* This is used to extract the Asymmetric algorithm AlgId 
corresponding to a given signing AlgId.
*
* @par Description
* CRYPT_getAsymFromSignId function extracts the Asymmetric 
algorithm AlgId corresponding to a given signing AlgId.
*
* @param[in] uiSignAlg The signing AlgId [N/A]
*
* @retval SEC_UINT If algorithm IDs are valid [Asymmetric 
algid corresponding to the signing id|N/A]
* @retval SEC_UINT For unknown AlgId [ALGID_UNKNOWN|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* This function is used by the SSL library.
*       
* @par Related Topics
* N/A
*/


CRYPTOLINKDLL SEC_UINT CRYPT_getAsymFromSignId (
    SEC_UINT        uiSignAlg);

/*
    Func Name:  CRYPT_getSignFromHashAndAsymId
*/

/**
* @defgroup CRYPT_getSignFromHashAndAsymId
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT CRYPT_getSignFromHashAndAsymId (
* SEC_UINT uiAsymAlg,
* SEC_UINT uiHashAlg);
* @endcode
*
* @par Purpose
* This is used to build the signing algid from asymmetric 
and hash algorithm ids.
*
* @par Description
* CRYPT_getSignFromHashAndAsymId function builds the signing 
algid from asymmetric and hash algorithm ids.
*
* @param[in] uiAsymAlg The asymmetric algorithm Id [N/A]
* @param[in] uiHashAlg The hash algorithm Id [N/A]
*
* @retval SEC_UINT If algorithm ids are valid 
[The signing algorithm id corresponding to the asymmetric id and hash id|N/A]
* @retval SEC_UINT If unknown algorithm Id [ALGID_UNKNOWN|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT CRYPT_getSignFromHashAndAsymId (
    SEC_UINT        uiAsymAlg,
    SEC_UINT        uiHashAlg);

/*
    Func Name:  CRYPT_PKEY_new
*/

/**
* @defgroup CRYPT_PKEY_new
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_PKEY_S *CRYPT_PKEY_new();
* @endcode
*
* @par Purpose
* This is used to create a new uninitialized key structure.
*
* @par Description
* CRYPT_PKEY_new function creates a new uninitialized key structure.
*
* @par Parameters
* N/A
*
* @retval SEC_PKEY_S* If Memory allocation fails [0|N/A]
* @retval SEC_PKEY_S* Otherwise [New key structure|N|A] 
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* CRYPT_PKEY_free should be used to free the memory create by the function CRYPT_PKEY_new
* N/A
*       
* @par Related Topics
* N/A
*/


CRYPTOLINKDLL SEC_PKEY_S *CRYPT_PKEY_new(SEC_VOID);

/*
    Func Name:  CRYPT_PKEY_free
*/

/**
* @defgroup CRYPT_PKEY_free
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_VOID CRYPT_PKEY_free(
* SEC_PKEY_S* pKey);
* @endcode
*
* @par Purpose
* This is used to free the key structure.
*
* @par Description
* CRYPT_PKEY_free function frees the key structure.
*
* @param[in] pKey Key to be freed [N/A]
*
* @retval SEC_VOID This function does not return any value [N/A|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_VOID CRYPT_PKEY_free(
    SEC_PKEY_S*     pKey);

/*
    Func Name:  CRYPT_PKEY_type
*/

/**
* @defgroup CRYPT_PKEY_type
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_PKEY_type(
* SEC_PKEY_S* pKey);
* @endcode
* 
* @par Purpose
* This is used to return the algorithm type of a key.
*
* @par Description
* CRYPT_PKEY_type function returns the algorithm type of a key.
*
* @param[in] pKey Key to be used [N/A]
*
* @retval SEC_UINT32 If key is valid [Algorithm ID stored in the key|N/A]
* @retval SEC_UINT32 If key is invalid [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/


CRYPTOLINKDLL SEC_UINT32 CRYPT_PKEY_type(
    SEC_PKEY_S*     pKey);

/*
    Func Name:  CRYPT_PKEY_bits
*/

/**
* @defgroup CRYPT_PKEY_bits
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_PKEY_bits(
* SEC_PKEY_S* pKey);
* @endcode
*
* @par Purpose
* This returns the size of the asymmetric key in bits.
*
* @par Description
* CRYPT_PKEY_bits function returns the size of the asymmetric key in bits.
*
* @param[in] pKey Key to be used [N/A]
*
* @retval SEC_UINT32 If key is valid [Number of bits in the key|N/A]
* @retval SEC_UINT32 If key is invalid [0|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_PKEY_bits(
    SEC_PKEY_S*     pKey);

/*
    Func Name:  CRYPT_PKEY_size
*/

/**
* @defgroup CRYPT_PKEY_size
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_PKEY_size(
* SEC_PKEY_S* pKey);
* @endcode
*
* @par Purpose
* This returns the size of the asymmetric key in bytes.
*
* @par Description
* CRYPT_PKEY_size function returns the size of the asymmetric key in bytes.
*
* @param[in] pKey Key to be used [N/A]
*
* @retval SEC_UINT32 If key is valid [Number of bytes in the key|N/A]
* @retval SEC_UINT32 If key is invalid [0|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/


CRYPTOLINKDLL SEC_UINT32 CRYPT_PKEY_size(
    SEC_PKEY_S*     pKey);

/*
    Func Name:  CRYPT_PKEY_cmp
*/

/**
* @defgroup CRYPT_PKEY_cmp
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_PKEY_cmp(
* SEC_PKEY_S* pKeyA,
* SEC_PKEY_S* pKeyB);
* @endcode
*
* @par Purpose
* This is used to compare two keys.
*
* @par Description
* CRYPT_PKEY_cmp function compares the two keys.
*
* @param[in] pKeyA First key to be used [N/A]
* @param[in] pKeyB Second key to be used [N/A]
*
* @retval SEC_UINT32 When keys match [SEC_CRYPT_MATCH|N/A]
* @retval SEC_UINT32 When keys do not match [SEC_CRYPT_NO_MATCH|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A 
*/


CRYPTOLINKDLL SEC_UINT32 CRYPT_PKEY_cmp(
    SEC_PKEY_S*     pKeyA,
    SEC_PKEY_S*     pKeyB);

/*
    Func Name:  CRYPT_PKEY_copy
*/

/**
* @defgroup CRYPT_PKEY_copy
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_PKEY_copy(
* SEC_PKEY_S* pSrc,
* SEC_PKEY_S* pDest);
* @endcode
*
* @par Purpose
* This is used to copy a key structure to another.
*
* @par Description

* CRYPT_PKEY_copy function copies a key structure to another. 
This function does not copy the parameters.
*
* @param[in] pSrc Source key [N/A]
* @param[in] pDest Destination key [N/A]
*
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If invalid Key [SEC_CRYPT_ERR_INVALID_PKEY|N/A]
* @retval SEC_UINT32 If invalid Arguments [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 On Memory allocation failure [SEC_ERR_MALLOC_FAIL|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_PKEY_copy(
    SEC_PKEY_S*     pSrc,
    SEC_PKEY_S*     pDest);

/*
 Func Name:  CRYPT_PKEY_copyPubKey
*/

/**
* @defgroup CRYPT_PKEY_copyPubKey
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_PKEY_copyPubKey(
* SEC_PKEY_S* pKey,
* SEC_PKEY_S* pOutPubKey);
* @endcode
*
* @par Purpose
* This is used to copy  the public key structure from the given key pair
* to another SEC_PKEY_S structure.
*
* @par Description

* CRYPT_PKEY_copyPubKey function copies the public key from the
* given key pair to another.
*
* @param[in] pKey Source key [N/A]
* @param[in] pOutPubKey Destination key [N/A]
*
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If invalid Key [SEC_CRYPT_ERR_INVALID_PKEY|N/A]
* @retval SEC_UINT32 If invalid AlgorithmId [SEC_ERR_INVALID_ALGID]
* @retval SEC_UINT32 If invalid Arguments [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 On Memory allocation failure [SEC_ERR_MALLOC_FAIL|N/A]
* @par Required Header File
* sec_crypto.h
*
* @par Note
* The memory for the key pOutPubKey must be allocated
* before calling this function. Hence the same should be freed by the user.
* This API is applicable only for RSA, ECDSA and ECDH algorithm.
* N/A
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 CRYPT_PKEY_copyPubKey(
    SEC_PKEY_S* pKey,
    SEC_PKEY_S* pOutPubKey);



/*
    Func Name:  CRYPT_PKEY_copyPrivKey
*/

/**
* @defgroup CRYPT_PKEY_copyPrivKey
* @ingroup HLF High Level Functions
* @par Prototype
* @code

* SEC_UINT32 CRYPT_PKEY_copyPrivKey(
* SEC_PKEY_S* pKey,
* SEC_PKEY_S* pOutPrvKey);
* @endcode
*

* @par Purpose
* This function is used to copy the private key from the
* given key pair to another SEC_PKEY_S structure.
*
* @par Description

* CRYPT_PKEY_copyPrivKey function copies the private key from the given
* key pair to another.
*
* @param[in] pKey Source key [N/A]
* @param[in] pOutPrvKey Destination key [N/A]
*
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If invalid Key [SEC_CRYPT_ERR_INVALID_PKEY|N/A]
* @retval SEC_UINT32 If invalid AlgorithmId [SEC_ERR_INVALID_ALGID]
* @retval SEC_UINT32 If invalid Arguments [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 On Memory allocation failure [SEC_ERR_MALLOC_FAIL|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* The memory for the key pOutPrvKey must be allocated
* before calling this function. Hence the same should be freed by the user.
* This API is applicable only for RSA, ECDSA and ECDH algorithm.
* N/A
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 CRYPT_PKEY_copyPrivKey(
    SEC_PKEY_S* pKey,
    SEC_PKEY_S* pOutPrvKey);


/*
    Func Name:  CRYPT_PKEY_checkParam
*/

/**
* @defgroup CRYPT_PKEY_checkParam
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_PKEY_checkParam(
* SEC_PKEY_S* pkey);
* @endcode
*
* @par Purpose
* This is used to check whether parameters are defined for a key structure.
*
* @par Description
* CRYPT_PKEY_checkParam function checks whether parameters are defined
for a key structure.
*
* @param[in] pKey Key to be checked [N/A]
*
* @retval SEC_UINT32  If parameters are defined [SEC_TRUE|N/A]
* @retval SEC_UINT32 If parameters are not defined [SEC_FALSE|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/


CRYPTOLINKDLL SEC_UINT32 CRYPT_PKEY_checkParam(
    SEC_PKEY_S*     pkey);

/*
    Func Name:  CRYPT_PKEY_cmpParam
*/

/**
* @defgroup CRYPT_PKEY_cmpParam
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_PKEY_cmpParam(
* SEC_PKEY_S* pKeyA,
* SEC_PKEY_S* pKeyB);
* @endcode
*
* @par Purpose
* This is used to compare the parameters of two key structures.
*
* @par Description
* CRYPT_PKEY_cmpParam function compares the parameters of two key structures.
*
* @param[in] pKeyA First key to be compared [N/A]
* @param[in] pKeyB Second key to be compared [N/A]
*
* @retval SEC_UINT32 When parameters match [SEC_CRYPT_MATCH|N/A]
* @retval SEC_UINT32 When parameters do not match [SEC_CRYPT_NO_MATCH|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_PKEY_cmpParam(
    SEC_PKEY_S*     pKeyA,
    SEC_PKEY_S*     pKeyB);

/*
    Func Name:  CRYPT_PKEY_copyParam
*/

/**
* @defgroup CRYPT_PKEY_copyParam
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_PKEY_copyParam(
* SEC_PKEY_S* pSrc,
* SEC_PKEY_S* pDest);
* @endcode
*
* @par Purpose
* This is used to copy the parameters of a key structure to 
another key structure.
*
* @par Description
* CRYPT_PKEY_copyParam function copies the parameters of a key
structure to another key structure.
*
* @param[in] pSrc Source key [N/A]
* @param[in] pDest Destination key [N/A]
*
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If algorithm not supported
[SEC_CRYPT_ERR_UNDEFINED_KEY_OPERATION|N/A]
* @retval SEC_UINT32 Invalid Key [SEC_CRYPT_ERR_INVALID_PKEY|N/A]
* @retval SEC_UINT32 Invalid Arguments [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 On Memory allocation failure [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If Keys are of different type 
[SEC_ERR_KEYPAIR_MISMATCH|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_PKEY_copyParam(
    SEC_PKEY_S*     pSrc,
    SEC_PKEY_S*     pDest);

/*
    Func Name:  CRYPT_PKEY_privORpub
*/

/**
* @defgroup CRYPT_PKEY_privORpub
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_PKEY_privORpub(
* SEC_PKEY_S* pkey);
* @endcode
*
* @par Purpose
* This is used to check whether a given key is a private key,
public key, or a key pair.
*
* @par Description
* CRYPT_PKEY_privORpub function checks whether a given key is
a private key, public key, or a key pair.
*
* @param[in] pKey Key to be checked [N/A]
*
* @retval SEC_UINT32 If Private key [CRYPT_PKEY_PRIVATE|N/A]
* @retval SEC_UINT32 If Public key [CRYPT_PKEY_PUBLIC|N/A]
* @retval SEC_UINT32 If Key Pair [CRYPT_PKEY_PAIR|N/A]
* @retval SEC_UINT32 If unknown Key type [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 If invalid Key [SEC_CRYPT_ERR_INVALID_PKEY|N/A]
* @retval SEC_UINT32 If invalid Arguments [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_PKEY_privORpub(
    SEC_PKEY_S*     pkey);

/*
    Func Name:  CRYPT_PKEY_checkKeyPair
*/

/**
* @defgroup CRYPT_PKEY_checkKeyPair
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_PKEY_checkKeyPair(
* SEC_PKEY_S* pPubKey,
* SEC_PKEY_S* pPrivKey);
* @endcode
*
* @par Purpose
* This is used to check whether a given key-pair is well-formed.
*
* @par Description
* CRYPT_PKEY_checkKeyPair function checks whether a given key-pair 
is well-formed.
*
* @param[in] pPubKey Public key to be used [N/A]
* @param[in] pPrivKey Private key to be used [N/A]
*
* @retval SEC_UINT32 If keys are proper [SEC_TRUE|N/A]
* @retval SEC_UINT32 If keys are not proper or Library is 
not initialized [SEC_FALSE|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* This function is used by the PSE Library.
* This API do not support ALGID_ECDH (EC Diffie-Hellman) and ALGID_DH(Diffie-Hellman) key types.
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_PKEY_checkKeyPair(
    SEC_PKEY_S*     pPubKey,
    SEC_PKEY_S*     pPrivKey);


/*
    Func Name:  CRYPT_PKEY_checkKeyPairEx
*/

/**
* @defgroup CRYPT_PKEY_checkKeyPairEx
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_BOOL CRYPT_PKEY_checkKeyPairEx(
* SEC_PKEY_S* pPubKey,
* SEC_PKEY_S* pPrivKey);
* @endcode
*
* @par Purpose
* This is used to check whether a given public key and 
private key are of the same pair.
*
* @par Description
* CRYPT_PKEY_checkKeyPairEx function checks whether a 
given public key and private key are of the same pair.
*
* @param[in] pPubKey Public key to be used [N/A]
* @param[in] pPrivKey Private key to be used [N/A]
*
* @retval SEC_BOOL If keys belong to a pair [SEC_TRUE|N/A]
* @retval SEC_BOOL If keys does not belong to a pair or
Library is not initialized [SEC_FALSE|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* This function is used by the PSE Library.
* This API do not support ALGID_ECDH (EC Diffie-Hellman) and ALGID_DH(Diffie-Hellman) key types.
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_BOOL CRYPT_PKEY_checkKeyPairEx(
    SEC_PKEY_S*     pPubKey,
    SEC_PKEY_S*     pPrivKey);


/*
    Func Name:  CRYPT_PKEY_getAlgParams
*/

/**
* @defgroup CRYPT_PKEY_getAlgParams
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_VOID* CRYPT_PKEY_getAlgParams(
* SEC_PKEY_S* pKey);
* @endcode
*
* @par Purpose
* This is used to retrieve the params of a key.
*
* @par Description
* CRYPT_PKEY_getAlgParams function retrieves the params of a key.
This is the pointer to the params stored in the key,
* so must not be freed by user. The returned pointer is a pointer 
to an algorithm specific parameter struct like
* DSA_PARA_S.
*
* @param[in] pKey Key struct [N/A]
*
* @retval SEC_VOID* If key is valid [The parameter struct
corresponding to the key|N/A]
* @retval SEC_VOID* If key doesnot have params or arguments
are missing [0|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_VOID* CRYPT_PKEY_getAlgParams(
    SEC_PKEY_S*     pKey);


/*
    Func Name:  CRYPT_PKEY_setAlgParams
*/

/**
* @defgroup CRYPT_PKEY_setAlgParams
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_PKEY_setAlgParams(
* SEC_PKEY_S* pKey,
* SEC_VOID* pParams);
* @endcode
*
* @par Purpose
* This is used to copy the parameters of an algorithm to the key.
*
* @par Description
* CRYPT_PKEY_setAlgParams function copies the parameters of 
an algorithm to the key. The pParams parameter argument must
* contain an algorithm specific parameter structure like 
RSA_PARA_S. After setting params, the input parameter pParams
* can be freed.
*
* @param[in] pKey Key struct [N/A]
* @param[in] pParams Parameter structure [N/A]
*
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If algorithm is not supported 
[SEC_CRYPT_ERR_UNDEFINED_KEY_OPERATION|N/A]
* @retval SEC_UINT32 Invalid Key [SEC_CRYPT_ERR_INVALID_PKEY|N/A]
* @retval SEC_UINT32 Invalid Arguments [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 On Memory allocation failure [SEC_ERR_MALLOC_FAIL|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_PKEY_setAlgParams (
    SEC_PKEY_S*     pKey,
    SEC_VOID*       pParams);


/*
    Func Name:  CRYPT_ecPointToOcts
*/

/**
* @defgroup CRYPT_ecPointToOcts
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UCHAR *CRYPT_ecPointToOcts(
* EC_POINT_S* pPt,
* SEC_UINT* puiLen);
* @endcode
*
* @par Purpose
* This is used to convert an EC_POINT_S structure to an octet string.
*
* @par Description
* CRYPT_ecPointToOcts function converts an EC_POINT_S
structure to an octet string, following the method mentioned in
* ANSI X.9 62 for point to octet conversion. The 
returned buffer can be freed after use.
*
* @param[in] pPt The point to be converted [N/A]
* @param[out] puiLen The length of the octet string [N/A]
*
* @retval SEC_UCHAR* On error [0|N/A] 
* @retval SEC_UCHAR* Otherwise [The octet string|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* Octect string pointer has to be freed by the user using ipsi_free().
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UCHAR *CRYPT_ecPointToOcts (
    EC_POINT_S*     pPt, 
    SEC_UINT*       puiLen);


/*
    Func Name:  CRYPT_octsToECPoint
*/

/**
* @defgroup CRYPT_octsToECPoint
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* EC_POINT_S *CRYPT_octsToECPoint(
* SEC_UCHAR* pucOcts,
* SEC_UINT uiLen);
* @endcode
*
* @par Purpose
* This is used to convert an octet string to an EC_POINT_S structure.
*
* @par Purpose
* CRYPT_octsToECPoint function converts an octet string to
an EC_POINT_S structure, following the method mentioned in
* ANSI X.9 62 for octet to point conversion. The returned 
struct can be freed after use.
*
* @param[in] pucOcts The octet to be converted [N/A]
* @param[in] uiLen The length of the octet string [N/A]
*
* @retval EC_POINT_S* On error [0|N/A]
* @retval EC_POINT_S* Otherwise [The EC point|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* The EC pointer has to be freed by the user using ipsi_free().
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL EC_POINT_S *CRYPT_octsToECPoint (
    SEC_UCHAR*      pucOcts,
    SEC_UINT        uiLen);


/*
    Func Name:  CRYPT_createECParamsById
*/

/**
* @defgroup CRYPT_createECParamsById
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* EC_PARA_S *CRYPT_createECParamsById(
* SEC_UINT32 uiParamID);
* @endcode
*
* @par Purpose
* This is used to get the param structure for a given
well-known parameter Id.
*
* @par Description
* CRYPT_createECParamsById function gets the param structur
e for a given well-known parameter Id. The parameters returned
* can be freed by user. However, the user has to make sure
that memory is freed using functions from the same library
* from which this function is called.
*
* @param[in] uiParamID The id of the well-known parameters [N/A]
*
* @retval EC_PARA_S* On error [0|N/A]
* @retval EC_PARA_S* Otherwise [The parameter structure 
corresponding to id|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* Pointer has to be freed by the user using ipsi_free().
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL EC_PARA_S *CRYPT_createECParamsById(
    SEC_UINT32      uiParamID);


/*
    Func Name:  CRYPT_computeDHKey
*/

/**
* @defgroup CRYPT_computeDHKey
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_computeDHKey(
* SEC_PKEY_S* pPvtKey,
* SEC_PKEY_S* pPubKey,
* SEC_UCHAR* pucKey,
* SEC_UINT32* pulKeyLen);
* @endcode
*
* @par Purpose
* This is used to generate a DH shared secret key from 
private key and peer public key.
*
* @par Description
* CRYPT_computeDHKey function generates a DH shared secret 
key from private key and peer public key. The memory for the
* shared secret must have been allocated prior to calling.
*
* @param[in] pPvtKey Own private key [N/A]
* @param[in] pPubKey Peer public key [N/A]
* @param[out] pucKey Shared secret key [N/A]
* @param[out] pulKeyLen Length of generated shared secret key [N/A]
*
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If algorithm is not supported 
[SEC_CRYPT_ERR_UNDEFINED_KEY_OPERATION|N/A]
* @retval SEC_UINT32 Invalid Key [SEC_CRYPT_ERR_INVALID_PKEY|N/A]
* @retval SEC_UINT32 Invalid Arguments [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If library is not initialized [SEC_ERR_INITLIB|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_computeDHKey(
    SEC_PKEY_S*     pPvtKey,
    SEC_PKEY_S*     pPubKey,
    SEC_UCHAR*      pucKey,
    SEC_UINT32*     pulKeyLen);


/*
    Func Name:  CRYPT_genDHPara
*/

/**
* @defgroup CRYPT_genDHPara
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_genDHPara(
* SEC_UINT32 ulPrimeLen,
* SEC_UINT32 ulGenrtor,
* SEC_PKEY_S* pPara);
* @endcode
*
* @par purpose
* This is used to generate the DH parameters p and g.
*
* @par Description
* CRYPT_genDHPara function generates the DH parameters p & g.
*
* @param[in] ulPrimeLen Length of the prime p [N/A]
* @param[in] ulGenrtor Generator g [N/A]
* @param[out] pPara Key structure with parameters [N/A]
*
* @retval SEC_UINT32 Always [SEC_CRYPT_ERR_UNDEFINED_KEY_OPERATION|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* This is unimplemented.
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 CRYPT_genDHPara(
    SEC_UINT32      ulPrimeLen,
    SEC_UINT32      ulGenrtor,
    SEC_PKEY_S*     pPara);


#ifndef __IPSI_NO_DH_PARA__

/*
    Func Name:  CRYPT_createDHParams
*/

/**
* @defgroup CRYPT_createDHParams
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_INT CRYPT_createDHParams(DH_PARA_S *pstDhPara,
*                           SEC_DH_PRIME_E enPrime);
* @endcode
*
* @par Purpose
* This function is used to get the dh parameters defined in the RFC 2409
* and 3526.
*
* @par Description
* CRYPT_createDHParams function will update the input argument pstDhPara 
* corresponding to the enum enPrime. The dh parameters updated in the 
* pstDhPara is according to the RFC 2409 or 3526 depending on the enPrime.
*
* @param[in] enPrime enum to identify the prime [N/A]
* @param[out] pstDhPara DH parameter structure [N/A]
*
* @retval SEC_INT On Success [SEC_SUCCESS|N/A]
* @retval SEC_INT If algorithm is not supported [SEC_ERROR|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
*	- DH Group 1 prime is GROUPID_RFC2409_1
*	- DH Group 2 prime is GROUPID_RFC2409_2
*	- DH Group 5 prime is GROUPID_RFC3256_5
*	- DH Group 14 prime is GROUPID_RFC3526_14
*	- DH Group 15 prime is GROUPID_RFC3526_15
*	- DH Group 16 prime is GROUPID_RFC3526_16
*
*	- The generator updated in the pstDhPara is always 2.
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_INT CRYPT_createDHParams(DH_PARA_S *pstDhPara,
                                         SEC_DH_PRIME_E enPrime);

#endif


/*
    Func Name:  CRYPT_computeECDHKey
*/

/**
* @defgroup CRYPT_computeECDHKey
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_computeECDHKey(
* SEC_PKEY_S* pPvtKey,
* SEC_PKEY_S* pPubKey,
* SEC_UCHAR* pucKey,
* SEC_UINT32* pulKeyLen);
* @endcode
*
* @par Purpose
* This is used to generate a ECDH shared secret key.
*
* @par Description
* CRYPT_computeECDHKey function generates a ECDH shared 
secret key from private key and peer public key. The memory for
* the shared secret must have been allocated prior to calling.
*
* @param[in] pPvtKey Own private key [N/A]
* @param[in] pPubKey Peer public key [N/A]
* @param[out] pucKey Shared secret key [N/A]
* @param[out] pulKeyLen Length of generated shared secret key [N/A]
*
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid Key [SEC_CRYPT_ERR_INVALID_PKEY|N/A]
* @retval SEC_UINT32 Invalid Arguments [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If library is not initialized [SEC_ERR_INITLIB|N/A]
* @retval SEC_UINT32 Incorrect Algorithm ID i.e. Key type is not ALGID_ECDH or ALGID_ECDSA or
* ALGID_ECKEY [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 Memory allocation failed [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 On other errors [SEC_ERR|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
*   - CRYPT_computeECDHKey will only output standard diffie helman primitive.
*     To get the modified diffie helman primitive use CRYPT_computeECDHKey_ex API.
*   - The minimum size of output key buffer should be atleast the input public key size.
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_computeECDHKey(
    SEC_PKEY_S*     pPvtKey,
    SEC_PKEY_S*     pPubKey,
    SEC_UCHAR*      pucKey,
    SEC_UINT32*     pulKeyLen);


/* Next Five functions are related to BigInt representatiosn */


/*
    Func Name:  SEC_assignToBigInt
*/

/**
* @defgroup SEC_assignToBigInt
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_INT SEC_assignToBigInt(
* const SEC_UINT intVal,
* SEC_BIGINT_S* pData);
* @endcode
*
* @par Purpose
* This is used to assign small values to the big integer structure.
*
* @par Description
* SEC_assignToBigInt function assigns small values to the 
big integer structure.
*
* @param[in] intVal The integer to be converted [N/A]
* @param[out] pData The big integer to be initialized [N/A]
*
* @retval SEC_INT On successful conversion [SEC_SUCCESS|N/A]
* @retval SEC_INT If conversion fails [SEC_ERROR|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_INT SEC_assignToBigInt (
    const SEC_UINT  intVal, 
    SEC_BIGINT_S*   pData);


/*
    Func Name:  SEC_cmpBigInt
*/

/**
* @defgroup SEC_cmpBigInt
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_INT SEC_cmpBigInt(
* SEC_BIGINT_S* pA,
* SEC_BIGINT_S* pB);
* @endcode
*
* @par Purpose
* This is used to compare two bigint values.
*
* @par Description
* SEC_cmpBigInt function compares two bigint values.
*
* @param[in] pA The first bigint [N/A]
* @param[in] pB The second bigint [N/A]
*
* @retval SEC_INT If pA is greater than pB [Greater than zero|N/A]
* @retval SEC_INT If pB is greater than pA [Lesser than zero|N/A]       
* @retval SEC_INT If pB is equal to pA [Equal to zero|N/A]      
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_INT SEC_cmpBigInt (
    SEC_BIGINT_S*   pA,
    SEC_BIGINT_S*   pB);


/*
    Func Name:  SEC_cpyBigInt
*/

/**
* @defgroup SEC_cpyBigInt
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 SEC_cpyBigInt(
* SEC_BIGINT_S* pstDestBigInt,
* SEC_BIGINT_S* pstSrcBigInt);
* @endcode
*
* @par Purpose
* This is used to copy one bigint value into another.
*
* @par Description
* SEC_cpyBigInt function copies one bigint value into another.
*
* @param[in] pstSrcBigInt The source bigint to be copied [N/A]
* @param[out] pstDestBigInt The destination bigint [N/A]
* 
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid Arguments [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 SEC_cpyBigInt (
    SEC_BIGINT_S*   pstDestBigInt,
    SEC_BIGINT_S*   pstSrcBigInt);


/*
    Func Name:  SEC_cvtToBigInt
*/

/**
* @defgroup SEC_cvtToBigInt
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_INT SEC_cvtToBigInt(
* SEC_CHAR* pHexStr,
* SEC_BIGINT_S* pData);
* @endcode
*
* @par Purpose
* This is used to convert the given hex string to octet representation.
*
* @par Description
* SEC_cvtToBigInt function converts the given hex string to 
octet representation. The input string is expected in two's
* complement form. The input string may or may not have a 
'0x'as a prefix. For eg: "0x12" and "12" mean the same.
*
* @param[in] pHexStr The hex character string [N/A]
* @param[out] pData The big integer to be initialized [N/A]
*
* @retval SEC_INT On Successful conversion [SEC_SUCCESS|N/A]
* @retval SEC_INT If conversion fails [SEC_ERROR|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* Eg: SEC_cvtToBigInt ("0x1234aE", &stOcts).\n
* Above call will return stOcts with {3, (int (*)[3])&{\x12\x34\xaE}}.\n
* "0xFF" is a negative number in 8 bits and will be stored as "FF".\n
* "0xFFF" is a positive number in 16 bits and will be stored as "0FFF".\n
* To store "0xFFF" as a negative value give "0xFFFF" (padding leading
4 bits with 1').\n
*"0x0FF" is a positive number in 16 bits and will be stroed as "00FF"
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_INT SEC_cvtToBigInt (
    SEC_CHAR*       pHexStr,
    SEC_BIGINT_S*   pData);


/*
    Func Name:  SEC_dupBigInt
*/

/**
* @defgroup SEC_dupBigInt
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_BIGINT_S *SEC_dupBigInt(
* SEC_BIGINT_S* pstBigInt);
* @endcode
*
* @par Purpose
* This is used to create a duplicate bigint.
*
* @par Description
* SEC_dupBigInt function creates a duplicate bigint.
*
* @param[in] pstBigInt The source bigint to be duplicated [N/A]]
*
* @retval SEC_BIGINT_S* On error [0|N/A]
* @retval SEC_BIGINT_S* Otherwise [Pointer to the duplicated bigint|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* Pointer to the duplicated bigint has to be freed by the user
using ipsi_free().
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_BIGINT_S *SEC_dupBigInt (
    SEC_BIGINT_S*   pstBigInt);


/* context functions */

/*
    Func Name:  CRYPT_CTX_status
*/

/**
* @defgroup CRYPT_CTX_status
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_BOOL CRYPT_CTX_status(
* CRYPT_CTX ctx);
* @endcode
*
* @par Purpose
* This is used to check if the context is NULL or initialized.
*
* @par Description
* CRYPT_CTX_status function checks if the context is NULL or initialized.
*
* @param[in] ctx The symmetric context to be validated [N/A]
*
* @retval SEC_BOOL If context is valid [SEC_TRUE|N/A]
* @retval SEC_BOOL If context is Invalid [SEC_FALSE|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
/* context status, not exist, initiated or in using */
CRYPTOLINKDLL SEC_BOOL CRYPT_CTX_status(
    CRYPT_CTX ctx);


/*
    Func Name:  CRYPT_isValidAlgId
*/

/**
* @defgroup CRYPT_isValidAlgId
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_BOOL CRYPT_isValidAlgId(SEC_UINT32 ulAlgId,SEC_ALG_CATEGORY_E enAlgCat);
* @endcode
*
* @par Purpose
* This is used to specify if the given algorithm is a valid algorithm or not.
*
* @par Description
* CRYPT_isValidAlgId function specifies that the given 
algorithm is a valid algorithm in the given category of crypto
* algorithms.
*
* @param[in] ulAlgId The algorithm Id [N/A
* @param[in] enAlgCat The type(category)of crypto algorithms [N/A]
*
* @retval SEC_BOOL If algorithm is valid [SEC_TRUE|N/A]
* @retval SEC_BOOL If algorithm is Invalid or library is not
initialized [SEC_FALSE|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
/* checks if the given AlgId is a valid algId of the given AlgCategory */
CRYPTOLINKDLL SEC_BOOL CRYPT_isValidAlgId(SEC_UINT32 ulAlgId,
SEC_ALG_CATEGORY_E enAlgCat);


/*
    Func Name:  CRYPT_saveRandState
*/

/**
* @defgroup CRYPT_saveRandState
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_INT CRYPT_saveRandState (const SEC_CHAR *file);
* @endcode
*
* @par Purpose
* This is used to save the random number generator internal 
state to a given file.
*
* @par Description
* CRYPT_saveRandState function saves the random number generator 
internal state to a given file.
*
* @param[in] file The file name [N/A]
*
* @retval SEC_INT If save is successful [SEC_SUCCESS|N/A]
* @retval SEC_INT If file operation(open, write or close) failed or NULL argument passed [SEC_ERROR|N/A]
* @retval SEC_INT If the hardware mode is set 
[SEC_HW_ERR_INVALID_OPERATION|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* 1. This function tries to save the rand state to the file name provided. But, this API doesn't set any specific
*     permissions for the file. If the file is being newly created, then it will have only default permissions. 
*     The permissions for this file (whether newly created or existing one) is totally dependent on the behavior
*     of the file system file open APIs (like fopen). If users, want to have restricted access permissions for the 
*     Rand State file, then they can use the CRYPT_getRandState API and get the rand state directly and store 
*     it in a file of their choice with appropriate access permissions.
*
*2. No specific validation is done for the filename or the path of the filename passed through the argument 
*    "file" to this API. User should themselves handle path canonicalization and validation of path and filename
*    before passing it to this API. Users are strongly suggested to use CRYPT_getRandState API instead of this
*    API and save the rand state to a file of their choice.
*
*
*
*\n
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_INT CRYPT_saveRandState (const SEC_CHAR *file);


/*
    Func Name:  CRYPT_loadRandState
*/

/**
* @defgroup CRYPT_loadRandState
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_INT CRYPT_loadRandState (const SEC_CHAR *file);
* @endcode
*
* @par Purpose
* This is used to load a saved random number genrator 
internal state from a given file.
*
* @par Description
* CRYPT_loadRandState function loads a saved random number 
genrator internal state from a given file.
*
* @param[in] file The file name [N/A]
*
* @retval SEC_INT If load is successful [SEC_SUCCESS|N/A]
* @retval SEC_INT If file operation(open, read or close) failed, empty file or NULL argument passed  [SEC_ERROR|N/A]
* @retval SEC_INT If the hardware mode is set
[SEC_HW_ERR_INVALID_OPERATION|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_INT CRYPT_loadRandState (const SEC_CHAR *file);

/*
    Func Name:  CRYPT_libraryInit
*/

/**
* @defgroup CRYPT_libraryInit
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_libraryInit();
* @endcode
*
* @par Purpose
* This is used to initialize the cryptographic library.
*
* @par Description
* CRYPT_libraryInit function initializes the cryptographic library.
*
* @par Parameters
* N/A
*
* @retval SEC_UINT32 If library initialization is successful [SEC_SUCCESS|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A 
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_libraryInit(void);

/*
 Func Name:  CRYPT_keyWrap
*/

/**
* @defgroup CRYPT_keyWrap
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_BOOL CRYPT_keyWrap(
* SEC_UCHAR* ciphertxt,
* const SEC_UCHAR* puckey,
* SEC_UINT32 ulKlen,
* SEC_UCHAR* plaintext,
* SEC_UCHAR* iv,
* SEC_UINT32 npt);
* @endcode
*
* @par Purpose
* This is used to generate an encrypted key.
*
* @par Description
* CRYPT_keyWrap function generats an encrypted key using an original key.
*
* @param[in] puckey Pointer to the key [N/A]
* @param[in] ulKlen The size of key in octets. The size 
must be 16,24 or 32 [N/A]
* @param[in] plaintext Pointer to the plain text [N/A]
* @param[in] iv Pointer to initial value [N/A]
* @param[in] npt A block number of key data plain text [N/A]
* @param[out] ciphertxt Pointer to the cipher text [N/A]
*
* @retval SEC_BOOL On failure [SEC_FALSE|N/A]
* @retval SEC_BOOL On success [SEC_TRUE|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_BOOL CRYPT_keyWrap(
    SEC_UCHAR*      ciphertxt,
    const SEC_UCHAR*puckey,
    SEC_UINT32      ulKlen,
    SEC_UCHAR*      plaintext,
    SEC_UCHAR*      iv,
    SEC_UINT32      npt);


/*
 Func Name:  CRYPT_HashCtxCopy
*/

/**
* @defgroup CRYPT_HashCtxCopy
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_BOOL CRYPT_HashCtxCopy(
* CRYPT_CTX outCtx,
* CRYPT_CTX inCtx);
* @endcode
*
* @par Purpose
* This is used to copy a hash context into another context.
*
* @par Description
* CRYPT_HashCtxCopy function copyies a hash context into another context.
*
* @param[in] inCtx Pointer to the input hash context [N/A]
* @param[out] outCtx Pointer to updated hash context [N/A]
*
* @retval SEC_BOOL On failure [SEC_FALSE|N/A]
* @retval SEC_BOOL On success [SEC_TRUE|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_BOOL CRYPT_HashCtxCopy(CRYPT_CTX outCtx, CRYPT_CTX inCtx);


/*
     Func Name:  CRYPT_HASH_ALG
*/

/**
* @defgroup CRYPT_HASH_ALG
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_HASH_ALG(CRYPT_CTX Ctx);
* @endcode
*
* @par Purpose
* This is used to get the hash algorithm from hash context.
*
* @par Description
* CRYPT_HASH_ALG function gets the hash algorithm from hash context.
*
* @param[in] Ctx Hash context [N/A]
*
* @retval SEC_UINT32 Hash Algorithm Id [Hash Algorithm Id|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 CRYPT_HASH_ALG(CRYPT_CTX Ctx);

/*
 Func Name:  CRYPT_keyUnwrap
*/

/**
* @defgroup CRYPT_keyUnwrap
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_BOOL CRYPT_keyUnwrap(
* SEC_UCHAR* plaintext,
* const SEC_UCHAR* puckey,
* SEC_UINT32 ulKlen,
* SEC_UCHAR* ciphertxt,
* SEC_UCHAR* iv,
* SEC_UINT32 npt);
* @endcode
*
* @par Purpose
* This is used to generate an original key using an encrypted key.
*
* @par Description
* CRYPT_keyUnwrap function generats an original key using an encrypted key.
*
* @param[in] puckey Pointer to the key [N/A]
* @param[in] ulKlen The size of key in octets. 
The size must be 16,24 or 32 [N/A]
* @param[in] ciphertxt Pointer to the cipher text [N/A]
* @param[in] iv Pointer to initial value [N/A]
* @param[in] npt A block number of key data plain text [N/A]
* @param[out] plaintext Pointer to the plain text [N/A]
*
* @retval SEC_BOOL On failure [SEC_FALSE|N/A]
* @retval SEC_BOOL On success [SEC_TRUE|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL  SEC_BOOL CRYPT_keyUnwrap(
    SEC_UCHAR*      plaintext,
    const SEC_UCHAR*puckey,
    SEC_UINT32      ulKlen,
    SEC_UCHAR*      ciphertxt,
    SEC_UCHAR*      iv,
    SEC_UINT32      npt);


/*
    Func Name:  CRYPT_ctxdigestFinal
*/
/** 
* @defgroup CRYPT_ctxdigestFinal
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_ctxdigestFinal (
* CRYPT_CTX*  pCtx,
* SEC_UCHAR*  pucDigest,
* SEC_UINT32* pulDigestLen);
* @endcode
*
* @par Purpose
* This is used to complete digest operation on remaining data, and is
* called at the end of digest operation.
*
* @par Description
* CRYPT_ctxdigestFinal function completes digest operation on remaining data, 
*and is called at the end of digest operation.
* A digestInit must have been called before calling this function. This 
function calculates the digest and doesn't free the
* context. The memory for digest must already have been allocated.
*
* @param[in] pCtx The context for digest [N/A]
* @param[out] pucDigest The digest [N/A]
* @param[out] pulDigestLen The digest length [N/A]
*
* @retval SEC_UINT32 If digest is calculated [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If context values are not correct 
[SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If arguments are invalid[SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
*	- CRYPT_digestReset
*	- CRYPT_digestFree
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_ctxdigestFinal(
CRYPT_CTX* pCtx,SEC_UCHAR* pucDigest, SEC_UINT32* pulLen);


/*
    Func Name:  CRYPT_digestReset
*/
/** 
* @defgroup CRYPT_digestReset
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_digestReset (
* CRYPT_CTX  pCtx);
* @endcode
*
* @par Purpose
* This is used to reset hash context to initial state.
*
* @par Description
* CRYPT_digestReset function resets hash context to initial state. 
* A digestInit must have been called before calling this function. 
*
* @param[in] pCtx The context for digest [N/A]

* @retval SEC_UINT32 If reset  is successful [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If arguments are invalid [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
*	- CRYPT_digestFree
*	- CRYPT_ctxdigestFinal
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_digestReset(
CRYPT_CTX pCtx);

/*
    Func Name:  CRYPT_digestFree
*/
/** 
* @defgroup CRYPT_digestFree
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_digestFree (
* CRYPT_CTX  *pCtx);
* @endcode
*
* @par Purpose
* This is used to free hash contex.
*
* @par Description
* CRYPT_digestFree function frees hash context. 
* A digestInit must have been called before calling this function. 
*
* @param[in] pCtx The context for digest [N/A]

* @retval SEC_VOID This function does not return any value [N/A|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
*	- CRYPT_digestReset
*	- CRYPT_ctxdigestFinal
*/

CRYPTOLINKDLL SEC_VOID CRYPT_digestFree(CRYPT_CTX *pCtx);




/* The RSA public key */
/**
* @defgroup RSA_PUB_KEY_S
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct stRSA_PUB_KEY
* {
*  SEC_BIGINT_S stN;
*  SEC_BIGINT_S stE;
* }RSA_PUB_KEY_S;
* @endcode
*
* @datastruct stN Modulus n.
* @datastruct stE Public exponent e.
*/
typedef struct stRSA_PUB_KEY{
    SEC_BIGINT_S stN;
    SEC_BIGINT_S stE;
} RSA_PUB_KEY_S;

/* The RSA private key */
/**
* @defgroup RSA_PRV_KEY_S
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct stRSA_PRV_KEY
* {
*  SEC_BIGINT_S stN;
*  SEC_BIGINT_S stE;
*  SEC_BIGINT_S stD;
*  SEC_BIGINT_S stP;
*  SEC_BIGINT_S stQ;
*  SEC_BIGINT_S stDP;
*  SEC_BIGINT_S stDQ;
*  SEC_BIGINT_S stQInv;
* }RSA_PRV_KEY_S;
* @endcode
*
* @datastruct stN Modulus.
* @datastruct stE Public exponent e.
* @datastruct stD Private exponent.
* @datastruct stP Prime factor p.
* @datastruct stQ Prime factor q.
* @datastruct stDP Exponent dP for CRT.
* @datastruct stDQ Exponent dQ for CRT.
* @datastruct stQInv CRT coefficient qInv.
*/
typedef struct stRSA_PRV_KEY{
    SEC_BIGINT_S stN;   /* modulus n */
    SEC_BIGINT_S stE;   /* public exponent e */

    SEC_BIGINT_S stD;   /* private exponent */
    SEC_BIGINT_S stP;   /* prime factor p */
    SEC_BIGINT_S stQ;   /* prime factor q */
    SEC_BIGINT_S stDP;  /* exponent dP for CRT */
    SEC_BIGINT_S stDQ;  /* exponent dQ for CRT */
    SEC_BIGINT_S stQInv; /* CRT co-efficient qInv */
} RSA_PRV_KEY_S;


/* The RSA key - can have one or both keys of a pair */
/**
* @defgroup RSA_KEY_S
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct stRSA_KEY
* {
*  SEC_UINT32 keyType;
*  SEC_UINT32 bits;
*  union
*  {
*   RSA_PUB_KEY_S* pPubKey;
*   RSA_PRV_KEY_S* pPrvKey;
*  }key;
* }RSA_KEY_S;
* @endcode
*
* @datastruct keyType Public or private or pair.
* @datastruct bits Length in bits of modulus.
* @datastruct key Union enclosing pointer to the key structure.
* @datastruct pPubKey Pointer to the RSA public key structure.
* @datastruct pPrvKey Pointer to the RSA private key structure.
*/
typedef struct stRSA_KEY
{
    SEC_UINT32 keyType;     /* public or private or pair */
    SEC_UINT32 bits;        /* length in bits of modulus */
    union
    {
        RSA_PUB_KEY_S* pPubKey;
        RSA_PRV_KEY_S* pPrvKey;
    } key;

} RSA_KEY_S;


/*
                Structures  & definitions needed for SSL
*/
/* All the integers expressed as octet strings. */
#define MAX_RSA_MODULUS_LEN     512
#define MAX_RSA_MODULUS_BITS    (MAX_RSA_MODULUS_LEN * 8)
#define MAX_RSA_PRIME_BITS      ((MAX_RSA_MODULUS_BITS + 1) / 2)
#define MAX_RSA_PRIME_LEN       ((MAX_RSA_PRIME_BITS + 7) / 8)

/**
* @defgroup RSA_OctKey
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct
* {
*  size_t bits;
*  unsigned char mod[MAX_RSA_MODULUS_LEN];
*  unsigned char exp[MAX_RSA_MODULUS_LEN];
* }RSA_OctKey;
* @endcode
*
* @datastruct bits Length in bits of modulus.
* @datastruct mod[MAX_RSA_MODULUS_LEN] Modulus n.
* @datastruct exp[MAX_RSA_MODULUS_LEN] Public/private exponent e/d.
*/
typedef struct 
{
    size_t bits;                  /* length in bits of modulus */
    unsigned char mod[MAX_RSA_MODULUS_LEN];   

    /* modulus n */
    
    unsigned char exp[MAX_RSA_MODULUS_LEN];   

    /* public/private exponent e/d */
    
} RSA_OctKey;

/**
* @defgroup RSA_OctPrvKeyCRT
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct
* {
*  size_t bits;
*  unsigned char p[MAX_RSA_PRIME_LEN];
*  unsigned char q[MAX_RSA_PRIME_LEN];
*  unsigned char dP[MAX_RSA_PRIME_LEN];
*  unsigned char dQ[MAX_RSA_PRIME_LEN];
*  unsigned char qInv[MAX_RSA_PRIME_LEN];
* }RSA_OctPrvKeyCRT;
* @endcode
*
* @datastruct bits Length in bits of modulus.
* @datastruct p[MAX_RSA_PRIME_LEN] Prime factor p.
* @datastruct q[MAX_RSA_PRIME_LEN] Prime factor q.
* @datastruct dP[MAX_RSA_PRIME_LEN] Exponent dP for CRT.
* @datastruct dQ[MAX_RSA_PRIME_LEN] Exponent dQ for CRT.
* @datastruct qInv[MAX_RSA_PRIME_LEN] CRT co-efficient qInv.
*/
typedef struct 
{
    size_t bits;                  /* length in bits of modulus */
    unsigned char p[MAX_RSA_PRIME_LEN];       /* prime factor p */
    unsigned char q[MAX_RSA_PRIME_LEN];       /* prime factor q */
    unsigned char dP[MAX_RSA_PRIME_LEN];      /* exponent dP for CRT */
    unsigned char dQ[MAX_RSA_PRIME_LEN];      /* exponent dQ for CRT */
    unsigned char qInv[MAX_RSA_PRIME_LEN];    /* CRT coefficient qInv */
} RSA_OctPrvKeyCRT;

typedef RSA_OctKey RSA_PubKey;
typedef RSA_OctPrvKeyCRT RSA_PrvKey;

/*
    Func Name:  rsa_cvtPKey
*/

/**
* @defgroup rsa_cvtPKey
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT rsa_cvtPKey (RSA_KEY_S* pRSAKey,
*    void* pKey, SEC_UINT32 ulKeyType);
* @endcode
*
* @par Purpose
* This is used to covert the RSA key from another key.
*
* @par Description
* rsa_cvtPKey converts the RSA key (RSA_KEY_S *) from pkey depending on the key type.
*
* @param[in] pRSAKey RSA key to be converted [N/A]
* @param[in] pKey Key to be used for conversion[N/A]
* @param[in] ulKeyType Key type, whether CRYPT_PKEY_PUBLIC or CRYPT_PKEY_PRIVATE [N/A]
*
* @retval SEC_UINT32 On success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Indicates invalid key type [SEC_CRYPT_ERR_INVALID_PKEY|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT rsa_cvtPKey (
    RSA_KEY_S* pRSAKey,
    void* pKey,
    SEC_UINT32 ulKeyType);


/*
    Func Name:  rsa_padPKCSType1
*/

/**
* @defgroup rsa_padPKCSType1
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT rsa_padPKCSType1 (
*    SEC_UCHAR aucCBuf[],
*    SEC_UINT blkSz,
*    SEC_UCHAR* pucBuf,
*    SEC_UINT blkLen);
* @endcode
*
* @par Purpose
* This is used to pad the RSA encoded buffer with PKCS Type1.
*
* @par Description
* rsa_padPKCSType1 used to pad the RSA encoded buffer with PKCS Type1 and provide the output .
*
* @param[out] aucCBuf Output buffer to be updated with padded data [N/A]
* @param[in] blkSz RSA key block size [N/A]
* @param[in] pucBuf Buffer to be padded[N/A]
* @param[in] blkLen Length of the buffer to be padded [N/A]
*
* @retval SEC_UINT32 On success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Indicates invalid key length [SEC_ERR_INVALID_KEY_LEN|N/A]
* @retval SEC_UINT32 Indicates data size is more than key size [SEC_CRYPT_ERR_LARGE_DATA_SIZE|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT rsa_padPKCSType1 (
    SEC_UCHAR aucCBuf[],
    SEC_UINT blkSz,
    SEC_UCHAR* pucBuf,
    SEC_UINT blkLen);

/*
    Func Name:  rsa_unPadPKCSType2
*/

/**
* @defgroup rsa_unPadPKCSType2
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT rsa_unPadPKCSType2 (
*    SEC_UCHAR aucCBuf[],
*    SEC_UINT blkSz,
*    SEC_UCHAR* pucBuf,
*    SEC_UINT* blkLen);
* @endcode
*
* @par Purpose
* This is used to remove the padding of RSA Type2 from the decoded buffer.
*
* @par Description
* rsa_padPKCSType2 used to remove the padding of RSA Type2 from the decoded buffer.
*
* @param[out] aucCBuf Output buffer to be updated with data after removing padding [N/A]
* @param[in] blkSz RSA key block size [N/A]
* @param[in] pucBuf Buffer on which padding to be removed[N/A]
* @param[in] blkLen Length of the buffer to be padded [N/A]
*
* @retval SEC_UINT32 On success [IPSI_TRUE|N/A]
* @retval SEC_UINT32 On failure [IPSI_FALSE|N/A]
* @retval SEC_UINT32 Invalid arguments [SEC_ERR|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT rsa_unPadPKCSType2 (
    SEC_UCHAR aucCBuf[],
    SEC_UINT blkSz,
    SEC_UCHAR* pucBuf,
    SEC_UINT* blkLen);

// PKEY encode decode functions.
/*
    Func Name:  CRYPT_RSAPubKeyDecode
*/

/**
* @defgroup CRYPT_RSAPubKeyDecode
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_RSAPubKeyDecode(
*   SEC_PKEY_S *pOutKey, 
*   SEC_CHAR *buf);
* @endcode
*
* @par Purpose
* This is used to decode the passed buffer and returns the RSA key structure.
*
* @par Description
* CRYPT_RSAPubKeyDecode decodes buffer into RSA public key structure.
*
* @param[in] buf The buffer which is to be decoded [N/A]
* @param[out] pOutKey Key to be updated[N/A]
*
* @retval SEC_UINT32 On success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Indicates invalid key [SEC_CRYPT_ERR_INVALID_PKEY|N/A]
* @retval SEC_UINT32 Indicates failure in memory allocation [SEC_ERR_MALLOC_FAIL|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* CRYPT_RSAPubKeyEncode
*/
CRYPTOLINKDLL SEC_UINT32 CRYPT_RSAPubKeyDecode(SEC_PKEY_S *pOutKey, 
    SEC_CHAR * buf);


/*
    Func Name:  CRYPT_RSAPubKeyEncode
*/

/**
* @defgroup CRYPT_RSAPubKeyEncode
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_RSAPubKeyEncode(
* SEC_PKEY_S *pInKey,
* SEC_UINT *uiSize,SEC_UCHAR **pcEncodedBuff);
* @endcode
*
* @par Purpose
* This is used to encode the passed RSA key structure and returns 
* the encoded buffer.
*
* @par Description
* CRYPT_RSAPubKeyEncode encodes RSA public key structure.
*
* @param[in]  pInKey Key to be encoded [N/A]
* @param[out] uiSize Size of encoded buffer [N/A]
* @param[out] pcEncodedBuff The encoded buffer [N/A]
*
* @retval SEC_UINT32 On success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If pInKey contains a non RSA key [SEC_ERR_NON_RSA_KEY|N/A]
* @retval SEC_UINT32 If pInKey does not contain any key [SEC_ERR_NO_KEY|N/A]
* @retval SEC_UINT32 Indictes failure of memory allocation [SEC_ERR_MALLOC_FAIL|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* CRYPT_RSAPubKeyDecode
*/
CRYPTOLINKDLL SEC_UINT32 CRYPT_RSAPubKeyEncode(SEC_PKEY_S *pInKey,
                        SEC_UINT *uiSize,SEC_UCHAR **pcEncodedBuff);


/**
* @defgroup DH_KEY_S
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct stDH_KEY
* {
*  SEC_UINT32 keyType;
*  DH_PARA_S* pPara;
*  SEC_BIGINT_S stPubKey;
*  SEC_BIGINT_S stPrvKey;
* }DH_KEY_S;
* @endcode
*
* @datastruct keyType Public or private or pair.
* @datastruct pPara Optional parameters.
* @datastruct stPubKey Public key structure.
* @datastruct stPrvKey Private key structure.
*/
typedef struct stDH_KEY
{
    SEC_UINT32 keyType;         /* public or private or pair */
    DH_PARA_S* pPara;           /* optional parameters */
    SEC_BIGINT_S stPubKey;      /* public key structure*/
    SEC_BIGINT_S stPrvKey;      /* private key structure*/
} DH_KEY_S;


/* DSA key */
/**
* @defgroup DSA_KEY_S
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct stDSA_KEY
* {
*  SEC_UINT32 keyType;
*  DSA_PARA_S* pPara;
*  SEC_BIGINT_S stPubKey;
*  SEC_BIGINT_S stPrvKey;
* }DSA_KEY_S;
* @endcode
*
* @datastruct keyType Public or private or pair.
* @datastruct pPara Optional parameters.
* @datastruct stPubKey Public key structure.
* @datastruct stPrvKey Private key structure.
*/
typedef struct stDSA_KEY
{
    SEC_UINT32 keyType;         /* public or private or pair */
    DSA_PARA_S* pPara;          /* optional parameters */
    SEC_BIGINT_S stPubKey;      /* public key structure*/
    SEC_BIGINT_S stPrvKey;      /* private key structure*/
} DSA_KEY_S;


/* Generic EC public key */
typedef struct stEC_POINT EC_PUB_KEY_S;

/* Generic EC private key */
typedef struct stBIGINT EC_PRV_KEY_S;

/* Generic EC key */
/**
* @defgroup EC_KEY_S
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct stECDSA_KEY
* {
*  SEC_UINT32 keyType;
*  EC_PARA_S* pPara;
*  EC_PUB_KEY_S* pPubKey;
*  EC_PRV_KEY_S* pPrvKey;
* }EC_KEY_S;
* @endcode
*
* @datastruct keyType Public or private or pair.
* @datastruct pPara Optional parameters.
* @datastruct pPubKey Pointer to the ECDSA public key structure.
* @datastruct pPrvKey Pointer to the ECDSA private key structure.
*
*/
typedef struct stECDSA_KEY
{
    SEC_UINT32 keyType;         /* public or private or pair */
    EC_PARA_S* pPara;           /* EC params structure */
    EC_PUB_KEY_S* pPubKey;     /* pointer to the ECDSA public key structure */
    EC_PRV_KEY_S* pPrvKey;     /* pointer to the ECDSA private key structure */
} EC_KEY_S;

/* ECDSA key */
typedef EC_PUB_KEY_S ECDSA_PUB_KEY_S;
typedef EC_PRV_KEY_S ECDSA_PRV_KEY_S;
typedef EC_KEY_S ECDSA_KEY_S;

/* ECDH key */
typedef EC_PUB_KEY_S ECDH_PUB_KEY_S;
typedef EC_PRV_KEY_S ECDH_PRV_KEY_S;
typedef EC_KEY_S ECDH_KEY_S;

/*
    Func Name:  IPSI_CRYPT_rsaBlindingAndConstTimeOff
*/

/**
* @defgroup IPSI_CRYPT_rsaBlindingAndConstTimeOff
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_VOID IPSI_CRYPT_rsaBlindingAndConstTimeOff();
* @endcode
*
* @par Purpose
* This is used to switch off the RSA blinding feature and constant time
* operations which helps in improving the RSA performance.
* By default, this feature is not disabled.
*
* @par Description
* IPSI_CRYPT_rsaBlindingAndConstTimeOff switch off the RSA blinding feature and
* constant time operations.
*
* @par Parameters
* N/A
*
* @retval
* N/A
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* RSA blinding feature is to avoid timing attacks on RSA. Before switching
* off this feature, user should consider the possibilities of this attack
* in their scenario.
*       
* @par Related Topics
* IPSI_CRYPT_rsaBlindingAndConstTimeOn
*/
CRYPTOLINKDLL SEC_VOID IPSI_CRYPT_rsaBlindingAndConstTimeOff();

/*
    Func Name:  IPSI_CRYPT_rsaBlindingAndConstTimeOn
*/

/**
* @defgroup IPSI_CRYPT_rsaBlindingAndConstTimeOn
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_VOID IPSI_CRYPT_rsaBlindingAndConstTimeOn();
* @endcode
*
* @par Purpose
* This is used to switch on the RSA blinding feature and constant time
* operations. No need to call this function if user does not disable this
* feature using API IPSI_CRYPT_rsaBlindingAndConstTimeOff.
*
* @par Description
* IPSI_CRYPT_rsaBlindingAndConstTimeOn switches on the RSA blinding feature and
* constant time operations.
*
* @par Parameters
* N/A
*
* @retval
* N/A

* @par Required Header File
* sec_crypto.h
*
* @par Note
* No need to call this function if user does not disable this feature using API
* IPSI_CRYPT_rsaBlindingAndConstTimeOff.
*
* @par Related Topics
* IPSI_CRYPT_rsaBlindingAndConstTimeOff
*/
CRYPTOLINKDLL SEC_VOID IPSI_CRYPT_rsaBlindingAndConstTimeOn();

/*
    Func Name:  CRYPT_privKeyEncrypt
*/

/** 
* @defgroup CRYPT_privKeyEncrypt
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_privKeyEncrypt(
* SEC_PKEY_S* pkey,
* SEC_UCHAR*  pucPlainText,
* SEC_UINT32  ulPlainLen,
* SEC_UINT32  ulPadding,
* SEC_UCHAR*  pucCipherText,
* SEC_UINT32* pulCLen);
* @endcode
*
* @par Purpose
* This is used to perform a private key encryption operation.
*
* @par Description
* CRYPT_privKeyEncrypt function performs a private key 
* encryption operation. The key passed to the function must be a
* private key or a key pair. The data size must not exceed size of key and
* for padding modes PKCS1 - Type1 (Default padding mode) data size must be < (key size - 11 bytes) and 
* for No padding data size should be equal or less than the key size. Supported padding modes are 
* PKCS1 (Type1), No padding and Default Padding. Default Padding will be PKCS1 (Type1) padding.
* @param[in] pKey Private key to be used [N/A]
* @param[in] pucPlainText Data buffer [N/A]
* @param[in] ulPlainLen Data buffer length [N/A]
* @param[in] ulPadding Padding mode used [N/A]
* @param[out] pucCipherText Encrypted data buffer [N/A]
* @param[out] pulCLen Encrypted data buffer length [N/A]
*
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid Arguments [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Key size not supported [SEC_ERR_INVALID_KEY_LEN|N/A]
* @retval SEC_UINT32 Invalid Key [SEC_CRYPT_ERR_INVALID_PKEY|N/A]
* @retval SEC_UINT32 Key is neither Pair nor private
[SEC_CRYPT_ERR_INVALID_PKEY_TYPE|N/A]
* @retval SEC_UINT32 Data size larger than key 
[SEC_CRYPT_ERR_LARGE_DATA_SIZE|N/A]
* @retval SEC_UINT32 Undefined padding mode 
[SEC_CRYPT_ERR_UNDEFINED_PADDING|N/A]
* @retval SEC_UINT32 If operation cannot be
performed on key [SEC_CRYPT_ERR_UNDEFINED_KEY_OPERATION|N/A]
* @retval SEC_UINT32 Library not initialized [SEC_ERR_INITLIB|N/A]
* @retval SEC_UINT32 Incorrect Algorithm ID [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 On Failure [SEC_ERR|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* - pucCipherText buffer size should be equal to or greater than the key size in bytes.
*    CRYPT_PKEY_size can be used to get the key size.
* - In case of no padding, if the data size is less than the key size then zero will be prepended to the data 
      to create the data size equal to key size.
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_privKeyEncrypt(SEC_PKEY_S *pKey, SEC_UCHAR *pucPlainText,
                                              SEC_UINT32 ulPlainLen, SEC_UINT32 ulPadding,
                                              SEC_UCHAR *pucCipherText, SEC_UINT32 *pulCLen);

/*
    Func Name:  CRYPT_pubKeyDecrypt
*/

/** 
* @defgroup CRYPT_pubKeyDecrypt
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_pubKeyDecrypt (
* SEC_PKEY_S* pkey,
* SEC_UCHAR*  pucCipherText,
* SEC_UINT32  ulCipherLen,
* SEC_UINT32  ulPadding,
* SEC_UCHAR*  pucPlainText,
* SEC_UINT32* pulPLen);
* @endcode
*
* @par Purpose
* This is used to perform a public key decryption operation.
*
* @par Description
* CRYPT_pubKeyDecrypt function performs a public key 
* decryption operation. The key must be a public key or a key pair. Supported padding modes are 
* PKCS1 (Type1), No padding and Default Padding. Default Padding will be PKCS1 (Type1) padding.
*
* @param[in] pKey Public key to be used [N/A]
* @param[in] pucCipherText Cipher buffer [N/A]
* @param[in] ulCipherLen Cipher buffer length [N/A]
* @param[in] ulPadding Padding mode used [N/A]
* @param[out] pucPlainText Data buffer [N/A]
* @param[out] pulPLen Data buffer length [N/A]
*
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid Arguments [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Key size not supported [SEC_ERR_INVALID_KEY_LEN|N/A]
* @retval SEC_UINT32 Invalid Key [SEC_CRYPT_ERR_INVALID_PKEY|N/A]
* @retval SEC_UINT32 Key is neither Pair nor Public
[SEC_CRYPT_ERR_INVALID_PKEY_TYPE|N/A]
* @retval SEC_UINT32 Data size larger than key 
[SEC_ERR_DATA_GREATER_THAN_KEY_LEN|N/A]
* @retval SEC_UINT32 Undefined padding mode 
[SEC_CRYPT_ERR_UNDEFINED_PADDING|N/A]
* @retval SEC_UINT32 If operation cannot be
performed on key [SEC_CRYPT_ERR_UNDEFINED_KEY_OPERATION|N/A]
* @retval SEC_UINT32 Library not initialized [SEC_ERR_INITLIB|N/A]
* @retval SEC_UINT32 Incorrect Algorithm ID [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 On Failure [SEC_ERR|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* - pucPlainText buffer size should be equal to or greater than the key size in bytes.
*    CRYPT_PKEY_size can be used to get the key size.
* - In case of no padding, the zero bytes which are prepended during CRYPT_privKeyEncrypt will not be removed.
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 CRYPT_pubKeyDecrypt(SEC_PKEY_S *pKey, SEC_UCHAR *pucCipherText, 
                                             SEC_UINT32 ulCipherLen, SEC_UINT32 ulPadding, 
                                             SEC_UCHAR *pucPlainText, SEC_UINT32 *pulPLen);


/*
    Func Name:  CRYPT_sm2GenZ
*/

/** 
* @defgroup CRYPT_sm2GenZ
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_sm2GenZ (
* SEC_UINT32 ulDigestAlg,
* SEC_PKEY_S *pKey,
* SEC_UCHAR *pucId,
* SEC_UINT32 uiIdLen,
* SEC_UCHAR *pucZ,
* SEC_UINT32 *pulZLen);
* @endcode
*
* @par Purpose
* This API is used to generate Z value, based on the Unique User ID,
* Elliptic curve parameters and selected Hash Algorithm.
* The Z - value has to be used later for various SM2 operations.
* Logic to calculate ZA (Read as Z value for user A)
*   ZA = HashAlg (ENTLA || IDA || a || b || xG || yG || xA || yA)
*       ENTLA   - Length of unique user identifier string (optional)
*       IDA     - Unique user identifier string (optional)
*       a		- Coefficient 'a' of the Elliptic Curve equation
*       b		- Coefficient 'b' of the Elliptic Curve equation
*       xG      - X value of base point of the Elliptic Curve
*       yG      - Y value of base point of the Elliptic Curve
*       xA      - X value of public key point on the Elliptic Curve for user A
*       yA      - Y value of public key point on the Elliptic Curve for user A
* @par Description
* CRYPT_sm2GenZ function generates the Z value specific to a user.
*
* @param[in] ulDigestAlg Hash algorithm to be used in Z calculation [N/A]
*       Supports only 256 bit hash algorithms like ALGID_SHA256 and ALGID_SM3.
* @param[in] pKey The (Public) or (Public & Private pair) Key, along with EC parameters [N/A]
* @param[in] pucId Unique ID of the user [N/A]
*       Optional parameter. Pass NULL, if not applicable.
* @param[in] uiIdLen Length of Unique ID of user [N/A]
*       Optional parameter. Pass zero, if unique ID is NULL.
* @param[out] pucZ Z value of the user [N/A]
* @param[out] pulZLen Length of Z value [N/A]
*
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid arguments passed [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Incorrect Algorithm ID [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 Memory allocation failed [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 Mathematical operation failed [SEC_ERR|N/A]
* @retval SEC_UINT32 Invalid pKey passed [SEC_CRYPT_ERR_INVALID_PKEY|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* The size of the buffer pointed by pucZ should be equal to the length 
* returned by the API CRYPT_MD_SIZE(ulDigestAlg)
* \n
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 CRYPT_sm2GenZ(
    SEC_UINT32 ulDigestAlg,
    SEC_PKEY_S *pKey,
    SEC_UCHAR *pucId,
    SEC_UINT32 uiIdLen,
    SEC_UCHAR *pucZ,
    SEC_UINT32 *pulZLen);

/*
    Func Name:  CRYPT_sm2KepInit
*/

/** 
* @defgroup CRYPT_sm2KepInit
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_sm2KepInit(
* CRYPT_SM2_KEP_CTX *ctx,
* SEC_PKEY_S *pKey,
* SEC_UINT32 ulKdfDigestAlg,
* SEC_UINT32 ulHashAlg,
* EC_POINT_S **pR)
* @endcode
*
* @par Purpose
* This function will create the context required for Key exchange protocol and return the elliptic curve point R
* @par Description
* This function will create the context required for Key exchange protocol and return the elliptic curve point R.
* This operation is equivalent to the steps A1-A2 mentioned for user A in the standard. It also takes as input 
* the kdf digest and hash algorithm id which will be used for all kdf and hash operations involved during the 
* key exchange protocol. As per standard if we consider user B point of view, then this function is 
* equivalent to the steps B1-B2.
*
* @param[in] pKey Contains the private key and EC parameters [N/A]
* @param[in] ulKdfDigestAlg Hash algorithm to be used during KDF operation. 
*   ALGID_MD5 and ALGID_MD4 are not valid algorithms for KDF operation [N/A]
* @param[in] ulHashAlg Hash algorithm to be used for hash operation in Key exchange protocol [N/A]
* @param[out] ctx SM2 key exchange protocol context
* @param[out] pR EC point R [N/A]
*
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid arguments passed [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Incorrect Algorithm ID [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 Memory allocation failed [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 Mathematical operation failed [SEC_ERR|N/A]
* @retval SEC_UINT32 Invalid pKey passed [SEC_CRYPT_ERR_INVALID_PKEY|N/A]


* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 CRYPT_sm2KepInit(
    CRYPT_SM2_KEP_CTX *ctx,
    SEC_PKEY_S *pKey,
    SEC_UINT32 ulKdfDigestAlg,
    SEC_UINT32 ulHashAlg,
    EC_POINT_S **pR);


/*
    Func Name:  CRYPT_sm2KepGenKey
*/

/** 
* @defgroup CRYPT_sm2KepGenKey
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_sm2KepGenKey(
* IPSI_SM2_KEP_GENKEY_OP_DATA_S *opData,
* SEC_UCHAR *pucKey,
* SEC_UINT32 ulKeyLen)
* @endcode
*
* @par Purpose
* This function will create the shared secret key using SM2 KEP
* @par Description
* This function will create the shared secret key using SM2 Key Exchange Protocol.
* This operation is equivalent to the steps A4-A8 mentioned for user A in the standard.
* As per standard if we consider user B point of view, then this function is equivalent to the steps B3-B7.
*
* @param[in] opData Contains the input required for Key Generation [N/A]
* @param[in] ulKeyLen Length of the shared key to be generated [N/A]
* @param[out] pucKey Shared key to be generated [N/A]
*
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid arguments passed [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Memory allocation failed [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 Mathematical operation failed [SEC_ERR|N/A]
* @retval SEC_UINT32 Invalid pKey passed [SEC_CRYPT_ERR_INVALID_PKEY|N/A]
* @retval SEC_UINT32 Invalid SM2 KEP context [SEC_CRYPT_ERR_INVALID_CTX|N/A]]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* The size of the buffer pointed by pucKey should be as per ulKeyLen.
* \n
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 CRYPT_sm2KepGenKey(
    IPSI_SM2_KEP_GENKEY_OP_DATA_S *opData,
    SEC_UCHAR *pucKey,
    SEC_UINT32 ulKeyLen);

/*
    Func Name:  CRYPT_sm2KepGenHash
*/

/** 
* @defgroup CRYPT_sm2KepGenHash
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_sm2KepGenHash(
* CRYPT_SM2_KEP_CTX ctx,
* IPSI_SM2_KEP_HASHTYPE_E enHashType,
* SEC_UCHAR *pucS,
* SEC_UINT32 *pulSLen)
* @endcode
*
* @par Purpose
* This function generates the optional hash as mentioned in the standard.
* @par Description
* This function generates the optional hash as mentioned in the standard. 
* If we consider the hash generation of user B, this function is equivalent to the step B8
* and enHashType should be selected as IPSI_SM2_HASH_SB. If we consider the hash generation for user A,
* this function is equivalent to the step A10 and enHashType should be selected as IPSI_SM2_HASH_SA. 
*
* @param[in] ctx Contains the input required for Key Generation [N/A]
* @param[in] enHashType The hash operation to be considered either IPSI_SM2_HASH_SA or IPSI_SM2_HASH_SB [N/A]
* @param[out] pucS Generated hash [N/A]
* @param[out] pulSLen Pointer to the length of generated hash [N/A]
*
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid arguments passed [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Memory allocation failed [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 Mathematical operation failed [SEC_ERR|N/A]
* @retval SEC_UINT32 Invalid SM2 KEP context [SEC_CRYPT_ERR_INVALID_CTX|N/A]]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* The size of the buffer pointed by pucS should be CRYPT_MD_SIZE(ulHashAlg).
* ulHashAlg is the hash algorithm set in the API CRYPT_sm2KepInit
* \n
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 CRYPT_sm2KepGenHash(
    CRYPT_SM2_KEP_CTX ctx,
    IPSI_SM2_KEP_HASHTYPE_E enHashType,
    SEC_UCHAR *pucS,
    SEC_UINT32 *pulSLen);

/*
    Func Name:  CRYPT_sm2KepVerifyHash
*/

/** 
* @defgroup CRYPT_sm2KepVerifyHash
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_sm2KepVerifyHash(
* CRYPT_SM2_KEP_CTX *ctx,
* IPSI_SM2_KEP_HASHTYPE_E enHashType,
* SEC_UCHAR *pucS,
* SEC_UINT32 pulSLen,
* SEC_UINT32 *verifyResult);
* @endcode
*
* @par Purpose
* This function compares the remote hash with the internally generated hash value. 
* @par Description
* This function compares the remote hash with the internally generated hash value
* and returns either success or failure. If we consider hash verification of user A, 
* this function is equivalent to step A9 and enHashType should be selected as IPSI_SM2_HASH_S1.
* If we consider hash verification of user B, this function is equivalent to step B10 
* and enHashType should be selected as IPSI_SM2_HASH_S2.
*
* @param[in] ctx SM2 key exchange protocol context [N/A]
* @param[in] enHashType The hash operation to be considered either IPSI_SM2_HASH_S1 or IPSI_SM2_HASH_S2 [N/A]
* @param[in] pucS Pointer to the hash which needs to be verified [N/A]
* @param[in] ulSLen  Length of the hash to be verified [N/A]
* @param[out] verifyResult  Verification result - whether success or failure.
*   Set to SEC_TRUE if the hash verification is successful.
*   Set to SEC_FALSE if the hash verification is unsuccessful. [N/A]
*
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid arguments passed [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Memory allocation failed [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 Mathematical operation failed [SEC_ERR|N/A]
* @retval SEC_UINT32 Invalid SM2 KEP context [SEC_CRYPT_ERR_INVALID_CTX|N/A]]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 CRYPT_sm2KepVerifyHash(
    CRYPT_SM2_KEP_CTX ctx,
    IPSI_SM2_KEP_HASHTYPE_E enHashType,
    SEC_UCHAR *pucS,
    SEC_UINT32 ulSLen,
    SEC_UINT32 *verifyResult);

/*
    Func Name:  CRYPT_sm2KepRemove
*/

/** 
* @defgroup CRYPT_sm2KepRemove
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* void CRYPT_sm2KepRemove(
* CRYPT_SM2_KEP_CTX *ctx) 
* @endcode
*
* @par Purpose
* Free the memory allocated held in SM2 key exchange protocol context.
* @par Description
* Free the memory allocated held in SM2 key exchange protocol context.
*
* @param[in] ctx Memory to be freed [N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL void CRYPT_sm2KepRemove(
    CRYPT_SM2_KEP_CTX *ctx);

/*
    Func Name:  CRYPT_sm2PkeaGetOutputSize
*/

/** 
* @defgroup CRYPT_sm2PkeaGetOutputSize
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_sm2PkeaGetOutputSize(
* SEC_PKEY_S *pKey,
* SEC_UINT32 ulHashAlg,
* SEC_UINT32 ulMsgLen,
* SEC_UINT32 *pulSizeInBytes)
* @endcode
*
* @par Purpose
* This function returns the size of the output after SM2 PKEA operation.
* @par Description
* This function returns the size of the output after SM2 PKEA operation.
* User need to call this function to obtain the size of the memory which must be allocated for output buffer.
*
* @param[in] pKey Contains the EC public key [N/A]
* @param[in] ulHashAlg Hash algorithm to be used for calculation of C3 during PKEA operation [N/A]
* @param[in] ulPlainLen  Input data length [N/A]
* @param[in] uiCipherType The cipher text consist of C1|| C2 || C3, C1 is a point and the point can
* be encoded as compressed or uncompressed format and the format will be determined by uiCipherType. The
* value of uiCipherType can be SEC_UNCOMPRESSED_CIPHER or SEC_COMPRESSED_CIPHER [N/A]
* @param[out] pulSizeInBytes Size of the output in bytes after PKEA operation [N/A]
*
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid arguments passed [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 EC Key field is not prime or polynomial [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 EC parameter's prime length or degree is zero [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Incorrect Hash Algorithm ID [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 Invalid pKey passed [SEC_CRYPT_ERR_INVALID_PKEY|N/A]
* @retval SEC_UINT32 Message length passed is too large i.e. MAX of SEC_UINT32
* or a value which lead to overflow of the SEC_UINT32 by adding it to the hash size and
* point length [SEC_ERR_INVALID_DATA_LEN|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* While decrypting the encrypted text the plain text length can be taken as cipher text length, 
* the plain text length will always be less than the cipher text length.
* \n
*       
* @par Related Topics
* CRYPT_sm2PkeaEncrypt
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 CRYPT_sm2PkeaGetOutputSize(
    SEC_PKEY_S *pKey,
    SEC_UINT32 ulHashAlg,
    SEC_UINT32 ulMsgLen,
    SEC_UINT32 uiCipherType,
    SEC_UINT32 *pulSizeInBytes);

/*
    Func Name:  CRYPT_sm2PkeaEncrypt
*/

/** 
* @defgroup CRYPT_sm2PkeaEncrypt
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_sm2PkeaEncrypt(
* SEC_PKEY_S *pKey,
* SEC_UINT32 ulKdfDigestAlg,
* SEC_UINT32 ulHashAlg,
* SEC_UCHAR *pucPlainText,
* SEC_UINT32 ulPlainLen,
* SEC_UCHAR *pucCipherText,
* SEC_UINT32 *pulCLen);
* @endcode
*
* @par Purpose
* This function encrypts the input plaintext as per SM2 PKEA standard.
* @par Description
* This function encrypts the input plaintext as per SM2 PKEA standard.
* It takes as input the EC public key and digest algorithm used during kdf calculation
* and the hash algorithm used for calculation of C3.
*
* @param[in] pKey Contains the EC public key [N/A]
* @param[in] ulKdfDigestAlg Hash algorithm to be used during KDF operation [N/A]
* @param[in] ulHashAlg Hash algorithm to be used for calculation of C3 [N/A]
* @param[in] pucPlainText Pointer to input data to be encrypted [N/A]
* @param[in] ulPlainLen Input data buffer length [N/A]
* @param[in] uiCipherType The cipher text consist of C1|| C2 || C3, C1 is a point and the point can
* be encoded as compressed or uncompressed format and the format will be determined by uiCipherType. The
* value of uiCipherType can be SEC_UNCOMPRESSED_CIPHER or SEC_COMPRESSED_CIPHER [N/A]
* @param[out] pucCipherText  Pointer to the output encrypted data buffer [N/A]
* @param[out] pulCLen Pointer to the encrypted data length [N/A]
*
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid arguments passed [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Memory allocation failed [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 Incorrect Hash Algorithm ID [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 Invalid Key [SEC_CRYPT_ERR_INVALID_PKEY|N/A]
* @retval SEC_UINT32 Mathematical operation failed [SEC_ERR|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* -The size of the buffer pointed to by pucCipherText, should be atleast equal to the 
*    size returned by the API CRYPT_sm2PkeaGetOutputSize.
* - ALGID_MD5 is not a valid algorithm for ulKdfDigestAlg
* - ALGID_MD4 is not a valid algorithm for ulHashAlg and ulKdfDigestAlg
*
* \n
*       
* @par Related Topics
* CRYPT_sm2PkeaGetOutputSize
* CRYPT_sm2PkeaDecrypt
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 CRYPT_sm2PkeaEncrypt(
    SEC_PKEY_S *pKey,
    SEC_UINT32 ulKdfDigestAlg,
    SEC_UINT32 ulHashAlg,
    SEC_UCHAR *pucPlainText,
    SEC_UINT32 ulPlainLen,
    SEC_UINT32 uiCipherType,
    SEC_UCHAR *pucCipherText,
    SEC_UINT32 *pulCLen);

/*
    Func Name:  CRYPT_sm2PkeaDecrypt
*/

/** 
* @defgroup CRYPT_sm2PkeaDecrypt
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_sm2PkeaDecrypt(
* SEC_PKEY_S *pKey,  
* SEC_UINT32 ulKdfDigestAlg,
* SEC_UINT32 ulHashAlg,
* SEC_UCHAR *pucCipherText, 
* SEC_UINT32 ulCipherLen, 
* SEC_UCHAR *pucPlainText, 
* SEC_UINT32 *pulPLen);
* @endcode
*
* @par Purpose
* This function decrypts the cipher text as per SM2 PKEA standard.
* @par Description
* This function decrypts the cipher text as per SM2 PKEA standard.
* It takes as input the EC public key and digest algorithm used during kdf calculation
* and the hash algorithm used for calculation of C3.
*
* @param[in] pKey Contains the EC public key [N/A]
* @param[in] ulKdfDigestAlg Hash algorithm to be used during KDF operation [N/A]
* @param[in] ulHashAlg Hash algorithm to be used for calculation of C3 [N/A]
* @param[in] pucCipherText Pointer to the input cipher text [N/A]
* @param[in] ulCipherLen Input cipher text length [N/A]
* @param[out] pucPlainText  Pointer to the decrypted data buffer [N/A]
* @param[out] pulPLen Pointer to decrypted data length [N/A]
*
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid arguments passed [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Memory allocation failed [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 Incorrect Hash Algorithm ID [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 Invalid Key [SEC_CRYPT_ERR_INVALID_PKEY|N/A]
* @retval SEC_UINT32 Mathematical operation failed [SEC_ERR|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* - The size of the buffer pointed to by pucPlainText, should be atleast equal to ulCipherLen.
* - ALGID_MD5 is not a valid algorithm for ulKdfDigestAlg
* - ALGID_MD4 is not a valid algorithm for ulHashAlg and ulKdfDigestAlg
* \n
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 CRYPT_sm2PkeaDecrypt(
    SEC_PKEY_S *pKey,  
    SEC_UINT32 ulKdfDigestAlg,
    SEC_UINT32 ulHashAlg,
    SEC_UCHAR *pucCipherText, 
    SEC_UINT32 ulCipherLen, 
    SEC_UCHAR *pucPlainText, 
    SEC_UINT32 *pulPLen);

/*
    Func Name:  CRYPT_checkECKey
*/

/** 
* @defgroup CRYPT_checkECKey
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_checkECKey(
* const SEC_PKEY_S *ecKey);
* 
* @endcode
*
* @par Purpose
* This function checks whether the EC key is valid. 
* @par Description
* This function checks the whether the EC key is valid. It checks the following:
*    Public Key is on the elliptic curve. 
*    Public Key * Order is point at infinity.
*    Base Point * Private Key is Public Key.
*
* @param[in] ecKey Input key contains either public key or key pair [N/A]
*
* @retval SEC_UINT32 Key verification is successful [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Memory allocation failed [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 Key verification failed [SEC_ERR|N/A]
* @retval SEC_UINT32 Invalid Key type [SEC_CRYPT_ERR_INVALID_PKEY|N/A]
* @retval SEC_UINT32 Invalid arguments passed [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 CRYPT_checkECKey(const SEC_PKEY_S *ecKey);

/*
    Func Name:  CRYPT_createECParamsById_ex
*/

/**
* @defgroup CRYPT_createECParamsById_ex
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* EC_PARA_S *CRYPT_createECParamsById_ex(
* SEC_UINT32 uiParamID);
* @endcode
*
* @par Purpose
* This is used to get the param structure along with the co-factor for a given
well-known parameter Id.
*
* @par Description
* CRYPT_createECParamsById_ex function gets the param structure
* for a given well-known parameter Id. The parameters returned will contain
* all the parameter including the cofactor and should be freed by user by using IPSI_EC_PARA_FREE.
*
* @param[in] uiParamID The id of the well-known parameters [N/A]
*
* @retval EC_PARA_S* On error [0|N/A]
* @retval EC_PARA_S* Otherwise [The parameter structure 
corresponding to id|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
* Returned pointer has to be freed by the application using IPSI_EC_PARA_FREE.
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL EC_PARA_S *CRYPT_createECParamsById_ex(
    SEC_UINT32      uiParamID);

/*
    Func Name:  CRYPT_computeECDHKey_ex
*/

/**
* @defgroup CRYPT_computeECDHKey_ex
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_computeECDHKey_ex(
*   SEC_PKEY_S *pPvtKey,
*   SEC_PKEY_S *pPubKey,
*   SEC_UCHAR *pucKey,
*   SEC_UINT32 *pulKeyLen,
*   IPSI_ECDH_PRIMITIVE_E uiEcdhPrimitive);
* @endcode
*
* @par Purpose
* This function is used to generate a ECDH shared secret key. 
* This function supports both Elliptic Curve Standard and Modified (cofactor) Diffie Hellman Primitive.
*
* @par Description
* This function is an extenstion to CRYPT_computeECDHKey. This function generates a ECDH shared secret key 
* from private key and peer public key. The memory for the shared secret must have been allocated prior to calling.
* Based on the enum value passed to uiEcdhPrimitive, this function generates shared secret key using 
* either standard or modified Diffie Hellman primitive.
* In the EC Standard DH primitive, cofactor is not required and pCoFactor in EC_PARA_S is ignored.
* In the EC Modified (cofactor) DH primitive, pCoFactor value present in EC_PARA_S is considered 
* and error is returned if pCoFactor is set to NULL. 
*
* @param[in] pPvtKey Own private key [N/A]
* @param[in] pPubKey Peer public key [N/A]
* @param[out] pucKey Shared secret key [N/A]
* @param[out] pulKeyLen Length of generated shared secret key [N/A]
* @param[in] uiEcdhPrimitive Identifies the ECDH primitive to be used whether EC Standard DH Primitive or 
*   EC Modified (Cofactor) DH Primitive [N/A]
*
* @retval SEC_UINT32 On Success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid Key [SEC_CRYPT_ERR_INVALID_PKEY|N/A]
* @retval SEC_UINT32 Invalid Arguments [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If library is not initialized [SEC_ERR_INITLIB|N/A]
* @retval SEC_UINT32 Incorrect Algorithm ID i.e. Key type is not ALGID_ECDH or ALGID_ECDSA or
* ALGID_ECKEY [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 Memory allocation failed [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 On other errors [SEC_ERR|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
*   - The minimum size of output key buffer should be atleast the input public key size.
* \n
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 CRYPT_computeECDHKey_ex(
    SEC_PKEY_S *pPvtKey,
    SEC_PKEY_S *pPubKey,
    SEC_UCHAR *pucKey,
    SEC_UINT32 *pulKeyLen,
    IPSI_ECDH_PRIMITIVE_E uiEcdhPrimitive);

/*
    Func Name:  CRYPT_PKEY_sign_size
*/

/**
* @defgroup CRYPT_PKEY_sign_size
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_PKEY_sign_size(SEC_PKEY_S* pKey);
* @endcode
*
* @par Purpose
* This function is used to get the maximum signature size for the key passed.
*
* @par Description
* This function is used to get the maximum signature size for the key passed.
*
* @param[in] pKey Key to be used [N/A]
*
* @retval SEC_UINT32 The maximum signature size for the key passed [Size of signature|N/A]
* @retval SEC_UINT32 If undefined algorithm [0|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* \n
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_PKEY_sign_size(SEC_PKEY_S* pKey);


/**
* @defgroup IPSI_SYM_CIPHER_DIRECTION_E
* @ingroup sec_cryptoEnum
* @par Prototype
* @code
* typedef enum enSymCipherDirection
* {
*     IPSI_SYM_CIPHER_ENCRYPT,
*     IPSI_SYM_CIPHER_DECRYPT
* } IPSI_SYM_CIPHER_DIRECTION_E;
* @endcode
*
* @dataenum IPSI_SYM_CIPHER_ENCRYPT Identifies that data provided is for encryption.
* @dataenum IPSI_SYM_CIPHER_DECRYPT Identifies that data provided is for decryption.
*/
typedef enum enSymCipherDirection
{
    IPSI_SYM_CIPHER_ENCRYPT,
    IPSI_SYM_CIPHER_DECRYPT
} IPSI_SYM_CIPHER_DIRECTION_E;



/* Enum to indicate whether data is complete or partial. User to decide to output tag or not. */


/**
* @defgroup IPSI_SYM_DATATYPE_E
* @ingroup sec_cryptoEnum
* @par Prototype
* @code
* typedef enum enAeadDataType
* {
*     IPSI_SYM_DATA_TYPE_FULL,
*     IPSI_SYM_DATA_TYPE_PARTIAL,
*     IPSI_SYM_DATA_TYPE_LAST_PARTIAL
* }IPSI_SYM_DATATYPE_E;
* @endcode
*
* @dataenum IPSI_SYM_DATA_TYPE_FULL Identifies that data provided to encryption/decryption operation is FULL and
*                                               in case of AEAD opertions, provides tag result in the same operation.
* @dataenum IPSI_SYM_DATA_TYPE_PARTIAL Identifies that data provided to encryption/decryption operation is partial
*                                                   and in case of AEAD operations, does not provide the tag result.
* @dataenum IPSI_SYM_DATA_TYPE_LAST_PARTIAL Identifies that call to encryption/decryption operation is final and
*                                                               in case of AEAD operations, provides the tag result.
*/
typedef enum enSymDataType
{
    IPSI_SYM_DATA_TYPE_FULL, // return hash result immediately
    IPSI_SYM_DATA_TYPE_PARTIAL, // do not return hash result, and maintain the hash state internal
    IPSI_SYM_DATA_TYPE_LAST_PARTIAL // the call to aeadOp contains the final data and therefore return the hash
}IPSI_SYM_DATATYPE_E;


/**
* @defgroup IPSI_AEAD_SETUP_DATA_S
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct stAEADSessionSetUpData
* {
*     SEC_UINT32 uiAEADAlgID;
*     IPSI_SYM_CIPHER_DIRECTION_E uiAEADDirection;
*     SEC_UCHAR *pucKey;
*     SEC_UINT32 uiKeyLen;
*     SEC_UCHAR *pCipherSetupData;
* }IPSI_AEAD_SETUP_DATA_S;
* @endcode
*
* @datastruct uiAEADAlgID AEAD algorithm ID. Supported algorithms are ALGID_AES128_GCM,
*                                    ALGID_AES192_GCM & ALGID_AES256_GCM.
* @datastruct uiAEADDirection Identifies the cipher direction whether encryption or decryption.
*                  Supported values are IPSI_SYM_CIPHER_ENCRYPT and IPSI_SYM_CIPHER_DECRYPT.
* @datastruct pucKey Pointer to the key structure used in AEAD operations.
* @datastruct uiKeyLen Key length.
* @datastruct pCipherSetupData No use for now. Added for future extensability.
*
*/
typedef struct stAEADSessionSetUpData
{
    SEC_UINT32 uiAEADAlgID;
    IPSI_SYM_CIPHER_DIRECTION_E uiAEADDirection;
    SEC_UCHAR *pucKey;
    SEC_UINT32 uiKeyLen;
    SEC_VOID *pCipherSetupData;
}IPSI_AEAD_SETUP_DATA_S;



/**
* @defgroup IPSI_AEAD_OP_DATA_S
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct stAeadOpData
* {
*     CRYPT_AEAD_CTX ctx;
*     IPSI_SYM_DATATYPE_E enDataType;
*     SEC_UCHAR *pucIV;
*     size_t uiIvLen;
*     SEC_UCHAR *pucAad;
*     size_t uiAadLen;
*     SEC_UCHAR *pCipherOpData;
* }IPSI_AEAD_OP_DATA_S;
* @endcode
*
* @datastruct ctx Pointer to the AEAD session context.
* @datastruct enDataType Identifies the data type whether FULL or PARTIAL.
* @datastruct pucIV Pointer to the Initialization Vector used in AEAD operations.
* @datastruct uiIvLen Initialization Vector length.
* @datastruct pucAad Pointer to Associated Authentication Data used in AEAD operations.
* @datastruct uiAadLen AAD length.
* @datastruct pCipherOpData No use for now. Added for future extensability.
*
*/
typedef struct stAeadOpData
{
    CRYPT_AEAD_CTX ctx;
    IPSI_SYM_DATATYPE_E enDataType;
    SEC_UCHAR *pucIV;
    size_t uiIvLen;
    SEC_UCHAR *pucAad;
    size_t uiAadLen;
    SEC_VOID *pCipherOpData;
}IPSI_AEAD_OP_DATA_S;


/* Supported authentication tag lengths for AES GCM */
/**
* @defgroup IPSI_AEAD_TAG_LEN_E
* @ingroup sec_cryptoEnum
* @par Prototype
* @code
* typedef enum
* {
*     IPSI_AEAD_TAG_LEN_32 = 4,
*     IPSI_AEAD_TAG_LEN_64 = 8,
*     IPSI_AEAD_TAG_LEN_96 = 12,
*     IPSI_AEAD_TAG_LEN_104 = 13,
*     IPSI_AEAD_TAG_LEN_112 = 14,
*     IPSI_AEAD_TAG_LEN_120 = 15,
*     IPSI_AEAD_TAG_LEN_128 = 16,
* } IPSI_AEAD_TAG_LEN_E;
* @endcode
*
* @dataenum IPSI_AEAD_TAG_LEN_32 Identifies tag length of 4 bytes.
* @dataenum IPSI_AEAD_TAG_LEN_64 Identifies tag length of 8 bytes.
* @dataenum IPSI_AEAD_TAG_LEN_96 Identifies tag length of 12 bytes.
* @dataenum IPSI_AEAD_TAG_LEN_104 Identifies tag length of 13 bytes.
* @dataenum IPSI_AEAD_TAG_LEN_112 Identifies tag length of 14 bytes.
* @dataenum IPSI_AEAD_TAG_LEN_120 Identifies tag length of 15 bytes.
* @dataenum IPSI_AEAD_TAG_LEN_128 Identifies tag length of 16 bytes.
*/

typedef enum
{
    IPSI_AEAD_TAG_LEN_32 = 4,
    IPSI_AEAD_TAG_LEN_64 = 8,
    IPSI_AEAD_TAG_LEN_96 = 12,
    IPSI_AEAD_TAG_LEN_104 = 13,
    IPSI_AEAD_TAG_LEN_112 = 14,
    IPSI_AEAD_TAG_LEN_120 = 15,
    IPSI_AEAD_TAG_LEN_128 = 16

} IPSI_AEAD_TAG_LEN_E;



/*
    Func Name:  IPSI_CRYPT_dhConstTimeOn
*/

/**
* @defgroup IPSI_CRYPT_dhConstTimeOn
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_VOID IPSI_CRYPT_dhConstTimeOn();
* @endcode
*
* @par Purpose
* This is used to switch on the DH constant time operations.
* No need to call this function if user does not disable this
* feature using API IPSI_CRYPT_dhConstTimeOff.
*
* @par Description
* IPSI_CRYPT_dhConstTimeOn switches on the DH constant time operations.
*
* @par Parameters
* N/A
*
* @retval
* N/A

* @par Required Header File
* sec_crypto.h
*
* @par Note
* - No need to call this function if user does not disable this feature using API
*     IPSI_CRYPT_dhConstTimeOff.
* - It is global function, application need to make sure that the function will not be called in parallel
*    with IPSI_CRYPT_dhConstTimeOff, CRYPT_computeDHKey and CRYPT_genKey for DH keys
*
* @par Related Topics
* IPSI_CRYPT_dhConstTimeOff
*/
CRYPTOLINKDLL SEC_VOID IPSI_CRYPT_dhConstTimeOn(SEC_VOID);


/*
    Func Name:  IPSI_CRYPT_dhConstTimeOff
*/

/**
* @defgroup IPSI_CRYPT_dhConstTimeOff
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_VOID IPSI_CRYPT_dhConstTimeOff();
* @endcode
*
* @par Purpose
* This is used to switch off the DH constant time operations. By default DH constant time operation is enabled.
*
* @par Description
* IPSI_CRYPT_dhConstTimeOff switches off the DH constant time operations.
*
* @par Parameters
* N/A
*
* @retval
* N/A

* @par Required Header File
* sec_crypto.h
*
* @par Note
* - It is global function, application need to make sure that the function will not be called in parallel
*    with IPSI_CRYPT_dhConstTimeOn, CRYPT_computeDHKey and CRYPT_genKey for DH keys
*
* @par Related Topics
* IPSI_CRYPT_dhConstTimeOn
*/
CRYPTOLINKDLL SEC_VOID IPSI_CRYPT_dhConstTimeOff(SEC_VOID);



/** 
* @defgroup IPSI_ECP_CB
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* typedef SEC_INT (*IPSI_ECP_CB) (SEC_VOID*);
*
* @endcode
*
* @par Purpose
* Callback function called from EC prime operations.
*
* @par Description
* This function is called from EC prime operations like EC signing, computing ECDH key, while doing SM2 operations.
* In all the cases the curve of the key should be of Prime type
* The first parameter to callback function is 
* reserved for future use. Currently the return value from the callback function
* is ignored and intended only for future use.
* 
*
* @retval SEC_INT32 Currently Nothing to be returned [N/A|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* N/A
* 
* @par Related Topics
* IPSI_CRYPT_setEcpCallback
*/
typedef SEC_INT (*IPSI_ECP_CB) (SEC_VOID*);


/*
    Func Name:  IPSI_CRYPT_setEcpCallback
*/

/**
* @defgroup IPSI_CRYPT_setEcpCallback
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 IPSI_CRYPT_setEcpCallback (IPSI_ECP_CB pCB, SEC_UINT32 lTimeOut,
*                                                     IPSI_AUX_PAR_S *pstAux);
* @endcode
*
* @par Purpose
* This function is used to set the callback function for EC prime multiplication and its timeout value.
*
* @par Description
* IPSI_CRYPT_setEcpCallback will be called at the time of EC prime multiplication (if the timeout is occurred).
* For binary curves this feature is not supported.
*
* @param[in] pCB Callback function which will be called at when the timer expires [N/A]
* @param[in] lTimeOut Timeout value in ticks. If the timeout value is more than LONG_MAX then API will return
* error SEC_ERR_INVALID_ARG. It is recommended to provide the timeout value little less than
* the expected timeout. ex: If the timeout is needed after 100 ticks then set the timeout value less than 60 ticks.
* It should be checked by the application that what timeout value suites their system.[N/A]
* @param[in] pstAux  Auxiliary parameter, reserved for future use. Currently NULL can be passed to this parameter. [N/A]
*
* @retval SEC_UINT32 On success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 lTimeOut is greater than LONG_MAX [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 lTimeOut is zero and  pCB is not NULL [SEC_ERR_INVALID_ARG|N/A]

* @par Required Header File
* sec_crypto.h
*
* @par Note
* - It is a global function, application need to make sure that the function will not be called in parallel
*    with the EC operations over the prime curves.
* - To remove the timeout callback, application need to pass the pCB as NULL.
* - NULL function pointer with some timeout value is a valid input to this API. It will remove the callback
*    function call.
*
* @par Related Topics
* 
*/
CRYPTOLINKDLL SEC_UINT32 IPSI_CRYPT_setEcpCallback (IPSI_ECP_CB pCB, SEC_UINT32 lTimeOut,
                                                     IPSI_AUX_PAR_S *pstAux);



/** 
* @defgroup IPSI_BN_CB
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* typedef SEC_INT (*IPSI_BN_CB) (SEC_VOID*);
*
* @endcode
*
* @par Purpose
* Callback function called from BN operations.
*
* @par Description
* This function is called from BN operations like while computing the DH keys,generating the DH keys.
* The first parameter to callback function is 
* reserved for future use. Currently the return value from the callback function
* is ignored and intended only for future use.
* 
*
* @retval SEC_INT32 Currently Nothing to be returned [N/A|N/A]
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* N/A
* 
* @par Related Topics
* IPSI_CRYPT_setBnCallback
*/
typedef SEC_INT (*IPSI_BN_CB) (SEC_VOID*);


/*
Func Name:  IPSI_CRYPT_setBnCallback
*/

/**
* @defgroup IPSI_CRYPT_setBnCallback
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 IPSI_CRYPT_setBnCallback (IPSI_BN_CB pCB, SEC_UINT32 lTimeOut, IPSI_AUX_PAR_S *pstAux);
* @endcode
*
* @par Purpose
* This function is used to set the callback function for BN operations and its timeout value.
*
* @par Description
* IPSI_CRYPT_setBnCallback will be called at the time of BN operations (if the timeout is occurred)
*
* @param[in] pCB Callback function which will be called at when the timer expires [N/A]
* @param[in] lTimeOut Timeout value in ticks. If the timeout value is more than LONG_MAX then API will return
* error SEC_ERR_INVALID_ARG. It is recommended to provide the timeout value little less than
* the expected timeout. ex: If the timeout is needed after 100 ticks then set the timeout value less than 60 ticks.
* It should be checked by the application that what timeout value suites their system.[N/A]
* @param[in] pstAux  Auxiliary parameter, reserved for future use. Currently NULL can be passed to this parameter. [N/A]
*
* @retval SEC_UINT32 On success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 lTimeOut is greater than LONG_MAX [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 lTimeOut is zero and  pCB is not NULL [SEC_ERR_INVALID_ARG|N/A]

* @par Required Header File
* sec_crypto.h
*
* @par Note
* - It is a global function, application need to make sure that the function will not be called in parallel.
* - To remove the timeout callback, application need to pass the pCB as NULL.
* - NULL function pointer with some timeout value is a valid input to this API. It will remove the callback
*    function call.
*
* @par Related Topics
* N/A
* 
*/
CRYPTOLINKDLL SEC_UINT32 IPSI_CRYPT_setBnCallback (IPSI_BN_CB pCB, SEC_UINT32 lTimeOut, IPSI_AUX_PAR_S *pstAux);


/*
    Func Name:  CRYPT_aeadInitSession
*/

/**
* @defgroup CRYPT_aeadInitSession
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_aeadInitSession(CRYPT_AEAD_CTX *ctx, IPSI_AEAD_SETUP_DATA_S *pstSetUpInfo,
*                                                  IPSI_AUX_PAR_S *pstAuxPar);
* @endcode
*
* @par Purpose
* This is used to initialize the AEAD session context structure.
*
* @par Description
* CRYPT_aeadInitSession used to initialize the AEAD session context structure with the algorithm, key, key length
* and cipher direction (encrypt or decrypt). Supported ciphers are ALGID_AES128_GCM,
* ALGID_AES192_GCM & ALGID_AES256_GCM.
*
* @param[in]  ctx Pointer to AEAD session context [N/A]
* @param[in]  pstSetUpInfo Pointer to AEAD initialization information [N/A]
* @param[in]  pstAuxPar Pass as SEC_NULL. Additional variable for future extensibility [N/A]
*
* @retval SEC_UINT32 Invalid argument [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Invalid algorithm identifier [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 Memory allocation failure [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 Invalid key length [SEC_ERR_INVALID_KEY_LEN|N/A]

* @par Required Header File
* sec_crypto.h
*
* @par Note
* 
* - SEC_ERR_INVALID_ARG will be returned if:
*    - Input arguments are NULL.
*    - Input key is NULL.
*    - Invalid direction (other than IPSI_SYM_CIPHER_ENCRYPT and IPSI_SYM_CIPHER_DECRYPT for AEAD direction
*       in setup information)
* - Padding is not applicable to AES GCM algorithms as there is no restriction on block size for AES GCM algorithm.
* Even if padding mode is set to algorithm id, it will be ignored.
* - SEC_ERR_INVALID_ALGID will be returned if:
*    - Ig algorithm ID passed is other than ALGID_AES128_GCM, ALGID_AES192_GCM & ALGID_AES256_GCM.
* - SEC_ERR_INVALID_KEY_LEN will be returned if key length passed is not matching with expected key length.
* For ALGID_AES128_GCM, the key length should be 16 bytes, for ALGID_AES192_GCM, the key length should be 24 bytes,
* for ALGID_AES256_GCM, the key length should be 32 bytes.
* 
* @par Related Topics
* CRYPT_aeadOp \n
* CRYPT_aeadRemoveSession
*/
CRYPTOLINKDLL SEC_UINT32 CRYPT_aeadInitSession(CRYPT_AEAD_CTX *ctx, IPSI_AEAD_SETUP_DATA_S *pstSetUpInfo,
                                                                                        IPSI_AUX_PAR_S *pstAuxPar);


/* Encryption / decryption operation using AEAD algorithm. */

/*
    Func Name:  CRYPT_aeadOp
*/

/**
* @defgroup CRYPT_aeadOp
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_aeadOp(
* IPSI_AEAD_OP_DATA_S *pstOpData,
* SEC_UCHAR *pucInData,
* size_t ulInDataLen,
* SEC_UCHAR *pucOutData,
* size_t *pulOutDataLen,
* SEC_UCHAR *pucHashResult,
* SEC_UINT32 ulHashResultLen,
* IPSI_AUX_PAR_S *pstAuxPar);
* @endcode
*
* @par Purpose
* Used to do encryption / decryption operation on AEAD algorithms.
*
* @par Description
* CRYPT_aeadOp used to do encryption / decryption operation. In case of encryption,
* both encrypted data and authentication tag will be generated by this function. In case
* of decryption, it takes encrypted data, authentication tag as input and outputs decrypted
* text only when both decryption and tag verification are success.
*
* @param[in]  pstOpData Pointer to AEAD operation data which holds information
*                                 required for encryption / decryption [N/A]
* @param[in]  pucInData Pointer to input data for encryption / decryption operation [N/A]
* @param[in]  ulInDataLen Input data length [N/A]
* @param[out]  pucOutData Pointer to output data [N/A]
* @param[out]  pulOutDataLen Pointer to output data length [N/A]
* @param[in]  pucHashResult Pointer to hold authentication tag in case of encryption and input
*                                      authentication tag in case of decryption[N/A]
* @param[in]  ulHashResultLen Desired authentication tag length [N/A]
* @param[in]  pstAuxPar Pass as SEC_NULL. Additional variable for future extensibility [N/A]
*
* @retval SEC_UINT32 Invalid argument [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Invalid IV length [SEC_ERR_INVALID_IV_LEN|N/A]
* @retval SEC_UINT32 Invalid tag length [SEC_CRYPT_ERR_INVALID_TAG_LEN|N/A]
* @retval SEC_UINT32 IV length exceeds maximum limit [SEC_CRYPT_ERR_IV_LEN_EXCEED_MAXLIMIT|N/A]
* @retval SEC_UINT32 AAD length exceeds maximum limit [SEC_CRYPT_ERR_AAD_LEN_EXCEED_MAXLIMIT|N/A]
* @retval SEC_UINT32 Trying to set AAD after encryption/decryption operation
*                              [SEC_CRYPT_ERR_SET_AAD_AFTER_CIPHER_OPERATION|N/A]
* @retval SEC_UINT32 Set IV failed [SEC_CRYPT_ERR_AEAD_SET_IV_FAILED|N/A]
* @retval SEC_UINT32 Data for encryption/decryption exceeds maximum limit [SEC_CRYPT_ERR_LARGE_DATA_SIZE|N/A]
* @retval SEC_UINT32 AEAD decryption operation failure / tag verification failure [SEC_ERR|N/A]
*
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
*
* - Supported lengths for authentication tag : \n
* 4 bytes, 8 bytes, 12 bytes, 13 bytes, 14 bytes, 15 bytes, 16 bytes. The tag length should be passed by
* user and the buffer to hold output tag in case of encryption should be allocated by user.
*
* - The output buffer to hold cipher text / decrypted text should be allocated by user. The buffer should
* contain memory of input length passed.
* - On encryption / decryption success, output data length will be same as input data length.
* - The data size need not be multiple of block size (block size of AES GCM is 16 bytes).
* - If data is being encrypted/decrypted as partial data with IPSI_SYM_DATA_TYPE_PARTIAL type,
* - IV should be set for the first time only. From the second time, even if IV are passed, they will be ignored.
* - AAD can be set multiple times. But AAD should be set before sending data for encryption/decryption.
* - If AAD is set after some encryption/decryption operation, API fails. In this failure case, context can not
* be reused for further operations.
* if  set AAD after doing partial encryption/decryption operation, error SEC_CRYPT_ERR_SET_AAD_AFTER_CIPHER_OPERATION
* will be returned.
* - The tag & tag length will be validated only if passed IPSI_SYM_DATA_TYPE_LAST_PARTIAL & IPSI_SYM_DATA_TYPE_FULL
* type. These will be ignored when passed type as IPSI_SYM_DATA_TYPE_PARTIAL.
* - As per NIST SP800-38D (AES-GCM) standard, decrypted output should be returned to user only when authentication(tag)
* verification is successful. But when used IPSI_SYM_DATA_TYPE_PARTIAL type, API will return the output data.
* So, application should check the return value of API when processed with IPSI_SYM_DATA_TYPE_LAST_PARTIAL type,
* if it is success only, should consider the decrypted data & use it for application operations.
* - The maximum lengths supported as per SP800-38D standard are :
*    (a) For AAD, length of AAD is less than or equal to (2^64 - 1) in bits.
*         In bytes, it should be less than or equal to 2^61.
*    (b) For IV, length of IV is (1<= len(IV) <= (2^64 - 1)) in bits.
*         In bytes, it should be less than or equal to 2^61.
*    (c) For Data to be encrypted / decrypted, length should be <= 2^39-256 in bits.
*         In bytes, it should be less than or equal to (2^36 - 32).
*    (d) For AAD, IV & length to encrypted / decrypted, the data types are "size_t".
*         So, on 32 bit systems, they support maximum length of size_t (2^32-1), on 64 bit systems,
*         they support maximum length of size_t (2^64 - 1).
* - When passed the input length to be encrypted / decrypted as zero, no output pointers will be updated.
* - SEC_ERR_INVALID_ARG will be returned if:
*     - Context is NULL.
*     - If input data length is not zero and any of the pointer of input data, output data, output data length is NULL.
*     - AAD pointer is NULL and AAD length is not zero.
*     - Pointer to tag is NULL.
*     - Invalid data type (other than IPSI_SYM_DATA_TYPE_FULL, IPSI_SYM_DATA_TYPE_PARTIAL,
*       IPSI_SYM_DATA_TYPE_LAST_PARTIAL).
*     - IV is NULL.
*     - Pointer to IPSI_AEAD_OP_DATA_S is NULL.
*
* @par Related Topics
* CRYPT_aeadInitSession \n
* CRYPT_aeadRemoveSession
*/
CRYPTOLINKDLL SEC_UINT32 CRYPT_aeadOp(IPSI_AEAD_OP_DATA_S *pstOpData,
                                                                        SEC_UCHAR *pucInData,
                                                                        size_t ulInDataLen,
                                                                        SEC_UCHAR *pucOutData,
                                                                        size_t *pulOutDataLen,
                                                                        SEC_UCHAR *pucHashResult,
                                                                        SEC_UINT32 ulHashResultLen,
                                                                        IPSI_AUX_PAR_S *pstAuxPar);


/*
    Func Name:  CRYPT_aeadRemoveSession
*/

/**
* @defgroup CRYPT_aeadRemoveSession
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_VOID CRYPT_aeadRemoveSession(CRYPT_AEAD_CTX ctx);
* @endcode
*
* @par Purpose
* This is used to free the AEAD session context structure.
*
* @par Description
* CRYPT_aeadRemoveSession used to free the AEAD session context structure.
*
* @param[in]  ctx Pointer to AEAD session context [N/A]
*
* @par Return values
* N/A

* @par Required Header File
* sec_crypto.h
*
* @par Note
* 
* CRYPT_aeadRemoveSession should be only used to remove the context created with AEAD algorithm.
* Currently, supported AEAD algorithms are ALGID_AES128_GCM, ALGID_AES192_GCM & ALGID_AES256_GCM.
* If called with context created with any other algorithm, behavior is undefined.
*
* @par Related Topics
* CRYPT_aeadInitSession \n
* CRYPT_aeadOp
*/
CRYPTOLINKDLL SEC_VOID CRYPT_aeadRemoveSession(CRYPT_AEAD_CTX ctx);



/**
* @defgroup IPSI_SYM_SETUP_DATA_S
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct stSymSessionSetUpData
* {
*     SEC_UINT32 uiSymAlgID;
*     IPSI_SYM_CIPHER_DIRECTION_E uiSymDirection;
*     SEC_UCHAR *pucKey;
*     SEC_UINT32 uiKeyLen;
*     SEC_VOID *pCipherSetupData;
* }IPSI_SYM_SETUP_DATA_S;
* @endcode
*
* @datastruct uiSymAlgID symmetric algorithm ID.
* Currently supported algorithm is only AES CTR (ALGID_AES128_CTR, ALGID_AES192_CTR & ALGID_AES256_CTR).
* @datastruct uiSymDirection Identifies the cipher direction whether encryption or decryption.
*                  Supported values are IPSI_SYM_ENCRYPT and IPSI_SYM_DECRYPT.
* @datastruct pucKey Pointer to the key structure used in AEAD operations.
* @datastruct uiKeyLen Key length.
* @datastruct pCipherSetupData No use for now. Added for future extensability.
*
*/
typedef struct stSymSessionSetUpData
{
    SEC_UINT32 uiSymAlgID;
    IPSI_SYM_CIPHER_DIRECTION_E uiSymDirection;
    SEC_UCHAR *pucKey;
    SEC_UINT32 uiKeyLen;
    SEC_VOID *pCipherSetupData;
}IPSI_SYM_SETUP_DATA_S;


/**
* @defgroup IPSI_SYM_OP_DATA_S
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct stSymOpData
* {
*     CRYPT_SYM_CTX ctx;
*     IPSI_SYM_DATATYPE_E enDataType;
*     SEC_UCHAR *pucIV;
*     SEC_UINT32 uiIvLen;
*     SEC_VOID *pCipherOpData;
* }IPSI_SYM_OP_DATA_S;
* @endcode
*
* @datastruct ctx Pointer to the symmetric operation session context.
* @datastruct enDataType Identifies the data type whether FULL or PARTIAL.
* @datastruct pucIV Pointer to the Initialization Vector used in symmetric encryption/decryption operations.
* @datastruct uiIvLen Initialization Vector length.
* @datastruct pCipherOpData No use for now. Added for future extensability.
*
*/
typedef struct stSymOpData
{
    CRYPT_SYM_CTX ctx;
    IPSI_SYM_DATATYPE_E enDataType;
    SEC_UCHAR *pucIV;
    SEC_UINT32 uiIvLen;
    SEC_VOID *pCipherOpData;
}IPSI_SYM_OP_DATA_S;


/*
    Func Name:  CRYPT_symInitSession
*/

/**
* @defgroup CRYPT_symInitSession
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_symInitSession(CRYPT_SYM_CTX *pCtx, IPSI_SYM_SETUP_DATA_S *pstSetUpInfo, IPSI_AUX_PAR_S *pstAuxPar);
* @endcode
*
* @par Purpose
* This is used to initialize the symmetric encryption/decryption session context structure.
*
* @par Description
* CRYPT_symInitSession used to initialize the symmetric encryption/decryption session context structure
* with the algorithm, key, key length and cipher direction (encrypt or decrypt).
*
* @param[in]  pCtx Pointer to symmetric encryption/decryption session context [N/A]
* @param[in]  pstSetUpInfo Pointer to symmetric encryption/decryption initialization information [N/A]
* @param[in]  pstAuxPar Pass as SEC_NULL. Additional variable for future extensibility [N/A]
*
* @retval SEC_UINT32 Invalid argument [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Invalid algorithm identifier [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 Memory allocation failure [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 Invalid key length [SEC_ERR_INVALID_KEY_LEN|N/A]

* @par Required Header File
* sec_crypto.h
*
* @par Note
* 
* - SEC_ERR_INVALID_ARG will be returned if:
*    - Input arguments are NULL.
*    - Input key is NULL.
*    - Invalid direction (other than IPSI_SYM_ENCRYPT and IPSI_SYM_DECRYPT for direction in setup information)
* - Padding is not applicable to AES CTR algorithms as there is no restriction on block size for AES CTR algorithm.
* Even if padding mode is set to algorithm id, it will be ignored.
* - SEC_ERR_INVALID_ALGID will be returned if:
*    - If algorithm ID passed is other than ALGID_AES128_CTR, ALGID_AES192_CTR & ALGID_AES256_CTR.
* - SEC_ERR_INVALID_KEY_LEN will be returned if key length passed is not matching with expected key length.
* For ALGID_AES128_CTR, the key length should be 16 bytes, for ALGID_AES192_CTR, the key length should be 24 bytes,
* for ALGID_AES256_CTR, the key length should be 32 bytes.
* 
* @par Related Topics
* CRYPT_symOp \n
* CRYPT_symRemoveSession
*/
CRYPTOLINKDLL SEC_UINT32 CRYPT_symInitSession(CRYPT_SYM_CTX *pCtx, IPSI_SYM_SETUP_DATA_S *pstSetUpInfo,
                                                                                    IPSI_AUX_PAR_S *pstAuxPar);


/*
    Func Name:  CRYPT_symOp
*/

/**
* @defgroup CRYPT_symOp
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_symOp(
* IPSI_SYM_OP_DATA_S *pstOpData,
* SEC_UCHAR *pucInData,
* size_t ulInDataLen,
* SEC_UCHAR *pucOutData,
* size_t *pulOutDataLen,
* IPSI_AUX_PAR_S *pstAuxPar);
* @endcode
*
* @par Purpose
* Used to do encryption / decryption operation on symmetric algorithms. Currently supported algorithms
* for this API are ALGID_AES128_CTR, ALGID_AES192_CTR & ALGID_AES256_CTR.
*
* @par Description
* CRYPT_symOp used to do encryption / decryption operation. In case of encryption,
* encrypted data will be generated by this function. In case of decryption, it takes encrypted data
* as input and outputs decrypted text.Currently supported algorithms
* for this API are ALGID_AES128_CTR, ALGID_AES192_CTR & ALGID_AES256_CTR.
*
* @param[in]  pstOpData Pointer to operation data which holds information
*                                 required for encryption / decryption [N/A]
* @param[in]  pucInData Pointer to input data for encryption / decryption operation [N/A]
* @param[in]  ulInDataLen Input data length [N/A]
* @param[out]  pucOutData Pointer to output data [N/A]
* @param[out]  pulOutDataLen Pointer to output data length [N/A]
* @param[in]  pstAuxPar Pass as SEC_NULL. Additional variable for future extensibility [N/A]
*
* @retval SEC_UINT32 Invalid arguments [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Invalid IV length [SEC_ERR_INVALID_IV_LEN|N/A]
* @retval SEC_UINT32 Internal error [SEC_ERR|N/A]
*
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
*
* - The output buffer to hold cipher text / decrypted text should be allocated by user. The buffer should
* contain memory of input length passed.
* - On encryption / decryption success, output data length will be same as input data length.
* - The data size need not be multiple of block size for CTR algorithms(block size of AES CTR is 16 bytes).
* - The counter increment is done on whole IV. If application requirements are there such that only
*    some lower bits of IV to be incremented, application should take care that data blocks passed are with
*    that limit. This implementation does not check counter overflow into rest of the IV when incremented.
* - To reuse the context for further encryption/decryption because of the same key already set to context,
* API should be called with IPSI_SYM_DATA_TYPE_LAST_PARTIAL with some data.
* If there is no data to be processed but want to reuse the context with the same key, application can pass
* some dummy data for encryption/decryption operation & ignore the output data.
*
* - SEC_ERR_INVALID_ARG will be returned if:
*     - Context is NULL.
*     - If input data length is zero, any of the pointer of input data, output data, output data length is NULL.
*     - Invalid data type (other than IPSI_SYM_DATA_TYPE_FULL, IPSI_SYM_DATA_TYPE_PARTIAL,
*       IPSI_SYM_DATA_TYPE_LAST_PARTIAL).
*     - IV is NULL.
*     - Pointer to IPSI_SYM_OP_DATA_S is NULL.
*
* @par Related Topics
* CRYPT_symInitSession \n
* CRYPT_symRemoveSession
*/
CRYPTOLINKDLL SEC_UINT32 CRYPT_symOp(IPSI_SYM_OP_DATA_S *pstOpData, SEC_UCHAR *pucInData, size_t ulInDataLen,
                                        SEC_UCHAR *pucOutData, size_t *pulOutDataLen, IPSI_AUX_PAR_S *pstAuxPar);


/*
    Func Name:  CRYPT_symRemoveSession
*/

/**
* @defgroup CRYPT_symRemoveSession
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_VOID CRYPT_symRemoveSession(CRYPT_SYM_CTX ctx);
* @endcode
*
* @par Purpose
* This is used to free the symmetric encryption/decryption session context structure created using CRYPT_symInitSession.
*
* @par Description
* CRYPT_symRemoveSession used to free the encryption/decryption session context structure
* created using CRYPT_symInitSession.
*
* @param[in]  ctx Pointer to symmetric operation session context [N/A]
*
* @par Return values
* N/A

* @par Required Header File
* sec_crypto.h
*
* @par Note
* 
* CRYPT_symRemoveSession should be only used to remove the context created with CRYPT_symInitSession.
* If called with context created with any other API, behavior is undefined.
*
* @par Related Topics
* CRYPT_symInitSession \n
* CRYPT_symOp
*/
CRYPTOLINKDLL SEC_VOID CRYPT_symRemoveSession(CRYPT_SYM_CTX ctx);

/**
* @defgroup IPSI_CRYPT_enableRsaSignWithPrvExp
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_VOID IPSI_CRYPT_enableRsaSignWithPrvExp();
* @endcode
*
* @par Purpose
* This API enables RSA signing with only the private key components.(D, N and E).
*
* @par Description
* This API is used to enable RSA signing with only the private key components.(D, N and E). If RSA signing with private 
* key  component is enabled, the Crypto library will first check whether p, q ,dp, dq and qinv are available in the
* RSA private key. If available, the signature will be generated with these values, otherwise the signature generation 
* will be done using D , N and E values. By default, this feature is disabled.
*
* @par Parameters
* N/A
*
* @retval
* N/A
*
* @par Required Header File
* sec_crypto.h
*
* @par Note
* On using IPSI_CRYPT_enableRsaSignWithPrvExp, the performance of RSA signature generation will be impacted in two ways:
* -#	When this API is used and all private key parameters p, q ,dp, dq and qInversion are available, the performance
*       is slightly impacted as Crypto needs to check all these parameters are available. If all these parameters are 
*       available, then Crypto will use these to precalculate the value for signing.
* -#	When this API is used and only the parameters D, N and E of the private key parameters are available, then 
*       these parameters are used for signing and the performance of signing will be lower than the normal case as 
*       signing does not use precalculated values.
*       
* @par Related Topics
* IPSI_CRYPT_disableRsaSignWithPrvExp
*/
CRYPTOLINKDLL SEC_VOID IPSI_CRYPT_enableRsaSignWithPrvExp();


/**
* @defgroup IPSI_CRYPT_disableRsaSignWithPrvExp
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_VOID IPSI_CRYPT_disableRsaSignWithPrvExp();
* @endcode
*
* @par Purpose
* This API disables RSA signing with only the private key components.(D, N and E).

* @par Description
* This API disables RSA signing with only the private key components.(D, N and E).
*
* @par Parameters
* N/A
*
* @retval
* N/A
*
* @par Required Header File
* sec_crypto.h
*
*       
* @par Related Topics
* IPSI_CRYPT_enableRsaSignWithPrvExp
*/
CRYPTOLINKDLL SEC_VOID IPSI_CRYPT_disableRsaSignWithPrvExp();


#ifdef __cplusplus
}
#endif

#endif /* _IPSI_SEC_CRYPTO_H */


