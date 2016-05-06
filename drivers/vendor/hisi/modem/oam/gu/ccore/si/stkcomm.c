/************************************************************************
Copyright   : 2005-2008, Huawei Tech. Co., Ltd.
File name   : SimProc.c
Author      : z00100318
Version     : V200R001
Date        : 2008-10-18
Description : 该文件定义了SIM卡事件实现

Description : SIM卡事件的处理和实现
History     :

1.日    期  : 2008年10月28日
  作    者  : H59254
  修改内容  : Create
************************************************************************/

#include "si_stk.h"
#include "csimagent.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID PS_FILE_ID_STK_COMM_C
/*lint +e767*/

SI_STK_DATADECODE_STRU gSTKDataDecode[] =
{
    {0                              ,0,0,0},
    {COMMAND_DETAILS_TAG            ,SI_TAG_TYPE_V     ,sizeof(VOS_UINT32)      ,3},
    {DEVICE_IDENTITY_TAG            ,SI_TAG_TYPE_V     ,sizeof(VOS_UINT32)      ,2},
    {RESULT_TAG                     ,SI_TAG_TYPE_TLV   ,sizeof(SI_SAT_TLV_STRU) ,0},
    {DURATION_TAG                   ,SI_TAG_TYPE_V     ,sizeof(VOS_UINT32)      ,2},
    {ALPHA_IDENTIFIER_TAG           ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {ADDRESS_TAG                    ,SI_TAG_TYPE_TLV   ,sizeof(SI_SAT_TLV_STRU) ,0},
    {CAP_CFG_PARA_TAG               ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {SUBADDRESS_TAG                 ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {SS_STRING_TAG                  ,SI_TAG_TYPE_TLV   ,sizeof(SI_SAT_TLV_STRU) ,0},
    {USSD_STRING_TAG                ,SI_TAG_TYPE_TLV   ,sizeof(SI_SAT_TLV_STRU) ,0},
    {SMS_TPDU_TAG                   ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {CELL_BROADCAST_PAGE_TAG        ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {TEXT_STRING_TAG                ,SI_TAG_TYPE_TLV   ,sizeof(SI_SAT_TLV_STRU) ,0},
    {TONE_TAG                       ,SI_TAG_TYPE_V     ,sizeof(VOS_UINT32)      ,1},
    {ITEM_TAG                       ,SI_TAG_TYPE_TLV   ,sizeof(SI_SAT_TLV_STRU) ,0},
    {ITEM_IDENTIFIER_TAG            ,SI_TAG_TYPE_V     ,sizeof(VOS_UINT32)      ,1},
    {RESPONSE_LENGTH_TAG            ,SI_TAG_TYPE_V     ,sizeof(VOS_UINT32)      ,2},
    {FILE_LIST_TAG                  ,SI_TAG_TYPE_TLV   ,sizeof(SI_SAT_TLV_STRU) ,0},
    {LOCATION_INFORMATION_TAG       ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {IMEI_TAG                       ,SI_TAG_TYPE_V     ,8*sizeof(VOS_UINT8)     ,8},
    {HELP_REQUEST_TAG               ,SI_TAG_TYPE_V     ,sizeof(VOS_UINT32)      ,0},
    {NET_MEASUREMENT_RESULTS_TAG    ,SI_TAG_TYPE_V     ,16*sizeof(VOS_UINT8)    ,16},
    {DEFAULT_TEXT_TAG               ,SI_TAG_TYPE_TLV   ,sizeof(SI_SAT_TLV_STRU) ,0},
    {MS_NEXTACTION_INDICATOR_TAG    ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {EVENT_LIST_TAG                 ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {CAUSE_TAG                      ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {LOCATION_STATUS_TAG            ,SI_TAG_TYPE_V     ,sizeof(VOS_UINT32)      ,1},
    {TRANSACTION_IDENTIFIER_TAG     ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {BCCH_CHANNEL_LIST_TAG          ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {ICON_IDENTIFIER_TAG            ,SI_TAG_TYPE_V     ,sizeof(SI_UINT32)       ,2},
    {ITEM_ICONID_LIST_TAG           ,SI_TAG_TYPE_TLV   ,sizeof(SI_SAT_TLV_STRU) ,0},
    {CARD_READER_STATUS_TAG         ,SI_TAG_TYPE_V     ,sizeof(VOS_UINT32)      ,1},
    {CARD_ATR_TAG                   ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {C_APDU_TAG                     ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {R_APDU_TAG                     ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {TIMER_IDENTIFIER_TAG           ,SI_TAG_TYPE_V     ,sizeof(VOS_UINT32)      ,1},
    {TIMER_VALUE_TAG                ,SI_TAG_TYPE_V     ,4*sizeof(VOS_UINT8)     ,3},
    {DATETIME_AND_TIMEZONE_TAG      ,SI_TAG_TYPE_V     ,8*sizeof(VOS_UINT8)     ,8},
    {CALL_CONTROL_REQACTION_TAG     ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {AT_COMMAND_TAG                 ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {AT_RESPONSE_TAG                ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {BC_REPEAT_INDICATOR_TAG        ,SI_TAG_TYPE_V     ,sizeof(VOS_UINT32)      ,1},
    {IMMEDIATE_RESPONSE_TAG         ,SI_TAG_TYPE_V     ,0                       ,0},
    {DTMF_STRING_TAG                ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {LANGUAGE_TAG                   ,SI_TAG_TYPE_V     ,sizeof(SI_UINT32)       ,2},
    {TIMING_ADVANCE_TAG             ,SI_TAG_TYPE_V     ,sizeof(SI_UINT32)       ,1},
    {AID_TAG                        ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {BROWSER_IDENTITY_TAG           ,SI_TAG_TYPE_V     ,sizeof(VOS_UINT32)      ,1},
    {URL_TAG                        ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {BEARER_TAG                     ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {PROVISIONING_REFFILE_TAG       ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {BROWSER_TERMINATION_CAUSE_TAG  ,SI_TAG_TYPE_V     ,sizeof(VOS_UINT32)      ,1},
    {BEARER_DESCRIPTION_TAG         ,SI_TAG_TYPE_TLV   ,sizeof(SI_SAT_TLV_STRU) ,0},
    {CHANNEL_DATA_TAG               ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {CHANNEL_DATA_LENGTH_TAG        ,SI_TAG_TYPE_V     ,sizeof(VOS_UINT32)      ,1},
    {CHANNEL_STATUS_TAG             ,SI_TAG_TYPE_V     ,sizeof(VOS_UINT32)      ,2},
    {BUFFER_SIZE_TAG                ,SI_TAG_TYPE_V     ,sizeof(SI_UINT32)       ,2},
    {CARD_READER_IDENTIFIER_TAG     ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {RFU_3B                         ,0,0,0},
    {UICC_TERMINAL_TRAN_LEVEL_TAG   ,SI_TAG_TYPE_V     ,sizeof(VOS_UINT32)      ,3},
    {RFU_3D                         ,0,0,0},
    {OTHER_ADDR_TAG                 ,SI_TAG_TYPE_TLV   ,sizeof(SI_SAT_TLV_STRU) ,0},
    {ACCESS_TECHNOLOGY_TAG          ,SI_TAG_TYPE_V     ,sizeof(VOS_UINT32)      ,1},
    {DISPLAY_PARAMETERS_TAG         ,SI_TAG_TYPE_V     ,sizeof(VOS_UINT32)      ,3},
    {SERVICE_RECORD_TAG             ,SI_TAG_TYPE_TLV   ,sizeof(SI_SAT_TLV_STRU) ,0},
    {DEVICE_FILTER_TAG              ,SI_TAG_TYPE_TLV   ,sizeof(SI_SAT_TLV_STRU) ,0},
    {SERVICE_SEARCH_TAG             ,SI_TAG_TYPE_TLV   ,sizeof(SI_SAT_TLV_STRU) ,0},
    {ATTRIBUTE_INFORMATION_TAG      ,SI_TAG_TYPE_TLV   ,sizeof(SI_SAT_TLV_STRU) ,0},
    {SERVICE_AVAILABILITY_TAG       ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {ESN_TAG                        ,SI_TAG_TYPE_V     ,sizeof(VOS_UINT32)      ,4},
    {NETWORK_ACCESS_NAME_TAG        ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {CDMA_SMS_TPDU                  ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {REMOTE_ENTITY_ADDRESS_TAG      ,SI_TAG_TYPE_TLV   ,sizeof(SI_SAT_TLV_STRU) ,0},
    {I_WLAN_ID_TAG                  ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {I_WLAN_ACCESS_STATUS_TAG       ,SI_TAG_TYPE_V     ,sizeof(VOS_UINT32)      ,1},
    {RFU_4C                         ,0,0,0},
    {RFU_4D                         ,0,0,0},
    {RFU_4E                         ,0,0,0},
    {RFU_4F                         ,0,0,0},
    {TEXT_ATTRIBUTE_TAG             ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {ITEM_TEXT_ATTRIBUTE_LIST_TAG   ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {PDP_CONTEXT_ACTIVATION_PAR_TAG ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {RFU_53                         ,0,0,0},
    {RFU_54                         ,0,0,0},
    {CSG_CELL_SELEC_STATUS_TAG      ,SI_TAG_TYPE_V     ,sizeof(VOS_UINT32)      ,2},
    {CSG_ID_TAG                     ,SI_TAG_TYPE_V     ,sizeof(VOS_UINT32)      ,3},
    {HNB_NAME_TAG                   ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {RFU_58                         ,0,0,0},
    {RFU_59                         ,0,0,0},
    {RFU_5A                         ,0,0,0},
    {RFU_5B                         ,0,0,0},
    {RFU_5C                         ,0,0,0},
    {RFU_5D                         ,0,0,0},
    {RFU_5E                         ,0,0,0},
    {RFU_5F                         ,0,0,0},
    {RFU_60                         ,0,0,0},
    {RFU_61                         ,0,0,0},
    {IMEISV_TAG                     ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {BATTERY_STATE_TAG              ,SI_TAG_TYPE_V     ,sizeof(VOS_UINT32)      ,1},
    {BROWSING_STATUS_TAG            ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {NETWORK_SEARCH_MODE_TAG        ,SI_TAG_TYPE_V     ,sizeof(VOS_UINT32)      ,1},
    {FRAME_LAYOUT_TAG               ,SI_TAG_TYPE_TLV   ,sizeof(SI_SAT_TLV_STRU) ,0},
    {FRAMES_INFORMATION_TAG         ,SI_TAG_TYPE_TLV   ,sizeof(SI_SAT_TLV_STRU) ,0},
    {FRAME_IDENTIFIER_TAG           ,SI_TAG_TYPE_V     ,sizeof(VOS_UINT32)      ,1},
    {UTRAN_MEASUREMENT_TAG          ,SI_TAG_TYPE_V     ,sizeof(VOS_UINT32)      ,1},
    {MMS_REFERENCE_TAG              ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {MMS_IDENTIFIER_TAG             ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {MMS_TRANSFER_STATUS_TAG        ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {MEID_TAG                       ,SI_TAG_TYPE_V     ,8*sizeof(VOS_UINT8)     ,8},
    {MMS_CONTENT_ID_TAG             ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {MMS_NOTIFICATION_TAG           ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {LAST_ENVELOPE_TAG              ,SI_TAG_TYPE_V     ,sizeof(VOS_UINT8)       ,0},
    {RFU_62                         ,0,0,0},
    {PLMNWACT_LIST_TAG              ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {ROUTING_AREA_INFO_TAG          ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {ATTACH_TYPE_TAG                ,SI_TAG_TYPE_V     ,sizeof(VOS_UINT32)      ,1},
    {REJETION_CAUSE_CODE_TAG        ,SI_TAG_TYPE_V     ,sizeof(VOS_UINT32)      ,1},
    {GEOGRAPH_LOCAL_PARA_TAG        ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {GAD_SHAPES_TAG                 ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {NMEA_SENTENCE_TAG              ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {PLMN_LIST_TAG                  ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {RFU_7A                         ,0,0,0},
    {RFU_7B                         ,0,0,0},
    {EPSPDN_ACTIVE_PARA_TAG         ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {TRACKING_AREA_ID_TAG           ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {CSG_ID_LIST_TAG                ,SI_TAG_TYPE_LV    ,sizeof(SI_SAT_LV_STRU)  ,0},
    {SI_STK_TAG_BUTT                ,0,0,0}
};

/*****************************************************************************
函 数 名  :SI_STK_BcdByteToAscii
功能描述  :BCD码转换成Ascii码
输入参数  :ucBcdNumLen:转换的号码长度
           pucBcdNum:转换的号码内容
           enChangeMode:转换的大小写
输出参数  :pucAsciiNum:转换的结果
返 回 值  :无
调用函数  :无
被调函数  :
修订记录  :
1. 日    期   : 2009年8月4日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_VOID SI_STK_BcdByteToAscii(VOS_UINT8 ucBcdByte,
                                        VOS_UINT8*pucAsciiByte,
                                        SI_STK_STR_CHANGEMODE_ENUM_UINT32 enChangeMode)
{
    if(ucBcdByte <= 9)
    {
        *pucAsciiByte = ucBcdByte + 0x30;
    }
    else if(0x0A == ucBcdByte)
    {
        *pucAsciiByte = 0x2a;
    }
    else if(0x0B == ucBcdByte)
    {
        *pucAsciiByte = 0x23;
    }
    else if(0x0C == ucBcdByte)   /*转换'P'字符*/
    {
        *pucAsciiByte = 0x50;
    }
    else if(0x0D == ucBcdByte)   /*转换'?'字符*/
    {
        *pucAsciiByte = 0x3F;
    }
    else
    {
        if (SI_STK_STR_CHANGESMALL == enChangeMode)
        {
            *pucAsciiByte = ucBcdByte + 0x57;
        }
        else
        {
            *pucAsciiByte = ucBcdByte + 0x37;
        }
    }

    return;
}

/*****************************************************************************
函 数 名  :SI_STK_BcdStrToAscii
功能描述  :BCD码转换成Ascii码
输入参数  :ucBcdNumLen:转换的号码长度
           pucBcdNum:转换的号码内容
           enChangeMode:转换模式
输出参数  :pucAsciiNum:转换的结果
返 回 值  :无
调用函数  :无
被调函数  :
修订记录  :
1. 日    期   : 2009年8月4日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_VOID SI_STK_BcdStrToAscii(VOS_UINT8 ucBcdNumLen,
                                        VOS_UINT8 *pucBcdNum,
                                        VOS_UINT8 *pucAsciiNum,
                                        VOS_UINT32*pulLen,
                                        SI_STK_STR_CHANGEMODE_ENUM_UINT32 enChangeMode)
{
    VOS_UINT8       ucTmp;
    VOS_UINT32      ulLen = 0;
    VOS_UINT8       ucFirstNumber;
    VOS_UINT8       ucSecondNumber;

    for (ucTmp = 0; ucTmp < ucBcdNumLen; ucTmp++)
    {
        if(0xFF == pucBcdNum[ucTmp])
        {
            break;
        }

        ucFirstNumber  = (VOS_UINT8)(pucBcdNum[ucTmp] & 0x0F); /*取出高半字节*/

        SI_STK_BcdByteToAscii(ucFirstNumber,pucAsciiNum,enChangeMode);

        pucAsciiNum++;

        ulLen++;

        ucSecondNumber = (VOS_UINT8)((pucBcdNum[ucTmp] >> 4) & 0x0F);/*取出低半字节*/

        if(0x0F == ucSecondNumber)
        {
            break;
        }

        SI_STK_BcdByteToAscii(ucSecondNumber,pucAsciiNum,enChangeMode);

        pucAsciiNum++;

        ulLen++;
    }

    *pulLen = ulLen;

    return;
}

/*****************************************************************************
函 数 名  :SI_STKSetBit32
功能描述  :32bit设置函数
输入参数  :
输出参数  :
返 回 值  :
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月03日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 SI_STKSetBit32(VOS_UINT32 ulValue, VOS_UINT32 ulBitNo)
{
    VOS_UINT32 ulTemp = 0;

    if(ulBitNo > 31)
    {
        STK_WARNING_LOG("SI_STKSetBit32: ulBitNo out of Range");

        return ulValue;
    }

    if(ulBitNo == 0)
    {
        ulValue = ulValue | 1;
    }
    else
    {   /*设置后不影响ulValue的其他BIT位*/
        /*lint -e701 */
        ulTemp = (~(VOS_UINT32)(1<<(ulBitNo-1)));

        ulValue |= (VOS_UINT32)((0 | (1<<ulBitNo))&(ulTemp));
        /*lint +e701 */
    }

    return ulValue;
}

/*****************************************************************************
函 数 名  :SI_STKGetBit32
功能描述  :32bit获取函数
输入参数  :
输出参数  :
返 回 值  :
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月03日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 SI_STKGetBit32(VOS_UINT32 ulValue, VOS_UINT32 ulBitNo)
{
    VOS_UINT32 ulTemp = 0;

    if(ulBitNo > 31)
    {
        STK_WARNING_LOG("SI_STKGetBit32: ulBitNo out of Range");

        return 0;
    }

    if(ulBitNo == 0)
    {
        ulValue = ulValue & 1;
    }
    else
    {
        /*取第ulBitNo位的值，0或1*/
        /*lint -e701 */
        ulValue &= (VOS_UINT32)((ulTemp | (1<<ulBitNo))&(~(VOS_UINT32)(1<<(ulBitNo-1))));
        /*lint +e701 */
    }

    return ulValue;
}

/*****************************************************************************
函 数 名  :SI_STKGetBitFromBuf
功能描述  :从数据中获取指定Bit位的值　
输入参数  :ucDataBuf:   数据内容
           ulBitNo:     Bit号从0开始
           ulBufLen:    数据总长度
输出参数  :无
返 回 值  :USIMM_BITNOFOUNE
           Bit值
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_STKGetBitFromBuf(VOS_UINT8 *pucDataBuf, VOS_UINT32 ulBitNo,VOS_UINT32 ulBufLen)
{
    VOS_UINT32  ulOffset;
    VOS_UINT8   ucBit;

    ulOffset = ulBitNo/ 8;              /*获取字节偏移*/

    ucBit    = (VOS_UINT8)(ulBitNo%8);  /*获取Bit偏移*/

    if ( ulOffset >=  ulBufLen )
    {
        return VOS_FALSE;
    }

    return ((pucDataBuf[ulOffset]>>ucBit)&0x00000001);/*返回bit值是0还是1*/
}

/*****************************************************************************
函 数 名  :SI_STKFindTag
功能描述  :在码流中找到指定的TAG
输入参数  :
输出参数  :
返 回 值  :
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月03日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 SI_STKFindTag(VOS_UINT8 ucTag, VOS_UINT8* pucData, VOS_UINT32 ulDataLen,VOS_UINT32 ulFindNum)
{
    VOS_UINT32 i;
    VOS_UINT32 j=1;

    for(i=0; i<ulDataLen;)
    {
        if((pucData[i]&0x7F) == (ucTag&0x7F))   /*返回长度字节偏移*/
        {
            if(j == ulFindNum)
            {
                if(pucData[i+1] == 0x81) /*0x81指示长度字节表示的长度大于等于0x80*/
                {
                    return (i+2);   /*跳过前面的指示字节返回长度字节的偏移*/
                }
                else
                {
                    return (i+1);
                }
              }
            else
            {
                j++;
            }
        }

        if(pucData[i+1] == 0x81)      /*跳到下一个Tag*/
        {
            i += pucData[i+2] + 3;
        }
        else
        {
            i += pucData[i+1] + 2;
        }
    }

    return SI_TAGNOTFOUND;
}

/*****************************************************************************
函 数 名  :SI_STKDecodeTagData
功能描述  :根据TAG类型对TLV格式进行解码
输入参数  :
输出参数  :
返 回 值  :
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月03日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 SI_STKDecodeTagData(VOS_UINT8 *pucCmdData, VOS_UINT8 ucTag, VOS_VOID *pDec)
{
    VOS_UINT32      ulDataLen = 0;
    SI_SAT_LV_STRU *pstLVData;
    SI_SAT_TLV_STRU*pstTLVData;

    if((pDec == VOS_NULL_PTR)||(ucTag >= SI_STK_TAG_BUTT))
    {
        STK_ERROR_LOG("SI_STKDecodeTagData: The Input Data is Error");

        return ulDataLen;
    }

    ulDataLen = gSTKDataDecode[ucTag].ucSTRULen;/*数据结构中该Tag数据的长度*/

    switch(gSTKDataDecode[ucTag].ucTagType)
    {
        case SI_TAG_TYPE_V:

            if(gSTKDataDecode[ucTag].ucValueLen != pucCmdData[0])
            {
                STK_WARNING_LOG1("SI_STKDecodeTagData: The SI_TAG_TYPE_V Tag TLV Data Len is Error", ucTag);

                break;
            }

            if(gSTKDataDecode[ucTag].ucValueLen != 0x00)
            {
                /*lint -e534*/
                VOS_MemCpy(pDec, &pucCmdData[1], gSTKDataDecode[ucTag].ucValueLen);
                /*lint +e534*/
            }
            break;

        case SI_TAG_TYPE_LV:
            if(0x00 != pucCmdData[0])
            {
                pstLVData           = (SI_SAT_LV_STRU *)pDec;
                pstLVData->ulLen    = pucCmdData[0];
                pstLVData->pValue   = (SI_UINT8 *)VOS_MemAlloc(MAPS_STK_PID, DYNAMIC_MEM_PT, pstLVData->ulLen);

                if(pstLVData->pValue != VOS_NULL)
                {
                    /*lint -e534*/
                    VOS_MemCpy(pstLVData->pValue, &pucCmdData[1], pstLVData->ulLen);
                    /*lint +e534*/
                }
            }
            else
            {
                STK_WARNING_LOG1("SI_STKDecodeTagData: The %x Tag LV Data Len is 0", ucTag);
            }
            break;

        case SI_TAG_TYPE_TLV:
            if(1 < pucCmdData[0])
            {
                pstTLVData          = (SI_SAT_TLV_STRU *)pDec;
                pstTLVData->ucTag   = pucCmdData[1];
                pstTLVData->ucLen   = pucCmdData[0] - 1;
                pstTLVData->pValue  = (SI_UINT8 *)VOS_MemAlloc(MAPS_STK_PID, DYNAMIC_MEM_PT, pstTLVData->ucLen);

                if(pstTLVData->pValue != VOS_NULL)
                {
                    /*lint -e534*/
                    VOS_MemCpy(pstTLVData->pValue, &pucCmdData[2], pstTLVData->ucLen);
                    /*lint +e534*/
                }
            }
            else
            {
                STK_WARNING_LOG1("SI_STKDecodeTagData: The %x Tag TLV Data Len is Error", ucTag);
            }
            break;

        default:
            STK_ERROR_LOG("SI_STKDecodeTagData: The Data Structure is Error");
            break;
    }

    return ulDataLen;
}

/*****************************************************************************
函 数 名  :SI_STKTagDataFree
功能描述  :TAG数据释放内存
输入参数  :
输出参数  :
返 回 值  :
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月03日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 SI_STKTagDataFree(VOS_UINT8 ucTag, VOS_VOID *pData)
{
    VOS_UINT32      ulDataLen = 0;
    SI_SAT_LV_STRU *pstLVData;
    SI_SAT_TLV_STRU*pstTLVData;

    if(ucTag >= SI_STK_TAG_BUTT)
    {
        STK_ERROR_LOG("SI_STKTagDataFree: The Input Data is Error");

        return ulDataLen;
    }

    ulDataLen = gSTKDataDecode[ucTag].ucSTRULen;/*数据结构中该Tag数据的长度*/

    switch(gSTKDataDecode[ucTag].ucTagType)
    {
        case SI_TAG_TYPE_V:
            break;
        case SI_TAG_TYPE_LV:
            pstLVData           = (SI_SAT_LV_STRU *)pData;

            if(pstLVData->pValue != VOS_NULL)
            {
                /*lint -e534*/
                VOS_MemFree(MAPS_STK_PID,pstLVData->pValue);
                /*lint +e534*/
            }

            break;
        case SI_TAG_TYPE_TLV:
            pstTLVData          = (SI_SAT_TLV_STRU *)pData;

            if(pstTLVData->pValue != VOS_NULL)
            {
                /*lint -e534*/
                VOS_MemFree(MAPS_STK_PID,pstTLVData->pValue);
                /*lint +e534*/
            }

            break;
        default:
            STK_ERROR_LOG("SI_STKDecodeTagData: The Data Structure is Error");
            ulDataLen = 0;
            break;
    }

    return ulDataLen;
}


/*****************************************************************************
函 数 名  :
功能描述  :
输入参数  :
输出参数  :
返 回 值  :
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月03日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STKDecodeTagList(VOS_UINT8 *pucCmdData,VOS_UINT8 *pucTagList,VOS_UINT32 ulListLen, SI_SAT_COMMDATA_STRU *pstDec)
{
    VOS_UINT32 i;
    VOS_UINT32 ulOffset     = 0;
    VOS_UINT32 ulDataLen    = 0;
    VOS_UINT32 ulDataOffset = 0;

    pstDec->ulOpInfo = 0;

    for(i=0; i<ulListLen; i++)
    {
        ulOffset = SI_STKFindTag(pucTagList[i], &pucCmdData[1], pucCmdData[0], 1);

        if(ulOffset != SI_TAGNOTFOUND)
        {
            ulDataLen = SI_STKDecodeTagData(&pucCmdData[ulOffset+1], pucTagList[i], &pstDec->aucDecode[ulDataOffset]);

            pstDec->ulOpInfo = SI_STKSetBit32(pstDec->ulOpInfo, i);
        }
        else
        {
            /*如果没有找到，仍需跳过该Tag指示的数据结构长度*/
            ulDataLen = gSTKDataDecode[pucTagList[i]].ucSTRULen;
        }

        ulDataOffset += ulDataLen;
    }

    return;
}

/*****************************************************************************
函 数 名  :SI_STKSendTRWithData
功能描述  :主动命令直接回复TERMINAL RESPONSE 和数据
输入参数  :
输出参数  :
返 回 值  :
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月03日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STKSendTRWithData(SI_STK_COMMAND_DETAILS_STRU *pstCMDInfo, VOS_UINT32 ulResultLen, VOS_UINT8 *pucResult, VOS_UINT32 ulDataLen, VOS_UINT8 *pucData)
{
    VOS_UINT8   aucTemp[255] = {0x81,0x03,0x00,0x00,0x00,0x82,0x02,0x82,0x81,0x03,0x00};
    VOS_UINT8   ucRspLen;
    VOS_UINT8   ulOffset;

    /* 判断如果当前没有主动命令需要下发RP */
    if(SI_STK_NOCMDDATA == gstUsatCmdDecode.SatType)
    {
        STK_ERROR_LOG("SI_STKSendTRWithData: Current CMD Type is NULL");

        return;
    }

    if((VOS_NULL == ulResultLen)||(0xF0 <= ulResultLen)||(0xF0 < (ulResultLen+ulDataLen)))
    {
        STK_ERROR_LOG("SI_STKSendTRWithData: Need Result data");

        return;
    }

    aucTemp[2]  = pstCMDInfo->ucCommandNum;
    aucTemp[3]  = pstCMDInfo->ucCommandType;
    aucTemp[4]  = pstCMDInfo->ucCommandQua;

    if(1 == ulResultLen)
    {
        aucTemp[9] = 0x83;
    }

    if(ulResultLen < 0x7F)  /*如果结果的长度不大于127*/
    {
        aucTemp[10] = (VOS_UINT8)ulResultLen;

        ucRspLen = (VOS_UINT8)(ulResultLen+ulDataLen+STK_TERMINAL_RSP_LEN-1);  /*减去重复计算的ulResultLen的一个字节*/

        ulOffset = 11;
    }
    else
    {
        aucTemp[10] = 0x81; /* 大于127的标记 */

        aucTemp[11] = (VOS_UINT8)ulResultLen;

        ucRspLen = (VOS_UINT8)(ulResultLen+ulDataLen+STK_TERMINAL_RSP_LEN);  /*加上0x81的一个字节*/

        ulOffset = 12;
    }

    /* 组装数据，复制附加信息 */
    /*lint -e534*/
    VOS_MemCpy(&aucTemp[ulOffset], pucResult, ulResultLen);
    /*lint +e534*/

    if(0 != ulDataLen)
    {
        /*lint -e534*/
        VOS_MemCpy(&aucTemp[ulOffset+ulResultLen], pucData, ulDataLen);
        /*lint +e534*/
    }

    if (VOS_OK != SI_STK_SendTerminalResponseReqMsg(ucRspLen, aucTemp, USIMM_TR_TYPE_BALONG))
    {
        STK_WARNING_LOG("SI_STKAutoResponse: SI_STK_SendTerminalResponse Return Error");
    }

    return;
}

/*****************************************************************************
函 数 名  :SI_STKSimpleResponseData
功能描述  :主动命令直接回复TERMINAL RESPONSE
输入参数  :
输出参数  :
返 回 值  :
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月03日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STKSimpleResponseData(SI_STK_COMMAND_DETAILS_STRU *pstCMDInfo, VOS_UINT32 ulDataLen, VOS_UINT8 *pucData)
{
    VOS_UINT8  aucTemp[] = {0x81,0x03,0x00,0x00,0x00,0x02,0x02,0x82,0x81,0x83,0x00};
    VOS_UINT8   aucData[100] = {0};
    VOS_UINT8  *pucRsp = VOS_NULL_PTR;

    /* 判断如果当前没有主动命令需要下发RP */
    if(SI_STK_NOCMDDATA == gstUsatCmdDecode.SatType)
    {
        STK_ERROR_LOG("SI_STKSimpleResponseData: Current CMD Type is NULL");

        return;
    }

    aucTemp[2]  = pstCMDInfo->ucCommandNum;
    aucTemp[3]  = pstCMDInfo->ucCommandType;
    aucTemp[4]  = pstCMDInfo->ucCommandQua;
    aucTemp[10] = (VOS_UINT8)ulDataLen;

    /* 大于数据空间 */
    if(ulDataLen > (sizeof(aucData)-sizeof(aucTemp)-2))
    {
        pucRsp = (VOS_UINT8*)VOS_MemAlloc(MAPS_STK_PID, DYNAMIC_MEM_PT, sizeof(aucTemp)+ulDataLen);

        if(VOS_NULL_PTR == pucRsp)
        {
            STK_ERROR_LOG("SI_STKSimpleResponseData: Data Length is too Long");

            return;
        }
    }
    else
    {
        pucRsp = aucData;   /* 指向数据空间 */
    }

    /* 组装数据，先复制数据头部信息 */
    /*lint -e534*/
    VOS_MemCpy(pucRsp, aucTemp, sizeof(aucTemp));

    /* 组装数据，复制附加信息 */
    VOS_MemCpy(&pucRsp[sizeof(aucTemp)], pucData, ulDataLen);
    /*lint +e534*/

    if (VOS_OK != SI_STK_SendTerminalResponseReqMsg((VOS_UINT8)(sizeof(aucTemp)+ulDataLen),pucRsp, USIMM_TR_TYPE_BALONG))
    {
        gstSTKCtrlStru.enSTKLock = SI_STK_PROUNLOCK;

        STK_WARNING_LOG("SI_STKAutoResponse: SI_STK_SendTerminalResponse Return Error");
    }

    if(ulDataLen > (sizeof(aucData)-sizeof(aucTemp)))
    {
        /*lint -e534*/
        VOS_MemFree(MAPS_STK_PID, pucRsp);
        /*lint +e534*/
    }

    return;
}

/*****************************************************************************
函 数 名  :SI_STKSimpleResponse
功能描述  :主动命令直接回复TERMINAL RESPONSE
输入参数  :
输出参数  :
返 回 值  :
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月03日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STKSimpleResponse(SI_STK_COMMAND_DETAILS_STRU *pstCMDInfo, VOS_UINT8 ucResult)
{
    SI_STKSimpleResponseData(pstCMDInfo, sizeof(VOS_UINT8), &ucResult);

    return;
}

/*****************************************************************************
函 数 名  :SI_STK_InitTResponse
功能描述  :ENVELOPE命令初始处理函数
输入参数  :
输出参数  :
返 回 值  :
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月03日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_InitTResponse(VOS_UINT8 *pTRdata, SI_STK_COMMAND_DETAILS_STRU *pstCMDInfo, SI_STK_RESULT_STRU *pstResult)
{
    VOS_UINT8  aucTemp[] = {0x81,0x03,0x00,0x00,0x00,0x82,0x02,0x82,0x81,0x83,0x01,0x00};

    aucTemp[2]  = pstCMDInfo->ucCommandNum;
    aucTemp[3]  = pstCMDInfo->ucCommandType;
    aucTemp[4]  = pstCMDInfo->ucCommandQua;
    aucTemp[11] = pstResult->Result;

    pTRdata[0] = sizeof(aucTemp);

    /*lint -e534*/
    VOS_MemCpy(&pTRdata[1], aucTemp, sizeof(aucTemp));
    /*lint +e534*/

    if(0x00 != pstResult->ucLen)
    {
        pTRdata[0] += pstResult->ucLen;

        /*lint -e534*/
        VOS_MemCpy(&pTRdata[sizeof(aucTemp)], pstResult->pucAddiInfo, pstResult->ucLen);
        /*lint +e534*/
    }

    return;
}

/*****************************************************************************
函 数 名  :SI_STK_InitEnvelope
功能描述  :ENVELOPE命令初始处理函数
输入参数  :
输出参数  :
返 回 值  :
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月03日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_InitEnvelope(VOS_UINT8 *pCmdData, SI_STK_DEVICE_IDENTITIES_STRU *pstDiInfo, VOS_UINT8 ucCmdType)
{
    VOS_UINT8 aucTemp[] = {0xFF, 0xFF, 0x04, 0x82,0x02,0xFF,0x81};

    aucTemp[0] = ucCmdType;

    aucTemp[1] = ucCmdType;

    aucTemp[5] = pstDiInfo->ucSDId;

    /*lint -e534*/
    VOS_MemCpy(pCmdData, aucTemp, sizeof(aucTemp));
    /*lint +e534*/

    return;
}

/*****************************************************************************
函 数 名  :
功能描述  :
输入参数  :
输出参数  :
返 回 值  :
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月03日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_InitEventDown(VOS_UINT8 *pCmdData, SI_STK_DEVICE_IDENTITIES_STRU *pstDiInfo, VOS_UINT8 ucEventType)
{
    VOS_UINT8 aucTemp[] = {0xD6, 0xD6, 0x07, 0x19, 0x01, 0xFF, 0x82, 0x02, 0xFF, 0x81};

    aucTemp[5] = ucEventType;

    aucTemp[8] = pstDiInfo->ucSDId;

    /*lint -e534*/
    VOS_MemCpy(pCmdData, aucTemp, sizeof(aucTemp));
    /*lint +e534*/
}

/*****************************************************************************
函 数 名  :
功能描述  :
输入参数  :
输出参数  :
返 回 值  :
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月03日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 SI_STKAddTLV(VOS_UINT8* pucTLV_AIM,VOS_UINT8* pucTLV_OBJECT)
{
    VOS_UINT8   ucNum;
    VOS_UINT8   ucaddLgth;
    VOS_UINT16  uslength;

    ucNum = pucTLV_OBJECT[1] + 0x02;

    uslength = pucTLV_AIM[1] + ucNum;

    if(uslength > 255)
    {
        STK_ERROR_LOG("SI_STKAddTLV: Error length");
        return VOS_ERR;
    }

    if(pucTLV_OBJECT[1] >= 0x80)/*长度超过0x80，需要增加0x81字节*/
    {
        pucTLV_AIM[ pucTLV_AIM[1] + 0x02] = pucTLV_OBJECT[0] ;

        pucTLV_AIM[ pucTLV_AIM[1] + 0x03] = 0x81;

        ucaddLgth = 1 ;

        /*lint -e534*/
        VOS_MemCpy(&pucTLV_AIM[ pucTLV_AIM[1] + 0x04],&pucTLV_OBJECT[1],ucNum-1);
        /*lint +e534*/
    }
    else
    {
        /*lint -e534*/
        VOS_MemCpy(&pucTLV_AIM[ pucTLV_AIM[1] + 0x02],&pucTLV_OBJECT[0],ucNum);
        /*lint +e534*/

        ucaddLgth = 0x00 ;
    }

    pucTLV_AIM[1] = pucTLV_AIM[1] + ucNum + ucaddLgth;

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :
功能描述  :
输入参数  :
输出参数  :
返 回 值  :
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月03日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 SI_STKAddValue(VOS_UINT8* pucLV_AIM,VOS_UINT8* pucLV_OBJECT)
{
    VOS_UINT8  ucNum;
    VOS_UINT16 uslength =0;

    if(2 > pucLV_OBJECT[0])
    {
        STK_ERROR_LOG("SI_STKAddValue:Object Error length");
        return VOS_ERR;
    }

    ucNum = pucLV_OBJECT[0] ;

    uslength = pucLV_AIM[0] + ucNum;

    if( uslength > 255 )
    {
        STK_ERROR_LOG("SI_STKAddValue: Error length");

        return  VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemCpy(&pucLV_AIM[ pucLV_AIM[0] + 0x01],&pucLV_OBJECT[1],ucNum);
    /*lint +e534*/

    pucLV_AIM[0] = pucLV_AIM[0] + ucNum;

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :
功能描述  :
输入参数  :
输出参数  :
返 回 值  :
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月03日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 SI_STKCodeTLVData(VOS_UINT8 *pucAIM, VOS_UINT8 ucTag, VOS_VOID *pucData)
{
    VOS_UINT32      ulDataLen = 0;
    VOS_UINT8       aucTemp[256];
    SI_SAT_LV_STRU *pstLVData  = (SI_SAT_LV_STRU *)pucData;
    SI_SAT_TLV_STRU*pstTLVData = (SI_SAT_TLV_STRU *)pucData;

    if( (VOS_NULL_PTR == pucAIM)||(ucTag >= SI_STK_TAG_BUTT)||(VOS_NULL_PTR == pucData))
    {
        STK_ERROR_LOG("SI_STKCodeTLVData: Input Parameter is Error");

        return ulDataLen;
    }

    ulDataLen = gSTKDataDecode[ucTag].ucSTRULen;

    aucTemp[0] = ucTag;
    aucTemp[1] = 0;

    switch(gSTKDataDecode[ucTag].ucTagType)
    {
        case SI_TAG_TYPE_V:
            aucTemp[1] = gSTKDataDecode[ucTag].ucValueLen;
            /*lint -e534*/
            VOS_MemCpy(&aucTemp[2], pucData, gSTKDataDecode[ucTag].ucValueLen);
            /*lint +e534*/
            break;

        case SI_TAG_TYPE_LV:
            if(pstLVData->ulLen < 253)
            {
                aucTemp[1] = (VOS_UINT8)pstLVData->ulLen;
                /*lint -e534*/
                VOS_MemCpy(&aucTemp[2], pstLVData->pValue, aucTemp[1]);
                /*lint +e534*/
            }
            break;

        case SI_TAG_TYPE_TLV:
            if(pstTLVData->ucLen < 252)
            {
                aucTemp[1]  = pstTLVData->ucLen + 1;
                aucTemp[2]  = pstTLVData->ucTag;
                /*lint -e534*/
                VOS_MemCpy(&aucTemp[3], pstTLVData->pValue, pstTLVData->ucLen);
                /*lint +e534*/
            }
            break;

        default:
            STK_ERROR_LOG("SI_STKCodeTLVData: The Data Structure is Error");
            break;
    }

    if(aucTemp[1] != 0x00)
    {
        /*lint -e534*/
        SI_STKAddTLV(pucAIM, aucTemp);
        /*lint +e534*/
    }
    else
    {
        /*lint -e534*/
        VOS_MemCpy(&pucAIM[pucAIM[1] + 0x02], aucTemp, 2);
        /*lint +e534*/
        pucAIM[1] += 2;
    }

    return ulDataLen;
}

/*****************************************************************************
函 数 名  :
功能描述  :
输入参数  :
输出参数  :
返 回 值  :
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月03日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 SI_STKCodeLVData(VOS_UINT8 *pucAIM, VOS_UINT8 ucTag, VOS_VOID *pucData)
{
    VOS_UINT32      ulDataLen = 0;
    VOS_UINT8       aucTemp[256];
    SI_SAT_LV_STRU *pstLVData=(SI_SAT_LV_STRU *)pucData;
    SI_SAT_TLV_STRU*pstTLVData=(SI_SAT_TLV_STRU *)pucData;

    if((VOS_NULL_PTR == pucAIM)||(ucTag >= SI_STK_TAG_BUTT)||(VOS_NULL_PTR == pucData))
    {
        STK_ERROR_LOG1("SI_STKCodeTLVData: Input Parameter is Error, tag is ", ucTag);

        return ulDataLen;
    }

    ulDataLen = gSTKDataDecode[ucTag].ucSTRULen;

    aucTemp[1] = ucTag;

    aucTemp[2] = ucTag;

    aucTemp[3] = 0;

    switch(gSTKDataDecode[ucTag].ucTagType)
    {
        case SI_TAG_TYPE_V:
            aucTemp[3] = gSTKDataDecode[ucTag].ucValueLen;
            /*lint -e534*/
            VOS_MemCpy(&aucTemp[4], pucData, gSTKDataDecode[ucTag].ucValueLen);
            /*lint +e534*/
            break;

        case SI_TAG_TYPE_LV:
            if(pstLVData->ulLen < 253)
            {
                aucTemp[3] = (VOS_UINT8)pstLVData->ulLen;
                /*lint -e534*/
                VOS_MemCpy(&aucTemp[4], pstLVData->pValue, pstLVData->ulLen);
                /*lint +e534*/
            }
            break;

        case SI_TAG_TYPE_TLV:
            if(pstTLVData->ucLen < 252)
            {
                aucTemp[3]  = pstTLVData->ucLen + 1;
                aucTemp[4]  = pstTLVData->ucTag;
                /*lint -e534*/
                VOS_MemCpy(&aucTemp[5], pstTLVData->pValue, pstTLVData->ucLen);
                /*lint +e534*/
            }
            break;

        default:
            STK_ERROR_LOG1("SI_STKCodeTLVData: The Data Structure is Error, tag is ", ucTag);
            break;
    }

    if(aucTemp[3] == 0x00)
    {
        return ulDataLen;
    }

    if(aucTemp[3] > 0x80)
    {
        aucTemp[2] = 0x81;

        aucTemp[0] = aucTemp[3] + 3;

        /*lint -e534*/
        SI_STKAddValue(pucAIM, aucTemp);
        /*lint +e534*/
    }
    else
    {
        aucTemp[1] = aucTemp[3] + 2;

        /*lint -e534*/
        SI_STKAddValue(pucAIM, &aucTemp[1]);
        /*lint +e534*/
    }

    return ulDataLen;
}

/*****************************************************************************
函 数 名  :
功能描述  :
输入参数  :
输出参数  :
返 回 值  :
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月03日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STKCodeTagList(VOS_UINT8 *pucCmdData,VOS_UINT8 *pucTagList,
                                    VOS_UINT32 ulListLen, VOS_UINT32 ulCodeType,
                                    SI_SAT_COMMDATA_STRU* pstSrc)
{
    VOS_UINT32 i;
    VOS_UINT32 ulBitValue   = 0;
    VOS_UINT32 ulDataLen    = 0;
    VOS_UINT32 ulDataOffset = 0;

    for(i=0; i<ulListLen; i++)
    {
        ulBitValue = SI_STKGetBit32(pstSrc->ulOpInfo, i);

        if(ulBitValue == 0)
        {
            ulDataLen = gSTKDataDecode[pucTagList[i]].ucSTRULen;
        }
        else
        {
            if(ulCodeType == SI_CODE_TR_DATA)/*对于Terminal Response，按照LV方式编码*/
            {
                ulDataLen = SI_STKCodeLVData(pucCmdData, pucTagList[i], &pstSrc->aucDecode[ulDataOffset]);
            }
            else
            {
                ulDataLen = SI_STKCodeTLVData(pucCmdData, pucTagList[i], &pstSrc->aucDecode[ulDataOffset]);
            }
        }

        ulDataOffset += ulDataLen;
    }

    return;
}


/*****************************************************************************
函 数 名  :
功能描述  :
输入参数  :
输出参数  :
返 回 值  :
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月03日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 SI_STKCommDecodeData(VOS_UINT8 *pucCmdData, VOS_UINT32 ulCmdType,SI_SAT_COMMDATA_STRU *pstDec)
{
    VOS_UINT32 i;

    if( (VOS_NULL_PTR == pucCmdData) || (VOS_NULL_PTR == pstDec) )
    {
        STK_ERROR_LOG("SI_STKCommDecodeData: The Input Parameter is Error");

        return VOS_ERR;
    }

    for(i=0; i<STK_ARRAYSIZE(gastSTKDecodeList); i++)
    {
        if(ulCmdType == gastSTKDecodeList[i].ulCmdType)
        {
            SI_STKDecodeTagList(pucCmdData, gastSTKDecodeList[i].pucTagList, gastSTKDecodeList[i].ulTagLen, pstDec);

            break;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :
功能描述  :
输入参数  :
输出参数  :
返 回 值  :
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月03日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 SI_STKCommCodeData(VOS_UINT8 *pucCmdData,SI_CODEDATA_TYPE_UINT32 enDataType, VOS_UINT32 ulCmdType, SI_SAT_COMMDATA_STRU *pstSrc)
{
    SI_STK_TAGLIST_STRU     *pstCodeList;
    VOS_UINT32              ulBufsize;
    VOS_UINT32              i;

    if((pucCmdData == VOS_NULL_PTR)||(pstSrc == VOS_NULL_PTR))
    {
        STK_ERROR_LOG("SI_STKCommCodeData: The Input Data is Error");

        return VOS_ERR;
    }

    switch(enDataType)
    {
        case SI_CODE_TR_DATA:
            pstCodeList = gastRespCodeList;
            ulBufsize   = STK_ARRAYSIZE(gastRespCodeList);
            break;
        case SI_CODE_EVENT_DATA:
            pstCodeList = gastEventCodeList;
            ulBufsize   = STK_ARRAYSIZE(gastEventCodeList);
            break;
        case SI_CODE_ENVELOPE_DATA:
            pstCodeList = gastEnvelopeList;
            ulBufsize   = STK_ARRAYSIZE(gastEnvelopeList);
            break;
        default:
            STK_ERROR_LOG1("SI_STKCommCodeData: The Input Data type is Error :", (VOS_INT32)enDataType);
            return VOS_ERR;
    }

    for(i=0; i<ulBufsize; i++)
    {
        if(ulCmdType == pstCodeList[i].ulCmdType)
        {
            SI_STKCodeTagList(pucCmdData, pstCodeList[i].pucTagList, pstCodeList[i].ulTagLen, enDataType, pstSrc);

            break;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : SI_STKAppendentTagFree
功能描述  :
输入参数  :
输出参数  :
返 回 值  :
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2010年02月07日
  作    者  : m00128685
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STKAppendentTagFree(VOS_UINT32 ulCmdType,
                                            VOS_UINT8  *pucData)
{
    VOS_UINT32 i;
    VOS_UINT32 ulTagNum;

    switch(ulCmdType)
    {
        case SI_STK_SELECTITEM:
        case SI_STK_SETUPMENU:
            ulTagNum = *((VOS_UINT32 *)pucData);

            pucData += sizeof(VOS_UINT32);

            for(i=0; i < ulTagNum; i++)
            {
                if (VOS_NULL_PTR != ((SI_SAT_TLV_STRU *)pucData)->pValue)
                {
                    /*lint -e534*/
                    VOS_MemFree(MAPS_STK_PID,((SI_SAT_TLV_STRU *)pucData)->pValue);
                    /*lint +e534*/
                }

                pucData += sizeof(SI_SAT_TLV_STRU);
            }

            break;
        case SI_STK_LAUNCHBROWSER:
            ulTagNum = *((VOS_UINT32 *)pucData);

            pucData += sizeof(VOS_UINT32);

            for(i=0; i < ulTagNum; i++)
            {
                if (VOS_NULL_PTR != ((SI_SAT_LV_STRU *)pucData)->pValue)
                {
                    /*lint -e534*/
                    VOS_MemFree(MAPS_STK_PID,((SI_SAT_LV_STRU *)pucData)->pValue);
                    /*lint +e534*/
                }

                pucData += sizeof(SI_SAT_LV_STRU);
            }

            break;
        case SI_STK_OPENCHANNEL:
            /*Jump over DURATION_TAG*/
            pucData += sizeof(VOS_UINT32);

            /*Free TEXT_STRING_TAG*/
            if (VOS_NULL_PTR != ((SI_SAT_TLV_STRU *)pucData)->pValue)
            {
                /*lint -e534*/
                VOS_MemFree(MAPS_STK_PID,((SI_SAT_TLV_STRU *)pucData)->pValue);
                /*lint +e534*/
            }

            pucData += sizeof(SI_SAT_TLV_STRU);

            /*Free OTHER_ADDR_TAG*/
            if (VOS_NULL_PTR != ((SI_SAT_TLV_STRU *)pucData)->pValue)
            {
                /*lint -e534*/
                VOS_MemFree(MAPS_STK_PID,((SI_SAT_TLV_STRU *)pucData)->pValue);
                /*lint +e534*/
            }

            break;
        case SI_STK_SETUPCALL:
            /*Free ALPHA_IDENTIFIER_TAG*/
            if (VOS_NULL_PTR != ((SI_SAT_LV_STRU *)pucData)->pValue)
            {
                /*lint -e534*/
                VOS_MemFree(MAPS_STK_PID,((SI_SAT_LV_STRU *)pucData)->pValue);
                /*lint +e534*/
            }

            /*Jump over ICON_IDENTIFIER_TAG*/
            pucData += (sizeof(SI_SAT_LV_STRU) + sizeof(VOS_UINT32));

            /*Free TEXT_ATTRIBUTE_TAG*/
            if (VOS_NULL_PTR != ((SI_SAT_LV_STRU *)pucData)->pValue)
            {
                /*lint -e534*/
                VOS_MemFree(MAPS_STK_PID,((SI_SAT_LV_STRU *)pucData)->pValue);
                /*lint +e534*/
            }

            break;
        default:
            break;
    }

    return;
}

/*****************************************************************************
函 数 名  :
功能描述  :
输入参数  :
输出参数  :
返 回 值  :
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年07月03日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STKCommDataFree(VOS_UINT32 ulCmdType, SI_SAT_COMMDATA_STRU *pstData)
{
    VOS_UINT32 i;
    VOS_UINT32 j;
    VOS_UINT32 ulOffset = 0;
    VOS_UINT8* pData;

    if(VOS_NULL_PTR == pstData)
    {
        STK_ERROR_LOG("SI_STKCommDataFree: The Input Parameter is Error");

        return ;
    }

    pData = pstData->aucDecode;

    for(i=0; i<STK_ARRAYSIZE(gastSTKDecodeList); i++)
    {
        if(ulCmdType == gastSTKDecodeList[i].ulCmdType)
        {
            for(j=0; j<gastSTKDecodeList[i].ulTagLen; j++)
            {
                ulOffset = SI_STKTagDataFree(*(gastSTKDecodeList[i].pucTagList+j), pData);

                pData += ulOffset;
            }
            break;
        }
    }

    SI_STKAppendentTagFree(ulCmdType,pData);

    return ;
}

/*****************************************************************************
函 数 名  : SI_STKErrorProc
功能描述  :
输入参数  :
输出参数  :
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2010年08月22日
    作    者   : zhuli
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_STKCheckCardState(VOS_VOID)
{
    if((USIMM_CARD_SERVIC_UNAVAILABLE == g_stStkCardInfo.enSvcStatus)
         || (USIMM_CARD_SERVIC_ABSENT == g_stStkCardInfo.enSvcStatus))
    {
        STK_WARNING_LOG("SI_STKCheckCardState: The Card Absent");

        return TAF_ERR_SIM_FAIL;
    }
    else if( USIMM_CARD_SERVIC_SIM_PUK == g_stStkCardInfo.enSvcStatus)
    {
        STK_WARNING_LOG("SI_STKCheckCardState: PUK NEED");

        return TAF_ERR_NEED_PUK1;
    }
    else if( USIMM_CARD_SERVIC_SIM_PIN == g_stStkCardInfo.enSvcStatus)
    {
        STK_WARNING_LOG("SI_STKCheckCardState: PIN NEED");

        return TAF_ERR_NEED_PIN1;
    }
    else
    {
        return TAF_ERR_NO_ERROR;
    }
}

/*****************************************************************************
函 数 名  : SI_STKErrorProc
功能描述  :
输入参数  :
输出参数  :
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2009年03月12日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_STKErrorProc(VOS_VOID)
{
    if( SI_STK_PROLOCK == gstSTKCtrlStru.enSTKLock )
    {
        STK_WARNING_LOG("SI_STKErrorProc: The STK is Locked");

        return TAF_ERR_UNSPECIFIED_ERROR;
    }

    return SI_STKCheckCardState();
}

/*****************************************************************************
 Function   : DIAG_Num2BCD
 Description: DIAG Num transfer to BCD
 Input      : const VOS_CHAR *pucSrc
              VOS_CHAR *pucDest
              VOS_UINT32 ulLength
 Return     : VOID
 History    :
1.日    期  : 2009年07月15日
  作    者  : H59254
  修改内容  : Create
 *****************************************************************************/
VOS_VOID SI_STK_Num2BCD(const VOS_UINT8 *pucSrc, VOS_UINT8 *pucDest, VOS_UINT32 ulLength)
{
    VOS_UINT8   i;

    for(i = 0; i < ulLength ; i++)
    {
        if(0 == (i%2))
        {
            pucDest[i/2] = pucSrc[i]&0xF;
        }
        else
        {
            pucDest[i/2] |= ((pucSrc[i]&0xF)<<4);
        }
    }

    if(1 == (ulLength % 2))
    {
        pucDest[ulLength/2] |= 0xF0; /* 高位 */
    }

    return;
}

/*****************************************************************************
 Function   : SI_STK_SsStr2ASCII
 Description: SS String transfer to ASCII
 Input      : const VOS_CHAR *pucSrc
              VOS_CHAR *pucDest
              VOS_UINT32 ulLength
 Return     : VOID
 History    :
1.日    期  : 2009年12月24日
  作    者  : m00128685
  修改内容  : Create
 *****************************************************************************/
VOS_VOID SI_STK_SsStr2ASCII(const VOS_UINT8 *pucSrc, VOS_UINT8 *pucDest, VOS_UINT32 ulLength)
{
    VOS_UINT8   i;
    VOS_UINT8   j;
    VOS_UINT8   ucHigh;
    VOS_UINT8   ucLow;

    for((i = 0),(j = 0); i < ulLength ; i++,(j += 2))
    {
        ucHigh = (pucSrc[i]>>4)&0x0F;
        ucLow = (pucSrc[i])&0x0F;

        if(ucHigh <= 0x09)
        {
            ucHigh = ucHigh + 0x30;
        }
        else
        {
            ucHigh = ucHigh + 0x37;
        }

        if(ucLow <= 0x09)
        {
            ucLow = ucLow + 0x30;
        }
        else
        {
            ucLow = ucLow + 0x37;
        }

        pucDest[j] = ucHigh;
        pucDest[j+1] = ucLow;

    }

    return;
}

/*****************************************************************************
 Function   : SI_STK_StrStr
 Description: 在码流1中查找码流2
 Input      :
 Return     : VOS_FALSE 匹配失败
              VOS_TRUE  匹配成功
 History    :
1.日    期  : 2010年02月10日
  作    者  : m00128685
  修改内容  : Create
 *****************************************************************************/
VOS_UINT32 SI_STK_StrStr(VOS_UINT8 *pucStr1, VOS_UINT8 *pucStr2 , VOS_UINT32 ulStrlen1, VOS_UINT32 ulStrlen2)
{
    VOS_UINT32 ulLen1;
    VOS_UINT8 *pucTempStr1;

    if ((VOS_NULL_PTR == pucStr1) || (VOS_NULL_PTR == pucStr2))
    {
        return VOS_FALSE;
    }

    if (0 == ulStrlen2)
    {
        return VOS_TRUE;
    }

    ulLen1      = ulStrlen1;
    pucTempStr1 = pucStr1;

    while (ulLen1 >= ulStrlen2)
    {
        ulLen1--;

        if (VOS_OK  == VOS_MemCmp(pucTempStr1, pucStr2, ulStrlen2))
        {
            return VOS_TRUE;
        }

        pucTempStr1++;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 Function   : SI_STK_SaveEnvelopeCmd
 Description: 缓存Envelope命令
 Input      :
 Return     : VOID
 History    :
1.日    期  : 2010年06月09日
  作    者  : m00128685
  修改内容  : Create
 *****************************************************************************/
VOS_VOID SI_STK_SaveEnvelopeCmd(VOS_UINT32 ulCmdLen, VOS_UINT8 *pucCmdData)
{
    (VOS_VOID)VOS_SmP(gulSTKApiSmId,500);

    gstSTKEnvelopeCmd.ulCmdLen = (ulCmdLen > sizeof(gstSTKEnvelopeCmd.aucCmdData))?
                                  sizeof(gstSTKEnvelopeCmd.aucCmdData):ulCmdLen;

    /*lint -e534*/
    VOS_MemCpy(gstSTKEnvelopeCmd.aucCmdData, pucCmdData, gstSTKEnvelopeCmd.ulCmdLen);

    VOS_SmV(gulSTKApiSmId);
    /*lint +e534*/

    return;
}

/*****************************************************************************
 Function   : SI_STK_ClearEnvelopeCmd
 Description: 清除缓存的Envelope命令
 Input      :
 Return     : VOID
 History    :
1.日    期  : 2010年06月09日
  作    者  : m00128685
  修改内容  : Create
 *****************************************************************************/
VOS_VOID SI_STK_ClearEnvelopeCmd(VOS_VOID)
{
    (VOS_VOID)VOS_SmP(gulSTKApiSmId,500);

    gstSTKEnvelopeCmd.ulCmdLen = 0;

    /*lint -e534*/
    VOS_SmV(gulSTKApiSmId);
    /*lint +e534*/

    return;
}

/*****************************************************************************
 Function   : SI_STK_CheckProfileCfg
 Description: 获取当前事件或主动命令在Profile中的配置信息
 Input      :
 Return     : VOS_UINT32
 History    :
1.日    期  : 2013年07月18日
  作    者  : H59254
  修改内容  : Create
 *****************************************************************************/
VOS_UINT32 SI_STK_CheckProfileCfg(VOS_UINT32 ulCmdType, SI_STK_CMD_PROFILE_CFG_STRU *pstCfgTbl, VOS_UINT32 ulTblSize)
{
    VOS_UINT32                          i;
    VOS_UINT8                           ucProfileLen = VOS_NULL;
    VOS_UINT8                          *pucProfile = VOS_NULL_PTR;

    STK_GetProfileInfo(&pucProfile, &ucProfileLen);

    for (i = 0; i < ulTblSize; i++)
    {
        if (pstCfgTbl[i].usCmdType == ulCmdType)
        {
            return SI_STKGetBitFromBuf(pucProfile, pstCfgTbl[i].usBitNum, ucProfileLen);
        }
    }

    /*配置表找不到的命令返回支持*/
    return VOS_TRUE;
}

/*****************************************************************************
 Prototype      : SI_STK_IsGULRATMode
 Description    : 事件下载判断是否下发，用于C+L产品
 Input          : 无
 Output         : VOS_TRUE:可以下发， VOS_FALSE: 不能下发
 Return Value   : 无
 History        : ---
  1.Date        : 2014-01-16
    Author      : zhuli
    Modification: Created function
*****************************************************************************/

VOS_BOOL SI_STK_IsGULRATMode(VOS_VOID)
{
    if ((VOS_TRUE == g_stLCEnableCfg.ucLCEnableFlg)&&(TAF_NVIM_LC_RAT_COMBINED_CL == g_stLCEnableCfg.enRatCombined))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
函 数 名  : SI_STK_EventDownload
功能描述  : STK功能事件下载函数
输入参数  : pEventData:下发数的数据结构
            ulEventLen: 下发数据的长度
            ulEventDownTag: 下发数据类型
            ulSDId:         下发数据的来源类型，高字节用于扩展透传参数，此为C+L项目扩展
输出参数  : 无
返 回 值  : SI_UINT32 函数执行结果
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2008年10月18日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
SI_VOID SI_STK_EventDownload(
    VOS_VOID                           *pEventData,
    VOS_UINT32                          ulEventLen,
    SI_STK_EVENT_TYPE                   ulEventDownTag,
    VOS_UINT32                          ulSDId)
{
    VOS_UINT8                           aucEvent[256] = {0};
    VOS_UINT8                          *pucEvent;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulSenderPara;
    SI_STK_EVENTDOWN_STRU              *pstEventData;

    if (SI_STK_PROLOCK == gstSTKCtrlStru.enSTKLock)
    {
        STK_WARNING_LOG("SI_STK_EventDownload: The STK is Locked");

        return;
    }

    pstEventData = (SI_STK_EVENTDOWN_STRU *)VOS_MemAlloc(MAPS_STK_PID,
                                                DYNAMIC_MEM_PT, sizeof(SI_STK_EVENTDOWN_STRU));

    if (VOS_NULL_PTR == pstEventData)
    {
        STK_WARNING_LOG("SI_STK_EventDownload:VOS_MemAlloc return NULL.");

        return;
    }

    pstEventData->DeviceId.ucSDId   = (VOS_UINT8)ulSDId;
    pstEventData->DeviceId.ucDDId   = SI_STK_DEV_UICC;
    pstEventData->EventDownTag      = ulEventDownTag;

    /*lint -e534*/
    VOS_MemCpy(&pstEventData->uEvent, pEventData, ulEventLen);
    /*lint +e534*/

    SI_STK_InitEventDown(aucEvent,
                        &pstEventData->DeviceId,
                        (VOS_UINT8)pstEventData->EventDownTag);

    ulResult = SI_STKCommCodeData(aucEvent + 1,
                                  SI_CODE_EVENT_DATA,
                                  pstEventData->EventDownTag,
                                  (SI_SAT_COMMDATA_STRU*)pstEventData);

    /*lint -e534*/
    VOS_MemFree(MAPS_STK_PID, pstEventData);
    /*lint +e534*/

    if (VOS_OK != ulResult)
    {
        STK_ERROR_LOG("SI_STK_EventDownload: SI_STKCommCodeData return error.");

        return ;
    }

    /*根据长度，如果大于0x7F需要在前面加上0x81，总长度也要加上0x81的长度*/
    if (aucEvent[2] > 0x7F)
    {
        aucEvent[1] = 0x81;

        ulDataLen   = aucEvent[2] + 3;

        pucEvent    = aucEvent;
    }
    else
    {
        ulDataLen   = aucEvent[2]+2;

        pucEvent    = aucEvent + 1;
    }

    ulSenderPara = ((ulSDId&0xFF00)>>8);

    ulResult = SI_STK_SendEnvelopeReqMsg(ulSenderPara, USIMM_GUTL_APP, (VOS_UINT8)ulDataLen, pucEvent);

    if (USIMM_API_SUCCESS == ulResult)
    {
        SI_STK_EventResendSave(ulSenderPara, ulDataLen, pucEvent);
    }
    else
    {
        STK_WARNING_LOG("SI_STK_EventDownload:USIMM_EnvelopeReq Fail.");
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_STK_SndProactiveCmd2CBP
功能描述  : STK主动命令发送到CPB处理
输入参数  : ulCmdLen:主动命令长度
            pucCmd:主动命令内容
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2013年12月19日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
VOS_VOID SI_STK_SndProactiveCmd2CBP(VOS_UINT32 ulCmdLen, VOS_UINT8 *pucCmd)
{
    CSIMA_STK_PROACTIVE_CMD_MSG_STRU   *pstMsg;

    pstMsg = (CSIMA_STK_PROACTIVE_CMD_MSG_STRU *)VOS_AllocMsg(MAPS_STK_PID,
                                                             (sizeof(CSIMA_STK_PROACTIVE_CMD_MSG_STRU)-VOS_MSG_HEAD_LENGTH));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->ulReceiverPid = WUEPS_PID_CSIMA;
    pstMsg->enIPCMsgId    = CSIMA_CBP_UICC_PROACTIVE_CMD_MSG;
    pstMsg->ulLen         = ulCmdLen;

    /*lint -e534*/
    VOS_MemCpy(pstMsg->aucProactiveCmd, pucCmd, ulCmdLen);
    /*lint +e534*/

    (VOS_VOID)VOS_SendMsg(MAPS_STK_PID, pstMsg);

    return;
}

/*****************************************************************************
函 数 名  : SI_STK_SendTerminalResponseReqMsg
功能描述  : STK模块发送TERMINAL RESPONSE数据
输入参数  : ucLen:TERMINAL RESPONSE数据长度
            pucRsp:TERMINAL RESPONSE数据内容
            ulPara:透传参数
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2015年01月30日
  作    者  : h00300778
  修改内容  : Create
*****************************************************************************/
/*lint -e669*/
VOS_UINT32 SI_STK_SendTerminalResponseReqMsg(VOS_UINT8 ucLen,VOS_UINT8 *pucRsp, USIMM_TR_PARA_ENUM_32 ulPara)
{
    USIMM_TERMINALRESPONSE_REQ_STRU    *pstMsg;

    pstMsg = (USIMM_TERMINALRESPONSE_REQ_STRU *)VOS_AllocMsg(MAPS_STK_PID,
                                                            (sizeof(USIMM_TERMINALRESPONSE_REQ_STRU)-VOS_MSG_HEAD_LENGTH)+ucLen);

    if(VOS_NULL_PTR == pstMsg)
    {
        STK_WARNING_LOG("SI_STK_SendTerminalResponse: VOS_AllocMsg is Failed");/*打印错误*/

        return VOS_ERR; /*返回函数错误信息*/
    }

    /* 填充消息内容 */
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.enMsgName       = USIMM_STKTERMINALRSP_REQ;
    pstMsg->stMsgHeader.ulSendPara      = ulPara;
    pstMsg->ucDataLen                   = ucLen;

    /*lint -e534*/
    VOS_MemCpy(pstMsg->aucContent, pucRsp, ucLen);
    /*lint +e534*/

    return VOS_SendMsg(MAPS_STK_PID, pstMsg);
}
/*lint +e669*/
/*****************************************************************************
函 数 名  : SI_STK_SendResetReqMsg
功能描述  : STK模块发送REFRESH的请求
输入参数  : pstCMDDetail:REFRESH命令的参数
            pstRstInfo:REFRESH命令中的FILE LIST和AID信息
            ulPara:透传参数
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2015年02月02日
  作    者  : h00300778
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 SI_STK_SendResetReqMsg(
    USIMM_STK_COMMAND_DETAILS_STRU     *pstCMDDetail,
    USIMM_RESET_INFO_STRU              *pstRstInfo)
{
    USIMM_STKREFRESH_REQ_STRU             *pstMsg;

    pstMsg = (USIMM_STKREFRESH_REQ_STRU *)VOS_AllocMsg(MAPS_STK_PID,
                                                       sizeof(USIMM_STKREFRESH_REQ_STRU)-VOS_MSG_HEAD_LENGTH + pstRstInfo->usFileListLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        STK_WARNING_LOG("SI_STK_SendResetReqMsg: VOS_AllocMsg is Failed");/*打印错误*/

        return VOS_ERR; /*返回函数错误信息*/
    }

    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.enMsgName       = USIMM_STKREFRESH_REQ;

    pstMsg->ulCommandNum                = pstCMDDetail->ucCommandNum;
    pstMsg->ulCommandType               = pstCMDDetail->ucCommandType;
    pstMsg->enRefreshType               = pstCMDDetail->ucCommandQua;

    if (USIMM_AID_LEN_MAX < pstRstInfo->usAidLen)
    {
        pstMsg->ulAidLen = USIMM_AID_LEN_MAX;
    }
    else
    {
        pstMsg->ulAidLen = pstRstInfo->usAidLen;
    }

    if (VOS_NULL != pstMsg->ulAidLen)
    {
        /*lint -e534*/
        VOS_MemCpy(pstMsg->aucAid, pstRstInfo->aucAid, pstMsg->ulAidLen);
        /*lint +e534*/
    }

    pstMsg->usLen = pstRstInfo->usFileListLen;

    if (VOS_NULL != pstRstInfo->usFileListLen)
    {
        /*lint -e534*/
        VOS_MemCpy(pstMsg->aucFileList, pstRstInfo->aucFileList, pstRstInfo->usFileListLen);
        /*lint +e534*/
    }

    return VOS_SendMsg(MAPS_STK_PID, pstMsg);
}

/*****************************************************************************
函 数 名  : SI_STK_SendEnvelopeReqMsg
功能描述  : STK模块发送ENVELOPE数据
输入参数  : ucLen:TERMINAL RESPONSE数据长度
            pucRsp:TERMINAL RESPONSE数据内容
            ulPara:透传参数
输出参数  : 无
返 回 值  : 无
History     :
1.日    期  : 2015年01月30日
  作    者  : h00300778
  修改内容  : Create
2.日    期  : 2015年06月18日
  作    者  : c00299064
  修改内容  : add apptype
*****************************************************************************/
VOS_UINT32 SI_STK_SendEnvelopeReqMsg(
    VOS_UINT32                          ulSendPara,
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT8                           ucLen,
    VOS_UINT8                          *pucEnvelope
)
{
    USIMM_STKENVELOPE_REQ_STRU            *pstMsg;

    pstMsg = (USIMM_STKENVELOPE_REQ_STRU *)VOS_AllocMsg(MAPS_STK_PID,
                                                     (sizeof(USIMM_STKENVELOPE_REQ_STRU)-VOS_MSG_HEAD_LENGTH)+ucLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        STK_WARNING_LOG("SI_STK_SendEnvelopeReqMsg: VOS_AllocMsg is Failed");/*打印错误*/

        return VOS_ERR; /*返回函数错误信息*/
    }

    /* 填充消息内容 */
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.enMsgName       = USIMM_STKENVELOPE_REQ;
    pstMsg->stMsgHeader.ulSendPara      = ulSendPara;
    pstMsg->stMsgHeader.enAppType       = enAppType;
    pstMsg->ucDataLen                   = ucLen;

    /*lint -e534*/
    VOS_MemCpy(pstMsg->aucContent, pucEnvelope, ucLen);
    /*lint +e534*/

    return VOS_SendMsg(MAPS_STK_PID, pstMsg);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




