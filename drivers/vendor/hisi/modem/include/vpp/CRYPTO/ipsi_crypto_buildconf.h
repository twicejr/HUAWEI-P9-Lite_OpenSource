/***********************************
Copyright (C), 2004, Huawei Tech. Co., Ltd.
FileName: ipsi_crypto_buildconf.h
Author: Prabhat Kumar Gopalika
Version: 1
Creation Date: 2010-04-08
Description: This file controls the build configurations of crypto.

        History               :
                <author>   <date>          <desc>
				Kaushik		2010-10-15	Addes VPPSEC and IKE Enhancement
										Macros
******************************************************************************/
#ifndef __IPSI_CRYPTO_BUILDCONF_H__
#define __IPSI_CRYPTO_BUILDCONF_H__

#ifdef __IPSI_NO_BIN_LOG__
#undef  __IPSI_NO_BIN_LOG__
#endif


#ifdef __IPSI_NO_CPLUS_SHA224__
#undef __IPSI_NO_CPLUS_SHA224__
#endif

#ifdef __IPSI_NO_CORE_SHA224__
#undef __IPSI_NO_CORE_SHA224__
#endif

#ifdef __IPSI_NO_CPLUS_SHA256__
#undef __IPSI_NO_CPLUS_SHA256__
#endif

//Enable DH Parameter Generation support
#ifdef __IPSI_NO_DH_PARA__
#undef __IPSI_NO_DH_PARA__
#endif
#ifdef __IPSI_NO_CORE_SHA256__
#undef __IPSI_NO_CORE_SHA256__
#endif

#ifdef __IPSI_NO_CPLUS_SHA384__
#undef __IPSI_NO_CPLUS_SHA384__
#endif

#ifdef __IPSI_NO_CORE_SHA384__
#undef __IPSI_NO_CORE_SHA384__
#endif

#ifdef __IPSI_NO_CPLUS_SHA512__
#undef __IPSI_NO_CPLUS_SHA512__
#endif

#ifdef __IPSI_NO_CORE_SHA512__
#undef __IPSI_NO_CORE_SHA512__
#endif

#ifdef __IPSI_NO_CPLUS_HMAC_SHA224__
#undef __IPSI_NO_CPLUS_HMAC_SHA224__
#endif

#ifdef __IPSI_NO_CORE_HMAC_SHA224__
#undef __IPSI_NO_CORE_HMAC_SHA224__
#endif

#ifdef __IPSI_NO_CPLUS_HMAC_SHA256__
#undef __IPSI_NO_CPLUS_HMAC_SHA256__
#endif

#ifdef __IPSI_NO_CORE_HMAC_SHA256__
#undef __IPSI_NO_CORE_HMAC_SHA256__
#endif

#ifdef __IPSI_NO_CPLUS_HMAC_SHA384__
#undef __IPSI_NO_CPLUS_HMAC_SHA384__
#endif

#ifdef __IPSI_NO_CORE_HMAC_SHA384__
#undef __IPSI_NO_CORE_HMAC_SHA384__
#endif

#ifdef __IPSI_NO_CPLUS_HMAC_SHA512__
#undef __IPSI_NO_CPLUS_HMAC_SHA512__
#endif

#ifdef __IPSI_NO_CORE_HMAC_SHA512__
#undef __IPSI_NO_CORE_HMAC_SHA512__
#endif


//Enable AES XCBC MAC Support
#ifdef __IPSI_NO_AES_XCBC__
#undef __IPSI_NO_AES_XCBC__
#endif

// BEGIN: Macros for disabling VPPSEC specific functions
#ifdef __IPSI_NO_CORE_AES__
#undef __IPSI_NO_CORE_AES__
#endif

#ifdef __IPSI_NO_CORE_DES__
#undef __IPSI_NO_CORE_DES__
#endif

#ifdef __IPSI_NO_CORE_BN__
#undef __IPSI_NO_CORE_BN__
#endif

#ifdef __IPSI_NO_CORE_DH__
#undef __IPSI_NO_CORE_DH__
#endif

// END: Macros for disabling VPPSEC specific functions

// BEGIN: Macros for disabling RC2
#ifdef __IPSI_NO_RC2__
#undef __IPSI_NO_RC2__
#endif

//END: Macros for disabling RC2

// BEGIN: Macros for disabling rsa prime generation callbacks

#ifdef __IPSI_RSA_NOEXTENDEDKEYPAIR__
#undef __IPSI_RSA_NOEXTENDEDKEYPAIR__
#endif

#ifdef __IPSI_RSA_NOTIMER__
#undef __IPSI_RSA_NOTIMER__
#endif

#ifdef __IPSI_NO_ASYM_COMMON_IFACE__
#undef __IPSI_NO_ASYM_COMMON_IFACE__
#endif

#ifdef __IPSI_NO_HMAC_COMMON_IFACE__
#undef __IPSI_NO_HMAC_COMMON_IFACE__
#endif

#ifdef __IPSI_CRYPTO_NO_ASSERTS__
#undef __IPSI_CRYPTO_NO_ASSERTS__
#endif

#ifdef __IPSI_NO_DSA_IFACE__
#undef __IPSI_NO_DSA_IFACE__
#endif

#ifdef __IPSI_NO_RNG_COREIMPL__
#undef __IPSI_NO_RNG_COREIMPL__
#endif

#ifdef __IPSI_NO_EC_PARAM_POINTS__
#undef __IPSI_NO_EC_PARAM_POINTS__
#endif

#ifdef __IPSI_NO_SEC_DEF__
#undef __IPSI_NO_SEC_DEF__
#endif

#ifdef __IPSI_NO_PID__
#undef __IPSI_NO_PID__
#endif

#ifdef __IPSI_NO_BITOP__
#undef __IPSI_NO_BITOP__
#endif

#ifdef __IPSI_NO_CRYPTO_FUNC__
#undef __IPSI_NO_CRYPTO_FUNC__
#endif

#ifdef __IPSI_NO_CRYPTO_INIT__
#undef __IPSI_NO_CRYPTO_INIT__
#endif

#ifdef __IPSI_NO_CRYPTO_MISC__
#undef __IPSI_NO_CRYPTO_MISC__
#endif

#ifdef __IPSI_NO_MEM_CALLOC__
#undef __IPSI_NO_MEM_CALLOC__
#endif


//END: Macros for disabling rsa prime generation callbacks

/* Macros for disabling AEAD (AES GCM) operations */
#ifdef __IPSI_NO_CORE_AES_GCM__
#undef __IPSI_NO_CORE_AES_GCM__
#endif

#ifdef __IPSI_NO_AES_GCM_ENC__
#undef __IPSI_NO_AES_GCM_ENC__
#endif

#ifdef __IPSI_NO_AES_GCM_DEC__
#undef __IPSI_NO_AES_GCM_DEC__
#endif

#ifdef __IPSI_NO_AEAD_ENC__
#undef __IPSI_NO_AEAD_ENC__
#endif

#ifdef __IPSI_NO_AEAD_DEC__
#undef __IPSI_NO_AEAD_DEC__
#endif

#ifdef __IPSI_NO_AEAD__
#undef __IPSI_NO_AEAD__
#endif

/* End - Macros for disabling AEAD (AES GCM) operations */



#ifdef __IPSI_SFTP_CRYPTO__

#define __IPSI_NO_AES_XCBC__
#define __IPSI_NO_CMAC__

#define __IPSI_NO_AES256_CBC_ENC__
#define __IPSI_NO_AES256_CBC_DCR__
#define __IPSI_NO_DES_CFB_ENC__
#define __IPSI_NO_DES_CFB_DCR__
#define __IPSI_NO_DES_OFB_ENC__
#define __IPSI_NO_DES_OFB_DCR__
#define __IPSI_NO_DES_EDE_CFB_ENC__
#define __IPSI_NO_DES_EDE_CFB_DCR__
#define __IPSI_NO_DES_EDE_OFB_ENC__
#define __IPSI_NO_DES_EDE_OFB_DCR__
#define __IPSI_NO_DES_EDE3_CFB_ENC__
#define __IPSI_NO_DES_EDE3_CFB_DCR__
#define __IPSI_NO_DES_EDE3_OFB_ENC__
#define __IPSI_NO_DES_EDE3_OFB_DCR__
#define __IPSI_NO_AES128_CFB_ENC__
#define __IPSI_NO_AES128_CFB_DCR__
#define __IPSI_NO_AES128_OFB_ENC__
#define __IPSI_NO_AES128_OFB_DCR__
#define __IPSI_NO_AES192_CFB_ENC__
#define __IPSI_NO_AES192_CFB_DCR__
#define __IPSI_NO_AES192_OFB_ENC__
#define __IPSI_NO_AES192_OFB_DCR__
#define __IPSI_NO_AES256_CFB_ENC__
#define __IPSI_NO_AES256_CFB_DCR__
#define __IPSI_NO_AES256_OFB_ENC__
#define __IPSI_NO_AES256_OFB_DCR__

/*Removing the Blowfish Core implementation as well */
#define __IPSI_NO_BLOWFISH__
#define __IPSI_NO_BF_ECB_DCR__
#define __IPSI_NO_BF_CBC_DCR__
#define __IPSI_NO_BF_CFB_DCR__
#define __IPSI_NO_BF_OFB_DCR__
#define __IPSI_NO_BF_ECB_ENC__
#define __IPSI_NO_BF_CBC_ENC__
#define __IPSI_NO_BF_CFB_ENC__
#define __IPSI_NO_BF_OFB_ENC__
#define __IPSI_NO_SHA384__
#define __IPSI_NO_SHA512__
#define __IPSI_NO_SHA224__

#define __IPSI_NO_MD4__

// HMAC Flag
#define __IPSI_NO_HMAC_MD4__

#define __IPSI_NO_HMAC_SHA224__
#define __IPSI_NO_HMAC_SHA256__
#define __IPSI_NO_HMAC_SHA384__
#define __IPSI_NO_HMAC_SHA512__

// CMAC Flag
#define __IPSI_NO_CMAC__
#define __IPSI_NO_CMAC_AES__
#define __IPSI_NO_CMAC_TDES__



// Asymmetric Key Flag
#define __IPSI_NO_ASYM_EC_KEY__

#define __IPSI_NO_ASYM_ECDH_KEY__

// Asymmetric Sign Flag
#define __IPSI_NO_ASYM_ECDSA_SIGN__
#define __IPSI_NO_ASYM_SM2DSA_SIGN__

// Asymmetric Sign Verify 
#define __IPSI_NO_ASYM_ECDSA_SIGN_VRF__
#define __IPSI_NO_ASYM_SM2DSA_SIGN_VRF__
#define __IPSI_NO_ASYM_SSL_SIGN_VRF__ 

#define __IPSI_NO_EC__ 
#define __IPSI_NO_ECDH__ 
#define __IPSI_NO_ECDSA__ 
#define __IPSI_NO_ASYM_EC_KEY__
#define __IPSI_NO_ASYM_ECDH_KEY__


// Asymmetric Key Flag
#define __IPSI_NO_ASYM_EC_KEY__

#define __IPSI_NO_ASYM_ECDH_KEY__


#define __IPSI_NO_KDF_SM3__
#define __IPSI_NO_SM3__
#define __IPSI_NO_HMAC_SM3__
#define __IPSI_NO_SM2__
#define __IPSI_NO_SM2DSA__
#define __IPSI_NO_KDF_SHA224__
#define __IPSI_NO_KDF_SHA256__
#define __IPSI_NO_KDF_SHA384__
#define __IPSI_NO_KDF_SHA512__
#define __IPSI_NO_SCRYPT
#define __IPSI_NO_OSSL_WRAP_BN__

#define __IPSI_NO_CORE_AES_GCM__
#define __IPSI_NO_AES_GCM_ENC__
#define __IPSI_NO_AES_GCM_DEC__
#define __IPSI_NO_AEAD_ENC__
#define __IPSI_NO_AEAD_DEC__
#define __IPSI_NO_AEAD__
#define __IPSI_NO_AEAD_IFACE__

#define __IPSI_NO_SYM_CTR_ENC_DEC__
#define __IPSI_NO_SYM_IFACE__
#define __IPSI_NO_RSA_SIGN_WITH_PVT_EXP__

#endif


// used to compile small crypto for Rosa Pico
#ifdef __IPSI_SMALL_SIGCBB__

