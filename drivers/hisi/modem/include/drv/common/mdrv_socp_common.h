

#ifndef __MDRV_SOCP_COMMON_H__
#define __MDRV_SOCP_COMMON_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include <product_config.h>
#include "soc_socp_adapter.h"

/**************************************************************************
  宏定义
**************************************************************************/
#define SOCP_CODER_SRC_CHAN                 0x00
#define SOCP_CODER_DEST_CHAN                0x01
#define SOCP_DECODER_SRC_CHAN               0x02
#define SOCP_DECODER_DEST_CHAN              0x03


#define SOCP_CHAN_DEF(chan_type, chan_id)   ((chan_type<<16)|chan_id)
#define SOCP_REAL_CHAN_ID(unique_chan_id)   (unique_chan_id & 0xFFFF)
#define SOCP_REAL_CHAN_TYPE(unique_chan_id) (unique_chan_id>>16)

/* 编码源通道ID枚举定义 */
/* 见soc_socp_adapter.h 中enum SOCP_CODER_SRC_ENUM枚举定义 */
typedef unsigned int SOCP_CODER_SRC_ENUM_U32;

/*解码源通道ID枚举定义*/
enum SOCP_DECODER_SRC_ENUM
{
    SOCP_DECODER_SRC_LOM        = SOCP_CHAN_DEF(SOCP_DECODER_SRC_CHAN,0),   /* LTE OM命令 */
    SOCP_DECODER_SRC_HDLC_AT    = SOCP_CHAN_DEF(SOCP_DECODER_SRC_CHAN,1),   /* HDLC编码的流式AT命令 */
    SOCP_DECODER_SRC_GUOM       = SOCP_CHAN_DEF(SOCP_DECODER_SRC_CHAN,2),   /* GU OM命令 */
    SOCP_DECODER_SRC_RFU        = SOCP_CHAN_DEF(SOCP_DECODER_SRC_CHAN,3),   /* 保留 */
    SOCP_DECODER_SRC_BUTT
};
typedef unsigned int SOCP_DECODER_SRC_ENUM_U32;

/*编码目的通道ID枚举定义*/
enum SOCP_CODER_DST_ENUM
    {
    SOCP_CODER_DST_OM_CNF        = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN,0), /* LTE OM命令响应输出 */
    SOCP_CODER_DST_OM_IND        = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN,1), /* LTE OM命令上报输出 */
    SOCP_CODER_DST_HDLC_AT       = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN,2), /* 流式AT命令响应输出 */
    SOCP_CODER_DST_RFU0          = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN,3), /* GU OM目的通道 */
    SOCP_CODER_DST_RFU1          = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN,4), /* 保留 */
    SOCP_CODER_DST_RFU2          = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN,5), /* 保留 */
    SOCP_CODER_DST_RFU3          = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN,6), /* 保留 */
    SOCP_CODER_DST_BUTT
};
typedef unsigned int SOCP_CODER_DST_ENUM_U32;

/*解码目的通道ID枚举定义*/
enum SOCP_DECODER_DST_ENUM
    {
    SOCP_DECODER_DST_LOM        = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN,0),  /* LTE OM命令 */
    SOCP_DECODER_DST_HDLC_AT    = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN,1),  /* HDLC编码的流式AT命令 */
    SOCP_DECODER_DST_GUOM       = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN,2),  /* GU OM命令 */
    SOCP_DECODER_DST_RFU        = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN,3),  /* 保留 */
    SOCP_DECODER_CBT            = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN,16), /* GU CBT */
    SOCP_DECODER_DST_BUTT
};
typedef unsigned int SOCP_DECODER_DST_ENUM_U32;

#define SOCP_CODER_SRC_CHAN_BASE            0x00000000
#define SOCP_CODER_DEST_CHAN_BASE           0x00010000
#define SOCP_DECODER_SRC_CHAN_BASE          0x00020000
#define SOCP_DECODER_DEST_CHAN_BASE         0x00030000

/**************************************************************************
  结构定义
**************************************************************************/
/* SCM使用数据结构，与V9同步 begin */
enum SOCP_BD_TYPE_ENUM
{
    SOCP_BD_DATA            = 0,    /* SOCP BD数据空间使用实际数据 */
    SOCP_BD_LIST            = 1,    /* SOCP BD数据空间使用实际数据的指针 */
    SOCP_BD_BUTT
};
typedef unsigned short SOCP_BD_TYPE_ENUM_UINT16;

enum SOCP_HDLC_FLAG_ENUM
    {
    SOCP_HDLC_ENABLE         = 0,    /* 当前HDLC功能打开 */
    SOCP_HDLC_DISABLE        = 1,    /* 当前HDLC功能关闭 */
    SOCP_HDLC_FLAG_BUTT
};

