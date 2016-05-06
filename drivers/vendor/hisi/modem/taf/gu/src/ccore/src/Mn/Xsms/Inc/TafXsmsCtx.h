/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXsmsCtx.h
  版 本 号   : 初稿
  作    者   : h00300778S
  生成日期   : 2014年10月31日
  功能描述   : TafXsmsCtx.c头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 创建文件
******************************************************************************/

#ifndef _TAF_XSMS_CTX_H_
#define _TAF_XSMS_CTX_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "TafFsm.h"

#include "TafXsmsUimProc.h"
#include "TafXsmsDecode.h"
#include "TafXsmsMoFsmMainTbl.h"
#include "TafXsmsMtFsmMainTbl.h"
#include "xcc_sms_pif.h"
#include "TafSdcCtx.h"
/* Added by wx270776 for OM融合, 2015-6-27, begin */
#include "TafLog.h"
/* Added by wx270776 for OM融合, 2015-6-27, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#pragma pack(4)
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#if 1
#define TAF_XSMS_INFO_LOG(string)            TAF_LOG(UEPS_PID_XSMS, 0, PS_LOG_LEVEL_INFO,   string)
#define TAF_XSMS_NORMAL_LOG(string)          TAF_LOG(UEPS_PID_XSMS, 0, PS_LOG_LEVEL_NORMAL, string)
#define TAF_XSMS_WARNING_LOG(string)         TAF_LOG(UEPS_PID_XSMS, 0, PS_LOG_LEVEL_WARNING,string)
#define TAF_XSMS_ERROR_LOG(string)           TAF_LOG(UEPS_PID_XSMS, 0, PS_LOG_LEVEL_ERROR,  string)

#define TAF_XSMS_INFO_LOG1(string, para1)    TAF_LOG1(UEPS_PID_XSMS, 0, PS_LOG_LEVEL_INFO,   string, para1)
#define TAF_XSMS_NORMAL_LOG1(string, para1)  TAF_LOG1(UEPS_PID_XSMS, 0, PS_LOG_LEVEL_NORMAL, string, para1)
#define TAF_XSMS_WARNING_LOG1(string, para1) TAF_LOG1(UEPS_PID_XSMS, 0, PS_LOG_LEVEL_WARNING,string, para1)
#define TAF_XSMS_ERROR_LOG1(string, para1)   TAF_LOG1(UEPS_PID_XSMS, 0, PS_LOG_LEVEL_ERROR,  string, para1)
#else
#define TAF_XSMS_INFO_LOG(string)            vos_printf("\r\nXSMS INFO:%s",   string)
#define TAF_XSMS_NORMAL_LOG(string)          vos_printf("\r\nXSMS NORMAL:%s", string)
#define TAF_XSMS_WARNING_LOG(string)         vos_printf("\r\nXSMS WARNING:%s",string)
#define TAF_XSMS_ERROR_LOG(string)           vos_printf("\r\nXSMS ERROR:%s",  string)

#define TAF_XSMS_INFO_LOG1(string, para1)    vos_printf("\r\nXSMS INFO:%s,para1=%d",    string, para1)
#define TAF_XSMS_NORMAL_LOG1(string, para1)  vos_printf("\r\nXSMS NORMAL:%s,para1=%d",  string, para1)
#define TAF_XSMS_WARNING_LOG1(string, para1) vos_printf("\r\nXSMS WARNING:%s,para1=%d", string, para1)
#define TAF_XSMS_ERROR_LOG1(string, para1)   vos_printf("\r\nXSMS ERROR:%s,para1=%d",   string, para1)
#endif

#define TAF_XSMS_BEAER_SEQ_NUM_MAX          (64)
#define TAF_XSMS_MILLISECS_IN_SECOND        (1000)
#define TAF_XSMS_HUNDRED_MILLISECS          (100)

#define TAF_XSMS_GET_MCC(NUM)             (100 * ((NUM  % 1000 / 100 + 1) % 10) \
                                        + 10* ((NUM % 100 / 10 + 1) % 10) \
                                        + (NUM % 10 + 1) % 10)


#define TAF_XSMS_POOL_REC_MAX_TIME          (6) /* 10 * 6 = 60S */
#define TAF_XSMS_MAX_REC_IN_POOL            (5)


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
enum TAF_XSMS_ACTIVE_CHANNEL_ENUM
{
    TAF_XSMS_ACTIVE_DSCH   = 0x01,
    TAF_XSMS_ACTIVE_CSCH   = 0x02,

