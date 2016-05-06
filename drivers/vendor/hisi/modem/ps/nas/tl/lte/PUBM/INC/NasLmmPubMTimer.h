/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasLmmPubMTimer.h
  Description     : NasLmmPubMTimer.c header file
  History         :
     1.lining 00141619       2008-10-25     Draft Enact
     2.zhuyiqiang 00138739   2009-05-14     Modify BJ9D00720
     3.zhengjunyan 00148421  2011-05-28     文件名由 NasMmPubMTimer.h修改为
                                            NasLmmPubMTimer.h
******************************************************************************/

#ifndef __NASLMMPUBMTIMER_H__
#define __NASLMMPUBMTIMER_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "NasLmmPubMOsa.h"
#include  "NasLmmPubMFsm.h"
#include  "NasEmmPubUGlobal.h"
#include  "NasLmmPublic.h"


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/

/*状态定时器*/
#define NAS_LMM_TIMER_ATTACH_WAIT_ESM_PDN_RSP_LEN    10000 /*ATTACH等待ESM承载建立请求:10s*/
#define NAS_LMM_TIMER_ATTACH_WAIT_ESM_BEARER_CNF_LEN 10000 /*ATTACH等待ESM承载激活结果:10s*/
#define NAS_LMM_TIMER_PLMN_WAIT_MMC_START_CNF_LEN    5000  /*PLMN等待MMC启动结果:5s*/
#define NAS_LMM_TIMER_PLMN_WAIT_MMC_STOP_CNF_LEN     5000  /*PLMN等待MMC停止结果:5s*/
#define NAS_LMM_TIMER_PLMN_WAIT_RRC_START_CNF_LEN    5000  /*PLMN等待RRC启动结果:5s*/
#define NAS_LMM_TIMER_MMC_USER_RES_PROTECT           10000 /*手动模式下，MMC等待用户选择PLMN:10s*/
#define NAS_LMM_TIMER_MMC_DEFAULT_HPLMN_SRCH_PRIOD_LEN   3600000/* MMC VPLMN下，定期进行HPLMN搜索的默认周期*/
/*#define NAS_LMM_TIMER_MMC_INITIAL_HPLMN_SRCH_PRIOD_LEN   120000  MMC VPLMN下，定期进行HPLMN搜索的初始周期*/
#define NAS_LMM_TIMER_EMM_DEL_FORB_TA_PRIOD_LEN      (12*60*60*1000)/*MMC删除 ForbTA的周期*/
#define NAS_LMM_TIMER_WAIT_USIM_READY_START_LEN      5000 /*等待USIM卡初始化*/
#define NAS_LMM_TIMER_DETACH_SWITCH_OFF_LEN          5000 /*尝试发送关机detach的等待定时器:5s*/

#define NAS_LMM_TIMER_REATTACH_DELAY_LEN             800       /*收到Rej #9、#10、#40被拒后重新发起attach的延时定时器 */

#define NAS_LMM_TIMER_CSFB_DELAY_LEN                 3000  /* NORMAL态下释放过程中收到MM的CSFB的延时定时器: 2s */

