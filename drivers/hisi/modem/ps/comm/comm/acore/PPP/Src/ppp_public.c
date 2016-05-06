/*
 *
 * All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses. You may choose this file to be licensed under the terms
 * of the GNU General Public License (GPL) Version 2 or the 2-clause
 * BSD license listed below:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/******************************************************************************
   1 头文件包含
******************************************************************************/
#include "PPP/Inc/ppp_public.h"
#include "PPP/Inc/hdlc_interface.h"

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767  打点日志文件宏ID定义 */
#define    THIS_FILE_ID                 PS_FILE_ID_PPP_PUBLIC_C
/*lint +e767   */


/******************************************************************************
   2 外部函数变量声明
******************************************************************************/



/******************************************************************************
   3 私有定义
******************************************************************************/


#if (FEATURE_ON == FEATURE_PPP)
/******************************************************************************
   4 全局变量定义
******************************************************************************/
extern PPP_DATA_Q_CTRL_ST               g_PppDataQCtrl;

VOS_UINT32                              g_ulPppDebugLevel = PS_PRINT_WARNING;
/******************************************************************************
   5 函数实现
******************************************************************************/
/*****************************************************************************
 函 数 名  : PPP_MemAlloc
 功能描述  : 分配零拷贝内存
 输入参数  : usLen      -- 数据块长度,单位为字节
 输出参数  : 无
 返 回 值  : 零拷贝内存指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011-03-09
    作    者   : l00164359
    修改内容   : Created
*****************************************************************************/
PPP_ZC_STRU * PPP_MemAlloc(VOS_UINT16 usLen, VOS_UINT16 usReserveLen)
{
    /* 该接口用在上行时需要保留MAC头长度，
      上行与ADS收发数为IP包，为与NDIS、E5保持数据结构统一，需要保留MAC头，
      零拷贝指针从C核返回的时候统一偏移固定字节，找到零拷贝头部。
    */
    /*
       用在下行时保留长度填0，下行与USB收发数据为字节流形式的PPP帧，无MAC头
    */
    PPP_ZC_STRU *pstMem = PPP_ZC_MEM_ALLOC(usLen + usReserveLen);


    if (VOS_NULL_PTR != pstMem)
    {
        if ( usReserveLen > 0)
        {
            /* 空出保留长度，对PPP模块而言数据长度是usLen，这个函数必须在未赋值前调用 */
            PPP_ZC_RESERVE(pstMem, usReserveLen);

            /* 更新上行申请总次数 */
            g_PppDataQCtrl.stStat.ulMemAllocUplinkCnt++;

            /* 用于区分协商阶段释放的数据来源 */
            PPP_ZC_SET_DATA_APP(pstMem, (VOS_UINT16)(1 << 8) | (VOS_UINT16)PPP_PULL_PACKET_TYPE);
        }
        else
        {
            /* 更新下行申请总次数 */
            g_PppDataQCtrl.stStat.ulMemAllocDownlinkCnt++;

            /* 用于区分协商阶段释放的数据来源 */
            PPP_ZC_SET_DATA_APP(pstMem, (VOS_UINT16)(1 << 8) | (VOS_UINT16)PPP_PUSH_PACKET_TYPE);
        }
    }
    else
    {
        if ( usReserveLen > 0)
        {
            /* 更新上行申请失败次数 */
            g_PppDataQCtrl.stStat.ulMemAllocUplinkFailCnt++;
        }
        else
        {
            /* 更新下行申请失败次数 */
            g_PppDataQCtrl.stStat.ulMemAllocDownlinkFailCnt++;
        }
    }

    return pstMem;
}

/*****************************************************************************
 函 数 名  : PPP_MemWriteData
 功能描述  : 往零拷贝数据结构写入一定长度的数据
 输入参数  : pMemSrc  -- 要获取数据的TTF内存块头指针
 输出参数  : 无
 返 回 值  : 数据长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011-12-14
    作    者   : l00164359
    修改内容   : Created
*****************************************************************************/
VOS_VOID PPP_MemWriteData(PPP_ZC_STRU *pstMem, VOS_UINT8 *pucSrc, VOS_UINT16 usLen)
{
    /* 设置好将要写入零拷贝内存数据内容长度 */
    PPP_ZC_SET_DATA_LEN(pstMem, usLen);

    /* 拷贝至内存数据部分 */
    PPP_MemSingleCopy(PPP_ZC_GET_DATA_PTR(pstMem), pucSrc, usLen);

    return;
}

