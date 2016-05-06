/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXsdSndInternalMsg.c
  版 本 号   : 初稿
  作    者   : h00246512
  生成日期   : 2014年7月5日
  最近修改   :
  功能描述   : XSD发送给XSD的消息处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年7月5日
    作    者   : h00246512
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "CnasXsdSndInternalMsg.h"
#include  "CnasMain.h"
#include "Nas_Mem.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XSD_SND_INTERNAL_MSG_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 -e429 -e830 */
/*****************************************************************************
 函 数 名  : CNAS_XSD_SndSwitchOnRlst
 功能描述  : 收到CAS开机后的确认后发送消息给XSD指示开机结果
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月8日
    作    者   : h00246512
    修改内容   : 新生成函数
  2.日    期   : 2014年10月15日
    作    者   : c00299063
    修改内容   : 发送XSD内部消息

*****************************************************************************/
VOS_VOID CNAS_XSD_SndSwitchOnRlst(
    VOS_UINT32                          ulResult
)
{
    CNAS_XSD_XSD_SWITCH_ON_RSLT_CNF_STRU                   *pstMsg = VOS_NULL_PTR;


    pstMsg  = (CNAS_XSD_XSD_SWITCH_ON_RSLT_CNF_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                            sizeof(CNAS_XSD_XSD_SWITCH_ON_RSLT_CNF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* 填充消息 */

    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_XSD;
    pstMsg->enMsgId                     = ID_CNAS_XSD_XSD_SWITCH_ON_RSLT_CNF;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(CNAS_XSD_XSD_SWITCH_ON_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enRslt                      = ulResult;

    CNAS_XSD_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);

}


/*****************************************************************************
 函 数 名  : CNAS_XSD_SndPowerOffRslt
 功能描述  : 发送关机状态机完成结果消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK: 函数处理消息成功
             VOS_ERR: 函数申请消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月8日
    作    者   : h00246512
    修改内容   : 新生成函数
  2.日    期   : 2014年10月15日
    作    者   : c00299063
    修改内容   : 发送XSD内部消息
  3. Date      : 2015-04-11
     Author    : a00295761
     Content   : Added argument to receive internal message ID. The function can accept two arguments:
                 ID_CNAS_XSD_XSD_POWER_OFF_RSLT_CNF and ID_CNAS_XSD_XSD_POWER_SAVE_RSLT_CNF

*****************************************************************************/
VOS_VOID CNAS_XSD_SndPowerOffRslt(
    CNAS_XSD_POWEROFF_RSLT_ENUM_UINT32                      enRslt,
    CNAS_XSD_POWEROFF_REASON_ENUM_UINT32                    enPowerOffReason
)
{
    CNAS_XSD_XSD_POWER_OFF_RSLT_CNF_STRU                   *pstMsg = VOS_NULL_PTR;


    pstMsg  = (CNAS_XSD_XSD_POWER_OFF_RSLT_CNF_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                            sizeof(CNAS_XSD_XSD_POWER_OFF_RSLT_CNF_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* 填充消息 */

    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_XSD;
    pstMsg->enMsgId                     = ID_CNAS_XSD_XSD_POWER_OFF_RSLT_CNF;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(CNAS_XSD_XSD_POWER_OFF_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enPowerOffReason            = enPowerOffReason;
    pstMsg->enRslt                      = enRslt;

    /* 发送内部消息 */
    CNAS_XSD_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_SndInternalSysAcqReq
 功能描述  : 发送ID_CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ消息
 输入参数  : CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32  enSysAcqScene
             VOS_UINT32                          ulFreqNum
             CNAS_PRL_FREQENCY_CHANNEL_STRU         *pstFreq
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月7日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2014年10月15日
    作    者   : c00299063
    修改内容   : 发送XSD内部消息

*****************************************************************************/
VOS_VOID CNAS_XSD_SndInternalSysAcqReq(
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32  enSysAcqScene,
    VOS_UINT32                          ulFreqNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq
)
{
    CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ_STRU                  *pstMsg = VOS_NULL_PTR;


    /* 检查内部消息队列，是否有缓存队列已满 */
    pstMsg  = (CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                            sizeof(CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* 填充消息 */

    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_XSD;
    pstMsg->enMsgId                     = ID_CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enSysAcqScene               = enSysAcqScene;
    pstMsg->ulFreqNum                   = ulFreqNum;

    NAS_MEM_SET_S(pstMsg->astFreq, sizeof(pstMsg->astFreq), 0, sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * CNAS_XSD_INTERNAL_SYSTEM_ACQ_REQ_CHAN_MAX_NUM);

    if ((0 != ulFreqNum)
     && (ulFreqNum <= CNAS_XSD_INTERNAL_SYSTEM_ACQ_REQ_CHAN_MAX_NUM))
    {
        NAS_MEM_CPY_S(pstMsg->astFreq, sizeof(pstMsg->astFreq), pstFreq, sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * ulFreqNum);
    }

    /* 发送内部消息 */
    CNAS_XSD_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_SndSysAcqRslt
 功能描述  : 发送SYSTEM ACQUIRE状态机完成结果消息
 输入参数  : CNAS_XSD_SYSTEM_ACQUIRED_RESULT_ENUM_UINT32             enResult
             VOS_UINT8                                               ucImmediateSysAcq
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月31日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2014年10月15日
    作    者   : c00299063
    修改内容   : 发送XSD内部消息
  3.日    期   : 2014年12月2日
    作    者   : w00176964
    修改内容   : CDMA 1X Iteration 5 Modfied

*****************************************************************************/
VOS_VOID CNAS_XSD_SndSysAcqRslt(
    CNAS_XSD_SYSTEM_ACQUIRED_RESULT_ENUM_UINT32             enResult,
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32                      enCurAcqScene,
    VOS_UINT8                                               ucImmediateSysAcq
)
{
    CNAS_XSD_XSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU             *pstMsg = VOS_NULL_PTR;

    pstMsg  = (CNAS_XSD_XSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                            sizeof(CNAS_XSD_XSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* 填充消息 */

    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_XSD;
    pstMsg->enMsgId                     = ID_CNAS_XSD_XSD_SYSTEM_ACQUIRED_RSLT_CNF;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(CNAS_XSD_XSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enRslt                      = enResult;
    pstMsg->ucImmediateSysAcq           = ucImmediateSysAcq;
    pstMsg->enCurAcqScene               = enCurAcqScene;


    /* 发送内部消息 */
    CNAS_XSD_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);
}




VOS_VOID CNAS_XSD_SndInternalRedirInd(
    CNAS_XSD_REDIRECTION_INFO_STRU                          *pstRedirectionInfo
)
{
    CNAS_XSD_XSD_REDIRECTION_IND_STRU  *pstMsg = VOS_NULL_PTR;

    pstMsg  = (CNAS_XSD_XSD_REDIRECTION_IND_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                            sizeof(CNAS_XSD_XSD_REDIRECTION_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_XSD;
    pstMsg->enMsgId                     = ID_CNAS_XSD_XSD_REDIRECTION_IND;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(CNAS_XSD_XSD_REDIRECTION_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stRedirectionInfo           = *pstRedirectionInfo;

    /* 发送内部消息 */
    CNAS_XSD_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);
}




VOS_VOID CNAS_XSD_SndRedirRslt(
    CNAS_XSD_REDIRECTION_RESULT_ENUM_UINT32                 enResult
)
{
    CNAS_XSD_XSD_REDIRECTION_RSLT_CNF_STRU                 *pstMsg = VOS_NULL_PTR;

    pstMsg  = (CNAS_XSD_XSD_REDIRECTION_RSLT_CNF_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                            sizeof(CNAS_XSD_XSD_REDIRECTION_RSLT_CNF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* 填充消息 */

    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_XSD;
    pstMsg->enMsgId                     = ID_CNAS_XSD_XSD_REDIRECTION_RSLT_CNF;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(CNAS_XSD_XSD_REDIRECTION_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enRslt                      = enResult;

    /* 发送内部消息 */
    CNAS_XSD_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);
}




/*lint -restore*/

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
