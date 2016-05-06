/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ospf_api_def.h
*
*  Project Code: VISPV1R7C02
*   Module Name: OSPF  
*   Description: 
*   01 OSPF API 宏定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-11-25   liangjicheng             Create                              
*******************************************************************************/

#ifndef _OSPF_API_DEF_H
#define _OSPF_API_DEF_H

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/*01 操作标志*/
#define OSPF_NOFLAG_ADD 0
#define OSPF_NOFLAG_DEL 1

#define OSPF_INPUT  1
#define OSPF_OUTPUT 2

#define DF_OSPF_TO_RM 1         /*路由引入方向-OSPF向RM引*/
#define DF_RM_TO_OSPF 2         /*路由引入方向-RM向OSPF引*/

/*02 规格*/
#define OSPF_ENCRYPT_DATA_LENGTH 255
#define OSPF_MAX_IF_NAME_LENGTH 47
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
#define OSPF_MAX_VRF_NAME_LENGTH 31
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
#define OSPF_MAX_EQCOST_PATH 32
#define OSPF_MAX_INET_ADDR_LEN 32

#define OSPF_ARRAY_SIZE_3           3
#define OSPF_LSA_MAX_RTR_PIECE     50
#define OSPF_LSA_MAX_TOS_COUNT     20
#define OSPF_LSA_MAX_NET_NBR       50
#define OSPF_LSA_MAX_SUM_PIECE     10
#define OSPF_LSA_MAX_ASE_PIECE     10
#define OSPF_LSA_MAX_OPQ_DATA      10


/*03 类型定义*/
#define OSPF_ROUTER_LSA           1
#define OSPF_NETWORK_LSA          2
#define OSPF_SUMMARY_LSA          3
#define OSPF_SUMMARY_ASBR_LSA     4
#define OSPF_ASEXTERNAL_LSA       5
#define OSPF_NSSA_LSA             7
#define OSPF_OPAQUE_LOCAL_LSA     9
#define OSPF_OPAQUE_AREA_LSA      10
#define OSPF_OPAQUE_AS_LSA        11
#define  OSPF_LSA_MAX_TYPE        11

/* 04 默认时间 */
#define OSPF_HELLO_INTER_10       10     /* BROADCAST POINT_TO_POINT LOOPBACK */
#define OSPF_HELLO_INTER_30       30     /* NBMA POINT_T_MLTPNT */
#define OSPF_DEAD_INTER_40        40     /* BROADCAST POINT_TO_POINT LOOPBACK */
#define OSPF_DEAD_INTER_120       120    /* NBMA POINT_T_MLTPNT */


#define OSPF_CFG_NSSAOPT_DEFAULT    0x01 /* bring default Type-7LSA to area NSSA  */
#define OSPF_CFG_NSSAOPT_NOIMPORT   0x02 /* no import exterior route to NSSA area */
#define OSPF_CFG_NSSAOPT_NOSUMMARY  0x04 /* forbid ABR send Summary LSA to NSSA area */
/*Add by q62011 for DTS2010090302774:【OSPF】增加实现 路由器的 no-import-route 选项的功能*/
#define OSPF_CFG_NSSAOPT_TRANSLATE_ROLE_ALWAYS 0x08 /*translation of type-7 LSAs into type-5 LSAs.*/


#define OSPF_CFG_IF_AUTH_NULL         0x0
#define OSPF_CFG_IF_AUTH_SIMPLE       0x1
#define OSPF_CFG_IF_AUTH_MD5          0x2
#define OSPF_CFG_IF_AUTH_HMAC         0x3
/*Added by guo00178934, 新增最大有效认证方式定义, 2011/3/3   问题单号:DTS2011030200955  */
#define OSPF_CFG_IF_AUTH_MAX          OSPF_CFG_IF_AUTH_HMAC
/* End of Added by guo00178934, 2011/3/3   问题单号:DTS2011030200955  */
/*Modified by lKF35457, DTS2010101601584  新增未配置认证方式的定义 for v1r8c01, 2010/10/19 */
#define OSPF_CFG_IF_AUTH_NOCFG        0xff 

