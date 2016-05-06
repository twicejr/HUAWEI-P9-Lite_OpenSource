/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptpv2_func.c
*
*  Project Code:
*   Module Name: PTPV2 func
*  Date Created: 2014-03-03
*        Author: luoagwoei
*   Description:
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2014-03-03    luoagwoei               Create
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "tcpip/ptpv2/include/ptpv2_ext.h"
#include "tcpip/ptpv2/include/ptpv2_mac.h"
#include "tcpip/ptpv2/include/ptpv2_common.h"
#include "tcpip/ptpv2/include/ptpv2_bmc.h"
#include "tcpip/ptpv2/include/ptpv2_timer.h"

#include "tcpip/public/entry/tcpip_entry.h"
#include "tcpip/ifnet/include/iifnet_inc.h"
#include "tcpip/ifnet/core/include/if_func.h"
#include "tcpip/public/tcpip_pub.h"
#include "tcpip/public/tcpip_ppi.h"

/*******************************************************************************
*    Func Name: PTPV2_TimerEventProc
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi61496
*  Description: PTPV2 定时器事件处理
*        Input:
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
VOID PTPV2_TimerEventProc()
{
    UINTPTR ulRcvMsg[4] = {0};
    ULONG ulCount = 0;

    /*读取定时器消息队列*/
    while (TCPIP_PTP_OK == VOS_Que_Read(g_ulPtpV2TimerQId, ulRcvMsg, VOS_NO_WAIT, 0))
    {
        if (((VOS_TIMERMSG_S*)ulRcvMsg)->tm_pfFunc)
        {
            (((VOS_TIMERMSG_S*)ulRcvMsg)->tm_pfFunc)(((VOS_TIMERMSG_S*)ulRcvMsg)->tm_pArg);
            ulCount++;
        }

        if (ulCount >= LEN_128) /*一次调度达到128个定时器，释放10ms*/
        {
            PTPV2_UnLock();

            VOS_T_Delay(10);

            ulCount = 0;
            PTPV2_Lock();
        }
    }

    return;
}

/*******************************************************************************
*    Func Name: PTPV2_RcvPacketEventProc
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi61496
*  Description: PTP 报文事件处理
*        Input:
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
VOID PTPV2_RcvPacketEventProc()
{
    UINTPTR ulRcvMsg[4] = {0};
    MBUF_S* pstMBuf;
    ULONG ulPktLen = 0;
    ULONG ulIfRcvIndex = 0;
    ULONG ulCount = 0;

    /*遍历报文处理和内部配置控制消息队列，并执行处理*/
    while (TCPIP_PTP_OK == VOS_Que_Read(g_ulPtpV2PktQId, ulRcvMsg, VOS_NO_WAIT, 0))
    {
        /*目前仅支持overmac*/
        VOS_DBGASSERT(PTPV2_IEEE8023_MSG_TYPE == (ULONG)ulRcvMsg[0]);

        if (NULL == ulRcvMsg[1])
        {
            continue;
        }

        /*读取消息*/
        pstMBuf = (MBUF_S*)ulRcvMsg[1];
        ulPktLen = (ULONG)ulRcvMsg[2];
        ulIfRcvIndex = (UINTPTR)ulRcvMsg[3];

        /*对于overmac来说，两者必须要相同*/
        VOS_DBGASSERT(ulPktLen == MBUF_GET_TOTAL_DATA_LENGTH(pstMBuf));

        VOS_DBGASSERT(ulIfRcvIndex == MBUF_GET_RECEIVE_IFNET_INDEX(pstMBuf));
        (VOID)PTPV2_OverMacPktRcvProc(pstMBuf);

        /*Added by likaikun213099, 清除Fortify DeadCode告警, 2014/9/12   问题单号:DTS2014091008399 */
        ulCount++;
        /* End of Added by likaikun213099, 2014/9/12   问题单号:DTS2014091008399 */
        if (ulCount >= LEN_128) /*一次处理128个报文，释放10ms*/
        {
            PTPV2_UnLock();

            VOS_T_Delay(10);

            ulCount = 0;
            PTPV2_Lock();
        }
    }

    return;
}


