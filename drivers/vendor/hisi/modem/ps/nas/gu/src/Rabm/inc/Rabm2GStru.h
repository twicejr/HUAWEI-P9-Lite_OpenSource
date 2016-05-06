/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : Rabm2GStru.h
  Author      : l47619
  Version     : V200R001
  Date        : 2005-08-20
  Description : 该头文件定义了RABM模块所用的数据结构
  History     :
  1. Date:2005-08-20
     Author: l47619
     Modification:Create
  2.日    期   : 2006年08月09日
    作    者   : 蒋丽萍j60010247
    修改内容   : 问题单A32D03479，在PC机上实现时将#pragma pack(0)和#pragma pack()加编译开关
  3. Date:2006-06-26
     Author: l47619
     Modification:根据问题单修改: A32D05709
************************************************************************/

#ifndef __RABM_2G_STRU_H__
#define __RABM_2G_STRU_H__


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"

#include "rabmstru.h"
#include "NasGmmInterface.h"

#include "TafAppRabm.h"
#include "RabmInterface.h"

#include "TTFMem.h"
#include "NasPdcpInterface.h"

#include "rabmdef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define RABM_2G_MAX_ENT_NUM             11                        /*2G中RABM实体最大个数*/
#define RABM_3G_PS_MAX_ENT_NUM          11                        /*3G中RABM实体最大个数*/

#define RABM_MIN_NSAPI_NUMBER           5                         /*NSAPI所对应的最小号*/
#define RABM_MAX_NSAPI_NUMBER           15                        /*NSAPI所对应的最大号*/

#define RABM_2G_NSAPI_OFFSET            5                         /*2G中RABM实体数组下标与NSAPI的差值*/

#define RABM_SUCCESS                    0                         /*RABM模块函数返回成功*/
#define RABM_FAILURE                    1                         /*RABM模块函数返回失败*/
#define RABM_MSGILLOGIC                 2                         /*不合逻辑的消息*/
#define RABM_PARAILLEGAL                3                         /*入口参数非法*/
#define RABM_MSGWRONG                   4                         /*消息的内容出错*/
#define RABM_STATEWRONG                 5                         /*NSAPI对应的状态字段出错*/

#define RABM_YES                        0                         /*存在*/
#define RABM_NO                         1                         /*不存在*/

#define RABM_COMMON_TIMER_NUMBER        13                         /*所使用的公共定时器的个数*/

#define RABM_LONG_REPRESENT_MAX         0xFFFFFFFF                /*一个无符号的long型变量所能表示的最大数值:2^32-1*/

#define RABM_N_PDU_OFFSET               2                         /*N-PDU 码流中VALUE在数组中的索引偏移*/

#define RABM_SUBMOD_NULL                0                         /* 无子模块 */
#define RABM_LOG_INFO( String )         PS_NAS_LOG( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_INFO, String )
#define RABM_LOG_NORMAL( String )       PS_NAS_LOG( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_NORMAL, String )
#define RABM_LOG_WARNING( String )      PS_NAS_LOG( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_WARNING, String )
#define RABM_LOG_ERROR( String )        PS_NAS_LOG( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_ERROR, String )

#define RABM_LOG1_INFO( String, Para1 )        PS_NAS_LOG1( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_INFO, String, Para1 )
#define RABM_LOG1_NORMAL( String, Para1 )      PS_NAS_LOG1( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_NORMAL, String, Para1 )
#define RABM_LOG1_WARNING( String, Para1 )     PS_NAS_LOG1( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_WARNING, String, Para1 )
#define RABM_LOG1_ERROR( String, Para1 )       PS_NAS_LOG1( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_ERROR, String, Para1 )

