/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              vrrp_api.h
*
*  Project Code: VISPV1R7
*   Module Name: VRRP
*  Date Created: 2008-01-12
*        Author: wuhailan
*   Description: vrrp模块对外提供api文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*-------------------------------------------------------------------------------
*  2008-10-18  wuhailan         Create the first version.
*
*******************************************************************************/
#ifndef _VRRP_API_H_
#define _VRRP_API_H_

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************
 * 错误码定义:                                                                 *
 *******************************************************************************/
/* VRRP模块错误码定义 */
typedef enum enumVrrpErrCode
{
    VRRP_OK = VOS_OK,                   /* 0 OK    */
    VRRP_ERR,                           /* 1 未知错误 */

    VRRP_ERR_NO_REGISTER = MID_COMP_VRRP + 1,   /* 2 组件未初始化, 值从0x0e3a0001即238682113开始 */
    VRRP_ERR_MALLOC_FAIL,               /* 3 申请内存失败 */
    VRRP_ERR_INVALID_VRID,              /* 4 无效的VRID，超出VRID的有效性范围 */
    VRRP_ERR_NULL_IFNET,                /* 5 接口为NULL */
    VRRP_ERR_INVALID_IFTYPE,            /* 6 无效的接口类型 */
    VRRP_ERR_VRID_REPEAT,               /* 7 同一个vrid不能在多个接口上创建 */
    VRRP_ERR_MAX_ROUTERNUM_PERPORT,     /* 8 超过每个端口上最大的虚拟路由器数目 */
    VRRP_ERR_SUBIF,                     /* 9 不允许对子接口进行操作 */
    VRRP_ERR_STANDBY_NOEXIST,           /* 10 备份组不存在，VRID有效，但是不存在对应的备份组 */
    VRRP_ERR_INVALID_IPADDR,            /* 11 地址非法 */
    VRRP_ERR_NOTSAMENET,                /* 12 虚IP与接口所有IP不在同一网段 */
    VRRP_ERR_IP_IN_OTHER_STANDBY,       /* 13 虚地址已经配置在另外的备份组里 */
    VRRP_ERR_IP_CONFLIC,                /* 14 虚IP与其他接口地址冲突 */
    VRRP_ERROR_ADDRESS_TOO_MANY,        /* 15 备份组中配置的虚地址达到最大值 */
    VRRP_ERR_NOOWNER,                   /* 16 不是IPOWNER*/
    VRRP_ERR_PPINOTREGISTER,            /* 17 PPI接口未注册,下发PPI失败 */
    VRRP_ERR_INVALIDTYPE,               /* 18 命令字类型错误 */
    VRRP_ERR_NULLPOINTER,               /* 19 参数指针为空 */
    VRRP_ERR_PARAWRONG,                 /* 20 参数不合法 */
    VRRP_ERR_IP_NOINSTANDBY,            /* 21 虚IP不在备份组中 */
    VRRP_ERR_IN_NO_PREEMPT,             /* 22 在不可抢占的时候不能配置delay time */
    VRRP_ERR_REDUCED,                   /* 23 优先级减少值不合法 */
    VRRP_ERR_CANNOT_TRACK_ITSELT,       /* 24 备份组不能监视它所在的接口 */
    VRRP_ERR_TRACK_INTERFACE_TOO_MANY,  /* 25 要监视的接口数超过了最大值 */
    VRRP_ERR_TRACK_INTERFACE_NOT_EXIST, /* 26 要取消监视的接口不存在 */
    VRRP_ERR_1AG_NO_REGISTER,           /* 27 未初始化1ag模块 */
    VRRP_ERR_MEPIDWRONG,                /* 28 输入的mep id不合法 */
    VRRP_ERR_SETFLAG,                   /* 29 输入的使能标志不合法 */
    VRRP_ERR_TRACK_1AG_TOO_MANY,        /* 30 要监视的1AG会话超过了最大值 */
    VRRP_ERR_TRACK_1AG_NOT_EXIST,       /* 31 要取消监视的1AG会话不存在 */
    VRRP_ERR_TRACK_3AH_NOT_EXIST,       /* 32 3ah会话不存在 */
    VRRP_ERR_3AH_NO_REGISTER,           /* 33 未初始化3ah模块 */
    VRRP_ERR_TRACK_3AH_TOO_MANY,        /* 34 要监视的3AH会话超过了最大值 */
    VRRP_ERR_AUTHKEY_TOO_LONG,          /* 35 认证字长度超过了最大值 */
    VRRP_ERR_AUTHKEY_ZERO,              /* 36 认证字长度不能为0 */
    VRRP_ERR_TRACK_1AG_NAME_LEN,        /* 37 1ag的md,ma名字长度错误 */
    VRRP_ERR_TRACK_1AG_GET_RMEP_STATUS, /* 38 获取rmep状态失败 */
    VRRP_ERR_BFDSESSIONID,              /* 39 设置BFD监听功能的BFD SESSION ID非法 */
    VRRP_ERR_TRACK_BFD_TOO_MANY,        /* 40 要监视的BFD会话数超过了最大值 */
    VRRP_ERR_TRACK_BFD_GETSESSIONFAIL,  /* 41 获取要监视的BFD会话失败 */
    VRRP_ERR_TRACK_BFD_NOTREGISTERHOOK, /* 42 BFD未注册监听BFD会话是否存在的钩子 */
    VRRP_ERR_TRACK_BFD_NOT_EXIST,       /* 43 要删除监视的BFD会话不存在 */
    VRRP_ERR_STATE_INITIALIZE,          /* 44 备份组处理初始化状态 */
    VRRP_ERR_VRFNOTREG_INVALIDINDEX,    /* 45 VRF组件未注册时输入的vrf索引不为0 */
    VRRP_ERR_INVALIDVRFINDEX,           /* 46 VRF索引非法 */

    VRRP_ERR_MAXCODE                    /* 最大错误码 */
}VRRP_ERRCODE_E;

