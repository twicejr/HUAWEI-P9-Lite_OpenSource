/*******************************************************************************
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              poes_ha.h
*
* Project Code: VISPV100R006C02
*  Module Name: POES
* Date Created: 2007-07-18
*       Author: lijing(52889)
*  Description: POES模块的HA的相关数据结构、宏、枚举类型定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2007-07-18   lijing(52889)           Create
*
*******************************************************************************/

#ifndef _POES_HA_H_
#define _POES_HA_H_

#ifdef __cplusplus
extern "C"{
#endif

ULONG POES_HA_RealTimeBackup(UCHAR ucBkMsgType, UCHAR *pucInfo);
VOID POES_HA_BindingPack(UCHAR *pucBkBuf, POES_CB_S *pstPoesCb);
VOID POES_HA_SessionPack(UCHAR *pucBkBuf, POES_SB_S *pstPoesSb);
ULONG POES_HA_BatchBackup();
ULONG POES_HA_RealTimeBackup(UCHAR ucBkMsgType, UCHAR *pucInfo);
ULONG POES_HA_Input(UCHAR *pucBkMsg, ULONG ulMsgLen);
ULONG POES_HA_Smooth();
ULONG POES_HA_Clean();
VOID POES_HA_DebugOutput(UCHAR *pucBkMsg, ULONG ulMsgLen, ULONG ulCmd);
ULONG TCPIP_HA_SetPoesDbg(ULONG ulValue);
ULONG TCPIP_HA_GetPoesDbg(ULONG *pulValue);
ULONG TCPIP_HA_SetPoesVerboseDbg(ULONG ulValue);
ULONG TCPIP_HA_GetPoesVerboseDbg(ULONG *pulValue);

/* Backup msg type of poes */
/* if you add or delete bak type,please upate g_aszPoesBackDbgInfo & function POES_HA_DebugOutput*/
enum enumPoesBkMsgType
{
    BK_POES_GLOBAL_SETTING = 1, /* Backup global settings */
    BK_POES_BINDING_UPDATE,     /* Create or update binding */
    BK_POES_BINDING_DELETE,     /* Delete binding */
    BK_POES_SESSION_UPDATE,     /* Create or update session*/
    BK_POES_SESSION_DELETE,     /* Delete session */
};

/* Backup struct for poes global vars */
typedef struct tagBkPoesGlobalSetting
{
    USHORT usMaxSession;          /* Max session */
    USHORT usMaxSessionPerOurMac; /* Max session per our mac */
    USHORT usMaxSessionPerHisMac; /* Max session per peer mac */
    UCHAR  ucPadding[2];
}BKPOESGLOBALSETTING_S;

/* Backup struct for poes binding */
typedef struct tagBkPoesBinding
{
    ULONG ulIfIndex ;      /* If index of ethernet*/
    ULONG ulVTIfIndex ;     /* If index of vt */
    UCHAR szServiceName[POES_SERVICENAME_MAX_LEN]; /* Service Name */
}BKPOESBINDING_S;

/* Backup struct for poes session */
typedef struct tagBkPoesSession
{
    ULONG ulIfIndex ;   /* If index of ethernet*/
    ULONG ulVAIfIndex ; /* If index of va */
    USHORT usSessionId; /* Session id */
    UCHAR ucSesState;   /* Session state */
    UCHAR szHisMacAddr[POES_MAC_LEN]; /* Client mac */
    UCHAR ucPadding_1[3];
}BKPOESSESSION_S;

#define POES_HA_SAVE_BINDING(pstBkPoesBinding, pstPoesCb) POES_HA_BindingPack((UCHAR *)(pstBkPoesBinding), pstPoesCb)
#define POES_HA_SAVE_SESSION(pstBkPoesSession, pstPoesSb) POES_HA_SessionPack((UCHAR *)(pstBkPoesSession), pstPoesSb)
#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _POEC_HA_H_ */

