/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasCcb.c
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年06月27日
  功能描述   : NAS 1x&evdo的全局变量管理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年06月27日
    作    者   : y00245242
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasCcb.h"
#include  "cas_1x_control_initialstate_nas_pif.h"
#include  "NasMntn.h"
#include  "msp_diag_comm.h"
#include  "Nas_Mem.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_CCB_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
CNAS_CCB_MODEM_PID_TAB_STRU        g_astCnasCcbModemPidTab[] = {{I0_UEPS_PID_MSCC,           I1_UEPS_PID_MSCC},
                                                                {I0_WUEPS_PID_TAF,           I1_WUEPS_PID_TAF},
                                                                {I0_UEPS_PID_XSMS,           I1_UEPS_PID_XSMS},
                                                                {I0_WUEPS_PID_USIM,          I1_WUEPS_PID_USIM}
                                                               };
#endif



/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
CNAS_CCB_CTX_STRU                       g_stCnasCcbCtx;




/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958 */
/*****************************************************************************
 函 数 名  : CNAS_CCB_GetCcbCtx
 功能描述  : 获取当前CCb的CTX
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前CCB的CTX
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年7月15日
   作    者   : h00246512
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_CCB_CTX_STRU*  CNAS_CCB_GetCcbCtxAddr( VOS_VOID )
{
    return &(g_stCnasCcbCtx);
}


/*****************************************************************************
 函 数 名  : CNAS_CCB_InitUIMID
 功能描述  : 初始化UIMID相关参数
 输入参数  : CNAS_CCB_UIMID_STRU                *pstUIMID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年05月30日
   作    者   : y00346957
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_CCB_InitUIMID(VOS_VOID)
{
    CNAS_CCB_UIMID_STRU                 *pstUIMID = VOS_NULL_PTR;
    VOS_UINT32                           i;

    pstUIMID = CNAS_CCB_GetUIMID();

    for (i = 0; i < CNAS_CCB_EFRUIMID_OCTET_LEN_EIGHT; i++)
    {
        pstUIMID->aucEFRUIMID[i] = 0xff;
    }

    /* the first byte EFRUIMID indicates the byte num of UIMID value,if read length fail,
        set the UIMID length to 0, namely invalid UIMID */
    pstUIMID->aucEFRUIMID[0] = 0;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_InitEsnMeidMeInfo
 功能描述  : 初始化ESNMEIDME相关参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年09月30日
   作    者   : y00307564
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_CCB_InitEsnMeidMeInfo(VOS_VOID)
{
    CNAS_CCB_ESNMEIDME_INFO_STRU       *pstEsnMeidMeInfo = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstEsnMeidMeInfo = CNAS_CCB_GetEsnMeidMeInfoAddr();

    for (i = 0; i < CNAS_CCB_ESN_OCTET_LEN; i++)
    {
        pstEsnMeidMeInfo->u.aucEsn[i] = 0xFF;
    }

    for (i = 0; i < CNAS_CCB_MEID_OCTET_LEN; i++)
    {
        pstEsnMeidMeInfo->u.aucMeid[i] = 0xFF;
    }

    pstEsnMeidMeInfo->enEsnMeidType = CNAS_CCB_ESN_MEID_TYPE_BUTT;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_InitHrpdAccessAuthInfo
 功能描述  : 初始化HrpdUppid相关参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年09月30日
   作    者   : y00307564
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_CCB_InitHrpdAccessAuthInfo(VOS_VOID)
{
    CNAS_CCB_HRPD_ACCESS_AUTH_INFO_STRU                    *pstHrpdAccessAuthInfo = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    pstHrpdAccessAuthInfo     = CNAS_CCB_GetHrpdAccesAuthInfoAddr();

    NAS_MEM_SET_S(pstHrpdAccessAuthInfo, sizeof(CNAS_CCB_HRPD_ACCESS_AUTH_INFO_STRU), 0, sizeof(CNAS_CCB_HRPD_ACCESS_AUTH_INFO_STRU));

    for (i = 0; i < CNAS_CCB_MAX_AUTHDATA_USERNAME_LEN; i++)
    {
        pstHrpdAccessAuthInfo->aucAccessAuthUserName[i] = 0xFF;
    }

    pstHrpdAccessAuthInfo->ucAccessAuthAvailFlag  = VOS_FALSE;
    pstHrpdAccessAuthInfo->ucAccessAuthUserNameLen = 0;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_InitCcbCtx
 功能描述  : 初始化CCB上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年7月15日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2015年5月30日
   作    者   : y00346957
   修改内容   : 增加对卡信息中的UIMID的初始化

*****************************************************************************/
VOS_VOID CNAS_CCB_InitCcbCtx(VOS_VOID)
{
    CNAS_CCB_CTX_STRU                   *pstCcbCtx = VOS_NULL_PTR;

    pstCcbCtx = CNAS_CCB_GetCcbCtxAddr();

    NAS_MEM_SET_S(pstCcbCtx, sizeof(CNAS_CCB_CTX_STRU), 0, sizeof(CNAS_CCB_CTX_STRU));

    /* To Do: 这里暂时初始化为与AS相同值6，后续待AS增加NV后，使用NV配置值 */
    pstCcbCtx->stNwInfo.ucPRevInUse                 = P_REV_IN_USE_6;

    pstCcbCtx->stCallInfoCfg.ucIsMtCallInRoamingAcc = VOS_TRUE;

    pstCcbCtx->stNwInfo.enCasSta    = CNAS_CCB_1X_CAS_STATE_BUTT;

    pstCcbCtx->stNwInfo.enCasSubSta    = CNAS_CCB_1X_CAS_SUB_STATE_ENUM_BUTT;
    pstCcbCtx->stNwInfo.enProtocolRev  = CNAS_CCB_1X_CAS_P_REV_ENUM_BUTT;

    pstCcbCtx->stCustomCfg.ucPowerOffCampOnCtrlFlg = VOS_FALSE;

    CNAS_CCB_InitHomeSidNidList(&(pstCcbCtx->stHomeSidNidList));

    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE, CNAS_CCB_1X_SO_TYPE_LOOPBACK);
    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE, CNAS_CCB_1X_SO_TYPE_VOICE);
    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE, CNAS_CCB_1X_SO_TYPE_PS);
    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE, CNAS_CCB_1X_SO_TYPE_SMS);

    CNAS_CCB_Set1XRfAvailFlg(VOS_TRUE);

    CNAS_CCB_InitUIMID();

    CNAS_CCB_InitIccId();

    CNAS_CCB_SetCurrPsRatType(CNAS_CCB_PS_RATTYPE_NULL);
    CNAS_CCB_SetPrevRatType(CNAS_CCB_PS_RATTYPE_NULL);

    CNAS_CCB_InitMntnInfo(&(pstCcbCtx->stMntnInfo));

    /* 设置当前计数器数量为0 */
    CNAS_CCB_Set1XCallExistCount((VOS_UINT8)VOS_FALSE);

    CNAS_CCB_SetHomeSidNidDependOnPrlFlg(VOS_FALSE);

    CNAS_CCB_InitCdmaStandardChannels(&(pstCcbCtx->stCdmaStandardChan));

    CNAS_CCB_InitEsnMeidMeInfo();
    CNAS_CCB_InitHrpdAccessAuthInfo();

    CNAS_CCB_SetCur1XSrvStatus(CNAS_CCB_SERVICE_STATUS_NO_SERVICE);
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_SetCsimCardStatus
 功能描述  : 设置CCB中保存的卡状态信息
 输入参数  : enCardStatus - 卡状态信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年7月14日
   作    者   : h00246512
   修改内容   : 新生成函数
 2.日    期   : 2015年06月04日
   作    者   : z00316370
   修改内容   : 更改变量名