    TAF_XSMS_ACTIVE_CH_BUTT
};
typedef VOS_UINT8 TAF_XSMS_ACTIVE_CHANNEL_ENUM8;

enum TAF_XSMS_SMS_ORIGPID_ENUM
{
    TAF_XSMS_SMS_ORIGPID_AT    = 0x7F01,
    TAF_XSMS_SMS_ORIGPID_STK   = 0x7F02,
    TAF_XSMS_SMS_ORIGPID_XPDS  = 0x7F03,
    TAF_XSMS_SMS_ORIGPID_XCALL = 0x7F04,

    TAF_XSMS_SMS_ORIGPID_BUTT
};
typedef VOS_UINT16 TAF_XSMS_SMS_ORIGPID_ENUM_UINT16;


enum TAF_XSMS_CCF_AP_MEM_FULL_ENUM
{
    TAF_XSMS_CCF_AP_MEM_FULL        = 0xAA,
    TAF_XSMS_CCF_AP_MEM_NOT_FULL    = 0x55,

    TAF_XSMS_CCF_AP_MEM_FULL_BUTT
};
typedef VOS_UINT8 TAF_XSMS_CCF_AP_MEM_FULL_ENUM8;


/*****************************************************************************
 结构名    : TAF_XSMS_MT_FSM_ID_ENUM
 结构说明  :
 1.日    期   : 2014年11月1日
   作    者   : l00208516
   修改内容   : 新建
*****************************************************************************/
enum TAF_XSMS_MT_FSM_ID_ENUM
{
    TAF_XSMS_MT_IDLE_STATE                     = 0,
    TAF_XSMS_MT_WAITING_XCC_CALL_CONN_STATE    = 1,
    TAF_XSMS_MT_WAITING_XCC_CALL_CNF_STATE     = 2,
    TAF_XSMS_MT_WAITING_XCC_SO_IND_STATE       = 3,
    TAF_XSMS_MT_WAITING_DSCH_DATA_IND_STATE    = 4,
    TAF_XSMS_MT_WAITING_UIM_WRITE_CNF_STATE    = 5,
    TAF_XSMS_MT_WAITING_UIM_READ_CNF_STATE     = 6,
    TAF_XSMS_MT_WAITING_AS_CNF_STATE           = 7,
    TAF_XSMS_MT_WAITING_XCC_DISCONNECT_STATE   = 8,

    TAF_XSMS_MT_STATE_BUTT

};
typedef VOS_UINT32 TAF_XSMS_MT_FSM_ID_ENUM_UINT32;

/*****************************************************************************
 结构名    : TAF_XSMS_MO_FSM_ID_ENUM
 结构说明  :
 1.日    期   : 2014年11月1日
   作    者   : l00208516
   修改内容   : 新建
*****************************************************************************/
enum TAF_XSMS_MO_FSM_ID_ENUM
{
    TAF_XSMS_MO_IDLE_STATE                     = 0,
    TAF_XSMS_MO_WAITING_FDN_CNF                = 1,
    TAF_XSMS_MO_WAITING_CC_CNF                 = 2,
    TAF_XSMS_MO_WAITING_XCC_ORIG_CALL_CNF      = 3,
    TAF_XSMS_MO_WAITING_XCC_SO_IND             = 4,
    TAF_XSMS_MO_WAITING_AS_CNF                 = 5,
    TAF_XSMS_MO_WAITING_TL_ACK                 = 6,
    TAF_XSMS_MO_WAITING_XCC_END_CALL_CNF       = 7,
    TAF_XSMS_MO_WAITING_CAS_SMS_ABORT_IND      = 8,

    TAF_XSMS_MO_STATE_BUTT
};
typedef VOS_UINT32 TAF_XSMS_MO_FSM_ID_ENUM_UINT32;

/*****************************************************************************
 结构名    : TAF_XSMS_BD_SMS_PRIO_ENUM
 结构说明  :
 1.日    期   :
   作    者   :
   修改内容   : 新建
*****************************************************************************/
enum TAF_XSMS_BD_SMS_PRIO_ENUM
{
    TAF_XSMS_BD_SMS_PRIO_NORMAL         = 0,
    TAF_XSMS_BD_SMS_PRIO_INTERACTIVE    = 1,
    TAF_XSMS_BD_SMS_PRIO_URGENT         = 2,
    TAF_XSMS_BD_SMS_PRIO_EMERGENCY      = 3,


