/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMsgEncDec.c
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2007年8月25日
  最近修改   :
  功能描述   : 实现NAS消息编解码的通用接口
  函数列表   :
  修改历史   :
  1.日    期   : 2007年8月25日
    作    者   : 丁庆 49431
    修改内容   : 创建文件

******************************************************************************/


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "NasMsgEncDec.h"
#include "NasMntn.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif


/*****************************************************************************
  2 常量定义
*****************************************************************************/
/* IE在消息中不存在 */
#define  NAS_IE_NOT_EXIST             0
#define  NAS_IE_EXIST                   1

#define  NAS_IE_COMPREHENSION_REQUIRED_MASK    0xF0
#define  NAS_IE_COMPREHENSION_REQUIRED_VALUE   0

/*lint -save -e958 */

/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : NasEncodeIE
 功能描述  : Encode Nas IE
 输入参数  : pucSrc       - IE编码前数据源地址
             ucLen        - IE长度
             ulExtFlag    - Ext标志位
 输出参数  : pucDest      - IE编码后数据目的地址
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年8月25日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NasEncodeIE (
    VOS_UINT8                           *pucDest,
    const VOS_UINT8                     *pucSrc,
    VOS_UINT8                           ucLen,
    VOS_UINT32                          ulExtFlag
)
{
    VOS_UINT8 ucEncodeLen;

    /*if((*pucSrc < 0x80) && (!(ulExtFlag & 0x01)))
 */
    /*{
 */
    /*    CC_ERR_LOG("NasEncodeIE: ulExtFlag error.");
 */
    /*    return VOS_ERR;
 */
    /*}
 */

    for(ucEncodeLen = 0; ucLen > 0; ulExtFlag >>= 1)
    {
        if(((*pucDest++ = *pucSrc++) > 0x7F) && (ulExtFlag  & 0x01))
        {
            do
            {
                pucSrc++;
                if(ucLen > 0)
                {
                    ucLen--;
                }
                else
                {
                    break;
                }
            }while((ulExtFlag >>= 1) & 0x01);
        }
        ucEncodeLen++;
        if(ucLen > 0)
        {
            ucLen--;
        }
    }
    return ucEncodeLen;
}


