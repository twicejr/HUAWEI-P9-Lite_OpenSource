/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptpv2_timer.c
*
*  Project Code:
*   Module Name: PTPV2 timer
*  Date Created: 2014-03-03
*        Author: luoagwoei & dutianyi
*   Description:
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2014-03-03  luoagwoei & dutianyi      Create
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "tcpip/ptpv2/include/ptpv2_ext.h"
#include "tcpip/ptpv2/include/ptpv2_bmc.h"
#include "tcpip/ptpv2/include/ptpv2_common.h"
#include "tcpip/ptpv2/include/ptpv2_timer.h"
#include "tcpip/ptpv2/include/ptpv2_ann.h"
#include "tcpip/public/tcpip_basefun.h"
#include "tcpip/etharp/include/etharp_api.h"

/*******************************************************************************
*    Func Name: PTPV2_CreateLogicTimer
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi61496
*  Description: 创建PTPV2 逻辑定时器
*        Input: ULONG ulPeriod:
*               PTPV2_FUNC_LOGIC_TIMER pfFunc:
*               VOID* pArg:
*               ULONG* pulTimerId:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_CreateLogicTimer(ULONG ulPeriod, PTPV2_FUNC_LOGIC_TIMER pfFunc, VOID* pArg, ULONG* pulTimerId)
{
    ULONG ulTimeHigh = 0;
    ULONG ulTimeLow = 0;
    ULONG ulTime = 0;
    PTPV2_LOGIC_TIMER_S* pstLogicTimer = NULL;

    if (NULL == pfFunc)
    {
        return TCPIP_PTP_ERR_INVALID_PARA;
    }

    /* 判断逻辑定时器是否超出规格 */
    if (g_PtpV2TimerList.u4_Count >= PTPV2_LOGIC_TIMER_MAX_NUM)
    {
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_280E, TCPIP_LOG_LEVEL_DEBUG, LOG_TYPE_RUN,
                         "TCPIP PTPV2 LOG: PTPV2_CreateLogicTimer failed, up to max!", 0, 0, 0, 0);
        return TCPIP_PTP_ERR_TIMER_NUM_FULL;
    }

    pstLogicTimer = (PTPV2_LOGIC_TIMER_S*)TCPIP_Malloc(PTPV2_MID | SID_PTP_TIMER, sizeof(PTPV2_LOGIC_TIMER_S));
    if (NULL == pstLogicTimer)
    {
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_280F, TCPIP_LOG_LEVEL_ERROR, LOG_TYPE_RUN,
                         "TCPIP PTPV2 LOG: PTPV2_CreateLogicTimer Malloc  pstLogicTimer  Failed!", 0, 0, 0, 0);

        return TCPIP_PTP_ERR_MALLOC_FAIL;
    }

    pstLogicTimer->ulPeriod = ulPeriod;
    pstLogicTimer->pfFunc = pfFunc;
    pstLogicTimer->pArg = pArg;
    pstLogicTimer->ulDelFlag = PTPV2_TIMER_NOT_DELETE;

    /*将该定时器节点的指针(地址)作为TimerId*/
    pstLogicTimer->ulTimerId = (ULONG)pstLogicTimer;
    *pulTimerId = pstLogicTimer->ulTimerId;

    /*获取当前时间并赋值到相应时间字段*/
    (VOID)VOS_Tm_Now(&ulTimeHigh, &ulTimeLow);

    /* 如果定时器超时时间ulOutTime + ulTimeLow时间小于0xFFFFFFFF,
     *就保持ulEndTimeHigh不变，直接在ulEndTimeLow上加上ulOutTime即可 */
    ulTime = 0xFFFFFFFF - ulTimeLow;
    if (ulTime >= ulPeriod)
    {
        pstLogicTimer->ulEndTimeLow = ulTimeLow + ulPeriod;
        pstLogicTimer->ulEndTimeHigh = ulTimeHigh;
    }
    /* 如果定时器超时周期 + ulTimeLow时间大于0xFFFFFFFF,
     *ulEndTimeHigh需要加1，在ulEndTimeLow上加上周期 */
    else
    {
        pstLogicTimer->ulEndTimeHigh = ulTimeHigh + 1;
        pstLogicTimer->ulEndTimeLow = ulPeriod + ulTimeLow;
    }

    DLL_Add(&g_PtpV2TimerList, (DLL_NODE_S*)pstLogicTimer);

    /*定时器Debug信息*/
    if (g_ulPtpV2GlobalDbgSwitch & TCPIP_PTP_DEBUG_TIMER)
    {
        TCPIP_InfoOutput("\r\ncreate logic timer:");

        PTPV2_TimerPrint(pstLogicTimer);
    }

    return TCPIP_PTP_OK;
}

