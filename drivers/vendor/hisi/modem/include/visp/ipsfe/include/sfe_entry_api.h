/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sfe_entry_api.h
*
*  Project Code: V1.1.0
*   Module Name:
*  Date Created: 2009-8-31
*        Author: w60786
*   Description: 数据面初始化相关对外API结构定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-8-31    w60786           Creat the first version.
*
*******************************************************************************/

#ifndef _SFE_ENTRY_API_H_
#define _SFE_ENTRY_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/* 数据面返回值全局唯一各模块错误码区段划分 */
typedef enum enumSfeGlobalRetCode
{
    SFE_ENTRY_BEGIN_RET_CODE = 1000,           /* ENTRY模块错误码起始值 */
    SFE_DEBUG_BEGIN_RET_CODE = 2000,           /* DEBUG模块错误码起始值 */
    SFE_MBUF_BEGIN_RET_CODE = 3000,            /* MBUF模块错误码起始值 */
    SFE_POOL_BEGIN_RET_CODE = 4000,            /* POOL模块错误码起始值 */
    SFE_ARP_BEGIN_RET_CODE = 5000,             /* ARP模块错误码起始值 */
    SFE_ROUTE_BEGIN_RET_CODE = 6000,           /* ROUTE模块错误码起始值 */
    SFE_IF_BEGIN_RET_CODE = 7000,              /* IF接口模块错误码起始值 */
    SFE_ETH_BEGIN_RET_CODE = 8000,             /* ETH模块错误码起始值 */
    SFE_COM_BEGIN_RET_CODE = 9000,             /* MSG消息通讯模块错误码起始值 */
    SFE_BFD_BEGIN_RET_CODE = 10000,            /* BFD消息通讯模块错误码起始值 */
    SFE_FAKEREASS_BEGIN_RET_CODE = 11000,      /* 假重组模块错误码起始值 */
    SFE_REASS_BEGIN_RET_CODE = 12000,          /* 真重组模块错误码起始值 */
    SFE_ICMP_BEGIN_RET_CODE = 13000,           /* ICMP模块错误码起始值 */
    SFE_IPFWD_BEGIN_RET_CODE = 14000,          /* IP模块错误码起始值 */
    SFE_PUB_BEGIN_RET_CODE = 15000,            /* PUB公共模块错误码起始值 */
    SFE_TCP_BEGIN_RET_CODE = 16000,            /* TCP模块错误码起始值 */
    SFE_UDP_BEGIN_RET_CODE = 17000,            /* UDP模块错误码起始值 */
    SFE_SOCK_BEGIN_RET_CODE = 18000,           /* socket模块错误码起始值 */
    SFE_ADDR_BEGIN_RET_CODE = 19000,           /* ADDR模块错误码起始值 */
    SFE_DRV_BEGIN_RET_CODE  = 20000,           /* DRIVER模块错误码起始值 */

    SFE_STUB_RET_CODE = 0x0fffffff             /* 支持可裁减统一返回的错误码. */
}SFE_GLOBAL_RET_CODE_E;

