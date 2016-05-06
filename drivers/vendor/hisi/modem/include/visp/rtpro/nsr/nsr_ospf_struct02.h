/*******************************************************************************
*
*
*                Copyright 2013, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              nsr_ospf_struct02.h
*
*  Project Code: Dopra V3R2
*   Module Name: OSPF NSR数据结果定义(2)    
*  Date Created: 2013-10-11
*        Author: guojianjun178934
*   Description: 该头文件中定义的数据结构既可以依赖NBase的基础数据结构，
*                也可以依赖OSPF内部数据结构 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2013-10-11   guojianjun178934        Create
*
*******************************************************************************/
#ifndef NSR_OSPF_STRUCT02_INCLUDED
#define NSR_OSPF_STRUCT02_INCLUDED

/*OSPF备份数据定义*/
typedef struct nsr_ospf_entity_repl
{
    /*当前生效的Router ID*/
#define NSR_REPL_QOPM_ENT_CUR_ROUTER_ID 1
    NBB_BYTE current_router_id_repl[QOPM_ID_LEN];

    /*当前的MD5序号*/
#define NSR_REPL_QOPM_ENT_SEQ_NUM 2
    NBB_ULONG crypto_seq_num_repl;

#define NSR_REPL_ENT_OPER_STATUS 3
    NBB_BYTE oper_status_repl;
}NSR_OSPF_ENTITY_REPL;

typedef struct nsr_ospf_area_repl
{
#define NSR_REPL_AREA_OPER_STATUS 1
    NBB_BYTE oper_status_repl;
}NSR_OSPF_AREA_REPL;


typedef struct nsr_ospf_interface_repl
{
    /*接口状态机状态*/
#define NSR_REPL_IF_FSM_STATE 1
    NBB_LONG state_repl;

    /*接口选举的DR*/
#define NSR_REPL_IF_DR 2
    NBB_BYTE designated_router_repl[QOPM_ID_LEN];

    /*接口选举的BDR*/
#define NSR_REPL_IF_BDR 3
    NBB_BYTE backup_designated_router_repl[QOPM_ID_LEN];

    /*接口所处区域的ID,该值只有在接口同区域关联时才生效*/
#define NSR_REPL_IF_PARENT_AREA_ID 4
    NBB_BYTE parent_area_id_repl[4];

#define NSR_REPL_IF_PARENT_AREA_EXIST 5
    NBB_BOOL parent_area_exist;

    /*接口类型*/
#define NSR_REPL_IF_TYPE 6
    NBB_LONG if_type_repl;

    /*接口的操作状态*/
#define NSR_REPL_IF_OPER_STATUS 7
    NBB_BYTE oper_status_repl;

}NSR_OSPF_INTERFACE_REPL;

typedef struct nsr_ospf_neighbor_repl
{
    /*邻居状态机状态*/
#define NSR_REPL_NBR_FSM_STATE 1
    NBB_LONG state_repl;

    /*邻居选举出的DR*/
#define NSR_REPL_NBR_DR 2
    NBB_BYTE designated_router_repl[QOPM_ID_LEN];

    /*邻居选举出的BDR*/
#define NSR_REPL_NBR_BDR 3
    NBB_BYTE backup_designated_router_repl[QOPM_ID_LEN];

    /*最后收到的DD序号*/
#define NSR_REPL_NBR_LAST_DD_SEQ_NUM 4
    NBB_ULONG last_dd_seq_num_repl;

    /*最后收到的DD选项*/
#define NSR_REPL_NBR_LSAT_DD_OPTIOINS 5
    NBB_BYTE last_dd_options_repl;

    /*最后收到的DD标识*/
#define NSR_REPL_NBR_LAST_DD_FLSGS 6
    NBB_BYTE last_dd_flags_repl;

    /*邻居标记(动态/永久)*/
#define NSR_REPL_NBR_PERMANENCE 7
    NBB_LONG permanence_repl;

    /*邻居对应的Router ID*/
#define NSR_REPL_NBR_ROUTER_ID 8
    NBB_BYTE rtr_id_repl[4];

    /*邻居的优先级*/
#define NSR_REPL_NBR_PRIORITY 9
    NBB_BYTE priority_repl;

    /*父接口的地址*/
#define NSR_REPL_PARENT_IF_ADDR 10
    ATG_INET_ADDRESS parent_if_ip_address_repl;

    /*同邻居的邻接关系*/
#define NSR_REPL_NBR_FRIEND_STATUS 11
    NBB_BYTE friend_status_repl;

#define NSR_REPL_NBR_OPER_STATUS 12
    NBB_BYTE oper_status_repl;

  /*邻居Helper状态机状态*/
#define NSR_REPL_NBR_RESTART_HELPER_FSM_STATE 13
    NBB_BYTE nbr_restart_helper_fsm_state_repl;
}NSR_OSPF_NEIGHBOR_REPL;

