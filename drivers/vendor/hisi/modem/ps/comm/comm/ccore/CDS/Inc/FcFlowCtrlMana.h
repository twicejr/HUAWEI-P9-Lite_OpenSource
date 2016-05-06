/******************************************************************************

                  版权所有 (C), 2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : FcFlowCtrlMana.h
  版 本 号   : 初稿
  作    者   : w00145177
  生成日期   : 2011年12月23日
  最近修改   :
  功能描述   : C核流控管理模块头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月23日
    作    者   : w00145177
    修改内容   : 创建文件

******************************************************************************/

#ifndef __FC_FLOWCTRL_MANA_H__
#define __FC_FLOWCTRL_MANA_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define QOS_FC_ENABLED_MASK                     0x01
#define QOS_FC_HIGHEST_FC_ENABLED_MASK          0x02
#define FC_CDS_DL_ENABLED_MASK                  0x04
#define QOS_FC_HIGHEST_NOTDISCARD_ENABLED_MASK  0x08

#define EN_NV_ITEM_CDS_FC_CONFIG            9042

#define FC_UL_DOWNGRADE_GAP                 100
#define FC_UL_ENTRY_THROUGHPUT_INIT         1875000    /* 150Mbps */

#define FC_UL_THROUGHPUT_THRES_CNT          13          /* FC_UL_THROUGHPUT_THRES_CNT_NV+1 */

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 枚举定义
*****************************************************************************/


/*****************************************************************************
   5 STRUCT定义
*****************************************************************************/
/*****************************************************************************
 结构名    : FC_LTE_CPU_CONTROL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 定义LTE CPU流控控制结构
*****************************************************************************/
typedef struct FC_LTE_CPU_CONTROL
{
    VOS_UINT32          ulFirstDelay;           /* 延迟进入流控状态，连续几个周期高于阈值才进行流控 */
    VOS_UINT32          ulUlDownRate;           /* 上行降速步长百分比 */
    VOS_UINT32          ulUlUpRate;             /* 上行升速步长百分比 */
    VOS_UINT32          ulUlMinBsr;             /* 上行降速下限 Bsr */
    VOS_UINT32          ulHqDownRate;           /* HARQ降速步长百分比 */
    VOS_UINT32          ulHqUpRate;             /* HARQ升速步长百分比 */
    VOS_UINT32          ulHqMaxDiscardRate;     /* HARQ丢包上限 */
    VOS_UINT32          ulDowngradeThres;       /* 降速阈值，CPU占用率高于该值时，MAC降低上行发送速率 */
    VOS_UINT32          ulUpgradeThres;         /* 升速阈值，CPU占用率低于该值时，MAC升高上行发送速率 */
} FC_LTE_CPU_CONTROL_STRU;

/*****************************************************************************
 结构名    : FC_LTE_TEMPERATURE_CONTROL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 定义LTE 温控控制结构
*****************************************************************************/
typedef struct FC_LTE_TEMPERATURE_CONTROL
{
    VOS_UINT8           ucInitialPos;           /* 降速开始位置0~11, 默认4 */
    VOS_UINT8           ucAvailCnt;
    VOS_UINT8           ucBsrThresCnt;          /* 入口控制的起始位置 */
    VOS_UINT8           ucCurrPos;
    VOS_UINT32          ulTemperSteps[FC_UL_THROUGHPUT_THRES_CNT];      /* 温控速率档位kbps -> BSR */
    VOS_UINT32          ulBsrTimerLen;          /* BSR上报周期 */
} FC_LTE_TEMPERATURE_CONTROL_STRU;

/*****************************************************************************
 结构名    : FC_CDS_DL_CONTROL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 定义CDS下行丢包流控控制结构
*****************************************************************************/
typedef struct FC_CDS_DL_CONTROL
{
    VOS_BOOL            bDlCdsFcEnable;         /* CDS下行流控是否使能 */
    VOS_UINT32          ulDiscardThres;         /* CDS下行队列丢包门限 */
    VOS_UINT32          ulDiscardRate;          /* 丢包率 */
} FC_CDS_DL_CONTROL_STRU;


