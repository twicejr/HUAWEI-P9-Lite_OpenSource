
/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MNCallCtx.c
  版 本 号   : 初稿
  作    者   : s62952
  生成日期   : 2012年03月03日
  最近修改   :
  功能描述   : MN CALL CTX文件
  函数列表   :

  修改历史   :
  1.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "MnCallCtx.h"

/* Added by l00167671 for NV拆分项目 , 2013-05-17, begin */
#include "NasNvInterface.h"
#include "TafNvInterface.h"
/* Added by l00167671 for NV拆分项目 , 2013-05-17, end*/

/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-17, begin */
#include "MnCallMgmt.h"
#include "MnCallTimer.h"
/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-17, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e(767)*/
#define    THIS_FILE_ID        PS_FILE_ID_MN_CALL_CTX_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* MMC CTX,用于保存MMC状态机,描述表 */
MN_CALL_CONTEXT_STRU                    g_stMnCallCtx;


/*****************************************************************************
   3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : MN_CALL_GetCtx
 功能描述  : 获取当前CALL的CTX
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前call的CTX
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月3日
   作    者   : s62952
   修改内容   : 新生成函数

*****************************************************************************/
MN_CALL_CONTEXT_STRU*  MN_CALL_GetCtx( VOS_VOID )
{
    return &(g_stMnCallCtx);
}

/*****************************************************************************
 函 数 名  : MN_CALL_GetCustomCfgInfo
 功能描述  : 获取CALL中保存特性定制特性信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CALL中保存特性定制特性信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月3日
   作    者   : s62952
   修改内容   : 新生成函数

*****************************************************************************/
MN_CALL_CUSTOM_CFG_INFO_STRU* MN_CALL_GetCustomCfgInfo( VOS_VOID )
{
    return &(MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg);
}

/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-3, begin */
/*****************************************************************************
 函 数 名  : MN_CALL_GetCallRedialCfg
 功能描述  : 获取CALL重拨配置参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回CALL呼叫重拨配置信息

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年4月2日
   作    者   : y00245242
   修改内容   : 为eCall feature增加
*****************************************************************************/
TAF_CALL_REDIAL_CFG_STRU *MN_CALL_GetCallRedialCfg(VOS_VOID)
{
    return &(MN_CALL_GetCustomCfgInfo()->stCallRedialCfgInfo.stCallRedialCfg);
}
/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-3, end */

/*****************************************************************************
 函 数 名  : TAF_CALL_GetCcwaCtrlMode
 功能描述  : 获取呼叫等待的控制模式
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_CALL_CCWA_CTRL_MODE_ENUM_U8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月24日
    作    者   : n00269697
    修改内容   : 新生成函数

*****************************************************************************/
TAF_CALL_CCWA_CTRL_MODE_ENUM_U8 TAF_CALL_GetCcwaCtrlMode(VOS_VOID)
{
    return MN_CALL_GetCustomCfgInfo()->enCcwaCtrlMode;
}

/*****************************************************************************
 函 数 名  : TAF_CALL_SetCcwaCtrlMode
 功能描述  : 设置呼叫等待的控制模式
 输入参数  : TAF_CALL_CCWA_CTRL_MODE_ENUM_U8    enCcwaCtrlMode
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月24日
    作    者   : n00269697
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CALL_SetCcwaCtrlMode(
    TAF_CALL_CCWA_CTRL_MODE_ENUM_U8     enCcwaCtrlMode
)
{
    MN_CALL_GetCustomCfgInfo()->enCcwaCtrlMode = enCcwaCtrlMode;

    return;
}

/*****************************************************************************
 函 数 名  : MN_CALL_GetAppCfgInfo
 功能描述  : 获取CALL中保存的AP配置的信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_CALL_APP_CFG_INFO_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月24日
    作    者   : n00269697
    修改内容   : 新生成函数

*****************************************************************************/
TAF_CALL_APP_CFG_INFO_STRU* MN_CALL_GetAppCfgInfo(VOS_VOID)
{
    return &(MN_CALL_GetCtx()->stMsCfgInfo.stAppCfg);
}

