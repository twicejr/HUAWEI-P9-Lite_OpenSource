/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              poec_api.h
*
*  Project Code: VISPV100R007
*   Module Name: POEC
*  Date Created: 2008-03-22
*        Author: luowentong105073
*   Description: poec api 头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-03-22   luowentong105073        Create
*
*******************************************************************************/
#ifndef _POEC_API_H_
#define _POEC_API_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/*注意:
如果修改错误码，请同步修改poec_sh_err.c 文件中的
char * Inf_PPPOE_Client_En[]描述信息*/
typedef enum tagPOEC_EXEC_INFO_INDEX
{
    PPPOE_CLIENT_OK = 0,                /* 0.成功 */
    PPPOE_CLIENT_ERR,                   /* 1.失败 */
    PPPOE_CLIENT_NO_SESSION_ON_ETH,     /* 2.当前的以太口没有可删除的会话 */
    PPPOE_CLIENT_NO_SUCH_SESSION,       /* 3.没有指定的session存在 */
    PPPOE_CLIENT_BUNDLE_NUMBER_USED,    /* 4.指定的Bundle号已经被使用, 请选择其他的Bundle号 */
    PPPOE_CLIENT_DEBUG_NO_ETH_ERROR,    /* 5.没有以太口 */
    PPPOE_CLIENT_DEBUG_NOT_ETH_TYPE,    /* 6.不是以太类型 */
    PPPOE_CLIENT_NO_SESSSION_RESET,     /* 7.没有可重启的会话 */
    PPPOE_CLIENT_CONFIG_RUNNING_SERVER, /* 8.接口上配置了POES，不能配置POEC */
    PPPOE_CLIENT_CONFIG_NOPVC_ATTACHED, /* 9.虚拟以太网没有和pvc关联上 */
    PPPOE_CLIENT_SESSION_NUMBER_MAX,    /* 10.会话数已满 */
    PPPOE_CLIENT_CONFIG_NO_NUMBER,      /* 11.没有可用的绑定号 */
    PPPOE_CLIENT_CREATE_SESSION_FAIL,   /* 12.创建POEC会话失败 */
    PPPOE_CLIENT_NO_DIALER,             /* 13.该接口不是Dialer口 */
    PPPOE_CLIENT_NO_PPPINFO_EXIST,      /* 14. 相应的ppp控制块不存在"*/
    PPPOE_CLIENT_BUNDLE_NUMBER_EXIST,   /* 15.Dialer口已经配置了BundleNumber */   
    PPPOE_CLIENT_BUNDLENUM_BEYOND,      /* 16.所设置的BundleNumber值越界了 */

    PPPOE_CLIENT_PAPA_NULLPOINTER,      /* 17.输入参数为空指针 */
    PPPOE_CLIENT_BUNDLE_INTNUM_DISACCORD,/*18.当系统存在没有用于PPPoE的Dialer接口时，或有的Dialer接口编号与绑定不一致 */
    PPPOE_CLIENT_INTF_INVALID,          /* 19.指定的接口索引无效 */
    PPPOE_CLIENT_HA_IS_SMOOTHING,       /* 20.HA正在平滑处理或手动倒换处理 */

    PPPOE_CLIENT_IS_SERVER,             /* 21.接口已经使能了PPPoE Server */
    PPPOE_CLIENT_IS_TRUNKPORT,          /* 22.接口是Trunk成员端口 */ 

    PPPOE_CLENET_NOTINIT,               /* 23.POEC模块未初始化 */
    
    PPPOE_CLIENT_IS_VIRTUAL_PORT,       /* 24.三维虚拟接口 */
    
    PPPOE_CLIENT_ERR_DIALER_DOWN,       /* 25.PPPOE Dialer接口DOWN*/
    PPPOE_CLIENT_ERR_NO_BUNDNUM,        /* 26.对应的接口索引不存在对应的绑定号 */
    PPPOE_CLIENT_ERR_NO_SESSION,        /* 27.获取Session控制块*/
    PPPOE_CLIENT_ERR_NO_ETHIF,          /* 28.没有对应的PPPOE会话信息*/

    PPPOE_CLIENT_DEBUG_NO_DIALER_ERROR, /* 29.没有Dialer口 */
    PPPOE_CLIENT_DEBUG_NOT_DIALER_TYPE, /* 30 .不是Dialer 接口类型 */

    PPPOE_CLIENT_IS_L2ETHORVLAN_TYPE,   /* 31.二层端口类型或VLANIF接口暂不支持POEC */
    PPPOE_CLIENT_COPY_SESSIONINFO_FAIL, /* 32.拷贝会话信息失败 */
    PPPOE_CLIENT_GR_STATE,              /* 33.PPPOE全局保活模式不正确，不允许配置 */
    PPPOE_CLIENT_SESSION_CFG_GR_STATE,  /* 34.配置的PPPOE会话保活模式不正确，不允许配置 */
    PPPOE_CLIENT_SESSION_CFG_NEGO_STATE,/* 35.配置的PPPOE会话协商状态不满足，不允许配置 */
    PPPOE_CLIENT_SESSION_NEGO_STATE,    /* 36.从底层NP获取到的PPPOE会话协商状态不满足，不允许配置 */
    PPPOE_CLIENT_PPI_HOOK_NULL,         /* 37.未注册PPI钩子 */
    PPPOE_CLIENT_ETHIF_PHY_NOTUP,       /* 38.以太接口的物理状态不是UP的 */
    PPPOE_CLIENT_SAME_SESSION,          /* 39.已经存在相同的PPPOE会话 */
    PPPOE_CLIENT_NP_MAC_INVALID,        /* 40.底层的会话信息中保存的physical地址非法 */
    PPPOE_CLIENT_NP_MAC_DIFF,           /* 41.底层的会话信息中保存的本端MAC地和上层Eth接口的physical地址不一致 */
    PPPOE_CLIENT_CREATE_VA_FAIL,        /* 42.创建VA接口失败 */
    PPPOE_CLIENT_CB_NULL,               /* 43.Client CB为空 */
    PPPOE_CLIENT_WRITE_QUE,             /* 44.写队列失败 */
    PPPOE_CLIENT_NO_ETH_CB,             /* 45.指定的ETH口无ETH控制块 */
    PPPOE_CLIENT_PARA_INVALID,          /* 46.入参无效 */
    PPPOE_CLIENT_MALLOC_FAIL,           /* 47.申请内存失败 */
    PPPOE_CLIENT_GET_NP_INFO_FAIL,      /* 48.从NP获取会话信息失败 */
    PPPOE_CLIENT_SUBIF,                 /* 49.子接口不支持该操作 */
    PPPOE_CLIENT_NUMBER_BEYOND,         /* 50.指定的端口号超过最大值 */
    
    PPPOE_CLIENT_EXEC_INFO_INDEX_MAX    /*Just for Offside Judging. NO accroding info. z36377*/
    
}POEC_EXEC_INFO_INDEX_EN;
/*注意:
如果修改错误码，请同步修改poec_sh_err.c 文件中的
char * Inf_PPPOE_Client_En[]描述信息*/




