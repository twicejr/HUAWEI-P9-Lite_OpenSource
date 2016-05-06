/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasPrlParse.c
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年08月日
  功能描述   : NAS 1X&EVDO PRL解析处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年08月06日
    作    者   : y00245242
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "PsCommonDef.h"
#include "CnasPrlParse.h"
#include "CnasPrlMem.h"
#include "Crc.h"
#include "CnasPrlMntn.h"
#include "CnasCcb.h"
#include "Nas_Mem.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_PRL_PARSE_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define CNAS_PRL_BIT_TO_BYTE(pBuf, bOffSet, bLen)                                   \
        CNAS_PRL_ExtractBitStringToOctet(&pBuf[bOffSet/CNAS_PRL_BIT_LEN_8_BIT],     \
                                         (VOS_UINT8)bOffSet%CNAS_PRL_BIT_LEN_8_BIT, \
                                         bLen)

#define CNAS_PRL_BIT_TO_WORD(pBuf, bOffSet, bLen)                                   \
        CNAS_PRL_ExtractBitStringToWord(&pBuf[bOffSet/CNAS_PRL_BIT_LEN_8_BIT],      \
                                        (VOS_UINT8)bOffSet%CNAS_PRL_BIT_LEN_8_BIT,  \
                                        bLen)

/*****************************************************************************
  3 全局变量定义
*****************************************************************************/
CNAS_PRL_INFO_STRU                      g_stCnasPrlInfo;    /* 存储PRL信息全局变量 */

CNAS_PARSE_ACQ_TYPE_REC_PROC_ENTITY     g_astCnasPrlProcParseAcqTypeRec[] =
{
    {(VOS_UINT32)CNAS_PRL_ACQ_TYPE_CELLULAR_ANALOG                           , CNAS_PRL_ParseAcqRec_CellularAnalog},
    {(VOS_UINT32)CNAS_PRL_ACQ_TYPE_CELLULAR_CDMA_STANDARD_CHANNELS           , CNAS_PRL_ParseAcqRec_CellularCdmaStandard},
    {(VOS_UINT32)CNAS_PRL_ACQ_TYPE_CELLULAR_CDMA_CUSTOM_CHANNELS             , CNAS_PRL_ParseAcqRec_CellularCdmaCustom},
    {(VOS_UINT32)CNAS_PRL_ACQ_TYPE_CELLULAR_CDMA_PREFERRED                   , CNAS_PRL_ParseAcqRec_CellularCdmaPrefered},
    {(VOS_UINT32)CNAS_PRL_ACQ_TYPE_PCS_CDMA_USING_BLOCKS                     , CNAS_PRL_ParseAcqRec_PcsCdmaUsingBlocks},
    {(VOS_UINT32)CNAS_PRL_ACQ_TYPE_PCS_CDMA_USING_CHANNELS                   , CNAS_PRL_ParseAcqRec_PcsCdmaUsingChannels},
    {(VOS_UINT32)CNAS_PRL_ACQ_TYPE_JTACS_CDMA_STANDARD_CHANNELS              , CNAS_PRL_ParseAcqRec_JtacsCdmaStandardChannels},
    {(VOS_UINT32)CNAS_PRL_ACQ_TYPE_JTACS_CDMA_CUSTOM_CHANNELS                , CNAS_PRL_ParseAcqRec_JtacsCdmaCustomChannels},
    {(VOS_UINT32)CNAS_PRL_ACQ_TYPE_2G_BAND_USING_CHANNELS                    , CNAS_PRL_ParseAcqRec_2gBandUsingChannels},
    {(VOS_UINT32)CNAS_PRL_ACQ_TYPE_GENERIC_ACQ_RECORD_FOR_1X_AND_IS95        , CNAS_PRL_ParseAcqRec_GenericCdma1X},
    {(VOS_UINT32)CNAS_PRL_ACQ_TYPE_GENERIC_ACQ_RECORD_FOR_HRPD               , CNAS_PRL_ParseAcqRec_GenericAcqRecordForHrpd},
    {(VOS_UINT32)CNAS_PRL_ACQ_TYPE_Reserved_FOR_OBSOLETE_IDENTIFICATION      , CNAS_PRL_ParseAcqRec_NotSupportRecType},
    {(VOS_UINT32)CNAS_PRL_ACQ_TYPE_COMMON_ACQ_TABLE_RECORD_FOR_UMB           , CNAS_PRL_ParseAcqRec_ComAcqTabRecordForUmb},
    {(VOS_UINT32)CNAS_PRL_ACQ_TYPE_COMMON_ACQ_RECORD_FOR_UMB                 , CNAS_PRL_ParseAcqRec_ComAcqRecordForUmb},
};

/*****************************************************************************
  4 函数定义
*****************************************************************************/
/*lint -save -e958 */

/*****************************************************************************
 函 数 名  : CNAS_PRL_IsAcqRecTabValid
 功能描述  : 捕获记录表是否有效
 输入参数  : pstAcqRecInfo -- 捕获表记录信息
 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 有效
             VOS_FALSE -- 无效
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年08月08日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_PRL_IsAcqRecTabValid(
    CNAS_PRL_ACQ_RECORD_INFO_STRU      *pstAcqRecInfo
)
{
    VOS_UINT32                          i;

    for (i = 0; i < pstAcqRecInfo->usAcqRecordNum; i++)
    {
        if ((VOS_NULL_PTR != pstAcqRecInfo->pastPrlAcqRecord[i])
        &&  (VOS_TRUE     == pstAcqRecInfo->pastPrlAcqRecord[i]->ucAcqValid))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_PRL_IsSysRecTabValid
 功能描述  : 系统记录表是否有效
 输入参数  : pstSysRecInfo -- 系统表记录信息
 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 有效
             VOS_FALSE -- 无效
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年08月08日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_PRL_IsSysRecTabValid(
    CNAS_PRL_SYS_RECORD_INFO_STRU      *pstSysRecInfo
)
{
    VOS_UINT32                          i;

    for (i = 0; i < pstSysRecInfo->usSysRecordNum; i++)
    {
        if ((VOS_NULL_PTR != pstSysRecInfo->pstSysRecord)
        &&  (VOS_TRUE     == pstSysRecInfo->pstSysRecord[i].ucSysRecValid))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_PRL_GetPrlInfoAddr
 功能描述  : 获取当前PRL信息首地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回PRL信息首地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年08月08日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_PRL_INFO_STRU* CNAS_PRL_GetPrlInfoAddr(VOS_VOID)
{
    return &(g_stCnasPrlInfo);
}

/*****************************************************************************
 函 数 名  : CNAS_PRL_CheckPrlCrcChecksum
 功能描述  : 验证CRC校验和
 输入参数  : pPrl -- prl原始数据地址
 输出参数  : 无
 返 回 值  : CNAS_PRL_PARSE_SUCCESS  － CRC校验成功
             CNAS_PRL_PARSE_CRC_FAIL － CRC校验失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年08月06日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_PRL_PARSE_CAUSE_ENUM_UINT32 CNAS_PRL_CheckPrlCrcChecksum(
    VOS_UINT8                          *pPrl
)
{
    VOS_UINT16                          usCrcCalLength;
    VOS_UINT16                          usPrlListCrc;
    VOS_UINT16                          usPrlListSize;
    VOS_UINT16                          usCalcCrc;
    VOS_UINT8                          *pBuff = VOS_NULL_PTR;

    pBuff        = pPrl;

    /* 获取PRL list size */
    usPrlListSize = CNAS_PRL_ExtractBitStringToWord(pBuff, 0, CNAS_PRL_BIT_LEN_16_BIT);

    /* See 3.5.5.1 Preferred Roaming List CRC Calculation in C.S0016-D:
       The 16-bit preferred roaming list CRC field PR_LIST_CRC is calculated on all bits of the
       Preferred Roaming List/Extended Preferred Roaming List excluding the bits of the PR_LIST_CRC
       field itself. The generator polynomial for this CRC is g(x) = x16 + x12 + x5 + x0 */
    usCrcCalLength = usPrlListSize - sizeof(VOS_UINT16);

    /* PR_LIST_SIZE - Preferred roaming list size.
       This field is set to the total size, in octets, of the preferred roaming list, including
       the PR_LIST_SIZE and PR_LIST_CRC fields. */
    usPrlListCrc = CNAS_PRL_BIT_TO_WORD(pBuff, (usCrcCalLength * CNAS_PRL_BIT_LEN_8_BIT), CNAS_PRL_BIT_LEN_16_BIT);

    /* 计算CRC, length需要转换成bit流 */
    usCalcCrc = CRC_CalculateCRC16(pBuff, usCrcCalLength * CNAS_PRL_BIT_LEN_8_BIT);

    if (usPrlListCrc == usCalcCrc)
    {
        return CNAS_PRL_PARSE_SUCCESS;
    }

    return CNAS_PRL_PARSE_CRC_FAIL;
}


/*****************************************************************************
 函 数 名  : CNAS_PRL_ExtractBitStringToOctet
 功能描述  : 由给定的字节流的开始地址，以及对应的bit偏移量，对应数据结构的bit长度，做数据的赋值
 输入参数  : pucSrcAddr  -- 对应的bit字节流的地址
             usOffsetPos -- 一个字节中的偏移位置
             usBitLen    -- 需要赋值的bit长度
 输出参数  : 无
 返 回 值  : 转换后的字节内容
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月5日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
/*lint -e701*/
VOS_UINT8  CNAS_PRL_ExtractBitStringToOctet(
    VOS_UINT8                          *pucSrcAddr,
    VOS_UINT8                           ucOffsetPos,
    VOS_UINT8                           ucBitLen
)
{
    VOS_UINT8                          *pucBuffOffset = VOS_NULL_PTR;
    VOS_INT16                           iRemainBitLen;
    VOS_UINT8                           ucExtractByte;
    VOS_UINT8                           ucRemainLen;

    pucBuffOffset = pucSrcAddr;

    iRemainBitLen = (VOS_INT16)(CNAS_PRL_BIT_LEN_8_BIT - (ucOffsetPos + ucBitLen));

    /* 如果一个字节左移usOffsetPos，剩余bit的长度大于等于usOffsetPos，则直接在该字节中进行取值 */
    /* 如果一个字节左移usOffsetPos，剩余bit的长度小于usOffsetPos,则还需要从下一个字节中进行取值*/
    if ( iRemainBitLen >= 0 )
    {
        ucExtractByte =  (VOS_UINT8)(((VOS_UINT8)((*pucBuffOffset) << ucOffsetPos)) >> (ucOffsetPos + iRemainBitLen));
    }
    else
    {
        /* 计算剩余位 */
        ucRemainLen = (VOS_UINT8)(ucBitLen - (CNAS_PRL_BIT_LEN_8_BIT - ucOffsetPos));

        ucExtractByte = (VOS_UINT8)(((*pucBuffOffset) & (0xFF >> ucOffsetPos)) << ucRemainLen);

        pucBuffOffset++;

        /* 把字节剩余bit补齐 */
        ucExtractByte |= (VOS_UINT8)(((*pucBuffOffset) & 0xFF) >> (CNAS_PRL_BIT_LEN_8_BIT - ucRemainLen));
    }

    return ucExtractByte;

}
/*lint +e701*/


/*****************************************************************************
 函 数 名  : CNAS_PRL_ExtractBitStringToWord
 功能描述  : 由给定的字节流的开始地址，以及对应的bit偏移量，对应数据结构的bit长度，做数据的赋值
 输入参数  : pucSrcAddr  -- 对应的bit字节流的地址
             usOffsetPos -- 当前字节的bit偏移位置
             usBitLen    -- 需要赋值的bit长度
 输出参数  : 无
 返 回 值  : 转换后的双字节内容
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月5日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
/*lint -e701*/
VOS_UINT16 CNAS_PRL_ExtractBitStringToWord(
    VOS_UINT8                          *pucSrcAddr,
    VOS_UINT8                           ucOffsetPos,
    VOS_UINT8                           ucBitLen
)
{
    VOS_UINT8                          *pucTmpSrc = VOS_NULL_PTR;
    VOS_UINT16                          usExtractWord;
    VOS_UINT16                          usRemainBitLen;

    pucTmpSrc = pucSrcAddr;

    if (ucBitLen > CNAS_PRL_BIT_LEN_16_BIT)
    {
        ucBitLen = CNAS_PRL_BIT_LEN_16_BIT;
    }

    if (ucBitLen <= CNAS_PRL_BIT_LEN_8_BIT)
    {
        /* 避免bit length小于等于8bit的处理 */
        usExtractWord = (VOS_UINT16)CNAS_PRL_ExtractBitStringToOctet(pucTmpSrc,
                                                                     ucOffsetPos,
                                                                     ucBitLen);

        return usExtractWord;
    }

    /* 计算除去当前字节有效bit后，剩余bit长度 */
    usRemainBitLen = (VOS_UINT16)(ucBitLen - (CNAS_PRL_BIT_LEN_8_BIT - ucOffsetPos));

    /* 获取首个字节数据部分，并移到对应的高位, 空出剩余bit位 */
    usExtractWord  = (VOS_UINT16)(((*pucTmpSrc) & (0xFF >> ucOffsetPos)) << usRemainBitLen);

    /* 指向下一个字节 */
    pucTmpSrc++;

    /* 检查剩余长度 */
    if (usRemainBitLen > CNAS_PRL_BIT_LEN_8_BIT)
    {
        /* 设置剩下未取完的bit */
        usRemainBitLen -= CNAS_PRL_BIT_LEN_8_BIT;

        /* 左移，空出剩余bit位 */
        usExtractWord |= (VOS_UINT16)((VOS_UINT8)(*pucTmpSrc) << usRemainBitLen);
    }
    else
    {
        /* 把字节剩余bit补齐 */
        usExtractWord |= (VOS_UINT16)(((*pucTmpSrc) & 0xFF) >> (CNAS_PRL_BIT_LEN_8_BIT - usRemainBitLen));

        /* bit已经取完，清0 */
        usRemainBitLen = 0;
    }

    if (usRemainBitLen > 0)
    {
        pucTmpSrc++;

        /* 把字节剩余bit补齐 */
        usExtractWord |= (VOS_UINT16)(((*pucTmpSrc) & 0xFF) >> (CNAS_PRL_BIT_LEN_8_BIT - usRemainBitLen));
    }

    /* 类似转换成字节的处理 */
    return usExtractWord;
}
/*lint +e701*/


