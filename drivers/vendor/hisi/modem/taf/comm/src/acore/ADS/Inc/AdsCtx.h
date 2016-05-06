

#ifndef __ADSCTX_H__
#define __ADSCTX_H__

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsCommonDef.h"
#include "PsLogdef.h"
#include "PsTypeDef.h"
#include "PsLib.h"
#include "AdsInterface.h"
#include "AdsDeviceInterface.h"
#include "CdsAdsInterface.h"
#include "AdsNdInterface.h"
#include "AdsTimerMgmt.h"
#include "AdsLog.h"
#include "mdrv.h"
#include "NVIM_Interface.h"
#include "AdsFcInterface.h"
#include "NasNvInterface.h"
#include "TafNvInterface.h"

#if (VOS_OS_VER == VOS_LINUX)
#include <asm/dma-mapping.h>
#include <linux/wakelock.h>
#if (defined(CONFIG_BALONG_SPE))
#include <linux/spe/spe_interface.h>
#include "mdrv_spe_wport.h"
#endif /* CONFIG_BALONG_SPE */
#else
#include "Linuxstub.h"
#endif /* VOS_OS_VER == VOS_LINUX */


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/

/* ADS实例个数与Modem个数保持一致 */
#define ADS_INSTANCE_MAX_NUM            (MODEM_ID_BUTT)

/* ADS实例索引值 */
#define ADS_INSTANCE_INDEX_0            (0)
#define ADS_INSTANCE_INDEX_1            (1)
#define ADS_INSTANCE_INDEX_2            (2)

/*上下缓存队列的最大值 */
#define ADS_RAB_NUM_MAX                 (11)

/* 当前到网络的定义是5到15, 因此有一个5的偏移量 */
#define ADS_RAB_ID_OFFSET               (5)

/* Rab Id的最小值 */
#define ADS_RAB_ID_MIN                  (5)

/* Rab Id的最大值 */
#define ADS_RAB_ID_MAX                  (15)

/* Rab Id的无效值 */
#define ADS_RAB_ID_INVALID              (0xFF)

/* 为了避免频繁触发IPF中断，需要采用攒包机制，攒包的最大个数 */
#define ADS_UL_SEND_DATA_NUM_THREDHOLD          (g_stAdsCtx.stAdsIpfCtx.ulThredHoldNum)

#define ADS_UL_SET_SEND_DATA_NUM_THREDHOLD(n)   (g_stAdsCtx.stAdsIpfCtx.ulThredHoldNum = (n))

#define ADS_UL_RX_WAKE_LOCK_TMR_LEN     (g_stAdsCtx.stAdsIpfCtx.ulRxWakeLockTmrLen)
#define ADS_DL_TX_WAKE_LOCK_TMR_LEN     (g_stAdsCtx.stAdsIpfCtx.ulTxWakeLockTmrLen)

/* 申请的AD需要偏移14作为IPF RD的目的地址，14为MAC头的长度 */
#define ADS_DL_AD_DATA_PTR_OFFSET       (14)

/* 默认的优先级加权数 */
#define ADS_UL_DEFAULT_PRI_WEIGHTED_NUM (0x01)

#define ADS_GET_CURR_KERNEL_TIME()      (jiffies)
#define ADS_TIME_AFTER_EQ(a, b)         time_after_eq((a), (b))

/* ADS ADQ的个数 */
#define ADS_DL_ADQ_MAX_NUM              (2)

/*启动ADQ空保护定时器的阈值，当可配置AD数量大于该值时则启动保护定时器*/
#define ADS_IPF_DLAD_START_TMR_THRESHOLD (IPF_DLAD0_DESC_SIZE - 6)

/* ADS使用的SPE端口号 */
#define ADS_IPF_SPE_PORT_0              (SPE_PORT_MAX + 128)
#define ADS_IPF_SPE_PORT_1              (SPE_PORT_MAX + 129)

/* AD内存队列大小 */
#define ADS_IPF_AD0_MEM_BLK_NUM         (IPF_DLAD0_DESC_SIZE * 2)
#define ADS_IPF_AD1_MEM_BLK_NUM         (IPF_DLAD1_DESC_SIZE * 3)

/* AD数据包的长度 */
#define ADS_IPF_AD0_MEM_BLK_SIZE        (448)
#define ADS_IPF_AD1_MEM_BLK_SIZE        (1536 + 14)

/* ADS_UL_SendPacket和ADS_DL_RegDlDataCallback的rabid为扩展的rabid，
   高2bit作为MODEM ID，低6bit作为RAB ID。根据扩展的RABID获取MODEM ID */
#define ADS_GET_MODEMID_FROM_EXRABID(i) ((i >> 6) & 0x03)

#define ADS_GET_RABID_FROM_EXRABID(i)   (i & 0x3F)

#define ADS_BUILD_EXRABID(i,j)          (((i << 6) & 0xC0) | (j & 0x3F))

/*******************************任务事件 Begin*******************************/

/* ADS上行任务事件 */
#define ADS_UL_EVENT_BASE               (0x00000000)
#define ADS_UL_EVENT_DATA_PROC          (ADS_UL_EVENT_BASE | 0x0001)

/* ADS下行任务事件 */
#define ADS_DL_EVENT_BASE               (0x00000000)
#define ADS_DL_EVENT_IPF_RD_INT         (ADS_DL_EVENT_BASE | 0x0001)
#define ADS_DL_EVENT_IPF_ADQ_EMPTY_INT  (ADS_DL_EVENT_BASE | 0x0002)

/*******************************任务事件 End*******************************/