enum SOCP_STATE_ENUM
    {
    SOCP_IDLE               = 0,    /* SOCP处于空闲态 */
    SOCP_BUSY,                      /* SOCP处忙 */
    SOCP_UNKNOWN_BUTT              /*  未知状态 */
};
typedef unsigned int SOCP_STATE_ENUM_UINT32;

/* 数据类型枚举值*/
enum SCM_DATA_TYPE_ENUM
    {
    SCM_DATA_TYPE_TL            = 0,            /* LTE OAM数据 */
    SCM_DATA_TYPE_GU,                           /* GU OAM数据 */
    SCM_DATA_TYPE_BUTT
};
typedef unsigned  char SOCP_DATA_TYPE_ENUM_UIN8;
/*用于SOCP通道的BD数据片结构*/
typedef struct
{
    unsigned int                      ulDataAddr;       /* 数据的指针 */
    unsigned short                      usMsgLen;       /* 数据长度 */
    SOCP_BD_TYPE_ENUM_UINT16     enDataType;     /* 实际数据类型，是链表还是真实数据 */
}SOCP_BD_DATA_STRU;

/*用于SOCP通道的RD数据片结构*/
typedef struct
{
    unsigned int                     ulDataAddr;       /*数据指针*/
    unsigned short                     usMsgLen;       /*数据长度*/
    SOCP_BD_TYPE_ENUM_UINT16    enDataType;     /*实际数据类型，是链表还是真实数据*/
}SOCP_RD_DATA_STRU;
/* SCM使用数据结构，与V9同步 end */

enum tagSOCP_EVENT_E
{
        SOCP_EVENT_PKT_HEADER_ERROR         = 0x1,    /* 包头检测错误，"HISI" */
        SOCP_EVENT_OUTBUFFER_OVERFLOW       = 0x2,    /* 目的buffer上溢 */
        SOCP_EVENT_RDBUFFER_OVERFLOW        = 0x4,    /* RDbuffer上溢 */
        SOCP_EVENT_DECODER_UNDERFLOW        = 0x8,    /* 解码源buffer下溢 */
        SOCP_EVENT_PKT_LENGTH_ERROR         = 0x10,   /* 解码包长度检测错误 */
        SOCP_EVENT_CRC_ERROR                = 0x20,   /* 解码CRC校验错误 */
        SOCP_EVENT_DATA_TYPE_ERROR          = 0x40,   /* 解码数据类型错误*/
        SOCP_EVENT_HDLC_HEADER_ERROR        = 0x80,   /* 解码HDLC检测错误 */
        SOCP_EVENT_OUTBUFFER_THRESHOLD_OVERFLOW = 0x100, /* 目的buffer阈值溢出中断 */
        SOCP_EVENT_BUTT
};
typedef unsigned int SOCP_EVENT_ENUM_UIN32;

/* 编码源的数据结构模式 */
enum tagSOCP_ENCSRC_CHNMODE_E
{
    SOCP_ENCSRC_CHNMODE_CTSPACKET       = 0,    /* 连续数据包环形缓冲区 */
    SOCP_ENCSRC_CHNMODE_FIXPACKET,              /* 固定长度数据包环形缓冲区 */
    SOCP_ENCSRC_CHNMODE_LIST,                   /* 链式环形缓冲区 */
    SOCP_ENCSRC_CHNMODE_BUTT
};
typedef unsigned int SOCP_ENCSRC_CHNMODE_ENUM_UIN32;

/* 解码源的数据结构模式 */
enum tagSOCP_DECSRC_CHNMODE_E
{
    SOCP_DECSRC_CHNMODE_BYTES        = 0,       /* 连续字节环形缓冲区 */
    SOCP_DECSRC_CHNMODE_LIST,                   /* 链式环形缓冲区 */
    SOCP_DECSRC_CHNMODE_BUTT
};
typedef unsigned int SOCP_DECSRC_CHNMODE_ENUM_UIN32;

/* 超时选择及使能数据结构体SOCP_TIMEOUT_DECODE_TRF */
/* 2014年2月22日15:34:11 l00258701 modify add */
enum tagSOCP_TIMEOUT_EN_E
{
    SOCP_TIMEOUT_BUFOVF_DISABLE        = 0,       /* buffer溢出，不上报中断 */
    SOCP_TIMEOUT_BUFOVF_ENABLE,                   /* buffer溢出，超时计数上报中断 */
    SOCP_TIMEOUT_TRF,                             /* 传输中断超时计数 */
    SOCP_TIMEOUT_DECODE_TRF,                      /* 解码中断超时 */
    SOCP_TIMEOUT_BUTT
};
typedef unsigned int SOCP_TIMEOUT_EN_ENUM_UIN32;

/* 同一类型的通道不同优先级枚举值*/
enum tagSOCP_CHAN_PRIORITY_E
{
    SOCP_CHAN_PRIORITY_0     = 0,               /* 最低优先级*/
    SOCP_CHAN_PRIORITY_1,                       /* 次低优先级*/
    SOCP_CHAN_PRIORITY_2,                       /* 次高优先级*/
    SOCP_CHAN_PRIORITY_3,                       /* 最高优先级*/
    SOCP_CHAN_PRIORITY_BUTT
};
typedef unsigned int SOCP_CHAN_PRIORITY_ENUM_UIN32;

