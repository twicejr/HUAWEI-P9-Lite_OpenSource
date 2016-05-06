/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : CstNasInterface.h
  Author      : x44545
  Version     : V100R002
  Date        : 2006-08-01
  Description : 该头文件定义了CST和上层NAS(包括:CCA,AT和DC模块)之间的接口
  History     :
  1. Date     : 2006-08-01
     Author   : x44545
     Modification: Create
************************************************************************/

#ifndef _CST_NAS_INTERFACE_H_
#define _CST_NAS_INTERFACE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "product_config.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*******************************************************************************
  3 枚举定义
*******************************************************************************/
/*================*/ /*CST与NAS之间的原语*/
enum CST_TAF_MSG_TYPE_ENUM
{
    ID_CALL_CST_SETUP_REQ               = 0xC102,/* _H2ASN_MsgChoice CALL_CST_SETUP_REQ_STRU */
    ID_CALL_CST_CHANGE_REQ              = 0xC104,/* _H2ASN_MsgChoice CALL_CST_CHANGE_REQ_STRU */
    ID_CALL_CST_REL_REQ                 = 0xC108,/* _H2ASN_MsgChoice CALL_CST_REL_REQ_STRU */
    ID_CST_CALL_SETUP_CNF               = 0xC101,/* _H2ASN_MsgChoice CST_CALL_SETUP_CNF_STRU */
    ID_CST_CALL_CHANGE_CNF              = 0xC103,/* _H2ASN_MsgChoice CST_CALL_CHANGE_CNF_STRU */
    ID_CST_CALL_ERROR_IND               = 0xC105,/* _H2ASN_MsgChoice CST_CALL_ERROR_IND_STRU */
    ID_TRACE_AT_CST_DATA_REQ            = 0xC10e,/* _H2ASN_MsgChoice CST_TRACE_AT_CST_DATA_REQ_STRU */
    ID_TRACE_CST_AT_DATA_IND            = 0xC10f,/* _H2ASN_MsgChoice CST_TRACE_CST_AT_DATA_IND_STRU */
    ID_TRACE_CST_SET_FLOW_CTRL          = 0xC109,/* _H2ASN_MsgChoice CST_TRACE_SET_FLOW_CTRL_STRU */
    ID_TRACE_CST_CLEAR_FLOW_CTRL        = 0xC10A,/* _H2ASN_MsgChoice CST_TRACE_CLEAR_FLOW_CTRL_STRU */

    ID_CST_TAF_MSG_TYPE_BUTT     = 0xFFFF
};
typedef VOS_UINT16 CST_TAF_MSG_TYPE_ENUM_UINT16;


/*================*/ /*CST上报给CCA的错误编码*/
enum CST_ERR_IND_CAUSE_ENUM
{
    CST_SETUP_ERROR             = 0,       /*建立失败指示*/
    CST_CHANGE_ERROR            = 1,       /*修改失败指示*/
    CST_UNSYNC_ERROR            = 2,       /*失步指示 */
    CST_RLP_TRANS_ERROR         = 3,       /*RLP传输失败指示*/
    CST_IWF_DISC                = 4,        /*RLP收到IWF的DISC指示*/
    CST_ERR_IND_CAUSE_BUTT
};

typedef VOS_UINT16 CST_ERR_IND_CAUSE_ENUM_UINT16;

/*================*/ /* 速率类型 */
enum CST_RATE_TYPE_ENUM
{
    CST_RATE_VALUE_300 = 1,  /* 300 bit/s */
    CST_RATE_VALUE_1K2,      /* 1.2kbit/s */
    CST_RATE_VALUE_2K4,      /* 2.4kbit/s */
    CST_RATE_VALUE_4K8,      /* 4.8kbit/s */
    CST_RATE_VALUE_9K6,      /* 9.6kbit/s */
    CST_RATE_VALUE_12K,      /* 12kbit/s */
    CST_RATE_VALUE_14K4,     /* 14.4kbit/s */
    CST_RATE_VALUE_19K2,     /* 19.2kbit/s */
    CST_RATE_VALUE_28K8,     /* 28.8kbit/s */
    CST_RATE_VALUE_31K2,     /* 31.2kbit/s */
    CST_RATE_VALUE_32K,      /* 32kbit/s */
    CST_RATE_VALUE_33K6,     /* 33.6kbit/s */
    CST_RATE_VALUE_38K4,     /* 38.4kbit/s */
    CST_RATE_VALUE_48K,      /* 48kbit/s */
    CST_RATE_VALUE_56K,      /* 56kbit/s */
    CST_RATE_VALUE_64K,      /* 64kbit/s */
    CST_RATE_BUTT
};

