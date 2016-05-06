/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasPdcpInterface.h
  版 本 号   : 初稿
  作    者   : 查鸣峰
  生成日期   : 2006年11月30日
  最近修改   :
  功能描述   : NasPdcpInterface.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2006年11月30日
    作    者   : 查鸣峰
    修改内容   : 创建文件

******************************************************************************/

#ifndef __NASPDCPINTERFACE_H__
#define __NASPDCPINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "WUeSpec.h"
#include "TtfDrvInterface.h"                                                           /* _H2ASN_Skip */
#include "NasTtf_typedef.h"

/* _H2ASN_Include PsTypeDef.h */

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define PS_NSAPI_NUM  16


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/* 原语标识 */
enum NAS_PDCP_MSG_TYPE_ENUM
{
    ID_RABM_PDCP_DATA_REQ           =   0x0013,             /* _H2ASN_MsgChoice RABM_PDCP_DATA_REQ_STRU */
    ID_PDCP_RABM_DATA_IND           =   0x0014,             /* _H2ASN_MsgChoice */ /* 目前下行数据直接走API，不发送该消息 */

    ID_RABM_PDCP_DATA_RESUME_IND    =   0x0015,             /* _H2ASN_MsgChoice RABM_PDCP_DATA_RESUME_IND_STRU*/
    ID_PDCP_RABM_DATA_RESUME_RSP    =   0x0016,             /* _H2ASN_MsgChoice PDCP_RABM_DATA_RESUME_RSP_STRU*/

    ID_RABM_PDCP_SAVE_DATA_IND      =   0x0017,             /* _H2ASN_MsgChoice RABM_PDCP_SAVE_DATA_IND_STRU*/
    ID_PDCP_RABM_SAVE_DATA_RSP      =   0x0018,             /* _H2ASN_MsgChoice PDCP_RABM_SAVE_DATA_RSP_STRU */

    ID_RABM_PDCP_TC_DATA_REQ        =   0x0019,             /* _H2ASN_MsgChoice RABM_PDCP_TC_DATA_REQ_STRU */
    ID_PDCP_RABM_TC_DATA_IND        =   0x001A,             /* _H2ASN_MsgChoice PDCP_RABM_TC_DATA_IND_STRU */

    ID_PDCP_RABM_TC_DATA_IND_NOTIFY =   0x001C,             /* _H2ASN_MsgChoice PDCP_RABM_TC_DATA_IND_NOTIFY_STRU */

    ID_RABM_PDCP_TRACE_DATA_REQ     =   0x8013,             /* _H2ASN_MsgChoice RABM_PDCP_TRACE_DATA_REQ_STRU */
    ID_PDCP_RABM_TRACE_DATA_IND     =   0x8014,             /* _H2ASN_MsgChoice PDCP_RABM_TRACE_DATA_IND_STRU */

    ID_RABM_PDCP_TRACE_TC_DATA_REQ  =   0x8019,             /* _H2ASN_MsgChoice RABM_PDCP_TRACE_DATA_REQ_STRU */
    ID_PDCP_RABM_TRACE_TC_DATA_IND  =   0x801A,             /* _H2ASN_MsgChoice PDCP_RABM_TRACE_DATA_IND_STRU */

    ID_NAS_PDCP_MSG_TYPE_BUTT
} ;
typedef VOS_UINT16 NAS_PDCP_MSG_TYPE_ENUM_UINT16;

enum RABMPDCPITF_RSLT_ENUM
{
    RABMPDCPITF_SUCC                         = 0,
    RABMPDCPITF_FAIL                         ,
    RABMPDCPITF_RSLT_BUTT
};
typedef VOS_UINT32   RABMPDCPITF_RSLT_ENUM_UINT32;


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

/******************************************************************************
*     RABM_PDCP_DATA_REQ_STRU 原语定义
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /* _H2ASN_Skip */
    NAS_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT8                           ucRbId;             /* [5,32],标志PDCP实体 */
    VOS_UINT8                           aucReserve[1];      /* 4字节对齐，保留*/
    VOS_UINT32                          ulDataBitLen;
    TTF_MEM_ST                         *pstDataMem;         /* PDCP SDU地址 */  /* _H2ASN_Replace VOS_UINT32 *pstDataMem */
}RABM_PDCP_DATA_REQ_STRU;



/******************************************************************************
*     PDCP_RABM_DATA_IND_STRU 原语定义，因为使用函数接口，
                              该结构只是RABM使用，PDCP不使用
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /* _H2ASN_Skip */
    NAS_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT8                           ucRbId;             /* [5,32] 标识与该RB ID对应的PDCP实体*/
    VOS_UINT8                           aucReserve1[1];     /* 4字节对齐，保留*/
    VOS_UINT32                          ulDataLen;
    TTF_MEM_ST                         *pstDataMem;        /* PDCP SDU地址 */  /* _H2ASN_Replace VOS_UINT32 *pstDataMem */
} PDCP_RABM_DATA_IND_STRU;

/******************************************************************************
*     RABM_PDCP_TC_DATA_REQ_STRU 原语定义
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /* _H2ASN_Skip */
    NAS_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT8                           ucRbId;             /* [5,32],标志PDCP实体 */
    VOS_UINT8                           aucReserve[1];      /* 4字节对齐，保留*/
    VOS_UINT32                          ulDataBitLen;       /* 单位:bit，对AM,UM,TM都是有效值*/
    TTF_MEM_ST                         *pstDataMem;         /* PDCP SDU地址 */  /* _H2ASN_Replace VOS_UINT32 *pstDataMem */
}RABM_PDCP_TC_DATA_REQ_STRU;