/*****************************************************************************
 函 数 名  : CNAS_PRL_ParseAcqRec_CellularCdmaStandard
 功能描述  : 解析一条acquisition record记录,Acquisition Record Type类型为
             Cellular CDMA (Standard Channels)
 输入参数  : pucSrc - 输入的bit流
             usOffsetPos    - 对应在一个字节中的偏移位置
 输出参数  : pastPrlAcqRecord - 输出的捕获记录数据结构
             pulCurOffSetPos - 返回本记录中的bit偏移量
 返 回 值  : VOS_TRUE  -- 解析成功
             VOS_FALSE -- 解析失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParseAcqRec_CellularCdmaStandard(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    VOS_UINT8                          *pucPrlBuff   = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU           *pstAcqRecord = VOS_NULL_PTR;
    VOS_UINT32                          ulSize;
    VOS_UINT32                          ulCurBitOffset;

    VOS_UINT32                          ulAcqRecordLength;
    CNAS_PRL_SSPR_P_REV_ENUM_UINT8      enSsprPRev;

    ulAcqRecordLength  = 0;
    enSsprPRev         = CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.enSsprPRev;

    /*
    PRL格式:
    Type-specific Record    Length (bits)
    A_B                           2
    PRI_SEC                       2

    EPRL格式:
    Type-specific Record          Length (bits)
    LENGTH                        8
    A_B                           2
    PRI_SEC                       2
    RESERVED                      4
    */

    /* 申请内存 */
    ulSize       = sizeof(CNAS_PRL_ACQ_RECORD_STRU);
    pstAcqRecord = (CNAS_PRL_ACQ_RECORD_STRU *)CNAS_PRL_Malloc(ulSize);

    if (VOS_NULL_PTR == pstAcqRecord)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseAcqRec_CellularCdmaStandard: mem alloc fail");

        return VOS_FALSE;
    }

    *pstPrlAcqRecord = pstAcqRecord;

    /* 设置当前字节中的bit偏移 */
    ulCurBitOffset = ulOffsetPos;

    /* 设置当前数据指针 */
    pucPrlBuff = pucSrc;

    /* 设置捕获记录类型 */
    pstAcqRecord->enAcqType = CNAS_PRL_ACQ_TYPE_CELLULAR_CDMA_STANDARD_CHANNELS;

    if (CNAS_PRL_SSPR_P_REV_3 == enSsprPRev)
    {
        /* 获取捕获记录长度*/
        ulAcqRecordLength = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);
        /* 跳过length域 */
        ulCurBitOffset += CNAS_PRL_BIT_LEN_8_BIT;
    }

    /* 解析 A_B field */
    pstAcqRecord->u.stCellularStandardSys.enSysSelType =
        (CNAS_PRL_SYS_SEL_TYPE_ENUM_UINT8)CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_2_BIT);
    ulCurBitOffset += CNAS_PRL_BIT_LEN_2_BIT;

    /* 解析 PRI_SEC field */
    pstAcqRecord->u.stCellularStandardSys.enChanSelType =
        (CNAS_PRL_STANDARD_CHAN_SEL_TYPE_ENUM_UINT8)CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_2_BIT);
    ulCurBitOffset += CNAS_PRL_BIT_LEN_2_BIT;


    /* 置Acq_valid */
    if ((CNAS_PRL_SYS_SEL_TYPE_RESERVED           == pstAcqRecord->u.stCellularStandardSys.enSysSelType)
     || (CNAS_PRL_STANDARD_CHAN_SEL_TYPE_RESERVED == pstAcqRecord->u.stCellularStandardSys.enChanSelType))
    {
        CNAS_ERROR_LOG2(UEPS_PID_XSD,
                        "CNAS_PRL_ParseAcqRec_CellularCdmaStandard: illegal parameter, enSysSelType = %d, enChanSelType = %d",
                        pstAcqRecord->u.stCellularStandardSys.enSysSelType,
                        pstAcqRecord->u.stCellularStandardSys.enChanSelType);

        pstAcqRecord->ucAcqValid = VOS_FALSE;
    }
    else
    {
        pstAcqRecord->ucAcqValid = VOS_TRUE;
    }


    /* 返回本记录中的bit偏移 */
    if (CNAS_PRL_SSPR_P_REV_3 == enSsprPRev)
    {
        *pulCurOffsetPos = ulOffsetPos + CNAS_PRL_BIT_LEN_8_BIT + ulAcqRecordLength * CNAS_PRL_BIT_LEN_8_BIT;
    }
    else
    {
        *pulCurOffsetPos = ulCurBitOffset;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_PRL_ParseAcqRec_CellularCdmaCustom
 功能描述  : 解析一条acquisition record记录,,Acquisition Record Type类型为
             Cellular CDMA (Custom Channels)
 输入参数  : pucSrc - 输入的bit流
             usOffsetPos - 对应在一个字节中的偏移位置
 输出参数  : pstPrlAcqRecord - 输出的捕获记录数据结构
             pulCurOffSetPos - 返回本记录中的bit偏移量
 返 回 值  : VOS_TRUE：解析成功； VOS_FALSE：解析失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParseAcqRec_CellularCdmaCustom(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    VOS_UINT8                          *pucPrlBuff   = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU           *pstAcqRecord = VOS_NULL_PTR;
    VOS_UINT32                          ulSize;
    VOS_UINT8                           ucNumChans;
    VOS_UINT32                          ulCurBitOffset;
    VOS_UINT8                           i;

    VOS_UINT32                          ulAcqRecordLength;
    CNAS_PRL_SSPR_P_REV_ENUM_UINT8      enSsprPRev;

    ulAcqRecordLength  = 0;
    enSsprPRev         = CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.enSsprPRev;

    /*
    PRL格式:
    Type-specific Record    Length (bits)
    NUM_CHANS               5
    NUM_CHANS occurrences of the following field:
    CHAN                   11

    EPRL格式:
    Type-specific Record    Length (bits)
    LENGTH                  8
    NUM_CHANS               5
    NUM_CHANS occurrences of the following field:
    CHAN                    11
    RESERVED                0 to 7
    */

    /* 设置当前数据指针 */
    pucPrlBuff  = pucSrc;

    /* 设置当前字节中的bit偏移 */
    ulCurBitOffset = ulOffsetPos;



    if (CNAS_PRL_SSPR_P_REV_3 == enSsprPRev)
    {
        /* 获取捕获记录长度*/
        ulAcqRecordLength = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);

        /* 跳过length域 */
        ulCurBitOffset += CNAS_PRL_BIT_LEN_8_BIT;
    }

    /* 解析NUM_CHANS */
    ucNumChans = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_5_BIT);
    ulCurBitOffset += CNAS_PRL_BIT_LEN_5_BIT;

    /* 申请内存 */
    ulSize       = ucNumChans * sizeof(VOS_UINT16) + sizeof(CNAS_PRL_ACQ_RECORD_STRU);
    pstAcqRecord = (CNAS_PRL_ACQ_RECORD_STRU *)CNAS_PRL_Malloc(ulSize);

    if (VOS_NULL_PTR == pstAcqRecord)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseAcqRec_CellularCdmaCustom: mem alloc fail");

        return VOS_FALSE;
    }

    *pstPrlAcqRecord = pstAcqRecord;

    /* 设置捕获记录类型 */
    pstAcqRecord->enAcqType = CNAS_PRL_ACQ_TYPE_CELLULAR_CDMA_CUSTOM_CHANNELS;

    /* 根据NUM_CHANS，走for循环，解析CHAN */
    pstAcqRecord->u.stCelluarCustomSys.ucNumOfChans = ucNumChans;

    /* 解析 CHAN field */
    for (i = 0; i < ucNumChans; i++)
    {
        pstAcqRecord->u.stCelluarCustomSys.ausChan[i] =
            CNAS_PRL_BIT_TO_WORD(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_11_BIT);

        ulCurBitOffset += CNAS_PRL_BIT_LEN_11_BIT;
    }

    /* 置Acq_valid */
    pstAcqRecord->ucAcqValid = VOS_TRUE;

    /* 返回本记录中的bit偏移 */
    if (CNAS_PRL_SSPR_P_REV_3 == enSsprPRev)
    {
        *pulCurOffsetPos = ulOffsetPos + CNAS_PRL_BIT_LEN_8_BIT + ulAcqRecordLength * CNAS_PRL_BIT_LEN_8_BIT;
    }
    else
    {
        *pulCurOffsetPos = ulCurBitOffset;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_PRL_ParseAcqRec_CellularCdmaPrefered
 功能描述  : 解析一条acquisition record记录,,Acquisition Record Type类型为
             Cellular CDMA Preferred
 输入参数  : pucSrc - 输入的bit流
             ulOffsetPos - 对应在一个字节中的偏移位置
 输出参数  : pstPrlAcqRecord - 输出的捕获记录数据结构
             pulCurOffSetPos - 返回本记录中的bit偏移量
 返 回 值  : VOS_TRUE：解析成功； VOS_FALSE：解析失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParseAcqRec_CellularCdmaPrefered(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    VOS_UINT8                          *pucPrlBuff   = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU           *pstAcqRecord = VOS_NULL_PTR;
    VOS_UINT32                          ulSize;
    VOS_UINT32                          ulCurBitOffset;

    VOS_UINT32                          ulAcqRecordLength;
    CNAS_PRL_SSPR_P_REV_ENUM_UINT8      enSsprPRev;

    ulAcqRecordLength  = 0;
    enSsprPRev         = CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.enSsprPRev;

    /*
    PRL格式:
    Type-specific Record        Length (bits)
    A_B                         2

    EPRL格式:
    Type-specific Record        Length (bits)
    LENGTH                      8
    A_B                         2
    RESERVED                    6
    */

    /* 申请内存 */
    ulSize       = sizeof(CNAS_PRL_ACQ_RECORD_STRU);
    pstAcqRecord = (CNAS_PRL_ACQ_RECORD_STRU *)CNAS_PRL_Malloc(ulSize);

    if (VOS_NULL_PTR == pstAcqRecord)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseAcqRec_CellularCdmaPrefered: mem alloc fail");

        return VOS_FALSE;
    }

    *pstPrlAcqRecord = pstAcqRecord;

    /* 设置当前数据指针 */
    pucPrlBuff     = pucSrc;

    /* 设置当前字节中的bit偏移 */
    ulCurBitOffset = ulOffsetPos;

    /* 设置捕获记录类型 */
    pstAcqRecord->enAcqType = CNAS_PRL_ACQ_TYPE_CELLULAR_CDMA_PREFERRED;

    if (CNAS_PRL_SSPR_P_REV_3 == enSsprPRev)
    {
        /* 获取捕获记录长度*/
        ulAcqRecordLength = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);

        /* 跳过length域 */
        ulCurBitOffset += CNAS_PRL_BIT_LEN_8_BIT;
    }

    /*解析 A_B field*/
    pstAcqRecord->u.stCellularPreSys.enSysSelType =
        (CNAS_PRL_SYS_SEL_TYPE_ENUM_UINT8)CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_2_BIT);

    ulCurBitOffset += CNAS_PRL_BIT_LEN_2_BIT;

    /* 置Acq_valid */
    if (CNAS_PRL_SYS_SEL_TYPE_RESERVED == pstAcqRecord->u.stCellularPreSys.enSysSelType)
    {
        CNAS_ERROR_LOG1(UEPS_PID_XSD,
                        "CNAS_PRL_ParseAcqRec_CellularCdmaPrefered: illegal parameter enSysSelType = %d",
                        pstAcqRecord->u.stCellularStandardSys.enSysSelType);

        pstAcqRecord->ucAcqValid = VOS_FALSE;
    }
    else
    {
        pstAcqRecord->ucAcqValid = VOS_TRUE;
    }

    /* 返回本记录中的bit偏移 */
    if (CNAS_PRL_SSPR_P_REV_3 == enSsprPRev)
    {
        *pulCurOffsetPos = ulOffsetPos + CNAS_PRL_BIT_LEN_8_BIT + ulAcqRecordLength * CNAS_PRL_BIT_LEN_8_BIT;
    }
    else
    {
        *pulCurOffsetPos = ulCurBitOffset;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_PRL_ParseAcqRec_PcsCdmaUsingBlocks
 功能描述  : 解析一条acquisition record记录,,Acquisition Record Type类型为
             PCS CDMA (Using Blocks)

 输入参数  : pucSrc - 输入的bit流
             usOffsetPos    - 对应在一个字节中的偏移位置

 输出参数  : pstPrlAcqRecord - 输出的捕获记录数据结构
             pulCurOffSetPos - 返回本记录中的bit偏移量

 返 回 值  : VOS_TRUE：解析成功； VOS_FALSE：解析失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParseAcqRec_PcsCdmaUsingBlocks(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    /*
    C.S0016-D
    3.5.5.2.2.5 PCS CDMA System Acquisition (Using Blocks) Record

    Type-specific Record        Length (bits)
    NUM_BLOCKS                  3
    NUM_BLOCKS occurrences of the following field:
    BLOCK                       3
    RESERVED                    0 to 7
    */

    VOS_UINT8                          *pucPrlBuff   = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU           *pstAcqRecord = VOS_NULL_PTR;
    VOS_UINT32                          ulSize;
    VOS_UINT8                           ucNumBlock;
    VOS_UINT32                          ulCurBitOffset;
    VOS_UINT8                           i;

    VOS_UINT32                          ulAcqRecordLength;
    CNAS_PRL_SSPR_P_REV_ENUM_UINT8      enSsprPRev;

    ulAcqRecordLength  = 0;
    enSsprPRev         = CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.enSsprPRev;

    /* 设置当前数据指针 */
    pucPrlBuff     = pucSrc;

    /* 设置当前字节中的bit偏移 */
    ulCurBitOffset = ulOffsetPos;

    /* 跳过 LENGTH field */
    if (CNAS_PRL_SSPR_P_REV_3 == enSsprPRev)
    {
        /* 获取捕获记录长度*/
        ulAcqRecordLength = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);

        ulCurBitOffset += CNAS_PRL_BIT_LEN_8_BIT;
    }

    /* 解析 NUM_BLOCKS field */
    ucNumBlock      = CNAS_PRL_BIT_TO_BYTE(pucSrc, ulCurBitOffset, CNAS_PRL_BIT_LEN_3_BIT);
    ulCurBitOffset += CNAS_PRL_BIT_LEN_3_BIT;

    /* 申请内存 */
    ulSize          = ucNumBlock * sizeof(VOS_UINT8) + sizeof(CNAS_PRL_ACQ_RECORD_STRU);
    pstAcqRecord    = (CNAS_PRL_ACQ_RECORD_STRU *)CNAS_PRL_Malloc(ulSize);

    if (VOS_NULL_PTR == pstAcqRecord)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseAcqRec_PcsCdmaUsingBlocks: mem alloc fail");

        return VOS_FALSE;
    }

    *pstPrlAcqRecord = pstAcqRecord;

    /* 设置捕获记录类型 */
    pstAcqRecord->enAcqType = CNAS_PRL_ACQ_TYPE_PCS_CDMA_USING_BLOCKS;

    /* 根据NUM_BLOCKS，走for循环，解析BLOCK */
    pstAcqRecord->u.stPcsBlocksSys.ucNumOfBlocks  = ucNumBlock;

    /* 解析 CHAN field */
    for (i = 0; i < ucNumBlock; i++)
    {
        pstAcqRecord->u.stPcsBlocksSys.aenBlock[i] =
            CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_3_BIT);

        ulCurBitOffset += CNAS_PRL_BIT_LEN_3_BIT;
    }

    /* 置Acq_valid */
    if (0 == pstAcqRecord->u.stPcsBlocksSys.ucNumOfBlocks)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseAcqRec_PcsCdmaUsingBlocks: ucNumOfBlocks = 0");

        pstAcqRecord->ucAcqValid = VOS_FALSE;
    }
    else
    {
        /* 置Acq_valid */
        pstAcqRecord->ucAcqValid = VOS_TRUE;
    }

    /* 返回当前bit偏移 */
    *pulCurOffsetPos = ulCurBitOffset;

    /* 返回本记录中的bit偏移 */
    if (CNAS_PRL_SSPR_P_REV_3 == enSsprPRev)
    {
        *pulCurOffsetPos = ulOffsetPos + CNAS_PRL_BIT_LEN_8_BIT + ulAcqRecordLength * CNAS_PRL_BIT_LEN_8_BIT;
    }
    else
    {
        *pulCurOffsetPos = ulCurBitOffset;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_PRL_ParseAcqRec_PcsCdmaUsingChannels
 功能描述  : 解析一条acquisition record记录,,Acquisition Record Type类型为
             PCS CDMA (Using Channels)

 输入参数  : pucSrc - 输入的bit流
             usOffsetPos    - 对应在一个字节中的偏移位置

 输出参数  : pstPrlAcqRecord - 输出的捕获记录数据结构
             pulCurOffSetPos - 返回本记录中的bit偏移量

 返 回 值  : VOS_TRUE：解析成功； VOS_FALSE：解析失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParseAcqRec_PcsCdmaUsingChannels(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    /*
    C.S0016-D
    3.5.5.2.2.6 PCS CDMA System Acquisition (Using Channels) Record

    Type-specific Record        Length (bits)
    NUM_CHANS                   5
    NUM_CHANS occurrences of the following field:
    CHAN                        11
    RESERVED                    0 to 7
    */

    VOS_UINT8                          *pucPrlBuff   = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU           *pstAcqRecord = VOS_NULL_PTR;
    VOS_UINT32                          ulSize;
    VOS_UINT8                           ucNumChan;
    VOS_UINT32                          ulCurBitOffset;
    VOS_UINT8                           i;

    VOS_UINT32                          ulAcqRecordLength;
    CNAS_PRL_SSPR_P_REV_ENUM_UINT8      enSsprPRev;

    ulAcqRecordLength  = 0;
    enSsprPRev         = CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.enSsprPRev;

    pucPrlBuff      = pucSrc;

    ulCurBitOffset  = ulOffsetPos;

    /* 跳过 LENGTH field */
    if (CNAS_PRL_SSPR_P_REV_3 == enSsprPRev)
    {
        /* 获取捕获记录长度*/
        ulAcqRecordLength = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);

        ulCurBitOffset  += CNAS_PRL_BIT_LEN_8_BIT;
    }

    /* 解析 NUM_BLOCKS field */
    ucNumChan       = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_5_BIT);
    ulCurBitOffset += CNAS_PRL_BIT_LEN_5_BIT;

    /* 申请内存 */
    ulSize          = ucNumChan * sizeof(VOS_UINT16) + sizeof(CNAS_PRL_ACQ_RECORD_STRU);
    pstAcqRecord    = (CNAS_PRL_ACQ_RECORD_STRU *)CNAS_PRL_Malloc(ulSize);

    if (VOS_NULL_PTR == pstAcqRecord)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseAcqRec_PcsCdmaUsingChannels: mem alloc fail");

        return VOS_FALSE;
    }

    *pstPrlAcqRecord = pstAcqRecord;

    /* 设置捕获记录类型 */
    pstAcqRecord->enAcqType = CNAS_PRL_ACQ_TYPE_PCS_CDMA_USING_CHANNELS;

    /* 根据NUM_BLOCKS，走for循环，解析BLOCK */
    pstAcqRecord->u.stPcsChannelsSys.ucNumOfChans   = ucNumChan;

    /* 解析 CHAN field */
    for (i = 0; i < ucNumChan; i++)
    {
        pstAcqRecord->u.stPcsChannelsSys.ausChan[i] =
            CNAS_PRL_BIT_TO_WORD(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_11_BIT);

        ulCurBitOffset += CNAS_PRL_BIT_LEN_11_BIT;
    }

    /* 置Acq_valid */
    pstAcqRecord->ucAcqValid = VOS_TRUE;

    /* 返回本记录中的bit偏移 */
    if (CNAS_PRL_SSPR_P_REV_3 == enSsprPRev)
    {
        *pulCurOffsetPos = ulOffsetPos + CNAS_PRL_BIT_LEN_8_BIT + ulAcqRecordLength * CNAS_PRL_BIT_LEN_8_BIT;
    }
    else
    {
        *pulCurOffsetPos = ulCurBitOffset;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_PRL_ParseAcqRec_GenericCdma1X
 功能描述  : 解析一条acquisition record记录,,Acquisition Record Type类型为
             Generic Acquisition Record for cdma2000 1x and IS-95

 输入参数  : pucSrc - 输入的bit流
             usOffsetPos    - 对应在一个字节中的偏移位

 输出参数  : pstPrlAcqRecord - 输出的捕获记录数据结构
             pulCurOffSetPos - 返回本记录中的bit偏移量

 返 回 值  : VOS_TRUE：解析成功； VOS_FALSE：解析失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParseAcqRec_GenericCdma1X(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    /*
    EPRL格式(该record仅用于EPRL):
    Type-specific Record            Length (bits)
    LENGTH/2 occurrences of the following two fields:
    BAND_CLASS                      5
    CHANNEL_NUMBER                  11
    */
    VOS_UINT8                          *pucPrlBuff   = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU           *pstAcqRecord = VOS_NULL_PTR;
    VOS_UINT32                          ulCurBitOffset;
    VOS_UINT8                           ucLen;
    VOS_UINT16                          usSize;
    VOS_UINT8                           i;

    /* 设置当前字节中的bit偏移 */
    ulCurBitOffset = ulOffsetPos;

    /* 设置当前数据指针 */
    pucPrlBuff     = pucSrc;

    ucLen = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);
    ulCurBitOffset += CNAS_PRL_BIT_LEN_8_BIT;

    /* 计算record内存空间, 申请内存 */
    usSize = ((ucLen/2) * sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU)) + sizeof(CNAS_PRL_ACQ_RECORD_STRU);

    pstAcqRecord = (CNAS_PRL_ACQ_RECORD_STRU *)CNAS_PRL_Malloc(usSize);

    if (VOS_NULL_PTR == pstAcqRecord)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseAcqRec_GenericCdma1X: mem alloc fail");

        return VOS_FALSE;
    }

    *pstPrlAcqRecord = pstAcqRecord;

    /* 设置捕获记录类型 */
    pstAcqRecord->enAcqType = CNAS_PRL_ACQ_TYPE_GENERIC_ACQ_RECORD_FOR_1X_AND_IS95;

    pstAcqRecord->u.st1xAndIs95Sys.ucNumOfChans = ucLen/2;

    for (i = 0; i < (ucLen/2); i++)
    {
        /* 解析 BAND_CLASS field */
        pstAcqRecord->u.st1xAndIs95Sys.astFreq[i].enBandClass =
            (CNAS_PRL_BAND_CLASS_ENUM_UINT16)CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_5_BIT);
        ulCurBitOffset += CNAS_PRL_BIT_LEN_5_BIT;

        /* 解析 CHANNEL_NUMBER */
        pstAcqRecord->u.st1xAndIs95Sys.astFreq[i].usChannel =
            CNAS_PRL_BIT_TO_WORD(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_11_BIT);
        ulCurBitOffset += CNAS_PRL_BIT_LEN_11_BIT;
    }

    pstAcqRecord->ucAcqValid = VOS_TRUE;

    *pulCurOffsetPos = ulOffsetPos + CNAS_PRL_BIT_LEN_8_BIT + ucLen * CNAS_PRL_BIT_LEN_8_BIT;

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_PRL_ParseAcqRec_CellularAnalog
 功能描述  : 解析一条acquisition record记录,Acquisition Record Type类型为cellular
             analog record type
 输入参数  : pucSrc - 输入的bit流
             usOffsetPos    - 对应在一个字节中的偏移位置

 输出参数  : pstPrlAcqRecord - 输出的捕获记录数据结构
             pulCurOffSetPos - 返回本记录中的bit偏移量

 返 回 值  : VOS_TRUE：解析成功； VOS_FALSE：解析失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParseAcqRec_CellularAnalog(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    /*
      PRL格式:
      A_B                               2

      EPRL格式:
      Type-specific Record            Length (bits)
      LENGTH                            8
      A_B                               2
      RESERVED                          6
    */

    /* cellular analog类型不支持，但这里仍然需要为它分配空间并计算该record bit偏移 */
    CNAS_PRL_ACQ_RECORD_STRU           *pstAcqRecord = VOS_NULL_PTR;
    VOS_UINT32                          ulCurBitOffset;

    VOS_UINT32                          ulAcqRecordLength;
    VOS_UINT8                          *pucPrlBuff   = VOS_NULL_PTR;

    pucPrlBuff         = pucSrc;
    ulAcqRecordLength  = 0;

    pstAcqRecord = (CNAS_PRL_ACQ_RECORD_STRU *)CNAS_PRL_Malloc(sizeof(CNAS_PRL_ACQ_RECORD_STRU));

    if (VOS_NULL_PTR == pstAcqRecord)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseAcqRec_CellularAnalog: mem alloc fail");

        return VOS_FALSE;
    }

    *pstPrlAcqRecord = pstAcqRecord;

    ulCurBitOffset = ulOffsetPos;

    /* 计算该record bit偏移 */
    if (CNAS_PRL_SSPR_P_REV_3 == CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.enSsprPRev)
    {
        /* 获取捕获记录长度*/
        ulAcqRecordLength = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);

        ulCurBitOffset += (CNAS_PRL_BIT_LEN_8_BIT + ulAcqRecordLength * CNAS_PRL_BIT_LEN_8_BIT);
    }
    else
    {
        ulCurBitOffset += CNAS_PRL_BIT_LEN_2_BIT;
    }

    /* 设置捕获记录类型 */
    pstAcqRecord->enAcqType  = CNAS_PRL_ACQ_TYPE_CELLULAR_ANALOG;

    /* 置该记录为无效 */
    pstAcqRecord->ucAcqValid = VOS_FALSE;

    *pulCurOffsetPos = ulCurBitOffset;

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_PRL_ParseAcqRec_JtacsCdmaStandardChannels
 功能描述  : 解析一条acquisition record记录,Acquisition Record Type类型JTACS
             CDMA standard channels
 输入参数  : pucSrc - 输入的bit流
             usOffsetPos    - 对应在一个字节中的偏移位置

 输出参数  : pstPrlAcqRecord - 输出的捕获记录数据结构
             pulCurOffSetPos - 返回本记录中的bit偏移量

 返 回 值  : VOS_TRUE：解析成功； VOS_FALSE：解析失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParseAcqRec_JtacsCdmaStandardChannels(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    /*
      PRL格式:
      A_B                               2
      PRI_SEC                           2

      EPRL格式:
      Type-specific Record            Length (bits)
      LENGTH                            8
      A_B                               2
      PRI_SEC                           2
      RESERVED                          4
    */

    /* JTACS CDMA standard channels类型不支持，但这里仍然需要为它分配空间并计算该record bit偏移 */
    CNAS_PRL_ACQ_RECORD_STRU           *pstAcqRecord = VOS_NULL_PTR;
    VOS_UINT32                          ulCurBitOffset;

    VOS_UINT32                          ulAcqRecordLength;
    VOS_UINT8                          *pucPrlBuff   = VOS_NULL_PTR;

    pucPrlBuff         = pucSrc;
    ulAcqRecordLength  = 0;

    pstAcqRecord = (CNAS_PRL_ACQ_RECORD_STRU *)CNAS_PRL_Malloc(sizeof(CNAS_PRL_ACQ_RECORD_STRU));

    if (VOS_NULL_PTR == pstAcqRecord)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseAcqRec_JtacsCdmaStandardChannels: mem alloc fail");

        return VOS_FALSE;
    }

    *pstPrlAcqRecord = pstAcqRecord;

    ulCurBitOffset = ulOffsetPos;

    /* 计算该record bit偏移 */
    if (CNAS_PRL_SSPR_P_REV_3 == CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.enSsprPRev)
    {
        /* 获取捕获记录长度*/
        ulAcqRecordLength = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);

        ulCurBitOffset += (CNAS_PRL_BIT_LEN_8_BIT + ulAcqRecordLength * CNAS_PRL_BIT_LEN_8_BIT);

    }
    else
    {
        ulCurBitOffset += CNAS_PRL_BIT_LEN_2_BIT * 2;
    }

    /* 设置捕获记录类型 */
    pstAcqRecord->enAcqType  = CNAS_PRL_ACQ_TYPE_JTACS_CDMA_STANDARD_CHANNELS;

    /* 置该记录为无效 */
    pstAcqRecord->ucAcqValid = VOS_FALSE;

    *pulCurOffsetPos = ulCurBitOffset;

    return VOS_TRUE;


}

