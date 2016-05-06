/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              udp_api.h
*
*  Project Code: VISPV1R7
*   Module Name: UDP_API  
*  Date Created: 2008-03-07
*        Author: zhengsenhuo(00104483)
*   Description:  
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*   2008-03-07  Zheng SenHuo           Creat the first version.
*  2008-10-15  xiehuaguo        C01同步C02
*   
*******************************************************************************/


#ifndef        _UDP_API_H
#define        _UDP_API_H

#ifdef    __cplusplus
extern    "C"{
#endif

/* added by tangcongfeng for VISP D02170 */
#define UDP_MAXFILTNUM      5  /* 规则组中的SOCKET数目上限 */
#define UDP_FILTOK          0  /* 操作成功，从规则表中移除一个socket */
#define UDP_FILTINUSE       1  /* 规则表中已经存在该socket */
#define UDP_FILTTOOMUCH     2  /* 规则表中socket数量已满 */
#define UDP_FILTNOTFOUND    3  /* 规则表中没有该socket */
#define UDP_FILTNONE        4  /* 规则表已空，UDP的调试开关也同时关闭 */
#define UDP_FILTISANY       5  /* 该socket被加入规则表 */
#define UDP_FILTCMDERR      6  /* 命令字错误 */
#define UDP_NOT_REGISTERED  7  /* UDP组件未注册 */
#define UDP_ENOBUFS         10 /* 报文指针为空 */

#define UDP_INPUT_NULL_POINT 11 /* 指定socket获取udp统计信息输入空指针 */
#define UDP_ERR_NULL_INPCB   12 /* INPCB控制块为空 */
#define UDP_ERR_GETSTAT_INPCB 13 /* 指定socket获取udp统计信息INPCB控制块为空 */
#define UDP_ERR_GETSTAT_SOCKETCB  14 /* 指定socket获取udp统计信息SOCKETCB控制块为空 */

/* ended */

#define UDP_NETINFO_FINISH        15 /* UDPNetInfo 查询结束 */
#define UDP_GETBFD_ERROR          16 /* 获取BFD链接端口信息失败 */
#define UDP_ERR_PARAWRONG         17 /* 参数输入错误 */
#define UDP_GETINPCB_WRONG        18 /* 获取得到的INPCB为空 */

/* debug 开关值 */
#define UDP_DEBUG_OFF       0
#define UDP_DEBUG_ON        1

typedef struct tagUDPHDR
{
    USHORT    uh_usSPort;        /* source port */
    USHORT    uh_usDPort;        /* destination port */
    SHORT     uh_sULen;          /* udp length */
    USHORT    uh_usSum;          /* udp checksum */
}UDPHDR_S;

typedef struct tagUDP_FILTER_S{
    ULONG   ulTaskId;
    ULONG   ulSockId;
}UDP_FILTER_S;

typedef struct tagUDP_DEBUGFILTER_S{       
    UDP_FILTER_S stDbugFilt[UDP_MAXFILTNUM];  /*Debug Filter*/
    ULONG        ulFiltCnt;                   /*Debug Filter Count*/
}UDP_DEBUGFILTER_S;

typedef struct tagUDPSTAT_S
{
                                        /* input statistics: */
    ULONG   udps_ulIPackets;            /* total input packets */
    ULONG   udps_ulHdrOps;              /* packet shorter than header */
    ULONG   udps_ulBadSum;              /* checksum error */
    ULONG   udps_ulBadLen;              /* data length larger than packet */
    ULONG   udps_ulNoPort;              /* no socket on port */
    ULONG   udps_ulNoPortBcast;         /* of above, arrived as broadcast */
    ULONG   udps_ulFullSock;            /* not delivered, input socket full */
    ULONG   udps_ulPcbCacheMiss;        /* input packets missing pcb cache */
                                        /* output statistics: */
    ULONG   udps_ulOPackets;            /* total output packets */
    ULONG   udps_ulOutErr;
}UDPSTAT_S;

/* 基于socket id,task id和四元组获取统计信息输入参数数据结构 */
typedef struct tagUDP4CONN_S
{
    ULONG    ulVrfIndex;    /* VRF索引*/
    ULONG    ulLAddr;       /* 本端地址 (主机序)*/
    ULONG    ulFAddr;       /* 对端地址 (主机序)*/
    ULONG    ulLPort;       /* 本端端口号 */
    ULONG    ulFPort;       /* 对端端口号 */
    ULONG    ulSocketID ;   /* Socket ID */
    ULONG    ulTaskID;      /* 任务 ID */
}UDP4CONN_S;

/* 基于socket id,task id和四元组获取统计信息数据结构 */
typedef struct tagUDP4PERSTAT_S
{
    UDP4CONN_S stUdp4Conn;          /* 实际获取的socket id task id 和四元组 */                                        
    ULONG   ulIPackets;             /* 接收到的UDP报文包数  */
    ULONG   ulIPacketBytes;         /* 接收到的UDP报文字节数 */
                                   
    ULONG   ulOPackets;              /* 发送的UDP报文包数  */
    ULONG   ulOPacketBytes;          /* 发送的UDP报文字节数 */

    /*socket 缓冲区信息*/
    ULONG    ulSndHiWat ;           /*发送缓冲区高水位*/
    ULONG    ulRcvHiWat ;           /*接收缓冲区高水位*/
    ULONG    ulSndCC ;              /*发送缓冲区中实际数据 */
    ULONG    ulRcbCC ;              /*接收缓冲区中实际数据 */
    ULONG    ulDropPackets;         /*由于接收缓冲区满丢弃的报文数*/
    ULONG    ulDropPacketBytes;     /*由于接收缓冲区满丢弃的报文字节数*/
}UDP4PERSTAT_S;

typedef ULONG (*UDP4InterMediate_HOOK_FUNC)(MBUF_S *pMBuf, LONG nIpHLen);

typedef struct tagTCPIP_UDPNETINFO_S
{
    ULONG   ulTaskId;       /*任务ID*/
    ULONG   ulSrcIp;        /* 主机字节序 */
    ULONG   ulDstIp;        /* 主机字节序 */
    USHORT  usSrcPort;
    USHORT  usDestPort;
    /*Added by limin00188004, 获取网络状态时输出socket所绑定的VRF索引, 2012/9/28   问题单号:S.VRF.02.01 */
    ULONG   ulVrfIndex;
    /* End of Added by limin00188004, 2012/9/28   问题单号:S.VRF.02.01 */
}TCPIP_UDPNETINFO_S;

/*******************************************************************************
*    Func Name: TCPIP_SetUDPDbgFilter
*  Description: 打开/关闭指定socket id和task id的udp4 debug开关
*        Input: ULONG ulFlag:命令字[0,1]
*               ULONG ulTaskId:socket所在的任务ID
*               ULONG ulSockId:套接字ID
*       Output: 
*       Return: UDP_FILTISANY       添加了一条规则
*               UDP_FILTTOOMUCH     规则表满
*               UDP_FILTINUSE       指定的规则已经被配置过了
*               UDP_FILTNOTFOUND    没找到要删除的规则
*               UDP_FILTNONE        规则表已经被清空了
*               UDP_FILTOK          操作成功
*               VOS_ERR             UDP4组件未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-17   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
ULONG TCPIP_SetUDPDbgFilter( ULONG ulFlag, ULONG ulTaskId, ULONG ulSockId );
/*******************************************************************************
*    Func Name: TCPIP_GetUDPDbgFilter
*  Description: 获取UDP4规则表和UDP4调试开关的状态
*        Input: ULONG *pulDebugFlag:UDP调试开关的值
*               UDP_DEBUGFILTER_S *pstUdpDbgFilter:UDP规则表
*       Output: 
*       Return: VOS_OK  成功
*               VOS_ERR 失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-17   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
ULONG TCPIP_GetUDPDbgFilter( ULONG *pulDebugFlag,UDP_DEBUGFILTER_S *pstUdpDbgFilter );
/*******************************************************************************
*    Func Name: TCPIP_NoDebugUDPAll
*  Description: 清除UDP4 DEBUG标记并将过滤值清零
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-17   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
VOID  TCPIP_NoDebugUDPAll(VOID);
/*******************************************************************************
*    Func Name: TCPIP_DebugUDPAll
*  Description: 打开所有UDP4 DEBUG开关
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-09   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
VOID  TCPIP_DebugUDPAll(VOID);
/*******************************************************************************
*    Func Name: TCPIP_GetUDPStat
*  Description: 获取UDP4组件的统计信息
*        Input: UDPSTAT_S *pstUdpStatistics: 保存UDP4组件的统计信息
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-17   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
VOID  TCPIP_GetUDPStat( UDPSTAT_S *pstUdpStatistics );
/*******************************************************************************
*    Func Name: TCPIP_ClrUDPStat
*  Description: 清空UDP4组件的统计信息
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-09   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
VOID  TCPIP_ClrUDPStat(VOID);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncUDPInterMediateHook
*  Description: 产品向VISP注册钩子函数，用于IWF模块处理UDP报文
*        Input: UDP4InterMediate_HOOK_FUNC pfHookFunc:钩子函数指针
*       Output: 
*       Return: VOS_OK  操作成功
*               VOS_ERR 操作失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-17   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
ULONG TCPIP_RegFuncUDPInterMediateHook(UDP4InterMediate_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_ShowUdpStatistic
*  Description: UDP统计信息显示接口
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-09   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
VOID  TCPIP_ShowUdpStatistic (VOID);
/*******************************************************************************
*    Func Name: TCPIP_UdpInput
*  Description: 处理输入的UDP报文
*        Input: MBUF_S *pMBuf:指向待处理的IP报文指针，该IP报文包含待处理的UDP报文
*               LONG nIpHLen:待处理报文的IP首部长度（含IP选项）
*       Output: 
*       Return: VOS_OK  操作成功
*               VOS_ERR 组件未注册
*               UDP_ENOBUFS 指针为空
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-17   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
ULONG TCPIP_UdpInput( MBUF_S *pMBuf, LONG nIpHLen);

/*******************************************************************************
*    Func Name: TCPIP_GetPerUdp4ConnStats
* Date Created: 2009-12-28
*       Author: Gexianjun/h00121208
*  Description: 指定socket id, task id或指定四元组，VRF获取指定的UDP统计信息
*        Input: UDP4CONN_S *pstConnInfo:    获取指定UDP Socket输入参数
*       Output: UDP4PERSTAT_S *pstRetStats: 获取指定的UDP统计信息
*       Return: 成功:VOS_OK;失败:错误码
*      Caution: 如果socket的模式是全局socket,根据socket id获取udp统计信息,则不需要指定task id;
*               否则需要同时指定socket id和task id。本接口获取UDP统计信息输入参数必须配对才能正确
*               获取:输入参数可以为socket id + task id去获取;或输入参数为四元组+vrf去获取；
*               也可以同时指定这两种组合。获取方法是先根据socket id +task id去获取,
*               如果获取失败,再根据四元组+vrf去获取。
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-28   Gexianjun/h00121208     Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPerUdp4ConnStats(UDP4CONN_S *pstConnInfo, UDP4PERSTAT_S  *pstRetStats);

/*******************************************************************************
*    Func Name: TCPIP_ResetPerUdp4ConnStats
* Date Created: 2009-12-28
*       Author: Gexianjun/h00121208
*  Description: 指定socket id, task id或指定四元组，VRF清除指定的UDP统计信息
*        Input: UDP4CONN_S *pstConnInfo: 清除指定UDP Socket输入参数
*       Output: 
*       Return: 成功:VOS_OK;失败:错误码
*      Caution: 如果socket的模式是全局socket,根据socket id清除udp统计信息,则不需要指定task id;
*               否则需要同时指定socket id和task id。本接口清除UDP统计信息输入参数必须配对才能正确
*               清除:输入参数可以为socket id + task id去清除;或输入参数为四元组+vrf去清除；
*               也可以同时指定这两种组合。清除方法是先根据socket id +task id去查找udp socket, 如果
*               查找成功,则清除指定的该udp socket的统计信息,如果查找失败,再根据四元组+vrf去查找udp socket,
*               如果查找成功,则清除指定的该udp socket的统计信息。 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-28   Gexianjun/h00121208     Create
*
*******************************************************************************/
extern ULONG TCPIP_ResetPerUdp4ConnStats(UDP4CONN_S *pstConnInfo);


typedef ULONG (*UDPINPUT_HOOK_FUNC)( MBUF_S* pMbuf );
ULONG TCPIP_RegFuncUDPInputHook( UDPINPUT_HOOK_FUNC pfFuncHook );
extern UDPINPUT_HOOK_FUNC g_UDP_Input_HookFunc;

#define UDP_NOT_PROCESSED_BY_INTERMEDIATE              0 
/* intermediate found the packet has Error, Stack will Destroy the Packet */
#define UDP_INTER_PROCESS_ERROR                        1
/* Intermediate Processing will continue processing and will own the packet
 * PP do not need to process the packet any more */
#define UDP_PROCESSED_BY_INTERMEDIATE                  2
/* UDP错误码 */
/* intermediate process not processed the packet. 
 * Stack (UDP4) will do the processing
 */
#define UDP4_NOT_PROCESSED_BY_INTERMEDIATE              1  /*钩子函数不处理（即由VISP处理）*/

/* Intermediate Processing will continue processing and will own the packet
 * UDP4 do not need to process the packet any more
 */
#define UDP4_PROCESSED_BY_INTERMEDIATE                  2  /*由钩子函数处理（即VISP不处理）*/

/*******************************************************************************
*    Func Name: TCPIP_OpenUdpNetInfo
* Date Created: 2011-11-5
*       Author: y00171195/p00193127
*  Description: 打开查询句柄
*        Input: 
*       Output: pulWaitlist:Waitlist句柄
*       Return: 成功:VOS_OK;失败:错误码
*      Caution: 只有查询句柄打开成功才能进行下一步UDP网络连接信息查询操作。
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-11-5   y00171195/p00193127     Create
*
*******************************************************************************/
extern ULONG TCPIP_OpenUdpNetInfo(UINTPTR *pulWaitlist);

/*******************************************************************************
*    Func Name: TCPIP_GetUdpNetInfo
* Date Created: 2011-11-5
*       Author: y00171195/p00193127
*  Description: 获取UDP网络连接信息
*        Input: pulWaitlist:Waitlist句柄
*       Output: TCPIP_UDPNETINFO_S*pstNetInfo网络连接信息
*       Return: 成功:VOS_OK;失败:错误码
*      Caution:
*               1、只有查询句柄打开成功才能进行下一步UDP网络连接信息查询操作
*               2、每次查询获取一个连接信息
*               3、该函数在打开查询句柄后可以进行多次查询以返回所有的UDP网络连接信息
*               4、每次查询是否成功依赖于其返回值,返回VOS_OK时本次查询成功
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-11-5   y00171195/p00193127     Create
*
*******************************************************************************/
extern ULONG TCPIP_GetUdpNetInfo(UINTPTR ulWaitlist, TCPIP_UDPNETINFO_S *pstNetInfo);

/*******************************************************************************
*    Func Name: TCPIP_CloseUdpNetInfo
* Date Created: 2011-11-5
*       Author: y00171195/p00193127
*  Description: 关闭查询句柄
*        Input: ulWaitlist:Waitlist句柄
*       Output: 
*       Return: 成功:VOS_OK;失败:错误码
*      Caution: 在查询结束后或者获取UDP网络连接信息失败时需要关闭查询句柄。
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-11-5   y00171195/p00193127     Create
*
*******************************************************************************/
extern ULONG TCPIP_CloseUdpNetInfo(UINTPTR ulWaitlist);

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif

