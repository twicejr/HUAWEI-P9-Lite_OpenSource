/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafSpmCtx.h
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2013年5月7日
  最近修改   :
  功能描述   : TafSpmCtx.c的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年5月7日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/
#ifndef _TAF_SPM_CTX_H_
#define _TAF_SPM_CTX_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "PsTypeDef.h"
#include  "TafFsm.h"
#include  "TafSpmTimerMgmt.h"
#include  "Taf_MmiStrParse.h"
/* Added by y00245242 for VoLTE_PhaseII 项目, 2013-9-23, begin */
#if (FEATURE_ON == FEATURE_IMS)
#include  "ImsaInterface.h"
#endif
/* Added by y00245242 for VoLTE_PhaseII 项目, 2013-9-23, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define TAF_SPM_MAX_MSG_BUFFER_LEN                    (1200)                    /* 缓存的最大长度 */
/* Modified by y00245242 for VoLTE_PhaseII  项目, 2013-9-22, begin */
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-23, begin */
/*
 * 注: 目前每个业务类型queue最多保存一个业务请求消息，现在对于queue队列操作已支持保存多个
 *     业务请求的处理，但目前一个业务类型只对应一个timer(见TAF_SPM_TIMER_ID_ENUM_UINT32枚
 *     举定义)，如果支持同类型业务支持多个缓存, 必须增加相应定时器数目，否则程序会有问题,
 *     切记!!!
 */
#define TAF_SPM_MAX_CC_MSG_QUEUE_NUM                  (1)       /* 最大缓存与呼叫业务相关的消息个数 */
#define TAF_SPM_MAX_SMS_MSG_QUEUE_NUM                 (3)       /* 最大缓存与SMS业务相关的消息个数 */
#define TAF_SPM_MAX_SS_MSG_QUEUE_NUM                  (1)       /* 最大缓存与SS业务相关的个数 */

#define TAF_SPM_MAX_CC_REDIAL_QUEUE_NUM               (1)       /* 呼叫重拨缓存queue最大数目 */
#define TAF_SPM_MAX_SMS_REDIAL_QUEUE_NUM              (1)       /* 短信重拨缓存queue最大数目 */
#define TAF_SPM_MAX_SS_REDIAL_QUEUE_NUM               (1)       /* 补充业务重拨缓存queue最大数目 */
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-23, end */

/* Modified by y00245242 for VoLTE_PhaseII  项目, 2013-9-22, end */
#define TAF_SPM_MAX_CLIENT_ID_ENTITY_FSM_ID_NUM       (5)                       /* 最大client ID实体状态机个数 */
#define TAF_SPM_INVALID_CLIENT_ID                     OMA_CLIENT_ID_BUTT        /* 无效的client id */
#define TAF_SPM_INVALID_CLIENT_ID_ENTITY_FSM_INDEX    (0xff)
#define TAF_SPM_SSC_FDN_CHECK_STR_MAX_LEN             (40)
#define TAF_SPM_SSC_FDN_CHECK_BCD_MAX_LEN             (TAF_SPM_SSC_FDN_CHECK_STR_MAX_LEN / 2)
#define TAF_SPM_SSC_FDN_CHECK_7BIT_MAX_LEN            (((TAF_SPM_SSC_FDN_CHECK_STR_MAX_LEN * 8) + 6) / 7)
#define TAF_SPM_SSC_MAX_LEN                           (256)
#define TAF_SPM_CALL_CTRL_SS_STRING_LEN               ((TAF_SPM_SSC_MAX_LEN / 2) + 1)
#define TAF_SPM_USSD_STRING_LEN                       (160)
#define TAF_SPM_CALL_CTRL_USSD_STRING_LEN             (TAF_SPM_USSD_STRING_LEN + 1)
#define TAF_SPM_USSD_STR_MAX_LEN                      (256)
#define TAF_SPM_SSC_OFFSET                            (1)
#define TAF_SPM_NUM_TYPE_INVALID                      (0xff)                    /* 无效号码类型 */
#define TAF_SPM_FDN_CHECK_STR_MAX_LEN                 (40)
#define TAF_SPM_FDN_CHECK_BCD_MAX_LEN                 (TAF_SPM_FDN_CHECK_STR_MAX_LEN / 2)
#define TAF_SPM_FDN_CHECK_7BIT_MAX_LEN                (((TAF_SPM_FDN_CHECK_STR_MAX_LEN * 8) + 6) / 7)
#define TAF_SPM_GET_7BIT_STRING_SIZE(ulPackStrLen,ulUnpackStrLen) (ulUnpackStrLen = ((ulPackStrLen * 8) + 6) / 7)
#define TAF_SPM_GET_BCD_NUBMER_LENGTH(ulAsciiLength)                            (((ulAsciiLength) + 1)/2)

/* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
#define TAF_SPM_USIM_FILE_FIRST_RECORD                  (1)

#define TAF_SPM_USIM_FILE_SECOND_RECORD                 (2)

#define TAF_SPM_USIM_FILE_MAX_RECORD                    (255)

/* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

#define NAS_SPM_ONE_THOUSAND_MILLISECOND                (1000)                  /* 1000MS */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : TAF_SPM_FSM_ID_ENUM_UINT32
 枚举说明  : 状态机ID枚举定义
 1.日    期   : 2013年5月7日
   作    者   : W00176964
   修改内容   : 新建
