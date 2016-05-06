/************************************************************************
  Copyright   : 2013-2015, Huawei Tech. Co., Ltd.
  File name   : cbpacommagent.h
  Author      : l00256032
  Version     : V900R001
  Date        : 2013-12-19
  Description : L+C共SIM卡项目头文件相关定义---
  History     :
   1.Date:2013-12-19
     Author: l00256032
     Modification:create

************************************************************************/

#ifndef __CBPA_COMMAGENT_H__
#define __CBPA_COMMAGENT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CbpaPsInterface.h"
#include "OmHdlcInterface.h"

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define CBPCA_HDLC_BUFFER_SIZE          (3 * 1024)          /* CBPCA用于HDLC封装、解封装的缓存大小 */

#define CBPCA_MAX_INDEX                 (0x7FFF)            /* HDLC中Index的值有效范围为:0~0x7FFF */


/* CBPCA收到上层应用发送的数据，需要预留6个字节，用于填写HDLC帧中断Index、Length、MsgId，
   可以减少一次内存拷贝，提高数据发送效率 */
#define CBPCA_RCV_UPPER_DATA_RSV_LEN    (6)

/* CBPA 调试打印宏 */
#if (VOS_WIN32 == VOS_OS_VER)
#define CBPA_DEBUG_TRACE(pucData, ulDataLen)    {;}
#else
#define CBPA_DEBUG_TRACE(pucData, ulDataLen) \
    if(VOS_FALSE != (g_ucCbpcaDbgFlag)) \
    { \
        VOS_UINT32 ulCbpaDbgLoop; \
        (VOS_VOID)vos_printf("\n%s, Rcv UART Data Len: = %d\n", __FUNCTION__, ulDataLen); \
        for (ulCbpaDbgLoop = 0 ; ulCbpaDbgLoop < ulDataLen; ulCbpaDbgLoop++) \
        { \
            (VOS_VOID)vos_printf("%02x ", *((VOS_UINT8*)pucData + ulCbpaDbgLoop)); \
        } \
        (VOS_VOID)vos_printf("\r\n"); \
    } \

#endif

/* CBPA LOG宏 */
#define CBPA_INFO_LOG(string)            PS_LOG(WUEPS_PID_CBPCA, 0, PS_PRINT_INFO,   string)
#define CBPA_NORMAL_LOG(string)          PS_LOG(WUEPS_PID_CBPCA, 0, PS_PRINT_NORMAL, string)
#define CBPA_WARNING_LOG(string)         PS_LOG(WUEPS_PID_CBPCA, 0, PS_PRINT_WARNING,string)
#define CBPA_ERROR_LOG(string)           PS_LOG(WUEPS_PID_CBPCA, 0, PS_PRINT_ERROR,  string)

#define CBPA_INFO1_LOG(string, para1)    PS_LOG1(WUEPS_PID_CBPCA, 0, PS_PRINT_INFO,   string, para1)
#define CBPA_NORMAL1_LOG(string, para1)  PS_LOG1(WUEPS_PID_CBPCA, 0, PS_PRINT_NORMAL, string, para1)
#define CBPA_WARNING1_LOG(string, para1) PS_LOG1(WUEPS_PID_CBPCA, 0, PS_PRINT_WARNING,string, para1)
#define CBPA_ERROR1_LOG(string, para1)   PS_LOG1(WUEPS_PID_CBPCA, 0, PS_PRINT_ERROR,  string, para1)

/* CBPCA可维可测统计宏 */
#define CBPCA_STATISTIC_INC(statistic_type)            ((*(((VOS_UINT32 *)&g_stCbpcaStatic) + statistic_type))++)

/*******************************************************************************
  3 枚举定义
*******************************************************************************/
/*****************************************************************************
 枚举名    : CBP_MODEM_STATUS_ENUM
 枚举说明  : CBP Modem是否就绪
*****************************************************************************/
enum CBP_MODEM_STATUS_ENUM
{
    CBP_MODEM_STATUS_NOT_READY          = 0x0000,           /* CBP Modem未就绪 */
    CBP_MODEM_STATUS_READY              = 0x0001,           /* CBP Modem已就绪 */

    CBP_MODEM_STATUS_BUTT
};
typedef VOS_UINT32 CBP_MODEM_STATUS_ENUM_UINT32;

