/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sfe_debug_api.h
*
*  Project Code: V1.1.0
*   Module Name:
*  Date Created: 2009-8-31
*        Author: w60786
*   Description: 数据面维测相关对外API结构定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-8-31    w60786           Creat the first version.
*
*******************************************************************************/

#ifndef _SFE_DEBUG_API_H_
#define _SFE_DEBUG_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif


/* 数据面维测模块错误码定义 */
typedef enum enumSfeDebugErrCode
{
    SFE_DEBUG_OK = SFE_OK,                          /* 操作成功 */
    SFE_DEBUG_ERR_BEGIN = SFE_DEBUG_BEGIN_RET_CODE, /* 模块错误码起始值,建议内部不要使用该值 */
    SFE_DEBUG_ALREADY_INIT_REGLOG,                  /* 1  注册日志输出函数时系统已经初始化 */
    SFE_DEBUG_ALREADY_INIT_REGDEBUG,                /* 2  注册调试输出函数时系统已经初始化 */
    SFE_DEBUG_ALREADY_INIT_REGINFO,                 /* 3  注册信息输出函数时系统已经初始化 */
    SFE_DEBUG_ALREADY_INIT_REGWARNING,              /* 4  注册告警输出函数时系统已经初始化 */
    SFE_DEBUG_NULL_POINTER_REGLOG,                  /* 5  注册日志输出函数时传入空指针 */
    SFE_DEBUG_FUNC_NULL_POINTER_REGLOG,             /* 6  注册日志输出函数时传入的注册函数为空指针 */
    SFE_DEBUG_NULL_POINTER_REGDEBUG,                /* 7  注册调试输出函数时传入空指针 */
    SFE_DEBUG_NULL_POINTER_REGINFO,                 /* 8  注册信息输出函数时传入空指针 */
    SFE_DEBUG_NULL_POINTER_REGWARNING,              /* 9  注册告警输出函数时传入空指针 */
    SFE_DEBUG_NULL_POINTER_GETLOGLEVEL,             /* 10 获取日志级别时传入空指针 */
    SFE_DEBUG_NULL_POINTER_GETLOGTYPE,              /* 11 获取日志类型时传入空指针 */
    SFE_DEBUG_NULL_POINTER_GETDEBUGSWITCH,          /* 12 获取调试开关时传入空指针 */
    SFE_DEBUG_SHAREVAR_NULL_POINTER_SETLOGLEVEL,    /* 13 设置日志级别时共享变量指针为NULL */
    SFE_DEBUG_SHAREVAR_NULL_POINTER_GETLOGLEVEL,    /* 14 获取日志级别时共享变量指针为NULL */
    SFE_DEBUG_SHAREVAR_NULL_POINTER_SETLOGTYPE,     /* 15 设置日志类型时共享变量指针为NULL */
    SFE_DEBUG_SHAREVAR_NULL_POINTER_GETLOGTYPE,     /* 16 获取日志类型时共享变量指针为NULL */
    SFE_DEBUG_SHAREVAR_NULL_POINTER_SETDEBUGTYPE,   /* 17 设置调试类型开关时共享变量指针为NULL */
    SFE_DEBUG_SHAREVAR_NULL_POINTER_SETDEBUGVCPU,   /* 18 设置调试VCPU开关时共享变量指针为NULL */
    SFE_DEBUG_SHAREVAR_NULL_POINTER_SETDEBUGMODULE, /* 19 设置调试模块开关时共享变量指针为NULL */
    SFE_DEBUG_SHAREVAR_NULL_POINTER_TYPE_GETDEBUG,  /* 20 获取调试开关时调试类型开关共享变量指针为NULL */
    SFE_DEBUG_SHAREVAR_NULL_POINTER_VCPU_GETDEBUG,  /* 21 获取调试开关时调试VCPU开关共享变量指针为NULL */
    SFE_DEBUG_SHAREVAR_NULL_POINTER_MODULE_GETDEBUG,/* 22 获取调试开关时调试模块开关共享变量指针为NULL */
    SFE_DEBUG_MALLOC_FAIL_OUTPUTTOCOM,              /* 23 初始化时分配输出到com口共享变量空间失败 */
    SFE_DEBUG_MALLOC_FAIL_LOGLEVEL,                 /* 24 初始化时分配日志级别共享变量空间失败 */
    SFE_DEBUG_MALLOC_FAIL_LOGTYPE,                  /* 25 初始化时分配日志类型共享变量空间失败 */
    SFE_DEBUG_MALLOC_FAIL_MANUALSTAT,               /* 26 初始化时分配手动统计共享变量空间失败 */
    SFE_DEBUG_MALLOC_FAIL_AUTOSTAT,                 /* 27 初始化时分配自动统计共享变量空间失败 */
    SFE_DEBUG_MALLOC_FAIL_DEBUGTYPE,                /* 28 初始化时分配调试类型共享变量空间失败 */
    SFE_DEBUG_MALLOC_FAIL_DEBUGVCPU,                /* 29 初始化时分配调试VCPU共享变量空间失败 */
    SFE_DEBUG_MALLOC_FAIL_DEBUGMODULE,              /* 30 初始化时分配调试模块共享变量空间失败 */
    SFE_DEBUG_ADD_NAMEDB_LOGLEVEL,                  /* 31 初始化时将日志级别共享变量加入名字库失败 */
    SFE_DEBUG_ADD_NAMEDB_LOGTYPE,                   /* 32 初始化时将日志类型共享变量加入名字库失败 */
    SFE_DEBUG_LEVEL_INVALID_SETLOGLEVEL,            /* 33 设置日志级别时日志级别不合法 */
    SFE_DEBUG_PARA_INVALID_SETLOGTYPE,              /* 34 设置日志类型时参数不合法 */
    SFE_DEBUG_GET_MAX_FLOW_NUM_PRECFG_FAIL,         /* 35 初始化时获取流统计个数预配置规格失败 */
    SFE_DEBUG_MALLOC_FAIL_FLOWSTATINFO,             /* 36 初始化时分配流统计信息空间失败 */
    SFE_DEBUG_ADD_NAMEDB_FLOWSTATINFO,              /* 37 初始化时将流统计信息空间变量加入名字库失败 */
    SFE_DEBUG_MALLOC_FAIL_FLOWSTATRULE,             /* 38 初始化时分配流统计规则空间失败 */
    SFE_DEBUG_ADD_NAMEDB_FLOWSTATRULE,              /* 39 初始化时将流统计规则空间变量加入名字库失败 */
    SFE_DEBUG_MALLOC_FAIL_MANUALFLOWSTAT,           /* 40 初始化时分配流统计手动统计项空间失败 */
    SFE_DEBUG_MALLOC_FAIL_AUTOFLOWSTAT,             /* 41 初始化时分配流统计自动统计项空间失败 */

    SFE_DEBUG_NULL_POINTER_GET_STATALLINFO,         /* 42 获取全局统计相关信息时,输入参数指针为NULL */

    SFE_DEBUG_INPUT_PARA_NULL_CFG_FLOWSTATISTIC,    /* 43 配置流规则时,输入参数为NULL */
    SFE_DEBUG_VCPU_NOT_INIT_CFG_FLOWSTATISTIC,      /* 44 配置流规则时,所在VCPU没有初始化 */
    SFE_DEBUG_VRF_INVALID_CFG_FLOWSTATISTIC,        /* 45 配置流规则时,VRF参数非法 */
    SFE_DEBUG_PRONO_INVALID_CFG_FLOWSTATISTIC,      /* 46 配置流规则时,协议号参数非法 */
    SFE_DEBUG_OPERTYPE_INVALID_CFG_FLOWSTATISTIC,   /* 47 配置流规则时,操作类型非法 */
    SFE_DEBUG_SHAREVAR_NULL_ADD_FLOWSTATISTIC,      /* 48 添加流规则时,核间共享变量指针为NULL */
    SFE_DEBUG_REACHED_MAXNUM_ADD_FLOWSTATISTIC,     /* 49 添加流规则时,当前规则数已达到最大值 */
    SFE_DEBUG_NO_FREENODE_ADD_FLOWSTATISTIC,        /* 50 添加流规则时,不存在空间的流规则空间 */
    SFE_DEBUG_FLOWID_INVALID_ADD_FLOWSTATISTIC,     /* 51 添加流规则时,流规则空间中的流ID不是期望的流ID */
    SFE_DEBUG_SHAREVAR_NULL_DEL_FLOWSTATISTIC,      /* 52 删除流规则时,核间共享变量指针为NULL */
    SFE_DEBUG_NO_RULE_DEL_FLOWSTATISTIC,            /* 53 删除流规则时,当前不存在流规则,规则数为0 */
    SFE_DEBUG_NO_SAMERULE_DEL_FLOWSTATISTIC,        /* 54 删除流规则时,有规则但待删除的规则不存在 */
    SFE_DEBUG_SHAREVAR_NULL_DELALL_FLOWSTATISTIC,   /* 55 删除所有流规则时,核间共享变量指针为NULL */
    SFE_DEBUG_SHAREVAR_NULL_SET_FLOWSTATSWITCH,     /* 56 设置流统计开关时,核间共享变量指针为NULL */
    SFE_DEBUG_SWITCH_INVALID_SET_FLOWSTATSWITCH,    /* 57 设置流统计开关时,开关值不合法 */
    SFE_DEBUG_SHAREVAR_NULL_GET_FLOWSTATSWITCH,     /* 58 获取流统计开关时,核间共享变量为NULL */
    SFE_DEBUG_NULL_POINTER_GET_FLOWSTATSWITCH,      /* 59 获取流统计开关时,输入参数指针为NULL */
    SFE_DEBUG_SHAREVAR_NULL_GET_FLOWSTATRULENUM,    /* 60 获取流统计规则数时,核间共享变量为NULL */
    SFE_DEBUG_NULL_POINTER_GET_FLOWSTATRULENUM,     /* 61 获取流统计规则数时,输入参数指针为NULL */
    SFE_DEBUG_NULL_POINTER_GET_FLOWSTATALLINFO,     /* 62 获取流统计相关信息时,输入参数指针为NULL */

    SFE_DEBUG_FLOWSTAT_6KEY_MATCHFLOW_EXCEEDMAX,    /* 63 流统计五元组匹配时,匹配的流数超过最大值 */
    SFE_DEBUG_FLOWSTAT_4KEY_MATCHFLOW_EXCEEDMAX,    /* 64 流统计三元组匹配时,匹配的流数超过最大值 */

    SFE_DEBUG_MALLOC_FAIL_DEBUGCNT,                 /* 65 初始化时分配详细调试报文个数共享变量失败 */
    SFE_DEBUG_ADD_NAMEDB_DEBUGCNT,                  /* 66 初始化时将详细调试报文个数共享变量加入名字库失败 */
    SFE_DEBUG_MALLOC_FAIL_DEBUGCURCNT,              /* 67 初始化时分配详细调试的当前次数共享变量失败 */
    SFE_DEBUG_MALLOC_FAIL_DEBUGLEN,                 /* 68 初始化时分配详细调试报文长度共享变量失败 */
    SFE_DEBUG_ADD_NAMEDB_DEBUGLEN,                  /* 69 初始化时将详细调试报文长度共享变量加入名字库失败 */
    SFE_DEBUG_MALLOC_FAIL_DEBUGSWITCH,              /* 70 初始化时分配消息或事件共享变量失败 */
    SFE_DEBUG_SHARE_NULL_POINTER_SETMSGDEBUG,       /* 71 设置消息或EVENT共享变量指针为NULL */
    SFE_DEBUG_SHARE_PARA_ERR_SETMSGDEBUG,           /* 72 设置消息或事件调试开关,参数错误 */
    SFE_DEBUG_SHARE_NULL_POINTER_GETMSGDEBUG,       /* 73 获取消息或EVENT共享变量指针为NULL */
    SFE_DEBUG_SHARE_PARA_ERR_GETMSGDEBUG,           /* 74 获取消息或事件调试开关,参数错误 */
    SFE_DEBUG_CNTSHARE_NULL_POINTER_SETVERBOSEDBG,  /* 75 设置详细调试的报文次数和报文长度时共享变量为NULL */
    SFE_DEBUG_LENSHARE_NULL_POINTER_SETVERBOSEDBG,  /* 76 设置详细调试的报文次数和报文长度时共享变量为NULL */
    SFE_DEBUG_NULL_POINT_GETVERBOSEDEBUG,           /* 77 获取详调报文次数和报文长度时,指针为NULL */
    SFE_DEBUG_CNTSHARE_NULL_POINTER_GETVERBOSEDBG,  /* 78 获取详细调试的报文次数和报文长度时共享变量为NULL */
    SFE_DEBUG_LENSHARE_NULL_POINTER_GETVERBOSEDBG,  /* 79 获取详细调试的报文次数和报文长度时共享变量为NULL */
    SFE_DEBUG_DEBUGTYPE_SWITCH_INVALID,             /* 80 设置调试类型开关时,调试类型开关值不合法 */
    SFE_DEBUG_MANUAL_SHAREVAR_NULL_CLEARALLSTAT,    /* 81 清除所有全局统计信息时,全局手动统计共享变量为NULL */
    SFE_DEBUG_AUTO_SHAREVAR_NULL_CLEARALLSTAT,      /* 82 清除所有全局统计信息时,全局自动统计共享变量为NULL */
    SFE_DEBUG_MANUAL_SHAREVAR_NULL_CLEARALLFLOWSTAT,/* 83 清除所有流统计信息时,手动流统计共享变量为NULL */
    SFE_DEBUG_AUTO_SHAREVAR_NULL_CLEARALLFLOWSTAT,  /* 84 清除所有流统计信息时,自动流统计共享变量为NULL */
    SFE_DEBUG_SHAREVAR_NULL_POINTER_CLR_ALLTCPSTAT, /* 85 清除所有核上的TCP统计时,核间共享变量为NULL */
    SFE_DEBUG_SHAREVAR_NULL_POINTER_GET_TCPSTAT,    /* 86 获取TCP统计时,核间共享变量为NULL */
    SFE_DEBUG_NULL_POINTER_GET_TCPSTAT,             /* 87 获取TCP统计信息时,输入参数指针为NULL */
    SFE_DEBUG_GET_TCPSTAT_VCPU_INVALID,             /* 88 获取TCP统计信息时,输入的VCPU ID参数不合法 */
    SFE_DEBUG_SHAREVAR_NULL_POINTER_CLR_TCPSTAT,    /* 89 清除TCP统计时,核间共享变量为NULL */
    SFE_DEBUG_CLR_TCPSTAT_VCPU_INVALID,             /* 90 清除TCP统计信息时,输入的VCPU ID参数不合法 */


}SFE_DEBUG_ERR_CODE_E;

