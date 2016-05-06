/****************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ospf_apiadp.h
*
*  Project Code: VISPV1R7C02
*   Module Name: OSPF  
*   Description: ospf API适配
*   01  定义引用的外部头文件(为了相关模块可以直接引用)
*   02  声明本本模块库全局变量
*   03  声明本本模块库函数
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-11-25   liangjicheng             Create
*  2009-01-20   l00147446               BC3D01126【OSPF】查询函数写越界
*
*******************************************************************************/

#ifndef OSPF_APIADP_H
#define OSPF_APIADP_H

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */
#include "ospf_apiadp_def.h"
#include "ospf_apiadp_stru01.h"
#include "ospf_apiadp_stru02.h"
#include "rpm_type.h"

extern ULONG g_ulOSPFRegFalg;
extern OSPF_PACKET_HOOK_FUNC g_pstOspfInputPktHook;
extern OSPF_PACKET_HOOK_FUNC g_pstOspfOuputPktHook;
extern ULONG g_ulCurProcesses;
extern ULONG g_ulCurAreas;
extern ULONG g_ulMaxAreaNums;
extern OSPF_PROCESS_USED_S g_ulOspfProcessId[]; 
extern ULONG ospf_adp_mutex;
extern OSPF_CFG_LIST_INFO ospf_cfg_list_info;
extern IF_CFG_LIST_INFO if_cfg_list_info;
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
extern NETWORK_CFG_LIST_INFO *network_cfg_list_info;
extern ULONG g_ulOspfMaxVrfNum;
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
extern NBB_ULONG g_ulAreaAsyncDeactivation;

/*Begin BC3D01513 liangjicheng 2009-04-28*/
extern ULONG g_ulOspfMd5Offset;
/*End BC3D01513 */

#if 1

NBB_ULONG ospf_vrpadp_init(NBB_VOID);
NBB_ULONG ospf_add_ospf_process(NBB_ULONG ospf_process_id);
NBB_ULONG ospf_show_ospf_process();
NBB_ULONG ospf_del_ospf_process(NBB_ULONG ospf_process_id);
NBB_ULONG ospf_add_area(NBB_ULONG ospf_process_id, NBB_ULONG area_id);

/*Added by guo00178934, OSPF可维可测增强, 2011/9/6   问题单号:DTS2011091303512 */
NBB_ULONG ospf_area_find(NBB_ULONG ospf_process_id, NBB_ULONG area_id, 
  OSPF_CFG_LIST_ENTRY **ospf_cfg_entry, AREA_CFG_LIST_ENTRY **area_cfg_entry);
/* End of Added by guo00178934, 2011/9/13   问题单号:DTS2011091303512 */

NBB_ULONG ospf_show_area();
NBB_ULONG ospf_del_area(NBB_ULONG ospf_process_id, NBB_ULONG area_id);
NBB_ULONG ospf_set_area_auth(OSPF_CFGAUTHENMODE_S *pstAreaAuthIn);

/*Begin for BC3D02736 接口认证（或区域认证）Keyid值用户可配 l00147446 10-02-27*/
NBB_ULONG ospf_get_area_auth(NBB_ULONG ospf_process_id, 
                             NBB_ULONG area_id,
                             NBB_LONG *auth_type,
                             NBB_ULONG *auth_key_len,
                             NBB_BYTE auth_key_value[256],
                             NBB_BYTE *auth_key_id,
                             NBB_ULONG *auth_user_data_len,
                             NBB_BYTE auth_user_data[4]);
/*End for BC3D02736*/
NBB_ULONG ospf_add_network(NBB_ULONG ospf_process_id, 
                              NBB_ULONG area_id,
                              NBB_ULONG ip_addr,
                              NBB_ULONG prefix_len);
NBB_ULONG ospf_del_network(NBB_ULONG ospf_process_id, 
                              NBB_ULONG area_id,
                              NBB_ULONG ip_addr,
                              NBB_ULONG prefix_len);
NBB_ULONG ospf_get_network(NBB_ULONG ospf_process_id, 
                          NBB_ULONG area_id,
                          NBB_ULONG ulHandle,
                          NBB_ULONG *network_num,
                          NBB_VOID **network_info);
NBB_ULONG ospf_getall_network(NBB_ULONG *network_num,
                              NBB_VOID **network_info);
NBB_ULONG ospf_show_network();

VOID ospf_i3_cfg_if(NBB_ULONG cfg_flag, NBB_CHAR if_name[],NBB_ULONG if_index,NBB_ULONG vrf_index);
VOID ospf_i3_cfg_ifaddr(NBB_ULONG cfg_flag, 
                     NBB_ULONG primary_flag,
                     NBB_ULONG if_index,
                     NBB_ULONG ip_addr,
                     NBB_ULONG ip_mask);

NBB_ULONG ospf_add_second_ifaddr(NBB_ULONG if_index,
                     NBB_ULONG ip_addr,
                     NBB_ULONG prefix_len);

NBB_ULONG ospf_del_second_ifaddr( NBB_ULONG if_index,
                     NBB_ULONG ip_addr,
                     NBB_ULONG prefix_len);

