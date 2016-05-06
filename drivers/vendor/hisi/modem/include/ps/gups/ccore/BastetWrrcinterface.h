/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BastetWrrcinterface.h
  版 本 号   : 初稿
  作    者   : s00211350
  生成日期   : 2014年11月10日
  最近修改   :
  功能描述   : Wrrc和Bastet模块接口头文件定义
  函数列表   :
  修改历史   :
  1.日    期   : 2014年11月10日
    作    者   : s00211350
    修改内容   : 创建文件

******************************************************************************/

#ifndef __BASTETWRRCINTERFACE_H__
#define __BASTETWRRCINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
typedef VOS_UINT32 ( *BST_WRRC_RECV_NET_QUAL_FUNC)(
    const VOS_UINT32        ulModemId,
    const VOS_UINT32        ulRatMode,
    const VOS_UINT32        ulCellId,
    const VOS_INT16         sRscp,
    const VOS_INT16         sEcio );
/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
  枚举名    : WRRC_BASTET_MSG_ID_ENUM
  协议表格  :
  ASN.1描述 :
  枚举说明  : WRRC给Bastet模块发送消息定义
*****************************************************************************/
enum WRRC_BASTET_MSG_ID_ENUM
{
    /* WRRC发给Bastet的消息原语 */
    ID_WRRC_BASTET_RRC_STATUS_IND       = 0,      /* _H2ASN_MsgChoice WRRC_BASTET_STATUS_IND_STRU */
    ID_WRRC_BASTET_NET_QUAL_CB,                   /* _H2ASN_MsgChoice BST_WRRC_REG_NET_CB_STRU */
    ID_WRRC_BASTET_ID_ENUM_BUTT
};
typedef VOS_UINT32 WRRC_BASTET_MSG_ID_ENUM_UINT32;

enum BASTET_WRRC_STATE_ENUM
{
    BASTET_WRRC_STATE_CELL_DCH          = 0,
    BASTET_WRRC_STATE_CELL_FACH         = 1,
    BASTET_WRRC_STATE_CELL_PCH          = 2,
    BASTET_WRRC_STATE_URA_PCH           = 3,
    BASTET_WRRC_STATE_IDLE              = 4,
    BASTET_WRRC_STATE_BUTT
};
typedef VOS_UINT8 BASTET_WRRC_STATE_ENUM_UINT8;

/*****************************************************************************
  4 STRUCT定义
*****************************************************************************/
/*****************************************************************************
  结构名    : WRRC_BASTET_RRC_STATUS_IND_STRU
  协议表格  :
  ASN.1描述 :
  结构说明  : WRRC给Bastet模块发送消息定义
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;           /*_H2ASN_Skip*/
    BASTET_WRRC_STATE_ENUM_UINT8        enRrcState;          /* 当前RRC状态 */
    VOS_UINT8                           aucReserved[3];      /* 字节对齐 */
} WRRC_BASTET_STATUS_IND_STRU;


/*****************************************************************************
 结构名    : BST_WRRC_REG_NET_CB_STRU
 结构说明  : BASTET与WRRC交互原语
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;          /*_H2ASN_Skip*/
    VOS_UINT32                          ulModemId;
    VOS_UINT32                          ulRatMode;
    BST_WRRC_RECV_NET_QUAL_FUNC         pfRcvCb;
} BST_WRRC_REG_NET_CB_STRU;


/*****************************************************************************
 结构名    : BST_WRRC_NET_QUAL_STRU
 结构说明  : WRRC模块接收回调结构体
 1.日    期   : 2015年06月04日
   作    者   : l00220658
   修改内容   : 新增结构

*****************************************************************************/
typedef struct
{
    VOS_UINT32                         ulModemId;
    VOS_UINT32                         ulRatMode;
    BST_WRRC_RECV_NET_QUAL_FUNC        pfFunCB;
}BST_WRRC_NET_QUAL_STRU;

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
    WRRC_BASTET_MSG_ID_ENUM_UINT32      enMsgID;    /*_H2ASN_MsgChoice_Export WRRC_BASTET_MSG_ID_ENUM_UINT32*/

    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          WRRC_BASTET_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}BASTET_Wrrc_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    BASTET_Wrrc_MSG_DATA                stMsgData;
}BastetWrrcinterface_MSG;


/*****************************************************************************
  10 函数声明
*****************************************************************************/


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

#endif /* end of BastetWrrcinterface.h */
