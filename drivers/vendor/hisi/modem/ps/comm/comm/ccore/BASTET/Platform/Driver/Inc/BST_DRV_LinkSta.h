/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司
 *****************************************************************************
  文 件 名   : BST_DRV_LinkSta.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 
  最近修改   :
  功能描述   : 
  函数列表   :

  修改历史   :
  1.日    期   : 
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/
#ifndef __BST_DRV_LINKSTA_H__
#define __BST_DRV_LINKSTA_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_DRV_Common.h"
#include "BST_SRV_Define.h"
#include "BST_DRV_As.h"
#include "BST_DRV_Net.h"
#include "BST_PAL_As.h"
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define BST_DRV_LS_BUF_FAC          ( 0x03 )
#define BST_DRV_LS_BUF_LENGTH       ( ( 0x01 ) << ( BST_DRV_LS_BUF_FAC ) )
#define BST_DRV_LsGetInstance()     ( &g_BstDrvLsInstance )
#define BST_DRV_LsGetNetThreshold() ( &g_BstDrvLsInstance.stThreshold )
#define BST_DRV_LsMdmIdValid(id)    ( (id) < BST_MODEM_MAX )
#define BST_DRV_LsIsRatSnValid(sn)  ( ((sn)!=BST_DRV_LS_RAT_INVALID_SN)\
                                    &&((sn)<BST_DRV_LS_RAT_NUMBER) )

#define BST_DRV_LS_ONE_HUNDRED      ( 100U )
#define BST_DRV_LS_FULL_SCORE       ( 100U )   /* 链路质量优时，默认100分 */
#define BST_DRV_LS_ZERO_SCORE       ( 0U )     /* 链路质量不可用时，为0分 */
#define BST_DRV_LS_WEAK_SCORE       ( 40U )    /* 链路质量为差时，0-40分 */
#define BST_DRV_LS_MIDD_SCORE       ( 70U )    /* 链路质量为中时，40-70分 */
#define BST_DRV_LS_TRX_ADD_SVALUE   ( 10U )    /* 有数据收到，加分10 */
#define BST_DRV_LS_EXTRA_SCORE      ( 5U )     /* 网络质量从差->中，中->高变化时，网络质量分数变化需要大于BST_DRV_LS_EXTRA_SCORE*/

#define BST_DRV_LS_POOR_SCORE       ( 20 )     /* 当连接态重传率得分低于该值时，IDLE态下依靠此条件来判断网络质量是否处于低 */
#define BST_DRV_LS_STATIC_VRC       ( 15 )     /* 静态方差门限值 */
#define BST_DRV_LS_STATIC_CNT       ( 16 )     /* 当静态计数器大于等于该值，为静止状态 */
#define BST_DRV_LS_DYNAMIC_CNT      ( 8 )      /* 当静态计数器小于等于该值，为移动状态 */

/* 计算移位偏移量 */
#define BST_DRV_LS_BIT1_FAC         ( 1U )
#define BST_DRV_LS_BIT2_FAC         ( 2U )
#define BST_DRV_LS_BIT3_FAC         ( 3U )
#define BST_DRV_LS_BIT4_FAC         ( 4U )
#define BST_DRV_LS_BIT5_FAC         ( 5U )
#define BST_DRV_LS_BIT6_FAC         ( 6U )
#define BST_DRV_LS_BIT7_FAC         ( 7U )
#define BST_DRV_LS_BIT8_FAC         ( 8U )
#define BST_DRV_LS_BIT9_FAC         ( 9U )
#define BST_DRV_LS_BIT13_FAC        ( 13U )

/* 计算权重，根据N、T、Q值的有效性选择计算 */
#define BST_DRV_LS_NONE_USED_BIT    ( 0x00 )
#define BST_DRV_LS_N_USED_BIT       ( 0x01 )
#define BST_DRV_LS_Q_USED_BIT       ( 0x02 )
#define BST_DRV_LS_T_USED_BIT       ( 0x04 )
#define BST_DRV_LS_NQ_USED_BIT      ( BST_DRV_LS_N_USED_BIT | BST_DRV_LS_Q_USED_BIT )
#define BST_DRV_LS_NT_USED_BIT      ( BST_DRV_LS_N_USED_BIT | BST_DRV_LS_T_USED_BIT )
#define BST_DRV_LS_TQ_USED_BIT      ( BST_DRV_LS_T_USED_BIT | BST_DRV_LS_Q_USED_BIT )
#define BST_DRV_LS_ALL_USED_BIT     ( BST_DRV_LS_N_USED_BIT | BST_DRV_LS_Q_USED_BIT | BST_DRV_LS_T_USED_BIT )

#define BST_AS_INVALID_CELLID       ( 0xFFFF ) /* 无效小区ID */

/* 发送PDU样本个数，当大于该样本值时，才计算重传率 */
#define BST_DRV_LS_TX_PKT_NUM       ( 50U )

/* 队列门限判断 */
#define BST_DRV_LS_QUE_HIGH         ( 9216 )  /*队列清空时间 9216ms*/
#define BST_DRV_LS_QUE_LOW          ( 1024 )  /*队列清空时间 1024ms*/

#define BST_DRV_LS_QUE_LEN_MIN      ( 8192 )  /*队列长度最小值，当缓存队列小于8K时，不计算缓存队列的比重*/

/* TL场景下无效的RSRP和RSRQ值 */
#define BST_DRV_INVALID_RSCP        ( 99 )
#define BST_DRV_INVALID_ECI0        ( 99 )

/* 无效的带宽值 */
#define BST_DRV_INVALID_BAND_WIDTH  ( 0xFFFF )

#define BST_DRV_LS_MOD_SUB(x, y)    ( ( (x) > (y) ) ? ( ( x ) - ( y ) ) : ( 0 ) )

