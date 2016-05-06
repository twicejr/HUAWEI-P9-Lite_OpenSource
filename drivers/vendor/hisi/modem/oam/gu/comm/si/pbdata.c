

/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : UsimmApi.c
  Author       : zhuli
  Version      : V100R002
  Date         : 2008-5-15
  Description  : 该C文件给出了---完成缓冲内容处理模块实现
  Function List:
  History      :
 ************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include "si_pb.h"
#include "TafTypeDef.h"
#include "UsimPsInterface.h"
#include "NVIM_Interface.h"

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID PS_FILE_ID_PB_DATA_C
/*lint +e767*/


/*****************************************************************************
函 数 名  :SI_PB_FindPBOffset

功能描述  :用于在缓冲中定位电话本在列表中的偏移

输入参数  :enPBType:输入查询的电话本类型

输出参数  :pucOffset:输出查询的电话本偏移

返 回 值  :VOS_OK:查询成功
           VOS_ERR:查询失败

调用函数  :无

被调函数  :

修订记录  :
1. 日    期   : 2007年10月15日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_FindPBOffset(SI_PB_TYPE_ENUM_UINT32  enPBType, VOS_UINT8 *pucOffset)
{
    VOS_UINT8 i;

    for(i=0; i<SI_PB_MAX_NUMBER; i++)
    {
        if(gastPBContent[i].enPBType == enPBType)   /*当前的查询类型一致*/
        {
            PB_INFO_LOG("SI_PB_FindPBOffset Info: Locate the PhoneBook Accurately");

            *pucOffset = i;

            return VOS_OK;
        }
    }

    PB_ERROR_LOG("SI_PB_FindPBOffset Error: The PhoneBook Info is Not Exist");

    return VOS_ERR;             /*当前未找到偏移*/
}


/*****************************************************************************
函 数 名  :SI_PB_LocateRecord

功能描述  :定位当前访问的电话本在缓冲中的位置

输入参数  :enPBType:输入查询的电话本类型
           usIndex1:访问的电话本的范围起始地址
           usIndex2:访问的电话本的范围结束地址

输出参数  :pucNumber:电话本缓冲在列表中的偏移
           pucContent:电话本访问内容的起实地址

返 回 值  :VOS_OK:查询成功
           VOS_ERR:查询失败

调用函数  :SI_PB_FindPBOffset

被调函数  :

修订记录  :
1. 日    期   : 2007年10月15日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_LocateRecord(SI_PB_TYPE_ENUM_UINT32  enPBType, VOS_UINT16 usIndex1, VOS_UINT16 usIndex2, VOS_UINT8 *pucNumber)
{
    VOS_UINT8   ucPBOffset;
    VOS_UINT32 ulResult;

    ulResult = SI_PB_FindPBOffset(enPBType, &ucPBOffset);    /*首先查询当前的缓冲位置*/

    if(VOS_ERR == ulResult)
    {
        PB_WARNING_LOG("SI_PB_LocateRecord: Locate PhoneBook Error");

        return TAF_ERR_UNSPECIFIED_ERROR;
    }

    if(PB_NOT_INITIALISED == gastPBContent[ucPBOffset].enInitialState)   /*当前的电话本没有初始化完毕*/
    {
        PB_ERROR_LOG("SI_PB_LocateRecord:The PhoneBook is Not Initializtion");

        return TAF_ERR_SIM_BUSY;
    }

    if(PB_FILE_NOT_EXIST == gastPBContent[ucPBOffset].enInitialState)   /*当前的电话本没有初始化完毕*/
    {
        PB_ERROR_LOG("SI_PB_LocateRecord:The PhoneBook is Not Initializtion");

        return TAF_ERR_FILE_NOT_EXIST;
    }

    if((usIndex1 > gastPBContent[ucPBOffset].usTotalNum)
        || (usIndex2 > gastPBContent[ucPBOffset].usTotalNum)
        || (usIndex1 > usIndex2))/*当前的索引已经超出范围*/
    {
        PB_WARNING_LOG("SI_PB_LocateRecord: The Index is Not in The Range of PhoneBook");

        return TAF_ERR_PB_WRONG_INDEX;
    }

    *pucNumber = ucPBOffset;        /*返回当前的电话本缓冲偏移*/

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :SI_PB_CountADNRecordNum

功能描述  :计算缓冲索引号对应的电话本文件的ID和记录号

输入参数  :usIndex:索引号

输出参数  :pusFileId:对应的电话本文件
           pucRecordNum:对应的电话本记录号

返 回 值  :VOS_OK:查询成功
           VOS_ERR:查询失败

调用函数  :无

被调函数  :

修订记录  :
1. 日    期   : 2007年10月15日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_CountADNRecordNum(VOS_UINT16 usIndex, VOS_UINT16 *pusFileId, VOS_UINT8 *pucRecordNum)
{
    VOS_UINT8 i;
    VOS_UINT16 usTemp = 0;

    for(i=0; i<SI_PB_ADNMAX; i++)   /*根据当前的ADN列表内容循环*/
    {
        if((usTemp < usIndex)&&(usIndex <= (gstPBCtrlInfo.astADNInfo[i].ucRecordNum + usTemp)))/*索引号在文件的范围内*/
        {
            *pusFileId = gstPBCtrlInfo.astADNInfo[i].usFileID;  /*返回当前的文件ID*/
            *pucRecordNum = (VOS_UINT8)(usIndex - usTemp);/*返回当前的记录号*/

            return VOS_OK;
        }
        else
        {
            usTemp += gstPBCtrlInfo.astADNInfo[i].ucRecordNum;  /*索引号累计*/
        }
    }

    return VOS_ERR;
}

/*****************************************************************************
函 数 名  : SI_PB_GetXDNFileID
功能描述  : 根据XDN电话本类型返回对应电话本的FID
输入参数  : ulStorage:XDN点话本类型
输出参数  : pusFileId:电话本对应的FID
返 回 值  : VOS_OK
            VOS_ERR
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2008年10月15日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_GetXDNFileID(VOS_UINT32 ulStorage, VOS_UINT16 *pusFileId)
{
    VOS_UINT32 ulResult = VOS_OK;

    switch(ulStorage)
    {
        case SI_PB_STORAGE_ON:
            *pusFileId = EFMSISDN;
            break;
        case SI_PB_STORAGE_FD:
            *pusFileId = EFFDN;
            break;
        case SI_PB_STORAGE_BD:
            *pusFileId = EFBDN;
            break;
        default:
            ulResult = VOS_ERR;
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :SI_PB_BcdToAscii

功能描述  :BCD码转换成Ascii码

输入参数  :ucBcdNumLen:转换的号码长度
           pucBcdNum:转换的号码内容

输出参数  :pucAsciiNum:转换的结果

返 回 值  :无

调用函数  :无

被调函数  :

修订记录  :
1. 日    期   : 2007年10月15日
    作    者   : z00100318
    修改内容   : Creat
2. 日    期   : 2011年08月04日
    作    者   : w00184875
    修改内容   : DTS2011080203533

*****************************************************************************/
VOS_VOID SI_PB_BcdToAscii(VOS_UINT8 ucBcdNumLen,VOS_UINT8 *pucBcdNum, VOS_UINT8 *pucAsciiNum, VOS_UINT8 *pucLen)
{

    VOS_UINT8       ucTmp;
    VOS_UINT8       ucLen = 0;
    VOS_UINT8       ucFirstNumber;
    VOS_UINT8       ucSecondNumber;

    for (ucTmp = 0; ucTmp < ucBcdNumLen; ucTmp++)
    {

        if(0xFF == pucBcdNum[ucTmp])
        {
            break;
        }

        ucFirstNumber  = (VOS_UINT8)(pucBcdNum[ucTmp] & 0x0F); /*取出高半字节*/

        ucSecondNumber = (VOS_UINT8)((pucBcdNum[ucTmp] >> 4) & 0x0F);/*取出低半字节*/

        if(ucFirstNumber <= 9)  /*转换数字*/
        {
            *pucAsciiNum = ucFirstNumber + 0x30;

            pucAsciiNum++;

            ucLen++;
        }
        else if(0x0A == ucFirstNumber)   /*转换*字符*/
        {
            *pucAsciiNum = 0x2a;

            pucAsciiNum++;

            ucLen++;
        }
        else if(0x0B == ucFirstNumber)   /*转换#字符*/
        {
            *pucAsciiNum = 0x23;

            pucAsciiNum++;

            ucLen++;
        }
        else if(0x0C == ucFirstNumber)   /*转换'P'字符*/
        {
            *pucAsciiNum = 0x50;

            pucAsciiNum++;

            ucLen++;
        }
        else if(0x0D == ucFirstNumber)   /*转换'?'字符*/
        {
            *pucAsciiNum = 0x3F;

            pucAsciiNum++;

            ucLen++;
        }
        else                                    /*转换字母*/
        {
            *pucAsciiNum = ucFirstNumber + 0x57;

            pucAsciiNum++;

            ucLen++;
        }

        if(0x0F == ucSecondNumber)
        {
            break;
        }
        if(ucSecondNumber <= 9)
        {
            *pucAsciiNum = ucSecondNumber + 0x30;

            pucAsciiNum++;

            ucLen++;
        }
        else if(0x0A == ucSecondNumber)
        {
            *pucAsciiNum = 0x2a;

            pucAsciiNum++;

            ucLen++;
        }
        else if(0x0B == ucSecondNumber)
        {
            *pucAsciiNum = 0x23;

            pucAsciiNum++;

            ucLen++;
        }
        else if(0x0C == ucSecondNumber)   /*转换'P'字符*/
        {
            *pucAsciiNum = 0x50;

            pucAsciiNum++;

            ucLen++;
        }
        else if(0x0D == ucSecondNumber)   /*转换'?'字符*/
        {
            *pucAsciiNum = 0x3F;

            pucAsciiNum++;

            ucLen++;
        }
        else
        {
            *pucAsciiNum = ucSecondNumber + 0x57;

            pucAsciiNum++;

            ucLen++;
        }
    }

    *pucLen = ucLen;

    return;
}

/*****************************************************************************
函 数 名  :SI_PB_TransPBName

功能描述  :解析电话本姓名

输入参数  :ucNameMax 姓名长度的最大值
           pucName 姓名内容

输出参数  :pAlphaType 转换的姓名编码类型
           pNameLen 转换的姓名长度

返 回 值  :VOS_OK 解析成功
           VOS_ERR 解析失败

调用函数  :无

被调函数  :

修订记录  :
1. 日    期   : 2007年10月15日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_VOID SI_PB_DecodePBName(VOS_UINT8 ucNameMax, VOS_UINT8 *pucName,
                                        VOS_UINT32 *pAlphaType, VOS_UINT8 *pNameLen)
{
    VOS_UINT8 i = 0;

    /* 姓名是UCS2 80 */
    if (SI_PB_ALPHATAG_TYPE_UCS2_80 == pucName[0])
    {
        *pAlphaType = pucName[0];

        ucNameMax--;
        for(i=0;i<(ucNameMax-(ucNameMax%2));i+=2)   /*遍历当前的姓名长度*/
        {
            if((pucName[i+1] == 0xFF)&&(pucName[i+2] == 0xFF))
            {
                break;
            }
        }

        *pNameLen = i;      /*姓名长度返回*/

        return;
    }

    /* 姓名是UCS2 81 */
    if (SI_PB_ALPHATAG_TYPE_UCS2_81 == pucName[0])
    {
        *pAlphaType = pucName[0];

        if(pucName[1] > (ucNameMax - 3))/* 如果当前长度信息超过最大长度，则直接阶截断 */
        {
           i = ucNameMax -1;
        }
        else
        {
           i = pucName[1] + 2;     /*计算当前姓名长度*/
        }

        *pNameLen = i;      /*姓名长度返回*/

        return;
    }

    /* 姓名是UCS2 82 */
    if (SI_PB_ALPHATAG_TYPE_UCS2_82 == pucName[0])
    {
        *pAlphaType = pucName[0];

        if(pucName[1] > (ucNameMax - 4))/* 如果当前长度信息超过最大长度，则直接阶截断 */
        {
           i = ucNameMax -1;
        }
        else
        {
           i = pucName[1] + 3;     /*计算当前姓名长度*/
        }

        *pNameLen = i;      /*姓名长度返回*/

        return;
    }


    /* 姓名是GSM格式存储 */
    *pAlphaType = SI_PB_ALPHATAG_TYPE_GSM;

    for (i = 0; i < ucNameMax; i++)         /*遍历当前的姓名长度*/
    {
        if (0xFF == pucName[i])
        {
            break;
        }
    }

    *pNameLen = i;      /*姓名长度返回*/

    return;
}