    TAF_XSMS_BD_SMS_PRIO_BUTT
};
typedef VOS_UINT8 TAF_XSMS_BD_SMS_PRIO_ENUM_UINT8;


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
extern TAF_XSMS_INIT_CTRL_INFO_STRU     g_stTafXsmsInitCtrlInfo;
extern TAF_XSMS_CTRL_INFO_STRU          g_stTafXsmsReqCtrlInfo;


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
 结构名    : TAF_XSMS_MSG_MO_REC_STRU
 结构说明  : MO短信记录结构
 1.日    期   : 2014年11月3日
   作    者   : l00208516
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    /* NV项的结构体 */
    TAF_NVIM_1X_XSMS_CFG_STRU           stNvResend;
    /* reply_seq */
    VOS_UINT8                           ucReplySeq;
    VOS_UINT8                           ucIsRcvSmsWhenSndSms;  /* VOS_TRUE : 在发送短信的过程中收到了短信 VOS_FALSE: 没有收到短信 */
    VOS_UINT16                          usOpId;
    /* AT下发的短信内容 */
    TAF_XSMS_MESSAGE_STRU               st1xSms;
    /* 生成的DBM */
    TAF_XSMS_DATA_BURST_MSG_STRU        stDbm;
    /* message id */
    VOS_UINT16                          usMessageId;
    /* 当前发送使用的信道 */
    TAF_XSMS_ACTIVE_CHANNEL_ENUM8       enActiveSndChannel;
    /* 信道是否是短信建立的 */
    VOS_UINT8                           ucIsSmsOrigChannel;
    /* 实际重试次数 */
    VOS_UINT8                           ucResendTimes;
    /**<  reason of re orig is L2 error */
    VOS_UINT8                           ucIsL2ErrReOrig;
    /**<  coutinous count */
    VOS_UINT8                           ucL2ErrReOrigCount;
    VOS_UINT8                           ucWaitRedirCompleteFlag;
    /* 短信来源标志位 AT SMS*/
    TAF_XSMS_SMS_ORIGPID_ENUM_UINT16    enOrigPid;
    TAF_XCC_FAIL_LAYER_ENUM_UINT8       enLastErrType;
    VOS_UINT8                           ucIsOrigReqSendFlag;  /* VOS_TRUE: 已经发送请求；VOS_FALSE:没有发送 */
    VOS_UINT16                          usIsTlAckNeed;
    VOS_UINT8                           aucRsv1[2];
    /* 收到TL_ACK的cause code */
    TAF_XSMS_CAUSE_CODE_STRU            stCauseCode;
}TAF_XSMS_MSG_MO_REC_STRU;


/*****************************************************************************
 结构名    : TAF_XSMS_MSG_MT_REC_STRU
 结构说明  : MT短信记录结构
 1.日    期   : 2014年11月3日
   作    者   : l00208516
   修改内容   : 新建

*****************************************************************************/

/*****************************************************************************
 结构名    : TAF_XSMS_MSG_MT_REC_STRU
 结构说明  : MT短信记录结构
 1.日    期   : 2014年11月3日
   作    者   : l00208516
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    /* 重试NV */
    TAF_NVIM_1X_XSMS_CFG_STRU           stResend;
    /*　ＴＬ_ＡＣＫ　*/
    TAF_XSMS_TRANSPORT_MESSAGE_STRU     stTlAck;
    /* 接收的短信*/
    TAF_XSMS_TRANSPORT_MESSAGE_STRU     stTLP2PMsg;

    /* 生成的DBM */
    TAF_XSMS_DATA_BURST_MSG_STRU        stDbm;
    /* call id*/
    VOS_UINT8                           ucCallId;
    /* 接收短信使用的信道 */
    TAF_XSMS_ACTIVE_CHANNEL_ENUM8       enActiveRevChannel;
    /* 信道是否是短信建立的 */
    VOS_UINT8                           ucIsSmsOrigChannel;
    /* 实际重试次数 */
    VOS_UINT8                           ucReSendTimes;
    VOS_UINT8                           ucIsMtCreatLink;    /* FALSE 不是被叫链路，TRUE 是被叫链路 */
    PS_BOOL_ENUM_UINT8                  enIsCasAckFlag;
    VOS_UINT8                           aucCasAckData[2];
    VOS_UINT32                          ulIsTlAckSndToCas;  /* VOS_FALSE: 还没有发送TL_ACK VOS_TRUE:已经发送TL_ACK等待CNF中 */
}TAF_XSMS_MSG_MT_REC_STRU;

