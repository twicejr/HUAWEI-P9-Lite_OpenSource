/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasCcMnccSend.h
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2007年10月17日
  最近修改   : 2007年10月17日
  功能描述   : MNCC原语发送模块的接口
  函数列表   :
  修改历史   :
  1.日    期   : 2007年10月17日
    作    者   : 丁庆 49431
    修改内容   : 创建文件
******************************************************************************/
#ifndef  NAS_CC_MNCC_SEND_H
#define  NAS_CC_MNCC_SEND_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "NasMncc.h"
#include "NasCcCommon.h"

/*****************************************************************************
  2 函数声明
*****************************************************************************/
/*****************************************************************************
 函 数 名  : NAS_CC_SendMnccMsg
 功能描述  : 向上层发送MNCC原语消息
 输入参数  : entityId     - CC实体ID
             enPrimName   - 原语名称
             pParam       - 原语参数，参见MNCC_IND_PARAM_UNION
             ulParamLen   - 原语参数的长度
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月17日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_SendMnccMsg(
    NAS_CC_ENTITY_ID_T                  entityId,
    MNCC_PRIM_NAME_ENUM_U16             enPrimName,
    const VOS_VOID                      *pParam,
    VOS_UINT32                          ulParamLen
);

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-10, begin */
#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID  NAS_CC_SendMnccSrvccStatusIndMsg(
    NAS_MNCC_SRVCC_STATUS_ENUM_UINT32   enSrvccSta
);
#endif
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-10, end */

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

#endif /* NAS_CC_MNCC_SEND_H */


