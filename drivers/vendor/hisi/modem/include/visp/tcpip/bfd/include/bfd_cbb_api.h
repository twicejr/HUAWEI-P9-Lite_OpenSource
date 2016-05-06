/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              bfd_cbb_api.h
*
*  Project Code: VISPV100R006
*   Module Name: BFD API
*  Date Created: 2007-01-06
*        Author: Wangchengyang
*   Description: BFD PAI 函数声明以及宏、结构定义头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-12-07   Wangchengyang    Create
*
*******************************************************************************/
#ifndef _BFD_CBB_API_H_
#define _BFD_CBB_API_H_

#ifdef __cplusplus
extern "C" {
#endif

#define BFD_MAX_INTF_NAME_LEN   47
#define BFD_MAX_DESC_NAME_LEN   47
#define BFD_MAX_SESS_NAME_LEN   15
/* Begin:VISP1.7C03 VRF wangchengyang,2009-02-12 */
#define BFD_MAX_VRF_NAME_LEN   31
#define BFD_VRFNAME_LEN          VRF_MAX_VRFNAME_LENGTH
/* Begin:VISP1.7C03 VRF wangchengyang,2009-02-12 */
#define BFD_VRF_INVALIDINDEX 0xFFFFFFFF
/* END for BC3D03299 at 2010-05-31 */

/*BFD路由联动APP ID字段*/
#define BFD_FOR_OSPF_DETECT          0x00000001L
#define BFD_FOR_STATIC_ROUTE_DETECT  0x00000002L

/* BFD协议顺从性,为后续扩展性考虑，每一bit控制一个协议一致性问题 */
#define BFD_PROCOMPLIANCE_FOR_PF     0x00000001

/*Added by likaikun213099, 收到Rx=0的报文，应该停止发送BFD控制报文, 2014/9/19   问题单号:DTS2014090900429 */
#define BFD_PROCOMPLIANCE_FOR_RXZERO 0x00000002
/* End of Added by likaikun213099, 2014/9/19   问题单号:DTS2014090900429 */


/* BFD错误码定义如下 */
typedef enum tagBFD_ERR_E
{
    BFD_OK                         , /* 0 */
    BFD_ERR                        , /* 1 */
    BFD_ERR_DISABLE                , /* 2 BFD没有使能 */
    BFD_ERR_SESSION_ID             , /* 3 BFD Session ID非法,合法范围为[1,2000] */
    BFD_ERR_EXIST_SESSION          , /* 4 BFD会话已经存在 */
    BFD_ERR_SESSION_FULL           , /* 5 BFD会话已满,会话个数为512 */
    BFD_ERR_SESSION_NOT_EXIST      , /* 6 指定会话不存在 */
    BFD_ERR_NULL_POINTER           , /* 7 参数指针为空 */
    BFD_ERR_EVENT                  , /* 8 事件非法 */
    BFD_ERR_TX_INTERVAL            , /* 9 BFD发送时间间隔非法 */
    BFD_ERR_DETECT_MULT            , /* 10 BFD检测倍数非法 */
    BFD_ERR_SESSION_NOT_UP         , /* 11 当前BFD会话不为up */
    BFD_ERR_DISABLE_PROCESSING     , /* 12 BFD正在去使能 */
    BFD_ERR_CREATE_TASK            , /* 13 创建任务失败 */
    BFD_ERR_CREATE_QUEUE           , /* 14 创建队列失败 */
    BFD_ERR_CREATE_TIMER           , /* 15 创建定时器失败 */
    BFD_ERR_MEM_ALLOC              , /* 16 内存分配出错 */
    BFD_ERR_INVALID_PARAMETER      , /* 17 参数无效,一般用于0、1做逻辑真假的时候非0、1错误 */
    BFD_ERR_NOTIFIER               , /* 18 重复注册，或，删除不存在 */
    BFD_ERR_INVALID_ADDR           , /* 19 地址非法 */
    BFD_ERR_INTF_NOT_EXIST         , /* 20 指定接口不存在 */
    BFD_ERR_DISMATCH_IP_INDEX      , /* 21 指定接口索引和地址不匹配 */
    BFD_ERR_SRC_DST_IP_CONFLICT    , /* 22 创建会话源IP不为本机或者对端IP为本机 */
    BFD_ERR_NP_MODE                , /* 23 支持NP模式非法 */
    BFD_ERR_TASK_PRI               , /* 24 BFD任务优先级非法 */
    BFD_ERR_DETECT_MODE            , /* 25 检测模式非法 */
    BFD_ERR_DECODE_BFD_CTRLPKT     , /* 26 解析BFD报文出错 */
    BFD_ERR_APP_ID                 , /* 27 BFD应用ID非法 */
    BFD_ERR_BFD_PACKET             , /* 28 BFD报文选项出错 */
    BFD_ERR_PACKET_LEN             , /* 29 报文长度非法 */
    BFD_ERR_ONE_MULTI_HOP          , /* 30 报文单多跳非法 */
    BFD_ERR_BUILD_PKT              , /* 31 组装BFD控制报文出错 */
    BFD_ERR_HA_CREATE_SESSION      , /* 32 备板创建会话非法 */
    BFD_ERR_DEBUG_SWITCH           , /* 33 debug开关非法 */
    BFD_ERR_HA_IS_SMOOTHING        , /* 34 HA正在手动倒换或平滑处理 */
    BFD_ERR_NOT_INIT               , /* 35 BFD还未初始化 */
    BFD_ERR_QUE_BUSY               , /* 36 BFD配置消息队列忙 */
    BFD_ERR_WTR                    , /* 37 设置的WTR非法，合法范围为[0,BFD_MAX_WTR_TIME] */
    BFD_ERR_WRITEQUE_FAIL          , /* 38 写队列失败*/
    BFD_ERR_CREATE_OTHERQUEUE      , /* 39 创建OTHER队列失败 */
    BFD_ERR_CHECK_PACKET           , /* 40 CHECK BFD报文出错 */
    BFD_ERR_ZERODISCR              , /* 41 BFD处理表述符是0出错 */
    BFD_ERR_HANDLEPACKET           , /* 42 处理报文出错 */
    BFD_ERR_PORT                   , /* 43 报文的端口号错误 */
    BFD_ERR_CHECKCREATE            , /* 44 SH检查创建BFD会话错误 */
    BFD_ERR_CREATESESSION          , /* 45 创建BFD会话失败 */
    BFD_ERR_RX_INTERVAL            , /* 46 BFD接收时间间隔非法 */
    BFD_ERR_DISMATCH_TRUNK_IP      , /* 47 指定出接口为成员端口，但设置的本端IP不是所在trunk的IP */
    BFD_ERR_ONE_HOP_TTL            , /* 48 单跳报文TTL不为255 */
    BFD_ERR_GETTRUNK_BYPORT        , /* 49 通过成员端口获取trunk接口失败 */
    BFD_ERR_TRUNK_MODE_NOMATCH     , /* 50 用户设置的trunk bfd会话模式不匹配 */
    BFD_ERR_RECR_SESSION           , /* 51 重复创建ID相同的会话 */
    BFD_ERR_EXIST_SESSION_NAME     , /* 52 BFD会话名已经存在*/
    BFD_ERR_SESSION_NAME_DESC      , /* 53 配置的BFD会话名或描述信息长度异常*/
    BFD_ERR_GET_ENTRY_END          , /* 54 已到最后一个表项 */
    BFD_ERR_WAITLIST               , /* 55 WaitList机制返回异常*/
    BFD_ERR_INTF_NOT_L3ETH         , /* 56 二层端口不支持BFD */
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-01 */
    BFD_ERR_VRFINDEX               , /* 57 VRF不匹配 */
    BFD_ERR_FILTER                 , /* 58 过滤条件非法 */
    /* End:VISP1.7C03 VRF wangchengyang,2009-02-01 */
    /*Begin BC3D01505 关闭句柄出现段错误 l00147446 */
    BFD_ERR_MEM_RELEASE            , /* 59 释放内存出错*/
    /*END BC3D01505 关闭句柄出现段错误 l00147446 */
    BFD_ERR_GET_IPV6VTABLE         , /* 60 获取ipv6组件虚表失败 */
    BFD_ERR_IPVER_DISMATCH         , /* 61 BFD IP version不匹配 */
    BFD_ERR_SOCKET6                , /* 62 BFD6 操作socket失败 */

    /*63错误码是同步1.8C03的，1.8C05暂时未使用*/
    BFD_ERR_SESSION_FOR_OSPF_OR_STATIC  , /* 63 BFD会话被OSPF或者静态路由联动，不能删除 */
    BFD_ERR_SESSION_NAME                , /* 64  错误的会话名称*/

    /* BFD license功能错误码 --- start */
    BFD_ERR_LICENSE_WRONG_PARA     , /* 65 用户输入参数不正确 */
    BFD_ERR_LICENSE_IS_OFF         , /* 66 BFD License不通过 */
    BFD_ERR_LICENSE_CLOSE_MRCV     , /* 67 多跳报文接收socket关闭失败 */
    BFD_ERR_LICENSE_CLOSE_ORCV     , /* 68 单跳报文接收socket关闭失败 */
    BFD_ERR_LICENSE_CLOSE_SND      , /* 69 报文发送socket关闭失败 */
    BFD_ERR_LICENSE_GET_PRECFG     , /* 70 获取BFD6预配置失败 */
    BFD_ERR_LICENSE_BFD6_DISABLE   , /* 71 BFD6功能没有使能 */
    BFD_ERR_LICENSE_DISABLE_PROC   , /* 72 BFD License正在关闭中*/
    BFD_ERR_LICENSE_NOT_ENABLE     , /* 73 BFD License不在打开状态 */
    BFD_ERR_LICENSE_ENABLE         , /* 74 BFD License正处于使能中或已使能 */
    BFD_ERR_LICENSE_PROCING        , /* 75 BFD License正处于操作中 */
    /* BFD license功能错误码 ---  end  */
    BFD_ERR_GR_STATE               , /* 76 BFD GR状态错误 */
    BFD_ERR_NO_NP                  , /* 77 没有注册NP下发的钩子函数 */
    /*Begin BC3D02903 liangjicheng 2010-04-19 */
    BFD_ERR_CREATE_EXTQUEUE        , /* 78 创建OTHER队列失败 */
    /*End   BC3D02903 liangjicheng 2010-04-19 */

    /*SGSN需求DTS2010091302569: BFD 多会话和应用共用问题*/
    BFD_ERR_SESSION_CONFLICT,               /* 79 创建的静态会话或动态会话冲突 */

    BFD_ERR_DISABLE_WHEN_DELSES = 88,       /*88 BFD没有使能 */
    BFD_ERR_HA_IS_SMOOTHING_WHEN_DELSES,    /*89 BFD正在平滑过程中 */
    BFD_ERR_SESSION_ID_WHEN_DELSES,         /*90 BFD会话ID错误 */
    BFD_ERR_VRFINDEX_WHEN_DELSES,           /*91 VRF ID错误 */
    BFD_ERR_SESSION_NOT_EXIST_WHEN_DELSES,  /*92 BFD会话不存在 */
    BFD_ERR_MEM_ALLOC_VRFSESSENTY_ININIT,   /*93 BFD初始化时分配BFD会话全局表项定义内存失败 */
    BFD_ERR_MEM_ALLOC_GDBGSWTICH_ININIT,    /*94 BFD初始化时分配全局debug开关内存失败 */
    BFD_ERR_MEM_ALLOC_DISABLEONEVRF_ININIT, /*95 BFD初始化时分配去使能所有或单个VRF中BFD的标志内存失败 */
    /*Add for V2R3C05, by b0177000/y00176567, at 2011-06-03. 修改原因: V2R3C05 增加BFD会话创建时输入的协议类型错误码 */   
    BFD_ERR_PROTOCOL,                       /*96 BFD会话创建时输入的协议类型错误 */
    BFD_ERR_NOT_SUPORT_RFC_DEMANDMODE,      /*97 创建的BFD基于RFC的会话目前不支持查询模式 */
    BFD_ERR_MEM_ALLOC_SESSENTY_INIT,        /*98 BFD初始化时分配BFD表内存失败 */
    BFD_ERR_NO_CREATE_PACKET,               /*99 会话缓存报文没有生成 */
    BFD_ERR_DETECTTIME_ZORE,                /*100 探测时间为0，有除零危险*/

    BFD_ERR_NSR_WRONG_STATE,                /*101 NSR当前状态不允许相关操作 */
    BFD_ERR_NSR_NO_ENABLE,                  /*102 NSR功能未使能*/
    BFD_ERR_NSR_NULL_PPI_HOOK,              /*103 NSR钩子未注册*/
    BFD_ERR_NSR_CREATE_NSRQUEUE,            /*104 创建OTHER队列失败 */
    BFD_ERR_NSR_UNFINISHED,                 /*105 NSR过程没有结束*/
    BFD_ERR_NSR_SESSION_ACTIVE,             /*106 NSR过程中激活会话*/
    BFD_ERR_NSR_ALLOC_BAKCACHE,             /*107 BFD NSR初始化时分配存放备份数据的内存失败*/
    BFD_ERR_NSR_ALLOC_SESSENTY_INIT,        /*108 BFD NSR初始化时分配备份的BFD表内存失败*/
    BFD_ERR_NSR_ALLOC_VRFSESSENTY_ININIT,   /*109 BFD NSR初始化时分配备份的BFD会话全局表项定义内存失败*/
    BFD_ERR_NSR_BAKDATA_OVERFLOW,           /*110 BFD NSR产品上报备份数据超出规格*/
    BFD_ERR_NSR_INVAILD_DSTPORT,            /*111 BFD NSR恢复过程中，检查目的端口错误*/

    BFD_ERR_PORT_IS_OFF,                    /*112 BFD不需要对外暴露端口3784和4784*/
    BFD_ERR_MAX                             /*错误码最大值,以后添加错误码请按顺序添加到此前 */
}BFD_ERR_E;

/* 会话信息数据结构 */
typedef struct tagBFD_SESSION_INFO_S
{
    ULONG ulSessionID;        /* 会话ID */
    ULONG ulSessionState;     /* 会话状态 0:AdminDown 1:Down 2:Init 3:Up  */
    ULONG ulCfgDetectMode;    /* 用户配置的本端探测模式，1:查询模式 2:异步模式 */
    ULONG ulCfgMinTxInterval; /* 用户配置的本端发送间隔，单位:ms */
    ULONG ulCfgMinRxInterval; /* 用户配置的本端接收间隔，单位:ms */
    ULONG ulCfgDetectMult;    /* 用户配置的本端探测倍数，取值范围3~10 */
    ULONG ulActDetectMode;    /* 协商生效的探测模式，1:查询模式 2:异步模式 */
    ULONG ulActTxInterval;    /* 协商生效的本端发送间隔，单位:ms */
    ULONG ulActRxInterval;    /* 协商生效的本端发送间隔，单位:ms */
    ULONG ulDetectTime;       /* 协商生效的本端探测时间，单位:ms */
    ULONG ulMyDiscriminator;  /* 本端描述符 */
    ULONG ulYourDiscriminator;/* 对端端描述符 */
    ULONG ulDstIPAddress;     /* 会话的目的地址，主机序 */
    ULONG ulSrcIPAddress;     /* 会话的源地址，主机序 */
    ULONG ulIsMultiHop;       /* 会话是否是多跳，0:不是 1:是 */
    ULONG ulSentPakcets;      /* 会话发送的报文总个数 */
    ULONG ulRcvPackets;       /* 会话接收的报文总个数 */
    ULONG ulLastSentTime;     /* 上一个报文发送的时间，通过VOS_Tm_Now获取的低32位，单位:ms */
    ULONG ulAppId;            /* 会话设定的应用组合 */
    ULONG ulUpToDown;         /* 会话自创建之后，状态由Up变Down的总次数 */
    /* Added by w61195 for A82D13244，2007-4-3，用户可以根据诊断字判断会话DOWN掉的原因 */
    ULONG ulDiagnostic;       /* 会话的诊断字(0-9)，诊断字9代表本端收到了对端的AdminDown报文，0-8参见RFC草案 */
    /* Added by w61195 for A82D14110，2007-4-16，用户配置的会话所在接口索引，多跳会话该值为0 */
    ULONG ulSessIfIndex;
    UCHAR ucTos;              /* bfd会话tos */
    UCHAR Padding[3];
    ULONG ulCurrentGRState;  /* 该BFD会话当前的GR状态, 取值见enumBFD_GR_STATE */
    /*Add for V2R3C05, by b0177000/y00176567, at 2011-06-03. 修改原因: V2R3C05 会话创建协议类型 */   
    ULONG ulBfdProtocol;      /* bfd会话协议类型 */
    /*Add for V2R3C05, by b0177000/y00176567, at 2011-06-03. 修改原因: V2R3C05 对端报文中RequiredMinRxInterval值 */   
    ULONG ulRemoteMri;        /* 对端报文中RequiredMinRxInterval值 */
    /*Add for V2R3C05, by b0177000/y00176567, at 2011-06-03. 修改原因: V2R3C05 对端报文中Demand值 */   
    ULONG ulRemoteDemandMode; /* 对端报文中Demand值,1:查询模式；0:非查询模式(异步模式) */
}BFD_SESSION_INFO_S;

typedef struct tagBFD6_SESSION_INFO_S
{
    ULONG ulSessionID;        /* 会话ID */
    ULONG ulSessionState;     /* 会话状态 0:AdminDown 1:Down 2:Init 3:Up  */
    ULONG ulCfgDetectMode;    /* 用户配置的本端探测模式，1:查询模式 2:异步模式 */
    ULONG ulCfgMinTxInterval; /* 用户配置的本端发送间隔，单位:ms */
    ULONG ulCfgMinRxInterval; /* 用户配置的本端接收间隔，单位:ms */
    ULONG ulCfgDetectMult;    /* 用户配置的本端探测倍数，取值范围3~10 */
    ULONG ulActDetectMode;    /* 协商生效的探测模式，1:查询模式 2:异步模式 */
    ULONG ulActTxInterval;    /* 协商生效的本端发送间隔，单位:ms */
    ULONG ulActRxInterval;    /* 协商生效的本端发送间隔，单位:ms */
    ULONG ulDetectTime;       /* 协商生效的本端探测时间，单位:ms */
    ULONG ulMyDiscriminator;  /* 本端描述符 */
    ULONG ulYourDiscriminator;/* 对端端描述符 */
    ULONG ulDstIPAddress[4];     /* 会话的目的地址，主机序 */
    ULONG ulSrcIPAddress[4];     /* 会话的源地址，主机序 */
    ULONG ulIsMultiHop;       /* 会话是否是多跳，0:不是 1:是 */
    ULONG ulSentPakcets;      /* 会话发送的报文总个数 */
    ULONG ulRcvPackets;       /* 会话接收的报文总个数 */
    ULONG ulLastSentTime;     /* 上一个报文发送的时间，通过VOS_Tm_Now获取的低32位，单位:ms */
    ULONG ulAppId;            /* 会话设定的应用组合 */
    ULONG ulUpToDown;         /* 会话自创建之后，状态由Up变Down的总次数 */
    ULONG ulDiagnostic;       /* 会话的诊断字(0-9)，诊断字9代表本端收到了对端的AdminDown报文，0-8参见RFC草案 */
    ULONG ulSessIfIndex;
    UCHAR ucTos;              /* bfd会话tos */
    UCHAR Padding[3];
    ULONG ulCurrentGRState;  /* 该BFD会话当前的GR状态, 取值见enumBFD_GR_STATE */
    ULONG ulBfdProtocol;      /* bfd会话协议类型 */
    ULONG ulRemoteMri;        /* 对端报文中RequiredMinRxInterval值 */
    ULONG ulRemoteDemandMode; /* 对端报文中Demand值,1:查询模式；0:非查询模式(异步模式) */
}BFD6_SESSION_INFO_S;
/* 检测模式类型 */
typedef enum tagBFD_API_DETECT_MODE_E
{
    BFD_DETECT_MODE_DEMAND = 0x1,          /* 查询模式 */
    BFD_DETECT_MODE_ASYNC,                 /* 异步模式*/
    BFD_DETECT_MODE_API_MAX
}BFD_API_DETECT_MODE_E;

/* BFD报文强制部分数据结构 */
typedef struct tagBFD_PACKET_S
{
#if ( VRP_BIG_ENDIAN == VRP_YES )
    UCHAR   bVers                   : 3 ;       /* BFD的版本信息 */
    UCHAR   bDiagnostic             : 5 ;       /* BFD的诊断信息 */
#else
    UCHAR   bDiagnostic             : 5 ;       /* BFD的诊断信息 */
    UCHAR   bVers                   : 3 ;       /* BFD的版本信息 */
#endif
#if ( VRP_BIG_ENDIAN == VRP_YES )
    UCHAR   bState                  : 2 ;       /* BFD的状态信息 */
    UCHAR   bPollFlag               : 1 ;       /* BFD的轮询标志 */
    UCHAR   bFinalFlag              : 1 ;       /* BFD的轮询回应标志 */
    UCHAR   bControlPlanFlag        : 1 ;       /* BFD和控制平面共存的标志 */
    UCHAR   bAuthenticationFlag     : 1 ;       /* BFD的认证标志 */
    UCHAR   bDemandModeFlag         : 1 ;       /* BFD的查询方式标志 */
    UCHAR   bReserved               : 1 ;       /* BFD的保留位 */
#else
    UCHAR   bReserved               : 1 ;       /* BFD的保留位 */
    UCHAR   bDemandModeFlag         : 1 ;       /* BFD的查询方式标志 */
    UCHAR   bAuthenticationFlag     : 1 ;       /* BFD的认证标志 */
    UCHAR   bControlPlanFlag        : 1 ;       /* BFD和控制平面共存的标志 */
    UCHAR   bFinalFlag              : 1 ;       /* BFD的轮询回应标志 */
    UCHAR   bPollFlag               : 1 ;       /* BFD的轮询标志 */
    UCHAR   bState                  : 2 ;       /* BFD的状态信息 */
#endif
    UCHAR   ucDetectMult                ;       /* BFD的检测倍数 */
    UCHAR   ucPacketLength              ;       /* BFD的报文长度 */
    ULONG   ulLocalDiscriminitor        ;       /* BFD的本地标识符 */
    ULONG   ulRemoteDiscriminitor       ;       /* BFD的对端标识符 */
    ULONG   ulDesiredMinTxInterval      ;       /* BFD期望的发送间隔 */
    ULONG   ulRequiredMinRxInterval     ;       /* BFD的本地接收能力 */
    ULONG   ulRequiredMinEchoRxInterval ;       /* BFD回声功能的发送间隔 */
} BFD_PACKET_S;

/* 会话更新参数数据结构 */
typedef struct tagBFD_SESSION_PARA_S
{
    ULONG ulDetectMode;      /* 会话检测模式:1查询模式;2异步模式 */
    ULONG ulMinTxInterval;   /* ms,最小发送时间间隔：10~1000ms */
    ULONG ulMinRxInterval;   /* ms,最小接收时间间隔：10~1000ms */
    ULONG ulDetectMult;      /* 检测倍数：3~50 */
}BFD_SESSION_PARA_S;

/* BFD全局信息 */
typedef struct tagBFD_GLOBAL_INFO
{
    ULONG ulBfdGlobalCapability  ;   /* BFD全局使能状态 */
    ULONG ulWtrTimeInterval      ;   /* BFD全局WTR时间间隔，单位:s */
    ULONG ulAdaptMultiHopPort    ;   /* 是否允许BFD多跳自动调整端口号 */
    ULONG ulFirstNegoTimes       ;   /* 首次协商次数 */
    ULONG ulCurrentBFDGRState    ;   /* 当前的BFD GR状态, 取值见enumBFD_GR_STATE */
    ULONG ulDetectTime           ;
    ULONG ulDetectFlag           ;
    ULONG ulAutoDiscrGate        ;   /*自动分配会话Id的门限*/
    ULONG ulBfd6AutoDiscrGate    ;   /*自动分配会话Id的门限*/    
    ULONG ulBfd6WtrTimeInterval;      /*BFD DOWN后下一次协商的延迟时间*/
    ULONG ulBfd6GlobalCapability;    /*BFD6 全局开关*/
    ULONG ulBfd6AdaptMultiHopPort;   /*BFD6 多跳是否和对端自适应*/    
} BFD_GLOBAL_INFO_S;

/* BFD会话查询过滤信息数据结构 */
typedef struct tagBFD_SESSION_FILTER_S {
    UCHAR szCfgName[BFD_MAX_SESS_NAME_LEN + 1];
    ULONG ulPeerAddr;
    ULONG ulLocalDiscr;
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-01 */
    CHAR  szVrfName[BFD_MAX_VRF_NAME_LEN + 1];
    /* End:VISP1.7C03 VRF wangchengyang,2009-02-01 */
    ULONG ulIsAllVRF;   /* 为1表示在所有的VRF中进行查找,为0表示在指定的VRF中进行查找 */
}BFD_SESSION_FILTER_S;

/* BFD会话统计信息数据结构 */
typedef struct tagBFD_SESSION_COUNT_S {
    UCHAR szCfgName[BFD_MAX_SESS_NAME_LEN + 1];
    UCHAR szSessionDes[BFD_MAX_DESC_NAME_LEN + 1];
    ULONG ulSessionId;
    ULONG ulLocalDiscr;
    ULONG ulRemoteDiscr;
    USHORT usSessState;
    USHORT usIsMultiHop;
    ULONG ulPktRcv;
    ULONG ulPktSend;
    ULONG ulPktRcvDrop;
    ULONG ulPktSendErr;
    ULONG ulSessionDownNum;
    ULONG ulSessionStateTime;
    ULONG ulLastDownTime;
    /* mody for BC3D03299 at 2010-05-31 */
    ULONG ulVrfIndex;
    ULONG ulPeerAddr[4];
    /* end mody for BC3D03299 at 2010-05-31 */
}BFD_SESSION_COUNT_S;

/* BFD会话配置信息数据结构 */
typedef struct tagBFD_SESSION_CONFIG_INFO_S {
    UCHAR szCfgName[BFD_MAX_SESS_NAME_LEN + 1];
    UCHAR szSessionDes[BFD_MAX_DESC_NAME_LEN + 1];
    ULONG ulLocalDiscr;
    ULONG ulSrcAddr;
    ULONG ulPeerAddr;
    ULONG ulDetectMult;
    ULONG ulMinTxInterval;
    ULONG ulMinRxInterval;
    ULONG ulOutIndex;
    ULONG ulAppId;
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-01 */
    CHAR  szVrfName[BFD_MAX_VRF_NAME_LEN + 1];
    /* End:VISP1.7C03 VRF wangchengyang,2009-02-01 */
    UCHAR ucTos;              /* bfd会话tos */
    UCHAR Padding[3];
    ULONG ulRemoteDiscr;
}BFD_SESSION_CONFIG_INFO_S;

/* BFD会话信息数据结构 */
typedef struct tagBFD_SESSION_ALL_INFO_S {
    BFD_SESSION_CONFIG_INFO_S stConfigInfo;
    ULONG ulRemoteDiscr;
    ULONG ulSessionId;
    USHORT usSessState;
    USHORT usIsMultiHop;
    ULONG ulActTxInterval;
    ULONG ulActRxInterval;
    /*Add for BC3D00792,DR.177 保存对端实际检测倍数 */
    ULONG ulActDetectMult;
    ULONG ulActDetectTime;
    USHORT usLocalDiag;
    USHORT usDstPort; /* 会话目的端口号(主机序) */
    ULONG ulRemoteMinTxInterval; /* 对端的MTI */
    ULONG ulRemoteMinRxInterval; /* 对端的MRI */
    USHORT usRemoteDemandMode;   /* 对端的检测模式 */
    UCHAR  ucRemoteDetectMult;   /* 对端的检测倍数 */
    UCHAR  ucRec;
}BFD_SESSION_ALL_INFO_S;

/* BFD6会话查询过滤信息数据结构 */
typedef struct tagBFD6_SESSION_FILTER_S {
    UCHAR szCfgName[BFD_MAX_SESS_NAME_LEN + 1];
    ULONG ulPeerAddr[4];
    ULONG ulLocalDiscr;
    CHAR  szVrfName[BFD_MAX_VRF_NAME_LEN + 1];
    ULONG ulIsAllVRF;   /* 为1表示在所有的VRF中进行查找,为0表示在指定的VRF中进行查找 */    
}BFD6_SESSION_FILTER_S;

/* BFD6会话配置信息数据结构 */
typedef struct tagBFD6_SESSION_CONFIG_INFO_S {
    UCHAR szCfgName[BFD_MAX_SESS_NAME_LEN + 1];
    UCHAR szSessionDes[BFD_MAX_DESC_NAME_LEN + 1];
    ULONG ulLocalDiscr;
    ULONG ulSrcAddr[4];
    ULONG ulPeerAddr[4];
    ULONG ulDetectMult;
    ULONG ulMinTxInterval;
    ULONG ulMinRxInterval;
    ULONG ulOutIndex;
    ULONG ulAppId;
    CHAR  szVrfName[BFD_MAX_VRF_NAME_LEN + 1];
    UCHAR ucTos;          /* bfd会话tos，暂不支持*/
    UCHAR Padding[3];     /*填充字段*/
    ULONG ulRemoteDiscr;     /*对端的描述符*/    
}BFD6_SESSION_CONFIG_INFO_S;

/* BFD6会话信息数据结构 */
typedef struct tagBFD6_SESSION_ALL_INFO_S {
    BFD6_SESSION_CONFIG_INFO_S stConfigInfo;
    ULONG ulRemoteDiscr;
    ULONG ulSessionId;
    USHORT usSessState;
    USHORT usIsMultiHop;
    ULONG ulActTxInterval;
    ULONG ulActRxInterval;
    ULONG ulActDetectMult;
    ULONG ulActDetectTime;
    USHORT usLocalDiag;
    USHORT usRemoteDemandMode;   /* 对端的检测模式 */
    ULONG ulRemoteMinTxInterval; /* 对端的MTI */
    ULONG ulRemoteMinRxInterval; /* 对端的MRI */
    UCHAR  ucRemoteDetectMult;   /* 对端的检测倍数 */
    UCHAR  ucReserve[1];         /* 填充字段 */
    USHORT usDstPort;            /* 会话目的端口号(主机序) */
}BFD6_SESSION_ALL_INFO_S;

/* BFD会话简要信息数据结构 */
typedef struct tagBFD_SESSION_BRIEF_INFO_S {
    UCHAR szCfgName[BFD_MAX_SESS_NAME_LEN + 1];
    UCHAR szSessionDes[BFD_MAX_DESC_NAME_LEN + 1];
    ULONG ulSessionId;
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-01 */
    CHAR  szVrfName[BFD_MAX_VRF_NAME_LEN + 1];
    /* End:VISP1.7C03 VRF wangchengyang,2009-02-01 */
}BFD_SESSION_BRIEF_INFO_S;
typedef struct tagBfdStatistic
{
    UCHAR ucIpVer;           /*IPv4 或者IPv6*/
    ULONG ulSrcAddr[4];      /*BFD会话的源地址（主机序）*/
    ULONG ulPeerAddr[4];     /*BFD会话的目的地址（主机序）*/
    /* 协商统计信息  接收*/
    ULONG ulBfdRcvDown;      /*接收的DOWN报文*/
    ULONG ulBfdRcvInit;      /*接收的Init报文*/
    ULONG ulBfdRcvUp;        /*接收的Up报文*/
    ULONG ulBfdRcvAdminDown; /*接收的AdminDown报文*/
    ULONG ulBfdRcvErr;       /*接收的错误报文*/
    ULONG ulBfdRcvP;         /*接收的P报文*/
    ULONG ulBfdRcvF;         /*接收的F报文*/

    /* 协商统计信息  发送*/
    ULONG ulBfdSndDown;      /*发送的DOWN报文*/
    ULONG ulBfdSndInit;      /*发送的Init报文*/
    ULONG ulBfdSndUp;        /*发送的Up报文*/
    ULONG ulBfdSndAdminDown; /*发送的AdminDown报文*/
    ULONG ulBfdSndErr;       /*接收的错误报文*/    
    ULONG ulBfdSndP;         /*发送的P报文*/
    ULONG ulBfdSndF;         /*发送的F报文*/
} BFD_STATISTIC_S;

/* BFD诊断字类型字段 */
typedef enum tagBFD_DIAG_E
{
    BFD_DIAG_NONE      = 0               ,       /* 无诊断字 */
    BFD_DIAG_DETECT_DOWN                 ,       /* 检测时间DOWN */
    BFD_DIAG_ECHO_DOWN                   ,       /* 回声检测DOWN */
    BFD_DIAG_NEIGHBOR_DOWN               ,       /* 邻居通告DOWN */
    BFD_DIAG_FORWARDING_RESET            ,       /* 转发平面重启 */
    BFD_DIAG_PATH_DOWN                   ,       /* 路径DOWN */
    BFD_DIAG_CONCAT_PATH_DOWN            ,       /* 级联路径DOWN */
    BFD_DIAG_ADMIN_DOWN                  ,       /* 管理DOWN */
    BFD_DIAG_REVERSE_CONCAT_PATH_DOWN    ,       /* 反向级联路径DOWN */
    BFD_DIAG_RECEIVE_ADMIN_DOWN          ,       /* Receive admindown packet ,note : not define in the protocol */
    BFD_DIAG_MAX                                 /* 最大无效值 */
} BFD_DIAG_E ;

/* BFD会话状态 */
/* CAUTION: if modify state define, pls update g_aszSessionState */
typedef enum tagBFD_STATE_E
{
    BFD_STATE_ADMIN_DOWN  = 0            ,      /* 管理DOWN状态 */
    BFD_STATE_DOWN                       ,      /* DOWN状态 */
    BFD_STATE_INIT                       ,      /* INIT状态 */
    BFD_STATE_UP                         ,      /* UP状态 */
    BFD_STATE_MAX                               /* 会话的无效状态 */
} BFD_STATE_E ;

/* 外部通知地址增删事件 供BFD_IpAddrEventNotify和*/
typedef enum tagBFD_EVENT_E
{
    BFD_IPCHANGE_ADD_EVENT  = 0,                /* 增加地址 */
    BFD_IPCHANGE_DEL_EVENT,                     /* 删除地址 */
    BFD_TRUNKPORT_ADD_EVENT,                    /* 接口加入到trunk中 */
    BFD_TRUNKPORT_REMOVE_EVENT,                 /* 接口从trunk中移除 */
    BFD_EVENT_MAX
} BFD_EVENT_E ;

/*Added by w00207740, BFD NSR,上报消息定义, 2013/8/27 */
typedef enum tagBFD_NSR_MSG_E
{
    BFD_NSR_MSG_SESSINFO = 0    ,                 /* 上报BFD4会话信息 */
    BFD_NSR_MSG_RESUME_FINISH   ,                 /* 底层上报会话完成 */
    BFD_NSR_MSG_ALLSESS_DELETE  ,                 /* 通知控制面所有备份信息删除完成 */
    BFD6_NSR_MSG_SESSINFO       ,                 /* 上报BFD6会话信息 */
    BFD_NSR_MSG_MAX             ,      
} BFD_NSR_MSG_E ;

/*Added by w00207740, BFD NSR,全局信息结构体, 2013/8/27 */
typedef struct tagBFD_NSR_GLOBAL_INFO
{
    ULONG ulBfdNsrState;                    /* BFD NSR当前状态 */
    ULONG ulSessNumBeforeNSR;               /* 触发NSR过程前，BFD会话个数*/
    ULONG ulResumeSessNum;                  /* 转发面上报的会话个数*/
    ULONG ulAddSessNum;                     /* NSR过程中配置add的会话数*/
    ULONG ulDelSessNum;                     /* NSR过程中配置delete的会话数*/
    ULONG ulPPICreateSessNum;               /* PPI下发 create 的会话数*/
    ULONG ulPPIDelSessNum;                  /* PPI下发 delete 的会话数*/
    ULONG ulPPIDownSessNum;                 /* PPI下发 down 的会话数*/
    ULONG ulPPIUpSessNum;                   /* PPI下发 up 的会话数*/
    ULONG ulRcvAdmindownNum;                /* NSR过程中收到admindown报文的会话数*/
    ULONG ulAdmindownNum;                   /* NSR过程中配置admindown的会话数*/
    ULONG ulTimeOut;                        /* NSR过程是否超时*/
}BFD_NSR_GLOBAL_INFO_S;

/* Modified by w00207740, DTS2014021806601,usBfdNsrSessStateFlag字段废弃, 2014/2/19 */
typedef struct tagBFD_NSR_SESS_INFO
{
    ULONG   ulSessId;                                   /* 会话ID */
    ULONG   ulVrfIndex;                                 /* VRF索引 */
    ULONG   ulBfdNsrNpDiag;                             /* NP上报诊断字 */
    USHORT  usBfdNsrNpSessState;                        /* NP上报会话状态 */
    USHORT  usStateResultInSmooth;                      /*平滑后会话状态*/
    UCHAR   ucRcvAdmindown;                             /* nsr过程中收到admin down报文*/
    UCHAR   ucCfgAdmindown;                             /* nsr过程中配置admin down*/
    UCHAR   ucBfdNsrPPIFlag;                            /* nsr过程中PPI下发*/
    UCHAR   ucPad[1];
}BFD_NSR_SESS_INFO_S;

typedef struct tagBFD6_NSR_SESS_INFO
{
    ULONG   ulSessId;                                   /* 会话ID */
    ULONG   ulVrfIndex;                                 /* VRF索引 */
    ULONG   ulBfdNsrNpDiag;                             /* NP上报诊断字 */
    USHORT  usBfdNsrNpSessState;                        /* NP上报会话状态 */
    USHORT  usStateResultInSmooth;                      /*平滑后会话状态*/
    UCHAR   ucRcvAdmindown;                             /* nsr过程中收到admin down报文*/
    UCHAR   ucCfgAdmindown;                             /* nsr过程中配置admin down*/
    UCHAR   ucBfdNsrPPIFlag;                            /* nsr过程中PPI下发*/
    UCHAR   ucPad[1];
}BFD6_NSR_SESS_INFO_S;

/* 系统是否支持NP */
#define BFD_NP_NOT_SUPPORT             0            /* 不支持NP */
#define BFD_NP_HALF_SUPPORT            1            /* 支持弱NP,软件接收,NP发送 */
#define BFD_NP_SUPPROT                 2            /* 支持全NP,NP发送接收 */

/* 调试开关类型 */
#define BFD_DEBUG_STATE                0x1          /* BFD状态变迁调试 */
#define BFD_DEBUG_INPUT                0x2          /* 接收的BFD报文调试 */
#define BFD_DEBUG_OUTPUT               0x4          /* 发送的BFD报文调试 */
#define BFD_DEBUG_GR                   0x8          /* GR调试 */
#define BFD_DEBUG_NSR                  0x10         /* NSR调试*/

#define BFD_DEBUG_BITSWITCH            5            /* BFD调试开关只用低位 */

/* 打开所有调试 */
#define BFD_DEBUG_ALLTYPE              (BFD_DEBUG_STATE|BFD_DEBUG_INPUT|BFD_DEBUG_OUTPUT)

#define BFD_LEN_AUTH_NONE              24           /* 不带任何认证的BFD控制报文长度 */

/* Modified by z36377 for A82D12722:增加出接口信息字段 */
/* Modified by w61195 for A82D21612, 2007-12-4, 修改NP下发参数，将探测总时间拆分为检测间隔和检测倍数 */
/* 对NP下发参数数据结构 */
typedef struct tagBFD_PPI_S
{
    CHAR szCtlPkt[BFD_LEN_AUTH_NONE]; /* 会话的BFD控制报文,网络序,值为用户配置值 */

    ULONG ulDetectMode;             /* 本端实际的检测模式 */
    ULONG ulTxInterval;             /* 本端实际的发送时间间隔,ms */
    ULONG ulDetectInterval;         /* 本端实际的检测间隔,ms */
    ULONG ulDetectMult;             /* 本端实际的检测倍数 */
    ULONG ulMyDiscriminator;        /* 本端标识符 */
    ULONG ulYourDiscriminator;      /* 对端标识符 */

    ULONG ulDstIPAddress;           /* 对端地址,Big Endian */
    ULONG ulSrcIPAddress;           /* 本端地址,Big Endian */
    ULONG ulTTL;                    /* TTL */
    ULONG ulDstUdpPort;             /* UDP目的端口号,单跳为3784,多跳为4784 */
    ULONG ulSrcUdpPort;             /* UDP源端口号,值为49151+X(X>0) */
    ULONG ulTos;                    /* TOS值 */
    ULONG ulIfIndex;                /* 会话的出接口索引(多跳时为0) */
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-01 */
    ULONG ulVrfIndex;               /* 会话所在的VRF */
    /* ENd:VISP1.7C03 VRF wangchengyang,2009-02-01 */
    ULONG ulIfType;                 /* 出接口类型, 取值见enumIFTYPE */
    ULONG ulIfNum;                  /* 出接口的通道号 */
    USHORT usReserved;              /* 保留不用 */
    USHORT usCksum;                 /* 整个PPI结构体的校验和 */
    ULONG ulDiagnostic;             /* 下发当前会话诊断字 */
}BFD_PPI_S;

typedef struct tagBFD6_PPI_S
{
    CHAR szCtlPkt[BFD_LEN_AUTH_NONE]; /* 会话的BFD控制报文,网络序,值为用户配置值 */

    ULONG ulDetectMode;             /* 实际的检测模式 */
    ULONG ulTxInterval;             /* 本端实际的发送时间间隔,ms */
    ULONG ulDetectInterval;         /* 本端实际的检测间隔,ms */
    ULONG ulDetectMult;             /* 本端实际的检测倍数 */
    ULONG ulMyDiscriminator;        /* 本端标识符 */
    ULONG ulYourDiscriminator;      /* 对端标识符 */

    ULONG ulDstIPAddress[4];        /* 对端地址,网络序 */
    ULONG ulSrcIPAddress[4];        /* 本端地址,网络序 */
    ULONG ulHopLimit;               /* Hop Limit */
    ULONG ulDstUdpPort;             /* UDP目的端口号,单跳为3784,多跳为4784 */
    ULONG ulSrcUdpPort;             /* UDP源端口号,值为49151+X(X>0) */
    ULONG ulTclass;                 /* Traffic class值 */
    ULONG ulIfIndex;                /* 会话的出接口索引(多跳时为0) */
    ULONG ulVrfIndex;               /* 会话所在的VRF */
    ULONG ulSessionId;              /* 会话ID */
    ULONG ulDiagnostic;             /* 下发当前会话诊断字 */
}BFD6_PPI_S;

/* PPI Msg Type */
/* 修改该结构时请同步修改bfd_ppi.c中BFD_PPI_OprType_En */
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
    /* Add for V2R3C05, by b0177000/y00176567, at 2011-06-03. 修改原因: V2R3C05 增加停止或重新发送周期性BFD的NP下发类型 */   
    BFD_PPI_SESSION_STOP_SEND_DETECT_PKT           ,         /* 通知不再发送周期性BFD报文 */
    BFD_PPI_SESSION_START_SEND_DETECT_PKT          ,         /* 通知重新发送周期性BFD报文 */

    BFD_PPI_MSG_MAX
}PPI_MSG_TYPE_E;/* 修改该结构时请同步修改bfd_ppi.c中BFD_PPI_OprType_En */