/*******************************************************************************
 * 宏定义:                                                                     *
 *******************************************************************************/
#define VRRP_VIRTUAL_IP_ADDRESS_MAX             16
#define VRRP_TRACK_MAX                          8
#define VRRP_AUTHENTICATION_KEY_LENGTH          8

/* 每个端口上最大的虚拟备份组数目 */
#define VRRP_MAX_ROUTERNUM_PERPORT              14

/* 最大MD MA名字长度 */
#define VRRP_MAX_MDNAME_LEN                     43
#define VRRP_MAX_MANAME_LEN                     43

/* vrrp记录的接口状态 */
#define VRRP_IF_UP                              1
#define VRRP_IF_DOWN                            2
#define VRRP_IF_DELETE                          3

/* vrrp 监视的1ag会话是否有告警 */
#define VRRP_1AG_NO_WARNING                     0
#define VRRP_1AG_WARNING                        1

/* vrrp记录的3ah会话状态 */
#define VRRP_3AH_UP                              0
#define VRRP_3AH_DOWN                            1

/* vrrp记录的BFD会话状态 */
#define VRRP_BFD_STATE_UP                       0
#define VRRP_BFD_STATE_DOWN                     1
#define VRRP_BFD_SESSION_DELETE                 2

/* VRRP使能标志 */
#define VRRP_DISABLE                           0
#define VRRP_ENABLE                            1

/* 状态机的状态 */
#define VRRP_STATE_INITIALIZE                   1
#define VRRP_STATE_BACKUP                       2
#define VRRP_STATE_MASTER                       3

/*******************************************************************************
 * 枚举定义:                                                                   *
 *******************************************************************************/
/* VRRP调试类型 */
typedef enum enVRRP_DEBUG_TYPE
{
    VRRP_DEBUG_PACKET,
    VRRP_DEBUG_ERROR,
    VRRP_DEBUG_STATE,
    VRRP_DEBUG_EVENT,
    VRRP_DEBUG_ALL
}VRRP_DEBUG_TYPE_E;

/* VRRP状态切换诊断字 */
typedef enum enVRRP_STATE_CHANGE_DIAG
{
    /* 0, 初始化值 */
    VRRP_STATE_DIAG_NONE,
    /* 1, init->master: 备份组首次添加虚拟IP，且该IP是接口真实IP */
    VRRP_ADD_REAL_IP,
    /* 2, init->master: 备份组所在接口up，且备份组里某个虚拟IP是接口上的真实IP */
    VRRP_IF_UP_WITH_REAL_IP,

    /* 3, init->backup: 备份组首次添加虚拟IP，且该IP不是接口的真实IP */
    VRRP_ADD_VIRTUAL_IPADDR,
    /* 4, init->backup: 备份组所在接口up，且备份组里的虚拟IP都不是接口上的真实IP */
    VRRP_IF_UP_WITH_VIRTUAL_IP,

    /* 5, master->init: 备份组删除了最后一个虚拟IP，且当前状态为master */
    VRRP_DEL_LAST_IP_MASTER,
    /* 6, master->init: 备份组删除了所有虚拟IP，且当前状态为master */
    VRRP_DEL_ALL_IP_MASTER,
    /* 7, master->init: 接口down，且当前状态为master */
    VRRP_DEL_IF_DOWN_MASTER,

    /* 8, master->backup: master被backup抢占 */
    VRRP_BE_PREEMPTED,

    /* 9 ,backup->init: 备份组删除了最后一个虚拟IP，且当前状态为backup */
    VRRP_DEL_LAST_IP_BACKUP,
    /* 10,backup->init: 备份组删除了所有虚拟IP，且当前状态为backup */
    VRRP_DEL_ALL_IP_BACKUP,
    /* 11,backup->init: 接口down，且当前状态为backup */
    VRRP_DEL_IF_DOWN_BACKUP,

    /* 12,backup->master: master主动退出工作状态，且当前backup的优先级高于master，此时立刻抢占 */
    VRRP_MASTER_QUIT_IMMEDIATE,
    /* 13,backup->master: backup检测到master超时从而升为master */
    VRRP_MASTER_UNUSABLE,
    /* 14,backup->master: backup检测到master超时，在配置delay的情况下，
       如果当前时刻距离上次收到master报文的时刻已经多于一个master通告间隔，则立刻升为master */
    VRRP_MASTER_UNUSABLE_DELAY,

    /* 15,backup->master: 监视的接口状态变化导致备份组优先级变化，从而由backup升为master */
    VRRP_TRACK_IF,
    /* 16,backup->master: 监视的BFD状态变化导致备份组优先级变化，从而由backup升为master */
    VRRP_TRACK_BFD,
    /* 17,backup->master: 监视的1AG状态变化导致备份组优先级变化，从而由backup升为master */
    VRRP_TRACK_1AG,
    /* 18,backup->master: 监视的3AH状态变化导致备份组优先级变化，从而由backup升为master */
    VRRP_TRACK_3AH
}VRRP_STATE_CHANGE_DIAG_E;

