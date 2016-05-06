/*******************************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-------------------------------------------------------------------------------
*                              icmp6_sh_cfg.h
*
*   Project Code : VRP5.0
*    Module Name : IP6 BASIC ICMP6
*    Create Date : 2003/04/29
*         Author : Mahaveer Jain
*        Version :
*    Description : Shell CFG implement header file for ICMP6 module
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
* 2006-09-14   Alok       Updated for 14 Fly-Check rules adherence
*                         for IPBIRV1R2.IPv6
********************************************************************************
*/

#ifndef _ICMP6_SH_CFG_H
#define _ICMP6_SH_CFG_H

#ifdef _cplusplus
extern "C"{
#endif

#define SID_ICMP6_BUILDRUN            0x01
#define SID_ICMP6_MIB                 0x02

#define TBL_ICMP6_ERRORRATE           0x01
#define TBL_ICMP6_DEBUG               0x02
#define TBL_ICMP6_MIB                 0x03

#define ICMP6_VERSION_BUF_LEN          512
#define ICMP6_BUILDRUN_BUF_LEN         128

/* Defect Id : BYAD07812 Modified by Arun on 10/02/04
   Desc : System:Slave switchover,
   master reboots happens when sending  900 ICMP pkts with 10 ms delay */
#define TBL_ICMP6_RATELIMIT           0x04

#define CMO_IP6_ICMP6_UNDO       CFG_CMO_DEF(MID_ICMP6, TBL_ICMP6_ERRORRATE, 0)
#define CMO_IP6_ICMP6_INTERVAL   CFG_CMO_DEF(MID_ICMP6, TBL_ICMP6_ERRORRATE, 1)
#define CMO_IP6_ICMP6_BUCKET     CFG_CMO_DEF(MID_ICMP6, TBL_ICMP6_ERRORRATE, 2)
#define CMO_IP6_ICMP6_MILISEC    CFG_CMO_DEF(MID_ICMP6, TBL_ICMP6_ERRORRATE, 3)
#define CMO_IP6_ICMP6_BUCKETSIZE CFG_CMO_DEF(MID_ICMP6, TBL_ICMP6_ERRORRATE, 4)

#define CMO_IP6_ICMP6_DEBUG      CFG_CMO_DEF(MID_ICMP6, TBL_ICMP6_DEBUG, 0)
#define CMO_IP6_ICMP6_DEBUG_NO   CFG_CMO_DEF(MID_ICMP6, TBL_ICMP6_DEBUG, 1)

#define CMO_IP6_ICMP6_RATELIMIT  CFG_CMO_DEF(MID_ICMP6, TBL_ICMP6_RATELIMIT, 0)
#define CMO_IP6_ICMP6_RATELIMIT_NO  CFG_CMO_DEF(MID_ICMP6, \
                                        TBL_ICMP6_RATELIMIT, 1)

#define TBL_ICMP6_SHOW_COM_VERSION       0x05

#define CMO_ICMP6_SHOW_COM_VERSION  \
                     CFG_CMO_DEF(MID_ICMP6, TBL_ICMP6_SHOW_COM_VERSION, 1)
#define CMO_ICMP6_SHOW_COM_TEST_VERSION  \
                     CFG_CMO_DEF(MID_ICMP6, TBL_ICMP6_SHOW_COM_VERSION, 2)


#define TBL_ICMP6_SHOW_LOG       0x06

#define CMO_IP6_ICMP6_SHOW_LOG  \
                     CFG_CMO_DEF(MID_ICMP6, TBL_ICMP6_SHOW_LOG, 1)

/* CLI related enums */
enum enum_ICMP6NUM
{
    IP6_ICMP6_CMDELEMENT_IPV6,
    IP6_ICMP6_CMDELEMENT_DEBUG,
    IP6_ICMP6_CMDELEMENT_ICMPV6,
    IP6_ICMP6_CMDELEMENT_ERRORRATE,
    IP6_ICMP6_CMDELEMENT_INTERVAL,
    IP6_ICMP6_CMDELEMENT_BUCKET,
    IP6_ICMP6_CMDELEMENT_BUCKETVAL,
    IP6_ICMP6_CMDELEMENT_TOOBIGRATELIMIT,
    IP6_ICMP6_CMDELEMENT_SHOWCOM,
    IP6_ICMP6_CMDELEMENT_SHOWCOMVER,
    IP6_ICMP6_CMDELEMENT_SHOWCOMVERICMP6,
    IP6_ICMP6_CMDELEMENT_SHOWCOMTESTVER,
    IP6_ICMP6_CMDELEMENT_SHOWCOMTESTVERICMP6,
    IP6_ICMP6_CMDELEMENT_MAX,
    IP6_ICMP6_SH_END_PAD = IP6_ICMP6_MAX_ENUM_VALUE
};

#define IP6_ICMP6_IPC_RPC_PRIORITY             4
#define IP6_ICMP6_IPC_RPC_TIMEOUT              5000