/*****************************************************************************
 函 数 名  : CNAS_PRL_ParseAcqRec_JtacsCdmaCustomChannels
 功能描述  : 解析一条acquisition record记录,Acquisition Record Type类型JTACS
             CDMA custom channels
 输入参数  : pucSrc - 输入的bit流
             usOffsetPos    - 对应在一个字节中的偏移位置

 输出参数  : pstPrlAcqRecord - 输出的捕获记录数据结构
             pulCurOffSetPos - 返回本记录中的bit偏移量

 返 回 值  : VOS_TRUE：解析成功； VOS_FALSE：解析失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParseAcqRec_JtacsCdmaCustomChannels(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    /*
     PRL格式:
     NUM_CHANS                          5
     NUM_CHANS occurrences of the following field:
     CHAN                               11

     EPRL格式:
     LENGTH                             8
     Type-specific Record            Length (bits)
     NUM_CHANS                          5
     NUM_CHANS occurrences of the following field:
     CHAN                               11
     RESERVED                           0 to 7
     */

    /* JTACS CDMA Custom channels类型不支持，但这里仍然需要为它分配空间并计算该record bit偏移 */
    VOS_UINT8                          *pucPrlBuff   = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU           *pstAcqRecord = VOS_NULL_PTR;
    VOS_UINT32                          ulCurBitOffset;
    VOS_UINT8                           ucNumChans;
    VOS_UINT8                           ucLength;

    pucPrlBuff      = pucSrc;

    ulCurBitOffset  = ulOffsetPos;

    pstAcqRecord = (CNAS_PRL_ACQ_RECORD_STRU *)CNAS_PRL_Malloc(sizeof(CNAS_PRL_ACQ_RECORD_STRU));

    if (VOS_NULL_PTR == pstAcqRecord)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseAcqRec_JtacsCdmaCustomChannels: mem alloc fail");

        return VOS_FALSE;
    }

    *pstPrlAcqRecord = pstAcqRecord;

    if (CNAS_PRL_SSPR_P_REV_3 == CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.enSsprPRev)
    {
        ucLength = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);

        ulCurBitOffset += CNAS_PRL_BIT_LEN_8_BIT + (ucLength * CNAS_PRL_BIT_LEN_8_BIT);
    }
    else
    {
        /* 获取PRL格式中NUM_CHANS数目 */
        ucNumChans = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_5_BIT);

        ulCurBitOffset += CNAS_PRL_BIT_LEN_5_BIT + (ucNumChans * CNAS_PRL_BIT_LEN_11_BIT);
    }

    /* 设置捕获记录类型 */
    pstAcqRecord->enAcqType  = CNAS_PRL_ACQ_TYPE_JTACS_CDMA_CUSTOM_CHANNELS;

    /* 置该记录为无效 */
    pstAcqRecord->ucAcqValid = VOS_FALSE;

    *pulCurOffsetPos = ulCurBitOffset;

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_PRL_ParseAcqRec_2gBandUsingChannels
 功能描述  : 解析一条acquisition record记录,Acquisition Record Type类型2G BAND
             USING CHANNELS
 输入参数  : pucSrc - 输入的bit流
             usOffsetPos    - 对应在一个字节中的偏移位置

 输出参数  : pstPrlAcqRecord - 输出的捕获记录数据结构
             pulCurOffSetPos - 返回本记录中的bit偏移量

 返 回 值  : VOS_TRUE：解析成功； VOS_FALSE：解析失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParseAcqRec_2gBandUsingChannels(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    /*
     PRL格式:
     NUM_CHANS                          5
     NUM_CHANS occurrences of the following field:
     CHAN                               11

     EPRL格式:
     LENGTH                             8
     NUM_CHANS                          5
     NUM_CHANS occurrences of the following field:
     CHAN                               11
     RESERVED                           0 to 7
     */

    /* JTACS CDMA Custom channels类型不支持，这里仅为它分配空间并不解析具体内容 */
    VOS_UINT8                          *pucPrlBuff   = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU           *pstAcqRecord = VOS_NULL_PTR;
    VOS_UINT32                          ulCurBitOffset;
    VOS_UINT8                           ucNumChans;
    VOS_UINT8                           ucLength;

    pstAcqRecord = (CNAS_PRL_ACQ_RECORD_STRU *)CNAS_PRL_Malloc(sizeof(CNAS_PRL_ACQ_RECORD_STRU));

    if (VOS_NULL_PTR == pstAcqRecord)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseAcqRec_2gBandUsingChannels: mem alloc fail");

        return VOS_FALSE;
    }

    *pstPrlAcqRecord = pstAcqRecord;

    pucPrlBuff      = pucSrc;

    ulCurBitOffset  = ulOffsetPos;

    if (CNAS_PRL_SSPR_P_REV_3 == CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.enSsprPRev)
    {
        ucLength = CNAS_PRL_BIT_TO_BYTE(pucSrc, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);

        ulCurBitOffset += CNAS_PRL_BIT_LEN_8_BIT + (ucLength * CNAS_PRL_BIT_LEN_8_BIT);
    }
    else
    {
        /* 获取PRL格式中NUM_CHANS数目 */
        ucNumChans = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_5_BIT);

        ulCurBitOffset += CNAS_PRL_BIT_LEN_5_BIT + (ucNumChans * CNAS_PRL_BIT_LEN_11_BIT);
    }

    /* 设置捕获记录类型 */
    pstAcqRecord->enAcqType  = CNAS_PRL_ACQ_TYPE_2G_BAND_USING_CHANNELS;

    /* 置该记录为无效 */
    pstAcqRecord->ucAcqValid = VOS_FALSE;

    *pulCurOffsetPos = ulCurBitOffset;

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : CNAS_PRL_ParseAcqRec_GenericAcqRecordForHrpd
 功能描述  : 解析一条acquisition record记录,Acquisition Record Type类型Generic
             acquisition record for HRPD

 输入参数  : pucSrc - 输入的bit流
             usOffsetPos    - 对应在一个字节中的偏移位置

 输出参数  : pstPrlAcqRecord - 输出的捕获记录数据结构
             pulCurOffSetPos - 返回本记录中的bit偏移量

 返 回 值  : VOS_TRUE：解析成功； VOS_FALSE：解析失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : h00246512
    修改内容   : 新生成函数
  2.日    期   : 2014年12月6日
    作    者   : d00212987
    修改内容   : EVDO HSD Phase0

