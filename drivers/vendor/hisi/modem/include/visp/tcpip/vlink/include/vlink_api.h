/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              vlink_api.h
*
*  Project Code: node
*   Module Name:   
*  Date Created: 2008-08-01
*        Author: wangbin (62223)
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-08-01   wangbin (62223)         Create
*
*******************************************************************************/
#ifndef _VLINK_API_H_
#define _VLINK_API_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/* Add for DTS2011022102588, by tanyiming00171953, at 2011-02-22. 修改原因: 新增Vlink路由查询接口,增强Vlink维测手段  */
typedef enum tagVLINK_ERR_E
{
    VLINK_OK,                         /* 0 */
    VLINK_ERR = MID_COMP_VLINK + 1,   /* 1 相关组件函数指针未初始化*/
    VLINK_ERR_NULL_POINTER,           /* 2 参数指针为空 */
    VLINK_ERR_NO_INDEX_NODE,          /* 3 没有Vlink节点 */
    VLINK_ERR_GET_ENTRY_END,          /* 4 查询结束*/
    VLINK_ERR_WAITLIST,               /* 5 WaitList异常*/
    VLINK_ERR_INTERFACE,              /* 6 错误的接口索引*/
    VLINK_ERR_CFG_TYPE,               /* 7 错误的配置类型*/
    VLINK_ROUTE_NOTIFY_DISABLE,       /* 8 vlink 路由通知模式没有配置*/
    VLINK_ERR_ADDR,                   /* 9  错误的地址*/
    VLINK_ERR_VRF,                    /* 10 获取VRF错误 */
    VLINK_ERR_MAX                     /*   错误码最大值*/
}VLINK_ERR_E;

#define VLINK_FILTER_ALL  0x00000000
#define VLINK_FILTER_WITH_DESTMAST  0x00000001
#define VLINK_FILTER_WITH_IFINDEX   0x00000002
#define VLINK_FILTER_WITH_VRFINDEX  0x00000004
typedef struct tagVLINK_ENTRY_FILTER
{
    ULONG ulFiltFlag;   /* vlink路由过滤flag*/
    ULONG ulDestAddr;   /* 目的地址*/
    ULONG ulMaskLen;    /* 目的掩码*/
    ULONG ulIfIndex;    /* 出接口索引*/
    ULONG ulVrfIndex;   /* vrf索引*/
}VLINK_ENTRY_FILTER_S;

typedef struct tagVLINK_ROUTE_INFO
{
    ULONG ulDestAddr;   /* 目的地址*/
    ULONG ulMaskLen;    /* 目的掩码*/
    ULONG ulIfIndex;    /* 出接口索引*/
    ULONG ulNextHop;    /* 下一跳地址*/
    ULONG ulVrfIndex;   /* vrf索引*/
    ULONG ulVlinkIndex; /* vlink索引:0 －无效值 ，其他－有效值*/
    ULONG ulLastUpdTime;/* 最后一次更新时间，如果创建后一直没有更新，显示初始建立时间 */
}VLINK_ROUTE_INFO_S;


typedef struct tagVlink6CfgRt
{
    ULONG ulOperType;        /*
                               #define RTM_CREATE  0x01:增加路由
                               #define RTM_DEL     0x02:删除路由
                             */
    ULONG ulIfIndex;         /* 路由出接口索引 : 是否是IPC接口由用户保证 */
    UCHAR aucDestAddr[16];   /* 16字节以报文顺序即网络顺序传入*/
} VLINK6_CFG_RT_S; /*IPv6 对端路由配置结构*/

ULONG TCPIP_OpenVlinkRtTable(UINTPTR *pulWaitListHandle,VLINK_ENTRY_FILTER_S *pstFilter);
ULONG TCPIP_GetVlinkRtEntry(UINTPTR ulEntryWaitList, VLINK_ROUTE_INFO_S *pstVlinkRtInfo);
ULONG TCPIP_CloseVlinkRtTable( UINTPTR ulWaitListHandle );

VOID TCPIP_ShowVlinkRoute();
VOID TCPIP_ShowVlink6Route();
ULONG TCPIP_SetVlinkDbgFlg(ULONG ulFlag);
ULONG TCPIP_GetVlinkDbgFlg(ULONG *pulFlg);
VOID TCPIP_ShowVlinkDbgFlg();
VOID TCPIP_ShowIPCVlinkCount();

/*******************************************************************************
*    Func Name: TCPIP_CfgVlink6Rt
* Date Created: 2013-04-12
*       Author: luogaowei 61496
*  Description: 基于ND表项或者IPC 接口配置 128位的主机路由
*        Input: VLINK6_CFG_RT_S *pstRt6Info: 传入的路由信息
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-04-12   luogaowei 61496        create 
*******************************************************************************/
ULONG TCPIP_CfgVlink6Rt(VLINK6_CFG_RT_S *pstRt6Info);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _VLINK_API_H_ */


