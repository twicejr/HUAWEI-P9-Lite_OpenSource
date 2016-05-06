/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MonitorSystem.C
  版 本 号   : 初稿
  作    者   : z00100318 g47350
  生成日期   : 2009年7月23日
  最近修改   :
  功能描述   : MonitorSystem模块
  函数列表   :
  修改历史   :
  1.日    期   : 2008年7月1日
    作    者   : g47350
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "pamom.h"
#include "spysystem.h"
#include "TafClientApi.h"
#include "TafAppMma.h"
#include "NVIM_Interface.h"
#include "sleepsleep.h"
#include "errorlog.h"
#include "apminterface.h"
#include "hpaoperatertt.h"
#include "TafDrvAgent.h"
#include "OmApi.h"
#include "TafOamInterface.h"
#include "DspInterface.h"
#include "omprivate.h"
#include "msp_diag_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人：z00100318；检视人：l46160；原因简述：打点日志文件宏ID定义*/
#define    THIS_FILE_ID        PS_FILE_ID_SPYSYSTEM_C
/*lint +e767 修改人：z00100318；检视人：l46160*/


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

HTIMER                          g_stSpyTempProtect_Timer = VOS_NULL_PTR;/*用于温度保护查询定时器*/

HTIMER                          g_stSpyFlowCtrlTimer = VOS_NULL_PTR;/*用于流控定时器*/

SPY_SYSCUR_STATUS               g_stSysCurStatus;/*用于保存当前系统状态*/

SPY_STATE_ENUM_UINT32           g_enSpyCurState;/*用于保存当前系统调节状态*/

SPY_TEMP_STATE_CTRL_STRU        g_stTempStateCtrl; /*保存当前温度保护模块的状态*/

SPY_TEMP_PROTECT_NV_STRU        g_stTempProtectNv; /*温度保护NV项的结构*/

VOS_UINT16                      g_usSpyClientId;    /*注册的clientId*/

/*Reserve SD card and Antenna status*/
VOS_UINT32                      g_ulUsbStatus   = 0;
VOS_UINT32                      g_ulAntenStatus = 0;


SPY_DOWNGRADE_PROC_FUNC         g_pfunRegDowngradeProc = VOS_NULL_PTR;  /*用于流控降速执行函数*/

SPY_DOWNGRADE_PROC_FUNC         g_pfunRegUpgradeProc = VOS_NULL_PTR;  /*用于流控升速执行函数*/

SPY_RESTORE_PROC_FUNC           g_pfunRegRestoreProc = VOS_NULL_PTR;  /*用于软关机恢复初速执行函数*/

#ifdef SPY_STATISTICS_DEBUG
/* SPY温保措施执行统计信息 */
SPY_STATISTICS_INFO_STRU        g_stSpyStatisticsInfo;

VOS_UINT32                      g_ulSpyRecordFlag = 1;
SPY_RECORD_STRU                 g_stSpyTimeRecord;
#define SPY_GetTime(ulIndex)    (g_stSpyTimeRecord.astRecord[ulIndex].ulTime)
#define SPY_GetType(ulIndex)    (g_stSpyTimeRecord.astRecord[ulIndex].acType)
#endif

extern VOS_VOID L_ExtAntenStatus(VOS_INT32 para);

/* 上报给NAS的温保状态，只有开启和关闭两个状态 */
SPY_TEMPROTECT_SWITCH_STATE_ENUM_UINT32                    g_ulSpySwitchState = SPY_TEMPROTECT_SWITCH_OFF;

/* NAS 通知 SPY 的紧急呼叫的状态 */
TAF_OAM_EMERGENCY_CALL_STATUS_ENUM_UINT8                   g_ucSpyEmergencyCallState = TAF_OAM_EMERGENCY_CALL_END;

/*****************************************************************************
  3 函数实现
*****************************************************************************/

#ifdef SPY_STATISTICS_DEBUG
/*****************************************************************************
 函 数 名  : Spy_TimeRecord
 功能描述  : 记录SPY事件
 输入参数  : None
 输出参数  : None
 返 回 值  : VOS_VOID

 作者      : s00180715
             2012-02-16
*****************************************************************************/
VOS_VOID Spy_TimeRecord(VOS_CHAR * pcString)
{
    VOS_UINT32 ulRecordPosition = 0;

    if (1 != g_ulSpyRecordFlag)
    {
        return;
    }

    g_stSpyTimeRecord.ulCount++;

    ulRecordPosition = ((g_stSpyTimeRecord.ulCount-1)%SPY_RECORD_NUM);

    SPY_GetTime(ulRecordPosition) = VOS_GetTick();

    /*lint -e534*/
    VOS_StrCpy(SPY_GetType(ulRecordPosition),pcString);
    /*lint +e534*/

    return;
}
#endif


/*****************************************************************************
 Prototype       :   Spy_AntenStatusProc
 Description     :   回调函数，根据ANTEN状态，上报处理消息
 Input           :   enModemID 卡ID
                 :   ulStatus  天线状态
 Output          :   void
 Return Value    :   void

 History         : ---
    Date         : 2009-05-7
    Author       : m00128685
    Modification : Created function
 -------------------------------------
    Date         : 2012-03-20
    Author       : s00207770
    Modification : 修改为上报处理消息
 *****************************************************************************/
