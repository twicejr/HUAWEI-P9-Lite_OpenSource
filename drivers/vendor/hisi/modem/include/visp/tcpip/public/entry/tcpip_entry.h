/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_entry.h
*
*  Project Code: VISPV1R5
*   Module Name: PUBLIC  
*  Date Created: 2006-6-15
*        Author: X36317
*   Description: 此文件定义了tcpip_entry.c中使用的数据结构和宏等
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-6-15  X36317         Creat the first version.
*
*******************************************************************************/

#ifndef _TCPIP_ENTRY_H_
#define _TCPIP_ENTRY_H_
#ifdef  __cplusplus
extern "C"{
#endif

#include "tcpip/public/tcpip_pub_api.h"

#define APP_MAX_REG_NUM         256 /* Also include old version apps!! */

/*Modified by X36317, 大小从16调整到15，以保证结构体4字节对齐, 2006-05-12*/
#define APP_NAME_MAX_LEN        15 
/*Modified by X36317, 大小从4调整到7，以保证结构体4字节对齐, 2006-05-12*/
#define APP_TASK_NAME_LEN       7  
#define APP_TASK_PARA_NUM       4

typedef VOID  (*APP_TASK_ENTRY) (UINTPTR ulArg0, UINTPTR ulArg1, UINTPTR ulArg2, UINTPTR ulArg3);
typedef ULONG (*APP_INIT_FUNC)();
typedef VOID  (*APP_MIB_REG)();
typedef VOID  (*APP_IFNET_HOT_NOTIFY_CB)(ULONG ulEvent, ULONG ulSlot, VOID * pstIfnet, ULONG ulIfIndex);
typedef ULONG (*APP_CFA_CB)(VOID *, VOID **);


typedef struct tagAPP_INIT_INFO
{
    ULONG                   ulMID;                          /*MID*/
    UCHAR                   szAppName[APP_NAME_MAX_LEN + 1];    /*Application name, '\0' terminated */
    VOID                   *pstComponentInfo;

    APP_TASK_ENTRY          pfTaskEntry;                    /*Task entry, NULL for no own task*/
    UCHAR                   szTaskName[APP_TASK_NAME_LEN + 1];  /*Task name, zero terminated*/
    ULONG                   ulTaskPriority;                 /*Task priority*/   
    ULONG                   ulTaskMode;                     /*task mode*/
    ULONG                   ulTaskStackSize;                /*task stack size */
    UINTPTR                 ulTaskArg[APP_TASK_PARA_NUM];   /*task entry parameters*/

    APP_INIT_FUNC           pfAppInit;
    APP_MIB_REG             pfMibReg;                       /*register MIB*/
    APP_IFNET_HOT_NOTIFY_CB pfIfnetHotNotifyCB;
    APP_CFA_CB              pfCfaCB;                        /*config process func on IO board*/

    CHAR                  **ppcExecInfor_EN;                
    CHAR                  **ppcExecInfor_CN;                
    CHAR                  **ppcExecInfor_EXTD;              

    ULONG                   ulAppIndex;                     /*to store app id*/ 
    ULONG                   ulTaskId;                       /*to store the task ID*/
    ULONG                   ulExecInforIndex;               /*to store the execinfo index*/

}APP_INIT_INFO_S;

/*系统初始化返回的错误码定义*/
typedef enum tagSYS_INIT_ERROR
{
    SYS_INIT_OK = 0,
    SYS_INIT_ERR,
    SYS_INIT_NULL_PTR,
    SYS_INIT_NO_MEM,
    SYS_INIT_ERR_DUPLICATED,
    SYS_INIT_ERR_TOO_MANY_APPS,
    SYS_INIT_REG_COMP_FAIL,

    SYS_INIT_ERR_MAX
}SYS_INIT_ERROR_EN;

typedef struct tagTCPIP_PRECFG_VALUE
{
    ULONG ulKey;        /* 预配置参数ID */
    ULONG ulCfg_Value;  /* 配置值 */
    ULONG ulMin_Value;  /* 可配置值的下限 */
    ULONG ulMax_Value;  /* 可配置值的上限 */
}TCPIP_PRECFG_VALUE_S;


/*SOCKRUN的定时器消息队列*/
#define VRP_SOCK_QUEUE_TIMER_NAME       "SKTM"
#define VRP_SOCK_QUEUE_TIMER_LENGTH     2048
#define VRP_SOCK_QUEUE_TIMER_MODE       VOS_Q_FIFO | VOS_Q_ASYN

#define VRP_SOCK_QUEUE_DEFAULTSIZE   1024 /* 创建队列时指定的默认长度 */
/*Added by zhukun*/ /*IPv6 Pmtu消息队列*/
#define VRP_SOCK_QUEUE_PMTU_NAME        "SKPM"
#define VRP_SOCK_QUEUE_PMTU_LENGTH      2048
#define VRP_SOCK_QUEUE_PMTU_MODE        VOS_Q_FIFO | VOS_Q_ASYN
extern  ULONG                           ulSOCKPmtuQueID;


 /* 报文转发任务 */
#define VRP_TASK_SOCK_NAME          "SOCK"
#define VRP_TASK_SOCK_ENTRY         VRP_SockRun
#define VRP_TASK_SOCK_PRIO          100
#define VRP_TASK_SOCK_MODE          0       /* means default value: T_NOPREEMPT | T_NOTSLICE */
#define VRP_TASK_SOCK_SSIZE         16384   /* 为避免后续出现任务栈空间不足，将创建任务时的默认栈空间大小修改为16K，
                                               而非原来的2K */
#define VRP_TASK_SOCK_ARG           0       /* means no argument */

/* 第三方任务*/
#define VRP_TASK_DELAY_NAME         "SWITCH"
#define VRP_TASK_DELAY_ENTRY        VRP_TaskSwitch
#define VRP_TASK_DELAY_PRIO         64
#define VRP_TASK_DELAY_MODE         0      /* means default value: T_NOPREEMPT | T_NOTSLICE */
#define VRP_TASK_DELAY_SSIZE        2048   /* means default value: 2048 */

VOID TCPIP_InfoOutput(CHAR *pInfo);
#define TCPIP_printf TCPIP_InfoOutput

/*--------------------------------*/
/* 公共事件位:定时器事件          */
/*--------------------------------*/
#define VRP_EVENT_TIMERREQ          0X00008000  /* "00000000 00000000 10000000 00000000" */


/*-----------------------------------------*/
/* SockRun任务的私有事件:数据事件/控制事件 */
/*-----------------------------------------*/
#define VRP_SOCK_EVENT_DATAREQ      0X00000001  /* "00000000 00000000 00000000 00000001" */
#define VRP_DELAY_EVENT_SWITCH      0X00000002

#define VRP_SOCK_EVENT_CTRL         0X00000004  /* 底层(NP/DRIVER)控制事件上报 */
#define VRP_SOCK_EVENT_MOD2MOD      0X00000008  /* 用于module间通信 */

/* 底层事件对应的消息类型，组成:主类型(依模块划分) + 次类型(各模块自己区分) */
/* sockrun根据主类型分发,各模块事件处理函数根据次类型进行不同处理 */
/* 参考函数 TCPIP_DealLinkCtlMsgs */
typedef enum enLINKMSG
{   
    /* IFNET */
    LINK_MSG_IF             = 0x00010000,
    LINK_MSG_IF_IOCTL       = 0x00010001,

    /* ETHARP */
    LINK_MSG_ETH            = 0x00020000,
    LINK_MSG_ETH_ARPMISS    = 0x00020001,

    /* EOAM 3AH */
    LINK_MSG_3AH            = 0x00030000,
    LINK_MSG_3AH_NPLOSTLINK = 0x00030001,
    LINK_MSG_3AH_ERRPRDEVT  = 0x00030002,
    LINK_MSG_3AH_ERRFRMEVT  = 0x00030003,

    /*OAM 1AG*/
    LINK_MSG_1AG            = 0x00040000,
    LINK_MSG_1AG_CCMSG      = 0x00040001,

    /* MSTP*/
    LINK_MSG_MSTP_TO_L2IF   = 0x00050000,

    LINK_MSG_PUBLIC_CC       = 0x00060000,
    LINK_MSG_PUBLIC_DCC      = 0x00060001,
    LINK_MSG_PUBLIC_NCC      = 0x00060002,

    /* GR PPP */
    LINK_MSG_GRPPP          =  0x00070000,
    LINK_MSG_GRPPP_RESTORE  =  0x00070001,
    LINK_MSG_GRPPP_SMOOTH   =  0x00070002,
    
    /* GR POEC */
    LINK_MSG_GRPOEC           =  0x00080000,
    LINK_MSG_GRPOEC_RESTORE   =  0x00080001,
    LINK_MSG_GRPOEC_SMOOTH    =  0x00080002,

    /* Add for V2R3C07, by z00208058/w00207740, at 2012-4-16. 修改原因: TRUNK LACP下移需求开发 */
    /* Trunk Lacp  */
    LINK_MSG_LACP                     =  0x00090000,
    TRUNK_LACP_NOTIFY_RCV_TIMEOUT     =  0x00090001,
    LINK_MSG_NSR_PPI_MASTER_BOARD     =  0x00090002,
    LINK_MSG_NSR_PPI_SLAVE_BOARD      =  0x00090003,
    LINK_MSG_NSR_PHYINFET_READY       =  0x00090004,
    
    /* LINK CTRL MSG END */
    LINK_MSG_END            = 0xFFFFFFFF    
}LINKMSG_E;
#define LINK_MSG_MAJOR_MASK   0xFFFF0000



typedef enum TASK_MONITOR_TASK_INDEX
{
   TASK_MONITOR_TIMER_ID_SOCK = 0, /*Task monitor for sockrun*/
   TASK_MONITOR_TIMER_ID_BFD = 1,  /*Task monitor for bfd task*/
   TASK_MONITOR_TIMER_ID_TWAMP_CLIENT = 2,  /*Task monitor for TWAMP Client task*/
   TASK_MONITOR_TIMER_ID_TWAMP_REFL = 3,  /*Task monitor for TWAMP Reflector task*/
   TASK_MONITOR_TIMER_ID_MAX = 5  /*TASK_MONITOR_TASK_MAX_NUM */
}TASK_MONITOR_TASK_INDEX_E;

typedef enum TASK_MONITOR_TASK_STATE
{
   TASK_MONITOR_STATE_INIT = 0,    /*init , not register*/
   TASK_MONITOR_STATE_SUCCESS = 1, /*register ok*/
   TASK_MONITOR_STATE_FAIL = 2 /*TASK_MONITOR_TASK_MAX_NUM */
}TASK_MONITOR_TASK_STATE_E;

typedef struct tagTaskMonitorInfo
{
    ULONG ulVosTaskId;          /*VOS task id*/
    ULONG ulTaskMonitorTimerId; /*定时器id*/
    ULONG ulTaskMonitorRegState;/*注册状态*/
}TASKMONITORINFO_S;

#define TASK_MONITOR_KEEPLIVE_TIME  5000  /*MBSC 定制需求: 线程监视 心跳周期 5秒*/
#define TASK_NONITOR_MAX_LOST_TIME  6     /*线程监视 最多丢失次数*/
#define TASK_MONITOR_TASK_MAX_NUM   5    /*定义需要监视的任务个数*/


/*Added by zhukun*/ /*IPv6 Pmtu的两个事件*/
#define VRP_EVENT_PMTUREQ           0X00080000  /* "00000000 00001000 00000000 00000000" */
#define VRP_EVENT_PMTUFLUSH         0X00100000  /* "00000000 00010000 00000000 00000000" */

extern ULONG TCPIP_CreateMutex(CHAR *pMutexName, ULONG *pulMutexID);
extern ULONG TCPIP_CreateSm(CHAR * pCountName, ULONG ulSmInit, ULONG * pulCountID);
extern ULONG TCPIP_SmP(ULONG ulMutexID);
extern ULONG TCPIP_SmV(ULONG ulMutexID);
extern ULONG TCPIP_DeleteMutex(ULONG ulMutexID);

#define TCPIP_BEGIN_PT(ulSem) (VOID)TCPIP_SmP(ulSem)

#define TCPIP_END_PT(ulSem) (VOID)TCPIP_SmV(ulSem)
#define TCPIP_UNREFERENCED_PARAMETER(P) { (P) = (P); }

ULONG SYS_RegAppInfo(APP_INIT_INFO_S *);

/*链路层定时器的超时时间*/
#define LINKQUETIMEOUT  10 

/* 底层上报事件次数统计 */
typedef struct tagTCPIP_CTRLMSG_COUNT
{
    ULONG ulUpCount;
    ULONG ulDownCount;
    ULONG ulDownAllCount;
    ULONG ulSpeedCount;
    ULONG ulSetMacCount;
    ULONG ulArpMissCount;
}TCPIP_CTRLMSG_COUNT_S;

extern ULONG ulVRPTID_SOCK;      
extern ULONG ulSOCKTmrQueID; 

extern ULONG g_ulSemForTightMods;
/*Add by q62011 for DTS2013011509185 大规格配置性能优化*/
extern ULONG g_ulSemForI3Ifnet;
extern ULONG g_ulLinkQueTimerID;
extern ULONG g_ulLinkMaxPkt; 
extern ULONG g_ulLinkPktNum;
extern ULONG g_ulVrfNum;

ULONG TCPIP_IC_SendMsg(ULONG ulMId, ULONG ulInfoId, char *pBuf);
ULONG TCPIP_Set_ICDbgLevel(ULONG ulLevel);

/* ACL模块注册的匹配钩子函数，由pp4模块和以太模块调用 */
typedef ULONG (*ACL_CLASSIFYBYIPINFO_HOOK_FUNC)(VOID *pstMBUF, ULONG ulGroupNum, ULONG * pulRuleIndex, BOOL_T* pbLog);

typedef ULONG (*ACL_CLASSIFYBYIFINFO_HOOK_FUNC)(VOID *pstMBUF, ULONG ulIfType, ULONG ulGroupNum, ULONG * pulRuleIndex, BOOL_T* pbLog);
typedef ULONG (* ACL_CLASSIFYBYLINKINFO_HOOK_FUNC)(VOID *pstMBUF, ULONG ulGroupNum,
                                                            ULONG* pulRuleIndex, BOOL_T* pbLog);

/* mstp cbb初始化时注册钩子函数,供etharp模块使用*/
typedef ULONG (*MSTP_PORT_IS_ENABLE_HOOK_FUNC)(ULONG ulIfIndex, ULONG *pulIsEnable);
typedef ULONG (*MSTP_ISEDGEPORT_HOOK_FUNC)(ULONG ulIfIndex, ULONG *pulIsEdgePort);


extern ACL_CLASSIFYBYIPINFO_HOOK_FUNC g_pfACL_ClassifyByIpInfo;
extern ACL_CLASSIFYBYIFINFO_HOOK_FUNC g_pfACL_ClassifyByIfInfo;
extern ACL_CLASSIFYBYLINKINFO_HOOK_FUNC g_pfACL_ClassifyByLinkInfo;

extern MSTP_PORT_IS_ENABLE_HOOK_FUNC g_pfMstp_PortIsEnable;
extern MSTP_ISEDGEPORT_HOOK_FUNC g_pfMstp_IsEdgePort;

/* Queue id of link/driver/np layer's ctrl msgs */
extern ULONG   g_ulLinkIoCtlMsgQueID; 

/* Queue id of mstp event msgs*/
extern ULONG   g_ulMod2ModEvtQueID;

typedef ULONG (*PAF_SHOWNDEFFECTVALUE_HOOK_FUN)(VOID);

VOID TCPIP_DealLinkCtlMsgs(VOID);
VOID TCPIP_DealMod2ModMsgs(VOID);

ULONG TCPIP_Get_PreConfigPara(TCPIP_PRECFG_VALUE_S *pstComPara);
ULONG TCPIP_LinkCtlMsgCount(UINTPTR aulMsg[4]);


extern ULONG g_ulVispInitDone;

extern VOID TCPIP_TaskMonitor_CretaeTimerProc(ULONG ulTaskId, ULONG ulQueId, ULONG  ulTimerNo, ULONG ulPeriod);

extern VOID TCPIP_TaskMonitor_HeartTimerProc(VOID *pPara);
extern ULONG Sock_CreateMonitorTime(VOID);

VOID TCPIP_ReceivePhyFinish(VOID);
VOID TCPIP_NotifyNSRPhyFinish(VOID);

extern ULONG Sock_GetCurrentTime(ULONG* pulHighTime, ULONG* pulLowTime);

extern ULONG TCPIP_JudgeTimeout(ULONG ulCurValue, ULONG ulTOValue, ULONG ulThreshold);


/*Begin 2013-02-07 liangjicheng 增加Linux 默认栈配置 默认值:8M 考虑DLC任务嵌套*/

#define  LINUX_DEFAULTSTACKSIZE 1024*1024*8
#define  LINUX_MAXSTACKSIZE 1024*1024*16

/*End   2008-09-10 liangjicheng */

#ifdef  __cplusplus
}
#endif
#endif