/*Added by w00207740, NSR BFD,新增钩子函数下发命令, 2013/8/29 */
typedef enum tagNSR_PPI_MSG_TYPE_E
{
    BFD_PPI_NSR_READY                              ,         /* 通知转发面控制面就绪 */                            
    BFD_PPI_NSR_FAILED                             ,         /* 通知转发面控制面NSR失败 */
    BFD_PPI_NSR_SESSCREATE                         ,         /* 通知转发面创建会话 */
    BFD_PPI_NSR_SESSUPDATE                         ,         /* 通知转发面更新会话 */
    BFD_PPI_NSR_SESSDOWN                           ,         /* 通知转发面会话状态由UP变为down */
    BFD_PPI_NSR_SESSDELETE                         ,         /* 通知转发面删除会话 */
    BFD_PPI_NSR_FINISH                             ,         /* 通知转发面NSR过程完成 */
    BFD_PPI_NSR_MAX                                ,
}NSR_PPI_MSG_TYPE_E;

/* SGSN新需求: BFD会话删除时只下发BFD_PPI_USER_DELETE,不下发BFD_PPI_SESSION_DELETE zengshaoyang */
typedef enum tagPPI_DEL_BFDSESSION_MODE_E
{
    BFD_PPI_SESSION_DEL_MODE_DEF = 0,      /* 缺省模式,下发BFD_PPI_USER_DELETE和BFD_PPI_SESSION_DELETE*/
    BFD_PPI_SESSION_DEL_MODE_SGSN          /* SGSN模块,只下发BFD_PPI_USER_DELETE */
}PPI_DEL_BFDSESSION_MODE_E;