/* 数据类型枚举值*/
enum tagSOCP_DATA_TYPE_E
{
    SOCP_DATA_TYPE_0            = 0,            /* LTE OAM数据 */
    SOCP_DATA_TYPE_1,                           /* GU OAM数据 */
    SOCP_DATA_TYPE_2,                           /* 保留 */
    SOCP_DATA_TYPE_3,                           /* 保留 */
    SOCP_DATA_TYPE_BUTT
};
typedef unsigned int SOCP_DATA_TYPE_ENUM_UIN32;


/* BBP 数采模式，数据丢弃或覆盖 */
enum tagSOCP_BBP_DS_MODE_E
{
    SOCP_BBP_DS_MODE_DROP           = 0,        /* 数据丢弃 */
    SOCP_BBP_DS_MODE_OVERRIDE,                  /* 数据覆盖 */
    SOCP_BBP_DS_MODE_BUTT
};
typedef unsigned int SOCP_BBP_DS_MODE_ENUM_UIN32;

/* 编码源通道data type 使能位 */
enum tagSOCP_DATA_TYPE_EN_E
{
    SOCP_DATA_TYPE_EN           = 0,        /* data type 使能，默认值 */
    SOCP_DATA_TYPE_DIS,                     /* data type 不使能 */
    SOCP_DATA_TYPE_EN_BUTT
};
typedef unsigned int SOCP_DATA_TYPE_EN_ENUM_UIN32;

/* 编码源通道debug 使能位 */
enum tagSOCP_ENC_DEBUG_EN_E
{
    SOCP_ENC_DEBUG_DIS          = 0,       /* debug 不使能，默认值 */
    SOCP_ENC_DEBUG_EN,                     /* debug 使能 */
    SOCP_ENC_DEBUG_EN_BUTT
};
typedef unsigned int SOCP_ENC_DEBUG_EN_ENUM_UIN32;

/* 解码通路包长配置结构体 */
typedef struct tagSOCP_DEC_PKTLGTH_S
{
    unsigned int             u32PktMax;         /*包长度最大值*/
    unsigned int             u32PktMin;         /*包长度最小值*/
}SOCP_DEC_PKTLGTH_STRU;


/* 通用源通道buffer结构体定义*/
typedef struct
{
    unsigned  char                 *pucInputStart;      /* 输入通道起始地址*/
    unsigned  char                 *pucInputEnd;        /* 输入通道结束地址*/
    unsigned  char                 *pucRDStart;         /* RD buffer起始地址*/
    unsigned  char                 *pucRDEnd;           /* RD buffer结束地址*/
    unsigned int                 u32RDThreshold;     /* RD buffer数据上报阈值*/
    unsigned int                 ulRsv;              /* reserve */
}SOCP_SRC_SETBUF_STRU;

/* 通用目的通道buffer结构体定义*/
typedef struct
{
    unsigned  char                 *pucOutputStart;     /* 输出通道起始地址*/
    unsigned  char                 *pucOutputEnd;       /* 输出通道结束地址*/
    unsigned int                 u32Threshold;       /* 输出通道门限值 */
    unsigned int                 ulRsv;              /* reserve */
}SOCP_DST_SETBUF_STRU;

/* 编码源通道结构体定义*/
typedef struct tagSOCP_CODER_SRC_CHAN_S
{
    unsigned int                         u32DestChanID;      /* 目标通道ID*/
    unsigned int                         u32BypassEn;        /* 通道bypass使能*/
    SOCP_DATA_TYPE_ENUM_UIN32        eDataType;          /* 数据类型，指明数据封装协议，用于复用多平台*/
    SOCP_DATA_TYPE_EN_ENUM_UIN32     eDataTypeEn;        /* 数据类型使能位*/
    SOCP_ENC_DEBUG_EN_ENUM_UIN32     eDebugEn;           /* 调试位使能*/
    SOCP_ENCSRC_CHNMODE_ENUM_UIN32   eMode;              /* 通道数据模式*/
    SOCP_CHAN_PRIORITY_ENUM_UIN32    ePriority;          /* 通道优先级*/
    SOCP_SRC_SETBUF_STRU            sCoderSetSrcBuf;
}SOCP_CODER_SRC_CHAN_S;

/* 编码目的配置结构体定义*/
typedef struct tagSOCP_CODER_DEST_CHAN_S
{
    unsigned int                 u32EncDstThrh;     /* 编码目的通道阈值门限，仲裁通道时使用*/
    SOCP_DST_SETBUF_STRU       sCoderSetDstBuf;
}SOCP_CODER_DEST_CHAN_S;

