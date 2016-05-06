/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXregSndAps.c
  版 本 号   : 初稿
  作    者   : h00246512
  生成日期   : 2014年12月31日
  最近修改   :
  功能描述   : 1x REG(Register)发给APS的消息处理
  函数列表   :

  修改历史   :
  1.日    期   : 2014年12月31日
    作    者   : h00246512
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasXregSndAps.h"
#include  "xreg_aps_pif.h"
#include  "CnasXregProcess.h"
#include  "CnasCcb.h"
#include  "CnasMntn.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XREG_SND_APS_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : CNAS_XREG_SndApsRegBeginInd
 功能描述  : 给APS模块发送ID_XREG_APS_REG_BEGIN_IND消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月31日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XREG_SndApsRegBeginInd(VOS_VOID)
{
    XREG_APS_REG_BEGIN_IND_STRU        *pstMsg;
    VOS_UINT8                          *pucContent;
    CNAS_XREG_SYS_MSG_CONTENT_STRU     *pstSysMsgCont;

    /*申请消息*/
    pstMsg  = (XREG_APS_REG_BEGIN_IND_STRU*)PS_ALLOC_MSG(UEPS_PID_XREG,
                        sizeof(XREG_APS_REG_BEGIN_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pucContent = (VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH;

    PS_MEM_SET(pucContent, 0, sizeof(XREG_APS_REG_BEGIN_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /*填写参数*/
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstMsg->enMsgId         = ID_XREG_APS_REG_BEGIN_IND;

    pstSysMsgCont = CNAS_XREG_GetSysMsgAddr();

    pstMsg->usSid           = pstSysMsgCont->stSysInfo.usSid;

    pstMsg->usNid           = pstSysMsgCont->stSysInfo.usNid;
    pstMsg->ucPzid          = pstSysMsgCont->stSysInfo.ucPacketZoneId;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /*发送消息*/
    PS_SEND_MSG(UEPS_PID_XREG, pstMsg);

    return;
}

/*lint -restore*/
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



