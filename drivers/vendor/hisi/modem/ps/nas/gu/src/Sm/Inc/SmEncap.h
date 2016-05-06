/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : SmEncap.h
  Description : 封装函数
  History     :
      1.  张志勇      2003.12.04   新版作成
      2.  张志勇   2005.01.18   移植修改
*******************************************************************************/

#ifndef _SM_ENCAP_H_
#define _SM_ENCAP_H_


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"

#include "PsCommonDef.h"
#include "PsTypeDef.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
#pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define SM_NULL                         (0)

#define SM_TafFree(p)                   PS_SM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS,(p))
#define SM_RabmFree(p)                  PS_SM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS,(p))
#define SM_GmmFree(p)                   PS_SM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS,(p))
#define SM_Free(p)                      PS_SM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS,(p))
#define SM_Malloc(length)               PS_SM_MEM_ALLOC(VOS_MEMPOOL_INDEX_NAS,(length),WUEPS_MEM_WAIT)
#define SM_MemCpy(p1,p2,length)         PS_NAS_MEM_CPY((p1),(p2),(length))
#define SM_MemSet(p,value,length)       PS_NAS_MEM_SET((p),(value),(length))


/* 封装协议栈LOG接口 */
#define NAS_SM_INFO_LOG(String)                             PS_NAS_LOG(  WUEPS_PID_SM, SUBMOD_NULL, PS_LOG_LEVEL_INFO, (String) )
#define NAS_SM_INFO_LOG1(String,Para1)                      PS_NAS_LOG1( WUEPS_PID_SM, SUBMOD_NULL, PS_LOG_LEVEL_INFO, (String), (VOS_INT32)(Para1) )
#define NAS_SM_INFO_LOG2(String,Para1,Para2)                PS_NAS_LOG2( WUEPS_PID_SM, SUBMOD_NULL, PS_LOG_LEVEL_INFO, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define NAS_SM_INFO_LOG3(String,Para1,Para2,Para3)          PS_NAS_LOG3( WUEPS_PID_SM, SUBMOD_NULL, PS_LOG_LEVEL_INFO, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define NAS_SM_INFO_LOG4(String,Para1,Para2,Para3,Para4)    PS_NAS_LOG4( WUEPS_PID_SM, SUBMOD_NULL, PS_LOG_LEVEL_INFO, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define NAS_SM_NORM_LOG(String)                             PS_NAS_LOG(  WUEPS_PID_SM, SUBMOD_NULL, PS_LOG_LEVEL_NORMAL, (String) )
#define NAS_SM_NORM_LOG1(String,Para1)                      PS_NAS_LOG1( WUEPS_PID_SM, SUBMOD_NULL, PS_LOG_LEVEL_NORMAL, (String), (VOS_INT32)(Para1) )
#define NAS_SM_NORM_LOG2(String,Para1,Para2)                PS_NAS_LOG2( WUEPS_PID_SM, SUBMOD_NULL, PS_LOG_LEVEL_NORMAL, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define NAS_SM_NORM_LOG3(String,Para1,Para2,Para3)          PS_NAS_LOG3( WUEPS_PID_SM, SUBMOD_NULL, PS_LOG_LEVEL_NORMAL, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define NAS_SM_NORM_LOG4(String,Para1,Para2,Para3,Para4)    PS_NAS_LOG4( WUEPS_PID_SM, SUBMOD_NULL, PS_LOG_LEVEL_NORMAL, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define NAS_SM_WARN_LOG(String)                             PS_NAS_LOG(  WUEPS_PID_SM, SUBMOD_NULL, PS_LOG_LEVEL_WARNING, (String) )
#define NAS_SM_WARN_LOG1(String,Para1)                      PS_NAS_LOG1( WUEPS_PID_SM, SUBMOD_NULL, PS_LOG_LEVEL_WARNING, (String), (VOS_INT32)(Para1) )
#define NAS_SM_WARN_LOG2(String,Para1,Para2)                PS_NAS_LOG2( WUEPS_PID_SM, SUBMOD_NULL, PS_LOG_LEVEL_WARNING, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define NAS_SM_WARN_LOG3(String,Para1,Para2,Para3)          PS_NAS_LOG3( WUEPS_PID_SM, SUBMOD_NULL, PS_LOG_LEVEL_WARNING, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define NAS_SM_WARN_LOG4(String,Para1,Para2,Para3,Para4)    PS_NAS_LOG4( WUEPS_PID_SM, SUBMOD_NULL, PS_LOG_LEVEL_WARNING, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define NAS_SM_ERR_LOG(String)                              PS_NAS_LOG(  WUEPS_PID_SM, SUBMOD_NULL, PS_LOG_LEVEL_ERROR, (String) )
#define NAS_SM_ERR_LOG1(String,Para1)                       PS_NAS_LOG1( WUEPS_PID_SM, SUBMOD_NULL, PS_LOG_LEVEL_ERROR, (String), (VOS_INT32)(Para1) )
#define NAS_SM_ERR_LOG2(String,Para1,Para2)                 PS_NAS_LOG2( WUEPS_PID_SM, SUBMOD_NULL, PS_LOG_LEVEL_ERROR, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define NAS_SM_ERR_LOG3(String,Para1,Para2,Para3)           PS_NAS_LOG3( WUEPS_PID_SM, SUBMOD_NULL, PS_LOG_LEVEL_ERROR, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define NAS_SM_ERR_LOG4(String,Para1,Para2,Para3,Para4)     PS_NAS_LOG4( WUEPS_PID_SM, SUBMOD_NULL, PS_LOG_LEVEL_ERROR, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