/*****************************************************************************
函 数 名  :SI_PB_TransPBFromate

功能描述  :转换当前的一条电话本内容为指定的数据结构

输入参数  :pstPBContent 转换的电话本内容信息
           ucIndex 转换的电话本的索引号/记录号
           pContent 转换的电话本内容

输出参数  :pstRecord 转换的电话本数据结构

返 回 值  :VOS_OK 解析成功
           VOS_ERR 解析失败

调用函数  :
被调函数  :
修订记录  :
1. 日    期   : 2007年10月15日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_VOID SI_PB_TransPBFromate(SI_PB_CONTENT_STRU *pstPBContent, VOS_UINT16 usIndex, VOS_UINT8 *pContent, SI_PB_RECORD_STRU *pstRecord)
{
    VOS_UINT32 ulResult;
    VOS_UINT32 ulExtInfoNum;
    VOS_UINT8  ucExtRecord;
    VOS_UINT8  aucPhoneNumber[20];
    VOS_UINT8  *pucExtContent;
    VOS_UINT8  ucExtNumLen;
    VOS_UINT8  ucXdnNumLen;

    ulResult = SI_PB_CheckContentValidity(pstPBContent, pContent);/*检查当前的内容是否有效*/

    if(ulResult != VOS_OK)
    {
        pstRecord->ValidFlag = SI_PB_CONTENT_INVALID;     /*标记当前的内容无效*/

        /*全置为0*/
    }
    else
    {
        pstRecord->ValidFlag = SI_PB_CONTENT_VALID;/*标记当前的内容有效*/

        SI_PB_DecodePBName(pstPBContent->ucNameLen, pContent,
                            &pstRecord->AlphaTagType,&pstRecord->ucAlphaTagLength);

        if(pstRecord->ucAlphaTagLength != 0x00)         /*当前姓名不为空*/
        {
            if(pstRecord->AlphaTagType == SI_PB_ALPHATAG_TYPE_GSM)  /*拷贝英文姓名从头开始*/
            {
                /*lint -e534*/
                VOS_MemCpy(pstRecord->AlphaTag, pContent, pstRecord->ucAlphaTagLength);
                /*lint +e534*/
            }
            else                                                                                        /*拷贝中文姓名从第二个字节开始*/
            {
                /*ucs2编码，拷贝从长度字段开始*/
                /*lint -e534*/
                VOS_MemCpy(pstRecord->AlphaTag, pContent+1, pstRecord->ucAlphaTagLength);
                /*lint +e534*/
            }
        }

        if ((pContent[pstPBContent->ucNameLen+1] == 0xFF)
            && (pContent[pstPBContent->ucNameLen] == 0x0))
        {
            pstRecord->NumberType   =  PB_NUMBER_TYPE_NORMAL;
        }
        else
        {
            pstRecord->NumberType   =  pContent[pstPBContent->ucNameLen+1];
        }

        ucExtRecord = ((PB_BDN == pstPBContent->enPBType)?\
                        pContent[pstPBContent->ucRecordLen-2]:\
                        pContent[pstPBContent->ucRecordLen-1]);

        ulExtInfoNum  = pstPBContent->ulExtInfoNum;
        pucExtContent = gastEXTContent[ulExtInfoNum].pExtContent;

        ucExtRecord = ((VOS_NULL_PTR == pucExtContent) ? 0xFF : (ucExtRecord));

        if(pContent[pstPBContent->ucNameLen] < 2)           /*当前号码为空*/
        {
            pstRecord->NumberLength = 0;
        }
        else if((0xFF != ucExtRecord)&&(0 != ucExtRecord)&&(VOS_NULL_PTR != pucExtContent)
                &&(ucExtRecord <= gastEXTContent[ulExtInfoNum].usExtTotalNum))
        {
            pucExtContent += (ucExtRecord - 1) * SI_PB_EXT_LEN;
            ucExtNumLen   = (*(pucExtContent + 1) > (SI_PB_NUM_LEN/2))?
                            (SI_PB_NUM_LEN/2) : *(pucExtContent + 1);

            /*lint -e534*/
            VOS_MemCpy(aucPhoneNumber, pContent+(pstPBContent->ucNameLen+2), SI_PB_NUM_LEN/2 );
            VOS_MemCpy(aucPhoneNumber + (SI_PB_NUM_LEN/2), pucExtContent + 2, SI_PB_NUM_LEN/2 );
            /*lint +e534*/

            SI_PB_BcdToAscii((VOS_UINT8)(ucExtNumLen + (SI_PB_NUM_LEN/2)), aucPhoneNumber,
                                pstRecord->Number, &pstRecord->NumberLength);
        }
        else                                                                                /*拷贝号码从内容开始*/
        {
            ucXdnNumLen = ((pContent[pstPBContent->ucNameLen]-1) > (SI_PB_NUM_LEN/2))?
                           (SI_PB_NUM_LEN/2) : (pContent[pstPBContent->ucNameLen]-1);

            SI_PB_BcdToAscii(ucXdnNumLen, &pContent[pstPBContent->ucNameLen+2],
                            pstRecord->Number, &pstRecord->NumberLength);
        }
    }

    pstRecord->Index = usIndex;

    return ;
}

/*****************************************************************************
函 数 名  :SI_PB_MemSet

功能描述  :刷新内存为FF

输入参数  :ucLen: 刷新的内存长度
           pucMem:刷新的内存地址

输出参数  :无

返 回 值  :无

调用函数  :无

被调函数  :无

修订记录  :
1. 日    期   : 2007年10月15日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_VOID SI_PB_MemSet(VOS_UINT8 ucLen, VOS_UINT8 ucValue,VOS_UINT8 *pucMem)
{
    VOS_UINT8 i;

    for(i=0; i<ucLen; i++)
    {
        pucMem[i] = ucValue;
    }

    return;
}

/*****************************************************************************
函 数 名  :SI_PB_GetBitFromBuf
功能描述  :从数据中获取指定Bit位的值　
输入参数  :ucDataBuf:   数据内容
           ulBitNo:     Bit号，从1开始
输出参数  :无
返 回 值  : 1:有效、0:无效
调用函数  :无
修订记录  :
1. 日    期   : 2009年5月19日
    作    者   : m00128685
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_GetBitFromBuf(VOS_UINT8 *pucDataBuf, VOS_UINT32 ulBitNo)
{
    VOS_UINT32  ulOffset;
    VOS_UINT8   ucBit;

    if(VOS_NULL_PTR == pucDataBuf)
    {
        PB_ERROR_LOG("SI_PB_GetBitFromBuf: Input Null Ptr");

        return VOS_FALSE;
    }

    ulOffset = (ulBitNo - 1)/ 8;

    ucBit    = (VOS_UINT8)((ulBitNo - 1)%8);

    return (pucDataBuf[ulOffset]>>ucBit)&0x1;
}

/*****************************************************************************
函 数 名  :SI_PB_CheckEccValidity
功能描述  :检查ECC内容是否为空
输入参数  :pstPBContent:当前电话本的基本信息
           pContent:电话的内容
输出参数  :无
返 回 值  :VOS_OK:查询成功
           VOS_ERR:查询失败
调用函数  :无
被调函数  :
修订记录  :
1. 日    期   : 2009年12月5日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_CheckEccValidity(VOS_UINT8 *pContent)
{
    if (VOS_NULL_PTR == pContent)
    {
        PB_ERROR_LOG("SI_PB_CheckEccValidity: Input NULL PTR");

        return VOS_ERR;
    }

    if( 0xFF == pContent[0])
    {
        PB_INFO_LOG("SI_PB_CheckEccValidity: The ECC is Empty");

        return VOS_ERR;
    }
    else
    {
        PB_INFO_LOG("SI_PB_CheckEccValidity: The ECC is Not Empty");

        return VOS_OK;
    }
}

/*****************************************************************************
函 数 名  :SI_PB_CheckContentValidity

功能描述  :简单检查当前的电话本内容是否为空

输入参数  :pstPBContent:当前电话本的基本信息
           pContent:电话的内容

输出参数  :无

返 回 值  :VOS_OK:查询成功
           VOS_ERR:查询失败

调用函数  :无

被调函数  :

修订记录  :
1. 日    期   : 2007年10月15日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_CheckContentValidity(SI_PB_CONTENT_STRU *pstPBContent, VOS_UINT8 *pContent)
{
    if ((VOS_NULL_PTR == pContent)||(VOS_NULL_PTR == pstPBContent))
    {
        PB_ERROR_LOG("SI_PB_CheckContentValidity: Input NULL PTR");

        return VOS_ERR;
    }

    if(((pContent[pstPBContent->ucNameLen] == 0)||(pContent[pstPBContent->ucNameLen] == 0xFF))
        &&(pContent[0] == 0xFF))/*检查姓名和号码是否为空*/
    {
        PB_INFO_LOG("SI_PB_CheckContentValidity: The PhoneBook Content is Empty");

        return VOS_ERR;
    }
    else
    {
        PB_INFO_LOG("SI_PB_CheckContentValidity: The PhoneBook Content is Not Empty");

        return VOS_OK;
    }
}

/*****************************************************************************
函 数 名  :SI_PB_CheckANRValidity

功能描述  :简单检查当前的电话本内容是否为空

输入参数  :pstPBContent:当前电话本的基本信息
           pContent:电话的内容

输出参数  :无

返 回 值  :VOS_OK:查询成功
           VOS_ERR:查询失败

调用函数  :无

被调函数  :

修订记录  :
1. 日    期   : 2007年10月15日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_CheckANRValidity(VOS_UINT8 *pContent)
{
    if (VOS_NULL_PTR == pContent)
    {
        PB_ERROR_LOG("SI_PB_CheckANRValidity: Input NULL PTR");

        return VOS_ERR;
    }

    if((0xFF == pContent[0])||(0xFF == pContent[1])||(0 == pContent[1]))/*检查号码是否为空*/
    {
        PB_INFO_LOG("SI_PB_CheckANRValidity: The PhoneBook Content is Empty");

        return VOS_ERR;
    }
    else
    {
        PB_INFO_LOG("SI_PB_CheckANRValidity: The PhoneBook Content is Not Empty");

        return VOS_OK;
    }
}


#if ((OSA_CPU_CCPU == VOS_OSA_CPU)||(defined(DMT)))
/*****************************************************************************
函 数 名  :SI_PB_CountADNIndex

功能描述  :计算当前的文件记录号对应的缓冲索引号

输入参数  :usFileId:电话本文件ID
           ucRecordNum:实际的记录号

输出参数  :pusIndex:索引号

返 回 值  :VOS_OK:查询成功
           VOS_ERR:查询失败

调用函数  :无

被调函数  :

修订记录  :
1. 日    期   : 2007年10月15日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_CountADNIndex(VOS_UINT16 usFileId, VOS_UINT8 ucRecordNum, VOS_UINT16 *pusIndex)
{
    VOS_UINT8 i;
    VOS_UINT16 usIndex = 0;

    for(i=0; i<SI_PB_ADNMAX; i++)       /*根据当前的ADN 文件列表内容循环*/
    {
        if(usFileId == gstPBCtrlInfo.astADNInfo[i].usFileID)/*查询当前的文件ID 是否在列表中*/
        {
            *pusIndex = usIndex + ucRecordNum;      /*计算当前的记录号的索引号*/

            return VOS_OK;
        }
        else
        {
            usIndex += gstPBCtrlInfo.astADNInfo[i].ucRecordNum;/*索引号需要累计*/
        }
    }

    return VOS_ERR;             /*当前文件不存在文件列表中*/
}

