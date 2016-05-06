/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : Rabmdef.h
  Description : RABM宏定义
  History     :
      1.  张志勇       2003-07-25: The first version
      2.  l47619   2005-10-21  Modify for V200R001
*******************************************************************************/
#ifndef _RABM_DEF_H_
#define _RABM_DEF_H_

/* Determine if a C++ compiler is being used.  If so, ensure that standard
   C is used to process the API information.  */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define RABM_FALSE   0
#define RABM_TRUE    1

#define RABM_NSAPI_OFFSET    5

/* RABM实体的状态 */
#define RABM_NULL                       0
#define RABM_NSAPI_ACTIVE_PENDING       1
#define RABM_NSAPI_ACTIVE_NO_RAB        2
#define RABM_NSAPI_ACTIVE_WITH_RAB      3
#define RABM_DATA_TRANSFER_STOP         4
#define RABM_ACT_PENDING_WITH_RAB       5

#define RABM_SI_ACTIVE_WITH_RAB         1

/* TIMER */
#define RABM_TIMER_INVALID              0xffffffff

/* 指针 */
#define RABM_POINTER_NULL               0


/* CN DOMAIN */
#define RABM_CN_CS                      RRC_NAS_CS_DOMAIN
#define RABM_CN_PS                      RRC_NAS_PS_DOMAIN



/* TRAFFIC CLASS */
#define RABM_CONVERSATION_CLASS   0x20
#define RABM_STREAM_CLASS         0x40

/* ERROR SDU DELIVERY */
#define RABM_ERROR_SDU_DELIVERY_NO_DET    1

/* TC STATE */
#define RABM_TC_STATE_NULL              6
#define RABM_TC_STATE_WITH_RAB          7

/* 上下行数据区分 */
#define RABM_DOWNLINK   0
#define RABM_UPLINK        1

#define Rabm_TASK_NOT_START         0                   /*TASK Rabm 没有启动*/
#define Rabm_TASK_START             1                   /*TASK Rabm 已经启动*/

/* 重建RAB过程中RABM所处的暂态，用于标识这些暂态中所启的定时器 */
#define RABM_REESTABLISH_REQ_SENT       0      /* RABM已经发送了REESTABLISH_REQ请求消息，处于等待REESTABLISH_CNF响应消息的状态 */
#define RABM_REESTABLISH_RAB_PENDING    1      /* RABM已经收到了REESTABLISH_CNF响应消息，处于等待RAB重建的状态 */

#define NAS_RABM_INVALID_RAB_ID         (0xFF)

#define NAS_RABM_QOS_TRAFFIC_CLASS_MASK                     (0xE0)    /* 1110 0000*/
#define NAS_RABM_QOS_TRAFFIC_CLASS_BIT_OFFSET               (5)       /* Traffic Class参数在该字节的位偏移位 */
#define NAS_RABM_QOS_TRAFFIC_CLASS_BYTE_OFFSET              (3)       /* Traffic Class参数在QOS字节流中的位置 */

#define NAS_RABM_QOS_TRANSFER_DELAY_MASK                    (0xFC)    /* 1111 1100*/
#define NAS_RABM_QOS_TRANSFER_DELAY_BIT_OFFSET              (2)       /* Transfer Delay参数在该字节的位偏移位 */
#define NAS_RABM_QOS_TRANSFER_DELAY_BYTE_OFFSET             (8)       /* Transfer Delay参数在QOS字节流中的位置 */

#define NAS_RABM_QOS_TRAFFIC_HANDLING_PRIORITY_MASK         (0x03)    /* 0000 0011 */
#define NAS_RABM_QOS_TRAFFIC_HANDLING_PRIORITY_BYTE_OFFSET  (8)       /* Traffic Handling Priority 参数在QOS字节流中的位置 */

#define NAS_RABM_QOS_SRC_STATS_DESCRIPTOR_MASK              (0x0F)    /* 0000 1111*/
#define NAS_RABM_QOS_SRC_STATS_DESCRIPTOR_BYTE_OFFSET       (11)      /* SSD 参数在QOS字节流中的位置 */

#define NAS_RABM_QOS_SIGNAL_IND_MASK                        (0x10)    /* 0001 0000*/
#define NAS_RABM_QOS_SIGNAL_IND_BIT_OFFSET                  (4)       /* Signalling-Indication 参数在该字节的位偏移位 */
#define NAS_RABM_QOS_SIGNAL_IND_BYTE_OFFSET                 (11)      /* Signalling-Indication 参数在QOS字节流中的位置 */

/* QOS_TRAFFIC_CLASS */
#define NAS_RABM_QOS_TRAFFIC_CLASS_SUBSCRIBE                (0)
#define NAS_RABM_QOS_TRAFFIC_CLASS_CONVERSATIONAL           (1)
#define NAS_RABM_QOS_TRAFFIC_CLASS_STREAMING                (2)
#define NAS_RABM_QOS_TRAFFIC_CLASS_INTERACTIVE              (3)
#define NAS_RABM_QOS_TRAFFIC_CLASS_BACKGROUND               (4)

/* QOS_QOS_TRAFFIC_HANDLING */
#define NAS_RABM_QOS_TRAFFIC_HANDLING_PRIORITY_1            (1)
#define NAS_RABM_QOS_TRAFFIC_HANDLING_PRIORITY_2            (2)
#define NAS_RABM_QOS_TRAFFIC_HANDLING_PRIORITY_3            (3)

/* QOS_SRC_STATISTICS_DESCRIPTOR */
#define NAS_RABM_QOS_SRC_STATS_DESCRIPTOR_UNKNOWN           (0)
#define NAS_RABM_QOS_SRC_STATS_DESCRIPTOR_SPEECH            (1)

/* QOS_TRANSFER_DELAY */
#define NAS_RABM_QOS_TRANSFER_DELAY_150MS                   (0X0F)

/* QOS_SIGNAL_IND */
#define NAS_RABM_QOS_SIGNAL_IND_NOT_OPTIMISE                (0)
#define NAS_RABM_QOS_SIGNAL_IND_OPTIMISE                    (1)


#define NAS_RABM_QOS_DELIVERY_ERRORNEOUS_SDU_MASK           (0x07)

#define   D_RMC_RR_ACTION_SETUP         0
#define   D_RMC_RR_ACTION_RECFG         1
#define   D_RMC_RR_ACTION_RELEASE       2

typedef enum
{
    RABM_TIMER_NAME_NSAPI_5 = 0,
    RABM_TIMER_NAME_NSAPI_6,
    RABM_TIMER_NAME_NSAPI_7,
    RABM_TIMER_NAME_NSAPI_8,
    RABM_TIMER_NAME_NSAPI_9,
    RABM_TIMER_NAME_NSAPI_10,
    RABM_TIMER_NAME_NSAPI_11,
    RABM_TIMER_NAME_NSAPI_12,
    RABM_TIMER_NAME_NSAPI_13,
    RABM_TIMER_NAME_NSAPI_14,
    RABM_TIMER_NAME_NSAPI_15,
    RABM_TIMER_NAME_COMMON,
    RABM_TIMER_NAME_FD_RETRY,

    RABM_TIMER_NAME_FD_FLUX_DETECT,

    RABM_TIMER_NAME_BUTT
}RABM_TIMER_NAME_ENUM;     /*RABM定时器对应的NSAPI，用于设置定时器时的name字段*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif/* __cpluscplus */

#endif
