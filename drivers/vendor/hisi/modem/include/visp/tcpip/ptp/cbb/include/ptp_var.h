
#ifndef _ptp_var_h_
#define _ptp_var_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "ptp_timer.h"

/*全局报文捕获函数指针*/
extern PTP_CAPTURE_PACKET_FUNC g_pfPtpCapturePacketFunc;

extern PTP_GRANT_ACQUIRED_FUNC g_pfPtpGrantAcquired;
extern PTP_GRANT_ACQUIRED_ID_FUNC g_pfPtpGrantAcquiredById;

/* 维测全局指针 */
extern PTP_DBG_OUTPUT_HOOK_FUNC     g_pfDbgOutput;
extern PTP_WARN_OUTPUT_HOOK_FUNC    g_pfWarnOutput;

/*定义OC/BC PTP实体全局变量*/
extern PTP_CLOCK_S* g_pstPtpClock;

/*定义TC PTP实体全局变量*/
extern PTP_TCLOCK_S* g_pstTcPtpClock;

/*定义时钟设备的设备类型全局变量*/
extern PTP_DEV_TYPE_E g_ePtpDevType;

/*定义时钟设备的软件模式*/
extern PTP_SOFT_MODE_E g_ePtpSoftMode;

extern PTP_LOGIC_TIMER_H_S g_stLogicTimerHead ;

extern ULONG g_ulPtpTimerQId;

/*PTP报文队列的ID*/
extern ULONG g_ulPtpPktQId;

/*PTP内部控制和配置消息队列的ID*/
extern ULONG g_ulPtpCtrolQId;

/*PTP任务ID*/
extern ULONG g_ulPtpTaskId ;

/*PTP基定时器ID，VOS定时器,100ms*/
extern ULONG g_ulPtpBaseTimerId ;

/*PTP报文接收的事件ID，外围Shell可根据自身的情况进行适配*/
extern ULONG g_ulPtpPktRcvEventId;

/* 维测开关 */
extern ULONG g_ulPtpGlobalDbgSwitch;

extern ULONG g_ulPtpTestSyncTimerFlag;


/*控制只进行一次初始化*/
extern ULONG g_ulPtpInitFlag;


/*PTP信号量*/
extern ULONG g_ulSemForPTP;

/* keep alive报文时间间隔 */
extern CHAR g_cLogLiveInterval;

/* OVER physical地址 All except peer delay mechanism messages */
extern UCHAR gucPTPMultiMac[MACADDRLEN];

extern UCHAR gucPTPDelayMultiMac[MACADDRLEN];

/*Added by utc 需求 */
extern SHORT g_sCrtUtcOffsetValid;
extern SHORT g_sCrtUtcOffset;


/*qinyun&luogaowei 0地址方案 2011-12-12 start*/
/*qinyun&luogaowei 0地址方案 2011-12-12 end*/

extern DLL_S *g_stPtpvlanList;

/*extern ULONG g_ull3ifindex;*//*qinyun&luogaowei 0地址方案 2011-12-12 */

extern UCHAR g_ucPtpDomainSwitch;

extern UCHAR g_ucPtpConformitySwitch;

extern UCHAR g_ucPtpAlternateMasterFlag;

extern ULONG g_ulPtpMultiSelectMode;  /*5路选源开关,只在Slave侧,目前只针对单播,默认为FALSE,即单路选源*/

extern ULONG g_ulPtpMasterDurationSwitch;

extern USHORT g_usPtpMaxAddrNum;

extern ULONG g_ulDelSlavePeriod;

/*PPI 全局PTP_PPI_HOOK_FUNC 类型的函数指针定义*/
extern PTP_PPI_HOOK_FUNC g_pfPtpPpiHookFunc;

/*添加PTP PPI下发可测试性相关变量及宏定义 2008-12-15.*/
typedef struct tagPTP_CPUTICK
{
    ULONG  ulLowTick;   
    ULONG  ulHighTick; 
}PTP_CPUTICK_S;

#define PTP_PPI_COUNT 4  /*下发次数*/
typedef struct tagPTP_PPI_TIME
{
    PTP_CPUTICK_S stStartTime[PTP_PPI_COUNT];/*下发记录的开始时间*/
    PTP_CPUTICK_S stEndTime[PTP_PPI_COUNT];  /*下发记录的结束时间*/
    ULONG         ulOprType[PTP_PPI_COUNT];  /*下发的操作类型*/
    ULONG         ulPTPPpiCount;             /*下发次数*/
}PTP_PPI_TIME_S;

extern ULONG g_ulPTPPpiTimeSwitch;   /*PTP下发耗时计算开关*/
extern PTP_PPI_TIME_S g_ulPTPPpiTime;/*PTP下发耗时统计处理变量*/

