#ifndef NSR_OSPF_DEF01_INCLUDED
#define NSR_OSPF_DEF01_INCLUDED

/*NSR控制类消息类型定义*/
#define NSR_OSPF_CONTROL_MSG_BACKUP       1     /*OSPF备份状态消息*/
#define NSR_OSPF_CONTROL_MSG_RESTORE      2     /*OSPF备份恢复消息*/
#define NSR_OSPF_CONTROL_MSG_SMOOTH       3     /*OSPF平滑消息*/
#define NSR_OSPF_CONTROL_MSG_PROCESS      4     /*OSPF进程消息*/
#define NSR_OSPF_CONTROL_MSG_CAPABILITY   5     /*OSPF NSR使能/去使能*/


/*OSPF NSR状态定义*/
#define NSR_OSPF_STATUS_NULL              0
#define NSR_OSPF_STATUS_RESTORE_START    3
#define NSR_OSPF_STATUS_RESTORE_CANCEL   4
#define NSR_OSPF_STATUS_RESTORE_FINISH   5
#define NSR_OSPF_STATUS_SMOOTH_START     6
#define NSR_OSPF_STATUS_SMOOTH_FINISH    7

/*OSPF NSR消息收发类型定义*/
#define NSR_OSPF_MSG_DIRECT_SEND       0
#define NSR_OSPF_MSG_DIRECT_RECEIVE    1
#define NSR_OSPF_MSG_DIRECT_MAX        2

/*OSPF NSR控制类操作结果定义*/
#define NSR_OSPF_CONTROL_OK               0
#define NSR_OSPF_CONTROL_UNSUCCESS       1

#define NSR_OSPF_BACKUP_NULL      0   
#define NSR_OSPF_BACKUP_START     1   /*通知OSPF模块启动OSPF批量备份消息*/
#define NSR_OSPF_BACKUP_CANCEL    2   /*通知OSPF模块取消OSPF备份消息*/
#define NSR_OSPF_BACKUP_ERROR     3   /*通知OSPF模块备份错误消息，该消息会重新启动OSPF备份*/
#define NSR_OSPF_BACKUP_FINISH    4   /*通知NSR模块OSPF批量备份完成消息*/
#define NSR_OSPF_BACKUP_MAX       5

#define NSR_OSPF_RESTORE_NULL     0
#define NSR_OSPF_RESTORE_START    1   /*通知OSP模块启动备份恢复*/
#define NSR_OSPF_RESTORE_GET      2   /*OSPF模块向NSR模块发送备份恢复数据Get消息*/
#define NSR_OSPF_RESTORE_CANCEL   3   /*NSR模块通知OSPF执行备份恢复取消操作*/
#define NSR_OSPF_RESTORE_FINISH   4   /*OSPF模块备份恢复完成*/
#define NSR_OSPF_RESTORE_MAX      5

#define NSR_OSPF_SMOOTH_NULL      0
#define NSR_OSPF_SMOOTH_START     1
#define NSR_OSPF_SMOOTH_INTERFACE_NOTIFY_FINISH     2
#define NSR_OSPF_SMOOTH_FINISH    3
#define NSR_OSPF_SMOOTH_MAX       4

#define NSR_OSPF_PROCESS_DEL                0   /*通知NSR模块OSPF进程被删除*/
#define NSR_OSPF_PROCESS_ADD                1   /*通知NSR模块OSPF进程被添加*/
#define NSR_OSPF_PROCESS_UP                 2   /*通知NSR模块OSPF进程被up*/
#define NSR_OSPF_PROCESS_DOWN               3   /*通知NSR模块OSPF进程被down*/


#define NSR_OSPF_ATG_NO               0x00
#define NSR_OSPF_ATG_YES              0x01

#define NSR_OSPF_REPL_MAX_FIELDS   30

/*OSPF备份消息类型*/
#define NSR_OSPF_BACKUP_MSG_NULL      0
#define NSR_OSPF_BACKUP_MSG_START     1     /*OSPF备份启动消息*/
#define NSR_OSPF_BACKUP_MSG_DATA      2     /*OSPF备份数据消息*/
#define NSR_OSPF_BACKUP_MSG_FINISH    3     /*OSPF备份完成消息*/
#define NSR_OSPF_BACKUP_MSG_MAX       4