NBB_ULONG ospf_add_ifaddr(NBB_ULONG if_index,
                     NBB_ULONG ip_addr,
                     NBB_ULONG prefix_len);
NBB_ULONG ospf_del_ifaddr( NBB_ULONG if_index,
                     NBB_ULONG ip_addr,
                     NBB_ULONG prefix_len);
NBB_ULONG ospf_add_if(NBB_CHAR if_name[OSPF_MAX_IF_NAME_LENGTH+1],
                     NBB_ULONG if_index,NBB_ULONG vrf_index);


NBB_ULONG ospf_del_if(NBB_ULONG if_index);

IF_CFG_LIST_ENTRY * ospf_get_if_by_index(NBB_ULONG if_index);
NBB_ULONG ospf_show_if();
NBB_ULONG ospf_network_enable_if(NETWORK_CFG_LIST_ENTRY * network_cfg_entry,NBB_ULONG vrf_index);
NBB_ULONG ospf_network_disable_if(NETWORK_CFG_LIST_ENTRY * network_cfg_entry,NBB_ULONG vrf_index);
NBB_ULONG ospf_if_add_to_network(IF_CFG_LIST_ENTRY *if_entry_cb);
NBB_ULONG ospf_if_del_from_network(IF_CFG_LIST_ENTRY *walk_if_entry_cb);

NBB_ULONG ospf_if_matchaclip(NBB_ULONG if_index, NBB_ULONG acl_groupnum, NBB_ULONG ipaddr);
/*End of Modified by lKF35457, 2010/11/16   问题单号:DTS2010110104272  */

OSPF_ERROR_E ospf_cfg_if_cost_mib(USHORT usProcessId,
                               IF_CFG_LIST_ENTRY *if_cfg_list_entry,
                               NBB_LONG row_status);

#endif

#if 2

NBB_VOID OSPF_CMM_Copy_IfInfo(OSPF_SHOWIF_OUT_S *pstOspf_ShowIf,
                                        AMB_OSPF_PM_IF *pstOspfEntity);
VOID OSPF_CMM_Copy_EntityInfo(OSPF_ENTITY_SHOW_S *pstShow,AMB_OSPF_PM_ENT *pstPmEnt);

NBB_VOID OSPF_Fill_ClearOspfProc_Mib(AMB_GEN_IPS *mib_msg,
                          AMB_OSPF_PM_ENT *v_amb_qopm,
                          NBB_ULONG reset_flag,
                          NBB_ULONG gr_flag,
                          NBB_ULONG unplanned_gr_flag,
                          NBB_ULONG gr_period,
                          NBB_ULONG gr_reason,
                          NBB_ULONG row_status);

/*Begin for BC3D02736 接口认证（或区域认证）Keyid值用户可配 l00147446 10-02-27*/
NBB_VOID OSPF_Fill_IfAuthKeyProc_Mib(AMB_GEN_IPS *mib_msg,
                          AMB_OSPF_PM_IF *v_amb_pm_if,
                          NBB_ULONG auth_type,
                          NBB_ULONG auth_key_len,
                          CHAR *auth_key_value,
                          NBB_BYTE auth_key_id,
                          NBB_ULONG user_data_len,
                          CHAR *user_data_value,
                          NBB_ULONG row_status);
/*End for BC3D02736*/

OSPF_ERROR_E OSPF_Get_IfMetricByIfName(ULONG ulProcessId
     , ULONG ulAddrLessIf, ULONG ulIfIndex, OSPF_IF_METRIC_SHOW_S *pstShow);

OSPF_ERROR_E OSPF_CMM_Area_GetAuth(ULONG ulOspfInstance,ULONG ulAreaID,OSPF_AREA_INFO_S *pstAreaAuth);

ULONG OSPF_Judge_Process_Exist(USHORT usProcessId);
OSPF_ERROR_E  OSPF_CFG_JoinToOther(USHORT usProcId,USHORT bUndoConfig,ULONG InterfaceId,ULONG PartnerIndex);




NBB_VOID OSPF_Fill_ClearOspfProc_Mib(AMB_GEN_IPS *mib_msg,
                          AMB_OSPF_PM_ENT *v_amb_qopm,
                          NBB_ULONG reset_flag,
                          NBB_ULONG gr_flag,
                          NBB_ULONG unplanned_gr_flag,
                          NBB_ULONG gr_period,
                          NBB_ULONG gr_reason,
                          NBB_ULONG row_status);
NBB_VOID OSPF_Fill_ClearOspfProc_Mib(AMB_GEN_IPS *mib_msg,
                              AMB_OSPF_PM_ENT *v_amb_qopm,
                              NBB_ULONG reset_flag,
                              NBB_ULONG gr_flag,
                              NBB_ULONG unplanned_gr_flag,
                              NBB_ULONG gr_period,
                              NBB_ULONG gr_reason,
                              NBB_ULONG row_status);

OSPF_ERROR_E OSPF_CFG_OSPF_ENTITY(ULONG ulCfgType,VOID *pstCfgPara,USHORT usProcessId);

