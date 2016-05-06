#ifndef NSR_OSPF_API_DEF_INCLUDED
#define NSR_OSPF_API_DEF_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/*NSR消息请求/回复定义*/
#define NSR_MSG_SIGNAL_REQUEST    0
#define NSR_MSG_SIGNAL_RESPONSE   1

#define NSR_FILTER_PROC       0x01
#define NSR_FILTER_AREA       0x02
#define NSR_FILTER_ALL        0x03

/*查询nsr中备份的ospf进程信息，会话过滤条件*/
typedef struct nsr_ospf_entity_filter
{
    USHORT   usProcessId;                       /* ospf实例号 */
    USHORT   usPad;                             
}NSR_OSPF_ENTITY_FILTER;

/*会话: 查询nsr中备份的ospf进程信息，*/
typedef struct nsr_ospf_entity_session
{
    VOID *pstNSROSPFEntity;                        /* 指向当前查询的 ospf实例 cb*/
    NSR_OSPF_ENTITY_FILTER stFilter;            /* 过滤条件 */
}NSR_OSPF_ENTITY_SESSION;

/*OSPF进程备份状态信息*/
typedef struct nsr_ospf_backup_info_show
{
    UCHAR ucBackupOpt;
    UCHAR ucResult; 
    USHORT   usPad; 
}NSR_OSPF_BACKUP_INFO_SHOW;

/*OSPF进程备份恢复状态信息*/
typedef struct nsr_ospf_restore_info_show
{
    UCHAR ucRestoreOpt;
    UCHAR ucResult; 
    USHORT   usPad; 
}NSR_OSPF_RESTORE_INFO_SHOW;

/*OSPF进程平滑状态信息*/
typedef struct nsr_ospf_smooth_info_show
{
    UCHAR ucSmoothOpt;
    UCHAR ucResult; 
    USHORT   usPad;
}NSR_OSPF_SMOOTH_INFO_SHOW;

/*查询业务统计，会话过滤条件*/
typedef struct nsr_business_stat_filter
{
    USHORT   usProcessId;                       /*ospf实例号 */
    USHORT   usPad;             
}NSR_BUSINESS_STAT_FILTER;

/*会话:查询业务统计*/
typedef struct nsr_business_stat_session
{
    VOID *pstNSROSPFEntity;                        /*指向当前ospf实例*/
    NSR_BUSINESS_STAT_FILTER   stFilter;           /*过滤条件 */
}NSR_BUSINESS_STAT_SESSION;


typedef struct nsr_ospf_business_stat
{
    USHORT usProcessId;
    ULONG ulAreaCount;
    ULONG ulIfCount;
    ULONG ulNbrCount;
    ULONG ulLSACount;
    ULONG ulDownNbrCount;
    ULONG ulAttemptNbrCount;
    ULONG ulInitNbrCount;
    ULONG ul2WayNbrCount;
    ULONG ulExstartNbrCount;
    ULONG ulExchangeNbrCount;
    ULONG ulLoadingNbrCount;
    ULONG ulFullNbrCount;
    ULONG ulRouterLSACount;
    ULONG ulNetworkLSACount;
    ULONG ulSummsryNetLSACount;
    ULONG ulSummaryASBRLSACount;
    ULONG ulExternalLSACount;
    ULONG ulNSSALSACount;
    ULONG ulOpqLSACount;
}NSR_OSPF_BUSINESS_STAT;


/*查询到的，备份的ospf实例信息*/
typedef struct nsr_ospf_entity_repl_show
{
    USHORT   usProcessId;                       /*ospf实例号*/
    UCHAR    ucOperStatus;
    CHAR     pad[1];
    ULONG    ulRouterIdRepl;                    /*备份的OSPF router id*/
    ULONG    ulCryptoSeqNumRepl;                /*当前的MD5序号*/
    NSR_OSPF_BACKUP_INFO_SHOW stBackupInfo;     /*OSPF进程备份信息*/
    NSR_OSPF_RESTORE_INFO_SHOW stRestoreInfo;   /*OSPF进程备份恢复信息*/
    NSR_OSPF_SMOOTH_INFO_SHOW stSmoothInfo;     /*OSPF进程平滑信息*/
    NSR_OSPF_BUSINESS_STAT stBusinessStat;      /*临时成员：业务统计数据*/
}NSR_OSPF_ENTITY_REPL_SHOW;

/*查询nsr中备份的IF进程信息，会话过滤条件*/
typedef struct nsr_ospf_if_filter
{
    USHORT   usProcessId;                       /*ospf实例号 */
    USHORT   usPad;             
}NSR_OSPF_IF_FILTER;

/*会话:查询nsr中备份的ospf if数据*/
typedef struct nsr_ospf_if_session
{
    VOID *pstNSROSPFEntity;                        /*指向当前ospf实例*/
    VOID *pstIfCB;
    NSR_OSPF_IF_FILTER   stFilter;              /*过滤条件 */
}NSR_OSPF_IF_SESSION;

