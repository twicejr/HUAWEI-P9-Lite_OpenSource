/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SSA_Encode.c
  Author       : ---
  Version      : V200R001
  Date         : 2008-08-16
  Description  : 该C文件给出了SSA模块编码函数的实现
  Function List:
        ---
        ---
        ---
  History      :
  1. Date:2005-08-16
     Author: ---
     Modification:Create
  2. Date:2005-08-16
     Author: ---
     Modification:Add function ... 问题单号:

  3.日    期   : 2006年4月4日
    作    者   : liuyang id:48197
    修改内容   : 问题单号:A32D01738
  4.Date:2007-01-19
    Author: h44270
    Modification: 问题单号:A32D08448
  5.Date:2007-04-29
    Author: Li Jilin 60827
    Modification: 问题单号:A32D10708
  6. 日    期   : 2010年05月07日
     作    者   : s62952
     修改内容   : 问题单号:A2D18963

************************************************************************/

/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "Ps.h"

#include "Taf_Common.h"
#include "Taf_Ssa_EncodeDef.h"
#include "TafStdlib.h"
#include "TafMmiEncode.h"
/* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
#include "mnmsgcbencdec.h"
#include "MnErrorCode.h"
/* Added by f62575 for V9R1 STK升级, 2013-6-26, end */

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_SSA_ENCODE_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/



/*lint -save -e958 */

/*****************************************************************************
 Prototype      : SSA_EncodeRegisterSSReq
 Description    : 对MS发起的RegisterSS操作的facility内容进行编码
 Input          : *pSrc--编码前的数据结构
 Output         : *pucContent--编码后的字串   *pucCodeLen--字串的长度
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_EncodeRegisterSSReq(VOS_UINT8   *pucContent, VOS_UINT8  *pucCodeLen, TAF_SS_REGISTERSS_REQ_STRU *pSrc)
{
    VOS_UINT8           ucTmpLen = 0;              /*记录每个参数项的编码长度,初始值为0*/
    VOS_UINT8           ucOffset = 0;
    VOS_UINT32          ulRslt;

    gpucSsEncodeEndLocation = pucContent + MAX_FACILITY_LEN;

    /*对参数项ss-Code进行编码, 编码失败则返回*/
    ulRslt = SSA_EncodeSsCode(pucContent + ucOffset, &ucTmpLen, &(pSrc->SsCode), EXPLICIT_MODE);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeRegisterSSReq:WARNING:SSA_EncodeSsCode encode failure");
        return ulRslt;
    }
    /*计算偏移值*/
    ucOffset = ucOffset + ucTmpLen;

    /*如果有参数项basicService，则进行相应参数项的编码, 编码失败则返回*/
    if (pSrc->OP_BsService)
    {
        ulRslt = SSA_EncodeBasicService(pucContent + ucOffset, &ucTmpLen, &(pSrc->BsService), EXPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeRegisterSSReq:WARNING:SSA_EncodeBasicService encode failure");
            return ulRslt;
        }
        /*计算偏移值*/
        ucOffset = ucOffset + ucTmpLen;
    }

    /*如果有参数项forwardedToNumber，許SA_EncodeForwardedToNumber蚪邢嘤Σ问畹谋嗦? 编码失败则返回*/
    if (pSrc->OP_FwdToNum)
    {
        ulRslt = SSA_EncodeForwardedToNumber(pucContent + ucOffset, &ucTmpLen, pSrc->NumType, pSrc->aucFwdToNum, IMPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeRegisterSSReq:WARNING:SSA_EncodeForwardedToNumber encode failure");
            return ulRslt;
        }
        /*IMPLICIT模式下，对头部进行封装*/
        ulRslt = SSA_PackTL(0x84, pucContent + ucOffset , &ucTmpLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeRegisterSSReq:WARNING:FwdToNum: Tag Length encode failure");
            return ulRslt;
        }
        /*计算偏移值*/
        ucOffset = ucOffset + ucTmpLen;
    }

    /*如果有参数项forwardedToSubaddress，则进行相应参数项的编码, 编码失败则返回*/
    if (pSrc->OP_FwdToAddr)
    {
        ulRslt = SSA_EncodeForwardedToSubaddress(pucContent + ucOffset, &ucTmpLen, pSrc->SubAddrType, pSrc->aucFwdToSubAddr, IMPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeRegisterSSReq:WARNING:SSA_EncodeForwardedToSubaddress encode failure");
            return ulRslt;
        }
        /*IMPLICIT模式下，对头部进行封装*/
        ulRslt = SSA_PackTL(0x86, pucContent + ucOffset , &ucTmpLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeRegisterSSReq:WARNING:FwdToAddr: Tag Length encode encode failure");
            return ulRslt;
        }
        /*计算偏移值*/
        ucOffset = ucOffset + ucTmpLen;
    }

    /*如果有参数项noReplyConditionTime，则进行相应参数项的编码, 编码失败则返回*/
    if (pSrc->OP_NoRepCondTime)
    {
        ulRslt = SSA_EncodeNoRepCondTime(pucContent + ucOffset, &ucTmpLen, (VOS_INT)pSrc->NoRepCondTime, IMPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeRegisterSSReq:WARNING:SSA_EncodeNoRepCondTime encode failure");
            return ulRslt;
        }
        /*IMPLICIT模式下，对头部进行封装*/
        ulRslt = SSA_PackTL(0x85, pucContent + ucOffset , &ucTmpLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeRegisterSSReq:WARNING:NoRepCondTime: Tag Length encode encode failure");
            return ulRslt;
        }
        /*计算偏移值*/
        ucOffset = ucOffset + ucTmpLen;
    }


    /*如果有参数项defaultPriority，则进行相应参数项的编码, 编码失败则返回*/
    if (pSrc->OP_DefaultPrio)
    {
        ulRslt = SSA_EncodeDefaultPriority(pucContent + ucOffset, &ucTmpLen, (VOS_INT)pSrc->DefaultPrio, IMPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeRegisterSSReq:WARNING:WARNING:SSA_EncodeDefaultPriority encode failure");
            return ulRslt;
        }
        /*IMPLICIT模式下，对头部进行封装*/
        ulRslt = SSA_PackTL(0x87, pucContent + ucOffset , &ucTmpLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeRegisterSSReq:WARNING:DefaultPrio: Tag Length encode encode failure");
            return ulRslt;
        }
        /*计算偏移值*/
        ucOffset = ucOffset + ucTmpLen;
    }

    /*如果有参数项nbrUser，则进行相应参数项的编码, 编码失败则返回*/
    if (pSrc->OP_NbrUser)
    {
        ulRslt = SSA_EncodeNbrUser(pucContent + ucOffset, &ucTmpLen, (VOS_INT)pSrc->NbrUser, IMPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeRegisterSSReq:WARNING:SSA_EncodeNbrUser encode failure");
            return ulRslt;
        }
        /*IMPLICIT模式下，对头部进行封装*/
        ulRslt = SSA_PackTL(0x88, pucContent + ucOffset , &ucTmpLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeRegisterSSReq:WARNING:NbrUser: Tag Length encode encode failure");
            return ulRslt;
        }
        /*计算偏移值*/
        ucOffset = ucOffset + ucTmpLen;
    }

    /*如果有参数项longFTN-Supported，则进行相应参数项的编码, 编码失败则返回*/
    if (pSrc->OP_LongFTN_Supported)
    {
        /*使用EXPLICIT模式，对头部进行封装，NULL类型没有任何内容,只有T、L,没有V*/
        ulRslt = SSA_EncodeNullType(0x89, pucContent + ucOffset , &ucTmpLen, EXPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeRegisterSSReq:WARNING:SSA_EncodeNullType encode failure");
            return ulRslt;
        }
        /*计算偏移值*/
        ucOffset = ucOffset + ucTmpLen;
    }


    /*计算编码后字串长度*/
    *pucCodeLen = ucOffset;
    /*整个参数的结构体头部封装*/
    ulRslt = SSA_PackTL(0x30 , pucContent, pucCodeLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeRegisterSSReq:WARNING:RegisterSSReq: Tag Length encode encode failure");
        return ulRslt;
    }

    return SSA_SUCCESS;

}