#define __IPSI_NO_RC2__
#define __IPSI_NO_EC_PARAM_POINTS__
#define __IPSI_NO_KDF__
#define __IPSI_NO_KEY_WRAP_UNWRAP__
#define __IPSI_NO_EC_POLY_CURVE__
#define __IPSI_NO_EC_UTILS__
#define __IPSI_NO_EC_GF__
#define __IPSI_NO_EC_BITARRAY__
#define __IPSI_NO_AES_CORE_IMPL__
#define __IPSI_NO_DES__
#define __IPSI_NO_STREAM_CIPHER__
#define __IPSI_NO_AVL__
#define __CRYPTO_NO_SEC_LIST__
#define __IPSI_NO_BIN_LOG__
#define __IPSI_NO_MASK_GEN_CLASS__
#define __IPSI_NO_EXPOSED_DIGEST__
#define __IPSI_NO_RSA_MGF__
#define __IPSI_NO_SEC_LOG__
#define __IPSI_NO_LOCK__
#define __IPSI_NO_CORE_DES__
#define __IPSI_NO_OAEP_CLASS__
#define __IPSI_NO_ERROR_LOG__
#define __IPSI_NO_SYM_PAD__
#define __IPSI_NO_HMAC_COMMON_IFACE__
#define __IPSI_CRYPTO_NO_ASSERTS__
#define __IPSI_NO_DOUBLE_DES_DEC__
#define __IPSI_NO_DOUBLE_DES_ENC__
#define __IPSI_NO_KASUMI__
#define __IPSI_NO_RNG_COREIMPL__
#define __IPSI_NO_EXPOSED_DIGEST__

#define __IPSI_NO_MASK_GEN_CLASS__
#define __IPSI_NO_AES_XCBC__
#define __IPSI_NO_XCBC_AES__
#define __IPSI_NO_DH_PARA__
#define __IPSI_NO_BLOWFISH__


// Symmetric Encryption Flags
#define __IPSI_NO_SYM_ENC__
#define __IPSI_NO_DES_ECB_ENC__
#define __IPSI_NO_DES_CBC_ENC__
#define __IPSI_NO_DES_EDE_ECB_ENC__
#define __IPSI_NO_DES_EDE_CBC_ENC__
#define __IPSI_NO_DES_EDE3_ECB_ENC__
#define __IPSI_NO_DES_EDE3_CBC_ENC__
#define __IPSI_NO_AES128_ECB_ENC__
#define __IPSI_NO_AES128_CBC_ENC__
#define __IPSI_NO_AES192_ECB_ENC__
#define __IPSI_NO_AES192_CBC_ENC__
#define __IPSI_NO_AES256_ECB_ENC__
#define __IPSI_NO_AES256_CBC_ENC__
#define __IPSI_NO_DES_CFB_ENC__
#define __IPSI_NO_DES_OFB_ENC__
#define __IPSI_NO_DES_EDE_CFB_ENC__
#define __IPSI_NO_DES_EDE_OFB_ENC__
#define __IPSI_NO_DES_EDE3_CFB_ENC__
#define __IPSI_NO_DES_EDE3_OFB_ENC__
#define __IPSI_NO_AES128_CFB_ENC__
#define __IPSI_NO_AES128_OFB_ENC__
#define __IPSI_NO_AES192_CFB_ENC__
#define __IPSI_NO_AES192_OFB_ENC__
#define __IPSI_NO_AES256_CFB_ENC__
#define __IPSI_NO_AES256_OFB_ENC__
#define __IPSI_NO_KASUMI_ECB_ENC__
#define __IPSI_NO_KASUMI_CBC_ENC__
#define __IPSI_NO_KASUMI_CFB_ENC__
#define __IPSI_NO_KASUMI_OFB_ENC__
#define __IPSI_NO_RC4_ENC__

#define __IPSI_NO_BF_ECB_ENC__
#define __IPSI_NO_BF_CBC_ENC__
#define __IPSI_NO_BF_CFB_ENC__
#define __IPSI_NO_BF_OFB_ENC__

/*Removing the Blowfish Core implementation as well */
#define __IPSI_NO_BLOWFISH__

// Symmetric Decryption Flags
#define __IPSI_NO_SYM_DEC__
#define __IPSI_NO_DES_ECB_DCR__
#define __IPSI_NO_DES_CBC_DCR__
#define __IPSI_NO_DES_EDE_ECB_DCR__
#define __IPSI_NO_DES_EDE_CBC_DCR__
#define __IPSI_NO_DES_EDE3_ECB_DCR__
#define __IPSI_NO_DES_EDE3_CBC_DCR__
#define __IPSI_NO_AES128_ECB_DCR__
#define __IPSI_NO_AES128_CBC_DCR__
#define __IPSI_NO_AES192_ECB_DCR__
#define __IPSI_NO_AES192_CBC_DCR__
#define __IPSI_NO_AES256_ECB_DCR__
#define __IPSI_NO_AES256_CBC_DCR__
#define __IPSI_NO_DES_CFB_DCR__
#define __IPSI_NO_DES_OFB_DCR__
#define __IPSI_NO_DES_EDE_CFB_DCR__
#define __IPSI_NO_DES_EDE_OFB_DCR__
#define __IPSI_NO_DES_EDE3_CFB_DCR__
#define __IPSI_NO_DES_EDE3_OFB_DCR__
#define __IPSI_NO_AES128_CFB_DCR__
#define __IPSI_NO_AES128_OFB_DCR__
#define __IPSI_NO_AES192_CFB_DCR__
#define __IPSI_NO_AES192_OFB_DCR__
#define __IPSI_NO_AES256_CFB_DCR__
#define __IPSI_NO_AES256_OFB_DCR__
#define __IPSI_NO_RC4_DCR__

#define __IPSI_NO_BF_ECB_DCR__
#define __IPSI_NO_BF_CBC_DCR__
#define __IPSI_NO_BF_CFB_DCR__
#define __IPSI_NO_BF_OFB_DCR__

#define __IPSI_NO_DSA_IFACE__
#define __IPSI_NO_SHA1__
#define __IPSI_NO_SHA384__
#define __IPSI_NO_SHA512__
#define __IPSI_NO_SHA224__
#define __IPSI_NO_MD5__
#define __IPSI_NO_MD4__


// RNG Flag
#define __IPSI_NO_RNG__

#define __IPSI_NO_RNG_SSL__

// HMAC Flag
#define __IPSI_NO_HMAC__
#define __IPSI_NO_HMAC_MD4__
#define __IPSI_NO_HMAC_MD5__
#define __IPSI_NO_HMAC_SHA1__
#define __IPSI_NO_HMAC_SHA224__
#define __IPSI_NO_HMAC_SHA256__
#define __IPSI_NO_HMAC_SHA384__
#define __IPSI_NO_HMAC_SHA512__


// CMAC Flag
#define __IPSI_NO_CMAC__
#define __IPSI_NO_CMAC_AES__
#define __IPSI_NO_CMAC_TDES__


// Asymmetric RSA Encryption/Decryption Flag
#define __IPSI_NO_RSA_ENC_DEC__
#define __IPSI_NO_RSA_ENC__
#define __IPSI_NO_RSA_DEC__
#define __IPSI_NO_RSA_GEN__
#define __IPSI_NO_RSA_PAD__


// RSA Encode/Decode 
#define __IPSI_NO_RSA_PVT_KEY_ENC__
#define __IPSI_NO_RSA_KEY_PAIR_ENC__

// RSA Decode 
#define __IPSI_NO_RSA_KEY_DEC__
#define __IPSI_NO_RSA_PUB_KEY_DEC__
#define __IPSI_NO_RSA_PVT_KEY_DEC__
#define __IPSI_NO_RSA_KEY_PAIR_DEC__


// Asymmetric Key Flag
#define __IPSI_NO_ASYM_KEY__
#define __IPSI_NO_ASYM_RSA_KEY__
#define __IPSI_NO_ASYM_DSA_KEY__
#define __IPSI_NO_ASYM_EC_KEY__
#define __IPSI_NO_ASYM_DH_KEY__
#define __IPSI_NO_ASYM_ECDH_KEY__


// Asymmetric Sign Flag
#define __IPSI_NO_ASYM_SIGN__
#define __IPSI_NO_ASYM_RSA_SIGN__
#define __IPSI_NO_ASYM_DSA_SIGN__
#define __IPSI_NO_ASYM_ECDSA_SIGN__
#define __IPSI_NO_ASYM_SM2DSA_SIGN__


// Asymmetric Sign Verification Flag
#define __IPSI_NO_ASYM_DSA_SIGN_VRF__
#define __IPSI_NO_ASYM_ECDSA_SIGN_VRF__
#define __IPSI_NO_ASYM_SM2DSA_SIGN_VRF__

#define __IPSI_NO_ASYM_SSL_SIGN_VRF__ 


#define __IPSI_NO_DSA__
#define __IPSI_NO_EC__
#define __IPSI_NO_ECDH__
#define __IPSI_NO_ECDSA__
#define __IPSI_NO_DH__



#define __IPSI_NO_XBN__ 
#define __IPSI_NO_SMALL_BN__
#define __IPSI_NO_SMALL_SHA1__
#define __IPSI_NO_SMALL_SHA256__
#define __IPSI_NO_SMALL_ES__
#define __IPSI_NO_SMALL_SSA__
#define __IPSI_NO_SMALL_CPLUS__
#define __IPSI_NO_SMALL_KEY_ENC__

#define __IPSI_NO_SMALL_PKEY__
#define __IPSI_NO_KEY_ENC_DCR__
#define __IPSI_NO_ASYM_KEY_GEN__

#define __IPSI_NO_SMALL_DIGEST__

// no VPPSEC interface API's required
#define __IPSI_NO_CORE_AES__
#define __IPSI_NO_CORE_DES__
#define __IPSI_NO_CORE_BN__
#define __IPSI_NO_CORE_DH__
#define __IPSI_NO_CORE_SHA224__
#define __IPSI_NO_CORE_SHA384__
#define __IPSI_NO_CORE_SHA512__
#define __IPSI_NO_CPLUS_SHA384__
#define __IPSI_NO_CPLUS_SHA512__

#define __IPSI_NO_CRYPTO_UTILS__
#define __IPSI_NO_CRYPTO_LOG__
#define __IPSI_DISABLE_GET_CRYPTO_VERSION__
#define __IPSI_DISABLE_DISPLAY_CRYPTO_VERSION__
#define __IPSI_NO_KDF_SM3__
#define __IPSI_NO_SM3__
#define __IPSI_NO_HMAC_SM3__
#define __IPSI_NO_SM2__
#define __IPSI_NO_SM2DSA__
#define __IPSI_NO_KDF_SHA224__
#define __IPSI_NO_KDF_SHA256__
#define __IPSI_NO_KDF_SHA384__
#define __IPSI_NO_KDF_SHA512__
#define __IPSI_NO_SCRYPT
#define __IPSI_NO_OSSL_WRAP_BN__

#define __IPSI_NO_CORE_AES_GCM__
#define __IPSI_NO_AES_GCM_ENC__
#define __IPSI_NO_AES_GCM_DEC__
#define __IPSI_NO_AEAD_ENC__
#define __IPSI_NO_AEAD_DEC__
#define __IPSI_NO_AEAD__
#define __IPSI_NO_AEAD_IFACE__

#define __IPSI_NO_SYM_CTR_ENC_DEC__
#define __IPSI_NO_SYM_IFACE__

#define __IPSI_NO_RSA_SIGN_WITH_PVT_EXP__

#endif // End of Small Crypto

#ifdef __IPSI_PSOS_TRIMEDIA__
#define __IPSI_NO_SHA_64BIT
#define __IPSI_NO_CPLUS_SHA384__
#define __IPSI_NO_CPLUS_SHA512__
#define __IPSI_NO_CORE_SHA384__
#define __IPSI_NO_CORE_SHA512__
#define __IPSI_NO_CPLUS_HMAC_SHA384__
#define __IPSI_NO_CORE_HMAC_SHA384__
#define __IPSI_NO_CPLUS_HMAC_SHA512__
#define __IPSI_NO_CORE_HMAC_SHA512__
#endif

#ifdef __IPSI_UMG_NO_64BIT_OPERATIONS__

#define __IPSI_NO_SHA_64BIT
#define __IPSI_NO_CPLUS_SHA384__
#define __IPSI_NO_CPLUS_SHA512__
#define __IPSI_NO_CORE_SHA384__
#define __IPSI_NO_CORE_SHA512__
#define __IPSI_NO_CPLUS_HMAC_SHA384__
#define __IPSI_NO_CORE_HMAC_SHA384__
#define __IPSI_NO_CPLUS_HMAC_SHA512__
#define __IPSI_NO_CORE_HMAC_SHA512__
#define __IPSI_NO_KDF_SHA384__
#define __IPSI_NO_KDF_SHA512__

#endif // __IPSI_UMG_NO_64BIT_OPERATIONS__

#ifdef __IPSI_VISP_RELEASE__

// no RC2
#define __IPSI_NO_RC2__

// no VPPSEC releated functions
#define __IPSI_NO_CORE_AES__
#define __IPSI_NO_CORE_DES__
#define __IPSI_NO_CORE_BN__
#define __IPSI_NO_CORE_DH__

//no RFC defined DH params
#define __IPSI_NO_DH_PARA__

//no prime generation callback
#define __IPSI_RSA_NOEXTENDEDKEYPAIR__
#define __IPSI_RSA_NOTIMER__
#endif

#ifndef __IPSI_NO_OCTEON_IMPL__
#define  __IPSI_NO_OCTEON_IMPL__
#endif

#ifdef __IPSI_ENABLE_OCTEON_HARDWARE__
#undef __IPSI_NO_OCTEON_IMPL__
#endif