ULONG PTPV2_ResetLogicTimer(ULONG ulTimerId)
{
    ULONG ulTimeHigh = 0;
    ULONG ulTimeLow = 0;
    ULONG ulTime = 0;
    PTPV2_LOGIC_TIMER_S* pstLogicTimer = NULL;

    pstLogicTimer = (PTPV2_LOGIC_TIMER_S*)ulTimerId;
    if (NULL == pstLogicTimer)
    {
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_2810, TCPIP_LOG_LEVEL_ERROR, LOG_TYPE_RUN,
             "TCPIP PTPV2 LOG: PTPV2_ResetLogicTimer LogicTimerId is zero!", 0, 0, 0, 0);

        return TCPIP_PTP_ERR_LOGIC_TIMERID_NULL;
    }

    /* 检查链表是否为空 */
    if (0 == g_PtpV2TimerList.u4_Count)
    {
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_2811, TCPIP_LOG_LEVEL_ERROR, LOG_TYPE_RUN,
             "TCPIP PTPV2 LOG: PTPV2_ResetLogicTimer  There is no timer!", 0, 0, 0, 0);

        return TCPIP_PTP_ERR_LOGIC_TIMER_NUM_ZERO;
    }

    /*获取当前时间并赋值到相应时间字段*/
    (VOID)VOS_Tm_Now(&ulTimeHigh, &ulTimeLow);

    /*如果定时器超时周期 + ulTimeLow时间不大于0xFFFFFFFF,
     *ulEndTimeHigh保持不变，直接在ulEndTimeLow上加上ulOutTime即可*/
    ulTime = 0xFFFFFFFF - ulTimeLow;
    if (ulTime >= pstLogicTimer->ulPeriod)
    {
        pstLogicTimer->ulEndTimeLow = ulTimeLow + pstLogicTimer->ulPeriod;
        pstLogicTimer->ulEndTimeHigh = ulTimeHigh;
    }
    /*如果定时器超时周期 + ulTimeLow时间大于0xFFFFFFFF,
     *ulEndTimeHigh需要加1，在ulEndTimeLow上加上周期 */
    else
    {
        pstLogicTimer->ulEndTimeHigh = ulTimeHigh + 1;
        pstLogicTimer->ulEndTimeLow = pstLogicTimer->ulPeriod + ulTimeLow;
    }

    return TCPIP_PTP_OK;
}

/*******************************************************************************
*    Func Name: PTPV2_DeleteLogicTimer
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi61496
*  Description: 删除PTP 逻辑定时器
*        Input: ULONG ulTimerId:定时器Id
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
ULONG PTPV2_DeleteLogicTimer(ULONG ulTimerId)
{
    PTPV2_LOGIC_TIMER_S* pstLogicTimer = NULL;

    /*TimerId即为分配的控制块指针地址，不能为空*/
    pstLogicTimer = (PTPV2_LOGIC_TIMER_S*)ulTimerId;
    if (NULL == pstLogicTimer)
    {
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_2812, TCPIP_LOG_LEVEL_ERROR, LOG_TYPE_RUN,
                         "TCPIP PTPV2 LOG:PTPV2_DeleteLogicTimer logicTimerId is not exist!", 0, 0, 0, 0);
        return TCPIP_PTP_ERR_LOGIC_TIMERID_NULL;
    }

    /*把DelFlag设置为PTPV2_TIMER_DELETE，表示即将删除该定时器*/
    pstLogicTimer->ulDelFlag = PTPV2_TIMER_DELETE;

    /*定时器Debug信息*/
    if (g_ulPtpV2GlobalDbgSwitch & TCPIP_PTP_DEBUG_TIMER)
    {
        TCPIP_InfoOutput("\r\ndelete logic timer:");

        PTPV2_TimerPrint(pstLogicTimer);
    }

    return TCPIP_PTP_OK;
}

