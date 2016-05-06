/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   :
  Version     : V100R001
  Date        : 2005-04-19
  Description :
  History     :
  1. Date:2005-04-19
     Author: w29695
     Modification:Create
  2.日    期  : 2006年11月18日
    作    者  : luojian id:60022475
    修改内容  : 根据问题单号A32D06616
  3.日    期   : 2007年02月25日
    作    者   : luojian 60022475
    修改内容   : 问题单号：A32D08962,140芯片版本信息修改
*******************************************************************************/

#ifndef _PS_CONFIG_H_
#define _PS_CONFIG_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif    /* __cpluscplus   */
#endif    /* __cpluscplus   */

#include "wuepscfg.h"
#include "frmwkext.h"


/****************************************************************
 * wueps系统内部线程ID定义
 *
 ***************************************************************/
#define ADMIN_THREAD_ID                         0                               /* WUEPS系统admin模块                       */
#define AGENT_THREAD_ID                         1                               /* 标识外部AGENT模块                        */
#define WRR_THREAD_ID                           2
#define WCOM_THREAD_ID                          3
#define RESERVE1_THREAD_ID                      4
#define RESERVE2_THREAD_ID                      5

#if 0
#define RRC_MAIN_THREAD_ID                      2
#define RRC_MEAS_THREAD_ID                      3
#define RRC_SYSINFO_RCV_THREAD_ID               4
#define RRC_PLMN_CELL_SELECT_THREAD_ID          5
#endif

#define PDCP_THREAD_ID                          6
#define RLC_THREAD_ID                           7
#define MAC_THREAD_ID                           8
#define L1C_THREAD_ID                           9                               /* 标识外部RTT模块                          */
#define RABM_THREAD_ID                          10
#define MM_THREAD_ID                            11
#define MMC_THREAD_ID                           12
#define GMM_THREAD_ID                           13
#define CC_THREAD_ID                            14
#define SM_THREAD_ID                            15
#define APP_THREAD_ID                           16                              /* 标识外部APP模块                          */
#define TAF_THREAD_ID                           APP_THREAD_ID
#define SMA_THREAD_ID                           APP_THREAD_ID
#define SMS_THREAD_ID                           17
#define SS_THREAD_ID                            18
#define TC_THREAD_ID                            19
#define SMT_THREAD_ID                           20
#define USIM_THREAD_ID                          21                              /* 标识外部USIM模块                         */
#define GAS_MAIN_THREAD_ID                      22
#define TTF_LLC_THREAD_ID                       23
#define WUEPS_MAX_THREAD                        24                              /* WUEPS系统中最大的线程个数                */


/****************************************************************
 * 每个线程的内存池的操作标识
 *
 ***************************************************************/
#define VOS_MEMPOOL_INDEX_ADMIN                 0
#define VOS_MEMPOOL_INDEX_AGENT                 0
#define VOS_MEMPOOL_INDEX_WRR                   0
#define VOS_MEMPOOL_INDEX_WCOM                  0
#define VOS_MEMPOOL_INDEX_RESERVE1              0
#define VOS_MEMPOOL_INDEX_RESERVE2              0

#if 0
#define VOS_MEMPOOL_INDEX_RRC_MAIN              0
#define VOS_MEMPOOL_INDEX_RRC_MEAS              0
#define VOS_MEMPOOL_INDEX_RRC_SYSINFO_RCV       0
#define VOS_MEMPOOL_INDEX_RRC_PLMN_CELL_SELECT  0
#endif

#define VOS_MEMPOOL_INDEX_PDCP                  0
#define VOS_MEMPOOL_INDEX_RLC                   0
#define VOS_MEMPOOL_INDEX_MAC                   0
#define VOS_MEMPOOL_INDEX_L1C                   0
#define VOS_MEMPOOL_INDEX_NAS                   0
#define VOS_MEMPOOL_INDEX_RABM                  0
#define VOS_MEMPOOL_INDEX_MM                    0
#define VOS_MEMPOOL_INDEX_MMC                   0
#define VOS_MEMPOOL_INDEX_GMM                   0
#define VOS_MEMPOOL_INDEX_TC                    0
#define VOS_MEMPOOL_INDEX_L1A                   0
#define VOS_MEMPOOL_INDEX_APP                   0
#define VOS_MEMPOOL_INDEX_TAF                   0
#define VOS_MEMPOOL_INDEX_SMA                   0
#define VOS_MEMPOOL_INDEX_USIM                  0
#define VOS_MEMPOOL_INDEX_SMT                   0
#define VOS_MEMPOOL_INDEX_GAS                   0
#define VOS_MEMPOOL_INDEX_TTF_LLC               0