typedef struct nsr_ospf_repl_process_key
{
    NBB_USHORT process_id;
}NSR_OSPF_REPL_PROCESS_KEY;

typedef struct nsr_ospf_repl_area_key
{
    NBB_BYTE area_id[4];
}NSR_OSPF_REPL_AREA_KEY;

typedef struct nsr_ospf_repl_if_key
{
    ATG_INET_ADDRESS ip_address;
}NSR_OSPF_REPL_IF_KEY;

typedef struct nsr_ospf_repl_nbr_key
{
    NBB_LONG nbr_if_type; 
    NBB_BYTE router_id[QOPM_ID_LEN];
    ATG_INET_ADDRESS ip_addr;
}NSR_OSPF_REPL_NBR_KEY;

typedef struct nsr_ospf_repl_lsdb_key
{
    QOPM_LSA_HEADER lsa_header;
    NSR_OSPF_REPL_AREA_KEY area_key;
}NSR_OSPF_REPL_LSDB_KEY;

struct nsr_ospf_restore_cb;

/*NSR模块OSPF备份业务统计*/
typedef struct nsr_ospf_nsr_business_stat
{
    NBB_USHORT area_count;
    NBB_USHORT if_count;    
    NBB_USHORT nbr_count;
    NBB_USHORT nbr_in_state_count[QOAM_NBR_NUM_STATES + 1];
    NBB_ULONG  lsa_count;
    NBB_ULONG lsa_type_count[QOPM_MAX_AREA_LS_TYPE + 1];
}NSR_OSPF_NSR_BUSINESS_STAT;

typedef struct nsr_ospf_nsr_statistics
{
    NSR_OSPF_NSR_MSG_STAT ospf_nsr_msg_stat;
    NSR_OSPF_NSR_BUSINESS_STAT ospf_nsr_business_stat;
}NSR_OSPF_NSR_STATISTICS;


typedef struct nsr_ospf_entity
{
    NSR_OSPF_REPL_PROCESS_KEY repl_process_key;
    NSR_OSPF_ENTITY_REPL nsr_ospf_ent_repl;
    NBB_LQE entity_lqe; 
    AVLL_TREE active_repl_area_tree;
    AVLL_TREE glob_repl_if_tree;
    AVLL_TREE glob_repl_nbr_tree;
    AVLL_TREE repl_type5_lsdb_tree;
    NSR_OSPF_BACKUP_INFO backup_info;       /*OSPF批量备份结果*/
    NSR_OSPF_RESTORE_INFO restore_info;     /*OSPF备份恢复处理结果*/
    NSR_OSPF_SMOOTH_INFO smooth_info;       /*OSPF平滑处理结果*/
    struct nsr_ospf_restore_cb *restore_cb;
    NSR_OSPF_NSR_STATISTICS ospf_nsr_stat;
    NBB_BYTE restore_flag;    /*备份恢复标识*/
}NSR_OSPF_ENTITY;

typedef struct nsr_ospf_area_cb
{
    NSR_OSPF_REPL_AREA_KEY repl_area_key;
    AVLL_NODE active_repl_area_tree_node;
    AVLL_TREE repl_if_tree;
    AVLL_TREE repl_lsdb_type_tree[QOPM_MAX_AREA_LS_TYPE+1];
    NBB_ULONG  lsa_count;
    NBB_USHORT lsa_type_count[QOPM_MAX_AREA_LS_TYPE + 1];
    NBB_BYTE restore_flag;    /*备份恢复标识*/
}NSR_OSPF_AREA_CB;