/* 解码源通道结构体定义*/
typedef struct tagSOCP_DECODER_SRC_CHAN_S
{
    SOCP_DATA_TYPE_EN_ENUM_UIN32     eDataTypeEn;        /* 数据类型使能位*/
    SOCP_DECSRC_CHNMODE_ENUM_UIN32   eMode;              /* 通道模式*/
    SOCP_SRC_SETBUF_STRU       sDecoderSetSrcBuf;
}SOCP_DECODER_SRC_CHAN_STRU;

/* 解码目的通道结构体定义*/
typedef struct tagSOCP_DECODER_DEST_CHAN_S
{
    unsigned int                 u32SrcChanID;       /* 数据来源通道ID*/
    SOCP_DATA_TYPE_ENUM_UIN32        eDataType;          /* 数据类型，指明数据封装协议，用于复用多平台*/
    SOCP_DST_SETBUF_STRU       sDecoderDstSetBuf;
}SOCP_DECODER_DEST_CHAN_STRU;

/* 通用buffer描述结构体定义*/
typedef struct tagSOCP_BUFFER_RW_S
{
    char    *pBuffer;                        /* buffer指针*/
    char    *pRbBuffer;                      /* 回卷buffer指针*/
    unsigned int     u32Size;                        /* 可用buffer大小*/
    unsigned int     u32RbSize;                      /* 回卷buffer大小*/
}SOCP_BUFFER_RW_STRU;

/* 解码源通道错误计数结构体定义*/
typedef struct tagSOCP_DECODER_ERROR_CNT_S
{
    unsigned int     u32PktlengthCnt;                /* 包长检测错误计数*/
    unsigned int     u32CrcCnt;                      /* CRC校验错误计数*/
    unsigned int     u32DataTypeCnt;                 /* 解码数据类型检验错误计数*/
    unsigned int     u32HdlcHeaderCnt;               /* 0x7E校验错误*/
}SOCP_DECODER_ERROR_CNT_STRU;

/* 编码源保留通道配置结构体 */
typedef struct tagSOCP_ENCSRC_RSVCHN_SCOPE_S
{
    unsigned int                 u32RsvIDMin;        /*编码源保留通道ID最小值*/
    unsigned int                 u32RsvIDMax;        /*编码源保留通道ID最大值*/
}SOCP_ENCSRC_RSVCHN_SCOPE_STRU;

/* SOCP投票组件 */
enum SOCP_VOTE_ID_ENUM
{
    SOCP_VOTE_GU_DSP,       /* GU DSP */
    SOCP_VOTE_DIAG_APP,     /* DIAG APP,代表DRV APP */
    SOCP_VOTE_DIAG_COMM,    /* DIAG COMM,代表LDSP、DRV COMM */
    SOCP_VOTE_TL_DSP,       /* TL DSP*/
    SOCP_VOTE_SOCP_REG,     /* SOCP寄存器操作*/
    SOCP_VOTE_ID_BUTT
};
typedef unsigned int SOCP_VOTE_ID_ENUM_U32;

/* SOCP投票类型 */
enum SOCP_VOTE_TYPE_ENUM
{
    SOCP_VOTE_FOR_SLEEP,    /* 允许睡眠 */
    SOCP_VOTE_FOR_WAKE,     /* 反对睡眠 */
    SOCP_VOTE_TYPE_BUTT
};
typedef unsigned int SOCP_VOTE_TYPE_ENUM_U32;

typedef int (*socp_event_cb)(unsigned int u32ChanID, SOCP_EVENT_ENUM_UIN32 u32Event, unsigned int u32Param);
typedef int (*socp_read_cb)(unsigned int u32ChanID);
typedef int (*socp_rd_cb)(unsigned int u32ChanID);

/* log2.0 2014-03-19 Begin:*/
typedef struct SOCP_ENC_DST_BUF_LOG_CFG
{
    void*           pVirBuffer;      /* SOCP编码目的通道数据虚拟BUFFER、在32位系统上是4字节，在64位系统上是8字节 */
    unsigned long   ulPhyBufferAddr; /* SOCP编码目的通道数据物理BUFFER地址 */
    unsigned int    BufferSize;      /* SOCP编码目的通道数据BUFFER大小 */
    unsigned int    overTime;        /* NVE中设置的超时时间 */
    unsigned int    logOnFlag;       /* 底软配置buffer功能启动标志(SOCP_DST_CHAN_CFG_TYPE_ENUM) */
    unsigned int    ulCurTimeout;    /* SOCP编码目的通道数据传输超时时间 */
} SOCP_ENC_DST_BUF_LOG_CFG_STRU;
/* log2.0 2014-03-19 End*/

#define INNER_LOG_DATA_MAX                   0x40

typedef struct
{
    unsigned int                  ulSlice;
    unsigned int                  ulFileNO;
    signed int                   lLineNO;
    unsigned int                  ulP1;
    unsigned int                  ulP2;
}INNER_LOG_RECORD_STRU;

