/************************************************************************
  Copyright   : 2013-2015, Huawei Tech. Co., Ltd.
  File name   : usimmt1dl.h
  Author      : j00168360
  Version     : V900R001
  Date        : 2013-10-14
  Description : T=1项目头文件相关定义---
  History     :
   1.Date:2013-10-14
     Author: j00168360
     Modification:create

************************************************************************/

#ifndef __USIMM_T1_DL_H__
#define __USIMM_T1_DL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "usimmapdu.h"

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* 块信息域范围为1-254 */
#define     USIMM_T1_MAX_IFS                        (254)
#define     USIMM_T1_MIN_IFS                        (1)

/* LRC校验字为一字节 */
#define     USIMM_T1_LRC_SIZE                       (1)

/* CRC校验字为两字节 */
#define     USIMM_T1_CRC_SIZE                       (2)

/* 出错后最大重传尝试次数为2*/
#define     USIMM_T1_MAX_ATTEMPTS_TIMES             (2)

/* I-BLOCK块发送初始序号 */
#define     USIMM_T1_I_BLOCK_INIT_SEQ               (0)

/* WTX默认值,默认等待一个BWT时长 */
#define     USIMM_T1_DEFAULT_WTX                    (1)

/* I-block 的PCB字节中，N(S) bit的位置 */
#define     USIMM_I_BLOCK_PCB_NS_BIT                (7)

/* I-block 的PCB字节中，N(S) bit的掩码 */
#define     USIMM_I_BLOCK_PCB_NS_BIT_MASK           (0x40)

/* I-block 的PCB字节中，More data bit的位置 */
#define     USIMM_I_BLOCK_PCB_MORE_DATA_BIT         (6)

/* I-block 的PCB字节中，More data bit的掩码 */
#define     USIMM_I_BLOCK_PCB_MORE_DATA_BIT_MASK    (0x20)

/* R-block 的PCB字节中，第6 bit的掩码 */
#define     USIMM_R_BLOCK_PCB_SIXTH_BIT_MASK        (0x20)

/* R-block 的PCB字节中，N(R) bit的位置 */
#define     USIMM_R_BLOCK_PCB_NR_BIT                (5)

/* R-block 的PCB字节中，N(R) bit的掩码 */
#define     USIMM_R_BLOCK_PCB_NR_BIT_MASK           (0x10)

/* R-block 的PCB字节中，error code bit的掩码 */
#define     USIMM_R_BLOCK_PCB_ERRCODE_BIT_MASK      (0x0F)

/* S-block 的PCB字节中，request/response bit的掩码 */
#define     USIMM_S_BLOCK_PCB_REQ_RSP_BIT_MASK      (0x20)

/* 根据PCB字节高两bit确定块类型 */
#define     USIMM_T1_BLOCK_PCB_TYPE_BIT_MASK        (0xC0)

/* S-block 的PCB字节中,S-block子类型获取 */
#define     USIMM_T1_BLOCK_PCB_S_BLOCK_TYPE_BIT_MASK (0x3F)

/* 块起始域大小 */
#define     USIMM_T1_PROLOGUE_FIELD_SIZE            (3)

/* 块结束域最大大小 */
#define     USIMM_T1_EPILOGUE_FIELD_MAX_SIZE        (USIMM_T1_CRC_SIZE)

/* 块的最大大小 */
#define     USIMM_T1_BLOCK_MAX_SIZE                 (USIMM_T1_PROLOGUE_FIELD_SIZE + USIMM_T1_MAX_IFS + USIMM_T1_EPILOGUE_FIELD_MAX_SIZE)

/* PROLOGUE FIELD 中NAD/PCB/LEN域的字节偏移 */
#define     T1_NAD                                  (0)
#define     T1_PCB                                  (1)
#define     T1_LEN                                  (2)

/* 块中信息域起始字节 */
#define     T1_INFO_START_BYTE                      (3)

/* T1 CASE1中APDU长度 */
#define     T1_CASE1_APDU_LEN                       (4)

/* T1中卡返回的状态字长度 */
#define     T1_CARD_SW_LEN                          (2)

/* T1中接收数据buf大小,data+sw,暂定为260字节 */
#define     USIMM_T1_RCV_BUF_SIZE                   (260)

