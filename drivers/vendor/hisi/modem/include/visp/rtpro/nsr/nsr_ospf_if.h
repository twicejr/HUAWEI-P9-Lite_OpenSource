#ifndef NSR_OSPF_IF_INCLUDED
#define NSR_OSPF_IF_INCLUDED

NBB_INT nsr_ospf_compare_repl_interface(NBB_VOID *aa, NBB_VOID *bb);
NBB_BOOL nsr_ospf_define_repl_if(NBB_VOID);
NBB_VOID nsr_ospf_free_repl_if_cb(NSR_OSPF_ENTITY *nsr_ospf_ent, NSR_OSPF_IF_CB *repl_if_cb);
QOPM_IF_CB *nsr_ospf_find_if_cb(NSR_OSPF_REPL_IF_KEY *repl_if_key);
NSR_OSPF_IF_CB *nsr_ospf_find_repl_if_cb(NSR_OSPF_ENTITY *nsr_ospf_ent, NSR_OSPF_REPL_IF_KEY *repl_if_key);
NSR_OSPF_IF_CB *nsr_ospf_repl_if_get_one(NSR_OSPF_ENTITY *nsr_ospf_ent, 
                                                     NSR_OSPF_IF_CB *prev_repl_if_cb);
NBB_VOID *nsr_ospf_restored_ospf_if_traverse(NBB_BYTE repl_cb_type, 
                                                              NBB_VOID *prev_cb, 
                                                              NBB_BYTE restored_flag);
NBB_ULONG nsr_ospf_if_cb_restore_cancel(NBB_VOID *restored_data);
NBB_VOID nsr_ospf_check_if_consistency(NBB_VOID);
NBB_BOOL nsr_ospf_is_if_free_for_nbr(NSR_OSPF_IF_CB *nsr_ospf_if_cb,
                                 NSR_OSPF_NBR_CB *nsr_ospf_nbr_cb);

/*判断地址是否有效*/
#define NSR_OSPF_IS_IP_ADDR_VALID(IP_ADDRESS) \
  (NBB_MEMCMP((IP_ADDRESS).address, qoam_unknown_address, QOPM_IP_ADDR_LEN))

/*判断接口地址是否有效*/
#define NSR_OSPF_IS_IF_ADDR_VALID(IF_CB)  \
  (((IF_CB) != NULL) && \
   (NSR_OSPF_IS_IP_ADDR_VALID((IF_CB)->repl.key.ip_address)))

/*判断备份的接口关键字是否有效*/
#define NSR_OSPF_IS_REPL_IF_KEY_VALID(REPL_IF_KEY)  \
  (((REPL_IF_KEY) != NULL) && \
   (NSR_OSPF_IS_IP_ADDR_VALID((REPL_IF_KEY)->ip_address)))
#endif

