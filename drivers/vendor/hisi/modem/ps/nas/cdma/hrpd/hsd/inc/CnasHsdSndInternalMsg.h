/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsdSndInternalMsg.h
  版 本 号   : 初稿
  作    者   : C00299064
  生成日期   : 2014年12月2日
  最近修改   :
  功能描述   : CnasHsdSndInternalMsg.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月2日
    作    者   : C00299064
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CNAS_HSD_SND_INTERNAL_MSG_H__
#define __CNAS_HSD_SND_INTERNAL_MSG_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "CnasHsdCtx.h"
#include "CnasPrlApi.h"
#include "xsd_xreg_pif.h"
#include "cas_1x_idlectrl_proc_nas_pif.h"
#include "CnasHsdFsmSysAcq.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define CNAS_HSD_1X_MAX_REDIR_CHAN_NUM                      (16)

/* HSD内部系统捕获请求中带的频点最大个数 */
#define CNAS_HSD_INTERNAL_SYSTEM_ACQ_REQ_CHAN_MAX_NUM       (4)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : CNAS_HSD_INTERNAL_MSG_TYPE_ENUM
 枚举说明  : 内部消息名枚举定义
 1.日    期   : 2014年12月2日
   作    者   : C00299064
   修改内容   : 新建
*****************************************************************************/
enum CNAS_HSD_INTERNAL_MSG_TYPE_ENUM
{
    ID_CNAS_HSD_HSD_ABORT_REQ                = 0x0000, /* _H2ASN_MsgChoice CNAS_HSD_HSD_ABORT_REQ_STRU*/
    ID_CNAS_HSD_HSD_SWITCH_ON_RSLT_CNF       = 0x0001, /* _H2ASN_MsgChoice CNAS_HSD_HSD_SWITCH_ON_RSLT_CNF_STRU*/
    ID_CNAS_HSD_HSD_BSR_RSLT_CNF             = 0x0002, /* _H2ASN_MsgChoice CNAS_HSD_HSD_BSR_RSLT_CNF_STRU*/
    ID_CNAS_HSD_HSD_POWER_OFF_RSLT_CNF       = 0x0003, /* _H2ASN_MsgChoice CNAS_HSD_HSD_POWER_OFF_RSLT_CNF_STRU*/
    ID_CNAS_HSD_HSD_REDIRECTION_IND          = 0x0004, /* _H2ASN_MsgChoice CNAS_HSD_HSD_REDIRECTION_IND_STRU*/
    ID_CNAS_HSD_HSD_REDIRECTION_RSLT_CNF     = 0x0005, /* _H2ASN_MsgChoice CNAS_HSD_HSD_REDIRECTION_RSLT_CNF_STRU*/
    ID_CNAS_HSD_HSD_SYSTEM_ACQUIRED_REQ      = 0x0006, /* _H2ASN_MsgChoice CNAS_HSD_HSD_SYSTEM_ACQUIRED_REQ_STRU*/
    ID_CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF = 0x0007, /* _H2ASN_MsgChoice CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU*/

    ID_CNAS_HSD_HSD_POWER_SAVE_RSLT_CNF      = 0x0008, /* _H2ASN_MsgChoice CNAS_HSD_HSD_POWER_SAVE_RSLT_CNF_STRU*/
    ID_CNAS_HSD_HSD_INTER_SYS_RSLT_CNF       = 0x0009, /* _H2ASN_MsgChoice CNAS_HSD_HSD_INTER_SYS_RSLT_CNF_STRU*/

    ID_CNAS_XSD_HSD_SYS_ACQ_RSLT_IND         = 0x1000,



#ifdef DMT
    ID_CNAS_HSD_HSD_TEST_CFG_REQ,                      /* _H2ASN_MsgChoice CNAS_HSD_HSD_TEST_CFG_REQ_STRU*/
#endif

    ID_CNAS_HSD_HSD_PIF_MSG_TYPE_ENUM_BUTT   = 0xFFFF
};
typedef VOS_UINT16 CNAS_HSD_INTERNAL_MSG_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : CNAS_HSD_BSR_RESULT_ENUM
 枚举说明  : BSR搜索结果
 1.日    期   : 2014年12月2日
   作    者   : C00299064
   修改内容   : 新建
