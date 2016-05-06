/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsmCtx.c
  版 本 号   : w00176964
  生成日期   : 2014年06月27日
  功能描述   : HSM模块上下文操作文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年02月3日
    作    者   : w00176964
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CnasCcb.h"
#include "CnasHsmCtx.h"
#include "PsCommonDef.h"
#include "PsTypeDef.h"
#include "CnasMntn.h"
#include "CnasHsmMntn.h"
#include "CnasHsmFsmTbl.h"
#include "CnasHsmSndAps.h"

#include "CnasHsmSndInternalMsg.h"

#include "CnasHsmKeepAlive.h"
#include "CnasHsmFsmCachedMsgPriMnmt.h"
#include "Nas_Mem.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSM_CTX_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* XSD CTX,用于保存MMC状态机,描述表 */
CNAS_HSM_CTX_STRU                       g_stCnasHsmCtx;

#ifdef DMT
    VOS_UINT32                          g_ulCurSessionSeed = 0;
#endif

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/


CNAS_HSM_CTX_STRU* CNAS_HSM_GetHsmCtxAddr(VOS_VOID)
{
    return &(g_stCnasHsmCtx);
}



CNAS_HSM_HRPD_CONN_CTRL_STRU* CNAS_HSM_GetHrpdConnCtrlInfoAddr(VOS_VOID)
{
    return &(CNAS_HSM_GetHsmCtxAddr()->stHrpdConnCtrlInfo);
}



CNAS_HSM_MS_CFG_INFO_STRU* CNAS_HSM_GetMsCfgInfoAddr(VOS_VOID)
{
    return &(CNAS_HSM_GetHsmCtxAddr()->stMsCfgInfo);
}



CNAS_HSM_PUBLIC_DATA_CTX_STRU* CNAS_HSM_GetPublicDataAddr(VOS_VOID)
{
    return &(CNAS_HSM_GetHsmCtxAddr()->stSessionCtrlInfo.stPublicData);
}



CNAS_HSM_ATI_RECORD_STRU* CNAS_HSM_GetTransmitATIAddr(VOS_VOID)
{
    return &(CNAS_HSM_GetHsmCtxAddr()->stSessionCtrlInfo.stPublicData.stTransmitATI);
}




CNAS_HSM_ATI_LIST_INFO_STRU* CNAS_HSM_GetReceivedATIListAddr(VOS_VOID)
{
    return &(CNAS_HSM_GetHsmCtxAddr()->stSessionCtrlInfo.stPublicData.stReceiveATIList);
}





CNAS_HSM_SESSION_CTRL_STRU* CNAS_HSM_GetSessionCtrlInfoAddr(VOS_VOID)
{
    return &(CNAS_HSM_GetHsmCtxAddr()->stSessionCtrlInfo);
}




CNAS_HSM_LOC_INFO_STRU* CNAS_HSM_GetLocInfoAddr(VOS_VOID)
{
    return &(CNAS_HSM_GetHsmCtxAddr()->stSessionCtrlInfo.stLocInfo);
}



CNAS_HSM_UATI_INFO_STRU* CNAS_HSM_GetUatiInfoAddr(VOS_VOID)
{
    return &(CNAS_HSM_GetHsmCtxAddr()->stSessionCtrlInfo.stUATIInfo);
}




CNAS_HSM_FSM_CTX_STRU* CNAS_HSM_GetCurFsmCtxAddr(VOS_VOID)
{
    return &(CNAS_HSM_GetHsmCtxAddr()->stCurFsmCtx);
}



CNAS_HSM_FSM_UATI_REQUEST_CTX_STRU* CNAS_HSM_GetUATIRequestFsmCtxAddr(VOS_VOID)
{
    return &(CNAS_HSM_GetCurFsmCtxAddr()->stUatiReqFsmCtx);
}



CNAS_HSM_KEEP_ALIVE_CTRL_CTX_STRU* CNAS_HSM_GetKeepAliveCtrlCtxAddr(VOS_VOID)
{
    return &(CNAS_HSM_GetHsmCtxAddr()->stKeepAliveCtrlCtx);
}


/*****************************************************************************
Function Name   :   CNAS_HSM_InitCacheMsgQueue
Description     :   Init the cached message queue
Input parameters:   pstCacheMsgQueue ----thecahed message queue pointer
Outout parameters:  NONE
Return Value    :   VOS_VOID
Modify History  :
1)  Date           : 2015-01-27
    Author         : w00176964
    Modify content : Create
 2.Date            : 8/9/2015
   Author          : w00176964
   Modification    : CNAS内存裁剪
*****************************************************************************/

VOS_VOID CNAS_HSM_InitCacheMsgQueue(
    CNAS_HSM_INIT_CTX_TYPE_ENUM_UINT8   enInitType,
    CNAS_HSM_CACHE_MSG_QUEUE_STRU      *pstCacheMsgQueue
)
{
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-8, begin */
    VOS_UINT32                          i;

    if (CNAS_HSM_INIT_CTX_STARTUP == enInitType)
    {
        pstCacheMsgQueue->ucCacheMsgNum = 0;

        for (i = 0; i < CNAS_HSM_MAX_CACHE_MSG_QUEUE_NUM; i++)
        {
            pstCacheMsgQueue->astCacheMsg[i].enMsgPri        = CNAS_HSM_MSG_PRI_LVL_0;
            pstCacheMsgQueue->astCacheMsg[i].pucMsgBuffer    = VOS_NULL_PTR;
        }
    }
    else
    {
        for (i = 0; i < (VOS_UINT32)pstCacheMsgQueue->ucCacheMsgNum; i++)
        {
            pstCacheMsgQueue->astCacheMsg[i].enMsgPri        = CNAS_HSM_MSG_PRI_LVL_0;

            if (VOS_NULL_PTR != pstCacheMsgQueue->astCacheMsg[i].pucMsgBuffer)
            {
                PS_MEM_FREE(UEPS_PID_HSM, pstCacheMsgQueue->astCacheMsg[i].pucMsgBuffer);
                pstCacheMsgQueue->astCacheMsg[i].pucMsgBuffer    = VOS_NULL_PTR;
            }
        }

        pstCacheMsgQueue->ucCacheMsgNum = 0;
    }

    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-8, end */
}



CNAS_HSM_CACHE_MSG_QUEUE_STRU* CNAS_HSM_GetCacheMsgAddr(VOS_VOID)
{
    return &(CNAS_HSM_GetHsmCtxAddr()->stCacheMsgQueue);
}

/*****************************************************************************
Function Name   :   CNAS_HSM_SaveCacheMsgInMsgQueue
Description     :   save the message to the cache message queue
Input parameters:   ulEventType--message ID+PID
                    pstMsg-------message content
Outout parameters:  NONE
Return Value    :   VOS_VOID
Modify History  :
1)  Date           : 2015-01-27
    Author         : w00176964
    Modify content : Create
2)  Date           : 2015-06-11
    Author         : m00312079
    Modify content : Add the priority to cached message
3)  Date           : 2015-08-31
    Author         : y00307564
    Modify content : DTS2015081400901 Modify
4) Date            : 8/9/2015
   Author          : w00176964
   Modification    : CNAS内存裁剪
5)  Date           : 2015-09-22
    Author         : t00323010
    Modify content : HSM MNTN(DTS2015092201636): log msg buff index
*****************************************************************************/

VOS_VOID CNAS_HSM_SaveCacheMsgInMsgQueue(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    CNAS_HSM_CACHE_MSG_QUEUE_STRU                          *pstMsgQueue   = VOS_NULL_PTR;
    MSG_HEADER_STRU                                        *pstMsgHeader  = VOS_NULL_PTR;
    CNAS_HSM_MSG_PRI_ENUM_UINT8                             enMsgPri;
    VOS_UINT8                                               ucIndex;

    CNAS_HSM_BUFFER_MSG_OPERATE_TYPE_ENUM_UINT32            enOperateType;

    enOperateType   = CNAS_HSM_BUFFER_MSG_OPERATE_TYPE_BUTT;

    pstMsgHeader    = (MSG_HEADER_STRU*)pstMsg;

    pstMsgQueue     = CNAS_HSM_GetCacheMsgAddr();

    if (CNAS_HSM_MAX_CACHE_MSG_QUEUE_NUM <= pstMsgQueue->ucCacheMsgNum)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_SaveCacheMsgInMsgQueue:No Empty buffer");

        /* log msg buff queue if full, add to msg buff queue fail */
        CNAS_HSM_LogBuffQueueFullInd();

        CNAS_HSM_LogBufferMsgInfo(pstMsgHeader, CNAS_HSM_MAX_CACHE_MSG_QUEUE_NUM, enOperateType);

        return;
    }

    ucIndex = CNAS_HSM_GetCacheIndexByEventType(ulEventType);

    if (CNAS_HSM_INVAILD_CACHE_INDEX != ucIndex)
    {
        enOperateType   = CNAS_HSM_BUFFER_MSG_OPERATE_TYPE_REPLACE;

        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-8, begin */
        if (VOS_NULL_PTR != pstMsgQueue->astCacheMsg[ucIndex].pucMsgBuffer)
        {
            PS_MEM_FREE(UEPS_PID_HSM, pstMsgQueue->astCacheMsg[ucIndex].pucMsgBuffer);
        }

        pstMsgQueue->astCacheMsg[ucIndex].pucMsgBuffer
                            = (VOS_UINT8 *)PS_MEM_ALLOC(UEPS_PID_HSM, pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH);

        if (VOS_NULL_PTR == pstMsgQueue->astCacheMsg[ucIndex].pucMsgBuffer)
        {
            return;
        }

        NAS_MEM_CPY_S(pstMsgQueue->astCacheMsg[ucIndex].pucMsgBuffer,
                      pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH,
                      pstMsgHeader,
                      pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH);
        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-8, end */
    }
    else
    {
        enOperateType   = CNAS_HSM_BUFFER_MSG_OPERATE_TYPE_ADD;
        ucIndex         = pstMsgQueue->ucCacheMsgNum;
        enMsgPri        = CNAS_HSM_FindMsgPri(ulEventType);

        pstMsgQueue->astCacheMsg[pstMsgQueue->ucCacheMsgNum].pucMsgBuffer
                            = (VOS_UINT8 *)PS_MEM_ALLOC(UEPS_PID_HSM, pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH);

        if (VOS_NULL_PTR == pstMsgQueue->astCacheMsg[pstMsgQueue->ucCacheMsgNum].pucMsgBuffer)
        {
            return;
        }

        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-8, begin */
        NAS_MEM_CPY_S(pstMsgQueue->astCacheMsg[pstMsgQueue->ucCacheMsgNum].pucMsgBuffer,
                      pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH,
                      pstMsgHeader,
                      pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH);

        pstMsgQueue->astCacheMsg[pstMsgQueue->ucCacheMsgNum].enMsgPri = enMsgPri;

        pstMsgQueue->ucCacheMsgNum++;
    }

    CNAS_HSM_LogBufferMsgInfo(pstMsgHeader, ucIndex, enOperateType);

    CNAS_INFO_LOG1(UEPS_PID_HSM, "CNAS_HSM_SaveCacheMsgInMsgQueue: Cache Num = %d", pstMsgQueue->ucCacheMsgNum);
}



VOS_UINT32  CNAS_HSM_SaveCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    MSG_HEADER_STRU                    *pstMsgHeader  = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    if ((CNAS_HSM_MAX_MSG_BUFFER_LEN - VOS_MSG_HEAD_LENGTH) < pstMsgHeader->ulLength)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_SaveCacheMsg:Len too Long");
        return VOS_FALSE;
    }

    CNAS_HSM_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    return VOS_TRUE;
}


