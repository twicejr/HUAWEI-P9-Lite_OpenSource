/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : HifiOmInterface.h
  版 本 号   : 初稿
  作    者   : 苏庄銮 59026
  生成日期   : 2011年6月20日
  最近修改   :
  功能描述   : HifiOmInterface.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年6月20日
    作    者   : 苏庄銮 59026
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "CodecInterface.h"

/* _H2ASN_Include OmCodecInterface.h */
/* _H2ASN_Include om_log.h */


#ifndef __HIFIOMINTERFACE_H__
#define __HIFIOMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/* OM-PC tool之间交互消息头, 参见CARM内部OM_APP_HEADER_STRU */
#define OM_APP_HEADER VOS_UINT16 usFuncType;    \
                      VOS_UINT16 usLength;      \
                      VOS_UINT32 ulSn;          \
                      VOS_UINT32 ulTimeStamp;

#define OM_APP_HEADER_TAIL_LEN          (8)                 /* ulSn、ulTimerStamp长度      */
#define OM_TRACE_TAIL_LEN               (4)                 /* usPrimId、usToolId长度 */
#define OM_TRANS_FUNC_TYPE              (4)                 /* 参见CARM内部OM_FUNC_ID_ENUM */
#define OM_TRACE_FUNC_TYPE              (1)                 /* 参见CARM内部OM_FUNC_ID_ENUM */
#define OM_TRANS_PRIM_ID                (0x5001)            /* 参见CARM内部OM_TRANS_PRIMID */
#define OM_TRACE_PRIM_ID                (0x8003)            /* 参见CARM内部OM_APP_TRACE_IND*/


#define HIFI_SOCP_CHANNEL_START_ADDR    (0x33ffe000U)       /*HIFI SOCP通道首地址*/
#define HIFI_SOCP_CHANNEL_LEN           (0x2000)            /*HIFI SOCP通道长度*/
#define HIFI_SOCP_FIX_CHANNEL_ID        (29)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚 举 名  : HIFI_OM_MSG_ID_ENUM
 功能描述  : 定义HiFi可维可测功能的消息
*****************************************************************************/
enum HIFI_OM_MSG_ID_ENUM
{
    ID_OM_CODEC_SET_LOG_REQ               = 0x940D,           /* 语音软件打开或者关闭调试日志*/ /* _H2ASN_MsgChoice OM_CODEC_SET_LOG_REQ_STRU */
    ID_OM_CODEC_EXT_DEF_REQ               = 0x9417,           /* 执行扩展定义指令*/             /* _H2ASN_MsgChoice OM_CODEC_EXT_DEF_REQ_STRU */

    ID_OM_CODEC_MSG_HOOK_REQ              = 0x9420,                                             /* _H2ASN_MsgChoice OM_CODEC_MSG_HOOK_REQ_STRU */
    ID_OM_CODEC_CPU_VIEW_REQ              = 0x9421,                                             /* _H2ASN_MsgChoice OM_CODEC_CPU_VIEW_REQ_STRU */
    ID_OM_CODEC_OM_CONNECT_CMD            = 0x9422,
    ID_OM_CODEC_OM_DISCONNECT_CMD         = 0xc001,

    ID_TIMER_CODEC_CPUVIEW_RPT_IND        = 0x9401,

    ID_CODEC_OM_SET_LOG_CNF               = 0x490D,           /* 响应OM_VOICE_SET_LOG_REQ*/     /* _H2ASN_MsgChoice CODEC_OM_SET_LOG_CNF_STRU */
    ID_CODEC_OM_EXT_DEF_CNF               = 0x4917,           /* 响应OM_VOICE_EXT_DEF_REQ*/     /* _H2ASN_MsgChoice CODEC_OM_EXT_DEF_CNF_STRU */

    ID_CODEC_OM_MSG_HOOK_CNF              = 0x4920,                                             /* _H2ASN_MsgChoice CODEC_OM_MSG_HOOK_CNF_STRU */
    ID_CODEC_OM_CPU_VIEW_CNF              = 0x4921,                                             /* _H2ASN_MsgChoice CODEC_OM_CPU_VIEW_CNF_STRU */