/*******************************速率统计 Begin*******************************/
/* 获取流量统计上下文 */
#define ADS_GET_DSFLOW_STATS_CTX_PTR()              (&(g_stAdsCtx.stDsFlowStatsCtx))

/* 设置当前上行速率 */
#define ADS_SET_CURRENT_UL_RATE(n)                  (g_stAdsCtx.stDsFlowStatsCtx.stULDataStats.ulULCurDataRate = (n))

/* 设置当前下行速率 */
#define ADS_SET_CURRENT_DL_RATE(n)                  (g_stAdsCtx.stDsFlowStatsCtx.stDLDataStats.ulDLCurDataRate = (n))

/* 统计上行周期性收到包的个数 */
#define ADS_RECV_UL_PERIOD_PKT_NUM(n)               (g_stAdsCtx.stDsFlowStatsCtx.stULDataStats.ulULPeriodSndBytes += (n))

/* 统计下行周期性收到包的个数 */
#define ADS_RECV_DL_PERIOD_PKT_NUM(n)               (g_stAdsCtx.stDsFlowStatsCtx.stDLDataStats.ulDLPeriodRcvBytes += (n))

/* 获取上行周期性收到包的个数 */
#define ADS_GET_UL_PERIOD_PKT_NUM()                 (g_stAdsCtx.stDsFlowStatsCtx.stULDataStats.ulULPeriodSndBytes)

/* 获取下行周期性收到包的个数 */
#define ADS_GET_DL_PERIOD_PKT_NUM()                 (g_stAdsCtx.stDsFlowStatsCtx.stDLDataStats.ulDLPeriodRcvBytes)

/* 将上行周期性收到包的个数清零 */
#define ADS_CLEAR_UL_PERIOD_PKT_NUM()               (g_stAdsCtx.stDsFlowStatsCtx.stULDataStats.ulULPeriodSndBytes = 0)

/* 将下行周期性收到包的个数清零 */
#define ADS_CLEAR_DL_PERIOD_PKT_NUM()               (g_stAdsCtx.stDsFlowStatsCtx.stDLDataStats.ulDLPeriodRcvBytes = 0)

/*******************************速率统计 End*******************************/


/*******************************上行 Begin*******************************/
/* 获取ADS上行实体地址 */
#define ADS_UL_GET_CTX_PTR(i)                       (&(g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx))

/* 获取上行队列指针 */
#define ADS_UL_GET_QUEUE_LINK_PTR(i, j)             (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[j].pstAdsUlLink)

/* 获取上行队列锁 */
#define ADS_UL_GET_QUEUE_LINK_SPINLOCK(i, j)        (&(g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[j].stSpinLock))

/* 获取ADS上行BD配置参数地址 */
#define ADS_UL_GET_BD_CFG_PARA_PTR(index)           (&(g_stAdsCtx.stAdsIpfCtx.astIpfUlBdCfgParam[index]))

/* 获取ADS上行BD缓存地址 */
#define ADS_UL_GET_BD_BUFF_PTR(index)               (&(g_stAdsCtx.stAdsIpfCtx.astIpfUlBdBuff[index]))

/* 获取ADS上行发送保护定时器时长 */
#define ADS_UL_GET_PROTECT_TIMER_LEN()              (g_stAdsCtx.stAdsIpfCtx.ulProtectTmrLen)

/* 获取数据是否正在发送的标志位 */
#define ADS_UL_GET_SENDING_FLAG()                   (g_stAdsCtx.stAdsIpfCtx.ucSendingFlg)

/* 设置数据是否正在发送的标志位 */
#define ADS_UL_SET_SENDING_FLAG(flg)                (g_stAdsCtx.stAdsIpfCtx.ucSendingFlg = flg)

/* 获取存储队列的索引 */
#define ADS_UL_GET_PRIO_QUEUE_INDEX(i, j)           (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.aucPrioIndex[j])

/* 获取上行队列调度优先级*/
#define ADS_UL_GET_QUEUE_QCI(i, j)                  (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[ADS_UL_GET_PRIO_QUEUE_INDEX(i, j)].enPrio)

/* 获取上行队列信息 */
#define ADS_UL_GET_QUEUE_LINK_INFO(i, j)            (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[ADS_UL_GET_PRIO_QUEUE_INDEX(i, j)].pstAdsUlLink)

/* 获取IX OR HRPD的上行IPF过滤组标志 */
#define ADS_UL_GET_1X_OR_HRPD_UL_IPF_FLAG(i, j)     (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[ADS_UL_GET_PRIO_QUEUE_INDEX(i, j)].uc1XorHrpdUlIpfFlag)

/* 获取上行队列一个加权数范围内记录的发送个数 */
#define ADS_UL_GET_RECORD_NUM_IN_WEIGHTED(i, j)     (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[ADS_UL_GET_PRIO_QUEUE_INDEX(i, j)].usRecordNum)

/* 设置上行队列一个加权数范围内记录的发送个数 */
#define ADS_UL_SET_RECORD_NUM_IN_WEIGHTED(i, j, n)  (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[ADS_UL_GET_PRIO_QUEUE_INDEX(i, j)].usRecordNum += n)

/* 清除上行队列一个加权数范围内记录的发送个数 */
#define ADS_UL_CLR_RECORD_NUM_IN_WEIGHTED(i, j)     (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[ADS_UL_GET_PRIO_QUEUE_INDEX(i, j)].usRecordNum = 0)

/* 获取上行队列优先级的加权数 */
#define ADS_UL_GET_QUEUE_PRI_WEIGHTED_NUM(i, j)     (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.stQueuePriNv.ausPriWeightedNum[ADS_UL_GET_QUEUE_QCI(i, j)])

