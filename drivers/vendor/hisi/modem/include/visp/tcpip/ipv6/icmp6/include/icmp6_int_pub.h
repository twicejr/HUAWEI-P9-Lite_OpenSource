/*******************************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-------------------------------------------------------------------------------
*                              icmp6_int_pub.h
*
*    Project Code:  IPB IR V1R2
*    Module Name :  ND
*        Version :
*    Create Date :  2007/06/29
*    Author      :  karthik
*    Description :  To define the ICMP6 structures and macro's used by core
*                    and shell of component
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2007-06-29  karthik      Created for including all component
*                           public definitions in this file,
*                           for IPB IR V1R2 - COMMOM re-arrange
************************************************************************/
#ifndef _ICMP6_INT_PUB_H
#define _ICMP6_INT_PUB_H

#ifdef  __cplusplus
extern "C"{
#endif

/***********************************************************************/
/*                             Macro Defination                        */
/***********************************************************************/

/*Systrace base id for icmp6*/
#define SYSTRC_IPV6_ICMP6_BASE     10

/* Start: RFC4443 compliance changes */
/*Default value for error rate interval*/
#define IP6_ICMP6_DEFAULT_ERRORRATE_INTERVAL    10000 /* 100 Millisecound */
/* End: RFC4443 compliance changes */

/*Default value for error rate tokens count*/
#define IP6_ICMP6_DEFAULT_TOCKENS               10  /* 10 Tokens*/

/* Start: RFC4443 compliance changes */
/*Default value for which tokens are filled*/
#define IP6_ICMP6_DEFAULT_FILL_RATE             10  /* 1/10th of the interval */

/* End: RFC4443 compliance changes */
/***********************************************************************/
/*                              Enum Defenation                                                                        */
/***********************************************************************/

/* Debug ID */
typedef enum tagIP6_ICMP6_ICDbgID
{
    ICMP6_DBGID_PKT = 0,
    ICMP6_DBGID_STR,
    ICMP6_DBGID_MAXNUM,
    ICMP6_DBGID_MAX_INT = IP6_ICMP6_MAX_ENUM_VALUE
}IP6_ICMP6_ICDbgID_E;

/* Log ID */
typedef enum tagIP6_ICMP6_IClogID
{
    ICMP6_LOGID_CFG_RCV_FAIL = 0,
    ICMP6_LOGID_CFG_SND_FAIL,
    ICMP6_LOGID_TOO_BIG_TIMER_FAIL,
    ICMP6_LOGID_ERR_TIMER_FAIL,
    ICMP6_LOGID_INIT_COM_FAIL,
    ICMP6_LOGID_TOO_BIG_ENABLE,
    ICMP6_LOGID_TOO_BIG_DISABLE,
    ICMP6_LOGID_ACQUIRE_GLOBAL_SEM_FAILED,
    ICMP6_LOGID_RELEASE_GLOBAL_SEM_FAILED,
    ICMP6_LOGID_MAXNUM,
    ICMP6_LOGID_MAX_INT = IP6_ICMP6_MAX_ENUM_VALUE
}IP6_ICMP6_IClogID_E;

/*----------------------------------------------------------------------------*/
/* Level 3 */
/*Reference for shell and core to communicate different component IDs from
  shell to core. To fill ulLocalIntfId field of the IPB_IR_ICMP6_COM_ID_INFO_S
  structure passed as argument of pfIP6_ICMP6_Init_Com_New*/
#define IP6_ICMP6_LOCAL_INTF_ID_ADDR    2001
#define IP6_ICMP6_LOCAL_INTF_ID_ND      2002
#define IP6_ICMP6_LOCAL_INTF_ID_PMTU    2003
#define IP6_ICMP6_LOCAL_INTF_ID_RIP6    2004
#define IP6_ICMP6_LOCAL_INTF_ID_IND     2006
#define IP6_ICMP6_LOCAL_INTF_ID_IR_ND   2007

#define IP6_ICMP6_IND                0

/*Number of instances of IPB_IR_ICMP6_COM_ID_INFO_S shell passes to core
  through pfIP6_ICMP6_Init_Com_New*/
#if (VRP_CENTERALIZATION == VRP_YES)
#define IP6_ICMP6_EXT_COMIF_CNT      0x5 + IP6_ICMP6_IND
#else
#define IP6_ICMP6_EXT_COMIF_CNT      0x4 + IP6_ICMP6_IND
#endif

/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Level 3 */

/* Structure to store Component information */
typedef struct tagIPB_IR_ICMP6_COM_ID_INFO
{
    ULONG ulLocalIntfId;
    CHAR *szComName;
    ULONG ulComId;
    CHAR *szIntfName;
    ULONG ulIntfId;
}IPB_IR_ICMP6_COM_ID_INFO_S;

/* Module Information */
typedef struct  tagIP6_ICMP6_MOD_INFO
{
    ULONG ulModID; /* Module id */

} IP6_ICMP6_MOD_INFO_S;

/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Level 3 */

/* Using in IP6_ICMP6_SH_CALLBACK_FUNC_S */
typedef VOID (*pfIcmp6TimerFunc)(VOID *);

/* Shell callback set using by Core */
typedef struct tagIP6_ICMP6_SH_CALLBACK_FUNC_S
{
    ULONG (*pfIP6_ICMP6_SH_TimerCreate)(ULONG ulMillSec,
                                        pfIcmp6TimerFunc pfTimerFunc,
                                        VOID  *pArg,
                                        ULONG *pulTimerID,
                                        ULONG ulFlag);

    ULONG (*pfIP6_ICMP6_SH_TimerDelete) (ULONG ulTimerID);
    ULONG (*pfIP6_ICMP6_SH_TimerRefresh) (ULONG ulTimerID, ULONG ulNewMillSec);
    ULONG (*pfIP6_ICMP6_SH_LogToIPOSIC)(ULONG ulLogID, ...);
    ULONG (*pfIP6_ICMP6_SH_DbgToIPOSIC)(ULONG ulDbgID, ...);
    ULONG (*pfIP6_ICMP6_SH_AddrStToStr)(const IN6ADDR_S *pstAddress,
                                        char *szAddr);
}IP6_ICMP6_SH_CALLBACK_FUNC_S;
/*----------------------------------------------------------------------------*/


#ifdef  __cplusplus
}
#endif

#endif  /* _ICMP6_INT_PUB_H */

