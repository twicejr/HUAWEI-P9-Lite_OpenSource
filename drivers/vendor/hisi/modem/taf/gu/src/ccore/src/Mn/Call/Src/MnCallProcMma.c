/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnCallProcMma.c
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年04月26日
  最近修改   :
  功能描述   : 处理来自MMA模块的消息
  函数列表   :

  修改历史   :
  1.日    期   : 2014年04月26日
    作    者   : y00245242
    修改内容   : 创建文件

******************************************************************************/


/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "MnCallProcMma.h"
#include "MnCallMnccProc.h"
#include "MnCall.h"

#include "TafSdcLib.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#define    THIS_FILE_ID                 PS_FILE_ID_MN_CALL_PROC_MMA_C

/*****************************************************************************
   2 变量定义
*****************************************************************************/


/*****************************************************************************
   3 函数实现
*****************************************************************************/
/*lint -save -e958 */
/*****************************************************************************
 函 数 名  : TAF_CALL_ClearCallInfo
 功能描述  : 清除呼叫信息

 输入参数  : pstMsg   - 消息地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月20日
    作    者   : w00242748
    修改内容   : 新增函数
*****************************************************************************/
VOS_VOID TAF_CALL_ClearCallInfo(VOS_VOID)
{
    /*如果声码器打开则需关闭声码器*/
    if (VOS_TRUE == MN_CALL_GetChannelOpenFlg())
    {
        MN_CALL_SetChannelOpenFlg(VOS_FALSE);
        /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-18, begin */
        /* 发送消息通知VC关闭语音通道 */
        MN_CALL_SendVcMsg(CALL_VC_CHANNEL_CLOSE);
        /* 发送消息通知AT语音通道状态 */
        MN_CALL_ReportChannelEvent(MN_CALL_EVT_CHANNEL_CLOSE);
        /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-18, end */
    }

    MN_CALL_Init(MN_CALL_POWER_STATE_OFF);
}
/*****************************************************************************
 函 数 名  : TAF_CALL_RcvMmaPowerOffInd
 功能描述  : 处理来自MMA的关机指示消息

 输入参数  : pstMsg   - 消息地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年04月26日
    作    者   : y00245242
    修改内容   : 为eCall feature增加
*****************************************************************************/
VOS_VOID TAF_CALL_RcvMmaPowerOffInd(
    TAF_MMA_POWER_OFF_IND_STRU         *pstMsg
)
{
    TAF_CALL_ClearCallInfo();
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : TAF_CALL_RcvMmaPowerOffInd
 功能描述  : 处理来自MMA的关机指示消息

 输入参数  : pstMsg   - 消息地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年04月26日
    作    者   : y00245242
    修改内容   : 为eCall feature增加
*****************************************************************************/
VOS_VOID TAF_CALL_RcvMmaSyscfgInfoInd(
    MMA_TAF_SYS_CFG_INFO_IND_STRU       *pstMsg
)
{
    VOS_UINT32                          ulIsSupportGsm;

    ulIsSupportGsm = TAF_SDC_IsSpecRatInRatList(TAF_MMA_RAT_GSM, &(pstMsg->stNewRatOrder));

    if ( (VOS_TRUE == TAF_SDC_IsSpecRatInRatList(TAF_MMA_RAT_WCDMA, &(pstMsg->stNewRatOrder)))
      || (VOS_TRUE == ulIsSupportGsm) )
    {
        return;
    }

    TAF_CALL_ClearCallInfo();
}
#endif

/*lint -restore */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



