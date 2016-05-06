/******************************************************************************

            Copyright 2014, Huawei Technologies Co. Ltd.

 ******************************************************************************
File Name       :   NasMsccFsmCLInterSys.c
Author          :   W00176964
Version         :
Date            :   2015-11-05
Description     :   CL异系统流程状态机各状态的消息处理文件
Function list   :
History         :
    1) Date :
       Author:
       Modification:
******************************************************************************/


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "NasMsccFsmCLInterSys.h"
#include "NasMntn.h"
#include "NasMsccFsmCLInterSysTbl.h"
#include "NasMsccSndInternalMsg.h"
#include "NasMsccComFunc.h"
#include "NasMsccSndMmc.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 常量定义
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MSCC_FSM_CL_INTER_SYS_C

/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/

/*****************************************************************************
  5 变量定义
*****************************************************************************/

/*****************************************************************************
  6 函数实现
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
  Function Name   :   NAS_MSCC_RcvHsdInterSysStartInd_CLInterSys_Init
  Description     :   CL异系统的INIT状态收到HSD的异系统开始指示
  Input parameters:   VOS_UINT32                          ulEventType,
                      struct MsgCB                       *pstMsg
  Outout parameters:  VOS_VOID
  Return Value    :   VOS_TRUE----消息处理完成
                      VOS_FALSE----消息未处理完成
  Modify History:
      1)  Date    :   2015-11-05
          Author  :   w00176964
          Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvHsdInterSysStartInd_CLInterSys_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Save the entry message */
    NAS_MSCC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 子状态迁至等异系统结束指示 */
    NAS_MSCC_SetCurrFsmState(NAS_MSCC_CL_INTERSYS_STA_WAIT_INTERSYS_END_IND);

    /* C2L重选，起重选的定时器:67s */
    NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_CL_INTERSYS_END_IND, TI_NAS_MSCC_WAIT_CL_INTERSYS_END_IND_C2L_RESEL_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
  Function Name   :   NAS_MSCC_RcvMmcInterSysStartInd_CLInterSys_Init
  Description     :   CL异系统的INIT状态收到MMC的异系统开始指示
  Input parameters:   VOS_UINT32                          ulEventType,
                      struct MsgCB                       *pstMsg
  Outout parameters:  VOS_VOID
  Return Value    :   VOS_TRUE----消息处理完成
                      VOS_FALSE----消息未处理完成
  Modify History:
      1)  Date    :   2015-11-05
          Author  :   w00176964
          Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcInterSysStartInd_CLInterSys_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_INTERSYS_START_IND_STRU   *pstInterSysStartInd;

     /* Save the entry message */
    NAS_MSCC_SaveCurEntryMsg(ulEventType, pstMsg);

    pstInterSysStartInd = (MMC_MSCC_INTERSYS_START_IND_STRU *)pstMsg;

    /* 子状态迁至等异系统结束指示 */
    NAS_MSCC_SetCurrFsmState(NAS_MSCC_CL_INTERSYS_STA_WAIT_INTERSYS_END_IND);

    if (NAS_MSCC_PIF_INTERSYS_CAUSE_RESELECT == pstInterSysStartInd->enInterSysCause)
    {
        /* 起重选保护定时器:37s */
        NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_CL_INTERSYS_END_IND, TI_NAS_MSCC_WAIT_CL_INTERSYS_END_IND_L2C_RESEL_LEN);
    }
    else
    {
        /* 起重定向保护定时器:182s */
        NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_CL_INTERSYS_END_IND, TI_NAS_MSCC_WAIT_CL_INTERSYS_END_IND_L2C_REDIR_LEN);
    }

    return VOS_TRUE;
}


