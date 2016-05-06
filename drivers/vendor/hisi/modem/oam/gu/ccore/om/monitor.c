/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : Monitor.C
  版 本 号   : 初稿
  作    者   : m00128685
  生成日期   : 2009年3月23日
  最近修改   :
  功能描述   : Monitor模块
  函数列表   :
  修改历史   :
  1.日    期   : 2008年2月1日
    作    者   : m00128685
    修改内容   : 创建文件

******************************************************************************/

#if 0

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人：m00128685；检视人：l46160；原因简述：打点日志文件宏ID定义*/
#define    THIS_FILE_ID        PS_FILE_ID_MONITOR_C
/*lint +e767 修改人：m00128685；检视人：l46160*/


/*****************************************************************************
  1 头文件包含
*****************************************************************************/

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

#if 0
MONITOR_USIM_ANT2_CTRL    g_stMonitorUsimAntCtrl;

MONITOR_PA_PARA_STRU      g_stMonitorPAPara = {MONITOR_DEFAULT_PA_TEMPERATURE,
                                               MONITOR_DEFAULT_BATTERY_VOLTAGE};/*PA温度及电池电压*/

VOS_UINT32                g_ulMonitorIndType = ID_PHY_MONITOR_NULL_IND; /*DSP上报的中断类型*/

VOS_UINT32                g_ulMonitorConnectState = MONITOR_IDLE_STATE; /*目前的连接状态*/

VOS_UINT32                g_ulMonitorCtrlSem = VOS_NULL_PTR;  /* Monitor互斥信号量 */

VOS_UINT32                g_ulMonitorErrCode = MONITOR_ERR_CODE_NONE;/* Monitor模块错误码*/

HTIMER                    g_hQueryTimer = VOS_NULL_PTR; /*Monitor定时器*/

VOS_UINT32                g_ulPHYSimTempFlag = MONITOR_SIM_TEMP_LOW_FLAG; /*关分集后记录当前所处的温度区段*/

VOS_INT32                 g_lSimTempBuf[MONITOR_SIM_TEMP_BUF_LEN];

VOS_UINT32                g_ulSimTempBufPointor = 0;

extern VOS_VOID GSleep_ProcPsWakeCmd(VOS_VOID);

extern VOS_VOID SLEEP_ForceAwake(VOS_VOID);

/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : Monitor_Init
 功能描述  : 温度保护模块初始化函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID

 修改历史  : m00128685
             2009-03-25
