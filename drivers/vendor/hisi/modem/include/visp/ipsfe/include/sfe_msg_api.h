/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sfe_msg_api.h
*
*  Project Code: V1.1.0
*   Module Name:
*  Date Created: 2009-8-31
*        Author: w60786
*   Description: 数据面与控制面消息讯相关对外API结构定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-8-31    w60786           Creat the first version.
*
*******************************************************************************/

#ifndef _SFE_MSG_API_H_
#define _SFE_MSG_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/* 数据面与控制面消息通讯模块错误码 */
enum enumSfeComCode
{
    SFE_COM_SUCCESS,                                /* 通信成功 */
    SFE_COM_ERR_BEGIN = SFE_COM_BEGIN_RET_CODE,     /* 模块错误码起始值,建议内部不要使用该值 */
    SFE_COM_RCVMSG_NULL_POINTER,                    /* 1   从通道中收到消息为空 */
    SFE_COM_SENDACKHOOK_NULL,                       /* 2   发送ACK钩子函数为空 */
    SFE_COM_RCVMSG_LEN_ERR,                         /* 3   通道传递报文长度和收到报文长度不一致 */
    SFE_COM_RCVMSG_MODULE_ERR,                      /* 4   消息中模块号非法 */
    SFE_COM_RCVMSG_ITEM_LEN,                        /* 5   消息中子选项长度非法 */
    SFE_COM_REG_ACKMSG_POINTER,                     /* 6   注册回复ACK回调函数指针为空 */
    SFE_COM_REG_SEND_EVENT_NULL,                    /* 7   注册上送控制面EVENT回调函数指针为空 */
    SFE_COM_REG_SEND_PACKET_NULL,                   /* 8   注册上送控制面报文回调函数指针为空 */
    SFE_COM_ROUTE_ITEM_LEN,                         /* 9   解析路由ITEM长度非法 */
    SFE_COM_IF_ITEM_LEN,                            /* 10  解析接口ITEM长度非法 */
    SFE_COM_ARP_ITEM_LEN_ERROR,                     /* 11  ARP 配置消息长度错误 */
    SFE_COM_ARP_SEND_MSG_FUNC_NULL,                 /* 12  通道消息发送函数钩子为NULL */
    SFE_COM_ARP_SEND_ARPMISS_MSG_FAIL,              /* 13  通道发送ARP MISS消息失败 */
    SFE_COM_RCVMSG_LEN_SHORT,                       /* 14  报文总长度非法 */
    SFE_COM_RCVMSG_ITEM_LEN_SHORT,                  /* 15  解析报文时,ITEM报文长度非法 */
    SFE_COM_RCVMSG_TYPE_ERR,                        /* 16  报文消息类型非法 */
    SFE_COM_RCVMSG_OPENTABLE_LEN,                   /* 17  OPEN表项时长度非法 */
    SFE_COM_RCVMSG_OPENTABLE_TABLE,                 /* 18  OPEN表项时Talbe值非法 */
    SFE_COM_RCVMSG_OPENTABLE_REGISGT,               /* 19  OPEN表项时,该Table没有注册 */
    SFE_COM_RCVMSG_OPENTABLE_POOL,                  /* 20  OPEN表项时,Open pool失败 */
    SFE_COM_RCVMSG_OPENTABLE_HAVE,                  /* 21  OPEN表项时,已经Open pool */

    SFE_COM_RCVMSG_CLOSETABLE_LEN,                  /* 22  CLOSE表项时长度非法 */
    SFE_COM_RCVMSG_CLOSETABLE_TABLE,                /* 23  CLOSE表项时Talbe值非法 */
    SFE_COM_RCVMSG_CLOSETABLE_OPEN,                 /* 24  CLOSE表项时,该Table没有OPEN过 */
    SFE_COM_RCVMSG_CLOSETABLE_POOL,                 /* 25  CLOSE表项时,Open pool失败 */

    SFE_COM_RCVMSG_GETTABLE_LEN,                    /* 26  GET表项时长度非法 */
    SFE_COM_RCVMSG_GETTABLE_TABLE,                  /* 27  GET表项时Talbe值非法 */
    SFE_COM_RCVMSG_GETTABLE_OPEN,                   /* 28  GET表项时,该Table没有OPEN过 */

