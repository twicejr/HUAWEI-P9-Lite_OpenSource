/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : LTCPdcpInterface.h
  版 本 号   : 初稿
  作    者   : L62099
  生成日期   : 2009年10月9日
  最近修改   :
  功能描述   : TC与PDCP之间环回模式接口定义
  函数列表   :
  修改历史   :
  1.日    期   : 2009年10月9日
    作    者   : L62099
    修改内容   : 创建文件

******************************************************************************/
#ifndef __TCLPDCPINTERFACE_H__
#define __TCLPDCPINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif


#include "vos.h"
#include "LPSCommon.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif


/*----------------------------------------------*
 * 外部变量说明                                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 外部函数原型说明                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 内部函数原型说明                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 全局变量                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级变量                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 常量定义                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                       *
 *----------------------------------------------*/

#define LLOOP_BACK_MODE_MAX_LB_NUM       (8)

#define LTC_LPDCP_MSG_HDR                (PS_MSG_ID_LTC_TO_LPDCP_BASE)
#define LPDCP_LTC_MSG_HDR                (PS_MSG_ID_LPDCP_TO_LTC_BASE)

/*****************************************************************************
 结构名    : TC_LPDCP_MSG_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : TC和PDCP间的接口消息
*****************************************************************************/
enum LTC_LPDCP_MSG_TYPE_ENUM
{
    ID_LTC_LPDCP_ACTIVATE_TEST_MODE          = (LTC_LPDCP_MSG_HDR + 0x00),  /* _H2ASN_MsgChoice LTC_LPDCP_ACTIVATE_TEST_MODE_STRU */
    ID_LTC_LPDCP_ACTIVATE_TEST_MODE_CNF      = (LPDCP_LTC_MSG_HDR + 0x00),  /* _H2ASN_MsgChoice LTC_LPDCP_ACTIVATE_TEST_MODE_CNF_STRU */

    ID_LTC_LPDCP_START_TEST_LOOP             = (LTC_LPDCP_MSG_HDR + 0x01),  /* _H2ASN_MsgChoice LTC_LPDCP_START_TEST_LOOP_STRU */
    ID_LTC_LPDCP_START_TEST_LOOP_CNF         = (LPDCP_LTC_MSG_HDR + 0x01),  /* _H2ASN_MsgChoice LTC_LPDCP_START_TEST_LOOP_CNF_STRU */

    ID_LTC_LPDCP_STOP_TEST_LOOP              = (LTC_LPDCP_MSG_HDR + 0x02),  /* _H2ASN_MsgChoice LTC_LPDCP_STOP_TEST_LOOP_STRU */
    ID_LTC_LPDCP_STOP_TEST_LOOP_CNF          = (LPDCP_LTC_MSG_HDR + 0x02),  /* _H2ASN_MsgChoice LTC_LPDCP_STOP_TEST_LOOP_CNF_STRU */

    ID_LTC_LPDCP_DEACTIVATE_TEST_MODE        = (LTC_LPDCP_MSG_HDR + 0x03),  /* _H2ASN_MsgChoice LTC_LPDCP_DEACTIVATE_TEST_MODE_STRU */
    ID_LTC_LPDCP_DEACTIVATE_TEST_MODE_CNF    = (LPDCP_LTC_MSG_HDR + 0x03)   /* _H2ASN_MsgChoice LTC_LPDCP_DEACTIVATE_TEST_MODE_CNF_STRU */
};
typedef VOS_UINT32 LTC_LPDCP_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 结构名    : LTC_LPDCP_LOOPBACK_MODE_ENUM_UINT32
 协议表格  :
 ASN.1描述 :
 结构说明  : 环回模式类型枚举
*****************************************************************************/
enum LTC_LPDCP_LOOPBACK_MODE_ENUM
{
    LLOOP_BACK_MODE_A = 0,
    LLOOP_BACK_MODE_B = 1,
    LLOOP_BACK_MODE_BUTT
};
typedef VOS_UINT32 LTC_LPDCP_LOOPBACK_MODE_ENUM_UINT32;