typedef VOS_UINT8 CST_RATE_TYPE_ENUM_UINT8;

/*================*/ /* 物理信道类型 */
enum CST_TCH_TYPE_ENUM
{
    CST_TCH_NULL    = 0,
    CST_TCH_F_24    = 1,                        /* 全速率TCH_2.4 */
    CST_TCH_H_24,                               /* 半速率TCH_2.4 */
    CST_TCH_F_48,                               /* 全速率TCH_4.8 */
    CST_TCH_H_48,                               /* 半速率TCH_4.8 */
    CST_TCH_F_96,                               /* 全速率TCH_9.6 */
    CST_TCH_F_144,                              /* 全速率TCH_14.4 */
    CST_TCH_BUTT
};

typedef VOS_UINT8 CST_TCH_TYPE_ENUM_UINT8;

/*================*/ /* 奇偶校验类型 */
enum CST_PARITY_TYPE_ENUM
{
    CST_ODD_PARITY                  = 0,        /* 奇校验   */
    CST_EVEN_PARITY                 = 2,        /* 偶校验   */
    CST_NONE_PARITY                 = 3,        /* 不校验   */
    CST_FORC_0_PARITY               = 4,        /* 强制加0 */
    CST_FORC_1_PARITY               = 5,        /* 强制加1 */
    CST_PARITY_BUTT
};

typedef VOS_UINT8 CST_PARITY_TYPE_ENUM_UINT8;

/*================*/ /* 数据的同异步类型 */
enum CST_SYNC_TYPE_ENUM
{
    CST_SYNC_TYPE_SYNC              = 0,
    CST_SYNC_TYPE_ASYNC             = 1,
    CST_SYNC_TYPE_BUTT
};

typedef VOS_UINT8 CST_SYNC_TYPE_ENUM_UINT8;

/*================*/ /* 业务的透明/非透明类型 */
enum CST_TRAN_TYPE_ENUM
{
    CST_TRAN_TYPE_TRANSPARENT       = 0,
    CST_TRAN_TYPE_NON_TRANSPARENT   = 1,
    CST_TRAN_TYPE_BUTT
};

typedef VOS_UINT8 CST_TRAN_TYPE_ENUM_UINT8;

/*================*/ /* 接入网类型 */
enum CST_TRAN_MODE_ENUM
{
    CST_TRAN_MODE_GSM               = 0,
    CST_TRAN_MODE_UMTS              = 1,
    CST_TRAN_MODE_BUTT
};

typedef VOS_UINT8 CST_TRAN_MODE_ENUM_UINT8;

/*================*/ /* 数据的比特位个数 */
enum CST_DATA_BIT_NUM_ENUM
{
    CST_DATA_BIT_NUM_7              = 0,
    CST_DATA_BIT_NUM_8              = 1,
    CST_DATA_BIT_NUM_BUTT
};

typedef VOS_UINT8 CST_DATA_BIT_NUM_ENUM_UINT8;

/*================*/ /* Stop比特位的个数 */
enum CST_STOP_BIT_NUM_ENUM
{
    CST_STOP_BIT_NUM_1              = 0,
    CST_STOP_BIT_NUM_2              = 1,
    CST_STOP_BIT_NUM_BUTT
};

typedef VOS_UINT8 CST_STOP_BIT_NUM_ENUM_UINT8;

/*================*/ /* 是否采用压缩 */
enum CST_COMPRESS_ENUM
{
    CST_COMPRESS_NOT_ADOPT          = 0,        /* 不采用压缩 */
    CST_COMPRESS_ADOPT              = 1,        /* 采用压缩 */
    CST_COMPRESS_BUTT
};

