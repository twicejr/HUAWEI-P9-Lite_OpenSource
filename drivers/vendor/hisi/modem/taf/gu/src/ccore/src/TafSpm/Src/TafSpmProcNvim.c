/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafSpmProcNvim.c
  版 本 号   : 初稿
  作    者   : W00176964
  生成日期   : 2013年5月22日
  最近修改   :
  功能描述   : TafSpmProcNvim.C文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年5月22日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "PsTypeDef.h"
#include "TafSpmCtx.h"
#include "TafLog.h"
#include "PsNvId.h"
#include "NVIM_Interface.h"
#include "TafNvInterface.h"
#include "MnComm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 常量定义
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_TAF_SPM_PROC_NVIM_C

/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/

/*****************************************************************************
  5 变量定义
*****************************************************************************/


/*****************************************************************************
  6 函数定义
*****************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_SPM_ReadFdnInfoNvim
 功能描述  : 读取en_NV_Item_FDN_Info信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年05月22日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_ReadFdnInfoNvim(VOS_VOID)
{
    TAF_SPM_SERVICE_CTRL_CFG_INFO_STRU *pstServiceCtrlCfgInfo = VOS_NULL_PTR;
    TAF_FDN_NVIM_CONFIG_STRU            stFdnConfig;

    pstServiceCtrlCfgInfo               = TAF_SPM_GetServiceCtrlCfgInfoAddr();

    if (NV_OK != NV_Read(en_NV_Item_FDN_Info,
                         &stFdnConfig,
                         sizeof(TAF_FDN_NVIM_CONFIG_STRU)))
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_ReadNvimInfo():WARNING: en_NV_Item_FDN_Info Error");
        pstServiceCtrlCfgInfo->ulMeStatus = TAF_FDN_CHECK_FEATURE_OFF;

        return;
    }

    pstServiceCtrlCfgInfo->ulMeStatus   = stFdnConfig.ulMeStatus;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_ReadSimCallCtrlNvim
 功能描述  : 读取en_NV_Item_NVIM_SIM_CALL_CONTROL_SUPPORT_FLG信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年05月22日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_ReadSimCallCtrlNvim(VOS_VOID)
{
    TAF_SPM_SERVICE_CTRL_CFG_INFO_STRU                     *pstServiceCtrlCfgInfo = VOS_NULL_PTR;
    MN_CALL_NVIM_SIM_CALL_CONTROL_FLG_STRU                  stSimCallCtrlFlg;

    pstServiceCtrlCfgInfo                           = TAF_SPM_GetServiceCtrlCfgInfoAddr();

    if (NV_OK != NV_Read(en_NV_Item_NVIM_SIM_CALL_CONTROL_SUPPORT_FLG,
                        &stSimCallCtrlFlg,
                        sizeof(MN_CALL_NVIM_SIM_CALL_CONTROL_FLG_STRU)))
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_ReadNvimInfo():WARNING: en_NV_Item_NVIM_SIM_CALL_CONTROL_SUPPORT_FLG Error");
        pstServiceCtrlCfgInfo->ucSimCallCtrlSupportFlg  = VOS_FALSE;

        return;
    }

    pstServiceCtrlCfgInfo->ucSimCallCtrlSupportFlg = stSimCallCtrlFlg.ucSimCallCtrlSupportFlg;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_ReadBufferServiceReqProtectTimerCfgNvim
 功能描述  : 读取NV中缓存cc/ss/sms服务请求保护定时器的配置
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月9日
    作    者   : c00318887
    修改内容   : 新建函数
*****************************************************************************/
VOS_VOID TAF_SPM_ReadBufferServiceReqProtectTimerCfgNvim(VOS_VOID)
{
    TAF_NVIM_BUFFER_SERVICE_REQ_PROTECT_TIMER_CFG_STRU      stSrvReqProtectTimerCfg;
    TAF_SPM_BUFFER_SERVICE_REQ_PROTECT_TIMER_STRU          *pstSrvReqProtectTimerInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulNvLen                   = 0;

    pstSrvReqProtectTimerInfo                               = TAF_SPM_GetBufferServiceReqProtectTimerInfo();

    PS_MEM_SET(&stSrvReqProtectTimerCfg, 0x00, sizeof(stSrvReqProtectTimerCfg));

    (VOS_VOID)NV_GetLength(en_NV_Item_BUFFER_SERVICE_REQ_PROTECT_TIMER_CFG, &ulNvLen);

    if ( ulNvLen > sizeof(TAF_NVIM_BUFFER_SERVICE_REQ_PROTECT_TIMER_CFG_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SPM_ReadBufferServiceReqProtectTimerCfgNvim:read en_NV_Item_BUFFER_SERVICE_REQ_PROTECT_TIMER_CFG len failed");
        return;
    }

    /* 读取NV */
    if (NV_OK != NV_Read(en_NV_Item_BUFFER_SERVICE_REQ_PROTECT_TIMER_CFG,
                         &stSrvReqProtectTimerCfg,
                         sizeof(TAF_NVIM_BUFFER_SERVICE_REQ_PROTECT_TIMER_CFG_STRU)))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SPM_ReadBufferServiceReqProtectTimerCfgNvim:read en_NV_Item_BUFFER_SERVICE_REQ_PROTECT_TIMER_CFG failed");
        return;
    }

    /* 将NV读取的内容保存在全局变量中 */
    pstSrvReqProtectTimerInfo->ulBufferCcProtectTimerLen    = (stSrvReqProtectTimerCfg.ucBufferCcProtectTimerLen * NAS_SPM_ONE_THOUSAND_MILLISECOND);
    pstSrvReqProtectTimerInfo->ulBufferSmsProtectTimerLen   = (stSrvReqProtectTimerCfg.ucBufferSmsProtectTimerLen * NAS_SPM_ONE_THOUSAND_MILLISECOND);
    pstSrvReqProtectTimerInfo->ulBufferSsProtectTimerLen    = (stSrvReqProtectTimerCfg.ucBufferSsProtectTimerLen * NAS_SPM_ONE_THOUSAND_MILLISECOND);

    /* 防止NV值设置过大 */
    if (TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER_VAL < pstSrvReqProtectTimerInfo->ulBufferCcProtectTimerLen)
    {
        pstSrvReqProtectTimerInfo->ulBufferCcProtectTimerLen    = TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER_VAL;
    }
    
    if (TI_TAF_SPM_SMS_SRV_REQ_PROTECT_TIMER_VAL < pstSrvReqProtectTimerInfo->ulBufferSmsProtectTimerLen)
    {
        pstSrvReqProtectTimerInfo->ulBufferSmsProtectTimerLen   = TI_TAF_SPM_SMS_SRV_REQ_PROTECT_TIMER_VAL;
    }
    
    if (TI_TAF_SPM_SS_SRV_REQ_PROTECT_TIMER_VAL < pstSrvReqProtectTimerInfo->ulBufferSsProtectTimerLen)
    {
        pstSrvReqProtectTimerInfo->ulBufferSsProtectTimerLen    = TI_TAF_SPM_SS_SRV_REQ_PROTECT_TIMER_VAL;
    } 

    return;
}