*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParseAcqRec_GenericAcqRecordForHrpd(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    /*
     EPRL格式:
     LENGTH                             8
     Type-specific                      8*LENGTH
     --------------------------------------------------------------------
     LENGTH                             8
     LENGTH/2                           occurrences of the following two fields:
     BAND_CLASS                         5
     CHANNEL_NUMBER                     11
     */

    /* Generic acquisition record for HRPD类型只支持EPRL */
    VOS_UINT8                          *pucPrlBuff   = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU           *pstAcqRecord = VOS_NULL_PTR;
    VOS_UINT32                          ulCurBitOffset;
    VOS_UINT8                           ucLength;
    VOS_UINT32                          ulSize;
    VOS_UINT8                           i;

    pucPrlBuff      = pucSrc;

    ulCurBitOffset  = ulOffsetPos;

    /* 跳过 LENGTH field */
    if (CNAS_PRL_SSPR_P_REV_3 != CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.enSsprPRev)
    {
        /* 不支持PRL */
        return VOS_FALSE;
    }

    ucLength = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);

    /* 计算Hrpd解析后所占内存 结构体大小 + Freq 出现次数 */
    ulSize       = sizeof(CNAS_PRL_ACQ_RECORD_STRU) + ((ucLength / 2) * sizeof(VOS_UINT32));

    pstAcqRecord = (CNAS_PRL_ACQ_RECORD_STRU *)CNAS_PRL_Malloc(ulSize);

    if (VOS_NULL_PTR == pstAcqRecord)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseAcqRec_GenericAcqRecordForHrpd: mem alloc fail");

        return VOS_FALSE;
    }

    *pstPrlAcqRecord = pstAcqRecord;

    /* 设置捕获记录类型 */
    pstAcqRecord->enAcqType  = CNAS_PRL_ACQ_TYPE_GENERIC_ACQ_RECORD_FOR_HRPD;

    pstAcqRecord->u.stHrpdSys.ucNumOfChans = (ucLength/2);
    ulCurBitOffset  += CNAS_PRL_BIT_LEN_8_BIT;

    /* 解析 CHAN field */
    for (i = 0; i < pstAcqRecord->u.stHrpdSys.ucNumOfChans; i++)
    {
        /* 频段 */
        pstAcqRecord->u.stHrpdSys.astFreq[i].enBandClass =
            CNAS_PRL_BIT_TO_WORD(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_5_BIT);

        ulCurBitOffset += CNAS_PRL_BIT_LEN_5_BIT;

        /* 频点 */
        pstAcqRecord->u.stHrpdSys.astFreq[i].usChannel   =
            CNAS_PRL_BIT_TO_WORD(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_11_BIT);

        ulCurBitOffset += CNAS_PRL_BIT_LEN_11_BIT;
    }

    /* 置Acq_valid */
    pstAcqRecord->ucAcqValid = VOS_TRUE;

    *pulCurOffsetPos = ulOffsetPos + CNAS_PRL_BIT_LEN_8_BIT + ucLength * CNAS_PRL_BIT_LEN_8_BIT;

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_PRL_ParseAcqRec_ComAcqTabRecordForUmb
 功能描述  : 解析一条acquisition record记录,Acquisition Record Type类型Common
             Acquisition Table Record for UMB

 输入参数  : pucSrc - 输入的bit流
             usOffsetPos    - 对应在一个字节中的偏移位置

 输出参数  : pstPrlAcqRecord - 输出的捕获记录数据结构
             pulCurOffSetPos - 返回本记录中的bit偏移量
 返 回 值  : VOS_TRUE：解析成功； VOS_FALSE：解析失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParseAcqRec_ComAcqTabRecordForUmb(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    /*
       EPRL格式:
       LENGTH                           8
       Type-specific                    8*LENGTH
       --------------------------------------------------------------------
       LENGTH                           8
       LENGTH/2                         occurrences of the following fields:
       UMB_ACQ_PROFILE                  6
       FFT_SIZE                         4
       CYCLIC_PREFIX_LENGTH             3
       NUM_GUARD_SUBCARRIERS            7
       RESERVED                         0 to 7
    */

    /* Common Acquisition Table Record for UMB类型不支持，这里仅为它分配空间并计算该record bit偏移 */
    VOS_UINT8                          *pucPrlBuff   = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU           *pstAcqRecord = VOS_NULL_PTR;
    VOS_UINT32                          ulCurBitOffset;
    VOS_UINT8                           ucLength;

    pstAcqRecord = (CNAS_PRL_ACQ_RECORD_STRU *)CNAS_PRL_Malloc(sizeof(CNAS_PRL_ACQ_RECORD_STRU));

    if (VOS_NULL_PTR == pstAcqRecord)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseAcqRec_ComAcqTabRecordForUmb: mem alloc fail");

        return VOS_FALSE;
    }

    *pstPrlAcqRecord = pstAcqRecord;

    pucPrlBuff       = pucSrc;

    ulCurBitOffset   = ulOffsetPos;

    ucLength = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);

    ulCurBitOffset += CNAS_PRL_BIT_LEN_8_BIT + (ucLength * CNAS_PRL_BIT_LEN_8_BIT);

    /* 设置捕获记录类型 */
    pstAcqRecord->enAcqType  = CNAS_PRL_ACQ_TYPE_COMMON_ACQ_TABLE_RECORD_FOR_UMB;

    /* 置该记录为无效 */
    pstAcqRecord->ucAcqValid = VOS_FALSE;

    *pulCurOffsetPos = ulCurBitOffset;

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_PRL_ParseAcqRec_ComAcqRecordForUmb
 功能描述  : 解析一条acquisition record记录,Acquisition Record Type类型Common
             Acquisition Record for UMB

 输入参数  : pucSrc - 输入的bit流
             usOffsetPos    - 对应在一个字节中的偏移位置

 输出参数  : pstPrlAcqRecord - 输出的捕获记录数据结构
             pulCurOffSetPos - 返回本记录中的bit偏移量

 返 回 值  : VOS_TRUE：解析成功； VOS_FALSE：解析失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParseAcqRec_ComAcqRecordForUmb(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    /*
       EPRL格式:
       LENGTH                           8
       Type-specific                    8*LENGTH
       --------------------------------------------------------------------
       NUM_UMB_BLOCKS                   6
       NUM_UMB_BLOCKS                   occurrences of the following fields:
       BAND_CLASS                       8
       CHANNEL_NUMBER                   16
       UMB_ACQ_TABLE_PROFILE            6
       RESERVED                         0 to 7
    */

    /* Common Acquisition Record for UMB类型不支持，这里仅为它分配空间并计算该record bit偏移 */
    VOS_UINT8                          *pucPrlBuff   = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU           *pstAcqRecord = VOS_NULL_PTR;
    VOS_UINT32                          ulCurBitOffset;
    VOS_UINT8                           ucLength;

    pstAcqRecord = (CNAS_PRL_ACQ_RECORD_STRU *)CNAS_PRL_Malloc(sizeof(CNAS_PRL_ACQ_RECORD_STRU));

    if (VOS_NULL_PTR == pstAcqRecord)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseAcqRec_ComAcqRecordForUmb: mem alloc fail");

        return VOS_FALSE;
    }

    *pstPrlAcqRecord = pstAcqRecord;

    pucPrlBuff       = pucSrc;

    ulCurBitOffset   = ulOffsetPos;

    ucLength = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);

    ulCurBitOffset += CNAS_PRL_BIT_LEN_8_BIT + (ucLength * CNAS_PRL_BIT_LEN_8_BIT);

    /* 设置捕获记录类型 */
    pstAcqRecord->enAcqType  = CNAS_PRL_ACQ_TYPE_COMMON_ACQ_RECORD_FOR_UMB;

    /* 置该记录为无效 */
    pstAcqRecord->ucAcqValid = VOS_FALSE;

    *pulCurOffsetPos = ulCurBitOffset;

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_PRL_ParseAcqRec_NotSupportRecType
 功能描述  : 解析一条acquisition record记录,Acquisition Record Type类型不支持

 输入参数  : pucSrc         - 输入的bit流
             usOffsetPos    - 对应在一个字节中的偏移位置

 输出参数  : pstPrlAcqRecord - 输出的捕获记录数据结构
             pulCurOffSetPos - 返回本记录中的bit偏移量

 返 回 值  : VOS_TRUE：解析成功； VOS_FALSE：解析失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : h00246512
    修改内容   : 新生成函数

  2.日    期   : 2015年8月14日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParseAcqRec_NotSupportRecType(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    VOS_UINT8                          *pucPrlBuff   = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU           *pstAcqRecord = VOS_NULL_PTR;
    VOS_UINT32                          ulCurBitOffset;
    VOS_UINT8                           ucLen;

    /* 对于REV1，由于不同类型，数据长度没有明确定义，因此这里直接返回失败 */
    if (CNAS_PRL_SSPR_P_REV_1 == CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.enSsprPRev)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseAcqRec_NotSupportRecType: record type is unknown!");

        *pstPrlAcqRecord = VOS_NULL_PTR;

        return VOS_FALSE;
    }

    CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseAcqRec_NotSupportRecType: record type is unknown!");

    pstAcqRecord = (CNAS_PRL_ACQ_RECORD_STRU *)CNAS_PRL_Malloc(sizeof(CNAS_PRL_ACQ_RECORD_STRU));

    if (VOS_NULL_PTR == pstAcqRecord)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseAcqRec_JtacsCdmaStandardChannels: mem alloc fail");

        *pstPrlAcqRecord = VOS_NULL_PTR;

        return VOS_FALSE;
    }

    /*
      EPRL格式:
      LENGTH                           8
      Type-specific                    8*LENGTH
    */

    *pstPrlAcqRecord = pstAcqRecord;

    /* 设置当前字节中的bit偏移 */
    ulCurBitOffset           = ulOffsetPos;

    /* 设置当前数据指针 */
    pucPrlBuff               = pucSrc;

    /* 获取不支持的捕获类型的数据长度 */
    ucLen                    = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);
    ulCurBitOffset          += CNAS_PRL_BIT_LEN_8_BIT + ucLen * CNAS_PRL_BIT_LEN_8_BIT;


    pstAcqRecord->ucAcqValid = VOS_FALSE;

    *pulCurOffsetPos = ulCurBitOffset;

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_PRL_ParseExAcqRecTbl
 功能描述  : 对每一个捕获记录做解析
 输入参数  : enAcqType - 捕获记录类型
             pucSrc    - 输入的原始码流
 输出参数  : pstPrlAcqRecord - 解析后的数据结构
 返 回 值  : VOS_TRUE：解析成功； VOS_FALSE：解析失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : h00246512
    修改内容   : 新生成函数

  2.日    期   : 2015年8月14日
    作    者   : y00245242
    修改内容   : DTS2015030604458