*****************************************************************************/
enum CNAS_HSD_BSR_RESULT_ENUM
{
    CNAS_HSD_BSR_RESULT_SUCCESS         = 0x00000000,
    CNAS_HSD_BSR_RESULT_FAILURE         = 0x00000001,
    CNAS_HSD_BSR_RESULT_ABORTED         = 0x00000002,
    CNAS_HSD_BSR_RESULT_BUTT            = 0x00000003
};
typedef VOS_UINT32 CNAS_HSD_BSR_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : CNAS_HSD_ABORT_TYPE_ENUM
 枚举说明  : Abort类型
 1.日    期   : 2014年12月2日
   作    者   : C00299064
   修改内容   : 新建
*****************************************************************************/
enum CNAS_HSD_ABORT_TYPE_ENUM
{
    CNAS_HSD_ABORT_TYPE_IMMEDIATELY     = 0x00000000,
    CNAS_HSD_ABORT_TYPE_DELAY           = 0x00000001,
    CNAS_HSD_ABORT_TYPE_BUTT            = 0x00000002
};
typedef VOS_UINT32 CNAS_HSD_ABORT_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : CNAS_HSD_SWITCH_ON_RESULT_ENUM
 枚举说明  : 开机结果
 1.日    期   : 2014年12月2日
   作    者   : C00299064
   修改内容   : 新建
*****************************************************************************/
enum CNAS_HSD_SWITCH_ON_RESULT_ENUM
{
    CNAS_HSD_SWITCH_ON_RESULT_SUCCESS   = 0x00000000,
    CNAS_HSD_SWITCH_ON_RESULT_FAILURE   = 0x00000001,
    CNAS_HSD_SWITCH_ON_RESULT_ABORTED   = 0x00000002,
    CNAS_HSD_SWITCH_ON_RESULT_BUTT      = 0x00000003
};
typedef VOS_UINT32 CNAS_HSD_SWITCH_ON_RESULT_ENUM_UINT32;


/*****************************************************************************
 枚举名    : CNAS_HSD_REDIR_RESULT_ENUM
 枚举说明  : 重定向搜索搜索结果
 1.日    期   : 2014年12月2日
   作    者   : C00299064
   修改内容   : 新建
*****************************************************************************/

enum CNAS_HSD_REDIR_RESULT_ENUM
{
    CNAS_HSD_REDIR_RESULT_SUCCESS       = 0x00000000,
    CNAS_HSD_REDIR_RESULT_FAILURE       = 0x00000001,
    CNAS_HSD_REDIR_RESULT_ABORTED       = 0x00000002,
    CNAS_HSD_REDIR_RESULT_BUTT          = 0x00000003
};
typedef VOS_UINT32 CNAS_HSD_REDIR_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : CNAS_HSD_SYSTEM_ACQUIRED_RESULT_ENUM
 枚举说明  : 系统捕获结果
 1.日    期   : 2014年12月2日
   作    者   : C00299064
   修改内容   : 新建

 2.日    期   : 2015年08月02日
   作    者   : x00306642
   修改内容   : 添加搜网过程中重定向的结果
*****************************************************************************/
enum CNAS_HSD_SYSTEM_ACQUIRED_RESULT_ENUM
{
    CNAS_HSD_SYSTEM_ACQUIRED_RESULT_SUCCESS                 = 0x00000000,
    CNAS_HSD_SYSTEM_ACQUIRED_RESULT_FAILURE                 = 0x00000001,
    CNAS_HSD_SYSTEM_ACQUIRED_RESULT_ABORTED                 = 0x00000002,
    CNAS_HSD_SYSTEM_ACQUIRED_RESULT_NORF                    = 0x00000003,
    CNAS_HSD_SYSTEM_ACQUIRED_RESULT_REDIRECTION             = 0x00000004,
    CNAS_HSD_SYSTEM_ACQUIRED_RESULT_BUTT                    = 0x00000005
};
typedef VOS_UINT32 CNAS_HSD_SYSTEM_ACQUIRED_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : CNAS_XSD_HSD_SYS_ACQ_RSLT_ENUM
 枚举说明  : 1X系统捕获结果
 1.日    期   : 2014年12月2日
   作    者   : C00299064
   修改内容   : 新建