OSPF_ERROR_E OSPF_CFG_INTERFACE_MIB(ULONG ulCfgType,
                                                USHORT usProcessId,
                                                ULONG ulAddr_Less_if,
                                                UCHAR *pszIfName,
                                                VOID *pstCfgPara);
OSPF_ERROR_E OSPF_CFG_AREA_MIB(ULONG ulCfgType,
                               ULONG ulProcessId,
                               ULONG ulAreaId,
                               VOID *pstCfgPara);

OSPF_ERROR_E OSPF_Cfg_IP_To_Area(ULONG ulEnableFlg,
                                IF_CFG_LIST_ENTRY * if_cfg_cb);

OSPF_ERROR_E OSPF_CFG_IfEnableOspf(ULONG ulProcessId,UCHAR *pszIfName,ULONG ulEnableOspf);

NBB_LONG ospf_calc_dead_time(QOPM_NBR_CB *cb);
OSPF_ERROR_E OSPF_Direct_GetData_LsdbInfo(QOPM_LSA_HEADER *pstLsa_header, OSPF_SHOW_LSADATA_S *pstLsaData);


#endif
#if 3
NBB_ULONG ospf_yapi_send_ips(NBB_HANDLE conn_handle,
                         NBB_IPS *orig_ips,
                         NBB_IPS **reslut_ips);

ULONG ospf_t_ntoh(UCHAR *pInAddr);
CHAR *ospf_t_htos(ULONG ulIpAddr, CHAR *pStr);
CHAR *ospf_t_ntos(ULONG ulIpAddr, CHAR *pStr);
ULONG  ospf_t_get_sys_seconds();
ULONG ospf_get_processid(IF_CFG_LIST_ENTRY *if_cfg_list_entry);
OSPF_CFG_LIST_ENTRY * ospf_get_process(IF_CFG_LIST_ENTRY *if_cfg_list_entry);
/*End for BC3D03437 at 2010-07-16*/
NBB_VOID  ospf_t_set_if_default (IF_CFG_LIST_ENTRY *if_cfg_list_entry);

NBB_LONG  ospf_t_cmp_network(NBB_ULONG snet,
                                    NBB_ULONG smasklen,
                                    NBB_ULONG dnet,
                                    NBB_ULONG dmasklen);

/*Modified by lKF35457, prevent implicit declaration of function warning, 2010/11/22   问题单号:DTS2010112203622  */
CFG_AUTH_DATA *ospf_cfg_get_if_auth(IF_CFG_LIST_ENTRY *if_cfg_list_entry,
                                NBB_ULONG *pulAuthType);
/*End of Modified by lKF35457, 2010/11/22   问题单号:DTS2010112203622  */

OSPF_ERROR_E ospf_cfg_if_auth_mib(USHORT usProcessId, 
                                        NBB_ULONG ulAuthType,
                                        CFG_AUTH_DATA *pAuthData,
                                        IF_CFG_LIST_ENTRY *if_cfg_list_entry);

OSPF_ERROR_E ospf_cfg_if(NBB_ULONG ulCfgType, 
                                            NBB_CHAR *pszIfName, 
                                            VOID *pstCfgPara);
OSPF_ERROR_E ospf_cfg_if_default_mib(IF_CFG_LIST_ENTRY *if_cfg_list_entry);
NBB_VOID ospf_bfd_rule_refresh(NBB_VOID);/*Added by qinyun62011, for DTS2011022401691, 2011/2/24   问题单号:V2R3C03-ROTUE-MERGE */
NBB_VOID ospf_cmm_if_show_one(ULONG,OSPF_SHOWIF_OUT_S *);
NBB_VOID ospf_cmm_nbr_show_one(ULONG,OSPF_SHOWNBR_OUT_S *);
NBB_VOID ospf_cmm_peer_show_one(ULONG,OSPF_SHOWPEERCFG_OUT_S *);
NBB_VOID ospf_cmm_rt_show_one(ULONG, OSPF_SHOWROUTING_OUT_S *);
NBB_ULONG ospf_cmm_lsdb_show_one(ULONG, USHORT , USHORT  ,OSPF_SHOWLSDB_OUT_S *);
NBB_VOID ospf_cmm_network_show_one(ULONG,OSPF_SHOWNETWORK_OUT_S *);
NBB_VOID ospf_cmm_entity_show_one(ULONG,OSPF_SHOWOSPF_BRIEF_OUT_S *);


NBB_ULONG ospf_cmm_get_proc_dclpid(NBB_ULONG ulProcessId, NBB_ULONG *pulPid);

NBB_ULONG ospf_cmm_proc_get_next(NBB_ULONG ulProcessId);

OSPF_ERROR_E ospf_cmm_if_get_one(ULONG ulHandle,
                                          OSPF_SHOWIF_OUT_S *pstShowIfInfo,
                                          ULONG *pulAdminStatus);
OSPF_ERROR_E ospf_cmm_nbr_get_one(ULONG ulHandle,
                                          VOID *pstOspf_ShowNbr, 
                                          ULONG *pulPermanence);