/* Le字段最大值 */
#define     USIMM_LE_MAX_LEN                        (0xFF)

/*******************************************************************************
  3 枚举定义
*******************************************************************************/
/*****************************************************************************
 枚举名    : USIMM_T1_BLOCK_TYPE_ENUM_UINT32
 结构说明  : T=1协议中块类型枚举定义
*****************************************************************************/
enum USIMM_T1_BLOCK_TYPE_ENUM
{
    USIMM_T1_BLOCK_TYPE_I,              /* information block，用于发送应用层信息数据，PCB字节bit8为0表示I-BLOCK */
    USIMM_T1_BLOCK_TYPE_R       = 0x80, /* receive ready block，用于应答，PCB bit8bit7为10表示R-BLOCK，无信息域 */
    USIMM_T1_BLOCK_TYPE_S       = 0xC0, /* supervisory block, 用于发送控制信息，PCB bit8bit7为11表示S-BLOCK*/
    USIMM_T1_BLOCK_TYPE_BUTT
};
typedef VOS_UINT32      USIMM_T1_BLOCK_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : USIMM_T1_I_BLOCK_MORE_DATA_BIT_ENUM_UINT32
 结构说明  : T=1协议中I类型块的PCB字节中，more data bit的取值枚举定义
*****************************************************************************/
enum USIMM_T1_I_BLOCK_MORE_DATA_BIT_ENUM
{
    USIMM_T1_I_BLOCK_WITHOUT_MORE_DATA,              /* 没有下个链块，MORE DATA BIT 为0*/
    USIMM_T1_I_BLOCK_WITH_MORE_DATA,                 /* 存在下个链块，MORE DATA BIT 为1*/
    USIMM_T1_I_BLOCK_MORE_DATA_BIT_BUTT
};
typedef VOS_UINT32      USIMM_T1_I_BLOCK_MORE_DATA_BIT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : USIMM_T1_S_BLOCK_TYPE_ENUM_UINT32
 结构说明  : T=1协议中S类型块子类型定义
*****************************************************************************/
enum USIMM_T1_S_BLOCK_TYPE_ENUM
{
    USIMM_T1_S_BLOCK_RESYNCH_REQ        = 0xC0, /* 用于发送重同步请求，目前只能由UE发给卡，无信息域 */
    USIMM_T1_S_BLOCK_RESYNCH_RES        = 0xE0,
    USIMM_T1_S_BLOCK_IFS_REQ            = 0xC1, /* 用于协商信息域大小，信息域为一个字节 */
    USIMM_T1_S_BLOCK_IFS_RES            = 0xE1,
    USIMM_T1_S_BLOCK_ABORT_REQ          = 0xC2, /* 用于终止链块传输，卡和UE均可发起 */
    USIMM_T1_S_BLOCK_ABORT_RES          = 0xE2,
    USIMM_T1_S_BLOCK_WTX_REQ            = 0xC3, /* 用于卡请求终端多等待N个BWT处理数据，只能由卡发给UE，信息域为一个字节 */
    USIMM_T1_S_BLOCK_WTX_RES            = 0xE3,
    USIMM_T1_S_BLOCK_ERR_VPP_STATE      = 0xE4, /* 用于指示错误的VPP状态，目前未使用 */
    USIMM_T1_S_BLOCK_TYPE_BUTT
};
typedef VOS_UINT32      USIMM_T1_S_BLOCK_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : USIMM_T1_BLOCK_EPILOGUE_FIELD_ENUM
 结构说明  : T=1协议中块结束域校验类型枚举
*****************************************************************************/
enum USIMM_T1_BLOCK_EPILOGUE_FIELD_ENUM
{
    USIMM_T1_BLOCK_EPILOGUE_FIELD_LRC   = 0, /* 块结束域采用一字节LRC校验 */
    USIMM_T1_BLOCK_EPILOGUE_FIELD_CRC   = 1, /* 块结束域采用两字节CRC校验 */
    USIMM_T1_BLOCK_EPILOGUE_FIELD_BUTT
};

typedef VOS_UINT32      USIMM_T1_BLOCK_EPILOGUE_FIELD_ENUM_UINT32;

