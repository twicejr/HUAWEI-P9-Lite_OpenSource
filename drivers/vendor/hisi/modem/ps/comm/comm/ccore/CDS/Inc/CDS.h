/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : Cds.h
  版 本 号   : 初稿
  作    者   : y00151394
  生成日期   : 2011年12月12日
  最近修改   :
  功能描述   : 定义CDS相关的数据结构
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月12日
    作    者   : y00151394
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CDS_H__
#define __CDS_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "CdsDepend.h"


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*定义CDS处理事件*//*根据DOPRA手册，事件高16位为系统保留，用户使用低16位，OSA的使用待确定*/
#define  CDS_EVENT_BASE                 (0x00000000)
#define  CDS_EVENT_UL_IPF_INT           (CDS_EVENT_BASE | 0x0001)               /*上行IPF触发事件*/
#define  CDS_EVENT_DL_DATA_PROC         (CDS_EVENT_BASE | 0x0002)               /*CDS LTE模下在上行子帧中断总发出，GU模通过定时器发出*/
#define  CDS_EVENT_UL_ADQ_EMPTY         (CDS_EVENT_BASE | 0x0004)               /*IPF 桥模式ADQ空中断*/
#define  CDS_EVENT_UL_IMS_PROC          (CDS_EVENT_BASE | 0x0008)               /*IMS数据处理*/
#if (CDS_FEATURE_ON == CDS_FEATURE_BASTET)
#define  CDS_EVENT_UL_BASTET_PROC       (CDS_EVENT_BASE | 0x0010)               /*BASTET上行数据处理*/
#endif


/*上行IDLE队列大小*/
#define  CDS_UL_IDLE_QUE_SIZE           (256)

/*上行IMS队列大小*/
#define  CDS_IMS_QUE_SIZE               (64)
#if (CDS_FEATURE_ON == CDS_FEATURE_BASTET)
/*上行BASTET队列大小*/
#define  CDS_BASTET_QUE_SIZE            (256)
#endif

/*定义NAS最大承载数*/
#define  CDS_NAS_MAX_BEARER_NUM         (11)

/*定义NAS最小、最大承载ID*/
#define  CDS_NAS_MIN_BEARER_ID          (5)
#define  CDS_NAS_MAX_BEARER_ID          (15)

/*代表所有承载ID*/
#define  CDS_NAS_ALL_BEARER_ID          (0xFF)


/*CDS定时器时长，单位MS*/
#define  CDS_TMR_LEN                    (10)

/*上行数据保护定时器时长*/
#define  CDS_UL_DATA_PROTECT_TMR_LEN    (30*1000)

/*CDS下行缓存触发事件阈值*/
#define  CDS_DL_BUFF_TRIG_EVENT_THRES   (56)

/*CDS环回定义*/
#define  CDS_LB_QUE_SIZE                (16)

/*定义PDN最小、最大承载ID*/
#define  CDS_MIN_PDN_ID                 (0)
#define  CDS_MAX_PDN_ID                 (14)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 枚举定义
*****************************************************************************/
typedef enum CDS_TMR_ID
{
    CDS_TMR_ID_DL_10MS_PERIODIC_TMR         = 0x0,      /*下行10ms周期性定时器*/
    CDS_TMR_ID_LB_MODE_B_TMR                = 0x1,      /*环回模式B启动的定时器*/
    CDS_TMR_ID_UL_DATA_PROCTECT             = 0x2,      /*上行数据保护定时器*/
    CDS_TMR_ID_MODEM_BUTT,                              /*以上定时器是和Modem相关的，每一个CDS实体都存在*/

    /*IPF和流控相关定时器*/
    CDS_TMR_ID_ADQ_EMPTY_PROCTECT,                      /*ADQ空保护定时器*/
    CDS_TMR_ID_FC_CHECK_TMR,                            /*流控状态检查定时器*/
    CDS_TMR_ID_BUTT
}CDS_TMR_ID_ENUM;