/*****************************************************************************
 函 数 名  : NasDecodeIE
 功能描述  : Decode Nas IE
 输入参数  : pucSrc       - IE解码前数据源地址
             ucLen        - IE长度
             ulExtFlag    - Ext标志位
 输出参数  : pucDest      - IE解码后数据目的地址
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年8月25日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NasDecodeIE (
    VOS_UINT8                           *pucDest,
    const VOS_UINT8                     *pucSrc,
    VOS_UINT8                           ucLen,
    VOS_UINT32                          ulExtFlag
)
{
    VOS_UINT8 ucDecodeLen;
    for(ucDecodeLen = 0; ucLen > 0; ucDecodeLen++, ucLen--)
    {
        if(((*pucDest++ = *pucSrc++) > 0x7F) && (ulExtFlag & 0x01))
        {
            do
            {
                pucDest++;
                ucDecodeLen++;
            }while((ulExtFlag >>= 1) & 0x01);
        }
        ulExtFlag >>= 1;
    }
    return ucDecodeLen;
}


/*****************************************************************************
 函 数 名  : NasEncodeMsg
 功能描述  : Encode Nas Msg
 输入参数  : pstMsgEntry  - 消息入口表
             pucMsg       - 消息编码前数据源地址
 输出参数  : pucRawData   - 消息编码后数据目的地址
             pucLength    - 编码后的消息长度
 返 回 值  : 协议错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年8月25日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

*****************************************************************************/
NAS_PROTOCOL_ERR_ENUM_U8 NasEncodeMsg(
    const NAS_MSG_ENTRY_STRU            *pstMsgEntry,
    const VOS_UINT8                     *pucMsg,
    VOS_UINT8                           *pucRawData,
    VOS_UINT8                           *pucLength
)
{
    VOS_UINT8                           ucIeNum;
    VOS_UINT8                           ucIeLen,ucMsgLen;
    NAS_MSG_TBL_STRU                    *pstMsgTbl;
    const VOS_UINT8                     *pucSrcPos;

    pucSrcPos = pucMsg;

    *pucRawData++ = *pucSrcPos++;

    if(VOS_NULL_PTR == (pstMsgTbl = pstMsgEntry[*pucSrcPos].pstEncodeMsgTbl))
    {
        NAS_ERROR_LOG(WUEPS_PID_CC, "NasEncodeMsg: pstMsgTbl is NULL");

        return NAS_PROT_ERR_MSG_TYPE_UNKNOWN;
    }
    ucIeNum = (VOS_UINT8)pstMsgEntry[*pucSrcPos].ulEncodeIeNum;

    *pucRawData++ = *pucSrcPos++;

    ucMsgLen = 2;

    for(; (ucIeNum > 0); ucIeNum--, pstMsgTbl++)
    {
        pucSrcPos = pucMsg + pstMsgTbl->ulIePos;

        if (pstMsgTbl->enIeFormat & NAS_IE_FORMAT_T)
        {
            if( NAS_IE_NOT_EXIST != *pucSrcPos)
            {
                *pucRawData++ = ((*pucSrcPos) & ~pstMsgTbl->pstIeTbl->ucIEI_Msk)
                                + pstMsgTbl->pstIeTbl->ucIEI;
                ucMsgLen++;
            }
            else
            {
                if(NAS_IE_PRESENCE_M == pstMsgTbl->enIePresence)
                {
                    NAS_ERROR_LOG(WUEPS_PID_CC, "NasEncodeMsg: ERR MANDATORY IE ERR");

                    return NAS_PROT_ERR_MANDATORY_IE_ERR;
                }
                else
                {
                    continue;
                }
            }

        }


        if(pstMsgTbl->enIeFormat & NAS_IE_FORMAT_L)
        {
            if(pstMsgTbl->pstIeTbl->ucMinLen == pstMsgTbl->pstIeTbl->ucMaxLen)
            {
                ucIeLen = NasEncodeIE(pucRawData+1,
                                      pucSrcPos+2,
                                      pstMsgTbl->pstIeTbl->ucMinLen,
                                      pstMsgTbl->pstIeTbl->ulExtFlag);
            }
            else
            {
                ucIeLen = NasEncodeIE(pucRawData+1,
                                      pucSrcPos+2,
                                      *(pucSrcPos+1),
                                      pstMsgTbl->pstIeTbl->ulExtFlag);
                if((ucIeLen < pstMsgTbl->pstIeTbl->ucMinLen)
                    ||(ucIeLen > pstMsgTbl->pstIeTbl->ucMaxLen))
                {
                    NAS_ERROR_LOG(WUEPS_PID_CC, "NasEncodeMsg: INCORRECT CONTENT");

                    return NAS_PROT_ERR_INCORRECT_CONTENT;
                }
            }
            *pucRawData++ = ucIeLen;
            ucMsgLen++;
        }
        else
        {
            ucIeLen = NasEncodeIE(pucRawData,
                                  pucSrcPos+2,
                                  pstMsgTbl->pstIeTbl->ucMinLen,
                                  pstMsgTbl->pstIeTbl->ulExtFlag);

            /* 此处针对TV在一个字节内的情况做特殊处理 */
            if ((0 == pstMsgTbl->pstIeTbl->ucMinLen)
              &&(NAS_IE_FORMAT_TV == pstMsgTbl->enIeFormat)
              &&(1 == *(pucSrcPos+1)))
            {
                *(pucRawData-1) = ((*pucSrcPos+2) & ~pstMsgTbl->pstIeTbl->ucIEI_Msk)
                                + pstMsgTbl->pstIeTbl->ucIEI;
            }

        }

        ucMsgLen += ucIeLen;
        pucRawData += ucIeLen;
    }

    *pucLength = ucMsgLen;
    return NAS_PROT_ERR_NO_ERROR;
}