/* Begin:VISP1.7C03 VRF wangchengyang,2009-02-01 */
/* BFD配置控制块 */
typedef struct tagBFD_CREATEDEL_BYVRF_S
{
    ULONG  ulAction;
    ULONG  ulDstIP;
    ULONG  ulSrcIP;
    ULONG  ulOutIfIndex;
    ULONG  ulVrfIndex;               /* VRF 索引*/
    /* Add for V2R3C05, by b0177000/y00176567, at 2011-06-03. 修改原因: V2R3C05 增加创建会话的协议类型字段 */   
    ULONG  ulBfdProtocol;            /* 会话协议类型*/
}BFD_CREATEDEL_BYVRF_S;

typedef struct tagBFD_NOTIFY_BYVRF_S
{
    ULONG ulVrfInex;
    ULONG ulSessionID;
    ULONG ulState;
    ULONG ulDstIP;
    ULONG ulSrcIP;
    ULONG ulInIfIndex;
    ULONG ulAppGroup;
}BFD_NOTIFY_BYVRF_S;
/* End:VISP1.7C03 VRF wangchengyang,2009-02-01 */

typedef ULONG(*BFD_PPI_HOOK_FUNC)(ULONG ulBfdPpiMsgType, ULONG ulSessionID, BFD_PPI_S* pBfdPpiInfo);