/*****************************************************************************
 Prototype      : SSA_EncodeEraseSSReq
 Description    : 对MS发起的EraseSS操作的facility内容进行编码
 Input          : *pSrc--编码前的数据结构
 Output         : *pucContent--编码后的字串   *pucCodeLen--字串的长度
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_EncodeEraseSSReq(VOS_UINT8   *pucContent, VOS_UINT8  *pucCodeLen, TAF_SS_ERASESS_REQ_STRU *pSrc)
{
    VOS_UINT8           ucTmpLen = 0;              /*记录每个参数项的编码长度,初始值为0*/
    VOS_UINT8           ucOffset = 0;
    VOS_UINT32          ulRslt;

    gpucSsEncodeEndLocation = pucContent + MAX_FACILITY_LEN;

    /*对参数项ss-Code进行编码*/
    ulRslt = SSA_EncodeSsCode(pucContent + ucOffset, &ucTmpLen, &(pSrc->SsCode), EXPLICIT_MODE);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeEraseSSReq:WARNING:SSA_EncodeSsCode encode failure");
        return ulRslt;
    }
    /*计算偏移值*/
    ucOffset = ucOffset + ucTmpLen;

    /*如果有参数项basicService，则进行相应参数项的编码*/
    if (pSrc->OP_BsService)
    {
        ulRslt = SSA_EncodeBasicService(pucContent + ucOffset, &ucTmpLen, &(pSrc->BsService), EXPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeEraseSSReq:WARNING:SSA_EncodeBasicService encode failure");
            return ulRslt;
        }
        /*计算偏移值*/
        ucOffset = ucOffset + ucTmpLen;
    }

    /*如果有参数项longFTN-Supported，则进行相应参数项的编码*/
    if (pSrc->OP_LongFTN_Supported)
    {
        /*使用EXPLICIT模式，对头部进行封装，NULL类型没有任何内容*/
        ulRslt = SSA_EncodeNullType(0x84, pucContent + ucOffset , &ucTmpLen, EXPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeEraseSSReq:WARNING:SSA_EncodeNullType encode failure");
            return ulRslt;
        }
        /*计算偏移值*/
        ucOffset = ucOffset + ucTmpLen;
    }

    /*计算编码后字串长度*/
    *pucCodeLen = ucOffset;
    /*整个参数的结构体头部封装*/
    ulRslt = SSA_PackTL(0x30 , pucContent, pucCodeLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeEraseSSReq:WARNING:EraseSSReq: Tag Length encode encode failure");
        return ulRslt;
    }

    return SSA_SUCCESS;

}

/*****************************************************************************
 Prototype      : SSA_EncodeActivateSSReq
 Description    : 对MS发起的ActivateSS操作的facility内容进行编码
 Input          : *pSrc--编码前的数据结构
 Output         : *pucContent--编码后的字串   *pucCodeLen--字串的长度
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_EncodeActivateSSReq(VOS_UINT8   *pucContent, VOS_UINT8  *pucCodeLen, TAF_SS_ACTIVATESS_REQ_STRU *pSrc)
{
    VOS_UINT32          ulRslt;

    /*ActivateSS操作的参数和EraseSS操作相同*/
    ulRslt = SSA_EncodeEraseSSReq(pucContent, pucCodeLen, pSrc);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeActivateSSReq:WARNING:encode ActivateSS failure");
    }

    return ulRslt;

}

/*****************************************************************************
 Prototype      : SSA_EncodeDeativateSSReq
 Description    : 对MS发起的DeactivateSS操作的facility内容进行编码
 Input          : *pSrc--编码前的数据结构
 Output         : *pucContent--编码后的字串   *pucCodeLen--字串的长度
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_EncodeDeactivateSSReq(VOS_UINT8   *pucContent, VOS_UINT8  *pucCodeLen, TAF_SS_DEACTIVATESS_REQ_STRU *pSrc)
{
    VOS_UINT32          ulRslt;

    /*DeactivateSS操作的参数和EraseSS操作相同*/
    ulRslt = SSA_EncodeEraseSSReq(pucContent, pucCodeLen, pSrc);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeDeactivateSSReq:WARNING:encode DeactivateSS failure");
    }

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_EncodeInterrogateSsReq
 Description    : 对MS发起的InterrogateSS操作的facility内容进行编码
 Input          : *pSrc--编码前的数据结构
 Output         : *pucContent--编码后的字串   *pucCodeLen--字串的长度
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_EncodeInterrogateSsReq(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, TAF_SS_INTERROGATESS_REQ_STRU *pSrc)
{
    VOS_UINT32          ulRslt;

    /*InterrogateSS操作的参数和EraseSS操作相同*/
    ulRslt = SSA_EncodeEraseSSReq(pucContent, pucCodeLen, pSrc);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeInterrogateSsReq:WARNING:encode InterrogateSS failure");
    }

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_EncodeRegPwdReq
 Description    : 对MS发起的RegisterPassword操作的facility内容进行编码
 Input          : *pSrc--编码前的数据结构
 Output         : *pucContent--编码后的字串   *pucCodeLen--字串的长度
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_EncodeRegPwdReq(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, TAF_SS_REGPWD_REQ_STRU *pSrc)
{
    VOS_UINT8           ucTmpLen = 0;          /*记录每个参数项的编码长度,初始值为0*/
    VOS_UINT8           ucOffset = 0;
    VOS_UINT32          ulRslt;

    gpucSsEncodeEndLocation = pucContent + MAX_FACILITY_LEN;

    /*对参数项ss-Code进行编码*/
    ulRslt = SSA_EncodeSsCode(pucContent + ucOffset, &ucTmpLen, &(pSrc->SsCode), EXPLICIT_MODE);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeRegPwdReq:WARNING:SSA_EncodeSsCode encode failure");
        return ulRslt;
    }
    /*计算偏移值*/
    ucOffset = ucOffset + ucTmpLen;

    /*计算编码后字串长度*/
    *pucCodeLen = ucOffset;

    return SSA_SUCCESS;
}

/*****************************************************************************
 Prototype      : SSA_EncodeGetPwdRsp
 Description    : 对MS发起的GetPassword操作的facility内容进行编码
 Input          : *pSrc--编码前的数据结构
 Output         : *pucContent--编码后的字串   *pucCodeLen--字串的长度
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_EncodeGetPwdRsp(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, TAF_SS_GETPWD_RSP_STRU *pSrc)
{
    VOS_UINT8           ucTmpLen = 0;              /*记录每个参数项的编码长度,初始值为0*/
    VOS_UINT8           ucOffset = 0;
    VOS_UINT32          ulRslt;

    gpucSsEncodeEndLocation = pucContent + MAX_FACILITY_LEN;

    /*对参数项currentPassword(NumericString类型)进行编码*/
    ulRslt = SSA_EncodeNumericString(pucContent + ucOffset, &ucTmpLen, pSrc->aucPwdStr, TAF_SS_MAX_PASSWORD_LEN, EXPLICIT_MODE);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeGetPwdRsp:WARNING:SSA_EncodeNumericString encode failure");
        return ulRslt;
    }
    /*计算偏移值*/
    ucOffset = ucOffset + ucTmpLen;

    /*计算编码后字串长度*/
    *pucCodeLen = ucOffset;

    return SSA_SUCCESS;

}