/*****************************************************************************
函 数 名  :SI_PB_GetADNSfi

功能描述  :根据ADN的fid获取其SFI

输入参数  :usIndex:索引号

输出参数  :pusFileId:对应的电话本文件
           pucRecordNum:对应的电话本记录号

返 回 值  :VOS_OK:查询成功
           VOS_ERR:查询失败

调用函数  :无

被调函数  :

修订记录  :
1. 日    期   : 2009年06月08日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_GetADNSfi(VOS_UINT8 *pucSFI, VOS_UINT16 usFileId)
{
    VOS_UINT8 i;

    for(i = 0; i < gstPBCtrlInfo.ulADNFileNum; i++)   /*根据当前的ADN列表内容循环*/
    {
        if(usFileId == gstPBCtrlInfo.astADNInfo[i].usFileID)
        {
            *pucSFI = gstPBCtrlInfo.astADNInfo[i].ucSFI;

            return VOS_OK;
        }
    }

    return VOS_ERR;
}

/*****************************************************************************
函 数 名  : SI_PB_CheckADNFileID
功能描述  : 检查文件是否是ADN文件
输入参数  : usFileID:文件ID
输出参数  : 无
返 回 值  : VOS_OK
            VOS_ERR
调用函数  : 无
被调函数  :
修订记录  :
1.  日    期   : 2008年10月15日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_CheckADNFileID(VOS_UINT16 usFileID)
{
    VOS_UINT8 j;

    for(j=0; j<SI_PB_ADNMAX; j++)/*比较文件ID是否存在于ADN列表中*/
    {
        if(usFileID == gstPBCtrlInfo.astADNInfo[j].usFileID)
        {
            return VOS_OK;
        }
    }

    return VOS_ERR;
}

/*****************************************************************************
函 数 名  : SI_PB_GetXDNPBType
功能描述  : 输出FID对应的电话本类型
输入参数  : usFileId:FID
输出参数  : pulPBType:电话本类型
返 回 值  : VOS_OK
            VOS_ERR
调用函数  : SI_PB_CheckADNFileID
被调函数  :
修订记录  :
1.  日    期   : 2008年10月15日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_GetXDNPBType(VOS_UINT32 *pulPBType, VOS_UINT16 usFileId)
{
    VOS_UINT32 ulResult = VOS_OK;

    switch(usFileId)
    {
        case EFFDN:
            *pulPBType = PB_FDN_CONTENT;
            break;
        case EFBDN:
            *pulPBType = PB_BDN_CONTENT;
            break;
        case EFMSISDN:
            *pulPBType = PB_MSISDN_CONTENT;
            break;
        case EFSDN:
            *pulPBType = PB_SDN_CONTENT;
            break;
        default:
            ulResult = SI_PB_CheckADNFileID(usFileId);/*检查是否是ADN的FID*/

            if ( VOS_OK == ulResult )
            {
                *pulPBType = PB_ADN_CONTENT;
            }
            else
            {
                ulResult = VOS_ERR;
            }
            break;
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  : SI_PB_GetANRFid
功能描述  : 获取输入的ANR文件计数的ANR文件ID
输入参数  : usANRFileId:FID
输出参数  : pulPBType:电话本类型
返 回 值  : VOS_OK 成功
            VOS_ERR 失败
调用函数  : SI_PB_CheckADNFileID
被调函数  :
修订记录  :
1.  日    期   : 2009年06月03日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_GetANRFid(VOS_UINT32 ulANRFileNum,VOS_UINT16 *pusANRFileId)
{
    VOS_UINT32 i;
    VOS_UINT32 j;
    VOS_UINT32 ulFileCount = 0;

    for(i = 0; i < gstPBCtrlInfo.ulADNFileNum; i++)
    {
        for(j = 0; j < SI_PB_ANRMAX; j++)
        {
            if (SI_PB_FILE_NOT_EXIST != gstPBCtrlInfo.astANRInfo[i][j].usANRFileID)
            {
                ulFileCount++;
            }

            if (ulANRFileNum == ulFileCount)
            {
               *pusANRFileId = gstPBCtrlInfo.astANRInfo[i][j].usANRFileID;

               return VOS_OK;
            }
        }
    }

    return VOS_ERR;
}

/*****************************************************************************
函 数 名  : SI_PB_GetANRSuffix
功能描述  : 获取输入的ANR文件ID对应的控制文件下标
输入参数  : usANRFileId:FID
输出参数  : pulPBType:电话本类型
返 回 值  : VOS_OK 成功
            VOS_ERR 失败
调用函数  : SI_PB_CheckADNFileID
被调函数  :
修订记录  :
1.  日    期   : 2009年06月03日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_GetANRSuffix(VOS_UINT8 *pucXSuffix,VOS_UINT8 *pucYSuffix
                                      ,VOS_UINT16 usANRFileId)
{
    VOS_UINT8 i;
    VOS_UINT8 j;

    for(i = 0; i < gstPBCtrlInfo.ulADNFileNum; i++)
    {
        for(j = 0; j < SI_PB_ANRMAX; j++)
        {
            if (usANRFileId == gstPBCtrlInfo.astANRInfo[i][j].usANRFileID)
            {
                *pucXSuffix = i;
                *pucYSuffix = j;

                return VOS_OK;
            }
        }
    }

    return VOS_ERR;
}

/*****************************************************************************
函 数 名  : SI_PB_GetIAPFidFromANR
功能描述  : 获取输入的ANR文件ID对应的IAP
输入参数  : usANRFileId:FID
输出参数  : pusIAPFileId:IAP文件FID
返 回 值  : VOS_OK 成功
            VOS_ERR 失败
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2009年06月03日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_GetIAPFidFromANR(VOS_UINT16 usANRFileId, VOS_UINT16 *pusIAPFileId)
{
    VOS_UINT32 i;
    VOS_UINT32 j;

    for(i = 0; i < gstPBCtrlInfo.ulADNFileNum; i++)
    {
        for(j = 0; j < SI_PB_ANRMAX; j++)
        {
            if(usANRFileId == gstPBCtrlInfo.astANRInfo[i][j].usANRFileID)
            {
                *pusIAPFileId = gstPBCtrlInfo.astIAPInfo[i].usIAPFileID;

                return VOS_OK;
            }
        }
    }

    return VOS_ERR;
}

/*****************************************************************************
函 数 名  : SI_PB_GetIAPFidFromEML
功能描述  : 获取输入的EML文件ID对应的IAP
输入参数  : usANRFileId:FID
输出参数  : pulPBType:电话本类型
返 回 值  : VOS_OK 成功
            VOS_ERR 失败
调用函数  : SI_PB_CheckADNFileID
被调函数  :
修订记录  :
1.  日    期   : 2009年06月03日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_GetIAPFidFromEML(VOS_UINT16 usEMLFileId, VOS_UINT16 *pusIAPFileId)
{
    VOS_UINT8 i;

    for(i = 0; i < gstPBCtrlInfo.ulEMLFileNum; i++)
    {
        if (usEMLFileId == gstPBCtrlInfo.astEMLInfo[i].usEMLFileID)
        {
            *pusIAPFileId = gstPBCtrlInfo.astIAPInfo[i].usIAPFileID;

            return VOS_OK;
        }
    }

    return VOS_ERR;
}

/*****************************************************************************
函 数 名  : SI_PB_GheckANRLast
功能描述  : 根据控制信息下标和ANR文件ID，判断是否为最后一个
输入参数  : usANRFileId:FID
输出参数  : pulPBType:电话本类型
返 回 值  : VOS_OK 最后一个
            VOS_ERR 不是最后一个
调用函数  : SI_PB_CheckADNFileID
被调函数  :
修订记录  :
1.  日    期   : 2009年06月03日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_GheckANRLast(VOS_UINT8 ucXSuffix,VOS_UINT8 ucYSuffix)
{
    if ((ucXSuffix+1) == (VOS_UINT8)gstPBCtrlInfo.ulADNFileNum)
    {
        return VOS_OK;
    }

    if (SI_PB_FILE_NOT_EXIST == gstPBCtrlInfo.astANRInfo[ucXSuffix+1][ucYSuffix].usANRFileID)
    {
        return VOS_OK;
    }

    return VOS_ERR;
}

/*****************************************************************************
函 数 名  :SI_PB_GetEMLIdFromADN

功能描述  :通过ADN获取到Email文件的ID

输入参数  :usIndex:索引号

输出参数  :pusFileId:对应的电话本文件
           pucRecordNum:对应的电话本记录号

返 回 值  :VOS_OK:查询成功
           VOS_ERR:查询失败

调用函数  :无

被调函数  :

修订记录  :
1.  日    期   : 2009年06月10日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_GetEMLFIdFromADN(VOS_UINT16 *pusEMLFileId, VOS_UINT16 usADNId)
{
    VOS_UINT32 i;

    for (i = 0; i < gstPBCtrlInfo.ulEMLFileNum; i++)
    {
        if(usADNId == gstPBCtrlInfo.astADNInfo[i].usFileID)
        {
            *pusEMLFileId = gstPBCtrlInfo.astEMLInfo[i].usEMLFileID;

            return VOS_OK;
        }
    }

    PB_NORMAL1_LOG("SI_PB_GetEMLFIdFromADN: Get ADN %d Email Error", usADNId);

    return VOS_ERR;
}

/*****************************************************************************
函 数 名  :SI_PB_GetANRFidFromADNFid

功能描述  :通过ADN Fid 计算ANR Fid

输入参数  :usIndex:索引号

输出参数  :pusFileId:对应的电话本文件
           pucRecordNum:对应的电话本记录号

返 回 值  :VOS_OK:查询成功
           VOS_ERR:查询失败

调用函数  :无

被调函数  :

修订记录  :
1.  日    期   : 2009年06月08日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_GetANRFidFromADN(VOS_UINT8 ucANROffset, VOS_UINT16 usADNFileId,VOS_UINT16 *pusANRFileId)
{
    VOS_UINT32 i;

    for(i = 0; i < gstPBCtrlInfo.ulADNFileNum; i++)
    {
        if(usADNFileId == gstPBCtrlInfo.astADNInfo[i].usFileID)
        {
            *pusANRFileId = gstPBCtrlInfo.astANRInfo[i][ucANROffset].usANRFileID;

            return VOS_OK;
        }

    }

    return VOS_ERR;
}
/*****************************************************************************
函 数 名  :SI_PB_GetFreeANRRecordNum

功能描述  :根据输入的ANR文件ID,获取空闲记录号

输入参数  :usIndex:索引号

输出参数  :pusFileId:对应的电话本文件
           pucRecordNum:对应的电话本记录号

返 回 值  :VOS_OK:查询成功
           VOS_ERR:查询失败

调用函数  :无

被调函数  :

修订记录  :
1.  日    期   : 2009年06月08日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_GetFreeANRRecordNum(VOS_UINT16 usANRFid,VOS_UINT8 *pucRecordNum, VOS_UINT16 *pusIAPFid)
{
    VOS_UINT32 i = 0;
    VOS_UINT32 j = 0;
    VOS_UINT32 k = 0;
    VOS_UINT32 ulOffset = 0;
    VOS_UINT32 ulFlag = VOS_FALSE;

    for(i = 0; i < gstPBCtrlInfo.ulADNFileNum; i++)   /*根据当前的ADN列表内容循环*/
    {
        for(j = 0; j < SI_PB_ANRMAX; j++)
        {
            if(usANRFid == gstPBCtrlInfo.astANRInfo[i][j].usANRFileID)
            {
                *pusIAPFid = gstPBCtrlInfo.astIAPInfo[i].usIAPFileID;

                ulFlag = VOS_TRUE;

                break;
            }

        }

        if(VOS_TRUE == ulFlag)
        {
            break;
        }

        ulOffset += (gstPBCtrlInfo.astANRInfo[i][0].ucRecordNum*gstPBCtrlInfo.astANRInfo[i][0].ucRecordLen);
    }

    if(i == gstPBCtrlInfo.ulADNFileNum)
    {
        return VOS_ERR;
    }

    if (SI_PB_ANRMAX  <= j)
    {
        return VOS_ERR;
    }

    for(k = 0; k < gstPBCtrlInfo.astANRInfo[i][j].ucRecordNum; k++)
    {
        if(VOS_OK != SI_PB_CheckANRValidity(&gastANRContent[j%SI_PB_ANRMAX].pContent[ulOffset+(k*gastANRContent[j%SI_PB_ANRMAX].ucRecordLen)]))
        {
            *pucRecordNum = (VOS_UINT8)(k+1);
            return VOS_OK;
        }
    }

    return VOS_ERR;
}
/*****************************************************************************
函 数 名  :SI_PB_GetFreeEMLRecordNum

功能描述  :根据输入的Email文件ID,获取空闲记录号

输入参数  :usIndex:索引号

输出参数  :pusFileId:对应的电话本文件
           pucRecordNum:对应的电话本记录号

返 回 值  :VOS_OK:查询成功
           VOS_ERR:查询失败

调用函数  :无

被调函数  :

修订记录  :
1.  日    期   : 2009年06月08日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_GetFreeEMLRecordNum(VOS_UINT16 ucEMLFid,VOS_UINT8 *pucRecordNum, VOS_UINT16 *pusIAPFid)
{
    VOS_UINT32 i = 0;
    VOS_UINT32 j = 0;
    VOS_UINT32 ulOffset = 0;

    for(i = 0; i < gstPBCtrlInfo.ulEMLFileNum; i++)   /*根据当前的ADN列表内容循环*/
    {
        if(ucEMLFid == gstPBCtrlInfo.astEMLInfo[i].usEMLFileID)
        {
            *pusIAPFid = gstPBCtrlInfo.astIAPInfo[i].usIAPFileID;
            break;
        }

        ulOffset += (gstPBCtrlInfo.astEMLInfo[i].ucRecordNum*gstPBCtrlInfo.astEMLInfo[i].ucRecordLen);
    }

    if(i == gstPBCtrlInfo.ulEMLFileNum)
    {
        return VOS_ERR;
    }

    for(j = 0; j < gstPBCtrlInfo.astEMLInfo[i].ucRecordNum;j++)
    {
         if(0xFF == gstEMLContent.pContent[ulOffset+(j*gstEMLContent.ucRecordLen)])
         {
            *pucRecordNum = (VOS_UINT8)(j+1);
            return VOS_OK;
         }
    }

    return VOS_ERR;
}

