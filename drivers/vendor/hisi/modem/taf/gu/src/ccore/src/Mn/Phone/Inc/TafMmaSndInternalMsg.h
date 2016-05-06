/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMmaSndInternalMsg.h
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2013年7月9日
  最近修改   :
  功能描述   : 定义内部消息发送处理头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年7月9日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/
#ifndef _TAF_MMA_SND_INTERNAL_MSG_H_
#define _TAF_MMA_SND_INTERNAL_MSG_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "TafMmaCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define TAF_MMA_INVALID_INTERNAL_MSG_ID                 (0xFFFF)                /* 消息ID的无效值 */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : TAF_MMA_INTERNAL_MSG_ID_ENUM
 结构说明  : 内部消息ID
 1.日    期   : 2013年7月9日
   作    者   : w00176964
   修改内容   : MMA内部消息ID枚举
*****************************************************************************/
enum TAF_MMA_INTERNAL_MSG_ID_ENUM
{
    MMA_MMA_INTER_POWER_INIT                = 0x4000,                       /*_H2ASN_MsgChoice TAF_MMA_INTER_POWER_INIT_REQ_STRU */

    MMA_MMA_INTER_USIM_STATUS_CHANGE_IND,                                   /*_H2ASN_MsgChoice TAF_MMA_INTER_USIM_STATUS_CHANGE_IND_STRU */

    MMA_MMA_PHONE_MODE_RSLT_IND,                                            /*_H2ASN_MsgChoice TAF_MMA_PHONE_MODE_RSLT_IND_STRU */

    MMA_MMA_SIM_LOCK_STATUS_CHANGE_IND,                                     /*_H2ASN_MsgChoice TAF_MMA_SIM_LOCK_STATUS_CHANGE_IND_STRU */

    MMA_MMA_IMS_SWITCH_RSLT_IND,                                            /*_H2ASN_MsgChoice TAF_MMA_IMS_SWITCH_RSLT_IND_STRU */

    MMA_MMA_INTER_SYS_CFG_SET_REQ,                                          /*_H2ASN_MsgChoice TAF_MMA_INTER_SYS_CFG_SET_REQ_STRU */

    MMA_MMA_INTER_ABORT_IND,                                                /*_H2ASN_MsgChoice TAF_MMA_INTER_ABORT_IND_STRU */

    MMA_MMA_SYS_CFG_RSLT_IND,                                               /*_H2ASN_MsgChoice TAF_MMA_SYS_CFG_RSLT_STRU */

    MMA_MMA_INTER_MSG_BUTT
};
typedef VOS_UINT32 TAF_MMA_INTERNAL_MSG_ID_ENUM_UINT32;


/*****************************************************************************
 枚举名    : TAF_MMA_PHONE_MODE_RESULT_ENUM
 结构说明  : PHONE MODE状态机退出结果枚举
 1.日    期   : 2013年7月19日
   作    者   : w00176964
   修改内容   : 新建
*****************************************************************************/
enum TAF_MMA_PHONE_MODE_RESULT_ENUM
{
    TAF_MMA_PHONE_MODE_RESULT_SWITCH_ON_SUCC,

    TAF_MMA_PHONE_MODE_RESULT_SWITCH_ON_FAIL,

    TAF_MMA_PHONE_MODE_RESULT_POWER_OFF_SUCC,

    TAF_MMA_PHONE_MODE_RESULT_POWER_OFF_FAIL,

    TAF_MMA_PHONE_MODE_RESULT_BUTT,

};
typedef VOS_UINT8 TAF_MMA_PHONE_MODE_RESULT_ENUM_UINT8;

enum TAF_MMA_IMS_SWITCH_RESULT_ENUM
{
    TAF_MMA_IMS_SWITCH_RESULT_ON_SUCC,

    TAF_MMA_IMS_SWITCH_RESULT_ON_FAIL,

    TAF_MMA_IMS_SWITCH_RESULT_OFF_SUCC,

    TAF_MMA_IMS_SWITCH_RESULT_OFF_FAIL,

    TAF_MMA_IMS_SWITCH_RESULT_BUTT
};
typedef VOS_UINT8 TAF_MMA_IMS_SWITCH_RESULT_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_MMA_SYS_CFG_RSLT_ENUM
 结构说明  : SYS CFG状态机退出结果枚举
 1.日    期   : 2015年5月5日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
enum TAF_MMA_SYS_CFG_RSLT_ENUM
{
    TAF_MMA_SYS_CFG_RSLT_SYS_CFG_SUCC,        /* SYS CFG请求命令成功 */

    TAF_MMA_SYS_CFG_RSLT_SYS_CFG_FAIL,        /* SYS CFG请求命令失败 */

    TAF_MMA_SYS_CFG_RSLT_ATTACH_SUCCESS,      /* ATTACH请求命令操作成功 */

    TAF_MMA_SYS_CFG_RSLT_ATTACH_FAIL,         /* ATTACH请求命令操作失败 */

    TAF_MMA_SYS_CFG_RSLT_DETACH_SUCCESS,      /* DETACH请求命令操作成功 */

    TAF_MMA_SYS_CFG_RSLT_DETACH_FAIL,         /* DETACH请求命令操作失败 */

    TAF_MMA_SYS_CFG_RSLT_BUTT,
};
typedef VOS_UINT8 TAF_MMA_SYS_CFG_RSLT_ENUM_UINT8;

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
 结构名称: TAF_MMA_INTER_POWER_INIT_REQ_STRU
 结构说明: MMA->MMA,内部上电请求消息的结构
 1.日    期   : 2013年7月19日
   作    者   : w00176964
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    TAF_MMA_INTERNAL_MSG_ID_ENUM_UINT32 enMsgId;            /* _H2ASN_Skip */
}TAF_MMA_INTER_POWER_INIT_REQ_STRU;


