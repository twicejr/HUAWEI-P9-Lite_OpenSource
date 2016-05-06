#ifndef NSR_OSPF_NBR_INCLUDED
#define NSR_OSPF_NBR_INCLUDED

NBB_INT nsr_ospf_compare_repl_neighbor(NBB_VOID *aa, NBB_VOID *bb);
NBB_BOOL nsr_ospf_define_repl_nbr(NBB_VOID);
NBB_VOID nsr_ospf_free_repl_nbr_cb(NSR_OSPF_ENTITY *nsr_ospf_ent, NSR_OSPF_NBR_CB *repl_nbr_cb);
NSR_OSPF_NBR_CB *nsr_ospf_repl_nbr_get_one(NSR_OSPF_ENTITY *nsr_ospf_ent, 
                                                         NSR_OSPF_NBR_CB *prev_repl_nbr_cb);
NBB_VOID *nsr_ospf_restored_ospf_nbr_traverse(NBB_BYTE repl_cb_type, 
                                                      NBB_VOID *prev_cb, 
                                                      NBB_BYTE restored_flag);
NBB_ULONG nsr_ospf_nbr_cb_restore_cancel(VOID *restored_data);



#endif