/*OSPF批量备份状态*/
#define NSR_OSPF_CATCHUP_NOT_START    0     /*批量备份未启动*/
#define NSR_OSPF_CATCHUP_INPROCESS    1     /*批量备份过程*/
#define NSR_OSPF_CATCHUP_FINISH       2     /*批量备份完成*/

/*OSPF备份控制块批量备份状态*/
#define NSR_OSPF_CATCHUP_CB_NOT_START   0   /*备份控制块的批备未启动*/
#define NSR_OSPF_CATCHUP_CB_INPROCESS   1   /*备份控制块处于批备过程*/
#define NSR_OSPF_CATCHUP_CB_FINISHED    2   /*备份控制块批备完成*/


/*数据是否备份标识，启动批量备份更换一次*/
#define NSR_OSPF_REPLICATED_FLAG_NONE    0
#define NSR_OSPF_REPLICATED_FLAG_A        1   /*控制块是否备份标识A*/
#define NSR_OSPF_REPLICATED_FLSA_B        2   /*控制块是否备份标识B*/

#define NSR_OSPF_NEW_CB_BY_RESTORE           0x01   /*标识控制块为备份恢复数据创建*/
#define NSR_OSPF_REPL_CB_CREATE              0x02   /*标识控制块备份*/
#define NSR_OSPF_REPL_DATA_CHANGED           0x04   /*NSR备份数据更新有更新*/
#define NSR_OSPF_REPL_CB_ALREADY_RESTORED   0x08   /*标识备份数据已恢复至OSPF控制块内*/
#define NSR_OSPF_SEND_REPL_LSA_REQUEST      0x10    /*标识OSPF邻居需要基于备份的LSA发送LSA请求报文*/
#define NSR_OSPF_UPDATE_CB_BY_RESTORE       0x20    /*标识控制块存在NSR恢复数据*/


/*备份数据的最大长度*/
#define NSR_OSPF_BACKUP_LEN_MAX   2048
/*备份数据的最小长度*/
#define NSR_OSPF_BACKUP_LEN_MIN  \
  (sizeof(NSR_BACKUP_HEADER) + sizeof(NSR_OSPF_BACKUP_HEADER))

/*备份的数据类型*/
#define NSR_OSPF_REPL_TYPE_PROCESS  1
#define NSR_OSPF_REPL_TYPE_AREA     2
#define NSR_OSPF_REPL_TYPE_IF       3
#define NSR_OSPF_REPL_TYPE_NBR      4
#define NSR_OSPF_REPL_TYPE_LSA      5

/*数据操作类型*/
#define NSR_OSPF_OP_NONE    0
#define NSR_OSPF_OP_CREATE  1
#define NSR_OSPF_OP_MODIFY  2
#define NSR_OSPF_OP_DELETE  3


/*发送批量备份的时间间隔*/
#define NSR_OSPF_BATCHUP_INTERVAL  1000
/*每次发送批量备份的报文个数*/
#define NSR_OSPF_BATCHUP_COUNT  100

/*模块备份恢复分配的Buffer大小*/
#define NSR_OSPF_RESTORE_DEFAULT_LEN   8192

#define NSR_OSPF_RESTORE_FIRST  1
#define NSR_OSPF_RESTORE_NEXT   2

/*NSR备份恢复状态*/
#define NSR_RESTORE_NOT_START    0     /*备份恢复未启动*/
#define NSR_RESTORE_INPROCESS    1     /*备份恢复过程*/
#define NSR_RESTORE_FINISH       2     /*备份恢复完成*/

/*OSPF备份恢复数据获取状态*/
#define NSR_OSPF_RESTORED_GET_NOT_START    0     /*OSPF备份恢复数据获取未启动*/
#define NSR_OSPF_RESTORED_GET_INPROCESS    1     /*OSPF备份恢复数据获取过程*/
#define NSR_OSPF_RESTORED_GET_FINISH       2     /*OSPF备份恢复数据获取完成*/

#define NSR_OSPF_SET_REPL_DATA_CHANGE(NSR_OSPF_REPL_CB) \
  ((NSR_OSPF_REPL_CB).repl_cb_flag |= NSR_OSPF_REPL_DATA_CHANGED)
  