/*****************************************************************************
 结构名称: TAF_MMA_INTER_USIM_STATUS_CHANGE_IND_STRU
 结构说明: MMA->MMA,内部卡状态改变指示
 1.日    期   : 2013年7月19日
   作    者   : w00176964
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    TAF_MMA_INTERNAL_MSG_ID_ENUM_UINT32 enMsgId;            /* _H2ASN_Skip */
}TAF_MMA_INTER_USIM_STATUS_CHANGE_IND_STRU;

/*****************************************************************************
 结构名称: TAF_MMA_SIM_LOCK_STATUS_CHANGE_IND_STRU
 结构说明: MMA->MMA,锁网锁卡卡状态改变指示
 1.日    期   : 2013年10月15日
   作    者   : w00176964
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    TAF_MMA_INTERNAL_MSG_ID_ENUM_UINT32 enMsgId;            /* _H2ASN_Skip */
}TAF_MMA_SIM_LOCK_STATUS_CHANGE_IND_STRU;

/*****************************************************************************
 结构名称: TAF_MMA_PHONE_MODE_RSLT_IND_STRU
 结构说明: MMA->MMA,内部PHONE MODE结果消息指示
 1.日    期   : 2013年7月19日
   作    者   : w00176964
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAF_MMA_INTERNAL_MSG_ID_ENUM_UINT32                     enMsgId;            /* _H2ASN_Skip */
    TAF_MMA_PHONE_MODE_RESULT_ENUM_UINT8                    enRslt;
    VOS_UINT8                                               aucRsv[3];
}TAF_MMA_PHONE_MODE_RSLT_IND_STRU;

/*****************************************************************************
 结构名称: TAF_MMA_IMS_SWITCH_RSLT_IND_STRU
 结构说明: MMA->MMA,内部IMS_SWITCH结果消息指示
 1.日    期   : 2015-02-04
   作    者   : n00269697
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAF_MMA_INTERNAL_MSG_ID_ENUM_UINT32                     enMsgId;            /* _H2ASN_Skip */
    TAF_MMA_IMS_SWITCH_RESULT_ENUM_UINT8                    enRslt;
    VOS_UINT8                                               aucRsv[3];
}TAF_MMA_IMS_SWITCH_RSLT_IND_STRU;

/*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAF_MMA_INTERNAL_MSG_ID_ENUM_UINT32                     enMsgId;            /* _H2ASN_Skip */
    TAF_MMA_SYS_CFG_PARA_STRU                               stSysCfgPara;
}TAF_MMA_INTER_SYS_CFG_SET_REQ_STRU;


/*****************************************************************************
 结构名称: TAF_MMA_INTER_ABORT_IND_STRU
 结构说明: MMA->MMA, 终止当前状态机指示
 1.日    期   : 2015年4月9日
   作    者   : y00245242
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAF_MMA_INTERNAL_MSG_ID_ENUM_UINT32                     enMsgId;            /* _H2ASN_Skip */
    VOS_UINT8                                               aucReserved[4];
}TAF_MMA_INTER_ABORT_IND_STRU;

/*****************************************************************************
 结构名称: TAF_MMA_SYS_CFG_RSLT_STRU
 结构说明: MMA->MMA,内部SYS CFG RSLT结果消息指示
 1.日    期   : 2015年5月5日
   作    者   : y00245242
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAF_MMA_INTERNAL_MSG_ID_ENUM_UINT32                     enMsgId;            /* _H2ASN_Skip */
    TAF_MMA_SYS_CFG_RSLT_ENUM_UINT8                         enRslt;
    VOS_UINT8                                               ucIsNeedChkLock;
    VOS_UINT8                                               aucRsv[2];
}TAF_MMA_SYS_CFG_RSLT_STRU;


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
    TAF_MMA_INTERNAL_MSG_ID_ENUM_UINT32 enMsgId;

    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAF_MMA_INTERNAL_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}TAF_MMA_SND_INTERNAL_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_SND_INTERNAL_MSG_DATA       stMsgData;
}TafMmaSndInternalMsg_MSG;


/*****************************************************************************
  10 函数声明
*****************************************************************************/
TAF_MMA_INTERNAL_MSG_BUF_STRU* TAF_MMA_GetNextInternalMsg( VOS_VOID );

TAF_MMA_INTERNAL_MSG_BUF_STRU *TAF_MMA_GetIntMsgSendBuf(
    VOS_UINT32                          ulLen
);

VOS_VOID  TAF_MMA_SndInternalMsg(
    VOS_VOID                           *pSndMsg
);


VOS_VOID TAF_MMA_SndPhoneModeRsltInd(
    TAF_MMA_PHONE_MODE_RESULT_ENUM_UINT8                    enRslt
);

VOS_VOID TAF_MMA_SndSysCfgRsltInd(
    TAF_MMA_SYS_CFG_RSLT_ENUM_UINT8                         enRslt,
    VOS_UINT8                                               ucIsNeedChkLock
);

VOS_VOID TAF_MMA_SndInterUsimChangeInd(VOS_VOID);

VOS_VOID TAF_MMA_SndInterPowerInitReq(VOS_VOID);

VOS_VOID TAF_MMA_SndSimlocakStatusChangeInd(VOS_VOID);

#if (FEATURE_IMS == FEATURE_ON)
VOS_VOID TAF_MMA_SndImsSwitchRsltInd(
    TAF_MMA_IMS_SWITCH_RESULT_ENUM_UINT8                    enRslt
);
#endif

VOS_VOID TAF_MMA_SndInterSysCfgSetReq(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfg
);

VOS_VOID TAF_MMA_SndInterMmaAbortInd(VOS_VOID);

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

#endif



