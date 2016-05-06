/*******************************************************************************
*
*
*                Copyright 2013, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              nsr_entity.h
*
*  Project Code: Dopra V3R2
*   Module Name:   
*  Date Created: 2013-10-11
*        Author: guojianjun178934
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2013-10-11   guojianjun178934        Create
*
*******************************************************************************/
#ifndef NSR_ENTITY_INCLUDED
#define NSR_ENTITY_INCLUDED

/*NSR消息类型*/
#define NSR_MSG_BACKUP_START                 0X00000001    /*启动备份消息*/
#define NSR_MSG_BACKUP_OUT_OF_ORDER          0X00000002    /*备份乱序消息*/
#define NSR_MSG_BACKUP_ERROR                 0X00000003    /*备份过程出错消息*/
#define NSR_MSG_CHANNEL_INACTIVE             0X00000004    /*备份通道失效消息*/
#define NSR_MSG_BACKUP_END                   0X00000005    /*备份完成消息*/
#define NSR_MSG_RESTORE_START                0X00000006    /*启动备份恢复消息*/ 
#define NSR_MSG_RESTORE_END                   0X00000007    /*完成备份恢复消息*/
#define NSR_MSG_SMOOTH_START                0X00000008    /*启动平滑处理消息*/ 
#define NSR_MSG_SMOOTH_END                   0X00000009    /*完成平滑处理消息*/

/*OSPF  NSR消息类型*/
#define NSR_OSPF_MSG_BACKUP_START       0X00000001    /*OSPF进程启动备份消息*/
#define NSR_OSPF_MSG_BACKUP_CANCEL      0X00000002    /*OSPF进程取消备份消息*/
#define NSR_OSPF_MSG_BACKUP_ERROR       0X00000003    /*OSPF进程备份错误消息*/
#define NSR_OSPF_MSG_BACKUP_END         0X00000004    /*OSPF进程完成备份消息*/
#define NSR_OSPF_MSG_RESTORE_START       0X00000005    /*OSPF进程启动备份恢复消息*/
#define NSR_OSPF_MSG_RESTORE_BACKUP      0X00000006    /*OSPF进程备份数据恢复消息*/
#define NSR_OSPF_MSG_RESTORE_END         0X00000007    /*OSPF进程完成备份恢复消息*/
#define NSR_OSPF_MSG_SMOOTH_START       0X00000008    /*OSPF进程启动平滑消息*/
#define NSR_OSPF_MSG_SMOOTH_END         0X00000009    /*OSPF进程完成平滑消息*/

#define NSR_BACKUKP_FLAG_REBACKUP   0x01    /*NSR需要重新启动备份标记*/

#define NSR_INVALID_TIMERID 0    /*应用范围: NSR使用dopra提供的定时器*/

/*nsr ospf维护的ospf进程状态*/
#define NSR_OSPF_PROCESS_ACTIVE          0X01
#define NSR_OSPF_PROCESS_INACTIVE        0X02

#define NSR_OSPF_SEND_MSG_TO_OSPF_FAIL  0X01 /*nsr_ospf向ospf发送消息失败*/

#define NSR_OSPF_PROCESS_NULL        0X00   /*ospf进程初始状态*/
#define NSR_OSPF_PROCESS_IN_BACKUP   0X01   /*ospf进程正在备份*/
#define NSR_OSPF_PROCESS_IN_CANCEL   0X02   /*ospf进程正在取消备份*/
#define NSR_OSPF_PROCESS_BACKUP_OK   0X03   /*ospf进程备份完成*/
#define NSR_OSPF_PROCESS_CANCEL_OK   0X04   /*ospf进程取消备份完成*/

#define NSR_OSPF_PROCESS_IS_ACTIVE(index) \
  (g_stNSROSPFLocal.stNSROSPFInfo.stNSROSPFProcess[index].ucProcessStatus == NSR_OSPF_PROCESS_ACTIVE)