/*****************************************************************************
Function Name   :   CNAS_HSM_ClearCacheMsgByIndex
Description     :   clear the cached message according to the speical index
Input parameters:   ucIndex----the index in the cache message queue
Outout parameters:  NONE
Return Value    :   VOS_VOID

Modify History  :
1)  Date           : 2015-01-27
    Author         : w00176964
    Modify content : Create
 2.Date            : 8/9/2015
   Author          : w00176964
   Modification    : CNAS内存裁剪
3)  Date           : 2015-09-23
    Author         : t00323010
    Modify content : HSM MNTN(DTS2015092201636): log buffer msg index
*****************************************************************************/
VOS_VOID CNAS_HSM_ClearCacheMsgByIndex(
    VOS_UINT8                           ucIndex
)
{
    CNAS_HSM_CACHE_MSG_QUEUE_STRU      *pstMsgQueue     = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader    = VOS_NULL_PTR;

    if (CNAS_HSM_MAX_CACHE_MSG_QUEUE_NUM <= ucIndex)
    {
        return;
    }

    pstMsgQueue = CNAS_HSM_GetCacheMsgAddr();

    if (0 < pstMsgQueue->ucCacheMsgNum)
    {
        pstMsgQueue->ucCacheMsgNum--;

        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-8, begin */
        if (VOS_NULL_PTR != pstMsgQueue->astCacheMsg[ucIndex].pucMsgBuffer)
        {
            /* log buff msg queue and msg info before delete the msg */
            pstMsgHeader = (MSG_HEADER_STRU *)pstMsgQueue->astCacheMsg[ucIndex].pucMsgBuffer;

            CNAS_HSM_LogBufferMsgInfo(pstMsgHeader, ucIndex, CNAS_HSM_BUFFER_MSG_OPERATE_TYPE_DEL);

            PS_MEM_FREE(UEPS_PID_HSM, pstMsgQueue->astCacheMsg[ucIndex].pucMsgBuffer);
            pstMsgQueue->astCacheMsg[ucIndex].pucMsgBuffer = VOS_NULL_PTR;
        }

        if (ucIndex < (CNAS_HSM_MAX_CACHE_MSG_QUEUE_NUM - 1))
        {
            NAS_MEM_MOVE_S(&(pstMsgQueue->astCacheMsg[ucIndex]),
                           (CNAS_HSM_MAX_CACHE_MSG_QUEUE_NUM - ucIndex) * sizeof(CNAS_HSM_CACHE_MSG_INFO_STRU),
                           &(pstMsgQueue->astCacheMsg[ucIndex + 1]),
                           (pstMsgQueue->ucCacheMsgNum - ucIndex) * sizeof(CNAS_HSM_CACHE_MSG_INFO_STRU));
        }

        NAS_MEM_SET_S(&(pstMsgQueue->astCacheMsg[pstMsgQueue->ucCacheMsgNum]),
                      sizeof(CNAS_HSM_CACHE_MSG_INFO_STRU),
                      0x0,
                      sizeof(CNAS_HSM_CACHE_MSG_INFO_STRU));
        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-8, end */
    }
}

/*****************************************************************************
Function Name   :   CNAS_HSM_GetHighestPriCachedMsg
Description     :   Get the most highest priority message in the cache message queue
Input parameters:   CNAS_HSM_CACHE_MSG_QUEUE_STRU      *pstMsgQueue
Outout parameters:
Return Value    :   VOS_UINT8                           ucIndex

Modify History  :
1)  Date           : 2015-06-11
    Author         : m00312079
    Modify content : Create
 2.Date            : 8/9/2015
   Author          : w00176964
   Modification    : CNAS内存裁剪
*****************************************************************************/
VOS_UINT8 CNAS_HSM_GetHighestPriCachedMsg(
     CNAS_HSM_CACHE_MSG_QUEUE_STRU      *pstMsgQueue
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucSize;
    CNAS_HSM_MSG_PRI_ENUM_UINT8         enMsgPri;
    CNAS_HSM_MSG_PRI_ENUM_UINT8         enTmpMsgPri;

    enMsgPri =  CNAS_HSM_MSG_PRI_LVL_BUTT;
    ucIndex  =  0;
    ucSize   =  pstMsgQueue->ucCacheMsgNum;

    for (ucLoop = 0; ucLoop < ucSize; ucLoop++)
    {
        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-8, begin */
        enTmpMsgPri = pstMsgQueue->astCacheMsg[ucLoop].enMsgPri;
        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-8, end */

        if (enTmpMsgPri < enMsgPri)
        {
            enMsgPri = enTmpMsgPri;
            ucIndex  = ucLoop;
        }
    }

    return ucIndex;
}

/*****************************************************************************
Function Name   :   CNAS_HSM_GetCacheIndexByEventType
Description     :   get hsm cache index by EventType
Input parameters:   VOS_UINT32                          ulEventType

Outout parameters:
Return Value    :   VOS_UINT8

Modify History  :
1)  Date           : 2015-06-25
    Author         : m00312079
    Modify content : Create
2)  Date           : 2015-08-31
    Author         : y00307564
    Modify content : DTS2015081400901 Modify
3) Date            : 8/9/2015
   Author          : w00176964
   Modification    : CNAS内存裁剪
*****************************************************************************/
VOS_UINT8 CNAS_HSM_GetCacheIndexByEventType(
     VOS_UINT32                          ulEventType
)
{
    CNAS_HSM_CACHE_MSG_QUEUE_STRU      *pstMsgQueue;
    VOS_UINT8                           ucLoop;
    /* Added by w00176964 for CNAS内存裁剪, 2015-9-8, begin */
    MSG_HEADER_STRU                    *pstCacheMsgHdr;
    VOS_UINT32                          ulCacheMsgEventType;
    REL_TIMER_MSG                      *pstTimerMsg;
    /* Added by w00176964 for CNAS内存裁剪, 2015-9-8, end */

    pstMsgQueue  = CNAS_HSM_GetCacheMsgAddr();

    for (ucLoop = 0; ucLoop < pstMsgQueue->ucCacheMsgNum; ucLoop++)
    {
        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-8, begin */
        pstCacheMsgHdr = (MSG_HEADER_STRU *)(pstMsgQueue->astCacheMsg[ucLoop].pucMsgBuffer);

        if (VOS_NULL_PTR == pstCacheMsgHdr)
        {
            continue;
        }

        if (VOS_PID_TIMER == pstCacheMsgHdr->ulSenderPid)
        {
            pstTimerMsg = (REL_TIMER_MSG *)pstCacheMsgHdr;

            ulCacheMsgEventType  = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstTimerMsg->ulName);
        }
        else
        {
            ulCacheMsgEventType = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstCacheMsgHdr->ulMsgName);
        }

        if (ulCacheMsgEventType == ulEventType)
        {
            return ucLoop;
        }
        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-8, end */
    }

    return CNAS_HSM_INVAILD_CACHE_INDEX;
}

/*****************************************************************************
Function Name   :   CNAS_HSM_GetNextCachedMsg
Description     :   Get next cached message in the cache message queue
Input parameters:   NONE
Outout parameters:  pstEntryMsg------the next cached message
Return Value    :   VOS_UINT32

Modify History  :
1)  Date           : 2015-01-27
    Author         : w00176964
    Modify content : Create
2)  Date           : 2015-06-11
    Author         : m00312079
    Modify content : Add the logic to process the highest priority message
 3.Date            : 8/9/2015
   Author          : w00176964
   Modification    : CNAS内存裁剪
*****************************************************************************/

VOS_UINT32 CNAS_HSM_GetNextCachedMsg(
    CNAS_HSM_MSG_STRU                  *pstCachedMsg
)
{
    CNAS_HSM_CACHE_MSG_QUEUE_STRU      *pstMsgQueue = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    /* Added by w00176964 for CNAS内存裁剪, 2015-9-8, begin */
    MSG_HEADER_STRU                    *pstCacheMsgHdr;
    REL_TIMER_MSG                      *pstTimerMsg;
    /* Added by w00176964 for CNAS内存裁剪, 2015-9-8, end */

    pstMsgQueue = CNAS_HSM_GetCacheMsgAddr();

    if ( 0 == pstMsgQueue->ucCacheMsgNum )
    {
        CNAS_INFO_LOG(UEPS_PID_HSM, "CNAS_HSM_GetNextCachedMsg:Empty buffer");

        return VOS_FALSE;
    }

    ucIndex = CNAS_HSM_GetHighestPriCachedMsg(pstMsgQueue);

    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-8, begin */
    pstCacheMsgHdr = (MSG_HEADER_STRU *)pstMsgQueue->astCacheMsg[ucIndex].pucMsgBuffer;

    if (VOS_NULL_PTR == pstCacheMsgHdr)
    {
        return VOS_FALSE;
    }

    NAS_MEM_CPY_S(&(pstCachedMsg->aucMsgBuffer[0]),
                  sizeof(pstCachedMsg->aucMsgBuffer),
                  pstCacheMsgHdr,
                  pstCacheMsgHdr->ulLength + VOS_MSG_HEAD_LENGTH);

    if (VOS_PID_TIMER == pstCacheMsgHdr->ulSenderPid)
    {
        pstTimerMsg = (REL_TIMER_MSG *)pstCacheMsgHdr;

        pstCachedMsg->ulEventType  = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstTimerMsg->ulName);
    }
    else
    {
        pstCachedMsg->ulEventType = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstCacheMsgHdr->ulMsgName);
    }

    pstCachedMsg->enMsgPri    = pstMsgQueue->astCacheMsg[ucIndex].enMsgPri;
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-8, end */

    CNAS_HSM_ClearCacheMsgByIndex(ucIndex);

    return VOS_TRUE;
}



VOS_UINT8 CNAS_HSM_GetCacheMsgNum(VOS_VOID)
{
    CNAS_HSM_CACHE_MSG_QUEUE_STRU      *pstMsgQueue = VOS_NULL_PTR;

    pstMsgQueue = CNAS_HSM_GetCacheMsgAddr();

    return pstMsgQueue->ucCacheMsgNum;
}



VOS_VOID CNAS_HSM_InitIntMsgQueue(
    CNAS_HSM_INT_MSG_QUEUE_STRU        *pstIntMsgQueue
)
{
    VOS_UINT8                          i;

    for (i = 0; i < CNAS_HSM_MAX_INT_MSG_QUEUE_NUM; i++)
    {
        pstIntMsgQueue->pastIntMsg[i] = VOS_NULL_PTR;
    }

    pstIntMsgQueue->ucIntMsgNum = 0;
}




CNAS_HSM_INT_MSG_QUEUE_STRU* CNAS_HSM_GetIntMsgQueueAddr(VOS_VOID)
{
    return &(CNAS_HSM_GetHsmCtxAddr()->stIntMsgQueue);
}



VOS_VOID CNAS_HSM_PutMsgInIntMsgQueue(
    VOS_UINT8                          *pstMsg
)
{
    VOS_UINT8                           ucIntMsgNum;
    CNAS_HSM_INT_MSG_QUEUE_STRU        *pstMsgQueue = VOS_NULL_PTR;

    pstMsgQueue = CNAS_HSM_GetIntMsgQueueAddr();

    if (CNAS_HSM_MAX_INT_MSG_QUEUE_NUM <= CNAS_HSM_GetIntMsgNum())
    {
        PS_MEM_FREE(UEPS_PID_HSM, pstMsg);

        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_PutMsgInIntMsgQueue: msg queue is full!" );

        return;
    }

    ucIntMsgNum = pstMsgQueue->ucIntMsgNum;

    pstMsgQueue->pastIntMsg[ucIntMsgNum] = pstMsg;

    pstMsgQueue->ucIntMsgNum = (ucIntMsgNum + 1);

    return;
}



VOS_UINT8 *CNAS_HSM_GetNextIntMsg(VOS_VOID)
{
    VOS_UINT8                           ucIntMsgNum;
    VOS_UINT8                          *pstIntMsg = VOS_NULL_PTR;
    CNAS_HSM_INT_MSG_QUEUE_STRU        *pstMsgQueue = VOS_NULL_PTR;

    pstMsgQueue = CNAS_HSM_GetIntMsgQueueAddr();

    ucIntMsgNum = CNAS_HSM_GetIntMsgQueueAddr()->ucIntMsgNum;

    if (0 < ucIntMsgNum)
    {
        pstIntMsg = pstMsgQueue->pastIntMsg[0];

        /* reduce the internal message number */
        ucIntMsgNum--;

        if (0 != ucIntMsgNum)
        {
            NAS_MEM_MOVE_S(&(pstMsgQueue->pastIntMsg[0]),
                           sizeof(pstMsgQueue->pastIntMsg),
                           &(pstMsgQueue->pastIntMsg[1]),
                           ucIntMsgNum * sizeof(VOS_UINT8 *));
        }

        pstMsgQueue->pastIntMsg[ucIntMsgNum] = VOS_NULL_PTR;

        pstMsgQueue->ucIntMsgNum = ucIntMsgNum;
    }

    return pstIntMsg;
}



VOS_UINT32 CNAS_HSM_GetIntMsgNum(VOS_VOID)
{
    CNAS_HSM_INT_MSG_QUEUE_STRU        *pstMsgQueue = VOS_NULL_PTR;

    pstMsgQueue = CNAS_HSM_GetIntMsgQueueAddr();

    return pstMsgQueue->ucIntMsgNum;
}

/* Deleted by w00176964 for CNAS内存裁剪, 2015-9-18, begin */

/* Deleted by w00176964 for CNAS内存裁剪, 2015-9-18, end */


CNAS_HSM_HARDWARE_ID_INFO_STRU* CNAS_HSM_GetHardwareIdInfo(VOS_VOID)
{
    return &(CNAS_HSM_GetMsCfgInfoAddr()->stCustomCfgInfo.stNvimHwid);
}