NBB_VOID ospf_cmm_cumul_clear_one(NBB_ULONG ulProcessId);
NBB_ULONG ospf_cmm_cumul_get_one_area(ULONG ulHandle, VOID * pstCumulOut);
OSPF_ERROR_E ospf_cmm_cumul_get_one_entity(ULONG ulHandle, OSPF_SHOWCUMLTVE_OUT_S * pstCumulOut);

NBB_VOID ospf_cmm_cumul_show_one(NBB_ULONG ulPrintIndex, OSPF_SHOWCUMLTVE_OUT_S * psIn);
/*Begin BC3D03300 新增 API 申明： OSPF_CMM_Error_Clear L00147446 10-06-23*/
NBB_VOID ospf_cmm_error_clear_one(NBB_ULONG ulProcessId);
/*End for BC3D03300*/
NBB_ULONG ospf_cmm_error_get_one(NBB_ULONG ulSessionId, OSPF_SHOWERROR_OUT_S * pstErrorOut);
NBB_VOID ospf_cmm_error_show_one(NBB_ULONG ulPrintIndex, OSPF_SHOWERROR_OUT_S * pstInfo);

OSPF_ERROR_E ospf_cmm_rt_get_one(USHORT usProcId,
                                                ULONG ulHandle,
                                                OSPF_SHOWROUTING_OUT_S *pstOspfRts,
                                                ULONG *pulDestType);
OSPF_ERROR_E ospf_cmm_lsdb_get_one(ULONG ulHandle, OSPF_SHOWLSDB_OUT_S * pstLsdbOut);
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
OSPF_ERROR_E ospf_cmm_network_get_one(NBB_ULONG ulHandle,OSPF_SHOWNETWORK_OUT_S * pstNetworkOut,NBB_ULONG ulVrfIndex);
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
OSPF_ERROR_E ospf_cmm_entity_get_one(ULONG ulHandle,
                                               OSPF_SHOWOSPF_BRIEF_OUT_S *pstShow);

NBB_VOID ospf_cmm_show_head1(CHAR *pMod, USHORT usProc);
NBB_VOID ospf_cmm_show_head2(CHAR *pMod, USHORT usProc, ULONG ulType);
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
NBB_VOID ospf_cmm_show_head3(CHAR *pMod, USHORT usProc,CHAR *szVrfName);
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
NBB_VOID ospf_cmm_show_tail(CHAR *pMod);
NBB_VOID ospf_cmm_show_erropen(CHAR *pMod, ULONG ulRet);
NBB_VOID ospf_cmm_show_noentry(CHAR *pMod);
NBB_VOID ospf_cmm_show_line(CHAR *pLine);
NBB_VOID ospf_cmm_show_total(ULONG ulCount);

VOID ospf_cmm_import_show_one(OSPF_SHOWIMPORT_OUT_S  *pstConfigInfo);
VOID ospf_cmm_filter_show_one(OSPF_SHOWPLCYDIST_OUT_S  *pstConfigInfo);

/* Modified by guo00178934, OSPF Fortify分析：ospf_10_01, 2012/4/9   问题单号:fortify_ospf */
/* 快速down标记 for CGP BC3D02904*/
/*End of Modified by guo00178934, 2012/4/9   问题单号:fortify_ospf */

#endif

ULONG ospf_t_is_valid_ipaddr(ULONG ulHostIpAddr);
NBB_ULONG ospf_is_import_external_route(NBB_USHORT usProcessId);
NBB_ULONG ospf_cfg_asbr_flag(NBB_USHORT usProcessId,NBB_USHORT usAsbrFlg);

NBB_ULONG ospf_add_ospf_process_grhelper(NBB_ULONG ospf_process_id,
                                                     NBB_ULONG ulHelperMode,
                                                     NBB_ULONG ulGrPeriod,
                                                     NBB_ULONG ulAccNum);
OSPF_ERROR_E ospf_cmm_area_get_one(OSPF_AREA_KEY_S **ppstIndex,
                                          OSPF_SHOW_AREA_S *pstShow);
/*add by lkf35460 问题单号：DTS2011040603509*/
NBB_ULONG  ospf_get_default_if_priority(NBB_BYTE *pucDftPrity);
NBB_ULONG  ospf_get_default_if_cost(NBB_ULONG *pulDftCost);
ULONG ospf_get_processid_by_intf(ULONG ulIfIndex, ULONG *pulProcId);
/*end add by lkf35460 问题单号：DTS2011040603509*/


/*Added by qinyun62011, ospf for vrf, 2011/6/22   问题单号:OSPF_20110622_01 */
/*NBB_ULONG ospf_add_nm_process_mib(NBB_USHORT usProcessId);*/
NBB_ULONG ospf_add_nm_process_mib(NBB_USHORT usProcessId,NBB_ULONG sck_index);
/* End of Added by qinyun62011, 2011/6/22   问题单号:OSPF_20110622_01 */
NBB_ULONG ospf_del_nm_process_mib(NBB_USHORT usProcessId);
NBB_ULONG ospf_get_join_proc_by_vrfindex(NBB_ULONG vrf_index,
                                    NBB_ULONG *rtm_index,
                                    NBB_ULONG *i3_index,
                                    NBB_ULONG *sck_index);