/*****************************************************************************
 函 数 名  : PPP_MemCopyAllocForUlSdu
 功能描述  : 分配零拷贝内存块，并且填入已经填写完成的数据内容
 输入参数  : pSrc  -- 已经完成填写的数据头指针
             usLen -- 要复制的数据块长度,单位为字节
 输出参数  : 无
 返 回 值  : TTF内存块
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011-03-09
    作    者   : l00164359
    修改内容   : Created
*****************************************************************************/
PPP_ZC_STRU * PPP_MemCopyAlloc(VOS_UINT8 *pSrc, VOS_UINT16 usLen, VOS_UINT16 usReserveLen)
{
    PPP_ZC_STRU                        *pstMem = VOS_NULL_PTR;


    pstMem = PPP_MemAlloc(usLen, usReserveLen);

    if ( VOS_NULL_PTR != pstMem )
    {
        /* 拷贝至内存数据部分 */
        PPP_MemWriteData(pstMem, pSrc, usLen);
    }

    return pstMem;
}

/*****************************************************************************
 函 数 名  : PPP_MemCutTailData
 功能描述  : 从零拷贝块尾部移去指定字节数目的数据
 输入参数  : ppMemSrc   -- TTF MEM内存结构
             pucDest    -- 数据拷贝目的地地址
             ulDataLen  -- 需拷贝长度
 输出参数  : 无
 返 回 值  : 获取数据成功返回PS_SUCC；失败返回PS_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011-03-09
    作    者   : l00164359
    修改内容   : Created
*****************************************************************************/
VOS_UINT32 PPP_MemCutTailData
(
    PPP_ZC_STRU **ppMemSrc,
    VOS_UINT8 *pucDest,
    VOS_UINT16 usLen,
    VOS_UINT16 usReserveLen
)
{
    PPP_ZC_STRU                        *pCurrMem;
    VOS_UINT16                          usCurrLen;
    VOS_UINT16                          usCurrOffset;


    /* 参数检查 */
    if ( (VOS_NULL_PTR == ppMemSrc) ||
         (VOS_NULL_PTR == *ppMemSrc) ||
         (VOS_NULL_PTR == pucDest))
    {
        PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                      "PPP_MemCutTailData input parameters error, \
                      src addr'addr: 0X%p, dest addr: 0X%p\r\n",
                      (VOS_UINT_PTR)ppMemSrc, (VOS_UINT_PTR)pucDest);

        return PS_FAIL;
    }

    pCurrMem    = (PPP_ZC_STRU *)(*ppMemSrc);
    usCurrLen   = PPP_ZC_GET_DATA_LEN(pCurrMem);

    if ( ( 0 == usLen) || (usCurrLen < usLen) )
    {
        PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                      "PPP_MemCutTailData, Warning, usCurrLen %d Less Than usLen %d!\r\n",
                      usCurrLen, usLen);

        return PS_FAIL;
    }

    /* 从尾部拷贝定长数据，只会有一个节点 */
    usCurrOffset = usCurrLen - usLen;

    mdrv_memcpy(pucDest, &(PPP_ZC_GET_DATA_PTR(pCurrMem)[usCurrOffset]), usLen);

    if ( usCurrOffset > 0 )
    {
        /* 还有剩余数据，目前没有重算长度并将Tail指针前移的接口，重新申请 */
        (*ppMemSrc) = PPP_MemCopyAlloc(PPP_ZC_GET_DATA_PTR(pCurrMem), usCurrOffset, usReserveLen);
    }
    else
    {
        (*ppMemSrc) = VOS_NULL_PTR;
    }

    /* 释放内存 */
    PPP_MemFree(pCurrMem);

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : PPP_MemCutHeadData
 功能描述  : 从零拷贝内存块头部拷贝指定字节数目的数据
             并将下个字节位置返回
 输入参数  : ppMemSrc   -- TTF MEM内存结构
             pucDest    -- 数据拷贝目的地地址
             ulDataLen  -- 需拷贝长度
 输出参数  : 无
 返 回 值  : 获取数据成功返回PS_SUCC；失败返回PS_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011-03-09
    作    者   : l00164359
    修改内容   : Created