/* 获取上行队列数据包的类型*/
#define ADS_UL_GET_QUEUE_PKT_TYPE(InstanceIndex, RabId) \
            (g_stAdsCtx.astAdsSpecCtx[InstanceIndex].stAdsUlCtx.astAdsUlQueue[RabId].enPktType)


/* 获取ADS上行发送保护定时器时长 */
#define ADS_UL_GET_STAT_TIMER_LEN()     \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdStatInfo.ulStatTmrLen)

#define ADS_UL_ADD_STAT_PKT_NUM(n)      \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdStatInfo.ulStatPktNum += (n))

#define ADS_UL_GET_STAT_PKT_NUM()       \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdStatInfo.ulStatPktNum)

#define ADS_UL_CLR_STAT_PKT_NUM()       \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdStatInfo.ulStatPktNum = 0)

/* 获取上行赞包控制标记 */
#define ADS_UL_GET_THRESHOLD_ACTIVE_FLAG() \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.ulActiveFlag)

/* 获取上行赞包的jiffies的时间计数 */
#define ADS_UL_GET_JIFFIES_TMR_CNT()     (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.ulProtectTmrCnt)

/* 设置上行赞包的jiffies的时间计数 */
#define ADS_UL_SET_JIFFIES_TMR_CNT(n)     (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.ulProtectTmrCnt += (n))

/* 获取上行赞包的jiffies的超时长度 */
#define ADS_UL_GET_JIFFIES_EXP_TMR_LEN() (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.ulProtectTmrExpCnt)

/* 获取上行数据包水线等级 */
#define ADS_UL_GET_WATER_LEVEL_ONE()    \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stWaterMarkLevel.ulWaterLevel1)

#define ADS_UL_GET_WATER_LEVEL_TWO()    \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stWaterMarkLevel.ulWaterLevel2)

#define ADS_UL_GET_WATER_LEVEL_THREE()  \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stWaterMarkLevel.ulWaterLevel3)

#define ADS_UL_GET_WATER_LEVEL_FOUR()   \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stWaterMarkLevel.ulWaterLevel4)

/* 获取上行赞包门限 */
#define ADS_UL_DATA_THRESHOLD_ONE       \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdLevel.ulThreshold1)

#define ADS_UL_DATA_THRESHOLD_TWO       \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdLevel.ulThreshold2)

#define ADS_UL_DATA_THRESHOLD_THREE     \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdLevel.ulThreshold3)

#define ADS_UL_DATA_THRESHOLD_FOUR      \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdLevel.ulThreshold4)


/*******************************上行 End*******************************/

/* 上行IPF内存释放队列首地址 */
#define ADS_UL_IPF_SRCMEM_FREE_QUE()            (&(g_stAdsCtx.stAdsIpfCtx.stUlSrcMemFreeQue))

/* IPF上行源内存释放QUEUE，定义限长为上行IPF BD描述符的2倍 */
#define ADS_UL_IPF_SRCMEM_FREE_QUE_SIZE         (2 * IPF_ULBD_DESC_SIZE)

/* 通过限制ADS上行队列长度，限制A核系统内存，队列限长初始化值 */
#define ADS_UL_MAX_QUEUE_LENGTH                 (500)

/* 获取上行队列限长 */
#define ADS_UL_GET_MAX_QUEUE_LENGTH(i)          (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.ulUlMaxQueueLength)

/* 获取ADS下行IPF AD BUFFER地址 */
#define ADS_DL_GET_IPF_AD_DESC_PTR(i, j)        (&(g_stAdsCtx.stAdsIpfCtx.astIpfDlAdDesc[i][j]))

/*******************************下行 Begin*******************************/

/* 获取ADS下行实体地址 */
#define ADS_DL_GET_CTX_PTR(i)                   (&(g_stAdsCtx.astAdsSpecCtx[i].stAdsDlCtx))

/* 获取ADS下行IPF RD BUFFER地址 */
#define ADS_DL_GET_IPF_RD_DESC_PTR(index)       (&(g_stAdsCtx.stAdsIpfCtx.astIpfDlRdDesc[index]))

/* 获取ADS下行RAB INFO地址 */
#define ADS_DL_GET_RAB_INFO_PTR(i, rabid)       (&(ADS_DL_GET_CTX_PTR(i)->astAdsDlRabInfo[rabid - ADS_RAB_ID_OFFSET]))

/* 获取ADS下行RAB对应的数据包类型 */
#define ADS_DL_GET_PKT_TYPE(instance, rabid)    (ADS_DL_GET_CTX_PTR(instance)->astAdsDlRabInfo[rabid - ADS_RAB_ID_OFFSET].enPktType)

/* 获取ADS下行数据回调函数指针 */
#define ADS_DL_GET_DATA_CALLBACK_FUNC(i,j)      (ADS_DL_GET_RAB_INFO_PTR(i,j)->pRcvDlDataFunc)
#define ADS_DL_GET_DATA_EXPARAM(i,j)            (ADS_DL_GET_RAB_INFO_PTR(i,j)->ulExParam)

/* get/set the last data buff ptr */
#define ADS_DL_GET_LST_DATA_PTR(mid,rabid)          (ADS_DL_GET_RAB_INFO_PTR(mid,rabid)->pstLstPkt)
#define ADS_DL_SET_LST_DATA_PTR(mid,rabid, psPara)  (ADS_DL_GET_RAB_INFO_PTR(mid,rabid)->pstLstPkt = (psPara))