#define BST_DRV_LsGetDvcHandle()    ( &g_BstDrvLinkStateHandle );

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 枚举定义
*****************************************************************************/
enum{
    BST_DRV_LS_RAT_INVALID_SN       = 0U,
    BST_DRV_LS_RAT_GSM_SN,
    BST_DRV_LS_RAT_WCDMA_SN,
    BST_DRV_LS_RAT_TDSCDMA_SN,
    BST_DRV_LS_RAT_LTE_SN,
    BST_DRV_LS_RAT_NUMBER
};
typedef BST_UINT32                  BST_DRV_LS_RAT_SN_ENUM_UINT32;


enum{
    BST_DRV_LS_AP_STATE_SLEEP       = 0U,
    BST_DRV_LS_AP_STATE_WAKEUP,
    BST_DRV_LS_AP_STATE_BUTT
};
typedef BST_UINT32                  BST_DRV_LS_AP_STATE_UINT32;

enum{
    BST_DRV_LS_STATE_STATIC       = 0U,
    BST_DRV_LS_STATE_DYNAMIC,
    BST_DRV_LS_STATE_BUTT
};
typedef BST_UINT16                  BST_DRV_LS_MOVING_STATE_UINT16;

/*****************************************************************************
  5 类/结构定义
*****************************************************************************/
typedef BST_UINT32 ( *BST_DRV_LS_READ_TRS_FUNC )(
    BST_UINT32    *pulTotPktNumber,
    BST_UINT32    *pulRtxPktNumber );

typedef BST_UINT32 ( *BST_DRV_LS_READ_QUE_FUNC )(
    BST_UINT32    *pulQueLength,
    BST_UINT32    *pulBandWith );

typedef struct
{
    BST_UINT16                          usCounter;
    BST_UINT16                          usIsFull;
    BST_INT16                           asRscp[ BST_DRV_LS_BUF_LENGTH ];
    BST_INT16                           asEcI0[ BST_DRV_LS_BUF_LENGTH ];
}BST_DRV_LS_NETSTR_BUFF_STRU;

typedef struct{
  struct{
            BST_INT16                   sRxLevAMin;
            BST_INT16                   sRxLevAMax;
      }gsm;
  struct{
            BST_INT16                   sRscpMin;
            BST_INT16                   sRscpMax;
            BST_UINT16                  usReTxMin;
            BST_UINT16                  usReTxMax;
      }tdscdma;
  struct{
            BST_INT16                   sRscpMin;
            BST_INT16                   sRscpMax;
            BST_INT16                   sEci0Min;
            BST_INT16                   sEci0Max;
            BST_UINT16                  usReTxMin;
            BST_UINT16                  usReTxMax;
      }wcdma;
  struct{
            BST_INT16                   sRsrpMin;
            BST_INT16                   sRsrpMax;
            BST_INT16                   sRsrqMin;
            BST_INT16                   sRsrqMax;
            BST_UINT16                  usReTxMin;
            BST_UINT16                  usReTxMax;
      }lte;
}BST_DRV_LS_THRESHOLD_STRU;

typedef struct{
    BST_UINT32                          ulStatFlag;
    BST_UINT32                          ulTotalPkt;
    BST_UINT32                          ulTotalRePkt;
}BST_DRV_LS_RLC_PDU_STAT;

typedef struct{
    BST_AS_NET_RANK_ENUM_UINT32         ulRankValue;         /* 当前链路等级 */
    BST_AS_NET_RANK_ENUM_UINT32         ulLastRank;          /* 当从block到unblock状态时，上报上一次记录的RANK等级 */
    BST_MODEM_ID_ENUM_UINT32            ulCurModemId;        /* 当前PS域ModemId */
    BST_AS_RAT_MODE_UINT32              ulCurRAT;            /* 当前PS-MODEM RAT */
    BST_AS_RRC_STATE_ENUM_UINT32        ulCurRrc;            /* 当前RRC模式 */
    BST_DRV_NET_STATE_ENUM_UINT32       ulNetDeviceState;    /* 当前网卡状态,up or down */
    BST_UINT32                          ulBlockState;        /* 当前网络block状态 */
    BST_UINT32                          ulCellId;            /* 当前小区ID */
    BST_UINT32                          ulCurDValue;         /* 当前是否有收发的加分项 */
    BST_DRV_LS_NETSTR_BUFF_STRU         stNetSta;            /* 计算网络质量Buffer */
    BST_DRV_LS_THRESHOLD_STRU           stThreshold;         /* 网络质量门限值，信号强度、重传率 */
    BST_DRV_LS_RLC_PDU_STAT             stRlcStat;           /* TL制式下RLC层pdu信息统计结构体 */
    BST_UINT32                          ulTransScore;        /* 连接态下RLC重传率得分，供IDLE态使用 */
    BST_DRV_LS_MOVING_STATE_UINT16      usMovingState;       /* 移动、静止状态 */
    BST_UINT16                          usStaticCounter;     /* 静止计数器 */

    /* 各制式获取实时重传特性的入口函数 */
    BST_DRV_LS_READ_TRS_FUNC            apfReadTrsInfo[ BST_MODEM_MAX ][ BST_DRV_LS_RAT_NUMBER ];

    /* 各制式获取实时发送队列的入口函数 */
    BST_DRV_LS_READ_QUE_FUNC            apfReadQueInfo[ BST_MODEM_MAX ][ BST_DRV_LS_RAT_NUMBER ];
}BST_DRV_LS_INS_STRU;

/*****************************************************************************
  6 UNION定义
*****************************************************************************/

/*****************************************************************************
  7 全局变量声明
*****************************************************************************/
extern BST_DRV_STRU    g_BstDrvLinkStateHandle;
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


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif
