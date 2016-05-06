/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXccCtx.h
  版 本 号   : 初稿
  作    者   : Y00213812
  生成日期   : 2014年7月4日
  最近修改   :
  功能描述   : CnasXccCtx.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年7月4日
    作    者   : Y00213812
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CNAS_XCC_CTX_H__
#define __CNAS_XCC_CTX_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "NasFsm.h"
#include "cas_1x_access_ctrl_proc_nas_pif.h"
#include "xcc_xcall_pif.h"
#include "CnasXccComFunc.h"





#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* 状态机实例最大个数: voice call, sms, ps call , agps */
#define CNAS_XCC_MAX_FSM_ENTITY_NUM                         (4)

/* 状态机栈的深度 */
#define CNAS_XCC_MAX_FSM_STACK_DEPTH                        (4)

/* 缓存消息的最大长度 */
#define CNAS_XCC_MAX_MSG_BUFFER_LEN                         (1600)

/* 缓存内部消息队列的最大个数 */
#define CNAS_XCC_MAX_INT_MSG_QUEUE_NUM                      (8)

/* 缓存用户请求消息数目 */
#define CNAS_XCC_MAX_BUFFER_MSG_QUEUE_NUM                   (5)

/* QOS最大长度，与接入层CAS_CNAS_1X_QOS_MAX_LENGTH保持一致 */
#define CNAS_XCC_MAX_QOS_LENGTH                             (31)

#define CNAS_XCC_INVAILD_CON_ID                             (0xFF)

#define CNAS_XCC_INVAILD_CALL_ID                            (0)

#define CNAS_XCC_INVALID_CON_REF                            (0)

#define CNAS_XCC_MAX_UINT8                                  (255)

#define CNAS_XCC_OCTET_BIT_LEN                              (8)

/* If the service instance does not provide a service reference
identifier, the mobile station shall set this field to the
smallest unused service reference identifier value between 1
and 6 (inclusive). 根据这段协议，暂定SR_ID的最大个数应该是6 */
#define CNAS_XCC_MAX_SRID_NUM                               (6)

#define CNAS_XCC_INVALID_SR_ID                              (0)

/* 当前保留的SR_ID的情况 */
#define CNAS_XCC_RESERVED_SR_ID                             (1)

#define CNAS_XCC_MS_ACK_PARA_LEN                            (2)

#define CNAS_XCC_INVAILD_CALL_INDEX                         (0xFF)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : CNAS_XCC_FSM_ID_ENUM
 枚举说明  : 状态机ID枚举定义
 1.日    期   : 2014年07月04日
   作    者   : Y00213812
   修改内容   : 新建
*****************************************************************************/
enum CNAS_XCC_FSM_ID_ENUM
{
    /***********************************************************************
     * XCC L1状态机标识
     ***********************************************************************/
    /* CNAS XCC L1 main状态机的标识 */
    CNAS_XCC_FSM_L1_MAIN                                    =0x00,

    /***********************************************************************
     * XCC L2状态机的标识
     ***********************************************************************/
    /* XCC主叫L2状态机 */
    CNAS_XCC_FSM_MO_CALLING                                 =0x01,

    /* XCC被叫L2状态机 */
    CNAS_XCC_FSM_MT_CALLING                                 =0x02,


    CNAS_XCC_FSM_BUTT

};
typedef VOS_UINT32 CNAS_XCC_FSM_ID_ENUM_UINT32;

/*****************************************************************************
 枚举名    : CNAS_XCC_TX_ORDER_TYPE_ENUM
 枚举说明  : ORDER消息类型
 1.日    期   : 2014年9月15日
   作    者   : h00246512
   修改内容   : 新增
*****************************************************************************/
enum CNAS_XCC_TX_ORDER_TYPE_ENUM
{
    CNAS_XCC_TX_ORDER_TYPE_CONNECT_ORDER,                       /* Connect Order */
    CNAS_XCC_TX_ORDER_TYPE_CONTINUOUS_DTMF_TONE_START_ORDER,    /* Continuous DTMF Tone Start Order  */
    CNAS_XCC_TX_ORDER_TYPE_CONTINUOUS_DTMF_TONE_STOP_ORDER,     /* Continuous DTMF Tone Stop Order */
    CNAS_XCC_TX_ORDER_TYPE_MS_REJECT_ORDER,                     /* Mobile Station Reject Order */
    CNAS_XCC_TX_ORDER_TYPE_BUTT
};
typedef VOS_UINT8 CNAS_XCC_TX_ORDER_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_XCC_INIT_TYPE_ENUM
 枚举说明  : 初始化类型
 1.日    期   : 2014年9月15日
   作    者   : y00245242
   修改内容   : 新增
