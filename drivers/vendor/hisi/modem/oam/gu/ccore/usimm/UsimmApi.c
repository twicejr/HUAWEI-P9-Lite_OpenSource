/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : UsimmApi.c
  Author       : zhuli 00100318
  Version      : V100R002
  Date         : 2008-5-15
  Description  : 该C文件给出了---接口模块实现
  Function List:
  History      :
 ************************************************************************/
#include "product_config.h"

#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)
#include "UsimmApi.h"
#include "usimmapdu.h"
#include "usimmbase.h"
#include "usimmglobal.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_USIMM_API_C
/*lint +e767*/

#if defined (__PS_WIN32_RECUR__) || defined (__DART__)
VOS_UINT8 g_ucCardType = USIMM_CARD_USIM;
#endif

/*****************************************************************************
函 数 名  :USIMM_ApiParaCheckSimple
功能描述  :下发请求的检查，不包括vSIM的状态检查，实现原参数检查功能
输入参数  :ucClientId:调用者ID
输出参数  :pulSendPid:调用PID
返 回 值  :USIMM_API_SUCCESS
           USIMM_API_FAILED
           USIMM_API_WRONG_PARA
           USIMM_API_NOTAVAILABLE
           USIMM_API_NOCARD
           USIMM_API_ALLOCMEM_FAILED
           USIMM_API_SENDMSG_FAILED
调用函数  :USIMM_ClientToPid
被调函数  :
修订记录  :
1. 日    期   : 2010年8月10日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_ApiParaCheckSimple(VOS_VOID)
{
    VOS_UINT32                          ulUsimmOpenSpeed;

    ulUsimmOpenSpeed         = USIMM_CCB_GetUsimOpenSpeed();
    if ((USIMM_PHYCARD_TYPE_NOCARD == USIMM_CCB_GetCardType())
     || (USIMM_OPENSPEEDENABLE == ulUsimmOpenSpeed))/*卡状态检查*/
    {
        USIMM_WARNING_LOG("USIMM_ApiParaCheck: The Card Status is Wrong");

        return USIMM_API_NOTAVAILABLE;
    }

    return USIMM_API_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_ApiParaCheck
功能描述  :下发请求的检查，包括vSIM的状态检查，如果vSIM打开函数返回USIMM_API_NOTAVAILABLE
输入参数  :ucClientId:调用者ID
输出参数  :pulSendPid:调用PID
返 回 值  :USIMM_API_SUCCESS
           USIMM_API_FAILED
           USIMM_API_WRONG_PARA
           USIMM_API_NOTAVAILABLE
           USIMM_API_NOCARD
           USIMM_API_ALLOCMEM_FAILED
           USIMM_API_SENDMSG_FAILED
调用函数  :USIMM_ClientToPid
被调函数  :
修订记录  :
1. 日    期   : 2010年8月10日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/

VOS_UINT32 USIMM_ApiParaCheck(VOS_VOID)
{
    VOS_UINT32 ulResult;

    if(VOS_TRUE == USIMM_VsimIsActive())    /*vSIM功能打开*/
    {
        USIMM_WARNING_LOG("USIMM_ApiParaCheck: The vSIM is Open");

        return USIMM_API_NOTAVAILABLE;
    }

    ulResult = USIMM_ApiParaCheckSimple();

    if(USIMM_API_SUCCESS != ulResult)
    {
        return ulResult;
    }

    return USIMM_API_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_AsciiToHexCode
功能描述  :转换字符串格式
输入参数  :

输出参数  :无
返 回 值  :VOS_OK    :失败
           VOS_ERR   :成功

修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/

VOS_UINT32 USIMM_AsciiToHexCode(
    VOS_CHAR                           *pucSrc,
    VOS_UINT32                          ulSrcLen,
    VOS_CHAR                           *pucDst,
    VOS_UINT32                         *pulDstLen
)
{
    VOS_UINT16                          usChkLen = 0;
    VOS_UINT8                           ucTmp    = 0;
    VOS_CHAR                            ucLeft   = 0;
    VOS_CHAR                           *pucDest  = pucDst;

    while(usChkLen < ulSrcLen)
    {
        if ( (pucSrc[usChkLen] >= '0') && (pucSrc[usChkLen] <= '9') ) /* the number is 0-9 */
        {
            ucLeft = pucSrc[usChkLen] - '0';
        }
        else if ( (pucSrc[usChkLen] >= 'a') && (pucSrc[usChkLen] <= 'f') ) /* the number is 0-9 */
        {
            ucLeft = pucSrc[usChkLen] - 'a' + 0x0a;
        }
        else if ( (pucSrc[usChkLen] >= 'A') && (pucSrc[usChkLen] <= 'F') ) /* the number is 0-9 */
        {
            ucLeft = pucSrc[usChkLen] - 'A' + 0x0a;
        }
        else if ((pucSrc[usChkLen] >= '\0') )
        {
            break;
        }
        else
        {
            return VOS_ERR;
        }

        pucDest[ucTmp] = (VOS_CHAR)(0xf0 & ((VOS_UINT8)ucLeft << 4));

        usChkLen += 1;

        if ( (pucSrc[usChkLen] >= '0') && (pucSrc[usChkLen] <= '9') ) /* the number is 0-9 */
        {
            pucDest[ucTmp] |= pucSrc[usChkLen] - '0';
        }
        else if ( (pucSrc[usChkLen] >= 'a') && (pucSrc[usChkLen] <= 'f') ) /* the number is 0-9 */
        {
            pucDest[ucTmp] |= pucSrc[usChkLen] - 'a' + 0x0a;
        }
        else if ( (pucSrc[usChkLen] >= 'A') && (pucSrc[usChkLen] <= 'F') ) /* the number is 0-9 */
        {
            pucDest[ucTmp] |= pucSrc[usChkLen] - 'A' + 0x0a;
        }
        else if ((pucSrc[usChkLen] >= '\0') )
        {
            break;
        }
        else
        {
            return VOS_ERR;
        }

        usChkLen += 1;

        ucTmp += 1;
    }

    *pulDstLen = ucTmp;

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_GetFilePathFormStr
功能描述  :获取文件路径
输入参数  :

输出参数  :无
返 回 值  :VOS_OK    :失败
           VOS_ERR   :成功

修订记录  :
1. 日    期   : 2015年02月12日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/

VOS_UINT32 USIMM_GetFilePathFormStr(USIMM_FILEPATH_INFO_STRU *pstFilePath,
                                                VOS_UINT16             *pusDFID,
                                                VOS_UINT16             *pusSubDFID,
                                                VOS_UINT16             *pusEFID)
{
    VOS_CHAR                            aucPath[USIMM_PATHSTR_MAX_LEN];
    VOS_UINT32                          ulPathLen;
    VOS_UINT16                          usFileID;
    VOS_UINT16                          usTmp;

    if (VOS_NULL_WORD == pstFilePath->ulPathLen)
    {
        return VOS_ERR;
    }

    if (VOS_OK != USIMM_AsciiToHexCode(pstFilePath->acPath, pstFilePath->ulPathLen, aucPath, &ulPathLen))
    {
        return VOS_ERR;
    }

    usFileID        = aucPath[ulPathLen - 2] & 0xFF;
    usTmp           = aucPath[ulPathLen - 1] & 0xFF;
    usFileID        = ((usFileID << 0x08) & 0xFF00) + usTmp;

    if (aucPath[ulPathLen - 2] == 0x3F)
    {
        *pusDFID    = usFileID;

        *pusEFID    = VOS_NULL;

        *pusSubDFID = VOS_NULL;
    }
    else if (aucPath[ulPathLen - 2] == 0x5F)
    {
        *pusSubDFID = usFileID;

        usFileID    = aucPath[ulPathLen - 4] & 0xFF;
        usTmp       = aucPath[ulPathLen - 3] & 0xFF;
        usFileID    = ((usFileID << 0x08) & 0xFF00) + usTmp;

        *pusDFID    = usFileID;

        *pusEFID    = VOS_NULL;
    }
    else if (aucPath[ulPathLen - 2] == 0x7F)
    {
        *pusDFID    = usFileID;

        *pusEFID    = VOS_NULL;

        *pusSubDFID = VOS_NULL;
    }
    else if (aucPath[ulPathLen - 2] == 0x2F)
    {
        *pusEFID    = usFileID;

        *pusDFID    = MF;

        *pusSubDFID = VOS_NULL;
    }
    else if (aucPath[ulPathLen - 2] == 0x4F)
    {
        *pusEFID    = usFileID;

        usFileID    = aucPath[ulPathLen - 4] & 0xFF;
        usTmp       = aucPath[ulPathLen - 3] & 0xFF;
        usFileID    = ((usFileID << 0x08) & 0xFF00) + usTmp;

        *pusSubDFID = usFileID;

        usFileID    = aucPath[ulPathLen - 6] & 0xFF;
        usTmp       = aucPath[ulPathLen - 5] & 0xFF;
        usFileID    = ((usFileID << 0x08) & 0xFF00) + usTmp;

        *pusDFID    = usFileID;
    }
    else if (aucPath[ulPathLen - 2] == 0x6F)
    {
        *pusEFID    = usFileID;

        usFileID    = aucPath[ulPathLen - 4] & 0xFF;
        usTmp       = aucPath[ulPathLen - 3] & 0xFF;
        usFileID    = ((usFileID << 0x08) & 0xFF00) + usTmp;

        *pusSubDFID = VOS_NULL;

        *pusDFID    = usFileID;
    }
    else
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : USIMM_GetEFileIDFromStr
功能描述  : 获取文件名称,函数会识别出文件路径最后路径属于哪一个文件层级，
            调用者应先判断返回层级是否正确，再使用获取文件名
输入参数  : pstFilePath : 文件路径
            pusFID      : 获取后文件名称

输出参数  : 无
返 回 值  : USIMM_CARD_FILE_TYPE_ENUM

修订记录  :
1. 日    期   : 2015年3月31日
   作    者   : d00212987
   修改内容   : 卡多应用迭代II开发
*****************************************************************************/
USIMM_FILE_TYPE_ENUM_UINT32 USIMM_GetFileIDFromStr(
    USIMM_FILEPATH_INFO_STRU           *pstFilePath,
    VOS_UINT16                         *pusFID
)
{
    VOS_CHAR                            aucPath[USIMM_PATHSTR_MAX_LEN];
    VOS_UINT32                          ulPathLen;
    VOS_UINT16                          usFileID;
    VOS_UINT16                          usTmp;
    USIMM_FILE_TYPE_ENUM_UINT32         enCardFileType;

    if (VOS_NULL_WORD == pstFilePath->ulPathLen)
    {
        return USIMM_FILE_TYPE_BUTT;
    }

    if (VOS_OK != USIMM_AsciiToHexCode(pstFilePath->acPath, pstFilePath->ulPathLen, aucPath, &ulPathLen))
    {
        return USIMM_FILE_TYPE_BUTT;
    }

    usFileID        = aucPath[ulPathLen - 2] & 0xFF;
    usTmp           = aucPath[ulPathLen - 1] & 0xFF;
    usFileID        = ((usFileID << 0x08) & 0xFF00) + usTmp;

    if (aucPath[ulPathLen - 2] == 0x3F)
    {
        enCardFileType = USIMM_DF_FILE;
    }
    else if (aucPath[ulPathLen - 2] == 0x5F)
    {
        enCardFileType = USIMM_DF_FILE;
    }
    else if (aucPath[ulPathLen - 2] == 0x7F)
    {
        enCardFileType = USIMM_DF_FILE;
    }
    else if (aucPath[ulPathLen - 2] == 0x2F)
    {
        enCardFileType = USIMM_EF_FILE;
    }
    else if (aucPath[ulPathLen - 2] == 0x4F)
    {
        enCardFileType = USIMM_EF_FILE;
    }
    else if (aucPath[ulPathLen - 2] == 0x6F)
    {
        enCardFileType = USIMM_EF_FILE;
    }
    else
    {
        enCardFileType = USIMM_FILE_TYPE_BUTT;
    }

    *pusFID           = usFileID;

    return enCardFileType;
}

/*****************************************************************************
函 数 名  :USIMM_StrToFilePath
功能描述  :转换文件路径格式
输入参数  :

输出参数  :无
返 回 值  :VOS_OK    :失败
           VOS_ERR   :成功

修订记录  :
1. 日    期   : 2015年02月12日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/

VOS_UINT32 USIMM_StrToFilePath(USIMM_FILEPATH_INFO_STRU *pstFilePath,
                                        VOS_UINT16              *pusPath,
                                        VOS_UINT32              *pusPathLen)
{
    VOS_UINT8       aucPath[USIMM_PATHSTR_MAX_LEN];
    VOS_UINT32      ulPathLen;
    VOS_UINT16      usFileID;
    VOS_UINT32      i;

    if ((VOS_NULL_PTR == pstFilePath)||(VOS_NULL_PTR == pusPath)||(VOS_NULL_PTR == pusPathLen))
    {
        return VOS_ERR;
    }

    if (VOS_NULL_WORD == pstFilePath->ulPathLen)
    {
        *pusPathLen = 0;

        return VOS_ERR;
    }

    if (VOS_OK != USIMM_AsciiToHexCode(pstFilePath->acPath, pstFilePath->ulPathLen, (VOS_CHAR *)aucPath, &ulPathLen))
    {
        *pusPathLen = 0;

        return VOS_ERR;
    }

    for(i=0; i<(ulPathLen/2); i++)
    {
        usFileID = (VOS_UINT16)(aucPath[i*2]<<8) + aucPath[i*2+1];

        pusPath[i] = usFileID;
    }

    *pusPathLen = ulPathLen/2;

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_ChangePathToAsciiString
功能描述  :将U8类型的文件路径转换成字符串类型路径
输入参数  :pucPath:U8类型路径内容
           ucPathLen:路径长度
输出参数  :pucDest:输出的路径内容
           pusLen:输出的路径长度
返 回 值  :无
修订记录  :
1. 日    期   : 2015年02月06日
   作    者   : h00300778
   修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_ChangePathToAsciiString(
    VOS_UINT8                           *pucPath,
    VOS_UINT8                            ucPathLen,
    USIMM_FILEPATH_INFO_STRU            *pstFilePath)
{
    VOS_UINT8                          *pucWrite = (VOS_UINT8 *)pstFilePath->acPath;
    VOS_UINT8                          *pucRead = pucPath;
    VOS_UINT8                           ucHigh = 0;
    VOS_UINT8                           ucLow = 0;
    VOS_UINT16                          usLen = 0;
    VOS_UINT16                          usChkLen = 0;

    if(0 != ucPathLen)
    {
        /* 扫完整个字串 */
        while (usChkLen++ < ucPathLen)
        {
            ucHigh = 0x0F & (*pucRead >> 4);
            ucLow = 0x0F & *pucRead;

            usLen += 2;    /* 记录长度 */

            if (0x09 >= ucHigh)   /* 0-9 */
            {
                *pucWrite++ = ucHigh + 0x30;
            }
            else if (0x0A <= ucHigh)    /* A-F */
            {
                *pucWrite++ = ucHigh + 0x37;
            }
            else
            {

            }

            if (0x09 >= ucLow)   /* 0-9 */
            {
                *pucWrite++ = ucLow + 0x30;
            }
            else if (0x0A <= ucLow)    /* A-F */
            {
                *pucWrite++ = ucLow + 0x37;
            }
            else
            {

            }

            /* 下一个字符 */
            pucRead++;
        }
    }

    pstFilePath->ulPathLen = usLen;

    return;
}

/*****************************************************************************
函 数 名  :USIMM_SendInitCardMsg
功能描述  :发送初始化卡消息
输入参数  :ulSenderPid:发送请求的PID
           enMsgType:消息类型
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2015年02月12日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendInitCardMsg(VOS_UINT32 ulSenderPid, USIMM_CMDTYPE_REQ_ENUM_UINT32 enMsgType)
{
    USIMM_CMDHEADER_REQ_STRU           *pstMsg = VOS_NULL_PTR;

    pstMsg = (USIMM_CMDHEADER_REQ_STRU *)VOS_AllocMsg(ulSenderPid,
                                                      sizeof(USIMM_CMDHEADER_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        USIMM_ERROR_LOG("USIMM_InitCardStart:AllocMsg Failed.");

        return VOS_ERR;
    }

    pstMsg->ulReceiverPid      = WUEPS_PID_USIM;
    pstMsg->enMsgName          = enMsgType;
    pstMsg->enAppType          = USIMM_GUTL_APP;
    pstMsg->ulSendPara         = VOS_NULL;

    if (VOS_OK != VOS_SendMsg(ulSenderPid, pstMsg))
    {
        USIMM_ERROR_LOG("USIMM_SendInitCardMsg:SendMsg Failed.\n");

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_VsimIsActive
功能描述  :读取NV判断vSIM卡是否激活
输入参数  :无
输出参数  :无
返 回 值  :VOS_TRUE:vSIM卡激活
           VOS_FALSE:vSIM卡未激活
调用函数  :NV_Read
被调函数  :
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/
VOS_BOOL USIMM_VsimIsActive(VOS_VOID)
{
#if (FEATURE_VSIM == FEATURE_ON)
    VSIM_CARD_STATE_NV_STRU             stNvData;

#if defined(INSTANCE_1)
    /* SVLTE下Modem1虚拟卡永远不使能 */
    if (VOS_TRUE == USIMM_IsSvlte())
    {
        return VOS_FALSE;
    }
#elif defined (INSTANCE_2)
    if (VOS_TRUE == USIMM_IsSvlte())
    {
        return VOS_FALSE;
    }
#endif
    if(NV_OK != NV_Read(en_NV_Item_VSIM_SUPPORT_FLAG, &stNvData, sizeof(stNvData)))
    {
        USIMM_ERROR_LOG("USIMM_VsimIsActive:Read NV Failed.\n");
        return VOS_FALSE;
    }

    if(VSIM_VIRT_CARD_DEACTIVE == stNvData.enVsimState)
    {
        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
#else
    return VOS_FALSE;
#endif
}

/*****************************************************************************
函 数 名  :USIMM_ChangeDefFileToPath
功能描述  :转换文件扩展名称到真实文件路径
输入参数  :enDefFileID 定义的文件扩展名称
输出参数  :ppcPathStr  文件路径
返 回 值  :
修订记录  :
1. 日    期   : 2015年02月12日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_ChangeDefFileToPath(USIMM_DEF_FILEID_ENUM_UINT32  enDefFileID,
                                     VOS_CHAR                    **ppcPathStr)
{
    if ((enDefFileID >= USIMM_DEF_FILEID_BUTT) || (VOS_NULL_PTR == ppcPathStr))
    {
        USIMM_ERROR_LOG("USIMM_ChangeDefFileToPath: The Para is Fail");

        return VOS_ERR;
    }

    *ppcPathStr = (VOS_CHAR *)g_stUSIMMFilePathTable[enDefFileID].pcFilePath;

    USIMM_NORMAL_LOG("USIMM_ChangeDefFileToPath: The File Path has Found");

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_ChangePathToDefFileID
功能描述  :根据文件路径查询文件的扩展名称
输入参数  :ulPathLen  文件路径长度
           pcPathStr  文件路径内容
输出参数  :penDefFileID 文件扩展名称
返 回 值  :
修订记录  :
1. 日    期   : 2015年2月12日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_ChangePathToDefFileID(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT32                          ulPathLen,
    VOS_CHAR                           *pcPathStr,
    USIMM_DEF_FILEID_ENUM_UINT32       *penDefFileID)
{
    VOS_UINT32                          i;
    VOS_CHAR                            acTemp[USIMM_PATHSTR_MAX_LEN] = {0};
    VOS_INT32                           lRslt;

    if ((VOS_NULL_PTR == pcPathStr)
        ||(VOS_NULL_PTR == penDefFileID)
        ||(VOS_NULL == ulPathLen)
        ||(ulPathLen > (USIMM_PATHSTR_MAX_LEN-1)))
    {
        USIMM_ERROR_LOG("USIMM_ChangePathToDefFileID: The Para is wrong");

        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemCpy(acTemp, pcPathStr, ulPathLen);
    /*lint +e534*/

    acTemp[ulPathLen] = '\0';

    for (i=0; i<ARRAYSIZE(g_stUSIMMFilePathTable); i++)
    {
        lRslt = VOS_StrCmp((VOS_CHAR *)g_stUSIMMFilePathTable[i].pcFilePath, acTemp);

        if ((VOS_OK == lRslt)
            && ((enAppType == g_stUSIMMFilePathTable[i].enAppType)
            || (USIMM_UNLIMIT_AUTO == g_stUSIMMFilePathTable[i].enAppType)))
        {
            *penDefFileID = i;

            USIMM_NORMAL_LOG("USIMM_ChangePathToDefFileID: The File Path has Found");

            return VOS_OK;
        }
    }

    USIMM_NORMAL_LOG("USIMM_ChangePathToDefFileID: The File Path is Unknow");

    return VOS_ERR;
}

/*****************************************************************************
函 数 名  :USIMM_QueryPINType
功能描述  :查询PIN操作类型确定　
输入参数  :
输出参数  :无
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1. 日    期   : 2009年1月20日
   作    者   : m00128685
   修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_QueryPINType(
    USIMM_APP_PIN_INFO_STRU            *pstPin1Info,
    USIMM_APP_PIN_INFO_STRU            *pstPin2Info,
    VOS_UINT8                          *pucPINType
)
{
    /*根据校验状态判断需查寻的PIN码类型*/
    if(USIMM_PUK_BLOCK == pstPin1Info->enPinVerified)
    {
        USIMM_NORMAL_LOG("USIMM_QueryPINType: The Card PUK is Block");

        *pucPINType = USIMM_PUK;
    }
    else if(USIMM_PUK_NEED == pstPin1Info->enPinVerified)/*先判断PUK状态*/
    {
        USIMM_NORMAL_LOG("USIMM_QueryPINType: The Card Need the PUK Password");

        *pucPINType = USIMM_PUK;
    }
    else if(USIMM_PIN_NEED == pstPin1Info->enPinVerified) /*再判断当前PIN1状态*/
    {
        USIMM_NORMAL_LOG("USIMM_QueryPINType: The Card Need the PIN Password");

        *pucPINType = USIMM_PIN;
    }
    else if(USIMM_PUK_NEED == pstPin2Info->enPinVerified)   /*再判断PUK2状态*/
    {
        USIMM_NORMAL_LOG("USIMM_QueryPINType: The Card Need the PUK2 Password");

        *pucPINType = USIMM_PUK2;
    }
    else  /*再判断PIN2状态*/                                                                                  /*最后默认需要PIN2*/
    {
        USIMM_NORMAL_LOG("USIMM_QueryPINType: The Card Need the PIN2 Password");

        *pucPINType = USIMM_PIN2;
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_PINHandleType
功能描述  :PIN操作类型确定　
输入参数  :
输出参数  :无
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1. 日    期   : 2009年1月19日
   作    者   : m00128685
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_HandlePINType(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT8                           ucCmdType,
    VOS_UINT32                         *pulPINType
)
{
    VOS_UINT32                          ulResult = VOS_OK;
    USIMM_APP_PIN_INFO_STRU            *pstPin1Info;
    USIMM_APP_PIN_INFO_STRU            *pstPin2Info;

    pstPin1Info = USIMM_CCB_GetPIN1InfoByApp(enAppType);
    pstPin2Info = USIMM_CCB_GetPIN2InfoByApp(enAppType);

    if ((VOS_NULL_PTR == pstPin1Info)
    ||  (VOS_NULL_PTR == pstPin2Info))
    {
        USIMM_ERROR_LOG("USIMM_HandlePINType: pstPin1Info is Null Ptr");
        return VOS_ERR;
    }

    switch(ucCmdType)
    {
        case USIMM_PINCMD_DISABLE:          /*激活，去激活和验证PIN用同一函数处理*/
            if (USIMM_PIN_ENABLED == pstPin1Info->enPinEnable)
            {
                *pulPINType = USIMM_PIN;
            }
            else if (USIMM_PIN_ENABLED == pstPin2Info->enPinEnable)
            {
                *pulPINType = USIMM_PIN2;
            }
            else
            {
                USIMM_ERROR_LOG("USIMM_HandlePINType: The PIN Enable State is Error");

                ulResult = VOS_ERR;
            }

            break;

        case USIMM_PINCMD_VERIFY:
            if (USIMM_PIN_NEED == pstPin1Info->enPinVerified)
            {
                *pulPINType = USIMM_PIN;
            }
            else if (USIMM_PIN_NEED == pstPin2Info->enPinVerified)
            {
                *pulPINType = USIMM_PIN2;
            }
            else
            {
                USIMM_ERROR_LOG("USIMM_HandlePINType: The PIN Verified State is Error");

                ulResult = VOS_ERR;
            }

            break;

        case USIMM_PINCMD_UNBLOCK:          /*解锁PIN处理*/
            if (USIMM_PUK_NEED == pstPin1Info->enPinVerified)
            {
                *pulPINType = USIMM_PIN;
            }
            else if (USIMM_PUK_NEED == pstPin2Info->enPinVerified)
            {
                *pulPINType = USIMM_PIN2;
            }
            else
            {
                USIMM_ERROR_LOG("USIMM_HandlePINType: The PIN Block State is Error");

                ulResult = VOS_ERR;
            }

            break;

        default:
            USIMM_ERROR_LOG("USIMM_HandlePINType: The PIN Cmd Type State is Error");
            break;
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_IsServiceAvailable
功能描述  :获取卡服务状态　
输入参数  :enService:服务ID
输出参数  :无
返 回 值  :PS_USIM_SERVICE_NOT_AVAILIABLE
           PS_USIM_SERVICE_NOT_AVAILIABLE
调用函数  :USIMM_PoolFindFile
           USIMM_GetBitFromBuf
被调函数  :
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_IsServiceAvailable(UICC_SERVICES_TYPE_ENUM_UINT32 enService)
{
    VOS_UINT32                          ulResult;

    /* 参数检查 */
    if (UICC_SVR_NONE == enService)
    {
        USIMM_WARNING_LOG("USIMM_IsServiceAvailable: The Parameter is Wrong");

        return PS_USIM_SERVICE_NOT_AVAILIABLE;
    }

    if (VOS_OK != VOS_TaskLock())
    {
        USIMM_WARNING_LOG("USIMM_IsServiceAvailable: SmP Error");

        return PS_USIM_SERVICE_NOT_AVAILIABLE;
    }

    if (enService < SIM_SVR_BUTT)
    {
        ulResult = USIMM_IsSIMServiceAvailable(enService);

        /*lint -e534*/
        VOS_TaskUnlock();
        /*lint +e534*/

        return ulResult;
    }

    if (enService < USIM_SVR_BUTT)
    {
        ulResult = USIMM_IsUSIMServiceAvailable(enService);

        /*lint -e534*/
        VOS_TaskUnlock();
        /*lint +e534*/

        return ulResult;
    }

    if (enService < ISIM_SVR_BUTT)
    {
        ulResult = USIMM_IsISIMServiceAvailable(enService);

        /*lint -e534*/
        VOS_TaskUnlock();
        /*lint +e534*/

        return ulResult;
    }

    if (enService < UIM_SVR_BUTT)
    {
        ulResult = USIMM_IsUIMServiceAvailable(enService);

        /*lint -e534*/
        VOS_TaskUnlock();
        /*lint +e534*/

        return ulResult;
    }

    if (enService < CSIM_SVR_BUTT)
    {
        ulResult = USIMM_IsCSIMServiceAvailable(enService);

        /*lint -e534*/
        VOS_TaskUnlock();
        /*lint +e534*/

        return ulResult;
    }

    /*lint -e534*/
    VOS_TaskUnlock();
    /*lint +e534*/

    USIMM_WARNING_LOG("USIMM_IsServiceAvailable: The Parameter is Wrong");

    return PS_USIM_SERVICE_NOT_AVAILIABLE;
}

/*****************************************************************************
函 数 名  :USIMM_IsTestCard
功能描述  :判断当前是否是测试卡，仅SIM/USIM卡中的PLMN号与NV项中的PLMN匹配时返回VOS_TRUE
           其它任何情况下都返回VOS_FALSE，如无卡，快速开机，IMSI未读取到，未初始化完成等
输入参数  :无
输出参数  : 无
返 回 值  :VOS_TRUE/VOS_FALSE
修订记录  :
1. 日    期   : 2013年1月4日
   作    者   : H59254
   修改内容   : Creat
*****************************************************************************/
VOS_BOOL USIMM_IsTestCard(VOS_VOID)
{
    VOS_UINT32                          ulFileNum;
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          i;
    USIMM_TEST_CARD_CFG_ST              stPlmnInfo;
    VOS_UINT8                           aucPLMN[USIMM_TEST_CARD_PLMN_LEN] = {0};
    VOS_UINT32                          ulUsimmOpenSpeed;

    ulRslt = NV_Read(en_NV_Item_Test_Card_Cfg, &stPlmnInfo, sizeof(USIMM_TEST_CARD_CFG_ST));

    if ((VOS_OK != ulRslt)
     || (USIMM_TEST_CARD_CFG_NUM < stPlmnInfo.ulPlmnNum))
    {
        USIMM_WARNING_LOG("USIMM_IsTestCard: Read NV is Failed");

        return VOS_FALSE;
    }

    if (VOS_OK != VOS_TaskLock())
    {
        USIMM_WARNING_LOG("USIMM_IsTestCard: SmP Error");

        return VOS_FALSE;
    }

    ulUsimmOpenSpeed               = USIMM_CCB_GetUsimOpenSpeed();

    if ((USIMM_CCB_GetAppService(USIMM_GUTL_APP) != USIMM_CARD_SERVIC_AVAILABLE)
     || (USIMM_OPENSPEEDENABLE == ulUsimmOpenSpeed))/*卡状态检查*/
    {
        /*lint -e534*/
        VOS_TaskUnlock();
        /*lint +e534*/

        USIMM_WARNING_LOG("USIMM_IsTestCard: The Card Status is Wrong");

        return VOS_FALSE;
    }

    /* 查询当前的文件缓冲 */
    if (USIMM_API_SUCCESS != USIMM_PoolFindFile(0x6F07, &ulFileNum, USIMM_GUTL_APP))
    {
        /*lint -e534*/
        VOS_TaskUnlock();
        /*lint +e534*/

        USIMM_WARNING_LOG("USIMM_IsTestCard: Read File is Failed");

        return VOS_FALSE;
    }

    /*lint -e534*/
    VOS_MemCpy(aucPLMN, USIMM_CCB_GetPoolFileByIndex(ulFileNum)->pucContent + 1, USIMM_TEST_CARD_PLMN_LEN);

    VOS_TaskUnlock();
    /*lint +e534*/

    aucPLMN[0] &= 0xF0;

    for (i = 0; i < stPlmnInfo.ulPlmnNum; i++)
    {
        /*lint -e534*/
        if (VOS_OK == VOS_MemCmp(aucPLMN,
        /*lint +e534*/
                                 stPlmnInfo.astPlmnList[i].aucPlmn,
                                 USIMM_TEST_CARD_PLMN_LEN))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
函 数 名  :USIMM_IsCdmaTestCard
功能描述  :判断当前是否是Cdma测试卡，仅UIM/CSIM卡中的HPLMN号与NV项中的PLMN匹配时返回VOS_TRUE
           其它任何情况下都返回VOS_FALSE，如无卡，快速开机，IMSI未读取到，未初始化完成等
输入参数  :无
输出参数  : 无
返 回 值  :VOS_TRUE/VOS_FALSE
修订记录  :
1. 日    期   : 2013年1月4日
   作    者   : H59254
   修改内容   : Creat
*****************************************************************************/
VOS_BOOL USIMM_IsCdmaTestCard(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          ulFileNum;
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          i;
    USIMM_TEST_CARD_CFG_ST              stPlmnInfo;
    VOS_UINT8                           aucPLMN[USIMM_CDMATEST_CARD_PLMN_LEN] = {0};
    VOS_UINT32                          ulUsimmOpenSpeed;

    ulRslt = NV_Read(en_NV_Item_Cdma_Test_Card_Cfg,
                    &stPlmnInfo,
                    sizeof(USIMM_CDMATEST_CARD_CFG_ST));

    if ((VOS_OK != ulRslt)
     || (USIMM_TEST_CARD_CFG_NUM < stPlmnInfo.ulPlmnNum))
    {
        USIMM_WARNING_LOG("USIMM_IsCdmaTestCard: Read NV is Failed");

        return VOS_FALSE;
    }

    if (VOS_OK != VOS_TaskLock())
    {
        USIMM_WARNING_LOG("USIMM_IsCdmaTestCard: SmP Error");

        return VOS_FALSE;
    }

    ulUsimmOpenSpeed               = USIMM_CCB_GetUsimOpenSpeed();

    if ((USIMM_CCB_GetAppService(USIMM_CDMA_APP) != USIMM_CARD_SERVIC_AVAILABLE)
     || (USIMM_OPENSPEEDENABLE == ulUsimmOpenSpeed))/*卡状态检查*/
    {
        /*lint -e534*/
        VOS_TaskUnlock();
        /*lint +e534*/

        USIMM_WARNING_LOG("USIMM_IsCdmaTestCard: The Card Status is Wrong");

        return VOS_FALSE;
    }

    /* 查询当前的文件缓冲 */
    if (USIMM_API_SUCCESS != USIMM_PoolFindFile(EF_CUIM_IMSIM, &ulFileNum, USIMM_CDMA_APP))
    {
        /*lint -e534*/
        VOS_TaskUnlock();
        /*lint +e534*/

        USIMM_WARNING_LOG("USIMM_IsCdmaTestCard: Read File is Failed");

        return VOS_FALSE;
    }

    /*lint -e534*/
    VOS_MemCpy(aucPLMN,
                USIMM_CCB_GetPoolFileByIndex(ulFileNum)->pucContent+8,
                USIMM_CDMATEST_CARD_PLMN_LEN);  /*MCC长度2字节*/

    VOS_TaskUnlock();
    /*lint +e534*/

    for (i = 0; i < stPlmnInfo.ulPlmnNum; i++)
    {
        /*lint -e534*/
        if (VOS_OK == VOS_MemCmp(aucPLMN,
                                 stPlmnInfo.astPlmnList[i].aucPlmn,
                                 USIMM_CDMATEST_CARD_PLMN_LEN)) /*之间比较不需要转换*/
        {
            return VOS_TRUE;
        }
        /*lint +e534*/
    }

    return VOS_FALSE;
#else
    return VOS_FALSE;
#endif
}

/*****************************************************************************
函 数 名  :USIMM_GetPinStatus
功能描述  :获取PIN信息　
输入参数  :ucType:          PIN类型

输出参数  : pucBeEnable:  PIN是否开启
            pucBeNeed:PIN是否需要
            pucNum:PIN剩余次数
返 回 值  :USIMM_API_WRONG_PARA
           USIMM_API_SUCCESS
调用函数  :无
被调函数  :
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat
2.日    期  : 2011年5月26日
    作    者  : w00184875
    修改内容  : [DTS2011052606230],H3G需求，PUK码被锁时上报PUK码剩余次数
*****************************************************************************/
VOS_UINT32  USIMM_GetPinStatus(VOS_UINT8 *pucType,VOS_UINT8 *pucBeEnable,VOS_UINT8 *pucBeNeed,VOS_UINT8 *pucNum)
{
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    USIMM_PIN_TYPE_ENUM_UINT32          enPINType;
    USIMM_APP_PIN_INFO_STRU            *pstPin1Info;
    USIMM_APP_PIN_INFO_STRU            *pstPin2Info;
    USIMM_PHYCARD_TYPE_ENUM_UINT32      enCardType;

    /*卡状态检查*/
    enAppType  = USIMM_CCB_GetMainAppType();
    enCardType = USIMM_CCB_GetCardType();

    if ((USIMM_PHYCARD_TYPE_NOCARD == enCardType)
      || (USIMM_CARDAPP_BUTT <= enAppType))
    {
        USIMM_WARNING_LOG("USIMM_GetPinStatus: The Card Status is Wrong");

        return USIMM_API_NOTAVAILABLE;
    }

    if (USIMM_OPENSPEEDENABLE == USIMM_CCB_GetUsimOpenSpeed())
    {
        USIMM_WARNING_LOG("USIMM_GetPinStatus: Speed Open Mode");

        *pucBeNeed = USIMM_PIN_NONEED;

        return USIMM_API_SUCCESS;
    }

    pstPin1Info = USIMM_CCB_GetPIN1InfoByApp(enAppType);
    pstPin2Info = USIMM_CCB_GetPIN2InfoByApp(enAppType);

    if ((VOS_NULL_PTR == pstPin1Info)
    ||  (VOS_NULL_PTR == pstPin2Info))
    {
        USIMM_ERROR_LOG("USIMM_GetPinStatus: pstPin1Info is Null Ptr");
        return VOS_ERR;
    }

    if (USIMM_CARD_SERVIC_UNAVAILABLE == USIMM_CCB_GetAppService(enAppType))
    {
        if (USIMM_PUK_BLOCK == pstPin1Info->enPinVerified)
        {
            *pucType = USIMM_PUK;

            *pucNum  = (VOS_UINT8)(pstPin1Info->ucPukRemainTime);
            *pucBeNeed = USIMM_PUK_BLOCK;

            return USIMM_API_SUCCESS;
        }
        else
        {
            USIMM_WARNING_LOG("USIMM_GetPinStatus: The Card Status is Wrong");

            return USIMM_API_NOTAVAILABLE;
        }
    }

    if( USIMM_SIM_NON == *pucType )
    {
        USIMM_QueryPINType(pstPin1Info, pstPin2Info, pucType);
    }

    enPINType = *pucType;

    switch(enPINType)
    {
        /* 获取PIN1信息 */
        case USIMM_PIN:
            *pucBeEnable = (VOS_UINT8)(pstPin1Info->enPinEnable);
            *pucBeNeed   = (VOS_UINT8)(pstPin1Info->enPinVerified);
            *pucNum      = (VOS_UINT8)(pstPin1Info->ucPinRemainTime);
            break;

        /* 获取PIN2信息 */
        case USIMM_PIN2:
            *pucBeEnable = (VOS_UINT8)(pstPin2Info->enPinEnable);
            *pucBeNeed   = USIMM_PIN_NEED;
            *pucNum      = (VOS_UINT8)(pstPin2Info->ucPinRemainTime);
            break;

        /* 获取PUK1信息目前返回剩余次数 */
        case USIMM_PUK:
            *pucNum      = (VOS_UINT8)(pstPin1Info->ucPukRemainTime);
            break;

        /* 获取PUK2(信息目前返回剩余次数 */
        case USIMM_PUK2:
            *pucNum      = (VOS_UINT8)(pstPin2Info->ucPukRemainTime);
            break;

        default:
            USIMM_WARNING_LOG("USIMM_GetPinStatus: The PIN Type is Wrong");
            return USIMM_API_WRONG_PARA;
    }

    return USIMM_API_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_GetCardType
功能描述  :获取卡类型和卡服务状态　
输入参数  :enCardType:卡类型
输出参数  :pucCardType:卡状态
返 回 值  :USIMM_API_SUCCESS
调用函数  :无
被调函数  :
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_GetCardType(
    USIMM_CARD_TYPE_ENUM_UINT32         enCardType,
    USIMM_CARD_SERVIC_ENUM_UINT32      *pulCardStatus )
{
    if ((VOS_NULL_PTR == pulCardStatus) || (enCardType > USIMM_CARD_CSIM))
    {
        return USIMM_API_FAILED;
    }

    if ((USIMM_PHYCARD_TYPE_ICC == USIMM_CCB_GetCardType()) && (USIMM_CARD_SIM == enCardType))
    {
        *pulCardStatus = USIMM_CCB_GetAppService(USIMM_GUTL_APP);

        return USIMM_API_SUCCESS;
    }
    else if ((USIMM_PHYCARD_TYPE_UICC == USIMM_CCB_GetCardType()) && (USIMM_CARD_USIM == enCardType))
    {
        *pulCardStatus = USIMM_CCB_GetAppService(USIMM_GUTL_APP);

        return USIMM_API_SUCCESS;
    }
    else if ((USIMM_PHYCARD_TYPE_ICC == USIMM_CCB_GetCardType()) && (USIMM_CARD_UIM == enCardType))
    {
        *pulCardStatus = USIMM_CCB_GetAppService(USIMM_CDMA_APP);

        return USIMM_API_SUCCESS;
    }
    else if ((USIMM_PHYCARD_TYPE_UICC == USIMM_CCB_GetCardType()) && (USIMM_CARD_CSIM == enCardType))
    {
        *pulCardStatus = USIMM_CCB_GetAppService(USIMM_CDMA_APP);

        return USIMM_API_SUCCESS;
    }
    else if ((USIMM_PHYCARD_TYPE_UICC == USIMM_CCB_GetCardType()) && (USIMM_CARD_ISIM == enCardType))
    {
        *pulCardStatus = USIMM_CCB_GetAppService(USIMM_IMS_APP);

        return USIMM_API_SUCCESS;
    }
    else
    {
        *pulCardStatus = USIMM_CARD_SERVIC_ABSENT;

        return USIMM_API_FAILED;
    }
}

/*****************************************************************************
函 数 名  :USIMM_GetCardTypeByAppType
功能描述  :根据APP类型获取卡类型和卡服务状态　
输入参数  :enAppType:应用类型
输出参数  :pucCardStatus:卡服务状态
           pucCardType:卡状态
返 回 值  :VOS_OK/VOS_ERR
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : h00300778
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_GetCardTypeByAppType(
    VOS_UINT8                          *pucCardStatus,
    VOS_UINT8                          *pucCardType,
    USIMM_CARDAPP_ENUM_UINT32           enAppType)
{
    if (VOS_NULL_PTR != pucCardStatus)
    {
        if (USIMM_GUTL_APP == enAppType)
        {
            *pucCardStatus = (VOS_UINT8)USIMM_CCB_GetAppService(USIMM_GUTL_APP);
        }
        else if (USIMM_IMS_APP == enAppType)
        {
            *pucCardStatus = (VOS_UINT8)USIMM_CCB_GetAppService(USIMM_IMS_APP);
        }
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
        else if (USIMM_CDMA_APP == enAppType)
        {
            *pucCardStatus = (VOS_UINT8)USIMM_CCB_GetAppService(USIMM_CDMA_APP);
        }
#endif
        else
        {
            return VOS_ERR;
        }
    }

    if(VOS_NULL_PTR != pucCardType)
    {
        if (enAppType >= USIMM_CARDAPP_BUTT)
        {
            return VOS_ERR;
        }

        *pucCardType = (VOS_UINT8)USIMM_COMM_CardAppToType(enAppType);
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_GetCachedFile
功能描述  :获取缓冲的文件内容接口
输入参数  :无
输出参数  :usFileID   输入参数，读取的文件ID
           pulDataLen 输出参数  返回文件的内容长度
           ppucData   输出参数  返回文件内容的地址
返 回 值  :USIMM_API_SUCCESS
           USIMM_API_FAILED
           USIMM_API_WRONG_PARA
调用函数  :无
被调函数  :
修订记录  :
1. 日    期   : 2011年9月19日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_GetCachedFile(
    VOS_CHAR                           *pusFileStr,
    VOS_UINT32                         *pulDataLen,
    VOS_UINT8                         **ppucData,
    USIMM_CARDAPP_ENUM_UINT32           enAppType)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulRecordNum;
    VOS_UINT16                          usEFID;
    USIMM_FILEPATH_INFO_STRU            stFilePath;
    USIMM_POOL_ST                      *pstPoolGlobal;

    pstPoolGlobal       =  USIMM_CCB_GetFilePoolTotalGlobal();

    if(USIMM_OPENSPEEDENABLE == USIMM_CCB_GetUsimOpenSpeed())
    {
        USIMM_WARNING_LOG("USIMM_GetCachedFile: The Open Speed Mode is Not Support it");

        return USIMM_API_FAILED;
    }

    if (USIMM_CCB_GetAppService(enAppType) != USIMM_CARD_SERVIC_AVAILABLE)/*卡状态检查*/
    {
        USIMM_WARNING_LOG("USIMM_GetCachedFile: The Card Status is Wrong");

        return USIMM_API_FAILED;
    }

    if((USIMM_POOL_NOINTIAL == pstPoolGlobal->enPoolStatus)
     ||(0                   == pstPoolGlobal->ucPoolFileCount)
     ||(VOS_NULL_PTR        == pusFileStr))   /*状态检查*/
    {
        USIMM_WARNING_LOG("USIMM_GetCachedFile: Parameter wrong");/*打印错误*/

        return USIMM_API_WRONG_PARA;
    }

    stFilePath.ulPathLen = VOS_StrLen(pusFileStr);

    /*lint -e534*/
    VOS_MemCpy(stFilePath.acPath, pusFileStr, stFilePath.ulPathLen);
    /*lint +e534*/

    if (USIMM_EF_FILE != USIMM_GetFileIDFromStr(&stFilePath, &usEFID))
    {
        USIMM_WARNING_LOG("USIMM_GetCachedFile: USIMM_GetFilePathFormStr wrong");/*打印错误*/

        return USIMM_API_WRONG_PARA;
    }

    /* 查询文件位置 */
    ulResult    =   USIMM_PoolFindFile(usEFID, &ulRecordNum, enAppType);

    if(VOS_ERR == ulResult)
    {
        USIMM_ERROR_LOG("USIMM_GetCachedFile: File Could not Found");/*打印错误*/

        return USIMM_API_WRONG_PARA;
    }

    if(VOS_NULL_PTR == USIMM_CCB_GetPoolFileByIndex(ulRecordNum)->pucContent)
    {
        USIMM_ERROR_LOG("USIMM_PoolReadOneFile: File Content is Empty");/*打印错误*/

        return USIMM_API_WRONG_PARA;
    }

    *pulDataLen = USIMM_CCB_GetPoolFileByIndex(ulRecordNum)->usLen;

    *ppucData = USIMM_CCB_GetPoolFileByIndex(ulRecordNum)->pucContent;

    return USIMM_API_SUCCESS;
}


/*old API 2阶段删除或者修改替换*/

/*****************************************************************************
函 数 名  : USIMM_GetCardIMSI
功能描述  : 获取IMSI接口
输入参数  : 无
输出参数  : pucImsi 存储文件内容
返 回 值  : USIMM_API_SUCCESS

调用函数  :无
被调函数  :
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_GetCardIMSI(VOS_UINT8 *pucImsi)
{
    VOS_UINT32  ulResult;

    if(VOS_NULL_PTR == pucImsi)
    {
        USIMM_WARNING_LOG("USIMM_GetCardIMSI: The Parameter is Error");

        return USIMM_API_WRONG_PARA;
    }

    if(USIMM_OPENSPEEDENABLE == USIMM_CCB_GetUsimOpenSpeed())
    {
        ulResult = NV_Read(en_NV_Item_EF6F07, (VOS_VOID *)pucImsi, USIMM_EF_IMSI_LEN);

        return ((ulResult == VOS_OK)?USIMM_API_SUCCESS:USIMM_API_FAILED);/* [false alarm]: 屏蔽Fortify 错误 */
    }

    if(USIMM_CCB_GetAppService(USIMM_GUTL_APP) != USIMM_CARD_SERVIC_AVAILABLE)/*卡状态检查*/
    {
        USIMM_WARNING_LOG("USIMM_GetCardIMSI: The Card Status is Wrong");

        return USIMM_API_FAILED;
    }

    if (VOS_OK != VOS_TaskLock())
    {
        USIMM_WARNING_LOG("USIMM_GetCardIMSI: SmP Error");

        return USIMM_API_FAILED;
    }

    if(VOS_OK == USIMM_PoolReadOneFile(EFIMSI, USIMM_EF_IMSI_LEN, pucImsi, USIMM_GUTL_APP))
    {
        /*lint -e534*/
        VOS_TaskUnlock();
        /*lint +e534*/

        return USIMM_API_SUCCESS;
    }

    /*lint -e534*/
    VOS_TaskUnlock();
    /*lint +e534*/

    USIMM_WARNING_LOG("USIMM_GetCardIMSI: USIMM_PoolReadOneFile Error");

    return USIMM_API_NOTAVAILABLE;
}

/*****************************************************************************
函 数 名  : USIMM_GetCdmaIMSIM
功能描述  : 获取IMSI_M接口
输入参数  : 无
输出参数  : pucImsi 存储文件内容
返 回 值  : USIMM_API_SUCCESS

调用函数  :无
被调函数  :
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_GetCdmaIMSIM(
    VOS_UINT8                           *pucImsiM)
{
    if(VOS_NULL_PTR == pucImsiM)
    {
        USIMM_WARNING_LOG("USIMM_GetCdmaIMSIM: The Parameter is Error");

        return USIMM_API_WRONG_PARA;
    }

    if(USIMM_OPENSPEEDENABLE == USIMM_CCB_GetUsimOpenSpeed())
    {
        USIMM_WARNING_LOG("USIMM_GetCdmaIMSIM: The OpenSpeed is ON");

        return USIMM_API_FAILED;   /* [false alarm]: 屏蔽Fortify 错误 */
    }

    if(USIMM_CCB_GetAppService(USIMM_CDMA_APP) != USIMM_CARD_SERVIC_AVAILABLE)/*卡状态检查*/
    {
        USIMM_WARNING_LOG("USIMM_GetCdmaIMSIM: The Card Status is Wrong");

        return USIMM_API_FAILED;
    }

    if (VOS_OK != VOS_TaskLock())
    {
        USIMM_WARNING_LOG("USIMM_GetCdmaIMSIM: SmP Error");

        return USIMM_API_FAILED;
    }

    if(VOS_OK == USIMM_PoolReadOneFile(EF_CUIM_IMSIM, USIMM_EF_CIMSI_LEN, pucImsiM, USIMM_CDMA_APP))
    {
        /*lint -e534*/
        VOS_TaskUnlock();
        /*lint +e534*/

        return USIMM_API_SUCCESS;
    }

    /*lint -e534*/
    VOS_TaskUnlock();
    /*lint +e534*/

    USIMM_WARNING_LOG("USIMM_GetCdmaIMSIM: USIMM_PoolReadOneFile Error");

    return USIMM_API_NOTAVAILABLE;
}

/*****************************************************************************
函 数 名  : USIMM_GetPinRemainTime
功能描述  : 获取pin码操作剩余次数
输入参数  :
输出参数  : 无
返 回 值  : VOS_UINT32，表示函数执行结果
调用函数  :
被调函数  : 外部接口
*****************************************************************************/
VOS_UINT32 USIMM_GetPinRemainTime(USIMM_PIN_REMAIN_STRU *pstRemainTime)
{
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    USIMM_APP_PIN_INFO_STRU            *pstPin1Info;
    USIMM_APP_PIN_INFO_STRU            *pstPin2Info;

    if (USIMM_PHYCARD_TYPE_NOCARD == USIMM_CCB_GetCardType())
    {
        USIMM_WARNING_LOG("USIMM_GetPinRemainTime: The Card is not exsit.");

        return USIMM_API_NOTAVAILABLE;
    }

    enAppType = USIMM_CCB_GetMainAppType();

    if (USIMM_CARDAPP_BUTT <= enAppType)
    {
        return USIMM_API_FAILED;
    }

    pstPin1Info = USIMM_CCB_GetPIN1InfoByApp(enAppType);
    pstPin2Info = USIMM_CCB_GetPIN2InfoByApp(enAppType);

    if ((VOS_NULL_PTR == pstPin1Info)
    ||  (VOS_NULL_PTR == pstPin2Info))
    {
        USIMM_ERROR_LOG("USIMM_GetPinRemainTime: pstPin1Info is Null Ptr");
        return VOS_ERR;
    }

    pstRemainTime->ucPin1RemainTime = pstPin1Info->ucPinRemainTime;
    pstRemainTime->ucPin2RemainTime = pstPin2Info->ucPinRemainTime;
    pstRemainTime->ucPuk1RemainTime = pstPin1Info->ucPukRemainTime;
    pstRemainTime->ucPuk2RemainTime = pstPin2Info->ucPukRemainTime;

    return USIMM_API_SUCCESS;
}

/*****************************************************************************
函 数 名  : USIMM_BdnQuery
功能描述  : BDN状态查询接口
输入参数  : 无
输出参数  : 无
返 回 值  : SI_UINT32 函数执行结果
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2008年10月20日
  作    者  : H59254
  修改内容  : Create
*****************************************************************************/
VOS_VOID USIMM_BdnQuery(VOS_UINT32 *pulState)
{
    if(VOS_NULL_PTR != pulState)
    {
        *pulState = USIMM_CCB_GetAppBDN(USIMM_GUTL_APP);
    }

    return ;
}

/*****************************************************************************
函 数 名  : USIMM_FdnQuery
功能描述  : FDN状态查询接口
输入参数  : 无
输出参数  : 无
返 回 值  : SI_UINT32 函数执行结果
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2008年10月20日
  作    者  : H59254
  修改内容  : Create
*****************************************************************************/
VOS_VOID USIMM_FdnQuery(VOS_UINT32 *pulUsimFdnState, VOS_UINT32 *pulCsimFdnState)
{
    if(VOS_NULL_PTR != pulUsimFdnState)
    {
        *pulUsimFdnState = USIMM_CCB_GetAppFDN(USIMM_GUTL_APP);
    }

    /*中国电信不要支持FDN功能，默认关闭*/
    if(VOS_NULL_PTR != pulCsimFdnState)
    {
        *pulCsimFdnState = USIMM_FDNSTATUS_OFF;
    }

    return ;
}

/*****************************************************************************
函 数 名  :USIMM_ActiveCardReq
功能描述  :SIM卡激活请求
输入参数  :ulSenderPid:发送请求的PID
输出参数  :无
返 回 值  :VOS_OK
           VOS_ERR
被调函数  :
修订记录  :
1. 日    期   : 2010年 7 月 26日
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_ActiveCardReq(VOS_UINT32 ulSenderPid)
{
    if(USIMM_OPENSPEEDENABLE == USIMM_CCB_GetUsimOpenSpeed())/*卡状态检查*/
    {
        USIMM_WARNING_LOG("USIMM_ActiveCardReq: The Card Status is Wrong");

        return VOS_ERR;
    }

    if (VOS_ERR == USIMM_SendInitCardMsg(ulSenderPid, USIMM_ACTIVECARD_REQ))
    {
        USIMM_WARNING_LOG("USIMM_ActiveCardReq: VOS_SendMsg is Failed");/*打印错误*/

        return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
函 数 名  :USIMM_SCICardOutNotify
功能描述  :SIM卡热插拔注册给底软的回调函数,底软保证在中断中调用此函数，因此不需要增加信号量保护
输入参数  :卡的状态
输出参数  :无
返 回 值  :

修订记录  :
1. 日    期   : 2012年3月14日
   作    者   : w00184875
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_SCICardOutNotify(VOS_UINT ulCardInOutStatus)
{
    USIMM_CARD_INOUT_IND_STRU           *pUsimMsg;

    /*lint -e534*/
    LogPrint1("USIMM_SCICardOutNotify: The card status is %d .\r\n", (VOS_INT)ulCardInOutStatus);
    /*lint +e534*/

    if (USIMM_OPENSPEEDENABLE == USIMM_CCB_GetUsimOpenSpeed())
    {
        return;
    }

    if(VOS_TRUE == USIMM_VsimIsActive())    /*vSIM功能打开*/
    {
        USIMM_WARNING_LOG("USIMM_SCICardOutNotify: The vSIM is Open");

        return;
    }

    pUsimMsg = (USIMM_CARD_INOUT_IND_STRU*)VOS_AllocMsg(WUEPS_PID_USIM,
                                                sizeof(USIMM_CARD_INOUT_IND_STRU)-VOS_MSG_HEAD_LENGTH);

    if(VOS_NULL_PTR == pUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_CardInOutHandle: VOS_AllocMsg is Failed");

        return;
    }

    pUsimMsg->enMsgType         = USIMM_CARD_INOUT_IND;
    pUsimMsg->ulReceiverPid     = WUEPS_PID_USIM;
    pUsimMsg->ulSenderPid       = WUEPS_PID_USIM;
    pUsimMsg->ulCardInOutStatus = (VOS_UINT32)ulCardInOutStatus;

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pUsimMsg);

    return;
}

/*****************************************************************************
函 数 名  :USIMM_SciCardStatusIndCbFunc
功能描述  :CE产品上SIM卡热插拔注册给底软的回调函数,底软保证在中断中调用此函数，因此不需要增加信号量保护
输入参数  :卡的状态
输出参数  :无
返 回 值  :无
修订记录  :
1. 日    期   : 2013年9月23日
   作    者   : H59254
   修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_SciCardStatusIndCbFunc(USIMM_CARDSTATUS_IND_ENUM_UINT32 enCardStatus)
{
    USIMM_CARD_STATUS_IND_STRU         *pstMsg;

    if (USIMM_OPENSPEEDENABLE == USIMM_CCB_GetUsimOpenSpeed())
    {
        return;
    }

    if (VOS_TRUE == USIMM_VsimIsActive())    /*vSIM功能打开*/
    {
        return;
    }

    pstMsg = (USIMM_CARD_STATUS_IND_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                                                       sizeof(USIMM_CARD_STATUS_IND_STRU)-VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        USIMM_ERROR_LOG("USIMM_SciCardStatusIndCbFunc: VOS_AllocMsg is Failed");

        return;
    }

    pstMsg->enMsgType         = USIMM_CARDSTATUS_CB_IND;
    pstMsg->ulReceiverPid     = WUEPS_PID_USIM;
    pstMsg->ulSenderPid       = MAPS_PIH_PID;
    pstMsg->ulCardStatus      = enCardStatus;

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstMsg);

    return;
}


