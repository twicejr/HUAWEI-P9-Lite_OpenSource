/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dns_ext.h
*
*  Project Code: VISP1.5
*   Module Name: DNSC Module  
*  Date Created: 2002-11-25
*        Author: Sun Yanfeng(32084)
*   Description: DNS模块的所有函数引用声明     
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                 DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2002-11-25  Sun Yanfeng(32084)         Creat the first version.
*
*******************************************************************************/
 
/*======================================================================*/
/*                           End of Standard header                     */
/*======================================================================*/

#ifndef _DNS_EXT_H_
#define _DNS_EXT_H_

/*In case of the C++.*/
#ifdef  __cplusplus
extern "C" {
#endif

#include "tcpip/public/tcpip_basefun.h"


/*******************************************************************
                          yanghua added
*******************************************************************/
extern LONG VOS_strcmp (const CHAR *s1, const CHAR *s2);
extern CHAR *VOS_IpAddrToStr(ULONG ulAddr, CHAR *szStr);
extern LONG vos_printf(const char * format, ... );

extern IFNET_S * IF_GetIfByFullName(CHAR *);

extern ULONG VOS_WaitListSet(UINTPTR ulHandle, VOID *pListData, VOID *pParamOfGetNext);
extern ULONG VOS_WaitListGet(UINTPTR ulHandle, VOID **ppListData);

extern ULONG VOS_WaitListRegister(ULONG ulMainType, 
                                              UINTPTR *pulHandle, 
                                              WAITLIST_GETNEXTFUNC pfGetNextFunc);
extern ULONG VOS_WaitListDelFromList(ULONG ulMainType, VOID *pDataToDel);
extern ULONG VOS_WaitListUnregister(UINTPTR ulHandle);

/*******************************************************************
                          SUNYANFENG added
*******************************************************************/
extern ULONG VOS_Timer_Create(
                        ULONG ulTaskID,
                        ULONG ulMsgQueID,
                        ULONG ulMillSec,
                        VOID  (*pfTimerFunc)(VOID *),
                        VOID  *pArg,
                        ULONG *pulRetTimerID,
                        ULONG ulFlag /*VOS_TIMER_LOOP or VOS_TIMER_NOLOOP*/
                      );
extern ULONG VOS_WaitListDelFromList(ULONG ulMainType, VOID *pDataToDel);
extern CHAR VOS_tolower(CHAR ch);


/*In case of the C++.*/
#ifdef  __cplusplus
}
#endif


#endif/*End of the file. */

