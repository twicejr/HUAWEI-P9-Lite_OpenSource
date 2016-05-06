/*******************************************************************************
*
*
*                Copyright 2010, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sfe_tcp_api.h
*
*  Project Code: V1.1.0
*   Module Name:
*  Date Created: 2010-6-9
*        Author: w60786
*   Description: tcp模块用户API头文件，定义用户需要使用的数据结构、宏和API原型
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2010-6-9     w60786           Creat the first version.
*
*******************************************************************************/
#ifndef _SFE_TCP_API_H_
#define _SFE_TCP_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif


/*ERRORCODE<数据面TCP模块错误码>*/
typedef enum enumSfeTcpErrCode
{
    SFE_TCP_OK = SFE_OK,                                    /* 操作成功 */
    SFE_TCP_ERR_BEGIN = SFE_TCP_BEGIN_RET_CODE,             /* 模块错误码起始值,建议内部不要使用该值 */

    SFE_TCP_GET_SFE_VCPU_MAX_NUM_PRECFG_FAIL,               /* 1  获取最大VCPU数量预配置值失败 */
    SFE_TCP_MALLOC_TCPCB_POOL_FAIL,                         /* 2  分配TCP控制块资源池失败 */
    SFE_TCP_MALLOC_SOCKTRANS_VCPU_FAIL,                     /* 3  获取VCPU数组失败 */
    SFE_TCP_MALLOC_SOCKTRANS_VRF_FAIL,                      /* 4  获取VRF数组失败 */
    SFE_TCP_MALLOC_SOCKTRANS_HASH_FIRESTLEVEL_FAIL,         /* 5  获取一级HASH数组失败 */
    SFE_TCP_MALLOC_SOCKTRANS_HASH_SECONDLEVEL_FAIL,         /* 6  获取二级HASHA数组失败 */
    SFE_TCP_ADD_NAMEDB_SOCKTRANS_VCPU_FAIL,                 /* 7  添加VCPU到共享名字库失败 */
    SFE_TCP_GET_DORFC1323_FLAG_PRECFG_FAIL,                 /* 8  获取tcp支持rfc1323选项的预配置失败*/
    SFE_TCP_MALLOC_TCPNOW_FAIL,                             /* 9  分配TCPNOW数组失败 */

    SFE_TCP_MALLOC_VCPU_SOCKTIMER_MEM_FAIL,                 /* 10 分配每个VCPU上的定时器资源失败 */
    SFE_TCP_CREATE_VCPU_200MS_TIMER_FAIL,                   /* 11 创建每个VCPU上的200ms定时器失败 */
    SFE_TCP_CREATE_VCPU_500MS_TIMER_FAIL,                   /* 12 创建每个VCPU上的500ms定时器失败 */
    SFE_TCP_CREATE_VCPU_LONG_TIMER_FAIL,                    /* 13 创建每个VCPU上的10min定时器失败 */
    SFE_TCP_ADD_NAMEDB_VCPU_SOCKTIMER_FAIL,                 /* 14 添加定时器资源到名字共享库失败 */
    SFE_TCP_GET_SFE_TCP_REORDER_REASS_NUM_PRECFG_FAIL,      /* 15  获取TCP重排的乱序重组队列规模的预配置值失败 */
    SFE_TCP_GET_SFE_TCP_REORDER_REASS_CACHE_NUM_PRECFG_FAIL,/* 16 获取TCP重排的乱序重组重复缓存规模的预配置值失败 */

    SFE_TCP_SOCK_TYPE_INVAILD_FREESOCK,                     /* 17 释放socket以进行TCP重排放通时,socket节点类型不是TCP重排 */
    SFE_TCP_PREPROCESS_HEADERLEN_INVALID,                   /* 18 接收TCP报文预处理函数中TCP头长度不合法  */
    SFE_TCP_RCVACK_NO_ACK,                                  /* 19 接收TCP报文ACK处理时,报文ACK标志没有置位  */
    SFE_TCP_RCVACK_SYN_RECEIVED_ACKSEQ_INVALID,             /* 20 接收TCP报文ACK处理时,收到的三次握手最后一个ACK序号错误  */
    SFE_TCP_RCVACK_DUPLICATE_ACK_LESS_THAN_THREE,           /* 21 接收TCP报文ACK处理时,收到重复ACK且重复次数不大于3  */
    SFE_TCP_RCVACK_DUPLICATE_ACK_MORE_THAN_THREE,           /* 22 接收TCP报文ACK处理时,收到重复ACK且重复次数大于3  */
    SFE_TCP_RCVACK_DROP_OLD_ACK,                            /* 23 接收TCP报文ACK处理时,收到一个很老的ACK */
    SFE_TCP_RCVACK_LAST_ACK,                                /* 24 接收TCP报文ACK处理时,收到最后一个ACK */
    SFE_TCP_RCVACK_AT_TIME_WAIT,                            /* 25 接收TCP报文ACK处理时,TIME WAIT状态收到ACK */
    SFE_TCP_HEADERFLAG_INVALID,                             /* 26 TCP标志位不合法 */
    SFE_TCP_CHECKSUM_FAIL,                                  /* 27 TCP校验和检查时出错 */
    SFE_TCP_DROP_TAIL_DATA_FAILED,                          /* 28 TCP预处理时发现IP包长度小于mbuf总长度,删除mbuf尾部多余失败 */
    SFE_TCP_NO_RLTVSOCKCB_CREATEPROXY,                      /* 29 代理或重排连接创建时，获取关联socket控制块不存在 */
    SFE_TCP_REORDEROUT_MBUFBACKWARD_FAIL,                   /* 30 TCP重排输出时MBUF指针归位失败 */
    SFE_TCP_SOCK_TYPE_INVAILD_DATATRANSOVER,                /* 31 通知TCP重排数据搬迁完毕时,socket节点类型不是TCP重排 */
    SFE_TCP_NO_TCPCB_DATATRANSOVER,                         /* 32 通知TCP重排数据搬迁完毕时,没有TCPCB控制块 */
    SFE_TCP_NO_RLTVSOCKCB_DATATRANSOVER,                    /* 33 通知TCP重排数据搬迁完毕时,获取的关联SOCK控制块非法 */
    SFE_TCP_NO_RLTVTCPCB_DATATRANSOVER,                     /* 34 通知TCP重排数据搬迁完毕时,没有关联TCPCB控制块 */
    SFE_TCP_NO_CACHEPKT_DATATRANSOVER,                      /* 35 通知TCP重排数据搬迁完毕时,无缓存的断连请求报文 */
    SFE_TCP_STATE_INVALID_DATATRANSOVER,                    /* 36 通知TCP重排数据搬迁完毕时,TCP重排socket的状态非法 */
    SFE_TCP_REODERIN_MBUFFORWARD_FAIL,                      /* 37 TCP重排接收报文时,偏移掉TCPIP头时出错 */
    SFE_TCP_REODERIN_OVER_WINDOW,                           /* 38 TCP重排接收报文时,报文超出窗口 */
    SFE_TCP_CFG_TYPE_INVAILD_IOCTL,                         /* 39 配置ioctl时配置类型ID不支持或非法 */
    SFE_TCP_CFG_FIOASYN_PARA_INVAILD_IOCTL,                 /* 40 配置ioctl SFE_FIOASYNC时配置参数值非法 */
    SFE_TCP_FREE_SOCKET_VCPUID_INVALID,                     /* 41 释放socket节点时,获取vcpu无效 */
    SFE_TCP_VCPUID_INVALID_DATATRANSOVER,                   /* 42 重排数据传输完成时,获取vcpu无效 */
    SFE_TCP_REASS_INPUT_MBUF_VALID,                         /* 43 TCP重组时输入报文非法 */
    SFE_TCP_REASS_MBUFFORWARD_FAIL,                         /* 44 TCP重组时报文头偏移到数据区时失败 */
    SFE_TCP_REASS_DISCONNECT_NODATA,                        /* 45 TCP重组时, 上送数据发现断链报文且没有数据, 做断链处理,
                                                                    释放重组队列和重组缓存 */
    SFE_TCP_REASS_DISCONNECT,                               /* 46 TCP重组时, 上送数据发现断链报文, 做断链处理,
                                                                    释放重组队列和重组缓存 */
    SFE_TCP_REASS_NUM_FULL,                                 /* 47 TCP重排的重组时,乱序重组队列满 */
    SFE_TCP_REODERREASSIN_CACHE_NUM_FULL,                   /* 48 TCP重排的重组时,乱序重组重复缓存满*/
    SFE_TCP_REODERREASSIN_MBUFFORWARD_FAIL,                 /* 49 TCP重排的乱序重组队列发现重复报文入重复缓存处理,
                                                                    做尾部数据偏移还原时失败 */
    SFE_TCP_QUENCH,                                         /* 50 为SFE_TCP_Quench函数定义的错误码 */
    SFE_TCP_FIRSTFORECAST_FAILD,                            /* 51 TCP接收报文处理,首部预测不成功 */
    SFE_TCP_RCVRST_SEQ_ERR,                                 /* 52 TCP接收报文处理,RST报文处理,报文序号不对 */
    SFE_TCP_NEWCONNECT_GET_NEW_SOCKTRANSCB_FAILED,          /* 53 TCP接收报文处理,被动新建TCP连接时获取新的SockTransCB失败 */
    SFE_TCP_FILLHEADER_MOVE_BACK_MBUF_HEAD_FAILED,          /* 54 TCP发送报文处理,填充报文头时,将MBUF数据指针向后移动TCP/IP头长度过程失败 */
    SFE_TCP_STANDARDINPUT_GET_SOCKTRANSCB_FAILED,           /* 55 TCP接收报文处理,标准处理过程中,显示代理处理部分获取SockTransCB失败 */
    SFE_TCP_STANDARDINPUT_TCP_CLOSED,                       /* 56 TCP接收报文处理,标准处理过程中,连接已经断连,但是用户还没有关闭该socket */
    SFE_TCP_DATAPREPROCESS_DROP_DUPSYN,                     /* 57 TCP接收报文处理,数据预处理,显示代理场景下丢弃建链完成后收到的SYN报文 */
    SFE_TCP_DATAPREPROCESS_DROP_DUPRST,                     /* 58 TCP接收报文处理,数据预处理,丢弃重复的RST报文 */
    SFE_TCP_DATAPREPROCESS_DROP_SEQ_ERR_DATARST,            /* 59 TCP接收报文处理,数据预处理,带部分重复数据的RST报文,只要RST报文不是期望的接收序号直接回ACK后丢弃 */
    SFE_TCP_DATAPREPROCESS_RCVDATA_AFTER_CLOSE,             /* 60 TCP接收报文处理,数据预处理,用户已经主动调用了close函数关闭socket,又收到数据报文 */
    SFE_TCP_DATAPREPROCESS_DROP_DATA_EXCEED_WINDOW,         /* 61 TCP接收报文处理,数据预处理,收到完全超出接收窗口的报文 */
    SFE_TCP_DATAPREPROCESS_DROP_DATA_EXCEED_WINDOW_AFTER_ESTABLISHED,  /*  62  TCP接收报文处理,数据预处理,连接建立完成后的完全超出接收窗口的报文 */
    SFE_TCP_RCVSYN_RCVRST_AT_LISTEN,                        /* 63 TCP接收报文处理,显示代理收到SYN处理,LISTEN状态收到RST报文 */
    SFE_TCP_RCVSYN_RCVACK_AT_LISTEN,                        /* 64 TCP接收报文处理,显示代理收到SYN处理,LISTEN状态收到ACK报文 */
    SFE_TCP_RCVSYN_RCVNOSYN_AT_LISTEN,                      /* 65 TCP接收报文处理,显示代理收到SYN处理,LISTEN状态收到不带SYN标志的报文 */
    SFE_TCP_RCVSYN_RCVDSTMULTICAST_AT_LISTEN,               /* 66 TCP接收报文处理,显示代理收到SYN处理,LISTEN状态收到广播或者多播报文 */
    SFE_TCP_RCVSYN_INVALID_ACK_AT_SYN_SENT,                 /* 67 TCP接收报文处理,显示代理收到SYN处理,SYN SENT状态收到错误的ACK报文 */
    SFE_TCP_RCVSYN_RCVRST_AT_SYN_SENT,                      /* 68 TCP接收报文处理,显示代理收到SYN处理,SYN SENT状态收到RST报文 */
    SFE_TCP_RCVSYN_RCVNOSYN_AT_SYN_SENT,                    /* 69 TCP接收报文处理,显示代理收到SYN处理,SYN SENT状态收到不带SYN标志的报文 */
    SFE_TCP_RCVSYN_RCVRST_AT_SYN_SENT_DROPTCP,              /* 70 TCP建链处理,发出SYN报文后收到RST报文,建链失败,丢弃连接 */
    SFE_TCP_SYNRCV_STATE_RCV_INVALID_SYN_DROPTCP,           /* 71 TCP建链处理,收到SYN报文后又收到非法(非重复)的SYN报文,建链失败,丢弃连接 */

    SFE_TCP_CREATEBYCOPYBUF_ENOBUFS_ALLOCPACKET,            /* 72 TCP发送创建MBuf,通过拷贝缓存创建MBuf,没有BUF可用 */
    SFE_TCP_CREATEMBUF_ENOBUFS_ALLOCPACKET,                 /* 73 TCP发送创建MBuf,创建MBuf,没有BUF可用 */

    SFE_TCP_TCPT_PERSIST_ETIMEDOUT,                         /* 74 TCP定时器超时,坚持定时器超时,超过一定时间断开连接 */
    SFE_TCP_TCPT_ESTABLIST_ETIMEDOUT,                       /* 75 TCP定时器超时,保活定时器超时,连接建立时超时 */
    SFE_TCP_TCPT_KEEP_SET_ETIMEDOUT,                        /* 76 TCP定时器超时,保活定时器超时,用户设置了保活定时器的值 */
    SFE_TCP_TCPT_KEEP_DEFAULT_ETIMEDOUT,                    /* 77 TCP定时器超时,保活定时器超时,默认保活定时器的值 */
    SFE_TCP_TCPT_KEEP_NO_KEEPALIVE,                         /* 78 TCP定时器超时,保活定时器超时,没设置keep alive选项 */
    SFE_TCP_TCPT_REXMT_ETIMEDOUT,                           /* 79 TCP定时器超时,超时重传定时器超时 */
    SFE_TCP_GET_TCPREORDER_KEEPALIVE_TM_SWITCH_FAILD,       /* 80 TCP重传保活定时器开关状态获取失败 */

    SFE_TCP_REORDER_FILLHEADER_MBUFHEAD_BACKWARD_FAILED,    /* 81 TCP重排主动发送报文MBUF后向偏移到首部时失败*/
    SFE_TCP_REORDER_FILLHEADER_MBUFHEAD_FORWARD_FAILED,     /* 82 TCP重排主动发送报文MBUF前向偏移过首部时失败*/

    SFE_TCP_REORDER_SEND_NULL_POINTER,                      /* 83 TCP重排主动发送输出时MBUF指针为空 */
    SFE_TCP_REORDER_SEND_DATALEN_INVALID,                   /* 84 TCP重排主动发送输出时MBUF长度无效 */
    SFE_TCP_REORDER_SEND_MBUF_DB_RESERVE_NOTENOUGH,         /* 85 TCP重排主动发送输出时MBUF首部预留长度不足128字节 */
    SFE_TCP_REORDER_SEND_VCPUID_INVALID,                    /* 86 TCP重排主动发送输出时获取的VCPUID非法 */
    SFE_TCP_REORDER_SEND_SOCKTYPE_INVALID,                  /* 87 TCP重排主动发送输出时socket类型非法 */
    SFE_TCP_REORDER_SEND_FILL_TCPIPHEAD_FAILED,             /* 88 TCP重排主动发送输出时填充tcpip首部时失败 */
    SFE_TCP_REORDER_CLOSE_VCPUID_INVALID,                   /* 89 TCP重排主动发送RST断链时获取的VCPUID非法 */
    SFE_TCP_REORDER_CLOSE_SOCKTYPE_INVALID,                 /* 90 TCP重排主动发送RST断链时获取的socktrans主节点不是tcp重排的 */
    SFE_TCP_REORDER_CLOSE_SOCKRLTVTYPE_INVALID,             /* 91 TCP重排主动发送RST断链时获取的socktrans副节点不是tcp重排的 */
    SFE_TCP_PROXYCREATE_NOSOCK_AND_NOTSYNPKT,               /* 92 TCP重排或透明代理建立时收到的报文没有对应socket接收并且不是SYN报文 */
    SFE_TCP_FREESOCKET_MODULE_NOT_INIT,                     /* 93 TCP重排调用主动释放socket接口时模块还没有初始化 */
    SFE_TCP_REORDER_DATA_TRANSFER_COMPLETE_MODULE_NOT_INIT, /* 94 TCP重排调用数据搬迁接口时模块还没有初始化 */
    SFE_TCP_REORDER_ACTIVE_SEND_PKT_MODULE_NOT_INIT,        /* 95 TCP重排调用主动发送报文接口时模块还没有初始化 */
    SFE_TCP_REORDER_CLOSE_SOCKET_MODULE_NOT_INIT,           /* 96 TCP重排调用主动关闭接口时模块还没有初始化 */
    SFE_TCP_PROXY_NOTIFY_RCVSYN_FAIL,                       /* 97 TCP代理或重排建连时通知收到SYN事件产品处理返回失败 */
    SFE_TCP_GET_CHSUM_FLAG_PRECFG_FAIL,                     /* 98 获取TCP校验和预配置失败 */
    SFE_TCP_STANDARDINPUT_TCPCB_IS_NULL,                    /* 99 标准TCP接收处理入口TCPCB为NULL */
    SFE_TCP_CREATEPROXY_TCPCB_IS_NULL,                      /* 100 创建代理或重排Socket节点时,TCPCB为NULL */
    SFE_TCP_CREATEPROXY_RELATIVE_TCPCB_IS_NULL,             /* 101 创建代理或重排Socket节点时,关联的TCPCB为NULL */
    SFE_TCP_PREPROCESS_MBUF_CONTINUOUS_FAIL,                /* 102 将MBUF中的DB连续化失败 */
    SFE_TCP_REORDER_CLOSE_SOCKID_NOT_MATCH,                 /* 103 TCP重排调用主动关闭接口输入的两个SOCKET ID未关联的 */
    SFE_TCP_MALLOC_TCPREORDER_CURSTAT_FAIL,                 /* 104 TCP初始化时分配TCP重排记录当前采样内存失败 */
    SFE_TCP_MALLOC_TCPREORDER_PRESTAT_FAIL,                 /* 105 TCP初始化时分配TCP重排记录前次采样内存失败 */
    SFE_TCP_MALLOC_TCPREORDER_VCPU_SAMPLENOTIFY_CONNDLY_FAIL,/* 106 TCP初始化时分配TCP重排时延采样记录的内存失败*/
    SFE_TCP_MALLOC_TCPREORDER_CURALLCONNECTS_FAIL,          /* 107 TCP初始化时分配TCP重排并发连接采样记录的内存失败 */
    SFE_TCP_MALLOC_TCPREORDER_SAMPLEGEN_FAIL,               /* 108 TCP初始化时分配TCP重排采样组号内存失败 */
    SFE_TCP_MALLOC_TCPREORDER_SAMPLEPARA_FAIL,              /* 109 TCP初始化时分配TCP重排采样参数内存失败 */
    SFE_TCP_MALLOC_TCPREORDER_SAMPLETIMER_MEM_FAIL,         /* 110 TCP初始化时分配TCP重排采样定时器内存失败 */
    SFE_TCP_CREATE_TCPREORDER_SAMPLETIMER_INTERVALTIMER_FAIL,/* 111 TCP初始化时创建采样间隔定时器失败 */
    SFE_TCP_CREATE_TCPREORDER_SAMPLETIMER_STEPTIMER_FAIL,   /* 112 TCP初始化时创建采样时长定时器失败 */
    SFE_TCP_ADD_NAMEDB_TCPREORDER_SAMPLETIMER_FAIL,         /* 113 TCP初始化时添加采样定时器到共享内存失败 */
    SFE_TCP_ERR_SAMPLEOUTPUT_POINTNULL,                     /* 114 TCP重排采样回调钩子注册失败,注册钩子为空 */
    SFE_TCP_REORDER_SET_SAMPLE_INFO_MODULE_NOT_INIT,        /* 115 TCP重排采样设置时系统未初始化 */
    SFE_TCP_REORDER_SET_SAMPLE_INFO_VCPUID_INVALID,         /* 116 TCP重排采样设置时获取的当前核号非法 */
    SFE_TCP_REORDER_ENABLE_SAMPLE_INPUTPARA_INVALID,        /* 117 TCP重排采样设置时,使能采样时输入参数不合法 */
    SFE_TCP_REORDER_SET_SAMPLEINFO_INPUTPARA_INVALID,       /* 118 TCP重排采样设置时输入参数不合法 */
    SFE_TCP_REORDER_SET_SAMPLE_INPUT_PARAPOINT_NULL,        /* 119 TCP重排采样设置时输入参数的指针为空 */
    SFE_TCP_REODERIN_IS_REDIRECTION,                        /* 120 TCP重排做了重定向后特殊处理 */
    SFE_TCP_REORDER_SEND_SOCKTRANSRLTV_INVALID,             /* 121 TCP重排做重定向时获取对端节点非法 */
    SFE_TCP_REODERIN_IS_REDIRECTION_AOC_CACHEPKT_NULL,      /* 122 TCP重排做了重定向后控制块缓冲报文为空 */
    SFE_TCP_REORDER_SEND_MBUF_NO_DIRECTION,                 /* 123 TCP重排重定向时传入报文没有填入上下行方向 */
    SFE_TCP_REORDER_REDIRECTION_CREATE_RST_FAILED,          /* 124 TCP重排重定向后发送RST报文创建失败 */
    SFE_TCP_REORDER_REDIRECTION_FILL_RST_HEADER_FAILED,     /* 125 TCP重排重定向后发送RST报文填TCP头失败 */
    SFE_TCP_REORDER2PROXY_MODULE_NOT_INIT,                  /* 126 系统未初始化就执行TCP重排转透明代理失败 */
    SFE_TCP_REORDER2PROXY_INVALID_PARA,                     /* 127 TCP重排转透明代理传入socketID非法 */
    SFE_TCP_REORDER2PROXY_VCPUID_INVALID,                   /* 128 TCP重排转透明代理核号非法 */
    SFE_TCP_REORDER2PROXY_SOCKET_NOT_MATCH,                 /* 129 TCP重排转透明代理传入socket不匹配 */
    SFE_TCP_REORDER2PROXY_CID_NOT_MATCH,                    /* 130 TCP重排转透明代理传入CID不匹配 */
    SFE_TCP_REORDER2PROXY_UENODE_MODE_NOT_MATCH,            /* 131 TCP重排转透明代理传入模拟UE模式非法 */
    SFE_TCP_REORDER2PROXY_SPNODE_MODE_NOT_MATCH,            /* 132 TCP重排转透明代理传入模拟SP模式非法 */
    SFE_TCP_REORDER2PROXY_NOT_ESTABLISH_STATE,              /* 133 TCP重排转透明代理传入socket未建连成功 */
    SFE_TCP_REORDER2PROXY_HAVE_SENT_DATA,                   /* 134 TCP重排转透明代理,上层转发过数据 */
    SFE_TCP_REORDER2PROXY_HAVE_SENT_302_DATA,               /* 135 TCP重排转透明代理,上层做过重排的302重定向 */
    SFE_TCP_REODERIN_RCV_DUPPKT_BEFORE_POLICY_SURE,         /* 136 TCP重排模式下上层未决定是否要转透明代理,收到重传报文 */
    SFE_TCP_INPUT_REORDER_SOCK_RCV_NOT_MATCH_POLICY_PKT,    /* 137 TCP重排模式下收到的报文策略不是重排,退出 */
    SFE_TCP_STANDARDINPUT_RCV_PKT_POLICY_NOT_MATCH,         /* 138 TCP代理模式下收到的报文策略不匹配,退出 */
    SFE_TCP_GET_UPDATEWND_FLAG_PRECFG_FAIL,                 /* 139 TCP初始化时获取接收缓存读取后立即窗口通告的预配置,失败退出 */
    SFE_TCP_GET_UPDATE_ZEROWND_FLAG_PRECFG_FAIL,            /* 140 TCP初始化时获取部分超窗报文立即0窗口通告的预配置,失败退出 */
    SFE_TCP_REORDEROUT_MBUFNOTCPHDR_FAIL,                   /* 141 TCP重排下从MBUF中获取接收时设置的TCP头为空,失败退出 */
    SFE_TCP_RCVACK_DROP_ACK_TOOMUCH,                        /* 142 TCP代理接收TCP报文ACK处理时,收到一个对未发送数据的ACK*/
    SFE_TCP_REORDER2PROXY_GET_UENODE_FAILED,                /* 143 TCP重排转透明代理获取对端socket节点失败 */
    SFE_TCP_MALLOC_FAIL_TCPSTAT,                            /* 144 初始化时分配TCP统计共享变量空间失败 */
    SFE_TCP_FIRSTFORECAST_FAILD_PUREACK,                    /* 145 纯ACK报文首部预测失败 */
    SFE_TCP_FIRSTFORECAST_FAILD_REASSPKT,                   /* 146 当前报文不能触发乱序队列上送,首部预测失败 */
    SFE_TCP_GET_POOLUNITNUM_BEFORE_INIT,                    /* 147 在系统初始化前,不能获取到TCP资源池统计 */
    SFE_TCP_GET_POOLUNITNUM_INPUT_PARA_INVALID,             /* 148 获取TCP资源池统计时,输入的参数判断失败 */
    SFE_TCP_GET_POOLUNITNUM_INPUT_FAILED,                   /* 149 获取TCP资源池统计时,获取到的空闲单元数非法*/
    SFE_TCP_GET_MSL_TIME_PRECFG_FAIL,                       /* 150 TCP初始化时获取MSL老化超时时间的预配置,失败退出 */
    SFE_TCP_GET_DELAYED_ACK_SWITCH_PRECFG_FAIL,             /* 151 TCP初始化时获取延迟ACK开关的预配置,失败退出 */    
    SFE_TCP_REORDER_REDIRECTION_HAVE_BEEN_CALLED,           /* 152 TCP重排已做重定向 */
    SFE_TCP_REASSRXMT_CNT_PRECFG_FAIL,                      /* 153 获取TCP重排乱序报文优化处理:复制乱序包转发的连续重传次数的预配置值失败DTS2012110907656 l00177467*/
    SFE_TCP_MALLOC_SOCKTRANS_HASH_EXACT_FAIL,               /* 154 获取HASH数组失败，用本端端口、本端IP、远端端口、远端IP、VRF来计算索引 */
    SFE_TCP_MALLOC_SOCKTRANS_HASH_LPORT_FAIL,               /* 155 获取HASH数组失败，用本端端口来计算索引 */
}SFE_TCP_ERR_CODE_E;

