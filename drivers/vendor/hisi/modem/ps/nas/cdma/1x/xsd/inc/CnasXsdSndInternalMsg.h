/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXsdSndInternalMsg.h
  版 本 号   : 初稿
  作    者   : h00246512
  生成日期   : 2014年7月14日
  最近修改   :
  功能描述   : CnasXsdSndInternalMsg.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年7月14日
    作    者   : h00246512
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CNAS_XSD_SND_INTERNAL_MSG_H__
#define __CNAS_XSD_SND_INTERNAL_MSG_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "CnasXsdCtx.h"
#include "CnasPrlApi.h"
#include "xsd_xreg_pif.h"
#include "cas_1x_idlectrl_proc_nas_pif.h"
#include "CnasPrlMntn.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#ifdef DMT
#define CNAS_XSD_MAX_MODIFIED_PRL_SYS_RECORD_NUM            (50)
#define CNAS_XSD_MAX_MODIFIED_PRL_ACQ_RECORD_NUM            (10)
#endif
/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : CNAS_XSD_INTERNAL_MSG_TYPE_ENUM
 枚举说明  : 内部消息名枚举定义
 1.日    期   : 2014年7月14日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
enum CNAS_XSD_INTERNAL_MSG_TYPE_ENUM
{
    ID_CNAS_XSD_XSD_ABORT_REQ                = 0x0000, /* _H2ASN_MsgChoice CNAS_XSD_XSD_ABORT_REQ_STRU*/
    ID_CNAS_XSD_XSD_SWITCH_ON_RSLT_CNF       = 0x0001, /* _H2ASN_MsgChoice CNAS_XSD_XSD_SWITCH_ON_RSLT_CNF_STRU*/
    ID_CNAS_XSD_XSD_BSR_RSLT_CNF             = 0x0002, /* _H2ASN_MsgChoice CNAS_XSD_XSD_BSR_RSLT_CNF_STRU*/
    ID_CNAS_XSD_XSD_POWER_OFF_RSLT_CNF       = 0x0003, /* _H2ASN_MsgChoice CNAS_XSD_XSD_POWER_OFF_RSLT_CNF_STRU*/
    ID_CNAS_XSD_XSD_REDIRECTION_IND          = 0x0004, /* _H2ASN_MsgChoice CNAS_XSD_XSD_REDIRECTION_IND_STRU*/
    ID_CNAS_XSD_XSD_REDIRECTION_RSLT_CNF     = 0x0005, /* _H2ASN_MsgChoice CNAS_XSD_XSD_REDIRECTION_RSLT_CNF_STRU*/
    ID_CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ      = 0x0006, /* _H2ASN_MsgChoice CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ_STRU*/
    ID_CNAS_XSD_XSD_SYSTEM_ACQUIRED_RSLT_CNF = 0x0007, /* _H2ASN_MsgChoice CNAS_XSD_XSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU*/

#ifdef DMT
    ID_CNAS_XSD_XSD_TEST_CFG_REQ,                      /* _H2ASN_MsgChoice CNAS_XSD_XSD_TEST_CFG_REQ_STRU*/
    ID_CNAS_XSD_XSD_MODIFY_PRL_SYS_RECORD_REQ,         /* _H2ASN_MsgChoice CNAS_XSD_XSD_MODIFY_PRL_SYS_RECORD_REQ_STRU*/
    ID_CNAS_XSD_XSD_MODIFY_PRL_HEAD_INFO_REQ,          /* _H2ASN_MsgChoice CNAS_XSD_XSD_MODIFY_PRL_HEAD_INFO_REQ_STRU*/
    ID_CNAS_XSD_XSD_MODIFY_OOC_SCAN_INTERVAL_REQ,          /* _H2ASN_MsgChoice CNAS_XSD_XSD_MODIFY_OOC_SCAN_INTERVAL_REQ_STRU*/
    ID_CNAS_XSD_XSD_MODIFY_PRL_ACQ_RECORD_REQ,          /* _H2ASN_MsgChoice CNAS_XSD_XSD_MODIFY_PRL_ACQ_RECORD_REQ_STRU*/
#endif

    ID_CNAS_XSD_XSD_PIF_MSG_TYPE_ENUM_BUTT   = 0xFFFF
};
typedef VOS_UINT16 CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : CNAS_XSD_BSR_RESULT_ENUM
 枚举说明  : BSR搜索结果
 1.日    期   : 2014年7月14日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
enum CNAS_XSD_BSR_RESULT_ENUM
{
    CNAS_XSD_BSR_RESULT_SUCCESS         = 0x00000000,
    CNAS_XSD_BSR_RESULT_FAILURE         = 0x00000001,
    CNAS_XSD_BSR_RESULT_ABORTED         = 0x00000002,
    CNAS_XSD_BSR_RESULT_BUTT            = 0x00000003
};
typedef VOS_UINT32 CNAS_XSD_BSR_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : CNAS_XSD_ABORT_TYPE_ENUM
 枚举说明  : Abort类型
 1.日    期   : 2014年7月14日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