/* 异常调试信息输出位开关 */
#define SFE_DEBUG_TYPE_ERROR        0x0001
/* 入口出口调试信息输出位开关 */
#define SFE_DEBUG_TYPE_INOUT        0x0002
/* 重要处理流程调试信息输出位开关 */
#define SFE_DEBUG_TYPE_PROC         0x0004
/* 详细调试信息输出位开关*/
#define SFE_DEBUG_TYPE_VERBOSE      0x0008

/* 日志类型:告警类型日志位 */
#define SFE_LOG_TYPE_WARNING        0x0001
/* 日志类型:配置类型日志位 */
#define SFE_LOG_TYPE_CFG            0x0002
/* 日志类型:运行类型日志位 */
#define SFE_LOG_TYPE_RUN            0x0004

/* 日志输出的等级 */
typedef enum SFE_LOG_LEVEL_Etag
{
    SFE_LOG_LEVEL_CRITICAL = 0, /* 严重级别 */
    SFE_LOG_LEVEL_ERROR,        /* 错误级别 */
    SFE_LOG_LEVEL_WARNING,      /* 告警级别 */
    SFE_LOG_LEVEL_INFO,         /* 信息级别 */
    SFE_LOG_LEVEL_DEBUG,        /* 调试级别 */
    SFE_LOG_LEVEL_END,          /* 级别无效边界值 */
}SFE_LOG_LEVEL_E;

