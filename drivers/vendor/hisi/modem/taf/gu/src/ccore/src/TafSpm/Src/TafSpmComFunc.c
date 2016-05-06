/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafSpmComFunc.c
  版 本 号   : 初稿
  作    者   : W00176964
  生成日期   : 2013年12月16日
  最近修改   :
  功能描述   : TafSpmComFunc.C文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年12月16日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "v_msg.h"
#include "PsTypeDef.h"
#include "TafLog.h"
#include "TafSpmMntn.h"
#include "TafSdcCtx.h"
#include "TafStdlib.h"
#include "NasUsimmApi.h"
#include "MnCallMnccProc.h"
#include "MmaAppLocal.h"
#include "TafSpmComFunc.h"
#include "MnCallCtx.h"
#include "MnCall.h"
#include "MnComm.h"
#include "TafAgentInterface.h"
#include "TafStdlib.h"
#include "MnErrorCode.h"
#include "MnMsgApi.h"
#include "TafSpmSndImsa.h"
#include "TafSpmRedial.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_SPM_COM_FUNC_C

/*****************************************************************************
  2 常量定义
*****************************************************************************/



/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/

/*****************************************************************************
  5 变量定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  6 函数定义
*****************************************************************************/

/*****************************************************************************
 函 数 名  : TAF_SPM_IsNetworkEmergencyNum
 功能描述  : 检查当前号码是否属于网络下发中的紧急呼叫号码
 输入参数  : pstDialNum         - 号码
 输出参数  : pulEmerCatExist    - Emergency Category是否合法
             pucEmerCategory    - Emergency Category合法才有效,pucEmerCategory的值
 返 回 值  : VOS_TRUE 呼叫号码是紧急呼
             VOS_FALSE 呼叫号码不是紧急呼
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月31日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  TAF_SPM_IsNetworkEmergencyNum(
    MN_CALL_CALLED_NUM_STRU             *pstDialNum,
    VOS_UINT32                          *pulEmerCatExist,
    VOS_UINT8                           *pucEmerCategory
)
{
    VOS_UINT8                           i;
    TAF_SDC_MM_EMERGENCY_LIST_STRU     *pstMmCallEmerNumList    = VOS_NULL_PTR;

    pstMmCallEmerNumList    = TAF_SDC_GetMmCallEmerNumList();

    for (i = 0; i < pstMmCallEmerNumList->ucEmergencyNumber; i++)
    {
        if (pstMmCallEmerNumList->astEmergencyLists[i].ucEmcNumLen != pstDialNum->ucNumLen)
        {
            continue;
        }

        if ( 0 == VOS_MemCmp(pstMmCallEmerNumList->astEmergencyLists[i].aucEmergencyList,
                             pstDialNum->aucBcdNum,
                             pstDialNum->ucNumLen))
        {
            *pulEmerCatExist
                = TAF_STD_IsValidEmerCategory(pstMmCallEmerNumList->astEmergencyLists[i].ucCategoryValue);

             if (VOS_TRUE == *pulEmerCatExist)
             {
                 *pucEmerCategory = (pstMmCallEmerNumList->astEmergencyLists[i].ucCategoryValue
                                   & MN_CALL_EMER_CATEGORG_VAL_MAX);
             }

             return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_IsAppCustomEmergencyNum
 功能描述  : 检查当前号码是否属于APP定制的紧急呼叫号码
 输入参数  : pstDialNum         - 号码
 输出参数  : pulEmerCategory    - Emergency Category是否合法
             pucEmerCategory    - Emergency Category合法才有效,pucEmerCategory的值
 返 回 值  : VOS_TRUE   :是紧急呼叫号码
             VOS_FALSE  :不是紧急呼叫号码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月31日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2014年12月20日
    作    者   : l00198894
    修改内容   : DTS2014110508255: 增加有卡且非正常服务时紧急呼定制功能
*****************************************************************************/
VOS_UINT32  TAF_SPM_IsAppCustomEmergencyNum(
    MN_CALL_CALLED_NUM_STRU             *pstDialNum,
    VOS_UINT32                          *pulEmerCatExist,
    VOS_UINT8                           *pucEmerCategory
)
{
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enSimStatus;
    TAF_SDC_CUSTOM_ECC_CTX_STRU        *pstCustomCallEmerNumCtx    = VOS_NULL_PTR;
    VOS_UINT8                           i;

    pstCustomCallEmerNumCtx = TAF_SDC_GetCustomCallEccNumCtx();

    /* 获取卡的状态，根据卡的存在与否做不同处理 */
    enSimStatus = TAF_SDC_GetSimStatus();

    /* 检查是否APP定制紧急呼号码 */
    for (i = 0; i < pstCustomCallEmerNumCtx->stCustomEccNumList.ucEccNumCount; i++)
    {
        if (pstDialNum->ucNumLen != pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].ucEccNumLen)
        {
            continue;
        }

        if (0 == VOS_MemCmp(pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].aucEccNum,
                             pstDialNum->aucBcdNum,
                             pstDialNum->ucNumLen) )
        {
            if (TAF_SDC_USIM_STATUS_NO_PRESENT == enSimStatus)
            {
                /* 号码是有卡时的紧急呼号码 */
                if ((MN_CALL_ECC_NUM_VALID_SIM_ABSENT != pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].ucValidSimPresent))
                {
                    continue;
                }
            }
            else
            {
                /* 号码是无卡时的紧急呼号码 */
                if ((MN_CALL_ECC_NUM_VALID_SIM_PRESENT != pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].ucValidSimPresent))
                {
                    continue;
                }

                /* 有卡时，号码是仅非正常服务时的紧急呼号码，若当前CS正常服务则不作为紧急呼号码 */
                if ( (VOS_TRUE == TAF_SDC_IsCsNormalService())
                  && (pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].ucAbnormalServiceFlg == VOS_TRUE) )
                {
                    continue;
                }
            }

            *pulEmerCatExist
                = TAF_STD_IsValidEmerCategory(pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].ucCategory);

             if (VOS_TRUE == *pulEmerCatExist)
             {
                 *pucEmerCategory = (pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].ucCategory
                                   & MN_CALL_EMER_CATEGORG_VAL_MAX);
             }

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_IsPhoneEmergencyNum
 功能描述  : 判断呼叫号码是否协议定制的紧急呼叫号码
 输入参数  : pstDialNum------被叫号码
 输出参数  : 无
 返 回 值  : VOS_TRUE   :是紧急呼叫号码
             VOS_FALSE  :不是紧急呼叫号码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月31日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_IsPhoneEmergencyNum(
    MN_CALL_CALLED_NUM_STRU            *pstDialNum
)
{
    VOS_UINT32                          ulLoop;
    VOS_CHAR                          **pucEmcNumsNoUsim    = VOS_NULL_PTR;
    VOS_CHAR                          **pucEmcNumsWithUsim  = VOS_NULL_PTR;
    VOS_INT8                            acCalledNum[MN_CALL_MAX_CALLED_ASCII_NUM_LEN + 1];

    /* 号码转换 BCD-> Ascii */
    if (MN_ERR_NO_ERROR != TAF_STD_ConvertBcdNumberToAscii(pstDialNum->aucBcdNum,
                                                           pstDialNum->ucNumLen,
                                                           (VOS_CHAR *)acCalledNum))
    {
        MN_WARN_LOG("TAF_SPM_IsPhoneEmergencyNum: BCD -> Ascii ERROR.");

        return VOS_FALSE;
    }

    pucEmcNumsNoUsim    = TAF_SDC_GetCallEmerNumsNoUsimTblAddr();
    pucEmcNumsWithUsim  = TAF_SDC_GetCallEmerNumsWithUsimTblAddr();

    if (TAF_SDC_USIM_STATUS_NO_PRESENT == TAF_SDC_GetSimStatus())
    {
        for (ulLoop = 0; ulLoop < TAF_SDC_NUMOF_EMER_NUMS_NO_USIM; ulLoop++)
        {
            if (0 == VOS_StrCmp(pucEmcNumsNoUsim[ulLoop], (VOS_CHAR *)acCalledNum))
            {
                return VOS_TRUE;
            }
        }
    }
    else
    {

        /* 有卡时检查手机中存储的紧急呼叫号码 */
        for (ulLoop = 0; ulLoop < TAF_SDC_NUMOF_EMER_NUMS_WITH_USIM; ulLoop++ )
        {
            if (0 == VOS_StrCmp(pucEmcNumsWithUsim[ulLoop], (VOS_CHAR *)acCalledNum))
            {
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_IsUsimEmergencyNum
 功能描述  : 检查当前号码是否属于USIM卡中的紧急呼叫号码
 输入参数  : pucCalledNum       - 号码
 输出参数  : pulEmcCatExist     - Emergency Category是否合法
             pucEmerCategory    - Emergency Category合法才有效,pucEmerCategory的值
 返 回 值  : VOS_TRUE: 是USIM卡中的紧急呼叫号码
             VOS_FALSE:不是USIM卡中的紧急呼叫号码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月31日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  TAF_SPM_IsUsimEmergencyNum(
    MN_CALL_CALLED_NUM_STRU            *pstDialNum,
    VOS_UINT32                         *pulEmcCatExist,
    VOS_UINT8                          *pucEmerCategory
)
{
    SI_PB_ECC_DATA_STRU                *pstEccData = VOS_NULL_PTR;
    VOS_INT8                            acUsimCalledNum[MN_CALL_MAX_ASCII_NUM_LEN + 1];
    VOS_INT8                            acCalledNum[MN_CALL_MAX_CALLED_ASCII_NUM_LEN + 1];
    MN_CALL_TYPE_ENUM_U8                enCallType;
    VOS_UINT32                          i;

    enCallType  = MN_CALL_TYPE_VOICE;

    /* 获取USIM中的紧急呼叫号码 */
    pstEccData = (SI_PB_ECC_DATA_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(SI_PB_ECC_DATA_STRU));

    if (VOS_NULL_PTR == pstEccData)
    {
        MN_WARN_LOG("TAF_SPM_IsUsimEmergencyNum: Alloc Mem Fail.");

        return VOS_FALSE;
    }

    /* 号码转换 BCD-> Ascii */
    if (MN_ERR_NO_ERROR != TAF_STD_ConvertBcdNumberToAscii(pstDialNum->aucBcdNum,
                                                           pstDialNum->ucNumLen,
                                                           (VOS_CHAR *)acCalledNum))
    {
        MN_WARN_LOG("TAF_SPM_IsUsimEmergencyNum: BCD -> Ascii ERROR.");

        PS_MEM_FREE(WUEPS_PID_TAF, pstEccData);

        return VOS_FALSE;
    }

    PS_MEM_SET(pstEccData, 0, sizeof(SI_PB_ECC_DATA_STRU));
    NAS_PBAPI_GetEccNumber(pstEccData);

    /* 比较号码是否是EFECC文件中的紧急呼叫号码 */
    for (i = 0; i< pstEccData->ulReocrdNum; i++)
    {
        PS_MEM_SET(acUsimCalledNum,0,MN_CALL_MAX_ASCII_NUM_LEN + 1);

        if (MN_ERR_NO_ERROR != TAF_STD_ConvertBcdNumberToAscii(pstEccData->astEccRecord[i].aucEccCode,
                                                               USIM_ECC_LEN,
                                                               (VOS_CHAR *)acUsimCalledNum))
        {
            MN_INFO_LOG("TAF_SPM_IsUsimEmergencyNum: TAF_STD_ConvertBcdNumberToAscii fail");
        }

        if (0 == VOS_StrCmp((VOS_CHAR *)acUsimCalledNum, (VOS_CHAR *)acCalledNum))
        {
            enCallType = MN_CALL_TYPE_EMERGENCY;
            MN_INFO_LOG("TAF_SPM_IsUsimEmergencyNum: get card Ecc change to emergency");
            break;
        }
    }

    /* 当前是紧急呼叫号码则判断号码类型是否有效 */
    if (MN_CALL_TYPE_EMERGENCY == enCallType)
    {
        if (VOS_TRUE == pstEccData->astEccRecord[i].bESC)
        {
            *pulEmcCatExist = TAF_STD_IsValidEmerCategory(pstEccData->astEccRecord[i].ucESC);
        }

        if (VOS_TRUE == *pulEmcCatExist)
        {
            *pucEmerCategory = (pstEccData->astEccRecord[i].ucESC & MN_CALL_EMER_CATEGORG_VAL_MAX);
        }

        PS_MEM_FREE(WUEPS_PID_TAF, pstEccData);

        return VOS_TRUE;
    }

    PS_MEM_FREE(WUEPS_PID_TAF, pstEccData);

    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : TAF_SPM_IsPhoneEmergencyNum_CDMA
 功能描述  : 判断呼叫号码是否中国电信预置的紧急呼号码
 输入参数  : pstDialNum------被叫号码
 输出参数  : 无
 返 回 值  : VOS_TRUE   :是紧急呼叫号码
             VOS_FALSE  :不是紧急呼叫号码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年02月03日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_IsPhoneEmergencyNum_CDMA(
    MN_CALL_CALLED_NUM_STRU            *pstDialNum
)
{
    VOS_UINT32                          i;
    VOS_CHAR                            acCalledNum[MN_CALL_MAX_CALLED_ASCII_NUM_LEN + 1];
    VOS_CHAR                          **pacCdmaEmcNumList   = VOS_NULL_PTR;

    PS_MEM_SET(acCalledNum, 0x00, sizeof(acCalledNum));
    pacCdmaEmcNumList                   = TAF_SDC_GetCdmaCallEmcNumsAddr();

    /* 号码转换 BCD-> Ascii */
    if (MN_ERR_NO_ERROR != TAF_STD_ConvertBcdNumberToAscii(pstDialNum->aucBcdNum,
                                                           pstDialNum->ucNumLen,
                                                           acCalledNum))
    {
        MN_WARN_LOG("TAF_SPM_IsPhoneEmergencyNum_CDMA: BCD -> Ascii ERROR.");

        return VOS_FALSE;
    }

    for (i = 0; i < TAF_SDC_NUMOF_CDMA_PRESET_EMC_NUM; i++)
    {
        if (0 == VOS_StrCmp(pacCdmaEmcNumList[i], acCalledNum))
        {
            MN_INFO_LOG("TAF_SPM_IsPhoneEmergencyNum_CDMA: EMC NUM!.");

            return VOS_TRUE;
        }
    }

    MN_INFO_LOG("TAF_SPM_IsPhoneEmergencyNum_CDMA: NOT EMC NUM!.");

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_IsUcimEmergencyNum_CDMA
 功能描述  : 检查当前号码是否属于USIM卡中的紧急呼叫号码
 输入参数  : pucCalledNum       - 号码
 输出参数  : 无
 返 回 值  : VOS_TRUE: 是UCIM卡中的紧急呼叫号码
             VOS_FALSE:不是UCIM卡中的紧急呼叫号码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月29日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  TAF_SPM_IsUsimEmergencyNum_CDMA(
    MN_CALL_CALLED_NUM_STRU            *pstDialNum,
    VOS_UINT32                         *pulEmcCatExist,
    VOS_UINT8                          *pucEmerCategory
)
{
    SI_PB_ECC_DATA_STRU                *pstEccData = VOS_NULL_PTR;
    VOS_INT8                            acUsimCalledNum[MN_CALL_MAX_ASCII_NUM_LEN + 1];
    VOS_INT8                            acCalledNum[MN_CALL_MAX_CALLED_ASCII_NUM_LEN + 1];
    MN_CALL_TYPE_ENUM_U8                enCallType;
    VOS_UINT32                          i;

    enCallType  = MN_CALL_TYPE_VOICE;

    /* 获取USIM中的紧急呼叫号码 */
    pstEccData = (SI_PB_ECC_DATA_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(SI_PB_ECC_DATA_STRU));

    if (VOS_NULL_PTR == pstEccData)
    {
        MN_WARN_LOG("TAF_SPM_IsUsimEmergencyNum: Alloc Mem Fail.");

        return VOS_FALSE;
    }

    /* 号码转换 BCD-> Ascii */
    if (MN_ERR_NO_ERROR != TAF_STD_ConvertBcdNumberToAscii(pstDialNum->aucBcdNum,
                                                           pstDialNum->ucNumLen,
                                                           (VOS_CHAR *)acCalledNum))
    {
        MN_WARN_LOG("TAF_SPM_IsUsimEmergencyNum: BCD -> Ascii ERROR.");

        PS_MEM_FREE(WUEPS_PID_TAF, pstEccData);

        return VOS_FALSE;
    }

    PS_MEM_SET(pstEccData, 0, sizeof(SI_PB_ECC_DATA_STRU));
    NAS_PBAPI_GetXeccNumber(pstEccData);

    /* 比较号码是否是EFECC文件中的紧急呼叫号码 */
    for (i = 0; i< pstEccData->ulReocrdNum; i++)
    {
        PS_MEM_SET(acUsimCalledNum,0,MN_CALL_MAX_ASCII_NUM_LEN + 1);

        if (MN_ERR_NO_ERROR != TAF_STD_ConvertBcdNumberToAscii(pstEccData->astEccRecord[i].aucEccCode,
                                                               USIM_ECC_LEN,
                                                               (VOS_CHAR *)acUsimCalledNum))
        {
            MN_INFO_LOG("TAF_SPM_IsUsimEmergencyNum: TAF_STD_ConvertBcdNumberToAscii fail");
        }

        if (0 == VOS_StrCmp((VOS_CHAR *)acUsimCalledNum, (VOS_CHAR *)acCalledNum))
        {
            enCallType = MN_CALL_TYPE_EMERGENCY;
            MN_INFO_LOG("TAF_SPM_IsUsimEmergencyNum: get card Ecc change to emergency");
            break;
        }
    }

    /* 当前是紧急呼叫号码则判断号码类型是否有效 */
    if (MN_CALL_TYPE_EMERGENCY == enCallType)
    {
        if (VOS_TRUE == pstEccData->astEccRecord[i].bESC)
        {
            *pulEmcCatExist = TAF_STD_IsValidEmerCategory(pstEccData->astEccRecord[i].ucESC);
        }

        if (VOS_TRUE == *pulEmcCatExist)
        {
            *pucEmerCategory = (pstEccData->astEccRecord[i].ucESC & MN_CALL_EMER_CATEGORG_VAL_MAX);
        }

        PS_MEM_FREE(WUEPS_PID_TAF, pstEccData);

        return VOS_TRUE;
    }

    PS_MEM_FREE(WUEPS_PID_TAF, pstEccData);

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_IsEmergencyNum_CDMA
 功能描述  : CDMA下检查当前号码是否属于紧急呼叫号码
 输入参数  : pucCalledNum       - 号码
 输出参数  : 无
的值
 返 回 值  : VOS_TRUE   :是紧急呼叫号码
             VOS_FALSE  :不是紧急呼叫号码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月29日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  TAF_SPM_IsEmergencyNum_CDMA(
    MN_CALL_CALLED_NUM_STRU            *pstDialNum,
    VOS_UINT32                         *pulEmcCatExist,
    VOS_UINT8                          *pucEmerCategory
)
{
    MN_CALL_EMERGENCY_CAT_STRU          stEmergencyCat;
    VOS_INT8                            aucCalledNum[MN_CALL_MAX_CALLED_ASCII_NUM_LEN + 1];


    PS_MEM_SET(aucCalledNum, 0x00, sizeof(aucCalledNum));

    /* 1X下面紧急呼叫号码的判定只来源于UIM/CSIM卡文件中,至于定制的ECC号码以后可添加
       目前只判定卡文件中的号码以及协议定制的号码 */

    /* 检查是否(U)SIM卡中EFECC文件中的紧急呼叫号码 */
    if (TAF_SDC_USIM_STATUS_NO_PRESENT != TAF_SDC_GetCsimStatus())
    {
        /* 由于目前看来现网卡的6F47文件都没有ECC号码,因此如果在卡中找不到
           紧急呼叫号码继续看下本地定义的紧急呼叫号码 */
        if (VOS_TRUE == TAF_SPM_IsUsimEmergencyNum_CDMA(pstDialNum,
                                                        pulEmcCatExist,
                                                        pucEmerCategory))
        {
            return VOS_TRUE;
        }
    }

    if (VOS_TRUE == TAF_SPM_IsAppCustomEmergencyNum(pstDialNum,
                                                    &stEmergencyCat.bExist,
                                                    &stEmergencyCat.ucEmergencyCat))
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == TAF_SPM_IsPhoneEmergencyNum_CDMA(pstDialNum))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
#endif


/*****************************************************************************
 函 数 名  : TAF_SPM_IsEmergencyNum
 功能描述  : 检查当前号码是否属于紧急呼叫号码
 输入参数  : pucCalledNum       - 号码
             ulCheckEfecc       - 是否检查(U)SIM的EFECC文件
 输出参数  : pucEmerCategory    - Emergency Category合法才有效,pucEmerCategory
的值
 返 回 值  : VOS_TRUE   :是紧急呼叫号码
             VOS_FALSE  :不是紧急呼叫号码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月31日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2014年03月03日
    作    者   : y00245242
    修改内容   : dts2014030404097，处理emergency call category不存在时流程
  3.日    期   : 2014年11月17日
    作    者   : w00176964
    修改内容   : CDMA 1x项目迭代5修改
*****************************************************************************/
VOS_UINT32  TAF_SPM_IsEmergencyNum(
    MN_CALL_CALLED_NUM_STRU            *pstDialNum,
    VOS_UINT32                          ulCheckEfecc,
    MN_CALL_EMERGENCY_CAT_STRU         *pstEmergencyCat
)
{
    VOS_UINT8                           ucEmergencyCall;

    ucEmergencyCall = VOS_FALSE;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* CDMA inside，并且当前是CL模式 */
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        /* 判断1X下面紧急呼叫号码 */
        if (VOS_TRUE == TAF_SPM_IsEmergencyNum_CDMA(pstDialNum,
                                                    &pstEmergencyCat->bExist,
                                                    &pstEmergencyCat->ucEmergencyCat))
        {
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }
#endif

    /* 检查是否(U)SIM卡中EFECC文件中的紧急呼叫号码 */
    if (TAF_SDC_USIM_STATUS_NO_PRESENT != TAF_SDC_GetUsimStatus())
    {
        if (VOS_TRUE == ulCheckEfecc)
        {
            if (VOS_TRUE == TAF_SPM_IsUsimEmergencyNum(pstDialNum,
                                                        &pstEmergencyCat->bExist,
                                                        &pstEmergencyCat->ucEmergencyCat))
            {
                /* 是USIM中的紧急呼叫,且CATEGORY有效则直接返回 */
                if (VOS_TRUE  == pstEmergencyCat->bExist)
                {
                    return VOS_TRUE;
                }

                ucEmergencyCall = VOS_TRUE;
            }
        }

        /* 检查是否网络上报紧急呼叫号码列表中的紧急呼叫号码 */
        if (VOS_TRUE == TAF_SPM_IsNetworkEmergencyNum(pstDialNum,
                                                      &pstEmergencyCat->bExist,
                                                      &pstEmergencyCat->ucEmergencyCat))
        {
            /* 是网络中的紧急呼叫,且CATEGORY有效则直接返回 */
            if (VOS_TRUE == pstEmergencyCat->bExist)
            {
                return VOS_TRUE;
            }

            ucEmergencyCall = VOS_TRUE;

        }
    }

    /* 检查是否运营商定制紧急呼叫号码列表中的紧急呼叫号码 */
    if (VOS_TRUE == TAF_SPM_IsAppCustomEmergencyNum(pstDialNum,
                                                    &pstEmergencyCat->bExist,
                                                    &pstEmergencyCat->ucEmergencyCat))
    {
        /* 是网络中的紧急呼叫,且CATEGORY有效则直接返回 */
        if (VOS_TRUE == pstEmergencyCat->bExist)
        {
            return VOS_TRUE;
        }

        ucEmergencyCall = VOS_TRUE;
    }

    /* 检查是否协议定义的紧急呼叫号码 */
    if (VOS_TRUE == TAF_SPM_IsPhoneEmergencyNum(pstDialNum))
    {
        ucEmergencyCall = VOS_TRUE;
    }

    if (VOS_TRUE == ucEmergencyCall)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetBcCallType
 功能描述  : 获取BC指示的呼叫类型
 输入参数  : VOS_UINT32                          ulExistBc      BC参数是否存在
             VOS_UINT32                          ulBcLength     BC参数长度
             VOS_UINT8                          *pucBc          BC参数
 输出参数  : MN_CALL_TYPE_ENUM_U8               *penCallType    根据BC修改后的呼叫类型
 返 回 值  : VOS_UINT32
                TAF_CS_CAUSE_SUCCESS        检查通过
                其他，UE不支持的呼叫类型
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月20日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_GetBcCallType(
    VOS_UINT32                          ulExistBc,
    VOS_UINT32                          ulBcLength,
    VOS_UINT8                          *pucBc,
    MN_CALL_TYPE_ENUM_U8               *penCallType
)
{
    TAF_CALL_BC_STRU                    stBc1;

    /* 紧急呼叫不修改呼叫类型 */
    if (MN_CALL_TYPE_EMERGENCY == *penCallType)
    {
        return VOS_TRUE;
    }

    /* BC不存在不修改呼叫类型 */
    if (VOS_TRUE != ulExistBc)
    {
        return VOS_TRUE;
    }
    else
    {
        PS_MEM_SET(&stBc1, 0, sizeof(stBc1));
        stBc1.ulLength = ulBcLength;
        PS_MEM_CPY(&stBc1.Octet3, pucBc, stBc1.ulLength);
    }

    /* 获取新的BC是指示的呼叫类型 */
    if (VOS_OK != MN_CALL_JudgeMtCallType(&stBc1.Octet3, &stBc1.Octet5a, penCallType))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_SPM_IsUsimServiceAvailable
 功能描述  : 检查卡的服务状态是否可用

 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SPM_USIM_NO_ERROR:           (U)SIM状态正常
             TAF_SPM_USIM_NEED_PIN1:          需要PIN1码
             TAF_SPM_USIM_NEED_PUK1:          需要PUK1码
             TAF_SPM_USIM_PIN1_FAIL:          PIN1失败
             TAF_SPM_USIM_OTHER_FAIL:         其他失败
             TAF_SPM_USIM_NOT_EXIST:          卡不存在

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月18日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2014年2月27日
   作    者   : z00234330
   修改内容   : dts2014022402558,sim被puk锁定时,usim模块上报的invalid,usim没有上报
                卡状态在位时,sdc默认为卡invalid,这两种情况需要区分一下,否则使用
                at^cpin命令查询的会不正确。
*****************************************************************************/
VOS_UINT32 TAF_SPM_IsUsimServiceAvailable(VOS_VOID)
{

    TAF_SDC_USIM_STATUS_ENUM_UINT8      enUsimStatus;

    enUsimStatus = TAF_SDC_GetSimStatus();

    return TAF_SPM_IsSimServiceAvailable(enUsimStatus);
}


/*****************************************************************************
 函 数 名  : TAF_SPM_GetServiceRequestType
 功能描述  : 根据应用消息请求判断是否为USSD业务
 输入参数  : ulEventType -- 业务请求消息的event type
 输出参数  : 无
 返 回 值  : VOS_TRUE:是USSD业务
             VOS_FALSE:不是USSD业务
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月14日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_IsUssdServiceType(
    VOS_UINT32                          ulEventType
)
{
    VOS_UINT32                          ulResult;

    ulResult  = VOS_FALSE;

    switch (ulEventType)
    {
        case TAF_BuildEventType(WUEPS_PID_AT, TAF_MSG_PROCESS_USS_MSG):
        case TAF_BuildEventType(MAPS_STK_PID, STK_SS_USSD_REQ):

            ulResult = VOS_TRUE;
            break;

        default:

            break;
    }

    return ulResult;
}


/*****************************************************************************
 函 数 名  : TAF_SPM_GetServiceRequestTypeWithAtClient
 功能描述  : 根据AT消息请求，返回业务请求类型

 输入参数  : pstMsg -- 业务请求消息类型
 输出参数  : 无
 返 回 值  : 返回请求消息的业务类型
             TAF_SPM_SRV_REQ_TYPE_CALL －－ 呼叫控制业务请求类型
             TAF_SPM_SRV_REQ_TYPE_SMS －－ 短信业务请求类型
             TAF_SPM_SRV_REQ_TYPE_SS －－ 补充业务请求类型
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月09日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8 TAF_SPM_GetServiceRequestTypeWithAtClient(
    struct MsgCB                       *pstMsg
)
{
    MN_APP_REQ_MSG_STRU                *pstAppMsg = VOS_NULL_PTR;
    TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8     enSrvReqType;

    pstAppMsg = (MN_APP_REQ_MSG_STRU *)pstMsg;

    enSrvReqType = TAF_SPM_SRV_REQ_TYPE_BUTT;

    switch (pstAppMsg->usMsgName & MN_APP_MSG_CLASS_MASK)
    {
        /* call service request */
        case MN_APP_MSG_CLASS_CALL:
            enSrvReqType = TAF_SPM_SRV_REQ_TYPE_CALL;
            break;

        /* SMS service request */
        case MN_APP_MSG_CLASS_MSG:
            enSrvReqType = TAF_SPM_SRV_REQ_TYPE_SMS;
            break;

        /* SS service request */
        case MN_APP_MSG_CLASS_SSA:
            enSrvReqType = TAF_SPM_SRV_REQ_TYPE_SS;
            break;

        default:
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SPM_GetServiceRequestTypeWithAtClient: unknown message is received from AT!");
            break;
    }

    return enSrvReqType;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetServiceRequestTypeWithStkClient
 功能描述  : 根据STK消息请求，返回业务请求类型

 输入参数  : pstMsg -- 业务请求消息类型
 输出参数  : 无
 返 回 值  : 返回请求消息的业务类型
             TAF_SPM_SRV_REQ_TYPE_CALL －－ 呼叫控制业务请求类型
             TAF_SPM_SRV_REQ_TYPE_SMS －－ 短信业务请求类型
             TAF_SPM_SRV_REQ_TYPE_SS －－ 补充业务请求类型
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月09日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8 TAF_SPM_GetServiceRequestTypeWithStkClient(
    struct MsgCB                       *pstMsg
)
{
    MN_APP_REQ_MSG_STRU                *pstAppMsg = VOS_NULL_PTR;
    TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8     enSrvReqType;

    pstAppMsg = (MN_APP_REQ_MSG_STRU *)pstMsg;

    enSrvReqType = TAF_SPM_SRV_REQ_TYPE_BUTT;

    switch (pstAppMsg->usMsgName)
    {
        /* STK call service request */
        case STK_CALL_CALLORIG_REQ:
        case STK_CALL_SUPS_CMD_REQ:
        case STK_CALL_START_DTMF_REQ:
        case STK_CALL_STOP_DTMF_REQ:
            enSrvReqType = TAF_SPM_SRV_REQ_TYPE_CALL;
            break;

        /* STK SMS service request */
        case STK_MSG_SEND_REQ:
            enSrvReqType = TAF_SPM_SRV_REQ_TYPE_SMS;
            break;

        /* STK SS service request */
        case STK_SS_REGISTERSS_REQ:
        case STK_SS_ERASESS_REQ:
        case STK_SS_ACTIVATESS_REQ:
        case STK_SS_DEACTIVATESS_REQ:
        case STK_SS_INTERROGATESS_REQ:
        case STK_SS_USSD_REQ:
            enSrvReqType = TAF_SPM_SRV_REQ_TYPE_SS;
            break;

        default:
            TAF_ERROR_LOG(WUEPS_PID_TAF,
                          "TAF_SPM_GetServiceRequestTypeWithStkClient: unknown message is received from STK!");

            break;
    }

    return enSrvReqType;
}

/* Added by s00217060 for VoLTE_PhaseIII  项目, 2014-01-06, begin */
/*****************************************************************************
 函 数 名  : TAF_SPM_GetServiceRequestTypeWithTafClient
 功能描述  : 根据TAF消息请求，返回业务请求类型

 输入参数  : pstMsg -- 业务请求消息类型
 输出参数  : 无
 返 回 值  : 返回请求消息的业务类型
             TAF_SPM_SRV_REQ_TYPE_CALL －－ 呼叫控制业务请求类型
             TAF_SPM_SRV_REQ_TYPE_SMS －－ 短信业务请求类型
             TAF_SPM_SRV_REQ_TYPE_SS －－ 补充业务请求类型
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年01月06日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8 TAF_SPM_GetServiceRequestTypeWithTafClient(
    struct MsgCB                       *pstMsg
)
{
    TAF_INTERNAL_MSG_STRU              *pstTafMsg = VOS_NULL_PTR;
    TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8     enSrvReqType;

    pstTafMsg = (TAF_INTERNAL_MSG_STRU *)pstMsg;

    enSrvReqType = TAF_SPM_SRV_REQ_TYPE_BUTT;

    switch (pstTafMsg->ulMsgId)
    {
        /* ID_TAF_SPM_SMMA_IND */
        case ID_TAF_SPM_SMMA_IND:
            enSrvReqType = TAF_SPM_SRV_REQ_TYPE_SMS;
            break;

        default:
            TAF_ERROR_LOG(WUEPS_PID_TAF,
                          "TAF_SPM_GetServiceRequestTypeWithTafClient: unknown message is received from TAF!");

            break;
    }

    return enSrvReqType;
}
/* Added by s00217060 for VoLTE_PhaseIII  项目, 2014-01-06, end */


/*****************************************************************************
 函 数 名  : TAF_SPM_GetServiceRequestType
 功能描述  : 根据应用消息请求，返回业务请求类型。

 输入参数  : pstMsg -- 业务请求消息类型
 输出参数  : 无
 返 回 值  : 返回请求消息的业务类型
             TAF_SPM_SRV_REQ_TYPE_CALL －－ 呼叫控制业务请求类型
             TAF_SPM_SRV_REQ_TYPE_SMS －－ 短信业务请求类型
             TAF_SPM_SRV_REQ_TYPE_SS  －－ 补充业务请求类型
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8 TAF_SPM_GetServiceRequestType(
    struct MsgCB                       *pstMsg
)
{
    MN_APP_REQ_MSG_STRU                *pstAppMsg = VOS_NULL_PTR;
    TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8     enSrvReqType;

    pstAppMsg = (MN_APP_REQ_MSG_STRU *)pstMsg;

    enSrvReqType = TAF_SPM_SRV_REQ_TYPE_BUTT;

    /* messages from AT */
    if (WUEPS_PID_AT == (pstAppMsg->ulSenderPid))
    {
        enSrvReqType = TAF_SPM_GetServiceRequestTypeWithAtClient(pstMsg);
    }
    /* messages from STK */
    else if (MAPS_STK_PID == (pstAppMsg->ulSenderPid))
    {
        enSrvReqType = TAF_SPM_GetServiceRequestTypeWithStkClient(pstMsg);
    }
    /* other messages */
    else if (WUEPS_PID_TAF == (pstAppMsg->ulSenderPid))
    {
        enSrvReqType = TAF_SPM_GetServiceRequestTypeWithTafClient(pstMsg);
    }
    else
    {
        /* nothing to do */
    }

    return (enSrvReqType);
}


#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 函 数 名  : TAF_SPM_SendTafAgentGetCallInfoCnf
 功能描述  : 给TAFAGENT发送查询呼叫信息回复
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月18日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SPM_SendTafAgentGetCallInfoCnf(
    IMSA_SPM_CALL_GET_CALL_INFO_CNF_STRU    *pstImsaMsg
)
{
    TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU *pstCnf = VOS_NULL_PTR;
    VOS_UINT32                           i;

    pstCnf = (TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,
                                                                sizeof(TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstCnf)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SPM_SendTafAgentGetCallInfoCnf:alloc msg failed.");
        return;
    }

    PS_MEM_SET(pstCnf, 0x00, sizeof(TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU));

    /* 填写消息内容 */
    pstCnf->ulSenderCpuId                 = VOS_LOCAL_CPUID;
    pstCnf->ulSenderPid                   = WUEPS_PID_TAF;
    pstCnf->ulReceiverCpuId               = VOS_LOCAL_CPUID;
    pstCnf->ulReceiverPid                 = ACPU_PID_TAFAGENT;
    pstCnf->ulLength                      = sizeof(TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstCnf->enMsgId                       = ID_TAFAGENT_MN_GET_CALL_INFO_CNF;
    pstCnf->ucNumOfCalls                  = pstImsaMsg->ucNumOfCalls;

    /* IMSA消息中带的信息比较多，回复给TAFAGENT时，只需要callId,enCallType,enCallState */
    for (i = 0; i < pstImsaMsg->ucNumOfCalls; i++)
    {
        pstCnf->stCallInfo[i].callId       = pstImsaMsg->astCallInfo[i].callId;
        pstCnf->stCallInfo[i].enCallType   = pstImsaMsg->astCallInfo[i].enCallType;
        pstCnf->stCallInfo[i].enCallState  = pstImsaMsg->astCallInfo[i].enCallState;

    }

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstCnf))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SPM_SendTafAgentGetCallInfoCnf:send msg failed.");

    }

    return;

}

/*****************************************************************************
 函 数 名  : TAF_SPM_SendAtGetCallInfoCnf
 功能描述  : 给AT发送查询呼叫信息回复
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月18日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SPM_SendAtGetCallInfoCnf(
    IMSA_SPM_CALL_GET_CALL_INFO_CNF_STRU    *pstImsaMsg
)
{
    MN_CALL_INFO_QRY_CNF_STRU           stAppCnfMsg;
    VOS_UINT16                          usLength;

    /* 构造一条消息，给AT回复 */
    PS_MEM_SET(&stAppCnfMsg, 0x00, sizeof(MN_CALL_INFO_QRY_CNF_STRU));

    /* 填写事件名称 */
    stAppCnfMsg.enEvent         = MN_CALL_EVT_CLCC_INFO;
    stAppCnfMsg.clientId        = MN_GetRealClientId(pstImsaMsg->usClientId, WUEPS_PID_TAF);
    stAppCnfMsg.ucNumOfCalls    = pstImsaMsg->ucNumOfCalls;

    PS_MEM_CPY(stAppCnfMsg.astCallInfos,
               pstImsaMsg->astCallInfo,
               sizeof(MN_CALL_INFO_PARAM_STRU)*(stAppCnfMsg.ucNumOfCalls));

    /* 确定消息长度 */
    usLength = (VOS_UINT16)sizeof(MN_CALL_INFO_QRY_CNF_STRU);

    /* 通过异步消息发送给AT */
    MN_SendReportMsg(MN_CALLBACK_CS_CALL, (TAF_UINT8 *)&stAppCnfMsg, usLength);

    return;

}

/*****************************************************************************
 函 数 名  : TAF_SPM_SendAtGetEconfCallInfoCnf
 功能描述  : 给AT发送增强型多方通话查询呼叫信息回复
 输入参数  : pstImsaMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月28日
    作    者   : j00174725
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SPM_SendAtGetEconfCallInfoCnf(
    IMSA_SPM_CALL_GET_ECONF_CALLED_INFO_CNF_STRU   *pstImsaMsg
)
{
    TAF_CALL_ECONF_INFO_QRY_CNF_STRU   *pstImsaCnfMsg;
    VOS_UINT16                          usLength;

    pstImsaCnfMsg = (TAF_CALL_ECONF_INFO_QRY_CNF_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF,  sizeof(TAF_CALL_ECONF_INFO_QRY_CNF_STRU));
    if (VOS_NULL_PTR == pstImsaCnfMsg)
    {
        return;
    }
    /* 构造一条消息，给AT回复 */
    PS_MEM_SET((VOS_VOID *)pstImsaCnfMsg, 0x00, sizeof(TAF_CALL_ECONF_INFO_QRY_CNF_STRU));

    /* 填写事件名称 */
    pstImsaCnfMsg->enEvent            = TAF_CALL_EVT_CLCCECONF_INFO;
    pstImsaCnfMsg->usClientId         = MN_GetRealClientId(pstImsaMsg->usClientId, WUEPS_PID_TAF);
    pstImsaCnfMsg->ucNumOfMaxCalls    = pstImsaMsg->ucNumOfMaxCalls;
    pstImsaCnfMsg->ucNumOfCalls       = pstImsaMsg->ucNumOfCalls;

    PS_MEM_CPY(pstImsaCnfMsg->astCallInfo,
               pstImsaMsg->astCallInfo,
               sizeof(TAF_CALL_ECONF_INFO_PARAM_STRU) * (pstImsaMsg->ucNumOfCalls));

    /* 确定消息长度 */
    usLength = (VOS_UINT16)sizeof(TAF_CALL_ECONF_INFO_QRY_CNF_STRU);

    /* 通过异步消息发送给AT */
    MN_SendReportMsg(MN_CALLBACK_CS_CALL, (VOS_UINT8 *)pstImsaCnfMsg, usLength);

    PS_MEM_FREE(WUEPS_PID_TAF, pstImsaCnfMsg);

    return;

}
#endif

/*****************************************************************************
 函 数 名  : TAF_SPM_GetCallInfoFromFsmEntryMsg
 功能描述  : 从状态机入口消息中获取呼叫相关信息
 输入参数  : 无
 输出参数  : pstDialNumber:呼叫号码
             penCallType  :呼叫类型
             penCallMode  :呼叫模式
             pstDataCfg   :呼叫数据配置信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月16日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_GetCallInfoFromFsmEntryMsg(
    MN_CALL_CALLED_NUM_STRU            *pstDialNumber,
    MN_CALL_TYPE_ENUM_U8               *penCallType,
    MN_CALL_MODE_ENUM_U8               *penCallMode,
    MN_CALL_CS_DATA_CFG_STRU           *pstDataCfg
)
{
    MN_APP_REQ_MSG_STRU                *pstAppMsg       = VOS_NULL_PTR;
    MN_APP_CALL_CALLORIG_REQ_STRU      *pstStkOrigParam = VOS_NULL_PTR;
    TAF_SPM_ENTRY_MSG_STRU             *pstEntryMsg     = VOS_NULL_PTR;
    MN_CALL_APP_REQ_PARM_UNION         *pstAtOrigParam  = VOS_NULL_PTR;
    NAS_CC_IE_BC_STRU                   stBc1CallCnf;

    pstEntryMsg     = TAF_SPM_GetCurrEntityFsmEntryMsgAddr();
    pstAppMsg       = (MN_APP_REQ_MSG_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* 区分AT或STK的 */
    if (WUEPS_PID_AT == TAF_SPM_GetCurrEntityFsmEntryMsgSndPid())
    {
        pstAtOrigParam  = (MN_CALL_APP_REQ_PARM_UNION *)pstAppMsg->aucContent;

        *penCallType    = pstAtOrigParam->stOrig.enCallType;
        *penCallMode    = pstAtOrigParam->stOrig.enCallMode;

        PS_MEM_CPY(pstDialNumber, &pstAtOrigParam->stOrig.stDialNumber, sizeof(pstAtOrigParam->stOrig.stDialNumber));
        PS_MEM_CPY(pstDataCfg, &pstAtOrigParam->stOrig.stDataCfg, sizeof(pstAtOrigParam->stOrig.stDataCfg));
    }
    else
    {
        pstStkOrigParam = (MN_APP_CALL_CALLORIG_REQ_STRU *)pstAppMsg;

        *penCallType    = pstStkOrigParam->enCallType;
        *penCallMode    = MN_CALL_MODE_SINGLE;

        PS_MEM_CPY(pstDialNumber, (MN_CALL_CALLED_NUM_STRU *)&pstStkOrigParam->stCalledAddr, sizeof(pstStkOrigParam->stCalledAddr));

        stBc1CallCnf.IsExist        = VOS_TRUE;
        stBc1CallCnf.LastOctOffset  = (VOS_UINT8)pstStkOrigParam->stBc.ucLen;
        PS_MEM_CPY(&stBc1CallCnf.Octet3, pstStkOrigParam->stBc.aucBc, pstStkOrigParam->stBc.ucLen);

        MN_CALL_GetDataCfgInfoFromBc(&stBc1CallCnf, (MN_CALL_CS_DATA_CFG_INFO_STRU *)pstDataCfg);
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_SPM_IsNeedCheckFdn
 功能描述  : 判断是否需要做FDN检查
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_FALSE           不要求FDN检查
             VOS_TRUE            要求FDN检查
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年02月23日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数
  2.日    期   : 2013年05月13日
    作    者   : w00176964
    修改内容   : FDN检查函数位置、命名统一调整
  3.日    期   : 2013年6月5日
    作    者   : z00161729
    修改内容   : SVLTE 和usim接口调整修改
*****************************************************************************/
VOS_UINT32 TAF_SPM_IsNeedCheckFdn()
{
    TAF_SPM_SERVICE_CTRL_CFG_INFO_STRU *pstServiceCtrlCfgInfo = VOS_NULL_PTR;

    VOS_UINT32                          ulUsimFdnStatus;
    VOS_UINT32                          ulCsimFdnStatus;

    ulUsimFdnStatus         = 0;
    ulCsimFdnStatus         = 0;
    pstServiceCtrlCfgInfo   = TAF_SPM_GetServiceCtrlCfgInfoAddr();

    /* ME没有启用FDN检查功能，直接返回业务检查通过 */
    if (TAF_FDN_CHECK_FEATURE_ON != pstServiceCtrlCfgInfo->ulMeStatus)
    {
        return VOS_FALSE;
    }

    /*
    根据(U)SIM卡的FDN状态确定是否发起FDN检查
       0 去使能: 不做FDN检查
       1 使能:   做FDN检查
    */
    NAS_USIMMAPI_FdnQuery(&ulUsimFdnStatus, &ulCsimFdnStatus);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        return ulCsimFdnStatus;
    }
    else
#endif
    {
        return ulUsimFdnStatus;
    }

}

/*****************************************************************************
 函 数 名  : TAF_SPM_IsNeedCallControl
 功能描述  : 判断是否需要发起CALL CONTROL流程
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_FALSE           不要求CALL CONTROL检查
             VOS_TRUE            要求CALL CONTROL检查
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月20日
    作    者   : f62575
    修改内容   : 新生成函数
  2.日    期   : 2013年5月14日
    作    者   : w00176964
    修改内容   : CALL CONTROL检查函数位置、命名统一调整
  3.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : svlte和usim接口调整
  4.日    期   : 2013年7月29日
    作    者   : y00245242
    修改内容   : 适配新的USIM接口

*****************************************************************************/
VOS_UINT32 TAF_SPM_IsNeedCallControl(VOS_VOID)
{
    TAF_SPM_SERVICE_CTRL_CFG_INFO_STRU *pstServiceCtrlCfgInfo = VOS_NULL_PTR;

    pstServiceCtrlCfgInfo   = TAF_SPM_GetServiceCtrlCfgInfoAddr();

    /* ME没有启用CALL CONTROL检查功能，直接返回业务检查通过 */
    if (VOS_FALSE == pstServiceCtrlCfgInfo->ucSimCallCtrlSupportFlg)
    {
        return VOS_FALSE;
    }

    /*
    根据(U)SIM卡的CALL CONTROL状态确定是否发起CALL CONTROL检查
       0 去使能: 不做CALL CONTROL检查
       1 使能:   做CALL CONTROL检查
    如果是去使能状态，则退出；
    */
    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, begin */
    if (VOS_TRUE != NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_CALL_CONTROL))
    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, end */
    {

        return VOS_FALSE;
    }


    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_ConvertSrvTypeToMma
 功能描述  : 将spm业务类型转换为mma cs session type类型
 输入参数  : enSpmSrvReq   - spm的业务类型
 输出参数  : pucMmaSrvType - SPM和MMA接口的业务类型
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月7日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SPM_ConvertSrvTypeToMma(
    TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8     enSpmSrvReq,
    TAF_MMA_SRV_TYPE_ENUM_UINT8        *pucMmaSrvType
)
{
    switch(enSpmSrvReq)
    {
        case TAF_SPM_SRV_REQ_TYPE_CALL:
            *pucMmaSrvType = TAF_MMA_SRV_TYPE_CS_MO_NORMAL_CALL;
            break;

        case TAF_SPM_SRV_REQ_TYPE_SS:
            *pucMmaSrvType = TAF_MMA_SRV_TYPE_CS_MO_SS;
            break;

        case TAF_SPM_SRV_REQ_TYPE_SMS:
            *pucMmaSrvType = TAF_MMA_SRV_TYPE_CS_MO_SMS;
            break;

        default:
            *pucMmaSrvType = TAF_MMA_SRV_TYPE_BUTT;
            break;
    }

    return;
}



/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-1-15, begin */
/*****************************************************************************
 函 数 名  : TAF_SPM_IsUESupportMoCallType
 功能描述  : 判断UE是否支持MO的呼叫类型
 输入参数  : enCallType---MO呼叫类型
 输出参数  : 无
 返 回 值  : VOS_FALSE           UE不支持该呼叫类型
             VOS_TRUE            UE支持该呼叫类型
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月15日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SPM_IsUESupportMoCallType(
    MN_CALL_TYPE_ENUM_U8                enCallType
)
{
    /* 该处不能区分是CS域还是PS域或IMS域的VIDEO，因此CALL CTRL修改呼叫
       类型为VIDEO时也认为呼叫类型合法,域选择结果为CS域后在CALL模块有判断，
       故删除下面的NV判断 */

    if ((MN_CALL_TYPE_VOICE     == enCallType)
     || (MN_CALL_TYPE_EMERGENCY == enCallType)
     || (MN_CALL_TYPE_VIDEO     == enCallType))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-1-15, end */



#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 函 数 名  : TAF_SPM_ProcSmmaRpt
 功能描述  : 处理memory available report事件

 输入参数  : pstMsgReportInd －－ 短信report消息地址

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月31日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_ProcSmmaRpt(TAF_SPM_MSG_REPORT_IND_STRU  *pstMsgReportInd)
{
    MN_MSG_EVENT_INFO_STRU             *pstMsgEventInfo = VOS_NULL_PTR;

    /* 不需要报道SMMA结果事件，返回 */
    if (VOS_FALSE == pstMsgReportInd->ucReportFlag)
    {
        return;
    }

    pstMsgEventInfo = PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_MSG_EVENT_INFO_STRU));

    if (VOS_NULL_PTR == pstMsgEventInfo )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
                      "TAF_SPM_ProcSmmaRpt: ERROR:Memory Alloc is failure!");

        return;
    }

    PS_MEM_SET(pstMsgEventInfo, 0, sizeof(MN_MSG_EVENT_INFO_STRU));

    /* 设置client ID与op ID */
    pstMsgEventInfo->clientId = pstMsgReportInd->usClientId;
    pstMsgEventInfo->opId     = pstMsgReportInd->ucOpId;

    if (TAF_MSG_ERROR_NO_ERROR != pstMsgReportInd->stRptEvtInfo.enErrorCode)
    {
        pstMsgEventInfo->u.stMemStatusInfo.bSuccess    = VOS_FALSE;

        pstMsgEventInfo->u.stMemStatusInfo.ulFailCause = pstMsgReportInd->stRptEvtInfo.enErrorCode;

        pstMsgEventInfo->u.stMemStatusInfo.enMemFlag   = MN_MSG_MEM_FULL_SET;

        /* 上报SMMA事件 */
        MN_SendClientEvent(pstMsgReportInd->usClientId,
                           MN_CALLBACK_MSG,
                           MN_MSG_EVT_SET_MEMSTATUS,
                           (VOS_VOID *)pstMsgEventInfo);

    }
    else
    {
        pstMsgEventInfo->u.stMemStatusInfo.bSuccess    = VOS_TRUE;
        pstMsgEventInfo->u.stMemStatusInfo.ulFailCause = MN_ERR_NO_ERROR;
        pstMsgEventInfo->u.stMemStatusInfo.enMemFlag   = MN_MSG_MEM_FULL_UNSET;

        /* 上报SMMA事件 */
        MN_SendClientEvent(pstMsgReportInd->usClientId,
                           MN_CALLBACK_MSG,
                           MN_MSG_EVT_SET_MEMSTATUS,
                           (VOS_VOID *)&pstMsgEventInfo);

        /* 更新op ID为广播op ID */
        pstMsgEventInfo->opId = pstMsgReportInd->ucBcOpId;
        /* 广播事件 */
        MN_SendClientEvent(MN_CLIENT_ALL,
                           MN_CALLBACK_MSG,
                           MN_MSG_EVT_MEMSTATUS_CHANGED,
                           (VOS_VOID *)pstMsgEventInfo);

    }

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsgEventInfo);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_ProcMoSmsRpt
 功能描述  : 处理短信report事件

 输入参数  : pstMsgReportInd －－ 短信report消息地址

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月31日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_ProcMoSmsRpt(TAF_SPM_MSG_REPORT_IND_STRU  *pstMsgReportInd)
{
    MN_MSG_EVENT_INFO_STRU             *pstMsgEventInfo = VOS_NULL_PTR;

    pstMsgEventInfo = PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_MSG_EVENT_INFO_STRU));

    if (VOS_NULL_PTR == pstMsgEventInfo)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
                      "TAF_SPM_ProcMoSmsRpt: ERROR:Memory Alloc is failure!");

        return;
    }

    PS_MEM_SET(pstMsgEventInfo, 0, sizeof(MN_MSG_EVENT_INFO_STRU));

    pstMsgEventInfo->u.stSubmitRptInfo.enSaveArea  = pstMsgReportInd->stRptEvtInfo.enSaveArea;
    pstMsgEventInfo->u.stSubmitRptInfo.ulSaveIndex = pstMsgReportInd->stRptEvtInfo.ulSaveIndex;
    pstMsgEventInfo->u.stSubmitRptInfo.ucMr        = pstMsgReportInd->stRptEvtInfo.ucMr;

    pstMsgEventInfo->clientId                      = pstMsgReportInd->usClientId;
    pstMsgEventInfo->opId                          = pstMsgReportInd->ucOpId;

    if (TAF_MSG_ERROR_NO_ERROR != pstMsgReportInd->stRptEvtInfo.enErrorCode)
    {
        /* 短信发送失败，则转换cause值 */
        pstMsgEventInfo->u.stSubmitRptInfo.enErrorCode = pstMsgReportInd->stRptEvtInfo.enErrorCode;
    }

    /* 通知应用短信发送结果 */
    MN_SendClientEvent(pstMsgReportInd->usClientId,
                       MN_CALLBACK_MSG,
                       MN_MSG_EVT_SUBMIT_RPT,
                       (VOS_VOID *)pstMsgEventInfo);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsgEventInfo);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_ProcSmsRptEvent
 功能描述  : 处理短信report事件，根据事件信息内容，通知AT模块

 输入参数  : pstMsgReportInd －－ 短信report消息地址

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月24日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_ProcSmsRptEvent(TAF_SPM_MSG_REPORT_IND_STRU  *pstMsgReportInd)
{
    if (TAF_SMS_MO_TYPE_SMMA == pstMsgReportInd->enSmsMoType)
    {
        TAF_SPM_ProcSmmaRpt(pstMsgReportInd);
    }
    else
    {
        TAF_SPM_ProcMoSmsRpt(pstMsgReportInd);
    }
}