typedef ULONG(*BFD_NOTIFY_HOOK_FUNC)(ULONG ulSessionID, ULONG ulState,ULONG ulDstIP, ULONG ulSrcIP,
                                     ULONG ulInIfIndex, ULONG ulAppGroup);

/* RPU新需求: BFD状态变迁时对外通告 */
typedef ULONG(*BFD_STATECHG_NOTIFY_HOOK_FUNC)(
            ULONG ulSessionID,   /* Session ID */
            ULONG ulOldState,    /* BFD会话老的状态 */
            ULONG ulNewState,    /* BFD会话新的状态 */
            ULONG ulDstIP,       /* 目的IP 网络序*/
            ULONG ulSrcIP,       /* 源IP 网络序*/
            ULONG ulInIfIndex,   /* 出接口 */
            ULONG ulAppGroup,    /* 会话应用组 */
            ULONG ulVrfIndex);  /* VRF索引 */

/* Begin:VISP1.7C03 VRF wangchengyang,2009-02-01 */
typedef ULONG(*BFD_NOTIFY_BYVRF_HOOK_FUNC)(BFD_NOTIFY_BYVRF_S *pstBfdNotify);

typedef struct tagBfdNotifyByVrf {
    BFD_NOTIFY_BYVRF_HOOK_FUNC pfBfdNotifyByVrfHookFunc;  /* The Registered Function Pointer */
    struct tagBfdNotifyByVrf *pstNext;
} BFD_NOTIFY_BYVRF_HOOK_S;

