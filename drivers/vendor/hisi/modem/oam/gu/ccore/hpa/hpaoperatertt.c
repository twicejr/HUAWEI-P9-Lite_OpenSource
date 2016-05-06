/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: HPAOperateRtt.c                                                 */
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
#include "hpacomm.h"
#include "mdrv.h"

/*lint -e767 修改人: m00128685；检视人：l46160 原因简述:打点日志文件宏ID定义*/
#define    THIS_FILE_ID        PS_FILE_ID_HPA_OPERATE_RTT_C
/*lint -e767  修改人: m00128685；检视人：l46160*/



/*****************************************************************************
 Function   : HPA_Write32Reg
 Description: write 32bit data to DSP & BBP
 Input      : ulRegAddr -- address of DSP & BBP
            : ulRegVal -- 32bit data
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID HPA_Write32Reg( VOS_UINT32 ulRegAddr, VOS_UINT32 ulRegVal)
{
    if ( 0 != (ulRegAddr & 0x03) )/* not 4byte aligned */
    {
        /*lint -e534*/
        LogPrint1("HPA_Write32Reg Address: 0x%x not aligned.\r\n",(VOS_INT)ulRegAddr);
        /*lint +e534*/
        return;
    }

    *(volatile VOS_UINT32 *)ulRegAddr = ulRegVal;
}

/*****************************************************************************
 Function   : HPA_Write32RegMask
 Description: write mask to DSP & BBP
 Input      : ulRegAddr -- address of DSP & BBP
            : ulMask -- mask
 Return     : void
 Other      : caution: BIT_N must be used befor call the function
 *****************************************************************************/
VOS_VOID HPA_Write32RegMask(VOS_UINT32 ulRegAddr, VOS_UINT32 ulMask)
{
    if ( 0 != (ulRegAddr & 0x03) )/* not 4byte aligned */
    {
        /*lint -e534*/
        LogPrint1("HPA_Write32RegMask Address: 0x%x not aligned.\r\n",(VOS_INT)ulRegAddr);
        /*lint +e534*/
        return;
    }

    *(volatile VOS_UINT32 *)ulRegAddr |= ulMask;
}

/*****************************************************************************
 Function   : HPA_Clear32RegMask
 Description: clear mask of DSP & BBP
 Input      : ulRegAddr -- address of DSP & BBP
            : ulMask -- mask
 Return     : void
 Other      : caution: BIT_N must be used befor call the function
 *****************************************************************************/
VOS_VOID HPA_Clear32RegMask(VOS_UINT32 ulRegAddr, VOS_UINT32 ulMask)
{
    if ( 0 != (ulRegAddr & 0x03) )/* not 4byte aligned */
    {
        /*lint -e534*/
        LogPrint1("HPA_Clear32RegMask Address: 0x%x not aligned.\r\n",(VOS_INT)ulRegAddr);
        /*lint +e534*/
        return;
    }

    *(volatile VOS_UINT32 *)ulRegAddr &= ~ulMask;
}

/*****************************************************************************
 Function   : HPA_Write16Reg
 Description: write 16bit data to DSP & BBP
 Input      : ulRegAddr -- address of DSP & BBP
            : ulRegVal -- 16bit data
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID HPA_Write16Reg( VOS_UINT32 ulRegAddr, VOS_UINT16 usRegVal)
{
    if ( 0 != (ulRegAddr & 0x01) )/* not 2byte aligned */
    {
        /*lint -e534*/
        LogPrint1("HPA_Write16Reg Address: 0x%x not aligned.\r\n",(VOS_INT)ulRegAddr);
        /*lint +e534*/
        return;
    }

    *(volatile VOS_UINT16 *)ulRegAddr = usRegVal;
}

/*****************************************************************************
 Function   : HPA_Write16RegMask
 Description: write mask to DSP & BBP
 Input      : ulRegAddr -- address of DSP & BBP
            : ulMask -- mask
 Return     : void
 Other      : caution: BIT_N must be used befor call the function
 *****************************************************************************/
VOS_VOID HPA_Write16RegMask(VOS_UINT32 ulRegAddr, VOS_UINT16 ulMask)
{
    if ( 0 != (ulRegAddr & 0x01) )/* not 2byte aligned */
    {
        /*lint -e534*/
        LogPrint1("HPA_Write16RegMask Address: 0x%x not aligned.\r\n",(VOS_INT)ulRegAddr);
        /*lint +e534*/
        return;
    }

    *(volatile VOS_UINT16 *)ulRegAddr |= ulMask;
}