typedef struct nsr_ospf_if_cb
{
    NSR_OSPF_REPL_IF_KEY repl_if_key;
    NSR_OSPF_INTERFACE_REPL nsr_ospf_if_repl;
    AVLL_NODE glob_repl_if_tree_node;
    AVLL_NODE repl_if_tree_node;
    AVLL_TREE repl_nbr_tree;
    NSR_OSPF_AREA_CB *parent_repl_area_cb;
    NBB_USHORT num_repl_neighbors;    
    NBB_USHORT repl_neighbors_in_state[QOAM_NBR_NUM_STATES + 1];
    NBB_BYTE restore_flag;    /*备份恢复标识*/
}NSR_OSPF_IF_CB;

typedef struct nsr_ospf_nbr_cb
{
    NSR_OSPF_REPL_NBR_KEY repl_nbr_key;
    NSR_OSPF_NEIGHBOR_REPL nsr_ospf_nbr_repl;
    AVLL_NODE glob_repl_nbr_tree_node;
    NSR_OSPF_IF_CB *parent_repl_if_cb;
    AVLL_NODE repl_nbr_tree_node;
    NBB_BYTE restore_flag;    /*备份恢复标识*/
}NSR_OSPF_NBR_CB;

typedef struct nsr_ospf_lsdb_cb
{
    QOPM_LSA_HEADER lsa_header;
    AVLL_NODE repl_lsdb_tree_node;
    NSR_OSPF_AREA_CB *associated_repl_area;
    NBB_BYTE restore_flag;    /*备份恢复标识*/
}NSR_OSPF_LSDB_CB;

typedef struct nsr_ospf_repl_pack_parms
{
  NBB_BYTE cb_type;

  NBB_VOID *cb_ptr;

  NBB_BYTE repl_operation;

  NBB_BOOL pack_entire;

  NBB_BYTE *packed_cb;    /*备份数据起始位置*/
  NBB_ULONG offset;       /*备份数据偏移(已备份数据长度)*/

  NBB_ULONG packed_cb_len;  /*备份数据的长度*/

} NSR_OSPF_REPL_PACK_PARMS;

typedef struct nsr_ospf_repl_unpack_parms
{
  //NBB_BYTE cb_type;

  NBB_VOID *cb_ptr;
  NSR_OSPF_ENTITY *nsr_ospf_ent;
  
  NSR_OSPF_DATA_HEADER *nsr_ospf_data_head;
  //NBB_BOOL pack_entire;

  NBB_BYTE *packed_cb;    /*备份数据起始位置*/
  NBB_ULONG offset;       /*备份数据偏移(已备份数据长度)*/

  NBB_ULONG packed_cb_len;  /*备份数据的长度*/

} NSR_OSPF_REPL_UNPACK_PARMS;

typedef struct nsr_ospf_restore_repl_pack_parms
{
    NBB_BYTE cb_type;
    NBB_VOID *cb_ptr;
    NBB_BYTE *packed_cb;        /*备份数据恢复Buffer的起始位置*/
    NBB_ULONG offset;            /*偏移(已备份恢复的数据长度)*/
    NBB_ULONG packed_cb_len;    /*整改备份数据恢复Buffer的大小*/
} NSR_OSPF_RESTORE_REPL_PACK_PARMS;

typedef struct nsr_ospf_restore_repl_unpack_parms
{
  NBB_VOID *cb_ptr;
  NSR_OSPF_RESTORE_HEADER *nsr_ospf_restore_head;
  //NBB_BOOL pack_entire;

  NBB_BYTE *packed_cb;    /*备份数据起始位置*/
  NBB_ULONG offset;       /*备份数据偏移(已备份数据长度)*/

  NBB_ULONG packed_cb_len;  /*备份数据的长度*/

} NSR_OSPF_RESTORE_REPL_UNPACK_PARMS;