/* 告警类型 */
typedef enum SFE_WARNING_TYPE_Etag
{
    SFE_WARNING_TYPE_EVENT = 0, /* 事件类型告警 */
    SFE_WARNING_TYPE_OPERATION, /* 操作类型告警 */
    SFE_WARNING_TYPE_END,       /* 告警类型无效边界值 */
}SFE_WARNING_TYPE_E;

/* 告警ID */
typedef enum SFE_WARNING_ID_Etag
{
    SFE_WARNING_ID_DRV_RCVQUE_STATE = 0,    /* 驱动接收报文队列当前状态(上下限)告警 */
    SFE_WARNING_ID_DRV_IFSTATE,             /* 驱动接口UP/DOWN变化告警 */
    SFE_WARNING_ID_SOCK_RCVBUF_FULL,        /* socket接收缓冲区满告警 */

    SFE_WARNING_ID_END,       /* 告警类型无效边界值 */
}SFE_WARNING_ID_E;

/* 驱动报文接收队列状态为,当前接收报文队列中的报文数小于等于用户设定的告警下限值 */
#define SFE_DRV_RCVQUESTATE_LOWTHAN_LOWLIMIT      0
/* 驱动报文接收队列状态为,当前接收报文队列中的报文数大于等于用户设定的告警上限值 */
#define SFE_DRV_RCVQUESTATE_EXCEED_UPLIMIT        1
/* 驱动报文接收队列状态为,驱动接收报文队列已满开始丢包告警 */
#define SFE_DRV_RCVQUESTATE_FULL_DROPPKT     2
/* 驱动接收报文队列当前状态(上下限)告警信息数据结构定义 */
typedef struct tagSFE_WARNING_DRV_RCVQUESTATE
{
    UINT32      u32VcpuId;      /* 引起告警的报文接收队列所在的VCPUID */
    UINT32      u32RcvQueState; /* 该VCPUID下的报文接收队列告警状态 */
}SFE_WARNING_DRV_RCVQUESTATE_S;