#define OSPF_IF_PASSWORD_PLAIN        0x01
#define OSPF_IF_PASSWORD_CIPHER       0x02

#define OSPF_AREA_PASSWORD_PLAIN    0x01
#define OSPF_AREA_PASSWORD_CIPHER   0x02

/*Modified by lKF35457, , 2011/5/25   问题单号:OSPF_20110521_01 */
#define OSPF_AUTH_SIMPLE_PW_LEN_MAX   8
#define OSPF_AUTH_MD5_PW_LEN_MAX      255 
/*End of Modified by lKF35457, 2011/5/25   问题单号:OSPF_20110521_01 */

#define OSPF_PREFERENCE_SWITH_INT   0x01
#define OSPF_PREFERENCE_SWITH_EXT   0x02

#define OSPF_CFG_RESET_CFG_GRPARA   0x00
#define OSPF_CFG_RESET_SET_DOWN     0x01
#define OSPF_CFG_RESET_SET_UP       0x02
#define OSPF_CFG_RESET_SET_DOWNUP   0x03

/*Begin BC3D00000 liangjicheng 2009-09-09*/
/*OSPF 接口网络类型 */
#define OSPF_NETWORK_BROADCAST       1
#define OSPF_NETWORK_NBMA            2
#define OSPF_NETWORK_POINT_TO_POINT  3
#define OSPF_NETWORK_POINT_T_MLTPNT  5
#define OSPF_NETWORK_LOOPBACK        10

/*Hitless Restart Reason*/
#define OSPF_RESTART_REASON_UNKNOWN 0
#define OSPF_RESTART_REASON_SOFTWARE_RESTART 1
#define OSPF_RESTART_REASON_SOFTWARE_RELOAD  2
#define OSPF_RESTART_REASON_SWITCH_TO_BACKUP 3

/*Helper Mode*/
#define OSPF_HELP_POLICY_NONE       0x00000000
#define OSPF_HELP_POLICY_UNKNOWN    0x00000001
#define OSPF_HELP_POLICY_SOFTWARE   0x00000002
#define OSPF_HELP_POLICY_RELOAD     0x00000004
#define OSPF_HELP_POLICY_SWITCH     0x00000008
#define OSPF_HELP_POLICY_ALL        0x0000000F
/*End   BC3D00000 liangjicheng 2009-09-09*/

/* 配置/删除 OSPF引如路由的策略*/
typedef enum tagOSPF_RPM_METRICTYPE
{
    OSPF_RPM_MTYPE_INVALID   =   0, 
    OSPF_RPM_MTYPE_INTERNAL  =   1,
    OSPF_RPM_MTYPE_EXTERNAL  =   2,
    OSPF_RPM_MTYPE_TYPE1     =   3,
    OSPF_RPM_MTYPE_TYPE2     =   4
} OSPF_RPM_METRICTYPE_E;