/*Modified by liangjicheng 00103192, NBR, 2011/6/23   问题单号:OSPF_20110620_01 */
OSPF_ERROR_E ospf_cmm_nbr_get_exact(NBB_ULONG ulProcessId, NBB_ULONG ulNbrIP);
/*End of Modified by liangjicheng 00103192, 2011/6/23   问题单号:OSPF_20110620_01 */

/*Modified by liangjicheng 00103192, 增加动态邻居删除广播接口和P2P接口的处理, 2011/7/2   问题单号:DTS2011062804135  */
OSPF_ERROR_E ospf_cmm_nbr_del_dynamic(NBB_ULONG ulProcessId, NBB_ULONG ulNbrIP);
/*End of Modified by liangjicheng 00103192, 2011/7/2   问题单号:DTS2011062804135  */

/*Added by guo00178934, 全系统邻居、LSA个数统计, 2011/7/19   问题单号:DTS2011071901386 */
ULONG OSPF_CMM_NbrCount(USHORT usProcId, ULONG *pulNbrCount);
/* End of Added by guo00178934, 2011/7/19   问题单号:DTS2011071901386 */

/*Added by guo00178934, OSPF可维可测增强, 2011/9/6   问题单号:DTS2011091303512 */
#define OSPF_API_LOG_COUNT  50
#define OSPF_API_NAME_LENGTH  50
#define OSPF_API_LOG_MEMBERS 4
#define OSPF_API_LOG_RECORDS 256
/*Added by guo00178934, 防止输出越界, 2011/12/27   问题单号:DTS2011122703877 */
#define OSPF_API_LOG_PRINT 5
/* End of Added by guo00178934, 2011/12/27   问题单号:DTS2011122703877 */

#define OSPF_API_LOG_LOCATE(idx)  \
    (idx) * OSPF_API_LOG_MEMBERS

typedef struct tagOSPF_API_LOG_TAG
{
    NBB_CHAR *name;
    NBB_USHORT ustag;
} OSPF_API_LOG_TAG;

#define OSPF_API_LOG_SET_API_TAG(p, api_tag)  \
    (p) |= ((api_tag) & 0x0000ffff) << 16

#define OSPF_API_LOG_GET_API_TAG(p, api_tag)  \
    (api_tag) = ((p) >> 16) & 0x0000ffff

#define OSPF_API_LOG_SET_RETURN_CODE(p, rc) \
    (p) |= ((rc) & (~MID_COMP_OSPF)) & 0x0000ffff
  
#define OSPF_API_LOG_GET_RETURN_CODE(p, rc) \
    (rc) = ((p) & 0x0000ffff) | MID_COMP_OSPF

#define OSPF_API_LOG_SET_TAG(p, tag)  \
    (p) |= ((tag) & 0x0000000f) << 28

#define OSPF_API_LOG_GET_TAG(p, tag)  \
    (tag) = ((p) >> 28) & 0x0000000f

#define OSPF_API_LOG_SET_OPTION(p, option)  \
    (p) |= ((option) & 0x00000fff) << 16

#define OSPF_API_LOG_GET_OPTION(p, option)  \
    (option) = ((p) >> 16) & 0x00000fff

#define OSPF_API_LOG_SET_PID(p, pid)  \
  (p) |= ((pid) & 0x0000ffff)

#define OSPF_API_LOG_GET_PID(p, pid)  \
    (pid) = (p) & 0x0000ffff

#define OSPF_API_LOG_SET_VALUE(p, value)  \
    (p) = (value)

#define OSPF_API_LOG_GET_VALUE(p, value)  \
    (value) = (p)

/*获取结构体:OSPF_CFGPROC_S成员值*/
#define OSPF_CFGPROC_S_GET_MEMBER(cfg_s, p1, p2, p3)  \
    OSPF_API_LOG_SET_TAG(p1, (cfg_s)->bNoFlag); \
    OSPF_API_LOG_SET_PID(p1, (cfg_s)->usProcessId);  

/*设置结构体:OSPF_CFGPROC_S成员值*/
#define OSPF_CFGPROC_S_SET_MEMBER(cfg_s, p1, p2, p3)  \
    OSPF_API_LOG_GET_TAG(p1, (cfg_s)->bNoFlag); \
    OSPF_API_LOG_GET_PID(p1, (cfg_s)->usProcessId); 

/*打印结构体:OSPF_CFGPROC_S成员值*/
#define OSPF_CFGPROC_S_SHOW_MEMBER(cfg_s, pszStrPrint, i32Offset, size) \
    (i32Offset) += TCPIP_SNPRINTF((pszStrPrint) + (i32Offset), (size) - (i32Offset), P0("\nShow OSPF_CFGPROC_S Members:"));  \
    (i32Offset) += TCPIP_SNPRINTF((pszStrPrint) + (i32Offset), (size) - (i32Offset), P1("\n\tusProcessId:%u", (cfg_s)->usProcessId));  \
    (i32Offset) += TCPIP_SNPRINTF((pszStrPrint) + (i32Offset), (size) - (i32Offset), P1("\n\tbNoFlag:%u", (cfg_s)->bNoFlag));  \
    (i32Offset) += TCPIP_SNPRINTF((pszStrPrint) + (i32Offset), (size) - (i32Offset), P0("\n\tszVrfName:(no log)\n"));