/* 封装OSA申请消息接口 */
#define NAS_SM_ALLOC_MSG_WITH_HDR(ulMsgLen)\
            PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_SM, (ulMsgLen))

/* 封装OSA消息头 */
#define NAS_SM_CFG_MSG_HDR(pstMsg, ulRecvPid, ulMsgId)\
            ((MSG_HEADER_STRU *)(pstMsg))->ulSenderCpuId   = VOS_LOCAL_CPUID;\
            ((MSG_HEADER_STRU *)(pstMsg))->ulSenderPid     = WUEPS_PID_SM;\
            ((MSG_HEADER_STRU *)(pstMsg))->ulReceiverCpuId = VOS_LOCAL_CPUID;\
            ((MSG_HEADER_STRU *)(pstMsg))->ulReceiverPid   = (ulRecvPid);\
            ((MSG_HEADER_STRU *)(pstMsg))->ulMsgName       = (ulMsgId)

/* 封装OSA消息头(GMM) */
#define NAS_SM_CFG_GMM_MSG_HDR(pstMsg, ulMsgId)\
            NAS_SM_CFG_MSG_HDR(pstMsg, WUEPS_PID_GMM, ulMsgId)

/* 封装OSA消息头(RABM) */
#define NAS_SM_CFG_RABM_MSG_HDR(pstMsg, ulMsgId)\
            NAS_SM_CFG_MSG_HDR(pstMsg, WUEPS_PID_RABM, ulMsgId)

/* 封装OSA消息头(TAF) */
#define NAS_SM_CFG_TAF_MSG_HDR(pstMsg, ulMsgId)\
            NAS_SM_CFG_MSG_HDR(pstMsg, WUEPS_PID_TAF, ulMsgId)

/* 获取OSA消息内容 */
#define NAS_SM_GET_MSG_ENTITY(pstMsg)\
            ((VOS_VOID *)&(((MSG_HEADER_STRU *)(pstMsg))->ulMsgName))

/* 获取OSA消息长度 */
#define NAS_SM_GET_MSG_LENGTH(pstMsg)\
            (((MSG_HEADER_STRU *)(pstMsg))->ulLength)

/* 封装OSA发送消息接口 */
#define NAS_SM_SEND_MSG(pstMsg)\
            if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM, pstMsg))\
            {\
                NAS_SM_ERR_LOG("NAS_SM_SEND_MSG: Send message fail!\n");\
            }


/*****************************************************************************
  3 枚举定义
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

#endif /* _SM_ENCAP_H_ */
