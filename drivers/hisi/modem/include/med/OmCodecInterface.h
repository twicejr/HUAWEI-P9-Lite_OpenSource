/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : OmCodecInterface.h
  版 本 号   : 初稿
  作    者   : gaozhendong /g00148507
  生成日期   : 2010年4月27日
  最近修改   :
  功能描述   : OM和CODEC模块间的接口文件
  函数列表   :
  修改历史   :
  1.日    期   : 2010年4月27日
    作    者   : gaozhendong /g00148507
    修改内容   : 创建文件
  2.日    期   : 2010年7月16日
    作    者   : shaodan /s00166362
    修改内容   : 修改宏命名,防止重复编译

******************************************************************************/

#ifndef __OMCODECINTERFACE_H__
#define __OMCODECINTERFACE_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "CodecInterface.h"
#include  "CodecNvInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*CODEC发送OM勾取数据同步信息指示结构体*/
#define MSG_CODEC_OM_HOOK_IND_STRU        MSG_OM_VOICE_HOOK_REQ_STRU

/* 消息码流结尾填充字 */
#define VOICE_OM_TRANS_REPLICATED_BYTES (4)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/* 消息ID定义 */
enum CODEC_OM_MSG_ID_ENUM
{
    ID_VOICE_OM_SET_HOOK_CNF              = 0x491C,           /* 响应OM_VOICE_SET_HOOK_REQ*/         /* _H2ASN_MsgChoice MSG_CODEC_CNF_STRU */
    ID_VOICE_OM_SET_LOOP_CNF              = 0x491E,           /* 响应OM_VOICE_SET_LOOP_REQ*/         /* _H2ASN_MsgChoice MSG_CODEC_CNF_STRU */

    ID_VOICE_OM_QUERY_STATUS_CNF          = 0x491F,           /* 响应OM_VOICE_QUERY_STATUS_REQ*/     /* _H2ASN_MsgChoice MSG_VOICE_OM_QUERY_RSP_STRU */
    ID_VOICE_OM_SET_NV_CNF                = 0x4918,           /* 响应OM_VOICE_SET_NV_REQ*/           /* _H2ASN_MsgChoice MSG_CODEC_CNF_STRU */
    ID_VOICE_OM_GET_NV_CNF                = 0x4919,           /* 响应OM_VOICE_GET_NV_REQ*/           /* _H2ASN_MsgChoice MSG_OM_MLIB_PARA_GET_STRU */
    ID_AUDIO_OM_SET_HOOK_CNF              = 0x491A,           /* 响应OM_AUDIO_SET_HOOK_REQ*/         /* _H2ASN_MsgChoice MSG_CODEC_CNF_STRU */
    ID_AUDIO_OM_QUERY_STATUS_CNF          = 0x491B,           /* 响应OM_AUDIO_QUERY_STATUS_REQ*/     /* _H2ASN_MsgChoice MSG_AUDIO_OM_QUERY_RSP_STRU */

    ID_VOICE_OM_SET_HOOK_IND              = 0x4922,           /* VOICE向OM发送数据勾取配置同步 */    /* _H2ASN_MsgChoice MSG_OM_VOICE_HOOK_REQ_STRU */
    ID_VOICE_OM_HOOK_IND                  = 0x4811,                                                     /* _H2ASN_MsgChoice MSG_VOICE_OM_HOOK_STRU */
    ID_AUDIO_OM_HOOK_IND                  = 0x4812,                                                     /* _H2ASN_MsgChoice MSG_AUDIO_OM_HOOK_STRU */

    ID_OM_VOICE_SET_HOOK_REQ              = 0x941C,           /* 语音软件打开或者关闭语音数据钩取*/     /* _H2ASN_MsgChoice MSG_OM_VOICE_HOOK_REQ_STRU */
    ID_OM_VOICE_SET_LOOP_REQ              = 0x941E,           /* 设置语音环回测试模式*/                 /* _H2ASN_MsgChoice MSG_OM_VOICE_LOOP_REQ_STRU */
    ID_OM_VOICE_QUERY_STATUS_REQ          = 0x941F,           /* 查询语音软件工作状态*/                 /* _H2ASN_MsgChoice MSG_VOICE_OM_QUERY_RSP_STRU */
    ID_OM_VOICE_SET_NV_REQ                = 0x9418,           /* 设置NV项*/                             /* _H2ASN_MsgChoice MSG_OM_MLIB_PARA_SET_STRU */
    ID_OM_VOICE_GET_NV_REQ                = 0x9419,           /* 获取NV项相关值*/                       /* _H2ASN_MsgChoice MSG_OM_MLIB_PARA_GET_STRU */