/*备份数据查找函数*/
typedef NSR_OSPF_REPL_CB *(NSR_OSPF_REPL_TRAVERSE_PROC)(NBB_BYTE, NBB_VOID *);
/*备份数据比较函数*/
typedef NBB_INT (NSR_OSPF_REPL_COMPARE_PROC)(NBB_BYTE, NBB_VOID *, NBB_VOID *);
/*备份数据长度计算函数*/
typedef NBB_ULONG (NSR_OSPF_REPL_PACK_LEN_PROC)(NSR_OSPF_REPL_PACK_PARMS *);
/*备份数据打包函数*/
typedef NBB_VOID (NSR_OSPF_REPL_PACK_PROC)(NSR_OSPF_REPL_PACK_PARMS *);
/*备份数据解包函数*/
typedef NBB_ULONG (NSR_OSPF_REPL_UNPACK_PROC)(NSR_OSPF_REPL_UNPACK_PARMS *);
/*备份恢复数据查找函数*/
typedef NBB_VOID *(NSR_OSPF_RESTORE_TRAVERSE_PROC)(NSR_OSPF_ENTITY *, NBB_BYTE, NBB_VOID *);
/*备份恢复数据打包函数*/
typedef NBB_ULONG (NSR_OSPF_RESTORE_REPL_PACK_PROC)(NSR_OSPF_RESTORE_REPL_PACK_PARMS *);
/*备份恢复数据解包函数*/
typedef NBB_ULONG (NSR_OSPF_RESTORE_REPL_UNPACK_PROC)(NSR_OSPF_RESTORE_REPL_UNPACK_PARMS *);
/*备份恢复的OSPF控制块查找函数*/
typedef NBB_VOID *(NSR_OSPF_RESTORED_OSPF_TRAVERSE_PROC)(NBB_BYTE, NBB_VOID *, NBB_BYTE);
/*取消备份恢复的OSPF数据处理函数*/
typedef NBB_ULONG (NSR_OSPF_RESTORED_DATA_CANCEL_PROC)(NBB_VOID *);

/*定义OSPF备份数据操作参数*/
typedef struct nsr_ospf_rep_cb_type_parms
{
    NBB_BYTE cb_type;
    NBB_BOOL need_restore;          /*备份数据是否需要执行备份恢复操作(如:区域不需要恢复)*/
    NBB_BOOL need_restore_cancel;  /*备份恢复数据是否可以取消*/
    NBB_ULONG repl_cb_offset;
    NBB_ULONG repl_cb_key_len;
    NBB_ULONG restore_repl_len;
    //NBB_ULONG pack_len;
    /*OSPF NSR备份数据函数*/
    NSR_OSPF_REPL_TRAVERSE_PROC *nsr_ospf_traverse_proc;
    NSR_OSPF_REPL_COMPARE_PROC *nsr_ospf_compare_proc;
    NSR_OSPF_REPL_PACK_LEN_PROC *nsr_ospf_pack_len_proc;
    NSR_OSPF_REPL_PACK_PROC *nsr_ospf_pack_proc;
    NSR_OSPF_REPL_UNPACK_PROC *nsr_ospf_unpack_proc;
    /*OSPF NSR 备份数据恢复处理函数*/
    NSR_OSPF_RESTORE_TRAVERSE_PROC *nsr_ospf_restore_traverse_proc;
    NSR_OSPF_RESTORE_REPL_PACK_PROC *nsr_ospf_restore_pack_proc;
    NSR_OSPF_RESTORE_REPL_UNPACK_PROC *nsr_ospf_restore_unpack_proc;
    /*OSPF NSR备份恢复数据取消处理函数*/
    NSR_OSPF_RESTORED_OSPF_TRAVERSE_PROC *nsr_ospf_restored_ospf_traverse_proc;
    NSR_OSPF_RESTORED_DATA_CANCEL_PROC *nsr_ospf_restored_data_cancel_proc;
} NSR_OSPF_REP_CB_TYPE_PARMS;

/*定义OSPF备份的数据类型*/
typedef struct nsr_ospf_repl_cb_type
{
    AVL_NODE cb_type_node;

    NBB_LQE entry_lqe;

    NBB_LONG cb_type;

    NBB_ULONG repl_order;

    NSR_OSPF_REP_CB_TYPE_PARMS parms;

} NSR_OSPF_REPL_CB_TYPE;

