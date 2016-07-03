

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "TafAgentCtx.h"
#include  "TafAgentLog.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/

    /*lint -e767 */
#define    THIS_FILE_ID                 PS_FILE_ID_TAF_AGENT_CTX_C
    /*lint -e767 */

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

TAFAGENT_CTX_STRU                       g_stTafAgentCtx = {0};
TAF_AGENT_STATS_INFO_STRU               g_stTafAgentStats = {0};

/*****************************************************************************
  3 函数实现
*****************************************************************************/


VOS_UINT32 Taf_Agent_InitCtx(VOS_VOID)
{
    g_stTafAgentCtx.pucTafAcpuCnfMsg = VOS_NULL_PTR;

    /* 分配互斥信号量 */
    if (VOS_OK != VOS_SmMCreate("SYNC", VOS_SEMA4_FIFO, &g_stTafAgentCtx.hTafAcpuSyncSem))
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "Create aps acpu sycn sem failed!");
        TAF_AGENT_DBG_CREATE_MUTEX_SEM_FAIL_NUM(1);
        g_stTafAgentCtx.ulInitFlg = VOS_FALSE;
        return VOS_ERR;
    }
    else
    {
        TAF_AGENT_DBG_SAVE_MUTEX_SEM_ID(g_stTafAgentCtx.hTafAcpuSyncSem);
    }

    /* 分配二进制信号量 */
    if (VOS_OK != VOS_SmBCreate( "CNF", 0, VOS_SEMA4_FIFO, &g_stTafAgentCtx.hTafAcpuCnfSem))
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "Create aps acpu cnf sem failed!");
        TAF_AGENT_DBG_CREATE_BINARY_SEM_FAIL_NUM(1);
        g_stTafAgentCtx.ulInitFlg = VOS_FALSE;
        return VOS_ERR;
    }
    else
    {
        TAF_AGENT_DBG_SAVE_BINARY_SEM_ID(g_stTafAgentCtx.hTafAcpuCnfSem);
    }

    g_stTafAgentCtx.ulInitFlg = VOS_TRUE;

    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

    TAF_AGENT_ClearMsg();

    return VOS_OK;
}


VOS_SEM TAF_AGENT_GetTafAcpuSyncSem(VOS_VOID)
{
    return g_stTafAgentCtx.hTafAcpuSyncSem;
}


VOS_SEM TAF_AGENT_GetTafAcpuCnfSem(VOS_VOID)
{
    return g_stTafAgentCtx.hTafAcpuCnfSem;
}


VOS_UINT8* TAF_AGENT_GetTafAcpuCnfMsg(VOS_VOID)
{
    return g_stTafAgentCtx.pucTafAcpuCnfMsg;
}


VOS_VOID TAF_AGENT_SetTafAcpuCnfMsg(VOS_UINT8* pMsg)
{
    g_stTafAgentCtx.pucTafAcpuCnfMsg = pMsg;
}


VOS_VOID TAF_AGENT_ClearMsg(VOS_VOID)
{
    PS_MEM_SET(g_stTafAgentCtx.aucMsg,0,sizeof(g_stTafAgentCtx.aucMsg));
}


VOS_UINT8* TAF_AGENT_SaveMsg(
    VOS_UINT8                          *pucMsg,
    VOS_UINT32                          ulLen
)
{
    if ((TAFAGENT_APS_MAX_MSG_LEN - VOS_MSG_HEAD_LENGTH) >= ulLen)
    {
        /* 备份回复消息 */
        PS_MEM_CPY(g_stTafAgentCtx.aucMsg, pucMsg, ulLen + VOS_MSG_HEAD_LENGTH);

        return &(g_stTafAgentCtx.aucMsg[0]);
    }
    else
    {
        (VOS_VOID)vos_printf("TAF_AGENT_SaveMsg-->msg len too big\n");
        return VOS_NULL_PTR;
    }
}


VOS_VOID TAF_AGENT_ShowStats(VOS_VOID)
{
    (VOS_VOID)vos_printf("********************TAF AGENT统计信息*******************\n");
    (VOS_VOID)vos_printf("模块初始化标识                              %d\n", g_stTafAgentCtx.ulInitFlg);
    (VOS_VOID)vos_printf("当前的互斥信号量                            %x\n", g_stTafAgentCtx.hTafAcpuSyncSem);
    (VOS_VOID)vos_printf("当前的互斥信号量                            %x\n", g_stTafAgentCtx.hTafAcpuCnfSem);
    (VOS_VOID)vos_printf("创建的互斥信号量                            %p\n", g_stTafAgentStats.ulMutexSemId);
    (VOS_VOID)vos_printf("创建的二进制信号量                          %p\n", g_stTafAgentStats.ulBinarySemId);
    (VOS_VOID)vos_printf("创建互斥信号量失败次数                      %d\n", g_stTafAgentStats.ulCreateMutexSemFailNum);
    (VOS_VOID)vos_printf("创建二进制信号量失败次数                    %d\n", g_stTafAgentStats.ulCreateBinarySemFailNum);
    (VOS_VOID)vos_printf("锁互斥信号量失败次数                        %d\n", g_stTafAgentStats.ulLockMutexSemFailNum);
    (VOS_VOID)vos_printf("锁二进制信号量失败次数                      %d\n", g_stTafAgentStats.ulLockBinarySemFailNum);
    (VOS_VOID)vos_printf("最后一次锁互斥信号量失败原因                %x\n", g_stTafAgentStats.ulLastMutexSemErrRslt);
    (VOS_VOID)vos_printf("最后一次锁二进制信号量失败原因              %x\n", g_stTafAgentStats.ulLastBinarySemErrRslt);
    (VOS_VOID)vos_printf("同步消息为空次数                            %d\n", g_stTafAgentStats.ulSyncMsgIsNullNum);
    (VOS_VOID)vos_printf("同步消息不匹配次数                          %d\n", g_stTafAgentStats.ulSyncMsgNotMatchNum);

    (VOS_VOID)vos_printf("\r\n");

}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
