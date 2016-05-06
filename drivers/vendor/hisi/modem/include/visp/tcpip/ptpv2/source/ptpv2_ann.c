/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptp_ann.c
*
*  Project Code: IPCLOCK SERVER V100R002
*   Module Name: PTP Ann
*  Date Created: 2008-06-02
*        Author: 谭强
*   Description: Announce消息接收和发送处理
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-06-02      谭强                  Create
*
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "tcpip/ptpv2/include/ptpv2_ext.h"

#include "tcpip/ptpv2/include/ptpv2_pkt.h"
#include "tcpip/ptpv2/include/ptpv2_func.h"
#include "tcpip/ptpv2/include/ptpv2_bmc.h"
#include "tcpip/ptpv2/include/ptpv2_common.h"
#include "tcpip/public/tcpip_basefun.h"

/*******************************************************************************
*    Func Name: PTPV2_Ann_RcvMsg
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi61496
*  Description:
*        Input: UCHAR* pucBuffer:
*               ULONG ulPacketLen:
*               TCPIP_PTP_ADDRINFO_S* pstAddrInfo:
*               PTPV2_PORT_S *pstPortInfo:
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
ULONG PTPV2_Ann_RcvMsg (UCHAR* pucBuffer, ULONG ulPacketLen, 
                                  TCPIP_PTP_ADDRINFO_S* pstAddrInfo, PTPV2_PORT_S *pstPortInfo)
{
    ULONG ulRet = TCPIP_PTP_OK;
    PTPV2_ANNOUNCE_MSG_S* pstAnnMsg = NULL;
    PTPV2_FOREIGN_MASTER_S* pstSelectMaster = NULL;
    ULONG ulPtpV2ClockType = 0;

    VOS_DBGASSERT(NULL != pucBuffer);
    VOS_DBGASSERT(NULL != pstAddrInfo);

    /*全局报文统计*/
    g_stGlobalPtpV2PktStat.ulRcvAnnPackets ++;
    /*端口报文统计*/
    pstPortInfo->stPacketStat.ulRcvAnnPackets ++;

    pstAnnMsg = (PTPV2_ANNOUNCE_MSG_S*) pucBuffer;

    ulPtpV2ClockType = PTPV2_GetClockType();

    /*
      是否可以处理ann报文
      条件:1、端口必须有效   && 2、启动已经start &&  3、不能是OC master
    */
    if (NULL == pstPortInfo->pstSubPortInfo || PTPV2_NO == pstPortInfo->pstSubPortInfo->ucWorkState
        || (PTPV2_CLOCK_TYPE_OC == ulPtpV2ClockType
            && TCPIP_PTP_PORT_ROLE_MASTER == pstPortInfo->pstSubPortInfo->ucPtpPortRole))
    {
        ulRet =  TCPIP_PTP_ERR_NO_START;

        goto EXIT_LABEL;
    }

    /*模式是否匹配*/
    ulRet =  PTPV2_PktWithCastModeMatch(pstPortInfo, pstAddrInfo);
    if (TCPIP_PTP_OK != ulRet)
    {
        goto EXIT_LABEL;
    }
        
    /*announce报文的正确性检查*/
    ulRet = PTPV2_PktHeaderCheck(pstPortInfo,
                               pucBuffer,
                               TCPIP_PTP_MSG_ANNOUNCE,
                               ulPacketLen,
                               pstAddrInfo);
    if (TCPIP_PTP_OK != ulRet)
    {
        goto EXIT_LABEL;
    }

    /*If the stepsRemoved field of S is 255 or greater, S shall not be qualified.*/
    if (PTPV2_MAX_STEPSREMOVED <= VOS_NTOHS(pstAnnMsg->usStepsRemoved))
    {
        ulRet = TCPIP_PTP_ERR_STEPSREMOVED;
        goto EXIT_LABEL;
    }

    ulRet = PTPV2_GrandMasterIDCheck(pstAnnMsg);
    if (TCPIP_PTP_OK != ulRet)
    {
        goto EXIT_LABEL;
    }

    /*BMC 预处理:添加新的时钟源或者更新旧的*/ /*创建forgein  matser*/
    ulRet = PTPV2_BMCPreProcess(pstPortInfo, pstAnnMsg, pstAddrInfo);
    if (TCPIP_PTP_OK != ulRet)
    {
        goto EXIT_LABEL;
    }

    /*选源处理*/
    (VOID)PTPV2_BMCProcess(&pstSelectMaster);

    /*选源后处理，更新参数*/
    (VOID)PTPV2_BMCNotify(pstSelectMaster);

EXIT_LABEL:
    if (TCPIP_PTP_OK != ulRet)
    {
        /*丢包并统计*/
        g_stGlobalPtpV2PktStat.ulRcvErrorForeMasterPackets ++;
        pstPortInfo->stPacketStat.ulRcvErrorForeMasterPackets ++;
    }

    return ulRet;
}