/* VRRP状态转变时通知用户的钩子函数原型
ULONG ulIfIndex     :接口索引
ULONG ulVRID        :备份组ID
ULONG ulChangeType  :状态转变类型
ULONG ulDiagnostic  :诊断字,表示状态转变的原因,参见VRRP_STATE_CHANGE_DIAG_E */
typedef VOID (*TCPIP_VRRP_NOTIFY_STATE)(ULONG ulIfIndex, ULONG ulVRID,
                                        ULONG ulChangeType, ULONG ulDiagnostic);

/* 状态变化过程 */
#define VRRP_TRANSITION_NO                      0
#define VRRP_TRANSITION_INITIALIZE_TO_BACKUP    1
#define VRRP_TRANSITION_INITIALIZE_TO_MASTER    2
#define VRRP_TRANSITION_BACKUP_TO_INITIALIZE    3
#define VRRP_TRANSITION_BACKUP_TO_MASTER        4
#define VRRP_TRANSITION_MASTER_TO_INITIALIZE    5
#define VRRP_TRANSITION_MASTER_TO_BACKUP        6

/*******************************************************************************
 * 数据结构定义:                                                               *
 *******************************************************************************/
/* VRRP报文统计信息结构 */
typedef struct tagTCPIP_VRRP_STATISTICS
{
    ULONG ulErrorSum;          /* 校验错误的总的次数,指该VRID下接收方向的异常报文个数总和,不仅仅包括下面列出的几类情况错误*/

    ULONG ulErrorCheckSum;     /* 校验和错误次数 */
    ULONG ulErrorTtlCheck;     /* TTL错误的次数 */
    ULONG ulErrorVersion;      /* 版本号错误次数 */
    ULONG ulErrorVirtualIpList;/* 虚拟地址列表匹配错误的次数 */
    ULONG ulErrorLength;       /* 报文长度错误的次数 */
    ULONG ulErrorAdvertiseTime;/* ADVERTISEMENT时间间隔错误的次数 */
    ULONG ulErrorAuth;         /* 认证错误的次数 */
    ULONG ulErrorInitialState;  /* 备份组为Initial状态收到的报文次数 */

    ULONG ulRcvAdvertisePkt;   /* 接收到的报文总和 */
    ULONG ulSndAdvertisePkt;   /* 发送到的报文总和 */
    ULONG ulRcvPriorityZeroPkt;/* 接收到的优先级为0报文总和 */
    ULONG ulSndPriorityZeroPkt;/* 发送到的优先级为0报文总和 */

    ULONG ulGlobalErrorVrid;   /* 统计接收的报文中VRID错误的报文个数,为全局统计值*/
}TCPIP_VRRP_STATISTICS_S;

/* VRRP详细配置信息 */
typedef struct tagTCPIP_VRRP_CONFIGINFO
{
    ULONG ulVrid;       /* 备份组ID */
    ULONG ulIfIndex;    /* 备份组所在接口索引 */
    ULONG ulState;      /* 备份组状态(init,backup,master) */

    ULONG ulIpAddressCount;         /* 虚地址个数 */
    ULONG ulIpAddressList[VRRP_VIRTUAL_IP_ADDRESS_MAX]; /* 虚地址列表 */

    UCHAR ucAdvertisementInterval;  /* master发送vrrp报文的时间间隔 */
    UCHAR ucPriorityConfig;         /* 配置的优先级 */
    UCHAR ucPriorityRun;            /* 生效的优先级 */

    UCHAR ucAuthenticationType;     /* 认证模式 */
    UCHAR ucAuthenticationKey[VRRP_AUTHENTICATION_KEY_LENGTH];  /* 认证pwd */

    UCHAR ucPreempt;            /* 是否可抢占 */
    UCHAR ucDelayValue;         /* 延迟时间 */
    UCHAR ucEnablePing;         /* 是否支持ping功能 */
    UCHAR ucEnableCheckTtl;     /* 是否检查接收报文的TTL */

    ULONG ulGratuitousArptime;  /* 发送免费arp的时间 */

    ULONG ulDiagnostic;         /* 诊断上一次VRRP状态变迁的原因,参见VRRP_STATE_CHANGE_DIAG_E */
}TCPIP_VRRP_CONFIGINFO_S;