/*MACRO<可以进行TCP粘连处理>*/
#define SFE_TCP_CAN_SPLICE   1
/*MACRO<不可以进行TCP粘连处理>*/
#define SFE_TCP_CAN_NOT_SPLICE 0

/*******************************************************************************
*    Func Name: SFE_TCP_IsCanSplice
* Date Created: 2010-06-04
*       Author: w60786
*      Purpose: 查询是否可以进行TCP粘连处理
*  Description: 查询是否可以进行TCP粘连处理
*        Input: INT32 i32UeFd:与UE相关联的socket id(即模拟SP socket id)<大于0>
*               INT32 i32SpFd:与SP相关联的socket id(即模拟UE socket id)<大于0>
*       Output: UINT32 *pu32IsCanSplice:是否可以进行粘连
*       Return: 成功: 0
*               失败: 其它
*      Caution: 1.当前不支持该接口功能,这里只是保留API接口定义
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
UINT32 SFE_TCP_IsCanSplice(INT32 i32UeFd, INT32 i32SpFd, UINT32 *pu32IsCanSplice);

/*******************************************************************************
*    Func Name: SFE_TCP_Splice
* Date Created: 2010-06-04
*       Author: w60786
*      Purpose: TCP粘连处理
*  Description: TCP粘连处理
*        Input: INT32 i32UeFd:与UE相关联的socket id(即模拟SP socket id)<大于0>
*               INT32 i32SpFd:与SP相关联的socket id(即模拟UE socket id)<大于0>
*               UINT32 u32ConnectionId:产品的连接id,VISP处理时不解析直接透传该值给产品.
*       Output: 
*       Return: 成功: 0
*               失败: 其它
*      Caution: 1.当前不支持该接口功能,这里只是保留API接口定义
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
UINT32 SFE_TCP_Splice(INT32 i32UeFd, INT32 i32SpFd, UINT32 u32ConnectionId);

/*MACRO<TCP粘连成功 >*/
#define SFE_TCP_SPLICE_SUCCESS      0
/*MACRO<TCP粘连失败 >*/
#define SFE_TCP_SPLICE_FAIL         1