#define NSR_OSPF_PROCESS_START_BACKUP(index) \
(g_stNSROSPFLocal.stNSROSPFInfo.stNSROSPFProcess[index].ucBackupState != NSR_OSPF_PROCESS_NULL)

#define NSR_OSPF_PROCESS_IS_INBACKUP(index) \
  (g_stNSROSPFLocal.stNSROSPFInfo.stNSROSPFProcess[index].ucBackupState == NSR_OSPF_PROCESS_IN_BACKUP)

#define NSR_OSPF_PROCESS_IS_INCANCEL(index) \
  (g_stNSROSPFLocal.stNSROSPFInfo.stNSROSPFProcess[index].ucBackupState == NSR_OSPF_PROCESS_IN_CANCEL)

#define NSR_OSPF_PROCESS_IS_BACKUP_OK(index) \
  (g_stNSROSPFLocal.stNSROSPFInfo.stNSROSPFProcess[index].ucBackupState == NSR_OSPF_PROCESS_BACKUP_OK)

#define NSR_OSPF_PROCESS_IS_CANCEL_OK(index) \
  (g_stNSROSPFLocal.stNSROSPFInfo.stNSROSPFProcess[index].ucBackupState == NSR_OSPF_PROCESS_CANCEL_OK)


/* NSR消息首部定义 */
typedef struct nsr_backup_header
{
    /* HA备份消息编号, 如果有多个消息合成一个消息包，则只有最外面层才消息才存在编号 */
    ULONG         ulSeq ;       

    /* HA版本号, 外部模块的HA版本号和VISP模块的版本号不相同 */
    ULONG         ulVer;

    /* 模块编号, VISP HA采用统一的消息号, 各备份模块可以增加自已的子模块编号 */
    UCHAR         ucModID;       
   
    /* 操作命令字, 具体含义由各模块解释 */
    UCHAR         ucOperation;   

    /* 备份消息长度(包括HA消息首部) */
    USHORT        usMsgLen;      

    /* 校验和, 缺省为0 */
    ULONG         ulChksum;
}NSR_BACKUP_HEADER;

typedef struct nsr_backup_cb
{
    UCHAR ucBackupState;
    UCHAR ucBackupFlag;     /*是否需要重新备份*/
    CHAR  pad[2];
    ULONG ulBackupBeginTimerID;
    ULONG ulLastBackupTime;
    ULONG ulBackupDelayTimerID;   /*NSR批备延时定时器*/
    NSR_CONTROL_MSG *pstNSRControlMsg;
}NSR_BACKUP_CB;

typedef struct nsr_fsm_data
{
    UCHAR ucNSRState;     /*NSR状态机的状态*/
    UCHAR pad[3];
    ULONG ulBackupTimerID;
    NSR_OSPF_ENTITY *nsr_ospf_entity;
}NSR_FSM_DATA;

/*NSR性能统计采集结构*/
typedef struct nsr_performance_data
{
    ULONG ulStartTime;
    ULONG ulEndTime;
}NSR_PERFORMANCE_DATA;

/*NSR性能统计*/
typedef struct nsr_performance_stat
{
    NSR_PERFORMANCE_DATA arrPerformanceData[NSR_PERFORMANCE_MAX];
}NSR_PERFORMANCE_STAT;

/*NSR备份消息统计*/
typedef struct nsr_backup_msg_stat
{
    ULONG ulMasterBackupMsgStat[NSR_BACKUP_MAX];
    ULONG ulSlaveBackupMsgStat[NSR_BACKUP_MAX];
}NSR_BACKUP_MSG_STAT;

/*NSR备份消息统计*/
typedef struct nsr_restore_msg_stat
{
    ULONG ulRestoreMsgStat[NSR_RESTORE_MAX];
}NSR_RESTORE_MSG_STAT;

/*NSR备份消息统计*/
typedef struct nsr_smooth_msg_stat
{
    ULONG ulSmoothMsgStat[NSR_SMOOTH_MAX];
}NSR_SMOOTH_MSG_STAT;