#ifndef PS_ITT_PC_TEST
#define NAS_LMM_TIMER_T3440_LEN                      10000 /*T3440:10s*/
#define NAS_LMM_TIMER_PUB_WAIT_MRRC_REL_CNF_LEN      5000  /*各模块等待内部连接释放:5s*/
#define NAS_LMM_TIMER_DETACH_T3421_LEN               15000 /*DETACH等待网侧响应:15S*/
#define NAS_LMM_TIMER_TAU_T3430                      15000 /*TAU等待网侧响应:15s*/
#define NAS_LMM_TIMER_AUTH_T3418_LEN                 20000 /*AUTH MAC FAIL等待网侧响应:20s*/
#define NAS_LMM_TIMER_AUTH_T3420_LEN                 15000 /*AUTH SYN FAIL等待网侧响应:15s*/
#define NAS_LMM_TIMER_MMC_WAIT_AS_RESULT_LEN         (60000*5) /*MMC等待搜网结果:5min*/
#define NAS_LMM_TIMER_MMC_WAIT_PLMN_LIST_LEN         (60000*5) /*MMC等待PLMN LIST搜索结果:5min*/
#define NAS_LMM_TIMER_MRRC_WAIT_RRC_CONN_CNF_LEN     5000  /*MRRC等待连接建立:5s*/
#define NAS_LMM_TIMER_MRRC_WAIT_RRC_REL_CNF_LEN      5000  /*MRRC等待连接释放:5s*/
#define NAS_LMM_TIMER_ATTACH_T3410_LEN               15000 /*ATTACH等待网侧响应:15s*/
#define NAS_LMM_TIMER_T3411_LEN                      10000 /*ATTACH&TAU T3411:10S*/
#define NAS_LMM_TIMER_SER_T3417_LEN                  5000  /*SER等待网侧响应:5s*/
#define NAS_LMM_TIMER_SER_T3417_EXT_LEN              10000  /*SER等待网侧响应:10s*/
#define NAS_LMM_TIMER_PLMN_WAIT_RRC_STOP_CNF_LEN     5000  /*PLMN等待RRC停止结果:5s*/
#define NAS_LMM_TIMER_MMC_AVAILABLE_PLMN_SRCH_LEN    180000/*MMC定期搜索AVAILABLE小区:3min*/
#define NAS_LMM_TIMER_MMC_INITIAL_HPLMN_SRCH_PRIOD_LEN   120000
#define NAS_LMM_TIMER_WAIT_USIM_CNF_LEN              30000 /*等待USIM卡响应定时器:30s*/
#define NAS_LMM_TIMER_WAIT_RRC_DATA_CNF_LEN          6000 /*等待RRC对直传消息确认的定时器:6s*/
#define NAS_LMM_TIMER_MMC_SUIT_CELL_SRCH_LEN         120000 /*MMC搜索suit小区:2min*/
#define NAS_LMM_TIMER_SUSPEND_RESUME_WAIT_LEN        5000 /*等待MMC,ESM,ERABM挂起的定时器时长:5s*/
#define NAS_LMM_TIMER_SUSPEND_WAIT_END_LEN           200000 /*等待MMC GU RESUME NOTIFY的定时器时长:200s*/
#define NAS_LMM_TIMER_WAIT_SYS_INFO_IND_LEN          20000  /*等待系统消息的时长:20s*/

#define NAS_LMM_TIMER_SYSCFG_CNF_WAIT_LEN            8000 /*等待SYSCFG_CNF的定时器时长:8s*/
#define NAS_LMM_TIMER_PLMN_SRCH_CNF_WAIT_LEN         100000 /*等待PLMN_SRCH_CNF的定时器时长:100s*/