/*STRUCT<TCP粘连回调通知信息 >*/
typedef struct tagSFE_TCP_SPLICE_NOTIFY_INFO
{
    UINT32 u32TcpSpliceType;                       /* TCP粘连类型 */
    UINT32 u32ConnectionId;                        /* 连接id */
    UINT32 u32TcpSpliceResult;                     /* TCP粘连结果:
                                                      (1)取值如下: TCP粘连成功: SFE_TCP_SPLICE_SUCCESS
                                                                   TCP粘连失败: SFE_TCP_SPLICE_FAIL
                                                      (2)只有在粘连成功时后续参数才有效. */
    /* 透明代理粘连处理参数 */
    INT32  i32UeToSpSeqDiff;                       /* UE到SP报文的序号差值 */
    INT32  i32UeToSpAckSeqDiff;                    /* UE到SP报文的ack序号差值 */
    INT32  i32SpToUeSeqDiff;                       /* SP到UE报文的序号差值 */
    INT32  i32SpToUeAckSeqDiff;                    /* SP到UE报文的ack序号差值 */

    /* 透明代理重定向后进行粘连处理的特殊参数,以下参数仅对重定向后的粘连有效. */
    UINT32 u32OldMss;                              /* 重定向前原连接的MSS值 */
    UINT32 u32NewMss;                              /* 重定向后新连接的MSS值 */
    UINT32 u32UeWndScale;                          /* UE端窗口缩放因子值 */
    UINT32 u32LocalWndScale;                       /* 本地窗口缩放因子值 */
    UINT32 u32OldSpWndScale;                       /* 原SP端窗口缩放因子值 */
    UINT32 u32NewSpWndScale;                       /* 新SP端窗口缩放因子值 */
    UINT32 u32Res;                                 /* 保留字段 */
}SFE_TCP_SPLICE_NOTIFY_INFO_S;