#define ADS_DL_GET_FILTER_DATA_CALLBACK_FUNC(ucInstanceIndex, ucRabId) \
            (ADS_DL_GET_RAB_INFO_PTR(ucInstanceIndex, ucRabId)->pRcvDlFilterDataFunc)

/* 获取ADS下行流控参数信息地址 */
#define ADS_DL_GET_FC_ASSEM_INFO_PTR(i)         (&(ADS_DL_GET_CTX_PTR(i)->stFcAssemInfo))

/* 获取ADS下行流控组包参数调整回调函数指针 */
#define ADS_DL_GET_FC_ASSEM_TUNE_FUNC(i)        (ADS_DL_GET_FC_ASSEM_INFO_PTR(i)->pFcAssemTuneFunc)

/*******************************下行 End*******************************/

/*******************************IPF Begin*******************************/
/* 获取IPF相关的上下文 */
#define ADS_GET_IPF_CTX_PTR()           (&(g_stAdsCtx.stAdsIpfCtx))

#define ADS_GET_IPF_DEV()               (&(g_stAdsCtx.stAdsIpfCtx.stDev))
#define ADS_IMM_MEM_CB(pstImmZc)        ((ADS_IMM_MEM_CB_STRU *)((pstImmZc)->cb))

#if (defined(CONFIG_BALONG_SPE))
#define ADS_GET_IPF_SPE_WPORT()         (g_stAdsCtx.stAdsIpfCtx.lSpeWPort)
#define ADS_GET_IPF_MEM_POOL_CFG_PTR()  (&(g_stAdsCtx.stAdsIpfCtx.stMemPoolCfg))
#define ADS_GET_IPF_MEM_POOL_PTR(id)    (&(g_stAdsCtx.stAdsIpfCtx.astMemPool[id]))
#define ADS_GET_IPF_MEM_QUE(id)         (&(g_stAdsCtx.stAdsIpfCtx.astMemPool[id].stQue))
#define ADS_SPE_MEM_CB(pstImmZc)        ((ADS_SPE_MEM_CB_STRU *)&((pstImmZc)->dma))
#endif

/*lint -emacro({717}, ADS_IPF_SPE_MEM_MAP)*/
#define ADS_IPF_SPE_MEM_MAP(pstImmZc, ulLen)\
            do\
            {\
                if (VOS_TRUE == ADS_IPF_IsSpeMem(pstImmZc))\
                {\
                    ADS_IPF_MemMapByDmaRequset(pstImmZc, ulLen, 0);\
                }\
            } while(0)

/*lint -emacro({717}, ADS_IPF_SPE_MEM_UNMAP)*/
#define ADS_IPF_SPE_MEM_UNMAP(pstImmZc, ulLen)\
            do\
            {\
                if (VOS_TRUE == ADS_IPF_IsSpeMem(pstImmZc))\
                {\
                    ADS_IPF_MemUnmapRequset(pstImmZc, ulLen, 0);\
                }\
            } while(0)


/*******************************IPF End*******************************/

/* 检查MODEMID有效性 */
#define ADS_IS_MODEMID_VALID(usModemId)\
            ((usModemId) < ADS_INSTANCE_MAX_NUM)

/* 检查RABIID有效性 */
#define ADS_IS_RABID_VALID(ucRabId)\
            (((ucRabId) >= ADS_RAB_ID_MIN) && ((ucRabId) <= ADS_RAB_ID_MAX))

#define ADS_UL_IS_REACH_THRESHOLD(ulAllUlQueueDataNum, ucSendingFlg) \
    ((0 != ulAllUlQueueDataNum) && (ulAllUlQueueDataNum >= ADS_UL_SEND_DATA_NUM_THREDHOLD) && (VOS_FALSE == ucSendingFlg))

#if !defined(ADS_ARRAY_SIZE)
#define ADS_ARRAY_SIZE(a)               (sizeof((a)) / sizeof((a[0])))
#endif


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名称  : ADS_IPF_MEM_POOL_ID_ENUM
 枚举说明  : IPF 内存队列
*****************************************************************************/
enum ADS_IPF_MEM_POOL_ID_ENUM
{
    ADS_IPF_MEM_POOL_ID_AD0             = 0,
    ADS_IPF_MEM_POOL_ID_AD1,

    ADS_IPF_MEM_POOL_ID_BUTT
};
typedef VOS_UINT32 ADS_IPF_MEM_POOL_ID_ENUM_UINT32;


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/*****************************************************************************
 结构名称  : ADS_SPE_MEM_CB_STRU
 结构说明  : IPF CB结构
*****************************************************************************/
typedef struct
{
    dma_addr_t                          ulDmaAddr;

} ADS_SPE_MEM_CB_STRU;

/*****************************************************************************
 结构名称  : ADS_IMM_MEM_CB_STRU
 结构说明  : IMM CB结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          aulPriv[2];
    dma_addr_t                          ulDmaAddr;

} ADS_IMM_MEM_CB_STRU;

/*****************************************************************************
 结构名称  : ADS_IPF_BD_BUFF_STRU
 结构说明  : IPF BD Buffer结构
*****************************************************************************/
typedef struct
{
    IMM_ZC_STRU                        *pstPkt;

} ADS_IPF_BD_BUFF_STRU;