#ifdef __IPSI_WLAN_SMALL_CRYPTO__

#define __IPSI_NO_AES_XCBC__
#define __IPSI_NO_DH_PARA__

// Symmetric Encryption Flags
#define __IPSI_NO_DES_CFB_ENC__
#define __IPSI_NO_DES_ECB_ENC__
#define __IPSI_NO_DES_OFB_ENC__
#define __IPSI_NO_DES_EDE_CBC_ENC__
#define __IPSI_NO_DES_EDE_CFB_ENC__
#define __IPSI_NO_DES_EDE_ECB_ENC__
#define __IPSI_NO_DES_EDE_OFB_ENC__
#define __IPSI_NO_DES_EDE3_CFB_ENC__
#define __IPSI_NO_DES_EDE3_ECB_ENC__
#define __IPSI_NO_DES_EDE3_OFB_ENC__
#define __IPSI_NO_AES128_CFB_ENC__
#define __IPSI_NO_AES128_ECB_ENC__
#define __IPSI_NO_AES128_OFB_ENC__
#define __IPSI_NO_AES192_CBC_ENC__
#define __IPSI_NO_AES192_CFB_ENC__
#define __IPSI_NO_AES192_ECB_ENC__
#define __IPSI_NO_AES192_OFB_ENC__
#define __IPSI_NO_AES256_CFB_ENC__
#define __IPSI_NO_AES256_ECB_ENC__
#define __IPSI_NO_AES256_OFB_ENC__
#define __IPSI_NO_KASUMI_CBC_ENC__
#define __IPSI_NO_KASUMI_CFB_ENC__
#define __IPSI_NO_KASUMI_ECB_ENC__
#define __IPSI_NO_KASUMI_OFB_ENC__

#define __IPSI_NO_BF_ECB_ENC__
#define __IPSI_NO_BF_CBC_ENC__
#define __IPSI_NO_BF_CFB_ENC__
#define __IPSI_NO_BF_OFB_ENC__

// Symmetric Decryption Flags
#define __IPSI_NO_DES_CFB_DCR__
#define __IPSI_NO_DES_ECB_DCR__
#define __IPSI_NO_DES_OFB_DCR__
#define __IPSI_NO_DES_EDE_CBC_DCR__
#define __IPSI_NO_DES_EDE_CFB_DCR__
#define __IPSI_NO_DES_EDE_ECB_DCR__
#define __IPSI_NO_DES_EDE_OFB_DCR__
#define __IPSI_NO_DES_EDE3_CFB_DCR__
#define __IPSI_NO_DES_EDE3_ECB_DCR__
#define __IPSI_NO_DES_EDE3_OFB_DCR__
#define __IPSI_NO_AES128_CFB_DCR__
#define __IPSI_NO_AES128_ECB_DCR__
#define __IPSI_NO_AES128_OFB_DCR__
#define __IPSI_NO_AES192_CBC_DCR__
#define __IPSI_NO_AES192_CFB_DCR__
#define __IPSI_NO_AES192_ECB_DCR__
#define __IPSI_NO_AES192_OFB_DCR__
#define __IPSI_NO_AES256_CFB_DCR__
#define __IPSI_NO_AES256_ECB_DCR__
#define __IPSI_NO_AES256_OFB_DCR__

#define __IPSI_NO_BF_ECB_DCR__
#define __IPSI_NO_BF_CBC_DCR__
#define __IPSI_NO_BF_CFB_DCR__
#define __IPSI_NO_BF_OFB_DCR__

/*Removing the Blowfish Core implementation as well */
#define __IPSI_NO_BLOWFISH__

#define __IPSI_NO_DOUBLE_DES_ENC__
#define __IPSI_NO_DOUBLE_DES_DEC__
#define __IPSI_NO_KASUMI__

#define __IPSI_NO_SYM_CFB_MODE__
#define __IPSI_NO_SYM_AES128_CFB_MODE__
#define __IPSI_NO_SYM_ECB_MODE__
#define __IPSI_NO_SYM_OFB_MODE__

#define __IPSI_NO_SYM_CFB_DEC__
#define __IPSI_NO_SYM_CFB_ENC__
#define __IPSI_NO_SYM_ECB_DEC__
#define __IPSI_NO_SYM_ECB_ENC__
#define __IPSI_NO_SYM_OFB_DEC__
#define __IPSI_NO_SYM_OFB_ENC__

#define __IPSI_NO_SHA224__

#define __IPSI_NO_MD4__


// RNG Flag
#define __IPSI_NO_RNG__

// HMAC Flag
#define __IPSI_NO_HMAC_MD4__

#define __IPSI_NO_HMAC_SHA224__
#define __IPSI_NO_HMAC_SHA256__
#define __IPSI_NO_HMAC_SHA384__
#define __IPSI_NO_HMAC_SHA512__


// CMAC Flag
#define __IPSI_NO_CMAC__
#define __IPSI_NO_CMAC_AES__
#define __IPSI_NO_CMAC_TDES__


// Asymmetric RSA Encryption/Decryption Flag
#define __IPSI_NO_RSA_ENC_DEC__
#define __IPSI_NO_RSA_ENC__
#define __IPSI_NO_RSA_DEC__
#define __IPSI_NO_RSA_GEN__
#define __IPSI_NO_RSA_PAD__
#define __IPSI_RSA_NOTIMER__

// RSA Encode/Decode 
 #define __IPSI_NO_RSA_KEY_ENC_DEC__
 #define __IPSI_NO_RSA_KEY_ENC__
 #define __IPSI_NO_RSA_PUB_KEY_ENC__
#define __IPSI_NO_RSA_PVT_KEY_ENC__
#define __IPSI_NO_RSA_PUB_KEY_DEC__
#define __IPSI_NO_RSA_KEY_PAIR_ENC__

// RSA Decode 
#define __IPSI_NO_RSA_KEY_DEC__
#define __IPSI_NO_RSA_PUB_KEY_DEC__
#define __IPSI_NO_RSA_PVT_KEY_DEC__
#define __IPSI_NO_RSA_KEY_PAIR_DEC__


// Asymmetric Key Flag
#define __IPSI_NO_ASYM_RSA_KEY__
#define __IPSI_NO_ASYM_DSA_KEY__


// Asymmetric Sign Flag
#define __IPSI_NO_ASYM_RSA_SIGN__
#define __IPSI_NO_ASYM_DSA_SIGN__

// Asymmetric Sign Verification Flag
#define __IPSI_NO_ASYM_RSA_SIGN_VRF__
#define __IPSI_NO_ASYM_DSA_SIGN_VRF__

#define __IPSI_NO_ASYM_SSL_SIGN_VRF__ 

#define __IPSI_NO_RSA__ 
#define __IPSI_NO_DSA_IFACE__

#define __IPSI_NO_KDF__
#define __IPSI_NO_KEY_WRAP_UNWRAP__
#define __IPSI_NO_EC_POLY_CURVE__
#define __IPSI_NO_EC_UTILS__
#define __IPSI_NO_EC_GF__
#define __IPSI_NO_EC_BITARRAY__
#define __IPSI_NO_RSA_MGF__
#define __IPSI_NO_ASYM_UTILS__
#define __IPSI_NO_OAEP_CLASS__
#define __IPSI_NO_MASK_GEN_CLASS__
#define __IPSI_NO_FEEDBACK__
#define __IPSI_NO_SET_IV__
#define __IPSI_NO_CRYPTO_UTILS__
#define __IPSI_NO_CRYPTO_ALG_UTILS__

// no VPPSEC interface API's required
#define __IPSI_NO_CORE_AES__
#define __IPSI_NO_CORE_DES__
#define __IPSI_NO_CORE_BN__
#define __IPSI_NO_CORE_DH__
#define __IPSI_NO_CORE_SHA224__
#define __IPSI_NO_CORE_SHA384_INTERFACE__
#define __IPSI_NO_CORE_SHA512_INTERFACE__

#define __IPSI_NO_RC2__

#define __IPSI_NO_ASYM_RSA_KEY__
#define __IPSI_RSA_NOEXTENDEDKEYPAIR__
#define __IPSI_NO_KEY_ENC_DCR__
#define __IPSI_NO_ERROR_LOG__
#define __IPSI_NO_BIN_LOG__
#define __IPSI_NO_CRYPTO_LOG__
#define __IPSI_NO_LOCK__
#define __IPSI_NO_AVL__
#define __IPSI_SMALL_SSL__
#define __IPSI_NO_KDF_SM3__
#define __IPSI_NO_SM3__
#define __IPSI_NO_HMAC_SM3__
#define __IPSI_NO_SM2__
#define __IPSI_NO_SM2DSA__
#define __IPSI_NO_KDF_SHA224__
#define __IPSI_NO_KDF_SHA256__
#define __IPSI_NO_KDF_SHA384__
#define __IPSI_NO_KDF_SHA512__
#define __IPSI_NO_SCRYPT
#define __IPSI_NO_OSSL_WRAP_BN__

#define __IPSI_NO_CORE_AES_GCM__
#define __IPSI_NO_AES_GCM_ENC__
#define __IPSI_NO_AES_GCM_DEC__
#define __IPSI_NO_AEAD_ENC__
#define __IPSI_NO_AEAD_DEC__
#define __IPSI_NO_AEAD__
#define __IPSI_NO_AEAD_IFACE__

#define __IPSI_NO_SYM_CTR_ENC_DEC__
#define __IPSI_NO_SYM_IFACE__

#define __IPSI_NO_RSA_SIGN_WITH_PVT_EXP__

#endif // __IPSI_WLAN_SMALL_CRYPTO__


#ifdef __IPSI_MBSC_SMALL_CRYPTO__

/* Symmetric core implementation algorithm tailoring */
#define __IPSI_NO_DOUBLE_DES_DEC__
#define __IPSI_NO_DOUBLE_DES_ENC__
#define __IPSI_NO_KASUMI__
#define __IPSI_NO_RC2__

/* Symmetric encryption algorithm tailoring through crypto_func.c */
#define __IPSI_NO_DES_ECB_ENC__
#define __IPSI_NO_DES_CBC_ENC__
#define __IPSI_NO_DES_CFB_ENC__
#define __IPSI_NO_DES_OFB_ENC__
#define __IPSI_NO_DES_EDE_ECB_ENC__
#define __IPSI_NO_DES_EDE_CBC_ENC__
#define __IPSI_NO_DES_EDE_CFB_ENC__
#define __IPSI_NO_DES_EDE_OFB_ENC__
#define __IPSI_NO_DES_EDE3_ECB_ENC__
#define __IPSI_NO_DES_EDE3_CBC_ENC__
#define __IPSI_NO_DES_EDE3_CFB_ENC__
#define __IPSI_NO_DES_EDE3_OFB_ENC__
#define __IPSI_NO_AES128_ECB_ENC__
#define __IPSI_NO_AES128_CFB_ENC__
#define __IPSI_NO_AES128_OFB_ENC__
#define __IPSI_NO_AES192_ECB_ENC__
#define __IPSI_NO_AES192_CFB_ENC__
#define __IPSI_NO_AES192_OFB_ENC__
#define __IPSI_NO_AES256_ECB_ENC__
#define __IPSI_NO_AES256_CFB_ENC__
#define __IPSI_NO_AES256_OFB_ENC__
#define __IPSI_NO_RC2__
#define __IPSI_NO_KASUMI_ECB_ENC__
#define __IPSI_NO_KASUMI_CBC_ENC__
#define __IPSI_NO_KASUMI_CFB_ENC__
#define __IPSI_NO_KASUMI_OFB_ENC__
#define __IPSI_NO_RC4_ENC__

#define __IPSI_NO_BF_ECB_ENC__
#define __IPSI_NO_BF_CBC_ENC__
#define __IPSI_NO_BF_CFB_ENC__
#define __IPSI_NO_BF_OFB_ENC__

/* Symmetric decryption algorithm tailoring through crypto_func.c */
#define __IPSI_NO_DES_ECB_DCR__
#define __IPSI_NO_DES_CBC_DCR__
#define __IPSI_NO_DES_CFB_DCR__
#define __IPSI_NO_DES_OFB_DCR__
#define __IPSI_NO_DES_EDE_ECB_DCR__
#define __IPSI_NO_DES_EDE_CBC_DCR__
#define __IPSI_NO_DES_EDE_CFB_DCR__
#define __IPSI_NO_DES_EDE_OFB_DCR__
#define __IPSI_NO_DES_EDE3_ECB_DCR__
#define __IPSI_NO_DES_EDE3_CBC_DCR__
#define __IPSI_NO_DES_EDE3_CFB_DCR__
#define __IPSI_NO_DES_EDE3_OFB_DCR__
#define __IPSI_NO_AES128_ECB_DCR__
#define __IPSI_NO_AES128_CFB_DCR__
#define __IPSI_NO_AES128_OFB_DCR__
#define __IPSI_NO_AES192_ECB_DCR__
#define __IPSI_NO_AES192_CFB_DCR__
#define __IPSI_NO_AES192_OFB_DCR__
#define __IPSI_NO_AES256_ECB_DCR__
#define __IPSI_NO_AES256_CFB_DCR__
#define __IPSI_NO_AES256_OFB_DCR__
#define __IPSI_NO_RC2__
#define __IPSI_NO_RC4_DCR__

