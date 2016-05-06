/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ping_api.h
*
*  Project Code: VISPV1R7
*   Module Name: ping
*  Date Created: 2008-03-09
*        Author: wuhailan
*   Description: ping用户API接口文件,该头文件涉及到IPV6的地址数据结构VRP_IN6ADDR_S
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
#ifndef _PING_API_H_
#define _PING_API_H_


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


#ifndef _VRP_IN6ADDR_S
#define _VRP_IN6ADDR_S
typedef   struct    tagVRPIN6Addr
{
    union
    {
        UCHAR   u6_ucaddr[16];
        USHORT  u6_usaddr[8];
        ULONG   u6_uladdr[4];
    } vrp_u6_addr;    /* 128-bit IP6 address */
}VRP_IN6ADDR_S;
#endif

#ifndef IP_HOSTNAME_LEN
#define IP_HOSTNAME_LEN    254   /* 主机名长度*/
#endif

#ifndef MAX_IF_NAME_LENGTH
#define MAX_IF_NAME_LENGTH  47   /* 接口名长度 */
#endif

#define PIN_PADLEN          80   /* ping 报文填充长度 */
#define PIN_VRFNAMELEN      31   /* 私网标识名 */


typedef struct tagPing_Comm_s
{
    CHAR   szHostName[IP_HOSTNAME_LEN + 1];
    UCHAR  ucPadding_1[4-((IP_HOSTNAME_LEN + 1)%4)];
    CHAR   szPattern[PIN_PADLEN];   /* 报文的填充值 */
    ULONG  ulPackets;        /* 发送的报文数量 */
    ULONG  lDatalen;         /* 发送的报文长度 */
    ULONG  ulTimeout;        /* 发送报文的超时时间 */
    ULONG  ulFlag;           /* ping6: 1 or ping4 : 0 */
    ULONG  ulMore;           /* 报文发送时间间隔,单位:ms */

    union
    {
        struct tagPing6_S
        {
            CHAR szInterface[MAX_IF_NAME_LENGTH + 1]; /* 接口名称信息 指定出接口发送,对于ping6全球单播地址如果指定出接口一定指定下一跳.对于ping6链路本地地址一定指定出接口不能指定下一跳 */
            VRP_IN6ADDR_S stSourAddr;                 /* 出接口的源地址,主机序 */
            VRP_IN6ADDR_S stNextHop;                  /* 指定下一跳,主机序,对于ping6指定下一跳一定要指定出接口,否则可以不指定 */
            ULONG ulHopLimit;                         /* 报文中Hop limit */
            ULONG ulTos6;                             /* 报文中Tos */
            ULONG ulForeverFlag;                      /* 不间断ping6, 1表示不间断ping, 0该字段无意义 */
            ULONG ulVrf6Flag ;      /* PING_Vrf_NO or  PING_Vrf_YES */
            CHAR  szVrf6Name[PIN_VRFNAMELEN + 1]; /* 私网标识名,该字段和下面ulVrfIndex字段相同,优先考虑该字段 */
            ULONG ulVrf6Index;      /* VRF Index,该字段和上面szVrfName字段相同,优先考虑该szVrfName */
        }Ping6_Comm;

        struct tagPing4_S
        {
            ULONG ulTTL;           /* 设置的TTL值 */
            ULONG ulTos;           /* 设置的TOS值 */
            ULONG ulIfIndex;       /* 出接口索引 */
            ULONG ulRdqnv[6];      /* Flag of Parameter (-R -d -q -n -v -t) have been specified */
            ULONG ulVrfFlag ;      /* PING_Vrf_NO or  PING_Vrf_YES */
            CHAR  szVrfName[PIN_VRFNAMELEN + 1]; /* 私网标识名,该字段和下面ulVrfIndex字段相同,优先考虑该字段 */
            ULONG ulSourceAddr;    /* 出接口的源地址,主机序 */
            ULONG ulVrfIndex;      /* VRF Index,该字段和上面szVrfName字段相同,优先考虑该szVrfName */
            ULONG ulNextHop;       /* 指定下一跳,主机序 */
            USHORT usDF;           /* 为0表示不设置DF标志，为1则设置DF标志，默认为0 */
            UCHAR  ucRes[2];
        }Ping4_Comm;
    }Ping_Un;

#define   Ping_szInterface    Ping_Un.Ping6_Comm.szInterface
#define   Ping_stSourAddr     Ping_Un.Ping6_Comm.stSourAddr
#define   Ping_stNextHop      Ping_Un.Ping6_Comm.stNextHop
#define   Ping_ulHopLimit     Ping_Un.Ping6_Comm.ulHopLimit
#define   Ping_ulTos6         Ping_Un.Ping6_Comm.ulTos6
#define   Ping_ulForeverFlag  Ping_Un.Ping6_Comm.ulForeverFlag
#define   Ping_ulVrf6Flag      Ping_Un.Ping6_Comm.ulVrf6Flag
#define   Ping_ulVrf6Index     Ping_Un.Ping6_Comm.ulVrf6Index
#define   Ping_szVrf6Name      Ping_Un.Ping6_Comm.szVrf6Name


#define   Ping_ulTTL          Ping_Un.Ping4_Comm.ulTTL
#define   Ping_ulTos          Ping_Un.Ping4_Comm.ulTos
#define   Ping_ulIfIndex      Ping_Un.Ping4_Comm.ulIfIndex
#define   Ping_ulRdqnv        Ping_Un.Ping4_Comm.ulRdqnv
#define   Ping_ulSourceAddr   Ping_Un.Ping4_Comm.ulSourceAddr
#define   Ping_szVrfName      Ping_Un.Ping4_Comm.szVrfName
#define   Ping_ulVrfFlag      Ping_Un.Ping4_Comm.ulVrfFlag
#define   Ping_ulVrfIndex     Ping_Un.Ping4_Comm.ulVrfIndex
#define   Ping_ulNextHop      Ping_Un.Ping4_Comm.ulNextHop
#define   Ping_usDF           Ping_Un.Ping4_Comm.usDF
}Ping_Comm_S;

