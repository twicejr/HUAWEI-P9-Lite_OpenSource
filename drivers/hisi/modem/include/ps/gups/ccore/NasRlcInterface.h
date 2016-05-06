/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasRlcInterface.h
  版 本 号   : 初稿
  作    者   : 查鸣峰
  生成日期   : 2006年12月21日
  最近修改   :
  功能描述   : NasRlcInterface.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2006年12月21日
    作    者   : 查鸣峰
    修改内容   : 创建文件

******************************************************************************/

#ifndef __NASRLCINTERFACE_H__
#define __NASRLCINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"               /* _H2ASN_Skip */
#include "TtfDrvInterface.h"        /* _H2ASN_Skip */
#include "NasTtf_typedef.h"     /* _H2ASN_Include PsTypeDef.h */

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/* 原语标识 */
enum NAS_RLC_MSG_TYPE_ENUM
{
    ID_RLC_RABM_CS_DATA_IND  =  0x0001, /* _H2ASN_MsgChoice RLC_RABM_CS_DATA_IND_STRU */

    ID_RABM_RLC_AM_DATA_REQ  =  0x0000, /* _H2ASN_MsgChoice RABM_RLC_AM_DATA_REQ_STRU */
    ID_RABM_RLC_UM_DATA_REQ  =  0x0002, /* _H2ASN_MsgChoice RABM_RLC_UM_DATA_REQ_STRU */
    ID_RABM_RLC_TM_DATA_REQ  =  0x0004, /* _H2ASN_MsgChoice RABM_RLC_TM_DATA_REQ_STRU */
    ID_TC_RLC_TEST_IND       =  0x0006, /* _H2ASN_MsgChoice TC_RLC_TEST_IND_STRU */

    ID_NAS_RLC_MSG_TYPE_BUTT
};
typedef VOS_UINT16 NAS_RLC_MSG_TYPE_ENUM_UINT16;


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
typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    NAS_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* message name */ /* _H2ASN_Skip */
    VOS_UINT8                           ucRbId;             /* 发送上层PDU使用的RB号, Vaule: [5, 32] */
    VOS_UINT8                           aucReserve[3];      /* 四字节对齐，保留 */
    VOS_UINT16                          usDataBitLen;       /* 上层PDU数据长度, 单位: Bit */
    TTF_MEM_ST                         *pstDataMem;         /* RLC SDU */ /* _H2ASN_Replace VOS_UINT32 *ppstDataMem */
} RABM_RLC_AM_DATA_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    NAS_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* message name */ /* _H2ASN_Skip */
    VOS_UINT8                           ucRbId;             /* 发送上层PDU使用的RB号, Value: 5-32 */
    VOS_UINT8                           aucReserve[3];      /* 四字节对齐，保留 */
    VOS_UINT16                          usDataBitLen;       /* 上层PDU数据长度, 单位: Bit */
    TTF_MEM_ST                         *pstDataMem;         /* RLC SDU */ /* _H2ASN_Replace VOS_UINT32 *ppstDataMem */
} RABM_RLC_UM_DATA_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    NAS_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* message name */ /* _H2ASN_Skip */
    VOS_UINT8                           ucRbId;             /* 发送上层PDU使用的RB号, Value: 0, 5-32 */
    VOS_UINT8                           aucReserve[3];      /* 四字节对齐，保留 */
    VOS_UINT16                          usDataBitLen;       /* 上层PDU数据长度, 单位: Bit */
    TTF_MEM_ST                         *pstDataMem;         /* RLC SDU */ /* _H2ASN_Replace VOS_UINT32 *ppstDataMem */
} RABM_RLC_TM_DATA_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    NAS_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* message name */ /* _H2ASN_Skip */
    VOS_UINT8                           ucRbId;             /* RB标识, Value: 5-32 */
    VOS_UINT8                           aucReserve1[1];      /* 四字节对齐，保留 */
    DL_DATA_CRC_INFO_STRU               stCrcInfo;
    VOS_UINT16                          usDataBitLen;       /* 数据的长度, 单位: Bit */
    VOS_UINT8                           aucReserve2[2];      /* 四字节对齐，保留 */
    VOS_UINT8                           *pucData;           /* 数据首地址 */
} RLC_RABM_CS_DATA_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                          /*消息头*/ /* _H2ASN_Skip */
    NAS_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /*消息类型*/ /* _H2ASN_Skip */
    TEST_LOOP_TYPE_ENUM_UINT8           enTcMode;           /*测试环回模式类型，只要当enTcAct=TEST_MODE_ACTIVE，时才有意义*/
    VOS_UINT8                           aucReserve[1];      /* 四字节对齐，保留 */
} TC_RLC_TEST_IND_STRU;

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
    NAS_RLC_MSG_TYPE_ENUM_UINT16        enMsgID;    /*_H2ASN_MsgChoice_Export NAS_RLC_MSG_TYPE_ENUM_UINT16*/

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          NAS_RLC_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}NAS_RLC_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    NAS_RLC_MSG_DATA                    stMsgData;
}NasRlcInterface_MSG;

/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern VOS_UINT32 WTTF_RLC_GetRbSuitableUlPduSize(VOS_UINT8  ucRbId   ,VOS_UINT32 ulPduSize,
                                      VOS_UINT8  ucCrcSize,VOS_UINT32 *pulUlPduSize);


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

#endif /* end of NasRlcInterface.h */