VOS_VOID CNAS_HSM_InitUATIReqFsmCtx(
    CNAS_HSM_FSM_UATI_REQUEST_CTX_STRU *pstUATIReqFsmCtx
)
{
    pstUATIReqFsmCtx->ucUATIAssignTimerExpiredCnt = 0;
    pstUATIReqFsmCtx->ucUATIReqFailedCnt          = 0;
    pstUATIReqFsmCtx->ucAbortFlg                  = VOS_FALSE;
}


VOS_VOID CNAS_HSM_InitSessionDeactiveFsmCtx(
    CNAS_HSM_FSM_SESSION_DEACTIVE_CTX_STRU                  *pstSessionDeactiveFsmCtx
)
{
    pstSessionDeactiveFsmCtx->enSessionDeactReason = CNAS_HSM_SESSION_DEACT_REASON_BUTT;
    pstSessionDeactiveFsmCtx->ucAbortFlg           = VOS_FALSE;

    pstSessionDeactiveFsmCtx->enReviseTimerScene   = CNAS_HSM_SESSION_DEACT_REVISE_TIMER_SCENE_BUTT;
}


VOS_VOID CNAS_HSM_InitSessionActiveFsmCtx(
    CNAS_HSM_FSM_SESSION_ACTIVE_CTX_STRU *pstSessionActFsmCtx
)
{
    pstSessionActFsmCtx->ucAbortFlg             = VOS_FALSE;
    pstSessionActFsmCtx->enSessionActiveReason  = CNAS_HSM_SESSION_ACTIVE_REASON_BUTT;
    pstSessionActFsmCtx->ucIsGetPaNtf           = VOS_FALSE;

    NAS_MEM_SET_S(pstSessionActFsmCtx->aucRsv, sizeof(pstSessionActFsmCtx->aucRsv), 0, sizeof(pstSessionActFsmCtx->aucRsv));
}


VOS_VOID CNAS_HSM_InitConnMnmtFsmCtx(
    CNAS_HSM_FSM_CONN_MNMT_CTX_STRU *pstConnMnmtFsmCtx
)
{
    pstConnMnmtFsmCtx->ucAbortFlg        = VOS_FALSE;
    pstConnMnmtFsmCtx->enTriggerScene    = CNAS_HSM_CONN_MNMT_TRIGGER_BUTT;

    NAS_MEM_SET_S(pstConnMnmtFsmCtx->aucRsv, sizeof(pstConnMnmtFsmCtx->aucRsv), 0, sizeof(pstConnMnmtFsmCtx->aucRsv));
}



VOS_VOID CNAS_HSM_InitReadCardInfo(
    CNAS_HSM_FSM_SWITCH_ON_CTX_STRU    *pstCardReadInfo
)
{
    pstCardReadInfo->ulWaitCardReadFlag = CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_NULL;
}



VOS_VOID CNAS_HSM_InitKeepAliveCtrlCtx(
    CNAS_HSM_KEEP_ALIVE_CTRL_CTX_STRU       *pstKeepAliveCtrlCtx
)
{
    NAS_MEM_SET_S(pstKeepAliveCtrlCtx, sizeof(CNAS_HSM_KEEP_ALIVE_CTRL_CTX_STRU), 0x00, sizeof(CNAS_HSM_KEEP_ALIVE_CTRL_CTX_STRU));

    /* Set the Initial Sys Tick to zero */
    pstKeepAliveCtrlCtx->ulReferenceSysTick   = 0;

    /* Set the Keep Alive transaction IDs to zero */
    pstKeepAliveCtrlCtx->ucKeepAliveReqTransId = 0;

    /* Init the Session Keep Alive Info */
    NAS_MEM_SET_S(&(pstKeepAliveCtrlCtx->stSessionKeepAliveInfo),
                  sizeof(pstKeepAliveCtrlCtx->stSessionKeepAliveInfo),
                  0x00,
                  sizeof(pstKeepAliveCtrlCtx->stSessionKeepAliveInfo));

    pstKeepAliveCtrlCtx->stSessionKeepAliveInfo.ucIsKeepAliveInfoValid = VOS_FALSE;

    /* Set the TsmpClose and the TsmpClose Remain Len to default value of 54 hours. The unit is minutes */
    pstKeepAliveCtrlCtx->stSessionKeepAliveInfo.usTsmpClose           = CNAS_HSM_DEFAULT_TSMP_CLOSE_LEN;
    pstKeepAliveCtrlCtx->stSessionKeepAliveInfo.ulTsmpCloseRemainTime = CNAS_HSM_DEFAULT_TSMP_CLOSE_REMAIN_LEN;

    /* Init the Keep Alive Timer Info */
    pstKeepAliveCtrlCtx->stKeepAliveTimerInfo.ucKeepAliveReqSndCount  = 0;
    pstKeepAliveCtrlCtx->stKeepAliveTimerInfo.ulKeepAliveTimerLen     = 0;
    pstKeepAliveCtrlCtx->stKeepAliveTimerInfo.ulSysTickFwdTrafChan    = 0;
    pstKeepAliveCtrlCtx->stKeepAliveTimerInfo.ulOldSysTickFwdTrafChan = 0;
    pstKeepAliveCtrlCtx->stKeepAliveTimerInfo.ulTimerExpiredCount     = 0;
    pstKeepAliveCtrlCtx->stKeepAliveTimerInfo.ulTotalTimerRunCount    = 0;
}





VOS_VOID CNAS_HSM_InitCurFsmCtx(
    CNAS_HSM_FSM_CTX_STRU              *pstCurFsmCtx
)
{
    pstCurFsmCtx->enMainState = CNAS_HSM_L1_STA_NULL;
    pstCurFsmCtx->enSubState  = CNAS_HSM_SS_VACANT;

    CNAS_HSM_InitUATIReqFsmCtx(&pstCurFsmCtx->stUatiReqFsmCtx);

    CNAS_HSM_InitSessionDeactiveFsmCtx(&pstCurFsmCtx->stSessionDeactiveFsmCtx);

    CNAS_HSM_InitSessionActiveFsmCtx(&pstCurFsmCtx->stSessionActiceFsmCtx);
    CNAS_HSM_InitConnMnmtFsmCtx(&pstCurFsmCtx->stConnMnmtFsmCtx);


    CNAS_HSM_InitReadCardInfo(&pstCurFsmCtx->stCardReadInfo);
}



VOS_VOID CNAS_HSM_InitATIRecord(
    CNAS_HSM_ATI_RECORD_STRU           *pstATIRecord
)
{
    VOS_UINT8                           i;

    pstATIRecord->enATIType  = CNAS_HSM_ATI_TYPE_INACTIVE;

    pstATIRecord->ulAddrTimerLen = 0;

    for (i = 0; i < CNAS_HSM_ATI_VALUE_LENGTH; i++)
    {
        pstATIRecord->aucATIValue[i] = CNAS_HSM_INVALID_ATI_VALUE;
    }

    NAS_MEM_SET_S(&pstATIRecord->aucRsv[0], sizeof(pstATIRecord->aucRsv), 0x0, sizeof(VOS_UINT8) * 3);
}


VOS_VOID CNAS_HSM_InitATIList(
    CNAS_HSM_ATI_LIST_INFO_STRU        *pstATIListInfo
)
{
    VOS_UINT8                           i;

    pstATIListInfo->ulATIRecordNum = 0;

    /* Update ReceiveATIList */
    for (i = 0; i < CNAS_HSM_MAX_UATI_REC_NUM; i++)
    {
        CNAS_HSM_InitATIRecord(&(pstATIListInfo->astATIEntry[i]));
    }
}



VOS_VOID CNAS_HSM_InitPublicData(
    CNAS_HSM_PUBLIC_DATA_CTX_STRU      *pstPublicData
)
{
    pstPublicData->ulSessionSeed = 0;

    CNAS_HSM_InitATIRecord(&pstPublicData->stTransmitATI);

    CNAS_HSM_InitATIList(&pstPublicData->stReceiveATIList);
}



VOS_VOID CNAS_HSM_InitMsCfgInfo(
    CNAS_HSM_MS_CFG_INFO_STRU          *pstMsCfgInfo
)
{
    pstMsCfgInfo->stCustomCfgInfo.stNvimHwid.enHwidType     = CNAS_HSM_HARDWARE_ID_TYPE_NULL;

    NAS_MEM_SET_S(&pstMsCfgInfo->stCustomCfgInfo.stNvimHwid.ulEsn,
                  sizeof(pstMsCfgInfo->stCustomCfgInfo.stNvimHwid.ulEsn),
                  0x0,
                  sizeof(VOS_UINT32));

    NAS_MEM_SET_S(&pstMsCfgInfo->stCustomCfgInfo.stNvimHwid.aucMeId[0],
                  sizeof(pstMsCfgInfo->stCustomCfgInfo.stNvimHwid.aucMeId),
                  0x0,
                  sizeof(VOS_UINT8) * CNAS_HSM_MEID_OCTET_NUM);

    CNAS_HSM_InitUERevInfo(&(pstMsCfgInfo->stCustomCfgInfo.stHrpdUERevInfo));

    CNAS_HSM_InitLastHrpdSessionInfo(&(pstMsCfgInfo->stCustomCfgInfo.stHrpdNvimSessInfo));

    CNAS_HSM_InitLastHrpdNvimAccessAuthInfo(&(pstMsCfgInfo->stCustomCfgInfo.stHrpdNvimAccessAuthInfo));
}



VOS_VOID CNAS_HSM_InitMntnInfo(
    CNAS_HSM_MAINTAIN_CTX_STRU         *pstMntnInfo
)
{
    NAS_MEM_SET_S(&pstMntnInfo->aucReserve[0], sizeof(pstMntnInfo->aucReserve), 0x0, sizeof(VOS_UINT8) * 4);
}



VOS_VOID CNAS_HSM_InitHrpdConnCtrlInfo(
    CNAS_HSM_HRPD_CONN_CTRL_STRU       *pstCallCtrlInfo
)
{
    pstCallCtrlInfo->enHrpdConvertedCasStatus        = CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT;
    pstCallCtrlInfo->enHrpdOriginalCasStatus         = CAS_CNAS_HRPD_CAS_STATUS_ENUM_NONE;
    pstCallCtrlInfo->ucHsmCallId                     = CNAS_HSM_CALL_ID_INVALID;
    pstCallCtrlInfo->enConnStatus                    = CNAS_HSM_HRPD_CONN_STATUS_CLOSE;
}



VOS_VOID CNAS_HSM_InitUATIInfo(
    CNAS_HSM_UATI_INFO_STRU            *pstUATIInfo
)
{
    NAS_MEM_SET_S(pstUATIInfo, sizeof(CNAS_HSM_UATI_INFO_STRU), 0x0, sizeof(CNAS_HSM_UATI_INFO_STRU));
}


VOS_VOID CNAS_HSM_InitSessionActiveCtx(
    CNAS_HSM_SESSION_ACTIVE_CTRL_CTX_STRU                  *pstSessionActiveCtrlCtx
)
{
    pstSessionActiveCtrlCtx->ucSessionActTriedCntConnFail  = 0;
    pstSessionActiveCtrlCtx->ucSessionActTriedCntOtherFail = 0;
    pstSessionActiveCtrlCtx->ucSessionActMaxCntConnFail    = CNAS_HSM_DEFAULT_SESSION_ACT_MAX_CNT_CONN_FAIL;
    pstSessionActiveCtrlCtx->ucSessionActMaxCntOtherFail   = CNAS_HSM_DEFAULT_SESSION_ACT_MAX_CNT_OTHER_FAIL;
    pstSessionActiveCtrlCtx->ulSessionActTimerLen          = TI_CNAS_HSM_DEFAULT_UATI_SESSION_ACT_PROTECT_TIMER_LEN;
    pstSessionActiveCtrlCtx->usScpActFailProtType          = 0;
    pstSessionActiveCtrlCtx->usScpActFailProtSubtype       = 0;
    pstSessionActiveCtrlCtx->enReqSessionTypeForRetry      = CNAS_HSM_SESSION_TYPE_BUTT;
     pstSessionActiveCtrlCtx->ucIsExplicitlyConnDenyFlg    = VOS_FALSE;
}



