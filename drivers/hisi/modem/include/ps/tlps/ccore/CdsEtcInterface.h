/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CdsEtcInterface.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2011年12月10日
  最近修改   :
  功能描述   : CDS与ETC之间的接口
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月10日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CDSETCINTERFACE_H__
#define __CDSETCINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "LPSCommon.h"



#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define  ETC_CDS_MSG_HDR               (PS_MSG_ID_ETC_TO_CDS_BASE)
#define  CDS_ETC_MSG_HDR               (PS_MSG_ID_CDS_TO_ETC_BASE)
/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 结构名    : CDS_TEST_MODE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : 还回模式状态类型
*****************************************************************************/
enum CDS_ETC_MSG_ID_ENUM
{
    /* ETC->CDS的消息原语 */
    ID_ETC_CDS_ACT_TEST_MODE_NOTIFY     = (0x01 + ETC_CDS_MSG_HDR),   /* _H2ASN_MsgChoice ETC_CDS_ACT_TEST_MODE_NOTIFY_STRU */
    ID_ETC_CDS_DEACT_TEST_MODE_NOTIFY   = (0x02 + ETC_CDS_MSG_HDR),   /* _H2ASN_MsgChoice ETC_CDS_DEACT_TEST_MODE_NOTIFY_STRU */
    ID_ETC_CDS_START_TEST_LOOP_NOTIFY   = (0x03 + ETC_CDS_MSG_HDR),   /* _H2ASN_MsgChoice ETC_CDS_START_TEST_LOOP_NOTIFY_STRU */
    ID_ETC_CDS_STOP_TEST_LOOP_NOTIFY    = (0x04 + ETC_CDS_MSG_HDR),   /* _H2ASN_MsgChoice ETC_CDS_STOP_TEST_LOOP_NOTIFY_STRU */
    ID_CDS_ETC_MSG_ID_ENUM_BUTT
};

typedef VOS_UINT32   CDS_ETC_MSG_ID_ENUM_UINT32;

/*****************************************************************************
 结构名    : CDS_TEST_MODE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : 还回模式状态类型
*****************************************************************************/
enum CDS_TEST_MODE_ENUM
{
    CDS_TEST_MODE_ACTIVATED              = 0,
    CDS_TEST_MODE_DEACTIVATED            = 1,
    CDS_TEST_MODE_BUTT
};
typedef VOS_UINT32 CDS_TEST_MODE_ENUM_UINT32;


/*****************************************************************************
 结构名    : CDS_ETC_LB_MODE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : 还回模式状态类型
*****************************************************************************/
enum CDS_ETC_LB_MODE_ENUM
{
    CDS_ETC_LB_MODE_A               = 0,
    CDS_ETC_LB_MODE_B               = 1,
    CDS_ETC_LB_MODE_BUTT
};

typedef VOS_UINT32 CDS_ETC_LB_MODE_ENUM_UINT32;


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

/*****************************************************************************
 结构名    : CDS_ETC_ACT_TEST_MODE_NOTIFY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDS与ETC之间的原语，ETC通过这条原语通知CDS开启环回模式
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CDS_ETC_MSG_ID_ENUM_UINT32         enMsgId;

     VOS_UINT8                          aucReserved[4];
} CDS_ETC_ACT_TEST_MODE_NOTIFY_STRU;

/*****************************************************************************
 结构名    : ETC_CDS_DEACT_TEST_MODE_NOTIFY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDS与ETC之间的原语，ETC通过这条原语通知CDS关闭环回模式
*****************************************************************************/
typedef struct
 {
     VOS_MSG_HEADER
     CDS_ETC_MSG_ID_ENUM_UINT32         enMsgId;

     VOS_UINT8                          aucReserved[4];
} ETC_CDS_DEACT_TEST_MODE_NOTIFY_STRU;

/*****************************************************************************
 结构名    : ETC_CDS_START_TEST_LOOP_NOTIFY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDS与ETC之间的原语，ETC通过这条原语通知CDS每一个用例的信息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CDS_ETC_MSG_ID_ENUM_UINT32         enMsgId;

    VOS_UINT32                         ulLBMode;
    VOS_UINT32                         ulLBModeBTmrLen;

} ETC_CDS_START_TEST_LOOP_NOTIFY_STRU;

/*****************************************************************************
 结构名    : ETC_CDS_STOP_TEST_LOOP_NOTIFY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDS与ETC之间的原语，ETC通过这条原语通知CDS关闭一个用例的测试
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CDS_ETC_MSG_ID_ENUM_UINT32         enMsgId;

    VOS_UINT8                          aucReserved[4];
} ETC_CDS_STOP_TEST_LOOP_NOTIFY_STRU;



/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
CDS_TEST_MODE_ENUM_UINT32 CDS_GetTestMode(VOS_VOID);




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

#endif /* end of CdsEtcInterface.h */
