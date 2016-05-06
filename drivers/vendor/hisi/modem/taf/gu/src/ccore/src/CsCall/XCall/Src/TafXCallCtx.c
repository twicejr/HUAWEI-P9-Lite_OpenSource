/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXCallCtx.c
  版 本 号   : 初稿
  作    者   : l60609
  生成日期   : 2014年09月03日
  功能描述   : TAF X CALL上下文管理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年09月03日
    作    者   : l60609
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafXCallCtx.h"
#include "TafSdcCtx.h"
#include "TafStdlib.h"
#include "TafXCallMntn.h"
#include "MnClient.h"
#include "siapppb.h"

#include "TafCdmaPlusTranslate.h"

#include "TafXCallProcNvim.h"
#include "TafLog.h"
#include "TafXCallSndApp.h"
#include "TafXCallSndXcc.h"

#include "TafXCallEccCipher.h"

#include "NasUsimmApi.h"
#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_X_CALL_CTX_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
TAF_XCALL_CTX_STRU                      g_stTafXcallCtx;

TAF_XCALL_CS_ERR_CODE_MAP_STRU          g_astTafXcallErrCodeMapTbl[] =
{
    {TAF_CS_CAUSE_SUCCESS,                                  TAF_XCC_CAUSE_SUCCESS},
    {TAF_CS_CAUSE_XCALL_NO_SERVICE,                         TAF_XCC_CAUSE_NO_SERVICE},
    {TAF_CS_CAUSE_XCALL_MAX_ACCESS_PROBES,                  TAF_XCC_CAUSE_MAX_ACCESS_PROBES},
    {TAF_CS_CAUSE_XCALL_REORDER,                            TAF_XCC_CAUSE_REORDER},
    {TAF_CS_CAUSE_XCALL_INTERCEPT,                          TAF_XCC_CAUSE_INTERCEPT},
    {TAF_CS_CAUSE_XCALL_ACCESS_DENYIED,                     TAF_XCC_CAUSE_ACCESS_DENYIED},
    {TAF_CS_CAUSE_XCALL_LOCK,                               TAF_XCC_CAUSE_LOCK},
    {TAF_CS_CAUSE_XCALL_ACCT_BLOCK,                         TAF_XCC_CAUSE_ACCT_BLOCK},
    {TAF_CS_CAUSE_XCALL_NDSS,                               TAF_XCC_CAUSE_NDSS},
    {TAF_CS_CAUSE_XCALL_REDIRECTION,                        TAF_XCC_CAUSE_REDIRECTION},
    {TAF_CS_CAUSE_XCALL_NOT_ACCEPT_BY_BS,                   TAF_XCC_CAUSE_NOT_ACCEPT_BY_BS},
    {TAF_CS_CAUSE_XCALL_ACCESS_IN_PROGRESS,                 TAF_XCC_CAUSE_ACCESS_IN_PROGRESS},
    {TAF_CS_CAUSE_XCALL_ACCESS_FAIL,                        TAF_XCC_CAUSE_ACCESS_FAIL},
    {TAF_CS_CAUSE_XCALL_ABORT,                              TAF_XCC_CAUSE_ABORT},


    {TAF_CS_CAUSE_XCALL_SIGNAL_FADE_IN_ACH,                 TAF_XCC_CAUSE_SIGNAL_FADE_IN_ACH},
    {TAF_CS_CAUSE_XCALL_CHANNEL_ASSIGN_TIMEOUT,             TAF_XCC_CAUSE_CHANNEL_ASSIGN_TIMEOUT},
    {TAF_CS_CAUSE_XCALL_BS_RELEASE,                         TAF_XCC_CAUSE_BS_RELEASE},
    {TAF_CS_CAUSE_XCALL_OTHER_SERVICE_IN_TCH,               TAF_XCC_CAUSE_OTHER_SERVICE_IN_TCH},
    {TAF_CS_CAUSE_XCALL_CCS_NOT_SUPPORT,                    TAF_XCC_CAUSE_CCS_NOT_SUPPORT},
    {TAF_CS_CAUSE_XCALL_MS_NORMAL_RELEASE,                  TAF_XCC_CAUSE_MS_NORMAL_RELEASE},
    {TAF_CS_CAUSE_XCALL_NW_NORMAL_RELEASE,                  TAF_XCC_CAUSE_NW_NORMAL_RELEASE},
    {TAF_CS_CAUSE_XCALL_SO_REJ,                             TAF_XCC_CAUSE_SO_REJ},
    {TAF_CS_CAUSE_XCALL_RELEASE_TIME_OUT,                   TAF_XCC_CAUSE_RELEASE_TIME_OUT},
    {TAF_CS_CAUSE_XCALL_CONNECT_ORDER_ACK_FAILURE,          TAF_XCC_CAUSE_CONNECT_ORDER_ACK_FAILURE},
    {TAF_CS_CAUSE_XCALL_INCOMING_RSP_TIME_OUT,              TAF_XCC_CAUSE_INCOMING_RSP_TIME_OUT},
    {TAF_CS_CAUSE_XCALL_L2_ACK_TIME_OUT,                    TAF_XCC_CAUSE_L2_ACK_TIME_OUT},
    {TAF_CS_CAUSE_XCALL_POWER_DOWN_IND,                     TAF_XCC_CAUSE_POWER_DOWN_IND},

    {TAF_CS_CAUSE_XCALL_CONNID_NOT_FOUND,                   TAF_XCC_CAUSE_CONNID_NOT_FOUND},
    {TAF_CS_CAUSE_XCALL_ACCESS_CNF_TIMEOUT,                 TAF_XCC_CAUSE_ACCESS_CNF_TIMEOUT},
    {TAF_CS_CAUSE_XCALL_ACCESS_IND_TIMEOUT,                 TAF_XCC_CAUSE_ACCESS_TCH_TIMEOUT},

    {TAF_CS_CAUSE_XCALL_UNKNOWN,                            TAF_XCC_CAUSE_UNKNOWN},
    {TAF_CS_CAUSE_XCALL_CALL_NOT_ALLOWED,                   TAF_XCC_CAUSE_CALL_NOT_ALLOWED},

    {TAF_CS_CAUSE_XCALL_XCALL_HANGUP,                       TAF_XCC_CAUSE_XCALL_HANGUP},

    {TAF_CS_CAUSE_XCALL_WAIT_L2_ACK_RELEASE,                TAF_XCC_CAUSE_WAIT_L2_ACK_CALL_RELEASE},
    {TAF_CS_CAUSE_XCALL_EMERGENCY_CALL_FLASHED,             TAF_XCC_CAUSE_EMERGENCY_CALL_FLASHED},
    {TAF_CS_CAUSE_XCALL_EMERGENCY_CALL_ABORT,               TAF_XCC_CAUSE_EMERGENCY_CALL_ABORT},

    {TAF_CS_CAUSE_XCALL_NDSS_REDIAL_IND,                    TAF_XCC_CAUSE_NDSS_REDIAL_IND},

    {TAF_CS_CAUSE_XCALL_MT_SMS_IN_TCH,                      TAF_XCC_CAUSE_MT_SMS_IN_TCH},

    {TAF_CS_CAUSE_XCALL_SIGNAL_FADE_IN_TCH,                 TAF_XCC_CAUSE_SIGNAL_FADE_IN_TCH},
};


/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/