*****************************************************************************/
VOS_UINT32 PPP_MemCutHeadData
(
    PPP_ZC_STRU **ppMemSrc,
    VOS_UINT8 *pucDest,
    VOS_UINT16 usDataLen
)
{
    PPP_ZC_STRU                        *pCurrMem;
    VOS_UINT16                          usMemSrcLen;


    if ( (VOS_NULL_PTR == ppMemSrc) ||
         (VOS_NULL_PTR == *ppMemSrc) ||
         (VOS_NULL_PTR == pucDest) )
    {
        PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, LOG_LEVEL_WARNING,
                     "PPP_MemCutHeadData input parameters error, \
                     src addr'addr: 0x%p, dest addr: 0x%p\r\n",
                    (VOS_UINT_PTR)ppMemSrc, (VOS_UINT_PTR)pucDest);

        return PS_FAIL;
    }

    /* 判断TTF内存块的长度是否符合要求 */
    pCurrMem        = (PPP_ZC_STRU *)(*ppMemSrc);
    usMemSrcLen     = PPP_ZC_GET_DATA_LEN(pCurrMem);

    if ( ( 0 == usDataLen) || (usMemSrcLen < usDataLen) )
    {
        PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, LOG_LEVEL_WARNING,
                      "PPP_MemCutHeadData, Warning: usMemSrcLen: %d Less Than usDataLen: %d!\r\n",
                      usMemSrcLen, usDataLen);

        return PS_FAIL;
    }

    /* 从头部拷贝定长数据，只会有一个节点 */
    mdrv_memcpy(pucDest, PPP_ZC_GET_DATA_PTR(pCurrMem), usDataLen);

    if ( usMemSrcLen >  usDataLen)
    {
        /* 还有剩余数据，更新数据指针和长度 */
        PPP_ZC_REMOVE_HDR(pCurrMem, usDataLen);
    }
    else
    {
        /* 释放原始内存 */
        PPP_MemFree(pCurrMem);
        (*ppMemSrc) = VOS_NULL_PTR;
    }

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : PPP_MemGet
 功能描述  : 从一TTF内存块获取一定长度的数据到指定目标地址
 输入参数  : pMemSrc  -- 要获取数据的TTF内存块头指针
             usOffset -- 内存块数据偏移
             pDest    -- 存放获取数据的目标地址
             usLen    -- 获取的数据长度，单位为字节
 输出参数  : 无
 返 回 值  : 获取数据成功返回PS_SUCC；失败返回PS_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011-03-09
    作    者   : l00164359
    修改内容   : Created
*****************************************************************************/
VOS_UINT32 PPP_MemGet(PPP_ZC_STRU *pMemSrc, VOS_UINT16 usOffset, VOS_UINT8 *pDest, VOS_UINT16 usLen)
{
    VOS_UINT16                          usMemSrcLen;


    /* 参数检查 */
    if ( (VOS_NULL_PTR == pMemSrc)||(VOS_NULL_PTR == pDest) )
    {
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                     "PPP_MemGet, Warning, Input Par pMemSrc Or pDest is Null!\r\n");

        return PS_FAIL;
    }

    if ( 0 == usLen )
    {
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                     "PPP_MemGet, Warning, Input Par usLen is 0!\r\n");

        return PS_FAIL;
    }

    /* 判断TTF内存块的长度是否符合要求 */
    usMemSrcLen = PPP_ZC_GET_DATA_LEN(pMemSrc);

    if ( usMemSrcLen < (usOffset + usLen) )
    {
        PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                      "PPP_MemGet, Warning, MemSrcLen %d Less Than (Offset + Len) %d!\r\n",
                      usMemSrcLen, (usOffset + usLen));

        return PS_FAIL;
    }

    mdrv_memcpy(pDest, PPP_ZC_GET_DATA_PTR(pMemSrc) + usOffset, usLen);

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : PPP_MemFreeWithData
 功能描述  : 释放零拷贝内存
 输入参数  : pstMem  --- TTF_MEM形式的数据
 输出参数  :
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011-03-09
    作    者   : l00164359
    修改内容   : Created