typedef struct tagTCPIP_PING_STAT
{
    ULONG ulIPAddr;      /* 目的地址，主机序 */
    ULONG ulSendCount;   /* 发送个数*/
    ULONG ulRecvCount;   /* 接收个数*/
    ULONG ulLostCount;   /* 丢包个数*/
    ULONG ulMinTime;     /* 最小响应时间（毫秒）*/
    ULONG ulMaxTime;     /* 最大响应时间（毫秒）*/
    ULONG ulAvgTime;     /* 平均响应时间（毫秒）*/
    VRP_IN6ADDR_S stIPAddr6;  /* 目的IPv6地址, 主机序 */
}TCPIP_PING_STAT_S;

/*ping模块错误码*/
enum tagEnum_PINGERR
{
    PING_ERR_RECVALL = 0,      /* 0 PING操作成功，发出的PING请求报文均收到正确的PING响应报文 */
    PING_ERR_RECVPART,         /* 1 PING操作部分成功，发出的PING请求报文收到部分PING响应报文 */
    PING_ERR_NORECV,           /* 2 PING操作失败，发出的PING请求报文未收到任何PING响应报文 */
    PING_ERR_UNKNOWN_HOST,     /* 3 非法的地址或主机名 */
    PING_ERR_INVAILD_ADDRESS,  /* 4 无效的地址，如广播地址、D类/E类地址等 */
    PING_ERR_OUT_MEMORY,       /* 5 申请内存失败 */
    PING_ERR_FILL_PACKET,      /* 6 报文填充失败 */
    PING_ERR_SOCKET,           /* 7 创建socket失败 */
    PING_ERR_UNKNOWN_VRF,      /* 8 错误的VRF */
    PING_ERR_UNABLE_GETADDR,   /* 9 获取源地址失败 */
    PING_ERR_BIND,             /* 10 Bind失败 */
    PING_ERR_IFINDEX,          /* 11 接口索引错误或IP控制块错误 */
    PING_ERR_TTL,              /* 12 设置socket的TTL选项失败 */
    PING_ERR_TOS,              /* 13 设置socket的TOS选项失败 */
    PING_ERR_INTERFACE,        /* 14 设置socket从特定接口发送选项失败 */
    PING_ERR_RECORD_ROUTE,     /* 15 设置socket记录路由选项失败 */
    PING_ERR_IPV6_UNSPECIFIED, /* 16 IPv6的源地址为空 */
    PING_ERR_IPV6_SOURCEADDR,  /* 17 IPv6的源地址非法 */
    PING_ERR_IPV6_DESTADDR,    /* 18 IPv6的目的地址非法 */
    PING_ERR_IPV6_INTERNAME,   /* 19 非法的接口名 （IPv6）*/
    PING_ERR_IPV6_GETTABLE,    /* 20 获取虚表失败 （IPv6）*/
    PING_ERR_IPV6_INTERADDR,   /* 21 获取地址失败 （IPv6）,目的地址是全球单播且没有指定源IP,接口必须存在全球单播地址 */
    PING_ERR_IPV6_LINKLOCAL,   /* 22 链路本地地址接口非法（IPv6）*/
    PING_ERR_IPV6_NOLINKLOCAL, /* 23 非链路本地地址接口非法（IPv6）*/
    PING_ERR_IPV6_NOINTERNAME, /* 24 非链路本地且非多播却指定了出接口（IPv6）*/
    PING_ERR_IPV6_BIND,        /* 25 Bind失败（IPv6）*/
    PING_ERR_IPV6_RECVMSG,     /* 26 获取ICMPv6replay报文的源地址失败（IPv6）*/
    PING_ERR_SETOPT_DEBUG,     /* 27 设置socket的SO_DEBUG选项失败 */
    PING_ERR_SETOPT_DONTROUTE, /* 28 设置socket的SO_DONTROUTE选项失败 */
    PING_ERR_SETOPT_RCVBUF,    /* 29 设置socket的SO_RCVBUF选项失败 */
    PING_ERR_DATALEN,          /* 30 报文长度错误,范围是0~8100 */
    PING_ERR_PARAM,            /* 31 输入参数错误,如空指针等 */