*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParseExAcqRecTbl(
    CNAS_PRL_ACQ_TYPE_ENUM_UINT8        enAcqType,
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    VOS_UINT32                                    i;
    VOS_UINT32                                    ulRslt;
    CNAS_PRL_PARSE_ACQ_TYPE_REC_PROC_FUNC_PTR     pParseAcqTypeRecProcFunc = VOS_NULL_PTR;

    ulRslt = VOS_FALSE;

    /* 根据场景在gastCnasProcParseAcqTypeRec查找搜网列表初始化函数 */
    for (i = 0; i < (sizeof(g_astCnasPrlProcParseAcqTypeRec)/sizeof(CNAS_PARSE_ACQ_TYPE_REC_PROC_ENTITY)); i++)
    {
        if (enAcqType == g_astCnasPrlProcParseAcqTypeRec[i].enAcqType)
        {
            pParseAcqTypeRecProcFunc = g_astCnasPrlProcParseAcqTypeRec[i].pParseAcqTypeRecProcFunc;
            break;
        }
    }

    /* 查找成功时调用初始化函数进行初始化 */
    if (VOS_NULL_PTR != pParseAcqTypeRecProcFunc)
    {
        ulRslt = pParseAcqTypeRecProcFunc(pucSrc, ulOffsetPos, pstPrlAcqRecord, pulCurOffsetPos);
    }
    else
    {
        /* 对不支持的类型做处理 */
        ulRslt = CNAS_PRL_ParseAcqRec_NotSupportRecType(pucSrc, ulOffsetPos, pstPrlAcqRecord, pulCurOffsetPos);
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : CNAS_PRL_AddCTCCCustomizeFreqListIntoAcqRec
 功能描述  : 将中国电信自定义频点加入到捕获表中
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月7日
    作    者   : w00242748
    修改内容   : 新生成函数
  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity
*****************************************************************************/
VOS_VOID CNAS_PRL_AddCTCCCustomizeFreqListIntoAcqRec(VOS_VOID)
{
    CNAS_CCB_CTCC_CUSTOMIZE_FREQ_LIST_STRU                 *pstCustFreqList = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_INFO_STRU                          *pstAcqRecInfo = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU                               *pstAcqRecord = VOS_NULL_PTR;
    VOS_UINT32                                              ulSize;
    VOS_UINT16                                              i;

    pstCustFreqList                =  CNAS_CCB_GetCTCCCustomizeFreqList();

    pstAcqRecInfo                  = &(CNAS_PRL_GetPrlInfoAddr()->stPrlAcqInfo);
    pstAcqRecInfo->usAcqRecordNum++;

    /* 申请内存 */
    ulSize                             = (pstCustFreqList->usFreqNum) * sizeof(VOS_UINT16) + sizeof(CNAS_PRL_ACQ_RECORD_STRU);
    pstAcqRecord                       = (CNAS_PRL_ACQ_RECORD_STRU *)CNAS_PRL_Malloc(ulSize);

    if (VOS_NULL_PTR == pstAcqRecord)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_AddCTCCCustomizeFreqListIntoAcqRec: mem alloc fail");

        return;
    }

    pstAcqRecInfo->pastPrlAcqRecord[pstAcqRecInfo->usAcqRecordNum - 1] = pstAcqRecord;

    pstAcqRecord->enAcqType            = CNAS_PRL_ACQ_TYPE_CELLULAR_CDMA_CUSTOM_CHANNELS;
    pstAcqRecord->ucAcqValid           = VOS_TRUE;
    pstAcqRecord->u.stCelluarCustomSys.ucNumOfChans = (VOS_UINT8)(pstCustFreqList->usFreqNum);

    for (i = 0;i < pstCustFreqList->usFreqNum;i++)
    {
        pstAcqRecord->u.stCelluarCustomSys.ausChan[i] = pstCustFreqList->astFreqList[i].usChannel;
    }
}


/*****************************************************************************
 函 数 名  : CNAS_PRL_ParsePrlAcqRec
 功能描述  : 解析一条acquisition record记录
 输入参数  : pucSrc:原始bit码流
             pstPrlAcqRecord:解析后的acquisition record
 输出参数  : pulBitOffset:解析后的bit偏移量
 返 回 值  : VOS_TRUE：解析成功； VOS_FALSE：解析失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : h00246512
    修改内容   : 新生成函数
  2.日    期   : 2015年7月7日
    作    者   : w00242748
    修改内容   : CDMA 1X Iteration 17 modified
*****************************************************************************/
CNAS_PRL_PARSE_CAUSE_ENUM_UINT32 CNAS_PRL_ParsePrlAcqRec(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    VOS_UINT32                         *pulCurOffSetPos
)
{
    VOS_UINT8                                              *pucPrlBuff    = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_INFO_STRU                          *pstAcqRecInfo = VOS_NULL_PTR;
    CNAS_CCB_CTCC_CUSTOMIZE_FREQ_LIST_STRU                 *pstCustFreqList = VOS_NULL_PTR;
    CNAS_PRL_ACQ_TYPE_ENUM_UINT8                            enAcqType;
    VOS_UINT8                                               ucBitLen;
    VOS_UINT32                                              ulCurBitOffset;
    VOS_UINT32                                              ulAcqBitOffset;
    VOS_UINT32                                              i;

    pstCustFreqList =  CNAS_CCB_GetCTCCCustomizeFreqList();

    /* 获取信息头中解析出的ACQ_NUMS */
    pstAcqRecInfo                  = &(CNAS_PRL_GetPrlInfoAddr()->stPrlAcqInfo);
    pstAcqRecInfo->usAcqRecordNum  = CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.usNumAcqRecs;


    /*
    对于CNAS_PRL_SSPR_P_REV_1，参考C.S0016 3.5.5.2.1.1
    Acquisition Record  Field Length (bits)
    ACQ_TYPE            4

    对于CNAS_PRL_SSPR_P_REV_3，参考C.S0016 3.5.5.2.2
    Type-specific     Record Length (bits)
    ACQ_TYPE          8
    两者的长度是不一样的
    */
    if (CNAS_PRL_SSPR_P_REV_3 == CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.enSsprPRev)
    {
        ucBitLen = CNAS_PRL_BIT_LEN_8_BIT;
    }
    else
    {
        ucBitLen = CNAS_PRL_BIT_LEN_4_BIT;
    }

    pucPrlBuff     = pucSrc;
    ulCurBitOffset = ulOffsetPos;

    for (i = 0; i < (VOS_UINT32)CNAS_MIN(pstAcqRecInfo->usAcqRecordNum,CNAS_PRL_ACQ_RECORD_MAX_NUM); i++)
    {
        /* 解析ACQ_TYPE */
        enAcqType       = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, ucBitLen);
        ulCurBitOffset += ucBitLen;

        ulAcqBitOffset  = 0;

        /* 根据enAcqType查找g_astCnasPrlProcParseAcqTypeRec，进行解析 */
        if (VOS_TRUE != CNAS_PRL_ParseExAcqRecTbl(enAcqType,
                                                  pucPrlBuff,
                                                  ulCurBitOffset,
                                                  &(pstAcqRecInfo->pastPrlAcqRecord[i]),
                                                  &ulAcqBitOffset))
        {
            return CNAS_PRL_PARSE_ACQ_RECORD_FAIL;
        }

        ulCurBitOffset = ulAcqBitOffset;
    }

    /* 如果所有系统记录都无效，则认为PRL表无效 */
    if (VOS_FALSE == CNAS_PRL_IsAcqRecTabValid(pstAcqRecInfo))
    {
        return CNAS_PRL_PARSE_ACQ_RECORD_FAIL;
    }

    if ( (CNAS_PRL_SSPR_P_REV_1 == CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.enSsprPRev)
      && (VOS_TRUE == pstCustFreqList->ucEnableFlg) )
    {
        CNAS_PRL_AddCTCCCustomizeFreqListIntoAcqRec();
    }

    /* 输出捕获表记录信息 */
    CNAS_PRL_LogAcqRecInfo(pstAcqRecInfo);

    /* 返回获取表记录的偏移 */
    *pulCurOffSetPos    = ulCurBitOffset;

    return CNAS_PRL_PARSE_SUCCESS;

}

