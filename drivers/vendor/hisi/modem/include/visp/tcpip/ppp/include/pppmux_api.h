/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              pppmux_api.h
*
*  Project Code: VISPV100R006C02
*   Module Name: PPPMUX  
*  Date Created: 2008-03-17
*        Author: chenfutian69112
*   Description: PPPMUX模块提供的对外数据结构定义和API声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-03-17   chenfutian69112         Create
*
*******************************************************************************/

#ifndef _PPPMUX_API_H_
#define _PPPMUX_API_H_


#ifdef  __cplusplus
extern "C"{
#endif

/**********************************************************************
*                        对外提供的数据结构
***********************************************************************/

/* PPPMUX配置参数数据结构 */
typedef struct tagPPPMUX_CONFIG_STRUCT
{
    ULONG ulMuxEnable;    /*是否使能PPPMux*/
    ULONG ulDefaultPID;   /*Default PID*/
    ULONG ulSubFrameLen;  /*最大子帧长度*/
    ULONG ulFrameLen;     /*最大复合帧长度*/
    ULONG ulSubFrameCount;/*最大子帧个数*/
    ULONG ulMuxDelay;     /*最大复合时延*/
}PPPMUXCONFIG_S;

/* PPPMUX统计信数据结构 */
typedef struct tagPPPMUX_STAT_STRUCT
{
    ULONG ulSendPackets;         /*发送报文总数*/
    ULONG ulSendSubFrames;       /*发送子帧总数*/
    ULONG ulSendBytes;           /*发送字节总数*/
    ULONG ulSendBytes_PayLoad;   /*净复合净荷字节数*/
    ULONG ulSendError;           /*报文复合错误数*/
    ULONG ulRecvPackets;         /*接收报文总数*/
    ULONG ulRecvSubFrames;       /*接收子帧总数*/
    ULONG ulRecvBytes;           /*接收字节总数*/
    ULONG ulRecvBytes_PayLoad;   /*解复合净荷字节数*/
    ULONG ulRecvError;           /*报文解复合错误数*/
    ULONG ulSendSingPkt;         /*发送的单报文,但打的是PPP头*/
}PPPMUXSTATS_S;

/* PPPMUXCP协商结果数据结构 */
typedef struct tagPPPMUXUP_NEGORESULT_STRUCT
{
    ULONG ulNegoDefaultPID;      /*是否协商PPPMux*/
    ULONG ulDefaultPID;          /*Default PID*/
}PPP_MUXCP_NEGORESULT_S;

/*如下全局变量是在用户在实现自定义的PPPMUX复合任务和定时器处理时，用来保存相关信息*/
/*严格来讲,VISP不应该向用户开放全局变量, 后续再考虑整改以解除依赖*/
extern ULONG g_ulPPPMUXTaskId;      /* PPPMUX复合任务ID */
extern ULONG g_ulPPPMUXTimerId;     /* PPPMUX定时器ID */
extern ULONG g_ulPPPMUXQueId;       /* PPPMUX定时器消息队列ID */


/**********************************************************************
*                        对外提供的类型定义和用户API声明
***********************************************************************/

typedef ULONG ( * QOSPacketClass_HOOK_FUNC)(ULONG ulIfIndex,MBUF_S* pstMBuf,UCHAR * pucClass);
typedef ULONG ( * CreatePPPMUXTimer_HOOK_FUNC)(VOID ( *pfTimerFunc )( VOID* ), VOID *pArg);
typedef ULONG ( * DeletePPPMUXTimer_HOOK_FUNC)(VOID);
typedef ULONG ( * PPPMUXTimerOut_HOOK_FUNC)(VOID *pArg );
typedef ULONG ( * PPPMUXSchedule_HOOK_FUNC)(ULONG ulArg0, ULONG ulArg1, ULONG ulArg2, ULONG ulArg3);

/*******************************************************************************
*    Func Name: TCPIP_ShowMuxConfig
*  Description: 显示指定接口的PPPMUX功能的配置参数
*        Input: CHAR *pszIfName:接口索引
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern VOID TCPIP_ShowMuxConfig(CHAR *pszIfName);
/*******************************************************************************
*    Func Name: TCPIP_ShowMUXNegoResultByIfName
*  Description: 显示指定接口的PPPMUXCP协商结果
*        Input: CHAR *pszIfName:接口名称
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern VOID TCPIP_ShowMUXNegoResultByIfName (CHAR *pszIfName);
/*******************************************************************************
*    Func Name: TCPIP_ShowMuxStat
*  Description: 显示指定接口的PPPMUX统计数据
*        Input: CHAR *pszIfName:接口指针
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern VOID TCPIP_ShowMuxStat(CHAR *pszIfName);
/*******************************************************************************
*    Func Name: TCPIP_ClrPppMuxStat
*  Description: 统计信息清零
*        Input: ULONG ulIfIndex:接口索引
*       Output: 
*       Return: VOS_OK                     成功
*               PPP_IFNETCB_NOEXIST        接口控制块不存在
*               PPP_NOENCAP_ERROR          接口不是PPP族接口
*               PPP_PPPCB_NOEXIST          PPP控制块不存在
*               PPP_WRONGPARA_ERROR        参数非法
*               PPP_MUX_DISABLE            PPPMUX功能未使能
*               PPP_MUX_CONTEXT_NOEXIST    PPPMUX上下文结构不存在
*               PPP_MUXCPCB_NOEXIST        PPPMUX控制块不存在
*               VOS_ERR                    接口索引非法
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_ClrPppMuxStat(ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_MuxcpPid
*  Description: 设置本端默认协议号
*        Input: ULONG ulIfIndex:接口索引
*               USHORT usDefaultPid:默认协议号
*               ULONG ulReset:设置标志，1 undo，0 不undo，其他非法
*       Output: 
*       Return: VOS_OK                              成功
*               PPP_IFNETCB_NOEXIST                 接口控制块不存在
*               PPP_NOENCAP_ERROR                   接口不是PPP族接口
*               PPP_PPPCB_NOEXIST                   PPP控制块不存在
*               PPP_CONFIGINFO_NOEXIST              配置控制块不存在
*               PPP_WRONGPARA_ERROR                 参数非法
*               PPP_HA_IS_SMOOTHING                 HA正在平滑处理或手动倒换处理
*               VOS_ERR                             接口索引非法
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_MuxcpPid (ULONG ulIfIndex, USHORT usDefaultPid, ULONG ulReset );
/*******************************************************************************
*    Func Name: TCPIP_SetMaxMuxframeLen
*  Description: 设置PPP复合帧最大长度
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulLength:最大复合帧长度，取值范围为3－1500
*       Output: 
*       Return: VOS_OK                       成功
*               PPP_HA_IS_SMOOTHING          HA正在平滑处理或手动倒换处理
*               PPP_WRONGPARA_ERROR          参数非法（指定长度值超出合法范围）
*               PPP_IFNETCB_NOEXIST          指定接口不存在
*               PPP_NOENCAP_ERROR            指定接口非PPP链路类型
*               PPP_PPPCB_NOEXIST            指定接口的PPP控制块不存在
*               PPP_CONFIGINFO_NOEXIST       指定接口的PPP配置控制块不存在
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetMaxMuxframeLen(ULONG ulIfIndex, ULONG ulLength);
/*******************************************************************************
*    Func Name: TCPIP_PppMux
*  Description: 设置接口使能/去使能PPPMUX功能
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulSetYes:使能/去使能标记(0 去使能，1 使能)
*       Output: 
*       Return: VOS_OK                    成功
*               PPP_IFNETCB_NOEXIST       接口控制块不存在
*               PPP_NOENCAP_ERROR         接口不是PPP族接口
*               PPP_PPPCB_NOEXIST         PPP控制块不存在
*               PPP_CONFIGINFO_NOEXIST    配置控制块不存在
*               PPP_WRONGPARA_ERROR       参数非法
*               PPP_HA_IS_SMOOTHING       HA正在平滑处理或手动倒换处理
*               VOS_ERR                   接口索引非法
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_PppMux ( ULONG ulIfIndex, ULONG ulSetYes );
/*******************************************************************************
*    Func Name: TCPIP_GetMuxConfig
*  Description: 查询PPPMUX功能相关的配置参数
*        Input: ULONG ulIfIndex:接口索引
*               PPPMUXCONFIG_S* pstMuxConfig:PPPMUX配置参数查询结果
*       Output: PPPMUXCONFIG_S* pstMuxConfig:PPPMUX配置参数查询结果
*       Return: VOS_OK                    成功
*               PPP_IFNETCB_NOEXIST       接口控制块不存在
*               PPP_NOENCAP_ERROR         接口不是PPP族接口
*               PPP_PPPCB_NOEXIST         PPP控制块不存在
*               PPP_CONFIGINFO_NOEXIST    配置控制块不存在
*               PPP_WRONGPARA_ERROR       参数非法
*               PPP_HA_IS_SMOOTHING       HA正在平滑处理或手动倒换处理
*               VOS_ERR                   接口索引非法
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_GetMuxConfig(ULONG ulIfIndex, PPPMUXCONFIG_S* pstMuxConfig);
/*******************************************************************************
*    Func Name: TCPIP_SetMuxOverTime
*  Description: 设置报文复合的最大时延
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulTime:报文复合时延(1～1000ms)
*       Output: 
*       Return: VOS_OK                          成功
*               PPP_IFNETCB_NOEXIST             接口控制块不存在
*               PPP_NOENCAP_ERROR               接口不是PPP族接口
*               PPP_PPPCB_NOEXIST               PPP控制块不存在
*               PPP_CONFIGINFO_NOEXIST          配置控制块不存在
*               PPP_WRONGPARA_ERROR             参数非法
*               PPP_HA_IS_SMOOTHING             HA正在平滑处理或手动倒换处理
*               VOS_ERR                         接口索引非法
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetMuxOverTime(ULONG ulIfIndex, ULONG ulTime);
/*******************************************************************************
*    Func Name: TCPIP_GetPppMuxStat
*  Description: 获取接口的PPPMUX统计信息
*        Input: ULONG ulIfIndex:接口索引
*               PPPMUXSTATS_S*  pstMuxStat:统计信息查询结果
*       Output: PPPMUXSTATS_S*  pstMuxStat:统计信息查询结果
*       Return: VOS_OK                   成功
*               PPP_IFNETCB_NOEXIST      接口控制块不存在
*               PPP_NOENCAP_ERROR        接口不是PPP族接口
*               PPP_PPPCB_NOEXIST        PPP控制块不存在
*               PPP_WRONGPARA_ERROR      参数非法
*               PPP_MUX_DISABLE          PPPMUX功能未使能
*               PPP_MUXCPCB_NOEXIST      PPPMUX控制块不存在
*               PPP_MUX_CONTEXT_NOEXIST  PPPMUX上下文结构不存在
*               VOS_ERR                  接口索引非法
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPppMuxStat(ULONG ulIfIndex, PPPMUXSTATS_S*  pstMuxStat);
/*******************************************************************************
*    Func Name: TCPIP_GetMuxNegoResult
*  Description: 查询PPPMUXCP协议协商结果
*        Input: ULONG ulIfIndex:接口索引
*               PPP_MUXCP_NEGORESULT_S *pstOur:本端协商结果
*               PPP_MUXCP_NEGORESULT_S *pstHis:对端协商结果
*       Output: PPP_MUXCP_NEGORESULT_S *pstOur:本端协商结果
*               PPP_MUXCP_NEGORESULT_S *pstHis:对端协商结果
*       Return: VOS_OK                    成功
*               PPP_IFNETCB_NOEXIST       接口不存在
*               PPP_NOENCAP_ERROR         指定接口非PPP类型接口
*               PPP_PPPCB_NOEXIST         指定接口的PPP控制块不存在
*               PPP_WRONGPARA_ERROR       参数非法
*               PPP_MUXCPCB_NOEXIST       PPPMUX控制块不存在
*               PPP_FSMSTATE_ERR          Mux协议状态错误（没有通过协商）
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_GetMuxNegoResult(ULONG ulIfIndex, PPP_MUXCP_NEGORESULT_S *pstOur, PPP_MUXCP_NEGORESULT_S *pstHis);
/*******************************************************************************
*    Func Name: TCPIP_SetMuxSubFrameCount
*  Description: 设置一个复合报文中最多包含的子帧数目
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulSubFrameCount:最大子帧数(1~15)
*       Output: 
*       Return: VOS_OK                  成功
*               PPP_IFNETCB_NOEXIST     接口控制块不存在
*               PPP_NOENCAP_ERROR       接口不是PPP族接口
*               PPP_PPPCB_NOEXIST       PPP控制块不存在
*               PPP_CONFIGINFO_NOEXIST  配置控制块不存在
*               PPP_WRONGPARA_ERROR     参数非法
*               PPP_HA_IS_SMOOTHING     HA正在平滑处理或手动倒换处理
*               VOS_ERR                 接口索引非法
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetMuxSubFrameCount(ULONG ulIfIndex, ULONG ulSubFrameCount);
/*******************************************************************************
*    Func Name: TCPIP_SetMuxMaxSubframeLen
*  Description: 设置子帧最大长度
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulLength:子帧长度(1~512)
*       Output: 
*       Return: VOS_OK                    成功
*               PPP_IFNETCB_NOEXIST       接口控制块不存在
*               PPP_NOENCAP_ERROR         接口不是PPP族接口。
*               PPP_PPPCB_NOEXIST         PPP控制块不存在
*               PPP_CONFIGINFO_NOEXIST    配置控制块不存在
*               PPP_WRONGPARA_ERROR       参数非法
*               PPP_HA_IS_SMOOTHING       HA正在平滑处理或手动倒换处理
*               VOS_ERR                   接口索引非法
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetMuxMaxSubframeLen(ULONG ulIfIndex, ULONG ulLength);
/*******************************************************************************
*    Func Name: TCPIP_SetMuxMaxSubframeLenEx
* Date Created: 2013-03-05
*       Author: luogaowei
*  Description: MBSC需求PPPMUX最大子帧长度规格扩展
*        Input: ULONG ulIfIndex:ppp接口索引值
*               ULONG ulLength:最大子帧长度(范围1~1498)
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-03-05   luogaowei               Create     DTS2013030608162
*
*******************************************************************************/
ULONG TCPIP_SetMuxMaxSubframeLenEx(ULONG ulIfIndex, ULONG ulLength);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncQOSPacketClassHook
*  Description: 根据报文获取MC Class的注册接口,此钩子由用户适配注册后,由PPPMUX模块调用
*        Input: QOSPacketClass_HOOK_FUNC pfHookFunc:函数钩子指针
*       Output: 无
*       Return: 成功VOS_OK,失败VOS_ERR
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncQOSPacketClassHook(QOSPacketClass_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncCreatePPPMUXTimerHook
*  Description: 创建PPPMUX复合定时器函数
*        Input: CreatePPPMUXTimer_HOOK_FUNC pfHookFunc:函数钩子
*       Output: 
*       Return: VOS_OK                      成功
*      Caution: VRP_EVENT_TIMERREQ 产品向VISP写的事件；g_ulPppmuxTimerID 定时器ID;g_ulTaskID 任务ID.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncCreatePPPMUXTimerHook(CreatePPPMUXTimer_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncDeletePPPMUXTimer
*  Description: 删除PPPMUX复合定时器函数
*        Input: DeletePPPMUXTimer_HOOK_FUNC pfHookFunc:函数钩子
*       Output: 
*       Return: VOS_OK                         成功
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncDeletePPPMUXTimer(DeletePPPMUXTimer_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncPPPMUXTimerOutHook
*  Description: PPPMUX定时器超时函数
*        Input: PPPMUXTimerOut_HOOK_FUNC pfHookFunc:函数钩子
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncPPPMUXTimerOutHook(PPPMUXTimerOut_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncPPPMUXScheduleHook
*  Description: PPPMUX复合任务的主函数
*        Input: PPPMUXSchedule_HOOK_FUNC pfHookFunc:函数钩子
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncPPPMUXScheduleHook(PPPMUXSchedule_HOOK_FUNC pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_ScanAndSendMuxPacket
*  Description: 扫描所有未发送的PPP复合报文，如果报文超过最大复合时延，发送报文
*        Input: 无
*       Output: 无
*       Return: VOID
*      Caution: 供PPPMUX定时器超时处理函数调用
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-07-01   wuhailan                Create
*
*******************************************************************************/
extern VOID TCPIP_ScanAndSendMuxPacket(VOID);

#ifdef __cplusplus
}
#endif


#endif