#define WUEPS_MEMORY_POOL_CNT                   1

/****************************************************************
 * 每个线程的消息队列的操作标识
 *
 ***************************************************************/
#define VOS_MSG_QUEUE_HANDLER_ADMIN     &WuepsThreadInfo[ADMIN_THREAD_ID].MsgQueueId
#define VOS_MSG_QUEUE_HANDLER_AGENT     &WuepsThreadInfo[AGENT_THREAD_ID].MsgQueueId
#define VOS_MSG_QUEUE_HANDLER_WRRC      &WuepsThreadInfo[WRR_THREAD_ID].MsgQueueId
#define VOS_MSG_QUEUE_HANDLER_WCOM      &WuepsThreadInfo[WCOM_THREAD_ID].MsgQueueId
#define VOS_MSG_QUEUE_HANDLER_RESERVE1  &WuepsThreadInfo[RESERVE1_THREAD_ID].MsgQueueId
#define VOS_MSG_QUEUE_HANDLER_RESERVE2  &WuepsThreadInfo[RESERVE2_THREAD_ID].MsgQueueId

#if 0
#define VOS_MSG_QUEUE_HANDLER_RRC_MAIN  &WuepsThreadInfo[RRC_MAIN_THREAD_ID].MsgQueueId
#define VOS_MSG_QUEUE_HANDLER_RMF       &WuepsThreadInfo[RRC_MEAS_THREAD_ID].MsgQueueId
#define VOS_MSG_QUEUE_HANDLER_RSRF      &WuepsThreadInfo[RRC_SYSINFO_RCV_THREAD_ID].MsgQueueId
#define VOS_MSG_QUEUE_HANDLER_RCSF      &WuepsThreadInfo[RRC_PLMN_CELL_SELECT_THREAD_ID].MsgQueueId
#endif

#define VOS_MSG_QUEUE_HANDLER_PDCP      &WuepsThreadInfo[PDCP_THREAD_ID].MsgQueueId
#define VOS_MSG_QUEUE_HANDLER_RLC       &WuepsThreadInfo[RLC_THREAD_ID].MsgQueueId
#define VOS_MSG_QUEUE_HANDLER_MAC       &WuepsThreadInfo[MAC_THREAD_ID].MsgQueueId
#define VOS_MSG_QUEUE_HANDLER_L1C       &WuepsThreadInfo[L1C_THREAD_ID].MsgQueueId
#define VOS_MSG_QUEUE_HANDLER_HPA       VOS_MSG_QUEUE_HANDLER_L1C
#define VOS_MSG_QUEUE_HANDLER_RABM      &WuepsThreadInfo[RABM_THREAD_ID].MsgQueueId
#define VOS_MSG_QUEUE_HANDLER_MM        &WuepsThreadInfo[MM_THREAD_ID].MsgQueueId
#define VOS_MSG_QUEUE_HANDLER_MMC       &WuepsThreadInfo[MMC_THREAD_ID].MsgQueueId
#define VOS_MSG_QUEUE_HANDLER_GMM       &WuepsThreadInfo[GMM_THREAD_ID].MsgQueueId
#define VOS_MSG_QUEUE_HANDLER_CC        &WuepsThreadInfo[CC_THREAD_ID].MsgQueueId
#define VOS_MSG_QUEUE_HANDLER_SM        &WuepsThreadInfo[SM_THREAD_ID].MsgQueueId
#define VOS_MSG_QUEUE_HANDLER_APP       &WuepsThreadInfo[APP_THREAD_ID].MsgQueueId
#define VOS_MSG_QUEUE_HANDLER_TAF       VOS_MSG_QUEUE_HANDLER_APP
#define VOS_MSG_QUEUE_HANDLER_SMA       VOS_MSG_QUEUE_HANDLER_APP
#define VOS_MSG_QUEUE_HANDLER_SMS       &WuepsThreadInfo[SMS_THREAD_ID].MsgQueueId
#define VOS_MSG_QUEUE_HANDLER_SS        &WuepsThreadInfo[SS_THREAD_ID].MsgQueueId
#define VOS_MSG_QUEUE_HANDLER_TC        &WuepsThreadInfo[TC_THREAD_ID].MsgQueueId
#define VOS_MSG_QUEUE_HANDLER_SMT       &WuepsThreadInfo[SMT_THREAD_ID].MsgQueueId
#define VOS_MSG_QUEUE_HANDLER_USIM      &WuepsThreadInfo[USIM_THREAD_ID].MsgQueueId
#define VOS_MSG_QUEUE_HANDLER_GAS       &WuepsThreadInfo[GAS_MAIN_THREAD_ID].MsgQueueId
#define VOS_MSG_QUEUE_HANDLER_TTF