*****************************************************************************/
enum CNAS_XCC_INIT_TYPE_ENUM
{
    CNAS_XCC_INIT_TYPE_POWER_ON,                                /* 初始化类型为开机 */
    CNAS_XCC_INIT_TYPE_POWER_DOWN,                              /* 初始化类型为关机  */
    CNAS_XCC_INIT_TYPE_POWER_SAVE,                              /* 初始化类型为挂起  */

    CNAS_XCC_INIT_TYPE_BUTT
};
typedef VOS_UINT8 CNAS_XCC_INIT_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_XCC_INIT_CALLINFO_SCENE_ENUM
 枚举说明  : 初始化类型
 1.日    期   : 2014年9月20日
   作    者   : w00242748
   修改内容   : 新增
*****************************************************************************/
enum CNAS_XCC_INIT_CALLINFO_SCENE_ENUM
{
    CNAS_XCC_INIT_CALLINFO_SCENE_POWER_ON,                      /* 初始化类型为开机 */
    CNAS_XCC_INIT_CALLINFO_SCENE_ENDING,                        /* 初始化类型为L1 MAIN状态迁移到ENDING  */
    CNAS_XCC_INIT_CALLINFO_SCENE_ENDED,                         /* 初始化类型为L1 MAIN状态迁移到IDLE  */

    CNAS_XCC_INIT_CALLINFO_SCENE_BUTT
};
typedef VOS_UINT8  CNAS_XCC_INIT_CALLINFO_SCENE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_XCC_SERVICE_SUSPEND_FLG_ENUM
 结构说明  : 用于标记读取卡文件的回复消息
 1.日    期   : 2014年9月19日
   作    者   : h00246512
   修改内容   : 新增

*****************************************************************************/
enum   CNAS_XCC_SERVICE_SUSPEND_FLG_ENUM
{
    CNAS_XCC_SERVICE_SUSPEND_FLG_NULL                       = 0x00,

    CNAS_XCC_SERVICE_SUSPEND_FLG_XCALL                      = 0x01,

    CNAS_XCC_SERVICE_SUSPEND_FLG_SMS                        = 0x02,

    CNAS_XCC_SERVICE_SUSPEND_FLG_BUTT
};

typedef VOS_UINT8 CNAS_XCC_SERVICE_SUSPEND_FLG_ENUM_UINT8;

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
 结构名    : CNAS_XCC_ENTRY_MSG_STRU
 结构说明  : XCC消息结构，状态机保存的入口消息和CACHE消息都使用此结构
 1.日    期   : 2014年07月04日
   作    者   : Y00213812
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEventType;
    VOS_UINT8                           aucMsgBuffer[CNAS_XCC_MAX_MSG_BUFFER_LEN];
}CNAS_XCC_ENTRY_MSG_STRU;

/*****************************************************************************
结构名    : CNAS_XCC_BUFFER_MSG_QUEUE_STRU
结构说明  : 缓存的消息队列，
1.日    期   : 2014年09月15日
  作    者   : y00245242
  修改内容   : 新建
2.日    期   : 2015年09月08日
  作    者   : w00176964
  修改内容   : CNAS内存裁剪
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMsgNum;                                /* 缓存消息的个数 */
    VOS_UINT8                           aucReserve[3];
    VOS_UINT8                          *pastBufferMsg[CNAS_XCC_MAX_BUFFER_MSG_QUEUE_NUM]; /* 缓存用户的请求消息，根据业务类型缓存 */
}CNAS_XCC_BUFFER_MSG_QUEUE_STRU;

 /*****************************************************************************
 结构名    : CNAS_XCC_INT_MSG_QUEUE_STRU
 结构说明  : 缓存的消息队列
 1.日    期   : 2014年07月04日
   作    者   : Y00213812
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIntMsgNum;                                /* 缓存消息的个数 */
    VOS_UINT8                           aucReserve[3];
    VOS_UINT8                          *pastIntMsg[CNAS_XCC_MAX_INT_MSG_QUEUE_NUM]; /* XCC的消息队列数组，存放消息指针 */
}CNAS_XCC_INT_MSG_QUEUE_STRU;