/*****************************************************************************
函 数 名  :USIMM_GetAid
功能描述  :获取AID请求
输入参数  :ulAidType:AID类型
输出参数  :pulLen:返回的数据长度
           pucAid:AID的内容
返 回 值  :USIMM_API_SUCCESS:成功，其余失败

修订记录  :
1.日    期  : 2013年12月19日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 USIMM_GetAid(VOS_UINT32 ulAidType, VOS_UINT32 *pulLen, VOS_UINT8 *pucAid)
{
    USIMM_AID_INFO_STRU         *pstAIDInfo;

    if ((VOS_NULL_PTR == pulLen) || (VOS_NULL_PTR == pucAid))
    {
        return USIMM_API_WRONG_PARA;
    }


    pstAIDInfo = USIMM_CCB_GetAIDByApp(ulAidType);

    if (VOS_NULL_PTR == pstAIDInfo)
    {
        return USIMM_API_WRONG_PARA;
    }

    /*lint -e534*/
    VOS_MemCpy(pucAid, pstAIDInfo->aucAID, pstAIDInfo->ulAIDLen);
    /*lint +e534*/

    *pulLen = pstAIDInfo->ulAIDLen;

    return USIMM_API_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_GetCardCGType
功能描述  :获取C or G 请求
输入参数  :
输出参数  :
返 回 值  :USIMM_API_SUCCESS:成功，其余失败