/*****************************************************************************
 枚举名    : CBPCA_STATISTIC_TYPE_ENUM
 枚举说明  : CBPCA可维可测类型枚举
*****************************************************************************/
enum CBPCA_STATISTIC_TYPE_ENUM
{
    CBPCA_STATISTIC_HDLC_DECAP_SUCC             = 0x0000,    /* HDLC解封装:解封装成功 */
    CBPCA_STATISTIC_UART_CALLBACK_WRONG_PORTNO  = 0x0001,    /* 底软调用回调函数，但uPortNo错误 */
    CBPCA_STATISTIC_UART_CALLBACK_NULL_PTR      = 0x0002,    /* 底软调用回调函数，但入口指针为空 */
    CBPCA_STATISTIC_UART_CALLBACK_LEN_IS_ZERO   = 0x0003,    /* 底软调用回调函数，但入口长度为0 */
    CBPCA_STATISTIC_UART_CALLBACK_CBP_NOT_READY = 0x0004,    /* 底软调用回调函数，但CBP状态为NOT READY */
    CBPCA_STATISTIC_HDLC_DECAP_FCS_ERR          = 0x0005,    /* HDLC解封装:FCS错误 */
    CBPCA_STATISTIC_HDLC_DECAP_DISCARD          = 0x0006,    /* HDLC解封装:异常帧，丢弃 */
    CBPCA_STATISTIC_HDLC_DECAP_BUFF_FULL        = 0x0007,    /* HDLC解封装:缓存溢出 */
    CBPCA_STATISTIC_HDLC_DECAP_PARA_ERROR       = 0x0008,    /* HDLC解封装:入参错误 */
    CBPCA_STATISTIC_HDLC_DECAP_INVALID_INDEX    = 0x0009,    /* HDLC解封装:错误的Index */
    CBPCA_STATISTIC_HDLC_DECAP_NO_DATA_FIELD    = 0x000A,    /* HDLC解封装:解封装后的数据长度<=6，不存在Data域 */
    CBPCA_STATISTIC_HDLC_DECAP_LENGTH_ABNORMAL  = 0x000B,    /* HDLC解封装:解封装后，LENGTH域<=2，异常 */
    CBPCA_STATISTIC_HDLC_DECAP_LENGTH_IS_LESS   = 0x000C,    /* HDLC解封装:Length比实际数据长度要小 */
    CBPCA_STATISTIC_HDLC_DECAP_LENGTH_IS_MORE   = 0x000D,    /* HDLC解封装:Length比实际数据长度要大 */
    CBPCA_STATISTIC_HDLC_DECAP_INVALID_MSGID    = 0x000E,    /* HDLC解封装:错误的MsgId */
    CBPCA_STATISTIC_HDLC_DECAP_INVALID_FRAME    = 0x000F,    /* HDLC解封装:无效帧 */

    CBPCA_STATISTIC_HDLC_ENCAP_SEND_SUCC        = 0x0010,    /* 调用底软接口DRV_UART_SEND发送成功 */
    CBPCA_STATISTIC_CBP_NOT_READY_DISCARD_FRAME = 0x0011,    /* CBP未就绪，导致发往CBP的帧被丢弃 */
    CBPCA_STATISTIC_CANNOT_FIND_MATCH_MSGID     = 0x0012,    /* 发往CBP的数据，由于找不到MsgId对应的PID而被丢弃 */
    CBPCA_STATISTIC_HDLC_ENCAP_FAIL             = 0x0013,    /* HDLC封装失败 */
    CBPCA_STATISTIC_HDLC_ENCAP_SEND_FAIL        = 0x0014,    /* 调用底软接口DRV_UART_SEND返回失败 */

    CBPCA_STATISTIC_TYPE_BUTT
};
typedef VOS_UINT32 CBPCA_STATISTIC_TYPE_ENUM_UINT32;

/*******************************************************************************
  4 结构定义
*******************************************************************************/
/*****************************************************************************
 结构名    : CBPCA_HDLC_ENCAP_BUFFER_STRU
 结构说明  : CBPCA模块管理所使用上下文的数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          *pucEncapBuff;       /* HDLC封装所用的缓存 */
    VOS_UINT32                          ulEncapBuffSize;    /* 缓存总长度 */
}CBPCA_HDLC_ENCAP_BUFFER_STRU;

