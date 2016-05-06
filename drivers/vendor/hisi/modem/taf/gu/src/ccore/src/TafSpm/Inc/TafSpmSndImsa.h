/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafSpmSndImsa.h
  版 本 号   : 初稿
  作    者   : s00217060
  生成日期   : 2013年7月16日
  最近修改   :
  功能描述   : 定义SPM发送给IMSA消息的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年7月16日
    作    者   : s00217060
    修改内容   : 创建文件

******************************************************************************/
#ifndef _TAF_SPM_SND_IMSA_H_
#define _TAF_SPM_SND_IMSA_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "TafSpmCtx.h"
#if (FEATURE_IMS == FEATURE_ON)
#include "SpmImsaInterface.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

#if (FEATURE_IMS == FEATURE_ON)
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



/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID TAF_SPM_SendImsaCallOrigReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);
VOS_VOID TAF_SPM_SendImsaSupsCmdReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);
VOS_VOID TAF_SPM_SendImsaGetCallInfoReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg,
    CALL_IMSA_GET_CALL_INFO_REQ_TYPE_ENMU_UINT8 enReqType
);

VOS_VOID TAF_SPM_SendImsaGetClprReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);

VOS_VOID TAF_SPM_SendImsaStartDtmfReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);
VOS_VOID TAF_SPM_SendImsaStopDtmfReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);
VOS_VOID TAF_SPM_SendImsaGetCdurReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);
/*****************************************************************************
 函 数 名  : TAF_SPM_SendImsaRegisterSsReq
 功能描述  : 发送REGISTER消息给IMSA
 输入参数  : pstAppMsg 消息地址
 输出参数  : 无
 返 回 值  : VOS_TRUE 消息处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月11日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_SendImsaRegisterSsReq(
    struct MsgCB                       *pstMsg
);
/*****************************************************************************
 函 数 名  : TAF_SPM_SendImsaEraseSsReq
 功能描述  : 发送ERASE消息给IMSA
 输入参数  : pstAppMsg 消息地址
 输出参数  : 无
 返 回 值  : VOS_TRUE 消息处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月11日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_SendImsaEraseSsReq(
    struct MsgCB                       *pstMsg
);
/*****************************************************************************
 函 数 名  : TAF_SPM_SendImsaActivateSsReq
 功能描述  : 发送ACTIVATE请求消息给IMSA
 输入参数  : pstAppMsg 消息地址
 输出参数  : 无
 返 回 值  : VOS_TRUE 消息处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月11日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_SendImsaActivateSsReq(
    struct MsgCB                       *pstMsg
);
/*****************************************************************************
 函 数 名  : TAF_SPM_SendImsaDeactivateSsReq
 功能描述  : 发送DEACTIVATE请求消息给IMSA
 输入参数  : pstAppMsg 消息地址
 输出参数  : 无
 返 回 值  : VOS_TRUE 消息处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月11日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_SendImsaDeactivateSsReq(
    struct MsgCB                       *pstMsg
);
/*****************************************************************************
 函 数 名  : TAF_SPM_SendImsaInterrogateSsReq
 功能描述  : 发送Interrogate请求消息给IMSA
 输入参数  : pstAppMsg 消息地址
 输出参数  : 无
 返 回 值  : VOS_TRUE 消息处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月11日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_SendImsaInterrogateSsReq(
    struct MsgCB                       *pstMsg
);
/*****************************************************************************
 函 数 名  : TAF_SPM_SendImsaProcessUssSsReq
 功能描述  : 发送USSD DATA消息给IMSA
 输入参数  : pstAppMsg 消息地址
 输出参数  : 无
 返 回 值  : VOS_TRUE 消息处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月11日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_SendImsaProcessUssSsReq(
    struct MsgCB                       *pstMsg
);
/*****************************************************************************
 函 数 名  : TAF_SPM_SendImsaReleaseSsReq
 功能描述  : 发送release请求消息给IMSA
 输入参数  : pstAppMsg 消息地址
 输出参数  : 无
 返 回 值  : VOS_TRUE 消息处理成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月11日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_SendImsaReleaseSsReq(
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_SPM_SendImsaCallInviteNewPtptReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);

VOS_VOID TAF_SPM_SendImsaCallModifyReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);

VOS_VOID TAF_SPM_SendImsaCallAnswerRemoteModifyReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);

VOS_VOID TAF_SPM_SendImsaEconfAddUsersReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);
VOS_VOID TAF_SPM_SendImsaEconfDialReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);

VOS_VOID TAF_SPM_SendImsaGetEconfInfoReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
);

VOS_VOID TAF_SPM_FillImsaEconfCallList(
    TAF_CALL_ECONF_CALL_LIST_STRU      *pstCallList
);


#endif

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


