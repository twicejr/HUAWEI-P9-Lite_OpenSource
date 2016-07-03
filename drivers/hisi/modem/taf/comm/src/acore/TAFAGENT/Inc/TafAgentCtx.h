

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#ifndef _TAFAGENT_CTX_H_
#define _TAFAGENT_CTX_H_


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
#define TAFAGENT_APS_MAX_MSG_LEN       (512)

#define TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(locked)         (g_stTafAgentCtx.ulAcpuCnfSemLockedFlg = (locked))
#define TAF_AGENT_GET_ACPU_CNF_SEM_LOCK_FLG()               (g_stTafAgentCtx.ulAcpuCnfSemLockedFlg)

#define TAF_AGENT_DBG_SAVE_MUTEX_SEM_ID(sem_id)             (g_stTafAgentStats.ulMutexSemId = (sem_id))
#define TAF_AGENT_DBG_SAVE_BINARY_SEM_ID(sem_id)            (g_stTafAgentStats.ulBinarySemId = (sem_id))
#define TAF_AGENT_DBG_CREATE_MUTEX_SEM_FAIL_NUM(n)          (g_stTafAgentStats.ulCreateMutexSemFailNum += (n))
#define TAF_AGENT_DBG_CREATE_BINARY_SEM_FAIL_NUM(n)         (g_stTafAgentStats.ulCreateBinarySemFailNum += (n))
#define TAF_AGENT_DBG_LOCK_MUTEX_SEM_FAIL_NUM(n)            (g_stTafAgentStats.ulLockMutexSemFailNum += (n))
#define TAF_AGENT_DBG_LOCK_BINARY_SEM_FAIL_NUM(n)           (g_stTafAgentStats.ulLockBinarySemFailNum += (n))
#define TAF_AGENT_DBG_SAVE_LAST_MUTEX_SEM_ERR_RSLT(rslt)    (g_stTafAgentStats.ulLastMutexSemErrRslt = (rslt))
#define TAF_AGENT_DBG_SAVE_LAST_BIN_SEM_ERR_RSLT(rslt)      (g_stTafAgentStats.ulLastBinarySemErrRslt = (rslt))
#define TAF_AGENT_DBG_SYNC_MSG_IS_NULL_NUM(n)               (g_stTafAgentStats.ulSyncMsgIsNullNum += (n))
#define TAF_AGENT_DBG_SYNC_MSG_NOT_MATCH_NUM(n)             (g_stTafAgentStats.ulSyncMsgNotMatchNum += (n))


/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  2 全局变量定义
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


typedef struct
{
    /* 互斥信号量，用来同步PS域同步API的互斥操作,初始值为非锁状态(0xFFFFFFFF) */
    VOS_SEM                             hTafAcpuSyncSem;

    /* 二进制信号量，用来等待返回结果， */
    VOS_SEM                             hTafAcpuCnfSem;

    /* 初始化标识, VOS_TRUE: 成功; VOS_FALSE: 失败 */
    VOS_UINT32                          ulInitFlg;

    /* 二进制信号量状态 */
    VOS_UINT32                          ulAcpuCnfSemLockedFlg;

    /* 保存PS域同步API回复消息的指针 */
    VOS_UINT8                          *pucTafAcpuCnfMsg;

    VOS_UINT8                           aucMsg[TAFAGENT_APS_MAX_MSG_LEN];
}TAFAGENT_CTX_STRU;


typedef struct
{
    VOS_SEM                             ulMutexSemId;               /* 互斥信号量ID */
    VOS_SEM                             ulBinarySemId;              /* 二进制信号量ID */
    VOS_UINT32                          ulCreateMutexSemFailNum;    /* 创建互斥信号量失败次数 */
    VOS_UINT32                          ulCreateBinarySemFailNum;   /* 创建二进制信号量失败次数 */
    VOS_UINT32                          ulLockMutexSemFailNum;      /* 锁互斥信号量失败次数 */
    VOS_UINT32                          ulLockBinarySemFailNum;     /* 锁二进制信号量失败次数 */
    VOS_UINT32                          ulLastMutexSemErrRslt;      /* 最后一次锁互斥信号量失败结果 */
    VOS_UINT32                          ulLastBinarySemErrRslt;     /* 最后一次锁二进制信号量失败结果 */
    VOS_UINT32                          ulSyncMsgIsNullNum;         /* 同步消息为空次数 */
    VOS_UINT32                          ulSyncMsgNotMatchNum;       /* 同步消息不匹配次数 */

} TAF_AGENT_STATS_INFO_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

extern TAF_AGENT_STATS_INFO_STRU        g_stTafAgentStats;

extern TAFAGENT_CTX_STRU                g_stTafAgentCtx;


/*****************************************************************************
  10 函数声明
*****************************************************************************/

extern VOS_UINT32 Taf_Agent_InitCtx(VOS_VOID);


extern VOS_SEM TAF_AGENT_GetTafAcpuSyncSem(VOS_VOID);


extern VOS_SEM TAF_AGENT_GetTafAcpuCnfSem(VOS_VOID);


extern VOS_UINT8* TAF_AGENT_GetTafAcpuCnfMsg(VOS_VOID);


extern VOS_VOID TAF_AGENT_SetTafAcpuCnfMsg(VOS_UINT8* pMsg);


extern VOS_VOID TAF_AGENT_ClearMsg(VOS_VOID);


extern VOS_UINT8* TAF_AGENT_SaveMsg(
    VOS_UINT8                          *pucMsg,
    VOS_UINT32                          ulLen
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

#endif