修订记录  :
1.日    期  : 2014年06月04日
  作    者  : zhuli
  修改内容  : Create
*****************************************************************************/

VOS_UINT32 USIMM_GetCardCGType(
    VOS_UINT32                          *pulCardMode,
    VOS_BOOL                            *pbHasCModule,
    VOS_BOOL                            *pbHasWGModule)
{
    if ((VOS_NULL_PTR == pulCardMode)
        || (VOS_NULL_PTR == pbHasCModule)
        || (VOS_NULL_PTR == pbHasWGModule))
    {
        return USIMM_API_WRONG_PARA;
    }

    *pulCardMode = USIMM_CCB_GetCardVersion();

    if (VOS_NULL_PTR == USIMM_CCB_GetAIDByApp(USIMM_CDMA_APP))
    {
        *pbHasCModule = VOS_FALSE;
    }
    else
    {
        *pbHasCModule = VOS_TRUE;
    }

    if (VOS_NULL_PTR == USIMM_CCB_GetAIDByApp(USIMM_GUTL_APP))
    {
        *pbHasWGModule = VOS_FALSE;
    }
    else
    {
        *pbHasWGModule = VOS_TRUE;
    }

    return USIMM_API_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_GetPbDfPath
功能描述  :获取USIM卡PHONEBOOK路径
输入参数  :无
输出参数  :无
返 回 值  :无

修订记录  :
1.日    期  : 2014年06月04日
  作    者  : h00300778
  修改内容  : Create
*****************************************************************************/
VOS_UINT16 USIMM_GetPbDfPath(VOS_VOID)
{
    return gstUSIMMBaseInfo.stPBInfo.usPBDfID;
}

#if (FEATURE_VSIM == FEATURE_ON)
/*****************************************************************************
函 数 名  :USIMM_SaveHvteeVsimData
功能描述  :保存共享内存中的VSIM数据
输入参数  : ulDataLen: 数据长度
            pucVsimData:数据内容
输出参数  : 无
返 回 值  : 无

修订记录  :
1.日    期  : 2014年10月09日
  作    者  : 祝锂
  修改内容  : Create
*****************************************************************************/

VOS_VOID USIMM_SaveHvteeVsimData(
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                           *pucVsimData
)
{
    if ((VOS_NULL_PTR == pucVsimData) || (VOS_NULL == ulDataLen))
    {
        USIMM_WARNING_LOG("USIMM_SaveHvteeVsimData: The para is Wrong");
        return;
    }

    if (g_pucUSIMMVsimData != VOS_NULL_PTR)
    {
        (VOS_VOID)VOS_MemFree(WUEPS_PID_USIM, g_pucUSIMMVsimData);
    }

    g_pucUSIMMVsimData = VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, ulDataLen+1);  /*多申请一个字节用于存储'\0'*/

    if (VOS_NULL_PTR == g_pucUSIMMVsimData) /*申请失败会复位*/
    {
        USIMM_WARNING_LOG("USIMM_SaveHvteeVsimData: The VOS_MemAlloc is Wrong");
        return;
    }

    (VOS_VOID)VOS_MemCpy(g_pucUSIMMVsimData, pucVsimData, ulDataLen);

    g_pucUSIMMVsimData[ulDataLen] = '\0';

    return;
}
#endif /*(FEATURE_VSIM == FEATURE_ON)*/