/*****************************************************************************
  Function Name   :   NAS_MSCC_RcvMmcPowerSaveCnf_CLInterSys_WaitMmcPowerSaveCnf
  Description     :   CL异系等mmc power save cnf状态收到mmc power save cnf
  Input parameters:   VOS_UINT32                          ulEventType,
                      struct MsgCB                       *pstMsg
  Outout parameters:  VOS_VOID
  Return Value    :   VOS_TRUE----消息处理完成
                      VOS_FALSE----消息未处理完成
  Modify History:
      1)  Date    :   2015-11-05
          Author  :   w00176964
          Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcPowerSaveCnf_CLInterSys_WaitMmcPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
     /* 停止对应的定时器 */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_MMC_POWER_SAVE_CNF);

    /* 发送内部异系统结果:打断 */
    NAS_MSCC_SndCLInterSysRsltCnf(NAS_MSCC_CL_INTERSYS_RESULT_ABORTED);

    /* 退出层二状态机 */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
  Function Name   :   NAS_MSCC_RcvHsdInterSysEndInd_CLInterSys_WaitInterSysEndInd
  Description     :   CL异系统等异系统结束的状态收到hsd的异系统结束指示
  Input parameters:   VOS_UINT32                          ulEventType,
                      struct MsgCB                       *pstMsg
  Outout parameters:  VOS_VOID
  Return Value    :   VOS_TRUE----消息处理完成
                      VOS_FALSE----消息未处理完成
  Modify History:
      1)  Date    :   2015-11-05
          Author  :   w00176964
          Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvHsdInterSysEndInd_CLInterSys_WaitInterSysEndInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_MSCC_CL_INTERSYS_RESULT_ENUM_UINT32                 enCLInterSysRslt;

    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_CL_INTERSYS_END_IND);

    /* 判断异系统结果 */
    enCLInterSysRslt = NAS_MSCC_JudgeCLInterSysRslt();

    NAS_MSCC_SndCLInterSysRsltCnf(enCLInterSysRslt);

    /* 退出层二状态机 */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
  Function Name   :   NAS_MSCC_RcvMsccAbortFsmReq_CLInterSys_WaitInterSysEndInd
  Description     :   CL异系统的INIT状态收到MMC的异系统开始指示
  Input parameters:   VOS_UINT32                          ulEventType,
                      struct MsgCB                       *pstMsg
  Outout parameters:  VOS_VOID
  Return Value    :   VOS_TRUE----消息处理完成
                      VOS_FALSE----消息未处理完成
  Modify History:
      1)  Date    :   2015-11-05
          Author  :   w00176964
          Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMsccAbortFsmReq_CLInterSys_WaitInterSysEndInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_MSG_STRU                                      *pstEntryMsg;

    pstEntryMsg = NAS_MSCC_GetCurrFsmEntryMsgAddr();

    /* 如果是L发起的异系统,收到用户操作，mscc要打断mmc的异系统流程
       如果是C发起的异系统,收到用户操作，mscc不做处理，仍等待异系统结束指示*/
    if (pstEntryMsg->ulEventType == NAS_BuildEventType(WUEPS_PID_MMC, ID_MMC_MSCC_INTERSYS_START_IND))
    {
        /* 先停止等异系统结束的定时器 */
        NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_CL_INTERSYS_END_IND);

        /* 打断L发起的异系统 */
        NAS_MSCC_SndMmcPowerSaveReq();

        NAS_MSCC_SetCurrFsmState(NAS_MSCC_CL_INTERSYS_STA_WAIT_MMC_POWER_SAVE_CNF);

        NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_MMC_POWER_SAVE_CNF, TI_NAS_MSCC_WAIT_CL_INTERSYS_MMC_POWERSAVE_CNF_LEN);
    }

    return VOS_TRUE;
}



/*****************************************************************************
  Function Name   :   NAS_MSCC_RcvMmcInterSysEndInd_CLInterSys_WaitInterSysEndInd
  Description     :   CL异系统的INIT状态收到MMC的异系统开始指示
  Input parameters:   VOS_UINT32                          ulEventType,
                      struct MsgCB                       *pstMsg
  Outout parameters:  VOS_VOID
  Return Value    :   VOS_TRUE----消息处理完成
                      VOS_FALSE----消息未处理完成
  Modify History:
      1)  Date    :   2015-11-05
          Author  :   w00176964
          Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcInterSysEndInd_CLInterSys_WaitInterSysEndInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_CL_INTERSYS_RESULT_ENUM_UINT32                 enCLInterSysRslt;

    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_CL_INTERSYS_END_IND);

    /* 判断异系统结果 */
    enCLInterSysRslt = NAS_MSCC_JudgeCLInterSysRslt();

    NAS_MSCC_SndCLInterSysRsltCnf(enCLInterSysRslt);

    /* 退出层二状态机 */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
  Function Name   :   NAS_MSCC_RcvTiWaitCLInterSysEndIndExpired_CLInterSys_WaitInterSysEndInd
  Description     :   CL异系统的INIT状态收到MMC的异系统开始指示
  Input parameters:   VOS_UINT32                          ulEventType,
                      struct MsgCB                       *pstMsg
  Outout parameters:  VOS_VOID
  Return Value    :   VOS_TRUE----消息处理完成
                      VOS_FALSE----消息未处理完成
  Modify History:
      1)  Date    :   2015-11-05
          Author  :   w00176964
          Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvTiWaitCLInterSysEndIndExpired_CLInterSys_WaitInterSysEndInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_MSG_STRU                                      *pstEntryMsg;

    pstEntryMsg = NAS_MSCC_GetCurrFsmEntryMsgAddr();

    /* Print Warning Log */
    NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvTiWaitCLInterSysEndIndExpired_CLInterSys_WaitInterSysEndInd:time expired!");

    if (pstEntryMsg->ulEventType == NAS_BuildEventType(WUEPS_PID_MMC, ID_MMC_MSCC_INTERSYS_START_IND))
    {
        /* L2C 超时复位 */
        NAS_MSCC_SoftReBoot(NAS_MSCC_REBOOT_SCENE_MSCC_WAIT_CL_INTERSYS_END_L2C_EXPIRED, UEPS_PID_MSCC);
    }
    else
    {
        /* C2L 超时复位 */
        NAS_MSCC_SoftReBoot(NAS_MSCC_REBOOT_SCENE_MSCC_WAIT_CL_INTERSYS_END_C2L_EXPIRED, UEPS_PID_MSCC);
    }

    return VOS_TRUE;
}

/*****************************************************************************
  Function Name   :   NAS_MSCC_RcvTiWaitMmcPowerSaveCnfExpired_CLInterSys_WaitMmcPowerSaveCnf
  Description     :   CL异系统等power save cnf超时
  Input parameters:   VOS_UINT32                          ulEventType,
                      struct MsgCB                       *pstMsg
  Outout parameters:  VOS_VOID
  Return Value    :   VOS_TRUE----消息处理完成
                      VOS_FALSE----消息未处理完成
  Modify History:
      1)  Date    :   2015-11-05
          Author  :   w00176964
          Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvTiWaitMmcPowerSaveCnfExpired_CLInterSys_WaitMmcPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Print Warning Log */
    NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvTiWaitMmcPowerSaveCnfExpired_CLInterSys_WaitMmcPowerSaveCnf:time expired!");

    /* Reboot */
    NAS_MSCC_SoftReBoot(NAS_MSCC_REBOOT_SCENE_MSCC_WAIT_CL_INTERSYS_MMC_POWER_SAVE_CNF_L2C_EXPIRED, UEPS_PID_MSCC);

    return VOS_TRUE;
}

/*****************************************************************************
  Function Name   :   NAS_MSCC_JudgeCLInterSysRslt
  Description     :   根据异系统发起方和当前处于激活态的接入网络判断异系统结果
  Input parameters:   None
  Outout parameters:  None
  Return Value    :   None
  Modify History:
      1)  Date    :   2015-11-09
          Author  :   y00346957
          Modify content :    Create
*****************************************************************************/
NAS_MSCC_CL_INTERSYS_RESULT_ENUM_UINT32 NAS_MSCC_JudgeCLInterSysRslt(VOS_VOID)
{
    NAS_MSCC_MSG_STRU                   *pstEntryMsg = VOS_NULL_PTR;

    pstEntryMsg = NAS_MSCC_GetCurrFsmEntryMsgAddr();

    /* 如果是L发起的异系统,如果lte处于激活态，异系统失败 */
    if (pstEntryMsg->ulEventType == NAS_BuildEventType(WUEPS_PID_MMC, ID_MMC_MSCC_INTERSYS_START_IND))
    {
        if (VOS_TRUE == NAS_MSCC_Get3gppActiveFlg())
        {
            return NAS_MSCC_CL_INTERSYS_RESULT_FAIL;
        }
        else
        {
            return NAS_MSCC_CL_INTERSYS_RESULT_SUCC;
        }
    }
    /* 如果是C发起的异系统,如果hrpd处于激活态，异系统失败 */
    else
    {
        if (VOS_TRUE == NAS_MSCC_GetHrpdActiveFlg())
        {
            return NAS_MSCC_CL_INTERSYS_RESULT_FAIL;
        }
        else
        {
            return NAS_MSCC_CL_INTERSYS_RESULT_SUCC;
        }
    }
}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