/*****************************************************************************
 结构名    : CBPCA_CTX_STRU
 结构说明  : CBPCA模块管理所使用上下文的数据结构
*****************************************************************************/
typedef struct
{
    CBPCA_HDLC_ENCAP_BUFFER_STRU        stEncapCtrlCtx;     /* HDLC封装所用的缓存 */
    OM_HDLC_STRU                        stDecapCtrlCtx;     /* HDLC解封装所使用的缓存及控制参数 */
    VOS_UINT16                          usExpectRcvIndex;   /* CPBCA期望接收到的Index索引 */
    VOS_UINT16                          usExpectSndIndex;   /* CPBCA期望发送的Index索引 */
    CBP_MODEM_STATUS_ENUM_UINT32        enCBPStatus;        /* CPB Modem当前是否就绪 */
}CBPCA_CTX_STRU;

/*****************************************************************************
 结构名    : CBPCA_STATISTIC_STRU
 结构说明  : CBPCA模块可维可测统计数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulHdlcDecapSucc;                        /* HDLC解封装:解封装成功 */
    VOS_UINT32                          ulUartCBWrongPortNo;                    /* 底软调用回调函数，但uPortNo错误 */
    VOS_UINT32                          ulUartCBNullPtr;                        /* 底软调用回调函数，但入口指针为空 */
    VOS_UINT32                          ulUartCBLenIsZero;                      /* 底软调用回调函数，但入口长度为0 */
    VOS_UINT32                          ulUartCBCBPNotReady;                    /* 底软调用回调函数，但CBP状态为NOT READY */
    VOS_UINT32                          ulHdlcDecapFCSError;                    /* HDLC解封装:FCS错误 */
    VOS_UINT32                          ulHdlcDecapDiscard;                     /* HDLC解封装:异常帧，丢弃 */
    VOS_UINT32                          ulHdlcDecapBuffFull;                    /* HDLC解封装:缓存溢出 */
    VOS_UINT32                          ulHdlcDecapParaError;                   /* HDLC解封装:入参错误 */
    VOS_UINT32                          ulHdlcDecapInvalidIndex;                /* HDLC解封装:错误的Index */
    VOS_UINT32                          ulHdlcDecapNoDataField;                 /* HDLC解封装:解封装后的数据长度<=6，不存在Data域 */
    VOS_UINT32                          ulHdlcDecapLengthAbnormal;              /* HDLC解封装:解封装后，LENGTH域<=2，异常 */
    VOS_UINT32                          ulHdlcDecapLengthIsLess;                /* HDLC解封装:Length比实际数据长度要小 */
    VOS_UINT32                          ulHdlcDecapLengthIsMore;                /* HDLC解封装:Length比实际数据长度要大 */
    VOS_UINT32                          ulHdlcDecapInvalidMsgId;                /* HDLC解封装:错误的MsgId */
    VOS_UINT32                          ulHdlcDecapInvalidFrame;                /* HDLC解封装:无效帧 */

    VOS_UINT32                          ulSendToUartSucc;                       /* 调用底软接口DRV_UART_SEND发送成功 */
    VOS_UINT32                          ulCBPNotReadyDiscardFrame;              /* CBP未就绪，导致发往CBP的帧被丢弃 */
    VOS_UINT32                          ulHdlcEncapInvalidPID;                  /* 发往CBP的数据，由于找不到MsgId对应的PID而被丢弃 */
    VOS_UINT32                          ulHdlcEncapFail;                        /* HDLC封装失败 */
    VOS_UINT32                          ulSendToUartFail;                       /* 调用底软接口DRV_UART_SEND返回失败 */
}CBPCA_STATISTIC_STRU;


/*****************************************************************************
 结构名    : CBPCA_PID_MSGID_MAP_TABLE_STRU
 结构说明  : HDLC帧中的MsgId与CBPCA需要转发到的PID之间的映射关系表
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPid;              /* CBPCA需要转发到的PID */
    VOS_UINT16                          usMsgId;            /* HDLC帧中的MsgId */
    VOS_UINT16                          usRsv;              /* 保留字节 */
    CBPCA_MSG_TYPE_ENUM_UINT32          enMsgType;          /* 与对应PID间的MsgType */
}CBPCA_PID_MSGID_MAP_TABLE_STRU;

/*****************************************************************************
 结构名    : CBPCA_MSG_HDR_STRU
 结构说明  : CSIMA接收到的消息的头，用于消息处理函数入口判断消息类型使用
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CBPCA_MSG_TYPE_ENUM_UINT32          enMsgType;          /* 消息ID */
}CBPCA_MSG_HDR_STRU;

/*****************************************************************************
  5 全局变量声明
*****************************************************************************/


/*****************************************************************************
  6 函数声明
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

#endif /* end of cbpacommagent.h*/

