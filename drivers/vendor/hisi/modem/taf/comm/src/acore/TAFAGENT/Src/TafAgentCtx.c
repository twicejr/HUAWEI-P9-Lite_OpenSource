

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

  2.日    期   : 2012年7月4日
    作    者   : A00165503
    修改内容   : DTS2012042102488: TAF AGENT模块增加软调信息, 用于定位跨核API
                 调用失败问题

  3.日    期   : 2012年7月17日
    作    者   : A00165503
    修改内容   : DTS2012071607302: TAF跨核同步API实现优化, 防止异常出现后,
                 所有API功能失效
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

/*****************************************************************************
 函 数 名  : TAF_AGETN_GetTafAcpuSyncSem
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
VOS_SEM TAF_AGENT_GetTafAcpuSyncSem(VOS_VOID)
{
    return g_stTafAgentCtx.hTafAcpuSyncSem;
}

/*****************************************************************************
 函 数 名  : TAF_AGENT_GetTafAcpuCnfSem
 功能描述  : 获取Cnf信号量
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
VOS_SEM TAF_AGENT_GetTafAcpuCnfSem(VOS_VOID)
{
    return g_stTafAgentCtx.hTafAcpuCnfSem;
}

/*****************************************************************************
 函 数 名  : TAF_AGETN_GetTafAcpuCnfMsg
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
VOS_UINT8* TAF_AGENT_GetTafAcpuCnfMsg(VOS_VOID)
{
    return g_stTafAgentCtx.pucTafAcpuCnfMsg;
}

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
VOS_VOID TAF_AGENT_SetTafAcpuCnfMsg(VOS_UINT8* pMsg)
{
    g_stTafAgentCtx.pucTafAcpuCnfMsg = pMsg;
}

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
VOS_VOID TAF_AGENT_ClearMsg(VOS_VOID)
{
    PS_MEM_SET(g_stTafAgentCtx.aucMsg,0,sizeof(g_stTafAgentCtx.aucMsg));
}

/*****************************************************************************
 函 数 名  : TAF_AGENT_SaveMsg
 功能描述  : 保存消息缓冲
 输入参数  :
 输出参数  : VOS_UINT8*
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : c00173809
    修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_AGENT_ShowStats
 功能描述  : 显示TAF AGENT模块的软调信息, 用于定位跨核API调用失败问题
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月4日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2012年7月17日
    作    者   : A00165503
    修改内容   : DTS2012071607302: TAF跨核同步API实现优化, 防止异常出现后,
                 所有API功能失效
*****************************************************************************/
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