/* 数据面ENTRY模块错误码定义 */
typedef enum enumSfeEntryErrCode
{
    SFE_ENTRY_OK = SFE_OK,                      /* 操作成功 */
    SFE_ENTRY_ERR_BEGIN = SFE_ENTRY_BEGIN_RET_CODE,/* 模块错误码起始值,建议内部不要使用该值 */
    SFE_ENTRY_CREATE_SPINLOCK_FAIL,             /* 1  创建自旋锁失败 */
    SFE_ENTRY_GET_SPINLOCK_FAIL,                /* 2  获取自旋锁失败 */
    SFE_ENTRY_VCPU_ALREADY_INIT_SETPRECFG,      /* 3  设置预配置项时VCPU 已经初始化 */
    SFE_ENTRY_MALLOC_MEMORY_FAIL_PRECFGVAR,     /* 4  初始化时分配预配置共享变量失败 */
    SFE_ENTRY_ADD_SHARE_DB_FAIL_PRECFGVAR,      /* 5  初始化时预配置共享变量加入共享名字库失败 */
    SFE_ENTRY_NULL_POINTER_GETPRECFG,           /* 6  获取预配置项时传入参数为空指针 */
    SFE_ENTRY_NO_PRE_VALUE_SETPRECFG,           /* 7  设置预配置项时没有预配置项 */
    SFE_ENTRY_NO_PRE_VALUE_GETPRECFG,           /* 8  获取预配置项时没有预配置项 */
    SFE_ENTRY_PARA_INVALID_SETPRECFG,           /* 9  设置预配置项时参数不合法 */
    SFE_ENTRY_GET_VRF_PRECONFIG_FAIL,           /* 10 获取VRF预配置项失败 */
    SFE_ENTRY_VCPU_ALREADY_INIT_SETSHAREMEMID,  /* 11 设置共享内存分区号时VCPU已经初始化 */
    SFE_ENTRY_NULL_POINTER_GETSHAREMEMID,       /* 12 获取共享内存分区号时传入参数为空指针 */
    SFE_ENTRY_GET_SFE_VCPU_MAX_NUM_PRECFG_FAIL, /* 13 获取最大VCPU数量预配置值失败 */
    SFE_ENTRY_GET_SFE_ALIGN_LEN_PRECFG_FAIL,    /* 14 获取分配资源池时使用的字节对齐值预配置值失败 */
    SFE_ENTRY_GET_SFE_IP_OPTION_PROCESS_MODE_PRECFG_FAIL,/* 15 获取数据面IP选项处理方式预配置值失败 */
    SFE_ENTRY_GET_SFE_VLAN_PKT_PROCESS_MODE_PRECFG_FAIL, /* 16 获取数据面VLAN报文处理方式预配置值失败 */
    SFE_ENTRY_GET_SFE_PKT_FAST_PATH_PROCESS_PRECFG_FAIL, /* 17 获取数据面报文接收快通道处理预配置值失败 */
    SFE_ENTRY_CREATE_SEMA_FAIL,                          /* 18  创建信号量失败 */  
}SFE_ENTRY_ERR_CODE_E;

/************************************************************
 * 本VCPU默认的数据面预配置项参数值
 * - - -
 * 注意，调整/新增预配置项时，以下几处须同步修改:
 * (1)枚举定义SFE_PRECONFIG_INFO_E
 * (2)预配置初始值g_stSFE_ComPara
 ************************************************************/