VOS_VOID CNAS_HSM_InitSessionCtrlInfo(
    CNAS_HSM_INIT_CTX_TYPE_ENUM_UINT8   enInitType,
    CNAS_HSM_SESSION_CTRL_STRU         *pstSessionCtrlInfo
)
{
    pstSessionCtrlInfo->enRcvOhmScene                   = CNAS_HSM_RCV_OHM_SCENE_FOLLOW_OHM;
    pstSessionCtrlInfo->ucUATIReqTransId                = 1;
    pstSessionCtrlInfo->ucIsSessionNegOngoing           = VOS_FALSE;
    pstSessionCtrlInfo->ucIsScpActive                   = VOS_FALSE;

    CNAS_HSM_SetSessionStatus(CNAS_HSM_SESSION_STATUS_CLOSE);
    CNAS_HSM_SetCurrSessionRelType(CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);

    CNAS_HSM_InitUATIInfo(&pstSessionCtrlInfo->stUATIInfo);

    CNAS_HSM_InitPublicData(&(pstSessionCtrlInfo->stPublicData));

    CNAS_HSM_InitSessionActiveCtx(&(pstSessionCtrlInfo->stSessionActiveCtrlCtx));

    pstSessionCtrlInfo->ucStartUatiReqAfterSectorIdChgFlg = VOS_TRUE;

    /* Set the First System Acquire Ind flag to TRUE */
    pstSessionCtrlInfo->ucIsFirstSysAcq         = VOS_TRUE;

    pstSessionCtrlInfo->enReqSessionType        = CNAS_HSM_SESSION_TYPE_BUTT;
    pstSessionCtrlInfo->enNegoSessionType       = CNAS_HSM_SESSION_TYPE_BUTT;

    pstSessionCtrlInfo->enLatestSessionDeactReason = CNAS_HSM_SESSION_DEACT_REASON_BUTT;

    pstSessionCtrlInfo->ucUatiReqRetryTimesWhenUatiAssignTimerExpireInAmpOpen = 0;

    pstSessionCtrlInfo->ucUatiCompleteRetryTimes = 0;

    NAS_MEM_SET_S(pstSessionCtrlInfo->aucPrevUatiForSessionRestore, sizeof(pstSessionCtrlInfo->aucPrevUatiForSessionRestore), 0, CNAS_HSM_UATI_OCTET_LENGTH);

    NAS_MEM_SET_S(&(pstSessionCtrlInfo->stLastHrpdUERevInfo), sizeof(pstSessionCtrlInfo->stLastHrpdUERevInfo), 0x00, sizeof(CNAS_NVIM_HRPD_UE_REV_INFO_STRU));

    NAS_MEM_SET_S(&(pstSessionCtrlInfo->stSessionCloseInfo), sizeof(pstSessionCtrlInfo->stSessionCloseInfo), 0x00, sizeof(CNAS_HSM_SESSION_CLOSE_INFO_STRU));

    CNAS_HSM_InitStoreEsnMeidRsltInfo(enInitType, &(pstSessionCtrlInfo->stStoreEsnMeidRslt));
    CNAS_HSM_InitHsmCardStatusInfo(enInitType, &(pstSessionCtrlInfo->stCardStatusChgInfo));

    CNAS_HSM_InitWaitUatiAssignTimerLenInfo();


    /* 删除本处可维可测, 如果MMA任务初始化在HSM初始化之后，会造成系统会崩掉 */
}


VOS_VOID CNAS_HSM_InitMultiModeCtrlInfo(
    CNAS_HSM_MULTI_MODE_CTRL_INFO_STRU         *pstMultiModeCtrlInfo
)
{
    pstMultiModeCtrlInfo->ucLteRegSuccFlg   = VOS_FALSE;
}


VOS_VOID CNAS_HSM_InitLastHrpdSessionInfo(
    CNAS_HSM_LAST_HRPD_SESSION_INFO_STRU                   *pstHrpdNvimSessInfo
)
{
    pstHrpdNvimSessInfo->enSessionStatus = CNAS_HSM_SESSION_STATUS_CLOSE;
    pstHrpdNvimSessInfo->enSessionType   = CNAS_HSM_SESSION_TYPE_BUTT;

    NAS_MEM_SET_S(&(pstHrpdNvimSessInfo->stHwid),
                  sizeof(pstHrpdNvimSessInfo->stHwid),
                  0x00,
                  sizeof(CNAS_HSM_HARDWARE_ID_INFO_STRU));

    pstHrpdNvimSessInfo->stHwid.enHwidType = CNAS_HSM_HARDWARE_ID_TYPE_NULL;
}


VOS_VOID CNAS_HSM_InitUERevInfo(
    CNAS_NVIM_HRPD_UE_REV_INFO_STRU*                        pstHrpdUERevInfo
)
{
    /* 默认支持EHRPD */
    pstHrpdUERevInfo->enSuppOnlyDo0         = PS_FALSE;

    pstHrpdUERevInfo->enSuppDoaWithMfpa     = PS_TRUE;
    pstHrpdUERevInfo->enSuppDoaWithEmfpa    = PS_TRUE;
    pstHrpdUERevInfo->enSuppDoaEhrpd        = PS_TRUE;
}


VOS_VOID CNAS_HSM_InitHrpdAmpNegAttrib(
    CNAS_HSM_HRPD_AMP_NEG_ATTRIB_STRU  *pstHrpdAmpNegAttibInfo
)
{
    pstHrpdAmpNegAttibInfo->usHardwareSeparableFromSession    = 0;
    pstHrpdAmpNegAttibInfo->usMaxNoMonitorDistance            = 0;
    pstHrpdAmpNegAttibInfo->usReducedSubnetMaskOffset         = 0;
    pstHrpdAmpNegAttibInfo->usSupportGAUPMaxNoMonitorDistance = 0;
    pstHrpdAmpNegAttibInfo->usSupportSecondaryColorCodes      = 0;
}


VOS_VOID CNAS_HSM_InitSnpDataReqCtrlInfo(
    CNAS_HSM_SNP_DATA_REQ_OPID_CTRL_STRU                   *pstSnpDataReqCtrlInfo
)
{
    pstSnpDataReqCtrlInfo->usHsmSnpDataReqOpId      = 0;
    pstSnpDataReqCtrlInfo->stSaveSnpDataReqOpId.usSessionCloseOpId      = 0;
    pstSnpDataReqCtrlInfo->stSaveSnpDataReqOpId.usUatiReqOpId           = 0;
    pstSnpDataReqCtrlInfo->stSaveSnpDataReqOpId.usUatiCmplOpId          = 0;
    pstSnpDataReqCtrlInfo->stSaveSnpDataReqOpId.usHardWareIdRspOpId     = 0;
    pstSnpDataReqCtrlInfo->stSaveSnpDataReqOpId.usKeepAliveReqOpId      = 0;
    pstSnpDataReqCtrlInfo->stSaveSnpDataReqOpId.usKeepALiveRspOpId      = 0;
}



VOS_VOID CNAS_HSM_InitLastHrpdNvimAccessAuthInfo(
    CNAS_CCB_HRPD_ACCESS_AUTH_INFO_STRU                    *pstLastHrpdNvimAccessAuthInfo
)
{
    NAS_MEM_SET_S(pstLastHrpdNvimAccessAuthInfo, sizeof(CNAS_CCB_HRPD_ACCESS_AUTH_INFO_STRU), 0x0, sizeof(CNAS_CCB_HRPD_ACCESS_AUTH_INFO_STRU));

    pstLastHrpdNvimAccessAuthInfo->ucAccessAuthAvailFlag = VOS_FALSE;
}



VOS_VOID CNAS_HSM_InitStoreEsnMeidRsltInfo(
    CNAS_HSM_INIT_CTX_TYPE_ENUM_UINT8   enInitType,
    CNAS_HSM_STORE_ESN_MEID_RSLT_STRU  *pstStoreEsnMeidRslt
)
{
    if (CNAS_HSM_INIT_CTX_STARTUP == enInitType)
    {
        pstStoreEsnMeidRslt->ucIsStored  = VOS_FALSE;
        pstStoreEsnMeidRslt->ucIsChanged = VOS_FALSE;
    }
}



VOS_VOID CNAS_HSM_InitHsmCardStatusInfo(
    CNAS_HSM_INIT_CTX_TYPE_ENUM_UINT8                       enInitType,
    CNAS_HSM_CARD_STATUS_CHANGE_INFO_STRU                  *pstCardStatusChangeInfo
)
{
    if (CNAS_HSM_INIT_CTX_STARTUP == enInitType)
    {
        NAS_MEM_SET_S(pstCardStatusChangeInfo, sizeof(CNAS_HSM_CARD_STATUS_CHANGE_INFO_STRU), 0x00, sizeof(CNAS_HSM_CARD_STATUS_CHANGE_INFO_STRU));

        pstCardStatusChangeInfo->ucIsPreCardPresent    = VOS_FALSE;
        pstCardStatusChangeInfo->ucIsCurCardPresent    = VOS_FALSE;
    }
}




VOS_VOID CNAS_HSM_InitCtx(
    CNAS_HSM_INIT_CTX_TYPE_ENUM_UINT8   enInitType
)
{
    CNAS_HSM_CTX_STRU                  *pstHsmCtx;

    pstHsmCtx = CNAS_HSM_GetHsmCtxAddr();

    CNAS_HSM_InitCurFsmCtx(&pstHsmCtx->stCurFsmCtx);

    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-18, begin */
    CNAS_HSM_InitCacheMsgQueue(enInitType, &(pstHsmCtx->stCacheMsgQueue));
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-18, end */

    CNAS_HSM_InitIntMsgQueue(&(pstHsmCtx->stIntMsgQueue));

    CNAS_HSM_InitHrpdConnCtrlInfo(&(pstHsmCtx->stHrpdConnCtrlInfo));

    CNAS_HSM_InitMntnInfo(&(pstHsmCtx->stMntnInfo));

    CNAS_HSM_InitSessionCtrlInfo(enInitType, &(pstHsmCtx->stSessionCtrlInfo));

    CNAS_HSM_InitMsCfgInfo(&(pstHsmCtx->stMsCfgInfo));

    CNAS_HSM_InitKeepAliveCtrlCtx(&(pstHsmCtx->stKeepAliveCtrlCtx));

    CNAS_HSM_InitMultiModeCtrlInfo(&pstHsmCtx->stMultiModeCtrlInfo);

    CNAS_HSM_InitHrpdAmpNegAttrib(&pstHsmCtx->stHrpdAmpNegAttibInfo);

    CNAS_HSM_InitSnpDataReqCtrlInfo(&pstHsmCtx->stSnpDataReqCtrlInfo);
    CNAS_HSM_SetSlotVoteBox(0);
}



VOS_UINT8 CNAS_HSM_GetUATIAssignTimerExpiredCnt(VOS_VOID)
{
    return (CNAS_HSM_GetHsmCtxAddr()->stCurFsmCtx.stUatiReqFsmCtx.ucUATIAssignTimerExpiredCnt);
}



VOS_UINT8 CNAS_HSM_GetUATIReqFailedCnt(VOS_VOID)
{
    return (CNAS_HSM_GetHsmCtxAddr()->stCurFsmCtx.stUatiReqFsmCtx.ucUATIReqFailedCnt);
}




VOS_VOID CNAS_HSM_IncreaseUATITransId(VOS_VOID)
{
    VOS_UINT8                           ucTI;

    ucTI = (CNAS_HSM_GetHsmCtxAddr()->stSessionCtrlInfo.ucUATIReqTransId);

    ucTI++;
    ucTI = ucTI % 256;

    (CNAS_HSM_GetHsmCtxAddr()->stSessionCtrlInfo.ucUATIReqTransId) = ucTI;
}



VOS_UINT8 CNAS_HSM_GetUATITransId(VOS_VOID)
{
    return (CNAS_HSM_GetHsmCtxAddr()->stSessionCtrlInfo.ucUATIReqTransId);
}



VOS_UINT8 CNAS_HSM_GetCurrUATIAssignMsgSeqNum(VOS_VOID)
{
    return (CNAS_HSM_GetHsmCtxAddr()->stSessionCtrlInfo.ucUATIAssignMsgSeq);
}



VOS_VOID CNAS_HSM_SetCurrUATIAssignMsgSeqNum(
    VOS_UINT8                           ucSeqNum
)
{
    (CNAS_HSM_GetHsmCtxAddr()->stSessionCtrlInfo.ucUATIAssignMsgSeq) = ucSeqNum;
}





VOS_VOID CNAS_HSM_IncreaseUATIAssignTimerExpiredCnt(VOS_VOID)
{
    (CNAS_HSM_GetHsmCtxAddr()->stCurFsmCtx.stUatiReqFsmCtx.ucUATIAssignTimerExpiredCnt)++;
}



VOS_VOID CNAS_HSM_IncreaseUATIReqFailedCnt(VOS_VOID)
{
    (CNAS_HSM_GetHsmCtxAddr()->stCurFsmCtx.stUatiReqFsmCtx.ucUATIReqFailedCnt)++;
}




VOS_VOID CNAS_HSM_ResetUATIReqFailedCnt(VOS_VOID)
{
    (CNAS_HSM_GetHsmCtxAddr()->stCurFsmCtx.stUatiReqFsmCtx.ucUATIReqFailedCnt) = 0;
}

/*****************************************************************************
Function Name   :   CNAS_HSM_SetCurrMainState
Description     :   Set Current Main State
Input parameters:   ulMainState---the main state
Outout parameters:  None
Return Value    :   VOS_VOID

Modify History  :
1)  Date           : 2015-01-27
    Author         : w00176964
    Modify content : Create

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity
*****************************************************************************/