/*ethernet mac 地址长度*/
#define PPPOE_MAC_LEN           6

typedef struct tagPOECSTAT_S
{
    USHORT usSessionId;
    UCHAR  ucSessionPhase;
    UCHAR  ucPad;
    UCHAR  aucLocalMac[PPPOE_MAC_LEN];
    UCHAR  aucRemoteMac[PPPOE_MAC_LEN];
    ULONG  ulSendPkt;
    ULONG  ulRecvPkt;
    ULONG  ulSendFlow;
    ULONG  ulRecvFlow;
} POECSTAT_S;

/* 获取的PPPOE session信息 */
typedef struct tagPPPOE_C_SESSION_S
{
    ULONG   ulEthIfIndex;                 /* PPPOE接口对应的以太接口索引*/
    ULONG   ulSessionId;                  /* PPPOE Session的ID */
    UCHAR   szOurMacAddr[PPPOE_MAC_LEN];  /*Client physical地址 */
    UCHAR   szHisMacAddr[PPPOE_MAC_LEN];  /*Server physical地址 */
}TCPIP_PPPOE_C_SESSION_S;

/* PPPOE client在进入/退出session阶段时调用钩子函数通知产品
   入参说明:
   ulDialerIfIndex: dialer接口索引
    ulSessionPhase: 0 进入session阶段  1 退出session阶段
    pstSessionInfo: PPPOE会话信息, 指针指向的内存由VISP申请和释放
   返回值说明:
     0  钩子函数处理成功
   其他 钩子函数处理失败, VISP记录日志 */
typedef ULONG (*POEC_PHASE_NOTIFY)(ULONG ulDialerIfIndex, ULONG ulSessionPhase, TCPIP_PPPOE_C_SESSION_S *pstSessionInfo);