typedef struct
{
    unsigned int                  ulCnt;
    INNER_LOG_RECORD_STRU       astLogData[INNER_LOG_DATA_MAX];
}INNER_LOG_DATA_STRU;

/**************************************************************************
  函数声明
**************************************************************************/
/*****************************************************************************
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : 初始化成功的标识码
*****************************************************************************/
int DRV_SOCP_INIT(void);

/*****************************************************************************
函 数 名  : mdrv_socp_corder_set_src_chan
功能描述  : 此接口完成SOCP编码器源通道的分配，根据编码器源通道参数设置通道属性，连接目标通道，返回函数执行结果。
输入参数  : pSrcAttr:编码器源通道参数结构体指针。
     pSrcChanID:申请到的源通道ID。
*  输出参数  : 无。
*  返 回 值  : SOCP_OK:     编码源通道分配成功。
*              SOCP_ERROR:  编码源通道分配失败。
*****************************************************************************/
int mdrv_socp_corder_set_src_chan(SOCP_CODER_SRC_ENUM_U32 enSrcChanID, SOCP_CODER_SRC_CHAN_S *pSrcAttr);

/*****************************************************************************
*  函 数 名  : mdrv_socp_coder_set_dest_chan_attr
*  功能描述  : 此接口完成某一编码目标通道的配置，返回函数执行的结果。
*  输入参数  : u32DestChanID:   SOCP编码器的目标通道ID。
*                  pDestAttr:   SOCP编码器目标通道参数结构体指针。
*  输出参数  : 无。
*  返 回 值  : SOCP_OK:      编码目的通道设置成功。
*              SOCP_ERROR:   编码目的通道设置失败。
******************************************************************************/
int mdrv_socp_coder_set_dest_chan_attr(unsigned int u32DestChanID, SOCP_CODER_DEST_CHAN_S *pDestAttr);

/*****************************************************************************
*  函 数 名  : mdrv_socp_decoder_set_dest_chan
*  功能描述  : 此接口完成SOCP解码器目标通道的分配，
*              根据解码目标通道参数设置通道属性，
*              并连接源通道，返回函数执行结果。
输入参数  : pAttr:解码器目标通道参数结构体指针
     pDestChanID:申请到的目标通道ID
输出参数  : 无。
返 回 值  : SOCP_OK:解码目的通道分配成功。
     SOCP_ERROR:解码目的通道设置失败。
*****************************************************************************/
int DRV_SOCP_DECODER_SET_DEST_CHAN(SOCP_DECODER_DST_ENUM_U32 enDestChanID, SOCP_DECODER_DEST_CHAN_STRU *pAttr);

/*****************************************************************************
函 数 名  : DRV_SOCP_DECODER_SET_SRC_CHAN_ATTR
功能描述  : 此接口完成某一解码源通道的配置，返回函数执行的结果。
输入参数  : u32SrcChanID:解码器源通道ID
     pInputAttr:解码器源通道参数结构体指针
输出参数  : 无。
返 回 值  : SOCP_OK:解码源通道设置成功
     SOCP_ERROR:解码源通道设置失败
*****************************************************************************/
int DRV_SOCP_DECODER_SET_SRC_CHAN_ATTR ( unsigned int u32SrcChanID,SOCP_DECODER_SRC_CHAN_STRU *pInputAttr);

/*****************************************************************************
函 数 名  : DRV_SOCP_DECODER_GET_ERR_CNT
功能描述  :此接口给出解码通道中四种异常情况的计数值。
输入参数  : u32ChanID:解码器通道ID
                 pErrCnt:解码器异常计数结构体指针
输出参数  : 无。
返 回 值      : SOCP_OK:返回异常计数成功
                     SOCP_ERROR:返回异常计数失败
*****************************************************************************/
int DRV_SOCP_DECODER_GET_ERR_CNT (unsigned int u32ChanID, SOCP_DECODER_ERROR_CNT_STRU *pErrCnt);

/*****************************************************************************
函 数 名  : DRV_SOCP_FREE_CHANNEL
功能描述  : 此接口根据通道ID释放分配的编解码通道。
输入参数  : u32ChanID:通道ID。
输出参数  : 无。
返 回 值  : SOCP_OK:通道释放成功。
     SOCP_ERROR:通道释放失败。
*****************************************************************************/
int DRV_SOCP_FREE_CHANNEL(unsigned int u32ChanID);

/*****************************************************************************
* 函 数 名  : DRV_SOCP_CLEAN_ENCSRC_CHAN
*
* 功能描述  : 清空编码源通道，同步V9 SOCP接口
*
* 输入参数  : enSrcChanID       编码通道号
*
* 输出参数  : 无
*
* 返 回 值  : BSP_OK
*****************************************************************************/
unsigned int DRV_SOCP_CLEAN_ENCSRC_CHAN(SOCP_CODER_SRC_ENUM_U32 enSrcChanID);
#define SOCP_CleanEncSrcChan(enSrcChanID)  DRV_SOCP_CLEAN_ENCSRC_CHAN(enSrcChanID)