/*****************************************************************************
结构名    : ADS_UL_QUEUE_STRU
结构说明  : ADS上行队列管理

  1.日    期   : 2011年12月6日
    作    者   : 鲁琳/l60609
    修改内容   : 定义ADS上行队列管理
  2.日    期   : 2012年02月20日
    作    者   : f00179208
    修改内容   : 修改优先级域的定义
  3.日    期   : 2012年9月12日
    作    者   : l60609
    修改内容   : AP适配项目：增加锁处理
  4.日    期   : 2012年11月27日
    作    者   : l60609
    修改内容   : DSDA Phase II:双实例
  5.日    期   : 2013年05月22日
    作    者   : f00179208
    修改内容   : V3R3 PPP RPOJECT:增加PDP TYPE
*****************************************************************************/
typedef struct
{
    IMM_ZC_HEAD_STRU                   *pstAdsUlLink;                           /* Rab Id对应的队列 */
    VOS_UINT8                           ucIsQueueValid;                         /* 队列是否激活，VOS_TRUE:激活，VOS_FALSE:未激活 */
    ADS_QCI_TYPE_ENUM_UINT8             enPrio;                                 /* 调度优先级 */
    VOS_UINT16                          usRecordNum;                            /* 记录在一个加权数范围内发送数据的个数 */
    VOS_SPINLOCK                        stSpinLock;                             /* 队列锁 */
    ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8     enPktType;                              /* 数据包类型 */
    VOS_UINT8                           uc1XorHrpdUlIpfFlag;                    /* 1X OR HRPD模式下的IPF过滤组 */
    VOS_UINT8                           aucRsv[6];

}ADS_UL_QUEUE_STRU;

/*****************************************************************************
结构名    : ADS_DL_RAB_INFO_STRU
结构说明  : ADS下行RAB信息管理

  1.日    期   : 2011年12月6日
    作    者   : 鲁琳/l60609
    修改内容   : 定义ADS下行RABID信息管理
  2.日    期   : 2013年06月04日
    作    者   : l00198894
    修改内容   : Share-PDP项目增加下行过滤接收函数
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRabId;                                /* Rab Id */
    ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8     enPktType;                              /* 数据包类型 */
    VOS_UINT8                           aucRsv[2];                              /* 保留 */
    VOS_UINT32                          ulExParam;                              /* RMNET数据接收扩展参数 */
    RCV_DL_DATA_FUNC                    pRcvDlDataFunc;                         /* 对应的下行接收函数 */
    RCV_DL_DATA_FUNC                    pRcvDlFilterDataFunc;                   /* 对应的下行过滤接收函数 */
    IMM_ZC_STRU                        *pstLstPkt;

}ADS_DL_RAB_INFO_STRU;

/*****************************************************************************
 结构名   : ADS_DL_FC_ASSEM_STRU
 结构说明 : 流控动态组包参数

 修改历史      :
  1.日    期   : 2012年11月19日
    作    者   : A00165503
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32              ulEnableMask;
    VOS_UINT32              ulFcActiveFlg;
    unsigned long           ulTmrCnt;
    VOS_UINT32              ulRdCnt;
    VOS_UINT32              ulRateUpLev;
    VOS_UINT32              ulRateDownLev;
    VOS_UINT32              ulExpireTmrLen;
    ADS_DRV_ASSEM_FUNC      pFcAssemTuneFunc;

} ADS_DL_FC_ASSEM_STRU;

/*****************************************************************************
结构名    : ADS_DL_CTX_STRU
结构说明  : ADS下行上下文

  1.日    期   : 2011年12月6日
    作    者   : 鲁琳/l60609
    修改内容   : 定义ADS下行上下文

  2.日    期   : 2012年4月12日
    作    者   : A00165503
    修改内容   : DTS2012020708222: ADS性能优化

  3.日    期   : 2012年11月19日
    作    者   : A00165503
    修改内容   : DTS2012112206761: 底软动态组包参数调整

  4.日    期   : 2012年11月23日
    作    者   : L60609
    修改内容   : DSDA Phase II

*****************************************************************************/
typedef struct
{
    ADS_DL_RAB_INFO_STRU                astAdsDlRabInfo[ADS_RAB_NUM_MAX];       /*下行Rab信息 */
    ADS_DL_FC_ASSEM_STRU                stFcAssemInfo;

} ADS_DL_CTX_STRU;

/*****************************************************************************
结构名    : ADS_UL_CTX_STRU
结构说明  : ADS上行上下文

  1.日    期   : 2011年12月6日
    作    者   : 鲁琳/l60609
    修改内容   : 定义ADS上行上下文

  2.日    期   : 2012年02月20日
    作    者   : f00179208
    修改内容   : V7R1C50项目，增加上行队列优先级加权数

  3.日    期   : 2012年4月12日
    作    者   : A00165503
    修改内容   : DTS2012020708222: ADS性能优化

  4.日    期   : 2012年8月31日
    作    者   : l60609
    修改内容   : AP适配项目：增加上行内存释放队列

  5.日    期   : 2012年11月23日
    作    者   : L60609
    修改内容   : DSDA Phase II
*****************************************************************************/
typedef struct
{
    ADS_UL_QUEUE_STRU                   astAdsUlQueue[ADS_RAB_ID_MAX + 1];      /* 上行队列管理，只用5-15 */
    ADS_UL_QUEUE_SCHEDULER_PRI_NV_STRU  stQueuePriNv;                           /* 从NV中读取的上行队列优先级对应的加权数 */
    VOS_UINT8                           aucPrioIndex[ADS_RAB_NUM_MAX];          /* 存储已排好优先级的上行队列的索引 */
    VOS_UINT8                           ucAdsUlCurIndex;                        /* 记录当前调度的队列 */
    VOS_UINT8                           aucRsv[4];
    VOS_UINT32                          ulUlMaxQueueLength;                     /* 上行队列限长 */
    VOS_UINT8                           aucReserved1[4];

}ADS_UL_CTX_STRU;

