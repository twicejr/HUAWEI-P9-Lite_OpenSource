#ifndef NSR_OSPF_LSDB_INCLUDED
#define NSR_OSPF_LSDB_INCLUDED

NBB_INT nsr_ospf_compare_repl_lsdb(NBB_VOID *aa, NBB_VOID *bb);
NBB_BOOL nsr_ospf_define_repl_lsdb(NBB_VOID);
NBB_ULONG nsr_ospf_free_repl_lsdb_cb(NSR_OSPF_ENTITY *nsr_ospf_ent, 
                                            NSR_OSPF_AREA_CB *nsr_ospf_area_cb, 
                                            NSR_OSPF_LSDB_CB *nsr_ospf_lsdb_cb);
NSR_OSPF_LSDB_CB *nsr_ospf_repl_lsdb_get_one(NSR_OSPF_ENTITY *nsr_ospf_ent, 
                                                            NSR_OSPF_LSDB_CB *prev_repl_lsdb_cb,
                                                            NBB_BYTE lsa_type_filter);
NSR_OSPF_LSDB_CB *nsr_ospf_find_repl_lsdb_cb(NSR_OSPF_ENTITY *nsr_ospf_ent, 
                                                    NSR_OSPF_AREA_CB *nsr_ospf_area_cb, 
                                                    NSR_OSPF_REPL_LSDB_KEY *repl_lsdb_key);



#endif