/*****************************************************************************
 函 数 名  : TAF_XCALL_GetCtxAddr
 功能描述  : 获取XCALL模块的上下文地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_XCALL_CTX_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月9日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
TAF_XCALL_CTX_STRU* TAF_XCALL_GetCtxAddr(VOS_VOID)
{
    return &(g_stTafXcallCtx);
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_GetCallEntityAddr
 功能描述  : 根据call id获取对应的呼叫实体信息
 输入参数  : VOS_UINT8                           ucCallId
 输出参数  : 无
 返 回 值  : TAF_XCALL_CALL_ENTITY_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月9日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
TAF_XCALL_CALL_ENTITY_STRU* TAF_XCALL_GetCallEntityAddr(
    VOS_UINT8                           ucCallId
)
{
    TAF_XCALL_CTX_STRU                 *pstXcallCtx = VOS_NULL_PTR;

    pstXcallCtx = TAF_XCALL_GetCtxAddr();

    return &(pstXcallCtx->astCallEntity[ucCallId - 1]);
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_GetCallConfigInfo
 功能描述  : 获取呼叫配置信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_XCALL_CONFIG_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月30日
    作    者   : y00218312
    修改内容   : 新生成函数

*****************************************************************************/
TAF_XCALL_CONFIG_STRU* TAF_XCALL_GetConfigInfo(VOS_VOID)
{
    TAF_XCALL_CTX_STRU                 *pstXcallCtx = VOS_NULL_PTR;

    pstXcallCtx = TAF_XCALL_GetCtxAddr();

    return &(pstXcallCtx->stConfig);
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_UpdateDigitMode
 功能描述  : 更新digitmode参数
 输入参数  : TAF_XCALL_DIGIT_MODE_ENUM_UINT8     enDigitMode
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月30日
    作    者   : y00218312
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_UpdateDigitMode(
    TAF_XCALL_DIGIT_MODE_ENUM_UINT8     enDigitMode
)
{
    TAF_XCALL_CONFIG_STRU              *pstCallConfig = VOS_NULL_PTR;

    pstCallConfig                       = TAF_XCALL_GetConfigInfo();
    pstCallConfig->enDigitMode          = enDigitMode;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_InitSpecCallEntity
 功能描述  : 初始化指定的呼叫实体
 输入参数  : VOS_UINT8                           ucCallId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月16日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2015年7月24日
    作    者   : l00324781
    修改内容   : Iter16 新开发,Cont DTMF和Burst DTMF缓存合一
  3.日    期   : 2015年12月24日
    作    者   : y00245242
    修改内容   : privacy mode特性开发
*****************************************************************************/
VOS_VOID TAF_XCALL_InitSpecCallEntity(
    VOS_UINT8                           ucCallId
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

    PS_MEM_SET(pstCallEntity, 0, sizeof(TAF_XCALL_CALL_ENTITY_STRU));

    pstCallEntity->ulUsed         = VOS_FALSE;

    pstCallEntity->enSo           = TAF_XCALL_SO_BUTT;

    pstCallEntity->enCallState    = MN_CALL_S_IDLE;

    pstCallEntity->enLastReOrigErr = TAF_XCC_FAIL_LAYER_BUTT;

    /* 默认配置为public */
    pstCallEntity->enPrivacyMode   = TAF_CALL_PRIVACY_MODE_PUBLIC;

    /*lint -e717*/
    HI_INIT_LIST_HEAD(&pstCallEntity->stDtmfBuffer.stList);
    /*lint +e717*/
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_InitNvConfig
 功能描述  : 初始化XCALL的NV设置
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月20日
    作    者   : h00313353
    修改内容   : 新生成函数
  2.日    期   : 2015年8月18日
    作    者   : l00324781
    修改内容   : DTS2015081708770修改

*****************************************************************************/
VOS_VOID TAF_XCALL_InitNvConfig( VOS_VOID )
{
    TAF_XCALL_ReadEmcCallRedialPeriod();

    TAF_XCALL_Read1xVoiceSoCfgNvim();
    TAF_XCALL_ReadStartAndStopContDtmfIntervalLen();

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
    TAF_XCALL_ReadVoiceEncryptPublicKeyAndVersionNumber();

    TAF_XCALL_ReadVoiceEncryptCapCfgPara();

    TAF_XCALL_ReadVoiceEncryptSecInfoEraseSysTime();

    TAF_XCALL_ReadVoiceEncryptPassWordResetSysTime();

    TAF_XCALL_ReadVoiceEncryptTimerCfgInfo();
#endif

    TAF_XCALL_ReadEmcCallBackCfgNvim();

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_InitCtx
 功能描述  : 初始化XCALL的上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月9日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2014年11月17日
    作    者   : w00176964
    修改内容   : CDMA 1x项目迭代5修改

*****************************************************************************/
VOS_VOID TAF_XCALL_InitCtx(VOS_VOID)
{
    VOS_UINT8                           ucCallId;
    TAF_XCALL_CTX_STRU                 *pstXcallCtx = VOS_NULL_PTR;

    pstXcallCtx = TAF_XCALL_GetCtxAddr();

    /* 初始化呼叫实体 */
    for (ucCallId = 1; ucCallId <= TAF_XCALL_CALL_ENTITY_MAX_NUM; ucCallId++)
    {
        TAF_XCALL_InitSpecCallEntity(ucCallId);
    }

    /* 初始化sups mgmt */
    PS_MEM_SET(&(pstXcallCtx->stSupsCmdMgmt), 0, sizeof(TAF_XCALL_SUPS_CMD_MGMT_STRU));

    /* 初始化configure */
    PS_MEM_SET(&(pstXcallCtx->stConfig), 0, sizeof(TAF_XCALL_CONFIG_STRU));
    pstXcallCtx->stConfig.enDigitMode   = TAF_XCALL_DIGIT_MODE_DTMF;

    TAF_XCALL_InitAllTimers(pstXcallCtx->astTimerCtx);

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
    TAF_XCALL_InitEncVoiceCtx();
#endif

    TAF_XCALL_InitNvConfig();
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_GetTimerCtxAddr
 功能描述  : 获取xcall CTX模块中定时器的上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  : xcall CTX模块中定时器的上下文指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月26日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
TAF_XCALL_TIMER_CTX_STRU*  TAF_XCALL_GetTimerCtxAddr( VOS_VOID )
{
    return TAF_XCALL_GetCtxAddr()->astTimerCtx;
}



/*****************************************************************************
 函 数 名  : TAF_XCALL_AllocCallId
 功能描述  : 分配CALL ID
 输入参数  : 无
 输出参数  : pucCallId      - call id
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月5日
    作    者   : y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_XCALL_AllocCallId(
    VOS_UINT8                      *pucCallId
)
{
    /* 查找空闲的CALL ID，分配给新的呼叫 */
    VOS_UINT8                           i;
    TAF_XCALL_CTX_STRU                 *pstXcallCtx = VOS_NULL_PTR;

    pstXcallCtx = TAF_XCALL_GetCtxAddr();

    for (i = 0; i < TAF_XCALL_CALL_ENTITY_MAX_NUM; i++)
    {
        /* 如果有未分配的实体，返回的Call id 的值为实体数组下标值加1 */
        if (VOS_FALSE == pstXcallCtx->astCallEntity[i].ulUsed)
        {
            *pucCallId = i + 1;

            TAF_XCALL_InitSpecCallEntity(*pucCallId);
            pstXcallCtx->astCallEntity[i].ulUsed = VOS_TRUE;

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;

}

/*****************************************************************************
 函 数 名  : TAF_XCALL_IsAllowToDailMoCall
 功能描述  : 判断是否允许发起新的拨号
 输入参数  : MN_CALL_TYPE_ENUM_U8                enCallType,
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月5日
    作    者   : y00213812
    修改内容   : 新生成函数
  2.日    期   : 2014年11月17日
    作    者   : w00176964
    修改内容   : CDMA 1x项目迭代5修改

*****************************************************************************/
VOS_UINT32 TAF_XCALL_IsAllowMoCallInCurrentStatus(
    MN_CALL_TYPE_ENUM_U8                enCallType
)
{
    /* 目前呼叫重拨已经实现,服务状态的判定这里不需要 */

    /* 发起的为紧急呼且当前存在一路被叫则允许发起,被叫的具体状态在XCC
       进行判定能否发起 */
    if (MN_CALL_TYPE_EMERGENCY == enCallType)
    {
        if (VOS_TRUE == TAF_XCALL_IsMtCallInstanceExist())
        {
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
            if (TAF_XCALL_VOICE_ENCRYPT_STA_INACTIVE != TAF_XCALL_GetVoiceEncryptNegotiateState())
            {
                /* 如果有密话存在，拒绝紧急呼 */
                return VOS_FALSE;
            }
#endif

            return VOS_TRUE;
        }
    }

    /* 当前呼叫类型为normal call时，所有呼叫实体都处于IDLE态,可以发起新呼叫 */
    if (VOS_TRUE == TAF_XCALL_ExistCallInstance())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_IsAvailCallId
 功能描述  : 判断是否为合法的Call Id
 输入参数  : VOS_UINT8                           ucCallId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月9日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XCALL_IsAvailCallId(
    VOS_UINT8                           ucCallId
)
{
    if ((0 == ucCallId)
     || (TAF_XCALL_CALL_ENTITY_MAX_NUM < ucCallId))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_IsAvailVoiceCallSo
 功能描述  : 判断是否有效的语音呼叫的SO
 输入参数  : VOS_UINT16                          usSo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月15日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XCALL_IsAvailVoiceCallSo(
    VOS_UINT16                          usSo
)
{
    if ((TAF_XCALL_SO_3_EVRC == usSo)
     || (TAF_XCALL_SO_68_EVRC_B == usSo)
     || (TAF_XCALL_SO_73_EVRC_NW == usSo))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_CreateMoCallEntity
 功能描述  : 创建MO call实体
 输入参数  : ulModuleId     - 发起呼叫的用户 id
             ucCallId       - call Id
             pstOrigPara    - 呼叫参数
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月5日
    作    者   : y00213812
    修改内容   : 新生成函数
  2.日    期   : 2015年1月5日
    作    者   : c00299063
    修改内容   : 增加加号转换

  3.日    期   : 2015年10月27日
    作    者   : y00245242
    修改内容   : iteration 19
*****************************************************************************/
VOS_VOID TAF_XCALL_CreateMoCallEntity(
    VOS_UINT8                           ucCallId,
    MN_CALL_APP_REQ_MSG_STRU           *pstCallPara
)
{
    /* 根据CALL ID分配呼叫实体 */
    MN_CALL_ORIG_PARAM_STRU            *pstOrig       = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstOrig       = &pstCallPara->unParm.stOrig;
    pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

    /* 记录发起call业务用户的信息(AT/STK) */
    TAF_XCALL_UpdateClientInfo(ucCallId,
                               pstCallPara->ulSenderPid,
                               pstCallPara->clientId,
                               pstCallPara->opId);
    /* 初始化呼叫参数 */
    pstCallEntity->enCallDir            = MN_CALL_DIR_MO;
    pstCallEntity->enCallState          = MN_CALL_S_DIALING;
    pstCallEntity->enCallType           = pstOrig->enCallType;
    pstCallEntity->enCause              = TAF_CS_CAUSE_SUCCESS;
    pstCallEntity->ucConnectId          = 0;
    pstCallEntity->ucConRef             = 0;

    #if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
    /***********************************************************************************************
     * 如果密话能力支持，则SO设置为EVRC
     **********************************************************************************************/
    if (VOS_TRUE == TAF_XCALL_GetVoiceEncryptCapCfgPara()->ucEccSrvCap)
    {
        pstCallEntity->enSo = TAF_XCALL_SO_3_EVRC;
    }
    else
    #endif
    {
        pstCallEntity->enSo = TAF_XCALL_GetConfigInfo()->enSoInitType;
    }

    pstCallEntity->ucIsAlertAnsByPass   = VOS_FALSE;


    /* 初始化被叫号码 */
    PS_MEM_CPY(&pstCallEntity->stCalledNumber,
               &pstOrig->stDialNumber,
               sizeof(MN_CALL_CALLED_NUM_STRU));

    PS_MEM_CPY(&pstCallEntity->stCalledSubAddr,
               &pstOrig->stSubaddr,
               sizeof(MN_CALL_SUBADDR_STRU));

    /* 呼叫号码加号转换 */
    TAF_XCALL_TranlatePlusToCallNum(pstCallEntity);

    pstCallEntity->stRedirectNumber.ucNumLen    = 0;
    pstCallEntity->stConnectNumber.ucNumLen     = 0;

    /* 设置SDC中CS呼叫标志 */
    TAF_XCALL_SetCsCallExistFlg(VOS_TRUE, pstCallPara->unParm.stOrig.enCallType);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_CreateMtCallEntity
 功能描述  : 创建MT call实体
 输入参数  : VOS_UINT8                           ucCallId,
             VOS_UINT32                          ulModuleId,
             XCC_XCALL_INCOMING_CALL_IND_STRU   *pstIncomingCallInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月5日
    作    者   : y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_CreateMtCallEntity(
    VOS_UINT8                           ucCallId,
    VOS_UINT32                          ulModuleId,
    XCC_XCALL_INCOMING_CALL_IND_STRU   *pstIncomingCallInd
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    /* 此处不再判断call id的有效性，根据传入的call id分配呼叫实体 */
    pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

    /* 记录发起call业务用户的信息(AT/STK) */
    TAF_XCALL_UpdateClientInfo(ucCallId,
                               ulModuleId,
                               MN_CLIENT_ID_BROADCAST,
                               0);


    /* 更新SO */
    pstCallEntity->enSo               = pstIncomingCallInd->enSo;

    /* 更新By pass Flag */
    pstCallEntity->ucIsAlertAnsByPass = pstIncomingCallInd->ucIsAlertAnsByPass;

    /* 更新Connect Reference */
    pstCallEntity->ucConRef           = pstIncomingCallInd->ucConRef;

    /* 更新Connect Id */
    pstCallEntity->ucConnectId        = pstIncomingCallInd->ucConnectId;

    /* 更新呼叫状态 */
    pstCallEntity->enCallState        = MN_CALL_S_INCOMING;

    /* 更新呼叫类型 */
    pstCallEntity->enCallType         = MN_CALL_TYPE_VOICE;

    /* 更新发起呼叫Dir */
    pstCallEntity->enCallDir          = MN_CALL_DIR_MT;

    /* 更新来电号码 */
    TAF_XCALL_UpdateCallingNum(ucCallId, &(pstIncomingCallInd->stCallingPartyNum));

    /* 更新privacy mode */
    if (TAF_CALL_PRIVACY_MODE_BUTT != (TAF_CALL_PRIVACY_MODE_ENUM_UINT8)pstIncomingCallInd->enPrivacyMode)
    {
        pstCallEntity->enPrivacyMode  = (TAF_CALL_PRIVACY_MODE_ENUM_UINT8)pstIncomingCallInd->enPrivacyMode;
    }

    /* 设置SDC中CS呼叫标志 */
    TAF_XCALL_SetCsCallExistFlg(VOS_TRUE, MN_CALL_TYPE_VOICE);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_FreeCallEntity
 功能描述  : 释放呼叫ID
 输入参数  : VOS_UINT8                           ucCallId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月9日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_FreeCallEntity(
    VOS_UINT8                           ucCallId
)
{
    TAF_XCALL_InitSpecCallEntity(ucCallId);

    if (VOS_FALSE == TAF_XCALL_ExistCallInstance())
    {
        /* 清除SDC中CS呼叫标志 */
        TAF_XCALL_SetCsCallExistFlg(VOS_FALSE, MN_CALL_TYPE_BUTT);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_UpdateClientInfo
 功能描述  : 保存呼叫发起者的模块信息
 输入参数  : VOS_UINT8                           ucCallId
             VOS_UINT32                          ulModuleId
             VOS_UINT16                          usClientId
             VOS_UINT8                           ucOpId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月11日
    作    者   : y00218312
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_UpdateClientInfo(
    VOS_UINT8                           ucCallId,
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity       = TAF_XCALL_GetCallEntityAddr(ucCallId);

    pstCallEntity->stClientInfo.ulModuleId = ulModuleId;
    pstCallEntity->stClientInfo.usClientId = usClientId;
    pstCallEntity->stClientInfo.ucOpId     = ucOpId;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_UpdateCallState
 功能描述  : 更新指定呼叫的呼叫状态
 输入参数  : VOS_UINT8                           ucCallId,
             MN_CALL_STATE_ENUM_U8               enCallState
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月5日
    作    者   : y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_UpdateCallState(
    VOS_UINT8                           ucCallId,
    MN_CALL_STATE_ENUM_U8               enCallState
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity       = TAF_XCALL_GetCallEntityAddr(ucCallId);

    pstCallEntity->enCallState = enCallState;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_UpdateCallType
 功能描述  : 更新指定呼叫的呼叫类型
 输入参数  : VOS_UINT8                           ucCallId
             MN_CALL_TYPE_ENUM_U8                enCallType
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月9日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_UpdateCallType(
    VOS_UINT8                           ucCallId,
    MN_CALL_TYPE_ENUM_U8                enCallType
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity       = TAF_XCALL_GetCallEntityAddr(ucCallId);

    pstCallEntity->enCallType = enCallType;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_UpdateCallDir
 功能描述  : 更新指定呼叫的call direction
 输入参数  : VOS_UINT8                           ucCallId
             MN_CALL_DIR_ENUM_U8                 enCallDir
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月9日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_UpdateCallDir(
    VOS_UINT8                           ucCallId,
    MN_CALL_DIR_ENUM_U8                 enCallDir
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity       = TAF_XCALL_GetCallEntityAddr(ucCallId);

    pstCallEntity->enCallDir = enCallDir;
}


/*****************************************************************************
 函 数 名  : TAF_XCALL_UpdateSo
 功能描述  : 更新指定呼叫的SO
 输入参数  : VOS_UINT8                           ucCallId
             TAF_XCALL_SO_TYPE_ENUM_UINT16       enSo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月9日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_UpdateSo(
    VOS_UINT8                           ucCallId,
    TAF_XCALL_SO_TYPE_ENUM_UINT16       enSo
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity       = TAF_XCALL_GetCallEntityAddr(ucCallId);

    pstCallEntity->enSo = enSo;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_UpdateConnectId
 功能描述  : 更新指定呼叫的connect id
 输入参数  : VOS_UINT8                           ucCallId
             VOS_UINT8                           ucConnectId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月9日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_UpdateConnectId(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucConnectId
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity              = TAF_XCALL_GetCallEntityAddr(ucCallId);

    pstCallEntity->ucConnectId = ucConnectId;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_UpdateConnectRef
 功能描述  : 更新指定呼叫的connect reference
 输入参数  : VOS_UINT8                           ucCallId
             VOS_UINT8                           ucConRef
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月9日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_UpdateConnectRef(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucConRef
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity           = TAF_XCALL_GetCallEntityAddr(ucCallId);

    pstCallEntity->ucConRef = ucConRef;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_UpdateAlertAnsByPassFlg
 功能描述  : 更新指定呼叫的by pass标志
 输入参数  : VOS_UINT8                           ucCallId
             VOS_UINT8                           ucIsAlertAnsByPass
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月9日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_UpdateAlertAnsByPassFlg(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucIsAlertAnsByPass
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity                     = TAF_XCALL_GetCallEntityAddr(ucCallId);

    pstCallEntity->ucIsAlertAnsByPass = ucIsAlertAnsByPass;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_UpdateCcCause
 功能描述  : 更新指定呼叫的原因值
 输入参数  : VOS_UINT8                           ucCallId
             TAF_CS_CAUSE_ENUM_UINT32            enCcCause
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月15日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_UpdateCcCause(
    VOS_UINT8                           ucCallId,
    TAF_CS_CAUSE_ENUM_UINT32            enCcCause
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity                     = TAF_XCALL_GetCallEntityAddr(ucCallId);

    pstCallEntity->enCause            = enCcCause;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_UpdateDiscCallDir
 功能描述  : 更新指定呼叫的通话挂断方向
 输入参数  : VOS_UINT8                           ucCallId
             VOS_UINT8                           ucIsUser
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月15日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_UpdateDiscCallDir(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucIsUser
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity                     = TAF_XCALL_GetCallEntityAddr(ucCallId);

    if (VOS_TRUE == pstCallEntity->stDiscDir.ucDiscCallFlag)
    {
        return;
    }

    pstCallEntity->stDiscDir.ucIsUser       = ucIsUser;
    pstCallEntity->stDiscDir.ucDiscCallFlag = VOS_TRUE;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_UpdateCallingNum
 功能描述  : 更新指定呼叫的calling NUM
 输入参数  : VOS_UINT8                                               ucCallId
             XCC_XCALL_CALLING_PARTY_NUM_INFO_STRU                  *pstXccCallNum
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月18日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2015年08月24日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID TAF_XCALL_UpdateCallingNum(
    VOS_UINT8                                               ucCallId,
    XCC_XCALL_CALLING_PARTY_NUM_INFO_STRU                  *pstXccCallNum
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT8                           aucDigit[XCC_XCALL_MAX_NUM_DIGIT_LEN + 1];

    PS_MEM_SET(aucDigit, 0, sizeof(aucDigit));

    pstCallEntity                     = TAF_XCALL_GetCallEntityAddr(ucCallId);

    /* num type:
        bit7 | bit6 bit5 bit4 | bit3 bit2 bit1 bit0
          1  |     num type   |    num plan
     */
    pstCallEntity->stCallNumber.enNumType = 0x80 | (VOS_UINT8)(pstXccCallNum->enNumType << 4) | (pstXccCallNum->enNumPlan& 0x0F);

    pstCallEntity->ucPi                   = pstXccCallNum->ucPi;
    pstCallEntity->ucSi                   = pstXccCallNum->ucSi;

    PS_MEM_CPY(aucDigit, pstXccCallNum->aucDigit, TAF_XCALL_MIN(pstXccCallNum->ucDigitNum, XCC_XCALL_MAX_NUM_DIGIT_LEN));

    (VOS_VOID)TAF_STD_ConvertAsciiNumberToBcd((VOS_CHAR *)aucDigit,
                                    pstCallEntity->stCallNumber.aucBcdNum,
                                    &(pstCallEntity->stCallNumber.ucNumLen));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_GetSupsCmdMgmt
 功能描述  : 获取SUPS命令管理信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_XCALL_SUPS_CMD_MGMT_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月20日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
TAF_XCALL_SUPS_CMD_MGMT_STRU* TAF_XCALL_GetSupsCmdMgmt(VOS_VOID)
{
    TAF_XCALL_CTX_STRU                 *pstXcallCtx = VOS_NULL_PTR;

    pstXcallCtx = TAF_XCALL_GetCtxAddr();

    return &(pstXcallCtx->stSupsCmdMgmt);

}

/*****************************************************************************
 函 数 名  : TAF_XCALL_GetClientInfo
 功能描述  : 获取呼叫实体中CLIENT_INFO地址
 输入参数  : VOS_UINT8                           ucCallId
 输出参数  : 无
 返 回 值  : TAF_XCALL_CLIENT_INFO_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月11日
    作    者   : y00218312
    修改内容   : 新生成函数

*****************************************************************************/
TAF_XCALL_CLIENT_INFO_STRU* TAF_XCALL_GetClientInfo(
    VOS_UINT8                           ucCallId
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

    return &(pstCallEntity->stClientInfo);
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_GetCallState
 功能描述  : 获取指定呼叫的呼叫状态
 输入参数  : VOS_UINT8                           ucCallId
 输出参数  : 无
 返 回 值  : MN_CALL_STATE_ENUM_U8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月9日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
MN_CALL_STATE_ENUM_U8 TAF_XCALL_GetCallState(
    VOS_UINT8                           ucCallId
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity                     = TAF_XCALL_GetCallEntityAddr(ucCallId);

    return pstCallEntity->enCallState;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_GetSo
 功能描述  : 获取指定呼叫的SO
 输入参数  : VOS_UINT8                           ucCallId
 输出参数  : 无
 返 回 值  : TAF_XCALL_SO_TYPE_ENUM_UINT16
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月23日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
TAF_XCALL_SO_TYPE_ENUM_UINT16 TAF_XCALL_GetSo(
    VOS_UINT8                           ucCallId
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity                     = TAF_XCALL_GetCallEntityAddr(ucCallId);

    return pstCallEntity->enSo;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_GetCallType
 功能描述  : 获取指定呼叫的呼叫类型
 输入参数  : VOS_UINT8                           ucCallId
 输出参数  : 无
 返 回 值  : MN_CALL_TYPE_ENUM_U8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月16日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
MN_CALL_TYPE_ENUM_U8 TAF_XCALL_GetCallType(
    VOS_UINT8                           ucCallId
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity                     = TAF_XCALL_GetCallEntityAddr(ucCallId);

    return pstCallEntity->enCallType;
}


/*****************************************************************************
 函 数 名  : TAF_XCALL_GetAlertAnsByPassFlg
 功能描述  : 获取指定呼叫的by pass标志
 输入参数  : VOS_UINT8                           ucCallId
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月9日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_XCALL_GetAlertAnsByPassFlg(
    VOS_UINT8                           ucCallId
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity                     = TAF_XCALL_GetCallEntityAddr(ucCallId);

    return pstCallEntity->ucIsAlertAnsByPass;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_GetCcCause
 功能描述  : 获取指定呼叫的CC CAUSE
 输入参数  : VOS_UINT8                           ucCallId
 输出参数  : 无
 返 回 值  : TAF_CS_CAUSE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月17日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
TAF_CS_CAUSE_ENUM_UINT32 TAF_XCALL_GetCcCause(
    VOS_UINT8                           ucCallId
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity                     = TAF_XCALL_GetCallEntityAddr(ucCallId);

    return pstCallEntity->enCause;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_GetCallIdFromConnectId
 功能描述  : 根据connect id获取call id
 输入参数  : VOS_UINT8                           ucConnectId
 输出参数  : call id
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月28?
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XCALL_GetCallIdFromConnectId(
    VOS_UINT8                           ucConnectId,
    VOS_UINT8                          *pucCallId
)
{
    VOS_UINT8                           i;
    TAF_XCALL_CTX_STRU                 *pstXcallCtx = VOS_NULL_PTR;

    pstXcallCtx = TAF_XCALL_GetCtxAddr();

    for (i = 0; i < TAF_XCALL_CALL_ENTITY_MAX_NUM; i++)
    {
        if ((VOS_TRUE == pstXcallCtx->astCallEntity[i].ulUsed)
         && (ucConnectId == pstXcallCtx->astCallEntity[i].ucConnectId))
        {
            *pucCallId = (VOS_UINT8)(i + 1);

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : TAF_XCALL_GetCallsByState
 功能描述  : 获取特定呼叫状态的所有呼叫
 输入参数  : MN_CALL_STATE_ENUM_U8               enCallState
 输出参数  : VOS_UINT32                         *pulNumOfCalls
             VOS_UINT8                          *pucCallIds
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月9日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_GetCallsByState(
    MN_CALL_STATE_ENUM_U8               enCallState,
    VOS_UINT32                         *pulNumOfCalls,
    VOS_UINT8                          *pucCallIds
)
{
    VOS_UINT8                           i;
    TAF_XCALL_CTX_STRU                 *pstXcallCtx = VOS_NULL_PTR;

    pstXcallCtx = TAF_XCALL_GetCtxAddr();

    *pulNumOfCalls = 0;

    for (i = 0; i < TAF_XCALL_CALL_ENTITY_MAX_NUM; i++)
    {
        if ((VOS_TRUE == pstXcallCtx->astCallEntity[i].ulUsed)
         && (enCallState == pstXcallCtx->astCallEntity[i].enCallState))
        {
            *pucCallIds++ = (VOS_UINT8)(i + 1);
            (*pulNumOfCalls)++;
        }
    }
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_GetNotIdleStateCalls
 功能描述  : 获取非idle态的呼叫
 输入参数  : VOS_UINT32                         *pulNumOfCalls
             VOS_UINT8                          *pucCallIds
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月15日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_GetNotIdleStateCalls(
    VOS_UINT32                         *pulNumOfCalls,
    VOS_UINT8                          *pucCallIds
)
{
    VOS_UINT8                           i;
    TAF_XCALL_CTX_STRU                 *pstXcallCtx = VOS_NULL_PTR;

    pstXcallCtx = TAF_XCALL_GetCtxAddr();

    *pulNumOfCalls = 0;

    for (i = 0; i < TAF_XCALL_CALL_ENTITY_MAX_NUM; i++)
    {
        if ((VOS_TRUE == pstXcallCtx->astCallEntity[i].ulUsed)
         && (MN_CALL_S_IDLE != pstXcallCtx->astCallEntity[i].enCallState))
        {
            *pucCallIds++ = (VOS_UINT8)(i + 1);
            (*pulNumOfCalls)++;
        }
    }
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_MapXccCauseToCsCause
 功能描述  : 将XCC的错误码映射成TAF的cs cause
 输入参数  : TAF_XCC_CAUSE_ENUM_UINT32           enXccCause
 输出参数  : 无
 返 回 值  : TAF_CS_CAUSE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月17日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
TAF_CS_CAUSE_ENUM_UINT32 TAF_XCALL_MapXccCauseToCsCause(
    TAF_XCC_CAUSE_ENUM_UINT32           enXccCause
)
{
    VOS_UINT32                          ulCnt;

    for (ulCnt = 0; ulCnt < (sizeof(g_astTafXcallErrCodeMapTbl)/sizeof(TAF_XCALL_CS_ERR_CODE_MAP_STRU)); ulCnt++)
    {
        if (g_astTafXcallErrCodeMapTbl[ulCnt].enXccCause == enXccCause)
        {
            return g_astTafXcallErrCodeMapTbl[ulCnt].enCsCause;
        }
    }

    return TAF_CS_CAUSE_UNKNOWN;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ExistCallInstance
 功能描述  : 判断当前是否存在呼叫
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月19日
    作    者   : y00218312
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XCALL_ExistCallInstance(VOS_VOID)
{
    VOS_UINT8                           i;
    TAF_XCALL_CTX_STRU                 *pstXcallCtx = VOS_NULL_PTR;

    pstXcallCtx = TAF_XCALL_GetCtxAddr();

    for (i = 0; i < TAF_XCALL_CALL_ENTITY_MAX_NUM; i++)
    {
        if (VOS_TRUE == pstXcallCtx->astCallEntity[i].ulUsed)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_RegSsKeyEvent
 功能描述  : 注册补充业务操作的关注事件
 输入参数  : VOS_UINT8                                               ucCallId,
             TAF_XCALL_SS_PROGRESS_EVT_ENUM_UINT8                    enEvt,
             TAF_XCALL_SS_SUBSEQ_OP_ENUM_UINT8                       enSubseqOp
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月20日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_RegSsKeyEvent(
    VOS_UINT8                                               ucCallId,
    TAF_XCALL_SS_PROGRESS_EVT_ENUM_UINT8                    enEvt,
    TAF_XCALL_SS_SUBSEQ_OP_ENUM_UINT8                       enSubseqOp
)
{
    TAF_XCALL_SUPS_CMD_MGMT_STRU       *pstSupsCmdMgmt = VOS_NULL_PTR;
    VOS_UINT8                           i;

    pstSupsCmdMgmt = TAF_XCALL_GetSupsCmdMgmt();

    TAF_XCALL_MNTN_LogSupsCmdMgmt();

    if (pstSupsCmdMgmt->ucNumOfKeyEvt >= TAF_XCALL_MAX_SS_CMD_KEY_EVT_NUM)
    {
        return;
    }

    for (i = 0; i < pstSupsCmdMgmt->ucNumOfKeyEvt; i++)
    {
        /* 该call id对应的事件已存在 */
        if (pstSupsCmdMgmt->astKeyEvts[i].ucCallId == ucCallId)
        {
            pstSupsCmdMgmt->astKeyEvts[i].enEvt      = enEvt;
            pstSupsCmdMgmt->astKeyEvts[i].enSubseqOp = enSubseqOp;
            return;
        }
    }

    /* 添加一个关注事件, 根据输入参数填写事件内容 */
    pstSupsCmdMgmt->astKeyEvts[pstSupsCmdMgmt->ucNumOfKeyEvt].ucCallId   = ucCallId;
    pstSupsCmdMgmt->astKeyEvts[pstSupsCmdMgmt->ucNumOfKeyEvt].enEvt      = enEvt;
    pstSupsCmdMgmt->astKeyEvts[pstSupsCmdMgmt->ucNumOfKeyEvt].enSubseqOp = enSubseqOp;

    pstSupsCmdMgmt->ucNumOfKeyEvt++;

    TAF_XCALL_MNTN_LogSupsCmdMgmt();

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_DeRegSsKeyEvent
 功能描述  : 去注册补充业务操作的关注事件
 输入参数  : VOS_UINT8                                               ucCallId,
             TAF_XCALL_SS_PROGRESS_EVT_ENUM_UINT8                    enEvt
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月20日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_DeRegSsKeyEvent(
    VOS_UINT8                                               ucCallId,
    TAF_XCALL_SS_PROGRESS_EVT_ENUM_UINT8                    enEvt
)
{
    TAF_XCALL_SUPS_CMD_MGMT_STRU       *pstSupsCmdMgmt = VOS_NULL_PTR;
    VOS_UINT8                           ucNumOfKeyEvt;
    VOS_UINT8                           i;

    pstSupsCmdMgmt = TAF_XCALL_GetSupsCmdMgmt();

    ucNumOfKeyEvt  = pstSupsCmdMgmt->ucNumOfKeyEvt;

    TAF_XCALL_MNTN_LogSupsCmdMgmt();

    /* 查找对应关注的事件 */
    for (i = 0; i < ucNumOfKeyEvt; i++)
    {
        if ((ucCallId == pstSupsCmdMgmt->astKeyEvts[i].ucCallId)
           &&(enEvt == pstSupsCmdMgmt->astKeyEvts[i].enEvt))
        {
            break;
        }
    }

    if (i >= ucNumOfKeyEvt)
    {
        return;
    }

    PS_MEM_CPY(&(pstSupsCmdMgmt->astKeyEvts[i]),
               &(pstSupsCmdMgmt->astKeyEvts[i + 1]),
               ((ucNumOfKeyEvt - i) - 1) * sizeof(TAF_XCALL_SUPS_CMD_KEY_EVT_STRU));

    pstSupsCmdMgmt->ucNumOfKeyEvt--;

    TAF_XCALL_MNTN_LogSupsCmdMgmt();
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_GetSsKeyEvent
 功能描述  : 获取指定呼叫的补充业务操作关注的事件
 输入参数  : VOS_UINT8                           ucCallId
             TAF_XCALL_SS_PROGRESS_EVT_ENUM_UINT8     *penEvt
             TAF_XCALL_SS_SUBSEQ_OP_ENUM        *penSubseqOp
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月20日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_GetSsKeyEvent(
    VOS_UINT8                                               ucCallId,
    TAF_XCALL_SS_PROGRESS_EVT_ENUM_UINT8                   *penEvt,
    TAF_XCALL_SS_SUBSEQ_OP_ENUM_UINT8                      *penSubseqOp
)
{

    TAF_XCALL_SUPS_CMD_MGMT_STRU       *pstSupsCmdMgmt = VOS_NULL_PTR;
    VOS_UINT8                           ucNumOfKeyEvt;
    VOS_UINT8                           i;

    pstSupsCmdMgmt = TAF_XCALL_GetSupsCmdMgmt();

    ucNumOfKeyEvt  = pstSupsCmdMgmt->ucNumOfKeyEvt;

    TAF_XCALL_MNTN_LogSupsCmdMgmt();

    /* 查找对应关注的事件 */
    for (i = 0; i < ucNumOfKeyEvt; i++)
    {
        if (ucCallId == pstSupsCmdMgmt->astKeyEvts[i].ucCallId)
        {
            *penEvt      = pstSupsCmdMgmt->astKeyEvts[i].enEvt;
            *penSubseqOp = pstSupsCmdMgmt->astKeyEvts[i].enSubseqOp;
            return;
        }
    }

    *penEvt      = TAF_XCALL_SS_PROG_EVT_BUTT;
    *penSubseqOp = TAF_XCALL_SS_SUBSEQ_OP_BUTT;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_SetWaitForXCCDTMFCnfFlag
 功能描述  : 更新指定呼叫的等待XCC的Burst DTMF或Cont DTMF回复的标识
 输入参数  : VOS_UINT8                           ucCallId,
             TAF_XCALL_WAIT_XCC_CNF_TYPE_UINT8   enWaitForXCCDTMFCnfFlag
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成函数
  2.日    期   : 2015年7月29日
    作    者   : l00324781
    修改内容   : Iter16修改，Cont DTMF和Burst DTMF的等待XCC响应公用一个标志
  3.日    期   : 2015年8月18日
    作    者   : l00324781
    修改内容   : DTS2015081708770修改，WaitForXCCDTMFCnfFlag改为枚举类型

*****************************************************************************/
VOS_VOID TAF_XCALL_SetWaitForXCCDTMFCnfFlag(
    VOS_UINT8                           ucCallId,
    TAF_XCALL_WAIT_XCC_CNF_TYPE_UINT8   enWaitForXCCDTMFCnfFlag
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

    pstCallEntity->enWaitForXCCDTMFCnfFlag = enWaitForXCCDTMFCnfFlag;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_GetWaitForXCCDTMFCnfFlag
 功能描述  : 获取XCC等待标识
 输入参数  : VOS_UINT8                           ucCallId
 输出参数  : 无
 返 回 值  : TAF_XCALL_WAIT_XCC_CNF_TYPE_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成函数
  2.日    期   : 2015年7月29日
    作    者   : l00324781
    修改内容   : Iter16修改，Cont DTMF和Burst DTMF的等待XCC响应公用一个标志
  3.日    期   : 2015年8月18日
    作    者   : l00324781
    修改内容   : DTS2015081708770修改，WaitForXCCDTMFCnfFlag改为枚举类型
*****************************************************************************/
TAF_XCALL_WAIT_XCC_CNF_TYPE_UINT8 TAF_XCALL_GetWaitForXCCDTMFCnfFlag(
    VOS_UINT8       ucCallId
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

    return pstCallEntity->enWaitForXCCDTMFCnfFlag;
}


/*****************************************************************************
 函 数 名  : TAF_XCALL_IsMtCallInstanceExist
 功能描述  : 判断当前是否存在被叫
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月17日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XCALL_IsMtCallInstanceExist(VOS_VOID)
{
    VOS_UINT8                           i;
    TAF_XCALL_CTX_STRU                 *pstXcallCtx = VOS_NULL_PTR;

    pstXcallCtx = TAF_XCALL_GetCtxAddr();

    for (i = 0; i < TAF_XCALL_CALL_ENTITY_MAX_NUM; i++)
    {
        if ((VOS_TRUE       == pstXcallCtx->astCallEntity[i].ulUsed)
         && (MN_CALL_DIR_MT == pstXcallCtx->astCallEntity[i].enCallDir))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_GetCallDir
 功能描述  : 获取指定呼叫的call direction
 输入参数  : VOS_UINT8                           ucCallId
             MN_CALL_DIR_ENUM_U8                 enCallDir
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月4日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
MN_CALL_DIR_ENUM_U8 TAF_XCALL_GetCallDir(
    VOS_UINT8                           ucCallId
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;
    MN_CALL_DIR_ENUM_U8                 enCallDir;

    pstCallEntity       = TAF_XCALL_GetCallEntityAddr(ucCallId);

    enCallDir = pstCallEntity->enCallDir;

    return enCallDir;
}



#if 0
/*****************************************************************************
 函 数 名  : TAF_XCALL_TranlateCallNumToPlus
 功能描述  : 语音呼叫被叫加号转换
 输入参数  : TAF_XCALL_CALL_ENTITY_STRU                             *pstCallEntity
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月30日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_TranlateCallNumToPlus(
    TAF_XCALL_CALL_ENTITY_STRU                             *pstCallEntity
)
{
    VOS_UINT16                                              usCurMcc;
    MN_CALL_NUM_TYPE_ENUM_U8                                enCurNumType;
    VOS_UINT8                                               aucCurCallBcdNum[TAF_MT_MAX_BCD_NUM_LEN];
    VOS_UINT8                                               ucCurCallBcdNumLen;
    VOS_INT8                                                acCurCallAsciiNum[TAF_MT_MAX_ASCII_NUM_LEN + 1];
    VOS_UINT8                                               ucCurCallAsciiNumLen;
    TAF_SDC_1X_SYS_INFO_STRU                               *pstSdc1xSysInfo = VOS_NULL_PTR;

    /*获取mcc */
    pstSdc1xSysInfo      = TAF_SDC_Get1xSysInfo();
    usCurMcc             = pstSdc1xSysInfo->stServiceInfo.usMcc;

    /* 获取BCD号码长度 */
    ucCurCallBcdNumLen   = pstCallEntity->stCallNumber.ucNumLen;

    /* 获取号码类型*/
    enCurNumType         = pstCallEntity->stCallNumber.enNumType;

    /*获取呼叫号码 */
    PS_MEM_SET(aucCurCallBcdNum, 0, sizeof(aucCurCallBcdNum));
    PS_MEM_CPY(aucCurCallBcdNum, pstCallEntity->stCallNumber.aucBcdNum, sizeof(aucCurCallBcdNum));

    /*将BCD码呼叫格式的号码转换为ASCII格式 */
    PS_MEM_SET(acCurCallAsciiNum, 0, sizeof(acCurCallAsciiNum));
    TAF_STD_ConvertBcdNumberToAscii(aucCurCallBcdNum, ucCurCallBcdNumLen, acCurCallAsciiNum);

    /*语音模式下，加号转换处理 */
    ucCurCallAsciiNumLen  = (VOS_UINT8)VOS_StrLen(acCurCallAsciiNum);
    TAF_TranslateNumToPlus(usCurMcc, TAF_PLUS_TRANSLATE_DIAL_TYPE_VOICE, &enCurNumType, (VOS_UINT8 *)acCurCallAsciiNum, &ucCurCallAsciiNumLen);

    /*将ASCII呼叫格式的号码转换为BCD码 */
    ucCurCallBcdNumLen    = 0;
    PS_MEM_SET(aucCurCallBcdNum, 0, sizeof(aucCurCallBcdNum));
    TAF_STD_ConvertAsciiNumberToBcd(acCurCallAsciiNum, aucCurCallBcdNum, &ucCurCallBcdNumLen);

    /*将转换后的号码信息写回 */
    PS_MEM_CPY(pstCallEntity->stCallNumber.aucBcdNum, aucCurCallBcdNum, sizeof(aucCurCallBcdNum));
    pstCallEntity->stCallNumber.ucNumLen  = ucCurCallBcdNumLen;
    pstCallEntity->stCallNumber.enNumType = enCurNumType;

    return;
}
#endif
/*****************************************************************************
 函 数 名  : TAF_XCALL_TranlatePlusToCallNum
 功能描述  : 语音呼叫主叫加号转换
 输入参数  : TAF_XCALL_CALL_ENTITY_STRU                             *pstCallEntity
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月30日
    作    者   : c00299063
    修改内容   : 新生成函数

  2.日    期   : 2015年08月24日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

  3.日    期   : 2015年12月31日
    作    者   : h00313353
    修改内容   : DTS2015122804554
*****************************************************************************/
VOS_VOID TAF_XCALL_TranlatePlusToCallNum(
    TAF_XCALL_CALL_ENTITY_STRU                             *pstCallEntity
)
{
    VOS_INT32                                               lSid;
    MN_CALL_NUM_TYPE_ENUM_U8                                enCurNumType;
    VOS_UINT8                                               aucCurCalledBcdNum[TAF_MO_MAX_BCD_NUM_LEN];
    VOS_UINT8                                               aucCurCalledBcdNumLen;
    VOS_INT8                                                acCurCalledAsciiNum[TAF_MO_MAX_ASCII_NUM_LEN + 1];
    VOS_UINT8                                               ucCurCalledAsciiNumLen;

    /*获取mcc */
    lSid              = TAF_SDC_GetSdcCtx()->stNetworkInfo.lSid;

    /* 获取BCD号码长度 */
    aucCurCalledBcdNumLen = pstCallEntity->stCalledNumber.ucNumLen;

    /* 获取号码类型*/
    enCurNumType      = pstCallEntity->stCalledNumber.enNumType;

    /*获取呼叫号码 */
    PS_MEM_SET(aucCurCalledBcdNum, 0, sizeof(aucCurCalledBcdNum));
    PS_MEM_CPY(aucCurCalledBcdNum, pstCallEntity->stCalledNumber.aucBcdNum, sizeof(aucCurCalledBcdNum));

    /*将BCD码呼叫格式的号码转换为ASCII格式 */
    PS_MEM_SET(acCurCalledAsciiNum, 0, sizeof(acCurCalledAsciiNum));
    if (MN_ERR_NO_ERROR != TAF_STD_ConvertBcdNumberToAscii(aucCurCalledBcdNum, aucCurCalledBcdNumLen, (VOS_CHAR*)acCurCalledAsciiNum))
    {
        return;
    }

    /*语音模式下，加号转换处理 */
    ucCurCalledAsciiNumLen = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)acCurCalledAsciiNum);
    TAF_TranslatePlusToNum(lSid, TAF_PLUS_TRANSLATE_DIAL_TYPE_VOICE, &enCurNumType, (VOS_UINT8 *)acCurCalledAsciiNum, &ucCurCalledAsciiNumLen);

    /*将ASCII呼叫格式的号码转换为BCD码 */
    aucCurCalledBcdNumLen = 0;
    PS_MEM_SET(aucCurCalledBcdNum, 0, sizeof(aucCurCalledBcdNum));

    (VOS_VOID)TAF_STD_ConvertAsciiNumberToBcd((VOS_CHAR*)acCurCalledAsciiNum, aucCurCalledBcdNum, &aucCurCalledBcdNumLen);

    /*将转换后的号码信息写回 */
    PS_MEM_CPY(pstCallEntity->stCalledNumber.aucBcdNum, aucCurCalledBcdNum, sizeof(aucCurCalledBcdNum));
    pstCallEntity->stCalledNumber.ucNumLen  = aucCurCalledBcdNumLen;
    pstCallEntity->stCalledNumber.enNumType = enCurNumType;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_GetEccNumList
 功能描述  : 获取当前的紧急呼列表
 输入参数  : 无
 输出参数  : pstEccNumInfo:返回的紧急呼列表
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月4日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_GetEccNumList(
    MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo
)
{
    VOS_UINT32                          i;
    TAF_SDC_CUSTOM_ECC_CTX_STRU        *pstCustomCallEmerNumCtx = VOS_NULL_PTR;
    SI_PB_ECC_DATA_STRU                *pstEccData= VOS_NULL_PTR;

    pstEccNumInfo->ulEccNumCount = 0;

    /* 卡中存在号码，则先将卡中的号码放入上报内容中 */
    if (TAF_SDC_USIM_STATUS_NO_PRESENT != TAF_SDC_GetCsimStatus())
    {

        pstEccData = (SI_PB_ECC_DATA_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(SI_PB_ECC_DATA_STRU));

        if (VOS_NULL_PTR != pstEccData)
        {
            /* 获取USIM中的紧急呼叫号码 */
            PS_MEM_SET(pstEccData, 0, sizeof(SI_PB_ECC_DATA_STRU));
            NAS_PBAPI_GetXeccNumber(pstEccData);

            for (i = 0; i < TAF_XCALL_MIN(pstEccData->ulReocrdNum, TAF_SDC_MAX_UCIM_ECC_NUM); i++)
            {

                if (pstEccNumInfo->ulEccNumCount >= MN_CALL_MAX_EMC_NUM)
                {
                    break;
                }

                pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ulMcc              = 0xffffffff;
                pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucCategory         = 0;
                pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucValidSimPresent  = MN_CALL_ECC_NUM_VALID_SIM_PRESENT;

                pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucEccNumLen        = USIM_ECC_LEN;
                VOS_MemCpy(pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].aucEccNum,
                           pstEccData->astEccRecord[i].aucEccCode,
                           USIM_ECC_LEN);
                pstEccNumInfo->ulEccNumCount++;

            }

            /* 内存释放 */
            PS_MEM_FREE(WUEPS_PID_TAF,pstEccData);
        }
    }

    /* 列表未满,将APP定制的紧急呼号码加入消息 */
    pstCustomCallEmerNumCtx = TAF_SDC_GetCustomCallEccNumCtx();
    for (i = 0; i < TAF_XCALL_MIN(pstCustomCallEmerNumCtx->stCustomEccNumList.ucEccNumCount,TAF_SDC_MAX_CUSTOM_ECC_NUM); i++)
    {
        if (pstEccNumInfo->ulEccNumCount >= MN_CALL_MAX_EMC_NUM)
        {
            break;
        }

        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ulMcc
            = pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].ulMcc;

        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucCategory
            = pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].ucCategory;

        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucValidSimPresent
            = pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].ucValidSimPresent;

        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucEccNumLen
            = pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].ucEccNumLen;

        VOS_MemCpy(pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].aucEccNum,
                   pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].aucEccNum,
                   pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].ucEccNumLen);

        pstEccNumInfo->ulEccNumCount++;

    }


}

/* 1. Buffer操作函数从XCallProcApp挪到XCallCtx.c中
   2. Cont DTMF和BURST DTMF消息公用一个缓存
*/
/*****************************************************************************
 函 数 名  : TAF_XCALL_GetDtmfBufCnt
 功能描述  : 获取CALL模块BURST DTMF和CONT DTMF的缓存个数
 输入参数  : VOS_UINT8   ucCallId
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成函数
  2.日    期   : 2015年7月29日
    作    者   : l00324781
    修改内容   : Iter16修改,Cont DTMF和Burst DTMF缓存合一
*****************************************************************************/
VOS_UINT8 TAF_XCALL_GetDtmfBufCnt(VOS_UINT8 ucCallId)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

    return pstCallEntity->stDtmfBuffer.ucDtmfCnt;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_IncrementDtmfBufCnt
 功能描述  : CALL模块DTMF的缓存个数自增1
 输入参数  : VOS_UINT8   ucCallId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成函数
  2.日    期   : 2015年7月29日
    作    者   : l00324781
    修改内容   : Iter16修改,Cont DTMF和Burst DTMF缓存合一

*****************************************************************************/
VOS_VOID TAF_XCALL_IncrementDtmfBufCnt(VOS_UINT8   ucCallId)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

    pstCallEntity->stDtmfBuffer.ucDtmfCnt++;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_DecrementDtmfBufCnt
 功能描述  : CALL模块DTMF的缓存个数自检1
 输入参数  : VOS_UINT8   ucCallId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成函数
  2.日    期   : 2015年7月29日
    作    者   : l00324781
    修改内容   : Iter16修改,Cont DTMF和Burst DTMF缓存合一
*****************************************************************************/
VOS_VOID TAF_XCALL_DecrementDtmfBufCnt(VOS_UINT8   ucCallId)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

    pstCallEntity->stDtmfBuffer.ucDtmfCnt--;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_GetDtmfBuffListHead
 功能描述  : 获取CALL模块DTMF的缓存的头结点
 输入参数  : VOS_UINT8   ucCallId
 输出参数  : 无
 返 回 值  : HI_LIST_S
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成函数
  2.日    期   : 2015年7月29日
    作    者   : l00324781
    修改内容   : Iter16修改，Cont DTMF和Burst DTMF缓存合一
*****************************************************************************/
HI_LIST_S* TAF_XCALL_GetDtmfBuffListHead(VOS_UINT8   ucCallId)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

    return &(pstCallEntity->stDtmfBuffer.stList);
}


/*****************************************************************************
 函 数 名  : TAF_XCALL_DelDtmfNode
 功能描述  : 删除DTMF缓存链表中的节点
 输入参数  : pstNode    -- 需要删除DTMF缓存链表中的节点
           : ucCallId   -- Call 实例号
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成函数
  2.日    期   : 2015年7月29日
    作    者   : l00324781
    修改内容   : Iter16修改，Cont DTMF 和Burst DTMF缓存合一
*****************************************************************************/
VOS_VOID TAF_XCALL_DelDtmfNode(
    TAF_XCALL_DTMF_NODE_STRU     *pstNode,
    VOS_UINT8                     ucCallId
)
{
    /* 从过滤表中删除节点 */
    msp_list_del(&pstNode->stList);

    /* 释放节点内存 */
    PS_MEM_FREE(WUEPS_PID_TAF, pstNode);

    TAF_XCALL_DecrementDtmfBufCnt(ucCallId);

    return;
}
/*****************************************************************************
 函 数 名  : TAF_XCALL_AddBurstDtmfInfo
 功能描述  : 增加DTMF信息到DTMF缓存
 输入参数  : pstDtmfInfo   -- 新增的DTMF信息
 输出参数  : 无
 返 回 值  : TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ENUM_U8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成函数
  2.日    期   : 2015年7月29日
    作    者   : l00324781
    修改内容   : Iter16修改，Cont DTMF和Burst DTMF缓存合一
*****************************************************************************/
TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ENUM_U8 TAF_XCALL_AddBurstDtmfInfo(
    TAF_CALL_BURST_DTMF_REQ_MSG_STRU   *pstBurstDtmfInfo
)
{
    /*lint -e429 -e830*/
    TAF_XCALL_DTMF_NODE_STRU           *pstNode       = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(pstBurstDtmfInfo->stBurstDTMFPara.ucCallId);

    /* 申请过滤表节点内存 */
    pstNode = (TAF_XCALL_DTMF_NODE_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_XCALL_DTMF_NODE_STRU));
    if (VOS_NULL_PTR == pstNode)
    {
        return TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ALLOC_MEM_FAIL;
    }

    PS_MEM_CPY(&pstNode->unDtmf.stBurstDtmf, &pstBurstDtmfInfo->stBurstDTMFPara, sizeof(TAF_CALL_BURST_DTMF_PARA_STRU));
    pstNode->enMsgType = TAF_CALL_APP_SEND_BURST_DTMF_REQ;

    /* 将节点增加到DTMF缓存链表中 */
    msp_list_add_tail(&pstNode->stList, &pstCallEntity->stDtmfBuffer.stList);

    return TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_SUCCESS;
    /*lint +e429 +e830*/

}
/*****************************************************************************
 函 数 名  : TAF_XCALL_SaveBurstDtmfInfo
 功能描述  : 将DTMF信息保存到DTMF缓存中
 输入参数  : pstDtmfInfo    -- 需要保存到缓存中的DTMF信息
 输出参数  : 无
 返 回 值  : TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ENUM_U8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成函数
  2.日    期   : 2015年7月29日
    作    者   : l00324781
    修改内容   : Iter16修改，Cont DTMF 和Burst DTMF缓存合一
*****************************************************************************/
TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ENUM_U8 TAF_XCALL_SaveBurstDtmfInfo(
    TAF_CALL_BURST_DTMF_REQ_MSG_STRU   *pstBurstDtmfInfo
)
{
    TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ENUM_U8             enResult;
    VOS_UINT8                                               ucDtmfCnt;

    /* 判断缓存是否已经满了 */
    ucDtmfCnt = TAF_XCALL_GetDtmfBufCnt(pstBurstDtmfInfo->stBurstDTMFPara.ucCallId);
    if (TAF_XCALL_DTMF_BUF_MAX_CNT <= ucDtmfCnt)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_XCALL_SaveBurstDtmfInfo: DTMF Buffer is full ");
        return TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_BUFFER_FULL;
    }

    /* 将BURST DTMF信息保存到缓存中 */
    enResult = TAF_XCALL_AddBurstDtmfInfo(pstBurstDtmfInfo);
    if (TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_SUCCESS != enResult)
    {
        return enResult;
    }

    /* 将DTMF的缓存个数加一 */
    TAF_XCALL_IncrementDtmfBufCnt(pstBurstDtmfInfo->stBurstDTMFPara.ucCallId);

    return TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_SUCCESS;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_CleanDtmfBuff
 功能描述  : 重置DTM缓存信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成函数
  2.日    期   : 2015年7月29日
    作    者   : l00324781
    修改内容   : Iter16修改，Cont DTMF 和Burst DTMF缓存合一
*****************************************************************************/
VOS_VOID TAF_XCALL_CleanDtmfBuff(VOS_UINT8   ucCallId)
{
    HI_LIST_S                          *pstMe       = VOS_NULL_PTR;
    HI_LIST_S                          *pstTmp      = VOS_NULL_PTR;
    HI_LIST_S                          *pstHead     = VOS_NULL_PTR;
    TAF_XCALL_DTMF_NODE_STRU           *pstNode     = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstXcallCtx = VOS_NULL_PTR;

   /* 如果没有缓存，则直接退出 */
    if (0 == TAF_XCALL_GetDtmfBufCnt(ucCallId))
    {
        return;
    }

    /* 释放缓存内存 */
    /*lint -e961*/
    /* 循环遍历过滤表，并释放过滤表的所有节点 */
    pstHead = TAF_XCALL_GetDtmfBuffListHead(ucCallId);
    msp_list_for_each_safe(pstMe, pstTmp, pstHead)
    /*lint +e961*/
    {
        /*lint -e961*/
        pstNode = msp_list_entry(pstMe, TAF_XCALL_DTMF_NODE_STRU, stList);
        /*lint +e961*/

        if (TAF_CALL_APP_SEND_BURST_DTMF_REQ == pstNode->enMsgType)
        {
            pstXcallCtx = TAF_XCALL_GetCallEntityAddr(pstNode->unDtmf.stBurstDtmf.ucCallId);

            /* 重置时，需要给缓存中的所有BURST DTMF信息回复正式响应 */
            TAF_XCALL_SndBurstDTMFRslt(pstXcallCtx->stClientInfo.usClientId,
                                       pstXcallCtx->stClientInfo.ucOpId,
                                       VOS_ERR);
        }
        else if (TAF_CALL_APP_SEND_CONT_DTMF_REQ == pstNode->enMsgType)
        {
            pstXcallCtx = TAF_XCALL_GetCallEntityAddr(pstNode->unDtmf.stContDtmf.ucCallId);

            /* 重置时，需要给缓存中的所有CONT DTMF信息回复正式响应 */
            TAF_XCALL_SndContDTMFRslt(pstXcallCtx->stClientInfo.usClientId,
                                      pstXcallCtx->stClientInfo.ucOpId,
                                      VOS_ERR);
        }
        else /* 目前只缓存CONT DTMF和BURST DTMF,其它类型错误 */
        {
            TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_XCALL_CleanDtmfBuff: Node MsgType Error ", pstNode->enMsgType);
        }

        /* 从过滤表中删除节点 */
        TAF_XCALL_DelDtmfNode(pstNode, ucCallId);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcDtmfBuffer
 功能描述  :收到XCC的结果后，处理DTMF缓存，结果包括Cont DTMF 和Burst DTMF 的REQ结果
 输入参数  : VOS_UINT8    ucCallIds
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成函数
  2.日    期   : 2015年7月29日
    作    者   : l00324781
    修改内容   : Iter16修改，Cont DTMF 和Burst DTMF缓存合一
  3.日    期   : 2015年8月18日
    作    者   : l00324781
    修改内容   : DTS2015081708770修改，Start Cont DTMF Req发送后，启动定时器
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcDtmfBuffer(VOS_UINT8 ucCallId)
{
    TAF_XCALL_DTMF_NODE_STRU           *pstNode             = VOS_NULL_PTR;
    TAF_CALL_BURST_DTMF_PARA_STRU       stBurstDtmfCurInfo;
    TAF_CALL_CONT_DTMF_PARA_STRU        stContDtmfCurInfo;
    TAF_XCALL_CALL_ENTITY_STRU         *pstXcallCtx;
    HI_LIST_S                          *pstMe       = VOS_NULL_PTR;
    HI_LIST_S                          *pstTmp      = VOS_NULL_PTR;
    HI_LIST_S                          *pstHead     = VOS_NULL_PTR;

    PS_MEM_SET(&stBurstDtmfCurInfo, 0x0, sizeof(TAF_CALL_BURST_DTMF_PARA_STRU));
    PS_MEM_SET(&stContDtmfCurInfo, 0x0, sizeof(TAF_CALL_CONT_DTMF_PARA_STRU));

    /* 如果没有缓存，则直接退出 */
    if (0 == TAF_XCALL_GetDtmfBufCnt(ucCallId))
    {
        return;
    }

    /* 如果需处理DTMF缓存，且状态不为ACTIVE，则清缓存 */
    if (MN_CALL_S_ACTIVE != TAF_XCALL_GetCallState(ucCallId))
    {
        /* 清DTMF缓存 */
        TAF_XCALL_CleanDtmfBuff(ucCallId);
        return;
     }

    /*lint -e961*/
    /* 循环遍历过滤表，并释放过滤表的所有节点 */
    pstHead = TAF_XCALL_GetDtmfBuffListHead(ucCallId);

    msp_list_for_each_safe(pstMe, pstTmp, pstHead)
    /*lint +e961*/
    {
        /*lint -e961*/
        pstNode     = msp_list_entry(pstMe, TAF_XCALL_DTMF_NODE_STRU, stList);
        /*lint +e961*/

        /* 下一条NODE可能是BURST DTMF或CONT DTMF，根据类型进入不同处理分支 */
        if (TAF_CALL_APP_SEND_BURST_DTMF_REQ == pstNode->enMsgType)
        {
            /* 如果两个callid 不一致，则继续查找 */
            if(ucCallId != pstNode->unDtmf.stBurstDtmf.ucCallId)
            {
                /* 同一Call实例下的缓存链表中保存的消息的call id必定相同。如果不同，属于异常 */
                TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_XCALL_ProcDtmfBuffer: Call ID is not equal ");

                pstXcallCtx = TAF_XCALL_GetCallEntityAddr(pstNode->unDtmf.stBurstDtmf.ucCallId);
                TAF_XCALL_SndBurstDTMFRslt(pstXcallCtx->stClientInfo.usClientId,
                                          pstXcallCtx->stClientInfo.ucOpId,
                                          VOS_ERR);

                TAF_XCALL_DelDtmfNode(pstNode, pstNode->unDtmf.stBurstDtmf.ucCallId);
                continue;
            }

            PS_MEM_CPY(&stBurstDtmfCurInfo, &pstNode->unDtmf.stBurstDtmf, sizeof(TAF_CALL_BURST_DTMF_PARA_STRU));

            /* 从过滤表中删除节点 */
            TAF_XCALL_DelDtmfNode(pstNode, pstNode->unDtmf.stBurstDtmf.ucCallId);

            if (TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_SUCCESS == TAF_XCALL_SndXccBurstDTMFReq(&stBurstDtmfCurInfo))
            {
                /* 发送成功，设置标识位为VOS_TRUE,直接退出循环 */
                TAF_XCALL_SetWaitForXCCDTMFCnfFlag(stBurstDtmfCurInfo.ucCallId, TAF_XCALL_WAIT_XCC_CNF_BURST_DTMF);
                break;
            }

            /* 发送失败，从call id对应的实体中获取信息，回复失败的结果，继续处理下一条缓存 */
            pstXcallCtx = TAF_XCALL_GetCallEntityAddr(stBurstDtmfCurInfo.ucCallId);

            TAF_XCALL_SndBurstDTMFRslt(pstXcallCtx->stClientInfo.usClientId,
                                       pstXcallCtx->stClientInfo.ucOpId,
                                       VOS_ERR);
        }
        else if (TAF_CALL_APP_SEND_CONT_DTMF_REQ == pstNode->enMsgType)
        {
            /* 如果两个callid 不一致，则继续查找 */
            if (ucCallId != pstNode->unDtmf.stContDtmf.ucCallId)
            {
                /* 同一Call实例下的缓存链表中保存的消息的call id必定相同。如果不同，属于异常 */
                TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_XCALL_ProcDtmfBuffer: Call ID is not equal ");

                pstXcallCtx = TAF_XCALL_GetCallEntityAddr(pstNode->unDtmf.stContDtmf.ucCallId);
                TAF_XCALL_SndContDTMFRslt(pstXcallCtx->stClientInfo.usClientId,
                                          pstXcallCtx->stClientInfo.ucOpId,
                                          VOS_ERR);

                TAF_XCALL_DelDtmfNode(pstNode, pstNode->unDtmf.stContDtmf.ucCallId);

                continue;
            }

            PS_MEM_CPY(&stContDtmfCurInfo, &pstNode->unDtmf.stContDtmf, sizeof(TAF_CALL_CONT_DTMF_PARA_STRU));

            /* 从过滤表中删除节点 */
            TAF_XCALL_DelDtmfNode(pstNode, pstNode->unDtmf.stContDtmf.ucCallId);

            if (TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_SUCCESS == TAF_XCALL_SndXccContDTMFReq(&stContDtmfCurInfo))
            {
                /* 发送成功，设置标识位为VOS_TRUE,直接退出循环 */
                if (TAF_CALL_CONT_DTMF_START == stContDtmfCurInfo.enSwitch)
                {
                    TAF_XCALL_SetWaitForXCCDTMFCnfFlag(stContDtmfCurInfo.ucCallId, TAF_XCALL_WAIT_XCC_CNF_START_CONT_DTMF);
                }
                else
                {
                    TAF_XCALL_SetWaitForXCCDTMFCnfFlag(stContDtmfCurInfo.ucCallId, TAF_XCALL_WAIT_XCC_CNF_STOP_CONT_DTMF);
                }

                break;
            }

            /* 发送失败，从call id对应的实体中获取信息，回复失败的结果，继续处理下一条缓存 */
            pstXcallCtx = TAF_XCALL_GetCallEntityAddr(stContDtmfCurInfo.ucCallId);

            TAF_XCALL_SndContDTMFRslt(pstXcallCtx->stClientInfo.usClientId,
                                      pstXcallCtx->stClientInfo.ucOpId,
                                      VOS_ERR);
        }
        else
        {
            TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_XCALL_ProcBurstDtmfBuffer: Node MsgType Error ", pstNode->enMsgType);

            TAF_XCALL_DelDtmfNode(pstNode, pstNode->unDtmf.stContDtmf.ucCallId);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_AddContDtmfInfo
 功能描述  : 增加CONT DTMF信息到DTMF缓存
 输入参数  : pstContDtmfInfo   -- 新增的CONT DTMF信息
 输出参数  : 无
 返 回 值  : TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM_U8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月24日
    作    者   : l00324781
    修改内容   : Iter16 新生成函数
*****************************************************************************/
TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM_U8 TAF_XCALL_AddContDtmfInfo(
    TAF_CALL_CONT_DTMF_REQ_MSG_STRU    *pstContDtmfInfo
)
{
    /*lint -e429 -e830*/
    TAF_XCALL_DTMF_NODE_STRU           *pstNode       = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(pstContDtmfInfo->stContDTMFPara.ucCallId);

    /* 申请过滤表节点内存 */
    pstNode = (TAF_XCALL_DTMF_NODE_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_XCALL_DTMF_NODE_STRU));
    if (VOS_NULL_PTR == pstNode)
    {
        return TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ALLOC_MEM_FAIL;
    }

    PS_MEM_CPY(&pstNode->unDtmf.stContDtmf, &pstContDtmfInfo->stContDTMFPara, sizeof(TAF_CALL_CONT_DTMF_PARA_STRU));
    pstNode->enMsgType = TAF_CALL_APP_SEND_CONT_DTMF_REQ;

    /* 将节点增加到 DTMF缓存链表中 */
    msp_list_add_tail(&pstNode->stList, &pstCallEntity->stDtmfBuffer.stList);

    return TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_SUCCESS;
    /*lint +e429 +e830*/
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_SaveContDtmfInfo
 功能描述  : 将CONT DTMF信息保存到CONT DTMF缓存中
 输入参数  : pstContDtmfInfo    -- 需要保存到缓存中的CONT DTMF信息
 输出参数  : 无
 返 回 值  : TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM_U8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月24日
    作    者   : l00324781
    修改内容   : Iter16 新生成函数
*****************************************************************************/
TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM_U8 TAF_XCALL_SaveContDtmfInfo(
    TAF_CALL_CONT_DTMF_REQ_MSG_STRU    *pstContDtmfInfo
)
{
    TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM_U8              enResult;
    VOS_UINT8                                               ucDtmfCnt;

    /* 判断缓存是否已经满了 */
    ucDtmfCnt = TAF_XCALL_GetDtmfBufCnt(pstContDtmfInfo->stContDTMFPara.ucCallId);
    if (TAF_XCALL_DTMF_BUF_MAX_CNT <= ucDtmfCnt)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_XCALL_SaveContDtmfInfo: DTMF Buffer is full ");
        return TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_BUFFER_FULL;
    }

    /* 将CONT DTMF信息保存到缓存中 */
    enResult = TAF_XCALL_AddContDtmfInfo(pstContDtmfInfo);
    if (TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_SUCCESS != enResult)
    {
        return enResult;
    }

    /* 将CONT DTMF的缓存个数加一 */
    TAF_XCALL_IncrementDtmfBufCnt(pstContDtmfInfo->stContDTMFPara.ucCallId);

    return TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_SUCCESS;
}


/*****************************************************************************
 函 数 名  : TAF_XCALL_GetStartAndStopContDtmfIntervalLen
 功能描述  : 获取保存在Ctx中的ulStartAndStopContDtmfInterval 定时器时长,单位:ms
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32   定时器时长
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月18日
    作    者   : l00324781
    修改内容   : DTS2015081708770 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XCALL_GetStartAndStopContDtmfIntervalLen(VOS_VOID)
{
    return TAF_XCALL_GetConfigInfo()->ulStartAndStopContDtmfIntervalLen;
}


/*****************************************************************************
 函 数 名  : TAF_XCALL_GetAllUsedCallId
 功能描述  : 密话上下文初始
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32 -- 返回call id个数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XCALL_GetAllUsedCallId(
    VOS_UINT8                          *pucCallIds
)
{
    TAF_XCALL_CTX_STRU                 *pstXcallCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulCallIdNum;
    VOS_UINT32                          i;

    ulCallIdNum = 0;

    pstXcallCtx = TAF_XCALL_GetCtxAddr();

    for (i = 0; i < TAF_XCALL_CALL_ENTITY_MAX_NUM; i++)
    {
        if (VOS_TRUE == pstXcallCtx->astCallEntity[i].ulUsed)
        {
            *pucCallIds++ = (VOS_UINT8)(i + 1);
            ulCallIdNum++;
        }
    }

    return ulCallIdNum;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_SetCsCallExistFlg
 功能描述  : 设置当前是否处于CS CALL 和紧急呼标记
 输入参数  : ucCallExitFlg - 是否有call
             enCallType    - call type
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2016年01月10日
   作    者   : h00313353
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_SetCsCallExistFlg(
    VOS_UINT8                           ucCallExitFlg,
    MN_CALL_TYPE_ENUM_U8                enCallType
)
{
    /* 无电话，肯定无紧急呼 */
    if (VOS_FALSE == ucCallExitFlg)
    {
        TAF_SDC_SetCsCallExistFlg(VOS_FALSE);
        TAF_SDC_SetCsEccExistFlg(VOS_FALSE);

        TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_XCALL_SetCsCallExistFlg:Set Call And Ecc Call Exist Flg To False!");

        return;
    }

    /* 有电话，根据call type设置紧急呼标记 */
    TAF_SDC_SetCsCallExistFlg(VOS_TRUE);

    if (MN_CALL_TYPE_EMERGENCY == enCallType)
    {
        TAF_SDC_SetCsEccExistFlg(VOS_TRUE);
    }
    else
    {
        TAF_SDC_SetCsEccExistFlg(VOS_FALSE);
    }

    TAF_INFO_LOG1(WUEPS_PID_TAF, "TAF_XCALL_SetCsCallExistFlg:CallType:", (VOS_UINT32)enCallType);

    return;
}


#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
/*****************************************************************************
 函 数 名  : TAF_XCALL_InitEncVoiceCtx
 功能描述  : 密话上下文初始
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_InitEncVoiceCtx(VOS_VOID)
{
    TAF_XCALL_InitEncVoiceKeyNegotiateCtx();

    TAF_XCALL_InitEncVoiceRemoteCtrlCtx();

    TAF_XCALL_InitEncVoiceKmcUpdateCtx();

    TAF_XCALL_InitEncVoiceOpIdMgmtCtx();

    TAF_XCALL_InitEncVoiceParaInfoCtx();

    TAF_XCALL_CipherEccInit();
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_InitEncVoiceKeyNegotiateCtx
 功能描述  : 语音加密KEY协商初始化
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_InitEncVoiceKeyNegotiateCtx(VOS_VOID)
{
    TAF_XCALL_KS_NEGOTIATE_CTX         *pstKsNegoCtx = VOS_NULL_PTR;

    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    PS_MEM_SET(pstKsNegoCtx, 0, sizeof(TAF_XCALL_KS_NEGOTIATE_CTX));

    pstKsNegoCtx->enVoiceEncState      = TAF_XCALL_VOICE_ENCRYPT_STA_INACTIVE;

    pstKsNegoCtx->stCcaCtrl.usClientId = MN_GetRealClientId(MN_CLIENT_ID_BROADCAST, WUEPS_PID_TAF);
    pstKsNegoCtx->stCcaCtrl.ulModuleId = WUEPS_PID_AT;
    pstKsNegoCtx->stCcaCtrl.ucOpId     = 0;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_InitEncVoiceRemoteCtrlCtx
 功能描述  : 远程控制操作上下文初始化
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_InitEncVoiceRemoteCtrlCtx(VOS_VOID)
{
    TAF_XCALL_REMOTE_CTRL_CTX         *pstRemoteCtrlCtx = VOS_NULL_PTR;

    pstRemoteCtrlCtx = TAF_XCALL_GetRemoteCtrlCtxAddr();

    PS_MEM_SET(pstRemoteCtrlCtx, 0, sizeof(TAF_XCALL_REMOTE_CTRL_CTX));

    pstRemoteCtrlCtx->enRemoteCtrlState    = TAF_XCALL_REMOTE_CTRL_STA_INACTIVE;
    pstRemoteCtrlCtx->enRemoteCtrlCmdType  = TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_BUTT;

    pstRemoteCtrlCtx->stCcaCtrl.usClientId = MN_GetRealClientId(MN_CLIENT_ID_BROADCAST, WUEPS_PID_TAF);
    pstRemoteCtrlCtx->stCcaCtrl.ulModuleId = WUEPS_PID_AT;
    pstRemoteCtrlCtx->stCcaCtrl.ucOpId     = 0;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_InitEncVoiceOpIdMgmtCtx
 功能描述  : 初始化OPID管理上下文信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_InitEncVoiceOpIdMgmtCtx(VOS_VOID)
{
    TAF_XCALL_XSMS_SEND_REQ_OPID_MGMT_CTX                  *pstOpIdMgmtCtx = VOS_NULL_PTR;

    pstOpIdMgmtCtx = TAF_XCALL_GetOpIdMgmtCtxAddr();

    PS_MEM_SET(pstOpIdMgmtCtx, 0, sizeof(TAF_XCALL_XSMS_SEND_REQ_OPID_MGMT_CTX));
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_InitEncVoiceParaInfoCtx
 功能描述  : 初始化密话功能参数参数信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_InitEncVoiceParaInfoCtx(VOS_VOID)
{
    TAF_XCALL_ENCRYPT_VOICE_PARA_INFO_CTX                  *pstEncVoiceParaInfo = VOS_NULL_PTR;

    pstEncVoiceParaInfo = TAF_XCALL_GetEncVoiceInfoCtxAddr();

    PS_MEM_SET(pstEncVoiceParaInfo, 0, sizeof(TAF_XCALL_ENCRYPT_VOICE_PARA_INFO_CTX));

    pstEncVoiceParaInfo->enTestMode = TAF_CALL_APP_SET_EC_TEST_MODE_DISABLE;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_GetVoiceEncryptCtxAddr
 功能描述  : 获取加密上下文信息地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_XCALL_ENCRYPT_VOICE_CTX_STRU -- 返回加密上下文信息地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月24日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
TAF_XCALL_ENCRYPT_VOICE_CTX_STRU* TAF_XCALL_GetVoiceEncryptCtxAddr(VOS_VOID)
{
    return &(TAF_XCALL_GetCtxAddr()->stEncVoiceCtx);
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_GetOpIdMgmtCtxAddr
 功能描述  : 获取opId管理上下文信息地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_XCALL_XSMS_SEND_REQ_OPID_MGMT_CTX -- 返回短消息发送OPID管理信息上下文
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月24日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
TAF_XCALL_XSMS_SEND_REQ_OPID_MGMT_CTX* TAF_XCALL_GetOpIdMgmtCtxAddr(VOS_VOID)
{
    return &(TAF_XCALL_GetVoiceEncryptCtxAddr()->stOpIdMgmtCtx);
}


/*****************************************************************************
 函 数 名  : TAF_XCALL_GetRemoteCtrlCtxAddr
 功能描述  : 获取远程控制操作流程上下文地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_XCALL_REMOTE_CTRL_CTX -- 返回远程控制操作流程上下文地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月24日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
TAF_XCALL_REMOTE_CTRL_CTX* TAF_XCALL_GetRemoteCtrlCtxAddr(VOS_VOID)
{
    return &(TAF_XCALL_GetVoiceEncryptCtxAddr()->stRemoteCtrlCtx);
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_GetKsNegotiateCtxAddr
 功能描述  : 获取KS协商上下文地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_XCALL_KS_NEGOTIATE_CTX -- 返回KS协商上下文地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月24日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
TAF_XCALL_KS_NEGOTIATE_CTX* TAF_XCALL_GetKsNegotiateCtxAddr(VOS_VOID)
{
    return &(TAF_XCALL_GetVoiceEncryptCtxAddr()->stNegotiateCtx);
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_GetEncVoiceInfoCtxAddr
 功能描述  : 获取密话功能相关的参数信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_XCALL_ENCRYPT_VOICE_PARA_INFO_CTX -- 密话功能相关的参数信息地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月24日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
TAF_XCALL_ENCRYPT_VOICE_PARA_INFO_CTX* TAF_XCALL_GetEncVoiceInfoCtxAddr(VOS_VOID)
{
    return &(TAF_XCALL_GetVoiceEncryptCtxAddr()->stEncVoiceInfoCtx);
}


/*****************************************************************************
 函 数 名  : TAF_XCALL_GetVoiceEncryptNegotiateState
 功能描述  : 获取密话协商状态
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_XCALL_VOICE_ENCRYPT_STA_ENUM_UINT32 -- 返回密话协商当前状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月24日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
TAF_XCALL_VOICE_ENCRYPT_STA_ENUM_UINT32 TAF_XCALL_GetVoiceEncryptNegotiateState(VOS_VOID)
{
    return TAF_XCALL_GetVoiceEncryptCtxAddr()->stNegotiateCtx.enVoiceEncState;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_GetVoiceEncryptPublicKeyAndVersionNumber
 功能描述  : 获取ECC的公钥以及公钥版本号
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_XCALL_ECC_PUB_KEY_INFO_STRU
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : h00313353
    修改内容   : Iteration 19
*****************************************************************************/
TAF_XCALL_ECC_PUB_KEY_INFO_STRU* TAF_XCALL_GetVoiceEncryptPublicKeyAndVersionNumber( VOS_VOID )
{
    return &(TAF_XCALL_GetCtxAddr()->stEncVoiceCtx.stEncVoiceInfoCtx.stEccPubKeyInfo);
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_GetVoiceEncryptCapCfgPara
 功能描述  : 获取语音加密能力配置参数，即加密能力以及动态配置开关
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_XCALL_ECC_SRV_CAP_INFO_STRU
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : h00313353
    修改内容   : Iteration 19
*****************************************************************************/
TAF_XCALL_ECC_SRV_CAP_INFO_STRU* TAF_XCALL_GetVoiceEncryptCapCfgPara( VOS_VOID )
{
    return &(TAF_XCALL_GetCtxAddr()->stEncVoiceCtx.stEncVoiceInfoCtx.stEccSrvCapInfo);
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_GetVoiceEncryptSecInfoEraseSysTime
 功能描述  : 获取安全信息擦除系统时间
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_STD_TIME_ZONE_TYPE_STRUs
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : h00313353
    修改内容   : Iteration 19
*****************************************************************************/
TAF_STD_TIME_ZONE_TYPE_STRU* TAF_XCALL_GetVoiceEncryptSecInfoEraseSysTime( VOS_VOID )
{
    return &(TAF_XCALL_GetCtxAddr()->stEncVoiceCtx.stEncVoiceInfoCtx.stLastInfoEraseTime);
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_GetVoiceEncryptPassWordResetSysTime
 功能描述  : 获取密码重置系统时间
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_STD_TIME_ZONE_TYPE_STRUs
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : h00313353
    修改内容   : Iteration 19
*****************************************************************************/
TAF_STD_TIME_ZONE_TYPE_STRU* TAF_XCALL_GetVoiceEncryptPassWordResetSysTime( VOS_VOID )
{
    return &(TAF_XCALL_GetCtxAddr()->stEncVoiceCtx.stEncVoiceInfoCtx.stLastPassworResetTime);
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_GetVoiceEncryptReqDelaySendTimerLen
 功能描述  : 获取语音加密延时密钥请求发送时长
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : h00313353
    修改内容   : Iteration 19
*****************************************************************************/
VOS_UINT16 TAF_XCALL_GetVoiceEncryptReqDelaySendTimerLen( VOS_VOID )
{
    return TAF_XCALL_GetCtxAddr()->stEncVoiceCtx.stEncVoiceInfoCtx.usDelayEncVoiceReqTimerLen;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_GetRemoteCtrlWaitApAnswerTimerLen
 功能描述  : 获取远程控制等待AP应答定时器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT16
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月18日
    作    者   : y00245242
    修改内容   : Iteration 19
*****************************************************************************/
VOS_UINT16 TAF_XCALL_GetRemoteCtrlWaitApAnswerTimerLen(VOS_VOID)
{
    return TAF_XCALL_GetCtxAddr()->stEncVoiceCtx.stEncVoiceInfoCtx.usRemoteCtrlAnswerTimerLen;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_IsEccTestModeEnable
 功能描述  : 判断ECC测试模式是否开启
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_BOOL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : c00177591
    修改内容   : 新生成函数
*****************************************************************************/
TAF_CALL_APP_SET_EC_TEST_MODE_ENUM_UINT32 TAF_XCALL_GetVoiceEncryptTestMode( VOS_VOID )
{
    return TAF_XCALL_GetCtxAddr()->stEncVoiceCtx.stEncVoiceInfoCtx.enTestMode;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_GetPubKeyUpdateCtxAddr
 功能描述  : 获取公钥更新操作流程上下文地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_XCALL_PUBLIC_KEY_UPDATE_CTX -- 返回公钥更新操作流程上下文地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月27日
    作    者   : l00359089
    修改内容   : Iteration 19
*****************************************************************************/
TAF_XCALL_PUBLIC_KEY_UPDATE_CTX* TAF_XCALL_GetPubKeyUpdateCtxAddr( VOS_VOID )
{
    return &(TAF_XCALL_GetCtxAddr()->stEncVoiceCtx.stPubKeyUpdateCtx);
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_InitEncVoiceKmcUpdateCtx
 功能描述  : 语音加密KMC 公钥更新流程上下文初始化
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月27日
    作    者   : l00359089
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_InitEncVoiceKmcUpdateCtx(VOS_VOID)
{
    TAF_XCALL_PUBLIC_KEY_UPDATE_CTX    *pstPubKeyUpdateCtx = VOS_NULL_PTR;

    pstPubKeyUpdateCtx = TAF_XCALL_GetPubKeyUpdateCtxAddr();

    PS_MEM_SET(pstPubKeyUpdateCtx, 0, sizeof(TAF_XCALL_PUBLIC_KEY_UPDATE_CTX));

    pstPubKeyUpdateCtx->enK0UpdateState = TAF_XCALL_K0_UPATE_STA_INACTIVE;
}


#endif

/*****************************************************************************
 函 数 名  : TAF_XCALL_UpdatePrivacyMode
 功能描述  : 更新指定呼叫的Privacy Mode
 输入参数  : VOS_UINT8                           ucCallId,
             TAF_CALL_PRIVACY_MODE_ENUM_UINT8    enPrivacyMode
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016-1-6
    作    者   : l00359089
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_UpdatePrivacyMode(
    VOS_UINT8                           ucCallId,
    TAF_CALL_PRIVACY_MODE_ENUM_UINT8    enPrivacyMode
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    if (TAF_CALL_PRIVACY_MODE_BUTT == enPrivacyMode)
    {
        return;
    }

    pstCallEntity                       = TAF_XCALL_GetCallEntityAddr(ucCallId);

    pstCallEntity->enPrivacyMode        = enPrivacyMode;

    return;
}

/*lint -restore*/
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */





