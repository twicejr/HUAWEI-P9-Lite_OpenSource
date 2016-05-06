/*-----------------------------------------------------------------------
*                              tcp6_com_pub.h
*
*    Project Code:  IPB IR V1R2
*    Module Name :  TCP6
*    Create Date :  2007/06/29
*    Author      :  karthik
*    Description :  To define the structures and macro's used by core
*                    and shell of component
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2007-06-29  karthik      Created for including all component
*                           public definitions in this file,
*                           for IPB IR V1R2 - COMMOM re-arrange
************************************************************************/

#ifndef _TCP6_COM_PUB_H
#define _TCP6_COM_PUB_H

#ifdef  __cplusplus
extern "C"{
#endif

#include "common/ipos/ipv6/tcp6_public.h"

/* External module number*/
#define IP6_TCP6_EXT_COMIF_CNT            0x4

/* For Systrace */
#define  SYSTRC_IPV6_TCP6_BASE  01

#define IP6_TCP6_TCP6_USR       ((SYSTRC_IPV6_TCP6_BASE << 8) + 1)
#define IP6_TCP6_TCP6_SH_CFG    ((SYSTRC_IPV6_TCP6_BASE << 8) + 2)
#define IP6_TCP6_TCP6_IN        ((SYSTRC_IPV6_TCP6_BASE << 8) + 3)
#define IP6_TCP6_TCP6_OUT       ((SYSTRC_IPV6_TCP6_BASE << 8) + 4)
#define IP6_TCP6_TCP6_SH_INIT   ((SYSTRC_IPV6_TCP6_BASE << 8) + 5)
#define IP6_TCP6_TCP6_SH_IC     ((SYSTRC_IPV6_TCP6_BASE << 8) + 6)
#define IP6_TCP6_TCP6_INIT      ((SYSTRC_IPV6_TCP6_BASE << 8) + 7)
#define IP6_TCP6_TCP6_FUN       ((SYSTRC_IPV6_TCP6_BASE << 8) + 8)
#define IP6_TCP6_TCP6_TIMER     ((SYSTRC_IPV6_TCP6_BASE << 8) + 9)
#define IP6_TCP6_TCP6_FAC       ((SYSTRC_IPV6_TCP6_BASE << 8) + 10)
#define IP6_TCP6_TCP6_INT       ((SYSTRC_IPV6_TCP6_BASE << 8) + 11)



#define TCP6_FILENUM      FILENUM
#define TCP6_SOCKID_ANY   (TCP6_FILENUM + 1)
#define TCP6_TASKID_ANY   0xFFFFFFFF


#define TCP6_TASKID_MIN 1
#define TCP6_TASKID_MAX 100
#define TCP6_SOCKID_MAX TCP6_FILENUM


/*TCP6 Module info*/
typedef struct tagTCP6MODINFO //L3
{
    ULONG    ulModID;
    ULONG    ulSubModID;
    ULONG ulTCP6_CFG_NEED_CACHE;
    ULONG ulTCP6_OUTPUT_OPTIMIZE;
} TCP6_MOD_INFO_S;

/*Call Back structure provided to shell to register the IC and debug
  functions to core*/
typedef struct tagIP6_TCP6_SH_CALLBACUP_SET  //L3
{

    VOID (*pfIP6_TCP6_DbugPkt)(CHAR *pszPreStr,SHORT sTcpState,
                                                    TCP6IP6HDR_S *pstHeader);
    VOID (*pfIP6_TCP6_SH_SendInfo2IC)(ULONG ulInfoId,CHAR *pszInfo);
    ULONG (*pfIP6_TCP6_SH_ConnectionTableMib) (VOID* pMsgRcv, VOID** ppMsgSnd);
    ULONG (*pfIP6_TCP6_SH_ListenerTableMib) (VOID* pMsgRcv, VOID** ppMsgSnd);
}IP6_TCP6_SH_CALLBACUP_SET_S;

#ifdef  __cplusplus
}
#endif

#endif  /* _TCP6_COM_PUB_H */

