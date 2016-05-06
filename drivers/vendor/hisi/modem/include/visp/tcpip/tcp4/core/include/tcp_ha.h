/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcp_ha.h
*
*  Project Code: VISP V100R006
*   Module Name: TCP4
*  Date Created: 2006-12-7
*        Author: l48923(48923)
*   Description: Header of tcp ha
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-12-7   l48923(48923)    Create the first version.
*
*******************************************************************************/
#ifndef        _TCP_HA_H
#define        _TCP_HA_H

#ifdef    __cplusplus
extern    "C"{
#endif
/* Definition of backup operation of TCP module */
/* if you add or delete bak type,please upate g_aszTcpBackDbgInfo & function SOCK_HA_DebugBackupMsg*/
enum enumTCPHAOP
{
    BK_TCP_GLOBALVAR = 1, /* Backup tcp global variables */
    BK_TCP_TCPCB,         /* Backup tcp control block */
};

/* Max interval of routine backup of tcp socket buffer */
#define TCP_MAX_ROUTINE_BACKUP_INTERVAL 3600

/* Not backup tcp socket buffer */
#define TCP_NOT_BACKUP_DATA 0XFFFF

/* Realtime backup tcp socket buffer */
#define TCP_REALTIME_BACKUP_DATA 0

/* Backup tcpcb */
typedef struct tagBKTCPCB
{
    SHORT        sState;
    SHORT        sTimer[TCPT_NTIMERS];
    SHORT        sRexmtShift;
    SHORT        sRexmtCur;
    SHORT        sDupAcks;
    USHORT       usMaxSeg;
    USHORT       usFlags;
    TCP_SEQ      seqSndUnack;
    TCP_SEQ      seqSndNxt;
    TCP_SEQ      seqSndUrgentPoint;
    TCP_SEQ      seqLastRcvSeqToUpdWnd;    
    TCP_SEQ      seqLastRcvAckToUpdWnd;    
    TCP_SEQ      seqISS;
    ULONG        ulSndWnd;
    ULONG        ulRcvWnd;
    TCP_SEQ      seqRcvNxt;
    TCP_SEQ      seqRcvUrgentPoint;
    TCP_SEQ      seqInitRcvSeq;
    TCP_SEQ      seqRcvAdvertise;
    TCP_SEQ      seqSndMax;
    ULONG        ulSndCongestionWnd;
    ULONG        ulSndSSThresh;
    SHORT        sIdle;
    SHORT        sRTT;
    TCP_SEQ      seqRTSeq;
    SHORT        sSRTT;
    SHORT        sRTTVar;
    USHORT       usRTTMin;
    CHAR         cOOBFlags;
    CHAR         cIOBC;
    ULONG        ulMaxSndWnd;
    UCHAR        ucSndScale;
    UCHAR        ucRcvScale;
    UCHAR        ucRequestRScale;
    UCHAR        ucRequestedSScale;
    ULONG        ulTSRecent;
    ULONG        ulTSRecentAge;
    TCP_SEQ      seqLastAckSent;
    ULONG        ulRcvMSS;
    ULONG        ulSndMSS;
    ULONG        ulSndBufCutLen;
    USHORT       usRoutineBackupTime;
    UCHAR        ucHaveTemplate;
    UCHAR        ucPadding_1;
}BKTCPCB_S;

/* TCP global vars that need backup */
typedef struct tagBKTCPGlobalVar
{
    LONG         lTCPKeepIntvl;
    LONG         lTCPMaxIdle;
    ULONG        ulTCPNow;
    ULONG        ulTCPSndSpace;
    ULONG        ulTCPRcvSpace;
    TCP_SEQ      seqTCPISS;
    ULONG        ulRespondQuench;
}BKTCPGLOBALVAR_S;

extern TCPCB_S *g_pstTcpRoutineHead;

/* Check whether tcp socket buf should be realtime backuped */
#define TCP_HA_ISREALTIMEBACKUP(pTCPCB) \
    (TCP_REALTIME_BACKUP_DATA == (pTCPCB)->usRoutineBackupTime)

/* Check whether tcp socket buf should be routine backuped */
#define TCP_HA_ISROUTINEBACKUP(pTCPCB) \
    ((TCP_REALTIME_BACKUP_DATA != (pTCPCB)->usRoutineBackupTime) \
    && (TCP_NOT_BACKUP_DATA != (pTCPCB)->usRoutineBackupTime) \
	/*by q62011 for V3R2C00 coverity 选项配置处已经有保证了，此处仅为消除告警*/\
    && (TCP_MAX_ROUTINE_BACKUP_INTERVAL >= (pTCPCB)->usRoutineBackupTime))

/* Insert tcpcb into routine backup chain */
#define TCP_HA_INSROUTINEBACKUP(pTCPCB)   \
{   \
    if ((NULL == (pTCPCB)->pNextRoutine) \
        && (NULL == (pTCPCB)->pPrevRoutine) \
        && (g_pstTcpRoutineHead != (pTCPCB)) \
      ) \
    { \
        (pTCPCB)->pNextRoutine = g_pstTcpRoutineHead; \
        if (g_pstTcpRoutineHead) \
        { \
            g_pstTcpRoutineHead->pPrevRoutine= (pTCPCB); \
        } \
        g_pstTcpRoutineHead = (pTCPCB); \
    } \
}

/* Remove tcpcb from routine backup chain */
#define TCP_HA_DELROUTINEBACKUP(pTCPCB)   \
{  \
    if ((pTCPCB)->pNextRoutine)  \
    { \
        (pTCPCB)->pNextRoutine->pPrevRoutine = (pTCPCB)->pPrevRoutine; \
    } \
    if ((pTCPCB)->pPrevRoutine) \
    { \
        (pTCPCB)->pPrevRoutine->pNextRoutine = (pTCPCB)->pNextRoutine; \
    } \
    else if (g_pstTcpRoutineHead == (pTCPCB)) \
    { \
        g_pstTcpRoutineHead = (pTCPCB)->pNextRoutine; \
    } \
    (pTCPCB)->pNextRoutine = NULL; \
    (pTCPCB)->pPrevRoutine = NULL; \
}

/* Get length to backup tcpcb */
#define TCP_HA_GETTCPCBBACKUPLEN(pTCPCB, ulBackupLen) \
{ \
    ulBackupLen = sizeof(BKTCPCB_S); \
}

/* Get max length to backup tcpcb */
#define TCP_HA_GETMAXTCPCBBACKUPLEN(ulBackupLen) \
{ \
    ulBackupLen = sizeof(BKTCPCB_S) + 256; \
}

/* Revise seqRcvNxt and members in TCPCB that is related to seqRcvNxt */
#define TCP_REVISE_SEQRCVNXT(pTCPCB, seqNewRcvNxt) \
{ \
    pTCPCB->seqRcvNxtLastBackup += seqNewRcvNxt - pTCPCB->seqRcvNxt; \
    pTCPCB->seqRcvLastBackup    += seqNewRcvNxt - pTCPCB->seqRcvNxt; \
    pTCPCB->seqRcvAdvertise     += seqNewRcvNxt - pTCPCB->seqRcvNxt; \
    pTCPCB->seqRcvNxt           =  seqNewRcvNxt; \
    pTCPCB->ulSeqRcvNxtRevised++; \
    tstTCPStat.ulSeqRcvNxtRevised++; \
}

VOID TCP_HA_FreeTCPCB(TCPCB_S *pTCPCB);
VOID TCP_HA_SockShutdownRead(SOCKET_S *pSocket);
VOID TCP_HA_SockBackupStateChange(SOCKET_S *pSocket);
LONG TCP_HA_TCPCBPack(TCPCB_S *pTCPCB, BKTCPCB_S *pBkTCPCB);
LONG TCP_HA_TCPCBUnpack(TCPCB_S *pTCPCB, BKTCPCB_S *pBkTCPCB, ULONG ulBkTCPCBLen);
LONG TCP_HA_BackupNotify(TCPCB_S *pTCPCB, UCHAR ucOperation);
LONG TCP_HA_BatchBackup();
LONG TCP_HA_BackupMsgDeal(UINTPTR ulMsg[4], CHAR **ppszBuf, ULONG *pulBufLen);
LONG TCP_HA_Restore(CHAR *pszBackupMsg);

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif
