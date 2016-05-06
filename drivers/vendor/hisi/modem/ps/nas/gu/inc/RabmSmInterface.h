/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : RabmSmInterface.h
  Description : RABM与SM接口头文件
  History     :
      1.  张志勇      2003.12.04   新版作成
      2.日    期  : 2006年12月4日
        作    者  : luojian id:60022475
        修改内容  : 增加 #pragma pack(4)，问题单号:A32D07779
*******************************************************************************/

#ifndef _RABM_SM_INTERFACE_H_
#define _RABM_SM_INTERFACE_H_


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define RABMSM_ACT_MSG_1                (1)                 /* 指示SM发给RABM的是第一条激活消息 */
#define RABMSM_ACT_MSG_2                (2)                 /* 指示SM发给RABM的是第二条激活消息 */

#define RABM_SM_PPP_PROT                (0)                 /* 采用PPP协议 */
#define RABM_SM_IP_PROT                 (1)                 /* 采用IP协议  */

#define RABM_SM_MAX_NSAPI_NUM           (11)                /* 去激活的NSAPI的最多数量 */

#define RABM_SM_MAX_QOS_LEN             (16)                /* QOS字节流最大长度 */


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
enum RABM_SM_MSG_ID_ENUM
{
    /*------------------------------------------------------
                        SM<--->RABM
    *-----------------------------------------------------*/
    RABMSM_ACTIVATE_IND                 = 0x0000,           /* _H2ASN_MsgChoice RABMSM_ACTIVATE_IND_STRU */
    RABMSM_ACTIVATE_RSP                 = 0x0001,           /* _H2ASN_MsgChoice RABMSM_ACTIVATE_RSP_STRU */
    RABMSM_DEACTIVATE_IND               = 0x0002,           /* _H2ASN_MsgChoice RABMSM_DEACTIVATE_IND_STRU */
    RABMSM_DEACTIVATE_REQ               = 0x0003,           /* _H2ASN_MsgChoice RABMSM_DEACTIVATE_REQ_STRU */
    RABMSM_MODIFY_IND                   = 0x0004,           /* _H2ASN_MsgChoice RABMSM_MODIFY_IND_STRU */

#if (FEATURE_ON == FEATURE_LTE)
    /* 多模互操作新增原语 */
    ID_SM_RABM_BEARER_ACTIVATE_IND      = 0x0100,           /* _H2ASN_MsgChoice SM_RABM_BEARER_ACTIVATE_IND_STRU */
    ID_SM_RABM_BEARER_DEACTIVATE_IND    = 0x0101,           /* _H2ASN_MsgChoice SM_RABM_BEARER_DEACTIVATE_IND_STRU */
    ID_SM_RABM_BEARER_MODIFY_IND        = 0x0102,           /* _H2ASN_MsgChoice SM_RABM_BEARER_MODIFY_IND_STRU */
#endif

    ID_RABM_SM_MSG_BUTT
};
typedef VOS_UINT32 RABM_SM_MSG_ID_ENUM_UINT32;


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
 结构名   : RABMSM_QOS_STRU
 结构说明 : QOS结构

 修改历史      :
  1.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : 修改成员
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulLength;
    VOS_UINT8                           aucQosValue[RABM_SM_MAX_QOS_LEN];
} RABMSM_QOS_STRU;


/*****************************************************************************
 结构名    : RABMSM_ACTIVATE_IND_STRU
 结构说明  : 原语RABMSM_ACTIVATE_IND的结构体

 修改历史      :
  1.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : 增加Linked NSAPI
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头                       */ /* _H2ASN_Skip */
    VOS_UINT32                          ulNsapi;            /* 指定的NSAPI                  */
    VOS_UINT32                          ulLinkdNsapi;       /* 关联的NSAPI                  */
    VOS_UINT32                          ulPppFlag;          /* 是否采用PPP协议标志          */
    VOS_UINT32                          ulActMsgType;       /* 激活流程中SM发给RABM的第一条还是第二条激活消息*/
    RABMSM_QOS_STRU                     Qos;                /* 同指定的NSAPI相关的QOS       */
} RABMSM_ACTIVATE_IND_STRU;