/*****************************************************************************
 结构名    : ADS_UL_DATA_STATS_STRU
 结构说明  : ADS上行数据统计
   1.日    期   : 2012年1月10日
     作    者   : L60609
     修改内容   : 新建
*****************************************************************************/
typedef struct ADS_UL_DATA_STATS
{
    VOS_UINT32                          ulULCurDataRate;                        /* 当前上行速率，保存PDP激活后2秒的速率，去激活后清空 */
    VOS_UINT32                          ulULPeriodSndBytes;                     /* 一个流量统计周期内发送的byte数 */
}ADS_UL_DATA_STATS_STRU;

/*****************************************************************************
 结构名    : ADS_DL_DATA_STATS_STRU
 结构说明  : ADS下行数据统计
   1.日    期   : 2012年1月10日
     作    者   : L60609
     修改内容   : 新建
*****************************************************************************/
typedef struct ADS_DL_DATA_STATS
{
    VOS_UINT32                          ulDLCurDataRate;                        /* 当前下行速率，保存PDP激活后2秒的速率，去激活后清空 */
    VOS_UINT32                          ulDLPeriodRcvBytes;                     /* 一个流量统计周期内收到的byte数 */
}ADS_DL_DATA_STATS_STRU;

/*****************************************************************************
 结构名    : ADS_STATS_INFO_CTX_STRU
 结构说明  : ADS状态统计
   1.日    期   : 2012年1月10日
     作    者   : L60609
     修改内容   : 新建
*****************************************************************************/
typedef struct
{
    ADS_UL_DATA_STATS_STRU              stULDataStats;                          /* ADS上行数据统计 */
    ADS_DL_DATA_STATS_STRU              stDLDataStats;                          /* ADS下行数据统计 */
}ADS_STATS_INFO_CTX_STRU;

/*****************************************************************************
 结构名    : ADS_UL_THRESHOLD_STAT_STRU
 结构说明  : ADS上行赞包状态统计
   1.日    期   : 2014年06月03日
     作    者   : f00179208
     修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulStatTmrLen;                           /* 统计定时器长度 */
    VOS_UINT32                          ulStatPktNum;                           /* 在单位时间内上行统计包的个数 */
}ADS_UL_THRESHOLD_STAT_STRU;

/*****************************************************************************
 结构名    : ADS_UL_DYNAMIC_ASSEM_INFO_STRU
 结构说明  : ADS上行组包信息
   1.日    期   : 2014年11月08日
     作    者   : f00179208
     修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulActiveFlag;                           /* 使能标识: 0表示去使能,1表示使能 */
    VOS_UINT32                          ulProtectTmrExpCnt;                     /* 保护定时器超时时长 */
    unsigned long                       ulProtectTmrCnt;                        /* 保护定时器的计数 */
    ADS_UL_WATER_MARK_LEVEL_STRU        stWaterMarkLevel;                       /* 动态水线值 */
    ADS_UL_THRESHOLD_LEVEL_STRU         stThresholdLevel;                       /* 动态赞包门限值 */
    ADS_UL_THRESHOLD_STAT_STRU          stThresholdStatInfo;                    /* 赞包状态统计 */
}ADS_UL_DYNAMIC_ASSEM_INFO_STRU;

/*****************************************************************************
 结构名称  : ADS_IPF_MEM_CFG_STRU
 结构说明  : 内存配置信息

  1.日    期   : 2015年10月06日
    作    者   : A00165503
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usBlkNum;
    VOS_UINT16                          usBlkSize;
    VOS_UINT8                           ucPort;
    VOS_UINT8                           aucReserved[3];

} ADS_IPF_MEM_CFG_STRU;

/*****************************************************************************
 结构名称  : ADS_IPF_MEM_POOL_CFG_STRU
 结构说明  : 内存池配置结构

  1.日    期   : 2015年10月06日
    作    者   : A00165503
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEnable;
    ADS_IPF_MEM_CFG_STRU                astMemCfg[ADS_IPF_MEM_POOL_ID_BUTT];

} ADS_IPF_MEM_POOL_CFG_STRU;

/*****************************************************************************
 结构名称  : ADS_IPF_MEM_POOL_CFG_STRU
 结构说明  : 内存配置结构

  1.日    期   : 2015年10月06日
    作    者   : A00165503
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usBlkSize;
    VOS_UINT16                          usBlkNum;
    VOS_UINT8                           ucPort;
    VOS_UINT8                           aucReserved[3];
    IMM_ZC_HEAD_STRU                    stQue;

} ADS_IPF_MEM_POOL_STRU;

/*****************************************************************************
 结构名    : ADS_IPF_CTX_STRU
 结构说明  : ADS与IPF相关的上下文
   1.日    期   : 2012年11月23日
     作    者   : L60609
     修改内容   : DSDA Phase II
*****************************************************************************/
typedef struct
{
    IPF_CONFIG_ULPARAM_S                astIpfUlBdCfgParam[IPF_ULBD_DESC_SIZE]; /* 上行BD DESC */
    IPF_RD_DESC_S                       astIpfDlRdDesc[IPF_DLRD_DESC_SIZE];     /* 下行RD DESC */
    /* AD */
    IPF_AD_DESC_S                       astIpfDlAdDesc[ADS_DL_ADQ_MAX_NUM][IPF_DLAD0_DESC_SIZE];   /* 下行AD DESC */
    ADS_IPF_BD_BUFF_STRU                astIpfUlBdBuff[IPF_ULBD_DESC_SIZE];     /* 上行BD */
    IMM_ZC_HEAD_STRU                    stUlSrcMemFreeQue;                      /* IPF上行内存释放BUFF */
    ADS_UL_DYNAMIC_ASSEM_INFO_STRU      stUlAssemParmInfo;                      /* 上行动态组包信息 */
    VOS_UINT32                          ulThredHoldNum;                         /* 上行赞包门限值 */
    VOS_UINT32                          ulProtectTmrLen;
    VOS_UINT8                           ucSendingFlg;                           /* 正在发送标志 */
    VOS_UINT8                           aucRsv[3];

    VOS_UINT32                          ulWakeLockEnable;                       /* wake lock 使能标识 */

    struct wake_lock                    stUlBdWakeLock;                         /* wake lock BD */
    struct wake_lock                    stDlRdWakeLock;                         /* wake lock RD */

    struct wake_lock                    stRxWakeLock;                           /* wake lock RX */
    struct wake_lock                    stTxWakeLock;                           /* wake lock TX */

    VOS_UINT32                          ulUlBdWakeLockCnt;                      /* wake lock BD 计数 */
    VOS_UINT32                          ulDlRdWakeLockCnt;                      /* wake lock BD 计数 */

    VOS_UINT32                          ulRxWakeLockTimeout;                    /* wake lock RX 超时时间 */
    VOS_UINT32                          ulTxWakeLockTimeout;                    /* wake lock TX 超时时间 */

    VOS_UINT32                          ulTxWakeLockTmrLen;                     /* wake lock TX 超时配置 */
    VOS_UINT32                          ulRxWakeLockTmrLen;                     /* wake lock RX 超时配置 */

    struct device                       stDev;
#if (defined(CONFIG_BALONG_SPE))
    VOS_INT32                           lSpeWPort;
    ADS_IPF_MEM_POOL_CFG_STRU           stMemPoolCfg;
    ADS_IPF_MEM_POOL_STRU               astMemPool[ADS_IPF_MEM_POOL_ID_BUTT];
#endif

}ADS_IPF_CTX_STRU;

