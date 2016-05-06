/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              poes_api.h
*
*  Project Code: VISPV100R007
*   Module Name: POES
*  Date Created: 2008-03-17
*        Author: luowentong105073
*   Description: 用户API
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-03-17   luowentong105073        Create
*
*******************************************************************************/
#ifndef __POES_API_H__
#define __POES_API_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define POES_MAC_LEN 6                  /* physical地址长度 */
#define POES_ACNAME_MAX_LEN 58          /* ACName字符数组大小,包括'\0' */
#define POES_SERVICENAME_MAX_LEN 128    /* Service Name字符数组大小,包括'\0' */

#ifndef IF_MAX_INTERFACE_NAME_LEN
#define IF_MAX_INTERFACE_NAME_LEN 47       /* 最大接口名长度 */
#endif

/* POES模块的错误码 */
enum enPoesErrorCode
{
    POES_OK = 0,
    POES_ERR,
    POES_PARAM_ERR,                 /* 2、输入参数不合法 */
    POES_IF_NULL,                   /* 3、根据接口索引获取接口指针为空 */
    POES_IF_TYPE_ERR,               /* 4、接口类型错误 */
    POES_ISNOT_SERVER,              /* 5、接口没有使能PPPoE Server */
    POES_IS_SERVER,                 /* 6、以太接口已使能PPPoE Server */
    POES_IS_CLIENT,                 /* 7、以太接口已使能PPPoE Client */
    POES_ETH_IS_TRUNKPORT,          /* 8、以太接口是Trunk接口的成员端口 */
    POES_VT_ISNOT_USABLED,          /* 9、VT接口不可用 */
    POES_MEM_MALLOC_FAILED,         /* 10、分配内存失败 */    
    POES_HAVE_NO_SESSION,           /* 11、以太接口没有Session */
    POES_SESSIONID_ERR,             /* 12、输入Session ID错误 */
    POES_GET_SESSION_INFO_FAILED,   /* 13、输出Session信息失败（本次session输出无效）*/
    POES_SERVICENAME_TOOLONG,       /* 14、输入字符串太长 */
    POES_GET_END,                   /* 15、获取waitlist节点结束 */
    POES_HA_IS_SMOOTHING,           /* 16、HA正在手动倒换或平滑处理*/
    POES_HAVE_NO_HISMAC,            /* 17、没有该physical地址 */
    POES_SERVICE_NAME_ERR,          /* 18、PADR中service name 错误*/
    POES_NOTINIT,                   /* 19、POES模块未初始化 */    
    POES_IS_VIRTUAL_PORT,           /* 20, 三维虚拟接口 */   
    POES_CTRL_BLOCK_NULL,           /* 21, POES控制块为NULL */
    POES_HIS_MAC_NULL,              /* 22, his mac为空 */
    POES_MAX_ERR                    /* */
};



/* 调试信息开关数据结构 */
typedef struct tagPoesDebugInfo
{
    UCHAR ucDbgPoesData;    /* PPPOE模块数据报文调试开关 */
    UCHAR ucDbgPoesNego;    /* PPPOE模块协商报文调试开关 */
    UCHAR ucDbgPoesEvents;  /* PPPOE模块事件调试开关 */
    UCHAR ucDbgPoesErrors;  /* PPPOE模块协议及代码错误调试开关 */
} POES_DEBUG_INFO_S;

/*POES接口配置信息*/
typedef struct tagPoesIfCfgInfo
{
    ULONG ulEthIfIndex;     /* ETH接口索引值 */
    ULONG ulVTIfIndex;      /* 绑定的VT接口索引值 */
    UCHAR szServiceName[POES_SERVICENAME_MAX_LEN];  /* Service name */
} POES_IF_CFG_INFO_S;

/*Session的基本信息*/
typedef struct tagPoesSessionInfo
{
    USHORT usSessionId;         /* session id */
    USHORT usSessionState;      /* session 状态 */
    ULONG  ulVTIfIndex;         /* VT接口索引 */
    UCHAR  szVAIfName[IF_MAX_INTERFACE_NAME_LEN + 1];  /* VA子通道名称 */
    UCHAR  aucLocalMac[POES_MAC_LEN];   /* 本端physical地址 */
    UCHAR  aucRemoteMac[POES_MAC_LEN];  /* 远端physical地址 */
} POES_SESSION_INFO_S;