/*******************************************************************************
*    Func Name: PTPV2_BaseTimerProc
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi61496
*  Description: PTPV2的基定时器
*        Input: VOID* pArg:
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
VOID PTPV2_BaseTimerProc(VOID* pArg)
{
    ULONG ulTimeHigh = 0;
    ULONG ulTimeLow = 0;
    PTPV2_LOGIC_TIMER_S* pstIter = NULL;
    PTPV2_LOGIC_TIMER_S* pstDelTimer = NULL;
    ULONG ulCount = 0;

    (VOID)pArg;
    /*获取当前时间并赋值到相应时间字段*/
    (VOID)VOS_Tm_Now(&ulTimeHigh, &ulTimeLow);

    /*遍历链表，而后调用处理函数处理*/
    DLL_Scan(&g_PtpV2TimerList, pstIter, PTPV2_LOGIC_TIMER_S*)
    {
        /*删除定时器*/
        if(PTPV2_TIMER_DELETE == pstIter->ulDelFlag)
        {
            pstDelTimer = pstIter;
            pstIter = (PTPV2_LOGIC_TIMER_S *)(DLL_Previous(&g_PtpV2TimerList,(DLL_NODE_S *)pstIter));
            DLL_Delete(&g_PtpV2TimerList, (DLL_NODE_S*)pstDelTimer);
            (VOID)TCPIP_Free(pstDelTimer);

            continue;
        }

        if ((pstIter->ulEndTimeHigh < ulTimeHigh) ||
            ((pstIter->ulEndTimeHigh == ulTimeHigh) && (pstIter->ulEndTimeLow <= ulTimeLow)))
        {

            if (( NULL != pstIter->pfFunc ) && (0 != pstIter->ulTimerId))
            {
                (VOID)pstIter->pfFunc(pstIter->pArg);
                ulCount ++;
            }
        }

        /* 每遍历500个释放1ms cpu */
        if (LEN_512 == ulCount)
        {
            ulCount = 0;
            (VOID)VOS_T_Delay(1);
        }

    }

    return;
}

ULONG PTPV2_AnnSndTimerOut(VOID* pArg)
{
    ULONG ulRet = TCPIP_PTP_OK;
    PTPV2_PORT_S* pstPtpPort = NULL;
    MBUF_S* pstMBuf = NULL;
    UCHAR ucSrcMacAddr[PTPV2_MACADDRLEN] = {0};
    UCHAR *pucDstMacAddr = NULL;
    /*用于传入获取报文信息，目前仅传入接口索引信息*/
    TCPIP_PTP_ADDRINFO_S stAddrInfo;
    PTPV2_LOGIC_TIMER_S *pstLogicTimer = NULL;

    (VOID)TCPIP_Mem_Set((VOID *)&stAddrInfo, 0, sizeof(TCPIP_PTP_ADDRINFO_S));

    /* 参数合法性检查 */
    if (NULL == pArg)
    {
        return TCPIP_PTP_ERR_POINTER_NULL;
    }

    /*将pArg强制转化PTP PORT*/
    pstPtpPort = (PTPV2_PORT_S*)pArg;

    /*BC下如果没有曾经选到时钟源，则所有端口都不需要发送报文
      为了降低复杂度，定时器还是在启动时候创建
    */
    if (g_ucPtpGotTimeSourceFlag == PTPV2_NO && PTPV2_CLOCK_TYPE_BC == PTPV2_GetClockType())
    {
        return TCPIP_PTP_ERR_NO_TIME_SOURCE;
    }
 

    if (NULL == pstPtpPort->pfPtpBuildAnnPktFunc || NULL == pstPtpPort->pfPtpSndAnnPktFunc)
    {
        return TCPIP_PTP_ERR;
    }

    /*调用协议处理函数构造Ann报文*/
    ulRet = pstPtpPort->pfPtpBuildAnnPktFunc((VOID *)pstPtpPort,(VOID **)&pstMBuf);
    if (TCPIP_PTP_OK != ulRet)
    {
        return ulRet;
    }

    /*报文统计*/
    g_stGlobalPtpV2PktStat.ulSndAnnPackets ++;
    pstPtpPort->stPacketStat.ulSndAnnPackets ++;

    /*获取地址信息*/
    /*获取目的地址*/
    if (TCPIP_PTP_DELAY_MACHENISM_E2E == pstPtpPort->pstSubPortInfo->ucDelayMechanism)
    {
        pucDstMacAddr = (UCHAR *)g_szMacPTPV2_E2E;
    }
    else
    {
        pucDstMacAddr = (UCHAR *)g_szMacPTPV2_P2P;
    }

    /*获取源physical地址*/
    (VOID)TCPIP_GetEtharpMac(pstPtpPort->ulIfIndex, &ucSrcMacAddr[0]);

    /*如果注册了获取报文功能,则进行获取报文处理，对于报文发送，不关心长度*/
    stAddrInfo.ulIfIndex = pstPtpPort->ulIfIndex;
    (VOID)TCPIP_Mem_Copy((VOID*)stAddrInfo.stDstPortAddr.unAddr.ucMacAddr, 8,(VOID*)pucDstMacAddr, PTPV2_MACADDRLEN);
    (VOID)TCPIP_Mem_Copy((VOID*)stAddrInfo.stSrcPortAddr.unAddr.ucMacAddr, 8,(VOID*)ucSrcMacAddr, PTPV2_MACADDRLEN);
    stAddrInfo.stDstPortAddr.usNetworkProtocol = TCPIP_PTP_PROTOCAL_IEEE_802;
    stAddrInfo.stDstPortAddr.usAddressLength   = PTPV2_MACADDRLEN;
    stAddrInfo.stSrcPortAddr.usNetworkProtocol = TCPIP_PTP_PROTOCAL_IEEE_802;
    stAddrInfo.stSrcPortAddr.usAddressLength   = PTPV2_MACADDRLEN;

    /*Debug信息*/
    if (g_ulPtpV2GlobalDbgSwitch & TCPIP_PTP_DEBUG_OUTPUT)
    {
        PTPV2_ANN_PrintAnn((PTPV2_ANNOUNCE_MSG_S *)pstMBuf->stDataBlockDescriptor.pucData,
                           &stAddrInfo, TCPIP_PTP_PKT_OUT);
    }

    /*调用协议处理函数发送Ann报文,遍历发送*/
    (VOID)pstPtpPort->pfPtpSndAnnPktFunc(pstPtpPort, pstMBuf, &stAddrInfo);

    /*定时器Debug信息*/
    if (g_ulPtpV2GlobalDbgSwitch & TCPIP_PTP_DEBUG_TIMER)
    {
        TCPIP_InfoOutput("\r\nsnd timer timeout:");

        pstLogicTimer = (PTPV2_LOGIC_TIMER_S *)(pstPtpPort->pstSubPortInfo->ulAnnSndTimerId);

        PTPV2_TimerPrint(pstLogicTimer);
    }

    /*重置Ann发送定时器*/
    ulRet = PTPV2_ResetLogicTimer(pstPtpPort->pstSubPortInfo->ulAnnSndTimerId);

    return ulRet;
}