#define __IPSI_NO_BF_ECB_DCR__
#define __IPSI_NO_BF_CBC_DCR__
#define __IPSI_NO_BF_CFB_DCR__
#define __IPSI_NO_BF_OFB_DCR__

/*Removing the Blowfish Core implementation as well */
#define __IPSI_NO_BLOWFISH__



/* Symmetric opmode tailoring */
#define __IPSI_NO_SYM_CFB_DEC__
#define __IPSI_NO_SYM_CFB_ENC__
#define __IPSI_NO_SYM_ECB_DEC__
#define __IPSI_NO_SYM_ECB_ENC__
#define __IPSI_NO_SYM_OFB_ENC__
#define __IPSI_NO_SYM_OFB_DEC__

/* XCBC tailoring */
#define __IPSI_NO_AES_XCBC__
#define __IPSI_NO_XCBC_AES__

/* RNG tailoring */
#define __IPSI_NO_RNG__
#define __IPSI_NO_RNG_COREIMPL__
#define __IPSI_NO_RNG_SSL__

/* Key wrap tailoring */
#define __IPSI_NO_KEY_WRAP_UNWRAP__

/* Dot16 KDF tailoring */
#define __IPSI_NO_DOT16_KDF__

/* Hash tailoring */
#define __IPSI_NO_MD4__
#define __IPSI_NO_MD5__

#define __IPSI_NO_SHA224__
#define __IPSI_NO_SHA256__
#define __IPSI_NO_SHA384__
#define __IPSI_NO_SHA512__
#define __IPSI_NO_CORE_SHA224__

#define __IPSI_NO_CORE_SHA384__
#define __IPSI_NO_CORE_SHA512__
#define __IPSI_NO_CPLUS_SHA224__
#define __IPSI_NO_CPLUS_SHA384__
#define __IPSI_NO_CPLUS_SHA512__

/* HMAC tailoring */
#define __IPSI_NO_HMAC_MD4__
#define __IPSI_NO_HMAC_MD5__
#define __IPSI_NO_HMAC_SHA1__
#define __IPSI_NO_HMAC_SHA224__
#define __IPSI_NO_HMAC_SHA384__
#define __IPSI_NO_HMAC_SHA512__
#define __IPSI_NO_CORE_HMAC_SHA224__
#define __IPSI_NO_CORE_HMAC_SHA384__
#define __IPSI_NO_CORE_HMAC_SHA512__
#define __IPSI_NO_CPLUS_HMAC_SHA224__
#define __IPSI_NO_CPLUS_HMAC_SHA384__
#define __IPSI_NO_CPLUS_HMAC_SHA512__

/* CMAC tailoring */
#define __IPSI_NO_CMAC__
#define __IPSI_NO_CMAC_AES__
#define __IPSI_NO_CMAC_TDES__

/* Asymmetric tailoring */

/* Small crypto macros */
#define __IPSI_NO_BN_ENC_DEC__
#define __IPSI_NO_XBN__ 
#define __IPSI_NO_SMALL_BN__


#define __IPSI_NO_SMALL_SHA256__
#define __IPSI_NO_SMALL_ES__
#define __IPSI_NO_SMALL_SSA__
#define __IPSI_NO_SMALL_CPLUS__
#define __IPSI_NO_SMALL_KEY_ENC__
#define __IPSI_NO_SMALL_PKEY__
#define __IPSI_NO_KEY_ENC_DCR__
#define __IPSI_NO_ASYM_KEY_GEN__

/* Asymmetric RSA Encryption/Decryption Flag */
#define __IPSI_NO_RSA_ENC_DEC__
#define __IPSI_NO_RSA_ENC__
#define __IPSI_NO_RSA_DEC__
#define __IPSI_NO_RSA_GEN__
#define __IPSI_NO_RSA_PAD__

/* RSA Encode/Decode */
#define __IPSI_NO_RSA_KEY_ENC_DEC__
#define __IPSI_NO_RSA_KEY_ENC__
#define __IPSI_NO_RSA_PUB_KEY_ENC__
#define __IPSI_NO_RSA_PVT_KEY_ENC__
#define __IPSI_NO_RSA_PUB_KEY_DEC__
#define __IPSI_NO_RSA_KEY_PAIR_ENC__
#define __IPSI_NO_RSA_KEY_DEC__
#define __IPSI_NO_RSA_PUB_KEY_DEC__
#define __IPSI_NO_RSA_PVT_KEY_DEC__
#define __IPSI_NO_RSA_KEY_PAIR_DEC__

/* Asymmetric Key Flag */
#define __IPSI_NO_ASYM_KEY__
#define __IPSI_NO_ASYM_RSA_KEY__
#define __IPSI_NO_ASYM_DSA_KEY__
#define __IPSI_NO_ASYM_EC_KEY__
#define __IPSI_NO_ASYM_DH_KEY__
#define __IPSI_NO_ASYM_ECDH_KEY__
#define __IPSI_NO_ASYM_KEY_GEN__
#define __IPSI_NO_PKEY__
#define __IPSI_NO_KEY_ENC_DCR__
#define __IPSI_RSA_NOEXTENDEDKEYPAIR__
#define __IPSI_RSA_NOTIMER__


/* Asymmetric Sign Verify Flag */
#define __IPSI_NO_ASYM_SIGN__
#define __IPSI_NO_ASYM_RSA_SIGN__
#define __IPSI_NO_ASYM_DSA_SIGN__
#define __IPSI_NO_ASYM_ECDSA_SIGN__
#define __IPSI_NO_ASYM_SM2DSA_SIGN__
#define __IPSI_NO_ASYM_SIGN_VRF__ 
#define __IPSI_NO_ASYM_SIGN_VER__
#define __IPSI_NO_ASYM_RSA_SIGN_VRF__
#define __IPSI_NO_ASYM_DSA_SIGN_VRF__
#define __IPSI_NO_ASYM_ECDSA_SIGN_VRF__
#define __IPSI_NO_ASYM_SM2DSA_SIGN_VRF__
#define __IPSI_NO_ASYM_SSL_SIGN_VRF__ 

/* Asymmetric others */
#define __IPSI_NO_RSA__
#define __IPSI_NO_DSA__ 
#define __IPSI_NO_DH__
#define __IPSI_NO_EC__
#define __IPSI_NO_ECDH__
#define __IPSI_NO_ECDSA__
#define __IPSI_NO_XBN__
#define __IPSI_NO_CORE_BN__
#define __IPSI_NO_CORE_DH__
#define __IPSI_NO_DH_PARA__
#define __IPSI_NO_RSA_MGF__
#define __IPSI_NO_EC_POLY_CURVE__

/* Others */
#define __IPSI_NO_FEEDBACK__
#define __IPSI_NO_SET_IV__
#define __IPSI_NO_CRYPTO_ALG_UTILS__
#define __IPSI_NO_OCTEON_IMPL__
#define __IPSI_NO_SMALL_DIGEST__

#define __IPSI_NO_SYM_KEY_GEN__
#define __IPSI_NO_OAEP_CLASS__
#define __IPSI_NO_ERROR_LOG__
#define __IPSI_NO_BIN_LOG__
#define __IPSI_NO_SEC_LOG__
#define __IPSI_NO_CRYPTO_LOG__
#define __CRYPTO_NO_SEC_LIST__
#define __IPSI_NO_CORE_DES__


#define __IPSI_NO_CORE_ALGO_BUF__
#define __IPSI_NO_DIGEST__
#define __IPSI_NO_STREAM_CIPHER__
#define __IPSI_NO_LOCK__
#define __IPSI_NO_SYM_ENC__
#define __IPSI_NO_SYM_DEC__
#define __IPSI_NO_DES__
#define __IPSI_NO_BN__
#define __IPSI_NO_CRYPTO_UTILS__
#define __IPSI_DISABLE_GET_CRYPTO_VERSION__
#define __IPSI_DISABLE_DISPLAY_CRYPTO_VERSION__
#define __IPSI_NO_AVL__
#define __IPSI_NO_SEC_BIG_INT__
#define __IPSI_NO_HMAC__
#define __IPSI_NO_HASH__
#define __IPSI_NO_BN__
#define __IPSI_NO_SYM_PAD__

#define __IPSI_NO_DOT16KDF_CMAC__
#define __IPSI_NO_DOT16KDF_SHA1__
#define __IPSI_NO_CPLUS_HMAC_SHA256__
#define __IPSI_NO_CORE_AES_ENC__
#define __IPSI_NO_CORE_AES_ENC_IMPL__
#define __IPSI_NO_CORE_SHA256_INTERFACE__
#define __IPSI_NO_ASYM_COMMON_IFACE__
#define __IPSI_NO_HMAC_COMMON_IFACE__
#define __IPSI_CRYPTO_NO_ASSERTS__
#define __IPSI_NO_EC_PARAM_POINTS__
#define __IPSI_NO_SEC_DEF__
#define __IPSI_NO_PID__
#define __IPSI_NO_BITOP__
#define __IPSI_NO_CRYPTO_FUNC__
#define __IPSI_NO_CRYPTO_INIT__
#define __IPSI_NO_CRYPTO_MISC__
#define __IPSI_NO_MEM_CALLOC__
#define __IPSI_NO_ASYM_KEY_IMPL__
#define __IPSI_NO_BLOWFISH__

#define __IPSI_NO_KDF_SM3__
#define __IPSI_NO_SM3__
#define __IPSI_NO_HMAC_SM3__
#define __IPSI_NO_SM2__
#define __IPSI_NO_SM2DSA__
#define __IPSI_NO_KDF_SHA224__
#define __IPSI_NO_KDF_SHA256__
#define __IPSI_NO_KDF_SHA384__
#define __IPSI_NO_KDF_SHA512__
#define __IPSI_NO_SCRYPT
#define __IPSI_NO_OSSL_WRAP_BN__

#define __IPSI_NO_CORE_AES_GCM__
#define __IPSI_NO_AES_GCM_ENC__
#define __IPSI_NO_AES_GCM_DEC__
#define __IPSI_NO_AEAD_ENC__
#define __IPSI_NO_AEAD_DEC__
#define __IPSI_NO_AEAD__
#define __IPSI_NO_AEAD_IFACE__

#define __IPSI_NO_SYM_CTR_ENC_DEC__
#define __IPSI_NO_SYM_IFACE__
#define __IPSI_NO_RSA_SIGN_WITH_PVT_EXP__

#endif // __IPSI_MBSC_SMALL_CRYPTO__

#ifdef __IPSI_MBSC_SMALL_CRYPTO_VXWORKS_WRLINUX__

/* Symmetric core implementation algorithm tailoring */
#define __IPSI_NO_DOUBLE_DES_DEC__
#define __IPSI_NO_DOUBLE_DES_ENC__
#define __IPSI_NO_KASUMI__
#define __IPSI_NO_RC2__

/* Symmetric encryption algorithm tailoring through crypto_func.c */
#define __IPSI_NO_DES_ECB_ENC__
#define __IPSI_NO_DES_CBC_ENC__
#define __IPSI_NO_DES_CFB_ENC__
#define __IPSI_NO_DES_OFB_ENC__
#define __IPSI_NO_DES_EDE_ECB_ENC__
#define __IPSI_NO_DES_EDE_CBC_ENC__
#define __IPSI_NO_DES_EDE_CFB_ENC__
#define __IPSI_NO_DES_EDE_OFB_ENC__
#define __IPSI_NO_DES_EDE3_ECB_ENC__
#define __IPSI_NO_DES_EDE3_CBC_ENC__
#define __IPSI_NO_DES_EDE3_CFB_ENC__
#define __IPSI_NO_DES_EDE3_OFB_ENC__
#define __IPSI_NO_AES128_CFB_ENC__
#define __IPSI_NO_AES128_OFB_ENC__
#define __IPSI_NO_AES192_CFB_ENC__
#define __IPSI_NO_AES192_OFB_ENC__
#define __IPSI_NO_AES256_CFB_ENC__
#define __IPSI_NO_AES256_OFB_ENC__
#define __IPSI_NO_RC2__
#define __IPSI_NO_KASUMI_ECB_ENC__
#define __IPSI_NO_KASUMI_CBC_ENC__
#define __IPSI_NO_KASUMI_CFB_ENC__
#define __IPSI_NO_KASUMI_OFB_ENC__
#define __IPSI_NO_RC4_ENC__

#define __IPSI_NO_BF_ECB_ENC__
#define __IPSI_NO_BF_CBC_ENC__
#define __IPSI_NO_BF_CFB_ENC__
#define __IPSI_NO_BF_OFB_ENC__