#define RABM_LOG2_INFO( String, Para1, Para2 )        PS_NAS_LOG2( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_INFO, String, Para1, Para2 )
#define RABM_LOG2_NORMAL( String, Para1, Para2 )      PS_NAS_LOG2( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_NORMAL, String, Para1, Para2 )
#define RABM_LOG2_WARNING( String, Para1, Para2 )     PS_NAS_LOG2( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_WARNING, String, Para1, Para2 )
#define RABM_LOG2_ERROR( String, Para1, Para2 )       PS_NAS_LOG2( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_ERROR, String, Para1, Para2 )

#define RABM_LOG3_INFO( String, Para1, Para2, Para3 )        PS_NAS_LOG3( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_INFO, String, Para1, Para2, Para3 )
#define RABM_LOG3_NORMAL( String, Para1, Para2, Para3 )      PS_NAS_LOG3( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_NORMAL, String, Para1, Para2, Para3 )
#define RABM_LOG3_WARNING( String, Para1, Para2, Para3 )     PS_NAS_LOG3( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_WARNING, String, Para1, Para2, Para3 )
#define RABM_LOG3_ERROR( String, Para1, Para2, Para3 )       PS_NAS_LOG3( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_ERROR, String, Para1, Para2, Para3 )

#define RABM_LOG4_INFO( String, Para1, Para2, Para3, Para4 )        PS_NAS_LOG4( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_INFO, String, Para1, Para2, Para3, Para4 )
#define RABM_LOG4_NORMAL( String, Para1, Para2, Para3, Para4 )      PS_NAS_LOG4( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_NORMAL, String, Para1, Para2, Para3, Para4 )
#define RABM_LOG4_WARNING( String, Para1, Para2, Para3, Para4 )     PS_NAS_LOG4( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_WARNING, String, Para1, Para2, Para3, Para4 )
#define RABM_LOG4_ERROR( String, Para1, Para2, Para3, Para4 )       PS_NAS_LOG4( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_ERROR, String, Para1, Para2, Para3, Para4 )



/* ======================= */   /* RAB映射实体改变掩码 */
#define RAB_MAP_CHG_MASK_AS_ID          0x01
#define RAB_MAP_CHG_MASK_DL_CALLBACK    0x02
#define RAB_MAP_CHG_MASK_UL_CALLBACK    0x04

/* ======================= */   /* 无效ID定义 */
#define RAB_MAP_INVALID_RAB_ID          0xff
#define RAB_MAP_INVALID_AS_ID           0xff


/* RabId值，范围为:[5,15] */
#define RAB_MAP_RAB_IS_VALID(ucRabId)   \
    ( (RABM_MIN_NSAPI_NUMBER <= (ucRabId)) && (RABM_MAX_NSAPI_NUMBER >= (ucRabId)) )

/* AsId值，W范围为:[5,32], G范围为[5,15]，这里取W的值 */
#define RAB_MAP_ASID_IS_VALID(ucAsId)     \
    ( (NAS_MML_NET_RAT_TYPE_GSM == NAS_RABM_GetCurrentSysMode()) ? \
      ( (RABM_MIN_NSAPI_NUMBER <= (ucAsId)) && (RABM_MAX_NSAPI_NUMBER >= (ucAsId)) ) :\
      ( (PS_WUE_MIN_T_RB_ID <= (ucAsId)) && (PS_WUE_MAX_RB_ID >= (ucAsId)) ) )

/*******************************************************************************
  3 枚举定义
*******************************************************************************/
typedef enum
{
    /*公共定时器类型*/
    RABM_TIMER_PARA_ROUT_AREA_UPDATE_T1 = 0,
    RABM_TIMER_PARA_3_TO_2_T3,

    /*实体定时器类型*/
    RABM_TIMER_PARA_ACT_REQ_T1,

    /* 重建RAB时使用的定时器 */
    RABM_TIMER_PARA_REESTRAB_TIMER,

    RABM_TIMER_FASTDORM_FLUX_DETECT,                                            /* 周期性流量检测定时器，超时后检查是否有流量变化 */
    RABM_TIMER_FASTDORM_RETRY,                                                  /* RETRY定时器，超时后重新尝试FD */
    RABM_TIMER_FASTDORM_WAIT_GMM_QRY_RESULT,                                    /* 查询GMM当前信令业务状态保护定时器，超时后停止 */

    RABM_TIMER_RESEND_EST_REQ,

    RABM_TIMER_RAB_REESTABLISH_PENDING,

    RABM_TIMER_VOICEPREFER_DELAY,
    RABM_TIMER_VOICEPREFER_REQRY_GMM_DELAY,

    RABM_TIMER_PARA_BUTT
}RABM_TIMER_PARA_ENUM;     /*RABM定时器的名字，用于设置定时器时的para字段*/