/*******************************************************************************
*    Func Name: g_pfSfeTcpSpliceCompleteNotifyHook
* Date Created: 2010-06-04
*       Author: w60786
*      Purpose: TCP粘连完成后回调通知产品粘连信息的钩子函数原型
*  Description: TCP粘连完成后回调通知产品粘连信息的钩子函数原型
*        Input: SFE_TCP_SPLICE_NOTIFY_INFO_S *pstNotifyInfo:回调通知消息内容,不同
                   的消息类型该通知消息中的有效字段可能不同.
*       Output: 
*       Return: 成功: 0
*               失败: 其它
*      Caution: 
*        Since: DOPRA VISP V2R3C02
*    Reference: SFE_RegFuncTcpSpliceNotifyHook
*
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-04   w60786                  Create
*
*******************************************************************************/
typedef UINT32 (*g_pfSfeTcpSpliceCompleteNotifyHook)(SFE_TCP_SPLICE_NOTIFY_INFO_S *pstNotifyInfo);

/*******************************************************************************
*    Func Name: SFE_RegFuncTcpSpliceNotifyHook
* Date Created: 2010-06-04
*       Author: w60786
*      Purpose: 注册TCP粘连回调函数
*  Description: 注册TCP粘连回调函数
*        Input: g_pfSfeTcpSpliceCompleteNotifyHook pfRegFunc:TCP粘连完成后通知钩子 <非空>
*       Output: 
*       Return: 成功: 0
*               失败: 其它
*      Caution: 1.当前不支持该接口功能,这里只是保留API接口定义
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
UINT32 SFE_RegFuncTcpSpliceNotifyHook(g_pfSfeTcpSpliceCompleteNotifyHook pfRegFunc);

/* 用户态采样宏:采样使能控制,使能 */
#define SFE_TCP_REORDER_SAMPLE_ENABLE           1
/* 用户态采样宏:采样使能控制,去使能 */
#define SFE_TCP_REORDER_SAMPLE_DISABLE          0

