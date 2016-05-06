/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : GPhyCstInterface.h
  Author      : x44545
  Version     : V100R002
  Date        : 2006-08-01
  Description : 该头文件定义了CST与GHPA之间的接口
  History     :
  1. Date     : 2006-08-01
     Author   : x44545
     Modification: Create
************************************************************************/

#ifndef _GPHYCSTINTERFACE_H_
#define _GPHYCSTINTERFACE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
   其他头文件包含
*****************************************************************************/
#include "vos.h"

/*****************************************************************************
   宏定义
*****************************************************************************/

/*CST与GPHY之间的原语*/
#define ID_CST_PH_DATA_REQ                      0xD751
#define ID_PH_CST_READY_TO_SEND                 0x7D52

/*****************************************************************************
   全局变量声明
*****************************************************************************/
#pragma pack(4)

/*****************************************************************************

*****************************************************************************/
typedef struct
{
    VOS_UINT16   usMsgType;       /* 消息ID */
    VOS_UINT16   usChanType;   /* 上行发送TCH信道类型*/
} PH_CST_READY_TO_SEND_STRU;

/* ===== 1. 消息  =====*/
typedef struct
{
    VOS_MSG_HEADER
    PH_CST_READY_TO_SEND_STRU stSendInd;
} GHPA_CST_READY_TO_SEND_MSG;

#define CST_DL_BUF_LEN  19

typedef struct
{
    VOS_UINT16   usMsgType;         /* 上行数据消息*/
    VOS_UINT16   usErrorFlag;       /* 译码错误指示*/
    VOS_UINT16   usTn;              /* 时隙号*/
    VOS_UINT16   ausRsv;            /* 对齐保留*/
    VOS_UINT32   ulFrmNum;          /* 当前帧号*/
    VOS_UINT16   usBitLen;          /* 数据的bit长度*/
    VOS_UINT16   ausBitData[CST_DL_BUF_LEN]; /* 数据区 */
}PH_CST_DATA_IND_STRU;

/*GSM的下行数据指示消息*/
typedef struct
{
    VOS_MSG_HEADER
    PH_CST_DATA_IND_STRU stSendReq;
} PH_CST_DATA_IND_MSG;


typedef struct
{
    VOS_UINT16   usMsgType;   /* 上行数据消息*/
    VOS_UINT16   ausRsv;      /* 对齐保留*/
    VOS_UINT16   usBitLen;    /* 数据的bit长度*/
    VOS_UINT16   ausBitData[CST_DL_BUF_LEN];  /* 数据区 */
}CST_PH_DATA_REQ_STRU;

/* =====   =====*/
typedef struct
{
    VOS_MSG_HEADER
    CST_PH_DATA_REQ_STRU stSendReq;
} CST_PH_DATA_REQ_MSG;

/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/
#pragma pack(0)

/*****************************************************************************
  9 函数声明
*****************************************************************************/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* The end*/