typedef enum SFE_PRECONFIG_INFO_Etag
{
    /* 同框同槽上最大LoopBack数量 */
    SFE_MAX_LOOPBACK_PORT_NUM,

    /* 所有框槽上最大LoopBack数量 */
    SFE_MAX_TOTAL_LOOPBACK_PORT_NUM,

    /* 同框同槽上最大以太口数量 */
    SFE_MAX_ETH_PORT_NUM,

    /* 所有框槽上最大以太口数量 */
    SFE_MAX_TOTAL_ETH_PORT_NUM,

    /* 最大VRF个数,实际允许的VRF个数是配置个数加1,目的是为了与控制面的预配置项含义保持一致. */
    SFE_MAX_VRF_NUM,

    /* 最大路由数量 */
    SFE_MAX_ROUTE_NUM,

    /* 最大平衡路由数量 */
    SFE_MAX_BALANCE_ROUTE_NUM,

    /* 最大已解析ARP表项数量 */
    SFE_MAX_ARP_RESOLVED_NUM,

    /* 最大待解析ARP表项数量 */
    SFE_MAX_ARP_RESOLVING_NUM,

    /* 最大ARP待解析节点缓存报文个数 */
    SFE_MAX_ARP_CACHE_PACKET_NUM,

    /* 系统缓存假重组节点总个数,一个节点缓存一条流的分片报文,目前缓存分片报文的最大个数为2倍的系统缓存的假重组节点个数 */
    SFE_NET_FAKE_REASS_MAX_NUM,

    /* 假重组节点超时时间,单位是秒 */
    SFE_NET_FAKE_REASSNODE_TIMEOUT,

    /* 系统缓存真重组节点总个数,一个节点缓存一条流的分片报文,目前缓存分片报文的最大个数为2倍的系统缓存的真重组节点个数 */
    SFE_NET_REASS_MAX_NUM,

    /* 真重组节点超时时间,单位是秒 */
    SFE_NET_REASSNODE_TIMEOUT,

    /* 最大BFD会话数量 */
    SFE_MAX_BFD_SESSION_NUM,

    /* BFD单跳会话处理模式,取值范围[0,1],0表示单跳会话正常模式,1表示单跳会话特殊处理模式,默认值为0(即正常处理模式) */
    SFE_BFD_SINGLE_HOP_PROC_MODE,

    /* 流统计支持的最大流规格个数 */
    SFE_FLOW_STATISTIC_MAX_FLOW_NUM,

    /* 黑匣子申请的内存大小 */
    SFE_BOX_SIZE,

    /*Maximum number of rules for whitelist*/
    SFE_FW_WLS_MAX_RULE,

    /*Maximum number of rules for blacklist*/
    SFE_FW_BLS_MAX_RULE,

    /*Maximum number of interface based attack rules*/
    SFE_FW_AD_IF_CFG_MAX_RULE,

    /*Maximum number flood based atrack rules*/
    SFE_FW_AD_FLOOD_CFG_MAX_RULE,

    /*Maximum number interface indexes binding with acl group*/
    SFE_FW_ACLFW_MAX_IFINDEX,

    /*Maximum memory usage for acl rfc*/
    SFE_FW_ACL_RFC_MAX_MEM_USE,

    /*To enable/disable mac based acl filter*/
    SFE_FW_ENABLE_MAC_BASE_ACL_FILTER,

    /* 扩展MBUF结构体大小预配置,默认值为0,为了兼容原有RPU产品的特殊应用;
       预配置为0:在32位系统下MBUF结构体大小固定为160字节,DBD结构体大小固定为32字节保持不变;
       预配置为1:MBUF结构体大小和DBD结构体大小没有限制,在64位系统下,MBUF结构体大小变化,产品必须预配置为1 */
    SFE_MBUF_EXPEND_SIZE,

    /* MBUF初始资源池大小,指定的MBUF个数必须与内核态模块插入时指定的个数一致 */
    SFE_MBUF_POOL_INIT_NUM,

    /* 最大socket数量 */
    SFE_SOCKET_MAX_NUM,

    /* 最大TCP控制块数量,一个TCP socket对应一个TCP控制块 */
    SFE_TCP_MAX_NUM,

    /* 最大VCPU数量 */
    SFE_MAX_VCPU_NUM,

    /* 分配资源池时使用的字节对齐值,指定对齐方式必须与内核态模块插入时指定的对齐方式一致,建议产品直接填0,默认值为0表示自然对齐. */
    SFE_ALIGN_BYTE_NUM,

    /* TCP是否支持rfc1323的时间戳和窗口缩放因子选项 */
    SFE_TCP_DORFC1323_FLAG,

    /* 数据面IP选项处理方式 */
    SFE_IP_OPTION_PROCESS_MODE,

    /* 数据面VLAN报文处理方式 */
    SFE_VLAN_PKT_PROCESS_MODE,

    /* 最大IP ADDR数量 */
    SFE_IPADDR_MAX_NUM,

    /* 每个接口最大地址数目 */
    SFE_IPADDR_MAX_NUM_PER_IF,

    /* TCP重排保活定时器功能开关 */
    SFE_TCP_REORDER_KEEPALIVE_TIMER_SWITCH,

    /* TCP重排的乱序重组重复缓存规模 */
    SFE_TCP_REORDER_REASS_CACHE_NUM,

    /* 驱动接口管理支持管理的最大接口数 */
    SFE_DRV_INTF_MNG_MAX_NUM,

    /* 驱动期望一次从内核接收的最大报文个数 */
    SFE_DRV_ONCE_RCV_PKT_NUM,

    /* 驱动期望一次向内核发送的最大报文个数 */
    SFE_DRV_ONCE_SND_PKT_NUM,

    /* 驱动向内核发送报文的超时时间,当报文个数不足一次向内核发送的个数时,超时时有报文也会发送 */
    SFE_DRV_ONCE_SND_PKT_TIMEOUT,

    /* 数据面报文快通道处理 */
    SFE_PKT_FAST_PATH_PROCESS,

    /* TCP支持校验和检查的标志 */
    SFE_TCP_CKSUM_FLAG,

    /* UDP支持校验和检查的标志 */
    SFE_UDP_CKSUM_FLAG,

    /* TCP接收缓存读取后是否做立即窗口更新优化 */
    SFE_TCP_UPDATEWND_FLAG,

    /* TCP收到报文部分数据超窗是否立即通告0窗口优化 */    
    SFE_TCP_UPDATE_ZEROWND_FLAG,    

    /* 配置TCP MSL老化时间 */
    SFE_TCP_MSL_TIME,

    /* TCP延迟ACK功能开关*/
    SFE_TCP_DELAYED_ACK_SWITCH,

    /* 枚举边界值,新增预配置项时必须在此之前定义 */
    SFE_MAX_COM_PARA_NUM,
}SFE_PRECONFIG_INFO_E;

