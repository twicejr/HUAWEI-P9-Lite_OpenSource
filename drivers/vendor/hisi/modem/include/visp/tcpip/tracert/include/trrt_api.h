/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              trrt_api.h
*
*  Project Code: VISPV1R7
*   Module Name: trrt  
*  Date Created: 2008-03-09
*        Author: wuhailan
*   Description: trrt用户API接口文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
#ifndef _TRRT_API_H_
#define _TRRT_API_H_


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define TRRT_VRF_MAX_VRFNAME_LENGTH 31

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


typedef struct tagTrrtCommonParam
{
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-05统一用数组   */
    /* CHAR    *szVrfName;*/ 
    CHAR  szVrfName[TRRT_VRF_MAX_VRFNAME_LENGTH + 1];
    /* End:VISP1.7C03 VRF wangchengyang,2009-02-05   */
    CHAR    *szHostName; 
    ULONG    ulFirstTTL;
    ULONG    ulMaxTTL;
    USHORT   usPort;
    UCHAR    ucPadding[2]; 
    ULONG    ulNQueries;
    ULONG    ulTimeout;
    ULONG    ulSourceAddr;
    ULONG    ulTrrtFlag;         /* TRRT_6  or TRRT4 */
    ULONG    ulVrfFlag ;         /* VRF_YES or VRF_NO*/
    ULONG    ulOutIfIndex;       /* 指定出接口发送, TRRT4可以指定下一跳也可以不指定下一跳. 对于TRRT6下一跳和出接口必须同时指定,否则可以不指定 */
    ULONG    ulDetectMtu;        /* 路径Mtu探测标记 */
    ULONG    ulVrfIndex;         /* VrfIndex,可以同时指定szVrfName和VRFIndex,以szVrfName优先考虑VRF */
    ULONG    ulNextHopAddr;      /* IPV4下一跳, 指定下一跳必须指定出接口 */
    VRP_IN6ADDR_S stSourAddr6;   /* IPV6指定源地址 , 主机序*/
    VRP_IN6ADDR_S stNextHopAddr6;/* IPV6指定下一跳, 下一跳和出接口必须同时指定,否则可以不指定, 主机序 */
}TrrtCommonParam;

typedef struct tagTCPIP_TRRT_STAT
{
    ULONG ulInfoID;      /* 信息类型 */
    ULONG ulCode;        /* 接口不可达类型,仅在信息类型为TRRT_UNREACHABLE时使用 */
    ULONG ulHops;        /* 跳数 */
    ULONG ulDstIPAddr;   /* 目的地址，主机序, 在ping4操作中该字段有效  */
    ULONG ulHopIPAddr;   /* 中途地址, 主机序  在ping4操作中该字段有效  */
    ULONG ulQueryId;     /* 尝试次数 */
    ULONG ulTime;        /* 耗时(毫秒) */
    VRP_IN6ADDR_S stDstIPAddr6;  /* 目的IPv6地址, 主机序, 在ping6操作中该字段有效  */
    VRP_IN6ADDR_S stHopIPAddr6;  /* 中途IPv6地址, 主机序, 在ping6操作中该字段有效  */
}TCPIP_TRRT_STAT_S;

