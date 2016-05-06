/*******************************************************************************
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ifiba_api.h
*
* Project Code: VISPV100R005
*  Module Name: SFIB4
* Date Created: 2003-07-08
*       Author: Zhang Hongyan
*  Description: FIBAgent Component factory creation and Query prototypes
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2003-07-08   Zhang Hongyan           Create
*  2006-03-30   Jiangtao                Adjust for D00646
*  2006-04-21   Jiangtao                Adjust for D00859 
*
*******************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _IFIBA_API_H
#define _IFIBA_API_H

ULONG ImplFibAgentFactoryQueryInterface (IUnknown *This, COMP_IID iid, LPVOID *ppvObj);
ULONG ImplFibAgentFactoryCreateInstance (IComponentFactory *This, COMP_IID iid, VOID **ppvObj);
ULONG IP_FIBAGENT_QueryInterface (IUnknown *This, COMP_IID iid, LPVOID *ppvObj);

#endif

#ifdef  __cplusplus
}
#endif