    ID_OM_AUDIO_SET_HOOK_REQ              = 0x941A,           /* 打开或者关闭AUDIO数据钩取 */           /* _H2ASN_MsgChoice MSG_OM_AUDIO_HOOK_REQ_STRU */
    ID_OM_AUDIO_QUERY_STATUS_REQ          = 0x941B,           /* 查询音频软件工作状态*/                 /* _H2ASN_MsgChoice MSG_AUDIO_OM_QUERY_RSP_STRU */

    ID_AUDIO_OM_SET_NV_REQ                = 0x941C,           /* 设置NV项*/                             /* _H2ASN_MsgChoice MSG_CODEC_CNF_STRU */
    ID_AUDIO_OM_GET_NV_REQ                = 0x941D,           /* 获取NV项相关值*/

    CODEC_OM_MSG_ID_BUTT
};
typedef VOS_UINT16 CODEC_OM_MSG_ID_ENUM_UINT16;

/* 事件发生场景 */
enum CODEC_ERRLOG_EVENT_MODE_ENUM
{
    CODEC_ERRLOG_EVENT_MODE_GSM                               = 0,
    CODEC_ERRLOG_EVENT_MODE_WCDMA,
    CODEC_ERRLOG_EVENT_MODE_ALL,
    CODEC_ERRLOG_EVENT_MODE_ENUM_BUTT
};
typedef VOS_UINT16 CODEC_ERRLOG_EVENT_MODE_ENUM_UINT16;

/* ErrorLog 记录的事件号 */
enum CODEC_ERRLOG_EVENTS_ENUM
{
    /* -- 硬件类别 -- */
    CODEC_ERRLOG_EVENTS_DMA_MIC_RESET                          = 0,               /* MIC DMA 重启 */
    CODEC_ERRLOG_EVENTS_DMA_SPK_RESET,                                            /* SPK DMA 重启 */

    /* -- 语音组件 -- */

    /* - WCDMA - */

    CODEC_ERRLOG_EVENTS_WCDMA_DEC_INT_LOST,                                       /* WCDMA 接受译码丢失 */
    CODEC_ERRLOG_EVENTS_WCDMA_BBP_DATA_NONE,                                      /* WCDMA BBP 上报数据为空 */
    CODEC_ERRLOG_EVENTS_WCDMA_BBP_DATA_BAD,                                       /* WCDMA BBP 上报数据为坏帧 */
    CODEC_ERRLOG_EVENTS_WCDMA_DECIPHER_LOST,                                      /* WCDMA 解密序列丢失 */

    /* - GSM - */

    CODEC_ERRLOG_EVENTS_GSM_BFI_FRAME,                                            /* GSM 收到 BFI 帧 */

    /* - ALL - */
    CODEC_ERRLOG_EVENTS_CODEC_SID_FRAME,                                          /* SID 帧 */

    /* -- PC-Voice -- */

    CODEC_ERRLOG_EVENTS_PCVOICE_INTERPOLATE,                                      /* PC Voice 插帧 */
    CODEC_ERRLOG_EVENTS_PCVOICE_RINGBUF_FULL,                                     /* PC Voice Ring Buffer 满 */

    CODEC_ERRLOG_EVENTS_ENUM_BUTT
};
typedef VOS_UINT16 CODEC_ERRLOG_EVENTS_ENUM_UINT16;

/* ErrorLog 上报的声码器信息 */
enum CODEC_ERRLOG_ENV_CODEC_ENUM
{
    /* -- WCDMA -- */

    /* AMR 475 - 122 8种速率模式 */

    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR_475                      = 0,                /* WCDMA AMR 速率模式 4.75 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR_515,                                         /* WCDMA AMR 速率模式 5.15 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR_590,                                         /* WCDMA AMR 速率模式 5.90 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR_670,                                         /* WCDMA AMR 速率模式 6.70 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR_740,                                         /* WCDMA AMR 速率模式 7.40 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR_795,                                         /* WCDMA AMR 速率模式 7.95 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR_102,                                         /* WCDMA AMR 速率模式 10.2 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR_122,                                         /* WCDMA AMR 速率模式 12.2 kbits/s */

