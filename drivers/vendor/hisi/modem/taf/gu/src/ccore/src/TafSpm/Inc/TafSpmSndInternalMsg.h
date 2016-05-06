/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafSpmSndInternalMsg.h
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2013年5月9日
  最近修改   :
  功能描述   : 定义内部消息发送处理头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年5月9日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/
#ifndef _TAF_SPM_SND_INTERNAL_MSG_H_
#define _TAF_SPM_SND_INTERNAL_MSG_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "TafSpmCtx.h"
#include "TafSpmServiceDomainSelProc.h"
#include "TafInternalInterface.h"

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
枚举名    : TAF_SPM_SERVICE_CTRL_RESULT_ENUM
结构说明  : SERVICE CTRL状态机产生的结果
1.日    期   : 2013年5月9日
  作    者   : W00176964
  修改内容   : 新增
*****************************************************************************/
enum TAF_SPM_SERVICE_CTRL_RESULT_ENUM
{
    TAF_SPM_SERVICE_CTRL_SUCC                                   = 0,
    TAF_SPM_SERVICE_CTRL_FAIL                                   = 1,
    TAF_SPM_SERVICE_CTRL_BUTT
};
typedef VOS_UINT32 TAF_SPM_SERVICE_CTRL_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : TAF_SPM_INTERNAL_MSG_ID_ENUM
 结构说明  : 内部消息ID
 1.日    期   : 2013年5月9日
   作    者   : w00176964
   修改内容   : SPM内部消息ID枚举
*****************************************************************************/
enum TAF_SPM_INTERNAL_MSG_ID_ENUM
{
    TAF_SPM_INTERNAL_SERVICE_CTRL_RESULT_IND               = ID_TAF_MNTN_MSG_SPM_BASE +0x100, /*_H2ASN_MsgChoice TAF_SPM_SERVICE_CTRL_RSLT_STRU */

    TAF_SPM_INTERNAL_DOMAIN_SEL_IND,                                                          /*_H2ASN_MsgChoice TAF_SPM_DOMAIN_SEL_IND_STRU */

    TAF_SPM_INTERNAL_MSG_BUTT
};
typedef VOS_UINT32 TAF_SPM_INTERNAL_MSG_ID_ENUM_UINT32;


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
 结构名称: TAF_SPM_SERVICE_CTRL_RSLT_STRU
 结构说明:  TAF->TAF,SERVICE CTRL结果

  1.日    期   : 2013年5月9日
    作    者   : w00176964
    修改内容   : service ctrl状态机退出结果内部消息
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             MsgHeader;                              /* 消息头 */
    TAF_SPM_SERVICE_CTRL_RESULT_ENUM_UINT32     enResult;                               /* SERVICE CTRL结果 */
    VOS_UINT32                                  ulCause;                                /* 失败时携带的原因值 */
    VOS_UINT16                                  usClientId;                             /* 对应的client id */
    VOS_UINT8                                   aucRsv[2];
    TAF_SPM_ENTRY_MSG_STRU                      stEntryMsg;                             /* at或STK向SS发送的消息 */
} TAF_SPM_SERVICE_CTRL_RSLT_STRU;

/* 放到IMS宏开关外面公共使用 */
/* Added by y00245242 for VoLTE_PhaseII 项目, 2013-9-24, begin */
/*****************************************************************************
 结构名    : TAF_SPM_DOMAIN_SEL_IND_STRU
 结构说明  : 缓存消息域选择指示
 1.日    期   : 2013年9月22日
   作    者   : y00245242
   修改内容   : 新建，缓存消息队列
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             MsgHeader;
} TAF_SPM_DOMAIN_SEL_IND_STRU;
/* Added by y00245242 for VoLTE_PhaseII 项目, 2013-9-24, end */

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID TAF_SPM_SndServiceCtrlRsltInd(
        TAF_SPM_SERVICE_CTRL_RESULT_ENUM_UINT32                 enRslt,
        VOS_UINT32                                              ulCause,
        VOS_UINT16                                              usClientId,
        TAF_SPM_ENTRY_MSG_STRU                                 *pstEntryMsg
);

/* Added by y00245242 for VoLTE_PhaseII 项目, 2013-9-25, begin */
#if (FEATURE_IMS == FEATURE_ON)
VOS_VOID TAF_SPM_SendMsgSmmaRsp(
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType,
    struct MsgCB                       *pstMsg
);
#endif

/* 放到IMS宏开关外面公共使用 */
VOS_VOID TAF_SPM_SndInternalDomainSelectionInd(VOS_VOID);

/* Added by y00245242 for VoLTE_PhaseII 项目, 2013-9-25, end */

/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-26, begin */
#if (FEATURE_ON == FEATURE_ECALL)
VOS_VOID TAF_SPM_SndTafRelCallReq(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    TAF_CALL_REL_CALL_TYPE_ENUM_UINT8   enRelType
);
#endif
/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-26, end */

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