/*获取结构体:OSPF_CFGAREA_LOG_S成员值*/
#define OSPF_CFGAREA_LOG_S_GET_MEMBER(cfg_s, p1, p2, p3)  \
    OSPF_API_LOG_SET_TAG(p1, (cfg_s)->bNoFlag); \
    OSPF_API_LOG_SET_PID(p1, (cfg_s)->usProcessId); \
    OSPF_API_LOG_SET_VALUE(p2, (cfg_s)->ulAreaId);  \
    OSPF_API_LOG_SET_VALUE(p3, (cfg_s)->ulAreaStatus);

/*设置结构体:OSPF_CFGAREA_LOG_S成员值*/
#define OSPF_CFGAREA_LOG_S_SET_MEMBER(cfg_s, p1, p2, p3)  \
    OSPF_API_LOG_GET_TAG(p1, (cfg_s)->bNoFlag); \
    OSPF_API_LOG_GET_PID(p1, (cfg_s)->usProcessId); \
    OSPF_API_LOG_GET_VALUE(p2, (cfg_s)->ulAreaId);  \
    OSPF_API_LOG_GET_VALUE(p3, (cfg_s)->ulAreaStatus); 

/*打印结构体:OSPF_CFGAREA_LOG_S成员值*/
#define OSPF_CFGAREA_LOG_S_SHOW_MEMBER(cfg_s, pszStrPrint, i32Offset, size) \
    (i32Offset) += TCPIP_SNPRINTF((pszStrPrint) + (i32Offset), (size) - (i32Offset), P0("\nShow OSPF_CFGPROC_S Members:"));  \
    (i32Offset) += TCPIP_SNPRINTF((pszStrPrint) + (i32Offset), (size) - (i32Offset), P1("\n\tulAreaId:%#x", (cfg_s)->ulAreaId)); \
    (i32Offset) += TCPIP_SNPRINTF((pszStrPrint) + (i32Offset), (size) - (i32Offset), P1("\n\tbNoFlag:%u", (cfg_s)->bNoFlag));  \
    (i32Offset) += TCPIP_SNPRINTF((pszStrPrint) + (i32Offset), (size) - (i32Offset), P1("\n\tusProcessId:%u", (cfg_s)->usProcessId)); \
    (i32Offset) += TCPIP_SNPRINTF((pszStrPrint) + (i32Offset), (size) - (i32Offset), P1("\n\trow_status:%u ", OSPF_MIB_AREA_ROW_STATUS((cfg_s)->ulAreaStatus))); \
    (i32Offset) += TCPIP_SNPRINTF((pszStrPrint) + (i32Offset), (size) - (i32Offset), P1("admin_status:%u ", OSPF_MIB_AREA_ADMIN_STATUS((cfg_s)->ulAreaStatus))); \
    (i32Offset) += TCPIP_SNPRINTF((pszStrPrint) + (i32Offset), (size) - (i32Offset), P1("oper_status:%u ", OSPF_MIB_AREA_OPER_STATUS((cfg_s)->ulAreaStatus))); \
    (i32Offset) += TCPIP_SNPRINTF((pszStrPrint) + (i32Offset), (size) - (i32Offset), P1("ambl_state:%u\n", OSPF_MIB_AREA_AMBL_STATUS((cfg_s)->ulAreaStatus))); 

/*获取结构体:OSPF_CFGPROC_WITHRID_S成员值*/
#define OSPF_CFGPROC_WITHRID_S_GET_MEMBER(cfg_s, p1, p2, p3)  \
    OSPF_API_LOG_SET_TAG(p1, (cfg_s)->bNoFlag); \
    OSPF_API_LOG_SET_PID(p1, (cfg_s)->usProcessId); \
    OSPF_API_LOG_SET_VALUE(p2, (cfg_s)->ulRouterId);  

/*设置结构体:OSPF_CFGPROC_WITHRID_S成员值*/
#define OSPF_CFGPROC_WITHRID_S_SET_MEMBER(cfg_s, p1, p2, p3)  \
    OSPF_API_LOG_GET_TAG(p1, (cfg_s)->bNoFlag); \
    OSPF_API_LOG_GET_PID(p1, (cfg_s)->usProcessId); \
    OSPF_API_LOG_GET_VALUE(p2, (cfg_s)->ulRouterId); 