/* 用户态采样宏:连接速率,并发连接 */
#define SFE_TCP_REORDER_SAMPLE_CONNINFO         0x01
/* 用户态采样宏:建连时延 */
#define SFE_TCP_REORDER_SAMPLE_CONNDELAY        0x02
/* 用户态采样宏:所有指标包括建连速率,并发连接,建连时延 */
#define SFE_TCP_REORDER_SAMPLE_ALL              0x03

/* 用户态采样宏:采样间隔最小值 */
#define SFE_TCP_REORDER_SAMPLE_INTERVAL_MIN     10
/* 用户态采样宏:采样间隔最大值 */
#define SFE_TCP_REORDER_SAMPLE_INTERVAL_MAX     3600
/* 用户态采样宏:采样时长最小值 */
#define SFE_TCP_REORDER_SAMPLE_STEP_MIN         1
/* 用户态采样宏:采样时长最大值 */
#define SFE_TCP_REORDER_SAMPLE_STEP_MAX         50
/* 用户态采样宏:采样次数最小值 */
#define SFE_TCP_REORDER_SAMPLE_COUNT_MIN        1
/* 用户态采样宏:采样次数最大值 */
#define SFE_TCP_REORDER_SAMPLE_COUNT_MAX        50

/*STRUCT<TCP重排采样设置参数 >*/
typedef struct tagSFE_TCP_REORDER_SAMPLE_PARA
{
    UINT32  u32Switch;                      /* 采样开关,是否使能采样<SFE_TCP_REORDER_SAMPLE_DISABLE, SFE_TCP_REORDER_SAMPLE_ENABLE> */
    UINT32  u32Type;                        /* 采样类型,包括:建连速率和并发数,建连时延,两类都采<SFE_TCP_REORDER_SAMPLE_CONNINFO, SFE_TCP_REORDER_SAMPLE_ALL> */
    UINT32  u32Interval;                    /* 采样间隔<SFE_TCP_REORDER_SAMPLE_INTERVAL_MIN, SFE_TCP_REORDER_SAMPLE_INTERVAL_MAX>, 单位秒
                                               采样间隔内按照设置的采样时长和采样次数采样,即采样时长x采样次数小于采样间隔 */
    UINT32  u32Step;                        /* 采样时长<SFE_TCP_REORDER_SAMPLE_STEP_MIN, SFE_TCP_REORDER_SAMPLE_STEP_MAX>, 单位秒 */
    UINT32  u32Count;                       /* 采样次数<SFE_TCP_REORDER_SAMPLE_COUNT_MIN, SFE_TCP_REORDER_SAMPLE_COUNT_MAX> */
    UINT32  u32Resv;
}SFE_TCP_REORDER_SAMPLE_PARA_S;

