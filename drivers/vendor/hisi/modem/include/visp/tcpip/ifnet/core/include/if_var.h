/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                         IF_VAR.H
 *
 *  Project Code: VISP1.5
 *   Module Name: IFNET
 *  Date Created: 2004/03/28 
 *        Author: luohanjun
 *   Description: Ifnet全局变量声明头文件
 *               
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2004/03/28      luohanjun       Create
 *  2006/03/30      liai            Adjust for D00654
 *  2006/04/21      liai            Adjust for D00878
 *
 ************************************************************************/

#ifndef _IF_VAR_H_
#define _IF_VAR_H_


#ifdef  __cplusplus
extern "C"{
#endif


/*******************初始化使用变量 begin***********************************/
extern IF_SH_CALL_S* gpstShCallCenter ;               /*shell回调中心指针*/

extern IF_LMSG_FUNLINK_S* gpstLinkMsgNotifyHead ;   /*消息通知函数链头*/
extern IF_MSG_FUNLINK_S* gpstDevMsgNotifyHead ;     /*消息通知函数链头*/
extern IF_PTR_FUNLINK_S* gpstAddIfNotifyHead ;      /*接口创建通知函数链头*/
extern IF_PTR_FUNLINK_S* gpstAddSubIfNotifyHead ;   /*子接口创建通知函数链头*/
extern IF_PTR_FUNLINK_S* gpstDelIfNotifyHead;       /*接口删除通知函数链头*/
extern IF_PTR_FUNLINK_S* gpstShutIfNotifyHead ;     /*接口shutdown通知函数链头*/
extern IF_VLANCHECKFN gpstVlanCheck; /* 接口VLAN配置查询 */

/*******************初始化使用变量 end***********************************/


/******************* IPC使用变量 begin***********************************/
extern UCHAR*  gucBoardList;                           /* 描述系统板在位状态，同时描述物理板、逻辑板状态 */

extern ULONG   gulMaxBoardNum;
/******************* IPC使用变量 end***********************************/


/******************* Dev使用变量 begin***********************************/
/*指向shell的设备链头、链尾 ，实现于内存共享  add by luohanjun*/
extern DEVLINK_S **gppstDevHead;
extern DEVLINK_S **gppstDevTail;
extern DEVLINK_S **gppstTempDevHead;
extern DEVLINK_S **gppstTempDevTail;

/******************* Dev使用变量 end***********************************/


/******************* 配置使用变量 begin***********************************/
extern IFNET_S *g_pstIfConfigNet;
extern IFNET_S *g_pstIfConfigNetTail;

/* extern IFNET_S         gstDefaultIf; */

/*-----------------------------------------------------------------------*\
*                    路由器硬件结构描述指针                               *
*                    指向stIfInfo                                         *
\*-----------------------------------------------------------------------*/
extern VRP_INTERFACE_S     * gpstIfInfo;
extern IF_MOD_INFO_S  gstIFModInfo;
/*-----------------------------------------------------------------------*\
*                   名字解析树入口向量指针                       *
\*-----------------------------------------------------------------------*/
extern PIF_ANAL_VECTOR_S    gpstIfTreeManage;

extern ULONG           gulIfIndexNum[IFNET_MAX_BOARD_NUM] ;    /* 记录索引数组大小 */
extern ULONG           gulIfIndexInsert[IFNET_MAX_BOARD_NUM];  /* 记录当前可分配的第一个索引 */
extern ULONG           gulIfIndexMaxUsed[IFNET_MAX_BOARD_NUM]; /* 记录当前已经使用的最大的索引下标 */
extern IFINDEX_S       *gpIfIndexArray[IFNET_MAX_BOARD_NUM];

/*-----------------------------------------------------------------------*\
*            在接口板上用于分配VA索引的全局数据结构                      *
\*-----------------------------------------------------------------------*/
extern ULONG           gulVAIfIndexNum[IFNET_MAX_BOARD_NUM] ;
extern ULONG           gulVAIfIndexInsert[IFNET_MAX_BOARD_NUM];
extern IFINDEX_S       *gpVAIfIndexArray[IFNET_MAX_BOARD_NUM];

extern ULONG   gulVAIfNum[MAXVTNum] ;
extern ULONG   gulVAIfInsert[MAXVTNum];
extern UCHAR   *gpVAIfArray[MAXVTNum];

extern NotifyIfState_HOOK_FUNC    g_pfNotifyIfState;

extern struct IIF_IFNET_ComIntFUNVtbl* g_pstIfFunVtbl;   /* 功能函数表 */
extern struct IIF_IFNET_ComIntCFGVtbl* g_pstIfCfgVtbl;   /* 配置函数表 */
extern struct IIF_IFNET_ComIntSSAVtbl* g_pstIfSSAVtbl;   /* 系统支持函数表 */

/* VISP1.8.1 支持1AG标准协议开发*/
extern UCHAR   g_ucIf1agDefaultVersion;

extern DEVLINK_S * DevLinkHead[VRP_MAX_BOARD_NUM];     /* 设备链头数组 */
extern DEVLINK_S * DevLinkTail[VRP_MAX_BOARD_NUM];     /* 设备链尾数组 */
extern DEVLINK_S * TempDevLinkHead[VRP_MAX_BOARD_NUM]; /* 临时设备链头数组 */
extern DEVLINK_S * TempDevLinkTail[VRP_MAX_BOARD_NUM]; /* 临时设备链尾数组*/

extern TCPIP_CreateLogicIf_HookFunc g_pfTCPIP_CreateLogicIf;
extern TCPIP_ADDR_HOOK_S g_stAddrHook;

#ifdef  __cplusplus
}
#endif

#endif  /* _IF_VAR_H_ */

