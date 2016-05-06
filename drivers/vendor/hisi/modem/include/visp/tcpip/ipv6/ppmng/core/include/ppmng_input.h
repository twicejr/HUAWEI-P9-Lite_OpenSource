/******************************************************************************
 *
 *        Copyright 2003-2006  Huawei Technologies India Private Limited
 *                          All Rights Reserved
 *
 *------------------------------------------------------------------------------
 *                            ppmng_input.h
 *    Project Code:  VRP5.0
 *    Module Name:  IP6 PP
 *    Create Date:  2003/06/10
 *         Author:  Arun H S
 *     Description: Packet Input Module of PP
 *------------------------------------------------------------------------------
 *  Modification History                                                        
 *  DATE        NAME             DESCRIPTION                                    
 *  ----------------------------------------------------------------------------
 *  2003-06-10  Arun H S         Create
 ******************************************************************************/ 
#ifndef _IP6_PPMNGINPUT_H
#define _IP6_PPMNGINPUT_H

#ifdef __cplusplus
extern "C"{
#endif

#define IS_PP_FE_FLAG_SET(x) (\
    (x & IP6_PKT_HDR_EXT_HBH)||\
    (x & IP6_PKT_HDR_EXT_FRAG)||\
    (x & IP6_PKT_HDR_EXT_DST)||\
    (x & IP6_PKT_HDR_EXT_ROUTE)||\
    (x & IP6_PKT_HDR_EXT_IPV6)||\
    (x & IP6_PKT_HDR_EXT_UL))

/* External Functions. */
/* END: External Functions. */

/* Prototypes Of the Functions in input.c */
MBUF_S *IP6_PP_CheckValidPkt (MBUF_S *pstMBuf);
VOID IP6_PP_Input (MBUF_S *pstMBuf);
/* END: Prototypes Of the Functions in input.c */
ULONG IP6_PP_IsAnycastAddress (IN6ADDR_S  stIn6Addr, ULONG ulPrefixLen);

#ifdef __cplusplus
}
#endif

#endif 