/*****************************************************************************
 Prototype      : SSA_EncodeProcessUntructuredSSReq
 Description    : 对MS发起的ProcessUntructuredSS操作的facility内容进行编码
 Input          : *pSrc--编码前的数据结构
 Output         : *pucContent--编码后的字串   *pucCodeLen--字串的长度
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
  2.日    期   : 2012年02月24日
    作    者   : 傅映君/f62575
    修改内容   : C50_IPC Project  适配FDN业务，所有数据从SS实体获取
  3.日    期   : 2012年11月24日
    作    者   : 傅映君/f62575
    修改内容   : DTS2012120407185: STK触发USSD业务失败
  4.日    期   : 2013年5月23日
    作    者   : W00176964
    修改内容   : SS FDN&Call Control项目:SSA_EncodeUssdMessage函数名替换
  5.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级
*****************************************************************************/
VOS_UINT32  SSA_EncodeProcessUntructuredSSReq(
    VOS_UINT8                          *pucContent,
    VOS_UINT8                          *pucCodeLen,
    VOS_UINT8                           ucTi
)
{
    /*记录每个参数项的编码长度,初始值为0*/
    VOS_UINT8                           ucTmpLen;
    VOS_UINT8                           ucOffset;
    VOS_UINT32                          ulRslt;
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    MN_MSG_CBDCS_CODE_STRU              stDcsInfo;
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

    ucTmpLen                = 0;
    ucOffset                = 0;
    gpucSsEncodeEndLocation = pucContent + MAX_FACILITY_LEN;

    /*对参数项ussd-DataCodingScheme进行编码*/
    ulRslt = SSA_EncodeUssdDataCodingScheme(pucContent + ucOffset,
                                            &ucTmpLen,
                                            &gastSsaStatetable[ucTi].DatacodingScheme,
                                            EXPLICIT_MODE);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*计算偏移值*/
    ucOffset = ucOffset + ucTmpLen;

    /*
    将APP的字串根据编码方案,进行编码,根据GSM02.90，在所有移动台发起的操作中，其D
    CS必须设定为 "Language Unspecified"和"Default alphabet"。根据GSM03.38，其编
    码为OXOF（二进制为0000 1111）
    */
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    PS_MEM_SET(&stDcsInfo, 0, sizeof(stDcsInfo));
    ulRslt = MN_MSG_DecodeCbsDcs(gastSsaStatetable[ucTi].DatacodingScheme,
                                 gastSsaStatetable[ucTi].pstUssdBuf->aucUssdStr,
                                 gastSsaStatetable[ucTi].pstUssdBuf->usCnt,
                                 &stDcsInfo);
    if (MN_ERR_NO_ERROR != ulRslt)
    {
        stDcsInfo.enMsgCoding = MN_MSG_MSG_CODING_7_BIT;
    }

    if (MN_MSG_MSG_CODING_7_BIT == stDcsInfo.enMsgCoding)
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
    {
        if(AT_USSD_NON_TRAN_MODE == SSA_GetUssdTransMode())
        {
            ulRslt = TAF_MmiEncodeUssdMessage(gastSsaStatetable[ucTi].pstUssdBuf);
            if (VOS_FALSE == ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_EncodeProcessUntructuredSSReq:WARNING:SSA_EncodeUssdMessage encode failure");
                return SSA_PARA_ERROR;
            }
        }
        else
        {
            ulRslt = TAF_STD_AsciiNum2HexString(gastSsaStatetable[ucTi].pstUssdBuf->aucUssdStr,
                                               &(gastSsaStatetable[ucTi].pstUssdBuf->usCnt));

            if (VOS_FALSE == ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_EncodeProcessUntructuredSSReq:WARNING:SSA_AsciiNum2HexString encode failure");
                return SSA_PARA_ERROR;
            }
        }
    }
    else
    {
        if (gastSsaStatetable[ucTi].pstUssdBuf->usCnt > TAF_SS_MAX_USS_CHAR)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeProcessUntructuredSSReq:WARNING:String too Long failure");
            return SSA_PARA_ERROR;
        }
    }

    /*对参数项ussd-String进行编码*/
    ulRslt = SSA_EncodeUssdString(pucContent + ucOffset, &ucTmpLen, gastSsaStatetable[ucTi].pstUssdBuf, EXPLICIT_MODE);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeProcessUntructuredSSReq:WARNING:SSA_EncodeUssdString encode failure");
        return ulRslt;
    }

    /*计算偏移值*/
    ucOffset = ucOffset + ucTmpLen;

    /*如果有参数项alertingPattern，则进行相应参数项的编码*/
    if (gastSsaStatetable[ucTi].OP_AlertingPattern)
    {
        ulRslt = SSA_EncodeAlertingPattern(pucContent + ucOffset, &ucTmpLen, &(gastSsaStatetable[ucTi].AlertingPattern), EXPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeProcessUntructuredSSReq:WARNING:SSA_EncodeAlertingPattern encode failure");
            return ulRslt;
        }

        /*计算偏移值*/
        ucOffset = ucOffset + ucTmpLen;
    }

    /*如果有参数项msisdn，则进行相应参数项的编码*/
    if (gastSsaStatetable[ucTi].OP_Msisdn)
    {
        ulRslt = SSA_EncodeMsisdn(pucContent + ucOffset, &ucTmpLen, gastSsaStatetable[ucTi].aucMsisdn, IMPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeProcessUntructuredSSReq:WARNING:SSA_EncodeMsisdn encode failure");
            return ulRslt;
        }

        /*因为是IMPLICIT模式，对头部进行封装*/
        ulRslt = SSA_PackTL(0x80, pucContent + ucOffset, &ucTmpLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeProcessUntructuredSSReq:WARNING:Msisdn: Tag Length encode failure");
            return ulRslt;
        }

        /*计算偏移值*/
        ucOffset = ucOffset + ucTmpLen;
    }

    /*计算编码后字串长度*/
    *pucCodeLen = ucOffset;
    /*整个参数的结构体头部封装*/
    ulRslt = SSA_PackTL(0x30 , pucContent, pucCodeLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeProcessUntructuredSSReq:WARNING:ProcessUntructuredSS: Tag Length encode failure");
        return ulRslt;
    }
    return SSA_SUCCESS;
}

