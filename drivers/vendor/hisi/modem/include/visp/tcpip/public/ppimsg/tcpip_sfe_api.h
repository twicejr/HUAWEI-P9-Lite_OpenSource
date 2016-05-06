/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_sfe_api.h
*
*  Project Code: VISPV100R008C02
*   Module Name: 
*  Date Created: 2009-8-20
*        Author: zhangchunyu(62474)
*   Description: 控制面到数据面API
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                                   DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2009-8-20  zhangchunyu(62474)         Create the first version.
*
*******************************************************************************/
#ifndef _TCPIP_SFE_API_H_
#define _TCPIP_SFE_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

#include "tcpip/public/ppimsg/tcpip_sfe_share_api.h"
#include "tcpip/bfd/include/bfd_cbb_api.h"

typedef UINT32 (*g_pfSendMsgToSFE)(VOID * pMsg, UINT32 u32Len);
typedef UINT32 (*g_pfRecvMsgFromSFE)(VOID *pMsgBuf, UINT32 *u32Len);
typedef VOID * (*g_pfAllocMsg)(UINT32 ulLength);
typedef UINT32 (*g_pfFreeMsg)(VOID *pMsg);

typedef UINT32 (*PF_FILTER_ROUTE4)(PPI_RTMSG4_S *pstPpiRoute);