/*****************************************************************************
 函 数 名  : CNAS_PRL_ParseSysIdRec_1X
 功能描述  : 解析Type-specific system ID record记录
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_PRL_ParseSysIdRec_1X(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_SYS_TYPE_1X_IS95_ID_STRU  *pst1xAndIs95Id,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    /*
    Table 3.5.5.3.2-2 Type-specific system ID record
    System ID Record Field          Length (bits)
    RESERVED                        1
    NID_INCL                        2
    SID                             15
    NID                             0 or 16
    */
    VOS_UINT8                          *pucPrBuff    = VOS_NULL_PTR;
    VOS_UINT32                          ulCurBitOffset;

    /* 初始化变量 */
    pucPrBuff      = pucSrc;
    ulCurBitOffset = ulOffsetPos;

    /* 跳过RESERVED */
    ulCurBitOffset += CNAS_PRL_BIT_LEN_1_BIT;

    /* 解析NID_INCL */
    pst1xAndIs95Id->enNidIncl = CNAS_PRL_BIT_TO_BYTE(pucPrBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_2_BIT);
    ulCurBitOffset += CNAS_PRL_BIT_LEN_2_BIT;

    /* 解析SID */
    pst1xAndIs95Id->usSid = CNAS_PRL_BIT_TO_WORD(pucPrBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_15_BIT);
    ulCurBitOffset += CNAS_PRL_BIT_LEN_15_BIT;

    /* 解析NID */
    if (CNAS_PRL_NID_INCL == pst1xAndIs95Id->enNidIncl)
    {
        pst1xAndIs95Id->usNid = CNAS_PRL_BIT_TO_WORD(pucPrBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_16_BIT);
        ulCurBitOffset += CNAS_PRL_BIT_LEN_16_BIT;
    }
    else if (CNAS_PRL_NID_NOT_INCL_WILD_CARD == pst1xAndIs95Id->enNidIncl)
    {
        pst1xAndIs95Id->usNid           = CNAS_PRL_WILDCARD_NID;
    }
    else if (CNAS_PRL_NID_NOT_INCL_PLUBLIC_SYSTEM == pst1xAndIs95Id->enNidIncl)
    {
        pst1xAndIs95Id->usNid           = 0;
    }
    else
    {
        /* NID included is reserved */
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseSysIdRec_1X:  enNidIncl is illegal!");

        pst1xAndIs95Id->usNid = CNAS_PRL_WILDCARD_NID;
    }

    /* 记录本条记录的偏移值 */
    *pulCurOffsetPos = ulCurBitOffset;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_PRL_ParseSubnetComm
 功能描述  : 解析Type-specific system ID record记录
 输入参数  : pucSrc       : EPRL 码流
             ulOffsetPos  : SubnetCom相对表头的码流
             pstIs586Id   : Subnet地址

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月3日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_PRL_ParseSubnetComm(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_SYS_TYPE_HRPD_ID_STRU     *pstIs586Id
)
{
    VOS_UINT8                          *pucPrBuff       = VOS_NULL_PTR;
    VOS_UINT8                          *pucSubnetCom    = VOS_NULL_PTR;
    VOS_UINT32                          ulSubnetComOffset;

    /*
    Table 3.5.5.3.2.1-1 Common Subnet Record
    System ID Record Field      Length (bits)
    RESERVED                    4
    SUBNET_COMMON_LENGTH        4
    SUBNET_COMMON               8  *    SUBNET_COMMON_LENGTH
    */

    pucPrBuff = pucSrc;

    /* 获取SubnetComm在传入码流中起始位置 */
    ulSubnetComOffset = CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.ulComSubnetBitOffset +
                        ulOffsetPos;

    pucSubnetCom                = pucPrBuff + ulSubnetComOffset;

    pstIs586Id->ucSubnetCommLen = pucSubnetCom[0] & 0x0F;

    NAS_MEM_CPY_S(pstIs586Id->aucSubnet,
                  CNAS_PRL_BYTES_IN_SUBNET,
                  pucSubnetCom + sizeof(VOS_UINT8),
                  pstIs586Id->ucSubnetCommLen);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_PRL_ParseSysIdRec_Is856
 功能描述  : 解析Type-specific system ID record记录
 输入参数  : pucSrc          - EPRL 码流
             ulOffsetPos     - EPRL 码流当前位置
             pstIs856Id      - 解析存码流放地址

 输出参数  : pulCurOffsetPos - 解析完的bit码流长度

 返 回 值  : VOS_TRUE：解析成功； VOS_FALSE：解析失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月3日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_PRL_ParseSysIdRec_Is856(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_SYS_TYPE_HRPD_ID_STRU     *pstIs856Id,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    /*
    Table 3.5.5.3.2-2 Type-specific system ID record
    System ID Record Field          Length (bits)

    RESERVED                        3
    SUBNET_COMMON_INCLUDED          1
    SUBNET_LSB_LENGTH               7
    SUBNET_LSB                      SUBNET_LSB_LENGTH
    SUBNET_COMMON_OFFSET            0 or 12
    */

    VOS_UINT8                          *pucPrBuff               = VOS_NULL_PTR;
    VOS_UINT8                           ucSubnetLsbLen          = 0;
    VOS_UINT8                           ucMinSubnetLsbLen       = 0;
    VOS_UINT32                          ulSubCommOffset         = 0; /* 0 or 12 */
    VOS_UINT32                          ulSubCommOffsetToTable  = 0;
    VOS_UINT32                          ulCurBitOffset;

    /* 初始化变量 */
    pucPrBuff      = pucSrc;
    ulCurBitOffset = ulOffsetPos;

    /* 跳过RESERVED */
    ulCurBitOffset += CNAS_PRL_BIT_LEN_3_BIT;

    /* 解析COMM_INCL */
    pstIs856Id->ucSubnetCommInc = CNAS_PRL_BIT_TO_BYTE(pucPrBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_1_BIT);
    ulCurBitOffset += CNAS_PRL_BIT_LEN_1_BIT;

    /* 解析LSB_LEN */
    pstIs856Id->ucSubnetLsbLen = CNAS_PRL_BIT_TO_BYTE(pucPrBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_7_BIT);
    ulCurBitOffset += CNAS_PRL_BIT_LEN_7_BIT;

    /* Subnet组成 |--SubnetComm--+--SubnetLsb--|*/
    if (VOS_TRUE == pstIs856Id->ucSubnetCommInc)
    {
        /* 解析SubnetComm */
        /* 包含SUBNET_COMMON,解析SUBNET_COMMON_OFFSET */
        ulSubCommOffsetToTable = CNAS_PRL_BIT_TO_WORD(pucPrBuff,
                                                      (ulCurBitOffset + pstIs856Id->ucSubnetLsbLen),
                                                      CNAS_PRL_BIT_LEN_12_BIT);
        /* 解析SUBNET_COMMON */
        CNAS_PRL_ParseSubnetComm(pucPrBuff, ulSubCommOffsetToTable, pstIs856Id);

        ulSubCommOffset = CNAS_PRL_BIT_LEN_12_BIT;
    }
    else
    {
        ulSubCommOffset             = 0;
        pstIs856Id->ucSubnetCommLen = 0;
    }

    ucSubnetLsbLen = ((pstIs856Id->ucSubnetLsbLen + CNAS_PRL_BIT_LEN_7_BIT) / CNAS_PRL_BIT_LEN_8_BIT);

    /* 解析SubnetLsb */
    ucMinSubnetLsbLen = CNAS_MIN(ucSubnetLsbLen, (sizeof(pstIs856Id->aucSubnet) - pstIs856Id->ucSubnetCommLen));
    NAS_MEM_CPY_S(&(pstIs856Id->aucSubnet[pstIs856Id->ucSubnetCommLen]),
                  CNAS_PRL_BYTES_IN_SUBNET - pstIs856Id->ucSubnetCommLen,
                  &pucPrBuff[ulCurBitOffset / CNAS_PRL_BIT_LEN_8_BIT], /* PRL码流到此恰好是8bit对齐 */
                  (VOS_UINT32)ucMinSubnetLsbLen);

    pstIs856Id->ucSubnetBitLen = pstIs856Id->ucSubnetCommLen + pstIs856Id->ucSubnetLsbLen;

    ulCurBitOffset  += pstIs856Id->ucSubnetLsbLen;

    ulCurBitOffset  += ulSubCommOffset;

    /* 记录本条记录的偏移值 */
    *pulCurOffsetPos = ulCurBitOffset;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_PRL_ParseSysIdRec_Mcc
 功能描述  : 解析Type-specific system ID record记录
 输入参数  : pucSrc          - EPRL 码流
             ulOffsetPos     - EPRL 码流当前位置
             pstMccMncIdId   - 解析存码流放地址

 输出参数  : pulCurOffsetPos - 解析完的bit码流长度
 返 回 值  : VOS_TRUE：解析成功； VOS_FALSE：解析失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月3日
    作    者   : d00212987
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParseSysIdRec_Mcc(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_SYS_TYPE_MCC_MNC_ID_STRU  *pstMccMncIdId,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    /*
    Table 3.5.5.3.2.2-1 Type-specific system ID record  18
    System ID Record Field          Length (bits)
    SYS_RECORD_SUBTYPE              3
    Subtype dependent field         Variable

    ----------------------------------------------------
    Table 3.5.5.3.2.2-3 Subtype Dependent record for Subtype ‘000’  7
    Field Name                      Length (bits)
    MCC                             12
    MNC                             12
    ----------------------------------------------------
    Table 3.5.5.3.2.2-4 Subtype Dependent record for Subtype ‘001’  16
    Field Name                      Length (bits)
    RESERVED                        4
    NUM_SID                         4
    NUM_SID occurrences of the following field
    RESERVED                        1
    SID                             15
    ----------------------------------------------------
    Table 3.5.5.3.2.2-5 Subtype Dependent record for Subtype ‘010’
    Field Name                      Length (bits)
    RESERVED                        4
    NUM_SID_NID                     4
    NUM_SID_NID occurrences of the following two fields
    RESERVED                        1
    SID                             15
    NID                             16
    ----------------------------------------------------
    */
    VOS_UINT8                          *pucPrBuff    = VOS_NULL_PTR;
    VOS_UINT32                          ulCurBitOffset;
    VOS_UINT32                          ulSubnet_len;
    VOS_UINT32                          i;

    /* 初始化变量 */
    pucPrBuff      = pucSrc;
    ulCurBitOffset = ulOffsetPos;

    /* SYS_RECORD_SUBTYPE */
    pstMccMncIdId->enMccMncSubType = CNAS_PRL_BIT_TO_BYTE(pucPrBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_3_BIT);
    ulCurBitOffset += CNAS_PRL_BIT_LEN_3_BIT;

    /* 解析MCC */
    pstMccMncIdId->usMcc= CNAS_PRL_BIT_TO_WORD(pucPrBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_12_BIT);
    ulCurBitOffset += CNAS_PRL_BIT_LEN_12_BIT;

    /* 解析MNC */
    pstMccMncIdId->usMnc= CNAS_PRL_BIT_TO_WORD(pucPrBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_12_BIT);
    ulCurBitOffset += CNAS_PRL_BIT_LEN_12_BIT;

    switch(pstMccMncIdId->enMccMncSubType)
    {
        case CNAS_PRL_MCC_MNC_SUBTYPE_ONLY:
            break;

        case CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SID:
        case CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SID_NID:

            /* RESERVED 4 */
            ulCurBitOffset += CNAS_PRL_BIT_LEN_4_BIT;

            pstMccMncIdId->u.stSidNid.ucSidNidNum = CNAS_PRL_BIT_TO_BYTE(pucPrBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_4_BIT);
            ulCurBitOffset += CNAS_PRL_BIT_LEN_4_BIT;

            for (i=0; i<pstMccMncIdId->u.stSidNid.ucSidNidNum; i++)
            {
                /* RESERVED 1 */
                ulCurBitOffset += CNAS_PRL_BIT_LEN_1_BIT;

                pstMccMncIdId->u.stSidNid.asSid[i] = CNAS_PRL_BIT_TO_WORD(pucPrBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_15_BIT);
                ulCurBitOffset += CNAS_PRL_BIT_LEN_15_BIT;

                if(CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SID == pstMccMncIdId->enMccMncSubType)
                {
                    pstMccMncIdId->u.stSidNid.asNid[i] = CNAS_PRL_WILDCARD_NID;
                }
                else
                {
                    pstMccMncIdId->u.stSidNid.asNid[i] = CNAS_PRL_BIT_TO_WORD(pucPrBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_16_BIT);
                    ulCurBitOffset += CNAS_PRL_BIT_LEN_16_BIT;
                }

            }
            break;
        /*
        ----------------------------------------------------
        Table 3.5.5.3.2.2-6 Subtype Dependent record for Subtype ‘011’  14
        Field Name                  Length (bits)
        RESERVED                    4
        NUM_SUBNET_ID               4
        NUM_SUBNET_ID occurrences of the following three fields:
        SUBNET_LENGTH               8
        SUBNET_ID                   SUBNET_LENGTH
        RESERVED                    0 to 7
        ----------------------------------------------------
        */
        case CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SUBNET_ID:

            pstMccMncIdId->u.pstSubnetId = (CNAS_PRL_SYS_TYPE_SUBNET_ID_STRU*)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                                                           sizeof(CNAS_PRL_SYS_TYPE_SUBNET_ID_STRU));

            if (VOS_NULL_PTR == pstMccMncIdId->u.pstSubnetId)
            {
                return VOS_FALSE;
            }

            NAS_MEM_SET_S(pstMccMncIdId->u.pstSubnetId, sizeof(CNAS_PRL_SYS_TYPE_SUBNET_ID_STRU), 0, sizeof(CNAS_PRL_SYS_TYPE_SUBNET_ID_STRU));

            /* RESERVED 4 */
            ulCurBitOffset += CNAS_PRL_BIT_LEN_4_BIT;

            pstMccMncIdId->u.pstSubnetId->ucSubnetNum = CNAS_PRL_BIT_TO_BYTE(pucPrBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_4_BIT);
            ulCurBitOffset += CNAS_PRL_BIT_LEN_4_BIT;

            for (i=0; i<pstMccMncIdId->u.pstSubnetId->ucSubnetNum; i++)
            {
                pstMccMncIdId->u.pstSubnetId->aucSubnetLen[i]= CNAS_PRL_BIT_TO_BYTE(pucPrBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);
                ulCurBitOffset += CNAS_PRL_BIT_LEN_8_BIT;

                ulSubnet_len = CNAS_MIN( ((pstMccMncIdId->u.pstSubnetId->aucSubnetLen[i] + CNAS_PRL_BIT_LEN_7_BIT)/CNAS_PRL_BIT_LEN_8_BIT),
                                        CNAS_PRL_MCC_MNC_SUBNET_MAX_LEN);

                NAS_MEM_CPY_S(pstMccMncIdId->u.pstSubnetId->aucSubnetID[i],
                              (CNAS_PRL_MCC_MNC_SUBNET_MAX_NUM - i ) * CNAS_PRL_MCC_MNC_SUBNET_MAX_LEN,
                              &pucPrBuff[ulCurBitOffset / CNAS_PRL_BIT_LEN_8_BIT],
                              ulSubnet_len);

                ulCurBitOffset += pstMccMncIdId->u.pstSubnetId->aucSubnetLen[i];
            }

            ulCurBitOffset = ((ulCurBitOffset + CNAS_PRL_BIT_LEN_7_BIT) / CNAS_PRL_BIT_LEN_8_BIT) * CNAS_PRL_BIT_LEN_8_BIT;
            break;

        default:
        /* 该记录类型未知 */
        //pstPrlSysRecord->ucSysRecValid = VOS_FALSE;
        CNAS_ERROR_LOG1(UEPS_PID_XSD, "CNAS_PRL_ParseSysIdRec_1XMcc: system record = %d is unknown  ",
                        pstMccMncIdId->enMccMncSubType);
        return VOS_FALSE;
    }

    /* 记录本条记录的偏移值 */
    *pulCurOffsetPos = ulCurBitOffset;

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_PRL_ParseSysRec_REV3
 功能描述  : 解析一条system record记录
 输入参数  : pucSrc:原始bit码流
             pstPrlAcqRecord:解析后的system record
 输出参数  : pulBitOffset:解析后的bit偏移量
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : h00246512
    修改内容   : 新生成函数
  2.日    期   : 2015年7月3日
    作    者   : w00242748
    修改内容   : CDMA 1X Iteration 17

*****************************************************************************/
VOS_VOID CNAS_PRL_ParseSysRec_REV3(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstPrlSysRecord,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    /*
    System Record Field         Length (bits)
    SYS_RECORD_LENGTH           5
    SYS_RECORD_TYPE             4
    PREF_NEG                    1
    GEO                         1
    PRI                         1
    ACQ_INDEX                   9
    Type-specific system ID record variable
    ROAM_IND                    0 or 8
    ASSOCIATION_INC             1
    ASSOCIATION_TAG             0 or 8
    PN_ASSOCIATION              0 or 1
    DATA_ASSOCIATION            0 or 1
    RESERVED                    0 to 7
    */

    VOS_UINT8                          *pucPrlBuff = VOS_NULL_PTR;
    VOS_UINT32                          ulSysRecBitOffset;
    VOS_UINT32                          ulCurBitOffset;
    VOS_UINT8                           ucLength;

    /* 初始化变量 */
    ulSysRecBitOffset = 0;
    pucPrlBuff        = pucSrc;
    ulCurBitOffset    = ulOffsetPos;

    /* 解析SYS_RECORD_LENGTH,不需要保存 */
    ucLength        = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_5_BIT);
    ulCurBitOffset += CNAS_PRL_BIT_LEN_5_BIT;

    /* 返回该SYS_RECORD的偏移量 */
    *pulCurOffsetPos = ulOffsetPos + CNAS_PRL_BIT_LEN_8_BIT * ucLength;

    /* 解析SYS_RECORD_TYPE */
    pstPrlSysRecord->enRecordType = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_4_BIT);
    ulCurBitOffset               += CNAS_PRL_BIT_LEN_4_BIT;

    /* 解析PREF_NEG */
    pstPrlSysRecord->enPrefNegSys = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_1_BIT);
    ulCurBitOffset               += CNAS_PRL_BIT_LEN_1_BIT;

    /* 解析GEO */
    pstPrlSysRecord->enGeoInd     = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_1_BIT);
    ulCurBitOffset               += CNAS_PRL_BIT_LEN_1_BIT;

    /* 解析PRI */
    pstPrlSysRecord->enPriInd     = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_1_BIT);
    ulCurBitOffset               += CNAS_PRL_BIT_LEN_1_BIT;

    /* 解析ACQ_INDEX */
    pstPrlSysRecord->usAcqIndex   = CNAS_PRL_BIT_TO_WORD(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_9_BIT);
    ulCurBitOffset               += CNAS_PRL_BIT_LEN_9_BIT;

    /* 根据SYS_RECORD_TYPE，做不同的解析 */
    switch(pstPrlSysRecord->enRecordType)
    {
        case CNAS_PRL_SYS_RECORD_TYPE_1X_IS95:
            CNAS_PRL_ParseSysIdRec_1X(pucPrlBuff,
                                      ulCurBitOffset,
                                      &(pstPrlSysRecord->u.st1xAndIs95Id),
                                      &ulSysRecBitOffset);
            pstPrlSysRecord->ucSysRecValid = VOS_TRUE;
            break;

        case CNAS_PRL_SYS_RECORD_TYPE_HRPD:
            CNAS_PRL_ParseSysIdRec_Is856(pucPrlBuff,
                                         ulCurBitOffset,
                                         &(pstPrlSysRecord->u.stIs856Id),
                                         &ulSysRecBitOffset);
            pstPrlSysRecord->ucSysRecValid = VOS_TRUE;

            break;

        case CNAS_PRL_SYS_RECORD_TYPE_MCC_MNC_BASED:
            if (VOS_TRUE == CNAS_PRL_ParseSysIdRec_Mcc(pucPrlBuff,
                                                        ulCurBitOffset,
                                                        &(pstPrlSysRecord->u.stMccMncId),
                                                        &ulSysRecBitOffset))
            {
                pstPrlSysRecord->ucSysRecValid = VOS_TRUE;
            }
            else
            {
                pstPrlSysRecord->ucSysRecValid = VOS_FALSE;
            }

            break;

        default:
        /* 该记录类型未知 */
        pstPrlSysRecord->ucSysRecValid = VOS_FALSE;
        CNAS_ERROR_LOG1(UEPS_PID_XSD, "CNAS_PRL_ParseSysRec_REV3: system record = %d is unknown  ",
                        pstPrlSysRecord->enRecordType);
        return;
    }

    ulCurBitOffset = ulSysRecBitOffset;

    /* 解析是否是Negative */
    if (CNAS_PRL_PREF_NEG_SYS_PREF == pstPrlSysRecord->enPrefNegSys)
    {
        pstPrlSysRecord->enRoamingInd   = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);
        ulCurBitOffset                 += CNAS_PRL_BIT_LEN_8_BIT;
    }

    /* 解析ASSOCIATION_INC */
    pstPrlSysRecord->ucAssociationIncl  = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_1_BIT);

    if (VOS_TRUE == pstPrlSysRecord->ucAssociationIncl)
    {

        ulCurBitOffset                     += CNAS_PRL_BIT_LEN_1_BIT;

        /* 解析ASSOCIATION_TAG */
        pstPrlSysRecord->ucAssociationTag   = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);
        ulCurBitOffset                     += CNAS_PRL_BIT_LEN_8_BIT;

        /* 解析PN_ASSOCIATION */
        pstPrlSysRecord->ucPnAssociation    = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_1_BIT);
        ulCurBitOffset                     += CNAS_PRL_BIT_LEN_1_BIT;

        /* 解析DATA_ASSOCIATION */
        pstPrlSysRecord->ucDataAssociation  = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_1_BIT);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_PRL_ParseSysRec_REV1
 功能描述  : 解析一条PRL system record记录
 输入参数  : pucSrc:原始bit码流
             pstPrlAcqRecord:解析后的system record
 输出参数  : pulBitOffset:解析后的bit偏移量
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月10日
    作    者   : c00294324
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_PRL_ParseSysRec_REV1(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstPrlSysRecord,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    /*
    System Record Field         Length (bits)
    SID                         15
    NID_INCL                    2
    NID                         0 or 16
    PREF_NEG                    1
    GEO                         1
    PRI                         0 or 1
    ACQ_INDEX                   9
    ROAM_IND                    0 or 8
    */

    VOS_UINT8                          *pucPrlBuff = VOS_NULL_PTR;
    VOS_UINT32                          ulCurBitOffset;

    /* 初始化变量 */
    pucPrlBuff        = pucSrc;
    ulCurBitOffset    = ulOffsetPos;

    /* 解析SID */
    pstPrlSysRecord->u.st1xAndIs95Id.usSid  = CNAS_PRL_BIT_TO_WORD(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_15_BIT);
    ulCurBitOffset               += CNAS_PRL_BIT_LEN_15_BIT;

    /* 解析NID_INCL */
    pstPrlSysRecord->u.st1xAndIs95Id.enNidIncl = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_2_BIT);
    ulCurBitOffset               += CNAS_PRL_BIT_LEN_2_BIT;

    /* 解析NID */
    if (CNAS_PRL_NID_INCL ==  pstPrlSysRecord->u.st1xAndIs95Id.enNidIncl)
    {
        pstPrlSysRecord->u.st1xAndIs95Id.usNid = CNAS_PRL_BIT_TO_WORD(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_16_BIT);
        ulCurBitOffset += CNAS_PRL_BIT_LEN_16_BIT;
    }
    else if (CNAS_PRL_NID_NOT_INCL_WILD_CARD == pstPrlSysRecord->u.st1xAndIs95Id.enNidIncl)
    {
        pstPrlSysRecord->u.st1xAndIs95Id.usNid           = CNAS_PRL_WILDCARD_NID;
    }
    else if (CNAS_PRL_NID_NOT_INCL_PLUBLIC_SYSTEM == pstPrlSysRecord->u.st1xAndIs95Id.enNidIncl)
    {
        pstPrlSysRecord->u.st1xAndIs95Id.usNid           = 0;
    }
    else
    {
        /* NID included is reserved */
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseSysRec_REV1:  enNidIncl is illegal!");

        pstPrlSysRecord->u.st1xAndIs95Id.usNid = CNAS_PRL_WILDCARD_NID;
    }

    /* 解析PREF_NEG */
    pstPrlSysRecord->enPrefNegSys       =   CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_1_BIT);
    ulCurBitOffset                     +=   CNAS_PRL_BIT_LEN_1_BIT;

    /* 解析GEO */
    pstPrlSysRecord->enGeoInd           =   CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_1_BIT);
    ulCurBitOffset                     +=   CNAS_PRL_BIT_LEN_1_BIT;

    /* 解析PRI */
    if (CNAS_PRL_PREF_NEG_SYS_PREF == pstPrlSysRecord->enPrefNegSys)
    {
        pstPrlSysRecord->enPriInd       =   CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_1_BIT);
        ulCurBitOffset                 +=   CNAS_PRL_BIT_LEN_1_BIT;
    }

    /* 解析ACQ_INDEX */
    pstPrlSysRecord->usAcqIndex         =   CNAS_PRL_BIT_TO_WORD(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_9_BIT);
    ulCurBitOffset                     +=   CNAS_PRL_BIT_LEN_9_BIT;

    /* 解析ROAM_IND */
    if (CNAS_PRL_PREF_NEG_SYS_PREF == pstPrlSysRecord->enPrefNegSys)
    {
        pstPrlSysRecord->enRoamingInd   = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);
        ulCurBitOffset                 +=   CNAS_PRL_BIT_LEN_8_BIT;
    }

    pstPrlSysRecord->enRecordType       =   CNAS_PRL_SYS_RECORD_TYPE_1X_IS95;
    pstPrlSysRecord->ucSysRecValid      =   VOS_TRUE;
    *pulCurOffsetPos                    =   ulCurBitOffset;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_PRL_ParsePrlSysRec
 功能描述  : 解析一条system record记录
 输入参数  : pucSrc:原始bit码流
             pstPrlAcqRecord:解析后的system record
 输出参数  : pulBitOffset:解析后的bit偏移量
 返 回 值  : VOS_TRUE：解析成功； VOS_FALSE：解析失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : h00246512
    修改内容   : 新生成函数
  2.日    期   : 2015年7月7日
    作    者   : w00242748
    修改内容   : CDMA 1X Iteration 17 modified

