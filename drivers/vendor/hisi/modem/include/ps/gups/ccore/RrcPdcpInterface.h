/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : RrcPdcpInterface.h
  版 本 号   : 初稿
  作    者   : Jinying
  生成日期   : 2006年9月1日
  最近修改   :
  功能描述   : RrcPdcpInterface.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2006年9月1日
    作    者   : Jinying
    修改内容   : 创建文件

******************************************************************************/

#ifndef __RRCPDCPINTERFACE_H__
#define __RRCPDCPINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "PsTypeDef.h"
#include "WUeSpec.h"

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
enum RRC_PDCP_MSG_TYPE_ENUM
{
    ID_RRC_PDCP_CONFIG_REQ          = 0x0000,   /* _H2ASN_MsgChoice RRC_PDCP_CONFIG_REQ_STRU   */
    ID_PDCP_RRC_CONFIG_CNF          = 0x0001,   /* _H2ASN_MsgChoice PDCP_RRC_CONFIG_CNF_STRU   */
    ID_RRC_PDCP_RELEASE_REQ         = 0x0002,   /* _H2ASN_MsgChoice RRC_PDCP_RELEASE_REQ_STRU  */
    ID_PDCP_RRC_RELEASE_CNF         = 0x0003,   /* _H2ASN_MsgChoice PDCP_RRC_RELEASE_CNF_STRU  */
    ID_RRC_PDCP_SYNC_REQ            = 0x0004,   /* _H2ASN_MsgChoice RRC_PDCP_SYNC_REQ_STRU     */
    ID_PDCP_RRC_SYNC_CNF            = 0x0005,   /* _H2ASN_MsgChoice PDCP_RRC_SYNC_CNF_STRU     */
    ID_RRC_PDCP_STOP_REQ            = 0x0006,   /* _H2ASN_MsgChoice RRC_PDCP_STOP_REQ_STRU     */
    ID_PDCP_RRC_STOP_CNF            = 0x0007,   /* _H2ASN_MsgChoice PDCP_RRC_STOP_CNF_STRU     */
    ID_RRC_PDCP_CONTINUE_REQ        = 0x0008,   /* _H2ASN_MsgChoice RRC_PDCP_CONTINUE_REQ_STRU  */
    ID_PDCP_RRC_CONTINUE_CNF        = 0x0009,   /* _H2ASN_MsgChoice PDCP_RRC_CONTINUE_CNF_STRU  */
    ID_RRC_PDCP_RELOC_REQ           = 0x000A,   /* _H2ASN_MsgChoice RRC_PDCP_RELOC_REQ_STRU       */
    ID_PDCP_RRC_RELOC_CNF           = 0x000B,   /* _H2ASN_MsgChoice PDCP_RRC_RELOC_CNF_STRU    */
    ID_RRC_PDCP_DLSIZE_CHANGE_REQ   = 0x000C,   /* _H2ASN_MsgChoice RRC_PDCP_DLSIZE_CHANGE_REQ_STRU */
    ID_PDCP_RRC_DLSIZE_CHANGE_CNF   = 0x000D,   /* _H2ASN_MsgChoice PDCP_RRC_DLSIZE_CHANGE_CNF_STRU */
    ID_RRC_PDCP_COMPRESS_INI_REQ    = 0x000E,   /* _H2ASN_MsgChoice RRC_PDCP_COMPRESS_INI_REQ_STRU  */
    ID_PDCP_RRC_COMPRESS_INI_CNF    = 0x000F,   /* _H2ASN_MsgChoice PDCP_RRC_COMPRESS_INI_CNF_STRU  */
    ID_PDCP_RRC_ERROR_IND           = 0x0011,   /* _H2ASN_MsgChoice PDCP_RRC_ERROR_IND_STRU    */

    ID_PDCP_RRC_MSG_TYPE_BUTT
};
typedef VOS_UINT16 RRC_PDCP_MSG_TYPE_ENUM_UINT16;

/*****************************************************************************
 结构名    : RRC_PDCP_CFG_MODE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : PDCP配置模式，是初始配置还是重配: 取值为PDCP_INIT_MODE等宏定义
*****************************************************************************/
enum RRC_PDCP_CFG_MODE_ENUM
{
    RRC_PDCP_CFG_MODE_SETUP             = 0,
    RRC_PDCP_CFG_MODE_RECFG             = 1,
    RRC_PDCP_CFG_MODE_BUTT
};
typedef VOS_UINT8   RRC_PDCP_CFG_MODE_ENUM_UINT8;