    /* AMR2  475 - 122 8种速率模式 */

    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR2_475,                                        /* WCDMA AMR2 速率模式 4.75 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR2_515,                                        /* WCDMA AMR2 速率模式 5.15 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR2_590,                                        /* WCDMA AMR2 速率模式 5.90 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR2_670,                                        /* WCDMA AMR2 速率模式 6.70 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR2_740,                                        /* WCDMA AMR2 速率模式 7.40 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR2_795,                                        /* WCDMA AMR2 速率模式 7.95 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR2_102,                                        /* WCDMA AMR2 速率模式 10.2 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR2_122,                                        /* WCDMA AMR2 速率模式 12.2 kbits/s */

    /* -- GSM -- */

    /* AMR 475 - 122 8种速率模式 */

    CODEC_ERRLOG_ENV_CODEC_GSM_AMR_475,                                           /* GSM AMR 速率模式 4.75 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_GSM_AMR_515,                                           /* GSM AMR 速率模式 5.15 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_GSM_AMR_590,                                           /* GSM AMR 速率模式 5.90 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_GSM_AMR_670,                                           /* GSM AMR 速率模式 6.70 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_GSM_AMR_740,                                           /* GSM AMR 速率模式 7.40 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_GSM_AMR_795,                                           /* GSM AMR 速率模式 7.95 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_GSM_AMR_102,                                           /* GSM AMR 速率模式 10.2 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_GSM_AMR_122,                                           /* GSM AMR-NB 速率模式 12.2 kbits/s */

    /* EFR */
    CODEC_ERRLOG_ENV_CODEC_GSM_EFR,                                               /* GSM EFR 编码器 */

    /* FR */
    CODEC_ERRLOG_ENV_CODEC_GSM_FR,                                                /* GSM FR 编码器 */

    /* HR */
    CODEC_ERRLOG_ENV_CODEC_GSM_HR,                                                /* GSM HR 编码器 */

    /* WCDMA AMR-WB 660 - 2385 9种速率模式 */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMRWB_660,                                          /* WCDMA AMR-WB 速率模式 6.60 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMRWB_885,                                          /* WCDMA AMR-WB 速率模式 8.85 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMRWB_1265,                                         /* WCDMA AMR-WB 速率模式 12.65 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMRWB_1425,                                         /* WCDMA AMR-WB 速率模式 14.25 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMRWB_1585,                                         /* WCDMA AMR-WB 速率模式 15.85 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMRWB_1825,                                         /* WCDMA AMR-WB 速率模式 18.25 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMRWB_1985,                                         /* WCDMA AMR-WB 速率模式 19.85 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMRWB_2305,                                         /* WCDMA AMR-WB 速率模式 23.05 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMRWB_2385,                                         /* WCDMA AMR-WB 速率模式 23.85 kbits/s */

    /* GSM AMR-WB 660 - 1265 3种速率模式 */
    CODEC_ERRLOG_ENV_CODEC_GSM_AMRWB_660,                                          /* GSM AMR-WB 速率模式 6.60 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_GSM_AMRWB_885,                                          /* GSM AMR-WB 速率模式 8.85 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_GSM_AMRWB_1265,                                         /* GSM AMR-WB 速率模式 12.65 kbits/s */

    CODEC_ERRLOG_ENV_CODEC_ENUM_BUTT
};
typedef VOS_UINT16 CODEC_ERRLOG_ENV_CODEC_ENUM_UINT16;

/* 事件记录类型 */
enum CODEC_ERRLOG_EVENT_TYPE_ENUM
{
    CODEC_ERRLOG_EVENT_TYPE_TOTAL                             = 0,                /* 记录事件总数,计数大于该值上报 */
    CODEC_ERRLOG_EVENT_TYPE_REPEAT,                                               /* 记录重复事件,计数大于该值上报 */
    CODEC_ERRLOG_EVENT_TYPE_LOST,                                                 /* 记录丢失事件,计数小于该值上报 */
    CODEC_ERRLOG_EVENT_TYPE_ENUM_BUTT
};
typedef VOS_UINT16 CODEC_ERRLOG_EVENT_TYPE_ENUM_UINT16;

/* 环回测试类型 */
enum CODEC_LOOP_ENUM
{
    CODEC_LOOP_DMA                        = 0,                                    /* DMA环回 */
    CODEC_LOOP_BEFORE_CODEC,                                                      /* 编码前环回 */
    CODEC_LOOP_CODEC,                                                             /* 编码后环回 */
    CODEC_LOOP_BUTT
};
typedef VOS_UINT16  CODEC_LOOP_ENUM_UINT16;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/

