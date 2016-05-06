/*******************************************************************************
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ifib6c_api.h
*
* Project Code: VISPV100R005
*  Module Name: SFIB6
* Date Created: 2003-07-22
*       Author: Zhang Hongyan
*  Description: FIBContainerComponent factory creation and Query prototypes
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2003-07-22   Zhang Hongyan           Create
*  2006-03-30   Jiangtao                Adjust for D00645
*  2006-04-21   Jiangtao                Adjust for D00858 
*
*******************************************************************************/
#include "tcpip/public/tcpip_config.h"

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _IFIB6C_API_H
#define _IFIB6C_API_H

ULONG ImplFib6CFactoryQueryInterface (IUnknown * This, COMP_IID iid, LPVOID *ppvObj);
ULONG ImplFib6CFactoryCreateInstance (IComponentFactory * This, COMP_IID iid, VOID **ppvObj );
ULONG IP6_FIBCONTR_QueryInterface (IUnknown *This, COMP_IID iid, LPVOID *ppvObj);

#endif

#ifdef  __cplusplus
}
#endif

