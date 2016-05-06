/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmlLib.c
  版 本 号   : 初稿
  作    者   : zhoujun 40661
  生成日期   : 2011年7月25日
  最近修改   : 2011年7月25日
  功能描述   : MML_CTX的对外提供库函数
  函数列表   :
  修改历史   :
  1.日    期   : 2011年7月25日
    作    者   : zhoujun 40661
    修改内容   : 创建文件

****************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "PsLib.h"

#include "PsCommonDef.h"
#include "NasComm.h"
#include "NasMmlCtx.h"
#include "UsimPsInterface.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#include "MmLmmInterface.h"
#endif
#include "NasMmlLib.h"
#include "GmmExt.h"
#include "NasMmcSndLmm.h"

#include "zlib.h"
#include "NVIM_Interface.h"
#include "NasUsimmApi.h"
#include "NasMmlCtx.h"

#include "NasMmcSndOm.h"

#include "NasMmcFsmPlmnSelection.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*****************************************************************************
  2 常量定义
*****************************************************************************/

/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define THIS_FILE_ID PS_FILE_ID_NASMML_LIB_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/

/*****************************************************************************
  5 变量定义
*****************************************************************************/
VOS_UINT32 g_aulNasMmlNortAmericanMcc[]       = {0x00000103, 0x00010103, 0x00020103, 0x00030103, 0x00040103, 0x00050103, 0x00060103};
VOS_UINT32 g_aulNasMmlBritainMcc[]            = {0x00040302, 0x00050302};
VOS_UINT32 g_aulNasMmlIndianMcc[]             = {0x00040004, 0x00050004, 0x00060004};
VOS_UINT32 g_aulNasMmlJapanMcc[]              = {0x00000404, 0x00010404};
VOS_UINT32 g_aulNasMmlSudanMcc[]              = {0x00040306, 0x00090506};
VOS_UINT32 g_aulNasMmlDefaultSingleMcc[]      = {0xFFFFFFFF};

NAS_MML_MCC_DESC_STRU  g_astNasMmlMccList[] =
{
    {sizeof(g_aulNasMmlNortAmericanMcc)/sizeof(VOS_UINT32), g_aulNasMmlNortAmericanMcc},
    {sizeof(g_aulNasMmlBritainMcc)/sizeof(VOS_UINT32), g_aulNasMmlBritainMcc},
    {sizeof(g_aulNasMmlIndianMcc)/sizeof(VOS_UINT32), g_aulNasMmlIndianMcc},
    {sizeof(g_aulNasMmlJapanMcc)/sizeof(VOS_UINT32), g_aulNasMmlJapanMcc},
    {sizeof(g_aulNasMmlSudanMcc)/sizeof(VOS_UINT32), g_aulNasMmlSudanMcc},
    {sizeof(g_aulNasMmlDefaultSingleMcc)/sizeof(VOS_UINT32), g_aulNasMmlDefaultSingleMcc},
};

/* 复位分析需要忽略的消息列表 */
NAS_MML_DISCARD_MSG_STRU g_stNasMmlDiscardMsgTbl[]=
{
    /* GUNAS收到的消息 */
    {UEPS_PID_GAS,                      WUEPS_PID_MMC,                          GRRMM_SCELL_MEAS_IND},
    {WUEPS_PID_WRR,                     WUEPS_PID_MMC,                          RRMM_AT_MSG_IND},   
    {WUEPS_PID_WRR,                     WUEPS_PID_MMC,                          RRMM_AT_MSG_CNF},
    {UEPS_PID_GAS,                      WUEPS_PID_MMC,                          RRMM_USING_FREQ_IND},
    {WUEPS_PID_WRR,                     WUEPS_PID_MMC,                          RRMM_USING_FREQ_IND},
    {WUEPS_PID_WRR,                     WUEPS_PID_MMC,                          RRMM_SEARCHED_PLMN_INFO_IND},
    {WUEPS_PID_RABM,                    WUEPS_PID_GMM,                          ID_RABM_GMM_MML_PROC_STATUS_QRY_REQ},
    {PS_PID_MM,                         WUEPS_PID_MMC,                          ID_LMM_MMC_STATUS_IND},
    {PS_PID_MM,                         WUEPS_PID_MMC,                          ID_LMM_MMC_TIMER_STATE_NOTIFY},
    {PS_PID_MM,                         WUEPS_PID_MMC,                          ID_LMM_MMC_NOT_CAMP_ON_IND},
    {PS_PID_MM,                         WUEPS_PID_MMC,                          ID_LMM_MMC_CELL_SIGN_REPORT_IND},
    {WUEPS_PID_WRR,                     WUEPS_PID_MMC,                          RRMM_BG_PLMN_SEARCH_STATUS_IND},
    
    /* GUNAS发送的消息 */
    {WUEPS_PID_MM,                      WUEPS_PID_WRR,                          RRMM_NAS_INFO_CHANGE_REQ},
    {WUEPS_PID_GMM,                     WUEPS_PID_WRR,                          RRMM_NAS_INFO_CHANGE_REQ},
    {WUEPS_PID_MM,                      UEPS_PID_GAS,                           GRRMM_NAS_INFO_CHANGE_REQ},
    {WUEPS_PID_GMM,                     UEPS_PID_GAS,                           GRRMM_NAS_INFO_CHANGE_REQ},
    {WUEPS_PID_MMC,                     WUEPS_PID_WRR,                          RRMM_AT_MSG_REQ},
    {WUEPS_PID_MMC,                     UEPS_PID_GAS,                           GRRMM_AT_MSG_REQ},
    {WUEPS_PID_MMC,                     WUEPS_PID_WRR,                          RRMM_NAS_COMM_INFO_CHANGE_REQ},
    {WUEPS_PID_MMC,                     UEPS_PID_GAS,                           RRMM_NAS_COMM_INFO_CHANGE_REQ},
    {WUEPS_PID_GMM,                     WUEPS_PID_RABM,                         ID_GMM_RABM_MML_PROC_STATUS_QRY_CNF},
    {WUEPS_PID_GMM,                     WUEPS_PID_WRR,                          RRMM_BEGIN_SESSION_NOTIFY},
    {WUEPS_PID_GMM,                     WUEPS_PID_WRR,                          RRMM_END_SESSION_NOTIFY},
    {WUEPS_PID_GMM,                     TPS_PID_RRC,                            RRMM_BEGIN_SESSION_NOTIFY},
    {WUEPS_PID_GMM,                     TPS_PID_RRC,                            RRMM_END_SESSION_NOTIFY},
    {WUEPS_PID_GMM,                     UEPS_PID_GAS,                           RRMM_BEGIN_SESSION_NOTIFY},
    {WUEPS_PID_GMM,                     UEPS_PID_GAS,                           RRMM_END_SESSION_NOTIFY},
    {WUEPS_PID_MM,                      WUEPS_PID_WRR,                          RRMM_BEGIN_SESSION_NOTIFY},
    {WUEPS_PID_MM,                      WUEPS_PID_WRR,                          RRMM_END_SESSION_NOTIFY},
    {WUEPS_PID_MM,                      TPS_PID_RRC,                            RRMM_BEGIN_SESSION_NOTIFY},
    {WUEPS_PID_MM,                      TPS_PID_RRC,                            RRMM_END_SESSION_NOTIFY},
    {WUEPS_PID_MM,                      UEPS_PID_GAS,                           RRMM_BEGIN_SESSION_NOTIFY},
    {WUEPS_PID_MM,                      UEPS_PID_GAS,                           RRMM_END_SESSION_NOTIFY},
    {WUEPS_PID_MMC,                     PS_PID_MM,                              ID_MMC_LMM_OTHER_MODEM_INFO_NOTIFY},
    {WUEPS_PID_MMC,                     PS_PID_MM,                              ID_MMC_LMM_CELL_SIGN_REPORT_NOTIFY},
};

/*****************************************************************************
  6 函数定义
*****************************************************************************/
/*****************************************************************************
 函 数 名  : NAS_MML_GetEquivalentMccList
 功能描述  : 获取指定MCC对应的等效MCC列表，若此该国只有一个MCC，则返回一个指向只包含
             该MCC的NAS_MML_MCC_ELEMENT_STRU *类型的指针
 输入参数  : ulMcc
 输出参数  : 无
 返 回 值  : NAS_MML_MCC_DESC_STRU *，返回指向等效MCC结构体的指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月30日
    作    者   : l00289540
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_MCC_DESC_STRU* NAS_MML_GetEquivalentMccList(VOS_UINT32 ulMcc)
{
    VOS_UINT32                i;
    VOS_UINT32                j;
    VOS_UINT32                ulArraySize;

    ulArraySize = sizeof(g_astNasMmlMccList)/sizeof(NAS_MML_MCC_DESC_STRU);

    /* 将数组最后一个结构体的国家码赋值为ulMcc，从而使得如下查找始终可以成功 */
    g_astNasMmlMccList[ulArraySize - 1].pulMccList[0] = ulMcc;

    for (i = 0; i < ulArraySize; i++)
    {
        for (j = 0; j < g_astNasMmlMccList[i].ulMccNum; j++)
        {
            if (ulMcc == g_astNasMmlMccList[i].pulMccList[j])
            {
                return &(g_astNasMmlMccList[i]);
            }
        }
    }

    return VOS_NULL_PTR;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsSpecMccInList
 功能描述  : 判断指定MCC是否在某个等效MCC列表中
 输入参数  : ulMcc:待查找的国家码
             pstMccList:国家码列表
 输出参数  : 无
 返 回 值  : VOS_TRUE:ulMcc在列表pstMccList中，
             VOS_FALSE:ulMcc不在列表中
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月7日
    作    者   : l00289540
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_IsSpecMccInEquMccList(VOS_UINT32 ulMcc, NAS_MML_MCC_DESC_STRU *pstMccList)
{
    VOS_UINT32                ulIndex;

    for (ulIndex = 0; ulIndex < pstMccList->ulMccNum; ulIndex++)
    {
        if (ulMcc == pstMccList->pulMccList[ulIndex])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
/*lint -save -e958 */

/*****************************************************************************
 函 数 名  : NAS_MML_GetCsServiceExistFlg
 功能描述  : 获取CS域业务的存在情况,包括当前CS业务和缓存的CS业务
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:CS业务存在
             VOS_FALSE:CS业务不存在
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月16日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MML_GetCsServiceExistFlg( VOS_VOID )
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;

    pstConnStatus   = NAS_MML_GetConnStatus();

    /* CS域有缓存业务存在 */
    if ( VOS_TRUE == pstConnStatus->ucCsServiceBufferFlg)
    {
        return VOS_TRUE;
    }

    /* CS域有当前业务存在 */
    if ( VOS_TRUE == pstConnStatus->ucCsServiceConnStatusFlg)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetPsServiceExistFlg
 功能描述  : 获取PS域业务的存在情况,包括当前PS业务和缓存的PS业务
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:PS业务存在
             VOS_FALSE:PS业务不存在
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月16日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数
 2.日    期   : 2011年10月11日
   作    者   : l00171473
   修改内容   : V7R1 phase II, TC环回调整，增加PS TC业务存在标志

 3.日    期   : 2012年4月3日
   作    者   : z40661
   修改内容   : DTS2012040102003，当前判断PS业务是否存在的函数处理有问题
 4.日    期   : 2012年6月4日
   作    者   : w00176964
   修改内容   : V7R1 C50 GUL BG:PS业务判断不准确
*****************************************************************************/
VOS_UINT32  NAS_MML_GetPsServiceExistFlg( VOS_VOID )
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus;

    pstConnStatus     = NAS_MML_GetConnStatus();


    /* L下的判断规则完全依赖于LMM上报的链路状态 */
#if (FEATURE_ON == FEATURE_LTE)
    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        /* PS域有当前业务存在 */
        if ( VOS_TRUE == pstConnStatus->ucEpsServiceConnStatusFlg)
        {
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }
#endif

    /* GU下的判断规则在需要根据PDP激活状态和RRC链路状态 */

    /* PS域有缓存业务存在,此标志暂时不用更新,主要原因为当前MMC搜网不需要判断GMM的缓存业务 */
    if ( VOS_TRUE == pstConnStatus->ucPsServiceBufferFlg)
    {
        return VOS_TRUE;
    }


    /* GSM下当前PDP状态存在且TBF链路存在认为当前PS有业务存在 */
    if ((NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
     && (VOS_TRUE == pstConnStatus->ucPdpStatusFlg)
     && (VOS_TRUE == pstConnStatus->ucPsTbfStatusFlg))
    {
        return VOS_TRUE;
    }

    /* W下当前PDP状态存在时有PS信令连接和RRC连接则认为存在PS业务 */
    if ((NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
     && (VOS_TRUE == pstConnStatus->ucPdpStatusFlg)
     && (VOS_TRUE == pstConnStatus->ucRrcStatusFlg))
    {
        return VOS_TRUE;
    }

    /* PS域触发的TC环回业务存在 */
    if ( VOS_TRUE == pstConnStatus->ucPsTcServiceFlg )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MML_IsNorthAmericanMcc
 功能描述  : 判断mcc是否是north American的网络，范围310-316
 输入参数  : ulMcc - 国家码
 输出参数  : 无
 返 回 值  : VOS_TRUE:是北美网络国家码
             VOS_FALSE:不是北美网络国家码
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年6月8日
   作    者   : z00161729
   修改内容   : 24008 23122 R11 CR升级项目修改

*****************************************************************************/
VOS_UINT32 NAS_MML_IsNorthAmericanMcc(
    VOS_UINT32                          ulMcc
)
{
    if ((NAS_MML_PCS1900_MCC_LOW_VALUE == (ulMcc & NAS_MML_MCC_LOW_VALUE_MASK))
     && (NAS_MML_PCS1900_MCC_HIGH_VALUE_RANGE >= (ulMcc & NAS_MML_MCC_THIRD_BYTE_VALUE_MASK)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MML_IsIndianMcc
 功能描述  : 判断mcc是否是Indian的网络，范围404-406
 输入参数  : ulMcc - 国家码
 输出参数  : 无
 返 回 值  : VOS_TRUE:是印度网络国家码
             VOS_FALSE:不是印度网络国家码
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年6月8日
   作    者   : z00161729
   修改内容   : 24008 23122 R11 CR升级项目修改

*****************************************************************************/
VOS_UINT32 NAS_MML_IsIndianMcc(
    VOS_UINT32                          ulMcc
)
{
    /* 404-406为印度国家码 */
    if ((NAS_MML_INDIA_MCC_LOW_VALUE == (ulMcc & NAS_MML_MCC_LOW_VALUE_MASK))
     && (NAS_MML_INDIA_MCC_LOW_VALUE_RANGE <= (ulMcc & NAS_MML_MCC_THIRD_BYTE_VALUE_MASK))
     && (NAS_MML_INDIA_MCC_HIGH_VALUE_RANGE >= (ulMcc & NAS_MML_MCC_THIRD_BYTE_VALUE_MASK)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  :NAS_MML_SetBitValueToBuffer
 功能描述  :在数据中设定Bit位的值
 输入参数  :ucDataBuf:   数据内容
            ulBitNo:     Bit号,从1开始
            ucValue:     需要设置的值
 输出参数  :无
 返 回 值  : 无
 调用函数  :无

 修改历史      :
 1.日    期   : 2015年6月11日
   作    者   : z00161729
   修改内容   : 24008 23122 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID NAS_MML_SetBitValueToBuffer(
    VOS_UINT8                          *pucDataBuf,
    VOS_UINT32                          ulBitNo,
    VOS_UINT8                           ucValue
)
{
    VOS_UINT32                          ulOffset;
    VOS_UINT8                           ucBit;

    if (0 == ulBitNo)
    {
        return;
    }

    ulOffset = (ulBitNo - 1) / NAS_MML_OCTET_EIGHT_BITS;

    ucBit    = (VOS_UINT8)((ulBitNo - 1)% NAS_MML_OCTET_EIGHT_BITS);

    if (0 != ucValue)
    {
        /*lint -e701 */
        pucDataBuf[ulOffset] |= (VOS_UINT8)(NAS_MML_OCTET_MOVE_ONE_BITS << ucBit);
        /*lint +e701 */
    }
    else
    {
        /*lint -e701 */
        pucDataBuf[ulOffset] &= (~(VOS_UINT8)(NAS_MML_OCTET_MOVE_ONE_BITS << ucBit));
        /*lint +e701 */
    }

    return;
}

/*****************************************************************************
 函 数 名  :NAS_MML_GetBitValueFromBuffer
 功能描述  :从数据中获取指定Bit位的值　
 输入参数  :ucDataBuf:   数据内容
           ulBitNo:     Bit号，从1开始
 输出参数  :无
 返 回 值  : 指定bit位的值
 调用函数  :无

 修改历史      :
  1.日    期   : 2015年6月11日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT8 NAS_MML_GetBitValueFromBuffer(
    VOS_UINT8                          *pucDataBuf,
    VOS_UINT32                          ulBitNo
)
{
    VOS_UINT32                          ulOffset;
    VOS_UINT8                           ucBit;

    if (0 == ulBitNo)
    {
        return 0;
    }

    ulOffset = (ulBitNo - 1)/ NAS_MML_OCTET_EIGHT_BITS;

    ucBit    = (VOS_UINT8)((ulBitNo - 1) % NAS_MML_OCTET_EIGHT_BITS);

    return (pucDataBuf[ulOffset] >> ucBit)& 0x1;
}

/*****************************************************************************
 函 数 名  : NAS_MML_IsUeSupportImsVoice
 功能描述  : UE是否支持IMS Voice
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:支持 VOS_FALSE:不支持
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月23日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改

*****************************************************************************/
VOS_UINT8 NAS_MML_IsUeSupportImsVoice(VOS_VOID)
{
    VOS_UINT8                                               ucVoiceOnIms;
    NAS_MML_VOICE_DOMAIN_PREFERENCE_ENUM_UINT8              enVoiceDomainPreference;


    enVoiceDomainPreference = NAS_MML_GetVoiceDomainPreference();
    ucVoiceOnIms    = NAS_MML_GetVoiceCallOnImsSupportFlag();

    /* 总控开关未打开时，认为UE不支持IMS */
    if (VOS_FALSE == NAS_MML_GetLteImsSupportFlg())
    {
        return VOS_FALSE;
    }

    /* 支持IMS 语音且voice domain nv配置不是cs only则返回VOS_TRUE */
    if ((VOS_TRUE == ucVoiceOnIms)
     && (NAS_MML_CS_VOICE_ONLY != enVoiceDomainPreference))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MML_IsPlmnMccBelongToTheSameCountry
 功能描述  : 判断两个MCC是否属于同一个国家
 输入参数  : ulSrcMcc:需要比较的源国家码
             ulDestMcc:需要比较的目的国家码
 输出参数  : 无
 返 回 值  : VOS_TRUE:两个MCC属于同一国家
             VOS_FALSE:两个MCC不属于同一国家
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月9日
    作    者   : l00289540
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_IsPlmnMccBelongToTheSameCountry(
    VOS_UINT32                          ulSrcMcc,
    VOS_UINT32                          ulDestMcc
)
{
    NAS_MML_MCC_DESC_STRU              *pstEquMccList = VOS_NULL_PTR;
    VOS_UINT32                          i;

    if (ulSrcMcc == ulDestMcc)
    {
        return VOS_TRUE;
    }

    pstEquMccList = NAS_MML_GetEquivalentMccList(ulSrcMcc);

    if (VOS_NULL_PTR == pstEquMccList)
    {
        return VOS_FALSE;
    }

    for (i = 0; i < pstEquMccList->ulMccNum; i++)
    {
        if (ulDestMcc == pstEquMccList->pulMccList[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MML_ComparePlmnMcc
 功能描述  : 比较两个网络是否在同一个国家中,国家码是否相同
 输入参数  : ulSrcMcc:需要比较的源国家码
             ulDestMcc:需要比较的目的国家码
 输出参数  : 无
 返 回 值  : VOS_TRUE:是同一国家码
             VOS_FALSE:不是同一国家码
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月13日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2015年6月8日
   作    者   : z00161729
   修改内容   : 24008 23122 R11 CR升级项目修改

*****************************************************************************/
VOS_UINT32 NAS_MML_ComparePlmnMcc(
    VOS_UINT32                          ulSrcMcc,
    VOS_UINT32                          ulDestMcc
)
{
    VOS_UINT32                          ulSrcMccUsaMccFlag;
    VOS_UINT32                          ulDestMccUsaMccFlag;
    VOS_UINT32                          ulSrcMccIndianMccFlag;
    VOS_UINT32                          ulDestMccIndianMccFlag;

    /* 23122_CR0207R4_(Rel-11)_C1-113664-revc1-113621-revc1-113196-revc1-112708-revc1-112635 23122 1.2章节描述如下:
    Country: A country is identified by a single MCC value, with the exception that MCC
    values 310 through 316 identify a single country (USA) and MCC values 404 through
    406 identify a single country (India). pstBcchPLmnId属于 NA PCS1900,北美的国家码在310和316之间，要进行特殊处理。
    印度国家码在404-406之间，其它国家的PLMN的国家码都相同，可以直接比较*/
    ulSrcMccUsaMccFlag     = NAS_MML_IsNorthAmericanMcc(ulSrcMcc);
    ulDestMccUsaMccFlag    = NAS_MML_IsNorthAmericanMcc(ulDestMcc);
    ulSrcMccIndianMccFlag  = NAS_MML_IsIndianMcc(ulSrcMcc);
    ulDestMccIndianMccFlag = NAS_MML_IsIndianMcc(ulDestMcc);

    if (((VOS_TRUE == ulSrcMccUsaMccFlag)
       && (VOS_TRUE == ulDestMccUsaMccFlag))
      || ((VOS_TRUE == ulSrcMccIndianMccFlag)
       && (VOS_TRUE == ulDestMccIndianMccFlag)))
    {
        return VOS_TRUE;
    }
    else
    {
        if (ulDestMcc != ulSrcMcc)
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}


/* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-17, begin */
/*****************************************************************************
 函 数 名  : NAS_MML_ExactlyCompareBcchPlmnwithSimPlmn
 功能描述  : 精确比较SIM卡中存储PLMN与系统消息广播中PLMN是否相等,MNC完全相同才为相等，PLMN 属于 NA PCS1900 除外
             1)一个plmn是Bcch格式的，一个plmn是Sim格式的进行比较时，
               Bcch格式的plmn必须作为第一个入参，sim格式的必须作为第二个入参
             2)两个Bcch格式的plmn比较时，入参顺序没关系
             3)两个Sim格式的plmn比较时，入参顺序没关系
 输入参数  : NAS_MML_PLMN_ID_STRU    *pstBccPlmnId
             NAS_MML_PLMN_ID_STRU    *pstSimPlmnId
 输出参数  : 无
 返 回 值  : VOS_TRUE: PLMN ID相同
             VOS_FALSE: PLMN ID不相同
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月14日
   作    者   : t00212959
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_ExactlyCompareBcchPlmnwithSimPlmn(
    NAS_MML_PLMN_ID_STRU                *pstBccPlmnId,
    NAS_MML_PLMN_ID_STRU                *pstSimPlmnId
)
{
    VOS_UINT8                           ucBcchMnc3;
    VOS_UINT8                           ucSimMnc3;

    if (pstBccPlmnId->ulMcc == pstSimPlmnId->ulMcc)
    {
        if (pstBccPlmnId->ulMnc == pstSimPlmnId->ulMnc)
        {
            return VOS_TRUE;
        }
        else if ((pstBccPlmnId->ulMnc & NAS_MML_MCC_LOW_VALUE_MASK)
              == (pstSimPlmnId->ulMnc & NAS_MML_MCC_LOW_VALUE_MASK))
        {
            ucBcchMnc3 = (VOS_UINT8)((pstBccPlmnId->ulMnc & NAS_MML_MCC_THIRD_BYTE_VALUE_MASK) >> 16);
            ucSimMnc3  = (VOS_UINT8)((pstSimPlmnId->ulMnc & NAS_MML_MCC_THIRD_BYTE_VALUE_MASK) >> 16);

            /* PLMN 属于 NA PCS1900*/
            if ((NAS_MML_PCS1900_MCC_LOW_VALUE == (pstBccPlmnId->ulMcc & NAS_MML_MCC_LOW_VALUE_MASK))
             && (NAS_MML_PCS1900_MCC_HIGH_VALUE_RANGE >= (pstBccPlmnId->ulMcc & NAS_MML_MCC_THIRD_BYTE_VALUE_MASK)))
            {
                if ( ((NAS_MML_PCS1900_MNC_THIRD_BYTE_VALUE_F == ucBcchMnc3)
                 && (NAS_MML_PCS1900_MNC_THIRD_BYTE_VALUE_0 == ucSimMnc3))
                 || ((NAS_MML_PCS1900_MNC_THIRD_BYTE_VALUE_0 == ucBcchMnc3)
                 && (NAS_MML_PCS1900_MNC_THIRD_BYTE_VALUE_F == ucSimMnc3)) )
                {
                    return VOS_TRUE;
                }
            }
        }
        else
        {
        }
    }

    return VOS_FALSE;
}

/* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-17, end */
/*****************************************************************************
 函 数 名  : NAS_MML_CompareBcchPlmnwithSimPlmn
 功能描述  : 比较SIM卡中存储PLMN与系统消息广播中PLMN是否相等,
             1)一个plmn是Bcch格式的，一个plmn是Sim格式的进行比较时，
               Bcch格式的plmn必须作为第一个入参，sim格式的必须作为第二个入参
             2)两个Bcch格式的plmn比较时，入参顺序没关系
             3)两个Sim格式的plmn比较时，入参顺序没关系
 输入参数  : NAS_MML_PLMN_ID_STRU    *pstBccPlmnId
             NAS_MML_PLMN_ID_STRU    *pstSimPlmnId
 输出参数  : 无
 返 回 值  : VOS_TRUE: PLMN ID相同
             VOS_FALSE: PLMN ID不相同
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年07月15日
   作    者   : zhoujun \ 40661
   修改内容   : 新生成函数
 2.日    期   : 2012年8月14日
   作    者   : t00212959
   修改内容   : DCM定制需求和遗留问题
*****************************************************************************/
VOS_UINT32 NAS_MML_CompareBcchPlmnwithSimPlmn(
    NAS_MML_PLMN_ID_STRU                *pstBccPlmnId,
    NAS_MML_PLMN_ID_STRU                *pstSimPlmnId
)
{
    VOS_BOOL                            bCmpRlst;
    VOS_UINT8                           ucBcchMnc3;
    VOS_UINT8                           ucSimMnc3;

    bCmpRlst   = VOS_FALSE;

    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-14, begin */
    /* 如果需要精确比较MNC*/
    if (VOS_TRUE == NAS_MML_GetPlmnExactlyComparaFlg())
    {
        bCmpRlst = NAS_MML_ExactlyCompareBcchPlmnwithSimPlmn(pstBccPlmnId, pstSimPlmnId);

        return bCmpRlst;
    }
    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-14, end */

    /* HPLMN Matching Criteria for mobiles which support PCS1900 for NA:
    1) The MS shall compare using all 3 digits the SIM-MCC with the BCCH-MCC.
    If the values do not match, then the HPLMN match fails*/
    if (pstBccPlmnId->ulMcc == pstSimPlmnId->ulMcc)
    {
        /*The MS shall compare using all 3 digits the SIM-MNC with the BCCH-MNC.
          If the values match, then the HPLMN match succeeds*/
        if (pstBccPlmnId->ulMnc == pstSimPlmnId->ulMnc)
        {
            bCmpRlst = VOS_TRUE;
        }
        else if ((pstBccPlmnId->ulMnc & NAS_MML_MCC_LOW_VALUE_MASK)
              == (pstSimPlmnId->ulMnc & NAS_MML_MCC_LOW_VALUE_MASK))
        {
            /* 取MNC的最高位 ,若最高位是0或F，低2位Mnc相同则认为Plmn相等 */
            ucBcchMnc3 = (VOS_UINT8)((pstBccPlmnId->ulMnc & NAS_MML_MCC_THIRD_BYTE_VALUE_MASK) >> 16);
            ucSimMnc3  = (VOS_UINT8)((pstSimPlmnId->ulMnc & NAS_MML_MCC_THIRD_BYTE_VALUE_MASK) >> 16);

            /* PLMN 属于 NA PCS1900*/
            if ((NAS_MML_PCS1900_MCC_LOW_VALUE == (pstBccPlmnId->ulMcc & NAS_MML_MCC_LOW_VALUE_MASK))
             && (NAS_MML_PCS1900_MCC_HIGH_VALUE_RANGE >= (pstBccPlmnId->ulMcc & NAS_MML_MCC_THIRD_BYTE_VALUE_MASK)))
            {
                if ( ((NAS_MML_PCS1900_MNC_THIRD_BYTE_VALUE_F == ucBcchMnc3)
                   && (NAS_MML_PCS1900_MNC_THIRD_BYTE_VALUE_0 == ucSimMnc3))
                  || ((NAS_MML_PCS1900_MNC_THIRD_BYTE_VALUE_0 == ucBcchMnc3)
                   && (NAS_MML_PCS1900_MNC_THIRD_BYTE_VALUE_F == ucSimMnc3)) )
                {
                    bCmpRlst = VOS_TRUE;
                }
            }
            else
            {
                /* The MS shall compare using just the 1st 2 digits of the SIM-MNC
                with the BCCH-MNC. If the values match, then the HPLMN match succeeds,
                otherwise the HPLMN match fails.*/
                if (NAS_MML_LOW_BYTE_INVALID == ucBcchMnc3)
                {
                    bCmpRlst = VOS_TRUE;
                }
            }
        }
        else
        {
        }

    }

    return bCmpRlst;
}

/*****************************************************************************
 函 数 名  : NAS_MML_IsRatSupported
 功能描述  : 判断指定接入技术是否支持
 输入参数  : enSpecRat:指定的接入技术
 输出参数  : 无
 返 回 值  : VOS_TRUE:支持
             VOS_FALSE:不支持
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月18日
   作    者   : z40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_IsNetRatSupported(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enSpecRat
)
{
    VOS_UINT32                          i;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatList = VOS_NULL_PTR;

    pstRatList = NAS_MML_GetMsPrioRatList();

    /* 指定的接入技术是否在当前用户设置的RAT列表中 */
    for (i = 0 ; i < pstRatList->ucRatNum; i++)
    {
        if ( (enSpecRat == pstRatList->aucRatPrio[i])
          && (enSpecRat < NAS_MML_NET_RAT_TYPE_BUTT))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MML_IsSpecRatInRatList
 功能描述  : 判断指定接入技术是否在对应的接入技术列表中
 输入参数  : enSpecRat:指定的接入技术
              pstRatList:接入技术列表
 输出参数  : 无
 返 回 值  : VOS_TRUE:支持
              VOS_FALSE:不支持
 调用函数  :
 被调函数  :

 修改历史      :
    1.日    期   : 2012年5月15日
      作    者   : l00130025
      修改内容   : DTS2012041002516: L下默认承载存在数据连接时设置W only失败
*****************************************************************************/
VOS_UINT32 NAS_MML_IsSpecRatInRatList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enSpecRat,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatList
)
{
    VOS_UINT32                          i;

    /* 指定的接入技术是否在当前用户设置的RAT列表中 */
    for (i = 0 ; i < pstRatList->ucRatNum; i++)
    {
        if ( (enSpecRat == pstRatList->aucRatPrio[i])
          && (enSpecRat < NAS_MML_NET_RAT_TYPE_BUTT))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/* Added by s00246516 for L-C互操作项目, 2014-02-14, Begin */
/*****************************************************************************
 函 数 名  : NAS_MML_IsSpec3Gpp2RatInRatList
 功能描述  : 判断指定3GPP2接入技术是否在对应的接入技术列表中
 输入参数  : enSpec3Gpp2Rat:指定的3GPP2接入技术
              pst3Gpp2RatList:接入技术列表
 输出参数  : 无
 返 回 值  : VOS_TRUE:支持
              VOS_FALSE:不支持
 调用函数  :
 被调函数  :

 修改历史      :
    1.日    期   : 2012年5月15日
      作    者   : l00130025
      修改内容   : DTS2012041002516: L下默认承载存在数据连接时设置W only失败
*****************************************************************************/
VOS_UINT32 NAS_MML_IsSpec3Gpp2RatInRatList(
    NAS_MML_3GPP2_RAT_TYPE_ENUM_UINT8   enSpec3Gpp2Rat,
    NAS_MML_3GPP2_RAT_PRIO_STRU        *pst3Gpp2RatList
)
{
    VOS_UINT32                          i;

    /* 指定的接入技术是否在当前用户设置的RAT列表中 */
    for (i = 0 ; i < pst3Gpp2RatList->ucRatNum; i++)
    {
        if ( (enSpec3Gpp2Rat == pst3Gpp2RatList->aucRatPrio[i])
          && (enSpec3Gpp2Rat < NAS_MML_3GPP2_RAT_TYPE_BUTT))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
/* Added by s00246516 for L-C互操作项目, 2014-02-14, End */

/*****************************************************************************
 函 数 名  : NAS_MML_IsPlmnIdValid
 功能描述  : 判断PLMN ID是否有效
 输出参数  : VOS_VOID
 返 回 值  : VOS_FALSE  : PLMN ID是无效值
             VOS_TRUE : PLMN ID是有效值
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011年07月18日
   作    者   : zhoujun \40661
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsPlmnIdValid(
    NAS_MML_PLMN_ID_STRU                *pstPlmnId
)
{
    VOS_UINT32                          ulResult;

    /*
    The coding of this field is the responsibility of each administration but
    BCD coding shall be used. The MNC shall consist of 2 or 3 digits.
    If a network operator decides to use only two digits in the MNC,
    bits 5 to 8 of octet 7 shall be coded as "1111".
    MCC digit 2     MCC digit 1
    MNC digit 3     MCC digit 3
    MNC digit 2     MNC digit 1
    */

    ulResult = VOS_TRUE;

    if ( ((pstPlmnId->ulMcc & NAS_MML_BYTE_MASK) > NAS_MML_MAX_DIGIT_VALUE)
      || (((pstPlmnId->ulMcc >> 8) & NAS_MML_BYTE_MASK) > NAS_MML_MAX_DIGIT_VALUE)
      || (((pstPlmnId->ulMcc >> 16) & NAS_MML_BYTE_MASK) > NAS_MML_MAX_DIGIT_VALUE))
    {
        ulResult = VOS_FALSE;
    }

    if ((((pstPlmnId->ulMnc) & NAS_MML_BYTE_MASK) > NAS_MML_MAX_DIGIT_VALUE)
     || (((pstPlmnId->ulMnc >> 8) & NAS_MML_BYTE_MASK) > NAS_MML_MAX_DIGIT_VALUE))
    {
        ulResult = VOS_FALSE;
    }

    if ((((pstPlmnId->ulMnc >> 16) & NAS_MML_BYTE_MASK) > NAS_MML_MAX_DIGIT_VALUE)
     && (((pstPlmnId->ulMnc >> 16) & NAS_MML_BYTE_MASK) != NAS_MML_LOW_BYTE_INVALID))
    {
        ulResult = VOS_FALSE;
    }

    return ulResult;
}

/*****************************************************************************
 函 数 名  : NAS_MML_IsMccValid
 功能描述  : 判断国家号是否有效
 输出参数  : VOS_VOID
 返 回 值  : VOS_FALSE : ulMcc是无效值
              VOS_TRUE :  ulMcc是有效值
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2012年08月8日
   作    者   : w00167002
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsMccValid(
    VOS_UINT32                          ulMcc
)
{
    VOS_UINT32                          ulResult;

    /*
    The coding of this field is the responsibility of each administration but
    BCD coding shall be used. The MNC shall consist of 2 or 3 digits.
    If a network operator decides to use only two digits in the MNC,
    bits 5 to 8 of octet 7 shall be coded as "1111".
    MCC digit 2     MCC digit 1
    MNC digit 3     MCC digit 3
    MNC digit 2     MNC digit 1
    */

    ulResult = VOS_TRUE;

    if ( ((ulMcc & NAS_MML_BYTE_MASK) > NAS_MML_MAX_DIGIT_VALUE)
      || (((ulMcc >> NAS_MML_OCTET_MOVE_EIGHT_BITS) & NAS_MML_BYTE_MASK)  > NAS_MML_MAX_DIGIT_VALUE)
      || (((ulMcc >> NAS_MML_OCTET_MOVE_SIXTEEN_BITS) & NAS_MML_BYTE_MASK) > NAS_MML_MAX_DIGIT_VALUE)
      || (((ulMcc >> NAS_MML_OCTET_MOVE_TWENTY_FOUR_BITS) & NAS_MML_BYTE_MASK) != NAS_MML_MCC_FOURTH_BYTES_VALID) )
    {
        ulResult = VOS_FALSE;
    }

    return ulResult;
}


/*****************************************************************************
 函 数 名  : NAS_MML_IsBcchPlmnIdInDestSimPlmnList
 功能描述  : 判断PLMN ID是否在列表中
 输入参数  : pstBcchPlmnId:需要判断的PLMN ID
             ucSimPlmnNum:列表中plmn id的个数
             pstSimPlmnIdList:plmn列表
 输出参数  : 无
 返 回 值  : VOS_TRUE  : PLMN ID在列表中
             VOS_FALSE : PLMN ID不在列表中
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011年07月18日
   作    者   : zhoujun \40661
   修改内容   : 新生成函数

 2.日    期   : 2011年11月24日
   作    者   : w00167002
   修改内容   : DTS2011112405567:更改原有的函数名NAS_MML_IsPlmnIdInDestPlmnList
*****************************************************************************/
VOS_UINT32 NAS_MML_IsBcchPlmnIdInDestSimPlmnList (
    NAS_MML_PLMN_ID_STRU               *pstBcchPlmnId,
    VOS_UINT8                           ucSimPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstSimPlmnIdList
)
{
    VOS_UINT32                          i;

    for ( i = 0; i < ucSimPlmnNum; i++ )
    {
        if ( VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstBcchPlmnId,
                                                            pstSimPlmnIdList+i) )
        {
            return VOS_TRUE;
        }
    }


    return VOS_FALSE;
}



/*****************************************************************************
 函 数 名  : NAS_MML_IsSimPlmnIdInDestBcchPlmnList
 功能描述  : 判断PLMN ID(SIM卡中存储的网络ID)是否在列表中(BCCH类型的网络ID)
 输入参数  : pstSimPlmnId:     需要判断的PLMN ID
              ucBcchPlmnNum:    列表中plmn id的个数
              pstBcchPlmnIdList:plmn列表
 输出参数  : 无
 返 回 值  : VOS_TRUE  : PLMN ID在列表中
              VOS_FALSE : PLMN ID不在列表中
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011年11月24日
   作    者   : w00167002
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsSimPlmnIdInDestBcchPlmnList (
    NAS_MML_PLMN_ID_STRU               *pstSimPlmnId,
    VOS_UINT8                           ucBcchPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstBcchPlmnIdList
)
{
    VOS_UINT32                          i;

    for ( i = 0; i < ucBcchPlmnNum; i++ )
    {
        if ( VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstBcchPlmnIdList + i,
                                                            pstSimPlmnId) )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



/*****************************************************************************
 函 数 名  : NAS_MML_IsBcchPlmnIdInDestSimBcdPlmnList
 功能描述  : 判断Bcch格式的Plmn Id 是否在Sim Bcd格式的Plmn Id列表中
 输入参数  : NAS_MML_PLMN_ID_STRU               *pstBcchPlmnId
             VOS_UINT8                           ucSimPlmnNum
             VOS_UINT8                          *pstSimBcdPlmnIdList
 输出参数  : 无
 返 回 值  : VOS_TRUE: Bcch格式的PlmnId在Sim Bcd格式的PlmnId数组中，反之，返回VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : l00289540
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_IsBcchPlmnIdInDestSimBcdPlmnList(
    NAS_MML_PLMN_ID_STRU               *pstBcchPlmnId,
    VOS_UINT8                           ucSimPlmnNum,
    VOS_UINT8                          *pstSimBcdPlmnIdList
)
{
    NAS_MML_SIM_FORMAT_PLMN_ID          stSimPlmnId;
    NAS_MML_PLMN_ID_STRU                stUserPlmnId;
    VOS_UINT8                           i;

    for (i = 0; i < ucSimPlmnNum; i++)
    {
        PS_MEM_SET(&stSimPlmnId, 0x00, sizeof(NAS_MML_SIM_FORMAT_PLMN_ID));

        stSimPlmnId.aucSimPlmn[0] = pstSimBcdPlmnIdList[(i * NAS_MML_SIM_FORMAT_PLMN_LEN)];
        stSimPlmnId.aucSimPlmn[1] = pstSimBcdPlmnIdList[(i * NAS_MML_SIM_FORMAT_PLMN_LEN) + 1];
        stSimPlmnId.aucSimPlmn[2] = pstSimBcdPlmnIdList[(i * NAS_MML_SIM_FORMAT_PLMN_LEN) + 2];

        NAS_MML_ConvertSimPlmnToNasPLMN(&stSimPlmnId, &stUserPlmnId);

        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstBcchPlmnId, &stUserPlmnId))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MML_IsTheIntersectionOfSpecPlmnListsEmpty
 功能描述  : 判断两个Plmn List是否有交集
 输入参数  : VOS_UINT32                          ulSrcPlmnNum
             NAS_MML_PLMN_ID_STRU               *pstSrcPlmnIdList
             VOS_UINT32                          ulDstPlmnNum
             NAS_MML_PLMN_ID_STRU               *pstDstPlmnIdList
 输出参数  : 无
 返 回 值  : VOS_TRUE: 有交集，VOS_FALSE:无交集
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月1日
    作    者   : l00289540
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_IsTheIntersectionOfSpecPlmnListsEmpty(
    VOS_UINT8                           ucSrcPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstSrcPlmnIdList,
    VOS_UINT8                           ucDstPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstDstPlmnIdList
)
{
    VOS_UINT32                i;

    for (i = 0; i < ucSrcPlmnNum; i++)
    {
        if (VOS_TRUE == NAS_MML_IsSimPlmnIdInDestBcchPlmnList(pstSrcPlmnIdList + i, ucDstPlmnNum, pstDstPlmnIdList))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MML_IsBcchPlmnIdInDestSimPlmnList
 功能描述  : 判断PLMN ID是否在列表中
 输入参数  : pstBcchPlmnId:需要判断的PLMN ID
             usSimPlmnWithRatNum:列表中plmn id的个数
             pstSimPlmnWithRatList:plmn with rat列表
 输出参数  : 无
 返 回 值  : VOS_TRUE  : PLMN ID在列表中
             VOS_FALSE : PLMN ID不在列表中
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2012年8月21日
   作    者   : w00167002
   修改内容   : V7R1C50_GUTL_PhaseII:新建函数
 2.日    期   : 2014年2月12日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加获取和注册请求的处理
*****************************************************************************/
VOS_UINT32 NAS_MML_IsBcchPlmnIdInDestSimPlmnWithRatList (
    NAS_MML_PLMN_ID_STRU               *pstBcchPlmnId,
    VOS_UINT16                          usSimPlmnWithRatNum,
    NAS_MML_SIM_PLMN_WITH_RAT_STRU     *pstSimPlmnWithRatList
)
{
    VOS_UINT32                          i;

    /* Modified by s00246516 for L-C互操作项目, 2014-02-12, Begin */
    for ( i = 0; i < usSimPlmnWithRatNum; i++ )
    /* Modified by s00246516 for L-C互操作项目, 2014-02-12, End */
    {
        if ( VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstBcchPlmnId,
                                                            &pstSimPlmnWithRatList[i].stPlmnId) )
        {
            return VOS_TRUE;
        }
    }


    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MML_IsLaiInDestLaiList
 功能描述  : 判断LAI是否在ForbLa列表中
 输入参数  : pstLai:需要判断的LAI
             ulLaiNum:列表中LAI的个数
             pstLaiList:LAI列表
 输出参数  : 无
 返 回 值  : VOS_TRUE  : LAI在列表中
             VOS_FALSE : LAI不在列表中
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011年07月18日
   作    者   : l00130025
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsLaiInDestLaiList (
    NAS_MML_LAI_STRU                   *pstLai,
    VOS_UINT32                          ulLaiNum,
    NAS_MML_LAI_STRU                   *pstLaiList
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    VOS_BOOL                            bFlg;

    bFlg = VOS_FALSE;

    for ( i = 0; i < ulLaiNum; i++ )
    {
        if ( VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstLai->stPlmnId),
                                                  &(pstLaiList[i].stPlmnId)) )
        {

            for ( j = 0 ; j < NAS_MML_MAX_LAC_LEN ; j++ )
            {
                if (pstLai->aucLac[j] != pstLaiList[i].aucLac[j])
                {
                    break;
                }
            }

            if (NAS_MML_MAX_LAC_LEN == j)
            {
                bFlg = VOS_TRUE;
                break;
            }
        }
    }


    return (bFlg);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetLaiIndexInDestLaiList
 功能描述  : 在ForbLa列表中查找指定LA，存在则获取其Index并返回VOS_TRUE，不存在则
             返回VOS_FALSE
 输入参数  : pstLai: 需要查找的LAI
             ulLaiNum: 列表中LAI的个数
             pstLaiList: LAI列表
 输出参数  : pucLaiIdx: 查找到的LAI的Index
 返 回 值  : VOS_TRUE  : LAI在列表中
             VOS_FALSE : LAI不在列表中
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月28日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_GetLaiIndexInDestLaiList (
    NAS_MML_LAI_STRU                   *pstLai,
    VOS_UINT8                          *pucLaiIdx,
    VOS_UINT8                           ulLaiNum,
    NAS_MML_LAI_STRU                   *pstLaiList
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    VOS_UINT32                          ulFlg;

    ulFlg      = VOS_FALSE;
    *pucLaiIdx = 0;

    for ( i = 0; i < ulLaiNum; i++ )
    {
        if ( VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstLai->stPlmnId),
                                                  &(pstLaiList[i].stPlmnId)) )
        {
            for ( j = 0 ; j < NAS_MML_MAX_LAC_LEN; j++ )
            {
                if (pstLai->aucLac[j] != pstLaiList[i].aucLac[j])
                {
                    break;
                }
            }

            if (NAS_MML_MAX_LAC_LEN == j)
            {
                /* 返回查找的LAI在列表中的index */
                *pucLaiIdx = (VOS_UINT8)i;
                ulFlg = VOS_TRUE;
                break;
            }
        }
    }


    return (ulFlg);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetLaiIndexInRegFailForbLaList
 功能描述  : 在ForbLaList列表中查找指定LA，存在则获取其Index并返回VOS_TRUE，不存在则
             返回VOS_FALSE
 输入参数  : pstLai: 需要查找的LAI
             ulLaiNum: 列表中LAI的个数
             pstRegFailForbLaList: LAI列表
 输出参数  : pucLaiIdx: 查找到的LAI的Index
 返 回 值  : VOS_TRUE  : LAI在列表中
             VOS_FALSE : LAI不在列表中
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年9月24日
   作    者   : g00322017
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_GetLaiIndexInRegFailForbLaList (
    NAS_MML_LAI_STRU                                       *pstLai,
    VOS_UINT8                                              *pucLaiIdx,
    VOS_UINT32                                              ulLaiNum,
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_STRU                 *pstRegFailForbLaList
)
{
    NAS_MML_LAI_STRU                   *pstNasMmlLai = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT32                          ulFlg;

    ulFlg      = VOS_FALSE;
    *pucLaiIdx = 0;

    for ( i = 0; i < ulLaiNum; i++ )
    {
        pstNasMmlLai = &(pstRegFailForbLaList[i].stForbLaWithValidPeriodLai);
        if (VOS_TRUE == NAS_MML_CompareLai(pstLai, pstNasMmlLai))
        {
            /* 返回查找的LAI在列表中的index */
            *pucLaiIdx = (VOS_UINT8)i;
            ulFlg = VOS_TRUE;
            break;
        }
    }

    return (ulFlg);
}

/*****************************************************************************
 函 数 名  : NAS_MML_AddCustomizedForbLaToDestLaList
 功能描述  : 在tForbLaWithValidPeriod列表中LA,如果不在pstForbRomLaList列表中，
             则加入pstForbRomLaList列表，并且pucForbRoamLaNum跟着递增

 输入参数  :
             pucForbRoamLaNum: 列表中LAI的个数
             pstForbRomLaList: LAI列表
 输出参数  :
             pucForbRoamLaNum: 列表中LAI的个数
             pstForbRomLaList: LAI列表
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年9月24日
   作    者   : g00322017
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_AddCustomizedForbLaToDestLaList(
    VOS_UINT8                          *pucDestLaNum,
    NAS_MML_LAI_STRU                   *pstDestLaList
)
{
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU            *pstForbLaWithValidPeriodList = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                                       *pstLai                       = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    pstForbLaWithValidPeriodList = NAS_MML_GetForbLaWithValidPeriodList();
    for ( i = 0; i < pstForbLaWithValidPeriodList->ulForbLaWithValidPeriodNum; i++ )
    {
        pstLai = &(pstForbLaWithValidPeriodList->astForbLaWithValidPeriodList[i].stForbLaWithValidPeriodLai);
        if ( (VOS_FALSE == NAS_MML_IsLaiInDestLaiList(pstLai, *pucDestLaNum, pstDestLaList))
          && ( (*pucDestLaNum) < RRC_MAX_FORBLA_NUM) )
        {
            PS_MEM_CPY(&(pstDestLaList[*pucDestLaNum]) ,
                pstLai, sizeof(NAS_MML_LAI_STRU));
            (*pucDestLaNum)++;
        }
    }
}

/*****************************************************************************
 函 数 名  : NAS_MML_IsInForbLaWithValidPeriodList
 功能描述  : 判断LAI是否在ForbLaWithValidPeriod列表
 输入参数  : NAS_MML_LAI_STRU LAI信息
 输出参数  : 无
 返 回 值  : VOS_TRUE  : 在禁止位置区中
             VOS_FALSE : 不在禁止位置区中
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年09月28日
   作    者   : g00322017
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsInForbLaWithValidPeriodList(
    NAS_MML_LAI_STRU                    *pstLai
)
{
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU            *pstForbLaWithValidPeriod    = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                                       *pstTmpLai                   = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    pstForbLaWithValidPeriod = NAS_MML_GetForbLaWithValidPeriodList();

    /* LA在"forbidden las for regional" list */
    for (i = 0; i < pstForbLaWithValidPeriod->ulForbLaWithValidPeriodNum; i++)
    {
        pstTmpLai = &(pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].stForbLaWithValidPeriodLai);
        if (VOS_TRUE == NAS_MML_CompareLai(pstLai, pstTmpLai))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MML_ComparePlmnIdWithHplmn
 功能描述  : 判断PLMN是否是HPLMN
 输入参数  : pstPlmnId:需要比较的PLMNID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年07月22日
   作    者   : zhoujun \40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_ComparePlmnIdWithHplmn (
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstEhplmnInfo = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstEhplmnInfo = NAS_MML_GetSimEhplmnList();

    for (i = 0; i < pstEhplmnInfo->ucEhPlmnNum; i++)
    {
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstPlmnId,
                                                           &(pstEhplmnInfo->astEhPlmnInfo[i].stPlmnId)))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/* Added by s00246516 for L-C互操作项目, 2014-02-12, Begin */
/*****************************************************************************
 函 数 名  : NAS_MML_ComparePlmnIdWithUplmn
 功能描述  : 判断PLMN是否是UPLMN
 输入参数  : pstPlmnId:需要比较的PLMNID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年02月21日
   作    者   : s00246516
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_ComparePlmnIdWithUplmn (
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MML_SIM_USERPLMN_INFO_STRU     *pstUserPlmnList = VOS_NULL_PTR;
    NAS_MML_SIM_OPERPLMN_INFO_STRU     *pstOperPlmnList = VOS_NULL_PTR;
    NAS_MML_SIM_SELPLMN_INFO_STRU      *pstSelPlmnList  = VOS_NULL_PTR;

    /* 获取UOPLMN */
    pstUserPlmnList = NAS_MML_GetSimUserPlmnList();
    pstOperPlmnList = NAS_MML_GetSimOperPlmnList();

    /* UPLMN个数不为0或者OPLMN个数不为0 */
    if ((pstUserPlmnList->ucUserPlmnNum > 0)
     || (pstOperPlmnList->usOperPlmnNum > 0))
    {
        if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnWithRatList(pstPlmnId,
                                                      pstUserPlmnList->ucUserPlmnNum,
                                                      pstUserPlmnList->astUserPlmnInfo))
        {
            return VOS_TRUE;
        }
    }
    else /* 表示(U)SIM卡中不存在UPLMN、OPLMN，使用PLMN Sel文件 */
    {
        pstSelPlmnList = NAS_MML_GetSimSelPlmnList();

        if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstPlmnId,
                                                      pstSelPlmnList->ucSelPlmnNum,
                                                      pstSelPlmnList->astPlmnId))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MML_ComparePlmnIdWithOplmn
 功能描述  : 判断PLMN是否是OPLMN
 输入参数  : pstPlmnId:需要比较的PLMNID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年02月21日
   作    者   : s00246516
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_ComparePlmnIdWithOplmn (
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MML_SIM_USERPLMN_INFO_STRU     *pstUserPlmnList = VOS_NULL_PTR;
    NAS_MML_SIM_OPERPLMN_INFO_STRU     *pstOperPlmnList = VOS_NULL_PTR;
    NAS_MML_SIM_SELPLMN_INFO_STRU      *pstSelPlmnList  = VOS_NULL_PTR;

    /* 获取UOPLMN */
    pstUserPlmnList = NAS_MML_GetSimUserPlmnList();
    pstOperPlmnList = NAS_MML_GetSimOperPlmnList();

    /* UPLMN个数不为0或者OPLMN个数不为0 */
    if ((pstUserPlmnList->ucUserPlmnNum > 0)
     || (pstOperPlmnList->usOperPlmnNum > 0))
    {
        if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnWithRatList(pstPlmnId,
                                                      pstOperPlmnList->usOperPlmnNum,
                                                      pstOperPlmnList->astOperPlmnInfo))
        {
            return VOS_TRUE;
        }
    }
    else /* 表示(U)SIM卡中不存在UPLMN、OPLMN，使用PLMN Sel文件 */
    {
        pstSelPlmnList = NAS_MML_GetSimSelPlmnList();

        if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstPlmnId,
                                                      pstSelPlmnList->ucSelPlmnNum,
                                                      pstSelPlmnList->astPlmnId))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
/* Added by s00246516 for L-C互操作项目, 2014-02-12, End */

/*****************************************************************************
 函 数 名  : NAS_MML_IsPlmnIdRoamingAllowed
 功能描述  : 判断PLMN ID是否允许漫游
 输入参数  : pstPlmnId:需要判断的PLMN ID
 输出参数  : 无
 返 回 值  : VOS_TRUE  : PLMN ID允许漫游
             VOS_FALSE : PLMN ID不允许漫游
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011年07月18日
   作    者   : zhoujun \40661
   修改内容   : 新生成函数
 2.日    期   : 2011年11月24日
   作    者   : w00167002
   修改内容   : DTS2011112405567:原有的函数名NAS_MML_IsPlmnIdInDestPlmnList
                更改为NAS_MML_IsSimPlmnIdInDestBcchPlmnList,明确网络的比较类型，
                否则可能导致比较出错。
*****************************************************************************/
VOS_UINT32 NAS_MML_IsPlmnIdRoamingAllowed(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MML_ROAM_CFG_INFO_STRU         *pstRoamCfg = VOS_NULL_PTR;
    VOS_UINT32                          ulFlg;

    pstRoamCfg        = NAS_MML_GetRoamCfg();

    /*与HPLMN相同，直接返回允许*/
    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(pstPlmnId))
    {
        return VOS_TRUE;
    }

    /*漫游特性开关关闭，直接返回允许*/
    if (VOS_FALSE == pstRoamCfg->ucRoamFeatureFlg )
    {
        return VOS_TRUE;
    }

    /*允许漫游时直接返回允许*/
    if (NAS_MML_ROAM_NATION_ON_INTERNATION_ON == pstRoamCfg->enRoamCapability)
    {
        return VOS_TRUE;
    }

    /*允许国内漫游时,如果是用户列表搜索结果显示,则搜索和显示所有国内网，
      包括50506，50599，00101，50501, 以及Optus 2G,3G, Vodafone 2G 3G；
      如果不是用户列表搜索结果显示，可以注册或漫游到50501 */
    ulFlg = NAS_MML_IsSimPlmnIdInDestBcchPlmnList( pstPlmnId,
                                            pstRoamCfg->ucNationalRoamNum,
                                            pstRoamCfg->astRoamPlmnIdList );
    if ( (NAS_MML_ROAM_NATION_ON_INTERNATION_OFF == pstRoamCfg->enRoamCapability)
      && (VOS_TRUE                               == ulFlg) )
    {
        return VOS_TRUE;
    }

    /*不允许国内漫游时，不能漫游到任何网络 */
    ulFlg = NAS_MML_IsSimPlmnIdInDestBcchPlmnList( pstPlmnId,
                                                   pstRoamCfg->ucNotRoamNum,
                                                   pstRoamCfg->astRoamPlmnIdList );
    if ( ( (NAS_MML_ROAM_NATION_OFF_INTERNATION_ON == pstRoamCfg->enRoamCapability)
        || (NAS_MML_ROAM_NATION_OFF_INTERNATION_OFF == pstRoamCfg->enRoamCapability) )
      && (VOS_TRUE == ulFlg) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 函 数 名  : NAS_MML_IsSupportLteCsg
 功能描述  : 确定当前是否支持LTE CSG功能
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 支持LTE CSG功能
             VOS_FALSE - 不支持LTE CSG功能
 调用函数  :
 被调函数  :

 修改历史
  1.日    期   : 2015年9月11日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32 NAS_MML_IsSupportLteCsg(VOS_VOID)
{
    /* syscfg设置不支持Lte,返回false */
    if ( VOS_FALSE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
    {
        return VOS_FALSE;
    }

    /* CSG NV项关闭，返回false */
    if (VOS_FALSE == NAS_MML_GetCsgSupportFlag())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

#endif




/*****************************************************************************
 函 数 名  : NAS_MML_GetVoiceNotPreferDisabledPlmnForbiddenTimeSlice
 功能描述  : 获取禁止接入技术网络惩罚时间对应的time slice
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年4月24日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT32 NAS_MML_GetVoiceNotPreferDisabledPlmnForbiddenTimeSlice(VOS_VOID)
{
    VOS_UINT32                          ulDisabledPlmnInvalidPeriod;
    VOS_UINT32                          ulInvalidTimeSlice;

    ulDisabledPlmnInvalidPeriod = NAS_MML_GetVoiceNotAvailPlmnForbiddenPeriod();
    ulInvalidTimeSlice          = 0;

    if (NAS_MML_MAX_TIME_SLICE == ulDisabledPlmnInvalidPeriod)
    {
        return NAS_MML_MAX_TIME_SLICE;
    }

    ulInvalidTimeSlice = VOS_GetSliceUnit() * (ulDisabledPlmnInvalidPeriod / 1000);
    return ulInvalidTimeSlice;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetDisabledPlmnRejCause42ForbiddenTimeSlice
 功能描述  : 获取由于注册，业务请求被拒#42加入禁止接入技术网络惩罚时间对应的time slice
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年4月24日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT32 NAS_MML_GetDisabledPlmnRejCause42ForbiddenTimeSlice(VOS_VOID)
{
    VOS_UINT32                          ulInvalidTimeSlice;
    VOS_UINT32                          ulDisabledPlmnForbiddenPeriod;

    ulInvalidTimeSlice          = 0;
    ulDisabledPlmnForbiddenPeriod = 2 * NAS_MML_GetSimHplmnTimerLen();

    ulInvalidTimeSlice = VOS_GetSliceUnit() * (ulDisabledPlmnForbiddenPeriod / 1000);
    return ulInvalidTimeSlice;
}


/*****************************************************************************
 函 数 名  : NAS_MML_IsNeedAddVoiceNotAvailDisabledPlmnInDisabledPlmnWithForbiddenPeriodList
 功能描述  : 是否需要将语音不支持disable lte的网络加入禁止接入技术网络网络列表
 输入参数  : pstPlmnWithRat          - 禁止接入技术网络信息
             enCsRegCause            - CS被拒原因值
             enPsRegCause            - PS被拒原因值
             enAdditionUpdatRsltInfo - 注册结果中additional update result信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年4月24日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改

*****************************************************************************/
VOS_UINT32 NAS_MML_IsNeedAddVoiceNotAvailDisabledPlmnInDisabledPlmnWithForbiddenPeriodList(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstPlmnWithRat,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegCause,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegCause,
    NAS_MML_ADDITION_UPDATE_RSLT_INFO_ENUM_UINT8            enAdditionUpdatRsltInfo
)
{
    /* 如果协议版本小于r11，无需加入，返回false */
    if (NAS_MML_GetLte3gppRelVersion() < NAS_MML_3GPP_REL_R11)
    {
        return VOS_FALSE;
    }

    /* 如果pstPlmnWithRat已经在禁止接入技术网络列表中则无需处理 */
    if (VOS_TRUE == NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList(pstPlmnWithRat))
    {
        return VOS_FALSE;
    }


    /* 24301_CR1460R4_(Rel-11)_C1-123383 和24301_CR1527R1_(Rel-11)_C1-123937和
      24301_CR1504R1_(Rel-11)_C1-123388 rev of C1-122853 E-UTRA disabling clarification - v6
      对应24301 4.5章节:If UE that has disabled its E-UTRA capability due to IMS
      voice not available and CS fallback not available re-enables it when PLMN
      selection is performed, then it should memorize the identity of the PLMNs
      where E-UTRA capability was disabled and use that stored information in
      subsequent PLMN selections as specified in 3GPP TS 23.122 [6]. 该CR受协议版本控制 */
    if ((((NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE == enCsRegCause)
       || (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE == enCsRegCause)
       || (NAS_MML_REG_FAIL_CAUSE_CS_DOMAIN_NOT_AVAILABLE == enCsRegCause))
     && (NAS_MML_REG_FAIL_CAUSE_NULL == enPsRegCause))
     || (NAS_MML_ADDITION_UPDATE_RSLT_SMS_ONLY == enAdditionUpdatRsltInfo)
     || (NAS_MML_ADDITION_UPDATE_RSLT_CSFB_NOT_PREFERRED == enAdditionUpdatRsltInfo))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetPlmnWithRatIndexInDestDisabledPlmnWithForbiddenPeriodList
 功能描述  : 获取plmn在禁止接入技术网络列表中的索引
 输入参数  : pstSrcPlmnId:需要判断的PLMN ID
             ulDestPlmnNum:禁止plmn id的个数
             pstDestPlmnIdList:禁止plmn列表
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年4月23日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT32 NAS_MML_GetPlmnWithRatIndexInDestDisabledPlmnWithForbiddenPeriodList (
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstSrcPlmnId,
    VOS_UINT32                                              ulDestPlmnNum,
    NAS_MML_DISABLED_PLMN_WITH_FORBIDDEN_PERIOD_STRU       *pstDestPlmnIdList
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulIndex;

    ulIndex = ulDestPlmnNum;

    if (ulIndex > NAS_MML_MAX_DISABLED_RAT_PLMN_NUM)
    {
        ulIndex = NAS_MML_MAX_DISABLED_RAT_PLMN_NUM;
    }

    for ( i = 0; i < ulIndex; i++ )
    {
        if ((VOS_TRUE               == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstSrcPlmnId->stPlmnId), &(pstDestPlmnIdList[i].stPlmnWithRat.stPlmnId)))
         && (pstSrcPlmnId->enRat    == pstDestPlmnIdList[i].stPlmnWithRat.enRat))
        {
            break;
        }
    }

    return i;
}

/*****************************************************************************
 函 数 名  : NAS_MML_DeleteSpecDisabledPlmnWithValidPeriodInPlmnList
 功能描述  : 从禁止接入技术网络中删除指定网络
 输入参数  : pstPlmnWithRat - 网络信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年4月23日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID NAS_MML_DeleteSpecDisabledPlmnWithValidPeriodInPlmnList(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstPlmnWithRat
)
{
    NAS_MML_DISABLED_RAT_PLMN_CFG_INFO_STRU                *pstDisabledPlmnIdWithRatList = VOS_NULL_PTR;
    VOS_UINT32                                              ulIdx;

    pstDisabledPlmnIdWithRatList = NAS_MML_GetDisabledRatPlmnInfo();

    /* 获取删除plmn在禁止接入技术网络列表中 */
    ulIdx = NAS_MML_GetPlmnWithRatIndexInDestDisabledPlmnWithForbiddenPeriodList(pstPlmnWithRat,
                                                 pstDisabledPlmnIdWithRatList->ulDisabledRatPlmnNum,
                                                 pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId);

    /* 找到对应的PlmnId,删除 */
    if (ulIdx < pstDisabledPlmnIdWithRatList->ulDisabledRatPlmnNum)
    {
        if (ulIdx == (pstDisabledPlmnIdWithRatList->ulDisabledRatPlmnNum - 1))
        {
            pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIdx].stPlmnWithRat.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
            pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIdx].stPlmnWithRat.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
            pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIdx].stPlmnWithRat.enRat = NAS_MML_NET_RAT_TYPE_BUTT;
            pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIdx].ulPlmnDisabledForbiddenSlice   = NAS_MML_MAX_TIME_SLICE;
            pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIdx].ulPlmnDisabledBeginSlice = 0;
        }
        else
        {
            PS_MEM_MOVE(pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId + ulIdx,
              (pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId + (ulIdx + 1)),
              (NAS_MML_MAX_DISABLED_RAT_PLMN_NUM - (ulIdx + 1)) * sizeof(NAS_MML_DISABLED_PLMN_WITH_FORBIDDEN_PERIOD_STRU));
        }

        pstDisabledPlmnIdWithRatList->ulDisabledRatPlmnNum--;
    }

    NAS_MMC_LogForbiddenPlmnRelatedInfo();
    return;
}


/*****************************************************************************
 函 数 名  : NAS_MML_DeleteExpireValidPeriodPlmnInDisabledRatPlmnList
 功能描述  : 判断禁止接入技术网络中是否存在惩罚时间到的网络，如果存在则删除
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年4月23日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT32 NAS_MML_DeleteExpireValidPeriodPlmnInDisabledRatPlmnList(VOS_VOID)
{
    NAS_MML_DISABLED_RAT_PLMN_CFG_INFO_STRU                *pstDisabledPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulIndex;
    VOS_UINT32                                              ulIsNeedDeleteDisabledPlmnWithRat;

    pstDisabledPlmnInfo               = NAS_MML_GetDisabledRatPlmnInfo();
    ulIsNeedDeleteDisabledPlmnWithRat = VOS_FALSE;

    for (ulIndex = 0; ulIndex < pstDisabledPlmnInfo->ulDisabledRatPlmnNum;)
    {
        if (VOS_TRUE == NAS_MML_IsNeedDeleteDisabledPlmnWithValidPeriodInPlmnList(&pstDisabledPlmnInfo->astDisabledRatPlmnId[ulIndex]))
        {
            if (ulIndex < pstDisabledPlmnInfo->ulDisabledRatPlmnNum - 1)
            {
                PS_MEM_MOVE(&(pstDisabledPlmnInfo->astDisabledRatPlmnId[ulIndex]),
                            &(pstDisabledPlmnInfo->astDisabledRatPlmnId[ulIndex+1]),
                             (pstDisabledPlmnInfo->ulDisabledRatPlmnNum-ulIndex-1)*sizeof(NAS_MML_DISABLED_PLMN_WITH_FORBIDDEN_PERIOD_STRU));
            }

            (pstDisabledPlmnInfo->ulDisabledRatPlmnNum)--;

            ulIsNeedDeleteDisabledPlmnWithRat = VOS_TRUE;

            NAS_MMC_LogForbiddenPlmnRelatedInfo();

            if (ulIndex > 0 )
            {
                ulIndex--;
            }
            else
            {
                continue;
            }

        }

        ulIndex++;
    }

    /* 如果禁止接入技术网络列表中还存在非NV配置的网络禁止期限为全F，则继续启动周期删除禁止接入技术网络列表定时器 */
    for (ulIndex = 0; ulIndex < pstDisabledPlmnInfo->ulDisabledRatPlmnNum; ulIndex++)
    {
        if (NAS_MML_MAX_TIME_SLICE != pstDisabledPlmnInfo->astDisabledRatPlmnId[ulIndex].ulPlmnDisabledForbiddenSlice)
        {
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_DELETE_DISABLED_PLMN_WITH_RAT_TIMER,
                              TI_NAS_MMC_PERIOD_DELETE_DISABLED_PLMN_WITH_RAT_TIMER_LEN);
            break;
        }
    }

    return ulIsNeedDeleteDisabledPlmnWithRat;
}

/*****************************************************************************
 函 数 名  : NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList
 功能描述  : 判断带接入技术的PLMN ID是否在带接入技术的禁止PLMN ID列表中
 输入参数  : pstSrcPlmnId:需要判断的PLMN ID

 输出参数  : 无
 返 回 值  : VOS_TRUE  : PLMN ID在列表中
             VOS_FALSE : PLMN ID不在列表中
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年1月14日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改
 2.日    期   : 2015年4月23日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT32 NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList (
    NAS_MML_PLMN_WITH_RAT_STRU         *pstSrcPlmnId
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulIndex;

    NAS_MML_DISABLED_RAT_PLMN_CFG_INFO_STRU                *pstDisabledPlmnInfo = VOS_NULL_PTR;

    pstDisabledPlmnInfo = NAS_MML_GetDisabledRatPlmnInfo();

    /* 使用禁止接入技术网络列表前先判断下是否有惩罚时间到的网络，如果有先删除 */
    (VOS_VOID)NAS_MML_DeleteExpireValidPeriodPlmnInDisabledRatPlmnList();

    ulIndex = pstDisabledPlmnInfo->ulDisabledRatPlmnNum;

    if (ulIndex > NAS_MML_MAX_DISABLED_RAT_PLMN_NUM)
    {
        ulIndex = NAS_MML_MAX_DISABLED_RAT_PLMN_NUM;
    }

    for ( i = 0; i < ulIndex; i++ )
    {
        if ((VOS_TRUE               == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstSrcPlmnId->stPlmnId), &(pstDisabledPlmnInfo->astDisabledRatPlmnId[i].stPlmnWithRat.stPlmnId)))
         && (pstSrcPlmnId->enRat    == pstDisabledPlmnInfo->astDisabledRatPlmnId[i].stPlmnWithRat.enRat))
        {
            NAS_NORMAL_LOG3(WUEPS_PID_MMC, "NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList IS TRUE,MCC,MNC,RAT",pstSrcPlmnId->stPlmnId.ulMcc,pstSrcPlmnId->stPlmnId.ulMnc,pstSrcPlmnId->enRat);        
        
            return VOS_TRUE;
        }
    }


    return VOS_FALSE;
}




/*****************************************************************************
 函 数 名  : NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnRatList
 功能描述  : 判断带接入技术的PLMN ID是否在带接入技术的禁止PLMN ID列表中
 输入参数  : pstSrcPlmnId:需要判断的PLMN ID
             ulDestPlmnNum:禁止plmn id的个数
             pstDestPlmnIdList:禁止plmn列表
 输出参数  : 无
 返 回 值  : VOS_TRUE  : PLMN ID在列表中
             VOS_FALSE : PLMN ID不在列表中
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年8月18日
   作    者   : w00167002
   修改内容   : DTS2015071604422修改
*****************************************************************************/
VOS_UINT32 NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnRatList (
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstSrcPlmnId,
    VOS_UINT32                                              ulDestPlmnNum,
    NAS_MML_DISABLED_PLMN_WITH_FORBIDDEN_PERIOD_STRU       *pstDestPlmnIdList
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulIndex;

    ulIndex = ulDestPlmnNum;

    if (ulIndex > NAS_MML_MAX_DISABLED_RAT_PLMN_NUM)
    {
        ulIndex = NAS_MML_MAX_DISABLED_RAT_PLMN_NUM;
    }

    for ( i = 0; i < ulIndex; i++ )
    {
        if ((VOS_TRUE               == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstSrcPlmnId->stPlmnId), &(pstDestPlmnIdList[i].stPlmnWithRat.stPlmnId)))
         && (pstSrcPlmnId->enRat    == pstDestPlmnIdList[i].stPlmnWithRat.enRat))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



/*****************************************************************************
 函 数 名  : NAS_MML_IsBcchPlmnIdInLockPlmnList
 功能描述  : 判断PLMN ID是否在锁网的PLMN列表中
 输入参数  : pstBcchPlmnId:需要判断的PLMN ID
 输出参数  : 无
 返 回 值  : VOS_TRUE  : PLMN ID在列表中
             VOS_FALSE : PLMN ID不在列表中
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2012年10月12日
   作    者   : wenlutao \00176964
   修改内容   : 新生成函数
 2.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式
 3.日    期   : 2015年1月15日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
 4.日    期   : 2015年4月23日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT32 NAS_MML_IsBcchPlmnIdInLockPlmnList (
    NAS_MML_PLMN_ID_STRU               *pstBcchPlmnId
)
{
    NAS_MML_PLMN_LOCK_CFG_INFO_STRU                        *pstPlmnLockInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList       = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnWithRat;
    VOS_UINT32                                              ulIndex;
    VOS_UINT32                                              ulDisabledPlmnFlg;
    VOS_UINT32                                              ulRatDisabledFlg;

    /* 获取当前接入技术优先级信息 */
    pstPrioRatList          = NAS_MML_GetMsPrioRatList();

    pstPlmnLockInfo         = NAS_MML_GetPlmnLockCfg();

    ulDisabledPlmnFlg       = VOS_TRUE;

    ulRatDisabledFlg        = VOS_TRUE;

    /* E5形态PLMN ID在黑名单中 */
    if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstBcchPlmnId,
                                                          pstPlmnLockInfo->ucBlackPlmnLockNum,
                                                          pstPlmnLockInfo->astBlackPlmnId))
    {
        return VOS_TRUE;
    }

    /* 构造带接入技术的PLMN ID */
    stPlmnWithRat.stPlmnId.ulMcc    = pstBcchPlmnId->ulMcc;
    stPlmnWithRat.stPlmnId.ulMnc    = pstBcchPlmnId->ulMnc;

    /* 遍历UE支持的接入技术,如果PLMN ID在禁止接入技术的黑名单网络里, 而且当前UE
       支持的接入技术都被禁止,则认为该PLMN ID是禁止网络 */
    for (ulIndex = 0; ulIndex < pstPrioRatList->ucRatNum; ulIndex++)
    {
        stPlmnWithRat.enRat   = pstPrioRatList->aucRatPrio[ulIndex];

        if (VOS_FALSE == NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
        {
            ulDisabledPlmnFlg = VOS_FALSE;
            break;
        }
    }

    /* 该PLMN ID支持的接入技术都在禁止RAT的PLMN 列表中 */
    if (VOS_TRUE == ulDisabledPlmnFlg)
    {
        return VOS_TRUE;
    }

    for (ulIndex = 0; ulIndex < pstPrioRatList->ucRatNum; ulIndex++)
    {
        stPlmnWithRat.enRat   = pstPrioRatList->aucRatPrio[ulIndex];

        if (VOS_FALSE == NAS_MML_IsRatInForbiddenList(stPlmnWithRat.enRat))
        {
            ulRatDisabledFlg = VOS_FALSE;
            break;
        }
    }

    if (VOS_TRUE == ulRatDisabledFlg)
    {
        return VOS_TRUE;
    }

    /* 白名单个数为0表示未开启白名单特性,E5形态PLMN ID不在白名单中 */
    if (pstPlmnLockInfo->ucWhitePlmnLockNum > 0)
    {
        if (VOS_FALSE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstBcchPlmnId,
                                                               pstPlmnLockInfo->ucWhitePlmnLockNum,
                                                               pstPlmnLockInfo->astWhitePlmnId))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MML_IsPlmnIdInForbidPlmnList
 功能描述  : 判断PLMN ID是否在禁止列表中
 输入参数  : pstPlmnId:需要判断的PLMN ID
 输出参数  : 无
 返 回 值  : VOS_TRUE  : PLMN ID在禁止列表中
             VOS_FALSE : PLMN ID不在禁止列表中
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011年07月18日
   作    者   : zhoujun \40661
   修改内容   : 新生成函数
 2.日    期   : 2011年11月24日
   作    者   : w00167002
   修改内容   : DTS2011112405567:原有的函数名NAS_MML_IsPlmnIdInDestPlmnList
                更改为NAS_MML_IsSimPlmnIdInDestBcchPlmnList,明确网络的比较类型，
                否则可能导致比较出错。
 3.日    期   : 2012年03月03日
   作    者   : s62952
   修改内容   : BalongV300R002 Build优化项目:删除NAS_FEATURE_BLACK_WHITE_PLMN宏
 4.日    期   : 2012年10月11日
   作    者   : w00176964
   修改内容   : DTS201201002303:【移动定制黑名单】驻留TD小区,指定搜黑名单网络,NAS发起anycell
                搜驻留W小区后，依然启动available timer
*****************************************************************************/
VOS_UINT32 NAS_MML_IsPlmnIdInForbidPlmnList(
    NAS_MML_PLMN_ID_STRU                *pstPlmnId
)
{
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo = VOS_NULL_PTR;
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode;
    VOS_UINT32                          ulRet;

    pstForbidPlmnInfo = NAS_MML_GetForbidPlmnInfo();
    enMsMode          = NAS_MML_GetMsMode();

    /* 在forbid plmn列表中 */
    if(VOS_TRUE == NAS_MML_IsSimPlmnIdInDestBcchPlmnList(pstPlmnId,
                                          pstForbidPlmnInfo->ucForbPlmnNum,
                                          pstForbidPlmnInfo->astForbPlmnIdList))
    {
        return VOS_TRUE;
    }

    /* 该PLMN ID是否在锁网锁卡的PLMN 列表中 */
    if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInLockPlmnList(pstPlmnId))
    {
        return VOS_TRUE;
    }

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    /* 不允许漫游时 */
    if (VOS_FALSE == NAS_MML_IsPlmnIdRoamingAllowed(pstPlmnId))
    {
        return VOS_TRUE;
    }

    ulRet = NAS_MML_IsSimPlmnIdInDestBcchPlmnList(pstPlmnId,
                                              pstForbidPlmnInfo->ucForbGprsPlmnNum,
                                              pstForbidPlmnInfo->astForbGprsPlmnList);

    /* 在forbid plmn for gprs列表中 */
    if ( ( NAS_MML_MS_MODE_PS_ONLY == enMsMode)
      && ( VOS_TRUE == ulRet ))
    {
        return VOS_TRUE;
    }

    /* A模式时CS域卡无效时 */
    if ( ( VOS_FALSE             == NAS_MML_GetSimCsRegStatus())
      && ( NAS_MML_MS_MODE_PS_CS == enMsMode)
      && ( VOS_TRUE              == ulRet))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MML_IsRrcConnExist
 功能描述  : 判断当前是否存在信令链接
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:当前模下存在信令链接
              VOS_FALSE:当前模下不存在信令链接
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月11日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_IsRrcConnExist( VOS_VOID )
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat;

    /* 取得当前的接入模式 */
    enCurrRat     = NAS_MML_GetCurrNetRatType();

    /* 取得当前的链接信息 */
    pstConnStatus = NAS_MML_GetConnStatus();

    switch ( enCurrRat )
    {
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:

            /* 当前模在L下，存在信令链接或者数据链接 */
            if ( (VOS_TRUE == pstConnStatus->ucEpsSigConnStatusFlg)
              || (VOS_TRUE == pstConnStatus->ucEpsServiceConnStatusFlg) )
            {
                return VOS_TRUE;
            }

            /* 不存在返回FALSE */
            return VOS_FALSE;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:

            /* 当前模在W下，存在信令链接或者数据链接 */
            if ( (VOS_TRUE == pstConnStatus->ucRrcStatusFlg)
              || (VOS_TRUE == pstConnStatus->ucPsSigConnStatusFlg)
              || (VOS_TRUE == pstConnStatus->ucCsSigConnStatusFlg) )
            {
                return VOS_TRUE;
            }

            /* 不存在返回FALSE */
            return VOS_FALSE;

        case NAS_MML_NET_RAT_TYPE_GSM:

            /* 当前模在G下，存在信令链接或者数据链接 */
            if ( (VOS_TRUE == pstConnStatus->ucRrcStatusFlg)
              || (VOS_TRUE == pstConnStatus->ucCsSigConnStatusFlg)
              || (VOS_TRUE == pstConnStatus->ucPsTbfStatusFlg) )
            {
                return VOS_TRUE;
            }

            /* 不存在返回FALSE */
            return VOS_FALSE;

        default:

            /* 无法解析的接入模式，打印异常，按照链接不存在返回 */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MML_IsRrcConnExist,WARNING:无法解析的接入模式");

            return VOS_FALSE;
    }

}


/*****************************************************************************
 函 数 名  : NAS_MML_IsQuickStartFlg
 功能描述  : 判断是否是快速开机模式
 输入参数  : 无
 输出参数  : VOS_TRUE:是快速开机模式
             VOS_FALSE:非快速开机模式
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月27日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数
  2.日    期   : 2012年12月13日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  3.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : svlte和usim接口调整
*****************************************************************************/
VOS_UINT32  NAS_MML_IsQuickStartFlg( VOS_VOID )
{
    VOS_UINT8                           ucCardStatus;
    VOS_UINT8                           ucCardType;
    VOS_UINT32                          ulQuickStartFlag;


    ucCardStatus = USIMM_CARD_SERVIC_BUTT;
    ucCardType   = USIMM_CARD_NOCARD;

    if ( USIMM_API_SUCCESS != NAS_USIMMAPI_GetCardType(&ucCardStatus, &ucCardType) )
    {
        return VOS_TRUE;
    }
    if ( USIMM_CARD_ROM_SIM == ucCardType )
    {
        ulQuickStartFlag    = VOS_TRUE;
    }
    else
    {
        ulQuickStartFlag    = VOS_FALSE;
    }

    return ulQuickStartFlag;
}

/*****************************************************************************
 函 数 名  : NAS_MML_IsTmsiValid
 功能描述  : 判断TMSI是否有效
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  : TMSI有效
             VOS_FALSE : TMSI无效
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011年07月27日
   作    者   : h44270
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsTmsiValid(VOS_VOID)
{
    VOS_UINT8                          *pucTmsi = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pucTmsi = NAS_MML_GetUeIdTmsi();

    for ( i = 0; i < NAS_MML_MAX_TMSI_LEN; i++ )
    {
        if ( NAS_MML_TMSI_INVALID != pucTmsi[i] )
        {
            return VOS_TRUE;
        }
    }


    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MML_IsPtmsiValid
 功能描述  : 判断PTMSI是否有效
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  : PTMSI有效
             VOS_FALSE : PTMSI无效
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2012年03月03日
   作    者   : L65478
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsPtmsiValid(VOS_VOID)
{
    VOS_UINT8                          *pucPtmsi = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pucPtmsi = NAS_MML_GetUeIdPtmsi();

    for ( i = 0; i < NAS_MML_MAX_PTMSI_LEN; i++ )
    {
        if ( NAS_MML_PTMSI_INVALID != pucPtmsi[i] )
        {
            return VOS_TRUE;
        }
    }


    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetGsmForbidFlg
 功能描述  : 获取GSM是否需要禁止接入信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回GSM是否需要禁止接入信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数
 2.日    期   : 2012年5月24日
   作    者   : l60609
   修改内容   : 单板不支持GSM时，用户设置了G模，只要测量G模就会复位
 3.日    期   : 2012年6月19日
   作    者   : l00171473
   修改内容   : DTS2012061808626, BAND的NV已修改为W和G都为UINT32了,
                即 aulSptBand[0]为W的BAND, aulSptBand[1]为G的BAND
 4.日    期   : 2012年12月13日
   作    者   : L00171473
   修改内容   : DTS2012121802573, TQE清理
 5.日    期   : 2013年6月5日
   作    者   : w00242748
   修改内容   : svlte和usim接口调整
 6.日    期   : 2013年07月29日
   作    者   : y00245242
   修改内容   : 为开发VOLTE，适配新的USIM接口
 7.日    期   : 2014年02月10日
   作    者   : f62575
   修改内容   : DTS2014012600456: en_NV_Item_WG_RF_MAIN_BAND数据修改为从内存中获取
*****************************************************************************/
VOS_UINT32  NAS_MML_GetGsmForbidFlg( VOS_VOID )
{
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU *pstMiscellaneousCfg = VOS_NULL_PTR;
    NAS_MML_SIM_TYPE_ENUM_UINT8          enSimType;
    VOS_UINT8                            ucSimPresentStatus;

    /* 快速开机模式直接返回 */
    if ( VOS_TRUE == NAS_MML_IsQuickStartFlg())
    {
        return VOS_FALSE;
    }

    pstMiscellaneousCfg = NAS_MML_GetMiscellaneousCfgInfo();
    enSimType           = NAS_MML_GetSimType();
    ucSimPresentStatus  = NAS_MML_GetSimPresentStatus();

    /* 卡类型为USIM且卡在位 */
    if ((NAS_MML_SIM_TYPE_USIM == enSimType)
     && (VOS_TRUE == ucSimPresentStatus))
    {
        /* USIM和NV中都指示禁止GSM接入时，需要记录在GSM下不能进行接入 */
        /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, begin */
        if (VOS_FALSE == NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_GSM_ACCESS_IN_USIM))
        {
            if ((VOS_FALSE == NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_GSM_SECURITY_CONTEXT))
            && (VOS_TRUE  == pstMiscellaneousCfg->ucNvGsmForbidFlg))
            {
                return VOS_TRUE;
            }
        }
        /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, end */
    }

    /* 该NV已修改为W和G都为UINT32了, 原为UINT16, 即 aulSptBand[0]为W的BAND, aulSptBand[1]为G的BAND */

    if (0 == NAS_MML_GetGsmBandCapability())
    {
        return VOS_TRUE;
    }


    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MML_InitSimPlmnInfo
 功能描述  : 初始化SIM卡中的PLMN信息
 输入参数  : ulPlmnNum:PLMN个数
             pstPlmnInfo:PLMN信息
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月28日
    作    者   : w00176964
    修改内容   : 新生成函数
******************************************************************************/
VOS_VOID  NAS_MML_InitSimPlmnInfo(
    VOS_UINT32                          ulPlmnNum,
    NAS_MML_SIM_PLMN_WITH_RAT_STRU     *pstPlmnInfo
)
{
    VOS_UINT32                          i;

    for ( i = 0 ; i < ulPlmnNum ; i++ )
    {
        pstPlmnInfo[i].usSimRat         = NAS_MML_INVALID_SIM_RAT;
        pstPlmnInfo[i].stPlmnId.ulMcc   = NAS_MML_INVALID_MCC;
        pstPlmnInfo[i].stPlmnId.ulMnc   = NAS_MML_INVALID_MNC;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MML_ResumeSimEhplmnList
 功能描述  : 恢复SIM卡中的EHPLMN信息，PLMN with RAT文件更新后，需要重新构建
              HPLMN WITH RAT列表
 输入参数  : ulPlmnNum:PLMN个数
              pstPlmnInfo:PLMN信息
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月21日
    作    者   : w00167002
    修改内容   : 新生成函数
******************************************************************************/
VOS_VOID  NAS_MML_ResumeSimEhplmnList(
    VOS_UINT8                          *pucPlmnNum,
    NAS_MML_SIM_PLMN_WITH_RAT_STRU     *pstPlmnInfo
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulTempPlmnNum;
    NAS_MML_SIM_PLMN_WITH_RAT_STRU      astTempPlmnInfo[NAS_MML_MAX_EHPLMN_NUM];
    VOS_UINT16                          usUeSptRat;

    PS_MEM_SET(astTempPlmnInfo, 0x00, sizeof(astTempPlmnInfo));
#if (FEATURE_ON == FEATURE_LTE)
    usUeSptRat          = NAS_MML_SIM_UE_SUPPORT_RAT_SUPPORT_LTE;
#else
    usUeSptRat          = NAS_MML_SIM_UE_SUPPORT_RAT;
#endif

    /* 将要重新构建的PLMN WITH RAT信息拷贝到临时缓存中 */
    ulTempPlmnNum = *pucPlmnNum;
    PS_MEM_CPY(astTempPlmnInfo, pstPlmnInfo, sizeof(astTempPlmnInfo));

    /* 将源PLMN WITH RAT信息清空 */
    NAS_MML_InitSimPlmnInfo(*pucPlmnNum, pstPlmnInfo);
    *pucPlmnNum = 0;

    /* 将非重复的网络添加进入源PLMN WITH RAT 列表 */
    for ( i = 0 ; i < ulTempPlmnNum ; i++ )
    {
        /* 当前网络已经在原有的列表中了，则不添加  */
        if ( VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnWithRatList(&astTempPlmnInfo[i].stPlmnId,
                                                                      *pucPlmnNum,
                                                                       pstPlmnInfo) )
        {
            continue;
        }

        /* 当前网络不在原有的列表中了，则添加入源PLMN WITH RAT 列表 */
        pstPlmnInfo[*pucPlmnNum].stPlmnId = astTempPlmnInfo[i].stPlmnId;
        pstPlmnInfo[*pucPlmnNum].usSimRat = usUeSptRat;

        (*pucPlmnNum)++;
    }

    return;
}

/*******************************************************************************
  函 数 名  : NAS_MML_IsUsimStausValid
  功能描述  : 判断SIM卡是否有效
  输入参数  : 无
  输出参数  : 无
  返 回 值  : VOS_FALSE:SIM卡无效
              VOS_TRUE:SIM卡有效
  调用函数  :
  被调函数  :

  修改历史      :
  1.日    期   : 2011年7月28日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2011年7月14日
    作    者   : zhoujun 40661
    修改内容   : 增加CC和CG模式下的处理
  3.日    期   : 2011年12月24日
    作    者   : w00176964
    修改内容   : V7R1 PhaseIV调整
  4.日    期   : 2013年05月14日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，将CS ONLY的判断修改为PS是否允许注册
*******************************************************************************/
VOS_UINT32 NAS_MML_IsUsimStausValid(VOS_VOID)
{
    NAS_MML_SIM_STATUS_STRU            *pstSimStatus    = VOS_NULL_PTR;
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-14, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    NAS_MML_CALL_MODE_ENUM_UINT8        enCallMode;

    enCallMode = NAS_MML_GetCallMode();
#endif
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-14, end */

    pstSimStatus = NAS_MML_GetSimStatus();

    if ( VOS_FALSE == NAS_MML_GetSimPresentStatus() )
    {
        return VOS_FALSE;
    }

    if (( VOS_FALSE == pstSimStatus->ucSimPsRegStatus)
     && ( VOS_FALSE == pstSimStatus->ucSimCsRegStatus))
    {
        return VOS_FALSE;
    }

    if ((VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
     && (VOS_FALSE == pstSimStatus->ucSimCsRegStatus))
    {
        return VOS_FALSE;
    }

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-14, begin */
    /* 非ecall only模式CS不允许attach并且PS卡无效才认为卡无效 */
    if ((VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
     && (VOS_FALSE == pstSimStatus->ucSimPsRegStatus)
#if (FEATURE_ON == FEATURE_ECALL)
     && (NAS_MML_ECALL_ONLY != enCallMode)
#endif
       )
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-14, end */
    {
        return VOS_FALSE;
    }

#if (FEATURE_ON == FEATURE_LTE)

    /* LTE单模的情况PS卡无效的时候也认为此时卡无效 */
    if ((VOS_TRUE  == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
     && (VOS_FALSE == pstSimStatus->ucSimPsRegStatus))
    {
        return VOS_FALSE;
    }
#endif
    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MML_IsMccInDestMccList
 功能描述  : 判断MCC是否在MCC列表中
 输入参数  : ulMcc:需要判断的MCC
             ulMccNum:列表中MCC的个数
             pulMccList:MCC列表
 输出参数  : 无
 返 回 值  : VOS_TRUE  : MCC在列表中
             VOS_FALSE : MCC不在列表中
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2012年03月12日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsMccInDestMccList (
    VOS_UINT32                          ulMcc,
    VOS_UINT32                          ulMccNum,
    VOS_UINT32                         *pulMccList
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulFlg;

    ulFlg = VOS_FALSE;

    for ( i = 0; i < ulMccNum; i++ )
    {
        if ( VOS_TRUE == NAS_MML_ComparePlmnMcc(ulMcc,
                                                  pulMccList[i]) )
        {
            ulFlg = VOS_TRUE;
            break;
        }
    }

    return (ulFlg);
}


/* Added by n00355355 for 呼叫重建, 2015-9-17, begin */
/*****************************************************************************
 函 数 名  : NAS_MML_GetMmlCsTransactionStatus
 功能描述  : 将NAS维护的CS业务状态标志类型转换为AS格式的CS业务状态标志
 输入参数  : 无
 输出参数  : penAsCsTransactionsStatus: AS格式的CSFB状态标志
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月16日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 201211月15日
    作    者   : t00212959
    修改内容   : DTS2012041801803
*****************************************************************************/
VOS_VOID NAS_MML_GetMmlCsTransactionStatus(
    NAS_MML_CS_TRANSACTION_ENUM_UINT8                        *penAsCsTransactionsStatus
)
{
    /* 被叫就是CSFB的被叫*/
    if ( NAS_MML_CSFB_SERVICE_STATUS_MT_EXIST == NAS_MML_GetCsfbServiceStatus())
    {
        *penAsCsTransactionsStatus = NAS_MML_CS_TRANSACTION_MT_EXIST;

        return;
    }

    if (NAS_MML_MT_CSFB_PAGING_TIMER_RUNNING == NAS_MML_GetCsfbMtPagingTimerStatus())
    {
        *penAsCsTransactionsStatus = NAS_MML_CS_TRANSACTION_MT_EXIST;

        return;
    }

    if (NAS_MML_CSFB_MO_NORMAL_CALL_SETUP_START == NAS_MML_GetMoCallStatus())
    {
        *penAsCsTransactionsStatus = NAS_MML_CS_TRANSACTION_MO_NORMAL_EXIST;

        return;
    }

    if (NAS_MML_CSFB_MO_EMC_CALL_SETUP_START == NAS_MML_GetMoCallStatus())
    {
        *penAsCsTransactionsStatus = NAS_MML_CS_TRANSACTION_EMERGENCY_EXIST;

        return;
    }

    if (NAS_MML_CSFB_MO_SS_SETUP_START == NAS_MML_GetMoSsStatus())
    {
        *penAsCsTransactionsStatus = NAS_MML_CS_TRANSACTION_MO_NORMAL_EXIST;

        return;
    }

    if ( VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
    {
        /* 存在紧急呼*/
        if ( VOS_TRUE == NAS_MML_GetCsEmergencyServiceFlg())
        {
            *penAsCsTransactionsStatus = NAS_MML_CS_TRANSACTION_EMERGENCY_EXIST;
        }
        /* 不存在紧急呼，普通呼叫，SS,SM都算作普通呼叫*/
        else
        {
            *penAsCsTransactionsStatus = NAS_MML_CS_TRANSACTION_MO_NORMAL_EXIST;
        }

        return;
    }

    /*不存在业务*/
    *penAsCsTransactionsStatus = NAS_MML_CS_TRANSACTION_NO_EXIST;

    return;
}

/* Added by n00355355 for 呼叫重建, 2015-9-17, end */



#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MML_IsPlmnIdInCsDomainUnAvailPlmnList
 功能描述  : 判断一个PlmnId是否在原因值#18列表中
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE: 在原因值#18列表中
             VOS_FALSE: 不在原因值#18列表中
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年06月12日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2012年12月28日
    作    者   : s46746
    修改内容   : DSDA GUNAS C CORE项目，重新封装LMM提供的接口函数
  3.日    期   : 2015年6月4日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT32 NAS_MML_IsPlmnIdInCsDomainUnAvailPlmnList(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MML_PLMN_ID_STRU               *pstPlmnList = VOS_NULL_PTR;
    NAS_LMM_INFO_STRU                   stLmmInfo;

    PS_MEM_SET(&stLmmInfo, 0x0, sizeof(NAS_LMM_INFO_STRU));


    /* 平台不支持LTE */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportLte())
    {
        return VOS_FALSE;
    }

    /* 调用LNAS提供接口函数，成功返回VOS_OK */
    if (MMC_LMM_SUCC != Nas_GetLteInfo(NAS_LMM_CS_DOMAIN_UNAVAILABLE_PLMN_LIST, &stLmmInfo))
    {
        return VOS_FALSE;
    }

    /* 申请动态内存 */
    pstPlmnList = (NAS_MML_PLMN_ID_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC, (MMC_LMM_MAX_PLMN_NUM*sizeof(NAS_MML_PLMN_ID_STRU)));

    /* 如果申请失败，则返回 */
    if ( VOS_NULL_PTR == pstPlmnList )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MML_IsPlmnIdInCsDomainUnAvailPlmnList: Dynamic Memory Alloc Error");

        return VOS_FALSE;
    }

    NAS_MMC_ConvertLmmPlmnToGUNasPlmn(stLmmInfo.u.stCsDomainUnAvailPlmnList.ulPlmnNum,
                                      stLmmInfo.u.stCsDomainUnAvailPlmnList.astPlmnId,
                                      pstPlmnList);

    /* 在#18列表中 */
    if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstPlmnId,
                                         (VOS_UINT8)(stLmmInfo.u.stCsDomainUnAvailPlmnList.ulPlmnNum),
                                         pstPlmnList))
    {
        /* 释放动态内存 */
        PS_MEM_FREE(WUEPS_PID_MMC, pstPlmnList);

        return VOS_TRUE;
    }

    /* 释放动态内存 */
    PS_MEM_FREE(WUEPS_PID_MMC, pstPlmnList);

    return VOS_FALSE;
}


/*******************************************************************************
  函 数 名  : NAS_MML_GetLteRPlmn
  功能描述  : 获取LTE的RPLMN
  输入参数  : 无
  输出参数  : pstPlmnId
  返 回 值  : VOS_FALSE:获取失败
              VOS_TRUE:获取成功
  调用函数  :
  被调函数  :

  修改历史      :
   1.日    期   : 2011年7月28日
     作    者   : s46746
     修改内容   : 新生成函数
   2.日    期   : 2012年05月17日
     作    者   : w00166186
     修改内容   : DTS2012032401270,#12 #15原因被拒后删除了EPLMN
   3.日    期   : 2012年12月28日
     作    者   : s46746
     修改内容   : DSDA GUNAS C CORE项目，重新封装LMM提供的接口函数
*******************************************************************************/
VOS_UINT32 NAS_MML_GetLteRPlmn(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MML_PLMN_ID_STRU                stRPlmnId;
    NAS_LMM_INFO_STRU                   stLmmInfoStru;

    PS_MEM_SET(&stRPlmnId,     0x00, sizeof(NAS_MML_PLMN_ID_STRU));
    PS_MEM_SET(&stLmmInfoStru, 0x00, sizeof(NAS_LMM_INFO_STRU));

    /* 获取L模的GUTI, 获取失败则返回 VOS_FALSE */
    /* 如果平台能力不支持lte,返回不存在LTE的RPLMN */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportLte())
    {
        return VOS_FALSE;
    }

    if (MMC_LMM_SUCC != Nas_GetLteInfo(NAS_LMM_RPLMN, &stLmmInfoStru))
    {
        return VOS_FALSE;
    }

    /* 将GUTI中的PLMN转换为GUNAS使用的PLMN格式 */
    NAS_MMC_ConvertLmmPlmnToGUNasFormat(&(stLmmInfoStru.u.stPlmn), &(stRPlmnId));

    /* 若该PLMN有效且不是禁止网络则直接返回 */
    if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&stRPlmnId))
    {
        if (VOS_FALSE == NAS_MML_IsPlmnIdInForbidPlmnList(&stRPlmnId))
        {
            *pstPlmnId = stRPlmnId;

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MML_IsTaiInDestTaiList
 功能描述  : 判断TAI是否在ForbTa列表中
 输入参数  : pstTai:需要判断的TAI
             ulTaiNum:列表中TAI的个数
             pstTaiList:TAI列表
 输出参数  : 无
 返 回 值  : VOS_TRUE  : TAI在列表中
             VOS_FALSE : TAI不在列表中
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2012年5月9日
   作    者   : t00212959
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsTaiInDestTaiList (
    NAS_MML_TAI_STRU                   *pstTai,
    VOS_UINT32                          ulTaiNum,
    NAS_LMM_TAI_STRU                   *pstTaiList
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulIsTaiInTaiListFlg;
    NAS_MML_PLMN_ID_STRU                stPlmnId;
    VOS_UINT32                          ulIsSamePlmn;

    ulIsTaiInTaiListFlg = VOS_FALSE;

    for ( i = 0; i < ulTaiNum; i++ )
    {
        NAS_MMC_ConvertLmmPlmnToGUNasFormat(&pstTaiList[i].stPlmnId, &stPlmnId);

        ulIsSamePlmn = NAS_MML_CompareBcchPlmnwithSimPlmn(&pstTai->stPlmnId, &stPlmnId);

        if ((VOS_TRUE == ulIsSamePlmn)
         && (pstTai->stTac.ucTac == pstTaiList[i].stTac.ucTac)
         && (pstTai->stTac.ucTacCnt == pstTaiList[i].stTac.ucTacCnt))
        {
            ulIsTaiInTaiListFlg = VOS_TRUE;
            break;
        }
    }

    return ulIsTaiInTaiListFlg;
}

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, begin */
/*****************************************************************************
 函 数 名  : NAS_MML_IsSupportLteCapability
 功能描述  : 获取当前是否支持Lte能力
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 支持LTE能力
             VOS_FALSE - 不支持LTE能力
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2012年8月15日
   作    者   : z00161729
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsSupportLteCapability(VOS_VOID)
{
    VOS_UINT32                          ulIsLteRatSupportFlg;

    ulIsLteRatSupportFlg = NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE);

    if ((VOS_TRUE == NAS_MML_IsLteCapabilityDisabled(NAS_MML_GetLteCapabilityStatus(),NAS_MML_GetDisableLteRoamFlg()))
     || (VOS_FALSE == ulIsLteRatSupportFlg))
    {
        /* L处于disable状态或syscfg设置不支持L,返回VOS_FALSE*/
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, end */

#endif


/*******************************************************************************
  函 数 名  : NAS_MML_GetGU_CsRPlmn
  功能描述  : 获取GU的CS RPLMN
  输入参数  : 无
  输出参数  : pstPlmnId
  返 回 值  : VOS_FALSE:获取失败
              VOS_TRUE:获取成功
  调用函数  :
  被调函数  :

  修改历史      :
   1.日    期   : 2012年4月19日
     作    者   : l00130025
     修改内容   : DTS2012030806450,对于只支持PS的Sim卡，UE在CS_PS模式需要从PSLoci获取Rplmn
   2.日    期   : 2015年6月14日
     作    者   : z00301431
     修改内容   : DTS2015060309245，以色列卡问题适配，updatestatus为0xff，RPLMN为全0问题规避
*******************************************************************************/
VOS_UINT32 NAS_MML_GetGU_CsRPlmn(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MML_PLMN_ID_STRU                stRPlmnId;
    NAS_MML_LAI_STRU                   *pstLai = VOS_NULL_PTR;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enStatus;

    enStatus = NAS_MML_GetCsUpdateStatus();

    if ((NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED == enStatus)
     || (NAS_MML_LOCATION_UPDATE_STATUS_BUTT == enStatus))
    {
        return VOS_FALSE;
    }

    pstLai = NAS_MML_GetCsLastSuccLai();

    stRPlmnId = pstLai->stPlmnId;

    /* 若该PLMN有效且不在禁止网络中，返回该网络 */
    if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&stRPlmnId))
    {
        if (VOS_FALSE == NAS_MML_IsPlmnIdInForbidPlmnList(&stRPlmnId))
        {
           *pstPlmnId = stRPlmnId;

           return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
/*******************************************************************************
  函 数 名  : NAS_MML_GetGU_PsRPlmn
  功能描述  : 获取GU的PS RPLMN
  输入参数  : 无
  输出参数  : pstPlmnId
  返 回 值  : VOS_FALSE:获取失败
              VOS_TRUE:获取成功
  调用函数  :
  被调函数  :

  修改历史      :
   1.日    期   : 2012年4月19日
     作    者   : l00130025
     修改内容   : DTS2012030806450,对于只支持PS的Sim卡，UE在CS_PS模式需要从PSLoci获取Rplmn
   2.日    期   : 2015年6月14日
     作    者   : z00301431
     修改内容   : DTS2015060309245，以色列卡问题适配，updatestatus为0xff，RPLMN为全0问题规避
*******************************************************************************/
VOS_UINT32 NAS_MML_GetGU_PsRPlmn(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MML_PLMN_ID_STRU                stRPlmnId;
    NAS_MML_RAI_STRU                   *pstRai = VOS_NULL_PTR;
    NAS_MML_ROUTING_UPDATE_STATUS_ENUM_UINT8    enStatus;

    enStatus = NAS_MML_GetPsUpdateStatus();

    if ((NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED == enStatus)
     || (NAS_MML_ROUTING_UPDATE_STATUS_BUTT == enStatus))
    {
        return VOS_FALSE;
    }

    pstRai  = NAS_MML_GetPsLastSuccRai();

    stRPlmnId = pstRai->stLai.stPlmnId;

    /* 若该PLMN有效且不在禁止网络中，返回该网络 */
    if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&stRPlmnId))
    {
        if (VOS_FALSE == NAS_MML_IsPlmnIdInForbidPlmnList(&stRPlmnId))
        {
           *pstPlmnId = stRPlmnId;

           return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
/*******************************************************************************
  函 数 名  : NAS_MML_GetGURPlmn
  功能描述  : 获取GU的RPLMN
  输入参数  : 无
  输出参数  : pstPlmnId
  返 回 值  : VOS_FALSE:获取失败
              VOS_TRUE:获取成功
  调用函数  :
  被调函数  :

  修改历史      :
   1.日    期   : 2011年7月28日
     作    者   : s46746
     修改内容   : 新生成函数
   2.日    期   : 2012年4月19日
     作    者   : l00130025
     修改内容   : DTS2012030806450,对于只支持PS的Sim卡，UE在CS_PS模式需要从PSLoci获取Rplmn
*******************************************************************************/
VOS_UINT32 NAS_MML_GetGURPlmn(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    if (NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
    {
        return NAS_MML_GetGU_PsRPlmn(pstPlmnId);
    }
    else if (NAS_MML_MS_MODE_CS_ONLY == NAS_MML_GetMsMode())
    {
        return NAS_MML_GetGU_CsRPlmn(pstPlmnId);
    }
    else
    {
        /* CS和PS模式下，先判断CS的Rplmn,再判断PS的Rplmn */
        if (VOS_TRUE == NAS_MML_GetGU_CsRPlmn(pstPlmnId))
        {
            return VOS_TRUE;
        }
        else if (VOS_TRUE == NAS_MML_GetGU_PsRPlmn(pstPlmnId))
        {
            return VOS_TRUE;
        }
        else
        {
            return VOS_FALSE;
        }
    }

}

/*******************************************************************************
  函 数 名  : NAS_MML_GetEfLociPlmn
  功能描述  : 获取Sim卡中的EF LOCI文件中的PLMN
  输入参数  : 无
  输出参数  : pstPlmnId
  返 回 值  : VOS_FALSE:获取失败
              VOS_TRUE:获取成功
  调用函数  :
  被调函数  :

  修改历史      :
   1.日    期   : 2012年6月27日
     作    者   : w00176964
     修改内容   : 新生成函数
   2.日    期   : 2015年6月14日
     作    者   : z00301431
     修改内容   : DTS2015060309245，以色列卡问题适配，updatestatus为0xff，RPLMN为全0问题规避
*******************************************************************************/
VOS_UINT32 NAS_MML_GetEfLociPlmn(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MML_PLMN_ID_STRU                stRPlmnId;
    NAS_MML_RAI_STRU                   *pstRai = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                   *pstLai = VOS_NULL_PTR;
    NAS_MML_ROUTING_UPDATE_STATUS_ENUM_UINT8    enPsStatus;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsStatus;

    pstRai      = NAS_MML_GetPsLastSuccRai();
    pstLai      = NAS_MML_GetCsLastSuccLai();
    enPsStatus  = NAS_MML_GetPsUpdateStatus();
    enCsStatus  = NAS_MML_GetCsUpdateStatus();

    if (NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
    {
        if (NAS_MML_ROUTING_UPDATE_STATUS_BUTT == enPsStatus)
        {
            return VOS_FALSE;
        }

        stRPlmnId = pstRai->stLai.stPlmnId;
    }
    else
    {
        if (NAS_MML_LOCATION_UPDATE_STATUS_BUTT == enCsStatus)
        {
            return VOS_FALSE;
        }

        stRPlmnId = pstLai->stPlmnId;
    }

    /* 若该PLMN有效且不在禁止网络中，返回该网络 */
    if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&stRPlmnId))
    {
        if (VOS_FALSE == NAS_MML_IsPlmnIdInForbidPlmnList(&stRPlmnId))
        {
           *pstPlmnId = stRPlmnId;

           return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*******************************************************************************
  函 数 名  : NAS_MML_GetRPlmn
  功能描述  : 获取指定接入技术的RPLMN
  输入参数  : enRat
  输出参数  : pstPlmnId
  返 回 值  : VOS_FALSE:获取失败
              VOS_TRUE:获取成功
  调用函数  :
  被调函数  :

  修改历史      :
   1.日    期   : 2011年7月28日
     作    者   : s46746
     修改内容   : 新生成函数
*******************************************************************************/
VOS_UINT32 NAS_MML_GetRPlmn(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
#if (FEATURE_ON == FEATURE_LTE)
    if (NAS_MML_NET_RAT_TYPE_LTE == enRat)
    {
        return NAS_MML_GetLteRPlmn(pstPlmnId);
    }
#endif

    return NAS_MML_GetGURPlmn(pstPlmnId);

}

/*****************************************************************************
 函 数 名  : NAS_MML_AddForbPlmn
 功能描述  : 向禁止PLMN lsit添加元素的处理
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月24日
   作    者   : l00130025
   修改内容   : 新生成函数

 2.日    期   : 2011年11月24日
   作    者   : w00167002
   修改内容   : DTS2011112405567:原有的函数名NAS_MML_IsPlmnIdInDestPlmnList
                更改为NAS_MML_IsBcchPlmnIdInDestSimPlmnList

*****************************************************************************/
VOS_UINT32 NAS_MML_AddForbPlmn (
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    VOS_UINT32                          ulRlst;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbPlmnInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucForbPlmnNum;
    VOS_UINT32                          ulChgFlag;

    ulChgFlag  = VOS_FALSE;

    ulRlst    = NAS_MML_ComparePlmnIdWithHplmn(pstPlmnId);

    if (VOS_TRUE == ulRlst )
    {
        return ulChgFlag;
    }

    /*添加ForbPlmn，并向Usim发送更新消息*/
    pstForbPlmnInfo = NAS_MML_GetForbidPlmnInfo();
    ucForbPlmnNum   = pstForbPlmnInfo->ucForbPlmnNum;


    /* 在forbid plmn列表中 */
    ulRlst = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstPlmnId,
                                          pstForbPlmnInfo->ucForbPlmnNum,
                                          pstForbPlmnInfo->astForbPlmnIdList);

    if (VOS_FALSE == ulRlst)
    {
        /* 列表已满时，删除最先保存的元素 */
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-15, begin */
        if (( NAS_MML_MAX_FORBPLMN_NUM == ucForbPlmnNum )
         || ((pstForbPlmnInfo->ucUsimForbPlmnNum == ucForbPlmnNum)
          && (0 < ucForbPlmnNum)))
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-15, end */
        {
            (VOS_VOID)PS_MEM_MOVE(pstForbPlmnInfo->astForbPlmnIdList,
                        (pstForbPlmnInfo->astForbPlmnIdList + 1),
                        (NAS_MML_MAX_FORBPLMN_NUM -1) * sizeof(NAS_MML_PLMN_ID_STRU));

            ucForbPlmnNum--;
        }

        pstForbPlmnInfo->astForbPlmnIdList[ucForbPlmnNum].ulMcc
                                                       = pstPlmnId->ulMcc;
        pstForbPlmnInfo->astForbPlmnIdList[ucForbPlmnNum].ulMnc
                                                       = pstPlmnId->ulMnc;

        ucForbPlmnNum++;

        pstForbPlmnInfo->ucForbPlmnNum = ucForbPlmnNum;

        ulChgFlag = VOS_TRUE;

    }

    return ulChgFlag;
}
/*****************************************************************************
 函 数 名  : NAS_MML_DelForbPlmn
 功能描述  : 在禁止PLMN lsit中删除元素的处理
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月24日
    作    者   : l00130025
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_DelForbPlmn (
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulIdx;
    VOS_UINT32                          ulChgFlag;

    ulChgFlag  = VOS_FALSE;

    pstForbPlmnInfo   = NAS_MML_GetForbidPlmnInfo();

    /* 在forbid plmn列表中 */
    ulIdx = NAS_MML_GetPlmnIdxInList(pstPlmnId,
                    pstForbPlmnInfo->ucForbPlmnNum, pstForbPlmnInfo->astForbPlmnIdList);

    /* 找到对应的PlmnId,删除，更新ForbPlmn，并向Usim发送更新消息*/
    if (ulIdx < pstForbPlmnInfo->ucForbPlmnNum)
    {
        if (ulIdx == (pstForbPlmnInfo->ucForbPlmnNum -1))
        {
            pstForbPlmnInfo->astForbPlmnIdList[ulIdx].ulMcc = NAS_MML_INVALID_MCC;
            pstForbPlmnInfo->astForbPlmnIdList[ulIdx].ulMnc = NAS_MML_INVALID_MNC;
        }
        else
        {
            (VOS_VOID)PS_MEM_MOVE(pstForbPlmnInfo->astForbPlmnIdList + ulIdx,
                 (pstForbPlmnInfo->astForbPlmnIdList + (ulIdx + 1)),
                 (NAS_MML_MAX_FORBPLMN_NUM - (ulIdx + 1)) * sizeof(NAS_MML_PLMN_ID_STRU));
        }

        pstForbPlmnInfo->ucForbPlmnNum --;

        ulChgFlag  = VOS_TRUE;

    }

    return ulChgFlag;
}

/*****************************************************************************
 函 数 名  : NAS_MML_AddForbGprsPlmn
 功能描述  : 向禁止GPRS PLMN lsit添加元素的处理
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月24日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2011年7月28日
    作    者   : L00171473
    修改内容   : V7R1 PhaseII 修改
  3.日    期   : 2011年11月24日
    作    者   : w00167002
    修改内容   : DTS2011112405567:原有的函数名NAS_MML_IsPlmnIdInDestPlmnList
                 更改为NAS_MML_IsBcchPlmnIdInDestSimPlmnList
*****************************************************************************/
VOS_VOID NAS_MML_AddForbGprsPlmn(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbPlmnInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucForbGprsPlmnNum;
    VOS_UINT32                          ulRlst;

    ulRlst = VOS_FALSE;

    /* 用于获取禁止GPRS PLMN lsit */
    pstForbPlmnInfo = NAS_MML_GetForbidPlmnInfo();

    /* Ts23.122 Ch 3.1 The HPLMN (if the EHPLMN list is not present or is empty)
    or an EHPLMN (if the EHPLMN list is present) shall not be stored
    on the list of "forbidden PLMNs for GPRS service"
    相关测试用例: ts34.123 GCF12.3.2.8 cellA in MCC2/MNC1/LAC1/RAC1(RAI-2, Not HPLMN) */
    ulRlst = NAS_MML_ComparePlmnIdWithHplmn(pstPlmnId);
    if (VOS_TRUE == ulRlst)
    {
        return;
    }

    /* 该PLMN已在禁止GPRS PLMN lsit中，则不添加 */
    ulRlst = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstPlmnId,
                                            pstForbPlmnInfo->ucForbGprsPlmnNum,
                                            pstForbPlmnInfo->astForbGprsPlmnList);


    if (VOS_TRUE == ulRlst)
    {
        return;
    }

    /* 获取禁止GPRS PLMN 的个数 */
    ucForbGprsPlmnNum   = pstForbPlmnInfo->ucForbGprsPlmnNum;

    /* 列表已满时，移出最先保存的元素 */
    if ( NAS_MML_MAX_FORBGPRSPLMN_NUM == ucForbGprsPlmnNum )
    {
        (VOS_VOID)PS_MEM_MOVE(&(pstForbPlmnInfo->astForbGprsPlmnList[0]),
                    &(pstForbPlmnInfo->astForbGprsPlmnList[1]),
                     (ucForbGprsPlmnNum-1) * sizeof(NAS_MML_PLMN_ID_STRU));
        ucForbGprsPlmnNum--;
    }

    /* 添加禁止GPRS PLMN到列表的最后 */
    pstForbPlmnInfo->astForbGprsPlmnList[ucForbGprsPlmnNum].ulMcc
                                                   = pstPlmnId->ulMcc;
    pstForbPlmnInfo->astForbGprsPlmnList[ucForbGprsPlmnNum].ulMnc
                                                   = pstPlmnId->ulMnc;

    /* 更新禁止GPRS PLMN的个数 */
    ucForbGprsPlmnNum++;
    pstForbPlmnInfo->ucForbGprsPlmnNum = ucForbGprsPlmnNum;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_DelForbGprsPlmn
 功能描述  : 在禁止Forb PLMN for GPRS list中删除元素的处理
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月24日
    作    者   : l00130025
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_DelForbGprsPlmn (
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulIdx;

    pstForbPlmnInfo   = NAS_MML_GetForbidPlmnInfo();

    /* 在forbid plmn for Gprs列表中 */
    ulIdx = NAS_MML_GetPlmnIdxInList(pstPlmnId,
                    pstForbPlmnInfo->ucForbGprsPlmnNum, pstForbPlmnInfo->astForbGprsPlmnList);

    /* 找到对应的PlmnId,删除，更新ForbPlmn */
    if (ulIdx < pstForbPlmnInfo->ucForbGprsPlmnNum)
    {
        if (ulIdx == (pstForbPlmnInfo->ucForbGprsPlmnNum -1))
        {
            pstForbPlmnInfo->astForbGprsPlmnList[ulIdx].ulMcc = NAS_MML_INVALID_MCC;
            pstForbPlmnInfo->astForbGprsPlmnList[ulIdx].ulMnc = NAS_MML_INVALID_MNC;
        }
        else
        {
            (VOS_VOID)PS_MEM_MOVE(pstForbPlmnInfo->astForbGprsPlmnList + ulIdx,
                 (pstForbPlmnInfo->astForbGprsPlmnList + (ulIdx + 1)),
                 (NAS_MML_MAX_FORBGPRSPLMN_NUM - (ulIdx + 1)) * sizeof(NAS_MML_PLMN_ID_STRU));
        }

        pstForbPlmnInfo->ucForbGprsPlmnNum --;

    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MML_AddForbRoamLa
 功能描述  : 向"forbidden las for roaming" list添加元素的处理
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月24日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2011年7月28日
    作    者   : L00171473
    修改内容   : V7R1 PhaseII 修改
  3.日    期   : 2011年11月11日
    作    者   : w00167002
    修改内容   : DTS2011110907180:将禁止漫游位置区信息作为参数传递进来，便于
                  此函数的复用
*****************************************************************************/
VOS_VOID NAS_MML_AddForbRoamLa (
    NAS_MML_LAI_STRU                                       *pstLai,
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU               *pstForbRoamLaInfo
)
{
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU                    *pstMiscellaneousCfgInfo = VOS_NULL_PTR;
    VOS_UINT8                                               ucRealMaxForbRoamLaNum;
    VOS_UINT8                                               ucForbRoamLaNum;
    VOS_UINT32                                              ulRlst;

    ulRlst = VOS_FALSE;

    /* 已在"Forbidden las for roaming" list中，则不添加 */
    ulRlst = NAS_MML_IsLaiInDestLaiList(pstLai, pstForbRoamLaInfo->ucForbRoamLaNum,
                                        pstForbRoamLaInfo->astForbRomLaList);
    if (VOS_TRUE == ulRlst)
    {
        return;
    }

    /* 用于获取NV中保存的最大禁止LA个数信息 */
    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();

    /* 结合NV中的最大禁止LA个数信息获取有效的最大禁止个数 */
    ucRealMaxForbRoamLaNum = NAS_MML_MAX_FORBLA_FOR_ROAM_NUM;
    if (VOS_TRUE == pstMiscellaneousCfgInfo->ucMaxForbRoamLaFlg)
    {
        if (pstMiscellaneousCfgInfo->ucMaxForbRoamLaNum <= NAS_MML_MAX_FORBLA_FOR_ROAM_NUM)
        {
            ucRealMaxForbRoamLaNum = pstMiscellaneousCfgInfo->ucMaxForbRoamLaNum;
        }
    }

    if (0 == ucRealMaxForbRoamLaNum )
    {
        return;
    }

    /* 获取当前列表中的禁止LA个数 */
    ucForbRoamLaNum = pstForbRoamLaInfo->ucForbRoamLaNum;

    /* 列表已满时，移出最先保存的元素 */
    if (ucRealMaxForbRoamLaNum == ucForbRoamLaNum)
    {
        (VOS_VOID)PS_MEM_MOVE(&(pstForbRoamLaInfo->astForbRomLaList[0]),
                    &(pstForbRoamLaInfo->astForbRomLaList[1]),
                     (ucForbRoamLaNum - 1) * sizeof(NAS_MML_LAI_STRU ) );
        ucForbRoamLaNum--;
    }

    /* 添加Forbidden for roaming LA到列表的最后 */
    pstForbRoamLaInfo->astForbRomLaList[ucForbRoamLaNum] = (*pstLai);

    /* 更新当前列表中的禁止LA个数 */
    ucForbRoamLaNum++;
    pstForbRoamLaInfo->ucForbRoamLaNum = ucForbRoamLaNum;

    return;
}



/*****************************************************************************
 函 数 名  : NAS_MML_AddForbRegLa
 功能描述  : 向"forbidden LA for regional provision" list添加元素的处理
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月24日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2011年7月28日
    作    者   : L00171473
    修改内容   : V7R1 PhaseII 修改
*****************************************************************************/
VOS_VOID NAS_MML_AddForbRegLa (
    NAS_MML_LAI_STRU                   *pstLai
)
{
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbPlmnInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucForbRegLaNum;
    VOS_UINT32                          ulRlst;

    ulRlst = VOS_FALSE;

    /* 用于获取"Forbidden LA for regional provision" list */
    pstForbPlmnInfo = NAS_MML_GetForbidPlmnInfo();

    /* 已在"Forbidden LA for regional provision" list，则不添加 */
    ulRlst = NAS_MML_IsLaiInDestLaiList(pstLai, pstForbPlmnInfo->ucForbRegLaNum,
                                        pstForbPlmnInfo->astForbRegLaList);
    if (VOS_TRUE == ulRlst)
    {
        return;
    }

    /* 获取当前列表中Forbidden LA的个数 */
    ucForbRegLaNum = pstForbPlmnInfo->ucForbRegLaNum;

    /* 列表已满，则移出最先保存的元素 */
    if (NAS_MML_MAX_FORBLA_FOR_REG_NUM == ucForbRegLaNum)
    {
        (VOS_VOID)PS_MEM_MOVE(&(pstForbPlmnInfo->astForbRegLaList[0]),
                    &(pstForbPlmnInfo->astForbRegLaList[1]),
                    (ucForbRegLaNum-1)*sizeof(NAS_MML_LAI_STRU));
        ucForbRegLaNum--;
    }

    /* 添加Forbidden LA for regional provision到列表的最后 */
    pstForbPlmnInfo->astForbRegLaList[ucForbRegLaNum] = (*pstLai);

    /* 更新当前列表中的禁止LA个数 */
    ucForbRegLaNum++;
    pstForbPlmnInfo->ucForbRegLaNum = ucForbRegLaNum;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_DelForbLa
 功能描述  : 删除禁止LA列表中的注册成功的LA的处理
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月24日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2012年11月19日
    作    者   : t00212959
    修改内容   : DTS2012111905770:Forbidden LA For Roaming发生改变才需要通知接入层
  3.日    期   : 2015年09月24日
    作    者   : g00322017
    修改内容   : CS注册失败禁止LA，从禁止LA有效时长列表删除LAI
  4.日   期    : 2015-9-23
    作   者    : Z00359541
    修改内容   : 加入Domain参数给函数NAS_MML_DelForbLa

*****************************************************************************/
VOS_UINT32 NAS_MML_DelForbLa (
    NAS_MML_LAI_STRU                   *pstLai,
    NAS_MML_REG_DOMAIN_ENUM_UINT8       enDomain
)
{
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU             *pstForbLaWithValidPeriodList   = VOS_NULL_PTR;

    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                        *pstForbPlmnInfo                = VOS_NULL_PTR;
    VOS_UINT32                                              ulRlst;
    VOS_UINT8                                               ucLaiIndex;

    VOS_UINT32                                              ulIsLaInForbLaWithValidPeriodList;

    ulRlst                              = VOS_FALSE;
    ulIsLaInForbLaWithValidPeriodList   = VOS_FALSE;
    /* 用于获取禁止LA的信息 */
    pstForbPlmnInfo = NAS_MML_GetForbidPlmnInfo();

    /* Forbidden LA For Roaming发生改变才需要通知接入层,应该先判断Forbidden LA for regional provision，后判断
       Forbidden las for roaming */

    /* 在"Forbidden LA for regional provision" list 中查找要删除的LAI */
    ulRlst = NAS_MML_GetLaiIndexInDestLaiList(pstLai, &ucLaiIndex,
                                              pstForbPlmnInfo->ucForbRegLaNum,
                                              pstForbPlmnInfo->astForbRegLaList);
    /* 查找到LAI则进行删除操作 */
    if(VOS_TRUE == ulRlst)
    {
        if (ucLaiIndex < (pstForbPlmnInfo->ucForbRegLaNum - 1))
        {
            (VOS_VOID)PS_MEM_MOVE(&(pstForbPlmnInfo->astForbRegLaList[ucLaiIndex]),
                         &(pstForbPlmnInfo->astForbRegLaList[ucLaiIndex + 1]),
                         ((pstForbPlmnInfo->ucForbRegLaNum-ucLaiIndex) - 1) * sizeof(NAS_MML_LAI_STRU));
        }

        /* 删除"Forbidden LA for regional provision后，更新个数 */
        pstForbPlmnInfo->ucForbRegLaNum--;
    }

    if (NAS_MML_REG_DOMAIN_CS == enDomain)
    {
        pstForbLaWithValidPeriodList = NAS_MML_GetForbLaWithValidPeriodList();
        ulIsLaInForbLaWithValidPeriodList = NAS_MML_GetLaiIndexInRegFailForbLaList(pstLai, &ucLaiIndex,
                                                           pstForbLaWithValidPeriodList->ulForbLaWithValidPeriodNum,
                                                           pstForbLaWithValidPeriodList->astForbLaWithValidPeriodList);
        /* 查找到LAI则进行删除操作 */
        if (VOS_TRUE == ulIsLaInForbLaWithValidPeriodList)
        {
            NAS_MML_DeleteLaFromForbLaWithValidPeriodList(pstForbLaWithValidPeriodList, ucLaiIndex);

            /* 启动定时器 */
            NAS_MML_StartCustomizedForbLaTimer();
        }
    }

    /* 在"Forbidden las for roaming" list 中查找要删除的LAI */
    ulRlst = NAS_MML_GetLaiIndexInDestLaiList(pstLai, &ucLaiIndex,
                                              pstForbPlmnInfo->ucForbRoamLaNum,
                                              pstForbPlmnInfo->astForbRomLaList);

    /* 查找到LAI则进行删除操作 */
    if (VOS_TRUE == ulRlst)
    {
        /* 删除指定的LAI */
        if (ucLaiIndex < (pstForbPlmnInfo->ucForbRoamLaNum - 1))
        {
            (VOS_VOID)PS_MEM_MOVE(&(pstForbPlmnInfo->astForbRomLaList[ucLaiIndex]),
                         &(pstForbPlmnInfo->astForbRomLaList[ucLaiIndex + 1]),
                         ((pstForbPlmnInfo->ucForbRoamLaNum - ucLaiIndex) - 1) * sizeof(NAS_MML_LAI_STRU));
        }

        /* 删除Forbidden LA For Roam后, 更新个数 */
        pstForbPlmnInfo->ucForbRoamLaNum--;
    }
    return (ulRlst | ulIsLaInForbLaWithValidPeriodList);
}

/*****************************************************************************
 函 数 名  : NAS_MML_DelNotAllowRoamPlmnInList
 功能描述  : 从列表中删除不允许漫游的网络
 输入参数  : VOS_UINT32                         *pulPlmnNum
             NAS_MML_PLMN_ID_STRU               *pstPlmnList
 输出参数  : 删除非漫游网络后的列表
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月28日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_VOID NAS_MML_DelNotAllowRoamPlmnInList(
    VOS_UINT8                          *pucPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstPlmnList
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucPlmnNum;

    ucPlmnNum = *pucPlmnNum;


    i = 0;
    while ( i < ucPlmnNum )
    {
        if (VOS_FALSE == NAS_MML_IsPlmnIdRoamingAllowed(&pstPlmnList[i]))
        {
            if (i < (ucPlmnNum - 1))
            {
                (VOS_VOID)PS_MEM_MOVE(&pstPlmnList[i], &pstPlmnList[i+1],
                            ((ucPlmnNum - i)-1) * sizeof(NAS_MML_PLMN_ID_STRU));
            }

            ucPlmnNum--;

            continue;
        }

        i++;
    }


    *pucPlmnNum = ucPlmnNum;

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MML_DelForbPlmnInList
 功能描述  : 删除指定网络列表中的禁止网络
 输入参数  : VOS_UINT32                          ulPlmnNum,
             NAS_MML_PLMN_ID_STRU               *pHandlingPlmnList
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月28日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目:删除NAS_FEATURE_BLACK_WHITE_PLMN宏
  3.日    期   : 2012年04月21日
    作    者   : w00166186
    修改内容   : DTS2012041908119,PS ONLY时将GPRS禁止列表中网络加入了EPLMN列表，
                 导致重选限制驻留在该网络
  4.日    期   : 2012年5月7日
    作    者   : w00166186
    修改内容   : DTS20120050302236:手动搜网指定的网络在禁止列表中，注册成功后，
                 没有向LMM发送等效PLMN
*****************************************************************************/
VOS_UINT32 NAS_MML_DelForbPlmnInList(
    VOS_UINT32                          ulPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pHandlingPlmnList
)
{
    VOS_UINT8                           ucLeftPlmnNum;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo  = VOS_NULL_PTR;

    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode;

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    NAS_MML_PLMN_LOCK_CFG_INFO_STRU    *pstPlmnLockCfg     = VOS_NULL_PTR;


    /* 用于获取黑白名单 */
    pstPlmnLockCfg = NAS_MML_GetPlmnLockCfg();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    enMsMode = NAS_MML_GetMsMode();

    ucLeftPlmnNum     = (VOS_UINT8)ulPlmnNum;
    pstForbidPlmnInfo = NAS_MML_GetForbidPlmnInfo();

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    /* 用于获取黑白名单 */

    /* 删除存在于黑名单中的网络 */
    NAS_MML_DelPlmnsInRefList(&ucLeftPlmnNum, pHandlingPlmnList,
                   pstPlmnLockCfg->ucBlackPlmnLockNum, pstPlmnLockCfg->astBlackPlmnId);

    /* 删除不存在于白名单中的网络 */
    if (pstPlmnLockCfg->ucWhitePlmnLockNum != 0)
    {
        NAS_MML_DelPlmnsNotInRefList(&ucLeftPlmnNum, pHandlingPlmnList,
                       pstPlmnLockCfg->ucWhitePlmnLockNum, pstPlmnLockCfg->astWhitePlmnId);
    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    /* 删除禁止网络的网络,用户指定搜的PLMN在禁止列表时，注册成功后需要在MMC删除该PLMN，
    为了规避时序造成的删除了已经注册成功的网络，所以此处不能删除当前驻留的网络 */
    NAS_MML_DelEqualPlmnsInForbList(&ucLeftPlmnNum, pHandlingPlmnList,
                                pstForbidPlmnInfo->ucForbPlmnNum, pstForbidPlmnInfo->astForbPlmnIdList);

    /* CS卡无效或PS ONLY时删除禁止GPRS列表中的网络 */
    if ((VOS_FALSE == NAS_MML_GetSimCsRegStatus())
     || (NAS_MML_MS_MODE_PS_ONLY == enMsMode))
    {

        /* 删除禁止网络的网络,用户指定搜的PLMN在禁止列表时，注册成功后需要在MMC删除该PLMN，
        为了规避时序造成的删除了已经注册成功的网络，所以此处不能删除当前驻留的网络 */
        NAS_MML_DelEqualPlmnsInForbList(&ucLeftPlmnNum, pHandlingPlmnList,
                                        pstForbidPlmnInfo->ucForbGprsPlmnNum, pstForbidPlmnInfo->astForbGprsPlmnList);
    }

    /* 从列表中删除不允许漫游的网络 */
    NAS_MML_DelNotAllowRoamPlmnInList(&ucLeftPlmnNum, pHandlingPlmnList);

    return ucLeftPlmnNum;

}

/*****************************************************************************
 函 数 名  : NAS_MML_DelInvalidPlmnFromList
 功能描述  : 删除Plmn列表中的无效网络
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月10日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_UINT32 NAS_MML_DelInvalidPlmnFromList(
    VOS_UINT32                          ulPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstHandlingPlmnList
)
{

    VOS_UINT32                          i;

    /* 删除该列表中的无效网络 */


    i = 0;
    while ( i < ulPlmnNum )
    {
        if (VOS_FALSE == NAS_MML_IsPlmnIdValid(pstHandlingPlmnList + i))
        {
            if (i < (ulPlmnNum - 1))
            {
                (VOS_VOID)PS_MEM_MOVE(&pstHandlingPlmnList [i], &pstHandlingPlmnList[i+1],
                            ((ulPlmnNum - i) - 1 ) * sizeof(NAS_MML_PLMN_ID_STRU) );
            }
            ulPlmnNum--;
            continue;
        }

        i++;
    }


    return ulPlmnNum;

}

/*****************************************************************************
 函 数 名  : NAS_MML_DelPlmnsInRefList
 功能描述  : 将pHandlingPlmnList中的,在pRefPlmnList上的网络，删除
 输入参数  : VOS_UINT8                           *pHandlingPlmnNum,
             NAS_MML_PLMN_ID_STRU                    *pHandlingPlmnList,
             VOS_UINT8                           ucRefPlmnNum,
             NAS_MML_PLMN_ID_STRU                    *pRefPlmnList
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月23日
    作    者   : likelai
    修改内容   : 新生成函数
  2.日    期   : 2011年11月24日
    作    者   : w00167002
    修改内容   : DTS2011112405567:原有的函数名NAS_MML_IsPlmnIdInDestPlmnList
                更改为NAS_MML_IsBcchPlmnIdInDestSimPlmnList
  3.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_VOID NAS_MML_DelPlmnsInRefList(
    VOS_UINT8                          *pHandlingPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pHandlingPlmnList,
    VOS_UINT8                           ucRefPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pRefPlmnList
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucPlmnNum;
    VOS_UINT32                          ulRlst;

    ucPlmnNum = *pHandlingPlmnNum;


    i = 0;
    while ( i < ucPlmnNum )
    {
        ulRlst = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pHandlingPlmnList + i, ucRefPlmnNum, pRefPlmnList);

        if ( VOS_TRUE == ulRlst )
        {
            if (i < (ucPlmnNum - 1))
            {
                (VOS_VOID)PS_MEM_MOVE(&pHandlingPlmnList [i], &pHandlingPlmnList[ i + 1 ],
                            ((ucPlmnNum - i) - 1 ) * sizeof(NAS_MML_PLMN_ID_STRU));
            }
            ucPlmnNum--;
            continue;
        }
        i++;
    }


    *pHandlingPlmnNum = ucPlmnNum;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_DelPlmnsNotInRefList
 功能描述  : 将pHandlingPlmnList中的,不在pRefPlmnList上的网络，删除
 输入参数  : VOS_UINT8                          *pHandlingPlmnNum
             NAS_MML_PLMN_ID_STRU               *pHandlingPlmnList
             VOS_UINT8                           ucRefPlmnNum
             NAS_MML_PLMN_ID_STRU               *pRefPlmnList
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年8月3日
   作    者   : L00171473
   修改内容   : 新生成函数

 2.日    期   : 2011年11月24日
   作    者   : w00167002
   修改内容   : DTS2011112405567:原有的函数名NAS_MML_IsPlmnIdInDestPlmnList
                更改为NAS_MML_IsBcchPlmnIdInDestSimPlmnList
  3.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_VOID NAS_MML_DelPlmnsNotInRefList(
    VOS_UINT8                          *pHandlingPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pHandlingPlmnList,
    VOS_UINT8                           ucRefPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pRefPlmnList
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucPlmnNum;
    VOS_UINT32                          ulRlst;

    ucPlmnNum = *pHandlingPlmnNum;


    i = 0;
    while ( i < ucPlmnNum )
    {
        ulRlst = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pHandlingPlmnList + i, ucRefPlmnNum, pRefPlmnList);

        /* 不存在于pRefPlmnList中，则删除 */
        if ( VOS_FALSE == ulRlst )
        {
            if (i < (ucPlmnNum - 1))
            {
                (VOS_VOID)PS_MEM_MOVE(&pHandlingPlmnList [i], &pHandlingPlmnList[ i + 1 ],
                            ((ucPlmnNum - i) - 1 ) * sizeof(NAS_MML_PLMN_ID_STRU));
            }

            ucPlmnNum--;
            continue;
        }
        i++;
    }


    *pHandlingPlmnNum = ucPlmnNum;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetPlmnIdxInList
 功能描述  : 获取指定Plmn 在list中的位置
 输入参数  : NAS_MML_PLMN_ID_STRU               *pstPlmnId
             VOS_UINT32                          ulPlmnNum
             NAS_MML_PLMN_ID_STRU               *pstPlmnIdList
 输出参数  : 无
 返 回 值  : VOS_UINT32,成功时返回指定PLMN在list中的位置，失败时返回list的长度(最后位置+1)
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月26日
    作    者   : l00130025
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_GetPlmnIdxInList (
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    VOS_UINT32                          ulPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstPlmnIdList
)
{
    VOS_UINT32                          i;

    for ( i = 0; i < ulPlmnNum; i++ )
    {
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstPlmnId, (pstPlmnIdList + i)))
        {
            break;
        }
    }

    return i;
}

/*****************************************************************************
 函 数 名  :NAS_MML_IsGsmOnlyMode
 功能描述  :判断当前接入模式是否为G only
 输入参数  :pstRatOrder - 接入模式和优先级信息
 输出参数  :无
 返 回 值  :VOS_TRUE  - 当前为G单模
            VOS_FALSE - 当前不为G单模
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年8月03日
   作    者   : W00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_IsGsmOnlyMode(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatOrder
)
{
    if ( (1                        == pstRatOrder->ucRatNum)
      && (NAS_MML_NET_RAT_TYPE_GSM == pstRatOrder->aucRatPrio[0]) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  :NAS_MML_IsWcdmaOnlyMode
 功能描述  :判断当前接入模式是否为W only
 输入参数  :pstRatOrder - 接入模式和优先级信息
 输出参数  :无
 返 回 值  :VOS_TRUE  - 当前为W单模
            VOS_FALSE - 当前不为W单模
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年8月03日
   作    者   : W00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_IsWcdmaOnlyMode(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatOrder
)
{
    if ( (1                          == pstRatOrder->ucRatNum)
      && (NAS_MML_NET_RAT_TYPE_WCDMA == pstRatOrder->aucRatPrio[0]) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  :NAS_MML_IsWcdmaPrioGsm
 功能描述  :判断当前接入模式是否w优先于g
 输入参数  :pstRatOrder - 接入模式和优先级信息
 输出参数  :无
 返 回 值  :VOS_TRUE  - 当前W优先于G
            VOS_FALSE - 当前W不优先于G
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年8月03日
   作    者   : W00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_IsWcdmaPrioGsm(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatOrder
)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT8                           ucWcdmaPrioGsmFlag;

    ucWcdmaPrioGsmFlag = VOS_FALSE;

    for (ulIndex = 0; ulIndex < pstRatOrder->ucRatNum; ulIndex++)
    {
        if (NAS_MML_NET_RAT_TYPE_GSM == pstRatOrder->aucRatPrio[ulIndex])
        {
            ucWcdmaPrioGsmFlag = VOS_FALSE;
            return ucWcdmaPrioGsmFlag;
        }

        if (NAS_MML_NET_RAT_TYPE_WCDMA == pstRatOrder->aucRatPrio[ulIndex])
        {
            ucWcdmaPrioGsmFlag = VOS_TRUE;
            return ucWcdmaPrioGsmFlag;
        }
    }

    return ucWcdmaPrioGsmFlag;
}


/*****************************************************************************
 函 数 名  :NAS_MML_IsLteOnlyMode
 功能描述  :判断当前接入模式是否为Lte only
 输入参数  :pstRatOrder - 接入模式和优先级信息
 输出参数  :无
 返 回 值  :VOS_TRUE  - 当前为L单模
            VOS_FALSE - 当前不为L单模
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年8月03日
   作    者   : W00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_IsLteOnlyMode(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatOrder
)
{
    if ( (1                        == pstRatOrder->ucRatNum)
      && (NAS_MML_NET_RAT_TYPE_LTE == pstRatOrder->aucRatPrio[0]) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : Mmc_ComRemoveRoamPlmnInSrchList
 功能描述  : 从列表中删除不允许漫游的网络
 输入参数  : 网络PLMN ID列表及个数，是否用户发起列表选网
 输出参数  : 删除非漫游网络后的列表
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2009年11月19日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2011年8月03日
   作    者   : W00167002
   修改内容   : V7R1第二阶段进行调整
*****************************************************************************/
VOS_VOID NAS_MML_RemoveRoamPlmnInSrchList(
    VOS_UINT8                          *pucPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstPlmnList
)
{
    VOS_UINT32                          i;

    for ( i = 0; i < *pucPlmnNum; )
    {
        /* 如果列表中的PLMN不准许漫游，则将该PLMN移除 */
        if ( VOS_FALSE == NAS_MML_IsPlmnIdRoamingAllowed(&pstPlmnList[i]) )
        {
            /* 如果不是最后一个元素，则移除 */
            if ( (i + 1) != (*pucPlmnNum) )
            {
                (VOS_VOID)PS_MEM_MOVE(&pstPlmnList[i], &pstPlmnList[i+1],
                            ((*pucPlmnNum - i) - 1)*sizeof(NAS_MML_PLMN_ID_STRU));

            }

            /* 将总个数减一 */
            (*pucPlmnNum)--;

            continue;
        }
        i++;
    }

    return;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_IsRoam
 功能描述  : 获取当前是否处于漫游状态
 输出参数  : 无
 返 回 值  : VOS_BOOL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年8月21日
    作    者   : s46746
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsRoam()
{
    NAS_MML_PLMN_ID_STRU               *pstCurplmn = VOS_NULL_PTR;

    pstCurplmn = NAS_MML_GetCurrCampPlmnId();

    /*与HPLMN相同，直接返回允许*/
    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(pstCurplmn))
    {
        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MML_IsHplmnInEplmnList
 功能描述  : 获取当前EPLMN是否包含EPLMN
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月2日
    作    者   : b00269685
    修改内容   : 新增

*****************************************************************************/
VOS_UINT32 NAS_MML_IsHplmnInEplmnList()
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnList = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstEplmnList = NAS_MML_GetEquPlmnList();

    if (VOS_TRUE == pstEplmnList->ucValidFlg)
    {
        for (i = 0; i < pstEplmnList->ucEquPlmnNum; i++)
        {
            if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(&pstEplmnList->astEquPlmnAddr[i]))
            {
                return VOS_TRUE;
            }
        }
    }
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MML_IsCurrCampPlmnInEplmnList
 功能描述  : 获取当前EPLMN是否包含当前驻留的PLMN
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月13日
    作    者   : l00289540
    修改内容   : 新增

*****************************************************************************/
VOS_UINT32 NAS_MML_IsCurrCampPlmnInEplmnList(VOS_VOID)
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnList        = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstCurrCampPlmnId   = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstEplmnList              = NAS_MML_GetEquPlmnList();
    pstCurrCampPlmnId         = NAS_MML_GetCurrCampPlmnId();

    if (VOS_TRUE == pstEplmnList->ucValidFlg)
    {
        for (i = 0; i < pstEplmnList->ucEquPlmnNum; i++)
        {
            if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstCurrCampPlmnId, &pstEplmnList->astEquPlmnAddr[i]))
            {
                return VOS_TRUE;
            }
        }
    }
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MML_IsPlmnInEplmnList
 功能描述  : PLMN是否在EPLMN列表中
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月10日
    作    者   : z00359541
    修改内容   : 新增

*****************************************************************************/
VOS_UINT32 NAS_MML_IsPlmnInEplmnList(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnList        = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstEplmnList = NAS_MML_GetEquPlmnList();

    if (VOS_TRUE == pstEplmnList->ucValidFlg)
    {
        for (i = 0; i < pstEplmnList->ucEquPlmnNum; i++)
        {
            if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstPlmnId, &pstEplmnList->astEquPlmnAddr[i]))
            {
                return VOS_TRUE;
            }
        }
    }
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetLaiForbType
 功能描述  : 判断当前LAI的禁止类型
 输入参数  : NAS_MML_LAI_STRU
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年07月21日
   作    者   : l00130025
   修改内容   : 新生成函数

 2.日    期   : 2011年11月24日
   作    者   : w00167002
   修改内容   : DTS2011112405567:原有的函数名NAS_MML_IsPlmnIdInDestPlmnList
                更改为NAS_MML_IsBcchPlmnIdInDestSimPlmnList
  3.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目:删除NAS_FEATURE_BLACK_WHITE_PLMN宏
  4.日    期   : 2012年07月02日
    作    者   : z00161729
    修改内容   : GUL BG搜项目DTS2012063000279:L内部list搜L forbidden TAI判断需要调用L接口
  5.日    期   : 2012年10月11日
    作    者   : w00176964
    修改内容   : DTS201201002303:【移动定制黑名单】驻留TD小区,指定搜黑名单网络,NAS发起anycell
                 搜驻留W小区后，依然启动available timer
  6.日    期   : 2012年10月18日
    作    者   : w00176964
    修改内容   : DTS201201601239:UE不应该在禁止RAT的PLMN上发起注册
  7.日    期   : 2013年11月01日
    作    者   : l00208543
    修改内容   : 根据卡类型禁止网络制式
  8.日    期   : 2014年2月14日
    作    者   : z00161729
    修改内容   : DTS2014021000537:禁止网络判断未调用l接口获取注册被12拒绝网络列表
  9.日    期   : 2015年1月15日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
 10.日    期   : 2015年4月23日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
 11.日    期   : 2015年9月23日
    作    者   : z00359541
    修改内容   : 加入禁止LA有效时长列表类型的判断
*****************************************************************************/
VOS_UINT32 NAS_MML_GetLaiForbType(
    NAS_MML_LAI_STRU                   *pstLai
)
{
    VOS_UINT32                          ulPlmnLaType;
    NAS_MML_PLMN_ID_STRU               *pstPlmnId         = VOS_NULL_PTR;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulRlst;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_LMM_INFO_STRU                   stLmmInfo;
    NAS_MML_TAI_STRU                    stTai;
    VOS_UINT32                          ulForbidFlag;

    VOS_UINT32                          ulForbiddenRegLaFlag;
#endif

    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnWithRat;

    ulPlmnLaType      = NAS_MML_PLMN_FORBID_NULL;
    pstForbidPlmnInfo = NAS_MML_GetForbidPlmnInfo();
    pstPlmnId         = &(pstLai->stPlmnId);


    /* 在forbid plmn列表中 */
    ulRlst = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstPlmnId,
                                          pstForbidPlmnInfo->ucForbPlmnNum,
                                          pstForbidPlmnInfo->astForbPlmnIdList);
    if(VOS_TRUE == ulRlst)
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_GetLaiForbType FORBIDDEN:IN FORB PLMN LIST");        
        
        return NAS_MML_PLMN_FORBID_PLMN;
    }


    /* 构造当前接入技术的PLMN ID */
    stPlmnWithRat.stPlmnId.ulMcc    = pstLai->stPlmnId.ulMcc;
    stPlmnWithRat.stPlmnId.ulMnc    = pstLai->stPlmnId.ulMnc;
    stPlmnWithRat.enRat             = pstLai->enCampPlmnNetRat;

    /* 判断当前PLMN是否在禁止RAT的PLMN列表中同时当前接入技术被禁止,则认为当前PLMN为禁止网络 */
    if (VOS_TRUE == NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
    {
    
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_GetLaiForbType FORBIDDEN:IN FORB PLMN WITH PERIOD LIST");        
        
        return NAS_MML_PLMN_FORBID_PLMN;
    }

    /* 判断PLMN的RAT在禁止接入技术列表中，则认为当前RAT对应网络为禁止网络 */
    if (VOS_TRUE == NAS_MML_IsRatInForbiddenList(stPlmnWithRat.enRat))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_GetLaiForbType FORBIDDEN:IN FORB RAT LIST");        
        
        return NAS_MML_PLMN_FORBID_PLMN;
    }


    /* 该PLMN ID是否在锁网锁卡的PLMN 列表中 */
    if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInLockPlmnList(pstPlmnId))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_GetLaiForbType FORBIDDEN:IN LockPlmnList");        
        
        return NAS_MML_PLMN_FORBID_PLMN;
    }

    /* 不允许漫游时 */
    if (VOS_FALSE == NAS_MML_IsPlmnIdRoamingAllowed(pstPlmnId))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_GetLaiForbType FORBIDDEN:PlmnIdRoamingAllowed");        
        
        return NAS_MML_PLMN_FORBID_PLMN;
    }

    /* 在forbid plmn for gprs列表中 */
    ulRlst = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstPlmnId,
                                          pstForbidPlmnInfo->ucForbGprsPlmnNum,
                                          pstForbidPlmnInfo->astForbGprsPlmnList);
    if(VOS_TRUE == ulRlst)
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_GetLaiForbType:IN ForbGprsPlmnList");        
        
        ulPlmnLaType  |=   NAS_MML_PLMN_FORBID_PLMN_FOR_GPRS;
    }

    /* L下TAI需要从LAI中获取，收到L的系统消息，更新的是LAI */
#if (FEATURE_ON == FEATURE_LTE)
    ulForbidFlag         = VOS_FALSE;

    ulForbiddenRegLaFlag = NAS_MML_PLMN_FORBID_NULL;

    stTai.stPlmnId.ulMcc = pstLai->stPlmnId.ulMcc;
    stTai.stPlmnId.ulMnc = pstLai->stPlmnId.ulMnc;
    stTai.stTac.ucTac    = pstLai->aucLac[0];
    stTai.stTac.ucTacCnt = pstLai->aucLac[1];

    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        if ( MMC_LMM_SUCC == Nas_GetLteInfo(NAS_LMM_FORB_TAI_ROAM_LIST, &stLmmInfo) )
        {
            ulForbidFlag = NAS_MML_IsTaiInDestTaiList (&stTai,
                                                        stLmmInfo.u.stForbRoamTaiList.ulTaNum,
                                                        stLmmInfo.u.stForbRoamTaiList.astTa);
        }

        if (VOS_TRUE == ulForbidFlag)
        {
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_GetLaiForbType FORBIDDEN:IN stForbRoamTaiList");        
            
            ulPlmnLaType |= NAS_MML_PLMN_FORBID_PLMN;
        }

        if ( MMC_LMM_SUCC == Nas_GetLteInfo(NAS_LMM_FORB_TAI_RPOS_LIST, &stLmmInfo) )
        {
            ulForbiddenRegLaFlag = NAS_MML_IsTaiInDestTaiList (&stTai,
                                                        stLmmInfo.u.stForbRposTaiList.ulTaNum,
                                                        stLmmInfo.u.stForbRposTaiList.astTa);
        }

        if (VOS_TRUE == ulForbiddenRegLaFlag)
        {
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_GetLaiForbType FORBIDDEN REG LA:IN stForbRposTaiList");        
            
             ulPlmnLaType  |= NAS_MML_PLMN_FORBID_REG_LA;
        }

    }
    else
#endif
    {
        /* 是否在 ForbLA消息中 */
        ulRlst =  NAS_MML_GetLaiIndexInForbLaWithValidPeriodList(pstLai,
                    &(pstForbidPlmnInfo->stForbLaWithValidPeriod));

        if(NAS_MML_CUSTOMIZE_FORB_LA_MAX_NUM != ulRlst)
        {
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_GetLaiForbType FORBIDDEN REG LA:IN stForbLaWithValidPeriod");        
            
             ulPlmnLaType  |=   NAS_MML_PLMN_FORBID_ROAM_LA;
        }

        ulRlst =  NAS_MML_IsLaiInDestLaiList(pstLai,
                                            pstForbidPlmnInfo->ucForbRoamLaNum,
                                            pstForbidPlmnInfo->astForbRomLaList);

        if(VOS_TRUE == ulRlst)
        {
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_GetLaiForbType FORBIDDEN ROAM LA:IN astForbRomLaList");        
            
             ulPlmnLaType  |=   NAS_MML_PLMN_FORBID_ROAM_LA;
        }

        ulRlst =  NAS_MML_IsLaiInDestLaiList(pstLai,
                                            pstForbidPlmnInfo->ucForbRegLaNum,
                                            pstForbidPlmnInfo->astForbRegLaList);

        if (VOS_TRUE == ulRlst)
        {
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_GetLaiForbType FORBIDDEN REG LA:IN astForbRegLaList");        

            ulPlmnLaType  |=   NAS_MML_PLMN_FORBID_REG_LA;
        }
    }

    return ulPlmnLaType;
}




/*****************************************************************************
 函 数 名  : NAS_MML_IsCampInfoChanged
 功能描述  : 收到系统信息后，判断消息是否发生改变
 输入参数  :
             NAS_MML_CAMP_PLMN_INFO_STRU        *pOldCampInfo,
             NAS_MML_CAMP_PLMN_INFO_STRU        *pNewCampInfo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月28日
    作    者   : l00130025
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_IsCampPlmnInfoChanged(
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstOldCampInfo,
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstNewCampInfo
)
{
    VOS_UINT32                          i;

    /* 新老Plmn或 lac,rac,cellid或cell个数，或系统子模式是否有变化 */
    if ((pstOldCampInfo->stLai.stPlmnId.ulMcc  != pstNewCampInfo->stLai.stPlmnId.ulMcc)
     || (pstOldCampInfo->stLai.stPlmnId.ulMnc  != pstNewCampInfo->stLai.stPlmnId.ulMnc)
     || (pstOldCampInfo->ucRac                 != pstNewCampInfo->ucRac)
     || (pstOldCampInfo->enSysSubMode          != pstNewCampInfo->enSysSubMode)

     )
    {
        return VOS_TRUE;
    }

    for ( i = 0 ; i < NAS_MML_MAX_LAC_LEN ; i++ )
    {
        if (pstOldCampInfo->stLai.aucLac[i] != pstNewCampInfo->stLai.aucLac[i])
        {
            return VOS_TRUE;
        }
    }

    if (pstOldCampInfo->stCampCellInfo.ucCellNum != pstNewCampInfo->stCampCellInfo.ucCellNum)
    {
        return VOS_TRUE;
    }

    for ( i = 0 ; i < RRC_NAS_AT_CELL_MAX_NUM ; i++ )
    {
        if (pstOldCampInfo->stCampCellInfo.astCellInfo[i].ulCellId
                    != pstNewCampInfo->stCampCellInfo.astCellInfo[i].ulCellId)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MML_ConvertGprsSupportIndToSysSubMode
 功能描述  : 根据GAS上报的系统消息中GprsSupportInd参数获得当前小区的系统子模
             式
 输入参数  : VOS_UINT8 ucGprsSupportInd :当前小区是否支持GPRS
             0:不支持，1:支持GPRS, 2:支持EDGE
 输出参数  : NAS_MML_RRC_SYS_SUBMODE_ENUM_UINT8   : 系统子模式
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月20日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2011年11月30日
    作    者   : w00176964
    修改内容   : 联合注册BBIT调整

*****************************************************************************/
NAS_MML_RRC_SYS_SUBMODE_ENUM_UINT8 NAS_MML_ConvertGprsSupportIndToSysSubMode(
    VOS_UINT8                           ucGprsSupportInd
)
{
    NAS_MML_RRC_SYS_SUBMODE_ENUM_UINT8  enSysSubMode;

    switch ( ucGprsSupportInd )
    {
        case NAS_MML_GAS_SUBMODE_GSM:
            enSysSubMode = NAS_MML_RRC_SYS_SUBMODE_GSM;
            break;

        case NAS_MML_GAS_SUBMODE_GPRS:
            enSysSubMode = NAS_MML_RRC_SYS_SUBMODE_GPRS;
            break;

        case NAS_MML_GAS_SUBMODE_EDGE:
            enSysSubMode = NAS_MML_RRC_SYS_SUBMODE_EDGE;
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MML_ConvertGasNetModeToMmlNetMode, enSysSubMode invalid");
            enSysSubMode = NAS_MML_RRC_SYS_SUBMODE_NULL;
            break;
    }

    return enSysSubMode;
}

/*****************************************************************************
 函 数 名  :NAS_MML_SecContext3GTO2G
 功能描述  :通过 Ik、CK 计算 KC
 输入参数  :pucIk - 输入的IK
             pucCk - 输入的CK
 输出参数  :pucKc - 输出的KC
 返 回 值  :无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年8月9日
   作    者   : h44270
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_SecContext3GTO2G(
    VOS_UINT8                           *pucIk,
    VOS_UINT8                           *pucCk,
    VOS_UINT8                           *pucKc
)
{
    /* 临时变量，用于 for 循环 */
    VOS_UINT8       i;

    /* 保存输入参数 IK 的临时变量 */
    VOS_UINT8       aucIk[NAS_MML_UMTS_IK_LEN];

    /* 保存输入参数 CK 的临时变量 */
    VOS_UINT8       aucCk[NAS_MML_UMTS_CK_LEN];

    /* 变量 Kc */
    VOS_UINT8       aucKc[NAS_MML_GSM_KC_LEN];

    PS_MEM_SET(aucIk, 0x00, sizeof(aucIk));
    PS_MEM_SET(aucCk, 0x00, sizeof(aucCk));
    PS_MEM_SET(aucKc, 0x00, sizeof(aucKc));

    /* 获得 IK */
    PS_MEM_CPY(aucIk, pucIk, NAS_MML_UMTS_IK_LEN);

    /* 获得 CK */
    PS_MEM_CPY(aucCk, pucCk, NAS_MML_UMTS_CK_LEN);

    /* 调用公式计算 aucKc */
    /*Kc[GSM] = CK1 xor CK2 xor IK1 xor IK2（其中CKi 和 IKi 的长度都为 64 bits ；
    CK = CK1 || CK2 ；IK = IK1 || IK2。*/
    for (i = 0; i < NAS_MML_GSM_KC_LEN; i ++)
    {
        aucKc[i] = aucCk[i] ^ aucCk[NAS_MML_GSM_KC_LEN + i];
    }
    for (i = 0; i < NAS_MML_GSM_KC_LEN; i ++)
    {
        aucKc[i] = aucKc[i] ^ aucIk[i];
    }
    for (i = 0; i < NAS_MML_GSM_KC_LEN; i ++)
    {
        aucKc[i] = aucKc[i] ^ aucIk[NAS_MML_GSM_KC_LEN + i];
    }

    /* 将 KC 写回到输出参数中 */
    PS_MEM_CPY(pucKc, aucKc, NAS_MML_GSM_KC_LEN);

    return;

}

/*****************************************************************************
 函 数 名  :NAS_MML_SecContext2GTO3G
 功能描述  :通过 Kc 计算 IK、CK
 输入参数  :pucKc - 输出的KC
 输出参数  :pucIk - 输入的IK
             pucCk - 输入的CK
 返 回 值  :无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年8月9日
   作    者   : h44270
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_SecContext2GTO3G(
    VOS_UINT8                           *pucIk,
    VOS_UINT8                           *pucCk,
    VOS_UINT8                           *pucKc
)
{
    /* 临时变量，用于 for 循环 */
    VOS_UINT8       i;

    /* 变量 IK */
    VOS_UINT8       aucIk[NAS_MML_UMTS_IK_LEN];

    /* 变量 CK */
    VOS_UINT8       aucCk[NAS_MML_UMTS_CK_LEN];

    /* 保存输入参数 KC 的临时变量 */
    VOS_UINT8       aucKc[NAS_MML_GSM_KC_LEN];

    PS_MEM_SET(aucIk, 0x00, sizeof(aucIk));
    PS_MEM_SET(aucCk, 0x00, sizeof(aucCk));
    PS_MEM_SET(aucKc, 0x00, sizeof(aucKc));

    /* 获得 KC */
    PS_MEM_CPY(aucKc, pucKc, NAS_MML_GSM_KC_LEN);

    /* 调用公式计算 IK、CK */
    /* 转换加密密钥 */
    /* ck=kc||kc(其中||为连接符号) */
    PS_MEM_CPY(aucCk, aucKc, NAS_MML_GSM_KC_LEN);
    PS_MEM_CPY((aucCk + NAS_MML_GSM_KC_LEN), aucKc, NAS_MML_GSM_KC_LEN);

    /* 转换一致性检查密钥 */
    /* ik=Kc1 xor Kc2 || Kc || Kc1 xor Kc2(其中||为连接符号、Kc = Kc1 || Kc2) */
    for (i = 0; i < (NAS_MML_GSM_KC_LEN/2); i++)
    {
        aucIk[i] = aucKc[i] ^ aucKc[(NAS_MML_GSM_KC_LEN/2) + i];
        aucIk[NAS_MML_GSM_KC_LEN + (NAS_MML_GSM_KC_LEN/2) + i] = aucIk[i];
    }
    PS_MEM_CPY((aucIk + (NAS_MML_GSM_KC_LEN/2)), aucKc, NAS_MML_GSM_KC_LEN);

    /* 将 IK 写回到输出参数中 */
    PS_MEM_CPY(pucIk, aucIk, NAS_MML_UMTS_IK_LEN);

    /* 将 CK 写回到输出参数中 */
    PS_MEM_CPY(pucCk, aucCk, NAS_MML_UMTS_CK_LEN);

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MML_ConvertNasPlmnToLMMFormat
 功能描述  : 将MCC和MNC分开的格式转换为LMM的3字节格式PLMN(LAI格式的PLMN)
            (10.5.1.3 Location Area Identification)
             8 7 6 5     4 3 2 1
            Location Area Identification IEI       octet 1
            MCC digit 2     MCC digit 1            octet 2
            MNC digit 3     MCC digit 3            octet 3
            MNC digit 2     MNC digit 1            octet 4

            例如:230,02f (mcc:0x000302,mnc:0x0f0200)  --> 32f020

 输入参数  : pGUNasPlmn,GU格式的PLMN ID
 输出参数  : pLMMPlmn:L格式的PLMN ID
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月28日
    作    者   : likelai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_ConvertNasPlmnToLMMFormat(
    MMC_LMM_PLMN_ID_STRU               *pstLMMPlmn,
    NAS_MML_PLMN_ID_STRU               *pstGUNasPlmn
)
{
    pstLMMPlmn->aucPlmnId[0]
      = (VOS_UINT8)(0x0000000F & pstGUNasPlmn->ulMcc);
    pstLMMPlmn->aucPlmnId[0]
     |= (VOS_UINT8)((0x00000F00 & pstGUNasPlmn->ulMcc) >> 4);

    pstLMMPlmn->aucPlmnId[1]
     = (VOS_UINT8)((0x000F0000 & pstGUNasPlmn->ulMcc) >> 16);

    pstLMMPlmn->aucPlmnId[1]
     |= (VOS_UINT8)((0x000F0000 & pstGUNasPlmn->ulMnc) >> 12);

    pstLMMPlmn->aucPlmnId[2]
     = (VOS_UINT8)(0x0000000F & pstGUNasPlmn->ulMnc);
    pstLMMPlmn->aucPlmnId[2]
     |= (VOS_UINT8)((0x00000F00 & pstGUNasPlmn->ulMnc) >> 4);

    return ;

}
#endif

/*****************************************************************************
 函 数 名  : NAS_MML_SortSpecRatPrioHighest
 功能描述  : 将指定接入技术优先级调整到最高
 输入参数  : enSpecRat
 输出参数  : pstPrioRatList,接入技术优先顺序
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月19日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SortSpecRatPrioHighest(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enSpecRat,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList
)
{
    VOS_UINT32                          i;

    /* 排序方法是，在pstPrioRatList找到指定的接入技术后，将其放在pstPrioRatList最前面 */
    for (i = 0; i < pstPrioRatList->ucRatNum; i++)
    {
        if (enSpecRat == pstPrioRatList->aucRatPrio[i])
        {
            (VOS_VOID)PS_MEM_MOVE(&(pstPrioRatList->aucRatPrio[1]),
                        &(pstPrioRatList->aucRatPrio[0]), i);

            pstPrioRatList->aucRatPrio[0] = enSpecRat;

            break;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SortSpecRatPrioLowest
 功能描述  : 将指定接入技术优先级调整到最低
 输入参数  : enSpecRat
 输出参数  : pstPrioRatList,接入技术优先顺序
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月19日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2013年8月26日
   作    者   : w00242748
   修改内容   : DTS2013071808373,编译告警清理
*****************************************************************************/
VOS_VOID NAS_MML_SortSpecRatPrioLowest(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enSpecRat,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList
)
{
    VOS_UINT32                             i;
    VOS_UINT8                              ucRatNumIndex;

    if (pstPrioRatList->ucRatNum <= 1)
    {
        return;
    }

    ucRatNumIndex = pstPrioRatList->ucRatNum - 1;

    /* 排序方法是，在pstPrioRatList找到指定的接入技术后，将其放在pstPrioRatList最后面 */
    for (i = 0; i < ucRatNumIndex; i++)
    {
        if (enSpecRat == pstPrioRatList->aucRatPrio[i])
        {
            /*lint -e961*/
            (VOS_VOID)PS_MEM_MOVE(&(pstPrioRatList->aucRatPrio[i]),
                        &(pstPrioRatList->aucRatPrio[i+1]),
                        (pstPrioRatList->ucRatNum-i-1));
            /*lint +e961*/
            pstPrioRatList->aucRatPrio[pstPrioRatList->ucRatNum-1] = enSpecRat;

            break;
        }
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MML_DelSpecRatInPrioRatList
 功能描述  : 将指定接入技术优先级从列表中删除
 输入参数  : enSpecRat
 输出参数  : pstPrioRatList,接入技术优先顺序
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年10月21日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_DelSpecRatInPrioRatList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enSpecRat,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList
)
{
    VOS_UINT32                          i;

    if (pstPrioRatList->ucRatNum <= 1)
    {
        return;
    }

    /* 排序方法是，在pstPrioRatList找到指定的接入技术后，将后面的接入技术前移 */
    for (i = 0; i < pstPrioRatList->ucRatNum; i++)
    {
        if (enSpecRat == pstPrioRatList->aucRatPrio[i])
        {
            /*lint -e961*/
            (VOS_VOID)PS_MEM_MOVE(&(pstPrioRatList->aucRatPrio[i]),
                        &(pstPrioRatList->aucRatPrio[i+1]),
                        (pstPrioRatList->ucRatNum-i-1));
            /*lint +e961*/

            pstPrioRatList->ucRatNum--;
            break;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_IsPlmnIdForbiddenByWhiteBlackList
 功能描述  : 判断PLMN ID是否黑名单或者不在白名单
 输入参数  : pstPlmnId 判断的PLMN ID
 输出参数  : 无
 返 回 值  : VOS_TRUE  : PLMN ID 在黑名单或不在白名单
             VOS_FALSE : PLMN ID 在白名单但不在黑名单
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011年09月24日
   作    者   : w00166186
   修改内容   : 新生成函数

 2.日    期   : 2011年11月24日
   作    者   : w00167002
   修改内容   : DTS2011112405567:原有的函数名NAS_MML_IsPlmnIdInDestPlmnList
                更改为NAS_MML_IsBcchPlmnIdInDestSimPlmnList
*****************************************************************************/
VOS_UINT32 NAS_MML_IsPlmnIdForbiddenByWhiteBlackList (
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MML_PLMN_LOCK_CFG_INFO_STRU    *pstPlmnLockCfg = VOS_NULL_PTR;
    /* 用于获取黑白名单 */
    pstPlmnLockCfg = NAS_MML_GetPlmnLockCfg();

    if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstPlmnId,
                                                   pstPlmnLockCfg->ucBlackPlmnLockNum,
                                                   pstPlmnLockCfg->astBlackPlmnId))     /* 该PLMN在黑名单列表中 */
    {
       return VOS_TRUE;
    }

    if (pstPlmnLockCfg->ucWhitePlmnLockNum != 0)
    {

        if (VOS_FALSE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstPlmnId,
                                                        pstPlmnLockCfg->ucWhitePlmnLockNum,
                                                        pstPlmnLockCfg->astWhitePlmnId))     /* 该PLMN不在白名单列表中 */
        {
            return VOS_TRUE;
        }

    }

    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
 函 数 名  : NAS_MML_UpdateEpsConnectionStatus
 功能描述  : 更新LMM的链接状态
 输入参数  : enEpsConnState:EPS链接状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月23日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2012年5月15日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
*****************************************************************************/
VOS_VOID NAS_MML_UpdateEpsConnectionStatus(MMC_LMM_CONN_STATE_ENUM_UINT32 enEpsConnState)
{
    /* 更新LMM的链接状态 */
    switch (enEpsConnState)
    {
        case MMC_LMM_CONN_ESTING:
        case MMC_LMM_CONNECTED_SIG:
            NAS_MML_SetEpsSigConnStatusFlg(VOS_TRUE);
            NAS_MML_SetEpsServiceConnStatusFlg(VOS_FALSE);
            break;

        case MMC_LMM_CONNECTED_DATA:
            NAS_MML_SetEpsServiceConnStatusFlg(VOS_TRUE);
            break;

        case MMC_LMM_CONN_IDLE:
            NAS_MML_SetEpsSigConnStatusFlg(VOS_FALSE);
            NAS_MML_SetEpsServiceConnStatusFlg(VOS_FALSE);
            break;

        default:
            break;
    }

}



/*****************************************************************************
 函 数 名  : NAS_MML_IsCsfbServiceStatusExist
 功能描述  : 判断当前是否有CSFB业务标志
 输入参数  : 无
 输出参数  : VOS_TRUE: 存在CSFB业务标志
              VOS_FALSE:不存在CSFB业务标志
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年2月15日
   作    者   : w00167002
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsCsfbServiceStatusExist(VOS_VOID)
{
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enCsfbServiceStatus;
    VOS_UINT32                                              ulCsfbExistFlag;

    /* 默认CSFB不存在 */
    ulCsfbExistFlag     = VOS_FALSE;
    enCsfbServiceStatus = NAS_MML_GetCsfbServiceStatus();

    switch ( enCsfbServiceStatus )
    {
        /* CSFB标志不存在 */
        case NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST :
            ulCsfbExistFlag = VOS_FALSE;
            break;

        /* 存在MO非紧急呼叫的CC的CSFB标志 */
        case NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_CC_EXIST :
            ulCsfbExistFlag = VOS_TRUE;
            break;

        /* 存在MO的SS的CSFB标志 */
        case NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST :
            ulCsfbExistFlag = VOS_TRUE;
            break;

        /* 存在MO急呼叫的CSFB标志 */
        case NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST :
            ulCsfbExistFlag = VOS_TRUE;
            break;

        /* 存在MT呼叫的CSFB标志 */
        case NAS_MML_CSFB_SERVICE_STATUS_MT_EXIST :
            ulCsfbExistFlag = VOS_TRUE;
            break;

        /* CSFB标志不存在 */
        default:
            ulCsfbExistFlag = VOS_FALSE;
            break;
    }

    return ulCsfbExistFlag;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetLteUeOperationMode
 功能描述  : 获取L的手机模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 获取L的手机模式
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年10月28日
   作    者   : z00161729
   修改内容   : 新生成函数

  2.日    期   : 2012年2月24日
    作    者   : w00167002
    修改内容   : V7R1C50 支持CSFB特性修改
                  1.当前手机模式为PS ONLY，UE_USAGE_SETTING为数据中心，,则当前
                    LTE的模式为NAS_MML_LTE_UE_OPERATION_MODE_PS_2
                  2.当前手机模式为PS ONLY，UE_USAGE_SETTING为语音中心，,则当前
                    LTE的模式为NAS_MML_LTE_UE_OPERATION_MODE_PS_1
                  3.当前手机模式为NAS_MML_MS_MODE_PS_CS，UE_USAGE_SETTING为数据中心，,则当前
                    LTE的模式为NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_2
                  4.当前手机模式为NAS_MML_MS_MODE_PS_CS，UE_USAGE_SETTING为语音中心，,则当前
                    LTE的模式为NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1
*****************************************************************************/
NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8 NAS_MML_GetLteUeOperationMode( VOS_VOID)
{
    NAS_MML_LTE_UE_USAGE_SETTING_ENUM_UINT8                 enLteUeUsageSetting;
    NAS_MML_MS_MODE_ENUM_UINT8                              enMsMode;

    enMsMode            = NAS_MML_GetMsMode();
    enLteUeUsageSetting = NAS_MML_GetLteUeUsageSetting();

    /* PS ONLY且为数据中心，则为PS_2 */
    if ( (NAS_MML_MS_MODE_PS_ONLY                    == enMsMode)
      && (NAS_MML_LTE_UE_USAGE_SETTING_DATA_CENTRIC  == enLteUeUsageSetting) )
    {
        return NAS_MML_LTE_UE_OPERATION_MODE_PS_2;
    }

    /* CS_PS 且为数据中心，则为CS_PS_2 */
    if ( (NAS_MML_MS_MODE_PS_CS                      == enMsMode)
      && (NAS_MML_LTE_UE_USAGE_SETTING_DATA_CENTRIC  == enLteUeUsageSetting) )
    {
        return NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_2;
    }

    /* PS ONLY且为语音中心，则为PS_1 */
    if ( (NAS_MML_MS_MODE_PS_ONLY                    == enMsMode)
      && (NAS_MML_LTE_UE_USAGE_SETTING_VOICE_CENTRIC == enLteUeUsageSetting) )
    {
        return NAS_MML_LTE_UE_OPERATION_MODE_PS_1;
    }

    /* CS_PS 且为语音中心，则为CS_PS_1 */
    if ( (NAS_MML_MS_MODE_PS_CS                      == enMsMode)
      && (NAS_MML_LTE_UE_USAGE_SETTING_VOICE_CENTRIC == enLteUeUsageSetting) )
    {
        return NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1;
    }

    /* 异常处理,PS ONLY，则为PS_2 */
    if ( NAS_MML_MS_MODE_PS_ONLY                    == enMsMode )
    {
        return NAS_MML_LTE_UE_OPERATION_MODE_PS_2;
    }

    /* CS_PS，则为CS_PS_2 */
    return NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_2;
}


/*****************************************************************************
 函 数 名  : NAS_MML_IsCsfbMoServiceStatusExist
 功能描述  : 判断当前是否有CSFB MO业务标志
 输入参数  : 无
 输出参数  : VOS_TRUE: 存在CSFB MO业务标志
              VOS_FALSE:不存在CSFB MO业务标志
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年6月10日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsCsfbMoServiceStatusExist(VOS_VOID)
{
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enCsfbServiceStatus;

    enCsfbServiceStatus = NAS_MML_GetCsfbServiceStatus();

    if ( (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_CC_EXIST == enCsfbServiceStatus)
      || (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == enCsfbServiceStatus)
      || (NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST == enCsfbServiceStatus) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


#endif
/*****************************************************************************
 函 数 名  : NAS_MML_IsEquPlmnInfoChanged
 功能描述  : 判断LAU accpect消息中带的EPLMN和MML中保存的EPLMN是否相同
 输入参数  : pstSrcEquPlmnInfo --源EquPlmn信息
 输出参数  : 无
 返 回 值  : VOS_TRUE:等效PLMN改变
             VOS_FALSE:等效PLMN没有改变
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2010年10月08日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2011年11月24日
   作    者   : w00167002
   修改内容   : DTS2011112405567:原有的函数名NAS_MML_IsPlmnIdInDestPlmnList
                更改为NAS_MML_IsBcchPlmnIdInDestSimPlmnList
 3.日    期   : 2011年12月27日
   作    者   : l00130025
   修改内容   : DTS2011122702947: Eplmn列表比较错误,新的PlmnList是老的EplmnList的子集时处理错误
*****************************************************************************/
VOS_UINT32 NAS_MML_IsEquPlmnInfoChanged(
    NAS_MML_EQUPLMN_INFO_STRU          *pstSrcEquPlmnInfo
)
{
    VOS_UINT32                          i;
    NAS_MML_EQUPLMN_INFO_STRU          *pstDstEquPlmnInfo = VOS_NULL_PTR;

    pstDstEquPlmnInfo   = NAS_MML_GetEquPlmnList();

    /* 等效PLMN的个数相等，且等效PLMN完全相同，则Eplmn信息没有改变 */
    if ( pstSrcEquPlmnInfo->ucEquPlmnNum == pstDstEquPlmnInfo->ucEquPlmnNum )
    {
        for ( i = 0 ; i < pstSrcEquPlmnInfo->ucEquPlmnNum; i++ )
        {
            if ((pstSrcEquPlmnInfo->astEquPlmnAddr[i].ulMcc != pstDstEquPlmnInfo->astEquPlmnAddr[i].ulMcc)
             || (pstSrcEquPlmnInfo->astEquPlmnAddr[i].ulMnc != pstDstEquPlmnInfo->astEquPlmnAddr[i].ulMnc))
            {
                /* 等效PLMN改变，返回 VOS_TRUE */
                return VOS_TRUE;
            }

        }

        /* 等效PLMN没有改变，返回 VOS_FALSE */
        return VOS_FALSE;
    }

    /* 等效PLMN的个数不等，等效PLMN肯定发生了改变，返回 VOS_TRUE */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetMsNetworkCapability
 功能描述  : 获取GU 的ms network capability
 输入参数  : 无
 输出参数  : GU 的ms network capability
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年12月08日
    作    者   : z00161729
    修改内容   : 新生成函数

  2.日    期   : 2012年3月22日
    作    者   : z40661
    修改内容   : DTS2012032004429 MS capacity能力的修改
  3.日    期   : 2012年5月16日
    作    者   : l00171473
    修改内容   : DTS2012051003514, ISR能力的BIT位赋值修改

  4.日    期   : 2013年5月23日
    作    者   : z00234330
    修改内容   : DTS2013052301419, ISR能力通过NVIM项控制
*****************************************************************************/
VOS_VOID NAS_MML_GetMsNetworkCapability(
    NAS_MML_MS_NETWORK_CAPACILITY_STRU  *pstMsNetworkCapbility
)
{
    VOS_INT8                            cVersion;
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability = VOS_NULL_PTR;


#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode;
    VOS_UINT8                           ucIsrSupport;

    enMsMode        = NAS_MML_GetMsMode();
    ucIsrSupport    = NAS_MML_GetIsrSupportFlg();
#endif

    pstMsCapability = NAS_MML_GetMsCapability();
    cVersion        = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_PS);

    pstMsNetworkCapbility->ucNetworkCapabilityLen = NAS_MML_DEFAULT_NETWORKCAPABILITY_LEN;
    PS_MEM_CPY(pstMsNetworkCapbility->aucNetworkCapability, pstMsCapability->stMsNetworkCapability.aucNetworkCapability,
                pstMsNetworkCapbility->ucNetworkCapabilityLen);

    if(PS_PTL_VER_PRE_R99 == cVersion)
    {
        pstMsNetworkCapbility->aucNetworkCapability[0] &= 0xfe;
    }
    else
    {
        pstMsNetworkCapbility->aucNetworkCapability[0] |= 0x01;
    }

    if (PS_PTL_VER_R7 <= cVersion)
    {
        /* 目前NV项中Network cap填写长度为2,如果协议版本为R7或R7之后,其长度为3 */
        pstMsNetworkCapbility->ucNetworkCapabilityLen++;

        if (pstMsCapability->stMsNetworkCapability.ucNetworkCapabilityLen > 2)
        {
            pstMsNetworkCapbility->aucNetworkCapability[2] = pstMsCapability->stMsNetworkCapability.aucNetworkCapability[2];
        }
        else
        {
            pstMsNetworkCapbility->aucNetworkCapability[2] = 0x0;
        }

#if (FEATURE_ON == FEATURE_LTE)

        /* 如果支持LTE且模式为CS_PS时认为支持EMM Combined procedures capability */
        if ((VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
         && (NAS_MML_MS_MODE_PS_CS == enMsMode))
        {
            pstMsNetworkCapbility->aucNetworkCapability[2] |= 0x20;
        }
        else
#endif
        {
            pstMsNetworkCapbility->aucNetworkCapability[2] &= 0xDF;
        }
        /* 如果支持LTE,则认为支持ISR, ISR support对应bit填1 */

#if (FEATURE_ON == FEATURE_LTE)
        if ( (VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
          && (VOS_TRUE == ucIsrSupport))
        {
            pstMsNetworkCapbility->aucNetworkCapability[2] |= 0x10;
        }
        else
#endif
        {
            pstMsNetworkCapbility->aucNetworkCapability[2] &= 0xEF;
        }

    }
}

/*****************************************************************************
 函 数 名  : NAS_MML_IsEquPlmnInfoChanged
 功能描述  : 判断LAU accpect消息中带的EPLMN和MML中保存的EPLMN是否相同
 输入参数  : ulLineNO - 复位时函数所在的文件的行数
              ulFileID - 复位时函数所在的文件ID
 输出参数  : 无
 返 回 值  : VOS_TRUE:等效PLMN改变
             VOS_FALSE:等效PLMN没有改变
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月13日
   作    者   : w00167002
   修改内容   : DTS2011120702166:新生成函数，封装复位信息
 2.日    期   : 2012年5月29日
   作    者   : l00171473
   修改内容   : DTS2012053002974, 为便于问题定位, 复位时保存接入层的调用栈
 3.日    期   : 2015年1月27日
   作    者   : wx270776
   修改内容   : DTS2015011212939, 复位时增加复位场景
 4.日    期   : 2015年11月28日
   作    者   : z00359541
   修改内容   : DTS2015112803743, 复位时增加可维可测信息输出
*****************************************************************************/
VOS_VOID NAS_MML_SoftReBoot_WithLineNoAndFileID(
    VOS_UINT32                          ulLineNO,
    VOS_UINT32                          ulFileID,
    NAS_MML_REBOOT_SCENE_ENUM_UINT8     ucRebootScean
)
{
    NAS_MML_LOG_EVENT_STATE_STRU       *pstLogEventState    = VOS_NULL_PTR;
    VOS_UINT32                          ulTaskTcb;
    VOS_UINT32                          ulPid;
    VOS_UINT32                          enFsmId;
    VOS_UINT32                          enFsmTopState;

    pstLogEventState = &(NAS_MML_GetMmlCtx()->stMaintainInfo.stLogEventState);


#if   (FEATURE_ON == FEATURE_LTE)
    if ( NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        ulPid = PS_PID_MM;
    }
    else
#endif
    {
        /* GAS 和 WRR的FID相同 */
        ulPid = WUEPS_PID_WRR;
    }

    ulTaskTcb = VOS_GetTCBFromPid(ulPid);

    enFsmTopState = NAS_MMC_GetFsmTopState();
    enFsmId       = NAS_MMC_GetCurrFsmId();
    /* 复位时保存接入层的TCB信息 */
    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_SoftReBoot_WithLineNoAndFileID(): Trigger modem reset");
    mdrv_om_system_error( NAS_REBOOT_MOD_ID_MML | (VOS_INT)ucRebootScean
                          | (VOS_INT)(enFsmTopState << 8) | (VOS_INT)(enFsmId << 16),
                      (VOS_INT)ulTaskTcb,
                      (VOS_INT)((ulFileID << 16) | ulLineNO),
                      (VOS_CHAR *)(pstLogEventState),
                      sizeof(NAS_MML_LOG_EVENT_STATE_STRU) );
    return;

}

/*****************************************************************************
 函 数 名  : NAS_MML_IsRaiChanged
 功能描述  : 判断RAI是否改变
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:RAI改变
             VOS_FALSE:RAI未改变
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年11月08日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MML_IsRaiChanged(VOS_VOID)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo;
    NAS_MML_RAI_STRU                   *pstLastSuccRai;
    VOS_UINT32                           i;

    pstCampInfo    = NAS_MML_GetCurrCampPlmnInfo();
    pstLastSuccRai = NAS_MML_GetPsLastSuccRai();

    if ((pstCampInfo->stLai.stPlmnId.ulMcc != pstLastSuccRai->stLai.stPlmnId.ulMcc)
     || (pstCampInfo->stLai.stPlmnId.ulMnc != pstLastSuccRai->stLai.stPlmnId.ulMnc)
     || (pstCampInfo->ucRac != pstLastSuccRai->ucRac))
    {
        return VOS_TRUE;
    }

    for ( i = 0 ; i < NAS_MML_MAX_LAC_LEN ; i++ )
    {
        if (pstCampInfo->stLai.aucLac[i] != pstLastSuccRai->stLai.aucLac[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;

}

/*****************************************************************************
 函 数 名  : NAS_MML_CompareLai
 功能描述  : 判断LAI是否改变
 输入参数  :
             NAS_MML_LAI_STRU                    *pstCurLai,
             NAS_MML_LAI_STRU                    *pstOldLai
 输出参数  : 无
 返 回 值  : VOS_TRUE:LAI相同
             VOS_FALSE:LAI不相同
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年06月22日
    作    者   : w00166186
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MML_CompareLai(
    NAS_MML_LAI_STRU                    *pstCurLai,
    NAS_MML_LAI_STRU                    *pstOldLai
)
{
    VOS_UINT32                         i;

    if (VOS_FALSE == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstCurLai->stPlmnId), &(pstOldLai->stPlmnId)))
    {
        return VOS_FALSE;
    }

    for ( i = 0 ; i < NAS_MML_MAX_LAC_LEN ; i++ )
    {
        if (pstCurLai->aucLac[i] != pstOldLai->aucLac[i])
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MML_IsNetworkRegFailCause
 功能描述  : 判断是否是用户自定义的注册原因值还是跟网侧真实交互的注册原因值
 输入参数  : usRegFailCause: 注册原因值
 输出参数  : 无
 返 回 值  : VOS_FALSE: 用户自定的注册原因值
              VOS_TRUE:跟网侧真实交互的注册原因值
 调用函数  :
 被调函数  :

 修改历史      :

  1.日    期   : 2012年1月3日
    作    者   : w00167002
    修改内容   : DTS2011122006209:判断是否是用户自定义的注册原因值还是跟网侧
                  真实交互的注册原因值
*****************************************************************************/
VOS_UINT32 NAS_MML_IsNetworkRegFailCause(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 usRegFailCause
)
{
    /* 原因值小于280时，则是跟网侧交互的注册原因值 */
    if ( usRegFailCause < NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT )
    {
        return VOS_TRUE;
    }

    /* 原因值大于等于280时，则是用户自定义的注册原因值 */
    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MML_IsRegFailCauseNotifyLmm
 功能描述  : 判断GU注册失败原因值是否需要通知给LMM
 输入参数  : usRegFailCause: 注册原因值
 输出参数  : 无
 返 回 值  : VOS_FALSE: 不需要将GU注册失败原因值通知给LMM
             VOS_TRUE: 需要将GU注册失败原因值通知给LMM
 调用函数  :
 被调函数  :

 修改历史      :

  1.日    期   : 2012年1月3日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsRegFailCauseNotifyLmm(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  usRegFailCause
)
{
    /* 原因值小于300时，需要将注册结果通知给LMM */
    if ( usRegFailCause < NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE )
    {
        return VOS_TRUE;
    }

    /* 原因值大于等于300时，*/
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MML_UnCompressData
 功能描述  : 解压缩算法
 输入参数  : pucDest    - 解压缩后数据首地址，前四个字节存放解压缩后数据长度，第五个字节开始存放解压缩后的数据
             pulDestLen - 解压缩的数据长度
             pucSrc     - 解压缩前的数据首地址
             ulSrcLen  - 解压缩前的数据长度
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月29日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_UnCompressData(
    VOS_UINT8                          *pucDest,
    VOS_UINT32                         *pulDestLen,
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                         *pulSrcLen
)
{
    VOS_UINT32                          ulRslt;

    /* 格式为,cmpsSize(32BITs) + data(length=cmpsSize) */

    /* 前四个字节为cmpsSize,获取cmpsSize */
    PS_MEM_CPY(pulSrcLen, pucSrc, sizeof(VOS_UINT32));
    pucSrc += sizeof(VOS_UINT32);

    /* 从第五个字节开始存放压缩后的数据 */
    ulRslt  = (VOS_UINT32)_uncompress(pucDest, (unsigned long *)pulDestLen,
                                      pucSrc, *pulSrcLen);
    if (VOS_OK != ulRslt)
    {
        NAS_WARNING_LOG1(WUEPS_PID_MMC,
                         "NAS_MML_UnCompressData: ulRslt",
                         ulRslt);

        return VOS_FALSE;
    }

    /* 补充4个cmpsSize空间 */
    *pulSrcLen += sizeof(VOS_UINT32);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MML_CompressData
 功能描述  : 压缩算法
 输入参数  : pucDest    - 压缩后数据首地址，前四个字节存放压缩后数据长度，第五个字节开始存放压缩后的数据
             pulDestLen - 压缩后码流长度
             pucSrc     - 压缩前源数据首地址
             ulSrcLen   - 压缩前数据码流长度
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月30日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  NAS_MML_CompressData(
    VOS_UINT8                          *pucDest,
    VOS_UINT32                         *pulDestLen,
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulSrcLen
)
{
    VOS_UINT32                          ulRslt;

    /*格式为,cmpsSize(32BITs) + data(length=cmpsSize)*/
    if ((*pulDestLen) < sizeof(VOS_UINT32))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,
                         "NAS_MML_CompressData: 剩余空间不足");
        return VOS_FALSE;
    }

    /*预留前四个字节，从第五个字节开始存放压缩后的数据*/
    (*pulDestLen) -= sizeof(VOS_UINT32);

    ulRslt         = (VOS_UINT32)compress(pucDest + sizeof(VOS_UINT32), (unsigned long *)pulDestLen,
                                   pucSrc, ulSrcLen);

    if( VOS_OK != ulRslt )
    {
        NAS_WARNING_LOG1(WUEPS_PID_MMC,
                         "NAS_MML_CompressData: compress", ulRslt);

        return VOS_FALSE;
    }

    /*在预留的前四个字节上，填充cmpsSize*/
    PS_MEM_CPY( pucDest, pulDestLen, sizeof(VOS_UINT32));

    /*补充4个字节长度*/
    (*pulDestLen) += sizeof(VOS_UINT32);

    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : NAS_MML_IsSndOmPcRecurMsgValid
 功能描述  : 判断当前向SDT发送PC 回放消息是否有效
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月23日
    作    者   : L00171473
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsSndOmPcRecurMsgValid(VOS_VOID)
{
    /* 当前UE与PC工具未连接, 无需发送回放消息 */
    if ( VOS_FALSE == NAS_MML_GetOmConnectFlg() )
    {
        return VOS_FALSE;
    }

#ifndef WIN32
    /* 当前PC工具未使能NAS回放消息的发送, 无需发送回放消息 */
    if ( VOS_FALSE == NAS_MML_GetOmPcRecurEnableFlg() )
    {
        return VOS_FALSE;
    }
#endif

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MML_DelEqualPlmnsInForbList
 功能描述  : 将等效PLMN中在禁止列表且不是当前驻留网络删除
 输入参数  : VOS_UINT8                           *pEPlmnNum,
             NAS_MML_PLMN_ID_STRU                    *pEPlmnList,
             VOS_UINT8                           ucRefPlmnNum,
             NAS_MML_PLMN_ID_STRU                    *pRefPlmnList
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年05月07日
    作    者   : w00166186
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_DelEqualPlmnsInForbList(
    VOS_UINT8                          *pEPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pEPlmnList,
    VOS_UINT8                           ucRefPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pRefPlmnList
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucPlmnNum;
    VOS_UINT32                          ulRlst;
    NAS_MML_PLMN_ID_STRU               *pstCurrPlmnId;                          /* PlMN标识 */
    NAS_MML_PLMN_ID_STRU               *pstEPlmn;

    pstCurrPlmnId = NAS_MML_GetCurrCampPlmnId();

    ucPlmnNum = *pEPlmnNum;

    for ( i = 0; i < ucPlmnNum;  )
    {
        ulRlst = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pEPlmnList + i, ucRefPlmnNum, pRefPlmnList);

        pstEPlmn = pEPlmnList + i;

        /* 将在禁止列表且不是当前驻留网络删除 */
        if ((VOS_FALSE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstCurrPlmnId, pstEPlmn))
         && ( VOS_TRUE == ulRlst ))
        {
            if (i < (ucPlmnNum - 1))
            {
                (VOS_VOID)PS_MEM_MOVE(&pEPlmnList [i], &pEPlmnList[ i + 1 ],
                            ((ucPlmnNum - i) - 1 ) * sizeof(NAS_MML_PLMN_ID_STRU));
            }

            ucPlmnNum--;

            if ( i > 0 )
            {
                i--;
            }
            else
            {
                continue;
            }

        }

        i++;
    }

    *pEPlmnNum = ucPlmnNum;

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MML_IsPsBearerExist
 功能描述  : 是否存在PS承载
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 存在PS承载
             VOS_FALSE - 不存在PS承载
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月7日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_IsPsBearerExist(VOS_VOID)
{
    NAS_MML_PS_BEARER_CONTEXT_STRU     *pstPsBearerCtx;
    VOS_UINT32                          i;

    pstPsBearerCtx = NAS_MML_GetPsBearerCtx();

    for (i = 0; i < NAS_MML_MAX_PS_BEARER_NUM; i++)
    {
        if (NAS_MML_PS_BEARER_STATE_ACTIVE == pstPsBearerCtx[i].enPsBearerState)
        {
            return VOS_TRUE;
        }
    }
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MML_UpdateAllPsBearIsrFlg
 功能描述  : 更新所有ps 承载的ISR状态，即是在ISR激活前激活的或是在ISR激活后激活的
 输入参数  : enPsBearerIsrFlg - ps承载的ISR状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月7日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_UpdateAllPsBearIsrFlg(
    NAS_MML_PS_BEARER_ISR_ENUM_UINT8    enPsBearerIsrFlg
)
{
    NAS_MML_PS_BEARER_CONTEXT_STRU     *pstPsBearerCtx;
    VOS_UINT8                           i;

    pstPsBearerCtx = NAS_MML_GetPsBearerCtx();

    for (i = 0; i < NAS_MML_MAX_PS_BEARER_NUM; i++)
    {
        pstPsBearerCtx[i].enPsBearerIsrFlg = enPsBearerIsrFlg;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_IsPsBearerExistBeforeIsrAct
 功能描述  : 判断某个PS承载是否为ISR激活前激活的承载
 输入参数  : ucNsapi - 承载id
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 是ISR激活前激活的PS承载
             VOS_FALSE - 不是ISR激活前前激活的PS承载
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月7日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_IsPsBearerExistBeforeIsrAct(VOS_UINT8 ucNsapi)
{
    NAS_MML_PS_BEARER_CONTEXT_STRU     *pstPsBearerCtx;

    pstPsBearerCtx = NAS_MML_GetPsBearerCtx();

    /* 合法性检查，如果ucRabId取值不在协议定义[5,15]范围，则不处理直接返回 */
    if ((ucNsapi < NAS_MML_MIN_NSAPI)
     || (ucNsapi > NAS_MML_MAX_NSAPI))
    {
        return VOS_FALSE;
    }

    if ((NAS_MML_PS_BEARER_STATE_ACTIVE == pstPsBearerCtx[ucNsapi - 5].enPsBearerState)
     && (NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT == pstPsBearerCtx[ucNsapi - 5].enPsBearerIsrFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}

/*****************************************************************************
 函 数 名  : NAS_MML_IsPsBearerAfterIsrActExist
 功能描述  : 是否存在ISR激活后激活的PS承载
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 存在PS承载
             VOS_FALSE - 不存在PS承载
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月7日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_IsPsBearerAfterIsrActExist(VOS_VOID)
{
    NAS_MML_PS_BEARER_CONTEXT_STRU     *pstPsBearerCtx;
    VOS_UINT8                           i;

    pstPsBearerCtx = NAS_MML_GetPsBearerCtx();

    for (i = 0; i < NAS_MML_MAX_PS_BEARER_NUM; i++)
    {
        if ((NAS_MML_PS_BEARER_STATE_ACTIVE == pstPsBearerCtx[i].enPsBearerState)
         && (NAS_MML_PS_BEARER_EXIST_AFTER_ISR_ACT == pstPsBearerCtx[i].enPsBearerIsrFlg))
        {
            return VOS_TRUE;
        }
    }
    return VOS_FALSE;

}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MML_ConvertMmlCsfbStatusToLmmCsfbStatus
 功能描述  : 将MML维护的CSFB状态标志类型转换为LMM格式的CSFB状态标志
 输入参数  : enMmlCsfbStatus:  MML维护的CSFB状态标志类型
 输出参数  : penLmmCsfbStatus: LMM格式的CSFB状态标志
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月16日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_ConvertMmlCsfbStatusToLmmCsfbStatus(
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enMmlCsfbStatus,
    MM_LMM_CSFB_SERVICE_TYPE_ENUM_UINT32                   *penLmmCsfbStatus
)
{
    switch ( enMmlCsfbStatus )
    {
        case NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_CC_EXIST :
        case NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST :
            *penLmmCsfbStatus = MM_LMM_CSFB_SERVICE_MO_NORMAL;
            break;

        case NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST :
            *penLmmCsfbStatus = MM_LMM_CSFB_SERVICE_MO_EMERGENCY;
            break;

        case NAS_MML_CSFB_SERVICE_STATUS_MT_EXIST :
            *penLmmCsfbStatus = MM_LMM_CSFB_SERVICE_MT_NORMAL;
            break;

        default:
            *penLmmCsfbStatus = MM_LMM_CSFB_SERVICE_BUTT;
            break;
    }

    return;
}
/*****************************************************************************
 函 数 名  : NAS_MML_GetCsPsMode1EnableLteTimerLen
 功能描述  : 获取cs ps mode1 disable lte场景enable lte 定时器时长
 输入参数  : 无
 输出参数  : 无
 返 回 值  : enable lte定时器时长
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月5日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改

*****************************************************************************/
VOS_UINT32 NAS_MML_GetCsPsMode1EnableLteTimerLen(VOS_VOID)
{
    /* 如果当前驻留plmn在支持DAM特性网络列表中，则返回T3402定时器时长，
       否则返回9220 en_NV_Item_Enable_Lte_Timer_Len NV项中配置的时长 */
    if (VOS_TRUE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
    {
        return NAS_MML_GetT3402Len();
    }

    /* Modified by c00318887 for 移植T3402 , 2015-6-17, begin */
    /* 如果 en_NV_Item_DISABLE_LTE_START_T3402_ENABLE_LTE_CFG 开，则从ID_LMM_MMC_T3402_LEN_NOTIFY消息中的 T3402定时器时长，
       否则返回9220 en_NV_Item_Enable_Lte_Timer_Len NV项中配置的时长 */
    if (VOS_TRUE == NAS_MML_GetDisableLteStartT3402EnableLteFlag())
    {
        return NAS_MML_GetT3402Len();
    }
    /* Modified by c00318887 for 移植T3402 , 2015-6-17, end */


    return NAS_MML_GetCsPsMode13GPPEnableLteTimerLen();
}

#endif
/*****************************************************************************
 函 数 名  : NAS_MML_IsLteCapabilityDisabled
 功能描述  : 判断Lte的能力是否已经disable了
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - LTE已经disable
             VOS_FALSE - LTE未disable
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年06月07日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsLteCapabilityDisabled(
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapStatus,
    VOS_UINT32                                              ulDisableLteRoamFlg
)
{
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapStatus)
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapStatus)
     || (VOS_TRUE == ulDisableLteRoamFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}

/*****************************************************************************
 函 数 名  : NAS_MML_IsNeedAddDamPlmnInDisabledPlmnWithForbiddenPeriodList
 功能描述  : 是否需要将指定禁止接入技术DAM网络加入禁止接入技术网络网络列表
 输入参数  : pstPlmnWithRat - 禁止接入技术网络信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年1月14日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改
 2.日    期   : 2015年4月22日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改

*****************************************************************************/
VOS_UINT32 NAS_MML_IsNeedAddDamPlmnInDisabledPlmnWithForbiddenPeriodList(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstPlmnWithRat
)
{
    NAS_MML_DISABLED_RAT_PLMN_CFG_INFO_STRU                *pstDisabledPlmnIdWithRatList = VOS_NULL_PTR;
    VOS_UINT32                                              ulIndex;
    VOS_UINT32                                              ulIsPlmnSupportDam;

    pstDisabledPlmnIdWithRatList = NAS_MML_GetDisabledRatPlmnInfo();

    /* 如果pstPlmnWithRat已经在禁止接入技术网络列表中则无需处理 */
    if (VOS_TRUE == NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList(pstPlmnWithRat))
    {
        return VOS_FALSE;
    }

    ulIndex = pstDisabledPlmnIdWithRatList->ulDisabledRatPlmnNum;

    /* 列表已满返回VOS_FALSE */
    if (NAS_MML_MAX_DISABLED_RAT_PLMN_NUM == ulIndex)
    {
        return VOS_FALSE;
    }

    ulIsPlmnSupportDam = NAS_MML_IsPlmnSupportDam(&pstPlmnWithRat->stPlmnId);

    /* DAM特性生效且在DAM网络disable lte后需要将DAM网络加入禁止接入
       技术网络列表中，则动态加入禁止接入技术网络列表 */
    if ((VOS_TRUE == NAS_MML_GetAddDamPlmnInDisablePlmnWithRatListFlag())
     && (VOS_TRUE == ulIsPlmnSupportDam))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetDamDisabledPlmnWithForbiddenPeriodTimeSlice
 功能描述  : 获取禁止接入技术网络解除禁止的time slice
 输入参数  : pstPlmnWithRat - 禁止接入技术网络信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年1月14日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改
 2.日    期   : 2015年4月22日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT32 NAS_MML_GetDamDisabledPlmnWithForbiddenPeriodTimeSlice(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnWithRat
)
{
    VOS_UINT32                          ulExpiredTimeSlice;
    VOS_UINT32                          ulIsPlmnSupportDam;

    ulExpiredTimeSlice = 0;

    ulIsPlmnSupportDam = NAS_MML_IsPlmnSupportDam(&pstPlmnWithRat->stPlmnId);

    /* DAM特性生效且在DAM网络disable lte后需要将DAM网络加入禁止接入
       技术网络列表中，根据T3402定时器时长返回对应的timeslice */
    if ((VOS_TRUE == NAS_MML_GetAddDamPlmnInDisablePlmnWithRatListFlag())
     && (VOS_TRUE == ulIsPlmnSupportDam))
    {
        ulExpiredTimeSlice = VOS_GetSliceUnit() * (NAS_MML_GetT3402Len()/1000);
    }

    return ulExpiredTimeSlice;
}

/*****************************************************************************
 函 数 名  : NAS_MML_IsNeedDeleteDisabledPlmnWithValidPeriodInPlmnList
 功能描述  : 判断是否需要从禁止接入技术网络列表中删除指定网络
 输入参数  : pstDisabledPlmnIdWithRat - 禁止接入技术网络
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 需要删除
             VOS_FALSE - 无需删除
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年1月14日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改
 2.日    期   : 2015年4月29日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT32 NAS_MML_IsNeedDeleteDisabledPlmnWithValidPeriodInPlmnList (
    NAS_MML_DISABLED_PLMN_WITH_FORBIDDEN_PERIOD_STRU       *pstDisabledPlmnIdWithRat
)
{
    VOS_UINT32                          ulCurrTimeSlice;
    VOS_UINT32                          ulDuration;

    ulCurrTimeSlice = VOS_GetSlice();

    /* 如果禁止接入技术网络是nv配置的禁止期限为全F，则返回VOS_FALSE无需动态删除 */
    if (NAS_MML_MAX_TIME_SLICE == pstDisabledPlmnIdWithRat->ulPlmnDisabledForbiddenSlice)
    {
        return VOS_FALSE;
    }

    /* 达到禁止时间，则从禁止接入技术网络列表中删除该网络,因为存在翻转所以如果
       ulCurrTimeSlice小于ulPlmnDisabledBeginSlice也认为达到禁止时间，从禁止接入技术网络列表中删除该网络*/
    if (ulCurrTimeSlice < pstDisabledPlmnIdWithRat->ulPlmnDisabledBeginSlice)
    {
        ulDuration = NAS_MML_MAX_TIME_SLICE - pstDisabledPlmnIdWithRat->ulPlmnDisabledBeginSlice + ulCurrTimeSlice + 1;
    }
    else
    {
        ulDuration = ulCurrTimeSlice - pstDisabledPlmnIdWithRat->ulPlmnDisabledBeginSlice;
    }

    if (ulDuration >= pstDisabledPlmnIdWithRat->ulPlmnDisabledForbiddenSlice)
    {
        return VOS_TRUE;
    }


    return VOS_FALSE;
}




/*****************************************************************************
 函 数 名  : NAS_MML_GetFirstAddPlmnIndexInDestDisabledPlmnWithForbiddenPeriodList
 功能描述  : 获取最早加入禁止接入技术网络列表中其惩罚时间不是永久的网络的索引
 输入参数  : ulDestPlmnNum:禁止plmn id的个数
             pstDestPlmnIdList:禁止plmn列表
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年4月23日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT32 NAS_MML_GetFirstAddPlmnIndexInDestDisabledPlmnWithForbiddenPeriodList (
    VOS_UINT32                                              ulDestPlmnNum,
    NAS_MML_DISABLED_PLMN_WITH_FORBIDDEN_PERIOD_STRU       *pstDestPlmnIdList
)
{
    VOS_UINT32                          ulFirstAddPlmnIdIndex;
    VOS_UINT32                          j;
    VOS_UINT32                          ulIndex;

    ulIndex               = ulDestPlmnNum;
    ulFirstAddPlmnIdIndex = NAS_MML_MAX_DISABLED_RAT_PLMN_NUM;

    if (ulIndex > NAS_MML_MAX_DISABLED_RAT_PLMN_NUM)
    {
        ulIndex = NAS_MML_MAX_DISABLED_RAT_PLMN_NUM;
    }

    /* 找第一个惩罚时间不为NAS_MML_MAX_TIME_SLICE的网络 */
    for (j = 0; j < ulIndex; j++)
    {
        if (pstDestPlmnIdList[j].ulPlmnDisabledForbiddenSlice != NAS_MML_MAX_TIME_SLICE)
        {
            ulFirstAddPlmnIdIndex = j;
            break;
        }
    }

    /* 如果都是惩罚时间为NAS_MML_MAX_TIME_SLICE的网络，则返回无效值 */
    if (NAS_MML_MAX_DISABLED_RAT_PLMN_NUM == ulFirstAddPlmnIdIndex)
    {
        return ulFirstAddPlmnIdIndex;
    }

    /* 找最早加入且惩罚时间不是ulFirstAddPlmnIdIndex的网络index */
    for (j = ulFirstAddPlmnIdIndex + 1; j < ulIndex; ++j)
    {
        if ((pstDestPlmnIdList[j].ulPlmnDisabledBeginSlice < pstDestPlmnIdList[ulFirstAddPlmnIdIndex].ulPlmnDisabledBeginSlice)
         && (pstDestPlmnIdList[j].ulPlmnDisabledForbiddenSlice != NAS_MML_MAX_TIME_SLICE))
        {
            ulFirstAddPlmnIdIndex = j;
        }
    }

    return ulFirstAddPlmnIdIndex;
}


/*****************************************************************************
 函 数 名  : NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList
 功能描述  : 向禁止接入技术列表中增加网络
 输入参数  : pstPlmnWithRat                 - 禁止接入技术网络信息
             ulPlmnDisabledInvalidSlice     - 禁止SLICE时长
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年4月17日
   作    者   : w00167002
   修改内容   : DTS2015032709270

 2.日    期   : 2015年7月18日
   作    者   : w00167002
   修改内容   : DTS2015071604422:同步3g卡4g未开户特性到AUSTIN.
                联通3g卡未开通4g，在46001上LTE注册拒绝#15,LNAS通知MMC需要进行DISABLE
                LTE，后续在WCDMA网络上注册成功。
                接着在W下丢网，触发了搜网LTE失败，后续重新回到WCDMA网络上。接着发起了
                W->LTE的盲重定向，mmc通知LMM等效PLMN时候，删除了禁止网络，即EPLMN个数为0.
                由于LRRC只判断驻留在EPLMN上得TAI信息，导致没有给LNAS上报当前的禁止TAI
                信息，导致LNAS没有给MMC上报禁止LTE的指示，没有禁止LTE网络。
                修改为；MMC在通知LNAS当前EPLMN时候，不删除拒绝#15惩罚的网络，这样
                后续ENABLE LTE后，发生了gu->lte的重定向，LNAS会给MMC上报触发需要DISABLE
                LTE的消息，从而解决了GU->LTE盲重定向的问题。
*****************************************************************************/
VOS_VOID NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstPlmnWithRat,
    VOS_UINT32                                              ulPlmnDisabledInvalidSlice,
    MMC_LMM_DISABLE_LTE_REASON_ENUM_UINT32                  enDisableLteReason
)
{
    NAS_MML_DISABLED_RAT_PLMN_CFG_INFO_STRU                *pstDisabledPlmnIdWithRatList = VOS_NULL_PTR;
    VOS_UINT32                                              ulIndex;

    pstDisabledPlmnIdWithRatList = NAS_MML_GetDisabledRatPlmnInfo();

    /* 如果pstPlmnWithRat已经在禁止接入技术网络列表中则无需添加，更新下begin slice、惩罚时长和禁止原因 */
    if (VOS_TRUE == NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList(pstPlmnWithRat))
    {
        ulIndex = NAS_MML_GetPlmnWithRatIndexInDestDisabledPlmnWithForbiddenPeriodList(pstPlmnWithRat,
                                                   pstDisabledPlmnIdWithRatList->ulDisabledRatPlmnNum,
                                                   pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId);

        if (ulIndex < NAS_MML_MAX_DISABLED_RAT_PLMN_NUM)
        {
            pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIndex].ulPlmnDisabledForbiddenSlice = ulPlmnDisabledInvalidSlice;
            pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIndex].ulPlmnDisabledBeginSlice     = VOS_GetSlice();
            pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIndex].enDisableLteReason           = enDisableLteReason;
        }
        return;
    }

    /* 列表已满,删除最早加入禁止接入技术网络列表中的网络 */
    if (NAS_MML_MAX_DISABLED_RAT_PLMN_NUM == pstDisabledPlmnIdWithRatList->ulDisabledRatPlmnNum)
    {
        ulIndex = NAS_MML_GetFirstAddPlmnIndexInDestDisabledPlmnWithForbiddenPeriodList(pstDisabledPlmnIdWithRatList->ulDisabledRatPlmnNum,
                                pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId);

        if (ulIndex < NAS_MML_MAX_DISABLED_RAT_PLMN_NUM)
        {
            pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIndex].stPlmnWithRat.stPlmnId.ulMcc = pstPlmnWithRat->stPlmnId.ulMcc;
            pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIndex].stPlmnWithRat.stPlmnId.ulMnc = pstPlmnWithRat->stPlmnId.ulMnc;
            pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIndex].stPlmnWithRat.enRat          = pstPlmnWithRat->enRat;
            pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIndex].ulPlmnDisabledForbiddenSlice = ulPlmnDisabledInvalidSlice;
            pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIndex].ulPlmnDisabledBeginSlice     = VOS_GetSlice();
            pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIndex].enDisableLteReason           = enDisableLteReason;

            NAS_MMC_LogForbiddenPlmnRelatedInfo();
        }
        return;
    }

    /* 当前PLMN不在惩罚列表里面，且当前列表未满，则需要将PLMN加入到禁止接入技术列表里面 */
    ulIndex                      = pstDisabledPlmnIdWithRatList->ulDisabledRatPlmnNum;

    pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIndex].stPlmnWithRat.stPlmnId.ulMcc = pstPlmnWithRat->stPlmnId.ulMcc;
    pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIndex].stPlmnWithRat.stPlmnId.ulMnc = pstPlmnWithRat->stPlmnId.ulMnc;
    pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIndex].stPlmnWithRat.enRat          = pstPlmnWithRat->enRat;
    pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIndex].ulPlmnDisabledForbiddenSlice = ulPlmnDisabledInvalidSlice;
    pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIndex].ulPlmnDisabledBeginSlice     = VOS_GetSlice();
    pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIndex].enDisableLteReason           = enDisableLteReason;
    pstDisabledPlmnIdWithRatList->ulDisabledRatPlmnNum++;

    /* 启动周期定时器判断加入禁止接入技术网络禁止时间是否到达，
        到达后需要删除认为该网络不再禁止且重新通知接入层等效plmn信息 */
    if (NAS_MMC_TIMER_STATUS_RUNING != NAS_MMC_GetTimerStatus(TI_NAS_MMC_PERIOD_DELETE_DISABLED_PLMN_WITH_RAT_TIMER))
    {
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_DELETE_DISABLED_PLMN_WITH_RAT_TIMER,
                            TI_NAS_MMC_PERIOD_DELETE_DISABLED_PLMN_WITH_RAT_TIMER_LEN);
    }


    NAS_MMC_LogForbiddenPlmnRelatedInfo();

    return;
}



/*****************************************************************************
 函 数 名  : NAS_MML_IsImsiHplmnInDamImsiPlmnList
 功能描述  : 判断IMSI hplmn是否在DAM imsi网络列表中
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - IMSI hplmn在DAM imsi网络列表中
             VOS_FALSE - IMSI hplmn不在DAM imsi网络列表中
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月14日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsImsiHplmnInDamImsiPlmnList(VOS_VOID)
{
    NAS_MML_DAM_IMSI_PLMN_LIST_STRU    *pstDamImsiPlmnList    = VOS_NULL_PTR;
    VOS_UINT8                          *pucImsi               = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stHplmnId;
    VOS_UINT32                          ulIsHplmnInDamImsiPlmnList;

    pstDamImsiPlmnList         = NAS_MML_GetDamImsiPlmnList();
    stHplmnId.ulMcc            = NAS_MML_INVALID_MCC;
    stHplmnId.ulMnc            = NAS_MML_INVALID_MNC;
    ulIsHplmnInDamImsiPlmnList = VOS_FALSE;

    /* 取得手机卡中IMSI的信息 */
    pucImsi     = NAS_MML_GetSimImsi();

    /* 从当前的IMSI中取出home plmn */
    stHplmnId                  = NAS_MML_GetImsiHomePlmn(pucImsi);

    /* 如果DAM imsi plmn个数为1，且mcc和mnc为0xFF,则无需判卡,返回TRUE */
    if ((1 == pstDamImsiPlmnList->ucPlmnNum)
     && (NAS_MML_INVALID_MCC == pstDamImsiPlmnList->astPlmnId[0].ulMcc)
     && (NAS_MML_INVALID_MNC == pstDamImsiPlmnList->astPlmnId[0].ulMnc))
    {
        ulIsHplmnInDamImsiPlmnList = VOS_TRUE;
    }
    else
    {
        ulIsHplmnInDamImsiPlmnList = NAS_MML_IsSimPlmnIdInDestBcchPlmnList(&stHplmnId,
                                              pstDamImsiPlmnList->ucPlmnNum,
                                              pstDamImsiPlmnList->astPlmnId);
    }

    return ulIsHplmnInDamImsiPlmnList;
}

/*****************************************************************************
 函 数 名  : NAS_MML_IsPlmnSupportDam
 功能描述  : 判断网络是否支持DAM特性
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 网络支持DAM特性
             VOS_FALSE - 网络不支持DAM特性
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月14日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsPlmnSupportDam(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MML_SUPPORT_DAM_PLMN_INFO_STRU *pstSupportDamPlmnList = VOS_NULL_PTR;
    VOS_UINT32                          ulIsPlmnInDamPlmnList;
    VOS_UINT32                          ulIsHplmnInDamImsiPlmnList;

    pstSupportDamPlmnList      = NAS_MML_GetSupportDamPlmnList();
    ulIsPlmnInDamPlmnList      = VOS_FALSE;
    ulIsHplmnInDamImsiPlmnList = VOS_FALSE;

    ulIsPlmnInDamPlmnList      = NAS_MML_IsSimPlmnIdInDestBcchPlmnList(pstPlmnId,
                                              pstSupportDamPlmnList->ucPlmnNum,
                                              pstSupportDamPlmnList->astPlmnId);

    ulIsHplmnInDamImsiPlmnList = NAS_MML_IsImsiHplmnInDamImsiPlmnList();

    /* IMSI HPLMN在DAM imsi plmn列表中并且驻留网络在支持DAM特性的网络列表中返回TRUE */
    if ((VOS_TRUE == ulIsPlmnInDamPlmnList)
     && (VOS_TRUE == ulIsHplmnInDamImsiPlmnList))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



/*****************************************************************************
 函 数 名  : NAS_MML_IsCsLaiChanged
 功能描述  : 判断CS LAI是否改变
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:LAI改变
             VOS_FALSE:LAI未改变
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月17日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MML_IsCsLaiChanged(VOS_VOID)
{
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-19, begin */
    NAS_MML_LAI_STRU                   *pstCampLai;
    NAS_MML_LAI_STRU                   *pstLastSuccLai;
    VOS_UINT32                          i;

    pstCampLai     = NAS_MML_GetCurrCampLai();
    pstLastSuccLai = NAS_MML_GetCsLastSuccLai();

    if ((pstCampLai->stPlmnId.ulMcc != pstLastSuccLai->stPlmnId.ulMcc)
     || (pstCampLai->stPlmnId.ulMnc != pstLastSuccLai->stPlmnId.ulMnc))
    {
        return VOS_TRUE;
    }

    for ( i = 0 ; i < NAS_MML_MAX_LAC_LEN ; i++ )
    {
        if (pstCampLai->aucLac[i] != pstLastSuccLai->aucLac[i])
        {
            return VOS_TRUE;
        }
    }
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-19, end */

    return VOS_FALSE;

}


/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-22, begin */
/*****************************************************************************
 函 数 名  : NAS_MML_IsExistBufferedEmgCall
 功能描述  : 判断是否存在缓存的紧急呼叫
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 存在缓存的紧急呼叫
             VOS_FALSE - 不存在缓存的紧急呼叫
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012年8月22日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsExistBufferedEmgCall(VOS_VOID)
{
    VOS_UINT8                           ucIsExistEmgCall;

    ucIsExistEmgCall = NAS_MML_GetCsEmergencyServiceFlg();

    if ((VOS_TRUE == NAS_MML_GetCsServiceBufferStatusFlg())
     && (VOS_TRUE == ucIsExistEmgCall))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-22, end */


/*****************************************************************************
 函 数 名  :NAS_MML_GetValidUserCfgEhplmnInfo
 功能描述  :根据IMSI信息，解析en_NV_Item_User_Cfg_Ehplmn中的Ehplmn
 输入参数  :pucImsi - imsi信息
 输出参数  :pstEHPlmnInfo:取出的ehplmn
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月03日
   作    者   : W00167002
   修改内容   : 新生成函数
 2.日    期   : 2014年12月22日
   作    者   : wx270776
   修改内容   : 扩充结构体，增加循环

*****************************************************************************/
VOS_VOID NAS_MML_GetValidUserCfgEhplmnInfo(
    VOS_UINT8                          *pucImsi,
    VOS_UINT8                          *pucEhplmnListNum,
    NAS_MML_PLMN_ID_STRU               *pstEhPlmnList
)
{
    VOS_UINT32                                  i;
    VOS_UINT32                                  j;
    VOS_UINT32                                  ulUserCfgEhplmnNum;
    NAS_MML_PLMN_ID_STRU                        stHPlmn;
    NAS_MML_USER_CFG_EXT_EHPLMN_INFO_STRU      *pstUserCfgExtEHplmnInfo;

    pstUserCfgExtEHplmnInfo = NAS_MML_GetUserCfgExtEhplmnInfo();
    ulUserCfgEhplmnNum = pstUserCfgExtEHplmnInfo->ulUserCfgEhplmnNum;
    /* 防止结构体数组越界 */
    if ( ulUserCfgEhplmnNum > NAS_MML_MAX_USER_CFG_EXT_EHPLMN_NUM )
    {
        ulUserCfgEhplmnNum = NAS_MML_MAX_USER_CFG_EXT_EHPLMN_NUM;
    }

    /* 默认用户设置的EHplmn的个数为0个 */
    *pucEhplmnListNum = 0;

    /* 从当前的IMSI中取出home plmn */
    stHPlmn = NAS_MML_GetImsiHomePlmn(pucImsi);


    /* 如果当前的IMSI中的Home Plmn在astImsiPlmnList中，则取当前的EHplmn */
    for (j = 0 ; j < ulUserCfgEhplmnNum; j++)
    {
        for ( i = 0 ; i < pstUserCfgExtEHplmnInfo->astUserCfgEhplmnInfo[j].ucImsiPlmnListNum; i++ )
        {
            /* 用户配置的IMSI plmn网络是BCCH格式的 */
            if ( VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&pstUserCfgExtEHplmnInfo->astUserCfgEhplmnInfo[j].astImsiPlmnList[i],
                                                            &stHPlmn) )
            {
                *pucEhplmnListNum = pstUserCfgExtEHplmnInfo->astUserCfgEhplmnInfo[j].ucEhplmnListNum;

                /* 取出用户配置的EHplmn内容 */
                PS_MEM_CPY(pstEhPlmnList, pstUserCfgExtEHplmnInfo->astUserCfgEhplmnInfo[j].astEhPlmnList,
                                            sizeof(pstUserCfgExtEHplmnInfo->astUserCfgEhplmnInfo[j].astEhPlmnList) );
                return;
            }
        }
    }


    return ;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetRrcSimStatus
 功能描述  : 获取发给 GU的当前的Sim卡的类型和存在状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : rrc格式的SIM卡状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月2日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2012年8月9日
    作    者   : w00176964
    修改内容   : GUTL PhaseII 调整调整:修改函数位置和名称
*****************************************************************************/
VOS_UINT32  NAS_MML_GetRrcSimStatus(VOS_VOID)
{
    RRC_NAS_SIM_STATUS_ENUM_UINT32      ulCardStatus;

    /* 卡存在 */
    if ( VOS_TRUE == NAS_MML_GetSimPresentStatus() )
    {
        /* SIM卡存在 */
        if ( NAS_MML_SIM_TYPE_SIM  == NAS_MML_GetSimType())
        {
            ulCardStatus = RRC_NAS_SIM_PRESENT;
        }
        /* USIM卡存在 */
        else
        {
            ulCardStatus = RRC_NAS_USIM_PRESENT;
        }
    }
    /* 卡不存在 */
    else
    {
        ulCardStatus = RRC_NAS_UICC_ABSENT;
    }

    return ulCardStatus;
}


/*****************************************************************************
 函 数 名  : NAS_MML_IsPlmnIdWithRatInDestPlmnWithRatList
 功能描述  : 判断带接入技术的PLMN ID是否在带接入技术的PLMN ID列表中
 输入参数  : pstSrcPlmnId:需要判断的PLMN ID
             ulDestPlmnNum:列表中plmn id的个数
             pstDestPlmnIdList:plmn列表
 输出参数  : 无
 返 回 值  : VOS_TRUE  : PLMN ID在列表中
             VOS_FALSE : PLMN ID不在列表中
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2012年08月20日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsBcchPlmnIdWithRatInDestPlmnWithRatList (
    NAS_MML_PLMN_WITH_RAT_STRU         *pstSrcPlmnId,
    VOS_UINT32                          ulDestPlmnNum,
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmnIdList
)
{
    VOS_UINT32                          i;

    for ( i = 0; i < ulDestPlmnNum; i++ )
    {
        if ((VOS_TRUE               == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstSrcPlmnId->stPlmnId), &(pstDestPlmnIdList[i].stPlmnId)))
         && (pstSrcPlmnId->enRat    == pstDestPlmnIdList[i].enRat))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MML_IsImsiInForbiddenList
 功能描述  : 判断当前的SIM卡是否在禁止列表中
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_TRUE  : IMSI在黑名单中
             VOS_FALSE : IMSI不在黑名单中
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsImsiInForbiddenList (VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_MML_PLMN_ID_STRU                stHplmnId;
    NAS_MML_PLMN_ID_STRU                stBlackPlmnId;
    NAS_MML_RAT_FORBIDDEN_LIST_STRU    *pstRatBlackList = VOS_NULL_PTR;
    VOS_UINT8                          *pucImsi         = VOS_NULL_PTR;

    i               = 0;
    pstRatBlackList = NAS_MML_GetRatForbiddenListCfg();

    PS_MEM_SET(&stHplmnId,     0x00, sizeof(stHplmnId));
    PS_MEM_SET(&stBlackPlmnId, 0x00, sizeof(stBlackPlmnId));

    if ( VOS_FALSE == NAS_MML_GetSimPresentStatus() )
    {
        return VOS_FALSE;
    }

    /* 增加测试卡保护，测试卡时不修改，直接返回 */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return VOS_FALSE;
    }


    if ( NAS_MML_RAT_FORBIDDEN_LIST_SWITCH_INACTIVE == pstRatBlackList->enSwitchFlag )
    {
        return VOS_FALSE;
    }

    /* 取得本地维护的IMSI的地址 */
    pucImsi    = NAS_MML_GetSimImsi();

    /* 从当前的IMSI中取出home plmn */
    stHplmnId  = NAS_MML_GetImsiHomePlmn(pucImsi);

    /* 判断IMSI是否在禁止的IMSI列表中 */
    if (NAS_MML_RAT_FORBIDDEN_LIST_SWITCH_BLACK == pstRatBlackList->enSwitchFlag)
    {
        for (i = 0; i < pstRatBlackList->ucImsiListNum; i++)
        {
            /* 如果在黑名单中，将ucIsPlmnIdInPlmnBlackList置为TRUE，需要禁止对应的RAT */
            stBlackPlmnId.ulMcc = pstRatBlackList->astImsiList[i].ulMcc;
            stBlackPlmnId.ulMnc = pstRatBlackList->astImsiList[i].ulMnc;

            if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&stBlackPlmnId, &stHplmnId))
            {
                return VOS_TRUE;
            }
        }

        return VOS_FALSE;
    }
    else if (NAS_MML_RAT_FORBIDDEN_LIST_SWITCH_WHITE == pstRatBlackList->enSwitchFlag)
    {
        for (i = 0; i < pstRatBlackList->ucImsiListNum; i++)
        {
            /* 如果在白名单中，直接返回VOS_FALSE(不在黑名单) */
            stBlackPlmnId.ulMcc = pstRatBlackList->astImsiList[i].ulMcc;
            stBlackPlmnId.ulMnc = pstRatBlackList->astImsiList[i].ulMnc;

            if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&stBlackPlmnId, &stHplmnId))
            {
                return VOS_FALSE;
            }
        }

        return VOS_TRUE;
    }
    else
    {
    }

    return VOS_FALSE;

}




/*****************************************************************************
 函 数 名  : NAS_MML_IsPlmnIdWithRatInRatBlackListAccordSimType
 功能描述  : 判断当前的SIM卡是否在禁止列表中，是否需要禁止对应的RAT
 输入参数  : enRatType:需要判断的RAT
 输出参数  : 无
 返 回 值  : VOS_TRUE  : 需要禁止该RAT
             VOS_FALSE : 需要禁止该RAT
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsRatInForbiddenList (
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType
)
{
    VOS_UINT32                          i;
    NAS_MML_RAT_FORBIDDEN_LIST_STRU    *pstRatBlackList = VOS_NULL_PTR;

    i                   = 0;
    pstRatBlackList     = NAS_MML_GetRatForbiddenListCfg();

    /* 如果不在IMSI黑名单中，返回VOS_FALSE */
    if (VOS_FALSE == NAS_MML_GetImsiInForbiddenListFlg())
    {
        return VOS_FALSE;
    }

    /* 如果在禁止IMSI列表中，判断RAT是否在禁止的网络制式列表中 */
    for (i = 0; i < pstRatBlackList->ucForbidRatNum; i++)
    {
        /* 如果传入的RAT在禁止网络制式列表中则返回VOS_TRUE */
        if (enRatType == pstRatBlackList->aenForbidRatList[i])
        {
            NAS_NORMAL_LOG1(WUEPS_PID_MMC, "NAS_MML_IsRatInForbiddenList enRatType == ",enRatType);        
            
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;

}


/*****************************************************************************
 函 数 名  : NAS_MML_IsAllMsRatInRatBlackList
 功能描述  : 判断UE配置的网络制式是否都被禁止
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsAllMsRatInForbiddenList (VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList       = VOS_NULL_PTR;
    VOS_UINT32                          i;

    i = 0;

     /* 获取当前接入技术优先级信息 */
    pstPrioRatList  = NAS_MML_GetMsPrioRatList();

    for (i = 0; i < pstPrioRatList->ucRatNum; i++)
    {
        if (VOS_FALSE == NAS_MML_IsRatInForbiddenList(pstPrioRatList->aucRatPrio[i]))
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}



#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MML_IsPlatformSupportLte
 功能描述  : 判断平台是否支持LTE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  : 平台支持LTE
             VOS_FALSE : 平台不支持LTE
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2012年12月26日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsPlatformSupportLte (VOS_VOID)
{
    NAS_MML_PLATFORM_RAT_CAP_STRU              *pstPlatformRatCap;
    VOS_UINT32                                  i;

    /* 获取平台接入技术能力 */
    pstPlatformRatCap = NAS_MML_GetPlatformRatCap();

    for ( i = 0; i < pstPlatformRatCap->ucRatNum; i++ )
    {
        if (NAS_MML_PLATFORM_RAT_TYPE_LTE == pstPlatformRatCap->aenRatPrio[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_MML_IsPlatformSupportUtranFdd
 功能描述  : 判断平台是否支持FDD
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  : 平台支持FDD
             VOS_FALSE : 平台不支持FDD
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2012年12月26日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsPlatformSupportUtranFdd (VOS_VOID)
{
    NAS_MML_PLATFORM_RAT_CAP_STRU              *pstPlatformRatCap;
    VOS_UINT32                                  i;

    /* 获取平台接入技术能力 */
    pstPlatformRatCap = NAS_MML_GetPlatformRatCap();

    for ( i = 0; i < pstPlatformRatCap->ucRatNum; i++ )
    {
        if (NAS_MML_PLATFORM_RAT_TYPE_WCDMA == pstPlatformRatCap->aenRatPrio[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
/*****************************************************************************
 函 数 名  : NAS_MML_IsPlatformSupportUtranTdd
 功能描述  : 判断平台是否支持TDD
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  : 平台支持TDD
             VOS_FALSE : 平台不支持TDD
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2012年12月26日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsPlatformSupportUtranTdd (VOS_VOID)
{
    NAS_MML_PLATFORM_RAT_CAP_STRU              *pstPlatformRatCap;
    VOS_UINT32                                  i;

    /* 获取平台接入技术能力 */
    pstPlatformRatCap = NAS_MML_GetPlatformRatCap();

    for ( i = 0; i < pstPlatformRatCap->ucRatNum; i++ )
    {
        if (NAS_MML_PLATFORM_RAT_TYPE_TD_SCDMA == pstPlatformRatCap->aenRatPrio[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_MML_IsDsdsMultiModemMode
 功能描述  : 判断平台是否是DSDS双卡模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE: 当前是DSDS多Modem
             VOS_FALSE:当前不是DSDS多Modem
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2014年02月11日
   作    者   : w00167002
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsDsdsMultiModemMode(VOS_VOID)
{
    /* 如果DSDS 功能未开启，则返回FALSE */
    if (VOS_FALSE == NAS_MML_GetDsdsRfShareFlg() )
    {
        return VOS_FALSE;
    }

    /* 如果当前不是多卡模式，则返回FALSE */
    if (VOS_FALSE == NAS_MML_GetDsdsMultiModemModeFlg())
    {
        return VOS_FALSE;
    }

    /* DSDS功能开启，并且当前是多卡模式，则返回TRUE */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MML_IsPlatformSupportGsm
 功能描述  : 判断平台是否支持GSM
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  : 平台支持GSM
             VOS_FALSE : 平台不支持GSM
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2012年12月26日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsPlatformSupportGsm (VOS_VOID)
{
    NAS_MML_PLATFORM_RAT_CAP_STRU              *pstPlatformRatCap;
    VOS_UINT32                                  i;

    /* 获取平台接入技术能力 */
    pstPlatformRatCap = NAS_MML_GetPlatformRatCap();

    for ( i = 0; i < pstPlatformRatCap->ucRatNum; i++ )
    {
        if (NAS_MML_PLATFORM_RAT_TYPE_GSM == pstPlatformRatCap->aenRatPrio[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MML_IsPlatformSupportUtran
 功能描述  : 判断平台是否支持Utran(包括UMTS FDD和UMTS TDD)
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  : 平台支持W/TD中的一个或两个都要支持
             VOS_FALSE : 平台既不支持W也不支持TD
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2012年12月26日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsPlatformSupportUtran (VOS_VOID)
{
    if (VOS_TRUE == NAS_MML_IsPlatformSupportUtranFdd())
    {
        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
    if (VOS_TRUE == NAS_MML_IsPlatformSupportUtranTdd())
    {
        return VOS_TRUE;
    }
#endif

    return VOS_FALSE;
}
/* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
/*****************************************************************************
 函 数 名  : NAS_MML_IsAcInfoChanged
 功能描述  : 收到系统信息后，判断当前驻留小区的接入受限信息是否发生改变
 输入参数  :
             NAS_MML_ACCESS_RESTRICTION_STRU    *pstOldAcRestrictInfo,
             NAS_MML_ACCESS_RESTRICTION_STRU    *pstNewAcRestrictInfo
 输出参数  : 无
 返 回 值  : VOS_TRUE:发生了改变
             VOS_FALSE:未发生改变
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月11日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_IsAcInfoChanged(
    NAS_MML_ACCESS_RESTRICTION_STRU    *pstOldAcRestrictInfo,
    NAS_MML_ACCESS_RESTRICTION_STRU    *pstNewAcRestrictInfo
)
{
    /* 新老限制注册、限制寻呼、限制正常业务、限制紧急业务标记是否有变化 */
    if ((pstOldAcRestrictInfo->ucRestrictPagingRsp        != pstNewAcRestrictInfo->ucRestrictPagingRsp)
     || (pstOldAcRestrictInfo->ucRestrictRegister         != pstNewAcRestrictInfo->ucRestrictRegister)
     || (pstOldAcRestrictInfo->ucRestrictNormalService    != pstNewAcRestrictInfo->ucRestrictNormalService)
     || (pstOldAcRestrictInfo->ucRestrictEmergencyService != pstNewAcRestrictInfo->ucRestrictEmergencyService))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */

/*******************************************************************************
 函 数 名  : NAS_MML_Update_Revision_Level
 功能描述  : 更新空口消息中的ClassMark IE 的 revision level参数
 输入参数  : pucClassMark:classmark 的第一个字节

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月27日
    作    者   : t00212959
    修改内容   : 新生成函数
*******************************************************************************/
VOS_VOID NAS_MML_Update_Revision_Level(
    VOS_UINT8                          *pucClassMark
)
{
    VOS_INT8                    cVersion;
    VOS_UINT8                   ucRevisionLevel;

    cVersion = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_CS);

    /* R99以前版本，上报 revision level 为 GSM PHASE 2*/
    if(PS_PTL_VER_PRE_R99 == cVersion)
    {
        ucRevisionLevel = MM_CLASSMARK_REVISION_LEVEL_GSM_PH2;
    }
    else
    {
        ucRevisionLevel = MM_CLASSMARK_REVISION_LEVEL_R99_OR_LATER;
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* L使用时都是R99以后的版本*/
    if(NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        ucRevisionLevel = MM_CLASSMARK_REVISION_LEVEL_R99_OR_LATER;
    }
#endif

    *pucClassMark &= 0x9f;
    *pucClassMark |= (VOS_UINT8)(ucRevisionLevel << 5);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetSupportBandNum
 功能描述  : 根据输入参数ulBand来判读该参数变量中有多少个bit值为1，
             此函数可用于判断当前所处频段是否为多频段。
 输入参数  : VOS_UINT32 ulBand
 输出参数  : VOS_UINT8 &ucBandNum，用来取得ulBand中的bit值为1的个数，即频段个数
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月27日
    作    者   : t00212959
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_GetSupportBandNum(
    VOS_UINT32                          ulBand,
    VOS_UINT8                          *pucBandNum
)
{
    /* ucIndicator用来进行移位指示 */
    VOS_UINT8                           ucIndicator;

    /* ucTotalLen表示用来参数usBand的总bit位数 */
    VOS_UINT8                           ucTotalLen;

    /* ucBandNum用来记录bit值为1的个数，并作为函数的返回值 */
    *pucBandNum = 0;
    ucIndicator = 0;
    ucTotalLen  = sizeof(ulBand) * 8;

    /* 通过循环移位计算ulBand中的bit值为1的总个数，并保存到ucBandNum中 */
    while (ucIndicator < ucTotalLen)
    {
        if ((ulBand>>ucIndicator) & 0x01)
        {
            (*pucBandNum)++;
        }

        ucIndicator++;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_Fill_IE_ClassMark2
 功能描述  : 填写空口消息中的ClassMark2 IE
 输入参数  :

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月27日
    作    者   : t00212959
    修改内容   : 新生成函数
  2.日    期   : 2013年4月7日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mmc接口调整

  3.日    期   : 2014年6月17日
    作    者   : z00234330
    修改内容   : PCINT清理
*****************************************************************************/
VOS_VOID NAS_MML_Fill_IE_ClassMark2(
    VOS_UINT8                          *pClassMark2
)
{
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
    GSM_BAND_SET_UN                     unSysCfgSetGsmBand;
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */

    VOS_UINT8                           ucBandNum;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRat;
    NAS_MML_MS_BAND_INFO_STRU          *pstCurrBandInfo = VOS_NULL_PTR;
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability = VOS_NULL_PTR;
    NAS_MML_MS_BAND_INFO_STRU          *pstUserSetBand  = VOS_NULL_PTR;

    pstUserSetBand  = NAS_MML_GetMsSupportBand();
    pstMsCapability = NAS_MML_GetMsCapability();
    pstCurrBandInfo = NAS_MML_GetCurrBandInfo();
    enCurrNetRat    = NAS_MML_GetCurrNetRatType();

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
    if (pstMsCapability->aucClassmark2[0] != 0)
    {
        pClassMark2[0] = pstMsCapability->aucClassmark2[0];
        pClassMark2[1] = pstMsCapability->aucClassmark2[1];
        pClassMark2[2] = pstMsCapability->aucClassmark2[2];
        pClassMark2[3] = pstMsCapability->aucClassmark2[3];

        NAS_MML_Update_Revision_Level(&pClassMark2[1]);

        /* 默认设置FC为0 */
        pClassMark2[2] &= 0xFE;

        /* 不支持G就不填写GSM能力 */
        if ( VOS_FALSE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_GSM))
        {
            // W only
            // ES IND => 0, A5/1 => 1, RF power capability => 111
            pClassMark2[1] &= 0xE0;
            pClassMark2[1] |= 0x0F;

            /* PS capability => 0, VBS => 0, VGCS => 0 */
            pClassMark2[2] &= 0xB9;
            /* SoLSA => 0, A5/3 => 0 */
            pClassMark2[3] &= 0xF5;

        }
        else
        {   /* W/G or G only */
            /* 获取当前的小区网络频段 */
            unSysCfgSetGsmBand.ulBand = pstCurrBandInfo->unGsmBand.ulBand;
            if ( (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrNetRat)
#if (FEATURE_ON == FEATURE_LTE)
              || (NAS_MML_NET_RAT_TYPE_LTE == enCurrNetRat)
#endif
             )
            {
                unSysCfgSetGsmBand.ulBand = pstUserSetBand->unGsmBand.ulBand;
            }
            /* Modified by z00234330 for PCLINT清理, 2014-06-24, begin */
            /*根据当前驻留的频段填写RF power capability*/
            if (( VOS_TRUE == unSysCfgSetGsmBand.stBitBand.BandGsm1800)
             || (VOS_TRUE== unSysCfgSetGsmBand.stBitBand.BandGsm1900))
            {
                /*power class 1*/
                pClassMark2[1] &= ~MM_CLASSMARK_RF_POWER_CAP_MASK;
                pClassMark2[1] |= MM_CLASSMARK_RF_POWER_CAP_CLASS1;
            }
            else /* 其它频段 */
            {
                /*power class 4*/
                pClassMark2[1] &= ~MM_CLASSMARK_RF_POWER_CAP_MASK;
                pClassMark2[1] |= MM_CLASSMARK_RF_POWER_CAP_CLASS4;
            }

            /*当前网络驻留在G下*/
            if (NAS_MML_NET_RAT_TYPE_GSM == enCurrNetRat)
            {

                /* 如果是900，需要判断是否支持E900或R900,如果支持FC为1，
                   否则只支持P900且驻留P900，则FC为0 */
                if ( ( (VOS_TRUE == unSysCfgSetGsmBand.stBitBand.BandGsmE900)
                    || (VOS_TRUE == unSysCfgSetGsmBand.stBitBand.BandGsmR900))
                 || (VOS_TRUE == unSysCfgSetGsmBand.stBitBand.BandGsmP900))
                {
                    if (pstUserSetBand->unGsmBand.ulBand & 0x0030)
                    {
                        pClassMark2[2] |= 0x01;
                    }
                }
            }
            else
            {
                /* 获取用户设置的可在小区内驻留的频段 */
                unSysCfgSetGsmBand.ulBand = pstUserSetBand->unGsmBand.ulBand;

                NAS_MML_GetSupportBandNum(unSysCfgSetGsmBand.ulBand, &ucBandNum);

                /*如果支持多频段或者不支持任何频段，设置RF power capability => 111*/
                if ( ((ucBandNum > 1)
                     ||(0 == ucBandNum))
                   ||((1 == ucBandNum) && ((VOS_TRUE == unSysCfgSetGsmBand.stBitBand.BandGsmE900)
                   || (VOS_TRUE == unSysCfgSetGsmBand.stBitBand.BandGsmR900))) )
                {
                    pClassMark2[1] |= MM_CLASSMARK_RF_POWER_CAP_MASK;
                }

                /* Modified by z00234330 for PCLINT清理, 2014-06-24, end */
            }

        }
    }
	/* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */
    return;
}


/*****************************************************************************
 函 数 名  : NAS_MML_IsCsServDomainAvail
 功能描述  : 根据当前手机模式判断CS域能力是否可用
 输入参数  : enMsMode:手机模式
 输出参数  : 无
 返 回 值  : VOS_TRUE:CS域能力可用
              VOS_FALSE:CS域能力不可用
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2013年6月3日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MML_IsCsServDomainAvail(
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode
)
{
    /* A模式、CS ONLY模式时，认为CS域可用，其他模式认为CS域不可用 */
    if ( (NAS_MML_MS_MODE_PS_CS == enMsMode)
      || (NAS_MML_MS_MODE_CS_ONLY == enMsMode) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MML_ConvertOamSendPid
 功能描述  : svlte特性开启时，modem1可能收到usim0的消息，需要将消息中send pid进行转换
 输入参数  : pulConvertedSendPid - 消息中原始的send pid
 输出参数  : pulConvertedSendPid - 转换后的send pid
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月5日
    作    者   : z00161729
    修改内容   : SVLTE 和usim接口调整修改

  2.日    期   : 2015年6月25日
    作    者   : l00198894
    修改内容   : TSTS
*****************************************************************************/
VOS_VOID NAS_MML_ConvertOamSendPid(
    VOS_UINT32                         *pulConvertedSendPid
)
{
    VOS_UINT32                          ulOrigSendPid;

    ulOrigSendPid = *pulConvertedSendPid;

    if ((I0_WUEPS_PID_USIM == ulOrigSendPid)
     || (I1_WUEPS_PID_USIM == ulOrigSendPid)
     || (I2_WUEPS_PID_USIM == ulOrigSendPid))
    {
        *pulConvertedSendPid = WUEPS_PID_USIM;
        return;
    }

    if ((I0_MAPS_STK_PID == ulOrigSendPid)
     || (I1_MAPS_STK_PID == ulOrigSendPid)
     || (I2_MAPS_STK_PID == ulOrigSendPid))
    {
        *pulConvertedSendPid = MAPS_STK_PID;
        return;
    }

    if ((I0_MAPS_PB_PID == ulOrigSendPid)
     || (I1_MAPS_PB_PID == ulOrigSendPid)
     || (I2_MAPS_PB_PID == ulOrigSendPid))
    {
        *pulConvertedSendPid = MAPS_PB_PID;
        return;
    }

    if ((I0_MAPS_PIH_PID == ulOrigSendPid)
     || (I1_MAPS_PIH_PID == ulOrigSendPid)
     || (I2_MAPS_PIH_PID == ulOrigSendPid))
    {
        *pulConvertedSendPid = MAPS_PIH_PID;
        return;
    }
}

#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 函 数 名  : NAS_MML_IsErrLogNeedRecord
 功能描述  : 查询usLevel级别的异常是否需要记录
 输入参数  : VOS_UINT16 usLevel
 输出参数  : 无
 返 回 值  : VOS_TRUE:   需要上报
             VOS_FALSE:  不需要上报

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月23日
    作    者   : s00190137
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_IsErrLogNeedRecord(VOS_UINT16 usLevel)
{
    /* Log开关关闭，不需要上报 */
    if (0 == NAS_MML_GetErrlogCtrlFlag())
    {
        return VOS_FALSE;
    }

    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return VOS_FALSE;
    }

    /* 模块log级别usLevel大于用户设置的log上报级别或usLevel无效，不需要上报 */
    if ((NAS_MML_GetErrlogAlmLevel() < usLevel)
     || (NAS_ERR_LOG_CTRL_LEVEL_NULL == usLevel))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MML_IsNeedNwSearchInfoRecord
 功能描述  : 是否需要记录搜网信息
 输入参数  : pstMsg
 输出参数  : 无
 返 回 值  : VOS_TRUE  : 需要记录
             VOS_FALSE : 不需要记录
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月13日
    作    者   : f00179208
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsNeedNwSearchInfoRecord(
    VOS_VOID                           *pstMsg
)
{
    MSG_HEADER_STRU                    *pstMsgHeader  = VOS_NULL_PTR;
    NAS_MML_ERRLOG_NW_SEARCH_INFO_STRU *pstNwSrchInfo = VOS_NULL_PTR;
    NAS_MML_REG_STATUS_ENUM_UINT8       ucCsRegState;
    NAS_MML_REG_STATUS_ENUM_UINT8       ucPsRegState;
    VOS_UINT32                          ulIsAsPid;

    pstMsgHeader  = (MSG_HEADER_STRU *)pstMsg;
    ucCsRegState  = NAS_MML_GetCsRegStatus();
    ucPsRegState  = NAS_MML_GetPsRegStatus();
    pstNwSrchInfo = NAS_MML_GetErrLogNwSearchInfoAddr();
    ulIsAsPid     = NAS_MML_IsAsPid(pstMsgHeader->ulSenderPid);

    if (WUEPS_PID_MMC != pstMsgHeader->ulReceiverPid)
    {
        return VOS_FALSE;
    }

    /* 搜网结果回复以及停止搜网结果回复需要记录CHR */
    if (((ID_LMM_MMC_PLMN_SRCH_CNF      == pstMsgHeader->ulMsgName)
      || (ID_LMM_MMC_STOP_PLMN_SRCH_CNF == pstMsgHeader->ulMsgName)
      || (RRMM_PLMN_SEARCH_CNF          == pstMsgHeader->ulMsgName)
      || (RRMM_PLMN_SEARCH_STOP_CNF     == pstMsgHeader->ulMsgName))
     && (VOS_TRUE == ulIsAsPid))
    {
        /* 如果当前在注册状态发生的搜网，则不记录CHR */
        if (((NAS_MML_REG_REGISTERED_HOME_NETWORK == ucCsRegState)
          || (NAS_MML_REG_REGISTERED_ROAM         == ucCsRegState))
         && ((NAS_MML_REG_REGISTERED_HOME_NETWORK == ucPsRegState)
          || (NAS_MML_REG_REGISTERED_ROAM         == ucPsRegState)))
        {
            return VOS_FALSE;
        }

        /* L下的快速指定搜，则不需要记录CHR */
        if ((PS_PID_MM                   == pstMsgHeader->ulSenderPid)
         && (MMC_LMM_PLMN_SRCH_FAST_SPEC == pstNwSrchInfo->ulSearchType))
        {
            return VOS_FALSE;
        }

        /* GUT下的快速指定搜，则不需要记录CHR */
        if ((VOS_TRUE                    == NAS_MML_IsGutAsPid(pstMsgHeader->ulSenderPid))
         && (RRC_PLMN_SEARCH_SPEC_FAST   == pstNwSrchInfo->ulSearchType))
        {
            return VOS_FALSE;
        }

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MML_RecordNwSearchInfo
 功能描述  : 记录搜网回复事件
 输入参数  : pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月13日
    作    者   : f00179208
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_RecordNwSearchInfo(
    VOS_VOID                           *pstMsg
)
{
    MSG_HEADER_STRU                            *pstMsgHeader      = VOS_NULL_PTR;
    NAS_MML_ERRLOG_NW_SEARCH_INFO_STRU         *pstNwSrchInfo     = VOS_NULL_PTR;
    LMM_MMC_PLMN_SRCH_CNF_STRU                 *pstLmmSrchCnfMsg  = VOS_NULL_PTR;
    RRMM_PLMN_SEARCH_CNF_STRU                  *pstRrmmSrchCnfMsg = VOS_NULL_PTR;
    NAS_ERR_LOG_OOS_NW_SRCH_PROC_INFO_STRU      stProcInfoEvent;
    VOS_UINT32                                  ulIsLogNeedRecord;
    VOS_UINT32                                  ulLength;
    VOS_UINT32                                  ulResult;
    VOS_UINT16                                  usLevel;
    VOS_UINT8                                   ucCfgActiveFlag;
    VOS_UINT32                                  ulCfgRecordNum;

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel           = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_OOS_NW_SRCH_PROC_INFO);
    ulIsLogNeedRecord = NAS_MML_IsErrLogNeedRecord(usLevel);
    pstNwSrchInfo     = NAS_MML_GetErrLogNwSearchInfoAddr();
    ulCfgRecordNum    = NAS_MML_GetErrLogNwSrchCfgRecordNum();
    ucCfgActiveFlag   = NAS_MML_GetErrLogNwSrchCfgActiveFlag();

    pstMsgHeader      = (MSG_HEADER_STRU *)pstMsg;

    /* 1. 模块异常不需要记录
       2. NV配置不需要记录 */
    if ((VOS_FALSE == ulIsLogNeedRecord)
     || (VOS_FALSE == ucCfgActiveFlag))
    {
        return;
    }

    /* 如果超过NV记录的最大次数，则不再记录 */
    if (pstNwSrchInfo->ulSearchCount > ulCfgRecordNum)
    {
        return;
    }

    /* 搜索过程记录次数加1 */
    NAS_MML_AddErrLogNwSearchCount();

    ulLength = sizeof(NAS_ERR_LOG_OOS_NW_SRCH_PROC_INFO_STRU);

    /* 填充本地记录信息 */
    PS_MEM_SET(&stProcInfoEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stProcInfoEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_MMC),
                                      NAS_ERR_LOG_ALM_OOS_NW_SRCH_PROC_INFO,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stProcInfoEvent.stPlmnId.ulMcc          = pstNwSrchInfo->stPlmnId.ulMcc;
    stProcInfoEvent.stPlmnId.ulMnc          = pstNwSrchInfo->stPlmnId.ulMnc;
    stProcInfoEvent.enSrchRat               = pstNwSrchInfo->enSrchRat;
    stProcInfoEvent.ucSearchType            = (VOS_UINT8)pstNwSrchInfo->ulSearchType;
    stProcInfoEvent.ulPlmnSrchReqSlice      = pstNwSrchInfo->ulPlmnSrchReqSlice;
    stProcInfoEvent.ulCurPlmnSelectionScene           = pstNwSrchInfo->ulCurPlmnSelectionScene;
    stProcInfoEvent.stOosInfo.ucCurOosPhaseNum        = pstNwSrchInfo->stOosInfo.ucCurOosPhaseNum;
    stProcInfoEvent.stOosInfo.ulCurHistoryTimerCount  = pstNwSrchInfo->stOosInfo.ulCurHistoryTimerCount;
    stProcInfoEvent.stOosInfo.ulCurPrefBandTimerCount = pstNwSrchInfo->stOosInfo.ulCurPrefBandTimerCount;
    stProcInfoEvent.stOosInfo.ulCurFullBandTimerCount = pstNwSrchInfo->stOosInfo.ulCurFullBandTimerCount;
    PS_MEM_CPY(stProcInfoEvent.aucDplmnVersionId, pstNwSrchInfo->aucDplmnVersionId, NAS_INFO_VERSION_INFO_LEN);
    PS_MEM_CPY(stProcInfoEvent.aucMccFreqVersion, pstNwSrchInfo->aucMccFreqVersion, NAS_INFO_VERSION_INFO_LEN);

    if (ID_LMM_MMC_PLMN_SRCH_CNF == pstMsgHeader->ulMsgName)
    {
        pstLmmSrchCnfMsg  = (LMM_MMC_PLMN_SRCH_CNF_STRU *)pstMsg;
        stProcInfoEvent.ucResult        = (VOS_UINT8)pstLmmSrchCnfMsg->enRlst;
        stProcInfoEvent.ucCoverageType  = (VOS_UINT8)pstLmmSrchCnfMsg->enCoverageType;
    }
    else if (RRMM_PLMN_SEARCH_CNF == pstMsgHeader->ulMsgName)
    {
        pstRrmmSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;
        stProcInfoEvent.ucResult        = (VOS_UINT8)pstRrmmSrchCnfMsg->ulSearchRlt;
        stProcInfoEvent.ucCoverageType  = (VOS_UINT8)pstRrmmSrchCnfMsg->enCoverageType;
    }
    else
    {
        stProcInfoEvent.ucResult        = 0xFF;
        stProcInfoEvent.ucCoverageType  = 0xFF;
    }

    /* 清空之前记录的搜网请求信息 */
    pstNwSrchInfo->stPlmnId.ulMcc           = 0;
    pstNwSrchInfo->stPlmnId.ulMnc           = 0;
    pstNwSrchInfo->enSrchRat                = NAS_ERR_LOG_RATMODE_BUTT;
    pstNwSrchInfo->ulSearchType             = 0xFF;
    pstNwSrchInfo->ulPlmnSrchReqSlice       = 0;
    pstNwSrchInfo->ulCurPlmnSelectionScene            = NAS_MMC_PLMN_SEARCH_SCENE_BUTT;
    PS_MEM_SET(&pstNwSrchInfo->stOosInfo, 0x00, sizeof(NAS_MML_OOS_INFO_STRU));
    pstNwSrchInfo->stOosInfo.ucCurOosPhaseNum         = NAS_MMC_OOS_PHASE_BUTT;
    PS_MEM_SET(pstNwSrchInfo->aucDplmnVersionId, 0x00, NAS_INFO_VERSION_INFO_LEN);
    PS_MEM_SET(pstNwSrchInfo->aucMccFreqVersion, 0x00, NAS_INFO_VERSION_INFO_LEN);

    /*
       将异常信息写入Buffer中
       实际写入的字符数与需要写入的不等则打印异常
     */
    ulResult = NAS_MML_PutErrLogRingBuf((VOS_CHAR *)&stProcInfoEvent, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MML_RecordNwSearchInfo(): Push buffer error.");
    }

    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_OOS_NW_SRCH_PROC_INFO,
                           WUEPS_PID_MMC,
                           (VOS_UINT8 *)&stProcInfoEvent,
                           sizeof(stProcInfoEvent));

    return;
}

#endif

/*****************************************************************************
 函 数 名  : NAS_MML_IsGutAsPid
 功能描述  : 是否是GUT接入层的PID
 输入参数  : ulPid
 输出参数  : 无
 返 回 值  : VOS_TRUE  : 是
             VOS_FALSE : 不是
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月27日
    作    者   : f00179208
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsGutAsPid(VOS_UINT32 ulPid)
{
    VOS_UINT32                          ulRslt;

    switch (ulPid)
    {
        case UEPS_PID_GAS:
        case WUEPS_PID_WRR:
        case TPS_PID_RRC:
            ulRslt = VOS_TRUE;
            break;

        default:
            ulRslt = VOS_FALSE;
            break;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : NAS_MML_IsAsPid
 功能描述  : 是否是接入层的PID
 输入参数  : ulPid
 输出参数  : 无
 返 回 值  : VOS_TRUE  : 是
             VOS_FALSE : 不是
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月27日
    作    者   : f00179208
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsAsPid(VOS_UINT32 ulPid)
{
    VOS_UINT32                          ulRslt;

    switch (ulPid)
    {
        case PS_PID_MM:
        case UEPS_PID_GAS:
        case WUEPS_PID_WRR:
        case TPS_PID_RRC:
            ulRslt = VOS_TRUE;
            break;

        default:
            ulRslt = VOS_FALSE;
            break;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SaveNwSearchReqInfo
 功能描述  : 记录搜网请求信息
 输入参数  : pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月13日
    作    者   : f00179208
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_SaveNwSearchReqInfo(
    VOS_VOID                           *pstMsg
)
{
    MSG_HEADER_STRU                        *pstMsgHeader       = VOS_NULL_PTR;
    MMC_LMM_PLMN_SRCH_REQ_STRU             *pstLmmPlmnSrchReq  = VOS_NULL_PTR;
    RRMM_PLMN_SEARCH_REQ_STRU              *pstRrmmPlmnSrchReq = VOS_NULL_PTR;
    NAS_MML_ERRLOG_NW_SEARCH_INFO_STRU     *pstNwSrchInfo      = VOS_NULL_PTR;
    NAS_MML_SIM_FORMAT_PLMN_ID              stSimPlmn;
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU      *pstDplmnNPlmnCfgInfo = VOS_NULL_PTR;
    NAS_MML_OOS_INFO_STRU                   stOosInfo;
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32   enCurPlmnSelectionScene;
    VOS_UINT8                               aucMccFreqVersion[NAS_INFO_VERSION_INFO_LEN] = {0};
    VOS_UINT32                          ulReceiverPid;

    pstMsgHeader  = (MSG_HEADER_STRU *)pstMsg;
    pstNwSrchInfo = NAS_MML_GetErrLogNwSearchInfoAddr();

    ulReceiverPid = pstMsgHeader->ulReceiverPid;

    /* 记录OOS相关信息 */
    PS_MEM_SET(&stOosInfo, 0x00, sizeof(NAS_MML_OOS_INFO_STRU));
    NAS_MMC_GetOosCurInfo(&stOosInfo);

    /* 记录当前搜网场景 */
    enCurPlmnSelectionScene = NAS_MMC_PLMN_SEARCH_SCENE_BUTT;

    if (NAS_MMC_FSM_PLMN_SELECTION == NAS_MMC_GetCurrFsmId())
    {
        enCurPlmnSelectionScene = NAS_MMC_GetPlmnSearchScene_PlmnSelection();
    }

    /* 记录Dplmn版本号 */
    pstDplmnNPlmnCfgInfo = NAS_MMC_GetDPlmnNPlmnCfgInfo();

    /* 记录预置频点版本号 */
    //aucMccFreqVersion[NAS_INFO_VERSION_INFO_LEN] = {0};

    /* LTE的搜网请求 */
    if ((ID_MMC_LMM_PLMN_SRCH_REQ == pstMsgHeader->ulMsgName)
     && (PS_PID_MM                == ulReceiverPid))
    {
        PS_MEM_SET(&stSimPlmn, 0x0, sizeof(NAS_MML_SIM_FORMAT_PLMN_ID));

        pstLmmPlmnSrchReq = (MMC_LMM_PLMN_SRCH_REQ_STRU *)pstMsg;

        pstNwSrchInfo->enSrchRat          = NAS_ERR_LOG_RATMODE_LTE;
        pstNwSrchInfo->ulSearchType       = pstLmmPlmnSrchReq->enSrchType;
        pstNwSrchInfo->ulPlmnSrchReqSlice = VOS_GetSlice();

        pstNwSrchInfo->ulCurPlmnSelectionScene            = enCurPlmnSelectionScene;
        pstNwSrchInfo->stOosInfo.ucCurOosPhaseNum         = stOosInfo.ucCurOosPhaseNum;
        pstNwSrchInfo->stOosInfo.ulCurHistoryTimerCount   = stOosInfo.ulCurHistoryTimerCount;
        pstNwSrchInfo->stOosInfo.ulCurPrefBandTimerCount  = stOosInfo.ulCurPrefBandTimerCount;
        pstNwSrchInfo->stOosInfo.ulCurFullBandTimerCount  = stOosInfo.ulCurFullBandTimerCount;
        PS_MEM_CPY(pstNwSrchInfo->aucDplmnVersionId, pstDplmnNPlmnCfgInfo->aucVersionId, NAS_INFO_VERSION_INFO_LEN);
        PS_MEM_CPY(pstNwSrchInfo->aucMccFreqVersion, aucMccFreqVersion, NAS_INFO_VERSION_INFO_LEN);

        /* 先转换为SIM格式 */
        PS_MEM_CPY(stSimPlmn.aucSimPlmn,
                   pstLmmPlmnSrchReq->stSpecPlmnId.aucPlmnId,
                   MMC_LMM_PLMN_ID_LEN);

        NAS_MML_ConvertSimPlmnToNasPLMN(&stSimPlmn,
                                        (NAS_MML_PLMN_ID_STRU *)&pstNwSrchInfo->stPlmnId);

        return;
    }

    /* GUT的搜网请求 */
    if (RRMM_PLMN_SEARCH_REQ == pstMsgHeader->ulMsgName)
    {
        pstRrmmPlmnSrchReq = (RRMM_PLMN_SEARCH_REQ_STRU *)pstMsg;

        pstNwSrchInfo->ulSearchType       = pstRrmmPlmnSrchReq->ulSearchType;
        pstNwSrchInfo->stPlmnId.ulMcc     = pstRrmmPlmnSrchReq->aPlmnIdList[0].ulMcc;
        pstNwSrchInfo->stPlmnId.ulMnc     = pstRrmmPlmnSrchReq->aPlmnIdList[0].ulMnc;
        pstNwSrchInfo->ulPlmnSrchReqSlice = VOS_GetSlice();

        pstNwSrchInfo->ulCurPlmnSelectionScene            = enCurPlmnSelectionScene;
        pstNwSrchInfo->stOosInfo.ucCurOosPhaseNum         = stOosInfo.ucCurOosPhaseNum;
        pstNwSrchInfo->stOosInfo.ulCurHistoryTimerCount   = stOosInfo.ulCurHistoryTimerCount;
        pstNwSrchInfo->stOosInfo.ulCurPrefBandTimerCount  = stOosInfo.ulCurPrefBandTimerCount;
        pstNwSrchInfo->stOosInfo.ulCurFullBandTimerCount  = stOosInfo.ulCurFullBandTimerCount;
        PS_MEM_CPY(pstNwSrchInfo->aucDplmnVersionId, pstDplmnNPlmnCfgInfo->aucVersionId, NAS_INFO_VERSION_INFO_LEN);
        PS_MEM_CPY(pstNwSrchInfo->aucMccFreqVersion, aucMccFreqVersion, NAS_INFO_VERSION_INFO_LEN);

        if (UEPS_PID_GAS == ulReceiverPid)
        {
            pstNwSrchInfo->enSrchRat = NAS_ERR_LOG_RATMODE_GSM;
        }
        else if (WUEPS_PID_WRR == ulReceiverPid)
        {
            pstNwSrchInfo->enSrchRat = NAS_ERR_LOG_RATMODE_WCDMA;
        }
        else
        {
            pstNwSrchInfo->enSrchRat = NAS_ERR_LOG_RATMODE_TDS;
        }

        return;

    }
}

/*****************************************************************************
 函 数 名  : NAS_MML_ConvertSimPlmnToNasPLMN
 功能描述  : 将SIM卡中的3字节格式PLMN转换为MCC和MNC分开的格式
 输入参数  : aucEFplmn[3]
 输出参数  : 无
 返 回 值  :MMC_PLMN_ID_STRU
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月13日
    作    者   : f00179208
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_MML_ConvertSimPlmnToNasPLMN(
    NAS_MML_SIM_FORMAT_PLMN_ID          *pstSimPlmn,
    NAS_MML_PLMN_ID_STRU                *pstNasPlmn
)
{

    VOS_UINT32                          ulTempData;
    NAS_MML_PLMN_ID_STRU                stPlmn;

    /*
       PLMN BCD 编码 方式

       MCC digit 2,  MCC digit 1, ----OCTET 1
       MNC digit 3,  MCC digit 3, ----OCTET 2
       MNC digit 2,  MNC digit 1, ----OCTET 3
    */
    ulTempData = NAS_MML_OCTET_LOW_FOUR_BITS & (pstSimPlmn->aucSimPlmn[0]);
    stPlmn.ulMcc = ulTempData;
    ulTempData = (NAS_MML_OCTET_HIGH_FOUR_BITS & (pstSimPlmn->aucSimPlmn[0])) >> NAS_MML_OCTET_MOVE_FOUR_BITS;
    stPlmn.ulMcc |= ulTempData << NAS_MML_OCTET_MOVE_EIGHT_BITS;

    ulTempData = NAS_MML_OCTET_LOW_FOUR_BITS & (pstSimPlmn->aucSimPlmn[1]);
    stPlmn.ulMcc |= ulTempData << NAS_MML_OCTET_MOVE_SIXTEEN_BITS;
    ulTempData = (NAS_MML_OCTET_HIGH_FOUR_BITS & (pstSimPlmn->aucSimPlmn[1])) >> NAS_MML_OCTET_MOVE_FOUR_BITS;

    stPlmn.ulMnc = ulTempData << NAS_MML_OCTET_MOVE_SIXTEEN_BITS;
    ulTempData = NAS_MML_OCTET_LOW_FOUR_BITS & (pstSimPlmn->aucSimPlmn[2]);
    stPlmn.ulMnc |= ulTempData;
    ulTempData = (NAS_MML_OCTET_HIGH_FOUR_BITS & (pstSimPlmn->aucSimPlmn[2])) >> NAS_MML_OCTET_MOVE_FOUR_BITS;
    stPlmn.ulMnc |= ulTempData << NAS_MML_OCTET_MOVE_EIGHT_BITS;

    *pstNasPlmn = stPlmn;


    return ;

}



/*****************************************************************************
 函 数 名  : NAS_MML_DecodeEmergencyNumList
 功能描述  : 解码紧急呼叫号码
 输入参数  : VOS_UINT16          *pusIndex
             VOS_UINT8           *pucRcvMsg
             VOS_UINT16          usMsgSize
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月3日
    作    者   : l65478
    修改内容   : 新生成函数
  2.日    期   : 2012年3月27日
    作    者   : w00166186
    修改内容   : CSFB&PPAC&ETWS&ISR 开发 EMERGENCY CALL
  3.日    期   : 2012年07月05日
    作    者   : w00166186
    修改内容   : AT&T&DCM项目
  4.日    期   : 2013年10月25日
    作    者   : w00167002
    修改内容   : DTS2013102201891:增加对紧急呼长度异常的处理。
                 1.按照紧急呼填写的总长度值解析，会超过整个消息的长度，则认为异常；
                 2.按照每个子紧急呼消息的长度值解析，超过了紧急呼填写的总长度值，则认为异常；

                 调整NAS_MM_DecodeEMC函数到MML中，供GMM/MM解码紧急呼列表使用
 5.日    期   : 2014年6月17日
   作    者   : z00234330
   修改内容   : PCINT清理
*****************************************************************************/

VOS_UINT32 NAS_MML_DecodeEmergencyNumList(
    VOS_UINT16                         *pusIndex,
    VOS_UINT8                          *pucRcvMsg,
    VOS_UINT16                          usMsgSize
)
{
    NAS_MML_EMERGENCY_NUM_LIST_STRU    *pstEmergencyNumList = VOS_NULL_PTR;
    VOS_UINT16                          usIndex;
    VOS_UINT8                           ucTotalIeLength;
    VOS_UINT8                           ucParseEmcTotalLength;
    VOS_UINT8                           ucTempLength;
    VOS_UINT8                           ucLength;
    VOS_UINT8                           i;

    usIndex                             = *pusIndex;
    ucTotalIeLength                     = 0;
    ucTempLength                        = 0;
    ucLength                            = 0;
    ucParseEmcTotalLength               = 0;

    pstEmergencyNumList                 = NAS_MML_GetEmergencyNumList();

    pstEmergencyNumList->ucEmergencyNumber = 0;

    /* 整个紧急呼IE的长度，包括IEI */
    ucTotalIeLength       = pucRcvMsg[usIndex + 1] + 2;

    /* Length of Emergency Number List IE contents */
    ucParseEmcTotalLength = pucRcvMsg[usIndex + 1];

    /* 按照紧急呼填写的总长度值解析，会超过整个消息的长度，则认为异常 */
    if ( ( *pusIndex + ucTotalIeLength) > usMsgSize )
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MML_DecodeEmergencyNumList: IE emergency number length error!!!");

        *pusIndex = usMsgSize;

        /* 解析异常，直接返回END */
        return VOS_FALSE;
    }

    if ( ucParseEmcTotalLength < NAS_MML_MIN_EMERGENCY_NUM_LEN )
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MML_DecodeEmergencyNumList: IE emergency number length < NAS_MML_MIN_EMERGENCY_NUM_LEN error !!!");

        /* 直接指向紧急呼的结束符号:即下一个IEI或解析完毕了 */
        *pusIndex = *pusIndex + ucTotalIeLength;

        return VOS_FALSE;
    }

    if ( ucParseEmcTotalLength > NAS_MML_MAX_EMERGENCY_NUM_LEN )
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MML_DecodeEmergencyNumList: IE emergency number length > NAS_MML_MAX_EMERGENCY_NUM_LEN error !!!");

        ucParseEmcTotalLength =  NAS_MML_MAX_EMERGENCY_NUM_LEN;
    }

    /* 指向第一个紧急呼列表 */
    usIndex = usIndex + 2;

    while (ucParseEmcTotalLength > ucTempLength)
    {

       ucLength     = pucRcvMsg[usIndex];                                      /* Length of Nst Emergency Number information */

       /*************************************************************************
       *TS 24.007, section 11.4.2
       * -- It is not a syntactical error that a type 4 standard IE specifies in
       * its length indicator a greater length than possible according to the
       * value part specification: extra bits shall be ignored.
       *
       *TS 24.007, section 11.2.1.1.4
       *A type 4 standard information element has format LV or TLV. Its LI precedes
       *the value part, which consists of zero, one, or more octets; if present,
       *its IEI has one octet length and precedes the LI.
       *
       *Hence, this is a type 4 information element.
       **************************************************************************/
        if ( (ucTempLength + 1 + NAS_MML_MIN(ucLength, NAS_MML_MAX_EMERGENCY_NUM_INFO_LEN)) > ucParseEmcTotalLength )
        {
            /* 直接指向紧急呼的结束符号:即下一个IEI或解析完毕了 */
            *pusIndex = *pusIndex + ucTotalIeLength;

            return VOS_FALSE;
        }

        /* 含有无效的EMERGENCY Number List子项,则认为整个紧急呼列表都无效 */
        if (ucLength < NAS_MML_MIN_EMERGENCY_NUM_INFO_LEN)
        {
            pstEmergencyNumList->ucEmergencyNumber = 0;
            *pusIndex = *pusIndex + ucTotalIeLength;
            return VOS_FALSE;
        }

        ucTempLength = ucTempLength + ucLength + 1;                             /* 累计所有Emergency Number List的总长度，包括 Length IE */

        if (ucLength > NAS_MML_MAX_EMERGENCY_NUM_INFO_LEN)
        {
            /* usIndex指向下一个紧急呼长度 */
            usIndex += ucTempLength;

            /* 仅忽略掉当前紧急呼项 */
            continue;
        }

        pstEmergencyNumList->ucEmergencyNumber++;
        pstEmergencyNumList->aucEmergencyList[pstEmergencyNumList->ucEmergencyNumber - 1].ucEmcNumLen
            = ucLength - 1;
        pstEmergencyNumList->aucEmergencyList[pstEmergencyNumList->ucEmergencyNumber - 1].ucCategory
            = pucRcvMsg[usIndex + 1] & 0x1F;                                    /* Emergency Service Category Value         */

        /* 偏移到 Number digit 1 字节 */
        usIndex = usIndex + 2;

        for (i = 0; i < (ucLength - 1); i++)
        {
            /* Modified by z00234330 for PCLINT清理, 2014-06-24, begin */
            pstEmergencyNumList->aucEmergencyList[pstEmergencyNumList->ucEmergencyNumber - 1].aucEmcNum[i]
                = pucRcvMsg[usIndex];                                        /* Number digit N                           */
            usIndex++;
            /* Modified by z00234330 for PCLINT清理, 2014-06-24, end */
        }

        /* usIndex指向下一个紧急呼长度 */

        if (pstEmergencyNumList->ucEmergencyNumber >= NAS_MML_EMERGENCY_NUM_LIST_MAX_RECORDS)
        {
            /* 达到自大紧急呼个数，则认为解析完毕 */
            *pusIndex = *pusIndex + ucTotalIeLength;

            return VOS_TRUE;
        }

    }

    /* 解析完毕，则指向最后一个字符 */
    *pusIndex = *pusIndex + ucTotalIeLength;

    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : NAS_MML_IsNvimOplmnAvail
 功能描述  : 查询NV中用户配置的OPLMN列表是否生效
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_TRUE:   列表有效
             VOS_FALSE:  列表无效

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月15日
    作    者   : s00190137
    修改内容   : 新生成函数
  2.日    期   : 2013年11月26日
    作    者   : s00190137
    修改内容   : 添加分组机制，最大支持设置256个OPLMN,单组允许最大设置50个OPLMN
*****************************************************************************/
VOS_UINT32 NAS_MML_IsNvimOplmnAvail(VOS_VOID)
{
    VOS_UINT32                          ulStep;
    NAS_MML_PLMN_ID_STRU                stHPlmn;
    RRC_NAS_SIM_STATUS_ENUM_UINT32      ulCardStatus;
    VOS_UINT8                          *pucImsi             = VOS_NULL_PTR;
    NAS_MML_USER_CFG_OPLMN_INFO_STRU   *pstUserCfgOPlmnInfo = VOS_NULL_PTR;

    PS_MEM_SET(&stHPlmn, 0x00, sizeof(NAS_MML_PLMN_ID_STRU));

    pstUserCfgOPlmnInfo = NAS_MML_GetUserCfgOPlmnInfo();

    /* 特性开关未打开，或OPLMN个数为0，内置OPLMN功能无效 */
    if ((VOS_FALSE == pstUserCfgOPlmnInfo->ucActiveFlg)
     || (0 == pstUserCfgOPlmnInfo->usOplmnListNum))
    {
        return VOS_FALSE;
    }

    /* 卡类型不为USIM，或卡不存在时，内置OPLMN不生效 */
    ulCardStatus = NAS_MML_GetRrcSimStatus();

    if (RRC_NAS_USIM_PRESENT != ulCardStatus)
    {
        return VOS_FALSE;
    }

    /* IMSI检查未使能，不需要做IMSI检查 */
    if (VOS_FALSE == pstUserCfgOPlmnInfo->ucImsiCheckFlg)
    {
        return VOS_TRUE;
    }

    /* 取得本地维护的IMSI的地址 */
    pucImsi  = NAS_MML_GetSimImsi();

    /* 从当前的IMSI中取出home plmn */
    stHPlmn  = NAS_MML_GetImsiHomePlmn(pucImsi);

    /* 如果当前IMSI中的Home Plmn在astImsiPlmnList中，内置OPLMN功能生效 */
    for ( ulStep = 0 ; ulStep < pstUserCfgOPlmnInfo->ucImsiPlmnListNum; ulStep++ )
    {
        if ( VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&pstUserCfgOPlmnInfo->astImsiPlmnList[ulStep],
                                                            &stHPlmn) )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-21, begin */
/*****************************************************************************
 函 数 名  : NAS_MML_Fill_IE_TddClassMark3
 功能描述  : 填写空口消息中的TDD模式下的ClassMark3 IE
 输入参数  :

 输出参数  : pucTddClassMark3---TDD模式下的classmark3
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月21日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2014年2月27日
    作    者   : w00242748
    修改内容   : DTS2014022805239
*****************************************************************************/
VOS_VOID NAS_MML_Fill_IE_TddClassMark3(
    VOS_UINT8                          *pucTddClassMark3
)
{
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability = VOS_NULL_PTR;
    VOS_UINT8                           ucLen;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulRst;
    RRMM_CLASSMARK_CHANGE_IND_STRU     *pstRrmmClassMarkChgInd = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurNetRatType;
    RRC_PLMN_ID_STRU                    stRrmmPlmnId;

    enCurNetRatType        = NAS_MML_GetCurrNetRatType();

    pstRrmmClassMarkChgInd = (RRMM_CLASSMARK_CHANGE_IND_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC, sizeof(RRMM_CLASSMARK_CHANGE_IND_STRU));

    /* 当前NV打开，申请内存成功且当前模不是GSM */
    if ( (VOS_TRUE == NAS_MML_GetIsDelFddBandSwitchOnFlg())
      && (VOS_NULL_PTR != pstRrmmClassMarkChgInd)
      && (NAS_MML_NET_RAT_TYPE_GSM != enCurNetRatType) )
    {
        PS_MEM_SET(pstRrmmClassMarkChgInd, 0x00, sizeof(RRMM_CLASSMARK_CHANGE_IND_STRU));

        stRrmmPlmnId.ulMcc = NAS_MML_GetCurrCampPlmnId()->ulMcc;
        stRrmmPlmnId.ulMnc = NAS_MML_GetCurrCampPlmnId()->ulMnc;

        /* 调用GAS接口获取TDD classmark3 */
        ulRst = GASGCOM_GetMsCapability(&stRrmmPlmnId, NAS_GAS_MS_CAP_TYPE_CLASSMARK,
                                                sizeof(RRMM_CLASSMARK_CHANGE_IND_STRU),
                                                (VOS_UINT8*)pstRrmmClassMarkChgInd);

        if ( VOS_TRUE == ulRst )
        {
            pucTddClassMark3[0] = pstRrmmClassMarkChgInd->ucClassmark3TddLen;
            PS_MEM_CPY(&pucTddClassMark3[1], pstRrmmClassMarkChgInd->aucClassmark3Tdd, pucTddClassMark3[0]);

            PS_MEM_FREE(WUEPS_PID_MMC, pstRrmmClassMarkChgInd);
            return;
        }
    }
#endif

    pstMsCapability = NAS_MML_GetMsCapability();

    /* 第0位填写为长度 */
    ucLen = pstMsCapability->aucTddClassmark3[0];

    PS_MEM_CPY(&pucTddClassMark3[0], &(pstMsCapability->aucTddClassmark3[0]), ucLen+1);

#if (FEATURE_ON == FEATURE_LTE)
    if ( VOS_NULL_PTR != pstRrmmClassMarkChgInd )
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstRrmmClassMarkChgInd);
    }
#endif

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_Fill_IE_FddClassMark3
 功能描述  : 填写空口消息中的FDD模式下的ClassMark3 IE
 输入参数  :

 输出参数  : pucFddClassMark3---FDD模式下的classmark3
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月21日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2014年2月27日
    作    者   : w00242748
    修改内容   : DTS2014022805239
*****************************************************************************/
VOS_VOID NAS_MML_Fill_IE_FddClassMark3(
    VOS_UINT8                          *pucFddClassMark3
)
{
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability = VOS_NULL_PTR;
    VOS_UINT8                           ucLen;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulRst;
    RRMM_CLASSMARK_CHANGE_IND_STRU     *pstRrmmClassMarkChgInd = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurNetRatType;
    RRC_PLMN_ID_STRU                    stRrmmPlmnId;

    enCurNetRatType        = NAS_MML_GetCurrNetRatType();

    pstRrmmClassMarkChgInd = (RRMM_CLASSMARK_CHANGE_IND_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC, sizeof(RRMM_CLASSMARK_CHANGE_IND_STRU));

    /* 当前NV打开，申请内存成功且当前模不是GSM */
    if ( (VOS_TRUE == NAS_MML_GetIsDelFddBandSwitchOnFlg())
      && (VOS_NULL_PTR != pstRrmmClassMarkChgInd)
      && (NAS_MML_NET_RAT_TYPE_GSM != enCurNetRatType) )
    {
        PS_MEM_SET(pstRrmmClassMarkChgInd, 0x00, sizeof(RRMM_CLASSMARK_CHANGE_IND_STRU));

        stRrmmPlmnId.ulMcc = NAS_MML_GetCurrCampPlmnId()->ulMcc;
        stRrmmPlmnId.ulMnc = NAS_MML_GetCurrCampPlmnId()->ulMnc;

        /* 调用GAS接口获取FDD classmark3 */
        ulRst = GASGCOM_GetMsCapability(&stRrmmPlmnId, NAS_GAS_MS_CAP_TYPE_CLASSMARK,
                                                sizeof(RRMM_CLASSMARK_CHANGE_IND_STRU),
                                                (VOS_UINT8*)pstRrmmClassMarkChgInd);

        if ( VOS_TRUE == ulRst )
        {
            pucFddClassMark3[0] = pstRrmmClassMarkChgInd->ucClassmark3FddLen;
            PS_MEM_CPY(&pucFddClassMark3[1], pstRrmmClassMarkChgInd->aucClassmark3Fdd, pucFddClassMark3[0]);

            PS_MEM_FREE(WUEPS_PID_MMC, pstRrmmClassMarkChgInd);
            return;
        }
    }
#endif

    pstMsCapability = NAS_MML_GetMsCapability();

    /* 第0位填写为长度 */
    ucLen = pstMsCapability->aucFddClassmark3[0];

    PS_MEM_CPY(&pucFddClassMark3[0], &(pstMsCapability->aucFddClassmark3[0]), ucLen+1);

#if(FEATURE_ON == FEATURE_LTE)
    if ( VOS_NULL_PTR != pstRrmmClassMarkChgInd )
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstRrmmClassMarkChgInd);
    }
#endif

    return;
}


/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-21, end */


/* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, begin */
/*****************************************************************************
 函 数 名  : NAS_MML_DelEqualPlmnsInDisableRatList
 功能描述  : 将等效PLMN中在禁止列表且不是当前驻留网络删除
 输入参数  : VOS_UINT8                           *pEPlmnNum,
             NAS_MML_PLMN_ID_STRU                    *pEPlmnList,
             VOS_UINT8                           ucRefPlmnNum,
             NAS_MML_PLMN_ID_STRU                    *pRefPlmnList
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月25日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2015年1月14日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
  3.日    期   : 2015年4月23日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID NAS_MML_DelEqualPlmnsInDisableRatList(
    VOS_UINT8                                              *pucEPlmnNum,
    NAS_MML_PLMN_ID_STRU                                   *pstEPlmnList,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enSpecRat,
    VOS_UINT32                                              ulDisabledRatPlmnNum,
    NAS_MML_DISABLED_PLMN_WITH_FORBIDDEN_PERIOD_STRU       *pstDisabledRatPlmnIdList
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucPlmnNum;
    VOS_UINT32                          ulRlst;
    NAS_MML_PLMN_WITH_RAT_STRU          stPlmnWithRat;

    ucPlmnNum = *pucEPlmnNum;

    for ( i = 0; i < ucPlmnNum;  )
    {
        /* 构造带接入技术的PLMN ID */
        stPlmnWithRat.enRat         = enSpecRat;
        stPlmnWithRat.stPlmnId      = pstEPlmnList[i];

        ulRlst = NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnRatList(&stPlmnWithRat,
                                                                  ulDisabledRatPlmnNum,
                                                                  pstDisabledRatPlmnIdList);

        /* 将在禁止列表且不是当前驻留网络删除 */
        if ( VOS_TRUE == ulRlst )
        {
            if (i < (ucPlmnNum - 1))
            {
                (VOS_VOID)PS_MEM_MOVE(&pstEPlmnList [i], &pstEPlmnList[ i + 1 ],
                            ((ucPlmnNum - i) - 1 ) * sizeof(NAS_MML_PLMN_ID_STRU));
            }

            ucPlmnNum--;

            if ( i > 0 )
            {
                i--;
            }
            else
            {
                continue;
            }

        }

        i++;
    }

    *pucEPlmnNum = ucPlmnNum;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_DelEqualPlmnNotInAllowLteRoamMccList
 功能描述  : 将等效PLMN中不在LTE漫游的MCC列表且不是当前驻留网络删除
 输入参数  : VOS_UINT8                           *pEPlmnNum,
             NAS_MML_PLMN_ID_STRU                *pEPlmnList,
             VOS_UINT8                            ulAllowLteRoamMccNum,
             NAS_MML_PLMN_ID_STRU                *pulAllowLteRoamMccList
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月25日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2013年1月13日
    作    者   : w00242748
    修改内容   : DTS2014010906851:NV 9052配置不允许国际漫游，配置允许漫游MCC为440，
                当前设置接入模式支持GL，L的46012在禁止国际漫游列表中，不应该发起
                注册。刚开始驻留在G，衰减G 46012小区信号，紧急驻留在L的46012，此时
                发生同系统切换到另一个PLMN为46012的小区上，L会报假的TAU流程，MMC收到
                TAU结果后，给LNAS发送等效PLMN 46012，此时LAS因为ANYCELL驻留又收到
                等效PLMN通知，则认为正常驻留，因此会发起注册。
*****************************************************************************/
VOS_VOID NAS_MML_DelEqualPlmnNotInAllowLteRoamMccList(
    VOS_UINT8                          *pucEPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstEPlmnList,
    VOS_UINT32                          ulAllowLteRoamMccNum,
    VOS_UINT32                         *pulAllowLteRoamMccList
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucPlmnNum;
    VOS_UINT8                           ucLteRoamFlg;


    ucPlmnNum       = *pucEPlmnNum;
    ucLteRoamFlg    = NAS_MML_GetLteRoamAllowedFlg();

    /* 允许LTE国际漫游时，不删除 */
    if (VOS_TRUE == ucLteRoamFlg)
    {
        return;
    }

    for ( i = 0; i < ucPlmnNum;  )
    {
            /* EPLMN ID为国际漫游网络,不允许漫游,需要删除 */
        if (VOS_FALSE == NAS_MML_IsMccInDestMccList(pstEPlmnList[i].ulMcc, ulAllowLteRoamMccNum, pulAllowLteRoamMccList))
        {
            if (i < (ucPlmnNum - 1))
            {
                (VOS_VOID)PS_MEM_MOVE(&pstEPlmnList [i], &pstEPlmnList[ i + 1 ],
                            ((ucPlmnNum - i) - 1 ) * sizeof(NAS_MML_PLMN_ID_STRU));
            }

            ucPlmnNum--;

            if ( i > 0 )
            {
                i--;
            }
            else
            {
                continue;
            }
        }

        i++;
    }

    *pucEPlmnNum = ucPlmnNum;

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_DelDuplicatedPlmnInPlmnList
 功能描述  : 将等效PLMN中不在LTE漫游的MCC列表且不是当前驻留网络删除
 输入参数  : VOS_UINT8                           *pEPlmnNum,
             NAS_MML_PLMN_ID_STRU                *pEPlmnList,
             VOS_UINT8                            ulAllowLteRoamMccNum,
             NAS_MML_PLMN_ID_STRU                *pulAllowLteRoamMccList
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月25日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_DelDuplicatedPlmnInPlmnList(
    VOS_UINT8                          *pucPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstPlmnList
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucPlmnNum;


    ucPlmnNum       = *pucPlmnNum;

    /* 第一个PLMN肯定不会重复，默认在列表中，循环变量从1开始 */
    for ( i = 1; i < ucPlmnNum;  )
    {
        if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(&(pstPlmnList[i]),
                                               i, pstPlmnList))
        {
            if (i < (ucPlmnNum - 1))
            {
                (VOS_VOID)PS_MEM_MOVE(&pstPlmnList [i], &pstPlmnList[ i + 1 ],
                            ((ucPlmnNum - i) - 1 ) * sizeof(NAS_MML_PLMN_ID_STRU));
            }

            ucPlmnNum--;

            if ( i > 0 )
            {
                i--;
            }
            else
            {
                continue;
            }
        }

        i++;
    }

    *pucPlmnNum = ucPlmnNum;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_DelForbPlmnInPlmnList
 功能描述  : 将等效PLMN中不在LTE漫游的MCC列表且不是当前驻留网络删除
 输入参数  : VOS_UINT8                           *pEPlmnNum,
             NAS_MML_PLMN_ID_STRU                *pEPlmnList,
             VOS_UINT8                            ulAllowLteRoamMccNum,
             NAS_MML_PLMN_ID_STRU                *pulAllowLteRoamMccList
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月25日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_DelForbPlmnInPlmnList(
    VOS_UINT8                          *pucPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstPlmnList
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucPlmnNum;


    ucPlmnNum       = *pucPlmnNum;

    for ( i = 0; i < ucPlmnNum;  )
    {
        if (VOS_TRUE == NAS_MML_IsPlmnIdInForbidPlmnList(&(pstPlmnList[i])))
        {
            if (i < (ucPlmnNum - 1))
            {
                (VOS_VOID)PS_MEM_MOVE(&pstPlmnList [i], &pstPlmnList[ i + 1 ],
                            ((ucPlmnNum - i) - 1 ) * sizeof(NAS_MML_PLMN_ID_STRU));
            }

            ucPlmnNum--;

            if ( i > 0 )
            {
                i--;
            }
            else
            {
                continue;
            }
        }

        i++;
    }

    *pucPlmnNum = ucPlmnNum;

    return;
}

/* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */

/*****************************************************************************
 函 数 名  : NAS_MML_GetCsOnlyDataServiceSupportFlg
 功能描述  : 获取PS注册被禁止情况下，是否允许数据业务触发注册的标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE 允许数据业务触发注册，
             VOS_FALSE 不允许数据业务触发注册，
 调用函数  :
 被调函数  :

 修改历史      :
    1.日    期   : 2014年02月13日
      作    者   : f62575
      修改内容   : DTS2014012902032
*****************************************************************************/
VOS_UINT32 NAS_MML_GetCsOnlyDataServiceSupportFlg(VOS_VOID)
{
    VOS_UINT32                                              ulIsTestCard;
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU                    *pstMiscellaneousCfgInfo = VOS_NULL_PTR;

    /* GCF测试卡允许PS业务触发注册流程 */
    ulIsTestCard    = NAS_USIMMAPI_IsTestCard();
    if (VOS_TRUE == ulIsTestCard)
    {
        return VOS_TRUE;
    }

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();

    if (VOS_FALSE == pstMiscellaneousCfgInfo->ucCsOnlyDataServiceSupportFlg)
    {
        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MML_IsPlmnListSrchRslt
 功能描述  : 判断搜网结果是否是LIST搜网结果
 输入参数  : 搜网结果
 输出参数  : 无
 返 回 值  : VOS_TRUE 是LIST搜网结果
             VOS_FALSE 不是LIST搜网结果
 调用函数  :
 被调函数  :

 修改历史      :
    1.日    期   : 2014年02月21日
      作    者   : s00217060
      修改内容   : DTS2014021902519
    2.日    期   : 2015年5月29日
      作    者   : s00217060
      修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0修改
*****************************************************************************/
VOS_UINT32 NAS_MML_IsPlmnListSrchRslt(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT32                          enPlmnSrchRslt
)
{

    switch(enRat)
    {
        /* GU时这些搜网结果是列表搜结果 */
        case NAS_MML_NET_RAT_TYPE_GSM:
        case NAS_MML_NET_RAT_TYPE_WCDMA:

            if ((RRC_PLMN_SEARCH_RLT_LIST           == enPlmnSrchRslt)
             || (RRC_PLMN_SEARCH_RLT_LIST_REJ       == enPlmnSrchRslt)
             || (RRC_PLMN_SEARCH_RLT_LIST_FAIL      == enPlmnSrchRslt)
             || (RRC_PLMN_SEARCH_RLT_LIST_NO_RF     == enPlmnSrchRslt))
            {
                return VOS_TRUE;
            }
            break;

        /* LTE时这些搜网结果是列表搜结果 */
        case NAS_MML_NET_RAT_TYPE_LTE:

            if ((MMC_LMM_PLMN_SRCH_RLT_LIST_SUCC    == enPlmnSrchRslt)
             || (MMC_LMM_PLMN_SRCH_RLT_LIST_REJ     == enPlmnSrchRslt)
             || (MMC_LMM_PLMN_SRCH_RLT_LIST_NO_RF   == enPlmnSrchRslt))
            {
                return VOS_TRUE;
            }
            break;

        default:

            break;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MML_IsGetGeoPlmnSrchRslt
 功能描述  : 搜网回复是否为get_geo结果
 输入参数  : VOS_UINT32     enPlmnSrchRslt
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_IsGetGeoPlmnSrchRslt(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT32                          enPlmnSrchRslt
)
{
    switch(enRat)
    {
        /* GU下时这些搜网结果是GET_GEO结果 */
        case NAS_MML_NET_RAT_TYPE_GSM:
        case NAS_MML_NET_RAT_TYPE_WCDMA:

            if ((RRC_PLMN_SEARCH_RLT_GET_GEO_SUCC   == enPlmnSrchRslt)
             || (RRC_PLMN_SEARCH_RLT_GET_GEO_FAIL   == enPlmnSrchRslt)
             || (RRC_PLMN_SEARCH_RLT_GET_GEO_NO_RF  == enPlmnSrchRslt))
            {
                return VOS_TRUE;
            }
            break;

        /* LTE时这些搜网结果是GET_GEO结果 */
        case NAS_MML_NET_RAT_TYPE_LTE:

            if ((MMC_LMM_PLMN_SRCH_RLT_GET_GEO_FAIL     == enPlmnSrchRslt)
             || (MMC_LMM_PLMN_SRCH_RLT_GET_GEO_SUCC     == enPlmnSrchRslt)
             || (MMC_LMM_PLMN_SRCH_RLT_GET_GEO_NO_RF    == enPlmnSrchRslt))
            {
                return VOS_TRUE;
            }
            break;

        default:

            break;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MML_IsPrefBandPlmnSrchRslt
 功能描述  : 搜网回复是否为pref band结果
 输入参数  : VOS_UINT32     enPlmnSrchRslt
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月12日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_IsPrefBandPlmnSrchRslt(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT32                          enPlmnSrchRslt
)
{
    switch(enRat)
    {
        /* GU下时这些搜网结果是pref band结果 */
        case NAS_MML_NET_RAT_TYPE_GSM:
        case NAS_MML_NET_RAT_TYPE_WCDMA:

            if ((RRC_PLMN_SEARCH_RLT_PREF_BAND_SUCC   == enPlmnSrchRslt)
             || (RRC_PLMN_SEARCH_RLT_PREF_BAND_FAIL   == enPlmnSrchRslt)
             || (RRC_PLMN_SEARCH_RLT_PREF_BAND_NO_RF  == enPlmnSrchRslt))
            {
                return VOS_TRUE;
            }
            break;

        /* LTE时这些搜网结果是pref band结果 */
        case NAS_MML_NET_RAT_TYPE_LTE:

            if ((MMC_LMM_PLMN_SRCH_RLT_PREF_BAND_FAIL     == enPlmnSrchRslt)
             || (MMC_LMM_PLMN_SRCH_RLT_PREF_BAND_SUCC     == enPlmnSrchRslt)
             || (MMC_LMM_PLMN_SRCH_RLT_PREF_BAND_NO_RF    == enPlmnSrchRslt))
            {
                return VOS_TRUE;
            }
            break;

        default:

            break;
    }

    return VOS_FALSE;
}


/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-28, begin */
/*****************************************************************************
 函 数 名  : NAS_MML_IsCampInfoChanged
 功能描述  : 收到系统信息后，判断驻留的LAI消息是否发生改变
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE :驻留LAI信息与上次相比发生变化
             VOS_FALSE:驻留LAI信息与上次相比发生变化
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月28日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_IsCampLaiInfoChanged( VOS_VOID )
{
    NAS_MML_LAI_STRU                   *pstOldLai = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                   *pstCurLai = VOS_NULL_PTR;

    pstOldLai   = NAS_MML_GetOldCampLai();
    pstCurLai   = NAS_MML_GetCurrCampLai();

    if ((pstOldLai->stPlmnId.ulMcc != pstCurLai->stPlmnId.ulMcc)
     || (pstOldLai->stPlmnId.ulMnc != pstCurLai->stPlmnId.ulMnc)
     || (pstOldLai->aucLac[0]      != pstCurLai->aucLac[0])
     || (pstOldLai->aucLac[1]      != pstCurLai->aucLac[1]))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-28, end */



/*****************************************************************************
 函 数 名  : NAS_MML_IsRoamingRejectNoRetryFlgActived
 功能描述  : 判断是否打开了reject #17的定制
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年4月29日
   作    者   : l00208543
   修改内容   : 新增函数

*****************************************************************************/
VOS_UINT8 NAS_MML_IsRoamingRejectNoRetryFlgActived(VOS_UINT8 ucCause)
 {
    NAS_MML_PLMN_ID_STRU                                   *pstCurplmn    = VOS_NULL_PTR;
    VOS_UINT32                                              ulIsRoam;
    NAS_MML_ROAMINGREJECT_NORETYR_CFG_STRU                 *pstNoRetryCfg = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    i               = 0;
    pstCurplmn      = NAS_MML_GetCurrCampPlmnId();
    ulIsRoam        = NAS_MMC_IsRoam();
    pstNoRetryCfg   = NAS_MML_GetRoamingRejectNoRetryCfg();

    /*
    满足如下条件的时候收到reject 17不重试
    1. 不是测试卡；
    2. 定制nv打开,拒绝原因值在nv配置中；
    3. 漫游状态且当前PLMN不是UPLMN也不是OPLMN；
    */

    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return VOS_FALSE;
    }

    if (VOS_FALSE == ulIsRoam)
    {
        return VOS_FALSE;
    }

    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithUplmn(pstCurplmn))
    {
        return VOS_FALSE;
    }

    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithOplmn(pstCurplmn))
    {
        return VOS_FALSE;
    }

    if (0 == pstNoRetryCfg->ucNoRetryRejectCauseNum)
    {
        return VOS_FALSE;
    }

    for (i=0; i<pstNoRetryCfg->ucNoRetryRejectCauseNum; i++)
    {
        if (ucCause == pstNoRetryCfg->aucNoRetryRejectCause[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MML_IsUeSupportIms
 功能描述  : UE是否支持IMS，包括LTE下的IMS是否支持和IMS的业务能力
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:支持 VOS_FALSE:不支持
 调用函数  :
 被调函数  :

 修改历史      :
  2.日    期   : 2015年2月11日
    作    者   : s00217060
    修改内容   : VOLTE SWITCH新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_IsUeSupportIms(VOS_VOID)
{
    VOS_UINT8                           ucVoiceOnIms;
    VOS_UINT8                           ucSmsOnIms;
    VOS_UINT8                           ucVideoOnIms;
    VOS_UINT8                           ucUssdOnIms;


    /* 总控开关未打开时，认为UE不支持IMS */
    if (VOS_FALSE == NAS_MML_GetLteImsSupportFlg())
    {
        return VOS_FALSE;
    }

    /* 任意一项业务能力支持时，认为UE支持IMS */
    ucVoiceOnIms    = NAS_MML_GetVoiceCallOnImsSupportFlag();
    ucSmsOnIms      = NAS_MML_GetSmsOnImsSupportFlag();
    ucVideoOnIms    = NAS_MML_GetVideoCallOnImsSupportFlag();
    ucUssdOnIms     = NAS_MML_GetUssdOnImsSupportFlag();

    if ( (VOS_TRUE == ucVoiceOnIms)
      || (VOS_TRUE == ucSmsOnIms)
      || (VOS_TRUE == ucVideoOnIms)
      || (VOS_TRUE == ucUssdOnIms) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetMoCallSetupFlg
 功能描述  : 获取主叫建立标志
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月25日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetMoCallSetupFlg(VOS_VOID)
{
    NAS_MML_MO_CALL_STATUS_ENUM_UINT8   enCallStatus;
    VOS_UINT8                           ucRslt;

    enCallStatus    = NAS_MML_GetMoCallStatus();

    switch(enCallStatus)
    {
        case NAS_MML_CSFB_MO_NORMAL_CALL_SETUP_START:
        case NAS_MML_CSFB_MO_EMC_CALL_SETUP_START:
        case NAS_MML_MO_NORMAL_CALL_SETUP_START:
        case NAS_MML_MO_EMC_CALL_SETUP_START:

            ucRslt  = VOS_TRUE;
            break;

        default:

            ucRslt  = VOS_FALSE;
            break;
    }

    return ucRslt;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetMoSsSetupFlg
 功能描述  : 获取主叫SS业务建立标志
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月25日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetMoSsSetupFlg(VOS_VOID)
{
    NAS_MML_MO_SS_STATUS_ENUM_UINT8     enSsStatus;
    VOS_UINT8                           ucRslt;

    enSsStatus      = NAS_MML_GetMoSsStatus();

    switch(enSsStatus)
    {
        case NAS_MML_CSFB_MO_SS_SETUP_START:
        case NAS_MML_MO_NORMAL_SS_SETUP_START:

            ucRslt  = VOS_TRUE;
            break;

        default:
            ucRslt  = VOS_FALSE;
            break;

    }

    return ucRslt;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetCmServiceSetupFlg
 功能描述  : 获取业务建立标志
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月18日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetCmServiceSetupFlg( VOS_VOID )
{

    /* MO呼叫业务标志 */
    if (VOS_TRUE == NAS_MML_GetMoCallSetupFlg())
    {
        return VOS_TRUE;
    }

    /* MO SS业务标志 */
    if (VOS_TRUE == NAS_MML_GetMoSsSetupFlg())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MML_Is3Gpp2Rat
 功能描述  : 判断当前接入技术是否是3GPP2接入技术
 输入参数  : 指定的接入技术
 输出参数  : 无
 返 回 值  : VOS_TRUE:是
             VOS_FALSE:不是
 调用函数  :
 被调函数  :

 修改历史      :
    1.日    期   : 2015年5月6日
      作    者   : h00246512
      修改内容   : 新增函数
*****************************************************************************/
VOS_UINT32 NAS_MML_Is3Gpp2Rat(
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8            enRatType
)
{
    if ((NAS_MSCC_PIF_NET_RAT_TYPE_1X == enRatType)
      ||(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD == enRatType))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MML_IsImsiInLteOos2GPrefPlmnSelCfg
 功能描述  : 判断当前的SIM卡是否在LTE OOS选网优化配置中
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_TRUE  : IMSI在LTE OOS选网优化配置中
             VOS_FALSE : IMSI不在LTE OOS选网优化配置中
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年07月03日
   作    者   : h00285180
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsImsiInLteOos2GPrefPlmnSelCfg(VOS_VOID)
{
    VOS_UINT32                                              i;
    NAS_MML_PLMN_ID_STRU                                    stHplmnId;
    NAS_MML_PLMN_ID_STRU                                    stPlmnId;
    NAS_MML_LTE_OOS_2G_PREF_PLMN_SEL_CFG_STRU              *pstLteOosPlmnSelCfg = VOS_NULL_PTR;
    VOS_UINT8                                              *pucImsi             = VOS_NULL_PTR;

    i                   = 0;
    pstLteOosPlmnSelCfg = NAS_MML_GetLteOos2GPrefPlmnSelCfg();

    PS_MEM_SET(&stHplmnId,0x00, sizeof(stHplmnId));
    PS_MEM_SET(&stPlmnId, 0x00, sizeof(stPlmnId));

    if ( VOS_FALSE == NAS_MML_GetSimPresentStatus() )
    {
        return VOS_FALSE;
    }

    /* 增加测试卡保护，测试卡时不修改，直接返回 */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return VOS_FALSE;
    }

    /* 取得本地维护的IMSI的地址 */
    pucImsi   = NAS_MML_GetSimImsi();

    /* 从当前的IMSI中取出home plmn */
    stHplmnId = NAS_MML_GetImsiHomePlmn(pucImsi);

    /* 判断IMSI是否在LTE OOS选网优化配置列表中 */
    for (i = 0; i < pstLteOosPlmnSelCfg->ucImsiListNum; i++)
    {
        stPlmnId.ulMcc = pstLteOosPlmnSelCfg->astImsiList[i].ulMcc;
        stPlmnId.ulMnc = pstLteOosPlmnSelCfg->astImsiList[i].ulMnc;

        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&stPlmnId, &stHplmnId))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MML_IsNeedSortRatPrioForLteOos2GPrefPlmnSel
 功能描述  : 是否需要对接入技术优先顺序进行排序
 输入参数  : 无
 输出参数  : pstPrioRatList,接入技术优先顺序
 返 回 值  : VOS_TRUE  - 需要排序
             VOS_FALSE - 不需要排序
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年7月03日
   作    者   : h00285180
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_IsNeedSortRatPrioForLteOos2GPrefPlmnSel(
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList
)
{
    if ( (VOS_TRUE                      == NAS_MML_IsImsiInLteOos2GPrefPlmnSelCfg())
      && (NAS_MML_MAX_RAT_NUM           == pstPrioRatList->ucRatNum)
      && (NAS_MML_NET_RAT_TYPE_LTE      == pstPrioRatList->aucRatPrio[0])
      && (NAS_MML_NET_RAT_TYPE_WCDMA    == pstPrioRatList->aucRatPrio[1])
      && (NAS_MML_NET_RAT_TYPE_GSM      == pstPrioRatList->aucRatPrio[2]))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MML_IsLastCampedPlmnIdRoam
 功能描述  : 获取最后驻留PLMN是否处于漫游状态
 输出参数  : 无
 返 回 值  : VOS_BOOL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 20105年7月3日
    作    者   : h00285180
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_IsLastCampedPlmnIdRoam(VOS_VOID)
{
    NAS_MML_PLMN_ID_STRU               *pstLastCampedPlmn = VOS_NULL_PTR;

    pstLastCampedPlmn = NAS_MMC_GetLastCampedPlmnid();

    /* 与HPLMN相同 */
    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(pstLastCampedPlmn))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
#endif

/*****************************************************************************
 函 数 名  :NAS_MML_IsGULModeConfigured
 功能描述  :判断当前是否为GUL模式
 输入参数  :VOS_VOID
 输出参数  :无
 返 回 值  :VOS_TRUE  - 当前为GUL模式
            VOS_FALSE - 当前为CL模式
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年5月29日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_IsGULModeConfigured(VOS_VOID)
{
    /* syscfg set not support HRPD and 1X, we consider it's GUL mode */
    VOS_UINT32                          ulSupport1x;
    VOS_UINT32                          ulSupportHrpd;

    ulSupport1x   = NAS_MML_IsSpec3Gpp2RatInRatList(NAS_MML_3GPP2_RAT_TYPE_CDMA1X, NAS_MML_GetMs3Gpp2PrioRatList());
    ulSupportHrpd = NAS_MML_IsSpec3Gpp2RatInRatList(NAS_MML_3GPP2_RAT_TYPE_HRPD, NAS_MML_GetMs3Gpp2PrioRatList());

    if ((VOS_FALSE == ulSupportHrpd)
     && (VOS_FALSE == ulSupport1x))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MML_IsCLModeSupportedInRatList
 功能描述  : 判断目标接入技术是否支持CL模式
 输入参数  : NAS_MSCC_PIF_RAT_PRIO_STRU         *pstRatPrioList
 输出参数  : 无
 返 回 值  : VOS_UINT32
             VOS_TRUE  表示支持
             VOS_FASLE 表示不支持
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月21日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_IsCLModeSupportedInRatList(
    NAS_MSCC_PIF_RAT_PRIO_STRU         *pstRatPrioList
)
{
    VOS_UINT32                          i;

    for ( i = 0 ; i < (VOS_UINT32)pstRatPrioList->ucRatNum; i++ )
    {
        if ( (NAS_MSCC_PIF_NET_RAT_TYPE_1X == pstRatPrioList->aucRatPrio[i])
          || (NAS_MSCC_PIF_NET_RAT_TYPE_HRPD == pstRatPrioList->aucRatPrio[i]) )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetNewRatFromRatList
 功能描述  : 从接入技术列表中获取新的接入技术
 输入参数  : *pstOriRatList:    原先的接入技术列表地址
             *pstNewRatList:    现在的接入技术列表地址
 输出参数  : *pstOutputRatList  输出的接入技术列表
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015-09-06
   作    者   : wx270776
   修改内容   : 新生成函数

****************************************************************************/
VOS_VOID NAS_MML_GetNewRatFromRatList(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstOriRatList,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstNewRatList,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstOutputRatList
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulNum;
    VOS_UINT32                          ulResult;

    /* 初始化 */
    ulNum    = pstNewRatList->ucRatNum;
    ulResult = VOS_FALSE;

    PS_MEM_SET(pstOutputRatList, 0x00, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    for (i = 0; i < ulNum; i++)
    {
        /* 判断指定的接入技术是否在接入技术列表中 */
        ulResult = NAS_MML_IsSpecRatInRatList( pstNewRatList->aucRatPrio[i],
                                               pstOriRatList );

        if (VOS_FALSE == ulResult)
        {
            pstOutputRatList->aucRatPrio[pstOutputRatList->ucRatNum] = pstNewRatList->aucRatPrio[i];
           (pstOutputRatList->ucRatNum)++;
        }
    }
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetCsfbMoCallSetupFlg
 功能描述  : 获取CSFB主叫建立标志
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月16日
    作    者   : j00174725
    修改内容   : DTS2015101603066
*****************************************************************************/
VOS_UINT8 NAS_MML_GetCsfbMoCallSetupFlg(VOS_VOID)
{
    NAS_MML_MO_CALL_STATUS_ENUM_UINT8   enCallStatus;
    VOS_UINT8                           ucRslt;

    enCallStatus    = NAS_MML_GetMoCallStatus();

    switch (enCallStatus)
    {
        case NAS_MML_CSFB_MO_NORMAL_CALL_SETUP_START:
        case NAS_MML_CSFB_MO_EMC_CALL_SETUP_START:

            ucRslt  = VOS_TRUE;
            break;

        default:

            ucRslt  = VOS_FALSE;
            break;
    }

    return ucRslt;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetCsfbMoSsSetupFlg
 功能描述  : 获取CSFB 补充业务建立标志
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :
 修改历史      :

 1.日    期   : 2015年10月16日
    作    者   : j00174725
    修改内容   : DTS2015101603066
*****************************************************************************/
VOS_UINT8 NAS_MML_GetCsfbMoSsSetupFlg(VOS_VOID)
{
    NAS_MML_MO_CALL_STATUS_ENUM_UINT8   enCallStatus;
    VOS_UINT8                           ucRslt;

    enCallStatus    = NAS_MML_GetMoSsStatus();

    switch (enCallStatus)
    {
        case NAS_MML_CSFB_MO_SS_SETUP_START:

            ucRslt  = VOS_TRUE;
            break;

        default:

            ucRslt  = VOS_FALSE;
            break;
    }

    return ucRslt;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetCsfbMtPagingTimerStatus
 功能描述  : 设置CSFB 被叫保护定时器状态
 输入参数  : enStatus
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月16日
    作    者   : j00174725
    修改内容   : DTS2015101603066
*****************************************************************************/
VOS_VOID NAS_MML_SetCsfbMtPagingTimerStatus(
    NAS_MML_MT_CSFB_PAGING_TIMER_STATUS_ENUM_UINT8  enStatus
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stCmSrvStatus.enMtCsfbPagingTimerStatus = enStatus;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetCsfbMtPagingTimerStatus
 功能描述  : 获取CSFB 被叫保护定时器状态
 输入参数  : enStatus
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月16日
    作    者   : j00174725
    修改内容   : DTS2015101603066
*****************************************************************************/
NAS_MML_MT_CSFB_PAGING_TIMER_STATUS_ENUM_UINT8 NAS_MML_GetCsfbMtPagingTimerStatus(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stCmSrvStatus.enMtCsfbPagingTimerStatus);
}

/*****************************************************************************
函 数 名  : NAS_MML_IsPidUnderGunas
功能描述  : 判断PID是否属于GUNAS组件
输入参数  : 无
输出参数  : 无
返 回 值  :
调用函数  :
被调函数  :

修改历史  :
1.日    期  : 2015年12月02日
  作    者  : z00359541
  修改内容  : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsPidUnderGunas(
    VOS_UINT32                          ulPid
)
{
    if ((ulPid == WUEPS_PID_MMC)
     || (ulPid == WUEPS_PID_MM)
     || (ulPid == WUEPS_PID_GMM)
     || (ulPid == WUEPS_PID_MMA))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
函 数 名  : NAS_MML_IsNeedDiscardMsg
功能描述  : 判断消息是否在忽略列表中
输入参数  : 无
输出参数  : 无
返 回 值  :
调用函数  :
被调函数  :

修改历史  :
1.日    期  : 2015年11月30日
  作    者  : z00359541
  修改内容  : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsNeedDiscardMsg(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulReceiverPid,
    VOS_UINT32                          ulMsgName
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulRslt;

    ulRslt = NAS_MML_IsPidUnderGunas(ulReceiverPid);

    /* 发送方和接收方都不是GUNAS PID则丢弃 */
    if ((VOS_FALSE == NAS_MML_IsPidUnderGunas(ulSenderPid))
      &&(VOS_FALSE == ulRslt))
    {
        return VOS_TRUE;
    }

    /* 丢弃在忽略列表中的消息 */
    for (i = 0; i < (sizeof(g_stNasMmlDiscardMsgTbl)/sizeof(NAS_MML_DISCARD_MSG_STRU)); i++)
    {
        if ((ulSenderPid                == g_stNasMmlDiscardMsgTbl[i].ulSenderPid)
         && (ulReceiverPid              == g_stNasMmlDiscardMsgTbl[i].ulReceiverPid)
         && (ulMsgName                  == g_stNasMmlDiscardMsgTbl[i].ulMsgName))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  :IsCurrRatGUMode
 功能描述  :判断当前模是否GU模
 输入参数  :
 输出参数  :
 返 回 值  : VOS_TRUE: 是
             VOS_FALSE；不是
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年10月12日
   作    者   : z00359541
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsCurrGURatMode(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enCurrRat;

    enCurrRat = NAS_MML_GetCurrNetRatType();

    if ((NAS_MML_NET_RAT_TYPE_WCDMA == enCurrRat)
     || (NAS_MML_NET_RAT_TYPE_GSM == enCurrRat))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  :NAS_MML_IsNeedTriggerPLMNSearch
 功能描述  :判断删除LAI后是否需要立即触发搜网
 输入参数  :
 输出参数  :
 返 回 值  : VOS_TRUE: 需要立即触发搜网
             VOS_FALSE；不需要立即触发搜网
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年10月12日
   作    者   : z00359541
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsNeedTriggerPlmnSearchWhenRemoveCustomizedFrobLa(VOS_VOID)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCampPlmnInfo            = VOS_NULL_PTR;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                       *pstForbidPlmnInfo          = VOS_NULL_PTR;
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU            *pstForbLaWithValidPeriod   = VOS_NULL_PTR;
    VOS_UINT32                                              ulRlstLaiInForbidRegLaiList;
    VOS_UINT32                                              i;

    pstForbLaWithValidPeriod            = NAS_MML_GetForbLaWithValidPeriodList();

    /* 获取当前驻留PLMN信息 */
    pstCampPlmnInfo                     = NAS_MML_GetCurrCampPlmnInfo();

    /* 获取FPLMN信息*/
    pstForbidPlmnInfo                   = NAS_MML_GetForbidPlmnInfo();

    ulRlstLaiInForbidRegLaiList         = NAS_MML_IsLaiInDestLaiList(&(pstCampPlmnInfo->stLai),
        pstForbidPlmnInfo->ucForbRegLaNum, pstForbidPlmnInfo->astForbRegLaList);

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_IsNeedTriggerPlmnSearchWhenRemoveCustomizedFrobLa");

    /* 驻留PLMN在禁止FPLMN列表中 */
    if (VOS_TRUE == NAS_MML_IsPlmnIdInForbidPlmnList(&(pstCampPlmnInfo->stLai.stPlmnId)))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_IsNeedTriggerPlmnSearchWhenRemoveCustomizedFrobLa: Cur PLMN in FPLMN, No need search");
        return VOS_FALSE;
    }

    /* 驻留的LAI在禁止LAI列表中 */
    if ((VOS_TRUE == NAS_MML_IsLaiInDestLaiList(&(pstCampPlmnInfo->stLai),
            pstForbidPlmnInfo->ucForbRoamLaNum, pstForbidPlmnInfo->astForbRomLaList)) ||
        (VOS_TRUE == ulRlstLaiInForbidRegLaiList))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_IsNeedTriggerPlmnSearchWhenRemoveCustomizedFrobLa: Cur LA in Forb LA, No need search");
        return VOS_FALSE;
    }

    /* 判断超时的LAI是否是当前驻留的LAI */
    for (i = 0; i < pstForbLaWithValidPeriod->ulForbLaWithValidPeriodNum; i++)
    {
        if (0 == NAS_MMC_GetCustomizedForbLaLeftTimeLen(&(pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i])))
        {
            if(VOS_TRUE == NAS_MML_CompareLai(&(pstCampPlmnInfo->stLai),
                &(pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].stForbLaWithValidPeriodLai)))
            {
                NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_IsNeedTriggerPlmnSearchWhenRemoveCustomizedFrobLa: Cur LA will remove from Customized Forb LA, need search");
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
 }

/*****************************************************************************
 函 数 名  :NAS_MML_StartCustomizedForbLaTimer
 功能描述  :启动删除定制禁止LA列表定时器
 输入参数  :pstForbLaWithValidPeriod
 输出参数  :
 返 回 值  : VOS_TRUE: 定时器启动
             VOS_FALSE；定时器未启动
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年9月23日
   作    者   : z00359541
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_StartCustomizedForbLaTimer(VOS_VOID)
{
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU            *pstForbLaWithValidPeriod = VOS_NULL_PTR;
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulLeftTimeLen;
    VOS_UINT32                                              ulTmpTimeLen;

    pstForbLaWithValidPeriod            = NAS_MML_GetForbLaWithValidPeriodList();
    ulLeftTimeLen                       = NAS_MML_MAX_TIME_TICK;

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_StartCustomizedForbLaTimer");

    /* 禁止LA列表为空，不处理 */
    if (0 == pstForbLaWithValidPeriod->ulForbLaWithValidPeriodNum)
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_StartCustomizedForbLaTimer: Customized Forb LA is empty");
        return;
    }

    (VOS_VOID)NAS_MMC_StopTimer(TI_NAS_MMC_CUSTOMIZED_FORB_LA_TIMER);

    /* 获取当前列表中最短的剩余时长 */
    for ( i = 0; i < pstForbLaWithValidPeriod->ulForbLaWithValidPeriodNum; i++ )
    {
        ulTmpTimeLen = NAS_MMC_GetCustomizedForbLaLeftTimeLen(&(pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i]));

        if (0 == ulTmpTimeLen)
        {
            continue;
        }

        ulLeftTimeLen = NAS_MML_MIN(ulLeftTimeLen, ulTmpTimeLen);
    }

    NAS_NORMAL_LOG2(WUEPS_PID_MMC, "NAS_MML_StartCustomizedForbLaTimer: Get the Customized Forb LA num and next expire timer len: ",
        pstForbLaWithValidPeriod->ulForbLaWithValidPeriodNum, ulLeftTimeLen);

    if (NAS_MML_MAX_TIME_TICK != ulLeftTimeLen)
    {
        /* 启动定时器 */
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_StartCustomizedForbLaTimer: Start FORB LA timer");
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_CUSTOMIZED_FORB_LA_TIMER,
                            (((ulLeftTimeLen)*NAS_MML_ONE_THOUSAND_MILLISECOND)/NAS_MML_SECOND_TO_TICK));
    }

    return;
}

/*****************************************************************************
 函 数 名  :NAS_MML_GetForbLaWithValidPeriodTimerLen
 功能描述  :获取对应失败原因值的惩罚时长
 输入参数  :NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16          enRegFailCause,
            NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_LIST_STRU   *pstForbLaWithValidPeriodCfg
 输出参数  :
 返 回 值  :对应此原因值的惩罚时间
 调用函数  :
 被调函数  :
 修改历史      :
1.日    期   : 2015年9月23日
   作    者   : z00359541
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT16 NAS_MML_GetForbLaWithValidPeriodTimerLen(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enRegFailCause,
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_LIST_STRU   *pstForbLaWithValidPeriodCfg
)
{
    VOS_UINT32                                              i;



    for (i = 0; i < pstForbLaWithValidPeriodCfg->ulSupportForbLaWithValidPeriodNum; i++)
    {
        if (pstForbLaWithValidPeriodCfg->astForbLaWithValidPeriodCfgList[i].usRegFailCause == enRegFailCause)
        {
            NAS_NORMAL_LOG1(WUEPS_PID_MMC, "NAS_MML_GetForbLaWithValidPeriodTimerLen: ", pstForbLaWithValidPeriodCfg->astForbLaWithValidPeriodCfgList[i].usForbLaValidPeriodLen);

            return pstForbLaWithValidPeriodCfg->astForbLaWithValidPeriodCfgList[i].usForbLaValidPeriodLen;
        }
    }

    /* 没有找到对应匹配时长，设置为0 */
    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_GetForbLaWithValidPeriodTimerLen: 0");

    return 0;
}

/*****************************************************************************
 函 数 名  :NAS_MML_GetCustomizedForbLaPunishTimeLen
 功能描述  :获取对应失败原因值防乒乓机制的惩罚时长
 输入参数  :NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16          enRegFailCause,
            NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_LIST_STRU   *pstForbLaWithValidPeriodCfg
 输出参数  :
 返 回 值  :对应此原因值的防乒乓机制的惩罚时长
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年9月23日
   作    者   : z00359541
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT16 NAS_MML_GetCustomizedForbLaPunishTimeLen(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enRegFailCause,
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_LIST_STRU   *pstForbLaWithValidPeriodCfg
)
{
    VOS_UINT32                                              i;



    for (i = 0; i < pstForbLaWithValidPeriodCfg->ulSupportForbLaWithValidPeriodNum; i++)
    {
        if (pstForbLaWithValidPeriodCfg->astForbLaWithValidPeriodCfgList[i].usRegFailCause == enRegFailCause)
        {
            NAS_NORMAL_LOG1(WUEPS_PID_MMC, "NAS_MML_GetCustomizedForbLaPunishTimeLen: ", pstForbLaWithValidPeriodCfg->astForbLaWithValidPeriodCfgList[i].usPunishTimeLen);

            return pstForbLaWithValidPeriodCfg->astForbLaWithValidPeriodCfgList[i].usPunishTimeLen;
        }
    }

    /* 没有找到对应匹配时长，设置为0 */
    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_GetCustomizedForbLaPunishTimeLen: 0");
    return 0;
}

/*****************************************************************************
 函 数 名  : NAS_MML_IsCustomizedForbLaTimerExpired
 功能描述  : 判断定时器是否已经超时，精度设定为1秒
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32

 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年11月7日
   作    者   : z00359541
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsCustomizedForbLaTimerExpired(
    VOS_UINT32                                              ulDuration,
    VOS_UINT32                                              ulPeriod
)
{
    if ((ulDuration >= ulPeriod)
     || ((ulDuration + NAS_MML_CUSTOMIZED_FORB_LA_TIMER_PRECISION) >= ulPeriod))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetCustomizedForbLaLeftTimeLen
 功能描述  : 获取禁止LA的剩余时长
 输入参数  : pstLaiWithValidPeriod - 禁止LA有效时长列表中的元素
 输出参数  : 无
 返 回 值  : VOS_UINT32

 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年9月23日
   作    者   : z00359541
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetCustomizedForbLaLeftTimeLen(
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_STRU                 *pstLaWithValidPeriod
)
{
    VOS_UINT32                                              ulCurrTimeTick;
    VOS_UINT32                                              ulDuration;
    VOS_UINT32                                              ulPunishDuration;
    VOS_UINT32                                              ulLeftTimeLen;
    VOS_UINT32                                              ulPunishLeftTimeLen;

    ulCurrTimeTick = VOS_GetTick();

    NAS_NORMAL_LOG3(WUEPS_PID_MMC,
        "NAS_MMC_GetCustomizedForbLaLeftTimeLen: Current Tick and Forb La BeginTick, Period",
        ulCurrTimeTick,
        pstLaWithValidPeriod->ulForbLaWithValidPeriodBeginTick,
        pstLaWithValidPeriod->ulForbLaWithValidPeriodTick
        );

    /* 如果LAI 是nv配置的禁止期限为全F，则返回VOS_FALSE无需动态删除 */
    if (NAS_MML_MAX_TIME_TICK == pstLaWithValidPeriod->ulForbLaWithValidPeriodTick)
    {
        return NAS_MML_MAX_TIME_TICK;
    }

    ulDuration = ulCurrTimeTick - pstLaWithValidPeriod->ulForbLaWithValidPeriodBeginTick;

    ulPunishDuration = ulCurrTimeTick - pstLaWithValidPeriod->ulForbLaWithValidPeriodPunishBeginTick;

    /* 定时器精度为1秒，离到期1秒内都算超时 */
    if (VOS_TRUE == NAS_MML_IsCustomizedForbLaTimerExpired(ulDuration, pstLaWithValidPeriod->ulForbLaWithValidPeriodTick))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCustomizedForbLaLeftTimeLen: Customized Forb LA timer expired");
        ulLeftTimeLen = 0;
    }
    else
    {
        /* 计算当前剩余禁止有效时长 */
        ulLeftTimeLen = pstLaWithValidPeriod->ulForbLaWithValidPeriodTick - ulDuration;
    }

    /* 防乒乓惩罚时间已过 */
    if (VOS_TRUE == NAS_MML_IsCustomizedForbLaTimerExpired(ulPunishDuration,
        pstLaWithValidPeriod->ulForbLaWithValidPeriodPunishDurationTick))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCustomizedForbLaLeftTimeLen: Customized Forb LA punish timer expired");
        ulPunishLeftTimeLen = 0;
    }
    else
    {
        /* 计算当前惩罚剩余时长 */
        ulPunishLeftTimeLen =  pstLaWithValidPeriod->ulForbLaWithValidPeriodPunishDurationTick - ulPunishDuration;
    }

    /* 取两者剩余时长中的最小值为返回值 */
    return NAS_MML_MIN(ulLeftTimeLen, ulPunishLeftTimeLen);

}

/*****************************************************************************
 函 数 名  : NAS_MML_CompareLac
 功能描述  : 判断LAC是否相同
 输入参数  : pstCurLai
             pstOldLai
 输出参数  : 无
 返 回 值  : VOS_TRUE: 相同
             VOS_FALSE: 不同
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年9月23日
   作    者   : z00359541
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_CompareLac(
    NAS_MML_LAI_STRU                                       *pstCurLai,
    NAS_MML_LAI_STRU                                       *pstOldLai
)
{
    VOS_UINT32                         i;

    for ( i = 0 ; i < NAS_MML_MAX_LAC_LEN ; i++ )
    {
        if (pstCurLai->aucLac[i] != pstOldLai->aucLac[i])
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MML_DeleteLaFromForbLaWithValidPeriodList
 功能描述  : 从禁止LA列表中删除指定索引的LA
 输入参数  : pstForbLaWithValidPeriod
 输出参数  : pstForbLaWithValidPeriod
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年9月23日
   作    者   : z00359541
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_DeleteLaFromForbLaWithValidPeriodList(
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU            *pstForbLaWithValidPeriod,
    VOS_UINT32                                              ulIndex
)
{

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_DeleteLaFromForbLaWithValidPeriodList");

    /* 删除指定的LAI */
    if (ulIndex < (pstForbLaWithValidPeriod->ulForbLaWithValidPeriodNum - 1))
    {
        (VOS_VOID)PS_MEM_MOVE(&(pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[ulIndex]),
                     &(pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[ulIndex + 1]),
                     ((pstForbLaWithValidPeriod->ulForbLaWithValidPeriodNum- ulIndex) - 1) * sizeof(NAS_MML_FORB_LA_WITH_VALID_PERIOD_STRU));
    }

    /* 删除LA后, 更新个数 */
    pstForbLaWithValidPeriod->ulForbLaWithValidPeriodNum--;

    /* 可维可测打印 */
    NAS_MMC_LogForbLaWithValidPeriodListInfo();

}

/*****************************************************************************
 函 数 名  : NAS_MML_IsNeedProtectionBeforeDeleteCustomizedForbLa
 功能描述  : 判断是否需要启动防兵乓机制
 输入参数  : pstForbLaWithValidPeriod
 输出参数  : pstForbLaWithValidPeriod
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年9月23日
   作    者   : z00359541
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsNeedProtectionBeforeDeleteCustomizedForbLa(
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU            *pstForbLaWithValidPeriod,
    VOS_UINT32                                              ulIndex
)
{
    NAS_MML_LAI_STRU                                       *pstCurrCampLai      = VOS_NULL_PTR;
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_STRU                 *pstCustomizedForbLa = VOS_NULL_PTR;
    VOS_UINT32                                              ulMatchEplmnFlg;
    VOS_UINT32                                              ulPunishTimeDuration;
    VOS_UINT32                                              ulCsServiceFlg;

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_IsNeedProtectionBeforeDeleteCustomizedForbLa");

    pstCurrCampLai                      = NAS_MML_GetCurrCampLai();
    pstCustomizedForbLa                 = &(pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[ulIndex]);
    ulMatchEplmnFlg                     = NAS_MML_IsPlmnInEplmnList(&(pstCustomizedForbLa->stForbLaWithValidPeriodLai.stPlmnId));
    ulPunishTimeDuration                = VOS_GetTick() - pstCustomizedForbLa->ulForbLaWithValidPeriodPunishBeginTick;
    ulCsServiceFlg                      = NAS_MMC_IsCsNormalService();

    NAS_NORMAL_LOG2(WUEPS_PID_MMC, "NAS_MML_IsNeedProtectionBeforeDeleteCustomizedForbLa: ulCsServiceFlg and ulMatchEplmnFlg",
        ulCsServiceFlg, ulMatchEplmnFlg);

    /* 防兵乓机制，惩罚时长精度为1秒 */
    if ( (VOS_TRUE == ulCsServiceFlg)
      && (VOS_TRUE == ulMatchEplmnFlg)
      && ((ulPunishTimeDuration + NAS_MML_CUSTOMIZED_FORB_LA_TIMER_PRECISION) < pstCustomizedForbLa->ulForbLaWithValidPeriodPunishDurationTick) )
    {
        /* 比较当前驻留PLMN与要删除的PLMN是否相同 */
        if (VOS_FALSE == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstCurrCampLai->stPlmnId),
                            &(pstCustomizedForbLa->stForbLaWithValidPeriodLai.stPlmnId)))
        {
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_IsNeedProtectionBeforeDeleteCustomizedForbLa(): In EPLMN list, Start Protection");
            return VOS_TRUE;
        }

        /* 比较当前驻留的LAC与要删除的LAC是否相同 */
        if (VOS_FALSE == NAS_MML_CompareLac(pstCurrCampLai,
                            &(pstCustomizedForbLa->stForbLaWithValidPeriodLai)))
        {
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_IsNeedProtectionBeforeDeleteCustomizedForbLa(): Same PLMN, Diff LA, Start Protection");
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MML_DeleteExpiredLaFromForbLaWithValidPeriodList
 功能描述  : 当定时器超时或注册成功时从禁止LA列表中删除指定LA的处理
 输入参数  : pstForbLaWithValidPeriod
 输出参数  : pstForbLaWithValidPeriod
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年9月23日
   作    者   : z00359541
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_DeleteExpiredLaFromForbLaWithValidPeriodList(
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU            *pstForbLaWithValidPeriod
)
{
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_LIST_STRU   *pstForbLaWithValidPeriodCfg = VOS_NULL_PTR;
    VOS_UINT16                                              usTimeLen;
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulDeleteFlg;

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_DeleteExpiredLaFromForbLaWithValidPeriodList");

    ulDeleteFlg                         = VOS_FALSE;    
    pstForbLaWithValidPeriodCfg         = NAS_MML_GetForbLaWithValidPeriodCfg();

    /* 判断是列表中哪一个LA超时 */
    for (i = 0; i < pstForbLaWithValidPeriod->ulForbLaWithValidPeriodNum; i++)
    {
        usTimeLen = NAS_MML_GetForbLaWithValidPeriodTimerLen(pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].enCsRegFailCause,
                                                pstForbLaWithValidPeriodCfg);
        if (0 == NAS_MMC_GetCustomizedForbLaLeftTimeLen(&(pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i])))
        {
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_DeleteExpiredLaFromForbLaWithValidPeriodList: Got expired LA");

            /* 防兵乓机制是否需要启动 */
            if (VOS_TRUE == NAS_MML_IsNeedProtectionBeforeDeleteCustomizedForbLa(pstForbLaWithValidPeriod, i))
            {
                /* 更新禁止LA信息 */
                pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].ulForbLaWithValidPeriodTick                    = NAS_MML_SECOND_TO_TICK * usTimeLen;
                pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].ulForbLaWithValidPeriodBeginTick               = VOS_GetTick();
                NAS_NORMAL_LOG4(WUEPS_PID_MMC,
                    "NAS_MML_DeleteExpiredLaFromForbLaWithValidPeriodList: Ping-Pang protection started, update Forb La info(BeginTick, Period, PunishBeginTick)",
                    i,
                    pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].ulForbLaWithValidPeriodBeginTick,
                    pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].ulForbLaWithValidPeriodTick,
                    pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].ulForbLaWithValidPeriodPunishBeginTick
                    );

                continue;
            }

            /* 删除指定的LAI */
            NAS_MML_DeleteLaFromForbLaWithValidPeriodList(pstForbLaWithValidPeriod, i);

            ulDeleteFlg = VOS_TRUE;
        }
    }

    return ulDeleteFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_IsLaiInForbLaWithValidPeriodList
 功能描述  : 判断LAI 是否在禁止LA 列表中
 输入参数  : pstForbLai:需要判断的LAI
 输出参数  : 无
 返 回 值  : LAI在禁止LA列表中的索引，如无匹配，返回最大值
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年9月23日
   作    者   : z00359541
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_GetLaiIndexInForbLaWithValidPeriodList(
    NAS_MML_LAI_STRU                                       *pstCurrCampLai,
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU            *pstForbLaWithValidPeriod
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulIndex;

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_GetLaiIndexInForbLaWithValidPeriodList");

    ulIndex = NAS_MML_MIN(pstForbLaWithValidPeriod->ulForbLaWithValidPeriodNum, NAS_MML_CUSTOMIZE_FORB_LA_MAX_NUM);

    for ( i = 0; i < ulIndex; i++ )
    {
        /* 比较LAI */
        if(VOS_TRUE == NAS_MML_CompareLai(pstCurrCampLai,
            &(pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].stForbLaWithValidPeriodLai)))
        {
            return i;
        }
    }

    return NAS_MML_CUSTOMIZE_FORB_LA_MAX_NUM;
}

/*****************************************************************************
 函 数 名  :NAS_MML_AddCsRegFailLaIntoForbLaListWithValidPeriod
 功能描述  :判断当前CS注册失败原因值是否匹配禁止LA条件
 输入参数  :CS注册失败原因值
 输出参数  :
 返 回 值  :FORB LA是否变化
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年9月23日
   作    者   : z00359541
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_AddCsRegFailLaIntoForbLaListWithValidPeriod(
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_STRU        *pstForbLaWithValidPeriodCfgInfo
)
{
    NAS_MML_LAI_STRU                                       *pstCurrCampLai              = VOS_NULL_PTR;
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU            *pstForbLaWithValidPeriod    = VOS_NULL_PTR;
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_STRU                 *pstCustomizedForbLa         = VOS_NULL_PTR;
    VOS_UINT32                                              ulIndex;

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_AddCsRegFailLaIntoForbLaListWithValidPeriod");

    pstCurrCampLai                      = NAS_MML_GetCurrCampLai();
    pstForbLaWithValidPeriod            = NAS_MML_GetForbLaWithValidPeriodList();

    /* 在禁止LA列表中寻找当前LAI匹配 */
    ulIndex                             = NAS_MML_GetLaiIndexInForbLaWithValidPeriodList(pstCurrCampLai, pstForbLaWithValidPeriod);

    /* 如果pstForbLai已经在禁止LA 列表中则无需添加 */
    if (NAS_MML_CUSTOMIZE_FORB_LA_MAX_NUM != ulIndex)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MML_AddCsRegFailLaIntoForbLaListWithValidPeriod: LAI already added in Forb LA With Valid Period List");
        return VOS_FALSE;
    }

    /* 列表已满,放弃加入禁止LA列表，丢弃此LAI */
    if (NAS_MML_CUSTOMIZE_FORB_LA_MAX_NUM <= pstForbLaWithValidPeriod->ulForbLaWithValidPeriodNum)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MML_AddCsRegFailLaIntoForbLaListWithValidPeriod: Could not add  LAI into Forb LA With Valid Period List because it's full");
        return VOS_FALSE;
    }

    /* 当前LAI不在禁止LA列表里面，且当前列表未满，则需要将LAI加入到禁止LA列表里面 */
    ulIndex             = pstForbLaWithValidPeriod->ulForbLaWithValidPeriodNum;
    pstCustomizedForbLa = &(pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[ulIndex]);

    pstCustomizedForbLa->stForbLaWithValidPeriodLai.stPlmnId.ulMcc               = pstCurrCampLai->stPlmnId.ulMcc;
    pstCustomizedForbLa->stForbLaWithValidPeriodLai.stPlmnId.ulMnc               = pstCurrCampLai->stPlmnId.ulMnc;
    pstCustomizedForbLa->stForbLaWithValidPeriodLai.aucLac[0]                    = pstCurrCampLai->aucLac[0];
    pstCustomizedForbLa->stForbLaWithValidPeriodLai.aucLac[1]                    = pstCurrCampLai->aucLac[1];
    pstCustomizedForbLa->stForbLaWithValidPeriodLai.enCampPlmnNetRat             = pstCurrCampLai->enCampPlmnNetRat;
    pstCustomizedForbLa->stForbLaWithValidPeriodLai.ucRac                        = pstCurrCampLai->ucRac;

    NAS_NORMAL_LOG1(WUEPS_PID_MMC, "NAS_MML_AddCsRegFailLaIntoForbLaListWithValidPeriod: Current Tick", VOS_GetTick());    

    /* 更新禁止LA有效时长 */
    pstCustomizedForbLa->ulForbLaWithValidPeriodTick                             = NAS_MML_SECOND_TO_TICK * (pstForbLaWithValidPeriodCfgInfo->usForbLaValidPeriodLen);
    pstCustomizedForbLa->ulForbLaWithValidPeriodBeginTick                        = VOS_GetTick();

    /* 更新防乒乓机制惩罚时长 */
    pstCustomizedForbLa->ulForbLaWithValidPeriodPunishBeginTick                  = VOS_GetTick();
    pstCustomizedForbLa->ulForbLaWithValidPeriodPunishDurationTick               = NAS_MML_SECOND_TO_TICK * (pstForbLaWithValidPeriodCfgInfo->usPunishTimeLen);
    pstCustomizedForbLa->enCsRegFailCause                                        = pstForbLaWithValidPeriodCfgInfo->usRegFailCause;
    pstForbLaWithValidPeriod->ulForbLaWithValidPeriodNum++;

    /* 可维可测打印 */
    NAS_MMC_LogForbLaWithValidPeriodListInfo();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetCsfbMoSetupFlg
 功能描述  : 获取CSFB MO业务建立标志
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :
 修改历史      :

  1.日    期   : 2015年12月02日
    作    者   : j00174725
    修改内容   : DTS2015120100401
*****************************************************************************/
VOS_UINT8 NAS_MML_GetCsfbMoSetupFlg(VOS_VOID)
{
    VOS_UINT8                           ucCsfbMoCallFlag;
    VOS_UINT8                           ucCsfbMoSsFlag;

    ucCsfbMoCallFlag    = NAS_MML_GetCsfbMoCallSetupFlg();
    ucCsfbMoSsFlag      = NAS_MML_GetCsfbMoSsSetupFlg();

    if ( (VOS_TRUE == ucCsfbMoCallFlag)
      || (VOS_TRUE == ucCsfbMoSsFlag) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