VOS_VOID  CNAS_HSM_SetCurrMainState(
    CNAS_HSM_L1_STA_ENUM_UINT32         enMainState
)
{
    CNAS_HSM_L1_STA_ENUM_UINT32         enOldMainState;

    enOldMainState = CNAS_HSM_GetCurrMainState();

    if (CNAS_HSM_L1_STA_ID_BUTT == enOldMainState)
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_SetCurrMainState: Curr MainState is BUTT!");
    }

    CNAS_HSM_GetCurFsmCtxAddr()->enMainState = enMainState;

    CNAS_HSM_LogFsmStateInfoInd(ID_CNAS_HSM_MNTN_LOG_FSM_MAIN_STATE_INFO_IND, enOldMainState, enMainState);

    return;
}



VOS_VOID  CNAS_HSM_SetCurrSubState(
    CNAS_HSM_SS_ID_ENUM_UINT32          enSubState
)
{
    CNAS_HSM_SS_ID_ENUM_UINT32          enOldSubState;

    enOldSubState = CNAS_HSM_GetCurrSubState();

    if (CNAS_HSM_SS_ID_BUTT == enOldSubState)
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_SetCurrSubState: Curr SubState is BUTT!");
    }

    CNAS_HSM_GetCurFsmCtxAddr()->enSubState = enSubState;

    CNAS_HSM_LogFsmStateInfoInd(ID_CNAS_HSM_MNTN_LOG_FSM_SUB_STATE_INFO_IND, enOldSubState, enSubState);

    return;
}



CNAS_HSM_L1_STA_ENUM_UINT32  CNAS_HSM_GetCurrMainState(VOS_VOID)
{
    return (CNAS_HSM_GetCurFsmCtxAddr()->enMainState);
}



CNAS_HSM_SS_ID_ENUM_UINT32  CNAS_HSM_GetCurrSubState(VOS_VOID)
{
    return (CNAS_HSM_GetCurFsmCtxAddr()->enSubState);
}


VOS_VOID  CNAS_HSM_SetSessionSeed(
    VOS_UINT32                          ulSessionSeed
)
{
    CNAS_HSM_GetHsmCtxAddr()->stSessionCtrlInfo.stPublicData.ulSessionSeed = ulSessionSeed;
}


VOS_UINT32  CNAS_HSM_GetSessionSeed(VOS_VOID)
{
#ifdef DMT
    return g_ulCurSessionSeed;
#else
    return CNAS_HSM_GetHsmCtxAddr()->stSessionCtrlInfo.stPublicData.ulSessionSeed;
#endif
}


VOS_VOID  CNAS_HSM_SetStartUatiReqAfterSectorIdChgFlg(
    VOS_UINT8                          ucStartUatiReqAfterSectorIdChgFlg
)
{
    CNAS_HSM_GetHsmCtxAddr()->stSessionCtrlInfo.ucStartUatiReqAfterSectorIdChgFlg = ucStartUatiReqAfterSectorIdChgFlg;
}


VOS_UINT8  CNAS_HSM_GetStartUatiReqAfterSectorIdChgFlg(VOS_VOID)
{
    return CNAS_HSM_GetHsmCtxAddr()->stSessionCtrlInfo.ucStartUatiReqAfterSectorIdChgFlg;
}


VOS_VOID  CNAS_HSM_InitWaitUatiAssignTimerLenInfo(VOS_VOID)
{
    CNAS_HSM_WAIT_UATI_ASSIGN_TIMER_LEN_INFO_STRU          *pstWaitUaitAssignTimerLen;

    pstWaitUaitAssignTimerLen = CNAS_HSM_GetWaitUatiAssignTimerLenInfoAddr();

    pstWaitUaitAssignTimerLen->ucWaitUatiAssignTimerLenInAmpSetup = 5;
    pstWaitUaitAssignTimerLen->ucWaitUatiAssignTimerLenInAmpOpen  = 120;
}


CNAS_HSM_WAIT_UATI_ASSIGN_TIMER_LEN_INFO_STRU*  CNAS_HSM_GetWaitUatiAssignTimerLenInfoAddr(VOS_VOID)
{
    return &(CNAS_HSM_GetHsmCtxAddr()->stSessionCtrlInfo.stWaitUatiAssignTimerLenInfo);
}


CNAS_HSM_HRPD_CAS_STATUS_ENUM_UINT16 CNAS_HSM_GetHrpdConvertedCasStatus(VOS_VOID)
{
    return CNAS_HSM_GetHsmCtxAddr()->stHrpdConnCtrlInfo.enHrpdConvertedCasStatus;
}


VOS_VOID CNAS_HSM_SaveHrpdConvertedCasStatus(
    CNAS_HSM_HRPD_CAS_STATUS_ENUM_UINT16                    enHrpdConvertedCasStatus
)
{
    CNAS_HSM_GetHsmCtxAddr()->stHrpdConnCtrlInfo.enHrpdConvertedCasStatus = enHrpdConvertedCasStatus;
    return;
}


CAS_CNAS_HRPD_CAS_STATUS_ENUM_UINT16 CNAS_HSM_GetHrpdOriginalCasStatus(VOS_VOID)
{
    return CNAS_HSM_GetHsmCtxAddr()->stHrpdConnCtrlInfo.enHrpdOriginalCasStatus;
}


VOS_VOID CNAS_HSM_SaveHrpdOriginalCasStatus(
    CAS_CNAS_HRPD_CAS_STATUS_ENUM_UINT16                    enHrpdOriginalCasStatus
)
{
    CNAS_HSM_GetHsmCtxAddr()->stHrpdConnCtrlInfo.enHrpdOriginalCasStatus = enHrpdOriginalCasStatus;
    return;
}



CNAS_HSM_HRPD_CONN_STATUS_ENUM_UINT8 CNAS_HSM_GetConnStatus(VOS_VOID)
{
    return CNAS_HSM_GetHsmCtxAddr()->stHrpdConnCtrlInfo.enConnStatus;
}


VOS_VOID CNAS_HSM_SetConnStatus(
    CNAS_HSM_HRPD_CONN_STATUS_ENUM_UINT8                    enConnStatus
)
{
    CNAS_HSM_GetHsmCtxAddr()->stHrpdConnCtrlInfo.enConnStatus = enConnStatus;
    return;
}


VOS_VOID CNAS_HSM_SetSessionNegOngoingFlag(
    VOS_UINT8                           ucIsSessionNegOngoing
)
{
    CNAS_HSM_GetHsmCtxAddr()->stSessionCtrlInfo.ucIsSessionNegOngoing = ucIsSessionNegOngoing;
}


VOS_UINT8 CNAS_HSM_GetSessionNegOngoingFlag(VOS_VOID)
{
    return CNAS_HSM_GetHsmCtxAddr()->stSessionCtrlInfo.ucIsSessionNegOngoing;
}


VOS_VOID CNAS_HSM_SetScpActiveFlag(
    VOS_UINT8                           ucIsScpActive
)
{
    CNAS_HSM_GetHsmCtxAddr()->stSessionCtrlInfo.ucIsScpActive = ucIsScpActive;
}


VOS_UINT8 CNAS_HSM_GetScpActiveFlag(VOS_VOID)
{
    return CNAS_HSM_GetHsmCtxAddr()->stSessionCtrlInfo.ucIsScpActive;
}




CNAS_HSM_RCV_OHM_SCENE_ENUM_UINT8 CNAS_HSM_GetRcvOhmScene(VOS_VOID)
{
    return CNAS_HSM_GetHsmCtxAddr()->stSessionCtrlInfo.enRcvOhmScene;
}


VOS_VOID CNAS_HSM_SetRcvOhmScene(
    CNAS_HSM_RCV_OHM_SCENE_ENUM_UINT8   enRcvOhmScene
)
{
    CNAS_HSM_GetHsmCtxAddr()->stSessionCtrlInfo.enRcvOhmScene= enRcvOhmScene;
}



VOS_UINT8 CNAS_HSM_GetHsmCallId(VOS_VOID)
{
    return CNAS_HSM_GetHrpdConnCtrlInfoAddr()->ucHsmCallId;
}


VOS_VOID CNAS_HSM_SaveHsmCallId(
    VOS_UINT8                           ucHsmCallId
)
{
    (CNAS_HSM_GetHrpdConnCtrlInfoAddr()->ucHsmCallId) = ucHsmCallId;
}


VOS_UINT8 CNAS_HSM_GetRegLteSuccFlag(VOS_VOID)
{
    return CNAS_HSM_GetHsmCtxAddr()->stMultiModeCtrlInfo.ucLteRegSuccFlg;
}


VOS_VOID CNAS_HSM_SetRegLteSuccFlag(
    VOS_UINT8                           ucRegLteSuccFlg
)
{
    CNAS_HSM_GetHsmCtxAddr()->stMultiModeCtrlInfo.ucLteRegSuccFlg = ucRegLteSuccFlg;
}



CNAS_HSM_SESSION_ACTIVE_CTRL_CTX_STRU* CNAS_HSM_GetSessionActiveCtrlCtx(VOS_VOID)
{
    return &(CNAS_HSM_GetSessionCtrlInfoAddr()->stSessionActiveCtrlCtx);
}


VOS_UINT8 CNAS_HSM_GetSessionActTriedCntConnFail(VOS_VOID)
{
    return (CNAS_HSM_GetSessionActiveCtrlCtx()->ucSessionActTriedCntConnFail);
}


VOS_UINT8 CNAS_HSM_GetSessionActTriedCntOtherFail(VOS_VOID)
{
    return (CNAS_HSM_GetSessionActiveCtrlCtx()->ucSessionActTriedCntOtherFail);
}


VOS_VOID CNAS_HSM_IncreaseSessionActTriedCntConnFail(VOS_VOID)
{
    (CNAS_HSM_GetSessionActiveCtrlCtx()->ucSessionActTriedCntConnFail)++;
}


VOS_VOID CNAS_HSM_IncreaseSessionActTriedCntOtherFail(VOS_VOID)
{
    (CNAS_HSM_GetSessionActiveCtrlCtx()->ucSessionActTriedCntOtherFail)++;
}


VOS_VOID CNAS_HSM_ResetSessionActTriedCntConnFail(VOS_VOID)
{
    (CNAS_HSM_GetSessionActiveCtrlCtx()->ucSessionActTriedCntConnFail) = 0;;
}


VOS_VOID CNAS_HSM_ResetSessionActTriedCntOtherFail(VOS_VOID)
{
    (CNAS_HSM_GetSessionActiveCtrlCtx()->ucSessionActTriedCntOtherFail) = 0;
}


VOS_UINT8 CNAS_HSM_GetSessionActMaxCntConnFail(VOS_VOID)
{
    return (CNAS_HSM_GetSessionActiveCtrlCtx()->ucSessionActMaxCntConnFail);
}


VOS_VOID CNAS_HSM_SetSessionActMaxCntConnFail(VOS_UINT8 ucMaxCnt)
{
    (CNAS_HSM_GetSessionActiveCtrlCtx()->ucSessionActMaxCntConnFail) = ucMaxCnt;
}


VOS_UINT8 CNAS_HSM_GetSessionActMaxCntOtherFail(VOS_VOID)
{
    return (CNAS_HSM_GetSessionActiveCtrlCtx()->ucSessionActMaxCntOtherFail);
}


VOS_VOID CNAS_HSM_SetSessionActMaxCntOtherFail(VOS_UINT8 ucMaxCnt)
{
    (CNAS_HSM_GetSessionActiveCtrlCtx()->ucSessionActMaxCntOtherFail) = ucMaxCnt;
}


VOS_UINT32 CNAS_HSM_GetSessionActTimerLen(VOS_VOID)
{
    return (CNAS_HSM_GetSessionActiveCtrlCtx()->ulSessionActTimerLen);
}


VOS_VOID CNAS_HSM_SetSessionActTimerLen(VOS_UINT32 ulTimerLen)
{
    (CNAS_HSM_GetSessionActiveCtrlCtx()->ulSessionActTimerLen) = ulTimerLen;
}


VOS_UINT8 CNAS_HSM_GetExplicitlyConnDenyFlg(VOS_VOID)
{
    return (CNAS_HSM_GetSessionActiveCtrlCtx()->ucIsExplicitlyConnDenyFlg);
}


VOS_VOID CNAS_HSM_SetExplicitlyConnDenyFlg(VOS_UINT8 ucIsExplicitlyConnDenyFlg)
{
    (CNAS_HSM_GetSessionActiveCtrlCtx()->ucIsExplicitlyConnDenyFlg) = ucIsExplicitlyConnDenyFlg;
}


CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8
CNAS_HSM_GetSessionDeactReason_SessionDeact(VOS_VOID)
{
    return (CNAS_HSM_GetSessionDeactiveFsmCtxAddr()->enSessionDeactReason);
}