*****************************************************************************/
enum TAF_SPM_FSM_ID_ENUM
{
    /* SPM MAIN态状态机的名称 */
    TAF_SPM_FSM_MAIN                                        = 0X00,

    /* SPM SERVICE CTRL状态机 */
    TAF_SPM_FSM_SERVICE_CTRL                                = 0X01,

    TAF_SPM_FSM_BUTT

};
typedef VOS_UINT32 TAF_SPM_FSM_ID_ENUM_UINT32;


/*****************************************************************************
 枚举名    : TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8
 枚举说明  : 业务请求类型
 1.日    期   : 2013年9月24日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
enum
{
    TAF_SPM_SRV_REQ_TYPE_CALL,                  /* CALL service request */
    TAF_SPM_SRV_REQ_TYPE_SS,                    /* SS service request */
    TAF_SPM_SRV_REQ_TYPE_SMS,                   /* SMS service request */

    TAF_SPM_SRV_REQ_TYPE_BUTT
};
typedef VOS_UINT8 TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_SPM_SERVICE_STATUS_ENUM
 枚举说明  : PS服务状态
 1.日    期   : 2014年1月2日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
enum TAF_SPM_SERVICE_STATUS_ENUM
{
    TAF_SPM_SERVICE_STATUS_NORMAL_SERVICE           = 0,                        /* 正常服务 */
    TAF_SPM_SERVICE_STATUS_LIMITED_SERVICE          = 1,                        /* 限制服务 */
    TAF_SPM_SERVICE_STATUS_LIMITED_SERVICE_REGION   = 2,                        /* 有限制区域服务 */
    TAF_SPM_SERVICE_STATUS_NO_IMSI                  = 3,                        /* 无imsi */
    TAF_SPM_SERVICE_STATUS_NO_SERVICE               = 4,                        /* 无服务 */
    TAF_SPM_SERVICE_STATUS_NO_CHANGE                = 5,
    TAF_SPM_SERVICE_STATUS_DEEP_SLEEP               = 6,
    TAF_SPM_SERVICE_STATUS_BUTT
};
typedef VOS_UINT8 TAF_SPM_SERVICE_STATUS_ENUM_UINT8;


/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-1-15, begin */
/*****************************************************************************
 枚举名    : TAF_SPM_VP_NV_CFG_STATE_ENUM
 枚举说明  : VP功能的NV设置状态
 1.日    期   : 2014年1月15日
   作    者   : w00176964
   修改内容   : 新建
*****************************************************************************/
enum TAF_SPM_VP_NV_CFG_STATE_ENUM
{
    TAF_SPM_VP_MO_MT_BOTH               = 0,                                    /* 允许视频呼叫(包括主叫和被叫) */
    TAF_SPM_VP_NONE                     = 1,                                    /* 禁止视频主叫和被叫 */
    TAF_SPM_VP_MO_ONLY                  = 2,                                    /* 允许视频主叫，禁止视频被叫 */
    TAF_SPM_VP_MT_ONLY                  = 3,                                    /* 禁止视频主叫，允许视频被叫 */
    TAF_SPM_VP_BUTT
};
typedef VOS_UINT8   TAF_SPM_VP_NV_CFG_STATE_ENUM_UINT8;

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-1-15, end */

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
 结构名    : TAF_SPM_GET_MSG_CLIENT_ID_FUNC_PTR
 结构说明  : 获取client ID操作列表的处理函数指针
  1.日    期   : 2013年5月9日
    作    者   : w00176964
    修改内容   : 新增
*****************************************************************************/
typedef VOS_UINT32  (*TAF_SPM_GET_MSG_CLIENT_ID_FUNC_PTR)(struct MsgCB *pstMsg, VOS_UINT16 *pusClientId);

/*****************************************************************************
 结构名    : TAF_SPM_GET_MSG_CLIENT_ID_LIST_STRU
 结构说明  : 针对发送的PID,获取发送消息对应的client ID操作列表
 1.日    期   : 2013年5月9日
   作    者   : w00176964
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSndPid;
    TAF_SPM_GET_MSG_CLIENT_ID_FUNC_PTR  pGetMsgClientIdProcFunc;
}TAF_SPM_GET_MSG_CLIENT_ID_LIST_STRU;



/*****************************************************************************
 结构名    : TAF_SPM_ENTRY_MSG_STRU
 结构说明  : 需要保存的入口消息
 1.日    期   : 2013年5月7日
   作    者   : W00176964
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEventType;
    VOS_UINT8                           aucEntryMsgBuffer[TAF_SPM_MAX_MSG_BUFFER_LEN];
} TAF_SPM_ENTRY_MSG_STRU;

/*****************************************************************************
 结构名    : TAF_SPM_CACHE_MSG_INFO_STRU
 结构说明  : 缓存的消息内容
 1.日    期   : 2013年5月7日
   作    者   : W00176964
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    TAF_SPM_ENTRY_MSG_STRU              stMsgEntry;                             /* 缓存的具体内容 */
}TAF_SPM_CACHE_MSG_INFO_STRU;