typedef VOS_UINT8 CST_COMPRESS_ENUM_UINT8;

/*================*/ /* 呼叫方向枚举 */
enum CST_CALL_DIR_ENUM
{
    CST_CALL_DIR_MO             = 0,
    CST_CALL_DIR_MT             = 1,
    CST_CALL_DIR_BUTT
};

typedef VOS_UINT8 CST_CALL_DIR_ENUM_UINT8;

/*================*/ /* 传真类型枚举 */
enum CST_FAX_CLASS_ENUM
{
    CST_FAX_CLASS_1_0           = 1,
    CST_FAX_CLASS_BUTT
};

typedef VOS_UINT8 CST_FAX_CLASS_ENUM_UINT8;

/*****************************************************************************
  4 STRUCT定义
*****************************************************************************/
#pragma pack(4)

/*****************************************************************************
 结构名    : CST_SETUP_PARAM_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :CALL_CST_SETUP_REQ_STRU结构中的参数结构
*****************************************************************************/
typedef struct
{
    CST_TRAN_TYPE_ENUM_UINT8    enTranType;      /* 业务透明/非透明数据类型*/
    CST_TRAN_MODE_ENUM_UINT8    enTranMode;      /* GSM还是WCDMA*/
    VOS_UINT8                   ucRbId;          /* RbId,仅在网络模式是WCDMA时有意义*/
    VOS_UINT8                   ucRsv[3];
    CST_RATE_TYPE_ENUM_UINT8    enUsrRate;       /* 用户速率*/
    CST_TCH_TYPE_ENUM_UINT8     enTchType;       /* 物理信道类型 */

    CST_PARITY_TYPE_ENUM_UINT8  enParityType;    /*奇偶校验类型*/
    CST_SYNC_TYPE_ENUM_UINT8    enSyncType;      /*传输类型:0为同步传输 1为异步传输*/
    CST_DATA_BIT_NUM_ENUM_UINT8 enDataBitNum;    /*数据的比特位个数*/
    CST_STOP_BIT_NUM_ENUM_UINT8 enStopBitNum;    /*Stop比特位的个数*/

    CST_COMPRESS_ENUM_UINT8     enCompressAdopt; /*是否进行压缩
                                                   1: 接收 2: 拒绝;
                                                   适用于非透明模式*/
    VOS_UINT8                   ucFaxCall;       /* 是否传真, VOS_YES:传真业务, VOS_NO:非传真业务*/
    CST_CALL_DIR_ENUM_UINT8     enCallDir;       /* 呼叫方向 */
    CST_FAX_CLASS_ENUM_UINT8    enFaxClass;      /* 传真类型 */
}CST_SETUP_PARAM_STRU;

/*****************************************************************************
 结构名    : CALL_CST_SETUP_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :ID_CALL_CST_SETUP_REQ对应的消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                         /* 消息头 */ /*_H2ASN_Skip*/
    VOS_UINT16                  usMsgType; /* 消息类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                  usTransId; /* 传输标识 */
    CST_SETUP_PARAM_STRU        stCSTPara;
}CALL_CST_SETUP_REQ_STRU;

/*****************************************************************************
 结构名    : CST_ATRLP_PARAM_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :CALL_CST_CHANGE_REQ_STRU中的参数结构
*****************************************************************************/
typedef struct
{
    CST_TRAN_MODE_ENUM_UINT8    enTranMode;     /* GSM还是WCDMA*/
    CST_TCH_TYPE_ENUM_UINT8     enTchType;      /* 信道类型*/
    VOS_UINT8                   aucRsv[2];      /* 保留*/
}CST_CHANGE_PARAM_STRU;

