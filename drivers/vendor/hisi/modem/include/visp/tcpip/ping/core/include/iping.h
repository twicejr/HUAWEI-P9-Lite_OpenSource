/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              Iping.h
*
*  Project Code: VISP1.5
*   Module Name: ping  
*  Date Created: 2004-03-12
*        Author: Li Lixiang 
*   Description: Defines Component ID, and All Interface IDs for ping Component
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  12/03/2004  Zhang Hongyan    Creat the first version.
*  2006-04-27  luyao            根据编程规范，对文件进行规范化整理
*
*******************************************************************************/


#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _I_PING_H_
#define _I_PING_H_

/* For implement of QuerfyInstance() */
typedef struct tagPING_INT_OBJ_S
{
    IIF_PING_ComIntFUN  *pComIntFUN;
    IIF_PING_ComIntCFG  *pComIntIFG;
}PING_INT_OBJ_S;

/* Component Factory of Ping */
extern IComponentFactory m_IPPingFactory;
ULONG PING_QueryInterface(IUnknown *This, COMP_IID iid, LPVOID *ppvObj);
ULONG PING_InitCom(COM_ID_INFO_S *pstComInfo, ULONG  ulComLen);
ULONG PING_ActivateCom();
ULONG PING_SetModuleInfo(PING_MOD_INFO_S *pstMInfo);
ULONG PING_RegShellApi(PING_CALLBACK_SET_S *pstPingCallBcakFun);


#endif  /*  _I_PP4_H_  */

#ifdef  __cplusplus
   }
#endif