/*******************************************************************************
*    Func Name: PTPV2_GetTaskPri
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi61496
*  Description:
*        Input: UINTPTR *pulTaskPri:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_GetTaskPri(UINTPTR *pulTaskPri)
{
    TCPIP_PRECFG_VALUE_S stPreValue   = {0};
    if(NULL == pulTaskPri)
    {
        return TCPIP_PTP_ERR_POINTER_NULL;
    }

    /* 获取预配置的任务优先级 */
    stPreValue.ulKey = PTP_CFG_TASK_PRI;
    if (TCPIP_PTP_OK == TCPIP_Get_PreConfigPara(&stPreValue))
    {
        *pulTaskPri = stPreValue.ulCfg_Value;
    }
    else
    {
        *pulTaskPri = VRP_TASK_SOCK_PRIO;
    }
    return TCPIP_PTP_OK;
}


/*******************************************************************************
*    Func Name: PTPV2_GlobalQueInfoUnInit
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi61496
*  Description:
*        Input:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_GlobalQueInfoUnInit()
{
    g_ulPtpV2ClockType = PTPV2_CLOCK_TYPE_NULL;
    (VOID)VOS_Que_Delete(g_ulPtpV2TimerQId);
    g_ulPtpV2TimerQId = 0;
    (VOID)VOS_Que_Delete(g_ulPtpV2PktQId);
    g_ulPtpV2PktQId = 0;
    
    return TCPIP_PTP_OK;
}

/*******************************************************************************
*    Func Name: PTPV2_GlobalClockInfoInit
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi61496
*  Description:
*        Input:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_GlobalClockInfoInit()
{
    ULONG ulPtpV2ClockType = 0;
    ULONG ulFsmMode = 0;

    DLL_Init(&g_GlobalForeignMasterList);/*初始化Foreign master链表*/
    DLL_Init(&g_PtpV2TimerList);         /*初始化全局定时器链表*/
    (VOID)TCPIP_Mem_Set((CHAR *)&g_PtpV2Tree, 0, sizeof(AVL3_TREE_S));

    /*端口号分配资源初始化*/
    g_pstPortManageInfo = (PTPV2_PORT_MANAGE_S*)TCPIP_Malloc(PTPV2_MID | SID_PTP_PORTMANAGEINFO, sizeof(PTPV2_PORT_MANAGE_S));
    if (NULL == g_pstPortManageInfo)
    {
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27FE, TCPIP_LOG_LEVEL_CRITICAL, LOG_TYPE_RUN,
            "TCPIP PTPV2 LOG: PTPV2_GlobalClockInfoInit malloc g_pstPortManageInfo failed.\r\n",
                         0, 0, 0, 0);
        return TCPIP_PTP_ERR_MALLOC_FAIL;
    }

    /*初始化PTP 端口管理信息*/
    (VOID)TCPIP_Mem_Set((CHAR *)g_pstPortManageInfo, 0, sizeof(PTPV2_PORT_MANAGE_S));

    /*系统全局的信息(含用户配置信息)*/
    g_pstPtpGlobalInfo = (PTPV2_GLOBAL_INFO_S*)TCPIP_Malloc(PTPV2_MID | SID_PTP_GLOBALINFO, sizeof(PTPV2_GLOBAL_INFO_S));
    if (NULL == g_pstPtpGlobalInfo)
    {
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27FF, TCPIP_LOG_LEVEL_ERROR, LOG_TYPE_RUN, "TCPIP PTPV2 LOG: PTPV2_GlobalClockInfoInit malloc g_pstPtpGlobalInfo failed.\r\n",
                         0, 0, 0, 0);
        (VOID)TCPIP_Free(g_pstPortManageInfo);
        return TCPIP_PTP_ERR_MALLOC_FAIL;
    }

    (VOID)TCPIP_Mem_Set((CHAR *)g_pstPtpGlobalInfo, 0, sizeof(PTPV2_GLOBAL_INFO_S));
    
    /*初始化时钟默认值*/
    g_pstPtpGlobalInfo->stCfgDefaultDs.sCurrentUtcOffset = 0;
    g_pstPtpGlobalInfo->stCfgDefaultDs.bLeap61 = FALSE;
    g_pstPtpGlobalInfo->stCfgDefaultDs.bLeap59 = FALSE;
    g_pstPtpGlobalInfo->stCfgDefaultDs.bCurrentUtcOffsetValid = FALSE;
    g_pstPtpGlobalInfo->bPtpTimescale = TRUE;
    g_pstPtpGlobalInfo->ucTimeSource = 0x10;
    g_pstPtpGlobalInfo->bTimeTraceable = 0;
    g_pstPtpGlobalInfo->bFrequencyTraceable = 0;

    g_pstPtpGlobalInfo->ulMaxMasterNum = TCPIP_PTP_FOREIGN_MASTER_LEN;
    g_pstPtpGlobalInfo->ucBMCPolicy = TCPIP_PTP_BMC_POLICY_1588;
    g_pstPtpGlobalInfo->usSndPortMaxNum = PTPV2_MAX_PORTNO;

    g_pstPtpGlobalInfo->stCfgDefaultDs.bTwoStepFlag = FALSE; /*默认单步时钟*/
    g_pstPtpGlobalInfo->stCfgDefaultDs.ucPriClassFlag = PTPV2_NO;/*默认没有优选源*/

    g_pstPtpGlobalInfo->stParentDs.ucBestClassFlag = PTPV2_NOT_PRI_CLASS; /*默认当前源非优选源*/
        
    ulPtpV2ClockType = PTPV2_GetClockType();

    if (PTPV2_CLOCK_TYPE_BC == ulPtpV2ClockType)
    {
        g_pstPtpGlobalInfo->stCfgDefaultDs.usClockFsmMode = PTPV2_FSM_MODE_BC;
        g_pstPtpGlobalInfo->stCfgDefaultDs.stCfgClockQa.ucClockAccuracy = 0xFE;/*initial as unknown*/
    }
    else if (PTPV2_CLOCK_TYPE_OC == ulPtpV2ClockType)
    {
        g_pstPtpGlobalInfo->stCfgDefaultDs.usClockFsmMode = PTPV2_FSM_MODE_OC_MASTER;

        /*OC仅有一个全局端口信息，只在第一次创建OC端口时进行申请*/
        g_pstOCPortSubInfo = (PTPV2_PORT_SUB_INFO_S*)TCPIP_Malloc(PTPV2_MID | SID_PTP_SUBPORTINFO,  sizeof(PTPV2_PORT_SUB_INFO_S));
        if (NULL == g_pstOCPortSubInfo)
        {
            (VOID)TCPIP_Free(g_pstPortManageInfo);
            (VOID)TCPIP_Free(g_pstPtpGlobalInfo);
            TCPIP_LOG_FIXLEN(RUN_LOG_VISP_2800, TCPIP_LOG_LEVEL_ERROR, LOG_TYPE_RUN,
                     "TCPIP PTPV2 LOG: PTPV2_GlobalClockInfoInit Malloc g_pstOCPortSubInfo  Failed!", 0, 0, 0, 0);

            return TCPIP_PTP_ERR_MALLOC_FAIL;
        }

        (VOID)TCPIP_Mem_Set((CHAR *)g_pstOCPortSubInfo, 0, sizeof(PTPV2_PORT_SUB_INFO_S));/*内存初始化*/

        (VOID)PTPV2_GetGlobalInfo(PTPV2_CMD_PORT_FSM_MODE, &ulFsmMode);
        /*初始化OC下的端口级别参数*/
        (VOID)PTPV2_InitPortSubInfo(g_pstOCPortSubInfo, ulFsmMode);
    }

    /*创建虚拟D0,用于后续的数据集比较流程和BC发包流程,当前只有BC会用得到*/
    g_pstVirtualD0 = PTPV2_CreateVirtualD0();
    if (NULL == g_pstVirtualD0)
    {
        (VOID)TCPIP_Free(g_pstPortManageInfo);
        (VOID)TCPIP_Free(g_pstPtpGlobalInfo);
        if (PTPV2_CLOCK_TYPE_OC == ulPtpV2ClockType)
        {
            (VOID)TCPIP_Free(g_pstOCPortSubInfo);
        }
        return TCPIP_PTP_ERR_MALLOC_FAIL;
    }

    return TCPIP_PTP_OK;
}

