/******************************************************************************

                  版权所有 (C), 2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_SRV_HbDetector.h
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2015年05月16日
  最近修改   :
  功能描述   : 心跳周期探测器
  函数列表   :
  修改历史   :
  1.日    期   : 2015年05月16日
    作    者   : d00173029
    修改内容   : 建立文件

******************************************************************************/

#ifndef __BST_SRV_HB_DETECTOR_H__
#define __BST_SRV_HB_DETECTOR_H__
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_SRV_Define.h"
#include "BST_OS_Timer.h"
#include "BST_CORE_Schd.h"
#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define BST_SRV_DTC_MAX_LEN             ( 3U )
#define BST_SRV_DTC_SYS_DLY             ( 500U )        /* 从无数据，到下发Start，AP为500mS */
#define BST_SRV_DTC_BAS_UNT             ( 300000U )     /* 基础周期单位：5分钟（300秒）*/
#define BST_SRV_DTC_GAD_OFS             ( 10000U )      /* 保护间隔，10秒*/
#define BST_SRV_DTC_UNT_REW             ( 60000U )      /* 单位回退时间，60秒*/
#define BST_SRV_DTC_MAX_REW             ( 120000U )     /* 最大允许回退间隔，120秒*/
#define BST_SRV_DTC_ONE_HUR             ( 3600000 )     /* 1小时所含ms数 */
#define BST_SRV_DTC_THR_HUR             ( 10800000 )    /* 3小时所含ms数 */
#define BST_SRV_DTC_SIX_HUR             ( 21600000 )    /* 6小时所含ms数 */
#define BST_SRV_DTC_INI_PNT             ( 2U )          /* 周期探测起始点*/
#define BST_SRV_DTC_MIN_PNT             ( 1U )          /* 最小周期点*/

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 枚举定义
*****************************************************************************/

enum BST_SRV_DET_STATE{
    BST_SRV_DET_STATE_INIT,
    BST_SRV_DET_STATE_FORWARD,
    BST_SRV_DET_STATE_REVERSE,
    BST_SRV_DET_STATE_FINISH,
    BST_SRV_DET_STATE_BUTT
};
typedef BST_UINT8   BST_SRV_DET_STATE_ENUM_UINT8;

/*****************************************************************************
  5 类/结构定义
*****************************************************************************/

class BST_SRV_CHbDetector
    : BST_OS_CTimerCb
{
BST_PUBLIC:
    static  BST_SRV_CHbDetector*    GetInstance     ( BST_VOID );
    BST_ERR_ENUM_UINT8              DefTask         ( BST_CORE_PTASK_NODE_STRU *pDetTask );
    BST_ERR_ENUM_UINT8              ClrTask         ( BST_VOID );
    BST_VOID                        AckSendResult   ( BST_UINT16 ucResult );
    BST_VOID                        ReStart         ( BST_VOID );
    BST_VOID                        Resume          ( BST_VOID );
    BST_VOID                        Pause           ( BST_VOID );
    BST_UINT32                      GetCurrentTick  ( BST_VOID );
    BST_VOID                        onBlock         ( BST_VOID );
    BST_VOID                        onUnBlock       ( BST_VOID );
    BST_BOOL                        IsTask          ( BST_CORE_CPTask *pcTask );
    BST_BOOL                        IsRuning        ( BST_VOID );
    BST_UINT16                      GetConfCyc      ( BST_UINT16 usInAppCyc );
BST_PRIVATE:
                                    BST_SRV_CHbDetector( BST_VOID );
    virtual                        ~BST_SRV_CHbDetector( BST_VOID );
    BST_VOID                        Initial         ( BST_VOID );
    BST_VOID                        Finish          ( BST_VOID );
    BST_VOID                        ProcHbSuc       ( BST_VOID );
    BST_VOID                        ProcHbErr       ( BST_VOID );
    BST_VOID                        RunTimer        ( BST_VOID );
    BST_ERR_ENUM_UINT8              UpdateConfCyc   ( BST_UINT8 ucPoint );
    BST_VOID                        TimerExpired    (
                                        BST_OS_TIMERID_T    ulId,
                                        BST_VOID           *pvPara );
    BST_OS_TIMERID_T                m_ulDetectingTmr;                           /*探测专用定时器*/
    BST_UINT32                      m_ulDetectingOfset;                         /*每次探测的偏移量*/
    BST_UINT32                      m_ulCfmSysTick_Ms;                          /*探测后，每次任务唤醒TICK值（5分钟左右）*/
    BST_UINT8                       m_ucDetectingCycle;                         /*目前正在探测的周期点值（1~3）*/
    BST_SRV_DET_STATE_ENUM_UINT8    m_enDtcState;                               /*运行状态*/
    BST_UINT8                       m_ucCfmTable[ BST_SRV_DTC_MAX_LEN + 1 ];    /*应用要求时长与探明时长映射表，例如最大10分钟，那么ucCfmTable[3]=2*/
    BST_BOOL                        m_bIsBlocked;                               /*当前是否处于Block状态*/
    BST_CORE_PTASK_NODE_STRU       *pcTaskItem;                                 /*探测器任务对象（华为PUSH）*/
};
/*****************************************************************************
  6 UNION定义
*****************************************************************************/

/*****************************************************************************
  7 全局变量声明
*****************************************************************************/

/*****************************************************************************
  8 函数声明
*****************************************************************************/

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif



#endif