/* 告警时使用的接口名 */
#define SFE_WARNING_DRV_IFNAME_MAXLEN  16
/* 接口物理状态:UP */
#define SFE_WARNING_DRV_IFSTATE_UP   1
/* 接口物理状态:DOWN */
#define SFE_WARNING_DRV_IFSTATE_DOWN 2
/* 驱动接口UP/DOWN变化告警信息数据结构定义 */
typedef struct tagSFE_WARNING_DRV_IFSTATE
{
    UINT8                       u8PortType;       /* VISP数据面接口类型 */
    UINT8                       u8Reserved;       /* 端口类型 */
    UINT16                      u16PortNo;        /* VISP数据面接口ID */
    UINT32                      u32DrvIfIndex;    /* 驱动接口索引(SCG产品使用方式下为Linux接口索引) */
    UINT32                      u32DrvIfPhyState; /* 零拷贝内核上报的接口物理状态,当前该字段未使用,未生效 */
    UINT8                       u8DrvIfName[SFE_WARNING_DRV_IFNAME_MAXLEN]; /* 驱动接口名 */
}SFE_WARNING_DRV_IFSTATE_S;

/* 当前接收报文大小加上接收缓冲区中已有数据超过了总的接收缓冲区大小 */
#define SFE_WARNING_SOCK_BUFFULL_REASON_NORMAL   0
/* 当前接收报文大小超过了总的接收缓冲区大小 */
#define SFE_WARNING_SOCK_BUFFULL_REASON_ONEPKT_EXCEED_RCVBUF   1
/* socket接收缓冲区满告警信息数据结构定义 */
typedef struct tagSFE_WARNING_SOCK_RCVBUF_FULL
{
    INT32  i32Fd;                                 /* socket id */
    INT32  i32RelativeFd;                         /* 相关联的socket id(如果有),用于TCP/UDP重排 */
    UINT32 u32LocalIP;                            /* 本地地址,报文中的目的地址(网络字节序) */
    UINT32 u32RemoteIP;                           /* 远端地址,报文中的源地址(网络字节序) */
    UINT16 u16LocalPort;                          /* 本地端口,报文中的目的端口(网络字节序) */
    UINT16 u16RemotePort;                         /* 远端端口,报文中的源端口(网络字节序) */
    UINT8  u8Protocol;                            /* 协议号 */
    UINT8  u8Reason;                              /* 缓冲区满的原因 */
    UINT8  u8Reserved[2];                         /* 保留字段 */
}SFE_WARNING_SOCK_RCVBUF_FULL_S;

