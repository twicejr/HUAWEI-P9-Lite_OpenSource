/******************************************************************************
 *
 *        Copyright 2003-2006  Huawei Technologies India Private Limited
 *                          All Rights Reserved
 *
 *------------------------------------------------------------------------------
 *                            ppmng_distribute.h
 *    Project Code:  VRP5.0
 *    Module Name:  IP6 PP
 *    Create Date:  2003/06/10
 *         Author:  Arun H S
 *     Description: 
 *------------------------------------------------------------------------------
 *  Modification History                                                        
 *  DATE        NAME             DESCRIPTION                                    
 * -----------------------------------------------------------------------------
 *  2003-06-10  Arun H S         Create
 ******************************************************************************/ 
#ifndef _IP6_PPMNGDISTRIBUTE_H
#define _IP6_PPMNGDISTRIBUTE_H

#ifdef __cplusplus
extern "C"{
#endif

/* Modified for GSR  arun/Rajesh BYAD10656*/
#define PPMNG_HDR2FLAG(ulNxtHdr,ulFlag) \
    switch(ulNxtHdr)\
    {\
        case IPPROTO_HOPOPTS: \
            ulFlag = IP6_PKT_HDR_EXT_HBH; \
            break;\
        case IPPROTO_FRAGMENT: \
            ulFlag = IP6_PKT_HDR_EXT_FRAG;\
            break;\
        case IPPROTO_DSTOPTS: \
            ulFlag = IP6_PKT_HDR_EXT_DST;\
            break;\
        case IPPROTO_ROUTING: \
            ulFlag = IP6_PKT_HDR_EXT_ROUTE;\
            break;\
        case IPPROTO_IPV6: \
            ulFlag = IP6_PKT_HDR_EXT_IPV6;\
            break;\
        case IPPROTO_ICMPV6:\
        case IPPROTO_RAW:\
        case IPPROTO_UDP: \
        case IPPROTO_TCP:\
            ulFlag = IP6_PKT_HDR_EXT_UL;\
            break;\
        default: \
            ulFlag = IP6_PKT_HDR_BASE;\
            break;\
    }


#define PPMNG_FLAG2HDR(ulFlag,ulNxtHdr) \
    switch(0xff000 & ulFlag)\
    {\
        case IP6_PKT_HDR_EXT_HBH: \
            ulNxtHdr = IPPROTO_HOPOPTS;\
            break;\
        case IP6_PKT_HDR_EXT_FRAG: \
            ulNxtHdr =  IPPROTO_FRAGMENT;\
            break;\
        case IP6_PKT_HDR_EXT_DST: \
            ulNxtHdr = IPPROTO_DSTOPTS; \
            break;\
        case IP6_PKT_HDR_EXT_ROUTE: \
            ulNxtHdr = IPPROTO_ROUTING;\
            break;\
        case IP6_PKT_HDR_EXT_IPV6: \
            ulNxtHdr = IPPROTO_IPV6;\
            break;\
        case IP6_PKT_HDR_EXT_UL: \
            ulNxtHdr = IP6_PKT_HDR_EXT_UL;\
            break;\
        case IP6_PKT_HDR_BASE: \
            ulNxtHdr = IP6_PKT_HDR_BASE; \
            break;\
        default: \
            ulNxtHdr = IP6_PKT_HDR_BASE; \
            break;\
    }


/* Prototypes Of the Functions in Distribute.c */
 ULONG IP6_PP_Protocol_Analyse (ULONG ulNxtHdr, UCHAR *pucDstOptions);
VOID IP6_PP_ProcessInMainBoard (MBUF_S *pstMBuf);
VOID IP6_PP_Distribute(MBUF_S *pstMBuf);
/* END: Prototypes Of the Functions in Distribute.c */

#ifdef __cplusplus
}
#endif

#endif 