/*******************************************************************************
*    Func Name: TCPIP_ClrPoecIntfStat
*  Description: Clear the statistical information of the appointed session
*        Input: ULONG ulPoecIfIndex:dialer口索引
*       Output:
*       Return: 成功返回VOS_OK，否则返回错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_ClrPoecIntfStat(ULONG ulPoecIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_CreatePoecIntf
*  Description: 创建PPPoE Client接口
*        Input: 
*       Output: pulPoecIfIndex: 保存创建的接口的索引
*       Return: SUCCESS     VOS_OK, FAILURE     error code
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_CreatePoecIntf(ULONG *pulPoecIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_CreatePoecIntfByNum
* Date Created: 2011-04-21
*       Author: zhaoyue00171897
*  Description: 根据接口号创建PPPoE Client接口
*        Input: ULONG ulPortNo: 指定的Dialer端口号(输入零表示按默认方式创建)
*       Output: pulPoecIfIndex: 保存创建的接口的索引
*       Return: SUCCESS     VOS_OK, FAILURE     error code
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-04-21   zhaoyue00171897         Create
*
*******************************************************************************/
extern ULONG TCPIP_CreatePoecIntfByNum(ULONG *pulPoecIfIndex, ULONG ulPortNo);
/*******************************************************************************
*    Func Name: TCPIP_DebugPoecAll
*  Description: 打开所有调试开关
*        Input: 
*       Output: 
*       Return: VOS_OK: 处理成功
*               POECNOTINIT:POEC组件未初始化
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_DebugPoecAll(VOID);
/*******************************************************************************
*    Func Name: TCPIP_DelPoecIntf
*  Description: 删除PPPoE Client接口，有共享数据互斥保护
*        Input: ulPoecIfIndex: 要删除的接口的索引
*       Output: None
*       Return: SUCCESS     VOS_OK,
*               FAILURE     error code
*      Caution: None
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_DelPoecIntf(ULONG ulPoecIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_GetPoecHADbg
*  Description: 获取PPPoE HA调试开关状态
*        Input:
*       Output: ULONG *pulRet: 调试开关状态
*       Return: VOS_OK(0)        成功
*               VOS_ERR(1)       失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPoecHADbg(ULONG *pulRet);
/*******************************************************************************
*    Func Name: TCPIP_GetPoecIntfStat
*  Description: 获得Poec虚接口上的统计信息
*        Input : ulPoecIfIndex：PPPOE虚接口索引
*       Output : *pstStat：PPPOE虚接口的统计信息
*       Return : 成功返回VOS_OK
*              : 失败返回“错误码”
*      Caution:  POECSTAT_S结构定义如下：
*              : typedef struct tagPOECSTAT_S
*              : {
*              :     USHORT usSessionId;
*              :     UCHAR ucSessionPhase;
*              :     UCHAR ucReserve;
*              :     UCHAR aucLocalMac[6];
*              :     UCHAR aucRemoteMac[6];
*              :     ULONG ulSendPkt;
*              :     ULONG ulRecvPkt;
*              :     ULONG ulSendFlow;
*              :     ULONG ulRecvFlow;
*              : } POECSTAT_S;
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPoecIntfStat(ULONG ulPoecIfIndex, POECSTAT_S *pstStat);
/*******************************************************************************
*    Func Name: TCPIP_NoDebugPoecAll
*  Description: 关闭所有调试开关
*        Input: 
*       Output: 
*       Return: VOS_OK: 处理成功
*               POECNOTINIT:POEC组件未初始化
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_NoDebugPoecAll(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ResetPoecSession
*  Description: 被命令行调用用以清除某一个PPPoE Client会话
*        Input: ULONG ulPoecIfIndex:PPP接口索引
*       Output: 
*       Return: 成功返回VOS_OK，否则返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_ResetPoecSession(ULONG ulPoecIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_ResetPoecSessionAll
*  Description: 被命令行调用用以清除所有PPPoE Client会话
*        Input: 
*       Output: 
*       Return: 成功返回VOS_OK，否则返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_ResetPoecSessionAll(VOID);
/*******************************************************************************
*    Func Name: TCPIP_SetPoecHADbg
*  Description: 设置PPPoE模块HA的调试开关状态
*        Input: ULONG ulDbg: 开关状态   1：打开    0：关闭
*       Output:
*       Return: VOS_OK（0）        成功
*               VOS_ERR（1）       失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPoecHADbg(ULONG ulDbg);
/*******************************************************************************
*    Func Name: TCPIP_ShowPOECInfoByIfName
*  Description: 通过封装现有函数实现PPPOE Client Session信息的查询，如PPPOE Client Session标题。
*        Input: CHAR *pszIfName:接口名
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern VOID  TCPIP_ShowPOECInfoByIfName(CHAR *pszIfName);
/*******************************************************************************
*    Func Name: TCPIP_ShowPoecSessionInfo
*  Description: 显示所有的PPPoE client会话信息接口
*        Input: 
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   luowentong105073        Create
*
*******************************************************************************/
extern VOID  TCPIP_ShowPoecSessionInfo(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ShowPoecStatistic
*  Description: 打印POEC模块统计信息
*        Input: CHAR *pName:
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
extern VOID  TCPIP_ShowPoecStatistic(CHAR *pName);
/*******************************************************************************
*    Func Name: TCPIP_StartPoecSession
*  Description: 在以太口上启动PPPOE会话
*        Input: ULONG ulEthIfIndex: 以太网接口索引
*               ULONG ulPoecIfIndex: PPPoE Client接口索引
*       Output: None
*       Return: SUCCESS     VOS_OK, FAILURE     error code
*      Caution: None
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_StartPoecSession(ULONG ulEthIfIndex, ULONG ulPoecIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_StopPoecSession
*  Description: 在以太口上关闭PPPOE会话，有共享数据互斥保护
*        Input: ULONG ulEthIfIndex: 以太网接口索引
*               ULONG ulPoecIfIndex: PPPoE Client接口索引
*       Output: None
*       Return: SUCCESS     VOS_OK, FAILURE     error code
*      Caution: None
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_StopPoecSession(ULONG ulEthIfIndex, ULONG ulPoecIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_GetPoecSessionInfo
*  Description: 获取Session控制块信息
*        Input: ULONG ulPoecIfIndex:接口索引
*       Output: TCPIP_PPPOE_C_SESSION_S *pstSessionInfo:控制块信息
*       Return: VOS_OK  成功
*               error code 失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-16   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPoecSessionInfo (ULONG ulPoecIfIndex, TCPIP_PPPOE_C_SESSION_S *pstSessionInfo );

/*******************************************************************************
*    Func Name: TCPIP_RegFuncPoecPhaseNotify
*  Description: 注册钩子函数, PPPOE client在进入/退出session阶段时调用钩子函数通知产品
*        Input: POEC_PHASE_NOTIFY pfHook: 钩子函数指针
*       Output: 
*       Return: VOS_OK   成功
*               VOS_ERR  钩子函数指针为空
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-10-24  wujie(61195)     Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncPoecPhaseNotify(POEC_PHASE_NOTIFY pfHook);

/*******************************************************************************
*    Func Name: TCPIP_SetPoecDebugFlag
* Date Created: 2010-02-05
*       Author: z00104207
*  Description: 设置POEC调试开关，支持分别基于ETH接口和基于Dialer接口
*        Input: ULONG ulDialerIfIndex: Dialer接口的接口索引
*               ULONG ulEthIfIndex:    Eth接口的接口索引
*               ULONG ulFlag:          调试开关
*       Output: 
*       Return: 成功则返回VOS_OK，否则返回其他错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-02-05   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPoecDebugFlag(ULONG ulDialerIfIndex, ULONG ulEthIfIndex, ULONG ulFlag);

/*******************************************************************************
*    Func Name: TCPIP_GetPoecDebugFlag
* Date Created: 2010-02-05
*       Author: z00104207
*  Description: 获取POEC调试开关
*        Input: ULONG ulDialerIfIndex: Dialer接口的接口索引
*               ULONG ulEthIfIndex:    Eth接口的接口索引
*       Output: ULONG *pulFlag:        调试开关取值
*       Return: 成功则返回VOS_OK，否则返回其他错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-02-05   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPoecDebugFlag(ULONG ulDialerIfIndex, ULONG ulEthIfIndex, ULONG *pulFlag);

/*******************************************************************************
*    Func Name: TCPIP_GR_POECRestore
* Date Created: 2010-02-05
*       Author: z00104207
*  Description: 向SOCK任务写事件，通知进行POEC保活处理
*        Input: VOID
*       Output: 
*       Return: 成功则返回VOS_OK，否则返回其他错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-02-05   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_GR_POECRestore(VOID);

/*******************************************************************************
*    Func Name: TCPIP_GR_POECSmooth
* Date Created: 2010-02-05
*       Author: z00104207
*  Description: 向SOCK任务写事件，通知进行POEC保活平滑处理
*        Input: VOID
*       Output: 
*       Return: 成功则返回VOS_OK，否则返回其他错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-02-05   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_GR_POECSmooth(VOID);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _POEC_API_H_ */