/*STRUCT<TCP采样回调通知信息:建连速率和并发连接 >*/
typedef struct tagSFE_TCP_REORDER_SAMPLE_NOTIFY_CONN_INFO
{
    UINT32  u32VcpuId;                      /* 当前所在核号 */
    UINT32  u32Resv;
    UINT64  u64CurAllConnects;              /* 当前的TCP并发连接数,指状态处于establish的所有连接 */
    UINT32  u32TcpConnectedPS;              /* 每秒成功TCP建连数,指每秒状态转为establish的连接 */
    UINT32  u32TcpConnectingPS;             /* 每秒尝试TCP建连的连接数,包括成功建链和仍在建链的连接 */
    UINT32  u32TcpClosedCPS;                /* 每秒成功关闭的TCP连接数,指每秒成功释放socket资源的连接数 */
    UINT32  u32TcpClosingCPS;               /* 每秒尝试关闭的TCP连接数,指每秒从establish状态转出的连接数 */
    UINT64  u64TcpConnectingPPS;            /* 每秒输入的TCP建连报文数,指每秒处于建连状态连接接收到的所有报文数 */
    UINT64  u64TcpDupPPS;                   /* 每秒输入的TCP重传报文数 */
    UINT64  u64TcpDupBPS;                   /* 每秒输入的TCP重传字节数 */
    UINT64  u64TcpOOPPS;                    /* 每秒输入的TCP乱序报文数 */
    UINT64  u64TcpOOBPS;                    /* 每秒输入的TCP乱序字节数 */
    UINT32  u32CurSysTime;                  /* 当前输出采样结果时的系统时间,单位毫秒 */
    UINT32  u32CurSysCpuRate;               /* 当前输出采样结果时的CPU占用率 */
}SFE_TCP_REORDER_SAMPLE_NOTIFY_CONN_INFO_S;

/*STRUCT<TCP采样回调通知信息:建连时延 >*/
typedef struct tagSFE_TCP_REORDER_SAMPLE_NOTIFY_DELAY_INFO
{
    UINT32  u32VcpuId;                      /* 当前所在核号 */
    UINT32  u32TcpConnDelayMax;             /* 当前采样时长TCP连接建链最大时延,单位毫秒 */
    UINT32  u32TcpConnDelayMin;             /* 当前采样时长TCP连接建链最小时延,单位毫秒 */
    UINT32  u32TcpConnDelayAvg;             /* 当前采样时长TCP连接建链平均时延,单位毫秒 */
    UINT32  u32CurSysTime;                  /* 当前输出采样结果时的系统时间,单位毫秒 */
    UINT32  u32CurSysCpuRate;               /* 当前输出采样结果时的CPU占用率 */
}SFE_TCP_REORDER_SAMPLE_NOTIFY_DELAY_INFO_S;

/*******************************************************************************
*    Func Name: SFE_SetTcpReorderSampleInfo
* Date Created: 2011-02-22
*       Author: z00166124
*      Purpose: 
*  Description: 设置数据面用户态TCP重排采样方式和采样参数
*        Input: SFE_TCP_REORDER_SAMPLE_PARA_S* pstSamplePara:设置的采样参数指针
*       Output: 
*       Return: 成功返回 0
*               失败返回 错误码
*      Caution: 1.每次只能运行一个采样实例:建连速率和并发连接采样,或建连时延采样,或全部采样.
*               2.当前运行的采样需要自行手动去使能后,才能执行下一次的采样
*               3.设置采样操作必须在系统初始化完成后执行.
*        Since: DOPRA VISP V2R3C03
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-02-22   z00166124               Create
*
*******************************************************************************/
UINT32 SFE_SetTcpReorderSampleInfo(SFE_TCP_REORDER_SAMPLE_PARA_S* pstSamplePara);

/*******************************************************************************
*    Func Name: g_pfSfeTcpReorderSampleOutputHook
* Date Created: 2011-02-22
*       Author: z00166124
*      Purpose: 
*  Description: 数据面用户态重排采样结果输出给产品的钩子
*        Input: UINT32 u32Type:采样类型 <SFE_TCP_REORDER_SAMPLE_CONNINFO,SFE_TCP_REORDER_SAMPLE_CONNDELAY>
*               VOID *pstSampleStatInfo:采样结果指针<非空>
*       Output: N/A
*       Return: 成功返回 0
*               失败返回 错误码
*      Caution: 1.用户需要根据采样类型解析输出结果
*        Since: DOPRA VISP V2R3C03
*    Reference: 
*
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-02-22   z00166124               Create
*
*******************************************************************************/
typedef UINT32 (*g_pfSfeTcpReorderSampleOutputHook)(UINT32 u32Type, VOID *pstSampleStatInfo);

/*******************************************************************************
*    Func Name: SFE_RegFuncTcpSampleOutputHook
* Date Created: 2011-02-22
*       Author: z00166124
*      Purpose: 
*  Description: 注册数据面用户态采样输出钩子
*        Input: g_pfSfeTcpReorderSampleOutputHook pfRegFunc:待注册的钩子函数指针 <非空>
*       Output: 
*       Return: 成功返回 0
*               失败返回 错误码
*      Caution: 
*        Since: DOPRA VISP V2R3C03
*    Reference: 
*
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-02-22   z00166124               Create
*
*******************************************************************************/
UINT32 SFE_RegFuncTcpSampleOutputHook(g_pfSfeTcpReorderSampleOutputHook pfRegFunc);

/*STRUCT< TCP重定向参数 >*/
typedef struct tagSFE_TCP_REDIRECTION_INFO
{
    INT32  i32SpFd;         /* 与原SP相关联的socket id(即模拟UE socket id) */
    UINT32 u32ConnectionId; /* 产品的连接id */
    UINT32 u32Direction;    /* socket上下行属性 */
    UINT32 u32LocalIpAddr;  /* 重定向后新SP socket的本地地址,用户必须指定该参数 */
    UINT16 u16LocalPort;    /* 重定向后新SP socket的本地端口号,用户可以不指定该参数,
                               当用户指定该值为0时,协议栈会自动为其分配一个本地端口号. */
    UINT32 u32NewSpIpAddr;  /* 重定向后新SP的地址(即新SP socket的远端地址) */
    UINT16 u16NewSpPort;    /* 重定向后新SP的端口号(即新SP socket的远端端口号) */
}SFE_TCP_REDIRECTION_INFO_S;

