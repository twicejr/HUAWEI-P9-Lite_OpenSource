/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcp_cmd.h
*
*  Project Code: VISP1.5
*   Module Name: IP TCP4  
*  Date Created: 2004-05-04
*        Author: w25705
*   Description: 定义TCP4组件配置相关的结构和宏
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2004-05-04  w25705           Create the first version.
*  2006-05-11  luyao           为支持ARM CPU字节对齐特性，修改结构。
*
*******************************************************************************/

#ifndef _tcp_cmd_h_
#define _tcp_cmd_h_


#ifdef __cplusplus
extern "C"{
#endif

#include "tcpip/tcp4/include/tcp_api.h"

typedef    struct
{
    ULONG ulTaskId;
    ULONG ulSocketId;
    
    ULONG ulState;
    ULONG ulLocalAddress;
    ULONG ulLocalPort;
    ULONG ulForeignAddress;
    ULONG ulForeignPort;
    
    ULONG ulISSSeq;
    ULONG ulSndUnackSeq;
    ULONG ulSndNxtSeq;
    ULONG ulSndWnd;
    ULONG ulSndMaxSeq;
    ULONG ulInitRcvSeq;
    ULONG ulRcvNxtSeq;
    ULONG ulRcvWnd;

    ULONG ulEstabtriggers;
    ULONG ulEstabtimeouts;
    ULONG ulRetranstriggers;
    ULONG ulRetranstimeouts;
    ULONG ulAckHoldtriggers;
    ULONG ulAckHoldtimeouts;
    ULONG ulPersisttriggers;
    ULONG ulPersisttimeouts;
    ULONG ulKeepAlivetriggers;
    ULONG ulKeepAlivetimeouts;
    ULONG ulFinWait2triggers;
    ULONG ulFinWait2timeouts;
    ULONG ulTimeWaittriggers;
    ULONG ulTimeWaittimeouts;
    
    ULONG ulRcvMSS;
    ULONG ulSndMSS;
    ULONG ulMaxSeg;
    ULONG ulSRTT;
    ULONG ulRTTO;
    ULONG ulMinRTT;
    ULONG ulRTTV;
    
    ULONG ulRcvTotal;
    ULONG ulRcvDataByte;
    ULONG ulRcvDataPacket;
    ULONG ulRcvOutOrderPacket;
    ULONG ulRcvMaxDataByte;
    ULONG ulRcvMinDataByte;
    ULONG ulSndTotal;
    ULONG ulSndErr;
    
    ULONG ulSndRetran;
    ULONG ulSndDataPacket;
    ULONG ulSndDataByte;        

    /* Backup info */
    ULONG   ulRcvNxtLastBackup;
    ULONG   ulRcvLastBackup;
    USHORT  usRoutineBackupTime;
    USHORT  usRoutineTimeout;
    ULONG   ulSndBufCutLen;
    ULONG   ulSeqRcvNxtRevised;
} TCPCB_INFO_S;

typedef struct 
{
    ULONG ulTCPCB;
    ULONG ulLocalAddr;
    ULONG ulLocalPort;
    ULONG ulForeignAddr;
    ULONG ulForeignPort;
    ULONG ulTCPCBState;
    ULONG ulHasMD5;
        
    VOID *pInPcbHandle;
    
}INPCB_INFO_S;

typedef struct tagTCPMIBCONN
{
    ULONG  ulLAddr;
    USHORT usLPort;
    UCHAR  ucPadding_1[2];
    ULONG  ulFAddr;
    USHORT usFPort;
    SHORT  sState;
} TCPMIBCONN_S;

/**********************************************************************/
/*TCP debug packet or transaction                                     *
 **********************************************************************/
/* used for output debug information. added by lilixiang */
#define TCP_DEBUG_OUT_GENERAL   0

#define TCP_DEBUG_MD5_FAIL  0x0101
#define TCP_DEBUG_MD5_OUTPUT 0x0102
#define TCP_DEBUG_MD5_SYSLOG 0x0103
#define TCP_DEBUG_MD5_SUCC  0x0104
/* end tcp debug output group. by lilixiang */

/* TCP收到错误报文时，用来填充调试函数的状态参数 TCP_DbugPkt() */
#define TCP_ERRORPACKET      99

#define TCP_FILT_PERMIT     0
#define TCP_FILT_DENY       1

#define TCP_SOCKID_ANY (FILENUM + 1)
#define TCP_TASKID_ANY 0xFFFFFFFF

/*shell service callback function*/
typedef struct tagIP4_TCP4_SH_CALLBACUP_SET
{
    
    VOID (*pfIP4_TCP4_DbugPkt)(CHAR *pPreStr,SHORT sTcpState,TCPIPHDR_S *pHeader);
    VOID (*pfIP4_TCP_MD5Debug)(CHAR * pszIpTcpHead,ULONG ulIpTcpLen, CHAR * pszTcpData,
                                ULONG ulTcpDataLen, CHAR * pszPassWord,ULONG ulPassLen,ULONG ulInOrOut);
    VOID (*pfIP4_TCP4_SH_SendInfo2IC)(ULONG ulInfoId,CHAR *pszInfo);
    VOID (*pfTCP_MD5AuthenFailTrap)(
        ULONG ulTcpConnEntry_tcpConnLocalAddress,
        ULONG ulTcpConnEntry_tcpConnLocalPort,
        ULONG ulTcpConnEntry_tcpConnRemAddress,
        ULONG ulTcpConnEntry_tcpConnRemPort,
        ULONG ulVrfIndex);
}IP4_TCP4_SH_CALLBACUP_SET_S; 

ULONG  TCP_ClassifyDbugFilt(TCPDBUGFILTRD_S *pstDbugFiltRd, ULONG ulTaskId, ULONG ulSockId);
        
#ifdef __cplusplus
}
#endif

#endif