/*****************************************************************************
 枚举名    : USIMM_T1_PROC_STATE_ENUM
 结构说明  : T=1 处理状态枚举
*****************************************************************************/
enum USIMM_T1_PROC_STATE_ENUM
{
    USIMM_T1_PROC_STATE_IDLE,                               /* 当前未发送任何数据 */
    USIMM_T1_PROC_STATE_SENT_APDU,                          /* 当前发送了单个APDU */
    USIMM_T1_PROC_STATE_SENT_CHAIN_APDU,                    /* 当前发送了链块APDU */
    USIMM_T1_PROC_STATE_SENT_S_BLOCK_REQ,                   /* 当前发送了S BLOCK(request)*/
    USIMM_T1_PROC_STATE_BUTT
};

typedef VOS_UINT32      USIMM_T1_PROC_STATE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : USIMM_T1DL_HANDLE_STATE_ENUM
 结构说明  : T=1 外层状态机枚举
*****************************************************************************/
enum USIMM_T1DL_HANDLE_STATE_ENUM
{
    USIMM_T1DL_HANDLE_STATE_IDLE,                           /* 当前未做任何事 */
    USIMM_T1DL_HANDLE_STATE_SEND_IFS,                       /* 当前发送IFS REQ */
    USIMM_T1DL_HANDLE_STATE_SEND_INFO,                      /* 当前发送业务数据 */
    USIMM_T1DL_HANDLE_STATE_RCV_BLOCK,                      /* 当前接收数据块 */
    USIMM_T1DL_HANDLE_STATE_BUTT
};

typedef VOS_UINT32      USIMM_T1DL_HANDLE_STATE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : USIMM_T1_R_BLOCK_ERRCODE_ENUM
 结构说明  : T=1 R BLOCK 错误类型枚举
*****************************************************************************/
enum USIMM_T1_R_BLOCK_ERRCODE_ENUM
{
    USIMM_T1_R_BLOCK_ERROR_FREE         = 0, /* denote an error-free acknowledgement */
    USIMM_T1_R_BLOCK_REDUNDANCY_ERR     = 1, /* indicate a redundancy code error or a character parity error */
    USIMM_T1_R_BLOCK_OTHER_ERR          = 2, /* indicate other error */
    USIMM_T1_R_BLOCK_ERRCODE_BUTT
};

typedef VOS_UINT32      USIMM_T1_R_BLOCK_ERRCODE_ENUM_UINT32;

/*****************************************************************************
  4 STRUCT定义
*****************************************************************************/
/*****************************************************************************
 结构名    : USIMM_T1_PROLOGUE_FIELD_STRU
 结构说明  : T=1块起始域结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8       ucNAD;    /* Node address byte, bit1-bit3:SAD; bit5-bit7:DAD */
    VOS_UINT8       ucPCB;    /* Protocol control byte */
    VOS_UINT8       ucLen;    /* 长度字节，指示后续信息域长度 */
    VOS_UINT8       ucRsv;    /* 保留 */
}USIMM_T1_PROLOGUE_FIELD_STRU;

typedef VOS_UINT32 (*PUSIMMT1DLRECVBLKPROC)(VOS_BOOL bValidFlag, VOS_UINT32 ulLength, VOS_UINT8 *pucData);

/*****************************************************************************
 结构名    : USIMMT1DL_RECV_FUNC_STATUS
 结构说明  : T=1接收块处理
*****************************************************************************/
typedef struct
{
    USIMM_T1_PROC_STATE_ENUM_UINT32     enStateId;          /* 状态ID */
    PUSIMMT1DLRECVBLKPROC               pProcFun;           /* 处理函数 */
}USIMMT1DL_RECV_FUNC_STATUS;

typedef VOS_UINT32 (*PUSIMMT1DLHANDLEPROC)(USIMM_APDU_ST* pstAPDUData);

/*****************************************************************************
 结构名    : USIMMT1DL_HANDLE_FUNC_STATUS
 结构说明  : T=1外层状态机处理
*****************************************************************************/
typedef struct
{
    USIMM_T1DL_HANDLE_STATE_ENUM_UINT32 enStateId;          /* 状态ID */
    PUSIMMT1DLHANDLEPROC                pProcFun;           /* 处理函数 */
}USIMMT1DL_HANDLE_FUNC_STATUS;