/*****************************************************************************
 函 数 名  : TAF_CALL_SetCcwaiFlg
 功能描述  : 设置IMS域的CCWA的能力标志
 输入参数  : VOS_BOOL                            bCcwaiFlg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月24日
    作    者   : n00269697
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CALL_SetCcwaiFlg(
    VOS_UINT8                           bCcwaiFlg
)
{
    MN_CALL_GetAppCfgInfo()->ucCcwaiFlg = bCcwaiFlg;
}

/*****************************************************************************
 函 数 名  : TAF_CALL_GetCcwaiFlg
 功能描述  : 获取IMS域的CCWA的能力标志
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_BOOL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月24日
    作    者   : n00269697
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_CALL_GetCcwaiFlg(VOS_VOID)
{
    return MN_CALL_GetAppCfgInfo()->ucCcwaiFlg;
}

/*****************************************************************************
 函 数 名  : TAF_CALL_GetAtaReportOkAsyncFlag
 功能描述  : 获取ata是否异步上报ok标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回ata是否异步上报ok

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年6月23日
   作    者   : z00161729
   修改内容   : 新增函数
*****************************************************************************/
VOS_UINT8 TAF_CALL_GetAtaReportOkAsyncFlag(VOS_VOID)
{
    return MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg.ucAtaReportOkAsyncFlag;
}

/*****************************************************************************
 函 数 名  : TAF_CALL_SetAtaReportOkAsyncFlag
 功能描述  : 设置ata是否异步上报ok标识
 输入参数  : ucAtaReportOkAsyncFlag - ata是否异步上报ok
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年6月23日
   作    者   : z00161729
   修改内容   : 新增函数
*****************************************************************************/
VOS_VOID TAF_CALL_SetAtaReportOkAsyncFlag(
    VOS_UINT8                           ucAtaReportOkAsyncFlag
)
{
    MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg.ucAtaReportOkAsyncFlag
                           = ucAtaReportOkAsyncFlag;
    return;
}



/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-3, begin */
/*****************************************************************************
 函 数 名  : MN_CALL_GetCallRedialSupportFlg
 功能描述  : 获取是否支持呼叫重建功能标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 支持呼叫重建功能
             VOS_FALSE - 不支持呼叫重建功能
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年10月29日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2014年4月2日
   作    者   : y00245242
   修改内容   : 为eCall feature增加
*****************************************************************************/
VOS_UINT32 MN_CALL_GetCallRedialSupportFlg(VOS_VOID)
{
    return (MN_CALL_GetCallRedialCfg()->ucCallRedialSupportFlg);
}

/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-3, end */
#if (FEATURE_ON == FEATURE_ECALL)
/*****************************************************************************
 函 数 名  : TAF_CALL_GetEcallRedialCfg
 功能描述  : 获取eCall重拨配置参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回eCall呼叫重拨配置信息

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年4月2日
   作    者   : y00245242
   修改内容   : 为eCall feature增加
*****************************************************************************/
MN_CALL_REDIAL_CFG_STRU *TAF_CALL_GetEcallRedialCfg(VOS_VOID)
{
    return &(MN_CALL_GetCustomCfgInfo()->stCallRedialCfgInfo.stEcallRedialCfg);
}

/*****************************************************************************
 函 数 名  : TAF_CALL_GetEcallRedialSupportFlg
 功能描述  : 获取eCall是否支持呼叫重拨功能
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 支持呼叫重建功能
             VOS_FALSE - 不支持呼叫重建功能
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年4月2日
   作    者   : y00245242
   修改内容   : 为eCall feature增加
*****************************************************************************/
VOS_UINT8 TAF_CALL_GetEcallRedialSupportFlg(VOS_VOID)
{
    return (TAF_CALL_GetEcallRedialCfg()->ucCallRedialSupportFlg);
}