typedef enum
{
    RABM_NSAPI_5  = 0,
    RABM_NSAPI_6 ,
    RABM_NSAPI_7 ,
    RABM_NSAPI_8 ,
    RABM_NSAPI_9 ,
    RABM_NSAPI_10 ,
    RABM_NSAPI_11 ,
    RABM_NSAPI_12 ,
    RABM_NSAPI_13 ,
    RABM_NSAPI_14 ,
    RABM_NSAPI_15 ,

    RABM_NSAPI_BUTT
}RABM_NSAPI_ENUM;             /*每个NSAPI所对应的数组索引*/


typedef enum
{
    RABM_2G_NULL = 0,
    RABM_NSAPI_OK_TRANSMODE_NO,
    RABM_DATA_TRANS_READY,
    RABM_ROUT_AREA_UPDATE,
    RABM_DATA_TRANS_STOP,

    RABM_STATE_BUTT
}RABM_2G_STATE_ENUM;        /*2G中RABM实体的状态*/

typedef enum
{
    RABM_2G_TO_3G_SWITCH_ON = 0,
    RABM_2G_TO_3G_SWITCH_OFF,

    RABM_2G_TO_3G_SWITCH_BUTT
}RABM_2G_TO_3G_SWITCH_ENUM;  /*标识当前是否正在进行2G到3G的切换*/

typedef enum
{
    RABM_3G_TO_2G_SWITCH_ON = 0,
    RABM_3G_TO_2G_SWITCH_OFF,

    RABM_3G_TO_2G_SWITCH_BUTT
}RABM_3G_TO_2G_SWITCH_ENUM;  /*标识当前是否正在进行3G到2G的切换*/

enum RABM_RA_T1_SWITCH_ENUM
{
    RABM_ROUTING_AREA_UPDATE_T1_ON = 0,
    RABM_ROUTING_AREA_UPDATE_T1_OFF,

    RABM_ROUTING_AREA_UPDATE_T1_BUTT
};/*标识2G中路由区更新定时器是否启动*/

typedef VOS_UINT8 RABM_RA_T1_SWITCH_ENUM_UINT8;

enum RABM_ACT_REQ_T1_SWITCH_ENUM
{
    RABM_ACT_REQ_T1_ON = 0,
    RABM_ACT_REQ_T1_OFF,

    RABM_ACT_REQ_T1_BUTT
}; /*标识Rabm.Act.Req.T1定时器是否启动*/

typedef VOS_UINT8  RABM_ACT_REQ_T1_SWITCH_ENUM_UINT8;

typedef enum
{
    RABM_2G_TO_3G_T1_ON = 0,
    RABM_2G_TO_3G_T1_OFF,

    RABM_2G_TO_3G_T1_BUTT
}RABM_2G_TO_3G_T1_SWITCH_ENUM;/*标识Rabm.2To3.T1定时器是否启动*/

typedef enum
{
    RABM_3G_TO_2G_T1_ON = 0,
    RABM_3G_TO_2G_T1_OFF,

    RABM_3G_TO_2G_T1_BUTT
}RABM_3G_TO_2G_T1_SWITCH_ENUM;/*标识Rabm.3To2.T1定时器是否启动*/

enum RABM_3G_TO_2G_T3_SWITCH_ENUM
{
    RABM_3G_TO_2G_T3_ON = 0,
    RABM_3G_TO_2G_T3_OFF,

