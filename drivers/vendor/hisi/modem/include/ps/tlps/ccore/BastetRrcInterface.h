/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BastetRrcInterface.h
  版 本 号   : 初稿
  作    者   : z00128442
  生成日期   : 2014年11月10日
  最近修改   :
  功能描述   : 定义BASTET 模块发送给LRRC模块的消息
  函数列表   :
  修改历史   :
  1.日    期   : 2014年11月02日
    作    者   : z00128442
    修改内容   : 创建文件

 ******************************************************************************/

#ifndef __BASTETRRCINTERFACE_H__
#define __BASTETRRCINTERFACE_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "PsTypeDef.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define LRRC_BASTET_MSG_HDR                  (0)
#define BASTET_LRRC_MSG_HDR                  (0)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum BASTET_LRRC_MSG_TYPE_ENUM
{
    /* 消息名称 */                              /* 消息ID */                    /* 备注 */
    ID_BASTET_LRRC_CON_TO_IDLE_NTF              = LRRC_BASTET_MSG_HDR + 0x00,   /* _H2ASN_MsgChoice BASTET_RRC_LTE_TO_IDLE_REQ_STRU */
    ID_LRRC_BASTET_RRC_STATUS_IND               = LRRC_BASTET_MSG_HDR + 0x01,   /* _H2ASN_MsgChoice BASTET_RRC_LRRC_STATUS_IND_STRU */
    ID_LRRC_BASTET_SERVICE_CELL_INFO_IND        = LRRC_BASTET_MSG_HDR + 0x02,   /* _H2ASN_MsgChoice LRRC_BASTET_SERVICE_CELL_INFO_IND_STRU */

    ID_BASTET_LRRC_MSG_TYPE_BUTT
};
typedef VOS_UINT32 BASTET_LRRC_MSG_TYPE_ENUM_UINT32;



enum BASTET_LRRC_STATE_ENUM
{
    BASTET_LRRC_STATE_IDLE          = 0,
    BASTET_LRRC_STATE_CONNECTED,
    BASTET_LRRC_STATE_BUTT
};
typedef VOS_UINT8 BASTET_LRRC_STATE_ENUM_UINT8;



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

/*******************************************************************************
 结构名    : BASTET_RRC_LTE_TO_IDLE_REQ_STRU
 结构说明  :
 1.日    期   : 2014年11月12日
   作    者   : z00128442
   修改内容   : 新增结构

*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             stMsgHeader;                    /*_H2ASN_Skip*/
}BASTET_RRC_LTE_TO_IDLE_REQ_STRU;


/*******************************************************************************
 结构名    : BASTET_RRC_LRRC_STATUS_IND_STRU
 结构说明  :
 1.日    期   : 2014年11月12日
   作    者   : z00128442
   修改内容   : 新增结构

*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             stMsgHeader;                    /*_H2ASN_Skip*/
    BASTET_LRRC_STATE_ENUM_UINT8                enRrcState;
    VOS_UINT8                                   enReserve[3];
}BASTET_RRC_LRRC_STATUS_IND_STRU;


/*****************************************************************************
 结构名称   : LRRC_BASTET_SERVICE_CELL_INFO_IND_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : LTE服务小区信息
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;            /*_H2ASN_Skip*/

    VOS_UINT32                          ulCellId;
    VOS_INT16                           sRsrp;                /*范围(-141,-44),99为无效*/
    VOS_INT16                           sRsrq;                /*范围(-40,-6),99为无效*/
}LRRC_BASTET_SERVICE_CELL_INFO_IND_STRU;



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
    BASTET_LRRC_MSG_TYPE_ENUM_UINT32          enMsgID;    /*_H2ASN_MsgChoice_Export BASTET_LRRC_MSG_TYPE_ENUM_UINT32*/

    VOS_UINT8                                 aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          BASTET_LRRC_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}BASTET_RRC_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    BASTET_RRC_MSG_DATA                       stMsgData;
}BastetRrcInterface_MSG;



/*****************************************************************************
  10 函数声明
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

