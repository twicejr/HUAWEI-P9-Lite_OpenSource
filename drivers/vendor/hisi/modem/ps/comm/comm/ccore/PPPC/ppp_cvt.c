/************************************************************************
*                                                                      *
*                             ppp_cvt.c                                *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2000/03/27                                      *
*  Author:             Deng Yi Ou                                      *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PPP模块的全局变量定义                           *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
*  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
*                      ALL RIGHTS RESERVED                             *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*   这个文件定义了PPP模块的所有全局变量                                *
*                                                                      *
************************************************************************/



/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "ppp_inc.h"
#include "fwd_ppp.h"
#include "pppc_ctrl.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_CVT_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
extern VOS_UINT16                        g_usPppSynSliceBufUsedLen;
extern PPP_REBUILD_INCOMPLETE_SLICE_STRU g_stPppRebuildIncompleteSliceStat;
extern VOS_UINT8                         g_aucPppRebuildSynSliceBuffer[];

VOS_UINT16 usFcsTab[256] = {
    /*
     * FCS lookup table as calculated by the table generator.
     */
    0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf,
    0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7,
    0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e,
    0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876,
    0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd,
    0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5,
    0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c,
    0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974,
    0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,
    0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3,
    0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,
    0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72,
    0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9,
    0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1,
    0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738,
    0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70,
    0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7,
    0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
    0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036,
    0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e,
    0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5,
    0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd,
    0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134,
    0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c,
    0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3,
    0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb,
    0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,
    0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a,
    0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1,
    0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9,
    0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330,
    0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78
};

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */

/****************************************************************************
* CREATE DATE  ：2015/06/18                                                 *
* CREATED BY   ：chenxianhua                                                 *
* FUNCTION     ：将上行数据同步报文转换为异步报文                                   *
* MODIFY DATE  ：                                                           *
* INPUT        ：pMbuf:同步报文                                             *
*                ulAsynAccm:同异步转换字符                                  *
* OUTPUT       ：                                                           *
* RETURN       ：转换后的异步报文,NULL则表示失败                            *
* CALLED BY    ：PPP_Shell_SendPacketToISL                                  *
****************************************************************************/
VOS_UINT32 PPP_UlDataSynToAsy
(
    VOS_UINT8                          *pucHeadData,
    VOS_UINT16                          usHeadDataLen,
    VOS_UINT8                          *pucSrcData,
    VOS_UINT16                          usSrcDataLen,
    VOS_UINT32                          ulAccmValue
)
{
    VOS_UINT16                          usTmpFcs    = 0;
    VOS_UINT16                          usTmpFcs1   = 0;
    VOS_UINT16                          usFcs       = 0xffff;
    VOS_UINT16                          usAsynDstLen;
    VOS_UINT32                          ulIndex;
    VOS_UINT8                           ucOctet;
    VOS_UINT8                          *pucDstDataPtr;
    VOS_UINT8                          *pucFcsValue;
    VOS_UINT8                          *pucHeadPtr;


    /* 内部调用保证指针非空 */

    pucDstDataPtr   = PPP_GetUlEncapDataPtr();
    PPP_InitEncapDataPtr();
    pucHeadPtr      = pucHeadData;

    /* 填充0x7e头部 */
    *pucDstDataPtr  = 0x7e;
    pucDstDataPtr++;
    usAsynDstLen = 1;

    /* 计算地址控制域和协议域的FCS */
    /* | 0xff 0x03   | 0x00 0x21 | */
    for (ulIndex = 0; ulIndex < usHeadDataLen; ulIndex++)
    {
        ucOctet = *pucHeadPtr;

        /* 计算校验和 */
        usFcs = (usFcs >> 8) ^ usFcsTab[(usFcs ^ ucOctet) & 0xff];

        /* 将当前字节转到异步报文 */
        PPP_ConvertByteToAsy(ucOctet, pucDstDataPtr, usAsynDstLen, ulAccmValue);

        /* 移动同步报文指针 */
        pucHeadPtr++;
    }

    /* 计算数据域的FCS */
    for (ulIndex = 0; ulIndex < usSrcDataLen; ulIndex++)
    {
        ucOctet = *pucSrcData;

        /* 计算校验和 */
        usFcs = (usFcs >> 8) ^ usFcsTab[(usFcs ^ ucOctet) & 0xff];

        /* 将当前字节转到异步报文 */
        PPP_ConvertByteToAsy(ucOctet, pucDstDataPtr, usAsynDstLen, ulAccmValue);

        /* 移动同步报文指针 */
        pucSrcData++;
    }

    /* 计算校验和 */
    usTmpFcs  = usFcs ^ 0xffff;
    usTmpFcs1 = usTmpFcs;
    usTmpFcs  = (usTmpFcs >> 8) & 0x00ff;
    usTmpFcs1 = (usTmpFcs1 << 8) & 0xff00;
    usTmpFcs |= usTmpFcs1;
    usFcs = VOS_NTOHS(usTmpFcs);

    /* 处理校验和 */
    pucFcsValue = (VOS_UINT8 *)&usFcs;
    for (ulIndex = 0; ulIndex < 2; ulIndex++)
    {
        ucOctet = *(pucFcsValue);
        PPP_ConvertByteToAsy(ucOctet, pucDstDataPtr, usAsynDstLen, ulAccmValue);
        pucFcsValue++;
    }

    /* 异步报文的结束字符 */
    *pucDstDataPtr = '\x7e';
    usAsynDstLen++;

    return usAsynDstLen;
}


