/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafCbaProcMma.c
  版 本 号   : 初稿
  作    者   : l00171473
  生成日期   : 2012年3月21日
  最近修改   :
  功能描述   : 处理与MMA相关的消息
  函数列表   :
  修改历史   :
  1.日    期   : 2012年3月21日
    作    者   : l00171473
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "TafCbaProcMma.h"
#include  "TafCbaProcUsim.h"
#include  "MnComm.h"
#include  "MnMsgTimerProc.h"
#include  "TafCbaMntn.h"

#include "TafMmaInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_CBA_PROC_MMA_C

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/



/*****************************************************************************
 函 数 名  : TAF_CBA_ProcMmaMsg
 功能描述  : 处理MMA模块发送的消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_VOID TAF_CBA_ProcMmaMsg(
    struct MsgCB                       *pstMsg
)
{
    MSG_HEADER_STRU                    *pstMsgHeader;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    switch (pstMsgHeader->ulMsgName)
    {
        case MN_USIM_STATUS_IND:
            TAF_CBA_RcvMmaUsimStatusInd(pstMsg);
            break;

        default:
            break;
    }
}

/*****************************************************************************
 函 数 名  : TAF_CBA_RcvMmaUsimStatusInd
 功能描述  : 处理MMA发送的USIM卡在位状态信息, 如果卡在位则开始读取CBS相关的
             USIM卡文件
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR
  2.日    期   : 2012年3月28日
    作    者   : w00176964
    修改内容   : 修改读取文件逻辑
  3.日    期   : 2012年12月04日
    作    者   : l00171473
    修改内容   : 开机时上报CBS相关NV的可维可测信息
  4.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级
  5.日    期   : 2013年8月12日
    作    者   : f62575
    修改内容   : DTS2013081900835，支持先更新USIM配置，后更新NV配置
*****************************************************************************/
VOS_VOID TAF_CBA_RcvMmaUsimStatusInd(
    struct MsgCB                       *pstMsg
)
{
    MNPH_USIM_STATUS_IND_STRU          *pstUsimStatus;

    pstUsimStatus = (MNPH_USIM_STATUS_IND_STRU *)pstMsg;

    if (MNPH_USIM_STATUS_AVILABLE != pstUsimStatus->enUsimStatus)
    {
        /* 初始化CBA模块的USIM相关的全局变量 */
        TAF_CBA_InitSimInfo();
        /* 追加NV中配置到CBS激活消息列表 */
        TAF_CBA_AppendNvUserAcceptMsgIdList();
        return;
    }

    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    /* 读取CBS相关的USIM卡文件. 文件读取顺序: CBMI 文件; CBMIR 文件 CBMID */
	/* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, begin */
    TAF_CBA_ReadUsimFile(USIMM_USIM_EFCBMI_ID, NAS_USIM_SVR_CBMI);

    TAF_CBA_ReadUsimFile(USIMM_USIM_EFCBMIR_ID, NAS_USIM_SVR_CBMIR);

    TAF_CBA_ReadUsimFile(USIMM_USIM_EFCBMID_ID, NAS_USIM_SVR_DATA_DL_SMSCB);

    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, end */

    /* 追加NV中配置到CBS激活消息列表 */
    TAF_CBA_AppendNvUserAcceptMsgIdList();

    /* 应用USIM文件信息到本地和通知底层配置更新 */
    TAF_CBA_ApplyUsimInfo();
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

    /* 勾NV相关的可维可测信息  */
    TAF_CBA_SndOmNvimInfo();

}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
