/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: HPAOperateRtt.h                                                 */
/*                                                                           */
/* Author: Windriver                                                         */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2006-10                                                             */
/*                                                                           */
/* Description: implement ring buffer subroutine                             */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date:                                                                  */
/*    Author: x51137                                                         */
/*    Modification: Adapt this file                                          */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#ifndef  _HPA_PPERATE_RTT_H
#define  _HPA_PPERATE_RTT_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include "vos.h"

VOS_VOID HPA_Write32Reg( VOS_UINT32 ulRegAddr, VOS_UINT32 ulRegVal);

VOS_VOID HPA_Write32RegMask(VOS_UINT32 ulRegAddr, VOS_UINT32 ulMask);

VOS_VOID HPA_Clear32RegMask(VOS_UINT32 ulRegAddr, VOS_UINT32 ulMask);

VOS_VOID HPA_Write16Reg( VOS_UINT32 ulRegAddr, VOS_UINT16 usRegVal);

VOS_VOID HPA_Write16RegMask(VOS_UINT32 ulRegAddr, VOS_UINT16 ulMask);

VOS_VOID HPA_Clear16RegMask(VOS_UINT32 ulRegAddr, VOS_UINT16 ulMask);

VOS_VOID HPA_Write8Reg( VOS_UINT32 ulRegAddr, VOS_UINT8 ucRegVal );

VOS_UINT32 HPA_Read32Reg( VOS_UINT32 ulRegAddr );

VOS_UINT16 HPA_Read16Reg( VOS_UINT32 ulRegAddr );

VOS_UINT8 HPA_Read8Reg( VOS_UINT32 ulRegAddr );

void HPA_PutDspMem( const char *source, char *destination, int nbytes );

void HPA_GetDspMem( const char *source, char *destination, int nbytes );

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _HPA_PPERATE_RTT_H */

