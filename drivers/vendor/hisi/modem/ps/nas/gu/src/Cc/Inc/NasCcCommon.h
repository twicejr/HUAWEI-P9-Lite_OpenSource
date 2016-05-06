/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasCcCommon.h
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2007年10月16日
  最近修改   : 2007年10月16日
  功能描述   : CC通用数据和接口定义
  函数列表   :
  修改历史   :
  1.日    期   : 2007年10月16日
    作    者   : 丁庆 49431
    修改内容   : 创建文件
******************************************************************************/
#ifndef  NAS_CC_COMMON_H
#define  NAS_CC_COMMON_H

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
#include "Ps.h"

#include "NasCommDef.h"

#if (FEATURE_ON == FEATURE_PTM)
#include "NasErrorLog.h"
#endif

/*****************************************************************************
  2 常量定义
*****************************************************************************/
/* 无效的实体ID */
#define  NAS_CC_INVALID_ENTITY_ID    ((VOS_UINT32)(-1))

/* CC空口消息的最大长度 */
#define  NAS_CC_MAX_AIR_MSG_LEN      251

/* CC无效原因值 */
#define NAS_CC_CAUSE_NULL               (0)

/* CC无效的InvokeId */
#define NAS_CC_INVALID_INVOKE_ID        (0xFF)

/*****************************************************************************
  3 类型定义
*****************************************************************************/
/* 实体ID类型 */
typedef VOS_UINT32  NAS_CC_ENTITY_ID_T;

/* 空口消息缓存类型 */
typedef struct
{
    VOS_UINT32                          ulLen;
    VOS_UINT8                           aucBuf[NAS_CC_MAX_AIR_MSG_LEN];
    VOS_UINT8                           aucReserve[1];
} NAS_CC_AIR_MSG_BUF_STRU;


/*****************************************************************************
  4 宏定义
*****************************************************************************/

/* CONST */
#ifdef  CONST
#undef  CONST
#endif

#define CONST const


/* 调试输出 */
#define NAS_CC_INFO_LOG(str)      PS_NAS_LOG(WUEPS_PID_CC, 0, PS_LOG_LEVEL_INFO, str)
#define NAS_CC_NORM_LOG(str)      PS_NAS_LOG(WUEPS_PID_CC, 0, PS_LOG_LEVEL_NORMAL, str)
#define NAS_CC_WARN_LOG(str)      PS_NAS_LOG(WUEPS_PID_CC, 0, PS_LOG_LEVEL_WARNING, str)
#define NAS_CC_ERR_LOG(str)       PS_NAS_LOG(WUEPS_PID_CC, 0, PS_LOG_LEVEL_ERROR, str)

#define NAS_CC_INFO_LOG1(str, x)  PS_NAS_LOG1(WUEPS_PID_CC, 0, PS_LOG_LEVEL_INFO, str, x)
#define NAS_CC_NORM_LOG1(str, x)  PS_NAS_LOG1(WUEPS_PID_CC, 0, PS_LOG_LEVEL_NORMAL, str, x)
#define NAS_CC_WARN_LOG1(str, x)  PS_NAS_LOG1(WUEPS_PID_CC, 0, PS_LOG_LEVEL_WARNING, str, x)
#define NAS_CC_ERR_LOG1(str, x)   PS_NAS_LOG1(WUEPS_PID_CC, 0, PS_LOG_LEVEL_ERROR, str, x)

#define NAS_CC_WARN_LOG2(str, x1, x2)  PS_NAS_LOG2(WUEPS_PID_CC, 0, PS_LOG_LEVEL_WARNING, str, x1, x2)

#define NAS_CC_INFO_LOG4(str, x1, x2, x3, x4)  PS_NAS_LOG4(WUEPS_PID_CC, 0, PS_LOG_LEVEL_INFO, str, x1, x2, x3, x4)

/* ASSERT */
#ifdef  _DEBUG
#define  NAS_CC_ASSERT(expr) \
        if(!(expr)) \
        { \
            NAS_CC_ERR_LOG("Assertion failed: " #expr); \
        }
#else
#define  NAS_CC_ASSERT(expr)   ((VOS_VOID)0)
#endif /* _DEBUG */



/*****************************************************************************
  5 全局变量声明
*****************************************************************************/
/* 主叫时缓存的Setup或Emergency Setup消息 */
extern NAS_CC_AIR_MSG_BUF_STRU          g_stNasCcBufferedSetupMsg;


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

VOS_VOID NAS_CC_ReadNvimInfo(VOS_VOID);


#if (FEATURE_ON == FEATURE_PTM)
VOS_VOID NAS_CC_SndAcpuOmFaultErrLogInd(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulDataLen,
    NAS_ERR_LOG_ALM_ID_ENUM_U16         usAlmId
);
VOS_UINT32 NAS_CC_IsErrLogNeedRecord(VOS_UINT16 usLevel);
VOS_VOID NAS_CC_CsMtCallFailRecord(
    NAS_ERR_LOG_CS_MT_CALL_CAUSE_ENUM_U32   enCause
);
#endif

VOS_VOID  NAS_CC_LogBufferQueueMsg(
    VOS_UINT32                          ulFullFlg
);

VOS_VOID  NAS_CC_ReadProceedingStartT310Nvim( VOS_VOID );



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* NAS_CC_COMMON_H */