ULONG PTPV2_BC_MasterBuildAnnPkt(VOID* pThis, VOID** ppData)
{
    ULONG ulRet = TCPIP_PTP_OK;
    USHORT usAnnPktLen = LEN_64;
    PTPV2_PORT_S* pstPtpPort = NULL;
    MBUF_S* pstSndBuf = NULL;
    PTPV2_ANNOUNCE_MSG_S* pstAnnMsg = NULL;
    PTPV2_FOREIGN_MASTER_S *pstVirutalD0 = g_pstVirtualD0;

    pstPtpPort = (PTPV2_PORT_S*)pThis;
    VOS_DBGASSERT(NULL != pstPtpPort);

    /*只允许端口为MASTER角色可发报文,AR-IP-PTP.002*/
    if (pstPtpPort->pstSubPortInfo->ucPtpPortRole != TCPIP_PTP_PORT_ROLE_MASTER)
    {        
        return TCPIP_PTP_ERR;
    }    

    /*构造announce报文*/
    pstSndBuf = (MBUF_S*)MBUF_CreateForControlPacket(LEN_128, sizeof(PTPV2_ANNOUNCE_MSG_S),
                MBUF_TYPE_DATA, PTPV2_MID);
    if (NULL == pstSndBuf)
    {
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_2816, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
                "TCPIP PTPV2 LOG: PTPV2_BC_MasterBuildAnnPkt fail to create mbuf!\r\n",
                0, 0, 0, 0);
        
        return TCPIP_PTP_ERR;
    }

    pstAnnMsg = MBUF_MTOD(pstSndBuf, PTPV2_ANNOUNCE_MSG_S*);

    /*Add by heyijun 00218462 for DTS2014080807614, 目标清零, 2014-8-14*/
    (VOID)TCPIP_Mem_Set((CHAR *)pstAnnMsg, 0, sizeof(PTPV2_ANNOUNCE_MSG_S)); 

    ulRet = PTPV2_BuildAnnPktHeader(pstPtpPort, &(pstAnnMsg->stMsgHeader));
    if (TCPIP_PTP_OK != ulRet)
    {
        /*报文统计*/
        g_stGlobalPtpV2PktStat.ulSndBuildDropPackets ++;
        pstPtpPort->stPacketStat.ulSndBuildDropPackets ++;
        
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_2817, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
                "TCPIP PTPV2 LOG: PTPV2_BC_MasterBuildAnnPkt fail to build ann header! Ret = %u!\r\n",
                ulRet, 0, 0, 0);
        MBUF_Destroy(pstSndBuf);
        return ulRet;
    }

    pstAnnMsg->stMsgHeader.usmessageLength = VOS_HTONS(usAnnPktLen);

    /*存在源Ebest时,utc/优先级/stepRemoved/timesource/GMid都从源获取,否则从VirtualD0获取*/
    if (PTPV2_YES == PTPV2_HaveParent())
    {
        pstAnnMsg->sCurrentUtcOffset = VOS_HTONS(g_pstPtpGlobalInfo->stParentDs.sCurrentUtcOffset);
        pstAnnMsg->ucGrandmasterPriority1 = g_pstPtpGlobalInfo->stParentDs.ucGrandmasterPriority1;
        pstAnnMsg->ucGrandmasterPriority2 = g_pstPtpGlobalInfo->stParentDs.ucGrandmasterPriority2;
        pstAnnMsg->usStepsRemoved = VOS_HTONS(g_pstPtpGlobalInfo->stParentDs.usStepsRemoved + 1);
        pstAnnMsg->ucTimeSource = g_pstPtpGlobalInfo->stParentDs.ucTimeSource;
        (VOID)TCPIP_Mem_Copy((VOID*)(pstAnnMsg->stGrandmasterIdentity), TCPIP_PTP_CLOCK_ID_LEN,
                           (VOID*)(g_pstPtpGlobalInfo->stParentDs.szGrandMasterId), TCPIP_PTP_CLOCK_ID_LEN);

        if (0xFE != g_pstPtpGlobalInfo->stCfgDefaultDs.stCfgClockQa.ucClockAccuracy)
        {   
            /*选到源,且有配置到visp,则取本地配置的时钟质量*/
            (VOID)PTPV2_BuildAnnPktClockQa(pstAnnMsg,&(g_pstPtpGlobalInfo->stCfgDefaultDs.stCfgClockQa));
        }
        else
        {
            /*选到源,没有配置到visp,则取选源的时钟质量*/
            (VOID)PTPV2_BuildAnnPktClockQa(pstAnnMsg,&(g_pstPtpGlobalInfo->stParentDs.stParentClockQA));
        }
    }
    else if (NULL != pstVirutalD0)
    {
        /*没有选到源,按D0值构包*/
        pstAnnMsg->sCurrentUtcOffset = VOS_HTONS(pstVirutalD0->sCurrentUtcOffset);
        pstAnnMsg->ucGrandmasterPriority1 = pstVirutalD0->ucGrandmasterPriority1;
        pstAnnMsg->ucGrandmasterPriority2 = pstVirutalD0->ucGrandmasterPriority2;
        pstAnnMsg->usStepsRemoved = VOS_HTONS(pstVirutalD0->usStepsRemoved + 1);
        pstAnnMsg->ucTimeSource = pstVirutalD0->ucTimeSource;
        (VOID)TCPIP_Mem_Copy((VOID*)(pstAnnMsg->stGrandmasterIdentity), TCPIP_PTP_CLOCK_ID_LEN,
                           (VOID*)&(pstVirutalD0->szForeignMasterPortId), TCPIP_PTP_CLOCK_ID_LEN);

        /*没有选到源,或者选到源却没有配置到visp,则取D0的时钟质量*/
        (VOID)PTPV2_BuildAnnPktClockQa(pstAnnMsg,&(pstVirutalD0->stGrandmasterClockQuality));
    }

    *ppData = pstSndBuf;
    return ulRet;

}

