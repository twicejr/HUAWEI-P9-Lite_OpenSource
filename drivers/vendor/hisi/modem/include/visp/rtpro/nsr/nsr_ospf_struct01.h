/*******************************************************************************
*
*
*                Copyright 2013, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              nsr_ospf_struct01.h
*
*  Project Code: Dopra V3R2
*   Module Name: OSPF NSR数据结果定义(1)  
*  Date Created: 2013-10-11
*        Author: guojianjun178934
*   Description: 该头文件中定义的数据结构只依赖NBase的基础数据结构，
*                不涉及OSPF内部数据结构,如果需要依赖OSPF内部结果，
*                请在文件nsr_ospf_struct02.h中定义。
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2013-10-11   guojianjun178934        Create
*
*******************************************************************************/
#ifndef NSR_OSPF_STRUCT01_INCLUDED
#define NSR_OSPF_STRUCT01_INCLUDED

typedef struct nsr_ospf_backup_info
{
    NBB_BYTE backup_opt;
    NBB_BYTE result;
    NBB_BYTE pad[2];
}NSR_OSPF_BACKUP_INFO;

typedef struct nsr_ospf_restore_header
{
    NBB_BYTE data_type;           /*恢复的数据类型*/
    NBB_USHORT num_entries;        /*包含的实例数*/
}NSR_OSPF_RESTORE_HEADER;

typedef struct atg_i3_nsr_ospf_restore_ind
{
    NBB_IPS ips_hdr;
    NBB_BYTE more_entries;
    NBB_USHORT total_entries;
} ATG_I3_NSR_OSPF_RESTORE_IND;

typedef struct nsr_ospf_restore_info
{
    NBB_BYTE restore_opt;
    NBB_BYTE list_option;
    NBB_BYTE result;
    NBB_BYTE pad[1];
    NBB_BYTE cur_router_id_repl[4];
    ATG_I3_NSR_OSPF_RESTORE_IND *nsr_ospf_restore_ind;
}NSR_OSPF_RESTORE_INFO;

typedef struct nsr_ospf_smooth_info
{
    NBB_BYTE smooth_opt;
    NBB_BYTE result;
    NBB_BYTE pad[2];
}NSR_OSPF_SMOOTH_INFO;

/* Modified by lihaiming218630, nsr通知ospf，start backup和backup cancel消息前提条件，因是两个任务，
在nsr读取配置链上的ospf备份状态时可能存在时序问题, 2013/9/2   问题单号:DTS2013082303531  */
typedef struct nsr_ospf_process_info
{
    NBB_LONG flag; /*值0-进程被删除*/
}NSR_OSPF_PROCESS_INFO;
/*End of Modified by lihaiming218630, 2013/9/2   问题单号:DTS2013082303531  */


/*OSPF NSR控制类型消息定义*/
typedef struct nsr_ospf_control_msg
{
    NBB_USHORT  process_id;
    NBB_BYTE msg_type;
    union
      {
          NSR_OSPF_BACKUP_INFO backup_info;       /*OSPF备份状态通知*/
          NSR_OSPF_RESTORE_INFO restore_info;     /*OSPF备份恢复通知*/
          NSR_OSPF_SMOOTH_INFO smooth_info;       /*OSPF平滑通知*/
          NSR_OSPF_PROCESS_INFO process_info;     /*OSPF进程状态*/
          NBB_BYTE nsr_capability_info;          /*OSPF NSR 使能/ 去使能*/
      }control_msg;

}NSR_OSPF_CONTROL_MSG;

typedef struct atg_i3_nsr_notify_ospf
{
  NBB_IPS ips_hdr;
  NSR_OSPF_CONTROL_MSG nsr_ospf_control_msg;
} ATG_I3_NSR_NOTIFY_OSPF;

/*OSPF NSR备份数据控制信息*/
typedef struct nsr_opsf_repl_cb
{
    /*NBB_BYTE repl_type;*/
    NBB_BYTE repl_operation;    /*备份数据的操作,用于实时备份*/
    NBB_BYTE repl_cb_flag;      /*备份数据的标识信息*/
    NBB_ULONG replicated_flag;   /*控制块是否备份标识*/
}NSR_OSPF_REPL_CB;

typedef struct nsr_ospf_repl_field_info
{
  NBB_BYTE field_absent[NSR_OSPF_REPL_MAX_FIELDS];

} NSR_OSPF_REPL_FIELD_INFO;

/* OSPF备份消息头定义 */
typedef struct nsr_ospf_backup_header
{
    NBB_USHORT process_id;    /*OSPF进程ID*/
    NBB_BYTE backup_type;     /*备份类型(批备/实备)*/
    NBB_BYTE msg_type;        /*消息类型(数据/操作)*/
    NBB_USHORT msg_len;       /*备份数据长度(不包括消息头)*/
}NSR_OSPF_BACKUP_HEADER;

/*OSPF备份数据头*/
typedef struct nsr_ospf_data_header
{
    NBB_BYTE data_type;          /*备份数据类型*/
    NBB_BYTE rep_operation;     /*备份操作类型*/
    NBB_USHORT total_len;      /*备份数据长度*/
    /*后面紧跟着备份数据类型对应的键值,但LSA的处理除外*/
}NSR_OSPF_DATA_HEADER;

/*存储NSR OSPF相关的数据*/
typedef struct nsr_ospf_data
{
    AVL_TREE cb_type_tree;
    NBB_LQE cb_type_list;
    NBB_ULONG next_cb_type_repl_order;

    NBB_LQE ospf_backup_list;
}NSR_OSPF_DATA;