/*****************************************************************************
函 数 名  :SI_PB_GetEMLRecord

功能描述  :根据输入的Email文件ID和Record，获取Email缓存内容

输入参数  :usIndex:索引号

输出参数  :pusFileId:对应的电话本文件
           pucRecordNum:对应的电话本记录号

返 回 值  :VOS_OK:查询成功
           VOS_ERR:查询失败

调用函数  :无

被调函数  :

修订记录  :
1.  日    期   : 2009年06月08日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_GetEMLRecord(VOS_UINT8 **ppEMLContent, VOS_UINT16 usEMLFileId,VOS_UINT8 ucRecordNum)
{
    VOS_UINT32 i = 0;
    VOS_UINT16 usOffset = 0;

    for(i = 0; i < gstPBCtrlInfo.ulEMLFileNum; i++)
    {
        if(usEMLFileId == gstPBCtrlInfo.astEMLInfo[i].usEMLFileID)
        {
            break;
        }
    }

    if((i >= gstPBCtrlInfo.ulEMLFileNum)
        ||(VOS_NULL_PTR == gstEMLContent.pContent))
    {
        return VOS_ERR;
    }

    usOffset = (VOS_UINT16)((i*gstPBCtrlInfo.astEMLInfo[i].ucRecordNum) + ucRecordNum);

    *ppEMLContent = &gstEMLContent.pContent[(usOffset-1)*gstEMLContent.ucRecordLen];

    return VOS_OK;

}

/*****************************************************************************
函 数 名  : SI_PB_FindUnusedExtRecord
功能描述  : 从EXT文件的缓存中找到第一个可以使用的空闲记录
输入参数  : 无
输出参数  :
返 回 值  : VOS_OK
            VOS_ERR
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2009年5月9日
    作    者   : h59254
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32  SI_PB_FindUnusedExtRecord(SI_EXT_CONTENT_STRU *pstEXTContent,
                                                    VOS_UINT8 *pucRecord,
                                                    VOS_UINT8 ucRecordCount)
{
    VOS_UINT32 ucCountFreeRec = 1;
    VOS_UINT8  *pContent;
    VOS_UINT8  i;

    /* 已使用记录数与最大记录数相等时表明已经没有可以使用的EXT记录 */
    if( pstEXTContent->usExtTotalNum == pstEXTContent->usExtUsedNum )
    {
        *pucRecord = 0xFF;

         return VOS_ERR;
    }

    pContent = pstEXTContent->pExtContent;

    if(VOS_NULL_PTR == pContent)
    {
        *pucRecord = 0xFF;

         return VOS_ERR;
    }

    /* 根据EXT文件的第二个字节来判断是否为空记录 */
    for( i = 0 ; i < pstEXTContent->usExtTotalNum ; i++ )
    {
        if( 0xFF == pContent[1] )
        {
            if(ucCountFreeRec == ucRecordCount)
            {
                break;
            }
            else
            {
                ucCountFreeRec++;
            }
        }

        pContent += SI_PB_EXT_LEN;
    }

    if( i < pstEXTContent->usExtTotalNum )
    {
        *pucRecord = i + 1;

        return VOS_OK;
    }
    else
    {
        *pucRecord = 0xFF;

        return VOS_ERR;
    }
}

/*****************************************************************************
函 数 名  :SI_PB_AsciiToBcd

功能描述  :转换ASCII码为BCD码

输入参数  :pucAsciiNum:转换的Ascii内容
           ucAsciiNumLen:转换的长度

输出参数  :pucBcdNum:转换的结果内容
           pucBcdNumLen:转换的结果长度

返 回 值      :无

调用函数  :无

被调函数  :

修订记录  :
1. 日    期   : 2007年10月15日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_VOID SI_PB_AsciiToBcd(VOS_UINT8 *pucAsciiNum, VOS_UINT8 ucAsciiNumLen, VOS_UINT8 *pucBcdNum, VOS_UINT8 *pucBcdNumLen)
{

    VOS_UINT8     i, k;
    VOS_UINT8     *pucTemp;

    pucTemp = pucBcdNum;

    for (i=0; i<ucAsciiNumLen; i++)
    {
        k = i % 2;

        if ((*(pucAsciiNum + i) >= 0x30) && (*(pucAsciiNum + i) <= 0x39))/*转换数字*/
        {
            if(k == 0)
            {
                *(pucTemp + (i / 2) ) = *(pucAsciiNum + i) - 0x30;
            }
            else
            {
                *(pucTemp + (i / 2) ) = (VOS_UINT8)(((VOS_UINT8)(*(pucAsciiNum + i) - 0x30) << 4) | *(pucTemp + (i / 2)));
            }
        }
        else if('*' == *(pucAsciiNum + i))  /*转换*字符*/
        {
            if(k == 0)
            {
                *(pucTemp + (i/2)) = 0xa;
            }
            else
            {
                *(pucTemp + (i/2)) = (0xa << 4) | *(pucTemp + (i/2));
            }
        }
        else if('#' == *(pucAsciiNum + i))  /*转换#字符*/
        {
            if(k == 0)
            {
                *(pucTemp + (i/2)) = 0xb;
            }
            else
            {
                *(pucTemp + (i/2)) = (0xb << 4) | *(pucTemp + (i/2));
            }
        }
        else if('?' == *(pucAsciiNum + i))  /*转换?字符*/
        {
            if(k == 0)
            {
                *(pucTemp + (i/2)) = 0xd;
            }
            else
            {
                *(pucTemp + (i/2)) = (0xd << 4) | *(pucTemp + (i/2));
            }
        }
        else if (('P' == *(pucAsciiNum + i))
             || ('p' == *(pucAsciiNum + i))
             || (',' == *(pucAsciiNum + i)) ) /*转换PAUSE字符*/
        {
            if(k == 0)
            {
                *(pucTemp + (i/2)) = 0xc;
            }
            else
            {
                *(pucTemp + (i/2)) = (0xc << 4) | *(pucTemp + (i/2));
            }
        }
        else                                        /*不能识别的字符*/
        {
            PB_WARNING_LOG("SI_PB_AsciiToBcd: The Char is Not Suspensory");/*打印警告*/
        }
    }

    *pucBcdNumLen = ucAsciiNumLen/2;

    if((ucAsciiNumLen % 2) == 1)    /*奇数字节后面添F*/
    {
        *(pucTemp + (ucAsciiNumLen / 2)) = 0xf0 | *(pucTemp + (ucAsciiNumLen / 2));

        (*pucBcdNumLen)++;
    }

    return;
}

/*****************************************************************************
函 数 名  :SI_FindMultiTagInBERTLV

功能描述  :在SimpleTLV数据结构中查询当前的Tag，返回实际数据长度的偏移

输入参数  :ucDataBuf:   数据内容
           ucTag:        查询的Tag
           ulDataLen:   数据总长度

输出参数  :无

返 回 值  :USIMM_TAGNOTFOUND
           找到Tag的个数

调用函数  :无

修订记录  :
1. 日    期   : 2009年05月23日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_FindMultiTagInBERTLV(VOS_UINT8 *pType1TagAddr, VOS_UINT8 ucTag,
                                            VOS_UINT8 *pucOffset,VOS_UINT8 ucTagCount)
{
    VOS_UINT8  i;
    VOS_UINT8 *pucDataBuf;
    VOS_UINT8  ucFindCount = 0;
    VOS_UINT32 ulDataLen;

    pucDataBuf = pType1TagAddr + 2;
    ulDataLen  = pType1TagAddr[1];

    for(i=0; (i < ulDataLen)&&(ucFindCount < ucTagCount);)
    {
        if(pucDataBuf[i] == ucTag)   /*返回长度字节偏移*/
        {
            pucOffset[ucFindCount] = i + 1;

            ucFindCount++;
        }

        i += pucDataBuf[i+1] + 2; /*跳到下一个Tag*/
    }

    return (0 == ucFindCount)?SI_TAGNOTFOUND:ucFindCount;
}

/*****************************************************************************
函 数 名  :SI_FindTagInBERTLV

功能描述  :在SimpleTLV数据结构中查询当前的Tag，返回实际数据长度的偏移

输入参数  :ucDataBuf:   数据内容
           ucTag:        查询的Tag
           ulDataLen:   数据总长度

输出参数  :无

返 回 值  :USIMM_TAGNOTFOUND
           长度字节的偏移

调用函数  :无

修订记录  :
1. 日    期   : 2007年10月20日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_FindTagInBERTLV(VOS_UINT8 *pucDataBuf, VOS_UINT8 ucTag, VOS_UINT32 ulDataLen)
{
    VOS_UINT32 i;

    for(i=0; i<ulDataLen;)
    {
        if(pucDataBuf[i] == ucTag)   /*返回长度字节偏移*/
        {
            return (i+1);
        }
        else
        {
            i += pucDataBuf[i+1] + 2; /*跳到下一个Tag*/
        }
    }

    return SI_TAGNOTFOUND;
}

/*****************************************************************************
函 数 名  :SI_FindType2FileTagNum

功能描述  :在Type2 TLV结构中找到对应Tag的是TLV文件中第几个文件

输入参数  :ucDataBuf:   数据内容
           ucTag:        查询的Tag
           ulDataLen:   数据总长度

输出参数  :无

返 回 值  :对应Tag在TLV结构中属于第几个文件

调用函数  :无

修订记录  :
1. 日    期   : 2009年06月05日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_FindType2FileTagNum(VOS_UINT8 *pucDataBuf, VOS_UINT8 ucTag, VOS_UINT32 ulDataLen)
{
    VOS_UINT32 i;
    VOS_UINT32 ulTagNum = 1;

    for(i=0; i<ulDataLen;)
    {
        if(pucDataBuf[i] == ucTag)   /*返回Tag Num*/
        {
            return ulTagNum;
        }
        else
        {
            ulTagNum++;
            i += pucDataBuf[i+1] + 2; /*跳到下一个Tag*/
        }
    }

    return SI_TAGNOTFOUND;
}


