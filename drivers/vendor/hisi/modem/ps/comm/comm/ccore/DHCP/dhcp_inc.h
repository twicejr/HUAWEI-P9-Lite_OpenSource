
#ifndef __DHCP_INC_H__
#define __DHCP_INC_H__

#if 0
#include "srv_common_inc.h"
#endif

#ifdef __WIN32_PLATFORM__
#ifdef PRODUCT_TYPE_HSGW
#include "hsgw_windows_stub.h"
#endif
#endif

#include "vos.h"
#include "v_lib.h"
#include "v_typdef.h"
#include "v_msg.h"

#ifndef _lint
typedef unsigned long   ULONG;
typedef unsigned short  USHORT;
#endif
typedef int             VOS_INTPTR;

#ifndef VOS_PACKED
#ifdef __WIN32_PLATFORM__
#define     VOS_PACKED
#else
#define     VOS_PACKED      __attribute__ ((__packed__))
#endif
#endif

#if 0
#include "ggsn_lock.h"
#include "pgp_ptm_stub.h"
#include "ptm_common.h"
#include "lap_api_pub.h"
#endif

#include "dhcp_spu_api.h"

#if 0
#include "dhcp_common_api.h"

#include "am_ptm_spu_api.h"
#include "pf_ptm_spu_api.h"
#include "pf_am_spu_api.h"
#include "ugw_ems_pub.h"
#include "ptm_logcnt.h"
#include "am_backup.h"
#include "am_trc_def_pub.h"
#include "sdb_context_adpt_api.h"
#include "lap_spu_api_am.h"
#include "li_api.h"
#endif



#define DHCP_INVALID_ULONG      0xFFFFFFFF
#define DHCP_INVALID_USHORT      0xFFFF

#define     DHCPS_GET_ROLE_INVALID 0
#define     DHCP_ENCAP_GTPV0   0
#define     DHCP_ENCAP_GTPV1  1
#define     DHCP_ENCAP_PMIP_GRE 2

#define     DHCP_IPUDP_HEAD_LENGTH  28


#define DHCP_Malloc(handle, memsize) PGP_MemAlloc(handle, (memsize))
#define DHCP_Free(handle, pBuf) PGP_MemFree(handle, pBuf);\
                                pBuf = NULL;
#define DHCP_MemZero(pBuf, len) PGP_MemZero(pBuf, len)


#define DHCP_RTDistributeAllocMsg(handle, msgLen) PGP_RTDistributeAllocMsg(handle, msgLen)
#define DHCP_RTDistributeSend(SrcCSI, DstCSI, Msg, Len, MsgType) PGP_RTDistributeSend(SrcCSI, DstCSI, Msg, Len, RTD_PRIORITY_MIDDLE,MsgType)
#define DHCP_RTDistributeFreeMsg(Msg) PGP_RTDistributeFreeMsg(Msg)



#endif /* end of __DHCP_INC_H__ */