enum CNAS_XSD_ABORT_TYPE_ENUM
{
    CNAS_XSD_ABORT_TYPE_IMMEDIATELY     = 0x00000000,
    CNAS_XSD_ABORT_TYPE_DELAY           = 0x00000001,
    CNAS_XSD_ABORT_TYPE_BUTT            = 0x00000002
};
typedef VOS_UINT32 CNAS_XSD_ABORT_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : CNAS_XSD_SWITCH_ON_RESULT_ENUM
 枚举说明  : 开机结果
 1.日    期   : 2014年7月14日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
enum CNAS_XSD_SWITCH_ON_RESULT_ENUM
{
    CNAS_XSD_SWITCH_ON_RESULT_SUCCESS   = 0x00000000,
    CNAS_XSD_SWITCH_ON_RESULT_FAILURE   = 0x00000001,
    CNAS_XSD_SWITCH_ON_RESULT_ABORTED   = 0x00000002,
    CNAS_XSD_SWITCH_ON_RESULT_BUTT      = 0x00000003
};
typedef VOS_UINT32 CNAS_XSD_SWITCH_ON_RESULT_ENUM_UINT32;


/* CNAS_XSD_REDIR_RESULT_ENUM_UINT32 */
/*****************************************************************************
 枚举名    : CNAS_XSD_SYSTEM_ACQUIRED_RESULT_ENUM
 枚举说明  : 系统捕获结果
 1.日    期   : 2014年7月14日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
enum CNAS_XSD_SYSTEM_ACQUIRED_RESULT_ENUM
{
    CNAS_XSD_SYSTEM_ACQUIRED_RESULT_SUCCESS                 = 0x00000000,
    CNAS_XSD_SYSTEM_ACQUIRED_RESULT_FAILURE                 = 0x00000001,
    CNAS_XSD_SYSTEM_ACQUIRED_RESULT_ABORTED                 = 0x00000002,
    CNAS_XSD_SYSTEM_ACQUIRED_RESULT_BUTT                    = 0x00000003
};
typedef VOS_UINT32 CNAS_XSD_SYSTEM_ACQUIRED_RESULT_ENUM_UINT32;


enum CNAS_XSD_REDIRECTION_RESULT_ENUM
{
    CNAS_XSD_REDIRECTION_RESULT_SUCCESS                 = 0x00000000,
    CNAS_XSD_REDIRECTION_RESULT_FAILURE                 = 0x00000001,
    CNAS_XSD_REDIRECTION_RESULT_ABORTED                 = 0x00000002,
    CNAS_XSD_REDIRECTION_RESULT_NORF                    = 0x00000004,
    CNAS_XSD_REDIRECTION_RESULT_BUTT                    = 0x00000005
};
typedef VOS_UINT32 CNAS_XSD_REDIRECTION_RESULT_ENUM_UINT32;


enum CNAS_XSD_POWEROFF_RSLT_ENUM
{
    CNAS_XSD_POWEROFF_RSLT_SUCCESS,
    CNAS_XSD_POWEROFF_RSLT_FAIL,

    CNAS_XSD_POWEROFF_RSLT_BUTT
};
typedef VOS_UINT32 CNAS_XSD_POWEROFF_RSLT_ENUM_UINT32;


enum CNAS_XSD_POWEROFF_REASON_ENUM
{
    CNAS_XSD_POWEROFF_REASON_POWER_OFF,
    CNAS_XSD_POWEROFF_REASON_POWER_SAVE,

    CNAS_XSD_POWEROFF_REASON_BUTT
};
typedef VOS_UINT32 CNAS_XSD_POWEROFF_REASON_ENUM_UINT32;


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
 结构名    : CNAS_XSD_XSD_ABORT_REQ_STRU
 结构说明  : XSD发送终止状态机消息的结构
 1.日    期   : 2014年7月15日
   作    者   : y00245242
   修改内容   : 终止状态机消息的结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                      /* _H2ASN_Skip */
    CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId;    /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_XSD_ABORT_TYPE_ENUM_UINT32                         enAbortType;
}CNAS_XSD_XSD_ABORT_REQ_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_XSD_SWITCH_ON_RSLT_CNF_STRU
 结构说明  : XSD发送开机确认消息结构
 1.日    期   : 2014年7月15日
   作    者   : y00245242
   修改内容   : 终止状态机消息的结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_XSD_SWITCH_ON_RESULT_ENUM_UINT32                   enRslt;
}CNAS_XSD_XSD_SWITCH_ON_RSLT_CNF_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_XSD_BSR_RSLT_CNF_STRU
 结构说明  : XSD发送BSR结果确认消息结构
 1.日    期   : 2014年7月15日
   作    者   : y00245242
   修改内容   : 终止状态机消息的结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_XSD_BSR_RESULT_ENUM_UINT32                         enRslt;
}CNAS_XSD_XSD_BSR_RSLT_CNF_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_XSD_POWER_OFF_RSLT_CNF_STRU
 结构说明  : XSD发送关机确认消息结构
 1.日    期   : 2014年7月15日
   作    者   : y00245242
   修改内容   : 终止状态机消息的结构
 2. Date      : 2015-04-11
    Author    : a00295761
    Content   : Added POwer off result enum to indicate if Power Off message or Power Save message
                is put in the internal message queue.
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_XSD_POWEROFF_RSLT_ENUM_UINT32                      enRslt;
    CNAS_XSD_POWEROFF_REASON_ENUM_UINT32                    enPowerOffReason;

}CNAS_XSD_XSD_POWER_OFF_RSLT_CNF_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_XSD_REDIRECTION_IND_STRU
 结构说明  : XSD发送重定向指示数据结构
 1.日    期   : 2014年7月15日
   作    者   : y00245242
   修改内容   : 终止状态机消息的结构
  2.日    期   : 2014年12月25日
    作    者   : w00176964
    修改内容   : CDMA Iteration 6 Modified
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                      /* _H2ASN_Skip */
    CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId;    /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_XSD_REDIRECTION_INFO_STRU                          stRedirectionInfo;
}CNAS_XSD_XSD_REDIRECTION_IND_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_XSD_REDIRECTION_RSLT_CNF_STRU
 结构说明  : XSD发送重定向结果确认消息结构
 1.日    期   : 2014年7月15日
   作    者   : y00245242
   修改内容   : 终止状态机消息的结构
  2.日    期   : 2014年12月25日
    作    者   : w00176964
    修改内容   : CDMA Iteration 6 Modified
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                      /* _H2ASN_Skip */
    CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId;    /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_XSD_REDIRECTION_RESULT_ENUM_UINT32                 enRslt;
}CNAS_XSD_XSD_REDIRECTION_RSLT_CNF_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ_STRU
 结构说明  : XSD系统获取内部消息结构
 1.日    期   : 2014年8月7日
   作    者   : l60609
   修改内容   : 系统获取内部消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene;
    VOS_UINT32                                              ulFreqNum;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          astFreq[CNAS_XSD_INTERNAL_SYSTEM_ACQ_REQ_CHAN_MAX_NUM];
}CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_XSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU
 结构说明  : XSD系统获取结果确认消息结构
 1.日    期   : 2014年7月15日
   作    者   : y00245242
   修改内容   : 状态机结果确认消息的结构
 2.日    期   : 2014年12月2日
   作    者   : w00176964
   修改内容   : CDMA 1X Iteration 5 Modfied
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_XSD_SYSTEM_ACQUIRED_RESULT_ENUM_UINT32             enRslt;
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32                      enCurAcqScene;
    VOS_UINT8                                               ucImmediateSysAcq;
    VOS_UINT8                                               aucRsv[3];
}CNAS_XSD_XSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU;