VOS_VOID CNAS_HSM_SetSessionDeactReason_SessionDeact(
    CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8                enDeactReason
)
{
    (CNAS_HSM_GetSessionDeactiveFsmCtxAddr()->enSessionDeactReason) = enDeactReason;
}



CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8 CNAS_HSM_GetLatestSessionDeactReason(VOS_VOID)
{
    return (CNAS_HSM_GetSessionCtrlInfoAddr()->enLatestSessionDeactReason);
}


VOS_VOID CNAS_HSM_SetLatestSessionDeactReason(
    CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8                enDeactReason
)
{
    (CNAS_HSM_GetSessionCtrlInfoAddr()->enLatestSessionDeactReason) = enDeactReason;
}


VOS_UINT8 CNAS_HSM_GetUatiReqRetryTimesWhenUatiAssignTimerExpireInAmpOpen(VOS_VOID)
{
    return (CNAS_HSM_GetSessionCtrlInfoAddr()->ucUatiReqRetryTimesWhenUatiAssignTimerExpireInAmpOpen);
}


VOS_VOID CNAS_HSM_SetUatiReqRetryTimesWhenUatiAssignTimerExpireInAmpOpen(
    VOS_UINT8                                               ucUatiReqRetryTimesWhenUatiAssignTimerExpireInAmpOpen
)
{
    (CNAS_HSM_GetSessionCtrlInfoAddr()->ucUatiReqRetryTimesWhenUatiAssignTimerExpireInAmpOpen) = ucUatiReqRetryTimesWhenUatiAssignTimerExpireInAmpOpen;
}


VOS_UINT8 CNAS_HSM_GetUatiCompleteRetryTimes(VOS_VOID)
{
    return (CNAS_HSM_GetSessionCtrlInfoAddr()->ucUatiCompleteRetryTimes);
}


VOS_VOID CNAS_HSM_IncreaseUatiCompleteRetryTimes(VOS_VOID)
{
    (CNAS_HSM_GetSessionCtrlInfoAddr()->ucUatiCompleteRetryTimes)++;

    CNAS_WARNING_LOG1(UEPS_PID_HSM, "CNAS_HSM_IncreaseUatiCompleteRetryTimes:", (VOS_INT32)(CNAS_HSM_GetSessionCtrlInfoAddr()->ucUatiCompleteRetryTimes));
}


VOS_VOID CNAS_HSM_ResetUatiCompleteRetryTimes(VOS_VOID)
{
    (CNAS_HSM_GetSessionCtrlInfoAddr()->ucUatiCompleteRetryTimes) = 0;

    CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_ResetUatiCompleteRetryTimes");
}


VOS_UINT16 CNAS_HSM_GetScpActFailProcType(VOS_VOID)
{
    return (CNAS_HSM_GetSessionActiveCtrlCtx()->usScpActFailProtType);
}


VOS_VOID CNAS_HSM_SetScpActFailProcType(VOS_UINT16 usProcType)
{
    (CNAS_HSM_GetSessionActiveCtrlCtx()->usScpActFailProtType) = usProcType;
}


VOS_UINT16 CNAS_HSM_GetScpActFailProcSubtype(VOS_VOID)
{
    return (CNAS_HSM_GetSessionActiveCtrlCtx()->usScpActFailProtSubtype);
}


VOS_VOID CNAS_HSM_SetScpActFailProcSubtype(VOS_UINT16 usProcSubtype)
{
    (CNAS_HSM_GetSessionActiveCtrlCtx()->usScpActFailProtSubtype) = usProcSubtype;
}


CNAS_HSM_FSM_SESSION_DEACTIVE_CTX_STRU* CNAS_HSM_GetSessionDeactiveFsmCtxAddr(VOS_VOID)
{
    return &(CNAS_HSM_GetCurFsmCtxAddr()->stSessionDeactiveFsmCtx);
}


CNAS_HSM_SESSION_TYPE_ENUM_UINT8 CNAS_HSM_GetReqSessionTypeForRetry(VOS_VOID)
{
    return (CNAS_HSM_GetSessionActiveCtrlCtx()->enReqSessionTypeForRetry);
}


VOS_VOID CNAS_HSM_SetReqSessionTypeForRetry(
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8    enReqSessionType
)
{
    (CNAS_HSM_GetSessionActiveCtrlCtx()->enReqSessionTypeForRetry) = enReqSessionType;
}


CNAS_HSM_HRPD_SYS_INFO_STRU* CNAS_HSM_GetHrpdSysInfoAddr(VOS_VOID)
{
    return &(CNAS_HSM_GetSessionCtrlInfoAddr()->stHrpdSysInfo);
}



CNAS_HSM_SESSION_KEEP_ALIVE_INFO_STRU* CNAS_HSM_GetSessionKeepAliveInfoAddr(VOS_VOID)
{
    return &(CNAS_HSM_GetHsmCtxAddr()->stKeepAliveCtrlCtx.stSessionKeepAliveInfo);
}




CNAS_HSM_LAST_HRPD_SESSION_INFO_STRU* CNAS_HSM_GetLastHrpdSessionInfoCtxAddr(VOS_VOID)
{
    return &(CNAS_HSM_GetHsmCtxAddr()->stMsCfgInfo.stCustomCfgInfo.stHrpdNvimSessInfo);
}



CNAS_CCB_HRPD_ACCESS_AUTH_INFO_STRU* CNAS_HSM_GetLastHrpdAccessAuthInfoCtxAddr(VOS_VOID)
{
    return &(CNAS_HSM_GetHsmCtxAddr()->stMsCfgInfo.stCustomCfgInfo.stHrpdNvimAccessAuthInfo);
}



CNAS_NVIM_HRPD_UE_REV_INFO_STRU* CNAS_HSM_GetHrpdUERevInfoCtxAddr(VOS_VOID)
{
    return &(CNAS_HSM_GetHsmCtxAddr()->stMsCfgInfo.stCustomCfgInfo.stHrpdUERevInfo);
}



CNAS_NVIM_HRPD_UE_REV_INFO_STRU* CNAS_HSM_GetLastHrpdUERevInfoCtxAddr(VOS_VOID)
{
      return &(CNAS_HSM_GetHsmCtxAddr()->stSessionCtrlInfo.stLastHrpdUERevInfo);
}




CNAS_HSM_SESSION_CLOSE_INFO_STRU* CNAS_HSM_GetSessionCloseInfoCtxAddr(VOS_VOID)
{
      return &(CNAS_HSM_GetHsmCtxAddr()->stSessionCtrlInfo.stSessionCloseInfo);
}



CNAS_HSM_HARDWARE_ID_INFO_STRU* CNAS_HSM_GetLastSessionHwidCtxAddr(VOS_VOID)
{
    return &(CNAS_HSM_GetLastHrpdSessionInfoCtxAddr()->stHwid);
}


CNAS_HSM_SESSION_STATUS_ENUM_UINT8 CNAS_HSM_GetLastHrpdSessionStatus()
{
    return CNAS_HSM_GetLastHrpdSessionInfoCtxAddr()->enSessionStatus;
}


VOS_VOID CNAS_HSM_SetLastHrpdSessionStatus(
    CNAS_HSM_SESSION_STATUS_ENUM_UINT8  enSessionStatus
)
{
    CNAS_HSM_GetLastHrpdSessionInfoCtxAddr()->enSessionStatus = enSessionStatus;
}




VOS_VOID CNAS_HSM_SetFirstSysAcqFlag(
    VOS_UINT8                           ucFirstSysAcqFlg
)
{
    CNAS_HSM_GetSessionCtrlInfoAddr()->ucIsFirstSysAcq = ucFirstSysAcqFlg;
}



VOS_UINT8 CNAS_HSM_GetFirstSysAcqFlag(VOS_VOID)
{
    return (CNAS_HSM_GetSessionCtrlInfoAddr()->ucIsFirstSysAcq);
}

/*****************************************************************************
 函 数 名  : CNAS_HSM_SetActivatedSessionType
 功能描述  : set current session type
 输入参数  : enSessionType EHSM_HSM_SESSION_TYPE_ENUM_UINT32
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月30日
    作    者   : x00314862
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSM_SetReqSessionType(CNAS_HSM_SESSION_TYPE_ENUM_UINT8 enSessionType)
{
    CNAS_HSM_GetSessionCtrlInfoAddr()->enReqSessionType = enSessionType;
}

/*****************************************************************************
 函 数 名  : CNAS_HSM_GetReqSessionType
 功能描述  : get req session type
 输入参数  : 无
 输出参数  : enSessionType EHSM_HSM_SESSION_TYPE_ENUM_UINT32
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月30日
    作    者   : x00314862
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_HSM_SESSION_TYPE_ENUM_UINT8 CNAS_HSM_GetReqSessionType(VOS_VOID)
{
    return CNAS_HSM_GetSessionCtrlInfoAddr()->enReqSessionType;
}

/*****************************************************************************
 函 数 名  : CNAS_HSM_SetNegoSessionType
 功能描述  : set nego session type
 输入参数  : enSessionType EHSM_HSM_SESSION_TYPE_ENUM_UINT32
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月30日
    作    者   : x00314862
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSM_SetNegoSessionType(
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8 enNegoSessionType
)
{
    CNAS_HSM_GetSessionCtrlInfoAddr()->enNegoSessionType = enNegoSessionType;
}

/*****************************************************************************
 函 数 名  : CNAS_HSM_GetNegoSessionType
 功能描述  : get cur session type
 输入参数  : 无
 输出参数  : enSessionType EHSM_HSM_SESSION_TYPE_ENUM_UINT32
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月30日
    作    者   : x00314862
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_HSM_SESSION_TYPE_ENUM_UINT8 CNAS_HSM_GetNegoSessionType(VOS_VOID)
{
    return CNAS_HSM_GetSessionCtrlInfoAddr()->enNegoSessionType;
}

/*****************************************************************************
 函 数 名  : CNAS_HSM_ClearNegoSessionType
 功能描述  : clear current session type
 输入参数  : 无
 输出参数  :
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月03日
    作    者   : x00314862
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSM_ClearNegoSessionType(VOS_VOID)
{
    CNAS_HSM_GetSessionCtrlInfoAddr()->enNegoSessionType = CNAS_HSM_SESSION_TYPE_BUTT;
}

/*****************************************************************************
 函 数 名  : CNAS_HSM_SetLastSessionType
 功能描述  : set current session type
 输入参数  : enSessionType EHSM_HSM_SESSION_TYPE_ENUM_UINT32
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月30日
    作    者   : x00314862
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSM_SetLastSessionType(CNAS_HSM_SESSION_TYPE_ENUM_UINT8 enSessionType)
{
    CNAS_HSM_GetLastHrpdSessionInfoCtxAddr()->enSessionType = enSessionType;
}

/*****************************************************************************
 函 数 名  : CNAS_HSM_GetLastSessionType
 功能描述  : get current session type
 输入参数  : 无
 输出参数  : enSessionType EHSM_HSM_SESSION_TYPE_ENUM_UINT32
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月30日
    作    者   : x00314862
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_HSM_SESSION_TYPE_ENUM_UINT8 CNAS_HSM_GetLastSessionType(VOS_VOID)
{
    return CNAS_HSM_GetLastHrpdSessionInfoCtxAddr()->enSessionType;
}

/*****************************************************************************
 函 数 名  : CNAS_HSM_IsCurrentCapSupportEhrpd
 功能描述  : Judge if eHrpd is supported in current scenrio
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_BOOL VOS_TRUE represent support eHRPD,else not suport
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月30日
    作    者   : x00314862
    修改内容   : 新生成函数

  2.日    期   : 2015年12月21日
    作    者   : m00312079
    修改内容   : DTS2015120208895,使用NV3600来判断UE是否支持EHRPD

*****************************************************************************/
VOS_UINT32 CNAS_HSM_IsCurrentCapSupportEhrpd(VOS_VOID)
{
    VOS_UINT8                                               ucIsEhrpdSupportFlag;
    CNAS_CCB_CARD_STATUS_ENUM_UINT8                         enUsimCardStatus;
    CNAS_NVIM_HRPD_UE_REV_INFO_STRU                        *pstHrpdUERevInfo;

    pstHrpdUERevInfo     = CNAS_HSM_GetHrpdUERevInfoCtxAddr();
    enUsimCardStatus     = CNAS_CCB_GetUsimCardStatus();

    ucIsEhrpdSupportFlag = VOS_FALSE;

    if (PS_FALSE == pstHrpdUERevInfo->enSuppOnlyDo0)
    {
        if ((PS_TRUE == pstHrpdUERevInfo->enSuppDoaWithMfpa)
         || (PS_TRUE == pstHrpdUERevInfo->enSuppDoaWithEmfpa))
        {
            if (PS_TRUE == pstHrpdUERevInfo->enSuppDoaEhrpd)
            {
                ucIsEhrpdSupportFlag = VOS_TRUE;
            }
        }
    }

    /* config from NV support and USIM application is supported*/
    if ((VOS_TRUE == ucIsEhrpdSupportFlag)
     && (CNAS_CCB_CARD_STATUS_USIM_PRESENT == enUsimCardStatus))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}


