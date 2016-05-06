/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dchpr_typ.h
*
*  Project Code: VISPV1R6
*   Module Name: DHCP4R  
*  Date Created: 2007-6-27
*        Author: LY(57500)
*   Description: DHCP4R模块的数据结构定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2007-6-27  LY(57500)     Create the first version.
*
*******************************************************************************/
#ifndef _DHCP4R_TYP_H_
#define _DHCP4R_TYP_H_

#ifdef __cplusplus
extern "C"{
#endif


/* 82选项配置控制块 */
typedef struct tagDHCP4ROption82
{
    /*ULONG   ul82SetFlag;  */      /* 子选项设置标记 */
    DHCP4R_SUBOPTION82_S astSubOption82[DHCP4R_82_SUB_NUM];   /* 子选项数组 */
}DHCP4R_OPTION82_S;

/* relay配置控制块 */
typedef struct tagDHCP4RCfgNode
{
    DLL_NODE_S          stDLLNode;
    ULONG               ulIfIndex;      /* 配置接口索引,如果为全局配置，则index为0 */
    ULONG               ulRelayFlag;    /* relay的配置标记      */
    ULONG               ulEnableStatus; /* 使能状态             */    
    ULONG               ulServerNum;    /* 配置的中继地址数目   */
    ULONG               aulServer[DHCP4R_SERVER_MAX_NUM];   /* 中继地址数组 */
    DHCP4R_OPTION82_S   stOption82;     /* 82选项配置   */
    ULONG               ulOpt82Mode;     /* 82选项模式*/ 
}DHCP4R_CFG_NODE_S;

/* 接口调试开关控制块 */
typedef struct tagDHCP4RDebug
{
    DLL_NODE_S          stDLLNode;
    ULONG               ulIfIndex;    
    ULONG               ulDebug;
}DHCP4R_DEBUG_NODE_S;  

#define     DLLDHCP4RCFG(x)      ((DHCP4R_CFG_NODE_S *)(x)) 
#define     DLLDHCP4RDEBUG(x)    ((DHCP4R_DEBUG_NODE_S *)(x))  


/* Shell向Core注册的回调函数集 */
typedef struct tagDHCP4RShellCallbackSet
{
    /* 调试信息输出函数 */
    VOID (*pfDHCP4R_DebugOutString) (CHAR * szStr);
}DHCP4R_SHELL_CALLBACK_SET_S;


/* 为支持VRF特性而增加的数据结构 */
typedef struct tagDHCP4RCfgVrfEntry
{
    ULONG   ulVrfIndex;               /* 实例号 */    
    DLL_S   stDhcp4rCfgList;          /* 该实例接口配置链表 */
    ULONG   ulDHCP4RFwdMode;          /* 该实例中继方式,初试值0,分担方式 */
    ULONG   ulDHCP4RMaxHops;          /* 该实例 最大RELAY跳数,初试值为16 */
    UCHAR   ucDHCP4RTos;              /* 该实例TOS值,默认为0 */
    UCHAR   ucDHCP4RCfgMode;          /* 该实例Relay 配置方式，全局(1),接口(0) */
    UCHAR   ucpad[2];
    DHCP4R_STATINFO_S stDhcp4rStat;   /* 该实例统计信息 */
}DHCP4R_CFG_VRF_S;

typedef struct tagDHCP4RDbgVrfEntry
{
    ULONG   ulVrfIndex;               /* 实例号 */
    DLL_S   stDhcp4rDebugList;        /* 该实例Debug开关链表 */
    ULONG   ulDHCP4RGlobalDebug;      /* 该实例全局调试开关 */ 
}DHCP4R_DBG_VRF_S;

#ifdef __cplusplus
}
#endif      /* end of _cplusplus        */

#endif      /* end of _DHCP4R_TYP_H_    */