typedef struct tagTrrtDetectMtuParam
{
    CHAR     szVrfName[TRRT_VRF_MAX_VRFNAME_LENGTH + 1];
    CHAR    *szHostName;         /* 主机名 */
    ULONG    ulFirstTTL;         /* 最小TTL */
    ULONG    ulMaxTTL;           /* 最大TTL,不能大于255 */
    USHORT   usPort;             /* 目的端口号(大于等于49152)*/
    UCHAR    ucTos;              /* IP首部TOS字段值 */
    UCHAR    ucDspPathDscp;      /* 显示收到的ICMP报文载荷中的IP首部的DSCP值，为0则不显示DSCP，为1则输出DSCP，默认为0 */
    ULONG    ulNQueries;         /* 每次发送的报文数字段 */
    ULONG    ulTimeout;          /* 超时时间 */
    ULONG    ulSourceAddr;       /* 源地址字段(主机序) */
    ULONG    ulTrrtFlag;         /* TRRT_6 or TRRT_4 */
    ULONG    ulVrfFlag ;         /* VRF_YES or VRF_NO */
    ULONG    ulOutIfIndex;       /* 指定出接口发送, TRRT4可以指定下一跳也可以不指定下一跳. 对于TRRT6下一跳和出接口必须同时指定,否则可以不指定 */
    ULONG    ulDetectMtu;        /* 路径Mtu探测标记, VOS_TRUE:启动探测功能  VOS_FALSE:不启动探测功能 */
    ULONG    ulVrfIndex;         /* VrfIndex,可以同时指定szVrfName和VRFIndex,以szVrfName优先考虑VRF */
    ULONG    ulNextHopAddr;      /* IPV4下一跳, 指定下一跳必须指定出接口 */
    VRP_IN6ADDR_S stSourAddr6;   /* IPV6指定源地址 , 主机序*/
    VRP_IN6ADDR_S stNextHopAddr6;/* IPV6指定下一跳, 下一跳和出接口必须同时指定,否则可以不指定, 主机序 */
    struct tagDetectMtu
    {
        ULONG    ulIpaddr;       /* 输出参数,路径MTU所在接口IP,网络序，当ulResult返回TRRT_SUC_MTUCHANGE有效 */
        ULONG    ulPathMtu;      /* 输出参数,探测路径MTU，当ulResult返回TRRT_SUC_MTUCHANGE有效 */
        ULONG    ulResult;       /* 输出参数,探测路径MTU返回的结果,返回值参考enumTrrtMtuErrInf */
    }DETECT_MTU;
}TCPIP_TRRT_DETECTMTU_S;


/*注意:如果修改错误码，请同步修改trrt_sh_info.c文件中的CHAR * Inf_Tracert_En[]描述信息*/
enum enumTracertErrInf
{ 
    TRRT_SUCESS  = 0,                                   /* 0 */
    TRRT_FAIL    = 1,                                   /* 1 */
    
    TRRT_CREATE_RECSOCKERR,                             /* 2 */
    TRRT_CREATE_SNDSOCKERR,                             /* 3 */                            
    TRRT_UNKNOWN_VPN,                                   /* 4 */
    TRRT_NO_SELECTLOCALADDR,                            /* 5 */
    TRRT_DESTADDR_NOLOCALADDR,                          /* 6 */
    TRRT_UNKNOW_HOST,                                   /* 7 */
    TRRT_OUTOF_MEMORY,                                  /* 8 */
    TRRT_SET_IP_HDRINCLERR,                             /* 9 */
    TRRT_TRACERT_VRFTO,                                 /* 10 */
    TRRT_TRACERT_TO,                                    /* 11 */
    TRRT_TRRT_BEGININFO,                                /* 12 */
    TRRT_PACKET_TOOSHORT,                               /* 13 */
    TRRT_PACKET_RETURNFORM,                             /* 14 */
    TRRT_ICMP_RETURNINFO,                               /* 15 */
    TRRT_SET_IPV6_RECVPKTINFOERR,                       /* 16 */
    TRRT__HOSTNAME_RESLOVED,                            /* 17 */
    TRRT_DESTADDR_UNSPEC,                               /* 18 */
    TRRT_FAIL_LINKLOCAL,                                /* 19 */
    TRRT_FAIL_MCASTADDR,                                /* 20 */
    TRRT_TTL_OUTOFBANK,                                 /* 21 */
    TRRT_UNABLE_SEND,                                   /* 22 */
    TRRT_SEND_DATAINFO,                                 /* 23 */
    TRRT_IPV6_PACKETDUMP,                               /* 24 */
    TRRT_RECEIVE_RESPONSE,                              /* 25 */ 
    TRRT_SET_OPTIONERR,                                 /* 26 */
    TRRT_INVALID_ADDRESS,                               /* 27 */
    TRRT_MINTTL_INVAL,                                  /* 28 */
    TRRT_SET_IPV6_RECVHOPLIMTERR,                       /* 29 */

    TRRT_PARAM_ERR,                                     /* 30 */   
    TRRT_PRINT_TRACE,                                   /* 31 */
    TRRT_PRINT,                                         /* 32 */
    TRRT_PRINT_TTL,                                     /* 33 */
    TRRT_PRINT_TIME,                                    /* 34 */
    TRRT_UNREACH_NOPORT,                                /* 35 */                   
    TRRT_UNREACH_NOROUTE,                               /* 36 */ 
    TRRT_UNREACH_ADDR,                                  /* 37 */ 
    TRRT_UNREACH_ADMIN,                                 /* 38 */              
    TRRT_UNREACH_NOTNEIGHBOR,                           /* 39 */                    
    TRRT_UNREACHABLE,                                   /* 40 */              
    TRRT_UNREACH_HOST,                                  /* 41 */                     
    TRRT_UNREACH_NEEDFRAG,                              /* 42 */                        
    TRRT_PRINT_TIMEOUT,                                 /* 43 */                         
    TRRT_NAME_NULL,                                     /* 44 */                         
    TRRT_NAMELEN_INVALID,                               /* 45 */                       
    TRRT_FLAG_ERR,                                      /* 46 */                            
    TRRT_MINTTL_ERR,                                    /* 47 */                            
    TRRT_MAXTTL_ERR,                                    /* 48 */                            