*****************************************************************************/
enum CNAS_XSD_HSD_SYS_ACQ_RSLT_ENUM
{
    CNAS_XSD_HSD_SYS_ACQ_RSLT_SUCCESS                 = 0x00000000,
    CNAS_XSD_HSD_SYS_ACQ_RSLT_FAILURE                 = 0x00000001,
    CNAS_XSD_HSD_SYS_ACQ_RSLT_BUTT                    = 0x00000002
};
typedef VOS_UINT32 CNAS_XSD_HSD_SYS_ACQ_RSLT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : CNAS_HSD_SYS_ACQ_FAIL_ACT_ENUM_UINT8
 枚举说明  : 搜网失败之后行为定义
 1.日    期   : 2014年12月16日
   作    者   : h00300778
   修改内容   : 新建
*****************************************************************************/
enum CNAS_HSD_SYS_ACQ_FAIL_ACT_ENUM
{
    CNAS_HSD_SYS_ACQ_FAIL_ACT_WAIT_TIMEOUT = 0,             /* 搜网失败之后等待定时器超时再发起搜网 */
    CNAS_HSD_SYS_ACQ_FAIL_ACT_ACQ_IMMEDIATE= 1,             /* 搜网失败之后马上再次发起搜网 */
    CNAS_HSD_SYS_ACQ_FAIL_ACT_BUTT
};

typedef VOS_UINT8 CNAS_HSD_SYS_ACQ_FAIL_ACT_ENUM_UINT8;

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
 结构名    : CNAS_HSD_HSD_ABORT_REQ_STRU
 结构说明  : HSD发送终止状态机消息的结构
 1.日    期   : 2014年7月15日
   作    者   : C00299064
   修改内容   : 终止状态机消息的结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                      /* _H2ASN_Skip */
    CNAS_HSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId;    /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_HSD_ABORT_TYPE_ENUM_UINT32                         enAbortType;
}CNAS_HSD_HSD_ABORT_REQ_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_HSD_SWITCH_ON_RSLT_CNF_STRU
 结构说明  : HSD发送开机确认消息结构
 1.日    期   : 2014年12月10日
   作    者   : h00300778
   修改内容   : HSD开机结果CNF消息的结构

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_HSD_SWITCH_ON_RESULT_ENUM_UINT32                   enRslt;
}CNAS_HSD_HSD_SWITCH_ON_RSLT_CNF_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_HSD_BSR_RSLT_CNF_STRU
 结构说明  : HSD发送BSR结果确认消息结构
 1.日    期   : 2014年7月15日
   作    者   : C00299064
   修改内容   : 终止状态机消息的结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_HSD_BSR_RESULT_ENUM_UINT32                         enRslt;
}CNAS_HSD_HSD_BSR_RSLT_CNF_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_HSD_POWER_OFF_RSLT_CNF_STRU
 结构说明  : HSD发送关机确认消息结构
 1.日    期   : 2014年7月15日
   作    者   : C00299064
   修改内容   : 终止状态机消息的结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
}CNAS_HSD_HSD_POWER_OFF_RSLT_CNF_STRU;