    SFE_COM_RCVMSG_INVALIDTABLE_TYPE,               /* 29  表项操作时,不存在该操作 */

    SFE_COM_RCVMSG_NPPI_ITEM_LEN,                   /* 30  数据面接收的NPPI类型消息长度不合法 */
    SFE_COM_RCVMSG_NPPI_ITEM_LEN_SHORT,             /* 31  数据面接收的NPPI类型消息子消息长度不合法 */
    SFE_COM_RCVMSG_NPPI_MODULE_ERR,                 /* 32  数据面接收的NPPI类型消息中的模块号不合法 */

    SFE_COM_ARP_GET_ITEM_LEN_ERROR,                 /* 33  ARP获取信息操作消息长度错误 */
    SFE_COM_ARP_SHOW_ALLARP_ITEM_LEN_ERROR,         /* 34  显示ARP信息消息长度错误 */
    SFE_COM_ARP_SHOW_ALLARP_BYVRF_ITEM_LEN_ERROR,   /* 35  显示ARP信息消息长度错误 */
    SFE_COM_ARP_SHOW_ONEARP_BYVRF_ERROR,            /* 36  显示指定的某个ARP表项时消息长度错误 */
    SFE_COM_ARP_GET_BUF_LEN_ERROR,                  /* 37  ARP获取信息操作时通道提供的缓冲区长度不够 */
    SFE_COM_ARP_NPPI_CMD_INVALID,                   /* 38  ARP 非PPI命令字不合法 */

    SFE_COM_GET_ROUTE_ITEM_LEN_ERROR,               /* 39  ROUTE获取信息操作消息长度错误 */
    SFE_COM_GET_ROUTE_BUF_LEN_ERROR,                /* 40  ROUTE获取信息操作时通道提供的缓冲区长度不够 */
    SFE_COM_NPPI_ROUTE_CMD_INVALID,                 /* 41  ROUTE 非PPI下发命令字错误 */
    SFE_COM_NPPI_ROUTE_SHOW_ALL_ITEM_LEN_ERROR,     /* 42  显示所有FIB信息消息长度错误 */
    SFE_COM_NPPI_ROUTE_SHOW_ONEIP_ITEM_LEN_ERROR,   /* 43  显示某个地址路由信息消息长度错误 */

    SFE_COM_IF_GET_ITEM_LEN_ERROR,                  /* 44  IF获取信息操作消息长度错误 */
    SFE_COM_IF_GET_BUF_LEN_ERROR,                   /* 45  IF获取信息操作时通道提供的缓冲区长度不够 */
    SFE_COM_IF_NPPI_CMD_INVALID,                    /* 46  IF 非PPI下发命令字错误 */

    SFE_COM_BFD_GET_ITEM_LEN_ERROR,                 /* 47  BFD获取信息操作消息长度错误 */
    SFE_COM_BFD_GET_BUF_LEN_ERROR,                  /* 48  BFD获取信息操作时通道提供的缓冲区长度不够 */
    SFE_COM_BFD_NPPI_CMD_INVALID,                   /* 49  BFD 非PPI命令字不合法 */

    SFE_COM_BFD_ITEM_LEN_ERROR,                     /* 50  BFD 配置消息长度错误 */
    SFE_COM_BFD_SEND_MSG_FUNC_NULL,                 /* 51  数据面通道消息发送函数钩子为NULL */
    SFE_COM_BFD_SEND_DETECTDOWN_MSG_FAIL,           /* 52  通道发送BFD探测会话DOWN消息失败 */

    SFE_COM_SET_ICMP_ITEM_LEN_ERROR,                /* 53  ICMP设置开关信息操作消息长度错误 */
    SFE_COM_GET_ICMP_BUF_LEN_ERROR,                 /* 54  ICMP获取开关信息时通道提供的缓冲区长度不够 */
    SFE_COM_GET_ICMP_ITEM_LEN_ERROR,                /* 55  ICMP获取开关信息操作消息长度错误 */
    SFE_COM_NPPI_ICMP_CMD_INVALID,                  /* 56  ICMP 非PPI下发命令字错误 */