/*******************************************************************************
*    Func Name: PTPV2_Start
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi61496
*  Description:
*        Input: VOID* pThis:
*               VOID* pData:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_Start(VOID* pThis, VOID* pData)
{
    PTPV2_PORT_S* pstLocalPortInfo = NULL;
    ULONG ulPeriod = 0;
    ULONG ulRet = TCPIP_PTP_OK;

    pstLocalPortInfo = (PTPV2_PORT_S*)pThis;
    if (NULL == pstLocalPortInfo || NULL == pstLocalPortInfo->pstSubPortInfo)
    {
        return TCPIP_PTP_ERR_POINTER_NULL;
    }

    PTPV2_CAL_LOG_TO_MILL(pstLocalPortInfo->pstSubPortInfo->stPortAnnInfo.clogAnnounceInterval, ulPeriod);
    if (0 == ulPeriod)
    {
        ulPeriod = 2000;
    }

    ulRet = PTPV2_CreateLogicTimer(ulPeriod, PTPV2_AnnSndTimerOut, pstLocalPortInfo, &pstLocalPortInfo->pstSubPortInfo->ulAnnSndTimerId);
    if (TCPIP_PTP_OK != ulRet)
    {
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_2801, TCPIP_LOG_LEVEL_ERROR, LOG_TYPE_RUN,
                         "TCPIP PTPV2 LOG: PTPV2_Start  Create annnouce send Timer failed, Period:%u\r\n", ulPeriod, 0, 0, 0);
    }

    pstLocalPortInfo->pstSubPortInfo->ucWorkState = PTPV2_YES;

    return ulRet;
}

/*******************************************************************************
*    Func Name: PTPV2_Stop
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi61496
*  Description:
*        Input: VOID* pThis:
*               VOID* pData:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_Stop(VOID* pThis, VOID* pData)
{
    return TCPIP_PTP_OK;
}

ULONG PTPV2_BcStart(VOID* pThis, VOID* pData)
{
    ULONG ulRet = TCPIP_PTP_OK;

    ulRet = PTPV2_Start(pThis, pData);
   
    if (TCPIP_PTP_OK == ulRet)
    {
        PTPV2_Set_FsmState(((PTPV2_PORT_S*)pThis)->pstSubPortInfo, PTPV2_PORT_FSM_LISTENING);
        PTPV2_Set_PortRole(((PTPV2_PORT_S*)pThis)->pstSubPortInfo, TCPIP_PTP_PORT_ROLE_MASTER);/*BC start后默认为Master角色,不用下发*/        

        if (NULL == g_ulPtpWarningTimerId)
        {
            /*创建定时器，即使失败不能影响其他功能*/
            (VOID)PTPV2_CreateWarningTimer();
        }            
    }    

    return ulRet;
}