/*****************************************************************************
 结构名    : USIMM_T1_I_BLOCK_PCB_PARA_STRU
 结构说明  : T=1 I BLOCK参数结构体，用于解析收到的块响应数据
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulSeqNum;           /* I BLOCK序号 */
    USIMM_T1_I_BLOCK_MORE_DATA_BIT_ENUM_UINT32              enMoreBit;          /* I BLOCK more data 指示 */
}USIMM_T1_I_BLOCK_PCB_PARA_STRU;

/*****************************************************************************
 结构名    : USIMM_T1_R_BLOCK_PCB_PARA_STRU
 结构说明  : T=1 R BLOCK参数结构体，用于解析收到的块响应数据
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulSeqNum;           /* R BLOCK序号 */
    USIMM_T1_R_BLOCK_ERRCODE_ENUM_UINT32                    enErrcode;          /* R BLOCK错误码指示 */
}USIMM_T1_R_BLOCK_PCB_PARA_STRU;

/*****************************************************************************
 结构名    : USIMM_T1_S_BLOCK_PCB_PARA_STRU
 结构说明  : T=1 S BLOCK参数结构体，用于解析收到的块响应数据
*****************************************************************************/
typedef struct
{
    USIMM_T1_S_BLOCK_TYPE_ENUM_UINT32                       enSBlkType;         /* S BLOCK类型 */
}USIMM_T1_S_BLOCK_PCB_PARA_STRU;

/*****************************************************************************
 结构名    : USIMM_T1_BLOCK_PARA_UNION
 结构说明  : T=1 三种块类型各自参数结构联合体，用于解析收到的块响应数据
*****************************************************************************/
typedef union
{
    USIMM_T1_I_BLOCK_PCB_PARA_STRU      stIBlockPara;       /*I BLOCK参数结构 */
    USIMM_T1_R_BLOCK_PCB_PARA_STRU      stRBlockPara;       /*R BLOCK参数结构 */
    USIMM_T1_S_BLOCK_PCB_PARA_STRU      stSBlockPara;       /*S BLOCK参数结构 */
}USIMM_T1_BLOCK_PARA_UNION;

/*****************************************************************************
 结构名    : USIMM_T1_BLOCK_PARA_STRU
 结构说明  : T=1块参数结构，用于解析收到的块响应数据
*****************************************************************************/
typedef struct
{
    USIMM_T1_BLOCK_TYPE_ENUM_UINT32     enBlockType;        /* 块类型 */
    USIMM_T1_BLOCK_PARA_UNION           uBlockPara;         /* 块相应类型对应的参数结构体 */
}USIMM_T1_BLOCK_PARA_STRU;

/*****************************************************************************
 结构名    : USIMM_T1_S_BLOCK_STRU
 结构说明  : T=1块参数结构，用于解析收到的块响应数据
*****************************************************************************/
typedef struct
{
    USIMM_T1_S_BLOCK_TYPE_ENUM_UINT32   enSBlkType;         /* S BLOCK类型 */
    VOS_UINT8                           ucLen;              /* S BLOCK的信息域数据长度 */
    VOS_UINT8                           ucData;             /* S BLOCK的信息域数据 */
    VOS_UINT16                          usRsv;              /* 保留字节 */
}USIMM_T1_S_BLOCK_STRU;

/*****************************************************************************
 结构名    : USIMM_T1_CTRL_CTX_STRU
 结构说明  : T=1协议的控制上下文
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulIFSC;             /* IFSC */
    VOS_UINT32                                              ulIFSD;             /* IFSD */
    USIMM_T1_BLOCK_EPILOGUE_FIELD_ENUM_UINT32               enErrDetectMode;    /* CRC或LRC */
    VOS_UINT32                                              ulBWTTimes;         /* BWT倍数 */
    USIMM_T1_S_BLOCK_STRU                                   stSBlkPara;         /* 待发送S BLOCK的结构 */
    USIMM_T1DL_HANDLE_STATE_ENUM_UINT32                     enT1HandleState;    /* T=1一层状态机 */
    USIMM_T1_PROC_STATE_ENUM_UINT32                         enT1ProcState;      /* T=1块接收处理状态机 */
    VOS_UINT32                                              ulUESeqNum;         /* UE下一次发给卡的I BLOCK序号 */
    VOS_UINT32                                              ulUICCSeqNum;       /* UE期望从卡收到的序号 */
    VOS_UINT32                                              ulRcvBlkChainFlg;   /* 收到链块的标记: VOS_TRUE-收到链块, VOS_FALSE-未收到链块 */
    VOS_UINT32                                              ulSendBlkChainFlg;  /* 发送链块的标记: VOS_TRUE-发送链块, VOS_FALSE-未发送链块 */
    VOS_UINT32                                              ulUnexpectCount;    /* 收到不符合预期块计数器 */
}USIMM_T1_CTRL_CTX_STRU;


