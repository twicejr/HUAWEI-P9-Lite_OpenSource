/*************************************************************************
*
*              Copyright 2010, Huawei Technologies Co. Ltd.
*                          ALL RIGHTS RESERVED
*
*-----------------------------------------------------------------------*
*
*                              fw_sh_inl.h
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
*  2011-07-02 Eswar(72335)         VxWorks 6.8 on ARM processor has a problem
                                   with inline. So if it is ARM processor
                                   we will define the inline function in c file.
************************************************************************/

#if (NAT_WVISP == 1)
#include "security/firewall/shell/cp/include/fw_sh_inl.h"
#elif (NAT_RPU == 1)
#include "security/firewall/shell/dp/include/fw_sh_inl.h"
#else

#ifndef _FW_SH_INL_H_
#define _FW_SH_INL_H_

/*******************************************************************************
*    Func Name: AD_Land_Sh
*  Description: This function provides the Attack Defense against Land Attack.
*               It checks whether 
*               1. Source IP is equal to Destination IP
*                       or
*               2. Source IP is equal to Loopback address
*               for all packets coming from Interfaces other than itself. If this 
*               condition is met, then its considered as Land Attack.
*        Input: PFWCOMMON_IPPACKETINFO_S pstPacketInfo, struct of packet
*       Output: None
*       Return: AD_OK, no Land attack detected
*				ATCK_LAND_STAT, Land attack detected
*
*      Caution: This function will not check the validation of input parameter,
*               caller to this function should ensure the validation of input
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-24   r72335               create
*
*  2011-3-04    r72335               Implemented default functionality for land attack
*******************************************************************************/

/*VxWorks 6.8 on ARM processor has a problem with inline. So if it is ARM processor
  we will define the inline function in c file.*/
#ifdef IPSAFE_ACLFW_ARM

UINT32 AD_Land_Sh(PFWCOMMON_IPPACKETINFO_S pstPacketInfo);

#else


static inline UINT32 AD_Land_Sh(PFWCOMMON_IPPACKETINFO_S pstPacketInfo)
{
    /* check whether the source IP equal dst IP, or whether the source IP is a loopback address */
    if ((pstPacketInfo->u32SIP == pstPacketInfo->u32DIP)
        || ((pstPacketInfo->u32SIP >> 24) == 127))
    {
        return ATCK_LAND_STAT;
    }

    return AD_OK;
}

#endif

#endif

#endif