/*****************************************************************************
 函 数 名  : TAF_SPM_SendAtEconfDialCnf
 功能描述  : 给AT发送创建增强型会议回复
 输入参数  : usClientId  --  cliend id
             ucOpId      --  opt id
             ucCallId    --  call id
             enCause     --  cause
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月28日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_SendAtEconfDialCnf(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    MN_CALL_ID_T                        ucCallId,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
)
{
    TAF_CALL_ECONF_DIAL_CNF_STRU        stEconfDialCnf;
    VOS_UINT16                          usLength;

    usLength = (VOS_UINT16)sizeof(TAF_CALL_ECONF_DIAL_CNF_STRU);

    PS_MEM_SET(&stEconfDialCnf, 0x00, usLength);

    stEconfDialCnf.enEvent      = TAF_CALL_EVT_ECONF_DIAL_CNF;
    stEconfDialCnf.usClientId   = usClientId;
    stEconfDialCnf.ucOpId       = ucOpId;
    stEconfDialCnf.ucCallId     = ucCallId;
    stEconfDialCnf.enCause      = enCause;

    MN_SendReportMsg(MN_CALLBACK_CS_CALL, (VOS_UINT8 *)&stEconfDialCnf, usLength);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_ParseEconfDailInfoFromMsg
 功能描述  : 从消息中获取呼叫相关信息
 输入参数  : pstMsg
 输出参数  :
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月28日
    作    者   : j00174725
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_ParseEconfDailInfoFromMsg(
    struct MsgCB                       *pstMsg
)
{
    MN_CALL_APP_REQ_MSG_STRU                *pstAppMsg           = VOS_NULL_PTR;
    TAF_CALL_ECONF_DIAL_REQ_STRU            *pstEconfParam       = VOS_NULL_PTR;
    TAF_SPM_CALL_ECONF_INFO_STRU            *pstEconfInfoAddr    = VOS_NULL_PTR;
    VOS_UINT32                               ulIndex;

    pstEconfInfoAddr    = TAF_SPM_GetCallEconfInfoAddr();
    pstAppMsg           = (MN_CALL_APP_REQ_MSG_STRU *)pstMsg;
    pstEconfParam       = &pstAppMsg->unParm.stEconfDial;
    PS_MEM_SET(pstEconfInfoAddr, 0x0, sizeof(TAF_SPM_CALL_ECONF_INFO_STRU));

    pstEconfInfoAddr->ucCallNum     = (VOS_UINT8)((pstEconfParam->stEconfCalllist.ulCallNum > TAF_CALL_MAX_ECONF_CALLED_NUM) ?
                                       TAF_CALL_MAX_ECONF_CALLED_NUM : pstEconfParam->stEconfCalllist.ulCallNum);
    pstEconfInfoAddr->usClientId    = pstAppMsg->clientId;
    pstEconfInfoAddr->ucopId        = pstAppMsg->opId;
    pstEconfInfoAddr->enCallMode    = pstEconfParam->enCallMode;
    pstEconfInfoAddr->enCallType    = pstEconfParam->enCallType;

    /* 将电话号码存到上下文中 */
    for (ulIndex = 0; ulIndex < pstEconfInfoAddr->ucCallNum; ulIndex++)
    {
        PS_MEM_CPY(&pstEconfInfoAddr->astEconfCheckInfo[ulIndex].stCalledNumber,
                   &pstEconfParam->stEconfCalllist.astDialNumber[ulIndex],
                   sizeof(MN_CALL_CALLED_NUM_STRU));

        PS_MEM_CPY(&pstEconfInfoAddr->astEconfCheckInfo[ulIndex].stSubaddr,
                   &pstEconfParam->stEconfCalllist.astSubaddr[ulIndex],
                   sizeof(MN_CALL_SUBADDR_STRU));
    }

    PS_MEM_CPY(&pstEconfInfoAddr->stDataCfg,
               &pstEconfParam->stDataCfg,
               sizeof(pstEconfParam->stDataCfg));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_SendEconfNotifyInd
 功能描述  : 给AT发送Notify Ind
 输入参数  : ucOpId
             ucNumOfCalls   --Call Num
             pstCallInfo
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月28日
   作    者   : j00174725
   修改内容   : 新建函数