/*****************************************************************************
 函 数 名  : TAF_CALL_GetEcallMsdTransStatus
 功能描述  : 获取保存eCall MSD数据传输状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回eCall MSD数据传输状态

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年4月8日
   作    者   : y00245242
   修改内容   : 为eCall feature增加
*****************************************************************************/
VC_CALL_ECALL_TRANS_STATUS_ENUM_UINT8 TAF_CALL_GetEcallMsdTransStatus(VOS_VOID)
{
    return (MN_CALL_GetCtx()->stEcallCtx.enEcallTransStatus);
}

/*****************************************************************************
 函 数 名  : TAF_CALL_SetEcallMsdTransStatus
 功能描述  : 更新eCall MSD传输状态
 输入参数  : enEcallTransStatus -- eCall MSD传输状态
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年4月8日
   作    者   : y00245242
   修改内容   : 为eCall feature增加
*****************************************************************************/
VOS_VOID TAF_CALL_SetEcallMsdTransStatus(VC_CALL_ECALL_TRANS_STATUS_ENUM_UINT8 enEcallTransStatus)
{
    MN_CALL_GetCtx()->stEcallCtx.enEcallTransStatus = enEcallTransStatus;
}

/*****************************************************************************
 函 数 名  : TAF_CALL_GetWaitingMtEcallFlag
 功能描述  : 获取等待MT eCall标志位
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回等待MT eCall标志位

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年4月8日
   作    者   : y00245242
   修改内容   : 为eCall feature增加
*****************************************************************************/
VOS_UINT8 TAF_CALL_GetWaitingMtEcallFlag(VOS_VOID)
{
    return (MN_CALL_GetCtx()->stEcallCtx.ucWaitMtEcallFlag);
}

/*****************************************************************************
 函 数 名  : TAF_CALL_SetWaitingMtEcallFlag
 功能描述  : 更新等待MT eCall flag标志
 输入参数  : ucWaitMtEcallFlag -- 等待mt eCall标志位
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年4月8日
   作    者   : y00245242
   修改内容   : 为eCall feature增加
*****************************************************************************/
VOS_VOID TAF_CALL_SetWaitingMtEcallFlag(VOS_UINT8 ucWaitMtEcallFlag)
{
    MN_CALL_GetCtx()->stEcallCtx.ucWaitMtEcallFlag = ucWaitMtEcallFlag;
}

/*****************************************************************************
 函 数 名  : TAF_CALL_SetInternalHangUpFlag
 功能描述  : 更新内部挂机标志
 输入参数  : ucInternalHangUpFlag -- 内部挂机标记
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年4月8日
   作    者   : y00245242
   修改内容   : 为eCall feature增加
*****************************************************************************/
VOS_VOID TAF_CALL_SetInternalHangUpFlag(VOS_UINT8 ucInternalHangUpFlag)
{
    MN_CALL_GetCtx()->stEcallCtx.ucInternalHangUpFlag = ucInternalHangUpFlag;
}

/*****************************************************************************
 函 数 名  : TAF_CALL_GetInternalHangUpFlag
 功能描述  : 获取内部挂机标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回内部挂机标志

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年4月8日
   作    者   : y00245242
   修改内容   : 为eCall feature增加
*****************************************************************************/
VOS_UINT8 TAF_CALL_GetInternalHangUpFlag(VOS_VOID)
{
    return (MN_CALL_GetCtx()->stEcallCtx.ucInternalHangUpFlag);
}

/*****************************************************************************
 函 数 名  : TAF_CALL_ResetEcallPeriodRemainTimerLen
 功能描述  : reset重拨时长
 输入参数  : 无

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年4月8日
   作    者   : y00245242
   修改内容   : 为eCall feature增加
*****************************************************************************/
VOS_VOID TAF_CALL_ResetEcallPeriodRemainTimerLen(VOS_VOID)
{
    MN_CALL_GetCtx()->stEcallCtx.ulEcallPeriodTimerLen = \
        TAF_CALL_GetTimerLen(TAF_CALL_TID_WAIT_ECALL_REDIAL_PERIOD);
}

/*****************************************************************************
 函 数 名  : TAF_CALL_UpdateEcallPeriodRemainTimerLen
 功能描述  : 更新eCall period剩余时长
 输入参数  : ulEcallPeriodTimerLen －－ eCall period剩余时长

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年4月8日
   作    者   : y00245242
   修改内容   : 为eCall feature增加
*****************************************************************************/
VOS_VOID TAF_CALL_UpdateEcallPeriodRemainTimerLen(VOS_UINT32 ulEcallPeriodTimerLen)
{
    MN_CALL_GetCtx()->stEcallCtx.ulEcallPeriodTimerLen = ulEcallPeriodTimerLen;
}

/*****************************************************************************
 函 数 名  : TAF_CALL_UpdateEcallPeriodRemainTimerLen
 功能描述  : 获取eCall period剩余时长
 输入参数  : 无

 输出参数  : 无
 返 回 值  : ulEcallPeriodTimerLen －－ eCall period剩余时长

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年4月8日
   作    者   : y00245242
   修改内容   : 为eCall feature增加
*****************************************************************************/
VOS_UINT32 TAF_CALL_GetEcallPeriodRemainTimerLen(VOS_VOID)
{
    return (MN_CALL_GetCtx()->stEcallCtx.ulEcallPeriodTimerLen);
}
#endif

/*lint -save -e958 */
/*****************************************************************************
 函 数 名  : TAF_CALL_GetRedialSupportFlg
 功能描述  : 获取呼叫重拨支持标志
 输入参数  : ucCallId -- 呼叫标识
 输出参数  : 无
 返 回 值  : 返回呼叫重拨标志
             VOS_TURE  - 支持重拨
             VOS_FALSE - 不支持重拨

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年4月8日
   作    者   : y00245242
   修改内容   : 为eCall feature增加
*****************************************************************************/
VOS_UINT32 TAF_CALL_GetRedialSupportFlg(VOS_UINT8 ucCallId)
{
    VOS_UINT32                          ulRedialSupportFlg;

#if (FEATURE_ON == FEATURE_ECALL)
    if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(ucCallId))
    {
        ulRedialSupportFlg = (VOS_UINT32)TAF_CALL_GetEcallRedialSupportFlg();
    }
    else
#endif
    {
        ulRedialSupportFlg = (VOS_UINT32)MN_CALL_GetCallRedialSupportFlg();
    }

    return ulRedialSupportFlg;
}
/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-3, end */
/*lint -restore */

/*****************************************************************************
 函 数 名  : MN_CALL_GetBufferedMsg
 功能描述  : 获取当前CALL缓存的setup消息或rel消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CALL中保存的setup消息或rel消息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年10月29日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
MN_CALL_MSG_BUFF_STRU*  MN_CALL_GetBufferedMsg( VOS_VOID )
{
    return &(MN_CALL_GetCtx()->stMnCallBufferedMsg);
}

/*****************************************************************************
 函 数 名  : MN_CALL_ClearBufferedMsg
 功能描述  : 清空缓存的消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年10月29日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_CALL_ClearBufferedMsg(VOS_VOID)
{
    MN_CALL_MSG_BUFF_STRU              *pstMsgBuff = VOS_NULL_PTR;

    pstMsgBuff = MN_CALL_GetBufferedMsg();

    PS_MEM_SET(pstMsgBuff, 0x0, sizeof(MN_CALL_MSG_BUFF_STRU));
    return;
}

#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 函 数 名  : TAF_CALL_SetSrvccState
 功能描述  : 设置SRVCC状态

 输入参数  : enSrvccState -- SRVCC状态

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月23日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_CALL_SetSrvccState(MN_CALL_SRVCC_STATE_ENUM_UINT8 enSrvccState)
{
    MN_CALL_GetCtx()->enSrvccState = enSrvccState;
}

/*****************************************************************************
 函 数 名  : TAF_CALL_GetSrvccState
 功能描述  : 获取SRVCC状态

 输入参数  : enSrvccState -- SRVCC状态

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月23日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
MN_CALL_SRVCC_STATE_ENUM_UINT8 TAF_CALL_GetSrvccState(VOS_VOID)
{
    return (MN_CALL_GetCtx()->enSrvccState);
}
#endif

/*****************************************************************************
 函 数 名  : MN_CALL_InitCtx
 功能描述  : 初始化全局变量
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年10月29日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2013年12月23日
   作    者   : y00245242
   修改内容   : 增加SRVCC缓存处理
*****************************************************************************/
VOS_VOID MN_CALL_InitCtx(VOS_VOID)
{
    PS_MEM_SET(MN_CALL_GetCtx(), 0x0, sizeof(g_stMnCallCtx));

    #if (FEATURE_ON == FEATURE_IMS)
    TAF_CALL_SetSrvccState(MN_CALL_SRVCC_STATE_BUTT);

    TAF_CALL_SetCcwaiFlg(VOS_TRUE);
    TAF_CALL_SetCcwaCtrlMode(TAF_CALL_CCWA_CTRL_BY_3GPP);
#endif

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-16, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    TAF_CALL_SetEcallMsdTransStatus(VC_CALL_ECALL_TRANS_STATUS_BUTT);
#endif
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-16, end */
}



