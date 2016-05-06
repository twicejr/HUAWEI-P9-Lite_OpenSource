/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcComFunc.c
  版 本 号   : 初稿
  作    者   : l00130025
  生成日期   : 2011年8月7日
  最近修改   :
  功能描述   : MMC公共处理函数
  函数列表   :
  修改历史   :
  1.日    期   : 2011年8月7日
    作    者   : l00130025
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "PsTypeDef.h"
#include "NasMmlCtx.h"
#include "NasMmlLib.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcSndLmm.h"
#include "NasMmcSndMm.h"
#include "NasMmSublayerDef.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "NasMmcSndMscc.h"
#include "NasMmcSndOm.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcCtx.h"
#include "NasMmcComFunc.h"
#include "NasMmcPlmnSelectionStrategy.h"
#include "NasMmcSndAps.h"
#include "NasMmcSndCds.h"
#include "NasMmcProcUsim.h"
#include "Nasrrcinterface.h"

#include "NasUtranCtrlInterface.h"
#include "NasMmcProcRegRslt.h"

/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

#include "NasUsimmApi.h"
#include "NasMmcFsmMainTbl.h"
/* added by wx270776 for OM融合, 2015-08-21, begin */
#include "OmApi.h"
/* added by wx270776 for OM融合, 2014-08-21, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e(767)*/
#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_COM_FUNC_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedSndEPlmn
 功能描述  : 当前是否需要发送等效Plmn
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年8月6日
   作    者   : l00130025
   修改内容   : 新生成函数

 2.日    期   : 2011年10月15日
   作    者   : w00167002
   修改内容   : 没有Eplmn时，也需要通知接入层
 3.日    期   : 2013年12月13日
   作    者   : w00242748
   修改内容   : DTS2013121103237:G NMOII，成功驻留，数传业务，业务进行过程中，
                指定搜其他网络，均搜网失败，紧急驻留后，数传业务恢复。此处修改
                当处于手动搜网且当前限制驻留或未注册时，不给接入层发送等效PLMN
 4.日    期   : 2014年1月28日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加获取和注册请求的处理
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedSndEplmn( VOS_VOID )
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnInfo  = VOS_NULL_PTR;
    VOS_UINT32                                              ulEplmnValidFlg;
    VOS_UINT32                                              ulRegFlag;

    /* Added by s00246516 for L-C互操作项目, 2014-02-14, Begin */
    VOS_UINT8                                               ucAsAnyCampOn;
    /* Added by s00246516 for L-C互操作项目, 2014-02-14, End */

    /* 无卡时，无须发送等效 Plmn */
    if (VOS_FALSE == NAS_MML_GetSimPresentStatus())
    {
        return VOS_FALSE;
    }

    /*  当前驻留网络，非Rplmn时，不发送 Eplmn给接入层，避免接入层丢网 */
    pstEplmnInfo = NAS_MML_GetEquPlmnList();


    /* 当前无EPlmn，通知接入层,联合RAU或者联合ATTACH,LAU时，需要删除Eplmn，24008:4.7.3.2.5
    if the attach attempt counter is smaller than 5 and, additionally,
    the update status is different from U1 UPDATED or the stored LAI is different
    from the one of the current serving cell, then the mobile station shall delete
    any LAI, TMSI, ciphering key sequence number stored in the SIM/USIM
    and list of equivalent PLMNs */
    if ( 0 == pstEplmnInfo->ucEquPlmnNum)
    {
        /* 没有EPlmn时，会通知接入层当前驻留的网络 */
        return VOS_TRUE;
    }

    if (VOS_FALSE == NAS_MML_CompareBcchPlmnwithSimPlmn(NAS_MML_GetCurrCampPlmnId(), &(pstEplmnInfo->astEquPlmnAddr[0])))
    {
        return VOS_FALSE;
    }

    ulEplmnValidFlg   = NAS_MML_GetEplmnValidFlg();
    ulRegFlag         = NAS_MMC_GetUserSpecPlmnRegisterStatus();

    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        /* 手动搜网模式判断eplmn列表是否有效，无效则返回 */
        if ((VOS_FALSE == ulRegFlag)
         || (VOS_FALSE == ulEplmnValidFlg))
        {
            return VOS_FALSE;
        }
    }

    /* Added by s00246516 for L-C互操作项目, 2014-02-14, Begin */
    ucAsAnyCampOn = NAS_MMC_GetAsAnyCampOn();

    /* 如果是3GPP2控制注册，当前L为限制驻留，不允许发起注册 */
    if ((NAS_MMC_REG_CONTROL_BY_3GPP_MMC != NAS_MMC_GetRegCtrl())
     && (VOS_TRUE == ucAsAnyCampOn))
    {
        return VOS_FALSE;
    }
    /* Added by s00246516 for L-C互操作项目, 2014-02-14, End */


    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetLaiForbTypeManualSelMode
 功能描述  : 获取手动模式下的禁止Plmn类型
 输入参数  : pstLai
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月21日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2011年11月11日
    作    者   : w00166186
    修改内容   : DTS201111105194,手动搜网失败后ANYCELL搜不是指定网络发起了注册，导致成功后不再搜指定的网络
  3.日    期   : 2011年11月24日
    作    者   : w00167002
    修改内容   : DTS2011112405567:原有的函数名NAS_MML_IsPlmnIdInDestPlmnList
                 更改为NAS_MML_IsBcchPlmnIdInDestSimPlmnList,用于明确判断
                 网络的类型，否则网络比较可能会出错
  4.日    期   : 2012年3月17日
    作    者   : w00176964
    修改内容   : DTS2012031900095 V7R1 C30 SBM&EM定制需求:增加禁止LTE国际漫游定制
  5.日    期   : 2012年11月09日
    作    者   : l65478
    修改内容   : DTS2012103005174, PS成功,在等效PLMN中不设置禁止标志
  6.日    期  : 2012年11月09日
    作    者  : z00161729
    修改内容  : DTS2013012301312:禁止lte漫游，syscfgex设置lw，l优先，开机驻留w的网络46011，disable lte，
                后指定搜46009失败，anycell驻留46011，available定时器超时搜46009过程指定搜46011不带接入技术，
                pdp激活失败后系统消息认为是forbidden网络
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetLaiForbTypeManualSelMode(
    NAS_MML_LAI_STRU                   *pstLai
)
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnInfo  = VOS_NULL_PTR;
    VOS_UINT32                          ulRlst;
    VOS_UINT32                          ulRegFlag;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserSpecPlmn = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          aulComparedMcc[NAS_MML_ROAM_ENABLED_MAX_MCC_NUMBER];

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;
#endif
    VOS_UINT32                          ulEplmnValidFlg;

    /* 手动模式当前Plmn不在Eplmn中且与用户指定网络不同时,禁止注册 */
    pstEplmnInfo = NAS_MML_GetEquPlmnList();

    ulRlst = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(&(pstLai->stPlmnId),
                                            pstEplmnInfo->ucEquPlmnNum,
                                            pstEplmnInfo->astEquPlmnAddr);

    ulRegFlag = NAS_MMC_GetUserSpecPlmnRegisterStatus();
    ulEplmnValidFlg = NAS_MML_GetEplmnValidFlg();

    pstUserSpecPlmn = NAS_MMC_GetUserSpecPlmnId();

    /* LTE禁止国际漫游时，当前用户指定的网络时漫游网络应该是forbidden网络 */
#if (FEATURE_ON == FEATURE_LTE)
    enRatType = NAS_MML_GetCurrNetRatType();

    if ((VOS_FALSE == NAS_MML_GetLteRoamAllowedFlg())
     && (NAS_MML_NET_RAT_TYPE_LTE == enRatType))
     {
        /* 获取运营商定制的MCC列表 */
        NAS_MML_GetRoamEnabledMccList(aulComparedMcc);

        /* 当前驻留PLMN ID为国际漫游网络 */
        if (VOS_FALSE == NAS_MML_IsMccInDestMccList(pstUserSpecPlmn->stPlmnId.ulMcc, NAS_MML_ROAM_ENABLED_MAX_MCC_NUMBER, aulComparedMcc))
        {
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_GetLaiForbTypeManualSelMode FORBIDDEN:ROAM NOT ALLOWED");
            
            return NAS_MML_PLMN_FORBID_PLMN;
        }
     }
#endif

    if ((VOS_TRUE== NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstLai->stPlmnId), &(pstUserSpecPlmn->stPlmnId)))
     || ((VOS_TRUE == ulRegFlag)
      && (VOS_TRUE == ulRlst)
      && (VOS_TRUE == ulEplmnValidFlg)))
    {
        return   NAS_MML_GetLaiForbType(pstLai);
    }
    else
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_GetLaiForbTypeManualSelMode FORBIDDEN:LIKE NOT USER SPEC PLMN");        
        
        return NAS_MML_PLMN_FORBID_PLMN;
    }

}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetLaiForbTypeAutoSelMode
 功能描述  : 获取自动模式下的禁止Plmn类型
 输入参数  : pstLai
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月21日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2011年11月24日
    作    者   : w00167002
    修改内容   : DTS2011112405567:原有的函数名NAS_MML_IsPlmnIdInDestPlmnList
                 更改为NAS_MML_IsBcchPlmnIdInDestSimPlmnList,用于明确判断
                 网络的类型，否则网络比较可能会出错
  3.日    期   : 2012年5月10日
    作    者   : l00130025
    修改内容   : DTS2012050301244: 自动模式，MMC能否驻留不再需要判断ucWrrLimitServiceInd
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetLaiForbTypeAutoSelMode(
    NAS_MML_LAI_STRU                   *pstLai
)
{

    return NAS_MML_GetLaiForbType(pstLai);


}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetCurrentLaiForbbidenType
 功能描述  : 获取当前LA是否在禁止列表中，如果在禁止列表中，禁止列表的类型
 输入参数  : VOS_UINT32                          *pulPlmnLaType
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年12月3日
    作    者   : l65478
    修改内容   : 新生成函数
  2.日    期   : 2011年7月21日
    作    者   : l00130025
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetCurrentLaiForbbidenType(VOS_VOID)
{
    NAS_MML_LAI_STRU                                       *pstCurrentLai = VOS_NULL_PTR;
    VOS_UINT32                                              ulPlmnLaType;
    NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8                  enPlmnSelMode;
    NAS_MML_SIM_STATUS_STRU                                *pstSimStatus    = VOS_NULL_PTR;

    pstSimStatus = NAS_MML_GetSimStatus();

    /* 无USIM卡或者SIM卡无效时，不需要判断FORBIDDEN标志，直接返回 */
    if ( VOS_FALSE == NAS_MML_GetSimPresentStatus() )
    {
        return NAS_MML_PLMN_FORBID_NULL;
    }

    if (( VOS_FALSE == pstSimStatus->ucSimPsRegStatus)
     && ( VOS_FALSE == pstSimStatus->ucSimCsRegStatus))
    {
        return NAS_MML_PLMN_FORBID_NULL;
    }

    enPlmnSelMode = NAS_MMC_GetPlmnSelectionMode();

    pstCurrentLai  = NAS_MML_GetCurrCampLai();

    /* 开机时当前驻留网络信息是默认无效值，无需判断禁止类型 */
    if (VOS_FALSE == NAS_MML_IsPlmnIdValid(&pstCurrentLai->stPlmnId))
    {
        return NAS_MML_PLMN_FORBID_NULL;
    }

    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == enPlmnSelMode)
    {
        ulPlmnLaType =  NAS_MMC_GetLaiForbTypeManualSelMode(pstCurrentLai);
    }
    /*自动模式下禁止信息获取*/
    else
    {
        ulPlmnLaType = NAS_MMC_GetLaiForbTypeAutoSelMode(pstCurrentLai);
    }

    /*返回禁止信息*/
    return ulPlmnLaType;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetHPlmnSpecDomainAccessCapa
 功能描述  : 当前的Hplmn网络的指定域目前是否允许接入,(依据是否之前已注册被拒过)
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:允许接入；VOS_FALSE:不允许接入
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月24日
    作    者   : likelai
    修改内容   : 新生成函数
  2.日    期   : 2011年7月29日
    作    者   : lijun 00171473
    修改内容   : V7R1 PhaseII 修改
  3.日    期   : 2011年12月5日
   作    者   : z00161729
   修改内容   : V7R1 phaseIV修改合并原NAS_MMC_HPLMN_REG_REJ_STRU和NAS_MMC_PLMN_REG_INFO_STRU
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetHPlmnSpecDomainAccessCapa(
    NAS_MMC_REG_DOMAIN_ENUM_UINT8       enRegCnDomain
)
{
    NAS_MMC_PLMN_REG_REJ_CTX_STRU      *pstRegRejCtx       = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstCurrPlmn        = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                   *pstCurrLai         = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;
    VOS_UINT8                           ucCurrCampRac;
    NAS_MMC_REG_DOMAIN_ENUM_UINT8       enDomain;

    if ((NAS_MMC_REG_DOMAIN_CS != enRegCnDomain)
     && (NAS_MMC_REG_DOMAIN_PS != enRegCnDomain)
#if   (FEATURE_ON == FEATURE_LTE)
     && (NAS_MMC_REG_DOMAIN_EPS !=  enRegCnDomain)
#endif
     )
    {
        return VOS_TRUE;
    }

    /* 获取当前驻留的PLMN */
    pstCurrPlmn = NAS_MML_GetCurrCampPlmnId();

    /* 当前驻留PLMN不在HPLMN列表中，则直接返回 */
    if (VOS_FALSE ==  NAS_MML_ComparePlmnIdWithHplmn(pstCurrPlmn))
    {
         return VOS_TRUE;
    }

    /* 获取HPLMN注册被拒的列表 */
    pstRegRejCtx       = NAS_MMC_GetPlmnRegRejInfo();

    /* 当前驻留PLMN在HPLMN注册被拒列表中，则直接返回 */
    ulIndex = NAS_MMC_GetPlmnIndexInRegInfoList(pstCurrPlmn,
                             pstRegRejCtx->ucPlmnRegInfoNum, pstRegRejCtx->astPlmnRegInfoList);

    if (NAS_MML_INVALID_INDEX == ulIndex)
    {
        return VOS_TRUE;
    }

    /* 获取当前驻留的LAI */
    pstCurrLai = NAS_MML_GetCurrCampLai();

    NAS_MMC_GetHplmnRejDomainInfo(&enDomain);

    if (enDomain & enRegCnDomain)
    {
        if (NAS_MMC_REG_DOMAIN_CS == enRegCnDomain)
        {
            if ( (pstRegRejCtx->astPlmnRegInfoList[ulIndex].aucLac[0] == pstCurrLai->aucLac[0])
              && (pstRegRejCtx->astPlmnRegInfoList[ulIndex].aucLac[1] == pstCurrLai->aucLac[1]) )
            {
                NAS_NORMAL_LOG4(WUEPS_PID_MMC,
                                "NAS_MMC_GetHPlmnSpecDomainAccessCapa: Curr LAC in HPLMN REG REJ list ",
                                pstRegRejCtx->astPlmnRegInfoList[ulIndex].stPlmnId.ulMcc,
                                pstRegRejCtx->astPlmnRegInfoList[ulIndex].stPlmnId.ulMnc,
                                pstRegRejCtx->astPlmnRegInfoList[ulIndex].aucLac[0],
                                pstRegRejCtx->astPlmnRegInfoList[ulIndex].aucLac[1]);
                return VOS_FALSE;
            }
        }
        else
        {
           ucCurrCampRac = NAS_MML_GetCurrCampRac();
           if ( (pstRegRejCtx->astPlmnRegInfoList[ulIndex].aucLac[0] == pstCurrLai->aucLac[0])
             && (pstRegRejCtx->astPlmnRegInfoList[ulIndex].aucLac[1] == pstCurrLai->aucLac[1])
             && (pstRegRejCtx->astPlmnRegInfoList[ulIndex].ucRac == ucCurrCampRac) )
           {
               NAS_NORMAL_LOG3(WUEPS_PID_MMC,
                               "NAS_MMC_GetHPlmnSpecDomainAccessCapa: Curr RAC in HPLMN REG REJ list ",
                               pstRegRejCtx->astPlmnRegInfoList[ulIndex].stPlmnId.ulMcc,
                               pstRegRejCtx->astPlmnRegInfoList[ulIndex].stPlmnId.ulMnc,
                               pstRegRejCtx->astPlmnRegInfoList[ulIndex].ucRac);
               return VOS_FALSE;
           }
        }
    }
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetPlmnIndexInRegInfoList
 功能描述  : 确定pstPlmnId在注册信息列表中的位置
 输入参数  : pstPlmnId: 需要查找的PLMN ID
             ulRegPlmnListNum: 列表中元素的个数
             pstPlmnRegList: 列表的指针
 输出参数  : 无
 返 回 值  : 查找到的PLMN的Index
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年2月27日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2011年7月28日
    作    者   : L00171473
    修改内容   : V7R1 PhaseII 修改
*****************************************************************************/
VOS_UINT32  NAS_MMC_GetPlmnIndexInRegInfoList(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    VOS_UINT32                          ulRegPlmnListNum,
    NAS_MMC_PLMN_REG_INFO_STRU         *pstPlmnRegList
)
{
    VOS_UINT32                          i;

    for ( i = 0; i < ulRegPlmnListNum; i++ )
    {
        /* pstPlmnRegList存储的是 BCCH中的值，pstPlmnId可能时卡中的 Plmn */
        if ( VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstPlmnRegList[i].stPlmnId), pstPlmnId) )
        {
            break;
        }
    }

    if (i < ulRegPlmnListNum)
    {
        return i;
    }
    else
    {
        return NAS_MML_INVALID_INDEX;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetOptMask_WasSysinfo
 功能描述  : 获取转发给 MM/GMM 的W系统消息需要的Masl值
 输入参数  : RRMM_SYS_INFO_IND_STRU             *pstRrMmSysInfoInd;
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月8日
    作    者   : l00130025
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetOptMask_WasSysinfo(
    RRMM_SYS_INFO_IND_STRU             *pstRrMmSysInfoInd
)
{
    VOS_UINT32                          ulBitMask;

    ulBitMask = 0;

    /* 根据系统消息的内容，填充Mask值 */
    if (VOS_TRUE == pstRrMmSysInfoInd->bitOpPlmnId)
    {
        ulBitMask |= RRC_NAS_SYS_MSK_PLMN;
    }

    if (VOS_TRUE == pstRrMmSysInfoInd->bitOpCsDrx)
    {
        ulBitMask |= RRC_NAS_SYS_MSK_CS_DRX;
    }

    if (VOS_TRUE == pstRrMmSysInfoInd->bitOpPsDrx)
    {
        ulBitMask |= RRC_NAS_SYS_MSK_PS_DRX;
    }

    if ((0< pstRrMmSysInfoInd->ucCsInfoSize)
     || (0< pstRrMmSysInfoInd->ucPsInfoSize))
    {
        ulBitMask |= RRC_NAS_SYS_MSK_CSPS_INFO;
    }

    return ulBitMask;
}

/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-16, begin */
/* 删除NAS_MMC_ConvertUserSpecAccessMode2MmlRat函数*/
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-16, end */



/*****************************************************************************
 函 数 名  : NAS_MMC_CovertMmlSysSubModeToMsccSysSubMode
 功能描述  : 将MML定义的系统子模式转为MSCC中的系统子模式
 输入参数  : enSysSubMode: MML定义的系统子模式
 输出参数  : 无
 返 回 值  : TAF_SYS_SUBMODE_ENUM_UINT8:  MSCC中的系统子模式
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年6月15日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2015年12月25日
   作    者   : z00359541
   修改内容   : DTS2015121007229:将subsysmode缺省值转换为无服务
*****************************************************************************/
TAF_SYS_SUBMODE_ENUM_UINT8 NAS_MMC_CovertMmlSysSubModeToMsccSysSubMode(
    NAS_MML_RRC_SYS_SUBMODE_ENUM_UINT8  enSysSubMode
)
{
    VOS_UINT32                          i;

    VOS_UINT8                           aucSysSubModeMapTable[NAS_MML_MAX_SYS_SUBMODE_NUM][2] =
    {
        {NAS_MML_RRC_SYS_SUBMODE_NULL,        TAF_SYS_SUBMODE_NONE       },
        {NAS_MML_RRC_SYS_SUBMODE_GSM,         TAF_SYS_SUBMODE_GSM        },
        {NAS_MML_RRC_SYS_SUBMODE_GPRS,        TAF_SYS_SUBMODE_GPRS       },
        {NAS_MML_RRC_SYS_SUBMODE_EDGE,        TAF_SYS_SUBMODE_EDGE       },
        {NAS_MML_RRC_SYS_SUBMODE_WCDMA,       TAF_SYS_SUBMODE_WCDMA      },
        {NAS_MML_RRC_SYS_SUBMODE_HSDPA,       TAF_SYS_SUBMODE_HSDPA      },
        {NAS_MML_RRC_SYS_SUBMODE_HSUPA,       TAF_SYS_SUBMODE_HSUPA      },
        {NAS_MML_RRC_SYS_SUBMODE_HSDPA_HSUPA, TAF_SYS_SUBMODE_HSDPA_HSUPA},
        {NAS_MML_RRC_SYS_SUBMODE_LTE,         TAF_SYS_SUBMODE_LTE        },
        {NAS_MML_RRC_SYS_SUBMODE_BUTT,        TAF_SYS_SUBMODE_NONE       },
    };

    for (i = 0; i < NAS_MML_MAX_SYS_SUBMODE_NUM; i++)
    {
        if (enSysSubMode == aucSysSubModeMapTable[i][0])
        {
            return aucSysSubModeMapTable[i][1];
        }
    }

    return TAF_SYS_SUBMODE_BUTT;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsHplmnTimerLenValid
 功能描述  : HPLMN定时器时长是否生效
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:有效
             VOS_FALSE:无效
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月13日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsHplmnTimerLenValid( VOS_VOID )
{
    NAS_MML_BG_SEARCH_CFG_INFO_STRU    *pstBgSearchCfg = VOS_NULL_PTR;

    pstBgSearchCfg = NAS_MML_GetBgSearchCfg();

    /* H3G需求特性(VPLMN下非首次搜HPLMN时长NV可配置)打开*/
    if (VOS_TRUE == pstBgSearchCfg->stNonFirstHplmnTimerPeriod.ucNvimActiveFlg)
    {
        /* HPLMN定时器的时长从从NV：en_NV_Item_SearchHplmnTtimerValue中获取，
           NV中值大于0时，HPLMN定时器时长有效 */
        if (pstBgSearchCfg->stNonFirstHplmnTimerPeriod.ulNonFirstHplmnTimerLen != 0)
        {
            return VOS_TRUE;
        }
    }
    else
    {
        /* HPLMN定时器的时长从USIM文件EFHPPLMN (0x6F31 Higher Priority PLMN search period)
           中获取，该文件的值大于0时，HPLMN定时器时长有效 */
        if (NAS_MML_GetSimHplmnTimerLen() != 0)
        {
            return VOS_TRUE;
        }
    }

    NAS_NORMAL_LOG2(WUEPS_PID_MMC, "stNonFirstHplmnTimerPeriod active and time len is: ",pstBgSearchCfg->stNonFirstHplmnTimerPeriod.ucNvimActiveFlg, pstBgSearchCfg->stNonFirstHplmnTimerPeriod.ulNonFirstHplmnTimerLen);

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsHighPrioPlmnSearchVaild
 功能描述  : 高优先级选网当前是否有效
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:有效
             VOS_FALSE:无效
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月13日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2012年6月22日
   作    者   : w00176964
   修改内容   : DTS2012062007370:PS ONLY,PS被拒#3卡无效,标杆在HPLMN超时不发起BG搜网
                balong发起了BG搜网
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsHighPrioPlmnSearchVaild( VOS_VOID )
{
    /* 手动模式下返回无效 */
    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "highPrioPlmnSearchVaild:manual mode");
        
        return VOS_FALSE;
    }

    if (VOS_FALSE == NAS_MML_IsUsimStausValid())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "highPrioPlmnSearchVaild:UsimStaus IN Valid");
        
        return VOS_FALSE;
    }

    /* HPLMN TIMER LEN定时器时长无效 */
    if ( VOS_FALSE == NAS_MMC_IsHplmnTimerLenValid() )
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "plmnTimerLen is inValid");
        
        return VOS_FALSE;
    }

    /* 返回有效 */
    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsCampOnHPlmn
 功能描述  : 判断当前是否已经驻留在HPLMN的网络上
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  : 已经驻留在HPLMN的网络上
             VOS_FALSE : 没有驻留在HPLMN的网络上
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月13日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsCampOnHPlmn(VOS_VOID)
{
    NAS_MML_PLMN_ID_STRU               *pstCurrCampPlmnId = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnList      = VOS_NULL_PTR;
    VOS_UINT32                          i;

    /* 取得当前驻留的PLMN ID */
    pstCurrCampPlmnId = NAS_MML_GetCurrCampPlmnId();

    /* 与HPLMN相同，返回已驻留HPLMN上 */
    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(pstCurrCampPlmnId))
    {
        return VOS_TRUE;
    }

    pstEplmnList  = NAS_MML_GetEquPlmnList();

    /* 如果当前网络与EPLMN第1个不同,表示存储的EPLMN非当前网络的EPLMN,此时不用比较EPLMN了 */
    if (VOS_FALSE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstCurrCampPlmnId,
                                                       &pstEplmnList->astEquPlmnAddr[0]))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsCampOnHPlmn:false, not eplmn");
        
        return VOS_FALSE;
    }

    /* EPLMN是从数组下标1开始存放的，数组下标0存放的是RPLMN */
    for ( i = 1; i < pstEplmnList->ucEquPlmnNum; i++ )
    {
        if (VOS_FALSE == NAS_MML_ComparePlmnMcc(pstCurrCampPlmnId->ulMcc, pstEplmnList->astEquPlmnAddr[i].ulMcc))
        {
            continue;
        }

        /* 如果HOME PLMN在EPLMN中，且和当前驻留的PLMN的MCC相同，
           认为当前已经在HOME PLMN上 */
        if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(&pstEplmnList->astEquPlmnAddr[i]))
        {
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsCampOnHPlmn:true");
            
            return VOS_TRUE;
        }
    }


    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsCampOnHighestPrioPlmn
 功能描述  : 判断当前是否已经驻留在最高优先级的网上
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  : 已经驻留在最高优先级的网络上
             VOS_FALSE : 没有驻留在最高优先级的网络上
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月13日
   作    者   : z00161729
   修改内容   : 新生成函数

 2.日    期   : 2011年10月21日
   作    者   : W00167002
   修改内容   :【高优先级ST发现，发现用例号:D03_HighPrioPlmnSearch_091
                场景:在L下注册成功后，单模发生丢网后, 认为驻留在最高优先级的网络上，没有启动周期尝试搜网定时器】
                增加当前驻留的网络是无效PLMNID的判断

 3.日    期   : 2012年5月17日
   作    者   : zhoujun 40661
   修改内容   : 泰国AIS特性

 4.日    期   : 2012年6月13日
   作    者   : l00171473
   修改内容   : DTS2012061302162, 当前驻留(E)HPLMN认为驻留最高优先级网络不起BG搜
 5.日    期   : 2012年6月20日
   作    者   : w00166186
   修改内容   : AT&T&DCM项目
 6.日    期   : 2014年5月28日
   作    者   : z00234330
   修改内容   : covertity修改
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsCampOnHighestPrioPlmn(VOS_VOID)
{
    NAS_MML_BG_SEARCH_CFG_INFO_STRU                        *pstBgSearchCfg           = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                                   *pstCurrCampPlmnId        = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEplmnList             = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stHighestPrioPlmnInfo;
    NAS_MML_AIS_ROAMING_CFG_STRU                           *pstRoamingCfg            = VOS_NULL_PTR;
    VOS_UINT32                                              ulIsCampOnHPlmn;
    NAS_MMC_HPLMN_SEARCH_REGARDLESS_MCC_CTX_STRU           *pstBgSearchRegardlessMccCtx = VOS_NULL_PTR;

    pstCurrCampPlmnId           = NAS_MML_GetCurrCampPlmnId();
    pstPlmnSelectionListInfo    = NAS_MMC_GetHighPrioPlmnList();
    pstBgSearchCfg              = NAS_MML_GetBgSearchCfg();
    pstEplmnList                = NAS_MML_GetEquPlmnList();

    pstBgSearchRegardlessMccCtx = NAS_MML_GetBgSearchRegardlessMccCtx();

    /* modified by z00234330 for coverity修改 2014-05-28 begin */
    PS_MEM_SET(&stHighestPrioPlmnInfo,0x00, sizeof(stHighestPrioPlmnInfo));
    /* modified by z00234330 for coverity修改 2014-05-28 end */


    /* 如果当前网络无效，则返回未驻留在最高优先级网络上，当单模丢网后，当前驻留的网络
       是无效PLMNID */
    if ( VOS_FALSE == NAS_MML_IsPlmnIdValid(pstCurrCampPlmnId) )
    {
        return VOS_FALSE;
    }

    /* Modified by z40661 for 泰国AIS特性 2012-05-17, begin */
    pstRoamingCfg  = NAS_MML_GetAisRoamingCfg();
    if ( VOS_TRUE == NAS_MMC_IsAisRoamingEffect())
    {
        /* 判断是否驻留在特殊的PLMN上,由于已经和运营商确认,
        AIS和TOT这两个网络之间不会配置为EPLMN，小区之间也不会配置为邻区关系
        */
        return NAS_MML_IsBcchPlmnIdInDestSimPlmnList(NAS_MML_GetCurrCampPlmnId(),
            1, &(pstRoamingCfg->stHighPrioPlmnId));
    }

    /* Modified by z40661 for 泰国AIS特性 2012-05-17, end */


    ulIsCampOnHPlmn = NAS_MMC_IsCampOnHPlmn();
    /* 如果当前已驻留在(E)HPLMN上, 认为驻留在最高优先级网络上 */
    if (VOS_TRUE == ulIsCampOnHPlmn)
    {
        return VOS_TRUE;
    }


    if (VOS_FALSE == NAS_MMC_IsCampOnHPlmn())
    {
        /* Vplmn与Hplmn不同国家码时,允许回到Hplmn的定制特性开关打开时 */
        if (VOS_TRUE == pstBgSearchCfg->ucSpecialRoamFlg)
        {
            return VOS_FALSE;
        }

        /* AT&T BG搜不考虑国家码定制开关打开，且VPLMN国家码在定制列表中 */
        if (VOS_TRUE == NAS_MML_IsMccInDestMccList(pstCurrCampPlmnId->ulMcc, pstBgSearchRegardlessMccCtx->ucCustomMccNum, pstBgSearchRegardlessMccCtx->aulCostumMccList))
        {
            return VOS_FALSE;
        }
    }

    /* 从高优先级列表中获取和当前驻留网络相同国家码的最高优先级网络 */
    if (VOS_FALSE == NAS_MMC_GetHighestPrioPlmnInHighPrioPlmnList(pstPlmnSelectionListInfo,
                                                          &stHighestPrioPlmnInfo))
    {
        /* 没有相同国家码的高优先级网络，认为已经驻留在最高优先级网络，返回vos_true,无需启动hplmn定时器*/
        return VOS_TRUE;
    }

    /* 比较VPLMN和高优先级网络优先级是否相同，相同则认为已经驻留在最高优先级网络 */
    if (VOS_TRUE == NAS_MMC_CompareVPlmnPrioWithHighPrioPlmn(pstCurrCampPlmnId,
                                                             NAS_MML_GetCurrNetRatType(),
                                                             pstEplmnList,
                                                             &stHighestPrioPlmnInfo ))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedStartHPlmnTimer
 功能描述  : 判断是否需要启动HPLMN定时器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要启动HPLMN定时器
             VOS_FALSE:不需要启动HPLMN定时器
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月21日
   作    者   : z00161729
   修改内容   : 新生成函数

 2.日    期   : 2012年8月28日
   作    者   : w00167002
   修改内容   : 当前UTRAN工作模式为TDD，则不启动背景搜定时器

 3.日    期   : 2013年12月20日
   作    者   : w00167002
   修改内容   : DTS2013112917981:guNAS删除在TD模式下不能进行bg搜的限制。
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedStartHPlmnTimer(VOS_VOID)
{
    NAS_MML_BG_SEARCH_CFG_INFO_STRU    *pstBgSearchCfg           = VOS_NULL_PTR;


    /* 判断当前高优先级搜网是否有效，手动模式或SIM卡不在位或CS和PS卡均无效
       或HPLMN定时器时长为0时，认为当前无需启动HPLMN定时器，不需进行高优先级搜网 */
    if (VOS_FALSE == NAS_MMC_IsHighPrioPlmnSearchVaild())
    {
        return VOS_FALSE;
    }

    /* 为了避免反复调用高优先级搜网的处理，在10s周期性尝试定时器运行期间不启动HPLMN定时器 */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedStartHPlmnTimer:TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH:RUNNING");
        
        return VOS_FALSE;
    }

    /* 如果HPLMN已经在运行，无需启动,on plmn下收到ps注册结果和cs注册结果都会判断是否需要启动hplmn定时器，可能存在已在运行的情况 */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_HPLMN_TIMER))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedStartHPlmnTimer:TI_NAS_MMC_HPLMN_TIMER:RUNNING");
        
        return VOS_FALSE;
    }

    pstBgSearchCfg            = NAS_MML_GetBgSearchCfg();

    /* 如果已经驻留到最高优先级网络 */
    if (VOS_TRUE == NAS_MMC_IsCampOnHighestPrioPlmn())
    {
        /* 如果增强的Hplmn搜网,法电定制特性开关打开: 启动Hplmn Timer定时器,
           只要没有驻留在home PLMN上,也需要启动此定时器,第一次启动2Min,后续都以T Min启动*/
        if ((VOS_FALSE == NAS_MMC_IsCampOnHPlmn())
         && (VOS_TRUE == pstBgSearchCfg->ucEnhancedHplmnSrchFlg))
        {
            return VOS_TRUE;
        }

        NAS_NORMAL_LOG1(WUEPS_PID_MMC, "NAS_MMC_IsNeedStartHPlmnTimer:ucEnhancedHplmnSrchFlg is",pstBgSearchCfg->ucEnhancedHplmnSrchFlg);

        return VOS_FALSE;
    }

    return VOS_TRUE;
}




/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertRrcPlmnList2SearchedPlmnListInfo
 功能描述  : 根据搜网结果更新相应接入技术的信息
 输入参数  : enRat
             pstPlmnIdList
 输出参数  : pstSearchedPlmnListInfo
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
   作    者   : s46746
   修改内容   : 新生成函数

 2.日    期   : 2011年9月26日
   作    者   : w00167002
   修改内容   : NAS_MMC_ConvertRrcPlmnList2SearchedPlmnListInfo_PlmnSelection函数
                名称更改为NAS_MMC_ConvertRrcPlmnList2SearchedPlmnListInfo，并从
                文件NasMmcFsmPlmnSelection.c文件迁移到NasMmcComFunc.c
 3.日    期   : 2011年10月4日
   作    者   : s46746
   修改内容   : 修改变量名pstInterPlmnSearchInfo为pstSearchedPlmnListInfo,与结构体名称一致
*****************************************************************************/
VOS_VOID NAS_MMC_ConvertRrcPlmnList2SearchedPlmnListInfo(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat,
    RRC_PLMN_ID_LIST_STRU                                  *pstPlmnIdList,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    VOS_UINT32                          i;

    pstSearchedPlmnListInfo->enRatType = enRat;

    /* 循环pstPlmnIdList中的每一个高质量PLMN ID,赋值到pstIntraPlmnSearchInfo */
    for (i = 0; ((i < pstPlmnIdList->ulHighPlmnNum) && (i < NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM)); i++)
    {
        pstSearchedPlmnListInfo->astHighPlmnList[i].ulMcc         = pstPlmnIdList->aHighPlmnList[i].stPlmnId.ulMcc;
        pstSearchedPlmnListInfo->astHighPlmnList[i].ulMnc         = pstPlmnIdList->aHighPlmnList[i].stPlmnId.ulMnc;
    }
    pstSearchedPlmnListInfo->ulHighPlmnNum = i;

    /* 循环pstPlmnIdList中的每一个低质量PLMN ID,将PLMN ID和质量赋值到pstIntraPlmnSearchInfo */
    for (i = 0; ((i < pstPlmnIdList->ulLowPlmnNum) && (i < NAS_MMC_INTRA_MAX_LOW_QUALITY_PLMN_NUM)); i++)
    {
        pstSearchedPlmnListInfo->astLowPlmnList[i].stPlmnId.ulMcc = pstPlmnIdList->aLowPlmnList[i].PlmnId.stPlmnId.ulMcc;
        pstSearchedPlmnListInfo->astLowPlmnList[i].stPlmnId.ulMnc = pstPlmnIdList->aLowPlmnList[i].PlmnId.stPlmnId.ulMnc;
        pstSearchedPlmnListInfo->astLowPlmnList[i].lRscp          = pstPlmnIdList->aLowPlmnList[i].lRscp;
    }
    pstSearchedPlmnListInfo->ulLowPlmnNum = i;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertRrcBgPlmnSearchRslt2SearchedPlmnListInfo
 功能描述  : 将GU下的BG搜网结果中的PLMN信息转为内部搜网消息结构中PLMN信息
 输入参数  : enRat                  -- 当前进行BG搜的接入技术
             pstBgSearchRslt        -- BG搜网结果消息
             pstSearchedPlmnListInfo -- 内部搜网消息结构中PLMN信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月27日
   作    者   : L00171473
   修改内容   : 新生成函数
 2.日    期   : 2012年5月7日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL 背景搜修改

*****************************************************************************/
VOS_VOID NAS_MMC_ConvertRrcBgPlmnSearchRslt2SearchedPlmnListInfo(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat,
    RRMM_BG_PLMN_SEARCH_CNF_ST                             *pstBgSearchRslt,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulTotalNum;

    /* 设置当前进行BG搜的接入技术 */
    pstSearchedPlmnListInfo->enRatType = enRat;

    /* 循环pstBgPlmnIdList中的每一个PLMN ID, 赋值到pstIntraPlmnSearchInfo */
    ulTotalNum                             = pstBgSearchRslt->ucPlmnNum;
    pstSearchedPlmnListInfo->ulHighPlmnNum = pstBgSearchRslt->ucPlmnNum;

    if (pstSearchedPlmnListInfo->ulHighPlmnNum > NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM)
    {
        pstSearchedPlmnListInfo->ulHighPlmnNum = NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM;
        ulTotalNum                             = NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM;
    }

    pstSearchedPlmnListInfo->ulLowPlmnNum  = 0x0;

    for ( i = 0 ; i < ulTotalNum; i++ )
    {
        pstSearchedPlmnListInfo->astHighPlmnList[i].ulMcc = pstBgSearchRslt->astPlmnId[i].stPlmnId.ulMcc;
        pstSearchedPlmnListInfo->astHighPlmnList[i].ulMnc = pstBgSearchRslt->astPlmnId[i].stPlmnId.ulMnc;
    }


    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertLmmPlmnList2SearchedPlmnListInfo
 功能描述  : 将L模的搜网结果中的PLMN信息转为内部搜网消息结构中PLMN信息
 输入参数  : pstPlmnIdList: 搜网结果中的PLMN信息
 输出参数  : pstSearchedPlmnListInfo: 内部搜网消息结构中PLMN信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
   作    者   : s46746
   修改内容   : 新生成函数

 2.日    期   : 2011年9月26日
   作    者   : w00167002
   修改内容   : NAS_MMC_ConvertLmmPlmnList2SearchedPlmnListInfo_PlmnSelection函数
                名称更改为NAS_MMC_ConvertLmmPlmnList2SearchedPlmnListInfo，并从
                文件NasMmcFsmPlmnSelection.c文件迁移到NasMmcComFunc.c
 3.日    期   : 2011年10月4日
   作    者   : s46746
   修改内容   : 修改变量名pstInterPlmnSearchInfo为pstSearchedPlmnListInfo,与结构体名称一致
 4.日    期   : 2012年4月27日
   作    者   : w00176964
   修改内容   : GUL_BG项目调整:L的搜网列表结构体调整,携带接入技术
*****************************************************************************/
VOS_VOID NAS_MMC_ConvertLmmPlmnList2SearchedPlmnListInfo(
    MMC_LMM_PLMN_ID_LIST_STRU                              *pstLMMPlmnList,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_PLMN_ID_STRU                stPlmn;
    VOS_UINT32                          i;
    NAS_MML_SIM_FORMAT_PLMN_ID          stSimPlmn;

    PS_MEM_SET(&stSimPlmn, 0, sizeof(NAS_MML_SIM_FORMAT_PLMN_ID));
    pstSearchedPlmnListInfo->enRatType = NAS_MML_NET_RAT_TYPE_LTE;

    /* 循环pstLMMPlmnList中的每一个高质量PLMN ID,赋值到pstIntraPlmnSearchInfo */
    for (i = 0; ((i < pstLMMPlmnList->ulHighPlmnNum) && (i < NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM)); i++)
    {
        /* 先转换为SIM格式 */
        PS_MEM_CPY(stSimPlmn.aucSimPlmn, pstLMMPlmnList->astHighPlmnWithRatList[i].aucPlmnId, MMC_LMM_PLMN_ID_LEN);

        NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmn, &stPlmn);

        pstSearchedPlmnListInfo->astHighPlmnList[i]         = stPlmn;
    }

    pstSearchedPlmnListInfo->ulHighPlmnNum = i;

    /* 循环pstLMMPlmnList中的每一个低质量PLMN ID,将PLMN ID和质量赋值到pstIntraPlmnSearchInfo */
    for (i = 0; ((i < pstLMMPlmnList->ulLowPlmnNum) && (i < NAS_MMC_INTRA_MAX_LOW_QUALITY_PLMN_NUM)); i++)
    {
        /* 先转换为SIM格式 */
        PS_MEM_CPY(stSimPlmn.aucSimPlmn, pstLMMPlmnList->astLowPlmnWithRatList[i].stPlmnIdWithRat.aucPlmnId, MMC_LMM_PLMN_ID_LEN);

        NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmn, &stPlmn);

        pstSearchedPlmnListInfo->astLowPlmnList[i].lRscp    = pstLMMPlmnList->astLowPlmnWithRatList[i].lRscp;


        pstSearchedPlmnListInfo->astLowPlmnList[i].stPlmnId = stPlmn;
    }
    pstSearchedPlmnListInfo->ulLowPlmnNum = i;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertLmmBgPlmnSearchRslt2SearchedPlmnListInfo
 功能描述  : 将L模的背景搜网结果中的PLMN信息转为内部搜网消息结构中PLMN信息
 输入参数  : pstLmmPlmnList          - 搜网结果中的PLMN信息
 输出参数  : pstSearchedPlmnListInfo - 内部搜网消息结构中PLMN信息
             enRatType               - 接入技术
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年4月25日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2012年6月19日
   作    者   : z00161729
   修改内容   : DTS2012061908820:L上报bg搜网失败没有带任何网络时未更新接入技术

*****************************************************************************/
VOS_VOID NAS_MMC_ConvertLmmBgPlmnSearchRslt2SearchedPlmnListInfo(
    LMM_MMC_BG_PLMN_SEARCH_CNF_STRU                        *pstLmmPlmnList,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo,
     NAS_MML_NET_RAT_TYPE_ENUM_UINT8                        enRatType
)
{
    VOS_UINT32                          ulIndex;
    MMC_LMM_PLMN_ID_STRU                stLmmPlmn;
    NAS_MML_PLMN_ID_STRU                stGUNasPlmn;
    VOS_UINT32                          ulTotalNum;

    pstSearchedPlmnListInfo->enRatType     = enRatType;

    ulTotalNum                             = pstLmmPlmnList->ulPlmnNum;
    pstSearchedPlmnListInfo->ulHighPlmnNum = pstLmmPlmnList->ulPlmnNum;

    if (pstSearchedPlmnListInfo->ulHighPlmnNum > NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM)
    {
        pstSearchedPlmnListInfo->ulHighPlmnNum = NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM;
        ulTotalNum                             = NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM;
    }

    pstSearchedPlmnListInfo->ulLowPlmnNum  = 0x0;

    for ( ulIndex = 0; ulIndex < ulTotalNum; ulIndex++ )
    {
        pstSearchedPlmnListInfo->enRatType = pstLmmPlmnList->astPlmnIdWithRatList[ulIndex].enPlmnRat;
        PS_MEM_CPY(stLmmPlmn.aucPlmnId, pstLmmPlmnList->astPlmnIdWithRatList[ulIndex].aucPlmnId, MMC_LMM_PLMN_ID_LEN);
        NAS_MMC_ConvertLmmPlmnToGUNasFormat(&stLmmPlmn, &stGUNasPlmn);
        pstSearchedPlmnListInfo->astHighPlmnList[ulIndex].ulMcc = stGUNasPlmn.ulMcc;
        pstSearchedPlmnListInfo->astHighPlmnList[ulIndex].ulMnc = stGUNasPlmn.ulMnc;
    }

    return;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_MML_IsPlmnWithRatInPlmnList
 功能描述  : 检查PLMN是否在列表中
 输入参数  : NAS_MML_PLMN_ID_STRU               *pstPlmnId
             NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
             NAS_MML_PLMN_ID_STRU               *pstPlmnIdList
             VOS_UINT32                          ulPlmnNum
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月4日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数
  2.日    期   : 2014年6月17日
    作    者   : z00234330
    修改内容   : PCINT清理
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlmnWithRatInPlmnList (
    NAS_MML_PLMN_ID_STRU                                   *pstPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    VOS_UINT32                                              ulPlmnNum
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;

    if (ulPlmnNum > pstPlmnSelectionListInfo->usSearchPlmnNum)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MML_IsPlmnWithRatInPlmnList: Plmn Num Overflow!");
        return VOS_FALSE;
    }

    /* 检查对应接入技术的PLMN ID 是否在列表中 */
    for (i = 0; i < ulPlmnNum; i++)
    {
        for (j = 0; j < pstPlmnSelectionListInfo->astPlmnSelectionList[i].ucRatNum; j++)
        {
            /* Modified by z00234330 for PCLINT清理, 2014-06-16, begin */
            if ((VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstPlmnId,
                                                                 &(pstPlmnSelectionListInfo->astPlmnSelectionList[i].stPlmnId)))
             && (enRat == pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j].enRatType))
            {
                return VOS_TRUE;
            }
            /* Modified by z00234330 for PCLINT清理, 2014-06-16, end */
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertPlmnId2NasFormat
 功能描述  : 将原PLMNid转化为NAS内部使用格式记录
             例如:MCC为460,MNC为01时,
             pstPlmnId->Mcc = 0x000604      pstPlmnId->Mcc = 0x00000460
                                        <----
             pstPlmnId->Mnc = 0x000100      pstPlmnId->Mnc = 0x00000001
 输入参数  : pstPlmnId - 原plmn格式
 输出参数  : pstPlmnId - nas内部plmn格式
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月28日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_ConvertPlmnId2NasFormat(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    VOS_UINT8                           ucPlmnMncNum
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           aucTmp[4];
    VOS_UINT32                          ulMcc;
    VOS_UINT32                          ulMnc;

    PS_MEM_SET(aucTmp, 0, sizeof(aucTmp));
    ulMcc = 0;
    ulMnc = 0;

    ulMcc            = pstPlmnId->ulMcc;
    pstPlmnId->ulMcc = 0;

    for ( i = 0 ; i < 3 ; i++ )
    {
        aucTmp[i]     = ulMcc & 0x0f;
        ulMcc         >>=  4;
    }

    pstPlmnId->ulMcc  =  aucTmp[2]
                     |((VOS_UINT32)aucTmp[1] << 8)
                     |((VOS_UINT32)aucTmp[0] << 16);

    /*更新MNC前，清空变量*/
    PS_MEM_SET(aucTmp, 0, sizeof(aucTmp));

    ulMnc           = pstPlmnId->ulMnc;
    pstPlmnId->ulMnc  = 0;

    for ( i = 0 ; i < 3 ; i++ )
    {
        aucTmp[i]     = ulMnc & 0x0f;
        ulMnc         >>=  4;
    }

    if(NAS_MML_MNC_LENGTH_TWO_BYTES_IN_IMSI == ucPlmnMncNum)
    {
        pstPlmnId->ulMnc =  aucTmp[1]
                         |((VOS_UINT32)aucTmp[0] << 8)
                         |0x0f0000;
    }
    else
    {
        pstPlmnId->ulMnc =   aucTmp[2]
                     |((VOS_UINT32)aucTmp[1] << 8)
                     |((VOS_UINT32)aucTmp[0] << 16);
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RemoveSpecDplmnFromeNplmnList
 功能描述  : 将指定DPLMN从在NPLMN List中删除
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : l00289540
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_RemoveSpecDplmnFromNplmnList(
    NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU                  *pstSpecDplmn,
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstRatPrioList = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                                        stTempLai;
    VOS_UINT8                                               i;

    PS_MEM_SET(&stTempLai, 0x00, sizeof(NAS_MML_LAI_STRU));

    pstRatPrioList       = NAS_MML_GetMsPrioRatList();
    stTempLai.stPlmnId   = pstSpecDplmn->stSimPlmnWithRat.stPlmnId;

    for (i = 0;  i < pstRatPrioList->ucRatNum; i++)
    {
        stTempLai.enCampPlmnNetRat = pstRatPrioList->aucRatPrio[i];

        if (VOS_FALSE == NAS_MMC_IsNetRatContainedInSimRat(stTempLai.enCampPlmnNetRat, pstSpecDplmn->stSimPlmnWithRat.usSimRat))
        {
            continue;
        }

        NAS_MMC_DeleteDPlmnNPlmnList(&(stTempLai), pstSpecDplmn->enRegDomain, &pstDPlmnNPlmnCfgInfo->usNplmnListNum, pstDPlmnNPlmnCfgInfo->astNPlmnList);
    }
}


/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateDplmnNplmnInfo
 功能描述  : 更新mmc DPLMN和NPLMN信息
 输入参数  : pstNvimCfgDPlmnNPlmnInfo - nv项里dplmn和nplmn信息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月3日
    作    者   : z00161729
    修改内容   : 开机漫游搜网项目修改
  2.日    期   : 2015-5-18
    作    者   : c00318887
    修改内容   : DPlmn扩容和优先接入HPLMN
  3.日    期   : 2015年10月21日
    作    者   : l00289540
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0 修改
  4.日    期   : 2015年12月15日
    作    者   : s00217060
    修改内容   : DTS2015120701561:防止数组越界
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateDplmnNplmnInfo(
    NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU                 *pstNvimCfgDPlmnNPlmnInfo,
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo
)
{
    VOS_UINT32                                              ulStep;
    NAS_MML_PLMN_ID_STRU                                    stTempPlmn;
    NAS_MML_SIM_FORMAT_PLMN_ID                              stNvimPlmn;
    VOS_UINT16                                              usSimRat;
    NAS_MMC_REG_DOMAIN_ENUM_UINT8                           enRegDomain;

    /* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-20, begin */
    NAS_MMC_DPLMN_NPLMN_SETTING_TYPE_ENUM_UINT8             enType;
    /* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-20, end */

    enRegDomain              = NAS_MMC_REG_DOMAIN_BUTT;
    PS_MEM_SET(&stTempPlmn, 0, sizeof(stTempPlmn));
    PS_MEM_SET(&stNvimPlmn, 0, sizeof(stNvimPlmn));

    /* 防止NV项越界，加异常保护 */
    if (pstNvimCfgDPlmnNPlmnInfo->usDplmnListNum > NAS_MMC_NVIM_MAX_CFG_DPLMN_NUM)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdateDplmnNplmnInfo: usDplmnListNum of NVIM is greater than NAS_MMC_MAX_CFG_DPLMN_NUM");

        pstNvimCfgDPlmnNPlmnInfo->usDplmnListNum = NAS_MMC_NVIM_MAX_CFG_DPLMN_NUM;
    }

    /* 将NV中的DPLMN保存到内存中,需要防止数组越界 */
    for ( ulStep = 0; ulStep < pstNvimCfgDPlmnNPlmnInfo->usDplmnListNum; ulStep++ )
    {
        /* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-20, begin */
        PS_MEM_CPY(stNvimPlmn.aucSimPlmn,
            pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList + (ulStep * (NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN)), NAS_MML_SIM_PLMN_ID_LEN);

        /* 转换PLMN ID为MMC内部的格式并存储 */
        NAS_MMC_ConvertSimPlmnToNasPLMN(&stNvimPlmn, &stTempPlmn);


        /* 存储PLMN对应的RAT */
        usSimRat    = (VOS_UINT16)(pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + NAS_MML_PLMN_WITH_RAT_FIRST_RAT_OFFSET] << NAS_MML_OCTET_MOVE_EIGHT_BITS)
                                | pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + NAS_MML_PLMN_WITH_RAT_SECOND_RAT_OFFSET];

        enRegDomain = (VOS_UINT8)(pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + NAS_MML_PLMN_WITH_RAT_UNIT_LEN]);

        enType      = (VOS_UINT8)(pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + NAS_MMC_DPLMN_NPLMN_NV_PRESETING_FLAG_INDEX]);
        /* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-20, end */

        /* 若是需要添加的DPLMN已经存在，不需要重复添加 */
        if (VOS_TRUE == NAS_MMC_IsPlmnIdWithSimRatInSimPlmnWithRegDomainList(&stTempPlmn, usSimRat, pstDPlmnNPlmnCfgInfo->usDplmnListNum, pstDPlmnNPlmnCfgInfo->astDPlmnList))
        {
            continue;
        }

        if ((VOS_TRUE == NAS_MML_IsPlmnIdValid(&stTempPlmn))
         && (NAS_MML_INVALID_SIM_RAT != usSimRat))
        {
            pstDPlmnNPlmnCfgInfo->astDPlmnList[pstDPlmnNPlmnCfgInfo->usDplmnListNum].stSimPlmnWithRat.stPlmnId = stTempPlmn;
            pstDPlmnNPlmnCfgInfo->astDPlmnList[pstDPlmnNPlmnCfgInfo->usDplmnListNum].stSimPlmnWithRat.usSimRat = usSimRat;
            pstDPlmnNPlmnCfgInfo->astDPlmnList[pstDPlmnNPlmnCfgInfo->usDplmnListNum].enRegDomain               = enRegDomain;

            /* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-20, begin */
            pstDPlmnNPlmnCfgInfo->astDPlmnList[pstDPlmnNPlmnCfgInfo->usDplmnListNum].enType                    = enType;
            /* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-20, end */

            pstDPlmnNPlmnCfgInfo->usDplmnListNum++;

        }

        /* 对数组进行保护，达到最大个数时不再增加 */
        if (pstDPlmnNPlmnCfgInfo->usDplmnListNum >= NAS_MMC_MAX_CFG_DPLMN_NUM)
        {
            /* normal打印 */
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdateDplmnNplmnInfo: usDplmnListNum of pstDPlmnNPlmnCfgInfo is NAS_MMC_MAX_CFG_DPLMN_NUM");
            break;
        }
    }


    /* NV项长度保护 */
    if (pstNvimCfgDPlmnNPlmnInfo->usNplmnListNum > NAS_MMC_NVIM_MAX_CFG_NPLMN_NUM)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdateDplmnNplmnInfo: usNplmnListNum of NVIM is greater than NAS_MMC_NVIM_MAX_CFG_NPLMN_NUM");
        pstNvimCfgDPlmnNPlmnInfo->usNplmnListNum    = NAS_MMC_NVIM_MAX_CFG_NPLMN_NUM;
    }

    for ( ulStep = 0; ulStep < pstNvimCfgDPlmnNPlmnInfo->usNplmnListNum; ulStep++ )
    {
        /* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-20, begin */
        PS_MEM_CPY(stNvimPlmn.aucSimPlmn, pstNvimCfgDPlmnNPlmnInfo->aucNPlmnList + (ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN), NAS_MML_SIM_PLMN_ID_LEN);

        /* 转换PLMN ID为MMC内部的格式并存储 */
        NAS_MMC_ConvertSimPlmnToNasPLMN(&stNvimPlmn, &stTempPlmn);


        /* 存储PLMN对应的RAT */
        usSimRat = (VOS_UINT16)(pstNvimCfgDPlmnNPlmnInfo->aucNPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + NAS_MML_PLMN_WITH_RAT_FIRST_RAT_OFFSET] << NAS_MML_OCTET_MOVE_EIGHT_BITS)
                     | pstNvimCfgDPlmnNPlmnInfo->aucNPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + NAS_MML_PLMN_WITH_RAT_SECOND_RAT_OFFSET];

        enRegDomain = (VOS_UINT8)(pstNvimCfgDPlmnNPlmnInfo->aucNPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + NAS_MML_PLMN_WITH_RAT_UNIT_LEN]);

        enType      = (VOS_UINT8)(pstNvimCfgDPlmnNPlmnInfo->aucNPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + NAS_MMC_DPLMN_NPLMN_NV_PRESETING_FLAG_INDEX]);
        /* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-20, end */

        /* 若是需要添加的NPLMN已经存在，不需要重复添加 */
        if (VOS_TRUE == NAS_MMC_IsPlmnIdWithSimRatInSimPlmnWithRegDomainList(&stTempPlmn, usSimRat, pstDPlmnNPlmnCfgInfo->usNplmnListNum, pstDPlmnNPlmnCfgInfo->astNPlmnList))
        {
            continue;
        }

        if ((VOS_TRUE == NAS_MML_IsPlmnIdValid(&stTempPlmn))
         && (NAS_MML_INVALID_SIM_RAT != usSimRat))
        {
            pstDPlmnNPlmnCfgInfo->astNPlmnList[pstDPlmnNPlmnCfgInfo->usNplmnListNum].stSimPlmnWithRat.stPlmnId = stTempPlmn;
            pstDPlmnNPlmnCfgInfo->astNPlmnList[pstDPlmnNPlmnCfgInfo->usNplmnListNum].stSimPlmnWithRat.usSimRat = usSimRat;
            pstDPlmnNPlmnCfgInfo->astNPlmnList[pstDPlmnNPlmnCfgInfo->usNplmnListNum].enRegDomain = enRegDomain;

            /* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-20, begin */
            pstDPlmnNPlmnCfgInfo->astNPlmnList[pstDPlmnNPlmnCfgInfo->usNplmnListNum].enType                    = enType;
            /* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-20, end */

            pstDPlmnNPlmnCfgInfo->usNplmnListNum++;

        }
        /* 对数组进行保护，达到最大个数时不再增加 */
        if (pstDPlmnNPlmnCfgInfo->usNplmnListNum >= NAS_MMC_MAX_CFG_NPLMN_NUM)
        {
            /* normal打印 */
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdateDplmnNplmnInfo: usNplmnListNum of pstDPlmnNPlmnCfgInfo is NAS_MMC_MAX_CFG_NPLMN_NUM");
            break;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateDPlmnNPlmnCfgHplmnInfo
 功能描述  : 更新DPLMNNPLMN功能控制信息中HPLMN信息
 输入参数  : pstNvimCfgDPlmnNPlmnFlagInfo - nv项里DPLMNNPLMN功能控制相关信息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月8日
    作    者   : c00188733
    修改内容   : 开机漫游搜网项目修改
  2.日    期   : 2015年12月15日
    作    者   : s00217060
    修改内容   : DTS2015120701561:重复的EHPLMN不添加
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateDPlmnNPlmnCfgInfo(
    NAS_MMC_NVIM_DPLMN_NPLMN_CFG_STRU                      *pstNvimDPlmnNPlmnCfg,
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo
)
{

    VOS_UINT32                                              ulStep;
    NAS_MML_PLMN_ID_STRU                                    stTempPlmn;
    NAS_MML_SIM_FORMAT_PLMN_ID                              stNvimPlmn;

    PS_MEM_SET(&stTempPlmn, 0x00, sizeof(stTempPlmn));
    PS_MEM_SET(&stNvimPlmn, 0x00, sizeof(stNvimPlmn));

    /* 将NV中的EHPLMN保存到内存中,需要防止数组越界 */
    if (pstNvimDPlmnNPlmnCfg->ucEHplmnNum > NAS_MMC_MAX_CFG_HPLMN_NUM)
    {
        pstNvimDPlmnNPlmnCfg->ucEHplmnNum = NAS_MMC_MAX_CFG_HPLMN_NUM;
    }

    for (ulStep = 0; ulStep < pstNvimDPlmnNPlmnCfg->ucEHplmnNum; ulStep++)
    {
        PS_MEM_CPY(stNvimPlmn.aucSimPlmn,
            pstNvimDPlmnNPlmnCfg->aucEHplmnList+ (ulStep * NAS_MML_SIM_PLMN_ID_LEN), NAS_MML_SIM_PLMN_ID_LEN);

        /* 转换PLMN ID为MMC内部的格式并存储 */
        NAS_MMC_ConvertSimPlmnToNasPLMN(&stNvimPlmn, &stTempPlmn);

        /* 若是需要添加的EHPLMN已经存在，不需要重复添加 */
        if (VOS_TRUE == NAS_MML_IsSimPlmnIdInDestBcchPlmnList(&stTempPlmn, pstDPlmnNPlmnCfgInfo->ucEHplmnNum, pstDPlmnNPlmnCfgInfo->astEHplmnList))
        {
            continue;
        }

        if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&stTempPlmn))
        {
            pstDPlmnNPlmnCfgInfo->astEHplmnList[pstDPlmnNPlmnCfgInfo->ucEHplmnNum] = stTempPlmn;
            pstDPlmnNPlmnCfgInfo->ucEHplmnNum++;
        }
    }

    PS_MEM_CPY(pstDPlmnNPlmnCfgInfo->aucVersionId, pstNvimDPlmnNPlmnCfg->aucVersionId, NAS_MCC_INFO_VERSION_LEN);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MML_DelPlmnWithRatInPlmnList
 功能描述  : 删除列表中重复PLMN
 输入参数  : NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                   pstPlmnSelectionListInfo
 输出参数  : pstPlmnSelectionListInfo
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月4日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数
  2.日    期   : 2014年5月28日
    作    者   : z00234330
    修改内容   : covertity修改

*****************************************************************************/
VOS_VOID  NAS_MMC_DelDuplicatedPlmnWithRatInPlmnList (
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;

    /* modified by z00234330 for coverity修改 2014-05-28 begin */
    /* 删除重复的PLMN */
    for (i = 0; i < NAS_MML_MIN(pstPlmnSelectionListInfo->usSearchPlmnNum, NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST); )
    {
        for (j = 0; j < pstPlmnSelectionListInfo->astPlmnSelectionList[i].ucRatNum; )
        {
            if (VOS_TRUE == NAS_MMC_IsPlmnWithRatInPlmnList(&(pstPlmnSelectionListInfo->astPlmnSelectionList[i].stPlmnId),
                                                            pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j].enRatType,
                                                            pstPlmnSelectionListInfo,
                                                            i))
            {
                /* 删除相应的RAT */
                /*lint -e961*/
                (VOS_VOID)PS_MEM_MOVE(&(pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j]),
                            &(pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j + 1]),
                            ((pstPlmnSelectionListInfo->astPlmnSelectionList[i]).ucRatNum - j - 1) * sizeof(NAS_MMC_PLMN_RAT_INFO_STRU));
                /*lint +e961*/

                pstPlmnSelectionListInfo->astPlmnSelectionList[i].ucRatNum--;

            }
            else
            {
                j++;
            }
        }

        /* 接入技术个数为0时，删除相应的PLMN ID */
        if (0 == pstPlmnSelectionListInfo->astPlmnSelectionList[i].ucRatNum)
        {
            /*lint -e961*/
            (VOS_VOID)PS_MEM_MOVE(&(pstPlmnSelectionListInfo->astPlmnSelectionList[i]),
                        &(pstPlmnSelectionListInfo->astPlmnSelectionList[i + 1]),
                        (pstPlmnSelectionListInfo->usSearchPlmnNum - i - 1) * sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));
            /*lint +e961*/
            pstPlmnSelectionListInfo->usSearchPlmnNum--;
        }
        else
        {
            i++;
        }
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection
 功能描述  : 确定当前是否为用户指定搜网
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月22日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId,
    VOS_UINT32                          ulEventType
)
{
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    if ( ( NAS_MMC_FSM_PLMN_SELECTION == enFsmId )
      && ( ulEventType == NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ )))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
	/* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetCurrentLaiForbbidenTypeForUserSpecPlmnSrch
 功能描述  : 在用户手动搜网时，判断当前LAI的禁止类型
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年09月13日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetCurrentLaiForbbidenTypeForUserSpecPlmnSrch(VOS_VOID)
{
    NAS_MML_LAI_STRU                                       *pstCurrentLai     = VOS_NULL_PTR;
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU               *pstForbRoamLaInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                                   *pstForbGprsPlmn   = VOS_NULL_PTR;
    NAS_MMC_FSM_EXTRA_CTX_UNION                            *punParentFsmCtx   = VOS_NULL_PTR;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enParentFsmId;
    VOS_UINT32                                              ulPlmnLaType;
    VOS_UINT32                                              ulRlst;

    ulPlmnLaType      = NAS_MML_PLMN_FORBID_NULL;
    pstCurrentLai     = NAS_MML_GetCurrCampLai();
    enParentFsmId     = NAS_MMC_GetParentFsmId();
    punParentFsmCtx   = NAS_MMC_GetParentFsmCtx();

    /* 如果当前状态机是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION == NAS_MMC_GetCurrFsmId())
    {
        pstForbRoamLaInfo = NAS_MMC_GetForbRoamLaInfo_PlmnSelection();
        pstForbGprsPlmn   = NAS_MMC_GetForbPlmnForGrpsInfo_PlmnSelection();
    }

    /* 当前父状态机是选网状态机，且当前的父状态机的上下文内容存在，则取父状态的相关禁止信息 */
    else if ( (NAS_MMC_FSM_PLMN_SELECTION == enParentFsmId)
           && (VOS_NULL_PTR               != punParentFsmCtx) )
    {
        pstForbRoamLaInfo = &(punParentFsmCtx->stPlmnSelectionCtx.stForbRoamLaInfo);
        pstForbGprsPlmn   = &(punParentFsmCtx->stPlmnSelectionCtx.stForbGprsPlmn);
    }
    else
    {
        /* 当前父状态机不是选网状态机，或者当前的父状态机的上下文内容为空，直接异常返回 */
        return ulPlmnLaType;
    }

    /* 是否在 ForbLA消息中 */
    ulRlst =  NAS_MML_IsLaiInDestLaiList(pstCurrentLai,
                                        pstForbRoamLaInfo->ucForbRoamLaNum,
                                        pstForbRoamLaInfo->astForbRomLaList);

    if(VOS_TRUE == ulRlst)
    {
         ulPlmnLaType  |=   NAS_MML_PLMN_FORBID_ROAM_LA;
    }


    /* 在forbid plmn for gprs列表中 */
    ulRlst = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(NAS_MML_GetCurrCampPlmnId(),
                                                   1,
                                                   pstForbGprsPlmn);
    if(VOS_TRUE == ulRlst)
    {
        ulPlmnLaType  |=   NAS_MML_PLMN_FORBID_PLMN_FOR_GPRS;
    }

    return ulPlmnLaType;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsSpecTypePlmnIdInDestPlmnList
 功能描述  : 判断指定类型功能的PLMN ID是否在列表中
 输入参数  : stSpecPlmnId:     需要判断的PLMN ID
              enSpecPlmnType:   PLMN ID的类型
              ucPlmnNum:        列表中plmn id的个数
              pstPlmnIdList:    plmn列表
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
VOS_UINT32 NAS_MMC_IsSpecTypePlmnIdInDestPlmnList (
    NAS_MML_PLMN_ID_STRU               *pstSpecPlmnId,
    NAS_MMC_PLMN_TYPE_ENUM_UINT8        enSpecPlmnType,
    VOS_UINT8                           ucPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstPlmnIdList
)
{
    /* 若指定的PLMN类型为H/U/O,则使用Sim类型的PLMN来判断当前PLMNID是否在
        网络列表中 */
    if ( (NAS_MMC_PLMN_TYPE_HPLMN  == enSpecPlmnType)
      || (NAS_MMC_PLMN_TYPE_UPLMN  == enSpecPlmnType)
      || (NAS_MMC_PLMN_TYPE_OPLMN  == enSpecPlmnType) )
    {
        if ( VOS_TRUE == NAS_MML_IsSimPlmnIdInDestBcchPlmnList(pstSpecPlmnId,
                                                               ucPlmnNum,
                                                               pstPlmnIdList) )
        {
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }

    /* 若指定的PLMN类型不为H/U/O,则使用BCCH类型的PLMN来判断当前PLMNID是否在
        网络列表中 */
    if ( VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstSpecPlmnId,
                                                           ucPlmnNum,
                                                           pstPlmnIdList) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}




/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateCsPsRestriction_WasInfo
 功能描述  : 更新WAS下的AccessBar信息以及Bar状态变化信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月21日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2012年2月15日
    作    者   : w00166186
    修改内容   : CSFB&PPAC&ETWS&ISR 开发
  3.日    期   : 2012年12月11日
    作    者   : w00176964
    修改内容   : 更新小区禁止正常业务标记
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateCsPsRestriction_WasInfo(
    RRMM_SYS_INFO_IND_STRU             *pstWrrSysInfo,
    NAS_MML_NETWORK_INFO_STRU          *pstNetWorkInfo
)
{
    /* 设置当前的Cs允许注册的变换标识 */
    pstNetWorkInfo->stCsDomainInfo.ulCsRegisterBarToUnBarFlag   = VOS_FALSE;
    /* 设置当前的Ps允许注册的变换标识 */
    pstNetWorkInfo->stPsDomainInfo.ulPsRegisterBarToUnBarFlag   = VOS_FALSE;

    if (VOS_FALSE == pstWrrSysInfo->stCsRestriction.enRestrictRegister)
    {
        if (VOS_TRUE == pstNetWorkInfo->stCsDomainInfo.stCsAcRestriction.ucRestrictRegister)
        {
            /* 设置当前的Cs允许注册的变换标识 */
            pstNetWorkInfo->stCsDomainInfo.ulCsRegisterBarToUnBarFlag   = VOS_TRUE;
        }
    }

    if (VOS_FALSE == pstWrrSysInfo->stPsRestriction.enRestrictRegister)
    {
        if (VOS_TRUE == pstNetWorkInfo->stPsDomainInfo.stPsAcRestriction.ucRestrictRegister)
        {
            /* 设置当前的Ps允许注册的变换标识 */
            pstNetWorkInfo->stPsDomainInfo.ulPsRegisterBarToUnBarFlag   = VOS_TRUE;
        }
    }

    /* 保存CS接入受限信息 */
    NAS_MML_SetCsRestrictRegisterFlg(pstWrrSysInfo->stCsRestriction.enRestrictRegister);
    NAS_MML_SetCsRestrictPagingFlg(pstWrrSysInfo->stCsRestriction.enRestrictPagingRsp);
    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
    NAS_MML_SetCsRestrictNormalServiceFlg(pstWrrSysInfo->stCsRestriction.enRestrictNormalService);
    NAS_MML_SetCsRestrictEmergencyServiceFlg(pstWrrSysInfo->stCsRestriction.enRestrictEmergencyService);
    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */


    /* 保存PS接入受限信息 */
    NAS_MML_SetPsRestrictRegisterFlg(pstWrrSysInfo->stPsRestriction.enRestrictRegister);
    NAS_MML_SetPsRestrictPagingFlg(pstWrrSysInfo->stPsRestriction.enRestrictPagingRsp);
    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
    NAS_MML_SetPsRestrictNormalServiceFlg(pstWrrSysInfo->stPsRestriction.enRestrictNormalService);
    NAS_MML_SetPsRestrictEmergencyServiceFlg(pstWrrSysInfo->stPsRestriction.enRestrictEmergencyService);
    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */

    return;
}






/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateCsPsRestriction_GasSysInfo
 功能描述  : 更新GAS下的Restriction信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月21日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2012年2月15日
    作    者   : w00166186
    修改内容   : CSFB&PPAC&ETWS&ISR 开发
  3.日    期   : 2012年12月11日
    作    者   : w00176964
    修改内容   : 更新小区禁止正常业务标记
  4.日    期   : 2012年12月27日
    作    者   : s00217060
    修改内容   : for DSDA GUNAS C CORE:如果USIM卡GSM禁止接入，设置限制注册和正常呼叫接入
  5.日    期   : 2013年1月8日
    作    者   : w00176964
    修改内容   : DTS2013010706340:G下无PS域紧急呼叫业务,G下接入禁止时该标记应该始终为FALSE
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateCsPsRestriction_GasSysInfo(
    GRRMM_SYS_INFO_IND_ST              *pstGrrSysInfo,
    NAS_MML_NETWORK_INFO_STRU          *pstNetWorkInfo
)
{
    /* GSM下无分域阻塞,全局变量复位， */
    pstNetWorkInfo->stCsDomainInfo.ulCsRegisterBarToUnBarFlag = VOS_FALSE;
    pstNetWorkInfo->stPsDomainInfo.ulPsRegisterBarToUnBarFlag = VOS_FALSE;

    /* 更新CS/PS 是否允许注册的标志 */
    switch (pstGrrSysInfo->unAcInfo.ucRestrictType)
    {
        case RRC_NAS_ACCESS_RESTRICTION_ALL_SERVICE:
            {
                /* 保存CS接入受限信息 */
                NAS_MML_SetCsRestrictRegisterFlg(VOS_TRUE);
                NAS_MML_SetCsRestrictPagingFlg(VOS_TRUE);
                NAS_MML_SetCsRestrictNormalServiceFlg(VOS_TRUE);
                NAS_MML_SetCsRestrictEmergencyServiceFlg(VOS_TRUE);

                /* 保存PS接入受限信息 */
                NAS_MML_SetPsRestrictRegisterFlg(VOS_TRUE);
                NAS_MML_SetPsRestrictPagingFlg(VOS_TRUE);
                NAS_MML_SetPsRestrictNormalServiceFlg(VOS_TRUE);
            }
            break;
        case RRC_NAS_ACCESS_NO_RESTRICTION:
            {
                if (VOS_TRUE == pstNetWorkInfo->stCsDomainInfo.stCsAcRestriction.ucRestrictRegister)
                {
                    /* 设置当前的Cs允许注册的变换标识 */
                    pstNetWorkInfo->stCsDomainInfo.ulCsRegisterBarToUnBarFlag   = VOS_TRUE;
                }


                if (VOS_TRUE == pstNetWorkInfo->stPsDomainInfo.stPsAcRestriction.ucRestrictRegister)
                {
                    /* 设置当前的Ps允许注册的变换标识 */
                    pstNetWorkInfo->stPsDomainInfo.ulPsRegisterBarToUnBarFlag   = VOS_TRUE;
                }

                /* 保存CS接入受限信息 */
                NAS_MML_SetCsRestrictRegisterFlg(VOS_FALSE);
                NAS_MML_SetCsRestrictPagingFlg(VOS_FALSE);
                NAS_MML_SetCsRestrictNormalServiceFlg(VOS_FALSE);
                NAS_MML_SetCsRestrictEmergencyServiceFlg(VOS_FALSE);

                /* 保存PS接入受限信息 */
                NAS_MML_SetPsRestrictRegisterFlg(VOS_FALSE);
                NAS_MML_SetPsRestrictPagingFlg(VOS_FALSE);
                NAS_MML_SetPsRestrictNormalServiceFlg(VOS_FALSE);
            }
            break;

        case RRC_NAS_ACCESS_RESTRICTION_NORMAL_SERVICE:
            {
                /* 保存CS接入受限信息 */
                NAS_MML_SetCsRestrictRegisterFlg(VOS_TRUE);
                NAS_MML_SetCsRestrictPagingFlg(VOS_TRUE);
                NAS_MML_SetCsRestrictNormalServiceFlg(VOS_TRUE);
                NAS_MML_SetCsRestrictEmergencyServiceFlg(VOS_FALSE);

                /* 保存PS接入受限信息 */
                NAS_MML_SetPsRestrictRegisterFlg(VOS_TRUE);
                NAS_MML_SetPsRestrictPagingFlg(VOS_TRUE);
                NAS_MML_SetPsRestrictNormalServiceFlg(VOS_TRUE);
            }
            break;

        case RRC_NAS_ACCESS_RESTRICTION_EMERGENCY_SERVICE:
            {
                /* 保存CS接入受限信息 */
                NAS_MML_SetCsRestrictRegisterFlg(VOS_FALSE);
                NAS_MML_SetCsRestrictPagingFlg(VOS_FALSE);
                NAS_MML_SetCsRestrictNormalServiceFlg(VOS_FALSE);
                NAS_MML_SetCsRestrictEmergencyServiceFlg(VOS_TRUE);

                /* 保存PS接入受限信息 */
                NAS_MML_SetPsRestrictRegisterFlg(VOS_FALSE);
                NAS_MML_SetPsRestrictPagingFlg(VOS_FALSE);
                NAS_MML_SetPsRestrictNormalServiceFlg(VOS_FALSE);
            }
            break;

        default:
            break;

    }

    /* PS无紧急业务，该值始终不受限 */
    NAS_MML_SetPsRestrictEmergencyServiceFlg(VOS_FALSE);

    /* USIM卡禁止GSM接入时，也需要更新CS/PS 是否允许注册的标志 */
    if (VOS_TRUE == NAS_MML_GetGsmForbidFlg())
    {
        /* 设置当前的Cs允许注册的变换标识 */
        pstNetWorkInfo->stCsDomainInfo.ulCsRegisterBarToUnBarFlag   = VOS_FALSE;

        /* 设置当前的Ps允许注册的变换标识 */
        pstNetWorkInfo->stPsDomainInfo.ulPsRegisterBarToUnBarFlag   = VOS_FALSE;

        /* 保存CS接入受限信息 */
        NAS_MML_SetCsRestrictRegisterFlg(VOS_TRUE);
        NAS_MML_SetCsRestrictPagingFlg(VOS_TRUE);
        NAS_MML_SetCsRestrictNormalServiceFlg(VOS_TRUE);

        /* 保存PS接入受限信息 */
        NAS_MML_SetPsRestrictRegisterFlg(VOS_TRUE);
        NAS_MML_SetPsRestrictPagingFlg(VOS_TRUE);
        NAS_MML_SetPsRestrictNormalServiceFlg(VOS_TRUE);
        NAS_MML_SetPsRestrictEmergencyServiceFlg(VOS_FALSE);

    }


    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateCsPsRestriction_WasInfo
 功能描述  : 更新WAS下的AccessBar信息以及Bar状态变化信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月21日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2012年2月15日
    作    者   : w00166186
    修改内容   : CSFB&PPAC&ETWS&ISR 开发
  3.日    期   : 2012年12月11日
    作    者   : w00176964
    修改内容   : 更新小区禁止正常业务标记
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateCsPsRestriction_AcChangeInd(
    RRMM_W_AC_INFO_CHANGE_IND_STRU     *pstWAcChangeInd,
    NAS_MML_NETWORK_INFO_STRU          *pstNetWorkInfo
)
{

    /* 设置当前的Cs允许注册的变换标识 */
    pstNetWorkInfo->stCsDomainInfo.ulCsRegisterBarToUnBarFlag   = VOS_FALSE;

    /* 设置当前的Ps允许注册的变换标识 */
    pstNetWorkInfo->stPsDomainInfo.ulPsRegisterBarToUnBarFlag   = VOS_FALSE;

    if (VOS_FALSE == pstWAcChangeInd->stCsRestriction.enRestrictRegister)
    {
        if (VOS_TRUE == pstNetWorkInfo->stCsDomainInfo.stCsAcRestriction.ucRestrictRegister)
        {
            /* 设置当前的Cs允许注册的变换标识 */
            pstNetWorkInfo->stCsDomainInfo.ulCsRegisterBarToUnBarFlag   = VOS_TRUE;
        }
    }

    if (VOS_FALSE == pstWAcChangeInd->stPsRestriction.enRestrictRegister)
    {
        if (VOS_TRUE == pstNetWorkInfo->stPsDomainInfo.stPsAcRestriction.ucRestrictRegister)
        {
            /* 设置当前的Ps允许注册的变换标识 */
            pstNetWorkInfo->stPsDomainInfo.ulPsRegisterBarToUnBarFlag   = VOS_TRUE;
        }
    }

    /* 保存CS接入受限信息 */
    NAS_MML_SetCsRestrictRegisterFlg(pstWAcChangeInd->stCsRestriction.enRestrictRegister);
    NAS_MML_SetCsRestrictPagingFlg(pstWAcChangeInd->stCsRestriction.enRestrictPagingRsp);
    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
    NAS_MML_SetCsRestrictNormalServiceFlg(pstWAcChangeInd->stCsRestriction.enRestrictNormalService);
    NAS_MML_SetCsRestrictEmergencyServiceFlg(pstWAcChangeInd->stCsRestriction.enRestrictEmergencyService);
    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */

    /* 保存PS接入受限信息 */
    NAS_MML_SetPsRestrictRegisterFlg(pstWAcChangeInd->stPsRestriction.enRestrictRegister);
    NAS_MML_SetPsRestrictPagingFlg(pstWAcChangeInd->stPsRestriction.enRestrictPagingRsp);
    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
    NAS_MML_SetPsRestrictNormalServiceFlg(pstWAcChangeInd->stPsRestriction.enRestrictNormalService);
    NAS_MML_SetPsRestrictEmergencyServiceFlg(pstWAcChangeInd->stPsRestriction.enRestrictEmergencyService);
    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertRrcRatToNasFormat
 功能描述  : 将接入层带上的接入技术类型转换为NAS格式的接入技术类型
 输入参数  : ulRrcRat 接入层带上来的接入技术类型
 输出参数  : enRat NAS格式的接入技术类型
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月30日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_ConvertRrcRatToNasFormat(
    RRC_NAS_RAT_TYPE_ENUM_UINT32        ulRrcRat,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    *penRat
)
{
    switch (ulRrcRat)
    {
        case RRC_NAS_RAT_WCDMA_FDD:

            *penRat = NAS_MML_NET_RAT_TYPE_WCDMA;
            break;

        case RRC_NAS_RAT_GSM:

            *penRat = NAS_MML_NET_RAT_TYPE_GSM;
            break;

        case RRC_NAS_RAT_LTE:

            *penRat = NAS_MML_NET_RAT_TYPE_LTE;
            break;

        default:

            /* 异常打印 */
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ConvertRrcRatToNasFormat,Unexpected Rrc rat!");
            *penRat = NAS_MML_NET_RAT_TYPE_BUTT;
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertNasRatToRrcFormat
 功能描述  : 将NAS格式的接入技术类型转换为接入层带上的接入技术类型
 输入参数  : enNasRat NAS格式的接入技术类型
 输出参数  : penRrcRat 接入层带上来的接入技术类型
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年10月24日
   作    者   : w00242748
   修改内容   : 新生成函数

 2.日    期   : 2013年10月29日
   作    者   : w00167002
   修改内容   : BUTT-->转换为给接入层的BUTT
*****************************************************************************/
VOS_VOID NAS_MMC_ConvertNasRatToRrcFormat(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNasRat,
    RRC_NAS_RAT_TYPE_ENUM_UINT32       *penRrcRat
)
{
    switch (enNasRat)
    {
        case NAS_MML_NET_RAT_TYPE_GSM:
            *penRrcRat = RRC_NAS_RAT_GSM;
            break;

        case NAS_MML_NET_RAT_TYPE_WCDMA:
            *penRrcRat = RRC_NAS_RAT_WCDMA_FDD;
            break;

        case NAS_MML_NET_RAT_TYPE_LTE:
            *penRrcRat = RRC_NAS_RAT_LTE;
            break;

        default:

            /* 异常打印 */
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ConvertRrcRatToNasFormat,Unexpected Nas rat!");

            *penRrcRat = RRC_NAS_RAT_TYPE_BUTT;

            break;
    }

    return;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertRrcCoverTypeToNasFormat
 功能描述  : 将接入层带上的网络覆盖类型转换为NAS格式的网络覆盖类型
 输入参数  : enRrcCoverType 接入层带上来的网络覆盖类型
 输出参数  : *penCoverType NAS格式的网络覆盖类型
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年11月5日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID   NAS_MMC_ConvertRrcCoverTypeToNasFormat(
    RRC_NAS_COVERAGE_TYPE_ENUM_UINT32   enRrcCoverType,
    NAS_MMC_COVERAGE_TYPE_ENUM_UINT8   *penCoverType
)
{
    switch (enRrcCoverType)
    {
        case RRC_NAS_COVERAGE_TYPE_NONE:

            *penCoverType = NAS_MMC_COVERAGE_TYPE_NONE;
            break;

        case RRC_NAS_COVERAGE_TYPE_LOW:

            *penCoverType = NAS_MMC_COVERAGE_TYPE_LOW;
            break;

        case RRC_NAS_COVERAGE_TYPE_HIGH:

            *penCoverType = NAS_MMC_COVERAGE_TYPE_HIGH;
            break;

        default:

            /* 异常打印 */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ConvertRrcCoverTypeToNasFormat,Unexpected Rrc coverage type!");
            *penCoverType = NAS_MMC_COVERAGE_TYPE_BUTT;
            break;
    }

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertLmmCoverTypeToNasFormat
 功能描述  : 将接入层带上的网络覆盖类型转换为NAS格式的网络覆盖类型
 输入参数  : enLmmCoverType 接入层带上来的网络覆盖类型
 输出参数  : *penCoverType NAS格式的网络覆盖类型
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年11月5日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID   NAS_MMC_ConvertLmmCoverTypeToNasFormat(
    MMC_LMM_COVERAGE_TYPE_ENUM_UINT32   enLmmCoverType,
    NAS_MMC_COVERAGE_TYPE_ENUM_UINT8   *penCoverType
)
{
    switch (enLmmCoverType)
    {
        case MMC_LMM_COVERAGE_TYPE_NONE:

            *penCoverType = NAS_MMC_COVERAGE_TYPE_NONE;
            break;

        case MMC_LMM_COVERAGE_TYPE_LOW:

            *penCoverType = NAS_MMC_COVERAGE_TYPE_LOW;
            break;

        case MMC_LMM_COVERAGE_TYPE_HIGH:

            *penCoverType = NAS_MMC_COVERAGE_TYPE_HIGH;
            break;

        default:

            /* 异常打印 */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ConvertLmmCoverTypeToNasFormat,Unexpected Rrc coverage type!");
            *penCoverType = NAS_MMC_COVERAGE_TYPE_BUTT;
            break;
    }

    return;
}
#endif



#if (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertLmmRatToRrcFormat
 功能描述  : 将LMM层带上的接入技术类型转换为RRC格式的接入技术类型
 输入参数  : ulLmmRat 接入层带上来的接入技术类型
 输出参数  : enRat RRC格式的接入技术类型
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年4月28日
   作    者   : t00212959
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_ConvertLmmRatToRrcFormat(
    MMC_LMM_RAT_TYPE_ENUM_UINT8         ucLmmRat,
    RRC_NAS_RAT_TYPE_ENUM_UINT32       *penRat
)
{
    switch (ucLmmRat)
    {
        case MMC_LMM_RAT_WCDMA_FDD:
            *penRat = RRC_NAS_RAT_WCDMA_FDD;
            break;

        case MMC_LMM_RAT_GSM:
            *penRat = RRC_NAS_RAT_GSM;
            break;

        case MMC_LMM_RAT_LTE:
            *penRat = RRC_NAS_RAT_LTE;
            break;

        default:

            /* 异常打印 */
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ConvertLmmRatToRrcFormat,Unexpected Rrc rat!");
            *penRat = RRC_NAS_RAT_TYPE_BUTT;
            break;
    }

    return;
}

#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertGasNetModeToMmlNetMode
 功能描述  : 将GAS的系统消息中网络模式参数转为MML中的网络模式类型
 输入参数  : enGasNetMode: GAS系统消息中的网络模式
 输出参数  : 无
 返 回 值  : MML中的网络模式类型
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年8月5日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_NET_MODE_ENUM_UINT8 NAS_MMC_ConvertGasNetModeToMmlNetMode(
    GRRMM_NW_OP_MODE_ENUM_UINT8         enGasNetMode
)
{
    NAS_MML_NET_MODE_ENUM_UINT8         enMmlNetMode;

    switch ( enGasNetMode )
    {
        case GRRMM_NW_OP_MODE_I:
            enMmlNetMode = NAS_MML_NET_MODE_I;
            break;

        case GRRMM_NW_OP_MODE_II:
            enMmlNetMode = NAS_MML_NET_MODE_II;
            break;

        case GRRMM_NW_OP_MODE_III:
            enMmlNetMode = NAS_MML_NET_MODE_III;
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ConvertGasNetModeToMmlNetMode, net mode invalid");
            enMmlNetMode = NAS_MML_NET_MODE_BUTT;
            break;
    }

    return enMmlNetMode;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsOptItemVaild_WasSysInfo
 功能描述  : WAS 系统消息中携带的Opt项参数是否有效
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月21日
    作    者   : l00130025
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsOptItemVaild_WasSysInfo(
    RRMM_SYS_INFO_IND_STRU             *pstWrrSysInfo
)
{
    if ((0 == pstWrrSysInfo->ucCnCommonSize)
     && (0 == pstWrrSysInfo->ucCsInfoSize)
     && (0 == pstWrrSysInfo->ucPsInfoSize)
     && (0 == pstWrrSysInfo->bitOpPlmnId)
     && (0 == pstWrrSysInfo->bitOpCsDrx)
     && (0 == pstWrrSysInfo->bitOpPsDrx))
    {
        return VOS_FALSE;
    }

    if ((RRC_NAS_MAX_SIZE_NAS_GSM_MAP < pstWrrSysInfo->ucCnCommonSize)
     || (RRC_NAS_MAX_SIZE_NAS_GSM_MAP < pstWrrSysInfo->ucCsInfoSize)
     || (RRC_NAS_MAX_SIZE_NAS_GSM_MAP < pstWrrSysInfo->ucPsInfoSize))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedEnableUtran_AnyCellSearch
 功能描述  : 进入Anycell搜网状态机后，如果Utran被Disable,需要重新Enable Utran，UE能够在Utran上限制驻留
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
VOS_UINT32 NAS_MMC_IsNeedEnableUtran_AnyCellSearch (VOS_VOID)
{
    /* 当处于Anycell搜网状态机时并且当前Utran被Disable了，则Re-Enable Utran */

    if (NAS_MMC_FSM_ANYCELL_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        return VOS_FALSE;
    }

    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE != NAS_MML_GetUtranForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedDisableUtran_RcvGasSysInfo
 功能描述  : 收到GAS系统消息的时候，如果这时UTRAN是Re-Enable状态，则将UTRAN重新Disable
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
VOS_UINT32 NAS_MMC_IsNeedDisableUtran_RcvGasSysInfo (VOS_VOID)
{
    /* 如果Utran在禁止接入技术列表里且此时Utran为Enable状态，则收到Gas的系统消息后Disable Utran */
    if (VOS_FALSE == NAS_MML_IsRatInForbiddenList(NAS_MML_NET_RAT_TYPE_WCDMA))
    {
        return VOS_FALSE;
    }

    if (NAS_MML_RAT_CAPABILITY_STATUS_REENABLE != NAS_MML_GetUtranForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateUtranCapabilityStatus_AnyCellSearch_Init
 功能描述  : 开始Anycell搜网前，如果Utran被Disable,则需要重新Enable Utran
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
VOS_VOID NAS_MMC_UpdateUtranCapabilityStatus_AnyCellSearch_Init (VOS_VOID)
{
    if (VOS_TRUE == NAS_MMC_IsNeedEnableUtran_AnyCellSearch())
    {
        NAS_MML_SetUtranForbiddenStatusFlg(NAS_MML_RAT_CAPABILITY_STATUS_REENABLE);
        NAS_MMC_SndAsRatCapabilityStatusChangeInfo();
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus
 功能描述  : 收到GAS系统消息的时候，如果这时UTRAN是Re-Enable状态，则将UTRAN重新Disable
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
VOS_VOID NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus (VOS_VOID)
{

    if (VOS_TRUE == NAS_MMC_IsNeedDisableUtran_RcvGasSysInfo())
    {
        NAS_MML_SetUtranForbiddenStatusFlg(NAS_MML_RAT_CAPABILITY_STATUS_DISABLE);
        NAS_MMC_SndAsRatCapabilityStatusChangeInfo();
    }

}


/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateOperNameInfo
 功能描述  : 更新Operate Name的信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月8日
    作    者   : l00130025
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_UpdateOperNameInfo(
    RRC_PLMN_ID_STRU                   *pstPlmnId
)
{
    NAS_MML_OPERATOR_NAME_INFO_STRU    *pstOperNameInfo = VOS_NULL_PTR;

    /* 更新当前驻留网络信息 */
    pstOperNameInfo = NAS_MML_GetOperatorNameInfo();

    /* 如果保存的长短网络名与当前驻留的PLMN ID不同，清除全局变量 */
    if ((pstOperNameInfo->stOperatorPlmnId.ulMcc != pstPlmnId->ulMcc)
     || (pstOperNameInfo->stOperatorPlmnId.ulMnc != pstPlmnId->ulMnc))
    {
        /* 清空aucOperatorNameShort和aucOperatorNameLong */
        PS_MEM_SET(pstOperNameInfo, 0x00, sizeof(NAS_MML_OPERATOR_NAME_INFO_STRU));
        pstOperNameInfo->stOperatorPlmnId.ulMcc = pstPlmnId->ulMcc;
        pstOperNameInfo->stOperatorPlmnId.ulMnc = pstPlmnId->ulMnc;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateNetworkInfo_GasSysInfo
 功能描述  : 检查并保存GSM下的系统信息
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月21日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2011年11月15日
    作    者   : w00166186
    修改内容   : DTS2011111500751,LAC值高低位保存反了，导致发给接入层的禁止LAC值不正确
  3.日    期   : 2012年6月9日
    作    者   : z00161729
    修改内容   : V7R1C50 GUL背景搜网修改
  4.日    期   : 2012年11月13日
    作    者   : z40661
    修改内容   : V7R1C50 GUL背景搜网修改

  5.日    期   : 2013年6月25日
    作    者   : w00167002
    修改内容   : V9R1_SVLTE ST测试:更新PS域的GPRS是否支持标志。

  6.日    期   : 2013年10月29日
    作    者   : z00234330
    修改内容   : 低功耗接口合入dts2013102911530
  7.日    期   : 2014年2月14日
    作    者   : s00246516
    修改内容   : L-C互操作项目:增加获取和注册请求的处理
  8.日   期    : 2014-04-15
    作   者    : w00176964
    修改内容   : V3R3C60_eCall项目调整:上次驻留LAI信息保存到MML中
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateNetworkInfo_GasSysInfo(
    struct MsgCB                       *pstMsg
)
{
    GRRMM_SYS_INFO_IND_ST              *pstGrrSysInfo       = VOS_NULL_PTR;
    NAS_MML_NETWORK_3GPP_REL_STRU      *pst3GPPRelVersion   = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCurrCampPlmnInfo = VOS_NULL_PTR;
    NAS_MML_MS_BAND_INFO_STRU          *pstBandInfo         = VOS_NULL_PTR;
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-4-28, begin */
    NAS_MML_LAI_STRU                   *pstOldCampLai       = VOS_NULL_PTR;
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-4-28, end */


    NAS_MML_NETWORK_INFO_STRU          *pstNetWorkInfo      = VOS_NULL_PTR;

    pstNetWorkInfo  =  NAS_MML_GetNetworkInfo();

    pstGrrSysInfo     = (GRRMM_SYS_INFO_IND_ST *)pstMsg;
    pst3GPPRelVersion = NAS_MML_GetNetwork3GppRel();

    pst3GPPRelVersion->enNetSgsnRel = pstGrrSysInfo->ucSgsnRelease;
    pst3GPPRelVersion->enNetMscRel  = pstGrrSysInfo->ucMsrRelease;

    pstCurrCampPlmnInfo = NAS_MML_GetCurrCampPlmnInfo();

    /* Added by w00176964 for V3R3C60_eCall项目, 2014-4-28, begin */
    pstOldCampLai       = NAS_MML_GetOldCampLai();

    /* 保存上次驻留的LAI信息,然后下面步骤更新当前驻留LAI信息 */
    if (VOS_FALSE == NAS_MMC_IsInValidCampPlmn())
    {
        PS_MEM_CPY(pstOldCampLai, &(pstCurrCampPlmnInfo->stLai), sizeof(NAS_MML_LAI_STRU));
    }
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-4-28, end */

    /* 当前ucGprsSupportInd为Gsm时，代表当前不支持GPRS，无法从PS域信息中获取网络模式 */
    if (NAS_MML_GAS_SUBMODE_GSM == pstGrrSysInfo->ucGprsSupportInd)
    {
        /* 设置当前网络模式为无效NAS_MML_NET_MODE_BUTT */
        pstCurrCampPlmnInfo->enNetworkMode = NAS_MML_NET_MODE_BUTT;

        pstCurrCampPlmnInfo->ucRac = NAS_MML_RAC_INVALID;
    }
    else
    {
        /* 更新网络模式 ，只有在PS域信息有效的情况下，网络模式才有效 */
        if (GRRMM_NW_OP_MODE_INVALID != pstGrrSysInfo->ucNetworkOperationMode)
        {
            pstCurrCampPlmnInfo->enNetworkMode =
                NAS_MMC_ConvertGasNetModeToMmlNetMode(pstGrrSysInfo->ucNetworkOperationMode);
        }

        pstCurrCampPlmnInfo->ucRac                = pstGrrSysInfo->ucRac;
    }

    /* 根据GAS上报的GPRS支持指示，转换为相应的系统子模式 */
    pstCurrCampPlmnInfo->enSysSubMode = NAS_MML_ConvertGprsSupportIndToSysSubMode(pstGrrSysInfo->ucGprsSupportInd);

    /* 更新网路的运营商名称信息 */
    NAS_MMC_UpdateOperNameInfo(&(pstGrrSysInfo->PlmnId));

    /* 更新当前驻留网络信息 */
    pstCurrCampPlmnInfo->stLai.stPlmnId.ulMcc = pstGrrSysInfo->PlmnId.ulMcc;
    pstCurrCampPlmnInfo->stLai.stPlmnId.ulMnc = pstGrrSysInfo->PlmnId.ulMnc;

    pstCurrCampPlmnInfo->stLai.enCampPlmnNetRat = NAS_MML_NET_RAT_TYPE_GSM;

    /* 更新当前驻留网络的LAC和RAC信息 */
    pstCurrCampPlmnInfo->stLai.aucLac[0]      = (VOS_UINT8)((pstGrrSysInfo->usLac & 0xFF00) >> 8);
    pstCurrCampPlmnInfo->stLai.aucLac[1]      = (VOS_UINT8)(pstGrrSysInfo->usLac & 0x00FF);


    /* 从小区中获取GPRS支持信息 */
    pstNetWorkInfo->stPsDomainInfo.ucPsSupportFlg = pstGrrSysInfo->ucGprsSupportInd;

    /* 更新cell Info */
    pstCurrCampPlmnInfo->stCampCellInfo.ucCellNum = 1;
    pstCurrCampPlmnInfo->stCampCellInfo.astCellInfo[0].ulCellId = pstGrrSysInfo->usCellId;

    /* Added by s00246516 for L-C互操作项目, 2014-02-14, Begin */
    NAS_MML_SetCurrCampArfcn(0x0);
    /* Added by s00246516 for L-C互操作项目, 2014-02-14, End */

    /* 更新当前的系统GsmBand信息，W,L 驻留 Band为0 */
    pstBandInfo = NAS_MML_GetCurrBandInfo();
    pstBandInfo->unWcdmaBand.ulBand      = 0;
    pstBandInfo->unGsmBand.ulBand        = pstGrrSysInfo->unGsmBand.ulBand;
#if (FEATURE_ON == FEATURE_LTE)
    pstBandInfo->stLteBand.aulLteBand[0] = 0;
    pstBandInfo->stLteBand.aulLteBand[1] = 0;
#endif

    /* 更新当前网络的 CS/PS域的分组域阻塞情况 */
    NAS_MMC_UpdateCsPsRestriction_GasSysInfo(pstGrrSysInfo, NAS_MML_GetNetworkInfo());
    OM_DelDrxTimerWakeSrc(VOS_GetModemIDFromPid(WUEPS_PID_MMC));
    NAS_MMC_SndDrxTimerInfo(VOS_FALSE);
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateNetworkInfo_WasSysInfo
 功能描述  : 收到WAS下系统消息的处理
 输入参数  : RRMM_SYS_INFO_IND_STRU* pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月21日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2012年6月9日
    作    者   : z00161729
    修改内容   : V7R1C50 GUL背景搜网修改
  3.日    期   : 2012年11月13日
    作    者   : z40661
    修改内容   : V7R1C50 GUL背景搜网修改
  4.日    期   : 2014年2月14日
    作    者   : s00246516
    修改内容   : L-C互操作项目:增加获取和注册请求的处理
  5.日   期    : 2014-04-15
    作   者    : w00176964
    修改内容   : V3R3C60_eCall项目调整:上次驻留LAI信息保存到MML中
  6.日   期    : 2015-6-11
    作   者    : b00269685
    修改内容   : 区分ota 和 sys
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateNetworkInfo_WasSysInfo(
    struct MsgCB                       *pstMsg
)
{
    RRMM_SYS_INFO_IND_STRU             *pstWrrSysInfo   = VOS_NULL_PTR;
    NAS_MML_NETWORK_INFO_STRU          *pstNetWorkInfo  = VOS_NULL_PTR;
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-4-28, begin */
    NAS_MML_LAI_STRU                   *pstOldCampLai   = VOS_NULL_PTR;
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-4-28, end */

    pstWrrSysInfo = (RRMM_SYS_INFO_IND_STRU*)pstMsg;

    if (VOS_FALSE == NAS_MMC_IsOptItemVaild_WasSysInfo(pstWrrSysInfo))
    {
        return;
    }

    pstNetWorkInfo  =  NAS_MML_GetNetworkInfo();

    /* Added by w00176964 for V3R3C60_eCall项目, 2014-4-28, begin */
    pstOldCampLai       = NAS_MML_GetOldCampLai();

    /* 保存上次驻留的LAI信息,然后下面步骤更新当前驻留LAI信息 */
    if (VOS_FALSE == NAS_MMC_IsInValidCampPlmn())
    {
        PS_MEM_CPY(pstOldCampLai, &(pstNetWorkInfo->stCampPlmnInfo.stLai), sizeof(NAS_MML_LAI_STRU));
    }
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-4-28, end */

    if (VOS_TRUE == pstWrrSysInfo->bitOpPlmnId)
    {
        /* 更新网路的运营商名称信息 */
        NAS_MMC_UpdateOperNameInfo(&(pstWrrSysInfo->PlmnId));

        /* 更新当前驻留网络的信息 */
        pstNetWorkInfo->stCampPlmnInfo.stLai.stPlmnId.ulMcc   = pstWrrSysInfo->PlmnId.ulMcc;
        pstNetWorkInfo->stCampPlmnInfo.stLai.stPlmnId.ulMnc   = pstWrrSysInfo->PlmnId.ulMnc;

        pstNetWorkInfo->stCampPlmnInfo.stLai.enCampPlmnNetRat = NAS_MML_NET_RAT_TYPE_WCDMA;
    }

    /* 获取 LAC, aucCnCommonInfo[0]代表Lac, aucCnCommonInfo[1]代表 Lac Continued Byte*/
    if (0 != pstWrrSysInfo->ucCnCommonSize)
    {
        pstNetWorkInfo->stCampPlmnInfo.stLai.aucLac[0] = pstWrrSysInfo->aucCnCommonInfo[0];
        pstNetWorkInfo->stCampPlmnInfo.stLai.aucLac[1] = pstWrrSysInfo->aucCnCommonInfo[1];
    }

    /* 更新 rac信息和PS域支持信息 */
    if (0 == pstWrrSysInfo->ucPsInfoSize)
    {
        if (RRC_NAS_SYS_INFO_TYPE_SYS == pstWrrSysInfo->enSysInfoType)
        {
            pstNetWorkInfo->stPsDomainInfo.ucPsSupportFlg = VOS_FALSE;

            pstNetWorkInfo->stCampPlmnInfo.ucRac = NAS_MML_RAC_INVALID;
        }
    }
    else
    {
        pstNetWorkInfo->stPsDomainInfo.ucPsSupportFlg = VOS_TRUE;
        pstNetWorkInfo->stCampPlmnInfo.ucRac = pstWrrSysInfo->aucPsInfo[0];
    }

    if (VOS_TRUE == pstWrrSysInfo->bitOpCellId)
    {
        /* 填入小区ID */
        pstNetWorkInfo->stCampPlmnInfo.stCampCellInfo.astCellInfo[0].ulCellId = pstWrrSysInfo->ulCellId;
        pstNetWorkInfo->stCampPlmnInfo.stCampCellInfo.ucCellNum               = 1;
    }

    /* 更新网络模式 :aucPsInfo[1]的Bit1指示网络模式 */
    if ( 0 == (pstWrrSysInfo->aucPsInfo[1] & NAS_MML_NET_MODE_BIT_MASK_WAS_SYS_INFO) )
    {
        /* 更新为网络模式I ,NAS_MML_NET_MODE_I */
        pstNetWorkInfo->stCampPlmnInfo.enNetworkMode = NAS_MML_NET_MODE_I;
    }
    else
    {
        /* 更新为网络模式II ,NAS_MML_NET_MODE_II */
        pstNetWorkInfo->stCampPlmnInfo.enNetworkMode = NAS_MML_NET_MODE_II;
    }

    /* 更新Sysinfo的子模式 */
    pstNetWorkInfo->stCampPlmnInfo.enSysSubMode = pstWrrSysInfo->enSysSubMode;

    /* Added by s00246516 for L-C互操作项目, 2014-02-14, Begin */
    NAS_MML_SetCurrCampArfcn(0x0);
    /* Added by s00246516 for L-C互操作项目, 2014-02-14, End */

    /* 更新当前的 W Band 系统信息，G和L驻留 Band为0 */
    pstNetWorkInfo->stBandInfo.unWcdmaBand.ulBand      = pstWrrSysInfo->unWcdmaBand.ulBand;
    pstNetWorkInfo->stBandInfo.unGsmBand.ulBand        = 0;
#if (FEATURE_ON == FEATURE_LTE)
    pstNetWorkInfo->stBandInfo.stLteBand.aulLteBand[0] = 0;
    pstNetWorkInfo->stBandInfo.stLteBand.aulLteBand[1] = 0;
#endif

    /* 更新CsPS 的是否允许注册的标志及unBar标志位 */

    NAS_MMC_UpdateCsPsRestriction_WasInfo(pstWrrSysInfo, pstNetWorkInfo);

    OM_DelDrxTimerWakeSrc(VOS_GetModemIDFromPid(WUEPS_PID_MMC));
    NAS_MMC_SndDrxTimerInfo(VOS_FALSE);
    return;
}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateSuitPlmnList_LmmSysInfo
 功能描述  : 收到l系统消息更新共享网络信息
 输入参数  : pstLteSysInfo - 系统消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月19日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateSuitPlmnList_LmmSysInfo(
    MMC_LMM_SYS_INFO_STRU              *pstLteSysInfo
)
{
    NAS_MML_PLMN_ID_STRU                stPlmnId;
    MMC_LMM_PLMN_ID_STRU               *pstLmmPlmnId = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucSuitTotalPlmnNum;
    NAS_MML_SUIT_PLMN_LIST_STRU        *pstSuitPlmnList = VOS_NULL_PTR;

    pstSuitPlmnList    = NAS_MML_GetSuitPlmnList();
    ucSuitTotalPlmnNum = (VOS_UINT8)pstLteSysInfo->stSpecPlmnIdList.ulSuitPlmnNum;

    if (ucSuitTotalPlmnNum > MMC_LMM_MAX_SRCH_PLMN_NUM)
    {
        ucSuitTotalPlmnNum = MMC_LMM_MAX_SRCH_PLMN_NUM;
    }

    for (ucIndex = 0; ucIndex < ucSuitTotalPlmnNum; ucIndex++)
    {
        pstLmmPlmnId = &(pstLteSysInfo->stSpecPlmnIdList.astSuitPlmnList[ucIndex]);

        /* 保存共享网络信息，包含当前驻留网络 */
        NAS_MMC_ConvertLmmPlmnToGUNasFormat(pstLmmPlmnId, &stPlmnId);

        PS_MEM_CPY(&pstSuitPlmnList->astSuitPlmnList[ucIndex], &stPlmnId, sizeof(pstSuitPlmnList->astSuitPlmnList[ucIndex]));
    }

    pstSuitPlmnList->ucSuitPlmnNum = ucSuitTotalPlmnNum;

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateNetworkInfo_LmmSysInfo
 功能描述  : 检查并保存LTE下的系统信息
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月6日
    作    者   : l00130025
    修改内容   : 新生成函数

  2.日    期   : 2011年11月4日
    作    者   : zhoujun 40661
    修改内容   : LMM的系统消息保存更新
  3.日    期   : 2012年2月15日
    作    者   : w00166186
    修改内容   : CSFB&PPAC&ETWS&ISR 开发
  4.日    期   : 2012年6月9日
    作    者   : z00161729
    修改内容   : V7R1C50 GUL背景搜修改
  5.日    期   : 2012年06月13日
    作    者   : s46746
    修改内容   : For CS/PS mode 1，修改LTE系统子模式

  6.日    期   : 2012年11月9日
    作    者   : z40661
    修改内容   : DRX TImer修改
  7.日    期   : 2014年2月14日
    作    者   : s00246516
    修改内容   : L-C互操作项目:增加获取和注册请求的处理
  7.日    期   : 2014年8月14日
    作    者   : s00217060
    修改内容   : DTS2014080700822:更新LTE驻留的小区是FDD还是TDD
  8.日    期   : 2015年4月19日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateNetworkInfo_LmmSysInfo(
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SYS_INFO_IND_STRU          *pstLmmSysInfoMsg    = VOS_NULL_PTR;
    MMC_LMM_PLMN_ID_STRU               *pstLmmPlmnId        = VOS_NULL_PTR;
    NAS_MML_MS_BAND_INFO_STRU          *pstBandInfo         = VOS_NULL_PTR;
    NAS_MML_CAMP_CELL_INFO_STRU        *pstCampCell         = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstCurrPlmnId       = VOS_NULL_PTR;
    NAS_MML_OPERATOR_NAME_INFO_STRU    *pstOperNameInfo     = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCurCampInfo      = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stPlmnId;


    pstLmmSysInfoMsg  = (LMM_MMC_SYS_INFO_IND_STRU*)pstMsg;

    pstLmmPlmnId = &(pstLmmSysInfoMsg->stLteSysInfo.stSpecPlmnIdList.astSuitPlmnList[0]);

    /* 保存PLMN ID信息到当前的信息里 */
    NAS_MMC_ConvertLmmPlmnToGUNasFormat(pstLmmPlmnId, &stPlmnId);

    pstCurCampInfo                       = NAS_MML_GetCurrCampPlmnInfo();
    NAS_MML_InitRssiValue(&(pstCurCampInfo->stCampCellInfo));

    /* 到L下后，清除接入受限信息 */
    NAS_MML_ClearCsPsRestrictionAll();

    /* 更新驻留信息 */
    pstOperNameInfo = NAS_MML_GetOperatorNameInfo();
    pstCurrPlmnId   = NAS_MML_GetCurrCampPlmnId();

    pstCurrPlmnId->ulMcc                    = stPlmnId.ulMcc;
    pstCurrPlmnId->ulMnc                    = stPlmnId.ulMnc;

    /* 如果保存的长短网络名与当前驻留的PLMN ID不同，清除全局变量 */
    if ((pstCurrPlmnId->ulMcc != pstOperNameInfo->stOperatorPlmnId.ulMcc)
     || (pstCurrPlmnId->ulMnc != pstOperNameInfo->stOperatorPlmnId.ulMnc))
    {
        /* 清空aucOperatorNameShort和aucOperatorNameLong */
        PS_MEM_SET(pstOperNameInfo, 0x00, sizeof(NAS_MML_OPERATOR_NAME_INFO_STRU));
        pstOperNameInfo->stOperatorPlmnId.ulMcc = stPlmnId.ulMcc;
        pstOperNameInfo->stOperatorPlmnId.ulMnc = stPlmnId.ulMnc;

    }

    /* 更新cell Info */
    pstCampCell     = NAS_MML_GetCampCellInfo();

    /* 填入小区ID */
    pstCampCell->ucCellNum               = 1;
    pstCampCell->astCellInfo[0].ulCellId = pstLmmSysInfoMsg->stLteSysInfo.ulCellId;

    /* Added by s00246516 for L-C互操作项目, 2014-02-14, Begin */
    NAS_MML_SetCurrCampArfcn(pstLmmSysInfoMsg->stLteSysInfo.ulArfcn);
    /* Added by s00246516 for L-C互操作项目, 2014-02-14, End */

    /* 更新当前的系统GsmBand信息，W,L 驻留 Band为0 */
    pstBandInfo = NAS_MML_GetCurrBandInfo();
    pstBandInfo->unWcdmaBand.ulBand      = 0;
    pstBandInfo->unGsmBand.ulBand        = 0;
    pstBandInfo->stLteBand.aulLteBand[0] = pstLmmSysInfoMsg->stLteSysInfo.stLteBand.aulLteBand[0];
    pstBandInfo->stLteBand.aulLteBand[1] = pstLmmSysInfoMsg->stLteSysInfo.stLteBand.aulLteBand[1];

    /* 获取当前驻留的网络信息 */
    pstCurCampInfo->enNetworkMode        = NAS_MML_NET_MODE_INVALID;

    pstCurCampInfo->enSysSubMode         = NAS_MML_RRC_SYS_SUBMODE_LTE;

    pstCurCampInfo->stLai.aucLac[0]      = pstLmmSysInfoMsg->stLteSysInfo.stTac.ucTac;
    pstCurCampInfo->stLai.aucLac[1]      = pstLmmSysInfoMsg->stLteSysInfo.stTac.ucTacCnt;
    pstCurCampInfo->ucRac                = NAS_MML_RAC_INVALID;

    pstCurCampInfo->enLmmAccessType      = pstLmmSysInfoMsg->stLteSysInfo.enAccessType;


    pstCurCampInfo->stLai.enCampPlmnNetRat = NAS_MML_NET_RAT_TYPE_LTE;

    /* Modified by z00234330 for 低功耗接口 , 2013-10-29, begin */
    OM_DelDrxTimerWakeSrc(VOS_GetModemIDFromPid(WUEPS_PID_MMC));
    /* Modified by z00234330 for 低功耗接口 , 2013-10-29, end */
    NAS_MMC_SndDrxTimerInfo(VOS_FALSE);

    NAS_MMC_UpdateSuitPlmnList_LmmSysInfo(&pstLmmSysInfoMsg->stLteSysInfo);

    return;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_GetDomainRegStatusInRegInfoList
 功能描述  : 从注册信息结果表中取得指定网络指定接入技术的CS/PS域的结果信息
 输入参数  : pstPlmnId      : 需要查找的PLMN ID
              enCurNetRatType: 指定网络的接入技术
 输出参数  : penCsCause     : CS域的结果信息
              penPsCause     : PS域的结果信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月21日
    作    者   : w00167002
    修改内容   : 新增函数
*****************************************************************************/
VOS_VOID NAS_MMC_GetDomainRegStatusInRegInfoList(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurNetRatType,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 *penCsCause,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 *penPsCause
)
{
    NAS_MMC_PLMN_REG_REJ_CTX_STRU      *pstPlmnRegRejInfo = VOS_NULL_PTR;
    NAS_MMC_PLMN_REG_INFO_STRU         *pstPlmnRegList    = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;

    pstPlmnRegRejInfo = NAS_MMC_GetPlmnRegRejInfo();

    /* 获取注册原因列表的指针 */
    pstPlmnRegList = pstPlmnRegRejInfo->astPlmnRegInfoList;

    /* 判断当前网络是否已在注册列表中 */
    ulIndex = NAS_MMC_GetPlmnIndexInRegInfoList(pstPlmnId,
                            pstPlmnRegRejInfo->ucPlmnRegInfoNum, pstPlmnRegList);

    /* 当前网络在注册列表中，取得对应接入技术的CS/PS域的注册结果 */
    if ((ulIndex < pstPlmnRegRejInfo->ucPlmnRegInfoNum)
     && (ulIndex < NAS_MMC_MAX_REG_PLMN_INFO_NUM))
    {
        switch ( enCurNetRatType )
        {

        #if (FEATURE_ON == FEATURE_LTE)

            case NAS_MML_NET_RAT_TYPE_LTE :
                *penCsCause = pstPlmnRegRejInfo->astPlmnRegInfoList[ulIndex].enLCsRegStatus;
                *penPsCause = pstPlmnRegRejInfo->astPlmnRegInfoList[ulIndex].enLPsRegStatus;
                return;
        #endif

            case NAS_MML_NET_RAT_TYPE_WCDMA:
                *penCsCause = pstPlmnRegRejInfo->astPlmnRegInfoList[ulIndex].enWCsRegStatus;
                *penPsCause = pstPlmnRegRejInfo->astPlmnRegInfoList[ulIndex].enWPsRegStatus;
                return;

            case NAS_MML_NET_RAT_TYPE_GSM :
                *penCsCause = pstPlmnRegRejInfo->astPlmnRegInfoList[ulIndex].enGCsRegStatus;
                *penPsCause = pstPlmnRegRejInfo->astPlmnRegInfoList[ulIndex].enGPsRegStatus;
                return;

            default:
                NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetDomainRegStatusInRegInfoList: NETRAT TYPE INVALID ");
                return;
        }
    }

    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetDomainRegStatusInRegInfoList: can't find the plmn id ");

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsPlmnRegInfoAllSucc
 功能描述  : 检测PLMN是否有注册失败的域信息
 输入参数  : pstPlmnRegList : PLMN的注册信息
 输出参数  : 无
 返 回 值  : VOS_TRUE       : PLMN有注册失败的域信息上
             VOS_FALSE      : PLMN没有注册失败的域信息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月15日
    作    者   : w00167002
    修改内容   : 新增函数
*****************************************************************************/
VOS_UINT32  NAS_MMC_IsPlmnRegInfoAllSucc(
    NAS_MMC_PLMN_REG_INFO_STRU         *pstPlmnRegList
)
{
	/* G下CS域是否注册失败过，若失败，则返回VOS_FASLE */
	if ( NAS_MML_REG_FAIL_CAUSE_NULL != pstPlmnRegList->enGCsRegStatus )
	{
	    return VOS_FALSE;
	}

	/* G下PS域是否注册失败过，若失败，则返回VOS_FASLE */
	if ( NAS_MML_REG_FAIL_CAUSE_NULL != pstPlmnRegList->enGPsRegStatus )
	{
	    return VOS_FALSE;
	}

	/* W下CS域是否注册失败过，若失败，则返回VOS_FASLE */

	if ( NAS_MML_REG_FAIL_CAUSE_NULL != pstPlmnRegList->enWCsRegStatus )
	{
	    return VOS_FALSE;
	}
	/* W下PS域是否注册失败过，若失败，则返回VOS_FASLE */
	if ( NAS_MML_REG_FAIL_CAUSE_NULL != pstPlmnRegList->enWPsRegStatus )
	{
	    return VOS_FALSE;
	}

#if (FEATURE_ON == FEATURE_LTE)

	/* L下CS域是否注册失败过，若失败，则返回VOS_FASLE */
	if ( NAS_MML_REG_FAIL_CAUSE_NULL != pstPlmnRegList->enLCsRegStatus )
	{
	    return VOS_FALSE;
	}

	/* L下PS域是否注册失败过，若失败，则返回VOS_FASLEs */
	if ( NAS_MML_REG_FAIL_CAUSE_NULL != pstPlmnRegList->enLPsRegStatus )
	{
	    return VOS_FALSE;
	}
#endif

	/* 所有域都为NAS_MML_REG_FAIL_CAUSE_NULL,则认为该网络注册成功 */
	return VOS_TRUE;

}
/*****************************************************************************
 函 数 名  : NAS_MMC_NotifyModeChange
 功能描述  : 通知其他模块当前的网络模式发生变化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2012年01月04日
   作    者   : w00167002
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_NotifyModeChange(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8             enRatType,
    VOS_UINT8                                   ucSimPsRegStatus
)
{
    NAS_MMC_SRV_STA_CHNG_INFO_STRU             *pstLastSrvStaInfo;

    pstLastSrvStaInfo = NAS_MMC_GetSrvStaChngInfo();

    /* 网络模式发生变化时，通知APS和CDS，卡变为无效时，通知APS和CDS */
    if ( ( enRatType != pstLastSrvStaInfo->enRatType )
      || ( ( ucSimPsRegStatus != pstLastSrvStaInfo->ucSimPsRegStatus )
        && ( VOS_FALSE == ucSimPsRegStatus )) )
    {
        NAS_MMC_SndApsServiceStatusInd(enRatType, ucSimPsRegStatus);
#if (FEATURE_OFF == FEATURE_UE_MODE_CDMA)
        /* CDMA宏关闭的情况下，由MMC通知CDS接入技术变更 */
        NAS_MMC_SndCdsModeChangeInd(enRatType);
#endif
        pstLastSrvStaInfo->enRatType          = enRatType;
        pstLastSrvStaInfo->ucSimPsRegStatus   = ucSimPsRegStatus;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsPlmnAllowedInManualMode
 功能描述  : 手动选网模式时，PlmnId是否允许
 输入参数  : enPlmnSelectionMode : 选网模式
 输出参数  : 无
 返 回 值  : VOS_TRUE:有效
             VOS_FALSE:无效
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年7月7日
   作    者   : s00217060
   修改内容   : 新生成函数
 2.日    期   : 2012年11月09日
   作    者   : l65478
   修改内容   : DTS2012103005174, PS成功,在等效PLMN中不设置禁止标志

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlmnAllowedInManualMode(
    NAS_MML_PLMN_ID_STRU                                   *pstPlmnId
)
{
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstUserSpecPlmnId = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEplmnInfo      = VOS_NULL_PTR;
    VOS_UINT32                                              ulRlst;
    VOS_UINT32                                              ulEplmnValidFlg;

    pstUserSpecPlmnId = NAS_MMC_GetUserSpecPlmnId();
    pstEplmnInfo      = NAS_MML_GetEquPlmnList();

    /* 手动选网模式回LTE的网络与用户指定的网络相同 */
    if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstPlmnId, &(pstUserSpecPlmnId->stPlmnId)))
    {
        return VOS_TRUE;
    }

    /* 判断手动选网模式回LTE的网络是不是用户指定的网络的EPLMN */
    ulRlst = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstPlmnId,
                                            pstEplmnInfo->ucEquPlmnNum,
                                            pstEplmnInfo->astEquPlmnAddr);

    ulEplmnValidFlg = NAS_MML_GetEplmnValidFlg();

    /* 手动选网模式时，用户指定的网络已注册，回LTE的网络是用户指定的网络的EPLMN*/
    if ((VOS_TRUE == NAS_MMC_GetUserSpecPlmnRegisterStatus())
     && (VOS_TRUE == ulRlst)
     && (VOS_TRUE == ulEplmnValidFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedDisableLte_SysCfg
 功能描述  : SYSCFG设置完成后判断是否需要disable LTE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要disable LTE
             VOS_FALSE:不需要disable LTE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年06月12日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年09月12日
   作    者   : z00161729
   修改内容   : DTS2012082702662 disable或enable lte不再判断当前syscfg是否支持L
 3.日    期   : 2012年11月10日
   作    者   : s00217060
   修改内容   : DTS2012102902559：SIM卡时，需要Disable Lte;
 4.日    期   : 2012年12月28日
   作    者   : s46746
   修改内容   : DSDA GUNAS C CORE项目，增加平台是否支持LTE判断
 5.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式
 6.日    期   : 2013年2月28日
   作    者   : w00176964
   修改内容   : DTS2014030100833:调整SIM卡disable和enable lTE逻辑
 7.日    期   : 2015年2月26日
   作    者   : w00167002
   修改内容   : DTS2015021604972:在SYSCFG设置完后，MMA进行ATTACH流程。MMC已经退出
                 SYSCFG状态机，并触发搜网。在搜网时候，如果PS不准许ATTACH，则不搜索LTE.
                 现修改为在SYSCFG后,如果需要搜网，则判别是否ATTACH PS需要先ENABLE LTE。
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableLte_SysCfg(
    NAS_MMCMMC_SysCfg_RSLT_STRU        *pstSyscfgRsltMsg
)
{
    VOS_UINT8                                               ucSimPsRegStatus;
    VOS_UINT8                                               ucSimCsRegStatus;
    VOS_UINT32                                              ulRatForbiddenFlg;

    ulRatForbiddenFlg   = NAS_MML_IsRatInForbiddenList(NAS_MML_NET_RAT_TYPE_LTE);

    /* 根据协议所述，在满足如下条件下，需要disable LTE：
    (1)SYSCFG设置当前接入技术为LW,LG,LWG
    (2)PS域卡无效或者PS域不允许attach或SIM卡
    (3)CS域卡有效且CS允许注册 */

    ucSimPsRegStatus    = NAS_MML_GetSimPsRegStatus();
    ucSimCsRegStatus    = NAS_MML_GetSimCsRegStatus();

    /* 卡不存在时不需要disable LTE */
    if (VOS_FALSE == NAS_MML_GetSimPresentStatus() )
    {
        return VOS_FALSE;
    }

    /* 平台不支持LTE时不需要disable LTE */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportLte())
    {
        return VOS_FALSE;
    }

    /* 如果已经disable 不需要再disable LTE */
    if (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
    {
        return VOS_FALSE;
    }

    /* LTE ONLY开机不会禁止LTE，因此在这里要禁止 */
    if ((VOS_FALSE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
     && (VOS_TRUE == ulRatForbiddenFlg))
    {
        return VOS_TRUE;
    }

    /* 非L单模且为SIM卡则直接disable L模 */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {
        return VOS_TRUE;
    }

    /* CS不允许注册或CS卡无效 */
    if ((VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
     || (VOS_FALSE == ucSimCsRegStatus))
    {
        return VOS_FALSE;
    }

    /* PS卡有效，并且PS允许attach */

    if (((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
       || (VOS_TRUE == pstSyscfgRsltMsg->ulIsNeedAttachPs))
     && (VOS_TRUE == ucSimPsRegStatus))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedEnableLte_SysCfg
 功能描述  : SYSCFG设置完成后判断是否需要enable LTE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要enable LTE
             VOS_FALSE:不需要enable LTE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年06月12日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2015年2月26日
   作    者   : w00167002
   修改内容   : DTS2015021604972:在SYSCFG设置完后，MMA进行ATTACH流程。MMC已经退出
                 SYSCFG状态机，并触发搜网。在搜网时候，如果PS不准许ATTACH，则不搜索LTE.
                 现修改为在SYSCFG后,如果需要搜网，则判别是否ATTACH PS需要先ENABLE LTE。
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedEnableLte_SysCfg(
    NAS_MMCMMC_SysCfg_RSLT_STRU        *pstSyscfgRsltMsg
)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;

    /* 在满足如下条件后，MMC需要重新enable LTE：
    (1)本地disable LTE的标记为真
    (2)接入模式设置支持LTE ONLY */

    /* 获取LTE的使能状态 */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

    /* 如果之前未disable LTE,也不需要enable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* 当前接入模式为L only,需要enable LTE */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_TRUE;
    }


    /* 判断ATTACH PS是否需要触发ENABLE LTE */
    if ((VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
     && (VOS_TRUE == pstSyscfgRsltMsg->ulIsNeedAttachPs))
    {
        if (VOS_TRUE == NAS_MMC_IsNeedEnableLte_AttachPs())
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedDisableLte_ModeChange
 功能描述  : ModeChange设置完成后判断是否需要disable LTE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要disable LTE
             VOS_FALSE:不需要disable LTE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年06月12日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年09月12日
   作    者   : z00161729
   修改内容   : DTS2012082702662：disable或enable lte不再判断当前syscfg是否支持L
 3.日    期   : 2012年11月10日
   作    者   : s00217060
   修改内容   : DTS2012102902559：SIM卡时，需要Disable Lte;
 4.日    期   : 2012年12月28日
   作    者   : s46746
   修改内容   : DSDA GUNAS C CORE项目，增加平台是否支持LTE判断
 5.日    期   : 2013年2月28日
   作    者   : w00176964
   修改内容   : DTS2014030100833:调整SIM卡disable和enable lTE逻辑
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableLte_ModeChange(VOS_VOID)
{
    VOS_UINT8                                               ucSimPsRegStatus;
    VOS_UINT8                                               ucSimCsRegStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    /* 根据协议所述，在满足如下条件下，需要disable LTE：
    (1)当前接入技术为LW,LG,LWG
    (2)PS域卡无效或SIM卡
    (3)CS+PS */

    ucSimPsRegStatus    = NAS_MML_GetSimPsRegStatus();
    ucSimCsRegStatus    = NAS_MML_GetSimCsRegStatus();
    enSimType           = NAS_MML_GetSimType();

    /* 卡不存在时不需要disable LTE */
    if (VOS_FALSE == NAS_MML_GetSimPresentStatus() )
    {
        return VOS_FALSE;
    }

    /* 平台不支持LTE时不需要disable LTE */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportLte())
    {
        return VOS_FALSE;
    }

    /* 如果已经disable 不需要再disable LTE */
    if (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
    {
        return VOS_FALSE;
    }

    /* LTE单模,无需disable */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    if (NAS_MML_SIM_TYPE_SIM == enSimType)
    {
        return VOS_TRUE;
    }

    /* CS卡无效 */
    if (VOS_FALSE == ucSimCsRegStatus)
    {
        return VOS_FALSE;
    }

    /* MS模式非CS+PS */
    if (NAS_MML_MS_MODE_PS_CS != NAS_MML_GetMsMode())
    {
        return VOS_FALSE;
    }

    /* PS卡有效 */
    if (VOS_TRUE == ucSimPsRegStatus)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedEnableLte_ModeChange
 功能描述  : ModeChange设置完成后判断是否需要enable LTE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要enable LTE
             VOS_FALSE:不需要enable LTE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年06月12日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年09月12日
   作    者   : z00161729
   修改内容   : DTS2012082702662：disable或enable lte不再判断当前syscfg是否支持L
 3.日    期   : 2012年11月10日
   作    者   : s00217060
   修改内容   : DTS2012102902559：USIM卡时，才需要Enable Lte;SIM卡时不需要
10.日    期   : 2012年12月15日
   作    者   : l65478
   修改内容   : DTS2012120508936:在发起紧急呼叫时需要disable LTE
11.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式
12.日    期   : 2013年2月28日
   作    者   : w00176964
   修改内容   : DTS2014030100833:调整SIM卡disable和enable lTE逻辑

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedEnableLte_ModeChange(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
    VOS_UINT8                                               ucCsAllowAttachFlg;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    /* 在满足如下条件后，MMC需要重新enable LTE：
    (1)本地disable LTE的标记为真
    (2)MS模式设置支持PS ONLY且CS不允许注册
    (3)PS卡无效或者USIM卡 */

    /* 获取LTE的使能状态 */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
    ucCsAllowAttachFlg     = NAS_MML_GetCsAttachAllowFlg();
    enSimType              = NAS_MML_GetSimType();

    /* 如果开机时已经根据en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config的配置禁止了LTE，则返回VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }

    /* 如果之前未disable LTE,也不需要enable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* SIM卡类型且不为L单模不需要enable LTE */
    if ((VOS_TRUE               != NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
     && (NAS_MML_SIM_TYPE_SIM   == enSimType))
    {
        return VOS_FALSE;
    }

    /* PS卡无效 */
    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        return VOS_FALSE;
    }


    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
    {
        return VOS_FALSE;
    }

    /* 当前MS模式为PS only,需要enable LTE */
    if ((NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
     && (VOS_FALSE == ucCsAllowAttachFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedDisableLte_DetachPs
 功能描述  : Detach PS完成后判断是否需要disable LTE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要disable LTE
             VOS_FALSE:不需要disable LTE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年06月12日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年09月12日
   作    者   : z00161729
   修改内容   : DTS2012082702662：disable或enable lte不再判断当前syscfg是否支持L
 3.日    期   : 2012年11月10日
   作    者   : s00217060
   修改内容   : DTS2012102902559：SIM卡时需要Disable Lte
 4.日    期   : 2012年12月28日
   作    者   : s46746
   修改内容   : DSDA GUNAS C CORE项目，增加平台是否支持LTE判断
 5.日    期   : 2013年2月28日
   作    者   : w00176964
   修改内容   : DTS2014030100833:调整SIM卡disable和enable lTE逻辑
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableLte_DetachPs(VOS_VOID)
{
    NAS_MMC_DETACH_REQ_CTX_STRU                            *pstDetachReqCtx = VOS_NULL_PTR;
    VOS_UINT8                                               ucSimCsRegStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    /* 根据协议3GPP 24.301所述,5.5.2.2.2 UE initiated detach procedure completion for EPS services only
    The UE in CS/PS mode 1 or CS/PS mode 2 of operation shall set the update status
    to U2 NOT UPDATED, disable E UTRAN and select GERAN or UTRAN access technology
    and enter the EMM-NULL state.

    从实现理解看，在满足如下条件下，需要disable LTE：
    (1)当前接入技术为LW,LG,LWG
    (2)PS卡不允许注册或SIM卡
    (3)CS卡有效且CS允许注册 */

    ucSimCsRegStatus    = NAS_MML_GetSimCsRegStatus();
    enSimType           = NAS_MML_GetSimType();

    /* 卡不存在时不需要disable LTE */
    if (VOS_FALSE == NAS_MML_GetSimPresentStatus() )
    {
        return VOS_FALSE;
    }

    /* 平台不支持LTE时不需要disable LTE */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportLte())
    {
        return VOS_FALSE;
    }

    /* 如果已经disable 不需要再disable LTE */
    if (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
    {
        return VOS_FALSE;
    }

    /* disable 或enable lte不再判断syscfg是否支持L */

    /* LTE单模 */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    if (NAS_MML_SIM_TYPE_SIM == enSimType)
    {
        return VOS_TRUE;
    }

    /* PS没有进行Detach */
    if (VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
    {
        return VOS_FALSE;
    }


    /* CS不允许注册或CS卡无效 */
    if ((VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
     || (VOS_FALSE == ucSimCsRegStatus))
    {
        return VOS_FALSE;
    }

    pstDetachReqCtx = NAS_MMC_GetDetachReqCtxAddr();

    if (VOS_FALSE == NAS_MMC_IsDetachReqestDisableLte(pstDetachReqCtx->enDetachType,
                                                      pstDetachReqCtx->enDetachReason))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedEnableLte_DetachPs
 功能描述  : Detach PS完成后判断是否需要enable LTE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要enable LTE
             VOS_FALSE:不需要enable LTE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年11月10日
   作    者   : s00217060
   修改内容   : 新生成函数
 2.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式
 3.日    期   : 2013年2月28日
   作    者   : w00176964
   修改内容   : DTS2014030100833:调整SIM卡disable和enable lTE逻辑

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedEnableLte_DetachPs(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
    VOS_UINT8                                               ucCsAttachAllowFlg;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;           /* SIM卡类型,USIM或SIM卡*/

    /* 在满足如下条件后，MMC需要重新enable LTE：
    (1)本地disable LTE的标记为真
    (2)CS卡无效或CS卡不允许注册 */

    /* 获取LTE的使能状态 */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
    ucCsAttachAllowFlg     = NAS_MML_GetCsAttachAllowFlg();

    /* 如果开机时已经根据en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config的配置禁止了LTE，则返回VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }


    /* 如果之前未disable LTE,也不需要enable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* SIM卡类型且不为L单模不需要enable LTE */
    enSimType = NAS_MML_GetSimType();
    if ((VOS_TRUE               != NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
     && (NAS_MML_SIM_TYPE_SIM   == enSimType))
    {
        return VOS_FALSE;
    }

    /* CS卡无效或CS卡不允许注册，需要Enable Lte */
    if ((VOS_FALSE == NAS_MML_GetSimCsRegStatus())
     || (VOS_FALSE == ucCsAttachAllowFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedEnableLte_AttachPs
 功能描述  : Attach PS完成后判断是否需要enable LTE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要enable LTE
             VOS_FALSE:不需要enable LTE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年06月12日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年9月4日
   作    者   : z00161729
   修改内容   : DCM定制需求和遗留问题修改DTS2012090600196,支持GL,驻留G,syscfg设置G only,
                先detach ps，disable lte，syscfg设置后，attach ps但判断当前不支持L未enable lte，
                后续syscfg设置GL,也未enable lte，导致gmm收到ms radio capability消息未进行rau
 3.日    期   : 2012年11月10日
   作    者   : s00217060
   修改内容   : DTS2012102902559：USIM卡时，才需要Enable Lte;SIM卡时不需要
 4.日    期   : 2012年12月15日
   作    者   : l65478
   修改内容   : DTS2012120508936:在发起紧急呼叫时需要disable LTE
 5.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式
 6.日    期   : 2013年2月28日
   作    者   : w00176964
   修改内容   : DTS2014030100833:调整SIM卡disable和enable lTE逻辑

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedEnableLte_AttachPs(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    /* 在满足如下条件后，MMC需要重新enable LTE：
    (1)本地disable LTE的标记为真
    (2)PS卡有效
    (3)USIM卡 */

    /* 获取LTE的使能状态 */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

    /* 如果开机时已经根据en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config的配置禁止了LTE，则返回VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }


    /* 如果之前未disable LTE,也不需要enable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* SIM卡类型且不为L单模不需要enable LTE */
    enSimType = NAS_MML_GetSimType();
    if ((VOS_TRUE               != NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
     && (NAS_MML_SIM_TYPE_SIM   == enSimType))
    {
        return VOS_FALSE;
    }

    /* PS卡无效 */
    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        return VOS_FALSE;
    }

    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedDisableLte_AttachCs
 功能描述  : Attach CS完成后判断是否需要disable LTE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要disable LTE
             VOS_FALSE:不需要disable LTE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年06月12日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年09月12日
   作    者   : z00161729
   修改内容   : DTS2012082702662：disable或enable lte不再判断当前syscfg是否支持L
 3.日    期   : 2012年11月10日
   作    者   : s00217060
   修改内容   : DTS2012102902559：SIM卡时，需要Disable Lte;
 4.日    期   : 2012年12月28日
   作    者   : s46746
   修改内容   : DSDA GUNAS C CORE项目，增加平台是否支持LTE判断
 5.日    期   : 2013年2月28日
   作    者   : w00176964
   修改内容   : DTS2014030100833:调整SIM卡disable和enable lTE逻辑
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableLte_AttachCs(VOS_VOID)
{
    VOS_UINT8                                               ucSimPsRegStatus;
    VOS_UINT8                                               ucSimCsRegStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    /* 根据协议所述，在满足如下条件下，需要disable LTE：
    (1)SYSCFG设置当前接入技术为LW,LG,LWG
    (2)PS域卡无效或PS不允许注册或SIM卡
    (3)CS卡有效且模式为CS+PS */

    ucSimPsRegStatus    = NAS_MML_GetSimPsRegStatus();
    ucSimCsRegStatus    = NAS_MML_GetSimCsRegStatus();
    enSimType           = NAS_MML_GetSimType();

    /* 卡不存在时不需要disable LTE */
    if (VOS_FALSE == NAS_MML_GetSimPresentStatus() )
    {
        return VOS_FALSE;
    }

    /* 平台不支持LTE时不需要disable LTE */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportLte())
    {
        return VOS_FALSE;
    }

    /* 如果已经disable 不需要再disable LTE */
    if (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
    {
        return VOS_FALSE;
    }

    /* LTE单模，无需disable lte */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    if (NAS_MML_SIM_TYPE_SIM == enSimType)
    {
        return VOS_TRUE;
    }

    /* CS卡无效 */
    if (VOS_FALSE == ucSimCsRegStatus)
    {
        return VOS_FALSE;
    }

    /* PS卡有效，并且PS允许attach */
    if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
     && (VOS_TRUE == ucSimPsRegStatus))
    {
        return VOS_FALSE;
    }


    if (NAS_MML_MS_MODE_PS_CS != NAS_MML_GetMsMode())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedEnableLte_DetachCs
 功能描述  : Detach CS完成后判断是否需要enable LTE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要enable LTE
             VOS_FALSE:不需要enable LTE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年06月12日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年09月12日
   作    者   : z00161729
   修改内容   : DTS2012082702662：disable或enable lte不再判断当前syscfg是否支持L
 3.日    期   : 2012年11月10日
   作    者   : s00217060
   修改内容   : DTS2012102902559：USIM卡需要Enable Lte;SIM卡时不需要
 4.日    期   : 2012年12月15日
   作    者   : l65478
   修改内容   : DTS2012120508936:在发起紧急呼叫时需要disable LTE
 5.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式
 6.日    期   : 2013年2月28日
   作    者   : w00176964
   修改内容   : DTS2014030100833:调整SIM卡disable和enable lTE逻辑
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedEnableLte_DetachCs(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    /* 在满足如下条件后，MMC需要重新enable LTE：
    (1)本地disable LTE的标记为真
    (2)支持LTE
    (3) USIM */

    /* 获取LTE的使能状态 */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
    enSimType              = NAS_MML_GetSimType();

    /* 如果开机时已经根据en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config的配置禁止了LTE，则返回VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }


    /* 如果之前未disable LTE,也不需要enable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* SIM卡类型且不为L单模不需要enable LTE */
    if ((VOS_TRUE               != NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
     && (NAS_MML_SIM_TYPE_SIM   == enSimType))
    {
        return VOS_FALSE;
    }


    /* disable 或enable lte不再判断syscfg是否支持L */

    /* CS没有进行Detach */
    if (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
    {
        return VOS_FALSE;
    }

    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedDisableLte_AttachCsPs
 功能描述  : Attach CSPS完成后判断是否需要disable LTE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要disable LTE
             VOS_FALSE:不需要disable LTE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年06月12日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年11月10日
   作    者   : s00217060
   修改内容   : DTS2012102902559：SIM卡时，需要Disable Lte;
 3.日    期   : 2012年12月28日
   作    者   : s46746
   修改内容   : DSDA GUNAS C CORE项目，增加平台是否支持LTE判断
 5.日    期   : 2013年2月28日
   作    者   : w00176964
   修改内容   : DTS2014030100833:调整SIM卡disable和enable lTE逻辑
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableLte_AttachCsPs(VOS_VOID)
{
    VOS_UINT8                                               ucSimPsRegStatus;
    VOS_UINT8                                               ucSimCsRegStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    /* 根据协议所述，在满足如下条件下，需要disable LTE：
    (1)SYSCFG设置当前接入技术为LW,LG,LWG
    (2)PS域卡无效或SIM卡
    (3)CS卡有效 */

    ucSimPsRegStatus    = NAS_MML_GetSimPsRegStatus();
    ucSimCsRegStatus    = NAS_MML_GetSimCsRegStatus();
    enSimType              = NAS_MML_GetSimType();

    /* 卡不存在时不需要disable LTE */
    if (VOS_FALSE == NAS_MML_GetSimPresentStatus() )
    {
        return VOS_FALSE;
    }

    /* 平台不支持LTE时不需要disable LTE */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportLte())
    {
        return VOS_FALSE;
    }

    /* 如果已经disable 不需要再disable LTE */
    if (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
    {
        return VOS_FALSE;
    }

    /* LTE单模 */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    if (NAS_MML_SIM_TYPE_SIM == enSimType)
    {
        return VOS_TRUE;
    }

    /* CS卡无效 */
    if (VOS_FALSE == ucSimCsRegStatus)
    {
        return VOS_FALSE;
    }

    /* PS卡有效 */
    if (VOS_TRUE == ucSimPsRegStatus)
    {
        return VOS_FALSE;
    }


    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedEnableLte_AttachCsPs
 功能描述  : attach CSPS完成后判断是否需要enable LTE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要enable LTE
             VOS_FALSE:不需要enable LTE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年06月12日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年09月12日
   作    者   : z00161729
   修改内容   : DTS2012082702662：disable或enable lte不再判断当前syscfg是否支持L
 3.日    期   : 2012年11月10日
   作    者   : s00217060
   修改内容   : DTS2012102902559：USIM卡时，才需要Enable Lte;SIM卡时不需要
 4.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式
 5.日    期   : 2013年2月28日
   作    者   : w00176964
   修改内容   : DTS2014030100833:调整SIM卡disable和enable lTE逻辑

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedEnableLte_AttachCsPs(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    /* 在满足如下条件后，MMC需要重新enable LTE：
    (1)本地disable LTE的标记为真
    (2)PS卡有效 */

    /* 获取LTE的使能状态 */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

    /* 如果开机时已经根据en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config的配置禁止了LTE，则返回VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }

    /* 如果之前未disable LTE,也不需要enable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* SIM卡类型且不为L单模不需要enable LTE */
    enSimType = NAS_MML_GetSimType();
    if ((VOS_TRUE               != NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
     && (NAS_MML_SIM_TYPE_SIM   == enSimType))
    {
        return VOS_FALSE;
    }

    /* disable 或enable lte不再判断syscfg是否支持L */

    /* PS卡无效 */
    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedDisableLte_DetachCsPs
 功能描述  : Detach CSPS完成后判断是否需要disable LTE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要disable LTE
             VOS_FALSE:不需要disable LTE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年06月12日
   作    者   : s46746
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableLte_DetachCsPs(VOS_VOID)
{
    /* 该场景不需要Disable lte, 函数预留后续扩展使用 */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedEnableLte_DetachCsPs
 功能描述  : Detach CSPS完成后判断是否需要enable LTE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要enable LTE
             VOS_FALSE:不需要enable LTE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年06月12日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年09月12日
   作    者   : z00161729
   修改内容   : DTS2012082702662：disable或enable lte不再判断当前syscfg是否支持L
 3.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式
 4.日    期   : 2013年2月28日
   作    者   : w00176964
   修改内容   : DTS2014030100833:调整SIM卡disable和enable lTE逻辑

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedEnableLte_DetachCsPs(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;           /* SIM卡类型,USIM或SIM卡*/

    /* 在满足如下条件后，MMC需要重新enable LTE：
    (1)本地disable LTE的标记为真
    (2)支持LTE */

    /* 获取LTE的使能状态 */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

    /* 如果开机时已经根据en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config的配置禁止了LTE，则返回VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }


    /* 如果之前未disable LTE,也不需要enable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* disable 或enable lte不再判断syscfg是否支持L */

    /* SIM卡类型且不为L单模不需要enable LTE */
    enSimType = NAS_MML_GetSimType();
    if ((VOS_TRUE               != NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
     && (NAS_MML_SIM_TYPE_SIM   == enSimType))
    {
        return VOS_FALSE;
    }

    /* CS没有进行Detach */
    if (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedDisableLteRoam
 功能描述  : 判断是否需要disable LTE漫游
 输入参数  : ulMcc:当前PLMN ID的国家码
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要disable LTE漫游
             VOS_FALSE:不需要disable LTE漫游
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月14日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年12月28日
   作    者   : s46746
   修改内容   : DSDA GUNAS C CORE项目，增加平台是否支持LTE判断
 3.日    期   : 2015年3月9日
   作    者   : wx270776
   修改内容   : DTS2015021601238:MCC无效时候，不需要DISABLE LTE
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableLteRoam(
    VOS_UINT32                          ulMcc
)
{
    VOS_UINT32                          aulComparedMcc[NAS_MML_ROAM_ENABLED_MAX_MCC_NUMBER];

    VOS_UINT32                          ulPlatformSuppLteFlg;

    ulPlatformSuppLteFlg = NAS_MML_IsPlatformSupportLte();


    /* MCC无效时候，不需要DISABLE LTE */
    if ( VOS_FALSE == NAS_MML_IsMccValid(ulMcc) )
    {
        return VOS_FALSE;
    }

    /* 禁止LTE国际漫游时 */
    if ((VOS_FALSE == NAS_MML_GetLteRoamAllowedFlg())
     && (VOS_TRUE == ulPlatformSuppLteFlg))
    {
        /* 获取运营商定制的MCC列表 */
        NAS_MML_GetRoamEnabledMccList(aulComparedMcc);

        /* 当前驻留PLMN ID为国际漫游网络 */
        if (VOS_FALSE == NAS_MML_IsMccInDestMccList(ulMcc, NAS_MML_ROAM_ENABLED_MAX_MCC_NUMBER, aulComparedMcc))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedEnableLteRoam
 功能描述  : 判断是否需要enable LTE漫游
 输入参数  : ulMcc:当前PLMN ID的国家码
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要enable LTE漫游
             VOS_FALSE:不需要enable LTE漫游
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月14日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式
 3.日    期   : 2015年3月9日
   作    者   : wx270776
   修改内容   : DTS2015021601238:MCC无效时候，不需要DISABLE LTE
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedEnableLteRoam(
    VOS_UINT32                          ulMcc
)
{
    VOS_UINT32                          ulDisableLte;
    VOS_UINT32                          aulComparedMcc[NAS_MML_ROAM_ENABLED_MAX_MCC_NUMBER];

    /* 获取是否需要disable LTE漫游标记 */
    ulDisableLte  = NAS_MML_GetDisableLteRoamFlg();


    /* MCC无效时候，不需要DISABLE LTE */
    if ( VOS_FALSE == NAS_MML_IsMccValid(ulMcc) )
    {
        return VOS_FALSE;
    }

    /* 如果开机时已经根据en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config的配置禁止了LTE，则返回VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }

    /* 禁止LTE国际漫游时 */
    if (VOS_FALSE == NAS_MML_GetLteRoamAllowedFlg())
    {
        /* 获取运营商定制的MCC列表 */
        NAS_MML_GetRoamEnabledMccList(aulComparedMcc);

        /* 当前驻留PLMN ID为国内网络并且已经disable LTE */
        if ((VOS_TRUE == NAS_MML_IsMccInDestMccList(ulMcc, NAS_MML_ROAM_ENABLED_MAX_MCC_NUMBER, aulComparedMcc))
         && (VOS_TRUE == ulDisableLte))
        {
           return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedEnableLte_ImsSwitchOn
 功能描述  : 判断IMS功能打开时，是否需要Enable LTE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要enable LTE
             VOS_FALSE:不需要enable LTE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月4日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedEnableLte_ImsSwitchOnOrNotCsOnly(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;           /* SIM卡类型,USIM或SIM卡*/

    /* 在满足如下条件后，MMC需要重新enable LTE：
    (1)NV没有配置禁止LTE模
    (2)已经Disable LTE
    (3)USIM卡,或者SIM卡L单模
    (4)PS卡有效,且允许注册
    (5)Disable LTE的原因值为LTE下voice unavailable
    (6)UE支持IMS
    (7)voice domain不为cs only

    这个地方和DS文档不同，因为此时无法知道之前在LTE下是注册成功导致的Disable LTE
    还是两个域都失败5次导致的Disable LTE
    对于LTE下联合注册两个域都失败的情况，这个地方也会Enable LTE，如果后续到LTE下仍然失败，再Disable LTE */

    /* 获取LTE的使能状态 */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

    /* 如果开机时已经根据en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config的配置禁止了LTE，则返回VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }


    /* 如果之前未disable LTE,也不需要enable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* UE不支持ims */
    if (VOS_FALSE == NAS_MML_IsUeSupportIms())
    {
        return VOS_FALSE;
    }

    /* voice domain为cs only */
    if (NAS_MML_CS_VOICE_ONLY == NAS_MML_GetVoiceDomainPreference())
    {
        return VOS_FALSE;
    }

    /* SIM卡类型且不为L单模不需要enable LTE */
    enSimType = NAS_MML_GetSimType();
    if ((VOS_TRUE               != NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
     && (NAS_MML_SIM_TYPE_SIM   == enSimType))
    {
        return VOS_FALSE;
    }

    /* PS卡无效 */
    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        return VOS_FALSE;
    }

    /* PS卡不允许注册 */
    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        return VOS_FALSE;
    }

    /* Disable LTE的原因值为LTE下语音不可用 */
    if (MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE == NAS_MML_GetDisableLteReason())
    {
       return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsCampLteNormalService
 功能描述  : 判断是否已经驻留在L网络提供正常服务
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_FALSE: 不是已经驻留在L网络提供正常服务
              VOS_TRUE: 已经驻留在L网络提供正常服务
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年06月02日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsCampLteNormalService(VOS_VOID)
{
    /* 当前接入技术不是LTE */
    if ( NAS_MML_NET_RAT_TYPE_LTE != NAS_MML_GetCurrNetRatType() )
    {
        return VOS_FALSE;
    }

    /* 当前NAS为未驻留状态 */
    if (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == NAS_MMC_GetSpecPlmnSearchState())
    {
        return VOS_FALSE;
    }

    /* 当前处在非正常服务状态 */
    if (VOS_FALSE == NAS_MMC_IsNormalServiceStatus())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsReCampLteLimitedService
 功能描述  : LTE需要disable时，判断是否仍然驻留在LTE的网络上
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:仍然驻留在LTE的网络上
             VOS_FALES:disable Lte
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月20日
    作    者   : z40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsReCampLteLimitedService( VOS_VOID )
{
    /* 当前接入技术不是LTE */
    if ( NAS_MML_NET_RAT_TYPE_LTE != NAS_MML_GetCurrNetRatType() )
    {
        return VOS_FALSE;
    }

    /* 当前NAS为未驻留状态 */
    if (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == NAS_MMC_GetSpecPlmnSearchState())
    {
        return VOS_FALSE;
    }

    /* 如果是卡无效导致的需要disable lte网络,则不需要在LTE上 */
    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        return VOS_FALSE;
    }

    /* 如果是PS域detach导致的需要disable lte网络,则不需要在LTE上 */
    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : NAS_MMC_IsCurrLtePlmnAllowSrchInCLMode
 功能描述  : 判断当前搜索的lte PLMN是否允许搜索
 输入参数  : pstPlmnId: plmnId值
 输出参数  : 无
 返 回 值  : vos_ture:当前plmn允许搜索
             vos_false:当前plmn不允许搜索

 修改历史      :
  1.日    期   : 2015年9月11日
    作    者   : y00346957
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsCurrLtePlmnAllowSrchInCLMode(NAS_MML_PLMN_ID_STRU *pstPlmnId)
{
    NAS_MMC_CL_ASSOCIATED_INFO_NTF_STRU                    *psCLAssociatedInfo;
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8             enPlmnPriClass;
    VOS_UINT32                                              ulIs1xSupported;
    VOS_UINT32                                              ulIsCurrLtePlmnAllowSrch;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    VOS_UINT8                                               ucIndex;
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8             enEqPlmnPriClass;
    VOS_UINT32                                              ulIsEqPlmnAllowSrch;
    NAS_MML_PLMN_ID_STRU                                    stEqPlmnId;

    ulIsCurrLtePlmnAllowSrch = VOS_TRUE;
    psCLAssociatedInfo       = NAS_MMC_GetCLAssociatedInfoAddr();

    /* 是否支持1x */
    ulIs1xSupported          = NAS_MML_IsSpec3Gpp2RatInRatList(NAS_MML_3GPP2_RAT_TYPE_CDMA1X, NAS_MML_GetMs3Gpp2PrioRatList());

    /* 1x不支持，lte的priclass没有限定 */
    if (VOS_FALSE == ulIs1xSupported)
    {
        return VOS_TRUE;
    }

    /* lte不可用,返回false */
    if (VOS_FALSE == psCLAssociatedInfo->ucAllowSrchLteFlg)
    {
        return VOS_FALSE;
    }

    /* 当前搜索或驻留的lte的priclass */
    enPlmnPriClass = NAS_MMC_GetPlmnPrioClass(pstPlmnId);

    /* 判断当前搜索或驻留的lte的priclass是否大于等于要求的最低等级的priclass */
    ulIsCurrLtePlmnAllowSrch = NAS_MMC_ComParePlmnPrioClass(enPlmnPriClass, psCLAssociatedInfo->enLteSysPriClass);

    if (VOS_TRUE == ulIsCurrLtePlmnAllowSrch)
    {
        return ulIsCurrLtePlmnAllowSrch;
    }

    /* 在当前plmn不允许搜索(驻留)时，若其等效plmn列表中有允许搜索(驻留)的plmn，则当前plmn允许搜索(驻留) */
    pstEquPlmnInfo = NAS_MML_GetEquPlmnList();

    if ((VOS_FALSE == pstEquPlmnInfo->ucValidFlg) || (0 == pstEquPlmnInfo->ucEquPlmnNum))
    {
        return ulIsCurrLtePlmnAllowSrch;
    }

    /* 如果等效plmn列表中第1个plmn不是当前的plmn，mmc保存的等效plmn列表与当前plmn不是互为等效plmn */
    if ((pstPlmnId->ulMcc != pstEquPlmnInfo->astEquPlmnAddr[0].ulMcc)
     || (pstPlmnId->ulMnc != pstEquPlmnInfo->astEquPlmnAddr[0].ulMnc))
    {
        return ulIsCurrLtePlmnAllowSrch;
    }

    /* 如果eplmn中有符合条件的plmn，则当前plmn也符合条件 */
    for (ucIndex = 1; ucIndex < pstEquPlmnInfo->ucEquPlmnNum; ucIndex++)
    {
        stEqPlmnId.ulMcc = pstEquPlmnInfo->astEquPlmnAddr[ucIndex].ulMcc;
        stEqPlmnId.ulMnc = pstEquPlmnInfo->astEquPlmnAddr[ucIndex].ulMnc;

        enEqPlmnPriClass = NAS_MMC_GetPlmnPrioClass(&stEqPlmnId);

        ulIsEqPlmnAllowSrch = NAS_MMC_ComParePlmnPrioClass(enEqPlmnPriClass, psCLAssociatedInfo->enLteSysPriClass);

        if (VOS_TRUE == ulIsEqPlmnAllowSrch)
        {
            ulIsCurrLtePlmnAllowSrch = VOS_TRUE;

            break;
        }
    }

    return ulIsCurrLtePlmnAllowSrch;
}
#endif
#endif

/* NAS_MMC_GetMmlCsTransactionStatu函数移到NAS MML LIB 中*/

/*****************************************************************************
 函 数 名  : NAS_MMC_SortPlmnSearchListSpecRatPrioLowest
 功能描述  : 对搜网列表进行排序，将指定接入技术剪切放到列表最后
 输入参数  : pstPlmnSelectionListInfo
 输出参数  : pstPlmnSelectionListInfo
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年2月16日
   作    者   : h00202780
   修改内容   : 新生成函数
 2.日    期   : 2012年10月17日
   作    者   : z00161729
   修改内容   : DTS2012081604223:csfb失败需要搜网到gu，gu下搜网失败回lte，没有搜rplmn而是搜的eplmn，因为rplmn状态不对为butt
 3.日    期   : 2013年8月26日
   作    者   : w00242748
   修改内容   : DTS2013071808373编译告警清理

 4.日    期   : 2014年11月13日
   作    者   : w00167002
   修改内容   : DTS2014111201728:CSFB搜网时候，当前存在AVAILABLE网络，但是没有搜索GU的
                PLMN，而是搜索了L得PLMN，导致回到L,
*****************************************************************************/
VOS_VOID NAS_MMC_SortPlmnSearchListSpecRatPrioLowest(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enSpecRatType,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;

    /* 列表中保存的PLMN个数 */
    VOS_UINT16                          usSearchPlmnNum;
    usSearchPlmnNum  = pstPlmnSelectionListInfo->usSearchPlmnNum;

    for( i = 0; i < usSearchPlmnNum; i++ )
    {
        for ( j = 0; j < pstPlmnSelectionListInfo->astPlmnSelectionList[i].ucRatNum; j++ )
        {
            /* 若当前PLMN列表已满，则退出 */
            if ( NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST <= pstPlmnSelectionListInfo->usSearchPlmnNum )
            {
                return;
            }

            if ( enSpecRatType == pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j].enRatType )
            {

                /* 拷贝一份当前处理的网络信息到现有的数组列表的后面 */
                PS_MEM_CPY(&(pstPlmnSelectionListInfo->astPlmnSelectionList[pstPlmnSelectionListInfo->usSearchPlmnNum]),
                           &(pstPlmnSelectionListInfo->astPlmnSelectionList[i]),
                           sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));

                /* 将最后一个网络的接入技术个数设置为1个，且接入技术类型为用户所要设置的接入技术 */
                pstPlmnSelectionListInfo->astPlmnSelectionList[pstPlmnSelectionListInfo->usSearchPlmnNum].ucRatNum = 1;
                pstPlmnSelectionListInfo->astPlmnSelectionList[pstPlmnSelectionListInfo->usSearchPlmnNum].astPlmnRatInfo[0].enRatType = enSpecRatType;

                pstPlmnSelectionListInfo->astPlmnSelectionList[pstPlmnSelectionListInfo->usSearchPlmnNum].astPlmnRatInfo[0].enNetStatus
                    = pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j].enNetStatus;
                pstPlmnSelectionListInfo->astPlmnSelectionList[pstPlmnSelectionListInfo->usSearchPlmnNum].astPlmnRatInfo[0].enQuality
                    = pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j].enQuality;
                pstPlmnSelectionListInfo->astPlmnSelectionList[pstPlmnSelectionListInfo->usSearchPlmnNum].astPlmnRatInfo[0].lRscp
                    = pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j].lRscp;
                pstPlmnSelectionListInfo->astPlmnSelectionList[pstPlmnSelectionListInfo->usSearchPlmnNum].astPlmnRatInfo[0].ucReserve
                    = 0;

                /* 选网数组列表中的网络个数增加了1个 */
                pstPlmnSelectionListInfo->usSearchPlmnNum++;

                /* 将当前处理的网络的要移动的接入技术设置为无效值，若当前网络的接入技术不是最后一个，
                       则需要将后面的接入技术移到前面去 */
                pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j].enRatType = NAS_MML_NET_RAT_TYPE_BUTT;
                if ( (NAS_MML_MAX_RAT_NUM - 1) > j  )
                {
                    /*lint -e961*/
                    (VOS_VOID)PS_MEM_MOVE(&(pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j]),
                            &(pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j + 1] ),
                            (NAS_MML_MAX_RAT_NUM - j - 1) * sizeof(NAS_MMC_PLMN_RAT_INFO_STRU));
                    /*lint +e961*/
                }

                /* 当前处理网络的接入技术减少一个 */
                pstPlmnSelectionListInfo->astPlmnSelectionList[i].ucRatNum--;


                /* 找到了指定接入技术的网络，则退出当层循环，处理下一个网络 */
                break;

            }
        }
    }

    /* 清除表中接入技术个数为0的网络 */
    for ( i = 0; i < usSearchPlmnNum;  )
    {
        /* 若当前处理的网络的接入技术个数为0个，则删除该PLMN网络 */
        if( 0 == pstPlmnSelectionListInfo->astPlmnSelectionList[i].ucRatNum )
        {
            if (i < (NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST - 1))
            {
                /*lint -e961*/
                (VOS_VOID)PS_MEM_MOVE(&(pstPlmnSelectionListInfo->astPlmnSelectionList[i]),
                        &(pstPlmnSelectionListInfo->astPlmnSelectionList[i + 1] ),
                        (NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST - i - 1) * sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));
                /*lint +e961*/
            }

            /* 选网数组列表中的网络个数减少了1个 */
            pstPlmnSelectionListInfo->usSearchPlmnNum--;

            /* 需要判断处理接入技术为0的网络个数减少一个 */
            usSearchPlmnNum--;
            continue;
        }

        i++;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsRejectedBySpecCause
 功能描述  : 判断UE本次开机是否被指定的原因值拒绝过
 输入参数  : enDomain:指定域
             enCause:指定的原因值
 输出参数  : 无
 返 回 值  : VOS_TRUE:被拒绝过
             VOS_FALSE:未被拒绝过
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年5月09日
   作    者   : w00166186
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsRejectedBySpecCause(
    NAS_MMC_REG_DOMAIN_ENUM_UINT8       enDomain,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause
)
{
    NAS_MMC_PLMN_REG_REJ_CTX_STRU      *pstPlmnRegRejInfo = VOS_NULL_PTR;
    VOS_UINT8                           i;

    pstPlmnRegRejInfo = NAS_MMC_GetPlmnRegRejInfo();

    for (i = 0; i < pstPlmnRegRejInfo->ucPlmnRegInfoNum; i++)
    {
        if (NAS_MMC_REG_DOMAIN_PS == enDomain)
        {
            if ((enCause == pstPlmnRegRejInfo->astPlmnRegInfoList[i].enGPsRegStatus)
             || (enCause == pstPlmnRegRejInfo->astPlmnRegInfoList[i].enWPsRegStatus)
#if (FEATURE_ON == FEATURE_LTE)
             || (enCause == pstPlmnRegRejInfo->astPlmnRegInfoList[i].enLPsRegStatus)
#endif
             )
            {
                return VOS_TRUE;
            }
        }

        if (NAS_MMC_REG_DOMAIN_CS == enDomain)
        {
            if ((enCause == pstPlmnRegRejInfo->astPlmnRegInfoList[i].enGCsRegStatus)
             || (enCause == pstPlmnRegRejInfo->astPlmnRegInfoList[i].enWCsRegStatus)
#if (FEATURE_ON == FEATURE_LTE)
             || (enCause == pstPlmnRegRejInfo->astPlmnRegInfoList[i].enLCsRegStatus)
#endif
             )
            {
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;

}


/* Modified by z40661 for 泰国AIS特性 2012-05-17, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_IsAisRoamingEffect
 功能描述  : 判断AIS特殊漫游功能是否生效
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:生效
             VOS_FALSE:不生效
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月17日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsAisRoamingEffect( VOS_VOID )
{
    /******************************************************************
    1.该文档只实现自动模式下优先搜TOT的网络。
    2．只要该特定打开，并只针对AIS SIM卡优先搜TOT网络。
    3．该特性只在开机和背景搜过程中起作用。
    4．背景搜过程被SYSCFG、用户列表搜、限制服务下用户重选等会引起搜网的场景打断，不会根据搜网结果实时更新TOT网络的存在状态。需要等到下次背景搜才会搜TOT。
    *******************************************************************/
    NAS_MML_AIS_ROAMING_CFG_STRU        *pstAisRoamingCfg;


    pstAisRoamingCfg        = NAS_MML_GetAisRoamingCfg();

    /* NVIM中功能不生效时,直接返回功能不生效 */
    if ( VOS_FALSE == pstAisRoamingCfg->ucEnableFlg )
    {
        return VOS_FALSE;
    }

    /* 当前是AIS的SIM卡 */
    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn((NAS_MML_PLMN_ID_STRU*)&(pstAisRoamingCfg->stSimHPlmnId)))
    {
        return VOS_TRUE;
    }

    /* 其他情况返回VOS_FALSE */
    return VOS_FALSE;
}
/* Modified by z40661 for 泰国AIS特性 2012-05-17, end */


/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateUserSpecPlmnRegisterStatusWhenRegFail
 功能描述  : 注册失败原因值为11 12 13 15的时候清除用户手动指定网络的注册状态标志
                PS注册成功, CS注册失败, 原因为11 12 13 15的情况, 需要清除该标志.
                因为此时CS的RPLMN没有更新为用户指定的PLMN, 此后丢网等触发的搜网不能搜
                RPLMN及其EPLMN, 故需要清除该标志.
                CS注册成功, PS注册失败时, 虽然RPLMN和用户指定PLMN相同, 但为了处理对称,
                也做清除标志的处理.

 输入参数  : enRegFailCause: 注册失败的原因值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年06月04日
    作    者   : l00171473
    修改内容   : 新生成函数, DTS2012053003921, 用户手动指定网络的注册状态标志清理
  2.日    期   : 2012年11月09日
    作    者   : l65478
    修改内容   : DTS2012103005174, 在#12,#15时不需要清除注册状态标志
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateUserSpecPlmnRegisterStatusWhenRegFail(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enRegFailCause
)
{
    /* 自动模式下不需要更新该全局变量 */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        return;
    }

    if ( (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW  == enRegFailCause)
      || (NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW  == enRegFailCause))
    {
        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_FALSE);
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateUserSpecPlmnRegisterStatus
 功能描述  : 在手动搜网模式下,注册成功时,需要更新用户指定搜网的状态

 输入参数  : enCsCause: CS注册失败的原因值
             enCsCause: PS注册失败的原因值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年08月18日
    作    者   : l65478
    修改内容   : 新生成函数, DTS2012081703289
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateUserSpecPlmnRegisterStatus(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause
)
{
    /* 自动模式下不需要更新该全局变量 */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        return;
    }

    if (NAS_MML_REG_FAIL_CAUSE_NULL == enCause)
    {
        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);
    }
    else
    {
        NAS_MMC_UpdateUserSpecPlmnRegisterStatusWhenRegFail(enCause);
    }

}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateEhplmnRat_WithNvPrioHplmnAct
 功能描述  : stPlmnId,              需要更新HPLMN
              usRatForOneEhplmnItem, 单个EHPLM对应的RAT
              ulPlmnNum,             已经更新的EHPLMN的个数
 输入参数  : pstPlmnWithRatInfo     更新后的EHPLMN
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月9日
    作    者   : w00166186
    修改内容   : AT&T & DCM项目
  2.日    期   : 2012年12月28日
    作    者   : s46746
    修改内容   : DSDA GUNAS C CORE项目，增加平台是否支持LTE判断
*****************************************************************************/
VOS_VOID  NAS_MMC_UpdateEhplmnRat_WithEhplmnRatList(
    NAS_MML_PLMN_ID_STRU                stPlmnId,
    VOS_UINT16                         *pusRatForOneEhplmnItem,
    VOS_UINT32                         *pulPlmnNum,
    NAS_MML_SIM_PLMN_WITH_RAT_STRU     *pstPlmnWithRatInfo
)
{
    NAS_MML_SIM_HPLMN_WITH_RAT_INFO_STRU        *pstHplmnWithRatList= VOS_NULL_PTR;
    VOS_UINT32                                   i;
    VOS_UINT32                                   ulEqual;
    VOS_UINT16                                   usRatInUsim;
    VOS_UINT16                                   usUeSptRat;

#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
    {
        usUeSptRat          = NAS_MML_SIM_UE_SUPPORT_RAT_SUPPORT_LTE;
    }
    else
    {
        usUeSptRat          = NAS_MML_SIM_UE_SUPPORT_RAT;
    }
#else
    usUeSptRat          = NAS_MML_SIM_UE_SUPPORT_RAT;
#endif

    pstHplmnWithRatList = NAS_MML_GetSimHplmnWithRatList();
    ulEqual             = VOS_FALSE;

    /* 获取SIM的信息 */
    for (i = 0; i < pstHplmnWithRatList->ucHPlmnWithRatNum; i++)
    {
        ulEqual = NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstHplmnWithRatList->astHPlmnWithRatInfo[i].stPlmnId),
                                                     &stPlmnId);
        if (VOS_TRUE == ulEqual )
        {
            usRatInUsim = pstHplmnWithRatList->astHPlmnWithRatInfo[i].usSimRat;

            if (NAS_MML_SIM_NO_RAT == ( usRatInUsim & (NAS_MML_SIM_ALL_RAT_SUPPORT_LTE)))
            {
                usRatInUsim = usUeSptRat;
            }
            else
            {
                usRatInUsim &= usUeSptRat;
            }

            if (NAS_MML_SIM_NO_RAT != ((~*pusRatForOneEhplmnItem) & usRatInUsim))
            {
                /*保存Sim卡中存在的剩余的接入技术到临时全局变量数组*/
                pstPlmnWithRatInfo[*pulPlmnNum].usSimRat = ((~*pusRatForOneEhplmnItem) & usRatInUsim);

                pstPlmnWithRatInfo[*pulPlmnNum].stPlmnId.ulMcc = stPlmnId.ulMcc;

                pstPlmnWithRatInfo[*pulPlmnNum].stPlmnId.ulMnc = stPlmnId.ulMnc;

                (*pulPlmnNum)++;

                (*pusRatForOneEhplmnItem) |= usRatInUsim;
            }

            if ((*pulPlmnNum >= NAS_MML_MAX_EHPLMN_NUM)
             || (usUeSptRat == (*pusRatForOneEhplmnItem & usUeSptRat)))
            {
                /*  当前Plmn个数超过数组总数，或所有接入技术已添加， 退出该项的添加 */
                break;
            }
        }
    }

}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateEhplmnRat_WithNvPrioHplmnAct
 功能描述  : 根据定制的HPLMN接入次序和Sim卡中的HplmnACt文件更新EHPLMN的接入技术
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月9日
    作    者   : l00130025
    修改内容   : DTS2012060400029:添加对HPLMNAct优先接入技术的定制；目前USim卡中HPLMNACT很多不支持L
  2.日    期   : 2012年12月28日
    作    者   : s46746
    修改内容   : DSDA GUNAS C CORE项目，增加平台是否支持LTE判断
*****************************************************************************/
VOS_VOID  NAS_MMC_UpdateEhplmnRat_WithNvPrioHplmnAct(VOS_VOID)
{
    NAS_MML_PRIO_HPLMNACT_CFG_STRU              *pstNvPrioHPlmnActCfg;
    NAS_MML_SIM_EHPLMN_INFO_STRU                *pstEHPlmnInfo = VOS_NULL_PTR;
    NAS_MML_SIM_PLMN_WITH_RAT_STRU              *pstTmpPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                                   k;
    VOS_UINT32                                   i;
    VOS_UINT32                                   ulPlmnNum;
    VOS_UINT16                                   usRatForOneEhplmnItem;
    VOS_UINT16                                   usRatNeedToAdd;
    VOS_UINT16                                   usUeSptRat;

    pstNvPrioHPlmnActCfg = NAS_MML_GetPrioHplmnActCfg();

    /* 获取SIM卡中EHPLMN信息*/
    pstEHPlmnInfo       = NAS_MML_GetSimEhplmnList();

    ulPlmnNum = 0;

#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
    {
        usUeSptRat          = NAS_MML_SIM_UE_SUPPORT_RAT_SUPPORT_LTE;
    }
    else
    {
        usUeSptRat          = NAS_MML_SIM_UE_SUPPORT_RAT;
    }
#else
    usUeSptRat          = NAS_MML_SIM_UE_SUPPORT_RAT;
#endif

    pstTmpPlmnInfo  = (NAS_MML_SIM_PLMN_WITH_RAT_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC, NAS_MML_MAX_EHPLMN_NUM * sizeof(NAS_MML_SIM_PLMN_WITH_RAT_STRU));

    if ( VOS_NULL_PTR == pstTmpPlmnInfo )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdateEhplmnRat: Alloc Mem Failed ");
        return;
    }

    NAS_MML_InitSimPlmnInfo(NAS_MML_MAX_EHPLMN_NUM, pstTmpPlmnInfo);

    /*根据NV值对EHPLMN的接入技术排序*/
    for ( k = 0; k < pstEHPlmnInfo->ucEhPlmnNum; k++ )
    {
        usRatForOneEhplmnItem = 0;

        /* 将NV中设置的HPLMNAct作为最高优先级，直接添加 */
        if (ulPlmnNum < NAS_MML_MAX_EHPLMN_NUM)
        {
            pstTmpPlmnInfo[ulPlmnNum].usSimRat = pstNvPrioHPlmnActCfg->usPrioHplmnAct;

            pstTmpPlmnInfo[ulPlmnNum].stPlmnId.ulMcc = pstEHPlmnInfo->astEhPlmnInfo[k].stPlmnId.ulMcc;

            pstTmpPlmnInfo[ulPlmnNum].stPlmnId.ulMnc = pstEHPlmnInfo->astEhPlmnInfo[k].stPlmnId.ulMnc;

            ulPlmnNum++;

            usRatForOneEhplmnItem = pstNvPrioHPlmnActCfg->usPrioHplmnAct;

        }

        /* EHPLMN的添加已达到最大个数，退出 */
        if(ulPlmnNum >= NAS_MML_MAX_EHPLMN_NUM)
        {
            break;
        }

        /* 所有接入技术已添加， 退出该项的添加 */
        if (usUeSptRat == (usRatForOneEhplmnItem & usUeSptRat))
        {
            continue;
        }

        /* 获取SIM的信息 */
        NAS_MMC_UpdateEhplmnRat_WithEhplmnRatList(pstEHPlmnInfo->astEhPlmnInfo[k].stPlmnId,
                                                  &usRatForOneEhplmnItem,
                                                  &ulPlmnNum,
                                                  pstTmpPlmnInfo);

        /* 确定剩余的 要添加的RAT */
        usRatNeedToAdd = ( (~usRatForOneEhplmnItem) & usUeSptRat);

        if ((NAS_MML_SIM_NO_RAT != usRatNeedToAdd)
         && (ulPlmnNum  < NAS_MML_MAX_EHPLMN_NUM))
        {
             /* 除NV中和卡中的HplmnAct，还有对应的RAT,需要添加所有接入技术;
                或已添加部分 RAT,添加剩余的RAT
             */
            pstTmpPlmnInfo[ulPlmnNum].usSimRat       = usRatNeedToAdd;

            pstTmpPlmnInfo[ulPlmnNum].stPlmnId.ulMcc = pstEHPlmnInfo->astEhPlmnInfo[k].stPlmnId.ulMcc;

            pstTmpPlmnInfo[ulPlmnNum].stPlmnId.ulMnc = pstEHPlmnInfo->astEhPlmnInfo[k].stPlmnId.ulMnc;

            ulPlmnNum++;
        }

    }

    /* 更新Hplmn的个数和Rat列表 */
    pstEHPlmnInfo->ucEhPlmnNum = (VOS_UINT8)ulPlmnNum;
    for (i = 0; i < ulPlmnNum; i++)
    {
        pstEHPlmnInfo->astEhPlmnInfo[i].stPlmnId.ulMcc = pstTmpPlmnInfo[i].stPlmnId.ulMcc;
        pstEHPlmnInfo->astEhPlmnInfo[i].stPlmnId.ulMnc = pstTmpPlmnInfo[i].stPlmnId.ulMnc;
        pstEHPlmnInfo->astEhPlmnInfo[i].usSimRat       = pstTmpPlmnInfo[i].usSimRat;
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pstTmpPlmnInfo);
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateEhplmnRat_WithOrigSimHplmnAct
 功能描述  : 根据SIM卡中HplmnAct的原始信息，更新EHPLMN的接入技术
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年11月27日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数
  2.日    期   : 2011年2月28日
    作    者   : z00161729
    修改内容   : DTS2011021602201:正向质量hplmn的接入技术没有赋值是随机值,不影响功能只影响可维可测消息显示
  3.日    期   : 2011年4月13日
    作    者   : l00130025
    修改内容   : 修改对GUL 3模的处理
  4.日    期   : 2011年7月25日
    作    者   : w00176964
    修改内容   : V7R1 PhaseII 全局变量 状态名调整
  5.日    期   : 2011年11月30日
    作    者   : w00176964
    修改内容   : 联合注册BBIT调整

  6.日    期   : 2012年1月11日
    作    者   : w00167002
    修改内容   : DTS2012011208030:用例测试发现问题，若L下注册被拒#13后，在L下
                  不搜HOME PLMN.(D03_DTS2011102200381_Combined_Registeration_FAIL_SCENE_13)
  7.日    期   : 2012年6月9日
    作    者   : l00130025
    修改内容   : DTS2012060400029:添加对HPLMNAct优先接入技术的定制；
                 函数重命名;6F62中存在Hplmn为0x0000的记录时，HPLMN在搜网时不会被添加
  8.日    期   : 2012年12月28日
    作    者   : s46746
    修改内容   : DSDA GUNAS C CORE项目，增加平台是否支持LTE判断
*****************************************************************************/
VOS_VOID  NAS_MMC_UpdateEhplmnRat_WithOrigSimHplmnAct(VOS_VOID)
{
    NAS_MML_SIM_EHPLMN_INFO_STRU                           *pstEHPlmnInfo = VOS_NULL_PTR;
    NAS_MML_SIM_PLMN_WITH_RAT_STRU                         *pstTmpPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                                              k;
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulPlmnNum;
    VOS_UINT16                                              usRatForOneEhplmnItem;
    VOS_UINT16                                              usRatNeedToAdd;
    VOS_UINT16                                              usUeSptRat;

    /* 获取SIM卡中EHPLMN信息*/
    pstEHPlmnInfo       = NAS_MML_GetSimEhplmnList();

#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
    {
        usUeSptRat          = NAS_MML_SIM_UE_SUPPORT_RAT_SUPPORT_LTE;
    }
    else
    {
        usUeSptRat          = NAS_MML_SIM_UE_SUPPORT_RAT;
    }
#else
    usUeSptRat          = NAS_MML_SIM_UE_SUPPORT_RAT;
#endif

    /* HPLMN默认是 多个模式都支持的,HPLMNWithRat中的接入模式仅仅
    需要更新当前PLMN的接入优先级,如果当前HPLMNWithRat支持所有模式,
    则不进行修改,如果当前HPLMNWithRat支持单模或2个模式,则需要遍历HplmnWithACt,确定余下的接入技术优先级指示,
    支持 的模式 放在前面,其它模式的放在后面;
    如HplmnWithAct指示: W -> L 则最终需要有3项 Hplmn: W->L->G ;卡中指示 W,则添加为W->LG
    */
    ulPlmnNum = 0;

    pstTmpPlmnInfo  = (NAS_MML_SIM_PLMN_WITH_RAT_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC, NAS_MML_MAX_EHPLMN_NUM * sizeof(NAS_MML_SIM_PLMN_WITH_RAT_STRU));
    if ( VOS_NULL_PTR == pstTmpPlmnInfo )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdateEhplmnRat: Alloc Mem Failed ");
        return;
    }

    NAS_MML_InitSimPlmnInfo(NAS_MML_MAX_EHPLMN_NUM, pstTmpPlmnInfo);

    for ( k = 0; k < pstEHPlmnInfo->ucEhPlmnNum; k++ )
    {
        usRatForOneEhplmnItem = 0;

        /* 从SIM卡文件0x6F62中获取对应PLMN的RAT */

        NAS_MMC_UpdateEhplmnRat_WithEhplmnRatList(pstEHPlmnInfo->astEhPlmnInfo[k].stPlmnId,
                                                  &usRatForOneEhplmnItem,
                                                  &ulPlmnNum,
                                                  pstTmpPlmnInfo);

        /* 确定剩余的 要添加的RAT */
        usRatNeedToAdd = ( (~usRatForOneEhplmnItem) & usUeSptRat);

        if ((NAS_MML_SIM_NO_RAT != usRatNeedToAdd)
         && (ulPlmnNum  < NAS_MML_MAX_EHPLMN_NUM))
        {
             /* 卡中没有找到对应的RAT,需要添加所有接入技术;
                或已添加部分 RAT,添加剩余的RAT
             */
            pstTmpPlmnInfo[ulPlmnNum].usSimRat       = usRatNeedToAdd;

            pstTmpPlmnInfo[ulPlmnNum].stPlmnId.ulMcc = pstEHPlmnInfo->astEhPlmnInfo[k].stPlmnId.ulMcc;

            pstTmpPlmnInfo[ulPlmnNum].stPlmnId.ulMnc = pstEHPlmnInfo->astEhPlmnInfo[k].stPlmnId.ulMnc;

            ulPlmnNum++;
        }

    }

    /* 更新Hplmn的个数和Rat列表 */
    pstEHPlmnInfo->ucEhPlmnNum = (VOS_UINT8)ulPlmnNum;
    for (i =0;i< ulPlmnNum;i++)
    {
        pstEHPlmnInfo->astEhPlmnInfo[i].stPlmnId.ulMcc = pstTmpPlmnInfo[i].stPlmnId.ulMcc;
        pstEHPlmnInfo->astEhPlmnInfo[i].stPlmnId.ulMnc = pstTmpPlmnInfo[i].stPlmnId.ulMnc;
        pstEHPlmnInfo->astEhPlmnInfo[i].usSimRat       = pstTmpPlmnInfo[i].usSimRat;
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pstTmpPlmnInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateEhplmnRat
 功能描述  : 更新EHPLMN的接入技术
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年11月27日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数
  2.日    期   : 2011年2月28日
    作    者   : z00161729
    修改内容   : DTS2011021602201:正向质量hplmn的接入技术没有赋值是随机值,不影响功能只影响可维可测消息显示
  3.日    期   : 2011年4月13日
    作    者   : l00130025
    修改内容   : 修改对GUL 3模的处理
  4.日    期   : 2011年7月25日
    作    者   : w00176964
    修改内容   : V7R1 PhaseII 全局变量 状态名调整
  5.日    期   : 2011年11月30日
    作    者   : w00176964
    修改内容   : 联合注册BBIT调整

  6.日    期   : 2012年1月11日
    作    者   : w00167002
    修改内容   : DTS2012011208030:用例测试发现问题，若L下注册被拒#13后，在L下
                  不搜HOME PLMN.(D03_DTS2011102200381_Combined_Registeration_FAIL_SCENE_13)
  7.日    期   : 2012年6月9日
    作    者   : l00130025
    修改内容   : DTS2012060400029:添加对HPLMNAct优先接入技术的定制；目前USim卡中HPLMNACT很多不支持L
*****************************************************************************/
VOS_VOID  NAS_MMC_UpdateEhplmnRat(VOS_VOID)
{

    NAS_MML_PRIO_HPLMNACT_CFG_STRU     *pstPrioHPlmnActCfg;

    pstPrioHPlmnActCfg = NAS_MML_GetPrioHplmnActCfg();

    if ((VOS_TRUE == pstPrioHPlmnActCfg->ucActiveFlg)
     && (NAS_MML_SIM_NO_RAT != pstPrioHPlmnActCfg->usPrioHplmnAct))
    {
        /*根据NV定制的HPLMN接入次序和Sim卡中的HPLMNACt调整HPLMN的接入技术*/
        NAS_MMC_UpdateEhplmnRat_WithNvPrioHplmnAct();
    }
    else
    {
        /* 根据原始的SIM卡中的HPLMN接入次序补充EHPLMN的接入技术*/
        NAS_MMC_UpdateEhplmnRat_WithOrigSimHplmnAct();
    }
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateHomePlmn
 功能描述  : 将IMSI转变成协议栈中使用的形式存储，并
              从IMSI中解析出HOME PLMN更新到全局变量中
 输入参数  : aucIMSI:存储IMSI的数组
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月19日
    作    者   : luokaihui / l00167671
    修改内容   : 新生成函数
  2.日    期   : 2011年07月13日
    作    者   : w00176964
    修改内容   : GUNAS V7R1 PhaseII 阶段调整
  3.日    期   : 2012年8月14日
    作    者   : t00212959
    修改内容   : DCM定制需求和遗留问题,得到三位MNC
  4.日    期   : 2011年07月13日
    作    者   : w00176964
    修改内容   : V7R1C50_GUTL_PhaseII:删除对46002/46007中国移动网络的特殊处理,
                  将46002和46007转换为46000，夏苗方确认MP后台支持46002和46007的处理。
*****************************************************************************/
VOS_VOID  NAS_MMC_UpdateHomePlmn(
    VOS_UINT8                           *pucIMSI
)
{
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstEHPlmnInfo = VOS_NULL_PTR;

    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-22, begin */
    VOS_UINT8                           ucUsimMncLenth;
    VOS_UINT8                           ucExactlyComparaFlag;

    ucUsimMncLenth       = NAS_MML_GetUsimMncLen();
    ucExactlyComparaFlag = NAS_MML_GetPlmnExactlyComparaFlg();
    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-22, end */

    pstEHPlmnInfo   = NAS_MML_GetSimEhplmnList();

    pstEHPlmnInfo->ucEhPlmnNum = 1;

    PS_MEM_SET(&pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId, 0, sizeof(NAS_MML_PLMN_ID_STRU));
    pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMcc |= (pucIMSI[1] & NAS_MML_OCTET_HIGH_FOUR_BITS) >> NAS_MML_OCTET_MOVE_FOUR_BITS;
    pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMcc |= (pucIMSI[2] & NAS_MML_OCTET_LOW_FOUR_BITS) << NAS_MML_OCTET_MOVE_EIGHT_BITS;
    pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMcc |= (pucIMSI[2] & NAS_MML_OCTET_HIGH_FOUR_BITS) << NAS_MML_OCTET_MOVE_TWELVE_BITS;
    pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMnc |= (pucIMSI[3] & NAS_MML_OCTET_LOW_FOUR_BITS);
    pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMnc |= (pucIMSI[3] & NAS_MML_OCTET_HIGH_FOUR_BITS) << NAS_MML_OCTET_MOVE_FOUR_BITS;

    /* Modified by t00212959 for DCM定制需求和遗留问题, 2012-8-15, begin */
    if ((NAS_MMC_MNC_LENGTH_TWO_BYTES_IN_IMSI == ucUsimMncLenth)
     && (VOS_TRUE == ucExactlyComparaFlag))
    {
        pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMnc |= (NAS_MML_LOW_BYTE_INVALID) << NAS_MML_OCTET_MOVE_SIXTEEN_BITS;
    }
    else
    {
        pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMnc |= (pucIMSI[4] & NAS_MML_OCTET_LOW_FOUR_BITS) << NAS_MML_OCTET_MOVE_SIXTEEN_BITS;
    }
    /* Modified by t00212959 for DCM定制需求和遗留问题, 2012-8-15, end */

    /* 对于PLMN ID相同的比较，末位为0或者F的情况，已经在新的比较函数中
      处理:NAS_MMC_CompareBcchPlmnwithSimPlmn不需要添加两次PLMN ID，对于
      中移动卡的特殊处理需要保留,添加2位MNC的HPLMN到Hplmn列表中,
      移动MCC=460,MNC=02和07中国移动卡特殊处理
    */
    if (( 0x000604 == pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMcc )
     && ( (0x200   == (pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMnc & 0xFFFF ) )
       || (0x700   == (pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMnc & 0xFFFF))))
    {
        pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMnc &= 0xFF0000;
    }
}
/*****************************************************************************
 函 数 名  : NAS_MMC_DelLowPrioEHPlmn
 功能描述  : 从list搜索中仅保持EHPLMN的最高优先级的PLMN,删除其余的EHPLMN
 输入参数  : pstReportList:上报的list搜网列表
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月23日
    作    者   : t00212959
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_DelLowPrioEHPlmn(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU  *pstReportList
)
{
    NAS_MML_SIM_EHPLMN_INFO_STRU           *pstEHPlmnList;
    VOS_UINT32                              i,j;
    VOS_UINT8                               ucHighPrioPlmn;
    VOS_UINT16                              usSearchPlmnNum;
    NAS_MML_PLMN_ID_STRU                    stHighPrioPlmnId;

    pstEHPlmnList   = NAS_MML_GetSimEhplmnList();
    ucHighPrioPlmn  = VOS_TRUE;
    usSearchPlmnNum = pstReportList->usSearchPlmnNum;

    stHighPrioPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    stHighPrioPlmnId.ulMnc = NAS_MML_INVALID_MNC;

    for ( i = 0 ; i < pstEHPlmnList->ucEhPlmnNum ; i++ )
    {
        for ( j = 0 ; j < pstReportList->usSearchPlmnNum ; j++ )
        {
            /* 先找到当前优先级最高的EHPLMN在list中存在 */
            if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&pstReportList->astPlmnSelectionList[j].stPlmnId,
                                                               &pstEHPlmnList->astEhPlmnInfo[i].stPlmnId))
            {
                /* 仅保留最高优先级的EHPLMN */
                if ( VOS_TRUE == ucHighPrioPlmn )
                {
                    ucHighPrioPlmn         = VOS_FALSE;
                    stHighPrioPlmnId.ulMcc = pstEHPlmnList->astEhPlmnInfo[i].stPlmnId.ulMcc;
                    stHighPrioPlmnId.ulMnc = pstEHPlmnList->astEhPlmnInfo[i].stPlmnId.ulMnc;
                    continue;
                }

                if (VOS_FALSE == NAS_MML_CompareBcchPlmnwithSimPlmn(&stHighPrioPlmnId,
                                                               &pstEHPlmnList->astEhPlmnInfo[i].stPlmnId))
                {
                    /* 删除其他的PLMN */
                    /*lint -e961*/
                    (VOS_VOID)PS_MEM_MOVE(&(pstReportList->astPlmnSelectionList[j]),
                                &(pstReportList->astPlmnSelectionList[j + 1]),
                                ((pstReportList->usSearchPlmnNum- j - 1) * sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU)));
                    /*lint +e961*/
                    usSearchPlmnNum--;
                }
            }
        }
    }

    pstReportList->usSearchPlmnNum = usSearchPlmnNum;
}




#if (FEATURE_ON == FEATURE_LTE)

/* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-14, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGuSysInfoIndSetLteRoamAbility
 功能描述  : 收到GU接入层的系统消息后，进行disable L 或者 enable L
 输入参数  : ulSysInfoMcc        - GU上报的系统消息所带上的国家码
             enLCapabilityStatus - 现在的LTE能力状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月14日
    作    者   : t00212959
    修改内容   : 新生成函数
  2.日    期   : 2013年01月23日
    作    者   : s00217060
    修改内容   : 问题单: DTS2013012106172,Enable Lte时停止定时器TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER
  3.日    期   : 2013年11月01日
    作    者   : l00208543
    修改内容   : 根据卡类型禁止网络制式
  4.日    期   : 2015年1月5日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
*****************************************************************************/
VOS_VOID  NAS_MMC_RcvGuSysInfoIndSetLteRoamAbility(
    VOS_UINT32                                              ulSysInfoMcc,
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus
)
{    /* 是否需要禁止LTE漫游 */
    if (VOS_TRUE == NAS_MMC_IsNeedDisableLteRoam(ulSysInfoMcc))
    {
        /* 已经通知disable LTE则不需要再通知它 */
        if ((VOS_FALSE == NAS_MML_GetDisableLteRoamFlg())
         && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLCapabilityStatus))
        {
            if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE != NAS_MML_GetLteForbiddenStatusFlg())
            {
                NAS_MMC_SndDisableLteNotify(MMC_LMM_DISABLE_LTE_REASON_LTE_ROAMING_NOT_ALLOWED);

                /* 记录disable lte时驻留的网络信息 */
                NAS_MMC_SetDisabledLtePlmnId(NAS_MML_GetCurrCampPlmnId());
            }

        }

        /* 更新disable LTE能力标记 */
        NAS_MML_SetDisableLteRoamFlg(VOS_TRUE);

        if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
        {
            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_IMSI_IN_FORBIDDEN_LIST);
        }
        else
        {
            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_ROAMING_NOT_ALLOWED);
        }
        return;
    }

    /* 是否需要允许LTE漫游 */
    if (VOS_TRUE == NAS_MMC_IsNeedEnableLteRoam(ulSysInfoMcc))
    {
        /* 当前LTE能力恢复可用或者为默认值 */
        if ((NAS_MML_LTE_CAPABILITY_STATUS_BUTT == enLCapabilityStatus)
         || (NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS == enLCapabilityStatus))
        {
            NAS_MMC_SndEnableLteNotify();
            NAS_MMC_ClearDisabledLtePlmnId();
            NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
        }

        if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
        {
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER);
        }

        /* 更新disable LTE能力标记 */
        NAS_MML_SetDisableLteRoamFlg(VOS_FALSE);
    }
    return;

}
/* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-14, end */
#endif
/*****************************************************************************
 函 数 名  : NAS_MMC_IsInterNationalRoamingSearchRPLMN
 功能描述  : 判断国际漫游时是否搜RPLMN
 输入参数  : ulMcc:当前PLMN ID的国家码
 输出参数  : 无
 返 回 值  : VOS_TRUE:漫游时要搜
             VOS_FALSE:开关未开，或者在国内不搜
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年2月24日
   作    者   : t00173447
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsInterNationalRoamingSearchRPLMN(
    VOS_UINT32                          ulMcc
)
{
    VOS_UINT32                          *aulComparedMcc ;

    aulComparedMcc = NAS_MML_GetNationalMCCList();

    if( VOS_TRUE == NAS_MML_GetRoamRplmnSearchFlg() )
    {
        if (VOS_TRUE == NAS_MML_IsMccInDestMccList(ulMcc, NAS_MML_MAX_NATIONAL_MCC_NUM, aulComparedMcc))
        {
           return VOS_FALSE;
        }
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

#if (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
 函 数 名  : NAS_MCC_IsNeedDisableLteWBand
 功能描述  : 根据频段禁用LTE
 输入参数  : ulBand频段
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要disable LTE漫游
             VOS_FALSE:不需要disable LTE漫游
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年2月24日
   作    者   : t00173447
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MCC_IsNeedDisableLteWBand(
    VOS_UINT32                         ulBand
)
{
    /*需要用NV控制 */
    if (VOS_TRUE == NAS_MML_GetDisableLTEOnBandFlg())
    {
        /* 当前驻留频段为BAND9 */
        if (NAS_MMC_WCDMA_BAND_IX == ulBand)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGuSysInfoIndSetLteAbility
 功能描述  : 收到GU接入层的系统消息后，进行disable L 或者 enable L
 输入参数  : SysInfo        - GU上报的系统消息
             enLCapabilityStatus - 现在的LTE能力状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月18日
    作    者   : t00173447
    修改内容   : 新生成函数
  2.日    期   : 2015年1月5日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
  3.日    期   : 2015年3月9日
    作    者   : wx270776
    修改内容   : 3g系统消息处理时对was是否带mmc进行判断
*****************************************************************************/
VOS_VOID  NAS_MMC_RcvGuSysInfoIndSetLteAbility(
    struct MsgCB                       *pstMsg,
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus
)
{
    MSG_HEADER_STRU                    *MsgHeader      = VOS_NULL_PTR;
    RRMM_SYS_INFO_IND_STRU             *pstWrrSysinfo  = VOS_NULL_PTR;
    GRRMM_SYS_INFO_IND_ST              *pstGasSysInfo  = VOS_NULL_PTR;
    VOS_UINT32                          ulSysInfoMcc;
    VOS_UINT32                          ulBand;
    VOS_UINT32                          ucDisableLTEOnBandFlg;

    ulSysInfoMcc            = NAS_MML_INVALID_MCC;
    ulBand                  = 0;
    ucDisableLTEOnBandFlg   = VOS_FALSE;

    MsgHeader = (MSG_HEADER_STRU*)pstMsg;

    if( RRMM_SYS_INFO_IND == MsgHeader->ulMsgName )
    {
        /*3g的系统消息处理,提取MCC与BAND信息*/
        pstWrrSysinfo = (RRMM_SYS_INFO_IND_STRU*)pstMsg;

        if (VOS_TRUE == pstWrrSysinfo->bitOpPlmnId)
        {
            ulSysInfoMcc = pstWrrSysinfo->PlmnId.ulMcc;
        }
        ulBand = pstWrrSysinfo->unWcdmaBand.ulBand;
    }
    else if( GRRMM_SYS_INFO_IND == MsgHeader->ulMsgName)
    {
        /*2g的系统消息处理,提取MCC与BAND信息*/
        pstGasSysInfo = (GRRMM_SYS_INFO_IND_ST*)pstMsg;
        ulSysInfoMcc = pstGasSysInfo->PlmnId.ulMcc;
        ulBand = pstGasSysInfo->unGsmBand.ulBand;
    }
    else
    {
        return;
    }

    ucDisableLTEOnBandFlg = NAS_MCC_IsNeedDisableLteWBand(ulBand);

    /* 是否需要禁止LTE漫游 */
    if ( (VOS_TRUE == NAS_MMC_IsNeedDisableLteRoam(ulSysInfoMcc))
      || (VOS_TRUE == ucDisableLTEOnBandFlg) )
    {
        /* 已经通知disable LTE则不需要再通知它 */
        if ((VOS_FALSE == NAS_MML_GetDisableLteRoamFlg())
         && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLCapabilityStatus))
        {
            NAS_MMC_SndDisableLteNotify(MMC_LMM_DISABLE_LTE_REASON_LTE_ROAMING_NOT_ALLOWED);

            /* 记录disable lte时驻留的网络信息 */
            NAS_MMC_SetDisabledLtePlmnId(NAS_MML_GetCurrCampPlmnId());
        }

        /* 更新disable LTE能力标记 */
        NAS_MML_SetDisableLteRoamFlg(VOS_TRUE);

        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_ROAMING_NOT_ALLOWED);
        return;
    }

    /* 是否需要允许LTE漫游 */
    if ( (VOS_TRUE  == NAS_MMC_IsNeedEnableLteRoam(ulSysInfoMcc))
      && (VOS_FALSE == ucDisableLTEOnBandFlg) )
    {
        /* 当前LTE能力恢复可用或者为默认值 */
        if ((NAS_MML_LTE_CAPABILITY_STATUS_BUTT == enLCapabilityStatus)
         || (NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS == enLCapabilityStatus))
        {
            NAS_MMC_SndEnableLteNotify();
            NAS_MMC_ClearDisabledLtePlmnId();
            NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
        }

        if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
        {
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER);
        }

        /* 更新disable LTE能力标记 */
        NAS_MML_SetDisableLteRoamFlg(VOS_FALSE);
    }
    return;

}

#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_DelHplmnInFplmn
 功能描述  : 删除FPLMN中HPLMN
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年02月25日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2011年7月25日
    作    者   : w00176964
    修改内容   : V7R1 PhaseII 全局变量 状态名调整
  3.日    期   : 2012年8月24日
    作    者   : w00167002
    修改内容   : 更改原函数NAS_MMC_DelHplmnInFplmn_SwitchOn的函数名字，并调整
                  函数的文件位置，函数内容功能不涉及修改
*****************************************************************************/
VOS_VOID NAS_MMC_DelHplmnInFplmn(VOS_VOID)
{
    VOS_INT8                            i;
    VOS_UINT8                           ucForbPlmnNum;
    VOS_UINT32                          ulHplmnInFplmnFlg;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo;

    pstForbidPlmnInfo           = NAS_MML_GetForbidPlmnInfo();

    ucForbPlmnNum               = pstForbidPlmnInfo->ucForbPlmnNum;
    ulHplmnInFplmnFlg           = VOS_FALSE;

    for (i = 0; i < ucForbPlmnNum; i++)
    {
        /* 如果hplmn在fplmn列表中则删除fplmn全局变量中的记录,否则无法发起hplmn的注册 */
        if ((VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(&(pstForbidPlmnInfo->astForbPlmnIdList[i]))))
        {
            if ( i < (ucForbPlmnNum - 1) )
            {
                (VOS_VOID)PS_MEM_MOVE(&pstForbidPlmnInfo->astForbPlmnIdList[i],
                            &pstForbidPlmnInfo->astForbPlmnIdList[i+1],
                            ((ucForbPlmnNum - i) - 1) * sizeof(NAS_MML_PLMN_ID_STRU ) );
            }
            ucForbPlmnNum--;
            i--;
            ulHplmnInFplmnFlg = VOS_TRUE;
        }
    }

    pstForbidPlmnInfo->ucForbPlmnNum = ucForbPlmnNum;

    if (VOS_TRUE == ulHplmnInFplmnFlg)
    {
        /* 如果HPLMN存在于FPLMN中认为卡文件不合法,从FPLMN中删除HPLMN记录 */
        NAS_MMC_SndUsimUpdateForbPlmnReq();
    }

}

#if (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertPlmnIdListToGUFormat
 功能描述  : 将L格式的PLMN ID列表转换成GU格式的PLMN ID列表
 输入参数  : pstSrcPlmnIdList  需要转换的PLMN ID列表
 输出参数  : pstDestPlmnIdList 转换后的PLMN ID列表
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月24日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年4月28日
    作    者   : t00212959
    修改内容   : GUL BG项目调整: L模接口改变
  3.日    期   : 2015年10月21日
    作    者   : s00217060
    修改内容   : 修改函数名
*****************************************************************************/
VOS_VOID NAS_MMC_ConvertLmmPlmnIdListToGUFormat(
    MMC_LMM_PLMN_ID_LIST_STRU          *pstSrcPlmnIdList,
    RRC_PLMN_ID_LIST_STRU              *pstDestPlmnIdList
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    NAS_MML_PLMN_ID_STRU                stPlmn;
    MMC_LMM_PLMN_ID_STRU                stLmmPlmn;
    RRC_NAS_RAT_TYPE_ENUM_UINT32        ulRrcRat;

    ulRrcRat = RRC_NAS_RAT_TYPE_BUTT;

    /* 先转换低质量网络列表 */
    if (pstSrcPlmnIdList->ulLowPlmnNum > RRC_MAX_LOW_PLMN_NUM)
    {
        pstSrcPlmnIdList->ulLowPlmnNum = RRC_MAX_LOW_PLMN_NUM;
    }

    pstDestPlmnIdList->ulLowPlmnNum = pstSrcPlmnIdList->ulLowPlmnNum;

    for ( i = 0; i < pstSrcPlmnIdList->ulLowPlmnNum; i++)
    {
        /* 将L格式的PLMN 列表转换成GU格式的*/
        for ( j = 0; j < MMC_LMM_PLMN_ID_LEN; j++)
        {
            stLmmPlmn.aucPlmnId[j] = pstSrcPlmnIdList->astLowPlmnWithRatList[i].stPlmnIdWithRat.aucPlmnId[j];
        }
        NAS_MMC_ConvertLmmPlmnToGUNasFormat(&stLmmPlmn,
                                            &stPlmn);
        pstDestPlmnIdList->aLowPlmnList[i].PlmnId.stPlmnId.ulMcc = stPlmn.ulMcc;

        pstDestPlmnIdList->aLowPlmnList[i].PlmnId.stPlmnId.ulMnc = stPlmn.ulMnc;

        NAS_MMC_ConvertLmmRatToRrcFormat(pstSrcPlmnIdList->astLowPlmnWithRatList[i].stPlmnIdWithRat.enPlmnRat, &ulRrcRat);

        pstDestPlmnIdList->aLowPlmnList[i].PlmnId.ulRat = ulRrcRat;

        pstDestPlmnIdList->aLowPlmnList[i].lRscp =
                                pstSrcPlmnIdList->astLowPlmnWithRatList[i].lRscp;
    }

    /* 转换高质量网络列表 */
    if (pstSrcPlmnIdList->ulHighPlmnNum > RRC_MAX_HIGH_PLMN_NUM)
    {
        pstSrcPlmnIdList->ulHighPlmnNum = RRC_MAX_HIGH_PLMN_NUM;
    }

    pstDestPlmnIdList->ulHighPlmnNum = pstSrcPlmnIdList->ulHighPlmnNum;

    for ( i=0; i < pstSrcPlmnIdList->ulHighPlmnNum; i++)
    {
        /* 将L格式的PLMN 列表转换成GU格式的*/
        for ( j = 0; j < MMC_LMM_PLMN_ID_LEN; j++)
        {
            stLmmPlmn.aucPlmnId[j] = pstSrcPlmnIdList->astHighPlmnWithRatList[i].aucPlmnId[j];
        }

        NAS_MMC_ConvertLmmPlmnToGUNasFormat(&stLmmPlmn,
                                            &stPlmn);

        pstDestPlmnIdList->aHighPlmnList[i].stPlmnId.ulMcc = stPlmn.ulMcc;

        pstDestPlmnIdList->aHighPlmnList[i].stPlmnId.ulMnc = stPlmn.ulMnc;

        NAS_MMC_ConvertLmmRatToRrcFormat(pstSrcPlmnIdList->astHighPlmnWithRatList[i].enPlmnRat, &ulRrcRat);

        pstDestPlmnIdList->aHighPlmnList[i].ulRat = ulRrcRat;

    }
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedPsRelConnEnableLteTimerExpired
 功能描述  : 判断enable lte定时器超时是否需要主动释放ps连接
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_FALSE:不需要释放链接
             VOS_TRUE: 需要释放链接
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年4月20日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedRelPsConnEnableLteTimerExpired(VOS_VOID)
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus  = VOS_NULL_PTR;
    NAS_MML_GMM_PROC_INFO_STRU         *pstGmmProcInfo = VOS_NULL_PTR;

    /* 取得当前的链接信息 */
    pstConnStatus    = NAS_MML_GetConnStatus();
    pstGmmProcInfo   = NAS_MML_GetGmmProcInfo();

    /* 不存在rrc连接，返回false不需要主动释放连接 */
    if (VOS_FALSE == NAS_MML_IsRrcConnExist())
    {
        return VOS_FALSE;
    }

    /* 如果存在cs业务，返回false不需要主动释放连接 */
    if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
    {
        return VOS_FALSE;
    }

    /* 如果存在cs信令连接lau流程，返回false不需要主动释放连接 */
    if (VOS_TRUE == pstConnStatus->ucCsSigConnStatusFlg)
    {
        return VOS_FALSE;
    }

    /* 如果gmm在注册流程，返回false，不需要主动释放连接 */
    if ((NAS_MML_GMM_PROC_TYPE_INVALID != pstGmmProcInfo->enGmmProcType)
     && (NAS_MML_GMM_PROC_FLAG_START == pstGmmProcInfo->enGmmProcFlag))
    {
        return VOS_FALSE;
    }

    /* sm在进行pdp激活、去激活、modify流程，返回false，不需要主动释放连接 */
    if (NAS_MML_SM_PROC_FLAG_START == NAS_MML_GetSmProcFlag())
    {
        return VOS_FALSE;
    }

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsDisableLteNeedLocalReleaseEpsConn
 功能描述  : 判断是否需要释放EPS链接
 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOS_FALSE:不需要释放EPS链接
              VOS_TRUE: 需要释放EPS链接
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年11月22日
   作    者   : t00212959
   修改内容   : 新生成函数
 2.日    期   : 2012年12月4日
   作    者   : t00212959
   修改内容   : DTS2012120302949 EPS only #16,#17,#22满5此种互动释放链接
 3.日    期   : 2014年01月10日
   作    者   : w00176964
   修改内容   : VoLTE_PhaseIII项目
 4.日    期   : 2014年5月19日
   作    者   : w00242748
   修改内容   : DTS2014051308442:L下注册成功支持IMS，但SMS ONLY，周期性TAU被16拒一次，直接disable
                LTE。
 5.日    期   : 2015年4月20日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
 6.日    期   : 2015年6月19日
   作    者   : z00161729
   修改内容   : 24008 23122 R11 CR升级项目修改

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsDisableLteNeedLocalReleaseEpsConn(VOS_VOID)
{
    NAS_MML_ADDITION_UPDATE_RSLT_INFO_ENUM_UINT8            enAdditionUpdateRslt;
    VOS_UINT32                                              ulCsDomainUnAvailFlg;
    MMC_LMM_DISABLE_LTE_REASON_ENUM_UINT32                  enDisableLteReason;

    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegCause;
    VOS_UINT32                                              ulAttempCounter;

    /* Attempt Counter 初始化为0 */
    ulAttempCounter = 0;

    enPsRegCause = NAS_MML_REG_FAIL_CAUSE_NULL;
    enCsRegCause = NAS_MML_REG_FAIL_CAUSE_NULL;

    enAdditionUpdateRslt = NAS_MML_GetAdditionUpdateRslt();
    ulCsDomainUnAvailFlg = VOS_FALSE;
    enDisableLteReason   = NAS_MML_GetDisableLteReason();

    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-18, begin */
    /* disable LTE，并且原因是IMS VOICE不可用需要通知L释放链接*/
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS  != NAS_MML_GetLteCapabilityStatus())
     || (MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE != enDisableLteReason))
    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-18, end */
    {
        return VOS_FALSE;
    }


    NAS_MMC_GetDomainRegStatusInRegInfoList( NAS_MML_GetCurrCampPlmnId(),
                                             NAS_MML_NET_RAT_TYPE_LTE,
                                             &enCsRegCause,
                                             &enPsRegCause );

    /* 获取L下的尝试次数*/
    ulAttempCounter = NAS_MMC_GetRegRsltAttemptCounter(NAS_MMC_GetRegRsltType());

    /* EPS only 成功，#16,#17,#22需要disable lte时主动释放链接*/
    if ((NAS_MML_REG_FAIL_CAUSE_NULL == enPsRegCause)
     && (NAS_MML_MAX_PS_REG_FAIL_CNT <= ulAttempCounter))
    {
        /* 24301_CR1884R4_(Rel-11)_C1-140658-C1-140643-C1-140393-C1-140368-C1-140004-24301-b90-TA-IMSVoPS-EPS-only
          TAU ACCEPT，EPS ONLY成功，被拒原因值为16,17，CS/PS1，DIABLE LTE的条件增加
          persistent EPS bearer是否存在，对应24301 5.5.3.3.4.3章节:
              #16 and #17:a UE operating in CS/PS mode 1 of operation with "IMS voice not available"
          and with a persistent EPS bearer context shall wait until the radio bearer
          associated with the persistent EPS bearer context has been released. When
          the radio bearer associated with the persistent EPS bearer context has been
          released and the UE is registered for EPS services only, operating in CS/PS
          mode 1 of operation with "IMS voice not available", then the UE shall attempt
          to select GERAN or UTRAN radio access technology and proceed with appropriate
          MM or GMM specific procedures and disable the E-UTRA capability (see subclause 4.5).
          该CR受协议版本控制 */
        if (NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE == enCsRegCause)
        {
            return NAS_MMC_IsNeedDisableL_RegFailCause16AttmptCntMaxTimes();
        }

        if (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE == enCsRegCause)
        {
            return NAS_MMC_IsNeedDisableL_RegFailCause17AttmptCntMaxTimes();
        }

        if (NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION == enCsRegCause)
        {
            return NAS_MMC_IsNeedDisableL_RegFailCause22AttmptCntMaxTimes();
        }

        return VOS_TRUE;
    }

    /*是否在#18列表中*/
    ulCsDomainUnAvailFlg = NAS_MML_IsPlmnIdInCsDomainUnAvailPlmnList(NAS_MML_GetCurrCampPlmnId());

    /* 在#18列表中，SMS ONLY ,CSFB NOT PREFERRED需要通知L释放链接*/
    if ((VOS_TRUE == NAS_MMC_IsNeedDisableL_CombinedRegSuccAdditionUpdateRslt(enAdditionUpdateRslt))
     || (VOS_TRUE == ulCsDomainUnAvailFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_IsPlmnMccSameWithRplmn
 功能描述  : 判断MCC是否在和rplmn的mcc相同
 输入参数  : ulMcc - 需要判断的MCC
 输出参数  : 无
 返 回 值  : VOS_TRUE  : MCC与rplmn的mcc相同
             VOS_FALSE : MCC与rplmn的mcc不同
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2014年10月30日
   作    者   : z00161729
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlmnMccSameWithRplmn(
    VOS_UINT32                          ulMcc
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRPlmnCfg  = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stRPlmnId;
    VOS_UINT32                          i;

    PS_MEM_SET(&stRPlmnId, 0, sizeof(stRPlmnId));
    i = 0;

    pstPrioRatList = NAS_MML_GetMsPrioRatList();

    /* 获取RPLMN配置信息 */
    pstRPlmnCfg = NAS_MML_GetRplmnCfg();

    /* 与所有支持接入技术的rplmn的mcc比较,因为多rplmn特性开启时，gul的rplmn可能会不同,
       如果多rplmn特性关闭，则只跟当前接入技术rplmn mcc比较，因为即使是单rplmn场景，也存在gu下rplmn和lte下不同的场景*/
    if (VOS_FALSE == pstRPlmnCfg->ucMultiRATRplmnFlg)
    {
        if (VOS_FALSE == NAS_MMC_GetRPlmn_PlmnSelectionStrategy(NAS_MML_GetLastRplmnRat(), &stRPlmnId))
        {
            /* rplmn不存在返回false*/
            return VOS_FALSE;
        }

        if (VOS_TRUE == NAS_MML_ComparePlmnMcc(ulMcc, stRPlmnId.ulMcc))
        {
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }

    /* 多rplmn特性开启 */
    for (i = 0; i < pstPrioRatList->ucRatNum; i++)
    {
        if (VOS_FALSE == NAS_MMC_GetRPlmn_PlmnSelectionStrategy(pstPrioRatList->aucRatPrio[i], &stRPlmnId))
        {
            continue;
        }

        if (VOS_TRUE == NAS_MML_ComparePlmnMcc(ulMcc, stRPlmnId.ulMcc))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsPlmnMccSameWithHplmn
 功能描述  : 判断MCC是否在和hplmn的mcc相同
 输入参数  : ulMcc - 需要判断的MCC
 输出参数  : 无
 返 回 值  : VOS_TRUE  : MCC与hplmn的mcc相同
             VOS_FALSE : MCC与hplmn的mcc不同
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2014年10月30日
   作    者   : z00161729
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlmnMccSameWithHplmn(
    VOS_UINT32                          ulMcc
)
{
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstEHPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                          i;

    /* 获取EHPLMN */
    pstEHPlmnInfo = NAS_MML_GetSimEhplmnList();

    for (i = 0; i < pstEHPlmnInfo->ucEhPlmnNum; i++)
    {
        if (VOS_TRUE == NAS_MML_ComparePlmnMcc(ulMcc,
                             pstEHPlmnInfo->astEhPlmnInfo[i].stPlmnId.ulMcc))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_IsPlmnSameWithRplmn
 功能描述  : 判断PLMN是否是RPLMN
 输入参数  : 待判断的PLMN
 输出参数  : 无
 返 回 值  : VOS_TRUE  : 相同；VOS_FALSE : 不同
 调用函数  :
 被调函数  :
 修改历史     :
 1.日    期   : 2015年10月21日
   作    者   : s00193151
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlmnSameWithRplmn(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRPlmnCfg    = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stRPlmnId;
    VOS_UINT32                          i;

    PS_MEM_SET(&stRPlmnId, 0, sizeof(stRPlmnId));

    pstPrioRatList = NAS_MML_GetMsPrioRatList();

    /* 获取RPLMN配置信息 */
    pstRPlmnCfg = NAS_MML_GetRplmnCfg();

    /* 与所有支持接入技术的rplmn的mcc比较,因为多rplmn特性开启时，gul的rplmn可能会不同,
       如果多rplmn特性关闭，则只跟当前接入技术rplmn mcc比较，因为即使是单rplmn场景，也存在gu下rplmn和lte下不同的场景*/
    if (VOS_FALSE == pstRPlmnCfg->ucMultiRATRplmnFlg)
    {
        if (VOS_FALSE == NAS_MMC_GetRPlmn_PlmnSelectionStrategy(NAS_MML_GetLastRplmnRat(), &stRPlmnId))
        {
            /* rplmn不存在返回false*/
            return VOS_FALSE;
        }

        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstPlmnId, &stRPlmnId))
        {
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }

    /* 多rplmn特性开启 */
    for (i = 0; i < pstPrioRatList->ucRatNum; i++)
    {
        if (VOS_FALSE == NAS_MMC_GetRPlmn_PlmnSelectionStrategy(pstPrioRatList->aucRatPrio[i], &stRPlmnId))
        {
            continue;
        }

        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstPlmnId, &stRPlmnId))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;

}

#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 函 数 名  : NAS_MMC_GetCsgIdIndexInDestCsgIdList
 功能描述  : 获取csd id在指定csg id列表中的索引
 输入参数  : ulCsgId        - 指定csg id
             ucDestCsgIdNum - CSG ID个数
             pstCsgIdlist   - CSG ID列表
 输出参数  : 无
 返 回 值  : 索引
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年9月15日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetCsgIdIndexInDestCsgIdList(
    NAS_MML_PLMN_WITH_CSG_ID_STRU      *pstPlmnWithCsgId,
    VOS_UINT32                          ulDestCsgIdNum,
    NAS_MML_PLMN_WITH_CSG_ID_INFO_STRU *pstDestCsgIdlist
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulIndex;

    ulIndex = NAS_MML_MIN(NAS_MML_MAX_PLMN_CSG_ID_NUM, ulDestCsgIdNum);

    for ( i = 0; i < ulIndex; i++ )
    {
        if ((VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstPlmnWithCsgId->stPlmnId), &(pstDestCsgIdlist[i].stPlmnWithCsgId.stPlmnId)))
         && (pstPlmnWithCsgId->ulCsgId == pstDestCsgIdlist[i].stPlmnWithCsgId.ulCsgId))
        {
            break;
        }
    }

    return i;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsPlmnWithCsgIdInDestCsgIdWithHomeNodeBNameList
 功能描述  : 判断CSG ID是否在目标CSG List中
 输入参数  : pstPlmnWithCsgId - 指定csg id
             ulPlmnWithCsgIdListNum   - csg id列表个数
             pstPlmnWithCsgIdList     - CSG ID列表
 输出参数  : 无
 返 回 值  : VOS_TRUE  : 在目标CSG List中
             VOS_FALSE : 不在目标CSG List中
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年9月15日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlmnWithCsgIdInDestCsgIdWithHomeNodeBNameList(
    NAS_MML_PLMN_WITH_CSG_ID_STRU      *pstPlmnWithCsgId,
    VOS_UINT32                          ulPlmnWithCsgIdListNum,
    NAS_MML_PLMN_WITH_CSG_ID_INFO_STRU *pstPlmnWithCsgIdList
)
{
    VOS_UINT32                          ulIndex;

    for (ulIndex = 0; ulIndex < NAS_MML_MIN(NAS_MML_MAX_PLMN_CSG_ID_NUM, ulPlmnWithCsgIdListNum); ulIndex++)
    {
        if ((VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&pstPlmnWithCsgId->stPlmnId, &(pstPlmnWithCsgIdList[ulIndex].stPlmnWithCsgId.stPlmnId)))
          && (pstPlmnWithCsgId->ulCsgId == pstPlmnWithCsgIdList[ulIndex].stPlmnWithCsgId.ulCsgId))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsPlmnCsgIdInForbidCsgList
 功能描述  : 判断CSG ID是否在Forbbiden LIST中
 输入参数  : pstPlmnCsgId - 指定CSG ID信息
 输出参数  : 无
 返 回 值  : VOS_TRUE  : 在；VOS_FALSE : 不在
 调用函数  :
 被调函数  :
 修改历史     :
 1.日    期   : 2015年10月21日
   作    者   : s00193151
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlmnCsgIdInForbiddenCsgList(
    NAS_MML_PLMN_WITH_CSG_ID_STRU      *pstPlmnCsgId
)
{
    VOS_UINT32                                              i;
    NAS_MML_CSG_ID_WITH_FORBIDDEN_PERIOD_LIST_STRU         *pstForbiddenList = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                                    stPlmnId;

    stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    pstForbiddenList = NAS_MML_GetForbiddenCsgList();

    for (i = 0; i < NAS_MML_MIN(pstForbiddenList->ulForbiddenCsgIdNum, NAS_MML_MAX_FORBIDDEN_CSG_ID_NUM); i++)
    {
        stPlmnId.ulMcc = pstForbiddenList->astForbiddenCsgIdPeriodInfo[i].stPlmnWithCsgIdInfo.stPlmnId.ulMcc;
        stPlmnId.ulMnc = pstForbiddenList->astForbiddenCsgIdPeriodInfo[i].stPlmnWithCsgIdInfo.stPlmnId.ulMnc;

        if ((VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&pstPlmnCsgId->stPlmnId, &stPlmnId))
         && (pstPlmnCsgId->ulCsgId == pstForbiddenList->astForbiddenCsgIdPeriodInfo[i].stPlmnWithCsgIdInfo.ulCsgId))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_IsBcchPlmnInInDestLowPlmnInfoList
 功能描述  : 判断PLMN是否在低质量网络列表中
 输入参数  : pstBcchPlmnId  - plmn信息
             ulPlmnNum      - 低质量网络列表个数
             pstLowPlmnList - 低质量网络列表信息
 输出参数  : 无
 返 回 值  : VOS_TRUE - 存在；VOS_FALSE- 不存在
 调用函数  :
 被调函数  :
 修改历史     :
 1.日    期   : 2015年10月21日
   作    者   : z00161729
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsBcchPlmnInInDestLowPlmnInfoList(
    NAS_MML_PLMN_ID_STRU               *pstBcchPlmnId,
    VOS_UINT32                          ulPlmnNum,
    NAS_MMC_LOW_PLMN_INFO_STRU         *pstLowPlmnList
)
{
    VOS_UINT32                          i;

    for ( i = 0; i < ulPlmnNum; i++ )
    {
        if ( VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstBcchPlmnId,
                                                            &(pstLowPlmnList[i].stPlmnId)) )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetMccListInRrcPlmnIdList
 功能描述  : 从GU RRC的PLMN ID列表中获取MCC列表
 输入参数  : pstRrcPlmnIdList:目的PLMN ID列表
 输出参数  : *pulMccNum:MCC列表个数
             pulMccList:MCC列表
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012-08-14
    作    者   : W00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_MMC_GetMccListInRrcPlmnIdList(
    VOS_UINT32                         *pulMccNum,
    VOS_UINT32                         *pulMccList,
    RRC_PLMN_ID_LIST_STRU              *pstRrcPlmnIdList
)
{
    VOS_UINT32                          i;

    *pulMccNum = 0;

    if (pstRrcPlmnIdList->ulHighPlmnNum > RRC_MAX_HIGH_PLMN_NUM)
    {
        pstRrcPlmnIdList->ulHighPlmnNum = RRC_MAX_HIGH_PLMN_NUM;
    }

    /* 遍历高质量网络 */
    for (i = 0; i < pstRrcPlmnIdList->ulHighPlmnNum; i++)
    {
        /*lint -e961*/
        pulMccList[(*pulMccNum)++]= pstRrcPlmnIdList->aHighPlmnList[i].stPlmnId.ulMcc;
        /*lint +e961*/
    }

    if (pstRrcPlmnIdList->ulLowPlmnNum > RRC_MAX_LOW_PLMN_NUM)
    {
        pstRrcPlmnIdList->ulLowPlmnNum = RRC_MAX_LOW_PLMN_NUM;
    }

    /* 遍历低质量网络 */
    for (i = 0; i < pstRrcPlmnIdList->ulLowPlmnNum; i++)
    {
        /*lint -e961*/
        pulMccList[(*pulMccNum)++] = pstRrcPlmnIdList->aLowPlmnList[i].PlmnId.stPlmnId.ulMcc;
        /*lint +e961*/

    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_DelPlmnSelectionRatInfoInPlmnWithRatList
 功能描述  : 在列表中查找指定的PLMN的接入技术，若找到，则删除指定的PLMN的接入技术
 输入参数  :
             NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU *pstPlmn,
             VOS_UINT8                              ucPlmnNum,
             NAS_MML_PLMN_WITH_RAT_STRU            *pstPlmnIdList
 输出参数  : pstPlmn
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月15日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2012年8月30日
    作    者   : w00167002
    修改内容   : 函数逻辑错误，如果当前有两个接入技术，第一个被禁止的话，
                 第二个接入技术未被禁止，会导致错误。
*****************************************************************************/
VOS_VOID  NAS_MMC_DelPlmnSelectionRatInfoInPlmnWithRatList (
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmn,
    VOS_UINT32                                              ulPlmnNum,
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstPlmnIdList
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           j;

    /* 在列表中查找指定的PLMN的接入技术 */
    for (i = 0; i < ulPlmnNum; i++)
    {
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstPlmnIdList[i].stPlmnId),
                                                            &(pstPlmn->stPlmnId)))
        {
            j = 0;

            while ( j < (pstPlmn->ucRatNum) )
            {
                if (pstPlmnIdList[i].enRat == pstPlmn->astPlmnRatInfo[j].enRatType)
                {
                    if (j < (pstPlmn->ucRatNum - 1))
                    {

                        /*lint -e961*/
                        (VOS_VOID)PS_MEM_MOVE(&(pstPlmn->astPlmnRatInfo[j]),
                                    &(pstPlmn->astPlmnRatInfo[j + 1]),
                                    (NAS_MML_MAX_RAT_NUM - j - 1) * sizeof(NAS_MMC_PLMN_RAT_INFO_STRU));
                        /*lint +e961*/
                    }

                    (pstPlmn->ucRatNum)--;

                    continue;
                }

                j++;
            }
        }
    }

    return;
}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_SndEnableLteNotify
 功能描述  : enable lte后通知接入层
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月20日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
*****************************************************************************/
VOS_VOID  NAS_MMC_SndEnableLteNotify(VOS_VOID)
{
    /* 向WAS/GAS发送enable LTE通知消息 */
    NAS_MMC_SndAsLteCapabilityStatus(WUEPS_PID_WRR, RRC_NAS_LTE_CAPABILITY_STATUS_REENABLE);
    NAS_MMC_SndAsLteCapabilityStatus(UEPS_PID_GAS, RRC_NAS_LTE_CAPABILITY_STATUS_REENABLE);

    /* 向LMM发送enable LTE消息 */
    NAS_MMC_SndLmmEnableLteNotify();
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndDisableLteNotify
 功能描述  : disable lte后通知接入层
 输入参数  : enDisableLteReason - disable lte原因值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月20日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
*****************************************************************************/
VOS_VOID  NAS_MMC_SndDisableLteNotify(
    MMC_LMM_DISABLE_LTE_REASON_ENUM_UINT32                  enDisableLteReason
)
{
    /* 向WAS/GAS发送disable LTE通知消息 */
    NAS_MMC_SndAsLteCapabilityStatus(WUEPS_PID_WRR, RRC_NAS_LTE_CAPABILITY_STATUS_DISABLE);
    NAS_MMC_SndAsLteCapabilityStatus(UEPS_PID_GAS, RRC_NAS_LTE_CAPABILITY_STATUS_DISABLE);

    /* 向LMM发送disable LTE消息 */
    NAS_MMC_SndLmmDisableLteNotify(enDisableLteReason);
    return;
}

#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_DelPlmnSelectionRatInfoInDisabledPlmnWithForbiddenPeriodList
 功能描述  : 在列表中查找指定的PLMN的接入技术，若找到，则删除指定的PLMN的接入技术
 输入参数  : VOS_UINT8                                          ucPlmnNum,
             NAS_MML_DISABLED_PLMN_WITH_FORBIDDEN_PERIOD_STRU   *pstPlmnIdList
 输出参数  : pstPlmn
 返 回 值  : VOS_VOID
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
VOS_VOID  NAS_MMC_DelPlmnSelectionRatInfoInDisabledPlmnWithForbiddenPeriodList (
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmn,
    VOS_UINT32                                              ulPlmnNum,
    NAS_MML_DISABLED_PLMN_WITH_FORBIDDEN_PERIOD_STRU       *pstPlmnIdList
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           j;
    VOS_UINT32                          ulIndex;

    ulIndex = ulPlmnNum;

    if (ulIndex > NAS_MML_MAX_DISABLED_RAT_PLMN_NUM)
    {
        ulIndex = NAS_MML_MAX_DISABLED_RAT_PLMN_NUM;
    }

    /* 在列表中查找指定的PLMN的接入技术 */
    for (i = 0; i < ulIndex; i++)
    {
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstPlmnIdList[i].stPlmnWithRat.stPlmnId),
                                                            &(pstPlmn->stPlmnId)))
        {
            j = 0;

            while ( j < (pstPlmn->ucRatNum) )
            {
                if (pstPlmnIdList[i].stPlmnWithRat.enRat == pstPlmn->astPlmnRatInfo[j].enRatType)
                {
                    if (j < (pstPlmn->ucRatNum - 1))
                    {

                        /*lint -e961*/
                        (VOS_VOID)PS_MEM_MOVE(&(pstPlmn->astPlmnRatInfo[j]),
                                    &(pstPlmn->astPlmnRatInfo[j + 1]),
                                    (NAS_MML_MAX_RAT_NUM - j - 1) * sizeof(NAS_MMC_PLMN_RAT_INFO_STRU));
                        /*lint +e961*/
                    }

                    (pstPlmn->ucRatNum)--;

                    continue;
                }

                j++;
            }
        }
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_DeleteForbiddenRatInPlmnSeleInfo
 功能描述  : 判断SIM卡是否在禁止列表中，删除对应的禁止RAT
 输入参数  :
             NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU *pstPlmn,
 输出参数  : pstPlmn
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月01日
    作    者   : l00208543
    修改内容   : 新生成函数
  2.日    期   : 2014年1月3日
    作    者   : s00261364
    修改内容   : gmm模块Converity告警消除

*****************************************************************************/
VOS_VOID  NAS_MMC_DeleteForbiddenRatInPlmnSeleInfo (
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU *pstPlmn
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    NAS_MML_RAT_FORBIDDEN_LIST_STRU    *pstRatBlackList = VOS_NULL_PTR;

    i               = 0;
    j               = 0;
    pstRatBlackList = NAS_MML_GetRatForbiddenListCfg();

    /* 如果IMSI不在黑名单中，则返回 */
    if (VOS_FALSE == NAS_MML_GetImsiInForbiddenListFlg())
    {
        return;
    }

    /* 如果IMSI在黑名单中，需要在搜网列表中将NV中配置禁止的RAT都删除 */
    for (i = 0; i < pstRatBlackList->ucForbidRatNum; i++)
    {
        j = 0;
        while ( j < NAS_MML_MIN((pstPlmn->ucRatNum),NAS_MML_MAX_RAT_NUM) )
        {
            if (pstRatBlackList->aenForbidRatList[i] == pstPlmn->astPlmnRatInfo[j].enRatType)
            {
                if ( (j + 1) < (pstPlmn->ucRatNum) )
                {
                    /*lint -e961*/
                    (VOS_VOID)PS_MEM_MOVE(&(pstPlmn->astPlmnRatInfo[j]),
                                &(pstPlmn->astPlmnRatInfo[j + 1]),
                                (NAS_MML_MAX_RAT_NUM - j - 1) * sizeof(NAS_MMC_PLMN_RAT_INFO_STRU));
                    /*lint +e961*/
                }

                (pstPlmn->ucRatNum)--;

                continue;
            }

            j++;
        }
    }

    return;
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
   作    者   : w00167002
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_AddPlmnListIntoSimEhplmnInfo(
    VOS_UINT32                          ulPlmnListNum,
    NAS_MML_PLMN_ID_STRU               *pstPlmnList,
    NAS_MMC_PLMN_TYPE_ENUM_UINT8        enSpecPlmnType,
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstEhplmnInfo
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           ucTempSimEhplmnListNum;
    NAS_MML_PLMN_ID_STRU                astTempEhplmnList[NAS_MML_MAX_EHPLMN_NUM];

    /* 将SIM中的EHplmn拷贝临时的EHplmn LIST里面，便于后面进行比较当前网络是否在EHPLMN LIST 里面 */
    for ( i = 0 ; i < pstEhplmnInfo->ucEhPlmnNum; i++ )
    {
        astTempEhplmnList[i] = pstEhplmnInfo->astEhPlmnInfo[i].stPlmnId;
    }
    ucTempSimEhplmnListNum = pstEhplmnInfo->ucEhPlmnNum;

    for ( i = 0 ; i < ulPlmnListNum; i++ )
    {
        /* 如果当前的SIM Ehplmn LIST里面的网络已满，则不添加 */
        if ( NAS_MML_MAX_EHPLMN_NUM <= pstEhplmnInfo->ucEhPlmnNum )
        {
            return;
        }

        /* 如果当前的网络在SIM Ehplmn LIST里面，则不添加 */
        if ( VOS_TRUE == NAS_MMC_IsSpecTypePlmnIdInDestPlmnList( &pstPlmnList[i],
                                                                 enSpecPlmnType,
                                                                 ucTempSimEhplmnListNum,
                                                                 astTempEhplmnList) )
        {
            continue;
        }

        /* 将PLMN ID加入到SIM Ehplmn LIST里面 */
        pstEhplmnInfo->astEhPlmnInfo[pstEhplmnInfo->ucEhPlmnNum].stPlmnId = pstPlmnList[i];
        pstEhplmnInfo->ucEhPlmnNum++;

        /* 将PLMN ID加入到临时的SIM Ehplmn LIST里面 */
        astTempEhplmnList[ucTempSimEhplmnListNum] = pstPlmnList[i];
        ucTempSimEhplmnListNum++;
    }

    return ;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsCurrentWcdmaMode
 功能描述  : 判断当前主模是否为WCDMA
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:当前主模为W
             VOS_FALSE:当前主模不为W
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月06日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsCurrentWcdmaMode(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    enRatType       = NAS_MML_GetCurrNetRatType();

    if ((NAS_UTRANCTRL_UTRAN_MODE_FDD   == NAS_UTRANCTRL_GetCurrUtranMode())
     && (NAS_MML_NET_RAT_TYPE_WCDMA     == enRatType))
    {
        return VOS_TRUE;
    }

    /* 其他情况返回VOS_FALSE */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsCurrentTdscdmaMode
 功能描述  : 判断当前主模是否为TDSCDMA
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:当前主模为TD
             VOS_FALSE:当前主模不为TD
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月11日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsCurrentTdscdmaMode(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    enRatType       = NAS_MML_GetCurrNetRatType();

    if ((NAS_UTRANCTRL_UTRAN_MODE_TDD   == NAS_UTRANCTRL_GetCurrUtranMode())
     && (NAS_MML_NET_RAT_TYPE_WCDMA     == enRatType))
    {
        return VOS_TRUE;
    }

    /* 其他情况返回VOS_FALSE */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNetRatSupportedTdscdma
 功能描述  : 判断当前接入技术是否支持TDSCDMA
 输入参数  : 无
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
VOS_UINT32 NAS_MMC_IsNetRatSupportedTdscdma(VOS_VOID)
{
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode;

    enUtranMode  = NAS_UTRANCTRL_GetCurrUtranMode();

    if ((VOS_TRUE                     == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_WCDMA))
     && (NAS_UTRANCTRL_UTRAN_MODE_TDD == enUtranMode))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


#if (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
 函 数 名  : NAS_MMC_IsEpsEmergencyAttachType
 功能描述  : 根据attach结果中的ulReqType获取是否为紧急注册标识
 输入参数  : ulReqType - l发起attach的类型
 输出参数  : VOS_TRUE  - attach类型为紧急注册
             VOS_FALSE - attach类型不为紧急注册
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月17日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT32  NAS_MMC_IsEpsEmergencyAttachType(
    MMC_LMM_ATTACH_TYPE_ENUM_UINT32     ulReqType
)
{
    if (MMC_LMM_ATT_TYPE_EPS_EMERGENCY == ulReqType)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_DelForbInfo_LmmAttRsltSucc
 功能描述  : L下注册成功时，删除对应的Forbidden信息
 输入参数  : pstLmmLai                - lai信息
             ulEpsEmergencyAttachFlag - 注册类型是否为紧急attach，VOS_TRUE:是紧急注册;VOS_FALSE:非紧急注册
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月6日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2015年4月14日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID  NAS_MMC_DelForbInfo_LmmAttRsltSucc(
    MMC_LMM_LAI_STRU                   *pstLmmLai,
    VOS_UINT32                          ulEpsEmergencyAttachFlag
)
{
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbPlmnInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstPlmn         = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                    stForbLai;

    /* 用于获取禁止LA的信息 */
    pstForbPlmnInfo     = NAS_MML_GetForbidPlmnInfo();
    pstPlmn             = NAS_MML_GetCurrCampPlmnId();
    PS_MEM_SET(&stForbLai, 0, sizeof(NAS_MML_LAI_STRU));

    /* 24301_CR1189R2_(Rel-11)_C1-113741
       1.If the attach procedure is not for emergency bearer services,
         and if the PLMN identity of the registered PLMN is a member of the list
         of "forbidden PLMNs" or the list of "forbidden PLMNs for GPRS service",
         any such PLMN identity shall be deleted from the corresponding list(s).
       2.If there is no established PDN connection for emergency bearer services
         and if the PLMN identity of the registered PLMN is a member of the list
         of "forbidden PLMNs" or the list of "forbidden PLMNs for GPRS service",
         any such PLMN identity shall be deleted from the corresponding list(s).
       该CR不受协议版本控制 */
    /* 不存在紧急PDN连接，且不是为紧急承载的attach,注册成功直接删除禁止PLMN信息,不需要判断是否为指定搜网,如果之前PS域或CS域注册
       加到禁止列表,只有在指定搜网时才会发起CS/PS的注册,注册成功便可以直接删除禁止信息 */
    if ((VOS_FALSE == NAS_MML_GetEmcPdpStatusFlg())
     && (VOS_FALSE == ulEpsEmergencyAttachFlag))
    {
        if (VOS_TRUE ==  NAS_MML_DelForbPlmn(pstPlmn))
        {
            NAS_MMC_SndUsimUpdateForbPlmnReq();
        }

        NAS_MML_DelForbGprsPlmn(pstPlmn);
    }

    /* pstLmmLai为无效值时，不需要删除ForbLai */
    if (VOS_NULL_PTR == pstLmmLai)
    {
        return;
    }

    /* 把LMM的LA转换成NAS的LA */
    NAS_MMC_ConvertLmmPlmnToGUNasFormat(&(pstLmmLai->stPlmnId), &(stForbLai.stPlmnId));
    stForbLai.aucLac[0]   = pstLmmLai->stLac.ucLac;
    stForbLai.aucLac[1]   = pstLmmLai->stLac.ucLacCnt;

    /* 接入技术为L时，LAI用ATTACH_IND消息中带的LAI，不能用当前驻留的LAI */
    (VOS_VOID)NAS_MML_DelForbLa(&stForbLai, NAS_MML_REG_DOMAIN_CS);

    /* 禁止Forbidden LA 为空，则停止 Forbidden LA TImer */
    if ( ( 0 == pstForbPlmnInfo->ucForbRegLaNum )
      && ( 0 == pstForbPlmnInfo->ucForbRoamLaNum ) )
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_FORBID_LA_TIMER);
    }

}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsLmmAttachCnfTriggerPlmnSrch
 功能描述  : 收到LMM的ATTACH CNF时候是否需要尝试搜网
 输入参数  : pstLmmAttachCnf
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月15日
    作    者   : w00167002
    修改内容   : 新生成函数: L->LWG后，会先DETACH CS/PS，MMA在收到SYSCFG CNF时候，
                 再下发ATTACH CS/PS，ATTACH失败时需要进行搜网.
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsLmmAttachCnfTriggerPlmnSrch(
    LMM_MMC_ATTACH_CNF_STRU            *pstLmmAttachCnf
)
{
    if ( NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER) )
    {
        return VOS_FALSE;
    }

    /* 当前已经处于正常服务，则不需要触发搜网 */
    if ( VOS_TRUE == NAS_MMC_IsNormalServiceStatus() )
    {
        return VOS_FALSE;
    }

    /* 当前接入技术不支持W/G，则不需要搜网 */
    if ( VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()) )
    {
        return VOS_FALSE;
    }

    switch ( pstLmmAttachCnf->ulAttachRslt)
    {
        /* 尝试触发搜网 */
        case MMC_LMM_ATT_RSLT_FAILURE :
        case MMC_LMM_ATT_RSLT_FORBID_PLMN :
        case MMC_LMM_ATT_RSLT_FORBID_PLMN_FOR_GPRS :
        case MMC_LMM_ATT_RSLT_FORBID_TA_FOR_ROAMING :
        case MMC_LMM_ATT_RSLT_FORBID_TA_FOR_RPOS :

            return VOS_TRUE;

        default:
            return VOS_FALSE;
    }

}

#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_DelForbInfo_AttRsltSucc
 功能描述  : GU下注册成功时，删除对应的Forbidden信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月6日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2013年06月03日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  3.日    期   : 2014年5月4日
    作    者   : z00161729
    修改内容   : DTS2014042816166:l csfb 到w，rau被12拒绝，lau成功没有清除forbidden信息，导致fast return到l后csfb到w相同小区电话失败
  4.日    期   : 2014年5月19日
    作    者   : w00242748
    修改内容   : DTS2014051308442:L下注册成功支持IMS，但SMS ONLY，周期性TAU被16拒一次，直接disable
                 LTE。
*****************************************************************************/
VOS_VOID  NAS_MMC_DelForbInfo_GuRegRsltSucc(
    NAS_MMC_REG_DOMAIN_ENUM_UINT8       enDomain
)
{
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbPlmnInfo = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                   *pstLai          = VOS_NULL_PTR;

    /* 用于获取禁止LA的信息 */
    pstForbPlmnInfo     = NAS_MML_GetForbidPlmnInfo();
    pstLai              = NAS_MML_GetCurrCampLai();

    /* 注册成功直接删除禁止PLMN信息,不需要判断是否为指定搜网,如果之前PS域或CS域注册
       加到禁止列表,只有在指定搜网时才会发起CS/PS的注册,注册成功便可以直接删除禁止信息 */
    if (VOS_TRUE ==  NAS_MML_DelForbPlmn(&(pstLai->stPlmnId)))
    {
        NAS_MMC_SndUsimUpdateForbPlmnReq();
    }

    if (NAS_MMC_REG_DOMAIN_CS != enDomain)
    {
        NAS_MML_DelForbGprsPlmn(&(pstLai->stPlmnId));
    }

    /* 获取CS PS的注册原因值 */

    /* 如果一个域已经被#12，13，#15拒，另一个域注册成功需要删除ForbLai */


    if (VOS_TRUE == NAS_MML_DelForbLa(pstLai, enDomain))
    {
        NAS_MMC_SndRrMmCellSelReq(RRC_NAS_FORBLA_CHANGE);
    }

    /* 禁止Forbidden LA 为空，则停止 Forbidden LA TImer */
    if ( ( 0 == pstForbPlmnInfo->ucForbRegLaNum )
      && ( 0 == pstForbPlmnInfo->ucForbRoamLaNum ) )
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_FORBID_LA_TIMER);
    }
}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_GetLteInfo
 功能描述  : 获取LTE信息公共接口函数
 输入参数  : ulInfoType
 输出参数  : pstLmmInfo
 返 回 值  : VOS_TRUE:获取成功
              VOS_FALSE:获取失败
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012年12月27日
    作    者   : s46746
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetLteInfo(
    NAS_LMM_INFO_TYPE_ENUM_UINT32       ulInfoType,
    NAS_LMM_INFO_STRU                  *pstLmmInfo
)
{
    /* 平台不支持LTE */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportLte())
    {
        return VOS_FALSE;
    }

    /* 调用LNAS提供接口函数，成功返回VOS_OK */
    if (MMC_LMM_SUCC == Nas_GetLteInfo(ulInfoType, pstLmmInfo))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_ChangeCsRegState
 功能描述  : 更改CS注册状态
 输入参数  : ucCsRegState:目标注册状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : 新生成函数
 2.日    期   : 2014年11月28日
   作    者   : w00281933
   修改内容   : 服务状态显示优化PhaseI。
*****************************************************************************/
VOS_VOID  NAS_MMC_ChangeCsRegState(
    NAS_MML_REG_STATUS_ENUM_UINT8       ucCsRegState
)
{
    NAS_MML_REG_STATUS_ENUM_UINT8       ucOldRegState;

    ucOldRegState = NAS_MML_GetCsRegStatus();

    /*normal 注册状态无条件上报*/
    if ((ucCsRegState == ucOldRegState)
     && (NAS_MML_REG_REGISTERED_HOME_NETWORK != ucCsRegState)
     && (NAS_MML_REG_REGISTERED_ROAM != ucCsRegState))
    {
        return;
    }

    NAS_MMC_ErrLogRecordCsOosCause(ucOldRegState, ucCsRegState);
    NAS_MMC_ErrLogClrNwSearchCount(ucOldRegState, ucCsRegState);

    /* 设置CS注册状态 */
    NAS_MML_SetCsRegStatus(ucCsRegState);

    /* 上报注册状态发生改变 */
    NAS_MMC_SndMsccRegStatusInd(NAS_MSCC_PIF_SRVDOMAIN_CS, ucCsRegState);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ChangePsRegState
 功能描述  : 更改PS注册状态
 输入参数  : ucPsRegState:目标注册状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : 新生成函数

 2.日    期   : 2014年11月28日
   作    者   : w00281933
   修改内容   : 服务状态显示优化PhaseI。

 3.日    期   : 2015年02月11日
   作    者   : l00305157
   修改内容   : Service_State_Optimize_PhaseII 项目修改

*****************************************************************************/
VOS_VOID  NAS_MMC_ChangePsRegState(
    NAS_MML_REG_STATUS_ENUM_UINT8       ucPsRegState
)
{
    NAS_MML_REG_STATUS_ENUM_UINT8       ucOldRegState;

    ucOldRegState = NAS_MML_GetPsRegStatus();

    /*normal 注册状态无条件上报*/
    if((ucPsRegState == ucOldRegState)
    && (NAS_MML_REG_REGISTERED_HOME_NETWORK != ucPsRegState)
    && (NAS_MML_REG_REGISTERED_ROAM != ucPsRegState))
    {
        return;
    }

    NAS_MMC_ErrLogRecordPsOosCause(ucOldRegState, ucPsRegState);
    NAS_MMC_ErrLogClrNwSearchCount(ucOldRegState, ucPsRegState);

    /*选网或Anycell搜网时，上报LTE的注册状态*/

    /* 设置PS注册状态 */
    NAS_MML_SetPsRegStatus(ucPsRegState);

    /* 上报注册状态发生改变 */
    NAS_MMC_SndMsccRegStatusInd(NAS_MSCC_PIF_SRVDOMAIN_PS, ucPsRegState);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateRegStateSpecPlmnSearch
 功能描述  : 选网或AnyCell进行指定搜索时更新注册状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_UpdateRegStateSpecPlmnSearch(VOS_VOID)
{
    /* 如果无卡注册状态为NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    if (VOS_FALSE == NAS_MML_GetSimPresentStatus())
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

        return;
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* 存在CSFB业务不更新CSPS注册状态 */
    if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
    {
        return;
    }
#endif

    /* 如果CS卡无效更新CS注册状态为NAS_MML_REG_REGISTERED_DENIED */
    if (VOS_FALSE == NAS_MML_GetSimCsRegStatus())
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
    }
    /* 如果CS不允许注册更新CS注册状态为NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    else if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }
    else
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    }

    /* 如果PS卡无效更新PS注册状态为NAS_MML_REG_REGISTERED_DENIED */
    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    }
    /* 如果PS不允许注册更新PS注册状态为NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    else if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }
    else
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateRegStateAnyCellSearchSucc
 功能描述  : AnyCell搜网成功更新CSPS注册状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2013年06月03日
    作    者   : s46746
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_UpdateRegStateAnyCellSearchSucc(VOS_VOID)
{
    NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8                  enSelectionMode;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstUserSpecPlmnId = VOS_NULL_PTR;
    VOS_UINT32                                              ulForbPlmnFlag;
    VOS_UINT8                                               ucUpdateRegStaFlg;
#if   (FEATURE_ON == FEATURE_LTE)
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                       *pstForbidPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulRet;
    VOS_UINT32                                              ulLteOnlyFlg;
#endif

    ucUpdateRegStaFlg = VOS_FALSE;

    /* 定时器不在运行,一定要更新注册状态 */
    if (NAS_MMC_TIMER_STATUS_STOP == NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER))
    {
        ucUpdateRegStaFlg = VOS_TRUE;
    }
    else
    {
        enSelectionMode   = NAS_MMC_GetPlmnSelectionMode();
        pstUserSpecPlmnId = NAS_MMC_GetUserSpecPlmnId();
        ulForbPlmnFlag    = NAS_MML_IsPlmnIdInForbidPlmnList( &(pstUserSpecPlmnId->stPlmnId) );

        /* 当前为手动模式且用户指定的网络在禁止网络列表中需要更改注册状态 */
        if ((NAS_MMC_PLMN_SELECTION_MODE_MANUAL == enSelectionMode)
         && (VOS_TRUE                           == ulForbPlmnFlag))
        {
            ucUpdateRegStaFlg = VOS_TRUE;
        }

#if   (FEATURE_ON == FEATURE_LTE)
        ulLteOnlyFlg        = NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList());
        pstForbidPlmnInfo   = NAS_MML_GetForbidPlmnInfo();

        ulRet = NAS_MML_IsSimPlmnIdInDestBcchPlmnList(&(pstUserSpecPlmnId->stPlmnId),
                                                  pstForbidPlmnInfo->ucForbGprsPlmnNum,
                                                  pstForbidPlmnInfo->astForbGprsPlmnList);

        /* LTE ONLY手动模式且用户指定的网络在禁止GPRS列表中,需要更改注册状态 */
        if ((NAS_MMC_PLMN_SELECTION_MODE_MANUAL == enSelectionMode)
         && (VOS_TRUE == ulLteOnlyFlg)
         && (VOS_TRUE == ulRet))
        {
            ucUpdateRegStaFlg = VOS_TRUE;
        }
#endif
    }

    if (VOS_FALSE == ucUpdateRegStaFlg)
    {
        return;
    }

    /* 如果无卡注册状态为NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    if (VOS_FALSE == NAS_MML_GetSimPresentStatus())
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

        return;
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* 存在CSFB业务不更新CSPS注册状态 */
    if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
    {
        return;
    }
#endif

    /* 如果CS卡无效更新CS注册状态为NAS_MML_REG_REGISTERED_DENIED */
    if (VOS_FALSE == NAS_MML_GetSimCsRegStatus())
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
    }
    /* 其它CS注册状态为NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    else
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }

    /* 如果PS卡无效更新PS注册状态为NAS_MML_REG_REGISTERED_DENIED */
    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    }
    /* 其它PS注册状态为NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    else
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateCsRegStateCsRegSucc
 功能描述  : CS注册成功时更新CS注册状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : 新生成函数
  2.日    期   : 2015年4月2日
    作    者   : b00269685
    修改内容   : 若EPLMN中包含HOME，则显示为非漫游

*****************************************************************************/
VOS_VOID  NAS_MMC_UpdateCsRegStateCsRegSucc(VOS_VOID)
{
    VOS_UINT8                           ucHplmnInEplmnDisplayHomeFlg;
    VOS_UINT32                          ulIsHplmnInEplmnList;

    ucHplmnInEplmnDisplayHomeFlg = NAS_MML_GetHplmnInEplmnDisplayHomeFlg();
    ulIsHplmnInEplmnList         = NAS_MML_IsHplmnInEplmnList();

    if ((VOS_FALSE == NAS_MMC_IsRoam())
     || ((VOS_TRUE == ucHplmnInEplmnDisplayHomeFlg)
      && (VOS_TRUE == ulIsHplmnInEplmnList)))
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_HOME_NETWORK);
    }
    else
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_ROAM);
    }


    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdatePsRegStatePsRegSucc
 功能描述  : PS注册成功时更新PS注册状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : 新生成函数
  2.日    期   : 2015年4月2日
    作    者   : b00269685
    修改内容   : 若EPLMN在HOME中，则显示为非漫游

*****************************************************************************/
VOS_VOID  NAS_MMC_UpdatePsRegStatePsRegSucc(VOS_VOID)
{
    VOS_UINT8                           ucHplmnInEplmnDisplayHomeFlg;
    VOS_UINT32                          ulIsHplmnInEplmnList;

    ucHplmnInEplmnDisplayHomeFlg = NAS_MML_GetHplmnInEplmnDisplayHomeFlg();
    ulIsHplmnInEplmnList         = NAS_MML_IsHplmnInEplmnList();

    if ((VOS_FALSE == NAS_MMC_IsRoam())
     || ((VOS_TRUE == ucHplmnInEplmnDisplayHomeFlg)
      && (VOS_TRUE == ulIsHplmnInEplmnList)))
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_HOME_NETWORK);
    }
    else
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_ROAM);
    }

    return;
}

/* Added by s00261364 for V3R360_eCall项目, 2014-4-3, begin */
/*lint -save -e958 */
/*****************************************************************************
 函 数 名  : NAS_MM_ConvertToLmmSrvccStatus
 功能描述  : 把MSCC的服务状态转换为MMC的格式
 输入参数  : penMmcServiceState--MMC的服务状态
 输出参数  : enMsccServiceState---上报MSCC的服务状态
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月8日
    作    者   : s00261364
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_ConvertToMsccSrvStatus(
    NAS_MMC_SERVICE_ENUM_UINT8          enMmcServiceState,
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32  *penMsccServiceState
)
{
    switch(enMmcServiceState)
    {
        case NAS_MMC_NO_SERVICE:
            *penMsccServiceState = NAS_MSCC_PIF_SERVICE_STATUS_NO_SERVICE;
            break;
        case NAS_MMC_NORMAL_SERVICE:
            *penMsccServiceState = NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE;
            break;
        case NAS_MMC_LIMITED_SERVICE:
            *penMsccServiceState = NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE;
            break;
        case NAS_MMC_LIMITED_SERVICE_REGION:
            *penMsccServiceState = NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE_REGION;
            break;
        default:
            *penMsccServiceState = NAS_MSCC_PIF_SERVICE_STATUS_BUTT;
            break;
    }

    return;
}
/*lint -restore */

/*lint -save -e958 */
/*****************************************************************************
 函 数 名  : NAS_MMC_ChangeServiceState
 功能描述  : 更改服务状态
 输入参数  : enServiceState:目标服务状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2014年04月03日
    作    者   : s00261364
    修改内容   : 新生成函数
  2.日    期   : 2014年5月31日
    作    者   : y00245242
    修改内容   : 修改服务状态上报
  3.日    期   : 2014年11月25日
    作    者   : s00217060
    修改内容   : Service_State_Optimize_PhaseI项目修改
  4.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
*****************************************************************************/
VOS_VOID  NAS_MMC_ChangeServiceState(
    VOS_UINT32                          ulCnDomainId,
    NAS_MMC_SERVICE_ENUM_UINT8          enServiceState
)
{

    NAS_MMC_SERVICE_INFO_CTX_STRU      *pstServiceInfo      = VOS_NULL_PTR;
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32  enMsccServiceState;



    /*选网或Anycell搜网时，上报LTE的服务状态*/


    pstServiceInfo =  NAS_MMC_GetServiceInfo();

    switch (ulCnDomainId)
    {
        case NAS_MSCC_PIF_SRVDOMAIN_CS:
            /* 正常服务时无条件通知MMA服务状态，MMA需要在正常服务时更新stAppNetworkInfo
               否则如果当前已经是需要更新的注册状态则不需要更新了 */
            if ((enServiceState == pstServiceInfo->enCsCurrService)
             && (NAS_MMC_NORMAL_SERVICE != enServiceState))
            {
                return;
            }
            /* 设置CS服务状态 */
            NAS_MMC_SetCsServiceStatus(enServiceState);
            break;

        case NAS_MSCC_PIF_SRVDOMAIN_PS:

            /* 正常服务时无条件通知MMA服务状态，MMA需要在正常服务时更新stAppNetworkInfo
               否则如果当前已经是需要更新的注册状态则不需要更新了 */
            if ((enServiceState == pstServiceInfo->enPsCurrService)
             && (NAS_MMC_NORMAL_SERVICE != enServiceState))
            {
                return;
            }
            /* 设置PS服务状态 */
            NAS_MMC_SetPsServiceStatus(enServiceState);
            break;

        case NAS_MSCC_PIF_SRVDOMAIN_CS_PS:
        /* Added by y00245242 for V3R3C60_eCall项目, 2014-5-31, begin */
        case NAS_MSCC_PIF_SRVDOMAIN_NOT_REG_PLMN_SEARCHING:
        /* Added by y00245242 for V3R3C60_eCall项目, 2014-5-31, end */

            /* 正常服务时无条件通知MMA服务状态，MMA需要在正常服务时更新stAppNetworkInfo
               否则如果当前已经是需要更新的注册状态则不需要更新了 */
            if ((enServiceState == pstServiceInfo->enPsCurrService)
             && (enServiceState == pstServiceInfo->enCsCurrService)
             && (NAS_MMC_NORMAL_SERVICE != enServiceState))
            {
                return;
            }

            /* 设置CS服务状态 */
            NAS_MMC_SetCsServiceStatus(enServiceState);

            /* 设置PS服务状态 */
            NAS_MMC_SetPsServiceStatus(enServiceState);
            break;

        default:

            NAS_ERROR_LOG(WUEPS_PID_MMC,"NAS_MMC_ChangeServiceState: domain Type Error");
            return;
    }

    NAS_MMC_ConvertToMsccSrvStatus(enServiceState, &enMsccServiceState);

    NAS_MMC_SndMsccServiceStatusInd(ulCnDomainId,  enMsccServiceState);

    return;
}
/*lint -restore */

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegStateAndCsServiceStateWhenReceiveDetachCnfSucc
 功能描述  : 收到Detach Cnf Succ 消息时，CS域的注册状态和服务状态的处理
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月9日
    作    者   : n00355355
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_ProcCsRegStateAndCsServiceState_DetachCnfSucc(VOS_VOID)
{
    VOS_UINT8                           ucSimCsRegStatus;
    NAS_MMC_SERVICE_INFO_CTX_STRU       *pstServiceInfo = VOS_NULL_PTR;

    ucSimCsRegStatus = VOS_FALSE;
    pstServiceInfo   = NAS_MMC_GetServiceInfo();

    NAS_NORMAL_LOG2(WUEPS_PID_MMC, "NAS_MMC_ProcCsRegStateAndCsServiceState_DetachCnfSucc:CsRegStatus, enCsCurrService", ucSimCsRegStatus, pstServiceInfo->enCsCurrService);

    /* 如果CS卡有效，上报cs注册状态为NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH*/
    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();
    if (VOS_TRUE == ucSimCsRegStatus)
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }

    /* 如果之前是正常服务状态，将其更新为限制服务状态 */
    if (NAS_MMC_NORMAL_SERVICE == pstServiceInfo->enCsCurrService)
    {
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS,NAS_MMC_LIMITED_SERVICE);
    }


    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegStateAndPsServiceStateWhenReceiveDetachCnfSucc
 功能描述  : 收到Detach Cnf Succ 消息时，PS域的注册状态和服务状态的处理
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月9日
    作    者   : n00355355
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_ProcPsRegStateAndPsServiceState_DetachCnfSucc(VOS_VOID)
{
    VOS_UINT8                           ucSimPsRegStatus;
    NAS_MMC_SERVICE_INFO_CTX_STRU       *pstServiceInfo = VOS_NULL_PTR;

    ucSimPsRegStatus = VOS_FALSE;
    pstServiceInfo   = NAS_MMC_GetServiceInfo();

    NAS_NORMAL_LOG2(WUEPS_PID_MMC, "NAS_MMC_ProcPsRegStateAndPsServiceState_DetachCnfSucc:PsRegStatus, enPsCurrService", ucSimPsRegStatus, pstServiceInfo->enPsCurrService);

    /* 如果PS不允许注册而且PS卡有效，上报ps注册状态为NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH*/
    ucSimPsRegStatus = NAS_MML_GetSimPsRegStatus();
    if (VOS_TRUE == ucSimPsRegStatus)
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }

    /* 如果之前是正常服务状态，将其更新为限制服务状态 */
    if (NAS_MMC_NORMAL_SERVICE == pstServiceInfo->enPsCurrService)
    {
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS,NAS_MMC_LIMITED_SERVICE);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ChangeServiceState
 功能描述  : 更改服务状态
 输入参数  : enServiceState:目标服务状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月14日
    作    者   : c00318887
    修改内容   : DTS2015082002854:  漫游标记不准
*****************************************************************************/
VOS_VOID  NAS_MMC_UpdateServiceState_RegSucc(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  ulCnDomainId,
    NAS_MMC_SERVICE_ENUM_UINT8          enServiceState
)
{
    NAS_NORMAL_LOG2(WUEPS_PID_MMC,"NAS_MMC_UpdateServiceState_RegSucc entered ulCnDomainId: enServiceState:", ulCnDomainId, enServiceState);

    if (NAS_MSCC_PIF_SRVDOMAIN_PS == ulCnDomainId)
    {
        NAS_MMC_UpdatePsRegStatePsRegSucc();
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, enServiceState);
    }
    else if (NAS_MSCC_PIF_SRVDOMAIN_CS == ulCnDomainId)
    {
        NAS_MMC_UpdateCsRegStateCsRegSucc();
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, enServiceState);
    }
    else if (NAS_MSCC_PIF_SRVDOMAIN_CS_PS == ulCnDomainId)
    {
        NAS_MMC_UpdateCsRegStateCsRegSucc();
        NAS_MMC_UpdatePsRegStatePsRegSucc();

        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, enServiceState);
    }
    else
    {
        /* nothing */
    }
}


/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateServiceStateSpecPlmnSearch
 功能描述  : 选网或AnyCell进行指定搜索时更新服务状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2014年04月08日
    作    者   : s00261364
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_UpdateServiceStateSpecPlmnSearch(VOS_VOID)
{
    NAS_MMC_SERVICE_ENUM_UINT8          enPsServiceStatus;
    NAS_MMC_SERVICE_ENUM_UINT8          enCsServiceStatus;

    enCsServiceStatus = NAS_MMC_GetCsServiceStatus();
    enPsServiceStatus = NAS_MMC_GetPsServiceStatus();

#if (FEATURE_ON == FEATURE_LTE)
     /* 存在CSFB业务不更新CSPS服务状态 */
     if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
     {
         return;
     }
#endif

     /* 判定驻留网络的MCC和MNC无效 */
    if (VOS_TRUE == NAS_MMC_IsInValidCampPlmn())
    {
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
        return;
    }

    /* 正常服务则更改为限制服务;其他保存不变-不判断CS不允许attach标记 */
    if( NAS_MMC_NORMAL_SERVICE == enCsServiceStatus)
    {
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS ,NAS_MMC_LIMITED_SERVICE);
    }

    if( NAS_MMC_NORMAL_SERVICE == enPsServiceStatus)
    {
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS,NAS_MMC_LIMITED_SERVICE);
    }

    return;
}

/* Added by s00261364 for V3R360_eCall项目, 2014-4-3, end */

/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertMsccMsModeToMmlMsMode
 功能描述  : 获取CS域能力变化类型
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
NAS_MML_MS_MODE_ENUM_UINT8  NAS_MMC_ConvertMsccMsModeToMmlMsMode(
    NAS_MSCC_PIF_MS_MODE_ENUM_UINT32    enMsccMsMode
)
{
    NAS_MML_MS_MODE_ENUM_UINT8          enMmlMsMode;

    /* 初始化为NAS_MML_MS_MODE_BUTT */
    enMmlMsMode = NAS_MML_MS_MODE_BUTT;

    switch (enMsccMsMode)
    {
        case NAS_MSCC_PIF_MS_MODE_A:

            enMmlMsMode = NAS_MML_MS_MODE_PS_CS;
            break;

        case NAS_MSCC_PIF_MS_MODE_CG:

            enMmlMsMode = NAS_MML_MS_MODE_PS_ONLY;
            break;

        case NAS_MSCC_PIF_MS_MODE_CC:

            enMmlMsMode = NAS_MML_MS_MODE_CS_ONLY;
            break;

        default:

            NAS_ERROR_LOG(WUEPS_PID_MMC,"NAS_MML_ConvertMsccMsModeToMmlMsMode: Ms Mode Type Error");
    }

    return enMmlMsMode;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetCsDomainCapaChangeType
 功能描述  : 获取CS域能力变化类型
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
NAS_MMC_CS_DOMAIN_CAPA_CHANGE_TYPE_ENUM_UINT8  NAS_MMC_GetCsDomainCapaChangeType(
    NAS_MML_MS_MODE_ENUM_UINT8          enOldMsMode,
    NAS_MML_MS_MODE_ENUM_UINT8          enNewMsMode
)
{
    VOS_UINT32                          ulOldCsAvailFlg;
    VOS_UINT32                          ulNewCsAvailFlg;

    ulOldCsAvailFlg = NAS_MML_IsCsServDomainAvail(enOldMsMode);
    ulNewCsAvailFlg = NAS_MML_IsCsServDomainAvail(enNewMsMode);

    /* 旧的CS域能力与新的相同时，无变化 */
    if (ulOldCsAvailFlg == ulNewCsAvailFlg)
    {
        return NAS_MMC_CS_DOMAIN_CAPA_NO_CHANGE;
    }

    /* 旧的CS域能力可用，新的CS域能力不可用 */
    if ( (VOS_TRUE  == ulOldCsAvailFlg)
      && (VOS_FALSE == ulNewCsAvailFlg) )
    {
        return NAS_MMC_CS_DOMAIN_CAPA_AVAIL_TO_UNAVAIL;
    }

    /* 旧的CS域能力不可用，新的CS域能力可用 */
    return NAS_MMC_CS_DOMAIN_CAPA_UNAVAIL_TO_AVAIL;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_DelForbPlmnFromAsSrchedPlmnList
 功能描述  : 从列表中删除禁止的PLMN
 输入参数  : pstSrchedPlmn:待删除的PLMN信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年06月03日
   作    者   : L65478
   修改内容   : 新生成函数
 2.日    期   : 2013年09月11日
   作    者   : w00242748
   修改内容   : 编译告警清理
 3.日    期   : 2013年10月18日
   作    者   : z00161729
   修改内容   : DTS2013101705317:oos was上报limit service camp in存在多个低质量网络
                且是forbidden plmn则mmc构造搜网列表错误存在不存在网络
*****************************************************************************/
VOS_VOID NAS_MMC_DelForbPlmnFromAsSrchedPlmnList(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    *pstSrchedPlmn
)
{
    VOS_UINT32                                              ulPlmnCnt;
    VOS_UINT32                                              ulRatCnt;

    /* 删除禁止的PLMN信息 */
    for (ulRatCnt = 0; ulRatCnt < NAS_MML_MAX_RAT_NUM; ulRatCnt++)
    {
        for (ulPlmnCnt = 0; ulPlmnCnt < pstSrchedPlmn[ulRatCnt].ulHighPlmnNum; )
        {
            if (VOS_TRUE == NAS_MML_IsPlmnIdInForbidPlmnList(&(pstSrchedPlmn[ulRatCnt].astHighPlmnList[ulPlmnCnt])))
            {
                (VOS_VOID)PS_MEM_MOVE(&(pstSrchedPlmn[ulRatCnt].astHighPlmnList[ulPlmnCnt]),
                    &(pstSrchedPlmn[ulRatCnt].astHighPlmnList[ulPlmnCnt + 1]),
                    (pstSrchedPlmn[ulRatCnt].ulHighPlmnNum - (ulPlmnCnt + 1)) * sizeof(NAS_MML_PLMN_ID_STRU));

                pstSrchedPlmn[ulRatCnt].ulHighPlmnNum--;
            }
            else
            {
                ulPlmnCnt++;
            }
        }

        for (ulPlmnCnt = 0; ulPlmnCnt < pstSrchedPlmn[ulRatCnt].ulLowPlmnNum; )
        {
            if (VOS_TRUE == NAS_MML_IsPlmnIdInForbidPlmnList(&(pstSrchedPlmn[ulRatCnt].astLowPlmnList[ulPlmnCnt].stPlmnId)))
            {
                (VOS_VOID)PS_MEM_MOVE(&(pstSrchedPlmn[ulRatCnt].astLowPlmnList[ulPlmnCnt]),
                    &(pstSrchedPlmn[ulRatCnt].astLowPlmnList[ulPlmnCnt + 1]),
                    (pstSrchedPlmn[ulRatCnt].ulLowPlmnNum - (ulPlmnCnt + 1)) * sizeof(NAS_MMC_LOW_PLMN_INFO_STRU));

                pstSrchedPlmn[ulRatCnt].ulLowPlmnNum--;
            }
            else
            {
                ulPlmnCnt++;
            }
        }
    }

}

/*****************************************************************************
 函 数 名  : NAS_MMC_DelNotUserSpecPlmnFromSrchedPlmnList
 功能描述  : 从列表中删除非用户指定的PLMN
 输入参数  : pstSrchedPlmn:待删除的PLMN信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年06月03日
   作    者   : L65478
   修改内容   : 新生成函数
 2.日    期   : 2013年09月011日
   作    者   : w00242748
   修改内容   : 编译告警清理
 3.日    期   : 2013年10月18日
   作    者   : z00161729
   修改内容   : DTS2013101705317:oos was上报limit service camp in存在多个低质量网络
               且是forbidden plmn则mmc构造搜网列表错误存在不存在网络

*****************************************************************************/
VOS_VOID NAS_MMC_DelNotUserSpecPlmnFromSrchedPlmnList(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSrchedPlmn
)
{
    VOS_UINT32                                              ulPlmnCnt;
    VOS_UINT32                                              ulRatCnt;
    VOS_UINT32                                              ulEplmnValidFlg;
    NAS_MML_EQUPLMN_INFO_STRU                              *pEplmnAddr  = VOS_NULL_PTR;

    pEplmnAddr = NAS_MML_GetEquPlmnList();
    ulEplmnValidFlg = NAS_MML_GetEplmnValidFlg();

    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL != NAS_MMC_GetPlmnSelectionMode())
    {
        return;
    }

    /* 手动搜网模式下,删除非用户指定的PLMN信息 */
    for (ulRatCnt = 0; ulRatCnt < NAS_MML_MAX_RAT_NUM; ulRatCnt++)
    {
        if ((VOS_TRUE != NAS_MMC_GetUserSpecPlmnRegisterStatus())
         || (VOS_TRUE != ulEplmnValidFlg))
        {
            /* EPLMN无效的情况下目前不考虑 */
            pstSrchedPlmn[ulRatCnt].ulHighPlmnNum = 0;

            /* EPLMN无效的情况下目前不考虑 */
            pstSrchedPlmn[ulRatCnt].ulLowPlmnNum  = 0;

            continue;
        }

        for (ulPlmnCnt = 0; ulPlmnCnt < pstSrchedPlmn[ulRatCnt].ulHighPlmnNum; )
        {
            if (VOS_FALSE == NAS_MML_IsSimPlmnIdInDestBcchPlmnList(&(pstSrchedPlmn[ulRatCnt].astHighPlmnList[ulPlmnCnt]),
                                        pEplmnAddr->ucEquPlmnNum,
                                        pEplmnAddr->astEquPlmnAddr))
            {
                (VOS_VOID)PS_MEM_MOVE(&(pstSrchedPlmn[ulRatCnt].astHighPlmnList[ulPlmnCnt]),
                    &(pstSrchedPlmn[ulRatCnt].astHighPlmnList[ulPlmnCnt + 1]),
                    (pstSrchedPlmn[ulRatCnt].ulHighPlmnNum - (ulPlmnCnt + 1)) * sizeof(NAS_MML_PLMN_ID_STRU));

                pstSrchedPlmn[ulRatCnt].ulHighPlmnNum--;
            }
            else
            {
                ulPlmnCnt++;
            }
        }

        for (ulPlmnCnt = 0; ulPlmnCnt < pstSrchedPlmn[ulRatCnt].ulLowPlmnNum; )
        {
            if (VOS_FALSE == NAS_MML_IsSimPlmnIdInDestBcchPlmnList(&(pstSrchedPlmn[ulRatCnt].astLowPlmnList[ulPlmnCnt].stPlmnId),
                                        pEplmnAddr->ucEquPlmnNum,
                                        pEplmnAddr->astEquPlmnAddr))
            {
                (VOS_VOID)PS_MEM_MOVE(&(pstSrchedPlmn[ulRatCnt].astLowPlmnList[ulPlmnCnt]),
                    &(pstSrchedPlmn[ulRatCnt].astLowPlmnList[ulPlmnCnt + 1]),
                    (pstSrchedPlmn[ulRatCnt].ulLowPlmnNum - (ulPlmnCnt + 1)) * sizeof(NAS_MMC_LOW_PLMN_INFO_STRU));

                pstSrchedPlmn[ulRatCnt].ulLowPlmnNum--;
            }
            else
            {
                ulPlmnCnt++;
            }
        }
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitSearchedPlmnListInfo
 功能描述  : 初始化搜索到的网络列表信息
 输入参数  : pstListInfo - 需要初始化的网络列表信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月15日
   作    者   : z00161729
   修改内容   : DTS2013062406563:WAS连接态OOS,T305运行期间只会在本系统下搜等效plmn，
                不会驻留到本系统其他网络，也不会异系统下进行搜网，导致无法很快在软银网络注册，nas配合修改

*****************************************************************************/
VOS_VOID NAS_MMC_InitSearchedPlmnListInfo(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstListInfo
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT32                                              k;

    if (VOS_NULL_PTR == pstListInfo)
    {
        return;
    }

    for ( i = 0; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        pstListInfo[i].enRatType        = NAS_MML_NET_RAT_TYPE_BUTT;
        pstListInfo[i].ulHighPlmnNum    = 0;
        pstListInfo[i].ulLowPlmnNum     = 0;
        pstListInfo[i].enCoverType      = NAS_MMC_COVERAGE_TYPE_BUTT;

        /* 高优先级列表 */
        for ( j = 0; j < NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM; j++ )
        {
            pstListInfo[i].astHighPlmnList[j].ulMcc = NAS_MML_INVALID_MCC;
            pstListInfo[i].astHighPlmnList[j].ulMnc = NAS_MML_INVALID_MNC;
        }

        /* 低优先级列表 */
        for ( k = 0; k < NAS_MMC_INTRA_MAX_LOW_QUALITY_PLMN_NUM; k++)
        {
            pstListInfo[i].astLowPlmnList[k].stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
            pstListInfo[i].astLowPlmnList[k].stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
            pstListInfo[i].astLowPlmnList[k].lRscp          = NAS_MML_UTRA_RSCP_UNVALID;
        }
    }
}


/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateSearchedPlmnListInfo
 功能描述  : 更新搜索到的网络列表信息
 输入参数  : pstRrcList  WAS丢网时上报的网络列表信息
 输出参数  : pstListInfo
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月29日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2015年10月21日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0修改

*****************************************************************************/
VOS_VOID NAS_MMC_UpdateSearchedPlmnListInfo(
    NAS_MMC_SEARCHED_TYPE_STRU                             *pstSearchedType,
    RRC_PLMN_ID_LIST_STRU                                  *pstRrcList,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatPrioList   = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;
    VOS_UINT32                          i;
    VOS_UINT32                          j;

    if ((VOS_NULL_PTR == pstRrcList)
     || (VOS_NULL_PTR == pstListInfo))
    {
        return;
    }

    /* 获取优先级列表 */
    pstRatPrioList      = NAS_MML_GetMsPrioRatList();

    /* 初始化上报的接入技术列表 */
    for (i =0; i< pstRatPrioList->ucRatNum; i++)
    {
        pstListInfo[i].enRatType        = pstRatPrioList->aucRatPrio[i];
        pstListInfo[i].ulHighPlmnNum    = 0;
        pstListInfo[i].ulLowPlmnNum     = 0;

        /* 保存AS已经搜索过的类型，没带该信息时默认没搜过 */
        pstListInfo[i].stSearchedType.ucHistorySearchedFlg  = VOS_FALSE;
        pstListInfo[i].stSearchedType.ucPrefBandSearchedFlg = VOS_FALSE;
        pstListInfo[i].stSearchedType.ucSpecSearchedFlg     = VOS_FALSE;

        if ((pstListInfo[i].enRatType == NAS_MML_GetCurrNetRatType())
         && (VOS_NULL_PTR != pstSearchedType))
        {
            /* 已经进行过spec搜时，认为history和pref band也已经搜过 */
            if (VOS_TRUE == pstSearchedType->ucSpecSearchedFlg)
            {
                pstListInfo[i].stSearchedType.ucHistorySearchedFlg  = VOS_TRUE;
                pstListInfo[i].stSearchedType.ucPrefBandSearchedFlg = VOS_TRUE;
                pstListInfo[i].stSearchedType.ucSpecSearchedFlg     = VOS_TRUE;
                break;
            }

            /* 已经进行过pref band搜时，认为history也已经搜过 */
            if (VOS_TRUE == pstSearchedType->ucPrefBandSearchedFlg)
            {
                pstListInfo[i].stSearchedType.ucHistorySearchedFlg  = VOS_TRUE;
                pstListInfo[i].stSearchedType.ucPrefBandSearchedFlg = VOS_TRUE;
                break;
            }

            if (VOS_TRUE == pstSearchedType->ucHistorySearchedFlg)
            {
                pstListInfo[i].stSearchedType.ucHistorySearchedFlg  = VOS_TRUE;
                break;
            }
        }
    }




    /* 保存高质量列表到上下文相应接入技术的列表 */
    for (i = 0; i < pstRrcList->ulHighPlmnNum; i++)
    {
        /* 转换RRC格式的接入技术 */
        NAS_MMC_ConvertRrcRatToNasFormat(pstRrcList->aHighPlmnList[i].ulRat, &enRat);

        for (j = 0; j < pstRatPrioList->ucRatNum; j++)
        {
            if (enRat == pstListInfo[j].enRatType)
            {
                pstListInfo[j].astHighPlmnList[pstListInfo[j].ulHighPlmnNum].ulMcc
                       = pstRrcList->aHighPlmnList[i].stPlmnId.ulMcc;

                pstListInfo[j].astHighPlmnList[pstListInfo[j].ulHighPlmnNum].ulMnc
                       = pstRrcList->aHighPlmnList[i].stPlmnId.ulMnc;

                pstListInfo[j].ulHighPlmnNum ++;

                break;
            }
        }
    }

    /* 保存低质量列表到上下文相应接入技术的列表 */
    for (i = 0; i < pstRrcList->ulLowPlmnNum; i++)
    {
        /* 转换RRC格式的接入技术 */
        NAS_MMC_ConvertRrcRatToNasFormat(pstRrcList->aLowPlmnList[i].PlmnId.ulRat, &enRat);

        for (j = 0; j < pstRatPrioList->ucRatNum; j++)
        {
            if ( enRat == pstListInfo[j].enRatType)
            {
                pstListInfo[j].astLowPlmnList[pstListInfo[j].ulLowPlmnNum].stPlmnId.ulMcc
                       = pstRrcList->aLowPlmnList[i].PlmnId.stPlmnId.ulMcc;

                pstListInfo[j].astLowPlmnList[pstListInfo[j].ulLowPlmnNum].stPlmnId.ulMnc
                       = pstRrcList->aLowPlmnList[i].PlmnId.stPlmnId.ulMnc;

                pstListInfo[j].astLowPlmnList[pstListInfo[j].ulLowPlmnNum].lRscp
                       = pstRrcList->aLowPlmnList[i].lRscp;

                pstListInfo[j].ulLowPlmnNum ++;

                break;
            }
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_BuildEquPlmnInfo
 功能描述  : 构造等效plmn信息
 输入参数  : 无
 输出参数  : pstEquPlmnInfo - 构造后的等效plmn列表,
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
 2.日    期   : 2014年1月26日
   作    者   : z00161729
   修改内容   : DTS2014012305088：支持增强NCELL搜网，如果Modem1传递过来的邻区信息不存在的情况下，通过历史频点支持NCELL搜索。
 3.日    期   : 2015年1月14日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
 4.日    期   : 2015年4月23日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID NAS_MMC_BuildEquPlmnInfo(
     NAS_MML_EQUPLMN_INFO_STRU         *pstOutEplmnInfo
)
{
    VOS_UINT32                                              ulLoop;
    VOS_UINT8                                               ucSndEplmnNum;
    NAS_MML_PLMN_ID_STRU                                   *pstCurrPlmnId = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnWithRat;
    MSCC_MMC_PLMN_ID_STRU                                   astEquPlmnAddr[NAS_MSCC_PIF_MAX_EQUPLMN_NUM];

    PS_MEM_SET(astEquPlmnAddr, 0, sizeof(astEquPlmnAddr));

    /* 获取当前驻留的网络和等效plmn  */
    pstCurrPlmnId = NAS_MML_GetCurrCampPlmnId();
    ucSndEplmnNum = 0;
    PS_MEM_SET(&stPlmnWithRat, 0, sizeof(stPlmnWithRat));

    /* EPLMN存在时 */
    if (pstOutEplmnInfo->ucEquPlmnNum > 0)
    {
        for (ulLoop = 0; ulLoop < pstOutEplmnInfo->ucEquPlmnNum; ulLoop++)
        {
            if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(&(pstOutEplmnInfo->astEquPlmnAddr[ulLoop]),
                                               (VOS_UINT8)ucSndEplmnNum, astEquPlmnAddr))
            {
                continue;
            }

            if (VOS_TRUE == NAS_MML_IsPlmnIdInForbidPlmnList(&(pstOutEplmnInfo->astEquPlmnAddr[ulLoop])))
            {
                continue;
            }

            /* 构造带接入技术的PLMN ID */
            stPlmnWithRat.enRat         = NAS_MML_GetCurrNetRatType();
            stPlmnWithRat.stPlmnId      = pstOutEplmnInfo->astEquPlmnAddr[ulLoop];

            /* 判断等效PLMN是否在禁止接入技术的PLMN列表中,如果在则不将该PLMN ID发给RRC */
            if (VOS_TRUE == NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
            {
                continue;
            }

            astEquPlmnAddr[ucSndEplmnNum].ulMcc = pstOutEplmnInfo->astEquPlmnAddr[ulLoop].ulMcc;
            astEquPlmnAddr[ucSndEplmnNum].ulMnc = pstOutEplmnInfo->astEquPlmnAddr[ulLoop].ulMnc;

            ucSndEplmnNum++;
        }
    }
    /*Eplmn不存在时，只添加当前网络*/
    else
    {
        if (VOS_FALSE == NAS_MML_IsPlmnIdInForbidPlmnList(pstCurrPlmnId))
        {
            astEquPlmnAddr[ucSndEplmnNum].ulMcc = pstCurrPlmnId->ulMcc;
            astEquPlmnAddr[ucSndEplmnNum].ulMnc = pstCurrPlmnId->ulMnc;

            ucSndEplmnNum++;
        }
    }


    pstOutEplmnInfo->ucEquPlmnNum = ucSndEplmnNum;
    PS_MEM_CPY(pstOutEplmnInfo->astEquPlmnAddr, astEquPlmnAddr, sizeof(pstOutEplmnInfo->astEquPlmnAddr));

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsExistAvailPlmnInSearchedPlmnList
 功能描述  : 判断搜网列表中是否有可用网络
 输入参数  : pastIntraPlmnSrchInfo:PLMN信息
 输出参数  : 无
 返 回 值  : VOS_TRUE:有可用网络
             VOS_FALSE:无可用网络
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年06月03日
   作    者   : L65478
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsExistAvailPlmnInSearchedPlmnList(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pastIntraPlmnSrchInfo
)
{
    VOS_UINT32                                              ulRatCnt;

    if (VOS_NULL_PTR == pastIntraPlmnSrchInfo)
    {
        return VOS_FALSE;
    }

    /* 有可用网络,需要发起搜网 */
    for (ulRatCnt = 0; ulRatCnt < NAS_MML_MAX_RAT_NUM; ulRatCnt++)
    {
        if ((0 != pastIntraPlmnSrchInfo[ulRatCnt].ulHighPlmnNum)
         || (0 != pastIntraPlmnSrchInfo[ulRatCnt].ulLowPlmnNum))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


#if (FEATURE_ON == FEATURE_PTM)


/*****************************************************************************
 函 数 名  : NAS_MMC_CsRegErrRecord
 功能描述  : 记录CS注册失败事件
 输入参数  : MMMMC_CS_REG_RESULT_IND_STRU *pstCsRegRstInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月23日
    作    者   : s00190137
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_CsRegErrRecord(MMMMC_CS_REG_RESULT_IND_STRU *pstCsRegRstInd)
{
    NAS_ERR_LOG_CS_REG_RESULT_EVENT_STRU                    stCsRegRstEvent;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulRegFailFlag;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_CS_REG_FAIL);
    ulIsLogRecord = NAS_MML_IsErrLogNeedRecord(usLevel);

    /* 判断对应的异常原因值是否需要记录 */
    ulRegFailFlag = NAS_MML_RegFailCauseNeedRecord(pstCsRegRstInd->enRegFailCause);

    /* 模块异常不需要记录或异常原因值不需要记录时，不保存异常信息 */
    if ((VOS_FALSE == ulIsLogRecord)
     || (VOS_FALSE == ulRegFailFlag))
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_CS_REG_RESULT_EVENT_STRU);

    /* 填充CS注册失败异常信息 */
    PS_MEM_SET(&stCsRegRstEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stCsRegRstEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_MMC),
                                      NAS_ERR_LOG_ALM_CS_REG_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stCsRegRstEvent.ulLuResult        = pstCsRegRstInd->enLuResult;
    stCsRegRstEvent.enNetType         = pstCsRegRstInd->enNetType;
    stCsRegRstEvent.ucIsComBined      = pstCsRegRstInd->ucIsComBined;
    stCsRegRstEvent.usRegFailCause    = pstCsRegRstInd->enRegFailCause;
    stCsRegRstEvent.ulServiceStatus   = pstCsRegRstInd->ulServiceStatus;
    stCsRegRstEvent.ulCsUpdateStatus  = pstCsRegRstInd->ulCsUpdateStatus;
    stCsRegRstEvent.ulLuAttemptCnt    = pstCsRegRstInd->ulLuAttemptCnt;

    PS_MEM_CPY(&stCsRegRstEvent.stOldLai, &pstCsRegRstInd->stOldLai, sizeof(MM_LAI_STRU));

    NAS_MNTN_OutputPositionInfo(&stCsRegRstEvent.stPositionInfo);

    stCsRegRstEvent.ucRegFailOriginalCause = NAS_MML_GetOriginalRejectCause(stCsRegRstEvent.usRegFailCause);
    /*
       将异常信息写入Buffer中
       实际写入的字符数与需要写入的不等则打印异常
     */
    ulResult = NAS_MML_PutErrLogRingBuf((VOS_CHAR *)&stCsRegRstEvent, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_CsRegErrRecord(): Push buffer error.");
    }

    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_CS_REG_FAIL,
                           WUEPS_PID_MMC,
                           (VOS_UINT8 *)&stCsRegRstEvent,
                           sizeof(stCsRegRstEvent));

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_PsRegErrRecord
 功能描述  : 记录PS注册异常事件
 输入参数  : GMMMMC_PS_REG_RESULT_IND_STRU *pstPsRegRstInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月23日
    作    者   : s00190137
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_PsRegErrRecord(GMMMMC_PS_REG_RESULT_IND_STRU *pstPsRegRstInd)
{
    NAS_ERR_LOG_PS_REG_RESULT_EVENT_STRU                    stPsRegRstEvent;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulRegFailFlag;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_PS_REG_FAIL);
    ulIsLogRecord = NAS_MML_IsErrLogNeedRecord(usLevel);

    /* 判断对应的异常原因值是否需要记录 */
    ulRegFailFlag = NAS_MML_RegFailCauseNeedRecord(pstPsRegRstInd->enRegFailCause);

    /* 模块异常不需要记录或异常原因值不需要记录时，不保存异常信息 */
    if ((VOS_FALSE == ulIsLogRecord)
     || (VOS_FALSE == ulRegFailFlag))
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_PS_REG_RESULT_EVENT_STRU);

    /* 填充PS注册失败异常信息 */
    PS_MEM_SET(&stPsRegRstEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stPsRegRstEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_MMC),
                                      NAS_ERR_LOG_ALM_PS_REG_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stPsRegRstEvent.enGmmActionType   = pstPsRegRstInd->enGmmActionType;
    stPsRegRstEvent.ulActionResult    = pstPsRegRstInd->enActionResult;
    stPsRegRstEvent.enReqDomain       = pstPsRegRstInd->enReqDomain;
    stPsRegRstEvent.enRsltDomain      = pstPsRegRstInd->enRsltDomain;
    stPsRegRstEvent.usRegFailCause    = pstPsRegRstInd->enRegFailCause;
    stPsRegRstEvent.enNetType         = pstPsRegRstInd->enNetType;
    stPsRegRstEvent.ulRegCounter      = pstPsRegRstInd->ulRegCounter;
    stPsRegRstEvent.ulServiceStatus   = pstPsRegRstInd->ulServiceStatus;

    NAS_MNTN_OutputPositionInfo(&stPsRegRstEvent.stPositionInfo);
    stPsRegRstEvent.ucRegFailOriginalCause = NAS_MML_GetOriginalRejectCause(stPsRegRstEvent.usRegFailCause);
    /*
       将异常信息写入Buffer中
       实际写入的字符数与需要写入的不等则打印异常
     */
    ulResult = NAS_MML_PutErrLogRingBuf((VOS_CHAR *)&stPsRegRstEvent, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_PsRegErrRecord(): Push buffer error.");
    }

    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_PS_REG_FAIL,
                           WUEPS_PID_MMC,
                           (VOS_UINT8 *)&stPsRegRstEvent,
                           sizeof(stPsRegRstEvent));
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_PsServiceRegErrRecord
 功能描述  : 记录PS Service 被拒异常事件
 输入参数  : GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU  *pstServiceRsltInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月28日
    作    者   : n00269697
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_PsServiceRegErrRecord(
    GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU                 *pstServiceRsltInd
)
{
    NAS_ERR_LOG_PS_SRV_REG_RESULT_EVENT_STRU                stPsSrvRegRstEvent;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulRegFailFlag;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_PS_SRV_REG_FAIL);
    ulIsLogRecord = NAS_MML_IsErrLogNeedRecord(usLevel);

    /* 判断对应的异常原因值是否需要记录 */
    ulRegFailFlag = NAS_MML_RegFailCauseNeedRecord(pstServiceRsltInd->enRegFailCause);

    /* 模块异常不需要记录或异常原因值不需要记录时，不保存异常信息 */
    if ((VOS_FALSE == ulIsLogRecord)
     || (VOS_FALSE == ulRegFailFlag))
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_PS_SRV_REG_RESULT_EVENT_STRU);

    /* 填充PS注册失败异常信息 */
    PS_MEM_SET(&stPsSrvRegRstEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stPsSrvRegRstEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_MMC),
                                      NAS_ERR_LOG_ALM_PS_SRV_REG_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stPsSrvRegRstEvent.enActionResult = pstServiceRsltInd->enActionResult;
    stPsSrvRegRstEvent.enRegFailCause = pstServiceRsltInd->enRegFailCause;
    stPsSrvRegRstEvent.ulServiceSts   = pstServiceRsltInd->ulServiceSts;

    NAS_MNTN_OutputPositionInfo(&stPsSrvRegRstEvent.stPositionInfo);

    stPsSrvRegRstEvent.ucRegFailOriginalCause = NAS_MML_GetOriginalRejectCause(stPsSrvRegRstEvent.enRegFailCause);

    /*
       将异常信息写入Buffer中
       实际写入的字符数与需要写入的不等则打印异常
     */
    ulResult = NAS_MML_PutErrLogRingBuf((VOS_CHAR *)&stPsSrvRegRstEvent, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_PsServiceRegErrRecord(): Push buffer error.");
    }

    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_PS_SRV_REG_FAIL,
                           WUEPS_PID_MMC,
                           (VOS_UINT8 *)&stPsSrvRegRstEvent,
                           sizeof(stPsSrvRegRstEvent));
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_CmServiceRejErrRecord
 功能描述  : 记录Cm Service 被拒异常事件
 输入参数  : VOS_UINT32                              ulCause,
             VOS_UINT32                              ulServiceStatus
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月13日
    作    者   : zwx247453
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_CmServiceRejErrRecord(
    VOS_UINT32                                              ulCause,
    VOS_UINT32                                              ulServiceStatus
)
{
    NAS_ERR_LOG_CM_SRV_REJ_IND_EVENT_STRU                   stCmSrvRejIndEvent;
    VOS_UINT32                                              ulIsLogNeedRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel           = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_CM_SRV_REJ_IND);
    ulIsLogNeedRecord = NAS_MML_IsErrLogNeedRecord(usLevel);

    /* 模块异常不需要记录或异常原因值不需要记录时，不保存异常信息 */
    if (VOS_FALSE == ulIsLogNeedRecord)
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_CM_SRV_REJ_IND_EVENT_STRU);

    /* 填充Cm服务被拒异常信息 */
    PS_MEM_SET(&stCmSrvRejIndEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stCmSrvRejIndEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_MMC),
                                      NAS_ERR_LOG_ALM_CM_SRV_REJ_IND,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stCmSrvRejIndEvent.ulCause         = ulCause;
    stCmSrvRejIndEvent.ulServiceStatus = ulServiceStatus;

    NAS_MNTN_OutputPositionInfo(&stCmSrvRejIndEvent.stPositionInfo);
    stCmSrvRejIndEvent.ucOriginalCause = NAS_MML_GetOriginalRejectCause(stCmSrvRejIndEvent.ulCause);

    /*
       将异常信息写入Buffer中
       实际写入的字符数与需要写入的不等则打印异常
     */
    ulResult = NAS_MML_PutErrLogRingBuf((VOS_CHAR *)&stCmSrvRejIndEvent, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_CmServiceRejErrRecord(): Push buffer error.");
    }

    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_CM_SRV_REJ_IND,
                           WUEPS_PID_MMC,
                           (VOS_UINT8 *)&stCmSrvRejIndEvent,
                           sizeof(stCmSrvRejIndEvent));

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_MoDetachIndRecord
 功能描述  : 记录MO Detach指示事件
 功能描述  : 记录主动Detach指示事件
 输入参数  : VOS_UINT32                              ulDetachType
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月13日
    作    者   : zwx247453
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_MoDetachIndRecord(
    VOS_UINT32                              ulDetachType
)
{
    NAS_ERR_LOG_MO_DETACH_IND_EVENT_STRU                    stMoDetachIndEvent;
    VOS_UINT32                                              ulIsLogNeedRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel           = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_MO_DETACH_IND);
    ulIsLogNeedRecord = NAS_MML_IsErrLogNeedRecord(usLevel);

    /* 模块异常不需要记录或异常原因值不需要记录时，不保存异常信息 */
    if (VOS_FALSE == ulIsLogNeedRecord)
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_MO_DETACH_IND_EVENT_STRU);

    /* 填充本地DETACH异常信息 */
    PS_MEM_SET(&stMoDetachIndEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stMoDetachIndEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_MMC),
                                      NAS_ERR_LOG_ALM_MO_DETACH_IND,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    NAS_MNTN_OutputPositionInfo(&stMoDetachIndEvent.stPositionInfo);

    stMoDetachIndEvent.enDetachType         = ulDetachType;

    /*
       将异常信息写入Buffer中
       实际写入的字符数与需要写入的不等则打印异常
     */
    ulResult = NAS_MML_PutErrLogRingBuf((VOS_CHAR *)&stMoDetachIndEvent, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_MoDetachIndRecord(): Push buffer error.");
    }

    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_MO_DETACH_IND,
                           WUEPS_PID_MMC,
                           (VOS_UINT8 *)&stMoDetachIndEvent,
                           sizeof(stMoDetachIndEvent));

    return;
}

#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_ErrLogRecordCsOosCause
 功能描述  : 记录CS域出服务的原因值
 输入参数  : enOldCsRegStatus -- 旧的CS域注册状态
             enNewCsRegStatus -- 新的CS域注册状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月13日
    作    者   : f00179208
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ErrLogRecordCsOosCause(
    NAS_MML_REG_STATUS_ENUM_UINT8        enOldCsRegStatus,
    NAS_MML_REG_STATUS_ENUM_UINT8        enNewCsRegStatus
)
{
    NAS_ERR_LOG_OOS_EVENT_ENUM_UINT32    enOosEvent;
    NAS_ERR_LOG_OOS_CAUSE_ENUM_UINT32    enOosCause;

    /* 有服务到无服务的情况下，记录无服务的原因 */
    if (((NAS_MML_REG_REGISTERED_HOME_NETWORK == enOldCsRegStatus)
      || (NAS_MML_REG_REGISTERED_ROAM         == enOldCsRegStatus))
     && ((NAS_MML_REG_REGISTERED_HOME_NETWORK != enNewCsRegStatus)
      && (NAS_MML_REG_REGISTERED_ROAM         != enNewCsRegStatus)))
    {
        enOosEvent = NAS_MML_GetErrLogOosEvent();
        enOosCause = NAS_MNTN_ConvertOosEventToOosCause(enOosEvent);

        NAS_MML_SetErrLogCsOosCause(enOosCause);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ErrLogRecordPsOosCause
 功能描述  : 记录PS域出服务的原因值
 输入参数  : enOldPsRegStatus -- 旧的PS域注册状态
             enNewPsRegStatus -- 新的PS域注册状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月13日
    作    者   : f00179208
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ErrLogRecordPsOosCause(
    NAS_MML_REG_STATUS_ENUM_UINT8        enOldPsRegStatus,
    NAS_MML_REG_STATUS_ENUM_UINT8        enNewPsRegStatus
)
{
    NAS_ERR_LOG_OOS_EVENT_ENUM_UINT32    enOosEvent;
    NAS_ERR_LOG_OOS_CAUSE_ENUM_UINT32    enOosCause;

    /* 有服务到无服务的情况下，记录无服务的原因 */
    if (((NAS_MML_REG_REGISTERED_HOME_NETWORK == enOldPsRegStatus)
      || (NAS_MML_REG_REGISTERED_ROAM         == enOldPsRegStatus))
     && ((NAS_MML_REG_REGISTERED_HOME_NETWORK != enNewPsRegStatus)
      && (NAS_MML_REG_REGISTERED_ROAM         != enNewPsRegStatus)))
    {
        enOosEvent = NAS_MML_GetErrLogOosEvent();
        enOosCause = NAS_MNTN_ConvertOosEventToOosCause(enOosEvent);

        NAS_MML_SetErrLogPsOosCause(enOosCause);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ErrLogClrNwSearchCount
 功能描述  : 清除搜网记录次数
 输入参数  : enOldRegStatus -- 旧的域注册状态
             enNewRegStatus -- 新的域注册状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月13日
    作    者   : f00179208
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ErrLogClrNwSearchCount(
    NAS_MML_REG_STATUS_ENUM_UINT8        enOldRegStatus,
    NAS_MML_REG_STATUS_ENUM_UINT8        enNewRegStatus
)
{
    /* 无服务到有服务的情况下，清除搜网记录的次数 */
    if (((NAS_MML_REG_REGISTERED_HOME_NETWORK != enOldRegStatus)
      && (NAS_MML_REG_REGISTERED_ROAM         != enOldRegStatus))
     && ((NAS_MML_REG_REGISTERED_HOME_NETWORK == enNewRegStatus)
      || (NAS_MML_REG_REGISTERED_ROAM         == enNewRegStatus)))
    {
        NAS_MML_ClrErrLogNwSearchCount();
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RecordErrLogOosEvent
 功能描述  : 记录出服务的事件
 输入参数  : enOosEvent
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月13日
    作    者   : f00179208
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_RecordOosEvent(
    NAS_ERR_LOG_OOS_EVENT_ENUM_UINT32    enOosEvent
)
{
    NAS_MML_SetErrLogOosEvent(enOosEvent);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RecordOosEventForPlmnSearchScene
 功能描述  : 根据搜网场景记录出服务的事件
 输入参数  : enPlmnSearchScene
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月21日
    作    者   : f00179208
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_RecordOosEventForPlmnSearchScene(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32    enPlmnSearchScene
)
{
    switch (enPlmnSearchScene)
    {
        case NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE:
            NAS_MML_SetErrLogOosEvent(NAS_ERR_LOG_OOS_EVENT_DISABLE_LTE);
            break;

        case NAS_MMC_PLMN_SEARCH_SCENE_ENABLE_LTE_PLMN_SEARCH:
            NAS_MML_SetErrLogOosEvent(NAS_ERR_LOG_OOS_EVENT_ENABLE_LTE);
            break;

        default:
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RecordOosEventForDetachReason
 功能描述  : 根据DETACH原因记录出服务的事件
 输入参数  : enDetachReason
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月31日
    作    者   : f00179208
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_RecordOosEventForDetachReason(
    NAS_MSCC_PIF_DETACH_REASON_ENUM_UINT32  enDetachReason
)
{
    switch (enDetachReason)
    {
        case NAS_MSCC_PIF_DETACH_REASON_USER_DETACH:
            NAS_MML_SetErrLogOosEvent(NAS_ERR_LOG_OOS_EVENT_USER_DETACH);
            break;

        case NAS_MSCC_PIF_DETACH_REASON_RAT_OR_BAND_DETACH:
        case NAS_MSCC_PIF_DETACH_REASON_SRV_DOMAIN_DETACH:
            NAS_MML_SetErrLogOosEvent(NAS_ERR_LOG_OOS_EVENT_USER_SYSCFG);
            break;

        default:
            break;
    }

    return;

}

/* 接入层获取NAS层相关信息函数 */
/*****************************************************************************
 函 数 名  : MM_GetNasInfo
 功能描述  : WAS 获取通过调用此接口来获取NAS的相关信息。比如说PLMN的信息等
             。
 输入参数  : VOS_INT8 ucType -- 0 :  PLMN信息与卡状态信息获得 其余值未定义
             VOS_VOID *pMmInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年1月4日
    作    者   : liuyang id:48197
    修改内容   : 新生成函数,根据A32D01561问题单添加
  2.日    期   : 2006年12月5日
    作    者   : luojian 60022475
    修改内容   : Maps3000接口修改
  3.日    期   : 2010年08月14日
    作    者   : s46746
    修改内容   : DTS2010081400653,PLMN信息修改为直接给接入层指示EPLMN，与GAS组确认
  4.日    期   : 2011年12月07日
    作    者   : s46746
    修改内容   : DTS2011112501364,当前没有EPLMN列表时需要将当前网络作为EPLMN返回,否则无法进行异系统重选
  5.日    期   : 2012年2月2日
    作    者   : l00130025
    修改内容   : DTS2012011905274,MM_GetNasInfo中的Eplmn错误，导致L下无法重选到G下
  6.日    期   : 2012年8月15日
    作    者   : w00176964
    修改内容   : V7R1C50_GUTL_PhaseII:在disabled RAT中的PLMN从等效PLMN列表中删除后发送给RRC
  7.日    期   : 2012年12月4日
    作    者   : w00176964
    修改内容   : DTS201212905979:通知RRC当前EPLMN时,清除禁止PLMN
  8.日    期   : 2013年10月15日
    作    者   : z00161729
    修改内容   : DTS2013082907281:UE在w进行紧急呼叫过程rrc rej重定向到g的消息，
                呼叫结束后无法成功重定向到w原小区，因为接入层查询plmn时nas只带了g小区plmn
  9.日    期   : 2013年11月18日
    作    者   : z00161729
    修改内容   : DTS2013111807881:接入层查询eplmn，当前驻留网络需要判断是否为禁止网络，如果是则不通知接入层
  10.日    期   : 2015年1月15日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
  11.日    期   : 2015年4月23日
     作    者   : z00161729
     修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID MM_GetNasInfo(MM_INFO_ST *pMmInfo)
{
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmn;
    NAS_MML_LAI_STRU                                       *pstLai;
    NAS_MML_PLMN_ID_STRU                                   *pstCurPlmnAddr;
    VOS_UINT32                                              i;
    PLMN_INFO_LIST_ST                                      *pstPlmnList;
    MM_INFO_ST                                             *pstMmInfo;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                       *pstForbidPlmnInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnWithRat;

    NAS_MML_PLMN_WITH_RAT_STRU                             *pstUserSpecPlmnId = VOS_NULL_PTR;
    VOS_UINT32                                              ulEplmnValidFlg;
    VOS_UINT32                                              ulRegFlag;

    VOS_UINT32                                              ulIsPlmnIdInDestPlmnWithRatList;
    VOS_UINT32                                              ulIsPlmnIdInForbidPlmnList;

    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU            *pstForbLaWithValidPeriodList =VOS_NULL_PTR;


    pstForbidPlmnInfo = NAS_MML_GetForbidPlmnInfo();
    pstEquPlmn        = NAS_MML_GetEquPlmnList();
    pstMmInfo         = (MM_INFO_ST *)pMmInfo;
    pstPlmnList       = &(pstMmInfo->stPlmnInfo);


    pstCurPlmnAddr    = NAS_MML_GetCurrCampPlmnId();
    pstLai            = NAS_MML_GetCurrCampLai();

    pstPlmnList->stEplmnInfo.ulPlmnIdNum  = 0;
    pstPlmnList->stEplmnInfo.bitOpCurPlmn = VOS_FALSE;
    pstUserSpecPlmnId                     = NAS_MMC_GetUserSpecPlmnId();
    ulEplmnValidFlg                       = NAS_MML_GetEplmnValidFlg();
    ulRegFlag                             = NAS_MMC_GetUserSpecPlmnRegisterStatus();

    /*获取禁止列表*/
    pstPlmnList->ulForbLaNum = pstForbidPlmnInfo->ucForbRoamLaNum;

    for (i = 0; i < pstPlmnList->ulForbLaNum; i++)
    {
        pstPlmnList->aForbLaList[i].PlmnId.ulMcc = pstForbidPlmnInfo->astForbRomLaList[i].stPlmnId.ulMcc;
        pstPlmnList->aForbLaList[i].PlmnId.ulMnc = pstForbidPlmnInfo->astForbRomLaList[i].stPlmnId.ulMnc;

        pstPlmnList->aForbLaList[i].ulForbLac    = (VOS_UINT32)pstForbidPlmnInfo->astForbRomLaList[i].aucLac[1]
                                                   |(VOS_UINT32)((VOS_UINT32)pstForbidPlmnInfo->astForbRomLaList[i].aucLac[0]<<8);
    }

    pstForbLaWithValidPeriodList = NAS_MML_GetForbLaWithValidPeriodList();
    for ( i = 0; i < pstForbLaWithValidPeriodList->ulForbLaWithValidPeriodNum; i++ )
    {
        pstLai = &(pstForbLaWithValidPeriodList->astForbLaWithValidPeriodList[i].stForbLaWithValidPeriodLai);
        if ( (VOS_FALSE == NAS_MML_IsLaiInDestLaiList(pstLai, pstForbidPlmnInfo->ucForbRoamLaNum, pstForbidPlmnInfo->astForbRomLaList))
          && ( pstPlmnList->ulForbLaNum < RRC_MAX_FORBLA_NUM) )
        {
            pstPlmnList->aForbLaList[pstPlmnList->ulForbLaNum].PlmnId.ulMcc   =
                        pstLai->stPlmnId.ulMcc;
            pstPlmnList->aForbLaList[pstPlmnList->ulForbLaNum].PlmnId.ulMnc   =
                        pstLai->stPlmnId.ulMnc;
            pstPlmnList->aForbLaList[pstPlmnList->ulForbLaNum].ulForbLac      =
                        ((VOS_UINT32)((pstLai->aucLac[0]) << 8 ) | (VOS_UINT32)((pstLai->aucLac[1])));
            (pstPlmnList->ulForbLaNum)++;
        }
    }


    /*获取usim卡状态*/
    if (VOS_FALSE == NAS_MML_IsUsimStausValid())
    {                                                                           /* SIM卡不存在                              */
        pstMmInfo->stSimInfo.ulSimStatus = RRC_NAS_UICC_ABSENT;                                      /* 设定SIM卡状态                            */
    }
    else
    {                                                                           /* SIM卡存在                                */
        if (NAS_MML_SIM_TYPE_SIM  == NAS_MML_GetSimType())
        {
            pstMmInfo->stSimInfo.ulSimStatus = RRC_NAS_SIM_PRESENT;
        }
        else
        {
            pstMmInfo->stSimInfo.ulSimStatus = RRC_NAS_USIM_PRESENT;                                     /* 设定SIM卡状态                            */
        }

        pstMmInfo->ucUeOperMode = NAS_MML_GetUeOperMode();
    }

    pMmInfo->stCurPlmnId.ulMcc = pstCurPlmnAddr->ulMcc;
    pMmInfo->stCurPlmnId.ulMnc = pstCurPlmnAddr->ulMnc;

    pMmInfo->usCurLac          = (VOS_UINT16)pstLai->aucLac[1]
                                 |(VOS_UINT16)((VOS_UINT16)pstLai->aucLac[0]<<8);

    pMmInfo->ucCurRac          = NAS_MML_GetCurrCampRac();

    pstPlmnList->stEplmnInfo.stCurCampedPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    pstPlmnList->stEplmnInfo.stCurCampedPlmnId.ulMnc = NAS_MML_INVALID_MNC;

    stPlmnWithRat.enRat         = NAS_MML_NET_RAT_TYPE_GSM;

    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        stPlmnWithRat.stPlmnId = pstUserSpecPlmnId->stPlmnId;
    }
    else
    {
        stPlmnWithRat.stPlmnId = *pstCurPlmnAddr;
    }

    ulIsPlmnIdInDestPlmnWithRatList = NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat);

    ulIsPlmnIdInForbidPlmnList = NAS_MML_IsPlmnIdInForbidPlmnList(&stPlmnWithRat.stPlmnId);

    if ((VOS_FALSE == ulIsPlmnIdInDestPlmnWithRatList)
     && (VOS_FALSE == ulIsPlmnIdInForbidPlmnList))
    {
        pstPlmnList->stEplmnInfo.bitOpCurPlmn = VOS_TRUE;
        pMmInfo->stPlmnInfo.stEplmnInfo.stCurCampedPlmnId.ulMcc = stPlmnWithRat.stPlmnId.ulMcc;
        pMmInfo->stPlmnInfo.stEplmnInfo.stCurCampedPlmnId.ulMnc = stPlmnWithRat.stPlmnId.ulMnc;
    }

    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        /* 判断eplmn列表是否有效,无效则返回 */
        if ((VOS_FALSE == ulRegFlag)
         || (VOS_FALSE == ulEplmnValidFlg))
        {
            pstPlmnList->stEplmnInfo.ulPlmnIdNum  = 0;
            return;
        }
    }

    /* 获取等效PLMN列表,若当前网络不在Eplmn中,将当前网络返回给接入层 */
    for (i = 0; i < pstEquPlmn->ucEquPlmnNum; i++)
    {
        /* 构造带接入技术的PLMN ID */
        stPlmnWithRat.enRat         = NAS_MML_NET_RAT_TYPE_GSM;
        stPlmnWithRat.stPlmnId      = pstEquPlmn->astEquPlmnAddr[i];

        /* 判断等效PLMN是否在禁止接入技术的PLMN列表中,如果在则不将该PLMN ID发给RRC */
        if (VOS_TRUE == NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
        {
            continue;
        }

        if (VOS_TRUE == NAS_MML_IsPlmnIdInForbidPlmnList(&(pstEquPlmn->astEquPlmnAddr[i])))
        {
            continue;
        }

        pstPlmnList->stEplmnInfo.aPlmnIdList[pstPlmnList->stEplmnInfo.ulPlmnIdNum].ulMcc = pstEquPlmn->astEquPlmnAddr[i].ulMcc;
        pstPlmnList->stEplmnInfo.aPlmnIdList[pstPlmnList->stEplmnInfo.ulPlmnIdNum].ulMnc = pstEquPlmn->astEquPlmnAddr[i].ulMnc;
        pstPlmnList->stEplmnInfo.ulPlmnIdNum++;
    }



    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsCsPsBothRegSucc
 功能描述  : 判断cs和ps是否都注册成功
 输入参数  : enNetRatType - 接入技术
 输出参数  : 无
 返 回 值  : VOS_TRUE:cs和ps注册均成功
             VOS_FALSE:cs和ps不是都注册成功
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年4月22日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsCsPsBothRegSucc(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetRatType
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsRegCause;
    NAS_MMC_SERVICE_ENUM_UINT8          enPsServiceStatus;
    NAS_MMC_SERVICE_ENUM_UINT8          enCsServiceStatus;


    enPsRegCause            = NAS_MML_REG_FAIL_CAUSE_NULL;
    enCsRegCause            = NAS_MML_REG_FAIL_CAUSE_NULL;

    enCsServiceStatus = NAS_MMC_GetCsServiceStatus();
    enPsServiceStatus = NAS_MMC_GetPsServiceStatus();


    /* 获取之前注册失败的原因值 */
    NAS_MMC_GetDomainRegStatusInRegInfoList(NAS_MML_GetCurrCampPlmnId(),
                                            enNetRatType,
                                            &enCsRegCause,
                                            &enPsRegCause);


    if ((NAS_MMC_NORMAL_SERVICE == enCsServiceStatus)
     && (NAS_MMC_NORMAL_SERVICE == enPsServiceStatus)
     && (NAS_MML_REG_FAIL_CAUSE_NULL == enCsRegCause)
     && (NAS_MML_REG_FAIL_CAUSE_NULL == enPsRegCause))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-10, begin */
#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail
 功能描述  : IMS不可用后判断是否需要disable LTE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要disable LTE
             VOS_FALSE:不需要disable LTE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月10日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2014年5月6日
   作    者   : z00161729
   修改内容   : DTS2014050602850:l下联合注册eps成功，cs注册被#18拒绝，disable lte到gu下搜网注册成功，后指定搜l cs注册被#18拒绝的网络，l发起eps单域注册成功，mmc没有disable lte
 3.日    期   : 2014年5月8日
   作    者   : z00161729
   修改内容   : DTS2014050701865:volte修改cs ps mode1 l被16、17、22拒绝达5次disable lte后未启动enable lte定时器
 4.日    期   : 2014年5月19日
   作    者   : w00242748
   修改内容   : DTS2014051402293:CSPS MODE1，指定搜24005 L，LTE下注册成功，指示SMS ONLY，
                Disable LTE后，发起GU下搜网，GU下搜网失败，RECAMP LTE(真流程)后，启动available
                定时器超时后，发起列表搜，带起来与24005等效PLMN的46002L、24005L、23002GU，指定
                搜这两个L下PLMN失败，紧急驻留在GU23002下，并启动available定时器。available定时
                器超时，搜网回24005 L(即需要disalbe lte的网络)，L下给NAS上报TAU假流程，此时NAS
                未进行Disable LTE，也未启动available定时器。
 5.日    期   : 2014年5月19日
   作    者   : w00242748
   修改内容   : DTS2014051308442:L下注册成功支持IMS，但SMS ONLY，周期性TAU被16拒一次，直接disable
                LTE。
 6.日    期   : 2014年5月20日
   作    者   : s00217060
   修改内容   : DTS2014051406792:L下TAU被拒#18，当作other cause处理，5次之后disable LTE。
 7.日    期   : 2015年1月5日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改
 8.日    期   : 2015年4月22日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail(VOS_VOID)
{
    VOS_UINT32                                              ulIsNeedDisableL;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegCause;
    NAS_MMC_SERVICE_ENUM_UINT8                              enPsServiceStatus;

    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnWithRat;

    VOS_UINT32                                              ulIsNeedAddVoiceNotAvailPlmnFlag;

    NAS_MMC_REG_RSLT_CTX_STRU                              *pstRegRsltCtx = VOS_NULL_PTR;

    pstRegRsltCtx   = NAS_MMC_GetRegRsltCtxAddr();

    enPsRegCause            = NAS_MML_REG_FAIL_CAUSE_NULL;
    enCsRegCause            = NAS_MML_REG_FAIL_CAUSE_NULL;

    /* 如果已经disable 不需要再disable LTE */
    if (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail: NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS");
        return VOS_FALSE;
    }


    /* 之前在L下进行过未TAU和ATTACH或业务请求 */
    if ( NAS_MML_NET_RAT_TYPE_LTE != NAS_MML_GetCurrNetRatType() )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail: CURR NOT LTE");
        return VOS_FALSE;
    }

    enPsServiceStatus = NAS_MMC_GetPsServiceStatus();

    PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(), sizeof(stPlmnWithRat.stPlmnId));
    stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

    /* 获取之前注册失败的原因值 */
    NAS_MMC_GetDomainRegStatusInRegInfoList(NAS_MML_GetCurrCampPlmnId(),
                                            NAS_MML_NET_RAT_TYPE_LTE,
                                            &enCsRegCause,
                                            &enPsRegCause);

    /* CS+EPS 都成功 */
    if (VOS_TRUE == NAS_MMC_IsCsPsBothRegSucc(NAS_MML_NET_RAT_TYPE_LTE))
    {
        ulIsNeedDisableL = NAS_MMC_IsNeedDisableL_CombinedRegRsltSucc();

        if (VOS_TRUE == ulIsNeedDisableL)
        {
            if (VOS_TRUE == NAS_MML_IsNeedAddVoiceNotAvailDisabledPlmnInDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat, NAS_MML_REG_FAIL_CAUSE_NULL, NAS_MML_REG_FAIL_CAUSE_NULL, NAS_MML_GetAdditionUpdateRslt()))
            {
                NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                                                              NAS_MML_GetVoiceNotPreferDisabledPlmnForbiddenTimeSlice(),
                                                              MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
            }
        }

        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail: CS&EPS SUCC");

        return ulIsNeedDisableL;
    }

    if ((NAS_MMC_NORMAL_SERVICE == enPsServiceStatus)
     && (NAS_MML_REG_FAIL_CAUSE_NULL == enPsRegCause))
    {

        /* EPS单域注册成功 */
        if (VOS_TRUE == pstRegRsltCtx->ucIsLteRegTypeEpsOnly)
        {
            ulIsNeedDisableL = NAS_MMC_IsNeedDisableL_EpsOnlyRegSucc();

            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail: ONLY EPS SUCC");

            return ulIsNeedDisableL;
        }

        /* EPS ONLY成功,CS被拒18,CS被拒16,17,22,other cause,EPS尝试次数达到5次 */
        if (NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR != enCsRegCause)
        {
            ulIsNeedDisableL = NAS_MMC_IsNeedDisableL_CombinedRegRsltOnlyEpsSucc(enCsRegCause);

            NAS_WARNING_LOG1(WUEPS_PID_MMC, "NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail: ulIsNeedDisableL.", ulIsNeedDisableL);

            if ((NAS_MML_MAX_PS_REG_FAIL_CNT == NAS_MMC_GetRegRsltAttemptCounter(NAS_MMC_GetRegRsltType()))
              && (VOS_TRUE == ulIsNeedDisableL))
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER, NAS_MML_GetCsPsMode1EnableLteTimerLen());

                if (VOS_TRUE == NAS_MML_IsNeedAddDamPlmnInDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
                {
                    NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                                                                  NAS_MML_GetDamDisabledPlmnWithForbiddenPeriodTimeSlice(&stPlmnWithRat),
                                                                  MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
                }

            }

            ulIsNeedAddVoiceNotAvailPlmnFlag = NAS_MML_IsNeedAddVoiceNotAvailDisabledPlmnInDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat, enCsRegCause, enPsRegCause, NAS_MML_GetAdditionUpdateRslt());

            NAS_WARNING_LOG1(WUEPS_PID_MMC, "NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail: ulIsNeedAddVoiceNotAvailPlmnFlag.", ulIsNeedAddVoiceNotAvailPlmnFlag);

            if ((VOS_TRUE == ulIsNeedDisableL)
             && (VOS_TRUE == ulIsNeedAddVoiceNotAvailPlmnFlag))
            {
                NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                                                              NAS_MML_GetVoiceNotPreferDisabledPlmnForbiddenTimeSlice(),
                                                              MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
            }
            return ulIsNeedDisableL;
        }
    }

    return VOS_FALSE;
}

#endif
/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-10, end */

/*****************************************************************************
 函 数 名  : NAS_MMC_GetWaitGasPlmnSearchCnfTimerLen
 功能描述  : 获取GAS下搜网定时器时长
 输入参数  : ulUserSpecSearchFlg:是否用户指定搜
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月11日
    作    者   : w00167002
    修改内容   : 新生成函数:当前在DSDS双卡中，GSM下搜网可能不回NAS 搜网NO RF,那么
                 NAS搜网定时器超时，则上报无服务了。修改为延长NAS定时器时长。
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetWaitGasPlmnSearchCnfTimerLen(
    VOS_UINT32                          ulUserSpecSearchFlg
)
{
    /* 在DSDS版本模式并且非用户指定搜时候，取长定时器的时长 */
    if ( (VOS_TRUE == NAS_MML_IsDsdsMultiModemMode())
      && (VOS_FALSE == ulUserSpecSearchFlg) )
    {
        return TI_NAS_MMC_DSDS_SCEAN_WAIT_GAS_PLMN_SEARCH_CNF_LEN;
    }

    return TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF_LEN;
}




/*****************************************************************************
 函 数 名  : NAS_MMC_RegisterRrmResourceNtf
 功能描述  : 处理向RRM发送注册信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月29日
    作    者   : y00176023
    修改内容   : 新生成函数
  2.日    期   : 2014年7月26日
    作    者   : b00269685
    修改内容   : DSDS IV接口修改
*****************************************************************************/
VOS_VOID NAS_MMC_RegisterRrmResourceNtf(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNasRat,
    RRM_PS_TASK_TYPE_ENUM_UINT16        enRrmTaskType
)
{
#if (FEATURE_ON == FEATURE_DSDS)
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_RATMODE_ENUM_UINT32             enRrmRat;

    enRrmRat = NAS_MMC_ConvertRatToRrmPsRat(enNasRat);

    /* 获取modem id */
    enModemId = VOS_GetModemIDFromPid(WUEPS_PID_MMC);

    /* 如果当前NV未开启DSDS,则不向RRM发送注册 */
    if ( VOS_FALSE == NAS_MML_GetDsdsRfShareFlg() )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RegisterRrmResourceNtf: DSDS RF SHARE FLG IS VOS_FALSE!!!");
        return;
    }

    /* 发送注册消息 */
    if((VOS_RATMODE_BUTT     != enRrmRat)
    && (MODEM_ID_BUTT        != enModemId))
    {
        NAS_MMC_SndRrmRegisterInd(enModemId,
                                  enRrmTaskType,
                                  enRrmRat);
    }

#endif

    NAS_INFO_LOG2(WUEPS_PID_MMC, "NAS_MMC_RegisterRrmResourceNtf : enNasRat, enRrmTaskType", enNasRat, enRrmTaskType);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_DeregisterRrmResourceNtf
 功能描述  : 处理向RRM发送去注册信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月29日
    作    者   : y00176023
    修改内容   : 新生成函数
  2.日    期   : 2014年7月26日
    作    者   : b00269685
    修改内容   : DSDS IV接口修改
*****************************************************************************/
VOS_VOID NAS_MMC_DeregisterRrmResourceNtf(
    VOS_RATMODE_ENUM_UINT32             enRrmRat,
    RRM_PS_TASK_TYPE_ENUM_UINT16        enRrmTaskType
)
{
#if (FEATURE_ON == FEATURE_DSDS)
    MODEM_ID_ENUM_UINT16                usModemId;

    /* 取得当前MODEM的ID信息  */
    usModemId = VOS_GetModemIDFromPid(WUEPS_PID_MMC);

    /* 如果当前NV未开启DSDS,则不向RRM发送去注册 */
    if ( VOS_FALSE == NAS_MML_GetDsdsRfShareFlg() )
    {
        return;
    }

    /* 向RRM发送的去注册信息 */
    if((VOS_RATMODE_BUTT     != enRrmRat)
    && (MODEM_ID_BUTT        != usModemId))
    {
        NAS_MMC_SndRrmDeRegisterInd(usModemId,
                                    enRrmTaskType,
                                    enRrmRat);
    }
#endif

    NAS_INFO_LOG2(WUEPS_PID_MMC, "NAS_MMC_DeregisterRrmResourceNtf : enRrmRat, enRrmTaskType", enRrmRat, enRrmTaskType);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_DeregisterRrmResourceNtfAllRat
 功能描述  : 处理向RRM发送平台支持所有RAT去注册信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月16日
    作    者   : y00176023
    修改内容   : 新生成函数
  2.日    期   : 2014年7月26日
    作    者   : b00269685
    修改内容   : 接口修改
*****************************************************************************/
VOS_VOID NAS_MMC_DeregisterRrmResourceNtfAllRat(
    RRM_PS_TASK_TYPE_ENUM_UINT16        enRrmTaskType
)
{
    VOS_UINT32                          i;
    NAS_MML_PLATFORM_RAT_CAP_STRU      *pstPlatformRatCap  = VOS_NULL_PTR;

    pstPlatformRatCap = NAS_MML_GetPlatformRatCap();

    /* LTE是否在平台接入技术能力列表中 */
    for (i = 0 ; i < pstPlatformRatCap->ucRatNum; i++)
    {
        if (NAS_MML_PLATFORM_RAT_TYPE_GSM == pstPlatformRatCap->aenRatPrio[i])
        {
            /* 根据保护模式类型向RRM发送去注册消息 */
            NAS_MMC_DeregisterRrmResourceNtf(VOS_RATMODE_GSM, enRrmTaskType);
        }
#if (FEATURE_ON == FEATURE_LTE)
        else if (NAS_MML_PLATFORM_RAT_TYPE_LTE == pstPlatformRatCap->aenRatPrio[i])
        {
            /* 根据保护模式类型向RRM发送去注册消息 */
            NAS_MMC_DeregisterRrmResourceNtf(VOS_RATMODE_LTE, enRrmTaskType);
        }
#endif
        else if (NAS_MML_PLATFORM_RAT_TYPE_WCDMA == pstPlatformRatCap->aenRatPrio[i])
        {
            /* 根据保护模式类型向RRM发送去注册消息 */
            NAS_MMC_DeregisterRrmResourceNtf(VOS_RATMODE_WCDMA, enRrmTaskType);
        }
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
        else if (NAS_MML_PLATFORM_RAT_TYPE_TD_SCDMA == pstPlatformRatCap->aenRatPrio[i])
        {
            /* 根据保护模式类型向RRM发送注册、去注册消息 */
            NAS_MMC_DeregisterRrmResourceNtf(VOS_RATMODE_TDS, enRrmTaskType);\
        }
#endif
        else
        {
            ;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertRatToRrmPsRat
 功能描述  : 将传进来的RAT转换为RRM PS RAT
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月29日
    作    者   : y00176023
    修改内容   : 新生成函数
  2.日    期   : 2014年7月26日
    作    者   : b00269685
    修改内容   : DSDS IV接口修改
*****************************************************************************/
VOS_RATMODE_ENUM_UINT32 NAS_MMC_ConvertRatToRrmPsRat(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enMmcRat
)
{
    VOS_RATMODE_ENUM_UINT32             enRrmPsRat;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode;

    /*获取TD还是WCDMA*/
    enUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();

    if (NAS_MML_NET_RAT_TYPE_GSM == enMmcRat)
    {
        enRrmPsRat = VOS_RATMODE_GSM;
    }
    else if ((NAS_MML_NET_RAT_TYPE_WCDMA   == enMmcRat)
          && (NAS_UTRANCTRL_UTRAN_MODE_FDD == enUtranMode))
    {
        enRrmPsRat = VOS_RATMODE_WCDMA;
    }
    else if ((NAS_MML_NET_RAT_TYPE_WCDMA   == enMmcRat)
          && (NAS_UTRANCTRL_UTRAN_MODE_TDD == enUtranMode))
    {
        enRrmPsRat = VOS_RATMODE_TDS;
    }
#if (FEATURE_ON == FEATURE_LTE)
    else if (NAS_MML_NET_RAT_TYPE_LTE == enMmcRat)
    {
        enRrmPsRat = VOS_RATMODE_LTE;
    }
#endif
    else
    {
        enRrmPsRat = VOS_RATMODE_BUTT;
    }

    return enRrmPsRat;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer_CsfbEnd
 功能描述  : CSFB END触发的搜网是否需要启高优先级RAT的HPLMN定时器
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月26日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer_CsfbEnd( VOS_VOID )
{
    VOS_UINT32                                              ulIsRrcConnExist;
    VOS_UINT32                                              ulIsNeedStartHighPrioRatHPlmnTimer;

    ulIsRrcConnExist                    = NAS_MML_IsRrcConnExist();
    ulIsNeedStartHighPrioRatHPlmnTimer  = NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer();

    /* 业务不存在，并且RRC链接不存在，高优先级RAT的HPLMN定时器的NV打开 */
    if ((VOS_FALSE  == NAS_MML_GetCmServiceSetupFlg())
     && (VOS_FALSE  == ulIsRrcConnExist)
     && (VOS_TRUE   == ulIsNeedStartHighPrioRatHPlmnTimer))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer
 功能描述  : 判断是否需要启动高优先级RAT的HPLMN定时器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要启动HPLMN定时器
             VOS_FALSE:不需要启动HPLMN定时器
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年2月19日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer(VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPlmnRatList       = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCurrCampPlmnInfo  = VOS_NULL_PTR;

    if (VOS_FALSE == NAS_MMC_IsHighPrioRatHplmnSearchVaild())
    {
        return VOS_FALSE;
    }

    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER))
    {
        return VOS_FALSE;
    }

    /* 获取MML中保存的当前MS支持的接入模式和接入优先级 */
    pstPlmnRatList = NAS_MML_GetMsPrioRatList();

    pstCurrCampPlmnInfo = NAS_MML_GetCurrCampPlmnInfo();

    if (VOS_FALSE == NAS_MML_ComparePlmnIdWithHplmn(&pstCurrCampPlmnInfo->stLai.stPlmnId))
    {
        return VOS_FALSE;
    }

    /* 驻留到HPLMN是最高优先级的接入技术 */
    if (pstPlmnRatList->aucRatPrio[0] == pstCurrCampPlmnInfo->stLai.enCampPlmnNetRat)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsHighPrioRatHplmnSearchVaild
 功能描述  : 高优先级RAT的HPLMN选网当前是否有效
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:有效
             VOS_FALSE:无效
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年2月21日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsHighPrioRatHplmnSearchVaild( VOS_VOID )
{
    NAS_MML_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU       *pstHighRatHplmnTimerCfg = VOS_NULL_PTR;

    pstHighRatHplmnTimerCfg = NAS_MML_GetHighPrioRatHplmnTimerCfg();

    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return VOS_FALSE;
    }

    if (VOS_FALSE == NAS_MML_GetHighPrioRatHplmnTimerActiveFlg())
    {
        return VOS_FALSE;
    }

    /* 手动模式下返回无效 */
    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        return VOS_FALSE;
    }

    if (VOS_FALSE == NAS_MML_IsUsimStausValid())
    {
        return VOS_FALSE;
    }

    /* HPLMN TIMER LEN定时器时长无效 */
    if ((0 != pstHighRatHplmnTimerCfg->ulFirstSearchTimeLen)
     && (0 != pstHighRatHplmnTimerCfg->ulNonFirstSearchTimeLen)
     && (0 != pstHighRatHplmnTimerCfg->ulRetrySearchTimeLen))
    {
        /* 返回有效 */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsCampOnHighestPrioRatHplmn
 功能描述  : 判断当前是否已经驻留在最高RAT优先级的HPLMN上
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  : 已经驻留在最高RAT优先级的HPLMN上
             VOS_FALSE : 没有驻留在最高RAT优先级的HPLMN上
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年2月22日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsCampOnHighestPrioRatHplmn(VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPlmnRatList       = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCurrCampPlmnInfo  = VOS_NULL_PTR;

    /* 获取MML中保存的当前MS支持的接入模式和接入优先级 */
    pstPlmnRatList = NAS_MML_GetMsPrioRatList();

    pstCurrCampPlmnInfo = NAS_MML_GetCurrCampPlmnInfo();

    /* 如果当前网络无效，则返回未驻留在最高优先级网络上，当单模丢网后，当前驻留的网络
       是无效PLMNID */
    if ( VOS_FALSE == NAS_MML_IsPlmnIdValid(&pstCurrCampPlmnInfo->stLai.stPlmnId) )
    {
        return VOS_FALSE;
    }

    if (VOS_FALSE == NAS_MML_ComparePlmnIdWithHplmn(&pstCurrCampPlmnInfo->stLai.stPlmnId))
    {
        return VOS_FALSE;
    }

    /* 驻留到HPLMN是非最高优先级的接入技术 */
    if (pstPlmnRatList->aucRatPrio[0] != pstCurrCampPlmnInfo->stLai.enCampPlmnNetRat)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateHighPrioRatHPlmnTimerTdCount
 功能描述  : 处理Td Count
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年10月27日
   作    者   : b00269685
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateHighPrioRatHPlmnTimerTdCount(VOS_VOID)
{
    VOS_UINT8                                               ucCurrHighRatHplmnTdCount;
    VOS_UINT8                                               ucHighRatHplmnTdThreshold;

    if (VOS_FALSE == NAS_MMC_IsCurrentTdscdmaMode())
    {
        return;
    }

    ucCurrHighRatHplmnTdCount = NAS_MMC_GetTdHighRatSearchCount();
    ucHighRatHplmnTdThreshold = NAS_MML_GetHighPrioRatHplmnTimerTdThreshold();

    if (ucCurrHighRatHplmnTdCount >= ucHighRatHplmnTdThreshold)
    {
        NAS_MMC_InitTdHighRatSearchCount();
    }

    NAS_MMC_AddTdHighRatSearchCount();

    return;

}

/* Added by s00246516 for L-C互操作项目, 2014-02-12, Begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_GetPlmnPrioClass
 功能描述  : 获取指定网络的优先级类别
 输入参数  : pstPlmnId
 输出参数  : 无
 返 回 值  : NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8:
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : s00246516
    修改内容   : 新生成函数
  2.日    期   : 2014年6月13日
    作    者   : b00269685
    修改内容   : 根据3gpp2,Pref网络不包含UPLMN
*****************************************************************************/
NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8 NAS_MMC_GetPlmnPrioClass(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    if (VOS_FALSE == NAS_MML_IsPlmnIdValid(pstPlmnId))
    {
        return NAS_MSCC_PIF_PLMN_PRIORITY_BUTT;
    }

    /* 与HPLMN相同，返回NAS_MSCC_PIF_PLMN_PRIORITY_HOME */
    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(pstPlmnId))
    {
        return NAS_MSCC_PIF_PLMN_PRIORITY_HOME;
    }

    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithUplmn(pstPlmnId))
    {
        if (VOS_FALSE == NAS_MML_Get3GPP2UplmnNotPrefFlg())
        {
            return NAS_MSCC_PIF_PLMN_PRIORITY_PREF;
        }
    }

    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithOplmn(pstPlmnId))
    {
        return NAS_MSCC_PIF_PLMN_PRIORITY_PREF;
    }

    return NAS_MSCC_PIF_PLMN_PRIORITY_ANY;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ComParePlmnPrioClass
 功能描述  : 比较两个PLMN优先级级别的优先级
 输入参数  : enSrcPrioClass
             enDestPrioClass
 输出参数  : 无
 返 回 值  : VOS_TRUE  --enSrcPrioClass优先级高于或等于enDestPrioClass
             VOS_FALSE --enSrcPrioClass优先级低于enDestPrioClass
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : s00246516
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_ComParePlmnPrioClass(
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8                  enSrcPrioClass,
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8                  enDestPrioClass
)
{
    /* 如果enSrcPrioClass已经是最高优先级，直接返回VOS_TRUE */
    if (NAS_MSCC_PIF_PLMN_PRIORITY_HOME == enSrcPrioClass)
    {
        return VOS_TRUE;
    }
    else if (NAS_MSCC_PIF_PLMN_PRIORITY_PREF == enSrcPrioClass)
    {
        /* 如果enSrcPrioClass是NAS_MSCC_PIF_PLMN_PRIORITY_PREF，仅在enDestPrioClass为最高优先级时返回VOS_FALSE */
        if (NAS_MSCC_PIF_PLMN_PRIORITY_HOME == enDestPrioClass)
        {
            return VOS_FALSE;
        }
        else
        {
            return VOS_TRUE;
        }
    }
    else
    {
        /* 如果enSrcPrioClass是NAS_MSCC_PIF_PLMN_PRIORITY_ANY，仅在enDestPrioClass为相同优先级时返回VOS_TRUE */
        if (NAS_MSCC_PIF_PLMN_PRIORITY_ANY == enDestPrioClass)
        {
            return VOS_TRUE;
        }
        else
        {
            return VOS_FALSE;
        }
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsSuccRegInSpecCellInfo
 功能描述  : 是否已经在指定CellInfo的小区上注册成功
 输入参数  : pstCellInfo
 输出参数  : 无
 返 回 值  : VOS_TRUE  --已经在指定CellInfo的小区上注册成功
             VOS_FALSE --没有在指定CellInfo的小区上注册成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : s00246516
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsSuccRegInSpecCellInfo(
    MSCC_MMC_REG_CELL_INFO_STRU         *pstCellInfo
)
{
    VOS_UINT32                          i;
    NAS_MML_CAMP_CELL_INFO_STRU        *pstCampCell         = VOS_NULL_PTR;

    /* 接入技术不同，返回VOS_FALSE */
    if (pstCellInfo->ucRat != NAS_MML_GetCurrNetRatType())
    {
        return VOS_FALSE;
    }

    /* 频点不同，返回VOS_FALSE */
    if (pstCellInfo->ulArfcn != NAS_MML_GetCurrCampArfcn())
    {
        return VOS_FALSE;
    }

    /* 请求消息中PLMN存在而且与当前驻留不同，返回VOS_FALSE */
    if (pstCellInfo->ucPlmnNum > 0)
    {
        if (VOS_FALSE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(NAS_MML_GetCurrCampPlmnId(),
                                                  pstCellInfo->ucPlmnNum,
                                                  pstCellInfo->astPlmnId))
        {
            return VOS_FALSE;
        }
    }

    /* 请求消息中没有携带小区ID，返回VOS_TRUE */
    if (0 == pstCellInfo->ucCellNum)
    {
        return VOS_TRUE;
    }

    pstCampCell     = NAS_MML_GetCampCellInfo();

    /* 请求消息中CELL ID存在而且与当前驻留相同，返回VOS_TRUE */
    for (i = 0; i < pstCellInfo->ucCellNum; i++)
    {
        if (pstCellInfo->ausCellId[i] == pstCampCell->astCellInfo[0].ulCellId)
        {
            return VOS_TRUE;
        }
    }

    /* 请求消息中CELL ID存在而且与当前驻留不同，返回VOS_FALSE */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetPlmnSearchSceneMsccRegReq
 功能描述  : 从MSCC模块的REG请求消息中获得搜网场景
 输入参数  : pstRegReq
 输出参数  : 无
 返 回 值  : NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : s00246516
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32 NAS_MMC_GetPlmnSearchSceneMsccRegReq(
    MSCC_MMC_REG_REQ_STRU               *pstRegReq
)
{
    /* 构造内部搜网消息，搜网场景构造逻辑 */
    if (VOS_TRUE == pstRegReq->bitOpCellInfo)
    {
        return NAS_MMC_PLMN_SEARCH_SCENE_REG_NCELL;
    }
    /* 进行指定优先级的注册 */
    else if (VOS_TRUE == pstRegReq->bitOpPrioClass)
    {
        /* 进行指定优先级为HPLMN的注册 */
        if (NAS_MSCC_PIF_PLMN_PRIORITY_HOME == pstRegReq->enPrioClass)
        {
            return NAS_MMC_PLMN_SEARCH_SCENE_REG_HPLMN;
        }
        /* 进行指定优先级为PREF的注册 */
        else if (NAS_MSCC_PIF_PLMN_PRIORITY_PREF == pstRegReq->enPrioClass)
        {
            return NAS_MMC_PLMN_SEARCH_SCENE_REG_PREF_PLMN;
        }
        else
        {
            return NAS_MMC_PLMN_SEARCH_SCENE_REG_ANY_PLMN;
        }
    }
    /* 异常保护按NAS_MMC_PLMN_SEARCH_SCENE_REG_ANY_PLMN处理 */
    else
    {
        return NAS_MMC_PLMN_SEARCH_SCENE_REG_ANY_PLMN;
    }
}

/* Added by s00246516 for L-C互操作项目, 2014-02-12, End */

/* Added by w00167002 for L-C互操作项目, 2014-2-19, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_Convert3GPP2RatType
 功能描述  : 将MSCC传过来的3GPP2类型转换为MML类型格式
 输入参数  : enMSCC3GPP2RatType      MSCC传过来的3GPP2类型
 输出参数  : *penMML3GPP2RatType    MML保存的3GPP2类型
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年2月19日
   作    者   : w00167002
   修改内容   : 新建函数
*****************************************************************************/
VOS_VOID   NAS_MMC_Convert3GPP2RatType(
    NAS_MSCC_PIF_3GPP2_RAT_TYPE_ENUM_UINT8   enMSCC3GPP2RatType,
    NAS_MML_3GPP2_RAT_TYPE_ENUM_UINT8  *penMML3GPP2RatType
)
{
    switch (enMSCC3GPP2RatType)
    {
        case NAS_MSCC_PIF_3GPP2_RAT_TYPE_CDMA1X:

            *penMML3GPP2RatType = NAS_MML_3GPP2_RAT_TYPE_CDMA1X;
            break;

        case NAS_MSCC_PIF_3GPP2_RAT_TYPE_HRPD:

            *penMML3GPP2RatType = NAS_MML_3GPP2_RAT_TYPE_HRPD;
            break;

        case NAS_MSCC_PIF_3GPP2_RAT_TYPE_BUTT:
            *penMML3GPP2RatType = NAS_MML_3GPP2_RAT_TYPE_BUTT;
            break;

        default:

            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ConvertRrcCoverTypeToNasFormat TYPE ERROR!!!");
            *penMML3GPP2RatType = NAS_MML_3GPP2_RAT_TYPE_BUTT;
            break;
    }

    return;
}


/* Added by w00167002 for L-C互操作项目, 2014-2-19, end */

/*****************************************************************************
 函 数 名  : NAS_MMC_IsSorTriggerSpecPlmnSrch_L1Main
 功能描述  : 判断是否SOR触发指定搜网而不是列表搜网
 输入参数  : VOS_UINT32
 输出参数  : VOS_TRUE : 需要发起指定搜网
             VOS_FALSE: 不需要发起指定搜网
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年05月16日
   作    者   : w00167002
   修改内容   : 新生成函数: DTS2014051602857:在SOR打开时候，如果CS注册失败达到4次，则等周期
                搜网定时器超时发起LIST搜网，如果当前仅有原有网络，则发起LAU,否则
                触发MM发起LAU;如果LIST搜后，发现有其他网络，则发起其他网络的搜网注册。
*****************************************************************************/
VOS_UINT32  NAS_MMC_IsSorTriggerAdditionalLau(VOS_VOID)
{
    NAS_MML_SOR_ADDITIONAL_LAU_STRU                        *pstAdditionalLau    = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCampInfo         = VOS_NULL_PTR;


    pstAdditionalLau    = NAS_MML_GetSorAdditionalLauCtx();
    pstCampInfo         = NAS_MML_GetCurrCampPlmnInfo();

    if ( VOS_FALSE == pstAdditionalLau->ucAdditionalLauFlag )
    {
        return VOS_FALSE;
    }

    /* 增强判断LAI是否改变 */
    if ( VOS_FALSE == NAS_MML_CompareLai(&(pstAdditionalLau->stLai),&(pstCampInfo->stLai)) )
    {
        return VOS_FALSE;
    }

    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        return VOS_FALSE;
    }

    /* 否则返回需要触发ADDITIONAL LAU */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccCurrServiceRelatedInfo
 功能描述  : 上报给MSCC当前的业务状态相关的信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年06月25日
   作    者   : b00269685
   修改内容   : 新生成函数
 2.日    期   : 2014年07月24日
   作    者   : b00269685
   修改内容   : Coverify清理
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccCurrServiceRelatedInfo(VOS_VOID)
{
    MSCC_MMC_SCELL_MEAS_REPORT_TYPE_UN   unMeasReportType;
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32  enMsccServiceState;

    PS_MEM_SET(((VOS_UINT8*)&unMeasReportType), 0, sizeof(MSCC_MMC_SCELL_MEAS_REPORT_TYPE_UN));

    unMeasReportType.ucMeasReportType |= NAS_MSCC_PIF_SCELL_MEAS_TYPE_RXLEV;

    /* 上报当前的系统消息，跟MSCC进行信息同步 */
    NAS_MMC_SndMsccSysInfo();

    /* 上报CAMP ON信息 */
    /* Modified by b00269685 for Coverify清理, 2014-7-24, begin */
    if (NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    }
    else
    {
        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
    }
    /* Modified by b00269685 for Coverify清理, 2014-7-24, end */

    /* 上报服务状态 */
    NAS_MMC_ConvertToMsccSrvStatus(NAS_MMC_GetCsServiceStatus(), &enMsccServiceState);
    NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_CS,  enMsccServiceState);

    NAS_MMC_ConvertToMsccSrvStatus(NAS_MMC_GetPsServiceStatus(), &enMsccServiceState);
    NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_PS,  enMsccServiceState);

    /* 上报注册状态 */
    NAS_MMC_SndMsccRegStatusInd(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MML_GetCsRegStatus());
    NAS_MMC_SndMsccRegStatusInd(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MML_GetPsRegStatus());

    /* 上报RSSI */
    NAS_MMC_SndMsccRssiInd(&unMeasReportType);

    return;
}


/* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-18, begin */


/*****************************************************************************
 函 数 名  : NAS_MMC_GetIndexOfFirstSelfLearningTypeElement
 功能描述  : 获取 DplmnList 中最后一个类型是预置类型的plmn的下标
 输入参数  :
             pulDestPlmnNum    - DPLMN/NPLMN list个数
             pstDestPlmnIdList - DPLMN/NPLMN list指针
 输出参数  : 无
 返 回 值  : ulIndex -- 数组下标
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年5月18日
   作    者   : c00318887
   修改内容   : for DPlmn扩容和优先接入HPLMN
 2.日    期   : 2015年11月3日
   作    者   : l00289540
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0 修改
*****************************************************************************/
VOS_UINT32  NAS_MMC_GetIndexOfFirstSelfLearningTypeElement(
    VOS_UINT16                                             *pulFirstPosition,
    VOS_UINT16                                              ulMaxAllowPlmnNum,
    VOS_UINT16                                              ulDestPlmnNum,
    NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU                  *pstDestPlmnIdList
)
{
    VOS_UINT32                    ulLoop  = 0;

    for (ulLoop = 0; ulLoop < ulDestPlmnNum; ulLoop++)
    {
        if (NAS_MMC_DPLMN_NPLMN_SELF_LEARING_TYPE == pstDestPlmnIdList[ulLoop].enType)
        {
            break;
        }
    }

    /* 有自学习类型 */
    if (ulLoop < ulDestPlmnNum)
    {
        *pulFirstPosition = (VOS_UINT16)ulLoop;
        return VOS_TRUE;
    }

    /* 没有自学习类型 数组没满 */
    if (ulMaxAllowPlmnNum - 1 >= ulDestPlmnNum)
    {
        *pulFirstPosition = ulDestPlmnNum;
        return VOS_TRUE;
    }

    /* 没有自学习类型, 数组满  */
    *pulFirstPosition = ulMaxAllowPlmnNum;

    return VOS_FALSE;
}
/* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-21, end */

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateDPlmnNPlmnList
 功能描述  : 更新DPLMNNPLMN列表
 输入参数  : pstCurrPlmnLai - 传入的当前注册网络的PLMN信息
             enNetType      - 接入技术
             enRegDomain    - 注册域
             pulDestPlmnNum - 更新DPLMN/NPLMN list个数
             pstDestPlmnIdList - 更新DPLMN/NPLMN list
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月11日
   作    者   : c00188733
   修改内容   : 新生成函数
 2.日    期   : 2015年5月18日
   作    者   : c00318887
   修改内容   : for DPlmn扩容和优先接入HPLMN
 3.日    期   : 2015年10月22日
   作    者   : l00289540
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0 修改
*****************************************************************************/
VOS_VOID  NAS_MMC_UpdateDPlmnNPlmnList(
    NAS_MML_LAI_STRU                                       *pstCurrLai,
    NAS_MMC_REG_DOMAIN_ENUM_UINT8                           enRegDomain,
    VOS_UINT16                                              ulMaxAllowPlmnNum,
    VOS_UINT16                                             *pulDestPlmnNum,
    NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU                  *pstDestPlmnIdList
)
{
    VOS_UINT32                                              i;
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    VOS_UINT16                                              usSimRat;

    /* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-21, begin */
    VOS_UINT16                                              usIndex;
    /* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-21, end */

    pstDPlmnNPlmnCfgInfo  = NAS_MMC_GetDPlmnNPlmnCfgInfo();
    usSimRat              = NAS_MML_INVALID_SIM_RAT;

    usSimRat = NAS_MMC_ConvertNetRatToSimRat(pstCurrLai->enCampPlmnNetRat);

    for (i = 0; i < *pulDestPlmnNum; i++)
    {
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstCurrLai->stPlmnId), &(pstDestPlmnIdList[i].stSimPlmnWithRat.stPlmnId)))
        {
            /* 如果PLMN相同，RAT也相同则不更新 */
            if ((usSimRat & pstDestPlmnIdList[i].stSimPlmnWithRat.usSimRat) == usSimRat)
            {
                return;
            }
            /*如果PLMN相同，RAT不同 */
            else
            {
                /* 是自学习类型,则仅更新RAT */
                /* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-21, begin */
                if (NAS_MMC_DPLMN_NPLMN_SELF_LEARING_TYPE == pstDestPlmnIdList[i].enType)
                {
                    pstDestPlmnIdList[i].stSimPlmnWithRat.usSimRat = usSimRat | pstDestPlmnIdList[i].stSimPlmnWithRat.usSimRat;
                    return;
                }
                /* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-21, end */
            }
        }
    }

    /* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-21, begin */
    if (VOS_FALSE == NAS_MMC_GetIndexOfFirstSelfLearningTypeElement(&usIndex, ulMaxAllowPlmnNum, *pulDestPlmnNum, pstDestPlmnIdList))
    {
        return;
    }

    /* 添加新记录 */
    if (*pulDestPlmnNum < ulMaxAllowPlmnNum )
    {
        (VOS_VOID)PS_MEM_MOVE(&pstDestPlmnIdList[usIndex + 1], &pstDestPlmnIdList[usIndex],
                               (*pulDestPlmnNum - usIndex) * sizeof(NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU));

        pstDestPlmnIdList[usIndex].stSimPlmnWithRat.stPlmnId.ulMcc    = pstCurrLai->stPlmnId.ulMcc;
        pstDestPlmnIdList[usIndex].stSimPlmnWithRat.stPlmnId.ulMnc    = pstCurrLai->stPlmnId.ulMnc;
        pstDestPlmnIdList[usIndex].stSimPlmnWithRat.usSimRat          = usSimRat;
        pstDestPlmnIdList[usIndex].enRegDomain                        = enRegDomain;
        pstDestPlmnIdList[usIndex].enType                             = NAS_MMC_DPLMN_NPLMN_SELF_LEARING_TYPE;
        (*pulDestPlmnNum)++;
    }
    else
    {
        (VOS_VOID)PS_MEM_MOVE(&pstDestPlmnIdList[usIndex + 1], &pstDestPlmnIdList[usIndex],
                               (ulMaxAllowPlmnNum - usIndex - 1) * sizeof(NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU));

        pstDestPlmnIdList[usIndex].stSimPlmnWithRat.stPlmnId.ulMcc    = pstCurrLai->stPlmnId.ulMcc;
        pstDestPlmnIdList[usIndex].stSimPlmnWithRat.stPlmnId.ulMnc    = pstCurrLai->stPlmnId.ulMnc;
        pstDestPlmnIdList[usIndex].stSimPlmnWithRat.usSimRat          = usSimRat;
        pstDestPlmnIdList[usIndex].enRegDomain                        = enRegDomain;
        pstDestPlmnIdList[usIndex].enType                             = NAS_MMC_DPLMN_NPLMN_SELF_LEARING_TYPE;
    }
    /* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-21, end */

    /* AP没有预置DPLMN信息，自学习的DPLMN后，也需要将Ehplmn更新到全局变量和NV中，
     * 以供其他modem判断通知给他的DPLMN是否可以使用
     */
    if (0 == pstDPlmnNPlmnCfgInfo->ucEHplmnNum)
    {
        NAS_MMC_UpdateEhplmnToDplmnNplmnCfgInfo();
    }


    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateDPlmnNPlmnList
 功能描述  : 删除DPLMNNPLMN列表
 输入参数  : pstCurrPlmnLai - 传入的当前注册网络的PLMN信息
             enNetType      - 接入技术
             enRegDomain    - 注册域
             pulDestPlmnNum - 删除DPLMN/NPLMN list个数
             pstDestPlmnIdList - 删除DPLMN/NPLMN list
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月11日
   作    者   : c00188733
   修改内容   : 新生成函数
2.日    期   : 2015年5月18日
  作    者   : c00318887
  修改内容   : for DPlmn扩容和优先接入HPLMN
*****************************************************************************/
VOS_VOID  NAS_MMC_DeleteDPlmnNPlmnList(
    NAS_MML_LAI_STRU                                       *pstCurrLai,
    NAS_MMC_REG_DOMAIN_ENUM_UINT8                           enRegDomain,
    VOS_UINT16                                             *pulDestPlmnNum,
    NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU                  *pstDestPlmnIdList
)
{
    VOS_UINT32                                              i;
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    VOS_UINT16                                              usSimRat;
    VOS_UINT16                                              usTmpSimRat;
    VOS_UINT32                                              ulIsDplmnType;

    pstDPlmnNPlmnCfgInfo     = NAS_MMC_GetDPlmnNPlmnCfgInfo();
    usSimRat                 = NAS_MML_INVALID_SIM_RAT;
    usTmpSimRat              = NAS_MML_INVALID_SIM_RAT;

    usSimRat = NAS_MMC_ConvertNetRatToSimRat(pstCurrLai->enCampPlmnNetRat);

    ulIsDplmnType = NAS_MMC_IsPlmnIdWithSimRatInSimPlmnWithRegDomainList(&(pstCurrLai->stPlmnId),
                                                                         usSimRat,
                                                                         pstDPlmnNPlmnCfgInfo->usDplmnListNum,
                                                                         pstDPlmnNPlmnCfgInfo->astDPlmnList);

    for (i = 0; i < *pulDestPlmnNum;)
    {
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstCurrLai->stPlmnId), &(pstDestPlmnIdList[i].stSimPlmnWithRat.stPlmnId)))
        {
            usTmpSimRat = pstDestPlmnIdList[i].stSimPlmnWithRat.usSimRat & ~usSimRat;

            /*如果PLMN相同，RAT也完全相同则删除这条记录*/
            if(usSimRat == pstDestPlmnIdList[i].stSimPlmnWithRat.usSimRat)
            {
                /* 删除的是预置的DPLMN，则更新usPresetDplmnNum */
                if ((VOS_TRUE == ulIsDplmnType)
                 && (NAS_MMC_DPLMN_NPLMN_PRESETTING_TYPE == pstDestPlmnIdList[i].enType))
                {
                    pstDPlmnNPlmnCfgInfo->usPresetDplmnNum--;
                }

                /* 要删除的不是最后一个时，把后面的列表全部向前移1位 */
                if ((i + 1) < *pulDestPlmnNum)
                {
                    (VOS_VOID)PS_MEM_MOVE(&pstDestPlmnIdList[i], &pstDestPlmnIdList[ i + 1 ],
                            ((*pulDestPlmnNum - i) - 1 ) * sizeof(NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU));
                }

                (*pulDestPlmnNum)--;

                continue;
            }
            /*如果PLMN相同，RAT仅是RAT集合中一个则删除这种制式*/
            else if((usSimRat & pstDestPlmnIdList[i].stSimPlmnWithRat.usSimRat) == usSimRat)
            {
                pstDestPlmnIdList[i].stSimPlmnWithRat.usSimRat = usTmpSimRat;
            }
            else
            {

            }
        }

        i++;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertApPresetRatToSimRat
 功能描述  : 将Ap 预置的DPLMN Rat转换为Sim Rat格式
 输入参数  : VOS_UINT16 usApPresetDplmnRat
 输出参数  : 无
 返 回 值  : VOS_UINT16 usSimRat 转换后的SIMRAT类型
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月26日
    作    者   : l00289540
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16  NAS_MMC_ConvertApPresetRatToSimRat(
    VOS_UINT16                          usApPresetDplmnRat
)
{
    VOS_UINT16                          usSimRat;

    switch (usApPresetDplmnRat)
    {
        case NAS_MML_AP_PRESET_RAT_GSM:
            usSimRat = NAS_MML_SIM_RAT_GSM;
            break;

        case NAS_MML_AP_PRESET_RAT_UTRN:
            usSimRat = NAS_MML_SIM_RAT_UTRN;
            break;

        case NAS_MML_AP_PRESET_RAT_UTRN_GSM:
            usSimRat = NAS_MML_SIM_UTRN_GSM_RAT;
            break;

        case NAS_MML_AP_PRESET_RAT_E_UTRN:
            usSimRat = NAS_MML_SIM_RAT_E_UTRN;
            break;

        case NAS_MML_AP_PRESET_RAT_E_UTRN_GSM:
            usSimRat = NAS_MML_SIM_E_UTRN_GSM_RAT;
            break;

        case NAS_MML_AP_PRESET_RAT_E_UTRN_UTRN:
            usSimRat = NAS_MML_SIM_E_UTRN_UTRN_RAT;
            break;

        case NAS_MML_AP_PRESET_RAT_ALL_SUPPORT:
            usSimRat = NAS_MML_SIM_UE_SUPPORT_RAT_SUPPORT_LTE;
            break;

        default:
            usSimRat = NAS_MML_INVALID_SIM_RAT;
            break;
    }

    return usSimRat;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertNetRatToSimRat
 功能描述  : 将网络RAT类型转换为SIM卡的RAT类型
 输入参数  :NAS_MML_NET_RAT_TYPE_ENUM_UINT8   enPlmnNetRat 需要转换的NetRAT类型
 输出参数  : 无
 返 回 值  : VOS_UINT16 usSimRat 转换后的SIMRAT类型
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年7月14日
   作    者   : c00188733
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT16  NAS_MMC_ConvertNetRatToSimRat(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enPlmnNetRat
)
{
    VOS_UINT16                          usSimRat;

    usSimRat = NAS_MML_INVALID_SIM_RAT;

    if (NAS_MML_NET_RAT_TYPE_LTE == enPlmnNetRat)
    {
        usSimRat = NAS_MML_SIM_RAT_E_UTRN;
    }
    else if (NAS_MML_NET_RAT_TYPE_WCDMA == enPlmnNetRat)
    {
        usSimRat = NAS_MML_SIM_RAT_UTRN;
    }
    else if (NAS_MML_NET_RAT_TYPE_GSM == enPlmnNetRat)
    {
        usSimRat = NAS_MML_SIM_RAT_GSM;
    }
    else
    {
        usSimRat = NAS_MML_INVALID_SIM_RAT;
    }

    return usSimRat;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsBcchPlmnIdWithRatInDestSimPlmnList
 功能描述  : 判断带接入技术PLMN ID是否在列表中
 输入参数  : pstBcchPlmnId:需要判断的PLMN ID
             usSimPlmnWithRatNum:列表中plmn id的个数
             pstSimPlmnWithRatList:plmn with rat列表
 输出参数  : 无
 返 回 值  : VOS_TRUE  : PLMN ID在列表中
             VOS_FALSE : PLMN ID不在列表中
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2014年11月8日
   作    者   : z00161729
   修改内容   : 开机搜网优化项目修改

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsBcchPlmnIdWithRatInDestSimPlmnList (
    NAS_MML_PLMN_WITH_RAT_STRU         *pstBcchPlmnIdWithRat,
    VOS_UINT16                          usSimPlmnWithRatNum,
    NAS_MML_SIM_PLMN_WITH_RAT_STRU     *pstSimPlmnWithRatList
)
{
    VOS_UINT32                          i;
    VOS_UINT16                          usBcchPlmnSimRat;

    usBcchPlmnSimRat = NAS_MMC_ConvertNetRatToSimRat(pstBcchPlmnIdWithRat->enRat);

    for ( i = 0; i < usSimPlmnWithRatNum; i++ )
    {
        if ( (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&pstBcchPlmnIdWithRat->stPlmnId,
                                                            &pstSimPlmnWithRatList[i].stPlmnId))
          && (usBcchPlmnSimRat == (pstSimPlmnWithRatList[i].usSimRat & usBcchPlmnSimRat)))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ComparePlmnIdWithRatWithUplmn
 功能描述  : 判断PLMN带接入技术是否是UPLMN
 输入参数  : pstPlmnIdWithRat:需要比较的PLMNID
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 与uplmn相同
             VOS_FALSE - 与uplmn不同
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月8日
   作    者   : z00161729
   修改内容   : 开机搜网优化项目修改
*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePlmnIdWithRatWithUplmn (
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnIdWithRat
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
        if (VOS_TRUE == NAS_MMC_IsBcchPlmnIdWithRatInDestSimPlmnList(pstPlmnIdWithRat,
                                                      pstUserPlmnList->ucUserPlmnNum,
                                                      pstUserPlmnList->astUserPlmnInfo))
        {
            return VOS_TRUE;
        }
    }
    else /* 表示(U)SIM卡中不存在UPLMN、OPLMN，使用PLMN Sel文件 */
    {
        pstSelPlmnList = NAS_MML_GetSimSelPlmnList();

        if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(&pstPlmnIdWithRat->stPlmnId,
                                                      pstSelPlmnList->ucSelPlmnNum,
                                                      pstSelPlmnList->astPlmnId))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ComparePlmnIdWithRatWithOplmn
 功能描述  : 判断带接入技术的PLMN是否是OPLMN
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
VOS_UINT32 NAS_MMC_ComparePlmnIdWithRatWithOplmn (
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnIdWithRat
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
        if (VOS_TRUE == NAS_MMC_IsBcchPlmnIdWithRatInDestSimPlmnList(pstPlmnIdWithRat,
                                                      pstOperPlmnList->usOperPlmnNum,
                                                      pstOperPlmnList->astOperPlmnInfo))
        {
            return VOS_TRUE;
        }
    }
    else /* 表示(U)SIM卡中不存在UPLMN、OPLMN，使用PLMN Sel文件 */
    {
        pstSelPlmnList = NAS_MML_GetSimSelPlmnList();

        if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(&pstPlmnIdWithRat->stPlmnId,
                                                      pstSelPlmnList->ucSelPlmnNum,
                                                      pstSelPlmnList->astPlmnId))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsPlmnIdWithSimRatInSimPlmnWithRegDomainList
 功能描述  : 判断PLMN ID是否在NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU格式网络列表中
 输入参数  : pstSrcPlmnId:需要判断的PLMN ID
             usSimRat    :接入技术
             ulDestPlmnNum:列表中plmn id的个数
             pstDestPlmnIdList:plmn列表
 输出参数  : 无
 返 回 值  : VOS_TRUE  : PLMN ID在列表中
             VOS_FALSE : PLMN ID不在列表中
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2014年11月8日
   作    者   : b00269685
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlmnIdWithSimRatInSimPlmnWithRegDomainList(
    NAS_MML_PLMN_ID_STRU                                   *pstPlmnId,
    VOS_UINT16                                              usSimRat,
    VOS_UINT32                                              ulDestPlmnNum,
    NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU                  *pstDestPlmnIdList
)
{
    VOS_UINT32                          i;

    for (i = 0; i < ulDestPlmnNum; i++)
    {
        if ((VOS_TRUE  == NAS_MML_CompareBcchPlmnwithSimPlmn(pstPlmnId, &(pstDestPlmnIdList[i].stSimPlmnWithRat.stPlmnId)))
         && ((usSimRat & pstDestPlmnIdList[i].stSimPlmnWithRat.usSimRat)  == usSimRat))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertSimRatToNetRat
 功能描述  : 将SIM卡的RAT类型转换为网络RAT类型，如果sim卡rat类型有多个按接入技术优先级返回第一个
 输入参数  : usSimRat - sim 卡rat
 输出参数  : 无
 返 回 值  : enPlmnNetRat - 转换后net rat
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月8日
   作    者   : z00161729
   修改内容   : 新生成函数
*****************************************************************************/
NAS_MML_NET_RAT_TYPE_ENUM_UINT8  NAS_MMC_ConvertSimRatToNetRat(
    VOS_UINT16                          usSimRat
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatPrio = VOS_NULL_PTR;
    VOS_UINT16                          usConvertedSimRat;
    VOS_UINT32                          i;

    pstRatPrio = NAS_MML_GetMsPrioRatList();

    for (i = 0; i < pstRatPrio->ucRatNum; i++)
    {
        usConvertedSimRat = NAS_MMC_ConvertNetRatToSimRat(pstRatPrio->aucRatPrio[i]);

        if (usConvertedSimRat == (usConvertedSimRat & usSimRat))
        {
            return pstRatPrio->aucRatPrio[i];
        }
    }

    return NAS_MML_NET_RAT_TYPE_BUTT;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_IsNetRatContainedInSimRat
 功能描述  : 判断SimRat是否包含当前SpecRat
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月30日
    作    者   : l00289540
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNetRatContainedInSimRat(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT16                          usSimRat
)
{
    VOS_UINT16                          usConvertedSimRat;

    usConvertedSimRat = NAS_MMC_ConvertNetRatToSimRat(enRat);

    if (usConvertedSimRat == (usConvertedSimRat & usSimRat))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsPlmnIdWithRatInSimPlmnWithRegDomainList
 功能描述  : 判断带接入技术的PLMN ID是否在NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU格式网络列表中
 输入参数  : pstSrcPlmnId:需要判断的PLMN ID
             ulDestPlmnNum:列表中plmn id的个数
             pstDestPlmnIdList:plmn列表
 输出参数  : 无
 返 回 值  : VOS_TRUE  : PLMN ID在列表中
             VOS_FALSE : PLMN ID不在列表中
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2014年10月30日
   作    者   : z00161729
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlmnIdWithRatInSimPlmnWithRegDomainList(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstSrcPlmnId,
    VOS_UINT32                                              ulDestPlmnNum,
    NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU                  *pstDestPlmnIdList
)
{
    VOS_UINT32                          i;
    VOS_UINT16                          usSrcPlmnSimRat;

    for ( i = 0; i < ulDestPlmnNum; i++ )
    {
        usSrcPlmnSimRat = NAS_MMC_ConvertNetRatToSimRat(pstSrcPlmnId->enRat);

        if ((VOS_TRUE  == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstSrcPlmnId->stPlmnId), &(pstDestPlmnIdList[i].stSimPlmnWithRat.stPlmnId)))
         && (usSrcPlmnSimRat == (usSrcPlmnSimRat & pstDestPlmnIdList[i].stSimPlmnWithRat.usSimRat)))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}






/*****************************************************************************
 函 数 名  : NAS_MMC_IsEnableLteTriggerPlmnSearch_ImsSwitchOnOrNotCsOnly
 功能描述  : IMS开关打开时或voice domain设成非cs only时，Enable LTE是否需要触发搜网
 输入参数  :
 返 回 值  : VOS_TRUE  : 需要搜网
             VOS_FALSE : 不需要搜网
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年02月12日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsEnableLteTriggerPlmnSearch_ImsSwitchOnOrNotCsOnly(VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;

    pstPrioRatList      = NAS_MML_GetMsPrioRatList();
    enFsmId             = NAS_MMC_GetCurrFsmId();

    /* 最高接入技术优先级不是LTE，不需要搜网 */
    if ((NAS_MML_NET_RAT_TYPE_LTE != pstPrioRatList->aucRatPrio[0]))
    {
        return VOS_FALSE;
    }

    /* 如果CS业务存在不需要搜网 */
    if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
    {
        return VOS_FALSE;
    }

    /* ON PLMN状态机时需要搜网 */
    if ((NAS_MMC_L1_STA_ON_PLMN == NAS_MMC_GetFsmTopState())
     && (NAS_MMC_FSM_L1_MAIN == enFsmId))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsPlmnValid
 功能描述  : 判断PLMN是否有效
 输入参数  : NAS_MSCC_PIF_PLMN_ID_STRU          *pstPlmnId
 输出参数  : 无
 返 回 值  : VOS_FALSE/VOS_TRUE
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年03月03日
   作    者   : y00307564
   修改内容   : Iteration 8新增
*****************************************************************************/
VOS_BOOL NAS_MMC_IsPlmnValid(
    NAS_MSCC_PIF_PLMN_ID_STRU          *pstPlmnId
)
{
    VOS_UINT32                          i;

    for (i=0; i<3; i++)
    {
        if ((((pstPlmnId->ulMcc >> (i*4)) & 0x0F) > 9)
         || ((((pstPlmnId->ulMnc >> (i*4)) & 0x0F) > 9) && (i != 2 ))
         || ((((pstPlmnId->ulMnc >> (i*4)) & 0x0F) > 9) && (((pstPlmnId->ulMnc >> (i*4)) & 0x0F) != 0x0F)))
        {
            /* PLMN ID?? */
            return VOS_FALSE;
        }
    }
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_PlmnId2Bcd
 功能描述  : 将PLMN转换为BCD码
 输入参数  : NAS_MSCC_PIF_PLMN_ID_STRU          *pstPlmnId
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年03月03日
   作    者   : y00307564
   修改内容   : Iteration 8新增
*****************************************************************************/
VOS_VOID NAS_MMC_PlmnId2Bcd(
    NAS_MSCC_PIF_PLMN_ID_STRU          *pstPlmnId
)
{
    VOS_UINT8                           ucI;
    VOS_UINT32                          ulTmp;
    VOS_UINT8                           aucTmp[4];

    ulTmp            = pstPlmnId->ulMcc;
    pstPlmnId->ulMcc = 0;
    for (ucI = 0 ;ucI < 3; ucI++)
    {
        aucTmp[ucI]     = ulTmp & 0x0f;
        ulTmp         >>=  8;
    }
    pstPlmnId->ulMcc = ((VOS_UINT32)aucTmp[0] << 8)
                      |((VOS_UINT32)aucTmp[1] << 4)
                      | aucTmp[2];

    ulTmp            = pstPlmnId->ulMnc;
    pstPlmnId->ulMnc = 0;
    for (ucI = 0; ucI < 3; ucI++)
    {
        aucTmp[ucI]     = ulTmp & 0x0f;
        ulTmp         >>=  8;
    }

    if (0xf == aucTmp[2])
    {
        pstPlmnId->ulMnc = ((VOS_UINT32)aucTmp[0] << 4)
                          |((VOS_UINT32)aucTmp[1] )
                          |0xf00;
    }
    else
    {
        pstPlmnId->ulMnc = ((VOS_UINT32)aucTmp[0] << 8)
                          |((VOS_UINT32)aucTmp[1] << 4)
                          | aucTmp[2];
    }
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_PlmnId2Bcd
 功能描述  : 将PLMN转换为NasStyle格式类型
 输入参数  : NAS_MSCC_PIF_PLMN_ID_STRU          *pstPlmnId
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年03月03日
   作    者   : y00307564
   修改内容   : Iteration 8新增
*****************************************************************************/
VOS_VOID NAS_MMC_PlmnId2NasStyle(NAS_MSCC_PIF_PLMN_ID_STRU *pstPlmnId)
{
    VOS_UINT8   ucI;
    VOS_UINT8   aucTmp[4];
    VOS_UINT32  ulTmp;

    ulTmp           = pstPlmnId->ulMcc;
    pstPlmnId->ulMcc  = 0;
    for (ucI = 0; ucI < 3; ucI++)
    {
        aucTmp[ucI]     = ulTmp & 0x0f;
        ulTmp         >>=  4;
    }
    pstPlmnId->ulMcc  =  aucTmp[2]
                     |((VOS_UINT32)aucTmp[1] << 8)
                     |((VOS_UINT32)aucTmp[0] << 16);

    ulTmp           = pstPlmnId->ulMnc;
    pstPlmnId->ulMnc  = 0;
    for (ucI = 0; ucI < 3; ucI++)
    {
        aucTmp[ucI]     = ulTmp & 0x0f;
        ulTmp         >>=  4;
    }

    if (0xf == aucTmp[2])
    {
        pstPlmnId->ulMnc =  aucTmp[1]
                         |((VOS_UINT32)aucTmp[0] << 8)
                         |0x0f0000;
    }
    else
    {
        pstPlmnId->ulMnc =   aucTmp[2]
                     |((VOS_UINT32)aucTmp[1] << 8)
                     |((VOS_UINT32)aucTmp[0] << 16);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetUpdateFileForPrefPlmn
 功能描述  : 根据Pref PLMN的操作,确定当前要更新的文件
 输出参数  : 需要更新的USIM文件
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年03月03日
   作    者   : y00307564
   修改内容   : Iteration 8新增
*****************************************************************************/
VOS_UINT16 NAS_MMC_GetUpdateFileForPrefPlmn(
    NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8                       enPrefPLMNType
)
{
    VOS_UINT16                          usUpdateFile;
    NAS_MML_SIM_TYPE_ENUM_UINT8         enSimType;

    enSimType       = NAS_MML_GetSimType();
    usUpdateFile    = 0;

    if (NAS_MSCC_UPLMN_INFO == enPrefPLMNType)
    {
        if (NAS_MML_SIM_TYPE_USIM == enSimType)
        {/* 3G USIM */
            usUpdateFile = USIMM_USIM_EFPLMNWACT_ID;
        }
        else if (NAS_MML_SIM_TYPE_SIM == enSimType)
        {/* 2G SIM */
            usUpdateFile = USIMM_GSM_EFPLMNWACT_ID;
        }
        else
        {
            usUpdateFile = USIMM_DEF_FILEID_BUTT;
        }
    }
    else if (NAS_MSCC_PLMNSEL_INFO == enPrefPLMNType)
    {
        usUpdateFile = USIMM_GSM_EFPLMNSEL_ID;
    }
    else if (NAS_MSCC_OPLMN_INFO == enPrefPLMNType)
    {
        if (NAS_MML_SIM_TYPE_USIM == enSimType)
        {/* 3G USIM */
            usUpdateFile = USIMM_USIM_EFOPLMNWACT_ID;
        }
        else if (NAS_MML_SIM_TYPE_SIM == enSimType)
        {/* 2G SIM */
            usUpdateFile = USIMM_GSM_EFOPLMNWACT_ID;
        }
        else
        {
            usUpdateFile = USIMM_DEF_FILEID_BUTT;
        }
    }
    else
    {
        if (NAS_MML_SIM_TYPE_USIM == enSimType)
        {/* 3G USIM */
            usUpdateFile = USIMM_USIM_EFHPLMNwACT_ID;
        }
        else if (NAS_MML_SIM_TYPE_SIM == enSimType)
        {/* 2G SIM */
            usUpdateFile = USIMM_GSM_EFHPLMNACT_ID;
        }
        else
        {
            usUpdateFile = USIMM_DEF_FILEID_BUTT;
        }
    }

    return usUpdateFile;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetWaitAsResumeIndTimerLen
 功能描述  : 获取Resume ind 定时器时长
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月24日
    作    者   : j00174725
    修改内容   : 新生成函数:接入层修改了与物理层之间的定时器
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetWaitAsResumeIndTimerLen(VOS_VOID)
{
    if (VOS_TRUE == NAS_MML_IsDsdsMultiModemMode())
    {
        return TI_NAS_MMC_DSDS_WAIT_AS_RESUME_IND_LEN;
    }

    return TI_NAS_MMC_WAIT_AS_RESUME_IND_LEN;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetWaitGUTAsRedirResumeIndTimerLen
 功能描述  : 获取GUT接入层重定向Resume ind 定时器时长
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月24日
    作    者   : j00174725
    修改内容   : 新生成函数:接入层修改了与物理层之间的定时器
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetWaitGUTAsRedirResumeIndTimerLen(VOS_VOID)
{
    if (VOS_TRUE == NAS_MML_IsDsdsMultiModemMode())
    {
        return TI_NAS_MMC_DSDS_INTER_SYS_GU_REDIR_WAIT_AS_RESUME_IND_LEN;
    }

    return TI_NAS_MMC_INTER_SYS_GU_REDIR_WAIT_AS_RESUME_IND_LEN;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetWaitAsOosResumeIndTimerLen
 功能描述  : 获取接入层OOS后Resume ind 定时器时长
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月24日
    作    者   : j00174725
    修改内容   : 新生成函数:接入层修改了与物理层之间的定时器
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetWaitAsOosResumeIndTimerLen(VOS_VOID)
{
    if (VOS_TRUE == NAS_MML_IsDsdsMultiModemMode())
    {
        return TI_NAS_MMC_DSDS_INTER_SYS_OOS_WAIT_AS_RESUME_IND_LEN;
    }

    return TI_NAS_MMC_INTER_SYS_OOS_WAIT_AS_RESUME_IND_LEN;
}




#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_IsDetachReqestDisableLte
 功能描述  : check detach请求是否需要disable LTE
 输出参数  : pstDetachReq -- detach请求
 返 回 值  : VOS_TRUE  -- 需要disable LTE
             VOS_FALSE -- 不需要disable LTE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年4月16日
   作    者   : y00245242
   修改内容   : iteration 13开发
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsDetachReqestDisableLte(
    NAS_MMC_DETACH_TYPE_ENUM_UINT32     enDetachType,
    NAS_MMC_DETACH_REASON_ENUM_UINT32   enDetachReason
)
{
    if (((NAS_MSCC_PIF_DETACH_REASON_USER_DETACH       == enDetachReason)
      || (NAS_MSCC_PIF_DETACH_REASON_SRV_DOMAIN_DETACH == enDetachReason))
     && (NAS_MSCC_PIF_DETACH_TYPE_GPRS            == enDetachType))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_BuildPlmnListInfoFromLmmAreaLostInd
 功能描述  : 根据GU的RRMM_AREA_LOST构造列表信息
 输入参数  : RRMM_AREA_LOST_IND_STRU                                *pstAreaLostInd
             NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnListInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_BuildPlmnListInfoFromLmmAreaLostInd(
    LMM_MMC_AREA_LOST_IND_STRU                             *pstAreaLostInd,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnListInfo
)
{
    RRC_PLMN_ID_LIST_STRU                                  *pstGuPlmnIdList = VOS_NULL_PTR;
    NAS_MMC_SEARCHED_TYPE_STRU                              stNasSearchedType;

    pstGuPlmnIdList = (RRC_PLMN_ID_LIST_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                   sizeof(RRC_PLMN_ID_LIST_STRU));

    if (VOS_NULL_PTR == pstGuPlmnIdList)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_BuildPlmnListInfoFromLmmAreaLostInd:ERROR: Memory Alloc Error");
        return;
    }

    PS_MEM_SET(&stNasSearchedType, 0, sizeof(NAS_MMC_SEARCHED_TYPE_STRU));
    stNasSearchedType.ucHistorySearchedFlg  = pstAreaLostInd->stSearchedType.ucHistorySearchedFlg;
    stNasSearchedType.ucPrefBandSearchedFlg = pstAreaLostInd->stSearchedType.ucPrefBandSearchedFlg;
    stNasSearchedType.ucSpecSearchedFlg     = pstAreaLostInd->stSearchedType.ucSpecSearchedFlg;

    NAS_MMC_InitSearchedPlmnListInfo(pstPlmnListInfo);

    /* 将搜网消息中携带的网络信息转换为内部消息中网络信息 */
    NAS_MMC_ConvertLmmPlmnIdListToGUFormat(&(pstAreaLostInd->stPlmnIdList),
                                           pstGuPlmnIdList);

    /* 根据area lost消息里带的已搜索类型和高低质量plmn更新内部选网消息 */
    NAS_MMC_UpdateSearchedPlmnListInfo(&stNasSearchedType, pstGuPlmnIdList, pstPlmnListInfo);

    PS_MEM_FREE(WUEPS_PID_MMC, pstGuPlmnIdList);

    return;
}

#endif


/*****************************************************************************
 函 数 名  : NAS_MMC_BuildPlmnListInfoFromGuAreaLostInd
 功能描述  : 根据GU的RRMM_AREA_LOST构造列表信息
 输入参数  : RRMM_AREA_LOST_IND_STRU                                *pstAreaLostInd
             NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnListInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_BuildPlmnListInfoFromGuAreaLostInd(
    RRMM_AREA_LOST_IND_STRU                                *pstAreaLostInd,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnListInfo
)
{
    NAS_MMC_SEARCHED_TYPE_STRU                              stNasSearchedType;

    PS_MEM_SET(&stNasSearchedType, 0, sizeof(NAS_MMC_SEARCHED_TYPE_STRU));
    stNasSearchedType.ucHistorySearchedFlg  = pstAreaLostInd->stSearchedType.ucHistorySearchedFlg;
    stNasSearchedType.ucPrefBandSearchedFlg = pstAreaLostInd->stSearchedType.ucPrefBandSearchedFlg;
    stNasSearchedType.ucSpecSearchedFlg     = pstAreaLostInd->stSearchedType.ucSpecSearchedFlg;

    NAS_MMC_InitSearchedPlmnListInfo(pstPlmnListInfo);

    /* 根据area lost消息里带的已搜索类型和高低质量plmn更新内部选网消息 */
    NAS_MMC_UpdateSearchedPlmnListInfo(&stNasSearchedType, &(pstAreaLostInd->PlmnIdList), pstPlmnListInfo);

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsOosPlmnSearchScene
 功能描述  : 是否为OOS搜网场景
 输入参数  : NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月30日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MMC_IsOosPlmnSearchScene(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene
)
{
    VOS_UINT8                                               ulRslt;

    switch(enPlmnSearchScene)
    {
        case NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED:
        case NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_HISTORY_PLMN_SEARCH:
        case NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_PREFBAND_PLMN_SEARCH:

            ulRslt = VOS_TRUE;
            break;

        default:

            ulRslt = VOS_FALSE;
            break;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsHistorySearchSupportInCurrPhase
 功能描述  : 当前阶段history是否支持
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月5日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MMC_IsHistorySearchSupportInCurrPhase(VOS_VOID)
{
    NAS_MMC_OOS_PLMN_SEARCH_STRATEGY_INFO_STRU             *pstOosPlmnSearchInfo    = VOS_NULL_PTR;
    NAS_MMC_OOS_PHASE_ENUM_UINT8                            enPhaseNum;
    VOS_UINT8                                               ucRslt;

    pstOosPlmnSearchInfo    = NAS_MMC_GetOosPlmnSearchStrategyInfo();
    enPhaseNum              = NAS_MMC_GetCurrOosSearchPhaseNum();
    ucRslt                  = VOS_FALSE;

    switch (enPhaseNum)
    {
        case NAS_MMC_OOS_PHASE_ONE:
            if (0 != pstOosPlmnSearchInfo->stPhaseOnePatternCfg.ucHistoryNum)
            {
                ucRslt = VOS_TRUE;
            }
            break;

        case NAS_MMC_OOS_PHASE_TWO:
            if (0 != pstOosPlmnSearchInfo->stPhaseTwoPatternCfg.ucHistoryNum)
            {
                ucRslt = VOS_TRUE;
            }
            break;

        default:
            ucRslt = VOS_FALSE;
            break;
    }

    return ucRslt;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertMsccHighPrioPlmnListToMmcPlmnListInfo
 功能描述  : 将MSCCPLMN搜索列表转换为MMC格式的PLMN列表信息
 输入参数  : ulMsccPlmnNum
             enRat
             pstMsccPlmnList
 输出参数  : pstMmcPlmnListInfo
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年4月3日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2015年6月1日
   作    者   : w00176964
   修改内容   : CDMA Iteration 12:修改接口

*****************************************************************************/
VOS_VOID NAS_MMC_ConvertMsccHighPrioPlmnListToMmcPlmnListInfo(
    NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU              *pstHighPrioPlmnInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstMmcPlmnListInfo
)
{
    VOS_UINT32                          i;

    if (VOS_NULL_PTR == pstHighPrioPlmnInfo)
    {
        return;
    }

    pstMmcPlmnListInfo[0].enRatType     = pstHighPrioPlmnInfo->enRat;
    pstMmcPlmnListInfo[0].enCoverType   = NAS_MMC_COVERAGE_TYPE_HIGH;

    pstMmcPlmnListInfo[0].ulHighPlmnNum = pstHighPrioPlmnInfo->ucHighPlmnNum;
    if (pstMmcPlmnListInfo[0].ulHighPlmnNum > NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM)
    {
        pstMmcPlmnListInfo[0].ulHighPlmnNum = NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM;
    }

    for (i = 0; i < (pstMmcPlmnListInfo[0].ulHighPlmnNum); i++)
    {
        pstMmcPlmnListInfo[0].astHighPlmnList[i].ulMcc = pstHighPrioPlmnInfo->astHighPlmnID[i].ulMcc;

        pstMmcPlmnListInfo[0].astHighPlmnList[i].ulMnc = pstHighPrioPlmnInfo->astHighPlmnID[i].ulMnc;
    }

    pstMmcPlmnListInfo[0].ulLowPlmnNum  = pstHighPrioPlmnInfo->ucLowPlmnNum;
    if (pstMmcPlmnListInfo[0].ulLowPlmnNum > NAS_MMC_INTRA_MAX_LOW_QUALITY_PLMN_NUM)
    {
        pstMmcPlmnListInfo[0].ulHighPlmnNum = NAS_MMC_INTRA_MAX_LOW_QUALITY_PLMN_NUM;
    }

    for (i = 0; i < (pstMmcPlmnListInfo[0].ulLowPlmnNum); i++)
    {
        pstMmcPlmnListInfo[0].astLowPlmnList[i].stPlmnId.ulMcc = pstHighPrioPlmnInfo->astLowPlmnID[i].ulMcc;

        pstMmcPlmnListInfo[0].astLowPlmnList[i].stPlmnId.ulMnc = pstHighPrioPlmnInfo->astLowPlmnID[i].ulMnc;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetPlmnSearchSceneMsccPlmnSrchReq
 功能描述  : 从MSCC模块的plmn search请求消息中获得搜网场景
 输入参数  : pstRegReq
 输出参数  : 无
 返 回 值  : NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月14日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32 NAS_MMC_GetPlmnSearchSceneMsccPlmnSrchReq(
    MSCC_MMC_PLMN_SEARCH_REQ_STRU      *pstPlmnSrchReq
)
{
    if (NAS_MSCC_PIF_ACQ_REASON_POWER_UP == pstPlmnSrchReq->enAcqReason)
    {
        return NAS_MMC_PLMN_SEARCH_SCENE_SWITCH_ON;
    }

    if (NAS_MSCC_PIF_ACQ_REASON_HIGH_PRIORITY == pstPlmnSrchReq->enAcqReason)
    {
        return NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_LTE_PLMN_SEARCH;
    }

    if (NAS_MSCC_PIF_ACQ_REASON_OTHER == pstPlmnSrchReq->enAcqReason)
    {
        return NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST;
    }

    return NAS_MMC_PLMN_SEARCH_SCENE_BUTT;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertMsccRatTypeToMml3GPP2RatType
 功能描述  : 将MSCC传过来的RAT类型转换为MML中3GPP2的类型格式
 输入参数  : enMsccRatType          MSCC传过来的RAT类型
 输出参数  : *penMml3GPP2RatType    MML保存的3GPP2类型
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年6月9日
   作    者   : w00176964
   修改内容   : 新建函数
*****************************************************************************/
VOS_VOID   NAS_MMC_ConvertMsccRatTypeToMml3GPP2RatType(
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    enMsccRatType,
    NAS_MML_3GPP2_RAT_TYPE_ENUM_UINT8                      *penMml3GPP2RatType
)
{
    switch (enMsccRatType)
    {
        case NAS_MSCC_PIF_NET_RAT_TYPE_1X:

            *penMml3GPP2RatType = NAS_MML_3GPP2_RAT_TYPE_CDMA1X;
            break;

        case NAS_MSCC_PIF_NET_RAT_TYPE_HRPD:

            *penMml3GPP2RatType = NAS_MML_3GPP2_RAT_TYPE_HRPD;
            break;

        default:

            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ConvertMsccRatTypeToMml3GPP2RatType TYPE ERROR!!!");
            *penMml3GPP2RatType = NAS_MML_3GPP2_RAT_TYPE_BUTT;
            break;
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsRatPrioChangeTriggerPlmnSrch
 功能描述  : 判断接入技术优先级变化是否需要发起高优先级搜网
 输入参数  : pstOldRatList --旧的接入技术列表
             pstNewRatList --新的接入技术列表
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要高优先级搜网
              VOS_FALSE:不需要高优先级搜网
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年7月15日
   作    者   : w00242748
   修改内容   : 新生成函数
 2.日    期   : 2015年8月6日
   作    者   : c00318887
   修改内容   : DTS2015041401965，syscfg设置只在增加接入技术且新增接入技术优先级高于当前接入技术才触发搜网
                例如: 4g -> 2g 4g(当前驻留4g，新增2g，2g接入技术优先级0 高于 4g 接入技术优先级 1，触发搜网)
                例如: 4g -> 4g 2g(当前驻留4g，新增2g，2g接入技术优先级1 低于 4g 接入技术优先级 0，不触发搜网)
*****************************************************************************/
VOS_UINT32  NAS_MMC_IsRatPrioChangeTriggerPlmnSrch(
    NAS_MSCC_PIF_RAT_PRIO_STRU         *pstOldRatList,
    NAS_MSCC_PIF_RAT_PRIO_STRU         *pstNewRatList
)
{
    VOS_UINT32                               ulCurrRatIndex;                         /* 当前接入技术在优先级里列表的index,0最高，2最低 */
    VOS_UINT8                                ucNewRatNum;                            /* 新增接入技术个数  */
    VOS_UINT8                                ucOldRatNum;                            /* 原有接入技术个数  */
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8    *pstNewRatPrio = VOS_NULL_PTR;           /* 新增接入优先级里列表 index表示优先级次序,0最高，2最低 */
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8    *pstOldRatPrio = VOS_NULL_PTR;           /* 原有接入优先级里列表 index表示优先级次序,0最高，2最低 */
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8          enCurrRat;
    VOS_UINT8                                ucOldRatIndex;
    VOS_UINT8                                ucNewRatIndex;


    /* 取得新增接入优先个数 */
    ucNewRatNum        = pstNewRatList->ucRatNum;

    /* 取得新增接入优先级列表 */
    pstNewRatPrio      = pstNewRatList->aucRatPrio;


    /* 取得当前的接入模式 */
    enCurrRat          = NAS_MML_GetCurrNetRatType();

    /* 取得原有的接入优先个数 */
    ucOldRatNum        = pstOldRatList->ucRatNum;

    /* 取得原有的接入优先级列表 */
    pstOldRatPrio      = pstOldRatList->aucRatPrio;

    if ( (0 == ucNewRatNum)
      || (0 == ucOldRatNum) )
    {
        return VOS_FALSE;
    }

    /* 当前接入技术在新的优先级列表里的index, 0最高，2最低  */
    ulCurrRatIndex = NAS_MML_GetRatIndexInPrioRatList(enCurrRat, pstNewRatList);

    /* 当前接入技术在新的优先级列表里没有，返回true */
    if (NAS_MML_INVALID_INDEX == ulCurrRatIndex)
    {
        return VOS_TRUE;
    }

    /* 触发依据:1、SysSet中新增了接入技术 */
    /*          2、新增的接入技术优先级高于当前驻留接入技术 */
    for (ucNewRatIndex = 0; ucNewRatIndex < ucNewRatNum; ucNewRatIndex++)
    {
        for (ucOldRatIndex = 0; ucOldRatIndex < ucOldRatNum; ucOldRatIndex++)
        {
            if (pstNewRatPrio[ucNewRatIndex] == pstOldRatPrio[ucOldRatIndex])
            {
                /* SysSet的某个接入技术在当前接入技术中 */
                break;
            }
        }

        /* 在原有接入技术列表中，不存在，表示有新增的  */
        if (ucOldRatIndex == ucOldRatNum)
        {
            /* 再判断新增接入技术在接入技术列表里的索引 是否小于 当前接入技术在接入技术列表里的索引 */
            if ((VOS_UINT32)ucNewRatIndex < ulCurrRatIndex)
            {
                return VOS_TRUE;
            }
        }

    }


    /* 默认不需要进行高优先级列表搜网 */
    return VOS_FALSE;
}


/* Added by c00318887 for 预置频点搜网优化, 2015-8-26, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_StartPlmnSearchPhaseOneTotalTimer
 功能描述  : 根据条件启动第一阶段搜网总时间控制定时器
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_TRUE: TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER 启动成功
             VOS_FALSE: TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER 启动失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月26日
    作    者   : c00318887
    修改内容   : 新建
  2.日    期   : 2015年10月21日
    作    者   : h00281185
    修改内容   : 架构改用 pstPhaseOneOosPlmnSearchPatternInfo, 取代 pstAvailTimerCfg/pstHistoryinfo
*****************************************************************************/
VOS_UINT32 NAS_MMC_StartPlmnSearchPhaseOneTotalTimer(VOS_VOID)
{
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU              *pstPhaseOneOosPlmnSearchPatternInfo  = VOS_NULL_PTR;


    pstPhaseOneOosPlmnSearchPatternInfo                    = NAS_MMC_GetPhaseOneOosPlmnSearchPatternInfo();

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_StartPlmnSearchPhaseOneTotalTimer entered.");

    /* 如果已经在搜网第二阶段，不启动 */
    if (NAS_MMC_OOS_PHASE_ONE != NAS_MMC_GetOosPhaseNum())
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_StartPlmnSearchPhaseOneTotalTimer WANRING: UE is in plmn search phaseII");

        return VOS_FALSE;
    }

    /* no rf ，不启动 */
    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_StartPlmnSearchPhaseOneTotalTimer:WARNING: no rf");

        return VOS_FALSE;
    }

    /* Timer Length 为0, 表示不须启动 定时器 */
    if (0 == pstPhaseOneOosPlmnSearchPatternInfo->usTotalTimerLen)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "pstPhaseOneOosPlmnSearchPatternInfo->usTotalTimerLen = 0, not start");

        return VOS_FALSE;
    }

     /* 第一阶段总时长 小于 第一阶段最小睡眠时长，不启动 */
    if ( pstPhaseOneOosPlmnSearchPatternInfo->usTotalTimerLen < pstPhaseOneOosPlmnSearchPatternInfo->usSleepTimerLen)
    {
        NAS_WARNING_LOG2(WUEPS_PID_MMC, "NAS_MMC_StartPlmnSearchPhaseOneTotalTimer:WARNING: PhaseOneTotalTimeLen=%d, historyFirstTimerLen=%d",
                        pstPhaseOneOosPlmnSearchPatternInfo->usTotalTimerLen, pstPhaseOneOosPlmnSearchPatternInfo->usSleepTimerLen);

        return VOS_FALSE;
    }

    if (VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER,
                                       (pstPhaseOneOosPlmnSearchPatternInfo->usTotalTimerLen) * NAS_MML_ONE_THOUSAND_MILLISECOND))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_StartPlmnSearchPhaseOneTotalTimer START SUCC.");
        return VOS_TRUE;
    }

    NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_StartPlmnSearchPhaseOneTotalTimer:info: START TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER IS FALSE");

    return VOS_FALSE;
}
/* Added by c00318887 for 预置频点搜网优化, 2015-8-26, end */

/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertRatTypeFromNasMsccToNasErr
 功能描述  : 将NAS_MSCC定义的RatType转化为Nas_Err定义的RatType值,因为Nas_Err还未支持1X&HRPD
 输入参数  : NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8
 输出参数  : 无
 返 回 值  : NAS_ERR_LOG_RATMODE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月30日
    作    者   : h00279575
    修改内容   : 新生成函数
*****************************************************************************/
NAS_ERR_LOG_RATMODE_ENUM_UINT8 NAS_MMC_ConvertRatTypeFromNasMsccToNasErr (
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8 msccRatType
)
{
    NAS_ERR_LOG_RATMODE_ENUM_UINT8 errRatType;
    switch (msccRatType)
    {
        case NAS_MSCC_PIF_NET_RAT_TYPE_GSM:           /* GSM接入技术 */
            errRatType = NAS_ERR_LOG_RATMODE_GSM;
            break;
        case NAS_MSCC_PIF_NET_RAT_TYPE_WCDMA:         /* WCDMA接入技术 */
            errRatType = NAS_ERR_LOG_RATMODE_WCDMA;
            break;
        case NAS_MSCC_PIF_NET_RAT_TYPE_LTE:           /* LTE接入技术 */
            errRatType = NAS_ERR_LOG_RATMODE_LTE;
            break;
        default:
            NAS_TRACE_HIGH("NAS_MMC_ConvertRatTypeFromNasMsccToNasErr: Convert rat(%d) to BUTT", msccRatType);
            errRatType = NAS_ERR_LOG_RATMODE_BUTT;
            break;
    }

    return errRatType;
}
#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 函 数 名  : NAS_MMC_RecordFftSrchMccInfo
 功能描述  : 将FFT搜索MCC的结果写入CHR缓存
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月30日
    作    者   : h00279575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_RecordFftSrchMccInfo( VOS_VOID )
{
    NAS_MML_ERRLOG_FFT_SRCH_INFO_STRU          *pstGeoSrchInfo = VOS_NULL_PTR;
    NAS_ERR_LOG_FFT_SRCH_MCC_PROC_INFO_STRU     stProcInfoEvent;
    VOS_UINT32                                  ulIsLogNeedRecord;
    VOS_UINT32                                  ulLength;
    VOS_UINT32                                  ulResult;
    VOS_UINT16                                  usLevel;

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel             = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_FFT_SRCH_MCC_INFO);
    ulIsLogNeedRecord   = NAS_MML_IsErrLogNeedRecord(usLevel);

    /* NV配置不需要记录 */
    if (VOS_FALSE == ulIsLogNeedRecord)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RecordFftSrchMccInfo,ERROR:log nv disable or low level");
        return;
    }

    NAS_TRACE_HIGH("NAS_MMC_RecordFftSrchMccInfo(): recording ");

    ulLength = sizeof(NAS_ERR_LOG_FFT_SRCH_MCC_PROC_INFO_STRU);

    /* 填充本地记录信息 */
    PS_MEM_SET(&stProcInfoEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stProcInfoEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_MMC),
                                      NAS_ERR_LOG_ALM_FFT_SRCH_MCC_INFO,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    pstGeoSrchInfo = NAS_MML_GetErrLogFftSrchInfoAddr();
    stProcInfoEvent.ulSrchStartSlice  = pstGeoSrchInfo->ulSrchStartSlice;
    stProcInfoEvent.ulSrchFinishSlice = pstGeoSrchInfo->ulSrchFinishSlice;

    /* 转化GetGeo的搜索MCC结果，成功还是失败，以及失败的原因 */
    if (NAS_MMC_GET_GEO_SUCCESS == pstGeoSrchInfo->ucSrchRslt)
    {
        stProcInfoEvent.ucSrchRslt  = VOS_TRUE;
        stProcInfoEvent.ucFailCause = 0;

        /* 转化MCC的接入技术制式 */
        stProcInfoEvent.enMccRatType = NAS_MMC_ConvertRatTypeFromNasMsccToNasErr(pstGeoSrchInfo->enMccRatType);

    }
    else
    {
        stProcInfoEvent.ucSrchRslt   = VOS_FALSE;
        stProcInfoEvent.ucFailCause  = pstGeoSrchInfo->ucSrchRslt;

        /* 未找到MCC，初始化当前制式为默认值 */
        stProcInfoEvent.enMccRatType = NAS_ERR_LOG_RATMODE_BUTT;
    }


    /* 记录CSS Multi Band Scan的结果 */
    stProcInfoEvent.stMultiBandScanInfo.ucResult                = (VOS_UINT8)pstGeoSrchInfo->stCssBandScanInfo.enResult;
    stProcInfoEvent.stMultiBandScanInfo.ulBandScanStartSlice    = pstGeoSrchInfo->stCssBandScanInfo.ulBandScanStartSlice;
    stProcInfoEvent.stMultiBandScanInfo.ulBandScanFinishSlice   = pstGeoSrchInfo->stCssBandScanInfo.ulBandScanFinishSlice;
    stProcInfoEvent.stMultiBandScanInfo.ucGsmCoverageType       = (VOS_UINT8)pstGeoSrchInfo->stCssBandScanInfo.enGsmCoverageType;
    stProcInfoEvent.stMultiBandScanInfo.ucLteCoverageType       = (VOS_UINT8)pstGeoSrchInfo->stCssBandScanInfo.enLteCoverageType;
    stProcInfoEvent.stMultiBandScanInfo.ucUmtsFddCoverageType   = (VOS_UINT8)pstGeoSrchInfo->stCssBandScanInfo.enUmtsFddCoverageType;

    /* 清空的FFT搜索MCC全局变量信息 */
    NAS_MML_InitErrLogFftSrchInfo();

    /*
       将异常信息写入Buffer中
       实际写入的字符数与需要写入的不等则打印异常
     */
    ulResult = NAS_MML_PutErrLogRingBuf((VOS_CHAR *)&stProcInfoEvent, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RecordFftSrchMccInfo(): Push buffer error.");
    }

    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_FFT_SRCH_MCC_INFO,
                           WUEPS_PID_MMC,
                           (VOS_UINT8 *)&stProcInfoEvent,
                           sizeof(stProcInfoEvent));

    return;
}
#endif
/*****************************************************************************
 函 数 名  : NAS_MMC_ModifyForbiddenFlg_HplmnRegisterRej
 功能描述  : 在hplmn上注册被拒时，需要修改转发的系统消息中的forbidden flag.
 输入参数  : ulInForbiddenFlg       -- 输入的 forbidden flag
             ulUserSrchFlg          -- 是否手动模式
             enRat                  -- 接入及时
             enRegCnDomain          -- PS /cs 域
 输出参数  : 无
 返 回 值  : ulOutForbiddenFlg      -- 修改后的forbidden flag
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月16日
    作    者   : c00318887
    修改内容   : DTS2015061609864
*****************************************************************************/
VOS_UINT32  NAS_MMC_ModifyForbiddenFlg_HplmnRegisterRej(
    VOS_UINT32                          ulInForbiddenFlg,
    VOS_UINT32                          ulUserSrchFlg,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    NAS_MMC_REG_DOMAIN_ENUM_UINT8       enRegCnDomain
)
{
    VOS_UINT32                          ulOutForbiddenFlg;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsRegCause      = NAS_MML_REG_FAIL_CAUSE_NULL;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsRegCause      = NAS_MML_REG_FAIL_CAUSE_NULL;
    VOS_UINT8                           ucHplmnRegisterCtrlFlg;

    ulOutForbiddenFlg                   = ulInForbiddenFlg;

    /* 手动搜模式不修改 */
    if (VOS_TRUE == ulUserSrchFlg)
    {      
        NAS_NORMAL_LOG1(WUEPS_PID_MMC, 
                        "NAS_MMC_ModifyForbiddenFlg_HplmnRegisterRej: ulUserSrchFlg = ",
                        ulUserSrchFlg);
        return ulOutForbiddenFlg;
    }

    ucHplmnRegisterCtrlFlg              = NAS_MML_GetHplmnRegisterCtrlFlg();

    NAS_MMC_GetDomainRegStatusInRegInfoList(NAS_MML_GetCurrCampPlmnId(),
                                            enRat,
                                            &enCsRegCause,
                                            &enPsRegCause);

    NAS_NORMAL_LOG3(WUEPS_PID_MMC, 
                    "NAS_MMC_ModifyForbiddenFlg_HplmnRegisterRej: ucHplmnRegisterCtrlFlg, enCsRegCause and enPsRegCause ",
                    ucHplmnRegisterCtrlFlg,
                    enCsRegCause,
                    enPsRegCause);

    if (VOS_FALSE == NAS_MMC_GetHPlmnSpecDomainAccessCapa(enRegCnDomain))
    {
        if (MMCMM_NO_FORBIDDEN == ulInForbiddenFlg)
        {
            ulOutForbiddenFlg           = MMCMM_FORBIDDEN_PLMN;
        }

        if ( (NAS_MML_NET_RAT_TYPE_WCDMA == enRat)
          && (VOS_TRUE                   == ucHplmnRegisterCtrlFlg))
        {
            ulOutForbiddenFlg           &= (~MMCMM_FORBIDDEN_PLMN);
        }
    }

    if (NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN == enPsRegCause)
    {
        /* 在Hplmn上PS注册被#14拒后，非E5时，不再发起PS attach, E5时，允许循环发起PS attach */
        if (MMCMM_NO_FORBIDDEN == ulInForbiddenFlg)
        {
            ulOutForbiddenFlg           |= MMCMM_FORBIDDEN_PLMN_FOR_GPRS;
        }

        if ( (NAS_MML_NET_RAT_TYPE_WCDMA == enRat)
          && (VOS_TRUE                   == ucHplmnRegisterCtrlFlg))
        {
            ulOutForbiddenFlg           &= (~MMCMM_FORBIDDEN_PLMN_FOR_GPRS);
        }
    }

    return ulOutForbiddenFlg;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetMmssLteUnavailableReasonByDetachReason
 功能描述  : 通过detach原因获取LTE不可用的原因
 输入参数  : enDetachReason---detach 原因值
 输出参数  : 无
 返 回 值  : MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月20日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_ENUM_UINT8 NAS_MMC_GetMmssLteUnavailableReasonByDetachReason (
    NAS_MMC_DETACH_REASON_ENUM_UINT32   enDetachReason
)
{
    MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_ENUM_UINT8          enReason;

    switch (enDetachReason)
    {
        case NAS_MSCC_PIF_DETACH_REASON_USER_DETACH:
            enReason = MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_USER_DETACH;
            break;

        case NAS_MSCC_PIF_DETACH_REASON_RAT_OR_BAND_DETACH:
            enReason = MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_RAT_OR_BAND_DETACH;
            break;

        case NAS_MSCC_PIF_DETACH_REASON_SRV_DOMAIN_DETACH:
            enReason = MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_SRV_DOMAIN_DETACH;
            break;

        default:
            enReason = MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_BUTT;
            break;
    }

    return enReason;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertToMmlSessionType
 功能描述  : 把MMC的Session type 转换MML的类型
 输入参数  :
 输出参数  :
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月27日
    作    者   : j00174725
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_ConvertToMmlSessionType(
    RRC_NAS_SESSION_TYPE_ENUM_UINT8   enMmSessionType,
    NAS_MML_SESSION_TYPE_ENUM_UINT8  *penMmlSessionType
)
{
    switch(enMmSessionType)
    {
        case RRC_NAS_SESSION_TYPE_CS_MO_NORMAL_CALL:
            *penMmlSessionType = NAS_MML_SESSION_TYPE_CS_MO_NORMAL_CALL;
            break;

        case RRC_NAS_SESSION_TYPE_CS_MO_EMERGENCY_CALL:
            *penMmlSessionType = NAS_MML_SESSION_TYPE_CS_MO_EMERGENCY_CALL;
            break;

        case RRC_NAS_SESSION_TYPE_CS_MO_SS:
            *penMmlSessionType = NAS_MML_SESSION_TYPE_CS_MO_SS;
            break;

        case RRC_NAS_SESSION_TYPE_CS_MO_SMS:
            *penMmlSessionType = NAS_MML_SESSION_TYPE_CS_MO_SMS;
            break;

        default:
            *penMmlSessionType = NAS_MML_SESSION_TYPE_BUTT;
            break;
    }

    return;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