    PING_API_COM_NULL,         /* 32 输入组件为空 */
    PING_API_PARA_WRONG,       /* 33 输入参数错误,如空指针等 */
    PING_ERR_NOT_L3INT,        /* 34 二层端口不支持Ping */
    PING_ERR_VRF_NOT_INIT,     /* 35 VRF模块未注册 */
    PING_ERR_IPV6_GET_IPCTL,   /* 36 获取IPV6控制块指针为空  */
    PING_ERR_LOCAL_NOT_NEXTHOP,/* 37 链路本地地址不能指定下一跳  */
    PING_ERR_NEXTHOP_NOTGLOBAL,/* 38 下一跳地址必须是全球单播地址  */
    PING_ERR_IF_NOTNEXTHOP,    /* 39 全球单播地址指定出接口时,必须要指定下一跳 */
    PING_ERR_NEXTHOP_NOTIF,    /* 40 全球单播地址指定下一跳时,必须要指定出接口 */
    PING_ERR_NH_NOINTF,        /* 41 PING4指定下一跳一定要指定出接口 */
    PING_ERR_IFANDNEXTHOP,     /* 42 PING4指定出接口和下一跳失败 */

    PING_ERR_IFANDNEXTHOP_2,   /* 43 通过查找路由表找到下一跳后设置出接口和下一跳失败 */
    PING_ERR_IFANDNEXTHOP_3,   /* 44 通过查找路由表找到出接口后设置出接口和下一跳失败 */
    PING_ERR_GETNEXTHOP_BY_FIB,/* 45 通过查找路由获取下一跳失败 */
    PING_ERR_GETIFINDEX_BY_FIB,/* 46 通过查找路由获取出接口失败 */
    PING_ERR_SETOPT_HDRINCL,   /* 47 设置socket的IP_HDRINCL选项失败 */
    PING_ERR_INVAILD_DF,       /* 48 无效的DF参数，只能为0或者1 */
};

typedef VOID (*TCPIP_PINGOutput_HOOK_FUNC)(CHAR *pstBuf);

/* ping统计信息通知回调函数原型, 统计信息内存由VISP申请, 如果传出参数指针不为空, 则需要产品释放 */
typedef VOID (*TCPIP_PINGSTAT_HOOK_FUNC)(TCPIP_PING_STAT_S *pstPingStat);

/* 多任务ping统计信息通知回调函数原型, 统计信息内存由VISP申请, 如果传出参数指针不为空, 则需要产品释放 */
typedef VOID (*TCPIP_PINGEXSTAT_HOOK_FUNC)(TCPIP_PING_STAT_S *pstPingStat, ULONG ulExecID);


typedef VOID (*TCPIP_PINGExOutput_HOOK_FUNC)(CHAR *pstBuf,ULONG ulExecID);