VOS_UINT8 CNAS_HSM_GetOhmParameterUpToDate(VOS_VOID)
{
    return CNAS_HSM_GetHrpdSysInfoAddr()->ucOhmParameterUpToDate;
}


VOS_VOID CNAS_HSM_SetOhmParameterUpToDate(
    VOS_UINT8                           ucOhmParameterUpToDate
)
{
    (CNAS_HSM_GetHrpdSysInfoAddr()->ucOhmParameterUpToDate) = ucOhmParameterUpToDate;
}


CNAS_HSM_FSM_SWITCH_ON_CTX_STRU* CNAS_HSM_GetCardReadInfoAddr(VOS_VOID)
{
    return &(CNAS_HSM_GetHsmCtxAddr()->stCurFsmCtx.stCardReadInfo);
}


CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_ENUM_UINT32 CNAS_HSM_GetWaitCardReadCnfFlag(VOS_VOID)
{
    CNAS_HSM_FSM_SWITCH_ON_CTX_STRU    *pstCardReadInfo = VOS_NULL_PTR;

    pstCardReadInfo = CNAS_HSM_GetCardReadInfoAddr();

    return pstCardReadInfo->ulWaitCardReadFlag;
}



VOS_VOID CNAS_HSM_SetWaitCardReadCnfFlag(
    CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_ENUM_UINT32            enFlag
)
{
    CNAS_HSM_FSM_SWITCH_ON_CTX_STRU    *pstCardReadInfo = VOS_NULL_PTR;

    pstCardReadInfo = CNAS_HSM_GetCardReadInfoAddr();

    pstCardReadInfo->ulWaitCardReadFlag |= enFlag;
}



VOS_VOID CNAS_HSM_ClearWaitCardReadCnfFlag(
    CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_ENUM_UINT32            enFlag
)
{
    CNAS_HSM_FSM_SWITCH_ON_CTX_STRU    *pstCardReadInfo = VOS_NULL_PTR;

    pstCardReadInfo = CNAS_HSM_GetCardReadInfoAddr();

    pstCardReadInfo->ulWaitCardReadFlag &= ~enFlag;
}


VOS_VOID CNAS_HSM_ResetWaitCardReadCnfFlag(VOS_VOID)
{
    CNAS_HSM_FSM_SWITCH_ON_CTX_STRU    *pstCardReadInfo = VOS_NULL_PTR;

    pstCardReadInfo = CNAS_HSM_GetCardReadInfoAddr();

    pstCardReadInfo->ulWaitCardReadFlag = CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_NULL;
}

/*****************************************************************************
 函 数 名  : CNAS_HSM_GetHrpdAmpNegAttribAddr
 功能描述  : 获取HRPD SESSION中AMP协商参数首地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : HRPD SESSION中AMP协商参数首地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年05月30日
   作    者   : y00307564
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_HSM_HRPD_AMP_NEG_ATTRIB_STRU*  CNAS_HSM_GetHrpdAmpNegAttribAddr(VOS_VOID)
{
    return &(CNAS_HSM_GetHsmCtxAddr()->stHrpdAmpNegAttibInfo);
}





VOS_UINT8 CNAS_HSM_GetKeepAliveReqSndCount(VOS_VOID)
{
    return CNAS_HSM_GetKeepAliveCtrlCtxAddr()->stKeepAliveTimerInfo.ucKeepAliveReqSndCount;
}




VOS_VOID CNAS_HSM_SetKeepAliveReqSndCount(
    VOS_UINT8                           ucKeepAliveReqSndCount
)
{
    CNAS_HSM_GetKeepAliveCtrlCtxAddr()->stKeepAliveTimerInfo.ucKeepAliveReqSndCount= ucKeepAliveReqSndCount;
}



VOS_UINT8 CNAS_HSM_GetKeepAliveReqTransId(VOS_VOID)
{
    return CNAS_HSM_GetKeepAliveCtrlCtxAddr()->ucKeepAliveReqTransId;
}




VOS_VOID CNAS_HSM_SetKeepAliveReqTransId(
    VOS_UINT8                           ucKeepAliveReqTransId
)
{
    CNAS_HSM_GetKeepAliveCtrlCtxAddr()->ucKeepAliveReqTransId = ucKeepAliveReqTransId;
}




VOS_VOID CNAS_HSM_IncreaseKeepAliveReqTransId(VOS_VOID)
{
    VOS_UINT8                           ucTI;

    ucTI = (CNAS_HSM_GetKeepAliveCtrlCtxAddr()->ucKeepAliveReqTransId);

    ucTI++;
    ucTI = ucTI % 256;

    (CNAS_HSM_GetKeepAliveCtrlCtxAddr()->ucKeepAliveReqTransId) = ucTI;
}



VOS_UINT32 CNAS_HSM_GetSysTickFwdTrafficChan(VOS_VOID)
{
    return CNAS_HSM_GetKeepAliveCtrlCtxAddr()->stKeepAliveTimerInfo.ulSysTickFwdTrafChan;
}




VOS_VOID CNAS_HSM_SetSysTickFwdTrafficChan(
    VOS_UINT32                          ulSysTick
)
{
    CNAS_HSM_GetKeepAliveCtrlCtxAddr()->stKeepAliveTimerInfo.ulSysTickFwdTrafChan = ulSysTick;
}




VOS_UINT32 CNAS_HSM_GetOldSysTickFwdTrafChan(VOS_VOID)
{
    return CNAS_HSM_GetKeepAliveCtrlCtxAddr()->stKeepAliveTimerInfo.ulOldSysTickFwdTrafChan;

}




VOS_VOID CNAS_HSM_SetOldSysTickFwdTrafChan(
    VOS_UINT32                          ulOldSysTickFwdTrafChan
)
{
    CNAS_HSM_GetKeepAliveCtrlCtxAddr()->stKeepAliveTimerInfo.ulOldSysTickFwdTrafChan = ulOldSysTickFwdTrafChan;
}




VOS_UINT32 CNAS_HSM_GetKeepAliveTimerLen(VOS_VOID)
{
    return CNAS_HSM_GetKeepAliveCtrlCtxAddr()->stKeepAliveTimerInfo.ulKeepAliveTimerLen;
}




VOS_VOID CNAS_HSM_SetKeepAliveTimerLen(
    VOS_UINT32                          ulKeepAliveTimerLen
)
{
    CNAS_HSM_GetKeepAliveCtrlCtxAddr()->stKeepAliveTimerInfo.ulKeepAliveTimerLen = ulKeepAliveTimerLen;
}




VOS_UINT32 CNAS_HSM_GetKeepAliveTimerTotalRunCount(VOS_VOID)
{
    return CNAS_HSM_GetKeepAliveCtrlCtxAddr()->stKeepAliveTimerInfo.ulTotalTimerRunCount;
}




VOS_VOID CNAS_HSM_SetKeepAliveTimerTotalRunCount(
    VOS_UINT32                          ulTotalTimerRunCount
)
{
    CNAS_HSM_GetKeepAliveCtrlCtxAddr()->stKeepAliveTimerInfo.ulTotalTimerRunCount= ulTotalTimerRunCount;
}




VOS_UINT32 CNAS_HSM_GetKeepAliveTimerExpiredCount(VOS_VOID)
{
    return CNAS_HSM_GetKeepAliveCtrlCtxAddr()->stKeepAliveTimerInfo.ulTimerExpiredCount;
}




VOS_VOID CNAS_HSM_SetKeepAliveTimerExpiredCount(
    VOS_UINT32                          ulTimerExpiredCount
)
{
    CNAS_HSM_GetKeepAliveCtrlCtxAddr()->stKeepAliveTimerInfo.ulTimerExpiredCount = ulTimerExpiredCount;
}




VOS_UINT16 CNAS_HSM_GetTsmpClose(VOS_VOID)
{
    return CNAS_HSM_GetKeepAliveCtrlCtxAddr()->stSessionKeepAliveInfo.usTsmpClose;
}




VOS_VOID CNAS_HSM_SetTsmpClose(
    VOS_UINT16                          usTsmpClose
)
{
    CNAS_HSM_GetKeepAliveCtrlCtxAddr()->stSessionKeepAliveInfo.usTsmpClose = usTsmpClose;
}




VOS_UINT32 CNAS_HSM_GetTsmpCloseRemainTime(VOS_VOID)
{
    return CNAS_HSM_GetKeepAliveCtrlCtxAddr()->stSessionKeepAliveInfo.ulTsmpCloseRemainTime;
}




VOS_VOID CNAS_HSM_SetTsmpCloseRemainTime(
    VOS_UINT32                          ulTsmpCloseRemainTime
)
{
    CNAS_HSM_GetKeepAliveCtrlCtxAddr()->stSessionKeepAliveInfo.ulTsmpCloseRemainTime = ulTsmpCloseRemainTime;
}




VOS_UINT32* CNAS_HSM_GetLastPowerOffSysTime(VOS_VOID)
{
    return CNAS_HSM_GetKeepAliveCtrlCtxAddr()->stSessionKeepAliveInfo.aulPowerOffSysTime;
}




VOS_VOID CNAS_HSM_SetLastPowerOffSysTime(
    VOS_UINT32                         *pulSysTime
)
{
    if (VOS_NULL_PTR == pulSysTime)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_SetSysTime: input pointer is NULL!");
        return;
    }

    NAS_MEM_CPY_S(CNAS_HSM_GetKeepAliveCtrlCtxAddr()->stSessionKeepAliveInfo.aulPowerOffSysTime,
                  CNAS_HSM_NUM_WORDS_IN_CDMA_SYS_TIME * sizeof(VOS_UINT32),
                  pulSysTime,
                  CNAS_HSM_NUM_WORDS_IN_CDMA_SYS_TIME * sizeof(VOS_UINT32));
}




VOS_UINT32* CNAS_HSM_GetLastReceivedSysTime(VOS_VOID)
{
    return CNAS_HSM_GetKeepAliveCtrlCtxAddr()->aulReceivedSysTime;
}




VOS_VOID CNAS_HSM_SetLastReceivedSysTime(
    VOS_UINT32                         *pulSysTime
)
{
    if (VOS_NULL_PTR == pulSysTime)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_SetSysTime: input pointer is NULL!");
        return;
    }

    NAS_MEM_CPY_S(CNAS_HSM_GetKeepAliveCtrlCtxAddr()->aulReceivedSysTime,
                  CNAS_HSM_NUM_WORDS_IN_CDMA_SYS_TIME * sizeof(VOS_UINT32),
                  pulSysTime,
                  CNAS_HSM_NUM_WORDS_IN_CDMA_SYS_TIME * sizeof(VOS_UINT32));
}




VOS_UINT32 CNAS_HSM_GetReferenceSysTick(VOS_VOID)
{
    return CNAS_HSM_GetKeepAliveCtrlCtxAddr()->ulReferenceSysTick;
}




VOS_VOID CNAS_HSM_SetReferenceSysTick(
    VOS_UINT32                          ulSysTick
)
{
    CNAS_HSM_GetKeepAliveCtrlCtxAddr()->ulReferenceSysTick = ulSysTick;
}




VOS_UINT8 CNAS_HSM_GetKeepAliveInfoValidFlag(VOS_VOID)
{
    return CNAS_HSM_GetKeepAliveCtrlCtxAddr()->stSessionKeepAliveInfo.ucIsKeepAliveInfoValid;
}




VOS_VOID CNAS_HSM_SetKeepAliveInfoValidFlag(
    VOS_UINT8                           ucIsKeepAliveInfoValid
)
{
    CNAS_HSM_GetKeepAliveCtrlCtxAddr()->stSessionKeepAliveInfo.ucIsKeepAliveInfoValid = ucIsKeepAliveInfoValid;
}



VOS_VOID CNAS_HSM_SetCurrSessionRelType(
     CNAS_HSM_SESSION_RELEASE_TYPE_ENUM_UINT8                enCurrSessionRelType
)
{
    CNAS_HSM_GetHsmCtxAddr()->stSessionCtrlInfo.enCurrSessionRelType = enCurrSessionRelType;
}



CNAS_HSM_SESSION_RELEASE_TYPE_ENUM_UINT8 CNAS_HSM_GetCurrSessionRelType(VOS_VOID)
{
    return CNAS_HSM_GetHsmCtxAddr()->stSessionCtrlInfo.enCurrSessionRelType;
}



VOS_VOID CNAS_HSM_SetSessionStatus(
     CNAS_HSM_SESSION_STATUS_ENUM_UINT8                enSessionStatus
)
{
    CNAS_HSM_GetHsmCtxAddr()->stSessionCtrlInfo.enSessionStatus = enSessionStatus;
}



CNAS_HSM_SESSION_STATUS_ENUM_UINT8 CNAS_HSM_GetSessionStatus(VOS_VOID)
{
    return CNAS_HSM_GetHsmCtxAddr()->stSessionCtrlInfo.enSessionStatus;
}





CNAS_HSM_FSM_SESSION_ACTIVE_CTX_STRU* CNAS_HSM_GetSessionActiveFsmCtxAddr(VOS_VOID)
{
    return &(CNAS_HSM_GetCurFsmCtxAddr()->stSessionActiceFsmCtx);
}


CNAS_HSM_FSM_CONN_MNMT_CTX_STRU* CNAS_HSM_GetConnMnmtFsmCtxAddr(VOS_VOID)
{
    return &(CNAS_HSM_GetCurFsmCtxAddr()->stConnMnmtFsmCtx);
}


VOS_VOID CNAS_HSM_SetAbortFlag_UatiReq(
    VOS_UINT8                           ucAbortFlg
)
{
    CNAS_HSM_GetCurFsmCtxAddr()->stUatiReqFsmCtx.ucAbortFlg = ucAbortFlg;
}


VOS_UINT8 CNAS_HSM_GetAbortFlag_UatiReq(VOS_VOID)
{
    return CNAS_HSM_GetCurFsmCtxAddr()->stUatiReqFsmCtx.ucAbortFlg;
}


VOS_VOID CNAS_HSM_SetAbortFlag_SessionDeact(
    VOS_UINT8                           ucAbortFlg
)
{
    CNAS_HSM_GetCurFsmCtxAddr()->stSessionDeactiveFsmCtx.ucAbortFlg = ucAbortFlg;
}


VOS_UINT8 CNAS_HSM_GetAbortFlag_SessionDeact(VOS_VOID)
{
    return CNAS_HSM_GetCurFsmCtxAddr()->stSessionDeactiveFsmCtx.ucAbortFlg;
}


VOS_VOID CNAS_HSM_SetReviseTimerScene_SessionDeact(
    CNAS_HSM_SESSION_DEACT_REVISE_TIMER_SCENE_ENUM_UINT8                  enCurReviseTimerScene
)
{
    CNAS_HSM_SESSION_DEACT_REVISE_TIMER_SCENE_ENUM_UINT8                  enPreReviseTimerScene;

    enPreReviseTimerScene = CNAS_HSM_GetReviseTimerScene_SessionDeact();

    /* 目前只有power save 和 power off需要设置启动修正定时器的场景，且power off目前的优先级高于power save，
       可以根据该场景枚举大小(越小优先级越高)，来判断是否需要修改启动修正定时器的场景。后续若有新的场景，
       该判断不能满足时，可以加优先级变量或者根据场景类型增加逻辑判断，来辅助完成设置当前的启动修正定时器场景 */

    if (enPreReviseTimerScene > enCurReviseTimerScene)
    {
        CNAS_HSM_GetCurFsmCtxAddr()->stSessionDeactiveFsmCtx.enReviseTimerScene = enCurReviseTimerScene;
    }
}