    RABM_3G_TO_2G_T3_BUTT
};/*标识Rabm.3To2.T3定时器是否启动*/

typedef VOS_UINT8  RABM_3G_TO_2G_T3_SWITCH_ENUM_UINT8;

typedef enum
{
    RABM_3G_TO_2G_RA_UPDATE_ON = 0,
    RABM_3G_TO_2G_RA_UPDATE_OFF,

    RABM_3G_TO_2G_RA_UPDATE_BUTT
}RABM_3G_TO_2G_RA_UPDATE_SWITCH_ENUM;/*标识Rabm.3To2.RA.Update定时器是否启动*/

typedef enum
{
    RABM_NSAPI_ACTIVE_SWITCH_ON = 0,
    RABM_NSAPI_ACTIVE_SWITCH_OFF,

    RABM_NSAPI_ACTIVE_SWITCH_BUTT
}RABM_NSAPI_ACTIVE_SWITCH_ENUM;               /*标识某NSAPI是否激活了*/

typedef enum
{
    RABM_FLUX_REPORT_SWITCH_ON = 0,
    RABM_FLUX_REPORT_SWITCH_OFF,

    RABM_FLUX_REPORT_SWITCH_BUTT
}RABM_FLUX_REPORT_SWITCH_ENUM;               /*标识是否上报流量*/

typedef enum
{
    RABM_FLUX_REPORT_TIMER_SWITCH_ON = 0,
    RABM_FLUX_REPORT_TIMER_SWITCH_OFF,

    RABM_FLUX_REPORT_TIMER_BUTT
}RABM_FLUX_REPORT_TIMER_SWITCH_ENUM;      /*标识流量上报定时器是否启动*/

enum RABM_FLUX_WRITE_NV_TIMER_SWITCH_ENUM
{
    RABM_FLUX_WRITE_NV_TIMER_SWITCH_ON = 0,
    RABM_FLUX_WRITE_NV_TIMER_SWITCH_OFF,

    RABM_FLUX_WRITE_NV_TIMER_BUTT
};      /*标识流量上报定时器是否启动*/

typedef VOS_UINT32       RABM_FLUX_WRITE_NV_TIMER_SWITCH_ENUM_U32;

typedef enum
{
    RABM_FLUX_WRITE_NV = 0,
    RABM_FLUX_CLEAR_NV,

    RABM_FLUX_BUTT
}RABM_FLOW_NV_OPT_ENUM;