/*****************************************************************************
 结构名    : CNAS_XCC_FSM_MO_CALLING_CTX_STRU
 结构说明  : 存放MO CALLING状态机的上下文信息
  1.日    期   : 2014年11月19日
    作    者   : w00176964
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserved[4];
}CNAS_XCC_FSM_MO_CALLING_CTX_STRU;

/*****************************************************************************
 结构名    : CNAS_XCC_FSM_MT_CALLING_CTX_STRU
 结构说明  : 存放MT CALLING状态机的上下文信息
  1.日    期   : 2014年11月19日
    作    者   : w00176964
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserved[4];
}CNAS_XCC_FSM_MT_CALLING_CTX_STRU;

/*****************************************************************************
 结构名    : CNAS_XCC_FSM_L1_MAIN_CTX_STRU
 结构说明  : 存放L1 MAIN状态机的上下文信息
  1.日    期   : 2014年11月19日
    作    者   : w00176964
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserved[4];
}CNAS_XCC_FSM_L1_MAIN_CTX_STRU;



/*****************************************************************************
 结构名    : CNAS_XCC_FSM_EXTRA_CTX_UNION
 结构说明  : 状态机状态描述结构,状态机上下文信息
 1.日    期   : 2014年11月19日
   作    者   : W00176964
   修改内容   : 新建
*****************************************************************************/
typedef union
{
    CNAS_XCC_FSM_MO_CALLING_CTX_STRU    stMoCallingCtx;
    CNAS_XCC_FSM_MT_CALLING_CTX_STRU    stMtCallingCtx;
    CNAS_XCC_FSM_L1_MAIN_CTX_STRU       stL1MainCtx;
}CNAS_XCC_FSM_EXTRA_CTX_UNION;


/*****************************************************************************
 结构名    : CNAS_XCC_FSM_CTX_STRU
 结构说明  : 状态机状态描述结构
 1.日    期   : 2014年07月04日
   作    者   : Y00213812
   修改内容   : 新建

 2.日    期   : 2014年11月19日
   作    者   : w00176964
   修改内容   : CDMA 1X项目迭代5修改:新增状态机上下文结构体

*****************************************************************************/
typedef struct
{
    /* 状态机描述指针,指针为NULL表示当前状态机无效  */
    NAS_FSM_DESC_STRU                  *pstFsmDesc;

    /* 当前状态机标识 */
    CNAS_XCC_FSM_ID_ENUM_UINT32         enFsmId;

    /* 上层状态机标识 */
    CNAS_XCC_FSM_ID_ENUM_UINT32         enParentFsmId;

    /* 上层状态机入口消息类型 */
    VOS_UINT32                          ulParentEventType;

    /* 当前状态 */
    VOS_UINT32                          ulState;

    VOS_UINT8                           ucConnectId;
    VOS_UINT8                           ucReserved[3];

    /* 入口消息MSGID和内容  */
    CNAS_XCC_ENTRY_MSG_STRU             stEntryMsg;

    /* 状态机数据 */
    CNAS_XCC_FSM_EXTRA_CTX_UNION        unFsmCtx;
}CNAS_XCC_FSM_CTX_STRU;

/*****************************************************************************
 结构名    : CNAS_XCC_FSM_STACK_STRU
 结构说明  : 状态机栈描述结构
 1.日    期   : 2014年07月04日
   作    者   : Y00213812
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usStackDepth;                           /* 当前压栈的状态机数 */
    VOS_UINT8                           aucReserved[2];
    CNAS_XCC_FSM_CTX_STRU               astFsmStack[CNAS_XCC_MAX_FSM_STACK_DEPTH];  /* 状态机栈的深度 */
}CNAS_XCC_FSM_STACK_STRU;


/*****************************************************************************
 结构名    : CNAS_XCC_AWI_EAWI_INFO_RECO_BUFFER_STRU
 结构说明  : 在WFO状态收到AWI/EAWI，需要缓存解析出的Info record
 1.日    期   : 2014年11月12日
   作    者   : L00256032
   修改内容   : 1X SS Project修改
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucIsBufferValid;            /* 缓存是否有效:VOS_TRUE:有效; VOS_FALSE:无效 */
    CAS_CNAS_1X_RX_TCH_MSG_TYPE_ENUM_UINT8  enMsgType;                  /* 记录消息类型为AWI或EAWI */
    VOS_UINT8                               aucReserve[2];
    union
    {
        CNAS_XCC_AWIM_STRU                  stAWIM;
        CNAS_XCC_EAWIM_STRU                 stEAWIM;
    }u;
}CNAS_XCC_AWI_EAWI_INFO_RECO_BUFFER_STRU;

