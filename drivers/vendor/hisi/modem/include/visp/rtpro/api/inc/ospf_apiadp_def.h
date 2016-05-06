/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ospf_apiadp_def.h
*
*  Project Code: VISPV1R7C02
*   Module Name: OSPF  
*   Description: 
*   01 OSPF 适配模块定义的宏
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-11-25   liangjicheng             Create                              
*******************************************************************************/

#ifndef OSPF_APIADP_DEF_H
#define OSPF_APIADP_DEF_H

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#include "ospf_api.h"

#if 1
#define OSPF_ADP_PT_BEGIN           (VOID)TCPIP_SmP(ospf_adp_mutex)
#define OSPF_ADP_PT_END             (VOID)TCPIP_SmV(ospf_adp_mutex)
#else
#define OSPF_ADP_PT_BEGIN
#define OSPF_ADP_PT_END
#endif

#define OSPF_TRUE 1
#define OSPF_FALSE 2

#define OSPF_CFG_ADD 1
#define OSPF_CFG_DEL 0

#define OSPF_F_PRIMARY 1
#define OSPF_F_SECONDARY 0

#define OSPF_IP_STR_LEN 32

#define OSPF_USED 1
#define OSPF_UNUSED 0

/*Begin BC3D01729 质量活动 liangjicheng 2009-07-06*/
#define OSPF_ADMIN_UP 1
#define OSPF_ADMIN_DOWN 0

#define OSPF_IPV4_MAX_MASKLEN   32
#define OSPF_IP_STRING_LEN      32

#define OSPF_PORCESS_ID_MIN  1          /*最小进程号*/
#define OSPF_PORCESS_ID_MAX  0xffff     /*最大进程号*/

#define OSPF_LSA_DELAY_MIN  1           /*最小LSA延时时间 1s*/
#define OSPF_LSA_DELAY_MAX  3600        /*最大LSA延时时间 3600s*/

#define OSPF_MTU_LEN_MIN  46            /*最小MTU长度*/
#define OSPF_MTU_LEN_MAX  1560          /*最大MTU长度*/

#define OSPF_IF_COST_MIN  1             /*最小接口Cost值*/
#define OSPF_IF_COST_MAX  0xffff        /*最大接口Cost值*/


#define OSPF_AREA_RFSH_ITVL_MIN  1      /*最小区域刷新间隔 s*/
#define OSPF_AREA_RFSH_ITVL_MAX  3599   /*最大区域刷新间隔 s*/

#define OSPF_POLL_ITVL_MAX  0xffff      /*最大轮询时间*/

#define OSPF_MIB_TRY_TIMES  4           /*MIB配置尝试次数*/
#define OSPF_MIB_TRY_DELAY  500         /*MIB配置尝试延时时间 ms*/

#define OSPF_AREA_ASYSNC_WAIT_TIMES  20   /*区域配置时异步等待次数*/
#define OSPF_AREA_ASYSNC_WAIT_ITVL   200  /*区域配置时异步等待间隔 ms*/
/*End BC3D01729*/

/*表明区域是否为stub/nssa*/
#define OSPF_GENERAL_AREA 1
#define OSPF_STUB_AREA    2
#define OSPF_NSSA_AREA    3

/*区域的属性*/
#define OSPF_SUMM_NO_AREA_SUMMARY     1
#define OSPF_SUMM_SEND_AREA_SUMMARY   2

/*ADD for BC3D02758 增加默认路由控制 l00147446 10-03-02*/  
#define OSPF_NO_AREA_DEFAULT_LSA  1
#define OSPF_AREA_DEFAULT_LSA     2
/*End for BC3D02758*/

/*Add by q62011 for DTS2010090302774:【OSPF】增加实现 路由器的 no-import-route 选项的功能*/
#define OSPF_AREA_NSSA_NO_IMPORT  1
#define OSPF_AREA_NSSA_IMPORT     2

/*路由聚合时，LSDB类型*/
#define OSPF_LS_SUMMARY_LINK 3
#define OSPF_LS_NSSA_EXTERNAL_LINK 7

/*路由聚合时，effect类型*/
#define OSPF_EFFECT_ADV_MATCHING 1
#define OSPF_EFFECT_DO_NOT_ADV   2

#define OSPF_AREA_ADMIN_STATUS_UP   1
#define OSPF_AREA_ADMIN_STATUS_DOWN 2

/*Added by jijianhua00169178, V2R3C02以上版本为32 个, 2011/3/4   问题单号:DTS2011030203676 */
#define OSPF_MAX_PROCESSES 32          /*最大进程数*/
/* End of Added by jijianhua00169178, 2011/3/4   问题单号:DTS2011030203676 */

/*Begin BC3D01086 liangjicheng 09-01-14*/
#define OSPF_GR_MIN_PERIOD 1          /*最小GR周期时间 1s*/
#define OSPF_GR_MAX_PERIOD 1800       /*最大GR周期时间 1800s*/
/*End BC3D01086 liangjicheng 09-01-14*/

