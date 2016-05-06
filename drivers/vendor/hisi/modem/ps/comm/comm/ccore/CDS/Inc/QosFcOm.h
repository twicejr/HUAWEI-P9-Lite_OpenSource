/******************************************************************************

                  版权所有 (C), 2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : QosFcOm.h
  版 本 号   : 初稿
  作    者   : w00145177
  生成日期   : 2011年12月23日
  最近修改   :
  功能描述   : QoS流控可维可测功能头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月23日
    作    者   : w00145177
    修改内容   : 创建文件

******************************************************************************/

#ifndef __QOS_FC_OM_H__
#define __QOS_FC_OM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "QosFcCommon.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/

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
 结构名    : QOS_FC_STATS_INFO
 协议表格  :
 ASN.1描述 :
 结构说明  : QOS流控统计量
*****************************************************************************/
typedef struct QOS_FC_STATS_INFO
{
    VOS_UINT32              ulCreateMsgNum;                     /* 收到CREATE消息数量 */
    VOS_UINT32              ulReleaseMsgNum;                    /* 收到RELEASE消息数量 */
    VOS_UINT32              ulCreateRabNum;                     /* 创建承载次数 */
    VOS_UINT32              ulUpdateRabNum;                     /* 更新承载次数 */
    VOS_UINT32              ulReleaseRabNum;                    /* 释放承载次数 */
    VOS_UINT32              aulToRandomDiscardNum[MODEM_ID_BUTT][FC_MAX_RAB_NUM];  /* 上行每个承载进入随机丢包状态次数 */
    VOS_UINT32              aulToDiscardNum[MODEM_ID_BUTT][FC_MAX_RAB_NUM];        /* 上行每个承载进入丢包状态次数 */
    VOS_UINT32              aulToNormalNum[MODEM_ID_BUTT][FC_MAX_RAB_NUM];         /* 上行每个承载恢复正常状态次数 */
    VOS_UINT32              aulRcvPktNumOnD[MODEM_ID_BUTT][FC_MAX_RAB_NUM];        /* 上行每个承载上丢包状态时收包数量 */
    VOS_UINT32              aulDiscardPktNumOnD[MODEM_ID_BUTT][FC_MAX_RAB_NUM];    /* 上行每个承载上丢包状态时丢包数量 */
    VOS_UINT32              aulRcvPktNumOnRD[MODEM_ID_BUTT][FC_MAX_RAB_NUM];       /* 上行每个承载上随机丢包状态时收包数量 */
    VOS_UINT32              aulDiscardPktNumOnRD[MODEM_ID_BUTT][FC_MAX_RAB_NUM];   /* 上行每个承载上随机丢包状态时丢包数量 */
    VOS_UINT32              aulChannelToFc[MODEM_ID_BUTT][FC_MAX_RAB_NUM];         /* 通道流控次数 */
    VOS_UINT32              aulChannelResume[MODEM_ID_BUTT][FC_MAX_RAB_NUM];       /* 解通道流控次数 */
    VOS_UINT32              ulUlLteDiscardTotalNum;                 /* 上行LTE丢包总数 */
    VOS_UINT32              ulUlGUDiscardTotalNum;                  /* 上行GU丢包总数 */
    VOS_UINT32              ulDlLteDiscardTotalNum;                 /* 下行LTE丢包总数 */
    VOS_UINT32              ulDlGUDiscardTotalNum;                  /* 下行GU丢包总数 */
    VOS_UINT32              ulDlCDMADiscardTotalNum;                  /* 下行CDMA丢包总数 */
    VOS_UINT32              ulUlCDMADiscardTotalNum;                 /* 上行CDMA丢包总数 */
}QOS_FC_STATS_INFO_STRU;



/*****************************************************************************
  6 UNION定义
*****************************************************************************/


/*****************************************************************************
  7 全局变量声明
*****************************************************************************/
extern QOS_FC_STATS_INFO_STRU g_stQosFcStats;

/* QoS流控统计 */
#define  FC_DBG_CREATE_MSG_STAT(n)                  (g_stQosFcStats.ulCreateMsgNum += (n))
#define  FC_DBG_RELEASE_MSG_STAT(n)                 (g_stQosFcStats.ulReleaseMsgNum += (n))
#define  FC_DBG_CREATE_RAB_STAT(n)                  (g_stQosFcStats.ulCreateRabNum += (n))
#define  FC_DBG_UPDATE_RAB_STAT(n)                  (g_stQosFcStats.ulUpdateRabNum += (n))
#define  FC_DBG_RELEASE_RAB_STAT(n)                 (g_stQosFcStats.ulReleaseRabNum += (n))

#define  FC_DBG_TO_RANDOMDISCARD_STAT(modem, rab, n)       (g_stQosFcStats.aulToRandomDiscardNum[modem][rab-5] += (n))
#define  FC_DBG_TO_DISCARD_STAT(modem, rab, n)             (g_stQosFcStats.aulToDiscardNum[modem][rab-5] += (n))
#define  FC_DBG_TO_NORMAL_STAT(modem, rab, n)              (g_stQosFcStats.aulToNormalNum[modem][rab-5] += (n))
#define  FC_DBG_RCV_PKT_OND_STAT(modem, rab, n)            (g_stQosFcStats.aulRcvPktNumOnD[modem][rab-5] += (n))
#define  FC_DBG_DISCARD_PKT_OND_STAT(modem, rab, n)        (g_stQosFcStats.aulDiscardPktNumOnD[modem][rab-5] += (n))
#define  FC_DBG_RCV_PKT_ONRD_STAT(modem, rab, n)           (g_stQosFcStats.aulRcvPktNumOnRD[modem][rab-5] += (n))
#define  FC_DBG_DISCARD_PKT_ONRD_STAT(modem, rab, n)       (g_stQosFcStats.aulDiscardPktNumOnRD[modem][rab-5] += (n))

#define  FC_DBG_CHANNEL_FC_STAT(modem, rab, n)             (g_stQosFcStats.aulChannelToFc[modem][rab-5] += (n))
#define  FC_DBG_CHANNEL_RESUME_STAT(modem, rab, n)         (g_stQosFcStats.aulChannelResume[modem][rab-5] += (n))

#define  FC_DBG_ULLTE_CDS_DISCARD_PKT_STAT(n)       (g_stQosFcStats.ulUlLteDiscardTotalNum += (n))
#define  FC_DBG_ULGU_CDS_DISCARD_PKT_STAT(n)        (g_stQosFcStats.ulUlGUDiscardTotalNum += (n))
#define  FC_DBG_DLLTE_CDS_DISCARD_PKT_STAT(n)       (g_stQosFcStats.ulDlLteDiscardTotalNum += (n))
#define  FC_DBG_DLGU_CDS_DISCARD_PKT_STAT(n)        (g_stQosFcStats.ulDlGUDiscardTotalNum += (n))
#define  FC_DBG_DLCDMA_CDS_DISCARD_PKT_STAT(n)       (g_stQosFcStats.ulDlCDMADiscardTotalNum += (n))
#define  FC_DBG_ULCDMA_CDS_DISCARD_PKT_STAT(n)       (g_stQosFcStats.ulUlCDMADiscardTotalNum += (n))


/*****************************************************************************
  8 函数声明
*****************************************************************************/


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