/*PTP下发耗前耗时打点*/
#define MAKE_PTPPPI_STARTDOT(OprType)\
{\
    if (g_ulPTPPpiTimeSwitch)\
    {\
        ULONG ii = g_ulPTPPpiTime.ulPTPPpiCount;\
        ii %= PTP_PPI_COUNT;\
        VOS_GetCpuTick(&(g_ulPTPPpiTime.stStartTime[ii].ulLowTick),  \
                        &(g_ulPTPPpiTime.stStartTime[ii].ulHighTick));\
        g_ulPTPPpiTime.ulOprType[ii] = OprType;\
    }\
}
/*PTP下发耗返回后时间打点*/
#define MAKE_PTPPPI_ENDDOT()\
{\
    if (g_ulPTPPpiTimeSwitch)\
    {\
        ULONG ii = g_ulPTPPpiTime.ulPTPPpiCount;\
        ii %= PTP_PPI_COUNT;\
        VOS_GetCpuTick(&(g_ulPTPPpiTime.stEndTime[ii].ulLowTick),  \
                        &(g_ulPTPPpiTime.stEndTime[ii].ulHighTick));\
        g_ulPTPPpiTime.ulPTPPpiCount++;\
    }\
}

/*单路Sync协商选源下发PPI，使用该宏*/
#define PTP_PPI_NOTIFY(usPtpPortNumber, ulPtpPpiCmd, ulVrfIndex, pstPtpPpiInfo)\
{                                    \
    if(PTP_NO == g_ulPtpMultiSelectMode) \
    {                                \
        PTP_PPI_NOTIFY_COMMON(usPtpPortNumber, ulPtpPpiCmd, ulVrfIndex, pstPtpPpiInfo);\
    }                                \
}

/*5路Sync协商选源下发PPI，使用该宏*/
#define PTP_PPI_NOTIFY5(usPtpPortNumber, ulPtpPpiCmd, ulVrfIndex, pstPtpPpiInfo)\
{                                     \
    if(PTP_YES == g_ulPtpMultiSelectMode) \
    {                                 \
        PTP_PPI_NOTIFY_COMMON(usPtpPortNumber, ulPtpPpiCmd, ulVrfIndex, pstPtpPpiInfo);\
    }                                 \
}

/*该宏不能在外面直接调用，请使用如上两个宏*/
#define PTP_PPI_NOTIFY_COMMON(usPtpPortNumber, ulPtpPpiCmd, ulVrfIndex, pstPtpPpiInfo)\
{                                                                                \
    PTP_ALL_PORT_ADDR_VRF_NODE_S stPtpPpiAddrVrfNode = {0};                    \
    ULONG ulPpiRet = PTP_OK;                                                   \
    ULONG ulDefVrfIndex = 0;                                                   \
    if (NULL != g_pfPtpPpiHookFunc)                                          \
    {                                                                          \
        if (ulDefVrfIndex != (ulVrfIndex))                                     \
        {                                                                      \
            (VOID)PTP_GetPortAddrVrfByVrf(usPtpPortNumber, ulVrfIndex, &stPtpPpiAddrVrfNode);\
            if(0 != stPtpPpiAddrVrfNode.ulNum)                                 \
            {                                                                  \
                (pstPtpPpiInfo)->ulIfIndex = stPtpPpiAddrVrfNode.szPortAddrVrf[0].ulIfIndex;\
            }                                                                  \
            else                                                               \
            {                                                                  \
                VOS_DBGASSERT(BOOL_FALSE);                                     \
            }                                                                  \
        }                                                                      \
        MAKE_PTPPPI_STARTDOT(ulPtpPpiCmd);                                     \
        ulPpiRet = g_pfPtpPpiHookFunc(usPtpPortNumber, ulPtpPpiCmd, pstPtpPpiInfo);\
        MAKE_PTPPPI_ENDDOT();                                                  \
        PTP_PPI_LogMsg(ulPpiRet, usPtpPortNumber, ulPtpPpiCmd, pstPtpPpiInfo); \
    }                                                                          \
}

extern PTP_ADDRINFO_S g_stPtpPacketFilterAddr;

extern ULONG g_ulPtpSeqIdCompatType;

extern ULONG g_ulPtpClassCheckSwitch; /* PTP_NO:校验(默认)  PTP_YES:不校验(PT5000对接用) */

extern UCHAR g_ucBmcSourceMode;
extern ULONG g_ulNegoAndBmcSplitMode;
extern UCHAR g_ucPtpMutexCfgFlag;       /*分离模式和keeplive 接口互斥标记，初始化为0, 仅仅用于互斥调用*/

#ifdef __cplusplus
}
#endif

#endif