ULONG PTPV2_OC_MasterBuildAnnPkt(VOID* pThis, VOID** ppData)
{
    ULONG ulRet = TCPIP_PTP_OK;
    USHORT usAnnPktLen = LEN_64;
    PTPV2_PORT_S* pstPtpPort = NULL;
    MBUF_S* pstSndBuf = NULL;
    PTPV2_ANNOUNCE_MSG_S* pstAnnMsg = NULL;

    pstPtpPort = (PTPV2_PORT_S*)pThis;
    VOS_DBGASSERT(NULL != pstPtpPort);
 
    /*OC master要自行构造announce报文*/
    pstSndBuf = (MBUF_S*)MBUF_CreateForControlPacket(LEN_128, sizeof(PTPV2_ANNOUNCE_MSG_S),
                MBUF_TYPE_DATA, PTPV2_MID);
    if (NULL == pstSndBuf)
    {
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_2818, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
                "TCPIP PTPV2 LOG: PTPV2_OC_MasterBuildAnnPkt!\r\n",
                0, 0, 0, 0);
        return TCPIP_PTP_ERR;
    }

    pstAnnMsg = MBUF_MTOD(pstSndBuf, PTPV2_ANNOUNCE_MSG_S*);

    /*Add by heyijun 00218462 for DTS2014080807614, 目标清零, 2014-8-14*/
    (VOID)TCPIP_Mem_Set((CHAR *)pstAnnMsg, 0, sizeof(PTPV2_ANNOUNCE_MSG_S)); 

    ulRet = PTPV2_BuildAnnPktHeader(pstPtpPort, &(pstAnnMsg->stMsgHeader));
    if (TCPIP_PTP_OK != ulRet)
    {
        /*报文统计*/
        g_stGlobalPtpV2PktStat.ulSndBuildDropPackets ++;
        pstPtpPort->stPacketStat.ulSndBuildDropPackets ++;
        
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_2819, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
                "TCPIP PTPV2 LOG: PTPV2_OC_MasterBuildAnnPkt fail to build ann header! Ret = %u!\r\n",
                ulRet, 0, 0, 0);
        /*丢包*/
        MBUF_Destroy(pstSndBuf);
        return ulRet;
    }

    pstAnnMsg->stMsgHeader.usmessageLength = VOS_HTONS(usAnnPktLen);

    if (BOOL_TRUE == g_pstPtpGlobalInfo->stCfgDefaultDs.bCurrentUtcOffsetValid)
    {
        pstAnnMsg->sCurrentUtcOffset = VOS_HTONS(g_pstPtpGlobalInfo->stCfgDefaultDs.sCurrentUtcOffset);
    }
    else
    {
        pstAnnMsg->sCurrentUtcOffset = 0; /*utc 无效，则值为0*/
    }

    pstAnnMsg->ucGrandmasterPriority1 = g_pstPtpGlobalInfo->stCfgDefaultDs.ucPriority1;
    pstAnnMsg->ucGrandmasterPriority2 = g_pstPtpGlobalInfo->stCfgDefaultDs.ucPriority2;
    /*时钟质量以本端配置为准*/
    (VOID)PTPV2_BuildAnnPktClockQa(pstAnnMsg,&(g_pstPtpGlobalInfo->stCfgDefaultDs.stCfgClockQa));

    (VOID)TCPIP_Mem_Copy((VOID*)(pstAnnMsg->stGrandmasterIdentity), TCPIP_PTP_CLOCK_ID_LEN,(VOID*)(g_pstPtpGlobalInfo->szClockId), TCPIP_PTP_CLOCK_ID_LEN);
    pstAnnMsg->usStepsRemoved = VOS_HTONS(g_pstPtpGlobalInfo->usStepsRemoved);
    pstAnnMsg->ucTimeSource =  g_pstPtpGlobalInfo->ucTimeSource;

    *ppData = pstSndBuf;
    return ulRet;
}

/******************************************************************************
*Func Name   : PTPV2_ANN_PrintAnn
*Description : announce报文打印接口
*Input       : PTPV2_ANNOUNCE_MSG_S *pstAnnMsg: 消息头
*              TCPIP_PTP_ADDRINFO_S *pstAddrInfo:  接收/发送报文的地址以及UDP信息
*              ULONG ulFlag:        标记:0-发送报文;非0-接收报文
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
VOID PTPV2_ANN_PrintAnn(PTPV2_ANNOUNCE_MSG_S *pstAnnMsg, TCPIP_PTP_ADDRINFO_S *pstAddrInfo, ULONG ulFlag)
{    
    CHAR szBuf[LEN_512] = {0};  /* 缓冲区长度512个字节，存放报文信息 */
    CHAR szInOrOut[10] = {0};
    INT32 i32Offset = 0;
    
    if ((NULL == pstAnnMsg) || (NULL == pstAddrInfo))
    {
        return;
    }
    
    if (0 == ulFlag)
    {
        i32Offset = TCPIP_SNPRINTF0(szInOrOut, 10, P0("send"));
    }
    else
    {
        i32Offset = TCPIP_SNPRINTF0(szInOrOut, 10, P0("receive"));
    }
    
    /* 先打印提示信息 */
    (VOID)TCPIP_SNPRINTF(szBuf + i32Offset, LEN_512 - i32Offset, P1("\r\n----------announce msg %s begin----------",szInOrOut));
    
    TCPIP_InfoOutput(szBuf);

    (VOID)TCPIP_Mem_Set(szBuf, 0, LEN_512);
    
    /* 打印消息头 */
    PTPV2_PrintHeader((PTPV2_MSGHEADER_S *)pstAnnMsg, pstAddrInfo);
    
    i32Offset = TCPIP_SNPRINTF0(szBuf, LEN_512, P0("\r\nANNOUNCE INFO:"));    

    /* 打印announce消息的其他内容 */
    i32Offset += TCPIP_SNPRINTF(szBuf + i32Offset, LEN_512 - i32Offset, P8("\r\n    originTimestamp : Nano-%u,Low-%u,High-%u \r\n    utcoffset : %d\r\n    grandmasterPri1 : %u\r\n    grandmasterQuality : Accuracy-%u,class-%u,offset-%u ",
                              pstAnnMsg->stOriginTimestamp.ulNanoseconds,
                              pstAnnMsg->stOriginTimestamp.ulSecondsLow,
                              pstAnnMsg->stOriginTimestamp.usSecondsHigh,
                              VOS_NTOHS(pstAnnMsg->sCurrentUtcOffset),
                              pstAnnMsg->ucGrandmasterPriority1,
                              pstAnnMsg->stGrandmasterClockQuality.ucClockAccuracy,
                              pstAnnMsg->stGrandmasterClockQuality.ucClockClass,
                              VOS_NTOHS(pstAnnMsg->stGrandmasterClockQuality.usOffsetScaledLogVariance)));

    i32Offset += TCPIP_SNPRINTF(szBuf + i32Offset, LEN_512 - i32Offset, P11("\r\n    grandmasterPri2 : %u\r\n    grandmasterId : %02x%02x%02x%02x%02x%02x%02x%02x\r\n    stepsremoved : %u\r\n    timesource : %u",
                              pstAnnMsg->ucGrandmasterPriority2,
                              pstAnnMsg->stGrandmasterIdentity[0],
                              pstAnnMsg->stGrandmasterIdentity[1],
                              pstAnnMsg->stGrandmasterIdentity[2],
                              pstAnnMsg->stGrandmasterIdentity[3],
                              pstAnnMsg->stGrandmasterIdentity[4],
                              pstAnnMsg->stGrandmasterIdentity[5],
                              pstAnnMsg->stGrandmasterIdentity[6],
                              pstAnnMsg->stGrandmasterIdentity[7],
                              VOS_NTOHS(pstAnnMsg->usStepsRemoved),
                              pstAnnMsg->ucTimeSource));
    (VOID)TCPIP_SNPRINTF(szBuf + i32Offset, LEN_512 - i32Offset, P1("\r\n----------announce msg %s end------------",szInOrOut));

    TCPIP_InfoOutput(szBuf);
    
}

#ifdef __cplusplus
}
#endif