/*****************************************************************************
结构名    : ADS_SPEC_CTX_STRU
结构说明  : ADS每个实例专有的上下文

  1.日    期   : 2012年11月23日
    作    者   : 鲁琳/l60609
    修改内容   : DSDA Phase II: 定义ADS每个实例专有的上下文
*****************************************************************************/
typedef struct
{
    ADS_UL_CTX_STRU                     stAdsUlCtx;                             /* 上行上下文 */
    ADS_DL_CTX_STRU                     stAdsDlCtx;                             /* 下行上下文 */

}ADS_SPEC_CTX_STRU;

/*****************************************************************************
结构名    : ADS_CTX_STRU
结构说明  : ADS上下文

  1.日    期   : 2011年12月6日
    作    者   : 鲁琳/l60609
    修改内容   : 定义ADS上下文

  2.日    期   : 2012年11月23日
    作    者   : L60609
    修改内容   : DSDA Phase II
*****************************************************************************/
typedef struct
{
    ADS_SPEC_CTX_STRU                   astAdsSpecCtx[ADS_INSTANCE_MAX_NUM];    /* 每个实例专有的上下文 */
    ADS_STATS_INFO_CTX_STRU             stDsFlowStatsCtx;                       /* 流量统计 */
    ADS_IPF_CTX_STRU                    stAdsIpfCtx;                            /* 与IPF相关的上下文 */
    ADS_TIMER_CTX_STRU                  astAdsTiCtx[ADS_MAX_TIMER_NUM];         /* 定时器上下文 */
    VOS_UINT8                           ucAdsCurInstanceIndex;                  /* 当前实例的index */
    VOS_UINT8                           ucUlResetFlag;
    VOS_UINT8                           aucRsv[6];
    VOS_SEM                             hULResetSem;                            /* 二进制信号量，用于UL复位处理  */
    VOS_SEM                             hDLResetSem;                            /* 二进制信号量，用于DL复位处理  */
}ADS_CTX_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

extern VOS_UINT32                       g_ulAdsULTaskId;
extern VOS_UINT32                       g_ulAdsDLTaskId;
extern VOS_UINT32                       g_ulAdsULTaskReadyFlag;
extern VOS_UINT32                       g_ulAdsDLTaskReadyFlag;
extern ADS_CTX_STRU                     g_stAdsCtx;


/*****************************************************************************
  10 函数声明
*****************************************************************************/