/* 最大VRF个数预配置下限值,将VRF预配置的最小值由1改为0,表示只有1个vrf,这样可以节约部分内存资源. */
#define SFE_MAX_VRF_NUM_LOWLIMIT 0
/* 最大VRF个数预配置上限值 */
/* 2012-12-04 合入企业VPN需求，VRF规格为200个，上限设为256 */
#define SFE_MAX_VRF_NUM_UPLIMIT 256
/* 最大VRF个数预配置默认值 */
#define SFE_MAX_VRF_NUM_DEFAULT 200

/* MBUF结构体大小固定(32位环境),MBUF结构体大小固定为160字节,DBD结构体大小固定为32字节,DB大小固定为1600字节,保持不变; */
#define SFE_MBUF_EXPAND_SIZE_DISABLE 0
/* MBUF结构体大小扩大,MBUF,DB大小扩大,DBD大小在32位环境固定为32字节. */
#define SFE_MBUF_EXPAND_SIZE_ENABLE 1

/* 数据面不支持接收处理VLAN报文 */
#define SFE_VLAN_PKT_NOT_SUPPORT_MODE 0
/* 数据面以直接忽略VLAN头的方式支持接收VLAN报文 */
#define SFE_VLAN_PKT_IGNORE_VLAN_MODE 1

/* 数据面不支持接收处理带IP选项的报文 */
#define SFE_IP_OPTION_NOT_SUPPORT_MODE 0
/* 数据面以直接忽略IP选项的方式支持接收带IP选项报文 */
#define SFE_IP_OPTION_IGNORE_OPRION_MODE 1

/* 数据面不支持接RFC1323规定的窗口缩放和时间戳选项 */
#define SFE_TCP_DORFC1323_NOT_SUPPORT 0
/* 数据面支持接RFC1323规定的窗口缩放和时间戳选项 */
#define SFE_TCP_DORFC1323_SUPPORT 1

/* 不打开TCP重排保活定时器功能 */
#define SFE_TCP_REORDER_KEEPALIVE_TIMER_DISABLE 0
/* 打开TCP重排保活定时器功能 */
#define SFE_TCP_REORDER_KEEPALIVE_TIMER_ENABLE 1

/* 数据面默认支持的驱动接口最大个数 */
#define SFE_DRV_INTF_DEFAULT_NUM    10
/* 数据面允许配置支持的驱动接口最小个数 */
#define SFE_DRV_INTF_MIN_NUM    1
/* 数据面允许配置支持的驱动接口最大个数 */
#define SFE_DRV_INTF_MAX_NUM    50

/* 驱动期望一次从内核接收的默认报文个数 */
#define SFE_DRV_ONCE_RCV_PKT_DEFAULT_NUM    1
/* 驱动期望一次从内核接收的最小报文个数 */
#define SFE_DRV_ONCE_RCV_PKT_MIN_NUM        1
/* 驱动期望一次从内核接收的最大报文个数,
   该值是与OS约定的最大值不能随意增大,否则要知会OS零拷贝模块修改 */
#define SFE_DRV_ONCE_RCV_PKT_MAX_NUM        500

/* 驱动期望一次从向内核发送的默认报文个数 */
#define SFE_DRV_ONCE_SND_PKT_DEFAULT_NUM    1
/* 驱动期望一次向内核发送的最小报文个数 */
#define SFE_DRV_ONCE_SND_PKT_MIN_NUM        1
/* 驱动期望一次向内核发送的最大报文个数,
   该值是与OS约定的最大值不能随意增大,否则要知会OS零拷贝模块修改 */
#define SFE_DRV_ONCE_SND_PKT_MAX_NUM        500

/* 驱动向内核发送报文的超时时间默认值,单位毫秒 */
#define SFE_DRV_ONCE_SND_TIMEOUT_DEFAULT    100
/* 驱动向内核发送报文的超时时间最小值,单位毫秒 */
#define SFE_DRV_ONCE_SND_TIMEOUT_MIN        10
/* 驱动向内核发送报文的超时时间最大值,单位毫秒 */
#define SFE_DRV_ONCE_SND_TIMEOUT_MAX        1000