/*****************************************************************************
 Prototype      : SSA_EncodeUssData
 Description    : 对MS发起的ProcessUntructuredSS操作的facility内容进行编码
 Input          : *pSrc--编码前的数据结构
 Output         : *pucContent--编码后的字串   *pucCodeLen--字串的长度
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2007-01-22
    Author      : ---
    Modification: Created function for A32D08448
*****************************************************************************/
VOS_UINT32  SSA_EncodeUssData(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, TAF_SS_PROCESS_USSDATA_REQ_STRU *pSrc)
{
    VOS_UINT8           ucTmpLen = 0;          /*记录每个参数项的编码长度,初始值为0*/
    VOS_UINT8           ucOffset = 0;
    VOS_UINT32          ulRslt;

    gpucSsEncodeEndLocation = pucContent + MAX_FACILITY_LEN;

    /*对参数项ussd-DataCodingScheme进行编码*/
    ulRslt = SSA_EncodeIa5String(pucContent + ucOffset, &ucTmpLen, pSrc->aucUserData, pSrc->ucCnt, IMPLICIT_MODE);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*因为是IMPLICIT模式，对头部进行封装*/
    ulRslt = SSA_PackTL(IA5STRING_TAG, pucContent + ucOffset, &ucTmpLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeProcessUntructuredSSReq:WARNING:Msisdn: Tag Length encode failure");
        return ulRslt;
    }
    /*计算偏移值*/
    ucOffset = ucOffset + ucTmpLen;

    /*计算编码后字串长度*/
    *pucCodeLen = ucOffset;


    return SSA_SUCCESS;
}

/*****************************************************************************
 Prototype      : SSA_EncodeUntructuredSSRsp
 Description    : 对MS发起的UntructuredSS操作的facility内容进行编码
 Input          : *pSrc--编码前的数据结构
 Output         : *pucContent--编码后的字串   *pucCodeLen--字串的长度
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
   2.日    期   : 2013年5月23日
     作    者   : W00176964
     修改内容   : SS FDN&Call Control项目:SSA_EncodeUssdMessage函数名替换
   3.日    期   : 2013年6月26日
     作    者   : f62575
     修改内容   : V9R1 STK升级
*****************************************************************************/
VOS_UINT32  SSA_EncodeUntructuredSSRsp(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, TAF_SS_USS_RSP_STRU *pSrc)
{
    VOS_UINT8                           ucTmpLen = 0;              /*记录每个参数项的编码长度,初始值为0*/
    VOS_UINT8                           ucOffset = 0;
    VOS_UINT32                          ulRslt;
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    MN_MSG_CBDCS_CODE_STRU              stDcsInfo;
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

    gpucSsEncodeEndLocation = pucContent + MAX_FACILITY_LEN;

    /*对参数项ussd-DataCodingScheme进行编码*/
    ulRslt = SSA_EncodeUssdDataCodingScheme(pucContent + ucOffset, &ucTmpLen, &(pSrc->DataCodeScheme), EXPLICIT_MODE);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeUntructuredSSRsp:WARNING:SSA_EncodeUssdDataCodingScheme encode failure");
        return ulRslt;
    }
    /*计算偏移值*/
    ucOffset = ucOffset + ucTmpLen;

    /*对参数项ussd-String进行编码*/
    /*
    将APP的字串根据编码方案,进行编码,根据GSM02.90，在所有移动台发起的操作中，其D
    CS必须设定为 "Language Unspecified"和"Default alphabet"。根据GSM03.38，其编
    码为OXOF（二进制为0000 1111）
    */
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    PS_MEM_SET(&stDcsInfo, 0, sizeof(stDcsInfo));
    ulRslt = MN_MSG_DecodeCbsDcs(pSrc->DataCodeScheme,
                                 pSrc->UssdStr.aucUssdStr,
                                 pSrc->UssdStr.usCnt,
                                &stDcsInfo);
    if (MN_ERR_NO_ERROR != ulRslt)
    {
        stDcsInfo.enMsgCoding = MN_MSG_MSG_CODING_7_BIT;
    }

    if (MN_MSG_MSG_CODING_7_BIT == stDcsInfo.enMsgCoding)
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
    {
        if (AT_USSD_NON_TRAN_MODE == SSA_GetUssdTransMode())
        {
            ulRslt = TAF_MmiEncodeUssdMessage(&(pSrc->UssdStr));

            if (VOS_FALSE == ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_EncodeUntructuredSSRsp:WARNING:SSA_EncodeUssdMessage encode failure");
                return SSA_PARA_ERROR;
            }
        }
        else
        {
            ulRslt = TAF_STD_AsciiNum2HexString(pSrc->UssdStr.aucUssdStr, &(pSrc->UssdStr.usCnt));

            if (VOS_FALSE == ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_EncodeUntructuredSSRsp:WARNING:SSA_AsciiNum2HexString encode failure");
                return SSA_PARA_ERROR;
            }
        }
    }

    ulRslt = SSA_EncodeUssdString(pucContent + ucOffset, &ucTmpLen, &(pSrc->UssdStr), EXPLICIT_MODE);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeUntructuredSSRsp:WARNING:SSA_EncodeUssdString encode failure");
        return ulRslt;
    }

    /*计算偏移值*/
    ucOffset = ucOffset + ucTmpLen;

     /*计算编码后字串长度*/
    *pucCodeLen = ucOffset;
    /*整个参数的结构体头部封装*/
    ulRslt = SSA_PackTL(0x30 , pucContent, pucCodeLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeUntructuredSSRsp:WARNING:UntructuredSSRsp: Tag Length encode failure");
        return ulRslt;
    }

    return SSA_SUCCESS;

}


/*****************************************************************************
 Prototype      : SSA_EncodeEraseCCEntryReq
 Description    : 对MS发起的EraseCCEntry操作的facility内容进行编码
 Input          : *pSrc--编码前的数据结构
 Output         : *pucContent--编码后的字串   *pucCodeLen--字串的长度
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_EncodeEraseCCEntryReq(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, TAF_SS_ERASECC_ENTRY_REQ_STRU  *pSrc)
{
    VOS_UINT8           ucTmpLen = 0;              /*记录每个参数项的编码长度,初始值为0*/
    VOS_UINT8           ucOffset = 0;
    VOS_UINT32          ulRslt;

    gpucSsEncodeEndLocation = pucContent + MAX_FACILITY_LEN;

    /*对参数项ss-Code进行编码*/
    ulRslt = SSA_EncodeSsCode(pucContent + ucOffset, &ucTmpLen, &(pSrc->SsCode), IMPLICIT_MODE);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeEraseCCEntryReq:WARNING:SSA_EncodeSsCode encode failure");
        return ulRslt;
    }
    /*因为是IMPLICIT模式，对头部进行封装*/
    ulRslt = SSA_PackTL(0x80 , pucContent + ucOffset, &ucTmpLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeEraseCCEntryReq:WARNING:SsCode: Tag Length encode failure");
        return ulRslt;
    }

    /*计算偏移值*/
    ucOffset = ucOffset + ucTmpLen;

    /*如果有参数项ccbs-Indexs，则进行相应参数项的编码*/
    if (pSrc->OP_CcbsIndex)
    {
        ulRslt = SSA_EncodeCcbsIndex(pucContent + ucOffset, &ucTmpLen, pSrc->CcbsIndex, IMPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeEraseCCEntryReq:WARNING:SSA_EncodeCcbsIndex encode failure");
            return ulRslt;
        }
        /*因为是IMPLICIT模式，对头部进行封装*/
        ulRslt = SSA_PackTL(0x81 , pucContent + ucOffset, &ucTmpLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeEraseCCEntryReq:WARNING:CcbsIndex: Tag Length encode failure");
            return ulRslt;
        }

        /*计算偏移值*/
        ucOffset = ucOffset + ucTmpLen;
    }

    /*计算编码后字串长度*/
    *pucCodeLen = ucOffset;
    /*整个参数的结构体头部封装*/
    ulRslt = SSA_PackTL(0x30 , pucContent, pucCodeLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeEraseCCEntryReq:WARNING:EraseCCEntry: Tag Length encode failure");
        return ulRslt;
    }

    return SSA_SUCCESS;

}