/*****************************************************************************
 枚举名    : NAS_RABM_TIMER_STATUS_ENUM
 结构说明  : RABM定时器状态,停止或运行
  1.日    期   : 2011年10月28日
    作    者   : h44270
    修改内容   : 新建
*****************************************************************************/
enum NAS_RABM_TIMER_STATUS_ENUM
{
    NAS_RABM_TIMER_STATUS_RUNING,            /* 定时器运行状态 */
    NAS_RABM_TIMER_STATUS_STOP,              /* 定时器停止状态 */
    NAS_RABM_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 NAS_RABM_TIMER_STATUS_ENUM_UINT8;



typedef enum
{
    RABM_GPRS_SYS_INFO_SWITCH_ON = 0,
    RABM_GPRS_SYS_INFO_SWITCH_OFF,

    RABM_GPRS_SYS_INFO_TIMER_BUTT
}RABM_GPRS_SYS_INFO_SWITCH_ENUM;             /*标识3G切入2G，等待GPRS支持能力消息的定时器是否启动*/

typedef enum
{
    RABM_TRANSMODE_LEGAL = 0,
    RABM_TRANSMODE_ILLEGAL,

    RABM_TRANSMODE_ILLEGAL_BUTT
}RABM_TRANSMODE_LEGITIMACY_ENUM;            /*设置传输模式时的入口参数中的TRANSMODE字段是否合法的标记*/


typedef enum
{
    RABM_RA_UPDATE_CAUSE_NORMAL = 0,
    RABM_RA_UPDATE_CAUSE_3G_TO_2G,

    RABM_RA_UPDATE_CAUSE_BUTT
}RABM_RA_UPDATE_CAUSE_ENUM;                   /*2G中发生路由区更新的原因*/

typedef enum
{
    RABM_CALCULATE_TIME_SUCCESS = 0,
    RABM_CALCULATE_TIME_FAIL,

    RABM_CALCULATE_TIME_BUTT
}RABM_CALCULATE_TIME_ENUM;                      /*计算时间成功与否的标志*/

typedef enum
{
    RABM_GET_CUR_NET_FIRSTTIME_ON = 0,
    RABM_GET_CUR_NET_FIRSTTIME_OFF,

    RABM_GET_CUR_NET_FIRSTTIME_BUTT
}RABM_GET_CUR_NET_FIRSTTIME_ENUM;            /*标识第一次获取网络是否完成*/

typedef enum
{
    RABM_FLOW_RPT_CTRL_ENABLE = 0,
    RABM_FLOW_RPT_CTRL_DISABLE,

    RABM_FLOW_RPT_CTRL_BUTT
}RABM_FLOW_RPT_CTRL_ENUM;                      /*流量自动上报特性的使能与否*/

/*****************************************************************************
 枚举名  : RNIC_MNTN_EVENT_TYPE_ENUM
 枚举说明: RNIC可维可测事件原语
*****************************************************************************/
enum NAS_RABM_MNTN_EVT_TYPE_ENUM
{
    ID_NAS_RABM_MNTN_EVT_UL_PKT_LOST    = 0x2001,
    ID_NAS_RABM_MNTN_EVT_DL_PKT_LOST    = 0x2002,
    ID_NAS_RABM_MNTN_EVT_BUTT
};
typedef VOS_UINT32 NAS_RABM_MNTN_EVT_TYPE_ENUM_UINT32;


/*****************************************************************************
 枚举名  : RNIC_MNTN_EVENT_TYPE_ENUM
 枚举说明: RNIC可维可测事件原语
*****************************************************************************/
enum NAS_RABM_PKT_FLOW_DIR_ENUM
{
    NAS_RABM_PKT_FLOW_DIR_UPLINK        = 0x00,
    NAS_RABM_PKT_FLOW_DIR_DOWNLINK      = 0x01
};
typedef VOS_UINT8 NAS_RABM_PKT_FLOW_DIR_ENUM_UINT8;



/*****************************************************************************
  5 消息头定义

模块名＋意义＋HEADER
#define MAPS_TEMPLATE_HEADER    VOS_UINT16    usTotalsMsgLen;\
                                                      VOS_UINT32    ulSendModuleId;\
                                                      VOS_UINT32    ulRecvModuleId;\
*****************************************************************************/

/*****************************************************************************
  6 消息定义

typedef struct
{
    MAPS_TEMPLATE_HEADER
    VOS_UINT8    aucData[2];     消息体

} MAPS_TEMPLATE_MSG;
*****************************************************************************/

/*****************************************************************************
  7 STRUCT定义
******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNsapi;
    RABM_2G_STATE_ENUM                  State;              /*本实体的状态*/
    RABM_TRANS_MODE_ENUM                TransMode;          /*传输模式*/
    RABM_QOS_STRU                       stQos;              /*本实体对应的QoS*/
    RABM_RA_UPDATE_CAUSE_ENUM           RAUpdateCause;      /*2G中路由区更新发生的原因*/
    VOS_UINT8                           ucPppFlg;           /*标识是否支持PPP，0：支持；1:不支持*/
}RABM_2G_ENTITY_ST;                                 /*RABM的状态机实体*/


typedef struct
{
    HTIMER                             *pstHTimer;
    VOS_UINT32                          ulPid;                                  /*PID的数据类型留待考虑*/
    VOS_UINT32                          ulLength;
    RABM_TIMER_NAME_ENUM                Name;
    RABM_TIMER_PARA_ENUM                Param;
    VOS_UINT8                           ucMode;

}RABM_START_TIMER_ST;              /*启动定时器时使用的数据结构*/


/* 数据发送接口 */
typedef VOS_UINT32 (*RAB_UL_DATA_CALLBACK)(VOS_UINT8 ucRabId, VOS_UINT8 ucRbId, TTF_MEM_ST *pstData);
typedef VOS_UINT32 (*RAB_DL_DATA_CALLBACK)(VOS_UINT8 ucRabId, TTF_MEM_ST *pstData);


/* ======================== */    /* RAB映射实体数据结构 */
/* 两点注意事项
   1.RAB是W下的概念，为保持统一，G下沿用这个概念，指NSAPI
   2.G下没有RB，为保持统一，可以在G模下虚拟出RAB和RB，但是都是指NSAPI
*/
/* RAB映射实体 */
typedef struct
{
    PS_BOOL_ENUM_UINT8      enucExistInd;       /* 该RAB链接的状态 */
    VOS_UINT8               ucRabId;            /* W下是RAB ID [5,15]，G下是NSAPI[5,15] */
    VOS_UINT8               ucLinkdRabId;       /* W下是RAB ID [5,15]，G下是NSAPI[5,15] */
    VOS_UINT8               ucAsId;             /* 接入层ID，W下RB存在是RB ID[5, 32]，
                                                   RB不存在是RAB Data Buffer ID,等于RAB_ID[5, 15]，
                                                   G下是NSAPI[5, 15]*/
    RAB_UL_DATA_CALLBACK    pUlDataCallBack;    /* 上行数据发送接口 */
    RAB_DL_DATA_CALLBACK    pDlDataCallBack;    /* 下行数据分发接口 */
} RAB_MAP_STRU;


/* ======================== */    /* RAB映射实体对应的接入层上行发送回调函数 */
typedef struct
{
    VOS_UINT8               ucMode;             /* 网络模式，W or G */
    VOS_UINT8               ucState;            /* RAB或NSAPI的状态 */
    VOS_UINT16              usRsv;
    RAB_UL_DATA_CALLBACK    pAsUlDataCallBack;  /* 接入层回调函数指针 */
} RAB_AS_UL_DATA_CALLBACK_STRU;


enum RAB_UL_CB_NAME_ENUM
{
    RAB_UL_CB_NAME_NULL             = 0,
    RAB_UL_CB_NAME_SND_RABM,
    RAB_UL_CB_NAME_SND_PDCP,
    RAB_UL_CB_NAME_SND_SNDCP,
    RAB_UL_CB_NAME_BUTT
};
typedef VOS_UINT16 RAB_UL_CB_NAME_ENUM_UINT16;

enum RAB_DL_CB_NAME_ENUM
{
    RAB_DL_CB_NAME_NULL          = 0,
    RAB_DL_CB_NAME_DEFAULT,
    RAB_DL_CB_NAME_APP_REG,
    RAB_DL_CB_NAME_BUTT
};
typedef VOS_UINT16 RAB_DL_CB_NAME_ENUM_UINT16;

#define RABM_TRACE_RAB_MAP_INFO_MSG     0xBA03;

typedef struct
{
    VOS_MSG_HEADER                                      /* 消息头 */        /* _H2ASN_Skip */
    VOS_UINT32                      ulMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    PS_BOOL_ENUM_UINT8              enucExistInd;
    VOS_UINT8                       ucRabId;
    VOS_UINT8                       ucAsId;
    VOS_UINT8                       aucRsv[1];
    RAB_UL_CB_NAME_ENUM_UINT16      enUlCbName;
    RAB_DL_CB_NAME_ENUM_UINT16      enDlCbName;
} RABM_TRACE_RAB_MAP_INFO_STRU;

#define EVT_NAS_RABM_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY   0xaaaa          /* 为PC工程回放定义的消息 */

