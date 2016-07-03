

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "TafCbaProcMmc.h"
#include  "TafCbaProcAs.h"
/* 删除ExtAppMmcInterface.h*/
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

    /* 查询是否从USIM中获取到CBS ID相关内容,如果当前未获取则不进行任何处理直接返回
        等待USIM初始化完成后,在继续下发相关消息进行处理 */

    /* 激活列表不为空时激活AS的CBS功能 */
    if (VOS_FALSE == TAF_CBA_IsCbsActiveListEmpty())
    {
        TAF_CBA_SndAsActiveCbsReq(TAF_CBS_CFG_ACTIVE);
    }
}


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