/*Session的报文统计信息*/
typedef struct tagPoesSesPktStatInfo
{
    USHORT usSessionId;     /* session id */
    UCHAR  aucLocalMac[POES_MAC_LEN];   /* 本端physical地址 */
    UCHAR  aucRemoteMac[POES_MAC_LEN];  /* 远端physical地址 */
    UCHAR  ucPadding[2];    /* 填充字段 */
    ULONG  ulInPackets;     /* 收到的包数 */
    ULONG  ulInOctets;      /* 收到的字节数 */
    ULONG  ulInDiscards;    /* 接收时丢弃的包数 */
    ULONG  ulOutPackets;    /* 发送的包数 */
    ULONG  ulOutOctets;     /* 发送的字节数 */
    ULONG  ulOutDiscards;   /* 发送时丢弃的包数 */
} POES_SES_PKT_STAT_INFO_S;

/*以太接口的Session统计信息*/
typedef struct tagPoesStatInfo
{
    ULONG ulOurMacCurtSessions;     /* 以太接口当前Session数目 */
    ULONG ulCurrentEstablishRate;   /* 以太接口当前Seesion建立速度 */
    ULONG ulBurstEstablishRate;     /* 以太接口最高Session建立速度 */
    ULONG ulFailedCount;            /* 建立Session失败次数 */
} POES_SESSION_STAT_INFO_S;

/*POES系统配置信息*/
typedef struct tagPoesSystemCfgInfo
{
    CHAR   szAcName[POES_ACNAME_MAX_LEN];/* AC NAME */
    USHORT usSessionNum;       /* 当前全局session数 */
    USHORT usMaxSesLimit;       /* 全局Session数限制 */
    USHORT usOurMacMaxSesLimit; /* 本端MAC Session数限制 */
    USHORT usHisMacMaxSesLimit;    /* 对端MAC Session数限制 */
    UCHAR  ucPadding[2];    /* 填充字段 */
} POES_SYS_CFG_INFO_S;

/* 统计信息类型 */
enum enumPoesStatType
{
    STAT_ALL = 0,
    STAT_PKT,
    STAT_SES
};


/* 调试信息类型 */
enum enumPoesDbgType
{
    DBG_ALL = 0,
    DBG_DATAPKT,
    DBG_NEGOPKT,
    DBG_EVENTS,
    DBG_ERRORS
};



typedef VOID (*GetACName_HOOK_FUNC)(UCHAR* pszAcName);