/* 调试信息输出钩子函数原型 */
typedef VOID (*gpfSFEDebugOutput)(CHAR *pcDebugInfo);
/* 显示信息输出钩子函数原型 */
typedef VOID (*gpfSFEInfoOutput)(CHAR *pcInfo);
/* 告警信息输出钩子函数原型 */
typedef VOID (*gpfSFEWarningOutput)(UINT32 u32WarningID, UINT32 u32WarningType, VOID* pWarningPara);
/* 日志输出钩子原型结构 */
typedef struct tagSFE_LOG_HOOK_FUNC
{
    VOID (*pfSFE_FixlenLogOutput)(UINT32 u32LogCode, UINT32 u32LogLevel,
                                    UINT32 u32LogType, VOID* pFormat,
                                    UINT32 u32Para1, UINT32 u32Para2,
                                    UINT32 u32Para3, UINT32 u32Para4);
    VOID (*pfSFE_VarlenLogOutput)(UINT32 u32LogCode, UINT32 u32LogLevel,
                                    UINT32 u32LogType, VOID* pFormat, VOID* pData);
}SFE_LOG_HOOK_FUNC;


/*******************************************************************************
*    Func Name: SFE_RegDebugOutputHookFunc
* Date Created: 2009-07-29
*       Author: w60786/luowentong
*      Purpose: 调试信息输出钩子注册函数
*  Description: 调试信息输出钩子注册函数
*        Input: gpfSFEDebugOutput pfDebugOutput: 待注册钩子函数
*       Output: 
*       Return: 成功: SFE_DEBUG_OK
*               失败: 错误码
*      Caution: 此函数必须在数据面初始化前调用
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-29   w60786/luowentong                             Create
*
*******************************************************************************/
extern UINT32 SFE_RegDebugOutputHookFunc(gpfSFEDebugOutput pfDebugOutput);