/*****************************************************************************
 结构名    : TAF_XSMS_FSM_CTX_STRU
 结构说明  : 状态机状态描述结构
 1.日    期   : 2014年11月1日
   作    者   : l00208516
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    /* 状态机描述指针,指针为NULL表示当前状态机无效  */
    TAF_STA_STRU                       *pstFsmDesc;

    /* 当前状态机标识 */
    TAF_XSMS_MT_FSM_ID_ENUM_UINT32      enFsmId;
}TAF_XSMS_MT_FSM_CTX_STRU;

typedef struct
{
    /* 状态机描述指针,指针为NULL表示当前状态机无效  */
    TAF_STA_STRU                       *pstFsmDesc;

    /* 当前状态机标识 */
    TAF_XSMS_MO_FSM_ID_ENUM_UINT32      enFsmId;
}TAF_XSMS_MO_FSM_CTX_STRU;

/*****************************************************************************
 结构名    : TAF_XSMS_CTX_STRU
 结构说明  : XSMS的上下文
 1.日    期   : 2014年11月1日
   作    者   : l00208516
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    /**************************************************************************
                        TAF XSMS MO状态机状态及其状态栈
     **************************************************************************/
    TAF_XSMS_MO_FSM_CTX_STRU           stCurFsm;                               /* 状态机当前的状态机数组 */
}TAF_XSMS_MO_CTX_STRU;


typedef struct
{
    /**************************************************************************
                        TAF XSMS MT状态机状态
     **************************************************************************/
    TAF_XSMS_MT_FSM_CTX_STRU           stCurFsm;                               /* 状态机当前的状态机数组 */
}TAF_XSMS_MT_CTX_STRU;

/*****************************************************************************
 结构名    : TAF_XSMS_MO_SEND_POOL_ITEM_STRU
 结构说明  : MO短信记录池
 1.日    期   : 2015年10月13日
   作    者   : c00299064
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsRecExist;  /* VOS_TRUE:存在记录 */
    VOS_UINT8                           ucRecTimeLeft; /* 增加记录的时候时间设置成60s ，变成0之后删除当前记录*/
    TAF_XSMS_SMS_ORIGPID_ENUM_UINT16    enOrigPid;
    VOS_UINT16                          usIsTlAckNeeded; /* TRUE: need ; FALSE :no NEED TL_ACK*/
    VOS_UINT16                          usOpId;
    TAF_XSMS_MESSAGE_STRU              *pst1xSms;      /* 短信记录 */
}TAF_XSMS_MO_SEND_POOL_ITEM_STRU;