/*NSR控制类消息统计*/
typedef struct nsr_control_msg_stat
{
    ULONG ulBoardMsgStat;
    ULONG ulChannleMsgStat;
    ULONG ulSlaveBoardMsgStat;
    ULONG ulMasterBackupMsgStat[NSR_BACKUP_MAX];
    ULONG ulSlaveBackupMsgStat[NSR_BACKUP_MAX];
    ULONG ulRestoreMsgStat[NSR_RESTORE_MAX];
    ULONG ulSmoothMsgStat[NSR_SMOOTH_MAX];
}NSR_CONTROL_MSG_STAT;

/*NSR消息统计*/
typedef struct nsr_msg_stat
{
    NSR_CONTROL_MSG_STAT stNSRControlMsgStat[NSR_MSG_DIRECT_MAX];
    ULONG ulBackupDataStat[NSR_MSG_DIRECT_MAX];
    ULONG ulTotalMsg[NSR_MSG_DIRECT_MAX][NSR_MSG_MAX];
}NSR_MSG_STAT;

/*NSR统计信息*/
typedef struct nsr_statistics
{
    NSR_MSG_STAT stNSRMsgStat;
    NSR_PERFORMANCE_STAT stPerformanceStat;       /*NSR性能统计数据*/
}NSR_STATISTICS;

/*ospf进程的id，进程状态，备份状态*/
typedef struct nsr_ospf_process
{
    USHORT usProcessId;          /*实例id*/
    UCHAR  ucProcessStatus;         /*进程状态 add del up down interact_error*/
    UCHAR  ucBackupState;        /*备份状态 INBACKUP INCANCEL BACKUP_OK CANCEL_OK*/
    UCHAR  ucInteractOpt;        /*例 nsr_ospf向ospf发送消息失败，记录在此*/
    UCHAR  pad[3];
}NSR_OSPF_PROCESS;

/*nsr ospf 维护的 ospf进程信息*/
typedef struct nsr_ospf_info
{
    ULONG ulActiveProcessNum; /*激活的ospf进程个数*/
    NSR_OSPF_PROCESS stNSROSPFProcess[OSPF_MAX_PROCESSES]; /*ospf进程信息*/
}NSR_OSPF_INFO;

/*NSR的本地数据*/
typedef struct nsr_ospf_local
{
    BOOL_T bNSROSPFInit;          /*NSR是否初始化 0-未初始化  1-已初始化*/
    UCHAR ucNSROSPFCapability;   /*NSR OSPF是否使能 1-使能  2-未使能,默认值为2*/
    UCHAR ucNSRRole;              /*NSR角色,默认为备*/
    UCHAR ucSlaveBoardStatus;   /*备板状态*/
    UCHAR ucChannelStatus;       /*备份通道是否OK，默认为False*/
    UCHAR ucNSRStatus;           /*使能/去是能过程中NSR状态*/
    BOOL_T bBatchFirstPkt;       /*是否为批量备份的首包, 0--否, 1--是(注意:两个任务可能同时操作)*/
    BOOL_T bCalcCheckSum;        /*NSR备份数据头是否计算CheckSum, 默认FALSE*/
    ULONG ulLastReceiveSeqNum;  /*最后接收的序号，默认值为0*/
    ULONG ulNextSendSeqNum;     /*下一次发送报文的序号，默认值为1*/
    NSR_FSM_DATA stNSRFSMData;
    NSR_BACKUP_CB stNSRBackupCB;
    NSR_OSPF_INFO stNSROSPFInfo;      /*nsr ospf 维护的ospf进程状态*/
    NSR_STATISTICS stNSRStatistics;   /*NSR统计信息*/
}NSR_OSPF_LOCAL;

/*NSR备份序号有效性判断(如果接收序号为0不判断)*/
#define NSR_CHECK_RCV_SEQ_NUM(SEQ_NUM)  \
  ((g_stNSROSPFLocal.ulLastReceiveSeqNum == 0) || \
   ((SEQ_NUM) == (g_stNSROSPFLocal.ulLastReceiveSeqNum + 1)))
