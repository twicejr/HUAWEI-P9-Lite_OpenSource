/************************************************************************
 *
 *    Copyright 2003, Huawei Technologies Co. Ltd  India Institute  
 *                     ALL RIGHTS RESERVED                           
 *                                                 
 *----------------------------------------------------------------------*
 *
 *                             natpt_api.h
 *
 *  Project Code:       VRPv5 
 *  Create Date:        2003-7-4
 *  Author:             Desh   (VRPv5 IPv6 Team) 
 *  Document:           This file will contain all the function declarations for the component manager
 *  Function Description:The functions are to be used by the component manager to 
 *                        query the interface ,query the factory method and create instance of the component.
 *  
 *----------------------------------------------------------------------*
 *  Modification History 
 *  DATE        NAME             DESCRIPTION
 *  2003-07-04  Desh             Created
 *  
 ************************************************************************/


#ifndef _NATPT_API_H
#define _NATPT_API_H

#ifdef  __cplusplus
extern  "C"{
#endif


ULONG  INATPTFactoryQueryInterface(IUnknown * This, COMP_IID iid, LPVOID * ppvObj);
ULONG  INATPTFactoryCreateInstance(IComponentFactory * This, COMP_IID iid, VOID ** ppvObj );
ULONG  NATPT_QueryInterface(IUnknown* This, COMP_IID iid, LPVOID *ppvObj);


#ifdef  __cplusplus
}
#endif
#endif /* end of ifndef _NATPT_API_H */