/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-23, begin */
/* Modified by y00245242 for VoLTE_PhaseII  项目, 2013-9-22, begin */
/*****************************************************************************
 结构名    : TAF_SPM_MSG_CC_QUEUE_STRU
 结构说明  : 缓存的消息队列
 1.日    期   : 2013年5月7日
   作    者   : W00176964
   修改内容   : 新建

 2.日    期   : 2013年9月22日
   作    者   : y00245242
   修改内容   : 修改数据结构，删除一个成员，修改结构名称
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCacheMsgNum;                             /* 缓存消息的个数 */
    VOS_UINT8                           aucReserve[3];
    TAF_SPM_CACHE_MSG_INFO_STRU         astMsgQueue[TAF_SPM_MAX_CC_MSG_QUEUE_NUM]; /* SPM的消息队列数组，存储的是带通用消息头的消息 */
}TAF_SPM_MSG_CC_QUEUE_STRU;
/* Modified by y00245242 for VoLTE_PhaseII  项目, 2013-9-22, end */

/* Added by y00245242 for VoLTE_PhaseII  项目, 2013-9-22, begin */
/*****************************************************************************
 结构名    : TAF_SPM_MSG_SMS_QUEUE_STRU
 结构说明  : 缓存的消息队列
 1.日    期   : 2013年9月22日
   作    者   : y00245242
   修改内容   : 新建，缓存SMS消息队列结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCacheMsgNum;                              /* 缓存消息的个数 */
    VOS_UINT8                           aucReserve[3];
    TAF_SPM_CACHE_MSG_INFO_STRU         astMsgQueue[TAF_SPM_MAX_SMS_MSG_QUEUE_NUM]; /* SPM的消息队列数组，存储的是带通用消息头的消息 */
}TAF_SPM_MSG_SMS_QUEUE_STRU;

/*****************************************************************************
 结构名    : TAF_SPM_MSG_SS_QUEUE_STRU
 结构说明  : 缓存的消息队列
 1.日    期   : 2013年9月22日
   作    者   : y00245242
   修改内容   : 新建，缓存SS消息队列结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCacheMsgNum;                              /* 缓存消息的个数 */
    VOS_UINT8                           aucReserve[3];
    TAF_SPM_CACHE_MSG_INFO_STRU         astMsgQueue[TAF_SPM_MAX_SS_MSG_QUEUE_NUM]; /* SPM的消息队列数组，存储的是带通用消息头的消息 */
}TAF_SPM_MSG_SS_QUEUE_STRU;

/*****************************************************************************
 结构名    : TAF_SPM_DOMAIN_SEL_MSG_QUEUE_STRU
 结构说明  : 缓存的消息队列
 1.日    期   : 2013年9月22日
   作    者   : y00245242
   修改内容   : 新建，缓存消息队列
*****************************************************************************/
typedef struct
{
    TAF_SPM_MSG_CC_QUEUE_STRU           stCcMsgQueue;                               /* buffer CC service request message queue */
    TAF_SPM_MSG_SMS_QUEUE_STRU          stSmsMsgQueue;                              /* buffer SMS service request message queue */
    TAF_SPM_MSG_SS_QUEUE_STRU           stSsMsgQueue;                               /* buffer SS service request message queue */
}TAF_SPM_DOMAIN_SEL_MSG_QUEUE_STRU;

/* Added by y00245242 for VoLTE_PhaseIII 项目, 2013-12-12, begin */
/*****************************************************************************
 结构名    : TAF_SPM_CC_REDIAL_QUEUE_STRU
 结构说明  : 缓存呼叫换域重拨消息队列
 1.日    期   : 2013年12月31日
   作    者   : y00245242
   修改内容   : 新建，缓存消息队列
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCacheMsgNum;                              /* 缓存消息的个数 */
    VOS_UINT8                           aucReserve[3];
    TAF_SPM_ENTRY_MSG_STRU              astMsgQueue[TAF_SPM_MAX_CC_REDIAL_QUEUE_NUM];
}TAF_SPM_CC_REDIAL_QUEUE_STRU;

/*****************************************************************************
 结构名    : TAF_SPM_SMS_REDIAL_QUEUE_STRU
 结构说明  : 缓存短信换域重拨消息队列
 1.日    期   : 2013年12月31日
   作    者   : y00245242
   修改内容   : 新建，缓存消息队列
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCacheMsgNum;                              /* 缓存消息的个数 */
    VOS_UINT8                           aucReserve[3];
    TAF_SPM_ENTRY_MSG_STRU              astMsgQueue[TAF_SPM_MAX_SMS_REDIAL_QUEUE_NUM];
}TAF_SPM_SMS_REDIAL_QUEUE_STRU;

/*****************************************************************************
 结构名    : TAF_SPM_SS_REDIAL_QUEUE_STRU
 结构说明  : 缓存补充业务换域重拨消息队列
 1.日    期   : 2013年12月31日
   作    者   : y00245242
   修改内容   : 新建，缓存消息队列
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCacheMsgNum;                              /* 缓存消息的个数 */
    VOS_UINT8                           aucReserve[3];
    TAF_SPM_ENTRY_MSG_STRU              astMsgQueue[TAF_SPM_MAX_SS_REDIAL_QUEUE_NUM];
}TAF_SPM_SS_REDIAL_QUEUE_STRU;