#else

#include "UsimmApi.h"
#include "usimmbase.h"
#include "usimmglobal.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_USIMM_API_C
/*lint +e767*/

#if defined (__PS_WIN32_RECUR__) || defined (__DART__)
VOS_UINT8 g_ucCardType = USIMM_CARD_USIM;
#endif

/*****************************************************************************
函 数 名  :USIMM_ApiParaCheckSimple
功能描述  :下发请求的检查，不包括vSIM的状态检查，实现原参数检查功能
输入参数  :ucClientId:调用者ID
输出参数  :pulSendPid:调用PID
返 回 值  :USIMM_API_SUCCESS
           USIMM_API_FAILED
           USIMM_API_WRONG_PARA
           USIMM_API_NOTAVAILABLE
           USIMM_API_NOCARD
           USIMM_API_ALLOCMEM_FAILED
           USIMM_API_SENDMSG_FAILED
调用函数  :USIMM_ClientToPid
被调函数  :
修订记录  :
1. 日    期   : 2010年8月10日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_ApiParaCheckSimple(VOS_VOID)
{
#if (FEATURE_OFF == FEATURE_UE_MODE_CDMA)
    if((gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService == USIMM_CARD_SERVIC_ABSENT)
        ||(USIMM_OPENSPEEDENABLE == gulUSIMMOpenSpeed))/*卡状态检查*/
    {
        USIMM_WARNING_LOG("USIMM_ApiParaCheck: The Card Status is Wrong");

        return USIMM_API_NOTAVAILABLE;
    }
#else
    if((gastUSIMMCardAppInfo[USIMM_UICC_CDMA].enCardService == USIMM_CARD_SERVIC_ABSENT)
        ||(USIMM_OPENSPEEDENABLE == gulUSIMMOpenSpeed))/*卡状态检查*/
    {
        USIMM_WARNING_LOG("USIMM_ApiParaCheck: The Card Status is Wrong");

        return USIMM_API_NOTAVAILABLE;
    }
#endif

    return USIMM_API_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_ApiParaCheck
功能描述  :下发请求的检查，包括vSIM的状态检查，如果vSIM打开函数返回USIMM_API_NOTAVAILABLE
输入参数  :ucClientId:调用者ID
输出参数  :pulSendPid:调用PID
返 回 值  :USIMM_API_SUCCESS
           USIMM_API_FAILED
           USIMM_API_WRONG_PARA
           USIMM_API_NOTAVAILABLE
           USIMM_API_NOCARD
           USIMM_API_ALLOCMEM_FAILED
           USIMM_API_SENDMSG_FAILED
调用函数  :USIMM_ClientToPid
被调函数  :
修订记录  :
1. 日    期   : 2010年8月10日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/

