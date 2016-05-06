/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ieth_inc.h
*
*  Project Code: VISPV100R005
*   Module Name: Etharp  
*  Date Created: 2004-3-12
*        Author: Zhang Hongyan(19316)
*   Description: Etharp core 的头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2004-3-12  Zhang Hongyan(19316)  Create the first version.
*  2006-4-27  wang xin(03278)       根据编程规范，对文件进行规范化整理
*******************************************************************************/

#ifdef    __cplusplus
extern    "C"{
#endif

#ifndef _IETH_INC_H
#define _IETH_INC_H
#include "tcpip/ifnet/include/ifnet_api.h"
#include "tcpip/ifnet/include/iifnet_inc.h"
#include "tcpip/ifnet/core/include/iifnet.h"

#include "tcpip/public/tcpip_ppi.h"
#include "tcpip/etharp/include/etharp_api.h"
#include "tcpip/etharp/core/include/etharp_pub_type.h"
#include "tcpip/etharp/core/include/etharp_core_api.h"
#include "tcpip/etharp/core/include/ieth.h"  

extern ComponentInfo *g_pCompEthInfo;

#endif


#ifdef    __cplusplus
}
#endif