/*****************************************************************************
 结构名    : FC_CL_STATS_INFO
 协议表格  :
 ASN.1描述 :
 结构说明  : C核LTE流控统计量
*****************************************************************************/
typedef struct FC_CL_STATS_INFO
{
    VOS_UINT32              ulToLteNum;                 /* 切为LTE模次数 */
    VOS_UINT32              ulToGUNum;                  /* 切为GU模次数 */
    VOS_UINT32              ulToNullNum;                /* 进入NULL处理次数 */
    VOS_UINT32              ulToLBNum;                  /* 进入LOOPBACK处理次数 */
    VOS_UINT32              ulTemperatureDownNum;       /* 温控降速次数 */
    VOS_UINT32              ulTemperatureUpNum;         /* 温控升速次数 */
    VOS_UINT32              ulTemperatureRecoverNum;    /* 温控直接恢复次数 */
    VOS_UINT32              ulTemperatureToLimitNum;    /* 温控降速到下限次数 */
    VOS_UINT32              ulTemperatureToNormalNum;   /* 温控恢复到正常次数 */
    VOS_UINT32              ulCpuDownNum;               /* CPU过载降速次数 */
    VOS_UINT32              ulCpuUpNum;                 /* CPU恢复升速次数 */
    VOS_UINT32              ulCpuToDownNum;             /* CPU进入降速状态数 */
    VOS_UINT32              ulCpuToNormalNum;           /* CPU恢复到正常次数 */
    VOS_UINT32              ulHqDownNum;                /* HARQ过载降速次数 */
    VOS_UINT32              ulHqUpNum;                  /* HARQ恢复升速次数 */
    VOS_UINT32              ulHqToDownNum;              /* HARQ进入降速状态数 */
    VOS_UINT32              ulHqToNormalNum;            /* HARQ恢复到正常次数 */
    VOS_UINT32              ulBelowMinBsr;              /* 上报缓存低于下限 */
}FC_CL_STATS_INFO_STRU;


/*****************************************************************************
  6 UNION定义
*****************************************************************************/


/*****************************************************************************
  7 全局变量声明
*****************************************************************************/
extern FC_CL_STATS_INFO_STRU    g_stFcCLStats;

/* C核LTE流控统计 */
#define  FC_CL_TO_LTE_STAT(n)               (g_stFcCLStats.ulToLteNum += (n))
#define  FC_CL_TO_GU_STAT(n)                (g_stFcCLStats.ulToGUNum += (n))
#define  FC_CL_TO_NULL_STAT(n)              (g_stFcCLStats.ulToNullNum += (n))
#define  FC_CL_TO_LB_STAT(n)                (g_stFcCLStats.ulToLBNum += (n))

#define  FC_CL_TEMPERATURE_DOWN_STAT(n)     (g_stFcCLStats.ulTemperatureDownNum += (n))
#define  FC_CL_TEMPERATURE_UP_STAT(n)       (g_stFcCLStats.ulTemperatureUpNum += (n))
#define  FC_CL_TEMPERATURE_RECOVER_STAT(n)  (g_stFcCLStats.ulTemperatureRecoverNum += (n))
#define  FC_CL_TEMPERATURE_TO_LIMIT_STAT(n) (g_stFcCLStats.ulTemperatureToLimitNum += (n))
#define  FC_CL_TEMPERATURE_TO_NORMAL_STAT(n)     (g_stFcCLStats.ulTemperatureToNormalNum += (n))

#define  FC_CL_CPU_DOWN_STAT(n)             (g_stFcCLStats.ulCpuDownNum += (n))
#define  FC_CL_CPU_UP_STAT(n)               (g_stFcCLStats.ulCpuUpNum += (n))
#define  FC_CL_CPU_TO_DOWN_STAT(n)          (g_stFcCLStats.ulCpuToDownNum += (n))
#define  FC_CL_CPU_TO_NORMAL_STAT(n)        (g_stFcCLStats.ulCpuToNormalNum += (n))
#define  FC_CL_HQ_DOWN_STAT(n)             (g_stFcCLStats.ulHqDownNum += (n))
#define  FC_CL_HQ_UP_STAT(n)               (g_stFcCLStats.ulHqUpNum += (n))
#define  FC_CL_HQ_TO_DOWN_STAT(n)          (g_stFcCLStats.ulHqToDownNum += (n))
#define  FC_CL_HQ_TO_NORMAL_STAT(n)        (g_stFcCLStats.ulHqToNormalNum += (n))
#define  FC_CL_BSR_BELOW_MIN_STAT(n)        (g_stFcCLStats.ulBelowMinBsr += (n))

/*****************************************************************************
  8 函数声明
*****************************************************************************/
extern VOS_VOID Fc_SwitchToGu(VOS_VOID);
extern VOS_VOID Fc_SwitchToLte(VOS_VOID);
extern VOS_VOID Fc_SwitchToNull(VOS_VOID);
extern VOS_UINT32 Fc_BufferReportDiscount( VOS_UINT32 ulBufferSize );
extern VOS_VOID LUP_RelDataReq(VOS_VOID);



/*****************************************************************************
  9 OTHERS定义
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

#endif

