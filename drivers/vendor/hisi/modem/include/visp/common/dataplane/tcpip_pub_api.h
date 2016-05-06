/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_pub_api.h
*
*  Project Code: copy 1.1
*   Module Name:
*  Date Created: 2009-08-20
*        Author: ZhengSenHuo/GeXianJun(104483/121208)
*   Description:
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-08-20   ZhengSenHuo/GeXianJun(104483/121208)  Create
*
*******************************************************************************/
#ifndef _TCPIP_PUB_API_H_
#define _TCPIP_PUB_API_H_

#ifdef __cplusplus
    extern "C"{
#endif

/* PPI操作类型,该定义是控制面对应定义的拷贝,请务必保证与控制面定义一致 */
enum tagPPIOprType
{
    /*do nothing*/
    PPI_OPR_NULL,

    /*路由消息类型*/
    PPI_ENTRY_FIB4_ADD,         /* 1 添加路由消息*/
    PPI_ENTRY_FIB4_DEL,         /* 2 删除路由消息*/
    PPI_ENTRY_FIB4_UPDATE,      /* 3 刷新路由消息*/

    /*ARP操作类型*/
    PPI_ENTRY_ARP_ADD,          /* 4 添加ARP*/
    PPI_ENTRY_ARP_DEL,          /* 5 删除ARP*/
    PPI_ENTRY_ARP_UPDATE,       /* 6 刷新ARP*/

    /*IFNET类型*/
    PPI_IF_CREATE,              /* 7 接口创建*/
    PPI_IF_DELETE,              /* 8 接口删除*/
    PPI_IF_SETMTU,              /* 9 设置MTU*/
    PPI_IF_GETMAXMTU,           /* 10 获取最大MTU */
    PPI_IF_UP,                  /* 11 接口UP*/
    PPI_IF_DOWN,                /* 12 接口DOWN*/
    PPI_IF_SETMAC,              /* 13 设置TRUNK接口的錺physical地址 */
    PPI_IF_SET_DEV,             /* 14 设置接口物理参数*/

    PPI_TRUNKPORT_UP,           /* 15 PORT UP*/
    PPI_TRUNKPORT_DOWN,         /* 16 PORT DOWN*/

    /*PPP类型*/
    PPI_PPP_SET_LCPGOTOPTION,   /* 17 通知NP LCP本端协商选项*/
    PPI_PPP_SET_LCPHISOPTION,   /* 18 通知NP LCP对端协商选项*/
    PPI_PPP_SET_IPCPGOTOPTION,  /* 19 通知NP IPCP本端协商选项*/
    PPI_PPP_SET_IPCPHISOPTION,  /* 20 通知NP IPCP对端协商选项*/
    PPI_PPP_SET_MUXCPGOTOPTION, /* 21 通知NP MUXCP本端协商选项*/
    PPI_PPP_SET_MUXCPHISOPTION, /* 22 通知NP MUXCP对端协商选项*/

    PPI_PPP_SET_IP6CPGOTOPTION,  /* 23 通知NP IP6CP本端协商选项*/
    PPI_PPP_SET_IP6CPHISOPTION,  /* 24 通知NP IP6CP对端协商选项*/

    PPI_PPP_ADD_MLPPP,          /* 25 通知NP接口加入到ML PPP*/
    PPI_PPP_DEL_MLPPP,          /* 26 通知NP接口从一个ML PPP中删除*/
    PPI_PPP_SET_CONFIGINFO,     /* 27 通知NP本端的配置信息*/
    PPI_PPP_GET_INFO,           /* 28 获取下发给NP的PPP/MP信息*/

    PPI_IP_SENDPKT,                 /* 29 发送IP报文*/

    PPI_3AH_CREATE,                 /* 30 创建3ah NP会话*/
    PPI_3AH_UPDATE,                 /* 31 更新3ah NP会话*/
    PPI_3AH_DELETE,                 /* 32 删除3ah NP会话*/

    /*1AG相关*/
    PPI_OAM1AG_ENABLECCM,       /* 33 使能CCM发送*/
    PPI_OAM1AG_DISABLECCM,      /* 34 去使能CCM发送*/
    PPI_OAM1AG_SETINTERVAL,     /* 35 CCM更新发送周期*/
    PPI_OAM1AG_SETCOMPATIBLE,   /* 36 兼容模式*/
    PPI_OAM1AG_SETGLBPARA,      /* 37 1ag设置全局属性*/
    OAM_OAM1AG_SETRMEPPARA,     /* 38 增加或更新RMEP的参数*/
    OAM_OAM1AG_DELRMEPRARA,     /* 39 删除RMEP项*/
    PPI_OAM1AG_SETMAVLANPRI,    /* 40 设置基于MA的VLAN优先级，未设置取全局优先级*/
    PPI_OAM1AG_SETRDIFLAG,      /* 41 设置同一MA下所有MEP发送CCM报文时的RDIFLAG值*/
    PPI_OAM1AG_SETGLOBALVLANPRITOMA,    /*42 设置全局VLAN优先级到使用全局VLAN优先级的MA中*/
    /* VISP1.8.1 支持1AG标准协议开发*/
    PPI_OAM1AG_SET1AGVERSION,    /* 43 设置MEP使用的1AG协议版本 */
    /* Added for 支持接收不带VLAN头的1AG报文2009-05-14 */
    PPI_OAM1AG_SETMEPVLANFLAG,   /* 44 设置MEP下发送报文时是否需要带VLAN头标志.
                                       0:表示不需要带VLAN头,1表示需要带VLAN*/
    PPI_OAM1AG_CREATE_MD,            /* 45 创建维护域 */
    PPI_OAM1AG_DELETE_MD,            /* 46 删除维护域 */
    PPI_OAM1AG_CREATE_MA,            /* 47 创建维护集 */
    PPI_OAM1AG_DELETE_MA,            /* 48 删除维护集 */
    PPI_OAM1AG_CREATE_MEP,           /* 49 创建维护节点 */
    PPI_OAM1AG_DELETE_MEP,           /* 50 删除维护节点 */
    PPI_OAM1AG_GETMEP,               /* 51 获取MEP信息 */

    PPI_IP_JOIN_MULTI,          /* 52 通知NP主机加入多播组*/
    PPI_IP_LEAVE_MULTI,         /* 53 通知NP主机离开多播组*/

    PPI_ENTRY_FIB6_ADD,         /* 54 */
    PPI_ENTRY_FIB6_DEL,         /* 55 */
    PPI_ENTRY_FIB6_UPDATE,      /* 56 */

    /* L2IF vlan ppi cmd */
    PPI_VLAN_CREATE,                        /* 57 通知NP创建VLAN */
    PPI_VLAN_DELETE,                        /* 58 删除VLAN*/
    PPI_VLAN_ADDSUB,                        /* 59 向指定的Su*** VLAN中添加Sub VLAN*/
    PPI_VLAN_REMOVESUB,                     /* 60 从指定的Su*** VLAN中删除指定的Sub VLAN*/
    PPI_VLAN_SET_TYPE,                      /* 61 设置VLAN类型，包括Su**r/Sub/Commom等*/
    PPI_VLAN_SET_UNKOWN_UNICAST_CTR_MODE,   /* 62 设置未知单播报文是否在VLAN中广播的控制开关*/
    PPI_VLAN_SET_BROADCAST_CTR_MODE,        /* 63 通知NP设置广播报文处理方式 */
    PPI_VLAN_SET_UNKOWN_MULTI_CTR_MODE,     /* 64 通知NP设置未知多播报文处理方式 */
    PPI_VLAN_SET_MACLEARN_MODE,             /* 65 使能/禁止VLAN内的physical地址学习*/
    PPI_VLAN_STATUS_DOWN,                   /* 66 通知NP VLAN的物理状态DOWN */
    PPI_VLAN_STATUS_UP,                     /* 67 通知NP VLAN的物理状态UP */
    PPI_VLANIF_CREATE,                      /* 68 创建vlanif接口时通知驱动、下发桥mac*/
    PPI_VLANIF_DELETE,                      /* 69 删除vlanif接口时通知驱动*/

    /* L2 端口消息类型 */
    PPI_PORT_SET_LINK_TYPE,                 /* 70 */
    PPI_PORT_SET_PVID,                      /* 71 */
    PPI_PORT_DEL_PVID,                      /* 72 */
    PPI_VLAN_ADD_PORT_TRUNK,                /* 73 */
    PPI_VLAN_DEL_PORT_TRUNK,                /* 74 */
    PPI_PORT_SET_MAC_LEARN_MODE,            /* 75 */
    PPI_PORT_SET_PRIORITY,                  /* 76 */
    PPI_PORT_SET_FLOW_SUPPRESS,             /* 77 */

    /* L2 转发表相关消息类型 */
    PPI_FDB_SET_AGINGTIME,                  /* 78 */
    PPI_FDB_ADD,                            /* 79 */
    PPI_FDB_DELETE,                         /* 80 */
    PPI_FDB_DELETE_BY_KEY,                  /* 81 */
    PPI_ML_ENABLE,                          /* 82 */
    PPI_ML_ADD,                             /* 83 */
    PPI_ML_DEL,                             /* 84 */

    /* L2 QinQ消息类型 */
    PPI_QINQ_SET,                           /* 85 */
    PPI_QINQ_DELETE,                        /* 86 */
    PPI_QINQ_SET_PROTOCOL,                  /* 87 */

    /* VRRP消息类型*/
    PPI_VRRP_ENABLE,                        /* 88 */
    PPI_VRRP_ADD_VIRTUAL_MAC,               /* 89 */
    PPI_VRRP_DEL_VIRTUAL_MAC,               /* 90 */

    PPI_VRRP_SUBVLAN_ADD_VIRTUAL_MAC,       /* 91 */
    PPI_VRRP_SUBVLAN_DEL_VIRTUAL_MAC,       /* 92 */
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-05 */
    PPI_VRF_CREATE   ,                      /* 93 VRF创建 */
    PPI_VRF_DELETE   ,                      /* 94 VRF删除 */
    PPI_VRF_BIND   ,                        /* 95 接口绑定到VRF */
    PPI_VRF_UNBIND ,                        /* 96 接口去绑定VRF */
    /* End:VISP1.7C03 VRF wangchengyang,2009-02-05   */

    /* multicast mac operate type */
    PPI_MULTICMAC_ADD,                      /* 97 增加多播physical地址 */
    PPI_MULTICMAC_DEL,                      /* 98 删除多播physical地址 */

    PPI_TRUNK_ADDPORT,   /* TRUNK添加绑定端口 */
    PPI_TRUNK_REMOVEPORT,/* TRUNK移除绑定端口 */

    PPI_AM4_ADD,         /* AM4添加地址 */
    PPI_AM4_DELETE,      /* AM4删除地址 */

    PPI_PPP_SET_OSICPGOTOPTION, /*通知NP OSICP本端协商选项*/
    PPI_PPP_SET_OSICPHISOPTION, /*通知NP OSICP对端协商选项*/

    PPI_PPP_GET_LCPGOTOPTION,    /* 获取本端LCP协商选项 */
    PPI_PPP_GET_LCPHISOPTION,    /* 获取对端LCP协商选项 */
    PPI_PPP_GET_IPCPGOTOPTION,   /* 获取IPCP本端协商选项 */
    PPI_PPP_GET_IPCPHISOPTION,   /* 获取IPCP对端协商选项 */
    PPI_PPP_GET_OSICPGOTOPTION,  /* 获取OSICP本端协商选项 */
    PPI_PPP_GET_OSICPHISOPTION,  /* 获取OSICP对端协商选项 */

    PPI_IP6_SENDPKT,             /* 发送IPv6报文*/

    /* PPPOE消息类型 */
    PPI_PPPOE_SESSION_CREATED,      /* 通知NP创建PPPOE会话 */
    PPI_PPPOE_SESSION_DELETED,      /* 通知NP删除PPPOE会话 */
    PPI_PPPOE_SESSION_UPDATED,      /* 通知NP更新PPPOE会话信息 */
    PPI_PPPOE_SESSION_GETINFO,      /* 从NP获取PPPOE会话信息 */
    PPI_PPPOE_SESSION_RESTORED,     /* 通知NP PPPOE会话恢复处理成功 */
    PPI_PPPOE_SESSION_RESTORED_FIN, /* 通知NP所有PPPOE会话恢复处理完成 */
    PPI_PPPOE_SESSION_SMOOTHED,     /* 通知NP PPPOE会话平滑处理成功 */
    PPI_PPPOE_SESSION_SMOOTHED_FIN, /* 通知NP所有PPPOE会话平滑处理完成 */
    PPI_OAM1AG_SETDETECTTIMER,      /* 通知NP CCM Loss检测时间值*/
    PPI_TRUNK_IS_PHYUP,             /* 121 TRUNK PHY UP */
    PPI_TRUNK_IS_PHYDOWN,           /* 122 TRUNK PHY DOWN */
    PPI_MAP_ADD,                    /* 123 MAP ADD*/
    PPI_MAP_DEL,                    /* 124 MAP DEL*/

    /*  Add for 新需求, by mengzechao176865, at 2011-02-23. 
        修改原因: 将VLAN与子接口对应关系下发给tran */
    PPI_IF_SUBIF_JOIN_VLAN,         /* 125 将子接口加入VLAN通知tran */
    PPI_IF_SUBIF_LEAVE_VLAN,        /* 126 将子接口离开VLAN通知tran */

    /* Add by zhaoyue00171897, at 2011-08-17. 修改原因: 支持获取动态FDB表项 */
    PPI_DYNAMIC_FDB_GET,            /* 127 从NP获取动态FDB表项 */
    
    /* Add for V2R3C06, by shuxie liu00176784, at 2011-10-04. 修改原因:  支持EOAM协议版本全局设置  */
    PPI_OAM1AG_SETGLBVERSION,     /* 128 EOAM协议全局版本设置 */

    /* Add for V2R3C06, by z00171897/p00193127, at 2011-10-17. 修改原因: 支持Y1731使能/去使性能检测 */
    PPI_OAMY1731_ENABLEDLM,        /* 129 使能双端帧丢失检测 */
    PPI_OAMY1731_DISABLEDLM,       /* 130 去使能双端帧丢失检测 */
    PPI_OAMY1731_ENABLESLM,        /* 131 使能单端帧丢失检测 */
    PPI_OAMY1731_DISABLESLM,       /* 132 去使能单端帧丢失检测 */
    PPI_OAMY1731_ENABLEDDM,        /* 133 使能双向延时检测 */
    PPI_OAMY1731_DISABLEDDM,       /* 134 去使能双向延时检测 */
    /* Add for VISPV2R3C05STACK-127, by zhaoyue00171897, at 2012-02-03. 修改原因: 增加使能/去使能3AH时NP下发 */
    PPI_3AH_ENABLE,                /* 135 使能3AH功能 */
    PPI_3AH_DISABLE,               /* 136 去使能3AH功能 */
     /* Add for V2R3C07, by z00208058/w00207740, at 2012-4-16. 修改原因: TRUNK LACP下移需求开发 */
    PPI_ADD_LINK,                  /*137 TRUNK下发ADD操作*/
    PPI_DEL_LINK,                  /*138 TRUNK下发DEL操作*/
    PPI_UPDATE_LINK,               /*139 TRUNK下发UPDATE操作*/

    /*Added by limin00188004, 支持全局和VRF域的控制License, 2012/9/26   问题单号:S.VRF.02.01 */
    PPI_VRF_GLOBAL_LICENCE,        /*140 VRF licence特性使能/去使能命令字*/
    PPI_VRF_SINGLE_LICENCE,        /*141 某个VRF的licence开关*/
    /* End of Added by limin00188004, 2012/9/26   问题单号:S.VRF.02.01 */
    PPI_OAM1AG_START_RMEP_DETECT,  /*142  通知底层启动RMEP的探测*/
    PPI_OAM1AG_STOP_RMEP_DETECT,   /*143  通知底层停止RMEP的探测*/

    PPI_POLICYRT_ADD_POLICY,   /* 144 Add policy group */
    PPI_POLICYRT_DEL_POLICY,   /* 145 Delete policy group */
    PPI_POLICYRT_ADD_NODE,     /* 146 Add policy node entry */
    PPI_POLICYRT_UPDATE_NODE, /*147  Update policy node entry */
    PPI_POLICYRT_DEL_NODE,  /* 148 Delete policy node entry */
    PPI_POLICYRT_GET_NODE_COUNT, /*149 Get the hit count from TRAN*/
    PPI_TUNNEL_PARA_CONFIG,        /* 150 tunnel接口参数配置*/
    PPI_OPR_END
};
/* PPI操作类型,该定义是控制面对应定义的拷贝,请务必保证与控制面定义一致 */


/* BFD PPI Msg Type,该定义是控制面对应定义的拷贝,请务必保证与控制面定义一致 */
typedef enum tagPPI_MSG_TYPE_E
{
    BFD_PPI_SESSION_CREATE        = 1              ,         /* 创建会话 */
    BFD_PPI_SESSION_REFRESH                        ,         /* 更新会话 */
    BFD_PPI_SESSION_DELETE                         ,         /* 删除会话 */
    BFD_PPI_START_SEND_SEQUENCE                    ,         /* 通知开始发送查询序列 */
    BFD_PPI_STOP_SEND_SEQUENCE                     ,         /* 通知停止发送查询序列 */
    /* Add by q62011 for SGSN NP */
    BFD_PPI_USER_CREATE                            ,         /* API创建会话 */
    BFD_PPI_USER_DELETE                            ,         /* API删除会话 */

    BFD_PPI_SESSION_GET                            ,         /* 获取底层NP的会话信息 */
    /* SGSN BFD新需求:区分会话删除的原因 */
    BFD_PPI_SESSION_DELETE_ADMINDOWN               ,         /* 由于Admin down导致会话删除 */
    BFD_PPI_SESSION_DELETE_DOWN                    ,         /* 由于其他原因导致会话删除 */
    BFD_PPI_SESSION_STOP_SEND_DETECT_PKT           ,         /* 通知不再发送周期性BFD报文 */
    BFD_PPI_SESSION_START_SEND_DETECT_PKT          ,         /* 通知重新发送周期性BFD报文 */
    BFD_PPI_MSG_MAX
}PPI_MSG_TYPE_E;


#ifdef __cplusplus
}
#endif
#endif


