/***********************************
Copyright (C), 2010, Huawei Tech. Co., Ltd.
FileName: ipsi_pse_build_conf.h
Author: Sreenivasulu D
Version: 1
Creation Date: 2012-01-04
Description: This file controls the build configurations of PSE.
***********************************/

#ifndef __IPSI_PSE_BUILD_CONF_H__
#define __IPSI_PSE_BUILD_CONF_H__
#ifdef __IPSI_WLAN_SMALL_PSE__

//Disables PKI feature
#ifndef IPSI_SEC_NO_PKI
#define IPSI_SEC_NO_PKI
#endif

//Disables PSE features which are not used in SSL
#ifndef _SSL_
#define _SSL_
#endif

#ifndef IPSI_SEC_NO_PKI
#define IPSI_SEC_NO_PKI
#endif

#ifndef IPSI_NO_WPKI
#define IPSI_NO_WPKI
#endif

#ifndef __SEC_NO_SCEP__
#define __SEC_NO_SCEP__
#endif

#ifndef __IPSI_SEC_NO_SCEP__
#define __IPSI_SEC_NO_SCEP__
#endif

#ifndef __SEC_NO_OCSP__
#define __SEC_NO_OCSP__
#endif

#ifndef __SEC_PKI_NO_OCSP__
#define __SEC_PKI_NO_OCSP__
#endif

#ifndef __IPSI_SEC_NO_CERT_BUNDLE__
#define __IPSI_SEC_NO_CERT_BUNDLE__
#endif


#ifndef __IPSI_NO_CRYPTO_LOG__
#define __IPSI_NO_CRYPTO_LOG__
#endif

#ifndef __IPSI_NO_ERROR_LOG__
#define __IPSI_NO_ERROR_LOG__
#endif

#ifndef __SEC_PKI_NO_LOCK__
#define __SEC_PKI_NO_LOCK__
#endif

#ifdef __IPSI_CMPV2__
#undef __IPSI_CMPV2__
#endif

#ifdef __SEC_PKI__
#undef __SEC_PKI__
#endif

#ifndef __IPSI_NO_SM2__
#define __IPSI_NO_SM2__
#endif


#endif //__IPSI_WLAN_SMALL_PSE__

#ifdef __IPSI_NO_EC__
#define __IPSI_NO_SM2__
#endif

#ifdef __IPSI_VRP_SMALL_PSE__
#define __IPSI_SEC_NO_SCEP__ 
#define __SEC_PKI_NO_OCSP__   
#define __SEC_NO_OCSP__
#define __SEC_NO_SCEP__ 
#define IPSI_NO_WPKI 
#define __IPSI_NO_EC__ 
#define __IPSI_NO_CRMF__
#define __IPSI_NO_CMP__
#define __IPSI_NO_PKCS10__ 
#define IPSI_SEC_NO_PKI
#define __IPSI_SEC_NO_CERT_BUNDLE__
#undef __SEC_PKI__
#undef __IPSI_CMPV2__
#define __IPSI_LOG_LVL__ 4 
#define __LOG_LVL__ 4
#define __IPSI_NO_CRYPTO_LOG__
#define __IPSI_NO_SM2__

#endif //__IPSI_VRP_SMALL_PSE__

#ifdef __IPSI_IWF_SMALL_LIB__
    #define __IPSI_SEC_NO_SCEP__ 
    #define __SEC_PKI_NO_OCSP__   
    #define __SEC_NO_OCSP__
    #define __SEC_NO_SCEP__ 
    #define IPSI_NO_WPKI 
    #define __IPSI_NO_EC__ 
    #define __IPSI_NO_CRMF__
    #define __IPSI_NO_CMP__
    #define __IPSI_NO_PKCS10__ 
    #define IPSI_SEC_NO_PKI
    #define __IPSI_SEC_NO_CERT_BUNDLE__
    #undef __SEC_PKI__
    #undef __IPSI_CMPV2__
    #define __IPSI_LOG_LVL__ 5
    #define __LOG_LVL__ 5
    #define __IPSI_NO_CRYPTO_LOG__
    #define __IPSI_NO_SM2__
#endif //__IPSI_IWF_SMALL_LIB__

#endif //__IPSI_PSE_BUILD_CONF_H__