/****************************************************************************
* CREATE DATE  ：2000/04/04                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：将同步报文转换为异步报文                                   *
* MODIFY DATE  ：                                                           *
* INPUT        ：pMbuf:同步报文                                             *
*                ulAsynAccm:同异步转换字符                                  *
* OUTPUT       ：                                                           *
* RETURN       ：转换后的异步报文,NULL则表示失败                            *
* CALLED BY    ：PPP_Shell_SendPacketToISL                                  *
****************************************************************************/
PMBUF_S *PPP_SynToAsy(PMBUF_S *pstSynMBuf, VOS_UINT32 ulAsynAccm)
{
    PMBUF_S *pstAsyBuf;
    UCHAR *pSynData;
    UCHAR *pAsyData = NULL;
    UCHAR *pAsyHead = NULL;
    VOS_UINT32 ulAsyLen = 0;
    VOS_UINT32 ulAsyDataBlockLen = 0;
    VOS_UINT32 ulSynFragLen = 0;  /* 同步报文各分片的长度 */
    VOS_UINT32 i = 0;
    PMBUF_DATABLOCKDESCRIPTOR_S *pstDBDescriptor;/*指向当前操作的MBUF片的描述符*/
    VOS_UINT16 usFcs = 0xffff;
    VOS_UINT16 usTmpFcs;
    VOS_UINT16 usTmpFcs1;
    UCHAR ucOctet;
    VOS_UINT32 ulRetCode = 0;

    if (NULL == pstSynMBuf)
    {
        return NULL;
    }

    ulAsynAccm = VOS_NTOHL(ulAsynAccm);

    /* 最大可能的异步报文长度:
       1字节异步起始字符 + (报文体长度 + 2字节校验和) * 2 + 1字节异步结束字符
       = 报文长度 * 2 + 6
     */
    ulAsyDataBlockLen = PMBUF_GET_TOTAL_DATA_LENGTH(pstSynMBuf) * 2 + 6;

    /* 根据同步报文大小,申请异步报文,大小为同步报文*2+2 */

    /* modified by luofang  切平台 20120925 */
    pAsyHead = (UCHAR *)PPP_Malloc(ulAsyDataBlockLen);
    if (pAsyHead == NULL)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_424);
        (VOID)PMBUF_Destroy(pstSynMBuf);
        return NULL;
    }

    pAsyData = pAsyHead;

    /* 异步报文的起始字符 */
    *pAsyData = (unsigned char)0x7e;
    pAsyData++;
    ulAsyLen++;

    /* 报文体 */
    pstDBDescriptor = (PMBUF_DATABLOCKDESCRIPTOR_S *)PMBUF_GET_DATA_BLOCK_DESC(pstSynMBuf);
    while (pstDBDescriptor != NULL)
    {
        /* 获取当前片的数据区指针和长度,并将pstDBDescriptor指向下一片 */
        PMBUF_GET_DATA_BLOCK_DESC_INFO(pstDBDescriptor,
                                      pSynData,
                                      ulSynFragLen,
                                      pstDBDescriptor
        );

        for (i = 0; i < ulSynFragLen; i++)
        {
            ucOctet = *(pSynData);

            /* 计算校验和 */
            usFcs = (usFcs >> 8) ^ usFcsTab[(usFcs ^ ucOctet) & 0xff];

            /* 将当前字节转到异步报文 */
            PPP_ConvertByteToAsy(ucOctet, pAsyData, ulAsyLen, ulAsynAccm);

            /* 移动同步报文指针 */
            pSynData++;
        }
    }

    /* 计算校验和 */
    usTmpFcs  = usFcs ^ 0xffff;
    usTmpFcs1 = usTmpFcs;
    usTmpFcs  = (usTmpFcs >> 8) & 0x00ff;
    usTmpFcs1 = (usTmpFcs1 << 8) & 0xff00;
    usTmpFcs |= usTmpFcs1;
    usFcs = VOS_NTOHS(usTmpFcs);

    /* 处理校验和 */
    pSynData = (UCHAR *)&usFcs;
    for (i = 0; i < 2; i++)
    {
        ucOctet = *(pSynData);
        PPP_ConvertByteToAsy(ucOctet, pAsyData, ulAsyLen, ulAsynAccm);
        pSynData++;
    }

    /* 异步报文的结束字符 */
    *pAsyData = '\x7e';
    ulAsyLen++;

    pstAsyBuf = (PMBUF_S *)PMBUF_GetPMbuf(MID_PPPC, ulAsyLen);
    if (NULL == pstAsyBuf)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_425);
        PPP_Free(pAsyHead);
        /* 释放异步报文 */
        (VOID)PMBUF_Destroy(pstSynMBuf);
        return NULL;
    }

    ulRetCode = PMBUF_CopyDataFromBufferToPMBuf(pstAsyBuf,
                                             0,
                                             ulAsyLen,
                                             (UCHAR *)pAsyHead,
                                             MID_PPPC);
    if (VOS_OK != ulRetCode)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_426);
        (VOID)PMBUF_Destroy(pstAsyBuf);
        PPP_Free(pAsyHead);
        /* 释放异步报文 */
        (VOID)PMBUF_Destroy(pstSynMBuf);
        return NULL;
    }

    /* 释放同步报文 */
    (VOID)PMBUF_Destroy(pstSynMBuf);

    PPP_Free(pAsyHead);

    return pstAsyBuf;
}