/*更新接收序号*/
#define NSR_UPDATE_RCV_SEQ_NUM(SEQ_NUM)  \
  (g_stNSROSPFLocal.ulLastReceiveSeqNum = (SEQ_NUM))
/*更新发送序号*/
#define NSR_UPDATE_SEND_SEQ_NUM(SEQ_NUM)  \
  (g_stNSROSPFLocal.ulNextSendSeqNum = (SEQ_NUM))
/*获取当前的发送序号*/
#define NSR_CUR_SEND_SEQ_NUM() (g_stNSROSPFLocal.ulNextSendSeqNum)
/*获取最新的接收序号*/
#define NSR_LAST_RCV_SEQ_NUM() (g_stNSROSPFLocal.ulLastReceiveSeqNum)
/*递增NSR发送序号*/
#define NSR_INC_SEND_SEQ_NUM()  \
  (g_stNSROSPFLocal.ulNextSendSeqNum++)

/*判断OSPF NSR是否为主板*/
#define NSR_OSPF_IS_MASTER_BOARD() (g_stNSROSPFLocal.ucNSRRole == NSR_ROLE_MASTER)

/*NSR OSPF模块是否已初始化*/
#define NSR_OSPF_IS_INIT()    (g_stNSROSPFLocal.bNSROSPFInit == BOOL_TRUE)
#define NSR_OSPF_SET_INIT(RESULT)    (g_stNSROSPFLocal.bNSROSPFInit = ((RESULT) == NSR_OK ? BOOL_TRUE : BOOL_FALSE))

/*NSR备份是否计算CheckSum*/
#define NSR_IS_CALC_CHECKSUM() (g_stNSROSPFLocal.bCalcCheckSum == BOOL_TRUE)

/* Modified by lihaiming218630, 之前inbackup以 非NULL且非pending_cancel 作为判断，有误, 2013/9/5   问题单号:DTS2013090400144 */
/*判断主板备份是否启动*/
#define NSR_OSPF_IS_MASTER_BACKUP_STARTED()   \
  (NSR_OSPF_IS_MASTER_BOARD() && \
   (g_stNSROSPFLocal.stNSRBackupCB.ucBackupState != NSR_BKS_NULL))

/*判断主板NSR备份是否已经启动*/
#define NSR_OSPF_IS_MASTER_INBACKUP()   \
  (NSR_OSPF_IS_MASTER_BOARD() && \
   ((g_stNSROSPFLocal.stNSRBackupCB.ucBackupState == NSR_BKS_INBACKUP) || \
   (g_stNSROSPFLocal.stNSRBackupCB.ucBackupState == NSR_BKS_BACKUP_OK)))
/*End of Modified by lihaiming218630, 2013/9/5   问题单号:DTS2013090400144 */

/* Modified by lihaiming218630, nsr通知ospf，start backup和backup cancel消息前提条件，因是两个任务，
在nsr读取配置链上的ospf备份状态时可能存在时序问题, 2013/9/2   问题单号:DTS2013082303531  */
/*判断主板NSR备份是否已经完成*/
#define NSR_OSPF_IS_MASTER_BACKUP_OK()   \
      (NSR_OSPF_IS_MASTER_BOARD() && \
       (g_stNSROSPFLocal.stNSRBackupCB.ucBackupState == NSR_BKS_BACKUP_OK))
/*End of Modified by lihaiming218630, 2013/10/30   问题单号:DTS2013082303531  */


/*判断主板NSR模块是否处于取消备份状态*/
#define NSR_OSPF_IS_MASTER_PENDING_CANCEL()  \
  (NSR_OSPF_IS_MASTER_BOARD() && \
   (g_stNSROSPFLocal.stNSRBackupCB.ucBackupState == NSR_BKS_PENDING_CANCEL))

/*判断备板备份是否启动*/
#define NSR_OSPF_IS_SLAVE_BACKUP_START()   \
  ((!NSR_OSPF_IS_MASTER_BOARD()) && \
   (g_stNSROSPFLocal.stNSRFSMData.ucNSRState != NSR_STATE_NULL))