/*******************************************************************************
*    Func Name: SFE_TCP_Redirection
* Date Created: 2010-06-04
*       Author: w60786
*      Purpose: TCP重定向处理
*  Description: TCP重定向处理
*        Input: SFE_TCP_REDIRECTION_INFO_S *pstTcpRedirectionInfo: TCP重定向信息.<非空>
*               INT32 *pi32NewSpFd: 重定向后与新SP相关联的socket id(即新的模拟UE socket id)<大于0>
*                注意:该socket在该函数返回时只是向新SP发起了建连,连接还处于建连过程中,
*                     当该socket建连完成后会通知产品建连完成，这时才能使能使用该socket收发数据
*       Output: 
*       Return: 成功: 0
*               失败: 其它
*      Caution: 1.当前不支持该接口功能,这里只是保留API接口定义
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
UINT32 SFE_TCP_Redirection(SFE_TCP_REDIRECTION_INFO_S *pstTcpRedirectionInfo,
                                  INT32 *pi32NewSpFd);

/*******************************************************************************
*    Func Name: SFE_TCP_ReorderToProxy
* Date Created: 2010-06-04
*       Author: w60786
*      Purpose: TCP重排socket转变为TCP透明代理socket
*  Description: TCP重排socket转变为TCP透明代理socket
*        Input: INT32 i32UeFd:与UE相关联的socket id(即模拟SP socket id)<大于0>
*               INT32 i32SpFd:与SP相关联的socket id(即模拟UE socket id)<大于0>
*               UINT32 u32ConnectionId:产品的连接id,VISP处理时不解析直接透传该值给产品.
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
UINT32 SFE_TCP_ReorderToProxy(INT32 i32UeFd, INT32 i32SpFd, UINT32 u32ConnectionId);

/*******************************************************************************
*    Func Name: SFE_TCP_ReorderDataTransferComplete
* Date Created: 2010-06-04
*       Author: w60786
*      Purpose: TCP重排socket数据搬迁完毕
*  Description: TCP重排socket数据搬迁完毕
*        Input: INT32 i32Fd: 收到断连请求通知的socket id <大于0>
*       Output: 
*       Return: 成功: 0
*               失败: 其它
*      Caution: 当VISP收到UE或SP的断连请求时通知产品,产品负责搬迁UE或SP的数据,
*               当数据搬迁完毕后通知VISP,VISP将之前缓存的断连请求报文透传给SP或UE.
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
UINT32 SFE_TCP_ReorderDataTransferComplete(INT32 i32Fd);

/*******************************************************************************
*    Func Name: SFE_TCP_ReorderActiveSendPktAndCloseSocket
* Date Created: 2010-06-04
*       Author: w60786
*      Purpose: TCP重排主动发送报文并关闭socket的特殊接口
*  Description: TCP重排主动发送报文并关闭socket的特殊接口
*        Input: INT32 i32Fd: TCP重排socket id <大于0>
*               SFE_MBUF_S *pstMBuf: 产品构造的待发送的数据报文.TCPIP头协议栈构造.<非空>
*       Output: 
*       Return: 成功返回 SFE_OK
*               失败返回 错误码
*      Caution: 1.只支持在连接建立完成状态下让产品主动发送报文,不允许在建连过程和断链过程中调用该接口.
*               2.只允许调用一次该接口,并且调用该接口时,VISP会先尝试发送数据,然后VISP内部直接发送RST到对端.
*               3.产品使用了该接口后,不能再调用主动RST断连的接口,后续重传和老化由VISP实现,老化由保活定时器实现(产品保证开启保活定时器).
*               4.该接口无论发送成功与否,报文都由VISP协议栈释放.
*               5.产品传入的MBUF数据区头部至少要预留128字节供协议栈添加头部信息使用.
*               6.产品传入的MBUF要保证已填入上下行方向,否则返回失败.
*               7.该接口只做了重定向报文发送和RST另外一端,在MBUF资源池耗尽时这两个动作会失败.
*        Since: V1R8C05
*    Reference:
*
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-04   w60786                  Create
*  2011-08-09   z00166124               Fixed
*
*******************************************************************************/
UINT32 SFE_TCP_ReorderActiveSendPktAndCloseSocket(INT32 i32Fd, SFE_MBUF_S *pstMBuf);