/*****************************************************************************
 结构名    : CALL_CST_CHANGE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :ID_CALL_CST_CHANGE_REQ对应的消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                            /* 消息头 */ /*_H2ASN_Skip*/
    VOS_UINT16                  usMsgType;    /* 消息类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                  usTransId;
    CST_CHANGE_PARAM_STRU       stChangPara;
}CALL_CST_CHANGE_REQ_STRU;

/*****************************************************************************
 结构名    : CALL_CST_REL_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :ID_CALL_CST_REL_REQ对应的消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                          /* 消息头 */ /*_H2ASN_Skip*/
    VOS_UINT16          usMsgType;          /* 消息类型 */ /*_H2ASN_Skip*/
    VOS_UINT16          usTransId;
}CALL_CST_REL_REQ_STRU;

/*****************************************************************************
 结构名    : CST_CALL_SETUP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :CST配置成功后,上报给CCA确认
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                          /* 消息头 */ /*_H2ASN_Skip*/
    VOS_UINT16          usMsgType;          /* 消息类型 */ /*_H2ASN_Skip*/
    VOS_UINT16          usTransId;
}CST_CALL_SETUP_CNF_STRU;

/*****************************************************************************
 结构名    : CST_CALL_CHANGE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :CST修改配置成功后,上报给CCA确认
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                          /* 消息头 */ /*_H2ASN_Skip*/
    VOS_UINT16          usMsgType;          /* 消息类型 */ /*_H2ASN_Skip*/
    VOS_UINT16          usTransId;
}CST_CALL_CHANGE_CNF_STRU;

/*****************************************************************************
 结构名    : CST_CALL_ERROR_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :CST发给CCA的错误状态指示
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                              /* 消息头 */ /*_H2ASN_Skip*/
    VOS_UINT16                      usMsgType;  /* 消息类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                      usTransId;
    CST_ERR_IND_CAUSE_ENUM_UINT16   usErrId;    /* 错误指示ID,定义见CST_ERR_IND_CAUSE_ENUM*/
    VOS_UINT8                       aucRsv[2];  /* 保留 */
}CST_CALL_ERROR_IND_STRU;


/*****************************************************************************
 结构名    : CST_TRACE_AT_CST_DATA_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :假消息ID_CST_TRACE_AT_CST_DATA_REQ的结构体
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */ /*_H2ASN_Skip*/
    VOS_UINT16                      usMsgType;          /* 消息类型 */ /*_H2ASN_Skip*/

    VOS_UINT16                      ulDataLen;          /* 数据长度, 单位: BYTE */
    VOS_UINT8                       aucData[4];         /* 数据部分，与前面字节一起属于连续的消息内存空间 */
    /******************************************************************************************************
         _H2ASN_Array2String
    ******************************************************************************************************/

} CST_TRACE_AT_CST_DATA_REQ_STRU;

/*****************************************************************************
 结构名    : CST_TRACE_CST_AT_DATA_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :假消息ID_CST_TRACE_CST_AT_DATA_IND的结构体
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */ /*_H2ASN_Skip*/
    VOS_UINT16                     usMsgType;          /* 消息类型 */ /*_H2ASN_Skip*/

    VOS_UINT16                     ulDataLen;           /* 数据的长度, 单位: BYTE*/
    VOS_UINT8                      aucData[4];          /* 数据部分，与前面字节一起属于连续的消息内存空间 */
    /******************************************************************************************************
       _H2ASN_Array2String
    ******************************************************************************************************/

} CST_TRACE_CST_AT_DATA_IND_STRU;

/*****************************************************************************
 结构名    : CST_TRACE_SET_FLOW_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :假消息ID_TRACE_CST_SET_FLOW_CTRL的结构体
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */ /*_H2ASN_Skip*/
    VOS_UINT16                     usMsgType;          /* 消息类型 */ /*_H2ASN_Skip*/

    VOS_UINT16                     usBuffUsedLen;           /* 数据的长度, 单位: BYTE*/
} CST_TRACE_SET_FLOW_CTRL_STRU;

/*****************************************************************************
 结构名    : CST_TRACE_CLEAR_FLOW_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :假消息ID_TRACE_CST_CLEAR_FLOW_CTRL的结构体
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */ /*_H2ASN_Skip*/
    VOS_UINT16                     usMsgType;          /* 消息类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                     usBuffUsedLen;           /* 数据的长度, 单位: BYTE*/

} CST_TRACE_CLEAR_FLOW_CTRL_STRU;