/*****************************************************************************
 结构名    : CNAS_XCC_EMERGENCY_CALL_CTRL_STRU
 结构说明  : emgency call ctrl info
 1.日    期   : 2014年11月25日
   作    者   : w00176964
   修改内容   : CDMA 1X Iteration 5 Modified
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucWaitFlashMsgRspFlg;                 /* wait emgency call flash msg response flag */
    VOS_UINT8                           ucEmcCallId;                          /* related emgency call ID */
    VOS_UINT8                           ucMtVoiceCallId;                      /* current MT voice call ID */
    VOS_UINT8                           ucFlashMsgSeqNum;                     /* allocated sequence number while sending emgency call FWI/EFWI msg */
}CNAS_XCC_EMERGENCY_CALL_CTRL_STRU;


/*****************************************************************************
 结构名    : CNAS_XCC_PREV_HRPD_ACT_DATA_NET_INFO_STRU
 结构说明  : Prev hrpd net info
 1.日    期   : 2015年7月9日
   作    者   : g00261581
   修改内容   : CDMA DTS2015041700164
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPzid;
    VOS_UINT16                          usSid;
    VOS_UINT16                          usNid;
    VOS_UINT8                           aucReserved[2];
} CNAS_XCC_PREV_HRPD_ACT_DATA_NET_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_XCC_CALL_INFO_CTX_STRU
 结构说明  : 呼叫信息上下文
 1.日    期   : 2014年09月09日
   作    者   : h00246512
   修改内容   : 新建
 2.日    期   : 2014年11月19日
   作    者   : w00176964
   修改内容   : CDMA 1X项目迭代5修改
 3.日    期   : 2015年1月3日
   作    者   : y00245242
   修改内容   : NDSS ORIG功能开发
 4.日    期   : 2015年7月27日
   作    者   : l00324781
   修改内容   : Iter16修改:删除无用元素，增加ucContDtmfSeqNum，ucIsContDtmfAckWait
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                      bitOpCallingPartyNum:1;
    VOS_UINT32                                      bitOpCallingPartySubAddr:1;
    VOS_UINT32                                      bitOpCalledPartySubAddr:1;
    VOS_UINT32                                      bitOpQosInfo:1;
    VOS_UINT32                                      bitOpSpare:28;

    VOS_UINT8                                       ucIsEntityActive;           /* 当前呼叫实例是否激活 */
    VOS_UINT8                                       ucConnectId;                /* 连接ID，XCC的实例标记 */
    VOS_UINT8                                       ucCallId;                   /* 呼叫ID，XCALL用的 */
    VOS_UINT8                                       ucIsDataReady;

    VOS_UINT8                                       ucConRef;                   /* Con_Ref，网络分配的，用于区分呼叫实例的一种标志 */
    VOS_UINT8                                       ucIsMoCall;                 /* 当前是否是主叫 */
    VOS_UINT8                                       ucIsNullCc;                 /* 是否是NULL标识，接入层通知 */
    VOS_UINT8                                       ucIsByPassAlertAns;         /* bypass标志，接入层通知，用于指明是否直接进入通话 */

    /* 删除ucIsStartDtmfAckWait,ucIsStopDtmfAckWait等无用元素 */
    VOS_UINT8                                       ucIsBurstDtmfAckWait;
    VOS_UINT8                                       ucBurstDtmfSeqNum;
    VOS_UINT8                                       ucIsSendFlashAckWait;
    VOS_UINT8                                       ucSendFlashSeqNum;

    VOS_UINT8                                       ucIsCodecOpen;              /* 声码器是否已经打开 */
    VOS_UINT8                                       ucIsSoNegCmplt;             /* SO协商是否完成 */
    VOS_UINT8                                       ucMsgSeqNum;                /* 发送数据的序列号，用于确认L2 ack */
    VOS_UINT8                                       ucContDtmfSeqNum;

    CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16          enInitSo;                   /* 业务初始开始的SO */
    CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16          enCurrentSo;                /* 业务过程中，so可能发生变化，记录当前的SO */

    VOS_UINT8                                       ucQosInfoLen;               /* Qos，数据呼叫需要 */
    VOS_UINT8                                       aucQosInfo[CNAS_XCC_MAX_QOS_LENGTH];

    CAS_CNAS_1X_ORIG_NUM_INFO_STRU                  stCalledPartyNum;           /* 被叫号码 */
    XCC_XCALL_CALLING_PARTY_NUM_INFO_STRU           stCallingPartyNum;          /* 主叫号码 */
    XCC_XCALL_SUB_ADDRESS_INFO_STRU                 stCallingPartySubAddr;      /* 主叫子地址 */
    XCC_XCALL_SUB_ADDRESS_INFO_STRU                 stCalledPartySubAddr;       /* 被叫子地址 */

    VOS_UINT8                                       ucReOrigCount;              /* 重拨次数 */
    VOS_UINT8                                       ucIsL2ErrReOrig;            /* 是否是层二异常导致的重拨 */
    VOS_UINT8                                       ucIsEmergencyCall;          /* 当前是否是紧急呼 */

    VOS_UINT8                                       ucIsReOrigReason;
    VOS_UINT8                                       ucIsDormDataCall;           /* 从DORMANT状态发起的ORIG请求 */
    VOS_UINT8                                       ucIsDataSrvConn;            /* 记录当前是否已经数据业务的连接建立 */
    VOS_UINT8                                       ucSrId;                     /* 记录当前使用的SR_ID */
    VOS_UINT8                                       ucIsContDtmfAckWait;        /* 向CAS发送Cont DTMF Tone Order,设置的等待标志，收到L2 ACK时清空 */


    VOS_UINT32                                      ulIsPrevHrpdFlg;
    CNAS_XCC_PREV_HRPD_ACT_DATA_NET_INFO_STRU       stPrevHrpdActNetInfo;

    CNAS_XCC_AWI_EAWI_INFO_RECO_BUFFER_STRU         stAWIorEAWIInfoRecoBuffer;  /* 在WFO状态收到AWI/EAWI，缓存解析出的Info record */

    XCALL_XCC_PRIVACY_MODE_ENUM_UINT8               enReqPrivacyMode;              /* 请求的privacy mode */
    XCALL_XCC_PRIVACY_MODE_ENUM_UINT8               enNegPrivacyMode;              /* 协商后的privacy mode */
    VOS_UINT8                                       aucReserved[2];
}CNAS_XCC_CALL_INFO_CTX_STRU;

