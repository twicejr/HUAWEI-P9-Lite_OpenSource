

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



VOS_VOID  TAF_CBA_RcvTiWaitGetCbEfRspTimerExpired(
    VOS_UINT32                          ulParam
)
{
    TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_CBA_RcvTiWaitGetCbEfRspTimerExpired: Entered.");

    /* 清除读取文件的所有标记 */
    /* TAF_CBA_ClearAllReadUsimFilesFlg */

}

#if ((FEATURE_ON == FEATURE_ETWS))

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