/* Modified by z00234330 for PCLINT清理, 2014-07-03, begin */
/*****************************************************************************
 函 数 名  : TAF_CALL_SetCallStatusControl
 功能描述  : 设置语音呼叫支持状态

 输入参数  : ucCallStatus -- 呼叫支持状态

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月03日
   作    者   : z00234330
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_CALL_SetCallStatusControl(
    VOS_UINT8                           ucCallStatus
)
{
    MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg.ucTafCallStatusControl = ucCallStatus;
}

/*****************************************************************************
 函 数 名  : TAF_CALL_GetCallStatusControl
 功能描述  : 获取语音呼叫是否支持状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月3日
    作    者   : z00234330
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_CALL_GetCallStatusControl( VOS_VOID  )
{
    return MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg.ucTafCallStatusControl;
}

/*****************************************************************************
 函 数 名  : TAF_CALL_SetMultiSimCallStatusControl
 功能描述  : 设置多卡呼叫支持状态

 输入参数  : ucMultiSimCallStatus -- 多卡呼叫支持状态

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月03日
   作    者   : z00234330
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_CALL_SetMultiSimCallStatusControl(
    VOS_UINT8                           ucMultiSimCallStatus
)
{
    MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg.ucTafMultiSimCallStatusControl = ucMultiSimCallStatus;
}

/*****************************************************************************
 函 数 名  : TAF_CALL_GetMultiSimCallStatusControl
 功能描述  : 获取多卡语音呼叫是否支持状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月3日
    作    者   : z00234330
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_CALL_GetMultiSimCallStatusControl( VOS_VOID  )
{
    return MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg.ucTafMultiSimCallStatusControl;
}


/*****************************************************************************
 函 数 名  : TAF_CALL_SetVpCfgState
 功能描述  : 设置可视电话呼叫支持状态

 输入参数  : enVpStateStatus -- 可视电话支持状态

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年07月03日
   作    者   : z00234330
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_CALL_SetVpCfgState(
    MN_CALL_VP_NV_CFG_STATE_ENUM_U8     enVpStateStatus
)
{
    MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg.enVpNvCfgState = enVpStateStatus;
}

/*****************************************************************************
 函 数 名  : TAF_CALL_GetVpCfgState
 功能描述  : 获取可视电话是否支持状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月3日
    作    者   : z00234330
    修改内容   : 新生成函数

*****************************************************************************/
MN_CALL_VP_NV_CFG_STATE_ENUM_U8 TAF_CALL_GetVpCfgState( VOS_VOID  )
{
    return MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg.enVpNvCfgState;
}


/* Modified by z00234330 for PCLINT清理, 2014-07-03, end */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