#define WUEPS_MSG_QUEUE_CNT             WUEPS_MAX_THREAD                        /* WUEPS系统中Message Queue的个数           */

#define VOS_MSG_QUEUE_HANDLER_RRC_MAIN  VOS_MSG_QUEUE_HANDLER_WRRC


/****************************************************************
 * 使用的互斥量的操作标识
 *
 ***************************************************************/
extern  MUTEX_ID    g_MutexRlcMacLEntityInfo;                                   /* MAC -- RLC                               */
extern  MUTEX_ID    g_MutexRrcRlcHfn;                                           /* RLC -- RRC                               */
extern  MUTEX_ID    g_MutexRrcMacRachInfo;                                      /* MAC -- RRC                               */
extern  MUTEX_ID    g_MutexRrcMacInfo;                                          /* MAC -- RRC                               */
extern  MUTEX_ID    g_MutexRrcRcsfInfo;                                         /* Rcsf -- RRC                              */
extern  MUTEX_ID    g_MutexRcsfRmfInfo;                                         /* Rcsf -- Rmf                              */
extern  MUTEX_ID    g_MutexMacDataProtection;                                   /* Mac */
extern  MUTEX_ID    g_MutexRrcRlcMacCk;                                         /* Rrc, Rlc, Mac                            */
extern  MUTEX_ID    g_MutexRlcHpaAmCipher;
extern  MUTEX_ID    g_MutexRlcHpaUmCipher;
extern  MUTEX_ID    g_MutexMacHpaTmCipher;

#define VOS_MUTEX_RLC_MAC_LCH_ENTITY_INFO_HANDLER \
                                    &g_MutexRlcMacLEntityInfo                   /* MAC -- RLC                               */
#define VOS_MUTEX_RRC_RLC_HFN_HANDLER \
                                    &g_MutexRrcRlcHfn                           /* RLC -- RRC                               */
#define VOS_MUTEX_RRC_MAC_RACH_INFO_HANDLER \
                                    &g_MutexRrcMacRachInfo                      /* MAC -- RRC                               */
#define VOS_MUTEX_RRC_MAC_INFO_HANDLER \
                                    &g_MutexRrcMacInfo                          /* MAC -- RRC                               */
#define VOS_MUTEX_RRC_RCSF_INFO_HANDLER \
                                    &g_MutexRrcRcsfInfo                         /* Rcsf -- RRC                              */
#define VOS_MUTEX_RCSF_RMF_INFO_HANDLER \
                                    &g_MutexRcsfRmfInfo                         /* Rcsf, Rsrf, RRC                          */
#define VOS_MUTEX_MAC_DATA_PROTECTION_INFO_HANDLER \
                                    &g_MutexMacDataProtection                         /* Mac Data Protection */
#define VOS_MUTEX_RRC_RLC_MAC_CK_HANDLER \
                                    &g_MutexRrcRlcMacCk


/****************************************************************
 * 使用的信号量的操作标识
 *
 ***************************************************************/
extern SEMAPHORE_ID  g_SemaPhoreMm;
extern SEMAPHORE_ID  g_SemaPhoreRlcHpaAmCipher;
extern SEMAPHORE_ID  g_SemaPhoreRlcHpaUmCipher;
extern SEMAPHORE_ID  g_SemaPhoreMacHpaTmCipher;
extern SEMAPHORE_ID  g_SemaPhoreRrcHpaIntegrity;

#define VOS_SEMA_MM_HANDLER     \
                                    &g_SemaPhoreMm
#define VOS_SEMA_RLC_HPA_AM_CIPHER_HANDLER \
                                    &g_SemaPhoreRlcHpaAmCipher
