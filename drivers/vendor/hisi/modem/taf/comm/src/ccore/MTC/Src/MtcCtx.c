/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MtcCtx.c
  版 本 号   : 初稿
  作    者   : l60609
  生成日期   : 2013年07月30日
  最近修改   :
  功能描述   : MTC模块的上下文管理
  函数列表   :
  修改历史   :
  1.日    期   : 2013年7月30日
    作    者   : l60609
    修改内容   : 新生成

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "MtcCtx.h"
#include "MtcDebug.h"
#include "TafNvInterface.h"
#include "NasNvInterface.h"
#include "NVIM_Interface.h"
#include "MtcRfLcdIntrusion.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

/*lint -e767 修改人: l00198894; */
#define    THIS_FILE_ID        PS_FILE_ID_MTC_CTX_C
/*lint +e767 修改人: l00198894; */

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
MTC_CONTEXT_STRU                        g_stMtcCtx;


/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*****************************************************************************
 函 数 名  : MTC_GetCtxAddr
 功能描述  : 获取MTC上下文地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MTC_CONTEXT_STRU* MTC上下文地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月13日
    作    者   : j00174725
    修改内容   : V9R1 干扰控制项目
*****************************************************************************/
MTC_CONTEXT_STRU* MTC_GetCtxAddr(VOS_VOID)
{
    return &g_stMtcCtx;
}

/*****************************************************************************
 函 数 名  : MTC_GetIntrusionCtxAddr
 功能描述  : 获取频段冲突上下文地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MTC_INTRUSION_CTX_STRU* 频段冲突上下文地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月13日
    作    者   : j00174725
    修改内容   : V9R1 干扰控制项目
*****************************************************************************/
MTC_INTRUSION_CTX_STRU* MTC_GetIntrusionCtxAddr(VOS_VOID)
{
    return &(MTC_GetCtxAddr()->stIntrusionCtx);
}

/*****************************************************************************
 函 数 名  : MTC_GetModemCtxAddr
 功能描述  : 获取MTC MODEM信息上下文地址
 输入参数  : 内部接口，enModemId 由调用者保证modemId的有效性
 输出参数  : 无
 返 回 值  : MTC_MODEM_INFO_STRU* MODEM信息上下文地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月13日
    作    者   : j00174725
    修改内容   : V9R1 干扰控制项目
*****************************************************************************/
MTC_MODEM_INFO_STRU* MTC_GetModemCtxAddr(MODEM_ID_ENUM_UINT16 enModemId)
{
    return &(MTC_GetCtxAddr()->astModemInfo[enModemId]);
}

/*****************************************************************************
 函 数 名  : MTC_InitIntrusionCtx
 功能描述  : 初始化频段冲突相关上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月13日
    作    者   : j00174725
    修改内容   : V9R1 干扰控制项目

  2.日    期   : 2013年12月21日
    作    者   : l00198894
    修改内容   : V9R1 Notch Bypass项目

  3.日    期   : 2014年3月24日
    作    者   : A00165503
    修改内容   : B39&B32 Intrusion
*****************************************************************************/
VOS_VOID MTC_InitIntrusionCtx(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    MTC_INTRUSION_CTX_STRU             *pstMtcIntrusionCtx = VOS_NULL_PTR;

    pstMtcIntrusionCtx = MTC_GetIntrusionCtxAddr();

    /* 初始化上下文 */
    PS_MEM_SET(pstMtcIntrusionCtx, 0, sizeof(MTC_INTRUSION_CTX_STRU));

    /* 读取NV项 */
    ulRet = NV_Read(en_NV_Item_RF_INTRUSION_CFG,
                    &pstMtcIntrusionCtx->stIntrusionCfg,
                    sizeof(MTC_NV_RF_INTRUSION_CFG_STRU));
    if (VOS_OK != ulRet)
    {
        MTC_WARNING_LOG("MTC_InitIntrusionCtx: Read Nv Fail.");
    }

    /* Added by l00198894 for V9R1 Notch Bypass项目, 2013-12-21, begin */
    MTC_SetNotchEnalbeFlag(PS_FALSE);
    /* Added by l00198894 for V9R1 Notch Bypass项目, 2013-12-21, end */

    MTC_SetNarrowDcsEnalbeFlag(PS_FALSE);

    MTC_SetTlRfCtrlEnalbeFlag(PS_FALSE);

    MTC_SetRseCfgValue(PS_FALSE);

    return;
}

/*****************************************************************************
 函 数 名  : MTC_InitPsTransferCtx
 功能描述  : 初始化PS域迁移相关上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年01月17日
    作    者   : l00198894
    修改内容   : V9R1C53 C+L 离网重选项目
*****************************************************************************/
VOS_VOID MTC_InitPsTransferCtx(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    MTC_PS_TRANSFER_CTX_STRU           *pstPsTransferCtx = VOS_NULL_PTR;

    pstPsTransferCtx = MTC_GetPsTransferCtxAddr();

    /* 初始化上下文 */
    PS_MEM_SET(pstPsTransferCtx, 0, sizeof(MTC_PS_TRANSFER_CTX_STRU));

    /* Added by Y00213812 for 主动离网重选, 2014-04-10, begin */
    /* 初始化PSTRANSFER的上报状态值 */
    pstPsTransferCtx->enReportCause     = MTC_PS_TRANSFER_CAUSE_BUTT;
    pstPsTransferCtx->enRrcCause        = MTC_PS_TRANSFER_CAUSE_BUTT;
    /* Added by Y00213812 for 主动离网重选, 2014-04-10, begin */

    /* 读取NV项 */
    ulRet = NV_Read(en_NV_Item_PS_TRANSFER_CFG,
                    &pstPsTransferCtx->stPsTransferCfg,
                    sizeof(MTC_NV_PS_TRANSFER_CFG_STRU));
    if (VOS_OK != ulRet)
    {
        MTC_WARNING_LOG("MTC_InitPsTransferCtx: Read Nv Fail.");
    }

    return;
}

/*****************************************************************************
 函 数 名  : MTC_InitOperatorCustSolution
 功能描述  : 初始化运营商
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年01月17日
    作    者   : l00198894
    修改内容   : V9R1C53 C+L 离网重选项目
*****************************************************************************/
VOS_VOID MTC_InitOperatorCustSolution(VOS_VOID)
{
    SVLTE_SUPPORT_FLAG_STRU             stSvlteSupportFlag;
    TAF_NV_LC_CTRL_PARA_STRU            stLcCtrlPara;

    PS_MEM_SET(&stSvlteSupportFlag, 0x00, sizeof(stSvlteSupportFlag));
    PS_MEM_SET(&stLcCtrlPara, 0x00, sizeof(stLcCtrlPara));

    /* 读SVLTE特性NV */
    if (NV_OK != NV_Read(en_NV_Item_SVLTE_FLAG,
                         &stSvlteSupportFlag,
                         sizeof(SVLTE_SUPPORT_FLAG_STRU)))
    {
        MTC_ERROR_LOG("MTC_InitOperatorCustSolution(): en_NV_Item_SVLTE_FLAG error");
        stSvlteSupportFlag.ucSvlteSupportFlag = VOS_FALSE;
    }

    /* 读LC特性NV */
    if (NV_OK != NV_Read(en_NV_Item_LC_Ctrl_PARA,
                         &stLcCtrlPara,
                         sizeof(TAF_NV_LC_CTRL_PARA_STRU)))
    {
        MTC_ERROR_LOG("MTC_InitOperatorCustSolution(): en_NV_Item_LC_Ctrl_PARA error");
        stLcCtrlPara.ucLCEnableFlg = VOS_FALSE;
    }

    if (VOS_TRUE == stSvlteSupportFlag.ucSvlteSupportFlag)
    {
        MTC_SetOperatorCustSolution(MTC_OPERATOR_CUST_CMCC_SVLTE);
    }
    else if (VOS_TRUE == stLcCtrlPara.ucLCEnableFlg)
    {
        MTC_SetOperatorCustSolution(MTC_OPERATOR_CUST_CT_LC);
    }
    else
    {
        MTC_SetOperatorCustSolution(MTC_OPERATOR_CUST_NONE);
    }

    return;
}

/*****************************************************************************
 函 数 名  : MTC_ParsePlatFormRat
 功能描述  : 解析接入技术
 输入参数  : pucRat  --MTC保存接入技术
 输出参数  : pstPlatFormRat  -- NV中的接入能力
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月12日
    作    者   : j00174725
    修改内容  : V9R1 干扰控制项目
*****************************************************************************/
VOS_VOID MTC_ParsePlatFormRat(
    VOS_UINT8                          *pucRat,
    PLATAFORM_RAT_CAPABILITY_STRU      *pstPlatFormRat
)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT16                          usRatNum;

    usRatNum = pstPlatFormRat->usRatNum;
    *pucRat  = 0;

    /* 将对应bit设置为1 */
    for (ulIndex = 0; ulIndex < usRatNum; ulIndex++)
    {
        if (pstPlatFormRat->aenRatList[ulIndex] >= PLATFORM_RAT_BUTT)
        {
            return;
        }

        *pucRat |= (VOS_UINT8)MTC_SET_BIT(pstPlatFormRat->aenRatList[ulIndex]);
    }

    return;
}