    ID_CODEC_OM_CPUVIEW_BASIC_IND         = 0x4802,                                             /* _H2ASN_MsgChoice CODEC_OM_CPUVIEW_BASIC_IND_STRU */
    ID_CODEC_OM_CPUVIEW_DETAIL_IND        = 0x4803,                                             /* _H2ASN_MsgChoice CODEC_OM_CPUVIEW_DETAIL_IND_STRU */
    ID_CODEC_OM_BUTT
};
typedef VOS_UINT16 HIFI_OM_MSG_ID_ENUM_UINT16;

enum HIFI_OM_LOG_LEVEL_ENUM
{
    ID_CODEC_OM_LOG_INFO_IND              = 0x08000000,                                         /* _H2ASN_MsgChoice _H2ASN_Skip */
    ID_CODEC_OM_LOG_NORMAL_IND            = 0x10000000,                                         /* _H2ASN_MsgChoice _H2ASN_Skip */
    ID_CODEC_OM_LOG_WARNING_IND           = 0x20000000,                                         /* _H2ASN_MsgChoice _H2ASN_Skip */
    ID_CODEC_OM_LOG_ERR_IND               = 0x40000000,                                         /* _H2ASN_MsgChoice _H2ASN_Skip */
};
typedef VOS_UINT32 HIFI_OM_LOG_LEVEL_ENUM_UINT32;

/*****************************************************************************
 枚举名    : OM_CODEC_EXT_CMD_ENUM
 枚举说明  : 扩展命令集
*****************************************************************************/
enum OM_CODEC_EXT_CMD_ENUM
{
    OM_CODEC_EXT_CMD_DEFAULT  = 0,
    OM_CODEC_EXT_ENABLE_OM,
    OM_CODEC_EXT_VQM_CMD,
    OM_CODEC_EXT_HIFI_DDR_DFS,
    OM_CODEC_EXT_AUDIO_SET_SOURCE,
    OM_CODEC_EXT_UCOM_MEM_DYN_SET_OM_FLAG,
    OM_CODEC_EXT_VOICE_DIAGNOSE_START,
    OM_CODEC_EXT_VOICE_EVRC_CODEC,
    OM_CODEC_EXT_CDMA_LOOP_ENABLE,
    OM_CODEC_EXT_CDMA_LOOP_DISABLE,
    OM_CODEC_EXT_CHANGE_MIC_DMA,
    OM_CODEC_EXT_CHANGE_SPK_DMA,
    OM_CODEC_EXT_CMD_BUT
};
typedef VOS_UINT16  OM_CODEC_EXT_CMD_ENUM_UINT16;

/*****************************************************************************
 枚举名    : OM_LOG_RPT_LEVEL_ENUM_UINT16
 枚举说明  : HIFI日志上报级别
*****************************************************************************/
enum OM_LOG_RPT_LEVEL_ENUM
{
    OM_LOG_LEVEL_INFO                   = 0 ,
    OM_LOG_LEVEL_WARNING,
    OM_LOG_LEVEL_ERROR,
    OM_LOG_LEVEL_BUTT
};
typedef VOS_UINT16 OM_LOG_RPT_LEVEL_ENUM_UINT16;

/*****************************************************************************
 枚举名    : OM_SWITCH_ENUM
 枚举说明  : 各功能使能开关
*****************************************************************************/
enum OM_SWITCH_ENUM
{
    OM_SWITCH_OFF                       = 0,                /* 关闭 */
    OM_SWITCH_ON,                                           /* 打开 */
    OM_SWITCH_BUTT
};
typedef VOS_UINT16 OM_SWITCH_ENUM_UINT16;

/*****************************************************************************
 枚举名    : OM_CPUVIEW_TARGET_ENUM
 枚举说明  : HIFI负载记录对象
*****************************************************************************/
enum OM_CPUVIEW_TARGET_ENUM
{
    OM_CPUVIEW_TARGET_TASK              = 0,                /*记录类型为任务*/
    OM_CPUVIEW_TARGET_INT               = 1,                /*记录类型为中断*/
    OM_CPUVIEW_TARGET_REGION            = 2,                /*记录类型为区域统计*/
    OM_CPUVIEW_TARGET_BUTT
};
typedef VOS_UINT8 OM_CPUVIEW_TARGET_ENUM_UINT8;