/*****************************************************************************
  5 消息头定义
*****************************************************************************/
/* 发给OM的原语消息头 */
typedef struct
{
    VOS_UINT16                                              usTransPrimId;      /* 固定填写0x5100 */
    VOS_UINT16                                              usReserved;

} MSG_CODEC_OM_ERRLOG_HEAD_STRU;

/*******************************************************************************
 结构名    : MNTN_HEAD_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 记录结构头
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulInfoLen;          /* _H2ASN_Skip */ /*整个记录结构的长度,单位:字节*/
    VOS_UINT32                                              ulErrNo;            /* _H2ASN_Skip */
    VOS_UINT32                                              ulBoardtime;
    VOS_UINT32                                              ulSliceTime;
}MNTN_HEAD_INFO_STRU;

/* 上报数据至工具的附加段 */
typedef struct
{
    VOS_UINT32                                              uwSN;               /* 上报SN号 */
    VOS_UINT32                                              uwTimeStamp;        /* 上报时戳 */
} VOICE_TOOL_EX_HEAD_STRU;

/* 语音数据上报结构体 */
typedef struct
{

    VOS_UINT8                           ucFuncType;
    VOS_UINT8                           ucCpuId;
    VOS_UINT16                          usLength;
    VOICE_TOOL_EX_HEAD_STRU             stToolExHead;                                   /* 工具头 */
    VOS_UINT8                           aucHookData[VOICE_OM_TRANS_REPLICATED_BYTES];   /* 上报数据内容 */
} VOICE_OM_TRANS_STRU;

/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/

/* 环回测试结构体 */
typedef struct
{
    CODEC_SWITCH_ENUM_UINT16              enLoopEnable;                           /*环回是否打开*/
    CODEC_LOOP_ENUM_UINT16                enLoopType;                             /*环回类型*/
}CODEC_LOOP_STRU;

/*上下行输入输出配置 */
typedef struct
{
    CODEC_INOUT_ENUM_UINT16               usTxIn;                                 /*上行输入*/
    CODEC_INOUT_ENUM_UINT16               usTxOut;                                /*上行输出*/
    CODEC_INOUT_ENUM_UINT16               usRxIn;                                 /*下行输入*/
    CODEC_INOUT_ENUM_UINT16               usRxOut;                                /*下行输出*/
} CODEC_INOUT_STRU;

/*上下行输入输出配置 */
typedef struct
{
    VOS_UINT16                          uhwTxIn;                                /* 上行输入 */
    VOS_UINT16                          uhwRxOut;                               /* 下行输出 */
} CODEC_ERRLOG_INOUT_STRU;

/* 运行环境结构 */
typedef struct
{
    CODEC_ERRLOG_ENV_CODEC_ENUM_UINT16    enCodecEnv;                             /* 声码器环境信息 */
    VOS_UINT16                          auhwRes[1];                             /* 保留字 */
    CODEC_ERRLOG_INOUT_STRU               stInout;                                /* 上下行输入输出配置 */
} CODEC_ERRLOG_ENV_STRU;

/* ErrorLog 上报事件结构 */
typedef struct
{
    CODEC_ERRLOG_ENV_STRU                 stErrEnv;                               /* 上报的环境信息 */
    VOS_UINT16                          uhwErrCnt;                              /* 事件错误计数 */
    CODEC_ERRLOG_EVENT_TYPE_ENUM_UINT16   enErrType;                              /* 事件错误类别 */
} CODEC_OM_ERRLOG_EVENT_RPT_STRU;

/* ErrorLog上报结构体 */
typedef struct
{
    MSG_CODEC_OM_ERRLOG_HEAD_STRU         stOmHead;                               /* OM ErrorLog 消息头 */
    MNTN_HEAD_INFO_STRU                 stRecordHead;                           /* ErrorLog 消息头 */
    CODEC_OM_ERRLOG_EVENT_RPT_STRU        stEventRpt;                             /* ErrorLog 上报事件信息 */
} MSG_CODEC_ERRLOG_STRU;