/*****************************************************************************
 Function   : HPA_Clear16RegMask
 Description: clear mask of DSP & BBP
 Input      : ulRegAddr -- address of DSP & BBP
            : ulMask -- mask
 Return     : void
 Other      : caution: BIT_N must be used befor call the function
 *****************************************************************************/
VOS_VOID HPA_Clear16RegMask(VOS_UINT32 ulRegAddr, VOS_UINT16 ulMask)
{
    if ( 0 != (ulRegAddr & 0x01) )/* not 2byte aligned */
    {
        /*lint -e534*/
        LogPrint1("HPA_Clear16RegMask Address: 0x%x not aligned.\r\n",(VOS_INT)ulRegAddr);
        /*lint +e534*/
        return;
    }

    *(volatile VOS_UINT16 *)ulRegAddr &= ~ulMask;
}

/*****************************************************************************
 Function   : HPA_Write8Reg
 Description: write 8bit data to DSP & BBP
 Input      : ulRegAddr -- address of DSP & BBP
            : ulRegVal -- 8bit data
 Return     : void
 Other      : Caution : this function should not supported.
 *****************************************************************************/
VOS_VOID HPA_Write8Reg( VOS_UINT32 ulRegAddr, VOS_UINT8 ucRegVal )
{
    VOS_UINT16 usTempValue;
    VOS_UINT32 ulTempAddr;
    VOS_UINT8 *pucTemp;

    ulTempAddr = ulRegAddr & 0xfffffffe;

    usTempValue = *(volatile VOS_UINT16 *)(ulTempAddr);

    pucTemp = (VOS_UINT8 *)&usTempValue;

    if ( ulRegAddr == ulTempAddr )
    {
        *pucTemp = ucRegVal;
    }
    else
    {
        pucTemp++;
        *pucTemp = ucRegVal;
    }

    *(volatile VOS_UINT16 *)ulTempAddr = usTempValue;
}

/*****************************************************************************
 Function   : HPA_Read32Reg
 Description: read 32bit data from DSP & BBP
 Input      : ulRegAddr -- address of DSP & BBP
            : ulRegVal -- 32bit data
 Return     : void
 Other      :
 *****************************************************************************/
VOS_UINT32 HPA_Read32Reg( VOS_UINT32 ulRegAddr )
{
    if ( 0 != (ulRegAddr & 0x03) )/* not 4byte aligned */
    {
        /*lint -e534*/
        LogPrint1("HPA_Read32Reg Address: 0x%x not aligned.\r\n",(VOS_INT)ulRegAddr);
        /*lint +e534*/
        return 0;
    }

    return *(volatile VOS_UINT32 *)ulRegAddr;
}

/*****************************************************************************
 Function   : HPA_Read16Reg
 Description: read 16bit data from DSP & BBP
 Input      : ulRegAddr -- address of DSP & BBP
            : ulRegVal -- 16bit data
 Return     : void
 Other      :
 *****************************************************************************/
VOS_UINT16 HPA_Read16Reg( VOS_UINT32 ulRegAddr )
{
    if ( 0 != (ulRegAddr & 0x01) )/* not 2byte aligned */
    {
        /*lint -e534*/
        LogPrint1("HPA_Read16Reg Address: 0x%x not aligned.\r\n",(VOS_INT)ulRegAddr);
        /*lint +e534*/
        return 0;
    }

    return *(volatile VOS_UINT16 *)ulRegAddr;
}

/*****************************************************************************
 Function   : HPA_Read8Reg
 Description: read 8bit data from DSP & BBP
 Input      : ulRegAddr -- address of DSP & BBP
            : ulRegVal -- 8bit data
 Return     : void
 Other      : Caution : this function should not supported.
 *****************************************************************************/
VOS_UINT8 HPA_Read8Reg( VOS_UINT32 ulRegAddr )
{
    VOS_UINT16 usTempValue;
    VOS_UINT32 ulTempAddr;
    VOS_UINT8 *pucTemp;

    ulTempAddr = ulRegAddr & 0xfffffffe;

    usTempValue = *(volatile VOS_UINT16 *)(ulTempAddr);

    pucTemp = (VOS_UINT8 *)&usTempValue;

    if ( ulRegAddr == ulTempAddr )
    {
        return *pucTemp;
    }
    else
    {
        pucTemp++;
        return *pucTemp;
    }
}


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _HPA_PPERATE_RTT_H */

