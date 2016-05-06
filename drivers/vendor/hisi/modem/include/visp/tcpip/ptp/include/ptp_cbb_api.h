/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptp_cbb_api.h
*
*  Project Code: IPCLOCK SERVER V100R002
*   Module Name: PTP api
*  Date Created: 2008-05-15
*        Author: lishenchuan
*   Description: 主要提供给产品以及CBB自己调用
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-05-15      lishenchuan       Create
*  2008-06-26      lishenchuan       modify the default and the range of
*                                    logAnnounceInterval    default:1      range: -3 to 3
*                                    logSycInterval         default:-4     range: -7 to 1
*                                    logMinDelayInterval    default:-4     range: -7 to 6
*                                    logMinPdelayInterval   default:-4     range: -7 to 6
*                                    RecipteTimeOut         default: 3     rangge  2 to 255
*  2008-12-17      wangchengyang     合入visp主线版本，整改头文件
*******************************************************************************/

#ifndef __ptp__cbb__api__h__
#define __ptp__cbb__api__h__

#ifdef __cplusplus
extern "C" {
#endif

/*定义ClockIdentity长度*/
#define PTP_CLOCK_ID_LEN                8

/* 事件消息UDP端口号 */
#define PTP_EVENT_PORT                  319

/* 普通消息UDP端口号 */
#define PTP_GENERAL_PORT                320

/*定义PTP模块支持的端口数规格*/
#define PTP_SUPPORT_PORT_NUMBER         2

/* PTP多播目的主地址，主机序:224.0.1.129,All except peer delay mechanism messages */
#define PTP_PRIMARY_MULTICAST_IP        0xE0000181L

/* PTP-Pdelay多播目的地址，主机序，该地址现在不用:224.0.0.107,Peer delay mechanism messages */
#define PTP_PDELAY_MULTICAST_IP         0xE000006BL

/*定义单播Master列表长度总规格*/
#define PTP_UNICAST_MASTR_LEN           5

/*定义ACCEPTABLE Master列表长度规格*/
#define PTP_ACCEPT_MASTR_LEN            2


#define PTPIF_MAX_VLAN_ID        4094
#define PTPIF_MIN_VLAN_ID        1

/* Master端设置最大地址个数 */
/* Modified by dutianyi00217007 2014-1-17 支持PTP端口地址扩展 */
#define PTP_MAX_IP_NUM         48
#define PTP_DEFAULT_IP_NUM     1

/* Slave 侧 配置VRF最大数量 */
#define PTP_MAX_VRF_NUM         5

/*Added by luogaowei 2013-4-7 支持1588 16.1可选需求

注意: PTP_NEGO_MODE_DURATION;必须保证宏值和PTP_KEEP_ALIVE_MODE_NEW 相同
*/
#define PTP_NEGO_MODE_NO_DURATION   0   /*PTP 的协商模式: 无duration ,即早期1588草案*/
#define PTP_NEGO_MODE_DURATION      1   /*PTP 的协商模式: 有duration ,即1588v2的可选16.1 、G8265.1*/
#define PTP_BMC_MODE_IEEE_1588      0   /*选源算法: 1588标准 */
#define PTP_BMC_MODE_ITU_G82651     1   /*选源算法: 8265.1标准*/
/*End by luogaowei 2013-4-7*/

/*Added by luogaowei 2013-4-7 支持1588 16.1可选需求
  定义几个标记 用于PTP_SetNegoAndBmcSplitMode 和PTP_SetKeepAliveMode配置互斥*/
#define PTP_MODE_API_FLAG_INIT      0
#define PTP_MODE_API_FLAG_KEEPVLIE  1
#define PTP_MODE_API_FLAG_SPLIT     2
/*End by luogaowei 2013-4-7*/

/*Added by dutianyi 2014-05-07 for DTS2014050703927 产品授权前，标识当前基站是否已存在于slave列表*/
#define PTP_SLAVE_ALREADY_EXIST 1
#define PTP_SLAVE_NOT_EXIST 0

/*错误码定义*/
typedef enum tagPTP_ERR_E
{
    PTP_OK =0,
    PTP_ERR,
    PTP_ERR_NULL,                      /* 2.指针为空错误 */
    PTP_ERR_CLOCK_UNINIT,              /* 3.时钟实体未初始化 */
    PTP_ERR_CLOCK_ACCURACY,            /* 4.时钟精度范围不合法 */
    PTP_ERR_LEAP_CONFLIT,              /* 5.时间leap冲突 */
    PTP_ERR_PORT_NUMBER,               /* 6.端口号不正确 */
    PTP_ERR_PORT_ADDR,                 /* 7.端口地址无效 */
    PTP_ERR_MAX_SIZE,                  /* 8.超过最大范围 */
    PTP_ERR_ALREADY_EXIST,             /* 9.该节点已经存在 */
    PTP_ERR_NOT_FOUND,                 /* 10.未找到该节点 */
    PTP_ERR_DELAY_MACHENISM,           /* 11.延时机制设置错误 */
    PTP_ERR_PORT_UNVALID,              /* 12.端口无效 */
    PTP_ERR_MEMORY,                    /* 13.内存分配失败 */
    PTP_ERR_INTERUPT,                  /* 14.关中断失败 */
    PTP_ERR_STATE_UNICAST,             /* 15.单播协商标记位状态出错 */
    PTP_ERR_FSM_EVENT_TYPE_ERR,        /* 16.状态机事件类型输入错误*/
    PTP_ERR_CLKTYPE,                   /* 17.时钟类型非法 */
    PTP_ERR_SOFTMODE,                  /* 18.软件类型非法，不为纯软或者纯软+FPGA架构 */
    PTP_ERR_SOCKET_INIT,               /* 19.socket初始化失败 */
    PTP_ERR_GET_SYSINFO,               /* 20.获取系统信息失败 */
    PTP_ERR_SET_ASYNSOCKET,            /* 21.设置socket异步属性失败 */
    PTP_ERR_MSGTYPE,                   /* 22.报文类型非法 */
    PTP_ERR_PACKET_BUFFER,             /* 23.报文缓存为空 */
    PTP_ERR_PACKET_LEN,                /* 24.报文长度非法 */
    PTP_ERR_SETMULTICAST,              /* 25.设置多播socket失败 */
    PTP_ERR_PACKET,                    /* 26.报文内容非法 */
    PTP_ERR_MASTER_NOTEXIST,           /* 27.不在单播master表/可接受master列表中 */
    PTP_ERR_DELAY_INTERVAL,            /* 28.delay延时间隔设置不合法 */
    PTP_ERR_CLOCK_FSM_MODE,            /* 29.时钟状态机模式错误 */
    PTP_ERR_ANN_INTERVAL,              /* 30.announce消息间隔设置错误 */
    PTP_ERR_SYNC_INTERVAL,             /* 31.sync消息间隔设置错误 */
    PTP_ERR_SYNC_MODE,                 /* 32.时间/频率同步设置错误 */
    PTP_ERR_CAST_MODE,                 /* 33.单播/多播模式设置错误 */
    PTP_ERR_TIME_SOURCE,               /* 34.时间源设置错误 */
    PTP_ERR_SEQUENCEID,                /* 35.报文序列号非法 */
    PTP_ERR_PORTNOTFIND,               /* 36.根据目的IP未找到时钟端口 */
    PTP_ERR_ACPTMSTR_NOTENABLE,        /* 37.可接受master表没有使能 */
    PTP_ERR_ANNOUNCE,                  /* 38.announce消息非法 */
    PTP_ERR_PORTSTATE,                 /* 39.端口状态错误，此时不能接收和发送报文 */
    PTP_ERR_MALLOC,                    /* 40.申请内存错误 */
    PTP_ERR_SLAVE_NOTEXIST,            /* 41.不在单播slave列表中 */
    PTP_ERR_TLVTYPE,                   /* 42.tlv类型非法 */
    PTP_ERR_DEV_NOTHUAWEI,             /* 43.对端不是华为设备，在扩展tlv处理时用 */
    PTP_ERR_DSCP_PRIORITY,             /* 44.DSCP值非法 */
    PTP_ERR_CLOSESOCKET,               /* 45.关闭socket */
    PTP_ERR_CREATESOCKET,              /* 46.创建socket失败 */
    PTP_ERR_SET_SOCKETOPTION,          /* 47.设置socket属性失败 */
    PTP_ERR_BINDSOCKET,                /* 48.绑定socket失败 */
    PTP_ERR_RECVPKT,                   /* 49.socket接收报文失败 */
    PTP_ERR_RECVMSG,                   /* 50.socket接收辅助数据失败 */
    PTP_ERR_SOCKETID,                  /* 51.socket id非法 */
    PTP_ERR_SOCKET_MSGTYPE,            /* 52.socket异步消息非法 */
    PTP_ERR_SND_GENERALPKT,            /* 53.socket报文发送失败 */
    PTP_ERR_IP_NOT_EXIST,              /* 54.源地址不在本机 */
    PTP_ERR_CLRSOCKETMULTICAST,        /* 55.清除多播选项 */
    PTP_ERR_GET_PORTADDR,              /* 56.获取地址非法 */
    PTP_ERR_VERSION,                   /* 57.PTP version非法 */
    PTP_ERR_DOMAINNUMBER,              /* 58.domain number非法 */
    PTP_ERR_FLAGFIELD,                 /* 59.flag field非法 */
    PTP_ERR_PORTID,                    /* 60.时钟id非法 */
    PTP_ERR_ORGSUBTYPE,                /* 61.OrganizationSubType非法 */
    PTP_ERR_EXTEN_EVENT,               /* 62.外部事件错误 */
    PTP_ERR_WRITEQUE_FAIL,             /* 63.写队列失败 */
    PTP_ERR_NOT_SUPP_BC,               /* 64.PTP CBB不支持BC节点*/
    PTP_ERR_DEV_TYPE,                  /* 65.PTP 设备类型非法*/
    PTP_ERR_CREATE_QUEUE,              /* 66.PTP 创建队列错误*/
    PTP_ERR_CREATE_TIMER,              /* 67.PTP 创建定时器错误*/
    PTP_ERR_CREATE_TASK,               /* 68.PTP 创建任务错误*/
    PTP_ERR_FSM_STATE,                 /* 69.PTP 状态机状态错误*/
    PTP_ERR_RECOMD_STATE,              /* 70.PTP 推荐状态错误*/
    PTP_ERR_UNIMASTER_NOT_VALID,       /* 71.PTP 单播Master无效*/

    PTP_ERR_DONT_PROCMSG,              /* 72.不处理消息*/
    PTP_ERR_MASTR_NOT_IN_UNICASTM_TAB, /* 73.Master不在单播Mst表中 */
    PTP_ERR_MASTR_NOT_IN_ACCEPTM_TAB,  /* 74Mst不在可接受Mst表中 */
    PTP_ERR_ITEM_EXIST,                /* 75.表项不存在*/
    PTP_ERR_TAB_FULL,                  /* 76.表项为空*/
    PTP_ERR_LOGIC_TIMER_OVER,          /* 77.逻辑定时器规格满*/
    PTP_ERR_LOGIC_TIMER_FUNC_NULL,     /* 78.传如逻辑定时器的函数指针为空*/
    PTP_ERR_LOGIC_TIMER_MALLOC_FAIL,   /* 79.逻辑定时器MALLOC失败*/
    PTP_ERR_LOGIC_TIMERID_NULL,        /* 80.逻辑定时器Id为空*/


    PTP_ERR_PROF_NOTSUPPORT,           /* 81.不支持该协议模板*/
    PTP_ERR_BMC_PARAM ,                /* 82.选源参数非法 */
    PTP_ERR_BMC_MASTER_INVALID,        /* 83.Master无效 */
    PTP_ERR_BMC_MASTER_NOT_UP,         /* 84.Master没有up */
    PTP_ERR_BMC_NO_MASTER,             /* 85.没有master可选 */
    PTP_ERR_ANN_NOTPROC,               /* 86.不处理announce报文 */

    PTP_ERR_PROTOCAL,                   /* 87.协议错误*/
    PTP_ERR_TIMEOUT_SCALE,              /* 88.timer scale非法*/
    PTP_ERR_LOGIC_TIMER_NUM_ZERO,       /* 89.逻辑定时器数为0*/
    PTP_ERR_LOGIC_TIMER_POINTER_INVALID,/* 90.逻辑定时器指针无效*/
    PTP_ERR_UNICASTFLAG,                /* 91.flagfiel域unicastflag非法 */
    PTP_ERR_ALTERNATE_MASTERFLAG,       /* 92.flagfiel域alternate mastter flag非法 */

    PTP_ERR_GROUPWARE_FALSE,            /* 93.组件指针未打开*/
    PTP_ERR_CREATE_MUTEX_FAILED,        /* 94.创建PTP组件的信号量失败 */
    PTP_ERR_SND_EVENTPKT,               /* 95.发送event消息失败 */
    PTP_ERR_MAX_CFG_SIZE,               /* 96.配置规格超过最大值 */
    PTP_ERR_NEGO_STATE_INCORRECT,       /* 97.单播协商状态机状态不正确、不合适 */
    PTP_ERR_UNIMASTER_RUN_TAB_NULL,     /* 98.单播Master运行表为空或未创建 */
    PTP_ERR_REFUSEGRANT,                /* 99.不同意授权*/
    PTP_ERR_BMC_SELECT_MODE,            /* 100.选源模式输入错误 */
    PTP_ERR_SLAVETABLE_FULL,            /* 101 单播SLAVE列表规格大于10000*/
    PTP_ERR_LIVE_INTERVAL,              /* 102 Keep alive 间隔值非法 */
    PTP_ERR_MODE_INTERVAL,              /* 103 模式错误  */
    PTP_ERR_RECEIPT_TIMEOUT,            /* 104 receipt time out次数非法 */
    PTP_ERR_DEBUG_SWITCH,               /* 105 debug类型非法 */
    PTP_ERR_NULL_P,                     /* 106 输入参数为空(端口号) */
    
    PTP_ERR_MAC_NOT_CFG,                /* 107 physical地址没有配置 */
    PTP_ERR_INTF_NOT_EXIST,             /* 108 适合physical地址的接口不存在 */
    PTP_ERR_CREATE_MBUF,                /* 109 创建Mbuf失败 */
    PTP_ERR_PREPEND_MEM_SPACE,          /* 110 扩展内存空间失败 */
    PTP_ERR_INVALID_ENCAP_TYPE,         /* 111 无效以太封装类型 */
    
    /*Add By t00110672/z00146309  10-1-11,支持路由器关于实现最新草案的需求 */
    PTP_ERR_DURATION_FIELD_INVALID, /*112 无效的发包时长*/
    PTP_ERR_STEPFLAG_SCOPE,         /*113 错误的STEP标记位*/
    PTP_ERR_PARA_INVALID,           /*114 参数错误，*/
    PTP_ERR_INVALID_VLANID,         /*115 错误的VLan id*/
    /*Add By t00110672 For BC3D02767,【TD产品需求】【PTP】实现1588无线选源方案优化*/
    PTP_ERR_BMC_NO_PRI_CLOCK_SOURCE,/* 116 没有可优选的参考源*/
    
    /*Add By z00146309 For DTS2010080400862 ,slave侧配置keeplive为老模式，不允许重新启动单播协商。 */
    PTP_ERR_ALIVE_MODE,/* 117 当KEEPALIVE是旧模式时，是不允许再次调用重协商接口的*/
    /*Added by zhangbo146309, 层三多播零地址适应, 2010/8/20 */
    PTP_ERR_GET_IFINDEXGP,/* 118 获取接口索引组失败*/
    PTP_ERR_SET_MULTISOCK_OPTION,/* 119 设计多播SOCKET选项失败*/
    PTP_ERR_GET_IPV6_CMP_FAIL, /*120 获取IPv6地址模块组建失败*/
    PTP_ERR_IPV6_UNENABLE,  /*121 PTP IPV6未使能(未设置预配值)*/
    PTP_ERR_SET_SOCKET_IOCTL, /*122 设置socket IOCTL失败*/
    PTP_ERR_PORT_ADDR_STATE, /*123 slave状态下仅允许配置允许配置一种类型地址*/
    PTP_ERR_PROFILE_MODE,               /* 124 profile mode error */
    PTP_ERR_BMC_LOCAL_ClASS,            /* 125 local class is better than master,only use at BMC */
    PTP_ERR_API_USAGE,                  /* 126 Wrong usage of API - Please check the API Description*/
    
    PTP_ERR_IPADDR,    /*127 add unicast master cann't add 0 addr*/
    PTP_ERR_IPSCOPE,     /*128 unicast master can't be the multi address*/
    PTP_ERR_INVALID_VLANPRI,         /*129 错误的VLan 优先级*/
    PTP_ERR_NO_SUCH_MASTER_ADDR,     /* 130 无效/未配置的master地址 */
    PTP_ERR_IS_NOT_MASTER,           /* 131 本clock 非master, 只针对master的API不可操作 */
    PTP_ERR_WRONG_PROTOCAL,          /* 132 协议号错误 */
    PTP_ERR_WRONG_LIMIT_IP_NUM,      /* 133 错误的最大IP数量范围,超过最大限制 */
    PTP_ERR_IP_LIMIT_LT_EXIST,       /* 134 设置的ip数量限制值比已经存在IP数还小 */
    PTP_ERR_ADDR_FULL,               /* 135 地址已经达到最大限制 */
    PTP_ERR_ADDR_ALREADY_EXIST,      /* 136 增加地址，但地址已经存在 */
    PTP_ERR_SET_ADDRESS_FAILED,      /* 137 增加地址失败 */
    PTP_ERR_DEST_IP_NOT_EXIST,       /* 138 接受报文目的ip不在配置列表中 */
    PTP_ERR_NO_PORT_ADDR,            /* 139 没有配置地址 */

    /* 149-200 用于VRF相关 */
    PTP_ERR_VRF_NO_CONFIG = 149,     /* 149 没有找到VRF */
    PTP_ERR_VRF,                     /* 150 VRF错误 */
    PTP_ERR_VRF_ADDR_FULL,           /* 151 vrf地址 已满 */
    PTP_ERR_VRF_ADDR_EXIST,          /* 152 VRF地址 已存在 */
    PTP_ERR_VRF_ADDR_NULL,           /* 153 vrf地址 不存在 */
    PTP_ERR_VRF_FULL,                /* 154 VRF已经规格已满 */
    PTP_ERR_VRF_EXIST,               /* 155 VRF已经存在 */
    PTP_ERR_VRF_NULL,                /* 156 VRF不存在 */
    PTP_ERR_VRF_ONE_ADDR_ONE_VRF,    /* 157 1个VRF下只一个端口地址 */
    PTP_ERR_VRF_MORE_ADDR_ONE_VRF,   /* 158 1个VRF下存在了多个端口地址 */
    PTP_ERR_VRF_DEFAULT_FOBBIDEN,    /* 159 默认VRF不可使用 */
    PTP_ERR_VRF_NOT_MATCH,           /* 160 收到报文VRF与本地VRF id不匹配 */
    PTP_ERR_VRF_INUSE,               /* 161 该vrf被UnicastMaster使用中 */
    PTP_ERR_VRF_ADDR_ONE,            /* 162 slave 端每个port只允许配置一个本端地址*/
    /* end of VRF 相关 */
    PTP_ERR_NOT_NEED_DOFSM,          /* 163 不需要选源操作 */
    PTP_ERR_DURATION_PRECENT_INVALID, /*164 设定Duration重协商时间(相对Duration百分比)无效*/
    PTP_ERR_WRITEVENT_FAIL,           /*165 写事件失败 */
    PTP_ERR_NEGO_AND_BMC_SPLIT_MODE,  /*166 错误的协商和选源分离模式*/
    PTP_ERR_INVALID_MASTER_CLASS,     /*167 错误的master class,不在80-110范围或者对应的QL为0*/
    PTP_ERR_OTHER_PTP_USED,           /*168 其他版本的PTP模块已在使用中*/
    PTP_ERR_BMC_G82751_ERRNO1,        /*169 按G8275.1标准选源出错，ForeMaster与本端的时钟Id一样*/
    PTP_ERR_BMC_G82751_ERRNO2,        /*170 按G8275.1标准选源出错，多个ForeMaster的时钟Id一样*/
    PTP_ERR_MAX                       /* 错误码最大值，后续要添加都添加在这之前 */
}PTP_ERR_E;

/*定义时钟设备类型枚举*/
typedef enum tagPTP_DEV_TYPE_E
{
    PTP_DEV_TYPE_OC =0,     /*0  OC*/
    PTP_DEV_TYPE_E2ETC,     /*1  E2ETC */
    PTP_DEV_TYPE_P2PTC,     /*2  P2PTC */
    PTP_DEV_TYPE_OC_E2ETC,  /*3  OC + E2ETC */
    PTP_DEV_TYPE_OC_P2PTC,  /*4  OC + P2PTC */
    PTP_DEV_TYPE_BC,        /*5  BC 目前不支持，为保留*/
    PTP_DEV_TYPE_END
}PTP_DEV_TYPE_E;

/*定义时钟组件的软件模式*/
typedef enum tagPTP_SOFT_MODE_E
{
    PTP_SOFT_MODE_ALLSOFT = 0,    /* 纯软模式 */
    PTP_SOFT_MODE_SOFTFPGA,       /* PTP管理，FPGA同步模式 */
    PTP_SOFT_MODE_END
}PTP_SOFT_MODE_E;


/* 定义协议枚举类型 */
typedef enum tagPTP_PROTOCAL_TYPE_E
{
    PTP_PROTOCAL_UDP_IPV4 = 1,
    PTP_PROTOCAL_UDP_IPV6,
    PTP_PROTOCAL_IEEE_802,
    PTP_PROTOCAL_DEVICE_NET,   /*不使用*/
    PTP_PROTOCAL_CONTROL_NET,  /*不使用*/
    PTP_PROTOCAL_PROFI_NET     /*不使用*/
}PTP_PROTOCAL_TYPE_E;

/* 时间精度枚举定义 */
typedef enum tagPTP_CLOCK_ACCURACY_E
{
    PTP_CLOCK_ACCURACY_25NS = 0X20, /*The time is accurate to within 25 ns*/
    PTP_CLOCK_ACCURACY_100NS,       /*The time is accurate to within 100 ns*/
    PTP_CLOCK_ACCURACY_250NS,       /*The time is accurate to within 250 ns*/
    PTP_CLOCK_ACCURACY_1US,         /*The time is accurate to within 1 us*/
    PTP_CLOCK_ACCURACY_2P5US,       /*The time is accurate to within 2.5 us*/
    PTP_CLOCK_ACCURACY_10US,        /*The time is accurate to within 10 us*/
    PTP_CLOCK_ACCURACY_25US,        /*The time is accurate to within 25 us*/
    PTP_CLOCK_ACCURACY_100US,       /*The time is accurate to within 100 us*/
    PTP_CLOCK_ACCURACY_250US,       /*The time is accurate to within 250 us*/
    PTP_CLOCK_ACCURACY_1MS,         /*The time is accurate to within 1 ms*/
    PTP_CLOCK_ACCURACY_2P5MS,       /*The time is accurate to within 2.5 ms*/
    PTP_CLOCK_ACCURACY_10MS,        /*The time is accurate to within 10 ms*/
    PTP_CLOCK_ACCURACY_25MS,        /*The time is accurate to within 25 ms*/
    PTP_CLOCK_ACCURACY_100MS,       /*The time is accurate to within 100 ms*/
    PTP_CLOCK_ACCURACY_250MS,       /*The time is accurate to within 250 ms*/
    PTP_CLOCK_ACCURACY_1S,          /*The time is accurate to within 1 s*/
    PTP_CLOCK_ACCURACY_10S,         /*The time is accurate to within 10 s*/
    PTP_CLOCK_ACCURACY_M10S,         /*The time is accurate to >10 s*/
    PTP_CLOCK_ACCURACY_UNKNOWN = 0xFE  /*The time is unknown*/
}PTP_CLOCK_ACCURACY_E;

/* 延时机制定义 */
typedef enum tagPTP_DELAY_MACHENISM_E
{
    /* In new profile:'01' for a two-way slave, and 'FE' for a one-way slave */
    PTP_DELAY_MACHENISM_E2E = 0X01,          /* 请求_响应延时机制 */
    PTP_DELAY_MACHENISM_P2P = 0X02,        /*  对端延时机制 */
    PTP_DELAY_MACHENISM_DISABLE = 0XFE      /*  延时机制不作用 */
}PTP_DELAY_MECHENISM_E;

/* 定义状态机模式 */
typedef enum tagPTP_CLOCK_FSM_MODE_E
{
    PTP_CLOCK_FSM_MODE_SLAVE_ONLY = 0,      /* slave_only 状态机设备 */
    PTP_CLOCK_FSM_MODE_MASTER_ONLY,     /* master_only 状态机设备*/
    PTP_CLOCK_FSM_MODE_FULL ,            /* 全状态机设备, 暂不支持 */
}PTP_CLOCK_FSM_MODE_E;

/* 定义单多播模式 */
typedef enum tagPTP_CLOCK_CAST_MODE_E
{
    PTP_CLOCK_UNICAST_MODE,             /* 单播模式*/
    PTP_CLOCK_MULTICAST_MODE,           /* 多播模式*/
    PTP_CLOCK_IEEE8023_MODE,            /* OVER MAC模式*/
}PTP_CLOCK_CAST_MODE_E;

/*  定义时间/频率同步模式 */
typedef enum tagPTP_SYNC_MODE_E
{
    PTP_SYNC_MODE_TIME,
    PTP_SYNC_MODE_FREQUENCY
}PTP_SYNC_MODE_E;

/* 单播协商状态机标志枚举定义 */
typedef enum tagPTP_STATE_UNICAST_NEGO_E
{
    PTP_STATE_UNICAST_NEGO_NULL = 0,
    PTP_STATE_UNICAST_NEGO_REQ,
    PTP_STATE_UNICAST_NEGO_GRANT,
    PTP_STATE_UNICAST_NEGO_REFUSE,
    PTP_STATE_UNICAST_NEGO_FAILURE,  /* 发送消息n次对方无响应 */
    PTP_STATE_UNICAST_NEGO_CANCEL,
    PTP_STATE_UNICAST_NEGO_ACK
}PTP_STATE_UNICAST_NEGO_E;

/* 报文类型定义 */
typedef enum tagPTP_MSG_TYPE_E
{
    PTP_MSG_SYNC              =       0,     /* Sync */
    PTP_MSG_DELAY_REQ,                       /* Delay_Req */
    PTP_MSG_PDELAY_REQ,                      /* Pdelay_Req */
    PTP_MSG_PDELAY_RESP,                     /* Pdelay_Resp */
    PTP_MSG_LIVE,                            /* keep alive packet */
                                             /* 5~7预留 */
    PTP_MSG_FOLLOW_UP         =       0x8,   /* Follow_Up */
    PTP_MSG_DELAY_RESP,                      /* Delay_Resp */
    PTP_MSG_PDELAY_RESP_FOLLOW_UP,           /* Pdelay_Resp_Follow_Up */
    PTP_MSG_ANNOUNCE,                        /* Announce */
    PTP_MSG_SIGNALING,                       /* Signaling */
    PTP_MSG_MANAGEMENT,                      /* Management */
    /* 以下两条消息为自定义握手消息 */
    PTP_MSG_HANDSHAKE_REQ     =       0xE,
    PTP_MSG_HANDSHAKE_RESP,
    PTP_MSG_MAX
}PTP_MSG_TYPE_E;

/*告警相关*/
typedef enum tagPTP_WARN_ID_E
{
    PTP_WARN_LINK_DOWN = 0x80,                      /* 128.链路down，实现表现为announce定时器超时,反馈以链路另一端的IP*/
    PTP_WARN_LINK_UP,                               /* 129.链路UP, 反馈以链路另一端的IP */
    PTP_WARN_BMC_FAILED,                            /* 130.选源失败,种类较多,暂时不带告警参数 */
    PTP_WARN_MASTER_CHANGED,                        /* 131.当前源改变, 携带新源参数, 同上 */
    PTP_WARN_MASTER_SYNCHRONIZATION_FAULT,          /* 132.发生Master同步错误 */
    PTP_WARN_ANNOUCE_NEGO_FAILED,                   /* 133.Annouce单播协商失败 */

    PTP_WARN_MUTICAST_FIRST_UP,                     /* 134.多播第一次up，选源结果之后上报 */

    PTP_WARN_SYNC_UP,                               /* 135.Sync单播协商成功,时钟同步链路建立成功之后通知产品高层软件 */
    PTP_WARN_SYNC_DOWN,                             /* 136.Sync单播协商失败或者单播取消,时钟同步链路建立失败之后通知产品高层软件
                                                     * 多播定时器超时时上报  */
    PTP_WARN_DELAY_NEGO_DOWN,                     /*137.Delay协商失败，上报Down告警*/
    PTP_WARN_DELAY_NEGO_UP,                       /*138.Delay协商成功，上报Up告警*/
    PTP_WARN_ANN_NEGO_REFUSE,                     /*139.Ann协商拒绝，上报Refuse告警*/
    PTP_WARN_SYNC_NEGO_TIMEOUT,                   /*140.Sync协商超时，上报Timeout告警*/
    PTP_WARN_SYNC_NEGO_REFUSE,                    /*141.Sync协商拒绝，上报Refuse告警*/
    PTP_WARN_DELAY_TIMEOUT,                       /*142.Delay协商超时，上报Timeout告警*/
    PTP_WANR_DELAY_REFUSE,                        /*143.Delay协商拒绝，上报Refuse告警*/
    PTP_WARN_ID_MAX                                 /* 144.PTP WARNING ID 最大值 */
    /* the end of wangchengyang's addition */
}PTP_WARNINGID_E;

/* 调试开关 */
typedef enum tagPTP_DEBUG_FLAG_E
{
    PTP_DEBUG_STATE  = 0x01,        /* PTP状态变迁调试 */
    PTP_DEBUG_INPUT  = 0X02,        /* 接收的PTP报文调试 */
    PTP_DEBUG_OUTPUT = 0X04,        /* 发送的PTP报文调试 */
    PTP_DEBUG_TIMER  = 0X08,        /* PTP定时器的调试 */
    PTP_DEBUG_WARN   = 0X10         /* PTP告警的调试 */
}PTP_DEBUG_FLAG_E;

/*选源模式设置*/
typedef enum tagPTP_BMC_SELECT_MODE_E
{
    PTP_BMC_SELECT_AUTO,       /*  自动选源， 默认值 */
    PTP_BMC_SELECT_MANUAL,     /*  手动选源， 指定某个源为同步源 */
}PTP_BMC_SELECT_MODE_E;

/* 定义外部通知类型 */
typedef enum tagPTP_EXTERN_EVENT_E
{
    PTP_EXTERN_EVENT_MASTER_LOCKED =0,     /* 0  master锁定基准时钟源 */
    PTP_EXTERN_EVENT_MASTER_UNLOCKED,      /* 1  master失锁*/
    PTP_EXTERN_EVENT_MAX
}PTP_EXTERN_EVENT_E;

/* 时钟源类型枚举值定义 */
typedef enum tagPTP_TIMESOURCE_E
{
    PTP_TIMESOURCE_ATOMIC     = 0x10,
    PTP_TIMESOURCE_GPS        = 0x20,
    PTP_TIMESOURCE_TRADIO     = 0x30,
    PTP_TIMESOURCE_PTP        = 0x40,
    PTP_TIMESOURCE_NTP        = 0x50,
    PTP_TIMESOURCE_HANDSET    = 0x60,
    PTP_TIMESOURCE_OTHER      = 0x90,
    PTP_TIMESOURCE_OSCILLATOR = 0xa0,
    PTP_TIMESOURCE_MAX        = 0xFF
}PTP_TIMESOURCE_E;

/*  define way mode */
typedef enum tagPTP_WAY_MODE_E
{
    PTP_WAY_MODE_ONE,
    PTP_WAY_MODE_TWO
}PTP_WAY_MODE_E;

/* define PTST types */
typedef enum tagPTP_PTSF_TYPE_E
{
    PTP_PTSF_ANNOUNCE,
    PTP_PTSF_SYNC,
    PTP_PTSF_UNUSED
}PTP_PTSF_TYPE_E;

/*define the cause of warning*/
typedef enum tagPTP_WARN_CAUSE_E
{
    PTP_WARN_CAUSE_LOCALCLASS,              /* server的class低于本端的class导致选源失败 */
    PTP_WARN_CAUSE_INVALID_MASTER_CLASS,    /* server的class无效，不在80-110范围内*/
    PTP_WARN_CAUSE_COMMON_MASTER_INVALID ,  /*通用原因:源无效，如PTSF等，供后续扩展*/
    PTP_WARN_CAUSE_MAX
}PTP_WARN_CAUSE_E;/*选源失败原因*/


typedef enum tagPTP_MASTER_CFG_CLOCK_CLASS_FLAG_E
{
    PTP_MASTER_CFG_INIT_CLOCK_CLASS,
    PTP_MASTER_CFG_MULTI_CLOCK_CLASS,
    PTP_MASTER_CFG_G8275_CLOCK_CLASS,
    PTP_MASTER_CFG_CLOCK_CLASS_MAX
}PTP_MASTER_CFG_CLOCK_CLASS_FLAG_E;

/* 时间间隔定义 */
typedef struct tagPTP_TIME_INTERVAL_S
{
    UULONG ullScaledNanoseconds;
}PTP_TIME_INTERVAL_S;

/* 端口地址定义 */
typedef struct tagPTP_PORT_ADDR_S
{
    USHORT  usNetworkProtocol;
    USHORT  usAddressLength;
    union
    {
        ULONG   ulIpv4;        /* 主机字节序 */
        UCHAR   ucMacAddr[8];  /*physical地址 8字节为了对齐*/
        ULONG   ulIpv6[4];  /*IPv6地址，主机字节序 */
    }unAddr;
}PTP_PORT_ADDR_S;

typedef struct tagPTP_PACKET_STAT_S
{
    /* Announce、Sync的收发只可能在一端存在，
     * 如果是slave就是接收个数，如果是master就是发送个数
     * Sync消息收发由FPGA实现，这里统计无意义，只是预留后续扩充 */
    ULONG ulRcvSndAnnouncePackets;
    ULONG ulRcvSndSyncPackets;
    ULONG ulRcvSignalingPackets;
    ULONG ulSndSignalingPackets;

    /* 统计信息 */
    ULONG ulTotalRcvPackets;
    ULONG ulTotalSndPackets;

    /* 接收到的错误包，sync为后续扩充 */
    ULONG ulTotalErrorPackets;
    /*丢包数 */
    ULONG ulTotalDropPackets;

    /* 乱序,乱序一般不会影响协议处理，但是能知道中途链路丢了多少包added by wangchengyang for stat. 2008-06-16 */
    ULONG ulAnnSequenceError;  /* announce乱序 */
    ULONG ulSigSequenceError;  /* signaling乱序 */
}PTP_PACKET_STAT_S;

/*Added by z00208058, 维测需求, 2012/8/31 */
typedef struct tagPTP_SLAVE_PACKET_S
{       
    ULONG ulSndAnnReqPackets;        /*发送announce协商请求报文*/
    ULONG ulRcvAnnReplyPackets;      /*接收announce协商应答报文*/
    ULONG ulRcvAnnRefusePackets;     /*接收announce协商拒绝报文*/
    
    ULONG ulRcvAnnPackets;           /*接收announce报文 */
  
    ULONG ulSndSyncReqPackets;       /*发送sync请求报文*/    
    ULONG ulRcvSyncReplyPackets;     /*接收sync应答报文*/
    ULONG ulRcvSyncRefusePackets;    /*接收sync 拒绝报文*/
  
    ULONG ulSndDelayReqPackets;      /*发送Delay请求报文 */
    ULONG ulRcvDelayReplyPackets;    /*接收Delay应答报文*/
    ULONG ulRcvDelayRefusePackets;   /*接收Delay 拒绝报文*/
  
    ULONG ulAnnSequenceError;         /* 接收announce乱序 */
    ULONG ulSignalingSequenceError;   /* 接收signaling乱序 */
    ULONG ulSndSignalingError;        /* 发送signaling报文失败 */

    ULONG ulSndAnnCancelPackets;     /*发送announce 取消报文*/
    ULONG ulRcvAnnCancelAckPackets;  /*接收announce 取消确认报文*/    
    ULONG ulRcvAnnCancelPackets;     /*接收announce 取消报文*/
    ULONG ulSndAnnCancelAckPackets;  /*发送announce 取消确认报文*/

    ULONG ulSndSyncCancelPackets;    /*发送sync 取消报文*/
    ULONG ulRcvSyncCancelAckPackets; /*接收sync 取消确认报文*/
    ULONG ulRcvSyncCancelPackets;    /*接收sync 取消报文*/
    ULONG ulSndSyncCancelAckPackets; /*发送sync 取消确认报文*/  

    ULONG ulSndDelayCancelPackets;    /*发送delay 取消报文*/
    ULONG ulRcvDelayCancelAckPackets; /*接收delay 取消确认报文*/
    ULONG ulRcvDelayCancelPackets;    /*接收delay 取消报文*/
    ULONG ulSndDelayCancelAckPackets; /*发送delay 取消确认报文*/
    
    ULONG  ulReserve[8];        /*保留字段，供以后扩展*/
      
}PTP_SLAVE_STAT_S;

/* 使能标记信息 */
typedef struct tagPTP_ENABLEINFO_S
{
    BOOL_T bAccepMasterTabEnable;   /* 可接受master列表使能标记 */
    BOOL_T bUnicastNego;            /* 使能单播协商标记 */
    ULONG ulPortEnable;             /* 端口使能标记 */
}PTP_ENABLEINFO_S;

/* 时钟ID定义 */
#pragma pack(1)
typedef UCHAR PTP_CLOCK_ID_SZ[PTP_CLOCK_ID_LEN];
#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

/* 端口ID定义 */
#pragma pack(1)
typedef struct tagPTP_PORT_ID_S
{
    PTP_CLOCK_ID_SZ szClockId;
    USHORT          usPortNumber;
}PTP_PORT_ID_S;
#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

/* Add by heyijun 00218462 for DTS2012092803600 维测需求开发, 2012-9 */
typedef struct tagSLAVE_PACKET_LIST_S
{
    PTP_CLOCK_ID_SZ  szClockId;
    PTP_SLAVE_STAT_S stSlaveStat;
}PTP_SLAVE_STAT_LIST_S;
/* End of Add by heyijun 00218462 for DTS2012092803600 维测需求开发, 2012-9 */

/*Added by weishanfengwKF61331, 钩子函数参所需消息结构体, 2011/11/23   问题单号:S.PTP.ANNCHOOK.01 */
typedef struct tagPTP_Grant_Para_S
{
    ULONG           ulMsgType;           /*消息类型: Ann 请求、Sync请求、Delay/Pdelay请求*/
    PTP_PORT_ID_S   stPortId;            /*Slave端的Port Id*/
    CHAR            cAnnInterval;        /*Announce发送间隔-3~ 4 ,实际时间取该值的对数*/
    CHAR            cSlaveFlag;          /*发出请求的主机是否已在slave列表*/
    CHAR            cPad[4];             /*保留字段*/
}PTP_GRANT_PARA_S;
/* End of Added by weishanfengwKF61331, 2011/11/23   问题单号:S.PTP.ANNCHOOK.01 */

typedef struct tagPTP_UNICAST_MASTER_S
{
    /* 公共表 */
    BOOL_T              bLink;   /*链路通断标记*/
    BOOL_T              bValid;  /*节点是否有效 */
    BOOL_T              bNegoEnable; /* 启动单播协商标记 */

    /* 协商状态标记 */
    UCHAR           ucAnnFlag; 
    UCHAR           ucSyncFlag;
    UCHAR           ucDelayFlag;   /* pdelay 和 delay 公用 */
    UCHAR           ucReserved[3];

    /* 单播协商请求和取消个消息的计数器 */
    ULONG            ulAnnReqCounter;
    ULONG            ulSyncReqCounter;
    ULONG            ulDelayReqCounter;

    ULONG            ulAnnCancelCounter;
    ULONG            ulSyncCancelCounter;
    ULONG            ulDelayCancelCounter;

    PTP_PORT_ID_S   stPortId;   /*master target id ，提供clock id信息*/
    CHAR            cPad[2];/*填充*/
}PTP_UNICAST_MASTER_S;

typedef struct tagPTP_UNICAST_SLAVE_S
{
    /* 协商状态标记 */
    UCHAR           ucAnnFlag;
    UCHAR           ucSyncFlag;
    UCHAR           ucDelayFlag;       /* pdelay 和 delay 公用 */
    UCHAR           ucReserved;

    CHAR cLogAnnInterval;/*Ann报文发送间隔*/
    CHAR cLogSyncInterval;/*Sync报文发送间隔*/
    CHAR cDelayReqInterval;/*DelayReq报文发送间隔*/
    UCHAR ucReserved2;

    ULONG ulAnnDurationField;/*Ann报文发送时长*/
    ULONG ulSyncDurationField;/*SYNC报文发送时长*/
    ULONG ulDelayReqDurationField;/*Delay Req报文发送时长*/

    /* 协商状态标记 */
    PTP_PORT_ADDR_S stSlaveAddr;       /*Slave的地址*/
    PTP_PORT_ADDR_S stExtSlaveAddr;
    PTP_PORT_ID_S   stSlaveId;         /* slave Id */
    USHORT usExtUdpPort;
}PTP_UNICAST_SLAVE_S;

typedef struct tagPTP_ACCEPT_MASTER_S
{
    BOOL_T          bValid;
    UCHAR           ucAlternatePri1;
    CHAR            cLogAnnInterval;       /* announce报文间隔 */
    PTP_PORT_ADDR_S stAcceptAddr;
    USHORT          usRcvAnnSequenceId;    /* 接收到的Announce消息的sequence id */

    /* USHORT          usResvered; */
    BOOL_T          bLink;                 /* 链路通断标记,TRUE表示链路up,FALSE表示链路down */
    ULONG           ulOutTimeHigh;         /* announce接收超时时间的HIGH位*/
    ULONG           ulOutTimeLow;          /* announce接收超时时间的LOW位*/
}PTP_ACCEPT_MASTER_S;


/* 时钟质量定义 */
#pragma pack(1)
typedef struct tagPTP_CLOCK_QA_S
{
    UCHAR   ucClockClass;                   /* 时钟等级 */
    UCHAR   ucClockAccuracy;                /* 时钟精度 */
    USHORT  usOffsetScaledLogVariance;      /* 时钟稳定度 */
}PTP_CLOCK_QA_S;
#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

/*定义默认数据集的查询数据结构*/
typedef struct tagPTP_QUERY_DEFAULT_DS
{
    /*静态成员*/
    BOOL_T          bTwoStep;
    USHORT          usNumberPorts;
    PTP_CLOCK_ID_SZ szClockId ;

    /*动态成员*/
    PTP_CLOCK_QA_S  stClockQuality;

    /*可配置成员*/
    UCHAR           ucPriority1;
    UCHAR           ucPriority2;
    USHORT          usClockFsmMode;
    UCHAR           ucDomainNumber;
    CHAR            szReserved[3];
}PTP_QUERY_DEFAULT_DS_S;

/*定义当前数据集的查询数据结构*/
typedef struct tagPTP_QUERY_CURRENT_DS
{
    USHORT              usStepsRemoved;
    USHORT              usReserved;
    PTP_TIME_INTERVAL_S stOffsetFromMaster;
    PTP_TIME_INTERVAL_S stMeanPathDelay;
}PTP_QUERY_CURRENT_DS_S;

/*定义父亲数据集的查询数据结构*/
typedef struct tagPTP_QUERY_PARENT_DS
{
    PTP_PORT_ID_S   stParentPortId;
    BOOL_T          bParentStats;
    USHORT          usObservedParentOffsetScaledLogVar;
    UCHAR           ucGrandmasterPriority1;
    UCHAR           ucGrandmasterPriority2;
    LONG            lObservedParentClockChangeRate;
    PTP_CLOCK_ID_SZ szGrandMasterId;
    PTP_CLOCK_QA_S  stGrandmasterClockQuality;      /* 时钟质量 */
    SHORT           sCurrentUtcOffset;              /* 当前UTC偏移 */
    /*Modified by r62469 for defect BC3D02265. 同步问题单 BC3D02263
    按照标准协议需要增加下发时标字段bTimeScale;*/    
    BOOL_T          bTimeScale;
    UCHAR           ucTimeSource;                   /* 时钟源 */
    UCHAR           ucPadding[3];


    /*需要补充PortAddress: 无线定制需求2各端口地址，注意同步问题*/
    PTP_PORT_ADDR_S stParentAddr[2]; /*当前同步的Master的网络地址，
                                    0为标准的，1为AP IPSEC的场景*/
}PTP_QUERY_PARENT_DS_S;

/*定义端口数据集的查询数据结构*/
typedef struct tagPTP_QUERY_PORT_DS
{
    /*静态成员*/
    PTP_PORT_ID_S stPortId;

    /*动态成员*/
    UCHAR       ucPortState;
    CHAR        cLogMinDelayReqInterval;
    PTP_TIME_INTERVAL_S stPeerMeanPathDelay;
    CHAR        cLogAnnInterval;
    UCHAR       ucAnnReceiptTimeout;
    CHAR        cLogSyncInterval;
    UCHAR       ucDelayMechanism;
    CHAR        cLogMinPdelayReqInterval;
    CHAR        versionNumber;
    USHORT      usReserveed;
}PTP_QUERY_PORT_DS_S;

/* IP/UDP信息，主要用来
   1)收到报文之后，将收到报文的IP/UDP信息组织起来，作为参数传给报文接收函数
   2)用户配置IP和UDP端口的时候调用
*/
typedef struct tagPTP_ADDRINFO_S
{
    PTP_PORT_ADDR_S  stDstPortAddr;    /* 目的地址信息，主机序。对接收报文来说，目的地址即为本地地址；对发送报文来说，目的地址为对端地址 */
    PTP_PORT_ADDR_S  stSrcPortAddr;    /* 源地址信息，主机序。对接收报文来说，源地址即为对端地址；对发送报文来说，源地址为本端地址 */
    ULONG            ulDstUdpPort;     /* 目的UDP端口，主机序。 */
    ULONG            ulSrcUdpPort;     /* 源UDP端口号，主机序。 */
    ULONG            ulVrfIndex;       /* 所属VRF index */
    ULONG            ulIfIndex;        /* 仅用于报文接收处理中保存入接口索引，发送流程中不使用*//*qinyun&luogaowei 0地址方案 2011-12-12*/
}PTP_ADDRINFO_S;

/*告警,维测相关*/
typedef struct tagPTP_WARN_PARAM_S
{
    /*所有告警的公共参数*/
    USHORT usPtpPortNum;              /*时钟端口号*/
    USHORT usReserved;
    PTP_PORT_ADDR_S stLocalPortAddr;    /*本地端口地址，可以是上报的目的端口地址SLAVE OR master*/
    PTP_PORT_ADDR_S stDstPortAddr;      /*目的端口地址，可以是上报的目的端口地址SLAVE OR master*/

    /*选源相关的告警参数*/
    UCHAR           ucOldGMPriority1;     /*时钟优先级1*/
    UCHAR           ucOldGMPriority2;     /*时钟优先级2*/
    UCHAR           ucNewGMPriority1;     /*时钟优先级1*/
    UCHAR           ucNewGMPriority2;     /*时钟优先级2*/
    PTP_PORT_ID_S   stOldMPortId;         /*老的Master PortId*/
    PTP_PORT_ID_S   stNewMPortId;         /*新的Master PortId*/
    PTP_CLOCK_ID_SZ szOldGMId;            /*该字段对于目前的一级场景，就是Fore的Clock ID*/
    PTP_CLOCK_QA_S  stOldGMClockQuality;   /*时钟*/
    PTP_PORT_ADDR_S stOldMPortAddr;        /*目的端口地址，可以是上报的目的端口地址SLAVE OR master*/
    PTP_CLOCK_ID_SZ szNewGMId;            /*该字段对于目前的一级场景，就是Fore的Clock ID*/
    PTP_CLOCK_QA_S  stNewGMClockQuality;   /*时钟*/
    PTP_PORT_ADDR_S stNewMPortAddr;        /*目的端口地址，可以是上报的目的端口地址SLAVE OR master*/
    ULONG ulCause;                        /*告警原因*/
    ULONG ulOldVrfIndex;
    ULONG ulVrfIndex;
}PTP_WARN_PARAM_S;

/*协议可选的数据类型*/
typedef struct tagPTP_UNICAST_MASTER_TAB_S
{
    USHORT  usPtpPortNumber;
    USHORT  usCfgTableSize;       /* 当前配置的单播master列表的大小,最多支持2个 */
    USHORT  usRunTableSize;       /* 当前运行状态里单播master列表的大小,在删除单播master列表发起单播取消之后，还没收到响应情况下比配置大小大 */
    USHORT  usTotalTableSize;     /* 当前节点大小 */
    PTP_UNICAST_MASTER_S stUnicastMasterTab[PTP_UNICAST_MASTR_LEN];
}PTP_UNICAST_MASTER_TAB_S;      /*该结构用于unicastMasterTable*/

typedef struct tag_PTP_ACCEPT_MASTER_TAB_S
{
    USHORT              usActualTabSize; /*协议默认值为0*/
    USHORT              usReserved;
    PTP_ACCEPT_MASTER_S stAcceptMaster[PTP_ACCEPT_MASTR_LEN];
}PTP_ACCEPT_MASTER_TAB_S;

/*定义时间属性数据集的查询数据结构*/
typedef struct tagPTP_QUERY_TIME_PROPERTIES_DS
{
    /*时间属性数据集，全部是动态成员*/
    SHORT     sCurrentUtcOffset;
    BOOL_T    bCurrentUtcOffsetValid;
    BOOL_T    bLeap59;
    BOOL_T    bLeap61;
    BOOL_T    bTimeTraceable;
    BOOL_T    bFrequencyTraceable;
    BOOL_T    bPtpTimescale;
    UCHAR     ucTimeSource;
    UCHAR     ucReserved;
}PTP_QUERY_TIME_PROPERTIES_DS_S;

/* IP struct, for query master's config */
typedef struct tagPTP_MULTI_PORT_ADDR
{
    PTP_PORT_ADDR_S stPortAddr[PTP_MAX_IP_NUM]; /*输出参数*/
    USHORT usNum;                  /*当前配置的个数      输出参数*/
    USHORT usReserved;             /* 保留 */
}PTP_MULTI_PORT_ADDR_S;

/*vrf address info*/

typedef struct tagPTP_ALL_PORT_ADDR_VRF_S
{
    ULONG ulNum;
    PTP_PORT_ADDR_S szPortAddr[PTP_MAX_VRF_NUM];
}PTP_ALL_PORT_ADDR_VRF_S;


/*报文捕获函数原型*/
typedef ULONG (* PTP_CAPTURE_PACKET_FUNC)(ULONG ulInOrOut, UCHAR* pucPacket, ULONG ulPacketLen, PTP_ADDRINFO_S *pstSrcIpUdpInfo);

/*SYNC报文是否授权回调函数*/
typedef ULONG (*PTP_GRANT_ACQUIRED_FUNC)(PTP_PORT_ADDR_S *pstPtpPortAdd, BOOL_T *pbGrant ,ULONG ulMsgType);

/*Begin Add by heyijun KF37287 for DTS2011062105058 支持clock id授权方案*/
/*Modified by weishanfengwKF61331, 产品授权导致函数参数发生改变 2011/11/23   问题单号:S.PTP.ANNCHOOK.01 */
/*SYNC报文是否授权回调函数(新)*/
typedef ULONG (*PTP_GRANT_ACQUIRED_ID_FUNC)(PTP_GRANT_PARA_S  *pstGrtInfo, BOOL_T *pbGrant);
/* End of Modified by weishanfengwKF61331, 2011/11/23   问题单号:S.PTP.ANNCHOOK.01 */
/*End Add by heyijun KF37287 for DTS2011062105058 支持clock id授权方案*/

/* Debug消息输出函数指针类型定义 */
typedef VOID (*PTP_DBG_OUTPUT_HOOK_FUNC)(CHAR *pszMsg);

/* Warning消息输出函数指针类型定义 */
typedef VOID (*PTP_WARN_OUTPUT_HOOK_FUNC)(ULONG ulWarnID, VOID *pWarnParam);

/* Added by dutianyi00217007, MANAGEMENT MESSAGE回调处理函数定义 */
typedef VOID (*PTP_GetInManagePkt_Func)(UCHAR *pucPacket, ULONG ulPacketLen, PTP_ADDRINFO_S *pstAddrInfo);
/* End of adding by dutianyi00217007, MANAGEMENT MESSAGE回调处理函数定义 */

#define PTP_COPY_UNICAST_SLAVE_OBJ(DEST, SRC)                         \
    (DEST)->ucAnnFlag               = (SRC)->ucAnnFlag;               \
    (DEST)->ucSyncFlag              = (SRC)->ucSyncFlag;              \
    (DEST)->ucDelayFlag             = (SRC)->ucDelayFlag;             \
    (DEST)->cLogAnnInterval         = (SRC)->cLogAnnInterval;         \
    (DEST)->cLogSyncInterval        = (SRC)->cLogSyncInterval;        \
    (DEST)->cDelayReqInterval       = (SRC)->cDelayReqInterval;       \
    (DEST)->ulAnnDurationField      = (SRC)->ulAnnDurationField;      \
    (DEST)->ulSyncDurationField     = (SRC)->ulSyncDurationField;     \
    (DEST)->ulDelayReqDurationField = (SRC)->ulDelayReqDurationField; \
    VOS_CopyVar((DEST)->stSlaveAddr,  (SRC)->stSlaveAddr);            \
    VOS_CopyVar((DEST)->stExtSlaveAddr,  (SRC)->stExtSlaveAddr);      \
    VOS_CopyVar((DEST)->stSlaveId,  (SRC)->stSlaveId)


/******************************************************************************
*Func Name   : PTP_Init
*Description : PTP CBB 初始化
*Input       : ulPtpDevType：PTP设备类型；
*              ulPtpSoftMode：PTP软件模式；
*              ulPtpTaskPri：PTP任务的优先级(0~255)
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   : CBB使用者
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG  PTP_Init(ULONG ulPtpDevType,ULONG ulPtpSoftMode, ULONG ulPtpTaskPri);

/******************************************************************************
*Func Name   : PTP_UnInit
*Description : PTP CBB 去初始化
*Input       : .
*Output      : .
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   : CBB使用者
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_UnInit(VOID);

/******************************************************************************
*Func Name   : PTP_SetClockAccuracy
*Description : 设置时钟时间精度，对应管理消息TLV的CLOCK_ACCURACY。
*Input       : UCHAR ucClockAccuracy:时钟时间精度。
*Output      : .
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetClockAccuracy(UCHAR ucClockAccuracy);

/******************************************************************************
*Func Name   : PTP_GetClockAccuracy
*Description : 获取时钟时间精度，对应管理消息TLV的CLOCK_ACCURACY。
*Input       : .
*Output      : UCHAR * pucClockAccuracy:时钟时间精度。
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetClockAccuracy(UCHAR *pucClockAccuracy);

/******************************************************************************
*Func Name   : PTP_SetUtcProperties
*Description : 设置时钟的UTC属性，对应管理消息TLV的UTC_PROPERTIES。
*Input       : SHORT sCurrentUtcOffset:currentUtcOffset属性;
*              BOOL_T bLeap61:leap61属性;
*              BOOL_T bLeap59:leap59属性;
*              BOOL_T bCurrentUtcOffsetValid:currentUtcOffsetValid属性;
*Output      : .
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetUtcProperties(SHORT sCurrentUtcOffset,BOOL_T bLeap61,BOOL_T bLeap59,BOOL_T bCurrentUtcOffsetValid);


/******************************************************************************
*Func Name   : PTP_GetUtcProperties
*Description : 获取时钟的UTC属性，对应管理消息TLV的UTC_PROPERTIES.
*Input       : .
*Output      : SHORT *psCurrentUtcOffset:currentUtcOffset属性;
*              BOOL_T *pbLeap61:leap61属性;
*              BOOL_T *pbLeap59:leap59属性;
*              BOOL_T *pbCurrentUtcOffsetValid:currentUtcOffsetValid属性;
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetUtcProperties(SHORT* psCurrentUtcOffset,BOOL_T *pbLeap61,BOOL_T* pbLeap59,BOOL_T* pbCurrentUtcOffsetValid);


/******************************************************************************
*Func Name   : PTP_SetTraceabilityProperties
*Description : 设置时钟的TRACEABILITY_PROPERTIES，对应管理消息TLV的
                TRACEABILITY_PROPERTIES.
*Input       : .
*Output      : BOOL_T bTimeTraceable:timeTraceable属性;
*              BOOL_T bFrequencyTraceable:frequencyTraceable属性;
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetTraceabilityProperties(BOOL_T bTimeTraceable,BOOL_T bFrequencyTraceable);


/******************************************************************************
*Func Name   : PTP_GetTraceabilityProperties
*Description : 获取时钟的TRACEABILITY_PROPERTIES，对应管理消息TLV的
TRACEABILITY_PROPERTIES.
*Input       : .
*Output      : BOOL_T *pbTimeTraceable:timeTraceable属性;
*              BOOL_T *pbFrequencyTraceable:frequencyTraceable属性;
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetTraceabilityProperties(BOOL_T *pbTimeTraceable,BOOL_T *pbFrequencyTraceable);


/******************************************************************************
*Func Name   : PTP_SetTimescaleProperties
*Description : 设置时钟的TIMESCALE_PROPERTIES，对应管理消息TLV的
TIMESCALE_PROPERTIES.
*Input       : .
*Output      : bPtpTimescale:ptpTimescale属性;
*              ucTimeSource:timeSource属性;
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetTimescaleProperties(BOOL_T bPtpTimescale,UCHAR ucTimeSource);


/******************************************************************************
*Func Name   : PTP_GetTimescaleProperties
*Description : 获取时钟的TIMESCALE_PROPERTIES，对应管理消息TLV的
TIMESCALE_PROPERTIES.
*Input       : .
*Output      : BOOL_T *pbPtpTimescale:ptpTimescale属性;
*              UCHAR *pucTimeSource:timeSource属性;
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetTimescaleProperties(BOOL_T *pbPtpTimescale,UCHAR *pucTimeSource);

/******************************************************************************
*Func Name   : PTP_SetUnicastNegotiate
*Description : 使能端口单播协商功能，对应管理TLV的UNICAST_NEGOTIATION_ENABLE.
*Input       : USHORT usPtpPortNumber:PTP端口号；
               BOOL_T bEnable:使能标记。
*Output      : .
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetUnicastNegotiate(USHORT usPtpPortNumber,BOOL_T bEnable);

/******************************************************************************
*Func Name   : PTP_SetLogQueryInterval
*Description : 设置单播master列表发送消息的请求间隔
*Input       : cLogQueryInterval:单播消息发送的请求/取消间隔
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetLogQueryInterval(CHAR cLogQueryInterval);

/******************************************************************************
*Func Name   : PTP_GetLogQueryInterval
*Description : 获取单播master列表发送消息的请求间隔
*Input       : 
*Output      : pcLogQueryInterval:  获取单播消息请求/取消间隔值的指针。
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetLogQueryInterval(CHAR* pcLogQueryInterval);

/******************************************************************************
*Func Name   : PTP_GetUnicastMasterTableSize
*Description : 获取单播master列表的元素个数
*Input       : 
*Output      : pusTableSize: 表的元素个数。
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*Remark      : Need modify
*******************************************************************************/
extern ULONG PTP_GetUnicastMasterTableSize(USHORT* pusTableSize);

/******************************************************************************
*Func Name   : PTP_AddUnicastMaster
*Description : 往单播master表中加入一个单播master
*Input       : *pstPortAddr:要添加的单播master,
               *pstExtPortAddr:扩展地址
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_AddUnicastMaster(PTP_PORT_ADDR_S *pstPortAddr, PTP_PORT_ADDR_S *pstExtPortAddr);

/******************************************************************************
*Func Name   : PTP_DelUnicastMaster
*Description : 删除单播master表中的一个master
*Input       : *pstPortAddr:要删除的单播master
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_DelUnicastMaster(PTP_PORT_ADDR_S *pstPortAddr);

/******************************************************************************
*Func Name   : PTP_QueryUnicastMaster
*Description : 查询某一地址是否在UnicastMasterTable中
*Input       : *pstPortAddr: 查询的地址
*Output      : *pstUnicastMaster: 查找节点的信息, 外部分配释放内存
*Return      : 成功返回PTP_OK，不在表中返回PTP_ERR_NOT_FOUND,其他失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_QueryUnicastMaster(PTP_PORT_ADDR_S *pstPortAddr, PTP_UNICAST_MASTER_S *pstUnicastMaster);


/******************************************************************************
*Func Name   : PTP_QueryUnicastMasterTable
*Description : 查询单播master列表。
*Input       : 
*Output      : pstUnicastMasterTable:指向单播master列表的指针;外部分配和释放,根据ulActualSize来分配
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : 
*Calls       :
*Called by   :函数需要修改
*******************************************************************************/
extern ULONG PTP_QueryUnicastMasterTable(PTP_UNICAST_MASTER_TAB_S* pstUnicastMasterTable);

/******************************************************************************
*Func Name   : PTP_QueryUnicastSlave
*Description : 查询某一地址是否在UnicastSalveTable中
*Input       : stPortAddr: 查询的IP
               ucPtpPortNumber: 对应的端口号
               pstUnicastSlave: 查询的Unicast slave, 外部分配和释放内存
*Return      : 成功返回PTP_OK，不存在返回PTP_ERR_NOT_FOUND,失败返回错误码
*Caution     :
*Calls       :
*Called by   : need modify
*******************************************************************************/
extern ULONG PTP_QueryUnicastSlave(USHORT usPtpPortNumber,
                                   PTP_PORT_ADDR_S *pstPortAddr,
                                   PTP_UNICAST_SLAVE_S *pstUnicastSlave);


/******************************************************************************
*Func Name   : PTP_AddAcceptMaster
*Description : 往AddAcceptMaster表中加入一个acceptableMaster
*Input       : *pstPortAddr:要添加的单播acceptableMaster
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_AddAcceptMaster(PTP_PORT_ADDR_S *pstPortAddr);

/******************************************************************************
*Func Name   : PTP_DelAcceptMaster
*Description : 删除AcceptMaster表中的一个acceptableMaster
*Input       :  *pstPortAddr: 要删除的单播acceptableMaster的端口地址
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_DelAcceptMaster(PTP_PORT_ADDR_S *pstPortAddr);

/******************************************************************************
*Func Name   : PTP_QueryAcceptMaster
*Description : 查询某一地址是否在AcceptMasterTable中
*Input       : *pstPortAddr: 查询的地址
*Output      : *pstAcceptMaster: 返回查询的节点
               pstAcceptMaster: 外部分配和释放内存
*Return      : 成功返回PTP_OK，未找到返回PTP_ERR_NOT_FOUND,失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_QueryAcceptMaster(PTP_PORT_ADDR_S *pstPortAddr, PTP_ACCEPT_MASTER_S *pstAcceptMaster);


/******************************************************************************
*Func Name   : PTP_QueryAcceptMasterTable
*Description : 获取时钟可接受的Master列表，对应管理TLV的
ACCEPTABLE_MASTER_TABLE。
*Input       : .
*Output      : pstAcceptMasterTable: AcceptableMasterTable，外部用户申请和释放;
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_QueryAcceptMasterTable(PTP_ACCEPT_MASTER_TAB_S *pstAcceptMasterTable);


/******************************************************************************
*Func Name   : PTP_GetAcceptMasterTableSize
*Description : 获取AcceptMasterTable的实际规格。
*Input       : 
*Output      : PpActualTableSize:指向AcceptMaster列表实际规格的指针;。
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetAcceptMasterTableSize(USHORT * pusActualTableSize);


/******************************************************************************
*Func Name   : PTP_SetAccepMasterTableEnable
*Description : 设置端口的可接受Master列表的使能开关，对应管理消息TLV的
ACCPTABLE_MASTER_TABLE_ENABLED。
*Input       : BOOL_T bAccepMasterTabEnable:PTP端口AcceptableMaster
                usPtpPortNumber: 使能的端口号
列表使能开关。
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : 请注意:该接口是针对时钟端口设置的。
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetAcceptMasterTableEnable(USHORT usPtpPortNumber, BOOL_T bAccepMasterTabEnable);

/******************************************************************************
*Func Name   : PTP_SetDelayMechanism
*Description : 设置时钟端口的DELAY_MECHANISM，对应管理消息TLV的DELAY_MECHANISM
。
*Input       : USHORT usPtpPortNumber:PTP端口号；
               UCHAR ucDelayMechanism:延时机制。
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetDelayMechanism(USHORT usPtpPortNumber,UCHAR ucDelayMechanism);

/******************************************************************************
*Func Name   : PTP_GetDelayMechanism
*Description : 设置时钟端口的DELAY_MECHANISM
*Input       : usPtpPortNumber:PTP端口号；
*Output      : UCHAR *pucDelayMechanism:延时机制。
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2008-5-27        Lishenchuan           Create
*******************************************************************************/
extern ULONG PTP_GetDelayMechanism(USHORT usPtpPortNumber,UCHAR *pucDelayMechanism);

/******************************************************************************
*Func Name   : PTP_SetLogMinDelayReqInterval
*Description : 设置时钟端口的logMinDelayReqInterval
*Input       : usPtpPortNumber:PTP时钟端口号；
               cLogMinDelayReqInterval: LogMinDelayReqInterval属性值
*               default:-4     range: -7 to 6
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : 目前设计为
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetLogMinDelayReqInterval(USHORT usPtpPortNumber, CHAR cLogMinDelayReqInterval);

/******************************************************************************
*Func Name   : PTP_GetLogMinDelayReqInterval
*Description : 获取时钟端口的logMinDelayReqInterval
*Input       : usPtpPortNumber:PTP时钟端口号；
*Output      : *pcLogMinDelayReqInterval: LogMinDelayReqInterval属性值。
*               default:-4     range: -7 to 6
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : 目前设计为
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetLogMinDelayReqInterval(USHORT usPtpPortNumber,CHAR *pcLogMinDelayReqInterval);

/******************************************************************************
*Func Name   : PTP_SetLogMinPdelayReqInterval
*Description : 设置时钟端口的logMinPdelayReqInterval，对应管理消息TLV的
LOG_MIN_MEAN_PDELAY_REQ_INTERVAL。
*Input       : usPtpPortNumber:PTP端口号；
               cLogMinPdelayReqInterval: LogMinPdelayReqInterval属性值。
*               default:-4     range: -7 to 6
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetLogMinPdelayReqInterval(USHORT usPtpPortNumber,CHAR cLogMinPdelayReqInterval);

/******************************************************************************
*Func Name   : PTP_SetLogMinPdelayReqInterval
*Description : 设置时钟端口的logMinPdelayReqInterval，对应管理消息TLV的
LOG_MIN_MEAN_PDELAY_REQ_INTERVAL。
*Input       : usPtpPortNumber:PTP端口号；
               cLogMinPdelayReqInterval: LogMinPdelayReqInterval属性值。
*               default:-4     range: -7 to 6
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetLogMinPdelayReqInterval(USHORT usPtpPortNumber,CHAR *pcLogMinPdelayReqInterval);

/******************************************************************************
*Func Name   : PTP_PtpPortEnable
*Description : 使能时钟端口，对应管理消息TLV的ENABLE_PORT。
*Input       : USHORT usPtpPortNumber:PTP时钟端口号。
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : 生成DESIGNATED_ENABLED事件输入到时钟端口。
*Calls       : 状态机函数
*Called by   :
*******************************************************************************/
extern ULONG PTP_PtpPortEnable(USHORT usPtpPortNumber);

/******************************************************************************
*Func Name   : PTP_PtpPortDisable
*Description : 去使能时钟端口，对应管理消息TLV的ENABLE_PORT。
*Input       : USHORT usPtpPortNumber:PTP时钟端口号。
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : 生成DESIGNATED_DISABLED事件输入到时钟端口。
*Calls       : 状态机函数
*Called by   :
*******************************************************************************/
extern ULONG PTP_PtpPortDisable(USHORT usPtpPortNumber);

/*******************************************************************************
*    Func Name: PTP_ExternNotifyPTPWithClass
* Date Created: 2010-09-25
*       Author: Anish K Kurian & Wangchengyang72338 & 62830
*  Description: extern module notify PTP the master's status
*        Input: USHORT usPtpPortNumber: port number
*               USHORT usCmd: notify commands
*               UCHAR ucClass:the master's class,should ensure the correction by caller
*       Output: None
*       Return: success: PTP_OK,
*               failure:respective error code
*      Caution: caller should ensure the validity of the clock class
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-09-25   Anish K Kurian & Wangchengyang72338 & 62830  Create
*
*******************************************************************************/
extern ULONG PTP_ExternNotifyPTPWithClass(USHORT usPtpPortNumber, USHORT usCmd, UCHAR ucClass);

/*******************************************************************************
*    Func Name: PTP_MasterAutoNotifyWithClass
* Date Created: 2012-09-13
*       Author: wuxiaowu217009
*  Description: 同时配置新、老模式的时钟等级时，外部通知master状态机跳转的api。
*        Input: USHORT usPtpPortNumber:PTP端口号
*               USHORT usCmd:notify命令字，0:master锁定基准时钟源、1:master失锁
*               UCHAR uc1588Class:用于配置master的老模式时钟等级。
*               UCHAR ucG8265Class:用于配置master的新模式时钟等级。
*       Output: 
*       Return: 
*      Caution: 只能用于Master侧，同时配置新、老模式ClockClass的外部事件通知
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-13   wuxiaowu217009          Create
*
*******************************************************************************/
extern ULONG PTP_MasterAutoNotifyWithClass(USHORT usPtpPortNumber, USHORT usCmd, UCHAR uc1588Class, UCHAR ucG8265Class);

/*******************************************************************************
*    Func Name: PTP_MasterGetProtocalClockClass
* Date Created: 2012-09-14
*       Author: wuxiaowu217009
*  Description: 查询新、老模式的时钟等级
*        Input: 
*       Output: UCHAR *uc1588Class:返回老模式时钟等级
*               UCHAR *ucG8265Class:返回新模式时钟等级
*       Return: PTP_OK:查询成功
*               PTP_ERR_CLOCK_UNINIT:时钟实体未初始化
*               PTP_ERR_MODE_INTERVAL:非Master侧或未使能多时钟等级
*               PTP_ERR_PARA_INVALID:传入参数非法
*      Caution: 只能用于Master侧使能了同时配置新、老模式ClockClass的场景
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-14   wuxiaowu217009          Create
*
*******************************************************************************/
extern ULONG PTP_MasterGetCfgClockClass(UCHAR *uc1588Class, UCHAR *ucG8265Class);

/******************************************************************************
*Func Name   : PTP_ExternChangeNotifyStack
*Description : 外部检测异常之后对协议栈通知
*Input       : ULONG ulPtpPortNumber  时钟端口号
*              ULONG ulCmd            外部通知事件
*Output      : 无
*Return      : 成功返回OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_ExternNotifyPTP(USHORT usPtpPortNumber, USHORT usCmd);


/******************************************************************************
*Func Name   : PTP_GetGrandClockQuality
*Description : 获取Grand Master 时钟质量
*Input       : 
*Output      : pstGrandClockQA: 祖时钟质量
                    由用户申请和释放。
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetGrandClockQuality(PTP_CLOCK_QA_S* pstGrandClockQA);


/******************************************************************************
*Func Name   : PTP_QueryLinkStatus
*Description : 获取某条链路的通断情况
*Input       : stPortAddr: 要查询链路的对端端口地址
                usPortNumber: 对应的端口号
*Output      : pbLinkstatus: BOOL_TRUE: 通  BOOL_FALSE: 断
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : 目前设计为
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_QueryLinkStatus(USHORT usPortNumber, PTP_PORT_ADDR_S *pstPortAddr, BOOL_T* pbLinkstatus);


/******************************************************************************
*功能名      : PTP_SetClockFsmMode
*描述        : 设置时钟设备的状态机模式
*输入        : ucClockFsmMode:时钟设备的状态机模式。
*输出        : 
*返回值      : 成功返回PTP_OK，失败返回错误码
*Caution     : 在添加端口后， 使能单播协商之前配置
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetClockFsmMode(UCHAR ucClockFsmMode);

/******************************************************************************
*功能名      : PTP_GetClockFsmMode
*描述        : 设置时钟设备的状态机模式
*输入        : 
*输出        : pucClockFsmMode:时钟设备的状态机模式。。
*返回值      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetClockFsmMode(UCHAR *pucClockFsmMode);

/******************************************************************************
*功能名      : PTP_SetlogAnnounceInterval
*描述        : 设置端口的logAnnounceInterval属性，对应管理消息TLV的LOG_ ANNOUNCE_INTERVAL。
*输入        : pusPtpPortNumber:时钟端口号;
*              cLogAnnounceInterval:时钟端口LogAnnounceInterval值
*               default:1      range: -3 to 3
*输出        : 
*返回值      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_SetLogAnnounceInterval(USHORT usPtpPortNumber, CHAR cLogAnnounceInterval);

/******************************************************************************
*功能名      : PTP_GetLogAnnounceInterval
*描述        : 获取端口的logAnnounceInterval属性
*输入        : pusPtpPortNumber:时钟端口号;
*              cLogAnnounceInterval:时钟端口cLogAnnounceInterval值;
*               default:1      range: -3 to 3
*输出        : 
*返回值      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_GetLogAnnounceInterval(USHORT usPtpPortNumber, CHAR *pcLogAnnounceInterval);

/******************************************************************************
*功能名      : PTP_SetlogSyncInterval
*描述        : 设置端口的logSyncInterval属性，对应管理消息TLV的LOG_ ANNOUNCE_INTERVAL。
*输入        : pusPtpPortNumber:时钟端口号;
*              ucLogSyncInterval:时钟端口LogSyncInterval值;
*               logSycInterval         default:-4     range: -7 to 1
*输出        : 
*返回值      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetLogSyncInterval(USHORT usPtpPortNumber,CHAR cLogSyncInterval);

/******************************************************************************
*功能名      : PTP_GetlogSyncInterval
*描述        : 获取端口的LogSyncInterval属性
*输入        : pusPtpPortNumber:时钟端口号;
*              pucLogSyncInterval:时钟端口LogSyncInterval值;
*               logSycInterval         default:-4     range: -7 to 1
*输出        : 
*返回值      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetLogSyncInterval(USHORT usPtpPortNumber, CHAR * pcLogSyncInterval);

/******************************************************************************
*Func Name   : PTP_SetSyncMode
*Description : 设置时钟的同步模式
*Input       : ucSyncMode: 时间同步or频率同步
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : 目前设计为
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetSyncMode(UCHAR ucSyncMode);

/******************************************************************************
*Func Name   : PTP_GetSyncMode
*Description : 获取时钟的同步模式
*Input       : 
*Output      : *pucSyncMode: 时间同步or频率同步。
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : 目前设计为
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetSyncMode(UCHAR *pucSyncMode);

/******************************************************************************
*Func Name   : PTP_SetCastMode
*Description : 设置时钟的单多播模式
*Input       : ucCastMode: 单播or多播
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : 在添加端口后， 使能单播协商之前配置
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetCastMode(UCHAR ucCastMode);

/******************************************************************************
*Func Name   : PTP_GetCastMode
*Description : 获取时钟的单多播模式
*Input       : 
*Output      : *pucCastMode: 单播or多播or OVER MAC模式
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : 目前设计为
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetCastMode(UCHAR *pucCastMode);

/******************************************************************************
*Func Name   : PTP_GetCurrentParent
*Description : 获得前时钟源端口地址
*Input       : 
*Output      : *pstParentPortAddr: 获取的单前源信息?
*Return      : PTP_OK:成功.
               else: 失败
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2008-7-17         Lishenchuan         Create
*******************************************************************************/
extern ULONG PTP_GetCurrentParent(PTP_PORT_ADDR_S *pstParentPortAddr);

/******************************************************************************
*Func Name   : PTP_GetTotalPacketStat
*Description : 获得报文统计信息
*Input       : usPtpPortNumber:需要输出统计信息的端口号
*Output      : pPacketStat: 获得报文统计信息的指针。
*Return      : PTP_OK:成功.
               else: 失败
*******************************************************************************/
extern ULONG PTP_GetTotalPacketStat(USHORT usPtpPortNumber, PTP_PACKET_STAT_S *pPacketStat);

/******************************************************************************
*Func Name   : PTP_ClearTotalPacketStat
*Description : 清除报文统计信息
*Input       : usPtpPortNumber:要清除统计信息的端口号
*Output      : 
*Return      : PTP_OK:成功.
               else: 失败
*******************************************************************************/
extern ULONG PTP_ClearTotalPacketStat(USHORT usPtpPortNumber);

/******************************************************************************
*Func Name   : PTP_GetLinkPacketStat
*Description : 获得链路报文统计信息
*Input       : *pstMasterPortAddress:链路远端的网络地址
*Output      : *pLinkPacketStat: 获得报文统计信息的指针。
*Return      : PTP_OK:成功.
               else: 失败
*Remark      : Need modify
*******************************************************************************/
extern ULONG PTP_GetLinkPacketStat(PTP_PORT_ADDR_S *pstMasterPortAddress, PTP_PACKET_STAT_S *pLinkPacketStat);

/******************************************************************************
*Func Name   : PTP_ClearLinkPacketStat
*Description : 清除链路报文统计信息
*Input       : *pstMasterPortAddress:链路远端的网络地址
*Output      : 
*Return      : PTP_OK:成功.
               else: 失败
*Remark      : Need modify
*******************************************************************************/
extern ULONG PTP_ClearLinkPacketStat(PTP_PORT_ADDR_S *pstMasterPortAddress);

/******************************************************************************
*Func Name   : PTP_SetClockQuality
*Description : 设置时钟源
*Input       : *pstClockQuality: 时钟源质量
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : 目前设计为
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetClockQuality(PTP_CLOCK_QA_S *pstClockQuality);

/******************************************************************************
*Func Name   : PTP_GetClockTwoStepFlag
*Description : 获取时钟Step模式
*Input       : 
*Output      : bTwoStep; TRUE:TwoStep;FALSE:OneStep,默认为OneStep；
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : 设置时钟为单步(不带Follow_Up)或者双步(带Follow_Up)，该接
*                 在Master侧调用；
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                       NAME                       DESCRIPTION
*  2010-1-11     t00110672/z00146309         create:支持路由器关于实现最新草案的需求
*******************************************************************************/
extern ULONG PTP_GetClockTwoStepFlag(BOOL_T   *bTwoStepFlag);


/******************************************************************************
*Func Name   : PTP_SetClockTwoStepFlag
*Description : 设置时钟Step模式
*Input       : bTwoStep; TRUE:TwoStep;FALSE:OneStep,默认为OneStep；
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : 设置时钟为单步(不带Follow_Up)或者双步(带Follow_Up)，该接
*                 在Master侧调用；
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                       NAME                       DESCRIPTION
*  2010-1-11     t00110672/z00146309         create:支持路由器关于实现最新草案的需求
*******************************************************************************/
extern ULONG PTP_SetClockTwoStepFlag(BOOL_T   bTwoStepFlag);

/******************************************************************************
*Func Name   : PTP_SetKeepAliveMode
*Description : 设置当前使用的KeepAlive模式是原有模式还是新模式;
*                   该接口在Master侧调用;
*Input       : UCHAR ucMode; 0:老模式;1:新模式;默认为1;
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : Do not support changing between modes Dynamically.
*              While switching between modes (old / New Profile), default values 
*              are updated as following:
*                                       New Profile         OLD
*                   Domain number   :       4               0
*                   Sync mode       :   Frequency           Time
*                   Delay Mechanism :   One Way(0xFE)       E2E(0x01)
*                   QueryMaxTimes   :       3               0xa
*                   ClockClass      :      255              7
*                   MAX UniMaster   :       5               2
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                       NAME                                 DESCRIPTION
*  2010-1-11     t00110672/z00146309    create:支持路由器关于实现最新草案的需求
*******************************************************************************/
extern ULONG PTP_SetKeepAliveMode(UCHAR ucMode);

/******************************************************************************
*Func Name   : PTP_SetAnnDurationField
*Description : 设置Ann报文的DurationField;
*Input       : USHORT usPtpPortNumber:PTP端口号;
*                ULONG ulAnnDuration:Ann报文的DurationField的值.范围(60~1000S),缺省300S;
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : 
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                       NAME                                 DESCRIPTION
*  2010-1-11     t00110672/z00146309    create:支持路由器关于实现最新草案的需求
*******************************************************************************/
extern ULONG PTP_SetAnnDurationField(USHORT usPtpPortNumber, ULONG ulAnnDuration);


/******************************************************************************
*Func Name   : PTP_SetSyncDurationField
*Description : 设置SYNC报文的DurationField;
*Input       : USHORT usPtpPortNumber:PTP端口号;
*                ULONG ulSyncDuration:SYNC报文的DurationField的值.范围(60~1000S),缺省300S;
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : 
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                       NAME                                 DESCRIPTION
*  2010-1-11     t00110672/z00146309    create:支持路由器关于实现最新草案的需求
*******************************************************************************/
extern ULONG PTP_SetSyncDurationField(USHORT usPtpPortNumber, ULONG ulSyncDuration);

/******************************************************************************
*Func Name   : PTP_SetDelayDurationField
*Description : 设置Delay Resp报文的DurationField;
*Input       : USHORT usPtpPortNumber:PTP端口号;
*                ULONG ulDelayDuration:DelayResp报文的DurationField的值.范围(60~1000S),缺省300S;
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : 
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                       NAME                                 DESCRIPTION
*  2010-1-11     t00110672/z00146309    create:支持路由器关于实现最新草案的需求
*******************************************************************************/
extern ULONG PTP_SetDelayDurationField(USHORT usPtpPortNumber, ULONG ulDelayRespDuration);


/******************************************************************************
*Func Name   : PTP_GetKeepAliveMode
*Description : 获取当前使用的KeepAlive模式是原有模式还是新模式;
*                   该接口在Master侧调用;
*Input       : UCHAR指针
*Output      : UCHAR ucMode; 0:老模式;1:新模式;默认为0;
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : 
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                       NAME                                 DESCRIPTION
*  2010-1-11     t00110672/z00146309    create:支持路由器关于实现最新草案的需求
*******************************************************************************/
extern ULONG PTP_GetKeepAliveMode(UCHAR *pucMode);

/******************************************************************************
*Func Name   : PTP_GetAnnDurationField
*Description : 获取Ann报文的DurationField;
*Input       : USHORT usPtpPortNumber:PTP端口号;
*                
*Output      : ULONG ulAnnDuration:Ann报文的DurationField的值.范围(60~1000S),缺省300S;
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : 
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                       NAME                                 DESCRIPTION
*  2010-1-11     t00110672/z00146309    create:支持路由器关于实现最新草案的需求
*******************************************************************************/
extern ULONG PTP_GetAnnDurationField(USHORT usPtpPortNumber, ULONG *pulAnnDuration);

/******************************************************************************
*Func Name   : PTP_GetSyncDurationField
*Description : 获取SYNC报文的DurationField;
*Input       : USHORT usPtpPortNumber:PTP端口号;
*                
*Output      : ULONG ulSyncDuration:SYNC报文的DurationField的值.范围(60~1000S),缺省300S;
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : 
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                       NAME                                 DESCRIPTION
*  2010-1-11     t00110672/z00146309    create:支持路由器关于实现最新草案的需求
*******************************************************************************/
extern ULONG PTP_GetSyncDurationField(USHORT usPtpPortNumber, ULONG *pulSyncDuration);


/******************************************************************************
*Func Name   : PTP_GetDelayDurationField
*Description : 获取Delay Resp报文的DurationField;
*Input       : USHORT usPtpPortNumber:PTP端口号;
*               
*Output      : ULONG ulDelayDuration:DelayResp报文的DurationField的值.范围(60~1000S),缺省300S;
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : 
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                       NAME                                 DESCRIPTION
*  2010-1-11     t00110672/z00146309    create:支持路由器关于实现最新草案的需求
*******************************************************************************/
extern ULONG PTP_GetDelayDurationField(USHORT usPtpPortNumber, ULONG *pulDelayRespDuration);


/******************************************************************************
*Func Name   : PTP_GetClockQuality
*Description : 获取时钟源质量
*Input       : 
*Output      : *pstClockQuality: 时钟源质量, 外部分配内存
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : 目前设计为
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetClockQuality(PTP_CLOCK_QA_S *pstClockQuality);

/******************************************************************************
*功能名      : PTP_SetPtpPortMaster
*描述        : 时钟选源模式
*输入        : lBMCSelectMode:选源模式
               *pstPortAddr: 手动选源设置的端口地址
*输出        : 
*返回值      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_SetBMCSelectMode(ULONG ulBMCSelectMode, PTP_PORT_ADDR_S *pstPortAddr);

/******************************************************************************
*功能名      : PTP_GetBMCSelectMode
*描述        : 时钟选源模式
*输入        : 
*输出        : pulBMCSelectMode:选源模式
*              pstPortAddr:手动选源下有效，手动选源的Master地址
*返回值      : 成功返回PTP_OK，失败返回错误码
*Caution     : 
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2008-06-03         lishenchuan        create
*******************************************************************************/
extern ULONG PTP_GetBMCSelectMode(ULONG *pulBMCSelectMode, PTP_PORT_ADDR_S *pstPortAddr);

/******************************************************************************
*Func Name   : PTP_GetDefaultDS
*Description : 获取时钟的默认数据集，对应管理消息TLV的DEFAULT_DATA_SET。
*Input       : .
*Output      : PTP_QUERY_DEFAULT_DS_S* pstQueryDefaultDS
:默认数据集，由用户申请和释放。
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : 目前设计为
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetDefaultDS(PTP_QUERY_DEFAULT_DS_S* pstQueryDefaultDS);

/******************************************************************************
*Func Name   : PTP_GetCurrentDS
*Description : 获取时钟当前数据集，对应管理消息TLV的CURRENT_DATA_SET。
*Input       : .
*Output      : QUERY_CURRENT_DS_S* pstQueryCurrentDS
:当前数据集，由用户申请和释放。
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : 目前设计为
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetCurrentDS(PTP_QUERY_CURRENT_DS_S* pstQueryCurrentDS);

/******************************************************************************
*Func Name   : PTP_GetParentDS
*Description : 获取时钟父亲数据集，对应管理消息TLV的PARENT_DATA_SET。
*Input       : .
*Output      : PTP_QUERY_PARENT_DS_S* pstQueryDefaultDS
:父亲数据集，由用户申请和释放。
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : 目前设计为
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetParentDS(PTP_QUERY_PARENT_DS_S* pstQueryParentDS);

/******************************************************************************
*Func Name   : PTP_GetTimePropertiesDS
*Description : 获取时间属性数据集，对应管理消息TLV的TIME_PROPERTIES_DATA_SET。
*Input       : .
*Output      : PTP_QUERY_TIME_PROPERTIES_DS_S* pstQueryTimePropertiesDS:时间属性数据集，由用户申请和释放。
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetTimePropertiesDS(PTP_QUERY_TIME_PROPERTIES_DS_S* pstQueryTimePropertiesDS);

/******************************************************************************
*Func Name   : PTP_GetPtpPortDS
*Description : 获取指定端口的数据集，对应管理消息TLV的PORT_DATA_SET。
*Input       : USHORT usPtpPortNumber:PTP时钟端口号.
*Output      : PTP_QUERY_PORT_DS_S* pstQueryPtpPortDS:时钟端口数据
                            集，由用户申请和释放。
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetPtpPortDS(USHORT usPtpPortNumber,PTP_QUERY_PORT_DS_S* pstQueryPtpPortDS);

/******************************************************************************
*功能名      : PTP_AddPtpPort
*描述        : 创建时钟端口
*输入        : ulIntfNumber：物理端口标识
*输出        : pusPtpPortNumber:时钟端口号
*返回值      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_AddPtpPort(ULONG ulIntfNumber,USHORT *pusPtpPortNumber);


extern ULONG PTP_AddMultiPortAddr(USHORT usPtpPortNumber,PTP_PORT_ADDR_S * pstPortAddr);


ULONG PTP_DelMultiPortAddr(USHORT usPtpPortNumber, PTP_PORT_ADDR_S *pstPortAddr);


extern ULONG PTP_GetMultiPortAddr(USHORT usPtpPortNumber, USHORT usNetworkProtocol, PTP_MULTI_PORT_ADDR_S *pstMultiPortAddr);


extern  ULONG  PTP_ShowMultiPortAddr(USHORT usPtpPortNumber, USHORT usNetworkProtocol);

/******************************************************************************
*功能名      : PTP_SetPtpPortAddr
*描述        : 设置时钟端口的网络层地址
*输入        : usPtpPortNumber：物理端口标识
             : *pstPortAddr:网络层地址
*输出        : 
*返回值      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_SetPtpPortAddr(USHORT usPtpPortNumber,PTP_PORT_ADDR_S *pstPortAddr);

/******************************************************************************
*功能名      : PTP_GetPtpPortAddr
*描述        : 获取时钟端口的网络层地址
*输入        : usPtpPortNumber：物理端口标识
*输出        : ptpPortAddr:网络层地址
*返回值      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_GetPtpPortAddr(USHORT usPtpPortNumber,PTP_PORT_ADDR_S* pPtpPortAddr);

/******************************************************************************
*功能名      : PTP_SetPtpPortExtendAddr
*描述        : 设置时钟端口的扩展地址
*输入        : usPtpPortNumber：物理端口标识
             : *pstPortAddr):扩展地址
*输出        : 
*返回值      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_SetPtpPortExtAddr(USHORT usPtpPortNumber,PTP_PORT_ADDR_S *pstExtPortAddr);

/******************************************************************************
*功能名      : PTP_GetPtpPortExtendAddr
*描述        : 获取时钟端口的网络层地址
*输入        : usPtpPortNumber：物理端口标识
*输出        : ptpPortAddr:网络层地址
*返回值      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_GetPtpPortExtAddr(USHORT usPtpPortNumber,PTP_PORT_ADDR_S* pPtpPortAddr);

/******************************************************************************
*功能名      : PTP_SetPtpExtUdpPort
*描述        : 设置时钟端口的扩展udp端口号
*输入        : usPtpPortNumber: 时钟端口标识
             : usUdpPort      : 扩展UDP端口号,主机序
*输出        : 
*返回值      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_SetPtpExtUdpPort (USHORT usPtpPortNumber,USHORT usUdpPort);

/******************************************************************************
*功能名      : PTP_GetPtpExtUdpPort
*描述        : 获取时钟端口的扩展udp端口号
*输入        : usPtpPortNumber: 时钟端口标识
*输出        : pusUdpPort      : 扩展UDP端口号,主机序
*返回值      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_GetPtpExtUdpPort(USHORT usPtpPortNumber,USHORT *pusUdpPort);

/******************************************************************************
*功能名      : PTP_GetVersion
*描述        : 获取PTP CBB的版本号和编译时间
*输入        : 
*输出        : CHAR *pcVerInfo:返回的PTP CBB的版本号和编译时间字符串，由用户
                分配256字节空间.
*返回值      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_GetVersion(CHAR *pcVerInfo);


/******************************************************************************
*功能名      : PTP_GetVersion
*描述        : 获取当前端口的版本号
*输入        : usPtpPortNumber:端口号
*输出        : *pcVersionNumber:端口版本号
*返回值      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_GetPTPVersion(USHORT usPtpPortNumber,CHAR *pcVersionNumber);


/******************************************************************************
*功能名      : PTP_SetDomain
*描述        : 设置TC时钟设备的域参数，对应管理消息TLV的DOMAIN。
*输入        : cDomainNumber:时钟设备域。
*输出        : 
*返回值      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_SetDomain(UCHAR ucDomainNumber);

/******************************************************************************
*功能名      : PTP_GetDomain
*描述        : 获取OC/BC时钟设备的域参数，对应管理消息TLV的DOMAIN。
*Input       : 
*Output      : *pcDomainNumber:时钟设备域。
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_GetDomain(UCHAR *pucDomainNumber);

/******************************************************************************
*功能名      : PTP_SetClockIdentity
*描述        : 设置时钟标识。
*输入        : PTP_ClockIdentity clockIdentity:时钟标识。
*输出        : 
*返回值      : 成功返回PTP_OK，失败返回错误码
*Caution     : 目前设计为
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_SetClockIdentity(PTP_CLOCK_ID_SZ clockIdentity);

/******************************************************************************
*功能名      : PTP_GetClockIdentity
*描述        : 获取时钟标识。
*输入        : 
*输出        : PTP_ClockIdentity clockIdentity:时钟标识。。
*返回值      : 成功返回PTP_OK，失败返回错误码
*Caution     : 目前设计为
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_GetClockIdentity(PTP_CLOCK_ID_SZ szClockID);

/******************************************************************************
*功能名      : PTP_SetPriority1
*描述        : 设置时钟设备的PRIORITY1参数，对应管理消息TLV的PRIORITY1。
*输入        : cPriority1:时钟设备priority1。
*输出        : 
*返回值      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_SetPriority1(UCHAR ucPriority1);

/******************************************************************************
*功能名      : PTP_GetPriority1
*描述        : 获取时钟设备的PRIORITY1参数，对应管理消息TLV的PRIORITY1。
*输入        : 
*输出        : *pcPriority1:时钟设备priority1。
*返回值      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_GetPriority1(UCHAR *pucPriority1);

/******************************************************************************
*功能名      : PTP_SetPriority2
*描述        : 设置时钟设备的PRIORITY2参数，对应管理消息TLV的PRIORITY2。
*输入        : cPriority2:时钟设备priority2。
*输出        : 
*返回值      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_SetPriority2(UCHAR ucPriority2);

/******************************************************************************
*功能名      : PTP_GetPriority2
*描述        : 获取时钟设备的PRIORITY2参数，对应管理消息TLV的PRIORITY2。
*输入        : 
*输出        : *pcPriority2:时钟设备priority2。
*返回值      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_GetPriority2(UCHAR *pucPriority2);

/******************************************************************************
*Func Name   : PTP_SetUniNegoQueryMaxTimes
*Description : 设置单播请求消息发送超时最大次数
*Input       : ulUniNegoQueryMaxTimes:单播请求最大次数, 协议未说明取值范围
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2008-5-27        Lishenchuan           Create
*******************************************************************************/
extern ULONG PTP_SetUniNegoQueryMaxTimes(ULONG ulUniNegoQueryMaxTimes);

/******************************************************************************
*Func Name   : PTP_GetUniNegoQueryMaxTimes
*Description : 获取单播请求消息发送超时最大次数
*Input       : 
*Output      : pulUniNegoQueryMaxTimes:单播请求最大次数, 协议未说明取值范围。
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2008-5-27        Lishenchuan           Create
*******************************************************************************/
extern ULONG PTP_GetUniNegoQueryMaxTimes(ULONG *pulUniNegoQueryMaxTimes);

/******************************************************************************
*Func Name   : PTP_RegFuncCapturePacketHook
*Description : 报文捕获注册函数定义
*Input       : PTP_CAPTURE_PACKET_FUNC pfPtpCapturePacket 处理函数
*Output      :
*Return      : 成功返回PTP_OK，失败返回错误码，
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2008-6-3             wangchengyang  Create
*******************************************************************************/
extern ULONG PTP_RegFuncCapturePacketHook(PTP_CAPTURE_PACKET_FUNC pfPtpCapturePacket);

/******************************************************************************
*Func Name   : PTP_SetReceiptTimeout
*Description : 设置Announce消息接收超时次数  默认3  范围2--255
*Input       : 
*Output      : ReceiptTimeout: 接收超时次数, 外部分配内存
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : 目前设计为
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetReceiptTimeout(UCHAR ReceiptTimeout);

/******************************************************************************
*Func Name   : PTP_GetReceiptTimeout
*Description : 获取Announce消息接收超时次数  默认3  范围2--255
*Input       : 
*Output      : *ReceiptTimeout: 接收超时次数, 外部分配内存
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : 目前设计为
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetReceiptTimeout(UCHAR *pucReceiptTimeout);

/******************************************************************************
*Func Name   : PTP_StartNego
*Description : 启动到某个Master的单播协商
*Input       : *pstMasterPortAddr:要启动的单播master
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2008-7-29        yaochengliang           Create
*******************************************************************************/
extern ULONG PTP_StartNego(PTP_PORT_ADDR_S *pstMasterPortAddr);

/******************************************************************************
*Func Name   : PTP_EndNego
*Description : 终止到某个Master的单播协商
*Input       : *pstMasterPortAddr:要终止的单播master
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2008-7-29        yaochengliang           Create
*******************************************************************************/
extern ULONG PTP_EndNego(PTP_PORT_ADDR_S *pstMasterPortAddr);

/******************************************************************************
*Func Name   : PTP_RegFuncSetSyncGrantNotifyHook
*Description : ANN单播请求是否授权钩子函数，由OM实现
*Input       : PTP_SYNC_GRANT_NOTIFY_FUNC pfPtpSetSyncGrantNotify 处理函数
*Output      :
*Return      : 成功返回PTP_OK，失败返回错误码，
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2008-6-3             杨洋           Create
*******************************************************************************/
extern ULONG PTP_RegFuncGrantAcquiredHook(PTP_GRANT_ACQUIRED_FUNC pfPtpSetSyncGrantNotify);


/******************************************************************************
*Func Name   : PTP_ReqCancel
*Description : Master侧单播请求取消，slave侧不能使用该API。
*Input       : usPtpPortNumber:   端口号
               ulMessageType:     消息类型
               pstPtpAddrInfo:    要取消的地址
*Output      : *ReceiptTimeout: 接收超时次数, 外部分配内存
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_ReqCancel(USHORT usPtpPortNumber,ULONG ulMessageType,PTP_PORT_ADDR_S *pstPortAddr);


/*******************************************************************************
*    Func Name: PTP_ShowVersion
* Date Created: 2008-9-11
*       Author: wangchengyang
*  Description: 显示PTP版本号和编译时间
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-9-11    Wangchengyang    Creat the first version.
*
*******************************************************************************/
extern VOID PTP_ShowVersion(VOID);

/*******************************************************************************
*    Func Name: PTP_ShowUnicastMaster
* Date Created: 2008-9-11
*       Author: wangchengyang
*  Description: 显示单播master列表
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-9-11    Wangchengyang    Creat the first version.
*
*******************************************************************************/
extern VOID PTP_ShowUnicastMaster(VOID);

/*******************************************************************************
*    Func Name: PTP_GetSlaveNumber
* Date Created: 2008-11-11
*       Author: wangchengyang
*  Description: master获取slave列表个数
*        Input: VOID
*       Output: 
*       Return: 成功返回PTP_OK;失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-11-11    Wangchengyang    Creat the first version.
*
*******************************************************************************/
extern ULONG PTP_GetSlaveNumber(USHORT usPtpPortNumber,USHORT *pusSlaveNumber);

/******************************************************************************
*Func Name   : PTP_SetLogLiveInterval
*Description : 设置keep alive报文时间间隔,目前不支持协商,master和slave两端必须设置一样
*Input       : CHAR cLogInterval:时间间隔(2的n次幂)
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : 
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetLogLiveInterval (CHAR cLogInterval);

/******************************************************************************
*Func Name   : PTP_GetLogLiveInterval
*Description : 获取keep alive报文时间间隔
*Input       : 
*Output      : CHAR *pcLogInterval:时间间隔(2的n次幂):1-10
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : 
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetLogLiveInterval (CHAR *pcLogInterval);

/******************************************************************************
*Func Name   : PTP_SetLiveReceiptTimeout
*Description : 设置keep alive报文接收超时次数
*Input       : ULONG ulReceiptTimeout:大于等于2,但是和时间间隔的乘积值域有效
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : 需要先调用接口PTP_SetLogLiveInterval配置间隔
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetLiveReceiptTimeout (ULONG ulReceiptTimeout);

/******************************************************************************
*Func Name   : PTP_GetLiveReceiptTimeout
*Description : 获取keep alive报文接收超时次数
*Input       : 
*Output      : ULONG ulReceiptTimeout:超时次数
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : 
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetLiveReceiptTimeout (ULONG *pulReceiptTimeout);

/* 注册函数接口 */
/******************************************************************************
*Func Name   : PTP_RegFuncDebugHook
*Description : 赋值gDebugOutput指针
*Input       : pfDebugOutPut: 传入的函数地址
*Output      : 
*Return      : .
*Caution     :
*Calls       : 调用统一的
*Called by   :
*******************************************************************************/
extern VOID PTP_RegFuncDebugHook(PTP_DBG_OUTPUT_HOOK_FUNC pfDbgOutPut);

/******************************************************************************
*Func Name   : PTP_RegFuncWarningHook
*Description : 赋值gWarnOutput函数指针
*Input       : pfWarnOutPut: 传入的函数地址
*Output      : 
*Return      : .
*Caution     :
*Calls       : 调用统一的
*Called by   :
*******************************************************************************/
extern VOID PTP_RegFuncWarningHook(PTP_WARN_OUTPUT_HOOK_FUNC pfWarnOutPut);

/******************************************************************************
*Func Name   : PTP_SetDbgSwitch
*Description : 输出调试信息
*Input       : dbgFlag:设置调试标记,打开(关闭)则将相应标志置位(清零)
*               PTP_DEBUG_STATE  = 0x01,        PTP状态变迁调试
*               PTP_DEBUG_INPUT  = 0X02,        接收的PTP报文调试
*               PTP_DEBUG_OUTPUT = 0X04,        发送的PTP报文调试
*               PTP_DEBUG_TIMER  = 0X08         PTP定时器的调试
*               若需要打开两个标记,则可位与
*Output      : 
*Return      : .
*******************************************************************************/
extern ULONG PTP_SetDbgSwitch (ULONG ulDbgFlag);

/******************************************************************************
*Func Name   : PTP_SetTimescaleProperties
*Description : 设置时钟的TIMESCALE_PROPERTIES，对应管理消息TLV的
TIMESCALE_PROPERTIES.
*Input       : .
*Output      : bPtpTimescale:ptpTimescale属性;
*              ucTimeSource:timeSource属性;
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2008-5-25        Lishenchuan           Create
*******************************************************************************/
extern ULONG PTP_SetTimescaleProperties(BOOL_T bPtpTimescale,UCHAR ucTimeSource);

/******************************************************************************
*Func Name   : PTP_GetTimescaleProperties
*Description : 获取时钟的TIMESCALE_PROPERTIES，对应管理消息TLV的
                TIMESCALE_PROPERTIES.
*Input       : .
*Output      : BOOL_T *pbPtpTimescale:ptpTimescale属性;
*              UCHAR *pucTimeSource:timeSource属性;
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2008-5-25        Lishenchuan           Create
*******************************************************************************/
extern ULONG PTP_GetTimescaleProperties(BOOL_T *pbPtpTimescale,UCHAR *pucTimeSource);

/******************************************************************************
*Func Name   : PTP_SetClockClassIdentify
*Description : 设置时钟Class识别功能开关
*Input       : bClassIdentify: 时钟Class开关，TRUE :打开,FALSE:关闭；
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : 
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2010-3-4         t00110672      create For BC3D02767,2010-3-4,【TD产品需求】【PTP】实现1588无线选源方案优化；
*******************************************************************************/
extern ULONG PTP_SetClockClassIdentify(BOOL_T bClassIdentify);

/******************************************************************************
*Func Name   : PTP_GetClockClassIdentify
*Description : 获取时钟Class识别功能开关
*Input       : bClassIdentify: 时钟Class开关，TRUE :打开,FALSE:关闭；
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : 
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2010-3-4         t00110672      create For BC3D02767,2010-3-4,【TD产品需求】【PTP】实现1588无线选源方案优化；
*******************************************************************************/
extern ULONG PTP_GetClockClassIdentify(BOOL_T *pbClassIdentify);

/******************************************************************************
*Func Name   : PTP_SetPriClassGroup
*Description : 设置设置一组优选时钟Class，参数按照优先级高低进行先后排序
*                  默认使用6>13>7>14.
*Input       : 按照优先级由高到底的顺序为:ucClass0>ucClass1>ucClass2>ucClass3
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : 
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2010-3-4         t00110672      create For BC3D02767,2010-3-4,【TD产品需求】【PTP】实现1588无线选源方案优化；
*******************************************************************************/
extern ULONG PTP_SetPriClassGroup(UCHAR ucClass0,UCHAR ucClass1,UCHAR ucClass2,UCHAR ucClass3);

/******************************************************************************
*Func Name   : PTP_GetPriClassGroup
*Description : 获取配置的一组优选时钟Class，参数按照优先级高低进行先后排序
*                  默认使用6>13>7>14.
*Input       : 按照优先级由高到底的顺序为:ucClass0>ucClass1>ucClass2>ucClass3
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     : 
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2010-3-4         t00110672      create For BC3D02767,2010-3-4,【TD产品需求】【PTP】实现1588无线选源方案优化；
*******************************************************************************/
extern ULONG PTP_GetPriClassGroup(UCHAR *pucClass0,UCHAR *pucClass1,UCHAR *pucClass2,UCHAR *pucClass3);

/******************************************************************************
*Func Name   : PTP_ShowClockInfo
*Description : 显示时钟相关配置信息
*Input       : 
*Output      : 
*Return      : 
*Caution     : 
*Calls       :PTP_GetClockIdentity、PTP_GetDomain、PTP_GetPriority1、PTP_GetPriority2、
*               PTP_GetCastMode、PTP_GetClockAccuracy、PTP_GetReceiptTimeout、PTP_GetSyncMode...
*Called by   :
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-25   r62469               Create
*
*******************************************************************************/
extern VOID PTP_ShowClockInfo(VOID);

/******************************************************************************
*Func Name   : PTP_ShowPortInfo
*Description : 显示时钟端口的相关动态信息
*Input       : USHORT usPtpPortNumber - 时钟端口号
*Output      : 
*Return      : 
*Caution     : 
*Calls       : PTP_GetPtpPortDSTP_GetSlaveNumber、PTP_GetPtpExtUdpPort、PTP_GetEnaleInfo、
*               PTP_GetPtpPortExtAddr、PTP_GetPtpPortAddr
*Called by   :
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-25   r62469               Create
*
*******************************************************************************/
extern VOID PTP_ShowPortInfo(USHORT usPtpPortNumber);

/******************************************************************************
*Func Name   : PTP_ShowTotalPacketStatistic
*Description : 根据端口显示时钟链路的报文统计信息
*Input       : USHORT usPtpPortNumber - 时钟端口号
*Output      : 
*Return      : 
*Caution     : 
*Calls       : PTP_GetTotalPacketStat
*Called by   :
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-25   r62469               Create
*
*******************************************************************************/
extern VOID PTP_ShowTotalPacketStatistic(USHORT usPtpPortNumber);

/******************************************************************************
*Func Name   : PTP_ShowLinkPacketStatistic
*Description : 根据地址显示时钟链路的报文统计信息
*Input       : USHORT usNetworkProtocol 
*                 USHORT usAddressLength
*                 UCHAR *pszIPOrMacAddr
*Output      : 
*Return      : 
*Caution     : 根据不同的协议，输入不同的地址
*Calls       : PTP_GetLinkPacketStat
*Called by   :
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-25   r62469               Create
*
*******************************************************************************/
extern VOID PTP_ShowLinkPacketStatistic(USHORT usNetworkProtocol,
                                                                USHORT usAddressLength, UCHAR *pszIPOrMacAddr);

/******************************************************************************
*Func Name   : PTP_ShowSlaveInfoByAddress
*Description : 根据指定地址，显示slave信息
*Input       : USHORT usNetworkProtocol 
*                 USHORT usAddressLength
*                 UCHAR *pszIPOrMacAddr
*Output      : 
*Return      : 
*Caution     : 根据不同的协议，输入不同的地址
*Calls       : PTP_GetLinkPacketStat
*Called by   :
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-25   r62469               Create
*
*******************************************************************************/
extern VOID PTP_ShowSlaveInfoByAddress(USHORT usNetworkProtocol,
                                                                USHORT usAddressLength, UCHAR *pszIPOrMacAddr);

/******************************************************************************
*Func Name   : PTP_ShowAcceptMaster
*Description : 显示可接受MASTER列表
*Input       : NAl 
*Output      : 
*Return      : 
*Caution     : 
*Calls       : 
*Called by   :
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-25   r62469               Create
*
*******************************************************************************/
extern VOID PTP_ShowAcceptMaster(VOID);

/******************************************************************************
*Func Name   : PTP_ShowLinkStatus
*Description : 显示所有链路的状态
*Input       :  
*Output      : 
*Return      : 
*Caution     : 
*Calls       : 
*Called by   :
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-25   r62469               Create
*
*******************************************************************************/
extern VOID PTP_ShowLinkStatus(VOID);

/*******************************************************************************
*    Func Name: Ptp_SetMacVlan
* Date Created: 2010-04-19
*       Author: zhangbo146309
*  Description: 设置层二组播VLAN ID
*        Input: ULONG ulPhyPortNo:
*               USHORT usVlanId:
*               USHORT usVlanPri
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-19   zhangbo146309           Create
*
*  2010-12-15  wangchengyang62830         DTS2010121500894.
*******************************************************************************/
extern ULONG  Ptp_SetMacVlan(ULONG ulPhyPortNo, USHORT usVlanId, USHORT usVlanPri);



extern ULONG  Ptp_GetMacVlan(ULONG ulPhyPortNo, USHORT * pusVlanId, USHORT * pusVlanPri);

/*******************************************************************************
*    Func Name: Ptp_ShowVlanInfo
* Date Created: 2010-04-22
*       Author: zhangbo146309
*  Description: 根据物理端口号显示配置的vlan id
*        Input: ULONG ulPhyPortNo:
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-22   zhangbo146309           Create
*
*******************************************************************************/
extern VOID Ptp_ShowVlanInfo(ULONG ulPhyPortNo);

/*******************************************************************************
*    Func Name: PTP_SetMasterWeight
* Date Created: 2010-09-25
*       Author: Anish K Kurian & Wangchengyang72338 & 62830
*  Description: Set the weigth(in new profile is priority) of the UnicastMaster
*        Input: PTP_PORT_ADDR_S *pstMaster:UnicastMaster
*               ULONG ulWeight: new profile's priority,the lesser value has high priority,no range
*       Output: None
*       Return: success: PTP_OK,
*               failure:respective error code
*      Caution: to be used only on the slave side and new profile,
*               cause don't impact the functionality, we don't check it.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-09-25   Anish K Kurian & Wangchengyang72338 & 62830  Create
*
*******************************************************************************/
extern ULONG PTP_SetMasterWeight(PTP_PORT_ADDR_S *pstMaster, ULONG ulWeight);

/*******************************************************************************
*    Func Name: PTP_GetMasterWeight
* Date Created: 2010-09-25
*       Author: Anish K Kurian & Wangchengyang72338 & 62830
*  Description: Get the weigth(in new profile is priority) of the UnicastMaster
*        Input: PTP_PORT_ADDR_S *pstMaster:UnicastMaster
*       Output: ULONG *pulWeight:to get new profile's priority
*       Return: success: PTP_OK,
*               failure:respective error code
*      Caution: to be used only on the slave side and new profile,
*               cause don't impact the functionality, we don't check it.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-09-25   Anish K Kurian & Wangchengyang72338 & 62830  Create
*
*******************************************************************************/
extern ULONG PTP_GetMasterWeight(PTP_PORT_ADDR_S *pstMaster, ULONG *pulWeight);


/*******************************************************************************
*    Func Name: PTP_SetPTSFByType
* Date Created: 2010-09-25
*       Author: Anish K Kurian & Wangchengyang72338 & 62830
*  Description: Set the PTSF value of Unicast Master for different types
*        Input: PTP_PORT_ADDR_S *pstMaster:Master's Address
*               ULONG ulType: (Sync/Unusable)
*               ULONG ulPTSFValue:  0       - none PTSF
*                                   non zero- PTSF happened
*       Output: None
*       Return: success: PTP_OK,
*               failure:respective error code
*      Caution: PTSF of Announce is set internally,can't be configured bu can be got
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-09-25   Anish K Kurian & Wangchengyang72338 & 62830  Create
*
*******************************************************************************/
extern ULONG PTP_SetPTSFByType(PTP_PORT_ADDR_S *pstMaster, ULONG ulType, ULONG ulPTSFValue);

/*******************************************************************************
*    Func Name: PTP_GetPTSFByType
* Date Created: 2010-09-25
*       Author: Anish K Kurian & Wangchengyang72338 & 62830
*  Description: Get the PTSF value of Unicast Master for different types
*        Input: PTP_PORT_ADDR_S *pstMaster:Unicast Master's Address
*               ULONG ulType:(Sync/Unusable/Announce)
*       Output: ULONG *pulPTSFValue:
*       Return: success: PTP_OK,
*               failure:respective error code
*      Caution: PTSF of Announce is set internally,can't be configured bu can be got
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-09-25   Anish K Kurian & Wangchengyang72338 & 62830  Create
*
*******************************************************************************/
extern ULONG PTP_GetPTSFByType(PTP_PORT_ADDR_S *pstMaster, ULONG ulType, ULONG *pulPTSFValue);



extern ULONG PTP_SetDomainSwitch(UCHAR ucSwitch);


extern ULONG PTP_GetDomainSwitch(UCHAR *pucSwitch);

/*******************************************************************************
*    Func Name: PTP_SetConformitySwitch
* Date Created: 2011-03-17
*       Author: tuojinbin0011672
*  Description: 设置协议一致性检查开关
*        Input: UCHAR ucSwitch:协议一致性检查开关,1-打开,0-关闭，默认关闭
*       Output: 无
*       Return: PTP_OK或者相应错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-03-17   tuojinbin00110672      Create for  DTS2011031504784 
*
*******************************************************************************/
extern ULONG PTP_SetConformitySwitch(UCHAR ucSwitch);

/*******************************************************************************
*    Func Name: PTP_GetConformitySwitch
* Date Created: 2011-03-17
*       Author: tuojinbin0011672
*  Description: 获取协议一致性检查开关
*        Input: 
*       Output: UCHAR *pucSwitch:协议一致性检查开关,1-打开,0-关闭，默认关闭
*       Return: PTP_OK或者相应错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-03-17   tuojinbin00110672      Create for  DTS2011031504784 
*
*******************************************************************************/
extern ULONG PTP_GetConformitySwitch(UCHAR *pucSwitch);

/*******************************************************************************
*    Func Name: PTP_SetCancelQueryMaxTimes
* Date Created: 2011-03-18
*       Author: wangchengyang62830
*  Description: 设置单播取消报文发送次数
*        Input: ULONG ulCancelQueryMaxTimes:单播取消报文次
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-03-18   wangchengyang62830      Create
*
*******************************************************************************/
extern ULONG PTP_SetCancelQueryMaxTimes(ULONG ulCancelQueryMaxTimes);

/*******************************************************************************
*    Func Name: PTP_GetCancelQueryMaxTimes
* Date Created: 2011-03-18
*       Author: wangchengyang62830
*  Description: 获取单播取消报文发送次数
*        Input: 
*       Output: ULONG *pulCancelQueryMaxTimes:单播取消报文次数
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-03-18   wangchengyang62830      Create
*
*******************************************************************************/
extern ULONG PTP_GetCancelQueryMaxTimes(ULONG *pulCancelQueryMaxTimes);

/*******************************************************************************
*    Func Name: PTP_SetLogAnnounceSendTime
* Date Created: 2011-03-18
*       Author: wangchengyang62830
*  Description: 设置Announce发送时间,Master侧调用,真正的发送时间为2的该值次幂
*        Input: CHAR cLogAnnSndTime:announce发送间隔[-3,4]
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-03-18   wangchengyang62830      Create DTS2011031800047 
*
*******************************************************************************/
extern ULONG PTP_SetLogAnnounceSendTime(USHORT usPtpPortNumber, CHAR cLogAnnSndTime);

/*******************************************************************************
*    Func Name: PTP_GetLogAnnounceSendTime
* Date Created: 2011-03-18
*       Author: wangchengyang62830
*  Description: 获取Announce发送时间,Master侧调用,真正的发送时间为2的该值次幂
*        Input: CHAR *pcLogAnnSndTime:announce发送间隔[-3,4]
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-03-18   wangchengyang62830      Create DTS2011031800047 
*
*******************************************************************************/
extern ULONG PTP_GetLogAnnounceSendTime(USHORT usPtpPortNumber, CHAR *pcLogAnnSndTime);

/*******************************************************************************
*    Func Name: PTP_GetTimerDelayCount
* Date Created: 2011-03-18
*       Author: wangchengyang62830
*  Description: 设置Master定时器的delay值(优化server性能时使用，即遍历多少定时器delay一下)
*        Input: ULONG ulCount:具体定时器个数[500,10240]
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-03-18   wangchengyang62830      Create DTS2011031800047
*
*******************************************************************************/
extern ULONG PTP_SetTimerDelayCount(ULONG ulCount);

/*******************************************************************************
*    Func Name: PTP_GetTimerDelayCount
* Date Created: 2011-03-18
*       Author: wangchengyang62830
*  Description: 获取Master定时器的delay值(优化server性能时使用，即遍历多少定时器delay一下)
*        Input: 
*       Output: ULONG *pulCount:具体定时器个数[500,10240]
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-03-18   wangchengyang62830      Create DTS2011031800047
*
*******************************************************************************/
extern ULONG PTP_GetTimerDelayCount(ULONG *pulCount);

/******************************************************************************
*Func Name   : PTP_RegFuncGrantAcquiredByIdHook
*Description : 单播请求是否授权钩子函数(根据Slave id来授权)，由产品高层软件实现
*Input       : PTP_GRANT_ACQUIRED_ID_FUNC pfPtpSetSyncGrantNotify 处理函数
*Output      :
*Return      : 成功返回PTP_OK，失败返回错误码，
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME                DESCRIPTION
*  2011-6-22            heyijun KF37287     Create
*******************************************************************************/
extern ULONG PTP_RegFuncGrantAcquiredByIdHook(PTP_GRANT_ACQUIRED_ID_FUNC pfPtpSetSyncGrantNotify);


extern ULONG PTP_SetPortAddrMaxCfgNum(USHORT usNetworkProtocol, USHORT usMaxNum);


extern ULONG PTP_GetPortAddrMaxCfgNum(USHORT usNetworkProtocol, USHORT *pusMaxNum);

/*Added by limin00188004, 同步问题单：根据协议要求，annouce和signing报文的alternateMasterFlag字段都应为FALSE,但是修改的时候需要考虑与老版本对接, 2011/12/15   问题单号:DTS2011121501803 */
/******************************************************************************
*Func Name   : PTP_SetAlternateMasterFlag
*Description : 设置Master侧AlternateMasterFlag字段值是否需要兼容老版本，老版本的Slave代码
*            : 会检查该字段，在Master侧修改为全false的情况下，老版本的Slave检查会不通过。
*Input       : UCHAR ucFlag,1：表示兼容老版本,0：表示不兼容老版本.默认是0.
*Output      :
*Return      : 成功返回PTP_OK，失败返回错误码，
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME                DESCRIPTION
*  2011-12-9            tuojinbin 00110672     Create
*******************************************************************************/
extern ULONG PTP_SetAlternateMasterFlag(UCHAR ucFlag);

/******************************************************************************
*Func Name   : PTP_GetAlternateMasterFlag
*Description : 获取Master侧AlternateMasterFlag字段值是否需要兼容老版本，老版本的Slave代码
*            : 会检查该字段，在Master侧修改为全false的情况下，老版本的Slave检查会不通过。
*Input       : UCHAR *pucFlag,1：表示兼容老版本,0：表示不兼容老版本.默认是0.
*Output      :
*Return      : 成功返回PTP_OK，失败返回错误码，
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME                DESCRIPTION
*  2011-12-9            tuojinbin 00110672     Create
*******************************************************************************/
extern ULONG PTP_GetAlternateMasterFlag(UCHAR *pucFlag);
/* End of Added by limin00188004, 2011/12/15   问题单号:DTS2011121501803 */

/******************************************************************************
*Func Name   : PTP_ShowMultCastTimerInfo
*Description : 显示多播PTP定时器信息
*Input       : USHORT usPtpPortNumber    时钟端口号
*Output      :
*Return      : 
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME                DESCRIPTION
*  2011-12-20           chixiang 00198096     Create
*******************************************************************************/
VOID PTP_ShowMultCastTimerInfo(USHORT usPtpPortNumber);

/*******************************************************************************
*    Func Name: PTP_SetPacketFilter
* Date Created: 2011-12-23
*       Author: heyijun KF62476
*  Description: 设置PTP报文调试过滤条件
*        Input: BOOL_T bSetYes:             打开或关闭报文调试过滤
*                                           1-打开
*                                           0-关闭
*               USHORT ulNetworkProtocol:   报文协议类型
*                                           1-IPv4 UDP报文
*                                           2-IPv6 UDP报文
*                                           3-层二多播报文
*               CHAR *pszSrcIPorMacAddr:    源地址，  可不填
*               CHAR *pszDstIPorMacAddr:    目的地址，可不填
*       Output: 
*       Return: 成功则返回PTP_OK，失败则返回其他错误码
*      Caution: 如果不指定某个地址过滤条件时，应将该元素值置为0，如不过滤源地址，
*               则将源地址值置为0
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-12-23   heyijun KF62476         Create for DTS2011122700669
*
*******************************************************************************/
extern ULONG PTP_SetPacketFilter(BOOL_T bSetYes, USHORT usNetworkProtocol, 
                                UCHAR *pszSrcIPorMacAddr, UCHAR *pszDstIPorMacAddr);

/*******************************************************************************
*    Func Name: PTP_AddPortAddrWithVrf
* Date Created: 2011-12-07
*       Author: z00187023/wKF61331/j00169178 
*  Description: add a port address with vrf
*        Input: USHORT usPtpPortNumber: 物理端口标识
*               PTP_PORT_ADDR_S *pstPortAddr: 端口地址
*               CHAR *pcVrfName: Vrf名称
*       Output: 
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: Slave, unicast, ipv4, keepAlive new mode only 
                and only the last address added is stored.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-12-07   z00187023/wKF61331/j00169178   Create for S_PTP_MULVRF_01
*
*******************************************************************************/
extern ULONG PTP_AddPortAddrWithVrf(USHORT usPtpPortNumber, PTP_PORT_ADDR_S *pstPortAddr, CHAR *pcVrfName);

/*******************************************************************************
*    Func Name: PTP_DelPortAddrWithVrf
* Date Created: 2011-12-08
*       Author: z00187023/wKF61331/j00169178 
*  Description: 
*        Input: USHORT usPtpPortNumber: 物理端口标识
*               PTP_PORT_ADDR_S *pstPortAddr: 端口地址
*               CHAR *pcVrfName: Vrf名称
*       Output: 删除带vrf的本地端口地址
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 如需支持基于线程socket, 此API必须与ADD在同一线程
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-12-08   z00187023/wKF61331/j00169178   Create for S_PTP_MULVRF_01
*
*******************************************************************************/
extern ULONG PTP_DelPortAddrWithVrf(USHORT usPtpPortNumber, PTP_PORT_ADDR_S *pstPortAddr, CHAR *pcVrfName);

/*******************************************************************************
*    Func Name: PTP_GetPortAddrWithVrf
* Date Created: 2011-12-08
*       Author: z00187023/wKF61331/j00169178 
*  Description: 返回本端地址列表
*        Input: USHORT usPtpPortNumber: 物理端口标识
*               CHAR *pcVrfName: Vrf名称
*       Output: 
*               PTP_ALL_PORT_ADDR_VRF_S *pstAllPortAddrVrf: 本端地址列表指针
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-12-08   z00187023/wKF61331/j00169178   Create for S_PTP_MULVRF_01
*
*******************************************************************************/
extern ULONG PTP_GetPortAddrWithVrf(USHORT usPtpPortNumber, CHAR *pcVrfName, PTP_ALL_PORT_ADDR_VRF_S *pstAllPortAddrVrf);

/*******************************************************************************
*    Func Name: PTP_ShowPortAddrWithVrf
* Date Created: 2011-12-08
*       Author: z00187023/wKF61331/j00169178 
*  Description: 显示本地端口地址
*        Input: USHORT usPtpPortNumber: 物理端口标识
*       Output: 
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-12-08   z00187023/wKF61331/j00169178   Create for S_PTP_MULVRF_01
*
*******************************************************************************/
extern ULONG PTP_ShowPortAddrWithVrf(USHORT usPtpPortNumber);

/*******************************************************************************
*    Func Name: PTP_StartNegoWithVrf
* Date Created: 2011-12-09
*       Author: z00187023/wKF61331/j00169178 
*  Description: 启动到某个vrf下的Master的单播协商
*        Input: PTP_PORT_ADDR_S *pstMasterPortAddr: 要启动的单播master
*               CHAR *pcVrfName: 单播master对应的vrf名称
*       Output: 
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-12-09   z00187023/wKF61331/j00169178   Create for S_PTP_MULVRF_01
*
*******************************************************************************/
extern ULONG PTP_StartNegoWithVrf(PTP_PORT_ADDR_S *pstMasterPortAddr, CHAR *pcVrfName);

/*******************************************************************************
*    Func Name: PTP_EndNegoWithVrf
* Date Created: 2011-12-09
*       Author: z00187023/wKF61331/j00169178 
*  Description:  终止到某个vrf下Master的单播协商
*        Input: PTP_PORT_ADDR_S *pstMasterPortAddr: 要终止的单播master
*               CHAR *pcVrfName: 单播master对应的vrf名称
*       Output: 
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-12-09   z00187023/wKF61331/j00169178   Create for S_PTP_MULVRF_01
*
*******************************************************************************/
extern ULONG PTP_EndNegoWithVrf(PTP_PORT_ADDR_S *pstMasterPortAddr, CHAR *pcVrfName);

/*******************************************************************************
*    Func Name: PTP_AddUnicastMasterWithVrf
* Date Created: 2011-12-09
*       Author: z00187023/wKF61331/j00169178 
*  Description:  往单播master表中加入一个vrf下的单播master
*        Input: PTP_PORT_ADDR_S *pstPortAddr: 要添加的单播master
*               PTP_PORT_ADDR_S*pstExtPortAddr: 扩展端口地址
*               CHAR *pcVrfName: 单播master对应的vrf名称
*       Output: 
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-12-09   z00187023/wKF61331/j00169178   Create for S_PTP_MULVRF_01
*
*******************************************************************************/
extern ULONG PTP_AddUnicastMasterWithVrf(PTP_PORT_ADDR_S *pstPortAddr, PTP_PORT_ADDR_S*pstExtPortAddr, CHAR *pcVrfName);


/*******************************************************************************
*    Func Name: PTP_DelUnicastMasterWithVrf
* Date Created: 2011-12-09
*       Author: z00187023/wKF61331/j00169178 
*  Description:  从单播master表中删除一个vrf下的单播master
*        Input: PTP_PORT_ADDR_S *pstPortAddr: 要删除的单播master
*               CHAR *pcVrfName: 要删除的单播master对应的vrf名称
*       Output: 
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-12-09   z00187023/wKF61331/j00169178   Create for S_PTP_MULVRF_01
*
*******************************************************************************/
extern ULONG PTP_DelUnicastMasterWithVrf(PTP_PORT_ADDR_S *pstPortAddr, CHAR *pcVrfName);

/*******************************************************************************
*    Func Name: PTP_QueryUnicastMasterWithVrf
* Date Created: 2011-12-09
*       Author: z00187023/wKF61331/j00169178 
*  Description: 查询某一地址是否在UnicastMasterTable中
*        Input: PTP_PORT_ADDR_S *pstPortAddr:  查询的地址
*               CHAR *pcVrfName: vrf名称
*       Output: 
*               PTP_UNICAST_MASTER_S *pstUnicastMaster:  查找节点的信息, 外部分配释放内存
*       Return:  成功返回PTP_OK，不在表中返回PTP_ERR_NOT_FOUND,其他失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-12-09   z00187023/wKF61331/j00169178   Create for S_PTP_MULVRF_01
*
*******************************************************************************/
extern ULONG PTP_QueryUnicastMasterWithVrf(PTP_PORT_ADDR_S *pstPortAddr, 
                                  CHAR *pcVrfName, 
                                  PTP_UNICAST_MASTER_S *pstUnicastMaster);

/*******************************************************************************
*    Func Name: PTP_QueryLinkStatusWithVrf
* Date Created: 2011-12-10
*       Author: z00187023/wKF61331/j00169178 
*  Description: 获取某条链路的通断情况
*        Input: USHORT usPortNumber: 物理端口标识
*               PTP_PORT_ADDR_S *pstPortAddr: 要查询链路的对端端口地址
*               CHAR *pcVrfName: 端口地址对应的vrf名称
*       Output: 
*               BOOL_T* pbLink: BOOL_TRUE: 通  BOOL_FALSE: 断
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-12-10   z00187023/wKF61331/j00169178   Create for S_PTP_MULVRF_01
*
*******************************************************************************/
extern ULONG PTP_QueryLinkStatusWithVrf(USHORT usPortNumber, PTP_PORT_ADDR_S *pstPortAddr, CHAR *pcVrfName, BOOL_T* pbLink);


/*******************************************************************************
*    Func Name: PTP_GetLinkPacketStatWithVrf
* Date Created: 2011-12-10
*       Author: z00187023/wKF61331/j00169178 
*  Description:  获取链路报文统计信息
*        Input: PTP_PORT_ADDR_S *pstMasterPortAddress: 链路远端的网络地址
*               CHAR *pcVrfName: 网络地址对应的vrf名称
*       Output: 
*               PTP_PACKET_STAT_S *pLinkPacketStat:  获得报文统计信息的指针。
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-12-10   z00187023/wKF61331/j00169178   Create for S_PTP_MULVRF_01
*
*******************************************************************************/
extern ULONG PTP_GetLinkPacketStatWithVrf(PTP_PORT_ADDR_S *pstMasterPortAddress, 
                                 CHAR *pcVrfName, 
                                 PTP_PACKET_STAT_S *pLinkPacketStat);

/*******************************************************************************
*    Func Name: PTP_ClearLinkPacketStatWithVrf
* Date Created: 2011-12-10
*       Author: z00187023/wKF61331/j00169178 
*  Description:  清除链路报文统计信息
*        Input: PTP_PORT_ADDR_S *pstMasterPortAddress: 链路远端的网络地址
*               CHAR *pcVrfName: 网络地址对应的vrf名称
*       Output: 
*       Return:  成功返回PTP_OK，失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-12-10   z00187023/wKF61331/j00169178   Create for S_PTP_MULVRF_01
*
*******************************************************************************/
extern ULONG PTP_ClearLinkPacketStatWithVrf(PTP_PORT_ADDR_S *pstMasterPortAddress, CHAR *pcVrfName);


/*******************************************************************************
*    Func Name: PTP_SetBMCSelectModeWithVrf
* Date Created: 2011-12-10
*       Author: z00187023/wKF61331/j00169178 
: ulBMCSelectMode:
               pstPortAddr:
*  Description:  设置时钟选源模式
*        Input: ULONG ulBMCSelectMode: 选源模式
*               PTP_PORT_ADDR_S *pstPortAddr: 手动选源下有效，手动选源的Master地址
*               CHAR *pcVrfName: Master地址的vrf名称
*       Output: 
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-12-10   z00187023/wKF61331/j00169178   Create for S_PTP_MULVRF_01
*
*******************************************************************************/
extern ULONG PTP_SetBMCSelectModeWithVrf(ULONG ulBMCSelectMode, PTP_PORT_ADDR_S *pstPortAddr, CHAR *pcVrfName);

/*******************************************************************************
*    Func Name: PTP_GetBMCSelectModeWithVrf
* Date Created: 2011-12-10
*       Author: z00187023/wKF61331/j00169178 
*  Description: 获得时钟选源模式
*        Input: 
*       Output: 
*               ULONG *pulBMCSelectMode: 选源模式
*               PTP_PORT_ADDR_S *pstPortAddr: 手动选源下有效，手动选源的Master地址
*               CHAR *pcVrfName: Master地址的vrf名称
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-12-10   z00187023/wKF61331/j00169178   Create for S_PTP_MULVRF_01
*
*******************************************************************************/
extern ULONG PTP_GetBMCSelectModeWithVrf(ULONG *pulBMCSelectMode, PTP_PORT_ADDR_S *pstPortAddr, CHAR *pcVrfName);



extern ULONG PTP_SetMasterWeightWithVrf(PTP_PORT_ADDR_S *pstMaster, CHAR *pcVrfName, ULONG ulWeight);



extern ULONG PTP_GetMasterWeightWithVrf(PTP_PORT_ADDR_S *pstMaster, CHAR *pcVrfName, ULONG *pulWeight);



extern ULONG PTP_SetPTSFByTypeWithVrf(PTP_PORT_ADDR_S *pstMaster, CHAR *pcVrfName, ULONG ulType, ULONG ulPTSFValue);



extern ULONG PTP_GetPTSFByTypeWithVrf(PTP_PORT_ADDR_S *pstMaster, CHAR *pcVrfName, ULONG ulType, ULONG *pulPTSFValue);


/*******************************************************************************
*    Func Name: PTP_GetCurrentParentWithVrf
* Date Created: 2011-12-12
*       Author: z00187023/wKF61331/j00169178 
*  Description: 获得前时钟源端口地址
*        Input: 
*       Output: PTP_PORT_ADDR_S *pstParentPortAddr: 获取的单前源信息
*               CHAR *pcVrfName: 单前源信息的vrf名称
*       Return: PTP_OK:成功.
*               else: 失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-12-12   z00187023/wKF61331/j00169178   Create for S_PTP_MULVRF_01
*
*******************************************************************************/
extern ULONG PTP_GetCurrentParentWithVrf(PTP_PORT_ADDR_S *pstParentPortAddr, CHAR *pcVrfName);


/*******************************************************************************
*    Func Name: PTP_ShowLinkPacketStatisticWithVrf
* Date Created: 2011-12-12
*       Author: z00187023/wKF61331/j00169178 
*  Description: 根据地址显示时钟链路的报文统计信息
*        Input: USHORT usNetworkProtocol:
*               USHORT usAddressLength:
*               UCHAR *pszIPOrMacAddr:
*               CHAR *pcVrfName:
*       Output: 
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 根据不同的协议，输入不同的地址
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-12-12   z00187023/wKF61331/j00169178   Create for S_PTP_MULVRF_01
*
*******************************************************************************/
extern ULONG PTP_ShowLinkPacketStatisticWithVrf(USHORT usNetworkProtocol, USHORT usAddressLength, UCHAR *pszIPOrMacAddr, CHAR *pcVrfName);


/*******************************************************************************
*    Func Name: PTP_SetSlaveMultiSelMode
* Date Created: 2011-12-28
*       Author: limin00188004/zhangliangzhi00187023/jijianhua00169178
*  Description: 配置PTP 5路选源，默认为单路选源。
*        Input: ULONG ulMultiSelMode: 0，为单路；1，为5路。默认为0，即单路。
*       Output: 
*       Return: PTP_OK，错误码。
*      Caution: 必须在PTP_AddPtpPort()之前配置是否为5路选源，不能在协商后动态配置。
*               Slave, unicast, ipv4, keepAlive new mode only.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-12-28   limin00188004/zhangliangzhi00187023/jijianhua00169178    Create
*
*******************************************************************************/
extern ULONG PTP_SetSlaveMultiSelectMode(ULONG ulMultiSelMode);

/*******************************************************************************
*    Func Name: PTP_GetSlaveMultiSelMode
* Date Created: 2011-12-28
*       Author: limin00188004/zhangliangzhi00187023/jijianhua00169178
*  Description: 获取是否为5路选源。
*        Input: 
*       Output: ULONG *pulMultiSelMode:  0，为单路；1，为5路。默认为0，即单路。
*       Return: PTP_OK, 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-12-28   limin00188004/zhangliangzhi00187023/jijianhua00169178   Create
*
*******************************************************************************/
extern ULONG PTP_GetSlaveMultiSelectMode(ULONG *pulMultiSelMode);

/*******************************************************************************
*    Func Name: PTP_SetSeqIdCompatSwitch
* Date Created: 2012-01-06
*       Author: guo00178934
*  Description: 设定Slave端Single报文SequenceID比较模式
*        Input: ULONG ulSwitch:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-01-06   guo00178934             Create
*
*******************************************************************************/
extern ULONG PTP_SetSeqIdCompatSwitch(ULONG ulSwitch);

/*******************************************************************************
*    Func Name: PTP_SetDurationTimeoutPercent
* Date Created: 2012-01-07
*       Author: guo00178934
*  Description: 配置Annc，Sync， Delay Duration重协商超时百分比(相对Duration的百分比)
*        Input: USHORT usPtpPortNumber:
*               ULONG ulDurationType:
*               ULONG ulTimeoutPrecent:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-01-07   guo00178934             Create
*
*******************************************************************************/
extern ULONG PTP_SetDurationTimeoutPercent(USHORT usPtpPortNumber, ULONG ulDurationType, ULONG ulTimeoutPrecent);

/*******************************************************************************
*    Func Name: PTP_GetDurationTimeoutPercent
* Date Created: 2012-02-03
*       Author: guo00178934
*  Description: 获取Annc，Sync， Delay Duration重协商超时百分比(相对Duration的百分比)
*        Input: USHORT usPtpPortNumber: 物理端口标识
*               ULONG ulDurationType: 消息类型
*                 (PTP_MSG_ANNOUNCE/PTP_MSG_SYNC/PTP_MSG_DELAY_RESP/PTP_MSG_PDELAY_RESP)
*               
*       Output: ULONG *pulTimeoutPrecent:Duration重协商超时百分比(50-99)
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-02-03   limin00188004           Create
*
*******************************************************************************/
extern ULONG PTP_GetDurationTimeoutPercent(USHORT usPtpPortNumber, ULONG ulDurationType, ULONG *pulTimeoutPrecent);

/*******************************************************************************
*    Func Name: PTP_ShowDurationTimeoutPercent
* Date Created: 2012-02-03
*       Author: guo00178934
*  Description: 
*        Input: USHORT usPtpPortNumber: 物理端口标识
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-02-03   limin00188004           Create
*
*******************************************************************************/
extern VOID PTP_ShowDurationTimeoutPercent(USHORT usPtpPortNumber);

/*******************************************************************************
*    Func Name: PTP_SetMasterLinkIndependSwitch
* Date Created: 2012-09-21
*       Author: limin00188004
*  Description: 设置1588 PTP支持多TLV处理和协商链路单独删除的开关
*        Input: ULONG ulSwitch: 0,关闭开关; 1,打开开关
*       Output: 
*       Return: 
*      Caution: 仅在Master侧使用; 开关打开后，不能动态关闭。
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-21   limin00188004           Create
*
*******************************************************************************/
extern ULONG PTP_SetMasterLinkIndependSwitch(ULONG ulSwitch);

/*******************************************************************************
*    Func Name: PTP_GetMasterLinkIndependSwitch
* Date Created: 2012-09-21
*       Author: limin00188004
*  Description: 获取1588 PTP支持多TLV处理和协商链路单独删除的开关
*        Input: ULONG *pulSwitch:传出参数。
*       Output: 
*       Return: 
*      Caution: 仅在Master侧使用
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-21   limin00188004           Create
*
*******************************************************************************/
extern ULONG PTP_GetMasterLinkIndependSwitch(ULONG *pulSwitch);


ULONG PTP_GetSlaveStat(PTP_PORT_ID_S *pPortId, PTP_SLAVE_STAT_S *pStatPackets);

/*******************************************************************************
*    Func Name: PTP_ShowSlaveStat
* Date Created: 2012-09-04
*       Author: z00208058
*  Description: Slave侧根据master的ClockId显示关于master的报文统计信息
*        Input: CHAR *pcClockId:Master端的clockid
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-04   z00208058               Create
*
*******************************************************************************/
VOID PTP_ShowSlaveStat(CHAR *pcClockId);

/*******************************************************************************
*    Func Name: PTP_ClearSlaveStat
* Date Created: 2012-09-04
*       Author: z00208058
*  Description: Slave侧清除关于master的1588统计信息
*        Input: PTP_PORT_ID_S *pPortId: Master端的portid
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-04   z00208058               Create
*
*******************************************************************************/
ULONG PTP_ClearSlaveStat(PTP_PORT_ID_S *pPortId);


/*******************************************************************************
*    Func Name: PTP_SetNegoAndBmcSplitMode
* Date Created: 2013-03-22
*       Author: 
*  Description: 设置ptp 协商和选源模式(用于协商和选源模式分离)
*        Input: ULONG ulNegoMode: PTP的协商模式(是否有duration协商,默认为0)
*               ULONG ulBmcMode: PTP选源模式(1588或者G8265.1,默认为0)
*       Output: 
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 
*#define PTP_NEGO_MODE_NO_DURATION   0   PTP 的协商模式: 无duration ,即早期1588草案
*#define PTP_NEGO_MODE_DURATION      1   PTP 的协商模式: 有duration ,即1588v2的可选16.1 、G8265.1
*  
*#define PTP_BMC_MODE_IEEE_1588    0 选源算法: 1588标准 
*#define PTP_BMC_MODE_ITU_G82651   1 选源算法: 8265.1标准
* 约束: 
*     1.不支持 协商模式为no duration，选源算法为8265.1的配置
*     2.暂不支持server侧的配置
*     3.此接口和PTP_SetKeepAliveMode 互斥
*     4.如果协商和选源不一致，必须显示配置同步模式、
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  
*
*******************************************************************************/
ULONG PTP_SetNegoAndBmcSplitMode(ULONG  ulNegoMode,  ULONG ulBmcMode);


/*******************************************************************************
*    Func Name: PTP_GetNegoAndBmcSplitMode
* Date Created: 2013-03-22
*       Author: 
*  Description: 获取当前ptp 协商和选源模式(用于协商和选源模式分离)
*        Input: 
*       Output: 
*               pulNegoMode: PTP的协商模式(是否有duration协商,默认为0)
*               pulBmcMode:  PTP选源模式(1588或者G8265.1,默认为0)
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  
*
*******************************************************************************/
ULONG PTP_GetNegoAndBmcSplitMode(ULONG  *pulNegoMode,  ULONG *pulBmcMode);

/*******************************************************************************
* Func Name: PTP_SendUsrManageMsg
* Date Created: 2014-01-20
* Author: dutianyi00217007
* Description: 发送PTP管理消息
* Input: USHORT usPtpPortNumber:发送管理消息的PTP端口号
*           ULONG ulVrfIndex:VRF索引
*           PTP_PORT_ADDR_S *pstDstAddr:发送管理消息的目的地址
*           UCHAR *pucBuffer:构造好的管理消息
*           ULONG ulPacketLen:欲发送的管理消息的长度
* Output: 
* Return: PTP_OK
*             PTP_ERR_PORT_NUMBER:端口号非0
*             PTP_ERR_VRF:VRF非0
*             PTP_ERR_NOT_FOUND:当前为Master侧时，找不到目的地址所对应的Slave
* Caution:PTP端口号与VRF索引只支持0；只针对3层单播
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-01-20   dutianyi00217007   Create
*
*******************************************************************************/

ULONG PTP_SendUsrManageMsg(USHORT usPtpPortNumber, ULONG ulVrfIndex, PTP_PORT_ADDR_S *pstDstAddr, UCHAR *pucBuffer, ULONG ulPacketLen);

/******************************************************************************
*Func Name   : PTP_RegManagePktInHook
*Description : 管理报文回调处理注册函数
*Input       : PTP_GetInManagePkt_Func pfPtpManagePkt:管理消息回调 处理函数
*Output      :
*Return      : 成功返回PTP_OK，失败返回错误码，
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2014-01-20     dutianyi        Create
*******************************************************************************/
ULONG PTP_RegManagePktInHook(PTP_GetInManagePkt_Func pfPtpManagePkt);

/******************************************************************************
*Func Name   : PTP_MasterNotifyWithG8275Class
*Description : 配置L2组播 G.8275.1 ClockClass并外部通知master状态机跳转
*Input       :  usPtpPortNumber:    PTP端口号
                usCmd:              notify命令字，0:master锁定基准时钟源、1:master失锁
                ucG8275Class:       用于配置master的G.8275.1时钟等级，有效性由配置保证
*Output      :
*Return      : VOS_OK:     成功
               VOS_ERR:    失败
*Caution     :1、仅对层2组播提出
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2014-02-10           dutianyi        Create
*******************************************************************************/
ULONG PTP_MasterNotifyWithG8275Class(USHORT usPtpPortNumber, USHORT usCmd, UCHAR ucG8275Class);

/******************************************************************************
*Func Name   : PTP_SetG82751Mode
*Description : 设置当前时钟是否使用L2组播G.8275.1模式
*Input       : ULONG ulMode:  是否使能G8275.1模式，0:不使能 1:使能
*Output      :
*Return      : VOS_OK:     成功
               VOS_ERR:    失败
*Caution     :1、仅对层2组播提出
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2014-02-10           dutianyi        Create
*******************************************************************************/
ULONG PTP_SetG82751Mode(ULONG ulMode);

/******************************************************************************
*Func Name   : PTP_GetG82751Mode
*Description : 获取当前时钟是否使用L2组播G.8275.1模式
*Input       : 
*Output      : ULONG ulMode:  是否使能G8275.1模式，0:不使能 1:使能
*Return      : VOS_OK:     成功
               VOS_ERR:    失败
*Caution     :1、仅对层2组播提出
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2014-02-10           dutianyi        Create
*******************************************************************************/
ULONG PTP_GetG82751Mode(ULONG *pulMode);


VOID PTP_ShowNonUnicastMaster (VOID);


#ifdef __cplusplus
}
#endif   /* end of __cplusplus          */

#endif   /* end of __ptp__common__h__    */