/* 数据面不使用报文快通道处理 */
#define SFE_PKT_FAST_PATH_DISABLE 0
/* 数据面接收报文流程使用报文快通道处理 */
#define SFE_PKT_FAST_PATH_ENABLE 1

/* 数据面不支持TCP校验和检查 */
#define SFE_TCP_CKSUM_FLAG_DISABLE 0
/* 数据面支持TCP校验和检查 */
#define SFE_TCP_CKSUM_FLAG_ENABLE 1

/* 数据面不支持TCP校验和检查 */
#define SFE_UDP_CKSUM_FLAG_DISABLE 0
/* 数据面支持TCP校验和检查 */
#define SFE_UDP_CKSUM_FLAG_ENABLE 1

/* 数据面不支持TCP接收数据后立即窗口通告优化 */
#define SFE_TCP_UPDATEWND_FLAG_DISABLE 0
/* 数据面支持TCP接收数据后立即窗口通告优化 */
#define SFE_TCP_UPDATEWND_FLAG_ENABLE 1

/* TCP MSL老化时间最小值,单位:秒 */
#define SFE_TCP_MSL_MIN_TIME 1
/* TCP MSL老化时间最大值(默认值),单位:秒 */
#define SFE_TCP_MSL_MAX_TIME 30

/* 不打开TCP延迟ACK功能 */
#define SEF_TCP_DELAYED_ACK_DISABLE 0

/* 打开TCP延迟ACK功能 */
#define SEF_TCP_DELAYED_ACK_ENABLE 1

/* 预配置项结构定义 */
typedef struct tagSFE_PRECFG_VALUE
{
    UINT32 u32Key;              /* 预配置参数ID */
    UINT32 u32Cfg_Value;        /* 配置值 */
    UINT32 u32Min_Value;        /* 可配置值的下限 */
    UINT32 u32Max_Value;        /* 可配置值的上限 */
    CHAR   ai8KeyName[LEN_64];  /* 预配置项名字 */
}SFE_PRECFG_VALUE_S;

/*******************************************************************************
*    Func Name: SFE_Init
* Date Created: 2009-7-29
*       Author: w60786
*      Purpose: SFE数据面初始化入口函数
*  Description: 本函数初始化数据面，请在调用该函数前注册钩子函数、设置预配置参数。
*        Input: VOID
*       Output: 
*       Return: 成功: SFE_OK
*               失败: 错误码
*      Caution: 1.初始化时不考虑资源释放问题.即初始化失败时不进行资源回收处理.
*                 原因:1)初始化过程不允许失败;
*                      2)涉及到多核共享问题,如果释放会导致其它核访问异常.
*               2.在调用该初始化函数之前,产品必须先注册维测相关钩子,再注册其它钩子
*                 和进行预配置处理.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                           DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-7-29    wangmingxia/luowentong         Creat the first version.
*
*******************************************************************************/
extern UINT32 SFE_Init(VOID);

/*******************************************************************************
*    Func Name: SFE_Set_PreConfigPara
* Date Created: 2009-7-28
*       Author: wangmingxia/luowentong
*      Purpose: SFE预配置参数值设置函数
*  Description: 本函数将预配置项参数u32Key的值设置为ulValue。
*               该函数必须在数据面初始化之前调用。
*        Input: UINT32 u32Key: 预配置项,取值范围见枚举定义SFE_PRECONFIG_INFO_E
*               UINT32 ulValue: 参数值
*       Output: 
*       Return: 成功: SFE_ENTRY_OK
*               失败: 错误码
*      Caution: 此函数提供给产品配置预配置项值,配置的是本VCPU的全局变量
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                         DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-7-28    wangmingxia/luowentong       Creat the first version.
*
*******************************************************************************/
extern UINT32 SFE_Set_PreConfigPara(UINT32 u32Key, UINT32 ulValue);

/*******************************************************************************
*    Func Name: SFE_Get_PreConfigPara
* Date Created: 2009-7-28
*       Author: wangmingxia/luowentong
*      Purpose: SFE预配置参数值获取函数
*  Description: 本函数获取预配置项pstComPara->u32Key的配置值、可配置的下限、
*               可配置的上限和预配置项名称，并将他们存放在参数pstComPara中。
*        Input: SFE_PRECFG_VALUE_S *pstComPara: 预配置结构信息
*       Output: SFE_PRECFG_VALUE_S *pstComPara: 预配置结构信息
*       Return: 成功: SFE_ENTRY_OK
*               失败: 错误码
*      Caution: 如果已经申请了共享内存，则返回共享内存的值，否则返回私有内存的值
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                         DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-7-28    wangmingxia/luowentong       Creat the first version.
*
*******************************************************************************/
extern UINT32 SFE_Get_PreConfigPara(SFE_PRECFG_VALUE_S *pstComPara);