/* Symmetric decryption algorithm tailoring through crypto_func.c */
#define __IPSI_NO_DES_ECB_DCR__
#define __IPSI_NO_DES_CBC_DCR__
#define __IPSI_NO_DES_CFB_DCR__
#define __IPSI_NO_DES_OFB_DCR__
#define __IPSI_NO_DES_EDE_ECB_DCR__
#define __IPSI_NO_DES_EDE_CBC_DCR__
#define __IPSI_NO_DES_EDE_CFB_DCR__
#define __IPSI_NO_DES_EDE_OFB_DCR__
#define __IPSI_NO_DES_EDE3_ECB_DCR__
#define __IPSI_NO_DES_EDE3_CBC_DCR__
#define __IPSI_NO_DES_EDE3_CFB_DCR__
#define __IPSI_NO_DES_EDE3_OFB_DCR__
#define __IPSI_NO_AES128_CFB_DCR__
#define __IPSI_NO_AES128_OFB_DCR__
#define __IPSI_NO_AES192_CFB_DCR__
#define __IPSI_NO_AES192_OFB_DCR__
#define __IPSI_NO_AES256_CFB_DCR__
#define __IPSI_NO_AES256_OFB_DCR__
#define __IPSI_NO_RC2__
#define __IPSI_NO_RC4_DCR__

#define __IPSI_NO_BF_ECB_DCR__
#define __IPSI_NO_BF_CBC_DCR__
#define __IPSI_NO_BF_CFB_DCR__
#define __IPSI_NO_BF_OFB_DCR__

/*Removing the Blowfish Core implementation as well */
#define __IPSI_NO_BLOWFISH__



/* Symmetric opmode tailoring */
#define __IPSI_NO_SYM_CFB_DEC__
#define __IPSI_NO_SYM_CFB_ENC__
#define __IPSI_NO_SYM_OFB_ENC__
#define __IPSI_NO_SYM_OFB_DEC__

/* XCBC tailoring */
#define __IPSI_NO_AES_XCBC__
#define __IPSI_NO_XCBC_AES__


/* Key wrap tailoring */
#define __IPSI_NO_KEY_WRAP_UNWRAP__

/* Dot16 KDF tailoring */
#define __IPSI_NO_DOT16_KDF__

/* Hash tailoring */
#define __IPSI_NO_MD4__
#define __IPSI_NO_MD5__

#define __IPSI_NO_SHA224__
#define __IPSI_NO_SHA256__
#define __IPSI_NO_SHA384__
#define __IPSI_NO_SHA512__
#define __IPSI_NO_CORE_SHA224__

#define __IPSI_NO_CORE_SHA384__
#define __IPSI_NO_CORE_SHA512__
#define __IPSI_NO_CPLUS_SHA224__
#define __IPSI_NO_CPLUS_SHA384__
#define __IPSI_NO_CPLUS_SHA512__

/* HMAC tailoring */
#define __IPSI_NO_HMAC_MD4__
#define __IPSI_NO_HMAC_MD5__
#define __IPSI_NO_HMAC_SHA1__
#define __IPSI_NO_HMAC_SHA224__
#define __IPSI_NO_HMAC_SHA384__
#define __IPSI_NO_HMAC_SHA512__
#define __IPSI_NO_CORE_HMAC_SHA224__
#define __IPSI_NO_CORE_HMAC_SHA384__
#define __IPSI_NO_CORE_HMAC_SHA512__
#define __IPSI_NO_CPLUS_HMAC_SHA224__
#define __IPSI_NO_CPLUS_HMAC_SHA384__
#define __IPSI_NO_CPLUS_HMAC_SHA512__

/* CMAC tailoring */
#define __IPSI_NO_CMAC__
#define __IPSI_NO_CMAC_AES__
#define __IPSI_NO_CMAC_TDES__

/* Asymmetric tailoring */

/* Small crypto macros */
#define __IPSI_NO_BN_ENC_DEC__
#define __IPSI_NO_XBN__ 
#define __IPSI_NO_SMALL_BN__


#define __IPSI_NO_SMALL_SHA256__
#define __IPSI_NO_SMALL_ES__
#define __IPSI_NO_SMALL_SSA__
#define __IPSI_NO_SMALL_KEY_ENC__
#define __IPSI_NO_SMALL_PKEY__
#define __IPSI_NO_KEY_ENC_DCR__
#define __IPSI_NO_ASYM_KEY_GEN__

/* Asymmetric RSA Encryption/Decryption Flag */
#define __IPSI_NO_RSA_ENC_DEC__
#define __IPSI_NO_RSA_ENC__
#define __IPSI_NO_RSA_DEC__
#define __IPSI_NO_RSA_GEN__
#define __IPSI_NO_RSA_PAD__

/* RSA Encode/Decode */
#define __IPSI_NO_RSA_KEY_ENC_DEC__
#define __IPSI_NO_RSA_KEY_ENC__
#define __IPSI_NO_RSA_PUB_KEY_ENC__
#define __IPSI_NO_RSA_PVT_KEY_ENC__
#define __IPSI_NO_RSA_PUB_KEY_DEC__
#define __IPSI_NO_RSA_KEY_PAIR_ENC__
#define __IPSI_NO_RSA_KEY_DEC__
#define __IPSI_NO_RSA_PUB_KEY_DEC__
#define __IPSI_NO_RSA_PVT_KEY_DEC__
#define __IPSI_NO_RSA_KEY_PAIR_DEC__

/* Asymmetric Key Flag */
#define __IPSI_NO_ASYM_KEY__
#define __IPSI_NO_ASYM_RSA_KEY__
#define __IPSI_NO_ASYM_DSA_KEY__
#define __IPSI_NO_ASYM_EC_KEY__
#define __IPSI_NO_ASYM_DH_KEY__
#define __IPSI_NO_ASYM_ECDH_KEY__
#define __IPSI_NO_ASYM_KEY_GEN__
#define __IPSI_NO_PKEY__
#define __IPSI_NO_KEY_ENC_DCR__
#define __IPSI_RSA_NOEXTENDEDKEYPAIR__
#define __IPSI_RSA_NOTIMER__


/* Asymmetric Sign Verify Flag */
#define __IPSI_NO_ASYM_SIGN__
#define __IPSI_NO_ASYM_RSA_SIGN__
#define __IPSI_NO_ASYM_DSA_SIGN__
#define __IPSI_NO_ASYM_ECDSA_SIGN__
#define __IPSI_NO_ASYM_SM2DSA_SIGN__
#define __IPSI_NO_ASYM_SIGN_VRF__ 
#define __IPSI_NO_ASYM_SIGN_VER__
#define __IPSI_NO_ASYM_RSA_SIGN_VRF__
#define __IPSI_NO_ASYM_DSA_SIGN_VRF__
#define __IPSI_NO_ASYM_ECDSA_SIGN_VRF__
#define __IPSI_NO_ASYM_SM2DSA_SIGN_VRF__
#define __IPSI_NO_ASYM_SSL_SIGN_VRF__ 

/* Asymmetric others */
#define __IPSI_NO_RSA__
#define __IPSI_NO_DSA__ 
#define __IPSI_NO_DH__
#define __IPSI_NO_EC__
#define __IPSI_NO_ECDH__
#define __IPSI_NO_ECDSA__
#define __IPSI_NO_XBN__
#define __IPSI_NO_CORE_BN__
#define __IPSI_NO_CORE_DH__
#define __IPSI_NO_DH_PARA__
#define __IPSI_NO_RSA_MGF__
#define __IPSI_NO_EC_POLY_CURVE__

/* Others */
#define __IPSI_NO_FEEDBACK__
#define __IPSI_NO_SET_IV__
#define __IPSI_NO_CRYPTO_ALG_UTILS__
#define __IPSI_NO_OCTEON_IMPL__

#define __IPSI_NO_SYM_KEY_GEN__
#define __IPSI_NO_OAEP_CLASS__
#define __IPSI_NO_ERROR_LOG__
#define __IPSI_NO_BIN_LOG__
#define __IPSI_NO_SEC_LOG__
#define __IPSI_NO_CRYPTO_LOG__
#define __CRYPTO_NO_SEC_LIST__
#define __IPSI_NO_CORE_DES__


#define __IPSI_NO_LOCK__
#define __IPSI_NO_BN__
#define __IPSI_NO_CRYPTO_UTILS__
#define __IPSI_NO_AVL__
#define __IPSI_NO_SEC_BIG_INT__
#define __IPSI_NO_HMAC__
#define __IPSI_NO_BN__

#define __IPSI_NO_DOT16KDF_CMAC__
#define __IPSI_NO_DOT16KDF_SHA1__
#define __IPSI_NO_CPLUS_HMAC_SHA256__
#define __IPSI_NO_CORE_AES_ENC__
#define __IPSI_NO_CORE_SHA256_INTERFACE__
#define __IPSI_NO_ASYM_COMMON_IFACE__
#define __IPSI_NO_HMAC_COMMON_IFACE__
#define __IPSI_CRYPTO_NO_ASSERTS__
#define __IPSI_NO_EC_PARAM_POINTS__
#define __IPSI_NO_SEC_DEF__
#define __IPSI_NO_PID__
#define __IPSI_NO_BITOP__
#define __IPSI_NO_CRYPTO_FUNC__
#define __IPSI_NO_MEM_CALLOC__
#define __IPSI_NO_ASYM_KEY_IMPL__
#define __IPSI_NO_BLOWFISH__

#define __IPSI_NO_KDF_SM3__
#define __IPSI_NO_SM3__
#define __IPSI_NO_HMAC_SM3__
#define __IPSI_NO_SM2__
#define __IPSI_NO_SM2DSA__
#define __IPSI_NO_KDF_SHA224__
#define __IPSI_NO_KDF_SHA256__
#define __IPSI_NO_KDF_SHA384__
#define __IPSI_NO_KDF_SHA512__
#define __IPSI_NO_SCRYPT
#define __IPSI_NO_OSSL_WRAP_BN__

#define __IPSI_NO_CORE_AES_GCM__
#define __IPSI_NO_AES_GCM_ENC__
#define __IPSI_NO_AES_GCM_DEC__
#define __IPSI_NO_AEAD_ENC__
#define __IPSI_NO_AEAD_DEC__
#define __IPSI_NO_AEAD__
#define __IPSI_NO_AEAD_IFACE__

#define __IPSI_NO_SYM_CTR_ENC_DEC__
#define __IPSI_NO_SYM_IFACE__
#define __IPSI_NO_RSA_SIGN_WITH_PVT_EXP__
#define __IPSI_NO_RNG__
#define __IPSI_NO_AES256_CBC_ENC__
#define __IPSI_NO_AES192_CBC_ENC__
#define __IPSI_NO_AES128_CBC_ENC__
#define __IPSI_NO_AES256_CBC_DCR__
#define __IPSI_NO_AES192_CBC_DCR__
#define __IPSI_NO_AES128_CBC_DCR__
#define __IPSI_NO_EXPOSED_DIGEST__
#define __IPSI_DISABLE_DISPLAY_CRYPTO_VERSION__

#endif // __IPSI_MBSC_SMALL_CRYPTO_VXWORKS_WRLINUX__


#ifdef __IPSI_CSC_SMALL_CRYPTO__

/* Symmetric core implementation algorithm tailoring */
#define __IPSI_NO_DOUBLE_DES_DEC__
#define __IPSI_NO_DOUBLE_DES_ENC__
#define __IPSI_NO_KASUMI__
#define __IPSI_NO_RC2__

/* Symmetric encryption algorithm tailoring through crypto_func.c */
#define __IPSI_NO_DES_ECB_ENC__
#define __IPSI_NO_DES_CBC_ENC__
#define __IPSI_NO_DES_CFB_ENC__
#define __IPSI_NO_DES_OFB_ENC__
#define __IPSI_NO_DES_EDE_ECB_ENC__
#define __IPSI_NO_DES_EDE_CBC_ENC__
#define __IPSI_NO_DES_EDE_CFB_ENC__
#define __IPSI_NO_DES_EDE_OFB_ENC__
#define __IPSI_NO_DES_EDE3_ECB_ENC__
#define __IPSI_NO_DES_EDE3_CBC_ENC__
#define __IPSI_NO_DES_EDE3_CFB_ENC__
#define __IPSI_NO_DES_EDE3_OFB_ENC__
#define __IPSI_NO_AES128_ECB_ENC__
#define __IPSI_NO_AES128_CFB_ENC__
#define __IPSI_NO_AES128_OFB_ENC__
#define __IPSI_NO_AES192_ECB_ENC__
#define __IPSI_NO_AES192_CFB_ENC__
#define __IPSI_NO_AES192_OFB_ENC__
#define __IPSI_NO_AES256_ECB_ENC__
#define __IPSI_NO_AES256_CFB_ENC__
#define __IPSI_NO_AES256_OFB_ENC__
#define __IPSI_NO_RC2__
#define __IPSI_NO_KASUMI_ECB_ENC__
#define __IPSI_NO_KASUMI_CBC_ENC__
#define __IPSI_NO_KASUMI_CFB_ENC__
#define __IPSI_NO_KASUMI_OFB_ENC__
#define __IPSI_NO_RC4_ENC__

#define __IPSI_NO_BF_ECB_ENC__
#define __IPSI_NO_BF_CBC_ENC__
#define __IPSI_NO_BF_CFB_ENC__
#define __IPSI_NO_BF_OFB_ENC__