/*Begin BC3D02903 liangjicheng 2010-04-19 */
#define OSPF_NBR_STATE_DOWN                ((LONG)1)
#define OSPF_NBR_STATE_ATTEMPT             ((LONG)2)
#define OSPF_NBR_STATE_INIT                ((LONG)3)
#define OSPF_NBR_STATE_TWO_WAY             ((LONG)4)
#define OSPF_NBR_STATE_EXCHANGE_START      ((LONG)5)
#define OSPF_NBR_STATE_EXCHANGE            ((LONG)6)
#define OSPF_NBR_STATE_LOADING             ((LONG)7)
#define OSPF_NBR_STATE_FULL                ((LONG)8)
/*End   BC3D02903 liangjicheng 2010-04-19 */
/*Begin BC3D03553 liangjicheng 2010-08-10 */
#define OSPF_NBR_EVENT_HELLO_RCVD                  0x00
#define OSPF_NBR_EVENT_INTERFACE_ID_CHANGED        0x01
#define OSPF_NBR_EVENT_START                       0x02
#define OSPF_NBR_EVENT_2WAY_RCVD                   0x03
#define OSPF_NBR_EVENT_NEGOTIATION_DONE            0x04
#define OSPF_NBR_EVENT_EXCHANGE_DONE               0x05
#define OSPF_NBR_EVENT_FULLY_EXCHANGED             0x06
#define OSPF_NBR_EVENT_BAD_LS_REQ                  0x07
#define OSPF_NBR_EVENT_LOADING_DONE                0x08
#define OSPF_NBR_EVENT_ADJ_OK                      0x09
#define OSPF_NBR_EVENT_SEQ_NUMBER_ERR              0x0A
#define OSPF_NBR_EVENT_1WAY_RCVD                   0x0B
#define OSPF_NBR_EVENT_KILL_NBR                    0x0C
#define OSPF_NBR_EVENT_INACTIVITY_TMR              0x0D
#define OSPF_NBR_EVENT_LL_DOWN                     0x0E
#define OSPF_NBR_EVENT_JUST_FRIENDS                0x0F
#define OSPF_NBR_EVENT_SETUP_ADJ                   0x10
#define OSPF_NBR_EVENT_SLOW_ADJ_ERR                0x11
#define OSPF_NBR_EVENT_RESET_INACT_TIMER           0x12
/*End   BC3D03553 */

/*IF FSM inputs*/
#define OSPF_IF_INPUT_NON_BCAST_UP              0x00
#define OSPF_IF_INPUT_ELIG_BCAST_UP             0x01
#define OSPF_IF_INPUT_BCAST_UP                  0x02
#define OSPF_IF_INPUT_WAIT_TIMER                0x03
#define OSPF_IF_INPUT_BACKUP_SEEN               0x04
#define OSPF_IF_INPUT_NEIGHBOR_CHANGE          0x05
#define OSPF_IF_INPUT_DR_LOCAL                  0x06
#define OSPF_IF_INPUT_BACKUP_LOCAL              0x07
#define OSPF_IF_INPUT_DR_OTHER                  0x08
#define OSPF_IF_INPUT_LOOP_IND                  0x09
#define OSPF_IF_INPUT_UNLOOP_IND               0x0A
#define OSPF_IF_INPUT_INTERFACE_DOWN            0x0B
#ifdef BLD_OSPFV3
#define OSPF_IF_INPUT_MULTI_IF_TO_LINK         0x0C
#endif
/*IF FSM states*/
#define OSPF_IF_STATE_DOWN                 ((LONG)1)
#define OSPF_IF_STATE_LOOPBACK             ((LONG)2)
#define OSPF_IF_STATE_WAITING              ((LONG)3)
#define OSPF_IF_STATE_POINT_TO_POINT       ((LONG)4)
#define OSPF_IF_STATE_DESIGNATED_ROUTER    ((LONG)5)
#define OSPF_IF_STATE_BACKUP_DESIGNTD_RTR  ((LONG)6)
#define OSPF_IF_STATE_OTHER_DESIGNATD_RTR  ((LONG)7)

/*Added by guojianjun178934, 【DOPRA IP V3R2C10-同步问题单-DTS2014040401470】【SGSN产品：OSPF】linux x86 系统函数times存在bug，需要VISP提供规避方案 , 2014/6/3   问题单号:DTS2014052908271 */
/*OSPF定时器只用的时钟函数类型定义*/
/*注意：定时器类型定义修改时，需同步修改NBB_TIMER_TYPE_***中的定义*/
#define OSPF_TIMER_TYPE_LINUX         1    /*OSPF使用Linux系统提供的时钟函数*/
#define OSPF_TIMER_TYPE_LINUX_EXT     2    /*OSPF使用Linux提供的时钟函数*/
/* End of Added by guojianjun178934, 2014/6/3   问题单号:DTS2014052908271 */