/*******************************************************************************
*    Func Name: TCPIP_Ping
*  Description: PING功能函数
*        Input: Ping_Comm_S *pPingParam:PING结构体参数信息指针
*       Output: 无
*       Return: 成功返回0
*               失败返回错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_Ping(Ping_Comm_S *pPingParam);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncPINGOutputHook
*  Description: PING信息输出适配函数注册接口
*        Input: TCPIP_PINGOutput_HOOK_FUNC pfHookFuc:提供给用户注册的PING模块信息输出函数指针
*       Output: 无
*       Return: VOS_OK成功,其他返回失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncPINGOutputHook(TCPIP_PINGOutput_HOOK_FUNC pfHookFuc);
/*******************************************************************************
*    Func Name: TCPIP_SetPingTos
*  Description: 设置ping模块的tos值
*        Input: UCHAR ucTos: 要设置的tos值，值域有效
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-19    LY(57500)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_SetPingTos(UCHAR ucTos);
/*******************************************************************************
*    Func Name: TCPIP_GetPingTos
*  Description: 获取ping模块设置的tos值
*        Input: UCHAR *pucTos: 保存输出的tos值
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-19    LY(57500)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_GetPingTos(UCHAR *pucTos);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncPingStatHook
*  Description: 注册Ping统计信息通知回调函数
*        Input: TCPIP_PINGSTAT_HOOK_FUNC pfFunc: 回调函数
*       Output: 
*       Return: PING_API_PARA_WRONG：回调函数指针为空
*               VOS_OK：处理成功
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-21  wujie(61195)     Create the first version.
*
*******************************************************************************/
ULONG TCPIP_RegFuncPingStatHook(TCPIP_PINGSTAT_HOOK_FUNC pfFunc);

/*****************************************************************************
 函 数 名  : TCPIP_PingEx
 功能描述  : PIng功能函数,支持多任务同时ping
 输入参数  : ULONG ulExecID:任务ID
             Ping_Comm_S *pPingParam
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年4月27日
    作    者   : w62223
    修改内容   : 新生成函数

*****************************************************************************/

ULONG TCPIP_PingEx(ULONG ulExecID, Ping_Comm_S *pPingParam);


/*****************************************************************************
 函 数 名  : TCPIP_RegFuncPINGExOutputHook
 功能描述  : PING信息输出适配函数注册接口
 输入参数  : TCPIP_PINGExOutput_HOOK_FUNC pfHookFuc
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年4月27日
    作    者   : w62223
    修改内容   : 新生成函数

*****************************************************************************/

ULONG TCPIP_RegFuncPINGExOutputHook(TCPIP_PINGExOutput_HOOK_FUNC pfHookFuc);

/*******************************************************************************
*    Func Name: TCPIP_VispPing
* Date Created: 2009-09-15
*       Author: z00104207
*  Description: 之前VISP协议栈在各个产品应用时，经常出现Ping相关的问题，而定位时
*               无法直接调用VISP的ping接口协助调试定位，因此需提供一个新的接口供
*               协助调试定位使用。
*        Input: CHAR *szHostName: 目的主机的地址
*               ULONG ulTimeout:  ping操作的超时时间
*               CHAR *szVrfName:  VRF名称
*               ULONG ulDatalen:  ping报文的净荷长度
*               ULONG ulPackets:  ping报文的个数
*               ULONG ulTos:      TOS值
*               ULONG ulTtl:      TTL值
*               CHAR *szIfName:   出接口名
*               CHAR *szSrcIp:    源地址
*               ULONG ulTaskPri:  ping任务的优先级，默认取为100
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-15   z00104207               Create
*
*******************************************************************************/
extern VOID TCPIP_VispPing(CHAR *szHostName, ULONG ulTimeout, CHAR *szVrfName, ULONG ulDatalen, ULONG ulPackets,
    ULONG ulTos, ULONG ulTtl, CHAR *szIfName, CHAR *szSrcIp, ULONG ulTaskPri);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncPingExStatHook
* Date Created: 2009-12-14
*       Author: zhangchunyu(62474)
*  Description: 注册多任务PING统计信息钩子函数
*        Input: TCPIP_PINGEXSTAT_HOOK_FUNC pfFunc: 钩子回调函数
*       Output: 
*       Return: VOS_OK:成功  其他:失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-14    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncPingExStatHook(TCPIP_PINGEXSTAT_HOOK_FUNC pfFunc);


/*******************************************************************************
*    Func Name: TCPIP_SetPing6Tos
* Date Created: 2009-12-14
*       Author: zhangchunyu(62474)
*  Description: 设置ping6全局tos值,在ping6的情况,如果没有指定tos,则使用全局tos值
*        Input: UCHAR ucTos: 设置Tos值[0,255]
*       Output:
*       Return: VOS_OK:成功  其他:失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-14    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetPing6Tos(UCHAR ucTos);

/*******************************************************************************
*    Func Name: TCPIP_GetPing6Tos
* Date Created: 2009-12-14
*       Author: zhangchunyu(62474)
*  Description: 获取全局tos值
*        Input: UCHAR *pucTos: 输出参数,获取全局tos值,获取值范围[0,255]
*       Output:
*       Return: VOS_OK:成功  其他:失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-14    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetPing6Tos(UCHAR *pucTos);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* _PING_API_H_ */

