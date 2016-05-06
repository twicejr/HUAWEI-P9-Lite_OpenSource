/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMsccSndRrm.c
  版 本 号   : 初稿
  作    者   : f00279542
  生成日期   : 2015年07月13日
  功能描述   : MSCC发送rrm消息处理
  函数列表   :
  修改历史   :
  1.日    期   : 2015年07月13日
    作    者   : f00279542
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "NasMntn.h"
#include "NasMsccSndRrm.h"
#include "NasComm.h"
#include "NasMsccCtx.h"
#include "NasMmlCtx.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_NAS_MSCC_SND_RRM_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/


#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_DSDS))

/*****************************************************************************
 函 数 名  : NAS_MSCC_SndRrmRatCombModeInd
 功能描述  : 向RRM发送ID_PS_RRM_RAT_COMBINED_MODE_IND消息
 输入参数  : enRatChangeType          : 接入模式变化的类型

 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月11日
    作    者   : f00279542
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MSCC_SndRrmRatCombModeInd(VOS_VOID)
{
    PS_RRM_RAT_COMBINED_MODE_IND_STRU  *pstMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucIsCLmode;

    pstMsg = (PS_RRM_RAT_COMBINED_MODE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                  UEPS_PID_MSCC,
                                                  sizeof(PS_RRM_RAT_COMBINED_MODE_IND_STRU));
    /* 内存申请失败 */
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMA, "NAS_MSCC_SndRrmRatCombModeInd:ERROR: Memory Alloc Error for pMsg");

        /* 返回失败 */
        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                 sizeof(PS_RRM_RAT_COMBINED_MODE_IND_STRU) - VOS_MSG_HEAD_LENGTH );

    pstMsg->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid         = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid       = UEPS_PID_RRM;
    pstMsg->stMsgHeader.ulMsgName           = ID_PS_RRM_RAT_COMBINED_MODE_IND;
    pstMsg->enModemId                       = VOS_GetModemIDFromPid(UEPS_PID_MSCC);

    ucIsCLmode = NAS_MSCC_IsCLCombinedModeWithRatPrio(NAS_MSCC_GetRatPrioList());
    if (VOS_TRUE == ucIsCLmode)
    {
        pstMsg->enRatCombMode               = PS_RRM_RAT_COMBINED_MODE_CL;
    }
    else
    {
        pstMsg->enRatCombMode               = PS_RRM_RAT_COMBINED_MODE_GUL;
    }

    /*发送消息*/
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