/*****************************************************************************
 结构名    : CST_UL_MODEM_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :上行行状态信息结构, DC模块用此结构向下传输状态信息
*****************************************************************************/
typedef struct
{
    VOS_UINT8           ucCt105;        /* 方向:MT->IWF, 代表 SB */
    VOS_UINT8           ucCt1082;       /* 方向:MT->IWF, 代表 SA */
    VOS_UINT8           ucCt133;        /* 方向:MT->IWF, 代表 X */
    VOS_UINT8           ucBreakSig;     /* break信号有效:1 , 无效:0 */
}CST_UL_MODEM_STRU;
/*****************************************************************************
 结构名    : AT_DL_MODEM_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :下行状态信息,上报给AT模块
*****************************************************************************/
typedef struct
{
    VOS_UINT8           ucCt107;        /* 方向:IWF->MT, 代表 SA */
    VOS_UINT8           ucCt109;        /* 方向:IWF->MT, 代表 SB */
    VOS_UINT8           ucCt106;        /* 方向:IWF->MT, 代表 X */
    VOS_UINT8           ucBreakSig;     /* break信号有效:1 , 无效:0 */
}AT_DL_MODEM_STRU;
/*****************************************************************************
 结构名    : CST_ATRLP_PARAM_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32          OP_Ver      : 1;    /* ucVer是否有效.1:有效,0:无效 */
    VOS_UINT32          OP_KIM      : 1;    /* ucKIM是否有效.1:有效,0:无效 */
    VOS_UINT32          OP_KMI      : 1;    /* ucKMI是否有效.1:有效,0:无效 */
    VOS_UINT32          OP_TimerT1  : 1;    /* ucTimerT1是否有效.1:有效,0:无效 */
    VOS_UINT32          OP_CountN2  : 1;    /* ucCountN2是否有效.1:有效,0:无效 */
    VOS_UINT32          OP_TimerT4  : 1;    /* ucTimerT4是否有效.1:有效,0:无效 */
    VOS_UINT8           ucVer;              /* RLP的版本: 有0,1,2三种 */
    VOS_UINT8           ucKIM;              /* 接收窗口的大小，RLP版本0、1时，单位:1; RLP版本2时，单位:8 */
    VOS_UINT8           ucKMI;              /* 发送窗口的大小，RLP版本0、1时，单位:1; RLP版本2时，单位:8 */
    VOS_UINT8           ucTimerT1;          /* 定时器T1的长度，单位:10ms */
    VOS_UINT8           ucCountN2;          /* 重传的次数 */
    VOS_UINT8           ucTimerT4;          /* 定时器T4的长度，单位:10ms */
    VOS_UINT8           aucRsv[2];          /* 保留 */
}CST_ATRLP_PARAM_STRU;


/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    CST_TAF_MSG_TYPE_ENUM_UINT16        enMsgID;    /*_H2ASN_MsgChoice_Export CST_TAF_MSG_TYPE_ENUM_UINT16*/

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          CST_TAF_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}CST_TAF_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    CST_TAF_MSG_DATA                    stMsgData;
}CstNasInterface_MSG;



#pragma pack(0)

/*****************************************************************************
  5 UNION定义
*****************************************************************************/

/*****************************************************************************
  6 全局变量声明
*****************************************************************************/

/*****************************************************************************
  7 函数申明
*****************************************************************************/
#if (FEATURE_ON == FEATURE_CSD)
extern VOS_UINT32  AT_CstDlDataInd(VOS_UINT8 *pDlData, VOS_UINT16 usDataLen,
    AT_DL_MODEM_STRU *pstModem);
#endif


extern VOS_UINT32 CST_SendCtrlInfVal(CST_UL_MODEM_STRU *pstCtrlInf);
extern VOS_VOID DC_CstActFlowCtrl(VOS_BOOL bActive);
extern VOS_UINT32 CST_SetRlpParam(CST_ATRLP_PARAM_STRU* pstParam);
extern VOS_UINT32 CST_QueryRlpParam(CST_ATRLP_PARAM_STRU* pstParam);

/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* The end*/


