/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              pppmux_func.h
*
*  Project Code: VISPV100R005
*   Module Name: PPPMUX
*  Date Created: 2006-5-11
*        Author: ZhouTong(43740)
*   Description: PPPMUX函数声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-5-11  ZhouTong(43740)   Create
*
*******************************************************************************/
#ifndef _PPPMUX_FUNC_H_
#define _PPPMUX_FUNC_H_

#ifdef  __cplusplus
extern "C"{
#endif

ULONG PPPMUX_Init_Com(const COM_ID_INFO_S *pstComInfo, ULONG ulComLen);
ULONG PPPMUX_Active_Com(VOID);
ULONG PPPMUX_SetModuleInfo(PPPMUX_MOD_INFO_S *pstMInfo);
ULONG PPPMUX_RegShellApi(PPPMUX_SHELL_CALLBACK_S *pstShellApi);
ULONG PPPMUX_InitData(VOID);

ULONG PPPMUX_ProcessMux(ULONG ulIfIndex, ULONG ulSetYes);
ULONG PPPMUX_ProcessDefaultPid(ULONG ulIfIndex, USHORT usDefaultPid, ULONG ulReset);
/*Added by luogaowei, for pppmux最大子帧长度扩展, 2013/3/5 */
ULONG PPPMUX_ProcessSubFrameLenEx(ULONG ulIfIndex, ULONG ulSubFrameLen);
ULONG PPPMUX_ProcessSubFrameLen(ULONG ulIfIndex,ULONG ulSubFrameLen);
ULONG PPPMUX_ProcessFrameLen(ULONG ulIfIndex,ULONG ulFrameLen);
ULONG PPPMUX_ProcessSubFrameCount(ULONG ulIfIndex,ULONG ulSubFrameCount);
ULONG PPPMUX_ProcessMuxDelay(ULONG ulIfIndex,ULONG ulDelay);
ULONG PPPMUX_ProcessMuxConfig(ULONG ulIfIndex,PPPMUXCONFIG_S* pstMuxConfig);
ULONG PPPMUX_ProcessNegoResult(ULONG ulIfIndex, PPP_MUXCP_NEGORESULT_S *pstOur, 
                               PPP_MUXCP_NEGORESULT_S *pstHis);
ULONG PPPMUX_ProcessMuxStat(ULONG ulIfIndex,PPPMUXSTATS_S* pstMuxStat);
ULONG PPPMUX_ProcessClearStat(ULONG ulIfIndex);

ULONG PPPMUX_ProcessMux_PT(ULONG ulIfIndex, ULONG ulSetYes);
ULONG PPPMUX_ProcessDefaultPid_PT(ULONG ulIfIndex, USHORT usDefaultPid, ULONG ulReset);
ULONG PPPMUX_ProcessSubFrameLen_PT(ULONG ulIfIndex,ULONG ulSubFrameLen);
/*Added by luogaowei, for pppmux最大子帧长度扩展, 2013/3/5 */
ULONG PPPMUX_ProcessSubFrameLenEx_PT(ULONG ulIfIndex, ULONG ulSubFrameLen);
ULONG PPPMUX_ProcessFrameLen_PT(ULONG ulIfIndex,ULONG ulFrameLen);
ULONG PPPMUX_ProcessSubFrameCount_PT(ULONG ulIfIndex,ULONG ulSubFrameCount);
ULONG PPPMUX_ProcessMuxDelay_PT(ULONG ulIfIndex,ULONG ulDelay);
ULONG PPPMUX_UpdateConfigInfo(ULONG ulIfIndex);

ULONG PPPMUX_ProcessMuxConfig_PT(ULONG ulIfIndex,PPPMUXCONFIG_S* pstMuxConfig);
ULONG PPPMUX_ProcessNegoResult_PT(ULONG ulIfIndex, PPP_MUXCP_NEGORESULT_S *pstOur, 
                               PPP_MUXCP_NEGORESULT_S *pstHis);
ULONG PPPMUX_ProcessMuxStat_PT(ULONG ulIfIndex,PPPMUXSTATS_S* pstMuxStat);
ULONG PPPMUX_ProcessClearStat_PT(ULONG ulIfIndex);

ULONG PPPMUX_Multiplexing(PPPINFO_S* pstPppInfo,MBUF_S* pstMBuf,USHORT usProtocol);
ULONG PPPMUX_Input(MBUF_S* pstMBuf);
ULONG PPPMUX_DropPacket( MBUF_S *pstMbuf, ULONG ulCmd, CHAR *pcData );
ULONG PPPMUX_GetMuxHeader (UCHAR* pszPacket,UCHAR* pucPFF,UCHAR* pucLXT,USHORT* pusSubFrameLen);
ULONG PPPMUX_DeMultiplexing(PPPINFO_S *pstPppInfo, MBUF_S *pstMBuf);
ULONG PPPMUX_SendSinglePacket(PPPINFO_S *pstPppInfo,MBUF_S *pstMBuf,USHORT usProtocol);

ULONG PPPMUX_Timer_Create(VOID (*pfTimerFunc)(VOID *), VOID *pArg);
ULONG PPPMUX_Timer_Delete(VOID);
VOID  PPPMUX_Timer_Out(VOID *pArg);
VOID  PPPMUX_Schedule(UINTPTR ulArg0, UINTPTR ulArg1,UINTPTR ulArg2,UINTPTR ulArg3);

VOID  PPPMUX_ScanAndSendPacket(VOID);
/*f47854 modify : 函数参数或者返回值类型与函数指针定义不匹配*/
VOID* PPPMUX_GetNextPppInfo(VOID *pParam,VOID **pNewParam);
ULONG PPPMUX_OpenPPPEntry(UINTPTR *pulWaitListHandle);
ULONG PPPMUX_GetPPPEntry(UINTPTR ulEntryWaitList, PPPINFO_S** pstPppInfo);
ULONG PPPMUX_ClosePPPEntry(UINTPTR ulWaitListHandle);
ULONG PPP_HA_ProcessMUXCPUP (PPPINFO_S *pstPppInfo);
VOID PPP_HA_ProcessMUXCDown(PPPINFO_S *pstPppInfo);
ULONG PPPMUX_isValidPid(ULONG ulPid);

/* 统计发送信息 */
#define PPPMUX_FLOW_STAT_SEND(pstMuxStat,usSubFrameCount,usFrameLen,usPayLoadLen) \
{\
    (pstMuxStat)->ulSendPackets++;\
    (pstMuxStat)->ulSendSubFrames += usSubFrameCount;\
    (pstMuxStat)->ulSendBytes += usFrameLen;\
    (pstMuxStat)->ulSendBytes_PayLoad += usPayLoadLen;\
}

/* 统计接收信息 */
#define PPPMUX_FLOW_STAT_RECV(pstMuxStat,ulSubFrameCount,ulFrameLen,ulPayLoadLen) \
{\
    (pstMuxStat)->ulRecvPackets++;\
    (pstMuxStat)->ulRecvSubFrames += ulSubFrameCount;\
    (pstMuxStat)->ulRecvBytes += ulFrameLen;\
    (pstMuxStat)->ulRecvBytes_PayLoad += ulPayLoadLen;\
}

#ifdef  __cplusplus
}
#endif

#endif  /* end of _PPPMUX_FUNC_H_ */