/*****************************************************************************
 枚举名    : OM_CPUVIEW_RECORD_TYPE_ENUM
 枚举说明  : HIFI负载记录动作类型
*****************************************************************************/
enum OM_CPUVIEW_ACTION_ENUM
{
    OM_CPUVIEW_ACTION_ENTER             = 0,                /*记录动作类型为进入*/
    OM_CPUVIEW_ACTION_EXIT              = 1,                /*记录动作类型为退出*/
    OM_CPUVIEW_ACTION_BUTT
};
typedef VOS_UINT8 OM_CPUVIEW_ACTION_ENUM_UINT8;

/*****************************************************************************
 实体名称  : IPC_STATUS_HIFI2CARM_ENUM
 功能描述  : 邮箱编号枚举定义
*****************************************************************************/
enum IPC_STATUS_HIFI2CARM_ENUM
{
    IPC_STATUS_HIFI2CARM_MB             = 0x1,              /* HIFI往CARM的邮箱中断 */
    IPC_STATUS_HIFI2CARM_INIT           = 0x2,              /* HIFI往CARM的启动完成中断 */
    IPC_STATUS_HIFI2CARM_PD             = 0x4,              /* HIFI往CARM的下电请求中断 */
    IPC_STATUS_HIFI2CARM_BUTT           = 0x8
};
typedef VOS_UINT16 IPC_STATUS_HIFI2CARM_ENUM_UINT16;

/*****************************************************************************
 实体名称  : COMM_VOICE_PCVOICE_DATA_DIRECTION_ENUM
 功能描述  : PC_VOICE数据流向
*****************************************************************************/
enum COMM_VOICE_PCVOICE_DATA_DIRECTION_ENUM
{
    COMM_VOICE_PCVOICE_DATA_DIRECTION_TX = 0,               /* 数据方向: USB -> COMM -> VOICE -> PHY -> 网侧 */
    COMM_VOICE_PCVOICE_DATA_DIRECTION_RX,                   /* 数据方向: USB <- COMM <- VOICE <- PHY <- 网侧 */
    COMM_VOICE_PCVOICE_DATA_DIRECTION_BUTT,
};
typedef VOS_UINT32 COMM_VOICE_PCVOICE_DATA_DIRECTION_ENUM_UINT32;

/*****************************************************************************
 实体名称  : HIFI_ERR_LOG_ALARM_ID_ENUM
 功能描述  : HIFI语音故障或告警上报ID
*****************************************************************************/
enum HIFI_ERR_LOG_ALARM_ID_ENUM
{
    HIFI_ERR_LOG_ONE_WAY_NO_SOUND     = 0x1000,
    HIFI_ERR_LOG_VOICE_CONTROL_FAULT,
    HIFI_ERR_LOG_VOICE_SUSPEND_SLOW,
    HIFI_ERR_LOG_VOICE_BSD_ALARM,
    HIFI_ERR_LOG_VOICE_BSD_ALARM_SUB,
    HIFI_ERR_LOG_VOICE_BSD_WRR_NOISE,
    HIFI_ERR_LOG_VOICE_BSD_VQI_ALARM,
    HIFI_ERR_LOG_ALARM_ID_BUTT,
};
typedef VOS_UINT16 HIFI_ERR_LOG_ALARM_ID_ENUM_UINT16;

/*****************************************************************************
 实体名称  : HFII_ERR_LOG_ALARM_LEVEL_ENUM
 功能描述  : HIFI语音故障或告警级别
*****************************************************************************/
enum HFII_ERR_LOG_ALARM_LEVEL_ENUM
{
    HIFI_ERR_LOG_ALARM_CRITICAL     = 0x01,             /* 紧急 */
    HIFI_ERR_LOG_ALARM_MAJOR,                           /* 重要 */
    HIFI_ERR_LOG_ALARM_MINOR,                           /* 次要 */
    HIFI_ERR_LOG_ALARM_WARNING,                         /* 提示 */
    HIFI_ERR_LOG_ALARM_LEVEL_BUTT,
};
typedef VOS_UINT16 HIFI_ERR_LOG_ALARM_LEVEL_ENUM_UINT16;