/*****************************************************************************
 Structure      : NAS_RABM_OUTSIDE_RUNNING_CONTEXT_ST
 Description    : PC回放工程，存储所有RABM相关的全局变量
 Message origin :
*****************************************************************************/

typedef struct
{
    RABM_3G_TO_2G_SWITCH_ENUM      pc_gRabm3GTo2GSwitch;
    RABM_3G_TO_2G_T1_SWITCH_ENUM   pc_gRabm3GTo2GT1Switch;
    VOS_UINT32                     pc_gRabm2GTo3GDataResume;

    VOS_UINT8               pc_g_ucReestTimerFlg;                                                 /* RABM_TRUE:重建TIMER有效；RABM_FALSE:无效 */
    VOS_UINT8               pc_g_aucSiMapEnt[256];                                                /* SI和RABM实体的映射关系                   */
    RABM_ENTITY_PS_STRU     pc_g_aRabmPsEnt[RABM_PS_MAX_ENT_NUM];                       /* PS域RABM实体的全局量                     */
    RABM_ENTITY_CS_STRU     pc_g_aRabmCsEnt[RABM_CS_MAX_ENT_NUM];                       /* CS域RABM实体的全局量                     */
    RABM_TC_INF_STRU        pc_g_RabmTcInf;
} NAS_RABM_OUTSIDE_RUNNING_CONTEXT_ST;

/*****************************************************************************
 Structure      : NAS_RABM_OUTSIDE_RUNNING_CONTEXT_ST
 Description    : PC回放工程，所有RABM相关的全局变量通过以下消息结构发送
 Message origin :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                             usMsgID;
    VOS_UINT16                             usReserved;                            /* 在PACK(1)到PACK(4)调整中定义的保留字节 */
    NAS_RABM_OUTSIDE_RUNNING_CONTEXT_ST    stOutsideCtx;
}NAS_RABM_SDT_MSG_ST;

typedef struct
{
    VOS_UINT32                          ulDSLastLinkTime;
    VOS_UINT32                          ulDSTotalSendFluxLow;
    VOS_UINT32                          ulDSTotalSendFluxHigh;
    VOS_UINT32                          ulDSTotalLinkTime;
    VOS_UINT32                          ulDSTotalReceiveFluxLow;
    VOS_UINT32                          ulDSTotalReceiveFluxHigh;
}NAS_RABM_TOTAL_RX_BYTES_STRU;

/*****************************************************************************
 结构名  : NAS_RABM_MNTN_UL_PKT_LOST_STRU
 结构说明: RABM丢包点可维可测
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    NAS_RABM_MNTN_EVT_TYPE_ENUM_UINT32  enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    VOS_UINT8                           ucPoint;
    VOS_UINT8                           aucRsv[3];
} NAS_RABM_MNTN_PKT_LOST_STRU;


/*****************************************************************************
  4 全局变量声明

extern VOS_UINT8* pgucMapsTemplateBuffer;   指针＋全局标识＋类型＋模块名＋意义描述
*****************************************************************************/
/*2G中RABM实体的结构体数组 */
extern RABM_2G_ENTITY_ST                                    gastRabm2GEntity[RABM_2G_MAX_ENT_NUM];

/*用以记录3G中发生3G到2G切换时，在发生切换前所处的状态*/
extern VOS_UCHAR                                            gaucRabm3GPreState[RABM_3G_PS_MAX_ENT_NUM];

/*标识当前是否正在进行2G到3G的切换*/
extern RABM_2G_TO_3G_SWITCH_ENUM                            gRabm2GTo3GSwitch;

/*标识当前是否正在进行3G到2G的切换*/
extern RABM_3G_TO_2G_SWITCH_ENUM                            gRabm3GTo2GSwitch;

/*标识2G中路由区更新定时器是否启动*/
extern RABM_RA_T1_SWITCH_ENUM_UINT8                         gRabmRAT1Switch;