#define IP6_ICMP6_ENABLE_CLI            1
#define IP6_ICMP6_DISABLE_CLI           0
#define IPV6IFICMPTABLE_TBL             TBL_ICMP6_MIB

#define CFGMIB_IPV6ICMPIFENTRY  CFG_CMO_DEF(MID_ICMP6, IPV6IFICMPTABLE_TBL, 36)

#define IPV6ICMPIFTABLE_TBL         04
#define CFGMIB_IPV6ICMPIFINDEX      CFG_CMO_DEF(MID_IP6_MANAGER, \
                                                IPV6ICMPIFTABLE_TBL, 1)

#define CFGMIB_IPV6IFICMPINMSGS       CFG_CMO_DEF(MID_ICMP6, \
                                                    IPV6IFICMPTABLE_TBL, 1)
#define CFGMIB_IPV6IFICMPINERRORS     CFG_CMO_DEF(MID_ICMP6, \
                                                    IPV6IFICMPTABLE_TBL, 2)
#define CFGMIB_IPV6IFICMPINDESTUNREACHS     CFG_CMO_DEF(MID_ICMP6, \
                                                        IPV6IFICMPTABLE_TBL, 3)
#define CFGMIB_IPV6IFICMPINADMINPROHIBS     CFG_CMO_DEF(MID_ICMP6, \
                                                        IPV6IFICMPTABLE_TBL, 4)
#define CFGMIB_IPV6IFICMPINTIMEEXCDS        CFG_CMO_DEF(MID_ICMP6, \
                                                        IPV6IFICMPTABLE_TBL, 5)
#define CFGMIB_IPV6IFICMPINPARMPROBLEMS     CFG_CMO_DEF(MID_ICMP6, \
                                                        IPV6IFICMPTABLE_TBL, 6)
#define CFGMIB_IPV6IFICMPINPKTTOOBIGS       CFG_CMO_DEF(MID_ICMP6, \
                                                        IPV6IFICMPTABLE_TBL, 7)
#define CFGMIB_IPV6IFICMPINECHOS            CFG_CMO_DEF(MID_ICMP6, \
                                                        IPV6IFICMPTABLE_TBL, 8)
#define CFGMIB_IPV6IFICMPINECHOREPLIES      CFG_CMO_DEF(MID_ICMP6, \
                                                        IPV6IFICMPTABLE_TBL, 9)
#define CFGMIB_IPV6IFICMPINROUTERSOLICITS   CFG_CMO_DEF(MID_ICMP6, \
                                                        IPV6IFICMPTABLE_TBL, 10)
#define CFGMIB_IPV6IFICMPINROUTERADVERTISEMENTS     CFG_CMO_DEF(MID_ICMP6, \
                                                        IPV6IFICMPTABLE_TBL, 11)
#define CFGMIB_IPV6IFICMPINNEIGHBORSOLICITS         CFG_CMO_DEF(MID_ICMP6, \
                                                        IPV6IFICMPTABLE_TBL, 12)
#define CFGMIB_IPV6IFICMPINNEIGHBORADVERTISEMENTS   CFG_CMO_DEF(MID_ICMP6, \
                                                        IPV6IFICMPTABLE_TBL, 13)
#define CFGMIB_IPV6IFICMPINREDIRECTS                CFG_CMO_DEF(MID_ICMP6, \
                                                        IPV6IFICMPTABLE_TBL, 14)
#define CFGMIB_IPV6IFICMPINGROUPMEMBQUERIES         CFG_CMO_DEF(MID_ICMP6, \
                                                        IPV6IFICMPTABLE_TBL, 15)
#define CFGMIB_IPV6IFICMPINGROUPMEMBRESPONSES       CFG_CMO_DEF(MID_ICMP6, \
                                                        IPV6IFICMPTABLE_TBL, 16)
#define CFGMIB_IPV6IFICMPINGROUPMEMBREDUCTIONS      CFG_CMO_DEF(MID_ICMP6, \
                                                        IPV6IFICMPTABLE_TBL, 17)
#define CFGMIB_IPV6IFICMPOUTMSGS            CFG_CMO_DEF(MID_ICMP6, \
                                                        IPV6IFICMPTABLE_TBL, 18)
#define CFGMIB_IPV6IFICMPOUTERRORS          CFG_CMO_DEF(MID_ICMP6, \
                                                        IPV6IFICMPTABLE_TBL, 19)
#define CFGMIB_IPV6IFICMPOUTDESTUNREACHS    CFG_CMO_DEF(MID_ICMP6, \
                                                        IPV6IFICMPTABLE_TBL, 20)
#define CFGMIB_IPV6IFICMPOUTADMINPROHIBS    CFG_CMO_DEF(MID_ICMP6, \
                                                        IPV6IFICMPTABLE_TBL, 21)