#define VOS_SEMA_RLC_HPA_UM_CIPHER_HANDLER \
                                    &g_SemaPhoreRlcHpaUmCipher
#define VOS_SEMA_MAC_HPA_TM_CIPHER_HANDLER \
                                    &g_SemaPhoreMacHpaTmCipher
#define VOS_SEMA_RRC_HPA_INTEGRITY_HANDLER \
                                    &g_SemaPhoreRrcHpaIntegrity

/****************************************************************
 * WUEPS message queue information
 *
 ****************************************************************/
typedef struct t_cmsgque {
    VOS_CHAR            pcName[20];                                                 /* 消息队列的名字                           */
    VOS_UINT32           QueStartAdr;                                                /* 设置消息队列的起始地址                   */
    VOS_UINT32           MsgSize;                                                    /* 每条消息的字节数                         */
    VOS_UINT32           MsgCnt;                                                     /* 消息的条数                               */
    VOS_UINT32           WaitOption;                                                 /* 消息收发时等待与否标志                   */
    VOS_UINT32           ulValid;                                                    /* 消息队列是否要创建的标志                 */
} WUEPS_MSG_QUEUE_INFO_STRU;
/****************************************************************
 * WUEPS系统中每个线程的信息
 *
 ***************************************************************/
typedef struct t_ctsk {
    VOS_CHAR            ThreadName[20];                                             /* 线程名称（暂不用）                       */
    VOS_VOID*       FunName;                                                    /* TASK启动地址                             */
    VOS_UINT32           FunPara;                                                    /* 启动函数参数                             */
    VOS_UINT32           StackStart;                                                 /* 堆栈的起始地址                           */
    VOS_UINT32           StackSize;                                                  /* 堆栈的大小                               */
    VOS_UINT32           Priority;                                                   /* 线程的优先级                             */
    VOS_VOID*       DummyFunName;                                               /* TASK启动地址                             */
    VOS_UINT32           ulValid;                                                    /* 线程是否要创建的标志                     */
} WUEPS_THREAD_INFO_STRU;
/****************************************************************
 * WUEPS系统中线程和消息队列管理结构体
 *
 ***************************************************************/
typedef struct
{
    THREAD_ID       pThreadId;                                                  /* 线程                                     */
    MSGQUE_ID       MsgQueueId;                                                 /* 消息队列                                 */
    VOS_CHAR*           pStackStartAddr;                                            /* 增加线程堆栈的起始地址                   */
    VOS_CHAR*           pQueueStartAddr;                                            /* 增加消息队列的起始地址                   */
}THREAD_INFO_STRU;

/****************************************************************
 * 系统资源管理表定义
 *
 ***************************************************************/
extern THREAD_INFO_STRU                 WuepsThreadInfo[WUEPS_MAX_THREAD];      /* WUEPS系统所有的线程信息                  */
extern const WUEPS_THREAD_INFO_STRU     taskDefTbl[WUEPS_MAX_THREAD];           /* WUEPS系统需要创建的线程常数表            */
extern const WUEPS_MSG_QUEUE_INFO_STRU  QueDefTbl[WUEPS_MSG_QUEUE_CNT];         /* WUEPS系统需要创建的消息队列常数表        */



/****************************************************************
 * 各个线程使用的消息队列大小的宏定义
 *
 ***************************************************************/
#define ADMIN_MSG_CNT       10
#define AGENT_MSG_CNT       10
#define WRR_MSG_CNT         20
#define WCOM_MSG_CNT        10
#define RESERVE1_MSG_CNT    1
#define RESERVE2_MSG_CNT    1

#if 0
#define RRCF_MSG_CNT        20
#define RMF_MSG_CNT         10
#define RSRF_MSG_CNT        30
#define RCSF_MSG_CNT        10
#endif

#define PDCP_MSG_CNT        10
#define RLC_MSG_CNT         10
#define MAC_MSG_CNT         30
#define L1C_MSG_CNT         10
#define RABM_MSG_CNT        10
#define MM_MSG_CNT          10
#define MMC_MSG_CNT         10
#define GMM_MSG_CNT         10
#define CC_MSG_CNT          10
#define MN_MSG_CNT          10
#define SM_MSG_CNT          10
#define APP_MSG_CNT         10
#define SMS_MSG_CNT         10
#define SS_MSG_CNT          10
#define TC_MSG_CNT          5
#define SMT_MSG_CNT         10
#define USIM_MSG_CNT        10