VOS_VOID Spy_AntenStatusProc(MODEM_ID_ENUM_UINT16 enModemID, VOS_UINT32 ulStatus)
{
    SPY_MSG_STRU                       *pstSarMsg;

    pstSarMsg = (SPY_MSG_STRU *)VOS_AllocMsg(WUEPS_PID_SAR,
                    sizeof(SPY_MSG_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSarMsg)
    {
        return;
    }

    pstSarMsg->ulReceiverPid    = WUEPS_PID_SAR;
    pstSarMsg->ulMsgName        = SPY_SAR_ANTEN_STATUS_IND;
    pstSarMsg->lAntenStatus     = (VOS_INT32)ulStatus;
    pstSarMsg->enModemID        = enModemID;

    if (VOS_OK != VOS_SendMsg(WUEPS_PID_SAR, pstSarMsg))
    {
        return;
    }

    return;
}

/*****************************************************************************
 Prototype       :   Spy_Anten0StatusProc
 Description     :   回调函数，给DRV上报天线0状态函数
 Input           :   enModemID 卡ID
 Output          :   void
 Return Value    :   void

 History         : ---
    Date         : 2013-05-30
    Author       : d00212987
    Modification : 上报天线处理消息
 *****************************************************************************/
VOS_VOID Spy_Anten0StatusProc(VOS_VOID)
{
    VOS_UINT                            ulStatus = 0; /* 无线连接 */

    if (VOS_OK != mdrv_anten_get_lockstate(PWC_COMM_MODEM_0, &ulStatus))
    {
        SAR_ERROR_LOG("Spy_Anten0StatusProc: get anten status from drv fail.\r\n");
        return;
    }

    mdrv_anten_register_intr_cb(PWC_COMM_MODEM_0, Spy_Anten0StatusProc, (VOS_INT)ulStatus);

    Spy_AntenStatusProc(MODEM_ID_0, ulStatus);
}

#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
/*****************************************************************************
 Prototype       :   Spy_Anten1StatusProc
 Description     :   回调函数，给DRV上报天线1状态函数
 Input           :   void
 Output          :   void
 Return Value    :   void

 History         : ---
    Date         : 2013-05-30
    Author       : d00212987
    Modification : 上报天线处理消息
 *****************************************************************************/
VOS_VOID Spy_Anten1StatusProc(VOS_VOID)
{
    VOS_UINT                            ulStatus = 0; /* 无线连接 */;

    if (VOS_OK != mdrv_anten_get_lockstate(PWC_COMM_MODEM_1, &ulStatus))
    {
        SAR_ERROR_LOG("Spy_Anten1StatusProc: get anten status from drv fail.\r\n");
        return;
    }

    mdrv_anten_register_intr_cb(PWC_COMM_MODEM_1, Spy_Anten1StatusProc, (VOS_INT)ulStatus);

    Spy_AntenStatusProc(MODEM_ID_1, ulStatus);

}
#endif

/*****************************************************************************
 Prototype       :   Spy_SarSendToDsp
 Description     :   将天线状态上报给DSP
 Input           :   enModemID 卡ID
                     stSpyToDsp 发给DSP Sar 内容

 Output          :   void
 Return Value    :   void

 History         : ---
    Date         : 2012-03-20
    Author       : s00207770
    Modification : Created function
 *****************************************************************************/
VOS_VOID Spy_SarSendToDsp(MODEM_ID_ENUM_UINT16 enModemID, MN_APP_SAR_INFO_STRU *pstSpyToDsp)
{
    PHY_OAM_SAR_CTRL_REQ_STRU          *pstSarMsg;

    pstSarMsg = (PHY_OAM_SAR_CTRL_REQ_STRU*)VOS_AllocMsg(WUEPS_PID_SAR,
                        sizeof(PHY_OAM_SAR_CTRL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstSarMsg )
    {
        SAR_WARNING_LOG("Spy_SarSendToDsp: Msg Alloc Failed!");
        return;
    }

    pstSarMsg->ulMask  = pstSpyToDsp->ulSarType;
    pstSarMsg->enMsgId = ID_OAM_PHY_SAR_CTRL_REQ;

    if(MODEM_ID_0 == enModemID)
    {
        pstSarMsg->ulReceiverPid    = I0_DSP_PID_APM;
    }
    else
    {
        pstSarMsg->ulReceiverPid    = I1_DSP_PID_APM;
    }

    /* 天线状态 */
    if ( PHY_OM_SAR_MASK_ANTSTATE == (PHY_OM_SAR_MASK_ANTSTATE & pstSpyToDsp->ulSarType) )
    {
        pstSarMsg->lAntenStatus = pstSpyToDsp->lAntenStatus;
    }

    /* 功率回退等级 */
    if ( PHY_OM_SAR_MASK_REDUCTION == (PHY_OM_SAR_MASK_REDUCTION & pstSpyToDsp->ulSarType) )
    {
        pstSarMsg->ulSarReduction = pstSpyToDsp->ulSarReduction;
    }

    if (VOS_OK != VOS_SendMsg(WUEPS_PID_SAR, pstSarMsg))
    {
        SAR_ERROR_LOG("Spy_SarSendToDsp: Send Msg Failed!");
        return;
    }

    return;
}

/*****************************************************************************
 Prototype       :   Spy_SarSendToTaf
 Description     :   将天线状态上报给TAF
 Input           :   enModemID   : 卡ID
                 :   lAntenStatu : 天线状态
 Output          :   void
 Return Value    :   void

 History         : ---
    Date         : 2012-03-20
    Author       : s00207770
    Modification : Created function
*****************************************************************************/
VOS_VOID Spy_SarSendToTaf(MODEM_ID_ENUM_UINT16 enModemID, VOS_INT32  lAntenStatus)
{
    MN_APP_SAR_ANTENSTATUS_MSG_STRU *pstAntenStatusStru;

    pstAntenStatusStru = (MN_APP_SAR_ANTENSTATUS_MSG_STRU *)VOS_AllocMsg(WUEPS_PID_SAR,
                            sizeof(MN_APP_SAR_ANTENSTATUS_MSG_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstAntenStatusStru)
    {
        SAR_WARNING_LOG("Spy_SarSendToTaf: Msg Alloc Failed!");
        return;
    }

    if (MODEM_ID_0 == enModemID)
    {
        pstAntenStatusStru->ulReceiverPid   = I0_WUEPS_PID_DRV_AGENT;
    }
    else
    {
        pstAntenStatusStru->ulReceiverPid   = I1_WUEPS_PID_DRV_AGENT;
    }

    pstAntenStatusStru->ulMsgId         = SAR_ANTSTATE_IND;
    pstAntenStatusStru->lAntenStatus    = lAntenStatus;

    if (VOS_OK != VOS_SendMsg(WUEPS_PID_SAR, pstAntenStatusStru))
    {
        SAR_ERROR_LOG("Spy_SarSendToTaf: SendMsg Failed!");
        return;
    }

    return;
}

/*****************************************************************************
 Prototype       :   Spy_SendAntenStatusToLte
 Description     :   天线状态上报给LTE
 Input           :   lAntenStatus 天线状态
 Output          :   void
 Return Value    :   void

 History         : ---
    Date         : 2013-05-30
    Author       : d00212987
    Modification : 上报天线处理消息
 *****************************************************************************/
VOS_VOID Spy_SendAntenStatusToLte(MODEM_ID_ENUM_UINT16 enModemID, VOS_INT32 lAntenStatus)
{
    PLATAFORM_RAT_CAPABILITY_STRU       stPlatFormRat;
    VOS_UINT32                          i;

    if (MODEM_ID_0 == enModemID)
    {
        /* 读取天线状态，判断是否需要给 L 模发 */
        if (NV_OK != NV_ReadEx(enModemID, en_NV_Item_Platform_RAT_CAP, &stPlatFormRat,
                              sizeof(PLATAFORM_RAT_CAPABILITY_STRU)))
        {
            SAR_ERROR_LOG("Spy_SendAntenStatusToLte: read nv fail.\r\n");
            return;
        }

        for (i=0; i<stPlatFormRat.usRatNum; i++)
        {
            /* 平台支持LTE */
            if (PLATFORM_RAT_LTE == stPlatFormRat.aenRatList[i])
            {
                L_ExtAntenStatus(lAntenStatus);
            }
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : Spy_SarMsgProc
 功能描述  : 降SAR功能，天线状态变更处理接口
 输入参数  : MsgBlock *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32 VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月20日
    作    者   : s00207770
    修改内容   : 新生成函数
  2.日    期   : 2012年5月28日
    作    者   : s00207770
    修改内容   : 添加L模天线状态更新处理

*****************************************************************************/
VOS_UINT32  Spy_SarMsgProc(MsgBlock *pMsg)
{
    SPY_MSG_STRU                        *pstMsg;
    MN_APP_SAR_INFO_STRU                      stSpyToDsp;

    pstMsg = (SPY_MSG_STRU *)pMsg;

    switch(pstMsg->ulMsgName)
    {
        case SPY_SAR_ANTEN_STATUS_IND:

            if (MODEM_ID_BUTT <= pstMsg->enModemID)
            {
                SPY_ERROR1_LOG("Spy_SarMsgProc: Modem ID is: %d error!", pstMsg->enModemID);
                return VOS_ERR;
            }

            /* 给DSP发送天线状态 */
            /*lint -e534*/
            VOS_MemSet(&stSpyToDsp, 0, sizeof(MN_APP_SAR_INFO_STRU));
            /*lint +e534*/
            stSpyToDsp.lAntenStatus = pstMsg->lAntenStatus;
            stSpyToDsp.ulSarType    = PHY_OM_SAR_MASK_ANTSTATE;
            Spy_SarSendToDsp(pstMsg->enModemID,&stSpyToDsp);

            /* 给Taf发送天线状态 */
            Spy_SarSendToTaf(pstMsg->enModemID,
                             pstMsg->lAntenStatus);

            /* 给L模发送天线状态 */
            Spy_SendAntenStatusToLte(pstMsg->enModemID,
                                     pstMsg->lAntenStatus);
            break;

        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : Spy_AntenStatusInit
 功能描述  : 降SAR功能，天线状态初始化接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月20日
    作    者   : s00207770
    修改内容   : 新生成函数
  2.日    期   : 2012年5月28日
    作    者   : s00207770
    修改内容   : 添加L模天线状态更新处理

*****************************************************************************/
VOS_VOID Spy_AntenStatusInit(VOS_VOID)
{
    VOS_UINT                    ulStatus = 0; /* 无线连接 */

    if (VOS_OK == mdrv_anten_get_lockstate(PWC_COMM_MODEM_0, &ulStatus))
    {
        /* 给L模发送天线状态 (只有卡0 存在L模) */
        Spy_SendAntenStatusToLte(MODEM_ID_0, (VOS_INT32)ulStatus);
    }
    else
    {
        SAR_WARNING_LOG("Spy_AntenStatusInit: Get Anten 0 status Failed!");
    }

    mdrv_anten_register_intr_cb(PWC_COMM_MODEM_0, Spy_Anten0StatusProc, (VOS_INT)ulStatus);

#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
    if (VOS_OK != mdrv_anten_get_lockstate(PWC_COMM_MODEM_1, &ulStatus))
    {
        SAR_WARNING_LOG("Spy_AntenStatusInit: Anten 1 Get Failed!");
    }

    mdrv_anten_register_intr_cb(PWC_COMM_MODEM_1, Spy_Anten1StatusProc, (VOS_INT)ulStatus);
#endif

    return;
}

/*****************************************************************************
 函 数 名  : Spy_ReportEvent
 功能描述  : 通过调用OM提供的接口上报状态事件
 输入参数  : usEventId: 事件ID
             lSimTemp:  SIM卡温度值
 输出参数  : 无
 返 回 值  : VOS_VOID

 修改历史  : m00128685
             2009-03-25
*****************************************************************************/
VOS_VOID Spy_ReportEvent(SPY_EVENT_NAME_ENUM_UINT32 enEventId, VOS_INT lSimTemp)
{
    DIAG_EVENT_IND_STRU                 stEventInd;

    stEventInd.ulModule = DIAG_GEN_MODULE(DIAG_MODEM_0, DIAG_MODE_COMM);
    stEventInd.ulPid    = WUEPS_PID_SPY;
    stEventInd.ulEventId= enEventId;
    stEventInd.ulLength = sizeof(lSimTemp);
    stEventInd.pData    = (VOS_VOID *)(&lSimTemp);

    /*lint -e534*/
    (VOS_VOID)DIAG_EventReport(&stEventInd);
    /*lint +e534*/

    return;
}

/*****************************************************************************
 函 数 名  : Spy_RegPhoneCallback
 功能描述  : 处理NAS的回调事件上报
 输入参数  : pEvent: 事件
 输出参数  : 无
 返 回 值  : VOS_VOID

 修改历史  : m00128685
             2009-03-25
*****************************************************************************/
VOS_VOID Spy_RegPhoneCallback(TAF_PHONE_EVENT_INFO_STRU *pEvent)
{
    if(VOS_YES != pEvent->OP_OperMode)/*判断当前是否是开关机事件*/
    {
        return;
    }

    if((VOS_OK != pEvent->OP_PhoneError)
        &&(TAF_PH_MODE_LOWPOWER == pEvent->OperMode.PhMode))/*判断当前关机事件操作的结果*/
    {
        SPY_WARNING_LOG("Spy_RegPhoneCallback: TAF Return Error");

        g_enSpyCurState = SPY_STATE_NORMAL;
    }

    if((TAF_PH_MODE_FULL == pEvent->OperMode.PhMode)
        &&(SPY_STATE_PSOFF == g_enSpyCurState))/*如果当前系统是关机但是消息中是开机，表明用户手动开机*/
    {
        SPY_WARNING_LOG("Spy_RegPhoneCallback: User Open the PS when the PS State is TAF_PH_MODE_FULL");

        g_enSpyCurState = SPY_STATE_NORMAL;
    }

    return;
}

/*****************************************************************************
 函 数 名  : Spy_SendAtTempProtectMsg
 功能描述  : 给AT任务发送温保状态变化指示消息
 输入参数  : ulTempProtectEvent -- 温度保护状态变化事件
             ulTempProtectParam -- 预留以备扩展
 输出参数  : 无
 返 回 值  : VOS_OK
             VOS_ERR
 修改历史  :
*****************************************************************************/
VOS_UINT32 Spy_SendAtTempProtectMsg(VOS_UINT32 ulTempProtectEvent, VOS_UINT32 ulTempProtectParam)
{
    VOS_UINT32                       ulTempState;
    TEMP_PROTECT_EVENT_AT_IND_STRU  *pstSpyMsg;

    pstSpyMsg = (TEMP_PROTECT_EVENT_AT_IND_STRU *)VOS_AllocMsg(WUEPS_PID_SPY,
                sizeof(TEMP_PROTECT_EVENT_AT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSpyMsg)
    {
        SPY_ERROR_LOG("Spy_SendAtTempProtectMsg: alloc normal msg Return Null");

        return VOS_ERR;
    }

    pstSpyMsg->ulReceiverPid        = WUEPS_PID_AT;
    pstSpyMsg->ulMsgId              = ID_TEMPPRT_AT_EVENT_IND;
    pstSpyMsg->ulTempProtectEvent   = ulTempProtectEvent;
    pstSpyMsg->ulTempProtectParam   = ulTempProtectParam;

    if (VOS_OK != VOS_SendMsg(WUEPS_PID_SPY, pstSpyMsg))
    {
        SPY_ERROR_LOG("Spy_SendAtTempProtectMsg: send normal Return Failed");

        return VOS_ERR;
    }

    if ( SPY_STATE_NORMAL == ulTempProtectEvent )
    {
        ulTempState = SPY_TEMPROTECT_SWITCH_OFF;
    }
    else
    {
        ulTempState = SPY_TEMPROTECT_SWITCH_ON;
    }

    if ( ulTempState == g_ulSpySwitchState )
    {
        SPY_INFO_LOG("Spy_SendAtTempProtectMsg: No Action");

        return VOS_OK;
    }

    g_ulSpySwitchState = ulTempState;

    pstSpyMsg = (TEMP_PROTECT_EVENT_AT_IND_STRU *)VOS_AllocMsg(WUEPS_PID_SPY,
                sizeof(TEMP_PROTECT_EVENT_AT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSpyMsg)
    {
        SPY_ERROR_LOG("Spy_SendAtTempProtectMsg:  alloc switch msg Return Null");

        return VOS_ERR;
    }

    pstSpyMsg->ulReceiverPid        = WUEPS_PID_AT;
    pstSpyMsg->ulMsgId              = ID_TEMPPRT_STATUS_AT_EVENT_IND;
    pstSpyMsg->ulTempProtectEvent   = ulTempState;
    pstSpyMsg->ulTempProtectParam   = ulTempProtectParam;

    if (VOS_OK != VOS_SendMsg(WUEPS_PID_SPY, pstSpyMsg))
    {
        SPY_ERROR_LOG("Spy_SendAtTempProtectMsg: send switch Return Failed");

        return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : Spy_CountInit
 功能描述  : 将计数器初始化
 输入参数  : usState -- 计数器类型
 输出参数  : 无
 返 回 值  : VOS_VOID

 修改历史  : g47350
             2009-07-07
*****************************************************************************/
VOS_VOID Spy_CountInit(VOS_UINT16 usState)
{
    if (0 != (usState & TEMP_CLOSE_ITEM))
    {
        g_stTempStateCtrl.ulTempCloseCount = TEMP_CLOSE_ADC_COUNT;

        SPY_NORMAL_LOG("Spy_CountInit: Clean the Temp Close Count");
    }

    if (0 != (usState & TEMP_ALARM_ITEM))
    {
        g_stTempStateCtrl.ulTempAlarmCount = TEMP_ALARM_ADC_COUNT;

        SPY_NORMAL_LOG("Spy_CountInit: Clean the Temp Alarm Count");
    }

    if (0 != (usState & TEMP_RESUME_ITEM))
    {
        g_stTempStateCtrl.ulTempResumeCount = TEMP_RESUME_ADC_COUNT;

        SPY_NORMAL_LOG("Spy_CountInit: Clean the Temp Resume Count");
    }

    if (0 != (usState & TEMP_POWEROFF_ITEM))
    {
        g_stTempStateCtrl.ulTempPowerOffCount = TEMP_POWEROFF_ADC_COUNT;

        SPY_NORMAL_LOG("Spy_CountInit: Clean the Temp Power Off Count");
    }

    return;
}

/*****************************************************************************
 函 数 名  : Spy_TempCheckInit
 功能描述  : 温度检测模块初始化
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 成功，失败

 修改历史  : g47350
             2009-07-07
*****************************************************************************/
VOS_UINT32 Spy_TempCheckInit(VOS_VOID)
{
    g_stTempStateCtrl.enTempEnable = TEMP_CLOSE_STATE;

    /*读取热保护门限值的NV项*/
    if(NV_OK != NV_Read(en_NV_Item_USIM_TEMP_PROTECT_NEW,
                            (VOS_VOID*)&g_stTempProtectNv,
                            sizeof(SPY_TEMP_PROTECT_NV_STRU)))
    {

        SPY_ERROR_LOG("Spy_TempCheckInit: NV_Read en_NV_Item_USIM_TEMP_PROTECT!");

        return VOS_ERR;
    }

    g_stTempStateCtrl.lOldTemperature = 0;

    /*初始化温度保护控制变量*/
    g_stTempStateCtrl.enTempEnable      = g_stTempProtectNv.ulIsEnable;

    g_stTempStateCtrl.enTempState       = TEMP_NORMAL_STATE;

    g_stTempStateCtrl.ulTempCloseCount  = TEMP_CLOSE_ADC_COUNT;

    g_stTempStateCtrl.ulTempAlarmCount  = TEMP_ALARM_ADC_COUNT;

    g_stTempStateCtrl.ulTempPowerOffCount   = TEMP_POWEROFF_ADC_COUNT;

    g_stTempStateCtrl.ulTempResumeCount = TEMP_RESUME_ADC_COUNT;

    g_stTempStateCtrl.ulTempWaitTimeLen = TEMP_CLOSE_TIMER_LEN;

    g_stTempStateCtrl.ulBatteryTempAlarmCount = 0;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : Spy_TempProtectInit
 功能描述  : 任务初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 作者      : z00100318
 修改历史  : z00100318
             2009-07-10
*****************************************************************************/
VOS_UINT32 Spy_TempProtectInit(VOS_VOID)
{
    VOS_INT16                           sTemp;

    g_enSpyCurState = SPY_STATE_NORMAL;

#ifdef SPY_STATISTICS_DEBUG
    /*lint -e534*/
    VOS_MemSet(&g_stSpyStatisticsInfo, 0, sizeof(SPY_STATISTICS_INFO_STRU));
    VOS_MemSet(&g_stSpyTimeRecord, 0, sizeof(SPY_RECORD_STRU));
    /*lint +e534*/
#endif

    if(VOS_OK != Spy_TempCheckInit())
    {
        SPY_ERROR_LOG("Spy_TempProtectInit: Spy_TempCheckInit Failed!");

        return VOS_ERR;
    }

    if(TEMP_ENABLE_STATE == g_stTempStateCtrl.enTempEnable)
    {
        /*读取当前温度值*/
        if(VOS_OK !=  mdrv_hkadc_get_temp((HKADC_TEMP_PROTECT_E)(g_stTempProtectNv.ulLocation),
                                          VOS_NULL_PTR, &sTemp, HKADC_CONV_DELAY))
        {
            SPY_WARNING_LOG("Spy_TempProtectInit: The Drv Interface Return Failed!");

            return VOS_ERR;
        }

        g_stTempStateCtrl.lOldTemperature   = sTemp;

        if(VOS_OK != VOS_StartRelTimer(&g_stSpyTempProtect_Timer, WUEPS_PID_SPY,
                                    SPY_TIMER_LEN, 1, 0, VOS_RELTIMER_NOLOOP,VOS_TIMER_NO_PRECISION))
        {
            SPY_ERROR_LOG("Spy_TempProtectInit: Start The Check Timer Failed!");

            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : Spy_CheckTemp
 功能描述  : 温度检测模块
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 无动作 降速 软关机 硬关机

 修改历史  : g47350
             2009-07-07
*****************************************************************************/
VOS_INT32 Spy_CheckTemp(VOS_VOID)
{
    VOS_INT16               sTemp;
    VOS_INT                 lSimTemp = 0;

    /* 紧急呼叫期间不考虑温度保护,但是如果温保已经开始了，那么不考虑紧急呼叫 */
    if ( (SPY_STATE_NORMAL == g_enSpyCurState) && (TAF_OAM_EMERGENCY_CALL_START == g_ucSpyEmergencyCallState) )
    {
        return SPY_VOTE_NOMAL;
    }

    /*温度监控没有启动 或者 当前处于FT模式下*/
    if ((TEMP_CLOSE_STATE == g_stTempStateCtrl.enTempEnable)
        || (TAF_PH_MODE_FT == g_stSysCurStatus.ulCurPSStatus))
    {
        SPY_NORMAL_LOG("Spy_CheckTemp: The Tempture Check is Disable");

        return SPY_VOTE_NOMAL;
    }

    if (VOS_OK != mdrv_hkadc_get_temp((HKADC_TEMP_PROTECT_E)(g_stTempProtectNv.ulLocation),
                                      VOS_NULL_PTR, &sTemp, HKADC_CONV_DELAY))
    {
        SPY_WARNING_LOG("Spy_CheckTemp: The Drv Interface Return Failed");

        return SPY_VOTE_NOMAL;
    }

    lSimTemp    = sTemp;

    /*判断两次温度差是否超标*/
    if (SPY_TEMP_MAX_INTERVAL < GET_TEMP_INTERVAL(g_stTempStateCtrl.lOldTemperature, lSimTemp))
    {
        g_stTempStateCtrl.lOldTemperature = lSimTemp;

        SPY_NORMAL1_LOG("Spy_CheckTemp: The Tempture is Too Larger then Old.", lSimTemp);

        return SPY_VOTE_NOMAL;
    }

    SPY_INFO1_LOG("Spy_CheckTemp: SIM temperature is %d", lSimTemp);

    g_stTempStateCtrl.lOldTemperature = lSimTemp;

    if (lSimTemp >= TEMP_POWEROFF_THRESHOLD)
    {
        g_stTempStateCtrl.ulTempPowerOffCount--;

        SPY_WARNING1_LOG("Spy_CheckTemp: The Tempture is Higher then Power Off Level, %d", lSimTemp);

        if(0 == g_stTempStateCtrl.ulTempPowerOffCount)
        {
            Spy_CountInit(TEMP_ALL_ITEM);

            g_stTempStateCtrl.enTempState = TEMP_WAIT_STATE;

            SPY_WARNING_LOG("Spy_CheckTemp: Vote the Power Off");

            return SPY_VOTE_POWEROFF;
        }
    }
    else
    {
        Spy_CountInit(TEMP_POWEROFF_ITEM);
    }

    /*判断是否超过实施关机的条件*/
    if (lSimTemp >= TEMP_CLOSE_THRESHOLD)
    {
        g_stTempStateCtrl.ulTempCloseCount--;

        SPY_WARNING1_LOG("Spy_CheckTemp: The Tempture is Higher then PS Off Level, %d", lSimTemp);

        if (0 == g_stTempStateCtrl.ulTempCloseCount)
        {
            /*进行软关机操作，并进入到低功耗状态*/
            Spy_CountInit(TEMP_ALL_ITEM);

            g_stTempStateCtrl.enTempState = TEMP_WAIT_STATE;

            SPY_WARNING_LOG("Spy_CheckTemp: Vote the soft down");

            return SPY_VOTE_SOFTDOWN;
        }
    }
    else
    {
        Spy_CountInit(TEMP_CLOSE_ITEM);
    }

    /*判断是否超过报警门限的条件*/
    if (lSimTemp >= TEMP_ALARM_THRESHOLD)
    {
        g_stTempStateCtrl.ulTempAlarmCount--;

        SPY_WARNING1_LOG("Spy_CheckTemp: The Tempture is Higher then Warning Level, %d", lSimTemp);

        /*SIM卡温度超过报警条件，进入报警状态*/
        if (0 == g_stTempStateCtrl.ulTempAlarmCount)
        {
            Spy_CountInit(TEMP_ALL_ITEM);

            g_stTempStateCtrl.enTempState = TEMP_WAIT_STATE;

            SPY_WARNING_LOG("Spy_CheckTemp: Vote the Qos 384");

            return SPY_VOTE_QOSDOWN;
        }

        Spy_ReportEvent(SPY_EVENT_TEMP_OVER_HIGH, lSimTemp);
    }
    else
    {
        Spy_CountInit(TEMP_ALARM_ITEM);
    }

    /*判断是否低于恢复门限的条件*/
    if (lSimTemp <= TEMP_RESUME_THRESHOLD)
    {
        g_stTempStateCtrl.ulTempResumeCount--;

        SPY_WARNING1_LOG("Spy_CheckTemp: The Tempture is Lower then Resume Level, %d", lSimTemp);

        /*SIM卡温度低于恢复门限，进行恢复操作*/
        if (0 == g_stTempStateCtrl.ulTempResumeCount)
        {
            Spy_CountInit(TEMP_ALL_ITEM);

            SPY_WARNING_LOG("Spy_CheckTemp: Vote the Resume");

            Spy_ReportEvent(SPY_EVENT_TEMP_RESUME, lSimTemp);

            return SPY_VOTE_RESUME;
        }
    }
    else
    {
        Spy_CountInit(TEMP_RESUME_ITEM);
    }

    return SPY_VOTE_NOMAL;
}

/*****************************************************************************
 函 数 名  : Spy_VoteJudgeState
 功能描述  : 根据投票结果进行系统状态转换，并计算真实的投票结果
 输入参数  : lVote: 投票结果
 输出参数  : 无
 返 回 值  : SPY_VOTERESULT_ENUM 中定义的投票操作
 作者      : z00100318
 修改历史  : z00100318 2009-7-8

*****************************************************************************/
VOS_UINT32 Spy_VoteJudgeState(VOS_INT32 lVote)
{
    SPY_STATE_ENUM_UINT32       enState     = SPY_STATE_NORMAL;
    SPY_VOTERESULT_ENUM_UINT32  enVoteResult= SPY_VOTERESULT_NULL;

    switch(lVote)
    {
        case SPY_VOTE_POWEROFF:/*当前的投票结果是关机*/
            enVoteResult    = SPY_VOTERESULT_POWEROFF;
            SPY_NORMAL_LOG("Spy_VoteJudgeState: The Vote is Power OFF");
            break;

        case SPY_VOTE_SOFTDOWN :
            if(TAF_PH_MODE_FULL == g_stSysCurStatus.ulCurPSStatus)/*当前开机状态是正常情况下可以关机*/
            {
                enState         = SPY_STATE_PSOFF;  /*更新当前系统状态*/
                enVoteResult    = SPY_VOTERESULT_PSOFF;
                SPY_NORMAL_LOG("Spy_VoteJudgeState: The Vote is Soft Down");

                /*lint -e534*/
                Spy_SendAtTempProtectMsg(SPY_STATE_PSOFF, 0);
                /*lint +e534*/
            }
            else /*如果不能正常关机，则将温度保护模块切换到正常状态*/
            {
                enState = g_enSpyCurState;
                g_stTempStateCtrl.enTempState = TEMP_NORMAL_STATE;
                SPY_NORMAL_LOG("Spy_VoteJudgeState: The Current PS Status is not TAF_PH_MODE_FULL");
            }
            break;

        case SPY_VOTE_QOSDOWN: /*当前的投票结果是调节QOS 384*/
            if (SPY_STATE_NORMAL == g_enSpyCurState)
            {
                enState = SPY_STATE_QOS;
                enVoteResult    = SPY_VOTERESULT_DOWNQOS;  /*更新当前系统状态*/
                SPY_NORMAL_LOG("Spy_VoteJudgeState: The Vote is QOS DOWN");

                /*lint -e534*/
                Spy_SendAtTempProtectMsg(SPY_STATE_QOS, 0);
                /*lint +e534*/
            }
            else
            {
                enState = g_enSpyCurState;
                SPY_NORMAL_LOG("Spy_VoteJudgeState: The Vote is NULL");
            }
            break;

        case SPY_VOTE_RESUME:   /*当前需要恢复*/
            if(SPY_STATE_QOS == g_enSpyCurState)/*当前系统状态在调节QOS后才能恢复*/
            {
                enVoteResult    = SPY_VOTERESULT_DEFQOS;
                enState         = SPY_STATE_NORMAL;
                SPY_NORMAL_LOG("Spy_VoteJudgeState: The Vote is Resume Qos");

                /*lint -e534*/
                Spy_SendAtTempProtectMsg(SPY_STATE_NORMAL, 0);
                /*lint +e534*/
            }
            else if(TAF_PH_MODE_LOWPOWER == g_stSysCurStatus.ulCurPSStatus)/*当前软关机状态,并且是SPY触发软关机*/
            {
                enVoteResult    = SPY_VOTERESULT_PSON;  /*系统状态是开机*/
                enState         = SPY_STATE_NORMAL;
                SPY_NORMAL_LOG("Spy_VoteJudgeState: The Vote is Turn On the PS");

                /*lint -e534*/
                Spy_SendAtTempProtectMsg(SPY_STATE_NORMAL, 0);
                /*lint +e534*/
            }
            else
            {
                SPY_WARNING_LOG("Spy_VoteJudgeState: The Current System do not Need Resume");
            }
            break;

        default:
            SPY_NORMAL_LOG("Spy_VoteJudgeState: The Vote is NULL");
            return SPY_VOTERESULT_NULL;
    }

    g_enSpyCurState = enState;

    return enVoteResult;
}

/*****************************************************************************
 函 数 名  : Spy_PowerDown
 功能描述  : 进行硬关机操作
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID

 修改历史  : m00128685
             2009-03-25
*****************************************************************************/
VOS_UINT32 Spy_PowerDown(VOS_VOID)
{
    OAM_MNTN_SPY_ERROR_EVENT_STRU       stSpyErrorLog;

    /* 在Errorlog文件中记录事件 */
    if(VOS_OK != MNTN_RecordErrorLog(MNTN_SPY_PWOER_DOWN_EVENT, (void *)&stSpyErrorLog,
                                            sizeof(OAM_MNTN_SPY_ERROR_EVENT_STRU)))
    {
        SPY_ERROR_LOG("Spy_PowerDown: Fail to record Power Down event in Errorlog file");
    }

#ifdef SPY_STATISTICS_DEBUG
    Spy_TimeRecord("Power Down");
    g_stSpyStatisticsInfo.ulPowerOffNum++;
#endif

    /*lint -e534*/
    vos_printf("\r\nSpy_PowerDown SHUT DOWN\r\n");
    /*lint +e534*/

    /* 当前版本手机形态Modem不在控制单板下电，在模块和MBB产品形态底软接口只能复位单板不再提供下电
       ，所以这里不再调用底软下电接口，直接使用CCPU单独复位接口作为关机保护 */
    VOS_ProtectionReboot(SPY_FLOWCTRL_POWEROFF, VOS_FILE_ID, __LINE__, VOS_NULL, VOS_NULL_PTR);
    /*mdrv_sysboot_shutdown(DRV_SHUTDOWN_TEMPERATURE_PROTECT);*/ /*如果不支持电池也可以调用接口，底软内部打桩*/

    return VOS_OK;
}

/*****************************************************************************
 Prototype       : OM_SysCtrlCmd
 Description     : 给MMA发送消息进行系统控制
 Input           : ulPid -- 发送消息PID.
                   ulMode -- 系统控制类型
 Output          : None
 Return Value    : VOS_UINT32

 History         : ---
    Date         : 2011-10-12
    Author       : g47350
    Modification : Created function
 *****************************************************************************/
VOS_UINT32 Spy_SysCtrlCmd(VOS_UINT8 usOpId, VOS_UINT16 usClientId, VOS_UINT32 ulMode, MODEM_ID_ENUM_UINT16 enModemID)
{
    MN_APP_PHONE_MODE_SET_REQ_STRU *pstMsg;

    if(MODEM_ID_BUTT <= enModemID)
    {
        PS_LOG(WUEPS_PID_SPY, 0, PS_PRINT_ERROR, "OM_SysCtrlCmd: Modem ID Error!");

        return VOS_ERR;
    }

    pstMsg = (MN_APP_PHONE_MODE_SET_REQ_STRU*)VOS_AllocMsg(WUEPS_PID_SPY,
            sizeof(MN_APP_PHONE_MODE_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        PS_LOG(WUEPS_PID_SPY, 0, PS_PRINT_ERROR, "OM_SysCtrlCmd: VOS_AllocMsg failed!");

        return VOS_ERR;
    }

    if(MODEM_ID_1 == enModemID)
    {
        pstMsg->ulReceiverPid      = I1_WUEPS_PID_MMA;
    }
    else
    {
        pstMsg->ulReceiverPid      = I0_WUEPS_PID_MMA;
    }

    pstMsg->ulMsgId            = OAM_MMA_PHONE_MODE_SET_REQ;

    /* 发送消息给NAS进行系统控制 */
    pstMsg->usClientId         = usClientId;
    pstMsg->opID               = usOpId;
    pstMsg->stPhOpMode.CmdType = TAF_PH_CMD_SET;
    pstMsg->stPhOpMode.PhMode  = (VOS_UINT8)ulMode;
    pstMsg->stPhOpMode.PhReset = TAF_PH_OP_MODE_UNRESET;

    return VOS_SendMsg(WUEPS_PID_SPY, pstMsg);
}

/*****************************************************************************
 函 数 名  : Spy_SoftPowerOff
 功能描述  : 进行软关机操作,并启动定时器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID

 修改历史  : m00128685
             2009-03-25
*****************************************************************************/
VOS_UINT32 Spy_SoftPowerOff(VOS_VOID)
{
#ifndef COMM_ITT
    OAM_MNTN_SPY_ERROR_EVENT_STRU       stSpyErrorLog;

    /*关闭2分钟定时器*/
    if (VOS_NULL_PTR!= g_stSpyFlowCtrlTimer)
    {
        /*lint -e534*/
        (VOS_VOID)VOS_StopRelTimer(&g_stSpyFlowCtrlTimer);
        /*lint +e534*/
    }

    /* 在Errorlog文件中记录事件 */
    if(VOS_OK != MNTN_RecordErrorLog(MNTN_SPY_SOFTOFF_EVENT, (void *)&stSpyErrorLog,
                                            sizeof(OAM_MNTN_SPY_ERROR_EVENT_STRU)))
    {
        SPY_ERROR_LOG("Spy_SoftPowerOff: Fail to Write Soft Off event in Errorlog file");
    }

    /* 恢复初速*/
    if (VOS_NULL_PTR != g_pfunRegRestoreProc)
    {
        g_pfunRegRestoreProc();
    }

#ifdef SPY_STATISTICS_DEBUG
    Spy_TimeRecord("Soft Power Off");
    g_stSpyStatisticsInfo.ulSoftPowerOffNum++;
#endif
    /*lint -e534*/
    Spy_SysCtrlCmd(VOS_NULL, OAM_CLIENT_ID_SPY, TAF_PH_MODE_LOWPOWER, MODEM_ID_0);
    /*lint +e534*/
#endif

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : Spy_SoftPowerOn
 功能描述  : 进行软开机操作，并且关闭定时器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID

 修改历史  : m00128685
             2009-03-25
*****************************************************************************/
VOS_UINT32 Spy_SoftPowerOn(VOS_VOID)
{
#ifndef COMM_ITT

#ifdef SPY_STATISTICS_DEBUG
    Spy_TimeRecord("Soft Power On");
    g_stSpyStatisticsInfo.ulSoftPowerOnNum++;
#endif
    /*lint -e534*/
    Spy_SysCtrlCmd(VOS_NULL, OAM_CLIENT_ID_SPY, TAF_PH_MODE_FULL, MODEM_ID_0);
    /*lint +e534*/
#endif

    return VOS_OK;
}

/*****************************************************************************
 函 数 名   : Spy_RateResume
 功能描述   : 进行速率恢复
 输入参数   : pstPdpInfo    指向PDP信息记录结构体
 输出参数   : 无
 返 回 值   : VOS_OK
              VOS_ERR

 修改历史   : m00128685
              2009-03-25
*****************************************************************************/
VOS_UINT32 Spy_FlowCtrlDown()
{
    /*call L2*/
    SPY_NORMAL_LOG("Spy_FlowCtrlDown: Down Flow Control Start.");

    if (VOS_NULL_PTR != g_stSpyFlowCtrlTimer)
    {
        /*lint -e534*/
        (VOS_VOID)VOS_StopRelTimer(&g_stSpyFlowCtrlTimer);
        /*lint +e534*/
    }

#ifdef SPY_STATISTICS_DEBUG
    Spy_TimeRecord("Flow Ctrl Down");
    g_stSpyStatisticsInfo.ulFlowCtrlDownNum++;
#endif

    if (VOS_NULL_PTR != g_pfunRegDowngradeProc)
    {
        /* 如果降速未完成，则需要再启动2分钟定时器*/
        if (SPY_DATA_DOWNGRADE_CONTINUE == g_pfunRegDowngradeProc())
        {
            /*启动2分钟定时器*/
            if (VOS_OK != VOS_StartRelTimer(&g_stSpyFlowCtrlTimer, WUEPS_PID_SPY,
                 SPY_FLOW_CTRL_TIMER_LEN,TIMER_FLOWCTRL,0,VOS_RELTIMER_NOLOOP, VOS_TIMER_NO_PRECISION))
            {
                SPY_ERROR_LOG("Spy_FlowCtrlDown:Start The Check Timer Failed!");
            }
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名   : Spy_RateResume
 功能描述   : 进行速率恢复
 输入参数   : pstPdpInfo    指向PDP信息记录结构体
 输出参数   : 无
 返 回 值   : VOS_OK
              VOS_ERR

 修改历史   : m00128685
              2009-03-25
*****************************************************************************/
VOS_UINT32 Spy_FlowCtrlUp()
{
    /*call L2*/
    SPY_NORMAL_LOG("Spy_FlowCtrlUp: Up Flow Control Start.");

    if (VOS_NULL_PTR!= g_stSpyFlowCtrlTimer)
    {
        /*lint -e534*/
        (VOS_VOID)VOS_StopRelTimer(&g_stSpyFlowCtrlTimer);
        /*lint +e534*/
    }

#ifdef SPY_STATISTICS_DEBUG
    Spy_TimeRecord("Flow Ctrl Up");
    g_stSpyStatisticsInfo.ulFlowCtrlUpNum++;
#endif

    if (VOS_NULL_PTR != g_pfunRegDowngradeProc)
    {
        /* 如果升速未完成，则需要再启动2分钟定时器*/
        if (SPY_DATA_UPGRADE_CONTINUE == g_pfunRegUpgradeProc())
        {
            /*启动2分钟定时器*/
            if (VOS_OK != VOS_StartRelTimer(&g_stSpyFlowCtrlTimer, WUEPS_PID_SPY,
                SPY_FLOW_CTRL_TIMER_LEN,TIMER_FLOWCTRL,0,VOS_RELTIMER_NOLOOP, VOS_TIMER_NO_PRECISION))
            {
                SPY_ERROR_LOG("Spy_FlowCtrlUp:Start The Check Timer Failed!");
            }
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : Spy_Execute
 功能描述  : 根据不同的投票值来决定怎样操作
 输入参数  : ulVoteResult   - 投票结果
 输出参数  : VOS_VOID
 返 回 值  : VOS_UINT32     - 执行结果
 修改历史   : g47350
              2009-07-07

*****************************************************************************/
VOS_UINT32 Spy_Execute(VOS_UINT32 ulVoteResult)
{
    VOS_UINT32  ulResult = VOS_ERR;

    switch(ulVoteResult)
    {
        case SPY_VOTERESULT_DEFQOS:
            SPY_NORMAL_LOG("Spy_Execute: Need Resume the User Default Qos Value");

            ulResult = Spy_FlowCtrlUp();
            break;

        case SPY_VOTERESULT_PSON:
            SPY_NORMAL_LOG("Spy_Execute: Need Re Start the PS");
            ulResult = Spy_SoftPowerOn();
            break;

        case SPY_VOTERESULT_DOWNQOS:
            SPY_NORMAL_LOG("Spy_Execute: Need Limit To the Qos");

            ulResult = Spy_FlowCtrlDown();
            break;

        case SPY_VOTERESULT_PSOFF:
            SPY_NORMAL_LOG("Spy_Execute: Need Power off the PS");
            ulResult = Spy_SoftPowerOff();
            break;

        case SPY_VOTERESULT_POWEROFF:
            SPY_NORMAL_LOG("Spy_Execute: Need Power off the Platform");
            ulResult = Spy_PowerDown();
            break;

        default:
            SPY_WARNING_LOG("Spy_Execute: The Vote is NULL");
            break;
    }

    if(VOS_ERR == ulResult)
    {
        SPY_WARNING1_LOG("Spy_Execute: Excute the Vote %d is Failed",
            (VOS_INT32)ulVoteResult);
    }

    return ulResult;
}

/*****************************************************************************
 函 数 名  : Spy_MainProc
 功能描述  : 系统监控任务的主处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 作者      : z00100318
 修改历史  : z00100318 2009-7-8

*****************************************************************************/
VOS_VOID Spy_MainProc(VOS_VOID)
{
    VOS_INT32  lTempVote;
    VOS_UINT32 ulVoteResult = SPY_VOTERESULT_NULL;
    VOS_UINT32 ulResult     = VOS_OK;
    VOS_UINT32 ulTimeLen    = SPY_TIMER_LEN;
    VOS_UINT32 ulPrecision  = VOS_TIMER_NO_PRECISION;

    lTempVote = Spy_CheckTemp();/*获取温度监控的投票*/

    if (SPY_VOTE_NOMAL != lTempVote)
    {
        Spy_ReportEvent(SPY_EVENT_VOTE_RESULT, (VOS_INT)lTempVote);

        ulVoteResult = Spy_VoteJudgeState(lTempVote);    /*需要根据当前的投票结果确定系统状态转换*/

        if(SPY_VOTERESULT_NULL != ulVoteResult)
        {
            ulTimeLen = TEMP_CLOSE_TIMER_LEN * SPY_TIMER_LEN;

            ulResult = Spy_Execute(ulVoteResult);

            if(VOS_OK != ulResult) /*根据投票结果操作*/
            {
                SPY_ERROR1_LOG(
                    "Spy_MainProc:Spy_Execute return result is  Failed!,Current State is %d", (VOS_INT32)g_enSpyCurState);

                ulTimeLen    = SPY_TIMER_LEN;
            }
        }
    }

    /* 温保软关机后，定时器类型需要修改为32K定时器,确保CCPU下电仍然可以进行温度监控 */
    if (SPY_STATE_PSOFF == g_enSpyCurState)
    {
        ulPrecision = VOS_TIMER_PRECISION_5;
    }

    if(VOS_OK != VOS_StartRelTimer(&g_stSpyTempProtect_Timer, WUEPS_PID_SPY,
                                ulTimeLen,1,0,VOS_RELTIMER_NOLOOP, ulPrecision))
    {
        SPY_ERROR_LOG("Spy_MainProc:Start The Check Timer Failed!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : Spy_E5_CheckSIMTemp
 功能描述  : 用于 E5 防止电池温度实效的保护
 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOS_VOID

 修改历史  : m00128685
             2009-03-25
*****************************************************************************/
VOS_VOID Spy_E5_CheckSIMTemp(VOS_VOID)
{
    VOS_UINT32                  ulResult;
    VOS_INT16                   sTemp;
    VOS_INT                     lSimTemp = 0;

    if(BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_CHARGE))   /*当前不支持电池*/
    {
        return ;
    }

    /*通过底软接口获取当前SIM卡温度*/
    ulResult = (VOS_UINT32)mdrv_hkadc_get_temp(HKADC_TEMP_SIM_CARD, VOS_NULL_PTR, &sTemp, HKADC_CONV_DELAY);

    if(VOS_OK != ulResult)
    {
        SPY_ERROR_LOG("Spy_E5_CheckSIMTemp: DRV_GET_SIM_TEMP Failed");

        return;
    }

    lSimTemp    = sTemp;

    if(lSimTemp >= TEMP_SIM_POWEROFF_THRESHOLD)
    {
        /*lint -e534*/
        vos_printf("\r\nSpy_E5_CheckSIMTemp SHUT DOWN, SIM Temperature is %d\r\n", lSimTemp);
        /*lint +e534*/
        mdrv_sysboot_shutdown(DRV_SHUTDOWN_TEMPERATURE_PROTECT);
    }

    return;
}

/*****************************************************************************
 函 数 名  : Spy_ReadTempMsgProc
 功能描述  : Monitor模块的消息处理函数
 输入参数  : pMsg  消息块
 输出参数  : 无
 返 回 值  : 成功，失败

 修改历史  : m00128685
             2009-03-25
*****************************************************************************/
VOS_UINT32 Spy_ReadTempMsgProc(MsgBlock *pMsg)
{
    /* 保留一个空函数以防方案再次发生变化 */
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : Spy_TempProtectMsgProc
 功能描述  : 消息处理函数
 输入参数  : pMsg:当前输入的消息内容
 输出参数  : 无
 返 回 值  : 无
 作者      : z00100318
 修改历史  : z00100318 2009-7-9

*****************************************************************************/
VOS_VOID Spy_TempProtectMsgProc(MsgBlock *pstMsg)
{
    REL_TIMER_MSG                           *pstExpireMsg;
    TAF_OAM_EMERGENCY_CALL_STATUS_STRU      *pstTafEmergencyMsg;

    if(VOS_PID_TIMER == pstMsg->ulSenderPid)
    {
        pstExpireMsg                = (REL_TIMER_MSG*)pstMsg;

        if (TIMER_FLOWCTRL == pstExpireMsg->ulName)
        {
            /*2分钟定时下调流控*/
            if(SPY_STATE_QOS == g_enSpyCurState)
            {
                /*lint -e534*/
                Spy_FlowCtrlDown();
                /*lint +e534*/
            }

            /*2分钟定时上调流控*/
            if(SPY_STATE_NORMAL == g_enSpyCurState)
            {
                /*lint -e534*/
                Spy_FlowCtrlUp();
                /*lint +e534*/
            }
        }
        else
        {
            Spy_E5_CheckSIMTemp();

            g_stSysCurStatus.ulCurPSStatus = MMA_GetCurrentPhoneMode();

            /* 如果温保软关机失败或用户手动开机，更新温保状态 */
            if ((TAF_PH_MODE_FULL == g_stSysCurStatus.ulCurPSStatus)&&(SPY_STATE_PSOFF == g_enSpyCurState))
            {
                g_enSpyCurState = SPY_STATE_NORMAL;

                SPY_NORMAL_LOG("Spy_TempProtectMsgProc: SPY state change from softoff to normal");

                /*lint -e534*/
                Spy_SendAtTempProtectMsg(SPY_STATE_NORMAL, 0);
                /*lint +e534*/
            }

            Spy_MainProc();
        }
    }
    else if(WUEPS_PID_TAF == pstMsg->ulSenderPid)
    {
        pstTafEmergencyMsg = (TAF_OAM_EMERGENCY_CALL_STATUS_STRU *)pstMsg;

        if ( TAF_OAM_EMERGENCY_CALL_STATUS_NOTIFY != pstTafEmergencyMsg->ulMsgId )
        {
            return;
        }

        if ( TAF_OAM_EMERGENCY_CALL_STATUS_BUTT == pstTafEmergencyMsg->enEmergencyCallStatus )
        {
            return;
        }

        g_ucSpyEmergencyCallState = pstTafEmergencyMsg->enEmergencyCallStatus;
    }
    else
    {
        SPY_WARNING1_LOG("Spy_TempProtectMsgProc: Receive Unkown Msg, Send PID is %d",(VOS_INT32)pstMsg->ulSenderPid);
    }

    return;
}

/*****************************************************************************
 函 数 名  : Spy_FID_Init
 功能描述  : 任务初始化函数
 输入参数  : 初始化步骤
 输出参数  : 无
 返 回 值  : 无
 作者      : z00100318
 修改历史  : z00100318 2009-7-9

*****************************************************************************/
VOS_UINT32 Spy_FID_Init(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32 ulResult = VOS_OK;

    switch (ip)
    {
        case VOS_IP_LOAD_CONFIG:
            ulResult = VOS_RegisterTaskPrio(WUEPS_FID_SPY, COMM_SPY_TASK_PRIO);

            if (ulResult != VOS_OK)
            {
                /*lint -e534*/
                LogPrint("Spy_FID_Init: VOS_RegisterTaskPrio Failed!");
                /*lint +e534*/
                return VOS_ERR;
            }

            ulResult = VOS_RegisterPIDInfo(WUEPS_PID_SPY,
                                            VOS_NULL_PTR,
                                            (Msg_Fun_Type)Spy_TempProtectMsgProc);

            if (ulResult != VOS_OK)
            {
                /*lint -e534*/
                LogPrint("Spy_FID_Init: VOS_RegisterPIDInfo WUEPS_PID_SPY Failed!");
                /*lint +e534*/
                return VOS_ERR;
            }

            ulResult = VOS_RegisterPIDInfo(WUEPS_PID_MONITOR,
                                            VOS_NULL_PTR,
                                            (Msg_Fun_Type)Spy_ReadTempMsgProc);

            if( VOS_OK != ulResult )
            {
                /*lint -e534*/
                LogPrint("Spy_FID_Init: VOS_RegisterPIDInfo WUEPS_PID_MONITOR Failed!");
                /*lint +e534*/
                return VOS_ERR;
            }

            ulResult = VOS_RegisterPIDInfo(WUEPS_PID_SAR,
                                            VOS_NULL_PTR,
                                            (Msg_Fun_Type)Spy_SarMsgProc);

            if( VOS_OK != ulResult )
            {
                /*lint -e534*/
                LogPrint("Spy_FID_Init: VOS_RegisterPIDInfo WUEPS_PID_SAR Failed!");
                /*lint +e534*/
                return VOS_ERR;
            }
            break;

        case VOS_IP_INITIAL:

            /*DRV_USB_STATUS_CALLBACK_REGI(Spy_UsbStatusProc);*/
            Spy_AntenStatusInit();

            ulResult = Spy_TempProtectInit();

            if (ulResult != VOS_OK)
            {
                /*lint -e534*/
                LogPrint("Spy_FID_Init: Spy_TempProtectInit Failed!");
                /*lint +e534*/
                return VOS_ERR;
            }

            break;

        default:
            break;
    }

    return ulResult;

}

/*****************************************************************************
 函 数 名  : Spy_SetTempPara
 功能描述  : 设置热保护参数，包括各门限值和使能位
 输入参数  : 需更改的门限值和使能位
 输出参数  : 无
 返 回 值  : VOS_OK  成功
             VOS_ERR 失败
 作者      : m00128685

*****************************************************************************/
VOS_UINT32 Spy_SetTempPara(SPY_TEMP_THRESHOLD_PARA_STRU *stTempPara)
{
    SPY_TEMP_PROTECT_NV_STRU stTempProtectNv;
    VOS_UINT32               ulChangeFlag = SPY_TEMP_THRESHOLD_PARA_UNCHANGE;

    if(VOS_NULL_PTR == stTempPara)
    {
        SPY_ERROR_LOG("Spy_SetTempPara: Input VOS_NULL_PTR");

        return VOS_ERR;
    }

    /*读取热保护门限值的NV项*/
    if(NV_OK != NV_Read(en_NV_Item_USIM_TEMP_PROTECT_NEW,
                        (VOS_VOID*)&stTempProtectNv,
                        sizeof(SPY_TEMP_PROTECT_NV_STRU)))
    {
        SPY_ERROR_LOG("Spy_SetTempPara: NV_Read en_NV_Item_USIM_TEMP_PROTECT Fail!");

        return VOS_ERR;
    }

    /*若输入参数有效，则进行赋值*/
    if((SPY_TEMP_THRESHOLD_PARA_INVALID != stTempPara->ulIsEnable)
        &&(stTempProtectNv.ulIsEnable != stTempPara->ulIsEnable))
    {
        stTempProtectNv.ulIsEnable = stTempPara->ulIsEnable;
        ulChangeFlag = SPY_TEMP_THRESHOLD_PARA_CHANGE;
    }

    if((SPY_TEMP_THRESHOLD_PARA_INVALID != (VOS_UINT32)stTempPara->lCloseAdcThreshold)
        &&(stTempProtectNv.lCloseAdcThreshold != stTempPara->lCloseAdcThreshold))
    {
        stTempProtectNv.lCloseAdcThreshold = stTempPara->lCloseAdcThreshold;
        ulChangeFlag = SPY_TEMP_THRESHOLD_PARA_CHANGE;
    }

    if((SPY_TEMP_THRESHOLD_PARA_INVALID != (VOS_UINT32)stTempPara->lAlarmAdcThreshold)
        &&(stTempProtectNv.lAlarmAdcThreshold != stTempPara->lAlarmAdcThreshold))
    {
        stTempProtectNv.lAlarmAdcThreshold = stTempPara->lAlarmAdcThreshold;
        ulChangeFlag = SPY_TEMP_THRESHOLD_PARA_CHANGE;
    }

    if((SPY_TEMP_THRESHOLD_PARA_INVALID != (VOS_UINT32)stTempPara->lResumeAdcThreshold)
        &&(stTempProtectNv.lResumeAdcThreshold != stTempPara->lResumeAdcThreshold))
    {
        stTempProtectNv.lResumeAdcThreshold = stTempPara->lResumeAdcThreshold;
        ulChangeFlag = SPY_TEMP_THRESHOLD_PARA_CHANGE;
    }

    /*判断取值合法性*/
    if((stTempProtectNv.lAlarmAdcThreshold >= stTempProtectNv.lCloseAdcThreshold)
       ||(stTempProtectNv.lResumeAdcThreshold >= stTempProtectNv.lAlarmAdcThreshold))
    {
        SPY_ERROR_LOG("Spy_SetTempPara: NV Value Error!");

        return VOS_ERR;
    }

    /*如果用户的输入与原先的门限值不同才写入NV项*/
    if(SPY_TEMP_THRESHOLD_PARA_CHANGE == ulChangeFlag)
    {
        if (NV_OK != NV_Write(en_NV_Item_USIM_TEMP_PROTECT_NEW,
                             (VOS_VOID*)&stTempProtectNv,
                             sizeof(SPY_TEMP_PROTECT_NV_STRU)))
        {
            SPY_ERROR_LOG("Spy_SetTempPara: NV_Write en_NV_Item_USIM_TEMP_PROTECT Fail!");

            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : Spy_DownGradeRegister
 功能描述  : 设置流控降速回调函数
 输入参数  : 流控回调函数
 输出参数  : 无
 返 回 值  : 无
 作者      : s00207770

*****************************************************************************/
VOS_VOID Spy_DownGradeRegister(SPY_DOWNGRADE_PROC_FUNC pFnDowngradeProcFunc)
{
    if (VOS_NULL_PTR ==  pFnDowngradeProcFunc)
    {
        SPY_ERROR_LOG("Spy_DownGradeRegister: Input VOS_NULL_PTR");
        return;
    }

    g_pfunRegDowngradeProc = pFnDowngradeProcFunc;

    if (SPY_STATE_QOS == g_enSpyCurState)
    {
        /*lint -e534*/
        Spy_FlowCtrlDown();
        /*lint +e534*/
    }

    return;
}

/*****************************************************************************
 函 数 名  : Spy_UpGradeRegister
 功能描述  : 设置流控升速回调函数
 输入参数  : 流控回调函数
 输出参数  : 无
 返 回 值  : 无
 作者      : s00207770

*****************************************************************************/
VOS_VOID Spy_UpGradeRegister(SPY_UPGRADE_PROC_FUNC pFnUpgradeProcFunc)
{
    if (VOS_NULL_PTR ==  pFnUpgradeProcFunc)
    {
        SPY_ERROR_LOG("Spy_UpGradeRegister: Input VOS_NULL_PTR");
        return;
    }

    g_pfunRegUpgradeProc = pFnUpgradeProcFunc;

    if (SPY_STATE_NORMAL == g_enSpyCurState)
    {
        /*lint -e534*/
        Spy_FlowCtrlUp();
        /*lint +e534*/
    }
    return;
}

/*****************************************************************************
 函 数 名  : Spy_RestoreRegister
 功能描述  : 设置流控恢复初速回调函数
 输入参数  : 流控回调函数
 输出参数  : 无
 返 回 值  : 无
 作者      : s00207770

*****************************************************************************/
VOS_VOID Spy_RestoreRegister(SPY_RESTORE_PROC_FUNC pFnRestoreProcFunc)
{
    if (VOS_NULL_PTR ==  pFnRestoreProcFunc)
    {
        SPY_ERROR_LOG("Spy_RestoreRegister: Input VOS_NULL_PTR");
        return;
    }

    g_pfunRegRestoreProc = pFnRestoreProcFunc;

    return;
}

#ifdef SPY_STATISTICS_DEBUG
/*****************************************************************************
 函 数 名  : Spy_ShowCmdHelp
 功能描述  : 显示SPY调试命令列表
 输入参数  : None
 输出参数  : None
 返 回 值  : VOS_VOID

 作者      : s00180715
             2012-02-16
*****************************************************************************/
VOS_VOID  Spy_ShowCmdHelp(VOS_VOID)
{
    /*lint -e534*/
    vos_printf("\r\n");
    vos_printf("********************** SPY COMMAND HELP *********************\r\n");
    vos_printf(" Spy_ShowSpyStat [1]\r\n");
    vos_printf(" Spy_ShowSysStat \r\n");
    vos_printf(" Spy_ShowNvItem \r\n");
    vos_printf(" Spy_ShowHkadcTable \r\n");
    vos_printf(" Spy_ShowMonitorStat \r\n");

    vos_printf("*******************************************************************\r\n");
    vos_printf("\r\n");
    /*lint +e534*/

    return;
}

/*****************************************************************************
 函 数 名  : Spy_ShowSpyStat
 功能描述  : 显示SPY状态信息
 输入参数  : None
 输出参数  : None
 返 回 值  : VOS_VOID

 作者      : s00180715
             2012-02-16
*****************************************************************************/
VOS_VOID Spy_ShowSpyStat(VOS_UINT32 ulIndex)
{
    VOS_UINT32 i;

    /*lint -e534*/
    vos_printf("Spy current state:      0x%x\r\n",g_enSpyCurState);
    vos_printf("Spy enable flag:        0x%x\r\n",g_stTempStateCtrl.enTempEnable);
    vos_printf("PowerOff count:         %d\r\n",g_stTempStateCtrl.ulTempPowerOffCount);
    vos_printf("Soft close count:       %d\r\n",g_stTempStateCtrl.ulTempCloseCount);
    vos_printf("Alarm count:            %d\r\n",g_stTempStateCtrl.ulTempAlarmCount);
    vos_printf("Resume count:           %d\r\n",g_stTempStateCtrl.ulTempResumeCount);
    vos_printf("Wait time:              %d\r\n",g_stTempStateCtrl.ulTempWaitTimeLen);
    vos_printf("Last temperature:       %d\r\n",g_stTempStateCtrl.lOldTemperature);

    vos_printf("\r\n");
    vos_printf("Spy timer info:\r\n");
    vos_printf("Spy temp protect timer: 0x%x\r\n",g_stSpyTempProtect_Timer);
    vos_printf("Spy flow ctrl timer:    0x%x\r\n",g_stSpyFlowCtrlTimer);

    vos_printf("\r\n");
    vos_printf("Spy statistics info:\r\n");
    vos_printf("Flow control down num:  %d\r\n",g_stSpyStatisticsInfo.ulFlowCtrlDownNum);
    vos_printf("Flow control up num:    %d\r\n",g_stSpyStatisticsInfo.ulFlowCtrlUpNum);
    vos_printf("Soft power off num:     %d\r\n",g_stSpyStatisticsInfo.ulSoftPowerOffNum);
    vos_printf("Soft power on num:      %d\r\n",g_stSpyStatisticsInfo.ulSoftPowerOnNum);
    vos_printf("Power off num:          %d\r\n",g_stSpyStatisticsInfo.ulPowerOffNum);
    /*lint +e534*/

    if (0 != ulIndex)
    {
        /*lint -e534*/
        vos_printf("\r\n");
        vos_printf("==========================================================\r\n");
        vos_printf("Time Record: count %d, current position %d\r\n",g_stSpyTimeRecord.ulCount,
            ((0==g_stSpyTimeRecord.ulCount) ? 0 : ((g_stSpyTimeRecord.ulCount-1)%SPY_RECORD_NUM)));
        vos_printf("Num      Type                 Time\r\n");
        /*lint +e534*/
        for (i=0; i<((g_stSpyTimeRecord.ulCount<SPY_RECORD_NUM) ? (g_stSpyTimeRecord.ulCount) : SPY_RECORD_NUM); i++)
        {
            /*lint -e534*/
            vos_printf("%3d    %-16s  %10d\r\n",i,g_stSpyTimeRecord.astRecord[i].acType,g_stSpyTimeRecord.astRecord[i].ulTime);
            /*lint +e534*/
        }
    }
}

/*****************************************************************************
 函 数 名  : Spy_ShowSysStat
 功能描述  : 显示SPY系统状态信息
 输入参数  : None
 输出参数  : None
 返 回 值  : VOS_VOID

 作者      : s00180715
             2012-02-16
*****************************************************************************/
VOS_VOID Spy_ShowSysStat(VOS_VOID)
{
    /*lint -e534*/
    vos_printf("PDP status:          0x%x\r\n",g_stSysCurStatus.ulCurPSStatus);
    /*lint +e534*/
}

/*****************************************************************************
 函 数 名  : Spy_ShowNvItem
 功能描述  : 显示SPY NV项信息
 输入参数  : None
 输出参数  : None
 返 回 值  : VOS_VOID

 作者      : s00180715
             2012-02-16
*****************************************************************************/
VOS_VOID Spy_ShowNvItem(VOS_VOID)
{
    /*lint -e534*/
    vos_printf("SPY NV item:\r\n");
    vos_printf("Spy enable flag:        0x%x\r\n",g_stTempProtectNv.ulIsEnable);
    vos_printf("Spy Location:           0x%x\r\n",g_stTempProtectNv.ulLocation);
    vos_printf("PowerOff threshold:     %d\r\n",g_stTempProtectNv.lPowerOffThreshold);
    vos_printf("Soft close threshold:   %d\r\n",g_stTempProtectNv.lCloseAdcThreshold);
    vos_printf("Alarm threshold:        %d\r\n",g_stTempProtectNv.lAlarmAdcThreshold);
    vos_printf("Resume threshold:       %d\r\n",g_stTempProtectNv.lResumeAdcThreshold);
    vos_printf("SIM PowerOff threshold: %d\r\n",g_stTempProtectNv.lSIMPowerOffThreshold);

    vos_printf("Alarm count:            %d\r\n",g_stTempProtectNv.stTempCtrlPara.ucTempOverCount);
    vos_printf("Rusume count:           %d\r\n",g_stTempProtectNv.stTempCtrlPara.ucTempRsumeCount);
    vos_printf("Soft close count:       %d\r\n",g_stTempProtectNv.stTempCtrlPara.ucTempCloseCount);
    vos_printf("PowerOff count:         %d\r\n",g_stTempProtectNv.stTempCtrlPara.ucTempPowerOffCount);
    vos_printf("Wait time:              %d\r\n",g_stTempProtectNv.stTempCtrlPara.ulWaitTimer);

    vos_printf("\r\n");
    vos_printf("AntCtrl NV item:\r\n");
    /*lint +e534*/
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