/*****************************************************************************
 结构名    : CNAS_XCC_FSM_ENTITY_STRU
 结构说明  : 状态机实例描述结构
 1.日    期   : 2014年07月09日
   作    者   : l60609
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    CNAS_XCC_FSM_CTX_STRU               stCurFsm;                              /* 状态机当前的状态机数组 */
    CNAS_XCC_FSM_STACK_STRU             stFsmStack;                            /* 状态机的状态机栈数组   */

    CNAS_XCC_CALL_INFO_CTX_STRU         stCallInfoCtx;
}CNAS_XCC_FSM_ENTITY_STRU;

/*****************************************************************************
 结构名    : CNAS_XCC_RECORD_ORIG_CALL_INDEX_ORDER_STRU
 结构说明  : 状态机实例描述结构
 1.日    期   : 2015年01月08日
   作    者   : y00245242
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCallNum;                                  /* 记录激活的呼叫数目*/
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucCallIndex[CNAS_XCC_MAX_FSM_ENTITY_NUM];  /* 记录呼叫所发起顺序索引信息，呼叫先发起的呼叫存在数组0下标，
                                                                                       当某路呼叫释放后，会重新排序 */
}CNAS_XCC_RECORD_ORIG_CALL_INDEX_ORDER_STRU;

/*****************************************************************************
 结构名    : CNAS_XCC_MAIN_CTRL_CTX_STRU
 结构说明  : main control上下文信息
 1.日    期   : 2014年09月10日
   作    者   : y00245242
   修改内容   : 新建
 2.日    期   : 2014年11月26日
   作    者   : w00176964
   修改内容   : CDMA 1X Iteration 5 Modified
 3.日    期   : 2015年1月6日
   作    者   : y00245242
   修改内容   : 增加NDSS ORIG功能

*****************************************************************************/
typedef struct
{
    CNAS_XCC_BUFFER_MSG_QUEUE_STRU                          stBufferMsgQueue;     /* 缓存用户请求消息 */

    VOS_UINT8                                               ucSeqNum;

    VOS_UINT8                                               ucLatestCallIndex;    /* 记录最后一路呼叫索引 */
    VOS_UINT8                                               aucReserve[2];

    CNAS_XCC_EMERGENCY_CALL_CTRL_STRU                       stEmcCallCtrl;      /* emgency call ctrl info */
}CNAS_XCC_MAIN_CTRL_CTX_STRU;