/*****************************************************************************
 结构名    : CDS_UL_IP_PKT_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : 上行IP包类型
*****************************************************************************/
typedef enum CDS_UL_IP_PKT_TYPE
{
    CDS_UL_IP_PKT_TYPE_NORMAL,               /*正常数据包*/
    CDS_UL_IP_PKT_TYPE_IPSEG,                /*分片包*/
    CDS_UL_IP_PKT_TYPE_NDIS,                 /*需要发送到A核的NDIS数据包*/
    CDS_UL_IP_PKT_TYPE_ERROR,                /*IPF过滤错误数据包*/
    CDS_UL_IP_IPF_MODE_BUTT
}CDS_UL_IP_PKT_TYPE_ENUM;

typedef VOS_UINT32 CDS_UL_IP_PKT_TYPE_ENUM_UINT32;


/*****************************************************************************
 结构名    : CDS_LB_MODE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : CDS环回模式
*****************************************************************************/
typedef enum
{
    CDS_LB_MODE_A       = 0,
    CDS_LB_MODE_B       = 1,
    CDS_LB_MODE_BUTT
}CDS_LB_MODE_ENUM;

typedef VOS_UINT32 CDS_LB_MODE_ENUM_UINT32;

/*****************************************************************************
 结构名    : CDS_LB_STATE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : CDS环回状态
*****************************************************************************/
typedef enum
{
    CDS_LB_STATE_ACTIVE    = 0,
    CDS_LB_STATE_START     = 1,
    CDS_LB_STATE_STOP      = 2,
    CDS_LB_STATE_DEACTIVE  = 3,
    CDS_LB_STATE_BUTT
}CDS_LB_STATE_ENUM;

typedef VOS_UINT32 CDS_LB_STATE_ENUM_UINT32;

/*****************************************************************************
 结构名    : CDS_DIRECTION_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : CDS数传方向
*****************************************************************************/
typedef enum
{
    CDS_DIRECTION_UL       = 0,
    CDS_DIRECTION_DL       = 1,
    CDS_DIRECTION_BUTT
}CDS_DIRECTION_ENUM;


/*****************************************************************************
   5 STRUCT定义
*****************************************************************************/

/*****************************************************************************
 结构名    : CDS_LB_DL_SDU_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 环回模式下行接收到的SDU.
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSduLen;           /* 数据长度 */
    TTF_MEM_ST                         *pstSdu;             /* SDU数据指针 */
}CDS_LB_DL_SDU_STRU;


/*****************************************************************************
 结构名    : CDS_TIMER_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDS定时器信息
*****************************************************************************/
typedef struct
{
    HTIMER                   pstTmrHdr;
    VOS_UINT32               ulTmrId;
    VOS_UINT32               ulTmrLen;
    VOS_UINT32               ulPara;
}CDS_TIMER_STRU;


/*****************************************************************************
 结构名    : CDS_FLOW_STATS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDS的流量统计数据结构
*****************************************************************************/
typedef struct CDS_FLOW_STATS
{
    CDS_BEARER_DATA_FLOW_STRU    astBearerDS[CDS_NAS_MAX_BEARER_NUM];           /*NAS承载ID的有效范围:5-15*/
}CDS_DATA_FLOW_STRU;

