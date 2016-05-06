
#define    THIS_FILE_ID        PS_FILE_ID_TAF_AGENT_C

#ifdef __cplusplus
  #if __cplusplus
  extern "C"{
  #endif
#endif

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafAgent.h"
#include "TafAgentCtx.h"
#include "TafAgentLog.h"
#include "TafAgentInterface.h"
#include "TafAgentOamInterface.h"


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
extern VOS_UINT32 AT_GetDestPid(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT32                          ulRcvPid
);

/*****************************************************************************
3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : TAF_AGENT_PidInit
 功能描述  : TAF AGENT PID的初始化函数，该PID挂在OM FID之下。
 输入参数  : enum VOS_INIT_PHASE_DEFINE enPhase
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月22日
    作    者   : c00173809
    修改内容   : 新生成函数/PS融合项目
*****************************************************************************/
VOS_UINT32 TAF_AGENT_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase)
{
    switch ( enPhase )
    {
        case VOS_IP_INITIAL:
            return Taf_Agent_InitCtx();

        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_AGENT_IsValidMsg
 功能描述  : 判断是否是有效的消息
 输入参数  : MsgBlock* pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月22日
    作    者   : C00173809
    修改内容   : 新生成函数/PS融合项目

  2.日    期   : 2012年12月24日
    作    者   : L60609
    修改内容   : DSDA Phase II
  3.日    期   : 2013年4月16日
    作    者   : s00217060
    修改内容   : 主动上报AT命令控制下移至C核
  4.日    期   : 2015年6月25日
    作    者   : l00198894
    修改内容   : TSTS
*****************************************************************************/
VOS_UINT32 TAF_AGENT_IsValidMsg(MsgBlock* pstMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader;

    if (VOS_NULL_PTR == pstMsg)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_IsValidMsg: Msg is invalid!");
        return VOS_ERR;
    }

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    /* Modified by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-16, begin */
    if ((I0_WUEPS_PID_TAF == pstMsgHeader->ulSenderPid)
     || (I1_WUEPS_PID_TAF == pstMsgHeader->ulSenderPid)
     || (I2_WUEPS_PID_TAF == pstMsgHeader->ulSenderPid)
     || (I0_UEPS_PID_MTA  == pstMsgHeader->ulSenderPid)
     || (I1_UEPS_PID_MTA  == pstMsgHeader->ulSenderPid)
     || (I2_UEPS_PID_MTA  == pstMsgHeader->ulSenderPid))
    /* Modified by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-16, end */
    {

        if ((ID_TAFAGENT_APS_FIND_CID_FOR_DIAL_CNF <= pstMsgHeader->ulMsgName)
         && (ID_TAFAGENT_MSG_ID_ENUM_BUTT > pstMsgHeader->ulMsgName))
        {
            return VOS_OK;
        }
    }

   return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : TAF_AGENT_ClearAllSem
 功能描述  : 清空所有的信号量
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年04月17日
    作    者   : f00179208
    修改内容   : 新生成函数/C核单独复位项目
*****************************************************************************/
VOS_VOID TAF_AGENT_ClearAllSem(VOS_VOID)
{
    /* 如果有锁的存在 */
    if (VOS_TRUE == TAF_AGENT_GET_ACPU_CNF_SEM_LOCK_FLG())
    {
        VOS_SmV(TAF_AGENT_GetTafAcpuCnfSem());
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_AGENT_ProcMsg
 功能描述  : TAF AGENT的消息处理函数
 输入参数  : MsgBlock* pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月22日
    作    者   : C00173809
    修改内容   : 新生成函数/PS融合项目

  2.日    期   : 2012年7月17日
    作    者   : A00165503
    修改内容   : DTS2012071607302: TAF跨核同步API实现优化, 防止异常出现后,
                 所有API功能失效
*****************************************************************************/
VOS_VOID TAF_AGENT_ProcMsg(MsgBlock* pstMsg)
{
    VOS_UINT8                          *pucMsg;

    if (VOS_OK == TAF_AGENT_IsValidMsg(pstMsg))
    {
        if (VOS_FALSE == TAF_AGENT_GET_ACPU_CNF_SEM_LOCK_FLG())
        {
            return;
        }

        /* 判断消息是否被释放 */
        if (VOS_NULL_PTR == TAF_AGENT_GetTafAcpuCnfMsg())
        {
            /* 备份回复消息 */
            pucMsg = TAF_AGENT_SaveMsg((VOS_UINT8*)pstMsg,pstMsg->ulLength);

            TAF_AGENT_SetTafAcpuCnfMsg(pucMsg);

            TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

            /* 释放信号量，使得调用API任务继续运行 */
            VOS_SmV(TAF_AGENT_GetTafAcpuCnfSem());
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_AGENT_FindCidForDial
 功能描述  : 通过同步机制获取用于拨号的CID
 输入参数  :
 输出参数  : VOS_VOID
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月18日
    作    者   : c00173809
    修改内容   : PS融合项目,发送同步消息

  2.日    期   : 2012年7月4日
    作    者   : A00165503
    修改内容   : DTS2012042102488: TAF AGENT模块增加软调信息, 用于定位跨核API
                 调用失败问题

  3.日    期   : 2012年7月17日
    作    者   : A00165503
    修改内容   : DTS2012071607302: TAF跨核同步API实现优化, 防止异常出现后,
                 所有API功能失效

  4.日    期   : 2012年7月26日
    作    者   : A00165503
    修改内容   : DTS2012072505555: TAF跨核同步API实现优化, 增加消息为空保护

  5.日    期   : 2012年12月21日
    作    者   : l00227485
    修改内容   : DSDA PhaseII
*****************************************************************************/
VOS_UINT32 TAF_AGENT_FindCidForDial(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT8                          *pCid
)
{
    VOS_UINT32                                  ulResult;
    TAFAGENT_APS_FIND_CID_FOR_DIAL_CNF_STRU    *pstCnf;
    TAFAGENT_APS_FIND_CID_FOR_DIAL_REQ_STRU    *pstMsg;

    ulResult                = VOS_ERR;

    TAF_AGENT_SetTafAcpuCnfMsg(VOS_NULL_PTR);

    TAF_AGENT_ClearMsg();

    /* 如果同步信号量已锁，挂起任务，依次进入等待队列；如果同步信号量未锁，锁信号量。*/
    ulResult = VOS_SmP(TAF_AGENT_GetTafAcpuSyncSem(), 0);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_FindCidForDial: Lock Mutex SEM Failed!");
        TAF_AGENT_DBG_SAVE_LAST_MUTEX_SEM_ERR_RSLT(ulResult);
        TAF_AGENT_DBG_LOCK_MUTEX_SEM_FAIL_NUM(1);
        return VOS_ERR;
    }

    /* 构造消息 */
    pstMsg = (TAFAGENT_APS_FIND_CID_FOR_DIAL_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(ACPU_PID_TAFAGENT,
                                                                                    sizeof(TAFAGENT_APS_FIND_CID_FOR_DIAL_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAFAGENT_APS_FIND_CID_FOR_DIAL_REQ_STRU: Malloc Msg Failed!");

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    /* 填写消息头 */
    pstMsg->ulReceiverPid               = AT_GetDestPid(usClientId, I0_WUEPS_PID_TAF);
    pstMsg->enMsgId                     = ID_TAFAGENT_APS_FIND_CID_FOR_DIAL_REQ;

    /* 将请求消息发送给CCPU */
    ulResult = PS_SEND_MSG(ACPU_PID_TAFAGENT, pstMsg);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_FindCidForDial: Send Msg Failed!");

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_TRUE);

    /* 等待回复信号量初始为锁状态，等待CCPU的回复后信号量解锁。 */
    ulResult = VOS_SmP(TAF_AGENT_GetTafAcpuCnfSem(), PS_SYNC_CNF_TIMEOUT_LEN);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_FindCidForDial: Lock Binary SEM Failed!");
        TAF_AGENT_DBG_SAVE_LAST_BIN_SEM_ERR_RSLT(ulResult);
        TAF_AGENT_DBG_LOCK_BINARY_SEM_FAIL_NUM(1);

        TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    ulResult    = VOS_ERR;
    pstCnf      = (TAFAGENT_APS_FIND_CID_FOR_DIAL_CNF_STRU*)TAF_AGENT_GetTafAcpuCnfMsg();

    if (VOS_NULL_PTR == pstCnf)
    {
        TAF_AGENT_DBG_SYNC_MSG_IS_NULL_NUM(1);

        TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    if ((ID_TAFAGENT_APS_FIND_CID_FOR_DIAL_CNF == pstCnf->enMsgId)
     && (VOS_OK == pstCnf->ulRet))
    {
        *pCid       = pstCnf->ucCid;
        ulResult    = VOS_OK;
    }
    else
    {
        TAF_AGENT_DBG_SYNC_MSG_NOT_MATCH_NUM(1);
    }

    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

    VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

    return ulResult;
}

/*****************************************************************************
 函 数 名  : TAF_AGENT_SetPdpCidPara
 功能描述  : 设置指定CID的参数
 输入参数  : MN_CLIENT_ID_T                      usClientId,
             TAF_PS_DIAL_PARA_STRU              *pstPdpPriPara
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月18日
    作    者   : c00173809
    修改内容   : PS融合项目,提供跨核同步API

  2.日    期   : 2012年7月4日
    作    者   : A00165503
    修改内容   : DTS2012042102488: TAF AGENT模块增加软调信息, 用于定位跨核API
                 调用失败问题

  3.日    期   : 2012年7月17日
    作    者   : A00165503
    修改内容   : DTS2012071607302: TAF跨核同步API实现优化, 防止异常出现后,
                 所有API功能失效

  4.日    期   : 2012年7月26日
    作    者   : A00165503
    修改内容   : DTS2012072505555: TAF跨核同步API实现优化, 增加消息为空保护

  5.日    期   : 2012年12月21日
    作    者   : l00227485
    修改内容   : DSDA PhaseII
*****************************************************************************/
VOS_UINT32 TAF_AGENT_SetPdpCidPara(
    MN_CLIENT_ID_T                      usClientId,
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt
)
{
    VOS_UINT32                                  ulResult;
    TAFAGENT_APS_SET_CID_PARA_CNF_STRU         *pstCnf;
    TAFAGENT_APS_SET_CID_PARA_REQ_STRU         *pstMsg;

    ulResult                = VOS_ERR;

    TAF_AGENT_SetTafAcpuCnfMsg(VOS_NULL_PTR);

    TAF_AGENT_ClearMsg();

    /* 如果同步信号量已锁，挂起任务，依次进入等待队列；如果同步信号量未锁，锁信号量。*/
    ulResult = VOS_SmP(TAF_AGENT_GetTafAcpuSyncSem(), 0);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_SetPdpCidPara: Lock Mutex SEM Failed!");
        TAF_AGENT_DBG_SAVE_LAST_MUTEX_SEM_ERR_RSLT(ulResult);
        TAF_AGENT_DBG_LOCK_MUTEX_SEM_FAIL_NUM(1);
        return VOS_ERR;
    }

    /* 构造消息 */
    pstMsg = (TAFAGENT_APS_SET_CID_PARA_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(ACPU_PID_TAFAGENT,
                                                                               sizeof(TAFAGENT_APS_SET_CID_PARA_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_SetPdpCidPara: Malloc Msg Failed!");

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    /* 填写消息头 */
    pstMsg->ulReceiverPid               = AT_GetDestPid(usClientId, I0_WUEPS_PID_TAF);
    pstMsg->enMsgId                     = ID_TAFAGENT_APS_SET_CID_PARA_REQ;

    pstMsg->ulClientID                  = usClientId;

    PS_MEM_CPY((VOS_VOID*)&(pstMsg->stPdpPrimContextExt),(VOS_VOID*)pstPdpPrimContextExt,sizeof(TAF_PDP_PRIM_CONTEXT_EXT_STRU));

    /* 将请求消息发送给CCPU */
    ulResult = PS_SEND_MSG(ACPU_PID_TAFAGENT, pstMsg);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_SetPdpCidPara: Send Msg Failed!");

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_TRUE);

    /* 等待回复信号量初始为锁状态，等待CCPU的回复后信号量解锁。 */
    ulResult = VOS_SmP(TAF_AGENT_GetTafAcpuCnfSem(), PS_SYNC_CNF_TIMEOUT_LEN);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_SetPdpCidPara: Lock Binary SEM Failed!");
        TAF_AGENT_DBG_SAVE_LAST_BIN_SEM_ERR_RSLT(ulResult);
        TAF_AGENT_DBG_LOCK_BINARY_SEM_FAIL_NUM(1);

        TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    ulResult    = VOS_ERR;
    pstCnf      = (TAFAGENT_APS_SET_CID_PARA_CNF_STRU*)(TAF_AGENT_GetTafAcpuCnfMsg());

    if (VOS_NULL_PTR == pstCnf)
    {
        TAF_AGENT_DBG_SYNC_MSG_IS_NULL_NUM(1);

        TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    if ((ID_TAFAGENT_APS_SET_CID_PARA_CNF == pstCnf->enMsgId)
     && (VOS_OK == pstCnf->ulRet))
    {
        ulResult = VOS_OK;
    }
    else
    {
        TAF_AGENT_DBG_SYNC_MSG_NOT_MATCH_NUM(1);
    }

    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

    VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

    return ulResult;

}

/*****************************************************************************
 函 数 名  : TAF_AGENT_GetPdpCidPara
 功能描述  : 查询指定CID的参数
 输入参数  : TAF_PDP_PRIM_CONTEXT_STRU                   *pstPdpPriPara,
             VOS_UINT8                           ucCid
 输出参数  : TAF_PDP_PRIM_CONTEXT_STRU                   *pstPdpPriPara
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月18日
    作    者   : c00173809
    修改内容   : PS融合项目,提供跨核同步API

  2.日    期   : 2012年7月4日
    作    者   : A00165503
    修改内容   : DTS2012042102488: TAF AGENT模块增加软调信息, 用于定位跨核API
                 调用失败问题

  3.日    期   : 2012年7月17日
    作    者   : A00165503
    修改内容   : DTS2012071607302: TAF跨核同步API实现优化, 防止异常出现后,
                 所有API功能失效

  4.日    期   : 2012年7月26日
    作    者   : A00165503
    修改内容   : DTS2012072505555: TAF跨核同步API实现优化, 增加消息为空保护

  5.日    期   : 2012年12月21日
    作    者   : l00227485
    修改内容   : DSDA PhaseII
*****************************************************************************/
VOS_UINT32 TAF_AGENT_GetPdpCidPara(
    TAF_PDP_PRIM_CONTEXT_STRU                   *pstPdpPriPara,
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT8                           ucCid
)
{
    VOS_UINT32                                  ulResult;
    TAFAGENT_APS_GET_CID_PARA_CNF_STRU         *pstCnf;
    TAFAGENT_APS_GET_CID_PARA_REQ_STRU         *pstMsg;

    ulResult                = VOS_ERR;

    TAF_AGENT_SetTafAcpuCnfMsg(VOS_NULL_PTR);

    TAF_AGENT_ClearMsg();

    /* 如果同步信号量已锁，挂起任务，依次进入等待队列；如果同步信号量未锁，锁信号量。*/
    ulResult = VOS_SmP(TAF_AGENT_GetTafAcpuSyncSem(), 0);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_GetPdpCidPara: Lock Mutex SEM Failed!");
        TAF_AGENT_DBG_SAVE_LAST_MUTEX_SEM_ERR_RSLT(ulResult);
        TAF_AGENT_DBG_LOCK_MUTEX_SEM_FAIL_NUM(1);
        return VOS_ERR;
    }

    /* 构造消息 */
    pstMsg = (TAFAGENT_APS_GET_CID_PARA_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(ACPU_PID_TAFAGENT,
                                                                               sizeof(TAFAGENT_APS_GET_CID_PARA_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_GetPdpCidPara: Malloc Msg Failed!");

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    /* 填写消息头 */
    pstMsg->ulReceiverPid               = AT_GetDestPid(usClientId, I0_WUEPS_PID_TAF);
    pstMsg->enMsgId                     = ID_TAFAGENT_APS_GET_CID_PARA_REQ;

    pstMsg->ucCid                       = ucCid;

    /* 将请求消息发送给CCPU */
    ulResult = PS_SEND_MSG(ACPU_PID_TAFAGENT, pstMsg);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_GetPdpCidPara: Send Msg Failed!");

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_TRUE);

    /* 等待回复信号量初始为锁状态，等待CCPU的回复后信号量解锁。 */
    ulResult = VOS_SmP(TAF_AGENT_GetTafAcpuCnfSem(), PS_SYNC_CNF_TIMEOUT_LEN);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_GetPdpCidPara: Lock Binary SEM Failed!");
        TAF_AGENT_DBG_SAVE_LAST_BIN_SEM_ERR_RSLT(ulResult);
        TAF_AGENT_DBG_LOCK_BINARY_SEM_FAIL_NUM(1);

        TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    ulResult    = VOS_ERR;
    pstCnf      = (TAFAGENT_APS_GET_CID_PARA_CNF_STRU*)(TAF_AGENT_GetTafAcpuCnfMsg());

    if (VOS_NULL_PTR == pstCnf)
    {
        TAF_AGENT_DBG_SYNC_MSG_IS_NULL_NUM(1);

        TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    if ((ID_TAFAGENT_APS_GET_CID_PARA_CNF == pstCnf->enMsgId)
     && (VOS_OK == pstCnf->ulRet))
    {
        PS_MEM_CPY((VOS_VOID*)pstPdpPriPara,(VOS_VOID*)&(pstCnf->stCidInfo),sizeof(TAF_PDP_PRIM_CONTEXT_STRU));
        ulResult = VOS_OK;
    }
    else
    {
        TAF_AGENT_DBG_SYNC_MSG_NOT_MATCH_NUM(1);
    }

    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

    VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

    return ulResult;

}


/*****************************************************************************
 函 数 名  : TAF_AGENT_SetPdpCidQosPara
 功能描述  : 设置指定CID的QOS参数
 输入参数  : MN_CLIENT_ID_T                      usClientId,
             TAF_PS_PDP_QOS_SET_PARA_STRU       *pstQosPara
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月29日
    作    者   : l60609
    修改内容   : DTS2013062201514:增加设置QOS参数同步接口

*****************************************************************************/
VOS_UINT32 TAF_AGENT_SetPdpCidQosPara(
    MN_CLIENT_ID_T                      usClientId,
    TAF_PS_PDP_QOS_SET_PARA_STRU       *pstQosPara
)
{
    VOS_UINT32                                  ulResult;
    TAFAGENT_APS_SET_CID_QOS_PARA_CNF_STRU     *pstCnf;
    TAFAGENT_APS_SET_CID_QOS_PARA_REQ_STRU     *pstMsg;

    ulResult                = VOS_ERR;

    TAF_AGENT_SetTafAcpuCnfMsg(VOS_NULL_PTR);

    TAF_AGENT_ClearMsg();

    /* 如果同步信号量已锁，挂起任务，依次进入等待队列；如果同步信号量未锁，锁信号量。*/
    ulResult = VOS_SmP(TAF_AGENT_GetTafAcpuSyncSem(), 0);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_SetPdpCidQosPara: Lock Mutex SEM Failed!");
        TAF_AGENT_DBG_SAVE_LAST_MUTEX_SEM_ERR_RSLT(ulResult);
        TAF_AGENT_DBG_LOCK_MUTEX_SEM_FAIL_NUM(1);
        return VOS_ERR;
    }

    /* 构造消息 */
    pstMsg = (TAFAGENT_APS_SET_CID_QOS_PARA_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(ACPU_PID_TAFAGENT,
                                                                               sizeof(TAFAGENT_APS_SET_CID_QOS_PARA_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_SetPdpCidQosPara: Malloc Msg Failed!");

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    /* 填写消息头 */
    pstMsg->ulReceiverPid               = AT_GetDestPid(usClientId, I0_WUEPS_PID_TAF);
    pstMsg->ulMsgId                     = ID_TAFAGENT_APS_SET_CID_QOS_PARA_REQ;

    pstMsg->usClientId                  = usClientId;

    PS_MEM_CPY((VOS_VOID*)&(pstMsg->stQosPara), (VOS_VOID*)pstQosPara, sizeof(TAF_PS_PDP_QOS_SET_PARA_STRU));

    /* 将请求消息发送给CCPU */
    ulResult = PS_SEND_MSG(ACPU_PID_TAFAGENT, pstMsg);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_SetPdpCidQosPara: Send Msg Failed!");

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_TRUE);

    /* 等待回复信号量初始为锁状态，等待CCPU的回复后信号量解锁。 */
    ulResult = VOS_SmP(TAF_AGENT_GetTafAcpuCnfSem(), PS_SYNC_CNF_TIMEOUT_LEN);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_SetPdpCidQosPara: Lock Binary SEM Failed!");
        TAF_AGENT_DBG_SAVE_LAST_BIN_SEM_ERR_RSLT(ulResult);
        TAF_AGENT_DBG_LOCK_BINARY_SEM_FAIL_NUM(1);

        TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    ulResult    = VOS_ERR;
    pstCnf      = (TAFAGENT_APS_SET_CID_QOS_PARA_CNF_STRU*)(TAF_AGENT_GetTafAcpuCnfMsg());

    if (VOS_NULL_PTR == pstCnf)
    {
        TAF_AGENT_DBG_SYNC_MSG_IS_NULL_NUM(1);

        TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    if ((ID_TAFAGENT_APS_SET_CID_QOS_PARA_CNF == pstCnf->enMsgId)
     && (VOS_OK == pstCnf->ulRet))
    {
        ulResult = VOS_OK;
    }
    else
    {
        TAF_AGENT_DBG_SYNC_MSG_NOT_MATCH_NUM(1);
    }

    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

    VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

    return ulResult;

}

/*****************************************************************************
 函 数 名  : TAF_AGENT_GetPdpCidQosPara
 功能描述  : 查询指定CID的参数
 输入参数  : MN_CLIENT_ID_T                      usClientId,
             VOS_UINT8                           ucCid
 输出参数  : TAF_PS_PDP_QOS_QUERY_PARA_STRU     *pstQosPara
 调用函数  :
 被调函数  :

 修改历史      :
   1.日    期   : 2013年06月29日
     作    者   : l60609
     修改内容   : DTS2013062201514:增加设置QOS参数同步接口
*****************************************************************************/
VOS_UINT32 TAF_AGENT_GetPdpCidQosPara(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT8                           ucCid,
    TAF_PS_PDP_QOS_QUERY_PARA_STRU     *pstQosPara
)
{
    VOS_UINT32                                  ulResult;
    TAFAGENT_APS_GET_CID_QOS_PARA_CNF_STRU     *pstCnf;
    TAFAGENT_APS_GET_CID_QOS_PARA_REQ_STRU     *pstMsg;

    ulResult                = VOS_ERR;

    TAF_AGENT_SetTafAcpuCnfMsg(VOS_NULL_PTR);

    TAF_AGENT_ClearMsg();
    /* 如果同步信号量已锁，挂起任务，依次进入等待队列；如果同步信号量未锁，锁信号量。*/
    ulResult = VOS_SmP(TAF_AGENT_GetTafAcpuSyncSem(), 0);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_GetPdpCidQosPara: Lock Mutex SEM Failed!");
        TAF_AGENT_DBG_SAVE_LAST_MUTEX_SEM_ERR_RSLT(ulResult);
        TAF_AGENT_DBG_LOCK_MUTEX_SEM_FAIL_NUM(1);
        return VOS_ERR;
    }

    /* 构造消息 */
    pstMsg = (TAFAGENT_APS_GET_CID_QOS_PARA_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(ACPU_PID_TAFAGENT,
                                                                               sizeof(TAFAGENT_APS_GET_CID_QOS_PARA_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_GetPdpCidQosPara: Malloc Msg Failed!");

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    /* 填写消息头 */
    pstMsg->ulReceiverPid               = AT_GetDestPid(usClientId, I0_WUEPS_PID_TAF);
    pstMsg->ulMsgId                     = ID_TAFAGENT_APS_GET_CID_QOS_PARA_REQ;
    pstMsg->ucCid                       = ucCid;

    /* 将请求消息发送给CCPU */
    ulResult = PS_SEND_MSG(ACPU_PID_TAFAGENT, pstMsg);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_GetPdpCidQosPara: Send Msg Failed!");

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_TRUE);

    /* 等待回复信号量初始为锁状态，等待CCPU的回复后信号量解锁。 */
    ulResult = VOS_SmP(TAF_AGENT_GetTafAcpuCnfSem(), PS_SYNC_CNF_TIMEOUT_LEN);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_GetPdpCidQosPara: Lock Binary SEM Failed!");
        TAF_AGENT_DBG_SAVE_LAST_BIN_SEM_ERR_RSLT(ulResult);
        TAF_AGENT_DBG_LOCK_BINARY_SEM_FAIL_NUM(1);

        TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    ulResult    = VOS_ERR;
    pstCnf      = (TAFAGENT_APS_GET_CID_QOS_PARA_CNF_STRU*)(TAF_AGENT_GetTafAcpuCnfMsg());

    if (VOS_NULL_PTR == pstCnf)
    {
        TAF_AGENT_DBG_SYNC_MSG_IS_NULL_NUM(1);

        TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    if ((ID_TAFAGENT_APS_GET_CID_QOS_PARA_CNF == pstCnf->enMsgId)
     && (VOS_OK == pstCnf->ulRet))
    {
        PS_MEM_CPY((VOS_VOID*)pstQosPara, (VOS_VOID*)&(pstCnf->stQosPara), sizeof(TAF_PS_PDP_QOS_QUERY_PARA_STRU));
        ulResult = VOS_OK;
    }
    else
    {
        TAF_AGENT_DBG_SYNC_MSG_NOT_MATCH_NUM(1);
    }

    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

    VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

    return ulResult;

}


/*****************************************************************************
 函 数 名  : TAF_AGENT_GetCallInfo
 功能描述  : 获取通话信息同步api
 输入参数  : MN_CLIENT_ID_T                      usClientId
             VOS_UINT8                           *pucNumOfCalls
             MN_CALL_INFO_STRU                   *pstCallInfos
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月27日
    作    者   : w00199382
    修改内容   : 新生成函数

  2.日    期   : 2012年7月4日
    作    者   : A00165503
    修改内容   : DTS2012042102488: TAF AGENT模块增加软调信息, 用于定位跨核API
                 调用失败问题

  3.日    期   : 2012年7月17日
    作    者   : A00165503
    修改内容   : DTS2012071607302: TAF跨核同步API实现优化, 防止异常出现后,
                 所有API功能失效

  4.日    期   : 2012年7月26日
    作    者   : A00165503
    修改内容   : DTS2012072505555: TAF跨核同步API实现优化, 增加消息为空保护

  5.日    期   : 2013年3月13日
    作    者   : l60609
    修改内容   : DSDA PHASE III
*****************************************************************************/
VOS_UINT32 TAF_AGENT_GetCallInfoReq(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT8                          *pucCallNum,
    TAFAGERNT_MN_CALL_INFO_STRU        *pstCallInfos
)
{
    TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU *pstCnf;
    VOS_UINT32                          ulResult;

    ulResult = VOS_ERR;

    TAF_AGENT_SetTafAcpuCnfMsg(VOS_NULL_PTR);

    TAF_AGENT_ClearMsg();

    /* 如果同步信号量已锁，挂起任务，依次进入等待队列；如果同步信号量未锁，锁信号量。*/
    ulResult = VOS_SmP(TAF_AGENT_GetTafAcpuSyncSem(), 0);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_GetCallInfoReq: Lock Mutex SEM Failed!");
        TAF_AGENT_DBG_SAVE_LAST_MUTEX_SEM_ERR_RSLT(ulResult);
        TAF_AGENT_DBG_LOCK_MUTEX_SEM_FAIL_NUM(1);
        return VOS_ERR;
    }

    /* 发送异步应用请求 */
    ulResult = MN_CALL_SendAppRequest(ID_TAFAGENT_MN_GET_CALL_INFO_REQ,
                                      usClientId, 0, 0,
                                      VOS_NULL_PTR);
    if (MN_ERR_NO_ERROR != ulResult)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_GetCallInfoReq: Malloc Msg Failed!");

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_TRUE);

#if (defined(__PS_WIN32_RECUR__))
    ulResult = VOS_OK;
#else
    /* 等待回复信号量初始为锁状态，等待CCPU的回复后信号量解锁。 */
    ulResult = VOS_SmP(TAF_AGENT_GetTafAcpuCnfSem(), PS_SYNC_CNF_TIMEOUT_LEN);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_GetCallInfoReq: Lock Binary SEM Failed!");
        TAF_AGENT_DBG_SAVE_LAST_BIN_SEM_ERR_RSLT(ulResult);
        TAF_AGENT_DBG_LOCK_BINARY_SEM_FAIL_NUM(1);

        TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }


    ulResult      = VOS_ERR;
    pstCnf      = (TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU*)(TAF_AGENT_GetTafAcpuCnfMsg());

    if (VOS_NULL_PTR == pstCnf)
    {
        TAF_AGENT_DBG_SYNC_MSG_IS_NULL_NUM(1);

        TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }


    if (ID_TAFAGENT_MN_GET_CALL_INFO_CNF == pstCnf->enMsgId)
    {
        PS_MEM_CPY((VOS_VOID*)pstCallInfos,
                   (VOS_VOID*)(pstCnf->stCallInfo),
                   sizeof(TAFAGERNT_MN_CALL_INFO_STRU) * MN_CALL_MAX_NUM);

        *pucCallNum = pstCnf->ucNumOfCalls;

        ulResult      = VOS_OK;
    }
    else
    {
        TAF_AGENT_DBG_SYNC_MSG_NOT_MATCH_NUM(1);
    }

    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

    VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());
#endif
    return ulResult;
}

/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */
/*****************************************************************************
 函 数 名  : TAF_AGENT_GetSysMode
 功能描述  : 获取系统模式
 输入参数  : AT_SYS_MODE_STRU                   *pstSysMode
 输出参数  : AT_SYS_MODE_STRU                   *pstSysMode
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月2日
    作    者   : s00217060
    修改内容   : 主动上报AT命令控制下移至C核新增函数
*****************************************************************************/
VOS_UINT32 TAF_AGENT_GetSysMode(
    VOS_UINT16                                 usClientId,
    TAF_AGENT_SYS_MODE_STRU                   *pstSysMode
)
{
    VOS_UINT32                                  ulResult;
    TAFAGENT_MTA_GET_SYSMODE_CNF_STRU          *pstCnf = VOS_NULL_PTR;
    TAFAGENT_MTA_GET_SYSMODE_REQ_STRU          *pstMsg = VOS_NULL_PTR;

    ulResult                = VOS_ERR;

#ifdef DMT
    return DMT_GetSysMode(pstSysMode);
#else
    TAF_AGENT_SetTafAcpuCnfMsg(VOS_NULL_PTR);

    TAF_AGENT_ClearMsg();

    /* 如果同步信号量已锁，挂起任务，依次进入等待队列；如果同步信号量未锁，锁信号量。*/
    ulResult = VOS_SmP(TAF_AGENT_GetTafAcpuSyncSem(), 0);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_GetSysMode: Lock Mutex SEM Failed!");
        TAF_AGENT_DBG_SAVE_LAST_MUTEX_SEM_ERR_RSLT(ulResult);
        TAF_AGENT_DBG_LOCK_MUTEX_SEM_FAIL_NUM(1);
        return VOS_ERR;
    }

    /* 构造消息 */
    pstMsg = (TAFAGENT_MTA_GET_SYSMODE_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(ACPU_PID_TAFAGENT,
                                                                               sizeof(TAFAGENT_MTA_GET_SYSMODE_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_GetSysMode: Malloc Msg Failed!");

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    /* 填写消息头 */
    pstMsg->ulReceiverPid               = AT_GetDestPid(usClientId, I0_UEPS_PID_MTA);

    pstMsg->enMsgId                     = ID_TAFAGENT_MTA_GET_SYSMODE_REQ;

    /* 将请求消息发送给CCPU */
    ulResult = PS_SEND_MSG(ACPU_PID_TAFAGENT, pstMsg);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_GetSysMode: Send Msg Failed!");

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_TRUE);

    /* 等待回复信号量初始为锁状态，等待CCPU的回复后信号量解锁。 */
    ulResult = VOS_SmP(TAF_AGENT_GetTafAcpuCnfSem(), PS_SYNC_CNF_TIMEOUT_LEN);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_GetSysMode: Lock Binary SEM Failed!");
        TAF_AGENT_DBG_SAVE_LAST_BIN_SEM_ERR_RSLT(ulResult);
        TAF_AGENT_DBG_LOCK_BINARY_SEM_FAIL_NUM(1);
        TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);
        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    ulResult    = VOS_ERR;
    pstCnf      = (TAFAGENT_MTA_GET_SYSMODE_CNF_STRU*)(TAF_AGENT_GetTafAcpuCnfMsg());

    if (VOS_NULL_PTR == pstCnf)
    {
        TAF_AGENT_DBG_SYNC_MSG_IS_NULL_NUM(1);

        TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    if ((ID_TAFAGENT_MTA_GET_SYSMODE_CNF == pstCnf->enMsgId)
     && (VOS_OK == pstCnf->ulRet))
    {
        pstSysMode->enRatType       = pstCnf->stSysMode.enRatType;
        pstSysMode->enSysSubMode    = pstCnf->stSysMode.enSysSubMode;
        ulResult = VOS_OK;
    }
    else
    {
        TAF_AGENT_DBG_SYNC_MSG_NOT_MATCH_NUM(1);
    }

    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

    VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

    return ulResult;
#endif
}
/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-2, end */

/*****************************************************************************
 函 数 名  : TAF_AGENT_GetAntState
 功能描述  : 获取天线状态
 输入参数  : VOS_UINT16                   usClientId
 输出参数  : VOS_UINT16                  *pusAntState
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月2日
    作    者   : z60575
    修改内容   : 获取天线状态
*****************************************************************************/
VOS_UINT32 TAF_AGENT_GetAntState(
    VOS_UINT16                                 usClientId,
    VOS_UINT16                                *pusAntState
)
{
    VOS_UINT32                                  ulResult;
    TAFAGENT_MTA_GET_ANT_STATE_CNF_STRU        *pstCnf = VOS_NULL_PTR;
    TAFAGENT_MTA_GET_ANT_STATE_REQ_STRU        *pstMsg = VOS_NULL_PTR;

    ulResult = VOS_ERR;

    TAF_AGENT_SetTafAcpuCnfMsg(VOS_NULL_PTR);

    TAF_AGENT_ClearMsg();

    /* 如果同步信号量已锁，挂起任务，依次进入等待队列；如果同步信号量未锁，锁信号量。*/
    ulResult = VOS_SmP(TAF_AGENT_GetTafAcpuSyncSem(), 0);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_GetAntState: Lock Mutex SEM Failed!");
        TAF_AGENT_DBG_SAVE_LAST_MUTEX_SEM_ERR_RSLT(ulResult);
        TAF_AGENT_DBG_LOCK_MUTEX_SEM_FAIL_NUM(1);
        return VOS_ERR;
    }

    /* 构造消息 */
    pstMsg = (TAFAGENT_MTA_GET_ANT_STATE_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(ACPU_PID_TAFAGENT,
                                                                               sizeof(TAFAGENT_MTA_GET_ANT_STATE_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_GetAntState: Malloc Msg Failed!");

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    /* 填写消息头 */
    pstMsg->ulReceiverPid               = AT_GetDestPid(usClientId, I0_UEPS_PID_MTA);
    pstMsg->enMsgId                     = ID_TAFAGENT_MTA_GET_ANT_STATE_REQ;

    /* 将请求消息发送给CCPU */
    ulResult = PS_SEND_MSG(ACPU_PID_TAFAGENT, pstMsg);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_GetAntState: Send Msg Failed!");

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_TRUE);

    /* 等待回复信号量初始为锁状态，等待CCPU的回复后信号量解锁。 */
    ulResult = VOS_SmP(TAF_AGENT_GetTafAcpuCnfSem(), PS_SYNC_CNF_TIMEOUT_LEN);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_GetAntState: Lock Binary SEM Failed!");
        TAF_AGENT_DBG_SAVE_LAST_BIN_SEM_ERR_RSLT(ulResult);
        TAF_AGENT_DBG_LOCK_BINARY_SEM_FAIL_NUM(1);
        TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);
        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    ulResult    = VOS_ERR;
    pstCnf      = (TAFAGENT_MTA_GET_ANT_STATE_CNF_STRU*)(TAF_AGENT_GetTafAcpuCnfMsg());

    if (VOS_NULL_PTR == pstCnf)
    {
        TAF_AGENT_DBG_SYNC_MSG_IS_NULL_NUM(1);

        TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    if ((ID_TAFAGENT_MTA_GET_ANT_STATE_CNF == pstCnf->enMsgId)
     && (VOS_OK == pstCnf->ulRslt))
    {
        *pusAntState    = pstCnf->usAntState;
        ulResult        = VOS_OK;
    }
    else
    {
        TAF_AGENT_DBG_SYNC_MSG_NOT_MATCH_NUM(1);
    }

    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

    VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

    return ulResult;
}


/*****************************************************************************
 函 数 名  : TAF_AGENT_FidInit
 功能描述  : TAF AGENT FID的初始化函数
 输入参数  : enum VOS_INIT_PHASE_DEFINE enPhase
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年02月17日
    作    者   : f00179208
    修改内容   : 问题单:DTS2013021700415,TAFAGENT单独起一个FID
*****************************************************************************/
VOS_UINT32 TAF_AGENT_FidInit (enum VOS_INIT_PHASE_DEFINE enPhase)
{
    VOS_UINT32                          ulRslt;

    switch(enPhase)
    {
        case VOS_IP_LOAD_CONFIG:

            /* 网卡模块注册PID */
            ulRslt = VOS_RegisterPIDInfo(ACPU_PID_TAFAGENT,
                                        (Init_Fun_Type)TAF_AGENT_PidInit,
                                        (Msg_Fun_Type)TAF_AGENT_ProcMsg);
            if( VOS_OK != ulRslt )
            {
                TAFAGENT_ERROR_LOG1(ACPU_PID_TAFAGENT, "reg ACPU_PID_TAFAGENT VOS_RegisterPIDInfo FAIL! ulRslt: %d\n", ulRslt);

                return VOS_ERR;
            }

            ulRslt = VOS_RegisterTaskPrio(ACPU_FID_TAFAGENT, TAF_AGENT_TASK_PRIORITY);
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }
            break;

        case VOS_IP_FARMALLOC:
        case VOS_IP_INITIAL:
        case VOS_IP_ENROLLMENT:
        case VOS_IP_LOAD_DATA:
        case VOS_IP_FETCH_DATA:
        case VOS_IP_STARTUP:
        case VOS_IP_RIVAL:
        case VOS_IP_KICKOFF:
        case VOS_IP_STANDBY:
        case VOS_IP_BROADCAST_STATE:
        case VOS_IP_RESTART:
        case VOS_IP_BUTT:
            break;

        default:
            break;
    }

    return VOS_OK;
}    /* TAF_AGENT_FidInit */


#ifdef __cplusplus
  #if __cplusplus
  }
  #endif
#endif