/*******************************************************************************
*    Func Name: TCPIP_RegRecvMsgFromSFE
* Date Created: 2009-8-20
*       Author: zhangchunyu(62474)
*  Description: 产品注册控制面接收数据面数据接口
*        Input: g_pfRecvMsgFromSFE *pfFunc:  注册函数 
*       Output: 
*       Return: 成功: TCPIP_SFE_COM_SUCCESS 其他: 失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-20    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_RegRecvMsgFromSFE(g_pfRecvMsgFromSFE pstFun);

/*******************************************************************************
*    Func Name: TCPIP_RegSendMsgToSFE
* Date Created: 2009-8-20
*       Author: zhangchunyu(62474)
*  Description: 产品注册控制面到数据面发送接口
*        Input: g_pfSendMsgToSFE *pfFunc: 注册函数 
*       Output: 
*       Return: 成功: TCPIP_SFE_COM_SUCCESS 其他: 失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-20    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_RegSendMsgToSFE(g_pfSendMsgToSFE pstFun);

/*******************************************************************************
*    Func Name: TCPIP_RegFreeMsg
* Date Created: 2009-8-20
*       Author: zhangchunyu(62474)
*  Description: 释放数据面申请的内存
*        Input: g_pfFreeMsg pfFunc: 回调函数
*       Output: 
*       Return: 成功: TCPIP_SFE_COM_SUCCESS 其他: 失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-20    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_RegFreeMsg(g_pfFreeMsg pfFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegAllocMsg
* Date Created: 2009-8-20
*       Author: zhangchunyu(62474)
*  Description: 注册申请数据面到控制面内存
*        Input: g_pfAllocMsg pfFunc: 
*       Output: 
*       Return: 成功: TCPIP_SFE_COM_SUCCESS 其他: 失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-20    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_RegAllocMsg(g_pfAllocMsg pfFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegFilterFib4
* Date Created: 2009-8-29
*       Author: zhangchunyu(62474)
*  Description: 路由过滤回调接口
*        Input: PF_FILTER_ROUTE4 pfFunc: 注册回调函数
*       Output: pfFunc函数返回结果:1表示不下发,0表示下发
*       Return: TCPIP_RT_SUCCESS:成功 其他:失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-29    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_RegFilterFib4(PF_FILTER_ROUTE4 pfFunc);

/*******************************************************************************
*    Func Name: TCPIP_RecvEvent
* Date Created: 2009-8-21
*       Author: zhangchunyu(62474)
*  Description: 控制面接收数据面消息分发函数
*        Input: VOID *pMsg: 消息
*               UINT32 u32MsgLen:消息长度 
*       Output: 
*       Return: 成功:TCPIP_SFE_COM_SUCCESS 其他:失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-21    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_RecvEvent(VOID *pMsg, UINT32 u32MsgLen);

/*******************************************************************************
*    Func Name: TCPIP_SFE_OperARP
* Date Created: 2009-8-20
*       Author: w60786
*  Description: ARP数据面操作对应的控制面
*        Input: UINT32 u32OperType: ARP配置类型
*               TCPIP_SFE_ARP_S *pstArp: ARP配置参数
*       Output: 
*       Return: 
*      Caution: Important points if any
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-20  w60786         Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_OperARP(UINT32 u32OperType, TCPIP_SFE_ARP_S *pstArp);

/*******************************************************************************
*    Func Name: TCPIP_SFE_OperFIB4
* Date Created: 2009-8-20
*       Author: zhangchunyu(62474)
*  Description: 用户调用操作路由接口
*        Input: ULONG ulOperType: 操作类型
*               TCPIP_SFE_ROUTE_S *pstRtMsg: 路由消息
*       Output: 
*       Return: 成功: TCPIP_SFE_RT_SUCCESS
*               失败: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-20    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_OperFIB4(UINT32 u32OperType, TCPIP_SFE_ROUTE_S *pstRtMsg);

/*******************************************************************************
*    Func Name: TCPIP_SFE_OperIf
* Date Created: 2009-08-21
*       Author: ZhengSenHuo/GeXianJun(104483/121208)
*  Description: 对外API，统一由产品调用，进行接口的配置更新等操作
*        Input: UINT32 u32OperType:操作码,参见tcpip_pub_api.h文件中tagPPIOprType
*               TCPIP_SFE_INTF_S *pstIntfInfo: 接口信息
*       Output: 
*       Return: 成功: TCPIP_SFE_IF_SUCCESS
*               失败: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-21   ZhengSenHuo/GeXianJun(104483/121208)  Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_OperIf(UINT32 u32OperType,TCPIP_SFE_INTF_S *pstIntfInfo);

/*******************************************************************************
*    Func Name: TCPIP_SFE_PPI_FIB4_Update
* Date Created: 2009-8-20
*       Author: zhangchunyu(62474)
*  Description: 控制面PPI下发接口
*        Input: UINT32 ulOprType: PPI类型
*               PPI_RTMSG4_S *pstPpiRoute:消息结构 
*       Output: 
*       Return: 成功: TCPIP_SFE_RT_SUCCESS
*               失败: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-20    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_PPI_FIB4_Update(UINT32 u32OprType, PPI_RTMSG4_S *pstPpiRoute);

/*******************************************************************************
*    Func Name: TCPIP_SFE_PPI_ARP_Update
* Date Created: 2009-8-21
*       Author: w60786
*  Description: ARP模块处理控制面PPI下发命令字的函数
*        Input: UINT32 u32OperType: ARP操作类型
*               PPI_ARP_S *pstArpMsg: ARP 控制面PPI下发参数
*       Output: 
*       Return: 成功: TCPIP_SFE_ARP_OK
*               失败: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-21    w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32  TCPIP_SFE_PPI_ARP_Update(UINT32 u32OperType, PPI_ARP_S *pstArpMsg);

/*******************************************************************************
*    Func Name: TCPIP_SFE_PPI_IF_Update
* Date Created: 2009-08-21
*       Author: ZhengSenHuo/GeXianJun(104483/121208)
*  Description: IFNET的PPI注册接口,控制面初始化前需调用TCPIP_PPI_HookRegister接口进行注册
*        Input: UINT32 u32IfIndex:接口索引
*               UINT32 u32Cmd:PPI命令
*               VOID *pData:
*       Output: 
*       Return: 成功: TCPIP_SFE_IF_SUCCESS
*               失败: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-21   ZhengSenHuo/GeXianJun(104483/121208)  Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_PPI_IF_Update(UINT32 u32IfIndex, UINT32 u32Cmd, VOID *pData);

/*******************************************************************************
*    Func Name: TCPIP_SFE_PPI_VRF_Update
* Date Created: 2009-08-21
*       Author: ZhengSenHuo/GeXianJun(104483/121208)
*  Description: Vrf的PPI注册接口,控制面初始化前需调用TCPIP_PPI_HookRegister接口进行注册
*        Input: UINT32 u32Cmd:命令字
*               VRF_PPI_S *pstVrfPpi:Vrf信息
*       Output: 
*       Return: 成功: TCPIP_SFE_IF_SUCCESS
*               失败: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-21   ZhengSenHuo/GeXianJun(104483/121208)  Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_PPI_VRF_Update(UINT32 u32Cmd, VRF_PPI_S *pstVrfPpi);

/*******************************************************************************
*    Func Name: TCPIP_SFE_PPI_BFD4_Update
* Date Created: 2009-9-3
*       Author: w60786
*  Description: BFD模块处理控制面PPI下发命令字的函数
*        Input: UINT32 u32OperType: PPI 命令字
*               UINT32 u32SessionID: 会话ID
*               BFD_PPI_S *pstBfdPpiInfo: IPV4 BFD会话信息
*       Output: 
*       Return: 成功: TCPIP_SFE_BFD_OK
*               失败: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-9-3     w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_PPI_BFD4_Update(UINT32 u32OperType, UINT32 u32SessionID, BFD_PPI_S *pstBfdPpiInfo);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetFIBInfo
* Date Created: 2009-8-29
*       Author: zhangchunyu(62474)
*  Description: 获取指定VRF下指定IP对应的路由表项信息
*        Input: UINT32 u32VrfIndex: VRF索引
*               UINT32 u32IpAddr: 地址(网络序)
*               TCPIP_SFE_ROUTE_S *pstRouteInfo: 获取的路由信息
*       Output: *pstRouteInfo: 获取的路由信息
*       Return: TCPIP_SFE_COM_SUCCESS:成功 其他:失败
*      Caution: 该函数从数据面只能获取一条路由信息,如果是平衡路由,则随机获取一条平衡路由
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-29    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetFIBInfo(UINT32 u32VrfIndex, UINT32 u32IpAddr, TCPIP_SFE_ROUTE_S *pstRouteInfo);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetArpInfo
* Date Created: 2009-8-28
*       Author: w60786
*  Description: 获取指定VRF下指定IP对应的ARP表项信息
*        Input: UINT32 u32VrfIndex: VRF索引
*               UINT32 u32IpAddr: 地址(网络序)
*               TCPIP_SFE_ARP_S *pstArp: 获取的ARP信息
*       Output: 
*       Return: 成功: TCPIP_SFE_ARP_OK
*               失败: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-28    w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetArpInfo(UINT32 u32VrfIndex, UINT32 u32IpAddr, TCPIP_SFE_ARP_S *pstArp);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetIfInfoByID
* Date Created: 2009-8-28
*       Author: w60786
*  Description: 获取指定接口ID的信息
*        Input: TCPIP_SFE_IFID *pstIntfID: 接口ID
*               TCPIP_SFE_INTF_S *pstIntfInfo: 接口信息
*       Output: 
*       Return: 成功: TCPIP_SFE_IF_SUCCESS
*               失败: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-28    w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetIfInfoByID(TCPIP_SFE_IFID *pstIntfID,TCPIP_SFE_INTF_S *pstIntfInfo);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetBfdSessionInfo
* Date Created: 2009-9-15
*       Author: w60786/h00121208
*  Description: 获取指定VRF下指定会话ID对应的BFD会话信息
*        Input: UINT32 u32VrfIndex: VRF索引
*               UINT32 u32SessionId: BFD会话ID
*       Output: TCPIP_SFE_BFD_SESS_INFO_S *pstBfdSessInfo: 获取的BFD会话信息
*       Return: 成功: TCPIP_SFE_BFD_OK
*               失败: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                     DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-9-15    w60786/h00121208         Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetBfdSessionInfo(UINT32 u32VrfIndex, UINT32 u32SessionId,
                                                    TCPIP_SFE_BFD_SESS_INFO_S *pstBfdSessInfo);
                                             
/*******************************************************************************
*    Func Name: TCPIP_SFE_OpenTable
* Date Created: 2009-8-22
*       Author: zhangchunyu(62474)
*  Description: 打开指定的数据表
*        Input: UINT32  u32TableType: 数据表, 取值见enumTableType
*               UINT32  u32VrfIndex:  VRF实例号
*       Output: UINT32 *pu32Handle:   数据表操作句柄, 用于get和close
*       Return: TCPIP_SFE_TABLE_SUCCESS 成功 / 其他 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                   DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-22    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_OpenTable(UINT32 u32TableType, UINT32 u32VrfIndex, UINT32 *pu32Handle);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetTableData
* Date Created: 2009-8-22
*       Author: zhangchunyu(62474)
*  Description: 
*        Input: UINT32  u32Handle:  数据表操作句柄, open时获得
*               UINT32 *pu32GetNum: 打算获取的表项个数
*               UINT32 *pu32BufLen: 缓冲区长度 
*       Output: 
*               UINT32 *pu32GetNum: 实际获取的表项个数
*               UINT8  *pu8Buf:     缓冲区地址
*               UINT32 *pu32BufLen: 实际拷贝的长度 
*       Return: TCPIP_SFE_TABLE_SUCCESS: 成功
*               TCPIP_SFE_TABLE_GET_OVER: 获取表项完成
*               其他: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                   DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-22    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetTableData(UINT32  u32Handle,
                              UINT32 *pu32GetNum,
                              UINT8  *pu8Buf,
                              UINT32 *pu32BufLen);

/*******************************************************************************
*    Func Name: TCPIP_SFE_CloseTable
* Date Created: 2009-8-22
*       Author: zhangchunyu(62474)
*  Description: 关闭指定的数据表
*        Input: UINT32 u32Handle: 数据表操作句柄, open时获得
*       Output: 
*       Return: TCPIP_SFE_TABLE_SUCCESS 成功 / 其他 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                   DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-22    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_CloseTable(UINT32 u32Handle);

/*******************************************************************************
*    Func Name: TCPIP_SFE_SetSendIcmpErrSwitch
* Date Created: 2009-08-21
*       Author: z62474/z62531
*  Description: 设置发送ICMP差错报文的开关
*        Input: u32Switch:调试开关
*       Output: 
*       Return: 成功: TCPIP_SFE_ICMP_OK
*               失败: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-21   z62474/z62531           Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_SetSendIcmpErrSwitch(UINT32 u32Switch);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetSendIcmpErrSwitch
* Date Created: 2009-9-12
*       Author: z62474/z62531
*  Description: 获取ICMP调试开关
*        Input: UINT32 *pu32Switch: 输出参数,获取值
*       Output: 
*       Return: 成功: TCPIP_SFE_ICMP_OK
*               失败: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-9-12    z62474/z62531     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetSendIcmpErrSwitch(UINT32 *pu32Switch);

/*******************************************************************************
*    Func Name: TCPIP_SFE_IF_SetEthArpMissSwitch
* Date Created: 2009-9-16
*       Author: w60786/h00121208
*  Description: 设置以太接口是否需要进行ARP MISS处理开关
*        Input: TCPIP_SFE_IFID *pstIfId: 以太接口ID
*               UINT32 u32Switch: ARP MISS处理开关值
*       Output: 
*       Return: 成功: TCPIP_SFE_IF_SUCCESS
*               失败: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                     DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-9-16    w60786/h00121208         Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_IF_SetEthArpMissSwitch(TCPIP_SFE_IFID *pstIfId, UINT32 u32Switch);

/*******************************************************************************
*    Func Name: TCPIP_SFE_IF_SetReduceTTLSwitch
* Date Created: 2009-9-16
*       Author: w60786/h00121208
*  Description: 设置接口是否需要递减TTL开关
*        Input: TCPIP_SFE_IFID *pstIfId: 接口ID
*               UINT32 u32Switch: TTL是否递减开关值
*       Output: 
*       Return: 成功: TCPIP_SFE_IF_SUCCESS
*               失败: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                     DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-9-16    w60786/h00121208         Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_IF_SetReduceTTLSwitch(TCPIP_SFE_IFID *pstIfId, UINT32 u32Switch);

/*******************************************************************************
*    Func Name: TCPIP_SFE_SetSrcIpAddr
* Date Created: 2009-10-16
*       Author: z62474/z62531
*  Description: 在控制面设置数据面发送报文时可能需要的源IP
*        Input: u32VrfIndex:实例号
*               u32SrcIpAddr:IP Addr,主机序
*       Output: 
*       Return: 成功: TCPIP_SFE_ICMP_OK
*               失败: 错误码
*      Caution: 目前数据面接口没有维护地址,在发送报文的时候,
*               根据用户配置VRF下的IP填充报文的源IP
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-16   z62474/z62531  Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_SetSrcIpAddr(UINT32 u32VrfIndex, UINT32 u32SrcIpAddr);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetSrcIpAddr
* Date Created: 2009-10-16
*       Author: z62474/z62531
*  Description: 在控制面获取源IP
*        Input: u32VrfIndex:实例号
*       Output: pu32SrcIpAddr:输出参数, 获取到的Src IP
*       Return: 成功: TCPIP_SFE_IP_OK
*               失败: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-16   z62474/z62531  Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetSrcIpAddr(UINT32 u32VrfIndex, UINT32 *pu32SrcIpAddr);

/*******************************************************************************
*    Func Name: TCPIP_SFE_BFD_SetDebugSwitch
* Date Created: 2009-10-16
*       Author: z62531
*  Description: 基于BFD会话设置调试开关
*        Input: UINT32 u32VrfIndex:VRF索引
*               UINT32 u32SessionId:会话ID
*               UINT32 u32IsDebug:是否调试，1打开调试开关,0关闭调试开关
*       Output: 
*       Return: 成功: TCPIP_SFE_BFD_OK
*               失败: 错误码
*      Caution: 会话ID为0时表示打开所有会话的调试开关
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-16   z62531                   Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_BFD_SetDebugSwitch(UINT32 u32VrfIndex, UINT32 u32SessionId, UINT32 u32IsDebug);

/*******************************************************************************
*    Func Name: TCPIP_SFE_BFD_GetDebugSwitch
* Date Created: 2009-10-16
*       Author: z62531
*  Description: 基于BFD会话获取调试开关
*        Input: UINT32 u32VrfIndex:VRF索引
*               UINT32 u32SessionId:会话ID
*       Output: UINT32 *pu32IsDebug:是否调试，1打开调试开关,0关闭调试开关
*       Return: 成功: TCPIP_SFE_BFD_OK
*               失败: 错误码
*      Caution: 会话ID为0时表示获取是否打开所有BFD会话的调试开关,1为打开,0为关闭
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-16   z62531                   Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_BFD_GetDebugSwitch(UINT32 u32VrfIndex, 
                                                UINT32 u32SessionId, UINT32 *pu32IsDebug);

/*******************************************************************************
*    Func Name: TCPIP_SFE_SetDebugTypeSwitch
* Date Created: 2009-10-16
*       Author: z62531
*  Description: 设置调试类型开关
*        Input: UINT32 u32DebugTypeSwitch: 位调试类型开关值
*       Output: pu32SrcIpAddr:输出参数, 获取到的Src IP
*       Return: 成功: TCPIP_SFE_DEBUG_OK
*               失败: 错误码
*      Caution: 参数如下:,当前不支持SFE_DEBUG_TYPE_PROC
*               #define SFE_DEBUG_TYPE_ERROR        0x0001
*               #define SFE_DEBUG_TYPE_INOUT        0x0002  
*               #define SFE_DEBUG_TYPE_PROC         0x0004
*               #define SFE_DEBUG_TYPE_VERBOSE      0x0008
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-16   z62531  Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_SetDebugTypeSwitch(UINT32 u32DebugTypeSwitch);

/*******************************************************************************
*    Func Name: SFE_SetDebugVcpuSwitch
* Date Created: 2009-7-31
*       Author: z62531
*  Description: 设置调试VCPU开关
*        Input: UINT32 u32DebugVcpuSwitch: 位调试VCPU开关值
*       Output: 
*       Return: 成功: SFE_DEBUG_OK
*               失败: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-31   z62531                                        Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_SetDebugVcpuSwitch (UINT32 u32DebugVcpuSwitch);

/*******************************************************************************
*    Func Name: TCPIP_SFE_SetDebugModuleSwitch
* Date Created: 2009-7-31
*       Author: z62531
*  Description: 设置调试模块开关
*        Input: UINT32 u32DebugModuleSwitch: 位调试模块开关值
*               SFE_DEBUG_MODULE_IPFWD     0x00000001
*               SFE_DEBUG_MODULE_ICMP      0x00000002
*               SFE_DEBUG_MODULE_BFD       0x00000004
*               SFE_DEBUG_MODULE_ALL       (SFE_DEBUG_MODULE_IPFWD | SFE_DEBUG_MODULE_ICMP | SFE_DEBUG_MODULE_BFD)
*       Output: 
*       Return: 成功: SFE_DEBUG_OK
*               失败: 错误码
*      Caution: 为后续扩展,不限定u32DebugModuleSwitch的大小
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-31   z62531                                        Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_SetDebugModuleSwitch (UINT32 u32DebugModuleSwitch);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetDebugSwitch
* Date Created: 2009-7-31
*       Author: z62531
*  Description: 获取各种调试开关
*        Input: 
*       Output: UINT32* pu32DebugTypeSwitch: 调试类型开关
*               UINT32* pu32DebugVcpuSwitch: 调试VPU开关
*               UINT32* pu32DebugModuleSwitch: 调试模块开关
*       Return: 成功: SFE_DEBUG_OK
*               失败: 错误码
*      Caution: Important points if any
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-31   z62531                                       Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetDebugSwitch(UINT32* pu32DebugTypeSwitch, 
                                                UINT32* pu32DebugVcpuSwitch, 
                                                UINT32* pu32DebugModuleSwitch);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowDebugSwitch
* Date Created: 2009-11-2
*       Author: w60786
*  Description: 显示数据面各种调试开关信息
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowDebugSwitch(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_SetMsgOrEvent_DebugSwitch
* Date Created: 2009-7-31
*       Author: z62531
*  Description: 控制面设置消息或事件调试开关,1为打开,0为关闭
*        Input: UINT32 u32DebugSwitch:调试开关
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-31   z62531                                         Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_SetMsgOrEvent_DebugSwitch(UINT32 u32Switch);

/*******************************************************************************
*    Func Name: SFE_GetMsgOrEvent_DebugSwitch
* Date Created: 2009-7-31
*       Author: z62531
*  Description: 获取消息或事件调试开关,1为打开,0为关闭
*        Input: 
*       Output: UINT32 *pu32CtlDbgSwitch:控制面的调试开关
*               UINT32 *pu32SfeDbgSwitch:转发面的调试开关
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-31   z62531                                         Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetMsgOrEvent_DebugSwitch(UINT32 *pu32CtlDbgSwitch,
                                           UINT32 *pu32SfeDbgSwitch);

/*******************************************************************************
*    Func Name: TCPIP_SFE_SetVerboseDebug_CntAndLen
* Date Created: 2009-7-31
*       Author: z62531
*  Description: 设置详细调试报文的次数和长度
*        Input: UINT32 u32PktNum:报文次数
*               UINT32 u32Length:调试报文的长度
*       Output: 
*       Return: VOID
*      Caution: u32PktNum为0表示不打印
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-31   z62531                                         Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_SetVerboseDebug_CntAndLen(UINT32 u32PktNum, UINT32 u32Length);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetVerboseDebug_CntAndLen
* Date Created: 2009-7-31
*       Author: z62531
*  Description: 获取详细调试报文的次数和长度
*        Input: 
*       Output: UINT32 *pu32PktNum:报文次数
*               UINT32 *pu32Length:调试报文的长度
*       Return: VOID
*      Caution: u32PktNum为0时表示不限制调试报文的个数
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-31   z62531                                         Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetVerboseDebug_CntAndLen(UINT32 *pu32PktNum, UINT32 *pu32Length);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetAllStatistic
* Date Created: 2009-11-2
*       Author: w60786
*  Description: 获取数据面全局统计信息
*        Input: 
*       Output: SFE_IPSFE_STATISTIC_S *pstStatisticManualInfo: 全局手动统计信息(各VCPU统计之和),
*                   用户提供空间.
*               UINT32 pu32StaisticAutoInfo[SFE_STAT_IPFWD_MAX]: 全局自动统计信息,用户提供空间,
*               用户必须保证该空间足够大,至少有SFE_STAT_IPFWD_MAX*sizeof(UINT32)字节大.
*       Return: 成功: TCPIP_SFE_DEBUG_OK
*               失败: 错误码
*      Caution: 用户必须保证提供的存储空间足够大
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetAllStatistic(SFE_IPSFE_STATISTIC_S *pstStatisticManualInfo,
                                        UINT32 pu32StaisticAutoInfo[SFE_STAT_IPFWD_MAX]);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetManualStatisticByVcpu
* Date Created: 2009-11-2
*       Author: w60786
*  Description: 获取数据面指定VCPU的全局手动统计信息
*        Input: UINT32 u32VcpuId: VCPU ID,取值范围[0, SFE_VCPU_MAX_NUM-1]
*       Output: SFE_IPSFE_STATISTIC_S *pstStatisticManualInfo: 指定VCPU的全局手动统计信息,用户提供空间
*       Return: 成功: TCPIP_SFE_DEBUG_OK
*               失败: 错误码
*      Caution: 用户必须保证提供的存储空间足够大
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetManualStatisticByVcpu(UINT32 u32VcpuId, SFE_IPSFE_STATISTIC_S *pstStatisticManualInfo);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowAllStatistic
* Date Created: 2009-11-2
*       Author: w60786
*  Description: 显示全局统计信息(全局手动各VCPU统计之和,以及全局自动统计信息)
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowAllStatistic();

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowAutoStatistic
* Date Created: 2009-11-2
*       Author: w60786
*  Description: 显示全局自动统计信息
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowAutoStatistic();

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowManualStatistic
* Date Created: 2009-11-2
*       Author: w60786
*  Description: 显示全局手动统计信息(各VCPU统计信息之和)
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowManualStatistic();

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowManualStatisticByVCPU
* Date Created: 2009-11-2
*       Author: w60786
*  Description: 显示指定VCPU的全局手动统计信息
*        Input: UINT32 u32VCPUID: 
*               ID编号[0,SFE_VCPU_MAX_NUM－1]:表示显示指定VCPU编号的手动统计信息
*               SFE_VCPU_MAX_NUM(32):表示循环显示各VCPU的手动统计信息
*               SFE_SHOW_TOTAL_MANUAL_STATISTIC(0xffffffff):表示显示各VCPU手动统计值之和
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowManualStatisticByVCPU(UINT32 u32VCPUID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_SetFlowStatisticSwitch
* Date Created: 2009-10-31
*       Author: w60786
*  Description: 设置数据面流统计开关
*        Input: UINT32 u32FlowStatSwitch: 流统计开关值
*               `   SFE_FLOWSTAT_SWITCH_ON:打开流统计功能
*                   SFE_FLOWSTAT_SWITCH_OFF:关闭流统计功能
*       Output: 
*       Return: 成功: TCPIP_SFE_DEBUG_OK
*               失败: 错误码
*      Caution: Important points if any
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-10-31   w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_SetFlowStatisticSwitch(UINT32 u32FlowStatSwitch);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetFlowStatisticSwitch
* Date Created: 2009-10-31
*       Author: w60786
*  Description: 获取数据面流统计开关
*        Input: 
*       Output: UINT32 *pu32FlowStatSwitch: 流统计开关,
*               `   SFE_FLOWSTAT_SWITCH_ON:打开
*                   SFE_FLOWSTAT_SWITCH_OFF:关闭
*       Return: 成功: TCPIP_SFE_DEBUG_OK
*               失败: 错误码
*      Caution: Important points if any
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-10-31   w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetFlowStatisticSwitch(UINT32 *pu32FlowStatSwitch);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowFlowStatisticSwitch
* Date Created: 2009-10-31
*       Author: w60786
*  Description: 显示数据面流统计开关
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: Important points if any
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-10-31   w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowFlowStatisticSwitch(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ConfigFlowStatisticRule
* Date Created: 2009-10-31
*       Author: w60786
*  Description: 配置数据面的流统计规则
*        Input: UINT32 u32OperType: 配置操作类型,取值请参见SFE_FLOWSTATISTIC_RULE_OPER_TYPE_E定义
*               TCPIP_SFE_FLOWSTATISTIC_RULE_S *pstFlowStatisticRule: 流统计规则信息,
*                   当配置操作类型为SFE_FLOWSTATISTIC_DELALL时,该参数无效,可传入NULL指针.
*                   但是其余配置操作该参数必须非NULL.
*       Output: 
*       Return: 成功: TCPIP_SFE_DEBUG_OK
*               失败: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-10-31   w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_ConfigFlowStatisticRule(UINT32 u32OperType, TCPIP_SFE_FLOWSTATISTIC_RULE_S *pstFlowStatisticRule);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetFlowStatisticRuleNum
* Date Created: 2009-10-31
*       Author: w60786
*  Description: 获取数据面当前的流统计规则数
*        Input: 
*       Output: UINT32 *pu32FlowStatisticRuleNum: 流统计规则数指针
*       Return: 成功: TCPIP_SFE_DEBUG_OK
*               失败: 错误码
*      Caution: 成功时输出信息才有效,用户必须先判断返回值,再使用
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-10-31   w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetFlowStatisticRuleNum(UINT32 *pu32FlowStatisticRuleNum);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetFlowStatisticRule
* Date Created: 2009-10-31
*       Author: w60786
*  Description: 指定规则数目获取流统计规则
*        Input: pu32FlowRuleNum: 指定用户需要获取的流规则数,
*       Output: TCPIP_SFE_FLOWSTATISTIC_RULE_S *pstFlowStatisticRule: 存放获取的流统计规则
*                   用户传入的空间大小要足够大,必须至少是pstFlowRuleNum参数值乘以
*                   TCPIP_SFE_FLOWSTATISTIC_RULE_S结构大小的空间。
*               UINT32 *pstFlowRuleNum: 输入时,指定用户需要获取的流规则数,
*                   输出时,表示实际获取的流统计规则数,该值也可能为0,表示不存在规则没有获取到.
*       Return: 成功: TCPIP_SFE_DEBUG_OK
*               失败: 错误码
*      Caution: 成功时输出信息才有效,用户必须先判断返回值,再使用
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-31   w60786                  Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetFlowStatisticRule(TCPIP_SFE_FLOWSTATISTIC_RULE_S *pstFlowStatisticRule,
                                               UINT32 *pu32FlowRuleNum);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetFlowStatisticInfoByRule
* Date Created: 2009-10-31
*       Author: w60786
*  Description: 根据流统计规则获取对应的统计信息
*        Input: TCPIP_SFE_FLOWSTATISTIC_RULE_S *pstFlowStatisticRule: 流统计规则
*                  如果是协议号TCP和UDP,输入的源目的端口号才有效,否则无效.
*                  流统计ID字段作为输出参数.
*       Output: SFE_IPSFE_FLOWSTATISTIC_S *pstFlowStatisticManualInfo: 对应流的手动统计信息
*               UINT32 pu32FlowStaisticAutoInfo[SFE_STAT_IPFWD_MAX]: 对应流的自动统计信息
*                     用户必须保证该空间足够大,至少有SFE_STAT_IPFWD_MAX*sizeof(UINT32)字节大.
*       Return: 成功: TCPIP_SFE_DEBUG_OK
*               失败: 错误码
*      Caution: pu32FlowStaisticAutoInfo参数是一个大小为SFE_STAT_IPFWD_MAX的UINT32类型的数组
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-31   w60786                  Create
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetFlowStatisticInfoByRule(TCPIP_SFE_FLOWSTATISTIC_RULE_S *pstFlowStatisticRule,
                                                       SFE_IPSFE_FLOWSTATISTIC_S *pstFlowStatisticManualInfo,
                                                       UINT32 pu32FlowStaisticAutoInfo[SFE_STAT_IPFWD_MAX]);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowAllFlowStatisticRule
* Date Created: 2009-11-2
*       Author: w60786
*  Description: 显示数据面所有的流统计规则
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowAllFlowStatisticRule(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowFlowStatisticRuleByFlowId
* Date Created: 2009-11-2
*       Author: w60786
*  Description: 显示数据面指定流ID的流统计规则
*        Input: UINT32 u32FlowId: 流ID值
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowFlowStatisticRuleByFlowId(UINT32 u32FlowId);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowAllFlowStatistic
* Date Created: 2009-11-2
*       Author: w60786
*  Description: 显示数据面所有的流统计信息
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowAllFlowStatistic(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowFlowStatisticByFlowRule
* Date Created: 2009-11-2
*       Author: w60786
*  Description: 显示数据面指定流规则的流统计信息
*        Input: TCPIP_SFE_FLOWSTATISTIC_RULE_S *pstFlowStatisticRule: 指定的流规则信息
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowFlowStatisticByFlowRule(TCPIP_SFE_FLOWSTATISTIC_RULE_S *pstFlowStatisticRule);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowFlowStatisticByFlowId
* Date Created: 2009-11-2
*       Author: w60786
*  Description: 显示数据面指定流ID的流统计信息
*        Input: UINT32 u32FlowId:
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowFlowStatisticByFlowId(UINT32 u32FlowId);

/*******************************************************************************
*    Func Name: TCPIP_SFE_SetLogLevel
* Date Created: 2009-11-2
*       Author: w60786
*  Description: 设置数据面日志级别开关
*        Input: UINT32 u32LogLevel: 日志级别,取值清参见SFE_LOG_LEVEL_E枚举定义
*       Output: 
*       Return: 成功: TCPIP_SFE_DEBUG_OK
*               失败: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_SetLogLevel(UINT32 u32LogLevel);

/*******************************************************************************
*    Func Name: TCPIP_SFE_SetLogType
* Date Created: 2009-11-2
*       Author: w60786
*  Description: 设置日志记录类型开关
*        Input: UINT32 ul32WarningLogEnable: 告警日志记录开关,取值:0:关闭 1:打开
*               UINT32 u32CfgLogEnable: 配置日志记录开关,取值:0:关闭 1:打开
*               UINT32 u32RunLogEnable: 运行日志记录开关,取值:0:关闭 1:打开
*       Output: 
*       Return: 成功: TCPIP_SFE_DEBUG_OK
*               失败: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_SetLogType(UINT32 ul32WarningLogEnable, UINT32 u32CfgLogEnable, UINT32 u32RunLogEnable);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowLogSwitch
* Date Created: 2009-11-2
*       Author: w60786
*  Description: 显示数据面日志开关信息
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowLogSwitch(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowVersion
* Date Created: 2009-11-2
*       Author: w60786
*  Description: 显示数据面版本号信息
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowVersion(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_Show_PreConfigPara
* Date Created: 2009-11-2
*       Author: w60786
*  Description: 显示数据面预配置信息
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_Show_PreConfigPara(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_Show_ShareMemoryID
* Date Created: 2009-11-2
*       Author: w60786
*  Description: 显示数据面使用的各类型共享内存ID
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_Show_ShareMemoryID(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_Show_StubDeleteModule
* Date Created: 2009-11-2
*       Author: w60786
*  Description: 显示数据面模块裁减情况
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_Show_StubDeleteModule(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_SetAclNeedFakeReassSwitch
* Date Created: 2009-11-2
*       Author: w60786
*  Description: 设置ACL处理是否需要数据面进行假重组开关以支持精确匹配功能
*        Input: UINT32 u32Switch: 开关,
*               取值: SFE_ACL_NEED_FAKEREASS_SWITCH_ON: ACL处理需要数据面进行假重组处理
*                     SFE_ACL_NEED_FAKEREASS_SWITCH_OFF: ACL处理不需要数据面进行假重组处理
*       Output: 
*       Return: 成功: TCPIP_SFE_PUB_OK
*               失败: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_SetAclNeedFakeReassSwitch(UINT32 u32Switch);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetAclNeedFakeReassSwitch
* Date Created: 2009-11-2
*       Author: w60786
*  Description: 获取ACL处理是否需要数据面进行假重组开关以支持精确匹配功能
*        Input: 
*       Output: UINT32 *pu32Switch: 开关值,取值含义请参见TCPIP_SFE_SetAclNeedFakeReassSwitch接口说明
*       Return: 成功: TCPIP_SFE_PUB_OK
*               失败: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetAclNeedFakeReassSwitch(UINT32 *pu32Switch);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowAclNeedFakeReassSwitch
* Date Created: 2009-11-2
*       Author: w60786
*  Description: 显示ACL处理是否需要数据面进行假重组开关以支持精确匹配功能
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowAclNeedFakeReassSwitch(VOID);

/*******************************************************************************
*    Func Name: TCPIP_Show_MsgSeq
* Date Created: 2009-10-26
*       Author: maqinggao(00116466)
*  Description: 显示控制面通道消息序列号
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                     DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-26   maqinggao(00116466)      Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_Show_MsgSeq(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_Show_MsgSeq
* Date Created: 2009-11-2
*       Author: w60786
*  Description: 显示数据面通道消息序列号
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_Show_MsgSeq(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_OutputToCOMSwitch
* Date Created: 2009-11-2
*       Author: w60786
*  Description: 数据面维测信息com口输出开关,该接口不是对外API接口,只是用于维测调试
*        Input: UINT32 u32Switch: 开关,取值请参见SFE_OUTPUT_FIX_LOG等宏定义
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-2    w60786           Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_OutputToCOMSwitch(UINT32 u32Switch);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ClearAllStatistic
* Date Created: 2009-11-6
*       Author: w60786
*  Description: 清除数据面所有全局统计信息(该接口不是对外API接口,只用于内部维测调试,
*               由于统计信息是多核操作,所以该接口操作可能不太准确),
*        Input: VOID
*       Output: 
*       Return: 成功: TCPIP_SFE_DEBUG_OK
*               失败: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-6    w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_ClearAllStatistic(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ClearAllFlowStatistic
* Date Created: 2009-11-6
*       Author: w60786
*  Description: 清除数据面所有流统计信息(该接口不是对外API接口,只用于内部维测调试,
*               由于统计信息是多核操作,所以该接口操作可能不太准确),
*        Input: VOID
*       Output: 
*       Return: 成功: TCPIP_SFE_DEBUG_OK
*               失败: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-6    w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_ClearAllFlowStatistic(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowAllArpInfo
* Date Created: 2009-11-10
*       Author: m00116466
*  Description: 显示所有ARP表项
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                      DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-10     m00116466         Create the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowAllArpInfo(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowArpInfoByVrf
* Date Created: 2009-8-6
*       Author: m00116466
*  Description: 显示指定VRF下的所有ARP表项
*        Input: UINT32 u32VrfIndex: VRF索引
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                      DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-11     m00116466         Create the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowArpInfoByVrf(UINT32 u32VrfIndex);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowOneArpInfo
* Date Created: 2009-8-6
*       Author: m00116466
*  Description: 显示指定的某个ARP表项
*        Input: UINT32 u32VrfIndex: VRF索引
*               CHAR *pcIpAddr: 点分十进制形式的地址
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                      DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-6     w60786/luowentong         Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowOneArpInfo(UINT32 u32VrfIndex, CHAR *pcIpAddr);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowAllIfInfo
* Date Created: 2009-11-10
*       Author: m00116466
*  Description: 显示所有接口信息
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-11-10   m00116466               Create the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowAllIfInfo(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowIfInfoByID
* Date Created: 2009-12-01
*       Author: maqinggao(00116466)
*  Description: 根据接口ID显示接口信息
*        Input: TCPIP_SFE_IFID *pstIfID:接口ID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-01   maqinggao(00116466)  Create
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowIfInfoByID(TCPIP_SFE_IFID *pstIfID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowAllBfdInfo
* Date Created: 2009-11-10
*       Author: m00116466
*  Description: 显示所有VRF下的BFD会话信息
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                     DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-10   m00116466         Create the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowAllBfdInfo(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowBfdInfoByVrf
* Date Created: 2009-12-01
*       Author: m00116466
*  Description: 显示指定VRF下的BFD会话信息 
*        Input: UINT32 u32VrfIndex: VRF索引
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                     DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-12-01     m00116466         Create the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowBfdInfoByVrf(UINT32 u32VrfIndex);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowBfdInfoByID
* Date Created: 2009-11-10
*       Author: m00116466
*  Description: 显示指定VRF SessionID的会话信息
*        Input: UINT32 u32VrfIndex: VRF索引
*        Input: UINT32 u32SessionId:BFD会话ID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                     DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-10   m00116466         Create the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowBfdInfoByID(UINT32 u32VrfIndex, UINT32 u32SessionId);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowAllFibInfo
* Date Created: 2009-11-10
*       Author: m00116466
*  Description: 显示所有路由信息
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-11-10   m00116466               Create the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowAllFibInfo(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowFibInfoByIP
* Date Created: 2009-11-10
*       Author: m00116466
*  Description: 显示指定VRF 某个IP的路由信息
*        Input: UINT32 u32VrfIndex: VRF索引
*        Input: CHAR  *pi8IpAddr:  点分十进制形式的地址
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                     DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-11-10   m00116466         Create the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowFibInfoByIP(UINT32 u32VrfIndex, CHAR *pi8IpAddr);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetBfdStatistic
* Date Created: 2009-12-3
*       Author: zhangchunyu(62474)
*  Description: 获取指定VRF下某一BFD会话统计信息
*        Input: UINT32 u32VrfIndex: VRF索引
*               UINT32 u32SessionId: 会话ID
*               SFE_BFD_SESS_STATISTIC_S *pstStat:输出参数, 统计信息
*       Output: 
*       Return: 成功 TCPIP_SFE_COM_SUCCESS
*               失败 其他错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-12-3    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetBfdStatistic(UINT32 u32VrfIndex, UINT32 u32SessionId, SFE_BFD_SESS_STATISTIC_S *pstStat);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ClearBfdStatistic
* Date Created: 2009-12-3
*       Author: zhangchunyu(62474)
*  Description: 清0指定VRF下某一BFD会话统计信息
*        Input: UINT32 u32VrfIndex: VRF索引
*               UINT32 u32SessionId: 会话ID
*       Output: 
*       Return: 成功 TCPIP_SFE_COM_SUCCESS
*               失败 其他错误码
*      Caution: 数据面是多核,存在多核同时读写相关字段,所以在清0后,存在相关字段可能不是0的概率
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-12-3    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_ClearBfdStatistic(UINT32 u32VrfIndex, UINT32 u32SessionId);


/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowBfdStatistic
* Date Created: 2009-12-3
*       Author: zhangchunyu(62474)
*  Description: 显示指定VRF下某一BFD会话统计信息
*        Input: UINT32 u32VrfIndex: VRF索引
*               UINT32 u32SessionId: 会话ID
*       Output: 显示会话信息
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-12-3    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowBfdStatistic(UINT32 u32VrfIndex, UINT32 u32SessionId);


#ifdef  __cplusplus
}
#endif
#endif

