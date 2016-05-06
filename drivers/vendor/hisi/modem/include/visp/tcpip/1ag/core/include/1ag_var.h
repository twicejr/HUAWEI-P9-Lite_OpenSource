/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              1ag_var.h
*
*  Project Code: VISPV100R007
*   Module Name: 1AG  
*  Date Created: 2008-3-3
*        Author: yebo(62007)
*   Description: 1AG变量头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-3-3  yebo(62007)         Create the first version.
*
*******************************************************************************/
#ifndef _1AG_VAR_H
#define _1AG_VAR_H

#ifdef  __cplusplus
    extern "C"{
#endif

#include "tcpip/public/tcpip_basefun.h"

extern APP_INIT_INFO_S g_stOam1agAppInfo;

/*全局1AG报文类型,默认为8902*/
extern USHORT g_usOam1agPktType;
/*全局1AG报文优先级,默认为6*/
extern UCHAR g_ucOam1agPktPri;
/* 全局1AG兼容性开关 */
extern ULONG g_ulCompatibleSwitch;

extern ULONG g_ulMaxMdNum;
extern ULONG g_ulMaxMaNum;
extern ULONG g_ulMaxMepNum;
extern ULONG g_ulMaxRmepNum;

/*定义全局MD数组*/
extern OAM_1AG_MDCHAIN_S *g_pstMdChainTable;
/*定义全局MA数组*/
extern OAM_1AG_MACHAIN_S *g_pstMaChainTable;
/*定义全局MEP数组*/
extern OAM_1AG_MEPCHAIN_S *g_pstMepChainTable;
/*定义全局RMEP数组*/
extern OAM_1AG_RMEPCHAIN_S *g_pstRmepChainTable;

/*定义MEP超时定时器ID值*/
extern ULONG g_ulMepTimerId;
/*定义RMEP超时定时器ID值*/
extern ULONG g_ulRmepTimerId;

/*定义Ltr超时定时器ID值*/
extern ULONG g_ulLtrTimerId;

/*定义AIS超时定时器ID值*/
extern ULONG g_ulAISTimerId;


/*定义MEP 100ms双向链表*/
extern DLL_S g_stMep100msList;
/*定义MEP 1s双向链表*/
extern DLL_S g_stMep1sList;
/*定义MEP 10双向链表*/
extern DLL_S g_stMep10sList;

extern DLL_S *g_pstMepTimerList[3];

/*定义RMEP 100ms双向链表*/
extern DLL_S g_stRmep100msList;
/*定义RMEP 1s双向链表*/
extern DLL_S g_stRmep1sList;
/*定义RMEP 10双向链表*/
extern DLL_S g_stRmep10sList;

extern DLL_S *g_pstRmepTimerList[3];

/*LBr链表*/
extern DLL_S g_stLbrList;
/*Ltr链表*/
extern DLL_S g_stLtrList;

/*AIS  1s 链表*/
extern DLL_S g_st1sAISList;

/*AIS  1min 链表*/
extern DLL_S g_st1minAISList;

extern DLL_S *g_pstAISTimerList[2];

/*发起LB的总任务数*/
extern ULONG   g_ulTotalLBNum;
/*LB发送序号,全局唯一*/
extern ULONG   g_ulLbSequence;
/* 因为LB的序号任何值都是可能的，所以用链表来作为管理结构 */
extern DLL_S   g_stLBsequenceList;
/*1AG 报文调试开关*/
extern ULONG    g_ulDebugNormal1AGPktFlag;
/*1AG 错误报文调试开关*/
extern ULONG    g_ulDebugException1AGPktFlag;
/*1AG 报文详细信息调试开关*/
extern ULONG    g_ulDebug1AGVerboseFlag;
/*Verbose 打印次数*/
extern ULONG    g_ulDebug1AGVerbosePktNum;
/*Verbose 打印字节数*/
extern ULONG    g_ulDebug1AGVerbosePktOctets;

/*1AG 报文ha调试开关*/
extern ULONG    g_ulDebug1AGHAFlag;

/*1ag组件信息*/
extern OAM_1AG_MOD_INFO_S g_stOam1agModInfo;
/*HA统计信息*/
extern HA1AGSTAT_S   g_stHa1agStat; 
/*用户自定义报文处理函数*/
extern OAM_1AG_USERPINGPKTDEAL    g_pfUserPingPktDeal;
/*lt、lb输出信息*/
extern OAM_1AG_OUTINFO_HOOK_FUNC  g_pfOAM1AGOutputInfo;
/*1ag停止函数*/
extern OAM_1AG_STOP_HOOK_FUNC     g_pf1AGUserStop;
/*注册回调函数*/
extern OAM_1AG_SHELL_CALLBACK_S g_stOam1agshellFunc;
/*性能测试钩子函数*/
extern OAM_1AG_CAPTEST g_pfOam1agCapTest;
/* 收到不带VLAN的LB和LT报文时,存在多个不带VLAN的MEP的通知钩子函数 */
extern OAM_1AG_MORENOVLANNOTIFY_HOOK_FUNC g_pfOam1agMoreNoVlanNotifyFunc;

/* 1AG模块的IFNET组件功能虚表指针 */
extern struct IIF_IFNET_ComIntFUNVtbl *g_pstOam1agIfnetFunTable;
/* 1AG模块的ETHARP组件功能虚表指针 */
extern struct IIF_COMP_ETHERNET_ComIntCFGVtbl *g_pstOam1agEthCfgTable;
/* 1AG模块的Trunk组件配置虚表指针 */
extern struct IIF_COMP_TRUNK_ComIntCFGVtbl *g_pstOam1agTrunkCfgTable;
/* 1AG模块的Trunk组件功能虚表指针 */
extern struct IIF_COMP_TRUNK_ComIntFUNVtbl *g_pstOam1agTrunkFunTable;

/* 1AG模块组件配置虚表指针 */
extern struct IIF_COMP_OAM1AG_ComIntCFGVtbl *g_pstOam1agCfgTable;
/* 1AG模块组件功能虚表指针 */
extern struct IIF_COMP_OAM1AG_ComIntFUNVtbl *g_pstOam1agFuncTable;

/* 1AG模块L2IF功能虚表指针 */
extern struct IIF_COMP_L2IF_ComIntFUNVtbl *g_pst1AGL2ifIntFunTbl;
/* 1AG模块VRRP功能虚表指针 */
extern struct IIF_COMP_VRRP_ComIntCFGVtbl *g_pstOam1agVrrpCfgTable;


/* 全局LTM数组 */
extern OAM_1AG_LTM_SENDOUTDATA_S *g_pstLtmSendOutData[OAM_1AG_MAX_LTMSEND];

/*LTM发送序列号*/
extern ULONG g_ulLtmSendId;
/*CCM发送序列号*/
extern ULONG g_ulCcmSendId;
/*当前MA数目,对应VLAN值*/
extern ULONG g_ulCurrentMaNum;

/* 用于设置老化时间，仅供测试使用 */
extern ULONG g_ulRmepOldTime;


extern VOS_VOID   VOS_GetCpuTick(ULONG *plow,ULONG *phigh);
extern ULONG VOS_TaskLock(VOS_VOID);
extern ULONG VOS_TaskUnlock(VOS_VOID);
extern ULONG TCPIP_Free(VOID* pBuf);
extern VOID *TCPIP_Malloc(ULONG ulInfo, ULONG ulSize);
extern VOID OAM_1AG_DebugInfo(CHAR* pcString);


extern ULONG g_ulRmepCCDetectMode; /*Added by luogaowei 2013-2-2 新增预配置值 在Hert3.3.中将下发和启动CC 分离 DTS2013020403949*/
#ifdef  __cplusplus
}
#endif

#endif