/*****************************************************************************
 结构名    : TAF_SPM_REDIAL_MSG_CTX_STRU
 结构说明  : 重拨缓存队列数据结构
 1.日    期   : 2013年12月12日
   作    者   : y00245242
   修改内容   : 新建，缓存消息队列
*****************************************************************************/
typedef struct
{
    TAF_SPM_CC_REDIAL_QUEUE_STRU        stCcMsgQueue;                               /* 缓存呼叫消息 */
    TAF_SPM_SMS_REDIAL_QUEUE_STRU       stSmsMsgQueue;                              /* 缓存短信消息 */
    TAF_SPM_SS_REDIAL_QUEUE_STRU        stSsMsgQueue;                               /* 缓存补充业务消息 */
}TAF_SPM_REDIAL_MSG_CTX_STRU;

/* Added by y00245242 for VoLTE_PhaseIII 项目, 2013-12-12, end */
/*****************************************************************************
 结构名    : TAF_SPM_DOMAIN_SEL_CTX_STRU
 结构说明  : 缓存的消息队列
 1.日    期   : 2013年9月23日
   作    者   : y00245242
   修改内容   : 新建，缓存消息队列
 2.日    期   : 2013年12月12日
   作    者   : y00245242
   修改内容   : 增加换域重拨功能
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSubscriptId;              /* my subscriptId in IMS */
    VOS_UINT8                           ucImsSmsSupported;          /* IMS SMS supported by IMS server, from ext_info */
    VOS_UINT8                           ucImsSmsSendingFlg;         /* IMS短信正在发送标志 */
    TAF_SPM_SERVICE_STATUS_ENUM_UINT8   enLastPsStatus;              /* 上次的PS服务状态 */
    VOS_UINT8                           aucReserve[1];

    /* 删除IMS注册状态，移到SDC中 */
    TAF_SPM_DOMAIN_SEL_MSG_QUEUE_STRU   stBufferMsgQueue;           /* buffer mesage queue */
    /* Added by y00245242 for VoLTE_PhaseIII 项目, 2013-12-12, begin */
    TAF_SPM_REDIAL_MSG_CTX_STRU         stRedialMsgQueue;
    /* Added by y00245242 for VoLTE_PhaseIII 项目, 2013-12-12, end */
}TAF_SPM_DOMAIN_SEL_CTX_STRU;
/* Added by y00245242 for VoLTE_PhaseII  项目, 2013-9-22, end */
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-23, end */


/*****************************************************************************
 结构名    : TAF_SPM_SERVICE_CTRL_CTX_STRU
 结构说明  : SERVICE CONTROL状态机上下文
 1.日    期   : 2013年5月07日
   作    者   : w00176964
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve[4];
}TAF_SPM_SERVICE_CTRL_CTX_STRU;

/*****************************************************************************
 结构名    : TAF_SPM_FSM_EXTRA_CTX_UNION
 结构说明  : 状态机状态描述结构,状态机上下文信息
 1.日    期   : 2013年5月7日
   作    者   : w00176964
   修改内容   : 新建
*****************************************************************************/
typedef union
{
    TAF_SPM_SERVICE_CTRL_CTX_STRU                           stServiceCtrlCtx;

}TAF_SPM_FSM_EXTRA_CTX_UNION;



/*****************************************************************************
 结构名    : TAF_SPM_FSM_CTX_STRU
 结构说明  : 状态机状态描述结构
 1.日    期   : 2013年5月7日
   作    者   : W00176964
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    /* 状态机描述指针,指针为NULL表示当前状态机无效  */
    TAF_FSM_DESC_STRU                  *pstFsmDesc;

    /* 当前状态机标识 */
    TAF_SPM_FSM_ID_ENUM_UINT32          enFsmId;

    /* 当前状态 */
    VOS_UINT32                          ulState;                                /* 当前状态 */

    /* 入口消息MSGID和内容  */
    TAF_SPM_ENTRY_MSG_STRU              stEntryMsg;

    /* 状态机上下文数据 */
    TAF_SPM_FSM_EXTRA_CTX_UNION         unFsmCtx;

}TAF_SPM_FSM_CTX_STRU;


/*****************************************************************************
 结构名    : TAF_SPM_CLIENT_ID_ENTITY_FSM_CTX_STRU
 结构说明  : 每个client ID实体对应的状态机描述表结构
 1.日    期   : 2013年5月7日
   作    者   : W00176964
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    TAF_SPM_FSM_CTX_STRU                stFsmCtx;                  /* 状态机描述表信息 */

    /*********************发起业务的通道的client id,用于识别指定的状态机******************************/
    VOS_UINT16                          usClientId;

    VOS_UINT8                           ucRunFlg;                  /* 状态机在运行:VOS_TRUE:状态机有clientd ID在占用否则无 */
    VOS_UINT8                           aucRsv[1];
}TAF_SPM_CLIENT_ID_ENTITY_FSM_CTX_STRU;


/*****************************************************************************
 结构名    : TAF_SPM_MAIN_FSM_CTX_STRU
 结构说明  : 主状态机描述表结构
 1.日    期   : 2013年5月15日
   作    者   : W00176964
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    TAF_SPM_FSM_CTX_STRU                stFsmCtx;               /* 状态机描述表信息 */
}TAF_SPM_MAIN_FSM_CTX_STRU;