/* Symmetric decryption algorithm tailoring through crypto_func.c */
#define __IPSI_NO_DES_ECB_DCR__
#define __IPSI_NO_DES_CBC_DCR__
#define __IPSI_NO_DES_CFB_DCR__
#define __IPSI_NO_DES_OFB_DCR__
#define __IPSI_NO_DES_EDE_ECB_DCR__
#define __IPSI_NO_DES_EDE_CBC_DCR__
#define __IPSI_NO_DES_EDE_CFB_DCR__
#define __IPSI_NO_DES_EDE_OFB_DCR__
#define __IPSI_NO_DES_EDE3_ECB_DCR__
#define __IPSI_NO_DES_EDE3_CBC_DCR__
#define __IPSI_NO_DES_EDE3_CFB_DCR__
#define __IPSI_NO_DES_EDE3_OFB_DCR__
#define __IPSI_NO_AES128_ECB_DCR__
#define __IPSI_NO_AES128_CFB_DCR__
#define __IPSI_NO_AES128_OFB_DCR__
#define __IPSI_NO_AES192_ECB_DCR__
#define __IPSI_NO_AES192_CFB_DCR__
#define __IPSI_NO_AES192_OFB_DCR__
#define __IPSI_NO_AES256_ECB_DCR__
#define __IPSI_NO_AES256_CFB_DCR__
#define __IPSI_NO_AES256_OFB_DCR__
#define __IPSI_NO_RC2__
#define __IPSI_NO_RC4_DCR__

#define __IPSI_NO_BF_ECB_DCR__
#define __IPSI_NO_BF_CBC_DCR__
#define __IPSI_NO_BF_CFB_DCR__
#define __IPSI_NO_BF_OFB_DCR__

/*Removing the Blowfish Core implementation as well */
#define __IPSI_NO_BLOWFISH__


/* Symmetric opmode tailoring */
#define __IPSI_NO_SYM_CFB_DEC__
#define __IPSI_NO_SYM_CFB_ENC__
#define __IPSI_NO_SYM_ECB_DEC__
#define __IPSI_NO_SYM_ECB_ENC__
#define __IPSI_NO_SYM_OFB_ENC__
#define __IPSI_NO_SYM_OFB_DEC__

/* XCBC tailoring */
#define __IPSI_NO_AES_XCBC__
#define __IPSI_NO_XCBC_AES__

/* RNG tailoring */
#define __IPSI_NO_RNG__
#define __IPSI_NO_RNG_COREIMPL__
#define __IPSI_NO_RNG_SSL__

/* Key wrap tailoring */
#define __IPSI_NO_KEY_WRAP_UNWRAP__

/* Dot16 KDF tailoring */
#define __IPSI_NO_DOT16_KDF__

/* Hash tailoring */
#define __IPSI_NO_MD4__
#define __IPSI_NO_MD5__


#define __IPSI_NO_SHA224__
#define __IPSI_NO_SHA256__
#define __IPSI_NO_SHA384__
#define __IPSI_NO_SHA512__
#define __IPSI_NO_CORE_SHA224__


#define __IPSI_NO_CORE_SHA384__
#define __IPSI_NO_CORE_SHA512__
#define __IPSI_NO_CPLUS_SHA224__
#define __IPSI_NO_CPLUS_SHA384__
#define __IPSI_NO_CPLUS_SHA512__



/* HMAC tailoring */
#define __IPSI_NO_HMAC_MD4__
#define __IPSI_NO_HMAC_MD5__
#define __IPSI_NO_HMAC_SHA1__
#define __IPSI_NO_HMAC_SHA224__
#define __IPSI_NO_HMAC_SHA384__
#define __IPSI_NO_HMAC_SHA512__
#define __IPSI_NO_HMAC_SHA256__
#define __IPSI_NO_CORE_HMAC_SHA224__
#define __IPSI_NO_CORE_HMAC_SHA384__
#define __IPSI_NO_CORE_HMAC_SHA512__
#define __IPSI_NO_CORE_HMAC_SHA256__
#define __IPSI_NO_CPLUS_HMAC_SHA224__
#define __IPSI_NO_CPLUS_HMAC_SHA384__
#define __IPSI_NO_CPLUS_HMAC_SHA512__
#define __IPSI_NO_CPLUS_HMAC_SHA256__

/* CMAC tailoring */
#define __IPSI_NO_CMAC__
#define __IPSI_NO_CMAC_AES__
#define __IPSI_NO_CMAC_TDES__

/* Asymmetric tailoring */

/* Small crypto macros */
#define __IPSI_NO_BN_ENC_DEC__
#define __IPSI_NO_XBN__ 
#define __IPSI_NO_SMALL_BN__


#define __IPSI_NO_SMALL_SHA256__
#define __IPSI_NO_SMALL_ES__
#define __IPSI_NO_SMALL_SSA__
#define __IPSI_NO_SMALL_CPLUS__
#define __IPSI_NO_SMALL_KEY_ENC__
#define __IPSI_NO_SMALL_PKEY__
#define __IPSI_NO_KEY_ENC_DCR__
#define __IPSI_NO_ASYM_KEY_GEN__

/* Asymmetric RSA Encryption/Decryption Flag */
#define __IPSI_NO_RSA_ENC_DEC__
#define __IPSI_NO_RSA_ENC__
#define __IPSI_NO_RSA_DEC__
#define __IPSI_NO_RSA_GEN__
#define __IPSI_NO_RSA_PAD__

/* RSA Encode/Decode */
#define __IPSI_NO_RSA_KEY_ENC_DEC__
#define __IPSI_NO_RSA_KEY_ENC__
#define __IPSI_NO_RSA_PUB_KEY_ENC__
#define __IPSI_NO_RSA_PVT_KEY_ENC__
#define __IPSI_NO_RSA_PUB_KEY_DEC__
#define __IPSI_NO_RSA_KEY_PAIR_ENC__
#define __IPSI_NO_RSA_KEY_DEC__
#define __IPSI_NO_RSA_PUB_KEY_DEC__
#define __IPSI_NO_RSA_PVT_KEY_DEC__
#define __IPSI_NO_RSA_KEY_PAIR_DEC__

/* Asymmetric Key Flag */
#define __IPSI_NO_ASYM_KEY__
#define __IPSI_NO_ASYM_RSA_KEY__
#define __IPSI_NO_ASYM_DSA_KEY__
#define __IPSI_NO_ASYM_EC_KEY__
#define __IPSI_NO_ASYM_DH_KEY__
#define __IPSI_NO_ASYM_ECDH_KEY__
#define __IPSI_NO_ASYM_KEY_GEN__
#define __IPSI_NO_PKEY__
#define __IPSI_NO_KEY_ENC_DCR__
#define __IPSI_RSA_NOEXTENDEDKEYPAIR__
#define __IPSI_RSA_NOTIMER__


/* Asymmetric Sign Verify Flag */
#define __IPSI_NO_ASYM_SIGN__
#define __IPSI_NO_ASYM_RSA_SIGN__
#define __IPSI_NO_ASYM_DSA_SIGN__
#define __IPSI_NO_ASYM_ECDSA_SIGN__
#define __IPSI_NO_ASYM_SM2DSA_SIGN__
#define __IPSI_NO_ASYM_SIGN_VRF__ 
#define __IPSI_NO_ASYM_SIGN_VER__
#define __IPSI_NO_ASYM_RSA_SIGN_VRF__
#define __IPSI_NO_ASYM_DSA_SIGN_VRF__
#define __IPSI_NO_ASYM_ECDSA_SIGN_VRF__
#define __IPSI_NO_ASYM_SM2DSA_SIGN_VRF__
#define __IPSI_NO_ASYM_SSL_SIGN_VRF__ 

/* Asymmetric others */
#define __IPSI_NO_RSA__
#define __IPSI_NO_DSA__ 
#define __IPSI_NO_DH__
#define __IPSI_NO_EC__
#define __IPSI_NO_ECDH__
#define __IPSI_NO_ECDSA__
#define __IPSI_NO_XBN__
#define __IPSI_NO_CORE_BN__
#define __IPSI_NO_CORE_DH__
#define __IPSI_NO_DH_PARA__
#define __IPSI_NO_RSA_MGF__
#define __IPSI_NO_EC_POLY_CURVE__

/* Others */
#define __IPSI_NO_FEEDBACK__
#define __IPSI_NO_SET_IV__
#define __IPSI_NO_CRYPTO_ALG_UTILS__
#define __IPSI_NO_OCTEON_IMPL__
#define __IPSI_NO_SMALL_DIGEST__

#define __IPSI_NO_SYM_KEY_GEN__
#define __IPSI_NO_OAEP_CLASS__
#define __IPSI_NO_ERROR_LOG__
#define __IPSI_NO_BIN_LOG__
#define __IPSI_NO_SEC_LOG__
#define __IPSI_NO_CRYPTO_LOG__
#define __CRYPTO_NO_SEC_LIST__
#define __IPSI_NO_CORE_DES__


#define __IPSI_NO_CORE_ALGO_BUF__
#define __IPSI_NO_DIGEST__
#define __IPSI_NO_STREAM_CIPHER__
#define __IPSI_NO_LOCK__
#define __IPSI_NO_SYM_ENC__
#define __IPSI_NO_SYM_DEC__
#define __IPSI_NO_DES__
#define __IPSI_NO_BN__
#define __IPSI_NO_CRYPTO_UTILS__
#define __IPSI_DISABLE_GET_CRYPTO_VERSION__
#define __IPSI_DISABLE_DISPLAY_CRYPTO_VERSION__
#define __IPSI_NO_AVL__
#define __IPSI_NO_SEC_BIG_INT__
#define __IPSI_NO_HMAC__
#define __IPSI_NO_HASH__
#define __IPSI_NO_BN__
#define __IPSI_NO_SYM_PAD__

/*Removing the Blowfish Core implementation as well */
#define __IPSI_NO_BLOWFISH__

#define __IPSI_NO_DOT16KDF_CMAC__
#define __IPSI_NO_DOT16KDF_SHA1__

#define __IPSI_NO_CORE_SHA256_INTERFACE__
#define __IPSI_NO_ASYM_COMMON_IFACE__
#define __IPSI_NO_HMAC_COMMON_IFACE__
#define __IPSI_CRYPTO_NO_ASSERTS__
#define __IPSI_NO_EC_PARAM_POINTS__
#define __IPSI_NO_SEC_DEF__
#define __IPSI_NO_PID__
#define __IPSI_NO_BITOP__
#define __IPSI_NO_CRYPTO_FUNC__
#define __IPSI_NO_CRYPTO_INIT__
#define __IPSI_NO_CRYPTO_MISC__
#define __IPSI_NO_MEM_CALLOC__
#define __IPSI_NO_ASYM_KEY_IMPL__


#define __IPSI_NO_KDF_SM3__
#define __IPSI_NO_SM3__
#define __IPSI_NO_HMAC_SM3__
#define __IPSI_NO_SM2__
#define __IPSI_NO_SM2DSA__
#define __IPSI_NO_KDF_SHA224__
#define __IPSI_NO_KDF_SHA256__
#define __IPSI_NO_KDF_SHA384__
#define __IPSI_NO_KDF_SHA512__
#define __IPSI_NO_SCRYPT
#define __IPSI_NO_OSSL_WRAP_BN__

#define __IPSI_NO_CORE_AES_GCM__
#define __IPSI_NO_AES_GCM_ENC__
#define __IPSI_NO_AES_GCM_DEC__
#define __IPSI_NO_AEAD_ENC__
#define __IPSI_NO_AEAD_DEC__
#define __IPSI_NO_AEAD__
#define __IPSI_NO_AEAD_IFACE__

#define __IPSI_NO_SYM_CTR_ENC_DEC__
#define __IPSI_NO_SYM_IFACE__

#define __IPSI_NO_RSA_SIGN_WITH_PVT_EXP__


#endif // __IPSI_CSC_SMALL_CRYPTO__

#ifdef __IPSI_VRP_SMALL_CRYPTO__

#define __IPSI_NO_SHA512__
#define __IPSI_NO_SHA384__
#define __IPSI_NO_MD4__
#define __IPSI_NO_CPLUS_SHA384__
#define __IPSI_NO_CPLUS_SHA512__
#define __IPSI_NO_CORE_SHA384__
#define __IPSI_NO_CORE_SHA512__

#define __IPSI_NO_HMAC_SHA384__
#define __IPSI_NO_HMAC_SHA512__
#define __IPSI_NO_HMAC_MD4__
#define __IPSI_NO_CPLUS_HMAC_SHA384__
#define __IPSI_NO_CPLUS_HMAC_SHA512__
#define __IPSI_NO_CORE_HMAC_SHA384__
#define __IPSI_NO_CORE_HMAC_SHA512__

#define __IPSI_NO_CMAC__ 
#define __IPSI_NO_CMAC_AES__ 
#define __IPSI_NO_CMAC_TDES__ 