    SFE_COM_IF_SET_ARPMISSWITCH_ITEM_LEN_ERROR,     /* 57  设置ARP MISS开关消息长度错误 */
    SFE_COM_IF_SET_REDUCETTLSWITCH_ITEM_LEN_ERROR,  /* 58  设置TTL是否递减开关消息长度错误 */
    SFE_COM_IF_SHOW_ALL_IFINFO_ITEM_LEN_ERROR,      /* 59  显示所有接口信息时消息长度错误 */
    SFE_COM_IF_SHOWBYID_IFINFO_ITEM_LEN_ERROR,      /* 60  根据接口ID显示接口信息时消息长度错误 */

    SFE_COM_REG_ACL_PPIMSG_DISPATCH_HOOK_NULL,      /* 61  注册ACL PPI消息分发函数指针为空 */
    SFE_COM_REG_ACL_NPPIMSG_DISPATCH_HOOK_NULL,     /* 62  注册ACL NPPI消息分发函数指针为空 */

    SFE_COM_SET_SRCIPADDR_ITEM_LEN_ERROR,           /* 63  设置Src IP Addr信息操作消息长度错误 */
    SFE_COM_GET_SRCIPADDR_ITEM_LEN_ERR,             /* 64  获取Src IP Addr时，操作消息长度错误 */
    SFE_COM_GET_SRCIPADDR_BUF_LEN_ERROR,            /* 65  获取Src IP Addr时，通道提供的BUF长度不够 */

    SFE_COM_NPPI_IP_CMD_INVALID,                    /* 66  IP 非PPI下发命令字错误 */

    SFE_COM_VCPU_NOT_INIT_SFERCVMSG,                /* 67  接收通道消息时VCPU没有初始化*/
    SFE_COM_GET_CFGPPI_SPINLOCK_FAIL,               /* 68  获取PPI配置自旋锁失败 */
    SFE_COM_GET_CFGNPPI_SPINLOCK_FAIL,              /* 69  获取NPPI配置自旋锁失败 */
    SFE_COM_GET_CFGTABLE_SPINLOCK_FAIL,             /* 70  获取TABLE操作自旋锁失败 */
    SFE_COM_CHECKSUM_FAIL,                          /* 71  消息校验和错误 */

    SFE_COM_MAINTENANCE_NPPI_CMD_INVALID,           /* 72  维测模块配置非PPI命令字不合法 */
    SFE_COM_DEBUG_NPPI_CMD_INVALID,                 /* 73  维测DEBUG模块配置非PPI命令字不合法 */
    SFE_COM_FLOWSTAT_NPPI_CMD_INVALID,              /* 74  维测流统计模块配置非PPI命令字不合法 */
    SFE_COM_STATISTIC_NPPI_CMD_INVALID,             /* 75  维测统计模块配置非PPI命令字不合法 */
    SFE_COM_LOG_NPPI_CMD_INVALID,                   /* 76  维测日志模块配置非PPI命令字不合法 */
    SFE_COM_PUB_NPPI_CMD_INVALID,                   /* 77  公共处理模块配置非PPI命令字不合法 */

    SFE_COM_GET_STAT_ALLINFO_ITEM_LEN_ERROR,        /* 78  获取全局统计信息时，操作消息长度错误 */
    SFE_COM_GET_STAT_ALLINFO_CFG_BUF_LEN_ERROR,     /* 79  获取全局统计信息时，通道提供的BUF长度不够 */
    SFE_COM_SHOW_STAT_ALLSTAT_ITEM_LEN_ERROR,       /* 80  显示所有全局统计信息时,消息长度错误 */
    SFE_COM_SHOW_STAT_AUTOSTAT_ITEM_LEN_ERROR,      /* 81  显示全局自动统计信息时,消息长度错误 */
    SFE_COM_SHOW_STAT_MANUALSTAT_ITEM_LEN_ERROR,    /* 82  显示全局手动统计信息时,消息长度错误 */
    SFE_COM_SHOW_STAT_MANUALSTATBYVCPU_ITEM_LEN_ERROR,/* 82  显示指定VCPU的全局手动统计信息时,消息长度错误 */
    SFE_COM_CLEAR_ALLSTAT_ITEM_LEN_ERROR,           /* 83  清除所有全局统计信息时,消息长度错误 */