/*******************************************************************************
*    Func Name: SFE_TCP_ReorderCloseSocket
* Date Created: 2010-06-04
*       Author: w60786
*      Purpose: 主动关闭TCP重排socket
*  Description: 主动关闭TCP重排socket
*        Input: INT32 i32UeFd: TCP重排与UE相关联的socket id(即模拟SP socket id)<大于0>
*               INT32 i32SpFd: TCP重排与SP相关联的socket id(即模拟UE socket id)<大于0>
*       Output: 
*       Return: 成功: 0
*               失败: 其它
*      Caution: 1.该接口有条件尽量尝试发送RST报文(也可能发送不了RST报文)后,
*                 直接释放资源不通知产品断连完成.
*               2.该函数返回失败时socket没有释放.
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
UINT32 SFE_TCP_ReorderCloseSocket(INT32 i32UeFd, INT32 i32SpFd);

/*******************************************************************************
*    Func Name: SFE_TCP_FreeSocket
* Date Created: 2010-06-04
*       Author: w60786
*      Purpose: 释放TCP socket的所有相关资源但不发起断连,用于TCP重排放通
*  Description: 释放TCP socket的所有相关资源但不发起断连,用于TCP重排放通
*        Input: INT32 i32Fd:socket id <非0>
*       Output: 
*       Return: 成功: 0
*               失败: 其它
*      Caution: 1.当前该接口用于SCG产品的TCP重排放通功能.
*               2.该接口不进行(也不能进行)任何的通知.
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
UINT32 SFE_TCP_FreeSocket(INT32 i32Fd);

/* TCP统计结构 */
typedef struct tagSFETCPSTAT
{
    UINT64    u64Accepts;                                       /* 被动打开的连接数 */
    UINT64    u64Closed;                                        /* 关闭的连接数 (包括丢弃的连接) */
    UINT64    u64ConnAttempt;                                   /* 试图建立连接的次数(调用connect) */
    UINT64    u64ConnDrops;                                     /* 在连接建立阶段失败的连接次数(SYN收到之前) */
    UINT64    u64Connects;                                      /* 建连成功的次数 */
    UINT64    u64DelayedAck;                                    /* 延迟发送的ACK数 */
    UINT64    u64Drops;                                         /* 意外丢失的连接数(收到SYN之后) */
    UINT64    u64KeepDrops;                                     /* 在保活阶段丢失的连接数(已建立或正等待SYN) */
    UINT64    u64KeepProbe;                                     /* 保活探测探测报文发送次数 */
    UINT64    u64KeepTimeOut;                                   /* 保活定时器或者连接建立定时器超时次数 */
    UINT64    u64PAWSDrop;                                      /* 由于PAWS而丢失的报文数*/

    UINT64    u64PersistDrops;                                  /* 持续定时器超时次数达到最大值的次数 */
    UINT64    u64PersistTimeOut;                                /* 持续定时器超时次数*/
    UINT64    u64PredictionAck;                                 /* 对ACK报文首部预测的正确次数 */
    UINT64    u64PredictionData;                                /* 对数据报文首部预测的正确次数 */
    UINT64    u64RcvAckByte;                                    /* 由收到的ACK报文确认的发送字节数 */
    UINT64    u64RcvAckPacket;                                  /* 收到的ACK报文数 */
    UINT64    u64RcvAckTooMuch;                                 /* 收到对未发送数据进行的ACK报文数*/
    UINT64    u64RcvDupAck;                                     /* 收到的重复ACK数 */
    UINT64    u64RcvAfterClose;                                 /* 连接关闭后收到的报文数 */
    UINT64    u64RcvBadOff;                                     /* 收到的首部长度无效的报文数 */
    UINT64    u64RcvBadSum;                                     /* 收到的校验和错误的报文数 */
    UINT64    u64RcvByte;                                       /* 连续收到的字节数 */
    UINT64    u64RcvDupByte;                                    /* 完全重复报文中的重复字节数 */
    UINT64    u64RcvDupPacket;                                  /* 完全重复报文的报文数 */
    UINT64    u64RcvPacketAfterWnd;                             /* 携带数据超出滑动窗口通告值的报文数 */
    UINT64    u64RcvByteAfterWnd;                               /* 在滑动窗口已满时收到的字节数 */
    UINT64    u64RcvPartDupByte;                                /* 部分数据重复的报文重复字节数 */
    UINT64    u64RcvPartDupPacket;                              /* 部分数据重复的报文数 */
    UINT64    u64RcvOutOrderPacket;                             /* 收到失序的报文数 */
    UINT64    u64RcvOutOrderByte;                               /* 收到失序的字节数 */
    UINT64    u64RcvShort;                                      /* 长度过短的报文数 */
    UINT64    u64RcvTotal;                                      /* 收到的报文总数 */
    UINT64    u64RcvPacket;                                     /* 顺序接收的报文数 */
    UINT64    u64RcvWndProbe;                                   /* 收到的窗口探测报文数 */
    UINT64    u64RcvWndUpdate;                                  /* 收到的窗口更新报文数 */
    UINT64    u64RexmtTimeOut;                                  /* 重传超时次数 */
    UINT64    u64RTTUpdated;                                    /* RTT估算值更新次数 */
    UINT64    u64SegsTimed;                                     /* 可用于RTT测算的报文数 */
    UINT64    u64SndByte;                                       /* 发送的字节数 */
    UINT64    u64SndControl;                                    /* 发送的控制报文数(SYN FIN RST) */
    UINT64    u64SndPacket;                                     /* 发送的数据报文数(数据长度大于0) */
    UINT64    u64SndProbe;                                      /* 发送的窗口探测次数 */
    UINT64    u64SndRexmtByte;                                  /* 重传的数据字节数 */
    UINT64    u64SndAcks;                                       /* 发送的纯ACK报文数(数据长度为0) */
    UINT64    u64SndRexmtPacket;                                /* 重传的报文数 */
    UINT64    u64SndTotal;                                      /* 发送的报文总数 */

    UINT64    u64SndRST;                                        /* 发送的RST报文数 */
    UINT64    u64SndUrgent;                                     /* 只携带URG标志的报文数(数据长度为0) */
    UINT64    u64SndWndUpdate;                                  /* 只携带窗口更新信息的报文数 */
    UINT64    u64TimeOutDrop;                                   /* 由于重传超时而丢失的连接数 */
    UINT64    u64KeepAliveTimeOut;                              /* 保活定时器超时次数 */
    UINT64    u64KeepAliveDrops;                                /* 保活定时器在用户设置了保活定时器的值超时 */
}SFE_TCPSTAT_S;

/*******************************************************************************
*    Func Name: SFE_GetTCPStatist
* Date Created: 2012-04-05
*       Author: z00171897/h00177429
*      Purpose: 获取TCP统计信息
*  Description: 获取TCP统计信息
*        Input: UINT32 u32VcpuId: 核号
*               SFE_TCPSTAT_S *pstTCPStat: 保存TCP统计信息的内存
*       Output: SFE_TCPSTAT_S *pstTCPStat: 保存获取的TCP统计信息
*       Return: 成功:SFE_DEBUG_OK
*               失败:错误码
*      Caution: 仅在本核上使用该接口
*        Since: DOPRA IP V200R003C06SPC100
*    Reference:
*
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2012-04-05  z00171897/h00177429  Create the first version.
*
*******************************************************************************/
UINT32 SFE_GetTCPStatist(UINT32 u32VcpuId, SFE_TCPSTAT_S *pstTCPStat);

/*******************************************************************************
*    Func Name: SFE_ClrTCPStatist
* Date Created: 2012-04-05
*       Author: z00171897/h00177429
*      Purpose: 清除TCP统计信息
*  Description: 清除TCP统计信息
*        Input: UINT32 u32VcpuId: 核号
*       Output: 
*       Return: 成功:SFE_DEBUG_OK
*               失败:错误码
*      Caution: 入参必须为当前核号
*        Since: DOPRA IP V200R003C06SPC100
*    Reference:
*
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2012-04-05  z00171897/h00177429  Create the first version.
*
*******************************************************************************/
UINT32 SFE_ClrTCPStatist(UINT32 u32VcpuId);

/*******************************************************************************
*    Func Name: SFE_ShowTCPStatist
* Date Created: 2012-04-05
*       Author: z00171897/h00177429
*      Purpose: 显示TCP统计信息
*  Description: 显示TCP统计信息
*        Input: UINT32 u32VcpuId: 核号
*       Output: 
*       Return: 
*      Caution: 仅在本核上使用该接口
*        Since: DOPRA IP V200R003C06SPC100
*    Reference:
*
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2012-04-05  z00171897/h00177429  Create the first version.
*
*******************************************************************************/
VOID SFE_ShowTCPStatist(UINT32 u32VcpuId);

/*******************************************************************************
*    Func Name: SFE_ShowAllTCPStatist
* Date Created: 2012-04-18
*       Author: z00171897
*      Purpose: 显示所有核的TCP统计信息
*  Description: 显示所有核的TCP统计信息
*        Input: 
*       Output: 
*       Return: 
*      Caution: None
*        Since: DOPRA IP V200R003C06SPC100
*    Reference:
*
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2012-04-18   z00171897        Create the first version.
*
*******************************************************************************/
VOID SFE_ShowAllTCPStatist(VOID);

/*******************************************************************************
*    Func Name: SFE_TCP_GetPoolTotalAndFreeUnitNum
* Date Created: 2012-05-03
*       Author: zhaoyue00171897
*      Purpose: 获取TCP资源池总的和剩余的单元数
*  Description: 获取TCP资源池总的和剩余的单元数
*        Input: 
*       Output: UINT32 *pu32TotalUnitNum:TCP资源池总的单元数
*               UINT32 *pu32FreeUnitNum:TCP资源池剩余的单元数
*       Return: 成功:SFE_TCP_OK
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
UINT32 SFE_TCP_GetPoolTotalAndFreeUnitNum(UINT32 *pu32TotalUnitNum, UINT32 *pu32FreeUnitNum);

#ifdef  __cplusplus
}
#endif

#endif