/*打印结构体:OSPF_CFGPROC_WITHRID_S成员值*/
#define OSPF_CFGPROC_WITHRID_S_SHOW_MEMBER(cfg_s, pszStrPrint, i32Offset, size) \
    (i32Offset) += TCPIP_SNPRINTF((pszStrPrint) + (i32Offset), (size) - (i32Offset), P0("\nShow OSPF_CFGPROC_WITHRID_S Members:"));  \
    (i32Offset) += TCPIP_SNPRINTF((pszStrPrint) + (i32Offset), (size) - (i32Offset), P1("\n\tulRouterId:%#x", (cfg_s)->ulRouterId)); \
    (i32Offset) += TCPIP_SNPRINTF((pszStrPrint) + (i32Offset), (size) - (i32Offset), P1("\n\tusProcessId:%u", (cfg_s)->usProcessId));  \
    (i32Offset) += TCPIP_SNPRINTF((pszStrPrint) + (i32Offset), (size) - (i32Offset), P1("\n\tbNoFlag:%u", (cfg_s)->bNoFlag)); \
    (i32Offset) += TCPIP_SNPRINTF((pszStrPrint) + (i32Offset), (size) - (i32Offset), P0("\n\tszVrfName:(no log)\n")); 
  
/*获取结构体:OSPF_CFGAREANSSA_S成员值*/
#define OSPF_CFGAREANSSA_S_GET_MEMBER(cfg_s, p1, p2, p3)  \
    OSPF_API_LOG_SET_TAG(p1, (cfg_s)->bNoFlag); \
    OSPF_API_LOG_SET_PID(p1, (cfg_s)->usProcessId); \
    OSPF_API_LOG_SET_OPTION(p1, (cfg_s)->ucNssaOption); \
    OSPF_API_LOG_SET_VALUE(p2, (cfg_s)->ulAreaId);  

/*设置结构体:OSPF_CFGAREANSSA_S成员值*/
#define OSPF_CFGAREANSSA_S_SET_MEMBER(cfg_s, p1, p2, p3)  \
    OSPF_API_LOG_GET_TAG(p1, (cfg_s)->bNoFlag); \
    OSPF_API_LOG_GET_PID(p1, (cfg_s)->usProcessId); \
    OSPF_API_LOG_GET_OPTION(p1, (cfg_s)->ucNssaOption); \
    OSPF_API_LOG_GET_VALUE(p2, (cfg_s)->ulAreaId);  

/*打印结构体:OSPF_CFGAREANSSA_S成员值*/
#define OSPF_CFGAREANSSA_S_SHOW_MEMBER(cfg_s, pszStrPrint, i32Offset, size)  \
    (i32Offset) += TCPIP_SNPRINTF((pszStrPrint) + (i32Offset), (size) - (i32Offset), P0("\nShow OSPF_CFGAREANSSA_S Members:"));  \
    (i32Offset) += TCPIP_SNPRINTF((pszStrPrint) + (i32Offset), (size) - (i32Offset), P1("\n\tbNoFlag:%u", (cfg_s)->bNoFlag));  \
    (i32Offset) += TCPIP_SNPRINTF((pszStrPrint) + (i32Offset), (size) - (i32Offset), P1("\n\tusProcessId:%u", (cfg_s)->usProcessId));  \
    (i32Offset) += TCPIP_SNPRINTF((pszStrPrint) + (i32Offset), (size) - (i32Offset), P1("\n\tulAreaId:%#x", (cfg_s)->ulAreaId)); \
    (i32Offset) += TCPIP_SNPRINTF((pszStrPrint) + (i32Offset), (size) - (i32Offset), P1("\n\tucNssaOption:%#x\n", (cfg_s)->ucNssaOption)); 

/*获取结构体:OSPF_CFGAREASTUB_S成员值*/
#define OSPF_CFGAREASTUB_S_GET_MEMBER(cfg_s, p1, p2, p3)  \
    OSPF_API_LOG_SET_TAG(p1, (cfg_s)->bNoFlag); \
    OSPF_API_LOG_SET_PID(p1, (cfg_s)->usProcessId); \
    OSPF_API_LOG_SET_OPTION(p1, (cfg_s)->bNoSummaryFlag); \
    OSPF_API_LOG_SET_VALUE(p2, (cfg_s)->ulAreaId); 

/*设置结构体:OSPF_CFGAREASTUB_S成员值*/
#define OSPF_CFGAREASTUB_S_SET_MEMBER(cfg_s, p1, p2, p3)  \
    OSPF_API_LOG_GET_TAG(p1, (cfg_s)->bNoFlag); \
    OSPF_API_LOG_GET_PID(p1, (cfg_s)->usProcessId); \
    OSPF_API_LOG_GET_OPTION(p1, (cfg_s)->bNoSummaryFlag); \
    OSPF_API_LOG_GET_VALUE(p2, (cfg_s)->ulAreaId); 

/*打印结构体:OSPF_CFGAREASTUB_S成员值*/
#define OSPF_CFGAREASTUB_S_SHOW_MEMBER(cfg_s, pszStrPrint, i32Offset, size) \
    (i32Offset) += TCPIP_SNPRINTF((pszStrPrint) + (i32Offset), (size) - (i32Offset), P0("\nShow OSPF_CFGAREASTUB_S Members:"));  \
    (i32Offset) += TCPIP_SNPRINTF((pszStrPrint) + (i32Offset), (size) - (i32Offset), P1("\n\tbNoFlag:%d", (cfg_s)->bNoFlag));  \
    (i32Offset) += TCPIP_SNPRINTF((pszStrPrint) + (i32Offset), (size) - (i32Offset), P1("\n\tbNoSummaryFlag:%d", (cfg_s)->bNoSummaryFlag));  \
    (i32Offset) += TCPIP_SNPRINTF((pszStrPrint) + (i32Offset), (size) - (i32Offset), P1("\n\tulAreaId:%#x", (cfg_s)->ulAreaId)); \
    (i32Offset) += TCPIP_SNPRINTF((pszStrPrint) + (i32Offset), (size) - (i32Offset), P1("\n\tusProcessId:%d\n", (cfg_s)->usProcessId)); 

