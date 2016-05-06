/************************************************************************
 *
 *    Copyright 2003, Huawei Technologies Co. Ltd  India Institute  
 *                     ALL RIGHTS RESERVED                           
 *                                                 
 *----------------------------------------------------------------------*
 *
 *                             Natpt_Mgmt.h
 *
 *  Project Code:       VRPv5 
 *  Create Date:        2003-7-5
 *  Author:             usha   (VRPv5 IPv6 Team) 
 *  Document:
 *  Function Description:
 *  
 *----------------------------------------------------------------------*
 *  Modification History 
 *  DATE        NAME             DESCRIPTION
 *  
 *  
 ************************************************************************/





#ifndef _NATPT_MGMT_H_
#define _NATPT_MGMT_H_


#ifdef  __cplusplus
extern  "C"{
#endif



/*----------------------------------------------*
 * Macros            
 *----------------------------------------------*/
#define NATPT_DROP_PKT                        2 /* error code */  
#define NATPT_ICMPERROR_GENERATED             3 /* error code */

#define NATPT_UNEXPIRED_SROUTE                1


#define NATPT_NOFRAG_FLAG                  0x00            /* Flag to indicate no fragmentation */



                                                              

#define NATPT_SET_NEXT_HOP                 1 /*TBD */                 





#define NATPT_UNDO_ENB                      0x01
#define NATPT_INTF_DELETE                   0x02



#define NATPT_SET_IFENABLE(pstNatptIf)\
    (pstNatptIf->usNatptEnableFlag |= NATPT_ENABLE)
#define NATPT_UNDO_IFENABLE(pstNatptIf)\
    (pstNatptIf->usNatptEnableFlag = NATPT_DISENABLE)

#define NATPT_SET_IFDBGFLAG(pstNatptIf,usFlag)\
    (pstNatptIf->usDebugFlag |= usFlag)
#define NATPT_RESET_IFDBGFLAG(pstNatptIf, usFlag)\
    (pstNatptIf->usDebugFlag &= (~usFlag))



#define MBUF_SET_NEXT_HOP(pstMbuf, ulNextHop) \
    (pstMbuf->stUserTagData.unPacketInfoRelevantToNetwork.stIpPacketInfo.ulNextHopIpAddress = ulNextHop)

#define NATPT_IS_SYN_PKT(ucFlag)(ucFlag & TH_SYN)
#define NATPT_IS_FIN_PKT(ucFlag)(ucFlag & TH_FIN)
#define NATPT_IS_RST_PKT(ucFlag)(ucFlag & TH_RST)

/* For defect BYAD06344 */
#define NATPT_FIBLOOKUP 1
#define NATPT_NO_FIBLOOKUP 0
/* End of defect BYAD06344 */

#define NATPT_MGMT 1
/* Macro to get pointer to optional hdr in IPv6 pkt */
#ifndef IP6_EXTHDR_GET
#define IP6_EXTHDR_GET(m, val, type, off, len, mid, ret) \
do { \
    MBUF_MAKE_MEMORY_CONTINUOUS( (m), (off)+(len), (mid), (ret) ); \
    if ( (ret) == 0 ) \
    { \
        (val) = (type)(MBUF_MTOD(m, UCHAR *) + off); \
    } \
} while(0)
#endif

/*----------------------------------------------*
 * Structure Defintions
 *----------------------------------------------*/

typedef struct tagNatptAutHdr_S
{
    UCHAR ucNxtHdr;
    UCHAR ucLength;
}NATPT_AUTHDR_S;



/*----------------------------------------------*
 * Global Variables
 *----------------------------------------------*/




/*----------------------------------------------*
 * Function Decalrations
 *----------------------------------------------*/
    
ULONG NATPT_GetIP6PktInfo (MBUF_S *, NATPT_PKTCHAR_S *,IP6_ROUTE_S **);
ULONG NATPT_NeedToTranslateV6 (NATPT_PKTCHAR_S *, ULONG *, ULONG *, UCHAR *);

ULONG NATPT_V6CheckSessionAndForwardPkt (MBUF_S *, NATPT_PKTCHAR_S, IP6_ROUTE_S *);

ULONG NATPT_IsV6PktValid (MBUF_S *, NATPT_PKTCHAR_S ,IP6_ROUTE_S *);
ULONG NATPT_HandleFirstV6Pkt (MBUF_S *,UCHAR ,NATPT_PKTCHAR_S *);
ULONG NATPT_V6ForwardSessionExist (MBUF_S *, NATPT_PKTCHAR_S *);

/* For defect BYAD06344 */
ULONG NATPT_V4CheckSessionAndForwardPkt (MBUF_S *, NATPT_PKTCHAR_S, UCHAR);
 /* End of defect BYAD06344*/

ULONG NATPT_GetIP4PktInfo (MBUF_S *,NATPT_PKTCHAR_S *);
ULONG NATPT_NeedToTranslateV4 (NATPT_PKTCHAR_S *, UCHAR *);
ULONG NATPT_IsV4PktValid (MBUF_S *, NATPT_PKTCHAR_S );

ULONG NATPT_HandleFirstV4Pkt (MBUF_S *, UCHAR , NATPT_PKTCHAR_S *);
ULONG NATPT_V4ForwardSessionExist (MBUF_S *,NATPT_PKTCHAR_S *);
ULONG NATPT_CheckV4SourceRoute (MBUF_S *pstMBuf,UCHAR *pucSourceRoute);

/* For defect BYAD06308 */
/* Macro is being used instead of this function
ULONG NATPT_Enabled_On_Interface (IFNET_S *);*/
/* End of defect BYAD06308 */    

BOOL_T NATPT_IsV6AddressValid(IN6ADDR_S );
BOOL_T NATPT_IsV4AddressValid (ULONG );

VOID Natpt_DebugOutStr(NATPT_PKTCHAR_S stPktChar, USHORT usDirection );

ULONG NATPT_Delete_Interface (ULONG, UCHAR );

ULONG NATPT_VirtualInfEnable(ULONG ulIfIndex);
ULONG NATPT_VirtualInfDisable(ULONG ulIfIndex);
ULONG NATPT_HandleLastV6FragPkt (MBUF_S *pstMBuf, NATPT_PKTCHAR_S *pstPktChar);

#ifdef  __cplusplus
}
#endif


#endif