/*Added by guojianjun178934, I3通知OSPF更新认证序号, 2013/3/2   问题单号:20130118_01 */
typedef struct atg_i3_notify_crypto_seq_num_refresh
{
    NBB_IPS ips_hdr;
    NBB_ULONG seq_num;
}ATG_I3_NOTIFY_CRYPTO_SEQ_NUM_REFRESH;
/* End of Added by guojianjun178934, 2013/3/2   问题单号:20130118_01 */

/*OSPF NSR消息统计数据结构*/
/*OSPF NSR备份消息统计*/
typedef struct nsr_ospf_backup_msg_stat
{   
    NBB_ULONG control_msg[NSR_OSPF_BACKUP_MAX];
    NBB_ULONG data_msg[NSR_OSPF_BACKUP_MSG_MAX];
}NSR_OSPF_BACKUP_MSG_STAT;

/*OSPF NSR备份恢复消息统计*/
typedef struct nsr_ospf_restore_msg_stat
{   
    NBB_ULONG control_msg[NSR_OSPF_RESTORE_MAX];
    NBB_ULONG data_msg;
}NSR_OSPF_RESTORE_MSG_STAT;

/*OSPF NSR备份平滑消息统计*/
typedef struct nsr_ospf_smooth_msg_stat
{   
    NBB_ULONG control_msg[NSR_OSPF_SMOOTH_MAX];
    NBB_ULONG data_msg;
}NSR_OSPF_SMOOTH_MSG_STAT;

/*OSPF NSR消息统计数据*/
typedef struct nsr_ospf_msg_stat
{
    NSR_OSPF_BACKUP_MSG_STAT backup_msg_stat[NSR_OSPF_MSG_DIRECT_MAX];
    NSR_OSPF_RESTORE_MSG_STAT restore_msg_stat[NSR_OSPF_MSG_DIRECT_MAX];
    NSR_OSPF_SMOOTH_MSG_STAT smooth_msg_stat[NSR_OSPF_MSG_DIRECT_MAX];
}NSR_OSPF_MSG_STAT;

/*OSPF NSR性能数据统计*/
typedef struct nsr_ospf_performance_data
{
    NBB_ULONG start_time;
    NBB_ULONG end_time;
}NSR_OSPF_PERFORMANCE_DATA;

/*OSPF NSR备份恢复性能统计数据*/
typedef struct nsr_ospf_restore_performance_stat
{
    NSR_OSPF_PERFORMANCE_DATA restore_perf;
    NSR_OSPF_PERFORMANCE_DATA last_restore_unpacket_perf;
    NBB_ULONG total_restore_unpacket_time;
}NSR_OSPF_RESTORE_PERFORMANCE_STAT;

/*OSPF NSR性能统计数据*/
typedef struct nsr_ospf_performance_stat
{
    NSR_OSPF_RESTORE_PERFORMANCE_STAT restore_perf_stat;
}NSR_OSPF_PERFORMANCE_STAT;

/*OSPF NSR统计数据*/
typedef struct nsr_ospf_statistics
{
    NSR_OSPF_MSG_STAT nsr_ospf_msg_stat;
    NSR_OSPF_PERFORMANCE_STAT nsr_ospf_perf_stat;
}NSR_OSPF_STATISTICS;

typedef struct nsr_ospf_adp_statistics
{
    NBB_ULONG backup_control_msg[NSR_OSPF_MSG_DIRECT_MAX][NSR_OSPF_BACKUP_MAX];
    NBB_ULONG smooth_control_msg[NSR_OSPF_MSG_DIRECT_MAX][NSR_OSPF_SMOOTH_MAX];

}NSR_OSPF_ADP_STATISTICS;

typedef struct nsr_ospf_nsr_msg_stat
{
    /*收到消息NSR_OSPF_BACKUP_MSG_START后，会执行删除备份的OSPF进程，所以不统计该消息*/
    NBB_ULONG rcv_backup_data_msg[NSR_OSPF_BACKUP_MSG_MAX];
    NSR_OSPF_RESTORE_MSG_STAT restore_msg_stat[NSR_OSPF_MSG_DIRECT_MAX];
    NSR_OSPF_SMOOTH_MSG_STAT smooth_msg_stat[NSR_OSPF_MSG_DIRECT_MAX];
}NSR_OSPF_NSR_MSG_STAT;

typedef struct if_notify_data
{
    NBB_USHORT if_up_stat;
    NBB_USHORT if_down_stat;
}IF_NOTIFY_DATA;

typedef struct nsr_i3_if_notify_stat
{
    /*Trunk接口上报统计*/
    IF_NOTIFY_DATA trunk_notify_stat;
    /*非Trunk接口上报统计*/
    IF_NOTIFY_DATA no_trunk_notify_stat;
}NSR_I3_IF_NOTIFY_STAT;

typedef struct nsr_i3_data
{
    NBB_BOOL switch_to_master;
    NBB_BOOL if_notify_finish;
    /*倒换后，接口上报结束前上报接口统计*/
    NSR_I3_IF_NOTIFY_STAT if_notify_stat_before_finish;
    /*倒换后，接口上报结束后接口上报统计*/
    NSR_I3_IF_NOTIFY_STAT if_notify_stat_after_finish;
}NSR_I3_DATA;

#endif