/*****************************************************************************
 实体名称  : HIFI_ERR_LOG_ALARM_TYPE_ENUM
 功能描述  : HIFI语音故障或告警业务类型
*****************************************************************************/
enum HIFI_ERR_LOG_ALARM_TYPE_ENUM
{
    HIFI_ERR_LOG_ALARM_COMMUNICATION = 0x00,            /* 通信 */
    HIFI_ERR_LOG_ALARM_TYPE_BUTT,
};
typedef VOS_UINT16 HIFI_ERR_LOG_ALARM_TYPE_ENUM_UINT16;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/

/*****************************************************************************
  5 消息头定义
*****************************************************************************/

/*****************************************************************************
 结构名    : OM_TRACE_HEADER_STRU
 结构说明  : TRACE消息头结构, 参见CARM内部OM_APP_TRACE_STRU
*****************************************************************************/
typedef struct
{
    OM_APP_HEADER
    VOS_UINT16                          usPrimId;           /* TRACE ID */
    VOS_UINT16                          usToolId;           /* reserve  */
}OM_TRACE_HEADER_STRU;

/*****************************************************************************
 结构名    : OM_TRANS_HEADER_STRU
 结构说明  : OM透明消息头结构, 参见CARM内部PS_OM_TRANS_IND_STRU
*****************************************************************************/
typedef struct
{
    OM_APP_HEADER
}OM_TRANS_HEADER_STRU;

/*****************************************************************************
 结构名    : OM_TRANS_PASS_HEADER_STRU
 结构说明  : OM透明消息经由CARM-OM转发头结构, 参见CARM内部PS_OM_TRANS_IND_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTransPrimId;      /* TRANS ID */
    VOS_UINT16                          usReserve;
    OM_APP_HEADER
}OM_TRANS_PASS_HEADER_STRU;

/*****************************************************************************
 实体名称  : OM_SOCP_FRAME_HEAD_STRU
 功能描述  : SOCP通道帧结构
*****************************************************************************/
typedef struct
{
    VOS_UCHAR       ucCpuId;         /* CPU范围，此处填0x5，表示Hifi */      /*_H2ASN_Skip */
    VOS_UCHAR       aucRsv[3];       /* 保留暂不涉及    */                /*_H2ASN_Skip */
    VOS_UINT32      ulRtc;           /* 32比特，后续扩展使用 */
}OM_SOCP_FRAME_HEAD_STRU;

/*****************************************************************************
 实体名称  : OM_SOCP_FRAME_SEG_STRU
 功能描述  : SOCP通道帧分段头结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16      uhwSegLen;          /*当前帧自本字段开始(含本字段)的数据长度，不含UsbTail，单位byte*/
    VOS_UCHAR       ucSegNum;           /*总的分段数:Range[1,255] 1: 没有分段 other: 段的数目，第一阶段实现时，固定填写为1，即不分段*/ /*_H2ASN_Skip */
    VOS_UCHAR       ucSegSn;            /*当前段序号:Range[1,255]*/ /*_H2ASN_Skip */
}OM_SOCP_FRAME_SEG_STRU;

/*****************************************************************************
 实体名称  : OM_SOCP_MSG_STRUs
 功能描述  : SOCP通道传输消息结构
*****************************************************************************/
/* 消息结构示意
typedef struct
{
    VOS_UINT32                          uwMagicNum;     'hisi'
    VOS_UINT16                          uhwMsgLen;      消息长度
    VOS_UINT16                          uhwReserve;
    OM_SOCP_FRAME_HEAD_STRU             stFrmHead;      OM帧头
    VOS_UINT32                          uwUsbHead;      固定为0xaaaa5555
    OM_SOCP_FRAME_SEG_STRU              stFrmSegHead;   OM帧分段头
    VOS_UINT32                          auwMsg[xxx];    具体消息内容,8字节对齐
    VOS_UINT32                          uwUsbTail;      固定为0x5555aaaa
}OM_SOCP_MSG_STRU;
*/

/*****************************************************************************
  6 消息定义
*****************************************************************************/