#if 0
/*****************************************************************************
 Prototype      : SSA_EncodeUnstructuredSSDataReq
 Description    : 对MS发起的Process-UnstructuredSSData操作的facility内容进行编码
 Input          : *pSrc--编码前的数据结构
 Output         : *pucContent--编码后的字串   *pucCodeLen--字串的长度
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_EncodeProcessUSSDataReq(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, TAF_SS_PROCESS_USSDATA_REQ_STRU  *pSrc)
{
    VOS_UINT32          ulRslt;

    gpucSsEncodeEndLocation = pucContent + MAX_FACILITY_LEN;

    if (pSrc->ucCnt > TAF_SS_MAX_NUM_OF_USERDATA)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeProcessUSSDataReq:WARNING:StrLen too Long");
        return SSA_PARA_ERROR;
    }

    /*参数项ss-UserData(IA5String类型)编码*/
    ulRslt = SSA_EncodeIA5String(pucContent, pucCodeLen, pSrc->aucUserData, pSrc->ucCnt, EXPLICIT_MODE);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeEraseCCEntryReq:WARNING:SSA_EncodeCcbsIndex encode failure");
        return ulRslt;
    }
    return SSA_SUCCESS;
}
#endif

/*****************************************************************************
 Prototype      : SSA_EncodeBasicService
 Description    : 参数basicservice的编码，参见24.080 Annex A的ASN.1描述
 Input          : *pSrc--编码前的数据结构, ucTagMode -- 标签模式,EXPLICIT_MODE还是IMPLICIT_MODE
 Output         : *pucContent--编码后的字串   *pucCodeLen--字串的长度
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_EncodeBasicService(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, TAF_SS_BASIC_SERVICE_STRU  *pstSrc, TAG_MODE ucTagMode)
{
    VOS_UINT32      ulRslt;

    /*长度初始化为0*/
    *pucCodeLen = 0;

    switch (pstSrc->BsType)
    {
        /*bearerService编码*/
        case TAF_SS_BEARER_SERVICE:
            ulRslt = SSA_EncodeBearerService(pucContent, pucCodeLen, &(pstSrc->BsServiceCode), IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_EncodeBasicService:WARNING:SSA_EncodeBearerService encode failure");
                return ulRslt;
            }
            ulRslt = SSA_PackTL(0x82, pucContent, pucCodeLen);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_EncodeBasicService:WARNING:bearerService Tag Length encode failure");
                return ulRslt;
            }

            break;

        /*teleservice编码*/
        case TAF_SS_TELE_SERVICE:
            ulRslt = SSA_EncodeTeleService(pucContent, pucCodeLen, &(pstSrc->BsServiceCode), IMPLICIT_MODE);
            if (ulRslt != SSA_SUCCESS)
            {
                SSA_LOG(WARNING_PRINT, "SSA_EncodeBasicService:WARNING:SSA_EncodeTeleService encode failure");
                return ulRslt;
            }
            ulRslt = SSA_PackTL(0x83, pucContent, pucCodeLen);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_EncodeBasicService:WARNING:teleservice Tag Length encode failure");
                return ulRslt;
            }
            break;
        default:
            /*参数异常处理*/
            SSA_LOG(WARNING_PRINT, "SSA_EncodeBasicService:WARNING:Parameter Error!");
            return SSA_PARA_ERROR;
    }

    return SSA_SUCCESS;
}

