/************************************************************************
 *
 *    Copyright 2003, Huawei Technologies Co. Ltd  India Institute  
 *                     ALL RIGHTS RESERVED                           
 *                                                 
 *----------------------------------------------------------------------*
 *
 *                             natpt_type.h
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
 *  2003-12-10  Archana PV       For Defect BYAD05088
 *  2004-01-12  Archana PV       For Defect BYAD06880
 *  2004-02-03  Archana P V      For Defect BYAD06372
 ************************************************************************/


#ifndef _NATPT_TYPE_H_
#define _NATPT_TYPE_H_

#ifdef  __cplusplus
extern  "C"{
#endif


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


/*----------------------------------------------*
 *Enum and Structure Defintions
 *----------------------------------------------*/
/*enum for real time data */
enum enumNATPT_REALTIME_BACKUP
{
    NATPT_HA_BATCHDATA,
    NATPT_HA_TIMER_BACKUP,
    NATPT_HA_ADDRMAP,
    NATPT_HA_INCREMENT,
    NATPT_HA_DECREMENT,
    /*Add for Defect BYAD05088*/
    NATPT_HA_LCS_ADDRMAP,
    NATPT_HA_LCS_DPATMAP,
    NATPT_HA_LCS_SESSMAP,
    NATPT_HA_LCS_PAT,
    NATPT_HA_LCS_DPAT
};


typedef struct tagNATPT_V4SearchParams
{
    ULONG ulV4SrcAddr;
    ULONG ulV4DstAddr;
    USHORT usV4SrcPort;
    USHORT usV4DstPort;
    ULONG ulIfIndex;
    UCHAR ucProtocol;
} NATPT_V4SearchParams_S;



typedef struct tagNATPT_V6SearchParams
{
    IN6ADDR_S stV6SrcAddr;
    IN6ADDR_S stV6DstAddr;
    USHORT usV6SrcPort;
    USHORT usV6DstPort;
    UCHAR ucProtocol;
    UCHAR ucIsDNS;
    UCHAR ucIsValidPort; 
} NATPT_V6SearchParams_S;


typedef struct tagNATPT_SearchAddr
{
    ULONG ulV4SrcAddr;
    ULONG ulV4DstAddr;
    IN6ADDR_S stV6SrcAddr;
    IN6ADDR_S stV6DstAddr;
    USHORT usV4SrcPort;
    USHORT usV4DstPort;
    USHORT usV6SrcPort;
    USHORT usV6DstPort;
    ULONG ulIfIndex;
    UCHAR ucProtocol;
    UCHAR   ucFlag;
}NATPT_SEARCH_ADDR_S;

/* Natpt structure maintained in the IFnet structure */
typedef struct tagNatptIf_S
{
    USHORT usNatptEnableFlag;
    USHORT usDebugFlag;
}NATPTIF_S;


/* Structure for  Packet Character */
typedef struct tagPktChar_S
{
    IN6ADDR_S stV6DAddr;
    IN6ADDR_S stV6SAddr;
    USHORT    usV6SPort;
    USHORT    usV6DPort; 
    ULONG     ulV4DAddr;
    ULONG     ulV4SAddr;
    USHORT    usV4SPort;
    USHORT    usV4DPort;
    ULONG     ulPktID;
    ULONG     ulOptHdrLen;
    ULONG     ulV4PayloadLen;
    ULONG     ulV6PayloadLen;   
    USHORT    usFragOffSet;
    UCHAR     ucFlag;
    UCHAR     ucHopLimit;
    UCHAR     ucTrafficClass;
    UCHAR     ucSourceRouteOpt;
    UCHAR     ucProtocol;
    UCHAR     ucSynFinRstFlag;
 }NATPT_PKTCHAR_S;

typedef struct tagALG_PROCESSCHECK_S
{
    UCHAR      ucProtocol;/*Protocol. TCP or UDP*/
    ULONG      ulV4Addr;/*V4 Address*/
    USHORT     usPort;/*Port number of the application*/
    IN6ADDR_S  stV6Addr; /*    V6 Address */
} NATPT_ALG_PROCESSCHECK_S ;

/*Added for Defect BYAD05088*/

typedef struct tagNATPT_LicenseBackUp   
{
    USHORT  usTypeOfLcs;
    USHORT  usReserved; 
    ULONG   ulAvailParam;
    ULONG   ulEvent; 
}NATPT_HA_LCSBACUP_S;


#ifdef  __cplusplus
}
#endif

#endif /* end of VRP_MODULE_IPV6 */