/*****************************************************************************
 结构名    : TAF_XSMS_MO_SEND_MSG_POOL_STRU
 结构说明  : MO短信记录池
 1.日    期   : 2015年10月13日
   作    者   : c00299064
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCurItemNumInPool;
    TAF_XSMS_MO_SEND_POOL_ITEM_STRU     stPoolItem[TAF_XSMS_MAX_REC_IN_POOL];
}TAF_XSMS_MO_SEND_MSG_POOL_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
extern TAF_XSMS_MO_SEND_MSG_POOL_STRU          g_stXsmsMoSendPool;

/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern TAF_XSMS_MSG_MO_REC_STRU * TAF_XSMS_MoGetRecAddr(VOS_VOID);
extern TAF_XSMS_MSG_MT_REC_STRU * TAF_XSMS_MtGetRecAddr(VOS_VOID);

extern TAF_XSMS_MO_CTX_STRU* TAF_XSMS_MoGetCtxAddr(VOS_VOID);
extern TAF_XSMS_MT_CTX_STRU* TAF_XSMS_MtGetCtxAddr(VOS_VOID);
extern TAF_XSMS_MT_FSM_CTX_STRU* TAF_XSMS_MtGetCurFsmAddr(VOS_VOID);

extern TAF_XSMS_MO_FSM_CTX_STRU* TAF_XSMS_MoGetCurFsmAddr(VOS_VOID);
extern VOS_VOID TAF_XSMS_MtSetCurrFsmState(VOS_UINT32 ulCurrState);
extern VOS_VOID TAF_XSMS_MoSetCurrFsmState(VOS_UINT32 ulCurrState);
extern TAF_XSMS_MO_FSM_ID_ENUM_UINT32 TAF_XSMS_MoGetCurrFsmId(VOS_VOID);
extern TAF_XSMS_MT_FSM_ID_ENUM_UINT32 TAF_XSMS_MtGetCurrFsmId(VOS_VOID);
extern VOS_VOID TAF_XSMS_MoIdleInit(VOS_VOID);
extern VOS_VOID TAF_XSMS_MtIdleInit(VOS_VOID);
extern VOS_VOID TAF_XSMS_MoStopAllTimer(VOS_VOID);
extern VOS_VOID TAF_XSMS_MtStopAllTimer(VOS_VOID);
extern VOS_VOID TAF_XSMS_MoInitGobal(VOS_VOID);
extern VOS_VOID TAF_XSMS_MtInitGobal(VOS_VOID);
extern TAF_XSMS_CTRL_INFO_STRU * TAF_XSMS_GetReqCtrlInfoAddr(VOS_VOID);
extern TAF_XSMS_INIT_CTRL_INFO_STRU * TAF_XSMS_GetInitCtrlInfoAddr(VOS_VOID);
extern VOS_VOID TAF_XSMS_ReqCtrlInfoClear(VOS_VOID);
extern VOS_VOID TAF_XSMS_InitCtrlInfoClear(VOS_VOID);
extern VOS_UINT8 TAF_XSMS_MoGetBearSeqNum(TAF_XSMS_MSG_MO_REC_STRU *pstMoRec);
extern TAF_STA_STRU* TAF_XSMS_MtGetStaTblAddr(VOS_VOID);
extern TAF_STA_STRU* TAF_XSMS_MoGetStaTblAddr(VOS_VOID);
extern VOS_VOID TAF_XSMS_InitFsmCtx_Main(VOS_VOID);
extern VOS_VOID TAF_XSMS_RegMoFsm(VOS_VOID);
extern VOS_VOID TAF_XSMS_RegMtFsm(VOS_VOID);
extern VOS_VOID TAF_XSMS_SetApMemFullFlag(
    TAF_XSMS_AP_MEM_FULL_ENUM_UINT8     enAPMemFullFlag
);
extern TAF_XSMS_CCF_AP_MEM_FULL_ENUM8 TAF_XSMS_GetApMemFullFlag(VOS_VOID);
VOS_VOID TAF_XSMS_TranslatePlusToNum(
    TAF_XSMS_ADDR_STRU                 *pstXsmsAddr
);

VOS_UINT32 TAF_XSMS_GetHomeMcc(
    VOS_VOID
);

VOS_VOID TAF_XSMS_TransAsciiToDtmf(
    VOS_UINT8                          *pucSrcData,
    VOS_UINT8                          *pucDestData,
    VOS_UINT8                           ucLen
);

VOS_VOID TAF_XSMS_MoInitSendPool(VOS_VOID);

VOS_UINT32 TAF_XSMS_IsMoSendPoolFull(VOS_VOID);

VOS_UINT32 TAF_XSMS_InsertRecToMoSendPool
(
    TAF_XSMS_SMS_ORIGPID_ENUM_UINT16    enOrigPid,
    VOS_UINT16                          usIsTlAckNeeded,
    VOS_UINT16                          usOpId,
    TAF_XSMS_MESSAGE_STRU              *pst1xSms
);

VOS_UINT32 TAF_XSMS_DeleteRecInMoSendPool
(
    VOS_UINT32                          ulRecIndex
);

VOS_UINT32 TAF_XSMS_GetRecFromMoSendPool
(
    TAF_XSMS_SMS_ORIGPID_ENUM_UINT16   *pusOrigPid,
    VOS_UINT16                         *pusIsTlAckNeeded,
    VOS_UINT16                         *pusOpId,
    TAF_XSMS_MESSAGE_STRU              *pst1xSms
);

VOS_VOID TAF_XSMS_RefreshRecsInMoSendPool
(
    VOS_VOID
);

VOS_UINT32 TAF_XSMS_IsRecCanInsertToPool
(
    TAF_XSMS_SMS_ORIGPID_ENUM_UINT16    enOrigPid
);

VOS_VOID TAF_XSMS_GetKmcDefaultAddress
(
    TAF_XSMS_ADDR_STRU                 *pstXsmsKmcAddr
);
VOS_UINT32 TAF_XSMS_IsMoSendPoolEmpty(VOS_VOID);

VOS_UINT32 TAF_XSMS_IsMtKmcSms(
    TAF_XSMS_ADDR_STRU                 *pstXsmsKmcAddr
);

extern VOS_UINT32 TAF_XSMS_RcvSendPoolMsgReq_MoIdle(VOS_VOID);


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif

#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of __TAF_XSMS_CTX_H__ */