/* 监视接口功能的数据结构*/
typedef struct tagTCPIP_VRRP_TRACKIF
{
    ULONG ulTrackIfIndex;      /* 被监视接口的索引 */
    LONG  lReduce;             /* 被监视的接口DOWN掉时，下降的优先级数额 */
    UCHAR ucTrackedIfnetState; /* 被监视接口的状态 */
    UCHAR ucReserve[3];
}TCPIP_VRRP_TRACKIF_S;

/* 监视BFD功能的数据结构*/
typedef struct tagTCPIP_VRRP_TRACKBFD
{
    ULONG ulBfdSessionId;       /* BFD会话本地唯一标识符 */
    ULONG ulVrfIndex;           /* VRF索引 */
    LONG  lReduce;              /* 下降的优先级数额 */
    UCHAR ucVrrpBfdState;       /* 被监视BDF 会话的状态*/
    UCHAR ucReserve[3];
}TCPIP_VRRP_TRACKBFD_S;

/* 监视1AG功能的数据结构*/
typedef struct tagTCPIP_VRRP_TRACK1AG
{
    UCHAR szMdName[VRRP_MAX_MDNAME_LEN + 1];    /* Md名字 */
    UCHAR szMaName[VRRP_MAX_MANAME_LEN + 1];    /* Ma名字 */
    LONG  lReduce;                              /* 下降的优先级数额 */
    USHORT usRmepId;                            /* rmep id */
    UCHAR ucVrrp1agState;                       /* 监视的rmep是否存在CC LOST告警或Interface down告警 */
    UCHAR ucReserve;
}TCPIP_VRRP_TRACK1AG_S;

/* 监视3AH功能的数据结构*/
typedef struct tagTCPIP_VRRP_TRACK3AH
{
    ULONG ul3ahIfIndex;         /* 监视的3ah接口索引 */
    LONG  lReduce;              /* 下降的优先级数额 */
    UCHAR ucVrrp3ahState;       /* 被监视3ah的状态*/
    UCHAR ucReserve[3];
}TCPIP_VRRP_TRACK3AH_S;


/*******************************************************************************
 * 注册适配函数原型:                                                           *
 *******************************************************************************/
typedef ULONG (*VRRP_GETBFDSESSIONSTATE)(ULONG ulSessionID, ULONG ulVrfIndex, ULONG *pstState);

/*******************************************************************************
 * API原型:                                                                    *
 *******************************************************************************/
