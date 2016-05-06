/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ipoa_type.h
*
*  Project Code: node
*   Module Name:   
*  Date Created: 2008-07-24
*        Author: wangbin (62223)
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-07-24   wangbin (62223)         Create
*
*******************************************************************************/
#ifndef _IPOA_TYPE_H_
#define _IPOA_TYPE_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#define IPOA_PVC_HASH_SIZE               256
#define IPOA_MAX_VC_NAME_LEN             16

typedef struct tagIPOA_CB
{
    DLL_NODE_S              stNode;         /* CB链表节点 */
    struct tagIPOA_PKT_STAT stPktStat;     /* 端口报文统计 */
    DLL_S                   stIntfHead;     /* 子接口链表头 */
    DLL_S                   stPVCHead;      /* PVC链表头 */
    DLL_S                   stPVCHash[IPOA_PVC_HASH_SIZE];/* 哈希表 */
    ULONG                   ulIfIndex;      /* 端口IFNET索引 */
    ULONG                   ulMapCount;     /* CB上的MAP计数器 */    
    UCHAR                   ucPhyState;     /* 物理层状态 */
    UCHAR                   ucRes[3];
    ULONG ulReserved1;
    ULONG ulReserved2;

}IPOA_CB_S;


typedef struct tagIPOA_INTERFACE
{
    DLL_NODE_S              stNode;         /* 子接口链表节点 */
    DLL_S                   stPVCHead;      /* PVC链表头 */
    struct tagIPOA_PVC      *pstDefaultPVC; /* 具有default MAP的PVC指针 */
    struct tagIPOA_PVC      *pstInArpPVC;  /* 具有动态 MAP的PVC指针 */    
    struct tagIPOA_CB       *pstIpoaCB;         /* CB指针 */
    struct tagIPOA_PKT_STAT stPktStat;      /* 子接口报文统计 */
    ULONG                   ulMapCount;     /* 子接口上的MAP数量 */
    ULONG                   ulDebugFlag;
    ULONG                   ulIfIndex;      /* 子接口IFNET索引 */
    BOOL_T                  bShutdown;      /* 是否shutdown */
    UCHAR                   ucPhyState;     /* 子接口状态 */
    UCHAR                   ucReserve[1];
    ULONG ulReserved1;
    ULONG ulReserved2;
}IPOA_INTERFACE_S;


typedef struct tagIPOA_PVC
{
    DLL_NODE_S                  stNode;         /* 子接口PVC链表节点 */
    DLL_NODE_S                  stCBNode;       /* CB PVC链表节点 */
    DLL_NODE_S                  stHashNode;     /* CB上的PVC哈希链表节点 */
    USHORT                      usVPI;          /* VPI */
    USHORT                      usVCI;          /* VCI */
    ULONG                       ulVccIndex;     /* 底层的PVC索引 */
    DLL_S                       stIPMapHead;    /* IP MAP */
    struct tagIPOA_MAP_IP       *pstInARPMap;   /* 指向PVC的InARP MAP，没有为NULL */
    struct tagIPOA_MAP_IP       *pstDefaultMap; /* 指向具有default属性的IP MAP，没有为NULL */
    struct tagIPOA_INTERFACE    *pstIpoaIntf;    /* 所属子接口指针 */

    struct tagIPOA_PKT_STAT     stPktStat;      /* PVC报文统计 */
    ULONG                       ulDebugFlag;    /* VC DEBUG开关 */
    BOOL_T                      bShutdown;      /* 是否shutdown */
    UCHAR                       ucPhyState;     /* PVC物理状态，请使用宏ATM_PVCSTATE判断PVC状态 */
    UCHAR                       ucEncType;      /* 封装类型 */
    ULONG                       ulLastChange;   /* 进入当前状态的时间 */
    UCHAR                       if_szDescript[ MAX_INTERFACE_DESCRIPTION_LEN+1 ];
    UCHAR                       ucRes[3];
    ULONG ulReserved1;
    ULONG ulReserved2;
}IPOA_PVC_S;

typedef struct tagIPOA_INARP_PARAM
{
    USHORT      usMinute;       /* InARP周期 */
    UCHAR       ucRes[2];    
}IPOA_INARP_PARAM_S;

typedef struct tagIPOA_INARP_WORK
{
    ULONG       ulTimerID;      /* 定时器ID */
    BOOL_T      bTimerOn;       /* 定时器是否运行 */
    USHORT      usMinute;       /* 现在的定时器间隔长度 */
    UCHAR       ucState;        /* InARP状态: 等待应答、收到应答、收到请求、 发送应答 */
    UCHAR       ucRes[3];    
}IPOA_INARP_WORK_S;


typedef struct tagIPOA_MAP_IP
{
    DLL_NODE_S                  stNode;         /* PVC的IP MAP链表节点 */
    ULONG                       ulMask;         /* 掩码 */
    BOOL_T                      bBroadcast;     /* 是否支持广播 */
    UCHAR                       ucType;         /* MAP类型: IP/InARP/Default */
    UCHAR                       ucState;        /* MAP状态，与VC状态同步 */
    ULONG                       ulIPAddr;       /* 地址，主机字节序 */
    ULONG                       ulVLinkIndex;   /* VLINK索引 */
    struct tagIPOA_INARP_PARAM  stInARPParam;   /* InARP配置参数 */
    struct tagIPOA_INARP_WORK   stInARPWork;    /* InARP工作变量 */
    struct tagIPOA_PVC          *pstPVC;        /* PVC指针 */
    UCHAR                       if_szDescript[ MAX_INTERFACE_DESCRIPTION_LEN+1 ];
    UCHAR                       ucRes[3];
    ULONG ulReserved1;
    ULONG ulReserved2;
}IPOA_MAP_IP_S;


typedef struct tagIPOA_INARP_PACKET_FIXED
{
    USHORT usHrd;   /* 硬件类型 */
    USHORT usPrt;   /* 协议类型 */

    UCHAR  ucShtl;  /* 本端ATM类型(bit7)和ATM号码长度 */
    UCHAR  ucSstl;  /* 本端ATM子地址类型(bit7)和ATM子地址长度 */

    USHORT usOp;    /* 操作符: 请求、应答、NAK */

    UCHAR  ucSpln;  /* 本端协议地址长度 0/4 */
    UCHAR  ucThtl;  /* 对端ATM类型(bit7)和ATM号码长度 */
    UCHAR  ucTstl;  /* 对端ATM子地址类型(bit7)和ATM子地址长度 */
    UCHAR  ucTpln;  /* 对端协议地址长度 0/4 */

}IPOA_INARP_PACKET_FIXED_S;


typedef ULONG (*IPOAGetMap_HOOK_FUNC)(ULONG ulIfIndex, ULONG ulIpAddr, IPOA_MAP_IP_S *pstIpoaMap);
/*Add for BC3D00792,DR.131获取链路层状态*/
typedef ULONG (*IPOAGetLinkStatus_HOOK_FUNC)(ULONG ulIfIndex,ULONG *pulLinkSatus);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _IPOA_TYPE_H_ */