*****************************************************************************/
VOS_UINT32 Monitor_Init(VOS_VOID)
{

    /*读取开关分集的USIM卡温度门限*/
    if(NV_OK != NV_Read(en_NV_Item_W_USIM_TEMP_ANT2_CTRL,
                            (VOS_VOID*)&g_stMonitorUsimAntCtrl,
                            sizeof(MONITOR_USIM_ANT2_CTRL)))
    {
        g_ulMonitorErrCode |= MONITOR_ERR_CODE_NV;

        return VOS_ERR;
    }

    if (VOS_OK != VOS_SmCCreate("MONS", 0, VOS_SEMA4_FIFO, &(g_ulMonitorCtrlSem)))
    {
        g_ulMonitorErrCode |= MONITOR_ERR_CODE_SEM;

        return VOS_ERR;
    }

#if (VOS_VXWORKS == VOS_OS_VER)
    taskSpawn("MONITOR_TASK", 159, 0, 10240,(FUNCPTR)Monitor_QueryTask, 0, 0, 0, 0, 0, 0, 0, 0,0,0);
#endif

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : Monitor_WakeUpDsp
 功能描述  : 查询温度时唤醒DSP
 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOS_VOID

 修改历史  : h59254
             2009-05-04
*****************************************************************************/
VOS_VOID Monitor_WakeUpDsp(VOS_UINT32  RAT_mode)
{
    if( SHPA_SYSTEM_GSM == RAT_mode )
    {
        GSleep_ProcPsWakeCmd();
    }
    else
    {
        SLEEP_ForceAwake();
    }

    return;
}

/*****************************************************************************
 函 数 名  : Monitor_QueryPA
 功能描述  : PA温度及电池电压查询函数
 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOS_VOID

 修改历史  : m00128685
             2009-03-25
*****************************************************************************/
VOS_VOID Monitor_QueryPA(VOS_INT lSimTemp)
{
    VOS_INT     lPaTemperature  = MONITOR_DEFAULT_PA_TEMPERATURE;
    VOS_INT     lBatteryVoltage = MONITOR_DEFAULT_BATTERY_VOLTAGE;
    VOS_UINT32  RAT_mode;
    VOS_INT32   lResult = VOS_ERROR;
    VOS_UINT32  ulTempType = CPHY_TEMPERATURE_TYPE_NULL;
    VOS_INT32   lSimAverageTemp = 0;
    VOS_UINT32  i;

    RAT_mode =  SHPA_GetRateType();

    /* 调用底软接口，读取当前PA温度 */
    if( SHPA_SYSTEM_GSM == RAT_mode )
    {
        lResult = DRV_GET_PA_GTEMP(&lPaTemperature, g_pusAdcTable);
    }
    else if( SHPA_SYSTEM_WCDMA == RAT_mode )
    {
        lResult = DRV_GET_PA_WTEMP(&lPaTemperature, g_pusAdcTable);
    }
    else
    {
        return;
    }

    if (VOS_OK != lResult)
    {
        /*lint -e534*/
        LogPrint1("\r\nMonitor_QueryPA:Query Tempareture:%d.!", lResult);
        /*lint +e534*/
        return;
    }


    /* 保存当前温度到循环队列 */
    g_ulSimTempBufPointor = g_ulSimTempBufPointor%MONITOR_SIM_TEMP_BUF_LEN;

    g_lSimTempBuf[g_ulSimTempBufPointor] = lSimTemp;

    g_ulSimTempBufPointor++;


    /* 取温度循环队列平均值 */
    for(i = 0; i < MONITOR_SIM_TEMP_BUF_LEN; i++)
    {
        lSimAverageTemp += g_lSimTempBuf[i];

    }

    lSimAverageTemp = (lSimAverageTemp/MONITOR_SIM_TEMP_BUF_LEN);

    /*判断是否需要将SIM卡温度报给物理层*/
    if((g_stMonitorUsimAntCtrl.sUsimHigh <= lSimAverageTemp)&&
       (MONITOR_SIM_TEMP_LOW_FLAG == g_ulPHYSimTempFlag))
    {

        g_ulPHYSimTempFlag = MONITOR_SIM_TEMP_HIGH_FLAG;

        ulTempType = CPHY_TEMPERATURE_TYPE_SIM;
    }
    else if((g_stMonitorUsimAntCtrl.sUsimLow > lSimAverageTemp)&&(MONITOR_SIM_TEMP_HIGH_FLAG == g_ulPHYSimTempFlag))
    {
        g_ulPHYSimTempFlag = MONITOR_SIM_TEMP_LOW_FLAG;

        ulTempType = CPHY_TEMPERATURE_TYPE_SIM;
    }
    else
    {
        /*do nothing*/
    }

    /* 如果温度改变超过门限值OM_PA_TEMPERATURE_DIFF_LIMIT */
    if ((( lPaTemperature + MONITOR_PA_TEMPERATURE_DIFF_LIMIT ) < g_stMonitorPAPara.lPaTemperature )
        || (( g_stMonitorPAPara.lPaTemperature + MONITOR_PA_TEMPERATURE_DIFF_LIMIT ) < lPaTemperature ))
    {
        g_stMonitorPAPara.lPaTemperature = lPaTemperature;

        ulTempType |= CPHY_TEMPERATURE_TYPE_PA;
    }


    if(CPHY_TEMPERATURE_TYPE_NULL != ulTempType)
    {
        Monitor_WakeUpDsp(RAT_mode);

        /* 将温度信息发送给DSP*/
        Shpa_ProcTemperatureReq(GGPHY_MONITOR_TEMP_REQ, (VOS_INT16)lPaTemperature,
                                (VOS_INT16)lSimAverageTemp,ulTempType);
    }

    /* 调用底软接口，读取当前电池电压 */

    /* 如果电压改变超过门限值OM_BATTERY_VOLTAGE_DIFF_LIMIT */
    if ((( lBatteryVoltage + MONITOR_BATTERY_VOLTAGE_DIFF_LIMIT ) < g_stMonitorPAPara.lBatteryVoltage )
        || (( g_stMonitorPAPara.lBatteryVoltage + MONITOR_BATTERY_VOLTAGE_DIFF_LIMIT ) < lBatteryVoltage ))
    {
        g_stMonitorPAPara.lBatteryVoltage = lBatteryVoltage;

        /* 将当前电池电压信息发送给DSP*/

        Shpa_ProcVoltageReq(GGPHY_MONITOR_VOLTAGE_REQ, (VOS_UINT16)lBatteryVoltage);
    }

    return;
}

/*****************************************************************************
 函 数 名  : Moniter_SetPhyIndType
 功能描述  : 物理层上报给校准模块的中断类型设置
 输入参数  : ulPhyIndType
 输出参数  : 无
 返 回 值  : VOS_VOID

 修改历史  : m00128685
             2009-03-25

*****************************************************************************/
VOS_VOID Moniter_SetPhyIndType( VOS_UINT32 ulPhyIndType )
{
    g_ulMonitorIndType = ulPhyIndType;
    return;
}

/*****************************************************************************
 函 数 名  : Moniter_SendReq
 功能描述  : 温度查询请求发送函数
 输入参数  : ulSenderPid
             ulCmdType

 输出参数  : 无
 返 回 值  : VOS_VOID

 修改历史  : m00128685
             2009-03-25

*****************************************************************************/
VOS_VOID Moniter_SendReq(VOS_UINT32 ulSenderPid, VOS_UINT32 ulCmdType)
{
    MONITOR_CMD_STRU *pMsg;

    pMsg = (MONITOR_CMD_STRU *)VOS_AllocMsg(ulSenderPid,
                               sizeof(MONITOR_CMD_STRU)-VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pMsg)
    {
        g_ulMonitorErrCode |= MONITOR_ERR_CODE_MEM;
        return;
    }

    pMsg->ulMsgName     = ulCmdType;
    pMsg->ulReceiverPid = WUEPS_PID_MONITOR;

    if (VOS_OK != VOS_SendMsg(ulSenderPid, pMsg))
    {
        g_ulMonitorErrCode |= MONITOR_ERR_CODE_MSG;
    }

    return;
}

/*****************************************************************************
 函 数 名  : Monitor_QueryTask
 功能描述  : Monitor监控管理自处理任务
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID

 修改历史  : m00128685
             2009-03-25
*****************************************************************************/
VOS_VOID Monitor_QueryTask( VOS_VOID )
{
#if 0
    VOS_UINT32       ulRet;
#endif

    for(;;)
    {
        /* 等待信号量 */
        VOS_SmP(g_ulMonitorCtrlSem, 0);

#if 0

        switch ( g_ulMonitorConnectState )
        {
            case MONITOR_IDLE_STATE:

                if (ID_PHY_MONITOR_QUERY_IND == g_ulMonitorIndType )   /* IDLE态收到环境查询中断 */
                {
                    Moniter_SendReq(WUEPS_PID_MONITOR,ID_MONITOR_TEMP_QUERY_REQ);
                }
                else                                        /* IDLE态收到进入NORMAL态中断 */
                {
                    if (VOS_NULL_PTR == g_hQueryTimer)
                    {
                       ulRet = VOS_StartRelTimer( &g_hQueryTimer,
                                                   WUEPS_PID_MONITOR,
                                                   2000,
                                                   MONITOR_TIMER_NAME_QUERY,
                                                   0,
                                                   VOS_RELTIMER_LOOP );

                        if(VOS_OK != ulRet)
                        {
                            g_ulMonitorErrCode |= MONITOR_ERR_CODE_TIMER;
                        }
                    }

                    g_ulMonitorConnectState = MONITOR_CONNECT_STATE;
                }

                break;

            case MONITOR_CONNECT_STATE:      /* 进入CONN态 */

                if (ID_PHY_MONITOR_QUERY_IND == g_ulMonitorIndType )   /* IDLE态收到环境查询中断 */
                {
                    if( VOS_NULL_PTR != g_hQueryTimer )
                    {
                        VOS_StopRelTimer( &g_hQueryTimer );
                    }

                    g_hQueryTimer = VOS_NULL_PTR;

                    Moniter_SendReq(WUEPS_PID_MONITOR, ID_MONITOR_TEMP_QUERY_REQ);

                    g_ulMonitorConnectState = MONITOR_IDLE_STATE;
                }
                else
                {
                    g_ulMonitorErrCode |= MONITOR_ERR_CODE_INT;
                }

                break;

            default:
                break;
        }
#endif
    }
}

/*****************************************************************************
 函 数 名  : Monitor_TimerMsgProc
 功能描述  : Monitor模块定时器超时消息处理函数
 输入参数  : pMsg  消息块
 输出参数  : 无
 返 回 值  : 成功，失败

 修改历史  : m00128685
             2009-03-25

*****************************************************************************/
VOS_VOID Monitor_TimerMsgProc(REL_TIMER_MSG *pMsg)
{

    if (MONITOR_TIMER_NAME_QUERY == pMsg->ulName)
    {
        Monitor_QueryPA(g_stTempStateCtrl.lOldTemperature);/*查询PA温度*/
    }
    else
    {
        g_ulMonitorErrCode |= MONITOR_ERR_CODE_MSGPROC;
    }

    return;
}

/*****************************************************************************
 函 数 名  : Monitor_MsgProc
 功能描述  : Monitor模块的消息处理函数
 输入参数  : pMsg  消息块
 输出参数  : 无
 返 回 值  : 成功，失败

 修改历史  : m00128685
             2009-03-25
*****************************************************************************/
VOS_UINT32 Monitor_MsgProc(MsgBlock *pMsg)
{
#if 0
    MONITOR_CMD_STRU *pCmdMsg;

    if (VOS_PID_TIMER == pMsg->ulSenderPid)
    {
        Monitor_TimerMsgProc((REL_TIMER_MSG *)pMsg);

        return VOS_OK;
    }

    pCmdMsg = (MONITOR_CMD_STRU *)pMsg;

    switch (pCmdMsg->ulMsgName)
    {
        case ID_MONITOR_TEMP_QUERY_REQ:

            Monitor_QueryPA(g_stTempStateCtrl.lOldTemperature);/*查询PA温度*/

            break;

        default:

            break;

    }
#endif
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : WuepsMonitorPidInit
 功能描述  : PID初始化函数
 输入参数  : VOS_INIT_PHASE_DEFINE 初始化步骤
 输出参数  : 无
 返 回 值  :

 修改历史  : m00128685
             2009-03-25

*****************************************************************************/
VOS_UINT32 WuepsMonitorPidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    switch( ip )
    {
        case   VOS_IP_LOAD_CONFIG:

            if (VOS_OK != Monitor_Init())
            {
                /*lint -e534*/
                LogPrint("\r\nWuepsMonitorPidInit:Monitor_Init Fail!");
                /*lint +e534*/
            }

           break;
        case   VOS_IP_FARMALLOC:
        case   VOS_IP_INITIAL:
        case   VOS_IP_ENROLLMENT:
        case   VOS_IP_LOAD_DATA:
        case   VOS_IP_FETCH_DATA:
        case   VOS_IP_STARTUP:
        case   VOS_IP_RIVAL:
        case   VOS_IP_KICKOFF:
        case   VOS_IP_STANDBY:
        case   VOS_IP_BROADCAST_STATE:
        case   VOS_IP_RESTART:
        case   VOS_IP_BUTT:
            break;
    }
    return VOS_OK;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