/*****************************************************************************
 结构名    : CNAS_HSD_HSD_SYSTEM_ACQUIRED_REQ_STRU
 结构说明  : HSD系统获取内部消息结构
 1.日    期   : 2014年8月7日
   作    者   : g00256031
   修改内容   : 系统获取内部消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene;
    VOS_UINT32                                              ulFreqNum;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          astFreq[CNAS_HSD_INTERNAL_SYSTEM_ACQ_REQ_CHAN_MAX_NUM];
}CNAS_HSD_HSD_SYSTEM_ACQUIRED_REQ_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU
 结构说明  : HSD系统获取结果确认消息结构
 1.日    期   : 2014年7月15日
   作    者   : C00299064
   修改内容   : 状态机结果确认消息的结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_HSD_SYSTEM_ACQUIRED_RESULT_ENUM_UINT32             enRslt;
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enCurAcqScene;
    CNAS_HSD_SYS_ACQ_FAIL_ACT_ENUM_UINT8                    enImmediateSysAcq;
    VOS_UINT8                                               aucRsved[3];
}CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_HSD_SYS_ACQ_RSLT_IND_STRU
 结构说明  : HSD获得XSD的搜网结果
 1.日    期   : 2014年7月15日
   作    者   : C00299064
   修改内容   : 状态机结果确认消息的结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_XSD_HSD_SYS_ACQ_RSLT_ENUM_UINT32                   enRlst;
    CNAS_PRL_1X_SYSTEM_STRU                                 st1xSys;
}CNAS_XSD_HSD_SYS_ACQ_RSLT_IND_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_HSD_POWER_SAVE_RSLT_CNF_STRU
 结构说明  : HSD发送POWER_SAVE确认消息结构
 1.日    期   : 2015年04月03日
   作    者   : z00316370
   修改内容   : 状态机结果确认消息的结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
}CNAS_HSD_HSD_POWER_SAVE_RSLT_CNF_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_HSD_INTER_SYS_RSLT_CNF_STRU
 结构说明  : HSD发送INTER_SYS确认消息结构
 1.日    期   : 2015年06月03日
   作    者   : z00316370
   修改内容   : 状态机结果确认消息的结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_RATMODE_ENUM_UINT32                                 enCampedRatMode;
    VOS_UINT8                                               ucRslt;
    VOS_UINT8                                               aucRsved[1];
    CAS_CNAS_HRPD_NETWORK_LOST_REASON_ENUM_UINT16           enNetworkLostReason;
}CNAS_HSD_HSD_INTER_SYS_RSLT_CNF_STRU;




#ifdef DMT
/*****************************************************************************
 结构名    : CNAS_HSD_HSD_TEST_CFG_REQ_STRU
 结构说明  : 用于DMT测试配置，配置相关的参数信息
 1.日    期   : 2015年01月29日
   作    者   : x00306642
   修改内容   : 测试配置消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT32                                              ulCurSlice;
}CNAS_HSD_HSD_TEST_CFG_REQ_STRU;
#endif

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    CNAS_HSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId;            /* _H2ASN_MsgChoice_Export CNAS_HSD_INTERNAL_MSG_TYPE_ENUM_UINT16 */

    VOS_UINT8                                               aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          CNAS_HSD_INTERNAL_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}CNAS_HSD_INTERNAL_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    CNAS_HSD_INTERNAL_MSG_DATA          stMsgData;
}CNAS_HSD_INTERNAL_MSG;



/*****************************************************************************
  10 函数声明
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID CNAS_HSD_SndPowerOffRslt(VOS_VOID);

VOS_VOID CNAS_HSD_SndSwitchOnRlst(
    VOS_UINT32                          ulResult
);

VOS_VOID CNAS_HSD_SndInternalSysAcqReq(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32  enSysAcqScene,
    VOS_UINT32                          ulFreqNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq
);

extern VOS_VOID CNAS_HSD_SndSysAcqRslt(
    CNAS_HSD_SYSTEM_ACQUIRED_RESULT_ENUM_UINT32             enResult,
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enCurAcqScene,
    CNAS_HSD_SYS_ACQ_FAIL_ACT_ENUM_UINT8                    enImmediateSysAcq
);

extern VOS_VOID CNAS_HSD_SndPowerSaveRslt(VOS_VOID);

extern VOS_VOID CNAS_HSD_SndInterSysRslt(
    VOS_RATMODE_ENUM_UINT32                                 enCampedRatMode,
    VOS_UINT8                                               ucRslt,
    CAS_CNAS_HRPD_NETWORK_LOST_REASON_ENUM_UINT16           enNetworkLostReason
);

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

#endif /* end of CnasHsdSndInternalMsg.h */