/*判断备板NSR备份是否已经启动*/
#define NSR_OSPF_IS_SLAVE_INBACKUP()   \
  ((!NSR_OSPF_IS_MASTER_BOARD()) && \
   ((g_stNSROSPFLocal.stNSRFSMData.ucNSRState == NSR_STATE_INBACKUP) || \
    (g_stNSROSPFLocal.stNSRFSMData.ucNSRState == NSR_STATE_BACKUP_OK)))

/* Modified by lihaiming218630, 将dcl定时器改为dopra定时器，及根据检视意见代码优化, 2013/8/28   问题单号:DTS2013081608457  */   
/*判断备板NSR备份是否已经收到主板发来的备份开始消息*/
#define NSR_OSPF_IS_SLAVE_BACKUP_INIT() \
    ((!NSR_OSPF_IS_MASTER_BOARD()) && \
     (g_stNSROSPFLocal.stNSRFSMData.ucNSRState == NSR_STATE_INIT))

/*判断主板NSR备份是否处于等待备份开始ack状态*/
#define NSR_IS_MASTER_WAIT_ACK()   \
  (NSR_OSPF_IS_MASTER_BOARD() && \
   (g_stNSROSPFLocal.stNSRBackupCB.ucBackupState == NSR_BKS_WAIT_ACK))

#define NSR_GET_BACKUP_TIMER_ID()    \
    (g_stNSROSPFLocal.stNSRFSMData.ulBackupTimerID)

#define NSR_GET_BACKUP_BEGIN_TIMER_ID()    \
    (g_stNSROSPFLocal.stNSRBackupCB.ulBackupBeginTimerID)    
/*End of Modified by lihaiming218630, 2013/8/28   问题单号:DTS2013081608457  */

/*Added by guojianjun178934, 【检视发现问题】NSR批备抑制处理：连续两次批备等待一定的时间启动，避免频繁启动批备, 2013/9/9   问题单号:DTS2013090509585 */
/*NSR批备延时定时器ID*/
#define NSR_GET_BACKUP_DELAY_TIMER_ID()    \
    (g_stNSROSPFLocal.stNSRBackupCB.ulBackupDelayTimerID)

/*设定NSR批备启动时间*/
#define NSR_SET_BACKUP_START_TIME(SEC_TIME) \
  (g_stNSROSPFLocal.stNSRBackupCB.ulLastBackupTime = (SEC_TIME))

#define NSR_GET_BACKUP_DELAY_TIME(SEC_TIME) \
  (((SEC_TIME) >= g_stNSROSPFLocal.stNSRBackupCB.ulLastBackupTime) ? \
    (NSR_BATCHUP_DELAY_INTERVAL - (SEC_TIME) + g_stNSROSPFLocal.stNSRBackupCB.ulLastBackupTime) : 0)

#define NSR_IS_BACKUP_DELAY() \
  (NSR_GET_BACKUP_DELAY_TIMER_ID() != NSR_INVALID_TIMERID)

#define NSR_IS_NSR_FSM_START()  \
  (g_stNSROSPFLocal.stNSRFSMData.ucNSRState != NSR_STATE_NULL)
/* End of Added by guojianjun178934, 2013/9/9   问题单号:DTS2013090509585 */
   
/*判断备份通道是否有效*/
#define NSR_OSPF_IS_CHANNEL_ACTIVE()   (g_stNSROSPFLocal.ucChannelStatus == NSR_CHANNEL_ACTIVE)

/*判断备板是否激活*/
#define NSR_OSPF_IS_SLAVE_BOARD_ACTIVE()   (g_stNSROSPFLocal.ucSlaveBoardStatus == NSR_SLAVE_BOARD_ACTIVE)

#define NSR_GET_CONTROL_MSG_BACKUP_INFO(pstControlMsg)    \
    ((NULL == pstControlMsg) ? NULL : (&(pstControlMsg->uControlMsg.stBackupInfo)))