/*获取结构体:OSPF_CFGNETWORK_S成员值*/
#define OSPF_CFGNETWORK_S_GET_MEMBER(cfg_s, p1, p2, p3) \
    OSPF_API_LOG_SET_TAG(p1, (cfg_s)->bNoFlag); \
    OSPF_API_LOG_SET_PID(p1, (cfg_s)->usProcessId); \
    OSPF_API_LOG_SET_VALUE(p2, (cfg_s)->ulAreaId);  \
    OSPF_API_LOG_SET_VALUE(p3, (cfg_s)->ulNetworkAddr);

/*设置结构体:OSPF_CFGNETWORK_S成员值*/
#define OSPF_CFGNETWORK_S_SET_MEMBER(cfg_s, p1, p2, p3) \
    OSPF_API_LOG_GET_TAG(p1, (cfg_s)->bNoFlag); \
    OSPF_API_LOG_GET_PID(p1, (cfg_s)->usProcessId); \
    OSPF_API_LOG_GET_VALUE(p2, (cfg_s)->ulAreaId);  \
    OSPF_API_LOG_GET_VALUE(p3, (cfg_s)->ulNetworkAddr);

/*打印结构体:OSPF_CFGNETWORK_S成员值*/
#define OSPF_CFGNETWORK_S_SHOW_MEMBER(cfg_s, pszStrPrint, i32Offset, size)  \
    (i32Offset) += TCPIP_SNPRINTF((pszStrPrint) + (i32Offset), (size) - (i32Offset), P0("\nShow OSPF_CFGNETWORK_S Members:")); \
    (i32Offset) += TCPIP_SNPRINTF((pszStrPrint) + (i32Offset), (size) - (i32Offset), P1("\n\tulAreaId:%#x", (cfg_s)->ulAreaId)); \
    (i32Offset) += TCPIP_SNPRINTF((pszStrPrint) + (i32Offset), (size) - (i32Offset), P1("\n\tulNetworkAddr:%#x", (cfg_s)->ulNetworkAddr)); \
    (i32Offset) += TCPIP_SNPRINTF((pszStrPrint) + (i32Offset), (size) - (i32Offset), P0("\n\tulMaskLen:(no log)"));  \
    (i32Offset) += TCPIP_SNPRINTF((pszStrPrint) + (i32Offset), (size) - (i32Offset), P1("\n\tusProcessId:%u", (cfg_s)->usProcessId));  \
    (i32Offset) += TCPIP_SNPRINTF((pszStrPrint) + (i32Offset), (size) - (i32Offset), P1("\n\tbNoFlag:%u\n", (cfg_s)->bNoFlag));

NBB_VOID ospf_api_cfg_error_log(NBB_VOID *ospf_api_cfg_parameter, NBB_ULONG rc, NBB_CHAR *function_name);
NBB_VOID ospf_api_cfg_show_log();
NBB_VOID ospf_api_cfg_show_log_detail(NBB_CONST NBB_USHORT index);
NBB_VOID ospf_debug_helper(NBB_USHORT type, NBB_USHORT p1, NBB_LONG p2, NBB_ULONG p3);


#define OSPF_API_CFG_SHOW_LOG   1
#define OSPF_API_CFG_SHOW_LOG_DETAIL 2
#define OSPF_SHOWENTITYINFO     3
#define OSPF_SHOWAREA_INFO      4
#define OSPF_SHOWERR_INFO       5
/* End of Added by guo00178934, 2011/9/6   问题单号:DTS2011091303512 */

/*Added by guo00178934, 在OSPF上下文中查找Area, 2011/11/25   问题单号:DTS2011092904809  */
ULONG ospf_get_mib_area_ststus(USHORT usProcessId, ULONG ulAreaId);

#define OSPF_MIB_AREA_ROW_STATUS(ulMibAreaStatus) \
  ((ulMibAreaStatus) >> 24 & 0xFF)

#define OSPF_MIB_AREA_ADMIN_STATUS(ulMibAreaStatus) \
  ((ulMibAreaStatus) >> 16 & 0xFF)

#define OSPF_MIB_AREA_OPER_STATUS(ulMibAreaStatus) \
  ((ulMibAreaStatus) >> 8 & 0xFF)

#define OSPF_MIB_AREA_AMBL_STATUS(ulMibAreaStatus) \
  ((ulMibAreaStatus) & 0xFF)

/* End of Added by guo00178934, 2011/11/25   问题单号:DTS2011092904809  */

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif
