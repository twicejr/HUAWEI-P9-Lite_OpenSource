/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              3ah_api.h
*
*  Project Code: VISPV100R007
*   Module Name: ETH OAM 3AH  
*  Date Created: 2008-2-28
*        Author: LY(57500)
*   Description: 3AH模块用户api头文件，定义用户需要使用的数据结构、宏和api原型
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2008-2-28  LY(57500)     Create the first version.
*
*******************************************************************************/
#ifndef _3AH_API_H_
#define _3AH_API_H_

#ifdef __cplusplus
extern "C"{
#endif

/* 3AH错误码类型,如果有新增类型,请从后面依次添加 */
typedef enum enumOam3ahErrCode
{
    OAM3AH_OK = VOS_OK,                 /* 0  OK                                */
    OAM3AH_ERR,                         /* 1  ERROR                             */
    OAM3AH_ERR_HA_IS_SMOOTHING,         /* 2  3AH正平滑处理或手动倒换处理       */
    OAM3AH_ERR_PARA,                    /* 3  参数有效性错误                    */
    OAM3AH_ERR_NULL_POINTER,            /* 4  指针参数错误                      */ 
    OAM3AH_ERR_IF_NULL,                 /* 5  接口不存在                        */
    OAM3AH_ERR_IF_INVALID,              /* 6  接口类型错误                      */
    OAM3AH_ERR_MEMORY,                  /* 7  内存空间不足                      */
    OAM3AH_ERR_ENABLED,                 /* 8  3AH已使能                         */
    OAM3AH_ERR_DISABLED,                /* 9  3AH未使能                         */
    OAM3AH_ERR_NOTINACTIVE,             /* 10 非3AH主动端                       */
    OAM3AH_ERR_NOTINLBREMOTE,           /* 11 3AH未处于环回发起稳态             */
    OAM3AH_ERR_CB_NOTEXIST,             /* 12 3AH配置控制块不存在               */
    OAM3AH_ERR_EVENT_WIN,               /* 13 链路事件窗口非法(包括步长错误)    */
    OAM3AH_ERR_EVENT_THRESH,            /* 14 链路事件门限值非法                */
    OAM3AH_ERR_WIN_THRESH_CONFLICT,     /* 15 3AH窗口值和门限值冲突             */
    OAM3AH_ERR_NP_NOT_SUPPORT,          /* 16 NP模式不支持                      */
    OAM3AH_ERR_WRONG_STATE,             /* 17 3AH处于错误的状态下               */
    OAM3AH_ERR_WRONG_MODE,              /* 18 3AH使能去使能环回模式错误         */ 
    OAM3AH_ERR_LINKEV_DISABLE,          /* 19 事件通知去使能                    */
    OAM3AH_ERR_EVENT_NOT_SATISFY,       /* 20 事件发生条件不满足                */
    OAM3AH_ERR_INLB,                    /* 21 3AH处于环回模式                   */
    OAM3AH_ERR_LB_TEST_NP,              /* 22 NP实现环回模式                    */
    OAM3AH_ERR_NO_REGISTER,             /* 23 3AH模块未注册                     */
    OAM3AH_ERR_PORT_IS_VIRTUAL,         /* 24 接口非本板接口                    */
    OAM3AH_ERR_MBUF_PREPEND,            /* 25 MBUF指针前移错误                  */
    OAM3AH_ERR_FRAME_ACT,               /* 26 错帧/错帧秒实现方式配置不支持     */
    OAM3AH_ERR_WIN_THRESH_CONFLICT_NUMMODE,     /* 27 3AH错帧周期事件配置模式为帧数目模式时窗口值和门限值冲突 */
    OAM3AH_ERR_HA_IS_SMB,               /* 28 3AH备板不允许发送数据             */
    OAM3AH_ERR_WIN_THRESH_CONFLICT_SYMMODE,     /* 29 3AH错误符号周期事件配置模式为符号数模式时窗口值和门限值冲突 */
    OAM3AH_ERR_VIRTUA_ENABLED,          /* 30 3ah已经虚使能了                   */
    OAM3AH_ERR_NOT_SUPPORT_IF,          /* 31 3ah虚使能只支持二层Eth口和二层TrunkPort口 */
    OAM3AH_ERR_NEG_TIME_REACHMAX,       /* 32 3AH首次协商不通过告警时间超过最大值 */
    OAM3AH_ERR_CREATE_TIMER_FAIL,       /* 33 3AH首次协商不通过设置时内部创建定时器失败 */
    OAM3AH_ERR_DELETE_TIMER_FAIL,       /* 34 3AH首次协商不通过定时器删除失败 */
    OAM3AH_ERR_RMT_NOTSPPT_LB,          /* 35 对端不支持环回，本端使能环回操作失败，VISPV100R007C01维优项目新增的错误码 */
    OAM3AH_ERR_INVALID_MAIN_FSMSTATE,   /* 36 接口3AH状态机状态非法 */
        
    OAM3AH_ERR_MAXCODE                  /* 3AH错误码最大值,以后添加错误码请按顺序添加到此前 */
}OAM3AH_ERRCODE_E;

/* 8字节数据表示 */
typedef struct tagDULONG_S
{
    ULONG ulDulHi;
    ULONG ulDulLo;
}DULONG_S;

/* 对外输出3AH配置信息结构体 */
typedef struct tag3ahCfgInfo
{
    ULONG  ul3AHEnable;                     /* 是否已使能                       */
    ULONG  ul3AHMode;                       /* 工作模式 0~主动模式，1~被动模式  */
    ULONG  ulDetectInteval;                 /* 探测速率                         */
    ULONG  ulPDUSize;                       /* 最大PDUSize                      */
    ULONG  ulLbTestMode;                    /* 环回测试模式 0~visp软件测试模式，1~NP测试模式    */
    ULONG  ulIsEnableEvent;                 /* 是否使能链路事件，按位输出，从低到高四位分别表示如下事件的使能状态：
                                               错误符号周期事件、 错帧事件、错误帧周期事件、错帧秒事件 */

    ULONG  ulSymbolPeriodWindow;            /* 错误符号周期事件窗口     */
    ULONG  ulSymbolPeriodThreshold;         /* 错误符号周期事件门限     */
    ULONG  ulFrameWindow;                   /* 错误帧事件窗口           */
    ULONG  ulFrameThreshold;                /* 错误帧事件门限           */
    ULONG  ulFramePeriodWindow;             /* 错误帧周期事件窗口       */
    ULONG  ulFramelPeriodThreshold;         /* 错误帧周期事件门限       */
    ULONG  ulFrameSecondSummaryWindow;      /* 错误帧秒累计事件窗口     */
    ULONG  ulFrameSecondSummaryThreshold;   /* 错误帧秒累计事件门限     */
                                            
    ULONG  ulIsEnableFault;                 /* 是否使能紧急链路事件，按位输出 ，从低到高三位分别表示如下紧急事件的
                                               使能状态：链路故障、致命故障、紧急事件 */
    ULONG  ulLocalBoardState;               /* 本板设置的接口主备信息 */
    ULONG  ulRemoteBoardState;              /* 接收自对端的接口主备信息 */
                                               
}OAM3AH_CFG_INFO_S;

/*Added by wangtong207740, HIU 3AH规格扩展, 2012/6/14 */
/* 对外输出3AH配置信息结构体 */
typedef struct tag3ahCfgInfoEx
{
    ULONG  ul3AHEnable;                     /* 是否已使能                       */
    ULONG  ul3AHMode;                       /* 工作模式 0~主动模式，1~被动模式  */
    ULONG  ulDetectInteval;                 /* 探测速率                         */
    ULONG  ulPDUSize;                       /* 最大PDUSize                      */
    ULONG  ulLbTestMode;                    /* 环回测试模式 0~visp软件测试模式，1~NP测试模式    */
    ULONG  ulIsEnableEvent;                 /* 是否使能链路事件，按位输出，从低到高四位分别表示如下事件的使能状态：
                                               错误符号周期事件、 错帧事件、错误帧周期事件、错帧秒事件 */

    DULONG_S  stSymbolPeriodWindow;            /* 错误符号周期事件窗口     */
    DULONG_S  stSymbolPeriodThreshold;         /* 错误符号周期事件门限     */
    USHORT  usFrameWindow;                   /* 错误帧事件窗口           */
    UCHAR szReserve[2];                      /* 字节对齐 */
    ULONG  ulFrameThreshold;                /* 错误帧事件门限           */
    ULONG  ulFramePeriodWindow;             /* 错误帧周期事件窗口       */
    ULONG  ulFramelPeriodThreshold;         /* 错误帧周期事件门限       */
    USHORT  usFrameSecondSummaryWindow;      /* 错误帧秒累计事件窗口     */
    USHORT  usFrameSecondSummaryThreshold;   /* 错误帧秒累计事件门限     */
                                            
    ULONG  ulIsEnableFault;                 /* 是否使能紧急链路事件，按位输出 ，从低到高三位分别表示如下紧急事件的
                                               使能状态：链路故障、致命故障、紧急事件 */
    ULONG  ulLocalBoardState;               /* 本板设置的接口主备信息 */
    ULONG  ulRemoteBoardState;              /* 接收自对端的接口主备信息 */
                                               
}OAM3AH_CFG_INFO_EX_S;

/*接口OAMPDU报文统计*/
typedef struct tagOam3ahPduStat
{
    ULONG ulSndTotalOampdu;                 /* 接口发送总的OAMPDU报文        */
    ULONG ulSndDropOampdu;                  /* 接口发送时总的丢弃OAMPDU报文  */
    ULONG ulSndInfoOampdu;                  /* 接口发送信息OAMPDU报文        */
    ULONG ulSndEventOampdu;                 /* 接口发送事件OAMPDU报文        */
    ULONG ulSndFaultOampdu;                 /* 接口发送故障OAMPDU报文        */
    ULONG ulSndLbOampdu;                    /* 接口发送环回控制OAMPDU报文    */
    
    ULONG ulRcvTotalOampdu;                 /* 接口接收总的OAMPDU报文        */
    ULONG ulRcvDropOampdu;                  /* 接口接收总的丢弃OAMPDU报文    */
    ULONG ulRcvInfoOampdu;                  /* 接口接收信息OAMPDU报文        */
    ULONG ulRcvEventOampdu;                 /* 接口接收事件OAMPDU报文        */
    ULONG ulRcvFaultOampdu;                 /* 接口接收故障OAMPDU报文        */
    ULONG ulRcvLbOampdu;                    /* 接口接收环回控制OAMPDU报文    */
}OAM3AH_PDUSTAT_S;



/* 获取底层错帧适配函数原型     */
typedef ULONG (*GET_PHY_ERROR_FRAME_HOOK_FUNC)(ULONG ulIfIndex, DULONG_S *pstdulNum);

/* 下发周期事件参数适配函数原型 */
typedef ULONG (*SET_LINK_EVENT_WINTHRSH_HOOK_FUNC)(ULONG ulIfIndex, ULONG ulEventType, ULONG ulEnabled,
                                                   ULONG ulErrorWindow, ULONG ulErroredThreshold);

/*Added by z00208058/w00207740, 3AH链路事件窗口和门限规格扩展, 2012/5/9 */
typedef ULONG (*SET_LINK_EVENT_WINTHRSH_EX_HOOK_FUNC)(ULONG ulIfIndex, ULONG ulEventType, ULONG ulEnabled,DULONG_S dulErrorWindow, DULONG_S dulErroredThreshold);

typedef ULONG (*LBINPUT_HOOK_FUNC) (struct tagMBuf *pstMBuf, ULONG ulIfIndex);

#define OAM3AH_LB_REMOTE_INPUT  0       /* 环回发起端注册接收函数   */
#define OAM3AH_LB_LOCAL_INPUT   1       /* 环回响应端注册接收函数   */

/* 组织自定义TLV对外通知适配函数原型 */
typedef ULONG (*OAM3AH_ORG_SPEC_NOTIFY_HOOK_FUNC)(ULONG ulIfIndex, ULONG ulOrgSpecType, VOID* OrgSpecInfo);

/* 自定义TLV对外通知类型: 主备信息类型 */
#define OAM3AH_ORGSPEC_BOARDSTATE_TYPE 0x01

/* 自定义TLV对外通知数据: 主备信息类型对应的数据 */
typedef struct tagOam3ahOrgSpecBoardState
{
    /* 0-对端无主备信息通知; 1-主用信息; 2-备用信息 */
    ULONG ulOldState;
    ULONG ulNewState;
}OAM3AH_ORGSPEC_BOARDSTATE_S;


/* 事件/故障使能接口使能参数中BIT位枚举  */  
typedef enum enOam3ahEnableBit
{
    OAM3AH_BIT_ERR_SYMPRD = 0,
    OAM3AH_BIT_ERR_FRAME,
    OAM3AH_BIT_ERR_FRMPRD,
    OAM3AH_BIT_ERR_FRMSECSUM,

    OAM3AH_BIT_LINKFAULT,
    OAM3AH_BIT_DYINGGASP,
    OAM3AH_BIT_CRITICALEVT,
    OAM3AH_BIT_MAX,
}OAM3AH_ENABLE_BIT_E;

/* max event enable value */
#define OAM3AH_EVENT_MAX_ENABLE   ((0x1 << OAM3AH_BIT_MAX) - 1)

/* 用户接口事件类型参数枚举定义  */
typedef enum
{
    OAM3AH_API_LINKEVENT_SYMPRD = 1,
    OAM3AH_API_LINKEVENT_FRAME,
    OAM3AH_API_LINKEVENT_FRMPRD,
    OAM3AH_API_LINKEVENT_FRMSECSUM,
}OAM3AH_API_LINKEVENT_E;

/* 用户接口故障类型参数枚举定义  */
typedef enum
{
    OAM3AH_API_FAULT_LINKFAULT = 0,
    OAM3AH_API_FAULT_DYINGGASP,
    OAM3AH_API_FAULT_CRITICALEVT,
}OAM3AH_API_FAULT_E;

/* 获取3AH状态机状态 */
typedef enum tagOam3ahStateInfo
{
    OAM3AH_SESSION_IDLE,               /* 未使能3AH，状态机处于IDLE状态    */
    OAM3AH_SESSION_DISCOVER,           /* 正在发现阶段                     */
    OAM3AH_SESSION_DETECT,             /* 完成发现，定时探测阶段           */
    OAM3AH_SESSION_LB_LOCAL,           /* 本端处于环回响应稳态             */
    OAM3AH_SESSION_LB_REMOTE,          /* 本端处于环回发起稳态             */
}OAM3AH_STATE_INFO_E;

/* 事件/故障发生位置:本端/对端  */
typedef enum enEventLocation
{
    OAM3AH_EVENT_LCL,               /* 本地事件/故障    */
    OAM3AH_EVENT_RMT                /* 对端事件/故障    */
}OAM3AH_EVENT_LOCATION_E;

/* 故障状态 */
typedef enum enFaultState
{
    OAM3AH_FAULT_END,           /* 故障状态标志,故障消失     */
    OAM3AH_FAULT_BEGIN,         /* 故障状态标志,故障开始     */
}OAM3AH_FAULT_STATE_E;

/* 3ah HA统计信息数据结构 */
typedef struct tag3ahHaStat
{
    ULONG ul3ahHaOutSucsPkt;    /* 主板成功发送的3AH备份报文数  */
    ULONG ul3ahHaOutFailPkt;    /* 主板发送备份报文失败数       */
    ULONG ul3ahHaInSucsPkt;     /* 备板接收的恢复成功的HA报文数 */
    ULONG ul3ahHaInFailPkt;     /* 备板接收的恢复失败的HA报文数(包括非法报文) */ 
}OAM3AH_HASTAT_S;


/* 3AH对外告警状态 */
typedef struct tagOam3ahWarnState
{ 
    ULONG ulLclLinkFaultWarn;     /* 本端链路故障告警 */
    ULONG ulRmtLinkFaultWarn;     /* 远端链路故障告警 */
    ULONG ulLclDyingGaspWarn;     /* 本端致命故障告警 */
    ULONG ulRmtDyingGaspWarn;     /* 远端致命故障告警 */
    ULONG ulLclCriticalEvtWarn;   /* 本端紧急事件告警 */
    ULONG ulRmtCriticalEvtWarn;   /* 远端紧急事件告警 */                                                                 
}OAM3AH_WARN_STATE_S;                          

/* lb test mode */
#define OAM3AH_LB_TEST_VISP     0   /* visp软件实现环回功能 */
#define OMM3AH_LB_TEST_NP       1   /* np实现环回功能       */

/* 3ah work mode */
#define OAM3AH_PASSIVE_MODE     0   /*工作模式为被动模式*/
#define OAM3AH_ACTIVE_MODE      1   /*工作模式为主动模式*/

/* define 3ah enable & disable */
#define OAM3AH_DISABLE          0
#define OAM3AH_ENABLE           1
#define OAM3AH_VIRTUAL_ENABLE   2

/* board state */
#define OAM3AH_BOARD_STATE_NULL     0 /* 取消向对端通告本端主备状态 */
#define OAM3AH_BOARD_STATE_MASTER   1
#define OAM3AH_BOARD_STATE_SLAVE    2

/* DULONG_S(双字节)结构计算宏 ---- BEGIN */
#define DULONG_S_COMPARE(dulFirst,dulSecond) \
    (((dulFirst).ulDulHi<(dulSecond).ulDulHi)?-1: \
        (((dulFirst).ulDulHi>(dulSecond).ulDulHi)?1: \
            (((dulFirst).ulDulLo<(dulSecond).ulDulLo)?-1: \
                (((dulFirst).ulDulLo>(dulSecond).ulDulLo)?1:0))))

#define DULONG_S_ADD(dulSum,dulFirst,dulSecond)    \
{ \
    DULONG_S dulSum_temp; \
    \
    (dulSum_temp).ulDulLo = (dulFirst).ulDulLo+(dulSecond).ulDulLo; \
    (dulSum_temp).ulDulHi = (dulFirst).ulDulHi+(dulSecond).ulDulHi+(ULONG)((dulSum_temp).ulDulLo<(dulFirst).ulDulLo); \
    (dulSum).ulDulLo = (dulSum_temp).ulDulLo;\
    (dulSum).ulDulHi = (dulSum_temp).ulDulHi;\
}

#define DULONG_S_SUB(dulResult,dulFirst,dulSecond) \
{ \
    DULONG_S dulRst_temp; \
    \
    (dulRst_temp).ulDulLo = (dulFirst).ulDulLo-(dulSecond).ulDulLo; \
    (dulRst_temp).ulDulHi = (dulFirst).ulDulHi-(dulSecond).ulDulHi-(ULONG)((dulRst_temp).ulDulLo>(dulFirst).ulDulLo); \
    (dulResult).ulDulLo = (dulRst_temp).ulDulLo;\
    (dulResult).ulDulHi= (dulRst_temp).ulDulHi;\
}

#define DULONG_S_SELFADD(dulResult)\
{\
    (dulResult).ulDulLo++;\
    if((dulResult).ulDulLo == 0)\
        (dulResult).ulDulHi++; \
}

#define DULONG_S_COPY(dulTo, dulFrom)\
{\
    (dulTo).ulDulHi = (dulFrom).ulDulHi;\
    (dulTo).ulDulLo = (dulFrom).ulDulLo;\
}

#define DULONG_S_COMPARE_ULONG(dulFirst,ulSecond)\
(((dulFirst).ulDulHi>0)?1: \
        (((dulFirst).ulDulLo>ulSecond)?1: \
            (((dulFirst).ulDulLo<ulSecond)?-1:0)))

/* DULONG_S(双字节)结构计算宏 ---- END */

/* ------------------------------------------------------------------------------------ */
/* 3ah_api.c */
/*******************************************************************************
*    Func Name: TCPIP_3AH_Enable
*  Description: 使能/去使能接口的3AH功能
*        Input: ULONG ulIfIndex:                接口索引
*               ULONG ul3AHEnable:              使能/去使能 3AH 功能，0 去使能，1 使能，2虚使能
*       Output: 
*       Return: OAM3AH_OK                       操作成功
*               OAM3AH_ERR_HA_IS_SMOOTHING      正在平滑
*               OAM3AH_ERR_PARA                 参数错误
*               OAM3AH_ERR_IF_NULL              接口不存在
*               OAM3AH_ERR_IF_INVALID           接口类型错误
*               OAM3AH_ERR_PORT_IS_VIRTUAL      接口非本板接口
*               OAM3AH_ERR_MEMORY               内存分配失败
*               OAM3AH_ERR_ENABLED              接口已使能3AH
*               OAM3AH_ERR_CB_NOTEXIST          3AH控制块不存在
*               OAM3AH_ERR_DISABLED             接口已经去使能
*               OAM3AH_ERR_NO_REGISTER          3AH模块未注册 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-11   chenfutian69112         Create
*
*******************************************************************************/
ULONG TCPIP_3AH_Enable(ULONG ulIfIndex, ULONG ul3AHEnable);
/*******************************************************************************
*    Func Name: TCPIP_3AH_SetDetect
*  Description: 设置3AH的探测周期
*        Input: ULONG ulIfIndex:                接口索引
*               ULONG ulDetectInterval:         探测周期
*       Output: 
*       Return: OAM3AH_OK                       操作成功
*               OAM3AH_ERR_HA_IS_SMOOTHING      正在平滑
*               OAM3AH_ERR_PARA                 探测周期参数错误
*               OAM3AH_ERR_NP_NOT_SUPPORT       配置的探测周期NP不支持
*               OAM3AH_ERR_IF_NULL              接口不存在
*               OAM3AH_ERR_IF_INVALID           接口类型错误
*               OAM3AH_ERR_PORT_IS_VIRTUAL      接口非本板接口
*               OAM3AH_ERR_MEMORY               内存分配失败
*               OAM3AH_ERR_NO_REGISTER          3AH模块未注册 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-11   LY(57500)               Create
*
*******************************************************************************/
ULONG TCPIP_3AH_SetDetect(ULONG ulIfIndex, ULONG ulDetectInteval);
/*******************************************************************************
*    Func Name: TCPIP_3AH_SetLoopback
*  Description: 使能/去使能远端环回
*        Input: ULONG ulIfIndex:                接口索引
*               ULONG ulLoopbackCmd:            使能/去使能命令，0去使能，1使能。
*       Output: 
*       Return: OAM3AH_OK                       操作成功
*               OAM3AH_ERR_HA_IS_SMOOTHING      正在平滑
*               OAM3AH_ERR_PARA                 参数错误
*               OAM3AH_ERR_IF_NULL              接口不存在
*               OAM3AH_ERR_IF_INVALID           接口类型错误
*               OAM3AH_ERR_CB_NOTEXIST          3AH控制块不存在
*               OAM3AH_ERR_DISABLED             未使能3AH
*               OAM3AH_ERR_WRONG_MODE           接口工作模式错误
*               OAM3AH_ERR_PORT_IS_VIRTUAL      接口非本板接口
*               OAM3AH_ERR_WRONG_STATE          状态机处于错误的状态
*               OAM3AH_ERR_NO_REGISTER          3AH模块未注册 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-11   chenfutian69112         Create
*
*******************************************************************************/
ULONG TCPIP_3AH_SetLoopback(ULONG ulIfIndex, ULONG ulLoopbackCmd);
/*******************************************************************************
*    Func Name: TCPIP_3AH_SetLbTestMode
*  Description: 设置环回测试模式
*        Input: ULONG ulIfIndex:                接口索引
*               ULONG ulLbTestMode:             环回测试模式,0 VISP软件实现环回,1 NP实现环回
*       Output: 
*       Return: OAM3AH_OK                       操作成功
*               OAM3AH_ERR_HA_IS_SMOOTHING      正在平滑
*               OAM3AH_ERR_PARA                 参数错误
*               OAM3AH_ERR_IF_NULL              接口不存在
*               OAM3AH_ERR_IF_INVALID           接口类型错误
*               OAM3AH_ERR_PORT_IS_VIRTUAL      接口非本板接口
*               OAM3AH_ERR_MEMORY               内存分配失败
*               OAM3AH_ERR_INLB                 处于环回错误状态
*               OAM3AH_ERR_NO_REGISTER          3AH模块未注册 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-11   chenfutian69112         Create
*
*******************************************************************************/
ULONG TCPIP_3AH_SetLbTestMode (ULONG ulIfIndex, ULONG ulLbTestMode);
/*******************************************************************************
*    Func Name: TCPIP_3AH_GlobalDisable
*  Description: 全局去使能3AH功能
*        Input: VOID
*       Output: 
*       Return: OAM3AH_ERR_HA_IS_SMOOTHING  正在平滑
*               OAM3AH_ERR_NO_REGISTER      接口未注册
*               OAM3AH_OK                   成功
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-11   GeXianJun121208         Create
*
*******************************************************************************/
ULONG TCPIP_3AH_GlobalDisable(VOID);
/*******************************************************************************
*    Func Name: TCPIP_3AH_SetMode
*  Description: 按接口索引设置3AH工作模式
*        Input: ULONG ulIfIndex:            接口索引
*               ULONG ul3AHMode:            工作模式（0-被动模式，1-主动模式）
*       Output: 
*       Return: OAM3AH_ERR_HA_IS_SMOOTHING: 正在平滑
*               OAM3AH_ERR_IF_NULL:         接口不存在
*               OAM3AH_ERR_IF_INVALID:      接口类型错误
*               OAM3AH_ERR_PORT_IS_VIRTUAL  接口非本板接口
*               OAM3AH_ERR_CB_NOTEXIT:      3AH控制块不存在
*               OAM3AH_ERR_ENABLED:         3AH已经使能
*               OAM3AH_ERR_NO_REGISTER:     接口未注册
*               OAM3AH_OK:                  设置成功
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-11   GeXianJun121208         Create
*
*******************************************************************************/
ULONG TCPIP_3AH_SetMode(ULONG ulIfIndex, ULONG ul3AHMode);
/*******************************************************************************
*    Func Name: TCPIP_3AH_SetPduSize
*  Description: 按接口设置OAMPDU最大长度
*        Input: ULONG ulIfIndex:            接口索引
*               ULONG ulPduSize:            最大OAMPDU参数值
*       Output: 
*       Return: OAM3AH_ERR_HA_IS_SMOOTHING: 正在平滑
*               OAM3AH_ERR_IF_NULL:         接口不存在
*               OAM3AH_ERR_IF_INVALID:      接口类型错误
*               OAM3AH_ERR_PORT_IS_VIRTUAL  接口非本板接口
*               OAM3AH_ERR_MEMORY:          内存分配失败
*               OAM3AH_ERR_PARA:            参数错误
*               OAM3AH_ERR_NO_REGISTER:     接口未注册
*               OAM3AH_OK:                  设置成功
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-11   GeXianJun121208         Create
*
*******************************************************************************/
ULONG TCPIP_3AH_SetPduSize(ULONG ulIfIndex, ULONG ulPduSize);
/*******************************************************************************
*    Func Name: TCPIP_3AH_GetCfgInfo
*  Description: 按接口获取3AH配置信息
*        Input: ULONG ulIfIndex:                    接口索引
*       Output: OAM_3AH_CFG_INFO_S* pst3AHCfgInfo:  保存输出配置信息的内存指针
*       Return: OAM3AH_ERR_NULL_POINTER:            指针参数为空
*               OAM3AH_ERR_IF_NULL:                 接口不存在
*               OAM3AH_ERR_IF_INVALID:              接口类型错误
*               OAM3AH_ERR_PORT_IS_VIRTUAL          接口非本板接口
*               OAM3AH_ERR_CB_NOTEXIST:             获取3AH控制块失败
*               OAM3AH_ERR_NO_REGISTER:             组建未注册
*               OAM3AH_OK:                          获取配置信息成功
*      Caution: 用户负责分配和释放
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-11   GeXianJun121208         Create
*
*******************************************************************************/
ULONG TCPIP_3AH_GetCfgInfo(ULONG ulIfIndex, OAM3AH_CFG_INFO_S* pst3AHCfgInfo);
/*******************************************************************************
*    Func Name: TCPIP_3AH_GetCfgInfoEx
* Date Created: 2012-06-14
*       Author: wangtong207740
*  Description: 按接口获取3AH配置信息
*        Input: ULONG ulIfIndex:                    接口索引
*       Output: OAM_3AH_CFG_INFO_S* pst3AHCfgInfo:  保存输出配置信息的内存指针
*       Return: OAM3AH_ERR_NULL_POINTER:            指针参数为空
*               OAM3AH_ERR_IF_NULL:                 接口不存在
*               OAM3AH_ERR_IF_INVALID:              接口类型错误
*               OAM3AH_ERR_PORT_IS_VIRTUAL          接口非本板接口
*               OAM3AH_ERR_CB_NOTEXIST:             获取3AH控制块失败
*               OAM3AH_ERR_NO_REGISTER:             组建未注册
*               OAM3AH_OK:                          获取配置信息成功
*      Caution: 用户负责分配和释放
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-06-14   wangtong207740          Create
*
*******************************************************************************/
ULONG TCPIP_3AH_GetCfgInfoEx(ULONG ulIfIndex, OAM3AH_CFG_INFO_EX_S* pst3AHCfgInfo);
/*******************************************************************************
*    Func Name: TCPIP_3AH_ShowInfo
*  Description: 按接口显示3AH重要信息
*        Input: char *szIfName:接口名
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-11   GeXianJun121208         Create
*
*******************************************************************************/
VOID  TCPIP_3AH_ShowInfo(char *szIfName);
/*******************************************************************************
*    Func Name: TCPIP_3AH_GetFSMInfo
*  Description: 按接口获取状态机信息
*        Input: ULONG ulIfIndex:                接口索引
*       Output: ULONG* pulState:                保存状态机状态内存指针
*       Return: OAM3AH_ERR_HA_IS_SMOOTHING:     正在平滑
*               OAM3AH_ERR_NULL_POINTER:        保存状态机状态内存指针为空
*               OAM3AH_ERR_IF_NULL:             接口不存在
*               OAM3AH_ERR_IF_INVALID:          接口类型错误
*               OAM3AH_ERR_PORT_IS_VIRTUAL      接口非本板接口
*               OAM3AH_ERR_CB_NOTEXIST:         获取接口控制块失败
*               OAM3AH_ERR_NO_REGISTER:         接口未注册
*               OAM3AH_OK:                      获取成功
*      Caution: 用户负责分配和释放
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-11   GeXianJun121208         Create
*
*******************************************************************************/
ULONG TCPIP_3AH_GetFSMInfo(ULONG ulIfIndex, ULONG* pulState);
/*******************************************************************************
*    Func Name: TCPIP_3AH_GetPacketStat
*  Description: 按接口获取OAM统计报文信息
*        Input: ULONG ulIfIndex:                    接口索引
*       Output: OAM_3AH_PDUSTAT_S * pstOampduStat:  保存统计输出的数据结构指针
*       Return: OAM3AH_ERR_NULL_POINTER:            指针为空
*               OAM3AH_ERR_IF_NULL:                 接口不存在
*               OAM3AH_ERR_IF_INVALID:              接口类型错误
*               OAM3AH_ERR_PORT_IS_VIRTUAL          接口非本板接口
*               OAM3AH_ERR_CB_NOTEXIST:             获取接口控制块失败
*               OAM3AH_ERR_NO_REGISTER:             接口未注册
*               OAM3AH_OK:                          获取成功
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-11   GeXianJun121208         Create
*
*******************************************************************************/
ULONG TCPIP_3AH_GetPacketStat(ULONG ulIfIndex, OAM3AH_PDUSTAT_S * pstOampduStat);
/*******************************************************************************
*    Func Name: TCPIP_3AH_ShowPacketStat
*  Description: 按接口显示OAM统计报文信息
*        Input: char *szIfName:     接口名
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-11   GeXianJun121208         Create
*
*******************************************************************************/
VOID  TCPIP_3AH_ShowPacketStat(CHAR* szIfName);
/*******************************************************************************
*    Func Name: TCPIP_3AH_ClearPacketStat
*  Description: 按接口清零OAM报文统计信息
*        Input: ULONG ulIfIndex:                接口索引
*       Output: 
*       Return: OAM3AH_ERR_IF_NULL:             接口不存在
*               OAM3AH_ERR_IF_INVALID:          接口类型错误
*               OAM3AH_ERR_PORT_IS_VIRTUAL      接口非本板接口
*               OAM3AH_ERR_CB_NOTEXIST:         获取接口控制块失败
*               OAM3AH_ERR_NO_REGISTER:         接口未注册
*               OAM3AH_OK:                      成功
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-11   GeXianJun121208         Create
*
*******************************************************************************/
ULONG TCPIP_3AH_ClearPacketStat(ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_3AH_SetDbgSwitch
*  Description: 按接口设置调试开关级别
*        Input: ULONG ulIfIndex:            接口索引
*               ULONG ulDebugSwitche:       调试开关级别,调试级别分为4个：
*                                           OAM报文调试开关(0x1),状态机迁移调试开关(0x2),
*                                           环回测试报文调试开关(0x4),错误报文调试开关(0x8)
*       Output: 
*       Return: OAM3AH_ERR_PARA:            输入参数错误
*               OAM3AH_ERR_IF_NULL:         接口不存在
*               OAM3AH_ERR_IF_INVALID:      接口类型错误
*               OAM3AH_ERR_PORT_IS_VIRTUAL  接口非本板接口
*               OAM3AH_ERR_CB_NOTEXIST:     获取接口控制块失败
*               OAM3AH_ERR_NO_REGISTER:     组建未注册
*               OAM3AH_OK:                  成功
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-11   GeXianJun121208         Create
*
*******************************************************************************/
ULONG TCPIP_3AH_SetDbgSwitch(ULONG ulIfIndex, ULONG ulDebugSwitche);
/*******************************************************************************
*    Func Name: TCPIP_3AH_GetDbgSwitch
*  Description: 按接口获取调试开关级别
*        Input: ULONG ulIfIndex:            接口索引
*       Output: ULONG * pulDugInfo:         保存调试开关内存指针
*       Return: OAM3AH_ERR_PARA:            输入参数错误
*               OAM3AH_ERR_IF_NULL:         接口不存在
*               OAM3AH_ERR_IF_INVALID:      接口类型错误
*               OAM3AH_ERR_PORT_IS_VIRTUAL  接口非本板接口
*               OAM3AH_ERR_CB_NOTEXIST:     获取接口控制块失败
*               OAM3AH_ERR_NO_REGISTER:     接口未注册
*               OAM3AH_OK:                  成功
*      Caution: 用户负责分配和释放
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-11   GeXianJun121208         Create
*
*******************************************************************************/
ULONG TCPIP_3AH_GetDbgSwitch(ULONG ulIfIndex, ULONG *pulDugInfo);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetPhyErrorFrameNumHook
*  Description: 注册获取底层错帧的适配函数
*        Input: GET_PHY_ERROR_FRAME_HOOK_FUNC pfGetPhyErrorFrame: 要注册的函数指针
*       Output: 
*       Return: OAM3AH_OK:                  注册成功
*               OAM3AH_ERR_NULL_POINTER     注册失败(注册函数为NULL)
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-11    LY(57500)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_RegFuncGetPhyErrorFrameNumHook(GET_PHY_ERROR_FRAME_HOOK_FUNC pfGetPhyErrorFrame);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncSetLinkEventWinThrshHook
*  Description: 注册下发周期事件窗口和门限参数的适配函数
*        Input: SET_LINK_EVENT_WINTHRSH_HOOK_FUNC pfSetEventWinThrsh: 要注册的函数指针
*       Output: 
*       Return: OAM3AH_OK:                  注册成功
*               OAM3AH_ERR_NULL_POINTER     注册失败(注册函数为NULL)
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-11    LY(57500)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_RegFuncSetLinkEventWinThrshHook(SET_LINK_EVENT_WINTHRSH_HOOK_FUNC pfSetEventWinThrsh);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncLBInputHook
*  Description: 注册环回报文接收处理函数
*        Input: LBINPUT_HOOK_FUNC pfLBInput:    注册接收函数的指针
*               ULONG ulLbLclRmt:               环回响应端/应答端接收函数注册
*                                               0－环回发起端报文接收处理钩子。
*                                               1－环回响应端报文接收处理钩子
*       Output: 
*       Return: OAM3AH_OK                       操作成功
*               OAM3AH_ERR_PARA                 参数错误
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-14    LY(57500)        Create the first version.
*
*******************************************************************************/
ULONG TCPIP_RegFuncLBInputHook(LBINPUT_HOOK_FUNC pfLBInput, ULONG ulLbLclRmt);
/*******************************************************************************
*    Func Name: TCPIP_3AH_NotifyCriticalLinkEvent
*  Description: 用户通知向3AH模块通告致命故障或紧急事件的起始/终止
*        Input: ULONG ulIfIndex:                接口索引
*               ULONG ulCriticalLinkEventType:  故障类型;1-致命故障;2-紧急事件
*               ULONG ulState:                  故障状态;0-故障终止;1-故障发生
*       Output: 
*       Return: OAM3AH_OK                       处理成功
*               OAM3AH_ERR_HA_IS_SMOOTHING      系统处于平滑或手动倒换阶段
*               3AH_ERR_PARA                    参数错误
*               OAM3AH_ERR_IF_NULL              接口为空
*               OAM3AH_ERR_IF_INVALID           接口类型错误
*               OAM3AH_ERR_PORT_IS_VIRTUAL      接口非本板接口
*               OAM3AH_ERR_CB_NOTEXIST          控制块不存在
*               OAM3AH_ERR_DISABLED             3AH未使能
*               OAM3AH_ERR_NO_REGISTER          3AH模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-11    LY(57500)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_3AH_NotifyCriticalLinkEvent(ULONG ulIfIndex, ULONG ulCriticalLinkEventType, ULONG ulState);
/*******************************************************************************
*    Func Name: TCPIP_3AH_OccurErroredPeriodEvent
*  Description: 发生错帧周期事件或错误符号周期事件时产品调此函数通知VISP
*        Input: ULONG ulIfIndex:                接口索引
*               ULONG ulErroredType:            事件类型;1=错误符号周期事件;3=错帧周期事件 
*               DULONG_S stdulWindows:          事件窗口值
*               DULONG_S stdulThreshold:        事件门限值
*               DULONG_S stdulErrorNum:         本次错帧或错误符号数
*               DULONG_S stdulErrRunTotal:      总错帧或错误符号数
*       Output: 
*       Return: OAM3AH_OK                       处理成功
*               OAM3AH_ERR_MEMORY               系统内存不足
*               OAM3AH_ERR                      控制事件入队列失败
*               OAM3AH_ERR_NO_REGISTER          3AH模块未注册
*               OAM3AH_ERR_PARA                 链路事件参数错误
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-11    LY(57500)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_3AH_OccurErroredPeriodEvent(ULONG ulIfIndex, ULONG ulErroredType, DULONG_S stdulWindows,
                                  DULONG_S stdulThreshold, DULONG_S stdulErrorNum, DULONG_S stdulErrRunTotal);
/*******************************************************************************
*    Func Name: TCPIP_3AH_OccurErroredFrameEvent
*  Description: 发生错帧事件或错帧秒事件时产品调此函数通知VISP
*        Input: ULONG ulIfIndex:                接口索引
*               ULONG ulErroredType:            事件类型;2=错帧事件;4=错帧秒事件 
*               DULONG_S stdulWindows:          事件窗口值
*               DULONG_S stdulThreshold:        事件门限值
*               DULONG_S stdulErrorNum:         本次错帧或错帧秒数
*               DULONG_S stdulErrRunTotal:      总错帧或错帧秒数
*       Output: 
*       Return: OAM3AH_OK                       处理成功
*               OAM3AH_ERR_MEMORY               系统内存不足
*               OAM3AH_ERR                      控制事件入队列失败
*               OAM3AH_ERR_NO_REGISTER          3AH模块未注册
*               OAM3AH_ERR_PARA                 链路事件参数错误
*               OAM3AH_ERR_FRAME_ACT            错帧/错帧秒实现方式配置不支持
*      Caution: 错帧和错帧秒事件可以由VISP实现也可以由产品实现，如果是产品实现则调用此接口通知VISP
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-7-26    LY(57500)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_3AH_OccurErroredFrameEvent(ULONG ulIfIndex, ULONG ulErroredType, DULONG_S stdulWindows,
                                       DULONG_S stdulThreshold, DULONG_S stdulErrorNum, DULONG_S stdulErrRunTotal);
/*******************************************************************************
*    Func Name: TCPIP_3AH_EventEnable
*  Description: 使能去使能3AH链路事件或故障通告功能
*        Input: ULONG ulIfIndex:        接口索引
*               ULONG ulEventEnable:    事件使能参数, 0~127，使用低七位分别表示四种链路事件和三种故障检测的使能状态，
*                                       对应事件位置1表示使能，置0表示去使能。
*                                       第1位代表错误符号周期事件，
*                                       第2位代表错帧事件，
*                                       第3位代表错帧周期事件，
*                                       第4位代表错帧秒累计事件，
*                                       第5位代表链路故障，
*                                       第6位代表致命故障，
*                                       第7位代表紧急事件
*       Output: 
*       Return: OAM3AH_OK                       处理成功
*               OAM3AH_ERR_HA_IS_SMOOTHING      3AH正平滑处理或手动倒换处理
*               OAM3AH_ERR_PARA                 参数有效性错误 
*               OAM3AH_ERR_IF_NULL              接口为空
*               OAM3AH_ERR_IF_INVALID           接口类型错误
*               OAM3AH_ERR_PORT_IS_VIRTUAL      接口非本板接口
*               OAM3AH_ERR_MEMORY               内存空间不足
*               OAM3AH_ERR_NO_REGISTER          3AH模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-11    LY(57500)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_3AH_EventEnable(ULONG ulIfIndex, ULONG ulEventEnable);
/*******************************************************************************
*    Func Name: TCPIP_3AH_SetErroredWinThres
*  Description: 设置 3AH 各链路事件窗口和门限
*        Input: ULONG ulIfIndex:                接口索引
*               ULONG ulLinkEventType:          链路事件类型
*                                               1代表错误符号周期事件
*                                               2代表错误帧事件
*                                               3代表错误帧周期事件
*                                               4代表错误秒累计事件
*               ULONG ulErrWindow:              窗口（单位100ms）
*               ULONG ulErrThres:               门限（单位：个）
*       Output: 
*       Return: OAM3AH_OK                       操作成功
*               OAM3AH_ERR_HA_IS_SMOOTHING      正在平滑
*               OAM3AH_ERR_PARA                 参数错误
*               OAM3AH_ERR_EVENT_WIN            窗口值不合法
*               OAM3AH_ERR_EVENT_THRESH         门限值不合法
*               OAM3AH_ERR_WIN_THRESH_CONFLICT  窗口值和门限值冲突
*               OAM3AH_ERR_IF_NULL              接口不存在
*               OAM3AH_ERR_IF_INVALID           接口类型错误
*               OAM3AH_ERR_PORT_IS_VIRTUAL      接口非本板接口
*               OAM3AH_ERR_MEMORY               内存分配失败
*               OAM3AH_ERR_NO_REGISTER          3AH模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-11   chenfutian69112         Create
*
*******************************************************************************/
ULONG TCPIP_3AH_SetErroredWinThres(ULONG ulIfIndex, ULONG ulLinkEventType, ULONG ulErrWindow, ULONG ulErrThres);
/*******************************************************************************
*    Func Name: TCPIP_3AH_NpLostLink
*  Description: NP检测到链路DOWN后通知VISP
*        Input: ULONG ulIfIndex:    接口索引
*       Output: 
*       Return: OAM3AH_OK:              通知成功
*               OAM3AH_ERR_NO_REGISTER  组件未注册
*               OAM3AH_ERR              入底层控制信息队列失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-15    LY(57500)        Create the first version.
*
*******************************************************************************/
ULONG TCPIP_3AH_NpLostLink(ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_3AH_SetHaDbg
*  Description: 设置HA调试开关
*        Input: ULONG ulDbg: 调试开关.1打开/0关闭
*       Output: 
*       Return: VOS_OK/VOS_ERR:设置成功/设置失败
*               OAM3AH_ERR_NO_REGISTER: 组件未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-4-25    LY(57500)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_3AH_SetHaDbg(ULONG ulDbg);
/*******************************************************************************
*    Func Name: TCPIP_3AH_GetHaDbg
*  Description: 获取HA调试开关
*        Input: ULONG *pulDbg: 保存调试开关的ULONG变量指针
*       Output: 
*       Return: VOS_OK/VOS_ERR:获取成功/获取失败
*               OAM3AH_ERR_NO_REGISTER: 组件未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-4-25    LY(57500)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_3AH_GetHaDbg(ULONG *pulDbg);
/*******************************************************************************
*    Func Name: TCPIP_3AH_GetHaStat
*  Description: 获取3AH HA统计信息
*        Input: OAM3AH_HASTAT_S *pst3AHHaStat:  保存输出统计信息的内存指针
*       Output: 
*       Return: OAM3AH_OK                       获取成功
*               OAM3AH_ERR_NULL_POINTER         指针参数错误
*               OAM3AH_ERR_NO_REGISTER          3AH模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-12    LY(57500)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_3AH_GetHaStat(OAM3AH_HASTAT_S *pst3AHHaStat);
/*******************************************************************************
*    Func Name: TCPIP_3AH_ClearHaStat
*  Description: 清零3AH HA统计信息
*        Input: VOID
*       Output: 
*       Return: OAM3AH_OK                       清零成功
*               OAM3AH_ERR_NO_REGISTER          3AH模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-12    LY(57500)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_3AH_ClearHaStat(VOID);
/*******************************************************************************
*    Func Name: TCPIP_3AH_StartLbTest
*  Description: 启动 3AH 环回测试
*        Input: ULONG ulIfIndex:            接口索引
*               VOID* pBuffer:              报文指针
*               ULONG ulBufLen:             报文长度
*       Output: 
*       Return: OAM3AH_OK                   成功
*               OAM3AH_ERR_NO_REGISTER      3AH模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-15   chenfutian69112         Create
*
*******************************************************************************/
ULONG TCPIP_3AH_StartLbTest(ULONG ulIfIndex, VOID* pBuffer, ULONG ulBufLen);
/*******************************************************************************
*    Func Name: TCPIP_3AH_SetBoardState
*  Description: 设置本端的主备状态，用于通过ORG TLV向对端通告本端状态
*        Input: ULONG ulIfIndex: 接口索引
*               ULONG ulState: 0-取消对端通告,1-本端为主用板,2-本端为备用板
*       Output: 
*       Return: OAM3AH_OK:                      设置成功
*               OAM3AH_ERR_HA_IS_SMOOTHING      3AH正平滑处理或手动倒换处理
*               OAM3AH_ERR_PARA                 参数有效性错误
*               OAM3AH_ERR_IF_NULL              接口不存在
*               OAM3AH_ERR_IF_INVALID           接口类型错误
*               OAM3AH_ERR_PORT_IS_VIRTUAL      接口非本板接口
*               OAM3AH_ERR_CB_NOTEXIST          3AH配置控制块不存在
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-7-26    LY(57500)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_3AH_SetBoardState(ULONG ulIfIndex, ULONG ulState);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncOrgSpecNotifyHook
*  Description: 产品注册处理组织自定义TLV的适配函数
*        Input: OAM3AH_ORG_SPEC_NOTIFY_HOOK_FUNC pfOrgSpecNotify: 产品处理组织自定义TLV的适配函数指针
*       Output: 
*       Return: OAM3AH_OK:                  注册成功
*               OAM3AH_ERR_NULL_POINTER     注册失败(注册函数为NULL)
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-7-28    LY(57500)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_RegFuncOrgSpecNotifyHook(OAM3AH_ORG_SPEC_NOTIFY_HOOK_FUNC pfOrgSpecNotify);


/*******************************************************************************
*    Func Name: TCPIP_3AH_IoBoardSyncMainBoard
* Date Created: 2008-11-15
*       Author: luowentong105073
*  Description: 接口板状态同步到主控板
*        Input: OAM3AH_WARN_PARAM_S* pstWarn:
*       Output: 
*       Return: OAM3AH_OK:  成功 
*               其它: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-15   luowentong105073        Create
*
*******************************************************************************/
ULONG TCPIP_3AH_IoBoardSyncMainBoard(OAM3AH_WARN_PARAM_S* pstWarn);

/*******************************************************************************
*    Func Name: TCPIP_3AH_Set_NegTimeoutWaring
* Date Created: 2009-02-27
*       Author:  LiuYong/GeXianJun(57500/121208) 
*  Description: 设置/取消首次协商不过对外告警功能
*        Input: ULONG ulTime:为0时表示取消协商不过对外告警功能
*                            非0表示设置协商不过对外告警功能，
*                            ulTime数值表示用户指定的协商时间
*       Output: 
*       Return: 成功:VOS_OK;失败:返回错误码
*      Caution: ulTime必须为5的倍数,否则返回错误,最大为600s
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-27    LiuYong/GeXianJun(57500/121208)    Create
*
*******************************************************************************/
ULONG TCPIP_3AH_Set_NegTimeoutWaring (ULONG ulTime);

/*******************************************************************************
*    Func Name: TCPIP_3AH_Get_NegTimeoutWaring
* Date Created: 2009-02-27
*       Author:  LiuYong/GeXianJun(57500/121208) 
*  Description:  获取首次协商不过对外告警时间
*        Input: ULONG *pulTime: 用户指定的协商时间
*       Output: 
*       Return: 成功:OAM3AH_OK;失败:返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-27    LiuYong/GeXianJun(57500/121208)    Create
*
*******************************************************************************/
ULONG TCPIP_3AH_Get_NegTimeoutWaring (ULONG *pulTime);

/*******************************************************************************
*    Func Name: TCPIP_3AH_GetFaultWarnState
* Date Created: 2010-10-13
*       Author: c00168670
*  Description: 获取3AH本地和远端的故障告警状态
*        Input: ULONG ulIfIndex: 接口索引
*               OAM3AH_WARN_STATE_S* pst3ahWarnState: 3AH告警状态数据结构指针
*       Output: 
*       Return: 成功:OAM3AH_OK;失败:返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-10-13   c00168670               Create
*
*******************************************************************************/
ULONG TCPIP_3AH_GetFaultWarnState(ULONG ulIfIndex, OAM3AH_WARN_STATE_S* pst3ahWarnState);


ULONG TCPIP_3AH_SetErroredWinThresEx(ULONG ulIfIndex, ULONG ulLinkEventType, DULONG_S stdulErrWindow, DULONG_S stdulErrThres);


ULONG TCPIP_RegFuncSetLinkEventWinThrshExHook(SET_LINK_EVENT_WINTHRSH_EX_HOOK_FUNC pfSetEventWinThrsh);

/*******************************************************************************
*    Func Name: TCPIP_SetDealPacketWithVlanSwitch
* Date Created: 2012-10-22
*       Author: wangtong207740
*  Description: 
*        Input: ULONG ulSwitch:开VRP_YES 关VRP_NO
*       Output: VOS_OK设置成功             
*       Return: 错误返回错误码
*      Caution: 开启可以处理带VLAN的OAMPDU，关闭不能处理，默认为开启
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-10-22   wangtong207740          Create
*
*******************************************************************************/
ULONG TCPIP_SetDealPacketWithVlanSwitch(ULONG ulSwitch);

/*******************************************************************************
*    Func Name: TCPIP_GetDealPacketWithVlanSwitch
* Date Created: 2012-10-22
*       Author: wangtong207740
*  Description: 
*        Input: 
*       Output: ULONG *pulSwitch:
*       Return: 
*      Caution: 获取配置
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-10-22   wangtong207740          Create
*
*******************************************************************************/
ULONG TCPIP_GetDealPacketWithVlanSwitch(ULONG *pulSwitch);


#ifdef __cplusplus
}
#endif      /* end of __cplusplus   */

#endif      /* end of _3AH_API_H_   */