/*******************************************************************************
*    Func Name: PTPV2_AnnRcvTimerOut
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi61496
*  Description:  announce接收定时器处理函数
*        Input: VOID* pArg:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_AnnRcvTimerOut(VOID* pArg)
{
    PTPV2_PORT_S *pstPtpPort = NULL;
    PTPV2_FOREIGN_MASTER_S *pstForeign = NULL;
    PTPV2_FOREIGN_MASTER_S *pstSelectMaster = NULL;
    ULONG ulRet = TCPIP_PTP_OK;
    PTPV2_LOGIC_TIMER_S *pstLogicTimer = NULL;

    if (NULL == pArg)
    {
        return TCPIP_PTP_ERR_POINTER_NULL;
    }

    pstForeign = (PTPV2_FOREIGN_MASTER_S *)pArg;
    pstPtpPort = pstForeign->pstPortInfo;

    /*PTP 端口数据为空，说明系统出现异常*/
    if (NULL == pstPtpPort || NULL == pstPtpPort->pstSubPortInfo)
    {
        VOS_DBGASSERT(NULL != pstPtpPort);
        return TCPIP_PTP_ERR_SYSTEM_EXCEPTION;
    }

    /* Ann接收计数器++ */
    pstForeign->ulAnnRcvTimerCount ++;

    /*超时到达上限
      删除备用时钟源 & 马上再选一次源
    */
    if (pstForeign->ulAnnRcvTimerCount >= pstPtpPort->pstSubPortInfo->stPortAnnInfo.ucAnnRcvTimeoutNum)
    {
        /*删除备用时钟源*/
        (VOID)PTPV2_DelForeignMaster(pstForeign);

        /*重新选源*/
        (VOID)PTPV2_BMCProcess(&pstSelectMaster);

        /*选源后处理，更新参数*/
        (VOID)PTPV2_BMCNotify(pstSelectMaster);

        return TCPIP_PTP_OK;
    }

    /*定时器Debug信息*/
    if (g_ulPtpV2GlobalDbgSwitch & TCPIP_PTP_DEBUG_TIMER)
    {
        TCPIP_InfoOutput("\r\nrcv timer timeout:");

        pstLogicTimer = (PTPV2_LOGIC_TIMER_S *)(pstForeign->ulAnnRcvTimerId);

        PTPV2_TimerPrint(pstLogicTimer);
    }

    ulRet = PTPV2_ResetLogicTimer(pstForeign->ulAnnRcvTimerId);

    return ulRet;
}

