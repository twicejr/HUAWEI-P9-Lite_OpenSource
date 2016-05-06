/*******************************************************************************
*
*
*                Copyright 2013, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              nsr_ospf_fun02.h
*
*  Project Code: Dopra V3R2
*   Module Name: OSPF NSR对外提供的OSPF NSR模块间功能函数
*  Date Created: 2013-10-25
*        Author: guojianjun178934
*   Description: 该头文件中提供的函数入参和返回值需要依赖于OSPF内部定义的数据结构
*                如果不需要依赖，请在文件nsr_ospf_fun01.h中声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2013-10-25   guojianjun178934        Create
*
*******************************************************************************/
#ifndef NSR_OSPF_FUN02_INCLUDED
#define NSR_OSPF_FUN02_INCLUDED

NBB_VOID nsr_ospf_check_pre_start_network(QOPM_IF_CB *if_cb  NBB_CCXT_T NBB_CXT);
NBB_VOID nsr_ospf_check_pre_start_router(QOPM_AREA_CB *area_cb  NBB_CCXT_T NBB_CXT);
NBB_VOID nsr_ospf_check_lsa_consistencies(QOPM_AREA_CB *area_cb);
NBB_ULONG nsr_ospf_nbr_activate(QOPM_NBR_CB *nbr_cb);
NBB_VOID nsr_ospf_process_lsa_for_restart(QOPM_LSDB_CB *db_entry_ptr
                                                          NBB_CCXT_T NBB_CXT);
NBB_VOID nsr_ospf_check_adj_reestablished(NBB_CXT_T NBB_CXT);                                                          

/*判断备份的RouterID同当前的RouterID是否一致*/
#define NSR_VALID_REPL_ROUTER_ID(REPL_RID, CUR_RID) \
  (!QOPM_IS_RTR_ID_ZERO((REPL_RID), QOPM_ID_LEN) && \
   !NBB_MEMCMP((REPL_RID), (CUR_RID), QOPM_ID_LEN))


#endif