#ifdef DMT
/*****************************************************************************
 结构名    : CNAS_XSD_XSD_TEST_CFG_REQ_STRU
 结构说明  : 用于DMT测试配置，配置相关的参数信息
 1.日    期   : 2014年10月30日
   作    者   : y00245242
   修改内容   : 测试配置消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT32                                              ulCurSlice;
}CNAS_XSD_XSD_TEST_CFG_REQ_STRU;

/*****************************************************************************
 结构名    : CNAS_MODIFIED_PRL_SYS_RECORD_INFO_STRU
 结构说明  : 被修改的PRL系统记录信息
 1.日    期   : 2014年12月11日
   作    者   : y00245242
   修改内容   : 测试配置消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usAcqRecordIndex;
    VOS_UINT8                                               aucReserved[2];
    CNAS_PRL_MNTN_ACQ_RECORD_STRU                           stAcqRecordInfo;
}CNAS_MODIFIED_PRL_ACQ_RECORD_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_XSD_MODIFY_PRL_ACQ_RECORD_REQ_STRU
 结构说明  : 用于DMT测试, 用于修改PRL系统表中捕获record信息
 1.日    期   : 2015年1月17日
   作    者   : y00245242
   修改内容   : 测试配置消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT16                                              usRecNum;
    VOS_UINT8                                               aucReserved[2];
    CNAS_MODIFIED_PRL_ACQ_RECORD_INFO_STRU                  astAcqRecord[CNAS_XSD_MAX_MODIFIED_PRL_ACQ_RECORD_NUM];
}CNAS_XSD_XSD_MODIFY_PRL_ACQ_RECORD_REQ_STRU;

/*****************************************************************************
 结构名    : CNAS_MODIFIED_PRL_SYS_RECORD_INFO_STRU
 结构说明  : 被修改的PRL系统记录信息
 1.日    期   : 2014年12月11日
   作    者   : y00245242
   修改内容   : 测试配置消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usSysRecordIndex;
    VOS_UINT8                                               aucReserved[2];
    CNAS_PRL_EXT_SYS_RECORD_STRU                            stSysRecordInfo;
}CNAS_MODIFIED_PRL_SYS_RECORD_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_XSD_MODIFY_PRL_SYS_RECORD_REQ_STRU
 结构说明  : 用于DMT测试, 用于修改PRL系统表中system record信息
 1.日    期   : 2014年12月11日
   作    者   : y00245242
   修改内容   : 测试配置消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT16                                              usRecNum;
    VOS_UINT8                                               aucReserved[2];
    CNAS_MODIFIED_PRL_SYS_RECORD_INFO_STRU                  astSysRecord[CNAS_XSD_MAX_MODIFIED_PRL_SYS_RECORD_NUM];
}CNAS_XSD_XSD_MODIFY_PRL_SYS_RECORD_REQ_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_XSD_MODIFY_PRL_HEAD_INFO_REQ_STRU
 结构说明  : 用于DMT测试, 用于修改PRL头信息
 1.日    期   : 2014年12月11日
   作    者   : y00245242
   修改内容   : 测试配置消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               ucPreferOnly;
    CNAS_PRL_SYS_ROAMING_IND_ENUM_UINT8                     enDefRoamInd;
}CNAS_XSD_XSD_MODIFY_PRL_HEAD_INFO_REQ_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_XSD_MODIFY_PRL_HEAD_INFO_REQ_STRU
 结构说明  : 用于DMT测试, 用于修改PRL头信息
 1.日    期   : 2014年1月17日
   作    者   : c00299063
   修改内容   : 测试配置消息数据结构
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               ucInsertOrigChanFlg;        /* 在同步请求前是否插入先前驻留频点 */
    CNAS_XSD_OOC_SCAN_STRATEGY_ENUM_UINT8                   enOocScanStrategy;          /*频点重复搜索策略 */
    VOS_UINT8                                               aucReserved[2];
}CNAS_XSD_XSD_MODIFY_REPEAT_SCAN_INFO_REQ_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_XSD_MODIFY_OOC_SCAN_INTERVAL
 结构说明  : 用于DMT测试, 用于修改PRL头信息
 1.日    期   : 2014年1月17日
   作    者   : c00299063
   修改内容   : 测试配置消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               ucDoTrafficFlag;
    VOS_UINT8                                               aucReserved[3];
    CNAS_XSD_OOC_CONFIG_INFO_STRU                           stOocCfgInfo;
}CNAS_XSD_XSD_MODIFY_OOC_SCAN_INTERVAL_REQ_STRU;
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
    CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId;            /* _H2ASN_MsgChoice_Export CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16 */

    VOS_UINT8                                               aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}CNAS_XSD_INTERNAL_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    CNAS_XSD_INTERNAL_MSG_DATA          stMsgData;
}CNAS_XSD_INTERNAL_MSG;



/*****************************************************************************
  10 函数声明
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID CNAS_XSD_SndPowerOffRslt(
    CNAS_XSD_POWEROFF_RSLT_ENUM_UINT32                      enRslt,
    CNAS_XSD_POWEROFF_REASON_ENUM_UINT32                    enPowerOffReason
);

VOS_VOID CNAS_XSD_SndSwitchOnRlst(
    VOS_UINT32                          ulResult
);

VOS_VOID CNAS_XSD_SndInternalSysAcqReq(
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32  enSysAcqScene,
    VOS_UINT32                          ulFreqNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq
);

VOS_VOID CNAS_XSD_SndSysAcqRslt(
    CNAS_XSD_SYSTEM_ACQUIRED_RESULT_ENUM_UINT32             enResult,
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32                      enCurAcqScene,
    VOS_UINT8                                               ucImmediateSysAcq
);

VOS_VOID CNAS_XSD_SndInternalRedirInd(
    CNAS_XSD_REDIRECTION_INFO_STRU                          *pstRedirectionInfo
);

VOS_VOID CNAS_XSD_SndRedirRslt(
    CNAS_XSD_REDIRECTION_RESULT_ENUM_UINT32                 enResult
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

#endif /* end of CnasXsdSndInternalMsg.h */
