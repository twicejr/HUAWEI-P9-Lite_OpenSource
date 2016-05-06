

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

/*****************************************************************************
结构名    : TAFAGENT_CTX_STRU
结构说明  : TAFAGENT的上下文
  1.日    期   : 2012年01月02日
    作    者   : C00173809
    修改内容   : 新增结构

  2.日    期   : 2012年7月17日
    作    者   : A00165503
    修改内容   : DTS2012071607302: TAF跨核同步API实现优化, 防止异常出现后,
                 所有API功能失效
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

/*****************************************************************************
 结构名    : TAF_AGENT_STATS_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TAFAGENT统计信息
  1.日    期   : 2012年7月3日
    作    者   : A00165503
    修改内容   : 新增结构

  2.日    期   : 2012年7月17日
    作    者   : A00165503
    修改内容   : DTS2012071607302: TAF跨核同步API实现优化, 防止异常出现后,
                 所有API功能失效
*****************************************************************************/
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
/*****************************************************************************
 函 数 名  : Taf_Agent_InitCtx
 功能描述  : 初始化Taf Agent全局变量
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : c00173809
    修改内容   : 新生成函数
*****************************************************************************/
extern VOS_UINT32 Taf_Agent_InitCtx(VOS_VOID);

/*****************************************************************************
 函 数 名  : TAF_AGENT_GetTafAcpuSyncSem
 功能描述  : 获取SYNC信号量
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_SEM
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : c00173809
    修改内容   : 新生成函数
*****************************************************************************/
extern VOS_SEM TAF_AGENT_GetTafAcpuSyncSem(VOS_VOID);

/*****************************************************************************
 函 数 名  : TAF_AGENT_GetTafAcpuCnfSem
 功能描述  : 获取Cnf信号量
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : c00173809
    修改内容   : 新生成函数
*****************************************************************************/
extern VOS_SEM TAF_AGENT_GetTafAcpuCnfSem(VOS_VOID);

/*****************************************************************************
 函 数 名  : TAF_AGENT_GetTafAcpuCnfMsg
 功能描述  : 获取消息地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : MsgBlock*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : c00173809
    修改内容   : 新生成函数
*****************************************************************************/
extern VOS_UINT8* TAF_AGENT_GetTafAcpuCnfMsg(VOS_VOID);

/*****************************************************************************
 函 数 名  : TAF_AGENT_SetTafAcpuCnfMsg
 功能描述  : 设置消息地址
 输入参数  : MsgBlock* pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : c00173809
    修改内容   : 新生成函数
*****************************************************************************/
extern VOS_VOID TAF_AGENT_SetTafAcpuCnfMsg(VOS_UINT8* pMsg);

/*****************************************************************************
 函 数 名  : TAF_AGENT_ClearMsg
 功能描述  : 清除消息缓冲
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : c00173809
    修改内容   : 新生成函数
*****************************************************************************/
extern VOS_VOID TAF_AGENT_ClearMsg(VOS_VOID);

/*****************************************************************************
 函 数 名  : TAF_AGENT_SaveMsg
 功能描述  : 保存消息缓冲
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : c00173809
    修改内容   : 新生成函数
*****************************************************************************/
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