/*******************************************************************************
*    Func Name: TCPIP_VRRP_CreateStandby
* Date Created: 2009-01-17
*       Author: L00105073,L00111779
*  Description: 在指定接口上创建备份组
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulVrid:备份组id
*       Output: 
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-17   L00105073,L00111779                             Create
*
*******************************************************************************/
extern ULONG TCPIP_VRRP_CreateStandby(ULONG ulIfIndex, ULONG ulVrid);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_DelStandby
* Date Created: 2009-01-17
*       Author: L00105073,L00111779
*  Description: 删除备份组
*        Input: ULONG ulVrid: 备份组ID
*       Output: 
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-17   L00105073,L00111779                             Create
*
*******************************************************************************/
extern ULONG TCPIP_VRRP_DelStandby(ULONG ulVrid);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_AddVirtualIP
* Date Created: 2009-01-19
*       Author: zhongweihua/zhangchi(00104207/00142640)
*  Description: 增加指定备份组的地址
*        Input: ULONG ulVrid:  备份组ID
*               ULONG ulIpaddr:地址(主机序)
*       Output: 
*       Return: 成功返回VRRP_OK，失败返回错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-19   zhongweihua/zhangchi(00104207/00142640)  Create
*
*******************************************************************************/
extern ULONG TCPIP_VRRP_AddVirtualIP(ULONG ulVrid, ULONG ulIpaddr);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_DelVirtualIP
* Date Created: 2009-01-10
*       Author: zhongweihua/zhangchi(00104207/00142640)
*  Description: 删除指定备份组的地址
*        Input: ULONG ulVrid:  备份组ID
*               ULONG ulIpaddr:地址(主机序)
*       Output: 
*       Return: 成功返回VRRP_OK，失败返回错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-10   zhongweihua/zhangchi(00104207/00142640)        Create
*
*******************************************************************************/
extern ULONG TCPIP_VRRP_DelVirtualIP(ULONG ulVrid, ULONG ulIpaddr);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_DelAllVirtualIP
* Date Created: 2009-01-10
*       Author: zhongweihua/zhangchi(00104207/00142640)
*  Description: 删除备份组的所有地址
*        Input: ULONG ulVrid:备份组ID
*       Output: 
*       Return: 成功返回VRRP_OK，失败返回错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-10   zhongweihua/zhangchi(00104207/00142640)        Create
*
*******************************************************************************/
extern ULONG TCPIP_VRRP_DelAllVirtualIP(ULONG ulVrid);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_EnablePing
* Date Created: 2009-02-11
*       Author: zhongweihua/zhangchi(00104207/00142640)
*  Description: 设置Master是否响应Ping报文
*        Input: ULONG ulVrid:   备份组ID
*               ULONG ulSetYes: VRRP_TRUE:使能，VRRP_FALSE:去使能；默认VRRP_FALSE
*       Output: 
*       Return: 成功返回VRRP_OK，失败返回错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-11   zhongweihua/zhangchi(00104207/00142640)  Create
*
*******************************************************************************/
extern ULONG TCPIP_VRRP_EnablePing(ULONG ulVrid, ULONG ulSetYes);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_SetAdvertiseTimer
* Date Created: 2009-01-21
*       Author: L00105073,L00111779
*  Description: 设置Master发送VRRP报文的间隔时间
*        Input: ULONG ulVrid:  备份组ID
*               ULONG ulTimer: 发送时间间隔，范围1~255s，默认1s
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-21   L00105073,L00111779                             Create
*
*******************************************************************************/
extern ULONG TCPIP_VRRP_SetAdvertiseTimer(ULONG ulVrid, ULONG ulTimer);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_SetPriority
* Date Created: 2009-01-22
*       Author: L00105073,L00111779
*  Description: 配置备份组的优先级
*        Input: ULONG ulVrid:备份组id
*               ULONG ulPriority:要配置的优先级
*       Output: 
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-22   L00105073,L00111779                             Create
*
*******************************************************************************/
extern ULONG TCPIP_VRRP_SetPriority(ULONG ulVrid, ULONG ulPriority);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_SetPreemptDelay
* Date Created: 2009-01-22
*       Author: L00105073,L00111779
*  Description: 配置抢占延迟时间
*        Input: ULONG ulVrid:备份组id
*               ULONG ulDelay:延迟时间
*       Output: 
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-22   L00105073,L00111779                             Create
*
*******************************************************************************/
extern ULONG TCPIP_VRRP_SetPreemptDelay(ULONG ulVrid, ULONG ulDelay);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_EnablePreempt
* Date Created: 2009-01-22
*       Author: L00105073,L00111779
*  Description: 设置备份组中路由器是否采用抢占方式
*        Input: ULONG ulVrid:备份组id
*               ULONG ulSetYes:是否采用抢占方式，1表示抢占，0表示不抢占
*               默认值为可抢占,如果设置了不抢占，内部自动把delay时间清零
*       Output: 
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-22   L00105073,L00111779                             Create
*
*******************************************************************************/
extern ULONG TCPIP_VRRP_EnablePreempt(ULONG ulVrid, ULONG ulSetYes);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_EnableCheckTTL
* Date Created: 2009-01-21
*       Author: L00105073,L00111779
*  Description: 设置是否检测VRRP报文的TTL值
*        Input: ULONG ulVrid: 备份组ID
*               ULONG ulSetYes: True/False
*       Output: 
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-21   L00105073,L00111779                             Create
*
*******************************************************************************/
extern ULONG TCPIP_VRRP_EnableCheckTTL(ULONG ulVrid, ULONG ulSetYes);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_SetGratuitousArpTimer
* Date Created: 2009-01-10
*       Author: zhongweihua/zhangchi(00104207/00142640)
*  Description: 设置Master发送免费ARP报文的时间间隔
*        Input: ULONG ulTimer:时间间隔范围30~1200s，默认300s，
*       Output: 
*       Return: 成功返回VRRP_OK，失败返回错误码
*      Caution: 0为不定时发送免费ARP
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-10   zhongweihua/zhangchi(00104207/00142640)    Create
*
*******************************************************************************/
extern ULONG TCPIP_VRRP_SetGratuitousArpTimer(ULONG ulTimer);


/*******************************************************************************
*    Func Name: TCPIP_VRRP_SetAuthMode
* Date Created: 2009-01-21
*       Author: L00105073,L00111779
*  Description: 设置指定接口上的所以VRRP备份组的简单认证认证字
*        Input: ULONG ulVrid:VRID
*               ULONG ulMode:0表示不做认证(默认),1表示简单认证
*               UCHAR pszKey:长度不超过8的字符串，如果ulMode为0,则不处理ucKey
*       Output: 
*       Return: 成功返回VRRP_OK，失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-21   L00105073,L00111779                             Create
*
*******************************************************************************/
extern ULONG TCPIP_VRRP_SetAuthMode(ULONG ulVrid, ULONG ulMode, UCHAR* pszKey);