ULONG PTPV2_OcStart(VOID* pThis, VOID* pData)
{
    ULONG ulRet = TCPIP_PTP_OK;
    ulRet = PTPV2_Start(pThis, pData);
    if (TCPIP_PTP_OK == ulRet)
    {
        PTPV2_Set_FsmState(((PTPV2_PORT_S*)pThis)->pstSubPortInfo, PTPV2_PORT_FSM_MASTER);
        PTPV2_Set_PortRole(((PTPV2_PORT_S*)pThis)->pstSubPortInfo, TCPIP_PTP_PORT_ROLE_MASTER);
    }
    return ulRet;
}



/******************************************************************************
*Func Name   : PTPV2_Global_UnInit
*Description :  删除所有分配的资源
*Input       : ulPtpMode: PTP模式
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*     DATE                 NAME             DESCRIPTION
*  2014-03-03      luogaowei & dutianyi     create
*******************************************************************************/
ULONG PTPV2_Global_Uninit()
{
    PTPV2_LOGIC_TIMER_S * pstDelTimer = NULL;
    
    /*
    删除信息有
    1. PTP端口信息(备用时钟源 以及对应的定时器Id、sub信息) 、 端口树结构
       告警解除
    2. 离开多播组
    3. PTP全局信息
    4. PTP 管理信息
    5. PTP sub 信息(针对OC)
    6. 全局变量
    */
    if (PTPV2_CLOCK_TYPE_OC == PTPV2_GetClockType())
    {
        PTPV2_DelAllOCPortInfo();/*删除OC的所有资源*/
    }
    else
    {
        PTPV2_DelAllBCPortInfo();/*删除BC的所有资源*/
    }

    /*删除定时器*/
    while (NULL != (pstDelTimer = (PTPV2_LOGIC_TIMER_S *)DLL_First(&g_PtpV2TimerList)))
    {
        DLL_Delete(&g_PtpV2TimerList, (DLL_NODE_S*)pstDelTimer);
        (VOID)TCPIP_Free(pstDelTimer);
    }

    (VOID)TCPIP_Mem_Set((CHAR *)&g_PtpV2Tree, 0, sizeof(AVL3_TREE_S));

    if (DLL_Count(&g_GlobalForeignMasterList))/*这里结点不应该还有数据*/
    {
       TCPIP_LOG_FIXLEN(RUN_LOG_VISP_2802, TCPIP_LOG_LEVEL_CRITICAL, LOG_TYPE_RUN,
            "TCPIP PTPV2 LOG: PTPV2_Global_Uninit g_GlobalForeignMasterList is error.\r\n",
            0, 0, 0, 0);
    }

    (VOID)TCPIP_Mem_Set((CHAR *)&g_GlobalForeignMasterList, 0, sizeof(DLL_S));

    /*清除全局统计信息*/
    (VOID)TCPIP_Mem_Set((CHAR *)&g_stGlobalPtpV2PktStat, 0, sizeof(TCPIP_PTP_PKT_STAT_S));
    
    (VOID)VOS_Timer_Delete(g_ulPtpV2BaseTimerId);
    g_ulPtpV2BaseTimerId = 0;
    (VOID)TCPIP_Mem_Set((CHAR *)&g_PtpV2TimerList, 0, sizeof(DLL_S));

    /*删除全局数据*/
    (VOID)TCPIP_Free(g_pstPortManageInfo);
    g_pstPortManageInfo = NULL;
    (VOID)TCPIP_Free(g_pstPtpGlobalInfo);
    g_pstPtpGlobalInfo = NULL;

    /*删除相关队列*/
    (VOID)PTPV2_GlobalQueInfoUnInit();    
    g_ulPtpV2TaskId = 0;/*任务Id*/
    
    g_ulPtpV2InitFlag = PTPV2_NO;
    g_ulPtpCompVersion = PTPCOMP_VERSION_NULL;
    g_pfPtpV2PpiHookFunc = NULL;
    g_pstBmcEbest  = NULL; /*当前没有时钟源*/
    g_ucPtpGotTimeSourceFlag = PTPV2_NO; /*PTP选到时钟源的标记*/
    g_ulPtpWarningTimerId = 0;  /* 30秒选不到源的一个告警定时器*/
    g_pfPtpV2WarnOutput = NULL;

    PTPV2_FreeVirtualD0();/*释放创建的虚拟D0节点*/
    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_2803, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_RUN,
        "TCPIP PTPv2 LOG: PTPV2_Global_Uninit  suceesfully.\r\n",
         0, 0,  0, 0);
    return TCPIP_PTP_OK;
}