*****************************************************************************/
VOS_VOID TAF_SPM_SendEconfNotifyInd(
    MN_OPERATION_ID_T                   ucOpId,
    VOS_UINT8                           ucNumOfCalls,
    TAF_CALL_ECONF_INFO_PARAM_STRU     *pstCallInfo
)
{
    TAF_CALL_EVT_ECONF_NOTIFY_IND_STRU *pstEconfNotify = VOS_NULL_PTR;

    /* 由于sizeof(TAF_CALL_EVT_ECONF_NOTIFY_IND_STRU)太大，采用动态内存 */
    pstEconfNotify = (TAF_CALL_EVT_ECONF_NOTIFY_IND_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_CALL_EVT_ECONF_NOTIFY_IND_STRU));
    if (VOS_NULL_PTR == pstEconfNotify)
    {
        return;
    }

    PS_MEM_SET(pstEconfNotify, 0, sizeof(TAF_CALL_EVT_ECONF_NOTIFY_IND_STRU));

    pstEconfNotify->enEvent                 = TAF_CALL_EVT_ECONF_NOTIFY_IND;
    pstEconfNotify->usClientId              = MN_GetRealClientId(MN_CLIENT_ID_BROADCAST, WUEPS_PID_TAF);;
    pstEconfNotify->ucOpId                  = ucOpId;
    pstEconfNotify->ucNumOfCalls            = ucNumOfCalls;

    PS_MEM_CPY(pstEconfNotify->astCallInfo, pstCallInfo, sizeof(TAF_CALL_ECONF_INFO_PARAM_STRU) * ucNumOfCalls);

    MN_SendReportMsg(MN_CALLBACK_CS_CALL, (VOS_UINT8 *)pstEconfNotify, sizeof(TAF_CALL_EVT_ECONF_NOTIFY_IND_STRU));

    PS_MEM_FREE(WUEPS_PID_TAF, pstEconfNotify);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_SPM_ReportEconfCheckRslt
 功能描述  : 将检查结果上报给AT
 输入参数  : enType
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月28日
   作    者   : j00174725
   修改内容   : 新建函数