/*****************************************************************************
函 数 名  : SI_PB_DecodeEFPBR_AdnContent
功能描述  : 从A8的TAG中解析ADN文件信息
输入参数  : PBR文件内容
输出参数  :
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2009年6月15日
    作    者   : h59254
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_DecodeEFPBR_AdnContent(VOS_UINT8  *pType1TagAddr, VOS_UINT32 i)
{
    VOS_UINT32 ulOffset;

    ulOffset = SI_FindTagInBERTLV(&pType1TagAddr[2], EFADNDO_TAG, pType1TagAddr[1]);/*查询当前的ADN文件ID*/

    if(SI_TAGNOTFOUND == ulOffset)     /*未找到信息*/
    {
        PB_ERROR_LOG("SI_PB_DecodeEFPBR_AdnContent: Could Not Find the EFADNDO_TAG Tag");

        return ulOffset;
    }

    gstPBCtrlInfo.astADNInfo[i].usFileID = ((pType1TagAddr[ulOffset+3]<<0x08)&0xFF00)+pType1TagAddr[ulOffset+4];

    /*如果有SFI，需要记录下来*/
    if(0x03 == pType1TagAddr[ulOffset+2])
    {
        gstPBCtrlInfo.astADNInfo[i].ucSFI = pType1TagAddr[ulOffset+5];
    }

    gstPBCtrlInfo.ulADNFileNum++;

    return VOS_OK;
}


/*****************************************************************************
函 数 名  : SI_PB_DecodeEFPBR_UidContent
功能描述  : 从A8的TAG中解析UID文件信息
输入参数  : PBR文件内容
输出参数  :
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2009年6月15日
    作    者   : h59254
    修改内容   : Creat
*****************************************************************************/
VOS_VOID SI_PB_DecodeEFPBR_UidContent(VOS_UINT8 * pType1TagAddr, VOS_UINT32 i)
{
    VOS_UINT32 ulOffset;

    ulOffset = SI_FindTagInBERTLV(&pType1TagAddr[2], EFUIDDO_TAG, pType1TagAddr[1]);/*查询当前的UID文件ID*/

    if(SI_TAGNOTFOUND == ulOffset) /*未找到信息*/
    {
        PB_WARNING_LOG("SI_PB_DecodeEFPBR_UidContent: Could Not Find the EFUIDDO_TAG Tag");

        gstPBCtrlInfo.astUIDInfo[i].usFileID = 0xFFFF;
    }
    else
    {
        gstPBCtrlInfo.astUIDInfo[i].usFileID = ((pType1TagAddr[ulOffset+3]<<0x08)&0xFF00)+pType1TagAddr[ulOffset+4];
    }
}

/*****************************************************************************
函 数 名  : SI_PB_DecodeEFPBR_PbcContent
功能描述  : 从A8的TAG中解析PBC文件信息
输入参数  : PBR文件内容
输出参数  :
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2009年6月15日
    作    者   : h59254
    修改内容   : Creat
*****************************************************************************/
VOS_VOID SI_PB_DecodeEFPBR_PbcContent(VOS_UINT8 * pType1TagAddr, VOS_UINT32 i)
{
    VOS_UINT32 ulOffset;

    ulOffset = SI_FindTagInBERTLV(&pType1TagAddr[2], EFPBCDO_TAG, pType1TagAddr[1]);/*查询当前的PBC文件ID*/

    if(SI_TAGNOTFOUND == ulOffset) /*未找到信息*/
    {
        PB_WARNING_LOG("SI_PB_DecodeEFPBR_PbcContent: Could Not Find the EFUIDDO_TAG Tag");

        gstPBCtrlInfo.astPBCInfo[i].usFileID = 0xFFFF;

        gucPBCStatus = VOS_FALSE;
    }
    else if(VOS_TRUE == SI_PB_CheckSupportAP())
    {
        gstPBCtrlInfo.astPBCInfo[i].usFileID = 0xFFFF;

        gucPBCStatus = VOS_FALSE;
    }
    else
    {
        gstPBCtrlInfo.astPBCInfo[i].usFileID = ((pType1TagAddr[ulOffset+3]<<0x08)&0xFF00)+pType1TagAddr[ulOffset+4];
    }
}

/*****************************************************************************
函 数 名  : SI_PB_DecodeEFPBR_PbcContent
功能描述  : 从A8的TAG中解析AIP文件信息
输入参数  : PBR文件内容
输出参数  :
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2009年6月15日
    作    者   : h59254
    修改内容   : Creat
*****************************************************************************/
VOS_VOID SI_PB_DecodeEFPBR_IapContent(VOS_UINT8 * pType1TagAddr, VOS_UINT32 i)
{
    VOS_UINT32 ulOffset;

    ulOffset = SI_FindTagInBERTLV(&pType1TagAddr[2], EFIAPDO_TAG, pType1TagAddr[1]);/*查询当前的IAP文件ID*/

    if(SI_TAGNOTFOUND == ulOffset) /*未找到信息*/
    {
        PB_WARNING_LOG("SI_PB_DecodeEFPBR_IapContent: Could Not Find the EFIAPDO_TAG Tag");
    }
    else
    {
        gstPBCtrlInfo.astIAPInfo[i].usIAPFileID = ((pType1TagAddr[ulOffset+3]<<0x08)&0xFF00)+pType1TagAddr[ulOffset+4];

        gstPBCtrlInfo.ulIAPFileNum++;
    }
}

/*****************************************************************************
函 数 名  : SI_PB_DecodeEFPBR_PbcContent
功能描述  : 从A8的TAG中解析ANR文件信息
输入参数  : PBR文件内容
输出参数  :
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2009年6月15日
    作    者   : h59254
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_DecodeType1EFPBR_AnrContent(VOS_UINT8 * pType1TagAddr, VOS_UINT32 i, VOS_UINT8 *pucOffset)
{
    VOS_UINT32 ulANRCount; /*记录每条记录中的ANR个数*/
    VOS_UINT32 ulOffset;
    VOS_UINT32 j;

    ulANRCount = SI_FindMultiTagInBERTLV(pType1TagAddr, (VOS_UINT8)EFANRDO_TAG,
                                       pucOffset,(VOS_UINT8)SI_PB_ANR_MAX);/*查询当前的ANR文件*/

    if(SI_TAGNOTFOUND == ulANRCount) /*未找到信息*/
    {
        PB_NORMAL_LOG("SI_PB_DecodeType1EFPBR_AnrContent: Could Not Find the EFANRDO_TAG Tag");
    }
    else
    {
        ulANRCount = (ulANRCount > SI_PB_ANRMAX)?SI_PB_ANRMAX:ulANRCount;

        for(j = 0; j < ulANRCount; j++)
        {
            ulOffset = pucOffset[j];

            gstPBCtrlInfo.astANRInfo[i][j].usANRFileID  = ((pType1TagAddr[ulOffset+3]<<0x08)&0xFF00)+pType1TagAddr[ulOffset+4];
            gstPBCtrlInfo.astANRInfo[i][j].enANRType = PB_FILE_TYPE1;
            gstPBCtrlInfo.ulANRFileNum++;
        }
    }

    return ulANRCount;
}

/*****************************************************************************
函 数 名  : SI_PB_DecodeType2EFPBR_AnrContent
功能描述  : 从A9的TAG中解析ANR文件信息
输入参数  : PBR文件内容
输出参数  :
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2009年9月5日
    作    者   : m00128685
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_DecodeType2EFPBR_AnrContent(VOS_UINT8 * pType2TagAddr, VOS_UINT32 i, VOS_UINT8 *pucOffset)
{
    VOS_UINT32 ulANRCount; /*记录每条记录中的ANR个数*/
    VOS_UINT32 ulOffset;
    VOS_UINT32 j;

    ulANRCount = SI_FindMultiTagInBERTLV(pType2TagAddr, (VOS_UINT8)EFANRDO_TAG,
                                       pucOffset,(VOS_UINT8)SI_PB_ANR_MAX);/*查询当前的ANR文件*/

    if(SI_TAGNOTFOUND == ulANRCount) /*未找到信息*/
    {
        PB_NORMAL_LOG("SI_PB_DecodeType2EFPBR_AnrContent: Could Not Find the EFANRDO_TAG Tag");
    }
    else
    {
        ulANRCount = (ulANRCount > SI_PB_ANRMAX)?SI_PB_ANRMAX:ulANRCount;

        for(j = 0; j < ulANRCount; j++)
        {
            ulOffset = pucOffset[j];

            gstPBCtrlInfo.astANRInfo[i][j].usANRFileID  = ((pType2TagAddr[ulOffset+3]<<0x08)&0xFF00)+pType2TagAddr[ulOffset+4];
            gstPBCtrlInfo.astANRInfo[i][j].enANRType = PB_FILE_TYPE2;
            gstPBCtrlInfo.ulANRFileNum++;

            gstPBCtrlInfo.astANRInfo[i][j].ulANRTagNum =
            SI_FindType2FileTagNum(pType2TagAddr+2, EFANRDO_TAG, pType2TagAddr[1]);
        }
    }

    return ulANRCount;
}

/*****************************************************************************
函 数 名  : SI_PB_DecodeEFPBR_PbcContent
功能描述  : 从AA的TAG中解析EXT1文件信息
输入参数  : PBR文件内容
输出参数  :
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2009年6月15日
    作    者   : h59254
    修改内容   : Creat
*****************************************************************************/
VOS_VOID SI_PB_DecodeEFPBR_ExtContent(VOS_UINT8  *pType3TagAddr)
{
    VOS_UINT32 ulOffset;

    /* 所有的ADN文件都只对应于同一个EXT1文件,只要在一个PBR的记录里找到就可以了 */
    ulOffset = SI_FindTagInBERTLV(pType3TagAddr+2, EFEXT1DO_TAG, pType3TagAddr[1]);/*查询当前的EXT文件ID*/

    /*未找到信息*/
    if(SI_TAGNOTFOUND == ulOffset)
    {
        PB_WARNING_LOG("SI_PB_DecodeEFPBR_ExtContent: Could Not Find the EFEXTDO_TAG Tag");

        gstPBCtrlInfo.usEXT1FileID = 0xFFFF;
        gastEXTContent[PB_ADN_CONTENT].usExtFileId  = 0xFFFF;
        gastEXTContent[PB_ADN_CONTENT].usExtFlag    = SI_PB_FILE_NOT_EXIST;
    }
    else if( SI_PB_FILE_EXIST == gastEXTContent[PB_ADN_CONTENT].usExtFlag )
    {
        /*do nothing*/
    }
    else
    {
        gstPBCtrlInfo.usEXT1FileID = ((pType3TagAddr[ulOffset+3]<<0x08)&0xFF00)+pType3TagAddr[ulOffset+4];
        gastEXTContent[PB_ADN_CONTENT].usExtFlag = SI_PB_FILE_EXIST;
    }
}

/*****************************************************************************
函 数 名  : SI_PB_DecodeType2EFPBR_EmailContent
功能描述  : 从A9的TAG中解析EMAIL文件信息
输入参数  : PBR文件内容
输出参数  :
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2009年6月15日
    作    者   : h59254
    修改内容   : Creat
*****************************************************************************/
VOS_VOID SI_PB_DecodeType2EFPBR_EmailContent(VOS_UINT8 * pType2TagAddr, VOS_UINT32 i)
{
    VOS_UINT32 ulOffset;

    ulOffset = SI_FindTagInBERTLV(pType2TagAddr+2, EFEMAILDO_TAG, pType2TagAddr[1]);/*查询当前的EXT文件ID*/

    /*未找到信息*/
    if(SI_TAGNOTFOUND == ulOffset)
    {
        PB_NORMAL_LOG("SI_PB_DecodeType2EFPBR_EmailContent: Could Not Find the EFEMAILDO_TAG Tag");
    }
    else
    {
        gstPBCtrlInfo.astEMLInfo[i].usEMLFileID = ((pType2TagAddr[ulOffset+3]<<0x08)&0xFF00)+pType2TagAddr[ulOffset+4];
        gstPBCtrlInfo.ulEMLFileNum++;

        gstPBCtrlInfo.astEMLInfo[i].enEMLType = PB_FILE_TYPE2;

        gstPBCtrlInfo.astEMLInfo[i].ulEMLTagNum =
        SI_FindType2FileTagNum(pType2TagAddr+2, EFEMAILDO_TAG, pType2TagAddr[1]);
    }
}