/*****************************************************************************
函 数 名  : DRV_SOCP_REGISTER_EVENT_CB
功能描述  : 此接口为给定通道注册事件回调函数。
输入参数  : u32ChanID:通道ID。
     EventCB:事件回调函数，参考socp_event_cb函数定义
输出参数  : 无。
返 回 值  : SOCP_OK:注册事件回调函数成功。
     SOCP_ERROR:注册事件回调函数失败。
*****************************************************************************/
int DRV_SOCP_REGISTER_EVENT_CB(unsigned int u32ChanID, socp_event_cb EventCB);

/*****************************************************************************
函 数 名  : mdrv_socp_start
功能描述  : 此接口用于源通道，启动编码或者解码。
输入参数  : u32SrcChanID:源通道ID。
输出参数  : 无。
返 回 值  : SOCP_OK:编码或解码启动成功。
      SOCP_ERROR:编码或解码启动失败。
*****************************************************************************/
int mdrv_socp_start(unsigned int u32SrcChanID);

/*****************************************************************************
函 数 名  : mdrv_socp_stop
功能描述  : 此接口用于源通道，停止编码或者解码。
输入参数  : u32SrcChanID:源通道ID。
输出参数  : 无。
返 回 值  : SOCP_OK:编码或解码停止成功。
     SOCP_ERROR:编码或解码停止失败。
*****************************************************************************/
int mdrv_socp_stop(unsigned int u32SrcChanID);
static inline void SOCP_Stop1SrcChan(unsigned int u32SrcChanID)
{
    (void)mdrv_socp_stop(u32SrcChanID);
}

/*****************************************************************************
函 数 名  : DRV_SOCP_SET_TIMEOUT
功能描述  : 此接口设置超时阈值。
输入参数  : u32Timeout:超时阈值

输出参数  : 无。
返 回 值  : SOCP_OK:设置超时时间阈值成功。
     SOCP_ERROR:设置超时时间阈值失败
*****************************************************************************/
int DRV_SOCP_SET_TIMEOUT (SOCP_TIMEOUT_EN_ENUM_UIN32 eTmOutEn, unsigned int u32Timeout);

/*****************************************************************************
函 数 名  : DRV_SOCP_SET_DEC_PKT_LGTH
功能描述  : 设置解码包长度极限值
输入参数  : pPktlgth:解码包长度极值

输出参数  : 无。
返 回 值  : SOCP_OK:设置成功。
     其他值:设置失败
*****************************************************************************/
int DRV_SOCP_SET_DEC_PKT_LGTH(SOCP_DEC_PKTLGTH_STRU *pPktlgth);

/*****************************************************************************
函 数 名  : DRV_SOCP_SET_DEBUG
功能描述  : 设置解码源通道的debug模式
输入参数  : u32ChanID:通道ID
     u32DebugEn: debug标识
输出参数  : 无。
返 回 值  : SOCP_OK:设置成功。
     其他值:设置失败
*****************************************************************************/
int DRV_SOCP_SET_DEBUG(unsigned int u32DestChanID, unsigned int u32DebugEn);

/*****************************************************************************
函 数 名  : DRV_SOCP_CHAN_SOFT_RESET
功能描述  : 源通道软复位
输入参数  : u32ChanID:通道ID
输出参数  : 无。
返 回 值  : SOCP_OK:设复位成功。
     其他值:复位失败
*****************************************************************************/
int DRV_SOCP_CHAN_SOFT_RESET(unsigned int u32ChanID);

/*****************************************************************************
函 数 名  : mdrv_socp_get_write_buff
功能描述  : 此接口用于获取写数据buffer。
输入参数  : u32SrcChanID:源通道ID
     pBuff:           :写数据buffer

输出参数  : 无。
返 回 值  : SOCP_OK:获取写数据buffer成功。
     SOCP_ERROR:获取写数据buffer失败
*****************************************************************************/
int mdrv_socp_get_write_buff( unsigned int u32SrcChanID, SOCP_BUFFER_RW_STRU *pBuff);

/*****************************************************************************
函 数 名  : mdrv_socp_write_done
功能描述  : 该接口用于数据的写操作，提供写入数据的长度。
输入参数  : u32SrcChanID:源通道ID
     u32WrtSize:   已写入数据的长度
输出参数  : 无。
返 回 值  : SOCP_OK:写入数据成功。
       SOCP_ERROR:写入数据失败
*****************************************************************************/
int mdrv_socp_write_done(unsigned int u32SrcChanID, unsigned int u32WrtSize);

/*****************************************************************************
函 数 名  : mdrv_socp_register_rd_cb
功能描述  : 该接口用于注册从RD缓冲区中读取数据的回调函数。
输入参数  : u32SrcChanID:源通道ID
     RdCB:  事件回调函数
输出参数  : 无。
返 回 值  : SOCP_OK:注册RD环形缓冲区读数据回调函数成功。
     SOCP_ERROR:注册RD环形缓冲区读数据回调函数失败
*****************************************************************************/
int DRV_SOCP_REGISTER_RD_CB(unsigned int u32SrcChanID, socp_rd_cb RdCB);

