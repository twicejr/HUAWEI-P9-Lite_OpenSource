/***************************************************************************
*                                                                          *
*                         addr_type.h                                      *
*                                                                          *
*  Project Code:       VRP3.1 IPv6 project                                 *
*  Version:            IPBIRV100R003.IPv6.E001                             *
*  Module Code:        IPv6 Address management                             *
*  Create Date:        2002-8-14                                           *
*  Author:             luoli                                               *
*  Modify Date:                                                            *
*  Description:        This file describes ADDR module related data        *
                       structures.                                         *
*  Function:                                                               *
*  Others:                                                                 *
*--------------------------------------------------------------------------*
*                                                                          *
*     Copyright 2002 VRP3.1 Team Beijing Institute HuaWei Tech, Inc.       *
*                      ALL RIGHTS RESERVED                                 *
*                                                                          *
*  2006-09-23   Rajat Phull R71638  "Updated for 14 Fly-Check rules        *
*                                    adherence for IPBIRV100R002.IP.E001"  *
*                                                                          *
***************************************************************************/
#ifndef _ADDR_TYPE_H_
#define _ADDR_TYPE_H_


#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------*
 * macros                                       *
 *----------------------------------------------*/

#define ADDR_CONFIG_IF_NAME_LENGTH  256

/*----------------------------------------------*
 *              Data Structures                 *
 *----------------------------------------------*/

/* Begin  : Defect ID: D01006, Modifier:Rajesh,   Date:2004/9/13
   Reason : Get negotiated Mtu from I/O Board*/
typedef  struct  tagIp6NegMtu
{
    ULONG ulNGMtu;
}IP6_NEG_MTU_S;

/* Change for defect SWFD16749 BY:karthik ON:16/11/2005
   To implement get next for SMP */
/* WARNING-> The numbers of structure elements shall be moderate i.e <= 5 */
/* The Above HCC Warning is obvious - Will not be addressed */ 
typedef struct tagIP6_ADDR_CMD_PROC_CONFIG
{
    IN6ADDR_S stIn6Addr;   /*The address of the interface */
    ULONG  ulPrefixLength; /*The prefix length as per the address*/
    ULONG  ulEuiFlag;      /*IF the address is and EUI address or not*/
    ULONG  ulAddrTyFlag;   /*Represents the type of address on interface*/
    ULONG  ulIpv6Addr_RowStatus;/*If address is specified or unspecified*/
    CHAR    aucIfName[ADDR_CONFIG_IF_NAME_LENGTH]; /* The inteface name */

}IP6_ADDR_CMD_PROC_CONFIG_S;

typedef VOID  (*pfConvtoVoidFunc)(VOID *);

#ifdef __cplusplus
}
#endif /* end of __cplusplus */

#endif /* end of _ADDR_TYPE_H_ */

