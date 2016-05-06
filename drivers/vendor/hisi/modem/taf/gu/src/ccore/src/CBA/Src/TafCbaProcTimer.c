/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafCbaProcTimer.c
  版 本 号   : 初稿
  作    者   : l00171473
  生成日期   : 2012年3月26日
  最近修改   :
  功能描述   : CBA模块处理TIMER相关的处理
  函数列表   :
  修改历史   :
  1.日    期   : 2012年3月26日
    作    者   : l00171473
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "TafCbaProcTimer.h"
#include  "TafCbaProcUsim.h"
#include  "TafCbaProcAs.h"
#include  "TafCbaComFunc.h"
#include  "TafLog.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_CBA_PROC_TIMER_C

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  3 函数实现
*****************************************************************************/


/*****************************************************************************
 函 数 名  : TAF_CBA_RcvTiWaitGetCbEfRspTimerExpired
 功能描述  : 初始化时读取USIM中的EFCBMI,EFCBMIR,EFCBMID文件时,定时器超时后的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2007年2月04日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2012年3月20日
    作    者   : l00171473
    修改内容   : for V7R1C50 CSFB&PPAC&ETWS&ISR
  3.日    期   : 2012年3月28日
    作    者   : w00176964
    修改内容   : for V7R1C50 CSFB&PPAC&ETWS&ISR
  4.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级

*****************************************************************************/
VOS_VOID  TAF_CBA_RcvTiWaitGetCbEfRspTimerExpired(
    VOS_UINT32                          ulParam
)
{
    TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_CBA_RcvTiWaitGetCbEfRspTimerExpired: Entered.");

    /* 清除读取文件的所有标记 */
    /* Deleted by f62575 for V9R1 STK升级, 2013-6-26, begin */
    /* TAF_CBA_ClearAllReadUsimFilesFlg */
    /* Deleted by f62575 for V9R1 STK升级, 2013-6-26, end */

}

#if ((FEATURE_ON == FEATURE_ETWS))
/*****************************************************************************
 函 数 名  : TAF_CBA_RcvTiEtwsTempEnableCbsTimerExpired
 功能描述  : 临时使能的CBS的定时器超时处理，去使能CBS功能
 输入参数  : ulParam: Timer parameter, input when the timer is started.
                      由于本定时器启动时未输入该参数，故这里不做处理
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月2日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CBA_RcvTiEtwsTempEnableCbsTimerExpired(
    VOS_UINT32                          ulParam
)
{
    TAF_CBA_NET_RAT_TYPE_ENUM_UINT8     enNetMode;
    VOS_UINT32                          ulIsActiveListEmpty;

    TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_CBA_RcvTiEtwsTempEnableCbsTimerExpired: Entered.");

    enNetMode = TAF_CBA_GetNetRatType();

    /* W模时才需要去使能CBS功能 */
    /* todo:如果G支持ETWS了这里需要修改 */
    if (TAF_CBA_NET_RAT_TYPE_WCDMA  != enNetMode)
    {
        return;
    }

    /* 定时器启动过程中用户可能设置激活列表为空了，此时就不需要向AS发DISABLE了 */
    ulIsActiveListEmpty = TAF_CBA_IsCbsActiveListEmpty();
    if ( VOS_TRUE != ulIsActiveListEmpty )
    {
        /* 向AS发CBS DISABLE消息 */
        TAF_CBA_SndAsActiveCbsReq(TAF_CBS_CFG_DEACTIVE);
    }
}

/*lint -restore */

#endif
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