ULONG PTPV2_GetPortInfo(TCPIP_PTP_ADDRINFO_S* pstAddrInfo,
                    PTPV2_PORT_S **ppstPtpPort)
{
    ULONG ulRet = TCPIP_PTP_OK;
    ULONG ulPhyIfIndex = 0;

    VOS_DBGASSERT(NULL != pstAddrInfo);
    VOS_DBGASSERT(NULL != ppstPtpPort);
    /*PTP端口号可能是逻辑接口，不是报文的入接口索引，两者存在一个换算关系*/

    ulPhyIfIndex = pstAddrInfo->ulIfIndex;/*目前是overmac ，两个相同*/

    ulRet = PTPV2_GetPortInfoByIntf(ulPhyIfIndex, &(pstAddrInfo->stDstPortAddr), ppstPtpPort);
    return ulRet;
}

/*******************************************************************************
*    Func Name: PTPV2_TaskMain
* Date Created: 2014-03-18
*       Author: luogaowei & dutianyi61496
*  Description:
*        Input: ULONG ul1:
*               ULONG ul2:
*               ULONG ul3:
*               ULONG ul4:
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-18   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
VOID PTPV2_TaskMain(UINTPTR ul1, UINTPTR ul2, UINTPTR ul3, UINTPTR ul4)
{
    ULONG ulEvRcv = 0;
    ULONG ulRet = TCPIP_PTP_OK;

    (VOID)ul1;
    (VOID)ul2;
    (VOID)ul3;
    (VOID)ul4;

    /*循环读系统事件:定时器事件、报文接收事件、PTPV2任务去初始化事件*/
    for (;;)
    {
        ulRet = VOS_Ev_Read((VOS_TIMER_EVENT | g_ulPtpV2PktRcvEventId | PTPV2_EVT_TASK_OVER_Q), &ulEvRcv, (VOS_EV_ANY | VOS_WAIT), 0);
        if (TCPIP_PTP_OK != ulRet)
        {
            TCPIP_LOG_FIXLEN(RUN_LOG_VISP_2804, TCPIP_LOG_LEVEL_ERROR, LOG_TYPE_RUN, "TCPIP PTPV2 LOG: Read Event failed, result = %u.\r\n",
                             ulRet, 0, 0, 0);
            continue;
        }

        /*处理定时器事件*/
        if (ulEvRcv & VOS_TIMER_EVENT)
        {
            PTPV2_Lock();
            (VOID)PTPV2_TimerEventProc();
            PTPV2_UnLock();
        }

        /*处理报文事件*/
        if (ulEvRcv & g_ulPtpV2PktRcvEventId)
        {
            PTPV2_Lock();
            (VOID)PTPV2_RcvPacketEventProc();
            PTPV2_UnLock();
        }

        /*PTPV2组件去初始化事件*/
        if (ulEvRcv & PTPV2_EVT_TASK_OVER_Q)
        {
            break;
        }
    }

    /*卸载PTPv2 模块 说明用户准备去初始化PTP，卸载前要保证队列数据处理完成*/
    PTPV2_Lock();
    (VOID)PTPV2_Global_Uninit();
    PTPV2_UnLock();

    /*通知产品 PTPV2模块卸载完成*/
    (VOID)TCPIP_SmV(g_ulSynsemId);
    return;
}