/*******************************************************************************
*    Func Name: TCPIP_VRRP_TrackIF
* Date Created: 2009-02-02
*       Author: L00105073,L00111779
*  Description: 设置/取消备份组要监视的接口
*        Input: ULONG ulVrid:备份组ID
*               ULONG ulTrackIfIndex:备份组要监视的接口索引
*               LONG lReduce:当被监视的接口down时减少的运行优先级，有效值1~255
*               ULONG ulSetYes:添加或删除监视接口 1 设置 0 取消
*       Output: 
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   L00105073,L00111779                          Create
*
*******************************************************************************/
extern ULONG TCPIP_VRRP_TrackIF(ULONG ulVrid, ULONG ulTrackIfIndex, LONG lReduce, ULONG ulSetYes);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_TrackBFD
* Date Created: 2009-01-10
*       Author: wuhailan/gexianjun
*  Description: 配置VRRP监听BFD会话
*        Input: ULONG ulVrid:VRRP备份组号
*               ULONG ulBfdSession:被监视的BFD会话
*               ULONG ulVrfIndex:  VRF索引
*               LONG lReduce:设置当被监视的BFD会话变为Down时，优先级增加的数值。取值范围是1～255
*               ULONG ulSetYes:1 设置监听  0 取消监听
*       Output:
*       Return: 成功VRRP_OK，其他返回错误码
*      Caution: 当VRF组件未注册时，VRF索引必须传入0，否则作为错误参数处理；
*               当BFD会话ID为0且设置为取消监听时，即为删除所有的BFD监听功能
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-10   wuhailan/gexianjun      Create
*
*******************************************************************************/
extern ULONG TCPIP_VRRP_TrackBFD(ULONG ulVrid, ULONG ulBfdSession, ULONG ulVrfIndex, LONG lReduce, ULONG ulSetYes);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_Track1AG
* Date Created: 2009-01-10
*       Author: L00105073,L00111779
*  Description: 配置VRRP监听1AG会话
*        Input: ULONG ulVrid:VRRP备份组号
*               UCHAR* szMdName:MD名字
*               UCHAR* szMaName:MA名字
*               USHORT usRmepid:rmep id
*               LONG lReduce:设置当被监视的1AG会话产生告警时，优先级降低的数值。取值范围是1～255
*               ULONG ulSetYes:1 设置监听  0 取消监听
*       Output:
*       Return: 成功VRRP_OK，其他返回错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                         DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-10   L00105073,L00111779          Create
*
*******************************************************************************/
extern ULONG TCPIP_VRRP_Track1AG(ULONG ulVrid, UCHAR* szMdName, UCHAR* szMaName, USHORT usRmepid,
                                        LONG lReduce, ULONG ulSetYes);


/*******************************************************************************
*    Func Name: TCPIP_VRRP_Track3AH
* Date Created: 2009-01-10
*       Author: L00105073,L00111779
*  Description: 配置VRRP监听3AH会话
*        Input: ULONG ulVrid:VRRP备份组号
*               ULONG ulTrackIfIndex:被监视的使能3AH的接口索引
*               LONG lReduce:设置当被监视的3AH会话变为非sendany状态时，优先级减少的数值。取值范围是1～255
*               ULONG ulSetYes:1 设置监听  0 取消监听
*       Output:
*       Return: 成功VRRP_OK，其他返回错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-10   L00105073,L00111779         Create
*
*******************************************************************************/
extern ULONG TCPIP_VRRP_Track3AH(ULONG ulVrid, ULONG ulTrackIfIndex, LONG lReduce, ULONG ulSetYes);