*****************************************************************************/
CNAS_PRL_PARSE_CAUSE_ENUM_UINT32 CNAS_PRL_ParsePrlSysRec(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    VOS_UINT32                         *pulCurOffSetPos
)
{
    CNAS_PRL_SYS_RECORD_INFO_STRU                          *pstSysRecInfo   = VOS_NULL_PTR;
    VOS_UINT8                                              *pucBuffOffset   = VOS_NULL_PTR;
    VOS_UINT32                                              ulSysRecBitOffset;
    VOS_UINT32                                              ulCurBitOffset;
    VOS_UINT32                                              ulSize;
    VOS_UINT32                                              i;
    VOS_UINT16                                              usPriLvlSeed;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstLastSysRec = VOS_NULL_PTR;
    CNAS_CCB_CTCC_CUSTOMIZE_FREQ_LIST_STRU                 *pstCustFreqList = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_INFO_STRU                          *pstAcqRecInfo = VOS_NULL_PTR;

    usPriLvlSeed                        = 0;
    pstCustFreqList                     =  CNAS_CCB_GetCTCCCustomizeFreqList();

    pstAcqRecInfo                       = &(CNAS_PRL_GetPrlInfoAddr()->stPrlAcqInfo);

    /* 初始化变量 */
    pucBuffOffset                       = pucSrc;
    ulCurBitOffset                      = ulOffsetPos;

    /* 获取信息头中解析出的ACQ_NUMS */
    pstSysRecInfo                       = &(CNAS_PRL_GetPrlInfoAddr()->stPrlSysInfo);
    pstSysRecInfo->usSysRecordNum       = CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.usNumSysRecs;

    /* 申请内存，多申请一个内存，为CNAS_PRL_SSPR_P_REV_1版本预留一个记录的空间 */
    ulSize                          = sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU) * (pstSysRecInfo->usSysRecordNum + 1);
    pstSysRecInfo->pstSysRecord     = (CNAS_PRL_EXT_SYS_RECORD_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD, ulSize);

    if (VOS_NULL_PTR == pstSysRecInfo->pstSysRecord)
    {
        return CNAS_PRL_PARSE_SYS_RECORD_FAIL;
    }

    /* 初始化内存空间 */
    NAS_MEM_SET_S(pstSysRecInfo->pstSysRecord, ulSize, 0, ulSize);

    /* 当前先只实现EPRL的解析 */
    if (CNAS_PRL_SSPR_P_REV_3 == CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.enSsprPRev)
    {
        /* 解析每一条系统记录 */
        for (i = 0;  i < pstSysRecInfo->usSysRecordNum; i++)
        {
            ulSysRecBitOffset           = 0;

            CNAS_PRL_ParseSysRec_REV3(pucBuffOffset,
                                      ulCurBitOffset,
                                      pstSysRecInfo->pstSysRecord + i,
                                      &ulSysRecBitOffset);

            /* 偏移BIT码流的指针 */
            ulCurBitOffset = ulSysRecBitOffset;

            (pstSysRecInfo->pstSysRecord + i)->usPriLvl = usPriLvlSeed;

            if (CNAS_PRL_RELATIVE_PRI_MORE == (pstSysRecInfo->pstSysRecord + i)->enPriInd)
            {
                usPriLvlSeed++;
            }
        }
    }

    /* 新增PRL的解析 */
    if (CNAS_PRL_SSPR_P_REV_1 == CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.enSsprPRev)
    {
        /* 解析每一条系统记录 */
        for (i = 0;  i < pstSysRecInfo->usSysRecordNum; i++)
        {
            ulSysRecBitOffset           = 0;

            CNAS_PRL_ParseSysRec_REV1(pucBuffOffset,
                                      ulCurBitOffset,
                                      pstSysRecInfo->pstSysRecord + i,
                                      &ulSysRecBitOffset);

            /* 偏移BIT码流的指针 */
            ulCurBitOffset = ulSysRecBitOffset;

            (pstSysRecInfo->pstSysRecord + i)->usPriLvl = usPriLvlSeed;

            if (CNAS_PRL_RELATIVE_PRI_MORE == (pstSysRecInfo->pstSysRecord + i)->enPriInd)
            {
                usPriLvlSeed++;
            }
        }

        if (VOS_TRUE == pstCustFreqList->ucEnableFlg)
        {
            pstLastSysRec = pstSysRecInfo->pstSysRecord + pstSysRecInfo->usSysRecordNum;

            NAS_MEM_SET_S(pstLastSysRec, sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU), 0x00, sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU));
            pstLastSysRec->enRecordType  = CNAS_PRL_SYS_RECORD_TYPE_HRPD;
            pstLastSysRec->enPrefNegSys  = CNAS_PRL_PREF_NEG_SYS_PREF;
            pstLastSysRec->enGeoInd      = CNAS_PRL_GEO_REGION_IND_NEW;
            pstLastSysRec->enPriInd      = CNAS_PRL_RELATIVE_PRI_MORE;
            pstLastSysRec->usAcqIndex    = pstAcqRecInfo->usAcqRecordNum - 1;
            pstLastSysRec->ucSysRecValid = VOS_TRUE;
            pstLastSysRec->usPriLvl      = usPriLvlSeed;
            /* 漫游指示标记，与甘兰确认，该标记其不使用 */
            pstLastSysRec->enRoamingInd  = CNAS_PRL_SYS_ROAMING_STATUS_OFF;

            pstSysRecInfo->usSysRecordNum++;
        }
    }

    /* 如果系统表中所有记录无效，则返回系统记录失败 */
    if (VOS_FALSE == CNAS_PRL_IsSysRecTabValid(pstSysRecInfo))
    {
        return CNAS_PRL_PARSE_SYS_RECORD_FAIL;
    }

    /* 输出系统表记录信息 */
    CNAS_PRL_LogSysRecInfo(pstSysRecInfo);

    *pulCurOffSetPos  = ulCurBitOffset;

    return CNAS_PRL_PARSE_SUCCESS;
}

/*****************************************************************************
 函 数 名  : CNAS_PRL_ParsePrlHeader
 功能描述  : 解析PRL表中的信息
 输入参数  : pucSrc -- PRL数据原始数据首地址
             enPrlRev -- PRL版本，为解析使用
 输出参数  : 无
 返 回 值  : VOS_TRUE：解析成功； VOS_FALSE：解析失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_PRL_PARSE_CAUSE_ENUM_UINT32 CNAS_PRL_ParsePrlHeader(
    VOS_UINT8                          *pucSrc,
    CNAS_PRL_SSPR_P_REV_ENUM_UINT8      enPrlRev
)
{
    CNAS_PRL_HEADER_INFO_STRU          *pstPrlHeaderInfo = VOS_NULL_PTR;
    VOS_UINT8                          *pucPrlBuff       = VOS_NULL_PTR;
    VOS_UINT16                          usPrlListSize;
    VOS_UINT8                           ucBitOffset;

    /* 解析PRL的头部，当前只解析ERPL */
    /* EPRL和PRL的格式有所差异，下面是协议定义的格式C.S0016 3.5.5
    Preferred Roaming List Field                Length (bits)
    PR_LIST_SIZE                                16
    PR_LIST_ID                                  16
    PREF_ONLY                                   1
    DEF_ROAM_IND                                8
    NUM_ACQ_RECS                                9
    NUM_SYS_RECS                                14
    ACQ_TABLE                                   variable
    SYS_TABLE                                   variable
    RESERVED                                    0 to 7
    PR_LIST_CRC                                 16

    Extended Preferred Roaming List Field       Length (bits)
    PR_LIST_SIZE                                16
    PR_LIST_ID                                  16
    CUR_SSPR_P_REV                              8
    PREF_ONLY                                   1
    DEF_ROAM_IND                                8
    NUM_ACQ_RECS                                9
    NUM_COMMON_SUBNET_RECS                      9
    NUM_SYS_RECS                                14
    RESERVED                                    7
    EXT_ACQ_TABLE                               variable
    COMMON_SUBNET_TABLE                         variable
    EXT_SYS_TABLE                               variable
    RESERVED                                    As needed
    PR_LIST_CRC                                 16
    */

    ucBitOffset     = 0;
    pucPrlBuff      = pucSrc;

    /* 解析PR_LIST_SIZE */
    usPrlListSize = CNAS_PRL_BIT_TO_WORD(pucPrlBuff, ucBitOffset, CNAS_PRL_BIT_LEN_16_BIT);
    ucBitOffset  += CNAS_PRL_BIT_LEN_16_BIT;

    /* 对PR_LIST_SIZE长度做检查, 除去PR_LIST_SIZE与PR_LIST_CRC长度需要大于0*/
    if (usPrlListSize <= (sizeof(VOS_UINT16) + sizeof(VOS_UINT16)))
    {
        return CNAS_PRL_PARSE_INVALID_LIST_SIZE;
    }

    /* 头信息中usPrListSize除去PR_LIST_SIZE与PR_LIST_CRC长度 */
    pstPrlHeaderInfo                = &(CNAS_PRL_GetPrlInfoAddr()->stPrlHeader);
    pstPrlHeaderInfo->usPrListSize  = usPrlListSize;

    /* 解析PR_LIST_ID */
    pstPrlHeaderInfo->usPrListId = CNAS_PRL_BIT_TO_WORD(pucPrlBuff, ucBitOffset, CNAS_PRL_BIT_LEN_16_BIT);
    ucBitOffset += CNAS_PRL_BIT_LEN_16_BIT;

    if (CNAS_PRL_SSPR_P_REV_1 == enPrlRev)
    {
        pstPrlHeaderInfo->enSsprPRev = CNAS_PRL_SSPR_P_REV_1;

        /* PRL头解析 */
        /* 解析PREF_ONLY */
        pstPrlHeaderInfo->ucPreferOnly  = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ucBitOffset, CNAS_PRL_BIT_LEN_1_BIT);
        ucBitOffset += CNAS_PRL_BIT_LEN_1_BIT;

        /* 解析DEF_ROAM_IND */
        pstPrlHeaderInfo->enDefRoamInd  = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ucBitOffset, CNAS_PRL_BIT_LEN_8_BIT);
        ucBitOffset += CNAS_PRL_BIT_LEN_8_BIT;

        /* 解析NUM_ACQ_RECS */
        pstPrlHeaderInfo->usNumAcqRecs  = CNAS_PRL_BIT_TO_WORD(pucPrlBuff, ucBitOffset, CNAS_PRL_BIT_LEN_9_BIT);
        ucBitOffset += CNAS_PRL_BIT_LEN_9_BIT;

        if (0 == pstPrlHeaderInfo->usNumAcqRecs)
        {
            return CNAS_PRL_PARSE_ACQ_RECORD_FAIL;
        }

        /* 解析NUM_SYS_RECS */
        pstPrlHeaderInfo->usNumSysRecs = CNAS_PRL_BIT_TO_WORD(pucPrlBuff, ucBitOffset, CNAS_PRL_BIT_LEN_14_BIT);
        ucBitOffset += CNAS_PRL_BIT_LEN_14_BIT;

        if (0 == pstPrlHeaderInfo->usNumSysRecs)
        {
            return CNAS_PRL_PARSE_SYS_RECORD_FAIL;
        }
    }
    else
    {
        /* 解析CUR_SSPR_P_REV */
        pstPrlHeaderInfo->enSsprPRev = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ucBitOffset, CNAS_PRL_BIT_LEN_8_BIT);
        ucBitOffset += CNAS_PRL_BIT_LEN_8_BIT;

        if (CNAS_PRL_SSPR_P_REV_3 != pstPrlHeaderInfo->enSsprPRev)
        {
            return CNAS_PRL_PARSE_VERSION_MISMATCH;
        }

        /* 解析PREF_ONLY */
        pstPrlHeaderInfo->ucPreferOnly  = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ucBitOffset, CNAS_PRL_BIT_LEN_1_BIT);
        ucBitOffset += CNAS_PRL_BIT_LEN_1_BIT;

        /* 解析DEF_ROAM_IND */
        pstPrlHeaderInfo->enDefRoamInd  = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ucBitOffset, CNAS_PRL_BIT_LEN_8_BIT);
        ucBitOffset += CNAS_PRL_BIT_LEN_8_BIT;

        /* 解析NUM_ACQ_RECS */
        pstPrlHeaderInfo->usNumAcqRecs  = CNAS_PRL_BIT_TO_WORD(pucPrlBuff, ucBitOffset, CNAS_PRL_BIT_LEN_9_BIT);
        ucBitOffset += CNAS_PRL_BIT_LEN_9_BIT;

        if (0 == pstPrlHeaderInfo->usNumAcqRecs)
        {
            return CNAS_PRL_PARSE_ACQ_RECORD_FAIL;
        }

        /* 解析NUM_COMMON_SUBNET_RECS */
        pstPrlHeaderInfo->usNumSubnetRecs   = CNAS_PRL_BIT_TO_WORD(pucPrlBuff, ucBitOffset, CNAS_PRL_BIT_LEN_9_BIT);
        ucBitOffset += CNAS_PRL_BIT_LEN_9_BIT;

        /* 解析NUM_SYS_RECS */
        pstPrlHeaderInfo->usNumSysRecs = CNAS_PRL_BIT_TO_WORD(pucPrlBuff, ucBitOffset, CNAS_PRL_BIT_LEN_14_BIT);
        ucBitOffset += CNAS_PRL_BIT_LEN_14_BIT;

        if (0 == pstPrlHeaderInfo->usNumSysRecs)
        {
            return CNAS_PRL_PARSE_SYS_RECORD_FAIL;
        }

        /* 跳过RESERVED字段，偏移指向EXT_ACQ_TABLE, 刷新到头部信息 */
        ucBitOffset += CNAS_PRL_BIT_LEN_7_BIT;
    }

    /* 设置捕获表在PRL中的bit偏移 */
    pstPrlHeaderInfo->usAcqTabBitOffset = ucBitOffset;

    /* 打印PRL header信息 */
    CNAS_PRL_LogHeaderInfo(pstPrlHeaderInfo);

    return CNAS_PRL_PARSE_SUCCESS;
}