/*****************************************************************************
 结构名    : PDCPITF_RLC_MODE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : PDCP对应的RLC德模式
*****************************************************************************/
enum PDCPITF_RLC_MODE_ENUM
{
    PDCPITF_RLC_AM_IN_SEQ               = 0,
    PDCPITF_RLC_AM_OUT_OF_SEQ           = 1,
    PDCPITF_RLC_UM_MODE                 = 2,
    PDCPITF_RLC_TM_MODE                 = 3,

    PDCPITF_RLC_MODE_BUTT
};
typedef VOS_UINT8   PDCPITF_RLC_MODE_ENUM_UINT8;

/*****************************************************************************
 结构名    : PDCPITF_RSLT_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : PDCP配置返回值
*****************************************************************************/
enum PDCPITF_RSLT_ENUM
{
    PDCPITF_SUCC                    = 0,
    PDCPITF_FAIL                       ,
    PDCPITF_RSLT_BUTT
};
typedef VOS_UINT32 PDCPITF_RSLT_ENUM_UINT32;

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
 结构名    : PDCPITF_RFC2507_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 压缩算法RFC_2507定义
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucFMaxTime;         /* INTEGER(1..255)  DEFAULT(5),全头之间发送压缩头的最大时间 */
    VOS_UINT8                           ucTcpSpace;         /* INTEGER(3..255)  DEFAULT(15),TCP连接的最大CID值 */
    VOS_UINT16                          usFMaxPeriod;       /* INTEGER(1..65535)  DEFAULT(256),全头之间发送压缩头的最大个数 */
    VOS_UINT16                          usMaxHeader;        /* INTEGER(60..65535)  DEFAULT(168),可以被压缩的最大头的长度 */
    VOS_UINT16                          usNonTcpSpace;      /* INTEGER(3..65535)  DEFAULT(15),非TCP连接的最大CID值  */
    PS_BOOL_ENUM_UINT8                  enExpReord;         /* ENUMERATED ,算法是否支持重排序*/
    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
}PDCPITF_RFC2507_INFO_STRU;

/*****************************************************************************
 结构名    : PDCPITF_COMPRS_ALG_CHOICE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PDCP信息定义
*****************************************************************************/
typedef struct
{
    /* PDCP 支持的算法类型 */
    #define    PDCPITF_HEAD_COMPRS_RFC2507_CHOSEN    0
    #define    PDCPITF_HEAD_COMPRS_RFC3095_CHOSEN    1

    VOS_UINT32                          ulAlgChoice;        /* 采用的压缩算法 */
    union
    {
        PDCPITF_RFC2507_INFO_STRU       stRfc2507Info;
        PS_NULL_STRU                    stRfc3095Info;
    }u;                                                     /* 可供选择的压缩算法 */
}PDCPITF_COMPRS_ALG_CHOICE_STRU;

/*****************************************************************************
 结构名    : PDCPITF_PDCP_INFO_STRU
 协议表格  :
 ASN.1描述 : PDCP_Info_r4
 结构说明  :
*****************************************************************************/
typedef struct
{
    /* ASN.1 文本 : LosslessSRNS-RelocSupport */
    PS_BOOL_ENUM_UINT8                  enSprtLossless;             /* [TRUE,FALSE]是否支持lossless SRNS relocation的标志 */
    /* ASN.1 文本 : PDCP-PDU-Header */
    PS_BOOL_ENUM_UINT8                  enPdcpPduHead;              /* [TRUE,FALSE]是否有PDCP PDU header的标志 */
    VOS_UINT16                          usMaxPdcpWndSize;           /* sn255, sn65535,支持无损时才携带，[0, PDCP_MAX_SND_WIN] 最大的PDCP SN window size */
    /* ASN.1 文本 : HeaderCompressionInfoList-r4 */
    VOS_UINT8                           aucReserve1[2];             /* 4字节对齐，保留 */
    VOS_UINT16                          usCnt;                      /* [0,PS_WUE_MAX_PDCP_ALGO_TYPE_NUM]压缩算法个数                            */
    PDCPITF_COMPRS_ALG_CHOICE_STRU      astHeadComprs[PS_WUE_MAX_PDCP_ALGO_TYPE_NUM];
}PDCPITF_PDCP_INFO_STRU;

/*****************************************************************************
 结构名    : RRC_PDCP_CONFIG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_PDCP_CONFIG_REQ 定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */    /*_H2ASN_Skip*/
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* 消息类型 */  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* 操作号,与应答原语对应 */
    VOS_UINT8                           ucRbId;             /* 唯一标志PDCP实体 */
    RRC_PDCP_CFG_MODE_ENUM_UINT8        enCfgMode;          /* PDCP配置模式，是配置还是重配 */
    PDCPITF_RLC_MODE_ENUM_UINT8         enRlcMode;          /* PDCP实体数据传输采用的的RLC模式 */
    PS_BOOL_ENUM_UINT8                  enPPPFlg;           /* TRUE是ppp头, FALSE:不是ppp头 */
    PDCPITF_PDCP_INFO_STRU              stPdcpInfo;         /* PDCP实体信息 */
}RRC_PDCP_CONFIG_REQ_STRU;