/*****************************************************************************
 结构名    : CNAS_XCC_SRID_INFO_STRU
 结构说明  : SR_ID的上下文信息
 1.日    期   : 2015年1月4日
   作    者   : h00246512
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucIsUsed;
    VOS_UINT8                                               ucSrid;
    CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16                  enSo;
    VOS_UINT8                                               ucConnectId;
    VOS_UINT8                                               aucReserved[3];
}CNAS_XCC_SRID_INFO_STRU;


/*****************************************************************************
 结构名    : CNAS_XCC_CALL_NVIM_CFG_STRU
 结构说明  : 呼叫nv控制
 1.日    期   : 2015年6月15日
   作    者   : c00299063
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucIsL3ErrReOrigCount;
    VOS_UINT8                                               ucPrivacyMode;      /* privacy mode flag: 0 - disable 1 - enable */

    VOS_UINT8                                               aucReserved[14];

    VOS_UINT8                                               ucEccSrvCap;        /* ECC服务能力: TRUE -- 支持ECC服务，FALSE -- 不支持ECC服务 */
    VOS_UINT8                                               ucEccSrvStatus;     /* ECC服务状态: TRUE -- ECC服务打开，FALSE -- ECC服务关闭 */

    VOS_UINT8                                               aucReserved1[2];
}CNAS_XCC_CALL_NVIM_CFG_STRU;


/*****************************************************************************
 结构名    : CNAS_XCC_1X_PAGING_RSP_SO_CFG_STRU
 结构说明  : 1x paging rsp中带so值的控制
 1.日    期   : 2015年11月02日
   作    者   : L00301449
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNoDataSrvRspSo33Flg;                  /* 没有数据业务时，Paging rsp的回复。0 - Paging Rsp中SO带0； 1 - Paging Rsp中SO带33 */
    VOS_UINT8                           aucReserved[3];
}CNAS_XCC_1X_PAGING_RSP_SO_CFG_STRU;

/*****************************************************************************
 结构名    : CNAS_XCC_CTX_STRU
 结构说明  : CNAS XCC 模块运行上下文
 1.日    期   : 2014年07月04日
   作    者   : Y00213812
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    /**************************************************************************
                        CNAS XCC状态机实例
    **************************************************************************/
    CNAS_XCC_FSM_ENTITY_STRU                                astFsmEntity[CNAS_XCC_MAX_FSM_ENTITY_NUM];
    CNAS_XCC_FSM_ENTITY_STRU                               *pstCurFsmEntity;      /* 当前需要处理的状态 */

    /* CNAS XCC内部消息队列 */
    CNAS_XCC_INT_MSG_QUEUE_STRU                             stIntMsgQueue;

    CNAS_XCC_MAIN_CTRL_CTX_STRU                             stMainCtrlCtx;

    CNAS_XCC_SRID_INFO_STRU                                 astSridInfo[CNAS_XCC_MAX_SRID_NUM + 1];

    CNAS_XCC_RECORD_ORIG_CALL_INDEX_ORDER_STRU              stOrigCallIndexOrder;   /* 发起呼叫顺序索引 */

    CNAS_XCC_CALL_NVIM_CFG_STRU                             stCallNvimCfg;

    CNAS_XCC_1X_PAGING_RSP_SO_CFG_STRU                      stPagingRspSoCfg;
}CNAS_XCC_CTX_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

CNAS_XCC_CTX_STRU* CNAS_XCC_GetCtxAddr(VOS_VOID);

CNAS_XCC_FSM_STACK_STRU* CNAS_XCC_GetFsmStackAddr(VOS_VOID);

CNAS_XCC_FSM_CTX_STRU* CNAS_XCC_GetCurFsmAddr(VOS_VOID);

VOS_VOID CNAS_XCC_InitCtx(CNAS_XCC_INIT_TYPE_ENUM_UINT8 enInitType);

