#ifndef NSR_FSM_INCLUDED
#define NSR_FSM_INCLUDED

#ifdef  __cplusplus
extern "C"{
#endif

/*NSR 状态机状态数量*/
#define NSR_FSM_NUM_STATES     8
/*NSR 状态机输入事件数量*/
#define NSR_FSM_NUM_INPUTS     12

/*NSR 状态机状态定义*/
#define NSR_STATE_NULL          1
#define NSR_STATE_INIT          2
#define NSR_STATE_INBACKUP     3
#define NSR_STATE_BACKUP_OK    4
#define NSR_STATE_INRESTORE    5
#define NSR_STATE_RESTORE_OK   6
#define NSR_STATE_INSMOOTH      7
#define NSR_STATE_SMOOTH_OK     8

/*NSR备份输入事件定义*/
#define NSR_INPUT_START_BACKUP         0
#define NSR_INPUT_RCV_BACKUP_DATA      1
#define NSR_INPUT_END_BACKUP            2
#define NSR_INPUT_DEL_BACKUP            3
#define NSR_INPUT_OSPF_BACKUP_ERROR    4
#define NSR_INPUT_BACKUP_ERROR         5
#define NSR_INPUT_BACKUP_TIMEOUT        6
#define NSR_INPUT_START_RESTORE         7
#define NSR_INPUT_RESTORE_COMPLETE      8
#define NSR_INPUT_START_SMOOTH          9
#define NSR_INPUT_SMOOTH_COMPLETE       10
#define NSR_INPUT_ABORT                  11

VOID NSR_FSM(UCHAR ucInput, NSR_FSM_DATA *pstNSRFSMData);


#ifdef  __cplusplus
}
#endif

#endif