VOS_UINT32 ADS_UL_IsAllRabNotSndPermitFlg(VOS_VOID);
VOS_UINT32 ADS_UL_GetSpecInstanceSndPermitFlg(VOS_UINT8 ucInstanceIndex);
VOS_VOID ADS_DL_ProcEvent(VOS_UINT32 ulEvent);
VOS_VOID ADS_DL_SndEvent(VOS_UINT32 ulEvent);
ADS_DL_CTX_STRU* ADS_GetDlCtx(VOS_UINT8 ucInstanceIndex);
ADS_TIMER_CTX_STRU* ADS_GetTiCtx(VOS_VOID);
ADS_UL_CTX_STRU* ADS_GetUlCtx(VOS_UINT8 ucInstanceIndex);
VOS_VOID ADS_InitCtx(VOS_VOID);
VOS_VOID ADS_InitDlCtx(VOS_UINT8 ucInstance);
VOS_VOID ADS_InitIpfCtx(VOS_VOID);
VOS_VOID ADS_InitSpecCtx(VOS_VOID);
VOS_VOID ADS_InitStatsInfoCtx(VOS_VOID);
VOS_VOID ADS_InitTiCtx(VOS_VOID);
VOS_VOID ADS_InitUlCtx(VOS_UINT8 ucInstanceIndex);
VOS_UINT32 ADS_UL_CheckAllQueueEmpty(VOS_UINT8 ucInstanceIndex);
VOS_VOID ADS_UL_ClearQueue(
    VOS_UINT8                           ucRabId,
    IMM_ZC_HEAD_STRU                   *pstQueue
);
VOS_UINT32 ADS_UL_CreateQueue(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           ucRabId,
    ADS_QCI_TYPE_ENUM_UINT8             enPrio,
    ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8     enPdpType,
    VOS_UINT8                           uc1XorHrpdUlIpfFlag
);
VOS_VOID ADS_UL_DestroyQueue(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           ucRabId
);
VOS_UINT32 ADS_UL_GetAllQueueDataNum(VOS_VOID);
VOS_UINT32 ADS_UL_GetInsertIndex(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           ucRabId
);
VOS_UINT32 ADS_UL_GetInstanceAllQueueDataNum(VOS_UINT8 ucInstanceIndex);
VOS_UINT32 ADS_UL_InsertQueue(
    VOS_UINT8                           ucInstance,
    IMM_ZC_STRU                        *pstData,
    VOS_UINT8                           ucRabId
);
VOS_UINT32 ADS_UL_IsQueueExistent(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           ucRabId
);
VOS_VOID ADS_UL_OrderQueueIndex(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           ucIndex
);
VOS_VOID ADS_UL_ProcEvent(VOS_UINT32 ulEvent);
VOS_VOID ADS_UL_SetProtectTmrLen(VOS_UINT32 ulTimerLen);
VOS_VOID ADS_UL_SetQueue(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           ucRabId,
    VOS_UINT8                           ucIsQueueValid,
    IMM_ZC_HEAD_STRU                   *pstUlQueue,
    ADS_QCI_TYPE_ENUM_UINT8             enPrio,
    ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8     enPdpType,
    VOS_UINT8                           uc1XorHrpdUlIpfFlag
);
VOS_VOID ADS_UL_SndEvent(VOS_UINT32 ulEvent);
VOS_VOID ADS_UL_UpdateQueueInPdpDeactived(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           ucRabId
);
VOS_VOID ADS_UL_UpdateQueueInPdpModified(
           VOS_UINT8                           ucInstanceIndex,
           ADS_QCI_TYPE_ENUM_UINT8             enPrio,
           VOS_UINT8                           ucRabId
);
ADS_CTX_STRU* ADS_GetAllCtx(VOS_VOID);

VOS_UINT32 ADS_UL_EnableRxWakeLockTimeout(VOS_UINT32 ulValue);
VOS_UINT32 ADS_UL_WakeLockTimeout(VOS_VOID);
VOS_UINT32 ADS_UL_WakeLock(VOS_VOID);
VOS_UINT32 ADS_UL_WakeUnLock(VOS_VOID);
VOS_UINT32 ADS_DL_EnableTxWakeLockTimeout(VOS_UINT32 ulValue);
VOS_UINT32 ADS_DL_WakeLockTimeout(VOS_VOID);
VOS_UINT32 ADS_DL_WakeLock(VOS_VOID);
VOS_UINT32 ADS_DL_WakeUnLock(VOS_VOID);

VOS_VOID ADS_DL_InitFcAssemParamInfo(VOS_VOID);
VOS_SEM ADS_GetULResetSem(VOS_VOID);
VOS_SEM ADS_GetDLResetSem(VOS_VOID);
VOS_VOID ADS_DL_ResetFcAssemParamInfo(VOS_VOID);
VOS_VOID ADS_ResetSpecUlCtx(VOS_UINT8 ucInstance);
VOS_VOID ADS_ResetUlCtx(VOS_VOID);
VOS_VOID ADS_ResetSpecDlCtx(VOS_UINT8 ucInstance);
VOS_VOID ADS_ResetDlCtx(VOS_VOID);
VOS_VOID ADS_ResetIpfCtx(VOS_VOID);

VOS_UINT32 ADS_UL_IsAnyQueueExist(VOS_VOID);

VOS_UINT8 ADS_GetUlResetFlag(VOS_VOID);
VOS_VOID  ADS_SetUlResetFlag(VOS_UINT8 ucFlag);

VOS_UINT32 ADS_IPF_IsSpeMem(IMM_ZC_STRU *pstImmZc);
IMM_ZC_STRU* ADS_IPF_AllocMem(VOS_UINT32 ulPoolId, VOS_UINT32 ulLen, VOS_UINT32 ulReserveLen);
dma_addr_t ADS_IPF_GetMemDma(IMM_ZC_STRU *pstImmZc);
VOS_VOID ADS_IPF_SetMemDma(IMM_ZC_STRU *pstImmZc, dma_addr_t ulDmaAddr);
VOS_VOID ADS_IPF_MemMapRequset(IMM_ZC_STRU *pstImmZc, VOS_UINT32 ulLen, VOS_UINT8 ucIsIn);
VOS_VOID ADS_IPF_MemMapByDmaRequset(IMM_ZC_STRU *pstImmZc, VOS_UINT32 ulLen, VOS_UINT8 ucIsIn);
VOS_VOID ADS_IPF_MemUnmapRequset(IMM_ZC_STRU *pstImmZc, VOS_UINT32 ulLen, VOS_UINT8 ucIsIn);

#if (defined(CONFIG_BALONG_SPE))
VOS_VOID ADS_IPF_InitMemPoolCfg(VOS_VOID);
VOS_VOID ADS_IPF_CreateMemPool(VOS_VOID);
#endif


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif


