/*******************************************************************************
*
*
*                Copyright 2010, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sfe_socket_api.h
*
*  Project Code: V1.1.0
*   Module Name:
*  Date Created: 2010-6-9
*        Author: w60786
*   Description: socket模块用户API头文件，定义用户需要使用的数据结构、宏和API原型
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2010-6-9     w60786           Creat the first version.
*
*******************************************************************************/
#ifndef __SFE_SOCKET_API_H__
#define __SFE_SOCKET_API_H__

#ifdef  __cplusplus
    extern "C"{
#endif

/*ERRORCODE<数据面socket模块错误码>*/
typedef enum enumSfeSockErrCode
{
    SFE_SOCK_OK = SFE_OK,                           /* 操作成功 */
    SFE_SOCK_ERR_BEGIN = SFE_SOCK_BEGIN_RET_CODE,   /* 模块错误码起始值,建议内部不要使用该值 */
    SFE_SOCK_GET_SFE_SOCKET_MAX_NUM_PRECFG_FAIL,    /* 1  获取最大socket数量预配置值失败 */
    SFE_SOCK_MALLOC_SOCKET_POOL_FAIL,               /* 2  分配socket资源池失败 */
    SFE_SOCK_MALLOC_SOCKET_NODETYPE_INVALID,        /* 3  申请socket节点时socket类型不合法. */
    SFE_SOCK_MALLOC_SOCKET_NODE_FAIL,               /* 4  从socket资源池中申请socket节点失败 */
    SFE_SOCK_MALLOC_SOCKET_NODEINDEX_INVALID,       /* 5  从socket资源池中申请的节点索引不合法 */
    SFE_SOCK_MALLOC_TCP_NODE_FAIL,                  /* 6  申请TCP资源池中的节点失败 */
    SFE_SOCK_CHECKHASH_VCPU_OVERMAX,                /* 7  判断vcpu数组有效性,数组越界 */
    SFE_SOCK_CHECKHASH_VRF_OVERMAX,                 /* 8  判断vrf数组有效性,数组越界 */
    SFE_SOCK_CHECKHASH_VCPU_POINTER_NULL,           /* 9  判断vcpu指针有效性,指针为空 */
    SFE_SOCK_CHECKHASH_VRF_POINTER_NULL,            /* 10 判断vrf指针有效性,指针为空 */

    SFE_SOCK_CHECKHASH_FIRSTHASH_NULL,              /* 11 判断1级hash指针有效性,指针为空 */
    SFE_SOCK_CHECKHASH_SECONDHASH_NULL,             /* 12 判断2级hash指针有效性,指针为空 */
    SFE_SOCK_FREE_SOCKTRANSCB_NULL,                 /* 13 释放节点时,待释放的socket节点为空 */
    SFE_SOCK_FREE_VCPUID_NOT_MATCH,                 /* 14 释放节点时,待释放的节点的VCPU ID和当前的不一致 */
    SFE_SOCK_FREE_SOCKTYPE_INVALID,                 /* 15 释放节点时,待释放的节点对应socket类型无效 */
    SFE_SOCK_FREE_HASHCHAIN_NO_NODE,                /* 16 释放节点时,当前的哈希链下无节点 */
    SFE_SOCK_HASH_SEARCH_NO_EXACTMATCH_NODE,        /* 17 没有找到精确匹配的socket */
    SFE_SOCK_HASH_SEARCH_NO_WILDCARD_NODE,          /* 18 没有找到通配匹配的socket */
    SFE_SOCK_ERR_SOCKET_NOTIFY_POINTNULL,           /* 19 获取传输层socket回调函数指针为空 */
    SFE_SOCK_FIND_NODE_FAIL_GETSOCKTRANSCB,         /* 20 根据FD获取socket节点时,未能找到对应节点 */

    SFE_SOCK_VCPUID_NOT_MATCH_GETSOCKTRANSCB,       /* 21 根据FD获取socket节点时,操作的节点的VCPU ID和当前的不一致 */
    SFE_SOCK_FD_INVALID_GETSOCKTRANSCB,             /* 22 根据FD获取socket节点时,输入FD非法 */
    SFE_SOCK_SOCKET_NOT_USED_GETSOCKTRANSCB,        /* 23 根据FD获取socket节点时,或缺的socket节点未被使用 */
    SFE_SOCK_RECV_ZMBUF_NULL_POINTER,               /* 24 接收缓冲区数据,指针为空 */
    SFE_SOCK_RECV_ZMBUF_NO_DATA,                    /* 25 接收缓冲区数据,缓冲区中无数据 */
    SFE_SOCK_SEND_ZMBUF_NULL_POINTER,               /* 26 发送用户指定数据,指针为空 */
    SFE_SOCK_SOCKBUF_FULL,                          /* 27 向socket缓冲区添加数据时,socket缓冲区满 */
    SFE_SOCK_SEND_ZMBUF_DATALEN_INVALID,            /* 28 零拷贝发送数据时, MBUF数据长度为0非法 */
    SFE_SOCK_CREATE_VCPU_SM_FAIL,                   /* 29 socket传输层初始化时创建信号量失败 */
    SFE_SOCK_FREE_SOCKET_NOT_USED,                  /* 30 释放的socket节点时,节点已被释放 */

    SFE_SOCK_HASH_SEARCH_SOCKET_NOT_USED,           /* 31 查找socket节点时, 精确匹配时节点已被释放*/
    SFE_SOCK_HASH_SEARCH_SOCKET_NOT_USED_WILD,      /* 32 查找socket节点,本地IP精确匹配其它通配时节点已被释放 */
    SFE_SOCK_HASH_SEARCH_SOCKET_NOT_USED_LIP_WILD,  /* 33 查找socket节点,本地IP通配其它通配时节点已被释放 */
    SFE_SOCK_RECV_ZMBUF_VCPUID_INVALID,             /* 34 零拷贝方式接收数据时,获取的vcpu无效 */
    SFE_SOCK_SEND_ZMBUF_VCPUID_INVALID,             /* 35 零拷贝方式发送数据时,获取的vcpu无效 */
    SFE_SOCK_IOCTL_VCPUID_INVALID,                  /* 36 设置或获取socket io时,获取的vcpu无效 */
    SFE_SOCK_MALLOC_VCPU_SM_MEM_FAIL,               /* 37 分配每个vcpu上的信号量保护失败 */
    SFE_SOCK_ADD_NAMEDB_VCPU_SM_FAIL,               /* 38 申请每个vcpu上的信号量保护添加到共享名字库失败 */
    SFE_SOCK_SETSOCKOPT_VCPUID_INVALID,             /* 39 设置SOCK选项时,获取的vcpu无效 */
    SFE_SOCK_SETSOCKOPT_LINGER_INPUT_INVAILD,       /* 40 设置SOCK选项时,设置LINGER选项输入非法 */

    SFE_SOCK_SETSOCKOPT_LINGER_SOCKTYPE_INVAILD,    /* 41 设置SOCK选项时,设置LINGER选项的不是TCP类型 */
    SFE_SOCK_SETSOCKOPT_SETKEEPALIVE_OPT_INVAILD,   /* 42 设置SOCK选项时,设置SETKEEPALIVE选项时KEEPALIVE没有置位 */
    SFE_SOCK_SETSOCKOPT_SETKEEPALIVE_SOCKTYPE_INVAILD,/* 43  设置SOCK选项时,设置KEEPALIVE选项的不是TCP类型 */
    SFE_SOCK_SETSOCKOPT_SETKEEPALIVE_VALUE_INVAILD, /* 44 设置SOCK选项时,设置SETKEEPALIVE选项输入值非法 */
    SFE_SOCK_SETSOCKOPT_SETKEEPALIVE_INPUT_INVAILD, /* 45 设置SOCK选项时,设置SETKEEPALIVE选项输入非法 */
    SFE_SOCK_SETSOCKOPT_KEEPALIVE_INPUT_INVAILD,    /* 46 设置SOCK选项时,设置SFE_SO_KEEPALIVE|SFE_SO_REUSEADDR|SFE_SO_REUSEPORT选项输入非法 */
    SFE_SOCK_SETSOCKOPT_SNDBUF_INPUT_INVAILD,       /* 47 设置SOCK选项时,设置SFE_SO_SNDBUF选项输入非法 */
    SFE_SOCK_SETSOCKOPT_SNDLOWAT_INPUT_INVAILD,     /* 48 设置SOCK选项时,设置SFE_SO_SNDLOWAT选项输入非法 */
    SFE_SOCK_SETSOCKOPT_SNDLOWAT_INVAILD,           /* 49 设置SOCK选项时,设置SFE_SO_SNDLOWAT选项设置的值非法 */
    SFE_SOCK_SETSOCKOPT_SOL_SOCKET_INVAILD,         /* 50 设置SOCK选项时,设置SOL_SOCKET级别时所操作的选项非法 */

    SFE_SOCK_SETSOCKOPT_IPPROTO_TCP_TCBCB_NULL,     /* 51 设置SOCK选项时,设置IPPROTO_TCP级别时所操作TCPCB为空 */
    SFE_SOCK_SETSOCKOPT_NODELAY_INPUT_INVAILD,      /* 52 设置SOCK选项时,设置NODELAY选项输入非法 */
    SFE_SOCK_SETSOCKOPT_IPPROTO_TCP_INVAILD,        /* 53 设置SOCK选项时,设置IPPROTO_TCP级别时所操作的选项非法 */
    SFE_SOCK_SETSOCKOPT_TOS_INPUT_INVAILD,          /* 54 设置SOCK选项时,设置TOS选项输入非法 */
    SFE_SOCK_SETSOCKOPT_TTL_INPUT_INVAILD,          /* 55 设置SOCK选项时,设置TTL选项输入非法 */
    SFE_SOCK_SETSOCKOPT_IPPROTO_IP_INVAILD,         /* 56 设置SOCK选项时,设置IPPROTO_IP级别时所操作的选项非法 */
    SFE_SOCK_SETSOCKOPT_LEVEL_INVAILD,              /* 57 设置SOCK选项时,设置级别非法 */
    SFE_SOCK_SETSOCKOPT_UDPCHECKSUM_INPUT_INVAILD,  /* 58 设置SOCK选项时,设置UDPCHECKSUM选项输入非法 */
    SFE_SOCK_GETSOCKOPT_VCPUID_INVALID,             /* 59 获取SOCK选项时,获取的vcpu无效 */
    SFE_SOCK_GETSOCKOPT_INPUT_INVALID,              /* 60 获取SOCK选项时,输入参数非法 */

    SFE_SOCK_GETSOCKOPT_SOL_SOCKET_INVAILD,         /* 61 获取SOCK选项时,获取SOL_SOCKET级别时所操作的选项非法 */
    SFE_SOCK_GETSOCKOPT_IPPROTO_TCP_TCBCB_NULL,     /* 62 获取SOCK选项时,获取IPPROTO_TCP级别时所操作TCPCB为空 */
    SFE_SOCK_GETSOCKOPT_IPPROTO_TCP_INVAILD,        /* 63 获取SOCK选项时,获取IPPROTO_TCP级别时所操作的选项非法 */
    SFE_SOCK_GETSOCKOPT_IPPROTO_IP_INVAILD,         /* 64 获取SOCK选项时,获取IPPROTO_IP级别时所操作的选项非法 */
    SFE_SOCK_GETSOCKOPT_LEVEL_INVAILD,              /* 65 获取SOCK选项时,获取级别非法 */
    SFE_SOCK_TCP_SNDBUF_NO_ENOUGH_SPACE,            /* 66 发送缓冲区空间不够 */
    SFE_SOCK_HASH_LOOKPORT_SOCKET_NOT_USED,         /* 67 根据端口查找socket节点时, 精确匹配时节点已被释放*/
    SFE_SOCK_HASH_LOOKPORT_SOCKET_NOT_USED_WILD,    /* 68 根据端口查找socket节点,本地IP精确匹配其它通配时节点已被释放 */
    SFE_SOCK_HASH_LOOKPORT_SOCKET_NOT_USED_LIP_WILD,/* 69 根据端口查找socket节点,本地IP通配其它通配时节点已被释放 */
    SFE_SOCK_HASH_LOOKPORT_NO_NODE,                 /* 70 根据端口查找HASH表失败 */

    SFE_SOCK_GET_SOCKET_NUMBER_NULL_POINTER,        /* 71 获取socket数目时传入空指针 */
    SFE_SOCK_TCP_ALREADY_CANTSENDMORE,              /* 72 发送TCP数据时TCP连接已经断连不能发送数据 */
    SFE_SOCK_TCP_NOT_ESTABLISHED,                   /* 73 发送TCP数据时TCP连接未建立完成不能发送数据 */
    SFE_SOCK_SOCKET_VCPUID_INVALID,                 /* 74 创建socket,获取的vcpu无效 */
    SFE_SOCK_SOCREATE_EAFNOSUPPORT,                 /* 75 创建socket,传入不支持的Address family */
    SFE_SOCK_SOCREATE_EPROTO_OR_SOCKTYPE,           /* 76 创建socket,传入不支持的socket类型 */
    SFE_SOCK_BIND_VCPUID_INVALID,                   /* 77 绑定socket,获取的vcpu无效 */
    SFE_SOCK_BIND_SOCKADDR_NULL,                    /* 78 绑定socket,传入地址结构为空 */
    SFE_SOCK_BIND_EAFNOSUPPORT,                     /* 79 绑定socket,传入不支持的Address family */
    SFE_SOCK_BIND_ERROR_ADDRLEN,                    /* 80 绑定socket,传入地址长度错误 */

    SFE_SOCK_BIND_EFAULT,                           /* 81 绑定socket,传入地址非法 */
    SFE_SOCK_BIND_NOT_STANDARDSOCK,                 /* 82 绑定socket,非标准socket不能调用bind函数 */
    SFE_SOCK_SOCKTRANS_BIND_PORTORADDR_NOZERO,      /* 83 绑定socket,地址端口非空，不可重复绑定 */
    SFE_SOCK_SOCKTRANS_BIND_EAFNOSUPPORT,           /* 84 绑定socket,Address family非法 */
    SFE_SOCK_SOCKTRANS_BIND_PORT_INVALID,           /* 85 绑定socket,端口非法 */
    SFE_SOCK_SOCKTRANS_EADDRINUSE,                  /* 86 绑定socket,地址已被使用 */
    SFE_SOCK_SOCKTRANS_CREATEPORT_EADDRINUSE,       /* 87 绑定socket,随机生成端口失败 */
    SFE_SOCK_LISTEN_VCPUID_INVALID,                 /* 88 监听socket,获取的vcpu无效 */
    SFE_SOCK_SOLISTEN_ENOTBIND,                     /* 89 监听socket,socket未绑定 */
    SFE_SOCK_SOLISTEN_ALREADYLISTEN,                /* 90 监听socket,已经是监听状态 */

    SFE_SOCK_LISTEN_NOT_STANDARD_TCPSOCK,           /* 91 监听socket,非标准TCP socket不能调用listen函数 */
    SFE_SOCK_CONNECT_VCPUID_INVALID,                /* 92 连接socket,获取的vcpu无效 */
    SFE_SOCK_CONNECT_SOCKADDR_NULL,                 /* 93 连接socket,传入地址结构为空 */
    SFE_SOCK_CONNECT_EAFNOSUPPORT,                  /* 94 连接socket,Address family非法 */
    SFE_SOCK_CONNECT_EPORTNOTAVAIL,                 /* 95 连接socket,socket端口为0 */
    SFE_SOCK_CONNECT_NOT_SUPPORT_NONASYN,           /* 96 连接socket,没有设置异步属性 */
    SFE_SOCK_SOCONNECT_ENOTBIND,                    /* 97 连接socket,socket未绑定 */
    SFE_SOCK_CONNECT_EFAULT,                        /* 98 连接socket,传入地址非法 */
    SFE_SOCK_CONNECT_ERROR_ADDRLEN,                 /* 99 连接socket,传入地址长度错误 */
    SFE_SOCK_CONNECT_EALREADY,                      /* 100 连接socket,已经在连接处理中 */

    SFE_SOCK_CONNECT_EINPROGRESS,                   /* 101 连接socket,开始处理 */
    SFE_SOCK_CONNECT_ERROR,                         /* 102 连接socket,TCP主动建连处理成功,但是socket未置SFE_SS_ISCONNECTING状态*/
    SFE_SOCK_CONNECT_EBLOCKING,                     /* 103 连接socket,已有任务在该socket上阻塞 */
    SFE_SOCK_SOCONNECT_EOPNOTSUPP,                  /* 104 连接socket,socket是监听socket */
    SFE_SOCK_SOCONNECT_EISCONN,                     /* 105 连接socket,socket已连接 */
    SFE_SOCK_SOCONNECT_TCPCLOSED,                   /* 106 连接socket,TCP连接已经关闭 */
    SFE_SOCK_SOCKTRANS_CONNECT_EADDRINUSE,          /* 107 连接socket,socket地址已经使用 */
    SFE_SOCK_CLOSE_VCPUID_INVALID,                  /* 108 关闭socket,获取的vcpu无效 */
    SFE_SOCK_CLOSE_EINPROGRESS,                     /* 109 关闭socket,已经在处理中 */
    SFE_SOCK_GETONESOCKDEBUG_NULL_POINTER,          /* 110 获取单个socket调试开关,传入空指针 */

    SFE_SOCK_GETALLSOCKDEBUG_NULL_POINTER,          /* 111 获取全局socket调试开关,传入空指针 */
    SFE_SOCK_SETSOCKDEBUG_VCPUID_INVALID,           /* 112 获取的VCPUID非法 */
    SFE_SOCK_SEND_BUF_TOO_BIG,                      /* 113 设置的发送缓冲区高水位置大于可以设置的最大发送缓冲区大小 */
    SFE_SOCK_RCV_BUF_TOO_BIG,                       /* 114 设置的接收缓冲区高水位置大于可以设置的最大接收缓冲区大小 */
    SFE_SOCK_SETSOCKOPT_TTL_VALUE_INPUT_INVAILD,    /* 115 设置SOCK选项时,设置TTL选项输入的TTL值非法 */
    SFE_SOCK_SETSOCKOPT_LINGER_VALUE_INPUT_INVAILD, /* 116 设置SOCK选项时,设置LINGER选项输入的LINGER选项值非法 */
    SFE_SOCK_SETSOCKOPT_TOS_INPUT_VALUE_INVAILD,    /* 117 设置SOCK选项时,设置TOS选项输入的TOS值非法 */
    SFE_SOCK_UDP_UNBIND_LOCAL_ADDR,                 /* 118 发送UDP数据时, UDP未绑定本端地址 */
    SFE_SOCK_UDP_FADDR_NULL_POINTER,                /* 119 发送UDP数据时, 远端地址为空 */
    SFE_SOCK_UDP_FADDR_AFNOSUPPORT,                 /* 120 发送UDP数据时, 远端协议族不支持 */

    SFE_SOCK_UDP_FADDR_PORTNOTAVAIL,                /* 121 发送UDP数据时, 远端端口无效 */
    SFE_SOCK_UDP_FADDR_ADDRINVALID,                 /* 122 发送UDP数据时, 远端地址无效 */
    SFE_SOCK_UDP_FADDR_LENINVALID,                  /* 123 发送UDP数据时, 远端地址长度非法 */
    SFE_SOCK_UDP_MBUF_DB_RESERVE_NOTENOUGH,         /* 124 发送UDP数据时, MBUF的DB预留长度小于最小的预留长度 */
    SFE_SOCK_UDP_MBUF_SIZE_LARGER,                  /* 125 发送UDP数据时, MBUF数据长度大于发送高水位 */
    SFE_SOCK_SET_CONNINFO_DIRC_INVALID,             /* 126 设置SOCK使用者信息时,方向信息非法 */
    SFE_SOCK_SET_CONNINFO_VCPUID_INVALID,           /* 127 设置SOCK使用者信息时,获取的vcpu无效 */
    SFE_SOCK_SOCKTRANS_BIND_TYPE_NOSUPPORT,         /* 128 绑定socket, socket类型非法 */
    SFE_SOCK_CLOSE_REORDER_NOT_ALLOWED,             /* 129 关闭socket,重排模式下不允许调用close函数 */
    SFE_SOCK_CONNECT_NOT_SUPPORT_TYPE,              /* 130 连接socket,非TCP socket进行连接 */

    SFE_SOCK_SETSOCKOPT_SETKEEPALIVE_PARAM_INVAILD, /* 131 设置SOCK选项时,设置SETKEEPALIVE选项输入的参数值非法 */
    SFE_SOCK_SETSOCKOPT_RCVBUF_INPUT_INVAILD,       /* 132 设置SOCK选项时,设置SFE_SO_RCVBUF选项输入非法 */
    SFE_SOCK_SETSOCKOPT_RCVLOWAT_INPUT_INVAILD,     /* 133 设置SOCK选项时,设置SFE_SO_RCVLOWAT选项输入非法 */
    SFE_SOCK_SETSOCKOPT_RCVLOWAT_INVAILD,           /* 134 设置SOCK选项时,设置SFE_SO_RCVLOWAT选项设置的值非法 */
    SFE_SOCK_MALLOC_GLOBALDEBUG_SWITCH_MEM_FAIL,    /* 135 初始化时,申请socket全局调试开关共享内存失败 */
    SFE_SOCK_SET_SOCKGLOBAL_DEBUGSWITCH_NULL,       /* 136 设置SOCK全局调试开关时,指针为NULL,数据面没有初始化 */
    SFE_RECV_ZMBUF_MODULE_NOT_INIT,                 /* 137 调用recvzmbuf接口时系统还未初始化 */
    SFE_SEND_ZMBUF_MODULE_NOT_INIT,                 /* 138 调用sendzmbuf接口时系统还未初始化 */
    SFE_SOCKET_MODULE_NOT_INIT,                     /* 139 调用socket接口时系统还未初始化 */
    SFE_BIND_MODULE_NOT_INIT,                       /* 140 调用bind接口时系统还未初始化 */

    SFE_LISTEN_MODULE_NOT_INIT,                     /* 141 调用listen接口时系统还未初始化 */
    SFE_CONNECT_MODULE_NOT_INIT,                    /* 142 调用connect接口时系统还未初始化 */
    SFE_CLOSE_MODULE_NOT_INIT,                      /* 143 调用close接口时系统还未初始化 */
    SFE_IOCTL_MODULE_NOT_INIT,                      /* 144 调用ioctl接口时系统还未初始化 */
    SFE_SET_SOCKETOPT_MODULE_NOT_INIT,              /* 145 调用setsocketopt接口时系统还未初始化 */
    SFE_GET_SOCKETOPT_MODULE_NOT_INIT,              /* 146 调用getsocketopt接口时系统还未初始化 */
    SFE_SET_CONNECTIONINFO_MODULE_NOT_INIT,         /* 147 调用setconnectinfo接口时系统还未初始化 */
    SFE_SOCK_SETSOCKDEBUG_MODULE_NOT_INIT,          /* 148 调用SetSocketDebugSwitchByFd接口时系统还未初始化 */
    SFE_SOCK_GET_POOLUNITNUM_BEFORE_INIT,           /* 149 在系统初始化前,不能获取到SOCKET资源池统计 */
    SFE_SOCK_GET_POOLUNITNUM_INPUT_PARA_INVALID,    /* 150 获取SOCKET资源池统计时,输入的参数判断失败 */
    SFE_SOCK_GET_POOLUNITNUM_INPUT_FAILED,          /* 151 获取SOCKET资源池统计时,获取到的空闲单元数非法*/
    SFE_SOCK_GETSOCKNAME_MODULE_NOT_INIT,           /* 152 调用SFE_GetSockName接口时,系统还未初始化 */
    SFE_SOCK_GETSOCKNAME_VCPUID_INVALID,            /* 153 调用SFE_GetSockName接口时,获取的vcpuid无效 */
    SFE_SOCK_GETSOCKNAME_NULL,                      /* 154 调用SFE_GetSockName接口时,传入指针为空 */
    SFE_SOCK_GETSOCKNAME_ERROR_ADDRLEN,             /* 155 调用SFE_GetSockName接口时,传入地址长度错误 */

    SFE_SOCK_SETSOCKOPT_ALLUSEPORT_INPUT_INVAILD,   /* 156 设置SOCK选项时,设置高端端口输入非法 */    
    SFE_SOCK_SETSOCKOPT_SOCKETTYPE_NOSUPPORT,       /* 157 设置SOCK选项时,设置VRF时,socket类型非法 */
    SFE_SOCK_SETSOCKOPT_SENDVPNID_INPUT_INVAILD,    /* 158 设置SOCK选项时,设置VRF输入非法 */
    SFE_SOCK_SETSOCKOPT_SETVRF_AFTER_BIND,          /* 159 设置SOCK选项时,设置VRF时此socket已经绑定过了(VRF设置必须在绑定操作前进行) */
    SFE_SOCK_SETSOCKOPT_VRFVALUE_TOO_BIG,           /* 160 设置SOCK选项时,待设置VRF值太大(比预配置最大值大) */
}SFE_SOCK_ERR_CODE_E;

/*MACRO<显示socket基本简要信息>*/
#define SFE_SOCK_SHOW_BASIC_INFO   0
/*MACRO<显示socket详细信息,级别1的详细信息,级别越高信息越多>*/
#define SFE_SOCK_SHOW_VERBOSE_INFO_LEVEL1   1
/*MACRO<显示socket详细信息,级别2的详细信息,级别越高信息越多>*/
#define SFE_SOCK_SHOW_VERBOSE_INFO_LEVEL2   2

/*MACRO<协议地址族>*/
#define SFE_AF_INET         2           /* internetwork: UDP, TCP, etc. */
#define SFE_AF_OSI          7
#define SFE_AF_INET6        29          /* added by mayun for IPv6 */

/*MACRO<协议号>*/
#define SFE_IPPROTO_IP          0       /* dummy for IP */
#define SFE_IPPROTO_ICMP        1       /* control message protocol */
#define SFE_IPPROTO_IGMP        2       /* group mgmt protocol */
#define SFE_IPPROTO_TCP         6       /* tcp */
#define SFE_IPPROTO_UDP         17      /* user datagram protocol */
#define SFE_IPPROTO_IPV6        41      /* IPv6 in IP */
#define SFE_IPPROTO_ICMPV6      58      /* ICMP over IPv6 */
#define SFE_IPPROTO_ISIS        124     /* ISIS over IPv4 */
#define SFE_IPPROTO_RAW         255     /* raw IP packet */

/*MACRO<socket类型>*/
#define SFE_SOCK_STREAM         1       /* stream socket */
#define SFE_SOCK_DGRAM          2       /* datagram socket */
#define SFE_SOCK_RAW            3       /* raw-protocol interface */

/*MACRO<监听socket连接队列最大长度>*/
#define SFE_SOMAXCONN       0x5

/*MACRO<socket级别>*/
#define SFE_SOL_SOCKET      0xffff

/*MACRO<socket级别选项>*/
#define SFE_SO_ACCEPTCONN       0x00000002      /* socket has had listen() */
#define SFE_SO_REUSEADDR        0x00000004      /* allow local address reuse */
#define SFE_SO_KEEPALIVE        0x00000008      /* keep connections alive */
#define SFE_SO_LINGER           0x00000080      /* linger on close if data present */
#define SFE_SO_REUSEPORT        0x00000200      /* allow local address & port reuse */
#define SFE_SO_SETKEEPALIVE     0x00020000      /* setting keepalive time value and count */
#define SFE_SO_UDPCHECKSUM      0x00000800      /* set/unset udp output to calculate check sum */

#define SFE_SO_USEALLPORT       0x00008000      /* 设置后可以使用所有端口，包括高端端口 */
/* 20121204合入企业VPN需求，增加设置VRF选项 */
#define SFE_SO_SENDVPNID        0x00002000      /* 绑定VRF */

#define SFE_SO_SNDBUF           0x1001          /* send buffer size */
#define SFE_SO_RCVBUF           0x1002          /* receive buffer size */
#define SFE_SO_SNDLOWAT         0x1003          /* send low-water mark */
#define SFE_SO_RCVLOWAT         0x1004          /* receive low-water mark */

/*MACRO<IP级别选项>*/
#define SFE_IP_TOS                      3       /* long; IP type of service and preced. */
#define SFE_IP_TTL                      4       /* long; IP time to live */

/*MACRO<TCP级别选项>*/
#define SFE_TCP_NODELAY                 1       /* set/get tcp nodelay option */

/*MACRO<ioctl操作类型>*/
#define SFE_FIOASYNC            0x8004667D      /* Set/Unset socket to receive */
/* 当前协议栈只支持SFE_FIOASYNC方式,产品使用时必须对所有socket设置该属性 */

/* MACRO<TCP重排保活定时器时长配置范围(单位:秒)> */
#define SFE_SO_KEEPALIVE_TIMER_MIN      600
#define SFE_SO_KEEPALIVE_TIMER_MAX      7800
#define SFE_SO_KEEPALIVE_TIMER_DEFAULT  7800

/*STRUCT<设置socket异步方式>*/
typedef struct  tagSFE_ASYNSOCKET
{
    UINT32 u32Value;        /* 取值: 0:取消socket异步方式 1:设置socket异步方式. */
    UINT32 u32Resv;         /* 保留 */
}SFE_ASYNSOCKET_S;

/*STRUCT<LINGER选项设定数据结构定义>*/
typedef struct tagSFE_LINGER
{
    UINT32  u32OnOff;        /* option on/off */
    UINT32  u32Linger;       /* linger time */
}SFE_LINGER_S;
#define        SFE_L_LINGER_S        sizeof(SFE_LINGER_S)

/* STRUCT<保活定时器时间设定数据结构定义,该结构不能显示8字节对齐> */
typedef struct tagSFE_KEEPALIVESET
{
    UINT16       u16Keepintvl;                  /* 保活报文发送时间间隔 */
                                                /* !!注意:TCP重排模式下,u16Keepintvl的配置要注意以下几点:(TCP重排下不关注u16Keepcount)
                                                        1.配置范围:[600, 7800], 即[SFE_SO_KEEPALIVE_TIMER_MIN, SFE_SO_KEEPALIVE_TIMER_MAX].
                                                        2.配置默认值:7800, 即SFE_SO_KEEPALIVE_TIMER_DEFAULT.
                                                        3.配置值单位:秒.
                                                        4.配置要求:配置值必须为600的整数倍,如果不是整数倍,将按照600的整数倍取整.
                                                          例如:用户配置值为:2000, 则实际配置值为:1800*/

    UINT16       u16Keepcount;                  /* 保活报文发送次数 */
}SFE_KEEPALIVESET_S;
#define        SFE_L_KEEPALIVE_S   sizeof(SFE_KEEPALIVESET_S)

/*STRUCT<Ipv4地址结构>*/
typedef struct tagSFE_IN_ADDR
{
    UINT32 s_addr;                              /* address of the socket */
}SFE_IN_ADDR_S;

/*STRUCT<Ipv4 socket地址结构>*/
typedef struct tagSFE_SOCKADDR_IN
{
    UINT8           sin_len;                    /* zy */
    UINT8           sin_family;                 /* must be AF_INET */
    UINT16          sin_port;                   /* 16-bit port number */
    SFE_IN_ADDR_S   sin_addr;                   /* 32-bit address */
    CHAR            sin_zero[8];                /* must be 0 */
}SFE_SOCKADDRIN_S;

/*STRUCT<传输层socket回调通知操作类型>*/
typedef enum enumSfeSockNotify
{
    SFE_SOCK_NOTIFY_RCVSYN = 0,                 /* 0  TCP收到SYN通知(TCP透明代理收到SYN，TCP重排收到SYN,
                                                   标准TCP被动建连收到SYN) */
    SFE_SOCK_NOTIFY_ESTABLISHED,                /* 1  TCP建连成功通知(TCP透明代理建连成功,TCP重排建连成功,
                                                   标准TCP本端主动建连成功,标准TCP被动建连成功.
                                                   标准TCP被动建连成功之后socket资源由用户负责释放即必须调用close. */
    SFE_SOCK_NOTIFY_CONNECTFAIL,                /* 2  TCP透明代理建连失败,TCP重排建连失败,及标准TCP本端被动建连失败通知.
                                                   用户不需要也不能调用close关闭socket,协议栈会自动释放socket相关资源. */
    SFE_SOCK_NOTIFY_ACTIVE_CONNECTFAIL,         /* 3  标准TCP本端主动建连失败通知.用户必须调用close关闭socket,
                                                   否则会存在socket资源泄漏. */
    SFE_SOCK_NOTIFY_RCVFIN,                     /* 4  TCP收到FIN通知(连接建立成功之后通知该事件)
                                                   (1)TCP重排socket两个相关联的socket都可能会通知该事件.用户收到该通知后
                                                      必须负责搬迁完socket缓冲区中的所有数据后通知协议栈数据搬迁完毕.不能
                                                      调用close接口.
                                                   (2)TCP透明代理socket和标准TCP socket,在本端被动断连时可能会通知该事件.
                                                      在本端主动断连时不会通知该事件.产品收到该事件后可以选择性搬迁数据,
                                                      处理完后必须调用close接口关闭socket,否则会存在socket资源泄漏.*/
    SFE_SOCK_NOTIFY_RCVRST,                     /* 5  TCP收到RST通知(连接建立成功之后通知该事件)
                                                   (1)TCP重排socket两个相关联的socket都可能会通知该事件..用户收到该通知后
                                                      必须负责搬迁完socket缓冲区中的所有数据后通知协议栈数据搬迁完毕.不能
                                                      调用close接口.
                                                   (2)TCP透明代理socket和标准TCP socket,在本端被动断连时可能会通知该事件.
                                                      在本端主动断连时不会通知该事件.产品收到该事件后可以选择性搬迁数据,
                                                      处理完后必须调用close接口关闭socket,否则会存在socket资源泄漏.*/
    SFE_SOCK_NOTIFY_DISCONNECTED,               /* 6  TCP断连完成通知(连接建立成功之后通知该事件)
                                                   (1)TCP重排两个相关联的socket只会通知一次断连完成事件.socket资源由VISP释放.
                                                   (2)TCP透明代理两个相关联的socket各自独立,会分别通知断连完成事件.
                                                   (3)标准TCP socket会通知断连完成事件.
                                                      对于VISP主动断连通知用户断连完成时,用户必须调用close接口关闭socket以释放资源.
                                                      对于用户主动调用close接口后VISP通知断连完成事件,此时用户已调用close,VISP已释放资源,
                                                      所以用户不能再调用close.
                                                   (4)正常断连完成和异常断连完成都通知该事件.VISP主动断连完成也通知该事件. */
    SFE_SOCK_NOTIFY_WRITE,                      /* 7  TCP发送缓冲区有空间可以发送数据通知.
                                                   (1)当用户调用发送接口由于发送缓冲区空间不够而不能发送时,后续协议栈空间扩
                                                   大后会通知该事件. */
    SFE_SOCK_NOTIFY_READ,                       /* 8  接收数据通知
                                                   (1)TCP有数据需要用户接收时通知;
                                                   (2)UDP有数据需要用户接收时通知; */
    SFE_SOCK_NOTIFY_UDP_REORDER_CREATE,         /* 9  协议栈主动创建新的UDP重排连接socket */
    SFE_SOCK_NOTIFY_UDP_REORDER_DELETE,         /* 10 协议栈主动删除UDP重排连接socket
                                                   (1)只在协议栈主动删除UDP重排socket时通知,用户主动调用close接口关闭时
                                                      不通知; */
    SFE_SOCK_NOTIFY_POLICY_NOT_MATCH_SOCK,      /* 11 产品在三层入口下发的报文处理策略和SOCK中记录的策略不一致,通知产品异常事件,需要产品主动断链 */
    SFE_SOCK_NOTIFY_MAX,
}SFE_SOCK_NOTIFY_E;

/*STRUCT<传输层socket回调通知信息>*/
typedef struct tagSFE_SOCK_NOTIFY_INFO
{
    UINT32 u32NotifyType;                         /* 通知类型 */
    UINT32 u32VcpuId;                             /* 核号 */
    UINT32 u32ConnectionId;                       /* 连接id */
    UINT32 u32Direction;                          /* 连接方向:上行,下行 */
    INT32  i32Fd;                                 /* socket id */
    INT32  i32RelativeFd;                         /* 相关联的socket id,用于TCP重排,TCP透明代理 */
    UINT32 u32LocalIP;                            /* 本地地址,报文中的目的地址(网络字节序) */
    UINT32 u32RemoteIP;                           /* 远端地址,报文中的源地址(网络字节序) */
    UINT16 u16LocalPort;                          /* 本地端口,报文中的目的端口(网络字节序) */
    UINT16 u16RemotePort;                         /* 远端端口,报文中的源端口(网络字节序) */
    UINT8  u8Protocol;                            /* 协议号 */
    UINT8  u8Reserved[1];                         /* 保留字段 */
    UINT16 u16VrfIndex;                           /* VPN ID */
}SFE_SOCK_NOTIFY_INFO_S;

/*******************************************************************************
*    Func Name: g_pfSfeSockNotifyHook
* Date Created: 2010-06-04
*       Author: w60786
*      Purpose: 传输层socket信息回调通知产品的钩子函数原型
*  Description: 传输层socket信息回调通知产品的钩子函数原型
*        Input: SFE_MBUF_S *pstMBuf: 只有在SFE_SOCK_NOTIFY_RCVSYN和
*                   SFE_SOCK_NOTIFY_UDP_REORDER_CREATE通知时MBUF参数才有效但产品只能访问MBUF不能修改MBUF任何内容,
*                   其余情况都为NULL,产品不能使用MBUF.<非空>
*               SFE_SOCK_NOTIFY_INFO_S *pstNotifyInfo:回调通知消息内容,不同
                   的消息类型该通知消息中的有效字段可能不同.通知类型详见SFE_SOCK_NOTIFY_E结构体。<非空>
*       Output: 
*       Return: 成功返回: 0
*               失败返回: 其它
*      Caution: 1.产品不能在钩子函数中对报文MBUF做任何修改,只能在收到第一个SYN事件时,
*                 从MBUF中获取相关信息,当前为产品自有数据FCB信息。
*               2.产品只有在处理收到的第一个SYN报文时,同步创建连接表.产品会在收到第一个SYN
*                 通知时创建产品流表,如果这时使用异步方式创建则在VISP透传SYN
*                 报文时向产品获取报文发送信息时会失败,所以这里产品需要同步创建流表.
*                 但是产品只能在这一种情况下采用同步方式，其它情况下要使用异步方式处理.
*        Since: DOPRA VISP V2R3C02
*    Reference: SFE_RegFuncSockTransNotifyHook
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-04   w60786             Create
*
*******************************************************************************/
typedef UINT32 (*g_pfSfeSockNotifyHook)(SFE_MBUF_S *pstMBuf, SFE_SOCK_NOTIFY_INFO_S *pstNotifyInfo);

/*******************************************************************************
*    Func Name: SFE_RegFuncSockNotifyHook
* Date Created: 2010-06-04
*       Author: w60786
*      Purpose: 注册传输层socket回调函数钩子
*  Description: 注册传输层socket回调函数钩子
*        Input: g_pfSfeSockTransNotifyHook pfRegFunc:待注册的钩子函数指针 <非空>
*       Output: 
*       Return: 成功: 0
*               失败: 其它
*      Caution: 
*        Since: DOPRA VISP V2R3C02
*    Reference: g_pfSfeSockNotifyHook
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-04   w60786             Create
*
*******************************************************************************/
UINT32 SFE_RegFuncSockNotifyHook(g_pfSfeSockNotifyHook pfRegFunc);

/*******************************************************************************
*    Func Name: g_pfSfeGetSocketIdHook
* Date Created: 2010-06-04
*       Author: w60786
*      Purpose: 根据产品连接ID和报文上下行属性向产品获取socket id,以提高socket匹配查找性能.
*  Description: 根据产品连接ID和报文上下行属性向产品获取socket id,以提高socket匹配查找性能.
*        Input: SFE_MBUF_S *pstMbuf: 报文MBUF指针 <非空>
*               UINT32 u32ConnectionId: 产品连接ID <任意值>
*               UINT32 u32Direction: 报文上下行属性
*               <参见SFE_PKT_NO_DIRECTION_FLOW宏定义>
*       Output: INT32 *pi32Fd: 接收该报文的socket id <大于0>
*       Return: 成功: 0
*               失败: 其它
*      Caution: 产品必须保证该函数返回成功时socket id是有效值.
*               当找不到对应socket时必须返回非0的错误码值.
*        Since: DOPRA VISP V2R3C02
*    Reference:
*
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-04   w60786                  Create
*
*******************************************************************************/
typedef UINT32 (*g_pfSfeGetSocketIdHook)(SFE_MBUF_S *pstMbuf, UINT32 u32ConnectionId,
                                               UINT32 u32Direction, INT32 *pi32Fd);

/*******************************************************************************
*    Func Name: SFE_RegFuncGetSocketIdHook
* Date Created: 2010-06-04
*       Author: w60786
*      Purpose: 注册根据产品连接ID和报文上下行属性向产品获取socket id的函数
*  Description: 注册根据产品连接ID和报文上下行属性向产品获取socket id的函数
*        Input: g_pfSfeGetSocketIdHook pfRegFunc:待注册的钩子函数指针 <非空>
*       Output: 
*       Return: 成功: 0
*               失败: 其它
*      Caution: 
*        Since: DOPRA VISP V2R3C02
*    Reference:
*
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-04   w60786                  Create
*
*******************************************************************************/
extern UINT32 SFE_RegFuncGetSocketIdHook(g_pfSfeGetSocketIdHook pfRegFunc);

/*******************************************************************************
*    Func Name: SFE_Socket
* Date Created: 2010-06-04
*       Author: wudingyuan 00110679
*      Purpose: 创建一个新的SOCKET
*  Description: 创建一个新的SOCKET
*        Input: INT32 i32Family:      协议族 < SFE_AF_INET>
*               INT32 i32Type:        插口类型 <SFE_SOCK_STREAM或SFE_SOCK_DGRAM>
*               INT32 i32Protocol:    协议类型 <SFE_IPPROTO_TCP或SFE_IPPROTO_UDP>
*       Output: 
*       Return: 成功: 新建的socket描述符,即socket id
*               失败: 负数错误码
*      Caution: 
*        Since: DOPRA VISP V2R3C02
*    Reference: SFE_Bind
*               SFE_Listen
*               SFE_Connect
*               SFE_SetSocketOpt
*               SFE_GetSocketOpt
*               SFE_Close
*               SFE_RecvZMbuf
*               SFE_SendZMbuf
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-04   wudingyuan 110679             Create
*
*******************************************************************************/
INT32 SFE_Socket(INT32 i32Family, INT32 i32Type, INT32 i32Protocol);

/*******************************************************************************
*    Func Name: SFE_Bind
* Date Created: 2010-06-04
*       Author: wudingyuan 00110679
*      Purpose: socket绑定
*  Description: 把一SOCKET与一地址及端口绑定
*        Input: INT32 i32Fd:                    Socket描述符 <大于0>
*               SFE_SOCKADDRIN_S *pstSockAddr:  指向SFE_SOCKADDRIN_S结构的指针,指定欲绑定的地址和端口 <非0>
*               INT32 i32AddrLen:               SFE_SOCKADDRIN_S结构的长度 <非0>
*       Output: 
*       Return: 成功: 0
*               失败: 负数错误码
*      Caution: 1.当前支持SFE_SO_REUSEADDR,SFE_SO_REUSEPORT选项下可以同一端口绑定不同的地址
*        Since: DOPRA VISP V2R3C02
*    Reference: SFE_Socket
*               SFE_Listen
*               SFE_Connect
*               SFE_SetSocketOpt
*               SFE_GetSocketOpt
*               SFE_Close
*               SFE_RecvZMbuf
*               SFE_SendZMbuf
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-04   wudingyuan 110679             Create
*
*******************************************************************************/
INT32 SFE_Bind(INT32 i32Fd, SFE_SOCKADDRIN_S *pstSockAddr, INT32 i32AddrLen);

/*******************************************************************************
*    Func Name: SFE_Listen
* Date Created: 2010-06-04
*       Author: wudingyuan 00110679
*      Purpose: socket侦听
*  Description: 侦听对端的连接
*        Input: INT32 i32Fd: Socket描述符 <大于0>
*               INT32 i32BackLog: 插口的排队等待的连接个数门限 <[0,5]>
*       Output: 
*       Return: 成功: 0
*               失败: 负数错误码
*      Caution: 参数u32BackLog的取值范围：0～5(SFE_SOMAXCONN)。如用户输入值大于5时取5，用户输入的值小于0时取0
*        Since: DOPRA VISP V2R3C02
*    Reference: SFE_Socket
*               SFE_Bind
*               SFE_Connect
*               SFE_SetSocketOpt
*               SFE_GetSocketOpt
*               SFE_Close
*               SFE_RecvZMbuf
*               SFE_SendZMbuf
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-04   wudingyuan 110679             Create
*
*******************************************************************************/
INT32 SFE_Listen(INT32 i32Fd, INT32 i32BackLog);

/*******************************************************************************
*    Func Name: SFE_Connect
* Date Created: 2010-06-04
*       Author: wudingyuan 00110679
*      Purpose: socket连接
*  Description: 向对端发送连接请求
*        Input: INT32 i32Fd:                   Socket描述符 <大于0>
*               SFE_SOCKADDRIN_S *pstSockAddr:  指向SFE_SOCKADDRIN_S结构的指针,指定欲连接的远端地址和端口 <非空>
*               INT32 i32AddrLen:              SFE_SOCKADDRIN_S结构的长度 <非0>
*       Output: 
*       Return: 成功: 0
*               失败: 负数错误码
*      Caution: 
*        Since: DOPRA VISP V2R3C02
*    Reference: SFE_Socket
*               SFE_Bind
*               SFE_Listen
*               SFE_SetSocketOpt
*               SFE_GetSocketOpt
*               SFE_Close
*               SFE_RecvZMbuf
*               SFE_SendZMbuf
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-04   wudingyuan 110679             Create
*
*******************************************************************************/
INT32 SFE_Connect(INT32 i32Fd, SFE_SOCKADDRIN_S *pstSockAddr, INT32 i32AddrLen);

/*******************************************************************************
*    Func Name: SFE_SetSocketOpt
* Date Created: 2010-06-04
*       Author: wudingyuan 00110679
*      Purpose: 设置socket属性
*  Description: 设置socket属性
*        Input: INT32 i32Fd:       Socket描述符 <大于0>
*               INT32 i32Level:    级别 <SFE_SOL_SOCKET,SFE_IPPROTO_IP,SFE_IPPROTO_TCP>
*               INT32 i32OptName:  选项名称 <SFE_SO_ACCEPTCONN, SFE_SO_REUSEADDR,SFE_SO_KEEPALIVE,
*                   SFE_SO_LINGER,SFE_SO_REUSEPORT,SFE_SO_SETKEEPALIVE,SFE_SO_UDPCHECKSUM,SFE_SO_SNDBUF,
*                   SFE_SO_SNDLOWAT,SFE_SO_RCVLOWAT,SFE_SO_RCVBUF>
*               CHAR *pcOptVal:   选项值       <非空>
*               INT32 i32OptLen:   选项值长度   <非0>
*       Output: 
*       Return: 成功: 0
*               失败: 负数错误码
*      Caution: 
*        Since: DOPRA VISP V2R3C02
*    Reference: SFE_Socket
*               SFE_Bind
*               SFE_Listen
*               SFE_Connect
*               SFE_GetSocketOpt
*               SFE_Close
*               SFE_RecvZMbuf
*               SFE_SendZMbuf
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-04   wudingyuan 110679             Create
*
*******************************************************************************/
INT32 SFE_SetSocketOpt(INT32 i32Fd, INT32 i32Level, INT32 i32OptName,
                       CHAR *pcOptVal, INT32 i32OptLen);

/*******************************************************************************
*    Func Name: SFE_GetSocketOpt
* Date Created: 2010-06-04
*       Author: wudingyuan 00110679
*      Purpose: 获取socket属性
*  Description: 获取socket属性
*        Input: INT32 i32Fd:       Socket描述符 <大于0>
*               INT32 i32Level:    级别  <SFE_SOL_SOCKET,SFE_IPPROTO_IP,SFE_IPPROTO_TCP>
*               INT32 i32OptName:  选项名称 <SFE_SO_ACCEPTCONN, SFE_SO_REUSEADDR,SFE_SO_KEEPALIVE,
*                   SFE_SO_LINGER,SFE_SO_REUSEPORT,SFE_SO_SETKEEPALIVE,SFE_SO_UDPCHECKSUM,SFE_SO_SNDBUF,
*                   SFE_SO_SNDLOWAT,SFE_SO_RCVLOWAT,SFE_SO_RCVBUF>
*       Output: CHAR *pcOptVal:   选项值   <非空>
*               INT32 *pi32OptLen: 选项值长度 <非空>
*       Return: 成功: 0
*               失败: 负数错误码
*      Caution: 
*        Since: DOPRA VISP V2R3C02
*    Reference: SFE_Socket
*               SFE_Bind
*               SFE_Listen
*               SFE_Connect
*               SFE_SetSocketOpt
*               SFE_Close
*               SFE_RecvZMbuf
*               SFE_SendZMbuf
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-04   wudingyuan 110679             Create
*
*******************************************************************************/
INT32 SFE_GetSocketOpt(INT32 i32Fd, INT32 i32Level, INT32 i32OptName,
                       CHAR *pcOptVal, INT32 *pi32OptLen);

/*******************************************************************************
*    Func Name: SFE_Ioctl
* Date Created: 2010-06-04
*       Author: wudingyuan 00110679
*      Purpose: 设置或获取socket的各IO方面属性
*  Description: 设置或获取socket的各IO方面属性
*        Input: INT32 i32Fd:       Socket描述符 <大于0>
*               UINT32 u32ReqType: 要设置的选项类型 <SFE_FIOASYNC>
*               CHAR *pcValue:   指向传入或传出数据的指针,不同的选项有不同的含义. <非空>
*       Output: 
*       Return: 成功: 0
*               失败: 负数错误码
*      Caution: 
*        Since: DOPRA VISP V2R3C02
*    Reference: SFE_Socket
*               SFE_Bind
*               SFE_Listen
*               SFE_Connect
*               SFE_SetSocketOpt
*               SFE_GetSocketOpt
*               SFE_RecvZMbuf
*               SFE_SendZMbuf

*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-04   wudingyuan 110679             Create
*
*******************************************************************************/
INT32 SFE_Ioctl(INT32 i32Fd, UINT32 u32ReqType, CHAR *pcValue);

/*******************************************************************************
*    Func Name: SFE_Close
* Date Created: 2010-06-04
*       Author: wudingyuan 00110679
*      Purpose: 关闭SOCKET
*  Description: 关闭SOCKET
*        Input: INT32 i32Fd: Socket描述符 <大于0>
*       Output: 
*       Return: 成功: 0
*               失败: 负数错误码
*      Caution: 1.该接口只适用于标准socket和透明代理socket和UDP重排socket,
*                 TCP重排socket不能使用该接口
*               2.从DOPRA IP V2R3C06SPC100起TCP重排socket可以使用该接口删除
*                 socket节点,但不会主动发送任何报文
*        Since: DOPRA VISP V2R3C02
*    Reference: SFE_Socket
*               SFE_Bind
*               SFE_Listen
*               SFE_Connect
*               SFE_SetSocketOpt
*               SFE_GetSocketOpt
*               SFE_RecvZMbuf
*               SFE_SendZMbuf
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-04   wudingyuan 110679             Create
*
*******************************************************************************/
INT32 SFE_Close(INT32 i32Fd);

/*******************************************************************************
*    Func Name: SFE_RecvZMbuf
* Date Created: 2010-06-04
*       Author: wudingyuan 00110679
*      Purpose: 零拷贝方式接收数据
*  Description: 零拷贝方式接收数据,一次将接收缓冲区中的所有数据接收完毕
*        Input: INT32 i32Fd:            Socket描述符    <大于0>
*               SFE_MBUF_S **ppstMBuf:  接收到的数据MBUF内存地址 <非空>
*       Output: UINT32 *pu32Len: 接收的数据长度 <非空>
*       Return: 成功: 0
*               失败: 其它
*      Caution: 1.对于TCP(标准TCP,透明代理),当前接收缓冲区中也可能是一个MBUF链,
*                 但是一个MBUF并不一定对应一个报文。
*               2.对于UDP和TCP重排，一个报文对应一个MBUF，多个报文构成MBUF链。
*               3.用户每次接收时协议栈会将当前接收缓冲区中的所有数据交给用户。
*               4.接收时socket缓冲区无数据返回特定的错误,产品如果要对于该情况进行区别对待,
*                 则产品只能使用该错误码的宏名SFE_SOCK_RECV_ZMBUF_NO_DATA不能直接使用其值,
*                 因为后续VISP可能会调整宏值,但是会保证宏名不变.
*               5.对于从重排socket接收的数据,产品不能修改MBUF中的内容,特别别是不能进行MBUF操作处理,只能访问MBUF中的信息。
*        Since: DOPRA VISP V2R3C02
*    Reference: SFE_Socket
*               SFE_Bind
*               SFE_Listen
*               SFE_Connect
*               SFE_SetSocketOpt
*               SFE_GetSocketOpt
*               SFE_Close
*               SFE_SendZMbuf
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-04   wudingyuan 110679             Create
*
*******************************************************************************/
UINT32 SFE_RecvZMbuf(INT32 i32Fd, SFE_MBUF_S **ppstMBuf, UINT32 *pu32Len);

/*******************************************************************************
*    Func Name: SFE_SendZMbuf
* Date Created: 2010-06-04
*       Author: wudingyuan 00110679
*      Purpose: 零拷贝方式发送数据
*  Description: 零拷贝方式发送数据
*        Input: INT32 i32Fd:           Socket描述符 <大于0>
*               SFE_MBUF_S **ppstMBuf: 待发送的MBUF(输出时为剩余未发送的MBUF数据，
*                                      如果为NULL表示报文已被发送完毕，否则表示还有部分数据未发送) <非空>
*               UINT32 *pu32Len:       待发送的数据长度，如果不指定待发送长度（值为0），则表示发送整个MBUF
*                                      (输出时为实际发送了的数据长度)<非空>
*               SFE_SOCKADDRIN_S *pstSockAddr: 发送UDP报文时指定的目的地.TCP不需要指定直接传入NULL即可. <见描述>
*               INT32 i32AddrLen: 发送UDP报文时指定的目的地址长度.TCP不需要指定直接传入0即可.   <见描述>
*       Output: 
*       Return: 成功: 0
*               失败: 其它
*      Caution: 1.对于TCP,产品可以指定发送当前MBUF中的部分数据.TCP重排不能发送MBUF中的部分数据.
*               2.对于UDP和TCP重排,产品每次只能发送一个MBUF，不能以MBUF链的形式发送；
*                 并且每次发送的是整个MBUF,不能发送MBUF中的部分数据。
*               3.UDP未进行连接时发送报文必须指定发送目的地.UDP进行了连接时即远端地址信息已经确定时不能指定发送目的地.
*                 当前标准UDP只支持不连接在发送时指定目的地址的方式.
*                 TCP发送数据时不能指定目的地址.
*               4.如果不指定发送地址则必须将pstSockAddr字段填NULL且i32AddrLen字段填0.
*               5.对于从重排socket接收的数据，产品不能修改MBUF中的内容,特别别是不能进行MBUF操作处理,
*                 只能访问MBUF中的信息.
*               6.无论该接口发送成功还是失败,产品都必须判断输入输出参数ppstMBuf,
*                 当该函数返回时如果输出的报文指针不为NULL则报文由产品负责缓存或释放;
*                 如果输出的报文指针为NULL则表示VISP已经将报文发送或者释放.
*        Since: DOPRA VISP V2R3C02
*    Reference: SFE_Socket
*               SFE_Bind
*               SFE_Listen
*               SFE_Connect
*               SFE_SetSocketOpt
*               SFE_GetSocketOpt
*               SFE_Close
*               SFE_RecvZMbuf
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-04   wudingyuan 110679       Create
*
*******************************************************************************/
UINT32 SFE_SendZMbuf(INT32 i32Fd, SFE_MBUF_S **ppstMBuf, UINT32 *pu32Len,
                     SFE_SOCKADDRIN_S *pstSockAddr, INT32 i32AddrLen);

/*******************************************************************************
*    Func Name: SFE_SetConnectionInfo
* Date Created: 2010-06-04
*       Author: w60786
*      Purpose: 设置socket对应的产品信息,包括连接id和socket的上下行属性
*  Description: 设置socket对应的产品信息,包括连接id和socket的上下行属性
*        Input: INT32 i32Fd: socket id  <大于0>
*               UINT32 u32ConnectionId: 产品连接id <任意值>
*               UINT32 u32Direction: socket上下行属性
*               <参见SFE_PKT_NO_DIRECTION_FLOW宏定义>
*       Output: 
*       Return: 成功: 0
*               失败: 其它
*      Caution: 
*        Since: DOPRA VISP V2R3C02
*    Reference:
*
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-04   w60786                  Create
*
*******************************************************************************/
UINT32 SFE_SetConnectionInfo(INT32 i32Fd, UINT32 u32ConnectionId, UINT32 u32Direction);

/*******************************************************************************
*    Func Name: SFE_SetSocketGlobalDebugSwitch
* Date Created: 2010-08-26
*       Author: zhangchi(00142640)
*      Purpose: 设置全部SOCKET调试开关
*  Description: 设置全部SOCKET调试开关
*        Input: UINT32 u32Switch: 开关<0:关闭;1:打开>
*       Output: 
*       Return: 成功: 0
*               失败: 其它
*      Caution: 
*        Since: DOPRA VISP V2R3C02
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-08-26   zhangchi(00142640)      Create the first version.
*
*******************************************************************************/
UINT32 SFE_SetSocketGlobalDebugSwitch(UINT32 u32Switch);

/*******************************************************************************
*    Func Name: SFE_SetSocketDebugSwitchByFd
* Date Created: 2010-08-26
*       Author: zhangchi(00142640)
*      Purpose: 设置单个SOCKET调试开关
*  Description: 设置单个SOCKET调试开关
*        Input: INT32 i32Fd: socket id<大于0>
*               UINT32 u32Switch: 开关<0:关闭;1:打开>
*       Output:
*       Return: 成功: 0
*               失败: 其它
*      Caution: 
*        Since: DOPRA VISP V2R3C02
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-08-26   zhangchi(00142640)      Create the first version.
*
*******************************************************************************/
UINT32 SFE_SetSocketDebugSwitchByFd(INT32 i32Fd, UINT32 u32Switch);

/*******************************************************************************
*    Func Name: SFE_ShowSocketByFd
* Date Created: 2010-08-26
*       Author: zhangchi(00142640)
*      Purpose: 显示指定socket的信息
*  Description: 显示指定socket的信息
*        Input: INT32 i32Fd:socket id<大于0>
*               UINT32 u32IsShowVerbose: 详细信息级别,级别越高信息越多.
*               <参见SFE_SOCK_SHOW_BASIC_INFO等宏定义>
*       Output: 
*       Return: VOID
*      Caution: 
*        Since: DOPRA VISP V2R3C02
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-08-26   zhangchi(00142640)      Create the first version.
*
*******************************************************************************/
VOID SFE_ShowSocketByFd(INT32 i32Fd, UINT32 u32IsShowVerbose);

/*******************************************************************************
*    Func Name: SFE_ShowAllTcpSocket
* Date Created: 2010-6-22
*       Author: w60786
*      Purpose: 显示所有TCP socket简要信息
*  Description: 显示所有TCP socket简要信息
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 如果socket太多会导致打印信息很多,该接口只用于调试定位
*        Since: DOPRA VISP V2R3C02
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-6-22    w60786           Creat the first version.
*
*******************************************************************************/
VOID SFE_ShowAllTcpSocket(VOID);

/*******************************************************************************
*    Func Name: SFE_ShowAllTcpSocketVerbose
* Date Created: 2010-6-22
*       Author: w60786
*      Purpose: 显示所有TCP socket详细信息
*  Description: 显示所有TCP socket详细信息
*        Input: UINT32 u32IsShowVerbose: 详细信息级别,级别越高信息越多.
*               <参见SFE_SOCK_SHOW_BASIC_INFO等宏定义>
*       Output: 
*       Return: VOID
*      Caution: 如果socket太多会导致打印信息很多,该接口只用于调试定位
*        Since: DOPRA VISP V2R3C02
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-6-22    w60786           Creat the first version.
*
*******************************************************************************/
VOID SFE_ShowAllTcpSocketVerbose(UINT32 u32IsShowVerbose);

/*******************************************************************************
*    Func Name: SFE_ShowAllTcpSocketNum
* Date Created: 2010-08-26
*       Author: zhangchi(00142640)
*      Purpose: 显示TCP socket计数信息
*  Description: 显示TCP socket计数信息
*        Input: UINT32 u32IsShowVerbose: 详细信息级别,级别越高信息越多.
*               <参见SFE_SOCK_SHOW_BASIC_INFO等宏定义>
*       Output: 
*       Return: VOID
*      Caution: 
*        Since: DOPRA VISP V2R3C02
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-08-26   zhangchi(00142640)      Create the first version.
*
*******************************************************************************/
VOID SFE_ShowAllTcpSocketNum(UINT32 u32IsShowVerbose);

/*******************************************************************************
*    Func Name: SFE_ShowAllUdpSocket
* Date Created: 2010-6-22
*       Author: w60786
*      Purpose: 显示所有UDP socket简要信息
*  Description: 显示所有UDP socket简要信息
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 如果socket太多会导致打印信息很多,该接口只用于调试定位
*        Since: DOPRA VISP V2R3C02
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-6-22    w60786           Creat the first version.
*
*******************************************************************************/
VOID SFE_ShowAllUdpSocket(VOID);

/*******************************************************************************
*    Func Name: SFE_ShowAllUdpSocketVerbose
* Date Created: 2010-6-22
*       Author: w60786
*      Purpose: 显示所有UDP socket详细信息
*  Description: 显示所有UDP socket详细信息
*        Input: UINT32 u32IsShowVerbose: 详细信息级别,级别越高信息越多.
*               <参见SFE_SOCK_SHOW_BASIC_INFO等宏定义>
*       Output: 
*       Return: VOID
*      Caution: 如果socket太多会导致打印信息很多,该接口只用于调试定位
*        Since: DOPRA VISP V2R3C02
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-6-22    w60786           Creat the first version.
*
*******************************************************************************/
VOID SFE_ShowAllUdpSocketVerbose(UINT32 u32IsShowVerbose);

/*******************************************************************************
*    Func Name: SFE_ShowAllUdpSocketNum
* Date Created: 2010-08-26
*       Author: zhangchi(00142640)
*      Purpose: 显示UDP socket计数信息
*  Description: 显示UDP socket计数信息
*        Input: UINT32 u32IsShowVerbose: 详细信息级别,级别越高信息越多.
*               <参见SFE_SOCK_SHOW_BASIC_INFO等宏定义>
*       Output: 
*       Return: VOID
*      Caution: 
*        Since: DOPRA VISP V2R3C02
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-08-26   zhangchi(00142640)      Create the first version.
*
*******************************************************************************/
VOID SFE_ShowAllUdpSocketNum(UINT32 u32IsShowVerbose);

/*******************************************************************************
*    Func Name: SFE_SOCK_GetPoolTotalAndFreeUnitNum
* Date Created: 2012-05-03
*       Author: zhaoyue00171897
*      Purpose: 获取SOCK资源池总的和剩余的单元数
*  Description: 获取SOCK资源池总的和剩余的单元数
*        Input: 
*       Output: UINT32 *pu32TotalUnitNum:SOCK资源池总的单元数
*               UINT32 *pu32FreeUnitNum:SOCK资源池剩余的单元数
*       Return: 成功:SFE_SOCK_OK
*               失败:错误码
*      Caution: 该接口要在系统启动完成后调用才能生效
*        Since: DOPRA IP V200R003C06SPC100
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-05-03   zhaoyue00171897         Create
*
*******************************************************************************/
UINT32 SFE_SOCK_GetPoolTotalAndFreeUnitNum(UINT32 *pu32TotalUnitNum, UINT32 *pu32FreeUnitNum);

/*******************************************************************************
*    Func Name: SFE_GetSockName
* Date Created: 2012-05-16
*       Author: zhaoyue00171897
*      Purpose: 获取指定ID的socket对应的本地协议地址和端口
*  Description: 获取指定ID的socket对应的本地协议地址和端口
*        Input: INT32 i32Fd:Socket描述符
*               INT32 *pi32AddrLen:SFE_SOCKADDRIN_S结构的长度指针
*       Output: SFE_SOCKADDRIN_S *pstSockAddr:查出的本地地址结果
*               INT32 *pi32AddrLen:SFE_SOCKADDRIN_S结构的长度指针
*       Return: 成功:SFE_SOCK_OK
*               失败:错误码
*      Caution: 该接口要在系统启动完成后调用才能生效
*        Since: DOPRA IP V200R003C06SPC100
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-05-16   zhaoyue00171897         Create
*
*******************************************************************************/
INT32 SFE_GetSockName(INT32 i32Fd, SFE_SOCKADDRIN_S *pstSockAddr, INT32 *pi32AddrLen);

#ifdef  __cplusplus
}
#endif

#endif

