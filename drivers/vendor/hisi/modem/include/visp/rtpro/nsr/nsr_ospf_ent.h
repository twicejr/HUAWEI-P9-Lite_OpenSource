#ifndef NSR_OSPF_ENT_INCLUDED
#define NSR_OSPF_ENT_INCLUDED

NBB_INT nsr_ospf_compare_repl_ent(NBB_VOID *aa, NBB_VOID *bb);
NBB_BOOL nsr_ospf_define_repl_ent(NBB_VOID);
NSR_OSPF_ENTITY *nsr_ospf_find_ent_cb(NSR_OSPF_REPL_PROCESS_KEY *repl_ent_key);
NBB_VOID nsr_ospf_free_repl_ent_cb(NSR_OSPF_ENTITY *repl_ent_cb);
NSR_OSPF_ENTITY *nsr_ospf_alloc_init_ent_cb(NBB_VOID);
NSR_OSPF_ENTITY *nsr_ospf_repl_ent_get_one(NSR_OSPF_ENTITY *prev_repl_ent_cb);



#endif