/******************************************************************************
函 数 名  : FWD_PppAsynToSyn
功能描述  : 将一实际异步数据段转换为同步数据段
输入参数  :
            VOS_UINT16                          usLenToHandle,
            VOS_UINT8                          *pucAsynData,
            VOS_UINT8                          *ucIsFinished
输出参数  : NA
全局变量  : NA
返 回 值  : NA
调用函数  : NA
被调函数  : NA

修改历史      :
1.日    期   : 星期六 2015年8月13日
作    者   : zWX297122
修改内容   : 新生成函数

******************************************************************************/
VOS_UINT32 PPP_AsyToSyn
(
    VOS_UINT8                           ucAsynByte
)
{
    static VOS_UINT32                   ulDLE = BOOL_FALSE;
    static VOS_UINT16                   usFcs = 0xffff;
    VOS_UINT8                          *pucSynBufPtr = g_aucPppRebuildSynSliceBuffer+g_usPppSynSliceBufUsedLen;
    VOS_UINT32                          ulRet = 0;


    if(g_usPppSynSliceBufUsedLen > 1560)
    {
        PS_MEM_SET(&g_stPppRebuildIncompleteSliceStat, 0, sizeof(g_stPppRebuildIncompleteSliceStat));
        g_usPppSynSliceBufUsedLen = 0;
        return ulRet;
    }

    switch (ucAsynByte)
    {
    case 0x7e:
        if ((ulDLE == BOOL_FALSE) && (0xf0b8 == usFcs))
        {
            /* valid  frame*/
            /* convert finished. */
            g_usPppSynSliceBufUsedLen -= 2; /* 合法报文长度 */
            /*合法报文，转化成功*/
            ulRet = 1;
        }
        ulDLE = BOOL_FALSE;
        usFcs = 0xffff;
        break;
    case 0x7d:
        if (ulDLE == BOOL_FALSE)
        {
            ulDLE = BOOL_TRUE;/* set the DLE flag */
        }
        else
        {
            /*if it has been mapped*/
            ulDLE = BOOL_FALSE;
            *pucSynBufPtr = ucAsynByte ^ (UCHAR)0x20;

            /* save the character*/
            usFcs = (usFcs >> 8) ^ usFcsTab[ (usFcs ^ *pucSynBufPtr) & 0xff ];
            pucSynBufPtr++;
            g_usPppSynSliceBufUsedLen++; /* adjust the value of frame length */
        }

        break;
    default:
        if (ulDLE)/* if the prior character is Control Escape  */
        {
            /* recover the original character:  */
            *pucSynBufPtr = ucAsynByte ^ (UCHAR)0x20;
            ulDLE = BOOL_FALSE;
        }
        else
        {
            *pucSynBufPtr = ucAsynByte;
        }                       /* save the character */

        usFcs = (usFcs >> 8)
            ^ usFcsTab[ (usFcs ^ (*pucSynBufPtr)) & 0xff ];

        /* update the value of FCS */
        g_usPppSynSliceBufUsedLen++;   /* adjust the value of frame length */
        break;
    } /* end of switch */

    (VOS_VOID)pucSynBufPtr;
    return ulRet;
}


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