VOS_UINT32 USIMM_ApiParaCheck(VOS_VOID)
{
    VOS_UINT32 ulResult;

    if(VOS_TRUE == USIMM_VsimIsActive())    /*vSIM功能打开*/
    {
        USIMM_WARNING_LOG("USIMM_ApiParaCheck: The vSIM is Open");

        return USIMM_API_NOTAVAILABLE;
    }

    ulResult = USIMM_ApiParaCheckSimple();

    if(USIMM_API_SUCCESS != ulResult)
    {
        return ulResult;
    }

    return USIMM_API_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_AsciiToHexCode
功能描述  :转换字符串格式
输入参数  :

输出参数  :无
返 回 值  :VOS_OK    :失败
           VOS_ERR   :成功

修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/

VOS_UINT32 USIMM_AsciiToHexCode(
    VOS_CHAR                           *pucSrc,
    VOS_UINT32                          ulSrcLen,
    VOS_CHAR                           *pucDst,
    VOS_UINT32                         *pulDstLen
)
{
    VOS_UINT16                          usChkLen = 0;
    VOS_UINT8                           ucTmp    = 0;
    VOS_CHAR                            ucLeft   = 0;
    VOS_CHAR                           *pucDest  = pucDst;

    while(usChkLen < ulSrcLen)
    {
        if ( (pucSrc[usChkLen] >= '0') && (pucSrc[usChkLen] <= '9') ) /* the number is 0-9 */
        {
            ucLeft = pucSrc[usChkLen] - '0';
        }
        else if ( (pucSrc[usChkLen] >= 'a') && (pucSrc[usChkLen] <= 'f') ) /* the number is 0-9 */
        {
            ucLeft = pucSrc[usChkLen] - 'a' + 0x0a;
        }
        else if ( (pucSrc[usChkLen] >= 'A') && (pucSrc[usChkLen] <= 'F') ) /* the number is 0-9 */
        {
            ucLeft = pucSrc[usChkLen] - 'A' + 0x0a;
        }
        else if ((pucSrc[usChkLen] >= '\0') )
        {
            break;
        }
        else
        {
            return VOS_ERR;
        }

        pucDest[ucTmp] = (VOS_CHAR)(0xf0 & ((VOS_UINT8)ucLeft << 4));

        usChkLen += 1;

        if ( (pucSrc[usChkLen] >= '0') && (pucSrc[usChkLen] <= '9') ) /* the number is 0-9 */
        {
            pucDest[ucTmp] |= pucSrc[usChkLen] - '0';
        }
        else if ( (pucSrc[usChkLen] >= 'a') && (pucSrc[usChkLen] <= 'f') ) /* the number is 0-9 */
        {
            pucDest[ucTmp] |= pucSrc[usChkLen] - 'a' + 0x0a;
        }
        else if ( (pucSrc[usChkLen] >= 'A') && (pucSrc[usChkLen] <= 'F') ) /* the number is 0-9 */
        {
            pucDest[ucTmp] |= pucSrc[usChkLen] - 'A' + 0x0a;
        }
        else if ((pucSrc[usChkLen] >= '\0') )
        {
            break;
        }
        else
        {
            return VOS_ERR;
        }

        usChkLen += 1;

        ucTmp += 1;
    }

    *pulDstLen = ucTmp;

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_GetFilePathFormStr
功能描述  :获取文件路径
输入参数  :

输出参数  :无
返 回 值  :VOS_OK    :失败
           VOS_ERR   :成功

修订记录  :
1. 日    期   : 2015年02月12日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/

VOS_UINT32 USIMM_GetFilePathFormStr(USIMM_FILEPATH_INFO_STRU *pstFilePath,
                                                VOS_UINT16             *pusDFID,
                                                VOS_UINT16             *pusSubDFID,
                                                VOS_UINT16             *pusEFID)
{
    VOS_CHAR                            aucPath[USIMM_PATHSTR_MAX_LEN];
    VOS_UINT32                          ulPathLen;
    VOS_UINT16                          usFileID;
    VOS_UINT16                          usTmp;

    if (VOS_NULL_WORD == pstFilePath->ulPathLen)
    {
        return VOS_ERR;
    }

    if (VOS_OK != USIMM_AsciiToHexCode(pstFilePath->acPath, pstFilePath->ulPathLen, aucPath, &ulPathLen))
    {
        return VOS_ERR;
    }

    usFileID        = aucPath[ulPathLen - 2] & 0xFF;
    usTmp           = aucPath[ulPathLen - 1] & 0xFF;
    usFileID        = ((usFileID << 0x08) & 0xFF00) + usTmp;

    if (aucPath[ulPathLen - 2] == 0x3F)
    {
        *pusDFID    = usFileID;

        *pusEFID    = VOS_NULL;

        *pusSubDFID = VOS_NULL;
    }
    else if (aucPath[ulPathLen - 2] == 0x5F)
    {
        *pusSubDFID = usFileID;

        usFileID    = aucPath[ulPathLen - 4] & 0xFF;
        usTmp       = aucPath[ulPathLen - 3] & 0xFF;
        usFileID    = ((usFileID << 0x08) & 0xFF00) + usTmp;

        *pusDFID    = usFileID;

        *pusEFID    = VOS_NULL;
    }
    else if (aucPath[ulPathLen - 2] == 0x7F)
    {
        *pusDFID    = usFileID;

        *pusEFID    = VOS_NULL;

        *pusSubDFID = VOS_NULL;
    }
    else if (aucPath[ulPathLen - 2] == 0x2F)
    {
        *pusEFID    = usFileID;

        *pusDFID    = MF;

        *pusSubDFID = VOS_NULL;
    }
    else if (aucPath[ulPathLen - 2] == 0x4F)
    {
        *pusEFID    = usFileID;

        usFileID    = aucPath[ulPathLen - 4] & 0xFF;
        usTmp       = aucPath[ulPathLen - 3] & 0xFF;
        usFileID    = ((usFileID << 0x08) & 0xFF00) + usTmp;

        *pusSubDFID = usFileID;

        usFileID    = aucPath[ulPathLen - 6] & 0xFF;
        usTmp       = aucPath[ulPathLen - 5] & 0xFF;
        usFileID    = ((usFileID << 0x08) & 0xFF00) + usTmp;

        *pusDFID    = usFileID;
    }
    else if (aucPath[ulPathLen - 2] == 0x6F)
    {
        *pusEFID    = usFileID;

        usFileID    = aucPath[ulPathLen - 4] & 0xFF;
        usTmp       = aucPath[ulPathLen - 3] & 0xFF;
        usFileID    = ((usFileID << 0x08) & 0xFF00) + usTmp;

        *pusSubDFID = VOS_NULL;

        *pusDFID    = usFileID;
    }
    else
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_StrToFilePath
功能描述  :转换文件路径格式
输入参数  :

输出参数  :无
返 回 值  :VOS_OK    :失败
           VOS_ERR   :成功

修订记录  :
1. 日    期   : 2015年02月12日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/

VOS_UINT32 USIMM_StrToFilePath(USIMM_FILEPATH_INFO_STRU *pstFilePath,
                                        VOS_UINT16              *pusPath,
                                        VOS_UINT32              *pusPathLen)
{
    VOS_UINT8       aucPath[USIMM_PATHSTR_MAX_LEN];
    VOS_UINT32      ulPathLen;
    VOS_UINT16      usFileID;
    VOS_UINT32      i;

    if ((VOS_NULL_PTR == pstFilePath)||(VOS_NULL_PTR == pusPath)||(VOS_NULL_PTR == pusPathLen))
    {
        return VOS_ERR;
    }

    if (VOS_NULL_WORD == pstFilePath->ulPathLen)
    {
        *pusPathLen = 0;

        return VOS_ERR;
    }

    if (VOS_OK != USIMM_AsciiToHexCode(pstFilePath->acPath, pstFilePath->ulPathLen, (VOS_CHAR *)aucPath, &ulPathLen))
    {
        *pusPathLen = 0;

        return VOS_ERR;
    }

    for(i=0; i<(ulPathLen/2); i++)
    {
        usFileID = (VOS_UINT16)(aucPath[i*2]<<8) + aucPath[i*2+1];

        pusPath[i] = usFileID;
    }

    *pusPathLen = ulPathLen/2;

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_ChangePathToAsciiString
功能描述  :将U8类型的文件路径转换成字符串类型路径
输入参数  :pucPath:U8类型路径内容
           ucPathLen:路径长度
输出参数  :pucDest:输出的路径内容
           pusLen:输出的路径长度
返 回 值  :无
修订记录  :
1. 日    期   : 2015年02月06日
   作    者   : h00300778
   修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_ChangePathToAsciiString(VOS_UINT8 *pucPath, VOS_UINT8 ucPathLen, VOS_CHAR *pucDest, VOS_UINT16 *pusLen)
{
    VOS_UINT8                          *pucWrite = (VOS_UINT8 *)pucDest;
    VOS_UINT8                          *pucRead = pucPath;
    VOS_UINT8                           ucHigh = 0;
    VOS_UINT8                           ucLow = 0;
    VOS_UINT16                          usLen = 0;
    VOS_UINT16                          usChkLen = 0;

    if(0 != ucPathLen)
    {
        /* 扫完整个字串 */
        while (usChkLen++ < ucPathLen)
        {
            ucHigh = 0x0F & (*pucRead >> 4);
            ucLow = 0x0F & *pucRead;

            usLen += 2;    /* 记录长度 */

            if (0x09 >= ucHigh)   /* 0-9 */
            {
                *pucWrite++ = ucHigh + 0x30;
            }
            else if (0x0A <= ucHigh)    /* A-F */
            {
                *pucWrite++ = ucHigh + 0x37;
            }
            else
            {

            }

            if (0x09 >= ucLow)   /* 0-9 */
            {
                *pucWrite++ = ucLow + 0x30;
            }
            else if (0x0A <= ucLow)    /* A-F */
            {
                *pucWrite++ = ucLow + 0x37;
            }
            else
            {

            }

            /* 下一个字符 */
            pucRead++;
        }
    }

    *pusLen = usLen;

    return;
}

/*****************************************************************************
函 数 名  :USIMM_SendInitCardMsg
功能描述  :发送初始化卡消息
输入参数  :ulSenderPid:发送请求的PID
           enMsgType:消息类型
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2015年02月12日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendInitCardMsg(VOS_UINT32 ulSenderPid, USIMM_CMDTYPE_REQ_ENUM_UINT32 enMsgType)
{
    USIMM_CMDHEADER_REQ_STRU           *pstMsg = VOS_NULL_PTR;

    pstMsg = (USIMM_CMDHEADER_REQ_STRU *)VOS_AllocMsg(ulSenderPid,
                                                      sizeof(USIMM_CMDHEADER_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        USIMM_ERROR_LOG("USIMM_InitCardStart:AllocMsg Failed.");

        return VOS_ERR;
    }

    pstMsg->ulReceiverPid      = WUEPS_PID_USIM;
    pstMsg->enMsgName          = enMsgType;
    pstMsg->enAppType          = USIMM_GUTL_APP;
    pstMsg->ulSendPara         = VOS_NULL;

    if (VOS_OK != VOS_SendMsg(ulSenderPid, pstMsg))
    {
        USIMM_ERROR_LOG("USIMM_SendInitCardMsg:SendMsg Failed.\n");

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_VsimIsActive
功能描述  :读取NV判断vSIM卡是否激活
输入参数  :无
输出参数  :无
返 回 值  :VOS_TRUE:vSIM卡激活
           VOS_FALSE:vSIM卡未激活
调用函数  :NV_Read
被调函数  :
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/
VOS_BOOL USIMM_VsimIsActive(VOS_VOID)
{
#if (FEATURE_VSIM == FEATURE_ON)
    VSIM_CARD_STATE_NV_STRU stNvData;

#if defined(INSTANCE_1)
    /* SVLTE下Modem1虚拟卡永远不使能 */
    if (VOS_TRUE == USIMM_IsSvlte())
    {
        return VOS_FALSE;
    }
#elif defined (INSTANCE_2)
    if (VOS_TRUE == USIMM_IsSvlte())
    {
        return VOS_FALSE;
    }
#endif

    if(NV_OK != NV_Read(en_NV_Item_VSIM_SUPPORT_FLAG, &stNvData, sizeof(stNvData)))
    {
        USIMM_ERROR_LOG("USIMM_VsimIsActive:Read NV Failed.\n");
        return VOS_FALSE;
    }

    if(VSIM_VIRT_CARD_ACTIVE == stNvData.enVsimState)
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
#else
    return VOS_FALSE;
#endif
}

/*****************************************************************************
函 数 名  :USIMM_ChangeDefFileToPath
功能描述  :转换文件扩展名称到真实文件路径
输入参数  :enDefFileID 定义的文件扩展名称
输出参数  :ppcPathStr  文件路径
返 回 值  :
修订记录  :
1. 日    期   : 2015年02月12日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_ChangeDefFileToPath(USIMM_DEF_FILEID_ENUM_UINT32  enDefFileID,
                                     VOS_CHAR                    **ppcPathStr)
{
    if ((enDefFileID >= USIMM_DEF_FILEID_BUTT) || (VOS_NULL_PTR == ppcPathStr))
    {
        USIMM_ERROR_LOG("USIMM_ChangeDefFileToPath: The Para is Fail");

        return VOS_ERR;
    }

    *ppcPathStr = (VOS_CHAR *)g_stUSIMMFilePathTable[enDefFileID].pcFilePath;

    USIMM_NORMAL_LOG("USIMM_ChangeDefFileToPath: The File Path has Found");

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_ChangePathToDefFileID
功能描述  :根据文件路径查询文件的扩展名称
输入参数  :ulPathLen  文件路径长度
           pcPathStr  文件路径内容
输出参数  :penDefFileID 文件扩展名称
返 回 值  :
修订记录  :
1. 日    期   : 2015年2月12日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_ChangePathToDefFileID(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT32                          ulPathLen,
    VOS_CHAR                           *pcPathStr,
    USIMM_DEF_FILEID_ENUM_UINT32       *penDefFileID)
{
    VOS_UINT32                          i;
    VOS_CHAR                            acTemp[USIMM_PATHSTR_MAX_LEN] = {0};
    VOS_INT32                           lRslt;

    if ((VOS_NULL_PTR == pcPathStr)
        ||(VOS_NULL_PTR == penDefFileID)
        ||(VOS_NULL == ulPathLen)
        ||(ulPathLen > (USIMM_PATHSTR_MAX_LEN-1)))
    {
        USIMM_ERROR_LOG("USIMM_ChangePathToDefFileID: The Para is wrong");

        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemCpy(acTemp, pcPathStr, ulPathLen);
    /*lint +e534*/

    acTemp[ulPathLen] = '\0';

    for (i=0; i<ARRAYSIZE(g_stUSIMMFilePathTable); i++)
    {
        lRslt = VOS_StrCmp((VOS_CHAR *)g_stUSIMMFilePathTable[i].pcFilePath, acTemp);

        if ((VOS_OK == lRslt)
            && ((enAppType == g_stUSIMMFilePathTable[i].enAppType) || (USIMM_UNLIMIT_AUTO == g_stUSIMMFilePathTable[i].enAppType)))
        {
            *penDefFileID = i;

            USIMM_NORMAL_LOG("USIMM_ChangePathToDefFileID: The File Path has Found");

            return VOS_OK;
        }
    }

    USIMM_NORMAL_LOG("USIMM_ChangePathToDefFileID: The File Path is Unknow");

    return VOS_ERR;
}

/*****************************************************************************
函 数 名  :USIMM_QueryPINType
功能描述  :查询PIN操作类型确定　
输入参数  :
输出参数  :无
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1. 日    期   : 2009年1月20日
   作    者   : m00128685
   修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_QueryPINType(VOS_UINT8 *pucPINType)
{
    /*根据校验状态判断需查寻的PIN码类型*/
    if(USIMM_PUK_BLOCK == gstUSIMMADFInfo.enPin1Verified)
    {
        USIMM_NORMAL_LOG("USIMM_QueryPINType: The Card PUK is Block");

        *pucPINType = USIMM_PUK;
    }
    else if(USIMM_PUK_NEED == gstUSIMMADFInfo.enPin1Verified)/*先判断PUK状态*/
    {
        USIMM_NORMAL_LOG("USIMM_QueryPINType: The Card Need the PUK Password");

        *pucPINType = USIMM_PUK;
    }
    else if(USIMM_PIN_NEED == gstUSIMMADFInfo.enPin1Verified) /*再判断当前PIN1状态*/
    {
        USIMM_NORMAL_LOG("USIMM_QueryPINType: The Card Need the PIN Password");

        *pucPINType = USIMM_PIN;
    }
    else if(USIMM_PUK_NEED == gstUSIMMADFInfo.enPin2Verified)   /*再判断PUK2状态*/
    {
        USIMM_NORMAL_LOG("USIMM_QueryPINType: The Card Need the PUK2 Password");

        *pucPINType = USIMM_PUK2;
    }
    else  /*再判断PIN2状态*/                                                                                  /*最后默认需要PIN2*/
    {
        USIMM_NORMAL_LOG("USIMM_QueryPINType: The Card Need the PIN2 Password");

        *pucPINType = USIMM_PIN2;
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_PINHandleType
功能描述  :PIN操作类型确定　
输入参数  :
输出参数  :无
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1. 日    期   : 2009年1月19日
   作    者   : m00128685
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_HandlePINType(VOS_UINT8 ucCmdType, VOS_UINT32 *pulPINType)
{
    VOS_UINT32 ulResult = VOS_OK;

    switch(ucCmdType)
    {
        case USIMM_PINCMD_DISABLE:          /*激活，去激活和验证PIN用同一函数处理*/
            if(gstUSIMMADFInfo.stPINInfo.enPin1Enable == USIMM_PIN_ENABLED)
            {
                *pulPINType = USIMM_PIN;
            }
            else if(gstUSIMMADFInfo.stPINInfo.enPin2Enable == USIMM_PIN_ENABLED)
            {
                *pulPINType = USIMM_PIN2;
            }
            else
            {
                USIMM_ERROR_LOG("USIMM_HandlePINType: The PIN Enable State is Error");

                ulResult = VOS_ERR;
            }

            break;

        case USIMM_PINCMD_VERIFY:
            if(gstUSIMMADFInfo.enPin1Verified == USIMM_PIN_NEED)
            {
                *pulPINType = USIMM_PIN;
            }
            else if(gstUSIMMADFInfo.enPin2Verified == USIMM_PIN_NEED)
            {
                *pulPINType = USIMM_PIN2;
            }
            else
            {
                USIMM_ERROR_LOG("USIMM_HandlePINType: The PIN Verified State is Error");

                ulResult = VOS_ERR;
            }

            break;

        case USIMM_PINCMD_UNBLOCK:          /*解锁PIN处理*/
            if(gstUSIMMADFInfo.enPin1Verified == USIMM_PUK_NEED)
            {
                *pulPINType = USIMM_PIN;
            }
            else if(gstUSIMMADFInfo.enPin2Verified == USIMM_PUK_NEED)
            {
                *pulPINType = USIMM_PIN2;
            }
            else
            {
                USIMM_ERROR_LOG("USIMM_HandlePINType: The PIN Block State is Error");

                ulResult = VOS_ERR;
            }

            break;

        default:
            USIMM_ERROR_LOG("USIMM_HandlePINType: The PIN Cmd Type State is Error");
            break;
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_IsServiceAvailable
功能描述  :获取卡服务状态　
输入参数  :enService:服务ID
输出参数  :无
返 回 值  :PS_USIM_SERVICE_NOT_AVAILIABLE
           PS_USIM_SERVICE_NOT_AVAILIABLE
调用函数  :USIMM_PoolFindFile
           USIMM_GetBitFromBuf
被调函数  :
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_IsServiceAvailable(UICC_SERVICES_TYPE_ENUM_UINT32 enService)
{
    VOS_UINT32                          ulResult;

    /* 参数检查 */
    if (UICC_SVR_NONE == enService)
    {
        USIMM_WARNING_LOG("USIMM_IsServiceAvailable: The Parameter is Wrong");

        return PS_USIM_SERVICE_NOT_AVAILIABLE;
    }

    if (VOS_OK != VOS_TaskLock())
    {
        USIMM_WARNING_LOG("USIMM_IsServiceAvailable: SmP Error");

        return PS_USIM_SERVICE_NOT_AVAILIABLE;
    }

    if (enService < SIM_SVR_BUTT)
    {
        ulResult = USIMM_IsSIMServiceAvailable(enService);

        /*lint -e534*/
        VOS_TaskUnlock();
        /*lint +e534*/

        return ulResult;
    }

    if (enService < USIM_SVR_BUTT)
    {
        ulResult = USIMM_IsUSIMServiceAvailable(enService);

        /*lint -e534*/
        VOS_TaskUnlock();
        /*lint +e534*/

        return ulResult;
    }

    if (enService < ISIM_SVR_BUTT)
    {
        ulResult = USIMM_IsISIMServiceAvailable(enService);

        /*lint -e534*/
        VOS_TaskUnlock();
        /*lint +e534*/

        return ulResult;
    }

#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)

    if (enService < UIM_SVR_BUTT)
    {
        ulResult = USIMM_IsUIMServiceAvailable(enService);

        /*lint -e534*/
        VOS_TaskUnlock();
        /*lint +e534*/

        return ulResult;
    }

    if (enService < CSIM_SVR_BUTT)
    {
        ulResult = USIMM_IsCSIMServiceAvailable(enService);

        /*lint -e534*/
        VOS_TaskUnlock();
        /*lint +e534*/

        return ulResult;
    }
#endif

    /*lint -e534*/
    VOS_TaskUnlock();
    /*lint +e534*/

    USIMM_WARNING_LOG("USIMM_IsServiceAvailable: The Parameter is Wrong");

    return PS_USIM_SERVICE_NOT_AVAILIABLE;
}

/*****************************************************************************
函 数 名  :USIMM_IsTestCard
功能描述  :判断当前是否是测试卡，仅SIM/USIM卡中的PLMN号与NV项中的PLMN匹配时返回VOS_TRUE
           其它任何情况下都返回VOS_FALSE，如无卡，快速开机，IMSI未读取到，未初始化完成等
输入参数  :无
输出参数  : 无
返 回 值  :VOS_TRUE/VOS_FALSE
修订记录  :
1. 日    期   : 2013年1月4日
   作    者   : H59254
   修改内容   : Creat
*****************************************************************************/
VOS_BOOL USIMM_IsTestCard(VOS_VOID)
{
    VOS_UINT32                          ulFileNum;
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          i;
    USIMM_TEST_CARD_CFG_ST              stPlmnInfo;
    VOS_UINT8                           aucPLMN[USIMM_TEST_CARD_PLMN_LEN] = {0};

    ulRslt = NV_Read(en_NV_Item_Test_Card_Cfg, &stPlmnInfo, sizeof(USIMM_TEST_CARD_CFG_ST));

    if ((VOS_OK != ulRslt)
     || (USIMM_TEST_CARD_CFG_NUM < stPlmnInfo.ulPlmnNum))
    {
        USIMM_WARNING_LOG("USIMM_IsTestCard: Read NV is Failed");

        return VOS_FALSE;
    }

    if (VOS_OK != VOS_TaskLock())
    {
        USIMM_WARNING_LOG("USIMM_IsTestCard: SmP Error");

        return VOS_FALSE;
    }

    if ((gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService != USIMM_CARD_SERVIC_AVAILABLE)
     || (USIMM_OPENSPEEDENABLE == gulUSIMMOpenSpeed))/*卡状态检查*/
    {
        /*lint -e534*/
        VOS_TaskUnlock();
        /*lint +e534*/

        USIMM_WARNING_LOG("USIMM_IsTestCard: The Card Status is Wrong");

        return VOS_FALSE;
    }

    /* 查询当前的文件缓冲 */
    if (USIMM_API_SUCCESS != USIMM_PoolFindFile(0x6F07, &ulFileNum, USIMM_UNLIMIT_APP))
    {
        /*lint -e534*/
        VOS_TaskUnlock();
        /*lint +e534*/

        USIMM_WARNING_LOG("USIMM_IsTestCard: Read File is Failed");

        return VOS_FALSE;
    }

    /*lint -e534*/
    VOS_MemCpy(aucPLMN, gstUSIMMPOOL.astpoolRecord[ulFileNum].pucContent + 1, USIMM_TEST_CARD_PLMN_LEN);

    VOS_TaskUnlock();
    /*lint +e534*/
    aucPLMN[0] &= 0xF0;

    for (i = 0; i < stPlmnInfo.ulPlmnNum; i++)
    {
        if (VOS_OK == VOS_MemCmp(aucPLMN,
                                 stPlmnInfo.astPlmnList[i].aucPlmn,
                                 USIMM_TEST_CARD_PLMN_LEN))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
函 数 名  :USIMM_IsCdmaTestCard
功能描述  :判断当前是否是Cdma测试卡，仅UIM/CSIM卡中的HPLMN号与NV项中的PLMN匹配时返回VOS_TRUE
           其它任何情况下都返回VOS_FALSE，如无卡，快速开机，IMSI未读取到，未初始化完成等
输入参数  :无
输出参数  : 无
返 回 值  :VOS_TRUE/VOS_FALSE
修订记录  :
1. 日    期   : 2013年1月4日
   作    者   : H59254
   修改内容   : Creat
*****************************************************************************/
VOS_BOOL USIMM_IsCdmaTestCard(VOS_VOID)
{
    return VOS_FALSE;   /*Stub*/
}

/*****************************************************************************
函 数 名  :USIMM_GetPinStatus
功能描述  :获取PIN信息　
输入参数  :ucType:          PIN类型

输出参数  : pucBeEnable:  PIN是否开启
            pucBeNeed:PIN是否需要
            pucNum:PIN剩余次数
返 回 值  :USIMM_API_WRONG_PARA
           USIMM_API_SUCCESS
调用函数  :无
被调函数  :
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat
2.日    期  : 2011年5月26日
    作    者  : w00184875
    修改内容  : [DTS2011052606230],H3G需求，PUK码被锁时上报PUK码剩余次数
*****************************************************************************/
VOS_UINT32  USIMM_GetPinStatus(VOS_UINT8 *pucType,VOS_UINT8 *pucBeEnable,VOS_UINT8 *pucBeNeed,VOS_UINT8 *pucNum)
{
    USIMM_PIN_TYPE_ENUM_UINT32 enPINType;

    /*卡状态检查*/
    if (gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService == USIMM_CARD_SERVIC_ABSENT)
    {
        USIMM_WARNING_LOG("USIMM_GetPinStatus: The Card Status is Wrong");

        return USIMM_API_NOTAVAILABLE;
    }

    if (USIMM_OPENSPEEDENABLE == gulUSIMMOpenSpeed)
    {
        USIMM_WARNING_LOG("USIMM_GetPinStatus: Speed Open Mode");

        *pucBeNeed = USIMM_NONEED;

        return USIMM_API_SUCCESS;
    }

    if(gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService == USIMM_CARD_SERVIC_UNAVAILABLE)
    {
        if(USIMM_PUK_BLOCK == gstUSIMMADFInfo.enPin1Verified)
        {
            *pucType = USIMM_PUK;

            *pucNum  = (VOS_UINT8)(gstUSIMMADFInfo.stPINInfo.ucPuk1RemainTime);
            *pucBeNeed = USIMM_PUK_BLOCK;

            return USIMM_API_SUCCESS;
        }
        else
        {
            USIMM_WARNING_LOG("USIMM_GetPinStatus: The Card Status is Wrong");

            return USIMM_API_NOTAVAILABLE;
        }
    }

    if( USIMM_SIM_NON == *pucType )
    {
        USIMM_QueryPINType(pucType);
    }

    enPINType = *pucType;

    switch(enPINType)
    {
        /* 获取PIN1信息 */
        case USIMM_PIN:
            *pucBeEnable = (VOS_UINT8)(gstUSIMMADFInfo.stPINInfo.enPin1Enable);
            *pucBeNeed   = (VOS_UINT8)(gstUSIMMADFInfo.enPin1Verified);
            *pucNum      = (VOS_UINT8)(gstUSIMMADFInfo.stPINInfo.ucPin1RemainTime);
            break;

        /* 获取PIN2信息 */
        case USIMM_PIN2:
            *pucBeEnable = (VOS_UINT8)(gstUSIMMADFInfo.stPINInfo.enPin2Enable);
            *pucBeNeed   = USIMM_PIN_NEED;
            *pucNum      = (VOS_UINT8)(gstUSIMMADFInfo.stPINInfo.ucPin2RemainTime);
            break;

        /* 获取PUK1信息目前返回剩余次数 */
        case USIMM_PUK:
            *pucNum      = (VOS_UINT8)(gstUSIMMADFInfo.stPINInfo.ucPuk1RemainTime);
            break;

        /* 获取PUK2(信息目前返回剩余次数 */
        case USIMM_PUK2:
            *pucNum      = (VOS_UINT8)(gstUSIMMADFInfo.stPINInfo.ucPuk2RemainTime);
            break;

        default:
            USIMM_WARNING_LOG("USIMM_GetPinStatus: The PIN Type is Wrong");
            return USIMM_API_WRONG_PARA;
    }

    return USIMM_API_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_GetCardType
功能描述  :获取卡类型和卡服务状态　
输入参数  :enCardType:卡类型
输出参数  :pucCardType:卡状态
返 回 值  :USIMM_API_SUCCESS
调用函数  :无
被调函数  :
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_GetCardType(
    USIMM_CARD_TYPE_ENUM_UINT32         enCardType,
    USIMM_CARD_SERVIC_ENUM_UINT32      *pulCardStatus )
{
    if ((VOS_NULL_PTR == pulCardStatus) || (enCardType > USIMM_CARD_CSIM))
    {
        return USIMM_API_FAILED;
    }

    if ((USIMM_CARD_SIM == enCardType) || (USIMM_CARD_USIM == enCardType))
    {
        if (enCardType == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
        {
            *pulCardStatus = gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService;

            return USIMM_API_SUCCESS;
        }
    }
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
    else if ((USIMM_CARD_UIM == enCardType) || (USIMM_CARD_CSIM == enCardType))
    {
        if (enCardType == gastUSIMMCardAppInfo[USIMM_UICC_CDMA].enCardType)
        {
            *pulCardStatus = gastUSIMMCardAppInfo[USIMM_UICC_CDMA].enCardService;

            return USIMM_API_SUCCESS;
        }
    }
#endif
    else
    {
        *pulCardStatus = gastUSIMMCardAppInfo[USIMM_UICC_ISIM].enCardService;

        return USIMM_API_SUCCESS;
    }

    *pulCardStatus = USIMM_CARD_SERVIC_ABSENT;

    return USIMM_API_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_GetCardTypeByAppType
功能描述  :根据APP类型获取卡类型和卡服务状态　
输入参数  :enAppType:应用类型
输出参数  :pucCardStatus:卡服务状态
           pucCardType:卡状态
返 回 值  :VOS_OK/VOS_ERR
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : h00300778
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_GetCardTypeByAppType(
    VOS_UINT8                          *pucCardStatus,
    VOS_UINT8                          *pucCardType,
    USIMM_CARDAPP_ENUM_UINT32           enAppType)
{
    if (VOS_NULL_PTR != pucCardStatus)
    {
        if (USIMM_GUTL_APP == enAppType)
        {
            *pucCardStatus = (VOS_UINT8)gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService;
        }
        else if (USIMM_IMS_APP == enAppType)
        {
            *pucCardStatus = (VOS_UINT8)gastUSIMMCardAppInfo[USIMM_UICC_ISIM].enCardService;
        }
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
        else if (USIMM_CDMA_APP == enAppType)
        {
            *pucCardStatus = (VOS_UINT8)gastUSIMMCardAppInfo[USIMM_UICC_CDMA].enCardService;
        }
#endif
        else
        {
            return VOS_ERR;
        }
    }

    if(VOS_NULL_PTR != pucCardType)
    {
        if (USIMM_GUTL_APP == enAppType)
        {
            *pucCardType = (VOS_UINT8)gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType;
        }
        else if (USIMM_IMS_APP == enAppType)
        {
            *pucCardType = (VOS_UINT8)gastUSIMMCardAppInfo[USIMM_UICC_ISIM].enCardType;
        }
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
        else if (USIMM_CDMA_APP == enAppType)
        {
            *pucCardType = (VOS_UINT8)gastUSIMMCardAppInfo[USIMM_UICC_CDMA].enCardType;
        }
#endif
        else
        {
            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_GetCachedFile
功能描述  :获取缓冲的文件内容接口
输入参数  :无
输出参数  :usFileID   输入参数，读取的文件ID
           pulDataLen 输出参数  返回文件的内容长度
           ppucData   输出参数  返回文件内容的地址
返 回 值  :USIMM_API_SUCCESS
           USIMM_API_FAILED
           USIMM_API_WRONG_PARA
调用函数  :无
被调函数  :
修订记录  :
1. 日    期   : 2011年9月19日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_GetCachedFile(
    VOS_CHAR                           *pusFileStr,
    VOS_UINT32                         *pulDataLen,
    VOS_UINT8                         **ppucData,
    USIMM_CARDAPP_ENUM_UINT32           enAppType)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulRecordNum;
    VOS_UINT16                          usDFID;
    VOS_UINT16                          usSDFID;
    VOS_UINT16                          usEFID;
    USIMM_FILEPATH_INFO_STRU            stFilePath;

    if(USIMM_OPENSPEEDENABLE == gulUSIMMOpenSpeed)
    {
        USIMM_WARNING_LOG("USIMM_GetCachedFile: The Open Speed Mode is Not Support it");

        return USIMM_API_FAILED;
    }

    if(gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService != USIMM_CARD_SERVIC_AVAILABLE)/*卡状态检查*/
    {
        USIMM_WARNING_LOG("USIMM_GetCachedFile: The Card Status is Wrong");

        return USIMM_API_FAILED;
    }

    if (USIMM_GUTL_APP != enAppType)
    {
        USIMM_WARNING_LOG("USIMM_GetCachedFile: The enAppType is Wrong");

        return USIMM_API_FAILED;
    }

    if((USIMM_POOL_NOINTIAL == gstUSIMMPOOL.enPoolStatus)
        ||(0                == gstUSIMMPOOL.ucNowLen)
        ||(VOS_NULL_PTR     == pusFileStr))   /*状态检查*/
    {
        USIMM_WARNING_LOG("USIMM_GetCachedFile: Parameter wrong");/*打印错误*/

        return USIMM_API_WRONG_PARA;
    }

    stFilePath.ulPathLen = VOS_StrLen(pusFileStr);

    /*lint -e534*/
    VOS_MemCpy(stFilePath.acPath, pusFileStr, stFilePath.ulPathLen);
    /*lint +e534*/

    if (VOS_OK != USIMM_GetFilePathFormStr(&stFilePath, &usDFID, &usSDFID, &usEFID))
    {
        USIMM_WARNING_LOG("USIMM_GetCachedFile: USIMM_GetFilePathFormStr wrong");/*打印错误*/

        return USIMM_API_WRONG_PARA;
    }

    /* 查询文件位置 */
    ulResult    =   USIMM_PoolFindFile(usEFID, &ulRecordNum, USIMM_UNLIMIT_APP);

    if(VOS_ERR == ulResult)
    {
        USIMM_ERROR_LOG("USIMM_GetCachedFile: File Could not Found");/*打印错误*/

        return USIMM_API_WRONG_PARA;
    }

    if(VOS_NULL_PTR == gstUSIMMPOOL.astpoolRecord[ulRecordNum].pucContent)
    {
        USIMM_ERROR_LOG("USIMM_PoolReadOneFile: File Content is Empty");/*打印错误*/

        return USIMM_API_WRONG_PARA;
    }

    *pulDataLen = gstUSIMMPOOL.astpoolRecord[ulRecordNum].usLen;

    *ppucData = gstUSIMMPOOL.astpoolRecord[ulRecordNum].pucContent;

    return USIMM_API_SUCCESS;
}


/*old API 2阶段删除或者修改替换*/

/*****************************************************************************
函 数 名      :USIMM_GetCardIMSI
功能描述  :获取IMSI接口
输入参数  :无
输出参数  :pucImsi 存储文件内容
返 回 值      :USIMM_API_SUCCESS

调用函数  :无
被调函数  :
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_GetCardIMSI(VOS_UINT8 *pucImsi)
{
    VOS_UINT32  ulResult;

    if(VOS_NULL_PTR == pucImsi)
    {
        USIMM_WARNING_LOG("USIMM_GetCardIMSI: The Parameter is Error");

        return USIMM_API_WRONG_PARA;
    }

    if(USIMM_OPENSPEEDENABLE == gulUSIMMOpenSpeed)
    {
        ulResult = NV_Read(en_NV_Item_EF6F07, (VOS_VOID *)pucImsi, USIMM_EF_IMSI_LEN);

        return ((ulResult == VOS_OK)?USIMM_API_SUCCESS:USIMM_API_FAILED);/* [false alarm]: 屏蔽Fortify 错误 */
    }

    if(gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService != USIMM_CARD_SERVIC_AVAILABLE)/*卡状态检查*/
    {
        USIMM_WARNING_LOG("USIMM_GetCardIMSI: The Card Status is Wrong");

        return USIMM_API_FAILED;
    }

    if (VOS_OK != VOS_TaskLock())
    {
        USIMM_WARNING_LOG("USIMM_GetCardIMSI: SmP Error");

        return USIMM_API_FAILED;
    }

    if(VOS_OK == USIMM_PoolReadOneFile(EFIMSI, USIMM_EF_IMSI_LEN, pucImsi, USIMM_UNLIMIT_APP))
    {
        /*lint -e534*/
        VOS_TaskUnlock();
        /*lint +e534*/

        return USIMM_API_SUCCESS;
    }

    /*lint -e534*/
    VOS_TaskUnlock();
    /*lint +e534*/

    USIMM_WARNING_LOG("USIMM_GetCardIMSI: USIMM_PoolReadOneFile Error");

    return USIMM_API_NOTAVAILABLE;
}

/*****************************************************************************
函 数 名  :USIMM_GetCdmaIMSIM
功能描述  :获取IMSIM接口
输入参数  :无
输出参数  :pucImsiM 存储文件内容
返 回 值  :USIMM_API_SUCCESS

调用函数  :无
被调函数  :
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_GetCdmaIMSIM(VOS_UINT8 *pucImsiM)
{
    USIMM_WARNING_LOG("USIMM_GetCdmaIMSIM: The Parameter is Error");

    return USIMM_API_WRONG_PARA;
}

/*****************************************************************************
函 数 名  : USIMM_GetPinRemainTime
功能描述  : 获取pin码操作剩余次数
输入参数  :
输出参数  : 无
返 回 值  : VOS_UINT32，表示函数执行结果
调用函数  :
被调函数  : 外部接口
*****************************************************************************/
VOS_UINT32 USIMM_GetPinRemainTime(USIMM_PIN_REMAIN_STRU *pstRemainTime)
{
    pstRemainTime->ucPin1RemainTime = gstUSIMMADFInfo.stPINInfo.ucPin1RemainTime;
    pstRemainTime->ucPin2RemainTime = gstUSIMMADFInfo.stPINInfo.ucPin2RemainTime;
    pstRemainTime->ucPuk1RemainTime = gstUSIMMADFInfo.stPINInfo.ucPuk1RemainTime;
    pstRemainTime->ucPuk2RemainTime = gstUSIMMADFInfo.stPINInfo.ucPuk2RemainTime;

    return USIMM_API_SUCCESS;
}

/*****************************************************************************
函 数 名  : USIMM_BdnQuery
功能描述  : BDN状态查询接口
输入参数  : 无
输出参数  : 无
返 回 值  : SI_UINT32 函数执行结果
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2008年10月20日
  作    者  : H59254
  修改内容  : Create
*****************************************************************************/
VOS_VOID USIMM_BdnQuery(VOS_UINT32 *pulState)
{
    if(VOS_NULL_PTR != pulState)
    {
        *pulState = gstUSIMMBaseInfo.enBDNStatus;
    }

    return ;
}

/*****************************************************************************
函 数 名  : USIMM_FdnQuery
功能描述  : FDN状态查询接口
输入参数  : 无
输出参数  : 无
返 回 值  : SI_UINT32 函数执行结果
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2008年10月20日
  作    者  : H59254
  修改内容  : Create
*****************************************************************************/

VOS_VOID USIMM_FdnQuery(VOS_UINT32 *pulUsimFdnState, VOS_UINT32 *pulCsimFdnState)
{
    if(VOS_NULL_PTR != pulUsimFdnState)
    {
        *pulUsimFdnState = gstUSIMMBaseInfo.enFDNStatus;
    }

    /*中国电信不要支持FDN功能，默认关闭*/
    if(VOS_NULL_PTR != pulCsimFdnState)
    {
        *pulCsimFdnState = USIMM_FDNSTATUS_OFF;
    }

    return ;
}

/*****************************************************************************
函 数 名  :USIMM_ActiveCardReq
功能描述  :SIM卡激活请求
输入参数  :ulSenderPid:发送请求的PID
输出参数  :无
返 回 值  :VOS_OK
           VOS_ERR
被调函数  :
修订记录  :
1. 日    期   : 2010年 7 月 26日
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_ActiveCardReq(VOS_UINT32 ulSenderPid)
{
    if(USIMM_OPENSPEEDENABLE == gulUSIMMOpenSpeed)/*卡状态检查*/
    {
        USIMM_WARNING_LOG("USIMM_ActiveCardReq: The Card Status is Wrong");

        return VOS_ERR;
    }

    if (VOS_ERR == USIMM_SendInitCardMsg(ulSenderPid, USIMM_ACTIVECARD_REQ))
    {
        USIMM_WARNING_LOG("USIMM_ActiveCardReq: VOS_SendMsg is Failed");/*打印错误*/

        return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
函 数 名  :USIMM_SCICardOutNotify
功能描述  :SIM卡热插拔注册给底软的回调函数,底软保证在中断中调用此函数，因此不需要增加信号量保护
输入参数  :卡的状态
输出参数  :无
返 回 值  :

修订记录  :
1. 日    期   : 2012年3月14日
   作    者   : w00184875
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_SCICardOutNotify(VOS_UINT32 ulCardInOutStatus)
{
    USIMM_CARD_INOUT_IND_STRU           *pUsimMsg;

    /*lint -e534*/
    LogPrint1("USIMM_SCICardOutNotify: The card status is %d .\r\n", (VOS_INT)ulCardInOutStatus);
    /*lint +e534*/

    if(VOS_TRUE == USIMM_VsimIsActive())    /*vSIM功能打开*/
    {
        USIMM_WARNING_LOG("USIMM_SCICardOutNotify: The vSIM is Open");

        return;
    }

    pUsimMsg = (USIMM_CARD_INOUT_IND_STRU*)VOS_AllocMsg(WUEPS_PID_USIM,
                                                sizeof(USIMM_CARD_INOUT_IND_STRU)-VOS_MSG_HEAD_LENGTH);

    if(VOS_NULL_PTR == pUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_CardInOutHandle: VOS_AllocMsg is Failed");

        return;
    }

    pUsimMsg->enMsgType         = USIMM_CARD_INOUT_IND;
    pUsimMsg->ulReceiverPid     = WUEPS_PID_USIM;
    pUsimMsg->ulSenderPid       = WUEPS_PID_USIM;
    pUsimMsg->ulCardInOutStatus = (VOS_UINT32)ulCardInOutStatus;

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pUsimMsg);

    return;
}

/*****************************************************************************
函 数 名  :USIMM_SciCardStatusIndCbFunc
功能描述  :CE产品上SIM卡热插拔注册给底软的回调函数,底软保证在中断中调用此函数，因此不需要增加信号量保护
输入参数  :卡的状态
输出参数  :无
返 回 值  :无
修订记录  :
1. 日    期   : 2013年9月23日
   作    者   : H59254
   修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_SciCardStatusIndCbFunc(USIMM_CARDSTATUS_IND_ENUM_UINT32 enCardStatus)
{
    USIMM_CARD_STATUS_IND_STRU         *pstMsg;

    if (VOS_TRUE == USIMM_VsimIsActive())    /*vSIM功能打开*/
    {
        return;
    }

    pstMsg = (USIMM_CARD_STATUS_IND_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                                                       sizeof(USIMM_CARD_STATUS_IND_STRU)-VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        USIMM_ERROR_LOG("USIMM_SciCardStatusIndCbFunc: VOS_AllocMsg is Failed");

        return;
    }

    pstMsg->enMsgType         = USIMM_CARDSTATUS_CB_IND;
    pstMsg->ulReceiverPid     = WUEPS_PID_USIM;
    pstMsg->ulSenderPid       = MAPS_PIH_PID;
    pstMsg->ulCardStatus      = enCardStatus;

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstMsg);

    return;
}

/*****************************************************************************
函 数 名  :USIMM_SessionIdToChanNum
功能描述  :根据会话ID查询通道号
输入参数  :ulSessionId:会话ID
输出参数  :pulChanNum:通道号
返 回 值  :无

修订记录  :
1.日    期  : 2013年12月20日
  作    者  : j00168360
  修改内容  : Create
*****************************************************************************/
VOS_VOID USIMM_SessionIdToChanNum(VOS_UINT32 ulSessionId, VOS_UINT32 *pulChanNum)
{
    VOS_UINT8                           ucIndex;

    for (ucIndex = 0; ucIndex < USIMM_CHANNEL_NUM_MAX; ucIndex++)
    {
        if (ulSessionId == g_astUSIMMChCtrl[ucIndex].ulSessionId)
        {
            *pulChanNum = g_astUSIMMChCtrl[ucIndex].ulChanNum;

            return;
        }
    }

    *pulChanNum = USIMM_CHANNEL_INVALID_NUM;

    return;
}

/*****************************************************************************
函 数 名  :USIMM_ChanNumToSessionId
功能描述  :根据通道号查询会话ID
输入参数  :ulChanNum:通道号
输出参数  :pulSessionId:会话ID
返 回 值  :无

修订记录  :
1.日    期  : 2013年12月20日
  作    者  : j00168360
  修改内容  : Create
*****************************************************************************/
VOS_VOID USIMM_ChanNumToSessionId(VOS_UINT32 ulChanNum, VOS_UINT32 *pulSessionId)
{
    VOS_UINT8                           ucIndex;

    for (ucIndex = 0; ucIndex < USIMM_CHANNEL_NUM_MAX; ucIndex++)
    {
        if (ulChanNum == g_astUSIMMChCtrl[ucIndex].ulChanNum)
        {
            *pulSessionId = g_astUSIMMChCtrl[ucIndex].ulSessionId;

            return;
        }
    }

    *pulSessionId = USIMM_SESSION_ID_MAX;

    return;
}

/*****************************************************************************
函 数 名  :USIMM_GetUiccChanNumByAid
功能描述  :根据AID查询通道号
输入参数  :pucAid:指向应用ID
           ulAIDLen:AID长度
输出参数  :pulChanNum:通道号
返 回 值  :无

修订记录  :
1.日    期  : 2013年12月20日
  作    者  : j00168360
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 USIMM_GetUiccChanNumByAid(VOS_UINT8 *pucAid, VOS_UINT32 ulAIDLen, VOS_UINT8 *pucChanNum)
{
    VOS_UINT8                           ucIndex;

    for (ucIndex = 0; ucIndex < USIMM_CHANNEL_NUM_MAX; ucIndex++)
    {
        if (VOS_OK == VOS_MemCmp(pucAid, g_astUSIMMChCtrl[ucIndex].aucADFName, ulAIDLen))
        {
            *pucChanNum = (VOS_UINT8)g_astUSIMMChCtrl[ucIndex].ulChanNum;

            return VOS_OK;
        }
    }

    *pucChanNum = 0xff;

    return VOS_ERR;
}

/*****************************************************************************
函 数 名  :USIMM_GetAid
功能描述  :获取AID请求
输入参数  :ulAidType:AID类型
输出参数  :pulLen:返回的数据长度
           pucAid:AID的内容
返 回 值  :USIMM_API_SUCCESS:成功，其余失败

修订记录  :
1.日    期  : 2013年12月19日
  作    者  : h59254
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 USIMM_GetAid(VOS_UINT32 ulAidType, VOS_UINT32 *pulLen, VOS_UINT8 *pucAid)
{
    if ((VOS_NULL_PTR == pulLen) || (VOS_NULL_PTR == pucAid))
    {
        return USIMM_API_WRONG_PARA;
    }

    if (ulAidType >= USIMM_AID_TYPE_BUTT)
    {
        return USIMM_API_WRONG_PARA;
    }

    if ((VOS_NULL == g_astAidInfo[ulAidType].ulAIDLen)
        || (g_astAidInfo[ulAidType].ulAIDLen > USIMM_AID_LEN_MAX))
    {
        return USIMM_API_NOTAVAILABLE;
    }

    /*lint -e534*/
    VOS_MemCpy(pucAid, g_astAidInfo[ulAidType].aucAID, g_astAidInfo[ulAidType].ulAIDLen);
    /*lint +e534*/

    *pulLen = g_astAidInfo[ulAidType].ulAIDLen;

    return USIMM_API_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_GetCardCGType
功能描述  :获取C or G 请求
输入参数  :
输出参数  :
返 回 值  :USIMM_API_SUCCESS:成功，其余失败

修订记录  :
1.日    期  : 2014年06月04日
  作    者  : w00180399
  修改内容  : Create
*****************************************************************************/

VOS_UINT32 USIMM_GetCardCGType(VOS_UINT8 *pucCardMode, VOS_UINT8 *pucHasCModule, VOS_UINT8 *pucHasWGModule)
{
    if ((VOS_NULL_PTR == pucCardMode) || (VOS_NULL_PTR == pucHasCModule) || (VOS_NULL_PTR == pucHasWGModule))
    {
        return USIMM_API_WRONG_PARA;
    }

    *pucCardMode    = g_stUSIMMCardVersionType.enCardMode;
    *pucHasCModule  = g_stUSIMMCardVersionType.ucHasCModule;
    *pucHasWGModule = g_stUSIMMCardVersionType.ucHasWGModule;

    return USIMM_API_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_GetPbDfPath
功能描述  :获取USIM卡PHONEBOOK路径
输入参数  :无
输出参数  :无
返 回 值  :无

修订记录  :
1.日    期  : 2014年06月04日
  作    者  : h00300778
  修改内容  : Create
*****************************************************************************/
VOS_UINT16 USIMM_GetPbDfPath(VOS_VOID)
{
    return gstUSIMMBaseInfo.stPBInfo.usPBDfID;
}

#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
/*****************************************************************************
函 数 名  :USIMM_CdmaParaCheckSimple
功能描述  :下发请求的检查，不包括vSIM的状态检查，实现原参数检查功能
输入参数  :无
输出参数  :pulSendPid:调用PID
返 回 值  :USIMM_API_SUCCESS
           USIMM_API_NOTAVAILABLE
           USIMM_API_SENDMSG_FAILED
被调函数  :
修订记录  :
1. 日    期   : 2014年07月10日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_CdmaParaCheckSimple(VOS_VOID)
{
    if((gastUSIMMCardAppInfo[USIMM_UICC_CDMA].enCardService == USIMM_CARD_SERVIC_ABSENT)
        ||(USIMM_OPENSPEEDENABLE == gulUSIMMOpenSpeed))/*卡状态检查*/
    {
        USIMM_WARNING_LOG("USIMM_CdmaParaCheckSimple: The Card Status is Wrong");

        return USIMM_API_NOTAVAILABLE;
    }

    return USIMM_API_SUCCESS;
}

#endif

#if (FEATURE_VSIM == FEATURE_ON)
/*****************************************************************************
函 数 名  :USIMM_SaveHvteeVsimData
功能描述  :保存共享内存中的VSIM数据
输入参数  : ulDataLen: 数据长度
            pucVsimData:数据内容
输出参数  : 无
返 回 值  : 无

修订记录  :
1.日    期  : 2014年10月09日
  作    者  : 祝锂
  修改内容  : Create
*****************************************************************************/

VOS_VOID USIMM_SaveHvteeVsimData(
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                           *pucVsimData
)
{
    if ((VOS_NULL_PTR == pucVsimData) || (VOS_NULL == ulDataLen))
    {
        USIMM_WARNING_LOG("USIMM_SaveHvteeVsimData: The para is Wrong");
        return;
    }

    if (g_pucUSIMMVsimData != VOS_NULL_PTR)
    {
        (VOS_VOID)VOS_MemFree(WUEPS_PID_USIM, g_pucUSIMMVsimData);
    }

    g_pucUSIMMVsimData = VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, ulDataLen+1);  /*多申请一个字节用于存储'\0'*/

    if (VOS_NULL_PTR == g_pucUSIMMVsimData) /*申请失败会复位*/
    {
        USIMM_WARNING_LOG("USIMM_SaveHvteeVsimData: The VOS_MemAlloc is Wrong");
        return;
    }

    (VOS_VOID)VOS_MemCpy(g_pucUSIMMVsimData, pucVsimData, ulDataLen);

    g_pucUSIMMVsimData[ulDataLen] = '\0';

    return;
}
#endif /*(FEATURE_VSIM == FEATURE_ON)*/

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif/*(FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)*/