#define CFGMIB_IPV6IFICMPOUTTIMEEXCDS       CFG_CMO_DEF(MID_ICMP6, \
                                                        IPV6IFICMPTABLE_TBL, 22)
#define CFGMIB_IPV6IFICMPOUTPARMPROBLEMS    CFG_CMO_DEF(MID_ICMP6, \
                                                        IPV6IFICMPTABLE_TBL, 23)
#define CFGMIB_IPV6IFICMPOUTPKTTOOBIGS      CFG_CMO_DEF(MID_ICMP6, \
                                                        IPV6IFICMPTABLE_TBL, 24)
#define CFGMIB_IPV6IFICMPOUTECHOS           CFG_CMO_DEF(MID_ICMP6, \
                                                        IPV6IFICMPTABLE_TBL, 25)
#define CFGMIB_IPV6IFICMPOUTECHOREPLIES     CFG_CMO_DEF(MID_ICMP6, \
                                                        IPV6IFICMPTABLE_TBL, 26)
#define CFGMIB_IPV6IFICMPOUTROUTERSOLICITS  CFG_CMO_DEF(MID_ICMP6, \
                                                        IPV6IFICMPTABLE_TBL, 27)
#define CFGMIB_IPV6IFICMPOUTROUTERADVERTISEMENTS   CFG_CMO_DEF(MID_ICMP6, \
                                                        IPV6IFICMPTABLE_TBL, 28)
#define CFGMIB_IPV6IFICMPOUTNEIGHBORSOLICITS       CFG_CMO_DEF(MID_ICMP6, \
                                                        IPV6IFICMPTABLE_TBL, 29)
#define CFGMIB_IPV6IFICMPOUTNEIGHBORADVERTISEMENTS   CFG_CMO_DEF(MID_ICMP6, \
                                                        IPV6IFICMPTABLE_TBL, 30)
#define CFGMIB_IPV6IFICMPOUTREDIRECTS            CFG_CMO_DEF(MID_ICMP6, \
                                                        IPV6IFICMPTABLE_TBL, 31)
#define CFGMIB_IPV6IFICMPOUTGROUPMEMBQUERIES     CFG_CMO_DEF(MID_ICMP6, \
                                                        IPV6IFICMPTABLE_TBL, 32)
#define CFGMIB_IPV6IFICMPOUTGROUPMEMBRESPONSES   CFG_CMO_DEF(MID_ICMP6, \
                                                        IPV6IFICMPTABLE_TBL, 33)
#define CFGMIB_IPV6IFICMPOUTGROUPMEMBREDUCTIONS  CFG_CMO_DEF(MID_ICMP6, \
                                                        IPV6IFICMPTABLE_TBL, 34)

#if (IPBIR_IPV6_NP_SUPPORT == VRP_YES)
#define IP6_ICMP_REG_NPCALLBACK_CORE()                                \
{                                                                     \
    IPV6_PPI_HOOK_S *pstNPCallBack = NULL;                            \
    (VOID)IP6_PPI_GetValue(&pstNPCallBack);                           \
    if (pstNPCallBack)                                                \
    {                                                                \
        (VOID)g_pstICMP6INTInitTable->pfIP6_ICMP6_RegNPCallback(     \
                                                pstNPCallBack);       \
    }                                                                 \
}

#else
#define IP6_ICMP_REG_NPCALLBACK_CORE()                                
#endif

/* Configure intialization and this fucntion will be called in shell
   initialization */
extern ULONG IP6_ICMP6_SH_LogToIPOSIC(ULONG ulLogID, ...);
extern ULONG IP6_ICMP6_SH_DbgToIPOSIC(ULONG ulLogID, ...);

/* Debug message structure */
typedef struct tagICMP6DBGMSG
{
    ULONG  ulDbgOption;
    ULONG  ulDbgFlag;
    ULONG  ulDbgAcl;
    ULONG  ulDbgIfOpt;
}ICMP6_DEBUGMSG_S;

/* Statistics request structure */
typedef struct tagICMP6_STAT_REQUEST
{
    ULONG   ulReqTypeFlag;
    ULONG   ulSlotNumber;
}ICMP6STAT_REQUEST_S;

/* MIB message structure */
typedef struct tagICMP6MIBMSG
{
    ULONG          ulIpv6IfIndex;
    ULONG          ulcfgMibIP6Stats;
    UCHAR          ucFlag;        /* SET, GET or GET_NEXT   */
    UCHAR          ucPadding[3];
    ULONG          ulData;
} ICMP6MIBMSG_S;

/* Plug-In data transfer from  Main board to IO board */
typedef struct tagICMP6_PLUGIN_DATA
{
    ULONG ulInterval;
    ULONG ulBucket;
    ULONG ulOpsFlag; /* SET_INTERVAL = 1, SET_BUCKET = 1, SET_BOTH = 2 */
    ULONG ulDebugFlag;

}ICMP6_PLUGIN_DATA_S;

#ifdef _cplusplus
}
#endif

#endif