    SFE_COM_SET_FLOWSTAT_SWITCH_ITEM_LEN_ERROR,     /* 84  设置流统计开关时,消息长度错误 */
    SFE_COM_GET_FLOWSTAT_SWITCH_ITEM_LEN_ERROR,     /* 85  获取流统计开关时,消息长度错误 */
    SFE_COM_GET_FLOWSTAT_SWITCH_CFG_BUF_LEN_ERROR,  /* 86  获取流统计开关时,通道提供的缓冲区长度不够 */
    SFE_COM_SHOW_FLOWSTAT_SWITCH_ITEM_LEN_ERROR,    /* 87  显示流统计开关时,消息长度错误 */
    SFE_COM_FLOWSTAT_CFG_ITEM_LEN_ERROR,            /* 88  配置流统计规则时,消息长度错误 */
    SFE_COM_FLOWSTAT_CFG_BUF_LEN_ERROR,             /* 89  配置流统计规则时,通道提供的缓冲区长度不够 */
    SFE_COM_GET_FLOWSTAT_RULENUM_ITEM_LEN_ERROR,    /* 90  获取流统计规则数时,消息长度错误 */
    SFE_COM_GET_FLOWSTAT_RULENUM_CFG_BUF_LEN_ERROR, /* 91  获取流统计规则数时,通道提供的缓冲区长度不够 */
    SFE_COM_GET_FLOWSTAT_ALLINFO_ITEM_LEN_ERROR,    /* 92  获取流统计相关信息时,消息长度错误 */
    SFE_COM_GET_FLOWSTAT_ALLINFO_CFG_BUF_LEN_ERROR, /* 93  获取流统计相关信息时,通道提供的缓冲区长度不够 */
    SFE_COM_SHOW_FLOWSTAT_ALLRULE_ITEM_LEN_ERROR,   /* 94  显示所有流统计规则时,消息长度错误 */
    SFE_COM_SHOW_FLOWSTAT_RULEBYFLOWID_ITEM_LEN_ERROR,/* 95  显示指定流ID的流统计规则时,消息长度错误 */
    SFE_COM_SHOW_FLOWSTAT_ALLSTAT_ITEM_LEN_ERROR,   /* 96  显示所有流统计信息时,消息长度错误 */
    SFE_COM_SHOW_FLOWSTAT_BYRULE_ITEM_LEN_ERROR,    /* 97  显示指定流规则的流统计信息时,消息长度错误 */
    SFE_COM_SHOW_FLOWSTAT_BYFLOWID_ITEM_LEN_ERROR,  /* 97  显示指定流ID的流统计信息时,消息长度错误 */
    SFE_COM_CLEAR_ALLFLOWSTAT_ITEM_LEN_ERROR,       /* 99  清除所有流统计信息时,消息长度错误 */

    SFE_COM_SET_DEBUGTYPE_ITEM_LEN_ERROR,           /* 100 设置Debug类型开关时，长度错误 */
    SFE_COM_SET_DEBUGVCPU_ITEM_LEN_ERROR,           /* 101 设置VCPU Debug类型开关时，长度错误 */
    SFE_COM_SET_DEBUGMODU_ITEM_LEN_ERROR,           /* 102 设置MODULE Debug类型开关时，长度错误 */
    SFE_COM_GET_DEBUGSWITCH_ITEM_LEN_ERROR,         /* 103 DEBUG获取开关信息操作消息长度错误 */
    SFE_COM_GET_DEBUGSWITCH_BUF_LEN_ERROR,          /* 104 DEBUG获取开关信息时通道提供的缓冲区长度不够 */
    SFE_COM_SET_MSGOREVENT_DEBUG_ITEM_LEN_ERROR,    /* 105 设置消息或事件调试开关时，长度错误 */
    SFE_COM_GET_MSGOREVENT_DEBUG_ITEM_LEN_ERROR,    /* 106 获取消息或事件调试开关时，长度错误 */
    SFE_COM_GET_MSGOREVENT_DEBUG_BUF_LEN_ERROR,     /* 107 获取消息或事件调试开关时，通道提供的长度错误 */
    SFE_COM_SET_VERBOSE_DEBUG_ITEM_LEN_ERROR,       /* 108 设置详细调试的报文个数和长度时，长度错误 */
    SFE_COM_GET_VERBOSE_DEBUG_ITEM_LEN_ERROR,       /* 109 获取详细调试的报文个数和长度时，长度错误 */
    SFE_COM_GET_VERBOSE_DEBUG_BUF_LEN_ERROR,        /* 110 获取详细调试的报文个数和长度时，通道提供的长度错误 */
    SFE_COM_SHOW_DEBUG_SWITCH_ITEM_LEN_ERROR,       /* 111 显示调试开关信息时,消息长度错误 */