/*****************************************************************************
 结构名    : PDCP_RRC_CONFIG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PDCP_RRC_CONFIG_CNF 定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */    /*_H2ASN_Skip*/
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* 消息类型 */  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* 操作号,与命令原语对应 */
    PDCPITF_RSLT_ENUM_UINT32            enRslt;             /* 配置结果 */
}PDCP_RRC_CONFIG_CNF_STRU;

/*****************************************************************************
 结构名    : RRC_PDCP_RELEASE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_PDCP_RELEASE_REQ定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */    /*_H2ASN_Skip*/
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* 消息类型 */  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* 操作号,与命令原语对应 */
    VOS_UINT8                           ucRbCnt;            /* [0, PDCP_MAX_ENT_NUM],释放的PDCP实体数，0表明释放所有的PDCP实体 */
    VOS_UINT8                           aucRbId[PS_WUE_MAX_PS_RB_NUM];   /* 标志PDCP实体 */
    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留 */
}RRC_PDCP_RELEASE_REQ_STRU;


/*****************************************************************************
 结构名    : PDCP_RRC_RELEASE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PDCP_RRC_RELEASE_CNF定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */    /*_H2ASN_Skip*/
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* 消息类型 */  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* 操作号,与命令原语对应 */
    PDCPITF_RSLT_ENUM_UINT32            enRslt;
}PDCP_RRC_RELEASE_CNF_STRU;

/*****************************************************************************
 结构名    : RRC_PDCP_SYNC_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_PDCP_SYNC_REQ定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */    /*_H2ASN_Skip*/
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* 消息类型 */  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* 操作号,与命令原语对应 */
    VOS_UINT8                           ucRbCnt;            /* [0, UU_MAX_RB],RB个数 */
    VOS_UINT8                           aucRbId[PS_WUE_MAX_PS_RB_NUM];  /* 标志PDCP实体 */
    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留 */
} RRC_PDCP_SYNC_REQ_STRU;

/*****************************************************************************
 结构名    : PDCP_RRC_SYNC_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PDCP_RRC_SYNC_CNF定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */    /*_H2ASN_Skip*/
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* 消息类型 */  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* 操作号,与命令原语对应 */
    PDCPITF_RSLT_ENUM_UINT32            enRslt;             /* 0:表示成功，1：实体不存在，2：不支持无损重定位   */
}PDCP_RRC_SYNC_CNF_STRU;

/*****************************************************************************
 结构名    : RRC_PDCP_STOP_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_PDCP_STOP_REQ定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */    /*_H2ASN_Skip*/
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* 消息类型 */  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* 操作号,与命令原语对应 */
    VOS_UINT8                           ucRbCnt;            /* 实体个数 */
    VOS_UINT8                           aucRbId[PS_WUE_MAX_PS_RB_NUM];
    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留 */
}RRC_PDCP_STOP_REQ_STRU;

/*****************************************************************************
 结构名    : PDCP_RRC_STOP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PDCP_RRC_STOP_CNF定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */    /*_H2ASN_Skip*/
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* 消息类型 */  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* 操作号,与命令原语对应 */
    PDCPITF_RSLT_ENUM_UINT32            enRslt;             /* VOS_OK:成功，VOS_ERR：失败  */
}PDCP_RRC_STOP_CNF_STRU;

/*****************************************************************************
 结构名    : RRC_PDCP_CONTINUE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_PDCP_CONTINUE_REQ定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */    /*_H2ASN_Skip*/
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* 消息类型 */  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* 操作号,与命令原语对应 */
    VOS_UINT8                           ucRbCnt;            /* 实体个数 */
    VOS_UINT8                           aucRbId[PS_WUE_MAX_PS_RB_NUM];
    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留 */
}RRC_PDCP_CONTINUE_REQ_STRU;

/*****************************************************************************
 结构名    : PDCP_RRC_CONTINUE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_PDCP_CONTINUE_CNF 定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */    /*_H2ASN_Skip*/
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* 消息类型 */  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* 操作号,与命令原语对应 */
    PDCPITF_RSLT_ENUM_UINT32            enRslt;
}PDCP_RRC_CONTINUE_CNF_STRU;


/*****************************************************************************
 结构名    : PDCP_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_PDCP_RELOC_REQ 定义
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[1];     /* 4字节对齐，保留 */
    VOS_UINT8                           ucRbId;             /* 标志PDCP实体               */
    VOS_UINT16                          usReceiveSN;        /* UTRAN下一个期望接收的序列号 */
}PDCP_INFO_STRU;

