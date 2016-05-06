/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BastetTrrcInterface.h
  版 本 号   : 初稿
  作    者   : s00211350
  生成日期   : 2014年11月10日
  最近修改   :
  功能描述   : Trrc和Bastet模块接口头文件定义
  函数列表   :
  修改历史   :
  1.日    期   : 2014年11月10日
    作    者   : s00211350
    修改内容   : 创建文件

******************************************************************************/

#ifndef __BASTETTRRCINTERFACE_H__
#define __BASTETTRRCINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define TRRC_BASTET_MSG_HDR                  (0)
#define BASTET_TRRC_MSG_HDR                  (0)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
  枚举名    : TRRC_BASTET_MSG_ID_ENUM
  协议表格  :
  ASN.1描述 :
  枚举说明  : TRRC和Bastet模块消息定义
*****************************************************************************/
enum TRRC_BASTET_MSG_ID_ENUM
{
    /* TRRC发给Bastet的消息原语 */
    ID_TRRC_BASTET_RRC_STATUS_IND           = TRRC_BASTET_MSG_HDR + 0x00,         /* _H2ASN_MsgChoice TRRC_BASTET_STATUS_IND_STRU */
    ID_TRRC_BASTET_SERVICE_CELL_INFO_IND    = TRRC_BASTET_MSG_HDR + 0x01,         /* _H2ASN_MsgChoice TRRC_BASTET_SERVICE_CELL_INFO_IND_STRU */
    ID_TRRC_BASTET_ID_ENUM_BUTT
};
typedef VOS_UINT32  TRRC_BASTET_MSG_ID_ENUM_UINT32;

enum BASTET_TRRC_STATE_ENUM
{
    BASTET_TRRC_STATE_IDLE              = 0,         /* IDLE态 */
    BASTET_TRRC_STATE_CELL_PCH             ,         /* CELL_PCH态 */
    BASTET_TRRC_STATE_URA_PCH              ,         /* URA_PCH态 */
    BASTET_TRRC_STATE_CELL_FACH            ,         /* CELL_FACH态 */
    BASTET_TRRC_STATE_CELL_DCH             ,         /* CELL_DCH态 */

    BASTET_TRRC_STATE_BUTT
};
typedef VOS_UINT8 BASTET_TRRC_STATE_ENUM_UINT8;
/*****************************************************************************
  4 STRUCT定义
*****************************************************************************/
/*****************************************************************************
  结构名    : TRRC_BASTET_STATUS_IND_STRU
  协议表格  :
  ASN.1描述 :
  结构说明  : TRRC给Bastet模块发送RRC状态消息定义
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;           /*_H2ASN_Skip*/
    BASTET_TRRC_STATE_ENUM_UINT8        enRrcState;          /* 当前RRC状态 */
    VOS_UINT8                           aucReserved[3];      /* 字节对齐 */
} TRRC_BASTET_STATUS_IND_STRU;


/*****************************************************************************
 结构名称   : TRRC_BASTET_SERVICE_CELL_INFO_IND_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : TDS服务小区信息
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;           /*_H2ASN_Skip*/

    VOS_UINT32                          ulCellId;
    VOS_INT16                           sRscp;                /*范围(-141,-44),99为无效*/
    VOS_UINT8                           aucResv[2];
}TRRC_BASTET_SERVICE_CELL_INFO_IND_STRU;



/*****************************************************************************
  5 全局变量声明
*****************************************************************************/


/*****************************************************************************
  6 消息头定义
*****************************************************************************/


/*****************************************************************************
  7 消息定义
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
    TRRC_BASTET_MSG_ID_ENUM_UINT32          enMsgID;    /*_H2ASN_MsgChoice_Export TRRC_BASTET_MSG_ID_ENUM_UINT32*/

    VOS_UINT8                               aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TRRC_BASTET_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}Bastet_TRRC_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    Bastet_TRRC_MSG_DATA                    stMsgData;
}BastetTrrcInterface_MSG;


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

#endif /* end of BastetTrrcInterface.h */