/*****************************************************************************
 实体名称  : OM_CODEC_SET_LOG_REQ_STRU
 功能描述  : MSG_OM_CODEC_SET_LOG_REQ消息,设置日志状态
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;           /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve1;
    OM_SWITCH_ENUM_UINT16               enLogEnable;        /* 日志使能 */
    OM_LOG_RPT_LEVEL_ENUM_UINT16        enLogLevel;         /* 日志级别 */
}OM_CODEC_SET_LOG_REQ_STRU;

/*****************************************************************************
 实体名称  : CODEC_OM_SET_LOG_CNF_STRU
 功能描述  : ID_CODEC_OM_SET_LOG_CNF消息,回复SDT设置日志状态
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwMsgId;           /*_H2ASN_Skip */
    VOS_UINT16                          uhwReserve;
    UCOM_RET_ENUM_UINT16                enReturn;           /* Request执行结果 */
    VOS_UINT16                          uhwReserve2;
}CODEC_OM_SET_LOG_CNF_STRU;

/*****************************************************************************
 实体名称  : CODEC_OM_LOG_IND_STRU
 功能描述  : ID_CODEC_OM_LOG_ERR_IND/ID_CODEC_OM_LOG_WARNING_IND/
             ID_CODEC_OM_LOG_INFO_IND消息,上报HIFI的日志消息
*****************************************************************************/
 typedef struct
{
    VOS_UINT16                          uhwMsgId;           /*_H2ASN_Skip */
    VOS_UINT16                          uhwReserve;
    VOS_UINT16                          uhwFileId;          /*_H2ASN_Replace OM_FILE_ID_ENUM_UINT16 enFileId; */
    VOS_UINT16                          uhwLineNo;
    VOS_UINT32                          uwLogId;            /*_H2ASN_Replace OM_LOG_ID_ENUM_UINT32  uwLogId; */
    VOS_INT32                           aswData[3];         /* 3个32BIT参数*/
} CODEC_OM_LOG_IND_STRU;

/*****************************************************************************
 实体名称  : OM_CODEC_CPU_VIEW_REQ_STRU
 功能描述  : 该消息请求CODEC配置是否使能负载统计、详细信息是否上报或改变负载统计上报周期
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;           /*_H2ASN_Skip */
    VOS_UINT16                          uhwReserve1;
    OM_SWITCH_ENUM_UINT16               enEnable;
    VOS_UINT16                          uhwPeriod;          /* 负载统计上报周期,取值1-5, 单位20ms */
    OM_SWITCH_ENUM_UINT16               enDetailEnable;     /* 负载统计详细信息上报开关 */
    VOS_UINT16                          uhwReserve2;
} OM_CODEC_CPU_VIEW_REQ_STRU;

/*****************************************************************************
 实体名称  : CODEC_OM_CPU_VIEW_CNF_STRU
 功能描述  : 该消息响应ID_OM_CODEC_CPU_VIEW_REQ，回应SDT
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwMsgId;           /*_H2ASN_Skip */
    VOS_UINT16                          uhwReserve;
    UCOM_RET_ENUM_UINT16                enReturn;           /* REQ执行结果 */
    VOS_UINT16                          uhwReserve2;
} CODEC_OM_CPU_VIEW_CNF_STRU;

/*****************************************************************************
 实体名称  : CODEC_OM_CPUVIEW_BASIC_IND_STRU
 功能描述  : ID_CODEC_OM_CPUVIEW_BASIC_IND消息,上报HIFI的基本负载信息
*****************************************************************************/
 typedef struct
{
    VOS_UINT16                          uhwMsgId;                               /*_H2ASN_Skip */
    VOS_UINT16                          usReserve;
    VOS_UINT32                          auwStackRate[HIFI_TASK_NUM];            /* 截至目前堆栈最大占用率, 依次为各任务栈, Q8 */
    VOS_UINT32                          auwTaskTime[HIFI_TASK_NUM];             /* 周期内任务运行时长 */
    VOS_UINT32                          auwIntrTime[HIFI_INTR_NUM];             /* 周期内中断运行时长 */
} CODEC_OM_CPUVIEW_BASIC_IND_STRU;