/******************************************************************************
*     PDCP_RABM_TC_DATA_IND_STRU 原语定义，用于PS域环回功能下行数据接口
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /* _H2ASN_Skip */
    NAS_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT8                           ucRbId;             /* [5,32] 标识与该RB ID对应的PDCP实体*/
    VOS_UINT8                           aucReserve1[1];     /* 4字节对齐，保留*/
    DL_DATA_CRC_INFO_STRU               stCrcInfo;          /* Crc信息，只供PS域环回模式二使用,PS域环回模式一不关心该属性  */
    VOS_UINT32                          ulDataBitLen;       /* 数据的长度，单位: Bit，因为环回，有可能数据长度非整数字节 */
    TTF_MEM_ST                         *pstDataMem;        /* PDCP SDU地址 */  /* _H2ASN_Replace VOS_UINT32 *pstDataMem */
} PDCP_RABM_TC_DATA_IND_STRU;

/******************************************************************************
*     PDCP_RABM_TC_DATA_Q_NODE_STRU 原语定义，用于PS域环回功能下行数据结点
******************************************************************************/
typedef struct
{
    TTF_NODE_ST                         stQNode;
    VOS_UINT8                           ucRbId;             /* [5,32] 标识与该RB ID对应的PDCP实体*/
    VOS_UINT8                           aucReserve[3];      /* 4字节对齐，保留*/
    DL_DATA_CRC_INFO_STRU               stCrcInfo;          /* Crc信息，只供PS域环回模式二使用,PS域环回模式一不关心该属性  */
    VOS_UINT32                          ulDataBitLen;       /* 数据的长度，单位: Bit，因为环回，有可能数据长度非整数字节 */
    TTF_MEM_ST                         *pstDataMem;         /* PDCP SDU地址 */  /* _H2ASN_Replace VOS_UINT32 *pstDataMem */
} PDCP_RABM_TC_DATA_Q_NODE_STRU;

/******************************************************************************
*     PDCP_RABM_DATA_BUF_STRU
******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRbId;
    VOS_UINT8                           ucRcvNPduNum;       /*RCV NPDU NUM*/
    VOS_UINT8                           aucReserve[2];
} PDCP_NUM_INFO;

typedef struct
{
    PS_BOOL_ENUM_UINT8                  enValidInd;         /* PS_FALSE:当前NSAPI无效   PS_TRUE:当前NSAPI有效 */
    VOS_UINT8                           ucRbId;             /* 该RAB所对应的RbId */
    VOS_UINT8                           aucReserve[2];      /* 4字节对齐，保留 */
}PDCP_NSAPI_MAP_RB_INFO;

/******************************************************************************
*     RABM_PDCP_DATA_RESUME_IND 原语定义
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /* _H2ASN_Skip */
    NAS_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    PDCP_NSAPI_MAP_RB_INFO              astNsapiMapRb[PS_NSAPI_NUM];  /*数组索引值为NSAPI*/
    VOS_UINT8                           aucReserve[2];      /* 4字节对齐，保留 */
}RABM_PDCP_DATA_RESUME_IND_STRU;

/******************************************************************************
*     PDCP_RABM_DATA_RESUME_RSP 原语定义
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /* _H2ASN_Skip */
    NAS_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve[2];      /* 4字节对齐，保留 */
    RABMPDCPITF_RSLT_ENUM_UINT32        enResult;
}PDCP_RABM_DATA_RESUME_RSP_STRU;

/******************************************************************************
*     RABM_PDCP_SAVE_DATA_IND 原语定义
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /* _H2ASN_Skip */
    NAS_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve[2];      /* 4字节对齐，保留 */
}RABM_PDCP_SAVE_DATA_IND_STRU;

/******************************************************************************
*     PDCP_RABM_SAVE_DATA_RSP 原语定义
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /* _H2ASN_Skip */
    NAS_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* 消息类型 */      /* _H2ASN_Skip */
    VOS_UINT8                           ucRbCnt;            /* RB 个数 */
    VOS_UINT8                           aucReserve[1];
    PDCP_NUM_INFO                       astPdcpNumInfo[PS_WUE_MAX_PS_RB_NUM]; /* PDCP 个数信息结构体 */
} PDCP_RABM_SAVE_DATA_RSP_STRU;

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
    NAS_PDCP_MSG_TYPE_ENUM_UINT16       enMsgID;    /*_H2ASN_MsgChoice_Export NAS_PDCP_MSG_TYPE_ENUM_UINT16*/

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          NAS_PDCP_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}NAS_PDCP_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    NAS_PDCP_MSG_DATA                   stMsgData;
}NasPdcpInterface_MSG;



/*****************************************************************************
  10 函数声明
*****************************************************************************/

VOS_UINT32 RABM_EnqueueTcData(PDCP_RABM_TC_DATA_Q_NODE_STRU *pstNode);
VOS_UINT32 WTTF_PDCP_RcvRabmData(VOS_UINT8 ucRbId, TTF_MEM_ST *pstData, VOS_UINT32 ulDataBitLen);
VOS_VOID  WTTF_PDCP_TrigRlcUlProc(VOS_VOID);




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

#endif /* end of NasPdcpInterface.h */
