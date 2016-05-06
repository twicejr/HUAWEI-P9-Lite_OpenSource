/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : RabmStru.h
  Description : RABM数据结构头文件
  History     :
      1.  张志勇      2003.12.04   新版作成
      2.  L47619   2005.12.12   A32D01107问题单
      3.日    期  : 2006年12月4日
        作    者  : luojian id:60022475
        修改内容  : 增加 #pragma pack(4)，问题单号:A32D07779
*******************************************************************************/

#ifndef _RABM_STRU_INTERFACE_H_
#define _RABM_STRU_INTERFACE_H_

#include "NasTtf_typedef.h"
#include "TTFLink.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */

#pragma pack(4)
#define RABM_PS_MAX_ENT_NUM         11
#define RABM_CS_MAX_ENT_NUM         14
#define RABM_MAX_RB_NUM_PER_RAB     3
#define RABM_MAX_RB_ID              32

#define RABM_MAX_SAVE_MSG_NUM   1

#define RABM_MAX_TAF_NUM        1

#define RABM_RABM_REEST_PROT_TIMER_LEN    30000                                 /* rab重建保护timer时长                     */

#define NAS_RABM_MAX_QOS_LEN            (16)

/*PDCP->RABM数据队列一次最多允许处理的结点个数*/
#define RABM_PDCP_ONCE_DEAL_MAX_CNT     100

#define RABM_TC_NO_START                (0)                 /* 没有启动TC                           */
#define RABM_TC_LOOP_OPEN               (1)                 /* TC启动，测试环没有关闭               */
#define RABM_TC_LOOP_CLOSE              (2)                 /* TC启动，测试环关闭，开始处理TC数据   */

typedef struct{
    VOS_UINT8     ucRabId;                                                          /* 该RAB对应的RAB ID                        */
    VOS_UINT8     ucRbNum;                                                          /* 该RAB包含RB数量                          */
    VOS_UINT8     aucRbId[RABM_MAX_RB_NUM_PER_RAB];                                 /* RB ID列表                                */
    VOS_UINT8     aucRbTxMode[RABM_MAX_RB_NUM_PER_RAB];                             /* RB 传输模式(与aucRbId下标一致)*/
}RABM_RAB_INFO_STRU;

/*****************************************************************************
 结构名  : RABM_QOS_STRU
 结构说明: RABM实体保存的QOS结构

 修改历史      :
  1.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : 修改成员
*****************************************************************************/
typedef struct{
    VOS_UINT32                          ulQosLength;                            /* Qos的数据大小 */
    VOS_UINT8                           aucQosValue[NAS_RABM_MAX_QOS_LEN];        /* Qos数据首地址 */
} RABM_QOS_STRU;

typedef struct datalink{
    VOS_VOID       *pData;                                                          /* 数据首地址                               */
    struct datalink   *pNxt;                                                    /* 下一个数据节点地址                       */
}RABM_DATA_LINK_STRU;

typedef struct datasave{
    VOS_UINT8    ucNum;                                                             /* 消息个数                                 */
    RABM_DATA_LINK_STRU   Data;                                                 /* 存储的消息链表                           */
}RABM_DATA_SAVE_STRU;


typedef struct
{
    VOS_UINT8                           ucState;            /* 本实体的状态                             */
    VOS_UINT8                           ucPppFlg;           /* 是否支持PPP，0：支持；1:不支持           */
    VOS_UINT8                           ucReEstFlg;         /* 是否为重建RAB的标志                      */
    VOS_UINT8                           ucStpFlg;           /* 标志是否已经通知taf停止数据传输，
                                                             * RABM_TRUE:已经通知,RABM_FALSE:没有通知   */
    HTIMER                              hRabPendingTmrHdl;  /* RAB重建保护定时器                        */
    RABM_RAB_INFO_STRU                  RabInfo;            /* 该实体对应的RAB信息                      */
    RABM_QOS_STRU                       QoS;                /* 本实体对应的QoS                          */
    RABM_DATA_SAVE_STRU                 DlDataSave;         /* 缓存的下行数据首地址                     */
    RABM_DATA_SAVE_STRU                 UlDataSave;         /* 缓存的上行数据首地址                     */
}RABM_ENTITY_PS_STRU;


typedef struct
{
    VOS_UINT8   ucState;                                                            /* 本实体的状态                             */
    VOS_UINT8   ucSi;                                                               /* 实体对应的si                             */
    RABM_RAB_INFO_STRU   RabInfo;                                               /* 该实体对应的RAB信息                      */
}RABM_ENTITY_CS_STRU;

typedef struct
{
    VOS_UINT8   ucRbNum;                                                            /* 传输AMR数据所需的RB个数                  */
    VOS_UINT8   aucDataLen[3];                                                      /* 数据的bit长度                            */
    VOS_UINT8   aucLenOffset[3];                                                    /* CLASS i的数据与padding长度               */
    VOS_UINT8   *apucData[3];                                                       /* 数据首地址                               */
} RABM_AMR_DATA_STRU;