#define NSR_OSPF_UNSET_REPL_DATA_CHANGE(NSR_OSPF_REPL_CB) \
  ((NSR_OSPF_REPL_CB).repl_cb_flag &= ~NSR_OSPF_REPL_DATA_CHANGED)

#define NSR_OSPF_IS_REPL_DATA_CHANGED(NSR_OSPF_REPL_CB) \
  ((NSR_OSPF_REPL_CB).repl_cb_flag & NSR_OSPF_REPL_DATA_CHANGED)

/*NSR平滑处理结果*/
#define NSR_OSPF_SMOOTH_NULL            0
#define NSR_OSPF_SMOOTH_COMPLETE        1
#define NSR_OSPF_SMOOTH_TIMEOUT         2
#define NSR_OSPF_SMOOTH_TOP_CHANGED    3

/*NSR平滑处理周期(40秒)*/
#define NSR_OSPF_NSR_SMOOTH_PERIOD    40

/*设定新生成的控制块由备份恢复创建*/
#define NSR_OSPF_SET_NEW_CB_BY_RESTORE(NSR_OSPF_REPL_CB)  \
  ((NSR_OSPF_REPL_CB).repl_cb_flag |= NSR_OSPF_NEW_CB_BY_RESTORE)
/*取消控制块由备份恢复创建标识*/
#define NSR_OSPF_UNSET_NEW_CB_BY_RESTORE(NSR_OSPF_REPL_CB)  \
  ((NSR_OSPF_REPL_CB).repl_cb_flag &= ~NSR_OSPF_NEW_CB_BY_RESTORE)
/*判断控制块是否由备份恢复创建*/
#define NSR_OSPF_IS_NEW_CB_BY_RESTORE(NSR_OSPF_REPL_CB)  \
  ((NSR_OSPF_REPL_CB).repl_cb_flag & NSR_OSPF_NEW_CB_BY_RESTORE)

/*设定备份数据已经恢复标识*/
#define NSR_OSPF_SET_REPL_DATA_RESTORED(NSR_OSPF_REPL_CB) \
  ((NSR_OSPF_REPL_CB).repl_cb_flag |= NSR_OSPF_REPL_CB_ALREADY_RESTORED)
/*取消备份数据数据已恢复标识*/
#define NSR_OSPF_SET_REPL_DATA_UNRESTORED(NSR_OSPF_REPL_CB) \
  ((NSR_OSPF_REPL_CB).repl_cb_flag &= ~NSR_OSPF_REPL_CB_ALREADY_RESTORED)
/*判断是否存在备份恢复数据*/
#define NSR_OSPF_IS_REPL_DATA_RESTORED(NSR_OSPF_REPL_CB) \
  ((NSR_OSPF_REPL_CB).repl_cb_flag & NSR_OSPF_REPL_CB_ALREADY_RESTORED)

/*设定OSPF邻居需要基于备份的LSA发送LSA Request*/
#define NSR_OSPF_SET_SEND_REPL_LSA_REQUEST(NSR_OSPF_REPL_CB) \
  ((NSR_OSPF_REPL_CB).repl_cb_flag |= NSR_OSPF_SEND_REPL_LSA_REQUEST)
/*取消OSPF邻居需要基于备份的LSA发送LSA Request标识*/
#define NSR_OSPF_UNSET_SEND_REPL_LSA_REQUEST(NSR_OSPF_REPL_CB) \
  ((NSR_OSPF_REPL_CB).repl_cb_flag &= ~NSR_OSPF_SEND_REPL_LSA_REQUEST)
/*判断OSPF邻居是否需要基于备份的LSA发送LSA Request*/
#define NSR_OSPF_NEED_SEND_REPL_LSA_REQUEST(NSR_OSPF_REPL_CB) \
  ((NSR_OSPF_REPL_CB).repl_cb_flag & NSR_OSPF_SEND_REPL_LSA_REQUEST)

