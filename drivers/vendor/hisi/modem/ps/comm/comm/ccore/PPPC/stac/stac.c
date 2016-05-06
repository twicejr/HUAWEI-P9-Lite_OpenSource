/************************************************************************
*                                                                      *
*                             stac.c                                   *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2000/06/21                                      *
*  Author:             SHIY YONG                                       *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           STAC的实现和对外接口函数                        *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
*  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
*                      ALL RIGHTS RESERVED                             *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*                       STAC的实现和对外接口函数                         *
*                                                                      *
************************************************************************/



/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "ppp_inc.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_VSNCP_STAC_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

#if( VRP_MODULE_STAC == VRP_YES )
/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */


LONG STAC_InitStacCompress( STAC_COMPRESSINFO_S *pstInfo )
{

    pstInfo->pucInputStream = VOS_NULL_PTR;
    pstInfo->usInlen = 0;
    pstInfo->pucOutputStream = VOS_NULL_PTR;
    pstInfo->usOutlen = 0;

    pstInfo->usBufferTail = 0;
    pstInfo->pucHoldBuf = VOS_NULL_PTR;
    pstInfo->usHoldLen = 0;

    /*从最高位输出*/
    pstInfo->ucBitMask = 0x80;

    pstInfo->ucSequenceNum = 1;
    pstInfo->pucOutput = VOS_NULL_PTR;

    return STAC_SUCCESS;
}



VOID  STAC_ExitStacCompress( STAC_COMPRESSINFO_S * pstInfo )
{
    /* Deleted start by liutao 38563 at 2004-11-09 V800R002 for PPPC移植 */
 #if 0
    if (pstInfo->pstHashTable != VOS_NULL_PTR)
    {
        STAC_HASH_FreeHashTable( pstInfo->pstHashTable );
        pstInfo->pstHashTable = VOS_NULL_PTR;
    }

    if (pstInfo->pucBuffer != VOS_NULL_PTR)
    {
        (VOID)PPP_Free( pstInfo->pucBuffer );
        pstInfo->pucBuffer = VOS_NULL_PTR;
    }
 #endif

    /* Deleted end by liutao 38563 at 2004-11-09 V800R002 for PPPC移植 */

    /*回到开始状态*/
    pstInfo->pucInputStream = VOS_NULL_PTR;
    pstInfo->usInlen = 0;
    pstInfo->pucOutputStream = VOS_NULL_PTR;
    pstInfo->usOutlen = 0;
    pstInfo->usBufferTail = 0;
    pstInfo->pucHoldBuf = VOS_NULL_PTR;
    pstInfo->usHoldLen = 0;
    pstInfo->ucBitMask = 0x80;
    pstInfo->ucSequenceNum = 0;
    pstInfo->pucOutput = VOS_NULL_PTR;

    return;
}



LONG     STAC_InitStacDecompress( STAC_DECOMPRESSINFO_S *pstInfo )
{

    if(VOS_NULL_PTR == pstInfo)
    {
        VOS_DBGASSERT(pstInfo);
        return STAC_FAIL;
    }
    pstInfo->pucInputStream = VOS_NULL_PTR;
    pstInfo->pucInput = VOS_NULL_PTR;
    pstInfo->usInlen = 0;
    pstInfo->pucOutputStream = VOS_NULL_PTR;
    pstInfo->usOutlen   = 0;
    pstInfo->pucHoldBuf = VOS_NULL_PTR;
    pstInfo->usHoldLen  = 0;

    /*从最高位输入*/
    pstInfo->ucBitMask = 0x80;

    pstInfo->usBufferTail  = 0;
    pstInfo->ucSequenceNum = 1;

    pstInfo->ucResetReqSend = 0;

    pstInfo->ulTimeoutID   = 0;
    pstInfo->ulTimeOutTime = STAC_SENDRSTREQTIMEOUT;
    return STAC_SUCCESS;
}


VOID     STAC_ExitStacDecompress( STAC_DECOMPRESSINFO_S *pstInfo )
{

    if(VOS_NULL_PTR == pstInfo)
    {
        VOS_DBGASSERT(pstInfo);
        return;
    }
    /* Deleted end by liutao 38563 at 2004-11-09 V800R002 for PPPC移植 */
    pstInfo->pucBuffer = VOS_NULL_PTR;

    /*回到开始状态*/
    pstInfo->pucInputStream = VOS_NULL_PTR;
    pstInfo->pucInput = VOS_NULL_PTR;
    pstInfo->usInlen = 0;
    pstInfo->pucOutputStream = VOS_NULL_PTR;
    pstInfo->usOutlen   = 0;
    pstInfo->pucHoldBuf = VOS_NULL_PTR;
    pstInfo->usHoldLen  = 0;
    pstInfo->ucBitMask  = 0x80;

    pstInfo->usBufferTail  = 0;
    pstInfo->ucSequenceNum = 1;

    pstInfo->ucResetReqSend = 0;

    return;
}




VOID STAC_ResetHistorybuffer(STAC_COMPRESSINFO_S *pstInfo)
{

    if(VOS_NULL_PTR ==  pstInfo)
    {
        VOS_DBGASSERT(pstInfo);
        return;
    }

    /*置尾指针*/
    pstInfo->usBufferTail = 0;

    /*置相关标志位*/
    pstInfo->pstHashTable->ulHashTable_NextNode = 0L;
    pstInfo->pstHashTable->ucHashTable_Recycled = 0L;
    pstInfo->ucBitMask = 0x80;

}



#endif

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