#define __IPSI_NO_OCTEON_IMPL__
#define __IPSI_NO_KASUMI_OFB_ENC__
#define __IPSI_NO_KASUMI_CFB_ENC__ 
#define __IPSI_NO_KASUMI_CBC_ENC__ 
#define __IPSI_NO_KASUMI_ECB_ENC__

#define __IPSI_NO_EC__
#define __IPSI_NO_EC_PARAM_POINTS__
#define __IPSI_NO_ASYM_EC_KEY__
#define __IPSI_NO_ASYM_ECDH_KEY__
#define __IPSI_NO_ASYM_ECDSA_SIGN_VRF__
#define __IPSI_NO_ECDH__
#define __IPSI_NO_ECDSA__ 
#define __IPSI_NO_ASYM_ECDSA_SIGN__ 

#define __IPSI_NO_DES_CFB_ENC__ 
#define __IPSI_NO_DES_ECB_ENC__ 
#define __IPSI_NO_DES_OFB_ENC__ 
#define __IPSI_NO_DES_CFB_DCR__ 
#define __IPSI_NO_DES_ECB_DCR__ 
#define __IPSI_NO_DES_OFB_DCR__

#define __IPSI_NO_DES_EDE_CBC_ENC__ 
#define __IPSI_NO_DES_EDE_CFB_ENC__ 
#define __IPSI_NO_DES_EDE_ECB_ENC__ 
#define __IPSI_NO_DES_EDE_OFB_ENC__ 
#define __IPSI_NO_DES_EDE_CBC_DCR__ 
#define __IPSI_NO_DES_EDE_CFB_DCR__ 
#define __IPSI_NO_DES_EDE_ECB_DCR__ 
#define __IPSI_NO_DES_EDE_OFB_DCR__ 


#define __IPSI_NO_AES128_ECB_ENC__ 
#define __IPSI_NO_AES128_OFB_ENC__ 
#define __IPSI_NO_AES192_CFB_ENC__ 
#define __IPSI_NO_AES192_ECB_ENC__ 
#define __IPSI_NO_AES192_OFB_ENC__ 
#define __IPSI_NO_AES256_CFB_ENC__ 
#define __IPSI_NO_AES256_ECB_ENC__ 
#define __IPSI_NO_AES256_OFB_ENC__ 

#define __IPSI_NO_AES128_ECB_DCR__ 
#define __IPSI_NO_AES128_OFB_DCR__ 
#define __IPSI_NO_AES192_CFB_DCR__ 
#define __IPSI_NO_AES192_ECB_DCR__ 
#define __IPSI_NO_AES192_OFB_DCR__ 
#define __IPSI_NO_AES256_CFB_DCR__ 
#define __IPSI_NO_AES256_ECB_DCR__ 
#define __IPSI_NO_AES256_OFB_DCR__ 

#define __IPSI_NO_DES_EDE3_ECB_ENC__ 
#define __IPSI_NO_DES_EDE3_OFB_ENC__ 
#define __IPSI_NO_DES_EDE3_CFB_ENC__
#define __IPSI_NO_DES_EDE3_CFB_DCR__ 
#define __IPSI_NO_DES_EDE3_ECB_DCR__ 
#define __IPSI_NO_DES_EDE3_OFB_DCR__ 

#define __IPSI_NO_DOUBLE_DES_ENC__ 
#define __IPSI_NO_DOUBLE_DES_DEC__ 
#define __IPSI_NO_SYM_CFB_MODE__ 

#define __IPSI_NO_SYM_ECB_MODE__ 
#define __IPSI_NO_SYM_OFB_MODE__ 

#define __IPSI_NO_SYM_ECB_ENC__ 
#define __IPSI_NO_SYM_ECB_DEC__ 
#define __IPSI_NO_SYM_OFB_ENC__ 
#define __IPSI_NO_SYM_OFB_DEC__ 
#define __IPSI_NO_RC2__
#define __IPSI_NO_KDF__ 
#define __IPSI_NO_KEY_WRAP_UNWRAP__ 
#define __IPSI_NO_DOT16_KDF__ 
#define __IPSI_NO_DOT16KDF_CMAC__ 
#define __IPSI_NO_DOT16KDF_SHA1__ 
#define __IPSI_NO_AES_XCBC__ 
#define __IPSI_NO_XCBC_AES__ 

#define __IPSI_NO_EC_POLY_CURVE__ 
#define __IPSI_NO_EC_GF__ 
#define __IPSI_NO_SM2__
#define __IPSI_NO_SM2DSA__
#define __IPSI_NO_KDF_SM3__
#define __IPSI_NO_SM3__
#define __IPSI_NO_HMAC_SM3__
#define __IPSI_NO_KDF_SHA224__
#define __IPSI_NO_KDF_SHA256__
#define __IPSI_NO_KDF_SHA384__
#define __IPSI_NO_KDF_SHA512__
#define __IPSI_NO_SCRYPT
#define __IPSI_NO_OSSL_WRAP_BN__


#define __IPSI_NO_CORE_AES_GCM__
#define __IPSI_NO_AES_GCM_ENC__
#define __IPSI_NO_AES_GCM_DEC__
#define __IPSI_NO_AEAD_ENC__
#define __IPSI_NO_AEAD_DEC__
#define __IPSI_NO_AEAD__
#define __IPSI_NO_AEAD_IFACE__

#define __IPSI_NO_SYM_CTR_ENC_DEC__
#define __IPSI_NO_SYM_IFACE__

#define __IPSI_NO_RSA_SIGN_WITH_PVT_EXP__

#define __IPSI_LOG_LVL__ 4 
#define __LOG_LVL__ 4
#define __IPSI_NO_CRYPTO_LOG__
#define __IPSI_NO_BIN_LOG__

/*Removing the Blowfish Core implementation as well */
#define __IPSI_NO_BLOWFISH__

#define __IPSI_NO_BF_ECB_DCR__
#define __IPSI_NO_BF_CBC_DCR__
#define __IPSI_NO_BF_CFB_DCR__
#define __IPSI_NO_BF_OFB_DCR__

#define __IPSI_NO_BF_ECB_ENC__
#define __IPSI_NO_BF_CBC_ENC__
#define __IPSI_NO_BF_CFB_ENC__
#define __IPSI_NO_BF_OFB_ENC__


#endif
#ifdef __IPSI_IWF_SMALL_LIB__
    #define __IPSI_NO_SHA_64BIT
    #define __IPSI_NO_CPLUS_SHA384__
    #define __IPSI_NO_CPLUS_SHA512__
    #define __IPSI_NO_CORE_SHA384__
    #define __IPSI_NO_CORE_SHA512__
    #define __IPSI_NO_CPLUS_HMAC_SHA384__
    #define __IPSI_NO_CORE_HMAC_SHA384__
    #define __IPSI_NO_CPLUS_HMAC_SHA512__
    #define __IPSI_NO_CORE_HMAC_SHA512__
    #define __IPSI_NO_KDF_SHA384__
    #define __IPSI_NO_KDF_SHA512__
    #define __IPSI_NO_SHA512__
    #define __IPSI_NO_SHA384__
    #define __IPSI_NO_MD4__
    #define __IPSI_NO_CPLUS_SHA384__
    #define __IPSI_NO_CPLUS_SHA512__
    #define __IPSI_NO_CORE_SHA384__
    #define __IPSI_NO_CORE_SHA512__
    #define __IPSI_NO_HMAC_SHA384__
    #define __IPSI_NO_HMAC_SHA512__
    #define __IPSI_NO_HMAC_MD4__
    #define __IPSI_NO_CPLUS_HMAC_SHA384__
    #define __IPSI_NO_CPLUS_HMAC_SHA512__
    #define __IPSI_NO_CORE_HMAC_SHA384__
    #define __IPSI_NO_CORE_HMAC_SHA512__
    #define __IPSI_NO_CMAC__ 
    #define __IPSI_NO_CMAC_AES__ 
    #define __IPSI_NO_CMAC_TDES__ 
    #define __IPSI_NO_KASUMI_OFB_ENC__
    #define __IPSI_NO_KASUMI_CFB_ENC__ 
    #define __IPSI_NO_KASUMI_CBC_ENC__ 
    #define __IPSI_NO_KASUMI_ECB_ENC__
    #define __IPSI_NO_OCTEON_IMPL__ 
    #define __IPSI_NO_EC__
    #define __IPSI_NO_EC_PARAM_POINTS__
    #define __IPSI_NO_ASYM_EC_KEY__
    #define __IPSI_NO_ASYM_ECDH_KEY__
    #define __IPSI_NO_ASYM_ECDSA_SIGN_VRF__
    #define __IPSI_NO_ECDH__
    #define __IPSI_NO_ECDSA__ 
    #define __IPSI_NO_ASYM_ECDSA_SIGN__ 
    #define __IPSI_NO_EC_POLY_CURVE__ 
    #define __IPSI_NO_EC_GF__ 
    #define __IPSI_NO_DES_CFB_ENC__ 
    #define __IPSI_NO_DES_ECB_ENC__ 
    #define __IPSI_NO_DES_OFB_ENC__ 
    #define __IPSI_NO_DES_CFB_DCR__ 
    #define __IPSI_NO_DES_ECB_DCR__ 
    #define __IPSI_NO_DES_OFB_DCR__
    #define __IPSI_NO_DES_EDE_CBC_ENC__ 
    #define __IPSI_NO_DES_EDE_CFB_ENC__ 
    #define __IPSI_NO_DES_EDE_ECB_ENC__ 
    #define __IPSI_NO_DES_EDE_OFB_ENC__ 
    #define __IPSI_NO_DES_EDE_CBC_DCR__ 
    #define __IPSI_NO_DES_EDE_CFB_DCR__ 
    #define __IPSI_NO_DES_EDE_ECB_DCR__ 
    #define __IPSI_NO_DES_EDE_OFB_DCR__ 
    #define __IPSI_NO_DES_EDE3_ECB_ENC__ 
    #define __IPSI_NO_DES_EDE3_OFB_ENC__ 
    #define __IPSI_NO_DES_EDE3_CFB_ENC__
    #define __IPSI_NO_DES_EDE3_CFB_DCR__ 
    #define __IPSI_NO_DES_EDE3_ECB_DCR__ 
    #define __IPSI_NO_DES_EDE3_OFB_DCR__ 
    #define __IPSI_NO_SYM_CFB_MODE__ 
    #define __IPSI_NO_SYM_ECB_MODE__ 
    #define __IPSI_NO_SYM_OFB_MODE__ 
    #define __IPSI_NO_SYM_AES128_CFB_MODE__
    #define __IPSI_NO_SYM_CFB_ENC__ 
    #define __IPSI_NO_SYM_CFB_DEC__ 
    #define __IPSI_NO_SYM_ECB_ENC__ 
    #define __IPSI_NO_SYM_ECB_DEC__ 
    #define __IPSI_NO_SYM_OFB_ENC__ 
    #define __IPSI_NO_SYM_OFB_DEC__ 
    #define __IPSI_NO_AES128_CFB_ENC__ 
    #define __IPSI_NO_AES128_ECB_ENC__ 
    #define __IPSI_NO_AES128_OFB_ENC__ 
    #define __IPSI_NO_AES192_CFB_ENC__ 
    #define __IPSI_NO_AES192_ECB_ENC__ 
    #define __IPSI_NO_AES192_OFB_ENC__ 
    #define __IPSI_NO_AES256_CFB_ENC__ 
    #define __IPSI_NO_AES256_ECB_ENC__ 
    #define __IPSI_NO_AES256_OFB_ENC__ 
    #define __IPSI_NO_AES128_CFB_DCR__ 
    #define __IPSI_NO_AES128_ECB_DCR__ 
    #define __IPSI_NO_AES128_OFB_DCR__ 
    #define __IPSI_NO_AES192_CFB_DCR__ 
    #define __IPSI_NO_AES192_ECB_DCR__ 
    #define __IPSI_NO_AES192_OFB_DCR__ 
    #define __IPSI_NO_AES256_CFB_DCR__ 
    #define __IPSI_NO_AES256_ECB_DCR__ 
    #define __IPSI_NO_AES256_OFB_DCR__ 
    #define __IPSI_NO_DOUBLE_DES_ENC__ 
    #define __IPSI_NO_DOUBLE_DES_DEC__ 
    #define __IPSI_NO_RC2__
    #define __IPSI_NO_KEY_WRAP_UNWRAP__
    #define __IPSI_NO_DOT16_KDF__ 
    #define __IPSI_NO_DOT16KDF_CMAC__ 
    #define __IPSI_NO_DOT16KDF_SHA1__ 
    #define __IPSI_NO_AES_XCBC__ 
    #define __IPSI_NO_XCBC_AES__ 
    #define __IPSI_NO_FEEDBACK__ 
    #define __IPSI_NO_SM2__
    #define __IPSI_NO_SM2DSA__
    #define __IPSI_NO_KDF_SM3__
    #define __IPSI_NO_SM3__
    #define __IPSI_NO_HMAC_SM3__
    #define __IPSI_NO_KDF_SHA224__
    #define __IPSI_NO_KDF_SHA256__
    #define __IPSI_NO_KDF_SHA384__
    #define __IPSI_NO_KDF_SHA512__
    #define __IPSI_NO_SCRYPT
    #define __IPSI_NO_SEC_64BIT
    #define __IPSI_NO_OSSL_WRAP_BN__
    #define __IPSI_LOG_LVL__ 5
    #define __LOG_LVL__ 5
    #define __IPSI_NO_CRYPTO_LOG__
    #define __IPSI_NO_BIN_LOG__

    #define __IPSI_NO_CORE_AES_GCM__
    #define __IPSI_NO_AES_GCM_ENC__
    #define __IPSI_NO_AES_GCM_DEC__
    #define __IPSI_NO_AEAD_ENC__
    #define __IPSI_NO_AEAD_DEC__
    #define __IPSI_NO_AEAD__
    #define __IPSI_NO_AEAD_IFACE__

    #define __IPSI_NO_SYM_CTR_ENC_DEC__
    #define __IPSI_NO_SYM_IFACE__

   
    #define __IPSI_NO_BF_ECB_DCR__
    #define __IPSI_NO_BF_CBC_DCR__
    #define __IPSI_NO_BF_CFB_DCR__
    #define __IPSI_NO_BF_OFB_DCR__

    #define __IPSI_NO_BF_ECB_ENC__
    #define __IPSI_NO_BF_CBC_ENC__
    #define __IPSI_NO_BF_CFB_ENC__
    #define __IPSI_NO_BF_OFB_ENC__

	/*Removing the Blowfish Core implementation as well */
    #define __IPSI_NO_BLOWFISH__
    
    #define __IPSI_NO_RSA_SIGN_WITH_PVT_EXP__
    
