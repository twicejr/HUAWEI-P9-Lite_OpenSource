/******************************************************************************
 *
 *        Copyright 2003-2006  Huawei Technologies India Private Limited
 *                          All Rights Reserved
 *
 *------------------------------------------------------------------------------
 *                            ipmtu_sh.h
 *    Project Code :  VRP5.0
 *    Module Name  :  IP6 PMTU
 *    Version      :  Initial Draft
 *    Create Date  :  2003/06/10
 *         Author  :  Surya PC
 *     Description :  Shell related header file
 *------------------------------------------------------------------------------
 *  Modification History
 *  DATE        NAME             DESCRIPTION
 *  ----------------------------------------------------------------------------
 *  2003-06-10  Surya         Create

   Problem Number : AC4D00997     Author:Sandeep71635,   Date:2006/11/9
   Description    : IP6_PMTU_SetResSpecs APIs input validation not complete
   Problem Number : AC4D01077     Author:Sandeep71635,   Date:2006/11/16
   Description    : Debugging information not shown for IO Board after reset
                        the IO board
 ******************************************************************************/

#ifndef _IP6_PMTU_SH_H
#define _IP6_PMTU_SH_H
#endif
#ifdef __cplusplus
extern "C"{
#endif

#define DEBUG_INFO_MSG 12


/*
    IAS changes Start :
    Maximum number of static PMTU entries are configuring through PAF.
    So maximum PAF variables for PMTU is 2.
*/
#define  MAX_SPECS_FOR_PMTU     2

/* IAS changes End */

 typedef VOID (* tmpfFunc)(VOID *);

/*Errors */
#define IP6_PMTU_PAF_INIT_ERROR                      100
#define IP6_PMTU_PAF_INIT_ERROR_REGISTER_CALLBACK       101


/* Enumeration constants for error codes in PMTU Module.*/
enum enum_IP6_PMTU
{
    IP6_PMTU_ipv6,
    IP6_PMTU_pathmtu,
    IP6_PMTU_age,
    IP6_PMTU_MTUVALUE,
    IP6_PMTU_IPAddress,
    IP6_PMTU_Zoneid,
    IP6_PMTU_Time,

    /*Defect :BYAD03866*/
    IP6_PMTU_All,
    IP6_PMTU_Static,
    IP6_PMTU_Dynamic,

    IP6_PMTU_CMDELEMENT_SHOWCOM,
    IP6_PMTU_CMDELEMENT_SHOWCOMVER,
    IP6_PMTU_CMDELEMENT_SHOWCOMVERPMTU,
    IP6_PMTU_CMDELEMENT_SHOWCOMTESTVER,
    IP6_PMTU_CMDELEMENT_SHOWCOMTESTVERPMTU,

    IP6_PMTU_PAD = IP6_PMTU_MAX_ENUM_VALUE
};

/* For CLI enable and Disable.*/
#define IP6_PMTU_ENABLE_CLI 1
#define IP6_PMTU_DISABLE_CLI 0

#define PMTU_MAX_AGETIME 100

/* These CMOs will be used in command registration.*/
#define TBL_IP6_PMTU_AGETIME            0x01
#define TBL_IP6_PMTU_PMTU               0x02
#define TBL_IP6_PMTU_RESETPMTU          0x03
#define TBL_IP6_PMTU_DISPLAYPMTU        0x04
#define TBL_IP6_PMTU_DEBUGPMTU          0x05
#define TBL_IP6_PMTU_SHOW_COM_VERSION   0x06
#define TBL_IP6_PMTU_SHOW_LOG           0x07

/*(undo) ipv6 pmtu age <IPv6_address> <time> */
#define CMO_IP6_AGE_PMTU_IPADDR  CFG_CMO_DEF(MID_PMTU, TBL_IP6_PMTU_AGETIME, 1)
#define CMO_IP6_AGE_PMTU_TIME   CFG_CMO_DEF(MID_PMTU, TBL_IP6_PMTU_AGETIME, 2)
#define CMO_IP6_AGE_PMTU_ZONEID  CFG_CMO_DEF(MID_PMTU, TBL_IP6_PMTU_AGETIME, 3)
#define CMO_IP6_UNDO_AGETIME     CFG_CMO_DEF(MID_PMTU, TBL_IP6_PMTU_AGETIME, 4)

/*(undo)ipv6 pmtu <IPv6_address>  <PMTU > */
#define CMO_IP6_PMTU       CFG_CMO_DEF(MID_PMTU, TBL_IP6_PMTU_PMTU, 1)
#define CMO_IP6_UNDO_PMTU      CFG_CMO_DEF(MID_PMTU, TBL_IP6_PMTU_PMTU, 2)
#define CMO_IP6_PMTU_IPADDR CFG_CMO_DEF(MID_PMTU, TBL_IP6_PMTU_PMTU, 3)

/* reset IPv6pmtu */
#define CMO_IP6_RESET_PMTU  CFG_CMO_DEF(MID_PMTU, TBL_IP6_PMTU_RESETPMTU, 1)
#define CMO_IP6_PMTU_RESET_ALL  CFG_CMO_DEF(MID_PMTU, TBL_IP6_PMTU_RESETPMTU, 2)
#define CMO_IP6_PMTU_RESET_STATIC \
    CFG_CMO_DEF(MID_PMTU, TBL_IP6_PMTU_RESETPMTU, 3)
#define CMO_IP6_PMTU_RESET_DYNAMIC    \
    CFG_CMO_DEF(MID_PMTU, TBL_IP6_PMTU_RESETPMTU, 4)

/*display ipv6 pathmtu <ipadress> */
#define CMO_IP6_DISPLAY_PMTU_IPADDR  \
    CFG_CMO_DEF(MID_PMTU, TBL_IP6_PMTU_DISPLAYPMTU, 2)
#define CMO_IP6_PMTU_DISPLAY_ALL   \
    CFG_CMO_DEF(MID_PMTU, TBL_IP6_PMTU_DISPLAYPMTU, 3)
#define CMO_IP6_PMTU_DISPLAY_STATIC  \
    CFG_CMO_DEF(MID_PMTU, TBL_IP6_PMTU_DISPLAYPMTU, 4)
#define CMO_IP6_PMTU_DISPLAY_DYNAMIC    \
    CFG_CMO_DEF(MID_PMTU, TBL_IP6_PMTU_DISPLAYPMTU, 5)

/* debugging ipv6 pathmtu */
#define CMO_IP6_PMTU_DEBUG_PATHMTU \
    CFG_CMO_DEF(MID_PMTU, TBL_IP6_PMTU_DEBUGPMTU, 1)
#define CMO_IP6_PMTU_DEBUG_UNDO CFG_CMO_DEF(MID_PMTU, TBL_IP6_PMTU_DEBUGPMTU, 2)
#define  CMO_IP6_PMTU_SHOW_COM_VERSION  \
                     CFG_CMO_DEF(MID_ICMP6, TBL_IP6_PMTU_SHOW_COM_VERSION, 1)
#define  CMO_IP6_PMTU_SHOW_COM_TEST_VERSION  \
                     CFG_CMO_DEF(MID_ICMP6, TBL_IP6_PMTU_SHOW_COM_VERSION, 2)
#define  CMO_IP6_PMTU_SHOW_LOG              \
                    CFG_CMO_DEF(MID_ICMP6, TBL_IP6_PMTU_SHOW_LOG, 2)

/* default state of the PMTU enabling */
#define IP6_PMTU_DEFUALT_AGETIME              10

/* Used in Show all function as ulFlag*/
#define PMTU_DISPLAY_ALL 1
#define PMTU_DISPLAY_STATIC 2
#define PMTU_DISPLAY_DYNAMIC 3

extern ULONG g_ulPMTUCliState;
extern ULONG g_ulIP6PMTUDebugFlag;
#if (VRP_MODULE_CFG_CLI_BASE == VRP_YES)
extern VRP_INFORMATION g_stIP6_PMTU_Info[];
#endif
extern ULONG g_ulShMaxPMtu;


extern struct IIF_IP6_PMTU_INT_HSBVtbl    *g_pstPMTU_INT_HSBVtbl;
extern struct IIF_IP6_PMTU_INITVtbl       *g_pstPMTU_INITVtbl;
extern struct IIF_IP6_PMTU_INT_INITVtbl   *g_pstPMTU_INT_INITVtbl;
extern struct IIF_IP6_PMTU_CFGVtbl        *g_pstPMTU_CFGVtbl;
extern struct IIF_IP6_PMTU_INT_SSAVtbl    *g_pstPMTU_INT_SSAVtbl;
extern struct IIF_IP6_PMTU_FUNVtbl        *g_pstPMTU_FUNVtbl;
extern struct IIF_IP6_PMTU_IR_FUNVtbl     *g_pstPMTU_IR_FUNVtbl;
extern struct IIF_IP6_ADDR_GENERIC_FUNVtbl *g_pstPMTU_SH_ADDR_FUNVtbl;
extern struct IIF_IP6_ADDR_GENERIC_IR_FUNVtbl *g_pstPMTU_SH_ADDR_IR_FUNVtbl;

extern ULONG g_ulPmtuExecIndex;
extern CHAR *g_Inf_Pmtu_En[];
extern CHAR *g_Inf_Pmtu_Ch[];
extern VOID   (*g_pfIP6_PMTU_SH_Ev_Process)(ULONG ulEvent);

extern  ULONG ulSOCKPmtuQueID;

extern  ULONG ulSOCKTmrQueID;
extern  ULONG ulVRPTID_SOCK;

#ifdef __cplusplus
}
#endif /* end of __cplusplus */