*****************************************************************************/
VOS_VOID PPP_MemFree(PPP_ZC_STRU *pstMem)
{
    /* 释放零拷贝内存 */
    PPP_ZC_MEM_FREE(pstMem);

    g_PppDataQCtrl.stStat.ulMemFreeCnt++;

    return;
}

/*****************************************************************************
 函 数 名  : PPP_MemSingleCopy
 功能描述  : 获取给定内存单元实际使用的总字节数，包括整个数据链
 输入参数  : pMemSrc  -- 要获取数据的TTF内存块头指针
 输出参数  : 无
 返 回 值  : 数据长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011-03-09
    作    者   : l00164359
    修改内容   : Created
*****************************************************************************/
VOS_VOID PPP_MemSingleCopy(VOS_UINT8 *pucDest, VOS_UINT8 *pucSrc, VOS_UINT32 ulLen)
{
    /* 待修改为EDMA拷贝 */
    mdrv_memcpy(pucDest, pucSrc, ulLen);

    return;
}

VOS_VOID     PPP_SetPrintLevel
(
    VOS_UINT32      ulLevel
)
{
    g_ulPppDebugLevel = ulLevel;
}

VOS_VOID     PPP_PrintLog
(
    VOS_UINT32      ulModuleId,
    VOS_UINT32      ulSubMod,
    VOS_UINT32      ulLevel,
    VOS_CHAR       *pcString
)
{
    if ( g_ulPppDebugLevel >=  ulLevel)
    {
        vos_printf(pcString);
    }

    return;
}

VOS_VOID     PPP_PrintLog1
(
    VOS_UINT32      ulModuleId,
    VOS_UINT32      ulSubMod,
    VOS_UINT32      ulLevel,
    VOS_CHAR       *pcString,
    VOS_INT32       lPara1
)
{
    if ( g_ulPppDebugLevel >=  ulLevel)
    {
        vos_printf(pcString, lPara1);
    }

    return;
}
VOS_VOID     PPP_PrintLog2
(
    VOS_UINT32      ulModuleId,
    VOS_UINT32      ulSubMod,
    VOS_UINT32      ulLevel,
    VOS_CHAR       *pcString,
    VOS_INT_PTR     lPara1,
    VOS_INT_PTR     lPara2
)
{
    if ( g_ulPppDebugLevel >=  ulLevel)
    {
        vos_printf(pcString, lPara1, lPara2);
    }

    return;
}

VOS_VOID     PPP_PrintLog3
(
    VOS_UINT32      ulModuleId,
    VOS_UINT32      ulSubMod,
    VOS_UINT32      ulLevel,
    VOS_CHAR       *pcString,
    VOS_INT32       lPara1,
    VOS_INT32       lPara2,
    VOS_INT32       lPara3
)
{
    if ( g_ulPppDebugLevel >=  ulLevel)
    {
        vos_printf(pcString, lPara1, lPara2, lPara3);
    }

    return;
}
VOS_VOID     PPP_PrintLog4
(
    VOS_UINT32      ulModuleId,
    VOS_UINT32      ulSubMod,
    VOS_UINT32      ulLevel,
    VOS_CHAR       *pcString,
    VOS_INT32       lPara1,
    VOS_INT32       lPara2,
    VOS_INT32       lPara3,
    VOS_INT32       lPara4
)
{
    if ( g_ulPppDebugLevel >=  ulLevel)
    {
        vos_printf(pcString, lPara1, lPara2, lPara3, lPara4);
    }

    return;
}
#else
VOS_VOID PPP_MemFree(PPP_ZC_STRU *pstMem)
{
    /* 释放零拷贝内存 */
    PPP_ZC_MEM_FREE(pstMem);

    return;
}

#endif


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