/*******************************************************************************
*    Func Name: SFE_RegInfoOutputHookFunc
* Date Created: 2009-07-29
*       Author: w60786/luowentong
*      Purpose: 显示类信息输出钩子注册函数
*  Description: 显示类信息输出钩子注册函数
*        Input: gpfSFEInfoOutput pfInfoOutput: 待注册钩子函数
*       Output: 
*       Return: 成功: SFE_DEBUG_OK
*               失败: 错误码
*      Caution: 此函数必须在数据面初始化前调用
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-29   w60786/luowentong                             Create
*
*******************************************************************************/
extern UINT32 SFE_RegInfoOutputHookFunc(gpfSFEInfoOutput pfInfoOutput);

/*******************************************************************************
*    Func Name: SFE_RegWarningOutputHookFunc
* Date Created: 2009-07-29
*       Author: w60786/luowentong
*      Purpose: 告警输出钩子注册函数
*  Description: 告警输出钩子注册函数
*        Input: gpfSFEWarningOutput pfWarningOutput: 待注册钩子函数
*       Output: 
*       Return: 成功: SFE_DEBUG_OK
*               失败: 错误码
*      Caution: 此函数必须在数据面初始化前调用
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-29   w60786/luowentong                             Create
*
*******************************************************************************/
extern UINT32 SFE_RegWarningOutputHookFunc(gpfSFEWarningOutput pfWarningOutput);

/*******************************************************************************
*    Func Name: SFE_RegLogHookFunc
* Date Created: 2009-07-29
*       Author: w60786/luowentong
*      Purpose: 日志输出钩子注册函数
*  Description: 日志输出钩子注册函数
*        Input: SFE_LOG_HOOK_FUNC* pstHookFunc: 待注册钩子函数
*       Output: 
*       Return: 成功: SFE_DEBUG_OK
*               失败: 错误码
*      Caution: 此函数必须在数据面初始化前调用
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-29   w60786/luowentong                             Create
*
*******************************************************************************/
extern UINT32 SFE_RegLogHookFunc(SFE_LOG_HOOK_FUNC* pstHookFunc);

/*******************************************************************************
*    Func Name: SFE_SetDebugTypeSwitch
* Date Created: 2009-7-31
*       Author: w60786/luowentong
*      Purpose: 设置调试类型开关
*  Description: 设置调试类型开关
*        Input: UINT32 u32DebugTypeSwitch: 位调试类型开关值
*       Output: 
*       Return: 成功: SFE_DEBUG_OK
*               失败: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-31   w60786/luowentong                             Create
*
*******************************************************************************/
extern UINT32 SFE_SetDebugTypeSwitch (UINT32 u32DebugTypeSwitch);

/*******************************************************************************
*    Func Name: SFE_SetDebugVcpuSwitch
* Date Created: 2009-7-31
*       Author: w60786
*      Purpose: 设置调试VCPU开关
*  Description: 设置调试VCPU开关
*        Input: UINT32 u32DebugVcpuSwitch: 位调试VCPU开关值
*       Output: 
*       Return: 成功: SFE_DEBUG_OK
*               失败: 错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-31   w60786/luowentong                             Create
*
*******************************************************************************/
extern UINT32 SFE_SetDebugVcpuSwitch (UINT32 u32DebugVcpuSwitch);

/*******************************************************************************
*    Func Name: SFE_SetDebugModuleSwitch
* Date Created: 2009-7-31
*       Author: w60786
*      Purpose: 设置调试模块开关
*  Description: 设置调试模块开关
*        Input: UINT32 u32DebugModuleSwitch: 位调试模块开关值
*       Output: 
*       Return: 成功: SFE_DEBUG_OK
*               失败: 错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-31   w60786/luowentong                             Create
*
*******************************************************************************/
extern UINT32 SFE_SetDebugModuleSwitch (UINT32 u32DebugModuleSwitch);

/*******************************************************************************
*    Func Name: SFE_GetDebugSwitch
* Date Created: 2009-7-31
*       Author: w60786
*      Purpose: 获取各种调试开关
*  Description: 获取各种调试开关
*        Input: 
*       Output: UINT32* pu32DebugTypeSwitch: 调试类型开关
*               UINT32* pu32DebugVcpuSwitch: 调试VPU开关
*               UINT32* pu32DebugModuleSwitch: 调试模块开关
*       Return: 成功: SFE_DEBUG_OK
*               失败: 错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-31   w60786/luowentong                             Create
*
*******************************************************************************/
extern UINT32 SFE_GetDebugSwitch(UINT32* pu32DebugTypeSwitch, UINT32* pu32DebugVcpuSwitch,

                                         UINT32* pu32DebugModuleSwitch);