/*****************************************************************************
 结构名    : USIMM_T1_SEND_DATA_STRU
 结构说明  : T=1数据发送结构定义
*****************************************************************************/
typedef struct
{
    VOS_UINT8       aucInfoData[USIMM_APDU_HEADLEN+USIMM_APDU_MAXLEN];          /* 待发送总数据 */
    VOS_UINT8       aucRsv[3];                                                  /* 保留字节 */
    VOS_UINT32      ulTotalLen;                                                 /* 待发送总数据长度 */
    VOS_UINT8      *pucLastInfoData;                                            /* 已发送数据指针 */
    VOS_UINT32      ulLastTotalLen;                                             /* 已发送数据长度总长度 */
    VOS_UINT32      ulLastLen;                                                  /* 上个分片发送数据长度 */
}USIMM_T1_SEND_DATA_STRU;

/*****************************************************************************
 结构名    : USIMM_T1_RCV_DATA_STRU
 结构说明  : T=1数据接收结构定义
*****************************************************************************/
typedef struct
{
    VOS_UINT8       aucInfoData[USIMM_T1_RCV_BUF_SIZE];     /* 接收块中信息域数据，data+sw */
    VOS_UINT32      ulDataLen;                              /* 接收信息域数据长度 */
}USIMM_T1_RCV_DATA_STRU;

/*****************************************************************************
 结构名    : USIMM_DL_T1_PARA_STRU
 结构说明  : T=1参数结构定义
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulIFSC;             /* IFSC */
    VOS_UINT32                                              ulIFSD;             /* IFSD */
    USIMM_T1_BLOCK_EPILOGUE_FIELD_ENUM_UINT32               enErrDetectMode;    /* CRC或LRC */
}USIMM_DL_T1_PARA_STRU;