/*查询到的，备份的接口信息*/
typedef struct nsr_ospf_if_repl_show
{
    USHORT   usProcessId;                       /* ospf实例号 */
    USHORT   usPad;
    ULONG    ulIfIpAddress;                     /* 接口的地址, 在ospf中数组下标值为 ATG_INET_ADDRESS*/
    ULONG    ulAreaId;
    ULONG    ulIfStateRepl;                       /*接口状态机状态*/
    ULONG    ulDRRepl;                          /*接口选举的DR  在ospf中数组下标值为 QOPM_ID_LEN*/
    ULONG    ulBDRRepl;                         /*接口选举的BDR 在ospf中数组下标值为 QOPM_ID_LEN*/
    ULONG    ulIfNetworkType;                  /*接口网络类型*/
    UCHAR    ulOperStatus;
    CHAR     pad[3];
}NSR_OSPF_IF_REPL_SHOW;

/*查询nsr中备份的nbr信息，会话过滤条件*/
typedef struct nsr_ospf_nbr_filter
{
    USHORT   usProcessId;                       /* ospf实例号 */
    USHORT   usPad;             
}NSR_OSPF_NBR_FILTER;

/*会话:查询nsr中备份的ospf nbr数据*/
typedef struct nsr_ospf_nbr_session
{
    VOID *pstNSROSPFEntity;                        /* 指向当前ospf实例*/
    VOID *pstNbrCB;
    NSR_OSPF_NBR_FILTER   stFilter;             /* 过滤条件 */
}NSR_OSPF_NBR_SESSION;

/*查询到的，备份的邻居信息*/
typedef struct nsr_ospf_nbr_repl_show
{
    USHORT  usProcessId;                        /* ospf实例号 */
    USHORT  usPad;
    ULONG   ulAreaId;
    LONG    lNbrStateRepl;                         /*邻居状态机状态*/
    ULONG   ulDRRepl;                           /*邻居选举出的DR*//*QOPM_ID_LEN*/
    ULONG   ulBDRRepl;                          /*邻居选举出的BDR*//*QOPM_ID_LEN*/
    ULONG   ulLastDDSeqNumRepl;                     /*最后收到的DD序号*/
    LONG    lPermanenceRepl;                    /*邻居标记(动态/永久)*/
    ULONG   ulRouterIdRepl;                     /*邻居对应的Router ID*/
    ULONG   ulParentIfIpAddress;                /*父接口的地址 */
    ULONG   ulNbrIpAddress;                     /*邻居地址 */
    UCHAR   ucPriorityRepl;                     /*邻居的优先级*/
    UCHAR   ucLastDDOptionsRepl;                /*最后收到的DD选项*/
    UCHAR   ucLastDDFlagsRepl;                  /*最后收到的DD标识*/
    UCHAR   ucFriendStatusRepl;                 /*同邻居的邻接关系*/
    UCHAR   ucOperStatus;                       /*邻居的操作状态*/
    UCHAR   ucNbrHelperStateRepl;              /*邻居Helper FSM状态*/
    CHAR    pad[2];
}NSR_OSPF_NBR_REPL_SHOW;

/*查询nsr中备份的区域信息，会话过滤条件*/
typedef struct nsr_ospf_area_filter
{
    USHORT  usFilterFlag;                          /*取值范围: NSR_FILTER_PROC       0x01
                                                             NSR_FILTER_AREA       0x02
                                                             NSR_FILTER_ALL        0x03*/
    USHORT  usProcessId;                        /* ospf实例号 */
    ULONG   ulAreaId;
}NSR_OSPF_AREA_FILTER;

/*会话:查询nsr中备份的ospf nbr数据*/
typedef struct nsr_ospf_area_session
{
    VOID *pstNSROSPFEntity;                        /* 指向当前ospf实例*/
    VOID *pstAreaCB;
    NSR_OSPF_AREA_FILTER   stFilter;            /* 过滤条件 */
}NSR_OSPF_AREA_SESSION;

/*查询到的，备份的区域信息*/
typedef struct nsr_ospf_area_repl_show
{
    USHORT  usProcessId;                        /* 指向当前ospf实例*/
    USHORT  usPad;
    ULONG   ulAreaId;
}NSR_OSPF_AREA_REPL_SHOW;

/*查询nsr中备份的lsdb信息，会话过滤条件*/
typedef struct nsr_ospf_lsdb_filter
{
    USHORT  usProcessId;
    UCHAR   ucLSAType;   
/*
#define OSPF_ROUTER_LSA           1
#define OSPF_NETWORK_LSA          2
#define OSPF_SUMMARY_LSA          3
#define OSPF_SUMMARY_ASBR_LSA     4
#define OSPF_ASEXTERNAL_LSA       5
#define OSPF_NSSA_LSA             7
#define OSPF_OPAQUE_LOCAL_LSA     9
#define OSPF_OPAQUE_AREA_LSA      10
#define OSPF_OPAQUE_AS_LSA        11*/
    UCHAR   ucPad;
}NSR_OSPF_LSDB_FILTER;