/*******************************************************************************
*    Func Name: SFE_ShowDebugSwitch
* Date Created: 2009-7-31
*       Author: w60786
*      Purpose: 显示各种调试开关信息
*  Description: 显示各种调试开关信息
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-31   w60786/luowentong                             Create
*
*******************************************************************************/
extern VOID   SFE_ShowDebugSwitch(VOID);

/*******************************************************************************
*    Func Name: SFE_SetLogLevel
* Date Created: 2009-7-31
*       Author: w60786/luowentong
*      Purpose: 设置日志记录级别开关
*  Description: 设置日志记录级别开关
*        Input: UINT32 u32LogLevel:日志级别
*       Output: 
*       Return: 成功: SFE_DEBUG_OK
*               失败: 错误码
*      Caution: Important points if any
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-31   w60786/luowentong                             Create
*
*******************************************************************************/
extern UINT32 SFE_SetLogLevel(UINT32 u32LogLevel);

/*******************************************************************************
*    Func Name: SFE_GetLogLevel
* Date Created: 2009-7-31
*       Author: w60786/luowentong
*      Purpose: 获取日志记录级别
*  Description: 获取日志记录级别
*        Input: 
*       Output: UINT32* pu32LogLevel:日志级别
*       Return: 成功: SFE_DEBUG_OK
*               失败: 错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-31   w60786/luowentong                             Create
*
*******************************************************************************/
extern UINT32 SFE_GetLogLevel(UINT32* pu32LogLevel);

/*******************************************************************************
*    Func Name: SFE_SetLogType
* Date Created: 2009-7-31
*       Author: w60786/luowentong
*      Purpose: 设置日志记录类型开关
*  Description: 设置日志记录类型开关
*        Input: UINT32 ul32WarningLogEnable: 告警日志记录开关
*               UINT32 u32CfgLogEnable: 配置日志记录开关
*               UINT32 u32RunLogEnable: 运行日志记录开关
*       Output: 
*       Return: 成功: SFE_DEBUG_OK
*               失败: 错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-31   w60786/luowentong                             Create
*
*******************************************************************************/
extern UINT32 SFE_SetLogType(UINT32 ul32WarningLogEnable, UINT32 u32CfgLogEnable, UINT32 u32RunLogEnable);

/*******************************************************************************
*    Func Name: SFE_GetLogType
* Date Created: 2009-7-31
*       Author: w60786/luowentong
*      Purpose: 获取日志记录类型开关
*  Description: 获取日志记录类型开关
*        Input: 
*       Output: UINT32* pu32WarningLogEnable: 告警日志记录开关值
*               UINT32* pul32CfgLogEnable: 配置日志记录开关值
*               UINT32* pu32RunLogEnable: 运行日志记录开关值
*       Return: 成功: SFE_DEBUG_OK
*               失败: 错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-31   w60786/luowentong                             Create
*
*******************************************************************************/
extern UINT32 SFE_GetLogType(UINT32* pu32WarningLogEnable, UINT32* pul32CfgLogEnable, UINT32* pu32RunLogEnable);

/*******************************************************************************
*    Func Name: SFE_ShowLogSwitch
* Date Created: 2009-7-31
*       Author: w60786/luowentong
*      Purpose: 显示日志记录级别和类型开关
*  Description: 显示日志记录级别和类型开关
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-31   w60786/luowentong                             Create
*
*******************************************************************************/
extern VOID   SFE_ShowLogSwitch(VOID);

/*******************************************************************************
*    Func Name: SFE_SetMsgOrEvent_DebugSwitch
* Date Created: 2009-7-31
*       Author: z62531
*      Purpose: 设置消息或事件调试开关。
*  Description: 设置消息或事件调试开关,1为打开,0为关闭
*        Input: UINT32 u32DebugSwitch:调试开关
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-31   z62531                                         Create
*
*******************************************************************************/
extern UINT32 SFE_SetMsgOrEvent_DebugSwitch(UINT32 u32DebugSwitch);