*****************************************************************************/
VOS_VOID CNAS_CCB_SetCsimCardStatus(
    CNAS_CCB_CARD_STATUS_ENUM_UINT8     enCsimCardStatus
)
{
    CNAS_CCB_GetCcbCtxAddr()->stCardInfo.enCsimCardStatus = enCsimCardStatus;
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_GetCardStatus
 功能描述  : 获取CCB中保存的卡状态信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的卡状态信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年7月14日
   作    者   : h00246512
   修改内容   : 新生成函数
 2.日    期   : 2015年06月04日
   作    者   : z00316370
   修改内容   : 更改变量名

*****************************************************************************/
CNAS_CCB_CARD_STATUS_ENUM_UINT8 CNAS_CCB_GetCsimCardStatus( VOS_VOID )
{
    return CNAS_CCB_GetCcbCtxAddr()->stCardInfo.enCsimCardStatus;
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_GetCasCardStatus
 功能描述  : 获取发给当前CAS的卡状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : rrc格式的SIM卡状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月15日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16  CNAS_CCB_GetCasCardStatus(VOS_VOID)
{
    CNASITF_CARD_STATUS_ENUM_UINT16      enCardStatus;

    /* UIM卡存在 */
    if (CNAS_CCB_CARD_STATUS_UIM_PRESENT  == CNAS_CCB_GetCsimCardStatus())
    {
        enCardStatus = CNASITF_CARD_STATUS_UIM_PRESENT;
    }
    /* CSIM卡存在 */
    else if (CNAS_CCB_CARD_STATUS_CSIM_PRESENT  == CNAS_CCB_GetCsimCardStatus())
    {
        enCardStatus = CNASITF_CARD_STATUS_CSIM_PRESENT;
    }
    else
    {
        enCardStatus = CNASITF_CARD_STATUS_ABSENT;
    }

    return enCardStatus;
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_GetCcbNwInfoAddr
 功能描述  : 获取网络信息地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前网络信息的首地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年9月15日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_CCB_NW_INFO_STRU* CNAS_CCB_GetCcbNwInfoAddr(VOS_VOID)
{
    return &(CNAS_CCB_GetCcbCtxAddr()->stNwInfo);
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_GetConcurrentSupportedFlag
 功能描述  : 获取并发业务支持标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  --支持
             VOS_FALSE --不支持
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月09日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_CCB_GetConcurrentSupportedFlag(VOS_VOID)
{
    /* 获取并发业务支持标志 */
    return (CNAS_CCB_GetCcbNwInfoAddr()->ucConcurrentSupported);
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_SetConcurrentSupportedFlag
 功能描述  : 保存基站并发业务支持标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  --支持
             VOS_FALSE --不支持
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月09日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_CCB_SetConcurrentSupportedFlag(
    VOS_UINT8                           ucConcurrentSupported
)
{
    /* 更新基站并发业务支持标志 */
    CNAS_CCB_GetCcbNwInfoAddr()->ucConcurrentSupported = ucConcurrentSupported;
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_GetPRevInUse
 功能描述  : 获取当前使用的协议版本
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ucPRevInUse -- 返回当前的协议使用版本

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月09日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_CCB_GetPRevInUse(VOS_VOID)
{
    /* 获取协议使用版本 */
    return (CNAS_CCB_GetCcbNwInfoAddr()->ucPRevInUse);
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_SetPRevInUse
 功能描述  : 保存当前使用的协议版本号
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ucPRevInUse -- 返回当前的协议使用版本

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月09日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_CCB_SetPRevInUse(
    VOS_UINT8                           ucPRevInUse
)
{
    /* 更新当前使用的协议版本号 */
    CNAS_CCB_GetCcbNwInfoAddr()->ucPRevInUse = ucPRevInUse;
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_GetCasState
 功能描述  : 获取当前CAS的状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : enCasSta -- 返回当前CAS的状态

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月18日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_CCB_1X_CAS_STATE_ENUM_UINT8 CNAS_CCB_GetCasState(VOS_VOID)
{
    /* 获取协议使用版本 */
    return (CNAS_CCB_GetCcbNwInfoAddr()->enCasSta);
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_SetCasState
 功能描述  : 保存当前CAS上报的状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : enSta -- CAS上报的状态

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月18日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_CCB_SetCasState(
    CNAS_CCB_1X_CAS_STATE_ENUM_UINT8    enSta
)
{
    CNAS_CCB_GetCcbNwInfoAddr()->enCasSta = enSta;
}



/*****************************************************************************
 函 数 名  : CNAS_CCB_SetMtCallInRoamingAccFlg
 功能描述  : 设置CCB中保存的MtCallInRoamingAcc信息
 输入参数  : ucIsMtCallInRoamingAcc - VOS_UINT8
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年9月15日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_CCB_SetMtCallInRoamingAccFlg(
    VOS_UINT8                           ucIsMtCallInRoamingAcc
)
{
    CNAS_CCB_GetCcbCtxAddr()->stCallInfoCfg.ucIsMtCallInRoamingAcc = ucIsMtCallInRoamingAcc;
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_GetMtCallInRoamingAccFlg
 功能描述  : 获取CCB中保存的MtCallInRoamingAcc信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CCB中保存的MtCallInRoamingAcc信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年7月14日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_CCB_GetMtCallInRoamingAccFlg( VOS_VOID )
{
    return CNAS_CCB_GetCcbCtxAddr()->stCallInfoCfg.ucIsMtCallInRoamingAcc;
}


/*****************************************************************************
 函 数 名  : CNAS_CCB_SetPowerOffCampOnCtrlFlg
 功能描述  : 设置关机驻留控制标记
 输入参数  : 关机驻留标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年10月23日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_CCB_SetPowerOffCampOnCtrlFlg(
    VOS_UINT8                           ucPowerOffCampOnFlg
)
{
    CNAS_CCB_GetCcbCtxAddr()->stCustomCfg.ucPowerOffCampOnCtrlFlg = ucPowerOffCampOnFlg;
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_GetPowerOffCampOnCtrlFlg
 功能描述  : 获取关机驻留控制标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 关机驻留控制标记
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年10月23日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_CCB_GetPowerOffCampOnCtrlFlg( VOS_VOID )
{
    return CNAS_CCB_GetCcbCtxAddr()->stCustomCfg.ucPowerOffCampOnCtrlFlg;
}


/*****************************************************************************
 函 数 名  : CNAS_CCB_InitHomeSidNidList
 功能描述  : 初始化Home SID/NID list
 输入参数  : pstHomeSidNidList -- home sid/nid list指针
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月3日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_CCB_InitHomeSidNidList(
    CNAS_CCB_1X_HOME_SID_NID_LIST_STRU *pstHomeSidNidList
)
{
    pstHomeSidNidList->ucSysNum = 0;

    NAS_MEM_SET_S(&pstHomeSidNidList->astHomeSidNid[0],
                  CNAS_CCB_MAX_HOME_SID_NID_LIST * sizeof(CNAS_CCB_1X_HOME_SID_NID_STRU),
                  0,
                  CNAS_CCB_MAX_HOME_SID_NID_LIST * sizeof(CNAS_CCB_1X_HOME_SID_NID_STRU));
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_GetHomeSidNidList
 功能描述  : 获取HomeSidNid table首地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回HomeSidNid table首地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月31日
   作    者   : h00313353
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_CCB_1X_HOME_SID_NID_LIST_STRU* CNAS_CCB_GetHomeSidNidList(VOS_VOID)
{
    return &(CNAS_CCB_GetCcbCtxAddr()->stHomeSidNidList);
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_GetCasSubState
 功能描述  : 获取当前CAS的子状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : enCasSta -- 返回当前CAS的子状态

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月16日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_CCB_1X_CAS_SUB_STATE_ENUM_UINT8 CNAS_CCB_GetCasSubState(VOS_VOID)
{
    /* 获取CAS子状态 */
    return (CNAS_CCB_GetCcbNwInfoAddr()->enCasSubSta);
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_SetCasState
 功能描述  : 保存当前CAS上报的子状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : enSta -- CAS上报的状态

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月16日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_CCB_SetCasSubState(
    CNAS_CCB_1X_CAS_SUB_STATE_ENUM_UINT8                    enSubSta
)
{
    CNAS_CCB_GetCcbNwInfoAddr()->enCasSubSta = enSubSta;
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_GetHighProRev
 功能描述  : 获取当前手机支持的最高协议版本
 输入参数  : 无
 输出参数  : 无
 返 回 值  : enProtocolRev -- 返回当前支持的协议版本

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月16日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_CCB_1X_CAS_P_REV_ENUM_UINT8 CNAS_CCB_GetHighProRev(VOS_VOID)
{
    /* 获取CAS子状态 */
    return (CNAS_CCB_GetCcbNwInfoAddr()->enProtocolRev);
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_SetHighProRev
 功能描述  : 保存当前手机支持的最高协议版本
 输入参数  : 无
 输出参数  : 无
 返 回 值  : enProtocolRev -- CAS上报的协议版本

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月16日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_CCB_SetHighProRev(
    CNAS_CCB_1X_CAS_P_REV_ENUM_UINT8    enProtocolRev
)
{
    CNAS_CCB_GetCcbNwInfoAddr()->enProtocolRev = enProtocolRev;
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_Get1xReturnCause
 功能描述  : 获取CCB中保存的1x的returnCause值
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAS_CCB_1X_RETURN_CAUSE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月13日
    作    者   : m00312079
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_CCB_1X_RETURN_CAUSE_ENUM_UINT8 CNAS_CCB_Get1xReturnCause(VOS_VOID)
{
    return CNAS_CCB_GetCcbCtxAddr()->en1xReturnCause;
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_Set1xReturnCause
 功能描述  : 更新CCB中保存的returnCause值
 输入参数  : CNAS_CCB_1X_RETURN_CAUSE_ENUM_UINT8   en1xReturnCause
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月13日
    作    者   : m00312079
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_CCB_Set1xReturnCause(
    CNAS_CCB_1X_RETURN_CAUSE_ENUM_UINT8                     en1xReturnCause
)
{
    CNAS_CCB_GetCcbCtxAddr()->en1xReturnCause = en1xReturnCause;
}


/*****************************************************************************
 函 数 名  : CNAS_CCB_Get1xVoiceCallState
 功能描述  : 获取CCB中保存的1X呼叫状态
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAS_CCB_1X_CALL_STATE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : l00301449
    修改内容   : 新生成函数

  2.日    期   : 2015年7月21日
    作    者   : y00322978
    修改内容   : 获取语音callstate信息
*****************************************************************************/
CNAS_CCB_1X_CALL_STATE_ENUM_UINT8 CNAS_CCB_Get1xVoiceCallState(VOS_VOID)
{
    VOS_UINT32                          ulIndex;

    for (ulIndex = 0; ulIndex < CNAS_CCB_MNTN_1X_CALL_STATE_MAX_NUM; ulIndex++)
    {
        if (CNAS_CCB_1X_SO_TYPE_VOICE == CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[ulIndex].en1xSoType)
        {
            return CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[ulIndex].en1xCallState;
        }
    }
    return CNAS_CCB_1X_CALL_STATE_IDLE;
}
/*****************************************************************************
 函 数 名  : CNAS_CCB_Get1xPsCallState
 功能描述  : 获取ps业务callstate信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAS_CCB_1X_CALL_STATE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月21日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_CCB_1X_CALL_STATE_ENUM_UINT8 CNAS_CCB_Get1xPsCallState(
    VOS_VOID
)
{
    VOS_UINT32                          ulIndex;

    for (ulIndex = 0; ulIndex < CNAS_CCB_MNTN_1X_CALL_STATE_MAX_NUM; ulIndex++)
    {
        if (CNAS_CCB_1X_SO_TYPE_PS == CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[ulIndex].en1xSoType)
        {
            return CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[ulIndex].en1xCallState;
        }
    }
    return CNAS_CCB_1X_CALL_STATE_IDLE;
}
/*****************************************************************************
 函 数 名  : CNAS_CCB_Get1xPsCallState
 功能描述  : 获取SMS业务callstate信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAS_CCB_1X_CALL_STATE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月21日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_CCB_1X_CALL_STATE_ENUM_UINT8 CNAS_CCB_Get1xSmsCallState(
    VOS_VOID
)
{
    VOS_UINT32                          ulIndex;

    for (ulIndex = 0; ulIndex < CNAS_CCB_MNTN_1X_CALL_STATE_MAX_NUM; ulIndex++)
    {
        if (CNAS_CCB_1X_SO_TYPE_SMS== CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[ulIndex].en1xSoType)
        {
            return CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[ulIndex].en1xCallState;
        }
    }
    return CNAS_CCB_1X_CALL_STATE_IDLE;
}
/*****************************************************************************
 函 数 名  : CNAS_CCB_Set1xCallState
 功能描述  : 更新CCB中保存的1X呼叫状态
 输入参数  : CNAS_CCB_1X_CALL_STATE_ENUM_UINT8   en1xCallState
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : l00301449
    修改内容   : 新生成函数

  2.日    期   : 2015年7月21日
    作    者   : y00322978
    修改内容   : 记录不同so的call state状态
*****************************************************************************/
VOS_VOID CNAS_CCB_Set1xCallState(
    CNAS_CCB_1X_CALL_STATE_ENUM_UINT8                       en1xCallState,
    CNAS_CCB_1X_SO_TYPE_ENUM_UINT8                          en1xSoType
)
{
    switch (en1xSoType)
    {
        case CNAS_CCB_1X_SO_TYPE_VOICE:
            CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[0].en1xSoType    = en1xSoType;
            CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[0].en1xCallState = en1xCallState;
            break;
        case CNAS_CCB_1X_SO_TYPE_SMS:
            CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[1].en1xSoType    = en1xSoType;
            CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[1].en1xCallState = en1xCallState;
            break;
        case CNAS_CCB_1X_SO_TYPE_PS:
            CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[2].en1xSoType    = en1xSoType;
            CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[2].en1xCallState = en1xCallState;
            break;
        case CNAS_CCB_1X_SO_TYPE_LOOPBACK:
            CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[3].en1xSoType    = en1xSoType;
            CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[3].en1xCallState = en1xCallState;
            break;
        default :
            CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[3].en1xSoType    = en1xSoType;
            CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[3].en1xCallState = en1xCallState;
    }


}




/*****************************************************************************
 函 数 名  : CNAS_CCB_Set1XRfAvailFlg
 功能描述  : 设置当前X模射频资源可用标志
 输入参数  : uc1XRfAvail: RF资源可用标志
             VOS_TRUE   : 可用
             VOS_FALSE  : 不可用
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_CCB_Set1XRfAvailFlg(
    VOS_UINT8                           uc1XRfAvailFlg
)
{
    CNAS_CCB_GetCcbCtxAddr()->stNwInfo.uc1XRfAvailFlg = uc1XRfAvailFlg;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_Get1XRfAvailFlg
 功能描述  : 获取当前X模射频资源可用标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
             VOS_TRUE   : 可用
             VOS_FALSE  : 不可用
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_CCB_Get1XRfAvailFlg( VOS_VOID )
{
    return CNAS_CCB_GetCcbCtxAddr()->stNwInfo.uc1XRfAvailFlg;
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_GetUIMID
 功能描述  : 获取CcbCtx中card info的UIMID
 输入参数  : 无
 输出参数  : 无
 返 回 值  : UIMID结构体
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年05月30日
   作    者   : y00346957
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_CCB_UIMID_STRU* CNAS_CCB_GetUIMID(VOS_VOID)
{
    return &(CNAS_CCB_GetCcbCtxAddr()->stCardInfo.stUIMID);
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_GetEsnMeidMeInfoAddr
 功能描述  : 获取CcbCtx中card info的esn meid me
 输入参数  : 无
 输出参数  : 无
 返 回 值  : esn meid me结构体
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年09月30日
   作    者   : y00307564
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_CCB_ESNMEIDME_INFO_STRU* CNAS_CCB_GetEsnMeidMeInfoAddr(VOS_VOID)
{
    return &(CNAS_CCB_GetCcbCtxAddr()->stCardInfo.stEsnMeidMe);
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_GetHrpdAccesAuthInfoAddr
 功能描述  : 获取CcbCtx中hrpd接入鉴权用户名
 输入参数  : 无
 输出参数  : 无
 返 回 值  : hrpd upp id结构体
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年09月30日
   作    者   : y00307564
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_CCB_HRPD_ACCESS_AUTH_INFO_STRU* CNAS_CCB_GetHrpdAccesAuthInfoAddr(VOS_VOID)
{
    return &(CNAS_CCB_GetCcbCtxAddr()->stCardInfo.stHrpdAccessAuthInfo);
}


/*****************************************************************************
 函 数 名  : CNAS_CCB_SetModemId
 功能描述  : 设置与C模对接的modemId
 输入参数  : enModemId              : modemId
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月21日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_CCB_SetCdmaModeModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    CNAS_CCB_GetCcbCtxAddr()->stModemInfo.enCdmaModeModemId = enModemId;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_GetCdmaModeModemId
 功能描述  : 获取与C模对接的modemIds
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MODEM_ID_0:modem0
             MODEM_ID_1:modem1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月21日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
MODEM_ID_ENUM_UINT16 CNAS_CCB_GetCdmaModeModemId( VOS_VOID )
{
    return CNAS_CCB_GetCcbCtxAddr()->stModemInfo.enCdmaModeModemId;
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_GetPidFromModemId
 功能描述  : 获取实际发送的PID
 输入参数  : MODEM_ID_ENUM_UINT16                enModemId,
             VOS_UINT32                          ulRcvPid
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_CCB_ConvertPidBasedOnModemId(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT32                          ulRcvPid
)
{
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    VOS_UINT32                          i;

    /* modem 1上ulRcvPid对应的pid */
    if (MODEM_ID_0 != enModemId)
    {
        for (i = 0; i < (sizeof(g_astCnasCcbModemPidTab)/sizeof(CNAS_CCB_MODEM_PID_TAB_STRU)); i++)
        {
            if (ulRcvPid == g_astCnasCcbModemPidTab[i].ulModem0Pid)
            {
                return g_astCnasCcbModemPidTab[i].ulModem1Pid;
            }
        }

        /* 如果出现找不到对应的PID时，有可能是X模内部模块间发消息 */
    }
#endif

    return ulRcvPid;
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_GetModem0Pid
 功能描述  : 获取modem0相应的PID
 输入参数  : MODEM_ID_ENUM_UINT16                enModemId,
             VOS_UINT32                          ulRcvPid
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_CCB_GetModem0Pid(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT32                          ulSenderPid
)
{
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    VOS_UINT32                          i;

    /* modem 1上ulRcvPid对应的pid */
    if (MODEM_ID_0 != enModemId)
    {
        for (i = 0; i < (sizeof(g_astCnasCcbModemPidTab)/sizeof(CNAS_CCB_MODEM_PID_TAB_STRU)); i++)
        {
            if (ulSenderPid == g_astCnasCcbModemPidTab[i].ulModem1Pid)
            {
                return g_astCnasCcbModemPidTab[i].ulModem0Pid;
            }
        }

        /* 如果出现找不到对应的PID时，有可能是X模内部模块间发消息 */
    }
#endif

    return ulSenderPid;
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_GetCardIccIdAddr
 功能描述  : 获取CcbCtx中的卡中保存的IccId
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CcbCtx中的IccId地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年06月03日
   作    者   : y00307564
   修改内容   : 新生成函数
 2.日    期   : 2015年10月19日
   作    者   : y00307564
   修改内容   : DTS2015082403731修改
*****************************************************************************/
VOS_UINT8* CNAS_CCB_GetCardIccIdAddr(VOS_VOID)
{
    return CNAS_CCB_GetCcbCtxAddr()->stCardInfo.aucCardIccId;
}



/*****************************************************************************
 函 数 名  : CNAS_CCB_InitIccId
 功能描述  : 初始化ICCID相关参数
 输入参数  : CNAS_CCB_UIMID_STRU                *pstUIMID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年06月08日
   作    者   : y00307564
   修改内容   : 新生成函数
 2.日    期   : 2015年10月19日
   作    者   : y00307564
   修改内容   : DTS2015082403731修改
*****************************************************************************/
VOS_VOID CNAS_CCB_InitIccId(VOS_VOID)
{
    VOS_UINT8                           *pucCardIccId    = VOS_NULL_PTR;
    VOS_UINT32                           i;

    pucCardIccId = CNAS_CCB_GetCardIccIdAddr();

    for (i = 0; i < CNAS_CCB_ICCID_OCTET_LEN; i++)
    {
        pucCardIccId[i] = 0xFF;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_SetUsimCardStatus
 功能描述  : 设置CCB中保存的卡状态信息
 输入参数  : enCardStatus - 卡状态信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年06月04日
   作    者   : z00316370
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_CCB_SetUsimCardStatus(
    CNAS_CCB_CARD_STATUS_ENUM_UINT8     enUsimCardStatus
)
{
    CNAS_CCB_GetCcbCtxAddr()->stCardInfo.enUsimCardStatus = enUsimCardStatus;
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_GetUsimCardStatus
 功能描述  : 获取CCB中保存的卡状态信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MML中保存的卡状态信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年06月04日
   作    者   : z00316370
   修改内容   : 新生成函数

*****************************************************************************/
CNAS_CCB_CARD_STATUS_ENUM_UINT8 CNAS_CCB_GetUsimCardStatus( VOS_VOID )
{
    return CNAS_CCB_GetCcbCtxAddr()->stCardInfo.enUsimCardStatus;
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_GetCurrPsRatType
 功能描述  : 获取当前使用的ps rat type
 输入参数  : 无
 输出参数  : 无
 返 回 值  : enPRevInUse -- 返回当前的ps rat type

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月21日
    作    者   : f00279542
    修改内容   : 新生成函数
*****************************************************************************/
CNAS_CCB_PS_RATTYPE_ENUM_UINT32 CNAS_CCB_GetCurrPsRatType(VOS_VOID)
{
    /* 获取PS rat type */
    return (CNAS_CCB_GetCcbCtxAddr()->enCurrPsRatType);
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_SetCurrPsRatType
 功能描述  : 保存当前使用的ps rat type
             (only ehsm can call this function when receiving ID_APS_EHSM_PS_RAT_TYPE_NOTIFY )

 输入参数  : 无
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月21日
    作    者   : f00279542
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_CCB_SetCurrPsRatType(
    CNAS_CCB_PS_RATTYPE_ENUM_UINT32    enPsRatType
)
{
    /* 更新当前使用的ps rat type */
    CNAS_CCB_GetCcbCtxAddr()->enCurrPsRatType = enPsRatType;
}
/*****************************************************************************
 函 数 名  : CNAS_CCB_GetPrevPsRatType
 功能描述  : get previous ps rat type
 输入参数  : 无
 输出参数  : 无
 返 回 值  : enPRevInUse -- 返回当前的ps rat type

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月21日
    作    者   : f00279542
    修改内容   : 新生成函数
*****************************************************************************/
CNAS_CCB_PS_RATTYPE_ENUM_UINT32 CNAS_CCB_GetPrevPsRatType(VOS_VOID)
{
    /* 获取PS rat type */
    return (CNAS_CCB_GetCcbCtxAddr()->enPrevPsRatType);
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_SetPrevRatType
 功能描述  : set previous ps rat type
            (only ehsm can call this function when receiving ID_APS_EHSM_PS_RAT_TYPE_NOTIFY )
 输入参数  : 无
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月21日
    作    者   : f00279542
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_CCB_SetPrevRatType(
    CNAS_CCB_PS_RATTYPE_ENUM_UINT32     enPsRatType
)
{
    /* 更新当前使用的ps rat type */
    CNAS_CCB_GetCcbCtxAddr()->enPrevPsRatType = enPsRatType;
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_CovertReturnCause
 功能描述  : 将CNAS的returnCause枚举CNAS_CCB_1X_RETURN_CAUSE_ENUM_UINT8转换为
             CNAS_CAS_1X_RETURN_CAUSE_ENUM_UINT8
 输入参数  : CNAS_CCB_1X_RETURN_CAUSE_ENUM_UINT8   en1xReturnCause
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月13日
    作    者   : m00312079
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_CAS_1X_RETURN_CAUSE_ENUM_UINT8 CNAS_CCB_CovertReturnCause(
    CNAS_CCB_1X_RETURN_CAUSE_ENUM_UINT8   enCnas1xReturnCause
)
{
    CNAS_CAS_1X_RETURN_CAUSE_ENUM_UINT8   enCasReturnCause;

    switch (enCnas1xReturnCause)
    {
        case CNAS_CCB_1X_RETURN_CAUSE_NORMAL_ACCESS :
            enCasReturnCause = CNAS_CAS_1X_RETURN_CAUSE_NORMAL_ACCESS;
            break;

        case CNAS_CCB_1X_RETURN_CAUSE_SYSTEM_NOT_ACQ :
            enCasReturnCause = CNAS_CAS_1X_RETURN_CAUSE_SYSTEM_NOT_FOUND;
            break;

        case CNAS_CCB_1X_RETURN_CAUSE_PROTOCOL_MISMATCH :
            enCasReturnCause = CNAS_CAS_1X_RETURN_CAUSE_PROTOCOL_MISMATCH;
            break;

        case CNAS_CCB_1X_RETURN_CAUSE_REG_REJ :
            enCasReturnCause = CNAS_CAS_1X_RETURN_CAUSE_REGISTRATION_REJECTION;
            break;

        case CNAS_CCB_1X_RETURN_CAUSE_WRONG_SID :
            enCasReturnCause = CNAS_CAS_1X_RETURN_CAUSE_WRONG_SID;
            break;

        case CNAS_CCB_1X_RETURN_CAUSE_WRONG_NID :
            enCasReturnCause = CNAS_CAS_1X_RETURN_CAUSE_WRONG_NID;
            break;

        default:
            enCasReturnCause = CNAS_CAS_1X_RETURN_CAUSE_BUTT;
            break;
    }

    return enCasReturnCause;
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_Set1XMtCallExistFlg
 功能描述  : 设置当前是否处于被叫状态的标识
 输入参数  : uc1XCallExistCount: 是否存在被叫的标识
             VOS_TRUE   : 被叫存在
             VOS_FALSE  : 被叫不存在
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月02日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_CCB_Set1XCallExistCount(
    VOS_UINT8                           uc1XCallExistCount
)
{
    CNAS_CCB_GetCcbCtxAddr()->uc1XCallExistCount = uc1XCallExistCount;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_Get1XMtCallExistFlg
 功能描述  : 获取当前是否处于被叫状态的标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
             VOS_TRUE   : 存在被叫
             VOS_FALSE  : 不存在被叫
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月02日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_CCB_Get1XCallExistCount( VOS_VOID )
{
    return (CNAS_CCB_GetCcbCtxAddr()->uc1XCallExistCount);
}


/*****************************************************************************
 函 数 名  : CNAS_CCB_GetHomeSidNidMostPriFlg
 功能描述  : 获取CCB中保存的home sid/nid最优选标记
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月3日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 CNAS_CCB_GetHomeSidNidDependOnPrlFlg(VOS_VOID)
{
    return CNAS_CCB_GetCcbCtxAddr()->ucHomeSidNidDependOnPrlFlg;
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_SetHomeSidNidMostPriFlg
 功能描述  : 更新CCB中HOME SID/NID是不是最优选的标记
 输入参数  : VOS_UINT8                           ucFlg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月3日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_CCB_SetHomeSidNidDependOnPrlFlg(
    VOS_UINT8                           ucFlg
)
{
    CNAS_CCB_GetCcbCtxAddr()->ucHomeSidNidDependOnPrlFlg = ucFlg;
}


/*****************************************************************************
 函 数 名  : CNAS_CCB_GetOperLockWhiteSidList
 功能描述  : 获取CCB中保存的白名单列表
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAS_CCB_OPER_LOCK_WHITE_SID_LIST_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月3日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_CCB_OPER_LOCK_SYS_WHITE_LIST_STRU* CNAS_CCB_GetOperLockSysWhiteList(VOS_VOID)
{
    return &(CNAS_CCB_GetCcbCtxAddr()->stOperLockSysWhiteList);
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_GetCTCCCustomizeFreqList
 功能描述  : 获取CCB中中国电信自定义频点列表
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAS_CCB_CTCC_CUSTOMIZE_FREQ_LIST_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月3日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_CCB_CTCC_CUSTOMIZE_FREQ_LIST_STRU* CNAS_CCB_GetCTCCCustomizeFreqList(VOS_VOID)
{
    return &(CNAS_CCB_GetCcbCtxAddr()->stCTCCCustInfo.stCustFreqList);
}


/*****************************************************************************
 函 数 名  : CNAS_CCB_InitMntnInfo
 功能描述  : 初始化CCB全局变量
 输入参数  : pstMntnInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_CCB_InitMntnInfo(
    CNAS_CCB_MNTN_CTX_STRU             *pstMntnInfo
)
{
    NAS_MEM_SET_S(pstMntnInfo, sizeof(CNAS_CCB_MNTN_CTX_STRU), 0x00, sizeof(CNAS_CCB_MNTN_CTX_STRU));
    return;
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_GetCdmaStandardChannels
 功能描述  : 获取CCB中cdma标准频段
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAS_CCB_CDMA_STANDARD_CHANNELS_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月14日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_CCB_CDMA_STANDARD_CHANNELS_STRU* CNAS_CCB_GetCdmaStandardChannels(VOS_VOID)
{
    return &(CNAS_CCB_GetCcbCtxAddr()->stCdmaStandardChan);
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_InitCdmaStandardChannels
 功能描述  : 初始化CCB中cdma标准频段
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月14日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_CCB_InitCdmaStandardChannels(
    CNAS_CCB_CDMA_STANDARD_CHANNELS_STRU                   *pstCdmaStandardChan
)
{
    /* 初始化默认频点为协议定义的频点 */
    /* 参考CDG 130 4.4.3章节Table 4-8中的定义 */
    pstCdmaStandardChan->usPrimaryA   = 283;

    pstCdmaStandardChan->usSecondaryA = 691;

    pstCdmaStandardChan->usPrimaryB   = 384;

    pstCdmaStandardChan->usSecondaryB = 777;
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_Judge1XSoType
 功能描述  : SO转成相应的服务类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CNAS_CCB_1X_SO_TYPE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月21日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_CCB_1X_SO_TYPE_ENUM_UINT8 CNAS_CCB_ConvertSoToServiceType(
    CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16                  en1xSo
)
{
    CNAS_CCB_1X_SO_TYPE_ENUM_UINT8      en1xSoType;

    switch (en1xSo)
    {
        case CAS_CNAS_1X_SO_3_EVRC:
        case CAS_CNAS_1X_SO_17_VOICE_13K:
        case CAS_CNAS_1X_SO_68_EVRC_B:
        case CAS_CNAS_1X_SO_73_EVRC_NW:
        case CAS_CNAS_1X_SO_18_OTASP:
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
        case CAS_CNAS_1X_SO_32944_VOICE_ENCRYPT:
#endif
            en1xSoType =  CNAS_CCB_1X_SO_TYPE_VOICE;
            break;
        case CAS_CNAS_1X_SO_7_PPP_PKT_DATA:
        case CAS_CNAS_1X_SO_33_PPP_PKT_DATA_CDMA2K:
            en1xSoType =  CNAS_CCB_1X_SO_TYPE_PS;
            break;
        case CAS_CNAS_1X_SO_6_SMS_RS1:
        case CAS_CNAS_1X_SO_14_SMS_RS2:
            en1xSoType =  CNAS_CCB_1X_SO_TYPE_SMS;
            break;
        case CAS_CNAS_1X_SO_2_LOOPBACK:
        case CAS_CNAS_1X_SO_9_LOOPBACK:
        case CAS_CNAS_1X_SO_54_MARKOV:
        case CAS_CNAS_1X_SO_55_LOOPBACK:
        case CAS_CNAS_1X_SO_74_LOOPBACK:
        case CAS_CNAS_1X_SO_75_LOOPBACK:
            en1xSoType = CNAS_CCB_1X_SO_TYPE_LOOPBACK;
            break;

        case CAS_CNAS_1X_SO_35_LOC_SERV:
        case CAS_CNAS_1X_SO_36_LOC_SERV:
            en1xSoType = CNAS_CCB_1X_SO_TYPE_AGPS;
            break;

        default :
            en1xSoType =  CNAS_CCB_1X_SO_TYPE_LOOPBACK;
    }
    return en1xSoType;
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_GetCdmaOhmFreq
 功能描述  : 获取overheader频点
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAS_PRL_FREQENCY_CHANNEL_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月12日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_PRL_FREQENCY_CHANNEL_STRU* CNAS_CCB_GetCdmaOhmFreq(VOS_VOID)
{
    return &(CNAS_CCB_GetCcbCtxAddr()->stOhmFreq);
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_SetCdmaOhmFreq
 功能描述  : 设置overheader频点
 输入参数  : CNAS_PRL_FREQENCY_CHANNEL_STRU*
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月12日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_CCB_SetCdmaOhmFreq(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstOhmFreq
)
{
    CNAS_CCB_GetCcbCtxAddr()->stOhmFreq = *pstOhmFreq;
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_ClearCdmaOhmFreq
 功能描述  : 清除cdma overheader消息中的频点
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月12日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_CCB_ClearCdmaOhmFreq(VOS_VOID)
{
    CNAS_CCB_GetCcbCtxAddr()->stOhmFreq.enBandClass = 0;

    CNAS_CCB_GetCcbCtxAddr()->stOhmFreq.usChannel   = 0;
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_Set1xSysInfo
 功能描述  : CCB模块更新1x系统消息，包括Sid/nid/band/freq信息
 输入参数  : VOS_UINT16                          usSid
             VOS_UINT16                          usNid
             VOS_UINT16                          usBandClass
             VOS_UINT16                          usChannel
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月27日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_CCB_Set1xSysInfo(
    VOS_UINT16                          usSid,
    VOS_UINT16                          usNid,
    VOS_UINT16                          usBandClass,
    VOS_UINT16                          usChannel
)
{
    CNAS_CCB_GetCcbNwInfoAddr()->st1xSysInfo.usSid       = usSid;
    CNAS_CCB_GetCcbNwInfoAddr()->st1xSysInfo.usNid       = usNid;
    CNAS_CCB_GetCcbNwInfoAddr()->st1xSysInfo.usBandClass = usBandClass;
    CNAS_CCB_GetCcbNwInfoAddr()->st1xSysInfo.usChannel   = usChannel;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_Get1xSysInfo
 功能描述  : CCB提供1X系统消息的查询接口
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAS_CCB_1X_SYS_INFO_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月27日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_CCB_1X_SYS_INFO_STRU* CNAS_CCB_Get1xSysInfo(VOS_VOID)
{
    return &(CNAS_CCB_GetCcbNwInfoAddr()->st1xSysInfo);
}


/*****************************************************************************
 函 数 名  : CNAS_CCB_IsCurCallStateIdle
 功能描述  : 判断CCB中保存的1X呼叫状态是否为空闲态,仅当数组中所有成员的呼叫状态均为Idle时，
             返回TRUE,其余情况返回FALSE
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32: 返回TRUE表示当前没有呼叫业务，返回FALSE表示当前存在呼叫业务
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月30日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_CCB_IsCurCallStateIdle( VOS_VOID )
{
    VOS_UINT32                          ulIndex;
    CNAS_CCB_CTX_STRU                  *pstCcbCtx   = VOS_NULL_PTR;

    pstCcbCtx                           = CNAS_CCB_GetCcbCtxAddr();

    for (ulIndex = 0; ulIndex < CNAS_CCB_MNTN_1X_CALL_STATE_MAX_NUM; ulIndex++)
    {
        if (CNAS_CCB_1X_CALL_STATE_IDLE != pstCcbCtx->astMntn1xCallState[ulIndex].en1xCallState)
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}
/*****************************************************************************
 函 数 名  : CNAS_CCB_GetCur1XSrvInfo
 功能描述  : 获取当前1X服务信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAS_CCB_1X_SRV_INFO_STRU* 当前1X服务状态信息结构体指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年01月26日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_CCB_1X_SRV_INFO_STRU* CNAS_CCB_GetCur1XSrvInfo(VOS_VOID)
{
    return &(CNAS_CCB_GetCcbCtxAddr()->st1XSrvInfo);
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_GetCur1XSrvStatus
 功能描述  : 获取当前1X服务状态
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : CNAS_CCB_SERVICE_STATUS_ENUM_UINT32 当前1X服务状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年01月26日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_CCB_SERVICE_STATUS_ENUM_UINT32 CNAS_CCB_GetCur1XSrvStatus(VOS_VOID)
{
    CNAS_CCB_1X_SRV_INFO_STRU          *pst1XSrvInfo = VOS_NULL_PTR;

    pst1XSrvInfo = CNAS_CCB_GetCur1XSrvInfo();

    return pst1XSrvInfo->enCurSrvStatus;
}

/*****************************************************************************
 函 数 名  : CNAS_CCB_SetCur1XSrvStatus
 功能描述  : 设置当前1X服务状态
 输入参数  : enSrvStatus -- 服务状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年01月26日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_CCB_SetCur1XSrvStatus(
    CNAS_CCB_SERVICE_STATUS_ENUM_UINT32 enSrvStatus
)
{
    CNAS_CCB_1X_SRV_INFO_STRU          *pst1XSrvInfo = VOS_NULL_PTR;

    pst1XSrvInfo = CNAS_CCB_GetCur1XSrvInfo();

    CNAS_INFO_LOG1(UEPS_PID_XSD, "CNAS_CCB_SetCur1XSrvStatus:Cur SrvStatus: ", (VOS_UINT32)pst1XSrvInfo->enCurSrvStatus);

    pst1XSrvInfo->enCurSrvStatus = enSrvStatus;

    CNAS_INFO_LOG1(UEPS_PID_XSD, "CNAS_CCB_SetCur1XSrvStatus:Set SrvStatus To: ", (VOS_UINT32)pst1XSrvInfo->enCurSrvStatus);

    return;
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



