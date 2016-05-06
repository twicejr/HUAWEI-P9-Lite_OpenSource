/*******************************************************************************
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ifib4c_api.h
*
* Project Code: VISPV100R005
*   Module Name: SFIB4
*  Date Created: 2003-07-08
*        Author: Zhang Hongyan
*   Description: FIBContainerComponent factory creation and Query prototypes
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

#ifndef _IFIB4C_API_H
#define _IFIB4C_API_H


ULONG ImplFib4CFactoryQueryInterface (IUnknown * This, COMP_IID iid, LPVOID *ppvObj);
ULONG ImplFib4CFactoryCreateInstance (IComponentFactory * This, COMP_IID iid, VOID **ppvObj );
ULONG IP4_FIBCONTR_QueryInterface (IUnknown *This, COMP_IID iid, LPVOID *ppvObj);


#endif

#ifdef  __cplusplus
}
#endif

