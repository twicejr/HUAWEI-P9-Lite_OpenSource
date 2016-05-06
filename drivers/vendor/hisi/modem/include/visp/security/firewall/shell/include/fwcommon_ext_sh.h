/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              fwcommon_ext_sh.h
*
*       Version: DOPRA VISP V1R8C02 Firewall
*   Module Name:
*  Date Created: 2009-08-10
*        Author: z57669
*   Description: define the internal data type for software forwarding which run
*      with control plane
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-7-27  z57669         Creat the first version.
*
*******************************************************************************/

#ifndef _FWCOMMON_EXT_SH_H_
#define _FWCOMMON_EXT_SH_H_

#ifdef  __cplusplus
extern "C" {
#endif

#include "security/apiinclude/fwipsafe.h"
#include "security/pub/include/fwipsafe_pub_inc.h"
          
#include "security/adp/include/fwcommon_msg_adaptor.h"

#include "security/firewall/core/common/include/sfe_fwcommon_inc.h"
#include "security/firewall/core/common/include/fwcommon_type.h"
#include "security/firewall/include/fw_inc.h"
#include "security/firewall/core/attack/include/ad_inc.h"

#include "security/firewall/core/whitelist/include/wls_func.h"
#include "security/firewall/core/blacklist/include/bls_func.h"

/*
#include "security/firewall/core/common/include/fwcommon_type.h"
#include "security/firewall/core/common/include/fwcommon_var.h"
*/
#ifdef  __cplusplus
}
#endif /*__cplusplus*/

#endif /*_FWCOMMON_EXT_SH_H_*/