/*******************************************************************************
*    Func Name: SFE_GetMsgOrEvent_DebugSwitch
* Date Created: 2009-7-31
*       Author: z62531
*      Purpose: 获取消息或事件调试开关。
*  Description: 获取消息或事件调试开关,1为打开,0为关闭
*        Input: UINT32 u32DebugSwitch:调试开关
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-31   z62531                                         Create
*
*******************************************************************************/
extern UINT32 SFE_GetMsgOrEvent_DebugSwitch(UINT32 *pu32DebugSwitch);

/*******************************************************************************
*    Func Name: SFE_SetVerboseDebug_CntAndLen
* Date Created: 2009-7-31
*       Author: z62531
*      Purpose: 设置详细调试报文的次数和长度
*  Description: 设置详细调试报文的次数和长度
*        Input: UINT32 u32PktNum:报文次数
*               UINT32 u32Length:调试报文的长度
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-31   z62531                                         Create
*
*******************************************************************************/
extern UINT32 SFE_SetVerboseDebug_CntAndLen(UINT32 u32PktNum, UINT32 u32Length);

/*******************************************************************************
*    Func Name: SFE_GetVerboseDebug_CntAndLen
* Date Created: 2009-7-31
*       Author: z62531
*      Purpose: 获取详细调试报文的次数和长度
*  Description: 获取详细调试报文的次数和长度
*        Input:
*       Output: UINT32 *pu32PktNum:报文次数
*               UINT32 *pu32Length:报文长度
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-31   z62531                                         Create
*
*******************************************************************************/
extern UINT32 SFE_GetVerboseDebug_CntAndLen(UINT32 *pu32PktNum, UINT32 *pu32Length);

/*******************************************************************************
*    Func Name: SFE_ShowAllStatistic
* Date Created: 2009-08-08
*       Author: wuhailan103194
*      Purpose: 显示所有统计信息情况
*  Description: 显示所有统计信息情况
*        Input: 
*       Output:
*       Return: VOID
*      Caution:
*    Reference: SFE_ShowAllStatistic
*               SFE_ShowAutoStatistic
*               SFE_ShowManualStatistic
*               SFE_ShowManualStatisticByVCPU
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-08   wuhailan103194          Create
*
*******************************************************************************/
extern VOID SFE_ShowAllStatistic(VOID);

/*******************************************************************************
*    Func Name: SFE_ShowAutoStatistic
* Date Created: 2009-08-08
*       Author: wuhailan103194
*      Purpose: 显示错误类(自动统计打点)计数情况
*  Description: 显示错误类(自动统计打点)计数情况
*        Input: 
*       Output:
*       Return: VOID
*      Caution:
*    Reference: SFE_ShowAllStatistic
*               SFE_ShowAutoStatistic
*               SFE_ShowManualStatistic
*               SFE_ShowManualStatisticByVCPU
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-08   wuhailan103194          Create
*
*******************************************************************************/
extern VOID SFE_ShowAutoStatistic(VOID);

/*******************************************************************************
*    Func Name: SFE_ShowManualStatistic
* Date Created: 2009-08-08
*       Author: wuhailan103194
*      Purpose: 显示正常(手动统计打点)计数情况
*  Description: 显示正常(手动统计打点)计数情况
*        Input: 
*       Output:
*       Return: VOID
*      Caution:
*    Reference: SFE_ShowAllStatistic
*               SFE_ShowAutoStatistic
*               SFE_ShowManualStatistic
*               SFE_ShowManualStatisticByVCPU
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-08   wuhailan103194          Create
*
*******************************************************************************/
extern VOID SFE_ShowManualStatistic(VOID);

/*******************************************************************************
*    Func Name: SFE_ShowManualStatisticByVCPU
* Date Created: 2009-08-17
*       Author: wuhailan103194
*      Purpose: 显示某个VCPU下的正常(手动打点)统计信息情况
*  Description: 显示某个VCPU下的正常(手动打点)统计信息情况
*        Input: UINT32 u32VCPUID:VCPU ID,
*               ID编号[0,31]:表示显示指定VCPU编号的手动统计信息
*               SFE_VCPU_MAX_NUM(32):表示循环显示各VCPU的手动统计信息
*               SFE_SHOW_TOTAL_MANUAL_STATISTIC(0xffffffff):表示显示各VCPU手动统计值之和
*       Output: 
*       Return: VOID
*      Caution: 
*    Reference: SFE_ShowAllStatistic
*               SFE_ShowAutoStatistic
*               SFE_ShowManualStatistic
*               SFE_ShowManualStatisticByVCPU
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-17   wuhailan103194          Create
*
*******************************************************************************/
extern VOID SFE_ShowManualStatisticByVCPU(UINT32 u32VCPUID);


#ifdef  __cplusplus
}
#endif

#endif