/*****************************************************************************
 结构名    : OMMED_RING_BUFFER_CONTROL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ring buffer控制信息结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwProtectWord1;                         /*保护字 0x55AA55AA*/
    VOS_UINT32                          uwProtectWord2;                         /*保护字 0x5A5A5A5A*/
    VOS_UINT32                          uwWriteAddr;                            /*下一个写入操作的相对地址,其指向单位为Byte*/
    VOS_UINT32                          uwReadAddr;                             /*下一个读取操作的相对地址,其指向单位为Byte*/
    VOS_UINT32                          uwBufSize;                              /*ring buffer的长度,单位byte */
    VOS_UINT32                          uwReserve;
    VOS_UINT32                          uwBufAddr;                              /*ring buffer的基址*/
    VOS_UINT32                          uwProtectWord3;                         /*保护字 0x55AA55AA*/
    VOS_UINT32                          uwProtectWord4;                         /*保护字 0x5A5A5A5A*/
}OMMED_RING_BUFFER_CONTROL_STRU;


/*****************************************************************************
  7 消息定义
*****************************************************************************/

/* 语音维测指令控制结构体 */
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgId;                                /* 原语类型 */  /*_H2ASN_Skip*/
    VOS_UINT16                          uwReserve;                              /* 保留 */
}MSG_OM_VOICE_REQ_STRU;

/* 语音设备参数结构体 */
typedef struct
{
    VOS_UINT16                          usDeviceMode;                           /* 语音设备：0 手持；1 手持免提；2 车载免提；3 耳机；4 蓝牙；5 PCVOICE */
    VOS_UINT16                          usNetMode;                              /* 网络模式：0 GSM； 1 WCDMA；   3 TD */
    VOS_UINT16                          usSampleRate;                           /* 采样率  : 0 8k;   1 16k */
    VOS_UINT16                          usIndex;                                /* 拆分消息号 即ID个数 */
    VOS_INT16                           ashwNv[CODEC_PP_NV_ARRAY_ID_LEN];       /* 单个ID的NV参数数组 */
}OM_VOICE_NV_STRU;

/* 参数设置结构体 */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgName;                              /* 原语类型 */  /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* 保留 */
    VOS_UINT32                          uwPathID;                               /* 路径ID */
    VOS_UINT32                          uwModuleID;                             /* 模块ID */
    VOS_UINT32                          uwSize;                                 /* 数据大小 */
    VOS_UINT8                           aucData[4];                             /* 数据起始 */

}MSG_OM_MLIB_PARA_SET_STRU;

/* 参数获取结构体 */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgName;                              /* 原语类型 */  /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* 保留 */
    VOS_UINT32                          uwPathID;                               /* 路径ID */
    VOS_UINT32                          uwModuleID;                             /* 模块ID */
    VOS_UINT32                          uwSize;                                 /* 数据大小 */
    VOS_UINT8                           aucData[4];                             /* 数据起始 */

}MSG_OM_MLIB_PARA_GET_STRU;

/* 语音数据钩取设置原语结构体 */
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgId;                                /*原语ID*/
    VOS_UINT16                          usReserve;
    CODEC_SWITCH_ENUM_UINT16            enHookEnable;                           /*钩取数据是否打开*/
    VOS_UINT16                          usHookTarget;                           /*钩取数据目标*/
}MSG_OM_VOICE_HOOK_REQ_STRU;

/* 音频数据钩取设置原语结构体 */
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgId;                                /*原语ID*/
    VOS_UINT16                          usReserve;
    CODEC_SWITCH_ENUM_UINT16            enHookEnable;                           /*钩取数据是否打开*/
    VOS_UINT16                          usHookTarget;                           /*钩取数据目标*/
}MSG_OM_AUDIO_HOOK_REQ_STRU;

/* 语音数据钩取上报原始结构体 */
typedef struct
{
    VOS_UINT16                          usMsgId;                                /* 原语ID */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;
    VOS_UINT32                          ulFrameTick;                            /* 当前语音帧帧号     */
    VOS_UINT32                          ulTimeStamp;                            /* 当前语音帧时戳     */
    VOS_UINT16                          usHookTarget;                           /* 钩取数据目标       */
    VOS_UINT16                          usHookLength;                           /* 钩取数据长度(8bit) */
}MSG_VOICE_OM_HOOK_STRU;

/* 音频数据钩取上报原始结构体 */
typedef struct
{
    VOS_UINT16                          usMsgId;                                /* 原语ID */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;
    VOS_UINT32                          ulTimeStamp;                            /* 当前语音帧帧号     */
    VOS_UINT16                          usHookTarget;                           /* 钩取数据目标       */
    VOS_UINT16                          usHookLength;                           /* 钩取数据长度(8bit) */
}MSG_AUDIO_OM_HOOK_STRU;

