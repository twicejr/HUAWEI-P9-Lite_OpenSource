#ifndef NSR_OSPF_AREA_INCLUDED
#define NSR_OSPF_AREA_INCLUDED

NBB_INT nsr_ospf_compare_repl_area(NBB_VOID *aa, NBB_VOID *bb);
NBB_BOOL nsr_ospf_define_repl_area(NBB_VOID);
NSR_OSPF_AREA_CB *nsr_ospf_find_repl_area_cb(NSR_OSPF_ENTITY *nsr_ospf_ent, 
                                  NSR_OSPF_REPL_AREA_KEY *repl_area_key);
NBB_INT nsr_ospf_repl_area_compare(NBB_BYTE cb_type,
                              NBB_VOID *cb_a,
                              NBB_VOID *cb_b);
NBB_VOID nsr_ospf_free_repl_area_cb(NSR_OSPF_ENTITY *nsr_ospf_ent, NSR_OSPF_AREA_CB *repl_area_cb);
QOPM_AREA_CB *nsr_ospf_find_area_cb(NSR_OSPF_REPL_AREA_KEY *repl_area_key);
NSR_OSPF_AREA_CB *nsr_ospf_repl_area_get_one(NSR_OSPF_ENTITY *nsr_ospf_ent, 
                                                           NSR_OSPF_AREA_CB *prev_repl_area_cb);

#endif