typedef struct{
    VOS_UINT8           ucTcStartSta;
    VOS_UINT8           ucLbCnt;
    struct{
        VOS_UINT8           ucEstFlg;                                               /* 标志该rb是否已经建立,RABM_TRUE:建立,
                                                                                 * RABM_FALSE:没有建立                      */
        VOS_UINT8           ucRabId;
        VOS_UINT8           ucRbId;
        VOS_UINT8           ucDomain;
        VOS_UINT32          ulRlcSduSize;                                           /* 该RB传输的上行RLC SDU的大小              */
        VOS_BOOL            bRlcSduSizeValid;
    }aRbInf[TC_LB_MAX_RBNUM];

    VOS_BOOL                bFlowCtrlFlg;
    VOS_UINT8               ucTestLoopMode;
}RABM_TC_INF_STRU;


typedef struct
{
    VOS_UINT8               ucRbId;             /* [5,32] 标识与该RB ID对应的PDCP实体*/
    VOS_UINT8               aucReserve[3];      /* 4字节对齐，保留*/
    VOS_UINT32              ulDataLen;          /* 数据的长度,单位:字节 */
    VOS_UINT8              *pucData;            /* 数据首地址 */
}PDCP_RABM_DATA_BUF_STRU;


/******************************************************************************
*     PDCP_RABM_TC_DATA_STRU 原语定义，用于PS域环回功能上行数据接口
      接口功能描述: RABM向PDCP发送上行环回数据时，需要将下行环回数据的
                    零拷贝内存转换为线性内存
******************************************************************************/
typedef struct
{
    VOS_UINT8               ucRbId;             /* [5,32] 标识与该RB ID对应的PDCP实体*/
    VOS_UINT8               aucReserve[3];      /* 4字节对齐，保留*/
    DL_DATA_CRC_INFO_STRU   stCrcInfo;          /* CRC信息，仅用于PS域环回模式二 */
    VOS_UINT32              ulDataBitLen;       /* 数据的长度,单位:Bit */
    TTF_MEM_ST             *pstDataMem;
}PDCP_RABM_TC_DATA_STRU;


/******************************************************************************
*     PDCP_RABM_TC_DATA_Q_STAT_STRU 原语定义，用于PS域环回功能下行数据的统计信息
******************************************************************************/
typedef struct
{
    VOS_UINT32                  ulDlTotalCnt;       /*下行数据包总个数*/
    VOS_UINT32                  ulQMaxCnt;          /*PDCP一次递交给RABM的数据块数的最大值*/
    VOS_UINT32                  ulMaxCntOnce;       /*RABM一次处理数据块数的最大值*/
}PDCP_RABM_TC_DATA_Q_STAT_STRU;

/******************************************************************************
*     PDCP_RABM_TC_DATA_Q_CFG_STRU 原语定义，用于PS域环回功能下行数据的配置信息
******************************************************************************/
typedef struct
{
    VOS_UINT32                  ulOnceDealMaxCnt;  /*RABM数据队列一次最多允许处理的结点个数*/
}PDCP_RABM_TC_DATA_Q_CFG_STRU;

/******************************************************************************
*     PDCP_RABM_TC_DATA_Q_STRU 原语定义，用于PS域环回功能下行数据队列
******************************************************************************/
typedef struct
{
    TTF_LINK_ST                    stDataQ;
    PDCP_RABM_TC_DATA_Q_STAT_STRU  stStat;      /*PDCP->RABM数据队列的统计信息*/
    PDCP_RABM_TC_DATA_Q_CFG_STRU   stCfg;       /*PDCP->RABM数据队列的配置信息*/
}PDCP_RABM_TC_DATA_Q_STRU;

/******************************************************************************
*     PDCP_RABM_TC_DATA_IND_NOTIFY_STRU 原语定义，用于PS域环回功能下行数据接口
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /* _H2ASN_Skip */
    NAS_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve[2];      /* 4字节对齐，保留*/
} PDCP_RABM_TC_DATA_IND_NOTIFY_STRU;



extern RABM_ENTITY_PS_STRU    g_aRabmPsEnt[RABM_PS_MAX_ENT_NUM];                /* PS域RABM实体的全局量                     */
extern RABM_ENTITY_CS_STRU    g_aRabmCsEnt[RABM_CS_MAX_ENT_NUM];                /* CS域RABM实体的全局量                     */


extern VOS_UINT8        g_aucSiMapEnt[256];                                         /* SI和RABM实体的映射关系                   */
extern VOS_UINT8        g_ucReestTimerFlg;                                          /* RABM_TRUE:重建TIMER有效；RABM_FALSE:无效 */
extern HTIMER     g_ulRabReestTimerId;                                        /* rab重建保护timer                         */

extern RABM_RRC_IMPORTED_FUNC_LIST_STRU  g_RabmRrcImportFunc;

extern RABM_TC_INF_STRU       g_RabmTcInf;

extern PDCP_RABM_TC_DATA_Q_STRU g_stPdcpRabmTcDataQ;

extern VOS_UINT32                       g_ulNasRabmRabPendingTmrLen;



#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif                                                                          /* __cpluscplus                             */

#endif