*****************************************************************************/
VOS_VOID TAF_SPM_ReportEconfCheckRslt(VOS_VOID)
{
    TAF_SPM_CALL_ECONF_INFO_STRU       *pstEconfInfoAddr    = VOS_NULL_PTR;
    TAF_CALL_ECONF_INFO_PARAM_STRU     *pstCallInfo         = VOS_NULL_PTR;
    TAF_CALL_ECONF_INFO_PARAM_STRU     *pstTemp             = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;
    MN_OPERATION_ID_T                   ucOpId;

    pstEconfInfoAddr    = TAF_SPM_GetCallEconfInfoAddr();
    ucOpId              = pstEconfInfoAddr->ucopId;

    pstCallInfo = (TAF_CALL_ECONF_INFO_PARAM_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_CALL_ECONF_INFO_PARAM_STRU) * TAF_CALL_MAX_ECONF_CALLED_NUM);
    if (VOS_NULL_PTR == pstCallInfo)
    {
        return;
    }

    PS_MEM_SET(pstCallInfo, 0, sizeof(TAF_CALL_ECONF_INFO_PARAM_STRU) * TAF_CALL_MAX_ECONF_CALLED_NUM);

    pstTemp = pstCallInfo;

    for (ulIndex = 0; ulIndex < pstEconfInfoAddr->ucCallNum; ulIndex++)
    {
        pstTemp->enCause = pstEconfInfoAddr->astEconfCheckInfo[ulIndex].enCheckRslt;
        PS_MEM_CPY(&pstTemp->stCallNumber,
                   &pstEconfInfoAddr->astEconfCheckInfo[ulIndex].stCalledNumber,
                   sizeof(MN_CALL_CALLED_NUM_STRU));
        pstTemp++;
    }

    /* 给AT上报TAF_CALL_EVT_ECONF_NOTIFY_IND */
    TAF_SPM_SendEconfNotifyInd(ucOpId, pstEconfInfoAddr->ucCallNum, pstCallInfo);

    PS_MEM_FREE(WUEPS_PID_TAF, pstCallInfo);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RecordEconfCheckRslt
 功能描述  : 记录call control检查结果
 输入参数  : ulResult  --结果
             ulIndex   --序号
             enType    --类型

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月28日
   作    者   : j00174725
   修改内容   : 新建函数
*****************************************************************************/
VOS_VOID TAF_SPM_RecordEconfCheckRslt(
    VOS_UINT32                          ulIndex,
    VOS_UINT32                          ulResult
)
{
    TAF_SPM_CALL_ECONF_INFO_STRU       *pstEconfInfoAddr    = VOS_NULL_PTR;

    pstEconfInfoAddr    = TAF_SPM_GetCallEconfInfoAddr();

    /* ulIndex错误 */
    if (ulIndex >= pstEconfInfoAddr->ucCallNum)
    {
        return;
    }

    pstEconfInfoAddr->astEconfCheckInfo[ulIndex].enCheckRslt        = ulResult;
    pstEconfInfoAddr->astEconfCheckInfo[ulIndex].ulCheckCnfFlag     = VOS_TRUE;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_SetCallEconfDailState
 功能描述  : 设置呼叫状态
 输入参数  : enCause
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月28日
    作    者   : j00174725
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_SetEconfPreRslt(
    TAF_CS_CAUSE_ENUM_UINT32            enCause
)
{
    TAF_SPM_CALL_ECONF_INFO_STRU       *pstEconfInfoAddr    = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;

    pstEconfInfoAddr    = TAF_SPM_GetCallEconfInfoAddr();

    for (ulIndex = 0; ulIndex < pstEconfInfoAddr->ucCallNum; ulIndex++)
    {
        TAF_SPM_RecordEconfCheckRslt(ulIndex, enCause);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetEconfCheckResultSuccNum
 输入参数  : VOS_VOID
 输出参数  : pulSuccNum
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月28日
    作    者   : j00174725
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_GetEconfCheckResultSuccNum(
    VOS_UINT32                         *pulSuccNum
)
{
    TAF_SPM_CALL_ECONF_INFO_STRU       *pstEconfInfoAddr    = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;

    pstEconfInfoAddr    = TAF_SPM_GetCallEconfInfoAddr();

    for (ulIndex = 0; ulIndex < pstEconfInfoAddr->ucCallNum; ulIndex++)
    {
        if (TAF_CS_CAUSE_SUCCESS == pstEconfInfoAddr->astEconfCheckInfo[ulIndex].enCheckRslt)
        {
            (*pulSuccNum)++;
        }
    }

    return;

}



/*****************************************************************************
 函 数 名  : TAF_SPM_ProcEconfCheckResult
 功能描述  : 检查结果处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月28日
    作    者   : j00174725
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_ProcEconfCheckResult(VOS_VOID)
{
    TAF_SPM_CALL_ECONF_INFO_STRU       *pstEconfInfoAddr    = VOS_NULL_PTR;
    VOS_UINT32                          ulSuccNum;

    pstEconfInfoAddr    = TAF_SPM_GetCallEconfInfoAddr();
    ulSuccNum           = 0;

    TAF_SPM_GetEconfCheckResultSuccNum(&ulSuccNum);

    /* 全部成功 */
    if (pstEconfInfoAddr->ucCallNum == ulSuccNum)
    {
        /* 不需要给AT上报结果 */
        return VOS_TRUE;
    }
    /* 部分失败或者全部失败 */
    else
    {
        TAF_SPM_ReportEconfCheckRslt();
        return VOS_FALSE;
    }

}


#endif

/* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
#if (FEATURE_ON == FEATURE_ECALL)
/*****************************************************************************
 函 数 名  : TAF_SPM_ReadEcallNumber
 功能描述  : 获取ecall sdn或fdn文件中的test或recfg号码
 输入参数  : ucFdnRecordNum---FDN文件的记录条数
             ucSdnRecordNum---SDN文件的记录条数
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年04月3日
    作    者   : s00261364
    修改内容   : 新生成函数:
*****************************************************************************/
VOS_VOID TAF_SPM_ReadEcallNumber(
    VOS_UINT8                           ucFdnRecordNum,
    VOS_UINT8                           ucSdnRecordNum
)
{
    VOS_UINT8                           ucListLen;
    VOS_UINT8                           aucList[TAF_SPM_USIM_FILE_MAX_RECORD] = {0};

    /* If eCall only calls are supported, then EFFDN shall only contain two entries.
       The first entry shall contain the eCall test number and the second entry shall
       contain the eCall reconfiguration number. A terminal in eCall only mode performs
       the FDN related procedures. */

    /* ecall only时读取FDN文件中的头两条记录 */
    if (TAF_SDC_ECALL_ONLY == TAF_SDC_GetCurCallMode())
    {
        if (0 == ucFdnRecordNum)
        {
            return;
        }

        /* 调用异步接口读取EFfdn文件,目前只需要读取FDN的前两条记录 */
        ucListLen    = 2;
        aucList[0]   = TAF_SPM_USIM_FILE_FIRST_RECORD;
        aucList[1]   = TAF_SPM_USIM_FILE_SECOND_RECORD;

        NAS_PBAPI_QryECallNumber(WUEPS_PID_TAF, SI_PB_STORAGE_FD, ucListLen, aucList);

        return;
    }

    /* If eCall and normal calls are supported, then the last two entries of EFSDN
       shall contain the eCall test number and the eCall reconfiguration number respectively.
       A terminal in eCall and normal mode performs the SDN related procedures.*/

    /* 非ecall only时读取SDN文件中的最后两条记录,因此先获取SDN文件中的最大记录数 */
    if (TAF_SDC_ECALL_AND_NORMAL_CALL == TAF_SDC_GetCurCallMode())
    {
        if (0 == ucSdnRecordNum)
        {
            return;
        }

        ucListLen  = ucSdnRecordNum;

        if (1 == ucSdnRecordNum)
        {
            aucList[0] = ucSdnRecordNum;
        }
        else
        {
            aucList[0] = ucListLen - 1;
            aucList[1] = ucListLen;
        }

        NAS_PBAPI_QryECallNumber(WUEPS_PID_TAF, SI_PB_STORAGE_SD, ucListLen, aucList);
    }

    return;
}

#if (FEATURE_IMS == FEATURE_ON)
/*****************************************************************************
 函 数 名  : TAF_SPM_IsImsCallTypeEmgencyCall
 功能描述  : 判断当前ims call中是否存在紧急呼
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE -- 有紧急呼
             VOS_FALSE-- 没有紧急呼

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月04日
    作    者   : j00174725
    修改内容   : 为eCall feature增加
*****************************************************************************/
VOS_UINT32 TAF_SPM_IsImsCallTypeEmgencyCall(VOS_VOID)
{
    IMSA_SPM_CALL_GET_CALL_INFO_IND_STRU    stCallInfoInd;
    VOS_UINT32                              i;

    /* 初始化 */
    PS_MEM_SET(&stCallInfoInd, 0x0, sizeof(IMSA_SPM_CALL_GET_CALL_INFO_IND_STRU));

    /* 获取IMS call 信息 */
    (VOS_VOID)IMSA_SpmGetCallInfo(&stCallInfoInd);

    for (i = 0; i < stCallInfoInd.ucNumOfCalls; i++)
    {
        /* IMS下只有普通紧急呼叫 */
        if (MN_CALL_TYPE_EMERGENCY == stCallInfoInd.astCallInfo[i].enCallType)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_SndImsRelAllCall
 功能描述  : 释放所有IMS Call
 输入参数  : MN_CLIENT_ID_T
             MN_OPERATION_ID_T
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月04日
    作    者   : j00174725
    修改内容   : 为eCall feature增加
*****************************************************************************/
VOS_VOID TAF_SPM_SndImsRelAllCall(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId
)
{
    MN_CALL_APP_REQ_MSG_STRU            stAppMsg;

    /* 初始化 */
    PS_MEM_SET(&stAppMsg, 0x0, sizeof(stAppMsg));

    stAppMsg.clientId                           = usClientId;
    stAppMsg.opId                               = ucOpId;
    stAppMsg.unParm.stCallMgmtCmd.enCallSupsCmd = MN_CALL_SUPS_CMD_REL_ALL_CALL;

    /* 发送给IMSA处理 */
    TAF_SPM_SendImsaSupsCmdReq((MN_CALL_APP_REQ_MSG_STRU *)&stAppMsg);

    /* 如果有重拨的缓存需要清掉  */
    TAF_SPM_FreeCallRedialBufferWithClientId(usClientId);

    return;
}
#endif

#endif

/* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : TAF_SPM_GetCdmaVoiceCallRfAvailInfo
 功能描述  : 获取CDMA语音呼叫的RF标志，当RF不可用时，输出捕获列表
 输入参数  : TAF_MMA_SRV_ACQ_RAT_LIST_STRU      *pstSrvAcqRatList
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月15日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SPM_GetCdmaVoiceCallRfAvailInfo(
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU      *pstSrvAcqRatList
)
{
    VOS_UINT8                           uc1xRfAvailFlg;

    uc1xRfAvailFlg   = TAF_SDC_Get1xRfAvailFlag();

    /* TO DO: 3GPP2的IMS方案未定，预留 */
#if 0
    /* 支持IMS语音 */
    if (VOS_TRUE == TAF_SDC_GetVoiceCallOnImsSupportFlag())
    {
#if (FEATURE_ON == FEATURE_LTE)
        /* 支持LTE下的IMS功能 */
        if (VOS_TRUE == TAF_SDC_GetLteImsSupportFlag())
        {
            enVoicePerferred = TAF_SDC_GetVoiceDomain();
            switch (enVoicePerferred)
            {
                /* domain selection in CS voice preferred */
                case TAF_SDC_VOICE_DOMAIN_CS_PREFERRED:
                    break;

                /* domain selection in IMS PS voice preferred */
                case TAF_SDC_VOICE_DOMAIN_IMS_PS_PREFERRED:
                    break;

                /* domain selection in IMS PS voice only */
                case TAF_SDC_VOICE_DOMAIN_IMS_PS_ONLY:
                    break;

                /* domain selection in CS voice only */
                case TAF_SDC_VOICE_DOMAIN_CS_ONLY:
                default:
                    break;
            }

        }
#endif
    }
#endif

    if (VOS_FALSE == uc1xRfAvailFlg)
    {
        pstSrvAcqRatList->aenRatType[pstSrvAcqRatList->ucRatNum] = TAF_MMA_SRV_ACQ_RAT_TYPE_1X;
        pstSrvAcqRatList->ucRatNum++;
    }

    /* 返回1X的RF标志 */
    return uc1xRfAvailFlg;

}
/*****************************************************************************
 函 数 名  : TAF_SPM_IsCsimServiceAvailable
 功能描述  : 检查卡的服务状态是否可用

 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:           CSIM可用
             VOS_FALSE:          CSIM不可用

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月22日
    作    者   : l00359089
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SPM_IsCsimServiceAvailable(VOS_VOID)
{
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enCsimStatus;

    enCsimStatus = TAF_SDC_GetCsimStatus();

    return TAF_SPM_IsSimServiceAvailable(enCsimStatus);
}

#endif

/*****************************************************************************
 函 数 名  : TAF_SPM_GetRfAvailInfo
 功能描述  : 判断当前RF是否可用，当RF不可用时输出捕获列表
 输入参数  : TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8     enSrvReqType
 输出参数  : TAF_MMA_SRV_ACQ_RAT_LIST_STRU      *pstSrvAcqRatList
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月15日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SPM_GetRfAvailInfo(
    TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8     enSrvReqType,
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU      *pstSrvAcqRatList
)
{
#if (FEATURE_ON == FEATURE_DSDS)
    VOS_UINT8                           uc3GppRfAvailFlg;

    uc3GppRfAvailFlg = TAF_SDC_Get3GppRfAvailFlag();
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        /* 3GPP2只有CS CALL业务经过SPM */
        if (TAF_SPM_SRV_REQ_TYPE_CALL == enSrvReqType)
        {
            return TAF_SPM_GetCdmaVoiceCallRfAvailInfo(pstSrvAcqRatList);
        }
    }
    else
#endif
    {
#if (FEATURE_ON == FEATURE_DSDS)
        /* 如果当前为NO RF，需要输出需要搜网的RAT类型 */
        if (VOS_FALSE == uc3GppRfAvailFlg)
        {
            pstSrvAcqRatList->aenRatType[pstSrvAcqRatList->ucRatNum] = TAF_MMA_SRV_ACQ_RAT_TYPE_GUL;
            pstSrvAcqRatList->ucRatNum++;
        }

        return uc3GppRfAvailFlg;
#endif
    }

    /*lint -e527*/
    return VOS_TRUE;
    /*lint +e527*/
}

/*****************************************************************************
 函 数 名  : TAF_SPM_IsSimServiceAvailable
 功能描述  : 检查卡的服务状态是否可用

 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:           SIM可用
             VOS_FALSE:          SIM不可用

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月22日
    作    者   : l00359089
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SPM_IsSimServiceAvailable(
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enSimStatus
)
{
    VOS_UINT32                           ulRslt;

    switch (enSimStatus)
    {
        case TAF_SDC_USIM_STATUS_ROMSIM:
        case TAF_SDC_USIM_STATUS_VALID:
        case TAF_SDC_USIM_STATUS_CS_UNVALID:
        /* 当PS业务无效时，在L下会disable LTE，因此此种场景下，后续允许被缓存 */
        case TAF_SDC_USIM_STATUS_PS_UNVALID:
            ulRslt = VOS_TRUE;
            break;

        case TAF_SDC_USIM_STATUS_SIM_PIN:
        case TAF_SDC_USIM_STATUS_SIM_PUK:
        case TAF_SDC_USIM_STATUS_NET_LCOK:
        case TAF_SDC_USIM_STATUS_IMSI_LCOK:
        case TAF_SDC_USIM_STATUS_UNVALID:
        case TAF_SDC_USIM_STATUS_NO_PRESENT:
        case TAF_SDC_USIM_STATUS_BUTT:
        case TAF_SDC_USIM_STATUS_CS_PS_UNVALID:
        case TAF_SDC_USIM_STATUS_READY_TIMEROUT:
            ulRslt = VOS_FALSE;
            break;

        default:
            ulRslt = VOS_FALSE;
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SPM_IssimServiceAvailable(): something wrong!");
            break;
    }

    return ulRslt;
}


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