/*会话:查询nsr中备份的 lsdb 数据*/
typedef struct nsr_ospf_lsdb_session
{
    VOID    *pstNSROSPFEntity;                     /* 指向当前ospf实例*/
    VOID    *pstLSDBCB;
    VOID    *pstAreaCB;
    NSR_OSPF_LSDB_FILTER   stFilter;            /* 过滤条件 */
}NSR_OSPF_LSDB_SESSION;


/*LSA的头部信息*/
typedef struct tag_nsr_ospf_lsa_hdr_repl_show
{
    ULONG   ulRouterId;
    ULONG   ulAreaId;                           /* for type-5 LSA, this field is invalid */
    USHORT  usProcessId;
    USHORT  usLSAAge;                           /* 老化时间 */
    UCHAR   ucOptions;                          /* 可选项 */
    UCHAR   ucLSAType;                          /* LSA 类型 */
    USHORT  usLength;                           /* 包含LSA头部在内的LSA长度 */
    ULONG   ulLinkId;                           /* 链路ID */
    ULONG   ulAdvRoute;                         /* 通告路由器ID */
    ULONG   ulSeqNum;                           /* 序列号 */
    ULONG   ulCheckSum;                         /* 校验和 */
}NSR_OSPF_LSA_HDR_REPL_SHOW_S;

/*NSR的本地数据*/
typedef struct nsr_state_info_show
{
    UCHAR ucNSRRole;                            /*NSR角色,默认为备*/
    UCHAR ucSlaveBoardStatus;                   /*备板状态*/
    UCHAR ucChannelStatus;                      /*备份通道是否OK，默认为False*/
    BOOL_T bNSRInit;                            /*NSR是否初始化 0-未初始化  1-已初始化*/
    BOOL_T bBatchFirstPkt;                      /*是否为批量备份的首包, 0--否, 1--是(注意:两个任务可能同时操作)*/
    UCHAR ucNSRState;                           /*NSR状态机的状态*/
    UCHAR ucNSRBackupState;
}NSR_STATE_INFO_SHOW;

/*NSR性能统计类型*/
#define NSR_PERFORMANCE_BATCH_MASTER          1
#define NSR_PERFORMANCE_BATCH_SLAVE           2
#define NSR_PERFORMANCE_RESTORE               3
#define NSR_PERFORMANCE_IF_NOTIFY             4
#define NSR_PERFORMANCE_TOP_RELEARN           5
#define NSR_PERFORMANCE_SWITCH                6
#define NSR_PERFORMANCE_TRUNK_NOTIFY          7
#define NSR_PERFORMANCE_MAX                   8

/*NSR性能统计数据查询接口*/
typedef struct nsr_performance_stat_show
{
    ULONG arrNSRPerformanceStat[NSR_PERFORMANCE_MAX];
}NSR_PERFORMANCE_STAT_SHOW;

/*NSR消息收发定义*/
#define NSR_MSG_DIRECT_SEND     0
#define NSR_MSG_DIRECT_RECEIVE  1
#define NSR_MSG_DIRECT_MAX      2

/*NSR消息统计查询接口*/
typedef struct nsr_msg_stat_show
{
    /*NSR处理的控制类消息统计*/
    ULONG ulBoardMsgStat[NSR_MSG_DIRECT_MAX];
    ULONG ulChannleMsgStat[NSR_MSG_DIRECT_MAX];
    ULONG ulSlaveBoardMsgStat[NSR_MSG_DIRECT_MAX];
    ULONG ulMasterBackupMsgStat[NSR_MSG_DIRECT_MAX][NSR_BACKUP_MAX];
    ULONG ulSlaveBackupMsgStat[NSR_MSG_DIRECT_MAX][NSR_BACKUP_MAX];
    ULONG ulRestoreMsgStat[NSR_MSG_DIRECT_MAX][NSR_RESTORE_MAX];
    ULONG ulSmoothMsgStat[NSR_MSG_DIRECT_MAX][NSR_SMOOTH_MAX];
    /*NSR处理的备份数据消息统计*/
    ULONG ulBackukDataStat[NSR_MSG_DIRECT_MAX];
    /*NSR收发的所有控制类统计*/
    ULONG ulTotalNSRControlMsg[NSR_MSG_DIRECT_MAX];
    /*NSR收发的所有备份数据消息统计*/
    ULONG ulTotalBackupDataMsg[NSR_MSG_DIRECT_MAX];
}NSR_MSG_STAT_SHOW;


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