#define NAS_LMM_TIMER_T3346_LEN                      15000 /*T3346默认时长:15s*/
#else
    #ifdef PS_ITT_PC_TEST_NAS
    #define NAS_LMM_TIMER_T3440_LEN                      5000 /*T3440:10s*/
    #define NAS_LMM_TIMER_PUB_WAIT_MRRC_REL_CNF_LEN      3000  /*各模块等待内部连接释放:5s*/
    #define NAS_LMM_TIMER_DETACH_T3421_LEN               4000 /*DETACH等待网侧响应:15S*/
    #define NAS_LMM_TIMER_TAU_T3430                      5000 /*TAU等待网侧响应:15s*/
    #define NAS_LMM_TIMER_AUTH_T3418_LEN                 5000 /*AUTH MAC FAIL等待网侧响应:20s*/
    #define NAS_LMM_TIMER_AUTH_T3420_LEN                 5000 /*AUTH SYN FAIL等待网侧响应:15s*/
    #define NAS_LMM_TIMER_MMC_WAIT_AS_RESULT_LEN         5000 /*MMC等待搜网结果:1min*/
    #define NAS_LMM_TIMER_MMC_WAIT_PLMN_LIST_LEN         5000 /*MMC等待PLMN LIST搜索结果:1min*/
    #define NAS_LMM_TIMER_MRRC_WAIT_RRC_CONN_CNF_LEN     20000  /*MRRC等待连接建立:4s*/
    #define NAS_LMM_TIMER_MRRC_WAIT_RRC_REL_CNF_LEN      5000  /*MRRC等待连接释放:5s*/
    #define NAS_LMM_TIMER_ATTACH_T3410_LEN               7000 /*ATTACH等待网侧响应:15s*/
    #define NAS_LMM_TIMER_T3411_LEN                      7000 /*ATTACH&TAU T3411:7S*/
    #define NAS_LMM_TIMER_SER_T3417_LEN                  15000  /*SER等待网侧响应:15s*/
    #define NAS_LMM_TIMER_SER_T3417_EXT_LEN              15000  /*SER等待网侧响应:15s*/
    #define NAS_LMM_TIMER_PLMN_WAIT_RRC_STOP_CNF_LEN     3000  /*PLMN等待RRC停止结果:5s*/
    #define NAS_LMM_TIMER_MMC_AVAILABLE_PLMN_SRCH_LEN    7000 /*MMC定期搜索AVAILABLE小区:7s*/
    #define NAS_LMM_TIMER_MMC_INITIAL_HPLMN_SRCH_PRIOD_LEN   15000
    #define NAS_LMM_TIMER_WAIT_USIM_CNF_LEN              30000 /*等待USIM卡响应定时器:30s*/
    #define NAS_LMM_TIMER_WAIT_RRC_DATA_CNF_LEN          6000 /*等待RRC对直传消息确认的定时器:2s*/
    #define NAS_LMM_TIMER_MMC_SUIT_CELL_SRCH_LEN         7000 /*MMC搜索suit小区:7s*/
    #define NAS_LMM_TIMER_SUSPEND_RESUME_WAIT_LEN        4000 /*等待MMC,ESM,ERABM挂起的定时器时长:5s*/
    #define NAS_LMM_TIMER_WAIT_SYS_INFO_IND_LEN          4000  /*等待系统消息的时长:4s*/
    #define NAS_LMM_TIMER_SYSCFG_CNF_WAIT_LEN            5000 /*等待SYSCFG_CNF的定时器时长:5s*/
    #define NAS_LMM_TIMER_PLMN_SRCH_CNF_WAIT_LEN         10000 /*等待PLMN_SRCH_CNF的定时器时长:10s*/
    #define NAS_LMM_TIMER_SUSPEND_WAIT_END_LEN           200000 /*等待MMC GU RESUME NOTIFY的定时器时长:200s*/

    #define NAS_LMM_TIMER_T3346_LEN                      15000 /*T3346默认时长:15s*/
    #else
    #define NAS_LMM_TIMER_T3440_LEN                      10000 /*T3440:10s*/
    #define NAS_LMM_TIMER_PUB_WAIT_MRRC_REL_CNF_LEN      5000  /*各模块等待内部连接释放:5s*/
    #define NAS_LMM_TIMER_DETACH_T3421_LEN               15000 /*DETACH等待网侧响应:15S*/
    #define NAS_LMM_TIMER_TAU_T3430                      15000 /*TAU等待网侧响应:15s*/
    #define NAS_LMM_TIMER_AUTH_T3418_LEN                 20000 /*AUTH MAC FAIL等待网侧响应:20s*/
    #define NAS_LMM_TIMER_AUTH_T3420_LEN                 15000 /*AUTH SYN FAIL等待网侧响应:15s*/
    #define NAS_LMM_TIMER_MMC_WAIT_AS_RESULT_LEN         (60000*5) /*MMC等待搜网结果:5min*/
    #define NAS_LMM_TIMER_MMC_WAIT_PLMN_LIST_LEN         (60000*5) /*MMC等待PLMN LIST搜索结果:5min*/
    #define NAS_LMM_TIMER_MRRC_WAIT_RRC_CONN_CNF_LEN     50000 /*MRRC等待连接建立:50s*/
    #define NAS_LMM_TIMER_MRRC_WAIT_RRC_REL_CNF_LEN      50000 /*MRRC等待连接释放:50s*/
    #define NAS_LMM_TIMER_ATTACH_T3410_LEN               30000 /*ATTACH等待网侧响应:30s*/
    #define NAS_LMM_TIMER_T3411_LEN                      30000 /*ATTACH&TAU T3411:30S*/
    #define NAS_LMM_TIMER_SER_T3417_LEN                  15000 /*SER等待网侧响应:15s*/
    #define NAS_LMM_TIMER_SER_T3417_EXT_LEN              15000  /*SER等待网侧响应:15s*/
    #define NAS_LMM_TIMER_PLMN_WAIT_RRC_STOP_CNF_LEN     120000 /*PLMN等待RRC停止结果:120s*/
    #define NAS_LMM_TIMER_MMC_AVAILABLE_PLMN_SRCH_LEN    60000 /*MMC定期搜索AVAILABLE小区:60s*/
    #define NAS_LMM_TIMER_MMC_INITIAL_HPLMN_SRCH_PRIOD_LEN   120000
    #define NAS_LMM_TIMER_WAIT_USIM_CNF_LEN              30000 /*等待USIM卡响应定时器:30s*/
    #define NAS_LMM_TIMER_WAIT_RRC_DATA_CNF_LEN          6000 /*等待RRC对直传消息确认的定时器:2s*/
    #define NAS_LMM_TIMER_MMC_SUIT_CELL_SRCH_LEN         60000 /*MMC搜索suit小区:60s*/
    #define NAS_LMM_TIMER_SUSPEND_RESUME_WAIT_LEN        5000 /*等待MMC,ESM,ERABM挂起的定时器时长:5s*/
    #define NAS_LMM_TIMER_WAIT_SYS_INFO_IND_LEN          5000  /*等待系统消息的时长:5s*/
    #define NAS_LMM_TIMER_SYSCFG_CNF_WAIT_LEN            5000 /*等待SYSCFG_CNF的定时器时长:2s*/
    #define NAS_LMM_TIMER_PLMN_SRCH_CNF_WAIT_LEN         10000 /*等待PLMN_SRCH_CNF的定时器时长:10s*/
    #define NAS_LMM_TIMER_SUSPEND_WAIT_END_LEN           200000 /*等待MMC GU RESUME NOTIFY的定时器时长:200s*/
    #endif