/*****************************************************************************
函 数 名  : SI_PB_DecodeType1EFPBR_EmailContent
功能描述  : 从A8的TAG中解析EMAIL文件信息
输入参数  : PBR文件内容
输出参数  :
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2009年6月26日
    作    者   : m00128685
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_DecodeType1EFPBR_EmailContent(VOS_UINT8 * pType2TagAddr, VOS_UINT32 i)
{
    VOS_UINT32 ulOffset;

    ulOffset = SI_FindTagInBERTLV(pType2TagAddr+2, EFEMAILDO_TAG, pType2TagAddr[1]);/*查询当前的EXT文件ID*/

    /*未找到信息*/
    if(SI_TAGNOTFOUND == ulOffset)
    {
        PB_NORMAL_LOG("SI_PB_DecodeType1EFPBR_EmailContent: Could Not Find the EFEMAILDO_TAG Tag");

        return SI_TAGNOTFOUND;
    }

    gstPBCtrlInfo.astEMLInfo[i].usEMLFileID = ((pType2TagAddr[ulOffset+3]<<0x08)&0xFF00)+pType2TagAddr[ulOffset+4];
    gstPBCtrlInfo.ulEMLFileNum++;

    gstPBCtrlInfo.astEMLInfo[i].enEMLType = PB_FILE_TYPE1;

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :SI_PB_DecodeEFPBR

功能描述  :解析EFPBR的内容，获取ADN /UID的文件ID

输入参数  :ucRecordNum:解析内容的记录条数
           ucRecordLen:解析的内容的记录长度
           pContent:解析的文件内容

输出参数  :无

返 回 值  :VOS_OK 解析成功
           VOS_ERR 解析失败

调用函数  :无

被调函数  :

修订记录  :
1. 日    期   : 2007年10月15日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_DecodeEFPBR(VOS_UINT8 ucRecordNum, VOS_UINT8 ucRecordLen, VOS_UINT8 *pContent)
{
    VOS_UINT32 i;
    VOS_UINT32 j;
    VOS_UINT8  *ptemp = pContent;
    VOS_UINT8  *pType1TagAddr;
    VOS_UINT8  *pType2TagAddr;
    VOS_UINT8  *pType3TagAddr;
    VOS_UINT8  aucANROffset[SI_PB_ANR_MAX];
    VOS_UINT32 ulType1EMLFlag = VOS_OK;
    VOS_UINT32 ulType1ANRFlag = VOS_OK;
    VOS_UINT32 ulOffset;

    gstPBCtrlInfo.ulADNFileNum  = 0;

    for(i=0; i<ucRecordNum; i++,(ptemp+= ucRecordLen))
    {
        if((ptemp[0]&0xF0) != 0xA0 ) /*判断当前的记录是否有效*/
        {
            continue;
        }

        /*解析Tpye1文件记录*/
        ulOffset = SI_FindTagInBERTLV(ptemp, PB_FILE_TYPE1, ucRecordLen);

        if(SI_TAGNOTFOUND == ulOffset)
        {
            PB_ERROR_LOG("SI_PB_DecodeEFPBR: Could Not Find the 0xA8 Tag");

            continue;
        }

        pType1TagAddr = (ptemp + ulOffset) - 1;

        if(SI_TAGNOTFOUND == SI_PB_DecodeEFPBR_AdnContent(pType1TagAddr, i))
        {
            continue;
        }

        ulType1EMLFlag = SI_PB_DecodeType1EFPBR_EmailContent(pType1TagAddr, i);

        SI_PB_DecodeEFPBR_UidContent(pType1TagAddr, i);

        SI_PB_DecodeEFPBR_PbcContent(pType1TagAddr, i);

        SI_PB_DecodeEFPBR_IapContent(pType1TagAddr, i);

        ulType1ANRFlag = SI_PB_DecodeType1EFPBR_AnrContent(pType1TagAddr, i, aucANROffset);

        /*解析Tpye2文件记录*/
        ulOffset = SI_FindTagInBERTLV(ptemp, PB_FILE_TYPE2, ucRecordLen);

        /*Type2 类型文件不存在或已解析出Type1类型 Email信息*/
        if(SI_TAGNOTFOUND == ulOffset)
        {
            PB_NORMAL_LOG("SI_PB_DecodeEFPBR: Could Not Find the Type2 Tag");
        }
        else
        {
            pType2TagAddr = (ptemp + ulOffset) - 1;

            if(SI_TAGNOTFOUND == ulType1EMLFlag)
            {
                SI_PB_DecodeType2EFPBR_EmailContent(pType2TagAddr, i);
            }

            if(SI_TAGNOTFOUND == ulType1ANRFlag)
            {
                /*lint -e534*/
                SI_PB_DecodeType2EFPBR_AnrContent(pType2TagAddr, i, aucANROffset);
                /*lint +e534*/
            }
        }

        /*解析Tpye3文件记录*/
        ulOffset = SI_FindTagInBERTLV(ptemp, PB_FILE_TYPE3, ucRecordLen);

        if(SI_TAGNOTFOUND == ulOffset)
        {
            PB_ERROR_LOG("SI_PB_DecodeEFPBR: Could Not Find the AA Tag");

            gstPBCtrlInfo.usEXT1FileID = 0xFFFF;
            gastEXTContent[PB_ADN_CONTENT].usExtFileId  = 0xFFFF;
            gastEXTContent[PB_ADN_CONTENT].usExtFlag    = SI_PB_FILE_NOT_EXIST;
        }
        else
        {
            pType3TagAddr = (ptemp + ulOffset) - 1;

            SI_PB_DecodeEFPBR_ExtContent(pType3TagAddr);
        }
    }

    if ( 0 == gstPBCtrlInfo.ulADNFileNum )
    {
        return VOS_ERR;
    }

    for(i = gstPBCtrlInfo.ulADNFileNum -1; i != 0; i--)
    {
        for(j = 0; j < SI_PB_ANRMAX; j++)
        {
            if((gstPBCtrlInfo.astANRInfo[i][j].usANRFileID
               == gstPBCtrlInfo.astANRInfo[i-1][j].usANRFileID)
               &&(0 != gstPBCtrlInfo.astANRInfo[i][j].usANRFileID))
            {
                gstPBCtrlInfo.astANRInfo[i][j].usANRFileID = 0;
                gstPBCtrlInfo.astANRInfo[i][j].ucRecordNum = 0;
                gstPBCtrlInfo.astANRInfo[i][j].ucRecordLen = 0;

                gstPBCtrlInfo.ulANRFileNum--;
            }
        }

        if((gstPBCtrlInfo.astEMLInfo[i].usEMLFileID
           == gstPBCtrlInfo.astEMLInfo[i-1].usEMLFileID)
           &&(0 != gstPBCtrlInfo.astEMLInfo[i].usEMLFileID))
        {
            gstPBCtrlInfo.astEMLInfo[i].usEMLFileID = 0;
            gstPBCtrlInfo.astEMLInfo[i].ucRecordLen = 0;
            gstPBCtrlInfo.astEMLInfo[i].ucRecordNum = 0;

            gstPBCtrlInfo.ulEMLFileNum--;
        }
    }

    /* 对于USIM卡，电话本文件的初始化优先采用SEARCH文件实现，
       初始化过程中出现SEARCH不成功时转为正常读取初始化 */
    gstPBInitState.enPBSearchState = PB_SEARCH_ENABLE;

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : SI_PB_DecodeEFPBCRecord
功能描述  : 根据USIMM模块主动上报的卡类型，确定下一个初始化步骤
输入参数  : 无
输出参数  : gstPBInitState
返 回 值  : VOS_Ok
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2008年10月31日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_VOID SI_PB_DecodeEFPBCRecord(VOS_UINT8 *pucContent, VOS_UINT8 ucRecordNum)
{

    if( 1 == ((*pucContent)&0x1) )
    {
        /*从第一个元素开始记录*/
        gstPBInitState.stPBCUpdate.aucRecord[++gstPBInitState.stPBCUpdate.ucEntryChangeNum] = ucRecordNum;

    }

    return;
}

/*****************************************************************************
函 数 名  : SI_PB_DecodeEFUIDRecord
功能描述  : 根据USIMM模块主动上报的卡类型，确定下一个初始化步骤
输入参数  : 无
输出参数  : gstPBInitState
返 回 值  : VOS_Ok
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2008年10月31日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_VOID SI_PB_DecodeEFUIDRecord(VOS_UINT8 *pucContent)
{
    VOS_UINT16 usEFUIDValue = 0;

    usEFUIDValue = *pucContent++;

    usEFUIDValue <<= 8;

    usEFUIDValue |= *pucContent++;

    if(usEFUIDValue == 0xFFFF)
    {
        return;
    }

    if(gstPBCtrlInfo.usUIDMaxValue < usEFUIDValue)
    {
        gstPBCtrlInfo.usUIDMaxValue = usEFUIDValue;
    }

    return;
}

/*****************************************************************************
函 数 名  :SI_PB_JudgeANDFid

功能描述  :判断是否为ADN

输入参数  :pstPBContent 转换的电话本内容信息
           ucIndex 转换的电话本的索引号/记录号
           pContent 转换的电话本内容

输出参数  :pstRecord 转换的电话本数据结构

返 回 值  :VOS_OK 解析成功
           VOS_ERR 解析失败

调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2009年06月08日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_JudgeADNFid(VOS_UINT16 usFileId)
{
    VOS_UINT32 i;

    for(i = 0; i < gstPBCtrlInfo.ulADNFileNum; i++)
    {
        if(usFileId == gstPBCtrlInfo.astADNInfo[i].usFileID)
        {
            return VOS_OK;
        }
    }

    return VOS_ERR;
}

/*****************************************************************************
函 数 名  :SI_PB_JudgeEXTFid

功能描述  :判断是否为指定电话本的EXT文件

输入参数  :pstPBContent 转换的电话本内容信息
           ucIndex 转换的电话本的索引号/记录号
           pContent 转换的电话本内容

输出参数  :pstRecord 转换的电话本数据结构

返 回 值  :VOS_OK 解析成功
           VOS_ERR 解析失败

调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2009年06月08日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_JudgeEXTFid(VOS_UINT16 usFileId, VOS_UINT16 usOffset)
{

    if(usFileId == gastEXTContent[usOffset].usExtFileId)
    {
        return VOS_OK;
    }

    return VOS_ERR;
}

/*****************************************************************************
函 数 名  :SI_PB_JudgeIAPFid

功能描述  :判断是否为ADN

输入参数  :pstPBContent 转换的电话本内容信息
           ucIndex 转换的电话本的索引号/记录号
           pContent 转换的电话本内容

输出参数  :pstRecord 转换的电话本数据结构

返 回 值  :VOS_OK 解析成功
           VOS_ERR 解析失败

调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2009年06月08日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_JudgeIAPFid(VOS_UINT16 usFileId)
{
    VOS_UINT32 i;

    for(i = 0; i < gstPBCtrlInfo.ulADNFileNum; i++)
    {
        if(usFileId == gstPBCtrlInfo.astIAPInfo[i].usIAPFileID)
        {
            return VOS_OK;
        }
    }

    return VOS_ERR;
}

/*****************************************************************************
函 数 名  :SI_PB_GetEXTContentFromReq

功能描述  :根据记录号从请求结构gstPBReqUnit中获取EXT文件的更新请求缓存内容

输入参数  :pstPBContent 转换的电话本内容信息
           ucIndex 转换的电话本的索引号/记录号
           pContent 转换的电话本内容

输出参数  :pstRecord 转换的电话本数据结构

返 回 值  :VOS_OK 解析成功
           VOS_ERR 解析失败

调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2009年06月08日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_GetEXTContentFromReq(VOS_UINT8 ucRecordNum, VOS_UINT8 **ppucContent)
{
    VOS_UINT32 i;

    if(ucRecordNum == gstPBReqUnit.usExtIndex)
    {
        *ppucContent = gstPBReqUnit.aucEXTContent;

        gstPBReqUnit.usExtIndex = 0;/*清为无效值*/

        return VOS_OK;
    }

    for(i = 0; i < SI_PB_ANR_MAX; i++)
    {
        if(ucRecordNum == gstPBReqUnit.stSPBReq.usANRExtIndex[i])
        {
            *ppucContent = gstPBReqUnit.stSPBReq.aucANRExtContent[i];

            gstPBReqUnit.stSPBReq.usANRExtIndex[i] = 0;/*清为无效值*/
            return VOS_OK;
        }
    }

    return VOS_ERR;
}