/*****************************************************************************
 结构名    : TAF_SPM_MAIN_CTRL_INFO_STRU
 结构说明  : SPM模块框架控制信息结构体描述
 1.日    期   : 2012年8月8日
   作    者   : w00176964
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUpdateEntryMsgFlg;                /* 更新入口消息标记:VOS-TRUE:需要更新service ctrl的入口消息；VOS_FALSE:不需要更新,直接透传 */
    VOS_UINT8                           aucRsv[2];
    TAF_SPM_ENTRY_MSG_STRU              stServiceCtrlEntryMsg;              /* 更新后的service ctrl的入口消息 */
}TAF_SPM_MAIN_CTRL_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_SPM_BUFFER_SERVICE_REQ_PROTECT_TIMER_STRU
 结构说明  : 域选择缓存服务请求保护定时器相关信息
 1.日    期   : 2015年10月9日
   作    者   : c00318887
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulBufferCcProtectTimerLen;              /* 0: 域选择时不进行缓存；大于0: 缓存CC服务的保护定时器时长，单位 ms */
    VOS_UINT32                          ulBufferSmsProtectTimerLen;             /* 0: 域选择时不进行缓存；大于0: 缓存SMS服务的保护定时器时长，单位 ms */
    VOS_UINT32                          ulBufferSsProtectTimerLen;              /* 0: 域选择时不进行缓存；大于0: 缓存SS服务的保护定时器时长，单位 ms */
}TAF_SPM_BUFFER_SERVICE_REQ_PROTECT_TIMER_STRU;

/*****************************************************************************
 结构名    : TAF_SPM_SERVICE_CTRL_CFG_INFO_STRU
 结构说明  : spm模块业务控制配置信息参数结构
1.日    期   : 2013年05月14日
  作    者   : w00176964
  修改内容   : 新建结构体
2.日    期   : 2013年6月5日
  作    者   : z00161729
  修改内容   : SVLTE 和usim接口调整修改
3.日    期   : 2014年1月15日
  作    者   : w00176964
  修改内容   : VoLTE_PhaseIII 项目修改
4.日    期   : 2015年10月10日
  作    者   : c00318887
  修改内容   : DTS2015090705019
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSimCallCtrlSupportFlg;            /* SIM卡中call ctrl支持标记 */
    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2014-1-15, begin */
    TAF_SPM_VP_NV_CFG_STATE_ENUM_UINT8  enVpCfgState;
    VOS_UINT8                           aucRsv[2];
    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2014-1-15, end */


    TAF_SPM_BUFFER_SERVICE_REQ_PROTECT_TIMER_STRU           stBufferServiceReqProtectTimerInfo;                 

    VOS_UINT32                          ulMeStatus;
}TAF_SPM_SERVICE_CTRL_CFG_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_SPM_CALL_CHECK_INFO_STRU
 结构说明  : FDN&CTRL检查信息
 1.日    期   : 2014年11月28日
   作    者   : j00174725
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MN_CALL_CALLED_NUM_STRU             stCalledNumber;
    MN_CALL_SUBADDR_STRU                stSubaddr;
    TAF_CS_CAUSE_ENUM_UINT32            enCheckRslt;                            /* 记录检查结果 */
    VOS_UINT32                          ulCheckCnfFlag;                         /* VOS_TRUE: 已经回复过，VOS_FALSE:没有回复过 */
}TAF_SPM_CALL_CHECK_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_SPM_CALL_ECONF_INFO_STRU
 结构说明  : SPM模块中记录的增强型多方会议信息
 1.日    期   : 2014年11月28日
   作    者   : j00174725
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usClientId;
    MN_OPERATION_ID_T                       ucopId;                             /* Operation ID */
    MN_CALL_TYPE_ENUM_U8                    enCallType;                         /* call Type */
    MN_CALL_MODE_ENUM_U8                    enCallMode;                         /* call mode */
    VOS_UINT8                               ucCallNum;                          /* 总的电话号码个数 */
    VOS_UINT8                               ucSendSuccNum;                      /* 发起检查成功的号码个数 */
    VOS_UINT8                               ucRcvNum;                           /* 收到回复的检查个数 */
    MN_CALL_CS_DATA_CFG_STRU                stDataCfg;
    TAF_SPM_CALL_CHECK_INFO_STRU            astEconfCheckInfo[TAF_CALL_MAX_ECONF_CALLED_NUM];
}TAF_SPM_CALL_ECONF_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_SPM_CONTEXT_STRU
 结构说明  : SPM模块的上下文信息
 1.日    期   : 2013年5月7日
   作    者   : W00176964
   修改内容   : 新建

 2.日    期   : 2013年9月22日
   作    者   : y00245242
   修改内容   : 在数据结构中增加缓存消息成员
*****************************************************************************/
typedef struct
{
    TAF_SPM_CLIENT_ID_ENTITY_FSM_CTX_STRU                   astEntityFsm[TAF_SPM_MAX_CLIENT_ID_ENTITY_FSM_ID_NUM];   /* 并发的client ID对应的状态机数组 */

    TAF_SPM_CLIENT_ID_ENTITY_FSM_CTX_STRU                  *pstCurrEntityFsm;                               /* 当前client id所对应的状态机信息 */

    TAF_SPM_MAIN_FSM_CTX_STRU                               stCurMainFsm;                                   /* 当前主状态机信息 */

    TAF_SPM_TIMER_CTX_STRU                                  astSpmTimerCtx[TAF_SPM_MAX_TIMER_NUM];          /* SPM当前正在运行的定时器资源 */

    TAF_SPM_MAIN_CTRL_INFO_STRU                             stMainCtrlInfo;                                 /* 框架控制信息 */

    TAF_SPM_SERVICE_CTRL_CFG_INFO_STRU                      stServiceCtrlCfgInfo;                           /* 业务控制配置信息 */

    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-23, begin */
    /* Added by y00245242 for VoLTE_PhaseII  项目, 2013-9-22, begin */
    TAF_SPM_DOMAIN_SEL_CTX_STRU                             stDomainSelCtx;                                 /* 域选择消息缓存队列 */
    /* Added by y00245242 for VoLTE_PhaseII  项目, 2013-9-22, end */
    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-23, end */

    TAF_SPM_CALL_ECONF_INFO_STRU                            stEconfInfo;

    VOS_UINT8                                               ucEcallHangUpImsFlag;
    VOS_UINT8                                               aucRsv[3];
}TAF_SPM_CONTEXT_STRU;


