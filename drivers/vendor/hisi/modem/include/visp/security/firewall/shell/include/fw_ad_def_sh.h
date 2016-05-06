/*************************************************************************
*
*              Copyright 2010, Huawei Technologies Co. Ltd.
*                          ALL RIGHTS RESERVED
*
*-----------------------------------------------------------------------*
*
*                              fw_ad_def_sh.h
*
*       Version: DOPRA VISP V1R8C03 Firewall
*   Module Name: inline function for firewall functionality
*  Date Created: 2010-01-13
*        Author: Kurt(z57669)
*   Description: This file contains the firewall functionality inline function.
*     Functions: AD_Land_Sh
*
*
*-----------------------------------------------------------------------*
*  Modification History
*  DATE            NAME            DESCRIPTION
*  2010-01-13      z57669          Created
************************************************************************/

#if (NAT_WVISP == 1)
#include "security/firewall/shell/cp/include/fw_ad_def_sh.h"
#elif (NAT_RPU == 1)
#include "security/firewall/shell/dp/include/fw_ad_def_sh.h"
#else

#ifndef _FW_AD_DEF_SH_H_
#define _FW_AD_DEF_SH_H_

/*This macro specifies the current number of entries in the array 'g_arrInboundBasicADTable',
that specifies the Basic Attack Defense mechanisms on the Inbound Interface.
Note : The macro should be updated inline with the changes in 'g_arrInboundBasicADTable'*/
#define INBOUNDBASICADTABLENUM 0

/*This macro specifies the current number of entries in the array 'g_arrOutboundBasicADTable',
that specifies the Basic Attack Defense mechanisms on the Outbound Interface.
Note : The macro should be updated inline with the changes in 'g_arrInboundBasicADTable'*/
#define OUTBOUNDBASICADTABLENUM 0

/*This macro specifies the current number of entries in the array 'g_arrInboundExtendedADTable',
that specifies the Extended Attack Defense mechanisms on the Inbound Interface.
Note : The macro should be updated inline with the changes in 'g_arrInboundBasicADTable'*/
#define INBOUNDEXTENDEDADTABLENUM 0

/*This macro specifies the current number of entries in the array 'g_arrOutboundExtendedADTable',
that specifies the Extended Attack Defense mechanisms on the Outbound Interface.
Note : The macro should be updated inline with the changes in 'g_arrInboundBasicADTable'*/
#define OUTBOUNDEXTENDEDADTABLENUM 0

/*This macro specifies the current number of entries in the array 'g_arrInboundFWTable',
that specifies the Firewall defense mechanisms on the Inbound Interface.
Note : The macro should be updated inline with the changes in 'g_arrInboundFWTable'*/
#define INBOUNDFWTABLENUM  0

/*This macro specifies the current number of entries in the array 'g_arrOutboundFWTable',
that specifies the Firewall defense mechanisms on the Outbound Interface.
Note : The macro should be updated inline with the changes in 'g_arrOutboundFWTable'*/
#define OUTBOUNDFWTABLENUM  0

#endif

#endif