/*****************************************************************************
 结构名    : RABMSM_ACTIVATE_RSP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 原语RABMSM_ACTIVATE_RSP的结构体
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头      */   /* _H2ASN_Skip */
    VOS_UINT32                          ulNsapi;            /* 激活的NSAPI */
} RABMSM_ACTIVATE_RSP_STRU;


/*****************************************************************************
 结构名    : RABMSM_DEACTIVATE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 原语RABMSM_DEACTIVATE_IND的结构体
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头             */ /* _H2ASN_Skip */
    VOS_UINT32                          ulDeactiveNum;      /*去激活的NSAPI的个数 */
    VOS_UINT32                          aulNsapiList[RABM_SM_MAX_NSAPI_NUM];    /* 去激活的NSAPI列表 */
} RABMSM_DEACTIVATE_IND_STRU;


/*****************************************************************************
 结构名    : RABMSM_MODIFY_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 原语RABMSM_MODIFY_IND的结构体
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头               */ /* _H2ASN_Skip */
    VOS_UINT32                          ulNsapi;            /* 指定的NSAPI          */
    RABMSM_QOS_STRU                     Qos;                /* 指定的NSAPI相关的QOS */
} RABMSM_MODIFY_IND_STRU;


/*****************************************************************************
 结构名    : RABMSM_DEACTIVATE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 原语RABMSM_DEACTIVATE_REQ的结构体
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* 消息头           */ /* _H2ASN_Skip */
    VOS_UINT32                          ulNsapi;            /* 已释放RAB的NSAPI */
} RABMSM_DEACTIVATE_REQ_STRU;


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 结构名    : SM_RABM_BEARER_ACTIVATE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 原语ID_SM_RABM_BEARER_ACTIVATE_IND的结构体
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* 消息头                       */ /* _H2ASN_Skip */
    VOS_UINT32                          ulNsapi;            /* 指定的NSAPI                  */
    VOS_UINT32                          ulLinkdNsapi;       /* 关联的NSAPI                  */
    RABMSM_QOS_STRU                     stQos;              /* 同指定的NSAPI相关的QOS       */
} SM_RABM_BEARER_ACTIVATE_IND_STRU;


/*****************************************************************************
 结构名    : SM_RABM_BEARER_DEACTIVATE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 原语ID_SM_RABM_BEARER_DEACTIVATE_IND的结构体
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* 消息头      */   /* _H2ASN_Skip */
    VOS_UINT32                          ulNsapi;            /* 指定的NSAPI */
} SM_RABM_BEARER_DEACTIVATE_IND_STRU;


/*****************************************************************************
 结构名    : SM_RABM_BEARER_MODIFY_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 原语ID_SM_RABM_BEARER_MODIFY_IND的结构体
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* 消息头                 */ /* _H2ASN_Skip */
    VOS_UINT32                          ulNsapi;            /* 指定的NSAPI            */
    RABMSM_QOS_STRU                     stQos;              /* 同指定的NSAPI相关的QOS */
} SM_RABM_BEARER_MODIFY_IND_STRU;
#endif


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
    RABM_SM_MSG_ID_ENUM_UINT32          enMsgId;            /* _H2ASN_MsgChoice_Export RABM_SM_MSG_ID_ENUM_UINT32 */
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          RABM_SM_MSG_ID_ENUM_UINT32
    ****************************************************************************/
} RABM_SM_INTERFACE_MSG_DATA;
/* _H2ASN_Length UINT32 */

typedef struct
{
    VOS_MSG_HEADER
    RABM_SM_INTERFACE_MSG_DATA          stMsgData;
} RabmSmInterface_MSG;


/*****************************************************************************
  10 函数声明
*****************************************************************************/

extern VOS_UINT32 SM_IsActivePending(VOS_UINT8 ucNsapi);
extern VOS_UINT32 SM_RabmGetFirstActIndMsgInfo(
    VOS_UINT8                           ucNsapi,
    RABMSM_ACTIVATE_IND_STRU           *pActivateInd
);
extern VOS_UINT32 NAS_SM_CheckPdpActiveState(VOS_VOID);

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

#endif