/*****************************************************************************
 结构名    : TAF_SPM_GET_MSG_CLIENT_ID_FUNC_PTR
 结构说明  : 获取client ID操作列表的处理函数指针
  1.日    期   : 2013年5月9日
    作    者   : w00176964
    修改内容   : 新增
*****************************************************************************/
typedef VOS_UINT32  (*TAF_SPM_CALL_CTRL_MODIFY_FUNC_PTR)(
    VOS_UINT32                          ulSenderPid,
    MN_MMI_OPERATION_PARAM_STRU        *pstMmiOpParam,
    VOS_VOID                           *pMsg
);

/*****************************************************************************
 结构名    : TAF_SPM_SS_CALL_CTRL_MODIFY_STRU
 结构说明  : SS进行call control检查后的修改表信息
 1.日    期   : 2013年5月17日
   作    者   : W00176964
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MN_MMI_OPERATION_TYPE_ENUM_U8       ucMmiOperationType;                       /*当前的操作类型*/
    VOS_UINT8                           aucReserved1[3];
    TAF_SPM_CALL_CTRL_MODIFY_FUNC_PTR   pModifyFunc;
}TAF_SPM_SS_CALL_CTRL_MODIFY_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
/*******************************状态机上下文操作API函数定义******************************/
VOS_VOID    TAF_SPM_SetCurrEntityFsmClientId(
    VOS_UINT16                          usClientId
);
VOS_UINT16  TAF_SPM_GetCurrEntityFsmClientId(VOS_VOID);

VOS_VOID    TAF_SPM_SetCurrEntityFsmState(
    VOS_UINT32                          ulState
);
VOS_UINT32  TAF_SPM_GetCurrEntityFsmState(VOS_VOID);


VOS_VOID    TAF_SPM_SetCurrEntityFsmRunFlg(
    VOS_UINT8                           ucRunFlg
);
VOS_UINT8   TAF_SPM_GetCurrEntityFsmRunFlg(VOS_VOID);


VOS_VOID TAF_SPM_SetCurrEntityFsmAddr(
    VOS_UINT8                           ucFsmIndex
);
TAF_SPM_CLIENT_ID_ENTITY_FSM_CTX_STRU* TAF_SPM_GetCurrEntityFsmAddr(VOS_VOID);

TAF_SPM_FSM_CTX_STRU* TAF_SPM_GetCurrEntityFsmCtxAddr(VOS_VOID);

TAF_SPM_MAIN_FSM_CTX_STRU* TAF_SPM_GetCurrMainFsmAddr(VOS_VOID);

TAF_SPM_FSM_ID_ENUM_UINT32  TAF_SPM_GetCurrEntityFsmId(VOS_VOID);

/***********************公共函数定义****************************/
VOS_UINT16 TAF_SPM_GetEntityFsmClientIdByFsmIndex(
    VOS_UINT8                           ucFsmIndex
);

VOS_UINT32 TAF_SPM_GetCurrEntityFsmEntryMsgSndPid(VOS_VOID);
VOS_UINT16 TAF_SPM_GetCurrEntityFsmEntryMsgName(VOS_VOID);

VOS_UINT8 TAF_SPM_GetEntityFsmIndexByClientId(
    VOS_UINT16                          usClientId
);
VOS_UINT8 TAF_SPM_GetIdleEntityFsmIndex(VOS_VOID);

VOS_UINT8 TAF_SPM_GetEntityFsmRunFlgByFsmIndex(
    VOS_UINT8                           ucFsmIndex
);

TAF_SPM_FSM_CTX_STRU* TAF_SPM_GetEntityFsmCtxAddrByFsmIndex(
    VOS_UINT8                           ucFsmIndex
);

TAF_SPM_TIMER_CTX_STRU*  TAF_SPM_GetTimerCtxAddr( VOS_VOID );

TAF_SPM_SERVICE_CTRL_CFG_INFO_STRU*  TAF_SPM_GetServiceCtrlCfgInfoAddr( VOS_VOID );

VOS_VOID TAF_SPM_SetUpdateEntryMsgFlg(
    VOS_UINT8                           ucReplaceFlg
);

VOS_UINT8 TAF_SPM_GetUpdateEntryMsgFlg(VOS_VOID);


TAF_SPM_ENTRY_MSG_STRU* TAF_SPM_GetServiceCtrlEntryMsgAddr(VOS_VOID);

VOS_VOID TAF_SPM_UpdateServiceCtrlEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_SPM_GetClientIdWithAppMsg(
    struct MsgCB                       *pstMsg,
    VOS_UINT16                         *pusClientId
);

VOS_VOID TAF_SPM_GetOpIdWithAppMsg(
    struct MsgCB                       *pstMsg,
    VOS_UINT8                          *pucOpId
);

