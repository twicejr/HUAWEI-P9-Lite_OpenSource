/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ipppmux.h
*
*  Project Code: VISPV100R005
*   Module Name: PPPMUX
*  Date Created: 2006-5-11
*        Author: ZhouTong(43740)
*   Description: Defines All interface of the PPPMUX Component
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-5-11  ZhouTong(43740)   Create
*
*******************************************************************************/

#ifndef _IPPPMUX_H_
#define _IPPPMUX_H_

#ifdef __cplusplus
extern "C" {
#endif


DECLARE_INTERFACE (IIF_PPPMUX_ComIntFUN)
{
    IUNKNOWN_METHODS
        
    METHOD_(VOID, pfPPP_MUXCP_Init)(PPPINFO_S* pstPppInfo);
    METHOD_(VOID, pfPPP_MUXCP_ReceiveEventFromCore)(VOID *pstMuxcpInfo, ULONG ulCmd, char *pPara);
    METHOD_(VOID, pfPPP_MUXCP_ReceivePacket)(VOID *pstMuxcpInfo, UCHAR *pucHead, UCHAR *pucPacket, ULONG ulLen);

    METHOD_(ULONG, pfPPPMUX_Multiplexing)(PPPINFO_S* pstPppInfo,MBUF_S* pstMBuf,USHORT usProtocol);
    METHOD_(VOID,  pfPPPMUX_ScanAndSendPacket)(VOID);
    METHOD_(ULONG, pfPPPMUX_Input)(MBUF_S *pstMBuf);
    METHOD_(ULONG, pfPPP_HA_ProcessMUXCPUP)(PPPINFO_S *pstPppInfo);
    METHOD_(VOID, pfPPP_HA_ProcessMUXCDown)(PPPINFO_S *pstPppInfo);
};

DECLARE_INTERFACE (IIF_PPPMUX_ComIntCFG)
{
    IUNKNOWN_METHODS

    METHOD_(ULONG, pfPPPMUX_Init_Com)(const COM_ID_INFO_S * pstComInfo, ULONG ulComLen);
    METHOD_(ULONG, pfPPPMUX_Active_Com)(VOID);
    METHOD_(ULONG, pfPPPMUX_SetModuleInfo)(PPPMUX_MOD_INFO_S * pstMInfo);
    METHOD_(ULONG, pfPPPMUX_RegShellApi)(PPPMUX_SHELL_CALLBACK_S * pstShellApi);
    
    METHOD_(ULONG, pfPPPMUX_ProcessMux)(ULONG ulIfIndex, ULONG ulSetYes);
    METHOD_(ULONG, pfPPPMUX_ProcessDefaultPid)(ULONG ulIfIndex, USHORT usDefaultPid, ULONG ulReset);
    METHOD_(ULONG, pfPPPMUX_ProcessSubFrameLen)(ULONG ulIfIndex, ULONG ulSubFrameLen);
    METHOD_(ULONG, pfPPPMUX_ProcessSubFrameLenEx)(ULONG ulIfIndex, ULONG ulSubFrameLen);
    METHOD_(ULONG, pfPPPMUX_ProcessFrameLen)(ULONG ulIfIndex, ULONG ulFrameLen);
    METHOD_(ULONG, pfPPPMUX_ProcessSubFrameCount)(ULONG ulIfIndex, ULONG ulSubFrameCount);
    METHOD_(ULONG, pfPPPMUX_ProcessMuxDelay)(ULONG ulIfIndex, ULONG ulDelay);
    METHOD_(ULONG, pfPPPMUX_ProcessMuxConfig)(ULONG ulIfIndex, PPPMUXCONFIG_S * pstMuxConfig);
    METHOD_(ULONG, pfPPPMUX_ProcessNegoResult)(ULONG ulIfIndex, 
                                               PPP_MUXCP_NEGORESULT_S *pstOur, 
                                               PPP_MUXCP_NEGORESULT_S *pstHis);
    METHOD_(ULONG, pfPPPMUX_ProcessMuxStat)(ULONG ulIfIndex, PPPMUXSTATS_S* pstMuxStat);
    METHOD_(ULONG, pfPPPMUX_ProcessClearStat)(ULONG ulIfIndex);
};
 

DECLARE_INTERFACE (IIF_PPPMUX_ComIntSSA)
{
    IUNKNOWN_METHODS
};

typedef struct tagMUXCP_IntObj
{
    struct IIF_PPPMUX_ComIntFUN    *pCompIntFUN;
    struct IIF_PPPMUX_ComIntCFG    *pCompIntCFG;
    struct IIF_PPPMUX_ComIntSSA    *pCompIntSSA;
}MUXCP_INT_OBJ_S;

#ifdef __cplusplus
}
#endif
#endif