/*******************************************************************************
*    Func Name: TCPIP_ClearPoesStatInfo
*  Description: 清除报文统计计数和以太接口下的Session统计计数
*        Input: ULONG ulEthIfIndex:以太接口的索引值,如果为0清除所有接口的统计信息
*               ULONG ulType:清除的类型
*               0－所有统计信息，1－报文统计计数，2－session统计信息,其他无效
*       Output: 
*       Return: VOS_OK: 处理成功
*               POES_PARAM_ERR: 输入参数不合法
*               POES_IF_NULL: 根据接口索引获取接口指针为空
*               POES_ISNOT_SERVER: 以太接口未使能PPPoE Server
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_ClearPoesStatInfo(ULONG ulEthIfIndex, ULONG ulType);
/*******************************************************************************
*    Func Name: TCPIP_DisablePoes
*  Description: 在以太接口去使能PPPoE Server功能
*        Input: ULONG ulEthIfIndex:以太接口索引
*       Output: 
*       Return: VOS_OK: 处理成功
*               POES_IF_NULL: 根据接口索引获取接口指针为空
*               POES_ISNOT_SERVER: 接口没有使能PPPoE Server
*               POES_HA_IS_SMOOTHING: HA正在手动倒换或平滑处理
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_DisablePoes (ULONG ulEthIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_EnablePoes
*  Description: 在以太接口使能PPPoE Server功能
*        Input: ULONG ulEthIfIndex:以太接口索引
*               ULONG ulVTIfIndex:VT接口索引
*       Output: 
*       Return: VOS_OK: 处理成功
*               POES_IF_NULL: 根据接口索引获取接口指针为空
*               POES_IF_TYPE_ERR: 接口类型错误
*               POES_IS_SERVER: 以太接口已使能PPPoE Server
*               POES_IS_CLIENT: 以太接口已使能PPPoE Client
*               POES_ETH_IS_TRUNKPORT: 以太接口是Trunk接口的成员端口
*               POES_VT_ISNOT_USABLED: VT接口不可用
*               POES_MEM_MALLOC_FAILED: 分配内存失败
*               POES_HA_IS_SMOOTHING: HA正在手动倒换或平滑处理
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_EnablePoes(ULONG ulEthIfIndex, ULONG ulVTIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_GetPoesDbgSwitch
*  Description: 获取调试信息开关
*        Input: ULONG ulEthIfIndex:以太接口索引(为0表示输出全局调试信息开关)
*       Output: POES_DEBUG_INFO_S *pstDbgInfo:调试信息开关 开关取值 0－关，1－开
*       Return: VOS_OK: 处理成功
*               POES_PARAM_ERR: 输入参数不合法
*               POES_IF_NULL: 根据接口索引获取接口指针为空
*               POES_ISNOT_SERVER: 以太接口未使能PPPoE Server
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPoesDbgSwitch(ULONG ulEthIfIndex, POES_DEBUG_INFO_S *pstDbgInfo);
/*******************************************************************************
*    Func Name: TCPIP_GetPoesHADbg
*  Description: Get poes ha debug switch
*        Input: None
*       Output: ULONG *pulRet: Poes ha debug switch
*       Return: VOS_OK(0): Success, VOS_ERR(1): Fail
*      Caution: None
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPoesHADbg(ULONG *pulRet);
/*******************************************************************************
*    Func Name: TCPIP_GetPoesHisMacSessions
*  Description: 获取对端mac的session数
*        Input: UCHAR *pucHisMac: 对端physical地址
*       Output: USHORT *pusSesNum: 输出对端mac的session数,失败则输出0xffff
*       Return: POES_PARAM_ERR: 参数错误
*               POES_HAVE_NO_HISMAC: 没有该physical地址
*               VOS_OK: 获取成功
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPoesHisMacSessions(UCHAR *pucHisMac, USHORT *pusSesNum);
/*******************************************************************************
*    Func Name: TCPIP_GetPoesIfCfgInfo
*  Description: 获取以太接口的PPPoE Server配置信息，包括：以太接口索引，绑定的VT接口索
*               引，Service Name（最大127个字符）。
*        Input: ULONG ulEthIfIndex:以太口的索引
*       Output: POES_IF_CFG_INFO_S *pstIfCfgInfo:获取的PPPoE Server配置信息
*       Return: VOS_OK: 处理成功
*               POES_PARAM_ERR: 输入参数不合法
*               POES_IF_NULL: 根据接口索引获取接口指针为空
*               POES_ISNOT_SERVER: 以太接口未使能PPPoE Server
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPoesIfCfgInfo(ULONG ulEthIfIndex, POES_IF_CFG_INFO_S *pstIfCfgInfo);
/*******************************************************************************
*    Func Name: TCPIP_GetPoesSesInfo
*  Description: 按以太接口获取Session基本信息
*        Input: ULONG ulEthIfIndex:以太接口索引
*               USHORT *pusSessionID:Session ID(为0表示输出第一个Session)
*       Output: USHORT *pusSessionID:下一个可输出Session的ID(为0xFFFF表示再没有Session可输出)
*               POES_SESSION_INFO_S *pstSesInfo:输出Session基本信息
*       Return: VOS_OK: 处理成功
*               POES_PARAM_ERR: 输入参数不合法
*               POES_IF_NULL: 根据接口索引获取接口指针为空
*               POES_ISNOT_SERVER: 以太接口未使能PPPoE Server
*               POES_HAVE_NO_SESSION: 以太接口没有Session
*               POES_SESSIONID_ERR: 输入Session ID为0xFFFF，ID非法
*               POES_GET_SESSION_INFO_FAILED: 输出Session信息失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPoesSesInfo(ULONG ulEthIfIndex, USHORT *pusSessionID, POES_SESSION_INFO_S *pstSesInfo);
/*******************************************************************************
*    Func Name: TCPIP_GetPoesSesPktStatInfo
*  Description: 按以太接口获取报文统计信息
*        Input: ULONG ulEthIfIndex:以太接口索引
*               USHORT *pusSessionID: Session ID(为0表示输出第一个Session)
*       Output: USHORT *pusSessionID:下一个可输出Session的ID(为0xFFFF表示没有Session可输出)
*               POES_SES_PKT_STAT_INFO_S *pstPktStatInfo: 输出报文统计信息
*       Return: VOS_OK: 处理成功
*               POES_PARAM_ERR: 输入参数不合法
*               POES_IF_NULL: 根据接口索引获取接口指针为空
*               POES_ISNOT_SERVER: 以太接口未使能PPPoE Server
*               POES_HAVE_NO_SESSION: 以太接口没有Session
*               POES_SESSIONID_ERR: 输入Session ID为0xFFFF，ID非法
*               POES_GET_SESSION_INFO_FAILED: 输出Session信息失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPoesSesPktStatInfo(ULONG ulEthIfIndex, USHORT *pusSessionID,
                                         POES_SES_PKT_STAT_INFO_S * pstPktStatInfo);
/*******************************************************************************
*    Func Name: TCPIP_GetPoesSesStatInfo
*  Description: 根据以太接口获取Session统计信息:
*               以太接口下的Session 数，当前Session建立速率，最高Session建立速率，Session建立失败次数
*        Input: ULONG ulEthIfIndex: 以太接口的索引值
*       Output: POES_SESSION_STAT_INFO_S *pstSesStatInfo:获取的统计信息
*       Return: VOS_OK: 处理成功
*               POES_PARAM_ERR: 输入参数不合法
*               POES_IF_NULL: 根据接口索引获取接口指针为空
*               POES_ISNOT_SERVER: 以太接口未使能PPPoE Server
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPoesSesStatInfo(ULONG ulEthIfIndex, POES_SESSION_STAT_INFO_S *pstSesStatInfo);
/*******************************************************************************
*    Func Name: TCPIP_GetPoesSysCfgInfo
*  Description: 获取全局的PPPoE Server配置信息，包括：AC Name（最大57个字符），全局Session数限制
*               本端MAC Session数限制，对端MAC Session数限制
*        Input: 
*       Output: POES_SYS_CFG_INFO_S *pstSysCfgInfo  记录获取的配置信息
*       Return: VOS_OK: 处理成功
*               POES_PARAM_ERR: 输入参数不合法
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPoesSysCfgInfo(POES_SYS_CFG_INFO_S *pstSysCfgInfo);
/*******************************************************************************
*    Func Name: TCPIP_GetPoesWarningSwitch
*  Description: 获取PPPoE连接LCPUP/DOWN告警开关
*        Input: 
*       Output: ULONG *pulSwitch:输出告警开关0: 关 1: 开
*       Return: VOS_OK: 处理成功
*               POES_PARAM_ERR: 输入参数不合法
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPoesWarningSwitch(ULONG *pulSwitch);
/*******************************************************************************
*    Func Name: TCPIP_SetPoesDbgSwitch
*  Description: 设置调试信息开关
*        Input: ULONG ulEthIfIndex:以太接口索引(为0表示设置全局调试信息开关)
*               ULONG ulType:调试信息开关类型 0－所有开关，1－数据报文，2－协商报文，3－事件报文，
*               4－协议及报文错误调试信息
*               ULONG ulValue:开关取值 0－关，1－开
*       Output: 
*       Return: VOS_OK: 处理成功
*               POES_PARAM_ERR: 输入参数不合法
*               POES_IF_NULL: 根据接口索引获取接口指针为空
*               POES_ISNOT_SERVER: 以太接口未使能PPPoE Server
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPoesDbgSwitch(ULONG ulEthIfIndex, ULONG ulType, ULONG ulValue);
/*******************************************************************************
*    Func Name: TCPIP_SetPoesHADbg
*  Description: Set poes ha debug switch
*        Input: ULONG ulDbg: 1: Set, 0: Clear
*       Output: 
*       Return: VOS_OK(0): Success, VOS_ERR(1): Fail
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPoesHADbg(ULONG ulDbg);
/*******************************************************************************
*    Func Name: TCPIP_SetPoesHisSesLimit
*  Description: 设置对端MAC最大Session数限制，默认是100个，配置范围为0－65534
*        Input: ULONG ulSesLimit:传入要配置的对端MAC最大Session数
*       Output: 
*       Return: VOS_OK: 处理成功
*               POES_PARAM_ERR: 输入参数不合法
*               POES_HA_IS_SMOOTHING: HA正在手动倒换或平滑处理
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPoesHisSesLimit(ULONG ulSesLimit);
/*******************************************************************************
*    Func Name: TCPIP_SetPoesOurSesLimit
*  Description: 设置本端Mac最大Session数限制，默认是1000个，配置范围为0－65534
*        Input: ULONG ulSesLimit:要配置的本端MAC最大Session数
*       Output: 
*       Return: VOS_OK: 处理成功
*               POES_PARAM_ERR: 输入参数不合法
*               POES_HA_IS_SMOOTHING: HA正在手动倒换或平滑处理
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPoesOurSesLimit(ULONG ulSesLimit);
/*******************************************************************************
*    Func Name: TCPIP_SetPoesServiceName
*  Description: 设置PPPoE Server的Service Name
*        Input: ULONG ulEthIfIndex:以太接口索引
*               CHAR *pszName:要配置的ServiceName字符串
*       Output: 
*       Return: VOS_OK: 处理成功
*               POES_IF_NULL:    根据接口索引获取接口指针为空
*               POES_ISNOT_SERVER:    以太接口未使能PPPoE Server
*               POES_SERVICENAME_TOOLONG:    输入字符串太长
*               POES_HA_IS_SMOOTHING:    HA正在手动倒换或平滑处理
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPoesServiceName(ULONG ulEthIfIndex, CHAR *pszName);
/*******************************************************************************
*    Func Name: TCPIP_SetPoesSesLimit
*  Description: 设置全局最大Session数限制，默认是1000个，配置范围为0－65534
*        Input: ULONG ulSesLimit:要配置的全局最大Session数
*       Output: 
*       Return: VOS_OK: 处理成功
*               POES_PARAM_ERR: 输入参数不合法
*               POES_HA_IS_SMOOTHING: HA正在手动倒换或平滑处理
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPoesSesLimit(ULONG ulSesLimit);
/*******************************************************************************
*    Func Name: TCPIP_SetPoesWarningSwitch
*  Description: 设置PPPoE连接LCP UP/DOWN告警开关
*        Input: ULONG ulWarnSw:控制命令
*               0表示关，1表示开，其他无效
*       Output: 
*       Return: VOS_OK: 处理成功
*               POES_PARAM_ERR: 输入参数不合法
*      Caution: 普通PPP连接在LCP UP/DOWN时无条件记告警。而POES的PPPoE连接可以通过开关控
*               制。开关的配置全局有效。默认是不记告警。
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPoesWarningSwitch(ULONG ulWarnSw);
/*******************************************************************************
*    Func Name: TCPIP_ShowPoesSessionInfo
*  Description: 显示VISP下所有PPPOE服务端会话信息
*        Input: 
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   luowentong105073        Create
*
*******************************************************************************/
extern VOID  TCPIP_ShowPoesSessionInfo(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ShowPoesStatistic
*  Description: 打印该接口下所有Session的统计信息
*        Input: CHAR *pszIfName:接口名字
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   luowentong105073        Create
*
*******************************************************************************/
extern VOID  TCPIP_ShowPoesStatistic(CHAR *pszIfName);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetACNameHook
*  Description: 注册获取AC NAME的钩子函数
*        Input: GetACName_HOOK_FUNC pfHookFunc:要注册的函数地址
*       Output: 
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-25   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncGetACNameHook(GetACName_HOOK_FUNC pfHookFunc);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __POES_API_H__ */

