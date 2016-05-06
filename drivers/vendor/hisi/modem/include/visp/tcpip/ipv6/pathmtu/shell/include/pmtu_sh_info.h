/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : pmtu_sh_info.h
  Version       : Initial Draft
  Author        : Sandeep71635
  Created       : 2006/11/13
  Last Modified :
  Description   : defines entities for displayig error info on terminal
  Function List :
  History       :
  1.Date        : 2006/11/13
    Author      : Sandeep71635
    Modification: Created file
  2.Problem Number: AC4D00960     Author:Sandeep71635,   Date:2006/11/13
    Description    : Dynamic PMTU Entry is created for  ANMA, ARMA and SNMA
  3.Problem Number: AC4D01070     Author:Sandeep71635,   Date:2006/11/14
    Description    : PMTU Entry is created to a local address

******************************************************************************/

#ifndef _PMTU_HLP_H_
#define _PMTU_HLP_H_


#ifdef    __cplusplus
extern "C"{
#endif

/* For chinese/english info Inf_Pmtu_En OR g_Inf_Pmtu_Ch */
enum PMTU_ERROR_EN
{
    PMTU_ADDR_INVALID_UNSPECIFIED,

    /* PN:AC4D00960*/
    PMTU_ADDR_INVALID_LINKLOCAL_MULTICAST,
    PMTU_ADDR_INVALID_LOOPBACK,
    PMTU_ADDR_INVALID_V4ADDR,
    PMTU_ADDR_V4MAPPED_ADDR,
    PMTU_ADDR_INVALID,
    PMTU_NODE_DOES_NOT_EXISTS,
    PMTU_DYNAMIC_ENTRY_CANNOT_DEL,
    PMTU_MAX_CLI_ENTRIES,
    PMTU_MAX_ENTRIES,
    PMTU_NO_ENTRY_ROUTER,
    PMTU_NO_STATIC_ENTRY_ROUTER,
    PMTU_NO_DYNAMIC_ENTRY_ROUTER,
    PMTU_NO_ENTRY_GIVEN_ADDRESS,

    /* PN:AC4D01070*/
    PMTU_ADDR_OWN_ADDRESS,
    PMTU_ERROR_MAX_NO,
    IP6_PMTU_ERROR_EN_PAD = IP6_PMTU_MAX_ENUM_VALUE
};


#ifdef __cplusplus
}
#endif


#endif