VOS_VOID CNAS_HSM_CleanReviseTimerScene_SessionDeact(VOS_VOID)
{
    CNAS_HSM_GetCurFsmCtxAddr()->stSessionDeactiveFsmCtx.enReviseTimerScene = CNAS_HSM_SESSION_DEACT_REVISE_TIMER_SCENE_BUTT;
}


CNAS_HSM_SESSION_DEACT_REVISE_TIMER_SCENE_ENUM_UINT8 CNAS_HSM_GetReviseTimerScene_SessionDeact(VOS_VOID)
{
    return CNAS_HSM_GetCurFsmCtxAddr()->stSessionDeactiveFsmCtx.enReviseTimerScene;
}


VOS_VOID CNAS_HSM_SetAbortFlag_SessionActive(
    VOS_UINT8                           ucAbortFlg
)
{
    CNAS_HSM_GetCurFsmCtxAddr()->stSessionActiceFsmCtx.ucAbortFlg = ucAbortFlg;
}


VOS_UINT8 CNAS_HSM_GetAbortFlag_SessionActive(VOS_VOID)
{
    return CNAS_HSM_GetCurFsmCtxAddr()->stSessionActiceFsmCtx.ucAbortFlg;
}

VOS_VOID CNAS_HSM_SetSessionActiveReason_SessionActive(
    CNAS_HSM_SESSION_ACTIVE_REASON_ENUM_UINT8               enSessionActiveReason
)
{
    CNAS_HSM_GetCurFsmCtxAddr()->stSessionActiceFsmCtx.enSessionActiveReason = enSessionActiveReason;
}


VOS_UINT8 CNAS_HSM_GetSessionActiveReason_SessionActive(VOS_VOID)
{
    return CNAS_HSM_GetCurFsmCtxAddr()->stSessionActiceFsmCtx.enSessionActiveReason;
}


VOS_UINT8 CNAS_HSM_GetPaNtfFlag_SessionActive(VOS_VOID)
{
    return CNAS_HSM_GetCurFsmCtxAddr()->stSessionActiceFsmCtx.ucIsGetPaNtf;
}


VOS_VOID CNAS_HSM_SetPaNtfFlag_SessionActive(
    VOS_UINT8                           ucIsGetPaNtf
)
{
    CNAS_HSM_GetCurFsmCtxAddr()->stSessionActiceFsmCtx.ucIsGetPaNtf = ucIsGetPaNtf;
}



VOS_VOID CNAS_HSM_SetAbortFlag_ConnMnmt(
    VOS_UINT8                           ucAbortFlg
)
{
    CNAS_HSM_GetCurFsmCtxAddr()->stConnMnmtFsmCtx.ucAbortFlg = ucAbortFlg;
}


VOS_UINT8 CNAS_HSM_GetAbortFlag_ConnMnmt(VOS_VOID)
{
    return CNAS_HSM_GetCurFsmCtxAddr()->stConnMnmtFsmCtx.ucAbortFlg;
}




VOS_VOID CNAS_HSM_SetConnMnmtTriggerScene_ConnMnmt(
    CNAS_HSM_CONN_MNMT_TRIGGER_ENUM_UINT8                   enTriggerScene
)
{
    CNAS_HSM_GetCurFsmCtxAddr()->stConnMnmtFsmCtx.enTriggerScene = enTriggerScene;
}


CNAS_HSM_CONN_MNMT_TRIGGER_ENUM_UINT8 CNAS_HSM_GetConnMnmtTriggerScene_ConnMnmt(VOS_VOID)
{
    return CNAS_HSM_GetCurFsmCtxAddr()->stConnMnmtFsmCtx.enTriggerScene;
}



VOS_UINT16 CNAS_HSM_GetSnpDataReqOpId(VOS_VOID)
{
    return (CNAS_HSM_GetHsmCtxAddr()->stSnpDataReqCtrlInfo.usHsmSnpDataReqOpId);
}


VOS_VOID CNAS_HSM_IncreaseSnpDataReqOpId(VOS_VOID)
{
    VOS_UINT16                          usOpId;

    usOpId = (CNAS_HSM_GetHsmCtxAddr()->stSnpDataReqCtrlInfo.usHsmSnpDataReqOpId);

    usOpId++;

    usOpId = usOpId % 65536;

    (CNAS_HSM_GetHsmCtxAddr()->stSnpDataReqCtrlInfo.usHsmSnpDataReqOpId) = usOpId;
}


VOS_VOID CNAS_HSM_SaveHardWareIdRspSnpDataReqOpId(VOS_UINT16 usOpId)
{
    (CNAS_HSM_GetHsmCtxAddr()->stSnpDataReqCtrlInfo.stSaveSnpDataReqOpId.usHardWareIdRspOpId) = usOpId;
}


VOS_UINT16 CNAS_HSM_GetHardWareIdRspSnpDataReqOpId(VOS_VOID)
{
    return (CNAS_HSM_GetHsmCtxAddr()->stSnpDataReqCtrlInfo.stSaveSnpDataReqOpId.usHardWareIdRspOpId);
}



VOS_VOID CNAS_HSM_SaveUatiReqSnpDataReqOpId(VOS_UINT16 usOpId)
{
    (CNAS_HSM_GetHsmCtxAddr()->stSnpDataReqCtrlInfo.stSaveSnpDataReqOpId.usUatiReqOpId) = usOpId;
}



VOS_UINT16 CNAS_HSM_GetUatiReqSnpDataReqOpId(VOS_VOID)
{
    return (CNAS_HSM_GetHsmCtxAddr()->stSnpDataReqCtrlInfo.stSaveSnpDataReqOpId.usUatiReqOpId);
}



VOS_VOID CNAS_HSM_SaveUatiCmplSnpDataReqOpId(VOS_UINT16 usOpId)
{
    (CNAS_HSM_GetHsmCtxAddr()->stSnpDataReqCtrlInfo.stSaveSnpDataReqOpId.usUatiCmplOpId) = usOpId;
}



VOS_UINT16 CNAS_HSM_GetUatiCmplSnpDataReqOpId(VOS_VOID)
{
    return (CNAS_HSM_GetHsmCtxAddr()->stSnpDataReqCtrlInfo.stSaveSnpDataReqOpId.usUatiCmplOpId);
}



VOS_VOID CNAS_HSM_SaveSessionCloseSnpDataReqOpId(VOS_UINT16 usOpId)
{
    (CNAS_HSM_GetHsmCtxAddr()->stSnpDataReqCtrlInfo.stSaveSnpDataReqOpId.usSessionCloseOpId) = usOpId;
}



VOS_UINT16 CNAS_HSM_GetSessionCloseSnpDataReqOpId(VOS_VOID)
{
    return (CNAS_HSM_GetHsmCtxAddr()->stSnpDataReqCtrlInfo.stSaveSnpDataReqOpId.usSessionCloseOpId);
}



VOS_VOID CNAS_HSM_SaveKeepAliveReqSnpDataReqOpId(VOS_UINT16 usOpId)
{
    (CNAS_HSM_GetHsmCtxAddr()->stSnpDataReqCtrlInfo.stSaveSnpDataReqOpId.usKeepAliveReqOpId) = usOpId;
}



VOS_UINT16 CNAS_HSM_GetKeepAliveReqSnpDataReqOpId(VOS_VOID)
{
    return (CNAS_HSM_GetHsmCtxAddr()->stSnpDataReqCtrlInfo.stSaveSnpDataReqOpId.usKeepAliveReqOpId);
}



VOS_VOID CNAS_HSM_SaveKeepAliveRspSnpDataReqOpId(VOS_UINT16 usOpId)
{
    (CNAS_HSM_GetHsmCtxAddr()->stSnpDataReqCtrlInfo.stSaveSnpDataReqOpId.usKeepALiveRspOpId) = usOpId;
}



VOS_UINT16 CNAS_HSM_GetKeepAliveRspSnpDataReqOpId(VOS_VOID)
{
    return (CNAS_HSM_GetHsmCtxAddr()->stSnpDataReqCtrlInfo.stSaveSnpDataReqOpId.usKeepALiveRspOpId);
}



CNAS_HSM_STORE_ESN_MEID_RSLT_STRU* CNAS_HSM_GetStoreEsnMeidRsltAddr(VOS_VOID)
{
    return &(CNAS_HSM_GetHsmCtxAddr()->stSessionCtrlInfo.stStoreEsnMeidRslt);
}



CNAS_HSM_CARD_STATUS_CHANGE_INFO_STRU* CNAS_HSM_GetCardStatusChangeInfoAddr(VOS_VOID)
{
    return &(CNAS_HSM_GetHsmCtxAddr()->stSessionCtrlInfo.stCardStatusChgInfo);
}


VOS_UINT8* CNAS_HSM_GetLastIccIdAddr(VOS_VOID)
{
    return CNAS_HSM_GetHsmCtxAddr()->stMsCfgInfo.stCustomCfgInfo.aucHrpdNvimIccId;
}


VOS_VOID CNAS_CCB_SetLastIccId(
    VOS_UINT8                          *pucIccId
)
{
    VOS_UINT8                          *pucLastIccId = VOS_NULL_PTR;

    pucLastIccId = CNAS_HSM_GetLastIccIdAddr();

    NAS_MEM_CPY_S(pucLastIccId, sizeof(VOS_UINT8) * CNAS_CCB_ICCID_OCTET_LEN, pucIccId, sizeof(VOS_UINT8) * CNAS_CCB_ICCID_OCTET_LEN);
}


VOS_UINT8 CNAS_HSM_GetSlotVoteBox(VOS_VOID)
{
    return CNAS_HSM_GetHsmCtxAddr()->stLowPowerCtrlInfo.ucSlotVoteBox;
}


VOS_VOID CNAS_HSM_SetSlotVoteBox(VOS_UINT8 ucSlotVoteBox)
{
    CNAS_HSM_GetHsmCtxAddr()->stLowPowerCtrlInfo.ucSlotVoteBox = ucSlotVoteBox;
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