/*****************************************************************************
 Prototype      : SSA_EncodeForwardedToNumber
 Description    : 参数forwardedToNumber的编码，参见24.080 Annex A的ASN.1描述
 Input          : *pSrc--编码前的数据结构, ucTagMode -- 标签模式,EXPLICIT_MODE还是IMPLICIT_MODE
 Output         : *pucContent--编码后的字串   *pucCodeLen--字串的长度
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_EncodeForwardedToNumber(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, VOS_UINT8 ucNumType, VOS_UINT8 *pucFwdNum, TAG_MODE ucTagMode)
{
    VOS_UINT8       ucAscIItrLen;
    VOS_UINT8       ucBcdStrLen;
    VOS_UINT32      ulRslt;
    VOS_UINT8       aucStr[TAF_SS_MAX_ENCODE_FWD_TO_NUM_LEN];

    /*获取ASCII码字符串的长度*/
    ucAscIItrLen = (VOS_UINT8)VOS_StrLen((VOS_CHAR *)pucFwdNum);
    if (ucAscIItrLen > (TAF_SS_MAX_FORWARDED_TO_NUM_LEN - 1))
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeForwardedToNumber:WARNING: String too Long");
        return SSA_PARA_ERROR;
    }

    /*将numtype 和 number 统一放到一个字符串内*/
    aucStr[0] = ucNumType;
    ulRslt = SSA_AsciiNumToBcdNum(pucFwdNum, ucAscIItrLen, aucStr + 1, &ucBcdStrLen, &(aucStr[0])); /*<==A32D10708*/
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeForwardedToNumber:WARNING: value is too large");
        return ulRslt;
    }

    /*字符串的BER编码*/
    ulRslt = SSA_EncodeString(pucContent, pucCodeLen, aucStr, ucBcdStrLen + 1, ucTagMode);

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_EncodeForwardedToSubaddress
 Description    : 参数forwardedToSubaddress的编码，参见24.080 Annex A的ASN.1描述
 Input          : *pSrc--编码前的数据结构, ucTagMode -- 标签模式,EXPLICIT_MODE还是IMPLICIT_MODE
 Output         : *pucContent--编码后的字串   *pucCodeLen--字串的长度
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_EncodeForwardedToSubaddress(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, VOS_UINT8 ucSubAddrType, VOS_UINT8  *paucFwdToSubAddr, TAG_MODE ucTagMode)
{
    VOS_UINT32      ulRslt;
    VOS_UINT8       ucStrLen;
    VOS_UINT8       aucStr[TAF_SS_MAX_ENCODE_FWD_TO_SUBADDR_LEN];

    /*将地址类型和子地址的字串合并到一个字符串中*/
    ucStrLen = (VOS_UINT8)VOS_StrLen((VOS_CHAR *)paucFwdToSubAddr);
    if (ucStrLen > (TAF_SS_MAX_ENCODE_FWD_TO_SUBADDR_LEN - 1))
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeForwardedToSubaddress:WARNING: String too Long");
        return SSA_PARA_ERROR;
    }

    aucStr[0] = ucSubAddrType;
    PS_MEM_CPY(aucStr + 1, paucFwdToSubAddr, ucStrLen);

    /*字符串编码*/
    ulRslt = SSA_EncodeString(pucContent, pucCodeLen, aucStr, ucStrLen + 1, ucTagMode);

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_EncodeUssdString
 Description    : 编码参数ussd-String参见24.080的Annex A的ASN.1的描述
 Input          : *pSrc--编码前的数据结构, ucTagMode -- 标签模式,EXPLICIT_MODE还是IMPLICIT_MODE
 Output         : *pucContent--编码后的字串   *pucCodeLen--字串的长度
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_EncodeUssdString(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, TAF_SS_USSD_STRING_STRU  *pSrc, TAG_MODE ucTagMode)
{
    VOS_UINT32   ulRslt;

    /*字符串编码*/
    ulRslt = SSA_EncodeString(pucContent, pucCodeLen, pSrc->aucUssdStr, (VOS_UINT8)pSrc->usCnt, ucTagMode);

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_EncodeMsisdn
 Description    : 编码参数msisdn参见24.080的Annex A的ASN.1的描述
 Input          : *pSrc--编码前的数据结构, ucTagMode -- 标签模式,EXPLICIT_MODE还是IMPLICIT_MODE
 Output         : *pucContent--编码后的字串   *pucCodeLen--字串的长度
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_EncodeMsisdn(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, VOS_UINT8  *pucSrc, TAG_MODE ucTagMode)
{
    VOS_UINT32   ulRslt;
    VOS_UINT8    ucStrLen;

    /*获取ASCII码字符串的长度*/
    ucStrLen = (VOS_UINT8)VOS_StrLen((VOS_CHAR *)pucSrc);
    if (ucStrLen > TAF_SS_MAX_MSISDN_LEN)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeMsisdn:WARNING: String too Long");
        return SSA_PARA_ERROR;
    }


    /*字符串编码*/
    ulRslt = SSA_EncodeString(pucContent, pucCodeLen, pucSrc, ucStrLen, ucTagMode);

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_EncodeErrorCode
 Description    : 编码参数Problem code的TLV,参见24.080的 Table 3.3的描述
 Input          : ucProblemCode -- problem Code的值
 Output         : *pucContent -- 编码后的字串,*pucCodeLen编码后的字串长度
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID SSA_EncodeErrorCode(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, VOS_UINT16 usErrCode)
{
    VOS_UINT8    ucTmp[3];

    /*T、L、V赋值*/
    ucTmp[0] = ERROR_CODE_TAG;
    ucTmp[1] = 1;
    /*提供给APP的错误码均有值的偏移,因此回复给网络侧的需要是网络侧定义的值*/
    if (usErrCode > TAF_SS_ERRCODE_OFFSET)
    {
        ucTmp[2] = (VOS_UINT8)(usErrCode - TAF_SS_ERRCODE_OFFSET);
    }

    /*内存移位拷贝*/
    (VOS_VOID)memmove(pucContent + 3, pucContent, *pucCodeLen);
    (VOS_VOID)memcpy(pucContent, ucTmp, 3);
    *pucCodeLen += 3;
}


 /*****************************************************************************
 Prototype      : SSA_EncodeProblemCode
 Description    : 编码参数Problem code的TLV,参见24.080的 Table 3.3的描述
 Input          : ucProblemCode -- problem Code的值
 Output         : *pucContent -- 编码后的字串,*pucCodeLen编码后的字串长度
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID SSA_EncodeProblemCode(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, VOS_UINT8 ucProblemCode)
{
    VOS_UINT8    ucTmp[3];

    /*T、L、V赋值*/
    /*ProblemCode的高4位决定了problem tag,低4位决定了具体tag下的错误码*/
    ucTmp[0] = 0x80 + (ucProblemCode >> 4);
    ucTmp[1] = 1;
    ucTmp[2] = ucProblemCode & 0x0f;

    /*内存移位拷贝*/
    (VOS_VOID)memmove(pucContent + 3, pucContent, *pucCodeLen);
    (VOS_VOID)memcpy(pucContent, ucTmp, 3);
    *pucCodeLen += 3;
}

 /*****************************************************************************
 Prototype      : SSA_EncodeOperationCode
 Description    : 编码参数Operation code的TLV,参见24.080的 Table 3.3的描述
 Input          : ucOpCode--Operation Code的值
 Output         : *pucContent--编码后的字串,*pucCodeLen编码后的字串长度
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID SSA_EncodeOperationCode(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, VOS_UINT8 ucOpCode)
{
    VOS_UINT8    ucTmp[3];

    /*T、L、V赋值*/
    ucTmp[0] = OPERATION_CODE_TAG;
    ucTmp[1] = 1;
    ucTmp[2] = ucOpCode;

    /*内存移位拷贝*/
    (VOS_VOID)memmove(pucContent + 3, pucContent, *pucCodeLen);
    (VOS_VOID)memcpy(pucContent, ucTmp, 3);
    *pucCodeLen += 3;
}

 /*****************************************************************************
 Prototype      : SSA_EncodeSequenceTag
 Description    : 编码参数Sequence Tag的TL,参见24.080的 Table 3.3的描述
 Input          : *pucCodeLen--编码前的字串长度
 Output         : *pucContent--编码后的字串,*pucCodeLen编码后的字串长度
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID SSA_EncodeSequenceTag(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen)
{
    VOS_UINT8    ucTmp[3];

    /*T、L、V赋值*/
    ucTmp[0] = TAG_SS_OF_SEQUENCE;
    ucTmp[1] = *pucCodeLen;

    /*内存移位拷贝*/
    (VOS_VOID)memmove(pucContent + 2, pucContent, *pucCodeLen);
    (VOS_VOID)memcpy(pucContent, ucTmp, 2);
    *pucCodeLen += 2;
}

/*****************************************************************************
 Prototype      : SSA_EncodeInvokeId
 Description    : 编码参数Invoke Id的TLV,参见24.080的Table 3.3的描述
 Input          : ucInvokeId -- INVOKE ID的值
 Output         : *pucContent--编码后的字串,*pucCodeLen编码后的字串长度
 Return Value   : 无
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID SSA_EncodeInvokeId(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, VOS_UINT8 ucInvokeId)
{
    VOS_UINT8    ucTmp[3];

    /*T、L、V赋值*/
    ucTmp[0] = INVOKE_ID_TAG;
    ucTmp[1] = 1;
    ucTmp[2] = ucInvokeId;

    /*内存移位拷贝*/
    (VOS_VOID)memmove(pucContent + 3, pucContent, *pucCodeLen);
    (VOS_VOID)memcpy(pucContent, ucTmp, 3);
    *pucCodeLen += 3;
}

/*****************************************************************************
 Prototype      : SSA_EncodeComponentType
 Description    : 编码参数Component Type的TL,参见24.080的Table 3.3的描述
 Input          : ucComponentTag -- component type标签值
 Output         : *pucContent--编码后的字串,*pucCodeLen编码后的字串长度
 Return Value   : 无
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID SSA_EncodeComponentType(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, VOS_UINT8 ucComponentTag)
{
    VOS_UINT8    ucTmp[5];
    VOS_UINT8    ucheaderLen;

    /*T、L赋值*/
    ucTmp[0] = ucComponentTag;

    SSA_EncodeLength(*pucCodeLen, ucTmp + 1, &ucheaderLen);
    ucheaderLen ++;


    /*内存移位拷贝*/
    (VOS_VOID)memmove(pucContent + ucheaderLen, pucContent, *pucCodeLen);
    (VOS_VOID)memcpy(pucContent, ucTmp, ucheaderLen);
    *pucCodeLen += ucheaderLen;

}