#endif

/*协议定时器*/
#ifndef PS_ITT_PC_TEST
#define NAS_LMM_TIMER_T3402_LEN                          720000/*ATTACH&TAU T3402:12min*/
#define NAS_LMM_TIMER_T3412_LEN                          (54*60*1000) /*TAU T3412:54min*/
#define NAS_LMM_TIMER_AUTH_T3416_LEN                     20000 /*AUTH确认鉴权完成T3416:30s*/
#define NAS_LMM_TIMER_T3423_LEN                          (54*60*1000) /*T3423:54min*/

#else
     #ifdef PS_ITT_PC_TEST_NAS
     #define NAS_LMM_TIMER_T3402_LEN                     30000 /*ATTACH&TAU T3402:1min*/
     #define NAS_LMM_TIMER_T3412_LEN                     15000 /*TAU T3412:15s*/
     #define NAS_LMM_TIMER_AUTH_T3416_LEN                 3000 /*AUTH确认鉴权完成T3416:30s*/
     #define NAS_LMM_TIMER_T3423_LEN                     15000 /*T3423: 15s*/

     #else
     #define NAS_LMM_TIMER_T3402_LEN                     60000 /*ATTACH&TAU T3402:1min*/
     #define NAS_LMM_TIMER_T3412_LEN                     (54*60*1000) /*TAU T3412:54min*/
     #define NAS_LMM_TIMER_AUTH_T3416_LEN                30000 /*AUTH确认鉴权完成T3416:30s*/
     #define NAS_LMM_TIMER_T3423_LEN                     (54*60*1000) /*T3412:54min*/
     #endif
