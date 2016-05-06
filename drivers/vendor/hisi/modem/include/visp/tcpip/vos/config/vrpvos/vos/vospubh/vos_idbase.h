/************************************************************************
 *                                                                      *
 *                                                                      *
 *  Project Code:       VRP5.0                                          *
 *  Create Date:        2003/06/09                                      *
 *  Author:                                                             *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:                                                           *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 *  Copyright 2003-2005 VRP5.0 Team HITPL                               *  
 *                      ALL RIGHTS RESERVED                             *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *                                                                      *
 ************************************************************************/
#ifndef _VOS_IDBASE_H_
#define _VOS_IDBASE_H_

#ifndef _VRPCFG_H_
#error "Please include vrpcfg.h before this file."
#endif

#ifndef _VOS_ID_H_
#error "Please include vos_id.h before this file."
#endif


/********************************************************/
/*                  define the CID base                 */
/********************************************************/
#define CID_GLOBAL_BASE		0

#define CID_INTERNAL        100

#define CID_MPLS_BASE       ((CID_GLOBAL_BASE) + 1*(CID_INTERNAL))
#define CID_IPV6_BASE       ((CID_GLOBAL_BASE) + 2*(CID_INTERNAL))
#define CID_ROUT_BASE       ((CID_GLOBAL_BASE) + 3*(CID_INTERNAL))
#define CID_VPN_BASE        ((CID_GLOBAL_BASE) + 4*(CID_INTERNAL))

#define CID_IFNET_BASE      ((CID_GLOBAL_BASE) + 5*(CID_INTERNAL))
#define CID_SEC_QOS_BASE    ((CID_GLOBAL_BASE) + 6*(CID_INTERNAL))
#define CID_SCP_BASE        ((CID_GLOBAL_BASE) + 7*(CID_INTERNAL))

/*added by liuye 37514 for Multicast */
#define CID_ROUT_MRM    CID_ROUT_BASE + 12


/********************************************************/
/*                  define IID base                     */
/********************************************************/
#define IID_GLOBAL_BASE		0

#define IID_INTERNAL        100

#define IID_MPLS_BASE       ((IID_GLOBAL_BASE) + 1*(IID_INTERNAL))
#define IID_IPV6_BASE       ((IID_GLOBAL_BASE) + 2*(IID_INTERNAL))
#define IID_ROUT_BASE       ((IID_GLOBAL_BASE) + 3*(IID_INTERNAL))
#define IID_VPN_BASE        ((IID_GLOBAL_BASE) + 4*(IID_INTERNAL))

#define IID_IFNET_BASE      ((IID_GLOBAL_BASE) + 5*(IID_INTERNAL))
#define IID_SEC_QOS_BASE    ((IID_GLOBAL_BASE) + 6*(IID_INTERNAL))
#define IID_SCP_BASE        ((IID_GLOBAL_BASE) + 7*(IID_INTERNAL))

#endif/*End of the file. */