/****************************************************************
 * WUEPS系统中每个线程优先级定义
 *
 ***************************************************************/
#define THREAD_PRI_ADMIN    VOS_PRIORITY_BASE
#define THREAD_PRI_AGENT    VOS_PRIORITY_M3
#define THREAD_PRI_WRR      VOS_PRIORITY_BASE
#define THREAD_PRI_WCOM     VOS_PRIORITY_BASE
#define THREAD_PRI_RESERVE  VOS_PRIORITY_BASE

#if 0
#define THREAD_PRI_RRCF     VOS_PRIORITY_BASE
#define THREAD_PRI_RMF      VOS_PRIORITY_BASE
#define THREAD_PRI_RCSF     VOS_PRIORITY_BASE
#define THREAD_PRI_RSRF     VOS_PRIORITY_BASE
#endif

#define THREAD_PRI_PDCP     VOS_PRIORITY_P1
#define THREAD_PRI_RLC      VOS_PRIORITY_P3
#define THREAD_PRI_MAC      VOS_PRIORITY_P3
#define THREAD_PRI_HPA_DN   VOS_PRIORITY_P3
#define THREAD_PRI_RABM     VOS_PRIORITY_BASE
#define THREAD_PRI_MM       VOS_PRIORITY_M1
#define THREAD_PRI_GMM      VOS_PRIORITY_M1
#define THREAD_PRI_MMC      VOS_PRIORITY_M1
#define THREAD_PRI_MN       VOS_PRIORITY_M2
#define THREAD_PRI_CC       VOS_PRIORITY_M2
#define THREAD_PRI_SM       VOS_PRIORITY_M2
#define THREAD_PRI_APP      VOS_PRIORITY_M2
#define THREAD_PRI_SMS      VOS_PRIORITY_M2
#define THREAD_PRI_SS       VOS_PRIORITY_M2
#define THREAD_PRI_TC       VOS_PRIORITY_M2
#define THREAD_PRI_SMT      VOS_PRIORITY_M2
#define THREAD_PRI_USIM     VOS_PRIORITY_BASE

#define VOS_MSG_HEADER_EXT_IF   VOS_UINT32 ulSenderCpuId;  \
                                VOS_UINT32 ulSenderPid;    \
                                VOS_UINT32 ulReceiverCpuId;\
                                VOS_UINT32 ulReceiverPid;  \
                                VOS_UINT32 ulLength;       \
                                VOS_UINT32      ulMsgName;

    #define VOS_MSG_HEADER_IT   VOS_MSG_HEADER

#if 0
#define PHY_VERSION_INFO_ADDR   0x900007e0 /* 物理层版本信息的内存地址 */
#define SOC_VERSION_INFO_ADDR   0x101e0e00 /* 芯片版本信息的内存地址 */
#endif
#define PS_READ                         0
#define PS_WRITE                        1
#define PS_DEFALUT_LEN                  0
#define PS_PHY_VERSION_INFO             0
#define PS_SOC_VERSION_INFO             1
#define PS_MEDIA_VERSION_INFO           2
#define PS_APP_VERSION_INFO             3
#define PS_VERSION_INFO                 4
#define PS_DR_VERSION_INFO              5
#define PS_RF_VERSION_INFO              6

/*extern VOS_UCHAR   g_PsVersionInfo[32];   协议栈版本信息 */

/********************************************************************
*  函数原型的定义
*********************************************************************/
extern VOS_VOID PsThreadStartNotify(VOS_VOID);
/* 底软提供的打印输出函数 */
/********************************************************************
*   id:task ID号；
*   fmt:同printf函数的打印格式。
*********************************************************************/
#ifdef PS_OM_DUMP_SWITCH
/*extern VOS_VOID Dumpbuffer (VOS_UINT32 id, VOS_CHAR* fmt, ...); *//* Dprint函数实现实体 */
extern VOS_VOID dump (VOS_INT32 id);  /* dump单个block数据 */
extern VOS_VOID dumpAll (VOS_VOID); /* dump所以block数据 */
extern VOS_VOID DprintInit(VOS_VOID);  /* 用于清Dprint的各block buffer */
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