#endif
#define NAS_LMM_TIMER_NOT_CARE           (0)
#define NAS_LMM_TIMER_ZERO_VALUE         (0)
#define TI_NAS_LMM_TIMER_MAX_LEN         (18*60*60*1000)     /* 18小时 */

#define NAS_LMM_TIMER_161722Atmpt5CSPS1_TRUE             (1)
#define NAS_LMM_TIMER_161722Atmpt5CSPS1_FALSE            (0)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
    枚举名    : NAS_LMM_TIMER_RUN_STA_ENUM
    枚举说明  : 定时器的状态:正在运行,停止
*****************************************************************************/
enum    NAS_LMM_TIMER_RUN_STA_ENUM
{
    NAS_LMM_TIMER_RUNNING                = 0x00,
    NAS_LMM_TIMER_STOPED,
    NAS_LMM_TIMER_INVALID,

    NAS_LMM_TIMER_BUTT
};
typedef VOS_UINT32   NAS_LMM_TIMER_RUN_STA_ENUM_UINT32;


/*****************************************************************************
 结构名    : NAS_EMM_TIMER_INFO_STRU
 结构说明  : log出EMM定时器运行情况
 1.日    期   : 2012年12月03日
   作    者   : n00181501
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                          stMsgHeader;     /*_H2ASN_Skip*/
    NAS_LMM_TIMER_RUN_STA_ENUM_UINT32        enTimerStatus;   /* 定时器状态*/

    VOS_UINT16                               usTimerId;       /* 定时器ID*/
    VOS_UINT16                               usRsv;
    VOS_UINT32                               ulTimerRemainLen;/* 定时器的时长 */
}NAS_EMM_TIMER_INFO_STRU;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID    NAS_LMM_InitAllPtlTimer( VOS_VOID );
extern VOS_VOID    NAS_LMM_InitAllStateTimer( VOS_VOID );
extern VOS_VOID    NAS_LMM_InitStateTimer(
                    NAS_LMM_STATE_TI_ENUM_UINT16             enStateTimerId,
                    VOS_UINT32                              ulTimerLen );
extern VOS_VOID    NAS_LMM_InitPtlTimer(
                    NAS_LMM_PTL_TI_ENUM_UINT16             enPtlTimerId,
                    VOS_UINT32                            ulTimerLen );

extern VOS_VOID    NAS_LMM_ModifyPtlTimer(
                           NAS_LMM_PTL_TI_ENUM_UINT16               enPtlTimerId,
                           VOS_UINT32                              ulTimerLen );
extern VOS_VOID    NAS_LMM_ModifyStateTimer(
                           NAS_LMM_STATE_TI_ENUM_UINT16             enStateTimerId,
                           VOS_UINT32                              ulTimerLen );
extern VOS_VOID    NAS_LMM_ResumeStateTimer(
                           NAS_LMM_STATE_TI_ENUM_UINT16             enStateTimerId );
extern VOS_VOID    NAS_LMM_StartStateTimer(
                           NAS_LMM_STATE_TI_ENUM_UINT16             enStateTimerId );
extern VOS_VOID    NAS_LMM_StartPtlTimer(
                           NAS_LMM_PTL_TI_ENUM_UINT16               enPtlTimerId );
extern VOS_VOID    NAS_LMM_Start3402Timer(VOS_UINT8 ucIs161722Atmpt5CsPs1);
extern VOS_VOID NAS_LMM_Stop3402Timer(VOS_VOID);
extern VOS_UINT32  NAS_LMM_IsNeedStop3402Timer(VOS_VOID);
extern VOS_VOID    NAS_LMM_StopAllPtlTimer( VOS_VOID );
extern VOS_VOID    NAS_LMM_StopAllStateTimer( VOS_VOID );
extern VOS_VOID    NAS_LMM_StopPtlTimer(
                           NAS_LMM_PTL_TI_ENUM_UINT16               enPtlTimerId );
extern VOS_VOID    NAS_LMM_StopStateTimer(
                           NAS_LMM_STATE_TI_ENUM_UINT16             enStateTimerId );