    TRRT_API_COM_NULL,                                  /* 49 组件为空*/
    TRRT_API_PARA_WRONG,                                /* 50 传入参数错误*/

    TRRT_NULL_IFNET,                                    /* 51 找不到出接口 */
    TRRT_WRONG_IFTYPE,                                  /* 52 出接口不是支持的类型 */
    TRRT_SET_OUTIFERR,                                  /* 53 设置出接口错误 */

    TRRT_VRF_NOT_INIT,                                  /* 54 VRF没有初始化 */
    TRRT_DETECTMTU_SUCCESS,                             /* 55 探测路径MTU成功 */
    TRRT_DETECTMTU_FAIL,                                /* 56 探测路径MTU失败 */
    TRRT_DETECTMTU_BEGININFO,                           /* 57 探测路径MTUINFO信息 */
    TRRT_GETIFBYIP_FAIL,                                /* 58 根据目的IP查找出接口失败 */
    TRRT_MTUFLAG_WRONG,                                 /* 59 MTU探测标记错误 */

    TRRT_SET_PORTERR,                                   /* 60 设置目的端口号错误 */
    
    TRRT_SOURIP_ONLY_GLOBAL,                            /* 61 源地址不能是链路本地地址或多播地址  */
    TRRT_BIND_ERR,                                      /* 62 绑定失败 */
    TRRT_NOGLOBALIP,                                    /* 63 出接口不存在全球单播地址 */
    TRRT_IPV6ADDRCOM_NULL,                              /* 64 ipv6地址组建为空 */
    TRRT_IPV6_IPCTL_NULL,                               /* 65 获取IPV6控制块指针为空 */
    TRRT_NEXTHOPIP_ONLY_GLOBAL,                         /* 66 下一跳地址不能是链路本地地址或多播地址 */
    TRRT_NHOP_IF_NOTALL,                                /* 67 出接口和下一跳地址必须同时指定,不能只指定其中一个 */
    TRRT_NHOP_NO_IF,                                    /* 68 指定出接口一定要指定下一跳 */
    TRRT_ERR_IFANDNEXTHOP,                              /* 69 PING4指定出接口和下一跳失败 */
    TRRT_ERR_IFANDNEXTHOP_2,                            /* 70 获取下一跳后设置出接口和下一跳失败 */
    TRRT_ERR_IFANDNEXTHOP_3,                            /* 71 获取出接口后设置出接口和下一跳失败 */
    TRRT_ERR_GETNEXTHOP_BY_FIB,                         /* 72 获取下一跳失败 */
    TRRT_ERR_GETIFINDEX_BY_FIB,                         /* 73 获取出接口失败 */
    TRRT_OVER,                                          /* 74 */
    TRRT_SET_PORTRANGE_ERR,                             /* 75 设置Traceroute目的端口号范围错误*/
    TRRT_SET_DEFAULTPORT_ERR,                           /* 76 设置Traceroute默认目的端口号错误*/
    TRRT_MULTI_PTMU_DETECT,                             /* 77 多次路径MTU探测*/
    TRRT_DROP_PACKET_BYSRCIP,                           /* 78 通过源IP查找出接口返回丢包 */
    TRRT_ERR_UNKNOWN_VRF,                               /* 79 指定出接口与指定VRF不相符 */
    TRRT_PRINT_DSCP,                                    /* 80 TRRT输出中打印DSCP信息 */
    TRRT_ERR_INVAILD_DSCPFLAG                           /* 81 输入参数ucDspPathDscp错误 */
};
/*注意:如果修改错误码，请同步修改trrt_sh_info.c文件中的CHAR * Inf_Tracert_En[]描述信息*/