#define NSR_GET_BACKUP_CB()    \
    (&(g_stNSROSPFLocal.stNSRBackupCB))

#define NSR_GET_NSR_FSM_DATA()    \
    (&(g_stNSROSPFLocal.stNSRFSMData))

ULONG NSR_ReplyOSPFControlMsg(UCHAR *pucBuf, ULONG ulMsgLen);
ULONG NSR_TranControlMsg(UCHAR *pMsgBuf, ULONG ulMsgLen);
BOOL_T NSR_IsOSPFInBackupOrBackupOk(USHORT usProcessID);
ULONG NSR_SetBackupHeader(UCHAR *pMsgBuf, ULONG ulMsgLen);
BOOL_T NSR_IsAllOSPFBackupOk(VOID);
BOOL_T NSR_IsSecondBatchupOK(VOID);

BOOL_T NSR_CheckReceiveBackupData(UCHAR *pRcvData, ULONG ulRcvDataLen);
NBB_VOID NSR_DeleteAllReplData(NBB_VOID);
NBB_VOID NSR_DealOSPFBackupMsg(NSR_OSPF_CONTROL_MSG *nsr_ospf_control_msg);
NBB_VOID NSR_DealOSPFRestoreMsg(NSR_OSPF_CONTROL_MSG *nsr_ospf_control_msg);
NBB_VOID NSR_DealOSPFSmoothMsg(NSR_OSPF_CONTROL_MSG *nsr_ospf_control_msg);
NBB_VOID NSR_BackupBeginTimerPop();
NBB_VOID NSR_BackupTimerPop();


/*备板NSR备份定时器间隔(NSR_BATCHUP_INTERVAL时间内完成批量备份)*/
#define NSR_BATCHUP_INTERVAL  60000

/*主板NSR备份开始定时器间隔(NSR_BATCHUP_BEGIN_INTERVAL为间隔发送备份开始消息给备板)*/
#define NSR_BATCHUP_BEGIN_INTERVAL  3000

/*主板NSR批备延时时间(单位:秒)*/
#define NSR_BATCHUP_DELAY_INTERVAL  10


/*NSR控制类消息发送给主板*/
#define NSR_CONTROL_MSG_TO_MASTER(RECEIVER)  ((RECEIVER) | NSR_CONTROL_MSG_DEST_MASTER)
/*NSR控制类消息发送给备板*/
#define NSR_CONTROL_MSG_TO_SLAVE(RECEIVER)   ((RECEIVER) | NSR_CONTROL_MSG_DEST_SLAVE)

/*判断消息是否发送给主板*/
#define NSR_OSPF_IS_MASTER_CONTROL_MSG(DIRECT_TYPE) \
  (((DIRECT_TYPE) & NSR_CONTROL_MSG_DEST_MASTER) && NSR_OSPF_IS_MASTER_BOARD())
  
/*判断消息是否发送给备板*/
#define NSR_OSPF_IS_SLAVE_CONTROL_MSG(DIRECT_TYPE) \
    (((DIRECT_TYPE) & NSR_CONTROL_MSG_DEST_SLAVE) && !NSR_OSPF_IS_MASTER_BOARD())

/*判断控制类消息是否有效*/
#define NSR_OSPF_IS_VALID_CONTROL_MSG(DIRECT_TYPE) \
  (((DIRECT_TYPE) & NSR_CONTROL_MSG_DIRECT_NSR) && \
  (NSR_OSPF_IS_MASTER_CONTROL_MSG(DIRECT_TYPE) || \
   NSR_OSPF_IS_SLAVE_CONTROL_MSG(DIRECT_TYPE)))

/*设定批量备份首包标识(注意:需要补充锁操作)*/
#define NSR_OSPF_SET_BATCH_FIRST_PKT_FLAG(FLAG)  \
  g_stNSROSPFLocal.bBatchFirstPkt = (FLAG)