/*******************************************************************************
*    Func Name: TCPIP_VRRP_GetConfigInfo
* Date Created: 2009-01-20
*       Author: L00105073,L00111779
*  Description: 获取备份组配置信息
*        Input: ULONG ulVrid:备份组id
*       Output: TCPIP_VRRP_CONFIGINFO_S *pstVrrpConfigInfo:配置信息
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-20   L00105073,L00111779                             Create
*
*******************************************************************************/
extern ULONG TCPIP_VRRP_GetConfigInfo(ULONG ulVrid, TCPIP_VRRP_CONFIGINFO_S *pstVrrpConfigInfo);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_ShowConfigInfo
* Date Created: 2009-01-20
*       Author: L00105073,L00111779
*  Description: 显示备份组配置信息
*        Input: ULONG ulVrid:备份组id
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-20   L00105073,L00111779                             Create
*
*******************************************************************************/
extern VOID TCPIP_VRRP_ShowConfigInfo(ULONG ulVrid);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_ShowAllInfo
* Date Created: 2009-01-20
*       Author: L00105073,L00111779
*  Description: 显示所有备份组信息
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-20   L00105073,L00111779                             Create
*
*******************************************************************************/
extern VOID TCPIP_VRRP_ShowAllInfo(VOID);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_GetTrackIFInfo
* Date Created: 2009-02-05
*       Author: zhongweihua/zhangchi(00104207/00142640)
*  Description: 获取配置的VRRP基于接口监视的功能信息
*        Input: ULONG ulVrid:VRRP备份组号
*       Output: TCPIP_VRRP_TRACKIF_S stVrrpTrackIfInfo[VRRP_TRACK_MAX]:配置的VRRP基于接口监视的功能信息
*               ULONG *pulCount:返回的实际基于接口监听的信息的条数
*       Return: 成功VRRP_OK，其他返回错误码
*      Caution: 传入内存stVrrpTrackIfInfo的初始化由用户保证
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-05   zhongweihua/zhangchi(00104207/00142640)  Create
*
*******************************************************************************/
extern ULONG TCPIP_VRRP_GetTrackIFInfo(ULONG ulVrid, TCPIP_VRRP_TRACKIF_S stVrrpTrackIfInfo[VRRP_TRACK_MAX], ULONG *pulCount);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_ShowTrackIFInfo
* Date Created: 2009-01-20
*       Author: wuhailan
*  Description: 显示配置的VRRP基于接口监视的功能信息
*        Input: ULONG ulVrid:VRRP备份组号
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-20   wuhailan                Create
*
*******************************************************************************/
extern VOID TCPIP_VRRP_ShowTrackIFInfo(ULONG ulVrid);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_GetTrackBFDInfo
* Date Created: 2009-02-06
*       Author: zhongweihua/zhangchi(00104207/00142640)
*  Description: 获取配置的VRRP基于BFD会话监视的功能信息
*        Input: ULONG ulVrid:VRRP备份组号
*       Output: TCPIP_VRRP_TRACKBFD_S stVrrpTrackBfdInfo[VRRP_TRACK_MAX]:配置的VRRP基于BFD会话监视的功能信息
*               ULONG *pulCount:返回的实际基于BFD监听的信息的条数
*       Return: 成功VRRP_OK，其他返回错误码
*      Caution: 传入内存stVrrpTrackBfdInfo的初始化由用户保证
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-06   zhongweihua/zhangchi(00104207/00142640)   Create
*
*******************************************************************************/
extern ULONG TCPIP_VRRP_GetTrackBFDInfo(ULONG ulVrid, TCPIP_VRRP_TRACKBFD_S stVrrpTrackBfdInfo[VRRP_TRACK_MAX], ULONG *pulCount);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_ShowTrackBFDInfo
* Date Created: 2009-02-06
*       Author: zhongweihua/zhangchi(00104207/00142640)
*  Description: 显示配置的VRRP基于BFD会话监视的功能信息
*        Input: ULONG ulVrid:VRRP备份组号
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-20   zhongweihua/zhangchi(00104207/00142640)   Create
*
*******************************************************************************/
extern VOID TCPIP_VRRP_ShowTrackBFDInfo(ULONG ulVrid);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_GetTrack1AGInfo
* Date Created: 2009-02-05
*       Author: zhongweihua/zhangchi(00104207/00142640)
*  Description: 获取配置的VRRP基于1AG监视的功能信息
*        Input: ULONG ulVrid:VRRP备份组号
*       Output: TCPIP_VRRP_TRACK1AG_S stVrrpTrack1agInfo[VRRP_TRACK_MAX]:配置的VRRP基于1AG监视的功能信息
*               ULONG *pulCount:返回的实际基于1AG监听的信息的条数
*       Return: 成功VRRP_OK，其他返回错误码
*      Caution: 传入内存stVrrpTrack1agInfo的初始化由用户保证
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-05   zhongweihua/zhangchi(00104207/00142640)   Create
*
*******************************************************************************/
extern ULONG TCPIP_VRRP_GetTrack1AGInfo(ULONG ulVrid, TCPIP_VRRP_TRACK1AG_S stVrrpTrack1agInfo[VRRP_TRACK_MAX], ULONG *pulCount);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_ShowTrack1AGInfo
* Date Created: 2009-02-05
*       Author: zhongweihua/zhangchi(00104207/00142640)
*  Description: 显示配置的VRRP基于1AG监视的功能信息
*        Input: ULONG ulVrid: 备份组ID
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-05   zhongweihua/zhangchi(00104207/00142640)   Create
*
*******************************************************************************/
extern VOID TCPIP_VRRP_ShowTrack1AGInfo(ULONG ulVrid);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_GetTrack3AHInfo
* Date Created: 2009-02-06
*       Author: zhongweihua/zhangchi(00104207/00142640)
*  Description: 获取配置的VRRP基于3AH监视的功能信息
*        Input: ULONG ulVrid:VRRP备份组号
*       Output: TCPIP_VRRP_TRACK3AH_S stVrrpTrack3ahInfo[VRRP_TRACK_MAX]:配置的VRRP基于3AH监视的功能信息
*               ULONG *pulCount:返回的实际基于3AH监听的信息的条数
*       Return: 成功VRRP_OK，其他返回错误码
*      Caution: 传入内存stVrrpTrack3ahInfo的初始化由用户保证
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-06   zhongweihua/zhangchi(00104207/00142640)   Create
*
*******************************************************************************/
extern ULONG TCPIP_VRRP_GetTrack3AHInfo(ULONG ulVrid, TCPIP_VRRP_TRACK3AH_S stVrrpTrack3ahInfo[VRRP_TRACK_MAX], ULONG *pulCount);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_ShowTrack3AHInfo
* Date Created: 2009-02-06
*       Author: zhongweihua/zhangchi(00104207/00142640)
*  Description: 显示配置的VRRP基于3AH监视的功能信息
*        Input: ULONG ulVrid:VRRP备份组号
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-06   zhongweihua/zhangchi(00104207/00142640)   Create
*
*******************************************************************************/
extern VOID TCPIP_VRRP_ShowTrack3AHInfo(ULONG ulVrid);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_GetVridlistByIfIndex
* Date Created: 2009-01-20
*       Author: L00105073,L00111779
*  Description: 获取接口上的备份组列表
*        Input: ULONG ulIfIndex:接口索引
*       Output: ULONG* pulVridCount:接口下含有的备份组个数
*               UCHAR ucVridlist[VRRP_MAX_ROUTERNUM_PERPORT]:备份组列表
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-20   L00105073,L00111779                             Create
*
*******************************************************************************/
extern ULONG TCPIP_VRRP_GetVridlistByIfIndex(ULONG ulIfIndex, ULONG* pulVridCount,
                                                            UCHAR ucVridlist[VRRP_MAX_ROUTERNUM_PERPORT]);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_ShowVridlist