    SFE_COM_BFD_SET_DEBUGSWITCH_ITEM_LEN_ERROR,     /* 112 BFD设置调试开关消息长度错误 */
    SFE_COM_BFD_GET_DEBUGSWITCH_ITEM_LEN_ERROR,     /* 113 BFD获取调试开关消息长度错误 */
    SFE_COM_BFD_GET_DEBUGSWITCH_BUF_LEN_ERROR,      /* 114 BFD获取调试开关操作时通道提供的缓冲区长度不够 */
    SFE_COM_BFD_SHOW_ALLINFO_ITEM_LEN_ERROR,        /* 115 显示所有BFD消息长度错误*/
    SFE_COM_BFD_SHOW_INFO_BYVRF_ITEM_LEN_ERROR,     /* 116 根据VRF显示BFD消息长度错误*/
    SFE_COM_BFD_SHOW_INFO_BYID_ITEM_LEN_ERROR,      /* 117 根据BFD 会话ID显示BFD消息长度错误*/

    SFE_COM_SET_LOGLEVEL_SWITCH_ITEM_LEN_ERROR,     /* 118 设置日志级别开关时,消息长度错误 */
    SFE_COM_SET_LOGTYPE_SWITCH_ITEM_LEN_ERROR,      /* 119 设置日志类型开关时,消息长度错误 */
    SFE_COM_SHOW_LOG_SWITCH_ITEM_LEN_ERROR,         /* 120 显示日志开关时,消息长度错误 */

    SFE_COM_SHOW_VERSION_ITEM_LEN_ERROR,            /* 121 显示数据面版本号时,消息长度错误 */
    SFE_COM_SHOW_PRECONFIG_ITEM_LEN_ERROR,          /* 122 显示数据面预配置时,消息长度错误 */
    SFE_COM_SHOW_SHAREMEMID_ITEM_LEN_ERROR,         /* 123 显示数据面共享内存ID时,消息长度错误 */
    SFE_COM_SHOW_STUBMODULE_ITEM_LEN_ERROR,         /* 124 显示数据面模块裁减时,消息长度错误 */
    SFE_COM_SET_ACLFAKEREASS_SWITCH_ITEM_LEN_ERROR, /* 125 设置ACL是否需要假重组开关时,消息长度错误 */
    SFE_COM_GET_ACLFAKEREASS_SWITCH_ITEM_LEN_ERROR, /* 126 获取ACL是否需要假重组开关时,消息长度错误 */
    SFE_COM_GET_ACLFAKEREASS_SWITCH_CFG_BUF_LEN_ERROR,/* 127 获取ACL是否需要假重组开关时,通道提供的缓冲区长度不够 */
    SFE_COM_SHOW_ACLFAKEREASS_ITEM_LEN_ERROR,       /* 128 显示ACL是否需要假重组开关时,消息长度错误 */
    SFE_COM_SHOW_MSGSEQ_ITEM_LEN_ERROR,             /* 129 显示数据面消息序号时,消息长度错误 */
    SFE_COM_SET_OUTPUTTOCOM_SWITCH_ITEM_LEN_ERROR,  /* 130 设置数据面信息输出到com口开关时,消息长度错误 */