/*****************************************************************************
函 数 名  : mdrv_socp_get_rd_buffer
功能描述  : 该此接口用于获取RD buffer的数据指针。
输入参数  : u32SrcChanID:源通道ID
     pBuff:  RD buffer
输出参数  : 无。
返 回 值  : SOCP_OK:获取RD环形缓冲区成功
     SOCP_ERROR:获取RD环形缓冲区失败
*****************************************************************************/
int mdrv_socp_get_rd_buffer( unsigned int u32SrcChanID,SOCP_BUFFER_RW_STRU *pBuff);


/*****************************************************************************
函 数 名  : bsp_socp_read_rd_done
功能描述  : 此接口用于上层通知SOCP驱动，从RD buffer中实际读取的数据。
输入参数  : u32SrcChanID:源通道ID
      u32RDSize:  从RD buffer中实际读取的数据长度
输出参数  : 无。
返 回 值  : SOCP_OK:读取RDbuffer中的数据成功
      SOCP_ERROR:读取RDbuffer中的数据失败
*****************************************************************************/
int mdrv_socp_read_rd_done(unsigned int u32SrcChanID, unsigned int u32RDSize);

/*****************************************************************************
函 数 名  : bsp_socp_register_read_cb
功能描述  : 该接口用于注册读数据的回调函数。
输入参数  : u32DestChanID:目标通道ID
     ReadCB: 事件回调函数
输出参数  : 无。
返 回 值  : SOCP_OK:注册读数据回调函数成功
     SOCP_ERROR:注册读数据回调函数失败
*****************************************************************************/
int DRV_SOCP_REGISTER_READ_CB( unsigned int u32DestChanID, socp_read_cb ReadCB);
#define BSP_SOCP_RegisterReadCB(u32DestChanID,ReadCB)  \
    DRV_SOCP_REGISTER_READ_CB(u32DestChanID,ReadCB)

/*****************************************************************************
函 数 名  : DRV_SOCP_GET_READ_BUFF
功能描述  : 该此接口用于获取读数据缓冲区指针。
输入参数  : u32DestChanID:目标通道ID
     ReadCB: 读数据buffer
输出参数  : 无。
返 回 值  : SOCP_OK:获取读数据缓冲区成功。
     SOCP_ERROR:获取读数据缓冲区成功。
*****************************************************************************/
int DRV_SOCP_GET_READ_BUFF(unsigned int u32DestChanID,SOCP_BUFFER_RW_STRU *pBuffer);
#define BSP_SOCP_GetReadBuff(u32SrcChanID,pBuff)  \
        DRV_SOCP_GET_READ_BUFF(u32SrcChanID,pBuff)

/*****************************************************************************
函 数 名  : DRV_SOCP_READ_DATA_DONE
功能描述  : 该接口用于上层告诉SOCP驱动，从目标通道中读走的实际数据。
输入参数  : u32DestChanID:目标通道ID
     u32ReadSize: 已读出数据的长度
输出参数  : 无。
返 回 值  : SOCP_OK:读数据成功。
     SOCP_ERROR:读数据失败
*****************************************************************************/
int DRV_SOCP_READ_DATA_DONE(unsigned int u32DestChanID,unsigned int u32ReadSize);
#define BSP_SOCP_ReadDataDone(u32DestChanID,u32ReadSize) \
        DRV_SOCP_READ_DATA_DONE(u32DestChanID,u32ReadSize)

/*****************************************************************************
函 数 名  : DRV_SOCP_SET_BBP_ENABLE
功能描述  : 使能或停止BBP通道。
输入参数  : bEnable:通道ID
输出参数  : 无。
返 回 值      : SOCP_OK:设置成功。
           其他值:设置失败
*****************************************************************************/
int DRV_SOCP_SET_BBP_ENABLE(int bEnable);

/*****************************************************************************
函 数 名  : DRV_SOCP_SET_BBP_DS_MODE
功能描述  : 设置BBP DS通道数据溢出处理模式。
输入参数  : eDsMode:DS通道数据溢出时处理模式设置
输出参数  : 无。
返 回 值      : SOCP_OK:设置成功。
           其他值:设置失败
*****************************************************************************/
int DRV_SOCP_SET_BBP_DS_MODE(SOCP_BBP_DS_MODE_ENUM_UIN32 eDsMode);

/*****************************************************************************
* 函 数 名  : DRV_SOCP_DSPCHN_START
* 功能描述  : enable DSP channel
* 输入参数  :
* 输出参数  : 无
* 返 回 值  :
*****************************************************************************/
void  DRV_SOCP_DSPCHN_START(void);