VOS_UINT32 SSA_AsciiNumToBcdNum(VOS_UINT8 *pucAsciiNum, VOS_UINT8 ucAsciiNumLen, VOS_UINT8 *pucBcdNum,
                                VOS_UINT8 *pucBcdNumLen, VOS_UINT8 *pucNewNumType)
{
    VOS_UINT32     i, k;
    VOS_UINT8     *pucTemp, ucNewAsciiNumLen;

    pucTemp = pucBcdNum;
    ucNewAsciiNumLen = ucAsciiNumLen;

    /*==>A32D10708*/
    if ('+' == *(pucAsciiNum))
    {
        /*remove the 1st character:'+' from the input number string*/
        (VOS_VOID)PS_MEM_MOVE(pucAsciiNum, pucAsciiNum + 1, ucNewAsciiNumLen - 1);
        ucNewAsciiNumLen--;

        /*change the number type to "international number"+"E.164"*/
        *pucNewNumType = SSA_NUM_TYPE_INT_E164;
    }
    /*<==A32D10708*/

    for (i = 0; i < ucNewAsciiNumLen; i++)
    {
        k = i % 2;

        /*ASCII NUMber  is  '0'~'9'*/
        if ((*(pucAsciiNum + i) >= 0x30) && (*(pucAsciiNum + i) <= 0x39))
        {
            if(k == 0)
            {
                *(pucTemp + (i/2)) = *(pucAsciiNum + i) - 0x30;
            }
            else
            {
                *(pucTemp + (i/2)) = (VOS_UINT8)(((VOS_UINT8)(*(pucAsciiNum + i) - 0x30) << 4) | *(pucTemp + (i/2)));
            }
        }
        else if('*' == *(pucAsciiNum + i))   /* the key is '*' */
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
        else if('#' == *(pucAsciiNum + i))   /* the key is '#' */
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
        else
        {
            TAF_PRINT( TAF_SSA, WARNING_PRINT, "SSA_AsciiNumToBcdNum:  The key is invalid" );
            return SSA_PARA_ERROR;
        }
    }

    *pucBcdNumLen = ucNewAsciiNumLen/2;

    if((ucNewAsciiNumLen % 2) == 1)
    {
        *(pucTemp + (ucNewAsciiNumLen / 2)) = 0xf0 | *(pucTemp + (ucNewAsciiNumLen / 2));
        (*pucBcdNumLen)++;
    }
    return SSA_SUCCESS;
}


/*****************************************************************************
*  Prototype       : SSA_Put7bits
*  Description     : 对输入的字节进行7bit编码
*  Input           : ulBitAddress  --- 以7为增量的bit串的长度值
*                    ucChar        --- 输入的字节
*  Output          : pucEncodedMsg --- 指向7bit编码转换后的短消息字符串的指针
*  Return Value    : SMT_FALSE     --- 失败
*                    SMT_TRUE      --- 成功
*  Calls           :
*  Called By       : Smt_EncodeMessage
*
*  History         :
*  1. Date         : 2005-10-13
*     Author       : 郜东东
*     Modification : Created function
*****************************************************************************/
VOS_UINT8 SSA_Put7bits( VOS_UINT8  *pucEncodedMsg,
                         VOS_UINT32  ulBitAddress,
                         VOS_UINT8   ucChar )
{
    VOS_UINT32    ulAddress;    /*存放字节地址*/
    VOS_UINT32    ulOffset;     /*存放位偏移*/

    /*检查参数的合法性*/
    if ( ucChar >= 128 )
    {
        return SSA_FAILURE;
    }

    /*计算出字节地址和位偏移*/
    ulAddress = ulBitAddress / 8;
    ulOffset  = ulBitAddress % 8;

    /*将需要编码的字符分成两部分，分别填入相邻的两个字节*/
    /*将第一部分的内容编码*/
    /*lint -e701*/
    pucEncodedMsg[ulAddress] |= (VOS_UINT8)( ucChar << ulOffset );
    /*lint +e701*/

    /*如果位偏移小于2，则没有第二部分的内容，直接返回*/
    if ( ulOffset < 2 )
    {
        return SSA_SUCCESS;
    }

    /*将第二部分的内容编码*/
    pucEncodedMsg[ulAddress + 1] |= ( ucChar >> ( 8 - ulOffset ) );

    return SSA_SUCCESS;
}



/*****************************************************************************
 Prototype      : SSA_Pack_TL
 Description    : 封装头部的T或者TL，参照Basetype.c文件中的pack函数
 Input          : ucTag--编码前Tag的值,
 Output         : *pucContent--编码后的字串    *pucLen--编码后的长度
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/

VOS_UINT32  SSA_PackTL(VOS_UINT8  ucTag,  VOS_UINT8   *pucContent,  VOS_UINT8 *pucCodeLen)
{
    VOS_UINT8    aucTmppool[5];
    VOS_UINT8    ucheaderLen;

    /*判断pucContent是否的地址是否在合法的范围内*/
    if (pucContent > gpucSsEncodeEndLocation)
    {
        SSA_LOG(WARNING_PRINT, "SSA_PackTL:WARNING:pucContent beyond mark");
        return SSA_PARA_ERROR;
    }

    /*如果当前还没有进行任何的参数的编码,整个长度为0*/
    if (0 == *pucCodeLen)
    {
        *pucContent = ucTag;
        *(pucContent + 1) = 0;
        *pucCodeLen = 2;
        return SSA_SUCCESS;
    }


    aucTmppool[0] = ucTag;
    /*对长度进行编码*/
    SSA_EncodeLength(*pucCodeLen, aucTmppool + 1, &ucheaderLen);
    ucheaderLen ++;

    /*判断ucheaderLen的长度是否小于4(当前的最短长度),小于4为出错*/
    if (ucheaderLen > 4)
    {
        SSA_LOG(WARNING_PRINT, "SSA_PackTL:WARNING:Length is Wrong");
        return SSA_PARA_ERROR;
    }

    /*对当前字串进行移位(为TL预留出空间)和拷贝*/
    (VOS_VOID)VOS_MemMove(pucContent + ucheaderLen, pucContent, *pucCodeLen);
    PS_MEM_CPY(pucContent, aucTmppool, ucheaderLen);

    /*当前已经编码的字串长度*/
    *pucCodeLen = ucheaderLen + *pucCodeLen;

    return SSA_SUCCESS;

}


/*****************************************************************************
 Prototype      : Encode_NumericString
 Description    : 将普通的字符串编码成NumericString类型的BER编码的字串
 Input          : *pucSrc--编码前的字符串  ucSrcLen--字符串长度
 Output         : *pcodeContent--编码后的字串   *pucCodeLen--编码后的字串长度
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_EncodeNumericString(VOS_UINT8 *pucCodeContent, VOS_UINT8 *pucCodeLen, VOS_UINT8 *pucSrc, VOS_UINT8 ucSrcLen, TAG_MODE ucTagMode)
{
    VOS_UINT32      ulRslt;

    /*调用相应的解码函数*/
    ulRslt = SSA_EncodeOtherString(NUMERICSTRING_TAG, pucCodeContent, pucCodeLen, pucSrc, ucSrcLen, ucTagMode);

    return ulRslt;
}


#if 0
/*****************************************************************************
 Prototype      : Encode_IA5String
 Description    : 将普通的字符串编码成IA5String类型的BER编码的字串
 Input          : *pucSrc--编码前的字符串  ucSrcLen--字符串长度
 Output         : *pcodeContent--编码后的字串   *pucCodeLen--编码后的字串长度
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_EncodeIA5String(VOS_UINT8 *pucCodeContent, VOS_UINT8 *pucCodeLen, VOS_UINT8 *pucSrc, VOS_UINT8 ucSrcLen, TAG_MODE ucTagMode)
{
    VOS_UINT32      ulRslt;

    /*调用相应的解码函数*/
    ulRslt = SSA_EncodeOtherString(IA5STRING_TAG, pucCodeContent, pucCodeLen, pucSrc, ucSrcLen, ucTagMode);

    return ulRslt;
}
#endif