/*****************************************************************************
 结构名    : CDS_ENTITY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 定义CDS任务实体结构
*****************************************************************************/
typedef struct CDS_ENTITY
{
    VOS_UINT16                          usModemId;
    VOS_UINT16                          usGuRabSRStatus;                        /*GU 承载触发SR状态标志位*/
    VOS_UINT16                          usCDMARabSRStatus;                        /*CDMA 承载触发SR状态标志位*/

    MMC_CDS_MODE_ENUM_UINT32            enRanMode;                              /*需要修改为ENUM类型*/
    VOS_UINT32                          ulServiceReqFlg;                        /*判断是否触发Service Request*/

    VOS_UINT32                          ulTestModeFlg;                          /*测试模式是否激活标志 : TRUE代表激活; FALSE代表未激活*/
    VOS_UINT32                          ulLoopBackMode;                         /*环回模式类型*/
    VOS_UINT32                          ulLoopBackState;                        /*环回模式状态*/

    LUP_QUEUE_STRU                     *pstUlDataQue;                           /*上行IDLE/SUSPEND态缓存，暂定256*/
    LUP_QUEUE_STRU                     *pstIMSDataQue;                          /*IMS数据队列*/
    LUP_QUEUE_STRU                     *pstLBModeBQue;                          /*环回模式队列*/
#if (CDS_FEATURE_ON == CDS_FEATURE_BASTET)
    LUP_QUEUE_STRU                     *pstBastetUlQue;                         /*数据业务代理数据队列*/
#endif
    CDS_TIMER_STRU                      astTimer[CDS_TMR_ID_MODEM_BUTT];        /*CDS定时器结构*/

    CDS_DATA_FLOW_STRU                  stFlowStats;                            /*流量统计*/

    VOS_UINT32                          ulImsBearerNum;                                 /*IMS承载个数*/
    IMSA_CDS_IMS_BEARER_STRU            astImsBearerInfo[IMSA_CDS_MAX_IMS_BEARER_NUM];  /*IMS承载类型信息*/
    IMSA_CDS_IMS_PORT_INFO_STRU         stImsPortInfo;

    VOS_UINT32                          ulUlSoftFilterNum;                              /*上行软过滤器个数*/
    CDS_SOFTFILTER_INFO_STRU            astUlSoftFilter[CDS_MAX_SOFT_FILTER_NUM];       /*本地上行软过滤器组*/

    /*特定承载ID*/
    VOS_UINT8                           ucMbmsBearerId;                         /*MBMS承载ID*/
    VOS_UINT8                           ucDbgBearerId;                          /*上传调试信息承载ID*/
    VOS_UINT8                           ucLBDefBearerId;                        /*环回模式缺省承载ID*/
    VOS_UINT8                           aucRes[1];

    VOS_UINT32                          ulULPktDiscardFlg;                      /*上行数据包丢弃开关*/
    VOS_UINT32                          ulDLPktDiscardFlg;                      /*下行数据包丢弃开关*/

    VOS_UINT32                          ulVoicePreferActFlag;                   /* VoicePrefer激活开关,FALSE:未激活;TRUE:激活 */

}CDS_ENTITY_STRU;


/*****************************************************************************
 结构名    : CDS_RX_DL_SDU_DATA_IND_STRU
 协议表格  : 定义CDS钩收到的下行SDU消息包。
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /* 消息头 */
    VOS_UINT16                              usMsgName;          /* 消息类型 */
    VOS_UINT8                               ucRbId;             /* Rb Id*/
    VOS_UINT8                               aucReserve1[1];     /* 4字节对齐，保留*/

    VOS_UINT8                               ucPduType;
    VOS_UINT8                               ucPdcpPid;
    VOS_UINT16                              usPdcpSn;
    VOS_UINT32                              ulDataLen;
    VOS_UINT8                               aucData[4];
} CDS_RX_SDU_DATA_IND_STRU;

extern CDS_ENTITY_STRU   g_astCdsEntity[];


/*设置定时器时长*/
#define CDS_SET_TMR_LEN(pstCdsEntity,ulTmrId,TmrLen)          ((pstCdsEntity)->astTimer[ulTmrId].ulTmrLen = (TmrLen))
#define CDS_GET_TMR_LEN(pstCdsEntity,ulTmrId)                 ((pstCdsEntity)->astTimer[ulTmrId].ulTmrLen)

