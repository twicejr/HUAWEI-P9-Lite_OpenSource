/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsSndEsm.h
  版 本 号   : 初稿
  作    者   : w00316404
  生成日期   : 2015年12月7日
  最近修改   :
  功能描述   : TafApsSndEsm.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年12月7日
    作    者   : w00316404
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAFAPSSNDESM_H__
#define __TAFAPSSNDESM_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "Taf_Aps.h"
#include "TafApsComFunc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名: APS_ESM_PDP_STATE_ENUM_UINT32
 枚举说明: PDP状态
 1.日    期   : 2015年12月7日
   作    者   : w00316404
   修改内容   : Added for Split L4A Project
*****************************************************************************/
enum APS_ESM_PDP_STATE_ENUM
{
    APS_ESM_PDP_STATE_INACTIVE                  = 0x00,                         /* PDP没激活 */
    APS_ESM_PDP_STATE_ACTIVE                    = 0x01,                         /* PDP已激活 */

    APS_ESM_PDP_STATE_BUTT                      = 0xFF
};
typedef VOS_UINT32 APS_ESM_PDP_STATE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : APS_ESM_BEARER_ACT_RESULT_ENUM
 枚举说明  : 承载激活结果取值
 1.日    期   : 2015年12月7日
   作    者   : w00316404
   修改内容   : Added for Split L4A Project
*****************************************************************************/
enum APS_ESM_BEARER_ACT_RESULT_ENUM
{
    APS_ESM_BEARER_ACT_ACCEPT           = 0x00,
    APS_ESM_BEARER_ACT_REJ              = 0x01,
    APS_ESM_BEARER_ACT_BUTT
};
typedef VOS_UINT32 APS_ESM_BEARER_ACT_RESULT_ENUM_UINT32;
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
VOS_VOID TAF_APS_SndEsmSetCgactMsgDistr(
    VOS_UINT8                           ucPdpId,
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpCtxStateReq
);
VOS_VOID TAF_APS_SndEsmSetCgactPdpSetupReq(
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpCtxStateReq
);
VOS_VOID TAF_APS_SndEsmSetCgactPdpReleaseReq(
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpCtxStateReq
);
VOS_VOID TAF_APS_SndEsmPppDialSetupReq(
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq,
    TAF_APS_AUTH_INFO_STRU             *pstAuthInfo,
    TAF_APS_IPCP_INFO_STRU             *pstIpcpInfo
);
VOS_UINT32 TAF_APS_SndEsmNdisconnReq(
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq
);
VOS_VOID TAF_APS_SndEsmPdpModifyReq(
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq
);
VOS_VOID TAF_APS_SndEsmPdpReleaseReq(
    TAF_PS_CALL_END_REQ_STRU           *pstCalEndReq
);
VOS_VOID TAF_APS_SndEsmPdpManagerRsp(
    APS_ESM_BEARER_ACT_RESULT_ENUM_UINT32   ulSetupRslt,
    VOS_UINT8                               ucCid
);

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

#endif /* end of TafApsSndEsm.h */