/*判断是否为批量备份的首包*/
#define NSR_IS_BATCH_FIRST_PKT()  (g_stNSROSPFLocal.bBatchFirstPkt == BOOL_TRUE)

/*此标记应该是指，nsr是否需要重新备份*/
/*设定NSR重备份标识*/
#define NSR_SET_REBACKUP_FLAG() \
  g_stNSROSPFLocal.stNSRBackupCB.ucBackupFlag |= NSR_BACKUKP_FLAG_REBACKUP
/*取消NSR重备份标识*/
#define NSR_UNSET_REBACKUP_FLAG() \
  g_stNSROSPFLocal.stNSRBackupCB.ucBackupFlag &= ~NSR_BACKUKP_FLAG_REBACKUP
/*判断NSR是否需要执行重备份*/
#define IS_NSR_NEED_REBACKUP() (g_stNSROSPFLocal.stNSRBackupCB.ucBackupFlag & NSR_BACKUKP_FLAG_REBACKUP)  

/*判断是否存在 激活 的OSPF进程*/
#define NSR_EXIST_ACTIVE_OSPF()  (g_stNSROSPFLocal.stNSROSPFInfo.ulActiveProcessNum > 0)

/*判断NSR模块是否可以处理NSR控制类消息*/
/*主板处于倒换平滑处理阶段，不处理NSR控制类消息*/
#define NSR_CAN_NOT_PROCESS_CONTROL_MSG() \
  (NSR_OSPF_IS_MASTER_BOARD() && \
   ((g_stNSROSPFLocal.stNSRFSMData.ucNSRState > NSR_STATE_BACKUP_OK) && \
    (g_stNSROSPFLocal.stNSRFSMData.ucNSRState < NSR_STATE_SMOOTH_OK)))

#define NSR_GET_PERFORMANCE_DATA(TYPE)  \
  (g_stNSROSPFLocal.stNSRStatistics.stPerformanceStat.arrPerformanceData[TYPE])

#define NSR_CLEAR_PERFORMANCE(TYPE) \
  (NSR_GET_PERFORMANCE_DATA(TYPE).ulStartTime) = 0;  \
  (NSR_GET_PERFORMANCE_DATA(TYPE).ulEndTime) = 0;

#define NSR_SET_PERFORMANCE_S(TYPE) \
  NSR_CLEAR_PERFORMANCE(TYPE); \
  (NSR_GET_PERFORMANCE_DATA(TYPE).ulStartTime) = NBB_GET_MTIME();

#define NSR_SET_PERFORMANCE_E(TYPE) \
  (NSR_GET_PERFORMANCE_DATA(TYPE).ulEndTime) = NBB_GET_MTIME();
   
#define NSR_CALC_PERFORMANCE(TYPE)  \
  ((NSR_GET_PERFORMANCE_DATA(TYPE).ulEndTime) - \
   (NSR_GET_PERFORMANCE_DATA(TYPE).ulStartTime))

#define NSR_GET_CONTROL_MSG_STAT(MSG_DIRECT)  \
  (g_stNSROSPFLocal.stNSRStatistics.stNSRMsgStat.stNSRControlMsgStat[MSG_DIRECT])

#define NSR_GET_TOTAL_MSG_STAT(MSG_DIRECT, MSG_TYPE)  \
  (g_stNSROSPFLocal.stNSRStatistics.stNSRMsgStat.ulTotalMsg[MSG_DIRECT][MSG_TYPE])

NBB_VOID NSR_StatisticMsg(NBB_BYTE msg_direct, NBB_BYTE msg_type, 
                                   NBB_BYTE sub_msg_type, NBB_BYTE msg_opt);
#define NSR_MSG_STAT_FOR_SEND(MSG_TYPE, SUB_MSG_TYPE, MSG_OPT) \
  NSR_StatisticMsg(NSR_MSG_DIRECT_SEND, (MSG_TYPE), (SUB_MSG_TYPE), (MSG_OPT))