/*****************************************************************************
 函 数 名  : NasDecodeMsg
 功能描述  : Decode Nas Msg
 输入参数  : pstMsgEntry    - 消息入口表
             pucRawData     - 消息解码前数据源地址
             ucLength       - 解码前的消息长度
 输出参数  : pucMsg         - 消息解码后数据目的地址
 返 回 值  : 协议错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年8月25日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2010年01月15日
    作    者   : l65478
    修改内容   : 问题单号:AT2D14565，收到不期望的"comprehension required"的IE，
                 需要向网络发送status消息
  3.日    期   : 2010年02月5日
    作    者   : l65478
    修改内容   : 问题单号:AT2D16762，CC在解析optional IE时，解码错误
                 需要向网络发送status消息
  4.日    期   : 2013年02月25日
    作    者   : z00214637
    修改内容   : 问题单号:DTS2013022107190,CC在解析消息时，表格访问越界保护；
*****************************************************************************/
NAS_PROTOCOL_ERR_ENUM_U8 NasDecodeMsg(
    const NAS_MSG_ENTRY_STRU           *pstMsgEntry,
    VOS_UINT16                          usTableNum,
    const VOS_UINT8                    *pucRawData,
    VOS_UINT8                           ucLength,
    VOS_UINT8                          *pucMsg
)
{
    VOS_UINT8           ucIeNum;
    VOS_UINT8           ucIeLen;
    NAS_MSG_TBL_STRU    *pstMsgTbl;
    VOS_UINT8           *pucDstPos;
    VOS_UINT8           i;
    NAS_MSG_TBL_STRU    *pstMsgTblBake1;
    NAS_MSG_TBL_STRU    *pstMsgTblBake2;
    VOS_UINT8           ucIeNumBake;

    if(ucLength < 2)
    {
        return NAS_PROT_ERR_MSG_TOO_SHORT;
    }

    pucDstPos = pucMsg;
    *pucDstPos++ = *pucRawData++;
    ucLength --;

    if(*pucRawData >= usTableNum)
    {
        return NAS_PROT_ERR_MSG_TYPE_UNKNOWN;
    }

    pstMsgTbl = pstMsgEntry[*pucRawData].pstDecodeMsgTbl;
    if(VOS_NULL_PTR == pstMsgTbl)
    {
        return NAS_PROT_ERR_MSG_TYPE_UNKNOWN;
    }


    ucIeNum = (VOS_UINT8)pstMsgEntry[*pucRawData].ulDecodeIeNum;

    *pucDstPos++ = *pucRawData++;
    ucLength --;

    if ((ucIeNum > 0) && (ucLength == 0) )
    {
        if(NAS_IE_PRESENCE_M == pstMsgTbl->enIePresence)
        {
            return NAS_PROT_ERR_MANDATORY_IE_ERR;
        }
    }

    pstMsgTblBake1 = pstMsgTbl;
    pstMsgTblBake2 = pstMsgTbl;
    ucIeNumBake    = ucIeNum;
    for(; (ucIeNum > 0) && (ucLength > 0); ucIeNum--, pstMsgTbl++)
    {
        pucDstPos = pucMsg + pstMsgTbl->ulIePos;
        if (pstMsgTbl->enIeFormat & NAS_IE_FORMAT_T)
        {

            /* 因为在消息带有多个可选项时，中间的某个可选项可以不出现，
            或者出现的顺序和24.008 9.3中的顺序不同，
            所以在解码时需要循环查找消息中的IE */
            pstMsgTblBake1 = pstMsgTblBake2;
            for(i = 0; i < ucIeNumBake; i++)
            {
                if(pstMsgTblBake1->pstIeTbl->ucIEI ==
                    ((*pucRawData) & pstMsgTblBake1->pstIeTbl->ucIEI_Msk))
                {
                    break;
                }
                pstMsgTblBake1++;
            }
            if (i >= ucIeNumBake)
            {
                /* according to 24.007 11.2.5，
                An IE is encoded as 'comprehension required'
                if bits 5, 6, 7 and 8 of its IEI are set to zero.*/
                if ((NAS_IE_PRESENCE_M == pstMsgTbl->enIePresence)
                    || (NAS_IE_COMPREHENSION_REQUIRED_VALUE ==
                         ((*pucRawData) & NAS_IE_COMPREHENSION_REQUIRED_MASK)))
                {
                    return NAS_PROT_ERR_MANDATORY_IE_ERR;
                }
            }

            if(pstMsgTbl->pstIeTbl->ucIEI == ((*pucRawData) & pstMsgTbl->pstIeTbl->ucIEI_Msk))
            {
                *pucDstPos = NAS_IE_EXIST;
                pucRawData++;
                ucLength--;
            }
            else
            {
                if(NAS_IE_PRESENCE_M == pstMsgTbl->enIePresence)
                {
                    return NAS_PROT_ERR_MANDATORY_IE_ERR;
                }
                else
                {
                    *pucDstPos = NAS_IE_NOT_EXIST;
                    continue;
                }
            }

        }
        else
        {
            /**pucDstPos = pstMsgTbl->pstIeTbl->ucIEI;
 */
            *pucDstPos = NAS_IE_EXIST;
        }

        if(pstMsgTbl->enIeFormat & NAS_IE_FORMAT_L)
        {
            ucIeLen = *pucRawData++;
            ucLength--;
        }
        else
        {
            ucIeLen = pstMsgTbl->pstIeTbl->ucMinLen;
        }
        if( (ucIeLen < pstMsgTbl->pstIeTbl->ucMinLen)
          ||(ucIeLen > pstMsgTbl->pstIeTbl->ucMaxLen)
          ||(ucIeLen > ucLength))
        {
            return NAS_PROT_ERR_INCORRECT_CONTENT;
        }

        *(pucDstPos+1) = NasDecodeIE(pucDstPos+2,
                                     pucRawData,
                                     ucIeLen,
                                     pstMsgTbl->pstIeTbl->ulExtFlag);

        /*特殊处理，TV结构，但是V和T在一个字节里面*/
        if ((NAS_IE_FORMAT_TV == pstMsgTbl->enIeFormat)
         && (0 == pstMsgTbl->pstIeTbl->ucMaxLen))
        {
            *(pucDstPos+1) = 1;
            *(pucDstPos+2) = ((*(pucRawData-1)) & (~pstMsgTbl->pstIeTbl->ucIEI_Msk));
        }

        pucRawData += ucIeLen;
        ucLength -= ucIeLen;
    }
    return NAS_PROT_ERR_NO_ERROR;
}

/*lint -restore */


#ifdef  __cplusplus
#if  __cplusplus
}
#endif
#endif

