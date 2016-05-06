#ifndef NSR_BACKUP_FSM_INCLUDED
#define NSR_BACKUP_FSM_INCLUDED

#ifdef  __cplusplus
extern "C"{
#endif

/*NSR备份状态定义*/
#define NSR_BKS_NULL                1
#define NSR_BKS_WAIT_ACK            2
#define NSR_BKS_INBACKUP            3
#define NSR_BKS_BACKUP_OK           4
#define NSR_BKS_PENDING_CANCEL      5

/*NSR 备份状态数量*/
#define NSR_BACKUP_NUM_STATES     5


/*NSR备份输入事件定义*/
#define NSR_BKI_NEW_BACKUP              0
#define NSR_BKI_RCV_BACKUP_START_ACK    1
#define NSR_BKI_REPL_COMPLETE           2
#define NSR_BKI_REPL_FAIL               3
#define NSR_BKI_OSPF_REPL_FAIL          4
#define NSR_BKI_REPL_ABORT              5
#define NSR_BKI_REPL_CANCEL_OK          6
#define NSR_BKI_ALL_OSPF_INACTIVE    7


/*NSR 备份输入事件数量*/
#define NSR_BACKUP_NUM_INPUTS           8


VOID NSR_BackupFSM(UCHAR ucInput, NSR_BACKUP_CB *pstBackupCB);
ULONG NSR_StartOSPFBackup(USHORT usProcessID);
ULONG NSR_SendBackupControlMsg(UCHAR ucMsgType, UCHAR ucResult);


#ifdef  __cplusplus
}
#endif

#endif