VOS_VOID CNAS_XCC_PushFsm(
    CNAS_XCC_FSM_STACK_STRU             *pstFsmStack,
    CNAS_XCC_FSM_CTX_STRU               *pstNewFsm
);

VOS_UINT16 CNAS_XCC_GetFsmStackDepth(VOS_VOID);


VOS_VOID CNAS_XCC_InitFsmL2(
    CNAS_XCC_FSM_ID_ENUM_UINT32         enFsmId
);

VOS_VOID CNAS_XCC_QuitFsmL2(VOS_VOID);

VOS_VOID CNAS_XCC_PopFsm(VOS_VOID);

VOS_UINT16 CNAS_XCC_GetFsmStackPopFlg(VOS_VOID);

VOS_UINT8 CNAS_XCC_GetBufferedMsgNum(VOS_VOID);

/* Modified by w00176964 for CNAS内存裁剪, 2015-9-8, begin */
VOS_UINT8 *CNAS_XCC_GetNextBufferMsg(VOS_VOID);
/* Modified by w00176964 for CNAS内存裁剪, 2015-9-8, end */

VOS_VOID CNAS_XCC_FreeCurrentBufferMsg(VOS_VOID);

/* Modified by w00176964 for CNAS内存裁剪, 2015-9-8, begin */
VOS_UINT8 *CNAS_XCC_GetSpecifiedIndexBufferMsg(
    VOS_UINT8                           ucIndex
);
/* Modified by w00176964 for CNAS内存裁剪, 2015-9-8, end */

VOS_VOID CNAS_XCC_FreeSpecifiedIndexBufferMsg(VOS_UINT8 ucIndex);

VOS_VOID CNAS_XCC_FreeAllBufferMsgInQueue(VOS_VOID);

