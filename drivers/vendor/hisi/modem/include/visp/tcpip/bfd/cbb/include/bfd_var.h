
/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              bfd_var.h
*
*  Project Code: VISPV100R006
*   Module Name: BFD
*  Date Created: 2006-12-01
*        Author: Wangchengyang
*   Description: BFD需要用到的全局变量声明头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-12-01      Wangchengyang       Create
*
*******************************************************************************/
#ifndef _BFD_VAR_H_
#define _BFD_VAR_H_

#ifdef __cplusplus
extern "C" {
#endif

extern BFD_PPI_HOOK_FUNC        g_pfBfdPpiHook;
extern BFD_HA_CAN_SEND_PACKET   g_pfHaCanSendPacket;
extern BFD_HA_SEND_LIVE_PACKET  g_pfHaSendLivePacket;
extern BFD_HA_GET_DBG_SWITCH    g_pfHaGetDbgSwitch;
extern BFD_HA_CANNOT_CFG        g_pfHaCannotCfg;
extern BFD_HA_DBG_OUTPUT        g_pfBfdHaDbgOutput;
extern BFD_STATE_NOTIFYVRRP     g_pfBfdStateNotifyVRRP;
/*Modified by qinyun62011, DTS2010092600602 BFD去使能时，没有删除对应的静态路由关联表项。 for VISP1.8C01, 2010/9/29 */
extern BFD_STATE_NOTIFYEXT     g_pfBfdStateNotifyExt;


extern ULONG g_ulBfdNpMode;

extern const CHAR g_szBfdVersion[30];

extern CHAR *g_pcBfdCompileTime;


/* Begin:VISP1.7C03 VRF wangchengyang,2009-02-01 */
extern ULONG *g_ulBfdGlobalDebugSwitch;
/* End:VISP1.7C03 VRF wangchengyang,2009-02-01 */

extern ULONG g_ulBfdGlobalCapability;
extern ULONG g_ulBfd6GlobalCapability;

extern ULONG g_ulBfdTaskId;

extern ULONG g_ulBfdOtherQueId;

/*Begin BC3D02903 liangjicheng 2010-04-19 */
extern ULONG g_ulBfdExtQueId;
extern ULONG g_ulBfdExtMsgCount;
extern VOID (* g_pfBfdOSPFRuleUpdateFunc)(BFD_EXT_OSPF_RULE_MSG *pstOSPFRuleMsg);
/*End   BC3D02903 liangjicheng 2010-04-19 */

extern ULONG g_ulBfd6ExtMsgCount;

extern ULONG g_ulBfdNsrQueId;

extern ULONG g_ulBfdTimerQueId;

/* Add for DTS2011021002203, by chenyaoKF34558, at 2011-02-28. 修改原因: 重新设计license功能 */
extern ULONG g_ulBfdLicenseTimerQueId;
extern ULONG g_ulBfd6LicenseTimerQueId;

extern ULONG g_ulBfdLicenseTimerInterval;

extern ULONG g_ulBfdWtrTimeInterval;
extern ULONG g_ulBfd6WtrTimeInterval;

extern ULONG g_ulBfdInitFlag;

extern ULONG g_ulBfdAdaptMultiHopPort;
extern ULONG g_ulBfd6AdaptMultiHopPort;

extern ULONG g_ulBfdBakDbg;

/*Modefy by Q62011 for bfd ext start*/
extern  BFD_NOTIFY_HOOK_S *g_pfBfdNotifyHookFunc;
/*Modefy by Q62011 for bfd ext end*/

/* RPU新需求: BFD状态变迁对外通告 */
extern BFD_STATECHG_NOTIFY_HOOK_FUNC g_pfBfdStateChgNotifyHookFunc;

extern BFD6_NOTIFY_HOOK_S *g_pfBfd6NotifyHookFunc;

extern ULONG g_ulBfdFirsNegoTimes;

extern BFD6_PPI_HOOK_FUNC        g_pfBfd6PpiHook;

/* add for show info */
extern CHAR *g_aszSessionState[]; 

/* add for show info */
extern CHAR *g_aszDetectMode[];

/* 协商失败探测时间 ms */
extern ULONG g_ulBfdNotifyTime;
/*是否使用协商失败探测时间 0 不使用 1 使用*/
extern ULONG g_ulBfdNotifyTimeFlag;


/* Begin:VISP1.7C03 VRF wangchengyang,2009-02-01 */
/* BFD会话全局表项定义 */
extern AVL3_TREE_INFO_S g_BfdTreeInfo;
extern BFD_TREE_SET_S  *g_pstBfdTreeSet;

extern ULONG g_ulBfdVrfSize;
extern ULONG g_ulSGSNPPIBFDDownMode;
extern BFD_NOTIFY_BYVRF_HOOK_S *g_pfBfdNotifyByVrfHookFunc;
/* End:VISP1.7C03 VRF wangchengyang,2009-02-01 */

/* BFD License 钩子函数定义 */
extern BFD_GET_LICENSE_STATE_FUNC g_pfBfdLicenseHook;
extern BFD_GET_LICENSE_STATE_FUNC g_pfBfd6LicenseHook;

/*添加BFD PPI下发可测试性相关变量及宏定义,add by wuhailan,2008-04-11.*/
typedef struct tagBFD_CPUTICK
{
    ULONG  ulLowTick;   
    ULONG  ulHighTick; 
}BFD_CPUTICK_S;

#define BFD_PPI_COUNT 5  /*下发次数*/
typedef struct tagBFD_PPI_TIME
{
    BFD_CPUTICK_S stStartTime[BFD_PPI_COUNT];/*下发记录的开始时间*/
    BFD_CPUTICK_S stEndTime[BFD_PPI_COUNT];  /*下发记录的结束时间*/
    ULONG         ulOprType[BFD_PPI_COUNT];  /*下发的操作类型*/
    ULONG         ulBFDPpiCount;             /*下发次数*/
}BFD_PPI_TIME_S;

extern ULONG g_ulCurrentBFDGRState; 
extern ULONG g_ulBFDPpiTimeSwitch;   /*BFD下发耗时计算开关*/
extern BFD_PPI_TIME_S g_ulBFDPpiTime;/*BFD下发耗时统计处理变量*/

/*BFD下发耗前耗时打点*/
#define MAKE_BFDPPI_STARTDOT(OprType)\
{\
    if (g_ulBFDPpiTimeSwitch)\
    {\
        ULONG ii = g_ulBFDPpiTime.ulBFDPpiCount;\
        ii %= BFD_PPI_COUNT;\
        VOS_GetCpuTick( &(g_ulBFDPpiTime.stStartTime[ii].ulLowTick),  \
                        &(g_ulBFDPpiTime.stStartTime[ii].ulHighTick) );\
        g_ulBFDPpiTime.ulOprType[ii] = OprType;\
    }\
}
/*BFD下发耗返回后时间打点*/
#define MAKE_BFDPPI_ENDDOT()\
{\
    if (g_ulBFDPpiTimeSwitch)\
    {\
        ULONG ii = g_ulBFDPpiTime.ulBFDPpiCount;\
        ii %= BFD_PPI_COUNT;\
        VOS_GetCpuTick( &(g_ulBFDPpiTime.stEndTime[ii].ulLowTick),  \
                        &(g_ulBFDPpiTime.stEndTime[ii].ulHighTick) );\
        g_ulBFDPpiTime.ulBFDPpiCount++;\
    }\
}

/* Add for DTS2011021503236, by baiweiqiang（00177000）, at 2011-02-22. 修改原因: 多跳会话发送报文时的TTL取值 */
extern UCHAR g_ucMultiHopTtl;
/* Add for DTS2011021700157 , by baiweiqiang（00177000）, at 2011-02-22. 修改原因: 支持用户预配置BFD session numuber */
extern ULONG g_ulBFDTotalSession;

/*Added by z00208058/w00207740, BFD会话规格扩展, 2012/5/8 */
extern ULONG g_ulBFDMaxSessionNum;

extern ULONG g_ulBfdPReTranMode; /*Added by luogaowei  PF 增强处理开关， 默认关闭*/
extern ULONG g_ulBfdPFProcPeriod; /*Added by luogaowei  PF 增强处理 定时器周期 */
extern ULONG g_ulBfdPFProcMaxNum; /*Added by luogaowei  PF 增强处理 定时器次数*/

extern ULONG g_ulBfdPFTimerId[BFD_PF_TIMER_NUM];   /*BFD PF 处理定时器个数，不能轻易修改，修改后 需要重新计算BFD 定时器索引值*/

/* Modified by l61496, DTS2013032200589 ,g_ulBfdPFSessionInfo全局变量会导致编译生成的bin文件增大8K, 2013/3/30 */
extern ULONG *g_pulBfdPFSessionInfo;  /*高16位保存vrf 索引，低16位保存BFD 会话id*/

extern ULONG g_ulGateValue;

extern BFD_PPI_HOOK_FUNC        g_pfNsrBfdPpiDownloadHook ;
extern BFD6_PPI_HOOK_FUNC       g_pfNsrBfd6PpiDownloadHook;

/*Added by w00207740, NSR TRUNK,添加与NSR模块配合需要的虚表, 2013/10/9 */
extern struct IIF_COMP_NSR_ComIntFUNVtbl *g_pstNsrBfdFunTable;

/* 收到对端的F 标记报文，清除本端P标记 并下发NP处理控制开关，默认0 -不打开*/
extern ULONG g_ulBfdPollClearSwitch;

/* 是否显示BFD端口的开关， VRP_NO 不显示，VRP_YES - 显示 */
extern ULONG g_ulBfdPortShowSwitch;

/* BFD协议顺从性开关,为后续扩展性考虑，每一bit控制一个协议一致性问题 */
extern ULONG g_ulBfdComplianceSwitch;

#ifdef __cplusplus
}
#endif

#endif

