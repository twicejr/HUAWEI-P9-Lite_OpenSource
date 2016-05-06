/************************************************************************
 *
 *    Copyright 2003, Huawei Technologies Co. Ltd  India Institute  
 *                     ALL RIGHTS RESERVED                           
 *                                                 
 *----------------------------------------------------------------------*
 *
 *                             natpt_def.h
 *
 *  Project Code:       VRPv5 
 *  Create Date:        2003-7-15
 *  Author:             keshava   (VRPv5 IPv6 Team) 
 *  Document:
 *  Function Description:
 *  
 *----------------------------------------------------------------------*
 *  Modification History 
 *  DATE        NAME             DESCRIPTION
 *  2003-11-27  ArvindSaproo     For Defect BYAD02940
 *  2003-12-09  ArvindSaproo     For Defect BYAD04518
 *  2004-01-05  Usha             For Defect BYAD06308
 ************************************************************************/

#ifndef _NATPT_DEF_H_
#define _NATPT_DEF_H_


#ifdef  __cplusplus
extern  "C"{
#endif

#define u6_addr32  u6_uladdr
/*----------------------------------------------*
 * Header Files                
 *----------------------------------------------*/
/*----------------------------------------------*
 * External Variables            
 *----------------------------------------------*/

/*----------------------------------------------*
 * Global Variables    
 *----------------------------------------------*/

/*----------------------------------------------*
 * External Functions
 *----------------------------------------------*/

/*----------------------------------------------*
 * Functions
 *----------------------------------------------*/

#define NATPT_LOG_BUFFER_SIZE      512

#define NATPT_SM_SYN      1
#define NATPT_SM_FIN      2



#define NATPT_FRAG_FLAG                    0x01           /* Flag to indicate  fragment */
#define NATPT_MFLAG                        0x02           /* Flag to indicate M flag */
#define NATPT_PAT_FLAG                     0x04           /* Flag to indicate PATed address */ 
#define NATPT_DF_BIT                       0x08           /* Flag to indicate DF bit */
#define NATPT_INNER_IP                     0x10           /* Flag to indicate inner ip header creation */




#define NATPT_SET_FRAG_FLAG(ucFlag)(ucFlag |= NATPT_FRAG_FLAG)
#define NATPT_RESET_FRAG_FLAG(ucFlag)(ucFlag &= ~NATPT_FRAG_FLAG)
#define NATPT_IS_FRAG_FLAG_SET(ucFlag)(ucFlag & NATPT_FRAG_FLAG)
#define NATPT_SET_MFLAG(ucFlag)(ucFlag |= NATPT_MFLAG)
#define NATPT_IS_MFLAG_SET(ucFlag)(ucFlag & NATPT_MFLAG)
#define NATPT_SET_PAT_FLAG(ucFlag)(ucFlag |= NATPT_PAT_FLAG)
#define NATPT_IS_PAT_FLAG_SET(ucFlag)(ucFlag & NATPT_PAT_FLAG)
#define NATPT_SET_DF_BIT(ucFlag)(ucFlag |= NATPT_DF_BIT)
#define NATPT_IS_DF_BIT_SET(ucFlag)(ucFlag & NATPT_DF_BIT)
#define NATPT_SET_INNER_IP_BIT(ucFlag)(ucFlag |= NATPT_INNER_IP)
#define NATPT_IS_INNER_IP_BIT_SET(ucFlag)(ucFlag & NATPT_INNER_IP)

     

#define GET_NATPTINFO_FROMIF(pstIf)(((NATPTIF_S *)(pstIf->if_pstNatpt))?(NATPTIF_S *)(pstIf->if_pstNatpt):NULL)
#define NATPT_IS_IFENABLE(pstNatptIf)(pstNatptIf->usNatptEnableFlag & NATPT_ENABLE)
 /* For defect BYAD06308  */
#define NATPT_ENABLED_ON_INTERFACE(pstRcvIf,bRetVal)\
{\
    if (NULL != pstRcvIf)\
    {\
        NATPTIF_S *pstNatptIf = NULL;\
        pstNatptIf = GET_NATPTINFO_FROMIF (pstRcvIf);\
        bRetVal = (BOOL_T)(( NULL == pstNatptIf) ? BOOL_FALSE : NATPT_IS_IFENABLE(pstNatptIf));\
    }\
    else\
    {\
        bRetVal = BOOL_FALSE;\
    }\
}
 /* End of defect BYAD06308 */

#define NATPT_MAX_UNFRAGMENTED_V4PAYLOAD       1232



#define NATPT_ADD_FRAGMENT_HDR(pstPktChar) \
  (!(NATPT_IS_DF_BIT_SET(pstPktChar->ucFlag)) && \
    ((pstPktChar->ulV4PayloadLen <= NATPT_MAX_UNFRAGMENTED_V4PAYLOAD) || \
     (NATPT_IS_INNER_IP_BIT_SET(pstPktChar->ucFlag))))



#define NATPT_REFRSH_SM 3
#define NATPT_REFRESH_AM 7

#define NATPT_MAX_FRAG_COUNT 5000/*Maximum number of Fragmentation mapping entries allowed.*/

#define NATPT_INVALID_PORT 0
#define NATPT_INVALID_PRO 0

#define NATPT_INVALID_IFINDEX  0
#define NATPT_INVALID_V4ADDR   0

#define NATPT_LIB6_IS_ADDRESS_EQUAL( Dest, Src )      \
    ( ((Dest).u6_addr.u6_addr32[0] == (Src).u6_addr.u6_addr32[0]) \
     && ((Dest).u6_addr.u6_addr32[1] == (Src).u6_addr.u6_addr32[1]) \
     && ((Dest).u6_addr.u6_addr32[2] == (Src).u6_addr.u6_addr32[2]) \
     && ((Dest).u6_addr.u6_addr32[3] == (Src).u6_addr.u6_addr32[3]) )
     

/* 
 * V6Address must be a valid IPV6 address
 * return value: 
 *      1 -- pAddress is a NULL address
 *      0 -- pAddress isn't a NULL address
 */
#define NATPT_LIB6_IS_ADDRESS_NULL( V6Address )         \
    ( (0 == (V6Address).u6_addr.u6_addr32[0]) \
     && (0 == (V6Address).u6_addr.u6_addr32[1]) \
     && (0 == (V6Address).u6_addr.u6_addr32[2]) \
     && (0 == (V6Address).u6_addr.u6_addr32[3]) )


/* 
 * pAddress must be a V6 address
 * return value: 
 *      1 -- pAddress is a link-local address
 *      0 -- pAddress isn't a link-local address
 */
#define NATPT_LIB6_IS_ADDRESS_LINKLOCAL( V6Address )    \
    (0xFE800000 == (0xFFC00000&((V6Address.u6_addr.u6_addr32[0])) ))

/* 
 * V6Address must be a v6 address
 * return value: 
 *      1 -- pAddress is a site-local address
 *      0 -- pAddress isn't a site-local address
 */
#define NATPT_LIB6_IS_ADDRESS_SITELOCAL( V6Address )    \
     (0xFEC00000 == (0xFFC00000&((V6Address.u6_addr.u6_addr32[0])) ))

/* 
 * V6Address must be a V6 address 
 * return value: 
 *      1 -- pAddress is a loopback address
 *      0 -- pAddress isn't a loopback address
 */
#define NATPT_LIB6_IS_ADDRESS_LOOPBACK( V6Address )     \
    ( (0 == V6Address.u6_addr.u6_addr32[0]) \
     && (0 == V6Address.u6_addr.u6_addr32[1]) \
     && (0 == (V6Address.u6_addr.u6_addr32)[2]) \
     && (1 == V6Address.u6_addr.u6_addr32[3]) )


/* 
 * pAddress must be a V6 address
 * return value: 
 *      1 -- pAddress is a multicast address
 *      0 -- pAddress isn't a multicast address
 */
#define NATPT_LIB6_IS_ADDRESS_MULTICAST( V6Address )    \
    ( 0xFF000000 == (0xFF000000&(V6Address.u6_addr.u6_addr32[0])) )


/* x must be a V6 address*/
#define NATPT_LIB6_ADDRESS_NTOH(x) \
        {\
           x.u6_addr.u6_addr32[0] = VOS_NTOHL(x.u6_addr.u6_addr32[0]);\
           x.u6_addr.u6_addr32[1] = VOS_NTOHL(x.u6_addr.u6_addr32[1]);\
           x.u6_addr.u6_addr32[2] = VOS_NTOHL(x.u6_addr.u6_addr32[2]);\
           x.u6_addr.u6_addr32[3] = VOS_NTOHL(x.u6_addr.u6_addr32[3]);\
        }
           
    
/* x must be a V6 address*/
#define NATPT_LIB6_ADDRESS_HTON(x) \
        {\
           x.u6_addr.u6_addr32[0] = VOS_HTONL(x.u6_addr.u6_addr32[0]);\
           x.u6_addr.u6_addr32[1] = VOS_HTONL(x.u6_addr.u6_addr32[1]);\
           x.u6_addr.u6_addr32[2] = VOS_HTONL(x.u6_addr.u6_addr32[2]);\
           x.u6_addr.u6_addr32[3] = VOS_HTONL(x.u6_addr.u6_addr32[3]);\
        }

/* x  and y are arrays that have 4 ULONG element  */
#define NATPT_LIB6_ADDRESS_ARRAY_NTOH(x,y) \
        {\
           (x)[0] = VOS_NTOHL((y)[0]);\
           (x)[1] = VOS_NTOHL((y)[1]);\
           (x)[2] = VOS_NTOHL((y)[2]);\
           (x)[3] = VOS_NTOHL((y)[3]);\
        }
/* x and y are arrays that have 4 ULONG element */
#define NATPT_LIB6_ADDRESS_ARRAY_HTON(x,y) \
        {\
           (x)[0] = VOS_HTONL((y)[0]);\
           (x)[1] = VOS_HTONL((y)[1]);\
           (x)[2] = VOS_HTONL((y)[2]);\
           (x)[3] = VOS_HTONL((y)[3]);\
        } 

/* x and y are arrays that have 4 ULONG element */
#define NATPT_LIB6_ADDRESS_ARRAY_COPY(x,y) \
        {\
           (x)[0] = (y)[0];\
           (x)[1] = (y)[1];\
           (x)[2] = (y)[2];\
           (x)[3] = (y)[3];\
        }

/* x must be a V6 address*/
#define NATPT_LIB6_ADDRESS_ASSIGN_NTOH(x,y) \
        {\
           (x).u6_addr.u6_addr32[0] = VOS_NTOHL((y).u6_addr.u6_addr32[0]);\
           (x).u6_addr.u6_addr32[1] = VOS_NTOHL((y).u6_addr.u6_addr32[1]);\
           (x).u6_addr.u6_addr32[2] = VOS_NTOHL((y).u6_addr.u6_addr32[2]);\
           (x).u6_addr.u6_addr32[3] = VOS_NTOHL((y).u6_addr.u6_addr32[3]);\
        }
           
    
/* x must be a V6 address*/
#define NATPT_LIB6_ADDRESS_ASSIGN_HTON(x,y) \
        {\
           (x).u6_addr.u6_addr32[0] = VOS_HTONL((y).u6_addr.u6_addr32[0]);\
           (x).u6_addr.u6_addr32[1] = VOS_HTONL((y).u6_addr.u6_addr32[1]);\
           (x).u6_addr.u6_addr32[2] = VOS_HTONL((y).u6_addr.u6_addr32[2]);\
           (x).u6_addr.u6_addr32[3] = VOS_HTONL((y).u6_addr.u6_addr32[3]);\
        }

/*
 * Checks if the given /96 IPv6 Prefix is contained in the given IPv6 Address
 * Src - /96 V6 Prefix
 * Dest -  IPv6 address 
 * Return Value :
 *     1 - V6 Prefix is contained in the V6 Addr
 *     0 - V6 Addr does Not contain the V6 Prefix
 */

#define NATPT_LIB6_IS_PREFIX_PRESENT_IN_ADDRESS( Dest , Src )\
    (((Dest).u6_addr.u6_addr32[0] == (Src).u6_addr.u6_addr32[0])\
     && ((Dest).u6_addr.u6_addr32[1] == (Src).u6_addr.u6_addr32[1])\
     && ((Dest).u6_addr.u6_addr32[2] == (Src).u6_addr.u6_addr32[2]))



/* Dest and Src must V6 Addresses*/
#define NATPT_LIB6_ADDRESS_COPY( Dest, Src )  \
    {\
        (Dest).u6_addr.u6_addr32[0] = (Src).u6_addr.u6_addr32[0] ;\
        (Dest).u6_addr.u6_addr32[1] = (Src).u6_addr.u6_addr32[1] ;\
        (Dest).u6_addr.u6_addr32[2] = (Src).u6_addr.u6_addr32[2] ;\
        (Dest).u6_addr.u6_addr32[3] = (Src).u6_addr.u6_addr32[3] ;\
    }




#ifndef MAKE_TRACE_ID    
#define MAKE_TRACE_ID(fileID) (ULONG) fileID
#endif


#define NATPT_DIR_V6TOV4  0x01
#define NATPT_DIR_V4TOV6  0x02


#ifdef  __cplusplus
}
#endif



#endif