VOS_UINT32 TAF_SPM_GetClientIdWithVosTimerMsg(
    struct MsgCB                       *pstMsg,
    VOS_UINT16                         *pusClientId
);

VOS_UINT32 TAF_SPM_GetClientIdWithUsimMsg(
    struct MsgCB                       *pstMsg,
    VOS_UINT16                         *pusClientId
);


VOS_UINT32 TAF_SPM_GetClientIdWithPbMsg(
    struct MsgCB                       *pstMsg,
    VOS_UINT16                         *pusClientId
);

VOS_UINT32 TAF_SPM_GetClientIdWithTafMsg(
    struct MsgCB                       *pstMsg,
    VOS_UINT16                         *pusClientId
);

VOS_VOID  TAF_SPM_InitEntityFsmCtx(
    TAF_SPM_FSM_CTX_STRU               *pstCurrFsmCtx
);

VOS_VOID  TAF_SPM_InitMainFsm( VOS_VOID );

VOS_VOID  TAF_SPM_InitEntityFsm( VOS_VOID );

VOS_VOID TAF_SPM_FSM_InitEntityFsm(
    TAF_SPM_FSM_ID_ENUM_UINT32          enFsmId,
    TAF_FSM_DESC_STRU                  *pstFsmDesc,
    VOS_UINT32                          ulState
);

VOS_VOID TAF_SPM_FSM_InitMainFsm(
    TAF_SPM_FSM_ID_ENUM_UINT32          enFsmId,
    TAF_FSM_DESC_STRU                  *pstFsmDesc,
    VOS_UINT32                          ulState
);

VOS_VOID TAF_SPM_FSM_QuitCurrEntityFsm(VOS_VOID);

VOS_VOID  TAF_SPM_InitMainCtrlInfo(
    TAF_SPM_MAIN_CTRL_INFO_STRU        *pstMainCtrl
);

VOS_VOID  TAF_SPM_InitServiceCtrlCfgInfo(
    TAF_SPM_SERVICE_CTRL_CFG_INFO_STRU *pstServiceCtrlCfg
);

VOS_VOID  TAF_SPM_InitFsmCtx_Main(VOS_VOID);

VOS_VOID  TAF_SPM_InitFsmCtx_ServiceCtrl(VOS_VOID);

TAF_SPM_CONTEXT_STRU* TAF_SPM_GetSpmCtxAddr( VOS_VOID );

TAF_SPM_ENTRY_MSG_STRU* TAF_SPM_GetCurrEntityFsmEntryMsgAddr(VOS_VOID);

VOS_VOID TAF_SPM_SaveCurrEntityFsmEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  TAF_SPM_GetClientId(
    struct MsgCB                       *pstMsg,
    VOS_UINT16                         *pusClientId
);

/* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
VOS_UINT32 TAF_SPM_GetClientIdWithStkMsg(
    struct MsgCB                       *pstMsg,
    VOS_UINT16                         *pusClientId
);
/* Added by f62575 for V9R1 STK升级, 2013-6-26, end */

/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-23, begin */
VOS_UINT8 TAF_SPM_GetCcMsgQueueNum(VOS_VOID);

VOS_UINT8 TAF_SPM_IsCcMsgQueueFull(VOS_VOID);

VOS_UINT8 TAF_SPM_GetSmsMsgQueueNum(VOS_VOID);

VOS_UINT8 TAF_SPM_IsSmsMsgQueueFull(VOS_VOID);

VOS_UINT8 TAF_SPM_GetSsMsgQueueNum(VOS_VOID);

VOS_UINT8 TAF_SPM_IsSsMsgQueueFull(VOS_VOID);
TAF_SPM_DOMAIN_SEL_MSG_QUEUE_STRU *TAF_SPM_GetBufferMsgQueueAddr(VOS_VOID);
VOS_VOID TAF_SPM_InitBufferCcMsgQueue(
    TAF_SPM_MSG_CC_QUEUE_STRU          *pstCcMsgQueue
);
VOS_VOID TAF_SPM_InitBufferSmsMsgQueue(
    TAF_SPM_MSG_SMS_QUEUE_STRU              *pstSmsMsgQueue
);
VOS_VOID TAF_SPM_InitBufferSsMsgQueue(
    TAF_SPM_MSG_SS_QUEUE_STRU              *pstSsMsgQueue
);


TAF_SPM_CACHE_MSG_INFO_STRU *TAF_SPM_GetSpecifiedIndexMessageAddrFromCcQueue(
    VOS_UINT8                           ucIndex
);

TAF_SPM_CACHE_MSG_INFO_STRU *TAF_SPM_GetSpecifiedIndexMessageAddrFromSmsQueue(
    VOS_UINT8                           ucIndex
);

TAF_SPM_CACHE_MSG_INFO_STRU *TAF_SPM_GetSpecifiedIndexMessageAddrFromSsQueue(
    VOS_UINT8                           ucIndex
);

VOS_VOID TAF_SPM_ClearMessagesInSmsQueue(VOS_VOID);

VOS_VOID TAF_SPM_FreeSpecificedIndexMessageInCcQueue(
    VOS_UINT8                           ucIndex
);

VOS_VOID TAF_SPM_FreeSpecificedIndexMessageInSmsQueue(
    VOS_UINT8                           ucIndex
);