typedef struct nsr_ospf_backup_cb
{
    NBB_BYTE backup_state;
    NBB_BYTE chatch_up_state;
    NSR_OSPF_REPL_CB_TYPE *catch_up_cb_type_cb;
    NSR_OSPF_REPL_CB *catch_up_repl_cb;
    NSR_OSPF_CONTROL_MSG nsr_ospf_control_msg;
}NSR_OSPF_BACKUP_CB;

typedef struct nsr_ospf_restore_cb
{
    NBB_BYTE restore_status;
    NSR_OSPF_REPL_CB_TYPE *restore_type_cb;
    NBB_VOID *last_restored_cb;
    /*存储备份恢复数据，由OSPF模块分配，收到Get消息后赋值，发送给OSPF模块后设定为Null*/
    ATG_I3_NSR_OSPF_RESTORE_IND *nsr_ospf_restore_ind;
    NSR_OSPF_ENTITY *parent_entry_cb;

}NSR_OSPF_RESTORE_CB;

/*OSPF NSR信息*/
typedef struct nsr_ospf
{
    NBB_BYTE nsr_ospf_status;     /*OSPF NSR状态, 但不包括OSPF备份状态机的状态*/
    NBB_BYTE smooth_exit_reason;
    NBB_BOOL if_finish;           /*ospf进程是否收到if finish消息。*/
    NBB_BOOL nsr_ospf_init;
    NBB_BOOL restore_finish;      /*OSPF的备份数据是否完成恢复*/
    NBB_ULONG replicated_flag;    /*OSPF进程备份数据备份是否备份标识,每次启动OSPF备份更新该标识,默认为0*/
    NBB_ULONG nsr_smooth_period;  /*OSPF NSR平滑周期，倒换后接口上报完成启动
                                    平滑定时器*/
    NBB_TIMER_DATA batchup_timer;
    NSR_OSPF_BACKUP_CB *ospf_backup_cb;
    /*备份恢复邻居延迟删除链表(只有动态邻居需要延迟删除)*/
    NBB_LLQE_ROOT nsr_ospf_nbr_delay_del_proc_list;

    NSR_OSPF_STATISTICS nsr_ospf_stat;    /*OSPF NSR相关的统计数据*/
    
}NSR_OSPF;

typedef struct nsr_ospf_restore_repl_entity
{
    NSR_OSPF_REPL_PROCESS_KEY repl_process_key;
    NSR_OSPF_ENTITY_REPL nsr_ospf_ent_repl;
}NSR_OSPF_RESTORE_REPL_ENTITY;

typedef struct nsr_ospf_restore_repl_area_cb
{
    NSR_OSPF_REPL_AREA_KEY repl_area_key;
}NSR_OSPF_RESTORE_REPL_AREA_CB;

typedef struct nsr_ospf_restore_repl_if_cb
{
    NSR_OSPF_REPL_IF_KEY repl_if_key;
    NSR_OSPF_INTERFACE_REPL nsr_ospf_if_repl;
}NSR_OSPF_RESTORE_REPL_IF_CB;

typedef struct nsr_ospf_restore_repl_nbr_cb
{
    NSR_OSPF_REPL_NBR_KEY repl_nbr_key;
    NSR_OSPF_NEIGHBOR_REPL nsr_ospf_nbr_repl;
}NSR_OSPF_RESTORE_REPL_NBR_CB;

typedef struct nsr_ospf_restore_repl_lsdb_cb
{
    QOPM_LSA_HEADER lsa_header;
    NSR_OSPF_REPL_AREA_KEY area_key;
}NSR_OSPF_RESTORE_REPL_LSDB_CB;


typedef struct nsr_ospf_restored_get_cb
{
    NBB_BYTE restored_get_status;
    NSR_OSPF_REPL_CB_TYPE *restore_type_cb;
    NBB_VOID *last_restored_ospf_cb;
}NSR_OSPF_RESTORED_GET_CB;


#endif