/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-1-15, begin */
/*****************************************************************************
 函 数 名  : TAF_SPM_ReadVideoCallNvim
 功能描述  : 读取en_NV_Item_VIDEO_CALL信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年01月15日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_ReadVideoCallNvim(VOS_VOID)
{
    TAF_SPM_SERVICE_CTRL_CFG_INFO_STRU                     *pstServiceCtrlCfgInfo = VOS_NULL_PTR;
    MN_CALL_NV_ITEM_VIDEO_CALL_STRU                         stVideoCall;

    pstServiceCtrlCfgInfo                           = TAF_SPM_GetServiceCtrlCfgInfoAddr();

    if (NV_OK != NV_Read(en_NV_Item_VIDEO_CALL,
                        &stVideoCall,
                        sizeof(MN_CALL_NV_ITEM_VIDEO_CALL_STRU)))
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_ReadVideoCallNvim():WARNING: en_NV_Item_VIDEO_CALL Error");

        return;
    }

    if (VOS_TRUE == stVideoCall.ucStatus)
    {
        pstServiceCtrlCfgInfo->enVpCfgState = stVideoCall.ucVpCfgState;
    }

    return;
}

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-1-15, end */

/*****************************************************************************
 函 数 名  : TAF_SPM_ReadNvimInfo
 功能描述  : 读取SPM模块的NV信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年05月22日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_ReadNvimInfo(VOS_VOID)
{
    TAF_SPM_ReadFdnInfoNvim();

    TAF_SPM_ReadSimCallCtrlNvim();

    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-1-15, begin */
    TAF_SPM_ReadVideoCallNvim();
    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-1-15, end */

    TAF_SPM_ReadBufferServiceReqProtectTimerCfgNvim();
    
    return;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

