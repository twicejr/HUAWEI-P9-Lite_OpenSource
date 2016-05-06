
#ifndef _IP6_PMTUHA_H
#define _IP6_PMTUHA_H

#ifdef  __cplusplus
extern "C"{
#endif

ULONG IP6_PMTU_HA_RealtimeBackup (UCHAR *pData, ULONG ulLen);
ULONG IP6_PMTU_HA_SetBackupData (UCHAR *pData, ULONG ulEventType);
VOID  IP6_PMTU_HA_DataSmoothOutside (VOID);
VOID  IP6_PMTU_HA_DataSmoothInside (VOID);
VOID  IP6_PMTU_HA_StateChange(ULONG ulHAState);
ULONG IP6_PMTU_HA_SendBackupData (VOID);


#ifdef  __cplusplus
}
#endif

#endif

