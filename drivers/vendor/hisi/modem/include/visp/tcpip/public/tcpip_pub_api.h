/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_pub_api.h
*
*  Project Code: VISPV100R005
*   Module Name: public
*  Date Created: 2008-03-07
*        Author: zhoutong(43740)
*   Description: public模块(包括公共查询显示函数，HA,NP特性)对外头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-03-07   zhoutong(43740)         Create
*  2008-08-13   f54882                  Modify for BC3D00237
*  2008-08-25   f54882                  Modify for BC3D00262
*  2008-08-25   f54882                  Modify for BC3D00263
*
*******************************************************************************/

#ifndef _TCPIP_PUB_API_H_
#define _TCPIP_PUB_API_H_

#ifdef  __cplusplus
extern  "C"{
#endif

/*******************************宏定义****************************************/
#define LINK_HOOK_INPUT_PKT     0x01   /*链路层注册钩子接收方向*/
#define LINK_HOOK_OUTPUT_PKT    0x02   /*链路层注册钩子发送方向*/

/*路由标记*/
#define PPI_RTF_UP              0x0001  /*路由可用*/
#define PPI_RTF_GATEWAY         0x0002  /*目的地址可路由*/
#define PPI_RTF_HOST            0x0004  /*主机路由，否则为网段路由*/
#define PPI_RTF_REJECT          0x0008
#define PPI_RTF_DYNAMIC         0x0010  /*动态路由*/
#define PPI_RTF_STATIC          0x0800  /*静态路由*/
#define PPI_RTF_SUBNET_BROCST   0x10000 /*子网广播路由*/
#define PPI_RTF_BLACKHOLE       0x1000  /*黑洞路由，表示需要丢弃报文*/
#define PPI_RTF_REJECT2         0x8000

/*ARP标志*/
#define PPI_ARPF_RESOLVED       0x01    /*ARP已解析*/
#define PPI_ARPF_RESOLVING      0x02    /*ARP正在解析*/
#define PPI_ARPF_STATIC         0x04    /*静态ARP*/
#define PPI_ARPF_DYNAMIC        0x08    /*动态ARP*/


#define PPI_RTMSG_LENGTH        sizeof(PPI_RTMSG4_S)
#define PPI_ARP_LENGTH          sizeof(PPI_ARP_S)

/*mc的规格*/
#define PPI_MC_PREFIX_MAX_NUM        16  /*前缀省略对的数目*/
#define PPI_MC_PREFIX_MAX_LEN        8   /*前缀省略的报文长度*/

/*IPHC压缩类型*/
#define PPI_IPHC_COMPRESS_ALL       0   /* 对TCP/non-TCP报文都压缩 */
#define PPI_IPHC_COMPRESS_NON_TCP   1   /* 仅压缩no-TCP报文 */
#define PPI_IPHC_COMPRESS_TCP       2   /* 仅压缩TCP报文*/
#define PPI_IPHC_COMPRESS_NONE      3   /* 禁止压缩TCP、non-TCP报文 */

/* 不进行RTP Compression和Enhanced RTP Compression压缩*/
#define PPI_IPHC_NONE_RTP_COMPRESSION      0
/* 进行RTP Compression压缩 */
#define PPI_IPHC_RTP_COMPRESSION           1
/* 进行Enhanced RTP Compression压缩 */
#define PPI_IPHC_ENHANCED_RTP_COMPRESSION  2

#define DYNAMIC_ARP_TYPE_NONE         0x00  /*ARP初始标记，有可能是ARP哑元*/
#define DYNAMIC_ARP_TYPE_USER_CONFIG  0x01  /*用户配置动态ARP表项*/
#define DYNAMIC_ARP_TYPE_LERAN        0x02  /*动态学习ARP表项*/
#define DYNAMIC_ARP_TYPE_REFRESH      0x03  /*用户配置的动态ARP表项被刷新*/

/*1AG MD最大名字长度*/
#ifndef OAM_1AG_MAX_MDNAME_LEN
#define OAM_1AG_MAX_MDNAME_LEN 43
#endif
/*1AG MA最大名字长度*/
#ifndef OAM_1AG_MAX_MANAME_LEN
#define OAM_1AG_MAX_MANAME_LEN 43
#endif
/*Y1731 MA最大名字长度*/
#ifndef OAM_Y1731_MAX_MANAME_LEN
#define OAM_Y1731_MAX_MANAME_LEN 13
#endif

#ifndef MACADDRLEN
#define MACADDRLEN 6   /* physical地址长度 */
#endif

#ifndef IF_MAX_INTERFACE_NAME_LEN
#define IF_MAX_INTERFACE_NAME_LEN 47       /* 最大接口名长度 */
#endif

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
#define  TCPIP_MAX_VRFNAME_LENGTH   31      /*VPN名字长度*/
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

/*定义日志的输出类型*/
#define LOG_TYPE_WARNING        0x001
#define LOG_TYPE_CFG            0x010
#define LOG_TYPE_RUN            0x100

/* HA预配置模块 */
#define HA_PRECFG_BASIC         0x00000001
#define HA_PRECFG_ETH           0x00000002
#define HA_PRECFG_PPP           0x00000004
#define HA_PRECFG_POEC          0x00000008
#define HA_PRECFG_POES          0x00000010
#define HA_PRECFG_DHCP4C        0x00000020
#define HA_PRECFG_DHCP4R        0x00000040
#define HA_PRECFG_BFD           0x00000080
#define HA_PRECFG_EOAM3AH       0x00000100
#define HA_PRECFG_OAM1AG        0x00000200
#define HA_PRECFG_IGMP          0x00000400
#define HA_PRECFG_VRF           0x00000800
#define HA_PRECFG_TWAMP           0x00001000
#define HA_PRECFG_ALL           0xFFFFFFFF

#define TCPIP_HA_AMB                0x1     /* 主用板 */
#define TCPIP_HA_SMB                0x0     /* 备用板 */

/* HA注册的模块名 */
#define HA_MOUDLE_NAME_LEN          23

/* 最多注册HA模块数目 */
#define HA_MAX_REGISTER_MOUDLE_NUM  16

/* 目前只有OSP不使用VISP SRM,但是会使用VISP FIB, 后续扩充需要注意修改*/
#define RM_DCLRTM    2
#define RM_VISPSRM   1
#define RM_PRODUCT   0
/*******************************枚举****************************************/
/*PPI操作类型,修改此结构后需修改对应的TCPIP_PPI_OprType_En[]结构,和common/dataplan目录下对应的该接口的拷贝*/
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
    PPI_IF_SETMAC,              /* 13 设置TRUNK接口的physical地址 */
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

    PPI_TRUNK_ADDPORT,                      /* 99 TRUNK添加绑定端口 */
    PPI_TRUNK_REMOVEPORT,                   /* 100 TRUNK移除绑定端口 */

    PPI_AM4_ADD,                            /* 101 AM4添加地址 */
    PPI_AM4_DELETE,                         /* 102 AM4删除地址 */

    PPI_PPP_SET_OSICPGOTOPTION,             /* 103 通知NP OSICP本端协商选项 */
    PPI_PPP_SET_OSICPHISOPTION,             /* 104 通知NP OSICP对端协商选项 */

    PPI_PPP_GET_LCPGOTOPTION,       /* 105 获取本端LCP协商选项 */
    PPI_PPP_GET_LCPHISOPTION,       /* 106 获取对端LCP协商选项 */
    PPI_PPP_GET_IPCPGOTOPTION,      /* 107 获取IPCP本端协商选项 */
    PPI_PPP_GET_IPCPHISOPTION,      /* 108 获取IPCP对端协商选项 */
    PPI_PPP_GET_OSICPGOTOPTION,     /* 109 获取OSICP本端协商选项 */
    PPI_PPP_GET_OSICPHISOPTION,     /* 110 获取OSICP对端协商选项 */

    PPI_IP6_SENDPKT,                /* 111 发送IPv6报文*/

    /* PPPOE消息类型 */
    PPI_PPPOE_SESSION_CREATED,      /* 112 通知NP创建PPPOE会话 */
    PPI_PPPOE_SESSION_DELETED,      /* 113 通知NP删除PPPOE会话 */
    PPI_PPPOE_SESSION_UPDATED,      /* 114 通知NP更新PPPOE会话信息 */
    PPI_PPPOE_SESSION_GETINFO,      /* 115 从NP获取PPPOE会话信息 */
    PPI_PPPOE_SESSION_RESTORED,     /* 116 通知NP PPPOE会话恢复处理成功 */
    PPI_PPPOE_SESSION_RESTORED_FIN, /* 117 通知NP所有PPPOE会话恢复处理完成 */
    PPI_PPPOE_SESSION_SMOOTHED,     /* 118 通知NP PPPOE会话平滑处理成功 */
    PPI_PPPOE_SESSION_SMOOTHED_FIN, /* 119 通知NP所有PPPOE会话平滑处理完成 */
    PPI_OAM1AG_SETDETECTTIMER,      /* 120 通知NP CCM Loss检测时间值*/
    PPI_TRUNK_IS_PHYUP,             /* 121 TRUNK PHY UP */
    PPI_TRUNK_IS_PHYDOWN,           /* 122 TRUNK PHY DOWN */
    PPI_MAP_ADD,                           /* 123 MAP ADD*/
    PPI_MAP_DEL,                           /* 124 MAP DEL*/

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
/*PPI操作类型,修改此结构后需修改对应的TCPIP_PPI_OprType_En[]结构,和common/dataplan目录下对应的该接口的拷贝*/

/* L2IF FDB下发键值类型 */
typedef enum tagPPI_L2IF_FDB_KEY_MODE
{
    PPI_FDB_KEY_INVALID = 0,                   /* 无效模式 */
    PPI_FDB_KEY_BY_VLAN,                     /* 基于VLAN的模式 */
    PPI_FDB_KEY_BY_PORT,                     /* 基于PORT的模式 */
    PPI_FDB_KEY_BY_DYNAMIC,
    PPI_FDB_KEY_BY_PORT_VLAN,            /* 基于PORT+VLAN的模式 */
    PPI_FDB_KEY_BY_VLAN_MAC,            /* 基于VLAN+MAC的模式 */
    PPI_FDB_KEY_BY_STATIC,
    PPI_FDB_KEY_BY_BLACKHOLE,
    PPI_FDB_KEY_MODE_MAX,
}PPI_L2IF_FDB_KEY_MODE_E;

/* multicast mac type*/
typedef enum tagPPI_MULTIMAC_TYPE
{
    PPI_MAC_TYPE_UNICAST = 0,   /* 单播MAC类型 */
    PPI_MAC_TYPE_MULTICAST,     /* 多播MAC类型 */
    PPI_MAC_TYPE_MAX,
}PPI_MULTIMAC_TYPE_E;

/*下发PPI消息类型*/
/* 修改该枚举请同步更新TCPIP_PPI_MsgType_En 和 TCPIP_NPUpdate_En*/
enum tagPPIMsgType
{
    PPI_TYPE_ARPMSG,
    PPI_TYPE_IFNETMSG,
    PPI_TYPE_PKTOUT,
    PPI_TYPE_PPPMSG,
    PPI_TYPE_RTMSG,
    PPI_TYPE_TRUNKPORTMSG,
    PPI_TYPE_OSIPKTOUTMSG,
    PPI_TYPE_OAM3AH,
    PPI_TYPE_OAM1AG,
    PPI_TYPE_IGMPMSG,
    PPI_TYPE_L2IFVLANMSG,
    PPI_TYPE_L2IFPORTMSG,
    PPI_TYPE_L2IFMACMSG,
    PPI_TYPE_L2IFQINQMSG,
    PPI_TYPE_VRRPMSG,
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-05 */
    PPI_TYPE_VRF,
    /* End:VISP1.7C03 VRF wangchengyang,2009-02-05   */
    PPI_TYPE_CTRLMSG,
    PPI_TYPE_TRUNKBIND,
    PPI_TYPE_AM4,
    PPI_TYPE_IP6PKTOUT,
    PPI_TYPE_RT6MSG,
    PPI_TYPE_PPPOE,
    PPI_TYPE_MAP,
    /*Added by z00208058/w00207740, TRUNK LACP下移需求开发, 2012/5/2 */
    PPI_TYPE_TRUNKUPDATE,
    PPI_TYPE_POLICYRTUPDATE,  /*CHANDRA */
    PPI_TYPE_VRF6,    /*Added by apurba for VRF6*/

    PPI_TYPE_END
};

/*各子系统采用函数TCPIP_PPI_HookRegisterByType进行注册时，要注册的函数的模块号*/
/*和TCPIP_PPI_HOOK_S结构保持一致顺序*/
enum tagPPIUpdateModuleType
{
    PPI_HOOKTYPE_FIB4,           /*路由更新通知模块号 */
    PPI_HOOKTYPE_ARP,            /*ARP更新通知模块号 */
    PPI_HOOKTYPE_IFNET,          /*接口创建/删除/属性/状态更新通知模块号 */
    PPI_HOOKTYPE_PPP,            /*PPP参数更新通知模块号 */
    PPI_HOOKTYPE_IP4,            /*NP报文处理模块号 */
    PPI_HOOKTYPE_TRUNKPORT,      /* Trunk Port NP下发函数模块号 */
    PPI_HOOKTYPE_OSI,            /*OSI NP报文发送处理处理模块号 */
    PPI_HOOKTYPE_3AH,            /* 3ah NP 下发函数模块号 */
    PPI_HOOKTYPE_1AG,            /*  1AG 配置NP下发模块号 */
    PPI_HOOKTYPE_IGMP,           /*IGMP下发NP通知模块号*/
    PPI_HOOKTYPE_MAP,            /* 下发MAP表项模块号 */
    PPI_HOOKTYPE_FIB6,           /* 下发FIB6路由消息模块号 */
    PPI_HOOKTYPE_VLAN,           /* L2IF VLAN管理消息通知模块号 */
    PPI_HOOKTYPE_PORT,           /* L2IF PORT管理消息通知模块号 */
    PPI_HOOKTYPE_MAC,            /* L2IF MAC管理消息通知模块号 */
    PPI_HOOKTYPE_QINQ,           /* L2IF QINQ管理消息通知模块号 */
    PPI_HOOKTYPE_VRRP,           /* VRRP PPI消息通知,包括使能VRRP和虚拟MAC信息模块号 */
    PPI_HOOKTYPE_VRF,            /* 接口绑定/去绑定VRF PPI下发模块号 */
    PPI_HOOKTYPE_CTRL,           /*多播MAC控制消息模块号*/
    PPI_HOOKTYPE_TRUNKBIND,      /*TRUNK绑定PPI信息下发模块号*/
    PPI_HOOKTYPE_AM4,            /*AM4 地址配置PPI信息下发模块号*/
    PPI_HOOKTYPE_MPLSFW,         /*隧道报文PPI钩子函数模块号*/
    PPI_HOOKTYPE_IP6,            /*IPv6报文发送PPI钩子函数模块号*/
    PPI_HOOKTYPE_PPPOE,          /*下发通知NP PPPOE会话的相关信息模块号*/
    PPI_HOOKTYPE_POLICYRT,    /* Hook type for policyrt -- CHANDRA */

    PPI_HOOKTYPE_END

};

/*PPI函数的返回值*/
enum tagPPIRetValue
{
    PPI_OK,
    PPI_ERR,

    PPI_PACKET_PROCESSED,       /*报文已被处理*/
    PPI_PACKET_NOT_PROCESSED,   /*PPI接口没有处理报文*/
    PPI_RET_END
};

/*协议类型*/
enum tagPPINetProto
{
    PPI_NETPROTO_LCP = 0,
    PPI_NETPROTO_IP,
    PPI_NETPROTO_IPv6,
    PPI_NETPROTO_MUXCP,
    PPI_NETPROTO_LACP,
    PPI_NETPROTO_OSICP,
    PPI_NETPROTO_END
};

/*错误码*/
enum tagPUBLICRetCode
{
    OVER_UPPER_LIMIT = VOS_ERR + 1,     /*2,用户设置值超过上限1024*/
    PUBLIC_HA_IS_SMOOTHING,             /*3,HA正在平滑处理或者手动倒换过程中*/
    DONOT_ENABLE_CACHEDPKT,             /*4,没有使能报文缓存功能*/
    INPUT_NULL_POINTER,                 /*5,输入空指针*/
    INPUT_OVER_MAX_SCOPE,               /*6,输入超过允许的范围*/
    LINK_HOOK_API_NULL_POINTER,         /*7,输入空指针*/
    LINK_HOOK_API_TYPE_WRONG,           /*8,输入类型参数错误*/
    LINK_HOOK_API_MEM_FAIL,             /*9,申请内存失败*/
    LINK_HOOK_API_HOOK_SAME,            /*10,注册函数指针与原有的相同*/
    PUBLIC_ERR_MBUF_NULL,               /*11,报文为空*/
    PUBLIC_ERR_IF_NULL,                 /*12,接口不存在*/
    PUBLIC_ERR_QUEUE_ID,                /*13,报文队列ID非法*/
    PUBLIC_ERR_ENQUEUE_FULL,            /*14,报文入队列时队列已满*/
    PUBLIC_ERR_ENQUEUE_SPLIMP,          /*15,报文入队列时关中断失败*/
    PUBLIC_ERR_ENQUEUE_SPLX,            /*16,报文入队列时开中断失败*/
    PUBLIC_ERR_HEALTH_PARAWRONG,        /*17,Health模块参数非法*/
    PUBLIC_ERR_HEALTH_SETFLAG,          /*18,Health模块开关参数错误*/
    PUBLIC_HEALTH_SMB,                  /*19,当前为背板不允许体检*/
    PUBLIC_ERR_LASTWORD_PARAWRONG,      /*20,临终遗言模块参数非法*/
    PUBLIC_ERR_LASTWORD_MALLOCFAIL,     /*21,临终遗言申请内存失败*/
    PUBLIC_ERR_LASTWORD_NOREG,          /*22,临终遗言输出函数未注册*/
    PUBLIC_ERR_LASTWORD_CHECKUPFAIL,    /*23,临终遗言处理失败*/
    PUBLIC_ERR_HDRTASKNOINIT,           /*24,HDR任务未初始化*/
    PUBLIC_ERR_HDRGETCOMPVTBLFAIL,      /*25,HDR任务获取组件虚表失败*/
    PUBLIC_ERR_HDRCREATETIMERQUEFAIL,   /*26,HDR任务创建定时器队列失败*/
    PUBLIC_ERR_HDRCREATEHELQUEFAIL,     /*27,HDR任务创建体检报告队列失败*/
    PUBLIC_ERR_HDRCREATEINFOQUEFAIL,    /*28,HDR任务创建日志信息队列失败*/
    PUBLIC_ERR_HDRCREATETASKFAIL,       /*29,HDR任务创建失败*/
    PUBLIC_ERR_HDRCREATCCQUEFAIL,       /*30,HDR CC队列创建失败*/
    PUBLIC_ERR_HDR_PARAWRONG,           /*31,HDR参数错误*/
    PUBLIC_ERR_COMPRESS_PARAWRONG,      /*32,数据压缩参数错误*/
    PUBLIC_ERR_COMPRESS_FAILED,         /*33,数据压缩失败*/
    PUBLIC_ERR_PARA_ERR,                /*34,参数错误*/
    PUBLIC_ERR_CHECKBYHOOK,             /*35,通过钩子函数进行释放CPU判断*/
    PUBLIC_ERR_TASKMONITOR_EXIST,       /*36,线程监视钩子函数已经存在*/
    PUBLIC_ERR_VISP_NOT_INIT,           /*37,协议栈还没有初始化*/
};

/*定义错误码 added by l61496 2007-8-1*/
enum  enTcpIpEntryErrorCode
{
    TCPIP_ENTRY_OK = 0,
    TCPIP_ENTRY_ERR,
    TCPIP_ENTRY_NO_PRE_VALUE,           /* 2  没有对应的预配置项 */
    TCPIP_ENTRY_NO_PAF_VALUE,           /* 3  没有对应的PAF预配置项 */
    TCPIP_ENTRY_INPUT_PARA_NULL,        /* 4  输入参数为NULL */
    TCPIP_ENTRY_INPUT_VALUE_INVALID,    /* 5  输入参数值不合法 */
};

/*定义错误码 added by l61496 2007-8-1*/
enum  enTcpIpHAErrorCode
{
    TCPIP_HA_OK = 0,
    TCPIP_HA_ERR,
    TCPIP_HA_BATCH_IS_NOT_OVER,             /*2  批备份没有完成*/
    TCPIP_HA_WRITE_QUEUE_FAIL,              /*3  写消息队列失败*/
    TCPIP_HA_IS_SMOOTHING,                  /*4  HA没有初始化或者处于平滑状态*/
    TCPIP_HA_SET_IFNET_IP_SOCKET_DBG_ERR,   /*5  设置IFNET、IP、SOCKET调试开关失败*/
    TCPIP_HA_SET_ETHARP_DBG_ERR,            /*6  设置ETHARP的HA调试开关失败*/
    TCPIP_HA_SET_TRUNK_DBG_ERR,             /*7  设置TRUNK的HA调试开关失败*/
    TCPIP_HA_SET_PPP_DBG_ERR,               /*8  设置PPP的HA调试开关失败*/
    TCPIP_HA_SET_POEC_DBG_ERR,              /*9  设置PPPE CLIENT 的HA调试开关失败*/
    TCPIP_HA_SET_POES_DBG_ERR,              /*10 设置PPPOE Server的HA调试开关失败*/
    TCPIP_HA_SET_DHCP4C_DBG_ERR,            /*11 设置DHCP4C的HA调试开关失败*/
    TCPIP_HA_SET_SFIB_DBG_ERR,              /*12 设置SFIB的HA调试开关失败*/
    TCPIP_HA_SET_BFD_DBG_ERR,               /*13 设置BFD的HA调试开关失败*/
    TCPIP_HA_SET_DHCP4R_DBG_ERR,            /*14 设置DHCP4R的HA调试开关失败*/
    TCPIP_HA_GET_IFNET_IP_SOCKET_DBG_ERR,   /*15 获取IFNET、IP、SOCKET调试开关失败*/
    TCPIP_HA_GET_ETHARP_DBG_ERR,            /*16 获取ETHARP的HA调试开关失败*/
    TCPIP_HA_GET_TRUNK_DBG_ERR,             /*17 获取TRUNK的HA调试开关失败*/
    TCPIP_HA_GET_PPP_DBG_ERR,               /*18 获取PPP的HA调试开关失败*/
    TCPIP_HA_GET_POEC_DBG_ERR,              /*19 获取PPPE CLIENT 的HA调试开关失败*/
    TCPIP_HA_GET_POES_DBG_ERR,              /*20 获取PPPOE Server的HA调试开关失败*/
    TCPIP_HA_GET_DHCP4C_DBG_ERR,            /*21 获取DHCP4C的HA调试开关失败*/
    TCPIP_HA_GET_SFIB_DBG_ERR,              /*22 获取SFIB的HA调试开关失败*/
    TCPIP_HA_GET_DHCP4R_DBG_ERR,            /*23 获取DHCP4R的HA调试开关失败*/
    TCPIP_HA_GET_PUBLIC_DBG_ERR,            /*24 获取public的HA调试开关失败*/

    TCPIP_HA_REGISTER_TOO_MUCH_ERR,         /*25 外部注册HA模块超出最到值*/
    TCPIP_HA_NAME_TO_LONG_ERR,              /*26 外部注册HA模块名字过长*/
    TCPIP_HA_REGISTER_LAYER_ERR,            /*27 外部注册HA模块层次错误*/
    TCPIP_HA_MODULE_ID_ERR,                 /*28 外部注册HA模块输入ID范围错误*/
    TCPIP_HA_CALL_BACK_NULL_ERR,            /*29 外部注册HA模块输入回调函数错误*/
    TCPIP_HA_CALL_HA_FUN_NULL_ERR,          /*30 外部注册HA模块的功能函数为空*/
    TCPIP_VOS_MALLOC_FAILED_1,              /*31 外部注册HA模块申请内存失败*/
    TCPIP_VOS_MALLOC_FAILED_2,              /*32 外部注册HA模块申请内存失败*/
    TCPIP_HA_MALLOC_FAILED_1,               /*33 TCPIP_HA_MALLOC申请内存失败 */
    TCPIP_HA_MALLOC_FAILED_2,               /*34 TCPIP_HA_MALLOC申请内存失败 */
    TCPIP_HA_WRITE_QUEUE_FAIL_1,            /*35 写消息对列失败  */
    TCPIP_HA_WRITE_QUEUE_FAIL_2,            /*36 写消息对列失败  */
    TCPIP_HA_EXIST_MODULE,                  /*37 模块重复注册 */
    TCPIP_HA_SET_OAM3AH_DBG_ERR,            /*38 设置OAM3AH模块调试开关失败     */
    TCPIP_HA_GET_OAM3AH_DBG_ERR,            /*39 获取OAM3AH模块调试开关失败     */
    TCPIP_HA_SET_OAM1AG_DBG_ERR,            /*40 设置oam1ag的HA调试开关失败*/
    TCPIP_HA_GET_OAM1AG_DBG_ERR,            /*41 获取oam1ag的HA调试开关失败*/
    TCPIP_HA_GET_IGMP_DBG_ERR,              /*42 获取igmp的ha调试开关失败*/

    TCPIP_HA_IF_BATCH_BACKUP_FAIL,          /*43 批量备份IFNET模块失败 */
    TCPIP_HA_IP_BATCH_BACKUP_FAIL,          /*44 批量备份IP模块失败 */
    TCPIP_HA_ETH_BATCH_BACKUP_FAIL,         /*45 批量备份ETH模块失败 */
    TCPIP_HA_TRUNK_BATCH_BACKUP_FAIL,       /*46 批量备份TRUNK模块失败 */
    TCPIP_HA_PPP_BATCH_BACKUP_FAIL,         /*47 批量备份PPP模块失败 */
    TCPIP_HA_POES_BATCH_BACKUP_FAIL,        /*48 批量备份POES模块失败 */
    TCPIP_HA_POEC_BATCH_BACKUP_FAIL,        /*49 批量备份POEC模块失败 */
    TCPIP_HA_LINKLAYER_BATCH_BACKUP_FAIL,   /*50 批量备份外部模块链路层失败 */
    TCPIP_HA_DHCP4C_BATCH_BACKUP_FAIL,      /*51 批量备份DHCP4C模块失败 */
    TCPIP_HA_DHCP4R_BATCH_BACKUP_FAIL,      /*52 批量备份DHCP4R模块失败 */
    TCPIP_HA_SFIB4_BATCH_BACKUP_FAIL,       /*53 批量备份SFIB4模块失败 */
    TCPIP_HA_IPLAYER_BATCH_BACKUP_FAIL,     /*54 批量备份外部模块网络层失败 */
    TCPIP_HA_SOCK_BATCH_BACKUP_FAIL,        /*55 批量备份SOCK模块失败 */
    TCPIP_HA_BFD_BATCH_BACKUP_FAIL,         /*56 批量备份BFD模块失败 */
    TCPIP_HA_APPLAYER_BATCH_BACKUP_FAIL,    /*57 批量备份外部模块应用层失败 */
    TCPIP_HA_PUBLIC_BATCH_BACKUP_FAIL,      /*58 批量备份PUBLIC模块失败 */
    TCPIP_HA_OAM3AH_BATCH_BACKUP_FAIL,      /*59 批量备份OAM3AH模块失败 */
    TCPIP_HA_OAM1AG_BATCH_BACKUP_FAIL,      /*60 批量备份OAM1AG模块失败 */
    TCPIP_HA_IGMP_BATCH_BACKUP_FAIL,        /*61 批量备份IGMP模块失败 */
    TCPIP_HA_VRF_BATCH_BACKUP_FAIL,         /*62 批量备份VRF模块失败 */
    TCPIP_HA_SET_VRF_DBG_ERR,               /*63 设置VRF的HA调试开关失败*/
    TCPIP_HA_GET_VRF_DBG_ERR,               /*64 获取VRF的HA调试开关失败*/
    TCPIP_HA_NOT_INIT,                      /*65 HA未初始化 */
    TCPIP_HA_EVENT_INVALID,                 /*66 HA事件类型不合法 */
    TCPIP_HA_NOT_MASTER,                    /*67 单板不是主板 */
    TCPIP_HA_ERROR_SETTIME,                 /*68 HA 动态参数设置错误*/
    TCPIP_HA_ERROR_SWITCH,                  /*69 HA延时选择开关设置错误*/
    TCPIP_HA_TWAMP_BATCH_BACKUP_FAIL,  /*70 Batch backup for TWAMP Module is failed*/
};

/*定义tcpip_debug.c中函数错误码 added by l61496 2007-8-1*/
typedef enum enTcpIpDbgErrorCode
{
    TCPIP_DBG_OK = 0,
    TCPIP_DBG_ERR,
    TCPIP_DBG_TCP4,
    TCPIP_DBG_UDP4,
    TCPIP_DBG_ICMP4,
    TCPIP_DBG_PP4,
    TCPIP_DBG_ETHARP,
    TCPIP_DBG_PPP,
    TCPIP_DBG_ERR_CMD,/*错误的命令字 */
    TCPIP_DBG_ERR_MID, /*错误的模块ID号*/
    TCPIP_DBG_ERR_DBG_LEVEL /*错误的DBG等级*/
}TCPIP_DEBUG_ERR_CODE_E;

/*定义Debug级别*/
typedef enum TCPIP_DEBUG_LEVEL_Etag
{
    ERR_LEVEL_TEST = 1,
    ERR_LEVEL_INFO,
    ERR_LEVEL_WARNING,
    ERR_LEVEL_ERROR,
    ERR_LEVEL_END
}TCPIP_DEBUG_LEVEL_E;

/*定义日志的输出等级*/
typedef enum TCPIP_LOG_LEVEL_Etag
{
    TCPIP_LOG_LEVEL_CRITICAL = 0,
    TCPIP_LOG_LEVEL_ERROR,
    TCPIP_LOG_LEVEL_WARNING,
    TCPIP_LOG_LEVEL_INFO,
    TCPIP_LOG_LEVEL_DEBUG,
    TCPIP_LOG_LEVEL_END
}TCPIP_LOG_LEVEL_E;

/*定义Debug的模块信息*/
typedef enum TCPIP_DEBUG_MID_INFO_Etag
{
    DEBUG_SOCKET = 1,
    DEBUG_TCP4,
    DEBUG_UDP4,
    DEBUG_ICMP4,
    DEBUG_PP4,
    DEBUG_ETHARP,
    DEBUG_PPP,
    DEBUG_ATTACK,
    DEBUG_RIP4,
    DEBUG_ALL
}TCPIP_DEBUG_MID_INFO_E;

/*可入队列的报文类别*/
/*【注意】每创建一个队列时，都应该在TCPIP_RESLIMIT_MSG_EN的中添加相应的列队名称信息 */
enum enumQueID
{
    RESERVE    = 0,
    QUE_LINK_LAYER,
    QUE_ARP,
    QUE_PPP_NEGO,
    QUE_PPP_ASY,
    QUE_PPP_STAC,
    QUE_PPP_MP,
    QUE_IP_INPUT ,
    QUE_IPV6_INPUT,
    QUE_PPPOE_CLIENT_INPUT,


    QUE_PPPMUX_INPUT,

    QUE_LACP,         /* LACP报文队列 */
    QUE_POES,         /* PPPoE Server报文队列 */
    QUE_ISIS_INPUT,   /* ISIS报文队列 */
    QUE_INARP,

    QUE_MAX_NUMBER

};

/* 性能优化表项/报文流类型 */
enum tagOPTEntryType
{
    OPTIM_ENTRY_RCVTYPE = 1,
    OPTIM_ENTRY_FWDTYPE,
    OPTIM_ENTRY_SNDTYPE,
};

/* 定义的HA注册层枚举值 */
typedef enum enumHALAYERMID
{
    HA_LINK_LAYER = 0,
    HA_IP_LAYER = 1,
    HA_APP_LAYER = 2,
    HA_MID_LAYER_MAX = 3,
}HALAYERMID_E;

/* 分配给外部模块的模块ID范围是 (127, 255) */
typedef enum enumHAMIDExtend
{
    HA_EXTERN_MID_MIN = 127,
    HA_MID_IPOA,                /* IPOA HA */
    HA_EXTERN_MID_MAX = 255,
}HAMIDEXTEND_E;

/* HA回调函数结构定义 */
typedef struct tagTCPIP_HA_CALLBACK
{
    /* HA批备份完成回调通知钩子 */
    ULONG (*pfHA_BATCH_HOOK_FUNC)(VOID);

    /* HA平滑完成回调通知钩子 */
    ULONG (*pfHA_SMOOTH_HOOK_FUNC)(VOID);

    /* HA手动倒换完成回调通知钩子 */
    ULONG (*pfHA_NOTIFYSWITCH_HOOK_FUNC)(VOID);
} TCPIP_HA_CALLBACK_S ;

/* 注册HA模块的钩子函数集合 */
typedef struct tagTCPIP_HA_MODULE_CALLBACK
{
    /* HA批备份回调通知钩子 */
    ULONG (*pfHA_BATCH_HOOK_FUNC)(VOID);

    /* HA平滑回调通知钩子 */
    ULONG (*pfHA_SMOOTH_HOOK_FUNC)(VOID);

    /*备板接收HA报文接口*/
    ULONG (*pfHA_Input)(UCHAR *pucBuf, ULONG ulMsgLen);

    /* HA手动倒换完成回调通知钩子 */
    ULONG (*pfHA_NOTIFYSWITCH_HOOK_FUNC)(VOID);

    ULONG (*pfHA_Clean)(VOID);/*清除模块信息的函数接口*/

} TCPIP_HA_MODULE_CALLBACK_S;

/* HA 统计信息定义 */
typedef struct tagHASTAT
{
    ULONG   ulIPackets;     /* 接收备份消息包个数 */
    ULONG   ulOPackets;     /* 发送备份消息包个数 */
    ULONG   ulIBytes;       /* 接收备份消息字节数,包括HA首部长度 */
    ULONG   ulOBytes;       /* 发送备份消息字节数,包括HA首部长度 */
    ULONG   ulErrPacket;    /* 错误消息包个数(包含报文长度和通道传送报文长度不一致、报文类型中长度字段为0) */
    ULONG   ulBadCheckSum;  /* 校验和错误消息包个数 */
    ULONG   ulBadVersion;   /* 错误版本消息包个数 */
    ULONG   ulHARcvSeq;     /* 最近接收的备份消息序号 */
    ULONG   ulHADropSeq;    /* 最近丢失的备份消息序号 */
    ULONG   ulHADropNum;    /* 最近丢包个数 */
    ULONG   ulHADropSum;    /* 丢包总个数 */
    ULONG   ulHADisorder;   /* 乱序报文统计个数 */
    ULONG   ulSendFailSum;  /* 发送报文失败个数 */
    ULONG   ulCreateIntfSum;/* 备板创建接口失败 */
    ULONG   ulNoIntfSum;    /* 由于没有接口导致备份消息无效个数 */
    ULONG   ulNoTypeSum;    /* 不识别报文统计信息 */
    ULONG   ulNullPkt;      /*空报文统计信息*/
}HASTAT_S;

typedef struct tagHADBG_S
{
#ifndef SOCK_HA_MAX_DEBUG
#define SOCK_HA_MAX_DEBUG 5
#endif
    ULONG  ulEthDbg;            /* 以太备份调试开关状态 */
    ULONG  ulPppDbg;            /* PPP备份调试开关状态 */
    ULONG  ulPoecDbg;           /* Poec备份调试开关状态 */
    ULONG  ulIfnetDbg;          /* IFNET备份调试开关状态 */
    ULONG  ulTrunkDbg;          /* TRUNK备份调试开关状态 */
    ULONG  ulIpDbg;             /* IP备份调试开关状态 */
    ULONG  ulSfibDbg;           /* SFIB备份调试开关状态 */
    ULONG  ulBfdDbg;            /* BFD备份调试开关状态 */
    ULONG  ulDhcpDbg;           /* DHCP备份调试开关状态 */
    ULONG  ulDhcp4rDbg;         /* DHCP Relay备份调试开关状态 */
    ULONG  aulSockHaDebug[SOCK_HA_MAX_DEBUG]; /* SOCKET备份调试开关状态 */
    ULONG  ulPoesDbg;           /* Poes debug switch */
    ULONG  ulPubDbg;            /* Public debug switch */
    ULONG  ulOam3ahDbg;         /* 3AH模块备份调试开关 */
    ULONG  ulOam1agDbg;         /* 1AG模块备份调试开关*/
    ULONG  ulIgmpDbg;           /* igmp debug switch*/
    ULONG  ulVrfDbg;            /* Vrf debug switch*/
}HADBG_S;

/*路由PPI结构*/
typedef struct tagPPI_RTMSG4
{
    ULONG    ulDestination;       /*目的地址*/
    ULONG    ulNexthop;           /*下一跳*/
    ULONG    ulLocalAddress;      /*本地出接口地址*/
    ULONG    ulIfIndex;           /*出接口IFNET索引*/
    ULONG    ulATIndex;           /*virtual link index*/
    ULONG    ulSlot;              /*路由的槽号，暂不使用*/
    ULONG    ulFlags;             /*路由标记*/
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    ULONG    ulVrfIndex;          /*接口所属VRF索引*/
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    UCHAR    ucDestPrefixLength;  /*目的地址掩码长度*/
    UCHAR    ucLocalPrefixLength; /*本地出接口地址掩码长度*/
    USHORT   usRTPri;             /*路由优先级*/
    UCHAR    ucIfName[IF_MAX_INTERFACE_NAME_LEN + 1]; /* 接口名 */
    ULONG ulPmtu;
}PPI_RTMSG4_S;

/*ARP PPI结构*/
typedef struct tagPPI_ARP
{
    ULONG   ulFlags;           /*resolved or resolving，静态还是动态*/
    ULONG   ulRtIfIndex;       /*接口索引*/
    ULONG   ulRtIpAddr;        /*地址，网络字节序*/
    ULONG   ulVlinkIndex;      /*VLINK index*/
    ULONG   ulVlanFlag ;       /*暂不使用*/
    ULONG   ulVlanId;          /*暂不使用*/
    UCHAR   ucMacAddr[6];      /*physical地址*/
    UCHAR   ucSourceType;      /*动态ARP的来源:自学习、用户配置、配置后给自学习更新*/
    UCHAR   ucReserved;
    ULONG   ulPortIfIndex;     /*二层端口索引*/
    /* Begin:VISP1.7C03 VRF wangchengyang , 2009-02-09 */
    ULONG    ulVrfIndex;
    /* End: VISP1.7C03 VRF wangchengyang , 2009-01-09 */

    /*arp Mccp support V300R001C00 --  start*/
    ULONG ulRemainExpireTime;         /*Remaining Expiry Time*/
    /*arp Mccp support V300R001C00 --  start*/

}PPI_ARP_S;

typedef struct tagPPI_MAP
{
    UCHAR   ucType;             /* MAP类型: IP/InARP/Default */
    UCHAR   ucPadding[3];
    ULONG   ulRtIfIndex;        /* 接口索引 */
    ULONG   ulIPAddr;           /* 地址 */
    ULONG   ulVLinkIndex;       /* virtual link index */
    USHORT  usVPI;              /* VPI */
    USHORT  usVCI;              /* VCI */
    ULONG   ulVccIndex;         /* Vcc Index */
}PPI_MAP_S;
typedef struct tagPPI_RTMSG6
{
    ULONG    ulDestination[4];       /*目的地址*/
    ULONG    ulNexthop[4];           /*下一跳*/
    ULONG    ulIfIndex;           /*出接口IFNET索引*/
    ULONG    ulATIndex;           /*virtual link index*/
    ULONG    ulSlot;              /*路由的槽号，暂不使用*/
    ULONG    ulFlags;             /*路由标记*/
    ULONG    ulDestPrefixLength;  /*目的地址掩码长度*/
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    ULONG    ulVrfIndex;          /*接口所属VRF */
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    UCHAR    ucIfName[IF_MAX_INTERFACE_NAME_LEN + 1];   /*接口名*/
    ULONG    ulRtPri;             /*路由优先级*/
}PPI_RTMSG6_S;
/* 3ah PPI下发信息数据结构 */
#define LCLRMT_INFOTLV_LEN  32
#define INFOTLV_MAX_LEN     47  /* INFO OAMPDU最大可能长度宏,实际NP下发tlv长度以ulTlvPktLen为准 */
#define PPI_3AH_LB_LOCAL    1
#define PPI_3AH_LB_REMOTE   2
typedef struct tagPpi3ah
{
    UCHAR  aucTlvPkt[INFOTLV_MAX_LEN];      /* 本端/对端TLV报文 + 组织自定义tlv(可能有)[不含end tlv],各字段都为网络序 */
    UCHAR  ucTlvPktLen;                     /* 实际下发的info tlv pkt长度 */

    USHORT usFlags;                         /* 报文的FLAG标记,主机序,下同   */
    UCHAR  aucPeerMac[6];                   /* 对端physical地址                  */
    ULONG  ulDetectInterval;                /* 探测周期,ms为单位            */
    ULONG  ulLbState;                       /* 本端环回状态,1-LB_LOCAL/2-LB_REMOTE              */
    ULONG  ulLbTestMode;                    /* 环回测试模式,0－visp软件测试模式，1－NP测试模式  */

    /* 本端信息 */
    USHORT usLclOamPduCfg;                  /* 本端配置的OAMPDU大小     */
    USHORT usLclRevision;                   /* 本端Revision值           */

    /* 对端信息 */
    USHORT usRmtOamPduCfg;                  /* 对端配置的OAMPDU大小     */
    USHORT usRmtRevision;                   /* 对端Revision值           */
}PPI_3AH_S;

/* Begin:VISP1.7C03 VRF wangchengyang , 2009-02-04 */
typedef struct tagVRF_PPI_S
{
    ULONG ulVrfIndex;               /* VRF索引 */
    ULONG ulIfIndex;                /* 接口索引 */
    /*Added by limin00188004, 支持全局和VRF域的控制License, 2012/9/26   问题单号:S.VRF.02.01 */
    ULONG ulLicence;                /* Licence标识，0是关闭，1是打开*/
    /* End of Added by limin00188004, 2012/9/26   问题单号:S.VRF.02.01 */
}VRF_PPI_S;
/* End:VISP1.7C03 VRF wangchengyang , 2009-02-04 */

/*Added by apurba for VRF6*/
typedef struct tagVRF6_PPI_S
{
    ULONG ulVrfIndex;
    ULONG ulIfIndex;
    ULONG ulLicence;
}VRF6_PPI_S;

/* L2IF FDB PPI结构*/
typedef struct tagPPI_L2IF_FDB_ENTRY
{
    UCHAR aucMacAddr[MACADDRLEN];        /* physical地址 */
    USHORT usVlanId;             /* physical地址所属VLAN ID */
    ULONG ulIfIndex;            /* 接口索引 */
    USHORT usOutCeVlanId;    /*用户侧VLAN ID */
    UCHAR ucType;              /* physical地址表项类型 */
    UCHAR usReserved;       /* 保留字段*/
}PPI_L2IF_FDB_ENTRY_S;

/* PPI FDB KEY结构，主要用于FDB表项删除操作 */
typedef struct tagPPI_L2IF_FDB_KEY
{
    UCHAR  aucMacAddr[MACADDRLEN];       /* physical地址 */
    USHORT usVlanId;                     /* VLAN ID */
    ULONG  ulIfIndex;                    /* 接口索引 */
    ULONG ulTransMode;   /*标识stacking或者是mapping*/
    USHORT usFlag;         /* 对于端口离开vlan,该标志位用于产品判断是否要进行下发,
                              如果下发是批量下发还是按原有流程单个下发
                              0:按原有流程单个下发
                              1:批量下发
                              2:不做任何处理*/
    USHORT usStartVlan;    /* 用于批量下发startvlan*/
    USHORT usEndVlan;      /* 用于批量下发endvlan*/
    USHORT usPVID;        /* PVID */
    UCHAR  ucFdbFlag;       /* VLAN/QINQ 标志 */
    UCHAR  ucType;                  /* 表项类型 */
    UCHAR  ucKeyMode;        /* 键值类型 */
    UCHAR  ucResved;        /* 保留字段 */
}PPI_L2IF_FDB_KEY_S;

/* VRRP PPI结构 用于添加删除虚IP */
typedef struct tagPPI_VRRP_UPDATEMAC
{
    ULONG ulVrId;                             /* 备份组ID */
    ULONG ulVirtualIP;                        /* 虚IP(网络序) */
    UCHAR aucVirtualMacAddr[MACADDRLEN];      /* 虚physical地址 */
    UCHAR ucReserved[2];                      /* 保留字段 */
}PPI_VRRP_UPDATEMAC_S;

/* VRRP PPI结构 用于S***R VLAN添加移除SUB VLAN时通知SUB VLAN添删虚拟MAC的处理 */
typedef struct tagPPI_VRRP_VLAN
{
    ULONG ulVrId;                             /* 备份组ID */
    UCHAR aucVirtualMacAddr[MACADDRLEN];      /* 虚physical地址 */
    UCHAR ucReserved[2];                      /* 保留字段 */
    ULONG ulIfIndex;
    ULONG ulSuperVlanId;
    ULONG ulSubVlanId;
}PPI_VRRP_VLAN_S;

/* 多播physical地址PPI结构定义 */
typedef struct tagPPI_MULTIMAC
{
    ULONG ulIfIndex;
    UCHAR aucMultiMacAddr[MACADDRLEN];  /* 多播physical地址 */
    UCHAR aucMultiMacMask[MACADDRLEN];  /* physical地址的掩码*/
}PPI_MULTIMAC_S;


/*TRUNK绑定PPI信息下发结构*/
typedef struct tagPPI_TRUNK_BIND
{
    ULONG   ulIfIndex;    /* 接口索引 */
    ULONG   ulTrunkId;    /* TRUNK接口ID */
    USHORT  usPri;        /* 绑定端口优先级 */
    USHORT  usReserved;   /* 保留 */
}PPI_TRUNK_BIND_S;

/*AM4 地址配置PPI信息下发结构*/
typedef struct tagPPI_IPADDR_INFO
{
    ULONG   ulIfIndex;      /* 接口索引 */
    ULONG   ulVrfIndex;     /* VRF索引 */
    ULONG   ulIpAddr;       /* 地址,网络序 */
    ULONG   ulSubnetMask;   /* 地址掩码 */
    ULONG   ulFlag;         /* 主从地址标记,1 从IP标记, 2 主IP标记 */
}PPI_IPADDR_INFO_S;

/* Add for V2R3C07, by z00208058/w00207740, at 2012-4-16. 修改原因: TRUNK LACP下移需求开发 */
/*TRUNK LACP链路保活设置PPI信息下发*/
typedef struct tagPPI_TRUNK_LACP
{
    ULONG  ulPortIfIndex;                           /* 成员端口接口索引 */
    UCHAR  ucPortMacAddress[MACADDRLEN];            /* TRUNK接口MAC，二层封装用*/
    UCHAR  ucActorExpiredType;                      /* 本端的发送周期模式0--长周期；1--短周期*/
    UCHAR  ucPartnerExpiredType;                    /*对端的发送周期模式0--长周期；1--短周期*/
    /* 本端信息 */
    USHORT usActorOperKey;                          /* 本端端口运作Key */
    USHORT usActorOperPortPri;                      /* 本端端口运作优先级 */
    USHORT usActorOperPortIndex;                    /* 本端端口运作端口号 */
    USHORT usActorOperSysPri;                       /* 本端系统运作优先级 */
    UCHAR  ucActorOperSysMac[MACADDRLEN];           /* 本端系统运作MAC */
    UCHAR  ucActorOperState;                        /* 本端端口运作状态值 */
    UCHAR  ucActorReserve;                          /* 保留字段 */

    /* 对端信息 */
    USHORT usPartnerOperKey;                        /* 对端端口运作Key */
    USHORT usPartnerOperPortPri;                    /* 对端端口运作优先级 */
    USHORT usPartnerOperPortIndex;                  /* 对端端口运作端口号 */
    USHORT usPartnerOperSysPri;                     /* 对端系统运作优先级 */
    UCHAR  ucPartnerOperSysMac[MACADDRLEN];         /* 对端系统运作MAC */
    UCHAR  ucPartnerOperState;                       /* 对端端口运作状态值 */
    UCHAR  ucPartnerReserve;                         /* 保留字段 */
}PPI_TRUNK_LACP_S;

typedef struct tagPPI_POLICYRT
{
    ULONG ulPolicyID;
    ULONG ulVrfIndex;
    ULONG ulNodeID;
    ULONG ulMatchCountLow32;
    ULONG ulMatchCountHigh32; /*命中次数，只有当PPI_POLICYRT_ GET_NODE_COUNT 时由TRAN返回*/
    ULONG ulAclGroup;      /*ACL规则组号*/
    ULONG ulOutIfIndex;    /*匹配成功后设置的出接口索引*/
    ULONG ulUserData;      /*自定义数据*/
    ULONG ulNextHop;       /*匹配成功后设置的下一跳信息，网络序*/
} PPI_POLICYRT_S;

typedef struct tagTCPIP_PPI_HOOK
{
    /*路由更新通知 */
    ULONG (*pfTCPIP_PPI_FIB4_Update)(ULONG ulOperType, PPI_RTMSG4_S *pstRtMsg);
    /*ARP更新通知 */
    ULONG (*pfTCPIP_PPI_ARP_Update)(ULONG ulOperType, PPI_ARP_S *pstArpMsg);
    /*接口创建/删除*/
    /*接口属性/状态更新通知 */
    ULONG (*pfTCPIP_PPI_IFNET_Update)(ULONG ulIfIndex, ULONG ulCmd, VOID *pData);
    /*PPP参数更新通知 */
    ULONG (*pfTCPIP_PPI_PPP_Update)(ULONG ulIfIndex, ULONG ulCmd, VOID *pData );
    /*NP报文处理 */
    ULONG (*pfTCPIP_PPI_IP4_Output)(MBUF_S *pstMbuf);

    /* Trunk Port NP下发函数 */
    ULONG (*pfTCPIP_PPI_TRUNKPORT_Update)(ULONG ulPortIfIndex, ULONG ulCmd, ULONG ulTrunkIfIndex);

    /*Add by z62474 for 2007-09-11,OSI NP报文发送处理处理 */
    ULONG (*pfTCPIP_PPI_OSI_Output)(MBUF_S *pstMbuf);

    /* 3ah NP 下发函数 */
    ULONG (*pfTCPIP_PPI_3AH_Update)(ULONG ulIfIndex, ULONG ulOprType, PPI_3AH_S *pstPpi3ah);

    /*  1AG 配置NP下发 */
    ULONG  (*pfTCPIP_PPI_1AG_Update) (ULONG ulIfIndex, ULONG ulOprType,VOID* pEoam1agMsg);

    /*IGMP下发NP通知*/
    ULONG (*pfTCPIP_PPI_IGMP_Update)(ULONG ulIfIndex,ULONG ulCmd,ULONG ulMultiAddr);

    /* 下发MAP表项 */
    ULONG (*pfTCPIP_PPI_MAP_Update)(PPI_MAP_S *pstMapInfo, ULONG ulOperType);

    /* 下发FIB6路由消息 */
    ULONG (*pfTCPIP_PPI_FIB6_Update)(ULONG ulOperType, PPI_RTMSG6_S *pstRtMsg);

    /* L2IF VLAN管理消息通知 */
    ULONG (*pfTCPIP_PPI_VLAN_Update)(ULONG ulVid, ULONG ulCmd, VOID *pData);

    /* L2IF PORT管理消息通知 */
    ULONG (*pfTCPIP_PPI_PORT_Update)(ULONG ulIndex, ULONG ulCmd, VOID *pData);

    /* L2IF MAC管理消息通知 */
    ULONG (*pfTCPIP_PPI_MAC_Update)(ULONG ulCmd, VOID *pData);

    /* L2IF QINQ管理消息通知 */
    ULONG (*pfTCPIP_PPI_QINQ_Update)(ULONG ulIndex, ULONG ulCmd, VOID *pData);

    /* VRRP PPI消息通知,包括使能VRRP和虚拟MAC信息 */
    ULONG (*pfTCPIP_PPI_VRRP_Update)(ULONG ulIfIndex, ULONG ulCmd, VOID *pData);

    /* Begin:VISP1.7C03 VRF wangchengyang , 2009-02-04 */
    /* 接口绑定/去绑定VRF PPI下发 */
    ULONG (*pfTCPIP_PPI_VRF_Update)(ULONG ulOperType, VRF_PPI_S *pstVrfMsg);
    /* End:VISP1.7C03 VRF wangchengyang , 2009-02-04 */

    /* Download multicase mac control message  */
    /*
     ulOperType  ==  add or del
     ulMsgType  ==  MultiMac、.....
     pData  :  struct for xxx
        typedef struct tagPPI_MULTIMAC
        {
            ULONG ulIfIndex;
            UCHAR aucMultiMacAddr[MACADDRLEN];
            UCHAR aucMultiMacMask[MACADDRLEN];
        }PPI_MULTIMAC_S;
    */
    ULONG (*pfTCPIP_PPI_CTRL_Update)(ULONG ulOperType, ULONG ulMsgType, VOID * pData);

    ULONG (*pfTCPIP_PPI_TRUNKBIND_Update)(ULONG ulOperType, PPI_TRUNK_BIND_S *pstTrunkBind);

    ULONG (*pfTCPIP_PPI_AM4_Update)(ULONG ulOperType, PPI_IPADDR_INFO_S *pstIpAddrInfo);

    ULONG (*pfTCPIP_PPI_MPLSFW_Output)(MBUF_S *pstMbuf, ULONG  ulTunnelInfo);
    /* End: VISP Support multi-instance project */

    /*NP IPV6 报文处理 */
    ULONG (*pfTCPIP_PPI_IP6_Output)(MBUF_S *pstMbuf);

    /* 下发通知NP PPPOE会话的相关信息 */
    ULONG (*pfTCPIP_PPI_PPPOE_Update)(ULONG ulSessionId, ULONG ulPpiCmd, VOID *pData);
    /* Add for V2R3C07, by z00208058/w00207740, at 2012-4-16. 修改原因: TRUNK LACP下移需求开发 */
    /*TRUNK 下发通知NP LACP链路保活相关信息*/
    ULONG (*pfTCPIP_PPI_TRUNK_LACP_Update)(ULONG ulOperType, PPI_TRUNK_LACP_S *pstRtMsg);

    ULONG (*pfTCPIP_PPI_POLICYRT_Update)(ULONG ulOperType, PPI_POLICYRT_S *pstRtMsg);

    /*Added by apurba for VRF6*/
    ULONG (*pfTCPIP_PPI_VRF6_Update)(ULONG ulOperType, VRF6_PPI_S *pstVrfMsg);

}TCPIP_PPI_HOOK_S;

/*前缀省略结构*/
typedef struct tagPPIMcPrefix
{
    UCHAR     ucPrefixValid;                    /*是否有效*/
    UCHAR     ucClass;                          /*class*/
    USHORT    usPrefixLength;                   /*Prefix长度*/
    UCHAR     aucPrefix[PPI_MC_PREFIX_MAX_LEN]; /*Prefix内容*/
}PPI_MC_PREFIX_S;

#define     PPI_MP_MP_DISCR_MAX_LENGTH   20  /* 终端描述符的最大长度 */

/*LCP选项PPI结构*/
typedef struct tagNpPppLcpOption
{
    /* 是否协商 */
#if (VRP_LITTLE_ENDIAN == VRP_YES)
    ULONG   breserved          : 22,
            neg_discr          : 1,       /*是否协商终端描述符*/
            neg_magicnumber    : 1,       /* 协商魔术字*/
            neg_prefix         : 1,       /*是否协商前缀省略*/
            neg_mhf            : 1,       /*是否协商MHF*/
            neg_ssnhf          : 1,       /*是否采用短序列号*/
            neg_mrru           : 1,       /*是否协商mrru*/
            neg_mru            : 1,       /**/
            neg_asyncmap       : 1,       /*是否协商ACCM*/
            neg_accompression  : 1,       /*ACFC Compression */
            neg_pcompression   : 1;       /*PFC Compression */
#else
    ULONG   neg_pcompression   : 1,       /*PFC Compression */
            neg_accompression  : 1,       /*ACFC Compression */
            neg_asyncmap       : 1,       /*是否协商ACCM*/
            neg_mru            : 1,       /**/
            neg_mrru           : 1,       /*是否协商mrru*/
            neg_ssnhf          : 1,       /*是否采用短序列号*/
            neg_mhf            : 1,       /*是否协商MHF*/
            neg_prefix         : 1,       /*是否协商前缀省略*/
            neg_magicnumber    : 1,       /* 协商魔术字*/
            neg_discr          : 1,       /*是否协商终端描述符*/
            breserved          : 22;
#endif
    USHORT  usMru;         /*最大接收单元*/
    USHORT  usMrru;        /*最大接收重组单元*/
    ULONG   ulAsyncmap;    /*ACCM的值*/
    UCHAR   ucCode;        /*MHF协商的code值*/
    UCHAR   ucClass;       /*MHF协商的class值*/
    UCHAR   ucDiscr_len;
    UCHAR   ucDiscr_class;
    PPI_MC_PREFIX_S astPrefix[PPI_MC_PREFIX_MAX_NUM];/*前缀省略映射结构*/
    UCHAR   discr_addr[PPI_MP_MP_DISCR_MAX_LENGTH];
    ULONG   ulMagicnumber; /*协商的魔术字*/
}PPI_PPP_LCP_OPTION_S ;


/*IPCP PPI结构*/
typedef struct tagNpPppIpcpOption
{
    /* 是否协商 */
#if (VRP_LITTLE_ENDIAN == VRP_YES)
    ULONG   breserved     : 30,
            neg_vj        : 1,
            neg_iphc      : 1;
#else
    ULONG   neg_iphc      : 1,  /* IPHC Compression? */
            neg_vj        : 1,
            breserved     : 30;
#endif

    /*地址*/
    ULONG   ulOurAddr;          /*本端地址，网络字节序*/
    ULONG   ulHisAddr;          /*对端地址，网络字节序*/
    /*IPHC协商结果*/
    USHORT  usTcpSpace;         /* TCP压缩最大CID值*/
    USHORT  usNonTcpSpace;      /* Non-TCP压缩最大CID值*/
    USHORT  usMaxPeriod;        /*同一报文流中连续发送压缩报文的最大数*/
    USHORT  usMaxTime;          /*同一报文流中发送完整首部报文的最大时间间隔*/
    USHORT  usMaxHeader;        /*允许压缩的首部最大长度*/
    UCHAR   ucCompressType;     /*报文压缩类型*/
    UCHAR   ucRtpCompressType;  /*RTP报文压缩类型*/
}PPI_PPP_IPCP_OPTION_S ;

/*IP6CP PPI结构*/
typedef struct tagNpPppIp6cpOption
{
    /* 是否协商 */
#if (VRP_BIG_ENDIAN == VRP_YES)
    ULONG   neg_interfaceid :  1,   /* Negotiate interface id */
            neg_compprotocol:  1,
            bReserve        :  30;  /* 为了以后扩展预留协商位 */
#else
    ULONG   bReserve        :  30,  /* 为了以后扩展预留协商位 */
            neg_compprotocol:  1,
            neg_interfaceid :  1;   /*  Negotiate interface id */
#endif

    UCHAR   my_interface_id[8],his_interface_id[8];
    USHORT  comp_protocol;   /* protocol value to use in compress protocol option */
    UCHAR   ucPadding[2];
}PPI_PPP_IP6CP_OPTION_S ;

typedef struct tagNpPppMuxcpOption
{
#if (VRP_LITTLE_ENDIAN == VRP_YES)
    ULONG   breserved      : 31,
            neg_defaultpid : 1; /*是否协商Defualt PID*/
#else
    ULONG   neg_defaultpid : 1,
            breserved      : 31;
#endif

    USHORT  usDefaultPid;       /*Defualt PID*/
    USHORT  usReserved;
}PPI_PPP_MUXCP_OPTION_S ;

typedef struct tagNpPppConfigInfo
{
#if (VRP_LITTLE_ENDIAN == VRP_YES)
    ULONG   breserved           : 30,
            bPppReorderWindow   : 1,  /*MP是否使能了reorder windows*/
            bPppInterleave      : 1;  /*MP是否使能了LFI功能*/
#else
    ULONG   bPppInterleave      : 1,  /*MP是否使能了LFI功能*/
            bPppReorderWindow   : 1,  /*MP是否使能了reorder windows*/
            breserved           : 30;
#endif
     /*以下是PPPMUX配置参数*/
    USHORT usMaxSubFrameLen;    /*最大子帧长度*/
    USHORT usMaxFrameLen;       /*最大复合帧长度*/
    USHORT usMaxSubFrameNum;    /*最大子帧数目*/
    USHORT usMaxDelay;          /*定时器超时时间*/
    /*MP配置参数*/
    USHORT usMinFragLen;        /*最小分片长度*/
    USHORT usMaxDelayLFI;       /*最大分片时延*/
    ULONG  ulNegoSubOptions ;  /*是否协商子选项*/
}PPI_PPPCONFIGINFO_S;

#define PPI_MP_SUPPORT_MAX_BIND  128   /*MP支持最大绑定子链路数*/

/*MP接口核查特有信息*/
typedef struct tagPPIMpInfo
{
    /*MP父通道绑定的子链路索引数组(已生效的)*/
    ULONG ulMpBindSubLink[PPI_MP_SUPPORT_MAX_BIND];
    /*MP父通道绑定的子链路数*/
    ULONG ulMpBindNum;
}PPI_MPINFO_S;

/*需要核查的信息结构*/
typedef struct tagPPIPppInfo
{
    ULONG                   ulIfIndex;        /*接口索引*/
    PPI_PPP_LCP_OPTION_S    stLCPGotOption;
    PPI_PPP_LCP_OPTION_S    stLCPHisOption;
    PPI_PPP_IPCP_OPTION_S   stIPCPGotOption;
    PPI_PPP_IPCP_OPTION_S   stIPCPHisOption;
    PPI_PPP_IP6CP_OPTION_S   stIP6CPGotOption;
    PPI_PPP_IP6CP_OPTION_S   stIP6CPHisOption;
    PPI_PPP_MUXCP_OPTION_S  stMUXCPGotOption;
    PPI_PPP_MUXCP_OPTION_S  stMUXCPHisOption;
    PPI_PPPCONFIGINFO_S     stConfigInfo;
    PPI_MPINFO_S            stMPInfo;         /*MP接口相关信息，如果是非MP接口则为空*/
}PPI_PPP_INFO_S;

/*配置模块CCM报文参数结构体*/
typedef struct tagPpi_1AGCcmMsg
{
    UCHAR  szMdName[OAM_1AG_MAX_MDNAME_LEN + 1];  /*MD名 ,44字节*/
    UCHAR  szMaName[OAM_1AG_MAX_MANAME_LEN + 1];  /*MD名 ,44字节*/
    USHORT usMepId;             /*MEPID值*/
    USHORT usVId;               /*vlan ID值*/
    UCHAR  ucMdLevel;           /*MD Level信息*/
    UCHAR  ucCcmInterval;       /*发送周期*/
    UCHAR  ucRdiFlag;           /*MA内的RDI标记,取值0，1*/
    UCHAR  ucMaPri;             /*MA的VLAN优先级*/
    UCHAR  ucCompatibleType;    /*1AG兼容模式*/
    UCHAR  uc1agVersion;        /*MEP使用的1AG版本号,0:Draft7版本;1:标准版本;2:Y1731版本*/
    UCHAR  ucVlanFlag;          /*该MEP下发送的报文是否带VLAN头标志.
                                  0:表示不需要带VLAN头,1表示需要带VLAN*/
    UCHAR  ucCcSendEnable ;     /* CCM 使能标记*/
    ULONG  ulIfIndex;           /* MEP所属的接口索引*/
    USHORT usLossDetectTimer;

    USHORT  ucPadding;
}PPI_1AGCCMMSG_S;

/* 新增1731 PM结构体 */
typedef struct tagPpi_Y1731PMMsg
{
    UCHAR  szMdName[OAM_1AG_MAX_MDNAME_LEN + 1];  /*MD名 ,44字节*/
    UCHAR  szMaName[OAM_1AG_MAX_MANAME_LEN + 1];  /*MA名 ,44字节*/
    USHORT usMepId;                               /*MEPID值*/
    USHORT usRmepId;                              /*RMEPID值*/
    ULONG  ulInterval;                            /*发送周期*/
    ULONG  ulTimeOut;                             /*超时时间*/
}PPI_Y1731PMMSG_S;

/* 1AG MA参数 */
typedef struct tagPpi_1AGMaMsg
{
    UCHAR  szMdName[OAM_1AG_MAX_MDNAME_LEN + 1];  /*MD名 ,44字节*/
    UCHAR  szMaName[OAM_1AG_MAX_MANAME_LEN + 1];  /*MD名 ,44字节*/
    UCHAR  ucCcmInterval;       /* 发送周期*/
    UCHAR  ucCompatibleType;    /* 1AG兼容模式*/
    USHORT usVlanId;            /* MA的VLAN id */
    UCHAR  ucMaPri;             /* MA的VLAN优先级*/
    UCHAR  ucRdiFlag;           /* MA内的RDI标记,取值0，1*/
    UCHAR  ucMaNameType;        /* MD名字类型,目前只支持字符串形式*/
    UCHAR  ucRes;
}PPI_1AGMAMSG_S;

/* 1AG全局变量 */
typedef struct tagPpi_1AGGlobalMsg
{
    USHORT usPktType;       /*1AG报文类型*/
    UCHAR  ucPktPriority;   /*1AG报文优先级*/
    UCHAR  ucRes;
    ULONG  ulCompatibleSwitch; /*协议兼容性开关*/
}PPI_1AGGLOBALMSG_S;

/* Add for V2R3C06, by shuxieliu00176784, at 2011-10-04. 修改原因: 1AG全局协议版本 支持EOAM协议版本全局设置  */
typedef struct tagPpi_1AGVersionMsg
{
    ULONG  ulGlobalVersion;  /* 全局协议版本 */
}PPI_1AGVERSION_MSG_S;

/*1AG RMEP参数*/
typedef struct tagPpi_1AGRmepPara
{
    ULONG  ulIfIndex;       /*Rmep对应的出接口,不同接口上可以维护相同远端MEP*/
    USHORT usVlanId;        /*VLAN ID,通过VLAN ID可找到对应的MA、MD*/
    USHORT usRmepId;        /*Rmep Id值*/
    UCHAR  ucInterval;      /*远端MEP的发送周期类型, 微码驱动接收到后需先转换为类型所表示的间隔值，然后乘以3.5倍作为超时周期*/
    UCHAR  ucMdLevelFlag;   /*收到RMEP大于本端MD Level,大于只做老化计时,等于则需同时做老化、超时及时*/
    UCHAR  aucMacAddr[MACADDRLEN];   /*远端physical地址*/
    UCHAR  aucMdName[OAM_1AG_MAX_MDNAME_LEN + 1];   /*维护域名称 */
    UCHAR  aucMaName[OAM_1AG_MAX_MANAME_LEN + 1];   /*维护组名称 */

    UCHAR  ucRdiFlag;         /* Rdi 标识*/
    UCHAR  ucRemoteIfFlag;    /* 0: 没有Interface TLV 1: 有，且接口为UP  2： 有，且接口为DOWN */
    UCHAR  ucVlanFlag;        /* 标识上次收到的CCM是否带有VLAN 1 :有  0 :没有*/
    UCHAR  ucRMepStatic;      /* 0表示动态生成的RMEP ，1表示静态创建的RMEP */
    UCHAR  ucMdLevel;         /* MD Level */
    UCHAR  ucPad[3];
}PPI_1AGRMEPPARA_S;

/* 1AG MD参数 */
typedef struct tagPpi_1AGMDMsg
{
    UCHAR  szMdName[OAM_1AG_MAX_MDNAME_LEN + 1];   /* MD名 ,44字节 */
    UCHAR  ucMdLevel;                              /* MD Level */
    UCHAR  ucMdNameType ;                          /* MD名字类型,目前只支持字符串形式 */
    UCHAR  ucPad[2];
}PPI_1AGMDMSG_S; /*该结构为新增*/

typedef struct tagNpIGMPConfigInfo
{
    ULONG ulMultiAddr;          /* 多播组地址 */
    ULONG ulIfIndex;            /* 接口索引 */
}PPI_IGMPConfigInfo_S;

/* VISVP1R7C03 L2IF,PPI下发数据结构定义 */
typedef struct tagPPI_VlanIf
{
    ULONG   ulIfIndex;           /* vlanif接口索引 */
    UCHAR   aucMac[MACADDRLEN];  /* vlanif physical地址*/
    UCHAR   ucReserved[2];
}PPI_VLANIF_S;

/* 端口抑制PPI下发信息 */
typedef struct tagPPI_RATELIMIT
{
    ULONG ulLimitEnable;   /* 设置或取消端口上指定的抑制类型 */
    ULONG ulLimitType;     /* 抑制类型：上行/下行广播、上行/下行多播、上行/下行未知单播报文 */
    ULONG ulSuppressType;  /* 该字段区分是设置速率抑制比例，还是设置占用带宽的绝对值 */
    ULONG ulSetValue;      /* 设置的值，当ulSuppressType表示是抑制比例时，取比例值；当ulSuppressType
                              表示占用带宽的绝对值时，表示带宽值，
                              （带宽值所表示的含义由驱动自己理解，可以理解为报文个数）。*/
}PPI_RATE_LIMIT_S;

/* 端口加入移除vlan操作PPI下发信息 */
typedef struct tagPPI_VLAN_LIST
{
    ULONG  ulTagFlag;    /* 是否带TAG: VLAN_TAGGED,VLAN_UNTAGGED */
    USHORT usStartVlanID;
    USHORT usEndVlanID;
}PPI_VLAN_LIST_S;

/* 配置TRANS时下发底层信息 */
typedef struct tagPPI_L2TRANS_CONFIGINFO
{
    ULONG  ulIfIndex;      /*二层端口索引*/
    ULONG  ulMode;         /*MODE:stacking ,mapping */
    USHORT usPEVlan;       /*PEVlan（要封装的外层VLAN）*/
    USHORT usMapVlan;      /*Stacking之前对CEVlan进行Mapping的值*/
    USHORT usCEVlanBegin;  /*CEVlan起始值（入报文携带标签中的VLAN号）*/
    USHORT usCEVlanEnd;    /*CEVlan终止值（入报文携带标签中的VLAN号）*/
} PPI_L2TRANS_CONFIGINFO_S;


typedef struct tagTCPIP_PPI_COUNT
{
    /*路由更新通知总次数 */
    ULONG ulRtMsg4Total;
    /*路由更新通知失败次数 */
    ULONG ulRtMsg4Failure;
    /*ARP更新通知总次数 */
    ULONG ulArpUpdateTotal;
    /*ARP更新通知失败次数 */
    ULONG ulArpUpdateFailure;
    /*接口属性更新通知总次数 */
    ULONG ulIfUpdateTotal;
    /*接口属性更新通知失败次数 */
    ULONG ulIfUpdateFailure;

    /*TRUNK PORT属性更新通知总次数 */
    ULONG ulTrunkPortTotal;
    /*TRUNK PORT属性更新通知失败次数 */
    ULONG ulTrunkPortFailure;

    /*PPP参数更新通知总次数 */
    ULONG ulPPPUpdateTotal;
    /*PPP参数更新通知失败次数 */
    ULONG ulPPPUpdateFailure;
    /*NP报文处理总次数 */
    ULONG ulNPOutputTotal;
    /*NP报文处理失败次数 */
    ULONG ulNPOutputFailure;

/*Begin:Add by z62474 for 2007-09-10 ,增加OSI对NP的支持*/
    /*OSI NP报文处理总次数 */
    ULONG ulOSINPOutputTotal;
    /*OSI NP报文处理失败次数 */
    ULONG ulOSINPOutputFailure;
/*End:Add by z62474 for 2007-09-10 ,增加OSI对NP的支持*/

    /* 3AH NP报文处理总次数 */
    ULONG ul3ahNpOutputTotal;
    /* 3AH NP报文处理失败次数 */
    ULONG ul3ahNpOutputFailure;

    /*1AG 通知NP总次数*/
    ULONG ul1agNPOutputTotal;
    /*1AG 通知NP失败次数*/
    ULONG ul1agNPOutputFailure;

    /*IGMP 通知NP总次数 byz00104207*/
    ULONG ulIGMPNPOutputTotal;
    /*IGMP 通知NP失败次数*/
    ULONG ulIGMPNPOutputFailure;

    /*路由更新通知总次数 */
    ULONG ulRtMsg6Total;
    /*路由更新通知失败次数 */
    ULONG ulRtMsg6Failure;

    /* L2IF VLAN 通知NP总次数 */
    ULONG ulL2ifVlanNPOutputTotal;
    /* L2IF VLAN 通知NP失败次数 */
    ULONG ulL2ifVlanNPOutputFailure;

    /* L2IF PORT 通知NP总次数 */
    ULONG ulL2ifPortNPOutputTotal;
    /* L2IF PORT 通知NP失败次数 */
    ULONG ulL2ifPortNPOutputFailure;

    /* L2IF MAC 通知NP总次数 */
    ULONG ulL2ifMacNPOutputTotal;
    /* L2IF MAC 通知NP失败次数 */
    ULONG ulL2ifMacNPOutputFailure;

    /* L2IF QinQ 通知NP总次数 */
    ULONG ulL2ifQinQNPOutputTotal;
    /* L2IF VLAN 通知NP失败次数 */
    ULONG ulL2ifQinQNPOutputFailure;

    /* VRRP 通知NP总次数*/
    ULONG ulVrrpNPOutputTotal;
    /* VRRP 通知NP失败总次数*/
    ULONG ulVrrpNPOutputFailure;

    /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-05   */
    /* VRF更新通知总次数 */
    ULONG ulVrfUpdateTotal;
    /* VRF更新通知失败次数 */
    ULONG ulVrfUpdateFailure;
    /* End:VISP1.7C03 VRF wangchengyang,2009-02-05   */

    /* 多播MAC更新通知总次数 */
    ULONG ulMultiMacUpdateTotal;
    /* 多播MAC更新通知失败次数 */
    ULONG ulMultiMacUpdateFailure;

    ULONG ulTrunkBindTotal;
    ULONG ulTrunkBindFailure;

    ULONG ulAM4IPConfigTotal;
    ULONG ulAM4IPConfigFailure;

    ULONG  ulVpnPacketRecvTotal;
    ULONG  ulVpnPacketSendTotal;
    ULONG  ulVpnPacketErrorTotal;
    /* End: VISP Support multi-instance project */

    /* IPv6报文下发PPI统计 */
    ULONG  ulNPIp6OutputTotal;
    /* IPv6报文下发PPI失败统计 */
    ULONG ulNPIp6OutputFailure;

    /* Begin: 为支持PPPOE协议保活处理，添加下面字段 */
    /* 下发PPPOE PPI命令字总次数 */
    ULONG ulPppoeUpdateTotal;
    /* 下发PPPOE PPI命令字失败总次数 */
    ULONG ulPppoeUpdateFailure;
    /* End: PPPOE协议保活处理时，统计字段添加结束 */
    /* Map更新通知总次数 */
    ULONG ulMapUpdateTotal;
    /* Map更新通知失败次数 */
    ULONG ulMapUpdateFailure;
    /*Added by z00208058/w00207740, TRUNK LACP下移需求开发, 2012/5/2 */
    /* 下发TRUNK PPI命令字总次数*/
    ULONG ulTrunkUpdateTotal;
    /* 下发TRUNK PPI命令字失败总次数*/
    ULONG ulTrunkUpdateFailure;
    /*Added by w00207740, NSR TRUNK,添加PPI统计信息, 2013/6/6 */
    ULONG ulPolicyRtUpdateTotal;
    ULONG ulPolicyRtUpdateFailure;

   /*Added by apurba for VRF6*/
    ULONG ulVrf6UpdateTotal;
    ULONG ulVrf6UpdateFailure;
}TCPIP_PPI_COUNT_S;



/************************告警相关数据结构及宏定义begin****************************/
typedef enum TCPIP_WARING_Etag
{
    WARNING_IF_PROTOCOL_UPDOWN,   /* 0 接口上的协议状态变化 */
    WARNING_PPP_AUTH_FAILURE,     /* 1 PPP协议认证失败(不被对方接收) */
    WARNING_ETHARP_IP_CONFLICT,   /* 2 ETH链路上检测有地址与本机冲突 */
    WARNING_TCP_QLIMIT,           /* 3 TCP监听套接口上连接请求已达上限，新的连接请求被忽略 */
    WARNING_SOCKET_NUMBER_MAX,    /* 4 SOCKET数目已达到系统配置上限，无法创建新的SOCKET */
    WARNING_DHCP_FAILURE,         /* 5 DHCP Client得不到网络上Server的相应 */
    WARNING_HA_FAIL,              /* 6 HA平滑校验时发现协议栈存在冗余信息 */
    WARNING_BFD_IPCHANGE,         /* 7 BFD使用的地址被用户更改 */
    WARNING_BFD_TRUNKPORTCHANGE,  /* 8 BFD使用的出接口被加入或移除trunk成员端口 */
    WARNING_ERR_NETWORK_CONFIGURE,/* 9 可能是一个错误的组网方式,本机上两个接口形成的vlink路由引起报文收发不正确 */
    WARNING_PPP_IPHC_PARA_DIFF,   /* 10 PPP本端配置的参数和本端协商获得的参数不一致, 或两端协商获得的参数不一致 */
    WARNING_PPP_IPCONFLICT,       /* 11 PPP协商两端地址冲突 */
    WARNING_PPP_LOOPBACK,         /* 12 PPP链路环回导致协商不过告警*/
    WARNING_MP_ED_NOCONSISTENT,   /* 13 MP ED不一致导致绑定失败协商不过告警*/
    WARNING_PPP_REMOVE,           /* 14 PPP告警消除通报*/
    WARNING_3AH,                  /* 15 3ah对外告警ID */
    WARNING_1AG_ACROSS,           /* 16 1AG交叉连接告警*/
    WARNING_1AG_ERR,              /* 17 1AG产生CC_LOST、MEPID重复、远端接口状态、CCM Interval不匹配、MD Level不匹配告警*/
    WARNING_1AG_RDI,              /* 18 1AG产生RDI告警*/
    WARNING_PPP_LCP_AUTH_NEGOTIATE_FAILURE, /* 19 LCP认证协议协商失败告警 */
    WARNING_PPP_LCP_MP_NOBIND,      /* 20 LCP协商时探测到一端绑定到MP组下一端没有绑定到MP组 */
    WARNING_PPP_MP_SUBLINKLOWLIMIT, /* 21 设定MP下限阀值导致链路断链告警 */
    WARNING_PPP_NPINFO_NOCONSISTENT,/* 22 VISP下发给NP的信息与NP生效的信息不一致*/
    WARNING_RM_ROUTENUM_MAX,        /* 23 RM FIB表中路由数量达到系统配置告警上限值 */
    WARNING_MSTP_GUARD,             /* 24 MSTP保护类告警信息 */
    WARNING_PPI_DOWN_PPP_FAIL,      /* 25 NP下发失败  */
    WARNING_LACP_NEGOUT,            /* 26 TRUNK端口LACP首次协商不通过对外告警 */
    WARNING_PPP_NEG_NOT_PASS,       /* 27 用户指定时间内协商不过对外告警*/
    WARNING_MP_CFG_NOCONSISTENT,    /* 28 本端或对端子通道PFC/ACFC/MHF/SSNHF/MRU/MRRU/PREFIX不一致导致LCP down */
    WARNING_ARPGUARD_HAPPEN,        /* 29 ARP防攻击告警产生 */
    WARNING_ARPGUARD_RESTORE,       /* 30 ARP防攻击告警恢复 */
    WARNING_ARP_CONFLICT,           /* 31 静态ARP和动态ARP冲突 */
    WARNING_LACP_PARAM_WRONG,       /* 32 TRUNK成员端口参数不正确导致协商失败告警产生或消除 SGSN需求 BC3D02743 20100224 */
    WARNING_BFD_SESSION_CONFLICT,   /* 33 BFD会话创建冲突 *//*SGSN需求DTS2010090200956: BFD 多会话和应用共用问题*/
    WARNING_VLAN_CONSISTENCY,       /* 34 VLAN ID 不一致告警 */
    WARNING_ARPGUARD_ARPCONFLICT,   /* 35 ARP防攻击告警 */
    WARNING_Y1731_AIS,              /* 36   Y1731 AIS 告警*/
    WARNING_LLDP_REMOTE_TABLE_UPDATE, /*37 LLDP告警*/
    WARNING_ATTACK,                 /*38 Attack 门限告警, added for IP attack statistics. */

    WARNING_MAX                   /* 枚举值上限，无实意 */
}TCPIP_WARING_E;

/* SGSN需求 BC3D02743 20100224: TRUNK成员端口参数不正确导致协商失败告警产生或消除 */
typedef struct tagLACP_PARAM_WRONG
{
    ULONG ulPortIfIndex;
    CHAR  szPortIfName[IF_MAX_INTERFACE_NAME_LEN+1];
    ULONG ulBeginOrEnd;    /* 1 产生告警；0 消除告警 */
    ULONG ulParamType;     /* 0 双工模式不正确； 1 速率不一致 */
}LACP_PARAM_WRONG_S;

typedef struct tagIF_PROTOCOL_PARAM
{
    ULONG ulIfIndex;
    CHAR  szIfName[IF_MAX_INTERFACE_NAME_LEN+1];
    ULONG ulProtocolID;
    ULONG ulUpDown;     /* 见下面宏定义 */
}IF_PROTOCOL_PARAM_S;
#define IF_WARN_PROTOCOLISUP   1 /* 协议UP */
#define IF_WARN_PROTOCOLISDOWN 2 /* 协议DOWN */

#define LQM_CHANGE_BAD  3
#define LQM_CHANGE_GOOD 4

typedef struct tagPPP_AUTH_PARAM
{
    ULONG ulIfIndex;
    CHAR  szIfName[IF_MAX_INTERFACE_NAME_LEN+1];
    ULONG ulAuthType;   /* 见下面宏定义 */
}PPP_AUTH_PARAM_S;
#define PPP_WARN_PAPAUTH  1 /* PAP认证类型 */
#define PPP_WARN_CHAPAUTH 2 /* CHAP认证类型 */

/*用户指定时间内协商不过对外告警的数据结构*/
typedef struct tagPPP_NEG_NOT_PASS_WARNINGOUT
{
    ULONG ulIfIndex;                   /*接口索引*/
    ULONG ulLcpState;                  /*LCP状态*/
    ULONG ulIpcpState;                 /*IPCP状态*/
    ULONG ulIp6cpState;                /*IP6CP状态*/
    ULONG ulPppmuxState;               /*PPPMUX状态*/
    ULONG ulMpIfIndex;                 /*mp父接口索引*/
}PPP_NEG_NOT_PASS_WARNINGOUT_S;

typedef struct tagETH_IPCONFLICT_PARAM
{
    ULONG ulIPConflictType;
    ULONG ulIfIndex;
    CHAR  szIfName[IF_MAX_INTERFACE_NAME_LEN+1];
    ULONG ulIPAddr;     /* 网络序地址 */
    UCHAR szMacAddr[6]; /* 冲突者的physical地址,6字节 */
    CHAR  ucReserved[2];
    /* Added by fengjing209023, DTS2014022106314 地址冲突告警(消除)上报携带VRF索引 */
    ULONG ulVrfIndex;   /* VRF索引 */
}ETH_IPCONFLICT_PARAM_S;

/* 动静态ARP冲突告警输出结构 */
typedef struct tagETH_SARPCONFLICT_PARAM
{
    ULONG     ulIfIndex;        /* 接口索引 */
    ULONG     ulVrfID;          /* VRF 实例 */
    ULONG     ulIPAddr;         /* 网络序地址 */
    UCHAR     szMacAddr[6];     /* 冲突者的静态physical地址 */
    UCHAR     ucAlmSt;          /* 告警状态,1告警产生 0告警结束 */
    UCHAR     ucPadding;
}ETH_SARPCONFLICT_PARAM_S;

#define ETH_WARN_ETHIP_CONFLICT     1   /* 以太接口地址冲突类型 */
#define ETH_WARN_OMIP_CONFLICT      2   /* 特殊ARP代理的逻辑接口地址冲突类型，用于地址冲突告警时使用 */
#define ETH_WARN_ETHIP_CONFLICT_CLEAR_CONFIGURE     3   /*以太接口地址冲突消除告警（自己修改配置消除）*/
#define ETH_WARN_ETHIP_CONFLICT_CLEAR_DETECT        4   /*以太接口地址冲突消除告警（探测消除） */
#define ETH_WARN_OMIP_CONFLICT_CLEAR_CONFIGURE      5   /* ARP代理的逻辑接口地址冲突消除告警（自己修改配置消除） */
#define ETH_WARN_OMIP_CONFLICT_CLEAR_DETECT         6   /* ARP代理的逻辑接口地址冲突消除告警（探测消除） */

#define ETH_WARN_CLEAR_BY_CONFIG 0
#define ETH_WARN_CLEAR_BY_DETECT 1

typedef struct tagTCP_QLIMIT_PARAM
{
    ULONG ulSockFD;     /* 监听Socket的Fd */
    ULONG ulLPort;      /* 监听Socket的绑定端口号 */
    ULONG ulQLimit;     /* 监听Socket设置的listen数值 */
}TCP_QLIMIT_PARAM_S;

typedef struct tagDHCP_FAILURE_PARAM
{
    ULONG ulIfIndex;    /* DHCP的所在的接口索引 */
    CHAR  szIfName[IF_MAX_INTERFACE_NAME_LEN+1];
    ULONG ulFailType;   /* 见下面的宏定义 */
    ULONG ulIPAddr;     /* 地址, 主机序 */
    ULONG ulIPMask;     /* 子网掩码, 主机序 */
}DHCP_FAILURE_PARAM_S;
#define DHCP4C_WARN_NOSERVER 1 /* DHCP Client得不到网络上Server的响应 */
#define DHCP4C_WARN_RCVNAK   2 /* DHCP Client请求延长周期、请求重绑定时被NAK，解除地址 */
#define DHCP4C_WARN_LEASEOUT 3 /* DHCP Client租期满，解除地址 */
#define DHCP4C_WARN_IPCONFLICT     4 /* DHCP Client获取地址和网络内其它地址冲突 */
#define DHCP4C_WARN_BINDFAIL    5 /* DHCP Client获取地址绑定失败 */

typedef struct tagBFD_WARNING_PARAM
{
    /* Modified by q62011 for A82D13314,2007-04-04
       change description from 'BFD会话所在的接口索引'to'地址所在的接口索引'*/
    ULONG ulIfIndex;     /* 地址所在的接口索引;或者为trunk成员端口索引 */
    ULONG ulBfdSessionID;/* BFD会话ID */
    ULONG ulIPAddr[4];      /* 地址值，网络序 */
    ULONG ulIpVersion;
    ULONG ulWarnType;     /* 见下面的宏定义 */
}BFD_WARNING_PARAM_S;
#define BFD_WARN_DELETESRCADRR  1 /* BFD会话使用的源地址被删除; */
#define BFD_WARN_DSTADRRISLOCAL 2 /* BFD会话使用的目的地址变为了本地地址 */
#define BFD_WARN_ADDPORT        3 /* 接口增加到trunk中 */
#define BFD_WARN_REMOVEPORT     4 /* 接口从trunk中移除 */
/*SGSN需求DTS2010090200956: BFD 多会话和应用共用问题*/
#define BFD_WARN_STATICSESSIONEXIST  5 /* 已经存在静态Session，不能创建动态Session*/
#define BFD_WARN_DYNAMICSESSIONEXIST 6 /* 已经存在动态Session，不能创建静态Session */

/* HA告警结构*/
typedef struct tagHAWARM_S
{
    ULONG  ulflag ; /* 告警ID，参下面的宏定义 */
    ULONG  ulPara ; /* 告警参数 */
}HAWARM_S;
#define WARNING_HA_PACKET_REASS             0x1
#define WARNING_HA_OUT_OF_ORDER             0x2
#define WARNING_HA_DEL_IF_BY_CHECK          0x3
#define WARNING_HA_SMOOTH_CHK_SOCKET_FAIL   0x4
#define WARNING_HA_KEEPALIVE_TIMEOUT        0x5
#define WARNING_HA_OUT_OF_ORDER_DETECT      0x6
#define WARNING_HA_CKSUM_ERROR              0x7
#define WARNING_HA_SENDMSG_FAIL             0x8

typedef struct tagPPP_PARA_S
{
    ULONG ul_is_different; /* 0 下面三个参数完全一致  1 下面三个参数不完全一致 */
    ULONG ul_want_value;  /* 本端配置的值 */
    ULONG ul_got_value;   /* 本端协商获得的值 */
    ULONG ul_his_value;   /* 协商获得的对端的值 */
}PPP_PARA_S;

typedef struct tagPPP_IPHC_PARA_WARNING_S
{
    ULONG ul_flag;  /* 0 告警消除  1 告警 */
    ULONG ul_if_index;  /* 接口索引 */
    PPP_PARA_S st_neg_iphc;  /* 是否使能IPHC, 参数取值: 0 未使能  1 使能 */
    PPP_PARA_S st_rtp_compression;  /* 是否使能RTP压缩, 参数取值: 0 未使能  1 使能 */
    /* 报文压缩类型, 参数取值: 0 全部压缩  1 仅压缩非TCP报文  2 仅压缩TCP报文  3 都不压缩 */
    PPP_PARA_S st_compress_type;
    PPP_PARA_S st_tcp_space;  /* TCP流个数,  参数取值范围[0, 255] */
    PPP_PARA_S st_non_tcp_space;  /* 非TCP流个数,  参数取值范围[0, 65535] */
}PPP_IPHC_PARA_WARNING_S;


/*增加PPP协商地址冲突告警、ED描述符不一致告警、环回冲突告警及相应的告警消除,add by wuhailan,2008-04-11.*/

/*支持PPP协商地址冲突告警*/
typedef struct tagPPP_IPCONFLICT_PARAM
{
    ULONG ulIPConflictType;   /* PPP协商IP冲突的类型：见宏定义 */
    ULONG ulIfIndex;          /* 冲突接口的索引 */
    ULONG ulIPAddr;           /* 主机序地址 */
}PPP_IPCONFLICT_PARAM_S;
#define PPP_WARN_IPCONFLIT_PEERSAME     1   /* 协商两端地址冲突 */
#define PPP_WARN_IPCONFLIT_MODE         2   /* 本端给对端分配地址，但是对端有自己的地址 */
#define PPP_WARN_IPCONFLIT_LOCALSAME    3   /* 协商得来地址与本端其他IP冲突 */

/*支持PPP链路环回导致协商不过告警*/
typedef struct tagPPP_LOOPBACK_PARAM_WARNING
{
    ULONG ulLoopBackType;     /* 环回阶段类型*/
    ULONG ulIfIndex;          /* 冲突接口的索引 */
    ULONG ulgot_magic_value;  /* 本端协商到的魔术字 */
    ULONG ulhis_magic_value;  /* 对端协商到的魔术字 */
    ULONG ulpck_magic_value;  /* 收到报文的魔术字 */
}PPP_LOOPBACK_PARAM_WARNING_S;
#define PPP_WARN_LOOPBACK_NAK      1   /* 协商过程中发现环回 */
#define PPP_WARN_LOOPBACK_ECHO     2   /* ECHO报文探测到环回 */
#define PPP_WARN_IN_SERIES         3   /* ECHO报文探测到链路串连 */


#ifndef PPP_MP_DISCR_MAX_LENGTH
#define PPP_MP_DISCR_MAX_LENGTH    20
#endif

typedef struct tagMP_ED_PARA_S
{
    ULONG ulIfIndex;     /* 接口索引 */
    ULONG ulneg_discr;   /* 是否协商终端描述符 */
    ULONG uldiscr_len;   /* 终端描述符长度 */
    ULONG uldiscr_class; /* 终端描述符类型 */
    UCHAR szdiscr_addr[PPP_MP_DISCR_MAX_LENGTH]; /* 协商获得的对端的值 */
}MP_ED_PARA_S;

/*支持MP终端描述符不一致告警*/
typedef struct tagMP_ED_CONSISTENT_WARNING
{
    ULONG        uledConsistentType;     /* MP终端描述符不一致告警类型*/
    MP_ED_PARA_S stfather_ed_Info;       /* 父通道终端描述符信息 */
    MP_ED_PARA_S stson_ed_Info;          /* 子链路终端描述符信息 */
}MP_ED_CONSISTENT_WARNING_S;
#define PPP_WARN_ED_CONSISTENT_NEGD      1   /* 是否协商ED */
#define PPP_WARN_ED_CONSISTENT_DLENCLASS 2   /* ED长度或类型 */
#define PPP_WARN_ED_CONSISTENT_DADDR     3   /* ED值 */

typedef struct tagPPP_WARNING_REMOVE
{
    ULONG ulIfIndex;     /* 接口索引*/
    ULONG ulWarningType; /* 告警类型*/
}PPP_WARNING_REMOVE_S;
#define PPP_WARN_LOOPBACK        1   /*消除环回告警类型*/
#define PPP_WARN_IPCONFLICT      2   /*消除IP协商地址冲突告警类型*/
#define PPP_WARN_ED_NOCONSISTENT 3   /*消除MP终端描述符不一致告警类型*/
#define PPP_WARN_LCP_AUTH_NEGOTIATE_FAILURE  4   /*消除LCP认证协议协商失败类型*/
#define PPP_WARN_LCP_MP_NOBIND      5   /*消除LCP协商时探测到一端绑定到MP组下一端没有绑定到MP组类型*/
#define PPP_WARN_MP_SUBLINKLOWLIMIT 6   /*消除设定MP下限阀值导致链路断链类型*/

/* 消除本端或对端子通道PFC/ACFC/MHF/SSNHF/MRU/MRRU/PREFIX不一致导致LCP down */
#define PPP_WARN_MP_CFG_NOCONSISTENT       7

/* 3ah对外告警输出的数据结构 */
typedef struct tagOam3ahWarnParam
{
    ULONG ulIfIndex;            /* 接口索引                                             */
    ULONG ulEventType;          /* 告警事件类型                                         */
    ULONG ulLclRmt;             /* 告警方向：来自本端还是对端(对事件或故障告警有意义)   */
    ULONG ulFaultStartEnd;      /*故障开始或终止(对故障告警有意义)                      */
}OAM3AH_WARN_PARAM_S;

/* 3AH对外告警类型 */
typedef enum enOam3ahWarnType
{
    OAM3AH_WARN_ERR_SYMPRD = 1, /* 错误符号周期事件 */
    OAM3AH_WARN_ERR_FRAME,      /* 错帧事件         */
    OAM3AH_WARN_ERR_FRMPRD,     /* 错帧周期事件     */
    OAM3AH_WARN_ERR_FRMSECSUM,  /* 错帧秒事件       */

    OAM3AH_WARN_LINKFAULT,      /* 链路故障         */
    OAM3AH_WARN_DYINGGASP,      /* 致命故障         */
    OAM3AH_WARN_CRITICALEVT,    /* 紧急事件         */

    OAM3AH_WARN_SENDANY_START,  /* 进入SENDANY      */
    OAM3AH_WARN_SENDANY_END,    /* 退出SENDANY      */

    OAM3AH_WARN_LB_LCL_START,   /* 进入环回响应稳态 */
    OAM3AH_WARN_LB_LCL_END,     /* 退出环回响应稳态 */
    OAM3AH_WARN_LB_RMT_START,   /* 进入环回发起稳态 */
    OAM3AH_WARN_LB_RMT_END,     /* 退出环回发起稳态 */

    OAM3AH_WARN_NEGTIMEOUT,          /* 首次协商不通过对外告警 */
}OAM3AH_WARN_TYPE_E;


/*1AG对外告警输出交叉连接数据结构。*/
typedef struct tagOAM_1AG_CROSSCONPARA
{
    ULONG ulIfIndex; /*接口索引*/
    USHORT usVlanId; /*关联的VLAN ID*/
    UCHAR ucWarnState; /*告警动作,1-告警,0-恢复告警*/
    UCHAR ucres;
    UCHAR szLocalMdName[OAM_1AG_MAX_MDNAME_LEN + 1];/*本地MD名*/
    UCHAR szLocalMAName[OAM_1AG_MAX_MANAME_LEN + 1];/*本地MA名*/
    UCHAR szRemoteMdName[OAM_1AG_MAX_MDNAME_LEN + 1];/*远端MD名*/
    UCHAR szRemoteMAName[OAM_1AG_MAX_MANAME_LEN + 1];/*远端MA名*/
}OAM_1AG_CROSSCONPARA_S;

/*1AG对外告警输出MEPID重复、CC_LOST、远端接口状态变化
CCM Interval不匹配、MD Level不匹配数据结构。*/
typedef struct tagOAM_1AG_ERRPARA
{
    ULONG  ulIfIndex;/*告警接口索引*/
    USHORT usRMepID; /*告警的远端MEPID*/
    UCHAR ucWarnType;/*告警类型*/
    UCHAR ucWarnState; /*告警动作,1-告警,0-恢复告警*/
    UCHAR szLocalMdName[OAM_1AG_MAX_MDNAME_LEN + 1];/*本地MD名*/
    UCHAR szLocalMAName[OAM_1AG_MAX_MANAME_LEN + 1];/*本地MA名*/
}OAM_1AG_ERRPARA_S;

/*1AG对外告警输出RDI告警。*/
typedef struct tagOAM_1AG_RDIPARA
{
    UCHAR ucWarnState; /*告警动作,1-告警,0-恢复告警*/
    UCHAR ucRes[3];
    UCHAR szLocalMdName[OAM_1AG_MAX_MDNAME_LEN + 1];/*本地MD名*/
    UCHAR szLocalMAName[OAM_1AG_MAX_MANAME_LEN + 1];/*本地MA名*/
}OAM_1AG_RDIPARA_S;

/* Add for V2R3C06, by z00171897/p00193127, at 2011-10-06. 修改原因: 扩展告警类型 */
typedef enum enumTcpipOAMWarn1AGType
{
    OAM_1AG_MEPIDREPEAT = 0, /*mep id重复*/
    OAM_1AG_CCLOST,       /*rmep CCM报文丢失*/
    OAM_1AG_IFSTATE,     /*rmep 接口状态*/
    OAM_1AG_CCM_INTERVAL,  /*rmep CCM周期 非期望传输周期 */
    OAM_1AG_MD_LEVEL,     /*MD Level 非期望MEG Level */
    OAM_Y1731_MEGID,    /* 非期望MEGID */
    OAM_Y1731_MEPID,    /* 非期望MEPID */

    OAM_WARN_TYPE_MAX
}TCPIP_OAM_1AG_WARN_TYPE_E;

typedef struct tagPPP_AUTH_NEGOTIATE_PARAM
{
    ULONG ulIfIndex;
    ULONG ulWantNegCHAP;    /* 本端配置是否协商CHAP(1-是,0-否) */
    ULONG ulWantNegPAP;     /* 本端配置是否协商PAP(1-是,0-否) */
    ULONG ulGotNegCHAP;     /* 协商结果是否进行CHAP认证(1-是,0-否) */
    ULONG ulGotNegPAP;      /* 协商结果是否进行PAP认证(1-是,0-否) */
}PPP_AUTH_NEGOTIATE_PARAM_S;

typedef struct tagPPP_MP_NOBIND_PARAM
{
    ULONG ulIfIndex;
    ULONG ulMpNobindType;   /*见下面宏定义*/
}PPP_MP_NOBIND_PARAM_S;
#define PPP_WARN_NOBIND_LOCAL     1  /* 本端未加入MP组 */
#define PPP_WARN_NOBIND_REMOTE    2  /* 对端未加入MP组 */

typedef struct tagPPP_MP_SUBLINKLOWLIMIT_PARAM
{
    ULONG ulIfIndex;
    ULONG ulMpBindNum;   /*当前父通道绑定的子链路数(已生效)*/
    ULONG ulUpSublinkLowLimit; /*下限阀值*/
}PPP_MP_SUBLINKLOWLIMIT_PARAM_S;

/*核查不一致时上报告警的参数*/
typedef struct tagPPP_NPINFO_PARAM
{
    ULONG ulIfIndex;    /*接口索引*/
    PPI_PPP_INFO_S stPPIInfo;  /*VISP面信息*/
    PPI_PPP_INFO_S stNPInfo;  /*NP面信息*/
}PPP_NPINFO_PARAM_S;

/*1AG对外告警输出AIS告警。*/
typedef struct tagOAM_1AG_AISPARA
{
    UCHAR ucWarnState; /*告警动作,1-告警,0-恢复告警*/
    UCHAR ucMdLevel;    /* MD 等级 */
    UCHAR ucRes[2];
    UCHAR szMdName[OAM_1AG_MAX_MDNAME_LEN + 1];/*本地MD名*/
    UCHAR szMAName[OAM_1AG_MAX_MANAME_LEN + 1];/*本地MA名*/
}OAM_1AG_AISPARA_S;


/* PPP模块NP下发失败标志位 */
#define    PPI_LCPGOTOPTION     0x0001    /* LCP本端协商选项 */
#define    PPI_LCPHISOPTION     0x0002    /* LCP对端协商选项 */
#define    PPI_IPCPGOTOPTION    0x0004    /* IPCP本端协商选项 */
#define    PPI_IPCPHISOPTION    0x0008    /* IPCP对端协商选项 */
#define    PPI_MUXCPGOTOPTION   0x0010    /* MUXCP本端协商选项 */
#define    PPI_MUXCPHISOPTION   0x0020    /* MUXCP对端协商选项 */
#define    PPI_ADD_MLPPP        0x0040    /* 接口加入到ML PPP */
#define    PPI_DEL_MLPPP        0x0080    /* 接口从一个ML PPP中删除 */
#define    PPI_CONFIGINFO       0x0100    /* 本端的配置信息*/
#define    PPI_IP6CPGOTOPTION    0x0200    /* IP6CP本端协商选项 */
#define    PPI_IP6CPHISOPTION    0x0400    /* IP6CP对端协商选项 */

#define     PPI_SET_OSICPGOTOPTION      0x0800      /*通知NP OSICP本端协商选项*/
#define     PPI_SET_OSICPHISOPTION      0x1000      /*通知NP OSICP对端协商选项*/
#define     PPI_GET_LCPGOTOPTION        0x2000      /* 获取本端LCP协商选项 */
#define     PPI_GET_LCPHISOPTION        0x4000      /* 获取对端LCP协商选项 */
#define     PPI_GET_IPCPGOTOPTION       0x8000      /* 获取IPCP本端协商选项 */
#define     PPI_GET_IPCPHISOPTION       0x10000     /* 获取IPCP对端协商选项 */
#define     PPI_GET_OSICPGOTOPTION      0x20000     /* 获取OSICP本端协商选项 */
#define     PPI_GET_OSICPHISOPTION      0x40000     /* 获取OSICP对端协商选项 */


/* PPP模块NP下发失败上报告警的参数 */
typedef struct tagPPI_DOWN_PPP_FAIL
{
    ULONG ulIfIndex;    /* PPP接口索引 */
    ULONG ulNpFailed;   /* 下发失败的类型，包括LCP,IPCP,MCP,MP,CONFIG，用位标识 */
}PPI_DOWN_PPP_FAIL;


/*RM路由数量告警*/
typedef struct tagRM_ROUTENUMMAX_PARAM
{
    ULONG ulWarnType;  /*告警类型，1-告警产生或者2-告警消除*/
    ULONG ulInstace;   /*实例号*/
    ULONG ulCurRouteNum; /*当前FIB表路由数量*/
}RM_ROUTENUMMAX_PARAM_S;
#define RM_WARN_RTNUM_EXCEED           1   /* FIB表路由数量超标 */
#define RM_WARN_RTNUM_CLEAR_EXCEED     2   /*FIB表路由数量超标消除告警 */

#define CONTROL_PACKET_OUTPUT 0      /* 表示报文的输出方向 */
#define CONTROL_PACKET_INPUT  1      /* 表示报文的输入方向 */


/* TRUNK端口LACP首次协商不通过对外告警结构
  告警ID: WARNING_LACP_NEGOUT */
typedef struct tagTrunkLacpNotPassWarning
{
    ULONG ulPortIfIndex;    /* 端口索引 */
    ULONG ulTkId;           /* 端口所在TrunkId */
}TRUNKPORT_LACPNOTPASS_WARNING_S;



/* 本端或对端子通道PFC/ACFC/MHF/SSNHF/MRU/MRRU/PREFIX不一致导致LCP down */
typedef struct tagMP_SONCFG_NOCONSISTENT_WARNING
{
    ULONG ulFatherIfIndex;
    ULONG ulSonIfIndex;
    PPI_PPP_LCP_OPTION_S stFatherGotOption;
    PPI_PPP_LCP_OPTION_S stSonGotOption;
    PPI_PPP_LCP_OPTION_S stFatherHisOption;
    PPI_PPP_LCP_OPTION_S stSonHisOption;
}MP_SONCFG_NOCONSISTENT_WARNING_S;

#define MEM_ERR_RECORDNUM   10
/* 内存操作失败类型 */
enum enMemErrType
{
    MEM_ERR_ALLOCMID = 1,  /* 1 分配内存时,MID错误 */
    MEM_ERR_FREEMID,       /* 2 释放内存时,MID错误 */
    MEM_ERR_FREELEN,       /* 3 释放内存时,长度错误 */

    MEM_ERR_MAX,
};

/*记录内存发生错误信息数据结构*/
typedef struct tagMemErrRecord
{
    ULONG ulErrType;   /* 错误信息类型, 取值为enMemErrType*/
    ULONG ulPara[4];   /* 错误信息相关参数 */
}MEM_ERR_RECORD_S;

/* 统计内存错误信息数据结构 */
typedef struct tagMemErrStat
{
    ULONG ulAllocMidErrNum;   /* 申请内存时MID错误次数 */
    ULONG ulFreeMidErrNum;    /* 释放内存时MID错误次数 */
    ULONG ulFreeLenErrNum;    /* 释放内存时LEN错误次数 */
    MEM_ERR_RECORD_S stMemErrRecord[MEM_ERR_RECORDNUM];     /* 记录最近MEM_ERR_RECORDNUM出错信息 */
    ULONG ulCurRecordTag;  /*当前应该记录统计信息下标,即本次记录在stMemErrRecord成员数组下标值 */
}MEMERRSTAT_S;


/* ARP防欺骗上报告警数据结构 */
typedef struct tagARPGuardWarning
{
    ULONG ulIPAddr;                   /* 地址 */
    UCHAR ucCurMac[MACADDRLEN];       /* 当前可信任的MAC，在告警恢复时使用，告警时填写为0 */
    UCHAR ucPad[2];                   /* 保留字段 */
}ARP_GUARD_WARNING_S;

typedef struct tagPPI_PPPOE_INFO
{
    ULONG ulSessionId;              /* PPPOE会话ID */
    ULONG ulEthIfIndex;             /* Ethernet接口的接口索引 */
    ULONG ulDialerIfIndex;          /* Dialer接口的接口索引 */
    ULONG ulVaIfIndex;              /* 对应的VA接口的接口索引 */
    ULONG ulSessionState;           /* PPPOE会话的状态 */
    UCHAR szOurMacAddr[MACADDRLEN]; /* 本端对应Ethernet接口的physical地址 */
    UCHAR szHisMacAddr[MACADDRLEN]; /* 对端的physical地址 */
    ULONG ulReserved;               /* 保留字段，用于以后扩展时使用 */
}PPI_PPPOE_INFO_S;


/* Add by zhaoyue00171897, at 2011-08-17. 修改原因: 支持获取动态FDB表项 */
/* 获取动态FDB表项PPI结构体 */
typedef struct tagPPI_L2IF_DYNAMIC_FDB_INFO
{
    UCHAR  aucMacAddr[MACADDRLEN];       /* physical地址             */
    USHORT usVlanId;                     /* physical地址所属VLAN ID  */
    ULONG  ulIfIndex;                    /* 接口索引            */
    ULONG  ulAgingTime;                  /* 老化时间 */
}PPI_L2IF_DYNAMIC_FDB_INFO_S;

typedef ULONG (*TCPIP_REBOOT_MODE_HOOK_FUNC)(ULONG ulModID);

/************************告警相关数据结构及宏定义end****************************/



/*********************************函数原型定义********************************/


typedef struct tagTCPIP_LOG_HOOK_FUNC
{
    VOID (*pfTCPIP_FixlenLogOutput)(ULONG ulLogCode, ULONG ulLogLevel,
                                    ULONG ulLogType, VOID* pcFormat,
                                    ULONG lPara1, ULONG lPara2,
                                    ULONG lPara3, ULONG lPara4);
    VOID (*pfTCPIP_VarlenLogOutput)(ULONG ulLogCode, ULONG ulLogLevel,
                                    ULONG ulLogType, VOID* pcFormat, VOID* pData);
}TCPIP_LOG_HOOK_FUNC;

typedef VOID (*gpfTCPIPDebugOutput)(CHAR *pDebugInfo);
typedef VOID (*gpfTCPIPWarningOutput)(ULONG ulWarningID, VOID* pWarnParam);
typedef VOID (*gpfTCPIPInfoOutput)(CHAR *pInfo);
typedef VOID (*gpfVOSAssertX)(LONG lExpression, CHAR *pcFileName, ULONG ulLine);
typedef ULONG (*gpfTCPIPUserStop)(VOID);
typedef ULONG (*gpfTCPIPTrrtUserStopEx )(ULONG ulExecID);
typedef ULONG (*gpfTCPIPPingUserStopEx )(ULONG ulExecID);
typedef ULONG (*gpfGetSockMaxNum)(VOID);
/*Added by yanlei00216869, 使以.so方式提供给bluestar的visp，不依赖产品代码, 2014/11/26   问题单号:DTS2014112500391 */
typedef ULONG (*gpfRegAllAppInfo)(VOID);
/* End of Added by yanlei00216869, 2014/11/26   问题单号:DTS2014112500391 */
typedef ULONG (*CreateMutex_HOOK_FUNC)(CHAR *pMutexName, ULONG *pulMutexID);
typedef ULONG (*CreateSm_HOOK_FUNC)(CHAR *pCountName, ULONG ulSmInit, ULONG *pulCountID);
typedef ULONG (*SmP_HOOK_FUNC)(ULONG ulMutexID);
typedef ULONG (*SmV_HOOK_FUNC)(ULONG ulMutexID);
typedef ULONG (*DeleteMutex_HOOK_FUNC)(ULONG ulMutexID);

typedef ULONG (*NPDOWNLOAD_FAILED_PROCESS)(ULONG ulMid, ULONG ulNpErrcode, ULONG ulIfIndex, ULONG ulCmdOrType, VOID *pArg);
typedef ULONG (*GetLinkControlPacket_HOOK_FUNC)(ULONG ulIfIndex, ULONG ulSndOrRcv, ULONG ulProtocolType,
                                                ULONG ulSubProtocolType,  MBUF_S *pstBuf);

typedef VOID (*GoNext_HOOK_FUNC)(VOID);

typedef ULONG (*gpfTCPIP_GetTunnelMtu_HOOK_FUNC)(ULONG *pulTunnelMtu, ULONG ulTunnelInfo);

/*******************************************************************************
*    Func Name: TCPIP_Malloc
*  Description: VISP内存申请函数,要求COMMON/MBUF模块不允许调用.另外涉及到VOS_Mem_IncRef
*               /VOS_Mem_GetRef等存在访问块内存首地址的模块也不允许通过该接口来进行内存申请
*               由于CBB模块也使用了此类处理,所以对VISP CBB模块依赖于该内存申请和释放函数
*        Input: ULONG ulInfo:模块ID,必需传入VISP支持的模块ID(见tcpip_id.h文件)
*               ULONG ulSize:申请的内存大小
*       Output: 无
*       Return: 申请到的内存首地址
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   wuhailan                Create
*
*******************************************************************************/
extern VOID *TCPIP_Malloc(ULONG ulInfo, ULONG ulSize);
/*******************************************************************************
*    Func Name: TCPIP_Free
*  Description: VISP内存释放函数,与TCPIP_Malloc配套使用.要求MBUF模块不允许调用.
*               另外涉及到VOS_Mem_IncRef/VOS_Mem_GetRef等存在访问块内存首地址的模块也不允许通过该接口来进行内存释放
*               由于CBB模块也使用了此类处理,所以对VISP CBB模块依赖于该内存申请和释放函数
*        Input: VOID* pBuf:要释放的内存首地址
*       Output: 无
*       Return: 成功/失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_Free(VOID* pBuf);

/*******************************************************************************
*    Func Name: TCPIP_SetMemPid
*  Description: 设置内存申请使用的DOPRA PID值,VISP默认值为0x1234
*        Input: ULONG ulPid:内存申请使用的DOPRA PID值
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-16   wuhailan(06310)         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetMemPid(USHORT usPid);
typedef ULONG (*TCPIP_LINK_HOOK_FUNC)(struct tagMBuf *pstMBuf);

typedef ULONG (*HA_GETBOARDTYPE_FUNC)(VOID);
typedef VOID* (*HA_MALLOC_FUNC)(ULONG ulModID, ULONG ulLength);
typedef ULONG (*HA_FREE_FUNC)(VOID *pBuf);
typedef ULONG (*HA_GETPHYINITBYTYPE_FUNC)(ULONG ulType, UCHAR * szIfName, ULONG *pfPhyInitial);
typedef ULONG (*HA_GETIFPHYSTATE_FUNC)(ULONG ulIfIndex);
typedef ULONG (*HA_SENDMSG_FUNC)(UCHAR *pMsgBuf, ULONG ulMsgLen);
typedef ULONG (*HA_SLAVEISREADY_FUNC)(VOID);
typedef VOID  (*HA_BADVERNOTIFY_FUNC)(ULONG ulCurrentSysVer, ULONG ulVerInBakMsg);

/* 获取调用者任务ID的钩子函数 */
typedef ULONG (*SELFTASKID_HOOK)(VOID);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncLogOutputHook
*  Description: 注册日志输出处理函数
*        Input: TCPIP_LOG_HOOK_FUNC  * pfHookFunc: 函数指针集合
*       Output: 
*       Return: 成功:VOS_OK
*               失败:VOS_ERR
*      Caution: 本回调函数不能注销，建议最先调用
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncLogOutputHook(TCPIP_LOG_HOOK_FUNC *pstHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncDebugOutputHook
*  Description: 注册调试信息输出处理函数
*        Input: gpfTCPIPDebugOutput pfHookFunc:函数指针
*       Output:
*       Return: 成功:VOS_OK
*               失败:VOS_ERR
*      Caution: 本回调函数不能注销
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncDebugOutputHook(gpfTCPIPDebugOutput pstHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncWarningOutputHook
*  Description: 注册告警处理函数
*        Input: gpfTCPIPWarningOutput pfHookFunc:函数指针
*       Output:
*       Return: 成功:VOS_OK
*               失败:VOS_ERR
*      Caution: 本回调函数不能注销
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncWarningOutputHook(gpfTCPIPWarningOutput pstHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncInfoOutputHook
*  Description: 注册信息输出处理函数
*        Input: gpfTCPIPInfoOutput pfHookFunc:函数指针
*       Output:
*       Return: 成功:VOS_OK
*               失败:VOS_ERR
*      Caution: 本回调函数不能注销
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncInfoOutputHook(gpfTCPIPInfoOutput pstHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncVOSAssertXHook
*  Description: 注册断言适配处理函数
*        Input: gpfVOSAssertX pfHookFunc:函数指针
*       Output:
*       Return: 成功:VOS_OK
*               失败:VOS_ERR
*      Caution: 本回调函数不能注销
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncVOSAssertXHook(gpfVOSAssertX pstHookFunc);

typedef VOID (*TCPIP_CC_OUTPUT_HOOK_FUNC)(ULONG ulCCType, ULONG ulExecID, ULONG ulInfoID, CHAR *pszCCResult);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncCCOutputHook
* Date Created: 2009-3-26
*       Author: zhangchunyu(62474)
*  Description: 用户注册数据连通性输出报告函数
*        Input: TCPIP_CC_OUTPUT_HOOK_FUNC pfHookFun:
*       Output:
*       Return: DCC_SUCCESS:成功  DCC_FAILED:注册指针为空
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-3-26    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncCCOutputHook(TCPIP_CC_OUTPUT_HOOK_FUNC pfHookFun);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncUserStopHook
*  Description: 注册用户停止命令函数
*        Input: gpfTCPIPUserStop pfHookFunc: 函数指针
*       Output:
*       Return: 成功:VOS_OK
*               失败:VOS_ERR
*      Caution: 本回调函数不能注销
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncUserStopHook(gpfTCPIPUserStop pstHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncCreateMutexHook
*  Description: 注册信号量申请函数
*        Input: CreateMutex_HOOK_FUNC pfHookFunc:函数指针
*       Output:
*       Return: 成功:VOS_OK
*               失败:VOS_ERR
*      Caution: 本回调函数不能注销
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncCreateMutexHook(CreateMutex_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncCreateSmHook
*  Description: 注册同步信号量申请钩子函数
*        Input: CreateSm_HOOK_FUNC pfHookFunc:函数指针
*       Output:
*       Return: 成功:VOS_OK
*               失败:VOS_ERR
*      Caution: 本回调函数不能注销
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-09-18   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncCreateSmHook(CreateSm_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncSmPHook
*  Description: 注册信号量获取函数
*        Input: SmP_HOOK_FUNC pfHookFunc:函数指针
*       Output:
*       Return: 成功:VOS_OK
*               失败:VOS_ERR
*      Caution: 本回调函数不能注销
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncSmPHook(SmP_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncSmVHook
*  Description: 注册信号量释放函数
*        Input: SmV_HOOK_FUNC pfHookFunc:函数指针
*       Output:
*       Return: 成功:VOS_OK
*               失败:VOS_ERR
*      Caution: 本回调函数不能注销
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncSmVHook(SmV_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncDeleteMutexHook
*  Description: 注册信号量删除函数
*        Input: DeleteMutex_HOOK_FUNC pfHookFunc:函数指针
*       Output:
*       Return: 成功:VOS_OK
*               失败:VOS_ERR
*      Caution: 本回调函数不能注销
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncDeleteMutexHook(DeleteMutex_HOOK_FUNC pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetBoardTypeHook
*  Description: 注册获取单板主备类型函数
*        Input: HA_GETBOARDTYPE_FUNC pfFunc: 函数指针
*       Output:
*       Return: VOS_OK      成功
*               VOS_ERR     失败
*      Caution: 本回调函数必须注册，且不能注销
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncGetBoardTypeHook(HA_GETBOARDTYPE_FUNC pfFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncHAMallocHook
*  Description: 注册HA备份内存申请函数
*        Input: HA_MALLOC_FUNC  pfFunc: 函数指针
*       Output:
*       Return: VOS_OK      成功
*               VOS_ERR     失败
*      Caution: 本回调函数必须注册，且不能注销
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncHAMallocHook(HA_MALLOC_FUNC  pfFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncHAFreeHook
*  Description: 注册HA备份内存释放函数
*        Input: HA_FREE_FUNC pfFunc: 函数指针
*       Output:
*       Return: VOS_OK      成功
*               VOS_ERR     失败
*      Caution: 本回调函数必须注册，且不能注销
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncHAFreeHook(HA_FREE_FUNC pfFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetPhyInitByTypeHook
*  Description: 注册获取接口底层初始化函数指针的函数
*        Input: HA_GETPHYINITBYTYPE_FUNC pfFunc: 函数指针
*       Output:
*       Return: VOS_OK      成功
*               VOS_ERR     失败
*      Caution: 本回调函数必须注册，且不能注销
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncGetPhyInitByTypeHook(HA_GETPHYINITBYTYPE_FUNC pfFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetIfPhyStateHook
*  Description: 注册获取接口底层状态函数
*        Input: HA_GETIFPHYSTATE_FUNC pfFunc: 函数指针
*       Output:
*       Return: VOS_OK      成功
*               VOS_ERR     失败
*      Caution: 本回调函数必须注册，且不能注销
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncGetIfPhyStateHook(HA_GETIFPHYSTATE_FUNC pfFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncHASendMsgHook
*  Description: 注册备份消息发送函数
*        Input: HA_SENDMSG_FUNC pfFunc: 函数指针
*       Output:
*       Return: VOS_OK      成功
*               VOS_ERR     失败
*      Caution: 本回调函数必须注册，且不能注销
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncHASendMsgHook(HA_SENDMSG_FUNC pfFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncHASlaveIsReadyHook
*  Description: 注册查询背板是否就绪的函数
*        Input: HA_SLAVEISREADY_FUNC pfFunc: 函数指针
*       Output:
*       Return: VOS_OK      成功
*               VOS_ERR     失败
*      Caution: 本回调函数必须注册，且不能注销
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncHASlaveIsReadyHook(HA_SLAVEISREADY_FUNC pfFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncHABadVerNotifyHook
*  Description: 注册HA版本号校验失败的通知函数
*        Input: HA_BADVERNOTIFY_FUNC pfFunc: HA版本号校验失败的通知函数
*       Output: 
*       Return: VOS_OK 成功
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-15  wujie(61195)      Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncHABadVerNotifyHook(HA_BADVERNOTIFY_FUNC pfFunc);
/*******************************************************************************
*    Func Name: TCPIP_HA_RegisterCallBack
*  Description: HA回调通知函数注册接口
*        Input:
*               pfBatchCallBack  : 回调函数指针
*       Output: 无
*       Return: VOS_OK  成功
*               VOS_ERR 失败
*      Caution:
*------------------------------------------------------------------------------*
*  Modification History
*   DATE        NAME            DESCRIPTION
*------------------------------------------------------------------------------*
*   2006-12-04  xiehuaguo       create
*
*******************************************************************************/
extern ULONG TCPIP_HA_RegisterCallBack (TCPIP_HA_CALLBACK_S  * pfBatchCallBack);

/*******************************************************************************
*    Func Name: TCPIP_HA_NotifySwitch
*  Description: VISP HA手动倒换处理函数(主板运行)
*        Input: VOID
*       Output: 无
*       Return: VOS_OK  成功
*               VOS_ERR 失败
*               TCPIP_HA_BATCH_IS_NOT_OVER 批量备份没有完成
*      Caution:
*------------------------------------------------------------------------------*
*  Modification History
*   DATE        NAME            DESCRIPTION
*------------------------------------------------------------------------------*
*   2006-12-04  xiehuaguo       create
*   2007-08-01  l61496          增加返回错误码
*******************************************************************************/
extern ULONG TCPIP_HA_NotifySwitch(VOID);
/*******************************************************************************
*    Func Name: TCPIP_HA_SlavePlugOut
*  Description: 备板拔出处理接口(主板运行)
*        Input: VOID
*       Output: 无
*       Return: VOS_OK  成功
*               VOS_ERR 失败
*      Caution:
*------------------------------------------------------------------------------*
*  Modification History
*   DATE        NAME            DESCRIPTION
*------------------------------------------------------------------------------*
*   2006-12-04  xiehuaguo       create
*   2007-04-04  xiehuaguo       modify by defect A82D13585
*
*******************************************************************************/
extern ULONG TCPIP_HA_SlavePlugOut(VOID);
/*******************************************************************************
*    Func Name: TCPIP_HA_VerifyInterface
*  Description: IFNET外部平滑处理函数
*        Input: 接口索引
*       Output: 无
*       Return: VOS_OK:  成功
*               VOS_ERR:  失败
*               2:  存在
*               3:  不存在
*               #define  IF_EXIST   2;
*               #define  IF_INEXIST 3;
*
*      Caution: 1.VISP内部平滑处理完成后，产品可以用自身保存的接口信息与
*                 VISP进行校验，以防止资料吊死。
*               2.产品在与VISP进行接口校验时，要么与VISP验校所有可见接口的信息,
*                 要么不进行接口校验，因为产品在传入0xFFFFFFFF时，VISP内部
*                 删除所有未被校验的接口
*               3.只检验对用户可见的接口，其它接口如:VA、Inloopback、NULL都不
*                 支持外部检验的
*------------------------------------------------------------------------------*
*  Modification History
*   DATE        NAME            DESCRIPTION
*   2007-03-13  x36530          MP-Group接口与绑定到其它的子接口在ifnet链表中并不是按顺序存在，在调用
*                               TCPIP_HA_VerifyInterface数据删除mp-group接口时，可能其下还存在子接口，
*                               因为此时删除交通道是不成功的
*------------------------------------------------------------------------------*
*   2006-12-09  xiehuaguo       create
*   2008-08-13  f54882          for BC3D00219, 同步V1R6C02问题单BC3D00169
*   2008-08-13  f54882          for BC3D00221, 同步V1R6C02问题单BC3D00185
*
*******************************************************************************/
extern ULONG TCPIP_HA_VerifyInterface(ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_HA_BatchBackup
*  Description: VISP HA批量备份处理总入口(主板运行)
*        Input: VOID
*       Output: 无
*       Return: VOS_OK  成功
*               VOS_ERR 失败
*      Caution:
*------------------------------------------------------------------------------*
* Modification History
*  DATE        NAME            DESCRIPTION
*------------------------------------------------------------------------------*
*  2006-12-04  xiehuaguo       create
*  2007-07-30  jiangtao(51916) modify
*
*******************************************************************************/
extern ULONG TCPIP_HA_BatchBackup(VOID);
/*******************************************************************************
*    Func Name: TCPIP_HA_Smooth
*  Description: VISP HA平滑处理函数(备板升为主板时运行)
*        Input: VOID
*       Output: 无
*       Return: VOS_OK  成功
*               VOS_ERR 失败
*      Caution:
*------------------------------------------------------------------------------*
*  Modification History
*   DATE        NAME            DESCRIPTION
*------------------------------------------------------------------------------*
*   2006-12-04  xiehuaguo       create
*
*******************************************************************************/
extern ULONG TCPIP_HA_Smooth(VOID);
/*******************************************************************************
*    Func Name: TCPIP_HA_VerifySocket
*  Description: After slave becomes master, product can call this function to verify
*               whether the Socket Fds that it saves are same as that is saved by VISP.
*        Input: LONG lSocketID: Socket Fd to be verified
*       Output: None
*       Return: VOS_OK(0): Success
*               VOS_ERR(1): Fail, invalid argument
*               2: Socket fd doesn't exist
*               3: VISP is not initialized or global socket is not enabled
*      Caution: None
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-7   l48923(48923)    Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_HA_VerifySocket(LONG lSocketID);
/*******************************************************************************
*    Func Name: TCPIP_HA_Input
*  Description: VISP HA备份消息输入处理函数(备板运行)
*        Input: UCHAR * pucBuf: 备份消息包
*               ULONG ulMsgLen: 消息包长度
*       Output: 无
*       Return: VOS_OK  成功
*               VOS_ERR 失败
*               TCPIP_HA_IS_SMOOTHING HA没有初始化或正在平滑处理
*               TCPIP_HA_WRITE_QUEUE_FAIL 写HA消息队列失败
*      Caution:
*------------------------------------------------------------------------------*
*  Modification History
*   DATE        NAME            DESCRIPTION
*------------------------------------------------------------------------------*
*   2006-12-04  xiehuaguo       create
*   2007-08-01  l61496          增加返回错误码
*******************************************************************************/
extern ULONG TCPIP_HA_Input(UCHAR * pucBuf, ULONG ulMsgLen);
/*******************************************************************************
*    Func Name: TCPIP_HA_BadVerNotify
*  Description: 对外通知HA备份消息的版本号错误，可供使用VISP HA机制的外部模块(例如IPOA HA)调用
*        Input: ULONG ulCurrentHAVer:  模块当前的HA版本号
*               ULONG ulBadVerInBakMsg: 收到的备份消息中携带的HA版本号
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-17  wujie(61195)      Creat the first version.
*
*******************************************************************************/
extern VOID  TCPIP_HA_BadVerNotify(ULONG ulCurrentSysVer, ULONG ulVerInBakMsg);

/*************************************************************************
*    Func Name: TCPIP_HA_GetStat
*  Description: VISP HA统计信息获取接口
*        Input: 无
*       Output: HAStat_S *pstStat HA统计信息
*       return: VOS_OK  成功
*               VOS_ERR 失败
*         Caution:
*------------------------------------------------------------------------*
*  Modification History
*   DATE        NAME            DESCRIPTION
*------------------------------------------------------------------------*
*   2006-12-06  zhangchunyu(62474)     Create
*
*************************************************************************/
extern ULONG TCPIP_HA_GetStat(HASTAT_S *pstStat);
/*************************************************************************
*    Func Name: TCPIP_HA_ResetStat
*  Description: VISP HA统计信息清除接口
*        Input: VOID
*       Output: 无
*       return:
*      Caution:
*------------------------------------------------------------------------*
*  Modification History
*   DATE        NAME            DESCRIPTION
*------------------------------------------------------------------------*
*   2006-12-06  zhangchunyu(62474)     Create
*
*************************************************************************/
extern VOID  TCPIP_HA_ResetStat(VOID);
/*************************************************************************
*    Func Name: TCPIP_HA_SetAllDbg
*  Description: 设置HA全部调试开关
*        Input: ULONG ulDbg 开关标志,0 关闭 1 打开
*       Output: 无
*       Return: VOS_OK  成功
*               VOS_ERR 失败
*               others  其他错误码
*       Caution:
*------------------------------------------------------------------------*
*  Modification History
*   DATE        NAME            DESCRIPTION
*------------------------------------------------------------------------*
*   2006-12-06  zhangchunyu(62474)     Create
*   2007-04-16  zhangchunyu(62474)     Modify for A82D13954.
*   2007-08-01  l61496                 增加返回错误码
*************************************************************************/
extern ULONG TCPIP_HA_SetAllDbg(ULONG ulDbg);
/*************************************************************************
*    Func Name: TCPIP_HA_GetDbg
*  Description: 获取HA全部调试开关
*        Input: 无
*       Output: HADBG_S  *pstDbg 各个模块调试开关
*       Return: VOS_OK  成功
*               VOS_ERR 失败
*      Caution:
*------------------------------------------------------------------------*
*  Modification History
*   DATE        NAME            DESCRIPTION
*------------------------------------------------------------------------*
*   2006-12-06  zhangchunyu(62474)     Create
*   2007-04-16  zhangchunyu(62474)     Modify for A82D13954.
*   2007-08-01   l61496                增加返回错误码
*************************************************************************/
extern ULONG TCPIP_HA_GetDbg(HADBG_S *pstDbg);

/*******************************************************************************
*    Func Name: TCPIP_HA_RegisterModule
*  Description: register Ha back_up module
*        Input: ULONG ulLayer: registe layer number(0-2)
*               ULONG ulModId: module id
*               ULONG ulPriority: the calling of ha register module is sequence
*               UCHAR *pucModuleName: module name
*               TCPIP_HA_MODULE_CALLBACK_S pstModCallback: register
*       Output: ULONG *pulModId: return to the register to identify a ha module
*       Return:
*              HA_REGISTER_TOO_MUCH_ERR   2
*              HA_NAME_TO_LONG_ERR        3
*              HA_REGISTER_LAYER_ERR      4
*              HA_MODULE_ID_NULL_ERR      5
*              HA_CALL_BACK_NULL_ERR      6
*              HA_CALL_HA_INPUT_NULL_ERR  7
*              VOS_MALLOC_FAILED_1        8
*              VOS_MALLOC_FAILED_2        9
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-28   jiangtao(51916)         Create
*
*******************************************************************************/
extern ULONG TCPIP_HA_RegisterModule(ULONG ulLayer, ULONG ulModId, ULONG ulPriority, UCHAR *pucModuleName,
                                         TCPIP_HA_MODULE_CALLBACK_S *pstModCallback);
/*******************************************************************************
*    Func Name: TCPIP_HA_TravelRegisteredLayer
*  Description: query the registered module
*        Input: ULONG ulLayer:need for inquring
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-31   jiangtao(51916)         Create
*  2007-09-19   y(62007)                Modify for A82D20238修改打印消息
*  2008-06-04   luowentong(00105073)    按照可维可测规范进行整改
*******************************************************************************/
extern VOID TCPIP_HA_TravelRegisteredLayer(ULONG ulLayer);
/*******************************************************************************
*    Func Name: TCPIP_HA_ModuleSendMsg
*  Description: send ha packet interface for every module except transmit layer
*        Input: UCHAR *pucData:
*               ULONG ulDataLen:
*       Output:
*       Return: VOS_OK
*               VOS_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-30   jiangtao(51916)         Create
*
*******************************************************************************/
extern ULONG TCPIP_HA_ModuleSendMsg(UCHAR *pucData, ULONG ulDataLen);
/*******************************************************************************
*    Func Name: TCPIP_HA_GetIsSmoothOrManual
*  Description: obtain the smooth and manual status
*        Input: VOID
*       Output:
*       Return: 1: in smoothing or manualing
*               0: on the contrary
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-30   jiangtao(51916)         Create
*
*******************************************************************************/
extern ULONG TCPIP_HA_GetIsSmoothOrManual(VOID);
/*******************************************************************************
*    Func Name: TCPIP_HA_BeforeSmooth
*  Description: obtain the status of smooth
*        Input: VOID
*       Output:
*       Return: 1: smoothed
*               0: unsmoothed
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-30   jiangtao(51916)         Create
*
*******************************************************************************/
extern ULONG TCPIP_HA_BeforeSmooth(VOID);
/*******************************************************************************
*    Func Name: TCPIP_HA_InitComplete
*  Description: obtain the ha initialization status
*        Input: VOID
*       Output:
*       Return: 1: initializtion
*               0: uninitializtion
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-30   jiangtao(51916)         Create
*
*******************************************************************************/
extern ULONG TCPIP_HA_InitComplete(VOID);
/*******************************************************************************
*    Func Name: TCPIP_HA_CanSendPack
*  Description: checking the moudle sending status
*        Input: ULONG ulModeId: the ha module id for checking the moudle sending status
*       Output:
*       Return: 1: can send HA packet
*               0: can't send HA packet
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-30   jiangtao(51916)         Create
*
*******************************************************************************/
extern ULONG TCPIP_HA_CanSendPack(ULONG ulModeId);

/*******************************************************************************
*    Func Name: TCPIP_HA_SetCksumSwitch
*  Description: 设置发送HA备份消息时是否计算校验和
*        Input: ULONG ulOpenOrClose: 0-不计算, 1-计算
*       Output: 
*       Return: VOS_OK 成功  VOS_ERR 失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-17  wujie(61195)      Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_HA_SetCksumSwitch(ULONG ulOpenOrClose);
/*******************************************************************************
*    Func Name: TCPIP_HA_GetCksumSwitch
*  Description: 获取是否计算HA备份消息校验和的开关
*        Input: VOID
*       Output: 
*       Return: 开关值: 0-不计算, 1-计算
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-17  wujie(61195)      Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_HA_GetCksumSwitch(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SetPublicHADbg
*  Description: 设置调试开关
*        Input: ULONG ulDbg: 设置的调试开关值1--开；0--关
*       Output: 无
*       Return: 成功: VOS_OK
                失败: VOS_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-27   zhanghuihui(55157)      Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPublicHADbg(ULONG ulDbg);
/*******************************************************************************
*    Func Name: TCPIP_GetPublicHADbg
*  Description: 获取调试开关的值
*        Input: ULONG *pulDbg   需要设置值的指针
*       Output: ULONG *pulDbg   已经设了值的指针
*       Return: 成功: VOS_OK
                失败: VOS_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-27   zhanghuihui(55157)      Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPublicHADbg(ULONG *pulDbg);
/*******************************************************************************
*    Func Name: TCPIP_SetPublicHAVerboseDbg
*  Description: 设置HA报文调试开关的接口
*        Input: ULONG ulDbg: 设置的调试开关值
*       Output: 无
*       Return: 成功: VOS_OK
                失败: VOS_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-27   zhanghuihui(55157)      Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPublicHAVerboseDbg(ULONG ulDbg);
/*******************************************************************************
*    Func Name: TCPIP_GetPublicHAVerboseDbg
*  Description: 获取HA报文调试开关的接口
*        Input: ULONG *pulDbg 需要设置值的指针
*       Output: ULONG *pulDbg 已经设了值的指针
*       Return: 成功: VOS_OK
                失败: VOS_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-27   zhanghuihui(55157)      Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPublicHAVerboseDbg(ULONG *pulDbg);

/****************************************************************************
*    Func Name: TCPIP_PPI_HookRegister
*  Description: 注册PPI钩子函数，在系统中只能注册一次(用户保证)
*        Input: pstHookFunc----钩子函数集
*       Output: 
*       Return: VOS_ERR:失败
*               VOS_OK:成功
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-02-28  y36299             Create
*
*******************************************************************************/
extern ULONG TCPIP_PPI_HookRegister(TCPIP_PPI_HOOK_S *pstHookFunc);
/****************************************************************************
*    Func Name: TCPIP_PPI_HookRegisterByType
* Date Created: 2010-07-19
*       Author: fKF30046
*  Description: 注册PPI钩子函数，在系统中只能注册一次(用户保证)
*        Input:ULONG ulType:要注册的函数所属的子系统类别；
                VOID *pfhook:要注册的钩子函数；
*       Output: 
*       Return: VOS_ERR:失败
*               VOS_OK:成功
*      Caution:   协议栈启动前可以重复注册，函数以最后一次注册成功为准
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-07-29  fKF30046            Create
*  2010-08-03  zKF23859           Modify
*******************************************************************************/
ULONG TCPIP_PPI_HookRegisterByType(ULONG ulType, VOID *pfHook);
/****************************************************************************
*    Func Name: TCPIP_PPI_Count_Get
*  Description: 获取PPI统计计数
*        Input: 
*       Output: *pstCount--获取的PPI统计计数结构
*       Return: VOS_ERR:失败
*               VOS_OK:成功
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-02-28  y36299             Create
*
*******************************************************************************/

extern ULONG TCPIP_PPI_Count_Get(TCPIP_PPI_COUNT_S *pstCount);
/****************************************************************************
*    Func Name: TCPIP_PPI_Count_Reset
*  Description: 清零PPI统计计数
*        Input: VOID
*       Output: 
*       Return: VOS_ERR:失败
*               VOS_OK:成功
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-02-28  y36299             Create
*
*******************************************************************************/
extern ULONG TCPIP_PPI_Count_Reset(VOID);
/****************************************************************************
*    Func Name: TCPIP_SetPpiDebugSwitch
*  Description: 设置Debug的开关
*        Input: ulSwitch: Debug开关，0为关闭，1为打开
*       Output: 
*       Return: VOS_ERR:失败
*               VOS_OK:成功
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-02-28  y36299             Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPpiDebugSwitch(ULONG ulSwitch);
/*******************************************************************************
*    Func Name: TCPIP_GetPpiDebugSwitch
*  Description: 获取PPI调试开关
*        Input:
*       Output: ULONG* pulSwitch: PPI开关
*       Return: VOS_OK
*               VOS_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-7-27    mafeng(59090)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetPpiDebugSwitch(ULONG* pulSwitch);

/* 设置和获取报文队列最大缓存数 */
/*******************************************************************************
*    Func Name: TCPIP_SetMaxCachedPkt
*  Description: 用户设置最大缓存报文数的接口
*        Input: ULONG ulMax:用户设置值，范围0--1024；输入0时取VISP默认值128
*       Output: 
*       Return: 成功:VOS_OK
                失败:错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-27   zhanghuihui(55157)      Create
*
*******************************************************************************/
extern ULONG TCPIP_SetMaxCachedPkt(ULONG ulMax);
/*******************************************************************************
*    Func Name: TCPIP_GetMaxCachedPkt
*  Description: 获取报文缓存个数的最大值N_Max
*        Input: ULONG* pulMax:存放的N_Max的指针地址
*       Output: ULONG* pulMax: N_Max的值
*       Return: 成功:VOS_OK
                失败:错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-27   zhanghuihui(55157)      Create
*
*******************************************************************************/
extern ULONG TCPIP_GetMaxCachedPkt(ULONG* pulMax);
/*******************************************************************************
*    Func Name: TCPIP_GetCurCachedPkt
*  Description: 获取当前N值
*        Input: ULONG* pulCurrent:存放的N值的指针地址
*       Output: ULONG* pulCurrent: N的值
*       Return: 成功:VOS_OK
                失败:错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-27   zhanghuihui(55157)      Create
*
*******************************************************************************/
extern ULONG TCPIP_GetCurCachedPkt(ULONG* pulCurrent);

/* 全局调试函数 */
/*******************************************************************************
*    Func Name: TCPIP_ShowARP
*  Description: 显示ARP表项
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2005-03-25  X36317         Create the first version.
*  2006-06-15  X36317         格式化调整.
*
*******************************************************************************/
extern VOID TCPIP_ShowARP(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ShowCompInfo
*  Description: 显示组件注册信息
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2005-03-25  X36317         Create the first version.
*  2006-06-15  X36317         格式化调整.
*
*******************************************************************************/
extern VOID TCPIP_ShowCompInfo(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ShowFIB
*  Description: 显示FIB表项
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2005-03-25  X36317         Create the first version.
*  2006-06-15  X36317         格式化调整.
*
*******************************************************************************/
extern VOID TCPIP_ShowFIB(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ShowInterface
*  Description: 显示接口信息
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2005-03-25  X36317         Create the first version.
*  2006-06-15  X36317         格式化调整.
*
*******************************************************************************/
extern VOID TCPIP_ShowInterface(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ShowInterfaceBriefInfo
*  Description: 查询接口简要信息
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-4-28    sunmo(44939)     Create the first version.
*
*******************************************************************************/
extern VOID TCPIP_ShowInterfaceBriefInfo(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ShowIPAddr
*  Description: 显示地址信息
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2005-03-25  X36317         Create the first version.
*  2006-06-15  X36317         格式化调整.
*
*******************************************************************************/
extern VOID TCPIP_ShowIPAddr(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ShowNetStatus
*  Description: 显示网络状况信息
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2005-03-25  X36317         Create the first version.
*  2006-06-15  X36317         格式化调整.
*
*******************************************************************************/
extern VOID TCPIP_ShowNetStatus(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ShowPacketStatics
*  Description: 查询报文统计信息
*        Input: ULONG ulMid, 模块ID
*               ULONG ulIfIndex, 接口索引
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-4-28    sunmo(44939)     Create the first version.
*  2006-5-17    sunmo(44939)     Modify output info format.
*  2007-5-17    wujie(61195)     Modified for A82D15480，显示函数无返回值
*
*******************************************************************************/
extern VOID TCPIP_ShowPacketStatics(ULONG ulMid, ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_ShowPPPNegoInfo
*  Description: 显示PPP协商信息
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2005-03-25  X36317         Create the first version.
*  2006-06-15  X36317         格式化调整.
*
*******************************************************************************/
extern VOID TCPIP_ShowPPPNegoInfo(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ShowPPPState
*  Description: 显示PPP状态
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2005-03-25  X36317         Create the first version.
*  2006-06-15  X36317         格式化调整.
*
*******************************************************************************/
extern VOID TCPIP_ShowPPPState(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ShowPreConfig
*  Description: 显示预配置信息
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2005-03-25  X36317         Create the first version.
*  2006-06-15  X36317         格式化调整.
*
*******************************************************************************/
extern VOID TCPIP_ShowPreConfig(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ShowRIB
*  Description: 显示RIB表项
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2005-05-30  z36377         Create the first version.
*  2006-06-15  X36317         格式化调整.
*
*******************************************************************************/
extern VOID TCPIP_ShowRIB(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ShowRunInfo
*  Description: 显示协议栈当前运行信息
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2005-03-25  X36317         Create the first version.
*  2006-06-15  X36317         格式化调整.
*
*******************************************************************************/
extern VOID TCPIP_ShowRunInfo(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ShowVersion
*  Description: 显示版本信息
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2005-03-25  X36317         Create the first version.
*  2006-06-15  X36317         格式化调整.
*  2007-07-30  mafeng 59090   增加CPU类型信息
*  2007-12-03  zhukun 36377   版本信息格式调整 SWID00305
*  2008-06-03  X36317         TCPIP_GetVersion已经包含了编译信息和CPU类型信息BC3D000024
*******************************************************************************/
extern VOID TCPIP_ShowVersion(VOID);

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
/*******************************************************************************
*    Func Name: TCPIP_ShowRIBByVrf
*  Description: 显示指定VRF的RIB表项
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-01  qinyun           Create the first version.
*
*******************************************************************************/
extern VOID TCPIP_ShowRIBByVrf(CHAR *pszVrfName);
/*******************************************************************************
*    Func Name: TCPIP_ShowFIBByVrf
*  Description: 显示指定VRF的FIB表项
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-01  qinyun           Create the first version.
*
*******************************************************************************/
extern VOID TCPIP_ShowFIBByVrf(CHAR *pszVrfName);
/*******************************************************************************
*    Func Name: TCPIP_ShowIPAddrByVrf
*  Description: 显示指定VRF的地址信息
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-01  qinyun           Create the first version.
*
*******************************************************************************/
extern VOID TCPIP_ShowIPAddrByVrf(CHAR *pszVrfName);
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

/*******************************************************************************
*    Func Name: TCPIP_Set_ICDbgLevel
*  Description: 设置VISP的信息输出等级
*        Input: ULONG ulLevel: lLevel 取值: 1-LOG, 2-TRAP, 3-DEBUG(默认值).
*       Output:
*       Return: 成功返回VOS_OK, 失败返回VOS_ERR
*      Caution: 应用VISP时，调用此函数设置VISP的信息输出等级。
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-11-1  X36317         Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_Set_ICDbgLevel(ULONG ulLevel);
/*******************************************************************************
*    Func Name: TCPIP_Get_ICDbgLevel
*  Description: 获取VISP的信息输出等级
*        Input: ULONG *pulLevel:
*       Output:
*       Return: 成功返回VOS_OK, 失败返回VOS_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-11-19   zhanghuihui(55157)      Create
*
*******************************************************************************/
extern ULONG TCPIP_Get_ICDbgLevel(ULONG *pulLevel);
/*******************************************************************************
*    Func Name: TCPIP_SetPacketTrace
*  Description: 设置报文调试开关
*        Input: ULONG ulMid, 模块ID
*               ULONG ulEnable, 打开/关闭标记, 1-打开, 0-关闭, 其它-非法
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-4-28    sunmo(44939)     Create the first version.
*  2006-5-17    sunmo(44939)     将获取组件虚表的方式修改为根据模块ID获取相应的虚表
*  2007-8-1     l61496           增加返回错误码
*******************************************************************************/
extern ULONG TCPIP_SetPacketTrace(ULONG ulMid, ULONG ulEnable);
/*******************************************************************************
*    Func Name: TCPIP_SetDebugLevel
*  Description: 按模块设置Debug级别
*        Input: ULONG ulMid:        模块号，取值范围见TCPIP_DEBUG_MID_INFO_E
*               ULONG ulDebugLevel: Debug级别，取值范围见TCPIP_DEBUG_LEVEL_E
*       Output: 
*       Return: 成功返回0，失败返回1
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2005-03-25  X36317         Create the first version.
*  2006-06-15  X36317         格式化调整，并删除了SFIB的调试开关设置.A82D02265
*  2007-08-01  l61496         增加错误码
*******************************************************************************/
extern ULONG TCPIP_SetDebugLevel(ULONG ulMid, ULONG ulDebugLevel);
/*******************************************************************************
*    Func Name: TCPIP_GetDebugLevel
*  Description: 获取模块调试级别
*        Input: ULONG ulMid:
*
*       Output: ULONG* pulDebugLevel:
*       Return: VOS_OK
*               V0S_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-7-27    mafeng(59090)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetDebugLevel(ULONG ulMid, ULONG* pulDebugLevel);

/*******************************************************************************
*    Func Name: TCPIP_SetLogType
*  Description: 日志类型输出控制接口
*        Input: ULONG ulWarningEnable:告警日志使能开关,0 去使能,1 使能
*               ULONG ulCfgEnable:操作日志使能开关,0 去使能,1 使能
*               ULONG ulRunEnable:运行日志使能开关,0 去使能,1 使能
*       Output: 无
*       Return: 成功VOS_OK,其他返回失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_SetLogType(ULONG ulWarningEnable, ULONG ulCfgEnable, ULONG ulRunEnable);
/*******************************************************************************
*    Func Name: TCPIP_GetLogType
*  Description: 获取日志类型值
*        Input: 无
*       Output: ULONG* pulWarningEnable:要获取的告警日志类型值,1使能,0去使能
*               ULONG* pulCfgEnable:要获取的操作日志类型值,1使能,0去使能
*               ULONG* pulRunEnable:要获取的运行日志类型值,1使能,0去使能
*       Return: 成功VOS_OK;失败VOS_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_GetLogType(ULONG* pulWarningEnable, ULONG* pulCfgEnable, ULONG* pulRunEnable);

/*******************************************************************************
*    Func Name: TCPIP_SetLogTypeNoLevelLimit
* Date Created: 2010-07-22
*       Author: liangjicheng
*  Description: 日志类型输出控制接口-不受Level限制
*        Input: ULONG ulWarningEnable:告警日志使能开关,0 去使能,1 使能
*               ULONG ulCfgEnable:操作日志使能开关,0 去使能,1 使能
*               ULONG ulRunEnable:运行日志使能开关,0 去使能,1 使能
*       Output: 无
*       Return: 成功VOS_OK,其他返回失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-07-22   liangjicheng            Create BC3D03507 增强日志控制
*******************************************************************************/
ULONG TCPIP_SetLogTypeNoLevelLimit(ULONG ulWarningEnable, ULONG ulCfgEnable, ULONG ulRunEnable);

/*******************************************************************************
*    Func Name: TCPIP_GetLogTypeNoLevelLimit
* Date Created: 2010-07-22
*       Author: liangjicheng
*  Description: 获取不受Level限制的日志类型值
*        Input: 无
*       Output: ULONG* pulWarningEnable:要获取的告警日志类型值,1使能,0去使能
*               ULONG* pulCfgEnable:要获取的操作日志类型值,1使能,0去使能
*               ULONG* pulRunEnable:要获取的运行日志类型值,1使能,0去使能
*       Return: 成功VOS_OK;失败VOS_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-07-22   liangjicheng            Create BC3D03507 增强日志控制
*
*******************************************************************************/
ULONG TCPIP_GetLogTypeNoLevelLimit(ULONG* pulWarningEnable, ULONG* pulCfgEnable, ULONG* pulRunEnable);

/*******************************************************************************
*    Func Name: TCPIP_SetLogLevel
* Date Created: 2006-4-29
*       Author: wuhailan(HT06310)
*  Description: 设置要记录的日志信息的级别
*        Input: ULONG ulLogLevel:LOG信息等级.VISP日志级别分为五个级别:
*               0 TCPIP_LOG_LEVEL_CRITICAL,1 TCPIP_LOG_LEVEL_ERROR,2 TCPIP_LOG_LEVEL_WARNING,
*               3 TCPIP_LOG_LEVEL_INFO,4 TCPIP_LOG_LEVEL_DEBUG,VISP默认为INFO级别.
*       Output: 无
*       Return: 成功 0,失败 1
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-4-29  wuhailan(06310)   Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetLogLevel(ULONG ulLogLevel);

/*******************************************************************************
*    Func Name: TCPIP_GetLogLevel
* Date Created: 2007-7-27
*       Author: mafeng(59090)
*  Description: 获取记录日志信息的级别
*        Input: 
*       Output: ULONG* pulLogLevel:VISP日志级别分为五个级别:
*               0 TCPIP_LOG_LEVEL_CRITICAL,1 TCPIP_LOG_LEVEL_ERROR,2 TCPIP_LOG_LEVEL_WARNING,
*               3 TCPIP_LOG_LEVEL_INFO,4 TCPIP_LOG_LEVEL_DEBUG,VISP默认为INFO级别.
*       Return: VOS_OK
*               VOS_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-7-27    mafeng(59090)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetLogLevel(ULONG* pulLogLevel);

/*******************************************************************************
*    Func Name: TCPIP_ShowHASmoothCost
*  Description: 显示计算HA平滑时延时间及TICK差值
*        Input: VOID
*       Output: 无
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-14   wuhailan                Create
*
*******************************************************************************/
extern VOID  TCPIP_ShowHASmoothCost(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ShowHAStatistic
*  Description: 显示HA统计信息
*        Input:
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   zhoutong(43740)         Create
*
*******************************************************************************/
extern VOID  TCPIP_ShowHAStatistic(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ShowNPCount
*  Description: 显示NP下发统计信息
*        Input:
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   zhoutong(43740)         Create
*
*******************************************************************************/
extern VOID  TCPIP_ShowNPCount(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ShowNPRegisterInfo
*  Description: 显示NP钩子函数注册情况
*        Input: VOID
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   zhoutong(43740)         Create
*
*******************************************************************************/
extern VOID  TCPIP_ShowNPRegisterInfo(VOID);

/*******************************************************************************
*    Func Name: TCPIP_ComputeNPUpdateCost
*  Description: 使能计算NP下发时延开关
*        Input: ULONG ulSetYes:使能开关:1使能,0去使能
*       Output: 无
*       Return: 成功VOS_OK,其他返回失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-15   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_ComputeNPUpdateCost(ULONG ulSetYes);
/*******************************************************************************
*    Func Name: TCPIP_ShowNPUpdateCost
*  Description: 显示NP下发耗时信息
*        Input: 无
*       Output: 无
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-15   wuhailan                Create
*
*******************************************************************************/
extern VOID  TCPIP_ShowNPUpdateCost(VOID);

/*******************************************************************************
*    Func Name: TCPIP_GetMemInfoByMid
*  Description: 获取指定模块的内存统计值,如果ulMid传0则认为获取总的统计信息
*               对于MBUF模块统计无法获取,可以通过MBUF提供的接口查看DB等使用情况
*        Input: ULONG ulMid:模块ID
*       Output: ULONG *pulSize:返回指定的模块内存统计值
*       Return: VOS_OK成功,其他返回失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_GetMemInfoByMid(ULONG ulMid,ULONG *pulSize);
/*******************************************************************************
*    Func Name: TCPIP_ShowMemInfo
*  Description: 显示各模块内存统计情况信息,对于MBUF情况只能统计显示MBUF CACHE中
*               的HEAD/DBD/DB的数目,若用户超过MBUF CACHE支持的最大规格,则无法统计.
*        Input: 无
*       Output: 无
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   wuhailan                Create
*
*******************************************************************************/
extern VOID  TCPIP_ShowMemInfo(VOID);

/*******************************************************************************
*    Func Name: TCPIP_ShowMbufInfo
* Date Created: 2009-02-28
*       Author: wuhailan/zhangchi(00103194/00142640)
*  Description: 显示各模块使用Mbuf统计情况信息,
*        Input: 无
*       Output: 无
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-28   wuhailan/zhangchi(00103194/00142640)  Create
*
*******************************************************************************/
extern VOID TCPIP_ShowMbufInfo(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SystemEntry
*  Description: VISP协议栈的入口函数
*        Input: None
*       Output: None
*       Return: 成功返回VOS_OK，失败返回VOS_ERR
*      Caution: 该函数被VISP_InitTCPIPStack所调用,用于初始化协议栈
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-11-01  X36317         Creat the first version.
*  2007-03-23  J51916         Modify for A82D12837
*
*******************************************************************************/
extern ULONG TCPIP_SystemEntry(VOID);
/*******************************************************************************
*    Func Name: TCPIP_Set_PreConfigPara
*  Description: VISP 预配置参数值设置函数
*        Input: ULONG ulKey:   预配置项,取值范围见枚举定义TCPIP_PRECONFIG_INFO_E
*               ULONG ulValue: 参数值
*       Output: None
*       Return: 成功返回VOS_OK, 失败返回VOS_ERR
*      Caution: 此函数提供给产品用户VISP参数预配置
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-11-1  X36317         Creat the first version.
*  2007-04-2  z62474         Modified for A82D12602(预配置设置时即检查合法性)
*  2007-7-17  wuhailan       modify for A82D17105,调整输出函数
*******************************************************************************/
extern ULONG TCPIP_Set_PreConfigPara(ULONG ulKey, ULONG ulValue);
/*******************************************************************************
*    Func Name: TCPIP_GetVersion
*  Description: 获取TCPIP的版本信息(含版本号/编译时间/CPU类型)
*        Input:
*       Output: CHAR *pVerInfo:字符串指针,用于保存获取到的TCPIP版本信息。
*               注: 此字符串的长度不得小于128字节!
*       Return: 成功返回VOS_OK，失败返回VOS_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2004-11-8   X36317                  Create for SWFD03040
*  2008-06-03  X36317                  添加编译信息和CPU类型信息BC3D000024
*
*******************************************************************************/
extern LONG  TCPIP_GetVersion(CHAR *pVerInfo);

/*******************************************************************************
*    Func Name: TCPIP_EnMBufQueue
*  Description: 把MBUF报文送入指定的报文队列
*        Input: MBUF_S* pMBuf:报文指针
*               ULONG ulQueueID: 队列ID
*               ulIfIndex: 入接口索引
*       Output:
*       Return: PUBLIC_ERR_MBUF_NULL 报文为空
*               PUBLIC_ERR_QUEUE_ID  报文队列非法
*               VOS_ERR              失败
*               VOS_OK               成功
*      Caution: 如果是入链路层队列，入接口索引为收到报文的物理接口的索引。
*               如果是入网络层队列，入接口索引为路由可见接口的索引。
*               该函数无论成功与否,报文都由该函数内部释放,调用者不能再释放报文
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-17   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_EnMBufQueue(MBUF_S* pMBuf, ULONG ulQueueID,ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncLinkHook
*  Description: 链路层钩子结点注册函数
*        Input: ULONG ulType:注册类型,1接收方向,2发送方向
*               TCPIP_LINK_HOOK_FUNC pfHook:函数指针
*               ULONG ulPriority:优先级,优先级高的插入的链表前面
*       Output: 无
*       Return: VOS_OK成功,其他返回失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-15   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncLinkHook(ULONG ulType, TCPIP_LINK_HOOK_FUNC pfHook, ULONG ulPriority);
/*******************************************************************************
*    Func Name: TCPIP_UnRegFuncLinkHook
*  Description: 链路层钩子结点注销函数
*        Input: ULONG ulType:注册类型,1接收方向,2发送方向
*               TCPIP_LINK_HOOK_FUNC pfHook:函数指针
*       Output: 无
*       Return: VOS_OK成功,其他返回失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-15   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_UnRegFuncLinkHook(ULONG ulType, TCPIP_LINK_HOOK_FUNC pfHook);

/***********************性能优化提供的用户接口***********************/

/* 性能优化用户接口返回的错误码 */
enum tagOPTErrCode
{
    OPTIM_OK = VOS_OK,
    OPTIM_ERR = VOS_ERR,
    OPTIM_ERR_HA_IS_SMOOTHING,       /* 2, HA正在手动或平滑中 */
    OPTIM_ERR_FILTER,                /* 3, NP未处理报文 */
    OPTIM_ERR_ST_PARAM,              /* 4, 使能优化参数错误(0/1之外) */
    OPTIM_ERR_SUM_PARAM,             /* 5, 使能缓存表项数量参数错误 */
    OPTIM_ERR_RTMODE,                /* 6, 路由模式预配置不可以使能优化 */
    OPTIM_ERR_SKTMODE,               /* 7, socket非全局模式不可以使能优化 */
    OPTIM_ERR_MEMORY,                /* 8, 分配缓存表项内存资源失败 */
    OPTIM_ERR_TIMER,                 /* 9, 创建缓存表刷新定时器失败 */
    OPTIM_ERR_DISABLE,               /* 10, 未使能性能优化 */
    OPTIM_ERR_HOOK_NULL,             /* 11, 未注册钩子处理函数 */
    OPTIM_ERR_ENTRY_NULL,            /* 12, 未查找到缓存表项 */
    OPTIM_ERR_VRF_INIT,              /* 13, 使能VRF不能进行性能优化 */
};

typedef ULONG(*OPTIM_INTERMEDIATE_HOOK_FUNC)(ULONG ulPktFlowType, MBUF_S *pstMbuf);

/* IP报文中五元组的信息network seq */
typedef struct tagTcpipOptimIpInfo
{
    ULONG ulSIP;    /* 源地址 */
    ULONG ulDIP;    /* 目的地址 */
    USHORT usSP;    /* 源端口号 */
    USHORT usDP;    /* 目的端口号 */
    UCHAR ucPID;    /* 协议号 */
    UCHAR ucPadding[3];
}TCPIP_OPTIMIPINFO_S;


/* 用户获取缓存表项信息数据结构 */
typedef struct tagTcpipOptimEntryInfo
{
    /* 1, host receive, 2, forward, 3, host send */
    UCHAR ucCacheType; /* SEND/RECEIVE/FORWARD */

    /* 17:udp,6:tcp,0:rawip,17:iwf */
    UCHAR ucPktType;   /* UDP/TCP/RAWIP/IWF */
    UCHAR ucNPFlag;    /* NP flag */
    UCHAR ucTmFlag;    /* time 老化标志*/

    LONG  iFd;            /* visp rcv/send skt id  */
    ULONG ulOutIfIndex;   /* snd ifnet index */
    ULONG ulVLINKIndex;   /* vlink index */
    ULONG ulNextHop;      /* next hop,network seq */

    TCPIP_OPTIMIPINFO_S stOptIpInfo; /* SIP/DIP/SP/DP/PID */
}TCPIP_OPTENTRYINFO_S;

/* 性能优化报文统计数据结构 */
typedef struct tagOptimStat
{
    ULONG   ulUdpRcv;   /* UDP received */
    ULONG   ulIWFRcv;   /* IWF received */
    ULONG   ulTcpRcv;   /* TCP received */
    ULONG   ulRipRcv;   /* RIP received */
    ULONG   ulEthRcv;   /* ETH received */
    ULONG   ulNoEthRcv; /* PPP received */
    ULONG   ulNPRcv;    /* NP received */

    ULONG   ulUdpSnd;   /* UDP Send */
    ULONG   ulTcpSnd;   /* TCP Send */
    ULONG   ulRipSnd;   /* RIP Send */
    ULONG   ulIWFSnd;   /* IWF Send */
    ULONG   ulEthSnd;   /* ETH Send */
    ULONG   ulNoEthSnd; /* No ETH Send */
    ULONG   ulPPISnd;   /* PPI Send */

    ULONG   ulNoOpt_E;  /* NoOptim_NoEntry */
}TCPIP_OPTIMSTAT_S;

/*******************************************************************************
*    Func Name: TCPIP_ClearOptimStatics
*  Description: 清空协议栈性能优化统计信息
*        Input: VOID
*       Output:
*       Return: OPTIM_OK
*               OPTIM_ERR_DISABLE
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-20   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_ClearOptimStatics(VOID);
/*******************************************************************************
*    Func Name: TCPIP_GetOptDbgSwitch
*  Description: 获取性能优化调试开关状态
*        Input: ULONG *pulOptDebug:返回调试开关状态
*       Output: pulOptDebug:性能优化调试开关状态
*       Return: OPTIM_OK
*               OPTIM_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-20   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetOptDbgSwitch(ULONG *pulOptDebug);
/*******************************************************************************
*    Func Name: TCPIP_GetOptimFlag
*  Description: 获取协议栈性能使能/去使能状态
*        Input: ULONG* pulFlag:性能优化使能标志
*               ULONG *pulOptEntryNum:性能优化设置缓存表项数量
*       Output:
*       Return: OPTIM_OK
*               OPTIM_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-04   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetOptimFlag(ULONG* pulFlag, ULONG *pulOptEntryNum);
/*******************************************************************************
*    Func Name: TCPIP_GetOptimStatics
*  Description: 获取协议栈性能优化统计信息
*        Input: TCPIP_OPTIMSTAT_S* pstOptStat: 性能优化报文统计信息指针
*       Output:
*       Return: OPTIM_OK
*               OPTIM_ERR_DISABLE
*               OPTIM_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-20   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetOptimStatics(TCPIP_OPTIMSTAT_S* pstOptStat);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncOptimHook
*  Description: 用户注册性能优化中间处理钩子函数(注册/解注册)
*        Input: OPTIM_INTERMEDIATE_HOOK_FUNC pfHookFuc:
*                  用户注册的钩子处理函数指针，为空则标识解注册
*       Output:
*       Return: VOS_OK
*               OPTIM_ERR_DISABLE
*               OPTIM_ERR_HOOK_NULL
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-20   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncOptimHook(OPTIM_INTERMEDIATE_HOOK_FUNC pfHookFuc);
/*******************************************************************************
*    Func Name: TCPIP_SetOptDbgSwitch
*  Description: 设置调试开关状态
*        Input: ULONG ulOptDebug:日志调试开关状态(1:打开调试开关,0:关闭调试开关)
*       Output:
*       Return: VOS_OK
*               OPTIM_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-04   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_SetOptDbgSwitch(ULONG ulOptDebug);
/*******************************************************************************
*    Func Name: TCPIP_SetOptimFlag
*  Description: 设置协议栈性能优化使能/去使能(1:使能/0:去使能)
*        Input: ULONG ulEnableFlag: 1:使能 0:去使能
*               ULONG ulOptEntryNum: 缓存优化表项的数量(0用户缺省/32-1024)
*       Output:
*       Return: VOS_OK
*               OPTIM_ERR_HA_IS_SMOOTHING
*               OPTIM_ERR_ST_PARAM
*               OPTIM_ERR_RTMODE
*               OPTIM_ERR_SKTMODE
*               OPTIM_ERR_MEMORY
*               OPTIM_ERR_TIMER
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-04   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_SetOptimFlag(ULONG ulEnableFlag, ULONG ulOptEntryNum);
/*******************************************************************************
*    Func Name: TCPIP_ShowOptimFlag
*  Description: 显示性能优化使能状态
*        Input: VOID
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-04   mafeng(59090)           Create
*
*******************************************************************************/
extern VOID  TCPIP_ShowOptimFlag(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ShowOptimStatics
*  Description: 显示协议栈性能优化统计信息
*        Input: VOID
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-20   mafeng(59090)           Create
*
*******************************************************************************/
extern VOID  TCPIP_ShowOptimStatics(VOID);
/*******************************************************************************
*    Func Name: TCPIP_GetOptimEntryInfo
*  Description: 用户根据五元组信息获取缓存表项信息
*        Input: TCPIP_OPTIPINFO_S *pstOptIpInfo:五元组信息
*       Output: TCPIP_OPTENTRYINFO_S *pstOptEntryInfo:缓存表项信息
*       Return: OPTIM_OK
*               OPTIM_ERR
*               OPTIM_ERR_DISABLE
*               OPTIM_ERR_ENTRY_NULL
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-25   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetOptimEntryInfo(TCPIP_OPTIMIPINFO_S *pstOptIpInfo, TCPIP_OPTENTRYINFO_S *pstOptEntryInfo);
/*******************************************************************************
*    Func Name: TCPIP_ShowOptimEntryInfo
*  Description: 按类型显示缓存表项内容信息
*        Input: ULONG ulEntryType:主机接收-1、转发-2、主机发送-3三类缓存表项
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-25   mafeng(59090)           Create
*
*******************************************************************************/
extern VOID TCPIP_ShowOptimEntryInfo(ULONG ulEntryType);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncNPDownloadFailedProcFunc
*  Description: 注册钩子函数, 如果NP下发失败, VISP会调用此钩子函数对外通知
*        Input: NPDOWNLOAD_FAILED_PROCESS pfHookFunc: 钩子函数
*       Output: 
*       Return: VOS_OK 成功  VOS_ERR 失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-15  wujie(61195)     Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncNPDownloadFailedProcFunc( NPDOWNLOAD_FAILED_PROCESS pfHookFunc );

/*******************************************************************************
*    Func Name: TCPIP_HDR_Init
* Date Created: 2009-02-26
*       Author: wuhailan/zhangchi(00103194/00142640)
*  Description: 体检报告及日志任务初始化
*        Input: ULONG ulTaskPri:        任务优先级，输入0则使用默认值
*               ULONG ulTaskStackSize:  任务调用栈，输入0则使用默认值
*       Output:
*       Return: 成功返回VOS_OK,其他返回VOS_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-26   wuhailan/zhangchi(00103194/00142640)  Create
*
*******************************************************************************/
extern ULONG TCPIP_HDR_Init(ULONG ulTaskPri,ULONG ulTaskStackSize);

/*******************************************************************************
*    Func Name: TCPIP_Health_Checkup
* Date Created: 2009-02-26
*       Author: wuhailan/zhangchi(00103194/00142640)
*  Description: 设置体检报告输出时间间隔及体检模块
*        Input: ULONG ulSwitch:          体检开关
*               ULONG ulTimer:           时间间隔
*               ULONG ulHeadthBatchFlag: 模块标记
*       Output: 
*       Return: 成功返回VOS_OK,其他返回错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-26   wuhailan/zhangchi(00103194/00142640)  Create
*
*******************************************************************************/
extern ULONG TCPIP_Health_Checkup(ULONG ulSwitch, ULONG ulTimer, ULONG ulHeadthBatchFlag);

typedef ULONG (*TCPIP_HEALTH_OUTPUT_HOOK_FUNC)(CHAR *pcBuf, ULONG ulMsglen, ULONG ulScanId);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncHealthOutputHook
* Date Created: 2009-02-26
*       Author: wuhailan/zhangchi(00103194/00142640)
*  Description: 体检报告输出钩子注册函数
*        Input: TCPIP_HEALTH_OUTPUT_HOOK_FUNC pfFunc:函数首地址
*       Output:
*       Return: 成功返回VOS_OK,其他返回错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-26   wuhailan/zhangchi(00103194/00142640)  Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncHealthOutputHook(TCPIP_HEALTH_OUTPUT_HOOK_FUNC pfFunc);

typedef ULONG (*TCPIP_LASTWORD_OUTPUT_HOOK_FUNC)(CHAR *pcMemAddr, ULONG ulMemlen);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncLastWordOutputHook
* Date Created: 2009-03-02
*       Author: wuhailan/zhangchi(00103194/00142640)
*  Description: 临终遗言输出钩子注册函数
*        Input: TCPIP_LASTWORD_OUTPUT_HOOK_FUNC pfFunc:函数首地址
*       Output:
*       Return: 成功返回VOS_OK,其他返回错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-03-02   wuhailan/zhangchi(00103194/00142640)  Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncLastWordOutputHook(TCPIP_LASTWORD_OUTPUT_HOOK_FUNC pfFunc);

/*******************************************************************************
*    Func Name: TCPIP_LastWord_Checkup
* Date Created: 2009-03-02
*       Author: wuhailan/zhangchi(00103194/00142640)
*  Description: 临终遗言处理函数
*        Input:
*       Output:
*       Return: 成功返回VOS_OK,其他返回错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-03-02   wuhailan/zhangchi(00103194/00142640)  Create
*
*******************************************************************************/
extern ULONG TCPIP_LastWord_Checkup(ULONG ulMemSize,ULONG ulLastWordBatchFlag);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetLinkControlPacketHook
* Date Created: 2009-02-24
*       Author: ZhengSenHuo(104483)
*  Description: 注册链路层获取控制报文钩子函数
*        Input: GetLinkControlPacket_HOOK_FUNC  * pfHookFunc:钩子函数指针
*               目前VISP支持的协议号:0x8809(慢协议) -->子协议号:0x01(LACP)
*                                                              :0x03(OAM3AH)
*                                   :0xc021(LCP)、0x8021(IPCP)、0x8057(IP6CP)、0xc023(PAP)、
*                                    0xc223(CHAP)、0xc025(LQR)、0x8023(OSICP)、0x8059(PPPMUXCP)
*                                    -->以此协议没有子协议号
*       Output:
*       Return: 成功返回VOS_OK,失败返回VOS_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-24   ZhengSenHuo(104483)     Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncGetLinkControlPacketHook(GetLinkControlPacket_HOOK_FUNC  pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_UnRegFuncGetLinkControlPacketHook
* Date Created: 2009-02-24
*       Author: ZhengSenHuo(104483)
*  Description: 解注册链路层获取控制报文钩子函数
*        Input: VOID
*       Output:
*       Return: 成功返回VOS_OK,失败返回VOS_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-24   ZhengSenHuo(104483)     Create
*
*******************************************************************************/
extern ULONG TCPIP_UnRegFuncGetLinkControlPacketHook(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SetResLimitRestrainTime
* Date Created: 2009-03-02
*       Author: z00104207
*  Description: 资源占用超过阈值时，VISP会记录日志，如果资源占用超过阈值出现反复
*               抖动时，就会记录多条日志，因此需要在规定时间内对这类日志进行抑制，
*               本接口提供设置该规定时间的功能。
*        Input: ULONG ulTime: 时间值，范围0~60，单位秒。0表示不抑制。
*       Output: 
*       Return: 成功VOS_OK，失败返回其他错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-03-02   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_SetResLimitRestrainTime(ULONG ulTime);

/*******************************************************************************
*    Func Name: TCPIP_ClearMemErrInfo
* Date Created: 2008-12-13
*       Author: zhangchunyu(62474)
*  Description: 清空内存出错统计
*        Input: VOID
*       Output: 无
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-13    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_ClearMemErrInfo(VOID);

/*******************************************************************************
*    Func Name: TCPIP_ShowMemErrInfo
* Date Created: 2008-12-13
*       Author: zhangchunyu(62474)
*  Description: 显示内存出错信息
*        Input: VOID
*       Output: 无
*       Return: VOID
*      Caution: 目前记录最近出错信息只输出一个参数,后续扩展需要修改该函数
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-13    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_ShowMemErrInfo(VOID);

/*******************************************************************************
*    Func Name: TCPIP_GetMemErrInfo
* Date Created: 2008-12-13
*       Author: zhangchunyu(62474)
*  Description: 获取内存出错统计信息
*        Input: MEMERRSTAT_S *pstMemErrStat:
*       Output: pstMemErrStat内存出错统计信息
*       Return: VOS_OK,成功, 其他,失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-13    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetMemErrInfo(MEMERRSTAT_S * pstMemErrStat);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncGoNextHook
* Date Created: 2009-03-04
*       Author: wangbin (62223)
*  Description: 注册通知dopra下一阶段启动处理
*        Input: VOID
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-03-04   wangbin (62223)         Create
*
*******************************************************************************/

extern ULONG TCPIP_RegFuncGoNextHook(GoNext_HOOK_FUNC pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_PrintToCOM
* Date Created: 2008-9-28
*       Author: wujie(61195)
*  Description: 设置日志、调试信息、显示信息是否打印到com口
*        Input: ULONG ulSwitch:
*               bit 0: 是否输出定长日志到com口 0 否  1 是
*               bit 1: 是否输出变长日志到com口 0 否  1 是
*               bit 2: 是否输出调试信息到com口 0 否  1 是
*               bit 3: 是否输出显示信息到com口 0 否  1 是
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-9-28   wujie(61195)     Create the first version.
*
*******************************************************************************/
extern VOID TCPIP_OutputToCOM(ULONG ulSwitch);


/*******************************************************************************
*    Func Name: TCPIP_SetSockRunSchedNum
* Date Created: 2008-08-05
*       Author: fangpu
*  Description: 设置sockrun任务单次调度报文次数
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-08-05   fangpu                Create
*
*******************************************************************************/
extern ULONG TCPIP_SetSockRunSchedNum( ULONG ulSockRunSchedNum );

/*******************************************************************************
*    Func Name: TCPIP_GetSockRunSchedNum
* Date Created: 2008-08-05
*       Author: fangpu
*  Description: 获取sockrun任务单次调度报文次数
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-08-05   fangpu                Create
*
*******************************************************************************/
extern ULONG TCPIP_GetSockRunSchedNum( ULONG* pulSockRunSchedNum );

/*******************************************************************************
*    Func Name: TCPIP_ShowSockRunSchedNum
* Date Created: 2008-08-05
*       Author: fangpu
*  Description: 显示sockrun任务单次调度报文次数
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-08-05   fangpu                Create
*
*******************************************************************************/
extern ULONG TCPIP_ShowSockRunSchedNum( VOID );

/*********************************全局变量定义********************************/


/*****************************************************************************
 函 数 名  : TCPIP_GetInterfaceInfo
 功能描述  : 获取接口详细信息
 输入参数  : ULONG ulIfIndex  :接口索引
             UCHAR *szBuf     :buf指针
             ULONG ulBufLen   :buf大小
             ULONG ulLen      :大小
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年4月20日
    作    者   : w62223
    修改内容   : 新生成函数

*****************************************************************************/

extern ULONG TCPIP_GetInterfaceInfo(ULONG ulIfIndex,CHAR *szBuf,ULONG ulBufLen,ULONG *pulLen);

/*****************************************************************************
 函 数 名  : TCPIP_RegFuncTrrtUserStopHook
 功能描述  :  注册用户traceroute停止命令函数
 输入参数  : gpfTCPIPUserStopEx pfHookFunc
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年4月28日
    作    者   : w62223
    修改内容   : 新生成函数

*****************************************************************************/

extern ULONG TCPIP_RegFuncTrrtUserStopHook(gpfTCPIPTrrtUserStopEx pfHookFunc);


/*****************************************************************************
 函 数 名  : TCPIP_RegFuncPingUserStopHook
 功能描述  :  注册用户Ping停止命令函数
 输入参数  : g_pfTCPIPPingUserStopEx pfHookFunc
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年4月28日
    作    者   : w62223
    修改内容   : 新生成函数

*****************************************************************************/

extern ULONG TCPIP_RegFuncPingUserStopHook(gpfTCPIPPingUserStopEx pfHookFunc);


/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetTunnelMtuHook
* Date Created: 2009-11-19
*       Author: zhangchunyu(62474)
*  Description: 注册产品获取隧道MTU
*        Input: gpfTCPIP_GetTunnelMtu_HOOK_FUNC pfHookFunc: 获取隧道
*       Output:
*       Return: 成功VOS_OK
*               失败VOS_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-11-19    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncGetTunnelMtuHook(gpfTCPIP_GetTunnelMtu_HOOK_FUNC pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncRebootModeHook
* Date Created: 2008-8-15
*       Author: zhangchunyu(62474)
*  Description: 注册本次启动钩子函数
*        Input: TCPIP_REBOOT_MODE_HOOK_FUNC pfHookFuc: 实现本次启动方式钩子函数
*       Output:
*       Return: GR_SUCCESS: 成功 其他: 失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-15    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_RegFuncRebootModeHook(TCPIP_REBOOT_MODE_HOOK_FUNC pfHookFuc);

/*******************************************************************************
*    Func Name: TCPIP_GetInterfaceInfoByIfIndex
* Date Created: 2008-8-16
*       Author: zhangchunyu(62474)
*  Description: 根据IFINDEX查询端口类型端口号的API函数
*        Input: ULONG ulIfIndex:接口索引
*
*       Output: ULONG *pulPortType:接口类型
*               ULONG *pulPortNo:接口号
*       Return: GR_SUCCESS: 成功, 其他: 失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-16    zhangchunyu(62474)     Creat the first version.
*******************************************************************************/
ULONG TCPIP_GetInterfaceInfoByIfIndex(ULONG ulIfIndex, ULONG *pulPortType, ULONG *pulPortNo);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetSockMaxNum
* Date Created: 2009-10-22
*       Author: LY(57500)
*  Description: 产品注册VISP能创建的最大socket个数钩子函数
*        Input: gpfGetSockMaxNum pfHookFunc:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-22    LY(57500)     Create the first version.
*
*******************************************************************************/
ULONG TCPIP_RegFuncGetSockMaxNum(gpfGetSockMaxNum pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncRegAllAppInfo
* Date Created: 2014-11-26
*       Author: yanlei00216869
*  Description: 产品注册组件注册的钩子函数
*        Input: gpfRegAllAppInfo pfHookFunc
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-11-26   yanlei00216869   Create the first version.
*
*******************************************************************************/
ULONG TCPIP_RegFuncRegAllAppInfo(gpfRegAllAppInfo pfHookFunc);


/*******************************************************************************
*    Func Name: TCPIP_ShowAllVpnArpInfo
* Date Created: 2008-5-15
*       Author: zhangchunyu(62474)
*  Description: 显示所有ARP表项，在函数ETHARP_ShowArpInfo基础上增加显示VPN 信息、VLAN ID信息
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-5-15    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_ShowAllVpnArpInfo(VOID);

/*******************************************************************************
*    Func Name: TCPIP_ShowAllVrfIPAddr
* Date Created: 2008-5-14
*       Author: zhangchunyu(62474)
*  Description: 显示所有实例下的地址
*        Input: VOID
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-5-14    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_ShowAllVrfIPAddr(VOID);


/*********************************全局变量定义********************************/

/* 钩子函数原型，实现的功能是:在Master路由器上虚拟IP冲突检测，即检测传入的地址是否与指定接
   口上的某个Master备份组的虚IP冲突（即是否相等，相等则返回1，否则返回0）；入参地址是网络序 */
typedef ULONG (*TCPIP_VirtualIpAddrConflict_HOOKFUNC)(ULONG ulIfIndex, ULONG ulIpAddr);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncVirtualIpAddrConflict
* Date Created: 2010-01-07
*       Author: z00104207
*  Description: 注册TCPIP_VirtualIpAddrConflict_HOOKFUNC钩子函数
*        Input: TCPIP_VirtualIpAddrConflict_HOOKFUNC pfHookFunc: 钩子函数
*       Output:
*       Return: 成功则返回VOS_OK，失败则返回其他错误码
*      Caution: 请参考TCPIP_VirtualIpAddrConflict_HOOKFUNC的定义描述
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-01-07   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncVirtualIpAddrConflict(TCPIP_VirtualIpAddrConflict_HOOKFUNC pfHookFunc);


/* 钩子函数原型，实现的功能是:判断physical地址是否与指定接口上某个备份组的虚MAC相同，是则返回1，否则返回0 */
typedef ULONG (*TCPIP_CompareVirtualMac_HOOKFUNC)(ULONG ulIfIndex, UCHAR *aucMacAddr);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncCompareVirtualMac
* Date Created: 2010-01-07
*       Author: z00104207
*  Description: 注册TCPIP_CompareVirtualMac_HOOKFUNC钩子函数
*        Input: TCPIP_CompareVirtualMac_HOOKFUNC pfHookFunc:钩子函数
*       Output:
*       Return: 成功则返回VOS_OK，失败则返回其他错误码
*      Caution: 请参考TCPIP_CompareVirtualMac_HOOKFUNC的定义描述
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-01-07   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncCompareVirtualMac(TCPIP_CompareVirtualMac_HOOKFUNC pfHookFunc);

/* 钩子函数原型，实现的功能是:判断地址是否虚地址，是则返回1，否则返回0；
   在入参aucMacAddr不为空时，需返回对应虚地址的虚MAC，否则无需返回，获取虚MAC成功也是返回1，否则返回0；入参地址是网络序 */
typedef ULONG (*TCPIP_IsVipInIf_HOOKFUNC)(ULONG ulIfIndex, ULONG ulIpAddr, UCHAR *aucMacAddr);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncIsVipInIf
* Date Created: 2010-01-07
*       Author: z00104207
*  Description: 注册TCPIP_IsVipInIf_HOOKFUNC钩子函数
*        Input: TCPIP_IsVipInIf_HOOKFUNC pfHookFunc:钩子函数
*       Output:
*       Return: 成功则返回VOS_OK，失败则返回其他错误码
*      Caution: 请参考TCPIP_IsVipInIf_HOOKFUNC的定义描述
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-01-07   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncIsVipInIf(TCPIP_IsVipInIf_HOOKFUNC pfHookFunc);


/* 钩子函数原型，实现的功能是:根据地址来取得与之网段匹配的虚IP对应的虚MAC，用于ARP代理的场景；进行报文发送/转发时，
   对于源IP不是本接口上的地址，但下一跳的地址与接口上的虚IP在同一网段时，报文的源MAC替换为虚MAC；成功则返回0，否则返回非0；
   入参地址是网络序 */
typedef ULONG (*TCPIP_GetVirtualMacByIpAddr_HOOKFUNC)(ULONG ulIfIndex, ULONG ulIpAddr, UCHAR *aucMacAddr);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetVirtualMacByIpAddr
* Date Created: 2010-01-07
*       Author: z00104207
*  Description: 注册TCPIP_GetVirtualMacByIpAddr_HOOKFUNC钩子函数
*        Input: TCPIP_GetVirtualMacByIpAddr_HOOKFUNC pfHookFunc:钩子函数
*       Output:
*       Return: 成功则返回VOS_OK，失败则返回其他错误码
*      Caution: 请参考TCPIP_GetVirtualMacByIpAddr_HOOKFUNC的定义描述
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-01-07   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncGetVirtualMacByIpAddr(TCPIP_GetVirtualMacByIpAddr_HOOKFUNC pfHookFunc);


/* 钩子函数原型，实现的功能是:根据VRF索引和地址，判断指定的地址是否VRF内某个VRRP备份组的虚地址，是则返回1，否则返回0 */
typedef ULONG (*TCPIP_IsVipInVrf_HOOKFUC)(ULONG ulVrfIndex, ULONG ulIpAddr);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncIsVipInVrf
* Date Created: 2010-01-08
*       Author: z00104207
*  Description: 注册TCPIP_IsVipInVrf_HOOKFUC钩子函数
*        Input: TCPIP_IsVipInVrf_HOOKFUC pfHookFunc:钩子函数
*       Output:
*       Return: 成功则返回VOS_OK，失败则返回其他错误码
*      Caution: 请参考TCPIP_IsVipInVrf_HOOKFUC的定义描述
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-01-08   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncIsVipInVrf(TCPIP_IsVipInVrf_HOOKFUC pfHookFunc);


typedef enum tagTCPIP_VRRP_DEBUG
{
    TCPIP_VRRP_DEBUG_IPCLFT      = 0x1,     /* 判断地址与虚IP是否冲突的调试开关 */
    TCPIP_VRRP_DEBUG_CMPVMAC     = 0x2,     /* 比较指定MAC是否虚MAC的调试开关 */
    TCPIP_VRRP_DEBUG_ISVIPINIF   = 0x4,     /* 判断IP是否指定接口的虚IP的调试开关 */
    TCPIP_VRRP_DEBUG_GETVMACBYIP = 0x8,    /* 根据地址获取接口上同网段虚IP对应的虚MAC的调试开关 */
    TCPIP_VRRP_DEBUG_ISVIPINVRF  = 0x10     /* 判断地址是否指定VRF内的虚IP的调试开关 */
}TCPIP_VRRP_DEBUG_E;

/*******************************************************************************
*    Func Name: TCPIP_SetVrrpDebug
* Date Created: 2010-01-09
*       Author: z00104207
*  Description: 设置调用VRRP回调钩子函数时的调试开关
*        Input: ULONG ulDebugFlag: 调试开关取值，取值范围见枚举TCPIP_VRRP_DEBUG_E
*       Output:
*       Return: VOS_OK
*      Caution: 调试开关通过按位与的方式来判断是否生效
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-01-09   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_SetVrrpDebug(ULONG ulDebugFlag);

/*******************************************************************************
*    Func Name: TCPIP_GetVrrpDebug
* Date Created: 2010-01-09
*       Author: z00104207
*  Description: 获取调用VRRP回调钩子函数时的调试开关
*        Input:
*       Output: ULONG *pulDebugFlag: 调试开关取值输出地址，调试开关取值范围见
*                                    枚举TCPIP_VRRP_DEBUG_E
*       Return: 成功则返回VOS_OK，否则返回VOS_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-01-09   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_GetVrrpDebug(ULONG *pulDebugFlag);
/* IPV6规格预配置KEY值,为字符串 */
/* Total number of PMTU entries */
#define PAF_LCS_IPV6_PMTU_SPECS_ENTRIES_NUM                 "PAF_LCS_IPV6_PMTU_SPECS_ENTRIES_NUM"
/* Total number of Neighbor entries */
#define PAF_LCS_IPV6_ND_SPECS_ENTRIES_NUM                   "PAF_LCS_IPV6_ND_SPECS_ENTRIES_NUM"
#define PAF_DHCP6C_SPECS_INTF_PER_CLIENT                    "PAF_DHCP6C_SPECS_INTF_PER_CLIENT"
#define PAF_DHCP6C_SPECS_IA_PER_INTF                        "PAF_DHCP6C_SPECS_IA_PER_INTF"
#define PAF_DHCP6C_SPECS_ADDR_PER_IA                        "PAF_DHCP6C_SPECS_ADDR_PER_IA"
#define PAF_DHCP6R_SPECS_HOP_COUNT                          "PAF_DHCP6R_SPECS_HOP_COUNT"
#define PAF_DHCP6R_ADDR_PER_INTF                            "PAF_DHCP6R_ADDR_PER_INTF"
/* Total number of default router entries per interface */
#define PAF_IP6ND_SPECS_DEFRTR_PER_INTF                     "PAF_IP6ND_SPECS_DEFRTR_PER_INTF"
/* Total number of prefix list entries per interface */
#define PAF_IP6ND_SPECS_PREFLIST_PER_INTF                   "PAF_IP6ND_SPECS_PREFLIST_PER_INTF"
/* Total Number of Destination Cache entries */
#define PAF_IP6ND_SPECS_DESTCACHE_PER_HOST                  "PAF_IP6ND_SPECS_DESTCACHE_PER_HOST"
/* Total number of addresses per interface */
#define PAF_LCS_IPV6_ADDR_ND_SPECS_INF_ADDR_PREFIX_NUM      "PAF_LCS_IPV6_ADDR_ND_SPECS_INF_ADDR_PREFIX_NUM"
/* Total neighbor entries per interface as a percent of total number of neighbor entries in the system */
#define PAF_LCS_IPV6_ND_SPECS_INF_NB_ENTRIES                "PAF_LCS_IPV6_ND_SPECS_INF_NB_ENTRIES"
/* Static neighbor entries per interface, as a percentage of total number of neighbor entries per interface */
#define PAF_LCS_IPV6_ND_SPECS_INF_STATIC_NB_ENTRIES         "PAF_LCS_IPV6_ND_SPECS_INF_STATIC_NB_ENTRIES"
/* Total number of static PMTU entries */
#define PAF_LCS_IPV6_PMTU_SPECS_STATIC_ENTRIES_NUM          "PAF_LCS_IPV6_PMTU_SPECS_STATIC_ENTRIES_NUM"
/* Total number of static neighbor entries */
#define PAF_LCS_IPV6_ND_SPECS_TOT_STATIC_NB_ENTRIES         "PAF_LCS_IPV6_ND_SPECS_TOT_STATIC_NB_ENTRIES"
/* Set MTU range for Gigabye Ethernet */
#define PAF_LCS_IPV6_ADDR_SPECS_GETH_MTU_NUM                "PAF_LCS_IPV6_ADDR_SPECS_GETH_MTU_NUM"


/* IPV6功能预配置KEY值,为字符串 */
/* IPV6基本功能开关 */
#define PAF_LCS_IPV6_BASE_SPECS_ENABLED                     "PAF_LCS_IPV6_BASE_SPECS_ENABLED"
/* 接口自动配置IPV6地址开关 */
#define PAF_LCS_IPV6_ADDR_AUTOCONFIG_SWITCH                 "PAF_LCS_IPV6_ADDR_AUTOCONFIG_SWITCH"

/*******************************************************************************
*    Func Name: TCPIP_Set_PAF_ResValue
* Date Created: 2009-12-15
*       Author: w60786
*  Description: 设置IPV6 PAF规格预配置值
*        Input: CHAR *pucKey: IPV6 PAF规格预配置项KEY值,
*                             取值请参见PAF_LCS_IPV6_BASE_SPECS_ENABLED等宏定义
*               ULONG ulValue: PAF预配置值
*       Output: 
*       Return: VOS_OK: 成功
*               其它: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-15   w60786           Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_Set_PAF_ResValue(CHAR *pcKey, ULONG ulValue);

/*******************************************************************************
*    Func Name: TCPIP_Set_PAF_FunValue
* Date Created: 2009-12-15
*       Author: w60786
*  Description: 设置IPV6 PAF功能预配置值
*        Input: CHAR *pcKey: IPV6 PAF功能预配置项KEY值,
*                            取值请参见PAF_LCS_IPV6_PMTU_SPECS_ENTRIES_NUM等宏定义
*               ULONG ulValue: PAF预配置值
*       Output: 
*       Return: VOS_OK: 成功
*               其它: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-15   w60786           Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_Set_PAF_FunValue(CHAR *pcKey, ULONG ulValue);

/*******************************************************************************
*    Func Name: TCPIP_Show_PAF_Value
* Date Created: 2009-12-15
*       Author: w60786
*  Description: 显示IPV6 PAF信息
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-15   w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_Show_PAF_Value(VOID);


/*******************************************************************************
*    Func Name: TCPIP_SetHDRSchedNum
* Date Created: 2009-07-23
*       Author: zhangchi(00142640)
*  Description: 设置体检报告调度次数
*        Input: ULONG ulHDRSchedNum:调度次数(32~512,默认128)
*       Output:
*       Return: 成功返回VOS_OK,失败返回错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-23   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG TCPIP_SetHDRSchedNum(ULONG ulHDRSchedNum);

/*******************************************************************************
*    Func Name: TCPIP_GetHDRSchedNum
* Date Created: 2009-07-23
*       Author: zhangchi(00142640)
*  Description: 获取体检报告调度次数
*        Input:
*       Output: ULONG* pulHDRSchedNum:体检报告调度次数
*       Return: 成功返回VOS_OK,失败返回错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-23   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG TCPIP_GetHDRSchedNum(ULONG* pulHDRSchedNum);

/*******************************************************************************
*    Func Name: TCPIP_ShowHDRSchedNum
* Date Created: 2009-07-23
*       Author: zhangchi(00142640)
*  Description: 显示体检报告调度次数
*        Input: VOID
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-23   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG TCPIP_ShowHDRSchedNum(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SetLastCompressBuf
* Date Created: 2009-11-16
*       Author: zhangchi(00142640)
*  Description: 设置临终遗言压缩缓存大小
*        Input: ULONG ulMemSize:内存大小
*       Output:
*       Return: 成功返回VOS_OK,失败返回错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-11-16   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG TCPIP_SetLastCompressBuf(ULONG ulMemSize);

/*******************************************************************************
*    Func Name: TCPIP_GetLastCompressBuf
* Date Created: 2009-11-16
*       Author: zhangchi(00142640)
*  Description: 获取临终遗言压缩缓存大小
*        Input:
*       Output: ULONG *pulMemSize:内存大小
*       Return: 成功返回VOS_OK,失败返回错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-11-16   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG TCPIP_GetLastCompressBuf(ULONG *pulMemSize);

/*******************************************************************************
*    Func Name: TCPIP_Compress
* Date Created: 2009-11-13
*       Author: zhangchi(00142640)
*  Description: 数据压缩主函数
*        Input: UCHAR* pcInputData:  待压缩数据首地址
*               ULONG ulInputDataLength:  数据长度
*               UCHAR* pOutputBuffer:压缩后数据首地址
*               ULONG* pulOutputDateLength: 压缩后位数
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-11-13   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG TCPIP_Compress(UCHAR* pcInputData,ULONG ulInputDataLength,UCHAR* pcOutputData,ULONG* pulOutputDateLength);

/*******************************************************************************
*    Func Name: TCPIP_SetSockSchedule
* Date Created: 2009-11-24
*       Author: zhangchi(00142640)
*  Description: 设置SOCK任务事件、报文、定时器调度一定次数释放CPU并延时
*        Input: ULONG ulSwitch:调度次数处理开关
*               ULONG ulTimes: 调度次数
*               ULONG ulDelayTime:达到调度此书后延时时间
*       Output:
*       Return:
*      Caution: 调度次数ulTimes不应太小，ulDelayTime时间不应该设置得太长，否则
*               会影响事件、报文、定时器事件的正常处理
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-11-24   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG TCPIP_SetSockSchedule(ULONG ulSwitch,ULONG ulTimes,ULONG ulDelayTime);

/*******************************************************************************
*    Func Name: TCPIP_GetSockSchedule
* Date Created: 2009-11-24
*       Author: zhangchi(00142640)
*  Description: 获取SOCK任务事件、报文、定时器调度一定次数释放CPU并延时的配置情况
*        Input:
*       Output: ULONG *pulSwitch: 调度次数处理开关
*               ULONG *pulTimes:  调度次数
*               ULONG *pulDelayTime: 调度延时
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-11-24   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG TCPIP_GetSockSchedule(ULONG *pulSwitch,ULONG *pulTimes,ULONG *pulDelayTime);

/*******************************************************************************
*    Func Name: TCPIP_ShowSockSchedule
* Date Created: 2009-12-21
*       Author: zhangchi(00142640)
*  Description: 显示SOCK任务事件、报文、定时器调度一定次数释放CPU并延时的配置情况
*        Input: VOID
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-21   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG TCPIP_ShowSockSchedule(VOID);

/* 获取是否释放CPU的钩子函数 */
typedef ULONG (*CHECK_TASKDELAY_HOOK)(ULONG ulTaskId,ULONG *pulDelayTime);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncCheckTaskDelayHook
* Date Created: 2009-07-22
*       Author: z00104207
*  Description: 注册是否释放CPU的钩子函数
*        Input: CHECK_TASKDELAY_HOOK pfHookFunc: 钩子函数指针
*       Output:
*       Return:
*      Caution: 该钩子函数可注销，传入空指针即注销
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-22   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncCheckTaskDelayHook(CHECK_TASKDELAY_HOOK pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_CheckTaskDelay
* Date Created: 2009-12-21
*       Author: zhangchi(00142640)
*  Description: 根据任务ID判断是否释放CPU函数
*        Input: ULONG ulTaskId:任务ID
*               ULONG *pulDelayTime:延时时间
*       Output:
*       Return: VRP_YES:需要释放CPU,VRP_NO:不需要释放CPU
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-21   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG TCPIP_CheckTaskDelay(ULONG ulTaskId,ULONG *pulDelayTime);

/*******************************************************************************
*    Func Name: TCPIP_HA_EventNotify
* Date Created: 2010-05-17
*       Author: z00104207
*  Description: 供产品调用，通知VISP处理HA事件
*        Input: ULONG ulMsgType: 事件类型
*       Output:
*       Return: 成功则返回VOS_OK，否则返回其他错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-05-17   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_HA_EventNotify(ULONG ulEventType);

/*******************************************************************************
*    Func Name: TCPIP_SetLogOutputMod
* Date Created: 2010-07-07
*       Author: mafeng59090
*  Description: 设置日志输出模式(是否使用VISP的INFO任务输出)
*        Input: ULONG ulMod:0:异步模式(使用INFO任务)，1:同步模式
*       Output: 
*       Return: VOS_ERR/VOS_OK
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-07-07   mafeng59090             Create
*
*******************************************************************************/
extern ULONG TCPIP_SetLogOutputMod(ULONG ulMod);

/*******************************************************************************
*    Func Name: TCPIP_GetLogOutputMod
* Date Created: 2010-07-07
*       Author: mafeng59090
*  Description: 获取VISP日志信息输出模式
*        Input: ULONG *pulMod:
*       Output: 日志输出模式
*       Return: PUBLIC_ERR_PARA_ERR/VOS_OK
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-07-07   mafeng59090             Create
*
*******************************************************************************/
extern ULONG TCPIP_GetLogOutputMod(ULONG *pulMod);

/*******************************************************************************
*    Func Name: TCPIP_AddVlanHead
* Date Created: 2008-03-29
*       Author: mafeng(59090)
*  Description: 增加VLAN字段
*        Input: MBUF_S *pMBuf:报文MBUF指针
*               ULONG ulVlanHead:VLAN字段(主机序)
*       Output:
*       Return: OPTIM_OK:处理成功
*               OPTIM_ERR:处理失败，释放报文
*      Caution: 丢弃报文(释放)不增加ETH控制块统计信息
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-29   mafeng(59090)           Create-123456789
*
*******************************************************************************/
extern ULONG TCPIP_AddVlanHead(MBUF_S *pMBuf, ULONG ulVlanHead);


/*******************************************************************************
*    Func Name: TCPIP_RegFuncHATaskDelayHook
* Date Created: 2011-03-02
*       Author: zKF23859
*  Description: 注册HA中是否释放CPU的钩子函数
*        Input: CHECK_TASKDELAY_HOOK pfHookFunc: 钩子函数指针
*       Output:
*       Return: 成功则返回VOS_OK，否则返回其他错误码
*      Caution: 该钩子函数可注销，传入空指针即注销
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-03-02   zKF23859               Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncHATaskDelayHook(CHECK_TASKDELAY_HOOK pfHookFunc);


/*******************************************************************************
*    Func Name: TCPIP_HA_SetDelaySetting
* Date Created: 2011-03-02
*       Author: zKF23859
*  Description: 设置HA任务的延时开关,时间,包数
*        Input: ULONG ulHADelaySwitch  延时选择开关1--设置延时0---钩子延时
*               ULONG ulDelayTime     延迟时间
*               ULONG ulDelayPacket       包后延数
*       Output:
*       Return: VOS_OK 设置正确,其他失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-03-02   zKF23859               Create
*
*******************************************************************************/
extern ULONG TCPIP_HA_SetDelaySetting(ULONG ulHADelaySwitch, ULONG ulDelayTime, ULONG ulDelayPacket);

/*******************************************************************************
*    Func Name: TCPIP_HA_GetDelaySetting
* Date Created: 2011-03-02
*       Author: zKF23859
*  Description: 获取HA任务设置的延时开关,时间,包数
*        Input:
*       Output: ULONG *pulDelaySwitch  延迟选择开关
*               ULONG pulDelayTime     延迟时间
*               ULONG pulDelayPacket   包后延时:
*       Return: VOS_OK获取正确,其他失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-03-02   zKF23859               Create
*
*******************************************************************************/
extern ULONG TCPIP_HA_GetDelaySetting(ULONG *pulDelaySwitch, ULONG *pulDelayTime, ULONG *pulDelayPacket);



/*******************************************************************************
*    Func Name: TCPIP_ShowHADelaySetting
* Date Created: 2011-03-02
*       Author: zKF23859
*  Description: 显示HA任务设置的延时开关,时间,包数,钩子地址
*        Input:
*       Output
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-03-02   zKF23859               Create
*
*******************************************************************************/
extern VOID TCPIP_ShowHADelaySetting(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SetSockRateTime
* Date Created: 2011-05-16
*       Author: luogaowei61496
*  Description: 设置SOCK 运行时间和释放CPU时间参数来调整SOCK 任务CPU占用比例
*        Input: ULONG ulSwitch:开关(1表示打开，0表示关闭)
*               ULONG ulRunTime:SOCK一次运行占用时间(0表示取默认值40ms)
*               ULONG ulFreeTime:SOCK运行一次后释放CPU时间(0表示取默认值40ms)
*       Output: 
*       Return: VOS_OK或者错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-05-16   luogaowei61496          Create
*
*******************************************************************************/
extern ULONG TCPIP_SetSockRateTime(ULONG ulSwitch, ULONG ulRunTime, ULONG ulFreeTime);

/*******************************************************************************
*    Func Name: TCPIP_GetSockRateTime
* Date Created: 2011-05-16
*       Author: luogaowei61496
*  Description: 获取SOCK运行时间和释放CPU时间参数
*        Input: 
*       Output: ULONG *pulSwitch:开关
*               ULONG *pulRunTime:SOCK一次运行占用时间
*               ULONG *pulFreeTime:SOCK运行一次后释放CPU时间
*       Return: VOS_OK或者错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-05-16   luogaowei61496          Create
*
*******************************************************************************/
extern ULONG TCPIP_GetSockRateTime(ULONG *pulSwitch, ULONG *pulRunTime, ULONG *pulFreeTime);

/* Add by shuxieliu00176784, at 2011-08-31. 修改原因:  DTS2011083101231
   SGSN需求: 新增钩子函数，在上报告警前，查询是否可以处理告警。返回值: True(上报), False(不用上报) */
typedef LONG  (*TCPIP_IsNeedWarning_HOOK_FUNC)(ULONG ulWarningID, VOID *pWarnParam);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncIsNeedWarningHook
* Date Created: 2011-08-31
*       Author: shuxieliu00176784
*  Description: DTS2011083101231 SGSN需求 注册钩子函数:在上报告警前，查询是否可以处理告警
*        Input: TCPIP_IsNeedWarning_HOOK_FUNC pfHookFunc: 钩子函数
*       Output: 
*       Return: VOS_OK成功,其他返回失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-08-31   shuxieliu00176784       Create the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_RegFuncIsNeedWarningHook(TCPIP_IsNeedWarning_HOOK_FUNC pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_HA_SetKeepalive
* Date Created: 2012-09-03
*       Author: MaFeng59090
*  Description: 设置HA保活探测超时倍数
*        Input: ULONG ulDetectThr:超时倍数[1-20]
*       Output: 无
*       Return: 成功/失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-03   MaFeng59090             Create
*
*******************************************************************************/
extern ULONG TCPIP_HA_SetKeepalive(ULONG ulDetectThr);

/*******************************************************************************
*    Func Name: TCPIP_HA_GetKeepalive
* Date Created: 2012-09-03
*       Author: MaFeng59090
*  Description: 获取设置的HA保活探测倍数
*        Input: ULONG *pulDetectThr:探测倍数指针
*       Output: 探测倍数
*       Return: 成功/失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-03   MaFeng59090             Create
*
*******************************************************************************/
extern ULONG TCPIP_HA_GetKeepalive(ULONG *pulDetectThr);

/*******************************************************************************
*    Func Name: TCPIP_HA_EnableDetect
* Date Created: 2012-09-07
*       Author: MaFeng59090
*  Description: 产品启动或停止HA保活探测功能
*        Input: ULONG ulStart:1:启动,0:停止
*       Output:
*       Return: VOS_ERR/VOS_OK
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-07   MaFeng59090             Create
*
*******************************************************************************/
extern ULONG TCPIP_HA_EnableDetect(ULONG ulStart);

/*******************************************************************************
*    Func Name: TCPIP_HA_GetDetect
* Date Created: 2012-09-07
*       Author: MaFeng59090
*  Description: 获取当前是否启动了HA保活探测功能
*        Input: ULONG *pulStart:当前HA保活探测的状态
*       Output:
*       Return: VOS_ERR/VOS_OK
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-07   MaFeng59090             Create
*
*******************************************************************************/
extern ULONG TCPIP_HA_GetDetectState(ULONG *pulState);


typedef ULONG  (*TCPIP_TaskExceptionHandlerFunc)(VOID);   /*任务监视异常处理函数*/
typedef ULONG  (*TCPIP_TaskIdGetThreadHook)(ULONG ulTaskId);/*用于任务ID转换成threadid 的回调函数*/

/* 注册需要监视的任务,
   ulThreadId: PthreadID，
   ulMaxSec: 任务未被调度的最大间隔（单位为秒），不能为0
   pfHandler:被监视任务未被调度达到门限值的处理函数，NULL表示采用默认处理(复位进程)，
*/
typedef ULONG (*TCPIP_RegMonitorTaskFunc)(ULONG ulThreadId, ULONG ulMaxSec, TCPIP_TaskExceptionHandlerFunc pfHandler);

/* 被监视任务定时调用此接口上报心跳 */
typedef VOID   (*TCPIP_TaskHeartbeatFunc)(VOID);

typedef struct tagTCPIPTaskMonitorPARA
{
    TCPIP_TaskIdGetThreadHook pfGetThreadIdFunc;   /*用于任务ID转换成threadid 的回调函数*/
    TCPIP_RegMonitorTaskFunc   pfRegTaskFunc;      /*注册需要监视的任务*/
    TCPIP_TaskHeartbeatFunc    pfHeartbeatFunc;    /*产品注册给VISP的心跳函数*/
}TCPIP_TASK_MONITOR_PARA_S;
/*********************************全局变量定义********************************/

/*************************************************************************
Function     : TCPIP_RegTaskMonitorFuncHook
Description  : 提供给产品注册任务监视函数，任务监视机制由产品实现
Input        : pfHookFunc: 任务监视接口
Output       :
Return       : 0--成功，非0--失败
Create By    :
Modification :
Restriction  :
*************************************************************************/
ULONG TCPIP_RegTaskMonitorFuncHook(TCPIP_TASK_MONITOR_PARA_S *pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_SetSockCpuScheTimeWay
* Date Created: 2014-05-28
*       Author: l00213099
*  Description: 设置SOCK任务获取时间方式开关
*        Input: ULONG ulSwitch:调度次数处理开关
*                              默认0- VOS_TmNow
*                                  1- VOS_GetCpuTick
*       Output:
*       Return:
*      Caution: 传送网USP平台,VOS_TmNow获取的时间由任务刷新,对于不可抢占的SOCK
*               任务获取的时间将不准,所以提供VOS_GetCpuTick方式获取时间
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-12-17   Create
*
*******************************************************************************/
ULONG TCPIP_SetSockCpuScheTimeWay(ULONG ulSwitch);

/*******************************************************************************
*    Func Name: TCPIP_GetSockCpuScheTimeWay
* Date Created: 2014-05-28
*       Author: l00213099
*  Description: 获取SOCK任务获取时间方式开关
*        Input: 
*       Output: ULONG *pulSwitch:调度次数处理开关
*                               默认0- VOS_TmNow
*                                  1- VOS_GetCpuTick
*       Return:
*      Caution: 传送网USP平台,VOS_TmNow获取的时间由任务刷新,对于不可抢占的SOCK
*               任务获取的时间将不准,所以提供VOS_GetCpuTick方式获取时间
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-12-17   Create
*
*******************************************************************************/
ULONG TCPIP_GetSockCpuScheTimeWay(ULONG* pulSwitch);

ULONG TCPIP_SetShutIFFlagForVRFChange(ULONG ulShutFlag);

/*******************************************************************************
*    Func Name: TCPIP_SetTcpPrecisionSwitch
* Date Created: 2015-08-26
*       Author: wangbin
*  Description: 设置TCP 2MSL时间精度开关
*        Input: ulSwitch  : 开关值
*       Output: NA
*       Return: VOS_ERR  失败
*               	VOS_OK 成功
*      Caution: 该接口主要场景应用系统提供的软超时定时器不精准场景下
*(主要指系统休眠时，软定时器未补偿休眠时间或休眠醒来时软定时器已超时无法补偿问题)
*目前终端手机下由于功耗KPI指标，经常出现该场景
* *
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2015-08-26   Create
*
*******************************************************************************/
ULONG TCPIP_SetTcpPrecisionSwitch(ULONG ulSwitch);

/*******************************************************************************
*    Func Name: TCPIP_GetTcpPrecisionSwitch
* Date Created: 2015-08-26
*       Author: wangbin
*  Description: 获取TCP 2MSL时间精度开关
*        Input:  NA
*       Output: pulSwitch :开关值指针
*       Return: VOS_ERR  失败
*               	VOS_OK 成功
*      Caution: s
* *
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2015-08-26   Create
*
*******************************************************************************/
ULONG TCPIP_GetTcpPrecisionSwitch(ULONG *pulSwitch);


#ifdef  __cplusplus
}
#endif

#endif