/*标识Rabm.Act.Req.T1定时器是否启动(以定时器的ulName作为索引)*/
extern RABM_ACT_REQ_T1_SWITCH_ENUM_UINT8                    gaRabmActReqT1Switch[RABM_2G_MAX_ENT_NUM];

/*标识Rabm.2To3.T1定时器是否启动*/
extern RABM_2G_TO_3G_T1_SWITCH_ENUM                         gRabm2GTo3GT1Switch;

/*标识Rabm.3To2.T1定时器是否启动*/
extern RABM_3G_TO_2G_T1_SWITCH_ENUM                         gRabm3GTo2GT1Switch;

/*标识Rabm.3To2.T3定时器是否启动*/
extern RABM_3G_TO_2G_T3_SWITCH_ENUM_UINT8                   gRabm3GTo2GT3Switch;

/*标识Rabm.3To2.RA.Update定时器是否启动*/
extern RABM_3G_TO_2G_RA_UPDATE_SWITCH_ENUM                  gRabm3GTo2GRAUpdateSwitch;

/*TLLI的全局变量*/
extern VOS_UINT32                                           gulRabmTLLI;

/*定时器时长数组(以定时器的PARA枚举作为索引)*/
extern VOS_UINT32                                           gaulRabmTimerLength[RABM_TIMER_PARA_BUTT];

/*实体定时器(以定时器的NAME枚举作为索引)*/
extern HTIMER                                               gastRabmEntityTimer[RABM_MAX_ENT_NUM];

/*公用定时器(以定时器的PARA枚举作为索引)*/
extern HTIMER                                               gastRabmCommonTimer[RABM_COMMON_TIMER_NUMBER];

/*标识第一次获取网络是否完成*/
extern RABM_GET_CUR_NET_FIRSTTIME_ENUM                      gRabmGetCurNetFirsttime;

/*标识当前所处的网络模式*/
extern RABM_CUR_NET_ENUM                                    gRabmCurNet;

/*2G向3G切换后，数传恢复的标志*/
extern VOS_UINT32                                           gRabm2GTo3GDataResume;

/*3G向2G切换时，RABM保存NSAPI和RB的映射关系*/
extern SNDCP_NSAPI_MAP_RB_INFO                              gastNsapiMapRb[SNDCP_RABM_MAX_NSAPI_NUM];

/*RABM从PDCP处获知的RCV NPDU NUM 信息*/
extern RABM_PDCP_GET_N_PDU_NUM_LIST_ST                      gPdcpRcvNpduNum;

extern GMM_RABM_NET_RAT_ENUM_UINT32     g_enNasRabmSysMode;
extern VOS_BOOL                         g_bNasRabmDataSuspendFlg;

extern NAS_RABM_TIMER_STATUS_ENUM_UINT8    g_ulNasRabmFDFluxDetectTimer;
extern NAS_RABM_TIMER_STATUS_ENUM_UINT8    g_ulNasRabmFDRetryTimer;
extern NAS_RABM_TIMER_STATUS_ENUM_UINT8    g_ulNasRabmFDWaitGmmQryRsltTimer;

extern NAS_RABM_TIMER_STATUS_ENUM_UINT8    g_ulNasRabmResendEstTimer;

extern RAB_MAP_STRU                     g_astRabMap[PS_WUE_MAX_RB_ID + 1];
extern VOS_UINT8                        g_aucRb2Rab[PS_WUE_MAX_RB_ID + 1];

#if (FEATURE_ON == FEATURE_LTE)
/* L->G标记, 用于标记L->G的流程 */
extern VOS_UINT32                       g_ulNasRabmL2GFlg;
#endif


/*****************************************************************************
  8 UNION定义

typedef union
{
    VOS_UINT8    ucTemplate;
    VOS_UINT8    aucData[2];

} MAPS_TEMPLATE_UNION;
*****************************************************************************/

/*****************************************************************************
  8 函数指针定义
*****************************************************************************/




#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of Rabm2GStru.h*/
