/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              poec_ext.h 
 *
 *  Project Code: VISP1.5
 *   Module Name: PPPoE Client
 *  Date Created: 2003-01-11
 *        Author: liuhui
 *   Description: PPPoE Client模块Shell部分引用其他模块的函数接口
 *               
 *----------------------------------------------------------------------*
 *  Modification History 
 *  DATE             NAME               DESCRIPTION
 *  2003-01-11       liuhui             Create file
 *  2005-09-15       t45114             Modify
 *  2006-03-30       liai               Adjust for D00660
 *  2006/04/21       liai               Adjust for D00865
 *   
 ************************************************************************/

#ifndef  _POEC_EXT_H_
#define  _POEC_EXT_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "tcpip/public/tcpip_basefun.h"
extern IFNET_S *IF_CreateVAByDialerIf ( IFNET_S *pstDialerif );
extern IFNET_S * IF_DynamicCreateIfNet( CHAR * szFullName, ULONG ulSubType );

#ifdef __cplusplus
}
#endif

#endif

