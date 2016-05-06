/************************************************************************
 *                                                                      *
 *                             Eap_typ.h                                *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        2010/07/05                                      *
 *  Author:             wangyong                                        *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:           PPP的eap协议模块私有数据结构                    *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 * Copyright 2000-2010 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.  *
 *                     ALL RIGHTS RESERVED                              *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *   这个文件定义了eap协议模块的全部私有数据结构                        *
 *                                                                      *
 ************************************************************************/

#if( VRP_MODULE_LINK_PPP == VRP_YES )

#ifndef      _PPPC_EAP_TYP_H_
#define      _PPPC_EAP_TYP_H_

#ifdef      __cplusplus
extern "C" {
#endif     /* end of __cplusplus */

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "pppc_eap_def.h"

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

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

/** ****************************************************************************
* Name        : PPPC_EAP_HEADER_STRU
*
* Description : EAP报文头的公共结构
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEAPCode;
    VOS_UINT8                           ucEAPID;
    VOS_UINT16                          usEAPLen;
    PPPC_EAP_METHODS_TYPE_ENUM_UINT8    enEAPType;
    VOS_UINT8                           aucResv[3];
}PPPC_EAP_HEADER_STRU;

/** ****************************************************************************
* Name        : PPPC_EAP_METHOD_OUTPUT_STRU
*
* Description : 方法的输出
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPppId;
    VOS_UINT16                         *pusRespLen;
    VOS_UINT8                          *pucPktData;
}PPPC_EAP_METHOD_OUTPUT_STRU;

/** ****************************************************************************
* Name        : PPPC_EAP_METHOD_INPUT_STRU
*
* Description : EAP方法的输入
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEAPID;
    PPPC_EAP_METHODS_TYPE_ENUM_UINT8    enEAPType;
    VOS_UINT16                          usEAPLen;                               /* 指示TYPE-DATA的长度 */
    VOS_UINT8                          *pucPktData;
}PPPC_EAP_METHOD_INPUT_STRU;

/** ****************************************************************************
* Name        : PPPC_EAP_EXPAND_NAK_TYPE_DATA_STRU
*
* Description : EXPAND NAK报文的type-data域结构
*******************************************************************************/
typedef struct
{
    PPPC_EAP_METHODS_TYPE_ENUM_UINT8    enEAPType;
    VOS_UINT8                           aucIETF[3];
    VOS_UINT32                          ulType;
}PPPC_EAP_EXPAND_NAK_TYPE_DATA_STRU;

/*****************************************************************************
 结构名    : PPPC_EAP_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : EAP 控制块数据结构定义
*****************************************************************************/
typedef struct
{
    PPPINFO_S                          *pstPppInfo;                             /* PPP控制块指针 */
    VOS_UINT16                          usEAPLastReqID;                         /* 上次发送的Response报文ID,用UINT16表示保证初始值不会与接收的重复 */
    PPPC_EAP_METHODS_TYPE_ENUM_UINT8    enRequestType;                          /* 收到的Request报文的Type */
    VOS_UINT8                           ucRequestID;                            /* 收到的Request报文的ID */
    PPPC_EAP_METHODS_TYPE_ENUM_UINT8    enSelectMethod;                         /* 选中的方法 */
    PPPC_EAP_METHODS_INTERNAL_TYPE_ENUM_UINT8 enInterType;                      /* 内部映射方法 */
    PPPC_EAP_PEER_STATE_MACHINE_ENUM_UINT16 enEapPeerState;                     /* Peer状态 */
    HTIMER                              hReqTimeoutID;                          /* 等待EAP Req超时定时器 */
    VOS_UINT32                          ulTimeOutTime;                          /* 超时时间 */
    VOS_UINT32                          ulLocalResult;                          /* 用于存储本端的鉴权结果 */
    VOS_UINT32                          ulRemoteResult;                         /* 用于存储网络的鉴权结果 */
    VOS_UINT16                          usRespPktLen;                           /* 填充Response报文的长度 */
    VOS_UINT8                           aucResv1[2];
    VOS_UINT8                           aucRespPkt[PPPC_EAP_MAX_RESPONSE_LEN];  /* Response报文Payload填充 */
} PPPC_EAP_INFO_STRU;

/*****************************************************************************
 结构名    : PPPC_EAP_METHOD_PROC_PKT_FUNC
 协议表格  :
 ASN.1描述 :
 结构说明  : EAP调用鉴权方法的回调函数处理报文
*****************************************************************************/
typedef VOS_VOID (*PPPC_EAP_METHOD_PROC_PKT_FUNC)
(
    PPPC_EAP_METHOD_OUTPUT_STRU        *pstEAPMethodOutput,
    PPPC_EAP_METHOD_INPUT_STRU         *pstEAPMethodInput
);

/*****************************************************************************
 结构名    : PPPC_EAP_METHOD_PRE_PROC_FUNC
 协议表格  :
 ASN.1描述 :
 结构说明  : EAP调用鉴权方法的回调函数返回预处理结果
*****************************************************************************/
typedef PS_BOOL_ENUM_UINT8 (*PPPC_EAP_METHOD_PRE_PROC_FUNC)
(
    PPPC_EAP_METHOD_INPUT_STRU         *pstEAPMethodInput
);

/*****************************************************************************
 结构名    : PPPC_EAP_METHOD_INIT_FUNC
 协议表格  :
 ASN.1描述 :
 结构说明  : EAP调用鉴权方法的回调函数初始化方法
*****************************************************************************/
typedef VOS_VOID (*PPPC_EAP_METHOD_INIT_FUNC)(PPPC_EAP_METHODS_TYPE_ENUM_UINT8);

/*****************************************************************************
 结构名    : PPPC_EAP_METHOD_RESULT_NOTIFY_FUNC
 协议表格  :
 ASN.1描述 :
 结构说明  : EAP调用鉴权方法的回调函数通知网络的鉴权结果
*****************************************************************************/
typedef VOS_VOID (*PPPC_EAP_METHOD_RESULT_NOTIFY_FUNC)(VOS_UINT32);

/*****************************************************************************
 结构名    : PPPC_EAP_METHOD_INIT_STATE_FUNC
 协议表格  :
 ASN.1描述 :
 结构说明  : 初始化方法的状态
*****************************************************************************/
typedef VOS_VOID (*PPPC_EAP_METHOD_INIT_STATE_FUNC)(VOS_VOID);

/*****************************************************************************
 结构名    : PPPC_EAP_PEER_EVENT_PROC_FUNC
 协议表格  :
 ASN.1描述 :
 结构说明  : PEER状态机的事件处理函数
*****************************************************************************/
typedef VOS_VOID (*PPPC_EAP_PEER_EVENT_PROC_FUNC)(PPPINFO_S *, VOS_VOID *);

/*****************************************************************************
 结构名    : PPPC_EAP_METHOD_CB_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 方法的处理回调函数
*****************************************************************************/
typedef struct
{
    PPPC_EAP_METHOD_INIT_FUNC           pfuncInitMethod;
    PPPC_EAP_METHOD_INIT_STATE_FUNC     pfuncInitMethodState;
    PPPC_EAP_METHOD_RESULT_NOTIFY_FUNC  pfuncNotifyMethodRes;
    PPPC_EAP_METHOD_PROC_PKT_FUNC       pfuncProcMethodPkt;
    PPPC_EAP_METHOD_PRE_PROC_FUNC       pfuncPreProc;
} PPPC_EAP_METHOD_CB_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/

#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _PPPC_EAP_TYP_H_ */

#endif  /* #if( VRP_MODULE_LINK_PPP == VRP_YES ) */