/*****************************************************************************
 函 数 名  : MTC_IsSupportRatType
 功能描述  : MODEM是否支持该接入技术
 输入参数  : enRatMode  -- 接入技术
 输出参数  : 无
 返 回 值  : VOS_TRUE   -- 支持该接入技术
              VOS_FALSE  -- 不支持该接入技术
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月13日
    作    者   : j00174725
    修改内容   : V9R1 干扰控制项目
*****************************************************************************/
VOS_UINT32 MTC_IsSupportRatType(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_RATMODE_ENUM_UINT8              enRatMode
)
{
    if (enRatMode >= MTC_RATMODE_BUTT)
    {
        return VOS_FALSE;
    }

    /* 判断modemId是否有效 */
    if (enModemId >= MODEM_ID_BUTT)
    {
        return VOS_FALSE;
    }

    if (0 != (MTC_GetModemCtxAddr(enModemId)->ucRatCap & MTC_SET_BIT(enRatMode)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}

/*****************************************************************************
 函 数 名  : MTC_ResetModemInfo
 功能描述  : 复位MTC模块中MODEM信息
 输入参数  : enModemId   --modemID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月13日
    作    者   : j00174725
    修改内容   : V9R1 干扰控制项目

  2.日    期   : 2014年3月24日
    作    者   : A00165503
    修改内容   : B39&B32 Intrusion

  3.日    期   : 2014年11月17日
    作    者   : l00198894
    修改内容   : ECID命令产品线定制需求
*****************************************************************************/
VOS_VOID MTC_ResetModemInfo(MODEM_ID_ENUM_UINT16 enModemId)
{
    MTC_MODEM_INFO_STRU                *pstModemInfo = VOS_NULL_PTR;

    pstModemInfo = MTC_GetModemCtxAddr(enModemId);

    PS_MEM_SET(&pstModemInfo->stSerCellBandInfo, 0, sizeof(RRC_MTC_MS_BAND_INFO_STRU));
    PS_MEM_SET(&pstModemInfo->stCurBandInfo, 0, sizeof(RRC_MTC_MS_BAND_INFO_STRU));
    PS_MEM_SET(&pstModemInfo->stSrvInfo, 0, sizeof(MTC_MODEM_SERVICE_INFO_STRU));
    pstModemInfo->enRatMode = MTC_RATMODE_BUTT;

    /* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
    PS_MEM_SET(&pstModemInfo->stConnStateInfo, 0, sizeof(MTC_MODEM_CONN_STATE_INFO_STRU));
    /* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, End */

    PS_MEM_SET(&pstModemInfo->stGsmCellInfoEx, 0, sizeof(MTC_GSM_CELLINFO_EX_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : MTC_InitModemCtx
 功能描述  : 初始MTC模块中MODEM信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月13日
    作    者   : j00174725
    修改内容   : V9R1 干扰控制项目

  2.日    期   : 2015年11月3日
    作    者   : h00313353
    修改内容   : Iteration 19
*****************************************************************************/
VOS_VOID MTC_InitModemCtx(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usIndex;

    PLATAFORM_RAT_CAPABILITY_STRU       stModemPlatFormRat;
    MTC_MODEM_INFO_STRU                *pastModemCtxAddr    = VOS_NULL_PTR;
    MTC_OUTSIDE_MODEM_INFO_STRU        *pstOutModemCtxAddr  = VOS_NULL_PTR;

    for (usIndex = 0; usIndex < MODEM_ID_BUTT; usIndex++)
    {
        PS_MEM_SET(&stModemPlatFormRat, 0, sizeof(stModemPlatFormRat));

        /* 获取Modem上下文 地址 */
        pastModemCtxAddr = MTC_GetModemCtxAddr(usIndex);

        PS_MEM_SET(pastModemCtxAddr, 0, sizeof(MTC_MODEM_INFO_STRU));

        PS_MEM_SET(&(pastModemCtxAddr->stRatCfg), 0xFF, sizeof(MTC_MODEM_RAT_CONFIG_STRU));

        pastModemCtxAddr->enCsimState   = TAF_MTC_USIMM_CARD_SERVIC_BUTT;
        pastModemCtxAddr->enUsimState   = TAF_MTC_USIMM_CARD_SERVIC_BUTT;

        /* 读取Modem当前接入技术nv项 */
        ulRet = NV_ReadEx(usIndex,
                          en_NV_Item_Platform_RAT_CAP,
                          &stModemPlatFormRat,
                          sizeof(PLATAFORM_RAT_CAPABILITY_STRU));
        if (VOS_OK != ulRet)
        {
            MTC_WARNING_LOG("MTC_InitIntrusionCtx: Read Nv Fail.");
            continue;
        }

        MTC_ParsePlatFormRat(&(pastModemCtxAddr->ucRatCap), &stModemPlatFormRat);

        pastModemCtxAddr->enRatMode = MTC_RATMODE_BUTT;
    }

    /* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
    /* 初始化外部modem上下文件信息 */
    for (usIndex = MTC_OUTSIDE_MODEM_CDMA; usIndex < MTC_OUTSIDE_MODEM_BUTT; usIndex++ )
    {
        pstOutModemCtxAddr =  MTC_GetOutSideModemCtxAddr(usIndex);

        PS_MEM_SET(pstOutModemCtxAddr, 0x0, sizeof(MTC_OUTSIDE_MODEM_INFO_STRU));
    }

    /* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, End */

    /* 初始化CDMA Modem Id */
    MTC_GetCtxAddr()->enCdmaModemId = MODEM_ID_BUTT;

    return;
}

/*****************************************************************************
 函 数 名  : MTC_InitCtx
 功能描述  : 初始化MTC上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月13日
    作    者   : j00174725
    修改内容   : V9R1 干扰控制项目
  2.日    期   : 2014年01月17日
    作    者   : l00198894
    修改内容   : V9R1C53 C+L 离网重选项目
*****************************************************************************/
VOS_VOID MTC_InitCtx(VOS_VOID)
{
    /* 初始化MTC调试信息上下文 */
    MTC_InitDebugCtx();

    /* 初始化频段冲突相关上下文 */
    MTC_InitIntrusionCtx();

    /* 初始化MTC模块PS域迁移相关上下文 */
    MTC_InitPsTransferCtx();

    /* 初始化MTC模块Modem信息上下文 */
    MTC_InitModemCtx();

    /* 初始化MTC模块运营商定制特性 */
    MTC_InitOperatorCustSolution();

    /* 初始化RF&LCD干扰规避上下文 */
    MTC_InitRfLcdIntrusionCtx();

    return ;
}

/*****************************************************************************
 函 数 名  : MTC_GetIntrusionCfg
 功能描述  : 获取频段冲突控制信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MTC_CFG_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月13日
    作    者   : j00174725
    修改内容   : V9R1 干扰控制项目
*****************************************************************************/
MTC_CFG_ENUM_UINT8 MTC_GetIntrusionCfg(VOS_VOID)
{
    MTC_INTRUSION_CTX_STRU             *pstMtcIntrusionCtx = VOS_NULL_PTR;

    pstMtcIntrusionCtx = MTC_GetIntrusionCtxAddr();

    if (0 != (pstMtcIntrusionCtx->stIntrusionCfg.ucSolutionMask & MTC_INTRUSION_CFG_BIT))
    {
        return MTC_CFG_ENABLE;
    }
    else
    {
        return MTC_CFG_DISABLE;
    }
}

/*****************************************************************************
 函 数 名  : MTC_SetModemPowerState
 功能描述  : 设置开关机状态,ModemID有效性由调用者保证
 输入参数  : enModemId  -- Modem ID
             enState    -- 开关机状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月13日
    作    者   : j00174725
    修改内容   : V9R1 干扰控制项目
*****************************************************************************/
VOS_VOID MTC_SetModemPowerState(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_MODEM_POWER_STATE_ENUM_UINT8    enState
)
{
    MTC_GetCtxAddr()->astModemInfo[enModemId].enPowerState = enState;

    return;
}

/*****************************************************************************
 函 数 名  : MTC_GetModemPowerState
 功能描述  : 获取开关机状态，ModemID有效性由调用者保证
 输入参数  : enModemId  -- Modem ID
 输出参数  : 无
 返 回 值  : MTC_MODEM_POWER_STATE_ENUM_UINT8 开关机状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月13日
    作    者   : j00174725
    修改内容   : V9R1 干扰控制项目
*****************************************************************************/
MTC_MODEM_POWER_STATE_ENUM_UINT8 MTC_GetModemPowerState(MODEM_ID_ENUM_UINT16 enModemId)
{
    return MTC_GetModemCtxAddr(enModemId)->enPowerState;
}

/*****************************************************************************
 函 数 名  : MTC_SetModemImsaState
 功能描述  : 设置IMSA开关机状态, ModemID有效性由调用者保证
 输入参数  : enModemId  -- Modem ID
             enState    -- IMSA开关机状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月13日
    作    者   : l00198894
    修改内容   : VOLTE Rank1方案项目
*****************************************************************************/
VOS_VOID MTC_SetModemImsaState(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_MODEM_POWER_STATE_ENUM_UINT8    enState
)
{
    MTC_GetCtxAddr()->astModemInfo[enModemId].enImsaState = enState;

    return;
}

/*****************************************************************************
 函 数 名  : MTC_GetModemImsaState
 功能描述  : 获取IMSA开关机状态，ModemID有效性由调用者保证
 输入参数  : enModemId  -- Modem ID
 输出参数  : 无
 返 回 值  : MTC_MODEM_POWER_STATE_ENUM_UINT8 IMSA开关机状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月13日
    作    者   : l00198894
    修改内容   : VOLTE Rank1方案项目

*****************************************************************************/
MTC_MODEM_POWER_STATE_ENUM_UINT8 MTC_GetModemImsaState(MODEM_ID_ENUM_UINT16 enModemId)
{
    return MTC_GetModemCtxAddr(enModemId)->enImsaState;
}

/*****************************************************************************
 函 数 名  : MTC_SetModemImsVoiceCap
 功能描述  : 设置IMS语音可用状态, ModemID有效性由调用者保证
 输入参数  : enModemId  -- Modem ID
             enState    -- IMS语音可用状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月17日
    作    者   : w00316404
    修改内容   : 新增函数
*****************************************************************************/
VOS_VOID MTC_SetModemImsVoiceCap(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_MODEM_IMS_VOICE_CAP_ENUM_UINT8  enState
)
{
    MTC_GetModemCtxAddr(enModemId)->enImsVoiceCap = enState;

    return;
}

/*****************************************************************************
 函 数 名  : MTC_GetModemImsVoiceCap
 功能描述  : 获取IMS语音可用状态，ModemID有效性由调用者保证
 输入参数  : enModemId  -- Modem ID
 输出参数  : 无
 返 回 值  : MTC_MODEM_IMS_VOICE_CAP_ENUM_UINT8 IMS语音可用状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月17日
    作    者   : w00316404
    修改内容   : 新增函数
*****************************************************************************/
MTC_MODEM_IMS_VOICE_CAP_ENUM_UINT8 MTC_GetModemImsVoiceCap(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return MTC_GetModemCtxAddr(enModemId)->enImsVoiceCap;
}

/*****************************************************************************
 函 数 名  : MTC_SetModemUsimValidFlag
 功能描述  : 设置卡状态是否有效,ModemID有效性由调用者保证
 输入参数  : enModemId            -- Modem ID
             ucUsimValidStatus    -- 卡状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月23日
    作    者   : z00161729
    修改内容   : DTS2014012305088:svlte特性开启卡无效场景mtc无需上报pstransfer:0

*****************************************************************************/
VOS_VOID MTC_SetModemUsimValidFlag(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucUsimValidStatus
)
{
    MTC_GetCtxAddr()->astModemInfo[enModemId].ucUsimValidFlag = ucUsimValidStatus;

    return;
}

/*****************************************************************************
 函 数 名  : MTC_GetModemUsimValidFlag
 功能描述  : 获取卡状态是否有效标识，ModemID有效性由调用者保证
 输入参数  : enModemId  -- Modem ID
 输出参数  : 无
 返 回 值  : 卡状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月23日
    作    者   : z00161729
    修改内容   : DTS2014012305088:svlte特性开启卡无效场景mtc无需上报pstransfer:0

*****************************************************************************/
VOS_UINT8 MTC_GetModemUsimValidFlag(MODEM_ID_ENUM_UINT16 enModemId)
{
    return MTC_GetModemCtxAddr(enModemId)->ucUsimValidFlag;
}


/*****************************************************************************
 函 数 名  : MTC_SetModemRatMode
 功能描述  : 设置接入模式信息,ModemID有效性由调用者保证
 输入参数  : enModemId  -- Modem ID
             enRatMode  -- 接入模式
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月13日
    作    者   : l00198894
    修改内容   : V9R1 干扰控制项目
*****************************************************************************/
VOS_VOID MTC_SetModemRatMode(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_RATMODE_ENUM_UINT8              enRatMode
)
{
    MTC_GetModemCtxAddr(enModemId)->enRatMode = enRatMode;

    return;
}

/*****************************************************************************
 函 数 名  : MTC_GetModemRatMode
 功能描述  : 获取接入模式，ModemID有效性由调用者保证
 输入参数  : enModemId  -- Modem ID
 输出参数  : 无
 返 回 值  : MTC_RATMODE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月13日
    作    者   : l00198894
    修改内容   : V9R1 干扰控制项目
*****************************************************************************/
MTC_RATMODE_ENUM_UINT8 MTC_GetModemRatMode(MODEM_ID_ENUM_UINT16 enModemId)
{
    return MTC_GetCtxAddr()->astModemInfo[enModemId].enRatMode;
}

/*****************************************************************************
 函 数 名  : MTC_SetModemCallSrvExistFlg
 功能描述  : 设置Modem CS域呼叫业务存在标志位,ModemID有效性由调用者保证
 输入参数  : enModemId  -- Modem ID
             ucFlg      -- 标志位
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月13日
    作    者   : l00198894
    修改内容   : V9R1 干扰控制项目
*****************************************************************************/
VOS_VOID MTC_SetModemCallSrvExistFlg(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucFlg
)
{
    MTC_GetCtxAddr()->astModemInfo[enModemId].stSrvInfo.ucCallSrvExistFlg = ucFlg;

    return;
}

/*****************************************************************************
 函 数 名  : MTC_SetModemSmsSrvExistFlg
 功能描述  : 设置Modem CS域短信业务存在标志位，ModemID有效性由调用者保证
 输入参数  : enModemId  -- Modem ID
             ucFlg      -- 标志位
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月13日
    作    者   : l00198894
    修改内容   : V9R1 干扰控制项目
*****************************************************************************/
VOS_VOID MTC_SetModemSmsSrvExistFlg(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucFlg
)
{
    MTC_GetCtxAddr()->astModemInfo[enModemId].stSrvInfo.ucSmsSrvExistFlg = ucFlg;

    return;
}

/*****************************************************************************
 函 数 名  : MTC_SetModemSsSrvExistFlg
 功能描述  : 设置Modem CS域补充业务存在标志位，ModemID有效性由调用者保证
 输入参数  : enModemId  -- Modem ID
             ucFlg      -- 标志位
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月13日
    作    者   : l00198894
    修改内容   : V9R1 干扰控制项目
*****************************************************************************/
VOS_VOID MTC_SetModemSsSrvExistFlg(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucFlg
)
{
    MTC_GetCtxAddr()->astModemInfo[enModemId].stSrvInfo.ucSsSrvExistFlg = ucFlg;

    return;
}

/*****************************************************************************
 函 数 名  : MTC_GetModemCsSrvExistFlg
 功能描述  : 设置Modem CS域业务存在标志位，ModemID有效性由调用者保证
 输入参数  : enModemId  -- Modem ID
 输出参数  : 无
 返 回 值  : MTC_CS_SERVICE_STATE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月13日
    作    者   : l00198894
    修改内容   : V9R1 干扰控制项目
*****************************************************************************/
MTC_CS_SERVICE_STATE_ENUM_UINT8 MTC_GetModemCsSrvExistFlg(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    MTC_MODEM_SERVICE_INFO_STRU        *pstSrvInfo = VOS_NULL_PTR;

    pstSrvInfo = &(MTC_GetCtxAddr()->astModemInfo[enModemId].stSrvInfo);

    /* 仅在当前呼叫、短信、补充业务都不存在时认为CS域服务不存在 */
    if ( (VOS_FALSE == pstSrvInfo->ucCallSrvExistFlg)
      && (VOS_FALSE == pstSrvInfo->ucSmsSrvExistFlg)
      && (VOS_FALSE == pstSrvInfo->ucSsSrvExistFlg) )
    {
        return MTC_CS_NO_SERVICE;
    }

    return MTC_CS_IN_SERVICE;
}

/*****************************************************************************
 函 数 名  : MTC_GetModemCurBandInfo
 功能描述  : 获取Modem当前频段信息，ModemID有效性由调用者保证
 输入参数  : 无
 输出参数  : 无
 返 回 值  : RRC_MTC_MS_BAND_INFO_STRU *
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月13日
    作    者   : l00198894
    修改内容   : V9R1 干扰控制项目
*****************************************************************************/
RRC_MTC_MS_BAND_INFO_STRU* MTC_GetModemCurBandInfo(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(MTC_GetCtxAddr()->astModemInfo[enModemId].stCurBandInfo);
}

/*****************************************************************************
 函 数 名  : MTC_ResetModemCurBandInfo
 功能描述  : 清空Modem当前频段信息，ModemID有效性由调用者保证
 输入参数  : enModemId   -- modem id
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月05日
    作    者   : j00174725
    修改内容   : DTS2015102706654
*****************************************************************************/
VOS_VOID MTC_ResetModemCurBandInfo(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    PS_MEM_SET(MTC_GetModemCurBandInfo(enModemId), 0x0, sizeof(RRC_MTC_MS_BAND_INFO_STRU));

    return;
}


/*****************************************************************************
 函 数 名  : MTC_GetModemNCellBandInfo
 功能描述  : 获取Modem临区频段信息，ModemID有效性由调用者保证
 输入参数  : enModemId
 输出参数  : 无
 返 回 值  : RRC_MTC_MS_BAND_INFO_STRU *
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月05日
    作    者   : j00174725
    修改内容   : DTS2015102706654
*****************************************************************************/
RRC_MTC_MS_BAND_INFO_STRU* MTC_GetModemNCellBandInfo(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(MTC_GetCtxAddr()->astModemInfo[enModemId].stNCellBandInfo);
}


/*****************************************************************************
 函 数 名  : MTC_SetModemNCellBandInfo
 功能描述  : 设置Modem临区频段信息，ModemID有效性由调用者保证
 输入参数  : enModemId   -- modem id
             enBandNum   -- Band No.
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月05日
    作    者   : j00174725
    修改内容   : DTS2015102706654
*****************************************************************************/
VOS_VOID MTC_SetModemNCellBandInfo(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_BAND_INFO_ENUM_UINT16           enBandNum
)
{
    VOS_UINT64                          *pulBandInfo;

    /* 检查Band的有效性 */
    if (enBandNum > MTC_FREQ_BAND44)
    {
        return;
    }

    pulBandInfo     = (VOS_UINT64 *)MTC_GetCtxAddr()->astModemInfo[enModemId].stNCellBandInfo.aulBandInfo;

    *pulBandInfo    |= MTC_SET_BIT64(enBandNum);

    return;
}

/*****************************************************************************
 函 数 名  : MTC_ResetNCellBandInfo
 功能描述  : 清空Modem临区频段信息，ModemID有效性由调用者保证
 输入参数  : enModemId   -- modem id
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月05日
    作    者   : j00174725
    修改内容   : DTS2015102706654
*****************************************************************************/
VOS_VOID MTC_ResetNCellBandInfo(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    PS_MEM_SET(MTC_GetModemNCellBandInfo(enModemId), 0x0, sizeof(RRC_MTC_MS_BAND_INFO_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : MTC_GetBufAddr
 功能描述  : 获取缓存消息地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MTC_MSG_BUF_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月05日
    作    者   : j00174725
    修改内容   : DTS2015102706654
*****************************************************************************/
MTC_MSG_BUF_STRU* MTC_GetBufAddr(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(MTC_GetCtxAddr()->astModemInfo[enModemId].stBufMsg);
}


/*****************************************************************************
 函 数 名  : MTC_GetModemSerCellBandInfo
 功能描述  : 获取Modem当前频段信息，ModemID有效性由调用者保证
 输入参数  : enModemId --- MODEM ID (有效性由调用者保证)
 输出参数  : 无
 返 回 值  : RRC_MTC_MS_BAND_INFO_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月24日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
RRC_MTC_MS_BAND_INFO_STRU* MTC_GetModemSerCellBandInfo(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(MTC_GetCtxAddr()->astModemInfo[enModemId].stSerCellBandInfo);
}

/*****************************************************************************
 函 数 名  : MTC_SetNotchEnalbeFlag
 功能描述  : 设置Notch使能状态标志
 输入参数  : PS_BOOL_ENUM_UINT8 enFlag
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月21日
    作    者   : z60575
    修改内容   : V9R1 Notch Bypass项目
*****************************************************************************/
VOS_VOID MTC_SetNotchEnalbeFlag(PS_BOOL_ENUM_UINT8 enFlag)
{
    MTC_INTRUSION_CTX_STRU             *pstMtcIntrusionCtx = VOS_NULL_PTR;

    pstMtcIntrusionCtx = MTC_GetIntrusionCtxAddr();

    pstMtcIntrusionCtx->enNotchEnableFlag = enFlag;

    return;
}

/*****************************************************************************
 函 数 名  : MTC_GetNotchEnalbeFlag
 功能描述  : 获取notch使能标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : PS_BOOL_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月21日
    作    者   : z60575
    修改内容   : V9R1 Notch Bypass项目
*****************************************************************************/
PS_BOOL_ENUM_UINT8 MTC_GetNotchEnalbeFlag(VOS_VOID)
{
    MTC_INTRUSION_CTX_STRU             *pstMtcIntrusionCtx = VOS_NULL_PTR;

    pstMtcIntrusionCtx = MTC_GetIntrusionCtxAddr();

    return pstMtcIntrusionCtx->enNotchEnableFlag;
}

/*****************************************************************************
 函 数 名  : MTC_GetNotchCfg
 功能描述  : 获取Notch Bypass特性的配置开关
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MTC_CFG_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月21日
    作    者   : z60575
    修改内容   : V9R1 Notch Bypass项目
*****************************************************************************/
MTC_CFG_ENUM_UINT8 MTC_GetNotchCfg(VOS_VOID)
{
    MTC_INTRUSION_CTX_STRU             *pstMtcIntrusionCtx = VOS_NULL_PTR;

    pstMtcIntrusionCtx = MTC_GetIntrusionCtxAddr();

    if (0 != (pstMtcIntrusionCtx->stIntrusionCfg.ucSolutionMask & MTC_NOTCH_CFG_BIT))
    {
        return MTC_CFG_ENABLE;
    }
    else
    {
        return MTC_CFG_DISABLE;
    }
}

/*****************************************************************************
 函 数 名  : MTC_SetNarrowDcsEnalbeFlag
 功能描述  : 设置NarrowDcs使能状态标志
 输入参数  : PS_BOOL_ENUM_UINT8 enFlag
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年02月13日
    作    者   : f00179208
    修改内容   : Jazz Narrow Band dcs项目
*****************************************************************************/
VOS_VOID MTC_SetNarrowDcsEnalbeFlag(PS_BOOL_ENUM_UINT8 enFlag)
{
    MTC_INTRUSION_CTX_STRU             *pstMtcIntrusionCtx = VOS_NULL_PTR;

    pstMtcIntrusionCtx = MTC_GetIntrusionCtxAddr();

    pstMtcIntrusionCtx->enNarrowDcsEnableFlag = enFlag;

    return;
}

/*****************************************************************************
 函 数 名  : MTC_GetNarrowDcsEnalbeFlag
 功能描述  : 获取NarrowDcs使能标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : PS_BOOL_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年02月13日
    作    者   : f00179208
    修改内容   : Jazz Narrow Band dcs项目
*****************************************************************************/
PS_BOOL_ENUM_UINT8 MTC_GetNarrowDcsEnalbeFlag(VOS_VOID)
{
    MTC_INTRUSION_CTX_STRU             *pstMtcIntrusionCtx = VOS_NULL_PTR;

    pstMtcIntrusionCtx = MTC_GetIntrusionCtxAddr();

    return pstMtcIntrusionCtx->enNarrowDcsEnableFlag;
}

/*****************************************************************************
 函 数 名  : MTC_GetNarrowBandDcsCfg
 功能描述  : 获取Narrow Band Dcs特性的配置开关
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MTC_CFG_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年02月13日
    作    者   : f00179208
    修改内容   : Jazz Narrow Band dcs项目
*****************************************************************************/
MTC_CFG_ENUM_UINT8 MTC_GetNarrowBandDcsCfg(VOS_VOID)
{
    MTC_INTRUSION_CTX_STRU             *pstMtcIntrusionCtx = VOS_NULL_PTR;

    pstMtcIntrusionCtx = MTC_GetIntrusionCtxAddr();

    if (0 != (pstMtcIntrusionCtx->stIntrusionCfg.ucSolutionMask & MTC_NARROW_BAND_DCS_CFG_BIT))
    {
        return MTC_CFG_ENABLE;
    }
    else
    {
        return MTC_CFG_DISABLE;
    }
}



/*****************************************************************************
 函 数 名  : MTC_GetTlRfCtrlCfg
 功能描述  : 获取TL射频控制特性的配置开关
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : MTC_CFG_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月24日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2014年4月24日
    作    者   : Y00213812
    修改内容   : DTS2014042306844: FORTIFY检查修改
*****************************************************************************/
MTC_CFG_ENUM_UINT8 MTC_GetTlRfCtrlCfg(VOS_VOID)
{
    MTC_RF_INTRUSION_CFG_STRU          *pstRfIntrusionCfg = VOS_NULL_PTR;
    MTC_CFG_ENUM_UINT8                  enMtcCfg;

    pstRfIntrusionCfg = (MTC_RF_INTRUSION_CFG_STRU *)&(MTC_GetIntrusionCtxAddr()->stIntrusionCfg);
    enMtcCfg          = (VOS_TRUE == pstRfIntrusionCfg->ucTlRfCtrlCfg) ? MTC_CFG_ENABLE : MTC_CFG_DISABLE;

    return enMtcCfg;
}

/*****************************************************************************
 函 数 名  : MTC_SetTlRfCtrlEnalbeFlag
 功能描述  : 设置TL上行发射控制标识
 输入参数  : PS_BOOL_ENUM_UINT8 enFlag
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月24日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MTC_SetTlRfCtrlEnalbeFlag(PS_BOOL_ENUM_UINT8 enFlag)
{
    MTC_GetIntrusionCtxAddr()->enTlRfCtrlEnableFlag = enFlag;
    return;
}

/*****************************************************************************
 函 数 名  : MTC_GetTlRfCtrlEnalbeFlag
 功能描述  : 获取TL上行发射控制标识
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : PS_BOOL_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月24日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
PS_BOOL_ENUM_UINT8 MTC_GetTlRfCtrlEnalbeFlag(VOS_VOID)
{
    return MTC_GetIntrusionCtxAddr()->enTlRfCtrlEnableFlag;
}

/*****************************************************************************
 函 数 名  : MTC_GetPsTransferCfg
 功能描述  : 获取PS 迁移特性的配置
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MTC_PS_TRANSFER_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月21日
    作    者   : z60575
    修改内容   : V9R1 Notch Bypass项目
*****************************************************************************/
MTC_PS_TRANSFER_ENUM_UINT8 MTC_GetPsTransferCfg(VOS_VOID)
{
    return MTC_GetCtxAddr()->stPsTransferCtx.stPsTransferCfg.enSolutionCfg;
}

/*****************************************************************************
 函 数 名  : MTC_GetPsTransferCtxAddr
 功能描述  : 获取PS 迁移特性上下文地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MTC_PS_TRANSFER_CTX_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月21日
    作    者   : z60575
    修改内容   : V9R1 Notch Bypass项目
*****************************************************************************/
MTC_PS_TRANSFER_CTX_STRU* MTC_GetPsTransferCtxAddr(VOS_VOID)
{
    return &(MTC_GetCtxAddr()->stPsTransferCtx);
}

/*****************************************************************************
 函 数 名  : MTC_GetModemNetworkInfoAddr
 功能描述  : 获取Modem当前驻留网络信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MTC_MODEM_NETWORK_INFO_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年01月17日
    作    者   : l00198894
    修改内容   : V9R1C53 C+L 离网重选项目
*****************************************************************************/
MTC_MODEM_NETWORK_INFO_STRU* MTC_GetModemNetworkInfoAddr(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(MTC_GetCtxAddr()->astModemInfo[enModemId].stNetworkInfo);
}

/*****************************************************************************
 函 数 名  : MTC_GetOperatorCustSolution
 功能描述  : 获取运营商定制方案
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MTC_OPERATOR_CUST_SOLUTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年01月17日
    作    者   : l00198894
    修改内容   : V9R1C53 C+L 离网重选项目
*****************************************************************************/
MTC_OPERATOR_CUST_SOLUTION_ENUM_UINT8 MTC_GetOperatorCustSolution(VOS_VOID)
{
    return MTC_GetCtxAddr()->enOperatorCustSolution;
}

/*****************************************************************************
 函 数 名  : MTC_SetOperatorCustSolution
 功能描述  : 设置运营商定制方案
 输入参数  : enOperatorCustSolution
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年01月17日
    作    者   : l00198894
    修改内容   : V9R1C53 C+L 离网重选项目
*****************************************************************************/
VOS_VOID MTC_SetOperatorCustSolution(
    MTC_OPERATOR_CUST_SOLUTION_ENUM_UINT8   enOperatorCustSolution
)
{
    MTC_GetCtxAddr()->enOperatorCustSolution = enOperatorCustSolution;
    return;
}


/*****************************************************************************
 函 数 名  : MTC_GetRfLcdIntrusionCtxAddr
 功能描述  : 获取RF&LCD干扰规避上下文地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MTC_RF_LCD_INTRUSION_CTX_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月04日
    作    者   : j00174725
    修改内容   : RF&LCD INTRUSION项目
*****************************************************************************/
MTC_RF_LCD_INTRUSION_CTX_STRU* MTC_GetRfLcdIntrusionCtxAddr(VOS_VOID)
{
    return &(MTC_GetCtxAddr()->stRfLcdIntrusionCtx);
}

/*****************************************************************************
 函 数 名  : MTC_GetMipiClkRcvPid
 功能描述  : 获取^mipiclk主动上报接收的MTA Pid
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月04日
    作    者   : j00174725
    修改内容   : RF&LCD INTRUSION项目
*****************************************************************************/
VOS_UINT32 MTC_GetMipiClkRcvPid(VOS_VOID)
{
    return MTC_GetRfLcdIntrusionCtxAddr()->ulMipiClkReportModemId;
}

/*****************************************************************************
 函 数 名  : MTC_ReadRfLcdCfgNv
 功能描述  : 读取RF&LCD配置NV项
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月04日
    作    者   : j00174725
    修改内容   : RF&LCD INTRUSION项目
*****************************************************************************/
VOS_VOID MTC_ReadRfLcdCfgNv(VOS_VOID)
{
    VOS_UINT16                          j;
    VOS_UINT16                          i;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulFlag;
    MTC_NVIM_RF_LCD_CFG_STRU            stRfLcdCfg;
    MTC_RF_LCD_INTRUSION_CTX_STRU      *pstRfLcdIntrusionCtx = VOS_NULL_PTR;

    /* 清零 */
    PS_MEM_SET(&stRfLcdCfg, 0x0, sizeof(MTC_NVIM_RF_LCD_CFG_STRU));

    pstRfLcdIntrusionCtx = MTC_GetRfLcdIntrusionCtxAddr();

    /* 读取en_NV_Item_MTC_RF_LCD_CFG NV项 */
    ulRet = NV_Read(en_NV_Item_MTC_RF_LCD_CFG,
                    &stRfLcdCfg,
                    sizeof(MTC_NVIM_RF_LCD_CFG_STRU));
    if (VOS_OK != ulRet)
    {
        pstRfLcdIntrusionCtx->usEnableBitMap = 0x0;
        MTC_WARNING1_LOG("MTC_ReadRfLcdCfgNv: Read Nv Fail.", en_NV_Item_MTC_RF_LCD_CFG);
    }
    else
    {
        pstRfLcdIntrusionCtx->usFreqWidth  = stRfLcdCfg.usFreqWidth;
        pstRfLcdIntrusionCtx->usEnableBitMap = stRfLcdCfg.usEnableBitMap;
    }

    if (0x0 == pstRfLcdIntrusionCtx->usEnableBitMap)
    {
        return;
    }

    /* 判断频率信息的正确性 */
    for (i = 0; i < MTC_RF_LCD_MIPICLK_MAX_NUM; i++)
    {
        ulFlag = VOS_FALSE;
        pstRfLcdIntrusionCtx->astRfLcdFreqList[i].ulMipiClk     = stRfLcdCfg.astRfMipiClkFreqList[i].ulMipiClk;
        pstRfLcdIntrusionCtx->astRfLcdFreqList[i].ulAvailNum    = 0;

        for(j = 0; j < MTC_RF_LCD_MIPICLK_FREQ_MAX_NUM; j++)
        {
            /* 频率值需要大于带宽，否则对应MIPICLK的后续频率都视为无效值 */
            if (stRfLcdCfg.astRfMipiClkFreqList[i].aulFreq[j] >= pstRfLcdIntrusionCtx->usFreqWidth)
            {
                pstRfLcdIntrusionCtx->astRfLcdFreqList[i].aulFreq[j] = stRfLcdCfg.astRfMipiClkFreqList[i].aulFreq[j];
                pstRfLcdIntrusionCtx->astRfLcdFreqList[i].ulAvailNum++;
                ulFlag = VOS_TRUE;
            }
            else
            {
                break;
            }
        }

        if (VOS_TRUE == ulFlag)
        {
            pstRfLcdIntrusionCtx->ucAvailFreqListNum++;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : MTC_GetRfCellInfoAddr
 功能描述  : 获取g_astScellInfo的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MTC_MODEM_MIPICLK_BITMAP_STRU
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月06日
    作    者   : Y00213812
    修改内容   : RF&LCD干扰规避项目新增
*****************************************************************************/
MTC_MODEM_MIPICLK_BITMAP_STRU* MTC_GetRfCellInfoAddr(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(MTC_GetModemCtxAddr(enModemId)->stRfCellInfo);
}

/*****************************************************************************
 函 数 名  : MTC_GetMipiClkBitMap
 功能描述  : 获取g_usMipiClkBitMap的数值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT16
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月06日
    作    者   : Y00213812
    修改内容   : RF&LCD干扰规避项目新增
*****************************************************************************/
VOS_UINT16 MTC_GetMipiClkBitMap(VOS_VOID)
{
    return MTC_GetRfLcdIntrusionCtxAddr()->usMipiClkBitMap;
}

/*****************************************************************************
 函 数 名  : MTC_InitRfCellInfo
 功能描述  : 全局变量初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月06日
    作    者   : Y00213812
    修改内容   : RF&LCD干扰规避项目新增
*****************************************************************************/
VOS_VOID MTC_InitRfCellInfo(MODEM_ID_ENUM_UINT16 enModemId)
{
    MTC_MODEM_MIPICLK_BITMAP_STRU      *pstRfCellInfo = VOS_NULL_PTR;

    pstRfCellInfo = MTC_GetRfCellInfoAddr(enModemId);

    pstRfCellInfo->enCsExistFlag     = PS_FALSE;
    pstRfCellInfo->enPsExistFlag     = PS_FALSE;
    pstRfCellInfo->usScellBitMap     = MTC_GetMipiClkBitMap();
    pstRfCellInfo->usHoppingBitMap   = MTC_GetMipiClkBitMap();
    pstRfCellInfo->usNcellBitMap     = MTC_GetMipiClkBitMap();
}

/*****************************************************************************
 函 数 名  : MTC_InitRfLcdIntrusionCtx
 功能描述  : 初始化Rf&Lcd干扰相关上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月04日
    作    者   : j00174725
    修改内容   : RF&LCD INTRUSION项目
*****************************************************************************/
VOS_VOID MTC_InitRfLcdIntrusionCtx(VOS_VOID)
{
    MTC_RF_LCD_INTRUSION_CTX_STRU      *pstRfLcdIntrusionCtx = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usModemIndex;

    pstRfLcdIntrusionCtx = MTC_GetRfLcdIntrusionCtxAddr();

    /* 初始化上下文 */
    PS_MEM_SET(pstRfLcdIntrusionCtx, 0x0, sizeof(MTC_RF_LCD_INTRUSION_CTX_STRU));

    /* 初始化为0xffff,为后继移位作准备 */
    pstRfLcdIntrusionCtx->usMipiClkBitMap = 0xFFFF;

    /* 读取NV项 */
    MTC_ReadRfLcdCfgNv();

    /* 根据LCD MIPICLK有效个数设置位图 */
    if (pstRfLcdIntrusionCtx->ucAvailFreqListNum <= MTC_RF_LCD_MIPICLK_MAX_NUM)
    {
        ucIndex = 16 - pstRfLcdIntrusionCtx->ucAvailFreqListNum;
        pstRfLcdIntrusionCtx->usMipiClkBitMap >>= ucIndex;
    }

    /* 设置^mipiclk主动上报接收的MTA Pid */
    pstRfLcdIntrusionCtx->ulMipiClkReportModemId = I0_UEPS_PID_MTA;             /* 当前方案默认从Modem0上报 */

    for (usModemIndex = 0; usModemIndex < MODEM_ID_BUTT; usModemIndex++)
    {
        /* 初始化RF&LCD筛选模块上下文 */
        MTC_InitRfCellInfo(usModemIndex);
    }

    return;
}

/*****************************************************************************
 函 数 名  : MTC_GetRfLcdIntrusionCfg
 功能描述  : 获取RF&LCD干扰规避是否使能
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MTC_CFG_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月13日
    作    者   : j00174725
    修改内容   : V9R1 干扰控制项目
*****************************************************************************/
MTC_CFG_ENUM_UINT8 MTC_GetRfLcdIntrusionCfg(VOS_VOID)
{
    MTC_RF_LCD_INTRUSION_CTX_STRU      *pstRfLcdIntrusionCtx = VOS_NULL_PTR;

    pstRfLcdIntrusionCtx = MTC_GetRfLcdIntrusionCtxAddr();

    if (0 != pstRfLcdIntrusionCtx->usEnableBitMap)
    {
        return MTC_CFG_ENABLE;
    }
    else
    {
        return MTC_CFG_DISABLE;
    }
}

/*****************************************************************************
 函 数 名  : MTC_GetRseSupportCfg
 功能描述  : RSE功能配置
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MTC_CFG_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年05月12日
    作    者   : j00174725
    修改内容   : RSE项目
*****************************************************************************/
MTC_CFG_ENUM_UINT8 MTC_GetRseSupportCfg(VOS_VOID)
{
    MTC_INTRUSION_CTX_STRU             *pstMtcIntrusionCtx = VOS_NULL_PTR;

    pstMtcIntrusionCtx = MTC_GetIntrusionCtxAddr();

    if (0 != (pstMtcIntrusionCtx->stIntrusionCfg.ucSolutionMask & MTC_RSE_CFG_BIT))
    {
        return MTC_CFG_ENABLE;
    }
    else
    {
        return MTC_CFG_DISABLE;
    }
}

/*****************************************************************************
 函 数 名  : MTC_GetRseCfgValue
 功能描述  : 从上下文中获取前一次配置的RSE值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : PS_BOOL_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年05月12日
    作    者   : j00174725
    修改内容   : RSE项目
*****************************************************************************/
PS_BOOL_ENUM_UINT8 MTC_GetRseCfgValue(VOS_VOID)
{
    MTC_INTRUSION_CTX_STRU             *pstMtcIntrusionCtx = VOS_NULL_PTR;

    pstMtcIntrusionCtx = MTC_GetIntrusionCtxAddr();

    return pstMtcIntrusionCtx->enRseCfg;
}

/*lint -e958 修改人: j00174725 for RSE 2014-06-16 begin */
/*****************************************************************************
 函 数 名  : MTC_SetRseCfgValue
 功能描述  : 保存RSE值到上下文中
 输入参数  : enValue
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年05月12日
    作    者   : j00174725
    修改内容   : RSE项目
*****************************************************************************/
VOS_VOID MTC_SetRseCfgValue(PS_BOOL_ENUM_UINT8 enValue)
{
    MTC_INTRUSION_CTX_STRU             *pstMtcIntrusionCtx = VOS_NULL_PTR;

    pstMtcIntrusionCtx = MTC_GetIntrusionCtxAddr();

    pstMtcIntrusionCtx->enRseCfg = enValue;

    return;
}
/*lint +e958 修改人: j00174725 for RSE 2014-06-16 end */


/*****************************************************************************
 函 数 名  : MTC_SetCsSessionInfo
 功能描述  : 设置CS Session
 输入参数  : enModemId            -- Modem ID
             enSessionType        -- session type
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月04日
    作    者   : j00174725
    修改内容   : DTS2015082406288
*****************************************************************************/
VOS_VOID MTC_SetCsSessionInfo(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_SESSION_TYPE_ENUM_UINT8         enSessionType
)
{
    MTC_GetModemCtxAddr(enModemId)->stConnStateInfo.ulCsSessionInfo |= MTC_SET_BIT(enSessionType);
}

/*****************************************************************************
 函 数 名  : MTC_SetPsSessionInfo
 功能描述  : 设置PS Session
 输入参数  : enModemId            -- Modem ID
             enSessionType        -- session type
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月24日
    作    者   : h00313353
    修改内容   : DTS2015122211114
*****************************************************************************/
VOS_VOID MTC_SetPsSessionInfo(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_SESSION_TYPE_ENUM_UINT8         enSessionType
)
{
    MTC_GetModemCtxAddr(enModemId)->stConnStateInfo.ulPsSessionInfo |= MTC_SET_BIT(enSessionType);
}

/*****************************************************************************
 函 数 名  : MTC_ClearCsSessionInfo
 功能描述  : 清除CS Session
 输入参数  : enModemId            -- Modem ID
             enSessionType        -- session type
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月04日
    作    者   : j00174725
    修改内容   : DTS2015082406288
*****************************************************************************/
VOS_VOID MTC_ClearCsSessionInfo(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_SESSION_TYPE_ENUM_UINT8         enSessionType
)
{
    MTC_GetModemCtxAddr(enModemId)->stConnStateInfo.ulCsSessionInfo &= ~(MTC_SET_BIT(enSessionType));
}

/*****************************************************************************
 函 数 名  : MTC_ClearPsSessionInfo
 功能描述  : 清除PS Session
 输入参数  : enModemId            -- Modem ID
             enSessionType        -- session type
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月24日
    作    者   : h00313353
    修改内容   : DTS2015122211114
*****************************************************************************/
VOS_VOID MTC_ClearPsSessionInfo(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_SESSION_TYPE_ENUM_UINT8         enSessionType
)
{
    MTC_GetModemCtxAddr(enModemId)->stConnStateInfo.ulPsSessionInfo &= ~(MTC_SET_BIT(enSessionType));
}

/*****************************************************************************
 函 数 名  : MTC_IsCsSessionInfoExit
 功能描述  : CS Session是否存在
 输入参数  : enModemId            -- Modem ID
 输出参数  : 无
 返 回 值  : PS_BOOL_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月04日
    作    者   : j00174725
    修改内容   : DTS2015082406288
*****************************************************************************/
PS_BOOL_ENUM_UINT8 MTC_IsCsSessionInfoExit(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    VOS_UINT32                          ulCsSessionInfo;
    VOS_UINT32                          ulIndex;

    ulCsSessionInfo = MTC_GetCsSessionInfo(enModemId);

    for (ulIndex = MTC_SESSION_TYPE_CS_MO_NORMAL_CALL; ulIndex < MTC_SESSION_TYPE_CS_BUTT; ulIndex++)
    {
        if (MTC_SET_BIT(ulIndex) == (ulCsSessionInfo & MTC_SET_BIT(ulIndex)))
        {
            return PS_TRUE;
        }
    }

    return PS_FALSE;
}
/*****************************************************************************
 函 数 名  : MTC_GetCsSessionInfo
 功能描述  : 获取CS Session记录值
 输入参数  : enModemId            -- Modem ID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月04日
    作    者   : j00174725
    修改内容   : DTS2015082406288
*****************************************************************************/
VOS_UINT32 MTC_GetCsSessionInfo(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return  MTC_GetModemCtxAddr(enModemId)->stConnStateInfo.ulCsSessionInfo;
}

/*****************************************************************************
 函 数 名  : MTC_GetPsSessionInfo
 功能描述  : 获取PS Session记录值
 输入参数  : enModemId            -- Modem ID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月04日
    作    者   : j00174725
    修改内容   : DTS2015082406288
*****************************************************************************/
VOS_UINT32 MTC_GetPsSessionInfo(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return  MTC_GetModemCtxAddr(enModemId)->stConnStateInfo.ulPsSessionInfo;
}

/*****************************************************************************
 函 数 名  : MTC_IsPsSessionInfoExit
 功能描述  : PS Session是否存在
 输入参数  : enModemId            -- Modem ID
 输出参数  : 无
 返 回 值  : PS_BOOL_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月24日
    作    者   : h00313353
    修改内容   : DTS2015122211114
*****************************************************************************/
PS_BOOL_ENUM_UINT8 MTC_IsPsSessionInfoExit(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    VOS_UINT32                          ulPsSessionInfo;
    VOS_UINT32                          ulIndex;

    ulPsSessionInfo = MTC_GetPsSessionInfo(enModemId);

    for (ulIndex = MTC_SESSION_TYPE_PS_CONVERSAT_CALL; ulIndex < MTC_SESSION_TYPE_BUTT; ulIndex++)
    {
        if (MTC_SET_BIT(ulIndex) == (ulPsSessionInfo & MTC_SET_BIT(ulIndex)))
        {
            return PS_TRUE;
        }
    }

    return PS_FALSE;
}


/* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
/*****************************************************************************
 函 数 名  : MTC_SetCsTypeInfo
 功能描述  : 设置CS连接状态
 输入参数  : enModemId            -- Modem ID
             ucCsType             -- CS类型
             enCsSrvConnState     -- 存在状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月16日
    作    者   : j00174725
    修改内容   : K3V3 多模多天线特性
*****************************************************************************/
VOS_VOID MTC_SetCsTypeInfo(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_CS_TYPE_ENUM_UINT8              enCsType,
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enCsSrvConnState
)
{
    if (TAF_MTC_SRV_EXIST == enCsSrvConnState)
    {
        MTC_GetModemCtxAddr(enModemId)->stConnStateInfo.ucCsSrvConnInfo |= (VOS_UINT8)MTC_SET_BIT(enCsType);
    }
    else
    {
        MTC_GetModemCtxAddr(enModemId)->stConnStateInfo.ucCsSrvConnInfo &=  (~((VOS_UINT8)MTC_SET_BIT(enCsType)));
    }

    return;
}

/*****************************************************************************
 函 数 名  : MTC_GetCsTypeInfo
 功能描述  : 获取CS连接状态
 输入参数  : enModemId            -- Modem ID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月16日
    作    者   : j00174725
    修改内容   : K3V3 多模多天线特性
*****************************************************************************/
VOS_UINT8 MTC_GetCsTypeInfo(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return (MTC_GetModemCtxAddr(enModemId)->stConnStateInfo.ucCsSrvConnInfo & MTC_CS_TYPE_ALL_VALUE);
}

/*****************************************************************************
 函 数 名  : MTC_GetCsSrvState
 功能描述  : 判断是否有CS连接存在
 输入参数  : enModemId            -- Modem ID
 输出参数  : 无
 返 回 值  : TAF_MTC_SRV_CONN_STATE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月16日
    作    者   : j00174725
    修改内容   : K3V3 多模多天线特性
*****************************************************************************/
TAF_MTC_SRV_CONN_STATE_ENUM_UINT8 MTC_GetCsSrvState(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT8                           ucCsTypeInfo;

    ucCsTypeInfo    = MTC_GetCsTypeInfo(enModemId) & MTC_CS_TYPE_ALL_VALUE;

    for (ulIndex = MTC_CS_TYPE_GU; ulIndex < MTC_CS_TYPE_BUTT; ulIndex++)
    {
        if (MTC_SET_BIT(ulIndex) == (ucCsTypeInfo & MTC_SET_BIT(ulIndex)))
        {
            return TAF_MTC_SRV_EXIST;
        }
    }

    return TAF_MTC_SRV_NO_EXIST;
}

/*****************************************************************************
 函 数 名  : MTC_SetPsTypeInfo
 功能描述  : 设置PS连接类型
 输入参数  : enModemId            -- Modem ID
             ucPsType             -- PS类型
             enPsSrvConnState     -- 存在状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月10日
    作    者   : j00174725
    修改内容   : DTS2015093005685
*****************************************************************************/
VOS_VOID MTC_SetPsTypeInfo(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_PS_TYPE_ENUM_UINT8              enPsType,
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enPsSrvConnState
)
{
    if (TAF_MTC_SRV_EXIST == enPsSrvConnState)
    {
        MTC_GetModemCtxAddr(enModemId)->stConnStateInfo.ucPsSrvConnInfo |= (VOS_UINT8)MTC_SET_BIT(enPsType);
    }
    else
    {
        MTC_GetModemCtxAddr(enModemId)->stConnStateInfo.ucPsSrvConnInfo &=  (~((VOS_UINT8)MTC_SET_BIT(enPsType)));
    }

    return;
}

/*****************************************************************************
 函 数 名  : MTC_GetPsTypeInfo
 功能描述  : 获取PS连接状态
 输入参数  : enModemId            -- Modem ID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月10日
    作    者   : j00174725
    修改内容   : DTS2015093005685
*****************************************************************************/
VOS_UINT8 MTC_GetPsTypeInfo(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return (MTC_GetModemCtxAddr(enModemId)->stConnStateInfo.ucPsSrvConnInfo & MTC_PS_TYPE_ALL_VALUE);
}

/*****************************************************************************
 函 数 名  : MTC_GetPsSrvState
 功能描述  : 判断是否有PS连接存在
 输入参数  : enModemId            -- Modem ID
 输出参数  : 无
 返 回 值  : TAF_MTC_SRV_CONN_STATE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月10日
    作    者   : j00174725
    修改内容   : DTS2015093005685
*****************************************************************************/
TAF_MTC_SRV_CONN_STATE_ENUM_UINT8 MTC_GetPsSrvState(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT8                           ucPsTypeInfo;

    ucPsTypeInfo    = MTC_GetPsTypeInfo(enModemId);

    for (ulIndex = MTC_PS_TYPE_GU; ulIndex < MTC_PS_TYPE_BUTT; ulIndex++)
    {
        if (MTC_SET_BIT(ulIndex) == (ucPsTypeInfo & MTC_SET_BIT(ulIndex)))
        {
            return TAF_MTC_SRV_EXIST;
        }
    }

    return TAF_MTC_SRV_NO_EXIST;
}

/*****************************************************************************
 函 数 名  : MTC_SetUsimStateInfo
 功能描述  : 设置卡状态
 输入参数  : enModemId            -- Modem ID
             enUsimState          -- Usim卡状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月16日
    作    者   : j00174725
    修改内容   : K3V3 多模多天线特性

  2.日    期   : 2015年10月21日
    作    者   : h00313353
    修改内容   : Iteration 19 TAS
*****************************************************************************/
VOS_VOID MTC_SetUsimStateInfo(
    MODEM_ID_ENUM_UINT16                    enModemId,
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16   enUsimState
)
{
    MTC_GetModemCtxAddr(enModemId)->enUsimState = enUsimState;

    return;
}

/*****************************************************************************
 函 数 名  : MTC_SetCsimStateInfo
 功能描述  : 设置卡状态
 输入参数  : enModemId            -- Modem ID
             enCsimState          -- Csim卡状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : h00313353
    修改内容   : Iteration 19 TAS
*****************************************************************************/
VOS_VOID MTC_SetCsimStateInfo(
    MODEM_ID_ENUM_UINT16                    enModemId,
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16   enCsimState
)
{
    MTC_GetModemCtxAddr(enModemId)->enCsimState = enCsimState;

    return;
}
/*****************************************************************************
 函 数 名  : MTC_GetUsimStateInfo
 功能描述  : 获取Usim卡状态
 输入参数  : enModemId            -- Modem ID
 输出参数  : 无
 返 回 值  : TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月16日
    作    者   : j00174725
    修改内容   : K3V3 多模多天线特性

  2.日    期   : 2015年10月21日
    作    者   : h00313353
    修改内容   : Iteration 19 TAS
*****************************************************************************/
TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16 MTC_GetUsimStateInfo(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return  MTC_GetModemCtxAddr(enModemId)->enUsimState;
}

/*****************************************************************************
 函 数 名  : MTC_GetCsimStateInfo
 功能描述  : 获取Csim卡状态
 输入参数  : enModemId            -- Modem ID
 输出参数  : 无
 返 回 值  : TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : h00313353
    修改内容   : Iteration 19 TAS
*****************************************************************************/
TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16 MTC_GetCsimStateInfo(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return MTC_GetModemCtxAddr(enModemId)->enCsimState;
}

/*****************************************************************************
 函 数 名  : MTC_GetRatCfgByModemId
 功能描述  : 根据ModemId,获取当前Modem的接入配置
 输入参数  : enModemId            -- Modem ID
 输出参数  : 无
 返 回 值  : MTC_RCM_MODEM_RAT_CFG_ENUM_UINT16
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : h00313353
    修改内容   : Iteration 19 TAS
*****************************************************************************/
MTC_MODEM_RAT_CONFIG_STRU* MTC_GetRatCfgByModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(MTC_GetModemCtxAddr(enModemId)->stRatCfg);
}

/*****************************************************************************
 函 数 名  : MTC_SetRatCfgByModemId
 功能描述  : 根据ModemId,设置当前Modem的接入制式
 输入参数  : enModemId                          -- Modem ID
             MTC_RCM_MODEM_RAT_CFG_ENUM_UINT16  -- 接入制式
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : h00313353
    修改内容   : Iteration 19 TAS
*****************************************************************************/
VOS_VOID MTC_SetRatCfgByModemId(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_MODEM_RAT_CONFIG_STRU          *pstRatCfg
)
{
    PS_MEM_CPY(MTC_GetRatCfgByModemId(enModemId), pstRatCfg, sizeof(MTC_MODEM_RAT_CONFIG_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : MTC_GetOutSideModemCtxAddr
 功能描述  : 获取外置MODEM信息上下文地址
 输入参数  : 内部接口，enModemId 由调用者保证modemId的有效性
 输出参数  : 无
 返 回 值  : MTC_OUTSIDE_MODEM_INFO_STRU* MODEM信息上下文地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月26日
    作    者   : j00174725
    修改内容   : K3V3 多模多天线特性
*****************************************************************************/
MTC_OUTSIDE_MODEM_INFO_STRU* MTC_GetOutSideModemCtxAddr(
    MTC_OUTSIDE_MODEM_ENUM_UINT16       enModemId
)
{
    return &(MTC_GetCtxAddr()->astOutSideModemInfo[enModemId]);
}


/*****************************************************************************
 函 数 名  : MTC_SetOutSideCsConnStateInfo
 功能描述  : 设置外置modem CS连接状态
 输入参数  : enModemId            -- 外置Modem ID
             enConnSt             -- 连接状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月16日
    作    者   : j00174725
    修改内容   : K3V3 多模多天线特性
*****************************************************************************/
VOS_VOID MTC_SetOutSideCsConnStateInfo(
    MTC_OUTSIDE_MODEM_ENUM_UINT16       enModemId,
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enConnSt
)
{
    MTC_GetOutSideModemCtxAddr(enModemId)->stConnStateInfo.enCsSrvConnState = enConnSt;
}

/*****************************************************************************
 函 数 名  : MTC_GetOutSideCsConnStateInfo
 功能描述  : 获取CS连接状态
 输入参数  : enModemId            -- 外置Modem ID
 输出参数  : 无
 返 回 值  : TAF_MTC_SRV_CONN_STATE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月16日
    作    者   : j00174725
    修改内容   : K3V3 多模多天线特性
*****************************************************************************/
TAF_MTC_SRV_CONN_STATE_ENUM_UINT8 MTC_GetOutSideCsConnStateInfo(
    MTC_OUTSIDE_MODEM_ENUM_UINT16       enModemId
)
{
    return MTC_GetOutSideModemCtxAddr(enModemId)->stConnStateInfo.enCsSrvConnState;
}

/*****************************************************************************
 函 数 名  : MTC_SetOutSidePsConnStateInfo
 功能描述  : 设置外置modem PS连接状态
 输入参数  : enModemId            -- 外置Modem ID
             enConnSt             -- 连接状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月16日
    作    者   : j00174725
    修改内容   : K3V3 多模多天线特性
*****************************************************************************/
VOS_VOID MTC_SetOutSidePsConnStateInfo(
    MTC_OUTSIDE_MODEM_ENUM_UINT16       enModemId,
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enConnSt
)
{
    MTC_GetOutSideModemCtxAddr(enModemId)->stConnStateInfo.enPsSrvConnState = enConnSt;
}

/*****************************************************************************
 函 数 名  : MTC_GetOutSidePsConnStateInfo
 功能描述  : 获取CS连接状态
 输入参数  : enModemId            -- 外置Modem ID
 输出参数  : 无
 返 回 值  : TAF_MTC_SRV_CONN_STATE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月16日
    作    者   : j00174725
    修改内容   : K3V3 多模多天线特性
*****************************************************************************/
TAF_MTC_SRV_CONN_STATE_ENUM_UINT8 MTC_GetOutSidePsConnStateInfo(
    MTC_OUTSIDE_MODEM_ENUM_UINT16       enModemId
)
{
    return MTC_GetOutSideModemCtxAddr(enModemId)->stConnStateInfo.enPsSrvConnState;
}

/*****************************************************************************
 函 数 名  : MTC_SetOutSideModemPowerState
 功能描述  : 设置外置modem 开关机状态
 输入参数  : enModemId            -- 外置Modem ID
             enPowerStatus        -- 开关机状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月16日
    作    者   : j00174725
    修改内容   : K3V3 多模多天线特性
*****************************************************************************/
VOS_VOID MTC_SetOutSideModemPowerState(
    MTC_OUTSIDE_MODEM_ENUM_UINT16       enModemId,
    MTC_MODEM_POWER_STATE_ENUM_UINT8    enPowerStatus
)
{
    MTC_GetOutSideModemCtxAddr(enModemId)->enPowerState = enPowerStatus;
}

/*****************************************************************************
 函 数 名  : MTC_GetOutSideModemPowerState
 功能描述  : 获取外置modem开关机状态
 输入参数  : enModemId            -- 外置Modem ID
 输出参数  : 无
 返 回 值  : MTC_MODEM_POWER_STATE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月16日
    作    者   : j00174725
    修改内容   : K3V3 多模多天线特性
*****************************************************************************/
MTC_MODEM_POWER_STATE_ENUM_UINT8 MTC_GetOutSideModemPowerState(
    MTC_OUTSIDE_MODEM_ENUM_UINT16       enModemId
)
{
    return MTC_GetOutSideModemCtxAddr(enModemId)->enPowerState;
}

/*****************************************************************************
 函 数 名  : MTC_SetOutSideModemUsimmState
 功能描述  : 设置外置modem 卡状态
 输入参数  : enModemId            -- 外置Modem ID
             enUsimmStatus        -- 卡状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月16日
    作    者   : j00174725
    修改内容   : K3V3 多模多天线特性
*****************************************************************************/
VOS_VOID MTC_SetOutSideModemUsimmState(
    MTC_OUTSIDE_MODEM_ENUM_UINT16           enModemId,
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16   enUsimmStatus
)
{
    MTC_GetOutSideModemCtxAddr(enModemId)->enUsimmState = enUsimmStatus;
}

/*****************************************************************************
 函 数 名  : MTC_GetOutSideModemUsimmState
 功能描述  : 获取外置modem卡状态
 输入参数  : enModemId            -- 外置Modem ID
 输出参数  : 无
 返 回 值  : TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月16日
    作    者   : j00174725
    修改内容   : K3V3 多模多天线特性
*****************************************************************************/
TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16 MTC_GetOutSideModemUsimmState(
    MTC_OUTSIDE_MODEM_ENUM_UINT16       enModemId
)
{
    return MTC_GetOutSideModemCtxAddr(enModemId)->enUsimmState;
}

/* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, End */

/*****************************************************************************
 函 数 名  : MTC_GetModemGsmCellInfoEx
 功能描述  : 获取Modem GSM小区扩展信息
 输入参数  : MODEM_ID_ENUM_UINT16 enModemId
 输出参数  : 无
 返 回 值  : MTC_GSM_CELLINFO_EX_STRU *
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月17日
    作    者   : l00198894
    修改内容   : 新增函数
*****************************************************************************/
MTC_GSM_CELLINFO_EX_STRU* MTC_GetModemGsmCellInfoEx(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(MTC_GetCtxAddr()->astModemInfo[enModemId].stGsmCellInfoEx);
}

/*****************************************************************************
 函 数 名  : MTC_GetCurrentTcStatus
 功能描述  : 获取TAS环回测试状态
 输入参数  : 内部接口，enModemId 由调用者保证modemId的有效性
 输出参数  : 无
 返 回 值  : MTC_NAS_TC_STATUS_ENUM_UINT16* 环回测试状态地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月15日
    作    者   : wx270776
    修改内容   : 新增函数
  2.日    期   : 2015年7月20日
    作    者   : zwx247453
    修改内容   : 3 modem TAS
*****************************************************************************/
MTC_RCM_TC_STATUS_ENUM_UINT16 MTC_GetCurrentTcStatus(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return MTC_GetCtxAddr()->astModemInfo[enModemId].enTcStatus;
}

/*****************************************************************************
 函 数 名  : MTC_SetCurrentTcStatus
 功能描述  : 更新TAS环回测试状态
 输入参数  : MTC_NAS_TC_STATUS_ENUM_UINT16       enTcStatus
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月15日
    作    者   : wx270776
    修改内容   : 新增函数
  2.日    期   : 2015年7月20日
    作    者   : zwx247453
    修改内容   : 3 modem TAS
*****************************************************************************/
VOS_VOID MTC_SetCurrentTcStatus(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_RCM_TC_STATUS_ENUM_UINT16       enTcStatus
)
{
    MTC_GetCtxAddr()->astModemInfo[enModemId].enTcStatus = enTcStatus;

    return;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