/*****************************************************************************
 结构名    : LTC_LPDCP_ACTIVATE_TEST_MODE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 激活PDCP环回功能消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LTC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;           /*_H2ASN_Skip*/
    LTC_LPDCP_LOOPBACK_MODE_ENUM_UINT32  enLoopBackMode;
}LTC_LPDCP_ACTIVATE_TEST_MODE_STRU;

/*****************************************************************************
 结构名    : LTC_LPDCP_ACTIVATE_TEST_MODE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 激活PDCP环回功能确认消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LTC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;           /*_H2ASN_Skip*/
    VOS_UINT32                         ulResult;
}LTC_LPDCP_ACTIVATE_TEST_MODE_CNF_STRU;


/*****************************************************************************
 结构名    : LLOOP_BACK_DRB_SETUP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 环回模式A时扩展参数设置结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDrbId;
    VOS_UINT32                          ulSduSize;
}LLOOP_BACK_DRB_SETUP_STRU;

/*****************************************************************************
 结构名    : LLOOP_BACK_MODE_A_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 环回模式A时LB参数
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDrbNum;
    LLOOP_BACK_DRB_SETUP_STRU           astDrbSetup[LLOOP_BACK_MODE_MAX_LB_NUM];
}LLOOP_BACK_MODE_A_STRU;

/*****************************************************************************
 结构名    : LLOOP_BACK_MODE_B_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 环回模式B时LB参数
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDelayTime;
}LLOOP_BACK_MODE_B_STRU;

/*****************************************************************************
 结构名    : LTC_LPDCP_START_TEST_LOOP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 启动环回模式消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LTC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;           /*_H2ASN_Skip*/
    LTC_LPDCP_LOOPBACK_MODE_ENUM_UINT32  enLoopBackMode;
    union
    {
        LLOOP_BACK_MODE_A_STRU           stLBModeA;
        LLOOP_BACK_MODE_B_STRU           stLBModeB;
    }u;
}LTC_LPDCP_START_TEST_LOOP_STRU;

/*****************************************************************************
 结构名    : LTC_LPDCP_START_TEST_LOOP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 启动环回模式确认消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LTC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;           /*_H2ASN_Skip*/
    VOS_UINT32                          ulResult;
}LTC_LPDCP_START_TEST_LOOP_CNF_STRU;

/*****************************************************************************
 结构名    : LTC_LPDCP_STOP_TEST_LOOP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 停止环回模式消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LTC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;           /*_H2ASN_Skip*/
}LTC_LPDCP_STOP_TEST_LOOP_STRU;

/*****************************************************************************
 结构名    : LTC_LPDCP_STOP_TEST_LOOP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 停止环回模式确认消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LTC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;           /*_H2ASN_Skip*/
    VOS_UINT32                          ulResult;
}LTC_LPDCP_STOP_TEST_LOOP_CNF_STRU;

/*****************************************************************************
 结构名    : LTC_LPDCP_DEACTIVATE_TEST_MODE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 去激活环回模式消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LTC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;           /*_H2ASN_Skip*/
}LTC_LPDCP_DEACTIVATE_TEST_MODE_STRU;

/*****************************************************************************
 结构名    : LTC_LPDCP_DEACTIVATE_TEST_MODE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 去激活环回模式确认消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LTC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;           /*_H2ASN_Skip*/
    VOS_UINT32                          ulResult;
}LTC_LPDCP_DEACTIVATE_TEST_MODE_CNF_STRU;

typedef struct
{
    LTC_LPDCP_MSG_TYPE_ENUM_UINT32        enMsgId;            /*_H2ASN_MsgChoice_Export LTC_LPDCP_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          LTC_LPDCP_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}LTC_LPDCP_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    LTC_LPDCP_MSG_DATA                    stMsgData;
}LTcLPdcpInterface_MSG;

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