/*******************************************************************************
*    Func Name: SFE_Show_PreConfigPara
* Date Created: 2009-7-31
*       Author: wangmingxia/luowentong
*      Purpose: 显示预配置项信息
*  Description: 显示预配置项信息,本函数显示以下预配置项信息：预配置项名称、配置值、可配置的下限和可配置的上限。
*       Output: 
*       Return: VOID
*      Caution: Important points if any
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                         DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-7-31    wangmingxia/luowentong       Creat the first version.
*
*******************************************************************************/
extern VOID SFE_Show_PreConfigPara(VOID);

/*******************************************************************************
*    Func Name: SFE_Set_ShareMemoryID
* Date Created: 2009-8-24
*       Author: w60786
*      Purpose: 设置数据面使用的各类型共享内存的ID
*  Description: 本函数将数据面核间共享内存分区号设置为u32SfeShareMemoryID，将数据面
*               核与控制面核用户态共享内存分区号设置为u32SfeUserShareMemoryID，将数
*               据面核与控制面核内核态共享内存分区号设置为u32SfeCoreShareMemoryID。
*        Input: UINT32 u32SfeShareMemoryID: 数据面核间共享内存分区号
*               UINT32 u32SfeUserShareMemoryID: 所有数据面核和控制面核用户态共享内存分区号
*               UINT32 u32SfeCoreShareMemoryID: 所有数据面核和控制面核内核态共享内存分区号
*       Output:
*       Return: 成功: SFE_ENTRY_OK
*               失败: 错误码
*      Caution: 各内存分区号必须在数据面初始化之前设置好.要求必须所有核都要进行相同的设置
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-8-24    w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 SFE_Set_ShareMemoryID(UINT32 u32SfeShareMemoryID, UINT32 u32SfeUserShareMemoryID,
                                      UINT32 u32SfeCoreShareMemoryID);

/*******************************************************************************
*    Func Name: SFE_Get_ShareMemoryID
* Date Created: 2009-8-24
*       Author: w60786
*      Purpose: 获取数据面使用的各类型共享内存的ID
*  Description: 获取数据面使用的各类型共享内存的ID
*        Input: 
*       Output: UINT32 *pu32SfeShareMemoryID: 数据面核间共享内存分区号
*               UINT32 *pu32SfeUserShareMemoryID: 所有数据面核和控制面核用户态共享内存分区号
*               UINT32 *pu32SfeCoreShareMemoryID: 所有数据面核和控制面核内核态共享内存分区号
*       Return: 成功: SFE_ENTRY_OK
*               失败: 错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-8-24    w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 SFE_Get_ShareMemoryID(UINT32 *pu32SfeShareMemoryID, UINT32 *pu32SfeUserShareMemoryID,
                                      UINT32 *pu32SfeCoreShareMemoryID);

/*******************************************************************************
*    Func Name: SFE_Show_ShareMemoryID
* Date Created: 2009-8-24
*       Author: w60786
*      Purpose: 显示数据面使用的各类型共享内存的ID
*  Description: 显示数据面使用的各类型共享内存的ID
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-8-24    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID SFE_Show_ShareMemoryID(VOID);

/*******************************************************************************
*    Func Name: SFE_ShowVersion
* Date Created: 2009-8-31
*       Author: w60786
*      Purpose: 显示数据面版本信息
*  Description: 显示数据面版本信息
*        Input: VOID
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-8-31    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID SFE_ShowVersion(VOID);

/*******************************************************************************
*    Func Name: SFE_Show_StubDeleteModule
* Date Created: 2009-10-22
*       Author: wuhailan103194
*      Purpose: 显示裁减的模块信息
*  Description: 显示裁减的模块信息
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-22   wuhailan103194          Create
*
*******************************************************************************/
extern VOID SFE_Show_StubDeleteModule(VOID);

#ifdef  __cplusplus
}
#endif

#endif


