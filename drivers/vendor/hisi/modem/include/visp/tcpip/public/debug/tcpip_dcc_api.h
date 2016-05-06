/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_pcap_api.h
*
*  Project Code: VISPV1R8C01
*   Module Name: DCC Debug
*  Date Created: 2009-04-11
*        Author: zhangchunyu62474
*   Description: DCC 对外头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-04-11   zhangchunyu62474          Create
*
*******************************************************************************/
#ifndef __TCPIP_DCC_API_H__
#define __TCPIP_DCC_API_H__

#ifdef __cplusplus
extern "C"{
#endif

#define MAX_VRFNAME_LEN    47
#define MAX_INTFNAME_LEN   31

#define DCC_TCP            6         
#define DCC_UDP            17

/* 数据连通性DCC用户输入数据结构 */
typedef struct tagDccInfo
{
    ULONG   ulSipAddr;                               /* 源地址,主机序 */
    ULONG   ulDipAddr;                               /* 目的地址,主机序 */
    USHORT  usSport;                                 /* 源端口号 */
    USHORT  usDport;                                 /* 目的端口号 */
    ULONG   ulSocketID;                              /* Socket ID*/
    ULONG   ulTaskID;                                /* Socket所属任务,基于全局socket可以不指定 */
    ULONG   ulProType;                               /* 协议类型 */
    CHAR    ucVrfName[MAX_VRFNAME_LEN+1];            /* 实例名称 */
    CHAR    ucIntfName[MAX_INTFNAME_LEN+1];          /* 接口名 */
}TCPIP_DCC_S;

/* 数据连通性DCC返回值 */
typedef enum enumDccErrCode
{
    DCC_SUCCESS = VOS_OK,           /* 0, 成功*/
    DCC_FAILED,                     /* 1, 失败*/
    DCC_ERR_NULLPOINT,              /* 2, 用户输入指针为空 */
    DCC_ERR_GETCOMVTBL,             /* 3, 获取组件失败 */
    DCC_ERR_IPALL,                  /* 4, 只指定源或目的IP,源IP和目的IP必须都指定 */
    DCC_ERR_WRITEQUE,               /* 5, 写队列失败,队列已满 */
    DCC_ERR_NOVRF,                  /* 6, VRF不存在*/
    DCC_ERR_NOINTF,                 /* 7,接口不存在 */
    DCC_ERR_INIT,                   /* 8,DCC初始化失败 */
    DCC_ERR_SIP,                    /* 9,源地址不合法 */
    DCC_ERR_DIP,                    /* 10,目的地址不合法 */
    DCC_ERR_DIPISLOC,               /* 11,目的地址不能是本机地址 */
    DCC_ERR_SIPNOTLOC,              /* 12,源地址不是本机地址 */
    DCC_ERR_INTFTYPR,               /* 13,不支持接口类型,只支持PPP ETH MP */
    DCC_ERR_RUNNING,                /* 14,DCC任务正在运行 */
    DCC_ERR_CREATETIMER,            /* 15,创建定时器失败*/
    DCC_ERR_CREATETASK,             /* 16,创建DCC任务失败*/
    DCC_ERR_CREATEQUE,              /* 17,创建DCC QUE任务失败*/
    DCC_ERR_NORUNNING,              /* 18,没有DCC任务在运行 */
    DCC_ERR_TASKPRI,                /* 19,DCC任务优先级大于255 */
    DCC_ERR_L2TYPR,                 /* 20,不支持二层ETH接口 */
    DCC_ERR_TRUNKPORT,              /* 21,不支持TRUNK成员子端口 */
    DCC_ERR_DATATIME,               /* 22,数据统计时间大于600 */
    DCC_ERR_EXECID,                 /* 23,用户执行ID不能为0 */
    DCC_ERR_NOSUCHEXECID,           /* 24,不存在相关执行ID的DCC */
    DCC_ERR_ISHEALTHCHECK,          /* 25,DCC正在做内部健康检查 */
    DCC_ERR_3DVIRTUALINTF,          /* 26,不支持3维虚接口检查 */
    
    DCC_ERR_MAX,                    /*上限值 */
}TCPIP_DCC_ERR_CODE_E;

/* 诊断类型 */
typedef enum enumDiagnoseTypeID
{
    DCC_DIAGNOSE_NA = 0,               /* 0 无错误正常的诊断信息 */
    DCC_START,                         /* 1 DCC诊断开始字段 */
    DCC_END,                           /* 2 DCC诊断结束标记 */
    
    DCC_DIAGNOSE_PHYDOWN,              /* 3 底层状态是Down */
    DCC_DIAGNOSE_NOARP,                /* 4 ARP学习不成功 */
    DCC_DIAGNOSE_ETHLINEDOWN,          /* 5 ETH接口协议DOWN */
    DCC_DIAGNOSE_LCPDOWN,              /* 6 LCP不是OPEN状态 */
    DCC_DIAGNOSE_IPCPDOWN,             /* 7 IPCP不是OPEN状态 */
    DCC_DIAGNOSE_NOFIB,                /* 8路由查找不成功 */
    DCC_DIAGNOSE_TRUNKLINEDOWN,        /* 9 TRUNK接口协议状态不是UP */
    DCC_DIAGNOSE_INNERERR,             /* 10 内部异常 */    
    DCC_DIAGNOSE_TCP_NOINPCB,          /* 11 INPCB不存在 */
    DCC_DIAGNOSE_TCP_NOTCPCB,          /* 12 TCPCB不存在 */
    DCC_DIAGNOSE_TCP_NOSOCKETCB,       /* 13 SOCKETCB不存在 */
    DCC_DIAGNOSE_NOSOCKET,             /* 14 根据socket id找不到socket,或者该socket类型与用户指定的不匹配 */
    DCC_DIAGNOSE_NONTCP_NOSOCKETCB,    /* 15 非TCP SOCKET控制块不存在,内部异常 */
    DCC_DIAGNOSE_CREATEDCCDATATIME,    /* 16 创建DCC数据统计定时器失败 */
    DCC_DIAGNOSE_MISMATCHPROTOTYPE,    /* 17 用户输入和检查到的协议类型不一致 */
    DCC_DIAGNOSE_DELETE_INTF,          /* 18 诊断过程时,接口被删除 */
    
    DCC_DIAGNOSE_MAX,                  /*  诊断类型最大值 */
    
}TCPIP_DCC_DIAGNOSEINFO_TYPE_E;


/*******************************************************************************
*    Func Name: TCPIP_DCC
* Date Created: 2009-3-26
*       Author: zhangchunyu(62474)
*  Description: 数据连通性检查用户接口
*        Input: ULONG ulExecID: 用户执行ID,输出结果会返回给用户
*               ULONG ulTaskPri:DCC任务优先级,0表示和sock任务优先级一致
*               ULONG ulDataStatTime: 数据统计时间,单位s,如果是0,表示默认30s
*               TCPIP_DCC_S *pstDcc: 用户输入数据连通性参数
*       Output: 
*       Return: DCC_SUCCESS:成功, 其他:失败
*      Caution: 数据连通性检查包括健康检查和数据统计
*               健康检查主要检查该数据流在VISP能否运行,包括MAC PING和IP PING,
*                   这两个操作会占用20s.
*               数据统计在健康检查之后,统计时间是用户指定,当时间到,根据统计信息
*                   输出该数据流在协议栈数据统计信息。
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-3-26    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_DCC(ULONG ulExecID, ULONG ulTaskPri, ULONG ulDataStatTime, TCPIP_DCC_S *pstDcc);

/*******************************************************************************
*    Func Name: TCPIP_StopDCC
* Date Created: 2009-3-27
*       Author: zhangchunyu(62474)
*  Description: 取消本次数据连通性检测
*        Input: ULONG ulExecID: 
*       Output: 
*       Return: DCC_SUCCESS 成功;DCC_FAILED 没有启动过数据连通探测
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-3-27    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_StopDCC(ULONG ulExecID);
/*******************************************************************************
*    Func Name: TCPIP_ShowDCCCfgInfo
* Date Created: 2009-4-22
*       Author: zhangchunyu(62474)
*  Description: 显示DCC诊断类型设置的相关信息
*        Input: ULONG ulExecID: 用户执行ID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-4-22    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_ShowDCCCfgInfo(ULONG ulExecID);

#ifdef __cplusplus
}
#endif      /* end of __cplusplus   */

#endif /* __TCPIP_PCAP_API_H__ */