/*Added by guojianjun178934, 【SDV-功能测试-NSR】NBMA网络下，删除一个区域后NSR恢复平滑出现异常, 2013/11/6   问题单号:DTS2013110401893  */
/*设定控制块存在NSR恢复的数据*/
#define NSR_OSPF_SET_UPDATE_CB_BY_RESTORE(NSR_OSPF_REPL_CB) \
  ((NSR_OSPF_REPL_CB).repl_cb_flag |= NSR_OSPF_UPDATE_CB_BY_RESTORE)
/*取消控制块保存NSR恢复数据标识*/
#define NSR_OSPF_UNSET_UPDATE_CB_BY_RESTORE(NSR_OSPF_REPL_CB) \
  ((NSR_OSPF_REPL_CB).repl_cb_flag &= ~NSR_OSPF_UPDATE_CB_BY_RESTORE)
/*判断控制块是否存在NSR恢复的数据*/
#define NSR_OSPF_IS_UPDATE_CB_BY_RESTORE(NSR_OSPF_REPL_CB) \
  ((NSR_OSPF_REPL_CB).repl_cb_flag & NSR_OSPF_UPDATE_CB_BY_RESTORE)
/* End of Added by guojianjun178934, 2013/11/6   问题单号:DTS2013110401893  */

#define NSR_OSPF_MSG_STAT_FOR_SEND(MSG_TYPE, MSG_OPT, SUB_OPT) \
  nsr_ospf_msg_statistics(NSR_OSPF_MSG_DIRECT_SEND, (MSG_TYPE), (MSG_OPT), (SUB_OPT))

#define NSR_OSPF_MSG_STAT_FOR_RECEIVE(MSG_TYPE, MSG_OPT, SUB_OPT) \
  nsr_ospf_msg_statistics(NSR_OSPF_MSG_DIRECT_RECEIVE, (MSG_TYPE), (MSG_OPT), (SUB_OPT))

/*OSPF NSR性能统计*/
#define NSR_OSPF_PERFORMANCE_OPT_START  1
#define NSR_OSPF_PERFORMANCE_OPT_END    2

/*OSPF NSR 性能统计类型*/
#define NSR_OSPF_PERFORMANCE_BACKUP              1
#define NSR_OSPF_PERFORMANCE_RESTORE             2
#define NSR_OSPF_PERFORMANCE_RESTORE_UNPACKET   3
#define NSR_OSPF_PERFORMANCE_IF_NOTIFY           4
#define NSR_OSPF_PERFORMANCE_SMOOTH              5

/*清除OSPF NSR性能数据*/
#define NSR_OSPF_CLEAR_PERFORMANCE(PERF_DATA) \
  (PERF_DATA).start_time = 0;  \
  (PERF_DATA).end_time = 0;

/*启动OSPF NSR性能数据采集*/
#define NSR_OSPF_SET_PERFORMANCE_S(PERF_DATA) \
  NSR_OSPF_CLEAR_PERFORMANCE(PERF_DATA);  \
  (PERF_DATA).start_time = NBB_GET_MTIME(); 

/*停止OSPF NSR性能数据采集*/
#define NSR_OSPF_SET_PERFORMANCE_E(PERF_DATA) \
  (PERF_DATA).end_time = NBB_GET_MTIME();

/*计算OSPF NSR性能数据*/
#define NSR_OSPF_CALC_PERFORMANCE(PERF_DATA)  \
  ((PERF_DATA).end_time - (PERF_DATA).start_time)

/*获取OSPF备份恢复整改过程性能信息*/
#define NSR_OSPF_GET_PERF_DATA_RESTORE()  \
  (LOCAL.nsr_ospf.nsr_ospf_stat.nsr_ospf_perf_stat.restore_perf_stat.restore_perf)

/*获取OSPF备份恢复最新解包处理性能信息*/
#define NSR_OSPF_GET_PERF_DATA_RESTORE_UNPACKET()  \
  (LOCAL.nsr_ospf.nsr_ospf_stat.nsr_ospf_perf_stat.restore_perf_stat.last_restore_unpacket_perf)

/*统计OSPF适配收到的消息*/
#define NSR_OSPF_ADP_MSG_STAT_FOR_SEND(INDEX, MSG_TYPE, MSG_OPT) \
  nsr_ospf_adp_msg_statistics(NSR_OSPF_MSG_DIRECT_SEND, (INDEX), (MSG_TYPE), (MSG_OPT))