extern VOS_VOID    NAS_LMM_SuspendStateTimer(
                           NAS_LMM_STATE_TI_ENUM_UINT16             enStateTimerId );
extern VOS_VOID    NAS_LMM_StopAllStateTimerExceptDelForbTaProidTimer(VOS_VOID);
extern VOS_VOID  NAS_LMM_StartInactivePtlTimer( NAS_LMM_PTL_TI_ENUM_UINT16  enPtlTimerId);
extern VOS_VOID  NAS_LMM_StartInactiveStateTimer( NAS_LMM_STATE_TI_ENUM_UINT16 enStateTimerId );
extern VOS_VOID  NAS_LMM_GetStateTimerLen( NAS_LMM_STATE_TI_ENUM_UINT16   enStateTimerId,
                                          VOS_UINT32   *pulTimerLen);
extern VOS_VOID  NAS_LMM_GetPtlTimerLen( NAS_LMM_PTL_TI_ENUM_UINT16   enStateTimerId,
                                          VOS_UINT32   *pulTimerLen);

extern NAS_LMM_TIMER_RUN_STA_ENUM_UINT32  NAS_LMM_IsStaTimerRunning(
                                    NAS_LMM_STATE_TI_ENUM_UINT16 enStateTimerId );
extern NAS_LMM_TIMER_RUN_STA_ENUM_UINT32  NAS_LMM_IsPtlTimerRunning(
                                    NAS_LMM_PTL_TI_ENUM_UINT16 enPtlTimerId );
extern VOS_VOID    NAS_LMM_StopAllEmmPtlTimer( VOS_VOID );
/* 删除不用函数 */
extern VOS_VOID    NAS_LMM_SuspendAllPtlTimerExpT3412( VOS_VOID );
extern VOS_VOID    NAS_LMM_ResumeAllPtlTimer( VOS_VOID );
extern VOS_VOID    NAS_LMM_SuspendAllPtlTimer( VOS_VOID );
extern VOS_VOID    NAS_LMM_StopAllAttachTimer( VOS_VOID );
extern VOS_VOID    NAS_LMM_SuspendInitStopLmmTimer( VOS_VOID );

extern VOS_VOID  NAS_LMM_SndOmEmmTimerStatus(
    NAS_LMM_TIMER_RUN_STA_ENUM_UINT32          enTimerStatus,
    VOS_UINT16                          usTimerId,
    VOS_UINT32                          ulTimerRemainLen
);
extern NAS_LMM_TIMER_CTRL_STRU *NAS_LMM_GetGradualForbidenTimer
(
    VOS_UINT32 ulIndex,
    NAS_LMM_PTL_TI_ENUM_UINT16 enPtlTimerId
);
extern VOS_UINT32  NAS_LMM_IsGradualForbiddenTimerNameValid
(
    VOS_UINT32                          ulIndex,
    NAS_LMM_PTL_TI_ENUM_UINT16          enPtlTimerId
);
extern VOS_UINT32 NAS_LMM_GetGradualForbiddenTimerLen(VOS_UINT32 ulIndex, NAS_LMM_PTL_TI_ENUM_UINT16 enPtlTimerId);
extern VOS_VOID NAS_LMM_StartGradualForbiddenTimer(VOS_UINT32 ulIndex, NAS_LMM_PTL_TI_ENUM_UINT16 enPtlTimerId, VOS_UINT32 ulTimerPara);
extern VOS_VOID  NAS_LMM_StopGradualForbiddenTimer(VOS_UINT32 ulIndex, NAS_LMM_PTL_TI_ENUM_UINT16  enPtlTimerId);
extern NAS_LMM_TIMER_RUN_STA_ENUM_UINT32 NAS_LMM_IsGradualForbiddenTimerRunning(VOS_UINT32 ulIndex,
                                                                        NAS_LMM_PTL_TI_ENUM_UINT16  enPtlTimerId);
/*****************************************************************************
  9 OTHERS
*****************************************************************************/










#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasLmmPubMTimer.h */