/*ospf模块的错误码*/
typedef enum tagOSPF_ERROR_CODE
{
    OSPF_OK = 0,
    /*以下错误码由DCL通过mib机制直接返回,只有IPS返回的时候才使用*/
    OSPF_NO_ERROR = 1,                   /*成功*/
    OSPF_ERR_GEN_ERROR = MID_COMP_OSPF + 2, /*002*/
    OSPF_ERR_WRONG_VALUE,                   /*003*/
    OSPF_ERR_INCONSISTENT_VALUE,            /*004*/
    OSPF_ERR_RESOURCE_UNAVAILABLE,          /*005*/
    OSPF_ERR_NO_SUCH_OBJECT,                /*006*/
    OSPF_ERR_AMB_RC_END_OF_TABLE,           /*007*/
    OSPF_ERR_AGENT_ERROR,                   /*008*/
    OSPF_ERR_INCOMPLETE,                    /*009*/
    OSPF_ERR_PARTIAL_FAMILY_OK,             /*010*/
    OSPF_ERR_PRODUCT_NOT_READY,             /*011*/
    OSPF_ERR_IPS_RETURN_TIME_OUT  = MID_COMP_OSPF + 15,   /*015*/
    /*新增错误码，从100开始*/
    OSPF_ERR_NULL_POINTER  = MID_COMP_OSPF + 100,   /*100 参数为空指针*/
    OSPF_ERR_PARAMETER,                  /*101 参数值错误*/     
    OSPF_ERR_FAIL_TO_BUILD_IPS,          /*102 构建IPS消息失败*/
    OSPF_ERR_FALI_TO_OPEN_CONNECTION,    /*103 生成发送句柄失败*/
    OSPF_ERR_PROCESS_IPS,                /*104 发送IPS消息后，返回失败*/
    OSPF_ERR_IF_NAME,                    /*105 错误的接口名*/
    OSPF_ERR_FAIL_TO_GET_IPADDR,         /*106 通过接口索引取首地址失败*/
    OSPF_ERR_CFG_ALREADY_EXIST,          /*107 配置已经存在*/
    OSPF_ERR_NULL_MIB_ENTRY,             /*108 mib实体指针为空*/
    OSPF_ERR_CFG_NOT_EXIST,              /*109 配置不存在*/
    OSPF_ERR_KEY_IS_NULL,                /*110 用于获取下一个mib项的key指针为NULL*/
    OSPF_ERR_WRONG_CFG_TYPE,             /*111 错误的配置类型*/
    OSPF_ERR_PROCESSES_REACH_MAX,        /*112 进程数达到最大*/
    OSPF_ERR_PROCESS_NOT_EXIST,          /*113 进程不存在*/
    OSPF_ERR_NO_MEMORY,                  /*114 适配代码错误*/
    OSPF_ERR_FIND_NEXT_NODE_FAIL,        /*115 fail to find next routing node*/
    OSPF_ERR_ENABLE_OSPF_ADMIN_STATUS,   /*116 fail to enable ospf process's admin status*/
    OSPF_ERR_DISABLE_OSPF_ADMIN_STATUS,  /*117 fail to disable ospf process's admin status*/
    OSPF_ERR_CFG_GR_PARA,                /*118 fail to config grace restart parameter*/
    OSPF_ERR_HAVE_NO_AVL_NODE,           /*119 找到不到节点*/
    OSPF_ERR_HAVE_NO_NEXT_AVL_NODE,      /*120 找不到下一个节点*/
    OSPF_ERR_HAVE_NO_VNBR,               /*121 找不到虚邻居*/
    OSPF_ERR_HAVE_NO_NEXT_VNBR,          /*122 找不到下一个虚邻居*/
    OSPF_ERR_IF_HAVE_MORE_VNBR,          /*123 接口有更多的虚邻居，表示有问题*/ 
    OSPF_ERR_HAVE_NO_AREA_CB,            /*124 没有域*/
    OSPF_ERR_HAVE_NO_NEXT_AREA_CB,       /*125*/
    OSPF_ERR_HAVE_NO_LSDB_CB,            /*126*/
    OSPF_ERR_HAVE_NO_NEXT_LSDB_CB,       /*127*/
    OSPF_ERR_HAVE_NO_LSA,                /*128 没有LSA*/
    OSPF_ERR_INVALID_LSA_TYPE,           /*129*/
    OSPF_ERR_HAVE_NO_HANDLE,             /*130 没有句柄*/
    OSPF_ERR_INSTANCE_CAN_NOT_ZERO,      /*131*/
    OSPF_ERR_MALLOC,                     /*132 分配内存失败*/

    OSPF_ERR_CFG_REFRESH_HELLO,          /*133 fail to Refresh other paremter */
    OSPF_ERR_CFG_REFRESH_DEAD,           /*134*/
    OSPF_ERR_PROCESS_ID_IS_ZERO,         /*135 OSPF伪进程为0*/
    OSPF_ERR_NO_CFG_IF,                  /*136 没有配置接口*/
    OSPF_ERR_GET_NET_TYPE,               /*137*/
    OSPF_ERR_INVALID_IPADDR,             /*138*/
    OSPF_ERR_INVALID_PROCID,             /*139*/
    OSPF_ERR_INVALID_NOFLAG,             /*140*/
    OSPF_ERR_INVALID_AREA,               /*141*/
    OSPF_ERR_INVALID_VALUE,              /*142*/
    OSPF_ERR_CFG_PREFERENCE_INT,         /*143*/
    OSPF_ERR_CFG_PREFERENCE_EXT,         /*144*/
    OSPF_ERR_MODULE_NOT_REGISTERED,      /*145*/
    
    OSPF_ERR_MEM_RELEASE,                /*146 释放内存有误 BC3D01051 l00147446 09-01-08*/
    OSPF_ERR_INVALID_GR_PERIOD,          /*147 Invalid Gr period BC3D01086 liangjicheng 09-01-14*/

    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    OSPF_ERR_GET_VRF_INDEX,              /*148 */
    OSPF_ERR_INST_NOT_IN_VRF,            /*149 */
    OSPF_ERR_GET_RTM_INST,               /*150 */
    OSPF_ERR_VRF_NOT_INIT,               /*151 */
    OSPF_ERR_CFG_DEADTIME,               /*152 配置的Dead Time小于或等于Hello Time BC3D02558 10-01-04*/
    OSPF_ERR_CFG_HELLOTIME,              /*153 配置的Hello Time大于或等于Dead Time BC3D02558 10-01-04*/
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    /* add for BC3D02908  */
    OSPF_ERR_INVALID_ACCNUM= MID_COMP_OSPF + 154,    /*154 acl规则组号无效 */
    /* end for BC3D02908  */
    
    OSPF_ERR_INVALID_PROTO_TYPE,         /*155 无效协议类型 */
    OSPF_ERR_INVALID_METRIC_TYPE,        /*156 无效Metric类型 */
    OSPF_ERR_INVALID_METRIC_VAL,         /*157 无效Metric值 */
    OSPF_ERR_INVALID_STATIC_RPAID,       /*158 无效静态协议引入ID */
    OSPF_ERR_INVALID_DYNAMIC_RPAID,      /*159 无效动态协议引入ID */
    
    /*Added by guojianjun178934, V2同步问题单的处理--同步错误码, 2013/9/18   问题单号:T.OSPF.DTS2013081601109 */
    OSPF_ERR_WAIT_RTM_JOIN_STATUS_TIMEOUT, /*160 等待OSPF同RTM Join 状态超时 */
    OSPF_ERR_WAIT_RTM_JOIN_ACTIVE_TIMEOUT,      /*161 等待OSPF同RTM Join UP超时 */
    OSPF_ERR_WAIT_RTM_JOIN_GONE_TIMEOUT,    /*162 等待OSPF同RTM GONE UP超时 */
    /* End of Added by guojianjun178934, 2013/9/18   问题单号:T.OSPF.DTS2013081601109 */
    OSPF_ERR_END                         
}OSPF_ERROR_E;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _OSPF_SGSN_API_DEF_H_ */