/* End:VISP1.7C03 VRF wangchengyang,2009-02-01 */

typedef struct tagBfdNotify {
    BFD_NOTIFY_HOOK_FUNC pfBfdNotifyHookFunc;  /* The Registered Function Pointer */
    struct tagBfdNotify *pstNext;
} BFD_NOTIFY_HOOK_S;


typedef ULONG(*BFD6_PPI_HOOK_FUNC)(ULONG ulBfdPpiMsgType, BFD6_PPI_S* pBfdPpiInfo);

/* 获取BFD License功能开关是否打开
#define BFD_LICENSE_ON   0x01 :BFD License功能打开
#define BFD_LICENSE_OFF  0x00 :BFD License功能关闭*/
typedef ULONG(*BFD_GET_LICENSE_STATE_FUNC)(ULONG *pulState);


typedef struct tagBFD6_NOTIFY_S
{
    ULONG ulVrfInex;
    ULONG ulSessionID;
    ULONG ulState;
    ULONG ulDstIP[4];
    ULONG ulSrcIP[4];
    ULONG ulInIfIndex;
    ULONG ulAppGroup;
}BFD6_NOTIFY_S;

typedef ULONG(*BFD6_NOTIFY_HOOK_FUNC)(BFD6_NOTIFY_S *pstBfd6Notify);

typedef struct tagBfd6Notify {
    BFD6_NOTIFY_HOOK_FUNC pfBfd6NotifyHookFunc;  /* The Registered Function Pointer */
    struct tagBfd6Notify *pstNext;
} BFD6_NOTIFY_HOOK_S;

/* Modified by likaikun213099, 原始宏定义与产品定义冲突了, 2014/11/15   问题单号:DTS2014111500081  */
#define VISP_BFD_FOR_IPV4      0
#define VISP_BFD_FOR_IPV6      1
#define VISP_BFD_FOR_ALL       2
/*End of Modified by likaikun213099, 2014/11/15   问题单号:DTS2014111500081  */
typedef struct tagBFD_SESSION_FILTER_EX_S {
    UCHAR szCfgName[BFD_MAX_SESS_NAME_LEN + 1];
    ULONG ulPeerAddr4;   /* IPv4地址  主机顺序 */                                                               
    UCHAR ucPeerAddr6[16]; 
    ULONG ulLocalDiscr;  /* 指定本端描述符 */
    CHAR  szVrfName[BFD_MAX_VRF_NAME_LEN + 1];
    USHORT usIsAllVRF;   /* 为1表示在所有的VRF中进行查找,为0表示在指定的VRF中进行查找 */
    UCHAR  ucIpVer;      /*为2则不区分IPv4和IPv6*/
    UCHAR  ucPad;
}BFD_SESSION_FILTER_EX_S;

typedef struct tagBFD_SESSION_CONFIG_INFO_EX_S {
    UCHAR szCfgName[BFD_MAX_SESS_NAME_LEN + 1];
    UCHAR szSessionDes[BFD_MAX_DESC_NAME_LEN + 1];
    ULONG ulLocalDiscr;
    ULONG ulSrcAddr4;       /* IPv4 源地址，主机顺序 */
    UCHAR ucSrcAddr6[16];   /* IPv6地址              */

    ULONG ulPeerAddr4;      /* IPv4 对端地址，主机顺序 */
    UCHAR ucPeerAddr6[16];   /* IPv6地址                */
    ULONG ulDetectMult;
    ULONG ulMinTxInterval;
    ULONG ulMinRxInterval;
    ULONG ulOutIndex;
    ULONG ulAppId;
    CHAR  szVrfName[BFD_MAX_VRF_NAME_LEN + 1];
    ULONG ulRemoteDiscr;
    UCHAR ucTos;            /* bfd会话tos */
    UCHAR ucIpVer;
    UCHAR Padding[2];
}BFD_SESSION_CONFIG_INFO_EX_S;

typedef struct tagBFD_SESSION_COUNT_EX_S {
    UCHAR szCfgName[BFD_MAX_SESS_NAME_LEN + 1];
    UCHAR szSessionDes[BFD_MAX_DESC_NAME_LEN + 1];
    ULONG ulSessionId;
    ULONG ulLocalDiscr;
    ULONG ulRemoteDiscr;
    USHORT usSessState;
    USHORT usIsMultiHop;
    ULONG ulPktRcv;
    ULONG ulPktSend;
    ULONG ulPktRcvDrop;
    ULONG ulPktSendErr;
    ULONG ulSessionDownNum;
    ULONG ulSessionStateTime;
    ULONG ulLastDownTime;
    ULONG ulVrfIndex;
    ULONG ulPeerAddr4;          /* IPv4地址 */
    UCHAR ucPeerAddr6[16];      /* IPv6地址 */
    UCHAR ucIpVer;
    UCHAR Padding[3];
}BFD_SESSION_COUNT_EX_S;

typedef struct tagBFD_SESSION_ALL_INFO_EX_S {
    BFD_SESSION_CONFIG_INFO_EX_S stConfigInfo;
    ULONG  ulRemoteDiscr;
    ULONG  ulSessionId;
    USHORT usSessState;
    USHORT usIsMultiHop;
    ULONG  ulActTxInterval;
    ULONG  ulActRxInterval;
    ULONG  ulActDetectMult;
    ULONG  ulActDetectTime;
    USHORT usLocalDiag;
    USHORT usDstPort;               /* 会话目的端口号(主机序) */
    ULONG  ulRemoteMinTxInterval;   /* 对端的MTI */
    ULONG  ulRemoteMinRxInterval;   /* 对端的MRI */
    USHORT usRemoteDemandMode;      /* 对端的检测模式 */
    UCHAR  ucRemoteDetectMult;      /* 对端的检测倍数 */
}BFD_SESSION_ALL_INFO_EX_S;