/*****************************************************************************
 实体名称  : OM_CPUVIEW_SLICE_RECORD_STRU
 功能描述  : 负载统计单条详细记录结构体
 *****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwTarget:2;                             /* 记录的类型, OM_CPUVIEW_TARGET_ENUM */
    VOS_UINT32                          uwTargetId:5;                           /* 任务ID或中断号或区域编号 */
    VOS_UINT32                          uwAction:1;                             /* OM_CPUVIEW_ACTION_ENUM_UINT8 */
    VOS_UINT32                          uwTimeStamp:24;                         /* 产生该记录时的时戳，取系统时戳低24bit*/
}OM_CPUVIEW_SLICE_RECORD_STRU;

/*****************************************************************************
 实体名称  : CODEC_OM_CPUVIEW_DETAIL_IND_STRU
 功能描述  : ID_CODEC_OM_CPUVIEW_DETAIL_IND消息,指示上报CPU负载详细统计
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwMsgId;                               /*_H2ASN_Skip */
    VOS_UINT16                          uhwReserve;
    VOS_UINT32                          uwRecNum;                               /* 记录条数 */
    OM_CPUVIEW_SLICE_RECORD_STRU        astRecords[1];                          /* 详细记录 */
} CODEC_OM_CPUVIEW_DETAIL_IND_STRU;

/*****************************************************************************
 实体名称  : OM_CODEC_MSG_HOOK_REQ_STRU
 功能描述  : 该消息配置CODEC是否钩取HiFi 330上交互的层间消息到SDT
 *****************************************************************************/
 typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;           /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;
    OM_SWITCH_ENUM_UINT16               enHookEnable;       /* 0-关闭, 1-打开原语钩取*/
    VOS_UINT16                          uhwReserve2;
}OM_CODEC_MSG_HOOK_REQ_STRU;

/*****************************************************************************
 实体名称  : CODEC_OM_MSG_HOOK_CNF_STRU
 功能描述  : 该消息响应ID_OM_CODEC_SET_HOOK_REQ，回应SDT
 *****************************************************************************/
 typedef struct
{
    VOS_UINT16                          uhwMsgId;           /*_H2ASN_Skip */
    VOS_UINT16                          uhwReserve;
    UCOM_RET_ENUM_UINT16                enReturn;
    VOS_UINT16                          uhwReserve2;
}CODEC_OM_MSG_HOOK_CNF_STRU;

/*****************************************************************************
 实体名称  : OM_CODEC_EXT_DEF_REQ_STRU
 功能描述  : 扩展命令消息
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;           /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;
    OM_CODEC_EXT_CMD_ENUM_UINT16          enExtCmd;           /* 扩展命令 */
    VOS_UINT16                          uhwExtLen;          /* 命令参数长度, 单位16bit */
    VOS_UINT16                          auhwExtData[2];     /* 命令参数，单元个数为uhwExtLen */
}OM_CODEC_EXT_DEF_REQ_STRU;

/*****************************************************************************
 实体名称  : CODEC_OM_EXT_DEF_CNF_STRU
 功能描述  : 回复OM_CODEC_EXT_DEF_REQ_STRU消息
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwMsgId;           /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;
    OM_CODEC_EXT_CMD_ENUM_UINT16          enExtCmd;           /* 回复的扩展命令 */
    VOS_UINT16                          uhwExtLen;          /* 回复数据长度, 单位16bit */
    VOS_UINT16                          auhwExtData[2];     /* 回复数据, 单元个数为uhwExtLen */
}CODEC_OM_EXT_DEF_CNF_STRU;

/*****************************************************************************
 实体名称  : OM_CODEC_OM_CONNECT_CMD_STRU
 功能描述  : 指示Hifi当前OM通道已连接
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;           /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;
}OM_CODEC_OM_CONNECT_CMD_STRU;

/*****************************************************************************
 实体名称  : OM_CODEC_OM_DISCONNECT_CMD_STRU
 功能描述  : 指示Hifi当前OM通道已断开
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;           /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;
}OM_CODEC_OM_DISCONNECT_CMD_STRU;


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/* RING BUFFER 保护字 */
#define COMM_VOICE_RING_BUFFER_PROTECT1 (0x55AA55AA)        /* 保护字1, 参考结构COMM_VOICE_RING_BUFFER_CONTROL_STRU */
#define COMM_VOICE_RING_BUFFER_PROTECT2 (0x5A5A5A5A)        /* 保护字2, 参考结构COMM_VOICE_RING_BUFFER_CONTROL_STRU */