/*****************************************************************************
函 数 名  :SI_PB_SetBitToBuf
功能描述  :在数据中设定Bit位的值　
输入参数  :ucDataBuf:   数据内容
           ulBitNo:     Bit号,从1开始
           ulValue:     需要设置的值,0或1
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2009年5月19日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_VOID SI_PB_SetBitToBuf(VOS_UINT8 *pucDataBuf, VOS_UINT32 ulBitNo,VOS_UINT32 ulValue)
{
    VOS_UINT32  ulOffset;
    VOS_UINT8   ucBit;

    if(VOS_NULL_PTR == pucDataBuf)
    {
        PB_ERROR_LOG("SI_PB_SetBitToBuf: Input Null Ptr");

        return;
    }

    ulOffset = (ulBitNo - 1)/ 8;

    ucBit    = (VOS_UINT8)((ulBitNo - 1)%8);

    if(0 != ulValue)
    {
        /*lint -e701 */
        pucDataBuf[ulOffset] |= (VOS_UINT8)(0x1<<ucBit);
        /*lint +e701 */
    }
    else
    {
        /*lint -e701 */
        pucDataBuf[ulOffset] &= (~(VOS_UINT8)(0x1<<ucBit));
        /*lint +e701 */
    }

    return;
}

/*****************************************************************************
函 数 名  :SI_PB_CheckFdnNumLen
功能描述  :比对FDN号码长度
输入参数  :ulCmpNumLen:发起业务号码串
           ulFdnNumLen:FDN号码长度
输出参数  :无
返 回 值  : VOS_ERR、VOS_OK
修订记录  :
1. 日    期   : 2012年2月22日
    作    者   : w00184875
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_CheckFdnNumLen(
    VOS_UINT32                          ulFdnNumLen,
    VOS_UINT32                          ulCmpNumLen)
{
    USIMM_FEATURE_CFG_STRU              stUsimmFeatureCfg;

    if (VOS_OK != NV_Read(en_NV_Item_Usim_Support_Feature_Config,
                         (VOS_VOID*)&stUsimmFeatureCfg, sizeof(stUsimmFeatureCfg)))
    {
        (VOS_VOID)VOS_MemSet(stUsimmFeatureCfg.unCfg.aulValue , VOS_FALSE, sizeof(stUsimmFeatureCfg.unCfg.aulValue));
    }

    /*如果不支持FDN号码完全匹配， 存储的FDN号码长度大于业务号码，返回失败 */
    if(VOS_FALSE == stUsimmFeatureCfg.unCfg.stFeatureCfg.ulAtt_flg)
    {        
        if (ulFdnNumLen > ulCmpNumLen)
        {
           return VOS_ERR;
        }
    }    
    /*ATT FDN号码完全匹配，存储的FDN号码长度和业务号码长度不一致，则直接返回*/
    else
    {
        if (ulFdnNumLen != ulCmpNumLen)
        {
            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :SI_PB_BcdCompare
功能描述  :比对BCD码
输入参数  :
输出参数  :
返 回 值  : 0:有效、1:无效
修订记录  :
1. 日    期   : 2012年3月8日
    作    者   : w00184875
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_BcdCompare(VOS_UINT8 *pucBcdNumSrc, VOS_UINT8 ucBcdSrcLen, VOS_UINT8 *pucFdnBcdNum, VOS_UINT8 ucFdnBcdLen)
{
    VOS_UINT8                           ucDstIndex;
    VOS_UINT8                           ucFdnNumLen;
    VOS_UINT8                           ucCmpNumLen;
    VOS_UINT8                           aucFdnNum[SI_PB_NUM_LEN*2];
    VOS_UINT8                           aucCmpNum[SI_PB_NUM_LEN*2];

    /*lint -e534*/
    VOS_MemSet(aucFdnNum, (VOS_CHAR)0xFF, sizeof(aucFdnNum));

    VOS_MemSet(aucCmpNum, (VOS_CHAR)0xFF, sizeof(aucCmpNum));
    /*lint +e534*/

    /* 电话本最长支持40个号码，BCD码的长度最长20个字节 */
    if ((ucBcdSrcLen > SI_PB_NUM_LEN) || (ucFdnBcdLen > SI_PB_NUM_LEN))
    {
        return VOS_ERR;
    }

    /* 将输入的号码转换成ASCII码后再进行比较 */
    SI_PB_BcdToAscii(ucBcdSrcLen, pucBcdNumSrc, aucCmpNum, &ucCmpNumLen);

    /* 将输入的FDN号码转换成ASCII码后再进行比较 */
    SI_PB_BcdToAscii(ucFdnBcdLen, pucFdnBcdNum, aucFdnNum, &ucFdnNumLen);

    if (VOS_OK != SI_PB_CheckFdnNumLen(ucFdnNumLen, ucCmpNumLen))
    {
        return VOS_ERR;
    }

    /* 循环比较两个号码的ASCII码 */
    for (ucDstIndex = 0; ucDstIndex < ucFdnNumLen; ucDstIndex++)
    {
        /* 遇到'?'跳过比较，比较下一个号码.或者两个号码必须相等 */
        if ((aucFdnNum[ucDstIndex] == aucCmpNum[ucDstIndex])
            || ('?' == aucFdnNum[ucDstIndex]))
        {
            continue;
        }
        else
        {
            break;
        }
    }

    /* 如果比较到结尾判定成功 */
    if (ucFdnNumLen == ucDstIndex)
    {
        return VOS_OK;
    }

    return VOS_ERR;
}

/*****************************************************************************
函 数 名  :SI_PB_CheckFdn
功能描述  :比对FDN号码
输入参数  :pstFdnInfo:号码结构
输出参数  :无
返 回 值  : 0:有效、1:无效
修订记录  :
1. 日    期   : 2012年2月22日
    作    者   : w00184875
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_CheckEXT2(VOS_UINT8 ucExtRecord, VOS_UINT32 ulExtInfoNum, VOS_UINT8 *pucDstNum, VOS_UINT8 *pucExNumLen)
{
    VOS_UINT8                          *pExTemp;
    VOS_UINT8                           ucExNumLen;

    pExTemp = gastEXTContent[ulExtInfoNum].pExtContent;

    if (VOS_NULL_PTR == pExTemp)
    {
        PB_ERROR_LOG("SI_PB_CheckFdn: gastEXTContent is null.\r\n");
        return VOS_ERR;
    }

    if ((ucExtRecord > gastEXTContent[ulExtInfoNum].usExtTotalNum)
       || (0 == ucExtRecord))
    {
        PB_ERROR1_LOG("SI_PB_CheckFdn: ucExtRecord: %d is wrong .\r\n", ucExtRecord);
        return VOS_ERR;
    }

    pExTemp += (ucExtRecord - 1) * SI_PB_EXT_LEN;

    /* 判断EX号码长度 */
    if ((0xFF == *(pExTemp+1)) || (0x0 == *(pExTemp+1)))
    {
        PB_ERROR_LOG("SI_PB_CheckFdn: EXT NUM Length is error.\r\n");
        return VOS_ERR;
    }

    ucExNumLen = (*(pExTemp+1) > (SI_PB_NUM_LEN/2))?
                    (SI_PB_NUM_LEN/2) : *(pExTemp + 1);

    /*lint -e534*/
    VOS_MemCpy(pucDstNum, (pExTemp+2), ucExNumLen);
    /*lint +e534*/

    *pucExNumLen = ucExNumLen;

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :SI_PB_CheckFdn
功能描述  :比对FDN号码
输入参数  :pucNum:发起业务号码串
            ulNumLength:号码长度
输出参数  :无
返 回 值  : 0:有效、1:无效
修订记录  :
1. 日    期   : 2012年2月22日
    作    者   : w00184875
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_CheckFdn(VOS_UINT8 *pucNum, VOS_UINT32 ulNumLength)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucPBOffset=0;
    VOS_UINT16                          i;
    VOS_UINT8                          *pTemp;
    VOS_UINT8                          *pucFdnContent;
    VOS_UINT8                           aucNumber[SI_PB_NUM_LEN];
    VOS_UINT16                          usTotalNum;
    VOS_UINT8                           ucNumLen;
    VOS_UINT8                           ucExNumLen;
    VOS_UINT32                          ulExtInfoNum;
    VOS_UINT8                           ucExtRecord;

    SI_PB_MemSet(SI_PB_NUM_LEN, (VOS_UINT8)0xFF, aucNumber);
    ucNumLen = 0;

    /*当前电话本不存在或者初始化未完成*/
    ulResult = SI_PB_LocateRecord(PB_FDN, 1, 1, &ucPBOffset);
    if(VOS_OK != ulResult)
    {
        PB_ERROR_LOG("SI_PB_CheckFdn: SI_PB_LocateRecord Return Failed.\r\n");
        return VOS_ERR;
    }

    usTotalNum      = gastPBContent[ucPBOffset].usTotalNum;
    pucFdnContent   = gastPBContent[ucPBOffset].pContent;

    if (VOS_NULL_PTR == pucFdnContent)
    {
        PB_ERROR_LOG("SI_PB_CheckFdn: gastPBContent is null.\r\n");
        return VOS_ERR;
    }

    ulExtInfoNum = gastPBContent[ucPBOffset].ulExtInfoNum;

    /*在电话本记录中循环进行字符串匹配，一旦成功返回VOS_OK*/
    for(i=0; i<usTotalNum; i++)   /*根据数据结构最大长度循环*/
    {
        pTemp = pucFdnContent;
        pTemp += gastPBContent[ucPBOffset].ucNameLen;

        /*检查号码长度是否合法*/
        if ((0xFF == *pTemp)||(*pTemp < 2))
        {
            pucFdnContent += gastPBContent[ucPBOffset].ucRecordLen;

            continue;
        }

        ucNumLen = *pTemp - 1;

        ucNumLen = (ucNumLen > (SI_PB_NUM_LEN / 2))?(SI_PB_NUM_LEN / 2):ucNumLen;

        SI_PB_MemSet(SI_PB_NUM_LEN, (VOS_UINT8)0xFF, aucNumber);

        /*lint -e534*/
        VOS_MemCpy(aucNumber, pTemp+2, ucNumLen);
        /*lint +e534*/

        ucExtRecord = pucFdnContent[gastPBContent[ucPBOffset].ucRecordLen-1];

        /* 读入EX文件 */
        if (0xFF != ucExtRecord)
        {
            if (VOS_OK != SI_PB_CheckEXT2(ucExtRecord, ulExtInfoNum, &(aucNumber[ucNumLen]), &ucExNumLen))
            {
                return VOS_ERR;
            }

            ucNumLen += ucExNumLen;
        }

        /*比对字符*/
        if (VOS_OK == SI_PB_BcdCompare(pucNum, (VOS_UINT8)ulNumLength, aucNumber, ucNumLen))
        {
            PB_ERROR_LOG("SI_PB_CheckFdn: SI_PB_BcdCompare fail");

            return VOS_OK;
        }

        pucFdnContent   += gastPBContent[ucPBOffset].ucRecordLen;
    }

    return VOS_ERR;
}

/*****************************************************************************
函 数 名  :SI_PB_EcallNumberErrProc
功能描述  :ECALL号码错误处理
输入参数  :ulStorage:存储器类型
           ucListLen:索引列表长度
           pucList:索引列表
输出参数  :pucPBOffset:电话本控制结构偏移量
返 回 值  : 0:有效、1:无效
修订记录  :
1.  日    期   : 2014年04月25日
    作    者   : h59254
    修改内容   : Creat
*****************************************************************************/
/*lint -save -e958 */
VOS_UINT32 SI_PB_EcallNumberErrProc(SI_PB_STORATE_TYPE ulStorage, VOS_UINT8 ucListLen, VOS_UINT8 *pucList, VOS_UINT8 *pucPBOffset)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucPBOffset;

    if (VOS_OK != SI_PB_FindPBOffset(ulStorage, pucPBOffset))
    {
        PB_WARNING_LOG("SI_PB_EcallNumberErrProc: Locate PhoneBook Error");

        return TAF_ERR_ERROR;
    }

    ucPBOffset = *pucPBOffset;

    /* 当前的电话本没有初始化完毕 */
    if (PB_INITIALISED != gastPBContent[ucPBOffset].enInitialState)
    {
        PB_ERROR_LOG("SI_PB_EcallNumberErrProc:The PhoneBook is Not Initializtion");

        return TAF_ERR_SIM_BUSY;
    }

    /* 当前的电话本没有内容 */
    if (VOS_NULL_PTR == gastPBContent[ucPBOffset].pContent)
    {
        PB_ERROR_LOG("SI_PB_EcallNumberErrProc:The PhoneBook is Not Initializtion");

        return TAF_ERR_PB_NOT_INIT;
    }

    /* 输入的index不能超过最大记录数或为0 */
    for (i = 0; i < ucListLen; i++)
    {
        if ((pucList[i] > gastPBContent[ucPBOffset].usTotalNum)
            || (VOS_NULL == pucList[i]))
        {
            PB_ERROR_LOG("SI_PB_EcallNumberErrProc:Wrong Index");

            return TAF_ERR_PB_WRONG_INDEX;
        }
    }

    return TAF_ERR_NO_ERROR;
}
/*lint -restore */
/*****************************************************************************
函 数 名  :SI_PB_EcallNumberErrProc
功能描述  :ECALL号码错误处理
输入参数  :pstXdnContent:电话本控制结构
           pstEcallNum:ECALL号码返回结构
           ucListLen:索引列表长度
           pucList:索引列表
输出参数  :无
返 回 值  :无
修订记录  :
1.  日    期   : 2014年04月25日
    作    者   : h59254
    修改内容   : Creat
*****************************************************************************/
/*lint -save -e958 */
VOS_VOID SI_PB_GetEcallNumber(SI_PB_CONTENT_STRU *pstXdnContent, SI_PB_ECALL_NUM_STRU *pstEcallNum, VOS_UINT8 ucListLen, VOS_UINT8 *pucList)
{
    VOS_UINT8                          *pucContent;
    VOS_UINT8                          *pucTmp;
    VOS_UINT8                          *pucExtContent;
    VOS_UINT32                          ulExtInfoNum;
    VOS_UINT8                           ucRecordLen;
    VOS_UINT8                           ucExNumLen;
    VOS_UINT8                           ucExtRecord;
    VOS_UINT8                           i;


    pucContent = pstXdnContent->pContent;
    ucRecordLen= pstXdnContent->ucRecordLen;

    for (i = 0; i < ucListLen; i++)
    {
        pstEcallNum->ucIndex  = pucList[i];

        SI_PB_MemSet(SI_PB_NUM_LEN, (VOS_UINT8)0xFF, pstEcallNum->aucCallNumber);
/*lint -save -e961 */
        pucTmp = pucContent + (pstXdnContent->ucRecordLen) * (pucList[i] - 1);
/*lint -restore */
        ucExtRecord  = pucTmp[ucRecordLen-1];
        ulExtInfoNum = pstXdnContent->ulExtInfoNum;
        pucExtContent = gastEXTContent[ulExtInfoNum].pExtContent;

        ucExtRecord = ((VOS_NULL_PTR == pucExtContent) ? 0xFF : (ucExtRecord));

        if ((pucTmp[pstXdnContent->ucNameLen] < 2) || (0xFF == pucTmp[pstXdnContent->ucNameLen]))
        {
            pstEcallNum->ucLength = 0;
        }
        else if((0xFF != ucExtRecord)&&(0 != ucExtRecord)&&(VOS_NULL_PTR != pucExtContent)
                &&(ucExtRecord <= gastEXTContent[ulExtInfoNum].usExtTotalNum))
        {
            pucExtContent += (ucExtRecord - 1) * SI_PB_EXT_LEN;
            ucExNumLen = (*(pucExtContent + 1) > (SI_PB_NUM_LEN/2))? (SI_PB_NUM_LEN/2) : *(pucExtContent + 1);

            /*lint -e534*/
            VOS_MemCpy(pstEcallNum->aucCallNumber, pucTmp + pstXdnContent->ucNameLen + 2, (SI_PB_NUM_LEN/2));
            VOS_MemCpy(pstEcallNum->aucCallNumber + (SI_PB_NUM_LEN/2), pucExtContent + 2, (SI_PB_NUM_LEN/2));
            /*lint +e534*/

            pstEcallNum->ucTon    = pucTmp[pstXdnContent->ucNameLen + 1];
            pstEcallNum->ucLength = (SI_PB_NUM_LEN/2) + ucExNumLen;
        }
        else
        {
            /*lint -e534*/
            VOS_MemCpy(pstEcallNum->aucCallNumber, pucTmp + pstXdnContent->ucNameLen + 2, (SI_PB_NUM_LEN/2));
            /*lint +e534*/

            pstEcallNum->ucTon    = pucTmp[pstXdnContent->ucNameLen + 1];
            pstEcallNum->ucLength = ((pucTmp[pstXdnContent->ucNameLen] - 1) > (SI_PB_NUM_LEN/2))?
                                    (SI_PB_NUM_LEN/2) : (pucTmp[pstXdnContent->ucNameLen] - 1);

        }

        pstEcallNum++;
    }

    return;
}
/*lint -restore */
#endif