/*
告警处理:
1. 在第一次启动PTP 需要创建告警定时器,定时器超时，判断是否有选中的时钟源，
   没有选中的时钟源，则上报告警
2. 选到时钟源，下发ADD ，则需要取消告警处理
3. 卸载PTPv2 模块，需要取消告警处理
*/
VOID PTPV2_WarningTimerProc(ULONG ulOperType)
{
    TCPIP_PTP_WARN_PARAM_S  stPtpWarnPara = {0};

    if (NULL != g_pfPtpV2WarnOutput && PTPV2_NO == PTPV2_HaveParent())/*没有选到源，则上报告警*/
    {
        /*上报选源失败告警*/
        stPtpWarnPara.ucWarnType = TCPIP_PTP_WARN_BMC_FAIL;
        stPtpWarnPara.ucWarnState = TCPIP_PTP_WARNING_BEGIN;

        (VOID)g_pfPtpV2WarnOutput(&stPtpWarnPara);
        g_pstPtpGlobalInfo->usWarningRecord |= TCPIP_PTP_WARN_BMC_FAIL_FLAG;
    }

    /*一次性告警定时器，超时后即删除，Id清零*/
    g_ulPtpWarningTimerId = 0;

    return;
}

ULONG PTPV2_CreateWarningTimer()
{
    if (0 != g_ulPtpWarningTimerId)
    {
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_2813, TCPIP_LOG_LEVEL_CRITICAL, LOG_TYPE_RUN,
            "TCPIP PTPV2 LOG: PTPV2_CreateWarningTimer  warning timer id = %#x exist.\r\n",
            g_ulPtpWarningTimerId, 0, 0, 0);
    }

    /*一次性定时器，30秒判断当前有没有源，没有源上报告警，有源，不作处理*/
    if (TCPIP_PTP_OK != VOS_Timer_Create(g_ulPtpV2TaskId,
                                         g_ulPtpV2TimerQId,
                                         PTPV2_WANRING_TIMER_INTERVAL,
                                         (VOID  (*)(VOID*))PTPV2_WarningTimerProc,
                                         (VOID*)0,
                                         &g_ulPtpWarningTimerId,
                                         VOS_TIMER_NOLOOP))
    {

        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_2814, TCPIP_LOG_LEVEL_CRITICAL,
            LOG_TYPE_RUN, "TCPIP PTPV2 LOG: PTPV2_CreateWarningTimer Create warning timer failed.\r\n",
            0, 0, 0, 0);

        return TCPIP_PTP_ERR_CREATE_TIMER;
    }

    return TCPIP_PTP_OK;
}

ULONG PTPV2_DeleteWarningTimer()
{
   if (0 != g_ulPtpWarningTimerId)
   {
        (VOID)VOS_Timer_Delete(g_ulPtpWarningTimerId);
        g_ulPtpWarningTimerId = 0;
   }

   return TCPIP_PTP_OK;
}

/******************************************************************************
*Func Name   : PTPV2_TimerPrint
*Description : 定时器信息打印接口
*Input       : PTPV2_LOGIC_TIMER_S *pstLogicTimer 
*Output      : 
*Return      : 
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2014-05-14           dutianyi       Create
*******************************************************************************/
VOID PTPV2_TimerPrint(PTPV2_LOGIC_TIMER_S *pstLogicTimer)
{
    CHAR szBuf[LEN_512] = {0};      /* 缓冲区长度512个字节，存放报文信息 */
    INT32 i32Offset = 0;

    if (NULL == pstLogicTimer)
    {
        return;
    }

    i32Offset = TCPIP_SNPRINTF0(szBuf, LEN_512, P8("\r\n %30s : %#x \r\n %30s : %u \r\n %30s : %u \r\n %30s : %u", 
                             "TimerId", pstLogicTimer->ulTimerId,
                             "Period", pstLogicTimer->ulPeriod,
                             "EndTimeHigh", pstLogicTimer->ulEndTimeHigh,
                             "EndTimeLow", pstLogicTimer->ulEndTimeLow));

    (VOID)TCPIP_SNPRINTF(szBuf + i32Offset, LEN_512 - i32Offset, 
                                P4("\r\n %30s : %#x \r\n %30s : %u \r\n",
                                "Func", pstLogicTimer->pfFunc,
                                "DelFlag", pstLogicTimer->ulDelFlag));

    TCPIP_InfoOutput(szBuf);

    return;
}

#ifdef __cplusplus
}
#endif   /* end of __cplusplus */