/*Begin BC3D01513 liangjicheng 2009-04-28*/
#define OSPF_CFG_RYTRY_TIMES 5          /*失败重配置次数*/
#define OSPF_CFG_RYTRY_INTERVAL 200     /*失败重配置间隔 ms*/
/*End BC3D01513 */

/*Begin BC3D01513 liangjicheng 2009-04-28*/
#define OSPF_GR_BACKUP_OFFSET  60*60    /*1小时 单位:s*/
/*End BC3D01513 */

#define ERR_NO_ERR                  OSPF_OK
#define ERR_RESOURCE_UNAVAILABLE    OSPF_ERR_NO_MEMORY
#define ERR_CFG_ALREADY_EXIST       OSPF_ERR_CFG_ALREADY_EXIST
#define ERR_CFG_NOT_EXIST           OSPF_ERR_CFG_NOT_EXIST

/*配置ospf entity相关的类型*/
#define OSPF_CFG_ASBR_ROUTER 1
#define OSPF_CFG_CMD_CLEAR_OSPFPROC 2
#define OSPF_CFG_CMD_MAXPATHS 3
#define OSPF_CFG_CMD_ROUTER_OSPF_PROC 4
#define OSPF_CFG_COMP_RFC1583 5
#define OSPF_CFG_SPF_CALC_ITVL 6
#define OSPF_CFG_ROUTER_ID 7
#define OSPF_CFG_ADMIN_STATUS 8
/*Modified by liangjicheng 00103192, Calc Delay, 2011/10/27   问题单号: REQ-201106295399-OSPF-PER */
#define OSPF_CFG_CMD_CALC_DELAY 9

#define OSPF_CALC_DELAY_MIN  1         /*最小延迟时间 ms*/
#define OSPF_CALC_DELAY_MAX  10000     /*最大延迟时间 ms*/
/*End of Modified by liangjicheng 00103192, 2011/10/27   问题单号: REQ-201106295399-OSPF-PER */

/*配置ospf if相关的类型*/
#define OSPF_CFG_IF_AUTHKEY 1
#define OSPF_CFG_IP_DEAD_ITVL 2
#define OSPF_CFG_IP_HELLO_ITVL 3
#define OSPF_CFG_IP_NETWORK 4
#define OSPF_CFG_PASSIVE_IF 5
#define OSPF_CFG_IF_ENABLE 6
#define OSPF_CFG_IF_LSA_DELAY 7
#define OSPF_CFG_IF_POLL_ITVL 8
#define OSPF_CFG_IF_PRIORITY 9
#define OSPF_CFG_INTERFACE_TO_AREA 10
#define OSPF_CFG_IF_MAX_MTU 11
#define OSPF_CFG_AUTO_DEL_NBR 12
#define OSPF_CFG_GR_HELPER 13
#define OSPF_CFG_IF_COST 14
#define OSPF_CFG_IF_RETRANSMIT 15


/*struct id,用于申请内存使用*/
#define SID_OSPF_SHOWIF_KEY_S        100
#define SID_OSPF_LSDB_KEY_S          101
#define SID_OSPF_NBR_KEY_S           102
#define SID_OSPF_ROUTING_KEY_S       103
#define SID_OSPF_VIRTUAL_IF_KEY_S    104
#define SID_OSPF_VIRTUAL_LSDB_KEY_S  105
#define SID_OSPF_VIRTUAL_NBR_KEY_S   106
#define SID_OSPF_CFG_OSPF_CB_S       107
#define SID_OSPF_CFG_AREA_CB_S       108
#define SID_OSPF_CFG_AREA_INFO_S     109
#define SID_OSPF_CFG_AUTH_CB_S       110
#define SID_OSPF_CFG_NETWORK_CB_S    111
#define SID_OSPF_CFG_NETWORK_INFO_S  112
#define SID_OSPF_CFG_IF_CB_S         113
#define SID_OSPF_ENTITY_KEY_S        114
#define SID_OSPF_IF_METRIC_KEY_S     115
#define SID_OSPF_AREA_KEY_S          116
#define SID_OSPF_AREA_AGG_KEY_S      117
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
#define SID_OSPF_INIT                118
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

/*快查引入*/
#define SID_OSPF_DIRECT_NBR_KEY_S      118
#define SID_OSPF_DIRECT_VNBR_KEY_S      119
#define SID_OSPF_DIRECT_LSDB_KEY_S      120
#define SID_OSPF_DIRECT_VLSDB_KEY_S      121

/*配置ospf area相关的类型*/
#define OSPF_CFG_CMD_AREA_NSSA 1
#define OSPF_CFG_AREA_RFSH_ITVL 2
#define OSPF_CFG_CMD_AREA_STUB 3
#define OSPF_CFG_AREA_ADMIN_STATUS 4
#define OSPF_CFG_AREA 5 /*for config area aggregate,you must config the area explicitly via MIB configured,
                            rather than implicitly created by an interface activation,otherwise return error*/

#define OSPF_IN_CLASSA(i) (0 == ((long)(i) & 0x80000000L))
#define OSPF_IN_CLASSB(i) (0x80000000L == ((long)(i) & 0xc0000000L))
#define OSPF_IN_CLASSC(i) (0xc0000000L == ((long)(i) & 0xe0000000L))


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif
