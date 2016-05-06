/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafCbaProcMmc.c
  版 本 号   : 初稿
  作    者   : l00171473
  生成日期   : 2012年3月21日
  最近修改   :
  功能描述   : 处理MMC和CBA相关的消息
  函数列表   :
  修改历史   :
  1.日    期   : 2012年3月21日
    作    者   : l00171473
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "TafCbaProcMmc.h"
#include  "TafCbaProcAs.h"
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
/* 删除ExtAppMmcInterface.h*/
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */
#include  "TafMmcInterface.h"
#include  "TafCbaComFunc.h"
#include  "MnComm.h"
#include  "TafLog.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_CBA_PROC_MMC_C

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : TAF_CBA_RcvMmcNetModeInd
 功能描述  : 收到MMC通知AS已准备好，并通知了当前模式，CBS模块判断CBS是否激活,
             激活则下发相关列表到接入层,否则不进行任何操作
 输入参数  : ucCurrNet  - 当前的接入模式
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月7日
    作    者   : zhoujun /z40661
    修改内容   : 新生成函数
  2.日    期   : 2012年3月2日
    作    者   : l00171473
    修改内容   : for V7R1C50 CSFB&PPAC&ETWS&ISR
  3.日    期   : 2012年3月28日
    作    者   : w00176964
    修改内容   : USIM文件读取逻辑修改
  4.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级
*****************************************************************************/
VOS_VOID TAF_CBA_RcvMmcNetModeInd(
    VOS_UINT8                           ucCurrNet
)
{
    TAF_CBA_NET_RAT_TYPE_ENUM_UINT8     enNetType;

    /* 接入技术进行转换 */
    TAF_CBA_ConvertMnNetModeToCbaFormat(ucCurrNet, &enNetType);

    /* 如果模式无效,直接返回，不更改*/
    if ( TAF_CBA_NET_RAT_TYPE_BUTT == enNetType )
    {
        TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_CBA_RcvMmcNetModeInd:INVALID Mode ");
        return;
    }

    /* 如果模式未发生改变,则不需要通知AS */
    if ( enNetType == TAF_CBA_GetNetRatType() )
    {
        TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_CBA_RcvMmcNetModeInd:Same Mode ");
        return;
    }

    /* 记录新的接入模式 */
    TAF_CBA_SetNetRatType(enNetType);

    /* 当前宏开关未打开或CBS未激活,则直接返回  */
    if ( VOS_FALSE == TAF_CBA_IsNeedActAsCbs())
    {
        TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_CBA_RcvMmcNetModeInd:CBS Disable ");
        return;
    }

    /* Deleted by f62575 for V9R1 STK升级, 2013-6-26, begin */
    /* 查询是否从USIM中获取到CBS ID相关内容,如果当前未获取则不进行任何处理直接返回
        等待USIM初始化完成后,在继续下发相关消息进行处理 */
    /* Deleted by f62575 for V9R1 STK升级, 2013-6-26, end */

    /* 激活列表不为空时激活AS的CBS功能 */
    if (VOS_FALSE == TAF_CBA_IsCbsActiveListEmpty())
    {
        TAF_CBA_SndAsActiveCbsReq(TAF_CBS_CFG_ACTIVE);
    }
}

/*****************************************************************************
 函 数 名  : TAF_CBA_ProcMmcMsg
 功能描述  : 处理来自MMC的消息
 输入参数  : pstMsg: 来自MMC模块的VOS消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CBA_ProcMmcMsg(
    struct MsgCB                       *pstMsg
)
{
    TAFMMC_CBS_CURR_NET_MODE_IND_STRU  *pstMsgInd;

    switch (((MSG_HEADER_STRU *)pstMsg)->ulMsgName)
    {
        case TAFMMC_CBS_NO_NETWORK_IND:
            TAF_CBA_SetNetRatType(TAF_CBA_NET_RAT_TYPE_BUTT);
            break;

        case TAFMMC_CBS_CURR_NET_MODE_IND:
            pstMsgInd = (TAFMMC_CBS_CURR_NET_MODE_IND_STRU *)pstMsg;
            TAF_CBA_RcvMmcNetModeInd(pstMsgInd->ucCurNetWork);
            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_CBA_ProcMmcMsg:Rcv Invalid Msg Type");
            break;
    }
}



#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