VOS_VOID CNAS_XCC_BufferMsgInQueue(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID CNAS_XCC_PutMsgInIntMsgQueue(
    VOS_UINT8                          *pstMsg
);

VOS_UINT8 *CNAS_XCC_GetNextIntMsg(VOS_VOID);

VOS_UINT32 CNAS_XCC_GetIntMsgNum(VOS_VOID);

CNAS_XCC_INT_MSG_QUEUE_STRU* CNAS_XCC_GetIntMsgQueueAddr(VOS_VOID);

VOS_VOID CNAS_XCC_InitFsmCtx_L1Main(VOS_VOID);

CNAS_XCC_FSM_ID_ENUM_UINT32 CNAS_XCC_GetCurrFsmId(VOS_VOID);

NAS_FSM_DESC_STRU* CNAS_XCC_GetCurFsmDesc(VOS_VOID);

VOS_VOID  CNAS_XCC_InitCurrFsmCtx(
    CNAS_XCC_INIT_TYPE_ENUM_UINT8       enInitType,
    CNAS_XCC_FSM_CTX_STRU              *pstCurrFsmCtx
)
;

VOS_VOID  CNAS_XCC_InitFsmStackCtx(
    CNAS_XCC_FSM_STACK_STRU            *pstFsmStack
);

VOS_VOID  CNAS_XCC_InitInternalBuffer(
    CNAS_XCC_INT_MSG_QUEUE_STRU        *pstIntMsgQueue
);

VOS_UINT32 CNAS_XCC_GetFsmTopState(VOS_VOID);

CNAS_XCC_MAIN_CTRL_CTX_STRU* CNAS_XCC_GetMainCtrlCtx(VOS_VOID);

VOS_VOID  CNAS_XCC_LoadSubFsm(
    CNAS_XCC_FSM_ID_ENUM_UINT32         enFsmId,
    CNAS_XCC_FSM_CTX_STRU              *pstCurFsm
);

VOS_VOID CNAS_XCC_InitFsmCtx_MoCalling(VOS_VOID);

VOS_VOID CNAS_XCC_InitFsmCtx_MtCalling(VOS_VOID);

VOS_VOID  CNAS_XCC_SetCurrFsmState(
    VOS_UINT32                          ulCurrState
);

CNAS_XCC_CALL_INFO_CTX_STRU*  CNAS_XCC_GetCurrFsmEntityCallInfoCtx( VOS_VOID );

VOS_VOID  CNAS_XCC_InitCallInfoCtx(
    CNAS_XCC_CALL_INFO_CTX_STRU                            *pstCallInfo,
    CNAS_XCC_INIT_CALLINFO_SCENE_ENUM_UINT8                 enScene
);

CNAS_XCC_ENTRY_MSG_STRU* CNAS_XCC_GetCurrFsmMsgAddr(VOS_VOID);

CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16 CNAS_XCC_GetInitSo(VOS_VOID);

VOS_VOID CNAS_XCC_SetInitSo(CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16 enSo);

CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16 CNAS_XCC_GetCurrentSo(VOS_VOID);

VOS_VOID CNAS_XCC_SetCurrentSo(CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16 enSo);

VOS_VOID CNAS_XCC_SaveCurEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT8 CNAS_XCC_AllocSeqNum(VOS_VOID);

VOS_VOID CNAS_XCC_InitMainCtrlCtx(
                                  CNAS_XCC_INIT_TYPE_ENUM_UINT8       enInitType,
                                  CNAS_XCC_MAIN_CTRL_CTX_STRU        *pstMainCtrlCtx
                                  );

VOS_VOID  CNAS_XCC_InitIntMsgQueue(
    CNAS_XCC_INT_MSG_QUEUE_STRU      *pstIntMsgQueue
);

VOS_UINT32 CNAS_XCC_BufferAWIOrEAWIInfoReco(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd,
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx
);

VOS_VOID CNAS_XCC_ClearAWIOrEAWIInfoRecoBuffer(VOS_VOID);

VOS_VOID CNAS_XCC_SetWaitEmcFlashMsgRspFlg(
    VOS_UINT8                           ucFlg
);
VOS_UINT8 CNAS_XCC_GetWaitEmcFlashMsgRspFlg(VOS_VOID);
VOS_VOID  CNAS_XCC_SaveEmcCallId(
    VOS_UINT8                           ucCallId
);
VOS_UINT8 CNAS_XCC_GetEmcCallId(VOS_VOID);
VOS_VOID  CNAS_XCC_SaveEmcFlashMsgSeqNum(
    VOS_UINT8                           ucSeqNum
);

VOS_UINT8 CNAS_XCC_GetEmcFlashMsgSeqNum(VOS_VOID);

VOS_VOID CNAS_XCC_SaveMtVoiceCallId(
    VOS_UINT8                           ucCallId
);
VOS_UINT8 CNAS_XCC_GetMtVoiceCallId(VOS_VOID);

VOS_VOID CNAS_XCC_InitEmergencyCallCtrlCtx(
    CNAS_XCC_EMERGENCY_CALL_CTRL_STRU  *pstEmcCtrl
);

VOS_UINT32   CNAS_XCC_AllocSrId(
    CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16  enSo,
    VOS_UINT8                              *pucSrId,
    VOS_UINT8                               ucConnectId
);
VOS_UINT32   CNAS_XCC_UpdateSrIdUsed(
    CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16  enSo,
    VOS_UINT8                               ucSrId,
    VOS_UINT8                               ucConnectId
);


VOS_VOID CNAS_XCC_SetOrigCallOrderIndex(
    VOS_UINT8                           ucCallIndex
);

VOS_VOID CNAS_XCC_ClearSpecificedOrigCallOrderIndex(
    VOS_UINT8                           ucCallIndex
);

VOS_VOID CNAS_XCC_ClearAllOrigCallOrderIndex(VOS_VOID);

VOS_UINT8 CNAS_XCC_GetLastCallIndex(VOS_VOID);
VOS_VOID CNAS_XCC_INIT_SRID_INFO( VOS_VOID );
VOS_VOID CNAS_XCC_ClearSpecificedSrIdByConnectId(
    VOS_UINT8                           ucConnectId
);

VOS_VOID CNAS_XCC_InitCallNvimCfg(
    CNAS_XCC_CALL_NVIM_CFG_STRU        *pstCallNvimCfg
);


VOS_UINT32 CNAS_XCC_IsExist1xDataOperation(
    TAF_CDMA_SO_TYPE_ENUM_UINT16        enSo
);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
extern VOS_UINT32 I1_TAF_APS_IsExist1xDataOperation(
    TAF_CDMA_SO_TYPE_ENUM_UINT16        enSo
);

#if (3 == MULTI_MODEM_NUMBER)
extern VOS_UINT32 I2_TAF_APS_IsExist1xDataOperation(
    TAF_CDMA_SO_TYPE_ENUM_UINT16        enSo
);
#endif

#endif

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

#endif /* end of CnasXccCtx.h */