/*****************************************************************************
 函 数 名  : CNAS_PRL_ParsePrlCalcCommSubnetSize
 功能描述  : 解析COMMON_SUBNET_TABLE占空大小
 输入参数  : pucSrc        -- 当前record首地址
             ucOffsetPos   -- 当前record在字节中的bit偏移
             usNumSubnetRecs- 当前Sub net个数

 输出参数  : pulBitOffset －－ 返回当前记录的bit偏移

 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : h00246512
    修改内容   : 新生成函数
  2.日    期   : 2014年12月6日
    作    者   : d00212987
    修改内容   : EVDO HSD Phase0

*****************************************************************************/
VOS_VOID CNAS_PRL_ParsePrlCalcComSubnetBits(
    VOS_UINT8                          *pucSrc,
    VOS_UINT16                          usNumSubnetRecs,
    VOS_UINT32                          ulOffsetPos,
    VOS_UINT32                         *pulBitOffset
)
{
    /* 当前函数不做实际解析，只做对应的bit偏移 */
    /*
    System ID Record Field      Length (bits)
    RESERVED                    4
    SUBNET_COMMON_LENGTH        4
    SUBNET_COMMON               8 * SUBNET_COMMON_LENGTH
    */

    VOS_UINT32                          ulCurBitOffset;
    VOS_UINT8                           ucSubnetComLen;
    VOS_UINT16                          i;

    /* 当前码流相对码流偏移位置 */
    ulCurBitOffset  = ulOffsetPos;

    for (i=0; i<usNumSubnetRecs; i++)
    {
        /* 统计4bit偏移量 */
        ulCurBitOffset += CNAS_PRL_BIT_LEN_4_BIT;

        /* 解析SUBNET_COMMON_LENGTH */
        ucSubnetComLen = CNAS_PRL_BIT_TO_BYTE(pucSrc, ulCurBitOffset, CNAS_PRL_BIT_LEN_4_BIT);
        ulCurBitOffset += CNAS_PRL_BIT_LEN_4_BIT;

        /* 计算该record总的bit偏移 */
        ulCurBitOffset += ucSubnetComLen * CNAS_PRL_BIT_LEN_8_BIT;
    }

    *pulBitOffset = ulCurBitOffset;

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_PRL_ParsePrlInfo
 功能描述  : 解析PRL表中的信息
 输入参数  : pucSrc   -- PRL原始数据
             usSrcLen -- 原始数据长度
 输出参数  : 无
 返 回 值  : VOS_TRUE：解析成功； VOS_FALSE：解析失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_PRL_PARSE_CAUSE_ENUM_UINT32 CNAS_PRL_ParsePrlInfo(
    VOS_UINT8                          *pucSrc,
    VOS_UINT16                          usSrcLen,
    CNAS_PRL_SSPR_P_REV_ENUM_UINT8      enPrlRev
)
{
    CNAS_PRL_HEADER_INFO_STRU          *pstPrlHeaderInfo = VOS_NULL_PTR;
    VOS_UINT8                          *pucPrlBuff       = VOS_NULL_PTR;
    VOS_UINT32                          ulPrlBitOffset;
    VOS_UINT32                          ulCurBitOffset;
    CNAS_PRL_PARSE_CAUSE_ENUM_UINT32    enCause;

    pucPrlBuff = pucSrc;

    enCause = CNAS_PRL_CheckPrlCrcChecksum(pucPrlBuff);
    if (CNAS_PRL_PARSE_SUCCESS != enCause)
    {
        /* CRC校验失败 */
        CNAS_ERROR_LOG1(UEPS_PID_XSD, "check CRC is failure! cause = %d", enCause);
        return enCause;
    }

    /* 先解析PRL的头部，当前只解析ERPL */
    enCause = CNAS_PRL_ParsePrlHeader(pucPrlBuff, enPrlRev);
    if (CNAS_PRL_PARSE_SUCCESS != enCause)
    {
        /* CRC校验失败 */
        CNAS_ERROR_LOG1(UEPS_PID_XSD, "ParseHeader is failure! cause = %d", enCause);

        return enCause;
    }
    pstPrlHeaderInfo = &(CNAS_PRL_GetPrlInfoAddr()->stPrlHeader);
    ulCurBitOffset   = pstPrlHeaderInfo->usAcqTabBitOffset;

    /* 解析acquisition表 */
    ulPrlBitOffset = 0;
    enCause = CNAS_PRL_ParsePrlAcqRec(pucPrlBuff, ulCurBitOffset, &ulPrlBitOffset);
    if (CNAS_PRL_PARSE_SUCCESS != enCause)
    {
        CNAS_ERROR_LOG1(UEPS_PID_XSD, "parse acquisiton record table is failure! cause = %d", enCause);

        return enCause;
    }

    ulCurBitOffset = ulPrlBitOffset;

    pstPrlHeaderInfo->ulComSubnetBitOffset = ulCurBitOffset; /* 记录Comm Sub Net bit偏移起始位置 */
    /* 解析SUBNET_COMM表 */
    if (CNAS_PRL_SSPR_P_REV_3 == enPrlRev)
    {
        CNAS_PRL_ParsePrlCalcComSubnetBits(pucPrlBuff,
                                           pstPrlHeaderInfo->usNumSubnetRecs,
                                           ulCurBitOffset,
                                           &ulPrlBitOffset);

        ulCurBitOffset = ulPrlBitOffset;
    }

    /* 解析system record表 */
    ulPrlBitOffset = 0;
    enCause        = CNAS_PRL_ParsePrlSysRec(pucPrlBuff, ulCurBitOffset, &ulPrlBitOffset);
    if (CNAS_PRL_PARSE_SUCCESS != enCause)
    {
        CNAS_ERROR_LOG1(UEPS_PID_XSD, "parse system tableis failure! cause = %d", enCause);

        return  enCause;
    }

    /* 解析成功，设置PRL有效 */
    CNAS_PRL_GetPrlInfoAddr()->ulIsPrlValid = VOS_TRUE;

    return CNAS_PRL_PARSE_SUCCESS;
}

/*****************************************************************************
 函 数 名  : CNAS_PRL_IsConcatenatedPrlProbable
 功能描述  : 串连PRL是否是可能，如果是，返回TRUE，否则为FALSE

 输入参数  : pucSrc             -- PRL原始数据
             usSrcLen           -- 原始数据长度
             usFirstPrlListSize -- 首个PRL长度

 输出参数  : 无
 返 回 值  : VOS_TRUE  －－可能有串连PRL
             VOS_FALSE --  不可能有串连PRL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_PRL_IsConcatenatedPrlProbable(
    VOS_UINT8                          *pucSrc,
    VOS_UINT16                          usSrcLen,
    VOS_UINT16                          usFirstPrlListSize
)
{
    VOS_UINT8                          *pucPrlBuff = VOS_NULL_PTR;
    VOS_UINT16                          usSecondPrlListSize;

    if ((usFirstPrlListSize + CNAS_PRL_PRL_LIST_SIZE_BYTE_LEN) < usSrcLen)
    {
        /* 跳到码流中首个PRL，检查是否有串联PRL存在 */
        pucPrlBuff = (pucSrc + usFirstPrlListSize);

        /* 获取第二码流的PRL_LIST_SIZE  */
        usSecondPrlListSize = CNAS_PRL_ExtractBitStringToWord(pucPrlBuff, 0, CNAS_PRL_BIT_LEN_16_BIT);

        if ((usFirstPrlListSize + usSecondPrlListSize) <= usSrcLen)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_PRL_ParsePrlBitStream
 功能描述  : 解析PRL表中的信息, 默认使用版本1解析码流，如果解析失败，尝试用版本
             2解析码流
             如果是串连PRL，

 输入参数  : pucSrc   -- PRL原始数据
             usSrcLen -- 原始数据长度
 输出参数  : 无
 返 回 值  : VOS_TRUE：解析成功； VOS_FALSE：解析失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParsePrlBitStream(
    VOS_UINT8                          *pucSrc,
    VOS_UINT16                          usSrcLen
)
{
    CNAS_PRL_PARSE_CAUSE_ENUM_UINT32    enCause;
    VOS_UINT16                          usFirstPrlListSize;
    VOS_UINT8                          *pucPrlBuff = VOS_NULL_PTR;

    /* 获取码流中首个的PRL_LIST_SIZE  */
     usFirstPrlListSize = CNAS_PRL_ExtractBitStringToWord(pucSrc, 0, CNAS_PRL_BIT_LEN_16_BIT);

    if (usFirstPrlListSize > usSrcLen)
    {
        /* PRL数据长度与返回的文件长度不匹配 */
        CNAS_ERROR_LOG1(UEPS_PID_XSD,
                        "PRL PRL_LIST_SIZE is mismatch usSrcLen: usFirstPrlListSize = " ,
                        usFirstPrlListSize);

        return VOS_FALSE;
    }

    if (VOS_TRUE == CNAS_PRL_IsConcatenatedPrlProbable(pucSrc, usSrcLen, usFirstPrlListSize))
    {
        pucPrlBuff = (pucSrc + usFirstPrlListSize);

        /* 尝试使用EPRL格式解析第二个PRL码流 */
        enCause = CNAS_PRL_ParsePrlInfo(pucPrlBuff, usSrcLen, CNAS_PRL_SSPR_P_REV_3);

        if (CNAS_PRL_PARSE_SUCCESS == enCause)
        {
            /* 解析成功，返回 */
            CNAS_NORMAL_LOG(UEPS_PID_XSD, "CNAS_PRL_ProcPrlInfo: working on 2nd PRL");

            return VOS_TRUE;
        }

        /* 尝试使用EPRL格式解析第一个PRL码流 */
        enCause = CNAS_PRL_ParsePrlInfo(pucSrc, usSrcLen, CNAS_PRL_SSPR_P_REV_3);
        if (CNAS_PRL_PARSE_SUCCESS == enCause)
        {
            /* 解析成功，返回 */
            CNAS_NORMAL_LOG(UEPS_PID_XSD, "CNAS_PRL_ProcPrlInfo: working on 1st PRL");

            return VOS_TRUE;
        }

        /* 使用PRL格式解析第二PRL码流 */
        enCause = CNAS_PRL_ParsePrlInfo(pucPrlBuff, usSrcLen, CNAS_PRL_SSPR_P_REV_1);

        if (CNAS_PRL_PARSE_SUCCESS == enCause)
        {
            /* 解析成功，返回 */
            CNAS_NORMAL_LOG(UEPS_PID_XSD, "CNAS_PRL_ProcPrlInfo: working on 2nd PRL");

            return VOS_TRUE;
        }

        /* 使用PRL格式解析第一PRL码流 */
        enCause = CNAS_PRL_ParsePrlInfo(pucSrc, usSrcLen, CNAS_PRL_SSPR_P_REV_1);

        if (CNAS_PRL_PARSE_SUCCESS == enCause)
        {
            /* 解析成功，返回 */
            CNAS_NORMAL_LOG(UEPS_PID_XSD, "CNAS_PRL_ProcPrlInfo: working on 1nd PRL");

            return VOS_TRUE;
        }
    }
    else
    {

        /* 使用PRL格式解析PRL码流 */
        enCause = CNAS_PRL_ParsePrlInfo(pucSrc, usSrcLen, CNAS_PRL_SSPR_P_REV_1);

        if (CNAS_PRL_PARSE_SUCCESS == enCause)
        {
            /* 解析成功，返回 */
            CNAS_NORMAL_LOG(UEPS_PID_XSD, "CNAS_PRL_ProcPrlInfo: working on PRL");

            return VOS_TRUE;
        }

        /* 使用EPRL格式解析PRL码流 */
        enCause = CNAS_PRL_ParsePrlInfo(pucSrc, usSrcLen, CNAS_PRL_SSPR_P_REV_3);

        if (CNAS_PRL_PARSE_SUCCESS == enCause)
        {
            /* 解析成功，返回 */
            CNAS_NORMAL_LOG(UEPS_PID_XSD, "CNAS_PRL_ProcPrlInfo: working on PRL");

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_PRL_ParseEprlBitStream
 功能描述  : 解析PRL表中的信息, 默认使用版本3解析码流，如果解析失败，尝试用版本
             1解析码流

 输入参数  : pucSrc   -- PRL原始数据
             usSrcLen -- 原始数据长度
 输出参数  : 无
 返 回 值  : VOS_TRUE：解析成功； VOS_FALSE：解析失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParseEprlBitStream(
    VOS_UINT8                          *pucSrc,
    VOS_UINT16                          usSrcLen
)
{
    CNAS_PRL_PARSE_CAUSE_ENUM_UINT32    enCause;
    VOS_UINT16                          usPrlListSize;

    /* 获取码流中首个的PRL_LIST_SIZE  */
     usPrlListSize = CNAS_PRL_ExtractBitStringToWord(pucSrc, 0, CNAS_PRL_BIT_LEN_16_BIT);

    if (usPrlListSize > usSrcLen)
    {
        /* PRL数据长度与返回的文件长度不匹配 */
        CNAS_ERROR_LOG1(UEPS_PID_XSD,
                        "PRL PRL_LIST_SIZE is mismatch usSrcLen: usPrlListSize = " ,
                        usPrlListSize);

        return VOS_FALSE;
    }

    enCause = CNAS_PRL_ParsePrlInfo(pucSrc, usSrcLen, CNAS_PRL_SSPR_P_REV_3);

    if (CNAS_PRL_PARSE_SUCCESS == enCause)
    {
        CNAS_NORMAL_LOG(UEPS_PID_XSD, "CNAS_PRL_ProcPrlInfo: working on EPRL");

        return VOS_TRUE;
    }

    /* 尝试用PRL格式解析码流 */
    enCause = CNAS_PRL_ParsePrlInfo(pucSrc, usSrcLen, CNAS_PRL_SSPR_P_REV_1);

    if (CNAS_PRL_PARSE_SUCCESS == enCause)
    {
        CNAS_NORMAL_LOG(UEPS_PID_XSD, "CNAS_PRL_ProcPrlInfo: working on EPRL");

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