/*****************************************************************************
 结构名    : RRC_PDCP_RELOC_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PDCP迁移请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */    /*_H2ASN_Skip*/
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* 消息类型 */  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* 操作号,与命令原语对应 */
    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
    VOS_UINT8                           ucCnt;              /* 实体个数 */
    PDCP_INFO_STRU                      astPdcpSNInfo[PS_WUE_MAX_PS_RB_NUM];
}RRC_PDCP_RELOC_REQ_STRU;

/*****************************************************************************
 结构名    : PDCP_RCVSN_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PDCP_RCVSN_INFO_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[1];     /* 4字节对齐，保留 */
    VOS_UINT8                           ucRbId;             /* 标志PDCP实体 */
    VOS_UINT16                          usReceiveSN;        /* UE下一个期望接收的序列号 */
}PDCP_RCVSN_INFO_STRU;

/*****************************************************************************
 结构名    : PDCP_RRC_RELOC_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 迁移响应
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */    /*_H2ASN_Skip*/
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* 消息类型 */  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* 操作号,与命令原语对应 */
    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
    VOS_UINT8                           ucCnt;              /* 实体个数 */
    PDCP_RCVSN_INFO_STRU                astRcvSnInfo[PS_WUE_MAX_PS_RB_NUM];
    PDCPITF_RSLT_ENUM_UINT32            enRslt;             /* 表示成功或失败 */
}PDCP_RRC_RELOC_CNF_STRU;

/*****************************************************************************
 结构名    : RRC_PDCP_DLSIZE_CHANGE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_PDCP_DLSIZE_CHANGE_REQ 定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */    /*_H2ASN_Skip*/
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* 消息类型 */  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* 操作号,与应答原语对应 */
    VOS_UINT8                           ucRbCnt;            /* 实体个数 */
    VOS_UINT8                           aucRbId[PS_WUE_MAX_PS_RB_NUM];   /* RbID 列表 */
    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留 */
}RRC_PDCP_DLSIZE_CHANGE_REQ_STRU;

/*****************************************************************************
 结构名    : PDCP_RRC_DLSIZE_CHANGE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PDCP_RRC_DLSIZE_CHANGE_CNF 定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */    /*_H2ASN_Skip*/
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* 消息类型 */  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* 操作号,与命令原语对应 */
    VOS_UINT8                           aucReserve1[3];     /* 4字节对齐，保留 */
    VOS_UINT8                           ucCnt;              /* 实体个数 */
    PDCP_RCVSN_INFO_STRU                astRcvSnInfo[PS_WUE_MAX_PS_RB_NUM];      /* 重定位信息列表 */
    PDCPITF_RSLT_ENUM_UINT32            enRslt;             /* 0:表示成功，1：实体不存在，2：不支持无损下行PDU 大小改变 */
}PDCP_RRC_DLSIZE_CHANGE_CNF_STRU;

/*****************************************************************************
 结构名    : RRC_PDCP_COMPRESS_INI_REQ
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_PDCP_COMPRESS_INI_REQ 定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /*_H2ASN_Skip*/
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* 消息类型标识 */  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* 操作号,与应答原语对应 */
    VOS_UINT8                           ucRbCnt;            /* 实体个数 */
    VOS_UINT8                           aucRbId[PS_WUE_MAX_PS_RB_NUM];/* 实体列表 */
    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留 */
}RRC_PDCP_COMPRESS_INI_REQ_STRU;


/*****************************************************************************
 结构名    : PDCP_RRC_COMPRESS_INI_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PDCP_RRC_COMPRESS_INI_CNF定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */    /*_H2ASN_Skip*/
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* 消息类型 */  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* 操作号,与命令原语对应 */
    PDCPITF_RSLT_ENUM_UINT32            enRslt;
} PDCP_RRC_COMPRESS_INI_CNF_STRU;

/*****************************************************************************
 结构名    : PDCP_RRC_ERROR_IND
 协议表格  :
 ASN.1描述 :
 结构说明  : PDCP_RRC_ERROR_IND 定义,PDCP异常通知RRC
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */    /*_H2ASN_Skip*/
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* 消息类型 */  /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留 */
    PDCPITF_RSLT_ENUM_UINT32            enRslt;
} PDCP_RRC_ERROR_IND_STRU;


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


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
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgID;    /*_H2ASN_MsgChoice_Export RRC_PDCP_MSG_TYPE_ENUM_UINT16*/

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          RRC_PDCP_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}RRC_PDCP_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    RRC_PDCP_MSG_DATA                   stMsgData;
}RrcPdcpInterface_MSG;


/*****************************************************************************
  10 函数声明
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

#endif /* end of RrcPdcpInterface.h */