#if ((OSA_CPU_ACPU == VOS_OSA_CPU)||(defined(DMT)))
/*****************************************************************************
函 数 名  :SI_PB_TransANRFromate

功能描述  :转换当前的一条ANR电话本为指定的数据结构

输入参数  :pstPBContent 转换的电话本内容信息
           ucIndex 转换的电话本的索引号/记录号
           pContent 转换的电话本内容

输出参数  :pstRecord 转换的电话本数据结构

返 回 值  :VOS_OK 解析成功
           VOS_ERR 解析失败

调用函数  :
被调函数  :
修订记录  :
1. 日    期   : 2009年06月08日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_VOID SI_PB_TransANRFromate(VOS_UINT8 ucANROffset,VOS_UINT8 *pANRContent, SI_PB_RECORD_STRU *pstRecord)
{
    VOS_UINT32 ulResult;
    VOS_UINT8  ucExtRecord;
    VOS_UINT8  aucPhoneNumber[20] = {0};
    VOS_UINT8  *pucExtContent;
    VOS_UINT8  ucExtNumLen;
    VOS_UINT8  ucAnrNumLen;

    ulResult = SI_PB_CheckANRValidity(pANRContent);/*检查当前的内容是否有效*/

    if(ulResult != VOS_OK)
    {
        /*全置为0*/
        pstRecord->AdditionNumber[ucANROffset].NumberLength = 0;
    }
    else
    {
        pstRecord->ValidFlag = SI_PB_CONTENT_VALID;/*标记当前的内容有效*/

        pstRecord->AdditionNumber[ucANROffset].NumberType = pANRContent[2];

        pucExtContent = gastEXTContent[PB_ADN_CONTENT].pExtContent;

        ucExtRecord = ((VOS_NULL_PTR == pucExtContent)?0xFF:pANRContent[14]);

        if((0xFF != ucExtRecord)&&(VOS_NULL_PTR != pucExtContent)
           &&(ucExtRecord <= gastEXTContent[PB_ADN_CONTENT].usExtTotalNum))
        {
            pucExtContent += (ucExtRecord - 1) * SI_PB_EXT_LEN;
            ucExtNumLen   = (*(pucExtContent + 1) > (SI_PB_NUM_LEN/2))?
                            (SI_PB_NUM_LEN/2) : *(pucExtContent + 1);

            /*lint -e534*/
            VOS_MemCpy(aucPhoneNumber, pANRContent+3, SI_PB_NUM_LEN/2 );
            VOS_MemCpy(aucPhoneNumber + (SI_PB_NUM_LEN/2), pucExtContent + 2, SI_PB_NUM_LEN/2 );
            /*lint +e534*/

            SI_PB_BcdToAscii( (VOS_UINT8)(ucExtNumLen + (SI_PB_NUM_LEN/2)), aucPhoneNumber,
                                pstRecord->AdditionNumber[ucANROffset].Number, &pstRecord->AdditionNumber[ucANROffset].NumberLength);
        }
        else                                                                                /*拷贝号码从内容开始*/
        {
            ucAnrNumLen = ((pANRContent[1]-1) > (SI_PB_NUM_LEN/2))?
                          (SI_PB_NUM_LEN/2) : (pANRContent[1]-1);

            SI_PB_BcdToAscii(ucAnrNumLen, &pANRContent[3],
                            pstRecord->AdditionNumber[ucANROffset].Number,
                            &pstRecord->AdditionNumber[ucANROffset].NumberLength);
        }
    }

    return;
}

/*****************************************************************************
函 数 名  :SI_PB_TransEMLFromate

功能描述  :转换Email文件内容为指定的数据结构

输入参数  :pstPBContent 转换的电话本内容信息
           ucIndex 转换的电话本的索引号/记录号
           pContent 转换的电话本内容

输出参数  :pstRecord 转换的电话本数据结构

返 回 值  :VOS_OK 解析成功
           VOS_ERR 解析失败

调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2009年06月08日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_VOID SI_PB_TransEMLFromate(VOS_UINT8 ucEmailMaxLen, VOS_UINT8 *pEMLContent, SI_PB_RECORD_STRU *pstRecord)
{
    VOS_UINT32 i;
    VOS_UINT8  ucEmailLen = 0;

    for(i = 0; i < ucEmailMaxLen; i++)
    {
        if(0xFF == pEMLContent[i])
        {
            break;
        }

        ucEmailLen++;
    }

    if(0 == ucEmailLen)
    {
        pstRecord->Email.EmailLen = 0;
    }
    else
    {
        pstRecord->Email.EmailLen = ucEmailLen;

        pstRecord->ValidFlag = SI_PB_CONTENT_VALID;

        /*lint -e534*/
        VOS_MemCpy(pstRecord->Email.Email, pEMLContent, ucEmailLen);
        /*lint +e534*/
    }

    return;
}

/*****************************************************************************
函 数 名  :SI_PB_GetFileCntFromIndex
功能描述  :根据输入的INDEX的值得到对应的EMAIL或ANR文件的偏移，从1开始　
输入参数  :ucIndex:   INDEX的值
           pucEMLFileCnt:     返回EMAIL文件的偏移
输出参数  :无
返 回 值  : 1:有效、0:无效
调用函数  :无
修订记录  :
1. 日    期   : 2009年5月19日
    作    者   : m00128685
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_GetFileCntFromIndex(VOS_UINT16 ucIndex, VOS_UINT8 *pucFileCnt)
{
    VOS_UINT8   i;
    VOS_UINT16  usSum;

    usSum = 0;

    for (i = 0; i < gstPBCtrlInfo.ulADNFileNum; i++)
    {
        if ((ucIndex <= (usSum + gstPBCtrlInfo.astADNInfo[i].ucRecordNum))
            && (ucIndex > usSum))
        {
            break;
        }
        else
        {
            usSum += gstPBCtrlInfo.astADNInfo[i].ucRecordNum;
        }
    }

    if (i >= gstPBCtrlInfo.ulADNFileNum)
    {
        *pucFileCnt = 0;
        return VOS_ERR;
    }
    else
    {
        *pucFileCnt = i + 1;
        return VOS_OK;
    }
}

#endif

#ifdef __cplusplus
  #if __cplusplus
  }
  #endif
#endif



