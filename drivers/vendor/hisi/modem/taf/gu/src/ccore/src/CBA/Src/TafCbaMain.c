/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafCbaMain.c
  版 本 号   : 初稿
  作    者   : l00171473
  生成日期   : 2012年3月19日
  最近修改   :
  功能描述   : CBA模块的消息入口处理
  函数列表   :
  修改历史   :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "TafCbaMain.h"
#include  "TafCbaProcAs.h"
#include  "TafCbaProcAt.h"
#include  "TafCbaProcMmc.h"
#include  "TafCbaProcMma.h"
#include  "TafCbaProcUsim.h"
#include  "MnComm.h"
#include  "TafLog.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_CBA_MAIN_C

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/



/*****************************************************************************
 函 数 名  : TAF_CBA_MsgProc
 功能描述  : CBA模块的消息处理入口
 输入参数  : pstMsg: CBA模块收到的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR
  2.日    期   : 2013年07月11日
    作    者   : f62575
    修改内容   : V9R1 STK升级项目
*****************************************************************************/
VOS_VOID TAF_CBA_MsgProc(
    struct MsgCB                       *pstMsg
)
{
    switch (pstMsg->ulSenderPid)
    {
        case UEPS_PID_GAS:
            TAF_CBA_ProcGasMsg(pstMsg);
            break;

        case WUEPS_PID_WRR:
            TAF_CBA_ProcWrrMsg(pstMsg);
            break;

        case WUEPS_PID_BMC:
            TAF_CBA_ProcBmcMsg(pstMsg);
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case PS_PID_ERRC:
            TAF_CBA_ProcLrrcMsg(pstMsg);
            break;
#endif

        case WUEPS_PID_MMC:
            TAF_CBA_ProcMmcMsg(pstMsg);
            break;

        case WUEPS_PID_AT:
            TAF_CBA_ProcAtMsg(pstMsg);
            break;

        case WUEPS_PID_MMA:
            TAF_CBA_ProcMmaMsg(pstMsg);
            break;

        /* Deleted WUEPS_PID_USIM by f62575 for V9R1 STK升级, 2013/07/11 */

        default:
            TAF_ERROR_LOG1(WUEPS_PID_TAF, "TAF_CBA_MsgProc: Unknown message sender, SenderPid, ", (VOS_INT32)pstMsg->ulSenderPid);
            break;

    }
}


#endif /* ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS)) */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