/*****************************************************************************
 结构名    : USIMM_T1_STATISTIC_STRU
 结构说明  : T=1可维可测统计数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32      ulSndIBlkSuccCnt;                       /* 发送I-Block成功次数统计 */
    VOS_UINT32      ulSndIBlkFailCnt;                       /* 发送I-Block失败次数统计 */

    VOS_UINT32      ulSndRBlkSuccCnt;                       /* 发送R-Block成功次数统计 */
    VOS_UINT32      ulSndRBlkFailCnt;                       /* 发送R-Block失败次数统计 */

    VOS_UINT32      ulSndSBlkResynchReqSuccCnt;             /* 发送S-Block(RESYNCH Request)成功次数统计 */
    VOS_UINT32      ulSndSBlkResynchReqFailCnt;             /* 发送S-Block(RESYNCH Request)失败次数统计 */
    VOS_UINT32      ulSndSBlkIFSReqSuccCnt;                 /* 发送S-Block(IFS Request)成功次数统计 */
    VOS_UINT32      ulSndSBlkIFSReqFailCnt;                 /* 发送S-Block(IFS Request)失败次数统计 */
    VOS_UINT32      ulSndSBlkIFSRspSuccCnt;                 /* 发送S-Block(IFS Response)成功次数统计 */
    VOS_UINT32      ulSndSBlkIFSRspFailCnt;                 /* 发送S-Block(IFS Response)失败次数统计 */
    VOS_UINT32      ulSndSBlkAbortReqSuccCnt;               /* 发送S-Block(ABORT Request)成功次数统计 */
    VOS_UINT32      ulSndSBlkAbortReqFailCnt;               /* 发送S-Block(ABORT Request)失败次数统计 */
    VOS_UINT32      ulSndSBlkAbortRspSuccCnt;               /* 发送S-Block(ABORT Response)成功次数统计 */
    VOS_UINT32      ulSndSBlkAbortRspFailCnt;               /* 发送S-Block(ABORT Response)失败次数统计 */
    VOS_UINT32      ulSndSBlkWTXRspSuccCnt;                 /* 发送S-Block(WTX Response)成功次数统计 */
    VOS_UINT32      ulSndSBlkWTXRspFailCnt;                 /* 发送S-Block(WTX Response)失败次数统计 */

    VOS_UINT32      ulRcvNADErrBlkCnt;                      /* 接收到NAD域错误的Block次数统计 */
    VOS_UINT32      ulRcvBlkSizeAbnormalBlkCnt;             /* 接收到长度异常(小于理论最小块长度或大于理论最大块长度)的Block次数统计 */
    VOS_UINT32      ulRcvBlkSizeErrBlkCnt;                  /* 接收到长度错误(头+LEN+EDC长度不等于接收到的总长度)的Block次数统计 */
    VOS_UINT32      ulRcvEDCErrBlkCnt;                      /* 接收到EDC域错误的Block次数统计 */
    VOS_UINT32      ulRcvMoreThanIFSDErrBlkCnt;             /* 接收到信息域超过IFSD的Block次数统计 */

    VOS_UINT32      ulRcvInvalidLenRBlkCnt;                 /* 接收到LEN长度不为0的R-Block次数统计 */
    VOS_UINT32      ulRcvInvalidBit6OfPCBRBlkCnt;           /* 接收到PCB域bit 6不为0的R-Block次数统计 */
    VOS_UINT32      ulRcvTriggerResendRBlkCnt;              /* 接收到触发UE重发的R-Block次数统计 */
    VOS_UINT32      ulRcvAbnormalRBlkCnt;                   /* 接收到不符合协议流程逻辑的R-Block次数统计 */

    VOS_UINT32      ulRcvAbnormalIBlkCnt;                   /* 接收到不符合协议流程逻辑的I-Block次数统计 */

    VOS_UINT32      ulRcvInvalidLenSBlkCnt;                 /* 接收到LEN长度不符合协议逻辑(如WTX REQ中LEN!=1)的S-Block次数统计 */
    VOS_UINT32      ulRcvInvalidTypeSBlkCnt;                /* 接收到Type不符合协议逻辑的S-Block次数统计 */
    VOS_UINT32      ulRcvAbnormalSBlkCnt;                   /* 接收到不符合协议流程逻辑的S-Block次数统计 */

    VOS_UINT32      ulDeactCardCnt;                         /* 去激活卡次数统计 */
    VOS_UINT32      ulSetBWTFailCnt;                        /* 调用底软接口设置BWT失败次数统计 */
    VOS_UINT32      ulProtocolSwitchFailCnt;                /* 调用底软接口进行T=0和T=1协议类型切换失败次数统计 */
}USIMM_T1_STATISTIC_STRU;


/*****************************************************************************
  5 全局变量声明
*****************************************************************************/
extern USIMM_T1_STATISTIC_STRU         g_stT1StatisticInfo;

extern USIMM_DL_T1_PARA_STRU           g_stUSIMMT1Para;

extern USIMM_T1_CTRL_CTX_STRU          g_stUsimmT1CtrlCtx;

/* T=1 数据发送信息结构  */
extern USIMM_T1_SEND_DATA_STRU         g_stT1SendDataInfo;

/* T=1 数据接收信息结构  */
extern USIMM_T1_RCV_DATA_STRU          g_stT1RcvDataInfo;

/*****************************************************************************
  6 OTHERS定义
*****************************************************************************/
extern VOS_UINT32 USIMM_T1DLUpdateParaByATR(USIMM_T1_BLOCK_EPILOGUE_FIELD_ENUM_UINT32 enEDCType, VOS_UINT32 ulIFSC, VOS_UINT32 ulIFSD);

extern VOS_UINT32 USIMM_T1DLHandle(USIMM_APDU_ST* pstAPDUData);

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

#endif /* end of usimmt1dl.h*/