/* 语音环回测试设置原语结构体 */
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgId;                                /*原语ID*/ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserved;
    CODEC_LOOP_STRU                     stLoop;                                 /*环回相关*/
}MSG_OM_VOICE_LOOP_REQ_STRU;

/* VOICE_OM_QUERY_STATUS_RSP 原始结构 */
typedef struct
{
    VOS_UINT16                          usMsgId;                                /* 原语ID */  /*_H2ASN_Skip*/
    VOS_UINT16                          usReserved1;                            /* 保留 */
    CODEC_NET_MODE_ENUM_UINT16          enNetMode;                              /* 通讯服务制式：0 G；1 W */
    CODEC_ENUM_UINT16                   enCodecType;                            /* 声码器类别：0 AMR；1 EFR；2 FR；3 HR */
    CODEC_SWITCH_ENUM_UINT16            enDtxMode;                              /* DTX使能：0 禁止；1 使能 */
    VOS_UINT16                          enAmrMode;                              /* 速率模式之一 */
    CODEC_INOUT_STRU                    stInout;                                /* 输入输出结构体 */
    VOS_UINT16                          usState;                                /* 语音软件状态 */
    VOS_UINT16                          usReserve2;                             /* 保留 */
}MSG_VOICE_OM_QUERY_RSP_STRU;

/* AUDIO_OM_QUERY_STATUS_RSP 原始结构 */
typedef struct
{
    VOS_UINT16                          usMsgId;                                /* 原语ID */  /*_H2ASN_Skip*/
    VOS_UINT16                          usReserved1;                            /* 保留 */
    AUDIO_PCM_STATUS_ENUM_UINT16        enPlayBackStatus;                       /* 播放音频通路状态 */
    VOS_UINT16                          usReserved2;                            /* 保留 */
    VOS_UINT32                          uwPlayBackSampleRate;                   /* 播放当前通道采样率 */
    VOS_UINT32                          uwPlayBackChannelNum;                   /* 播放通道的声道数 */
    AUDIO_PCM_STATUS_ENUM_UINT16        enCaptureStatus;                        /* 录音音频通路状态 */
    AUDIO_CAPTURE_MODE_ENUM_UINT16      enCaptureMode;                          /* 录音模式，仅在录音通道有效 */
    VOS_UINT32                          uwCaptureSampleRate;                    /* 录音当前通道采样率 */
    VOS_UINT32                          uwCaptureChannelNum;                    /* 录音通道的声道数 */
    VOS_UINT32                          uwEnhanceModule;                        /* 音频增强当前使用的模块 */
}MSG_AUDIO_OM_QUERY_RSP_STRU;

/* 音频设备参数结构体 */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgName;                              /* 原语类型 */  /*_H2ASN_Skip*/
    VOS_UINT16                          usDeviceMode;                           /* 语音设备：0 免提；1 耳机 */
    VOS_UINT32                          usSampleRate;                           /* 采样率   */
    VOS_UINT16                          usIndex;                                /* 拆分消息号 即ID个数 */
    VOS_INT16                           ashwNv[AUDIO_PP_NV_ARRAY_ID_LEN];       /* 单个ID的NV参数数组 */
    VOS_INT16                           shwReserved;
}MSG_OM_AUDIO_NV_REQ_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
#if 0                                                       /* _H2ASN_Skip */
/*****************************************************************************
  H2ASN生成的ASN文件需要添加
*****************************************************************************/

/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
/* 需要更改相应的ASN编码,去掉L方式,仅保留V方式 */
typedef struct
{
    CODEC_OM_MSG_ID_ENUM_UINT16           enMsgID;            /* _H2ASN_MsgChoice_Export CODEC_OM_MSG_ID_ENUM_UINT16 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          CODEC_OM_MSG_ID_ENUM_UINT16
    ****************************************************************************/
}VOICE_OM_TRANS_MSG_DATA;

/* 协议消息结构*/
typedef struct
{
    VOICE_OM_TRANS_MSG_DATA                     stMsgData;
}VoiceOmTrans_MSG;

#endif                                                     /* _H2ASN_Skip */

/*****************************************************************************
  10 函数声明
*****************************************************************************/


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

#endif /* end of VcCodecInterface.h */