/*****************************************************************************
 Prototype      : Encode_INT
 Description    : 对整型数值进行编码
 Input          : lSrc--编码前整型数值, lMaxNum -- 整型数值的最大值
 Output         : *pucContent--编码后的字串   *pucCodeLen--编码后字串的长度
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_EncodeInt(VOS_UINT8 *pucCodeContent, VOS_UINT8 *pucCodeLen, VOS_INT iSrc, VOS_INT iMaxNum, VOS_INT iMiniNum, TAG_MODE ucTagMode)
{
    VOS_UINT8   j = 0 , k = 0 ;
    VOS_UINT8   auctmpbuffer[sizeof(VOS_INT)];
    VOS_INT     Tmpvalue, Tmpint;
    VOS_UINT32  ulRslt;

    /*判断输入的整数是否超过了限定的范围*/
    if ((iSrc > iMaxNum)||(iSrc < iMiniNum))
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeInt:WARNING: value is beyond range");
        return SSA_PARA_ERROR;
    }

    /*判断当前地址有没有越界*/
    if (pucCodeContent > gpucSsEncodeEndLocation)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeString:WARNING: beyond mark");
        return SSA_PARA_ERROR;
    }

    /*lint -e961*/
    /*对正负整数进行字节处理*/
    Tmpvalue = iSrc;
    if (iSrc > 0)
    {
        while (Tmpvalue > 255)
        {
            auctmpbuffer[k++] = (VOS_UINT8)(Tmpvalue & 0x00ff);
            Tmpvalue = (VOS_UINT)Tmpvalue >> 8;
        }
        auctmpbuffer[k++] = (VOS_UINT8)(Tmpvalue & 0x00ff);
    }
    else
    {
        Tmpint = Tmpvalue;
        while (Tmpint < -255)
        {
            auctmpbuffer[k++] = (VOS_UINT8)(Tmpint & 0x00ff);
            Tmpint = (VOS_UINT)Tmpint >> 8;
        }
        auctmpbuffer[k++] = (VOS_UINT8)(Tmpint & 0x00ff);
    }


    if (Tmpvalue >= 0)
    {
        /*最高bit的值为1时,在之前再加一个字节,该字节的值为0*/
        if ( (auctmpbuffer[k-1] & 0x80) == 0x80 )
        {
            auctmpbuffer[k++] = 0x00;
        }
    }
    else
    {
        if ( (auctmpbuffer[k-1] & 0x80) == 0x00 )
        {
            auctmpbuffer[k++] = 0xff;
        }
    }

    while (k > 0)
    {
        pucCodeContent[j++] = auctmpbuffer[k-1] ;
        k--;
    }
    /* pucCodeContent[j++] = auctmpbuffer[0]; */

    *pucCodeLen = j;
    /*lint +e961*/
    /*如果是explicit mode标签编码，对T、L进行封装*/
    if (EXPLICIT_MODE == ucTagMode)
    {
        ulRslt = SSA_PackTL(INTEGER_TAG, pucCodeContent, pucCodeLen);
        if (ulRslt != SSA_SUCCESS)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeString:WARNING: Int:Tag Length Encode Error!");
            return ulRslt;
        }
    }

    return SSA_SUCCESS;
}

/*****************************************************************************
 Prototype      : Encode_String
 Description    : 将字符串编码成Octet String类型的字串
 Input          : *pSrc--编码前的字串   ucSrcLen--编码前的字符串长度
 Output         : *pContent--编码后的字串   *pucCodeLen--编码后的字串长度
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_EncodeString(VOS_UINT8 *pucCodeContent, VOS_UINT8 *pucCodeLen, VOS_UINT8 *pucSrc, VOS_UINT8 ucSrcLen, TAG_MODE ucTagMode)
{
    VOS_UINT32  ulRslt;

    /*判断当前地址有没有越界*/
    if (pucCodeContent > gpucSsEncodeEndLocation)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeString:WARNING: beyond mark");
        return SSA_PARA_ERROR;
    }

    /*L、V赋值*/
    *pucCodeLen = ucSrcLen;
    PS_MEM_CPY(pucCodeContent, pucSrc, ucSrcLen);

    /*如果是explicit mode标签编码，对T、L进行封装*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        ulRslt = SSA_PackTL(OCTETSTRING_TAG, pucCodeContent, pucCodeLen);
        if (ulRslt != SSA_SUCCESS)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeString:WARNING: Int:Tag Length Encode Error!");
            return ulRslt;
        }
    }
    return SSA_SUCCESS;
}




/*****************************************************************************
 Prototype      : Encode_Length
 Description    : 已知TLV中L的长度，对其进行BER编码
 Input          : ucSrcLen--编码前的长度
 Output         : *pucCodeLen--编码后的长度， *pucContent--编码后的字串
 Return Value   : 无
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID  SSA_EncodeLength(VOS_UINT8 ucSrcLen, VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen)
{
    /*这里只采用了两种编码方式，不明确长度的编码方式没有采用*/
    /*如果是明确长度形式的短格式，编码处理*/
    if (ucSrcLen < 128)
    {
        /*L、V赋值*/
        *pucCodeLen = 1;
        *pucContent = ucSrcLen;
        return;
    }
    /*如果是明确长度形式的长格式,编码处理*/
    else
    {
        /*L、V赋值*/
        *pucCodeLen = 2;
        *pucContent = 0x81;
        *(pucContent + 1) = ucSrcLen;
        return;
    }

    /* return SSA_FAILURE; */

}

/*****************************************************************************
 Prototype      : Encode_OtherString
 Description    : 将普通的字符串编码成其他类型的BER编码的字串(如IA5String)
 Input          : *pSrc--编码前的字符串  ucSrcLen--字符串长度   ucTagNum--要编码成哪种字串,标签部分的编码值
 Output         : *pcodeContent--编码后的字串   *pucCodeLen--编码后的字串长度
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
  2.日    期   : 2012年8月10日
    作    者   : y00213812
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_UINT32  SSA_EncodeOtherString(VOS_UINT8 ucTagNum, VOS_UINT8 *pucCodeContent, VOS_UINT8 *pucCodeLen, VOS_UINT8 *pSrc, VOS_UINT8 ucSrcLen, TAG_MODE ucTagMode)
{
    VOS_UINT32  ulRslt;

    /*进行字符串编码*/
    /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, begin*/
    ulRslt = SSA_EncodeString(pucCodeContent, pucCodeLen, pSrc, ucSrcLen, IMPLICIT_MODE);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeOtherString():WARNING:SSA_EncodeString Error!");
    }
    /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, end*/

    /*如果是explicit mode标签编码，对T、L进行封装*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        ulRslt = SSA_PackTL(ucTagNum, pucCodeContent, pucCodeLen);
        if (ulRslt != SSA_SUCCESS)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeString:WARNING: Int:Tag Length Encode Error!");
            return ulRslt;
        }

    }

    return SSA_SUCCESS;
}

/*****************************************************************************
 Prototype      : Encode_NullType
 Description    : 对Encode_NullType进行BER编码
 Input          : ucTag--Tag的值
 Output         : *pcodeContent--编码后的字串   *pucCodeLen--编码后的字串长度
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_EncodeNullType(VOS_UINT8 ucTag, VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, TAG_MODE ucTagMode)
{
    /*判断当前地址有没有越界*/
    if (pucContent > gpucSsEncodeEndLocation)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeNullType:WARNING: beyond mark");
        return SSA_PARA_ERROR;
    }

    if (ucTagMode == IMPLICIT_MODE)
    {
        *pucCodeLen = 0;
    }
    else
    {
        *pucCodeLen = 2;
        *pucContent = ucTag;
        *(pucContent+1) = 0;
    }
    return SSA_SUCCESS;
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