/*****************************************************************************
* 函 数 名  : DRV_SOCP_DSPCHN_STOP
* 功能描述  : disable DSP channel
* 输入参数  :
* 输出参数  : 无
* 返 回 值  :
*****************************************************************************/
void  DRV_SOCP_DSPCHN_STOP(void);

/*****************************************************************************
* 函 数 名  : DRV_SOCP_GET_STATE
*
* 功能描述  : 获取SOCP状态
*
* 返 回 值  : SOCP_IDLE    空闲
*             SOCP_BUSY    忙碌
*****************************************************************************/
SOCP_STATE_ENUM_UINT32  DRV_SOCP_GET_STATE(void);

/*****************************************************************************
* 函 数 名  : DRV_BBPDMA_DRX_BAK_REG
* 功能描述  : BBPDMA备份
* 输入参数  :
* 输出参数  : 无
* 返 回 值  :
*****************************************************************************/
int  DRV_BBPDMA_DRX_BAK_REG(void);

/*****************************************************************************
* 函 数 名  : DRV_BBPDMA_DRX_RESTORE_REG
* 功能描述  : 恢复BBPDMA
* 输入参数  :
* 输出参数  : 无
* 返 回 值  :
*****************************************************************************/
int  DRV_BBPDMA_DRX_RESTORE_REG(void);

/*****************************************************************************
* 函 数 名  : mdrv_socp_get_sd_logcfg
* 功能描述  : 查询刷新后LOG2.0 SOCP超时配置信息
* 输入参数  : 无
* 输出参数  : 无
* 返 回 值  : SOCP_ENC_DST_BUF_LOG_CFG_STRU指针
*****************************************************************************/
unsigned int mdrv_socp_get_sd_logcfg(SOCP_ENC_DST_BUF_LOG_CFG_STRU* cfg);
/*****************************************************************************
* 函 数 名  : mdrv_socp_set_log_int_timeout
* 功能描述  : 使用CMD LINE中的超时时间来设置LOG2.0 SOCP超时配置
* 输入参数  : 无
* 输出参数  : 无
* 返 回 值  : 无
*****************************************************************************/
void mdrv_socp_set_log_int_timeout(void);
/*****************************************************************************
* 函 数 名  : mdrv_socp_set_log_int_default_timeout
* 功能描述  : 使用默认的超时时间来设置LOG2.0 SOCP超时配置
* 输入参数  : 无
* 输出参数  : 无
* 返 回 值  : 无
*****************************************************************************/
void mdrv_socp_set_log_int_default_timeout(void);

unsigned int  DRV_SOCP_INIT_LTE_DSP(unsigned int ulChanId,unsigned int ulPhyAddr,unsigned int ulSize);

unsigned int  DRV_SOCP_INIT_LTE_BBP_LOG(unsigned int ulChanId,unsigned int ulPhyAddr,unsigned int ulSize);

unsigned int  DRV_SOCP_INIT_LTE_BBP_DS(unsigned int ulChanId,unsigned int ulPhyAddr,unsigned int ulSize);

void DRV_SOCP_ENABLE_LTE_BBP_DSP(unsigned int ulChanId);

void BSP_SOCP_RefreshSDLogCfg(unsigned int ulTimerLen);

/*****************************************************************************
* 函 数 名  : mdrv_socp_set_autodiv_enalbe
*
* 功能描述  : 使能SOCP的自动降频
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : 无
*****************************************************************************/
void mdrv_socp_enalbe_dfs(void);

/*****************************************************************************
* 函 数 名  : mdrv_socp_set_autodiv_disalbe
*
* 功能描述  : 去使能SOCP的自动降频
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : 无
*****************************************************************************/
void mdrv_socp_disalbe_dfs(void);

/*****************************************************************************
* 函 数 名  : DRV_SOCP_VOTE
* 功能描述  : SOCP投票接口，根据投票结果决定SOCP是否睡眠，该接口只在A核提供
* 输入参数  : id --- 投票组件ID，type --- 投票类型
* 输出参数  : 无
* 返 回 值  : int 0 --- 投票成功，0xFFFFFFFF --- 投票失败
*****************************************************************************/
int DRV_SOCP_VOTE(SOCP_VOTE_ID_ENUM_U32 id, SOCP_VOTE_TYPE_ENUM_U32 type);

/*****************************************************************************
* 函 数 名  : DRV_SOCP_VOTE_TO_MCORE
* 功能描述  : SOCP投票接口，该接口只在C核提供，适配LDSP首次加载的SOCP上电需求
* 输入参数  : type --- 投票类型
* 输出参数  : 无
* 返 回 值  : int 0 --- 投票成功，0xFFFFFFFF --- 投票失败
*****************************************************************************/
int DRV_SOCP_VOTE_TO_MCORE(SOCP_VOTE_TYPE_ENUM_U32 type);



#ifdef __cplusplus
}
#endif
#endif //__MDRV_SOCP_COMMON_H__