/* 只有使能探测MTU时，才会把该值赋给DETECT_MTU.ulResult字段 */
enum enumTrrtMtuErrInf
{
    TRRT_SUC_MTUCHANGE = 0,                             /* 0 探测路径MTU成功，且有更小的MTU */
    TRRT_SUC_MTUNOCHANGE,                               /* 1 探测路径MTU成功，路径中最小MTU和本接口MTU一致 */
    TRRT_ERR_DETECTMTU,                                 /* 2 探测路径MTU失败 */
};

typedef VOID (*TCPIP_TRRTOutput_HOOK_FUNC)(CHAR *pstBuf);

/* TraceRoute统计信息通知回调函数原型, 统计信息内存由VISP申请, 如果传出参数指针不为空, 则需要产品释放 */
typedef VOID (*TCPIP_TRRTSTAT_HOOK_FUNC)(TCPIP_TRRT_STAT_S *pstTRRTStat);

/*多任务统计信息通知回调函数原型, 统计信息内存由VISP申请, 如果传出参数指针不为空, 则需要产品释放 */
typedef VOID (*TCPIP_TRRTEXSTAT_HOOK_FUNC)(TCPIP_TRRT_STAT_S *pstTRRTStat, ULONG ulExecID);

typedef VOID (*TCPIP_TRRTDETECTMTU_HOOK_FUNC)(ULONG ulMtu);

typedef VOID (*TCPIP_TRRTExOutput_HOOK_FUNC)(ULONG ulExecID,CHAR *pstBuf);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncTRRTOutputHook
*  Description: TRACEROUTE信息输出适配函数注册接口
*        Input: TCPIP_TRRTOutput_HOOK_FUNC pfHookFuc:提供给用户注册的TRRT模块信息输出函数指针
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
extern ULONG TCPIP_RegFuncTRRTOutputHook(TCPIP_TRRTOutput_HOOK_FUNC pfHookFuc);

/*******************************************************************************
*    Func Name: TCPIP_Traceroute
*  Description: Traceroute功能函数
*        Input: TrrtCommonParam *pstTrrtParam:指向传入的结构体信息参数的指针
*       Output: 无
*       Return: 成功返回TRRT_SUCESS
*               失败返回enumTracertErrInf 中定义的错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_Traceroute(TrrtCommonParam *pstTrrtParam);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncTRRTStatHook
*  Description: 注册TraceRoute统计信息通知回调函数
*        Input: TCPIP_TRRTSTAT_HOOK_FUNC pfFunc: 回调函数
*       Output: 
*       Return: TRRT_API_PARA_WRONG：回调函数指针为空
*               VOS_OK：处理成功
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-10-21  wujie(61195)     Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncTRRTStatHook(TCPIP_TRRTSTAT_HOOK_FUNC pfFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncTRRTDetectMtuHook
* Date Created: 2009-03-25
*       Author: zhangchi00142640
*  Description: 注册TraceRouteMtu探测结果通知回调函数
*        Input: TCPIP_TRRTDETECTMTU_HOOK_FUNC pfFunc: 回调函数
*       Output: 
*       Return: TRRT_API_PARA_WRONG：回调函数指针为空
*               VOS_OK：处理成功
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-03-25   zhangchi00142640        Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncTRRTDetectMtuHook(TCPIP_TRRTDETECTMTU_HOOK_FUNC pfFunc);

/*****************************************************************************
 函 数 名  : TCPIP_RegFuncTRRTExOutputHook
 功能描述  : TRACEROUTE信息输出适配函数注册接口
 输入参数  : TCPIP_TRRTExOutput_HOOK_FUNC pfHookFuc 提供给用户注册的TRRT模块信息输出函数指针 
 输出参数  : 无
 返 回 值  : VOS_OK成功,其他返回失败
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2009年4月28日
    作    者   : w62223
    修改内容   : 新生成函数

*****************************************************************************/
extern ULONG TCPIP_RegFuncTRRTExOutputHook(TCPIP_TRRTExOutput_HOOK_FUNC pfHookFuc); 


/*****************************************************************************
 函 数 名  : TCPIP_TracerouteEx
 功能描述  : traceroute功能函数
 输入参数  : ULONG ulExecID :用户ID                
             TrrtCommonParam *pstTrrtParam  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2009年4月28日
    作    者   : w62223
    修改内容   : 新生成函数

*****************************************************************************/
extern ULONG TCPIP_TracerouteEx(ULONG ulExecID,TrrtCommonParam *pstTrrtParam) ;