* Date Created: 2009-01-20
*       Author: L00105073,L00111779
*  Description: 显示接口上的备份组列表
*        Input: UCHAR* pszIfName:接口名
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-20   L00105073,L00111779                             Create
*
*******************************************************************************/
extern VOID TCPIP_VRRP_ShowVridlist(UCHAR* pszIfName);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_ResetStatistic
* Date Created: 2009-01-20
*       Author: wuhailan/zhengsenhuo
*  Description: 初始化统计信息,包括将全局的VRID错误统计信息清0
*        Input: ULONG ulVrid:备份组id
*       Output: 
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-20   wuhailan/zhengsenhuo                             Create
*
*******************************************************************************/
extern ULONG TCPIP_VRRP_ResetStatistic(ULONG ulVrid);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_GetStatistic
* Date Created: 2009-01-20
*       Author: wuhailan/zhengsenhuo
*  Description: 获取指定VRID的统计信息,包括接收的报文中VRID错误的报文个数
*        Input: ULONG ulVrid:备份组VRID
*       Output: TCPIP_VRRP_STATISTICS_S *pstVrrpStatics: 返回的统计信息,包括接收的报文中VRID错误的报文个数
*       Return: 成功VRRP_OK,其他返回错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-20   wuhailan/zhengsenhuo         Create
*
*******************************************************************************/
extern ULONG TCPIP_VRRP_GetStatistic(ULONG ulVrid, TCPIP_VRRP_STATISTICS_S *pstVrrpStatics);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_ShowStatistic
* Date Created: 2009-01-20
*       Author: L00105073,L00111779
*  Description: 显示备份组统计信息
*        Input: ULONG ulVrid:备份组id
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-20   L00105073,L00111779                             Create
*
*******************************************************************************/
extern VOID TCPIP_VRRP_ShowStatistic(ULONG ulVrid);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_SetDebug
* Date Created: 2009-01-20
*       Author: wuhailan
*  Description: VRRP调试开关设置接口
*        Input: ULONG ulVrid:备份组ID
*               ULONG ulType:设置的调试类型
*               VRRP_DEBUG_PACKET,报文类调试开关
*               VRRP_DEBUG_ERROR,报文错误类调试开关
*               VRRP_DEBUG_STATE,状态机类调试开关
*               VRRP_DEBUG_EVENT,错误事件类调试开关
*               VRRP_DEBUG_ALL,打开全部类型调试开关
*               ULONG ulSetYes:调试开关，1表示打开，0表示关闭
*       Output: 
*       Return: 成功返回VRRP_OK,失败返回错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-20   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_VRRP_SetDebug(ULONG ulVrid, ULONG ulType, ULONG ulSetYes);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_ShowDebug
* Date Created: 2009-02-03
*       Author: wuhailan
*  Description: 显示VRRP的调试开关信息
*        Input: ULONG ulVrid:VRID
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-03   wuhailan                Create
*
*******************************************************************************/
VOID TCPIP_VRRP_ShowDebug(ULONG ulVrid);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_RegHookNotifyState
* Date Created: 2010-01-24
*       Author: zengshaoyang62531
*  Description: 注册VRRP状态变迁对外通告的钩子函数
*        Input: TCPIP_VRRP_NOTIFY_STATE pfFunc:钩子函数
*       Output: 
*       Return: VRRP_OK
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-01-24   zengshaoyang62531         Create
*
*******************************************************************************/
extern ULONG TCPIP_VRRP_RegHookNotifyState(TCPIP_VRRP_NOTIFY_STATE pfFunc);


#ifdef __cplusplus
}
#endif      /* end of __cplusplus   */

#endif      /* end of _VRRP_API_H_      */


