/***********************************
Copyright (C), 2012, Huawei Tech. Co., Ltd.
FileName: ipsi_ssl_build_conf.h
Author: Sreenivasulu D
Version: 1
Creation Date: 2012-01-03
Description: This file controls the build configurations of SSL.
***********************************/
#ifndef __IPSI_SSL_BUILD_CONF_H__
#define __IPSI_SSL_BUILD_CONF_H__

#ifdef __IPSI_WLAN_SMALL_SSL__

//Disables the SSL functionality
#ifndef IPSI_SSL_NO_SSL
#define IPSI_SSL_NO_SSL
#endif 

//Disables TLS12 support
#ifndef IPSI_NO_TLS12
#define IPSI_NO_TLS12
#endif

//Disables the RSA feature in SSL
#ifndef SSL_NO_RSA
#define SSL_NO_RSA
#endif

//Disables the DSA feature in SSL
#ifndef SSL_NO_DSA
#define SSL_NO_DSA
#endif

#ifndef SSL_NO_ECDSA
#define SSL_NO_ECDSA
#endif

//Disable the DH Keyexchange
#ifndef SSL_NO_DH
#define SSL_NO_DH
#endif

#ifndef SSL_NO_ECDH
#define SSL_NO_ECDH
#endif

//Disables the locks used in multithreading
#ifndef SSL_NO_LOCK
#define SSL_NO_LOCK
#endif

#ifndef __IPSI_NO_ERROR_LOG__
#define __IPSI_NO_ERROR_LOG__
#endif

#ifndef __IPSI_NO_CRYPTO_LOG__
#define __IPSI_NO_CRYPTO_LOG__
#endif

#ifndef TLS_NO_STRONG_LOG
#define TLS_NO_STRONG_LOG
#endif

#ifndef SSL_KLOC_UNUSED
#define SSL_KLOC_UNUSED
#endif

//Disables SSL v2 version support
#ifndef SSL_NO_SSL2
#define SSL_NO_SSL2
#endif

//Disables the compression feature in SSL
#ifndef SSL_NO_COMP
#define SSL_NO_COMP
#endif

//Disables the error loading feature
#ifndef SSL_NO_ERR
#define SSL_NO_ERR
#endif

#define IPSI_NO_TLS_EXP_KEYING_MATERIAL
#define IPSI_NO_SSL_GET_CURR_CIPH_ID

#endif//__IPSI_WLAN_SMALL_SSL__


#ifdef __IPSI_VRP_SMALL_SSL__

#define __IPSI_SEC_NO_SCEP__ 
#define __SEC_PKI_NO_OCSP__    
#define __SEC_NO_OCSP__ 
#define __SEC_NO_SCEP__ 
#define SSL_NO_PSK 
#define SSL_NO_DH_PSK 
#define SSL_NO_TLSEXT 
#define SSL_NO_COMP 
#define IPSI_NO_TLS12 
#define SSL_NO_ECDH  
#define SSL_NO_ECDSA 
#define IPSI_SSL_NO_DTLS 
#define SSL_NO_SSL2
#define SSL_NO_ERR
#define __IPSI_LOG_LVL__ 4 
#define __LOG_LVL__ 4
#define TLS_NO_STRONG_LOG
#define __IPSI_NO_CRYPTO_LOG__
#define IPSI_NO_TLS_EXP_KEYING_MATERIAL
#define IPSI_NO_SSL_GET_CURR_CIPH_ID

#endif

#ifdef __IPSI_IWF_SMALL_LIB__

    #define __IPSI_SEC_NO_SCEP__ 
    #define __SEC_PKI_NO_OCSP__    
    #define __SEC_NO_OCSP__ 
    #define __SEC_NO_SCEP__ 
    #define SSL_NO_PSK 
    #define SSL_NO_DH_PSK 
    #define SSL_NO_TLSEXT 
    #define SSL_NO_COMP 
    #define IPSI_NO_TLS12 
    #define SSL_NO_ECDH  
    #define SSL_NO_ECDSA 
    #define IPSI_SSL_NO_DTLS 
    #define __IPSI_NO_BIN_LOG__
    #define __IPSI_NO_CRYPTO_LOG__
    #define TLS_NO_STRONG_LOG
    #define __IPSI_LOG_LVL__ 5
    #define __LOG_LVL__ 5
    #define IPSI_NO_TLS_EXP_KEYING_MATERIAL
    #define IPSI_NO_SSL_GET_CURR_CIPH_ID    
#endif


#ifdef __IPSI_HERT_REDUCED_SSL__
#define IPSI_NO_TLS_EXP_KEYING_MATERIAL
#endif // __IPSI_HERT_REDUCED_SSL__




#endif //__IPSI_SSL_BUILD_CONF_H__

