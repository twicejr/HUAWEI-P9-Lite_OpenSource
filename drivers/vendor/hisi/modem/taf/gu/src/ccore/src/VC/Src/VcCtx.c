/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : VcCtx.c
  版 本 号   : 初稿
  作    者   : s62952
  生成日期   : 2012年03月03日
  最近修改   :
  功能描述   : VC模块上下文处理文件
  函数列表   :

  修改历史   :
   1. 日    期   : 2012年03月03日
      作    者   : s62952
      修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "VcCtx.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e(767)*/
#define THIS_FILE_ID                    PS_FILE_ID_VC_CTX_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* Added by j00174725 for V3R3C60_eCall项目, 2014-3-29, begin */
APP_VC_STATE_MGMT_STRU                  g_stVcStateMgmt;
/* Added by j00174725 for V3R3C60_eCall项目, 2014-3-29, end */

#if 0
/* VC CTX,用于保存VC上下文 */
APP_VC_STATE_MGMT_STRU                  g_stAppVcCtx;
#endif


/*****************************************************************************
   3 函数实现
*****************************************************************************/
#if 0
/*****************************************************************************
 函 数 名  : APP_VC_GetCtx
 功能描述  : 获取当前VC的CTX
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前VC的CTX
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月3日
   作    者   : s62952
   修改内容   : 新生成函数

*****************************************************************************/
APP_VC_STATE_MGMT_STRU*  APP_VC_GetCtx( VOS_VOID )
{
    return &(g_stAppVcCtx);
}
#endif
/*****************************************************************************
 函 数 名  : APP_VC_GetVcStateMgmtAddr
 功能描述  : 获取当前VC的状态变量
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VC状态变量地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年5月13日
   作    者   : j00174725
   修改内容   : 新生成函数

*****************************************************************************/
APP_VC_STATE_MGMT_STRU*  APP_VC_GetVcStateMgmtAddr( VOS_VOID )
{
    return &(g_stVcStateMgmt);
}


/*****************************************************************************
 函 数 名  : APP_VC_GetCustomCfgInfo
 功能描述  : 获取VC中保存特性定制特性信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VC中保存特性定制特性信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月3日
   作    者   : s62952
   修改内容   : 新生成函数

 2.日    期   : 2014年08月30日
   作    者   : l00198894
   修改内容   : DTS2014082905824

*****************************************************************************/
APP_VC_MS_CFG_INFO_STRU* APP_VC_GetCustomCfgInfo( VOS_VOID )
{
    return &(APP_VC_GetVcStateMgmtAddr()->stMsCfgInfo);
}

/* Added by j00174725 for V3R3C60_eCall项目, 2014-3-29, begin */
#if (FEATURE_ON == FEATURE_ECALL)
/*****************************************************************************
 函 数 名  : APP_VC_GetEcallMsdAddr
 功能描述  : 获取VC中保存Ecall MSD数据地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VC中保存Ecall MSD数据地址
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年3月27日
   作    者   : j00174725
   修改内容   : V3R3C60_eCall项目
*****************************************************************************/
VOS_UINT8* APP_VC_GetEcallMsdAddr( VOS_VOID )
{
    return &(APP_VC_GetVcStateMgmtAddr()->stEcallCtx.aucMsdData[0]);
}

/*****************************************************************************
 函 数 名  : APP_VC_SetNewEcallCfg
 功能描述  : 设置APP下发的最新Ecall配置
 输入参数  : usMode -- 数据传送模式
             usVocConfig --数据传送时是否打开声码器
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史    :
1.日    期   : 2014年3月27日
  作    者   : j00174725
  修改内容   : V3R3C60_eCall项目
*****************************************************************************/
VOS_VOID APP_VC_SetNewEcallCfg(
    VOS_UINT16                          usMode,
    VOS_UINT16                          usVocConfig
)
{
    APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enNewEcallMode         = usMode;
    APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enNewEcallVocConfig    = usVocConfig;
}

/*****************************************************************************
 函 数 名  : APP_VC_UpdateCurrEcallCfg
 功能描述  : 更新Ecall当前配置
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史    :
1.日    期   : 2014年3月27日
  作    者   : j00174725
  修改内容   : V3R3C60_eCall项目
*****************************************************************************/
VOS_VOID APP_VC_UpdateCurrEcallCfg(VOS_VOID)
{
    APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enCurrEcallMode        = APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enNewEcallMode;
    APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enCurrEcallVocConfig   = APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enNewEcallVocConfig;
}

/*****************************************************************************
 函 数 名  : APP_VC_GetCurrEcallCfg
 功能描述  : 设置当前Ecall配置
 输入参数  : 无
 输出参数  : pusMode -- 数据传送模式
             pusVocConfig --数据传送时是否打开声码器
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史    :
1.日    期   : 2014年3月27日
  作    者   : j00174725
  修改内容   : V3R3C60_eCall项目
*****************************************************************************/
VOS_VOID APP_VC_GetCurrEcallCfg(
    VOS_UINT16                         *pusMode,
    VOS_UINT16                         *pusVocConfig
)
{
    *pusMode        = APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enCurrEcallMode;
    *pusVocConfig   = APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enCurrEcallVocConfig;
}

/*****************************************************************************
 函 数 名  : APP_VC_SetInEcallFlag
 功能描述  : 置eCall标识
 输入参数  : PS_BOOL_ENUM_UINT8 -- 配置标志
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史    :
1.日    期   : 2014年3月27日
  作    者   : j00174725
  修改内容   : V3R3C60_eCall项目
*****************************************************************************/
VOS_VOID APP_VC_SetInEcallFlag(PS_BOOL_ENUM_UINT8 enFlag)
{
    APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enInECall = enFlag;
}

/*****************************************************************************
 函 数 名  : APP_VC_GetInEcallFlag
 功能描述  : 获取eCall标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : PS_BOOL_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史    :
1.日    期   : 2014年3月27日
  作    者   : j00174725
  修改内容   : V3R3C60_eCall项目
*****************************************************************************/
PS_BOOL_ENUM_UINT8 APP_VC_GetInEcallFlag(VOS_VOID)
{
    return APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enInECall;
}

/*****************************************************************************
 函 数 名  : APP_VC_SetMsdFlag
 功能描述  : 标识下发MSD 数据标识
 输入参数  : PS_BOOL_ENUM_UINT8
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史    :
1.日    期   : 2014年3月27日
  作    者   : j00174725
  修改内容   : V3R3C60_eCall项目
*****************************************************************************/
VOS_VOID APP_VC_SetMsdFlag(PS_BOOL_ENUM_UINT8 enFlag)
{
    APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enMsdFlag = enFlag;
}

/*****************************************************************************
 函 数 名  : APP_VC_GetMsdFlag
 功能描述  : 获取下发MSD 数据标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : PS_BOOL_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史    :
1.日    期   : 2014年3月27日
  作    者   : j00174725
  修改内容   : V3R3C60_eCall项目
*****************************************************************************/
PS_BOOL_ENUM_UINT8 APP_VC_GetMsdFlag(VOS_VOID)
{
    return APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enMsdFlag;
}


/*****************************************************************************
 函 数 名  : APP_VC_SetEcallState
 功能描述  : 设置Ecall 状态
 输入参数  : APP_VC_ECALL_TRANS_STATUS_ENUM_UINT8 -- 状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史    :
1.日    期   : 2014年3月27日
  作    者   : j00174725
  修改内容   : V3R3C60_eCall项目
*****************************************************************************/
VOS_VOID APP_VC_SetEcallState(APP_VC_ECALL_TRANS_STATUS_ENUM_UINT8 enState)
{
    APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enEcallState = enState;
}

/*****************************************************************************
 函 数 名  : APP_VC_GetEcallState
 功能描述  : 获取Ecall的状态
 输入参数  : 无
 输出参数  : APP_VC_ECALL_TRANS_STATUS_ENUM_UINT8 --ecll状态
 返 回 值  : VOS_BOOL
 调用函数  :
 被调函数  :

 修改历史    :
1.日    期   : 2014年3月27日
  作    者   : j00174725
  修改内容   : V3R3C60_eCall项目
*****************************************************************************/
APP_VC_ECALL_TRANS_STATUS_ENUM_UINT8 APP_VC_GetEcallState(VOS_VOID)
{
    return APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enEcallState;
}

/*****************************************************************************
 函 数 名  : APP_VC_SetEcallDescription
 功能描述  : 设置Ecall 状态描述
 输入参数  : VOS_UINT32 -- 状态描述
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史    :
1.日    期   : 2014年3月27日
  作    者   : j00174725
  修改内容   : V3R3C60_eCall项目
*****************************************************************************/
VOS_VOID APP_VC_SetEcallDescription(VOS_UINT32 ulDesc)
{
    APP_VC_GetVcStateMgmtAddr()->stEcallCtx.ulEcallDescription = ulDesc;
}

/*****************************************************************************
 函 数 名  : APP_VC_GetEcallDescription
 功能描述  : 获取当前Ecall的状态描述
 输入参数  : 无
 输出参数  : APP_VC_ECALL_TRANS_STATUS_ENUM_UINT8 --ecll状态
 返 回 值  : VOS_BOOL
 调用函数  :
 被调函数  :

 修改历史    :
1.日    期   : 2014年3月27日
  作    者   : j00174725
  修改内容   : V3R3C60_eCall项目
*****************************************************************************/
VOS_UINT32 APP_VC_GetEcallDescription(VOS_VOID)
{
    return APP_VC_GetVcStateMgmtAddr()->stEcallCtx.ulEcallDescription;
}

/*****************************************************************************
 函 数 名  : APP_VC_SetAllowSetMsdFlag
 功能描述  : 设置是否允许设置MSD数据的标志
 输入参数  : PS_BOOL_ENUM_UINT8
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史    :
1.日    期   : 2014年3月27日
  作    者   : j00174725
  修改内容   : V3R3C60_eCall项目
*****************************************************************************/
VOS_VOID APP_VC_SetAllowSetMsdFlag(PS_BOOL_ENUM_UINT8 enFlag)
{
    APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enAllowSetMsdFlag = enFlag;
}

/*****************************************************************************
 函 数 名  : APP_VC_GetAllowSetMsdFlag
 功能描述  : 获取是否允许设置MSD数据的标志
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : PS_BOOL_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史    :
1.日    期   : 2014年3月27日
  作    者   : j00174725
  修改内容   : V3R3C60_eCall项目
*****************************************************************************/
PS_BOOL_ENUM_UINT8 APP_VC_GetAllowSetMsdFlag(VOS_VOID)
{
    return APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enAllowSetMsdFlag;
}

/*****************************************************************************
 函 数 名  : APP_VC_GetAlAckInfoAddr
 功能描述  : 获取AlAck记录地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VC_AL_ACK_REPORT_INFO_STRU*
 调用函数  :
 被调函数  :

 修改历史    :
1.日    期   : 2014年6月30日
  作    者   : j00174725
  修改内容   : V3R3C60_eCall项目
*****************************************************************************/
VC_AL_ACK_REPORT_INFO_STRU* APP_VC_GetAlAckInfoAddr(VOS_VOID)
{
    return &(APP_VC_GetVcStateMgmtAddr()->stEcallCtx.stVcAlAckReportInfo);
}


#endif
/* Added by j00174725 for V3R3C60_eCall项目, 2014-3-29, End */



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