/*****************************************************************************
 结构名    : COMM_VOICE_RING_BUFFER_CONTROL_STRU
 结构说明  : ring buffer控制信息结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwProtectWord1;                         /*保护字 0x55AA55AA*/
    VOS_UINT32                          uwProtectWord2;                         /*保护字 0x5A5A5A5A*/
    VOS_UINT32                          uwWriteAddr;                            /*下一个写入操作的相对地址,其指向单位为Byte*/
    VOS_UINT32                          uwReadAddr;                             /*下一个读取操作的相对地址,其指向单位为Byte*/
    VOS_UINT32                          uwBufSize;                              /*ring buffer的长度,单位byte */
    VOS_UINT32                          uwBufAddr;                              /*ring buffer的基址(实地址)*/
    VOS_UINT32                          uwProtectWord3;                         /*保护字 0x55AA55AA*/
    VOS_UINT32                          uwProtectWord4;                         /*保护字 0x5A5A5A5A*/
}COMM_VOICE_RING_BUFFER_CONTROL_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
#if 0                                                       /* _H2ASN_Skip */

/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
/* 需要更改相应的ASN编码,去掉L方式,仅保留V方式 */
typedef struct
{
    HIFI_OM_MSG_ID_ENUM_UINT16          enMsgID;            /* _H2ASN_MsgChoice_Export HIFI_OM_MSG_ID_ENUM_UINT16 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          HIFI_OM_MSG_ID_ENUM_UINT16
    ****************************************************************************/
}VOICEOM_OM_TRANS_MSG_DATA;

/* 协议消息结构*/
typedef struct
{
    VOICEOM_OM_TRANS_MSG_DATA             stMsgData;
}VoiceomOmTrans_MSG;

#endif                                                     /* _H2ASN_Skip */

/*****************************************************************************
  10 函数声明
*****************************************************************************/

/*****************************************************************************
 函 数 名  : COMM_VOICE_GetPcVoiceRingBuffCtrlAddr
 功能描述  : 获得RingBuff控制结构体的初始化
 输入参数  : enDirection - 数据方向
 输出参数  : 无
 返 回 值  : Ring Buff控制结构体的地址(虚地址)
             若Ring Buff控制结构体初始化失败则返回VOS_NULL

 补充说明  : (1) Ring Buff控制结构体内容定义为COMM_VOICE_RING_BUFFER_CONTROL_STRU
             (2) Ring Buff控制结构体全局变量定义在COMM中(应存在2个, 分别用于上行和下行两个方向)
             (3) COMM需要在调用该接口函数前或者调用该接口函数时初始化RingBuff控制结构体

*****************************************************************************/
extern VOS_UINT32 COMM_VOICE_GetPcVoiceRingBuffCtrlAddr(COMM_VOICE_PCVOICE_DATA_DIRECTION_ENUM_UINT32 enDirection);

/*****************************************************************************
 函 数 名  : COMM_VOICE_TransferPcVoiceRxData
 功能描述  : 传输下行方向数据
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK  - 传输成功
             VOS_ERR - 传输失败

 补充说明  : (1) VOICE将下行数据写入Ring Buff后调用该函数通知COMM将数据传输至USB

*****************************************************************************/
extern VOS_UINT32 COMM_VOICE_TransferPcVoiceRxData(VOS_VOID);

/*****************************************************************************
 函 数 名  : COMM_VOICE_SetPcVoiceTransferSize
 功能描述  : 设置PC Voice每帧传输的数据大小, 默认为每帧320 Byte
 输入参数  : uwSize - 每帧传输的数据大小
 输出参数  : 无
 返 回 值  : VOS_OK  - 设置成功
             VOS_ERR - 设置失败

 补充说明  : (1) 语音有宽窄带两种模式, 窄带模式下, 每帧数据大小为320Byte; 宽带模式下, 每帧数据大小为640Byte

*****************************************************************************/
extern VOS_UINT32 COMM_VOICE_SetPcVoiceTransferSize(VOS_UINT32 uwSize);


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

#endif /* end of HifiOmInterface.h */