/*统计OSPF适配发送的消息*/
#define NSR_OSPF_ADP_MSG_STAT_FOR_RECEIVE(INDEX, MSG_TYPE, MSG_OPT) \
  nsr_ospf_adp_msg_statistics(NSR_OSPF_MSG_DIRECT_RECEIVE, (INDEX), (MSG_TYPE), (MSG_OPT))

/*统计NSR模块备份的OSPF收到的消息*/
#define NSR_OSPF_NSR_MSG_STAT_FOR_SEND(ENT_CB, MSG_TYPE, MSG_OPT, SUB_TYPE) \
  nsr_ospf_nsr_msg_statistics(NSR_OSPF_MSG_DIRECT_SEND, (ENT_CB), (MSG_TYPE), (MSG_OPT), (SUB_TYPE))

/*统计NSR模块备份的OSPF发送的消息*/
#define NSR_OSPF_NSR_MSG_STAT_FOR_RECEIVE(ENT_CB, MSG_TYPE, MSG_OPT, SUB_TYPE) \
  nsr_ospf_nsr_msg_statistics(NSR_OSPF_MSG_DIRECT_RECEIVE, (ENT_CB), (MSG_TYPE), (MSG_OPT), (SUB_TYPE))

/*OSPF NSR备份数据恢复标识*/
#define NSR_OSPF_RESTORE_FLG_CANCELED      0x01
#define NSR_OSPF_RESTORE_FLG_WAIT_RESTORE  0x02
#define NSR_OSPF_RESTORE_FLG_FINISHED       0x04

/*判断NSR备份的OSPF数据是否需要恢复,该标记执行NSR_CanStartOSPFRestore时设定。*/
#define NSR_OSPF_IS_DATA_WAIT_RESTORE(RESTORE_FLAG) \
  ((RESTORE_FLAG) & NSR_OSPF_RESTORE_FLG_WAIT_RESTORE) 
/*设定NSR备份的OSPF数据待执行备份恢复标识*/
#define NSR_OSPF_SET_DATA_WAIT_RESTORE(RESTORE_FLAG) \
  ((RESTORE_FLAG) |= NSR_OSPF_RESTORE_FLG_WAIT_RESTORE)
/*取消NSR备份的OSPF数据待执行备份恢复标识*/
#define NSR_OSPF_UNSET_DATA_WAIT_RESTORE(RESTORE_FLAG) \
  ((RESTORE_FLAG) &= ~NSR_OSPF_RESTORE_FLG_WAIT_RESTORE)
  
/*判断NSR备份的OSPF数据备份恢复是否已经取消*/
#define NSR_OSPF_IS_DATA_RESTORE_CANCEL(RESTORE_FLAG) \
    ((RESTORE_FLAG) & NSR_OSPF_RESTORE_FLG_CANCELED)
/*设定NSR备份的OSPF数据备份恢复取消标识*/
#define NSR_OSPF_SET_DATA_RESTORE_CANCEL(RESTORE_FLAG) \
    ((RESTORE_FLAG) |= NSR_OSPF_RESTORE_FLG_CANCELED)
/*取消NSR备份的OSPF数据备份恢复取消标识*/
#define NSR_OSPF_UNSET_DATA_RESTORE_CANCEL(RESTORE_FLAG) \
    ((RESTORE_FLAG) &= ~NSR_OSPF_RESTORE_FLG_CANCELED)
    
/*判断NSR备份的OSPF数据备份恢复是否完成*/
#define NSR_OSPF_IS_DATA_RESTORE_FINISH(RESTORE_FLAG) \
    ((RESTORE_FLAG) & NSR_OSPF_RESTORE_FLG_FINISHED)  
/*设定NSR备份的OSPF数据备份恢复完成标识*/
#define NSR_OSPF_SET_DATA_RESTORE_FINISH(RESTORE_FLAG) \
    ((RESTORE_FLAG) |= NSR_OSPF_RESTORE_FLG_FINISHED)
/*取消NSR备份的OSPF数据备份恢复完成标识*/
#define NSR_OSPF_UNSET_DATA_RESTORE_FINISH(RESTORE_FLAG) \
    ((RESTORE_FLAG) &= ~NSR_OSPF_RESTORE_FLG_FINISHED)

#endif