#endif // __IPSI_IWF_SMALL_LIB__

#ifdef __IPSI_HERT_REDUCED_CRYPTO__
#define __IPSI_NO_KDF_SM3__
#define __IPSI_NO_SM3__
#define __IPSI_NO_HMAC_SM3__
#define __IPSI_NO_SM2__
#define __IPSI_NO_SM2DSA__
#define __IPSI_NO_KDF_SHA224__
#define __IPSI_NO_KDF_SHA256__
#define __IPSI_NO_KDF_SHA384__
#define __IPSI_NO_KDF_SHA512__
#define __IPSI_NO_SCRYPT
#define __IPSI_NO_OSSL_WRAP_BN__

#define __IPSI_NO_CORE_AES_GCM__
#define __IPSI_NO_AES_GCM_ENC__
#define __IPSI_NO_AES_GCM_DEC__
#define __IPSI_NO_AEAD_ENC__
#define __IPSI_NO_AEAD_DEC__
#define __IPSI_NO_AEAD__
#define __IPSI_NO_AEAD_IFACE__

#define __IPSI_NO_SYM_CTR_ENC_DEC__
#define __IPSI_NO_SYM_IFACE__
#define __IPSI_NO_DES_EDE3_CBCM__
#define __IPSI_NO_RSA_SIGN_WITH_PVT_EXP__

/*Removing the Blowfish Core implementation as well */
#define __IPSI_NO_BLOWFISH__

#define __IPSI_NO_BF_ECB_DCR__
#define __IPSI_NO_BF_CBC_DCR__
#define __IPSI_NO_BF_CFB_DCR__
#define __IPSI_NO_BF_OFB_DCR__

#define __IPSI_NO_BF_ECB_ENC__
#define __IPSI_NO_BF_CBC_ENC__
#define __IPSI_NO_BF_CFB_ENC__
#define __IPSI_NO_BF_OFB_ENC__

#endif

#ifdef __IPSI_ANDROID_CRYPTO__
#define __IPSI_NO_MD4__
#define __IPSI_NO_MD5__
#define __IPSI_NO_SHA256__
#define __IPSI_NO_SHA512__
#define __IPSI_NO_SHA384__
#define __IPSI_NO_SHA224__
#define __IPSI_NO_CORE_SHA224__
#define __IPSI_NO_CORE_SHA256__
#define __IPSI_NO_CORE_SHA384__
#define __IPSI_NO_CORE_SHA512__
#define __IPSI_NO_ASYM_DSA_KEY__
#define __IPSI_NO_DH__
#define __IPSI_NO_ASYM_DH_KEY__
#define __IPSI_NO_ECDH__
#define __IPSI_NO_ASYM_ECDH_KEY__
#define __IPSI_NO_CORE_DH__
#define __IPSI_RSA_NOEXTENDEDKEYPAIR__

#define __IPSI_NO_BIN_LOG__
#define __IPSI_NO_AVL__
#define __IPSI_NO_ERROR_LOG__
#define __IPSI_NO_LOCK__
#define __IPSI_NO_CRYPTO_LOG__
#define __CRYPTO_NO_SEC_LIST__

#define __IPSI_NO_KDF_SM3__
#define __IPSI_NO_SM3__
#define __IPSI_NO_HMAC_SM3__
#define __IPSI_NO_SM2__
#define __IPSI_NO_SM2DSA__
#define __IPSI_NO_KDF_SHA224__
#define __IPSI_NO_KDF_SHA256__
#define __IPSI_NO_KDF_SHA384__
#define __IPSI_NO_KDF_SHA512__
#define __IPSI_NO_SCRYPT
#define __IPSI_NO_SYM_ALG__
#define __IPSI_NO_OSSL_WRAP_BN__


#define __IPSI_NO_CORE_AES_GCM__
#define __IPSI_NO_AES_GCM_ENC__
#define __IPSI_NO_AES_GCM_DEC__
#define __IPSI_NO_AEAD_ENC__
#define __IPSI_NO_AEAD_DEC__
#define __IPSI_NO_AEAD__
#define __IPSI_NO_AEAD_IFACE__

#define __IPSI_NO_SYM_CTR_ENC_DEC__
#define __IPSI_NO_SYM_IFACE__
#define __IPSI_NO_RSA_SIGN_WITH_PVT_EXP__

/*Removing the Blowfish Core implementation as well */
#define __IPSI_NO_BLOWFISH__

#define __IPSI_NO_BF_ECB_DCR__
#define __IPSI_NO_BF_CBC_DCR__
#define __IPSI_NO_BF_CFB_DCR__
#define __IPSI_NO_BF_OFB_DCR__

#define __IPSI_NO_BF_ECB_ENC__
#define __IPSI_NO_BF_CBC_ENC__
#define __IPSI_NO_BF_CFB_ENC__
#define __IPSI_NO_BF_OFB_ENC__

#endif //end of __IPSI_ANDROID_CRYPTO__

#ifdef __IPSI_NO_SYM_ALG__


#define __IPSI_NO_SYM_DEC__
#define __IPSI_NO_AES_XCBC__
#define __IPSI_NO_DH_PARA__
#define __IPSI_NO_XCBC_AES__

// Symmetric Encryption Flags
#define __IPSI_NO_DES_CBC_ENC__
#define __IPSI_NO_DES_CFB_ENC__
#define __IPSI_NO_DES_ECB_ENC__
#define __IPSI_NO_DES_OFB_ENC__
#define __IPSI_NO_DES_EDE_CBC_ENC__
#define __IPSI_NO_DES_EDE_CFB_ENC__
#define __IPSI_NO_DES_EDE_ECB_ENC__
#define __IPSI_NO_DES_EDE_OFB_ENC__
#define __IPSI_NO_DES_EDE3_CBC_ENC__
#define __IPSI_NO_DES_EDE3_CFB_ENC__
#define __IPSI_NO_DES_EDE3_ECB_ENC__
#define __IPSI_NO_DES_EDE3_OFB_ENC__
#define __IPSI_NO_AES128_CBC_ENC__
#define __IPSI_NO_AES192_CBC_ENC__
#define __IPSI_NO_AES256_CBC_ENC__
#define __IPSI_NO_AES128_CFB_ENC__
#define __IPSI_NO_AES128_ECB_ENC__
#define __IPSI_NO_AES128_OFB_ENC__
#define __IPSI_NO_AES192_CBC_ENC__
#define __IPSI_NO_AES192_CFB_ENC__
#define __IPSI_NO_AES192_ECB_ENC__
#define __IPSI_NO_AES192_OFB_ENC__
#define __IPSI_NO_AES256_CFB_ENC__
#define __IPSI_NO_AES256_ECB_ENC__
#define __IPSI_NO_AES256_OFB_ENC__
#define __IPSI_NO_KASUMI_CBC_ENC__
#define __IPSI_NO_KASUMI_CFB_ENC__
#define __IPSI_NO_KASUMI_ECB_ENC__
#define __IPSI_NO_KASUMI_OFB_ENC__
#define __IPSI_NO_CORE_AES__
#define __IPSI_NO_CORE_DES__
#define __IPSI_NO_DES__
#define __IPSI_NO_RC4_ENC__
#define __IPSI_NO_RC4_DCR__

#define __IPSI_NO_BF_ECB_ENC__
#define __IPSI_NO_BF_CBC_ENC__
#define __IPSI_NO_BF_CFB_ENC__
#define __IPSI_NO_BF_OFB_ENC__

/*Removing the Blowfish Core implementation as well */
#define __IPSI_NO_BLOWFISH__


// Symmetric Decryption Flags
#define __IPSI_NO_DES_CFB_DCR__
#define __IPSI_NO_DES_CBC_DCR__
#define __IPSI_NO_DES_ECB_DCR__
#define __IPSI_NO_DES_OFB_DCR__
#define __IPSI_NO_DES_EDE_CBC_DCR__
#define __IPSI_NO_DES_EDE_CFB_DCR__
#define __IPSI_NO_DES_EDE_ECB_DCR__
#define __IPSI_NO_DES_EDE_OFB_DCR__
#define __IPSI_NO_DES_EDE3_CBC_DCR__
#define __IPSI_NO_DES_EDE3_CFB_DCR__
#define __IPSI_NO_DES_EDE3_ECB_DCR__
#define __IPSI_NO_DES_EDE3_OFB_DCR__
#define __IPSI_NO_AES128_CBC_DCR__
#define __IPSI_NO_AES192_CBC_DCR__
#define __IPSI_NO_AES256_CBC_DCR__
#define __IPSI_NO_AES128_CFB_DCR__
#define __IPSI_NO_AES128_ECB_DCR__
#define __IPSI_NO_AES128_OFB_DCR__
#define __IPSI_NO_AES192_CBC_DCR__
#define __IPSI_NO_AES192_CFB_DCR__
#define __IPSI_NO_AES192_ECB_DCR__
#define __IPSI_NO_AES192_OFB_DCR__
#define __IPSI_NO_AES256_CFB_DCR__
#define __IPSI_NO_AES256_ECB_DCR__
#define __IPSI_NO_AES256_OFB_DCR__

#define __IPSI_NO_BF_ECB_DCR__
#define __IPSI_NO_BF_CBC_DCR__
#define __IPSI_NO_BF_CFB_DCR__
#define __IPSI_NO_BF_OFB_DCR__

#define __IPSI_NO_DOUBLE_DES_ENC__
#define __IPSI_NO_DOUBLE_DES_DEC__
#define __IPSI_NO_KASUMI__
#define __IPSI_NO_FEEDBACK__
#define __IPSI_NO_SET_IV__
#define __IPSI_NO_KEY_WRAP_UNWRAP__

// CMAC Flag
#define __IPSI_NO_CMAC__
#define __IPSI_NO_CMAC_AES__
#define __IPSI_NO_CMAC_TDES__

#define __IPSI_NO_SYM_CFB_MODE__
#define __IPSI_NO_SYM_AES128_CFB_MODE__
#define __IPSI_NO_SYM_ECB_MODE__
#define __IPSI_NO_SYM_OFB_MODE__

#define __IPSI_NO_SYM_CFB_DEC__
#define __IPSI_NO_SYM_CFB_ENC__
#define __IPSI_NO_SYM_ECB_DEC__
#define __IPSI_NO_SYM_ECB_ENC__
#define __IPSI_NO_SYM_OFB_ENC__
#define __IPSI_NO_SYM_OFB_DEC__
#define __IPSI_NO_RC2__
#define __IPSI_NO_KDF__
#define __IPSI_NO_HMAC__
#define __IPSI_NO_HMAC_MD4__
#define __IPSI_NO_HMAC_MD5__
#define __IPSI_NO_HMAC_SHA1__
#define __IPSI_NO_HMAC_SHA224__
#define __IPSI_NO_HMAC_SHA256__
#define __IPSI_NO_HMAC_SHA384__
#define __IPSI_NO_HMAC_SHA512__
#endif //end of __IPSI_NO_SYM_ALG__

/* As posix lock apis are not present in NSE environemnt commenting SEC logs and ipsi_lock */
#ifdef __IPSI_NSE_CRYPTO__
#define __IPSI_NO_SEC_LOG__
#define __IPSI_NO_LOCK__
#define __IPSI_NO_CRYPTO_LOG__
#define __IPSI_NO_DEBUG_SWITCH__
#define __IPSI_NO_ERROR_LOG__
#endif //__IPSI_NSE_CRYPTO__

#endif //__IPSI_CRYPTO_BUILDCONF_H__


