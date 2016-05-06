
/***********************************
Copyright (C), 2004, Huawei Tech. Co., Ltd.
FileName: sec_pki_buildconf.h
Author: Prabhat Kumar Gopalika
Version: 1
Creation Date: 2008-07-08
Description: This file controls the build configurations of PKI.
***********************************/
#include "ipsi_pse_build_conf.h"

#ifndef IPSI_SEC_NO_PKI


#ifndef __SEC_PKI_BUILDCONF_H__
#define __SEC_PKI_BUILDCONF_H__



//Enable Peer cert cache
#ifdef __SEC_PKI_NO_PEER_CACHE__
#undef __SEC_PKI_NO_PEER_CACHE__
#endif

//Enable multiple local cert support
#ifdef __SEC_PKI_NO_MULTIPLE_LOCAL_CERT__
#undef __SEC_PKI_NO_MULTIPLE_LOCAL_CERT__
#endif

//Enable Preshared Peer cert 
#ifdef __SEC_PKI_NO_PRESHARED_PEER_CERT__
#undef __SEC_PKI_NO_PRESHARED_PEER_CERT__
#endif

// Enable certificate bundle
#ifdef __IPSI_SEC_NO_CERT_BUNDLE__
#undef __IPSI_SEC_NO_CERT_BUNDLE__
#endif

#endif

#endif // IPSI_SEC_NO_PKI

