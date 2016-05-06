/*******************************************************************************
*
*
*                Copyright 2013, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              nsr_ospf_fun01.h
*
*  Project Code: Dopra V3R2
*   Module Name: OSPF NSR对外提供的OSPF NSR模块间功能函数
*  Date Created: 2013-10-25
*        Author: guojianjun178934
*   Description: 该头文件中提供的函数入参和返回值不依赖OSPF内部定义的数据结构
*                如果有依赖，请在文件nsr_ospf_fun02.h中声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2013-10-25   guojianjun178934        Create
*
*******************************************************************************/
#ifndef NSR_OSPF_FUN01_INCLUDED
#define NSR_OSPF_FUN01_INCLUDED

NBB_ULONG nsr_send_ospf_control_msg(NSR_OSPF_CONTROL_MSG *nsr_ospf_control_msg);
NBB_ULONG nsr_ospf_reply_control_msg(NBB_USHORT process_id, NBB_BYTE msg_type, NBB_BYTE opt_type, NBB_BYTE result);
NBB_VOID qoam_rcv_nsr_ospf_control_msg(ATG_I3_NSR_NOTIFY_OSPF *nsr_notify_data);
NSR_OSPF_REPL_CB *nsr_ospf_get_next_repl_cb(NSR_OSPF_BACKUP_CB *ospf_backup_cb);
NBB_ULONG nsr_ospf_send_backup_control_msg(NBB_SHORT process_id, NBB_BYTE msg_type);
NBB_ULONG nsr_ospf_send_backup_realtime(NBB_SHORT process_id, NSR_OSPF_REPL_CB_TYPE *repl_cb_type, 
                                                          NSR_OSPF_REPL_CB* repl_cb);
NBB_ULONG nsr_ospf_send_backup_batch(NBB_SHORT process_id, NSR_OSPF_BACKUP_CB *backup_cb);
NBB_BOOL nsr_ospf_repl_init(NBB_VOID);
NBB_BOOL ospf_nsr_init(NBB_VOID);
NBB_VOID nsr_ospf_destroy_proc(NBB_VOID);
NBB_ULONG nsr_ospf_batchup_proc(NBB_USHORT process_id, NSR_OSPF_BACKUP_CB *ospf_backup_cb);
NBB_BOOL nsr_ospf_data_init(NSR_OSPF_DATA *nsr_ospf_data);
NBB_BOOL nsr_ospf_rep_define_cb_type(NSR_OSPF_DATA *nsr_ospf_data, 
                                                    NSR_OSPF_REP_CB_TYPE_PARMS *rep_cb_parms);
NBB_ULONG nsr_ospf_backup_operation(NBB_USHORT process_id,
                                                  NSR_OSPF_BACKUP_CB *ospf_backup_cb, 
                                                  NSR_OSPF_REPL_CB *repl_cb,
                                                  NBB_BYTE opreation,
                                                  NBB_BYTE cb_type);

/*以下函数由OSPF模块调用*/
NBB_VOID nsr_ospf_update_repl_if_info(NBB_VOID *prt_cb, NBB_BYTE field_type);
NBB_VOID nsr_ospf_update_repl_ent_info(NBB_VOID *prt_cb, NBB_BYTE field_type);
NBB_VOID nsr_ospf_update_repl_nbr_info(NBB_VOID *prt_cb, NBB_BYTE field_type);
NBB_ULONG nsr_ospf_repl_ent_backup(NBB_VOID *prt_cb, NBB_BYTE opt_type);
NBB_ULONG nsr_ospf_repl_area_backup(NBB_VOID *prt_cb, NBB_BYTE opt_type);
NBB_ULONG nsr_ospf_repl_if_backup(NBB_VOID *prt_cb, NBB_BYTE opt_type);
NBB_ULONG nsr_ospf_repl_nbr_backup(NBB_VOID *prt_cb, NBB_BYTE opt_type);
NBB_ULONG nsr_ospf_repl_lsdb_backup(NBB_VOID *prt_cb, NBB_BYTE opt_type); 
NBB_BOOL nsr_ospf_check_backup_header(NSR_OSPF_BACKUP_HEADER *ospf_backup_header);
NBB_ULONG nsr_receive_backup_data(NBB_BYTE *rcv_buf, NBB_ULONG rcv_buf_len);
NBB_ULONG nsr_rcv_ospf_restore_get_msg(NBB_USHORT process_id, 
                                                       NSR_OSPF_RESTORE_INFO *ospf_restore_info,
                                                       NBB_CHAR *restore_status);
NBB_ULONG nsr_send_ospf_restore_msg(NBB_ULONG process_id, ATG_I3_NSR_OSPF_RESTORE_IND *ospf_restore_ind);
NBB_VOID qoam_rcv_nsr_ospf_restore_msg(ATG_I3_NSR_OSPF_RESTORE_IND *nsr_ospf_restore_ind);
NBB_ULONG nsr_ospf_notify_adp_api_cfg(NBB_USHORT process_id, NBB_ULONG process_operation);
NBB_ULONG nsr_ospf_notify_process_state(NBB_USHORT process_id, NBB_ULONG process_state);
NBB_VOID nsr_ospf_check_smooth_period_expiry(NBB_VOID);
NBB_ULONG nsr_notify_ospf_refersh_md5(NBB_USHORT process_id, NBB_ULONG crypto_seq_num);
NBB_ULONG nsr_ospf_restore_cancel(NBB_VOID);
NBB_VOID nsr_ospf_process_delayed_del_nbr(NBB_VOID);
NBB_VOID nsr_ospf_exit_nsr_smooth(NBB_BYTE smooth_exit_reason);
NBB_VOID nsr_ospf_msg_statistics(NBB_BYTE msg_direct, NBB_BYTE msg_type, 
                                             NBB_BYTE msg_opt, NBB_BYTE sub_opt);
NBB_VOID nsr_ospf_performance_statistics(NBB_BYTE perf_type, NBB_BYTE per_opt);
NBB_VOID nsr_ospf_adp_msg_statistics(NBB_BYTE msg_direct, NBB_ULONG index, NBB_BYTE msg_type, NBB_BYTE msg_opt);
NBB_VOID nsr_ospf_nsr_msg_statistics(NBB_BYTE msg_direct, NSR_OSPF_ENTITY *nsr_ospf_ent_cb, 
                                                   NBB_BYTE msg_type, NBB_BYTE msg_opt, NBB_BYTE sub_type);
NBB_VOID nsr_ospf_destroy_restore_cb(NSR_OSPF_ENTITY *nsr_ospf_ent_cb);
NBB_VOID nsr_ospf_deal_process_status_change(NBB_BYTE status);



#endif