/*******************************************************************************
*    Func Name: TCPIP_RegFuncTRRTExStatHook
* Date Created: 2009-12-17
*       Author: zhangchunyu(62474)
*  Description: 注册TraceRoute统计信息通知回调函数
*        Input: TCPIP_TRRTEXSTAT_HOOK_FUNC pfFunc: 
*       Output: 
*       Return: TRRT_API_PARA_WRONG：回调函数指针为空
*               TRRT_SUCESS：处理成功
*      Caution: 统计信息内存由VISP申请, 如果传出参数指针不为空, 则需要产品释放 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-12-17    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_RegFuncTRRTExStatHook(TCPIP_TRRTEXSTAT_HOOK_FUNC pfFunc);

/*******************************************************************************
*    Func Name: TCPIP_TrrtDetectPathMtu
* Date Created: 2010-08-21
*       Author: c168670
*      Purpose: 实现Traceroute功能，并且探测路径MTU
*  Description: 实现Traceroute功能，并且探测路径MTU
*        Input: ULONG ulExecID: 用户ID<ULONG范围>
*               TCPIP_TRRT_DETECTMTU_S *pstTrrtMtuParam: TRRT及探测MTU参数指针<非空>
*       Output: 对于探测MTU功能，输出DETECT_MTU结构
*       Return: 成功返回TRRT_SUCESS
*               失败返回enumTracertErrInf 中定义的错误码
*      Caution: 对于指定探测MTU,需要把探测开关ulDetectMtu置1，否则该接口只实现traceroute功能
*        Since: V200R003C02
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-08-21   c168670        Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_TrrtDetectPathMtu(ULONG ulExecID, TCPIP_TRRT_DETECTMTU_S *pstTrrtMtuParam);

/********************************************************************************** 
*    Func Name: TCPIP_TRRT_SetPortRange 
* Date Created: 2011-01-07 
*       Author: c168670(cKF34546) 
*      Purpose: 设置Traceroute目的端口号范围和默认端口号（主机序）
*  Description: 设置Traceroute目的端口号范围和默认端口号（主机序）
*        Input: USHORT usTrrtMinPort: 目的端口号下限<取值范围:[49152,65535]> 
*               USHORT usTrrtMaxPort: 目的端口号上限<取值范围:[usTrrtMinPort,65535]> 
*               USHORT usTrrtDefaultPort: 默认目的端口号<取值范围:[usTrrtMinPort,usTrrtMaxPort]>
*       Output: 
*       Return: 成功返回TRRT_SUCESS 
*               失败返回错误码
*      Caution: 端口上限不能小于端口下限，默认端口号在[端口下限，端口上限]范围内 
*        Since: V200R003C03 
*    Reference:  
*---------------------------------------------------------------------------------- 
*  Modification History 
*  DATE         NAME                    DESCRIPTION 
*  -------------------------------------------------------------------------------- 
*  2011-01-07   c168670(cKF34546)       Create the first version. 
* 
**********************************************************************************/
ULONG TCPIP_TRRT_SetPortRange(USHORT usTrrtMinPort, USHORT usTrrtMaxPort, USHORT usTrrtDefaultPort);

/********************************************************************************** 
*    Func Name: TCPIP_TRRT_GetPortRange 
* Date Created: 2011-01-07 
*       Author: c168670(cKF34546) 
*      Purpose: 获取Traceroute目的端口号范围和默认端口号（主机序）
*  Description: 获取Traceroute目的端口号范围和默认端口号（主机序）
*        Input: USHORT *pusTrrtMinPort: 目的端口号下限的指针 
*               USHORT *pusTrrtMaxPort: 目的端口号上限的指针
*               USHORT *pusTrrtDefaultPort: 默认目的端口号的指针
*       Output: 
*       Return: 成功返回TRRT_SUCESS 
*               失败返回错误码
*      Caution: 
*        Since: V200R003C03 
*    Reference:  
*---------------------------------------------------------------------------------- 
*  Modification History 
*  DATE         NAME                    DESCRIPTION 
*  -------------------------------------------------------------------------------- 
*  2011-01-07   c168670(cKF34546)       Create the first version. 
* 
**********************************************************************************/
ULONG TCPIP_TRRT_GetPortRange(USHORT *pusTrrtMinPort, USHORT *pusTrrtMaxPort, USHORT *pusTrrtDefaultPort);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* _TRRT_API_H_ */

