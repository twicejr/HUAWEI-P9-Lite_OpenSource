/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmlCtx.c
  版 本 号   : 初稿
  作    者   : zhoujun 40661
  生成日期   : 2011年6月29日
  最近修改   : 2011年6月29日
  功能描述   : MML_CTX的全局变量管理以及对外提供API接口
  函数列表   :
  修改历史   :
  1.日    期   : 2011年6月29日
    作    者   : zhoujun 40661
    修改内容   : 创建文件

****************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "PsLib.h"

#include "PsCommonDef.h"
#include "NasMmlCtx.h"
#include "NasComm.h"
#include "NasMmlLib.h"
#include "NasMmcSndLmm.h"

#if (FEATURE_ON == FEATURE_PTM)
#include "NasErrorLog.h"
#endif
#include "GmmExt.h"
#include "MM_Ext.h"

#include "NasUsimmApi.h"

#include "NasUtranCtrlCtx.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
  2 常量定义
*****************************************************************************/

/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define THIS_FILE_ID PS_FILE_ID_NASMML_CTX_C
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
/* 保存三个模块共用的CTX */
NAS_MML_CTX_STRU                        g_stNasMmlCtx;

extern NAS_MNTN_MM_INFO_STRU            g_stNasMntnErrorLogMm;

/*****************************************************************************
  6 函数定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
 函 数 名  : NAS_MML_GetMmlCtx
 功能描述  : 获取当前MML的CTX
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前MML的CTX
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月9日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_CTX_STRU*  NAS_MML_GetMmlCtx( VOS_VOID )
{
    return &(g_stNasMmlCtx);
}

/* Added by s00261364 for V3R360_eCall项目, 2014-4-28, begin */
/*****************************************************************************
 函 数 名  : NAS_MML_InitCallModeInfoCtx
 功能描述  : 初始化MML_CTX中SIM 状态相关信息
 输入参数  : 无
 输出参数  : pstSimStatusInfo:SIM卡状态相关信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年4月28日
   作    者   : s00261364
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_InitCallModeInfoCtx(
    NAS_MML_CALL_MODE_ENUM_UINT8        *penCallMode
)
{
    *penCallMode = NAS_MML_CALL_MODE_BUTT;
}


/* Added by s00261364 for V3R360_eCall项目, 2014-4-28, end */

/*****************************************************************************
 函 数 名  : NAS_MML_InitSimStatusInfoCtx
 功能描述  : 初始化MML_CTX中SIM 状态相关信息
 输入参数  : 无
 输出参数  : pstSimStatusInfo:SIM卡状态相关信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月11日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数
 2.日    期   : 2015年12月10日
   作    者   : z00359541
   修改内容   : DTS2015111208926 开关机时清除IMSI REFRESH状态
*****************************************************************************/
VOS_VOID  NAS_MML_InitSimStatusInfoCtx(
    NAS_MML_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    NAS_MML_SIM_STATUS_STRU             *pstSimStatusInfo
)
{
    if (NAS_MML_INIT_CTX_STARTUP == enInitType)
    {
        pstSimStatusInfo->ucSimPresentStatus  = VOS_FALSE;
        pstSimStatusInfo->enSimType           = NAS_MML_SIM_TYPE_BUTT;
    }

    pstSimStatusInfo->ucSimCsRegStatus    = VOS_FALSE;
    pstSimStatusInfo->ucSimPsRegStatus    = VOS_FALSE;
    pstSimStatusInfo->enCsUpdateStatus    = NAS_MML_LOCATION_UPDATE_STATUS_BUTT;
    pstSimStatusInfo->enPsUpdateStatus    = NAS_MML_ROUTING_UPDATE_STATUS_BUTT;
    /* IMSI REFRESH状态在开关机时都会清除 */
    pstSimStatusInfo->ucImsiRefreshStatus = VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MML_InitSimMsIdentityInfoCtx
 功能描述  : 初始化MML_CTX中SIM卡MS相关信息
 输入参数  : 无
 输出参数  : pstMsIdentity:SIM卡MS相关信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月11日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_InitSimMsIdentityInfoCtx(
    NAS_MML_SIM_MS_IDENTITY_STRU       *pstMsIdentity
)
{
    VOS_UINT32                          i;

    /* IMSI内容 */
    for ( i = 0 ; i < NAS_MML_MAX_IMSI_LEN ; i++ )
    {
        pstMsIdentity->aucImsi[i]           = NAS_MML_IMSI_INVALID;
    }

    /* PTMSI内容 */
    for ( i = 0 ; i < NAS_MML_MAX_PTMSI_LEN ; i++ )
    {
        pstMsIdentity->aucPtmsi[i]          = NAS_MML_PTMSI_INVALID;
    }

    /* PTMSI Signature内容 */
    for ( i = 0 ; i < NAS_MML_MAX_PTMSI_SIGNATURE_LEN ; i++ )
    {
        pstMsIdentity->aucPtmsiSignature[i] = NAS_MML_PTMSI_SIGNATURE_INVALID;
    }

    /* Tmsi内容 */
    for ( i = 0 ; i < NAS_MML_MAX_TMSI_LEN ; i++ )
    {
        pstMsIdentity->aucTmsi[i] = NAS_MML_TMSI_INVALID;
    }

    pstMsIdentity->enUeOperMode     = NAS_MML_SIM_UE_OPER_MODE_BUTT;
}

/*****************************************************************************
 函 数 名  : NAS_MML_InitUeIdPtmisInvalid
 功能描述  : 初始化MML_CTX中PTMSI为无效值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : huwen 44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_InitUeIdPtmisInvalid(VOS_VOID)
{
    VOS_UINT32                          i;

    /* PTMSI内容 */
    for ( i = 0 ; i < NAS_MML_MAX_PTMSI_LEN ; i++ )
    {
        NAS_MML_GetMmlCtx()->stSimInfo.stMsIdentity.aucPtmsi[i] = NAS_MML_PTMSI_INVALID;
    }

}

/*****************************************************************************
 函 数 名  : NAS_MML_InitUeIdPtmsiSignatureInvalid
 功能描述  : 初始化MML_CTX中PTMSI SIGNATURE为无效值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : huwen 44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_InitUeIdPtmsiSignatureInvalid(VOS_VOID)
{
    VOS_UINT32                          i;

    /* PTMSI SIGNATURE内容 */
    for ( i = 0 ; i < NAS_MML_MAX_PTMSI_SIGNATURE_LEN ; i++ )
    {
        NAS_MML_GetMmlCtx()->stSimInfo.stMsIdentity.aucPtmsiSignature[i] = NAS_MML_PTMSI_SIGNATURE_INVALID;
    }

}

/*****************************************************************************
 函 数 名  : NAS_MML_InitUeIdTmsiInvalid
 功能描述  : 初始化MML_CTX中TMSI为无效值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : huwen 44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_InitUeIdTmsiInvalid(VOS_VOID)
{
    VOS_UINT32                          i;

    /* PTMSI SIGNATURE内容 */
    for ( i = 0 ; i < NAS_MML_MAX_TMSI_LEN ; i++ )
    {
        NAS_MML_GetMmlCtx()->stSimInfo.stMsIdentity.aucTmsi[i] = NAS_MML_TMSI_INVALID;
    }

}

/*****************************************************************************
 函 数 名  : NAS_MML_InitSimPsSecurityCtx
 功能描述  : 初始化MML_CTX中SIM卡PS域的安全参数相关信息
 输入参数  : 无
 输出参数  : pstPsSecurity:SIM卡PS域的安全参数相关信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月11日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_InitSimPsSecurityCtx(
    NAS_MML_SIM_PS_SECURITY_INFO_STRU   *pstPsSecurity
)
{
    VOS_UINT32                          i;

    /* CKSN */
    pstPsSecurity->ucCKSN               = NAS_MML_CKSN_INVALID;

    /* GSM KC */
    for ( i = 0 ; i < NAS_MML_GSM_KC_LEN ; i++ )
    {
        pstPsSecurity->aucGsmKc[i]      = NAS_MML_GSMKC_INVALID;
    }

    /* UMTS CK */
    for ( i = 0 ; i < NAS_MML_UMTS_CK_LEN ; i++ )
    {
        pstPsSecurity->aucUmtsCk[i]      = NAS_MML_CK_INVALID;
    }

    /* UMTS IK */
    for ( i = 0 ; i < NAS_MML_UMTS_IK_LEN ; i++ )
    {
        pstPsSecurity->aucUmtsIk[i]      = NAS_MML_IK_INVALID;
    }
}


/*****************************************************************************
 函 数 名  : NAS_MML_InitPsSecurityGsmKcInvalid
 功能描述  : 初始化MML_CTX中PS域的安全参数中的GSM KC为无效值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : huwen 44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_InitPsSecurityGsmKcInvalid(VOS_VOID)
{
    VOS_UINT32                          i;

    /* GSM KC内容无效 */
    for ( i = 0 ; i < NAS_MML_GSM_KC_LEN ; i++ )
    {
        NAS_MML_GetMmlCtx()->stSimInfo.stPsSecurity.aucGsmKc[i] = NAS_MML_GSMKC_INVALID;
    }

}

/*****************************************************************************
 函 数 名  : NAS_MML_InitPsSecurityUmtsCkInvalid
 功能描述  : 初始化MML_CTX中PS域的安全参数中的UMTS CK为无效值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : huwen 44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_InitPsSecurityUmtsCkInvalid(VOS_VOID)
{
    VOS_UINT32                          i;

    /* UMTS CK内容无效 */
    for ( i = 0 ; i < NAS_MML_UMTS_CK_LEN ; i++ )
    {
        NAS_MML_GetMmlCtx()->stSimInfo.stPsSecurity.aucUmtsCk[i] = NAS_MML_CK_INVALID;
    }

}

/*****************************************************************************
 函 数 名  : NAS_MML_InitPsSecurityUmtsIkInvalid
 功能描述  : 初始化MML_CTX中PS域的安全参数中的UMTS IK为无效值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : huwen 44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_InitPsSecurityUmtsIkInvalid(VOS_VOID)
{
    VOS_UINT32                          i;

    /* UMTS CK内容无效 */
    for ( i = 0 ; i < NAS_MML_UMTS_IK_LEN ; i++ )
    {
        NAS_MML_GetMmlCtx()->stSimInfo.stPsSecurity.aucUmtsIk[i] = NAS_MML_IK_INVALID;
    }

}


/*****************************************************************************
 函 数 名  : NAS_MML_InitCsSecurityGsmKcInvalid
 功能描述  : 初始化MML_CTX中CS域的安全参数中的GSM KC为无效值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : huwen 44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_InitCsSecurityGsmKcInvalid(VOS_VOID)
{
    VOS_UINT32                          i;

    /* GSM KC内容无效 */
    for ( i = 0 ; i < NAS_MML_GSM_KC_LEN ; i++ )
    {
        NAS_MML_GetMmlCtx()->stSimInfo.stCsSecurity.aucGsmKc[i] = NAS_MML_GSMKC_INVALID;
    }

}

/*****************************************************************************
 函 数 名  : NAS_MML_InitCsSecurityUmtsCkInvalid
 功能描述  : 初始化MML_CTX中CS域的安全参数中的UMTS CK为无效值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : huwen 44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_InitCsSecurityUmtsCkInvalid(VOS_VOID)
{
    VOS_UINT32                          i;

    /* UMTS CK内容无效 */
    for ( i = 0 ; i < NAS_MML_UMTS_CK_LEN ; i++ )
    {
        NAS_MML_GetMmlCtx()->stSimInfo.stCsSecurity.aucUmtsCk[i] = NAS_MML_CK_INVALID;
    }

}

/*****************************************************************************
 函 数 名  : NAS_MML_InitCsSecurityUmtsIkInvalid
 功能描述  : 初始化MML_CTX中PS域的安全参数中的UMTS IK为无效值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : huwen 44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_InitCsSecurityUmtsIkInvalid(VOS_VOID)
{
    VOS_UINT32                          i;

    /* UMTS CK内容无效 */
    for ( i = 0 ; i < NAS_MML_UMTS_IK_LEN ; i++ )
    {
        NAS_MML_GetMmlCtx()->stSimInfo.stCsSecurity.aucUmtsIk[i] = NAS_MML_IK_INVALID;
    }

}

/*****************************************************************************
 函 数 名  : NAS_MML_InitSimCsSecurityCtx
 功能描述  : 初始化MML_CTX中SIM卡CS域的安全参数相关信息
 输入参数  : 无
 输出参数  : pstCsSecurity:SIM卡CS域的安全参数相关信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月11日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_InitSimCsSecurityCtx(
    NAS_MML_SIM_CS_SECURITY_INFO_STRU   *pstCsSecurity
)
{
    VOS_UINT32                          i;

    /* CKSN */
    pstCsSecurity->ucCKSN               = NAS_MML_CKSN_INVALID;

    /* GSM KC */
    for ( i = 0 ; i < NAS_MML_GSM_KC_LEN ; i++ )
    {
        pstCsSecurity->aucGsmKc[i]      = NAS_MML_GSMKC_INVALID;
    }

    /* UMTS CK */
    for ( i = 0 ; i < NAS_MML_UMTS_CK_LEN ; i++ )
    {
        pstCsSecurity->aucUmtsCk[i]      = NAS_MML_CK_INVALID;
    }

    /* UMTS IK */
    for ( i = 0 ; i < NAS_MML_UMTS_IK_LEN ; i++ )
    {
        pstCsSecurity->aucUmtsIk[i]      = NAS_MML_IK_INVALID;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MML_InitSimEhPlmnInfo
 功能描述  : 初始化MML_CTX中SIM卡EHPLMN信息
 输入参数  : 无
 输出参数  : pstEhPlmnInfo:EHPLMN信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月11日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数
 2.日    期   : 2011年11月30日
   作    者   : w00176964
   修改内容   : 联合注册BBIT调整
 3.日    期   : 2012年6月11日
   作    者   : w00166186
   修改内容   : AT&T&DCM项目

 4.日    期   : 2012年8月22日
   作    者   : w00167002
   修改内容   : V7R1C50_GUTL_PhaseII:初始化保留字段
*****************************************************************************/
VOS_VOID  NAS_MML_InitSimEhPlmnInfo(
    NAS_MML_SIM_EHPLMN_INFO_STRU        *pstEhPlmnInfo
)
{
    VOS_UINT32                          i;

    pstEhPlmnInfo->ucEhPlmnNum          = 0;
    pstEhPlmnInfo->enPLMNSelInd         = NAS_MML_LAST_RPLMN_SEL_IND_RPLMN;
    pstEhPlmnInfo->enEHplmnPresentInd   = NAS_MML_EHPLMN_PRESENT_IND_NO_PREF;

    pstEhPlmnInfo->enHplmnType          = NAS_MML_HPLMN_TYPE_BUTT;

    for ( i = 0 ; i < NAS_MML_MAX_EHPLMN_NUM ; i++ )
    {
        pstEhPlmnInfo->astEhPlmnInfo[i].stPlmnId.ulMcc  = NAS_MML_INVALID_MCC;
        pstEhPlmnInfo->astEhPlmnInfo[i].stPlmnId.ulMnc  = NAS_MML_INVALID_MNC;
#if (FEATURE_ON == FEATURE_LTE)
        pstEhPlmnInfo->astEhPlmnInfo[i].usSimRat        = NAS_MML_SIM_ALL_RAT_SUPPORT_LTE;
#else
        pstEhPlmnInfo->astEhPlmnInfo[i].usSimRat        = NAS_MML_SIM_ALL_RAT;
#endif

        PS_MEM_SET(pstEhPlmnInfo->astEhPlmnInfo[i].aucReserve,
                   0X00,
                   sizeof(pstEhPlmnInfo->astEhPlmnInfo[i].aucReserve));

    }
}

/*****************************************************************************
 函 数 名  : NAS_MML_InitSimHPlmnWithRatInfo
 功能描述  : 初始化MML_CTX中SIM卡HPLMNWITHRAT信息
 输入参数  : 无
 输出参数  : pstHplmnWithRatInfo:HPLMNWithRat信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月11日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_InitSimHPlmnWithRatInfo(
    NAS_MML_SIM_HPLMN_WITH_RAT_INFO_STRU *pstHplmnWithRatInfo
)
{
    VOS_UINT32                          i;

    pstHplmnWithRatInfo->ucHPlmnWithRatNum  = 0;

    for ( i = 0 ; i < NAS_MML_MAX_HPLMN_WITH_RAT_NUM ; i++ )
    {
        pstHplmnWithRatInfo->astHPlmnWithRatInfo[i].stPlmnId.ulMcc   = NAS_MML_INVALID_MCC;
        pstHplmnWithRatInfo->astHPlmnWithRatInfo[i].stPlmnId.ulMnc   = NAS_MML_INVALID_MNC;
        pstHplmnWithRatInfo->astHPlmnWithRatInfo[i].usSimRat         = NAS_MML_INVALID_SIM_RAT;
    }
}
/*****************************************************************************
 函 数 名  : NAS_MML_InitSimUserPlmnInfo
 功能描述  : 初始化MML_CTX中SIM卡USERPLMN信息
 输入参数  : 无
 输出参数  : pstUserPlmnInfo:USERPLMN信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月11日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_InitSimUserPlmnInfo(
    NAS_MML_SIM_USERPLMN_INFO_STRU      *pstUserPlmnInfo
)
{
    VOS_UINT32                          i;

    pstUserPlmnInfo->ucUserPlmnNum      = 0;

    for ( i = 0 ; i < NAS_MML_MAX_USERPLMN_NUM ; i++ )
    {
        pstUserPlmnInfo->astUserPlmnInfo[i].stPlmnId.ulMcc   = NAS_MML_INVALID_MCC;
        pstUserPlmnInfo->astUserPlmnInfo[i].stPlmnId.ulMnc   = NAS_MML_INVALID_MNC;
        pstUserPlmnInfo->astUserPlmnInfo[i].usSimRat         = NAS_MML_INVALID_SIM_RAT;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MML_InitSimOperPlmnInfo
 功能描述  : 初始化MML_CTX中SIM卡OPERPLMN信息
 输入参数  : 无
 输出参数  : pstUserPlmnInfo:OPERPLMN信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月11日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数
 2.日    期    : 2013年11月26日
   作    者    : s00190137
   修改内容    : 将最大支持设置的OPLMN扩展到256个

*****************************************************************************/
VOS_VOID  NAS_MML_InitSimOperPlmnInfo(
    NAS_MML_SIM_OPERPLMN_INFO_STRU      *pstOperPlmnInfo
)
{
    VOS_UINT32                          i;

    pstOperPlmnInfo->usOperPlmnNum = 0;

    for ( i = 0 ; i < NAS_MML_MAX_OPERPLMN_NUM ; i++ )
    {
        pstOperPlmnInfo->astOperPlmnInfo[i].stPlmnId.ulMcc   = NAS_MML_INVALID_MCC;
        pstOperPlmnInfo->astOperPlmnInfo[i].stPlmnId.ulMnc   = NAS_MML_INVALID_MNC;
        pstOperPlmnInfo->astOperPlmnInfo[i].usSimRat         = NAS_MML_INVALID_SIM_RAT;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MML_InitSimSelPlmnInfo
 功能描述  : 初始化MML_CTX中SIM卡SELPLMN信息
 输入参数  : 无
 输出参数  : pstSelPlmnInfo:SELPLMN信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月11日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_InitSimSelPlmnInfo(
    NAS_MML_SIM_SELPLMN_INFO_STRU        *pstSelPlmnInfo
)
{
    VOS_UINT32                          i;

    pstSelPlmnInfo->ucSelPlmnNum        = 0;

    for ( i = 0 ; i < NAS_MML_MAX_SELPLMN_NUM ; i++ )
    {
        pstSelPlmnInfo->astPlmnId[i].ulMcc   = NAS_MML_INVALID_MCC;
        pstSelPlmnInfo->astPlmnId[i].ulMnc   = NAS_MML_INVALID_MNC;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MML_InitSimForbidPlmnInfo
 功能描述  : 初始化MML_CTX中SIM卡FORBIDPLMN信息
 输入参数  : 无
 输出参数  : pstForbidPlmnInfo:FORBIDPLMN信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月11日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数
 2.日    期   : 2015年9月23日
   作    者   : z00359541
   修改内容   : for CS REG FAIL FORB LA

*****************************************************************************/
VOS_VOID  NAS_MML_InitSimForbidPlmnInfo(
    NAS_MML_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo
)
{
    VOS_UINT32                          i;

    pstForbidPlmnInfo->ucForbGprsPlmnNum    = 0;
    pstForbidPlmnInfo->ucForbRegLaNum       = 0;
    pstForbidPlmnInfo->ucForbRoamLaNum      = 0;

    for ( i = 0 ; i < NAS_MML_MAX_FORBGPRSPLMN_NUM ; i++ )
    {
        pstForbidPlmnInfo->astForbGprsPlmnList[i].ulMcc = NAS_MML_INVALID_MCC;
        pstForbidPlmnInfo->astForbGprsPlmnList[i].ulMnc = NAS_MML_INVALID_MNC;
    }

    for ( i = 0 ; i < NAS_MML_MAX_FORBLA_FOR_ROAM_NUM ; i++ )
    {
        pstForbidPlmnInfo->astForbRomLaList[i].stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
        pstForbidPlmnInfo->astForbRomLaList[i].stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
        pstForbidPlmnInfo->astForbRomLaList[i].aucLac[0]      = NAS_MML_LAC_LOW_BYTE_INVALID;
        pstForbidPlmnInfo->astForbRomLaList[i].aucLac[1]      = NAS_MML_LAC_HIGH_BYTE_INVALID;
    }

    for ( i = 0 ; i < NAS_MML_MAX_FORBLA_FOR_REG_NUM ; i++ )
    {
        pstForbidPlmnInfo->astForbRegLaList[i].stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
        pstForbidPlmnInfo->astForbRegLaList[i].stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
        pstForbidPlmnInfo->astForbRegLaList[i].aucLac[0]      = NAS_MML_LAC_LOW_BYTE_INVALID;
        pstForbidPlmnInfo->astForbRegLaList[i].aucLac[1]      = NAS_MML_LAC_HIGH_BYTE_INVALID;
    }

    NAS_MML_InitForbLaWithValidPeriodList(&pstForbidPlmnInfo->stForbLaWithValidPeriod);

    /* 关机情况下不能清理forbid plmn信息 */
    if ( NAS_MML_INIT_CTX_POWEROFF == enInitType )
    {
        return;
    }

    pstForbidPlmnInfo->ucUsimForbPlmnNum    = 0;
    pstForbidPlmnInfo->ucForbPlmnNum        = 0;
    for ( i = 0 ; i < NAS_MML_MAX_FORBPLMN_NUM ; i++ )
    {
        pstForbidPlmnInfo->astForbPlmnIdList[i].ulMcc   = NAS_MML_INVALID_MCC;
        pstForbidPlmnInfo->astForbPlmnIdList[i].ulMnc   = NAS_MML_INVALID_MNC;
    }


}

/*****************************************************************************
 函 数 名  : NAS_MML_InitForbLaWithValidPeriodCfg
 功能描述  : 初始化MML_CTX中禁止LA有效时长信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年9月23日
   作    者   : z00359541
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_InitForbLaWithValidPeriodCfg(
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_LIST_STRU   *pstForbLaWithValidPeriodCfg
)
{
    VOS_UINT32                          i;

    pstForbLaWithValidPeriodCfg->ulSupportForbLaWithValidPeriodNum = 0;

    for ( i = 0 ; i < NAS_MML_CUSTOMIZE_FORB_LA_MAX_NUM ; i++ )
    {
        pstForbLaWithValidPeriodCfg->astForbLaWithValidPeriodCfgList[i].usRegFailCause              = NAS_MML_REG_FAIL_CAUSE_BUTT;
        pstForbLaWithValidPeriodCfg->astForbLaWithValidPeriodCfgList[i].usForbLaValidPeriodLen      = 0;
    }
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_InitForbLaWithValidPeriodList
 功能描述  : 初始化MML_CTX中禁止LA有效时长列表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年9月23日
   作    者   : z00359541
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_MML_InitForbLaWithValidPeriodList(
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU            *pstForbLaWithValidPeriod

)
{
    VOS_UINT32                          i;

    pstForbLaWithValidPeriod->ulForbLaWithValidPeriodNum = 0;
    for ( i = 0 ; i < NAS_MML_CUSTOMIZE_FORB_LA_MAX_NUM ; i++ )
    {
        pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].stForbLaWithValidPeriodLai.stPlmnId.ulMcc             = NAS_MML_INVALID_MCC;
        pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].stForbLaWithValidPeriodLai.stPlmnId.ulMnc             = NAS_MML_INVALID_MNC;
        pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].stForbLaWithValidPeriodLai.aucLac[0]                  = NAS_MML_LAC_LOW_BYTE_INVALID;
        pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].stForbLaWithValidPeriodLai.aucLac[1]                  = NAS_MML_LAC_HIGH_BYTE_INVALID;
        pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].ulForbLaWithValidPeriodBeginTick                      = 0;
        pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].ulForbLaWithValidPeriodTick                           = NAS_MML_MAX_TIME_TICK;
        pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].enCsRegFailCause                                      = NAS_MML_REG_FAIL_CAUSE_BUTT;
        pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].ulForbLaWithValidPeriodPunishBeginTick                = 0;
        pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].ulForbLaWithValidPeriodPunishDurationTick             = NAS_MML_MAX_TIME_TICK;
    }
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetForbLaWithValidPeriodCfg
 功能描述  : 获取MML中保存的禁止LA有效时长配置信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的禁止LA有效时长配置信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年9月23日
   作    者   : z00359541
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_LIST_STRU* NAS_MML_GetForbLaWithValidPeriodCfg( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stForbLaWithValidPeriodCfg);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetForbLaWithValidPeriodList
 功能描述  : 获取MML中保存的禁止LA有效时长列表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的禁止LA列表和时间信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年9月23日
   作    者   : z00359541
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU* NAS_MML_GetForbLaWithValidPeriodList( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.stForbidPlmnInfo.stForbLaWithValidPeriod);
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetKeepCsForbInfoCfg
 功能描述  : 配置MML中当PS注册成功时是否保留CS禁止信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年12月12日
   作    者   : z00359541
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetKeepCsForbInfoCfg(
    VOS_UINT8                           ucKeepCsForbInfoFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucKeepCsForbInfoFlg = ucKeepCsForbInfoFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetKeepCsForbInfoCfg
 功能描述  : 获取MML中保存的是否保留CS禁止信息的配置
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的是否保留CS禁止信息的配置
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年12月12日
   作    者   : z00359541
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetKeepCsForbInfoCfg( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucKeepCsForbInfoFlg);
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetNwIgnoreAuthFailCfg
 功能描述  : 配置MML中当网络不响应鉴权失败消息，释放链路时是否清除CKSN
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月4日
   作    者   : z00359541
   修改内容   : 新生成函数

  2.日    期   : 2016年1月18日
    作    者   : c00318887
    修改内容   : DTS2015123110917，共用了nv结构
*****************************************************************************/
VOS_VOID NAS_MML_SetNwIgnoreAuthFailCfg(
    VOS_UINT8                           ucNwIgnoreAuthFailFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stCleanCksnCfg.ucNwIgnoreAuthFailFlg = ucNwIgnoreAuthFailFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetNwIgnoreAuthFailCfg
 功能描述  : 获取MML中保存的是否清除CKSN信息的配置
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的是否清除CKSN信息的配置
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月4日
   作    者   : z00359541
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetNwIgnoreAuthFailCfg( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stCleanCksnCfg.ucNwIgnoreAuthFailFlg);
}

/*****************************************************************************
 函 数 名  : NAS_MML_InitAuthInfo
 功能描述  : 初始化鉴权相关信息
 输入参数  : pstAuthInfo -- 鉴权相关信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月16日
    作    者   : c00318887
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_InitAuthInfo(
    NAS_MML_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    NAS_MML_AUTH_INFO_STRU *pstAuthInfo
)
{
    PS_MEM_SET(pstAuthInfo->aucReserved, 0x00, sizeof(pstAuthInfo->aucReserved));

    /* 以下全局变量只有在上电时需要初始化，关机时不需要初始化 */
    if (NAS_MML_INIT_CTX_STARTUP == enInitType)
    {
        pstAuthInfo->ucUsimDoneGsmCsAuthFlg           = VOS_FALSE;
        pstAuthInfo->ucUsimDoneGsmPsAuthFlg           = VOS_FALSE;
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MML_InitUsimGsmAuthCfgInfo
 功能描述  : 初始化USIM卡在GSM下做2G鉴权的相关配置
 输入参数  : pstUsimGsmAuthCfg -- 保存USIM卡在GSM下做2G鉴权的相关配置的全局变量地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月16日
    作    者   : c00318887
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_InitUsimGsmAuthCfgInfo(
    NAS_MML_CLEAR_CKSN_CFG_STRU *pstUsimGsmAuthCfg
)
{
    PS_MEM_SET(pstUsimGsmAuthCfg, 0x00, sizeof(NAS_MML_CLEAR_CKSN_CFG_STRU));

    pstUsimGsmAuthCfg->ucNwIgnoreAuthFailFlg      = VOS_FALSE;

    pstUsimGsmAuthCfg->ucUsimGsmAuthNvCfg         = VOS_FALSE;
    
    return;
}


/*****************************************************************************
 函 数 名  : NAS_MML_IsNeedClearUsimGsmAuthFlg
 功能描述  : 判断 USIM卡在GSM下做过2G CS 鉴权，是否需要清除CS CKSN
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 需要设置
             VOS_FALSE -- 不需要设置
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月16日
    作    者   : c00318887
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsNeedClearCsCksn_UsimDoneGsmCsAuth(VOS_VOID)
{
    VOS_UINT8                           ucUsimDoneGsmCsAuthFlg;
    
    ucUsimDoneGsmCsAuthFlg              = NAS_MML_GetUsimDoneGsmCsAuthFlg();

    /* 非测试卡USIM卡，USIM卡在GSM下做过2G鉴权标记，在进行3G鉴权时，需要清除 */
    if ((NAS_MML_NET_RAT_TYPE_WCDMA     == NAS_MML_GetCurrNetRatType())
     && (VOS_TRUE                       == ucUsimDoneGsmCsAuthFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;    
}


/*****************************************************************************
 函 数 名  : NAS_MML_IsNeedClearPsCksn_UsimDoneGsmPsAuth
 功能描述  : 判断 USIM卡在GSM下做过2G PS 鉴权，是否需要清除PS CKSN
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 需要设置
             VOS_FALSE -- 不需要设置
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月16日
    作    者   : c00318887
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsNeedClearPsCksn_UsimDoneGsmPsAuth(VOS_VOID)
{
    VOS_UINT8                           ucUsimDoneGsmPsAuthFlg;
    
    ucUsimDoneGsmPsAuthFlg              = NAS_MML_GetUsimDoneGsmPsAuthFlg();

    /* 非测试卡USIM卡，USIM卡在GSM下做过2G鉴权标记，在进行3G鉴权时，需要清除 */
    if ((NAS_MML_NET_RAT_TYPE_WCDMA     == NAS_MML_GetCurrNetRatType())
     && (VOS_TRUE                       == ucUsimDoneGsmPsAuthFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;  
}


/*****************************************************************************
 函 数 名  : NAS_MML_IsNeedSetUsimDoneGsmAuthFlg
 功能描述  : 是否记录非测试卡USIM卡，USIM卡在GSM下做2G CS鉴权标记，以便在进行3G鉴权时清除 CS CKSN
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 需要设置
             VOS_FALSE -- 不需要设置
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月16日
    作    者   : c00318887
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_IsNeedSetUsimDoneGsmAuthFlg(VOS_VOID)
{
    NAS_MML_SIM_TYPE_ENUM_UINT8         ucSimType;
    VOS_UINT8                           ucUsimGsmAuthCfg;
    
    ucSimType                           = NAS_MML_GetSimType();
    ucUsimGsmAuthCfg                    = NAS_MML_GetUsimGsmAuthNvCfg();

    /* 非测试卡USIM卡，USIM卡在GSM下做2G鉴权标记，以便在进行3G鉴权时清除CKSN */
    if ((NAS_MML_NET_RAT_TYPE_GSM       == NAS_MML_GetCurrNetRatType())
     && (NAS_MML_SIM_TYPE_USIM          == ucSimType)
     && (VOS_TRUE                       == ucUsimGsmAuthCfg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;    
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetUsimGsmAuthNvCfg
 功能描述  : 设置Usim卡在GSM下做2G鉴权，在3G下需要清除CS CKSN的NV配置
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月16日
    作    者   : c00318887
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetUsimGsmAuthNvCfg(
    VOS_UINT8                           ucUsimGsmCsAuthNvCfg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stCleanCksnCfg.ucUsimGsmAuthNvCfg = ucUsimGsmCsAuthNvCfg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetUsimGsmAuthNvCfg
 功能描述  : 获取MML中保存的Usim卡在GSM下做2G鉴权，在3G下需要清除CS CKSN的NV配置
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的Usim卡在GSM下做2G鉴权，在3G下需要清除CS CKSN的NV配置
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月16日
    作    者   : c00318887
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MML_GetUsimGsmAuthNvCfg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stCleanCksnCfg.ucUsimGsmAuthNvCfg);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetUsimDoneGsmCsAuthFlg
 功能描述  : 设置Usim卡在GSM下做2G cs 鉴权的标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月16日
    作    者   : c00318887
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetUsimDoneGsmCsAuthFlg(
    VOS_UINT8                           ucUsimDoneGsmCsAuthFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stAuthInfo.ucUsimDoneGsmCsAuthFlg = ucUsimDoneGsmCsAuthFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetUsimDoneGsmCsAuthFlg
 功能描述  : 获取Usim卡在GSM下做2G cs 鉴权的标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : Usim卡在GSM下做2G cs 鉴权的标记
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月16日
    作    者   : c00318887
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MML_GetUsimDoneGsmCsAuthFlg( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stAuthInfo.ucUsimDoneGsmCsAuthFlg);
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetUsimDoneGsmPsAuthFlg
 功能描述  : 设置Usim卡在GSM下做2G Ps 鉴权的标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月16日
    作    者   : c00318887
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetUsimDoneGsmPsAuthFlg(
    VOS_UINT8                           ucUsimDoneGsmPsAuthFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stAuthInfo.ucUsimDoneGsmPsAuthFlg = ucUsimDoneGsmPsAuthFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetUsimDoneGsmPsAuthFlg
 功能描述  : 获取Usim卡在GSM下做2G Ps 鉴权的标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : Usim卡在GSM下做2G Ps 鉴权的标记
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月16日
    作    者   : c00318887
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MML_GetUsimDoneGsmPsAuthFlg( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stAuthInfo.ucUsimDoneGsmPsAuthFlg);
}


/*****************************************************************************
 函 数 名  : NAS_MML_InitSimPlmnInfoCtx
 功能描述  : 初始化MML_CTX中SIM PLMN相关信息
 输入参数  : enInitType:初始化类型
 输出参数  : pstSimStatusInfo:SIM PLMN相关信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月11日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数
 2.日    期   : 2012年8月16日
   作    者   : t00212959
   修改内容   : DCM定制需求和遗留问题
 3.日    期   : 2015年10月20日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_VOID  NAS_MML_InitSimPlmnInfoCtx(
    NAS_MML_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    NAS_MML_SIM_PLMN_INFO_STRU         *pstSimStatusInfo
)
{
    /* 关机情况下不需要清空内存中SIM相关变量 */
    if (NAS_MML_INIT_CTX_STARTUP  == enInitType )
    {
        NAS_MML_InitSimEhPlmnInfo(&(pstSimStatusInfo->stEhPlmnInfo));

        NAS_MML_InitSimHPlmnWithRatInfo(&(pstSimStatusInfo->stHplmnWithRatInfo));

        NAS_MML_InitSimUserPlmnInfo(&(pstSimStatusInfo->stUserPlmnInfo));

        NAS_MML_InitSimOperPlmnInfo(&(pstSimStatusInfo->stOperPlmnInfo));

        NAS_MML_InitSimSelPlmnInfo(&(pstSimStatusInfo->stSelPlmnInfo));

        /* Modified by t00212959 for DCM定制需求和遗留问题, 2012-8-16, begin */
        NAS_MML_SetUsimMncLen(NAS_MML_MNC_LENGTH_THREE_BYTES_IN_IMSI);
        /* Modified by t00212959 for DCM定制需求和遗留问题, 2012-8-16, end */

        NAS_MML_SetCsgDisplayCtrlFlag(VOS_FALSE);

    }

    NAS_MML_InitSimForbidPlmnInfo(enInitType, &(pstSimStatusInfo->stForbidPlmnInfo));

}

/*****************************************************************************
 函 数 名  : NAS_MML_InitSimInfoCtx
 功能描述  : 初始化MML_CTX中SIM相关信息
 输入参数  : enInitType:初始化类型
             pstSimInfo:SIM卡信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月30日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数
 2.日    期   : 2014年4月18日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:call mode初始化
 3.日    期   : 2015年10月20日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_VOID  NAS_MML_InitSimInfoCtx(
    NAS_MML_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    NAS_MML_SIM_INFO_STRU              *pstSimInfo
)
{
    NAS_MML_InitSimStatusInfoCtx(enInitType, &(pstSimInfo->stSimStatus));

    NAS_MML_InitSimMsIdentityInfoCtx(&(pstSimInfo->stMsIdentity));

    NAS_MML_InitSimPsSecurityCtx(&(pstSimInfo->stPsSecurity));

    NAS_MML_InitSimCsSecurityCtx(&(pstSimInfo->stCsSecurity));

    NAS_MML_InitSimPlmnInfoCtx(enInitType, &(pstSimInfo->stSimPlmnInfo));
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-18, begin */
    NAS_MML_InitCallModeInfoCtx(&(pstSimInfo->enCallMode));
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-18, end */

    NAS_MML_InitSimCsgInfo(&pstSimInfo->stSimCsgInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MML_InitMs3GppRel
 功能描述  : 初始化MS的协议版本,默认为W支持R6,G支持R4
 输入参数  : 无
 输出参数  : pstMs3GppRel:MS协议版本
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月14日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数
 2.日    期   : 2013年12月24日
   作    者   : w00242748
   修改内容   : DTS2013101106863:L下被拒原因值#35，只有在R10及其协议以上处理才与#11
                原因值处理相同，否则当做OTHER CAUSE来处理。

*****************************************************************************/
VOS_VOID  NAS_MML_InitMs3GppRel(
    NAS_MML_MS_3GPP_REL_STRU               *pstMs3GppRel
)
{
    pstMs3GppRel->enMsGsmRel    =   NAS_MML_3GPP_REL_R4;
    pstMs3GppRel->enMsWcdmaRel  =   NAS_MML_3GPP_REL_R6;
    pstMs3GppRel->enMsMscRel    =   NAS_MML_MSC_REL_R99;
    pstMs3GppRel->enMsSgsnRel   =   NAS_MML_SGSN_REL_R99;
    pstMs3GppRel->enLteNasRelease = NAS_MML_3GPP_REL_R9;
}

/*****************************************************************************
 函 数 名  : NAS_MML_InitPlatformBandCap
 功能描述  : 初始化MML_CTX中手机通道能力
 输入参数  : 无
 输出参数  : pstPlatformBandCapability: 手机通道能力
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年02月10日
    作    者   : f62575
    修改内容   : DTS2014012600456: en_NV_Item_WG_RF_MAIN_BAND
数据修改为从内存中获取
*****************************************************************************/
VOS_VOID  NAS_MML_InitPlatformBandCap(
    NAS_MML_PLATFORM_BAND_CAP_STRU     *pstPlatformBandCapability
)
{
    PS_MEM_SET(pstPlatformBandCapability, 0, sizeof(NAS_MML_PLATFORM_BAND_CAP_STRU));
}

/*****************************************************************************
 函 数 名  : NAS_MML_InitMsCapability
 功能描述  : 初始化MS的手机能力
 输入参数  : 无
 输出参数  : pstMsCapability:MS手机能力
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月14日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数
 2.日    期   : 2011年10月28日
   作    者   : z00161729
   修改内容   : V7R1 phaseIII联合注册修改

 2.日    期   : 2012年3月22日
   作    者   : z40661
   修改内容   : DTS2012032004429 MS capacity能力的修改
 3.日    期   : 2013年1月6日
   作    者   : s00217060
   修改内容   : for DSDA GUNAS C CORE:初始化平台接入技术能力为GSM only
 4.日    期   : 2013年10月22日
   作    者   : w00176964
   修改内容   : VoLTE_PhaseII 项目修改:增加classmark3的默认值初始化
 5.日    期   : 2014年02月10日
   作    者   : f62575
   修改内容   : DTS2014012600456: en_NV_Item_WG_RF_MAIN_BAND
                数据修改为从内存中获取

*****************************************************************************/
VOS_VOID  NAS_MML_InitMsCapability(
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability
)
{
    VOS_UINT8                          i;

    pstMsCapability->ucClassmark1               =   NAS_MML_DEFAULT_CLASSMARK1_VALUE;

    pstMsCapability->aucClassmark2[0]           =   NAS_MML_DEFAULT_CLASSMARK2_FIRST_VALUE;
    pstMsCapability->aucClassmark2[1]           =   NAS_MML_DEFAULT_CLASSMARK2_SECOND_VALUE;
    pstMsCapability->aucClassmark2[2]           =   NAS_MML_DEFAULT_CLASSMARK2_THIRD_VALUE;
    pstMsCapability->aucClassmark2[3]           =   NAS_MML_DEFAULT_CLASSMARK2_FOURTH_VALUE;

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-22, begin */
    PS_MEM_SET(pstMsCapability->aucFddClassmark3, 0x0, NAS_MML_CLASSMARK3_LEN);
    PS_MEM_SET(pstMsCapability->aucTddClassmark3, 0x0, NAS_MML_CLASSMARK3_LEN);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-22, end */

    pstMsCapability->stMsNetworkCapability.ucNetworkCapabilityLen     =   NAS_MML_DEFAULT_NETWORKCAPABILITY_LEN;

    PS_MEM_SET(pstMsCapability->stMsNetworkCapability.aucNetworkCapability, 0, NAS_MML_MAX_NETWORK_CAPABILITY_LEN);

    pstMsCapability->stMsNetworkCapability.aucNetworkCapability[0]    =   NAS_MML_DEFAULT_NETWORKCAPABILITY_FIRST_VALUE;
    pstMsCapability->stMsNetworkCapability.aucNetworkCapability[1]    =   NAS_MML_DEFAULT_NETWORKCAPABILITY_SECOND_VALUE;

    for ( i = 0 ; i < NAS_MML_MAX_IMEISV_LEN ; i++ )
    {
        pstMsCapability->aucImeisv[i]           =   i;

        /* 后面的字段填写默认值 */
        if ( i >= 10 )
        {
            pstMsCapability->aucImeisv[i]       = NAS_MML_DEFAULT_IMEI_VALUE;
        }
    }

#if (FEATURE_ON == FEATURE_LTE)
    PS_MEM_SET(pstMsCapability->stUeNetworkCapbility.aucUeNetCap, 0, NAS_MML_MAX_UE_NETWORK_CAPABILITY_LEN);
    pstMsCapability->stUeNetworkCapbility.ucUeNetCapLen  = NAS_MML_DEFAULT_UE_NETWORK_CAPABILITY_LEN;
    pstMsCapability->stUeNetworkCapbility.aucUeNetCap[0] = NAS_MML_DEFAULT_UE_NET_CAP_FIRST_VALUE;
    pstMsCapability->stUeNetworkCapbility.aucUeNetCap[1] = NAS_MML_DEFAULT_UE_NET_CAP_FIRST_VALUE;
    pstMsCapability->stUeNetworkCapbility.aucUeNetCap[2] = NAS_MML_DEFAULT_UE_NET_CAP_THIRD_VALUE;
    pstMsCapability->stUeNetworkCapbility.aucUeNetCap[3] = NAS_MML_DEFAULT_UE_NET_CAP_THIRD_VALUE;
#endif

    /* 初始化为GSM only */
    for (i = 0; i < NAS_MML_MAX_PLATFORM_RAT_NUM; i++)
    {
        pstMsCapability->stPlatformRatCap.aenRatPrio[i] = NAS_MML_PLATFORM_RAT_TYPE_BUTT;
    }
    pstMsCapability->stPlatformRatCap.ucRatNum      = NAS_MML_MIN_PLATFORM_RAT_NUM;
    pstMsCapability->stPlatformRatCap.aenRatPrio[0] = NAS_MML_PLATFORM_RAT_TYPE_GSM;


    NAS_MML_InitPlatformBandCap(&(pstMsCapability->stPlatformBandCap));
}

/*****************************************************************************
 函 数 名  : NAS_MML_InitMsSysCfgInfo
 功能描述  : 初始化MS的系统配置能力
 输入参数  : 无
 输出参数  : pstMsSysCfgInfo:MS的系统配置能力
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月14日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

 2.日    期   : 2011年10月26日
   作    者   : w00176964
   修改内容   : V7R1 PhaseIII调整:新增LTE能力状态的初始化
 3.日    期   : 2011年10月28日
   作    者   : z00161729
   修改内容   : V7R1 PhaseIII调整:新增LTE ue operation mode初始化
 4.日    期   : 2012年3月17日
   作    者   : w00176964
   修改内容   : DTS2012031900095 V7R1 C30 SBM&EM定制需求:NV定制全局变量初始化为默认不支持
 5.日    期   : 2012年3月8日
   作    者   : w00167002
   修改内容   : CSFB调整:UE USAGE初始化
 6.日    期   : 2012年5月19日
   作    者   : z00161729
   修改内容  : V7R1C50 GUL BG搜网修改
 7.日    期   : 2012年6月12日
   作    者   : s46746
   修改内容   : for CS/PS mode 1,增加是否支持IMS标记初始化
 8.日    期   : 2013年7月25日
   作    者   : w00242748
   修改内容   : DTS2013072200933:vodafone r8网络csfb mt到w，cs ps链接释放后1.5s内重选回l，
                网络后续2s左右会重新下发paging消息，存在丢寻呼被叫打不通，参考标杆实现，
                rau req中带follow on标志,无明确协议依据
 9.日    期   : 2014年2月13日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加异系统到HRPD的处理
10.日    期   : 2014年7月14日
   作    者   : w00242748
   修改内容   : DTS2014063003419:SYSCFG触发高优先级接入技术搜网增加NV控制，同时
                打断搜网状态机(等CS/PS注册结果同样需要等)
*****************************************************************************/
VOS_VOID  NAS_MML_InitMsSysCfgInfo(
    NAS_MML_MS_SYS_CFG_INFO_STRU        *pstMsSysCfgInfo
)
{
    pstMsSysCfgInfo->enMsMode                   = NAS_MML_MS_MODE_PS_CS;
    pstMsSysCfgInfo->ucPsAutoAttachFlg          = VOS_TRUE;
#if   (FEATURE_ON == FEATURE_LTE)
    pstMsSysCfgInfo->stPrioRatList.ucRatNum     = NAS_MML_MAX_RAT_NUM;
    pstMsSysCfgInfo->stPrioRatList.aucRatPrio[0]= NAS_MML_NET_RAT_TYPE_LTE;
    pstMsSysCfgInfo->stPrioRatList.aucRatPrio[1]= NAS_MML_NET_RAT_TYPE_WCDMA;
    pstMsSysCfgInfo->stPrioRatList.aucRatPrio[2]= NAS_MML_NET_RAT_TYPE_GSM;
#else
    pstMsSysCfgInfo->stPrioRatList.ucRatNum     = NAS_MML_MAX_RAT_NUM;
    pstMsSysCfgInfo->stPrioRatList.aucRatPrio[0]= NAS_MML_NET_RAT_TYPE_WCDMA;
    pstMsSysCfgInfo->stPrioRatList.aucRatPrio[1]= NAS_MML_NET_RAT_TYPE_GSM;
#endif

    /* Added by s00246516 for L-C互操作项目, 2014-02-14, Begin */
    pstMsSysCfgInfo->st3Gpp2RatList.ucRatNum      = 0x0;
    pstMsSysCfgInfo->st3Gpp2RatList.aucRatPrio[0] = NAS_MML_3GPP2_RAT_TYPE_BUTT;
    pstMsSysCfgInfo->st3Gpp2RatList.aucRatPrio[1] = NAS_MML_3GPP2_RAT_TYPE_BUTT;
    /* Added by s00246516 for L-C互操作项目, 2014-02-14, End */

    /* GSM的支持的Band */
    pstMsSysCfgInfo->stMsBand.unGsmBand.stBitBand.BandGsm1800= VOS_TRUE;
    pstMsSysCfgInfo->stMsBand.unGsmBand.stBitBand.BandGsm1900= VOS_TRUE;
    pstMsSysCfgInfo->stMsBand.unGsmBand.stBitBand.BandGsm450 = VOS_TRUE;
    pstMsSysCfgInfo->stMsBand.unGsmBand.stBitBand.BandGsm480 = VOS_TRUE;
    pstMsSysCfgInfo->stMsBand.unGsmBand.stBitBand.BandGsm700 = VOS_TRUE;
    pstMsSysCfgInfo->stMsBand.unGsmBand.stBitBand.BandGsm850 = VOS_TRUE;
    pstMsSysCfgInfo->stMsBand.unGsmBand.stBitBand.BandGsmE900= VOS_TRUE;
    pstMsSysCfgInfo->stMsBand.unGsmBand.stBitBand.BandGsmP900= VOS_TRUE;
    pstMsSysCfgInfo->stMsBand.unGsmBand.stBitBand.BandGsmR900= VOS_FALSE;

    /* WCDMA的支持的Band */
    pstMsSysCfgInfo->stMsBand.unWcdmaBand.stBitBand.BandWCDMA_III_1800 = VOS_TRUE;
    pstMsSysCfgInfo->stMsBand.unWcdmaBand.stBitBand.BandWCDMA_II_1900  = VOS_TRUE;
    pstMsSysCfgInfo->stMsBand.unWcdmaBand.stBitBand.BandWCDMA_IV_1700  = VOS_TRUE;
    pstMsSysCfgInfo->stMsBand.unWcdmaBand.stBitBand.BandWCDMA_IX_J1700 = VOS_TRUE;
    pstMsSysCfgInfo->stMsBand.unWcdmaBand.stBitBand.BandWCDMA_I_2100   = VOS_TRUE;
    pstMsSysCfgInfo->stMsBand.unWcdmaBand.stBitBand.BandWCDMA_VIII_900 = VOS_TRUE;
    pstMsSysCfgInfo->stMsBand.unWcdmaBand.stBitBand.BandWCDMA_VII_2600 = VOS_TRUE;
    pstMsSysCfgInfo->stMsBand.unWcdmaBand.stBitBand.BandWCDMA_VI_800   = VOS_TRUE;
    pstMsSysCfgInfo->stMsBand.unWcdmaBand.stBitBand.BandWCDMA_V_850    = VOS_TRUE;

    /* LTE的支持的Band */
    pstMsSysCfgInfo->stMsBand.stLteBand.aulLteBand[0] = NAS_MML_LTE_ALL_BAND_SUPPORTED;
    pstMsSysCfgInfo->stMsBand.stLteBand.aulLteBand[1] = NAS_MML_LTE_ALL_BAND_SUPPORTED;

#if   (FEATURE_ON == FEATURE_LTE)
    /* 设置LTE的能力默认为ENABLE状态 */
    NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_BUTT);

    /* 设置LTE的CS业务配置能力默认为不激活 */
    NAS_MML_SetLteCsServiceCfg(NAS_MML_LTE_SUPPORT_BUTT);

    /* 初始化UE USAGE为无效值   */
    NAS_MML_SetLteUeUsageSetting(NAS_MML_LTE_UE_USAGE_SETTIN_BUTT);

    /* 初始化VOICE DOMAIN PREFERENCE为无效值 */
     NAS_MML_SetVoiceDomainPreference(NAS_MML_VOICE_DOMAIN_PREFER_BUTT);

    /* 初始化IMS不支持 */
    NAS_MML_SetLteImsSupportFlg(VOS_FALSE);
    NAS_MML_SetVoiceCallOnImsSupportFlag(VOS_FALSE);
    NAS_MML_SetSmsOnImsSupportFlag(VOS_FALSE);
    NAS_MML_SetVideoCallOnImsSupportFlag(VOS_FALSE);
    NAS_MML_SetUssdOnImsSupportFlag(VOS_FALSE);

    NAS_MML_SetDisableLteRoamFlg(VOS_FALSE);

    /* Deleted by w00176964 for VoLTE_PhaseIII  项目, 2014-01-13, begin */
    /* Deleted by w00176964 for VoLTE_PhaseIII  项目, 2014-01-13, end */
#endif

    NAS_MML_SetDelayedCsfbLauFlg(VOS_FALSE);

    NAS_MML_SetSyscfgTriHighRatSrchFlg(VOS_TRUE);
}

/*****************************************************************************
 函 数 名  : NAS_MML_InitRplmnCfgInfo
 功能描述  : 初始化RPLMN的定制特性
 输入参数  : 无
 输出参数  : pstRplmnCfg:RPLMN的定制特性
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月14日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_InitRplmnCfgInfo(
    NAS_MML_RPLMN_CFG_INFO_STRU         *pstRplmnCfg
)
{
    VOS_UINT32                          i;

    pstRplmnCfg->enTinType              = NAS_MML_TIN_TYPE_INVALID;
    pstRplmnCfg->ucMultiRATRplmnFlg     = VOS_FALSE;
    pstRplmnCfg->ucLastRplmnRatFlg      = VOS_FALSE;
    pstRplmnCfg->enLastRplmnRat         = NAS_MML_NET_RAT_TYPE_BUTT;
    pstRplmnCfg->stGRplmnInNV.ulMcc     = NAS_MML_INVALID_MCC;
    pstRplmnCfg->stGRplmnInNV.ulMnc     = NAS_MML_INVALID_MNC;
    pstRplmnCfg->stWRplmnInNV.ulMcc     = NAS_MML_INVALID_MCC;
    pstRplmnCfg->stWRplmnInNV.ulMnc     = NAS_MML_INVALID_MNC;

    for ( i = 0 ; i < NAS_MML_MAX_IMSI_LEN ; i++ )
    {
        pstRplmnCfg->aucLastImsi[i]    = NAS_MML_IMSI_INVALID;
    }
}


/*****************************************************************************
 函 数 名  : NAS_MML_InitHplmnCfgInfo
 功能描述  : 初始化HPLMN的定制特性
 输入参数  : 无
 输出参数  : pstHplmnCfg:HPLMN的定制特性
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月14日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数
 2.日    期   : 2011年7月20日
   作    者   : z00161729
   修改内容   : 修改默认值为打开
 3.日    期   : 2012年6月9日
   作    者   : l00130025
   修改内容   : DTS2012060400029:添加对HPLMNAct优先接入技术的定制；目前USim卡中HPLMNACT很多不支持L
 4.日    期   : 2012年6月11日
   作    者   : w00166186
   修改内容   : AT&T&DCM项目
 5.日    期   : 2012年8月15日
   作    者   : w00167002
   修改内容   : V7R1C50_GUTL_PhaseII:初始化用户配置的EHplmn列表信息
 6.日    期   : 2015年9月30日
   作    者   : c00318887
   修改内容   : DTS2015091700173
*****************************************************************************/
VOS_VOID  NAS_MML_InitHplmnCfgInfo(
    NAS_MML_HPLMN_CFG_INFO_STRU         *pstHplmnCfg
)
{
    pstHplmnCfg->enAutoSearchHplmnFlg   = NAS_MML_AUTO_SRCH_FLG_TYPE_HPLMN_FIRST;
    pstHplmnCfg->ucEhplmnSupportFlg     = VOS_TRUE;
    pstHplmnCfg->ucHplmnSearchPowerOn   = VOS_FALSE;
    pstHplmnCfg->ucManualSearchHplmnFlg = VOS_TRUE;

    pstHplmnCfg->stPrioHplmnActCfg.ucActiveFlg              = VOS_FALSE;
    pstHplmnCfg->stPrioHplmnActCfg.usPrioHplmnAct           = NAS_MML_SIM_NO_RAT;

    pstHplmnCfg->ucActingHPlmnSupportFlg                    = VOS_FALSE;

    pstHplmnCfg->ucAddEhplmnWhenSrchHplmnFlg                = VOS_FALSE;

    NAS_MML_InitUserCfgExtEHplmnInfo( &(pstHplmnCfg->stUserCfgExtEhplmnInfo) );
}

/* Modified by z40661 for 泰国AIS特性 2012-05-17, begin*/
/*****************************************************************************
 函 数 名  : NAS_MMC_InitAisRoamingCfg
 功能描述  : 初始化AIS定制需求的内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月17日
    作    者   : z40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_InitAisRoamingCfg(
    NAS_MML_AIS_ROAMING_CFG_STRU        *pstAisRoamingCfg
)
{
    pstAisRoamingCfg->ucEnableFlg               = VOS_FALSE;
    pstAisRoamingCfg->enHighPrioRatType         = NAS_MML_NET_RAT_TYPE_BUTT;
    pstAisRoamingCfg->stHighPrioPlmnId.ulMcc    = NAS_MML_INVALID_MCC;
    pstAisRoamingCfg->stHighPrioPlmnId.ulMnc    = NAS_MML_INVALID_MNC;
    pstAisRoamingCfg->stSimHPlmnId.ulMcc        = NAS_MML_INVALID_MCC;
    pstAisRoamingCfg->stSimHPlmnId.ulMnc        = NAS_MML_INVALID_MNC;
}
/* Modified by z40661 for 泰国AIS特性 2012-05-17, end */

/*****************************************************************************
 函 数 名  : NAS_MML_InitRoamCfgInfo
 功能描述  : 初始化漫游的定制特性
 输入参数  : 无
 输出参数  : pstRoamCfg:漫游的定制特性
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月14日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

 2.日    期   : 2012年5月17日
   作    者   : z40661
   修改内容   : 泰国AIS特性

*****************************************************************************/
VOS_VOID  NAS_MML_InitRoamCfgInfo(
    NAS_MML_ROAM_CFG_INFO_STRU          *pstRoamCfg
)
{
    pstRoamCfg->enRoamCapability            = NAS_MML_ROAM_NATION_OFF_INTERNATION_OFF;
    pstRoamCfg->ucRoamFeatureFlg            = VOS_FALSE;
    pstRoamCfg->ucNationalRoamNum           = NAS_MML_DFAULT_NATIONAL_ROAM_PLMN_NUM;
    pstRoamCfg->ucNotRoamNum                = NAS_MML_DFAULT_NOT_ROAM_PLMN_NUM;
    pstRoamCfg->astRoamPlmnIdList[0].ulMcc  = NAS_MML_DFAULT_NATIONAL_ROAM_MCC;
    pstRoamCfg->astRoamPlmnIdList[0].ulMnc  = NAS_MML_DFAULT_NATIONAL_ROAM_MNC;


    /* Modified by z40661 for 泰国AIS特性 2012-05-17, begin */
    NAS_MML_InitAisRoamingCfg(&(pstRoamCfg->stAisRoamingCfg));
    /* Modified by z40661 for 泰国AIS特性 2012-05-17, end */
}

/*****************************************************************************
函 数 名  : NAS_MML_InitBgSearchCfgInfo
功能描述  : 初始化BG搜索定制特性
输入参数  : 无
输出参数  : pstBgSearchCfg:BG搜索定制特性
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期  : 2011年7月14日
  作    者   : zhoujun 40661
  修改内容   : 新生成函数
2.日    期  : 2011年7月25日
  作    者   : z00161729
  修改内容   : 全局变量修改调整
3.日    期   : 2012年6月11日
  作    者   : l60609
  修改内容   : AT&T&DCM：搜索控制默认关闭
4.日    期   : 2012年6月11日
  作    者   : w00166186
  修改内容   : AT&T&DCM项目
5.日    期   : 2014年2月24日
  作    者   : w00176964
  修改内容   : High_Rat_Hplmn_Search特性调整
*****************************************************************************/
VOS_VOID  NAS_MML_InitBgSearchCfgInfo(
    NAS_MML_BG_SEARCH_CFG_INFO_STRU     *pstBgSearchCfg
)
{
    pstBgSearchCfg->ucEnhancedHplmnSrchFlg                             = VOS_FALSE;
    pstBgSearchCfg->ucSpecialRoamFlg                                   = VOS_FALSE;
    pstBgSearchCfg->ulFirstStartHplmnTimerLen                          = TI_NAS_MMC_HPLMN_TIMER_FIRST_LEN;                                /* 默认为2分钟 */
    pstBgSearchCfg->stDefaultMaxHplmnTimerPeriod.ucNvimActiveFlg       = VOS_FALSE;
    pstBgSearchCfg->stDefaultMaxHplmnTimerPeriod.ulDefaultMaxHplmnLen  = TI_NAS_MMC_DEFAULT_MAX_SEARCH_HPLMN_LEN;
    pstBgSearchCfg->stNonFirstHplmnTimerPeriod.ucNvimActiveFlg         = VOS_FALSE;
    pstBgSearchCfg->stNonFirstHplmnTimerPeriod.ulNonFirstHplmnTimerLen = TI_NAS_MMC_HPLMN_TIMER_FIRST_LEN;
    pstBgSearchCfg->ucScanCtrlFlg                                      = VOS_FALSE;

    pstBgSearchCfg->stBgSearchRegardlessMcc.ucCustomMccNum             = 0;

    NAS_MML_InitHighPrioRatHplmnTimerCfgInfo(&(pstBgSearchCfg->stHighRatHplmnTimerCfg));

    /* Modified by c00318887 for file refresh需要触发背景搜, 2015-4-28, begin */
    NAS_MML_InitHighPrioPlmnRefreshTriggerBGSearchCfgInfo(&pstBgSearchCfg->stHighPrioPlmnRefreshTriggerBGSearchCfg);
    /* Modified by c00318887 for file refresh需要触发背景搜, 2015-4-28, end */
}


/*****************************************************************************
函 数 名  : NAS_MML_InitRoamingRejectNoRetryInfo
功能描述  :
输入参数  : 无
输出参数  :
返 回 值  :
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2013年11月19日
  作    者   : l00208543
  修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_MML_InitRoamingRejectNoRetryInfo(
    NAS_MML_ROAMINGREJECT_NORETYR_CFG_STRU           *pstRetryInfo
)
{
    pstRetryInfo->aucReserve[0]                    = 0;
    pstRetryInfo->aucReserve[1]                    = 0;
    pstRetryInfo->aucReserve[2]                    = 0;
    pstRetryInfo->ucNoRetryRejectCauseNum          = 0;
    pstRetryInfo->aucNoRetryRejectCause[0]         = 0;
    pstRetryInfo->aucNoRetryRejectCause[1]         = 0;
    pstRetryInfo->aucNoRetryRejectCause[2]         = 0;
    pstRetryInfo->aucNoRetryRejectCause[3]         = 0;
    pstRetryInfo->aucNoRetryRejectCause[4]         = 0;
    pstRetryInfo->aucNoRetryRejectCause[5]         = 0;
    pstRetryInfo->aucNoRetryRejectCause[6]         = 0;
    pstRetryInfo->aucNoRetryRejectCause[7]         = 0;

    return;
}

/*****************************************************************************
函 数 名  : NAS_MML_InitPlmnLockCfgInfo
功能描述  : 初始化PLMN的锁卡信息
输入参数  : 无
输出参数  : pstPlmnLockCfg:初始化PLMN的锁卡信息
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期  : 2011年7月14日
  作    者   : zhoujun 40661
  修改内容   : 新生成函数
2.日    期   : 2012年8月20日
  作    者   : w00176964
  修改内容   : GUTL PhaseII:初始化禁止接入技术的PLMN信息
3.日    期   : 2015年4月24日
  作    者   : z00161729
  修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID  NAS_MML_InitPlmnLockCfgInfo(
    NAS_MML_PLMN_LOCK_CFG_INFO_STRU     *pstPlmnLockCfg
)
{
    VOS_UINT32                          i;

    /* 初始化锁网黑名单信息 */
    pstPlmnLockCfg->ucBlackPlmnLockNum  = 0;
    for ( i = 0 ; i < NAS_MML_MAX_BLACK_LOCK_PLMN_NUM; i++ )
    {
        pstPlmnLockCfg->astBlackPlmnId[i].ulMcc = NAS_MML_INVALID_MCC;
        pstPlmnLockCfg->astBlackPlmnId[i].ulMnc = NAS_MML_INVALID_MNC;
    }

    /* 初始化锁网白名单信息 */
    pstPlmnLockCfg->ucWhitePlmnLockNum  = 0;
    for ( i = 0 ; i < NAS_MML_MAX_WHITE_LOCK_PLMN_NUM; i++ )
    {
        pstPlmnLockCfg->astWhitePlmnId[i].ulMcc = NAS_MML_INVALID_MCC;
        pstPlmnLockCfg->astWhitePlmnId[i].ulMnc = NAS_MML_INVALID_MNC;
    }

    NAS_MML_InitDisabledRatPlmnCfgInfo(&(pstPlmnLockCfg->stDisabledRatPlmnInfo));
}

/*****************************************************************************
函 数 名  : NAS_MML_InitRatBlackListAccordSimType
功能描述  : 初始化根据卡类型禁止RAT列表
输入参数  : 无
输出参数  : pstRatBlackList:
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期  : 2013年11月01日
  作    者   : l00208543
  修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_MML_InitRatForbiddenList(
    NAS_MML_RAT_FORBIDDEN_LIST_STRU    *pstRatBlackList
)
{
    VOS_UINT32                          i;

    pstRatBlackList->enSwitchFlag       = NAS_MML_RAT_FORBIDDEN_LIST_SWITCH_INACTIVE;
    pstRatBlackList->ucImsiListNum      = 0;
    pstRatBlackList->ucForbidRatNum     = 0;

    for (i = 0; i < NAS_MML_MAX_IMSI_FORBIDDEN_LIST_NUM; i++)
    {
        pstRatBlackList->astImsiList[i].ulMcc = NAS_MML_INVALID_MCC;
        pstRatBlackList->astImsiList[i].ulMnc = NAS_MML_INVALID_MNC;
    }

    for (i = 0; i < NAS_MML_MAX_RAT_FORBIDDEN_LIST_NUM; i++)
    {
        pstRatBlackList->aenForbidRatList[i] = NAS_MML_NET_RAT_TYPE_BUTT;
    }

}

/*****************************************************************************
函 数 名  : NAS_MML_InitRatForbiddenStatusCfg
功能描述  : 初始化Nas保存的RAT禁止信息
输入参数  : 无
输出参数  : pstRatBlackList:
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期  : 2013年11月01日
  作    者   : l00208543
  修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_MML_InitRatForbiddenStatusCfg(
    NAS_MML_RAT_FORBIDDEN_STATUS_STRU  *pstRatCapaStatus
)
{
   pstRatCapaStatus->ucIsImsiInForbiddenListFlg = VOS_FALSE;
   pstRatCapaStatus->ucGsmCapaStatus            = NAS_MML_RAT_CAPABILITY_STATUS_BUTT;
   pstRatCapaStatus->ucLteCapaStatus            = NAS_MML_RAT_CAPABILITY_STATUS_BUTT;
   pstRatCapaStatus->ucUtranCapaStatus          = NAS_MML_RAT_CAPABILITY_STATUS_BUTT;
}


/*****************************************************************************
函 数 名  : NAS_MML_InitDisabledRatPlmnCfgInfo
功能描述  : 初始化禁止接入技术的PLMN信息
输入参数  : 无
输出参数  : pstDisabledRatPlmnCfg:禁止接入技术的PLMN信息
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期  : 2012年8月15日
 作    者   : w00176964
 修改内容   : 新生成函数
2.日    期   : 2015年1月14日
  作    者   : z00161729
  修改内容   : AT&T 支持DAM特性修改
3.日    期   : 2015年4月24日
  作    者   : z00161729
  修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID  NAS_MML_InitDisabledRatPlmnCfgInfo(
    NAS_MML_DISABLED_RAT_PLMN_CFG_INFO_STRU                *pstDisabledRatPlmnCfg
)
{
    /* 初始化带禁止接入技术的PLMN信息 */
    VOS_UINT32                          i;

    /* 初始化禁止接入技术的PLMN信息 */
    pstDisabledRatPlmnCfg->ulDisabledRatPlmnNum = 0;

    for ( i = 0 ; i < NAS_MML_MAX_DISABLED_RAT_PLMN_NUM; i++ )
    {
        pstDisabledRatPlmnCfg->astDisabledRatPlmnId[i].stPlmnWithRat.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
        pstDisabledRatPlmnCfg->astDisabledRatPlmnId[i].stPlmnWithRat.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
        pstDisabledRatPlmnCfg->astDisabledRatPlmnId[i].stPlmnWithRat.enRat = NAS_MML_NET_RAT_TYPE_BUTT;

        pstDisabledRatPlmnCfg->astDisabledRatPlmnId[i].ulPlmnDisabledForbiddenSlice   = NAS_MML_MAX_TIME_SLICE;
        pstDisabledRatPlmnCfg->astDisabledRatPlmnId[i].ulPlmnDisabledBeginSlice = 0;

        pstDisabledRatPlmnCfg->astDisabledRatPlmnId[i].enDisableLteReason = MMC_LMM_DISABLE_LTE_REASON_BUTT;
    }
}



/*****************************************************************************
函 数 名  : NAS_MML_InitUserCfgEHplmnInfo
功能描述  : 初始化用户配置的EHplmn列表信息
输入参数  : 无
输出参数  : pstUserCfgEhplmnInfo:用户配置的EHplmn列表信息
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期  : 2012年8月14日
  作    者  : w00167002
  修改内容  : 新生成函数
2.日    期  : 2014年12月22日
  作    者  : wx270776
  修改内容  : 扩充Ehplmn组

*****************************************************************************/
VOS_VOID  NAS_MML_InitUserCfgExtEHplmnInfo(
    NAS_MML_USER_CFG_EXT_EHPLMN_INFO_STRU  *pstUserCfgExtEhplmnInfo
)
{
    VOS_UINT32                          i;

    for (i = 0; i < NAS_MML_MAX_USER_CFG_EXT_EHPLMN_NUM; i++)
    {

        /* 初始化IMSI的PLMN LIST信息个数为0  */
        pstUserCfgExtEhplmnInfo->astUserCfgEhplmnInfo[i].ucImsiPlmnListNum = 0;
        PS_MEM_SET( pstUserCfgExtEhplmnInfo->astUserCfgEhplmnInfo[i].astImsiPlmnList,
                    (VOS_UINT8)0X00,
                    sizeof(pstUserCfgExtEhplmnInfo->astUserCfgEhplmnInfo[i].astImsiPlmnList));

        /* 初始化EHPLMN信息个数为0  */
        pstUserCfgExtEhplmnInfo->astUserCfgEhplmnInfo[i].ucEhplmnListNum = 0;
        PS_MEM_SET( pstUserCfgExtEhplmnInfo->astUserCfgEhplmnInfo[i].astEhPlmnList,
                    (VOS_UINT8)0X00,
                    sizeof(pstUserCfgExtEhplmnInfo->astUserCfgEhplmnInfo[i].astEhPlmnList));

        /* 初始化保留字段为0 */
        PS_MEM_SET( pstUserCfgExtEhplmnInfo->astUserCfgEhplmnInfo[i].aucResv,
                    (VOS_UINT8)0X00,
                    sizeof(pstUserCfgExtEhplmnInfo->astUserCfgEhplmnInfo[i].aucResv));
    }
    return;

}


/*****************************************************************************
函 数 名  : NAS_MML_InitMiscellaneousCfgInfo
功能描述  : 初始化搜网相关其他定制特性
输入参数  : 无
输出参数  : pstMiscellaneousCfg:初始化搜网相关其他定制特性
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期  : 2011年7月14日
 作    者   : zhoujun 40661
 修改内容   : 新生成函数
2.日    期  : 2011年7月29日
 作    者   : z00161729
 修改内容   : stk streer of roaming这个特性默认是支持的
3.日    期   : 2012年1月17日
  作    者   : w00167002
  修改内容   : DTS2011122006209:初始化RoamBroker未激活
4.日    期   : 2012年6月11日
  作    者   : w00166186
  修改内容   : AT&T&DCM项目
5.日    期   : 2014年02月13日
  作    者   : f62575
  修改内容   : DTS2014012902032: 禁止SVLTE产品出现双PS注册
6.日    期   : 2014年02月25日
  作    者   : z00161729
  修改内容   : DTS2014022206794:GCF 9.2.1.2.1b/9.2.3.2.3/9.2.1.2.1失败disable lte时rau需要从L获取安全上下文
7.日    期   : 2014年5月21日
  作    者   : w00167002
  修改内容   : DTS2014051602857:在SOR打开时候，如果CS注册失败达到4次，则等周期
                搜网定时器超时发起LIST搜网，如果当前仅有原有网络，则发起LAU,否则
                触发MM发起LAU;如果LIST搜后，发现有其他网络，则发起其他网络的搜网注册。
                手动选网时候，返回LIMIT CAMP ON,不再发起选网。
*****************************************************************************/
VOS_VOID  NAS_MML_InitMiscellaneousCfgInfo(
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU *pstMiscellaneousCfg
)
{
    pstMiscellaneousCfg->ucCsRejSearchSupportFlg            = VOS_FALSE;
    pstMiscellaneousCfg->ucStkSteeringOfRoamingSupportFlg   = VOS_TRUE;
    pstMiscellaneousCfg->ucMaxForbRoamLaFlg                 = VOS_FALSE;
    pstMiscellaneousCfg->ucMaxForbRoamLaNum                 = NAS_MML_DEFAULT_MAX_FORB_ROAM_LA_NUM;
    pstMiscellaneousCfg->ucNvGsmForbidFlg                   = VOS_FALSE;
    pstMiscellaneousCfg->ucRoamBrokerActiveFlag             = VOS_FALSE;
    pstMiscellaneousCfg->ucRoamBrokerRegisterFailCnt        = NAS_MML_MAX_CS_REG_FAIL_CNT;
    pstMiscellaneousCfg->ucSingleDomainFailPlmnSrchFlag     = VOS_FALSE;

    pstMiscellaneousCfg->stSingleDomainFailActionCtx.ucActiveFlag  = VOS_FALSE;
    pstMiscellaneousCfg->stSingleDomainFailActionCtx.ucCount       = 0;

    pstMiscellaneousCfg->ucRegFailNetWorkFailureCustomFlg          = VOS_FALSE;

    pstMiscellaneousCfg->ucCsOnlyDataServiceSupportFlg        = VOS_TRUE;

    NAS_MML_SetLteDisabledRauUseLteInfoFlag(VOS_FALSE);

    NAS_MML_InitSorAdditionalLauCtx();
}

/*****************************************************************************
函 数 名  : NAS_MML_InitCustomCfgInfo
功能描述  : 初始化客户定制特性
输入参数  : 无
输出参数  : pstCustomCfg:初始化客户定制特性
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2011年7月14日
  作    者   : zhoujun 40661
  修改内容   : 新生成函数
2.日    期   : 2012年3月17日
  作    者   : w00176964
  修改内容   : DTS2012031900095 V7R1 C30 SBM&EM定制需求:NV定制全局变量默认设置为不支持
3.日    期   : 2012年2月25日
  作    者   : w00167002
  修改内容   : V7R1C50 CSFB调整:初始化HO等系统消息时间
4.日    期   : 2012年5月15日
  作    者   : l00130025
  修改内容   : DTS2012012903053:Ts23.122 ch4.4.3.2.1 Auto user reselecton功能支持s
5.日    期   : 2012年8月14日
  作    者   : z00161729
  修改内容   : DCM定制需求和遗留问题修改,支持L紧急呼叫修改
6.日    期   : 2012年8月14日
  作    者   : t00212959
  修改内容   : DCM定制需求和遗留问题修改,比较3位MNC
7.日    期   : 2012年10月8日
  作    者   : z00161729
  修改内容   : DTS2012083007796:无卡支持语音业务时开机应优先选择gu下anycell驻留
8.日    期   : 2012年11月29日
  作    者   : w00176964
  修改内容   : DTS2012112902395:增加HPLMN上注册控制标记
9.日    期   : 2013年4月10日
  作    者   : w00176964
  修改内容   : 增加H3G控制标记
10.日    期   : 2013年05月23日
  作    者   : z00234330
  修改内容   : DTS2013052301419:增加ISR激活标志
11.日    期   : 2013年7月25日
  作    者    : w00242748
  修改内容    : DTS2013072200933:vodafone r8网络csfb mt到w，cs ps链接释放后1.5s内重选回l，
                网络后续2s左右会重新下发paging消息，存在丢寻呼被叫打不通，参考标杆实现，
                rau req中带follow on标志,无明确协议依据
12.日    期   : 2013年10月09日
   作    者   : l00208543
   修改内容   : DTS2013100904573
13.日    期   : 2013年10月15日
  作    者    : s00190137
  修改内容    : 增加非HPLMN/RPLMN网络下接入禁止后是否搜网标记
                增加电信内置OPLMN列表定制需求，NV定制全局变量默认设置为不支持
14.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式

 15.日    期   : 2014年01月10日
   作    者   : w00176964
   修改内容   : VoLTE_PhaseIII项目
16.日    期   : 2014年01月17日
   作    者   : l00198894
   修改内容   : V9R1C53 C+L 离网重选项目
17.日    期   : 2014年05月30日
   作    者   : s00217060
   修改内容   : 初始化不支持utran flash csfb
18.日    期   : 2013年7月25日
   作    者   : w00242748
   修改内容   : DTS2014053105098:CSFB mo是否需要带follow on增加NV控制
19.日    期   : 2014年7月17日
   作    者   : b00269685
   修改内容   : DSDS IV增加end session延时
20.日    期   : 2014年10月10日
   作    者   : b00269685
   修改内容   : 增加是否支持srvcc标志
21.日    期   : 2014年11月10日
   作    者   : s00217060
   修改内容   : 初始化支持utran flash csfb
22.日    期   : 2014年10月20日
   作    者   : h00285180
   修改内容   : 拒绝原因值优化PhaseII DTS2014110307415
23.日    期   : 2015年1月4日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改
24.日    期   : 2015年4月25日
  作    者   : z00161729
  修改内容   : 24301 R11 CR升级项目修改
25.日    期   : 2015年7月17日
   作    者   : z00161729
   修改内容   : DTS2015071505434:rau或attach请求不带follow on，网络回复attach accept或rau accept中携带follow on proceed标识，gmm需要
                增加判断如果ps rab存在或存在rabm重建或sm业务请求或cds存在缓存数据则不启动T3340，否则启动t3340开启网络防呆功能
26.日    期   : 2015年8月26日
   作    者   : c00318887
   修改内容   : for 预置频点搜网优化
27.日    期   : 2015年9月17日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
 28.日    期   : 2016年1月20日
    作    者   : c00318887
    修改内容   : DTS2015123110917: usim卡在GSM下做2G鉴权后，csfb到3G下鉴权错误
*****************************************************************************/
VOS_VOID  NAS_MML_InitCustomCfgInfo(
    NAS_MML_CUSTOM_CFG_INFO_STRU        *pstCustomCfg
)
{
    NAS_MML_InitRplmnCfgInfo(&(pstCustomCfg->stRplmnCfg));

    NAS_MML_InitHplmnCfgInfo(&(pstCustomCfg->stHplmnCfg));

    NAS_MML_InitRoamCfgInfo(&(pstCustomCfg->stRoamCfg));

    NAS_MML_InitBgSearchCfgInfo(&(pstCustomCfg->stBgSearchCfg));

    NAS_MML_InitPlmnLockCfgInfo(&(pstCustomCfg->stPlmnLockCfg));
    NAS_MML_SetHoWaitSysinfoTimerLen(NAS_MML_HO_WAIT_SYS_INFO_DEFAULT_LEN_VALUE);

    NAS_MML_InitMiscellaneousCfgInfo(&(pstCustomCfg->stMiscellaneousCfg));

#if (FEATURE_ON == FEATURE_LTE)
    /* 默认允许LTE国际漫游 */
    NAS_MML_SetLteRoamAllowedFlg(VOS_TRUE);
#endif

    NAS_MML_SetDailRejectCfg(VOS_FALSE);


    NAS_MML_InitChangeNWCauseInfo(&(pstCustomCfg->stChangeNWCauseInfo));
    NAS_MML_InitRoamingRejectNoRetryInfo(&(pstCustomCfg->stRoamingRejectNoRetryInfo));

    NAS_MML_SetUserAutoReselActiveFlg(VOS_FALSE);

    NAS_MML_InitHplmnAuthRejCounter(&(pstCustomCfg->stIgnoreAuthRejInfo));


    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, begin */
    NAS_MML_SetCsfbEmgCallLaiChgLauFirstFlg(VOS_FALSE);
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, end */

    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-15, begin */
    NAS_MML_SetPlmnExactlyComparaFlg(VOS_FALSE);
    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-15, end */

    /* 默认支持cs语音业务 */
    NAS_MML_SetSupportCsServiceFLg(VOS_TRUE);

    NAS_MML_SetHplmnRegisterCtrlFlg(VOS_FALSE);

    /* 默认支持H3G定制特性 */
    NAS_MML_SetH3gCtrlFlg(VOS_TRUE);

#if (FEATURE_ON == FEATURE_LTE)
    /* 默认enable lte定时器时长为0分钟 */
    NAS_MML_SetCsfbEmgCallEnableLteTimerLen(0);

    NAS_MML_SetCsPsMode13GPPEnableLteTimerLen(0);

    /* Modified by c00318887 for 移植T3402 , 2015-6-17, begin */
    NAS_MML_SetDisableLteStartT3402EnableLteFlag(VOS_FALSE);
    NAS_MML_SetHighPrioRatBgEnableLteFlag(NAS_MML_HIGH_PRIO_RAT_BG_SEARCH_PROC_LTE_ENABLE_LTE);
    /* Modified by c00318887 for 移植T3402 , 2015-6-17, end */


    NAS_MML_SetVoiceNotAvailPlmnForbiddenPeriod(0);

    /* 默认支持ISR */
    NAS_MML_SetIsrSupportFlg(VOS_TRUE);
    NAS_MML_SetIsRauNeedFollowOnCsfbMtFlg(VOS_FALSE);

    NAS_MML_SetIsRauNeedFollowOnCsfbMoFlg(VOS_FALSE);

    NAS_MML_SetIsDelFddBandSwitchOnFlg(VOS_FALSE);
#endif

    NAS_MML_SetCsgSupportFlag(VOS_FALSE);
    NAS_MML_SetOnlyReportOperatorCsgListFlag(VOS_FALSE);

    /* 默认不支持SVLTE特性 */
    NAS_MML_SetSvlteSupportFlag(VOS_FALSE);

    NAS_MML_SetPsTransferOffAreaModeFlag(VOS_FALSE);

    NAS_MML_SetDsdsRfShareFlg(VOS_FALSE);

    /* 默认不支持接入禁止发起PLMN搜网特性 */
    NAS_MML_SetSupportAccBarPlmnSearchFlg(VOS_FALSE);

    NAS_MML_InitUserCfgOPlmnInfo(&(pstCustomCfg->stUserCfgOPlmnInfo));

    NAS_MML_InitRatForbiddenList(&(pstCustomCfg->stRatForbiddenListInfo));
    NAS_MML_InitRatForbiddenStatusCfg(&(pstCustomCfg->stRatFirbiddenStatusCfg));
    NAS_MML_SetImsVoiceInterSysLauEnableFlg(VOS_FALSE);
    NAS_MML_SetImsVoiceMMEnableFlg(VOS_FALSE);

    NAS_MML_SetLcEnableFlg(VOS_FALSE);

    /* ultra flash csfb不支持，FR NV打开时，MO电话CSFB，CS域HO到GU,mm在connective active不处理系统消息，
       等链接释放之后再重新驻留才能处理。而如果FR打开，链接释放之后不会驻留，而是FR回LTE，导致电话失败 */
    NAS_MML_SetUltraFlashCsfbSupportFlg(VOS_TRUE);

    NAS_MML_Set3GPP2UplmnNotPrefFlg(VOS_TRUE);

    NAS_MML_InitDsdsSessionEndDelay(&(pstCustomCfg->stDsdsEndSesssionDelay));

    NAS_MML_SetSupportSrvccFlg(VOS_FALSE);

    NAS_MML_SetRelPsSigConFlg(VOS_FALSE);
    NAS_MML_SetRelPsSigConCfg_T3340TimerLen(0);

    NAS_MML_SetPdpExistNotStartT3340Flag(VOS_TRUE);


    /* 默认当前不是DSDS多卡 */
    NAS_MML_SetDsdsMultiModemModeFlg(VOS_FALSE);

    NAS_MML_InitDamPlmnInfoCfg(&pstCustomCfg->stDamPlmnInfoCfg);

    /* 设置enable lte触发搜网标识为VOS_FALSE */
    NAS_MML_SetEnableLteTrigPlmnSearchFlag(VOS_FALSE);
    NAS_MML_SetAddDamPlmnInDisablePlmnWithRatListFlag(VOS_FALSE);
    NAS_MML_SetCsmoSupportedFlg(VOS_FALSE);

    NAS_MML_InitT3212TimerCfgInfo(&(pstCustomCfg->stT3212Info));

    NAS_MML_SetHplmnInEplmnDisplayHomeFlg(VOS_FALSE);

    NAS_MML_SetProtectMtCsfbPagingProcedureLen(NAS_MML_PROTECT_MT_CSFB_PAGING_PROCEDURE_DEFAULT_LEN);

    NAS_MML_SetDeleteRplmnWhenEplmnInvalidFlg(VOS_TRUE);

    NAS_MML_SetEpsRejByCause14InVplmnAllowPsRegFlg(VOS_FALSE);
    NAS_MML_SetPsRegFailMaxTimesTrigLauOnceFlg(VOS_FALSE);
    NAS_MML_SetKeepSrchHplmnEvenRejByCause13Flg(VOS_FALSE);
    NAS_MML_InitCarryEplmnWhenSrchRplmnCfg(&(pstCustomCfg->stCarryEplmnWhenSrchRplmnCfg));
    NAS_MML_InitLauRejNoRetryWhenCmSrvExistCfg(&(pstCustomCfg->stLauRejNoRetryWhenCmSrvExistCfgInfo));
    NAS_MML_InitLauRejTrigPlmnSearchCfg(&(pstCustomCfg->stLauRejTrigPlmnSearchCfg));

    NAS_MML_InitGetGeoPrioRatList(&(pstCustomCfg->stGetGeoPrioRatList));

    NAS_MML_InitLteOos2GPrefPlmnSelCfg(&(pstCustomCfg->stLteOos2GPrefPlmnSelCfg));

    NAS_MML_InitForbLaWithValidPeriodCfg(&(pstCustomCfg->stForbLaWithValidPeriodCfg));

    NAS_MML_SetKeepCsForbInfoCfg(VOS_FALSE);

    NAS_MML_InitUsimGsmAuthCfgInfo(&(pstCustomCfg->stCleanCksnCfg));
    
    return;
}


/*****************************************************************************
 函 数 名  : NAS_MML_InitMsCfgCtx
 功能描述  : 初始化MML_CTX中手机配置相关信息
 输入参数  : pstMsCfgInfo:手机配置信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月30日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_InitMsCfgCtx(
    NAS_MML_MS_CFG_INFO_STRU           *pstMsCfgInfo
)
{
    NAS_MML_InitMs3GppRel(&(pstMsCfgInfo->stMs3GppRel));

    NAS_MML_InitMsCapability(&(pstMsCfgInfo->stMsCapability));

    NAS_MML_InitMsSysCfgInfo(&(pstMsCfgInfo->stMsSysCfgInfo));

    NAS_MML_InitCustomCfgInfo(&(pstMsCfgInfo->stCustomCfg));
}
/*****************************************************************************
 函 数 名  : NAS_MML_InitCampRai
 功能描述  : RAI = PLMN+ LAC+RAC, 将当前驻留PLMN，LAC,RAC更新为无效值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年8月5日
   作    者   : l00130025
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_InitCampRai(
    NAS_MML_CAMP_PLMN_INFO_STRU         *pstCampPlmnInfo
)
{
    /* 将当前驻留PLMN，LAI,RAC更新为无效值 */
    pstCampPlmnInfo->stLai.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    pstCampPlmnInfo->stLai.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    pstCampPlmnInfo->stLai.aucLac[0]      = NAS_MML_LAC_LOW_BYTE_INVALID;
    pstCampPlmnInfo->stLai.aucLac[1]      = NAS_MML_LAC_HIGH_BYTE_INVALID;
    pstCampPlmnInfo->ucRac                = NAS_MML_RAC_INVALID;

    return;
}
/*****************************************************************************
 函 数 名  : NAS_MML_InitRssiValue
 功能描述  : 初始化G和W的Rssi的值
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月29日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年4月9日
    作    者   : l00130025
    修改内容   : DTS2012033006643,搜网未成功时，CSQ查询返回空值
  3.日    期   : 2012年11月21日
    作    者   : z00161729
    修改内容   : 支持cerssi和nmr
  4.日    期   : 2014年2月12日
    作    者   : s00246516
    修改内容   : L-C互操作项目:增加获取和注册请求的处理
*****************************************************************************/
VOS_VOID NAS_MML_InitRssiValue(
    NAS_MML_CAMP_CELL_INFO_STRU        *pstCampCellInfo
)
{
    VOS_UINT8                           i;
    pstCampCellInfo->ucRssiNum = 1;

    for ( i = 0; i < RRC_NAS_AT_CELL_MAX_NUM; i++ )
    {
        pstCampCellInfo->astRssiInfo[i].sRscpValue      = NAS_MML_UTRA_RSCP_UNVALID;
        pstCampCellInfo->astRssiInfo[i].sRssiValue      = NAS_MML_RSSI_UNVALID;

        pstCampCellInfo->astRssiInfo[i].ucChannalQual   = NAS_MML_UTRA_BLER_INVALID;
        pstCampCellInfo->astRssiInfo[i].ucRssiLevel     = NAS_MML_LOWER_RSSI_LEVEL;
    }

    pstCampCellInfo->ucCellNum    = 0;
    pstCampCellInfo->sUeRfPower   = NAS_MML_UE_RFPOWER_INVALID;
    pstCampCellInfo->usCellDlFreq = NAS_MML_UE_FREQ_INVALID;
    pstCampCellInfo->usCellUlFreq = NAS_MML_UE_FREQ_INVALID;

    for ( i = 0; i < RRC_NAS_AT_CELL_MAX_NUM; i++ )
    {
        pstCampCellInfo->astCellInfo[i].sCellRSCP = NAS_MML_UTRA_RSCP_UNVALID;

        pstCampCellInfo->astCellInfo[i].sCellRssi = NAS_MML_RSSI_UNVALID;

        pstCampCellInfo->astCellInfo[i].ulCellId  = NAS_MML_CELLID_INVALID;
    }

    /* Added by s00246516 for L-C互操作项目, 2014-02-12, Begin */
    pstCampCellInfo->ulArfcn                      = 0x0;
    /* Added by s00246516 for L-C互操作项目, 2014-02-12, End */
}


/*****************************************************************************
函 数 名  : NAS_MML_InitRrcNcellInfo
功能描述  : 初始化当前临区网络信息
输入参数  : 无
输出参数  : pstCampPlmnInfo:初始化当前驻留网络信息
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
  1.日    期   : 2014年01月02日
    作    者   : z00234330
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_InitRrcNcellInfo(
    NAS_MML_RRC_NCELL_INFO_STRU         *pstRrcNcellInfo
)
{
    PS_MEM_SET(pstRrcNcellInfo,0x00,sizeof(NAS_MML_RRC_NCELL_INFO_STRU));
    pstRrcNcellInfo->ucLteNcellExist     = VOS_FALSE;
    pstRrcNcellInfo->ucUtranNcellExist   = VOS_FALSE;
}


/*****************************************************************************
函 数 名  : NAS_MML_InitCampPlmnInfo
功能描述  : 初始化当前驻留网络信息
输入参数  : 无
输出参数  : pstCampPlmnInfo:初始化当前驻留网络信息
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
  1.日    期   : 2011年7月14日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数
  2.日    期   : 2013年01月12日
    作    者   : l65478
    修改内容   : DTS2012011201289
  3.日    期   : 2014年04月28日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目调整
  4.日    期   : 2014年8月14日
    作    者   : s00217060
    修改内容   : DTS2014080700822:初始化LMM AccessType为BUTT

*****************************************************************************/
VOS_VOID  NAS_MML_InitCampPlmnInfo(
    NAS_MML_CAMP_PLMN_INFO_STRU         *pstCampPlmnInfo
)
{
    pstCampPlmnInfo->enNetRatType                              = NAS_MML_NET_RAT_TYPE_BUTT;
    pstCampPlmnInfo->enNetworkMode                             = NAS_MML_NET_MODE_BUTT;
    pstCampPlmnInfo->enSysSubMode                              = RRC_NAS_SYS_SUBMODE_BUTT;

    NAS_MML_InitCampRai(pstCampPlmnInfo);

    /* Added by w00176964 for V3R3C60_eCall项目, 2014-4-28, begin */
    NAS_MML_InitOldCampLai(&pstCampPlmnInfo->stOldLai);
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-4-28, end */

    pstCampPlmnInfo->stOperatorNameInfo.stOperatorPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    pstCampPlmnInfo->stOperatorNameInfo.stOperatorPlmnId.ulMnc = NAS_MML_INVALID_MNC;

    PS_MEM_SET(pstCampPlmnInfo->stOperatorNameInfo.aucOperatorNameLong, 0, NAS_MML_MAX_OPER_LONG_NAME_LEN);
    PS_MEM_SET(pstCampPlmnInfo->stOperatorNameInfo.aucOperatorNameShort, 0, NAS_MML_MAX_OPER_SHORT_NAME_LEN);

    NAS_MML_InitRrcNcellInfo(&(pstCampPlmnInfo->stRrcNcellInfo));

    NAS_MML_InitRssiValue(&(pstCampPlmnInfo->stCampCellInfo));

    pstCampPlmnInfo->enLmmAccessType    = NAS_MML_LMM_ACCESS_TYPE_BUTT;
}

/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-28, begin */
/*****************************************************************************
 函 数 名  : NAS_MML_InitOldCampLai
 功能描述  : RAI = PLMN+ LAC+RAC, 将上次驻留PLMN，LAC,RAC更新为无效值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年4月28日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_InitOldCampLai(
    NAS_MML_LAI_STRU                   *pstLaiInfo
)
{
    /* 将上次驻留PLMN，LAI,RAC更新为无效值 */
    pstLaiInfo->stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    pstLaiInfo->stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    pstLaiInfo->aucLac[0]      = NAS_MML_LAC_LOW_BYTE_INVALID;
    pstLaiInfo->aucLac[1]      = NAS_MML_LAC_HIGH_BYTE_INVALID;

    return;
}

/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-28, end */


/*****************************************************************************
函 数 名  : NAS_MML_InitCsDomainInfo
功能描述  : 初始化当前CS域相关信息
输入参数  : 无
输出参数  : pstCsDomainInfo:初始化当前CS域相关信息
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期  : 2011年7月14日
 作    者   : zhoujun 40661
 修改内容   : 新生成函数
2.日    期   : 2012年2月15日
  作    者   : w00166186
  修改内容   : CSFB&PPAC&ETWS&ISR 开发
3.日    期   : 2012年12月11日
  作    者   : w00176964
  修改内容   : 修改变量名
4.日    期   : 2013年05月21日
  作    者   : s46746
  修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
5.日    期   : 2015年10月16日
  作    者   : j00174725
  修改内容   : DTS2015101603066
5.日    期   : 2016年1月8日
  作    者   : z00359541
  修改内容   : DTS2015111402223:增加小区是否支持CSMO标识
*****************************************************************************/
VOS_VOID  NAS_MML_InitCsDomainInfo(
    NAS_MML_CS_DOMAIN_INFO_STRU         *pstCsDomainInfo
)
{
    pstCsDomainInfo->ucAttFlg                               = VOS_TRUE;
    pstCsDomainInfo->ucCsAttachAllow                        = VOS_TRUE;

    pstCsDomainInfo->enCsRegStatus                          = NAS_MML_REG_STATUS_BUTT;

    pstCsDomainInfo->stCsAcRestriction.ucRestrictPagingRsp  = VOS_FALSE;
    pstCsDomainInfo->stCsAcRestriction.ucRestrictRegister   = VOS_FALSE;
    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    pstCsDomainInfo->stCsAcRestriction.ucRestrictNormalService      = VOS_FALSE;
    pstCsDomainInfo->stCsAcRestriction.ucRestrictEmergencyService   = VOS_FALSE;
    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */

    pstCsDomainInfo->ucCsSupportFlg                         = VOS_FALSE;
    pstCsDomainInfo->ulCsDrxLen                             = NAS_MML_CS_INVALID_DRX_LEN;
    pstCsDomainInfo->ulCsRegisterBarToUnBarFlag             = VOS_FALSE;
    pstCsDomainInfo->ulT3212Len                     = NAS_MML_T3212_INFINITE_TIMEOUT_VALUE;
    pstCsDomainInfo->stLastSuccLai.stPlmnId.ulMcc   = NAS_MML_INVALID_MCC;
    pstCsDomainInfo->stLastSuccLai.stPlmnId.ulMnc   = NAS_MML_INVALID_MNC;
    pstCsDomainInfo->stLastSuccLai.aucLac[0]        = NAS_MML_LAC_LOW_BYTE_INVALID;
    pstCsDomainInfo->stLastSuccLai.aucLac[1]        = NAS_MML_LAC_HIGH_BYTE_INVALID;
    pstCsDomainInfo->stLastSuccLai.ucRac = NAS_MML_RAC_INVALID;

    pstCsDomainInfo->stCmSrvStatus.enMoCallStatus   = NAS_MML_CALL_STATUS_BUTT;
    pstCsDomainInfo->stCmSrvStatus.enMoSsStatus     = NAS_MML_SS_STATUS_BUTT;

    pstCsDomainInfo->stCmSrvStatus.enMtCsfbPagingTimerStatus = NAS_MML_MT_CSFB_PAGING_TIMER_STOP;

    pstCsDomainInfo->stCmSrvStatus.ucCellNotSupportCsmoFlg   =   VOS_FALSE;
}


/*****************************************************************************
函 数 名  : NAS_MML_InitPsDomainInfo
功能描述  : 初始化当前PS域相关信息
输入参数  : 无
输出参数  : pstPsDomainInfo:初始化当前PS域相关信息
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期  : 2011年7月14日
 作    者   : zhoujun 40661
 修改内容   : 新生成函数
2.日    期   : 2012年2月15日
  作    者   : w00166186
  修改内容   : CSFB&PPAC&ETWS&ISR 开发
3.日    期   : 2012年8月15日
  作    者   : t00212959
  修改内容   : DCM定制需求和遗留问题
4.日    期   : 2012年12月11日
  作    者   : w00176964
  修改内容   : 修改变量名
5.日    期   : 2013年05月21日
  作    者   : s46746
  修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
6.日    期   : 2014年1月4日
  作    者   : z00161729
  修改内容   : SVLTE优化G-TL ps切换性能修改
7.日    期   : 2014年01月10日
  作    者   : w00176964
  修改内容   : VoLTE_PhaseIII项目
8.日    期   : 2015年4月21日
  作    者   : z00161729
  修改内容   : 24301 R11 CR升级项目修改

*****************************************************************************/
VOS_VOID  NAS_MML_InitPsDomainInfo(
    NAS_MML_PS_DOMAIN_INFO_STRU         *pstPsDomainInfo
)
{
    pstPsDomainInfo->ucPsAttachAllow                    = VOS_FALSE;

    pstPsDomainInfo->enPsRegStatus                      = NAS_MML_REG_STATUS_BUTT;

    pstPsDomainInfo->stPsAcRestriction.ucRestrictPagingRsp  = VOS_FALSE;
    pstPsDomainInfo->stPsAcRestriction.ucRestrictRegister   = VOS_FALSE;
    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    pstPsDomainInfo->stPsAcRestriction.ucRestrictNormalService      = VOS_FALSE;
    pstPsDomainInfo->stPsAcRestriction.ucRestrictEmergencyService   = VOS_FALSE;
    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */
    pstPsDomainInfo->ucPsSupportFlg                     = VOS_FALSE;
    pstPsDomainInfo->ulPsRegisterBarToUnBarFlag         = VOS_FALSE;
    pstPsDomainInfo->stLastSuccRai.stLai.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    pstPsDomainInfo->stLastSuccRai.stLai.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    pstPsDomainInfo->stLastSuccRai.stLai.aucLac[0]      = NAS_MML_LAC_LOW_BYTE_INVALID;
    pstPsDomainInfo->stLastSuccRai.stLai.aucLac[1]      = NAS_MML_LAC_HIGH_BYTE_INVALID;

    /* Modified by t00212959 for DCM定制需求和遗留问题, 2012-8-13, begin */
    pstPsDomainInfo->stPsDomainDrxPara.enPsRegisterContainDrx = NAS_MML_PS_REG_CONTAIN_BUTT;
    pstPsDomainInfo->stPsDomainDrxPara.ucNonDrxTimer          = NAS_MML_PS_DEFAULT_NON_DRX_TIMER;
    pstPsDomainInfo->stPsDomainDrxPara.ucUeUtranPsDrxLen      = NAS_MML_PS_UE_UTRAN_DEFAULT_DRX_LEN;
    pstPsDomainInfo->stPsDomainDrxPara.ucWSysInfoDrxLen       = NAS_MML_PS_UE_UTRAN_DEFAULT_DRX_LEN;
    pstPsDomainInfo->stPsDomainDrxPara.ucUeEutranPsDrxLen     = NAS_MML_PS_UE_LTE_DEFAULT_DRX_LEN;
    pstPsDomainInfo->stPsDomainDrxPara.ucLSysInfoDrxLen       = NAS_MML_PS_UE_LTE_DEFAULT_DRX_LEN;
    pstPsDomainInfo->stPsDomainDrxPara.ucSplitOnCcch          = NAS_MML_PS_DEFAULT_DRX_SPLIT_ON_CCCH;
    pstPsDomainInfo->stPsDomainDrxPara.ucSplitPgCycleCode     = NAS_MML_PS_DEFAULT_DRX_SPLIT_PG_CYCLE_CODE;
    /* Modified by t00212959 for DCM定制需求和遗留问题, 2012-8-13, end */

    NAS_MML_SetPsLocalDetachFlag(VOS_FALSE);

    NAS_MML_SetGmmProcFlag(NAS_MML_GMM_PROC_FLAG_INVALID);
    NAS_MML_SetGmmProcType(NAS_MML_GMM_PROC_TYPE_INVALID);
    NAS_MML_SetSmProcFlag(NAS_MML_SM_PROC_FLAG_INVALID);

#if (FEATURE_ON == FEATURE_IMS)
    NAS_MML_SetGUNwImsVoiceSupportFlg(NAS_MML_NW_IMS_VOICE_NOT_SUPPORTED);
#endif

}

/*****************************************************************************
函 数 名  : NAS_MML_InitMsCurrBandInfoInfo
功能描述  : 初始化MS当前驻留的频段信息
输入参数  : 无
输出参数  : pstMsBandInfo:初始化MS当前频段相关信息
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期  : 2011年7月14日
 作    者   : zhoujun 40661
 修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_InitMsCurrBandInfoInfo(
    NAS_MML_MS_BAND_INFO_STRU         *pstMsBandInfo
)
{
    /* GSM的当前驻留的Band */
    pstMsBandInfo->unGsmBand.stBitBand.BandGsm1800          = VOS_FALSE;
    pstMsBandInfo->unGsmBand.stBitBand.BandGsm1900          = VOS_FALSE;
    pstMsBandInfo->unGsmBand.stBitBand.BandGsm450           = VOS_FALSE;
    pstMsBandInfo->unGsmBand.stBitBand.BandGsm480           = VOS_FALSE;
    pstMsBandInfo->unGsmBand.stBitBand.BandGsm700           = VOS_FALSE;
    pstMsBandInfo->unGsmBand.stBitBand.BandGsm850           = VOS_FALSE;
    pstMsBandInfo->unGsmBand.stBitBand.BandGsmE900          = VOS_FALSE;
    pstMsBandInfo->unGsmBand.stBitBand.BandGsmP900          = VOS_FALSE;
    pstMsBandInfo->unGsmBand.stBitBand.BandGsmR900          = VOS_FALSE;

    /* WCDMA的当前驻留的Band */
    pstMsBandInfo->unWcdmaBand.stBitBand.BandWCDMA_III_1800 = VOS_FALSE;
    pstMsBandInfo->unWcdmaBand.stBitBand.BandWCDMA_II_1900  = VOS_FALSE;
    pstMsBandInfo->unWcdmaBand.stBitBand.BandWCDMA_IV_1700  = VOS_FALSE;
    pstMsBandInfo->unWcdmaBand.stBitBand.BandWCDMA_IX_J1700 = VOS_FALSE;
    pstMsBandInfo->unWcdmaBand.stBitBand.BandWCDMA_I_2100   = VOS_FALSE;
    pstMsBandInfo->unWcdmaBand.stBitBand.BandWCDMA_VIII_900 = VOS_FALSE;
    pstMsBandInfo->unWcdmaBand.stBitBand.BandWCDMA_VII_2600 = VOS_FALSE;
    pstMsBandInfo->unWcdmaBand.stBitBand.BandWCDMA_VI_800   = VOS_FALSE;
    pstMsBandInfo->unWcdmaBand.stBitBand.BandWCDMA_V_850    = VOS_FALSE;

    /* LTE的当前驻留的的Band */
    pstMsBandInfo->stLteBand.aulLteBand[0]                  = NAS_MML_LTE_ALL_BAND_INVALID;
    pstMsBandInfo->stLteBand.aulLteBand[1]                  = NAS_MML_LTE_ALL_BAND_INVALID;
}

/*****************************************************************************
函 数 名  : NAS_MML_InitNetwork3GppRel
功能描述  : 初始化MS当前驻留网络的协议版本
输入参数  : 无
输出参数  : pstMsBandInfo:初始化MS当前驻留网络的协议版本
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期  : 2011年7月14日
 作    者   : zhoujun 40661
 修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_InitNetwork3GppRel(
    NAS_MML_NETWORK_3GPP_REL_STRU      *pstNetwork3GppRel
)
{
    pstNetwork3GppRel->enNetMscRel      = NAS_MML_NETWORK_MSG_REL_VER_BUTT;
    pstNetwork3GppRel->enNetSgsnRel     = NAS_MML_NETWORK_SGSN_REL_VER_BUTT;
}


/*****************************************************************************
函 数 名  : NAS_MML_InitEquPlmnInfo
功能描述  : 初始化EPLMN信息
输入参数  : pstEquPlmnInfo:初始化EPLMN信息
输出参数  : 无
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2011年7月14日
  作    者   : zhoujun 40661
  修改内容   : 新生成函数
2.日    期   : 2012年10月26日
  作    者   : W00176964
  修改内容   : DTS2012090303157:初始化EPLMN有效标记
*****************************************************************************/
VOS_VOID  NAS_MML_InitEquPlmnInfo(
    NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo
)
{
    VOS_UINT32                          i;

    pstEquPlmnInfo->ucEquPlmnNum    = 0;
    for ( i = 0 ; i < NAS_MML_MAX_EQUPLMN_NUM ; i++ )
    {
        pstEquPlmnInfo->astEquPlmnAddr[i].ulMcc = NAS_MML_INVALID_MCC;
        pstEquPlmnInfo->astEquPlmnAddr[i].ulMnc = NAS_MML_INVALID_MNC;
    }

    pstEquPlmnInfo->ucValidFlg = VOS_FALSE;
}

/*****************************************************************************
函 数 名  : NAS_MML_InitConnStatusInfo
功能描述  : 初始化当前链接状态信息
输入参数  : 无
输出参数  : pstConnStatus:初始化当前连接状态
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期  : 2011年7月14日
  作    者   : zhoujun 40661
  修改内容   : 新生成函数
2.日    期   : 2011年10月11日
  作    者   : l00171473
  修改内容   : V7R1 phase II, TC环回调整，增加PS TC业务存在标志
3.日    期   : 2012年3月8日
  作    者   : w00167002
  修改内容   : CSFB调整:Csfb Service Status初始化
4.日    期   : 2013年12月13日
  作    者   : s00217060
  修改内容   : VoLTE_PhaseIII项目:ucEmcPdnStatusFlg初始化
*****************************************************************************/
VOS_VOID  NAS_MML_InitConnStatusInfo(
    NAS_MML_CONN_STATUS_INFO_STRU       *pstConnStatus
)
{
    pstConnStatus->ucCsSigConnStatusFlg         =   VOS_FALSE;
    pstConnStatus->ucPsSigConnStatusFlg         =   VOS_FALSE;
    pstConnStatus->ucPsTbfStatusFlg             =   VOS_FALSE;
    pstConnStatus->ucRrcStatusFlg               =   VOS_FALSE;
    pstConnStatus->ucCsServiceConnStatusFlg     =   VOS_FALSE;
    pstConnStatus->ucCsServiceBufferFlg         =   VOS_FALSE;
    pstConnStatus->ucPsServiceBufferFlg         =   VOS_FALSE;
    pstConnStatus->ucPdpStatusFlg               =   VOS_FALSE;
    pstConnStatus->ucEpsSigConnStatusFlg        =   VOS_FALSE;
    pstConnStatus->ucEpsServiceConnStatusFlg    =   VOS_FALSE;
    pstConnStatus->ucEmergencyServiceFlg        =   VOS_FALSE;
    pstConnStatus->ucPsTcServiceFlg             =   VOS_FALSE;
    /* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-13, begin */
    pstConnStatus->ucEmcPdpStatusFlg            =   VOS_FALSE;
    /* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-13, end */


    pstConnStatus->enCsfbServiceStatus          =   NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST;

    PS_MEM_SET(pstConnStatus->aucReserved, 0x0, sizeof(pstConnStatus->aucReserved));
}

/*****************************************************************************
函 数 名  : NAS_MML_InitEpsDomainInfo
功能描述  : 初始化EPS域相关信息
输入参数  : 无
输出参数  : pstEpsDomainInfo-EPS域相关信息
返 回 值  : 无
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2012年3月1日
  作    者   : z00161729
  修改内容   : 新生成函数
2.日    期   : 2012年4月18日
  作    者   : l00130025
  修改内容   : DTS2012040200480,单独维护EPS注册状态,供L模下CEREG/CGREG查询和上报使用
3.日    期   : 2013年12月30日
  作    者   : f00261443
  修改内容   : 增加初始化Lte Ims Voice 能力
4.日    期   : 2015年1月5日
  作    者   : z00161729
  修改内容   : AT&T 支持DAM特性修改

*****************************************************************************/
VOS_VOID NAS_MML_InitEpsDomainInfo(
    NAS_MML_EPS_DOMAIN_INFO_STRU       *pstEpsDomainInfo
)
{
   pstEpsDomainInfo->enT3412Status            = NAS_MML_TIMER_STOP;
   pstEpsDomainInfo->enT3423Status            = NAS_MML_TIMER_STOP;
   pstEpsDomainInfo->enT3402Status            = NAS_MML_TIMER_STOP;
   pstEpsDomainInfo->enAdditionUpdateRsltInfo = NAS_MML_ADDITION_UPDATE_RSLT_BUTT;
   pstEpsDomainInfo->enEpsRegStatus           = NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH;
   pstEpsDomainInfo->enNwImsVoCap             = NAS_MML_NW_IMS_VOICE_NOT_SUPPORTED;

   /* 设置T3402定时器时长默认12分钟 */
   NAS_MML_SetT3402Len(NAS_MML_DEFAULT_T3402_LEN);

   return;
}

/*****************************************************************************
函 数 名  : NAS_MML_InitImsDomainInfo
功能描述  : 初始化Ims域相关信息
输入参数  : 无
输出参数  : pstImsDomainInfo-Ims域相关信息
返 回 值  : 无
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2013年12月28日
  作    者   : f00261443
  修改内容   : 新生成函数
2.日    期   : 2015年4月28日
  作    者   : z00161729
  修改内容   : 24301 R11 CR升级项目修改

*****************************************************************************/
VOS_VOID NAS_MML_InitImsDomainInfo(
    NAS_MML_IMS_DOMAIN_INFO_STRU        *pstImsDomainInfo
)
{
    pstImsDomainInfo->ucImsVoiceAvail   = VOS_FALSE;
    pstImsDomainInfo->enImsNormalRegSta = NAS_MML_IMS_NORMAL_REG_STATUS_DEREG;
    pstImsDomainInfo->ucImsCallFlg      = VOS_FALSE;

    NAS_MML_SetPersistentBearerState(NAS_MML_PERSISTENT_BEARER_STATE_NOT_EXIST);
}

/*****************************************************************************
 函 数 名  : NAS_MML_InitPsBearerContext
 功能描述  : 初始化PS承载上下文信息
 输入参数  : 无
 输出参数  : pstPsBearerCtx-EPS域相关信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2012年3月5日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年3月15日
    作    者   : l65478
    修改内容   : DTS2013120300990:在PDP激活过程中发起RAU,第一次PDP激活失败

  3.日    期   : 2014年12月06日
    作    者   : A00165503
    修改内容   : DTS2014120207400: 连续去激活多个PDP, 网侧不释放RRC连接
*****************************************************************************/
VOS_VOID NAS_MML_InitPsBearerContext(
    NAS_MML_PS_BEARER_CONTEXT_STRU     *pstPsBearerCtx
)
{
    VOS_UINT8                           i;

    for(i = 0; i < NAS_MML_MAX_PS_BEARER_NUM; i++)
    {
        pstPsBearerCtx[i].enPsBearerIsrFlg = NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT;
        pstPsBearerCtx[i].enPsBearerState  = NAS_MML_PS_BEARER_STATE_INACTIVE;
        pstPsBearerCtx[i].ucPsActPending   = VOS_FALSE;
        pstPsBearerCtx[i].ucPsDeactPending = VOS_FALSE;
    }

    return;
}

/*****************************************************************************
函 数 名  : NAS_MML_InitEmergencyNumList
功能描述  : 初始化紧急呼叫号码列表
输入参数  : 无
输出参数  : pstEmergencyNumList-紧急呼叫号码内容
返 回 值  : 无
调用函数  :
被调函数  :

修改历史     :
 1.日    期   : 2012年3月5日
   作    者   : z00161729
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_InitEmergencyNumList(
    NAS_MML_EMERGENCY_NUM_LIST_STRU    *pstEmergencyNumList
)
{
    pstEmergencyNumList->ucEmergencyNumber = 0;
    PS_MEM_SET(pstEmergencyNumList->aucEmergencyList, (VOS_CHAR)0xFF,
               sizeof(pstEmergencyNumList->aucEmergencyList));
    return;
}


/*****************************************************************************
 函 数 名  : NAS_MML_InitNetworkCtx
 功能描述  : 初始化MML_CTX中当前网络相关信息
 输入参数  : pstNetworkInfo:当前网络信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月30日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数
 2.日    期   : 2012年4月18日
   作    者   : l00130025
   修改内容   : DTS2012040200480,单独维护EPS注册状态,供L模下CEREG/CGREG查询和上报使用
 3.日    期   : 2012年3月1日
   作    者   : z00161729
   修改内容   : V7R1 C50 支持ISR修改
 4.日    期   : 2013年12月13日
   作    者   : w00176964
   修改内容   : Volte_PhaseIII 项目修改:增加IMS域上下文初始化信息
 5.日    期   : 2014年12月29日
    作    者   : z00161729
    修改内容   : DSDS业务重拨时no rf未触发搜网导致业务失败，mm在no cell available状态no rf时给mmc发送cm service ind触发搜网
 6.日    期   : 2015年4月19日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
  7.日    期   : 2016年1月20日
    作    者   : c00318887
    修改内容   : DTS2015123110917: usim卡在GSM下做2G鉴权后，csfb到3G下鉴权错误
*****************************************************************************/
VOS_VOID  NAS_MML_InitNetworkCtx(
    NAS_MML_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    NAS_MML_NETWORK_INFO_STRU           *pstNetworkInfo
)
{
    NAS_MML_InitCampPlmnInfo(&(pstNetworkInfo->stCampPlmnInfo));

    NAS_MML_InitEquPlmnInfo(&(pstNetworkInfo->stEquPlmnInfo));

    NAS_MML_InitNetwork3GppRel(&(pstNetworkInfo->stNetwork3GppRel));

    NAS_MML_InitMsCurrBandInfoInfo(&(pstNetworkInfo->stBandInfo));

    NAS_MML_InitPsDomainInfo(&(pstNetworkInfo->stPsDomainInfo));

    NAS_MML_InitCsDomainInfo(&(pstNetworkInfo->stCsDomainInfo));

    NAS_MML_InitEpsDomainInfo(&(pstNetworkInfo->stEpsDomainInfo));

    NAS_MML_InitImsDomainInfo(&(pstNetworkInfo->stImsDomainInfo));

    NAS_MML_InitConnStatusInfo(&(pstNetworkInfo->stConnStatus));
    NAS_MML_InitPsBearerContext(pstNetworkInfo->astPsBearerContext);
    NAS_MML_InitEmergencyNumList(&pstNetworkInfo->stEmergencyNumList);

    pstNetworkInfo->stNoRfInfo.ucRfAvailFlg   = VOS_TRUE;
    pstNetworkInfo->stNoRfInfo.enRatType      = NAS_MML_NET_RAT_TYPE_BUTT;
    pstNetworkInfo->stNoRfInfo.aucReserved[0] = 0;
    pstNetworkInfo->stNoRfInfo.aucReserved[1] = 0;

    NAS_MML_InitSuitPlmnListInfo(&(pstNetworkInfo->stSuitPlmnListInfo));

    NAS_MML_InitOriginalRejectCause(&(pstNetworkInfo->stOriginalRejectCause));

    NAS_MML_InitAuthInfo(enInitType, &(pstNetworkInfo->stAuthInfo));
}

/*****************************************************************************
 函 数 名  : NAS_MML_InitInternalMsgQueue
 功能描述  : 初始化MML_CTX中内部消息队列
 输入参数  : pstInternalMsgQueue:内部消息队列
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月30日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_InitInternalMsgQueue(
    NAS_MML_INTERNAL_MSG_QUEUE_STRU     *pstInternalMsgQueue                   /* MM子层的内部消息队列 */
)
{
    VOS_UINT32                          i;

    pstInternalMsgQueue->ucHeader   = 0;
    pstInternalMsgQueue->ucTail     = 0;

    for ( i = 0 ; i < NAS_MML_MAX_MSG_QUEUE_SIZE; i++ )
    {
        pstInternalMsgQueue->astNasMmMsgQueue[i].usMsgID    = NAS_MML_INVALID_INTERNAL_MSG_ID;
        PS_MEM_SET(pstInternalMsgQueue->astNasMmMsgQueue[i].aucBuf,
                   0x00,
                   NAS_MML_MAX_INTERNAL_MSG_LEN);
    }

}


/*****************************************************************************
 函 数 名  : NAS_MML_InitMaintainInfo
 功能描述  : 初始化MML_CTX中可谓可测部分
 输入参数  : pstMaintainInfo:可谓可测全局变量
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年04月23日
   作    者   : l00171473
   修改内容   : 新生成函数
 2.日    期   : 2013年07月222日
   作    者   : j00177245
   修改内容   : 清理编译warning
 3.日    期   : 2013年08月23日
   作    者   : f00179208
   修改内容   : ErrLog&FTM项目
 4.日    期   : 2014年10月21日
   作    者   : b00269685
   修改内容   : 可维可测
*****************************************************************************/
VOS_VOID  NAS_MML_InitMaintainInfo(
    NAS_MML_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    NAS_MML_MAINTAIN_CTX_STRU          *pstMaintainInfo
)
{
    PS_MEM_SET(&g_stNasMntnErrorLogMm, 0, sizeof(g_stNasMntnErrorLogMm));

    /* 上电开机时才需要初始化如下变量 */
    if (NAS_MML_INIT_CTX_STARTUP != enInitType)
    {
        return;
    }

    /* 初始默认不发送PC回放消息 */
    pstMaintainInfo->stUeMaintainInfo.ucUeSndPcRecurFlg    = VOS_FALSE;

    /* 初始默认PC工具未连接 */
    pstMaintainInfo->stOmMaintainInfo.ucOmConnectFlg       = VOS_FALSE;

    /* 初始默认PC工具未使能NAS的PC回放消息发送 */
    pstMaintainInfo->stOmMaintainInfo.ucOmPcRecurEnableFlg = VOS_FALSE;

    NAS_MML_InitErrLogMntnInfo(&pstMaintainInfo->stErrLogMntnInfo);
#if (FEATURE_ON == FEATURE_PTM)
    pstMaintainInfo->stFtmMntnInfo.ucFtmCtrlFlag           = VOS_FALSE;
#endif

    NAS_MML_InitLogEventState(&(pstMaintainInfo->stLogEventState));
}

/*****************************************************************************
 函 数 名  : NAS_MML_InitCtx
 功能描述  : 开机初始化MML_CTX
 输入参数  : pstMmlCtx:MML上下文信息
             enInitType:INIT类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年6月30日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_InitCtx(
    NAS_MML_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    NAS_MML_CTX_STRU                    *pstMmlCtx
)
{
    /* 初始化SIM卡信息 */
    NAS_MML_InitSimInfoCtx(enInitType, &(pstMmlCtx->stSimInfo));

    /* 初始化MS配置信息 */
    NAS_MML_InitMsCfgCtx(&(pstMmlCtx->stMsCfgInfo));

    /* 初始化当前网络信息 */
    NAS_MML_InitNetworkCtx(enInitType, &(pstMmlCtx->stNetworkInfo));

    /* 初始化内部消息队列 */
    NAS_MML_InitInternalMsgQueue(&(pstMmlCtx->stInternalMsgQueue));

    /* 初始化可谓可测信息 */
    NAS_MML_InitMaintainInfo(enInitType, &(pstMmlCtx->stMaintainInfo));

    PS_MEM_SET(&pstMmlCtx->stCsMoSessionManager, 0x0, sizeof(NAS_MML_CS_MO_SESSION_MANAGER_STRU));

}

/*****************************************************************************
 函 数 名  : NAS_MML_GetSimInfo
 功能描述  : 获取MML中保存的SIM信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的SIM卡信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_SIM_INFO_STRU*  NAS_MML_GetSimInfo( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stSimInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetMsCfgInfo
 功能描述  : 获取MML中保存的MS的配置信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的MS的配置信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_MS_CFG_INFO_STRU* NAS_MML_GetMsCfgInfo( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetNetworkInfo
 功能描述  : 获取MML中保存的当前网络的信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的当前网络的信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_NETWORK_INFO_STRU* NAS_MML_GetNetworkInfo( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetSimStatus
 功能描述  : 获取MML中保存的SIM的状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的SIM的状态
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_SIM_STATUS_STRU* NAS_MML_GetSimStatus(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stSimInfo.stSimStatus);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetSimPresentStatus
 功能描述  : 获取MML中保存的SIM的是否在位的信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的SIM的是否在位的信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetSimPresentStatus(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stSimInfo.stSimStatus.ucSimPresentStatus);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetSimPresentStatus
 功能描述  : 获取MML中保存的SIM的类型,USIM或SIM卡
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的SIM卡类型
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_SIM_TYPE_ENUM_UINT8 NAS_MML_GetSimType(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stSimInfo.stSimStatus.enSimType);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetSimType
 功能描述  : 设置MML中保存的SIM的类型,USIM或SIM卡
 输入参数  : enSimType - sim卡类型
 输出参数  : 无
 返 回 值  : MML中保存的SIM卡类型
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetSimType(
    NAS_MML_SIM_TYPE_ENUM_UINT8                 enSimType
)
{
    NAS_MML_GetMmlCtx()->stSimInfo.stSimStatus.enSimType = enSimType;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetSimCsRegStatus
 功能描述  : 获取MML中保存的CS域的SIM卡注册信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的CS域的SIM卡注册信息,有效或无效
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetSimCsRegStatus(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stSimInfo.stSimStatus.ucSimCsRegStatus);
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetSimPsRegStatus
 功能描述  : 获取MML中保存的PS域的SIM卡注册信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的PS域的SIM卡注册信息,有效或无效
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetSimPsRegStatus(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stSimInfo.stSimStatus.ucSimPsRegStatus);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetSimPresentStatus
 功能描述  : 设置MML中保存的SIM卡在位的状态
 输入参数  : ucSimPresentStatus:MML中保存的SIM的在位的状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : h44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetSimPresentStatus(
    VOS_UINT8                           ucSimPresentStatus
)
{
    NAS_MML_GetMmlCtx()->stSimInfo.stSimStatus.ucSimPresentStatus = ucSimPresentStatus;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetSimCsRegStatus
 功能描述  : 设置MML中保存的SIM卡CS域的状态,有效或无效
 输入参数  : ucSimPresentStatus:MML中保存的SIM卡CS域的状态,有效或无效
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : h44270
   修改内容   : 新生成函数


*****************************************************************************/
VOS_VOID NAS_MML_SetSimCsRegStatus(
    VOS_UINT8                           ucSimCsRegStatus
)
{
    NAS_MML_GetMmlCtx()->stSimInfo.stSimStatus.ucSimCsRegStatus = ucSimCsRegStatus;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetSimPsRegStatus
 功能描述  : 设置MML中保存的SIM卡PS域的状态,有效或无效
 输入参数  : ucSimPresentStatus:MML中保存的SIM卡PS域的状态,有效或无效
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : h44270
   修改内容   : 新生成函数


*****************************************************************************/
VOS_VOID NAS_MML_SetSimPsRegStatus(
    VOS_UINT8                           ucSimPsRegStatus
)
{
    NAS_MML_GetMmlCtx()->stSimInfo.stSimStatus.ucSimPsRegStatus = ucSimPsRegStatus;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetPsUpdateStatus
 功能描述  : 设置MML中保存的PS域的更新状态状
 输入参数  : enPsUpdateStatus:PS的更新状态状
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : h44270
   修改内容   : 新生成函数


*****************************************************************************/
VOS_VOID NAS_MML_SetPsUpdateStatus(
    NAS_MML_ROUTING_UPDATE_STATUS_ENUM_UINT8    enPsUpdateStatus
)
{
    NAS_MML_GetMmlCtx()->stSimInfo.stSimStatus.enPsUpdateStatus = enPsUpdateStatus;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetPsUpdateStatus
 功能描述  : 设置MML中保存的PS域的更新状态状
 输入参数  : 无
 输出参数  : 无
 返 回 值  : PS的更新状态状
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : h44270
   修改内容   : 新生成函数


*****************************************************************************/
NAS_MML_ROUTING_UPDATE_STATUS_ENUM_UINT8 NAS_MML_GetPsUpdateStatus(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stSimStatus.enPsUpdateStatus;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetCsUpdateStatus
 功能描述  : 获取MML中保存的CS域的更新状态状
 输入参数  : enCsUpdateStatus:CS的更新状态状
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : h44270
   修改内容   : 新生成函数


*****************************************************************************/
VOS_VOID NAS_MML_SetCsUpdateStatus(
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus
)
{
    NAS_MML_GetMmlCtx()->stSimInfo.stSimStatus.enCsUpdateStatus = enCsUpdateStatus;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetCsUpdateStatus
 功能描述  : 获取MML中保存的PS域的更新状态状
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CS的更新状态状
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : h44270
   修改内容   : 新生成函数


*****************************************************************************/
NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8 NAS_MML_GetCsUpdateStatus(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stSimStatus.enCsUpdateStatus;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetImsiRefreshStatus
 功能描述  : 获取MML中保存的IMSI REFRESH状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : IMSI REFRESH状态 VOS_TRUE表示IMSI REFRESH，VOS_FALSE表示非IMSI REFRESH
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年12月10日
   作    者   : z00359541
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MML_GetImsiRefreshStatus(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stSimStatus.ucImsiRefreshStatus;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetImsiRefreshStatus
 功能描述  : 将IMSI REFRESH状态写入MML中保存
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年12月10日
   作    者   : z00359541
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_SetImsiRefreshStatus(
    VOS_UINT8                           ucImsiRefreshStatus
)
{
    NAS_MML_GetMmlCtx()->stSimInfo.stSimStatus.ucImsiRefreshStatus = ucImsiRefreshStatus;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetSimMsIdentity
 功能描述  : 获取MML中保存的SIM卡中MS的IDENTITY
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的SIM卡中MS的IDENTITY
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_SIM_MS_IDENTITY_STRU* NAS_MML_GetSimMsIdentity(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stSimInfo.stMsIdentity);
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetSimMsIdentity
 功能描述  : 更新MML中保存的SIM卡中MS的IDENTITY
 输入参数  : pstSimMsIdentity:需要更新的SIM卡中MS的IDENTITY
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetSimMsIdentity(
    NAS_MML_SIM_MS_IDENTITY_STRU        *pstSimMsIdentity
)
{
    PS_MEM_CPY(&((NAS_MML_GetMmlCtx()->stSimInfo.stMsIdentity)),
               pstSimMsIdentity,
               sizeof(NAS_MML_SIM_MS_IDENTITY_STRU));
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetSimImsi
 功能描述  : 获取MML中保存的SIM卡中IMSI
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的SIM卡中IMSI
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : huwen 44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8* NAS_MML_GetSimImsi(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stMsIdentity.aucImsi;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetUeIdPtmsi
 功能描述  : 获取MML中保存的Ptmsi
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的Ptmsi
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : huwen 44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8* NAS_MML_GetUeIdPtmsi(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stMsIdentity.aucPtmsi;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetUeIdPtmsi
 功能描述  : 更新MML中保存Ptmsi
 输入参数  : pucPtmsi:需要更新PTMSI
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : huwen 44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetUeIdPtmsi(
    VOS_UINT8                          *pucPtmsi
)
{
    PS_MEM_CPY(NAS_MML_GetMmlCtx()->stSimInfo.stMsIdentity.aucPtmsi,
               pucPtmsi,
               (sizeof(VOS_UINT8) * NAS_MML_MAX_PTMSI_LEN));
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetUeIdPtmsiSignature
 功能描述  : 获取MML中保存的Ptmsi Signature
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的Ptmsi
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : huwen 44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8* NAS_MML_GetUeIdPtmsiSignature(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stMsIdentity.aucPtmsiSignature;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetUeIdPtmsiSignature
 功能描述  : 更新MML中保存Ptmsi
 输入参数  : pucPtmsi:需要更新PTMSI SIGNATURE
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : huwen 44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetUeIdPtmsiSignature(
    VOS_UINT8                          *pucPtmsiSignature
)
{
    PS_MEM_CPY(NAS_MML_GetMmlCtx()->stSimInfo.stMsIdentity.aucPtmsiSignature,
               pucPtmsiSignature,
               (sizeof(VOS_UINT8) * NAS_MML_MAX_PTMSI_SIGNATURE_LEN));
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetUeIdTmsi
 功能描述  : 获取MML中保存的Tmsi
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的Tmsi
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : huwen 44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8* NAS_MML_GetUeIdTmsi(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stMsIdentity.aucTmsi;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetUeIdTmsi
 功能描述  : 更新MML中保存Tmsi
 输入参数  : pucTmsi:需要更新Tmsi
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : huwen 44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetUeIdTmsi(
    VOS_UINT8                          *pucTmsi
)
{
    PS_MEM_CPY(NAS_MML_GetMmlCtx()->stSimInfo.stMsIdentity.aucTmsi,
               pucTmsi,
               NAS_MML_MAX_TMSI_LEN);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetUeOperMode
 功能描述  : 更新MML中保存UeOperMode
 输入参数  : enUeOperMode:UE模式
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : huwen 44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetUeOperMode(
    NAS_MML_SIM_UE_OPER_MODE_ENUM_UINT8 enUeOperMode
)
{
    NAS_MML_GetMmlCtx()->stSimInfo.stMsIdentity.enUeOperMode = enUeOperMode;
}
/*****************************************************************************
 函 数 名  : NAS_MML_GetUeOperMode
 功能描述  : 获取MML中保存UeOperMode
 输入参数  : enUeOperMode:UE模式
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : l00130025
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_SIM_UE_OPER_MODE_ENUM_UINT8 NAS_MML_GetUeOperMode(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stMsIdentity.enUeOperMode;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetSimPsSecurity
 功能描述  : 获取MML中保存的SIM卡中PS域的安全参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的SIM卡中PS域的安全参数
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_SIM_PS_SECURITY_INFO_STRU* NAS_MML_GetSimPsSecurity(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stSimInfo.stPsSecurity);
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetSimPsSecurity
 功能描述  : 更新MML中保存的SIM卡中PS域的安全参数
 输入参数  : pstSimPsSecruity:需要更新的SIM卡中PS域的安全参数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetSimPsSecurity(
    NAS_MML_SIM_PS_SECURITY_INFO_STRU   *pstSimPsSecruity

)
{
    PS_MEM_CPY(&((NAS_MML_GetMmlCtx()->stSimInfo.stPsSecurity)),
               pstSimPsSecruity,
               sizeof(NAS_MML_SIM_PS_SECURITY_INFO_STRU));
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetSimPsSecurityCksn
 功能描述  : 获取MML中保存的SIM卡中PS域的CKSN
 输入参数  : 无
 输出参数  : 无
 返 回 值  : PS域的CKSN
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : h44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetSimPsSecurityCksn(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stPsSecurity.ucCKSN;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetSimPsSecurityCksn
 功能描述  : 更新MML中保存的SIM卡中PS域的CKSN
 输入参数  : ucCksn:PS域的CKSN
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : h44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetSimPsSecurityCksn(
    VOS_UINT8                           ucCksn
)
{
    NAS_MML_GetMmlCtx()->stSimInfo.stPsSecurity.ucCKSN = ucCksn;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetSimPsSecurityUmtsCk
 功能描述  : 获取MML中保存的SIM卡中PS域的UmtsCk
 输入参数  : 无
 输出参数  : 无
 返 回 值  : PS域的UmtsCk
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : h44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8* NAS_MML_GetSimPsSecurityUmtsCk(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stPsSecurity.aucUmtsCk;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetSimPsSecurityUmtsCk
 功能描述  : 更新MML中保存的SIM卡中PS域的UmtsCk
 输入参数  : pucUmtsCk:PS域的UmtsCk
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : h44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetSimPsSecurityUmtsCk(
    VOS_UINT8                           *pucUmtsCk
)
{
    PS_MEM_CPY(NAS_MML_GetMmlCtx()->stSimInfo.stPsSecurity.aucUmtsCk,
               pucUmtsCk,
               (sizeof(VOS_UINT8) * NAS_MML_UMTS_CK_LEN));
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetSimPsSecurityUmtsIk
 功能描述  : 获取MML中保存的SIM卡中PS域的UmtsIk
 输入参数  : 无
 输出参数  : 无
 返 回 值  : PS域的UmtsCk
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : h44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8* NAS_MML_GetSimPsSecurityUmtsIk(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stPsSecurity.aucUmtsIk;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetSimPsSecurityUmtsIk
 功能描述  : 更新MML中保存的SIM卡中PS域的UmtsIk
 输入参数  : pucUmtsIk:PS域的UmtsIk
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : h44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetSimPsSecurityUmtsIk(
    VOS_UINT8                           *pucUmtsIk
)
{
    PS_MEM_CPY(NAS_MML_GetMmlCtx()->stSimInfo.stPsSecurity.aucUmtsIk,
               pucUmtsIk,
               (sizeof(VOS_UINT8) * NAS_MML_UMTS_IK_LEN));
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetSimPsSecurityGsmKc
 功能描述  : 获取MML中保存的SIM卡中PS域的GsmKc
 输入参数  : 无
 输出参数  : 无
 返 回 值  : PS域的GsmKc
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : h44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8* NAS_MML_GetSimPsSecurityGsmKc(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stPsSecurity.aucGsmKc;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetSimPsSecurityUmtsIk
 功能描述  : 更新MML中保存的SIM卡中PS域的GsmKc
 输入参数  : pucUmtsIk:PS域的GsmKc
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : h44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetSimPsSecurityGsmKc(
    VOS_UINT8                           *pucGsmKc
)
{
    PS_MEM_CPY(NAS_MML_GetMmlCtx()->stSimInfo.stPsSecurity.aucGsmKc,
               pucGsmKc,
               (sizeof(VOS_UINT8) * NAS_MML_GSM_KC_LEN));
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetSimCsSecurity
 功能描述  : 获取MML中保存的SIM卡中CS域的安全参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的SIM卡中CS域的安全参数
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_SIM_CS_SECURITY_INFO_STRU* NAS_MML_GetSimCsSecurity(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stSimInfo.stCsSecurity);
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetSimCsSecurity
 功能描述  : 更新MML中保存的SIM卡中CS域的安全参数
 输入参数  : pstSimCsSecruity:需要更新的SIM卡中CS域的安全参数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetSimCsSecurity(
    NAS_MML_SIM_CS_SECURITY_INFO_STRU  *pstSimCsSecruity
)
{
    PS_MEM_CPY(&((NAS_MML_GetMmlCtx()->stSimInfo.stCsSecurity)),
               pstSimCsSecruity,
               sizeof(NAS_MML_SIM_CS_SECURITY_INFO_STRU));
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetSimCsSecurityCksn
 功能描述  : 获取MML中保存的SIM卡中CS域的CKSN
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CS域的CKSN
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : h44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetSimCsSecurityCksn(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stCsSecurity.ucCKSN;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetSimCsSecurityCksn
 功能描述  : 更新MML中保存的SIM卡中CS域的CKSN
 输入参数  : ucCksn:CS域的CKSN
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : h44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetSimCsSecurityCksn(
    VOS_UINT8                           ucCksn
)
{
    NAS_MML_GetMmlCtx()->stSimInfo.stCsSecurity.ucCKSN = ucCksn;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetSimCsSecurityUmtsCk
 功能描述  : 获取MML中保存的SIM卡中CS域的UmtsCk
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CS域的UmtsCk
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : h44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8* NAS_MML_GetSimCsSecurityUmtsCk(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stCsSecurity.aucUmtsCk;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetSimCsSecurityUmtsCk
 功能描述  : 更新MML中保存的SIM卡中CS域的UmtsCk
 输入参数  : pucUmtsCk:CS域的UmtsCk
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : h44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetSimCsSecurityUmtsCk(
    VOS_UINT8                           *pucUmtsCk
)
{
    PS_MEM_CPY(NAS_MML_GetMmlCtx()->stSimInfo.stCsSecurity.aucUmtsCk,
               pucUmtsCk,
               (sizeof(VOS_UINT8) * NAS_MML_UMTS_CK_LEN));
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetSimCsSecurityUmtsIk
 功能描述  : 获取MML中保存的SIM卡中CS域的UmtsIk
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CS域的UmtsCk
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : h44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8* NAS_MML_GetSimCsSecurityUmtsIk(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stCsSecurity.aucUmtsIk;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetSimCsSecurityUmtsIk
 功能描述  : 更新MML中保存的SIM卡中CS域的UmtsIk
 输入参数  : pucUmtsIk:CS域的UmtsIk
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : h44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetSimCsSecurityUmtsIk(
    VOS_UINT8                           *pucUmtsIk
)
{
    PS_MEM_CPY(NAS_MML_GetMmlCtx()->stSimInfo.stCsSecurity.aucUmtsIk,
               pucUmtsIk,
               (sizeof(VOS_UINT8) * NAS_MML_UMTS_IK_LEN));
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetSimCsSecurityGsmKc
 功能描述  : 获取MML中保存的SIM卡中CS域的GsmKc
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CS域的GsmKc
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : h44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8* NAS_MML_GetSimCsSecurityGsmKc(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stCsSecurity.aucGsmKc;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetSimCsSecurityUmtsIk
 功能描述  : 更新MML中保存的SIM卡中CS域的GsmKc
 输入参数  : pucUmtsIk:CS域的GsmKc
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : h44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetSimCsSecurityGsmKc(
    VOS_UINT8                           *pucGsmKc
)
{
    PS_MEM_CPY(NAS_MML_GetMmlCtx()->stSimInfo.stCsSecurity.aucGsmKc,
               pucGsmKc,
               (sizeof(VOS_UINT8) * NAS_MML_GSM_KC_LEN));
}



/*****************************************************************************
 函 数 名  : NAS_MML_GetSimEhplmnList
 功能描述  : 获取MML中保存的SIM卡中EHPLMN的内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的SIM卡中EHPLMN的内容
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_SIM_EHPLMN_INFO_STRU* NAS_MML_GetSimEhplmnList(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.stEhPlmnInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetSimEhplmnList
 功能描述  : 更新MML中保存的SIM卡中EHPLMN的内容
 输入参数  : pstEhplmnList:需更新的EHPLMN的内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetSimEhplmnList(
    NAS_MML_SIM_EHPLMN_INFO_STRU        *pstEhplmnList
)
{
    PS_MEM_CPY(&(NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.stEhPlmnInfo),
               pstEhplmnList,
               sizeof(NAS_MML_SIM_EHPLMN_INFO_STRU));
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetSimPlmnInfo
 功能描述  : 获取MML中保存的SIM卡的内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 获取MML中保存的SIM卡的内容
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年10月15日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_SIM_PLMN_INFO_STRU* NAS_MML_GetSimPlmnInfo(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo);
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetSimHplmnWithRatList
 功能描述  : 获取MML中保存的SIM卡中HPLMNWITHRAT的内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的SIM卡中HPLMNWITHRAT的内容
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_SIM_HPLMN_WITH_RAT_INFO_STRU* NAS_MML_GetSimHplmnWithRatList(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.stHplmnWithRatInfo);
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetSimHplmnWithRatList
 功能描述  : 更新MML中保存的SIM卡中HPLMNWITHRAT的内容
 输入参数  : pstHplmnWithRatList:需要更新的HPLMNWITHRAT的内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetSimHplmnWithRatList(
    NAS_MML_SIM_HPLMN_WITH_RAT_INFO_STRU    *pstHplmnWithRatList
)
{
    PS_MEM_CPY(&(NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.stHplmnWithRatInfo),
               pstHplmnWithRatList,
               sizeof(NAS_MML_SIM_HPLMN_WITH_RAT_INFO_STRU));
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetSimUserPlmnList
 功能描述  : 获取MML中保存的SIM卡中USERPLMN的内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的SIM卡中USERPLMN的内容
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_SIM_USERPLMN_INFO_STRU* NAS_MML_GetSimUserPlmnList(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.stUserPlmnInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetSimUserPlmnList
 功能描述  : 更新MML中保存的SIM卡中USERPLMN的内容
 输入参数  : pstUserPlmnList:需更新USERPLMN的内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetSimUserPlmnList(
    NAS_MML_SIM_USERPLMN_INFO_STRU      *pstUserPlmnList
)
{
    PS_MEM_CPY(&(NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.stUserPlmnInfo),
               pstUserPlmnList,
               sizeof(NAS_MML_SIM_USERPLMN_INFO_STRU));
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetSimOperPlmnList
 功能描述  : 获取MML中保存的SIM卡中OPERPLMN的内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的SIM卡中OPERPLMN的内容
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_SIM_OPERPLMN_INFO_STRU* NAS_MML_GetSimOperPlmnList(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.stOperPlmnInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetSimOperPlmnList
 功能描述  : 更新MML中保存的SIM卡中OPERPLMN的内容
 输入参数  : pstOperPlmnList:需更新OPERPLMN的内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetSimOperPlmnList(
    NAS_MML_SIM_OPERPLMN_INFO_STRU     *pstOperPlmnList
)
{
    PS_MEM_CPY(&(NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.stOperPlmnInfo),
               pstOperPlmnList,
               sizeof(NAS_MML_SIM_OPERPLMN_INFO_STRU));
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetSimSelPlmnList
 功能描述  : 获取MML中保存的SIM卡中SELPLMN的内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的SIM卡中SELPLMN的内容
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_SIM_SELPLMN_INFO_STRU* NAS_MML_GetSimSelPlmnList(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.stSelPlmnInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetSimSelPlmnList
 功能描述  : 更新MML中保存的SIM卡中SELPLMN的内容
 输入参数  : 无
 输出参数  : pstSelPlmnList:需要更新的SELPLMN的内容
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetSimSelPlmnList(
    NAS_MML_SIM_SELPLMN_INFO_STRU       *pstSelPlmnList
)
{
    PS_MEM_CPY(&(NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.stSelPlmnInfo),
               pstSelPlmnList,
               sizeof(NAS_MML_SIM_SELPLMN_INFO_STRU));
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetSimForbidPlmnList
 功能描述  : 获取MML中保存的SIM卡中FORBID网络信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的SIM卡中FORBID网络信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_SIM_FORBIDPLMN_INFO_STRU* NAS_MML_GetForbidPlmnInfo( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.stForbidPlmnInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetSimForbidPlmnList
 功能描述  : 更新MML中保存的SIM卡中FORBID网络信息
 输入参数  : pstForbidPlmnInfo:需更新的FORBID网络信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetSimForbidPlmnList(
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU    *pstForbidPlmnInfo
)
{
    PS_MEM_CPY(&(NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.stForbidPlmnInfo),
               pstForbidPlmnInfo,
               sizeof(NAS_MML_SIM_FORBIDPLMN_INFO_STRU));
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetSimHplmnTimerLen
 功能描述  : 更新MML中保存SIM卡中HPLMN定时器的时长
 输入参数  : ulSimHplmnTimerLen:SIM卡中HPLMN定时器的时长
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetSimHplmnTimerLen(
    VOS_UINT32                          ulSimHplmnTimerLen
)
{
    NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.ulSimHplmnTimerLen = ulSimHplmnTimerLen;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetSimHplmnTimerLen
 功能描述  : 获取MML中保存SIM卡中HPLMN定时器的时长
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存SIM卡中HPLMN定时器的时长
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_GetSimHplmnTimerLen(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.ulSimHplmnTimerLen;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetSelplmnList
 功能描述  : 获取MML中保存当前MS支持的协议版本
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存当前MS支持的协议版本
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_MS_3GPP_REL_STRU* NAS_MML_GetMs3GppRel(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stMs3GppRel);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetMs3GppRel
 功能描述  : 更新MML中保存当前MS支持的协议版本
 输入参数  : pstMs3GppRel:需要更新的MS的协议版本
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetMs3GppRel(
    NAS_MML_MS_3GPP_REL_STRU           *pstMs3GppRel
)
{
    PS_MEM_CPY(&(NAS_MML_GetMmlCtx()->stMsCfgInfo.stMs3GppRel),
               pstMs3GppRel,
               sizeof(NAS_MML_MS_3GPP_REL_STRU));
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetMsCapability
 功能描述  : 获取MML中保存当前MS支持的手机能力
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存当前MS支持的手机能力
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_MS_CAPACILITY_INFO_STRU* NAS_MML_GetMsCapability(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsCapability);
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetImeisv
 功能描述  : 获取MML中保存当前MS的IMEISV的内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存当前MS的IMEISV的内容
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/

VOS_UINT8* NAS_MML_GetImeisv( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsCapability.aucImeisv);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetMsMode
 功能描述  : 获取当前手机模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 获取当前手机模式
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月9日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_MS_MODE_ENUM_UINT8 NAS_MML_GetMsMode( VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.enMsMode);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetLteCsServiceCfg
 功能描述  : 获取L支持的cs业务能力配置枚举值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 获取L支持的cs业务能力配置枚举值
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年10月28日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2012年3月8日
   作    者   : w00167002
   修改内容   : CSFB调整:enLteCsServiceCfg结构体的调整
*****************************************************************************/
NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8 NAS_MML_GetLteCsServiceCfg( VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.enLteCsServiceCfg;
}

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */



/*****************************************************************************
 函 数 名  : NAS_MML_GetLteCapabilityStatus
 功能描述  : 获取当前LTE能力状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前LTE能力状态
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年10月26日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32 NAS_MML_GetLteCapabilityStatus( VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.enLteCapabilityStatus);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetDisableLteReason
 功能描述  : 获取Disable LTE的原因值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : Disable LTE的原因值
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年7月27日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
MMC_LMM_DISABLE_LTE_REASON_ENUM_UINT32 NAS_MML_GetDisableLteReason( VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.enDisableLteReason);
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetLteDisabledRauUseLteInfoFlag
 功能描述  : 获取l disabled后rau是否需要从l获取安全上下文或guti映射信息标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年02月25日
   作    者   : z00161729
   修改内容   : DTS2014022206794:GCF 9.2.1.2.1b/9.2.3.2.3/9.2.1.2.1失败disable lte时rau需要从L获取安全上下文
*****************************************************************************/
VOS_UINT8 NAS_MML_GetLteDisabledRauUseLteInfoFlag(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.ucLteDisabledRauUseLteInfoFlag);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetLteDisabledRauUseLteInfoFlag
 功能描述  : 设置l disabled后rau是否需要从l获取安全上下文或guti映射信息标识
 输入参数  : ucLteDisabledRauUseLteInfoFlag - l disabled后rau是否需要从l获取安全上下文或guti映射标识
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年02月25日
   作    者   : z00161729
   修改内容   : DTS2014022206794:GCF 9.2.1.2.1b/9.2.3.2.3/9.2.1.2.1失败disable lte时rau需要从L获取安全上下文
*****************************************************************************/
VOS_VOID NAS_MML_SetLteDisabledRauUseLteInfoFlag(VOS_UINT8 ucLteDisabledRauUseLteInfoFlag)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.ucLteDisabledRauUseLteInfoFlag = ucLteDisabledRauUseLteInfoFlag;
    return;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetLteRoamAllowedFlg
 功能描述  : 获取当前LTE漫游允许标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前LTE漫游允许标记
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月6日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2013年6月11日
   作    者   : z00161729
   修改内容   : SVLTE调整修改
*****************************************************************************/
VOS_UINT8   NAS_MML_GetLteRoamAllowedFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.stLteRoamCfg.ucLteRoamAllowedFlg);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetDisableLteRoamFlg
 功能描述  : 获取当前是否disable LTE漫游标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前禁止LTE漫游标记
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月6日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_GetDisableLteRoamFlg( VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.ulDisableLteRoamFlg);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetRoamEnabledMccList
 功能描述  : 获取允许漫游的国家码列表
 输入参数  : 无
 输出参数  : pulMcc 允许漫游的国家码列表
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月6日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2013年6月11日
   作    者   : z00161729
   修改内容   : SVLTE调整修改
*****************************************************************************/
VOS_VOID NAS_MML_GetRoamEnabledMccList(VOS_UINT32 *pulMcc)
{
    VOS_UINT32      i;

    for (i=0; i<NAS_MML_ROAM_ENABLED_MAX_MCC_NUMBER; i++)
    {
        pulMcc[i] = NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.stLteRoamCfg.aulRoamEnabledMccList[i];
    }
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetEpsRegStatus
 功能描述  : 获取EPS域的注册结果
 输入参数  : 无
 输出参数  : 无
 返 回 值  : EPS域的注册结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年4月18日
   作    者   : l00130025
   修改内容   : DTS2012040200480,获取EPS当前注册状态

*****************************************************************************/
NAS_MML_REG_STATUS_ENUM_UINT8  NAS_MML_GetEpsRegStatus( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stEpsDomainInfo.enEpsRegStatus);
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetDailRejectCfg
 功能描述  : 获取拨号被拒配置Nv项是否使能
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 拨号被拒配置Nv项是否使能
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月6日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetDailRejectCfg( VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stDailRejectCfg.ucEnableFlg;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetCsfbServiceStatus
 功能描述  : 获取当前CSFB业务状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前CSFB状态
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年2月14日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8 NAS_MML_GetCsfbServiceStatus( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.enCsfbServiceStatus;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetPsBearerCtx
 功能描述  : 获取当前ps 承载上下文信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ps 承载上下文信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月5日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_PS_BEARER_CONTEXT_STRU* NAS_MML_GetPsBearerCtx( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.astPsBearerContext;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetT3412Status
 功能描述  : 获取T3412定时器运行状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : T3412定时器状态
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月1日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_TIMER_INFO_ENUM_UINT8 NAS_MML_GetT3412Status(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stEpsDomainInfo.enT3412Status;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetT3423Status
 功能描述  : 获取T3423定时器运行状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : T3423定时器状态
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月1日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_TIMER_INFO_ENUM_UINT8 NAS_MML_GetT3423Status(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stEpsDomainInfo.enT3423Status;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetT3402Status
 功能描述  : 获取T3402定时器运行状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : T3402定时器状态
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年07月23日
   作    者   : f00179208
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_TIMER_INFO_ENUM_UINT8 NAS_MML_GetT3402Status(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stEpsDomainInfo.enT3402Status;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetAdditionUpdateRslt
 功能描述  : 获取联合attach或tau中网侧回复结果中Additional update result IE内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 联合attach或tau中网侧回复结果中Additional update result IE内容
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月3日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_ADDITION_UPDATE_RSLT_INFO_ENUM_UINT8 NAS_MML_GetAdditionUpdateRslt(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stEpsDomainInfo.enAdditionUpdateRsltInfo;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetEmergencyNumList
 功能描述  : 获取紧急呼号码列表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 紧急呼叫号码列表
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月12日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_EMERGENCY_NUM_LIST_STRU* NAS_MML_GetEmergencyNumList (VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stEmergencyNumList);
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetLteUeUsageSetting
 功能描述  : 获取当前UE's usage setting value
 输入参数  : 无
 输出参数  : 无
 返 回 值  : UE's usage setting value
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年2月14日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_LTE_UE_USAGE_SETTING_ENUM_UINT8 NAS_MML_GetLteUeUsageSetting( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.enLteUeUsageSetting;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetVoiceDomainPreference
 功能描述  : 获取当前Voice domain preference for E-UTRAN
 输入参数  : 无
 输出参数  : 无
 返 回 值  : Voice domain preference for E-UTRAN
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年2月14日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_VOICE_DOMAIN_PREFERENCE_ENUM_UINT8 NAS_MML_GetVoiceDomainPreference( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.enVoiceDomainPreference;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetLteImsSupportFlg
 功能描述  : 获取当前LTE下ims是否支持
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ucLteImsSupportFlag:VOS_TRUE  UE支持LTE下的IMS
                                 VOS_FALSE UE不支持LTE下的IMS
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月6日
    作    者   : s00217060
    修改内容   : VOLTE SWITCH新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetLteImsSupportFlg( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.stImsConfig.stImsRatSupport.ucLteImsSupportFlag;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetVoiceCallOnImsSupportFlag
 功能描述  : 获取是否支持IMS语音呼叫标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:支持IMS语音呼叫
             VOS_FALSE:不支持IMS语音呼叫
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月11日
    作    者   : s00217060
    修改内容   : VOLTE SWITCH新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetVoiceCallOnImsSupportFlag( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.stImsConfig.stImsCapability.ucVoiceCallOnImsSupportFlag;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetSmsOnImsSupportFlag
 功能描述  : 获取是否支持IMS短信标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:支持IMS短信
             VOS_FALSE:不支持IMS短信
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月11日
    作    者   : s00217060
    修改内容   : VOLTE SWITCH新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetSmsOnImsSupportFlag( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.stImsConfig.stImsCapability.ucSmsOnImsSupportFlag;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetVideoCallOnImsSupportFlag
 功能描述  : 获取是否支持IMS域VIDEO CALL标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:支持IMS域VIDEO CALL
             VOS_FALSE:不支持IMS域VIDEO CALL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月11日
    作    者   : s00217060
    修改内容   : VOLTE SWITCH新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetVideoCallOnImsSupportFlag( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.stImsConfig.stImsCapability.ucVideoCallOnImsSupportFlag;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetUssdOnImsSupportFlag
 功能描述  : 获取是否支持IMS USSD标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:支持IMS USSD
             VOS_FALSE:不支持IMS USSD
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月11日
    作    者   : s00217060
    修改内容   : VOLTE SWITCH新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetUssdOnImsSupportFlag( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.stImsConfig.stImsCapability.ucUssdOnImsSupportFlag;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetHoWaitSysinfoTimerLen
 功能描述  : 获取CSFB HO流程等系统消息时长信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CSFB HO流程等系统消息时长信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年2月15日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2013年6月7日
   作    者   : z00161729
   修改内容   : SVLTE修改

*****************************************************************************/
VOS_UINT32 NAS_MML_GetHoWaitSysinfoTimerLen(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ulHoWaitSysinfoTimeLen);
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetPsAutoAttachFlg
 功能描述  : 获取当前PS域是否自动Attach标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 获取当前PS域是否自动Attach标识
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月9日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetPsAutoAttachFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.ucPsAutoAttachFlg);
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetRoamingRejectNoRetryCfg
 功能描述  : 获取Nvim中配置
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年4月29日
   作    者   : l00208543
   修改内容   : 新生成函数

*****************************************************************************/

NAS_MML_ROAMINGREJECT_NORETYR_CFG_STRU* NAS_MML_GetRoamingRejectNoRetryCfg( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRoamingRejectNoRetryInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetLauRejNoRetryWhenCmSrvExistCfgInfo
 功能描述  : 获取有业务时LAU被拒是否继续尝试的NV项配置信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MML_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST_CFG_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月21日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST_CFG_STRU* NAS_MML_GetLauRejNoRetryWhenCmSrvExistCfgInfo( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLauRejNoRetryWhenCmSrvExistCfgInfo);
}



/*****************************************************************************
 函 数 名  : NAS_MML_GetRejCauseChangedCounter
 功能描述  : 获取修改拒绝原因值为#17的计数器容器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年11月19日
   作    者   : l00208543
   修改内容   : 新生成函数
2.日    期   : 2014年10月20日
  作    者   : h00285180
  修改内容   : 拒绝原因值优化PhaseII DTS2014110307415
*****************************************************************************/
NAS_MML_REJ_CAUSE_CHANGED_COUNTER_STRU* NAS_MML_GetRejCauseChangedCounter(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stChangeNWCauseInfo.stRejCauseChangedCounter);
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetUserAutoReselActiveFlg
 功能描述  : 获取当前UserAutoResel功能是否使能
 输入参数  : 无
 输出参数  : 无
 返 回 值  : UserAutoResel功能是否使能
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年5月15日
   作    者   : l00130025
   修改内容   : DTS2012012903053:Ts23.122 ch4.4.3.2.1 Auto user reselecton功能支持
*****************************************************************************/
VOS_UINT8 NAS_MML_GetUserAutoReselActiveFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.ucUserAutoReselActiveFlg);
}
/*****************************************************************************
 函 数 名  : NAS_MML_GetUserAutoReselActiveFlg
 功能描述  : 设置当前UserAutoResel功能是否使能
 输入参数  : ucActiveFlag
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年5月15日
   作    者   : l00130025
   修改内容   : DTS2012012903053:Ts23.122 ch4.4.3.2.1 Auto user reselecton功能支持
*****************************************************************************/
VOS_VOID NAS_MML_SetUserAutoReselActiveFlg(VOS_UINT8 ucActiveFlag)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.ucUserAutoReselActiveFlg = ucActiveFlag;
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetMsMode
 功能描述  : 设置当前手机模式
 输入参数  : enMsMode - 设置的手机模式
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月9日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetMsMode(
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.enMsMode = enMsMode;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetLteCsServiceCfg
 功能描述  : 设置Lte支持的cs 业务能力
 输入参数  : enLteCsServiceCfg - 设置LTE支持的cs业务能力
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年10月28日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2012年3月8日
   作    者   : w00167002
   修改内容   : CSFB调整:enLteCsServiceCfg结构体的调整
*****************************************************************************/
VOS_VOID NAS_MML_SetLteCsServiceCfg(
    NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8                   enLteCsServiceCfg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.enLteCsServiceCfg
                               = enLteCsServiceCfg;
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetLteCapabilityStatus
 功能描述  : 设置当前LTE的能力状态
 输入参数  : enLCapabilityStatus - 设置的LTE能力状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年10月26日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetLteCapabilityStatus(
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.enLteCapabilityStatus = enLCapabilityStatus;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetDisableLteReason
 功能描述  : 设置Disable LTE的原因值
 输入参数  : enDisableLteReason - Disable LTE的原因值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年7月27日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_SetDisableLteReason(
    MMC_LMM_DISABLE_LTE_REASON_ENUM_UINT32                  enDisableLteReason
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.enDisableLteReason = enDisableLteReason;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetDisableLteRoamFlg
 功能描述  : 设置禁止LTE漫游标记
 输入参数  : ulDisableFlg - 禁止LTE漫游标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年3月9日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetDisableLteRoamFlg(
    VOS_UINT32                          ulDisableFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.ulDisableLteRoamFlg
                               = ulDisableFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetRoamEnabledMccList
 功能描述  : 设置允许漫游的国家码列表
 输入参数  : pulMcc 允许漫游的国家码列表
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月6日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2013年6月11日
   作    者   : z00161729
   修改内容   : SVLTE调整修改

*****************************************************************************/
VOS_VOID NAS_MML_SetRoamEnabledMccList(VOS_UINT32 *pulMcc)
{
    VOS_UINT32      i;

    for (i=0; i<NAS_MML_ROAM_ENABLED_MAX_MCC_NUMBER; i++)
    {
        NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.stLteRoamCfg.aulRoamEnabledMccList[i] = pulMcc[i];
    }
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetRoamRplmnSearchFlg
 功能描述  : 设置漫游先搜RPLMN特性开关
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年2月25日
   作    者   : t00173447

*****************************************************************************/
VOS_VOID NAS_MML_SetRoamRplmnSearchFlg(VOS_UINT8 ucRoamSearchRPLMNFlg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRoamCfg.ucRoamSearchRPLMNFlg = ucRoamSearchRPLMNFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetRoamRplmnSearchFlg
 功能描述  : 读取漫游时掉网先搜RPLMN标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年2月24日
   作    者   : t00173447
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetRoamRplmnSearchFlg()
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRoamCfg.ucRoamSearchRPLMNFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetInternalMCList
 功能描述  : 设置运营商定制的本国Mcc列表
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年2月25日
   作    者   : t00173447

*****************************************************************************/
VOS_UINT32 *NAS_MML_GetNationalMCCList()
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRoamCfg.aucNationalMccList;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetNationalMCCList
 功能描述  : 设置运营商定制的本国Mcc列表
 输入参数  : pulMcc 运营商定制的本国Mcc列表
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年2月25日
   作    者   : t00173447
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_SetNationalMCCList(VOS_UINT32 *pulMcc)
{
    VOS_UINT32      i;

    for (i=0; i<NAS_MML_MAX_NATIONAL_MCC_NUM; i++)
    {
        NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRoamCfg.aucNationalMccList[i] = pulMcc[i];
    }
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetDisableLTEOnBandFlg
 功能描述  : 设置在W的某个频段上禁用LTE标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年2月24日
   作    者   : t00173447
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetDisableLTEOnBandFlg(VOS_UINT8 ucDisableLTEOnBandFlg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucDisableLTEOnBandFlg = ucDisableLTEOnBandFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetDisableLTEOnBandFlg
 功能描述  : 读取在W的某个频段上禁用LTE标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年2月24日
   作    者   : t00173447
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetDisableLTEOnBandFlg()
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucDisableLTEOnBandFlg;
}



/*****************************************************************************
 函 数 名  : NAS_MML_SetUltraFlashCsfbSupportFlg
 功能描述  : 设置是否支持ultra flash csfb
 输入参数  : ucUltraFlashCsfbSupportFlg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年5月30日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetUltraFlashCsfbSupportFlg(
    VOS_UINT8                           ucUltraFlashCsfbSupportFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucUltraFlashCsfbSupportFlg = ucUltraFlashCsfbSupportFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetUltraFlashCsfbSupportFlg
 功能描述  : 读取是否支持ultra flash csfb
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8:是否支持ultra flash csfb
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年5月30日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetUltraFlashCsfbSupportFlg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucUltraFlashCsfbSupportFlg;
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetLteRoamAllowedFlg
 功能描述  : 设置Lte漫游允许标记
 输入参数  : ucAllowedFlg - Lte漫游允许标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年3月6日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2013年6月11日
   作    者   : z00161729
   修改内容   : SVLTE调整修改
*****************************************************************************/
VOS_VOID NAS_MML_SetLteRoamAllowedFlg(
    VOS_UINT8                           ucAllowedFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.stLteRoamCfg.ucLteRoamAllowedFlg
                               = ucAllowedFlg;
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetEpsRegStatus
 功能描述  : 设置EPS域的注册结果
 输入参数  : enEpsRegStatus:EPS域的注册结果
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年4月18日
   作    者   : l00130025
   修改内容   : DTS2012040200480,设置EPS当前注册状态

*****************************************************************************/
VOS_VOID NAS_MML_SetEpsRegStatus(
    NAS_MML_REG_STATUS_ENUM_UINT8       enEpsRegStatus
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stEpsDomainInfo.enEpsRegStatus = enEpsRegStatus;
}




/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
/*****************************************************************************
 函 数 名  : NAS_MML_SetEpsRegStatus
 功能描述  : 设置LRRC释放连接的原因值是否为CS Fallback High Priority
 输入参数  : ulFlg:VOS_TRUE表示CS Fallback High Priority,VOS_FALSE表示不是CS Fallback High Priority
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年4月1日
   作    者   : l00167671
   修改内容   : 新增函数

*****************************************************************************/
VOS_VOID NAS_MML_SetRelCauseCsfbHighPrioFlg(
    VOS_UINT8       ucFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stEpsDomainInfo.ucIsRelCauseCsfbHighPrio = ucFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetEpsRegStatus
 功能描述  : 获取LRRC释放连接的原因值是否为CS Fallback High Priority
 输入参数  : 无
 输出参数  : 无
 返 回 值  : LRRC释放连接的原因值是否为CS Fallback High Priority
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年4月1日
   作    者   : l00167671
   修改内容   : 新增函数

*****************************************************************************/
VOS_UINT32  NAS_MML_GetRelCauseCsfbHighPrioFlg()
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stEpsDomainInfo.ucIsRelCauseCsfbHighPrio);
}

/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */


/*****************************************************************************
 函 数 名  : NAS_MML_SetDailRejectCfg
 功能描述  : 设置拨号被拒是否使能
 输入参数  : ucEnableFlg - 拨号被拒是否使能
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年3月6日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetDailRejectCfg(
    VOS_UINT8                           ucEnableFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stDailRejectCfg.ucEnableFlg
                               = ucEnableFlg;
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetCsfbServiceStatus
 功能描述  : 设置CSFB状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 设置CSFB状态
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年2月14日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetCsfbServiceStatus(
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                     enCsfbServiceStatus
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.enCsfbServiceStatus = enCsfbServiceStatus;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetVoiceDomainPreference
 功能描述  : 设置voice domain preference
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年2月16日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetVoiceDomainPreference(
    NAS_MML_VOICE_DOMAIN_PREFERENCE_ENUM_UINT8              enVoiceDomainPrefer
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.enVoiceDomainPreference = enVoiceDomainPrefer;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetLteImsSupportFlg
 功能描述  : 设置LTE下ims 是否支持的标志
 输入参数  : ucImsSupportFlg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月6日
    作    者   : s00217060
    修改内容   : VOLTE SWITCH新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetLteImsSupportFlg(
    VOS_UINT8                           ucImsSupportFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.stImsConfig.stImsRatSupport.ucLteImsSupportFlag = ucImsSupportFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetLteImsSupportFlg
 功能描述  : 设置是否支持IMS语音呼叫标志
 输入参数  : ucVoiceCallOnImsSupportFlag - IMS语音呼叫是否支持
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月11日
    作    者   : s00217060
    修改内容   : VOLTE SWITCH新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetVoiceCallOnImsSupportFlag(
    VOS_UINT8                           ucVoiceCallOnImsSupportFlag
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.stImsConfig.stImsCapability.ucVoiceCallOnImsSupportFlag = ucVoiceCallOnImsSupportFlag;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetSmsOnImsSupportFlag
 功能描述  : 设置是否支持IMS短信标志
 输入参数  : ucSmsOnImsSupportFlag - IMS短信是否支持
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月11日
    作    者   : s00217060
    修改内容   : VOLTE SWITCH新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetSmsOnImsSupportFlag(
    VOS_UINT8                           ucSmsOnImsSupportFlag
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.stImsConfig.stImsCapability.ucSmsOnImsSupportFlag = ucSmsOnImsSupportFlag;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetVideoCallOnImsSupportFlag
 功能描述  : 设置是否支持IMS视频呼叫标志
 输入参数  : ucVideoCallOnImsSupportFlag - IMS视频呼叫是否支持
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月11日
    作    者   : s00217060
    修改内容   : VOLTE SWITCH新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetVideoCallOnImsSupportFlag(
    VOS_UINT8                           ucVideoCallOnImsSupportFlag
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.stImsConfig.stImsCapability.ucVideoCallOnImsSupportFlag = ucVideoCallOnImsSupportFlag;
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetUssdOnImsSupportFlag
 功能描述  : 设置是否支持IMS USSD标志
 输入参数  : ucUssdOnImsSupportFlag - IMS USSD是否支持
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月11日
    作    者   : s00217060
    修改内容   : VOLTE SWITCH新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetUssdOnImsSupportFlag(
    VOS_UINT8                           ucUssdOnImsSupportFlag
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.stImsConfig.stImsCapability.ucUssdOnImsSupportFlag = ucUssdOnImsSupportFlag;
}



/*****************************************************************************
 函 数 名  : NAS_MML_SetLteUeUsageSetting
 功能描述  : 设置当前UE's usage setting value
 输入参数  : enUeUsageSetting - UE's usage setting value
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年2月16日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetLteUeUsageSetting(
    NAS_MML_LTE_UE_USAGE_SETTING_ENUM_UINT8                 enUeUsageSetting
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.enLteUeUsageSetting = enUeUsageSetting;
}
/*****************************************************************************
 函 数 名  : NAS_MML_SetT3412Status
 功能描述  : 设置T3412定时器运行状态
 输入参数  : enTimerStatus - 定时器运行状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月1日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetT3412Status(NAS_MML_TIMER_INFO_ENUM_UINT8 enTimerStatus)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stEpsDomainInfo.enT3412Status = enTimerStatus;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetT3423Status
 功能描述  : 设置T3423定时器运行状态
 输入参数  : enTimerStatus - 定时器运行状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月1日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetT3423Status(NAS_MML_TIMER_INFO_ENUM_UINT8 enTimerStatus)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stEpsDomainInfo.enT3423Status = enTimerStatus;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetT3402Status
 功能描述  : 设置T3402定时器运行状态
 输入参数  : enTimerStatus - 定时器运行状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年07月23日
   作    者   : f00179208
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetT3402Status(NAS_MML_TIMER_INFO_ENUM_UINT8 enTimerStatus)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stEpsDomainInfo.enT3402Status = enTimerStatus;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetAdditionUpdateRslt
 功能描述  : 根据联合attach或tau中网侧回复结果中Additional update result IE内容设置对应MML全局变量
 输入参数  : enAdditionUpdRslt - 联合attach或tau中网侧回复结果中Additional update result IE内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月3日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetAdditionUpdateRslt(
    NAS_MML_ADDITION_UPDATE_RSLT_INFO_ENUM_UINT8            enAdditionUpdRslt
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stEpsDomainInfo.enAdditionUpdateRsltInfo = enAdditionUpdRslt;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetEmergencyNumList
 功能描述  : 设置紧急呼号码列表
 输入参数  : pstEmcNumList - 紧急呼叫号码列表
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月12日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetEmergencyNumList (
    NAS_MML_EMERGENCY_NUM_LIST_STRU    *pstEmcNumList
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stEmergencyNumList = *pstEmcNumList;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetTinType
 功能描述  : 设置TinType
 输入参数  : TIN类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月15日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetTinType(
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRplmnCfg.enTinType = enTinType;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetPsBearerCtx
 功能描述  : 设置PS承载信息
 输入参数  : ucRabId        - 承载ID
             pstPsBearerCtx - PS承载信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月15日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetPsBearerCtx(
    VOS_UINT8                           ucRabId,
    NAS_MML_PS_BEARER_CONTEXT_STRU     *pstPsBearerCtx
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.astPsBearerContext[ucRabId - NAS_MML_NSAPI_OFFSET] = *pstPsBearerCtx;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetHoWaitSysinfoTimerLen
 功能描述  : 设置CSFB HO流程等系统消息时长信息
 输入参数  : ulHoWaitSysinfoTimeLen - CSFB HO流程等系统消息时长信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年2月15日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2013年6月7日
   作    者   : z00161729
   修改内容   : SVLTE调整修改
*****************************************************************************/
VOS_VOID NAS_MML_SetHoWaitSysinfoTimerLen(
    VOS_UINT32                          ulHoWaitSysinfoTimeLen
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ulHoWaitSysinfoTimeLen = ulHoWaitSysinfoTimeLen;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetCsfbEmgCallEnableLteTimerLen
 功能描述  : 设置csfb 紧急呼叫 disable lte场景后enable lte 定时器时长
 输入参数  : ulEnalbeLteTimeLen - enable lte 定时器时长
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年6月3日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetCsfbEmgCallEnableLteTimerLen(
    VOS_UINT32                          ulEnalbeLteTimeLen
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ulCsfbEmgCallEnableLteTimerLen = ulEnalbeLteTimeLen;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetCsPsMode1EnableLteTimerLen
 功能描述  : 设置cs ps mode1 disable lte场景enable lte 定时器时长
 输入参数  : ulEnalbeLteTimeLen - enable lte 定时器时长
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年6月3日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2015年1月20日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改

*****************************************************************************/
VOS_VOID NAS_MML_SetCsPsMode13GPPEnableLteTimerLen(
    VOS_UINT32                          ulEnalbeLteTimeLen
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ulCsPsMode13GPPEnableLteTimerLen = ulEnalbeLteTimeLen;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetSvlteSupportFlag
 功能描述  : 设置svlte是否支持标识
 输入参数  : ucSvlteSupportFlag - svlte是否支持的值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年6月3日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetSvlteSupportFlag(
    VOS_UINT8                           ucSvlteSupportFlag
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucSvlteSupportFlag = ucSvlteSupportFlag;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetSvlteSupportFlag
 功能描述  : 获取svlte是否支持标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : svlte特性是否支持的取值
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年6月3日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetSvlteSupportFlag(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucSvlteSupportFlag);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetSvlteSupportFlag
 功能描述  : 设置PS 离网模式
 输入参数  : ucPsTransferOffAreaMode -  离网模式是否支持的值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年5月28日
   作    者   : x00203213
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetPsTransferOffAreaModeFlag(
    VOS_UINT8                           ucPsTransferOffAreaMode
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucPsTransferOffAreaModeFlg = ucPsTransferOffAreaMode;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetPsTransferOffAreaModeFlag
 功能描述  : 获取PS 离网模式是否支持标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : PS 离网模式是否支持的取值
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2014年5月28日
   作    者   : x00203213
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetPsTransferOffAreaModeFlag(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucPsTransferOffAreaModeFlg);
}



/*****************************************************************************
 函 数 名  : NAS_MML_GetCsfbEmgCallEnableLteTimerLen
 功能描述  : 获取csfb紧急呼叫 disable lte场景enable lte 定时器时长
 输入参数  : 无
 输出参数  : 无
 返 回 值  : enable lte 定时器时长
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年6月3日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_GetCsfbEmgCallEnableLteTimerLen(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ulCsfbEmgCallEnableLteTimerLen);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetCsPsMode13GPPEnableLteTimerLen
 功能描述  : 获取cs ps mode1 disable lte场景enable lte 定时器时长
 输入参数  : 无
 输出参数  : 无
 返 回 值  : enable lte 定时器时长
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年6月3日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2015年1月20日
  作    者   : z00161729
  修改内容   : AT&T 支持DAM特性修改

*****************************************************************************/
VOS_UINT32 NAS_MML_GetCsPsMode13GPPEnableLteTimerLen(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ulCsPsMode13GPPEnableLteTimerLen);
}


/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, begin */
/*****************************************************************************
 函 数 名  : NAS_MML_SetCsfbEmgCallLaiChgLauFirstFlg
 功能描述  : 设置紧急呼叫csfb到gu后MM收到系统消息判断LAI改变先进行lau还是先呼叫标志
 输入参数  : ucCsfbEmgCallLaiChgLauFirstFlg - LAI改变先进行lau还是先呼叫标志
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年8月14日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2013年6月11日
   作    者   : z00161729
   修改内容   : SVLTE调整修改
*****************************************************************************/
VOS_VOID NAS_MML_SetCsfbEmgCallLaiChgLauFirstFlg(
    VOS_UINT8                           ucCsfbEmgCallLaiChgLauFirstFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucCsfbEmgCallLaiChgLauFirstFlg
                         = ucCsfbEmgCallLaiChgLauFirstFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetCsfbEmgCallLaiChgLauFirstFlg
 功能描述  : 获取紧急呼叫csfb到gu后MM收到系统消息判断LAI改变先进行lau还是先呼叫标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : LAI改变先进行lau还是先呼叫标志
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年8月14日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2013年6月7日
   作    者   : z00161729
   修改内容   : SVLTE调整修改
*****************************************************************************/
VOS_UINT8 NAS_MML_GetCsfbEmgCallLaiChgLauFirstFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucCsfbEmgCallLaiChgLauFirstFlg);
}

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, end */

/*****************************************************************************
 函 数 名  : NAS_MML_SetPsAutoAttachFlg
 功能描述  : 更新PS域是否自动Attach标识
 输入参数  : usPsAutoAttachFlg - PS域是否自动Attach标识
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月9日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetPsAutoAttachFlg(
    VOS_UINT8                           usPsAutoAttachFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.ucPsAutoAttachFlg = usPsAutoAttachFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetMsSupportBand
 功能描述  : 获取MML中保存当前MS支持的手机Band
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存当前MS支持的手机Band
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_MS_BAND_INFO_STRU* NAS_MML_GetMsSupportBand( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.stMsBand);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetMsPrioRatList
 功能描述  : 获取MML中保存当前MS支持的接入模式和接入优先级
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存当前MS支持的接入模式和接入优先级
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_PLMN_RAT_PRIO_STRU* NAS_MML_GetMsPrioRatList( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.stPrioRatList);
}

/* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
/*****************************************************************************
 函 数 名  : NAS_MML_GetMs3Gpp2PrioRatList
 功能描述  : 获取MML中保存当前MS支持的3GPP2接入模式和接入优先级
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存当前MS支持的3GPP2接入模式和接入优先级
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年2月14日
   作    者   : s00246516
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_3GPP2_RAT_PRIO_STRU* NAS_MML_GetMs3Gpp2PrioRatList( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.st3Gpp2RatList);
}
/* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

/*****************************************************************************
 函 数 名  : NAS_MMC_GetRplmnCfg
 功能描述  : 获取MML中保存RPLMN的配置信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存RPLMN的配置信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/

NAS_MML_RPLMN_CFG_INFO_STRU* NAS_MML_GetRplmnCfg( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRplmnCfg);
}
/*****************************************************************************
 函 数 名  : NAS_MML_GetLastRplmnRat
 功能描述  : 获取MML中保存enLastRplmnRat
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存RPLMN的接入技术
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年8月6日
   作    者   : l00130025
   修改内容   : 新生成函数

*****************************************************************************/

NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MML_GetLastRplmnRat( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRplmnCfg.enLastRplmnRat);
}
/*****************************************************************************
 函 数 名  : NAS_MML_GetLastRplmnRat
 功能描述  : 获取MML中保存enLastRplmnRat
 输入参数  : 最新注册成功的接入技术
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年8月6日
   作    者   : l00130025
   修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID NAS_MML_SetLastRplmnRat(NAS_MML_NET_RAT_TYPE_ENUM_UINT8 enRat)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRplmnCfg.enLastRplmnRat = enRat;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetHplmnCfg
 功能描述  : 获取MML中保存HPLMN的配置信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存HPLMN的配置信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/

NAS_MML_HPLMN_CFG_INFO_STRU* NAS_MML_GetHplmnCfg( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stHplmnCfg);
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetRoamCfg
 功能描述  : 获取MML中保存漫游配置信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存漫游配置信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/

NAS_MML_ROAM_CFG_INFO_STRU* NAS_MML_GetRoamCfg( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRoamCfg);
}

/* Modified by z40661 for 泰国AIS特性 2012-05-17, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_GetAisRoamingCfg
 功能描述  : 获取MML中保存泰国漫游配置信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存泰国漫游配置信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年5月17日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/

NAS_MML_AIS_ROAMING_CFG_STRU* NAS_MML_GetAisRoamingCfg( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRoamCfg.stAisRoamingCfg);
}


/* Modified by z40661 for 泰国AIS特性 2012-05-17, end */



/*****************************************************************************
 函 数 名  : NAS_MML_GetPrioHplmnActCfg
 功能描述  : 获取MML中优先HplmnAct的配置
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 优先HplmnAct的配置
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年6月9日
   作    者   : l00130025
   修改内容   : DTS2012060400029:添加对HPLMNAct优先接入技术的定制；目前USim卡中HPLMNACT很多不支持L
*****************************************************************************/

NAS_MML_PRIO_HPLMNACT_CFG_STRU* NAS_MML_GetPrioHplmnActCfg( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stHplmnCfg.stPrioHplmnActCfg);
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetBgSearchCfg
 功能描述  : 获取MML中保存BG搜索信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存BG搜索信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/

NAS_MML_BG_SEARCH_CFG_INFO_STRU* NAS_MML_GetBgSearchCfg( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stBgSearchCfg);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetPlmnLockCfg
 功能描述  : 获取MML中保存运营商锁网信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存运营商锁网信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/

NAS_MML_PLMN_LOCK_CFG_INFO_STRU* NAS_MML_GetPlmnLockCfg( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stPlmnLockCfg);
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetCustomCfg
 功能描述  : 获取用户定制上下文信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 用户定制上下文信息地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月6日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/

NAS_MML_CUSTOM_CFG_INFO_STRU* NAS_MML_GetCustomCfg( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg);
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetDisabledRatPlmnInfo
 功能描述  : 获取MML中保存禁止接入技术的PLMN信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的禁止接入技术的PLMN信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月15日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2015年4月24日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改函数名称
*****************************************************************************/
NAS_MML_DISABLED_RAT_PLMN_CFG_INFO_STRU* NAS_MML_GetDisabledRatPlmnInfo( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stPlmnLockCfg.stDisabledRatPlmnInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetRatBlackListAccordSimTypeCfg
 功能描述  : 获取MML中保存根据卡类型禁止网络制式的信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的卡类型禁止网络制式的信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 新生成函数
*****************************************************************************/

NAS_MML_RAT_FORBIDDEN_LIST_STRU* NAS_MML_GetRatForbiddenListCfg( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRatForbiddenListInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetGsmForbiddenStatusFlg
 功能描述  : 获取GSM是否被禁止的信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前GSM是否被禁止
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 新生成函数
*****************************************************************************/

NAS_MML_RAT_CAPABILITY_STATUS_ENUM_UINT8 NAS_MML_GetGsmForbiddenStatusFlg( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRatFirbiddenStatusCfg.ucGsmCapaStatus);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetGsmCapabilityStatusAccordRatBlackList
 功能描述  : 设置GSM的禁止信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 新生成函数
*****************************************************************************/

VOS_VOID NAS_MML_SetGsmForbiddenStatusFlg( NAS_MML_RAT_CAPABILITY_STATUS_ENUM_UINT8 enGsmCapaStatus )
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRatFirbiddenStatusCfg.ucGsmCapaStatus = enGsmCapaStatus;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetUtranCapabilityStatusAccordRatBlackList
 功能描述  : 获取Utran是否被禁止的信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前Utran是否被禁止
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 新生成函数
*****************************************************************************/

NAS_MML_RAT_CAPABILITY_STATUS_ENUM_UINT8 NAS_MML_GetUtranForbiddenStatusFlg( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRatFirbiddenStatusCfg.ucUtranCapaStatus);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetUtranCapabilityStatusAccordRatBlackList
 功能描述  : 设置Utran的禁止信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 新生成函数
*****************************************************************************/

VOS_VOID NAS_MML_SetUtranForbiddenStatusFlg( NAS_MML_RAT_CAPABILITY_STATUS_ENUM_UINT8 enUtranCapaStatus )
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRatFirbiddenStatusCfg.ucUtranCapaStatus = enUtranCapaStatus;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetLteCapabilityStatusAccordRatBlackList
 功能描述  : 获取Lte是否被禁止的信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前Lte是否被禁止
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 新生成函数
*****************************************************************************/

NAS_MML_RAT_CAPABILITY_STATUS_ENUM_UINT8 NAS_MML_GetLteForbiddenStatusFlg( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRatFirbiddenStatusCfg.ucLteCapaStatus);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetLteCapabilityStatusAccordRatBlackList
 功能描述  : 设置Lte的禁止信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 新生成函数
*****************************************************************************/

VOS_VOID NAS_MML_SetLteForbiddenStatusFlg( NAS_MML_RAT_CAPABILITY_STATUS_ENUM_UINT8 enLteCapaStatus )
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRatFirbiddenStatusCfg.ucLteCapaStatus = enLteCapaStatus;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetImsiInForbiddenListFlg
 功能描述  : 获取IMSI是否在禁止列表中的信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : IMSI是否在禁止列表中
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 新生成函数
*****************************************************************************/

VOS_UINT8 NAS_MML_GetImsiInForbiddenListFlg( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRatFirbiddenStatusCfg.ucIsImsiInForbiddenListFlg);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetImsiInForbiddenListFlg
 功能描述  : 设置IMSI是否在禁止列表中的全局变量
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 新生成函数
*****************************************************************************/

VOS_VOID NAS_MML_SetImsiInForbiddenListFlg( VOS_UINT8 ucIsImsiInForbiddenList )
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRatFirbiddenStatusCfg.ucIsImsiInForbiddenListFlg = ucIsImsiInForbiddenList;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetMiscellaneousCfgInfo
 功能描述  : 获取MML中保存的运营商特殊的定制特性信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的运营商特殊的定制特性信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月26日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_MISCELLANEOUS_CFG_INFO_STRU* NAS_MML_GetMiscellaneousCfgInfo( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetStkSteeringOfRoamingSupportFlg
 功能描述  : 获取MML中是否支持stk streer of roaming这个特性
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_FALSE:不支持,VOS_TRUE:支持
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetStkSteeringOfRoamingSupportFlg( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.ucStkSteeringOfRoamingSupportFlg);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetStkSteeringOfRoamingSupportFlg
 功能描述  : 设置MML中保存的stk streer of roaming特性信息
 输入参数  : ucStkSteeringOfRoamingSupportFlg - stk streer of roaming特性信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月28日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetStkSteeringOfRoamingSupportFlg(
    VOS_UINT8                           ucStkSteeringOfRoamingSupportFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.ucStkSteeringOfRoamingSupportFlg
                                             = ucStkSteeringOfRoamingSupportFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetHighPrioRatHplmnTimerCfg
 功能描述  : 获取MML中高优先级RAT的HPLMN定时器NV配置信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中高优先级RAT的HPLMN定时器NV配置信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年2月19日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU* NAS_MML_GetHighPrioRatHplmnTimerCfg( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stBgSearchCfg.stHighRatHplmnTimerCfg);
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetHighPrioRatHplmnTimerActiveFlg
 功能描述  : 获取高优先级接入技术的HPLMN定时器是否使能
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:高优先级RAT的HPLMN定时器使能
             VOS_FALSE:高优先级RAT的HPLMN定时器非使能
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月19日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8  NAS_MML_GetHighPrioRatHplmnTimerActiveFlg( VOS_VOID )
{
    NAS_MML_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU             *pstHighRatHplmnTimerCfg = VOS_NULL_PTR;

    pstHighRatHplmnTimerCfg = NAS_MML_GetHighPrioRatHplmnTimerCfg();

    return pstHighRatHplmnTimerCfg->ucActiveFLg;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetHighPrioRatHplmnTimerTdThreshold
 功能描述  : 获取高优先级接入技术的TD下次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 获取高优先级接入技术的TD下次数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月25日
    作    者   : b00269685
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8  NAS_MML_GetHighPrioRatHplmnTimerTdThreshold(VOS_VOID)
{
    NAS_MML_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU             *pstHighRatHplmnTimerCfg = VOS_NULL_PTR;

    pstHighRatHplmnTimerCfg = NAS_MML_GetHighPrioRatHplmnTimerCfg();

    return pstHighRatHplmnTimerCfg->ucTdThreshold;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetStkSteeringOfRoamingSupportFlg
 功能描述  : 获取MML中vodafone的搜网定制需求,CS域失败四次后下发搜网请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_FALSE:不支持,VOS_TRUE:支持
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/

VOS_UINT8 NAS_MML_GetCsRejSearchSupportFlg( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.ucCsRejSearchSupportFlg);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetRoamBrokerActiveFlag
 功能描述  : 获取MML中Roam broker特性是否处于激活状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE: Roam broker特性激活
             VOS_FALSE:Roam broker特性未激活
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年1月17日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetRoamBrokerActiveFlag( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.ucRoamBrokerActiveFlag);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetRoamBrokerRegisterFailCnt
 功能描述  : 获取MML中Roam broker特性注册失败的次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : Roam broker特性注册失败的次数
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetRoamBrokerRegisterFailCnt( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.ucRoamBrokerRegisterFailCnt);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetRoamBrokerRegisterFailCnt
 功能描述  : 设置MML中Roam broker特性注册失败的次数
 输入参数  : ucRoamBrokerRegisterFailCnt - Roam broker特性注册失败的次数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetRoamBrokerRegisterFailCnt(
    VOS_UINT8                           ucRoamBrokerRegisterFailCnt
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.ucRoamBrokerRegisterFailCnt
                       = ucRoamBrokerRegisterFailCnt;
}
/*****************************************************************************
 函 数 名  : NAS_MML_GetDtSingleDomainPlmnSearchFlag
 功能描述  : 获取MML中 DT定制，单域注册被拒发起搜网标识
 输入参数  : ucPlmnSrchFlag - dt定制需求
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年8月5日
   作    者   : l00130025
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetDtSingleDomainPlmnSearchFlag( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.ucSingleDomainFailPlmnSrchFlag);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetDtSingleDomainPlmnSearchFlag
 功能描述  : 设置MML中 DT定制，单域注册被拒发起搜网标识
 输入参数  : ucPlmnSrchFlag - dt定制需求
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年8月5日
   作    者   : l00130025
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetDtSingleDomainPlmnSearchFlag(
    VOS_UINT8                           ucPlmnSrchFlag
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.ucSingleDomainFailPlmnSrchFlag
                       = ucPlmnSrchFlag;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetCsRejSearchSupportFlg
 功能描述  : 设置MML中vodafone的搜网定制需求,CS域失败四次后是否下发搜网请求标识
 输入参数  : ucCsRejSearchSupportFlg - CS域失败四次后是否下发搜网请求标识
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月25日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetCsRejSearchSupportFlg(
    VOS_UINT8                           ucCsRejSearchSupportFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.ucCsRejSearchSupportFlg
                                        = ucCsRejSearchSupportFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetCarryEplmnWhenSrchRplmnCfg
 功能描述  : 获取MML中保存搜索RPLMN时是否需要携带EPLMN场景配置信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存搜索RPLMN时是否需要携带EPLMN场景配置信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年8月13日
   作    者   : l00289540
   修改内容   : 新生成函数
*****************************************************************************/

NAS_MML_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG_STRU* NAS_MML_GetCarryEplmnWhenSrchRplmnCfg( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stCarryEplmnWhenSrchRplmnCfg);
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetCampPlmnInfo
 功能描述  : 获取MML中保存的当前驻留PLMN信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的当前驻留PLMN信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/

NAS_MML_CAMP_PLMN_INFO_STRU* NAS_MML_GetCurrCampPlmnInfo( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo) ;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetCampCellInfo
 功能描述  : 获取MML中保存的当前驻留小区信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的当前驻留小区信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/

NAS_MML_CAMP_CELL_INFO_STRU* NAS_MML_GetCampCellInfo( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.stCampCellInfo) ;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetCurrNetType
 功能描述  : 获取当前的网络接入模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前的网络接入模式
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月16日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_NET_RAT_TYPE_ENUM_UINT8  NAS_MML_GetCurrNetRatType( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.enNetRatType) ;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetCurrNetType
 功能描述  : 更新当前的网络接入模式
 输入参数  : enNetRatType:当前网络接入模式
 输出参数  : 无
 返 回 值  : 当前的网络接入模式
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月16日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_SetCurrNetRatType(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetRatType
)
{
    (NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.enNetRatType) = enNetRatType ;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetRfAvailFlg
 功能描述  : 获取当前搜网失败RF资源是否可用标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:当前RF资源可用
             VOS_FALSE:当前RF资源不可用
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月29日
    作    者   : z00161729
    修改内容   : 新生成函数
                 当前是否因NO RF导致的搜网失败，接入层上报NO RF则设置为VOS_TRUE,
                 MMC发起搜网时则设置为VOS_FALSE。
*****************************************************************************/
VOS_UINT8 NAS_MML_GetRfAvailFlg( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stNoRfInfo.ucRfAvailFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetRfAvailFlg
 功能描述  : 设置当前搜网失败RF资源是否可用标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:当前RF资源可用
             VOS_FALSE:当前RF资源不可用
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月29日
    作    者   : z00161729
    修改内容   : 新生成函数
                 当前是否因NO RF导致的搜网失败，接入层上报NO RF则设置为VOS_TRUE,
                 MMC发起搜网时则设置为VOS_FALSE。
*****************************************************************************/
VOS_VOID NAS_MML_SetRfAvailFlg(
    VOS_UINT8                           ucRfAvailFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stNoRfInfo.ucRfAvailFlg = ucRfAvailFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetNoRfRatType
 功能描述  : 查询当前搜网失败NO RF时的接入技术
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MML_NET_RAT_TYPE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月21日
    作    者   : w00167002
    修改内容   : 新生成函数:NO RF搜网失败时候的接入技术
  2.日    期   : 2013年4月03日
    作    者   : y00176023
    修改内容   : DSDS GUNAS II项目:更改NO RF相关名称
  3.日    期   : 2013年6月30日
    作    者   : w00176964
    修改内容   : DSDS III调整
  4.日    期   : 2014年12月29日
    作    者   : z00161729
    修改内容   : DSDS业务重拨时no rf未触发搜网导致业务失败，mm在no cell available状态no rf时给mmc发送cm service ind触发搜网

*****************************************************************************/
NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MML_GetNoRfRatType( VOS_VOID )
{
    if (VOS_TRUE == NAS_MML_GetRfAvailFlg())
    {
        return NAS_MML_NET_RAT_TYPE_BUTT;
    }

    return NAS_MML_GetMmlCtx()->stNetworkInfo.stNoRfInfo.enRatType;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetCurrRatRfAvailFlg
 功能描述  : 设置当前搜网失败NO RF存在标志和当时的接入技术
 输入参数  : ucRfAvail              : RF资源可用标记
             enRatType              : NO RF对应的接入技术
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月21日
    作    者   : w00167002
    修改内容   : 新生成函数
                 当前是否因NO RF导致的搜网失败，接入层上报NO RF则设置为VOS_TRUE,
                 MMC发起搜网时则设置为VOS_FALSE。
  2.日    期   : 2013年4月03日
    作    者   : y00176023
    修改内容   : DSDS GUNAS II项目:更改NO RF相关名称
  3.日    期   : 2013年4月03日
    作    者   : w00176964
    修改内容   : DSDS III项目调整:修改变量名称
  4.日    期   : 2014年12月29日
    作    者   : z00161729
    修改内容   : DSDS业务重拨时no rf未触发搜网导致业务失败，mm在no cell available状态no rf时给mmc发送cm service ind触发搜网
*****************************************************************************/
VOS_VOID  NAS_MML_SetCurrRatRfAvailFlg(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType,
    VOS_UINT8                           ucRfAvail
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stNoRfInfo.ucRfAvailFlg  = ucRfAvail;
    NAS_MML_GetMmlCtx()->stNetworkInfo.stNoRfInfo.enRatType     = enRatType;

    return;
}



/*****************************************************************************
 函 数 名  : NAS_MML_SetCurrSysSubMode
 功能描述  : 更新当前驻留网络系统模式
 输入参数  : NAS_MML_RRC_SYS_SUBMODE_ENUM_UINT8  enSysSubMode
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月23日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_SetCurrSysSubMode(
    NAS_MML_RRC_SYS_SUBMODE_ENUM_UINT8  enSysSubMode
)
{
    (NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.enSysSubMode) = enSysSubMode ;
}
/*****************************************************************************
 函 数 名  : NAS_MML_GetCurrCampPlmnId
 功能描述  : 获取当前驻留网络的PLMNID
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月16日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_PLMN_ID_STRU*  NAS_MML_GetCurrCampPlmnId( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.stLai.stPlmnId) ;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetCurrCampLai
 功能描述  : 获取当前驻留网络的LAI
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月28日
    作    者   : l00130025
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_LAI_STRU*  NAS_MML_GetCurrCampLai( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.stLai) ;
}

/*****************************************************************************
 函 数 名  : NAS_MML_InitSimCsgInfo
 功能描述  : 初始化csg卡相关信息
 输入参数  : pstSimCsgInfo - csg卡相关信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年10月20日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_VOID NAS_MML_InitSimCsgInfo(
    NAS_MML_SIM_CSG_INFO_STRU          *pstSimCsgInfo
)
{
    VOS_UINT32                          ulIndex;

    PS_MEM_SET(&pstSimCsgInfo->stAllowedCsgList, 0, sizeof(pstSimCsgInfo->stAllowedCsgList));
    PS_MEM_SET(&pstSimCsgInfo->stOperatorCsgList, 0, sizeof(pstSimCsgInfo->stOperatorCsgList));
    PS_MEM_SET(&pstSimCsgInfo->stForbiddenCsgList, 0, sizeof(pstSimCsgInfo->stForbiddenCsgList));

    for (ulIndex = 0; ulIndex < NAS_MML_MAX_PLMN_CSG_ID_NUM; ulIndex++)
    {
        pstSimCsgInfo->stAllowedCsgList.astPlmnWithCsgIdInfo[ulIndex].stPlmnWithCsgId.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
        pstSimCsgInfo->stAllowedCsgList.astPlmnWithCsgIdInfo[ulIndex].stPlmnWithCsgId.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
        pstSimCsgInfo->stAllowedCsgList.astPlmnWithCsgIdInfo[ulIndex].stPlmnWithCsgId.ulCsgId        = NAS_MML_INVALID_CSG_ID_VALUE;

        pstSimCsgInfo->stOperatorCsgList.astPlmnWithCsgIdInfo[ulIndex].stPlmnWithCsgId.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
        pstSimCsgInfo->stOperatorCsgList.astPlmnWithCsgIdInfo[ulIndex].stPlmnWithCsgId.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
        pstSimCsgInfo->stOperatorCsgList.astPlmnWithCsgIdInfo[ulIndex].stPlmnWithCsgId.ulCsgId        = NAS_MML_INVALID_CSG_ID_VALUE;
    }

    for (ulIndex = 0; ulIndex <NAS_MML_MAX_FORBIDDEN_CSG_ID_NUM; ulIndex++)
    {
        pstSimCsgInfo->stForbiddenCsgList.astForbiddenCsgIdPeriodInfo[ulIndex].stPlmnWithCsgIdInfo.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
        pstSimCsgInfo->stForbiddenCsgList.astForbiddenCsgIdPeriodInfo[ulIndex].stPlmnWithCsgIdInfo.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
        pstSimCsgInfo->stForbiddenCsgList.astForbiddenCsgIdPeriodInfo[ulIndex].stPlmnWithCsgIdInfo.ulCsgId        = NAS_MML_INVALID_CSG_ID_VALUE;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetAllowedCsgList
 功能描述  : 获取Alllowed CSG list信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MML_PLMN_WITH_CSG_ID_LIST_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年9月9日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
NAS_MML_PLMN_WITH_CSG_ID_LIST_STRU*  NAS_MML_GetAllowedCsgList(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stSimInfo.stSimCsgInfo.stAllowedCsgList);
}
/*****************************************************************************
 函 数 名  : NAS_MML_GetOperatorCsgList
 功能描述  : 获取Operator CSG list信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MML_PLMN_WITH_CSG_ID_LIST_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年9月9日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
NAS_MML_PLMN_WITH_CSG_ID_LIST_STRU* NAS_MML_GetOperatorCsgList(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stSimInfo.stSimCsgInfo.stOperatorCsgList);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetForbiddenCsgList
 功能描述  : 获取forbidden CSG list信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : foridden CSG List信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年9月9日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
NAS_MML_CSG_ID_WITH_FORBIDDEN_PERIOD_LIST_STRU* NAS_MML_GetForbiddenCsgList(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stSimInfo.stSimCsgInfo.stForbiddenCsgList);
}
/*****************************************************************************
 函 数 名  : NAS_MML_GetCsgDisplayCtrlFlag
 功能描述  : 获取MML中保存的从Usim卡EFAD文件中csg display ctrl bit信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年9月30日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT8 NAS_MML_GetCsgDisplayCtrlFlag(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.ucCsgDisplayCtrlFlag);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetCsgDisplayCtrlFlag
 功能描述  : 设置MML中保存的从Usim卡EFAD文件中csg display ctrl bit信息
 输入参数  : ucCsgDisplayCtrlFlag - csg display ctrl bit信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年9月30日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_VOID NAS_MML_SetCsgDisplayCtrlFlag(
    VOS_UINT8                           ucCsgDisplayCtrlFlag
)
{
    NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.ucCsgDisplayCtrlFlag = ucCsgDisplayCtrlFlag;
    return;
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetCsgSupportFlag
 功能描述  : 设置当前是否开启了CSG功能
 输入参数  : ucCsgSupportFlag - 是否支持CSG功能标识
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年9月17日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_VOID NAS_MML_SetCsgSupportFlag(
    VOS_UINT8                           ucCsgSupportFlag
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stCsgCfgInfo.ucCsgSupportFlag = ucCsgSupportFlag;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetCsgSupportFlag
 功能描述  : 获取是否支持CSG功能标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 是否支持CSG功能标识
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年9月17日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_UINT8 NAS_MML_GetCsgSupportFlag(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stCsgCfgInfo.ucCsgSupportFlag;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetOnlyReportOperatorCsgListFlag
 功能描述  : 获取CSG列表搜网结果是否仅上报在operator csg list中的CSG ID信息标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年10月12日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_UINT8 NAS_MML_GetOnlyReportOperatorCsgListFlag(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stCsgCfgInfo.ucOnlyReportOperatorCsgListFlag;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetOnlyReportOperatorCsgListFlag
 功能描述  : 设置CSG列表搜网结果是否仅上报在operator csg list中的CSG ID信息标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年10月12日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_VOID NAS_MML_SetOnlyReportOperatorCsgListFlag(
    VOS_UINT8                           ucOnlyReportOperatorCsgListFlag
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stCsgCfgInfo.ucOnlyReportOperatorCsgListFlag = ucOnlyReportOperatorCsgListFlag;
    return;
}

/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
/*****************************************************************************
 函 数 名  : NAS_MML_GetOldCampLai
 功能描述  : 获取上次驻留网络的LAI
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月28日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_LAI_STRU*  NAS_MML_GetOldCampLai( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.stOldLai) ;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetCurrCampLac
 功能描述  : 获取当前驻留网络的LAC
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月3日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MML_GetCurrCampLac( VOS_VOID )
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCurCampInfo      = VOS_NULL_PTR;
    VOS_UINT32                          ulLac;

    pstCurCampInfo = &(NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo);

    ulLac  = (pstCurCampInfo->stLai.aucLac[0] << 8) & 0xFF00;
    ulLac |= pstCurCampInfo->stLai.aucLac[1];

    return ulLac;
}

/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

/*****************************************************************************
 函 数 名  : NAS_MML_GetCurrCampRac
 功能描述  : 获取当前驻留网络的RAC
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前驻留网络的RAC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月28s日
    作    者   : l00130025
    修改内容   : 新生成函数

*****************************************************************************/

VOS_UINT8 NAS_MML_GetCurrCampRac(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.ucRac;
}

/* Added by s00246516 for L-C互操作项目, 2014-02-12, Begin */
/*****************************************************************************
 函 数 名  : NAS_MML_GetCurrCampArfcn
 功能描述  : 获取当前驻留网络的频点
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前驻留网络的频点
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : s00246516
    修改内容   : 新生成函数
  2.日    期   : 2015年7月20日
    作    者   : w000316404
    修改内容   : R11协议升级(LTE频点配置值扩展)

*****************************************************************************/

VOS_UINT32 NAS_MML_GetCurrCampArfcn(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.stCampCellInfo.ulArfcn;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetCurrCampArfcn
 功能描述  : 设置当前驻留网络的频点
 输入参数  : usArfcn--当前驻留网络的频点
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : s00246516
    修改内容   : 新生成函数
  2.日    期   : 2015年7月20日
    作    者   : w000316404
    修改内容   : R11协议升级(LTE频点配置值扩展)

*****************************************************************************/

VOS_VOID NAS_MML_SetCurrCampArfcn(
    VOS_UINT32                          ulArfcn
)
{
    (NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.stCampCellInfo.ulArfcn) = ulArfcn;
}
/* Added by s00246516 for L-C互操作项目, 2014-02-12, End */

/*****************************************************************************
 函 数 名  : NAS_MML_GetCurrBandInfo
 功能描述  : 获取MML中保存的当前驻留频段信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的当前驻留PLMN信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/

NAS_MML_MS_BAND_INFO_STRU* NAS_MML_GetCurrBandInfo( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stBandInfo) ;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetCsDomainInfo
 功能描述  : 获取MML中保存的CS域信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的CS域信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/

NAS_MML_CS_DOMAIN_INFO_STRU* NAS_MML_GetCsDomainInfo( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo);
}

/*****************************************************************************
 函 数 名  : NAS_GetCsDomainInfo
 功能描述  : 获取T3212长度
 输入参数  : 无
 输出参数  : 无
 返 回 值  : T3212长度
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年12月16日
   作    者   : h00360002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_GetT3212Len( VOS_VOID )
{
    return NAS_MML_GetCsDomainInfo()->ulT3212Len;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetCsRegStatus
 功能描述  : 更新CS域的注册结果
 输入参数  : enCsRegStatus:CS域需要更新的注册结果
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月23日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetCsRegStatus(
    NAS_MML_REG_STATUS_ENUM_UINT8       enCsRegStatus
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.enCsRegStatus = enCsRegStatus;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetCsRegStatus
 功能描述  : 获取CS域的注册结果
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CS域的注册结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月23日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_REG_STATUS_ENUM_UINT8  NAS_MML_GetCsRegStatus( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.enCsRegStatus);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetCsLastSuccLai
 功能描述  : 获取MML中保存的CS域最后一次注册成功的LAI信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的CS域最后一次注册成功的LAI信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/

NAS_MML_LAI_STRU* NAS_MML_GetCsLastSuccLai( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stLastSuccLai)   ;
}

/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-2, begin */
/*****************************************************************************
 函 数 名  : NAS_MML_GetCsLastSuccLac
 功能描述  : 获取MML中保存的CS域最后一次注册成功的LAC
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的CS域最后一次注册成功的LAC
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年4月2日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_GetCsLastSuccLac( VOS_VOID )
{
    NAS_MML_LAI_STRU                   *pstCsSuccLai = VOS_NULL_PTR;
    VOS_UINT32                          ulCsSuccLac;

    pstCsSuccLai    = &(NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stLastSuccLai);

    ulCsSuccLac = (pstCsSuccLai->aucLac[0] << 8) & 0xFF00;
    ulCsSuccLac |= pstCsSuccLai->aucLac[1];

    return ulCsSuccLac;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetCsLastSuccPlmnId
 功能描述  : 获取MML中保存的CS域最后一次注册成功的PLMN ID
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的CS域最后一次注册成功的PLMN ID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月2日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_PLMN_ID_STRU*  NAS_MML_GetCsLastSuccPlmnId( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stLastSuccLai.stPlmnId) ;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetCsLastSuccMcc
 功能描述  : 获取MML中保存的CS域最后一次注册成功的PLMN的MCC
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的CS域最后一次注册成功的PLMN的MCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月28日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MML_GetCsLastSuccMcc( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stLastSuccLai.stPlmnId.ulMcc) ;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetCsLastSuccMnc
 功能描述  : 获取MML中保存的CS域最后一次注册成功的PLMN的MNC
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的CS域最后一次注册成功的PLMN的MNC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月28日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MML_GetCsLastSuccMnc( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stLastSuccLai.stPlmnId.ulMnc) ;
}

/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-2, end */

/*****************************************************************************
 函 数 名  : NAS_MML_GetPsLastSuccRai
 功能描述  : 获取MML中保存的PS域最后一次注册成功的RAI信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的PS域最后一次注册成功的RAI信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/

NAS_MML_RAI_STRU* NAS_MML_GetPsLastSuccRai( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stLastSuccRai)   ;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetPsDomainInfo
 功能描述  : 获取MML中保存的PS域信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的PS域信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/

NAS_MML_PS_DOMAIN_INFO_STRU* NAS_MML_GetPsDomainInfo( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo);
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetPsRegStatus
 功能描述  : 获取PS域的注册结果
 输入参数  : 无
 输出参数  : 无
 返 回 值  : PS域的注册结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月23日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_REG_STATUS_ENUM_UINT8  NAS_MML_GetPsRegStatus( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.enPsRegStatus);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetPsRegStatus
 功能描述  : 设置PS域的注册结果
 输入参数  : enPsRegStatus:PS域的注册结果
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月23日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetPsRegStatus(
    NAS_MML_REG_STATUS_ENUM_UINT8       enPsRegStatus
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.enPsRegStatus = enPsRegStatus;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetNetwork3GppRel
 功能描述  : 获取MML中保存的当前网络的协议版本
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的当前网络的协议版本
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/

NAS_MML_NETWORK_3GPP_REL_STRU* NAS_MML_GetNetwork3GppRel( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stNetwork3GppRel)  ;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetEquPlmnList
 功能描述  : 获取MML中保存的当前EQU PLMN信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的当前EQU PLMN信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/

NAS_MML_EQUPLMN_INFO_STRU* NAS_MML_GetEquPlmnList( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stEquPlmnInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetSuitPlmnList
 功能描述  : 获取MML中保存的当前小区系统消息中共享网络信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的共享网络信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年4月19日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改

*****************************************************************************/
NAS_MML_SUIT_PLMN_LIST_STRU* NAS_MML_GetSuitPlmnList(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stSuitPlmnListInfo);
}




/*****************************************************************************
 函 数 名  : NAS_MML_GetGmmProcInfo
 功能描述  : 获取GMM过程信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MML_GMM_PROC_INFO_STRU
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年4月21日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
NAS_MML_GMM_PROC_INFO_STRU *NAS_MML_GetGmmProcInfo( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stGmmProcInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetGmmProcType
 功能描述  : 设置GMM过程类型
 输入参数  : enGmmProcType - GMM过程类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年4月21日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID NAS_MML_SetGmmProcType(
    NAS_MML_GMM_PROC_TYPE_ENUM_UINT16   enGmmProcType
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stGmmProcInfo.enGmmProcType = enGmmProcType;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetGmmProcFlag
 功能描述  : 设置GMM过程标识
 输入参数  : enGmmProcFlag - GMM过程标识
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年4月21日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID NAS_MML_SetGmmProcFlag(
    NAS_MML_GMM_PROC_FLAG_ENUM_UINT16   enGmmProcFlag
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stGmmProcInfo.enGmmProcFlag = enGmmProcFlag;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetSmProcFlag
 功能描述  : 设置SM过程标识
 输入参数  : enSmProcFlag - SM过程标识
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年4月21日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID NAS_MML_SetSmProcFlag(
    NAS_MML_SM_PROC_FLAG_ENUM_UINT8     enSmProcFlag
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.enSmProcFlag = enSmProcFlag;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetSmProcFlag
 功能描述  : 获取SM过程标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : SM过程标识
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年4月21日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
NAS_MML_SM_PROC_FLAG_ENUM_UINT8 NAS_MML_GetSmProcFlag(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.enSmProcFlag;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetEpsServiceConnStatusFlg
 功能描述  : 获取EPS域的数据连接状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : EPS的链接存在状态
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年4月19日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改

*****************************************************************************/
VOS_UINT8 NAS_MML_GetEpsServiceConnStatusFlg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucEpsServiceConnStatusFlg;
}

/*****************************************************************************
函 数 名  : NAS_MML_InitSuitPlmnInfo
功能描述  : 初始化共享网络信息
输入参数  : pstSuitPlmnListInfo:初始化共享网络信息
输出参数  : 无
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2015年4月19日
  作    者   : z00161729
  修改内容   : 24301 R11 CR升级项目修改

*****************************************************************************/
VOS_VOID  NAS_MML_InitSuitPlmnListInfo(
    NAS_MML_SUIT_PLMN_LIST_STRU        *pstSuitPlmnListInfo
)
{
    VOS_UINT32                          ucIndex;

    PS_MEM_SET(pstSuitPlmnListInfo, 0, sizeof(NAS_MML_SUIT_PLMN_LIST_STRU));
    pstSuitPlmnListInfo->ucSuitPlmnNum = 0;

    for (ucIndex = 0 ; ucIndex < MMC_LMM_MAX_SRCH_PLMN_NUM; ucIndex++ )
    {
        pstSuitPlmnListInfo->astSuitPlmnList[ucIndex].ulMcc = NAS_MML_INVALID_MCC;
        pstSuitPlmnListInfo->astSuitPlmnList[ucIndex].ulMnc = NAS_MML_INVALID_MNC;
    }

    return;
}



/*****************************************************************************
 函 数 名  : NAS_MML_GetConnStatus
 功能描述  : 获取MML中保存的当前连接状态和业务状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的当前连接状态和业务状态
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_CONN_STATUS_INFO_STRU* NAS_MML_GetConnStatus(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus)  ;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetRrcConnStatusFlg
 功能描述  : 设置RRC的连接状态
 输入参数  : ucRrcStatusFlg:RRC链接存在状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetRrcConnStatusFlg(
    VOS_UINT8                           ucRrcStatusFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucRrcStatusFlg
        = ucRrcStatusFlg;
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetCsSigConnStatusFlg
 功能描述  : 设置CS域的信令连接状态
 输入参数  : ucCsSigConnStatusFlg:CS域的信令链接存在状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetCsSigConnStatusFlg(
    VOS_UINT8                           ucCsSigConnStatusFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucCsSigConnStatusFlg
        = ucCsSigConnStatusFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetCsSigConnStatusFlg
 功能描述  : 设置CS域的信令连接状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ucCsSigConnStatusFlg:CS域的信令链接存在状态
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年2月24日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetCsSigConnStatusFlg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucCsSigConnStatusFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetPsSigConnStatusFlg
 功能描述  : 设置PS域的信令连接状态
 输入参数  : ucPsSigConnStatusFlg:PS域的信令链接存在状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetPsSigConnStatusFlg(
    VOS_UINT8                           ucPsSigConnStatusFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucPsSigConnStatusFlg
        = ucPsSigConnStatusFlg;
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetPsSigConnStatusFlg
 功能描述  : 设置PS域的TBF存在状态
 输入参数  : ucPsTbfStatusFlg:PS域的TBF链接存在状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetPsTbfStatusFlg(
    VOS_UINT8                           ucPsTbfStatusFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucPsTbfStatusFlg
        = ucPsTbfStatusFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMG_GetPsTbfStatusFlg
 功能描述  : 获取PS域的TBF存在状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回PS域的TBF存在状态
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/

VOS_UINT8 NAS_MML_GetPsTbfStatusFlg( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucPsTbfStatusFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetEpsSigConnStatusFlg
 功能描述  : 设置EPS域的信令连接状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetEpsSigConnStatusFlg(
    VOS_UINT8                           ucEpsSigConnStatusFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucEpsSigConnStatusFlg
        = ucEpsSigConnStatusFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetEpsServiceConnStatusFlg
 功能描述  : 设置EPS域的数据连接状态
 输入参数  : ucEpsServiceConnStatusFlg:EPS的链接存在状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetEpsServiceConnStatusFlg(
    VOS_UINT8                           ucEpsServiceConnStatusFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucEpsServiceConnStatusFlg
        = ucEpsServiceConnStatusFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetCsServiceConnStatusFlg
 功能描述  : 设置CS域的业务存在状态
 输入参数  : ucCsServiceConnStatusFlg:CS域的业务存在状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetCsServiceConnStatusFlg(
    VOS_UINT8                           ucCsServiceConnStatusFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucCsServiceConnStatusFlg
        = ucCsServiceConnStatusFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetCsServiceConnStatusFlg
 功能描述  : 获取CS域的业务存在状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CS域的业务存在状态
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年3月3日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetCsServiceConnStatusFlg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucCsServiceConnStatusFlg;
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetCsServiceBufferStatusFlg
 功能描述  : 设置CS域的缓存业务存在状态
 输入参数  : ucCsServiceConnStatusFlg:CS域的缓存业务存在状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetCsServiceBufferStatusFlg(
    VOS_UINT8                           ucCsServiceBufferStatusFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucCsServiceBufferFlg
        = ucCsServiceBufferStatusFlg;
}

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-22, begin */

/*****************************************************************************
 函 数 名  : NAS_MML_GetCsServiceBufferStatusFlg
 功能描述  : 获取CS域的缓存业务存在状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CS域的缓存业务存在状态
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月22日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetCsServiceBufferStatusFlg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucCsServiceBufferFlg;
}
/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-22, end */


/*****************************************************************************
 函 数 名  : NAS_MML_SetPsServiceBufferStatusFlg
 功能描述  : 设置PS域的缓存业务存在状态
 输入参数  : ucPsServiceConnStatusFlg:CS域的缓存业务存在状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetPsServiceBufferStatusFlg(
    VOS_UINT8                           ucPsServiceBufferStatusFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucPsServiceBufferFlg
        = ucPsServiceBufferStatusFlg;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetPsServiceBufferStatusFlg
 功能描述  : 获取PS域的缓存业务存在状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ucPsServiceConnStatusFlg:PS域的缓存业务存在状态
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月24日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetPsServiceBufferStatusFlg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucPsServiceBufferFlg;
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetCsEmergencyServiceFlg
 功能描述  : 设置CS域的业务是否为紧急呼叫业务
 输入参数  : ucEmergencyServiceFlg:CS域的业务是否为紧急呼叫业务
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetCsEmergencyServiceFlg(
    VOS_UINT8                           ucEmergencyServiceFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucEmergencyServiceFlg
        = ucEmergencyServiceFlg;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetCsEmergencyServiceFlg
 功能描述  : 判断CS域的业务
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 是否为紧急呼叫业务
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetCsEmergencyServiceFlg(VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucEmergencyServiceFlg);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetPsTcServiceFlg
 功能描述  : 设置通过PS域建立TC环回业务的标志
 输入参数  : VOS_UINT8                           ucPsTcServiceFlg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月30日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetPsTcServiceFlg(
    VOS_UINT8                           ucPsTcServiceFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucPsTcServiceFlg
        = ucPsTcServiceFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetEHplmnSupportFlg
 功能描述  : 获取MML中保存EHPLMN的是否支持的配置信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存EHPLMN的是否支持的配置信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/

VOS_UINT8 NAS_MML_GetEHplmnSupportFlg( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stHplmnCfg.ucEhplmnSupportFlg);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetActingHplmnSupportFlg
 功能描述  : 获取MML中保存ActingHPlmn的是否支持的配置信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存ActingHPlmn的是否支持的配置信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年6月11日
   作    者   : w00166186
   修改内容   : 新生成函数

*****************************************************************************/

VOS_UINT8 NAS_MML_GetActingHplmnSupportFlg( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stHplmnCfg.ucActingHPlmnSupportFlg);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetActingHplmnSupportFlg
 功能描述  : 设置MML中保存ActingHPlmn的是否支持的配置信息
 输入参数  : ucActingHPlmnSupportFlg ActingHPlmn的是否支持的配置信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年6月11日
   作    者   : w00166186
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetActingHplmnSupportFlg(VOS_UINT8 ucActingHPlmnSupportFlg)
{
   NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stHplmnCfg.ucActingHPlmnSupportFlg  = ucActingHPlmnSupportFlg;
}



/*****************************************************************************
 函 数 名  : NAS_MML_GetCsAttachAllowFlg
 功能描述  : 获取MML中保存的CS域是否允许ATTACH的标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的CS域是否允许ATTACH的标志
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetCsAttachAllowFlg( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.ucCsAttachAllow);
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetPsAttachAllowFlg
 功能描述  : 获取MML中保存的PS域是否允许ATTACH的标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的PS域是否允许ATTACH的标志
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetPsAttachAllowFlg( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.ucPsAttachAllow);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetCsAttachAllowFlg
 功能描述  : 更新MML中保存的CS域是否允许ATTACH的标志
 输入参数  : ucCsAttachAllowFlg:CS域是否允许ATTACH的标志
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID NAS_MML_SetCsAttachAllowFlg(
    VOS_UINT8                           ucCsAttachAllowFlg
)
{
    (NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.ucCsAttachAllow) = ucCsAttachAllowFlg;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetMoCallStatus
 功能描述  : 获取MML中保存的呼叫建立状态标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的呼叫建立状态标志
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月15日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_MO_CALL_STATUS_ENUM_UINT8 NAS_MML_GetMoCallStatus( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stCmSrvStatus.enMoCallStatus);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetMoCallStatus
 功能描述  : 更新MML中保存的呼叫建立状态标志
 输入参数  : enCallStatus:呼叫建立状态标志
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年8月15日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID NAS_MML_SetMoCallStatus(
    NAS_MML_MO_CALL_STATUS_ENUM_UINT8   enMoCallStatus
)
{
    (NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stCmSrvStatus.enMoCallStatus) = enMoCallStatus;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetMoSsStatus
 功能描述  : 获取MML中保存的SS建立状态标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的SS建立状态标志
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月15日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_MO_SS_STATUS_ENUM_UINT8 NAS_MML_GetMoSsStatus( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stCmSrvStatus.enMoSsStatus);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetMoSsStatus
 功能描述  : 更新MML中保存的SS建立状态标志
 输入参数  : enSsStatus:SS建立状态标志
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年8月15日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetMoSsStatus(
    NAS_MML_MO_SS_STATUS_ENUM_UINT8     enMoSsStatus
)
{
    (NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stCmSrvStatus.enMoSsStatus) = enMoSsStatus;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetPsLocalDetachFlag
 功能描述  : 获取MML中保存的ps是否本地detach标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 获取MML中保持的ps是否本地detach标识
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年01月03日
   作    者   : z00161729
   修改内容   : DTS2014010202583:SVLTE优化G-TL ps切换性能修改

*****************************************************************************/
VOS_UINT8 NAS_MML_GetPsLocalDetachFlag( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.ucPsLocalDetachFlag);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetPsLocalDetachFlag
 功能描述  : 设置MML中保存的ps是否本地detach标识
 输入参数  : ucPsLocalDetachFlag - ps是否本地detach标识
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年01月03日
   作    者   : z00161729
   修改内容   : DTS2014010202583:SVLTE优化G-TL ps切换性能修改

*****************************************************************************/
VOS_VOID NAS_MML_SetPsLocalDetachFlag(VOS_UINT8 ucPsLocalDetachFlag )
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.ucPsLocalDetachFlag = ucPsLocalDetachFlag;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SetPsAttachAllowFlg
 功能描述  : 更新MML中保存的PS域是否允许ATTACH的标志
 输入参数  : ucPsAttachAllowFlg:PS域是否允许ATTACH的标志
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID NAS_MML_SetPsAttachAllowFlg(
    VOS_UINT8                           ucPsAttachAllowFlg
)
{
    (NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.ucPsAttachAllow) = ucPsAttachAllowFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetOperatorNameLong
 功能描述  : 获取保存的运营商的长名称
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 保存的运营商的长名称
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/

VOS_UINT8 *NAS_MML_GetOperatorNameLong(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.stOperatorNameInfo.aucOperatorNameLong);
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetOperatorNameShort
 功能描述  : 获取保存的运营商的短名称
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 保存的运营商的短名称
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/

VOS_UINT8 *NAS_MML_GetOperatorNameShort(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.stOperatorNameInfo.aucOperatorNameShort);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetOperatorNameInfo
 功能描述  : 获取保存的运营商的相关信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 保存的运营商的相关信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月8日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/

NAS_MML_OPERATOR_NAME_INFO_STRU* NAS_MML_GetOperatorNameInfo(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.stOperatorNameInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetPsRestrictRegisterFlg
 功能描述  : 获取PS域禁止注册接入的标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回获取PS域禁止注册接入的标志
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年2月15日
   作    者   : w00166186
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetPsRestrictRegisterFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsAcRestriction.ucRestrictRegister);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetPsRestrictPagingFlg
 功能描述  : 获取PS域禁止寻呼的标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回获取PS域禁止寻呼接入的标志
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年2月15日
   作    者   : w00166186
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetPsRestrictPagingFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsAcRestriction.ucRestrictPagingRsp);
}

/* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
/*****************************************************************************
 函 数 名  : NAS_MML_GetPsRestrictNormalServiceFlg
 功能描述  : 获取PS域禁止正常业务的标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回获取PS域禁止正常业务的标志
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年2月15日
   作    者   : w00166186
   修改内容   : 新生成函数
 2.日    期   : 2012年12月11日
   作    者   : w00176964
   修改内容   : 修改函数名

*****************************************************************************/
VOS_UINT8 NAS_MML_GetPsRestrictNormalServiceFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsAcRestriction.ucRestrictNormalService);
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetPsRestrictEmergencyServiceFlg
 功能描述  : 获取PS域禁止紧急业务的标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回获取PS域禁止紧急业务的标志
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年12月11日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MML_GetPsRestrictEmergencyServiceFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsAcRestriction.ucRestrictEmergencyService);
}

/* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */

/*****************************************************************************
 函 数 名  : NAS_MML_GetCsRestrictRegisterFlg
 功能描述  : 获取Cs域禁止注册接入的标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回获取Cs域禁止注册接入的标志
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年2月15日
   作    者   : w00166186
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetCsRestrictRegisterFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stCsAcRestriction.ucRestrictRegister);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetPsRestrictPagingFlg
 功能描述  : 获取Cs域禁止寻呼的标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回获取Cs域禁止寻呼接入的标志
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年2月15日
   作    者   : w00166186
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetCsRestrictPagingFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stCsAcRestriction.ucRestrictPagingRsp);
}

/* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
/*****************************************************************************
 函 数 名  : NAS_MML_GetCsAcRestrictionInfo
 功能描述  : 获取CS域禁止信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回获取CS域禁止信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年12月11日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
NAS_MML_ACCESS_RESTRICTION_STRU* NAS_MML_GetCsAcRestrictionInfo(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stCsAcRestriction);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetPsAcRestrictionInfo
 功能描述  : 获取PS域禁止信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回获取Ps域禁止信息
 被调函数  :

 修改历史      :
 1.日    期   : 2012年12月11日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
NAS_MML_ACCESS_RESTRICTION_STRU* NAS_MML_GetPsAcRestrictionInfo(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsAcRestriction);
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetCsRestrictNormalServiceFlg
 功能描述  : 获取CS域禁止正常业务的标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回获取Cs域禁止正常业务的标志
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年2月15日
   作    者   : w00166186
   修改内容   : 新生成函数
 2.日    期   : 2012年12月11日
   作    者   : w00176964
   修改内容   : 获取CS限制正常服务标记

*****************************************************************************/
VOS_UINT8 NAS_MML_GetCsRestrictNormalServiceFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stCsAcRestriction.ucRestrictNormalService);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetCsRestrictEmergencyServiceFlg
 功能描述  : 获取CS域禁止紧急业务的标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回获取Cs域禁止紧急业务的标志
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年12月11日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MML_GetCsRestrictEmergencyServiceFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stCsAcRestriction.ucRestrictEmergencyService);
}

/* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */


/*****************************************************************************
 函 数 名  : NAS_MML_SetCsRestrictRegisterFlg
 功能描述  : 设置CS域禁止其他业务的标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回获取Cs域禁止其他业务的标志
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年2月15日
   作    者   : w00166186
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetCsRestrictRegisterFlg(
    VOS_UINT8                           ucCsRestrictionRegisterFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stCsAcRestriction.ucRestrictRegister = ucCsRestrictionRegisterFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetCsRestrictPagingFlg
 功能描述  : 设置CS域禁止寻呼的标志
 输入参数  :
            VOS_UINT8                           ucCsRestrictionPagingFlg

 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年2月15日
   作    者   : w00166186
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetCsRestrictPagingFlg(
    VOS_UINT8                           ucCsRestrictionPagingFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stCsAcRestriction.ucRestrictPagingRsp = ucCsRestrictionPagingFlg;
}

/* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
/*****************************************************************************
 函 数 名  : NAS_MML_SetCsRestrictNormalServiceFlg
 功能描述  : 设置CS域禁止正常业务的标志
 输入参数  :
            VOS_UINT8                           ucCsRestrictiNormalServiceFlg

 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年2月15日
   作    者   : w00166186
   修改内容   : 新生成函数
 2.日    期   : 2012年12月11日
   作    者   : w00176964
   修改内容   : 修改函数名

*****************************************************************************/
VOS_VOID NAS_MML_SetCsRestrictNormalServiceFlg(
    VOS_UINT8                           ucCsRestrictiNormalServiceFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stCsAcRestriction.ucRestrictNormalService = ucCsRestrictiNormalServiceFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetCsRestrictEmergencyServiceFlg
 功能描述  : 设置CS域禁止紧急业务的标志
 输入参数  :
            VOS_UINT8                           ucCsRestrictiNormalServiceFlg

 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年2月15日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_SetCsRestrictEmergencyServiceFlg(
    VOS_UINT8                           ucCsRestrictiEmergencyServiceFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stCsAcRestriction.ucRestrictEmergencyService = ucCsRestrictiEmergencyServiceFlg;
}

/* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */


/*****************************************************************************
 函 数 名  : NAS_MML_SetPsRestrictRegisterFlg
 功能描述  : 设置pS域禁止其他业务的标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年2月15日
   作    者   : w00166186
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetPsRestrictRegisterFlg(
    VOS_UINT8                           ucPsRestrictionRegisterFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsAcRestriction.ucRestrictRegister = ucPsRestrictionRegisterFlg;
}
/*****************************************************************************
 函 数 名  : NAS_MML_SetPsRestrictPagingFlg
 功能描述  : 设置CS域禁止其他业务的标志
 输入参数  :
            VOS_UINT8                           ucCsRestrictionPagingFlg

 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年2月15日
   作    者   : w00166186
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetPsRestrictPagingFlg(
    VOS_UINT8                           ucPsRestrictionPagingFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsAcRestriction.ucRestrictPagingRsp = ucPsRestrictionPagingFlg;
}

/* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
/*****************************************************************************
 函 数 名  : NAS_MML_SetPsRestrictNormalServiceFlg
 功能描述  : 设置PS域禁止正常业务的标志
 输入参数  :
            VOS_UINT8                           ucPsRestrictNormalServiceFlg

 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年2月15日
   作    者   : w00166186
   修改内容   : 新生成函数
 2.日    期   : 2012年12月11日
   作    者   : w00176964
   修改内容   : 修改函数名

*****************************************************************************/
VOS_VOID NAS_MML_SetPsRestrictNormalServiceFlg(
    VOS_UINT8                           ucPsRestrictNormalServiceFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsAcRestriction.ucRestrictNormalService = ucPsRestrictNormalServiceFlg;
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetPsRestrictEmergencyServiceFlg
 功能描述  : 设置PS域禁止紧急业务的标志
 输入参数  :
            VOS_UINT8                           ucPsRestrictiNormalServiceFlg

 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年2月15日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_SetPsRestrictEmergencyServiceFlg(
    VOS_UINT8                           ucPsRestrictiEmergencyServiceFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsAcRestriction.ucRestrictEmergencyService = ucPsRestrictiEmergencyServiceFlg;
}

/* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */

/*****************************************************************************
 函 数 名  : NAS_MML_ClearCsPsRestrictionAll
 功能描述  : 设置CS域禁止其他业务的标志
 输入参数  : 无

 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年2月15日
   作    者   : w00166186
   修改内容   : 新生成函数
 2.日    期   : 2012年12月11日
   作    者   : w00176964
   修改内容   : 更新小区禁止正常业务标记

*****************************************************************************/
VOS_VOID NAS_MML_ClearCsPsRestrictionAll()
{
    /* 清除CS接入受限信息 */
    NAS_MML_SetCsRestrictRegisterFlg(VOS_FALSE);
    NAS_MML_SetCsRestrictPagingFlg(VOS_FALSE);
    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
    NAS_MML_SetCsRestrictNormalServiceFlg(VOS_FALSE);
    NAS_MML_SetCsRestrictEmergencyServiceFlg(VOS_FALSE);
    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */

    /* 清除PS接入受限信息 */
    NAS_MML_SetPsRestrictRegisterFlg(VOS_FALSE);
    NAS_MML_SetPsRestrictPagingFlg(VOS_FALSE);
    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
    NAS_MML_SetPsRestrictNormalServiceFlg(VOS_FALSE);
    NAS_MML_SetPsRestrictEmergencyServiceFlg(VOS_FALSE);
    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetPsRegisterBarToUnBarFlg
 功能描述  : 获取PS域从禁止接入到非禁止接入的标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回PS域从禁止接入到非禁止接入的标志
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年8月8日
   作    者   : l00130025
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_GetPsRegisterBarToUnBarFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.ulPsRegisterBarToUnBarFlag);
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetPsRegisterBarToUnBarFlg
 功能描述  : 设置PS域从禁止接入到非禁止接入的标志
 输入参数  : ulPsUnBarFlg:需更新的PS域从禁止接入到非禁止接入的标志
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年8月8日
   作    者   : l00130025
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetPsRegisterBarToUnBarFlg(
    VOS_UINT32                           ulPsUnBarFlag
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.ulPsRegisterBarToUnBarFlag = ulPsUnBarFlag;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetCsRegisterBarToUnBarFlg
 功能描述  : 获取CS域从禁止接入到非禁止接入的标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回获取CS域从禁止接入到非禁止接入的标志
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年8月8日
   作    者   : l00130025
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_GetCsRegisterBarToUnBarFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.ulCsRegisterBarToUnBarFlag);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetCsRegisterBarToUnBarFlg
 功能描述  : 设置CS域从禁止接入到非禁止接入的标志
 输入参数  : ulCsUnBarFlag:需更新的CS域从禁止接入到非禁止接入的标志
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年8月8日
   作    者   : l00130025
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetCsRegisterBarToUnBarFlg(
    VOS_UINT32                           ulCsUnBarFlag
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.ulCsRegisterBarToUnBarFlag = ulCsUnBarFlag;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetTinType
 功能描述  : 获取TinType
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MML_RPLMN_CFG_INFO_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月28日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_TIN_TYPE_ENUM_UINT8 NAS_MML_GetTinType( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRplmnCfg.enTinType;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetUeNetWorkCapability
 功能描述  : 获取MML保持的UE NetWork Capability
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MML_UE_NETWORK_CAPABILITY_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月28日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_UE_NETWORK_CAPABILITY_STRU* NAS_MML_GetUeNetWorkCapability(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsCapability.stUeNetworkCapbility);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetUeNetWorkCapability
 功能描述  : 设置MML保持的UE NetWork Capability
 输入参数  : pstUeNetworkCapbility - UE NetWork Capability内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月8日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetUeNetWorkCapability(NAS_MML_UE_NETWORK_CAPABILITY_STRU *pstUeNetworkCapbility)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsCapability.stUeNetworkCapbility = *pstUeNetworkCapbility;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetPlatformRatCap
 功能描述  : 获取MML上下文中的平台接入技术能力
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MML_PLATFORM_RAT_CAP_STRU* 平台接入技术能力
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月26日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_PLATFORM_RAT_CAP_STRU* NAS_MML_GetPlatformRatCap(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsCapability.stPlatformRatCap);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetRoamCapability
 功能描述  : 设置MML中保存漫游能力信息
 输入参数  : enRoamCapability -设置的漫游能力信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年8月05日
   作    者   : W00167002
   修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID NAS_MML_SetRoamCapability(
    NAS_MML_ROAM_CAPABILITY_ENUM_UINT8  enRoamCapability
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRoamCfg.enRoamCapability
                                        = enRoamCapability;
}



/*****************************************************************************
 函 数 名  : NAS_MML_SetMsSysCfgBand
 功能描述  : 设置MML中保存SYSCFG的频段信息
 输入参数  : pstMsBand -设置频段信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年8月05日
   作    者   : W00167002
   修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID NAS_MML_SetMsSysCfgBand(
    NAS_MML_MS_BAND_INFO_STRU          *pstMsBand
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.stMsBand = *pstMsBand;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetMsSysCfgPrioRatList
 功能描述  : 设置MML中保存SYSCFG的接入优先级列表信息
 输入参数  : pstPrioRatList -SYSCFG的接入优先级列表信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年8月05日
   作    者   : W00167002
   修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID NAS_MML_SetMsSysCfgPrioRatList(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList
)
{
    VOS_UINT8                           ucRatNum;
    VOS_UINT32                          i;

    ucRatNum        = 0;
    PS_MEM_SET(NAS_MML_GetMsPrioRatList()->aucRatPrio,
               NAS_MSCC_PIF_NET_RAT_TYPE_BUTT,
               sizeof(NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8) * NAS_MSCC_PIF_MAX_RAT_NUM);

    for (i = 0; i < NAS_MML_MIN(NAS_MSCC_PIF_MAX_RAT_NUM,pstPrioRatList->ucRatNum); i++)
    {
        if (VOS_FALSE == NAS_MML_Is3Gpp2Rat(pstPrioRatList->aucRatPrio[i]))
        {
            NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.stPrioRatList.aucRatPrio[ucRatNum]= pstPrioRatList->aucRatPrio[i];
            ucRatNum ++;
        }
    }

    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.stPrioRatList.ucRatNum = ucRatNum;
}



/*****************************************************************************
 函 数 名  : NAS_MML_SaveEquPlmnList
 功能描述  : 保存等效PLMN信息
 输入参数  : VOS_UINT32                          ulPlmnNum
             NAS_MML_PLMN_ID_STRU               *pstNewEquPlmnList
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月28日
   作    者   : l00130025
   修改内容   : 新生成函数

 2.日    期   : 2011年8月14日
   作    者   : w00167002
   修改内容   : V7R1 PHASEII 重构: 取EQUPLMN得个数不对

 3.日    期   : 2012年10月26日
   作    者   : W00176964
   修改内容   : DTS2012090303157:更新EPLMN有效标记

 4.日    期   : 2014年6月12日
   作    者   : W00176964
   修改内容   : DTS2014050806812:删除EPLMN中的FPLMN只在紧急PDN连接存在时
 5.日    期   : 2014年6月17日
   作    者   : z00234330
   修改内容   : PCINT清理
*****************************************************************************/
VOS_VOID NAS_MML_SaveEquPlmnList (
    VOS_UINT32                          ulPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstNewEquPlmnList
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulEquPlmnNum;
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnList;
    NAS_MML_PLMN_ID_STRU               *pstPlmnId;

    /* 先添加当前驻留的plmn信息 */
    pstPlmnId    = NAS_MML_GetCurrCampPlmnId();
    pstEplmnList = NAS_MML_GetEquPlmnList();
    pstEplmnList->astEquPlmnAddr[0].ulMcc = pstPlmnId->ulMcc;
    pstEplmnList->astEquPlmnAddr[0].ulMnc = pstPlmnId->ulMnc;

    /* Modified by z00234330 for PCLINT清理, 2014-06-24, begin */
    /* 超过当前最大Eplmn容量时，使用最大容量,需要去除RPLMN个数 */
    if (ulPlmnNum > (NAS_MML_MAX_EQUPLMN_NUM - 1))
    {
        ulEquPlmnNum = NAS_MML_MAX_EQUPLMN_NUM - 1;
    }
    else
    {
        ulEquPlmnNum = ulPlmnNum;
    }
    /* Modified by z00234330 for PCLINT清理, 2014-06-24, end */

    /* EPLMN信息从第一个位置开始记录 */
    for ( i = 0; i < ulEquPlmnNum; i++ )
    {
        pstEplmnList->astEquPlmnAddr[1 + i].ulMcc = pstNewEquPlmnList[i].ulMcc;
        pstEplmnList->astEquPlmnAddr[1 + i].ulMnc = pstNewEquPlmnList[i].ulMnc;
    }

    ulEquPlmnNum ++;

    /* 1.紧急PDN连接存在时，不删除EPLMN列表中的forbidden plmn列表，待释放时删除：
         if there is no PDN connection for emergency bearer services established, the UE shall remove from
         the list any PLMN code that is already in the list of "forbidden PLMNs" or in the list of "forbidden
         PLMNs for GPRS service". If there is a PDN connection for emergency bearer services established, the
         UE shall remove from the list of equivalent PLMNs any PLMN code present in the list of forbidden PLMNs
         or in the list of "forbidden PLMNs for GPRS service" when the PDN connection for emergency bearer services
         is released.
       2.紧急注册时，不能删除EPLMN列表中的forbidden plmn列表(目前不支持)：
         and if the attach procedure is not for emergency bearer services, the UE shall remove from the list any
         PLMN code that is already in the list of "forbidden PLMNs" or in the list of "forbidden PLMNs for GPRS
         service". */
    if (VOS_FALSE == NAS_MML_GetEmcPdpStatusFlg())
    {
        /*从EPLMN列表中删除无效 、禁止和不允许漫游的网络*/
        ulEquPlmnNum = NAS_MML_DelInvalidPlmnFromList(ulEquPlmnNum, pstEplmnList->astEquPlmnAddr);
        ulEquPlmnNum = NAS_MML_DelForbPlmnInList(ulEquPlmnNum, pstEplmnList->astEquPlmnAddr);
    }

    pstEplmnList->ucEquPlmnNum = (VOS_UINT8)ulEquPlmnNum;

    NAS_MML_SetEplmnValidFlg(VOS_TRUE);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_UpdateGURplmn
 功能描述  : 更新RPLMN ID和接入技术
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年10月8日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_UpdateGURplmn (
    NAS_MML_PLMN_ID_STRU               *pstRPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat
)
{
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;

    /* 用于获取RPLMN的定制需求信息 */
    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

    /* 更新全局变量中的LastRPLMN的接入技术 */
    if (enCurrRat != NAS_MML_GetLastRplmnRat())
    {
        NAS_MML_SetLastRplmnRat(enCurrRat);
    }

    /* 更新全局变量中的RPLMN */
    if (VOS_FALSE == pstRplmnCfgInfo->ucMultiRATRplmnFlg)
    {
        /* 不支持双RPLMN，则W和G的RPLMN都更新 */
        pstRplmnCfgInfo->stGRplmnInNV = *pstRPlmnId;
        pstRplmnCfgInfo->stWRplmnInNV = *pstRPlmnId;

    }
    else
    {
        /* 支持双RPLMN, 则只更新对应接入技术的RPLMN */
        if (NAS_MML_NET_RAT_TYPE_GSM == enCurrRat)
        {
            pstRplmnCfgInfo->stGRplmnInNV = *pstRPlmnId;
        }
        else if (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrRat)
        {
            pstRplmnCfgInfo->stWRplmnInNV = *pstRPlmnId;
        }
        else
        {
            ;
        }
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetSimCsLociFileContent
 功能描述  : 获取MML内存中USIM模块EFLOCI文件的内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML内存中USIM模块EFLOCI文件的内容
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月1日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8* NAS_MML_GetSimCsLociFileContent( VOS_VOID )
{
    NAS_MML_SIM_INFO_STRU               *pstSimInfo;

    pstSimInfo  = NAS_MML_GetSimInfo();

    return pstSimInfo->stSimNativeContent.aucCsLociInfoFile;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetSimPsLociFileContent
 功能描述  : 获取MML内存中USIM模块EFPSLOCI文件的内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML内存中USIM模块EFPSLOCI文件的内容
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月1日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8* NAS_MML_GetSimPsLociFileContent( VOS_VOID )
{
    NAS_MML_SIM_INFO_STRU               *pstSimInfo;

    pstSimInfo  = NAS_MML_GetSimInfo();

    return pstSimInfo->stSimNativeContent.aucPsLociInfoFile;
}

/*****************************************************************************
 函 数 名  : NAS_MML_UpdateSimCsLociFileContent
 功能描述  : 更新MML内存中USIM模块EFLOCI文件的内容
 输入参数  : pucCsLociFileContent:待更新的EFCSLOCI文件的内容
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月1日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_UpdateSimCsLociFileContent(
    VOS_UINT8                          *pucCsLociFileContent
)
{
    NAS_MML_SIM_INFO_STRU               *pstSimInfo;

    pstSimInfo  = NAS_MML_GetSimInfo();

    PS_MEM_CPY(pstSimInfo->stSimNativeContent.aucCsLociInfoFile,
               pucCsLociFileContent,
               NAS_MML_CS_LOCI_SIM_FILE_LEN);
}

/*****************************************************************************
 函 数 名  : NAS_MML_UpdateSimPsLociFileContent
 功能描述  : 更新MML内存中USIM模块EFPSLOCI文件的内容
 输入参数  : pucPsLociFileContent:待更新的EFPSLOCI文件的内容
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月1日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_UpdateSimPsLociFileContent(
    VOS_UINT8                          *pucPsLociFileContent
)
{
    NAS_MML_SIM_INFO_STRU               *pstSimInfo;

    pstSimInfo  = NAS_MML_GetSimInfo();

    PS_MEM_CPY(pstSimInfo->stSimNativeContent.aucPsLociInfoFile,
               pucPsLociFileContent,
               NAS_MML_PS_LOCI_SIM_FILE_LEN);
}




/*****************************************************************************
 函 数 名  : NAS_MML_GetUePcRecurFlg
 功能描述  : 获取当前的UE侧的PC回放标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前的UE侧的PC回放标志
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年04月21日
   作    者   : l00171473
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetUePcRecurFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMaintainInfo.stUeMaintainInfo.ucUeSndPcRecurFlg);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetUePcRecurFlg
 功能描述  : 更新UE的PC回放使能标志
 输入参数  : ucUePcRecurFlg: UE侧的PC回放标志
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年04月21日
   作    者   : l00171473
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetUePcRecurFlg(
    VOS_UINT8                           ucUePcRecurFlg
)
{
    NAS_MML_GetMmlCtx()->stMaintainInfo.stUeMaintainInfo.ucUeSndPcRecurFlg = ucUePcRecurFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetOmConnectFlg
 功能描述  : 获取当前的PC工具的连接状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前的PC工具的连接状态
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年04月21日
   作    者   : l00171473
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetOmConnectFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMaintainInfo.stOmMaintainInfo.ucOmConnectFlg);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetOmConnectFlg
 功能描述  : 更新当前的PC工具的连接状态
 输入参数  : ucOmConnectFlg: PC工具连接状态
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年04月21日
   作    者   : l00171473
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetOmConnectFlg(
    VOS_UINT8                           ucOmConnectFlg
)
{
    NAS_MML_GetMmlCtx()->stMaintainInfo.stOmMaintainInfo.ucOmConnectFlg = ucOmConnectFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetOmPcRecurEnableFlg
 功能描述  : 获取PC工具配置的PC回放使能标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前PC工具配置的PC回放使能标志
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年04月21日
   作    者   : l00171473
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetOmPcRecurEnableFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMaintainInfo.stOmMaintainInfo.ucOmPcRecurEnableFlg);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetOmPcRecurEnableFlg
 功能描述  : 更新PC工具配置的PC回放使能标志
 输入参数  : ucOmPcRecurEnableFlg: SDT连接状态
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年04月21日
   作    者   : l00171473
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetOmPcRecurEnableFlg(
    VOS_UINT8                           ucOmPcRecurEnableFlg
)
{
    NAS_MML_GetMmlCtx()->stMaintainInfo.stOmMaintainInfo.ucOmPcRecurEnableFlg = ucOmPcRecurEnableFlg;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetScanCtrlEnableFlg
 功能描述  : 获取搜索控制标识
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月11日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetScanCtrlEnableFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stBgSearchCfg.ucScanCtrlFlg);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetScanCtrlEnableFlg
 功能描述  : 更新搜索控制标识
 输入参数  : VOS_UINT8 ucScanCtrlEnableFlg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月11日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetScanCtrlEnableFlg(VOS_UINT8 ucScanCtrlEnableFlg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stBgSearchCfg.ucScanCtrlFlg = ucScanCtrlEnableFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetHPlmnType
 功能描述  : 设置当前HPLMN的类型
 输入参数  : enHPlmnType - 设置的HPLMN类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年6月11日
   作    者   : w00166186
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetHPlmnType(
    NAS_MML_HPLMN_TYPE_ENUM_UINT8       enHPlmnType
)
{
    NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.stEhPlmnInfo.enHplmnType = enHPlmnType;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetHPlmnType
 功能描述  : 获取当前HPLMN的类型
 输入参数  :
 输出参数  : 无
 返 回 值  : NAS_MML_HPLMN_TYPE_ENUM_UINT8 当前HPLMN的类型
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年6月11日
   作    者   : w00166186
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_HPLMN_TYPE_ENUM_UINT8 NAS_MML_GetHPlmnType(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.stEhPlmnInfo.enHplmnType);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetSingleDomainRegFailActionSupportFlag
 功能描述  : 获取单域注册被拒定制flag
 输入参数  :
 输出参数  : 无
 返 回 值  : 定制是否打开
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年6月11日
   作    者   : w00166186
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8  NAS_MML_GetSingleDomainRegFailActionSupportFlag(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.stSingleDomainFailActionCtx.ucActiveFlag);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetSingleDomainFailActionCtx
 功能描述  : 获取单域注册被拒定制控制结构
 输入参数  :
 输出参数  : 无
 返 回 值  : 定制控制结构指针
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年6月11日
   作    者   : w00166186
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_SINGLE_DOMAIN_FAIL_ACTION_LIST_CTX_STRU*  NAS_MML_GetSingleDomainFailActionCtx(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.stSingleDomainFailActionCtx);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetSorAdditionalLauCtx
 功能描述  : 获取SOR额外LAU控制结构
 输入参数  :
 输出参数  : 无
 返 回 值  : NAS_MML_SOR_ADDITIONAL_LAU_STRU
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年5月22日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_SOR_ADDITIONAL_LAU_STRU*  NAS_MML_GetSorAdditionalLauCtx(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.stAdditionalLau);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetSorAdditionalLauCtx
 功能描述  : 获取SOR额外LAU控制结构
 输入参数  :
 输出参数  : 无
 返 回 值  : NAS_MML_SOR_ADDITIONAL_LAU_STRU
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年5月22日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_InitSorAdditionalLauCtx(VOS_VOID)
{
    NAS_MML_SOR_ADDITIONAL_LAU_STRU    *pstAdditionalLau    = VOS_NULL_PTR;

    pstAdditionalLau = NAS_MML_GetSorAdditionalLauCtx();

    pstAdditionalLau->ucAdditionalLauFlag       = VOS_FALSE;
    pstAdditionalLau->stLai.stPlmnId.ulMcc      = NAS_MML_INVALID_MCC;
    pstAdditionalLau->stLai.stPlmnId.ulMnc      = NAS_MML_INVALID_MNC;
    pstAdditionalLau->stLai.aucLac[0]           = NAS_MML_LAC_LOW_BYTE_INVALID;
    pstAdditionalLau->stLai.aucLac[1]           = NAS_MML_LAC_HIGH_BYTE_INVALID;
    pstAdditionalLau->stLai.enCampPlmnNetRat    = NAS_MML_NET_RAT_TYPE_BUTT;
    pstAdditionalLau->stLai.ucRac               = NAS_MML_RAC_INVALID;

    PS_MEM_SET(pstAdditionalLau->auReserv, 0X00, sizeof(pstAdditionalLau->auReserv));

    return ;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetSorAdditionalLauFlg
 功能描述  : 获取SOR额外LAU标志
 输入参数  :
 输出参数  : 无
 返 回 值  : NAS_MML_SOR_ADDITIONAL_LAU_STRU
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年5月22日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetSorAdditionalLauFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.stAdditionalLau.ucAdditionalLauFlag);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetBgSearchRegardlessMccList
 功能描述  : 设置BG搜不考虑国家码列表
 输入参数  : pulMcc 允许漫游的国家码列表
             ucMccNum 国家码
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年6月11日
   作    者   : w00166186
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetBgSearchRegardlessMccList(
    VOS_UINT32                         *pulMcc,
    VOS_UINT8                           ucMccNum
)
{
    VOS_UINT32                          i;

    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stBgSearchCfg.stBgSearchRegardlessMcc.ucCustomMccNum = ucMccNum;

    for (i = 0; i < ucMccNum; i++)
    {
        NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stBgSearchCfg.stBgSearchRegardlessMcc.aulCostumMccList[i] = pulMcc[i];
    }
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetBgSearchRegardlessMccCtx
 功能描述  : 获取BG搜不考虑国家码标志
 输入参数  :
 输出参数  : 无
 返 回 值  : BG搜不考虑国家码控制结构
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年6月11日
   作    者   : w00166186
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_HPLMN_SEARCH_REGARDLESS_MCC_CTX_STRU*  NAS_MML_GetBgSearchRegardlessMccCtx(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stBgSearchCfg.stBgSearchRegardlessMcc);
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetRegFailNetWorkFailureCustomFlag
 功能描述  : #17被拒的定制
 输入参数  :
 输出参数  : 无
 返 回 值  : 定制是否打开
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年6月11日
   作    者   : w00166186
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8  NAS_MML_GetRegFailNetWorkFailureCustomFlag(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.ucRegFailNetWorkFailureCustomFlg);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetRegFailNetWorkFailureCustomFlag
 功能描述  : 获取#17被拒定制开关
 输入参数  : ucRegFailNetWorkFailureCustomFlg #17被拒ATT定制开关
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年6月11日
   作    者   : w00166186
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_SetRegFailNetWorkFailureCustomFlag(VOS_UINT8 ucRegFailNetWorkFailureCustomFlg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stMiscellaneousCfg.ucRegFailNetWorkFailureCustomFlg = ucRegFailNetWorkFailureCustomFlg;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetImsiHomePlmn
 功能描述  : 从IMSI中获取HPLMN
 输入参数  :
 输出参数  : 无
 返 回 值  : HOME PLMN
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月11日
    作    者   : w00166186
    修改内容   : AT&T&DCM项目新增

  2.日    期   : 2012年8月17日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:删除将46002，46007转换为46000进行处理
                  对于中移动的卡，配置EHplmn NV项可以解决漫游显示问题。
  3.日    期   : 2012年8月19日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:调整函数，将IMSI作为参数输入，提升函数
                  的复用性。
  4.日    期   : 2012年9月19日
    作    者   : z00161729
    修改内容   : DTS2012091809171:需要判断mnc精确比较nv是否开启
*****************************************************************************/
NAS_MML_PLMN_ID_STRU  NAS_MML_GetImsiHomePlmn(
    VOS_UINT8                          *pucImsi
)
{
    NAS_MML_PLMN_ID_STRU                stHplmn;

    VOS_UINT8                           ucUsimMncLenth;
    VOS_UINT8                           ucExactlyComparaFlag;

    ucUsimMncLenth       = NAS_MML_GetUsimMncLen();
    ucExactlyComparaFlag = NAS_MML_GetPlmnExactlyComparaFlg();

    PS_MEM_SET(&stHplmn, 0, sizeof(NAS_MML_PLMN_ID_STRU));

    stHplmn.ulMcc |= (pucImsi[1] & NAS_MML_OCTET_HIGH_FOUR_BITS) >> NAS_MML_OCTET_MOVE_FOUR_BITS;
    stHplmn.ulMcc |= (pucImsi[2] & NAS_MML_OCTET_LOW_FOUR_BITS) << NAS_MML_OCTET_MOVE_EIGHT_BITS;
    stHplmn.ulMcc |= (pucImsi[2] & NAS_MML_OCTET_HIGH_FOUR_BITS) << NAS_MML_OCTET_MOVE_TWELVE_BITS;
    stHplmn.ulMnc |= (pucImsi[3] & NAS_MML_OCTET_LOW_FOUR_BITS);
    stHplmn.ulMnc |= (pucImsi[3] & NAS_MML_OCTET_HIGH_FOUR_BITS) << NAS_MML_OCTET_MOVE_FOUR_BITS;

    if ((NAS_MML_MNC_LENGTH_TWO_BYTES_IN_IMSI == ucUsimMncLenth)
     && (VOS_TRUE == ucExactlyComparaFlag))
    {
        stHplmn.ulMnc |= (NAS_MML_LOW_BYTE_INVALID) << NAS_MML_OCTET_MOVE_SIXTEEN_BITS;
    }
    else
    {
        stHplmn.ulMnc |= (pucImsi[4] & NAS_MML_OCTET_LOW_FOUR_BITS) << NAS_MML_OCTET_MOVE_SIXTEEN_BITS;
    }

    /* 对于PLMN ID相同的比较，末位为0或者F的情况，已经在新的比较函数中
      处理:NAS_MMC_CompareBcchPlmnwithSimPlmn不需要添加两次PLMN ID，对于
      中移动卡的特殊处理需要保留,添加2位MNC的HPLMN到Hplmn列表中,
      移动MCC=460,MNC=02和07中国移动卡特殊处理
    */
    if (( 0x000604 == stHplmn.ulMcc )
     && ( (0x200   == (stHplmn.ulMnc & 0xFFFF ) )
       || (0x700   == (stHplmn.ulMnc & 0xFFFF))))
    {
        stHplmn.ulMnc &= 0xFF0000;
    }

    return stHplmn;
}



/*****************************************************************************
 函 数 名  : NAS_MML_GetEHplmnPresentInd
 功能描述  : 获取EHPLMN显示的方式
 输入参数  : 无
 输出参数  : EHPLMN显示的方式
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月11日
    作    者   : z40661
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_EHPLMN_PRESENT_IND_ENUM_UINT8  NAS_MML_GetEHplmnPresentInd( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.stEhPlmnInfo.enEHplmnPresentInd;
}


/* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-13, begin */
/*****************************************************************************
 函 数 名  : NAS_MML_SetPsRegContainDrx
 功能描述  : 更新MML中保存的PsRegisterContainDrx
 输入参数  : enPsRegContainDrx :ps注册携带的DRX参数状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月13日
   作    者   : t00212959
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_SetPsRegContainDrx(
    NAS_MML_PS_REG_CONTAIN_DRX_PARA_ENUM_UINT8 enPsRegContainDrx)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsDomainDrxPara.enPsRegisterContainDrx = enPsRegContainDrx;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetPsRegContainDrx
 功能描述  : 获得MML中保存的PsRegisterContainDrx状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ps注册携带的DRX参数状态
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月13日
   作    者   : t00212959
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_PS_REG_CONTAIN_DRX_PARA_ENUM_UINT8 NAS_MML_GetPsRegContainDrx(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsDomainDrxPara.enPsRegisterContainDrx;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetNonDrxTimer
 功能描述  : 更新MML中保存的NonDrxTimer
 输入参数  : ucPsNonDrxTimerLength :non-DRX  timer信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月13日
   作    者   : t00212959
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_SetNonDrxTimer(VOS_UINT8  ucPsNonDrxTimerLength)
{
    /* 取值范围0-7，如果大于7则认为无效，取默认值0 */
    if (NAS_MML_NON_DRX_TIMER_MAX < ucPsNonDrxTimerLength)
    {
        ucPsNonDrxTimerLength = NAS_MML_PS_DEFAULT_NON_DRX_TIMER;
    }

    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsDomainDrxPara.ucNonDrxTimer = ucPsNonDrxTimerLength;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetSplitPgCycleCode
 功能描述  : 设置MML中保存的ucSplitPgCycleCode
 输入参数  : ucSplitPgCycleCode - 需要设置的SplitPgCycleCode
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月20日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetSplitPgCycleCode(
    VOS_UINT8                           ucSplitPgCycleCode
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsDomainDrxPara.ucSplitPgCycleCode = ucSplitPgCycleCode;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetNonDrxTimer
 功能描述  : 获得MML中保存的NonDrxTimer
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前MML中保存的NonDrxTimer值
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月14日
   作    者   : t00212959
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetNonDrxTimer(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsDomainDrxPara.ucNonDrxTimer);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetUeUtranPsDrxLen
 功能描述  : 更新MML中保存的ucUeUtranPsDrxLen
 输入参数  : ucUeUtranPsDrxLen - utran的drx len
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月13日
   作    者   : t00212959
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_SetUeUtranPsDrxLen(VOS_UINT8  ucUeUtranPsDrxLen)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsDomainDrxPara.ucUeUtranPsDrxLen = ucUeUtranPsDrxLen;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetUeUtranPsDrxLen
 功能描述  : 获得MML中保存的ucUeUtranPsDrxLen
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前MML中保存的ucUeUtranPsDrxLen值
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月13日
   作    者   : t00212959
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetUeUtranPsDrxLen(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsDomainDrxPara.ucUeUtranPsDrxLen);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetUeEutranPsDrxLen
 功能描述  : 更新MML中保存的ucUeEutranPsDrxLen
 输入参数  : ucUeEutranPsDrxLen - L drx len
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月13日
   作    者   : t00212959
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_SetUeEutranPsDrxLen(VOS_UINT8  ucUeEutranPsDrxLen)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsDomainDrxPara.ucUeEutranPsDrxLen = ucUeEutranPsDrxLen;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetUeEutranPsDrxLen
 功能描述  : 获得MML中保存的ucUeEutranPsDrxLen
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前MML中保存的ucUeEutranPsDrxLen值
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月13日
   作    者   : t00212959
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetUeEutranPsDrxLen(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsDomainDrxPara.ucUeEutranPsDrxLen);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetWSysInfoDrxLen
 功能描述  : 更新MML中保存的ucWSysInfoDrxLen
 输入参数  : ucWSysInfoDrxLen - W系统消息中drx len
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月13日
   作    者   : t00212959
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_SetWSysInfoDrxLen(VOS_UINT8  ucWSysInfoDrxLength)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsDomainDrxPara.ucWSysInfoDrxLen = ucWSysInfoDrxLength;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetWSysInfoDrxLen
 功能描述  : 获得MML中保存的ucWSysInfoDrxLen
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前MML中保存的WSysInfoDrxLen值
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月13日
   作    者   : t00212959
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetWSysInfoDrxLen(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsDomainDrxPara.ucWSysInfoDrxLen);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetLSysInfoDrxLen
 功能描述  : 更新MML中保存的ucLSysInfoDrxLen
 输入参数  : ucLSysInfoDrxLen - L系统消息中drx len
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月13日
   作    者   : t00212959
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_SetLSysInfoDrxLen(VOS_UINT8  ucLSysInfoDrxLength)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsDomainDrxPara.ucLSysInfoDrxLen = ucLSysInfoDrxLength;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetLSysInfoDrxLen
 功能描述  : 获得MML中保存的ucLSysInfoDrxLen
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前MML中保存的LSysInfoDrxLen值
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月13日
   作    者   : t00212959
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetLSysInfoDrxLen(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsDomainDrxPara.ucLSysInfoDrxLen);
}
/*****************************************************************************
 函 数 名  : NAS_MML_GetSplitPgCycleCode
 功能描述  : 获得MML中保存的ucSplitPgCycleCode
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前MML中保存的SplitPgCycleCode值
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月13日
   作    者   : t00212959
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetSplitPgCycleCode(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsDomainDrxPara.ucSplitPgCycleCode);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetSplitOnCcch
 功能描述  : 获得MML中保存的ucSplitOnCcch
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前MML中保存的SplitOnCcch值
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月13日
   作    者   : t00212959
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetSplitOnCcch(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsDomainDrxPara.ucSplitOnCcch);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetSplitOnCcch
 功能描述  : 设置MML中的ucSplitOnCcch
 输入参数  : ucSplitOnCcch - 需要设置的ucSplitOnCcch
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月13日
   作    者   : t00212959
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetSplitOnCcch(VOS_UINT8 ucSplitOnCcch)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.stPsDomainDrxPara.ucSplitOnCcch = ucSplitOnCcch;
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetPlmnExactlyComparaFlg
 功能描述  : 更新MML中保存的Mnc精确比较标记ExactlyCompareFlg
 输入参数  : ucPlmnExactlyComparaFlag :Mnc精确比较标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月13日
   作    者   : t00212959
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_SetPlmnExactlyComparaFlg(VOS_UINT8  ucPlmnExactlyComparaFlag)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucPlmnExactlyCompareFlg = ucPlmnExactlyComparaFlag;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetHplmnRegisterCtrlFlg
 功能描述  : 更新MML中保存的HPLMN的注册控制标记
 输入参数  : ucHplmnRegisterFlg :HPLMN注册标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年11月29日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_SetHplmnRegisterCtrlFlg(VOS_UINT8  ucHplmnRegisterFlg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucHplmnRegisterCtrlFlg = ucHplmnRegisterFlg;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetHplmnRegisterCtrlFlg
 功能描述  : 获取MML中保存的HPLMN的注册控制标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS-TRUE:允许HPLMN反复注册
             VOS_FALSE:不允许HPLMN反复注册
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年11月29日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetHplmnRegisterCtrlFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucHplmnRegisterCtrlFlg);
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetH3gCtrlFlg
 功能描述  : 更新MML中保存的H3G控制标记
 输入参数  : ucH3gFlg :H3g标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年4月10日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_SetH3gCtrlFlg(VOS_UINT8  ucH3gFlg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucH3gCtrlFlg = ucH3gFlg;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetH3gCtrlFlg
 功能描述  : 获取MML中保存的H3g控制标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS-TRUE:允许H3g控制
             VOS_FALSE:不允许H3g控制
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年4月10日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetH3gCtrlFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucH3gCtrlFlg);
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetPlmnExactlyComparaFlg
 功能描述  : 获取MML中保存的Mnc精确比较标记ExactlyCompareFlg
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS-TRUE:进行三位比较
             VOS_FALSE:进行两位比较
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月13日
   作    者   : t00212959
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetPlmnExactlyComparaFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucPlmnExactlyCompareFlg);
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetUsimMncLen
 功能描述  : 更新从Usim卡中读取的Mnc长度到MML中
 输入参数  : ucUsimMncLength :Mnc长度
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月13日
   作    者   : t00212959
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_SetUsimMncLen(VOS_UINT8  ucUsimMncLength)
{
    NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.ucUsimMncLen = ucUsimMncLength;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetUsimMncLen
 功能描述  : 获取MML中保存的从Usim卡中读取的Mnc长度
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 3:mnc长度为3
             2:mnc长度为2
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月13日
   作    者   : t00212959
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetUsimMncLen(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stSimInfo.stSimPlmnInfo.ucUsimMncLen);
}
/* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-13, end */

/*****************************************************************************
 函 数 名  : NAS_MML_SetSupportCsServiceFLg
 功能描述  : 更新是否支持cs语音业务标识
 输入参数  : ucCsServiceFlg - cs语音业务是否支持，VOS_TRUE:支持语音业务；VOS_FALSE:不支持语音业务
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年10月8日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_SetSupportCsServiceFLg(VOS_UINT8  ucCsServiceFlg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucSupportCsServiceFlg = ucCsServiceFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetSupportCsServiceFLg
 功能描述  : 获取是否支持cs语音业务标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 支持语音业务；
             VOS_FALSE - 不支持语音业务
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年10月8日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8  NAS_MML_GetSupportCsServiceFLg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucSupportCsServiceFlg;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetUserCfgEhplmnInfo
 功能描述  : 获取用户配置的EHplmn内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 用户配置的EHplmn内容
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月9日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2014年12月20日
   作    者   : wx270776
   修改内容   : 修改扩充的返回值
*****************************************************************************/
NAS_MML_USER_CFG_EXT_EHPLMN_INFO_STRU* NAS_MML_GetUserCfgExtEhplmnInfo( VOS_VOID )
{
    NAS_MML_HPLMN_CFG_INFO_STRU         *pstHplmnCfg;

    pstHplmnCfg = NAS_MML_GetHplmnCfg();


    return &(pstHplmnCfg->stUserCfgExtEhplmnInfo);
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetEplmnValidFlg
 功能描述  : 设置MML中保存EPLMN是否有效标记
 输入参数  : ucEplmnValidFlg -设置EPLMN有效标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年10月26日
   作    者   : W00167002
   修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID NAS_MML_SetEplmnValidFlg(
    VOS_UINT8                           ucEplmnValidFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stEquPlmnInfo.ucValidFlg = ucEplmnValidFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetEplmnValidFlg
 功能描述  : 获取EPLMN是否有效标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - EPLMN有效
             VOS_FALSE - EPLMN无效
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年10月26日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetEplmnValidFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stEquPlmnInfo.ucValidFlg);
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetIsrSupportFlg
 功能描述  : 获取ISR是否激活的标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - ISR激活
             VOS_FALSE - ISR未激活
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年5月23日
   作    者   : z00234330
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetIsrSupportFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucIsrSupportFlg);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetIsrSupportFlg
 功能描述  : 设置ISR是否激活的标志
 输入参数  : VOS_TRUE  - ISR激活
             VOS_FALSE - ISR未激活
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年5月23日
   作    者   : z00234330
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetIsrSupportFlg(
    VOS_UINT8                           ucIsrSupport
)
{
    (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucIsrSupportFlg) = ucIsrSupport;
}




/*****************************************************************************
 函 数 名  : NAS_MML_GetErrLogRingBufAddr
 功能描述  : 获取MM层RING BUFFER的地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : MM层RING BUFFER的地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年08月23日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
OM_RING_ID NAS_MML_GetErrLogRingBufAddr(VOS_VOID)
{
    return g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stBuffInfo.pstRingBuffer;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetErrLogRingBufAddr
 功能描述  : 设置MM层RING BUFFER的地址
 输入参数  : RING BUFFER的地址
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年08月23日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_SetErrLogRingBufAddr(OM_RING_ID pRingBuffer)
{
    g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stBuffInfo.pstRingBuffer = pRingBuffer;

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetErrlogCtrlFlag
 功能描述  : 获取ERRLOG打开和关闭的标识
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : ERRLOG打开和关闭的标识
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年08月23日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MML_GetErrlogCtrlFlag(VOS_VOID)
{
    return g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stCtrlInfo.ucErrLogCtrlFlag;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetErrlogCtrlFlag
 功能描述  : 设置ERRLOG打开和关闭的标识
 输入参数  : ucFlag
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年08月23日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_SetErrlogCtrlFlag(VOS_UINT8 ucFlag)
{
    g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stCtrlInfo.ucErrLogCtrlFlag = ucFlag;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetErrlogAlmLevel
 功能描述  : 获取ERRLOG打开和关闭的标识
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : ERRLOG打开和关闭的标识
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年08月23日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT16 NAS_MML_GetErrlogAlmLevel(VOS_VOID)
{
    return g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stCtrlInfo.usAlmLevel;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetErrlogAlmLevel
 功能描述  : 设置ERRLOG打开和关闭的标识
 输入参数  : usAlmLevel
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年08月23日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_SetErrlogAlmLevel(VOS_UINT16 usAlmLevel)
{
    g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stCtrlInfo.usAlmLevel = usAlmLevel;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetErrlogOverflowCnt
 功能描述  : 获取Ringbuf溢出的次数
 输入参数  : VOS_UINT32
 输出参数  : 无
 返 回 值  : Ringbuf溢出的次数
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年09月19日
   作    者   : n00269697
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_GetErrlogOverflowCnt(VOS_VOID)
{
    return g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stBuffInfo.ulOverflowCnt;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetErrlogOverflowCnt
 功能描述  : 设置Ringbuf溢出的次数
 输入参数  : Ringbuf溢出的次数
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年09月19日
   作    者   : n00269697
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_SetErrlogOverflowCnt(VOS_UINT32 ulOverflowCnt)
{
    g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stBuffInfo.ulOverflowCnt = ulOverflowCnt;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetCsfbMtInfoAddr
 功能描述  : 获取CSFB MT的信息地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CSFB MT状态
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年07月15日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
NAS_MML_ERRLOG_CSFB_MT_INFO_STRU* NAS_MML_GetCsfbMtInfoAddr(VOS_VOID)
{
    return &g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stCsfbMtInfo;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetCsfbMtCurrState
 功能描述  : 设置CSFB MT的当前过程状态变量
 输入参数  : CSFB MT状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年09月19日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_SetCsfbMtCurrState(
    NAS_ERR_LOG_CSFB_MT_STATE_ENUM_U32  enCsfbMtState
)
{
    NAS_MML_GetCsfbMtInfoAddr()->enCurrState = enCsfbMtState;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetCsfbMtCurrState
 功能描述  : 获取CSFB MT的当前状态
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CSFB MT状态
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年09月19日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
NAS_ERR_LOG_CSFB_MT_STATE_ENUM_U32 NAS_MML_GetCsfbMtCurrState(VOS_VOID)
{
    return g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stCsfbMtInfo.enCurrState;
}

/*****************************************************************************
 函 数 名  : NAS_MML_AddCsfbMtRecordPositionNum
 功能描述  : 增加CSFB MT记录的位置区个数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年07月17日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_AddCsfbMtRecordPositionNum(VOS_VOID)
{
    g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stCsfbMtInfo.ulPositionNum++;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetCsfbMtRecordPositionNum
 功能描述  : 获取CSFB MT记录的位置区个数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年07月17日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_GetCsfbMtRecordPositionNum(VOS_VOID)
{
    return g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stCsfbMtInfo.ulPositionNum;
}

/*****************************************************************************
 函 数 名  : NAS_MML_ClrCsfbMtRecordPositionNum
 功能描述  : 清空CSFB MT记录的位置区个数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年07月17日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_ClrCsfbMtRecordPositionNum(VOS_VOID)
{
    g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stCsfbMtInfo.ulPositionNum = 0;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_AddCsfbMtRecordStateNum
 功能描述  : 增加CSFB MT记录的状态个数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年07月17日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_AddCsfbMtRecordStateNum(VOS_VOID)
{
    g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stCsfbMtInfo.ulStateNum++;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetCsfbMtRecordStateNum
 功能描述  : 获取CSFB MT记录的状态个数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年07月17日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_GetCsfbMtRecordStateNum(VOS_VOID)
{
    return g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stCsfbMtInfo.ulStateNum;
}

/*****************************************************************************
 函 数 名  : NAS_MML_ClrCsfbMtRecordStateNum
 功能描述  : 清空CSFB MT记录的状态个数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年07月17日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_ClrCsfbMtRecordStateNum(VOS_VOID)
{
    g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stCsfbMtInfo.ulStateNum = 0;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_InitCsfbMtInfo
 功能描述  : 初始化CSFB MT的过程的信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年07月15日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_InitCsfbMtInfo(VOS_VOID)
{
    NAS_MML_ERRLOG_CSFB_MT_INFO_STRU       *pstCsfbMtInfo   = VOS_NULL_PTR;
    NAS_MNTN_POSITION_INFO_STRU            *pstPositionInfo = VOS_NULL_PTR;
    NAS_ERR_LOG_CSFB_MT_STATE_INFO_STRU    *pstStateInfo    = VOS_NULL_PTR;
    VOS_UINT32                              i;

    pstCsfbMtInfo = NAS_MML_GetCsfbMtInfoAddr();

    NAS_MML_SetCsfbMtCurrState(NAS_ERR_LOG_CSFB_MT_STATE_NULL);

    for (i = 0; i < NAS_ERR_LOG_MAX_POSITION_RECORD_NUM; i++)
    {
        pstPositionInfo = &(pstCsfbMtInfo->astPositionInfo[i]);

        PS_MEM_SET(pstPositionInfo,
                   0x0,
                   sizeof(NAS_MNTN_POSITION_INFO_STRU));
    }

    NAS_MML_ClrCsfbMtRecordPositionNum();

    for (i = 0; i < NAS_ERR_LOG_MAX_CSFB_MT_STATE_RECORD_NUM; i++)
    {
        pstStateInfo = &(pstCsfbMtInfo->astStateInfo[i]);
        pstStateInfo->enCsfbMtState  = NAS_ERR_LOG_CSFB_MT_STATE_NULL;
        pstStateInfo->ulMmState      = 0;
        pstStateInfo->ulCause        = 0;
        pstStateInfo->ulTick         = 0;
    }

    NAS_MML_ClrCsfbMtRecordStateNum();

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetErrLogNwSearchInfoAddr
 功能描述  : 获取搜网CHR信息地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MML_ERRLOG_NW_SEARCH_INFO_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年08月13日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
NAS_MML_ERRLOG_NW_SEARCH_INFO_STRU* NAS_MML_GetErrLogNwSearchInfoAddr(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMaintainInfo.stErrLogMntnInfo.stNwSrchInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetErrLogNwSrchCfgActiveFlag
 功能描述  : 获取ERRLOG搜网配置激活标识
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : ERRLOG搜网配置激活标识
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年08月13日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MML_GetErrLogNwSrchCfgActiveFlag(VOS_VOID)
{
    return NAS_MML_GetErrLogNwSearchInfoAddr()->ucCfgActiveFlag;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetErrLogNwSrchCfgActiveFlag
 功能描述  : 设置ERRLOG搜网配置激活标识
 输入参数  : ucFlag
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年08月23日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_SetErrLogNwSrchCfgActiveFlag(VOS_UINT8 ucFlag)
{
    NAS_MML_GetErrLogNwSearchInfoAddr()->ucCfgActiveFlag = ucFlag;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetErrLogNwSrchCfgRecordNum
 功能描述  : 获取ERRLOG搜网配置记录次数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : ERRLOG搜网配置记录次数
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年08月13日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_GetErrLogNwSrchCfgRecordNum(VOS_VOID)
{
    return NAS_MML_GetErrLogNwSearchInfoAddr()->ulCfgRecordNum;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetErrLogNvNwSrchRecordNum
 功能描述  : 设置NV中ERRLOG搜网记录次数
 输入参数  : ulNum
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年08月13日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_SetErrLogNwSrchCfgRecordNum(VOS_UINT32 ulNum)
{
    NAS_MML_GetErrLogNwSearchInfoAddr()->ulCfgRecordNum = ulNum;
}

/*****************************************************************************
 函 数 名  : NAS_MML_AddErrLogNwSearchCount
 功能描述  : 增加搜网记录次数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年08月13日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_AddErrLogNwSearchCount(VOS_VOID)
{
    NAS_MML_GetErrLogNwSearchInfoAddr()->ulSearchCount++;
}

/*****************************************************************************
 函 数 名  : NAS_MML_ClrErrLogNwSearchCount
 功能描述  : 清除搜网记录次数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年08月13日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_ClrErrLogNwSearchCount(VOS_VOID)
{
    NAS_MML_GetErrLogNwSearchInfoAddr()->ulSearchCount = 0;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetErrLogOosEvent
 功能描述  : 获取ERRLOG CS域无服务的事件
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : ERRLOG CS域无服务的原因值
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年08月13日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_GetErrLogOosEvent(VOS_VOID)
{
    return NAS_MML_GetErrLogNwSearchInfoAddr()->enOosEvent;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetErrLogOosEvent
 功能描述  : 设置ERRLOG CS域无服务的事件
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
VOS_VOID NAS_MML_SetErrLogOosEvent(
    NAS_ERR_LOG_OOS_EVENT_ENUM_UINT32   enOosEvent
)
{
    NAS_MML_GetErrLogNwSearchInfoAddr()->enOosEvent = enOosEvent;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetErrLogCsOosCause
 功能描述  : 获取ERRLOG CS域无服务的原因值
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : ERRLOG CS域无服务的原因值
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年08月13日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_GetErrLogCsOosCause(VOS_VOID)
{
    return NAS_MML_GetErrLogNwSearchInfoAddr()->enCsOosCause;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetErrLogCsOosCause
 功能描述  : 设置ERRLOG CS域无服务的原因值
 输入参数  : enOosCause
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年08月13日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_SetErrLogCsOosCause(
    NAS_ERR_LOG_OOS_CAUSE_ENUM_UINT32   enOosCause
)
{
    NAS_MML_GetErrLogNwSearchInfoAddr()->enCsOosCause = enOosCause;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetErrLogPsOosCause
 功能描述  : 获取ERRLOG PS域无服务的原因值
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : ERRLOG PS域无服务的原因值
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年08月13日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_GetErrLogPsOosCause(VOS_VOID)
{
    return NAS_MML_GetErrLogNwSearchInfoAddr()->enPsOosCause;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetErrLogPsOosCause
 功能描述  : 设置ERRLOG PS域无服务的原因值
 输入参数  : enOosCause
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年08月13日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_SetErrLogPsOosCause(
    NAS_ERR_LOG_OOS_CAUSE_ENUM_UINT32   enOosCause
)
{
    NAS_MML_GetErrLogNwSearchInfoAddr()->enPsOosCause = enOosCause;
}

/*****************************************************************************
 函 数 名  : NAS_MML_InitErrLogNwSearchInfo
 功能描述  : 初始化搜网CHR信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年08月13日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_InitErrLogNwSearchInfo(VOS_VOID)
{
    NAS_MML_ERRLOG_NW_SEARCH_INFO_STRU *pstNwSrchInfo = VOS_NULL_PTR;

    pstNwSrchInfo = NAS_MML_GetErrLogNwSearchInfoAddr();

    PS_MEM_SET(pstNwSrchInfo, 0x0, sizeof(NAS_MML_ERRLOG_NW_SEARCH_INFO_STRU));

    pstNwSrchInfo->enCsOosCause   = NAS_ERR_LOG_OOS_CAUSE_NULL;
    pstNwSrchInfo->enPsOosCause   = NAS_ERR_LOG_OOS_CAUSE_NULL;
    pstNwSrchInfo->enSrchRat      = NAS_ERR_LOG_RATMODE_BUTT;
    pstNwSrchInfo->ulSearchType   = 0xFF;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetErrLogGMsIdType
 功能描述  : 设置CS Paging ucGMsIdType变量
 输入参数  : VOS_UINT8                      ucGMsIdType
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年03月13日
   作    者   : zwx247453
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_SetErrLogGMsIdType(
    VOS_UINT8                               ucGMsIdType
)
{
    g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stPagingInfo.ucGMsIdType = ucGMsIdType;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetErrLogGMsIdType
 功能描述  : 获取CS Paging ucGMsIdType变量
 输入参数  :
 输出参数  : 无
 返 回 值  : CS Paging ucGMsIdType
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年03月13日
   作    者   : zwx247453
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MML_GetErrLogGMsIdType(VOS_VOID)
{
    return g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stPagingInfo.ucGMsIdType;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetErrLogGPagingType
 功能描述  : 设置CS Paging ucGPagingType变量
 输入参数  : VOS_UINT8                      ucGPagingType
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年03月13日
   作    者   : zwx247453
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_SetErrLogGPagingType(
    VOS_UINT8                               ucGPagingType
)
{
    g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stPagingInfo.ucGPagingType = ucGPagingType;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetErrLogGPagingType
 功能描述  : 获取CS Paging GMsIdType变量
 输入参数  :
 输出参数  : 无
 返 回 值  : CS Paging ucGPagingType
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年03月13日
   作    者   : zwx247453
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MML_GetErrLogGPagingType(VOS_VOID)
{
    return g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stPagingInfo.ucGPagingType;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetErrLogWCnDomainId
 功能描述  : 设置CS Paging ulWCnDomainId变量
 输入参数  : VOS_UINT32                     ulWCnDomainId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年03月13日
   作    者   : zwx247453
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_SetErrLogWCnDomainId(
    VOS_UINT32                              ulWCnDomainId
)
{
    g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stPagingInfo.ulWCnDomainId = ulWCnDomainId;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetErrLogWCnDomainId
 功能描述  : 获取CS Paging ulWCnDomainId变量
 输入参数  :
 输出参数  : 无
 返 回 值  : CS Paging ulWCnDomainId
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年03月13日
   作    者   : zwx247453
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_GetErrLogWCnDomainId(VOS_VOID)
{
    return g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stPagingInfo.ulWCnDomainId;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetErrLogWPagingType
 功能描述  : 设置CS Paging ulWPagingType变量
 输入参数  : VOS_UINT32                     ulWPagingType
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年03月13日
   作    者   : zwx247453
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_SetErrLogWPagingType(
    VOS_UINT32                              ulWPagingType
)
{
    g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stPagingInfo.ulWPagingType = ulWPagingType;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetErrLogWPagingType
 功能描述  : 获取CS Paging ulWPagingType变量
 输入参数  :
 输出参数  : 无
 返 回 值  : CS Paging ulWPagingType
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年03月13日
   作    者   : zwx247453
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_GetErrLogWPagingType(VOS_VOID)
{
    return g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stPagingInfo.ulWPagingType;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetErrLogWPagingCause
 功能描述  : 设置CS Paging ulWPagingCause变量
 输入参数  : VOS_UINT32                     ulWPagingCause
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年03月13日
   作    者   : zwx247453
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_SetErrLogWPagingCause(
    VOS_UINT32                              ulWPagingCause
)
{
    g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stPagingInfo.ulWPagingCause = ulWPagingCause;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetErrLogWPagingCause
 功能描述  : 获取CS Paging ulWPagingCause变量
 输入参数  :
 输出参数  : 无
 返 回 值  : CS Paging ulWPagingCause
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年03月13日
   作    者   : zwx247453
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_GetErrLogWPagingCause(VOS_VOID)
{
    return g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stPagingInfo.ulWPagingCause;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetErrLogWPagingUeId
 功能描述  : 设置CS Paging ulWPagingUeId变量
 输入参数  : VOS_UINT32                     ulWPagingUeId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年03月13日
   作    者   : zwx247453
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_SetErrLogWPagingUeId(
    VOS_UINT32                              ulWPagingUeId
)
{
    g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stPagingInfo.ulWPagingUeId = ulWPagingUeId;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetErrLogWPagingUeId
 功能描述  : 获取CS Paging ulWPagingUeId变量
 输入参数  :
 输出参数  : 无
 返 回 值  : CS Paging ulWPagingUeId
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年03月13日
   作    者   : zwx247453
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_GetErrLogWPagingUeId(VOS_VOID)
{
    return g_stNasMmlCtx.stMaintainInfo.stErrLogMntnInfo.stPagingInfo.ulWPagingUeId;
}

/*****************************************************************************
 函 数 名  : NAS_MML_InitErrLogPagingInfo
 功能描述  : 初始化Err log记录的paging info
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年03月13日
   作    者   : n00269697
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_InitErrLogPagingInfo(VOS_VOID)
{
    NAS_MML_SetErrLogGMsIdType(GAS_MS_ID_TYPE_BUTT);
    NAS_MML_SetErrLogGPagingType(GAS_PAGING_TYPE_BUTT);
    NAS_MML_SetErrLogWCnDomainId(RRC_NAS_CN_DOMAIN_TYPE_BUTT);
    NAS_MML_SetErrLogWPagingType(RRC_PAGE_CAUSE_BUTT);
    NAS_MML_SetErrLogWPagingCause(RRC_NAS_PAGING_TYPE_BUTT);
    NAS_MML_SetErrLogWPagingUeId(RRC_PAGE_UE_ID_BUTT);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetFtmCtrlFlag
 功能描述  : 获取工程菜单打开和关闭的标识
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 工程菜单打开和关闭的标识
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年08月23日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MML_GetFtmCtrlFlag(VOS_VOID)
{
    return g_stNasMmlCtx.stMaintainInfo.stFtmMntnInfo.ucFtmCtrlFlag;
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetFtmCtrlFlag
 功能描述  : 设置工程菜单打开和关闭的标识
 输入参数  : ucFlag
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年08月23日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_SetFtmCtrlFlag(VOS_UINT8 ucFlag)
{
    g_stNasMmlCtx.stMaintainInfo.stFtmMntnInfo.ucFtmCtrlFlag = ucFlag;

    return;
}

/*lint -e593 -e830*/

/*****************************************************************************
 函 数 名  : NAS_MML_InitErrLogMntnInfo
 功能描述  : 创建RING BUFFER
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月23日
    作    者   : f00179208
    修改内容   : 商用ErrLog上报及工程模式扩展目新增函数
  2.日    期   :2015年3月13日
    作    者   :n00269697
    修改内容   :CHR 优化项目
*****************************************************************************/
VOS_VOID NAS_MML_InitErrLogMntnInfo(
    NAS_MML_ERRLOG_MNTN_INFO_STRU          *pstErrLogInfo
)
{
#if (FEATURE_ON == FEATURE_PTM)
    VOS_CHAR                               *pbuffer;
    OM_RING_ID                              pRingbuffer;
#endif

    pstErrLogInfo->stCtrlInfo.ucErrLogCtrlFlag         = VOS_FALSE;
    pstErrLogInfo->stCtrlInfo.usAlmLevel               = NAS_ERR_LOG_CTRL_LEVEL_CRITICAL;

#if (FEATURE_ON == FEATURE_PTM)
    /* 申请cache的动态内存 , 长度加1是因为读和写指针之间在写满时会相差一个字节 */
    pbuffer = (char *)PS_MEM_ALLOC(WUEPS_PID_MMC ,NAS_MML_RING_BUFFER_SIZE + 1);
    if (VOS_NULL_PTR == pbuffer)
    {
        pstErrLogInfo->stBuffInfo.pstRingBuffer = VOS_NULL_PTR;
        return;
    }

    /* 调用OM的接口，将申请的动态内存创建为RING BUFFER */
    pRingbuffer = OM_RingBufferCreateEx(pbuffer, NAS_MML_RING_BUFFER_SIZE + 1);
    if (VOS_NULL_PTR == pRingbuffer)
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pbuffer);
    }

    /* 保存ringbuffer指针 */
    pstErrLogInfo->stBuffInfo.pstRingBuffer = pRingbuffer;

    pstErrLogInfo->stBuffInfo.ulOverflowCnt = 0;
#endif

    NAS_MML_InitErrLogPagingInfo();

    NAS_MML_InitCsfbMtInfo();

    NAS_MML_InitErrLogNwSearchInfo();

    NAS_MML_InitErrLogFftSrchInfo();
    return;

}
/*lint +e593 +e830*/

#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 函 数 名  : NAS_MML_PutErrLogRingBuf
 功能描述  : RING BUFFER写操作
 输入参数  : pbuffer:需要写入的内容
             lbytes :写入内容的长度
 输出参数  : 无
 返 回 值  : 实际写入的大小，如果BUFFER空间不够则返回0
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月23日
    作    者   : f00179208
    修改内容   : 商用ErrLog上报及工程模式扩展目新增函数
*****************************************************************************/
VOS_UINT32 NAS_MML_PutErrLogRingBuf(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
)
{
    VOS_UINT32                          ulFreeSize;
    VOS_UINT32                          ulCount;
    OM_RING_ID                          pTafRingBuffer;

    pTafRingBuffer = NAS_MML_GetErrLogRingBufAddr();
    if (VOS_NULL_PTR == pTafRingBuffer)
    {
        return 0;
    }

    /* 如果写入比RING BUFFER还大则不写入 */
    if (ulbytes > NAS_MML_RING_BUFFER_SIZE)
    {
        return 0;
    }

    /* 获取RING BUFFER剩余空间大小 */
    ulFreeSize = (VOS_UINT32)OM_RingBufferFreeBytes(pTafRingBuffer);

    ulCount = NAS_MML_GetErrlogOverflowCnt();
    /* 如果剩余空间不足写入的大小，则清空RING BUFFER */
    if (ulFreeSize < ulbytes)
    {
        ulCount++;
        NAS_MML_SetErrlogOverflowCnt(ulCount);

        OM_RingBufferFlush(pTafRingBuffer);
    }

    /* 写入RING BUFFER */
    return (VOS_UINT32)OM_RingBufferPut(pTafRingBuffer, pbuffer, (VOS_INT)ulbytes);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetErrLogRingBufContent
 功能描述  : RING BUFFER读操作操作
 输入参数  : pbuffer: 读出来存放的空间
             lbytes : 读取的最大值
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  : 实际读取的大小，如果RINGBUFFER为空，则返回0
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月23日
    作    者   : f00179208
    修改内容   : 商用ErrLog上报及工程模式扩展目新增函数
*****************************************************************************/
VOS_UINT32 NAS_MML_GetErrLogRingBufContent(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
)
{
    /* 增加异常保护 */
    if (VOS_NULL_PTR == NAS_MML_GetErrLogRingBufAddr())
    {
        return 0;
    }

    return (VOS_UINT32)OM_RingBufferGet(NAS_MML_GetErrLogRingBufAddr(), pbuffer, (VOS_INT)ulbytes);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetErrLogRingBufUseBytes
 功能描述  : RING BUFFER中有多少数据
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 实际RING BUFFER中数据大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月23日
    作    者   : f00179208
    修改内容   : 商用ErrLog上报及工程模式扩展目新增函数
*****************************************************************************/
VOS_UINT32 NAS_MML_GetErrLogRingBufUseBytes(VOS_VOID)
{
    /* 增加异常保护 */
    if (VOS_NULL_PTR == NAS_MML_GetErrLogRingBufAddr())
    {
        return 0;
    }

    return (VOS_UINT32)OM_RingBufferNBytes(NAS_MML_GetErrLogRingBufAddr());
}

/*****************************************************************************
 函 数 名  : NAS_MML_CleanErrLogRingBuf
 功能描述  : 清空RINGBUFFER中的数据
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月23日
    作    者   : f00179208
    修改内容   : 商用ErrLog上报及工程模式扩展目新增函数
*****************************************************************************/
VOS_VOID NAS_MML_CleanErrLogRingBuf(VOS_VOID)
{
    /* 增加异常保护 */
    if (VOS_NULL_PTR == NAS_MML_GetErrLogRingBufAddr())
    {
        return;
    }

    OM_RingBufferFlush(NAS_MML_GetErrLogRingBufAddr());

    return;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_MML_RegFailCauseNeedRecord
 功能描述  : 判断CS或PS注册拒绝原因是否需要记录到Error log
 输入参数  : NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 enRegFailCause
 输出参数  : 无
 返 回 值  : VOS_TRUE   -- 需要记录异常信息
             VOS_FALSE  -- 不需要记录
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月29日
    作    者   : s00190137
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_RegFailCauseNeedRecord(NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 enRegFailCause)
{
    /*以下原因值不需要记录，其余原因需要记录 */
    if ((enRegFailCause == NAS_MML_REG_FAIL_CAUSE_NULL)
     || (enRegFailCause == NAS_MML_REG_FAIL_CAUSE_LOCAL_NULL))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetDelayedCsfbLauFlg
 功能描述  : 获取ucDelayedCsfbLauFlg
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回csfb下，lau是否需要delay的标记
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月25日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetDelayedCsfbLauFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.ucDelayedCsfbLauFlg);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetDelayedCsfbLauFlg
 功能描述  : 设置ucDelayedCsfbLauFlg
 输入参数  : csfb下，lau是否需要delay的标记
 输出参数  :
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月25日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetDelayedCsfbLauFlg(VOS_UINT8 ucDelayedCsfbLauFlg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.ucDelayedCsfbLauFlg = ucDelayedCsfbLauFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetSupportCsfbMtFollowOnFlg
 功能描述  : 获取Csfb Mt流程下，RAU是否需要带follown on标记
 输入参数  :
 输出参数  : 无
 返 回 值  : 返回Csfb Mt流程下，RAU是否需要带follown on标记
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月25日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetIsRauNeedFollowOnCsfbMtFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucIsRauNeedFollowOnCsfbMtFlg);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetSupportCsfbMtFollowOnFlg
 功能描述  : 设置Csfb Mt流程下，RAU是否需要带follown on标记
 输入参数  : Csfb Mt流程下，RAU是否需要带follown on标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月25日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetIsRauNeedFollowOnCsfbMtFlg(VOS_UINT8 ucIsRauNeedFollowOnCsfbMtFlg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucIsRauNeedFollowOnCsfbMtFlg = ucIsRauNeedFollowOnCsfbMtFlg;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetSupportCsfbMoFollowOnFlg
 功能描述  : 获取Csfb Mo流程下，RAU是否需要带follown on标记
 输入参数  :
 输出参数  : 无
 返 回 值  : 返回Csfb Mo流程下，RAU是否需要带follown on标记
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年6月10日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetIsRauNeedFollowOnCsfbMoFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucIsRauNeedFollowOnCsfbMoFlg);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetSupportCsfbMoFollowOnFlg
 功能描述  : 设置Csfb Mo流程下，RAU是否需要带follown on标记
 输入参数  : Csfb Mo流程下，RAU是否需要带follown on标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年6月10日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetIsRauNeedFollowOnCsfbMoFlg(VOS_UINT8 ucIsRauNeedFollowOnCsfbMoFlg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucIsRauNeedFollowOnCsfbMoFlg = ucIsRauNeedFollowOnCsfbMoFlg;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetIsDelFddBandSwitchOnFlg
 功能描述  : 是否删除FDD的开关标记
 输入参数  :
 输出参数  : 无
 返 回 值  : 返回是否需要删除FDD的开机标记
             VOS_TRUE:表示该开关启用
             VOS_FALSE:表示该开关不启动
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年2月27日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetIsDelFddBandSwitchOnFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucIsDelFddBandSwitchOnFlg);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetSupportCsfbMtFollowOnFlg
 功能描述  : 设置删除FDD的开关标记
 输入参数  : 删除FDD的开关标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年2月27日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetIsDelFddBandSwitchOnFlg(VOS_UINT8 ucIsDelFddBandSwitchOnFlg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucIsDelFddBandSwitchOnFlg = ucIsDelFddBandSwitchOnFlg;
}



/*****************************************************************************
 函 数 名  : NAS_MML_GetSupportAccBarPlmnSearchFlg
 功能描述  : 获取接入禁止后是否发起PLMN搜网
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 接入禁止发起搜网特性开关
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年10月15日
   作    者   : s00190137
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetSupportAccBarPlmnSearchFlg(
    VOS_UINT8                           ucAccBarPlmnSearchFlg
)
{
    (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucSupportAccBarPlmnSearchFlg) = ucAccBarPlmnSearchFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetSupportAccBarPlmnSearchFlg
 功能描述  : 设置接入禁止后是否发起PLMN搜网
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS-TRUE:允许搜网
             VOS_FALSE:不允许搜网
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年10月15日
   作    者   : s00190137
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetSupportAccBarPlmnSearchFlg( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucSupportAccBarPlmnSearchFlg);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetUserCfgOPlmnInfo
 功能描述  : 获取NV项中预置的本地PLMN列表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 内置的本地PLMN列表
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年10月15日
   作    者   : s00190137
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_USER_CFG_OPLMN_INFO_STRU* NAS_MML_GetUserCfgOPlmnInfo( VOS_VOID )
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stUserCfgOPlmnInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetUserCfgOPlmnInfo
 功能描述  : 设置用户设置的OPLMN列表
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年10月15日
   作    者   : s00190137
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetUserCfgOPlmnInfo(
    NAS_MML_USER_CFG_OPLMN_INFO_STRU       *pstUserCfgOPlmnInfo
)
{
    PS_MEM_CPY(&(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stUserCfgOPlmnInfo),
               pstUserCfgOPlmnInfo,
               sizeof(NAS_MML_USER_CFG_OPLMN_INFO_STRU));
}

/*****************************************************************************
 函 数 名  : NAS_MML_InitUserCfgOPlmnInfo
 功能描述  : 初始化内置OPLMN特性
 输入参数  : 无
 输出参数  : pstUserCfgOPlmnInfo:用户设置的OPLMN的定制特性
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年10月15日
   作    者   : s00190137
   修改内容   : 新生成函数
 2.日    期    : 2013年11月26日
   作    者    : s00190137
   修改内容    : 将最大支持设置的OPLMN扩展到256个
*****************************************************************************/
VOS_VOID  NAS_MML_InitUserCfgOPlmnInfo(
    NAS_MML_USER_CFG_OPLMN_INFO_STRU       *pstUserCfgOPlmnInfo
)
{
    /* 初始化特性使能开关为关闭  */
    pstUserCfgOPlmnInfo->ucActiveFlg    = VOS_FALSE;
    pstUserCfgOPlmnInfo->ucImsiCheckFlg = VOS_TRUE;

    /* 初始化OPLMN版本号信息 */
    PS_MEM_SET( pstUserCfgOPlmnInfo->aucVersion,
                (VOS_UINT8)0X00,
                sizeof(pstUserCfgOPlmnInfo->aucVersion));

    /* 初始化OPLMN信息个数为0 */
    pstUserCfgOPlmnInfo->usOplmnListNum    = 0;

    /* 初始化使能IMSI信息个数为0 */
    pstUserCfgOPlmnInfo->ucImsiPlmnListNum= 0;

    /* 初始化IMSI列表 */
    PS_MEM_SET( pstUserCfgOPlmnInfo->astImsiPlmnList,
                (VOS_UINT8)0X00,
                sizeof(pstUserCfgOPlmnInfo->astImsiPlmnList));

    return;
}



/*****************************************************************************
 函 数 名  : NAS_MML_GetRrcUtranNcellExistFlg
 功能描述  : 获取rrc utran ncell存在标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 获取rrc utran ncell存在标志
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月2日
    作    者   : z00234330
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8  NAS_MML_GetRrcUtranNcellExistFlg( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.stRrcNcellInfo.ucUtranNcellExist;
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetRrcUtranNcellExistFlg
 功能描述  : 设置rrc utran ncell存在标志
 输入参数  : 设置rrc utran ncell存在标志
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月2日
    作    者   : z00234330
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_SetRrcUtranNcellExistFlg(
    VOS_UINT8                           ucUtranNcellExist
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.stRrcNcellInfo.ucUtranNcellExist = ucUtranNcellExist;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetRrcLteNcellExistFlg
 功能描述  : 获取rrc Lte ncell存在标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 获取rrc Lte ncell存在标志
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月2日
    作    者   : z00234330
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8  NAS_MML_GetRrcLteNcellExistFlg( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.stRrcNcellInfo.ucLteNcellExist;
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetRrcLteNcellExistFlg
 功能描述  : 设置rrc lte ncell存在标志
 输入参数  : 设置rrc lte ncell存在标志
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月2日
    作    者   : z00234330
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_SetRrcLteNcellExistFlg(
    VOS_UINT8                           ucLteNcellExist
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.stRrcNcellInfo.ucLteNcellExist = ucLteNcellExist;
}



/*****************************************************************************
 函 数 名  : NAS_MML_SetDsdsRfShareFlg
 功能描述  : 设置当前DSDS是否支持信息
 输入参数  : ucDsDsRfShareFlg      : DSDS是否支持
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月21日
    作    者   : w00167002
    修改内容   : 新生成函数，默认DSDS不支持

*****************************************************************************/
VOS_VOID  NAS_MML_SetDsdsRfShareFlg(
    VOS_UINT16                          usDsdsRfShareFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.usDsdsRfShareSupportFlg = usDsdsRfShareFlg;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetDsdsRfShareFlg
 功能描述  : 获取当前DSDS是否支持信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE: 当前DSDS支持
             VOS_FALSE:当前DSDS不支持
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月21日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT16 NAS_MML_GetDsdsRfShareFlg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.usDsdsRfShareSupportFlg;
}
/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, begin */
/*****************************************************************************
 函 数 名  : NAS_MMLSetImsNormalRegStatus
 功能描述  : 设置当前IMS的正常注册状态
 输入参数  : enRegStatus - IMS的注册状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年12月14日
   作    者   : w00176964
   修改内容   : VoLTE_PhaseIII项目新增

*****************************************************************************/
VOS_VOID    NAS_MML_SetImsNormalRegStatus(
    NAS_MML_IMS_NORMAL_REG_STATUS_ENUM_UINT8                enRegStatus
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stImsDomainInfo.enImsNormalRegSta = enRegStatus;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetImsNormalRegStatus
 功能描述  : 获取当前IMS的正常注册状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前IMS的正常注册状态
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年09月23日
   作    者   : w00176964
   修改内容   : VoLTE_PhaseIII项目新增

*****************************************************************************/
NAS_MML_IMS_NORMAL_REG_STATUS_ENUM_UINT8   NAS_MML_GetImsNormalRegStatus(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stImsDomainInfo.enImsNormalRegSta;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetImsVoiceAvailFlg
 功能描述  : 设置当前IMS voice是否可用
 输入参数  : ucAvail - IMS voice 是否可用
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年12月14日
   作    者   : w00176964
   修改内容   : VoLTE_PhaseIII项目新增

*****************************************************************************/
VOS_VOID    NAS_MML_SetImsVoiceAvailFlg(
    VOS_UINT8                                               ucAvail
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stImsDomainInfo.ucImsVoiceAvail = ucAvail;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetImsVoiceAvailFlg
 功能描述  : 获取当前IMS voice是否可用
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前当前IMS voice是否可用
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年09月23日
   作    者   : w00176964
   修改内容   : VoLTE_PhaseIII项目新增

*****************************************************************************/
VOS_UINT8   NAS_MML_GetImsVoiceAvailFlg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stImsDomainInfo.ucImsVoiceAvail;
}
/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, end */

/*****************************************************************************
 函 数 名  : NAS_MML_GetLte3gppRelVersion
 功能描述  : 获取当前LTE 3gpp的版本
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前LTE 3gpp 版本
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年4月19日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改

*****************************************************************************/
NAS_MML_3GPP_REL_ENUM_UINT8   NAS_MML_GetLte3gppRelVersion(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stMs3GppRel.enLteNasRelease;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetLte3gppRelVersion
 功能描述  : 设置当前LTE 3gpp的版本
 输入参数  : enLteNasRelease - 当前LTE 3gpp 版本
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年4月19日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改

*****************************************************************************/
VOS_VOID  NAS_MML_SetLte3gppRelVersion(
    NAS_MML_3GPP_REL_ENUM_UINT8         enLteNasRelease
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMs3GppRel.enLteNasRelease = enLteNasRelease;
    return;
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetPersistentBearerState
 功能描述  : 设置当前是否存在persistent eps bearer标识
 输入参数  : enPersistentBearerState - 是否存在persistent eps bearer标识
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年4月20日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改

*****************************************************************************/
VOS_VOID    NAS_MML_SetPersistentBearerState(
    NAS_MML_PERSISTENT_BEARER_STATE_ENUM_UINT8              enPersistentBearerState
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stImsDomainInfo.enPersistentBearerState = enPersistentBearerState;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetPersistentBearerState
 功能描述  : 获取当前是否存在persistent eps bearer标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 是否存在persistent eps bearer标识
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年4月20日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改

*****************************************************************************/
NAS_MML_PERSISTENT_BEARER_STATE_ENUM_UINT8  NAS_MML_GetPersistentBearerState(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stImsDomainInfo.enPersistentBearerState;
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetImsCallFlg
 功能描述  : 设置当前IMS call是否存在
 输入参数  : ucImsCallFlg - IMS call是否存在
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月06日
   作    者   : s00217060
   修改内容   : DTS2014110608091

*****************************************************************************/
VOS_VOID    NAS_MML_SetImsCallFlg(
    VOS_UINT8                                               ucImsCallFlg
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stImsDomainInfo.ucImsCallFlg = ucImsCallFlg;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetImsCallFlg
 功能描述  : 获取当前IMS call是否存在
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前当前IMS call是否存在
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月06日
   作    者   : s00217060
   修改内容   : DTS2014110608091
*****************************************************************************/
VOS_UINT8   NAS_MML_GetImsCallFlg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stImsDomainInfo.ucImsCallFlg;
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetGsmBandCapability
 功能描述  : 设置GSM主集通路BAND
 输入参数  : GSM主集通路BAND
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年02月10日
    作    者   : f62575
    修改内容   : DTS2014012600456: en_NV_Item_WG_RF_MAIN_BAND
数据修改为从内存中获取
*****************************************************************************/
VOS_VOID NAS_MML_SetGsmBandCapability(
    VOS_UINT32                          ulBand
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsCapability.stPlatformBandCap.ulGsmCapability = ulBand;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetGsmBandCapability
 功能描述  : 获取GSM主集通路BAND
 输入参数  : 无
 输出参数  : 无
 返 回 值  : GSM主集通路BAND
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年02月10日
    作    者   : f62575
    修改内容   : DTS2014012600456: en_NV_Item_WG_RF_MAIN_BAND
数据修改为从内存中获取
*****************************************************************************/
VOS_UINT32 NAS_MML_GetGsmBandCapability(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsCapability.stPlatformBandCap.ulGsmCapability;
}


/* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-13, begin */
/*****************************************************************************
 函 数 名  : NAS_MML_SetEmcPdpStatusFlg
 功能描述  : 设置当前紧急PDN是否存在标志
 输入参数  : 当前紧急PDN是否存在标志
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月13日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetEmcPdpStatusFlg(
    VOS_UINT8                           ucEmcPdpStatusFlg
)
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;

    pstConnStatus   = NAS_MML_GetConnStatus();

    pstConnStatus->ucEmcPdpStatusFlg    = ucEmcPdpStatusFlg;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetEmcPdpStatusFlg
 功能描述  : 获取当前紧急PDN是否存在标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前紧急PDN是否存在标志
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月13日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetEmcPdpStatusFlg( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucEmcPdpStatusFlg;
}
/* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-13, end */

/* Added by f00261443 for VoLTE_PhaseIII  项目, 2013-12-16, begin */
/*****************************************************************************
 函 数 名  : NAS_MML_GetImsVoiceInterSysLauEnableFlg
 功能描述  : 读取在ImsVoice可用的时候，进行从L到Gu的异系统变换时,是否需要进行强制Lau的标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ucImsVoiceInterSysLauEnable---是否需要强制进行LAU的nv标记
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年12月16日
   作    者   : f00261443
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetImsVoiceInterSysLauEnableFlg (VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stImsVoiceMM.ucImsVoiceInterSysLauEnable;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetImsVoiceInterSysLauEnableFlg
 功能描述  : 设置ImsVoice可用的时候，进行从L到Gu的异系统变换时,是否需要进行强制Lau的标记
 输入参数  : ucImsVoiceInterSysLauEnable ---是否需要强制进行LAU
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月16日
   作    者   : f00261443
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetImsVoiceInterSysLauEnableFlg( VOS_UINT8 ucImsVoiceInterSysLauEnable )
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stImsVoiceMM.ucImsVoiceInterSysLauEnable = ucImsVoiceInterSysLauEnable;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetImsVoiceMMEnableFlg()
 功能描述  : 读取是否打开IMS移动性管理的选项
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ucImsVoiceMMEnable ---IMS Voice 移动性管理的标记
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月16日
   作    者   : f00261443
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetImsVoiceMMEnableFlg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stImsVoiceMM.ucImsVoiceMMEnable;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetImsVoiceMMEnableFlg
 功能描述  : 设置是否打开IMS移动性管理的标记
 输入参数  : ucImsVoiceMMEnable ---IMS Voice 移动性管理的标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月16日
   作    者   : f00261443
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetImsVoiceMMEnableFlg( VOS_UINT8 ucImsVoiceMMEnable)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stImsVoiceMM.ucImsVoiceMMEnable = ucImsVoiceMMEnable;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetGUNwImsVoiceSupportFlg
 功能描述  : 读取GU下网络对IMS Voice支持的能力
 输入参数  : 无
 输出参数  : 无
 返 回 值  : enNwImsVoCap
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月16日
   作    者   : f00261443
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8 NAS_MML_GetGUNwImsVoiceSupportFlg( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.enNwImsVoCap;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetGUNwImsVoiceSupportFlg
 功能描述  : 设置GU下网络对IMS Voice 支持的能力
 输入参数  : enNwImsVoCap
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月16日
   作    者   : f00261443
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetGUNwImsVoiceSupportFlg( NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8 enNwImsVoCap )
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stPsDomainInfo.enNwImsVoCap = enNwImsVoCap;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetLteNwImsVoiceSupportFlg
 功能描述  : 获取LTE下网络对IMS Voice 支持的能力
 输入参数  : 无
 输出参数  : 无
 返 回 值  : enNwImsVoCap
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月16日
   作    者   : f00261443
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8 NAS_MML_GetLteNwImsVoiceSupportFlg( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stEpsDomainInfo.enNwImsVoCap;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetLteNwImsVoiceSupportFlg
 功能描述  : 设置LTE下网络多IMS Voice支持的能力
 输入参数  : enNwImsVoCap
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月16日
   作    者   : f00261443
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetLteNwImsVoiceSupportFlg( NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8 enNwImsVoCap )
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stEpsDomainInfo.enNwImsVoCap = enNwImsVoCap;
}
/* Added by f00261443 for VoLTE_PhaseIII  项目, 2013-12-16, end */
/*****************************************************************************
 函 数 名  : NAS_MML_GetPsSupportFLg
 功能描述  : 获取当前网络是否支持PS域
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE   -- 当前网络支持PS域
             VOS_FALSE  -- 当前网络不支持PS域
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年01月17日
    作    者   : l00198894
    修改内容   : V9R1C53 C+L 离网重选项目

*****************************************************************************/
VOS_UINT8 NAS_MML_GetPsSupportFLg(VOS_VOID)
{
    /* 由于LTE网络系统消息中无PS域支持项，默认填写支持 */
    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetMmlCtx()->stNetworkInfo.stCampPlmnInfo.enNetRatType)
    {
        return VOS_TRUE;
    }

    return NAS_MML_GetNetworkInfo()->stPsDomainInfo.ucPsSupportFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetLcEnableFlg
 功能描述  : 设置当前是否为C+L形态
 输入参数  : ucLcEnableFLg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年01月17日
    作    者   : l00198894
    修改内容   : V9R1C53 C+L 离网重选项目

*****************************************************************************/
VOS_VOID NAS_MML_SetLcEnableFlg(VOS_UINT8 ucLcEnableFLg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucLcEnableFLg = ucLcEnableFLg;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetLcEnableFlg
 功能描述  : 获取C+L形态是否使能
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE       -- 当前为C+L形态
             VOS_FALSE      -- 当前不为C+L形态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年01月17日
    作    者   : l00198894
    修改内容   : V9R1C53 C+L 离网重选项目

*****************************************************************************/
VOS_UINT8 NAS_MML_GetLcEnableFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucLcEnableFLg);
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetIgnoreAuthRejFlg
 功能描述  : 设置是否移除鉴权拒绝的处理标识
 输入参数  : 鉴权忽略标识
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年02月18日
   作    者   : l00215384
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetIgnoreAuthRejFlg(
    VOS_UINT8                           ucIgnoreAuthRejFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stIgnoreAuthRejInfo.ucIgnoreAuthRejFlg
                               = ucIgnoreAuthRejFlg;
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetMaxAuthRejNo
 功能描述  : 设置允许最大移除鉴权拒绝的次数
 输入参数  : 允许的次数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年02月18日
   作    者   : l00215384
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetMaxAuthRejNo(
    VOS_UINT8                           ucMaxAuthRejNo
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stIgnoreAuthRejInfo.ucMaxAuthRejNo
                               = ucMaxAuthRejNo;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetAuthRejInfo
 功能描述  : 获取当前鉴权拒绝信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前鉴权拒绝信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年02月18日
   作    者   : l00215384
   修改内容   : 新生成函数
*****************************************************************************/
NAS_MML_IGNORE_AUTH_REJ_INFO_STRU * NAS_MML_GetAuthRejInfo(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stIgnoreAuthRejInfo);
}

#if (FEATURE_ON == FEATURE_ECALL)
/*****************************************************************************
 函 数 名  : NAS_MML_SetCallMode
 功能描述  : 设置ecall模式信息
 输入参数  : ecall模式信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年04月1日
   作    者   : s00261364
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetCallMode(
    NAS_MML_CALL_MODE_ENUM_UINT8       enCallMode
)
{
    NAS_MML_GetMmlCtx()->stSimInfo.enCallMode = enCallMode;

}


/*****************************************************************************
 函 数 名  : NAS_MML_GetEcallModeInfo
 功能描述  : 获取ecall模式信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前ecall模式信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年04月1日
   作    者   : s00261364
   修改内容   : 新生成函数
*****************************************************************************/
NAS_MML_CALL_MODE_ENUM_UINT8  NAS_MML_GetCallMode(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stSimInfo.enCallMode);
}



#endif


/*****************************************************************************
 函 数 名  : NAS_MML_InitHplmnAuthRejCounter
 功能描述  : 初始化鉴权拒绝次数记录
 输入参数  : 鉴权拒绝信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年02月18日
   作    者   : l00215384
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_InitHplmnAuthRejCounter(
    NAS_MML_IGNORE_AUTH_REJ_INFO_STRU                      *pstAuthRejInfo
)
{
    pstAuthRejInfo->ucMaxAuthRejNo = 0;
    pstAuthRejInfo->ucHplmnCsAuthRejCounter = 0;
    pstAuthRejInfo->ucHplmnPsAuthRejCounter = 0;
    pstAuthRejInfo->ucIgnoreAuthRejFlg = VOS_FALSE;

    return;
}

/*****************************************************************************
函 数 名  : NAS_MML_InitHighPrioRatHplmnTimerCfgInfo
功能描述  : 初始化高接入技术优先级的HPLMN定时器信息
输入参数  : 无
输出参数  : pstHighHplmnTimerCfg - 初始化高接入技术优先级的HPLMN定时器信息
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期  : 2014年2月19日
 作    者   : w00176964
 修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_InitHighPrioRatHplmnTimerCfgInfo(
    NAS_MML_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU             *pstHighHplmnTimerCfg
)
{
    pstHighHplmnTimerCfg->ulNonFirstSearchTimeLen   = TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER_NON_FIRST_LEN;
    pstHighHplmnTimerCfg->ulFirstSearchTimeLen      = TI_NAS_MMC_HIGH_RPIO_RAT_HPLMN_TIMER_FIRST_LEN;
    pstHighHplmnTimerCfg->ulFirstSearchTimeCount    = TI_NAS_MMC_HIGH_RPIO_RAT_HPLMN_TIMER_FIRST_SEARCH_COUNT;
    pstHighHplmnTimerCfg->ulRetrySearchTimeLen      = TI_NAS_MMC_HIGH_RPIO_RAT_HPLMN_TIMER_FIRST_LEN;
    pstHighHplmnTimerCfg->ucActiveFLg               = VOS_FALSE;
}


/*****************************************************************************
函 数 名  : NAS_MML_Get3GPP2UplmnNotPrefFlg
功能描述  : 得到Uplmn是否为优选网络
输入参数  : 无
输出参数  : 无
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期  : 2014年6月13日
 作    者   : b00269685
 修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_Get3GPP2UplmnNotPrefFlg( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.uc3GPPUplmnNotPrefFlg;
}

/*****************************************************************************
函 数 名  : NAS_MML_Set3GPP2UplmnNotPrefFlg
功能描述  : 设置Uplmn是否为优选网络
输入参数  : 无
输出参数  : uc3GPPUplmnNotPrefFlg - Uplmn是否为优选网络标志
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期  : 2014年6月13日
 作    者   : b00269685
 修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_Set3GPP2UplmnNotPrefFlg(VOS_UINT8 uc3GPPUplmnNotPrefFlg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.uc3GPPUplmnNotPrefFlg = uc3GPPUplmnNotPrefFlg;
}


/* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
/*****************************************************************************
 函 数 名  : NAS_MML_GetPdpConnStateInfo
 功能描述  : 获取MML中保存的Pdp连接状态信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的Pdp连接状态信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年06月16日
   作    者   : j00174725
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MML_GetPdpConnStateInfo( VOS_VOID )
{
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stConnStatus.ucPdpStatusFlg;
}
/* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, End */

/*****************************************************************************
函 数 名  : NAS_MML_GetSupportSrvccFlg
功能描述  : 得到是否支持srvcc标志
输入参数  : 无
输出参数  : 无
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期  : 2014年10月8日
 作    者   : b00269685
 修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetSupportSrvccFlg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucSupportSrvccFlg;
}

/*****************************************************************************
函 数 名  : NAS_MML_SetSupportSrvccFlg
功能描述  : 设置是否支持srvcc标志
输入参数  : 无
输出参数  : ucSupportSrvccFlg - 是否支持srvcc标志
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期  : 2014年6月13日
 作    者   : b00269685
 修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetSupportSrvccFlg(VOS_UINT8 ucSupportSrvccFlg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucSupportSrvccFlg = ucSupportSrvccFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetSyscfgTriHighRatSrchFlg
 功能描述  : 获取ucSyscfgTriHighRatSrchFlg
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回SYSCFG触发高优先级接入技术搜网标记
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年7月14日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetSyscfgTriHighRatSrchFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.ucSyscfgTriHighRatSrchFlg);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetSyscfgTriHighRatSrchFlg
 功能描述  : 设置ucSyscfgTriHighRatSrchFlg
 输入参数  : ucSyscfgTriHighRatSrchFlg:SYSCFG触发高优先级接入技术搜网标记
 输出参数  :
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年7月14日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetSyscfgTriHighRatSrchFlg(VOS_UINT8 ucSyscfgTriHighRatSrchFlg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.ucSyscfgTriHighRatSrchFlg = ucSyscfgTriHighRatSrchFlg;
}

/*****************************************************************************
函 数 名  : NAS_MML_GetDsdsSessionEndDelay
功能描述  : 得到DSDS SESSION END延迟的配置
输入参数  : 无
输出参数  : 无
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期  : 2014年7月17日
 作    者   : b00269685
 修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_DSDS_END_SESSION_DELAY_STRU* NAS_MML_GetDsdsSessionEndDelay(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stDsdsEndSesssionDelay);
}

/*****************************************************************************
函 数 名  : NAS_MML_SetDsdsEndSessionDelay
功能描述  : 设置DSDS SESSION END延迟的配置
输入参数  : pstDsdsEndSesssionDelay
输出参数  : 无
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期  : 2014年7月17日
 作    者   : b00269685
 修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetDsdsEndSessionDelay(NAS_MML_DSDS_END_SESSION_DELAY_STRU *pstDsdsEndSesssionDelay)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stDsdsEndSesssionDelay.ulCsRegEndSessionDelayTime
                                                = pstDsdsEndSesssionDelay->ulCsRegEndSessionDelayTime;
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stDsdsEndSesssionDelay.ulPsRegEndSessionDelayTime
                                                = pstDsdsEndSesssionDelay->ulPsRegEndSessionDelayTime;

    return;
}

/*****************************************************************************
函 数 名  : NAS_MML_InitDsdsSessionEndDelay
功能描述  : 初始化DSDS SESSION END延迟的配置
输入参数  : 无
输出参数  : 无
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期  : 2014年7月17日
 作    者   : b00269685
 修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_InitDsdsSessionEndDelay(NAS_MML_DSDS_END_SESSION_DELAY_STRU *pstDsdsEndSesssionDelay)
{
    PS_MEM_SET(pstDsdsEndSesssionDelay, 0, sizeof(NAS_MML_DSDS_END_SESSION_DELAY_STRU));

    pstDsdsEndSesssionDelay->ulCsRegEndSessionDelayTime = NAS_MML_CS_REG_END_SESSION_DEFAULT_DELAY_TIME;
    pstDsdsEndSesssionDelay->ulPsRegEndSessionDelayTime = NAS_MML_PS_REG_END_SESSION_DEFAULT_DELAY_TIME;

    return;
}

/*****************************************************************************
函 数 名  : NAS_MML_CALL_GetCallUmtsCodecType
功能描述  : 得到Umts capability
输入参数  :
输出参数  :
返 回 值  : &stCallUmtsCodecTypes
调用函数  :
被调函数  :

修改历史      :
1.日    期  : 2014年10月8日
 作    者   : b00269685
 修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_CALL_UMTS_CODEC_TYPE_STRU *NAS_MML_CALL_GetCallUmtsCodecType(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stCallUmtsCodecType);
}

/*****************************************************************************
函 数 名  : NAS_MML_CALL_SetCallUmtsCapaProc
功能描述  : 设置Umts capability
输入参数  : pstCodecType
输出参数  : 无
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期  : 2014年10月8日
 作    者   : b00269685
 修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_CALL_SetCallUmtsCodecType(NAS_MML_CALL_UMTS_CODEC_TYPE_STRU *pstCodecType)
{
    NAS_MML_CALL_UMTS_CODEC_TYPE_STRU  *pstUmtsCodecType = VOS_NULL_PTR;
    VOS_UINT32                          ulDefaultValue;
    VOS_UINT32                          i;

    ulDefaultValue          = VOS_FALSE;

    pstUmtsCodecType        = &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stCallUmtsCodecType);

    /* 检查参数是否合法,不合法则使用默认值,个数是否越界 */
    if ( pstCodecType->ucCnt > NAS_MML_CALL_MAX_UMTS_CODEC_TYPE_NUM )
    {
        ulDefaultValue      = VOS_TRUE;
        pstCodecType->ucCnt = NAS_MML_CALL_MAX_UMTS_CODEC_TYPE_NUM;
    }

    pstUmtsCodecType->ucCnt = 0;

    /* 检查是否有重复定义和超出范围的codec类型*/
    for ( i = 0; i < pstCodecType->ucCnt; i++ )
    {
        if ( (NAS_MML_CALL_UMTS_CODEC_TYPE_AMR   != pstCodecType->aucUmtsCodec[i])
          && (NAS_MML_CALL_UMTS_CODEC_TYPE_AMR2  != pstCodecType->aucUmtsCodec[i])
          && (NAS_MML_CALL_UMTS_CODEC_TYPE_AMRWB != pstCodecType->aucUmtsCodec[i]) )
        {
            ulDefaultValue = VOS_TRUE;
            break;
        }

        /* 将NVIM中的语音能力加入到内存中 */
        pstUmtsCodecType->aucUmtsCodec[pstUmtsCodecType->ucCnt++] = pstCodecType->aucUmtsCodec[i];
    }

    if ( VOS_TRUE == ulDefaultValue )
    {
        pstUmtsCodecType->ucCnt                                   = 0;
        /*lint -e961*/
        pstUmtsCodecType->aucUmtsCodec[pstUmtsCodecType->ucCnt++] = NAS_MML_CALL_UMTS_CODEC_TYPE_AMR;
        pstUmtsCodecType->aucUmtsCodec[pstUmtsCodecType->ucCnt++] = NAS_MML_CALL_UMTS_CODEC_TYPE_AMR2;
        /*lint +e961*/
    }
}

/*****************************************************************************
函 数 名  : NAS_MML_CALL_InitCallUmtsCodecType
功能描述  : 初始化Umts capability
输入参数  : pstCodecType
输出参数  : pstCodecType
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期  : 2014年10月8日
 作    者   : b00269685
 修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_CALL_InitCallUmtsCodecType(NAS_MML_CALL_UMTS_CODEC_TYPE_STRU *pstCodecType)
{
    PS_MEM_SET(pstCodecType, 0, sizeof(NAS_MML_CALL_UMTS_CODEC_TYPE_STRU));

    pstCodecType->ucCnt                              = 0;
    /*lint -e961*/
    pstCodecType->aucUmtsCodec[pstCodecType->ucCnt++]= NAS_MML_CALL_UMTS_CODEC_TYPE_AMR;
    pstCodecType->aucUmtsCodec[pstCodecType->ucCnt++]= NAS_MML_CALL_UMTS_CODEC_TYPE_AMR2;
    /*lint -e961*/

    return;
}

/*****************************************************************************
函 数 名  : NAS_MML_CALL_GetCallGsmCodecType
功能描述  : 得到stCallItemCodecType
输入参数  : 无
输出参数  : 无
返 回 值  : &stCallItemCodecType
调用函数  :
被调函数  :

修改历史      :
1.日    期  : 2014年10月8日
 作    者   : b00269685
 修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_CALL_GSM_CODEC_TYPE_STRU *NAS_MML_CALL_GetCallGsmCodeType(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stCallGsmCodecType);
}

/*****************************************************************************
函 数 名  : NAS_MML_CALL_SetCallGsmCodeType
功能描述  : 得到
输入参数  : pstCodecType
输出参数  : 无
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期  : 2014年10月8日
 作    者   : b00269685
 修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_CALL_SetCallGsmCodecType(NAS_MML_CALL_GSM_CODEC_TYPE_STRU *pstCodecType)
{
    /* 初始化语音编码版本列表 */
    NAS_MML_CALL_GSM_CODEC_TYPE_STRU   *pstGsmCodecType  = VOS_NULL_PTR;
    VOS_UINT32                          ulDefaultValue;
    VOS_UINT32                          i;

    ulDefaultValue = VOS_FALSE;

    pstGsmCodecType = &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stCallGsmCodecType);

    /* 检查参数是否合法,不合法则使用默认值,个数是否越界 */
    if (pstCodecType->ucCodecTypeNum > NAS_MML_CALL_BC_MAX_SPH_VER_NUM )
    {
        ulDefaultValue               = VOS_TRUE;
        pstCodecType->ucCodecTypeNum = NAS_MML_CALL_BC_MAX_SPH_VER_NUM;
    }

    pstGsmCodecType->ucCodecTypeNum = 0;

    /* 检查是否有重复定义和超出范围的codec类型*/
    for ( i = 0; i < pstCodecType->ucCodecTypeNum; i++ )
    {
        if ( (NAS_MML_CALL_BC_VAL_SPH_VER_FR_1 != pstCodecType->aucCodecType[i])
          && (NAS_MML_CALL_BC_VAL_SPH_VER_FR_2 != pstCodecType->aucCodecType[i])
          && (NAS_MML_CALL_BC_VAL_SPH_VER_FR_3 != pstCodecType->aucCodecType[i])
          && (NAS_MML_CALL_BC_VAL_SPH_VER_HR_1 != pstCodecType->aucCodecType[i])
          && (NAS_MML_CALL_BC_VAL_SPH_VER_HR_3 != pstCodecType->aucCodecType[i])
          && (NAS_MML_CALL_BC_VAL_SPH_VER_FR_5 != pstCodecType->aucCodecType[i]))
        {
            ulDefaultValue = VOS_TRUE;
            break;
        }

        /* 将NVIM中的语音能力加入到内存中 */
        pstGsmCodecType->aucCodecType[pstGsmCodecType->ucCodecTypeNum] = pstCodecType->aucCodecType[i];
        pstGsmCodecType->ucCodecTypeNum++;
    }

    /* 此处表示需要使用默认值 */
    if ( VOS_TRUE == ulDefaultValue )
    {
        /*lint -e961*/
        pstGsmCodecType->ucCodecTypeNum                                   = 0;
        pstGsmCodecType->aucCodecType[pstGsmCodecType->ucCodecTypeNum++] = NAS_MML_CALL_BC_VAL_SPH_VER_FR_3;
        pstGsmCodecType->aucCodecType[pstGsmCodecType->ucCodecTypeNum++] = NAS_MML_CALL_BC_VAL_SPH_VER_HR_3;
        pstGsmCodecType->aucCodecType[pstGsmCodecType->ucCodecTypeNum++] = NAS_MML_CALL_BC_VAL_SPH_VER_FR_2;
        pstGsmCodecType->aucCodecType[pstGsmCodecType->ucCodecTypeNum++] = NAS_MML_CALL_BC_VAL_SPH_VER_FR_1;
        pstGsmCodecType->aucCodecType[pstGsmCodecType->ucCodecTypeNum++] = NAS_MML_CALL_BC_VAL_SPH_VER_HR_1;
        pstGsmCodecType->aucCodecType[pstGsmCodecType->ucCodecTypeNum++] = NAS_MML_CALL_BC_VAL_SPH_VER_FR_5;
        /*lint +e961*/
    }
}

/*****************************************************************************
函 数 名  : NAS_MML_CALL_InitCallGsmCodecType
功能描述  : 初始化call itme codec type
输入参数  : pstCodecType
输出参数  : pstCodecType
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期  : 2014年10月8日
 作    者   : b00269685
 修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_CALL_InitCallGsmCodecType(NAS_MML_CALL_GSM_CODEC_TYPE_STRU *pstCodecType)
{
    PS_MEM_SET(pstCodecType, 0, sizeof(NAS_MML_CALL_GSM_CODEC_TYPE_STRU));

    /*lint -e961*/
    pstCodecType->ucCodecTypeNum                               = 0;
    pstCodecType->aucCodecType[pstCodecType->ucCodecTypeNum++] = NAS_MML_CALL_BC_VAL_SPH_VER_FR_3;
    pstCodecType->aucCodecType[pstCodecType->ucCodecTypeNum++] = NAS_MML_CALL_BC_VAL_SPH_VER_HR_3;
    pstCodecType->aucCodecType[pstCodecType->ucCodecTypeNum++] = NAS_MML_CALL_BC_VAL_SPH_VER_FR_2;
    pstCodecType->aucCodecType[pstCodecType->ucCodecTypeNum++] = NAS_MML_CALL_BC_VAL_SPH_VER_FR_1;
    pstCodecType->aucCodecType[pstCodecType->ucCodecTypeNum++] = NAS_MML_CALL_BC_VAL_SPH_VER_HR_1;
    pstCodecType->aucCodecType[pstCodecType->ucCodecTypeNum++] = NAS_MML_CALL_BC_VAL_SPH_VER_FR_5;
    /*lint -e961*/

    return;
}

/*****************************************************************************
函 数 名  : NAS_MML_LogMsgInfo
功能描述  : 判断消息是否是定时器发出的，如果是就打印定时器信息，否则打印消息信息
输入参数  : pstMsgHeader
输出参数  : 无
返 回 值  :
调用函数  :
被调函数  :

修改历史  :
1.日    期  : 2015年01月23日
  作    者  : wx270776
  修改内容  : 新生成函数
2.日    期  : 2015年11月30日
  作    者  : z00359541
  修改内容  : DTS2015112803743: 在记录消息前加入消息过滤
*****************************************************************************/
VOS_VOID NAS_MML_LogMsgInfo(
    MSG_HEADER_STRU                    *pstMesgHeader
)
{
    VOS_UINT32                          ulSenderPid;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulMsgName;

    /* 消息在忽略列表中，不进行记录 */
    if (VOS_TRUE == NAS_MML_IsNeedDiscardMsg(pstMesgHeader->ulSenderPid,
            pstMesgHeader->ulReceiverPid, pstMesgHeader->ulMsgName))
    {
        return;
    }

    /* 判断发送id是否是定时器 */
    if (VOS_PID_TIMER == pstMesgHeader->ulSenderPid)
    {
        ulSenderPid      =    ((REL_TIMER_MSG*)pstMesgHeader)->ulSenderPid;
        ulReceiverPid    =    ((REL_TIMER_MSG*)pstMesgHeader)->ulReceiverPid;
        ulMsgName        =    ((REL_TIMER_MSG*)pstMesgHeader)->ulName;
    }
    else
    {
        ulSenderPid      =    pstMesgHeader->ulSenderPid;
        ulReceiverPid    =    pstMesgHeader->ulReceiverPid;
        ulMsgName        =    pstMesgHeader->ulMsgName;
    }
    /* 打印消息 */
    NAS_MML_AddLogEventState((VOS_UINT16)ulSenderPid, (VOS_UINT16)ulReceiverPid, (VOS_UINT16)ulMsgName);

    return;
}


/*****************************************************************************
函 数 名  : NAS_MML_AddLogEventState
功能描述  : 增加stLogEventState
输入参数  : usSendPid, usMsgName
输出参数  : 无
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期  : 2014年10月20日
 作    者   : b00269685
 修改内容   : 新生成函数
2.日    期  : 2014年12月04日
 作    者   : z00359541
 修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_AddLogEventState(VOS_UINT16 usSendPid, VOS_UINT16 usReceivePid, VOS_UINT16 usMsgName)
{
    NAS_MML_LOG_EVENT_STATE_STRU       *pstLogEventState;
    NAS_UTRANCTRL_CTX_STRU             *pstUtranCtrlCtx;
    VOS_UINT8                           ucIndex;

    pstUtranCtrlCtx     = NAS_UTRANCTRL_GetUtranCtrlCtx();

    pstLogEventState = &(NAS_MML_GetMmlCtx()->stMaintainInfo.stLogEventState);

    pstLogEventState->ucLatestIndex = (pstLogEventState->ucLatestIndex + 1) % NAS_MML_MAX_LOG_EVENT_STATE_NUM;

    ucIndex                         = pstLogEventState->ucLatestIndex;

    pstLogEventState->stEventState[ucIndex].ulReceiveTime = VOS_GetTick();
    pstLogEventState->stEventState[ucIndex].usSendPid     = usSendPid;
    pstLogEventState->stEventState[ucIndex].usReceivePid  = usReceivePid;
    pstLogEventState->stEventState[ucIndex].usMsgName     = usMsgName;
    pstLogEventState->stEventState[ucIndex].ucMmcFsmId    = (VOS_UINT8)NAS_MMC_GetCurrFsmId();
    pstLogEventState->stEventState[ucIndex].ucMmcState    = (VOS_UINT8)NAS_MMC_GetFsmTopState();
    pstLogEventState->stEventState[ucIndex].ucGmmState    = g_GmmGlobalCtrl.ucState;
    pstLogEventState->stEventState[ucIndex].ucMmState     = g_MmGlobalInfo.ucState;
    pstLogEventState->stEventState[ucIndex].ucUtranCtrlFsmId = (VOS_UINT8)pstUtranCtrlCtx->stCurFsm.enFsmId;
    pstLogEventState->stEventState[ucIndex].ucUtranCtrlState = (VOS_UINT8)pstUtranCtrlCtx->stCurFsm.ulState;

    return;
}

/*****************************************************************************
函 数 名  : NAS_MML_UpdateExitTime
功能描述  : 更新消息处理退出时间
输入参数  : 无
输出参数  : 无
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期  : 2014年10月20日
 作    者   : b00269685
 修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_UpdateExitTime(VOS_VOID)
{
    NAS_MML_LOG_EVENT_STATE_STRU       *pstLogEventState;

    pstLogEventState             = &(NAS_MML_GetMmlCtx()->stMaintainInfo.stLogEventState);

    pstLogEventState->ulExitTime = VOS_GetTick();

    return;
}

/*****************************************************************************
函 数 名  : NAS_MML_InitLogEventState
功能描述  : 初始化LogEventState
输入参数  : 无
输出参数  : 无
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期  : 2014年10月20日
 作    者   : b00269685
 修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_InitLogEventState(NAS_MML_LOG_EVENT_STATE_STRU *pstLogEventState)
{
    PS_MEM_SET(pstLogEventState, 0, sizeof(NAS_MML_LOG_EVENT_STATE_STRU));

    return;
}

/*****************************************************************************
函 数 名  : NAS_MML_InitChangeNWCauseInfo
功能描述  : 初始化修改拒绝原因值信息
输入参数  : 无
输出参数  :
返 回 值  :
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2014年10月20日
  作    者   : h00285180
  修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_MML_InitChangeNWCauseInfo(NAS_MML_CHANGE_NW_CAUSE_INFO_STRU *pstChangeNWCauseInfo)
{
    PS_MEM_SET(&(pstChangeNWCauseInfo->stChangeNWCauseCfg),
                (VOS_UINT8)0X00,
                sizeof(NAS_MML_CHANGE_NW_CAUSE_CFG_STRU));
    pstChangeNWCauseInfo->stChangeNWCauseCfg.ucCsRegCauseNum    = 0;
    pstChangeNWCauseInfo->stChangeNWCauseCfg.ucPsRegCauseNum    = 0;
    pstChangeNWCauseInfo->stChangeNWCauseCfg.ucDetachCauseNum   = 0;
    pstChangeNWCauseInfo->stChangeNWCauseCfg.ucPsSerRejCauseNum = 0;
    pstChangeNWCauseInfo->stChangeNWCauseCfg.ucMmAbortCauseNum  = 0;
    pstChangeNWCauseInfo->stChangeNWCauseCfg.ucCmSerRejCauseNum = 0;

    pstChangeNWCauseInfo->stChangeNWCauseCfg.ucHplmnCsRejCauseChangTo17MaxNum = 0;
    pstChangeNWCauseInfo->stChangeNWCauseCfg.ucHplmnPsRejCauseChangTo17MaxNum = 0;
    pstChangeNWCauseInfo->stChangeNWCauseCfg.ucVplmnCsRejCauseChangTo17MaxNum = 0;
    pstChangeNWCauseInfo->stChangeNWCauseCfg.ucVplmnPsRejCauseChangTo17MaxNum = 0;

    pstChangeNWCauseInfo->stRejCauseChangedCounter.ucHplmnPsRejCauseChangedCout = 0;
    pstChangeNWCauseInfo->stRejCauseChangedCounter.ucHplmnCsRejCauseChangedCout = 0;
    pstChangeNWCauseInfo->stRejCauseChangedCounter.ucVplmnPsRejCauseChangedCout = 0;
    pstChangeNWCauseInfo->stRejCauseChangedCounter.ucVplmnCsRejCauseChangedCout = 0;
}

/*****************************************************************************
函 数 名  : NAS_MML_SetChangeNWCauseCfg
功能描述  : 设置修改拒绝原因值信息
输入参数  : 无
输出参数  :
返 回 值  :
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2014年10月20日
  作    者   : h00285180
  修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_SetChangeNWCauseCfg(const NAS_MML_CHANGE_NW_CAUSE_CFG_STRU *pstChangeNWCauseCfg)
{
    PS_MEM_CPY(&(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stChangeNWCauseInfo.stChangeNWCauseCfg),
               pstChangeNWCauseCfg,
               sizeof(NAS_MML_CHANGE_NW_CAUSE_CFG_STRU));
}

/*****************************************************************************
函 数 名  : NAS_MML_GetChangeNWCauseCfg
功能描述  : 获取修改拒绝原因值配置信息
输入参数  : 无
输出参数  :
返 回 值  :
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2014年10月20日
  作    者   : h00285180
  修改内容   : 新生成函数
*****************************************************************************/
NAS_MML_CHANGE_NW_CAUSE_CFG_STRU* NAS_MML_GetChangeNWCauseCfg(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stChangeNWCauseInfo.stChangeNWCauseCfg);
}

/*****************************************************************************
函 数 名  : NAS_MML_GetChangeNWCauseCfgByRejType
功能描述  : 根据流程类型获取修改拒绝原因值配置信息
输入参数  : NAS_MML_CHANGE_REJ_TYPE_ENUM_UINT8  enChangeRejType流程类型
输出参数  : NAS_MMC_NVIM_ADAPTION_CAUSE_STRU   **pstAdaptCause 该流程类型配置的拒绝原因值信息
返 回 值  : 该流程类型配置的拒绝原因值个数
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2014年10月20日
  作    者   : h00285180
  修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MML_GetChangeNWCauseCfgByRejType(
    NAS_MML_CHANGE_REJ_TYPE_ENUM_UINT8  enChangeRejType,
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU   **pstAdaptCause
)
{
    NAS_MML_CHANGE_NW_CAUSE_CFG_STRU   *pstChangeNWCauseCfg  = VOS_NULL_PTR;

    pstChangeNWCauseCfg = NAS_MML_GetChangeNWCauseCfg();

    switch (enChangeRejType)
    {
        /* CS域注册流程(LU)拒绝原因值替换信息 */
        case NAS_MML_CHANGE_REJ_TYPE_CS_REG:
            *pstAdaptCause = pstChangeNWCauseCfg->astCsRegAdaptCause;
            return pstChangeNWCauseCfg->ucCsRegCauseNum;

        /* PS域注册流程(ATTACH/RAU)拒绝原因值替换信息 */
        case NAS_MML_CHANGE_REJ_TYPE_PS_REG:
             *pstAdaptCause = pstChangeNWCauseCfg->astPsRegAdaptCause;
             return pstChangeNWCauseCfg->ucPsRegCauseNum;

        /* 网络GPRS Detach 流程拒绝原因值替换信息 */
        case NAS_MML_CHANGE_REJ_TYPE_DETACH:
            *pstAdaptCause = pstChangeNWCauseCfg->astDetachAdaptCause;
            return pstChangeNWCauseCfg->ucDetachCauseNum;

        /* GMM service request流程拒绝原因值替换信息 */
        case NAS_MML_CHANGE_REJ_TYPE_PS_SER_REJ:
             *pstAdaptCause = pstChangeNWCauseCfg->astPsSerRejAdaptCause;
            return pstChangeNWCauseCfg->ucPsSerRejCauseNum;

        /* MM ABORT流程拒绝原因值替换信息 */
        case NAS_MML_CHANGE_REJ_TYPE_MM_ABORT:
            *pstAdaptCause = pstChangeNWCauseCfg->astMmAbortAdaptCause;
            return pstChangeNWCauseCfg->ucMmAbortCauseNum;

        /* CM Service流程拒绝原因值替换信息 */
        case NAS_MML_CHANGE_REJ_TYPE_CM_SER_REJ:
            *pstAdaptCause = pstChangeNWCauseCfg->astCmSerRejAdaptCause;
            return pstChangeNWCauseCfg->ucCmSerRejCauseNum;

        default:
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MML_GetChangeNWCauseCfgByRejType: The input in invalid" );
            *pstAdaptCause = VOS_NULL_PTR;
            return 0;
    }
}

/*****************************************************************************
函 数 名  : NAS_MML_GetHplmnChangeNWCause
功能描述  : 根据流程类型获取对应的替换后的HPLMN拒绝原因值
输入参数  : NAS_MML_CHANGE_REJ_TYPE_ENUM_UINT8  enChangeRejType 流程类型
            VOS_UINT8 ucCause 网络实际拒绝原因值
输出参数  : 无
返 回 值  : 返回NV配置的该流程对应HPLMN需要替换的原因值
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2014年10月20日
  作    者   : h00285180
  修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MML_GetHplmnChangeNWCause(
    NAS_MML_CHANGE_REJ_TYPE_ENUM_UINT8  enChangeRejType,
    VOS_UINT8                           ucCause
)
{
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU   *pstAdaptCause = VOS_NULL_PTR;
    VOS_UINT8                           ucAdaptCauseNum;
    VOS_UINT32                          i;

    ucAdaptCauseNum = NAS_MML_GetChangeNWCauseCfgByRejType(enChangeRejType, &pstAdaptCause);

    for (i = 0; i < ucAdaptCauseNum; i++)
    {
        if (ucCause == pstAdaptCause[i].ucCnCause)
        {
            return pstAdaptCause[i].ucHplmnCause;
        }
    }

    /* 未找到NV配置拒绝原因值，返回原有拒绝原因值 */
    return ucCause;
}

/*****************************************************************************
函 数 名  : NAS_MML_GetVplmnChangeNWCause
功能描述  : 根据流程类型获取对应的替换后的VPLMN拒绝原因值
输入参数  : NAS_MML_CHANGE_REJ_TYPE_ENUM_UINT8  enChangeRejType 流程类型
            VOS_UINT8 ucCause 网络实际拒绝原因值
输出参数  : 无
返 回 值  : 返回NV配置的该流程对应VPLMN需要替换的原因值
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2014年10月20日
  作    者   : h00285180
  修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MML_GetVplmnChangeNWCause(
    NAS_MML_CHANGE_REJ_TYPE_ENUM_UINT8  enChangeRejType,
    VOS_UINT8                           ucCause
)
{
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU   *pstAdaptCause = VOS_NULL_PTR;
    VOS_UINT8                           ucAdaptCauseNum;
    VOS_UINT32                          i;

    ucAdaptCauseNum = NAS_MML_GetChangeNWCauseCfgByRejType(enChangeRejType, &pstAdaptCause);

    for (i = 0; i < ucAdaptCauseNum; i++)
    {
        if (ucCause == pstAdaptCause[i].ucCnCause)
        {
            return pstAdaptCause[i].ucVplmnCause;
        }
    }

    /* 未找到NV配置拒绝原因值，返回原有拒绝原因值 */
    return ucCause;
}

/*****************************************************************************
函 数 名  : NAS_MML_GetHplmnPsRejChangeTo17Flg
功能描述  : 获取Hplmn Ps域拒绝时是否需要继续替换为#17标记
输入参数  : 无
输出参数  : 无
返 回 值  : 返回Hplmn Ps域拒绝时是否需要继续替换为#17标记
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2014年10月20日
  作    者   : h00285180
  修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MML_GetHplmnPsRejChangeTo17Flg(VOS_VOID)
{
    NAS_MML_REJ_CAUSE_CHANGED_COUNTER_STRU                 *pstChangeCauseCounterInfo = VOS_NULL_PTR;
    NAS_MML_CHANGE_NW_CAUSE_CFG_STRU                       *pstChangeNWCauseCfg       = VOS_NULL_PTR;

    pstChangeCauseCounterInfo = NAS_MML_GetRejCauseChangedCounter();
    pstChangeNWCauseCfg = NAS_MML_GetChangeNWCauseCfg();

    if ((pstChangeNWCauseCfg->ucHplmnPsRejCauseChangTo17MaxNum) > (pstChangeCauseCounterInfo->ucHplmnPsRejCauseChangedCout))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
函 数 名  : NAS_MML_GetHplmnCsRejChangeTo17Flg
功能描述  : 获取Hplmn Cs域拒绝时是否需要继续替换为#17标记
输入参数  : 无
输出参数  : 无
返 回 值  : 返回Hplmn Cs域拒绝时是否需要继续替换为#17标记
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2014年10月20日
  作    者   : h00285180
  修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MML_GetHplmnCsRejChangeTo17Flg(VOS_VOID)
{
    NAS_MML_REJ_CAUSE_CHANGED_COUNTER_STRU                 *pstChangeCauseCounterInfo = VOS_NULL_PTR;
    NAS_MML_CHANGE_NW_CAUSE_CFG_STRU                       *pstChangeNWCauseCfg       = VOS_NULL_PTR;

    pstChangeCauseCounterInfo = NAS_MML_GetRejCauseChangedCounter();
    pstChangeNWCauseCfg = NAS_MML_GetChangeNWCauseCfg();

    if ((pstChangeNWCauseCfg->ucHplmnCsRejCauseChangTo17MaxNum) > (pstChangeCauseCounterInfo->ucHplmnCsRejCauseChangedCout))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
函 数 名  : NAS_MML_GetVplmnPsRejChangeTo17Flg
功能描述  : 获取Vplmn Ps域拒绝时是否需要继续替换为#17标记
输入参数  : 无
输出参数  : 无
返 回 值  : 返回Vplmn Ps域拒绝时是否需要继续替换为#17标记
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2014年10月20日
  作    者   : h00285180
  修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MML_GetVplmnPsRejChangeTo17Flg(VOS_VOID)
{
    NAS_MML_REJ_CAUSE_CHANGED_COUNTER_STRU                 *pstChangeCauseCounterInfo = VOS_NULL_PTR;
    NAS_MML_CHANGE_NW_CAUSE_CFG_STRU                       *pstChangeNWCauseCfg       = VOS_NULL_PTR;

    pstChangeCauseCounterInfo = NAS_MML_GetRejCauseChangedCounter();
    pstChangeNWCauseCfg = NAS_MML_GetChangeNWCauseCfg();

    if ((pstChangeNWCauseCfg->ucVplmnPsRejCauseChangTo17MaxNum) > (pstChangeCauseCounterInfo->ucVplmnPsRejCauseChangedCout))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
函 数 名  : NAS_MML_GetVplmnCsRejChangeTo17Flg
功能描述  : 获取Vplmn Cs域拒绝时是否需要继续替换为#17标记
输入参数  : 无
输出参数  : 无
返 回 值  : 返回Vplmn Cs域拒绝时是否需要继续替换为#17标记
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2014年10月20日
  作    者   : h00285180
  修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MML_GetVplmnCsRejChangeTo17Flg(VOS_VOID)
{
    NAS_MML_REJ_CAUSE_CHANGED_COUNTER_STRU                 *pstChangeCauseCounterInfo = VOS_NULL_PTR;
    NAS_MML_CHANGE_NW_CAUSE_CFG_STRU                       *pstChangeNWCauseCfg       = VOS_NULL_PTR;

    pstChangeCauseCounterInfo = NAS_MML_GetRejCauseChangedCounter();
    pstChangeNWCauseCfg = NAS_MML_GetChangeNWCauseCfg();

    if ((pstChangeNWCauseCfg->ucVplmnCsRejCauseChangTo17MaxNum) > (pstChangeCauseCounterInfo->ucVplmnCsRejCauseChangedCout))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
函 数 名  : NAS_MML_IncHplmnPsRejCauseChangedCounter
功能描述  : Hplmn Ps域拒绝时替换为#17的计数器+1
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2014年10月20日
  作    者   : h00285180
  修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_IncHplmnPsRejCauseChangedCounter(VOS_VOID)
{
    NAS_MML_REJ_CAUSE_CHANGED_COUNTER_STRU                 *pstChangeCauseCounterInfo = VOS_NULL_PTR;

    pstChangeCauseCounterInfo = NAS_MML_GetRejCauseChangedCounter();
    (pstChangeCauseCounterInfo->ucHplmnPsRejCauseChangedCout)++;
}

/*****************************************************************************
函 数 名  : NAS_MML_IncHplmnCsRejCauseChangedCounter
功能描述  : Hplmn Cs域拒绝时替换为#17的计数器+1
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2014年10月20日
作    者   : h00285180
修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_IncHplmnCsRejCauseChangedCounter(VOS_VOID)
{
    NAS_MML_REJ_CAUSE_CHANGED_COUNTER_STRU                 *pstChangeCauseCounterInfo = VOS_NULL_PTR;

    pstChangeCauseCounterInfo = NAS_MML_GetRejCauseChangedCounter();
    (pstChangeCauseCounterInfo->ucHplmnCsRejCauseChangedCout)++;
}

/*****************************************************************************
函 数 名  : NAS_MML_IncVplmnPsRejCauseChangedCounter
功能描述  : Vplmn Ps域拒绝时替换为#17的计数器+1
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2014年10月20日
  作    者   : h00285180
  修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_IncVplmnPsRejCauseChangedCounter(VOS_VOID)
{
    NAS_MML_REJ_CAUSE_CHANGED_COUNTER_STRU                 *pstChangeCauseCounterInfo = VOS_NULL_PTR;

    pstChangeCauseCounterInfo = NAS_MML_GetRejCauseChangedCounter();
    (pstChangeCauseCounterInfo->ucVplmnPsRejCauseChangedCout)++;
}

/*****************************************************************************
函 数 名  : NAS_MML_IncVplmnCsRejCauseChangedCounter
功能描述  : Vplmn Cs域拒绝时替换为#17的计数器+1
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2014年10月20日
作    者   : h00285180
修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_IncVplmnCsRejCauseChangedCounter(VOS_VOID)
{
    NAS_MML_REJ_CAUSE_CHANGED_COUNTER_STRU                 *pstChangeCauseCounterInfo = VOS_NULL_PTR;

    pstChangeCauseCounterInfo = NAS_MML_GetRejCauseChangedCounter();
    (pstChangeCauseCounterInfo->ucVplmnCsRejCauseChangedCout)++;
}

/*****************************************************************************
函 数 名  : NAS_MML_ResetHplmnPsRejCauseChangedCounter
功能描述  : Hplmn Ps域拒绝时替换为#17的计数器清0
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2014年10月20日
  作    者   : h00285180
  修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_ResetHplmnPsRejCauseChangedCounter(VOS_VOID)
{
    NAS_MML_REJ_CAUSE_CHANGED_COUNTER_STRU                 *pstChangeCauseCounterInfo = VOS_NULL_PTR;

    pstChangeCauseCounterInfo = NAS_MML_GetRejCauseChangedCounter();
    pstChangeCauseCounterInfo->ucHplmnPsRejCauseChangedCout = 0;
}

/*****************************************************************************
函 数 名  : NAS_MML_ResetHplmnCsRejCauseChangedCounter
功能描述  : Hplmn Cs域拒绝时替换为#17的计数器清0
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2014年10月20日
  作    者   : h00285180
  修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_ResetHplmnCsRejCauseChangedCounter(VOS_VOID)
{
    NAS_MML_REJ_CAUSE_CHANGED_COUNTER_STRU                 *pstChangeCauseCounterInfo = VOS_NULL_PTR;

    pstChangeCauseCounterInfo = NAS_MML_GetRejCauseChangedCounter();
    pstChangeCauseCounterInfo->ucHplmnCsRejCauseChangedCout = 0;
}

/*****************************************************************************
函 数 名  : NAS_MML_ResetVplmnPsRejCauseChangedCounter
功能描述  : Vplmn Ps域拒绝时替换为#17的计数器清0
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2014年10月20日
  作    者   : h00285180
  修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_ResetVplmnPsRejCauseChangedCounter(VOS_VOID)
{
    NAS_MML_REJ_CAUSE_CHANGED_COUNTER_STRU                 *pstChangeCauseCounterInfo = VOS_NULL_PTR;

    pstChangeCauseCounterInfo = NAS_MML_GetRejCauseChangedCounter();
    pstChangeCauseCounterInfo->ucVplmnPsRejCauseChangedCout = 0;
}

/*****************************************************************************
函 数 名  : NAS_MML_ResetVplmnCsRejCauseChangedCounter
功能描述  : Vplmn Cs域拒绝时替换为#17的计数器清0
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2014年10月20日
  作    者   : h00285180
  修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_ResetVplmnCsRejCauseChangedCounter(VOS_VOID)
{
    NAS_MML_REJ_CAUSE_CHANGED_COUNTER_STRU                 *pstChangeCauseCounterInfo = VOS_NULL_PTR;

    pstChangeCauseCounterInfo = NAS_MML_GetRejCauseChangedCounter();
    pstChangeCauseCounterInfo->ucVplmnCsRejCauseChangedCout = 0;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetSupportDamPlmnList
 功能描述  : 获取支持DAM特性网络的信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 支持DAM特性网络的信息
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年1月4日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改

*****************************************************************************/
NAS_MML_SUPPORT_DAM_PLMN_INFO_STRU *NAS_MML_GetSupportDamPlmnList(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stDamPlmnInfoCfg.stDamPlmnList);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetDamImsiPlmnList
 功能描述  : 获取支持DAM特性卡号段对应的mcc、mnc的信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 支持DAM特性卡号段对应的mcc、mnc的信息
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年1月4日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改

*****************************************************************************/
NAS_MML_DAM_IMSI_PLMN_LIST_STRU *NAS_MML_GetDamImsiPlmnList(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stDamPlmnInfoCfg.stImsiPlmnList);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetDamPlmnInfoCfg
 功能描述  : 获取支持DAM特性卡号段和网络列表信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 支持DAM特性卡号段和网络列表信息
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年1月4日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改

*****************************************************************************/
NAS_MML_DAM_PLMN_INFO_CONFIG_STRU *NAS_MML_GetDamPlmnInfoCfg(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stDamPlmnInfoCfg);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetT3402Len
 功能描述  : 获取T3402定时器时长
 输入参数  : 无
 输出参数  : 无
 返 回 值  : T3402定时器时长
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年1月4日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改

*****************************************************************************/
VOS_UINT32 NAS_MML_GetT3402Len(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stEpsDomainInfo.ulT3402Len);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetT3402Len
 功能描述  : 设置T3402定时器时长
 输入参数  : ulT3402Len - T3402定时器时长
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年1月4日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改

*****************************************************************************/
VOS_VOID NAS_MML_SetT3402Len(
    VOS_UINT32                          ulT3402Len
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stEpsDomainInfo.ulT3402Len = ulT3402Len;
    return;
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetEnableLteTrigPlmnSearchFlag
 功能描述  : 设置enable lte后是否触发搜网标识
 输入参数  : ucEnableLteTrigPlmnSearchFlag - enable lte后是否触发搜网标识
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年1月4日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改

*****************************************************************************/
VOS_VOID NAS_MML_SetEnableLteTrigPlmnSearchFlag(
    VOS_UINT8                           ucEnableLteTrigPlmnSearchFlag
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucEnableLteTrigPlmnSearchFlag = ucEnableLteTrigPlmnSearchFlag;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetVoiceNotAvailPlmnForbiddenPeriod
 功能描述  : 设置cs ps mode1由于语音不支持导致disable lte的网络的惩罚时间
 输入参数  : ulLteVoiceNotAvailPlmnForbiddenPeriod - 不支持语音disable lte网络的惩罚时间
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年4月24日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改

*****************************************************************************/
VOS_VOID NAS_MML_SetVoiceNotAvailPlmnForbiddenPeriod(
    VOS_UINT32                          ulLteVoiceNotAvailPlmnForbiddenPeriod
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ulLteVoiceNotAvailPlmnForbiddenPeriod = ulLteVoiceNotAvailPlmnForbiddenPeriod;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetVoiceNotAvailPlmnForbiddenPeriod
 功能描述  : 获取cs ps mode1由于语音不支持导致disable lte的网络的惩罚时间
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年4月24日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改

*****************************************************************************/
VOS_UINT32 NAS_MML_GetVoiceNotAvailPlmnForbiddenPeriod(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ulLteVoiceNotAvailPlmnForbiddenPeriod;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetEnableLteTrigPlmnSearchFlag
 功能描述  : 获取enable lte后是否触发搜网标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : enable lte后是否触发搜网标识
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年1月4日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改

*****************************************************************************/
VOS_UINT8 NAS_MML_GetEnableLteTrigPlmnSearchFlag(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucEnableLteTrigPlmnSearchFlag);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetAddDamPlmnInDisablePlmnWithRatListFlag
 功能描述  : 设置在DAM网络 disable lte后是否将DAM的lte网络加入禁止接入技术网络列表中的标识
 输入参数  : ucAddDamPlmnInDisablePlmnWithRatListFlag - 在DAM网络 disable lte后是否将DAM的lte网络加入禁止接入技术网络列表中的标识
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年1月4日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改

*****************************************************************************/
VOS_VOID NAS_MML_SetAddDamPlmnInDisablePlmnWithRatListFlag(
    VOS_UINT8                           ucAddDamPlmnInDisablePlmnWithRatListFlag
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucAddDamPlmnInDisablePlmnWithRatListFlag = ucAddDamPlmnInDisablePlmnWithRatListFlag;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetAddDamPlmnInDisablePlmnWithRatListFlag
 功能描述  : 获取在DAM网络 disable lte后是否将DAM的lte网络加入禁止接入技术网络列表中的标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年1月4日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改

*****************************************************************************/
VOS_UINT8 NAS_MML_GetAddDamPlmnInDisablePlmnWithRatListFlag(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucAddDamPlmnInDisablePlmnWithRatListFlag;
}

/*****************************************************************************
函 数 名  : NAS_MML_InitDamPlmnInfoCfg
功能描述  : 初始化支持DAM特性网络信息
输入参数  : pstDamCfgPlmnInfo - Dam配置网络信息
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2015年1月4日
  作    者   : z00161729
  修改内容   : AT&T 支持DAM特性修改
*****************************************************************************/
VOS_VOID  NAS_MML_InitDamPlmnInfoCfg(
    NAS_MML_DAM_PLMN_INFO_CONFIG_STRU  *pstDamCfgPlmnInfo
)
{
    VOS_UINT32                          i;

    pstDamCfgPlmnInfo->stDamPlmnList.ucPlmnNum   = 0;
    pstDamCfgPlmnInfo->stImsiPlmnList.ucPlmnNum  = 0;
    PS_MEM_SET(pstDamCfgPlmnInfo->stDamPlmnList.aucReserved, 0, sizeof(pstDamCfgPlmnInfo->stDamPlmnList.aucReserved));
    PS_MEM_SET(pstDamCfgPlmnInfo->stImsiPlmnList.aucReserved, 0, sizeof(pstDamCfgPlmnInfo->stImsiPlmnList.aucReserved));

    for (i = 0; i < NAS_MML_SUPPORT_DAM_MAX_PLMN_NUM; i++)
    {
        pstDamCfgPlmnInfo->stDamPlmnList.astPlmnId[i].ulMcc = NAS_MML_INVALID_MCC;
        pstDamCfgPlmnInfo->stDamPlmnList.astPlmnId[i].ulMnc = NAS_MML_INVALID_MNC;
        pstDamCfgPlmnInfo->stImsiPlmnList.astPlmnId[i].ulMcc  = NAS_MML_INVALID_MCC;
        pstDamCfgPlmnInfo->stImsiPlmnList.astPlmnId[i].ulMnc  = NAS_MML_INVALID_MNC;
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetRelPsSigConFlg
 功能描述  : 设置当前是否启用了网络防呆功能
 输入参数  : ucRelPsSigConFlg - 网络防呆功能是打开
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月04日
   作    者   : w0000281933
   修改内容   : 新增

*****************************************************************************/
VOS_VOID NAS_MML_SetRelPsSigConFlg(VOS_UINT8 ucRelPsSigConFlg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRelPsSigConInfo.ucRelPsSigConFlg = ucRelPsSigConFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetRelPsSigConFlg
 功能描述  : 获取当前是否启用了网络防呆功能
 输入参数  :
 输出参数  : 无
 返 回 值  : 网络防呆功能是否开启的FLAG
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月04日
   作    者   : w0000281933
   修改内容   : 新增

*****************************************************************************/
VOS_UINT8 NAS_MML_GetRelPsSigConFlg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRelPsSigConInfo.ucRelPsSigConFlg);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetPdpExistNotStartT3340Flag
 功能描述  : 获取rau或attach请求不带follow on，网络回复attach accept或rau accept
             也不带follow on，存在pdp上下文场景是否需要启动T3340标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年7月17日
   作    者   : z00161729
   修改内容   : DTS2015071505434:rau或attach请求不带follow on，网络回复attach accept或rau accept中携带follow on proceed标识，gmm需要
                增加判断如果ps rab存在或存在rabm重建或sm业务请求或cds存在缓存数据则不启动T3340，否则启动t3340开启网络防呆功能

*****************************************************************************/
VOS_UINT8 NAS_MML_GetPdpExistNotStartT3340Flag(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRelPsSigConInfo.ucPdpExistNotStartT3340Flag);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetPdpExistNotStartT3340Flag
 功能描述  : 设置rau或attach请求不带follow on，网络回复attach accept或rau accept
             也不带follow on，存在pdp上下文场景是否需要启动T3340标识
 输入参数  : ucPdpExistNotStartT3340Flag
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年7月17日
   作    者   : z00161729
   修改内容   : DTS2015071505434:rau或attach请求不带follow on，网络回复attach accept或rau accept中携带follow on proceed标识，gmm需要
                增加判断如果ps rab存在或存在rabm重建或sm业务请求或cds存在缓存数据则不启动T3340，否则启动t3340开启网络防呆功能

*****************************************************************************/
VOS_VOID NAS_MML_SetPdpExistNotStartT3340Flag(VOS_UINT8 ucPdpExistNotStartT3340Flag)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRelPsSigConInfo.ucPdpExistNotStartT3340Flag = ucPdpExistNotStartT3340Flag;
    return;
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetRelPsSigConCfg_T3340TimerLen
 功能描述  : 设置当前启用了网络防呆功能配置的T3340的时长
 输入参数  : ulTimerLen - t3340 时长，单位秒
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月04日
   作    者   : w0000281933
   修改内容   : 新增

*****************************************************************************/
VOS_VOID NAS_MML_SetRelPsSigConCfg_T3340TimerLen(VOS_UINT32 ulTimerLen)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRelPsSigConInfo.ulT3340TimerLen= ulTimerLen;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetRelPsSigConCfg_T3340TimerLen
 功能描述  : 获取当前启用了网络防呆功能配置的T3340 的时长
 输入参数  :
 输出参数  : 无
 返 回 值     : t3340 的时长，单位秒
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月04日
   作    者   : h00285180
   修改内容   : 新增

*****************************************************************************/
VOS_UINT32 NAS_MML_GetRelPsSigConCfg_T3340TimerLen(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stRelPsSigConInfo.ulT3340TimerLen);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetLteRejCause14Flg
 功能描述  : 设置当前是否启用了LTE #14拒绝优化
 输入参数  : ucLteRejCause14Flg - LTE #14拒绝优化是否打开
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年1月05日
   作    者   : h00285180
   修改内容   : 新增

*****************************************************************************/
VOS_VOID NAS_MML_SetLteRejCause14Flg(VOS_UINT8 ucLteRejCause14Flg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucLteRejCause14Flg = ucLteRejCause14Flg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetLteRejCause14Flg
 功能描述  : 获取当前是否启用了LTE #14拒绝优化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : LTE #14拒绝优化是否打开
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年1月05日
   作    者   : h00285180
   修改内容   : 新增

*****************************************************************************/
VOS_UINT8 NAS_MML_GetLteRejCause14Flg(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucLteRejCause14Flg);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetLteRejCause14EnableLteTimerLen
 功能描述  : 设置LTE #14拒绝场景enable lte 定时器时长
 输入参数  : ulEnalbeLteTimeLen - enable lte 定时器时长
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月5日
   作    者   : h00285180
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetLteRejCause14EnableLteTimerLen(
    VOS_UINT32                          ulEnalbeLteTimeLen
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ulLteRejCause14EnableLteTimerLen = ulEnalbeLteTimeLen;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetLteRejCause14EnableLteTimerLen
 功能描述  : 获取LTE #14拒绝场景enable lte 定时器时长
 输入参数  : 无
 输出参数  : 无
 返 回 值  : enable lte 定时器时长
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月5日
   作    者   : h00285180
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MML_GetLteRejCause14EnableLteTimerLen(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ulLteRejCause14EnableLteTimerLen);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetDsdsMultiModemModeFlg
 功能描述  : 设置当前DSDS是否支持信息
 输入参数  : ucDsdsMultiModemModeFlg      : DSDS多Modem是否支持
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月11日
    作    者   : w00167002
    修改内容   : 新生成函数，默认DSDS多Modem不支持

*****************************************************************************/
VOS_VOID  NAS_MML_SetDsdsMultiModemModeFlg(
    VOS_UINT8                           ucDsdsMultiModemModeFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucDsdsMultiModemModeFlg = ucDsdsMultiModemModeFlg;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetDsdsMultiModemModeFlg
 功能描述  : 获取当前DSDS多Modem是否支持信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE: 当前DSDS多Modem支持
             VOS_FALSE:当前DSDS多Modem不支持
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月11日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MML_GetDsdsMultiModemModeFlg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucDsdsMultiModemModeFlg;
}

/* Added by w00167002 for DTS2015091602371 澳电低优先级ANYCELL搜LTE定制, 2015-9-17, begin */
/*****************************************************************************
 函 数 名  : NAS_MML_SetLowPrioAnycellSearchLteFlg
 功能描述  : 设置当前低优先级ANYCELL搜索LTE是否支持信息
 输入参数  : ucLowPrioAnycellSearchLteFlg      : 低优先级ANYCELL搜索LTE是否支持
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月17日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_SetLowPrioAnycellSearchLteFlg(
    VOS_UINT8                           ucLowPrioAnycellSearchLteFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucLowPrioAnycellSearchLteFlg = ucLowPrioAnycellSearchLteFlg;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetLowPrioAnycellSearchLteFlg
 功能描述  : 获取当前低优先级ANYCELL搜索LTE是否支持信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE: 支持当前低优先级ANYCELL搜索LTE
             VOS_FALSE:不支持当前低优先级ANYCELL搜索LTE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月17日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MML_GetLowPrioAnycellSearchLteFlg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucLowPrioAnycellSearchLteFlg;
}
/* Added by w00167002 for DTS2015091602371 澳电低优先级ANYCELL搜LTE定制, 2015-9-17, end */
/*****************************************************************************
 函 数 名  : NAS_MML_SetCsmoSupportedFlg
 功能描述  : 设置当前是否支持CSMO
 输入参数  : ucCsmoSupportedFlg      : 当前CSMO是否支持
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月3日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_SetCsmoSupportedFlg(
    VOS_UINT8                           ucCsmoSupportedFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucCsmoSupportedFlg = ucCsmoSupportedFlg;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetCsmoSupportedFlg
 功能描述  : 获取当前是否支持CSMO
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE: 当前支持CSMO
             VOS_FALSE:当前不支持CSMO
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月3日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MML_GetCsmoSupportedFlg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucCsmoSupportedFlg;
}


/*****************************************************************************
 函 数 名  : NAS_MML_GetT3212TimerInfo
 功能描述  : 获取当前是T3212信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的T3212信息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月15日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
NAS_MML_T3212_TIMER_INFO_CONFIG_STRU* NAS_MML_GetT3212TimerInfo(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stT3212Info);
}


/*****************************************************************************
函 数 名  : NAS_MML_InitT3212TimerInfo
功能描述  : 初始化T3212配置信息
输入参数  : pstT3212CfgInfo - T3212配置网络信息
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2015年3月24日
  作    者   : w00167002
  修改内容   : DTS2015030305199修改
*****************************************************************************/
VOS_VOID  NAS_MML_InitT3212TimerCfgInfo(
    NAS_MML_T3212_TIMER_INFO_CONFIG_STRU                   *pstT3212CfgInfo
)
{
    pstT3212CfgInfo->ulT3212NvActiveFlg             = VOS_FALSE;
    pstT3212CfgInfo->ulT3212StartSceneCtrlBitMask   = 0;
    pstT3212CfgInfo->ulT3212Phase1TimeLen           = 0;
    pstT3212CfgInfo->ulT3212Phase1Count             = 0;
    pstT3212CfgInfo->ulT3212Phase2TimeLen           = 0;
    pstT3212CfgInfo->ulT3212Phase2Count             = 0;

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MML_InitGetGeoPrioRatList
 功能描述  : 初始化获取地理位置信息接入技术优先级列表
 输入参数  : NAS_MML_PLMN_RAT_PRIO_STRU         *pstGetGeoRatList
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月27日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_InitGetGeoPrioRatList(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstGetGeoRatList
)
{
    PS_MEM_SET(pstGetGeoRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* 默认从G模获取地理位置信息 */
    pstGetGeoRatList->ucRatNum             = 1;
    pstGetGeoRatList->aucRatPrio[0]        = NAS_MML_NET_RAT_TYPE_GSM;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetHplmnInEplmnDisplayHomeFlg
 功能描述  : 设置若是EPLMN为HOME，是否显示为非漫游
 输入参数  : ucEplmnIsHomeDisplayHomeFlg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年4月2日
    作    者   : b00269685
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_SetHplmnInEplmnDisplayHomeFlg(
    VOS_UINT8                           ucHplmnInEplmnDisplayHomeFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucHplmnInEplmnDisplayHomeFlg = ucHplmnInEplmnDisplayHomeFlg;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetHplmnInEplmnDisplayHomeFlg
 功能描述  : 获取若是EPLMN为HOME，是否显示为非漫游
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE: 当前判断漫游需要考虑EPLMN
             VOS_FALSE:当前判断漫游不需要考虑EPLMN
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月20日
    作    者   : b00269685
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MML_GetHplmnInEplmnDisplayHomeFlg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucHplmnInEplmnDisplayHomeFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetProtectMtCsfbPagingProcedureLen
 功能描述  : 设置csmt保护时长
 输入参数  : usMtCsfbPagingProcedureLen
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年4月2日
    作    者   : b00269685
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_SetProtectMtCsfbPagingProcedureLen(
    VOS_UINT16                          usMtCsfbPagingProcedureLen
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.usMtCsfbPagingProcedureLen = usMtCsfbPagingProcedureLen;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetProtectMtCsfbPagingProcedureLen
 功能描述  : 获取csmt保护时长
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE: 当前判断漫游需要考虑EPLMN
             VOS_FALSE:当前判断漫游不需要考虑EPLMN
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月4日
    作    者   : b00269685
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT16 NAS_MML_GetProtectMtCsfbPagingProcedureLen(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.usMtCsfbPagingProcedureLen;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetDeleteRplmnWhenEplmnInvalidFlg
 功能描述  : 设置EPLMN无效时候，是否删除RPLMNS
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:只触发一次LAU ,VOS_FALSE:原有流程
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年10月10日
   作    者   : w00167002
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_SetDeleteRplmnWhenEplmnInvalidFlg(
    VOS_UINT8                           ucDeleteRplmnWhenEplmnInvalidFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucDeleteRplmnWhenEplmnInvalidFlg
                                                        = ucDeleteRplmnWhenEplmnInvalidFlg;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetDeleteRplmnWhenEplmnInvalidFlg
 功能描述  : 获取EPLMN无效时候是否删除RPLMN
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:EPLMN无效时候删除RPLMN,
             VOS_FALSE:EPLMN无效时候不删除RPLMN
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年10月10日
   作    者   : w00167002
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MML_GetDeleteRplmnWhenEplmnInvalidFlg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucDeleteRplmnWhenEplmnInvalidFlg;
}


/*****************************************************************************
 函 数 名  : NAS_MML_SetPsRegFailMaxTimesTrigLauOnceFlg
 功能描述  : 设置联合Attach/RAU建链失败达到最大次数是否只触发一次LAU的标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:只触发一次LAU ,VOS_FALSE:原有流程
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年08月13日
   作    者   : l00289540
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_SetPsRegFailMaxTimesTrigLauOnceFlg(VOS_UINT8 ucPsRegFailMaxTimesTrigLauOnceFlg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucPsRegFailMaxTimesTrigLauOnceFlg
                                                        = ucPsRegFailMaxTimesTrigLauOnceFlg;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetPsRegFailMaxTimesTrigLauOnceFlg
 功能描述  : 获取联合Attach/RAU建链失败达到最大次数是否只触发一次LAU的标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:只触发一次LAU ,VOS_FALSE:原有流程
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年08月13日
   作    者   : l00289540
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MML_GetPsRegFailMaxTimesTrigLauOnceFlg(VOS_VOID)
{
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return VOS_FALSE;
    }

    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucPsRegFailMaxTimesTrigLauOnceFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetKeepSrchHplmnEvenRejByCause13Flg
 功能描述  : 设置HPLMN上注册被#13拒之后是否再搜该HPLMN With Rat的标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:继续搜索该HPLMN WITH RAT ,VOS_FALSE:不再搜索当前HPLMN With Rat
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年08月13日
   作    者   : l00289540
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_SetKeepSrchHplmnEvenRejByCause13Flg(VOS_UINT8 ucKeepSrchHplmnEvenRejByCause13Flg)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucKeepSrchHplmnEvenRejByCause13Flg
                                                        = ucKeepSrchHplmnEvenRejByCause13Flg;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetKeepSrchHplmnEvenRejByCause13Flg
 功能描述  : 获取HPLMN上注册被#13拒之后是否再搜该HPLMN With Rat的标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:继续搜索该HPLMN WITH RAT ,VOS_FALSE:不再搜索当前HPLMN With Rat
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年08月13日
   作    者   : l00289540
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MML_GetKeepSrchHplmnEvenRejByCause13Flg(VOS_VOID)
{
    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucKeepSrchHplmnEvenRejByCause13Flg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetEpsRejByCause14InVplmnAllowPsRegFlg
 功能描述  : 设置VPLMN上注册被#14拒之后是否允许在2/3G PS注册的标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年08月13日
   作    者   : l00289540
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_SetEpsRejByCause14InVplmnAllowPsRegFlg(
    VOS_UINT8 ucEpsRejByCause14InVplmnAllowPsRegFlg
)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucEpsRejByCause14InVplmnAllowPsRegFlg
                                                = ucEpsRejByCause14InVplmnAllowPsRegFlg;
    return;
}
/*****************************************************************************
 函 数 名  : NAS_MML_GetEpsRejByCause14InVplmnAllowPsRegFlg
 功能描述  : 获取VPLMN上注册被#14拒之后是否允许在2/3G PS注册的标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:允许注册,VOS_FALSE:不允许注册
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年08月13日
   作    者   : l00289540
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MML_GetEpsRejByCause14InVplmnAllowPsRegFlg(VOS_VOID)
{
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return VOS_FALSE;
    }

    return NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.ucEpsRejByCause14InVplmnAllowPsRegFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetLauRejTrigPlmnSearchCfg
 功能描述  : 获取有业务存在时，LAU被#12拒是否继续触发搜网
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:允许继续搜网,VOS_FALSE:不允许继续搜网
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2015年8月23日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
NAS_MML_LAU_REJ_TRIG_PLMN_SEARCH_STRU* NAS_MML_GetLauRejTrigPlmnSearchCfg(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLauRejTrigPlmnSearchCfg);
}

/*****************************************************************************
 函 数 名  : NAS_MML_InitCarryEplmnWhenSrchRplmnCfg
 功能描述  : 初始化搜索RPLMN时是否需要携带EPLMN的配置
 输入参数  : stCarryEplmnWhenSrchRplmnCfg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月13日
    作    者   : l00289540
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_InitCarryEplmnWhenSrchRplmnCfg(
    NAS_MML_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG_STRU  *pstCarryEplmnWhenSrchRplmnCfg
)
{
    PS_MEM_SET(pstCarryEplmnWhenSrchRplmnCfg, 0x00, sizeof(NAS_MML_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG_STRU));

    pstCarryEplmnWhenSrchRplmnCfg->enSwitchFlag                           = NAS_MML_CARRY_EPLMN_SWITCH_OFF;
    pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneSwitchOn              = VOS_FALSE;
    pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneAreaLost              = VOS_FALSE;
    pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneAvailableTimerExpired = VOS_FALSE;
    pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneCSFBServiceRej        = VOS_FALSE;
    pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneDisableLte            = VOS_FALSE;
    pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneEnableLte             = VOS_FALSE;
    pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneSysCfgSet             = VOS_FALSE;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_InitLauRejNoRetryWhenCmSrvExistCfg
 功能描述  : 初始化如果CM业务存在，LAU被拒时是否需要继续尝试的NV配置
 输入参数  : NAS_MML_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST_CFG_STRU *pstLauRejNoRetryWhenCmSrvExist
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月23日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_InitLauRejNoRetryWhenCmSrvExistCfg(
    NAS_MML_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST_CFG_STRU *pstLauRejNoRetryWhenCmSrvExist
)
{
    PS_MEM_SET(pstLauRejNoRetryWhenCmSrvExist, 0, sizeof(NAS_MML_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST_CFG_STRU));

    pstLauRejNoRetryWhenCmSrvExist->ucLauRejCauseNum    = 0;

    return;
 }


/*****************************************************************************
 函 数 名  : NAS_MML_InitLauRejTrigPlmnSearchCfg
 功能描述  : 初始化注册被拒触发搜网的NV配置
 输入参数  : NAS_MML_LAU_REJ_TRIG_PLMN_SEARCH_STRU                  *pstLauRejTrigPlmnSrchCfg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月6日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_InitLauRejTrigPlmnSearchCfg(
    NAS_MML_LAU_REJ_TRIG_PLMN_SEARCH_STRU                  *pstLauRejTrigPlmnSrchCfg
)
{
    PS_MEM_SET(pstLauRejTrigPlmnSrchCfg, 0x00, sizeof(NAS_MML_LAU_REJ_TRIG_PLMN_SEARCH_STRU));

    pstLauRejTrigPlmnSrchCfg->ucCmSrvExistTrigPlmnSearch    = VOS_FALSE;

    pstLauRejTrigPlmnSrchCfg->ucCmSrvTrigPlmnSearchCauseNum = 0;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetGeoPrioRatList
 功能描述  : 获取获取地理信息接入技术优先级列表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MML_PLMN_RAT_PRIO_STRU*  优先级列表指针
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年05月08日
   作    者   : sunjitan 00193151
   修改内容   : 新生成函数
*****************************************************************************/
NAS_MML_PLMN_RAT_PRIO_STRU* NAS_MML_GetGeoPrioRatList(VOS_VOID)
{
    return &(g_stNasMmlCtx.stMsCfgInfo.stCustomCfg.stGetGeoPrioRatList);
}

/*****************************************************************************
 函 数 名  : NAS_MML_InitOriginalRejectCause
 功能描述  : 开机初始化网络侧发起的拒绝原因值
 输入参数  : pstOriginalRejectCause:网络原始拒绝原因值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年4月28日
   作    者   : g00322017
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_InitOriginalRejectCause(
    NAS_MML_ORIGNAL_REJECT_CAUSE_STRU   *pstOriginalRejectCause
)
{
    pstOriginalRejectCause->ucOriginalRejectCause = NAS_MML_REG_FAIL_CAUSE_NULL;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetOriginalRejectCause
 功能描述  : 设置OriginalRejectCause，用于rejinfo at命令上报
 输入参数  : ucOriginalUeCause
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年4月25日
    作    者   : g00322017
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_SetOriginalRejectCause(
    VOS_UINT8                           ucOriginalUeCause
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stOriginalRejectCause.ucOriginalRejectCause = ucOriginalUeCause;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetOriginalRejectCause
 功能描述  : 获得OriginalRejectCause，用于rejinfo at命令上报
 输入参数  : ucEplmnIsHomeDisplayHomeFlg
 输出参数  : 无
 返 回 值  : 网络侧原始拒绝原因值
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年4月25日
    作    者   : g00322017
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8  NAS_MML_GetOriginalRejectCause(VOS_UINT32 UlAdaptCause)
{
    if(UlAdaptCause > 255 || UlAdaptCause < 1)
    {
        return NAS_MML_REG_FAIL_CAUSE_NULL;
    }
    return NAS_MML_GetMmlCtx()->stNetworkInfo.stOriginalRejectCause.ucOriginalRejectCause;
}

/* Added by c00318887 for file refresh需要触发背景搜, 2015-4-28, begin */

/*****************************************************************************
 函 数 名  : NAS_MML_GetHighPrioPlmnRefreshTriggerBGSearchFlag
 功能描述  : 获取高优先级网络文件更新时是否触发背景搜标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月28日
    作    者   : c00318887
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetHighPrioPlmnRefreshTriggerBGSearchFlag(VOS_VOID)
{
    return (NAS_MML_GetBgSearchCfg()->stHighPrioPlmnRefreshTriggerBGSearchCfg.ucTriggerBGSearchFlag);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetHighPrioPlmnRefreshTriggerBGSearchDelayLen
 功能描述  : 获取高优先级网络文件更新时触发背景搜的定时器时长 单位:ms
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月28日
    作    者   : c00318887
    修改内容   : 新生成函数

*****************************************************************************/

VOS_UINT32 NAS_MML_GetHighPrioPlmnRefreshTriggerBGSearchDelayLen(VOS_VOID)
{
    return (NAS_MML_GetBgSearchCfg()->stHighPrioPlmnRefreshTriggerBGSearchCfg.ulSearchDelayLen);
}

/*****************************************************************************
函 数 名  : NAS_MML_InitHighPrioPlmnRefreshTriggerBGSearchCfgInfo
功能描述  : 初始化高优先级网络更新触发背景搜配置信息
输入参数  : 无
输出参数  : pstHighPrioPlmnRefreshTriggerBGSearchCfg - 高优先级网络更新触发背景搜配置信息
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期  : 2015年4月28日
 作    者   : c00318887
 修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MML_InitHighPrioPlmnRefreshTriggerBGSearchCfgInfo(
    NAS_MML_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_CFG_STRU             *pstHighPrioPlmnRefreshTriggerBGSearchCfg
)
{
    pstHighPrioPlmnRefreshTriggerBGSearchCfg->ucTriggerBGSearchFlag   = 0;
    pstHighPrioPlmnRefreshTriggerBGSearchCfg->ulSearchDelayLen        = 0;
    PS_MEM_SET(pstHighPrioPlmnRefreshTriggerBGSearchCfg->aucReserve, 0x0, sizeof(pstHighPrioPlmnRefreshTriggerBGSearchCfg->aucReserve));
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetHighPrioPlmnRefreshTriggerBGSearchFlag
 功能描述  : 设置高优先级网络文件更新时是否触发背景搜标识
 输入参数  : ucTriggerBGSearchFlag
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月28日
    作    者   : c00318887
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetHighPrioPlmnRefreshTriggerBGSearchFlag(VOS_UINT8 ucTriggerBGSearchFlag)
{
    NAS_MML_GetBgSearchCfg()->stHighPrioPlmnRefreshTriggerBGSearchCfg.ucTriggerBGSearchFlag = ucTriggerBGSearchFlag;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetHighPrioPlmnRefreshTriggerBGSearchDelayLen
 功能描述  : 获取高优先级网络文件更新时触发背景搜的定时器时长 单位:ms
 输入参数  : ulSearchDelayLen
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月28日
    作    者   : c00318887
    修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID NAS_MML_SetHighPrioPlmnRefreshTriggerBGSearchDelayLen(VOS_UINT32 ulSearchDelayLen)
{
    NAS_MML_GetBgSearchCfg()->stHighPrioPlmnRefreshTriggerBGSearchCfg.ulSearchDelayLen = ulSearchDelayLen;
}



/* Added by c00318887 for file refresh需要触发背景搜, 2015-4-28, end */


/* Added by c00318887 for 移植T3402 , 2015-6-17, begin */
/*****************************************************************************
 函 数 名  : NAS_MML_SetDisableLteStartT3402EnableLteFlag
 功能描述  : 设置DiableLteStartT3402EnableLteFlg
 输入参数  : ucT3402Flag  1: 使用LMM_MMC_T3402_LEN_NOTIFY消息中的长度，0: 不使用LMM_MMC_T3402_LEN_NOTIFY消息中的长度
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月17日
    作    者   : c00318887
    修改内容   : 移植T3402

*****************************************************************************/
VOS_VOID NAS_MML_SetDisableLteStartT3402EnableLteFlag(VOS_UINT8 ucT3402Flag)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucDiableLteStartT3402EnableLteFlg = ucT3402Flag;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetDisableLteStartT3402EnableLteFlag
 功能描述  : 获取DiableLteStartT3402EnableLteFlg
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 1: 使用LMM_MMC_T3402_LEN_NOTIFY消息中的长度，0: 不使用LMM_MMC_T3402_LEN_NOTIFY消息中的长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月17日
    作    者   : c00318887
    修改内容   : 移植T3402

*****************************************************************************/
VOS_UINT8 NAS_MML_GetDisableLteStartT3402EnableLteFlag(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.ucDiableLteStartT3402EnableLteFlg);
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetHighPrioRatBgEnableLteFlag
 功能描述  : 设置高优先级RAT定时器超时是否ENABLE LTE 
 输入参数  : enHighPrioRatTimerNotEnableLteFlag  0:高优先级RAT定时器超时不重新ENABLE lte；1: 高优先级RAT定时器超时重新enable LTE
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月17日
    作    者   : c00318887
    修改内容   : 移植T3402

*****************************************************************************/
VOS_VOID NAS_MML_SetHighPrioRatBgEnableLteFlag(NAS_MML_HIGH_PRIO_RAT_BG_SEARCH_PROC_LTE_ENUM_UINT8 enHighPrioRatTimerNotEnableLteFlag)
{
    NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.enHighPrioRatTimerNotEnableLteFlag = enHighPrioRatTimerNotEnableLteFlag;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetHighPrioRatBgEnableLteFlag
 功能描述  : 获取搜网时是否ENABLE LTE 标示
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 0:搜网时重新ENABLE lte；1: 搜网时不重新enable LTE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月17日
    作    者   : c00318887
    修改内容   : 移植T3402

*****************************************************************************/
NAS_MML_HIGH_PRIO_RAT_BG_SEARCH_PROC_LTE_ENUM_UINT8 NAS_MML_GetHighPrioRatBgEnableLteFlag(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteCustomCfgInfo.enHighPrioRatTimerNotEnableLteFlag);
}
/* Added by c00318887 for 移植T3402 , 2015-6-17, end */

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MML_InitLteOos2GPrefPlmnSelCfg
 功能描述  : 初始化Lte OOS选网优化配置信息
 输入参数  : Lte OOS选网优化配置信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年7月3日
   作    者   : h00285180
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_InitLteOos2GPrefPlmnSelCfg(NAS_MML_LTE_OOS_2G_PREF_PLMN_SEL_CFG_STRU *pstLteOos2GPrefPlmnSelCfg)
{
    VOS_UINT32                          i;

    pstLteOos2GPrefPlmnSelCfg->ucImsiListNum = 0;

    for (i = 0; i < NAS_MML_LTE_OOS_2G_PREF_PLMN_SEL_MAX_IMSI_LIST_NUM; i++)
    {
       pstLteOos2GPrefPlmnSelCfg->astImsiList[i].ulMcc = NAS_MML_INVALID_MCC;
       pstLteOos2GPrefPlmnSelCfg->astImsiList[i].ulMnc = NAS_MML_INVALID_MNC;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetLteOos2GPrefPlmnSelCfg
 功能描述  : 获取MML中保存LTE OOS选网优化配置信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存LTE OOS选网优化配置信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年7月03日
   作    者   : h00285180
   修改内容   : 新生成函数
*****************************************************************************/

NAS_MML_LTE_OOS_2G_PREF_PLMN_SEL_CFG_STRU* NAS_MML_GetLteOos2GPrefPlmnSelCfg(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMsCfgInfo.stCustomCfg.stLteOos2GPrefPlmnSelCfg);
}
#endif


/*****************************************************************************
 函 数 名  : NAS_MML_GetRatIndexInPrioRatList
 功能描述  : 获取某个网络接入技术在接入技术列表里的索引
 输入参数  : ucNetRat           -- 网络接入技术
             pstPrioRatList     -- 接入技术列表
 输出参数  : 无
 返 回 值  : 某个网络接入技术在接入技术列表里的索引
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月06日
    作    者   : c00318887
    修改内容   : 新生成函数　DTS2015041401965，syscfg设置只在增加接入技术且新增接入技术优先级高于当前接入技术才触发搜网

*****************************************************************************/
VOS_UINT32 NAS_MML_GetRatIndexInPrioRatList(
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8         ucNetRat,
    NAS_MSCC_PIF_RAT_PRIO_STRU                  *pstPrioRatList
)
{
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8    *pstRatPrio         = VOS_NULL_PTR;           /* 接入优先级里列表 index表示优先级次序,0最高，2最低 */
    VOS_UINT8                                ucRatNum;                                    /* 接入技术个数  */
    VOS_UINT32                               ulRatIndex;

    ucRatNum                            = pstPrioRatList->ucRatNum;
    pstRatPrio                          = pstPrioRatList->aucRatPrio;

    for (ulRatIndex = 0; ulRatIndex < ucRatNum; ulRatIndex++)
    {
        if (ucNetRat == pstRatPrio[ulRatIndex])
        {
            return ulRatIndex;
        }
    }

    return NAS_MML_INVALID_INDEX;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetErrLogFftSrchInfoAddr
 功能描述  : 获取FFT搜索MCC的CHR信息地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MML_ERRLOG_FFT_SRCH_INFO_STRU*
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年10月30日
   作    者   : h00279575
   修改内容   : 新生成函数
*****************************************************************************/
NAS_MML_ERRLOG_FFT_SRCH_INFO_STRU* NAS_MML_GetErrLogFftSrchInfoAddr(VOS_VOID)
{
    return &(NAS_MML_GetMmlCtx()->stMaintainInfo.stErrLogMntnInfo.stFftSrchInfo);
}
/*****************************************************************************
 函 数 名  : NAS_MML_InitErrLogFftSrchInfo
 功能描述  : 初始化FFT搜索MCC结果统计CHR信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年10月30日
   作    者   : h00279575
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_InitErrLogFftSrchInfo(VOS_VOID)
{
    NAS_MML_ERRLOG_FFT_SRCH_INFO_STRU  *pstFftrchInfo = VOS_NULL_PTR;

    pstFftrchInfo = NAS_MML_GetErrLogFftSrchInfoAddr();

    PS_MEM_SET(pstFftrchInfo, 0x0, sizeof(NAS_MML_ERRLOG_FFT_SRCH_INFO_STRU));

    pstFftrchInfo->enMccRatType      = NAS_MSCC_PIF_NET_RAT_TYPE_BUTT;

    /* 初始化 Band Scan结构体 */
    pstFftrchInfo->stCssBandScanInfo.enResult              = CSS_MULTI_BAND_SCAN_RESULT_FAIL_BUTT;
    pstFftrchInfo->stCssBandScanInfo.enGsmCoverageType     = CSS_COVERAGE_TYPE_BUTT;
    pstFftrchInfo->stCssBandScanInfo.enLteCoverageType     = CSS_COVERAGE_TYPE_BUTT;
    pstFftrchInfo->stCssBandScanInfo.enUmtsFddCoverageType = CSS_COVERAGE_TYPE_BUTT;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetFftSrchStartTime
 功能描述  : 记录FFT搜索MCC过程的开始时间点
 输入参数  : VOS_UINT32
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年10月30日
   作    者   : h00279575
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_SetFftSrchStartTime(VOS_UINT32 ulFftStartSlice)
{
    NAS_TRACE_HIGH("NAS_MML_SetFftSrchStartTime: Start slice:%u", ulFftStartSlice);

    NAS_MML_GetMmlCtx()->stMaintainInfo.stErrLogMntnInfo.stFftSrchInfo.ulSrchStartSlice
                                                                       = ulFftStartSlice;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetFftSrchBandScanStartTime
 功能描述  : 记录FFT搜索MCC过程之BAND SCAN的开始时间点
 输入参数  : VOS_UINT32
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年10月30日
   作    者   : h00279575
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_SetFftSrchBandScanStartTime(
    VOS_UINT32                           ulBandScanStartSlice
)
{
    NAS_TRACE_HIGH("NAS_MML_SetFftSrchBandScanStartTime: Start slice:%u", ulBandScanStartSlice);

    NAS_MML_GetMmlCtx()->stMaintainInfo.stErrLogMntnInfo.stFftSrchInfo.stCssBandScanInfo.ulBandScanStartSlice
                                                                                    = ulBandScanStartSlice;

    return;
}
/*****************************************************************************
 函 数 名  : NAS_MML_SaveFftSrchBandScanResultAndFinishTime
 功能描述  : 记录FFT搜索MCC过程之BAND SCAN的结束时间点和结果
 输入参数  : CSS_MULTI_BAND_SCAN_CNF_STRU*
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年10月30日
   作    者   : h00279575
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_SaveFftSrchBandScanResultAndFinishTime(
    CSS_MULTI_BAND_SCAN_CNF_STRU         *pstBandScanCnf
)
{
    NAS_MML_ERRLOG_FFT_BAND_SCAN_INFO_STRU *pstBandScanInfo = VOS_NULL_PTR;

    pstBandScanInfo = &(NAS_MML_GetErrLogFftSrchInfoAddr()->stCssBandScanInfo);
    pstBandScanInfo->ulBandScanFinishSlice = VOS_GetSlice();

    if (VOS_NULL_PTR == pstBandScanCnf)
    {
        /* 没有扫频结果，记录为默认值 */
        pstBandScanInfo->enResult               = CSS_MULTI_BAND_SCAN_RESULT_FAIL_BUTT;
        pstBandScanInfo->enGsmCoverageType      = CSS_COVERAGE_TYPE_BUTT;
        pstBandScanInfo->enLteCoverageType      = CSS_COVERAGE_TYPE_BUTT;
        pstBandScanInfo->enUmtsFddCoverageType  = CSS_COVERAGE_TYPE_BUTT;
    }
    else
    {
        pstBandScanInfo->enResult               = pstBandScanCnf->enResult;
        pstBandScanInfo->enGsmCoverageType      = pstBandScanCnf->enGsmCoverageType;
        pstBandScanInfo->enLteCoverageType      = pstBandScanCnf->enLteCoverageType;
        pstBandScanInfo->enUmtsFddCoverageType  = pstBandScanCnf->enUmtsFddCoverageType;

    }

    NAS_TRACE_HIGH("NAS_MML_SaveFftSrchBandScanResultAndFinishTime: result=%u, Coverage: G=%u, U=%u, L=%u",
                pstBandScanInfo->enResult,
                pstBandScanInfo->enGsmCoverageType,
                pstBandScanInfo->enUmtsFddCoverageType,
                pstBandScanInfo->enLteCoverageType);
    return;
}
/*****************************************************************************
 函 数 名  : NAS_MML_SetFftSrchPlmnSrchRatType
 功能描述  : 记录FFT搜索MCC过程之PLMN SEARCH的网络接入制式
 输入参数  : NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年10月30日
   作    者   : h00279575
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_SetFftSrchPlmnSrchRatType(
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8 enRatType
)
{
    NAS_TRACE_HIGH("NAS_MML_SetFftSrchPlmnSrchRatType: rat=%u", enRatType);

    NAS_MML_GetMmlCtx()->stMaintainInfo.stErrLogMntnInfo.stFftSrchInfo.enMccRatType = enRatType;

    return;
}
/*****************************************************************************
 函 数 名  : NAS_MML_SaveFftSrchResultAndFinishTime
 功能描述  : 记录FFT搜索MCC的结束时间点和结果
 输入参数  : VOS_UINT8
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年10月30日
   作    者   : h00279575
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MML_SaveFftSrchResultAndFinishTime(
    VOS_UINT8                            ucResult
)
{
    NAS_MML_ERRLOG_FFT_SRCH_INFO_STRU *pstGetGeoSrchLogInfo = VOS_NULL_PTR;

    pstGetGeoSrchLogInfo                    = NAS_MML_GetErrLogFftSrchInfoAddr();
    pstGetGeoSrchLogInfo->ulSrchFinishSlice = VOS_GetSlice();
    pstGetGeoSrchLogInfo->ucSrchRslt        = ucResult;

    NAS_TRACE_HIGH("NAS_MML_SaveFftSrchResultAndFinishTime: result=%u, rat=%u,time: Begin=%u -> End=%u ",
                pstGetGeoSrchLogInfo->ucSrchRslt,
                pstGetGeoSrchLogInfo->enMccRatType,
                pstGetGeoSrchLogInfo->ulSrchStartSlice,
                pstGetGeoSrchLogInfo->ulSrchFinishSlice);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetCsmoStatus
 功能描述  : 设置小区是否支持CSMO状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2016年1月8日
   作    者   : z00359541
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetCellNotSupportCsmoFlg(
    VOS_UINT8                           ucCellNotSupportCsmoFlg
)
{
    (NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stCmSrvStatus.ucCellNotSupportCsmoFlg) = ucCellNotSupportCsmoFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetCellNotSupportCsmoFlg
 功能描述  : 获取小区是否支持CSMO状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 小区是否支持CSMO状态
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2016年1月8日
   作    者   : z00359541
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MML_GetCellNotSupportCsmoFlg( VOS_VOID )
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stCmSrvStatus.ucCellNotSupportCsmoFlg);
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetCsMoSessionSndFlag
 功能描述  : 获取CS域的Sessio是否已经发送过
 输入参数  : NAS_MML_SESSION_TYPE_ENUM_UINT8
 输出参数  : 无
 返 回 值  : PS_BOOL_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2016年1月25日
   作    者   : j00174725
   修改内容   : 新生成函数

*****************************************************************************/
PS_BOOL_ENUM_UINT8 NAS_MML_GetCsMoSessionSndFlag(
    NAS_MML_SESSION_TYPE_ENUM_UINT8     enSessionType
)
{
    PS_BOOL_ENUM_UINT8                  enSessionFlag = VOS_FALSE;

    switch(enSessionType)
    {
        case NAS_MML_SESSION_TYPE_CS_MO_NORMAL_CALL:
            enSessionFlag = NAS_MML_GetMmlCtx()->stCsMoSessionManager.enCsMoNornalCallFlag;
            break;

        case NAS_MML_SESSION_TYPE_CS_MO_EMERGENCY_CALL:
            enSessionFlag = NAS_MML_GetMmlCtx()->stCsMoSessionManager.enCsMoEmergencyCallFlag;
            break;

        case NAS_MML_SESSION_TYPE_CS_MO_SS:
            enSessionFlag = NAS_MML_GetMmlCtx()->stCsMoSessionManager.enCsMoSsFlag;
            break;

        case NAS_MML_SESSION_TYPE_CS_MO_SMS:
            enSessionFlag = NAS_MML_GetMmlCtx()->stCsMoSessionManager.enCsMoSmsFlag;
            break;

        default:
            break;
    }

    return enSessionFlag;
}

/*****************************************************************************
 函 数 名  : NAS_MML_SetCsMoSessionSndFlag
 功能描述  : 设置CS域的Sessio是否已经发送过
 输入参数  : NAS_MML_SESSION_TYPE_ENUM_UINT8
             PS_BOOL_ENUM_UINT8
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2016年1月25日
   作    者   : j00174725
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MML_SetCsMoSessionSndFlag(
    NAS_MML_SESSION_TYPE_ENUM_UINT8     enSessionType,
    PS_BOOL_ENUM_UINT8                  enFlag
)
{
    switch(enSessionType)
    {
        case NAS_MML_SESSION_TYPE_CS_MO_NORMAL_CALL:
            NAS_MML_GetMmlCtx()->stCsMoSessionManager.enCsMoNornalCallFlag = enFlag;
            break;

        case NAS_MML_SESSION_TYPE_CS_MO_EMERGENCY_CALL:
            NAS_MML_GetMmlCtx()->stCsMoSessionManager.enCsMoEmergencyCallFlag = enFlag;
            break;

        case NAS_MML_SESSION_TYPE_CS_MO_SS:
            NAS_MML_GetMmlCtx()->stCsMoSessionManager.enCsMoSsFlag = enFlag;
            break;

        case NAS_MML_SESSION_TYPE_CS_MO_SMS:
            NAS_MML_GetMmlCtx()->stCsMoSessionManager.enCsMoSmsFlag = enFlag;
            break;

        default:
            break;
    }

    return;
}



/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