/*设置GU RAB SR状态*/
/*lint -emacro({701}, CDS_SET_GU_RAB_SR_FLG)*/
#define CDS_SET_GU_RAB_SR_FLG(pstCdsEntity,ucRabId)         (((pstCdsEntity)->usGuRabSRStatus) |= (VOS_UINT16)(1 << ((ucRabId)-1)))
#define CDS_CLR_GU_RAB_SR_FLG(pstCdsEntity,ucRabId)         (((pstCdsEntity)->usGuRabSRStatus) &= (~(VOS_UINT16)(1 << ((ucRabId)-1))))
#define CDS_CLR_GU_ALL_RAB_SR_FLG(pstCdsEntity)             ((pstCdsEntity)->usGuRabSRStatus = 0)
/*lint -emacro({701}, CDS_GET_GU_RAB_SR_FLG)*/
#define CDS_GET_GU_RAB_SR_FLG(pstCdsEntity,ucRabId)         ((((pstCdsEntity)->usGuRabSRStatus) & (1 << ((ucRabId)-1))) >> ((ucRabId)-1))
/*lint -emacro({701}, CDS_SET_CDMA_RAB_SR_FLG)*/
#define CDS_SET_CDMA_RAB_SR_FLG(pstCdsEntity,ucRabId)         (((pstCdsEntity)->usCDMARabSRStatus) |= (VOS_UINT16)(1 << ((ucRabId)-1)))
/*lint -emacro({701}, CDS_CLR_CDMA_RAB_SR_FLG)*/
#define CDS_CLR_CDMA_RAB_SR_FLG(pstCdsEntity,ucRabId)         (((pstCdsEntity)->usCDMARabSRStatus) &= (~(VOS_UINT16)(1 << ((ucRabId)-1))))
/*lint -emacro({701}, CDS_CLR_CDMA_ALL_RAB_SR_FLG)*/
#define CDS_CLR_CDMA_ALL_RAB_SR_FLG(pstCdsEntity)             ((pstCdsEntity)->usCDMARabSRStatus = 0)
/*lint -emacro({701}, CDS_GET_CDMA_RAB_SR_FLG)*/
#define CDS_GET_CDMA_RAB_SR_FLG(pstCdsEntity,ucRabId)         ((((pstCdsEntity)->usCDMARabSRStatus) & (1 << ((ucRabId)-1))) >> ((ucRabId)-1))


#define CDS_SET_VOICEPREFER_ACT_FLAG(pstCdsEntity,ulActFlag)          (((pstCdsEntity)->ulVoicePreferActFlag) = (ulActFlag))
#define CDS_GET_VOICEPREFER_ACT_FLAG(pstCdsEntity)                    ((pstCdsEntity)->ulVoicePreferActFlag)
/*****************************************************************************
  6 UNION定义
*****************************************************************************/


/*****************************************************************************
  7 全局变量声明
*****************************************************************************/


/*****************************************************************************
  8 函数声明
*****************************************************************************/

extern VOS_VOID   CDS_SendEventToCds(VOS_UINT32 ulEvent);
extern VOS_VOID   CDS_LoopBackModeBTimeoutProc(const REL_TIMER_MSG  *pstTmrMsg);
extern CDS_ENTITY_STRU* CDS_GetCdsEntity(MODEM_ID_ENUM_UINT16 enModemId);
extern VOS_UINT32 CDS_StartTimer(CDS_ENTITY_STRU  *pstCdsEntity, VOS_UINT32 ulTmrId);
extern VOS_VOID   CDS_StopTimer(CDS_ENTITY_STRU  *pstCdsEntity, VOS_UINT32 ulTmrId);
extern VOS_VOID   CDS_RxLoopBackPkt(CDS_LB_DL_SDU_STRU *pstDlData, CDS_ENTITY_STRU *pstCdsEntity);
extern VOS_VOID   CDS_ClearLoopBackQue(const CDS_ENTITY_STRU *pstCdsEntity);
extern VOS_VOID   CDS_LoopBackModeBTimeoutProc(const REL_TIMER_MSG  *pstTmrMsg);
extern VOS_VOID   CDS_Dl10msPeridicTmrTimeoutProc(const REL_TIMER_MSG  *pstTmrMsg);
extern VOS_VOID   CDS_UlDataProtectTmrTimeoutProc(const REL_TIMER_MSG  *pstTmrMsg);
extern VOS_VOID   CDS_DLDataFlowStats(VOS_UINT8 ucBearerId, VOS_UINT32 ulPktLen, const CDS_ENTITY_STRU *pstCdsEntity);
extern VOS_VOID   CDS_ULDataFlowStats(VOS_UINT8 ucBearerId, VOS_UINT32 ulPktLen, const CDS_ENTITY_STRU *pstCdsEntity);
extern VOS_VOID   CDS_AllocMemForAdq(VOS_VOID);

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