/*******************************************************************************
*    Func Name: PTPV2_GlobalTaskInfoInit
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi61496
*  Description:
*        Input: ULONG ulPtpClockType:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_GlobalTaskInfoInit(ULONG ulPtpClockType)
{
    ULONG ulPtpV2TaskPri = 0;

    /*创建定时器消息队列*/
    if (TCPIP_PTP_OK != VOS_Que_Create("PQT2",
                                       PTPV2_QDEPTH,
                                       PTPV2_QMODE,
                                       &g_ulPtpV2TimerQId))
    {
        /*输出日志信息*/
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_2805, TCPIP_LOG_LEVEL_CRITICAL, LOG_TYPE_RUN, "TCPIP PTPV2 LOG: PTPV2_GlobalTaskInfoInit Create Timer queue failed.\r\n",
                         0, 0, 0, 0);
        return TCPIP_PTP_ERR_CREATE_QUEUE_FAILED;
    }

    /* 创建报文消息队列 */
    if (TCPIP_PTP_OK != VOS_Que_Create("PKT2",
                                       PTPV2_QDEPTH,
                                       PTPV2_QMODE,
                                       &g_ulPtpV2PktQId))
    {
        /*输出日志信息*/
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_2806, TCPIP_LOG_LEVEL_CRITICAL, LOG_TYPE_RUN, "TCPIP PTPV2 LOG: PTPV2_GlobalTaskInfoInit Create packet queue failed.\r\n",
                         0, 0, 0, 0);
        (VOID)VOS_Que_Delete(g_ulPtpV2TimerQId);
        g_ulPtpV2TimerQId = 0;
        return TCPIP_PTP_ERR_CREATE_QUEUE_FAILED;
    }

    (VOID)PTPV2_GetTaskPri(&ulPtpV2TaskPri);/*获取PTPV2的任务优先级*/

    /*创建PTP任务,时间片轮转+可抢占 */
    if (TCPIP_PTP_OK != VOS_T_Create(PTPV2_TASK_NAME,
                                     ulPtpV2TaskPri,
                                     (VOS_T_MODE_PREEMPT | VOS_T_MODE_TSLICE),
                                     0,
                                     0,
                                     PTPV2_TaskMain,
                                     &g_ulPtpV2TaskId))
    {
        /*输出日志信息*/
        (VOID)VOS_Que_Delete(g_ulPtpV2TimerQId);
        g_ulPtpV2TimerQId = 0;
        (VOID)VOS_Que_Delete(g_ulPtpV2PktQId);
        g_ulPtpV2PktQId = 0;

        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_2807, TCPIP_LOG_LEVEL_CRITICAL, LOG_TYPE_RUN, "TCPIP PTPV2 LOG: PTPV2_GlobalTaskInfoInit Create task main failed.\r\n",
                 0, 0, 0, 0)

        return TCPIP_PTP_ERR_CREATE_TASK;
    }

    /*创建70ms基定时器*/
    if (TCPIP_PTP_OK != VOS_Timer_Create(g_ulPtpV2TaskId,
                                         g_ulPtpV2TimerQId,
                                         PTPV2_BASE_TIMER_LEN,
                                         (VOID  (*)(VOID*))PTPV2_BaseTimerProc,
                                         (VOID*)0,
                                         &g_ulPtpV2BaseTimerId,
                                         VOS_TIMER_LOOP))
    {
        (VOID)VOS_Que_Delete(g_ulPtpV2TimerQId);
        g_ulPtpV2TimerQId = 0;
        (VOID)VOS_Que_Delete(g_ulPtpV2PktQId);
        g_ulPtpV2PktQId = 0;

        (VOID)VOS_T_Delete(g_ulPtpV2TaskId);
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_2808, TCPIP_LOG_LEVEL_CRITICAL, LOG_TYPE_RUN, "TCPIP PTPV2 LOG: PTPV2_GlobalTaskInfoInit Create base timer failed.\r\n",
            0, 0, 0, 0);

        return TCPIP_PTP_ERR_CREATE_TIMER;
    }

    g_ulPtpV2ClockType = ulPtpClockType;/*PTP 模式*/
    return TCPIP_PTP_OK;
}