/* api declare */
/*******************************************************************************
*    Func Name: BFD_DemandQueryByApp
*  Description: 触发指定会话的查询序列的发送
*        Input: ULONG  ulSessionID 指定会话的标识ID；
*                                  有效取值范围1-用户配置BFD规格，且必须为已创建会话ID
*       Output: 
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_SESSION_ID
*                              BFD_ERR_SESSION_NOT_UP
*                              BFD_ERR_DETECT_MODE
*                              BFD_ERR_DISABLE
*                              BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_QUE_BUSY
*                              BFD_ERR_WRITEQUE_FAIL
*                              BFD_ERR_HA_IS_SMOOTHING
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-06      Wangchengyang    Create
*******************************************************************************/
extern ULONG BFD_DemandQueryByApp(ULONG ulSessionID);
/*******************************************************************************
*    Func Name: BFD_GetNextSessionID
*  Description: 获取指定会话的下一个会话的标识ID（会话按标识ID升序排列）
*        Input: ULONG  ulSessionID 指定的会话ID
*                      当输入参数为0时，返回当前存在的第一个会话的标识ID值；
*                      当输入参数小于用户配置的BFD规格时，返回该ID之后的第一个会话的标识ID值
*                      当输入参数大于等于用户配置的BFD规格 时直接返回0;
*       Output: 
*       Return: 成功返回       会话标识ID（非0）
*               失败返回       0（当前无会话，或BFD未使能，或者输入ID大于等于 BFD_MAX_SESSION_ID）
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-06      Wangchengyang    Create
*******************************************************************************/
extern ULONG BFD_GetNextSessionID(ULONG ulSessionID);
/*******************************************************************************
*    Func Name: BFD_GetSessionInfo
*  Description: 获取指定会话的当前信息
*        Input: ULONG  ulSessionID 指定会话的标识ID；取值范围为1～用户配置的BFD规格
*
*       Output: BFD_SESSION_INFO_S* pSess 用于存储会话参数的缓冲区地址指针
*                                         具体数据定义见数据描述
*       Return: 成功返回   BFD_OK
*               失败返回   BFD_ERR_SESSION_ID；      会话ID非法
*                          BFD_ERR_SESSION_NOT_EXIST 指定会话不存在
*                          BFD_ERR_NULL_POINTER
*                          BFD_ERR_DISABLE
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-06      Wangchengyang    Create
*******************************************************************************/
extern ULONG BFD_GetSessionInfo(ULONG ulSessionID, BFD_SESSION_INFO_S *pSess);
/*******************************************************************************
*    Func Name: BFD_GetVersion
*  Description: 获取BFD CBB的版本号和编译时间
*        Input: CHAR *szVerInfo: BFD CBB的版本信息和编译时间字符串
*                                由用户分配256字节空间。
*       Output:
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_NULL_POINTER
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-4-8    LY(57500)        Create the first version.
*
*******************************************************************************/
extern ULONG BFD_GetVersion(CHAR *szVerInfo);
/*******************************************************************************
*    Func Name: BFD_Init
*  Description: BFD初始化，由于现在基于VISP实现
*               因此放在VISP协议栈启动的SystemEntry中
*        Input: ULONG ulNpMode：
*                     0    不使用NP
*                     1    NP发送，软件探测
*                     2    NP发送、探测
*                     其他 非法
*               ULONG ulBFDTaskPri：BFD主任务的优先级(0～255)
*                                   visp中要求等于SOCKRUN任务的优先级
*               ULONG ulBFDTaskStackSize：BFD主任务栈大小
*                                   visp中要求等于SOCKRUN任务的栈大小，默认是16K*
*       Output: 
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR
*                              BFD_ERR_CREATE_TASK；
*                              BFD_ERR_CREATE_QUEUE；
*                              BFD_ERR_NP_MODE
*                              BFD_ERR_TASK_PRI
*                              BFD_ERR_CREATE_OTHERQUEUE
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-08      Wangchengyang    Create
*  2007-03-22      lijing 52889     modify for Defect A82D13061
*  2007-12-7       zhangchunyu      modify for Defect A82D21512
*******************************************************************************/
extern ULONG BFD_Init(ULONG ulNpMode,ULONG ulBFDTaskPri, ULONG ulBFDTaskStackSize);
/*******************************************************************************
*    Func Name: BFD_IpAddrEventNotify
*  Description: 当外部添加、删除了一个地址时，通知BFD模块进行相应处理，比如：
*               一个会话的源地址被删除了，则该会话被停止；
*               若一个会话的目的地址被设置为了本地地址，则该会话被停止。
*               直接写消息和事件通知BFD任务处理;
*
*        Input: ulIpEvent  地址事件：添加、删除;0 表示增加1 表示删除
*               ulIpAddr   添加或删除的地址值；主机序；
*               ulIfIndex  地址变化发生接口的索引值；
*
*       Output: 
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_DISABLE;
*                              BFD_ERR_EVENT
*
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-07     Wangchengyang    Create
*  2007-5-17  wujie(61195)         Modified for A82D15480，入参地址变为主机序
*******************************************************************************/
extern ULONG BFD_IpAddrEventNotify(ULONG ulIpEvent, ULONG ulIpAddr, ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: BFD6_IpAddrEventNotify
* Date Created: 2013-12-12
*       Author: Wangchengyang
*  Description: 当外部添加、删除了一个地址时，通知BFD模块进行相应处理，比如：
*               一个会话的源地址被删除了，则该会话被停止；
*               若一个会话的目的地址被设置为了本地地址，则该会话被停止。
*               直接写消息和事件通知BFD任务处理;
*
*        Input: ulIpEvent  IPv6地址事件：添加、删除;0 表示增加1 表示删除
*               pulIpAddr   添加或删除的地址值；主机序；
*               ulIfIndex  地址变化发生接口的索引值；
*
*       Output: 
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_DISABLE;
*                              BFD_ERR_EVENT
*
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-12-12     wangjiaqi         Create
*******************************************************************************/
ULONG BFD6_IpAddrEventNotify(ULONG ulIpEvent, ULONG *pulIpAddr, ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: BFD_TrunkPortEventNotify
* Date Created: 2007-8-29
*       Author: LY(57500)
*  Description: 如果eth接口加入到trunk或从trunk中移除,则需要通知bfd,查找是否有出接口设置为该接口,并输出告警
*        Input: ULONG ulPortEvent: BFD_TRUNKPORT_ADD_EVENT 接口加入到trunk
*                                  BFD_TRUNKPORT_REMOVE_EVENT 接口从trunk中移除
*               ULONG ulPortIfIndex: 接口(trunk成员端口)索引
*       Output: 
*       Return: BFD_OK 通知成功
*               其他   通知失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-8-29    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG BFD_TrunkPortEventNotify(ULONG ulPortEvent, ULONG ulPortIfIndex);
/*******************************************************************************
*    Func Name: BFD_RecvPacket
* Date Created: 2006-12-6
*       Author: wujie(61195)
*  Description: 接收处理一个BFD控制报文
*               当不能在协议栈的UDP输入处理中打钩子时，可以在UDP socket接收处理中使用此接收接口。
*        Input: CHAR *pBFDPacket: 接收的BFD报文
*               ULONG ulPktLenth: BFD报文总长度
*               ULONG ulDstIP: 接收报文的目的地址，网络序
*               ULONG ulSrcIP: 接收报文的源地址，网络序；
*               ULONG InIfIndex: 报文入接口索引
*       Output:
*       Return:
*      Caution: Important points if any
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-6   wujie(61195)         Creat the first version.
*  2009-02-01  wangchengyang        modified for VISP1.7C03 VRF
*******************************************************************************/
extern ULONG BFD_RecvPacket(CHAR *pBFDPacket, ULONG ulPktLenth, ULONG ulDstIP, ULONG ulSrcIP, ULONG InIfIndex);

/*******************************************************************************
*    Func Name: BFD_RecvPacketByVrf
* Date Created: 2009-04-15
*       Author: ZhengSenHuo(104483)
*  Description: 当不能在协议栈的UDP输入处理中打钩子时，可以在UDP socket接收处理中使用此接收接口。
*        Input: CHAR *pBFDPacket: 接收的BFD报文
*               ULONG ulPktLenth: BFD报文总长度
*               ULONG ulDstIP: 接收报文的目的地址，网络序
*               ULONG ulSrcIP: 接收报文的源地址，网络序；
*               ULONG InIfIndex: 报文入接口索引
*               ULONG ulVrfIndex VRF索引
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-15   ZhengSenHuo(104483)     Create
*
*******************************************************************************/
extern ULONG BFD_RecvPacketByVrf(CHAR *pBFDPacket, ULONG ulPktLenth, ULONG ulDstIP, ULONG ulSrcIP, ULONG InIfIndex,ULONG
ulVrfIndex);

/*******************************************************************************
*    Func Name: BFD_RecvPacketWithIP
*  Description: 接收处理一个UDP数据为BFD控制报文的IP报文；
*               当协议栈支持在UDP输入处理中打钩子时（比如在VISP中应用时），使用此接收接口。
*        Input: CHAR* pIpPacket:接收的BFD报文，报文格式为IP报文首部、UDP报文首部、BFD报文
*               ULONG ulInIfIndex:报文入接口索引
*       Output: 
*       Return: 成功或错误码
*      Caution: VISP协议栈在IP报文接收处理的时候，会将IP首部的长度字段转换为主机序，
*               然后减去IP首部的长度，所以这里传入的IP报文首部长度字段直接减去UDP首部长度
*               即得到BFD报文长度
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-5  wujie(61195)         Creat the first version.
*  2007-7-24  wujie(61195)         Modified for A82D18150，和VRP旧版本的BFD多跳对接
*
*******************************************************************************/
extern ULONG BFD_RecvPacketWithIP( CHAR* pIpPacket, ULONG ulInIfIndex);
/*******************************************************************************
*    Func Name: BFD_RecvPacketWithIP
* Date Created: 2006-12-5
*       Author: wujie(61195)
*  Description: 接收处理一个UDP数据为BFD控制报文的IP报文；
*               当协议栈支持在UDP输入处理中打钩子时（比如在VISP中应用时），使用此接收接口。
*        Input: CHAR* pIpPacket:接收的BFD报文，报文格式为IP报文首部、UDP报文首部、BFD报文
*               ULONG ulInIfIndex:报文入接口索引
*               ULONG ulVrfIndex :VRF索引
*       Output: 
*       Return: 成功或错误码
*      Caution: VISP协议栈在IP报文接收处理的时候，会将IP首部的长度字段转换为主机序，
*               然后减去IP首部的长度，所以这里传入的IP报文首部长度字段直接减去UDP首部长度
*               即得到BFD报文长度
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-5   wujie(61195)         Creat the first version.
*  2007-7-24   wujie(61195)         Modified for A82D18150，和VRP旧版本的BFD多跳对接
*  2009-02-01  wangchengyang        modified for VISP1.7C03 VRF
*******************************************************************************/
extern ULONG BFD_RecvPacketWithIPByVrf(CHAR* pIpPacket, ULONG ulInIfIndex,ULONG ulVrfIndex);
/*******************************************************************************
*    Func Name: BFD_SessionAdminister
*  Description: 会话的用户管理，Admindown，undo Admindown
*        Input: ULONG  ulSessionID 指定会话的标识ID；取值范围为1～用户配置的BFD规格
*               BOOL_T bShutdown   TRUE－关闭会话；FALSE－打开会话
*
*       Output: 
*       Return: 成功返回   BFD_OK
*               失败返回   BFD_ERR_SESSION_ID；      会话ID非法
*                          BFD_ERR_SESSION_NOT_EXIST 指定会话不存在
*                          BFD_ERR_INVALID_PARAMETER
*                          BFD_ERR_DISABLE
*                          BFD_ERR_HA_IS_SMOOTHING
*                          BFD_ERR_QUE_BUSY
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-06      Wangchengyang    Create
*******************************************************************************/
extern ULONG BFD_SessionAdminister(ULONG ulSessionID, BOOL_T bShutdown);
/*******************************************************************************
*    Func Name: BFD_SessionCreate
*  Description: 设定一个BFD会话的基本参数，并开始建立会话
*        Input: ULONG ulDstIP      指定会话的目的地址；主机序；
*               ULONG ulSrcIP      指定会话的源地址；主机序；
*               ULONG ulOutIfIndex   单跳会话时为出接口索引，多跳时值为0；
*                                    由调用者保证以上参数的合理性
*               ULONG *pulSessionID  取值范围为[0,512]，如果是0则由VISP自动分配会话ID，
*                                    否则根据指定的ID创建会话
*
*       Output: ULONG *pulSessionID  会话的标识ID
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_EXIST_SESSION
*                              BFD_ERR_SESSION_FULL
*                              BFD_ERR_NULL_POINTER
*                              BFD_ERR_MEM_ALLOC
*                              BFD_ERR_HA_IS_SMOOTHING
*                              BFD_ERR_DISABLE
*                              BFD_ERR_QUE_BUSY
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-05      Wangchengyang    Create
*  2007-5-17       wujie(61195)     Modified for A82D15480，入参地址变为主机序
*******************************************************************************/
extern ULONG BFD_SessionCreate(ULONG ulDstIP, ULONG ulSrcIP, ULONG ulOutIfIndex, ULONG* pulSessionID);
/*******************************************************************************
*    Func Name: BFD_SessionDeleteDontSendDDPkt
*  Description: 删除BFD会话时不发送Admin Down报文
*        Input: ULONG ulSessionID:会话ID
*
*       Output: 
*       Return: 成功返回       VOS_OK
*               失败返回       Error Code
*      Caution: 供CBSC/MBSC产品使用，在删除BFD会话时不发送Admin Down报文
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-10-08      chenlong168670   Create
*
*******************************************************************************/
extern ULONG BFD_SessionDeleteDontSendDDPkt(ULONG ulSessionID);
/*******************************************************************************
*    Func Name: BFD_SessionDelete
*  Description: 删除指定会话
*        Input: ulSessionID 会话标识ID；取值范围为1～用户配置的BFD规格；
*
*       Output: 
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_HA_IS_SMOOTHING
*                              BFD_ERR_SESSION_ID
*                              BFD_ERR_DISABLE
*                              BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_QUE_BUSY
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-06      Wangchengyang    Create
*******************************************************************************/
extern ULONG BFD_SessionDelete(ULONG ulSessionID);
/*******************************************************************************
*    Func Name: BFD_DeleteSingleAppFromSession
*  Description: 删除指定会话的单个应用
*        Input: ulSessionID 会话标识ID；取值范围为1～用户配置的BFD规格
*               ulAppID     应用ID      取值:2的N次幂,一个bit位表示一个应用
*
*       Output: 
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_SESSION_ID
*                              BFD_ERR_DISABLE
*                              BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_APP_ID;
*                              BFD_ERR_HA_IS_SMOOTHING
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-06      Wangchengyang    Create
*******************************************************************************/
extern ULONG BFD_DeleteSingleAppFromSession(ULONG ulSessionID, ULONG ulAppID);
/*******************************************************************************
*    Func Name: BFD_SessionParaUpdate
*  Description: 更新一个会话的参数，包括：MTI、MRI、Detect Mult、Detect Mode，
*               并立即将更新后的参数应用到会话中。
*        Input: ULONG ulSessionID 会话标识ID；取值范围为1～用户配置的BFD规格
*               BFD_SESSION_PARA_S *pSessPara 更新参数结构指针
*
*       Output: 
*       Return: 成功返回    BFD_OK
*               失败返回    BFD_ERR_SESSION_ID；      会话ID非法
*                           BFD_ERR_TX_INTERVAL;      发送时间间隔非法
*                           BFD_ERR_RX_INTERVAL;      接收时间间隔非法
*                           BFD_ERR_DETECT_MULT;      检测倍数非法
*                           BFD_ERR_SESSION_NOT_EXIST 指定会话不存在
*                           BFD_ERR_DETECT_MODE       检测模式非法
*                           BFD_ERR_NULL_POINTER      参数指针为空；
*                           BFD_ERR_DISABLE           BFD未使能
*                           BFD_ERR_HA_IS_SMOOTHING
*                           BFD_ERR_QUE_BUSY
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-06      Wangchengyang    Create
*******************************************************************************/
extern ULONG BFD_SessionParaUpdate( ULONG ulSessionID, BFD_SESSION_PARA_S *pSessPara);
/*******************************************************************************
*    Func Name: BFD_SetAppsToSession
*  Description: 设定某一会话的应用模块(应用组,即设置那些应用关系这个会话的状态变化)
*        Input: ULONG ulSessionID   会话ID 1~用户配置BFD规格
*               ULONG ulAppGroup    会话的应用模块组合，
*                                   每一个Bit标识着该会话的一个应用模块；
*                                   以最后一次设置为准；
*                                   为0表示取消所有模块对该会话的应用；
*                                   最多支持32个外部应用模块。
*       Output: 
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_SESSION_ID;
*                              BFD_ERR_APP_ID;
*                              BFD_ERR_DISABLE
*                              BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_HA_IS_SMOOTHING
*
*      Caution: 参考《会话状态变化时对外部通知处理》接口；
*               非必要接口；若任何会话的状态变化时，
*               产品适配的《会话状态变化时对外部通知处理》接口采用统一处理时
*               （产品的BFD应用模块较少），不必设置此接口；
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-06      Wangchengyang    Create
*******************************************************************************/
extern ULONG BFD_SetAppsToSession(ULONG ulSessionID, ULONG ulAppGroup);
/*******************************************************************************
*    Func Name: BFD_SetBfdCapability
*  Description: 使能或去使能BFD功能
*
*        Input: BOOL_T bBfdCapability TRUE－使能；FALSE－去使能；
*
*       Output: 
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_DISABLE_PROCESSING
*                              BFD_ERR_INVALID_PARAMETER
*
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-07      Wangchengyang    Create
*  2007-03-29      jiangtao(51916)  Modify for A82D13299
*******************************************************************************/
extern ULONG BFD_SetBfdCapability(BOOL_T bBfdCapability);
/*******************************************************************************
*    Func Name: BFD_SetDebugSwitch
*  Description: 打开或关闭BFD调试开关
*        Input: ULONG ulSessionID 指定会话ID合法性为1~用户配置的BFD规格，
*                                 若输入为0则标识打开/关闭所有会话的调试开关
*               ULONG ulDebug  设置调试标记,打开(关闭)则将相应标志置位(清零)
*                              BFD_DEBUG_STATE    0x1  BFD状态变迁调试
*                              BFD_DEBUG_INPUT    0x2  接收的BFD报文调试
*                              BFD_DEBUG_OUTPUT   0x4  发送的BFD报文调试
*                              若需要打开多个标记,则可位与
*       Output: 
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_INVALID_PARAMETER
*                              BFD_ERR_SESSION_ID
*                              BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_DISABLE
*                              BFD_ERR_HA_IS_SMOOTHING
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-06      Wangchengyang    Create
*******************************************************************************/
extern ULONG BFD_SetDebugSwitch(ULONG ulSessionID, ULONG ulDebug);
/*******************************************************************************
*    Func Name: BFD_GetDebugSwitch
*  Description: 获取BFD的调试开关，如果ulSessionID为0，获取全局Debug开关。否则获取
*                                  指定接口调试开关。
*        Input: ULONG ulSessionID: 会话ID(0-用户配置BFD规格)
*               ULONG *pulDebug: 获取开关指针
*       Output: pulDebug
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_NULL_POINTER
*                              BFD_ERR_SESSION_ID
*                              BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_DISABLE
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-7-31    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG BFD_GetDebugSwitch(ULONG ulSessionID, ULONG *pulDebug);
/*******************************************************************************
*    Func Name: BFD_SetSingleAppToSession
*  Description: 设定某一个会话的具体应用
*        Input: ULONG ulSessionID   会话ID 1~用户配置BFD规格
*               ULONG ulAppID       应用ID 2的N次幂,一个bit位表示一个应用
*       Output: 
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_SESSION_ID;
*                              BFD_ERR_APP_ID;
*                              BFD_ERR_DISABLE
*                              BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_HA_IS_SMOOTHING
*
*      Caution: 参考《会话状态变化时对外部通知处理》接口；
*               非必要接口；若任何会话的状态变化时，
*               产品适配的《会话状态变化时对外部通知处理》接口采用统一处理时
*               （产品的BFD应用模块较少），不必设置此接口；
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-06      Wangchengyang    Create
*******************************************************************************/
extern ULONG BFD_SetSingleAppToSession(ULONG ulSessionID, ULONG ulAppID);
/*******************************************************************************
*    Func Name: BFD_SetWtrTime
*  Description: 设定会话Down之后到重新建立的等待时间。WTR -- Waiting To Restart
*        Input: ULONG ulSeconds 等待时间（s），范围为0－0xFFFFFFFF；
*       Output: 
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_DISABLE;
*                              BFD_ERR_WTR
*                              BFD_ERR_HA_IS_SMOOTHING
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-06      Wangchengyang    Create
*******************************************************************************/
extern ULONG BFD_SetWtrTime(ULONG ulSeconds);
/*******************************************************************************
*    Func Name: BFD_GetGlobalInfo
*  Description: 获取BFD全局信息
*        Input: BFD_GLOBAL_INFO_S *pstBfdGlobalInfo: BFD全局信息结构体指针
*       Output: BFD全局信息
*       Return: BFD_OK
*               BFD_ERR_NULL_POINTER
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-5-16  wujie(61195)         Creat the first version.
*
*******************************************************************************/
extern ULONG BFD_GetGlobalInfo(BFD_GLOBAL_INFO_S *pstBfdGlobalInfo);
/*******************************************************************************
*    Func Name: BFD_SetAdaptMultiHopPort
*  Description: 设置是否自动调整多跳会话的UDP目的端口号。VRP旧版BFD的多跳端口号
*               与单跳端口号一样都是3784，VISP为了与其多跳会话对接作了一些修改。详见A82D18150。
*        Input: ULONG ulSwitch: BFD_ON/打开 BFD_OFF/关闭
*       Output: 
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_HA_IS_SMOOTHING;
*                              BFD_ERR_INVALID_PARAMETER;
*
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-7-24  wujie(61195)         Creat the first version.
*
*******************************************************************************/
extern ULONG BFD_SetAdaptMultiHopPort(ULONG ulSwitch);
/*******************************************************************************
*    Func Name:   BFD_PPI_HookRegister
*    Description: 若产品应用NP，则须向BFD CBB注册PPI通知函数。注册之后，BFD CBB
*                 调用注册的函数向NP通知会话信息。
*    Input:       BFD_PPI_HOOK_FUNC* pfBfdPpiHook: NP  钩子函数
*    Output:      无
*    Return:      成功返回       BFD_OK
*                 失败返回       BFD_ERR_NULL_POINTER
*                                BFD_ERR_DISABLE
*    Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-6    qinyun(62011)     Creat the first version.
*
*******************************************************************************/
extern ULONG BFD_PPI_HookRegister(BFD_PPI_HOOK_FUNC pfBfdPpiHook);
extern ULONG BFD_DetectDownWithDiagByPrdt(ULONG ulSessionID,ULONG ulDiag);
/*******************************************************************************
*    Func Name:   BFD_DetectDownByPrdt
*    Description: 产品的NP探测到会话Down时向控制层面的通知接口
*    Input:       ULONG ulSessionID: 会话ID
*    Output:      无
*    Return:      成功返回       BFD_OK
*                 失败返回       BFD_ERR_SESSION_ID
*                                BFD_ERR_SESSION_NOT_EXIST
*    Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-6    qinyun(62011)     Creat the first version.
*
*******************************************************************************/
extern ULONG BFD_DetectDownByPrdt(ULONG ulSessionID);
/*******************************************************************************
*    Func Name: BFD_GetSessionId
*  Description: 通过源目的IP和出接口索引，查询BFD 会话id
*        Input: ulDstIP   目的IP，主机序
*               ulSrcIP   源IP，主机序
*               ulIfIndex 出接口索引
*
*       Output: 
*       Return: 会话id,如果不存在指定的会话则返回0xFFFFFFFF
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-03-26      Wangchengyang    Create
*******************************************************************************/
extern ULONG BFD_GetSessionId(ULONG ulDstIP, ULONG ulSrcIP, ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: BFD_GetBfdTotalNumber
*  Description: 获取总的BFD会话个数
*        Input: ULONG *pulBfdSessionCnt:  会话个数
*       Output:
*       Return: BFD_OK:成功;
*               BFD_ERR:指针参数空
*               BFD_ERR_DISABLE:bfd未使能
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG BFD_GetBfdTotalNumber(ULONG *pulBfdSessionCnt);
/*******************************************************************************
*    Func Name: TCPIP_BfdNotifyRegister
*  Description: BFD通知注册函数
*        Input: BFD_NOTIFY_HOOK_FUNC pBfdNotifyHookFunc: 钩子函数指针
*       Output:
*       Return: 成功BFD_OK，失败BFD_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_BfdNotifyRegister(BFD_NOTIFY_HOOK_FUNC pBfdNotifyHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_Bfd_StateChg_Notify_Hook_Register
* Date Created: 2010-06-08
*       Author: zengshaoyang62531
*  Description: BFD会话在状态变迁时,对外通告
*        Input: BFD_STATECHG_NOTIFY_HOOK_FUNC pfFunc:注册钩子
*       Output: 
*       Return: VOS_OK;
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-08   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_Bfd_StateChg_Notify_Hook_Register(
                        BFD_STATECHG_NOTIFY_HOOK_FUNC pfFunc);

/*******************************************************************************
*    Func Name: TCPIP_BfdNotifyUnRegister
* Date Created: 2008-8-4
*       Author: qinyun(62011)
*  Description: BFD通知去注册函数
*        Input: BFD_NOTIFY_HOOK_FUNC pBfdNotifyHookFunc: 钩子函数指针
*       Output:
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_MEM_ALLOC
*                              BFD_ERR_NOTIFIER
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-4    qinyun(62011)     Creat the first version.
*******************************************************************************/
extern ULONG TCPIP_BfdNotifyUnRegister(BFD_NOTIFY_HOOK_FUNC pBfdNotifyHookFunc);

/*******************************************************************************
*    Func Name: BFD_ShowGlobalInfo
*  Description: 显示BFD公共信息
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern VOID  BFD_ShowGlobalInfo(VOID);
/*******************************************************************************
*    Func Name: BFD_ShowVersion
*  Description: 显示BFD版本号和编译时间
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern VOID  BFD_ShowVersion(VOID);
/*******************************************************************************
*    Func Name: BFD_ShowSessionInfo
*  Description: 显示BFD所有会话信息
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern VOID  BFD_ShowSessionInfo(VOID);

/*******************************************************************************
*    Func Name: BFD_GetSessionState
* Date Created: 2009-02-05
*       Author: wuhailan/gexianjun
*  Description: 获取BFD会话状态,用来提供给VRRP模块的监听功能使用
*        Input: ULONG ulSessionID:会话ID
*               ULONG ulVrfIndex: vrf索引
*       Output: ULONG *pstState:返回的会话状态
*       Return: 成功BFD_OK,其他返回错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-05   wuhailan/gexianjun      Create
*
*******************************************************************************/
extern ULONG BFD_GetSessionState(ULONG ulSessionID, ULONG ulVrfIndex, ULONG *pstState);

/*******************************************************************************
*    Func Name: BFD_ShowSessionInfoByVrf
* Date Created: 2009-02-01
*       Author: wangchengyang
*  Description: 显示指定VRF的BFD所有会话信息
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-01   wangchengyang    Create for VISP1.7C03 VRF
*******************************************************************************/
extern VOID BFD_ShowSessionInfoByVrf(CHAR *pszVrfName);

/*******************************************************************************
*    Func Name: BFD_ShowSessionCountByVrf
* Date Created: 2009-02-01
*       Author: wangchengyang
*  Description: 显示指定VRF下所有BFD所有会话统计信息
*        Input: pszVrfName VRF 名
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-01   wangchengyang    Create for VISP1.7C03 VRF
*******************************************************************************/
extern VOID BFD_ShowSessionCountByVrf(CHAR *pszVrfName);

/*******************************************************************************
*    Func Name: BFD_ShowSessionInfo
* Date Created: 2008-8-4
*       Author: qinyun
*  Description: 显示BFD所有会话统计信息
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-4  qinyun(62011)     Creat the first version.
*  2009-02-01  wangchengyang modified for VISP1.7C03 VRF
*******************************************************************************/
extern VOID BFD_ShowSessionCount(VOID);

/*******************************************************************************
*    Func Name: BFD_SetFirstNegoTimes
* Date Created: 2009-4-8
*       Author: wangchengyang-xujun62830-57575
*  Description: BFD首次通知down协商失败次数
*        Input: ulFirsNegoTimes    具体次数
*       Output:
*       Return: 成功返回       BFD_OK
*               失败返回       错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-4-8  wangchengyang-xujun62830-57575     Creat the first version.
*******************************************************************************/
extern ULONG BFD_SetFirstNegoTimes(ULONG ulFirsNegoTimes);

/*******************************************************************************
*    Func Name:   BFD6_PPI_HookRegister
* Date Created: 2009-4-8
*       Author: wangchengyang-xujun62830-57575
*  Description: 若产品应用BFD6 NP，则须向BFD CBB注册PPI通知函数。注册之后，BFD CBB
*                 调用注册的函数向NP通知会话信息。
*        Input:       BFD6_PPI_HOOK_FUNC* pfBfdPpiHook: NP  钩子函数
*       Output:      无
*       Return:      成功返回       BFD_OK
*                    失败返回       错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-4-8  wangchengyang-xujun62830-57575     Creat the first version.
*
*******************************************************************************/
extern ULONG BFD6_PPI_HookRegister(BFD6_PPI_HOOK_FUNC pfBfdPpiHook);


/*******************************************************************************
*    Func Name: BFD_SetSessionTos
* Date Created: 2009-8-12
*       Author: LY(57500)
*  Description: 设置bfd会话的tos值
*        Input: ULONG ulSessionID:会话id
*               UCHAR ucTos: tos值，值域有效。设置的值被直接设置到bfd报文ip头里的tos字段里。
*       Output:
*       Return: BFD_OK: 成功
*               其他:   失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-8-12    LY(57500)     Create the first version.
*
*******************************************************************************/
ULONG BFD_SetSessionTos(ULONG ulSessionID, UCHAR ucTos);

/*******************************************************************************
*    Func Name: BFD_SetSessionTosByVrf
* Date Created: 2009-8-12
*       Author: LY(57500)
*  Description: 设置bfd会话的tos值
*        Input: ULONG ulSessionID:会话id
*               ULONG ulVrfIndex: vrf索引
*               UCHAR ucTos: tos值，值域有效。设置的值被直接设置到bfd报文ip头里的tos字段里。
*       Output:
*       Return: BFD_OK: 成功
*               其他:   失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-8-12    LY(57500)     Create the first version.
*
*******************************************************************************/
ULONG BFD_SetSessionTosByVrf(ULONG ulSessionID, ULONG ulVrfIndex, UCHAR ucTos);

/****************************************************************************
*    Func Name: BFD_DelSessionByVrf
* Date Created: 2008-08-26
*       Author: wuhailan
*  Description: 根据VRF索引删除所有BFD会话信息
*        Input: ULONG ulVrfIndex:VRF索引
*       Output: 
*       Return: VOS_OK:成功 其他返回失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-08-26   wuhailan         Create
*
*******************************************************************************/
extern ULONG BFD_DelSessionByVrf(ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: BFD_SetPollRetranSwitch
* Date Created: 2013-01-17
*       Author: luogaowei
*  Description: BFD P/F 重传参数配置
*        Input: ULONG usSwitch: 配置开关，默认关闭(VRP_YES: 1为打开, VRP_NO: 0为关闭)
*               ULONG ulPeriod: 配置的定时器周期(实际会进行-2 和2之间偏移,默认10秒，范围3-20)
*               ULONG ulMaxNum: 配置的重传次数(默认5次，范围1-10)
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-01-17   luogaowei              Create for MBSC   
*
*******************************************************************************/
ULONG BFD_SetPollRetranSwitch(ULONG usSwitch, ULONG ulPeriod, ULONG ulMaxNum);


/*******************************************************************************
*    Func Name: BFD_GetPollRetranSwitch
* Date Created: 2013-01-17
*       Author: luogaowei
*  Description: BFD P/F 重传参数配置
*        Input: 
*       Output: ULONG *pusPFMode: 配置模式，默认关闭(0:下发P标记给NP重传  1:不重传， 2:控制面启动重传机制)
*               ULONG *pulPeriod: 配置的定时器周期(实际会进行-2 和2之间偏移,默认10秒，范围3-20)
*               ULONG *pulMaxNum: 配置的重传次数(默认5次，范围1-10)
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-01-17   luogaowei              Create for MBSC   
*
*******************************************************************************/
ULONG BFD_GetPollRetranSwitch(ULONG *pusReTranMode, ULONG *pulPeriod, ULONG *pulMaxNum);

/*******************************************************************************
*    Func Name: BFD_SetBfdPollClearSwitch
* Date Created: 2014-05-15
*       Author: wangbin
*  Description: 设置BFD P标记清除控制开关
*        Input: ulPollClearSwitch .0-  关闭, 1-打开
*       Output:  
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-05-15   wangbin               
*
*******************************************************************************/
ULONG BFD_SetBfdPollClearSwitch(ULONG ulPollClearSwitch);

/*******************************************************************************
*    Func Name: BFD_GetBfdPollClearSwitch
* Date Created: 2014-05-15
*       Author: wangbin
*  Description: 获取BFD P标记清除控制开关值
*        Input:    
*       Output:  pulPollClearSwitch 0-  关闭, 1-打开
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-05-15   wangbin               
*
*******************************************************************************/
ULONG BFD_GetBfdPollClearSwitch(ULONG *pulPollClearSwitch);

/*******************************************************************************
*    Func Name: BFD_SetBfdProtocolCompliance
* Date Created: 2014-09-01
*       Author: likaikun213099
*  Description: 设置BFD协议顺从性开关，每一bit控制一种协议一致性问题
*        Input: ULONG ulBfdComplianceBit:
*               ULONG ulSwitch:
*       Output: 
*       Return: 
*      Caution: ulSwitch为BFD_ON 时，开启ulBfdComplianceBit位为1的协议一致性问题.
*               ulSwitch为BFD_OFF时，关闭ulBfdComplianceBit位为1的协议一致性问题.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-09-01   likaikun213099          Create
*
*******************************************************************************/
ULONG BFD_SetBfdProtocolCompliance(ULONG ulBfdComplianceBit, ULONG ulSwitch);

/*******************************************************************************
*    Func Name: BFD_GetBfdProtocolCompliance
* Date Created: 2014-09-28
*       Author: likaikun213099
*  Description: 
*        Input: ULONG *pulSwitch:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-09-28   likaikun213099          Create
*
*******************************************************************************/
ULONG BFD_GetBfdProtocolCompliance(ULONG *pulSwitch);

#ifdef __cplusplus
}
#endif   /* end of __cplusplus */

#endif   /* end of _BFD_CBB_API_H_ */