VOS_VOID TAF_SPM_FreeSpecificedIndexMessageInSsQueue(
    VOS_UINT8                           ucIndex
);

VOS_UINT32 TAF_SPM_PutMessageToCcQueue(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_PutMessageToSmsQueue(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_PutMessageToSsQueue(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_SPM_SetCcMsgQueueNum(
    VOS_UINT8                           ucCacheMsgNum
);
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-23, end */

/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-28, begin */
VOS_VOID TAF_SPM_InitServiceReqBufferMsgQueue(VOS_VOID);
/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-28, end */

/* Added by s00261364 for V3R360_eCall项目, 2014-4-9, end */
#if (FEATURE_IMS == FEATURE_ON)
/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, begin */
/* 删除IMS注册状态，移到SDC中 */

VOS_VOID TAF_SPM_SetImsSmsSupportedOnImsServer(
    VOS_UINT8                           ucImsSmsSupported
);
VOS_UINT8 TAF_SPM_GetImsSmsSupportedOnImsServer(VOS_VOID);

/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, end */

/* Added by y00245242 for VoLTE_PhaseII 项目, 2013-9-23, begin */
VOS_VOID TAF_SPM_InitDomainSelCtx(TAF_SPM_DOMAIN_SEL_CTX_STRU *pstDomainSelMsgQueue);
/* Added by y00245242 for VoLTE_PhaseII 项目, 2013-9-23, end */

VOS_UINT8 TAF_SPM_GetImsSmsSendingFlg(VOS_VOID);

VOS_VOID TAF_SPM_SetImsSmsSendingFlg(VOS_UINT8 ucImsSmsSendingFlg);

TAF_SPM_SERVICE_STATUS_ENUM_UINT8 TAF_SPM_GetLastPsServiceStatus(VOS_VOID);

VOS_VOID TAF_SPM_SetLastPsServiceStatus(TAF_SPM_SERVICE_STATUS_ENUM_UINT8 enCurrPsStatus);

TAF_SPM_REDIAL_MSG_CTX_STRU *TAF_SPM_GetRedialMsgQueueAddr(VOS_VOID);

VOS_VOID TAF_SPM_InitCallRedialBuffer(
    TAF_SPM_CC_REDIAL_QUEUE_STRU       *pstCallRedialQueue
);

VOS_UINT8 TAF_SPM_GetNumberOfCallRedialBuffer(VOS_VOID);

VOS_UINT8 TAF_SPM_IsCallRedialBufferEmpty(VOS_VOID);

VOS_UINT8 TAF_SPM_IsCallRedialBufferFull(VOS_VOID);

VOS_VOID TAF_SPM_SetNumberOfCallRedialBuffer(VOS_UINT8 ucCacheMsgNum);

VOS_UINT32 TAF_SPM_PutMsgIntoCallRedialBuffer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

TAF_SPM_ENTRY_MSG_STRU *TAF_SPM_GetSpecificedIndexFromCallRedialBuffer(VOS_UINT8 ucIndex);

VOS_VOID TAF_SPM_FreeSpecificedIndexCallRedialBuffer(VOS_UINT8 ucIndex);

VOS_VOID TAF_SPM_InitSmsRedialBuffer(
    TAF_SPM_SMS_REDIAL_QUEUE_STRU      *pstSmsRedialQueue
);

VOS_UINT8 TAF_SPM_GetNumberOfSmsRedialBuffer(VOS_VOID);

VOS_VOID TAF_SPM_SetNumberOfSmsRedialBuffer(VOS_UINT8 ucCacheMsgNum);

VOS_UINT8 TAF_SPM_IsSmsRedialBufferEmpty(VOS_VOID);

VOS_UINT8 TAF_SPM_IsSmsRedialBufferFull(VOS_VOID);

VOS_UINT32 TAF_SPM_PutMsgIntoSmsRedialBuffer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

TAF_SPM_ENTRY_MSG_STRU *TAF_SPM_GetSpecificedIndexFromSmsRedialBuffer(VOS_UINT8 ucIndex);

VOS_VOID TAF_SPM_FreeSpecificedIndexSmsRedialBuffer(VOS_UINT8 ucIndex);

TAF_SPM_CALL_ECONF_INFO_STRU* TAF_SPM_GetCallEconfInfoAddr(VOS_VOID);

VOS_VOID TAF_SPM_InitEconfInfo(VOS_VOID);

VOS_UINT32 TAF_SPM_GetEventTypeFromCurrEntityFsmEntryMsg(VOS_VOID);

#if (FEATURE_IMS == FEATURE_ON)
VOS_VOID  TAF_SPM_SetEcallHangUpImsFlag(
    VOS_UINT8                           ucFlag
);

VOS_UINT8 TAF_SPM_GetEcallHangUpImsFlag(VOS_VOID);
#endif
#endif

TAF_SPM_BUFFER_SERVICE_REQ_PROTECT_TIMER_STRU* TAF_SPM_GetBufferServiceReqProtectTimerInfo(VOS_VOID);
VOS_UINT32   TAF_Spm_GetBufferCcProtectTimerLen(VOS_VOID);
VOS_UINT32   TAF_SPM_GetBufferSmsProtectTimerLen(VOS_VOID);
VOS_UINT32   TAF_SPM_GetBufferSsProtectTimerLen(VOS_VOID);

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

#endif /* end of TafSpmCtx.h */