/******************************************************************************
*Func Name   : PTPV2_Gloabl_Init
*Description : 分配设备内存，并初始化
*Input       : ulPtpClockType: PTP模式
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*     DATE                 NAME             DESCRIPTION
*  2014-03-03      luogaowei & dutianyi     create
*******************************************************************************/
ULONG PTPV2_Global_Init(ULONG ulPtpClockType)
{
    ULONG ulRet = TCPIP_PTP_OK;

    /*不能是老的PTP版本，两个lib组件互斥*/
    if (PTPCOMP_VERSION_NULL != g_ulPtpCompVersion)
    {
        ulRet = TCPIP_PTP_ERR_OTHER_PTP_USED;
        goto EXIT_LABEL;
    }

    /*只支持BC和OC*/
    if (PTPV2_CLOCK_TYPE_OC != ulPtpClockType && PTPV2_CLOCK_TYPE_BC != ulPtpClockType)
    {
        ulRet = TCPIP_PTP_ERR_INVALID_PARA;
        goto EXIT_LABEL;
    }

    /*初始化PTPv2的任务级资源:如 task、队列、定时器等*/
    ulRet = PTPV2_GlobalTaskInfoInit(ulPtpClockType);
    if (TCPIP_PTP_OK != ulRet)
    {
        goto EXIT_LABEL;
    }

    /*初始化PTPv2的时钟资源*/
    ulRet = PTPV2_GlobalClockInfoInit();
    if (TCPIP_PTP_OK != ulRet)
    {
        (VOID)PTPV2_GlobalQueInfoUnInit();/*释放已经分配的资源: 队列*/
        (VOID)VOS_T_Delete(g_ulPtpV2TaskId);/*删除任务*/
        g_ulPtpV2TaskId = 0;/*任务Id*/
        goto EXIT_LABEL;
    }

    /*挂接PTP报文接收函数*/
    g_pfETH_PTPV2_HOOK = PTPV2_OverMacRcvPktHookEntry;

    /* 初始化成功,置标志位为真 */
    g_ulPtpV2InitFlag = PTPV2_YES;
    /*当前为新的1588 版本*/
    g_ulPtpCompVersion = PTPCOMP_VERSION_NEW;
    /*输出日志信息*/
    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_2809, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_RUN,
    "TCPIP PTPV2 LOG: PTP initialize success, ulPtpClockType = %u.\r\n",
                     ulPtpClockType, 0, 0, 0);

EXIT_LABEL:

    /*logs*/
    return ulRet;

}

#ifdef __cplusplus
}
#endif   /* end of __cplusplus          */