    SFE_COM_ARP_MISS_RESTRAIN_FAIL,                 /* 131 ARP MISS抑制,返回1表示不上报 */
    SFE_COM_ARP_MISS_REG_RESTRAIN_HOOK_NULL,        /* 132 注册ARP MISS抑制钩子函数为空 */
    SFE_COM_BFD_GET_STAT_ITEM_LEN_ERROR,            /* 133 获取BFD会话统计信息消息长度错误 */
    SFE_COM_BFD_GET_STAT_BUF_LEN_ERROR,             /* 134 获取BFD会话统计信息操作时通道提供的缓冲区长度不够 */
    SFE_COM_BFD_CLEAR_STAT_ITEM_LEN_ERROR,          /* 135 清0BFD会话统计信息消息长度错误 */
    SFE_COM_BFD_SHOW_STAT_ITEM_LEN_ERROR,           /* 136 显示BFD会话统计信息消息长度错误 */
 };

/* 数据面回复控制面消息的钩子原型 */
typedef UINT32 (*g_pfSFESendAckMsg)(VOID *pSrcMsg, VOID *pMsg, UINT32 u32MsgLen);
/* 数据面通知控制面事件消息的钩子原型 */
typedef UINT32 (*g_pfSendEventToVISP)(VOID *pMsg, UINT32 u32MsgLen);

/*Description:数据面注册的ARP MISS上报抑制函数的钩子原型.
  Input      :UINT32 u32VrfIndex: VRF索引.
              UINT32 u32IpAddr: 地址,网络序.
  Return     :0,表示ARP Miss速率正常，可以上送ARP Miss消息.
              1,表示ARP Miss速率超标，不能上送ARP Miss消息.*/
typedef UINT32 (*g_pfSfeArpMissRestrainHook)(UINT32 u32VrfIndex, UINT32 u32IpAddr);

/*******************************************************************************
*    Func Name: SFE_RecvMsg
* Date Created: 2009-8-21
*       Author: zhangchunyu(62474)
*  Description: 数据面接收控制面消息入口,包括NP表项等
*        Input: VOID * pMsg:消息
*               UINT32 u32MsgLen: 消息长度
*       Output:
*       Return: 成功:SFE_COM_SUCCESS 其他:失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-8-21    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 SFE_RecvMsg(VOID * pMsg, UINT32 u32MsgLen);

/*******************************************************************************
*    Func Name: SFE_RegSendAckMsg
* Date Created: 2009-8-21
*       Author: zhangchunyu(62474)
*  Description: 数据面注册发送ACK回调函数
*        Input: g_pfSFESendAckMsg pfFunc:函数指针
*       Output:
*       Return: 成功:SFE_COM_SUCCESS 其他:失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-8-21    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 SFE_RegSendAckMsg(g_pfSFESendAckMsg pfFunc);

/*******************************************************************************
*    Func Name: SFE_RegSendEventToVISP
* Date Created: 2009-8-21
*       Author: zhangchunyu(62474)
*  Description: 数据面注册发送事件回调函数
*        Input: g_pfSendEventToVISP pfFunc: 函数指针
*       Output:
*       Return: 成功:SFE_COM_SUCCESS 其他:失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-8-21    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 SFE_RegSendEventToVISP(g_pfSendEventToVISP pfFunc);

/*******************************************************************************
*    Func Name: SFE_RegFuncArpMissRestrainHook
* Date Created: 2009-11-16
*       Author: zengshaoyang(62531)
*  Description: 注册ARP MISS上报抑止函数
*        Input: g_pfSfeArpMissRestrainHook pfRegFunc: 函数指针
*       Output:
*       Return: 成功:SFE_COM_SUCCESS 其他:失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-11-16   zengshaoyang(62531)     Creat the first version.
*
*******************************************************************************/
extern UINT32 SFE_RegFuncArpMissRestrainHook(g_pfSfeArpMissRestrainHook pfRegFunc);

/*******************************************************************************
*    Func Name: SFE_Show_MsgSeq
* Date Created: 2009-10-26
*       Author: maqinggao(00116466)
*  Description: 显示数据面通道消息序列号
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                     DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-26   maqinggao(00116466)      Creat the first version.
*
*******************************************************************************/
extern VOID SFE_Show_MsgSeq(VOID);


#ifdef  __cplusplus
}
#endif

#endif