#define NSR_MSG_STAT_FOR_RECEIVE(MSG_TYPE, SUB_MSG_TYPE, MSG_OPT) \
  NSR_StatisticMsg(NSR_MSG_DIRECT_RECEIVE, (MSG_TYPE), (SUB_MSG_TYPE), (MSG_OPT))

#define NSR_ADDCARRY(x)  (x > 65535L ? x -= 65535L : x)

#define NSR_REDUCE \
{ \
    unLUtil.l = lSum;\
    lSum = unLUtil.s[0] + unLUtil.s[1]; \
    NSR_ADDCARRY(lSum); \
}

/*设定使能/去使能过程OSPF NSR状态*/
#define NSR_OSPF_SET_NSR_STATUS(NSR_STATUS) \
  (g_stNSROSPFLocal.ucNSRStatus = (NSR_STATUS))

/*判断OSPF NSR是否激活*/
#define NSR_OSPF_IS_NSR_ACTIVE() \
  (NSR_STATUS_UP == g_stNSROSPFLocal.ucNSRStatus)
  
/*判断NSR是否处于去使能中*/
#define NSR_OSPF_IS_NSR_DEACTIVING() \
  ((NSR_CAPABILITY_DISENABLE == g_stNSROSPFLocal.ucNSROSPFCapability) &&  \
   (NSR_STATUS_GOING_DOWN == g_stNSROSPFLocal.ucNSRStatus))

/*判断OSPFNSR是否使能*/
#define NSR_OSPF_IS_NSR_ENABLE()  \
  (NSR_CAPABILITY_ENABLE ==g_stNSROSPFLocal.ucNSROSPFCapability)


/* Modified by lihaiming218630, nsr通知ospf，start backup和backup cancel消息前提条件，因是两个任务，
在nsr读取配置链上的ospf备份状态时可能存在时序问题, 2013/9/2   问题单号:DTS2013082303531  */
/*NSR 对ospf操作*/
#define NSR_NOTIFY_OSPF_START_BACKUP    0x01

/*全局变量声明区*/
extern NSR_OSPF_LOCAL g_stNSROSPFLocal;

NBB_VOID NSR_DealOSPFProcessMsg(NSR_OSPF_CONTROL_MSG *nsr_ospf_control_msg);
/*End of Modified by lihaiming218630, 2013/9/4   问题单号:DTS2013082303531  */

/* Modified by lihaiming218630, 将dcl定时器改为dopra定时器，及根据检视意见代码优化, 2013/8/28   问题单号:DTS2013081608457  */
NBB_VOID NSR_DeleteBackupTimer();
NBB_VOID NSR_DeleteBackupBeginTimer();
/*End of Modified by lihaiming218630, 2013/8/28   问题单号:DTS2013081608457  */

/*Added by guojianjun178934, 【检视发现问题】NSR批备抑制处理：连续两次批备等待一定的时间启动，避免频繁启动批备, 2013/9/9   问题单号:DTS2013090509585 */
/*NSR批备延时处理*/
NBB_VOID NSR_StartBackupDelayTimer();
NBB_VOID NSR_DeleteBackupDelayTimer();
VOID NSR_OSPF_NotifyBFDFinish();
NBB_VOID NSR_BackupDelayTimerPop();
/* End of Added by guojianjun178934, 2013/9/9   问题单号:DTS2013090509585 */
ULONG NSR_OSPF_SetNSRCapability(UCHAR  ucNSRCapability);
VOID NSR_OSPF_NotifyNSRSwitchFinish();

/* Modified by lihaiming218630, nsr与ospf 2个任务交互时, nsr读配置链g_ulOspfProcessId上ospf进程的状态, 
   若此时用户下配置或ospf自身状态变化，可能导致nsr backup fsm 死在pending cancel状态，2013/10/25   问题单号:DTS2013082303531  */
NSR_OSPF_PROCESS *NSR_OSPF_FindProcess(NBB_SHORT process_id);
/*End of Modified by lihaiming218630, 2013/10/26   问题单号:DTS2013082303531  */


#endif
