

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "PsTypeDef.h"
#include "TafSpmFsmMainTbl.h"
#include "TafSpmMain.h"
#include "TafSpmCtx.h"
#include "TafSpmFsmServiceCtrlTbl.h"
#include "TafLog.h"
#include "MnComm.h"
#include "UsimPsInterface.h"
#include "TafSpmSndInternalMsg.h"
#include "TafSpmMntn.h"
#include "NasUsimmApi.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 常量定义
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_TAF_SPM_CTX_C

/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/

/*****************************************************************************
  5 变量定义
*****************************************************************************/
/* 保存共用的CTX */
TAF_SPM_CONTEXT_STRU                    g_stTafSpmCtx;


TAF_SPM_GET_MSG_CLIENT_ID_LIST_STRU gastSpmGetClientIdList[] =
{
    {WUEPS_PID_AT,      TAF_SPM_GetClientIdWithAppMsg},
    {MAPS_STK_PID,      TAF_SPM_GetClientIdWithStkMsg},
    {WUEPS_PID_USIM,    TAF_SPM_GetClientIdWithUsimMsg},
    {MAPS_PB_PID,       TAF_SPM_GetClientIdWithPbMsg},
    {WUEPS_PID_TAF,     TAF_SPM_GetClientIdWithTafMsg},
    {VOS_PID_TIMER,     TAF_SPM_GetClientIdWithVosTimerMsg},
};

/*****************************************************************************
  6 函数定义
*****************************************************************************/

TAF_SPM_CONTEXT_STRU* TAF_SPM_GetSpmCtxAddr( VOS_VOID )
{
    return &(g_stTafSpmCtx);
}



VOS_VOID  TAF_SPM_SetCurrEntityFsmState(
    VOS_UINT32                          ulState
)
{
    TAF_SPM_GetSpmCtxAddr()->pstCurrEntityFsm->stFsmCtx.ulState = ulState;

    TAF_SPM_LogFsmInfo();
}


VOS_UINT32  TAF_SPM_GetCurrEntityFsmState( VOS_VOID )
{
    return (TAF_SPM_GetSpmCtxAddr()->pstCurrEntityFsm->stFsmCtx.ulState);
}



VOS_VOID  TAF_SPM_SetCurrEntityFsmClientId(
    VOS_UINT16                          usClientId
)
{
    TAF_SPM_GetSpmCtxAddr()->pstCurrEntityFsm->usClientId = usClientId;
}


VOS_UINT16  TAF_SPM_GetCurrEntityFsmClientId( VOS_VOID )
{
    return (TAF_SPM_GetSpmCtxAddr()->pstCurrEntityFsm->usClientId);
}




VOS_VOID TAF_SPM_SetCurrEntityFsmAddr(
    VOS_UINT8                           ucFsmIndex
)
{
    TAF_SPM_GetSpmCtxAddr()->pstCurrEntityFsm = &(TAF_SPM_GetSpmCtxAddr()->astEntityFsm[ucFsmIndex]);
}




TAF_SPM_CLIENT_ID_ENTITY_FSM_CTX_STRU* TAF_SPM_GetCurrEntityFsmAddr(VOS_VOID)
{
    return (TAF_SPM_GetSpmCtxAddr()->pstCurrEntityFsm);
}


VOS_VOID  TAF_SPM_SetCurrEntityFsmRunFlg(
    VOS_UINT8                           ucRunFlg
)
{
    TAF_SPM_GetSpmCtxAddr()->pstCurrEntityFsm->ucRunFlg = ucRunFlg;
}


VOS_UINT8  TAF_SPM_GetCurrEntityFsmRunFlg(VOS_VOID)
{
    return (TAF_SPM_GetSpmCtxAddr()->pstCurrEntityFsm->ucRunFlg);
}


TAF_SPM_FSM_ID_ENUM_UINT32  TAF_SPM_GetCurrEntityFsmId(VOS_VOID)
{
    return (TAF_SPM_GetSpmCtxAddr()->pstCurrEntityFsm->stFsmCtx.enFsmId);
}


TAF_SPM_FSM_CTX_STRU* TAF_SPM_GetCurrEntityFsmCtxAddr(VOS_VOID)
{
    return &(TAF_SPM_GetSpmCtxAddr()->pstCurrEntityFsm->stFsmCtx);
}


TAF_SPM_MAIN_FSM_CTX_STRU* TAF_SPM_GetCurrMainFsmAddr(VOS_VOID)
{
    return &(TAF_SPM_GetSpmCtxAddr()->stCurMainFsm);
}



VOS_UINT8 TAF_SPM_GetEntityFsmRunFlgByFsmIndex(
    VOS_UINT8                           ucFsmIndex
)
{
    return (TAF_SPM_GetSpmCtxAddr()->astEntityFsm[ucFsmIndex].ucRunFlg);
}


TAF_SPM_FSM_CTX_STRU* TAF_SPM_GetEntityFsmCtxAddrByFsmIndex(
    VOS_UINT8                           ucFsmIndex
)
{
    return &(TAF_SPM_GetSpmCtxAddr()->astEntityFsm[ucFsmIndex].stFsmCtx);
}


VOS_VOID  TAF_SPM_InitEntityFsmCtx(
    TAF_SPM_FSM_CTX_STRU                *pstCurrFsmCtx
)
{
    pstCurrFsmCtx->enFsmId    = TAF_SPM_FSM_BUTT;
    pstCurrFsmCtx->pstFsmDesc = VOS_NULL_PTR;
    pstCurrFsmCtx->ulState    = TAF_SPM_SERVICE_CTRL_STA_BUTT;

    PS_MEM_SET(&pstCurrFsmCtx->stEntryMsg,
               0,
               sizeof(pstCurrFsmCtx->stEntryMsg));
}


VOS_VOID  TAF_SPM_InitMainCtrlInfo(
    TAF_SPM_MAIN_CTRL_INFO_STRU        *pstMainCtrl
)
{
    /* 初始化当前主控信息 */
    pstMainCtrl->ucUpdateEntryMsgFlg     = VOS_FALSE;

    PS_MEM_SET( pstMainCtrl->aucRsv,
                (VOS_UINT8)0x00,
                sizeof(pstMainCtrl->aucRsv) );

    PS_MEM_SET( &(pstMainCtrl->stServiceCtrlEntryMsg),
                (VOS_UINT8)0x00,
                sizeof(TAF_SPM_ENTRY_MSG_STRU) );

    return;
}


VOS_VOID  TAF_SPM_InitServiceCtrlCfgInfo(
    TAF_SPM_SERVICE_CTRL_CFG_INFO_STRU *pstServiceCtrlCfg
)
{
    pstServiceCtrlCfg->ulMeStatus                               = TAF_FDN_CHECK_FEATURE_OFF;
    pstServiceCtrlCfg->ucSimCallCtrlSupportFlg                  = VOS_FALSE;

    pstServiceCtrlCfg->enVpCfgState                             = TAF_SPM_VP_MO_MT_BOTH;


    
    pstServiceCtrlCfg->stBufferServiceReqProtectTimerInfo.ulBufferCcProtectTimerLen 
                                        = TI_TAF_SPM_CC_SMS_SS_SRV_REQ_PROTECT_TIMER_DEFAULT_VAL;
    pstServiceCtrlCfg->stBufferServiceReqProtectTimerInfo.ulBufferSmsProtectTimerLen
                                        = TI_TAF_SPM_CC_SMS_SS_SRV_REQ_PROTECT_TIMER_DEFAULT_VAL;
    pstServiceCtrlCfg->stBufferServiceReqProtectTimerInfo.ulBufferSsProtectTimerLen
                                        = TI_TAF_SPM_CC_SMS_SS_SRV_REQ_PROTECT_TIMER_DEFAULT_VAL;

    
    return;
}



VOS_VOID  TAF_SPM_InitFsmCtx_Main(VOS_VOID)
{
    return;
}



VOS_VOID  TAF_SPM_InitFsmCtx_ServiceCtrl(VOS_VOID)
{
    return;
}


VOS_VOID TAF_SPM_FSM_InitEntityFsm(
    TAF_SPM_FSM_ID_ENUM_UINT32          enFsmId,
    TAF_FSM_DESC_STRU                  *pstFsmDesc,
    VOS_UINT32                          ulState
)
{
    TAF_SPM_FSM_CTX_STRU               *pstCurrEntityFsmCtx         = VOS_NULL_PTR;

    /*  获取当前client ID实体状态机上下文 */
    pstCurrEntityFsmCtx                 = TAF_SPM_GetCurrEntityFsmCtxAddr();

    pstCurrEntityFsmCtx->enFsmId      = enFsmId;
    pstCurrEntityFsmCtx->pstFsmDesc   = pstFsmDesc;
    pstCurrEntityFsmCtx->ulState      = ulState;

    TAF_SPM_SetCurrEntityFsmRunFlg(VOS_TRUE);

    /* 初始化状态机上下文 */
    pstCurrEntityFsmCtx->pstFsmDesc->pfInitHandle();

    TAF_SPM_LogFsmInfo();
}


VOS_VOID TAF_SPM_FSM_InitMainFsm(
    TAF_SPM_FSM_ID_ENUM_UINT32          enFsmId,
    TAF_FSM_DESC_STRU                  *pstFsmDesc,
    VOS_UINT32                          ulState
)
{
    TAF_SPM_MAIN_FSM_CTX_STRU          *pstCurrMainFsm  = VOS_NULL_PTR;

    /*  获取当前main状态机信息 */
    pstCurrMainFsm               = TAF_SPM_GetCurrMainFsmAddr();

    pstCurrMainFsm->stFsmCtx.enFsmId      = enFsmId;
    pstCurrMainFsm->stFsmCtx.pstFsmDesc   = pstFsmDesc;
    pstCurrMainFsm->stFsmCtx.ulState      = ulState;

    /* 初始化状态机上下文 */
    pstCurrMainFsm->stFsmCtx.pstFsmDesc->pfInitHandle();
}



VOS_VOID TAF_SPM_FSM_QuitCurrEntityFsm(VOS_VOID)
{
    TAF_SPM_FSM_CTX_STRU               *pstCurrFsmCtx = VOS_NULL_PTR;

    /*  获取当前的client ID实体状态机上下文 */
    pstCurrFsmCtx               = TAF_SPM_GetCurrEntityFsmCtxAddr();

    /* 清空状态机描述表和状态机ID */
    pstCurrFsmCtx->pstFsmDesc   = VOS_NULL_PTR;
    pstCurrFsmCtx->enFsmId      = TAF_SPM_FSM_BUTT;
    pstCurrFsmCtx->ulState      = TAF_SPM_SERVICE_CTRL_STA_BUTT;

    TAF_SPM_SetCurrEntityFsmClientId(TAF_SPM_INVALID_CLIENT_ID);
    TAF_SPM_SetCurrEntityFsmRunFlg(VOS_FALSE);

    TAF_SPM_LogFsmInfo();
}



VOS_VOID  TAF_SPM_InitEntityFsm(VOS_VOID)
{
    VOS_UINT8                           i;

    /* for 循环，初始化所有实体状态机上下文 */
    for (i = 0; i < TAF_SPM_MAX_CLIENT_ID_ENTITY_FSM_ID_NUM; i++)
    {
        /* 根据设置当前的实体状态机 */
        TAF_SPM_SetCurrEntityFsmAddr(i);

        /* 初始化实体上下文 */
        TAF_SPM_InitEntityFsmCtx(TAF_SPM_GetCurrEntityFsmCtxAddr());

        TAF_SPM_SetCurrEntityFsmRunFlg(VOS_FALSE);

        TAF_SPM_SetCurrEntityFsmClientId(TAF_SPM_INVALID_CLIENT_ID);
    }
}


VOS_VOID  TAF_SPM_InitMainFsm(VOS_VOID)
{
    TAF_SPM_MAIN_FSM_CTX_STRU          *pstMainFsmCtx = VOS_NULL_PTR;

    pstMainFsmCtx = TAF_SPM_GetCurrMainFsmAddr();

    pstMainFsmCtx->stFsmCtx.enFsmId         = TAF_SPM_FSM_BUTT;
    pstMainFsmCtx->stFsmCtx.ulState         = TAF_SPM_MAIN_STA_BUTT;
    pstMainFsmCtx->stFsmCtx.pstFsmDesc      = VOS_NULL_PTR;

    PS_MEM_SET(&pstMainFsmCtx->stFsmCtx.stEntryMsg,
               0,
               sizeof(pstMainFsmCtx->stFsmCtx.stEntryMsg));

}


TAF_SPM_ENTRY_MSG_STRU* TAF_SPM_GetCurrEntityFsmEntryMsgAddr(VOS_VOID)
{
    TAF_SPM_CLIENT_ID_ENTITY_FSM_CTX_STRU                  *pstCurEntityFsmCtx = VOS_NULL_PTR;

    /*  获取当前的client ID状态机上下文地址 */
    pstCurEntityFsmCtx = TAF_SPM_GetCurrEntityFsmAddr();

    return &(pstCurEntityFsmCtx->stFsmCtx.stEntryMsg);
}


VOS_UINT32 TAF_SPM_GetCurrEntityFsmEntryMsgSndPid(VOS_VOID)
{
    TAF_SPM_CLIENT_ID_ENTITY_FSM_CTX_STRU                  *pstCurEntityFsmCtx = VOS_NULL_PTR;
    TAF_SPM_ENTRY_MSG_STRU                                 *pstEntryMsg                = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                                    *pstAppMsg                  = VOS_NULL_PTR;
    VOS_UINT32                                              ulSndPid;

    /*  获取当前的client ID状态机上下文地址 */
    pstCurEntityFsmCtx = TAF_SPM_GetCurrEntityFsmAddr();

    pstEntryMsg  = &(pstCurEntityFsmCtx->stFsmCtx.stEntryMsg);
    pstAppMsg    = (MN_APP_REQ_MSG_STRU*)pstEntryMsg->aucEntryMsgBuffer;
    ulSndPid     = pstAppMsg->ulSenderPid;

    return ulSndPid;
}


VOS_UINT16 TAF_SPM_GetCurrEntityFsmEntryMsgName(VOS_VOID)
{
    TAF_SPM_CLIENT_ID_ENTITY_FSM_CTX_STRU                  *pstCurEntityFsmCtx = VOS_NULL_PTR;
    TAF_SPM_ENTRY_MSG_STRU                                 *pstEntryMsg                = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                                    *pstAppMsg                  = VOS_NULL_PTR;
    VOS_UINT16                                              usMsgName;

    /*  获取当前的client ID状态机上下文地址 */
    pstCurEntityFsmCtx = TAF_SPM_GetCurrEntityFsmAddr();

    pstEntryMsg  = &(pstCurEntityFsmCtx->stFsmCtx.stEntryMsg);
    pstAppMsg    = (MN_APP_REQ_MSG_STRU*)pstEntryMsg->aucEntryMsgBuffer;
    usMsgName    = pstAppMsg->usMsgName;

    return usMsgName;
}


VOS_UINT16 TAF_SPM_GetEntityFsmClientIdByFsmIndex(
    VOS_UINT8                           ucFsmIndex
)
{
    return (TAF_SPM_GetSpmCtxAddr()->astEntityFsm[ucFsmIndex].usClientId);
}


VOS_UINT8 TAF_SPM_GetEntityFsmIndexByClientId(
    VOS_UINT16                          usClientId
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucFsmIndex;
    VOS_UINT16                          usCurClientId;
    VOS_UINT8                           ucRunFlg;

    ucFsmIndex = TAF_SPM_INVALID_CLIENT_ID_ENTITY_FSM_INDEX;

    /* client ID无效不进行查找直接返回 */
    if (TAF_SPM_INVALID_CLIENT_ID == usClientId)
    {
        return ucFsmIndex;
    }

    for (i = 0; i < TAF_SPM_MAX_CLIENT_ID_ENTITY_FSM_ID_NUM; i++)
    {
        usCurClientId   = TAF_SPM_GetEntityFsmClientIdByFsmIndex(i);
        ucRunFlg        = TAF_SPM_GetEntityFsmRunFlgByFsmIndex(i);

        if ((usClientId == usCurClientId)
         && (VOS_TRUE   == ucRunFlg))
        {
            ucFsmIndex = i;
            break;
        }
    }

    return ucFsmIndex;
}



VOS_UINT8 TAF_SPM_GetIdleEntityFsmIndex(VOS_VOID)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucRunFlg;
    VOS_UINT8                           ucIndex;

    ucIndex = TAF_SPM_INVALID_CLIENT_ID_ENTITY_FSM_INDEX;

    for (i = 0; i < TAF_SPM_MAX_CLIENT_ID_ENTITY_FSM_ID_NUM; i++)
    {
        ucRunFlg = TAF_SPM_GetEntityFsmRunFlgByFsmIndex(i);

        if (VOS_FALSE == ucRunFlg)
        {
            ucIndex = i;
            break;
        }
    }

    return ucIndex;
}



VOS_VOID TAF_SPM_SaveCurrEntityFsmEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_ENTRY_MSG_STRU             *pstEntryMsg  = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 获得当前处理入口消息的缓冲区地址 */
    /* 获得当前处理SPM入口消息的缓冲区地址 */
    pstEntryMsg                 =   TAF_SPM_GetCurrEntityFsmEntryMsgAddr();
    pstMsgHeader                = (MSG_HEADER_STRU*)pstMsg;
    ulLen                       = pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH;

    /* 将当前处理的入口消息拷贝到Context对应的缓冲区 */
    PS_MEM_CPY( pstEntryMsg->aucEntryMsgBuffer, pstMsg, ulLen );

    /* 填写Context中的参数 */
    pstEntryMsg->ulEventType    =   ulEventType;

    return;
}




TAF_SPM_TIMER_CTX_STRU*  TAF_SPM_GetTimerCtxAddr( VOS_VOID )
{
    return TAF_SPM_GetSpmCtxAddr()->astSpmTimerCtx;
}


TAF_SPM_SERVICE_CTRL_CFG_INFO_STRU*  TAF_SPM_GetServiceCtrlCfgInfoAddr( VOS_VOID )
{
    return &(TAF_SPM_GetSpmCtxAddr()->stServiceCtrlCfgInfo);
}


TAF_SPM_BUFFER_SERVICE_REQ_PROTECT_TIMER_STRU* TAF_SPM_GetBufferServiceReqProtectTimerInfo(VOS_VOID)
{
    return &(TAF_SPM_GetSpmCtxAddr()->stServiceCtrlCfgInfo.stBufferServiceReqProtectTimerInfo);
}


VOS_UINT32   TAF_Spm_GetBufferCcProtectTimerLen(VOS_VOID)
{
    return TAF_SPM_GetSpmCtxAddr()->stServiceCtrlCfgInfo.stBufferServiceReqProtectTimerInfo.ulBufferCcProtectTimerLen;
}


VOS_UINT32   TAF_SPM_GetBufferSmsProtectTimerLen(VOS_VOID)
{
    return TAF_SPM_GetSpmCtxAddr()->stServiceCtrlCfgInfo.stBufferServiceReqProtectTimerInfo.ulBufferSmsProtectTimerLen;
}


VOS_UINT32   TAF_SPM_GetBufferSsProtectTimerLen(VOS_VOID)
{
    return TAF_SPM_GetSpmCtxAddr()->stServiceCtrlCfgInfo.stBufferServiceReqProtectTimerInfo.ulBufferSsProtectTimerLen;
}


VOS_VOID TAF_SPM_SetUpdateEntryMsgFlg(
    VOS_UINT8                           ucReplaceFlg
)
{
    TAF_SPM_GetSpmCtxAddr()->stMainCtrlInfo.ucUpdateEntryMsgFlg = ucReplaceFlg;
}


VOS_UINT8 TAF_SPM_GetUpdateEntryMsgFlg(VOS_VOID)
{
    return (TAF_SPM_GetSpmCtxAddr()->stMainCtrlInfo.ucUpdateEntryMsgFlg);
}


VOS_VOID TAF_SPM_UpdateServiceCtrlEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_ENTRY_MSG_STRU             *pstEntryMsg  = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 获得当前缓存的发送给SS的请求消息的缓冲区地址 */
    pstEntryMsg                 =   TAF_SPM_GetServiceCtrlEntryMsgAddr();
    pstMsgHeader                =   (MSG_HEADER_STRU*)pstMsg;
    ulLen                       =   pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH;

    /* 消息长度超过了缓存的长度，则不保存, 防止数组越界 */
    if ( ulLen > TAF_SPM_MAX_MSG_BUFFER_LEN )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SPM_UpdateServiceCtrlEntryMsg:Msg too big to save ");
        return ;
    }

    /* 将当前处理的入口消息拷贝到Context对应的缓冲区 */
    PS_MEM_CPY( pstEntryMsg->aucEntryMsgBuffer, pstMsg, ulLen );

    /* 填写Context中的参数 */
    pstEntryMsg->ulEventType    =   ulEventType;

    return;
}


TAF_SPM_ENTRY_MSG_STRU* TAF_SPM_GetServiceCtrlEntryMsgAddr(VOS_VOID)
{
    return &(TAF_SPM_GetSpmCtxAddr()->stMainCtrlInfo.stServiceCtrlEntryMsg);
}


VOS_UINT32 TAF_SPM_GetClientIdWithAppMsg(
    struct MsgCB                       *pstMsg,
    VOS_UINT16                         *pusClientId
)
{
    MN_APP_REQ_MSG_STRU                *pstAppMsg = VOS_NULL_PTR;

    pstAppMsg = (MN_APP_REQ_MSG_STRU *)pstMsg;

    *pusClientId =  pstAppMsg->clientId;

    return VOS_TRUE;
}


VOS_UINT32 TAF_SPM_GetClientIdWithStkMsg(
    struct MsgCB                       *pstMsg,
    VOS_UINT16                         *pusClientId
)
{
    MN_APP_REQ_MSG_STRU                *pstAppMsg       = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader    = VOS_NULL_PTR;
    SI_STK_ENVELOPEDWON_CNF_STRU       *pstEnvelope     = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;
    if (SI_STK_ENVELOPE_CNF == pstMsgHeader->ulMsgName)
    {
        pstEnvelope  = (SI_STK_ENVELOPEDWON_CNF_STRU *)pstMsg;
		/* 低16位为CliendId */
        *pusClientId = (VOS_UINT16)(pstEnvelope->stCmdResult.ulSendPara  & 0x0000ffff);
    }
    else
    {
        pstAppMsg    = (MN_APP_REQ_MSG_STRU *)pstMsg;

        *pusClientId =  pstAppMsg->clientId;
    }

    return VOS_TRUE;
}


VOS_VOID TAF_SPM_GetOpIdWithAppMsg(
    struct MsgCB                       *pstMsg,
    VOS_UINT8                          *pucOpId
)
{
    MN_APP_REQ_MSG_STRU                *pstAppMsg = VOS_NULL_PTR;

    pstAppMsg = (MN_APP_REQ_MSG_STRU *)pstMsg;

    *pucOpId =  pstAppMsg->opId;

    return;
}



VOS_UINT32 TAF_SPM_GetClientIdWithVosTimerMsg(
    struct MsgCB                       *pstMsg,
    VOS_UINT16                         *pusClientId
)
{
    REL_TIMER_MSG                      *pstRcvTimerMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    switch (pstRcvTimerMsg->ulName)
    {
        case TI_TAF_SPM_WAIT_PB_FDN_CHECK_CNF:
        case TI_TAF_SPM_WAIT_USIM_CALL_CTRL_CNF:

            *pusClientId = (VOS_UINT16)pstRcvTimerMsg->ulPara;
            ulRet = VOS_TRUE;

            break;

        default:

            ulRet = VOS_FALSE;
            break;
    }

    return ulRet;
}



VOS_UINT32 TAF_SPM_GetClientIdWithUsimMsg(
    struct MsgCB                       *pstMsg,
    VOS_UINT16                         *pusClientId
)
{
    VOS_UINT32                          ulRet;
    SI_STK_ENVELOPEDWON_CNF_STRU       *pstEnvelope = VOS_NULL_PTR;

    switch (((MSG_HEADER_STRU *)pstMsg)->ulMsgName)
    {
        case SI_STK_ENVELOPE_CNF:
             pstEnvelope  = (SI_STK_ENVELOPEDWON_CNF_STRU *)pstMsg;
            *pusClientId  = (VOS_UINT16)pstEnvelope->stCmdResult.ulSendPara;
             ulRet        = VOS_TRUE;
             break;

        default:

            ulRet = VOS_FALSE;
            break;
    }

    return ulRet;
}


VOS_UINT32 TAF_SPM_GetClientIdWithPbMsg(
    struct MsgCB                       *pstMsg,
    VOS_UINT16                         *pusClientId
)
{
    PB_FDN_CHECK_CNF_STRU              *pstCheckCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    switch (((MSG_HEADER_STRU *)pstMsg)->ulMsgName)
    {
        case SI_PB_EVENT_FDNCHECK_CNF:

            pstCheckCnf     = (PB_FDN_CHECK_CNF_STRU*)pstMsg;
            /* 低16位为CliendId */
           *pusClientId     = (VOS_UINT16)(pstCheckCnf->ulSendPara & 0x0000ffff);
            ulRet           = VOS_TRUE;
            break;

        default:

            ulRet = VOS_FALSE;
            break;
    }

    return ulRet;
}


VOS_UINT32 TAF_SPM_GetClientIdWithTafMsg(
    struct MsgCB                       *pstMsg,
    VOS_UINT16                         *pusClientId
)
{
    TAF_SPM_SERVICE_CTRL_RSLT_STRU     *pstServiceCtrlRsltInd = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    switch (((MSG_HEADER_STRU *)pstMsg)->ulMsgName)
    {
        case TAF_SPM_INTERNAL_SERVICE_CTRL_RESULT_IND:

             pstServiceCtrlRsltInd  = (TAF_SPM_SERVICE_CTRL_RSLT_STRU*)pstMsg;
            *pusClientId            = pstServiceCtrlRsltInd->usClientId;
             ulRet                  = VOS_TRUE;
             break;

        default:

            ulRet = VOS_FALSE;
            break;
    }

    return ulRet;
}


VOS_UINT32  TAF_SPM_GetClientId(
    struct MsgCB                       *pstMsg,
    VOS_UINT16                         *pusClientId
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulTblSize;
    VOS_UINT32                          ulSndPid;
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    TAF_SPM_GET_MSG_CLIENT_ID_FUNC_PTR  pCurFuncProc = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    ulTblSize       = sizeof(gastSpmGetClientIdList)/sizeof(gastSpmGetClientIdList[0]);
    pstMsgHeader    = (MSG_HEADER_STRU *)pstMsg;
    ulSndPid        = pstMsgHeader->ulSenderPid;

     /* 先根据消息的发送PID映射出对应的client ID */
    for (i = 0; i < ulTblSize; i++)
    {
        if (ulSndPid == gastSpmGetClientIdList[i].ulSndPid)
        {
            pCurFuncProc = gastSpmGetClientIdList[i].pGetMsgClientIdProcFunc;
            break;
        }
    }


    if (VOS_NULL_PTR != pCurFuncProc)
    {
        ulRet = pCurFuncProc(pstMsg, pusClientId);

        return ulRet;
    }

    /* 找不到对应的处理函数 */
    return VOS_FALSE;
}


VOS_VOID TAF_SPM_InitServiceReqBufferMsgQueue(VOS_VOID)
{
    TAF_SPM_DOMAIN_SEL_MSG_QUEUE_STRU  *pstBufferMsgQueue = VOS_NULL_PTR;

    /* get address of buffer message queue */
    pstBufferMsgQueue = TAF_SPM_GetBufferMsgQueueAddr();

    /* init buffer CC message queue */
    TAF_SPM_InitBufferCcMsgQueue(&(pstBufferMsgQueue->stCcMsgQueue));

    /* init buffer SMS message queue */
    TAF_SPM_InitBufferSmsMsgQueue(&(pstBufferMsgQueue->stSmsMsgQueue));

    /* init buffer SS message queue */
    TAF_SPM_InitBufferSsMsgQueue(&(pstBufferMsgQueue->stSsMsgQueue));
}

#if (FEATURE_IMS == FEATURE_ON)

VOS_VOID TAF_SPM_InitDomainSelCtx(TAF_SPM_DOMAIN_SEL_CTX_STRU *pstDomainSelCtx)
{
    /* 删除IMS注册状态，移到SDC中 */

    /* 初始化IMS短信发送标志 */
    pstDomainSelCtx->ucImsSmsSendingFlg  = VOS_FALSE;

    /* 初始化上次PS服务状态 */
    pstDomainSelCtx->enLastPsStatus      = TAF_SPM_SERVICE_STATUS_NO_SERVICE;

    /* set IMS SMS supported to TRUE by server */
    TAF_SPM_SetImsSmsSupportedOnImsServer(VOS_TRUE);

    /* 业务请求消息队列初始化移到函数TAF_SPM_InitServiceReqBufferMsgQueue中实现 */

    /* 初始化呼叫换域重拨缓存 */
    TAF_SPM_InitCallRedialBuffer(&(pstDomainSelCtx->stRedialMsgQueue.stCcMsgQueue));

    /* 初始化短信换域重拨缓存 */
    TAF_SPM_InitSmsRedialBuffer(&(pstDomainSelCtx->stRedialMsgQueue.stSmsMsgQueue));

    /* subscript IMS register status */
    pstDomainSelCtx->ulSubscriptId = 0;
    (VOS_VOID)IMSA_AddSubscription(WUEPS_PID_TAF, IMSA_SUBCRIBE_TYPE_NORMAL_REG, 0, &(pstDomainSelCtx->ulSubscriptId));
}

/* 删除IMS注册状态相关函数，移到SDC中 */


VOS_VOID TAF_SPM_SetImsSmsSupportedOnImsServer(
    VOS_UINT8                           ucImsSmsSupported
)
{
    TAF_SPM_GetSpmCtxAddr()->stDomainSelCtx.ucImsSmsSupported = ucImsSmsSupported;

    return;
}


VOS_UINT8 TAF_SPM_GetImsSmsSupportedOnImsServer(VOS_VOID)
{
    return (TAF_SPM_GetSpmCtxAddr()->stDomainSelCtx.ucImsSmsSupported);
}



VOS_UINT8 TAF_SPM_GetImsSmsSendingFlg(VOS_VOID)
{
    return (TAF_SPM_GetSpmCtxAddr()->stDomainSelCtx.ucImsSmsSendingFlg);
}


VOS_VOID TAF_SPM_SetImsSmsSendingFlg(VOS_UINT8 ucImsSmsSendingFlg)
{
    TAF_SPM_GetSpmCtxAddr()->stDomainSelCtx.ucImsSmsSendingFlg = ucImsSmsSendingFlg;
}


TAF_SPM_SERVICE_STATUS_ENUM_UINT8 TAF_SPM_GetLastPsServiceStatus(VOS_VOID)
{
    return (TAF_SPM_GetSpmCtxAddr()->stDomainSelCtx.enLastPsStatus);
}


VOS_VOID TAF_SPM_SetLastPsServiceStatus(TAF_SPM_SERVICE_STATUS_ENUM_UINT8 enCurrPsStatus)
{
    TAF_SPM_GetSpmCtxAddr()->stDomainSelCtx.enLastPsStatus = enCurrPsStatus;
}
#endif /* end of FEATURE_IMS */



TAF_SPM_DOMAIN_SEL_MSG_QUEUE_STRU *TAF_SPM_GetBufferMsgQueueAddr(VOS_VOID)
{
    return &(TAF_SPM_GetSpmCtxAddr()->stDomainSelCtx.stBufferMsgQueue);
}


VOS_VOID TAF_SPM_InitBufferCcMsgQueue(
    TAF_SPM_MSG_CC_QUEUE_STRU          *pstCcMsgQueue
)
{
    VOS_UINT8                           i;

    pstCcMsgQueue->ucCacheMsgNum = 0;

    for (i = 0; i < TAF_SPM_MAX_CC_MSG_QUEUE_NUM; i++)
    {
        PS_MEM_SET(&(pstCcMsgQueue->astMsgQueue[i]), 0, sizeof(TAF_SPM_CACHE_MSG_INFO_STRU));
    }

    PS_MEM_SET(&(pstCcMsgQueue->aucReserve[0]), 0, sizeof(VOS_UINT8)*3);
}


VOS_VOID TAF_SPM_InitBufferSmsMsgQueue(
    TAF_SPM_MSG_SMS_QUEUE_STRU              *pstSmsMsgQueue
)
{
    VOS_UINT8                           i;

    pstSmsMsgQueue->ucCacheMsgNum = 0;

    for (i = 0; i < TAF_SPM_MAX_SMS_MSG_QUEUE_NUM; i++)
    {
        PS_MEM_SET(&(pstSmsMsgQueue->astMsgQueue[i]), 0, sizeof(TAF_SPM_CACHE_MSG_INFO_STRU));
    }

    PS_MEM_SET(&(pstSmsMsgQueue->aucReserve[0]), 0, sizeof(VOS_UINT8)*3);
}


VOS_VOID TAF_SPM_InitBufferSsMsgQueue(
TAF_SPM_MSG_SS_QUEUE_STRU              *pstSsMsgQueue)
{
    VOS_UINT8                           i;

    pstSsMsgQueue->ucCacheMsgNum = 0;

    for (i = 0; i < TAF_SPM_MAX_SS_MSG_QUEUE_NUM; i++)
    {
        PS_MEM_SET(&(pstSsMsgQueue->astMsgQueue[i]), 0, sizeof(TAF_SPM_CACHE_MSG_INFO_STRU));
    }

    PS_MEM_SET(&(pstSsMsgQueue->aucReserve[0]), 0, sizeof(VOS_UINT8)*3);
}


VOS_UINT8 TAF_SPM_GetCcMsgQueueNum(VOS_VOID)
{
    return (TAF_SPM_GetBufferMsgQueueAddr()->stCcMsgQueue.ucCacheMsgNum);
}


VOS_VOID TAF_SPM_SetCcMsgQueueNum(VOS_UINT8 ucCacheMsgNum)
{
    TAF_SPM_GetBufferMsgQueueAddr()->stCcMsgQueue.ucCacheMsgNum = ucCacheMsgNum;
}


VOS_UINT8 TAF_SPM_IsCcMsgQueueFull(VOS_VOID)
{
    return (VOS_UINT8)((TAF_SPM_MAX_CC_MSG_QUEUE_NUM == TAF_SPM_GetCcMsgQueueNum())? VOS_TRUE : VOS_FALSE);
}


TAF_SPM_CACHE_MSG_INFO_STRU *TAF_SPM_GetSpecifiedIndexMessageAddrFromCcQueue(
    VOS_UINT8                           ucIndex
)
{
    return &(TAF_SPM_GetBufferMsgQueueAddr()->stCcMsgQueue.astMsgQueue[ucIndex]);
}


VOS_UINT32 TAF_SPM_PutMessageToCcQueue(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstCacheMsgInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucCacheMsgNum;

    /* check the incoming message length */
    if (TAF_SPM_MAX_MSG_BUFFER_LEN < (pstMsg->ulLength + VOS_MSG_HEAD_LENGTH))
    {
        return VOS_FALSE;
    }

    /* get the number of cached message */
    ucCacheMsgNum   = TAF_SPM_GetCcMsgQueueNum();

    /* get address of free message queue */
    pstCacheMsgInfo = TAF_SPM_GetSpecifiedIndexMessageAddrFromCcQueue(ucCacheMsgNum);

    /* cache message */
    pstCacheMsgInfo->stMsgEntry.ulEventType = ulEventType;
    PS_MEM_CPY(&(pstCacheMsgInfo->stMsgEntry.aucEntryMsgBuffer[0]), pstMsg, pstMsg->ulLength + VOS_MSG_HEAD_LENGTH);

    /* update number of cached messages */
    ucCacheMsgNum++;
    TAF_SPM_SetCcMsgQueueNum(ucCacheMsgNum);

    return (VOS_TRUE);
}

/*lint -save -e958 */

VOS_VOID TAF_SPM_FreeSpecificedIndexMessageInCcQueue(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT8                           ucCacheMsgNum;
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstCachedMsgInfo = VOS_NULL_PTR;

    /* get the specified index message address */
    pstCachedMsgInfo = TAF_SPM_GetSpecifiedIndexMessageAddrFromCcQueue(ucIndex);

    /* get the cached message number */
    ucCacheMsgNum = TAF_SPM_GetCcMsgQueueNum();

    if (0 < ucCacheMsgNum)
    {
        /* update the cached message number */
        ucCacheMsgNum--;
        TAF_SPM_SetCcMsgQueueNum(ucCacheMsgNum);

        /* by the way, move the cached messages forward */
        (VOS_VOID)PS_MEM_MOVE(pstCachedMsgInfo,
                    (pstCachedMsgInfo+1),
                    (ucCacheMsgNum - ucIndex) * sizeof(TAF_SPM_CACHE_MSG_INFO_STRU));

        PS_MEM_SET((pstCachedMsgInfo + ucCacheMsgNum), 0, sizeof(TAF_SPM_CACHE_MSG_INFO_STRU));
    }
}


VOS_UINT8 TAF_SPM_GetSmsMsgQueueNum(VOS_VOID)
{
    return (TAF_SPM_GetBufferMsgQueueAddr()->stSmsMsgQueue.ucCacheMsgNum);
}


VOS_VOID TAF_SPM_SetSmsMsgQueueNum(VOS_UINT8 ucCacheMsgNum)
{
    TAF_SPM_GetBufferMsgQueueAddr()->stSmsMsgQueue.ucCacheMsgNum = ucCacheMsgNum;
}


VOS_UINT8 TAF_SPM_IsSmsMsgQueueFull(VOS_VOID)
{
    return (VOS_UINT8)((TAF_SPM_MAX_SMS_MSG_QUEUE_NUM == TAF_SPM_GetSmsMsgQueueNum())? VOS_TRUE : VOS_FALSE);
}


TAF_SPM_CACHE_MSG_INFO_STRU *TAF_SPM_GetSpecifiedIndexMessageAddrFromSmsQueue(
    VOS_UINT8                           ucIndex
)
{
    return &(TAF_SPM_GetBufferMsgQueueAddr()->stSmsMsgQueue.astMsgQueue[ucIndex]);
}


VOS_UINT32 TAF_SPM_PutMessageToSmsQueue(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstCacheMsgInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucCacheMsgNum;

    /* check the incoming message length */
    if (TAF_SPM_MAX_MSG_BUFFER_LEN < (pstMsg->ulLength + VOS_MSG_HEAD_LENGTH))
    {
        return VOS_FALSE;
    }

    /* get the number of cached message */
    ucCacheMsgNum   = TAF_SPM_GetSmsMsgQueueNum();

    if (ucCacheMsgNum >= TAF_SPM_MAX_SMS_MSG_QUEUE_NUM)
    {
        return VOS_FALSE;
    }

    /* get address of free message queue */
    pstCacheMsgInfo = TAF_SPM_GetSpecifiedIndexMessageAddrFromSmsQueue(ucCacheMsgNum);

    /* cache message */
    pstCacheMsgInfo->stMsgEntry.ulEventType = ulEventType;
    PS_MEM_CPY(&(pstCacheMsgInfo->stMsgEntry.aucEntryMsgBuffer[0]), pstMsg, pstMsg->ulLength + VOS_MSG_HEAD_LENGTH);

    /* update number of cached messages */
    ucCacheMsgNum++;
    TAF_SPM_SetSmsMsgQueueNum(ucCacheMsgNum);

    return (VOS_TRUE);
}


/*lint -save -e958 */

VOS_VOID TAF_SPM_FreeSpecificedIndexMessageInSmsQueue(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT8                           ucCacheMsgNum;
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstCachedMsgInfo = VOS_NULL_PTR;

    /* get the first cached message in queue */
    pstCachedMsgInfo = TAF_SPM_GetSpecifiedIndexMessageAddrFromSmsQueue(ucIndex);

    /* get the cached message number */
    ucCacheMsgNum = TAF_SPM_GetSmsMsgQueueNum();

    if (0 < ucCacheMsgNum)
    {
        /* update the cached message number */
        ucCacheMsgNum--;
        TAF_SPM_SetSmsMsgQueueNum(ucCacheMsgNum);

        /* by the way, move the cached messages forward */
        (VOS_VOID)PS_MEM_MOVE(pstCachedMsgInfo,
                    (pstCachedMsgInfo+1),
                    (ucCacheMsgNum - ucIndex) * sizeof(TAF_SPM_CACHE_MSG_INFO_STRU));

        PS_MEM_SET((pstCachedMsgInfo + ucCacheMsgNum), 0, sizeof(TAF_SPM_CACHE_MSG_INFO_STRU));
    }
}
/*lint -restore */



VOS_UINT8 TAF_SPM_GetSsMsgQueueNum(VOS_VOID)
{
    return (TAF_SPM_GetBufferMsgQueueAddr()->stSsMsgQueue.ucCacheMsgNum);
}


VOS_VOID TAF_SPM_SetSsMsgQueueNum(VOS_UINT8 ucCacheMsgNum)
{
    TAF_SPM_GetBufferMsgQueueAddr()->stSsMsgQueue.ucCacheMsgNum = ucCacheMsgNum;
}


VOS_UINT8 TAF_SPM_IsSsMsgQueueFull(VOS_VOID)
{
    return (VOS_UINT8)((TAF_SPM_MAX_SS_MSG_QUEUE_NUM == TAF_SPM_GetSsMsgQueueNum())? VOS_TRUE : VOS_FALSE);
}


TAF_SPM_CACHE_MSG_INFO_STRU *TAF_SPM_GetSpecifiedIndexMessageAddrFromSsQueue(
    VOS_UINT8                           ucIndex
)
{
    return &(TAF_SPM_GetBufferMsgQueueAddr()->stSsMsgQueue.astMsgQueue[ucIndex]);
}


VOS_UINT32 TAF_SPM_PutMessageToSsQueue(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstCacheMsgInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucCacheMsgNum;

    /* check the incoming message length */
    if (TAF_SPM_MAX_MSG_BUFFER_LEN < (pstMsg->ulLength + VOS_MSG_HEAD_LENGTH))
    {
        return VOS_FALSE;
    }

    /* get the number of cached message */
    ucCacheMsgNum   = TAF_SPM_GetSsMsgQueueNum();

    if (ucCacheMsgNum >= TAF_SPM_MAX_SS_MSG_QUEUE_NUM)
    {
        return VOS_FALSE;
    }
    /* get address of free message queue */
    pstCacheMsgInfo = TAF_SPM_GetSpecifiedIndexMessageAddrFromSsQueue(ucCacheMsgNum);

    /* cache message */
    pstCacheMsgInfo->stMsgEntry.ulEventType = ulEventType;
    PS_MEM_CPY(&(pstCacheMsgInfo->stMsgEntry.aucEntryMsgBuffer[0]), pstMsg, pstMsg->ulLength + VOS_MSG_HEAD_LENGTH);

    /* update number of cached messages */
    ucCacheMsgNum++;
    TAF_SPM_SetSsMsgQueueNum(ucCacheMsgNum);

    return (VOS_TRUE);
}

/*lint -save -e958 */

VOS_VOID TAF_SPM_FreeSpecificedIndexMessageInSsQueue(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT8                           ucCacheMsgNum;
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstCachedMsgInfo = VOS_NULL_PTR;

    /* get the first cached message in queue */
    pstCachedMsgInfo = TAF_SPM_GetSpecifiedIndexMessageAddrFromSsQueue(ucIndex);

    /* get the cached message number */
    ucCacheMsgNum = TAF_SPM_GetSsMsgQueueNum();

    if (0 < ucCacheMsgNum)
    {
        /* update the cached message number */
        ucCacheMsgNum--;
        TAF_SPM_SetSsMsgQueueNum(ucCacheMsgNum);

        /* by the way, move the cached messages forward */
        (VOS_VOID)PS_MEM_MOVE(pstCachedMsgInfo,
                    (pstCachedMsgInfo+1),
                    (ucCacheMsgNum - ucIndex) * sizeof(TAF_SPM_CACHE_MSG_INFO_STRU));

        PS_MEM_SET((pstCachedMsgInfo + ucCacheMsgNum), 0, sizeof(TAF_SPM_CACHE_MSG_INFO_STRU));
    }
}
/*lint -restore */

#if (FEATURE_IMS == FEATURE_ON)

TAF_SPM_REDIAL_MSG_CTX_STRU *TAF_SPM_GetRedialMsgQueueAddr(VOS_VOID)
{
    return &(TAF_SPM_GetSpmCtxAddr()->stDomainSelCtx.stRedialMsgQueue);
}


VOS_VOID TAF_SPM_InitCallRedialBuffer(
    TAF_SPM_CC_REDIAL_QUEUE_STRU       *pstCallRedialQueue
)
{
    PS_MEM_SET(pstCallRedialQueue, 0, sizeof(TAF_SPM_CC_REDIAL_QUEUE_STRU));
}


VOS_UINT8 TAF_SPM_GetNumberOfCallRedialBuffer(VOS_VOID)
{
    return (TAF_SPM_GetRedialMsgQueueAddr()->stCcMsgQueue.ucCacheMsgNum);
}


VOS_UINT8 TAF_SPM_IsCallRedialBufferEmpty(VOS_VOID)
{
    return (VOS_UINT8)((0 == TAF_SPM_GetNumberOfCallRedialBuffer())? VOS_TRUE : VOS_FALSE);
}


VOS_UINT8 TAF_SPM_IsCallRedialBufferFull(VOS_VOID)
{
    return (VOS_UINT8)((TAF_SPM_MAX_CC_REDIAL_QUEUE_NUM == TAF_SPM_GetNumberOfCallRedialBuffer())? VOS_TRUE : VOS_FALSE);
}


VOS_VOID TAF_SPM_SetNumberOfCallRedialBuffer(VOS_UINT8 ucCacheMsgNum)
{
    TAF_SPM_GetRedialMsgQueueAddr()->stCcMsgQueue.ucCacheMsgNum = ucCacheMsgNum;
}


TAF_SPM_ENTRY_MSG_STRU *TAF_SPM_GetSpecificedIndexFromCallRedialBuffer(VOS_UINT8 ucIndex)
{
    return &(TAF_SPM_GetRedialMsgQueueAddr()->stCcMsgQueue.astMsgQueue[ucIndex]);
}


VOS_UINT32 TAF_SPM_PutMsgIntoCallRedialBuffer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_ENTRY_MSG_STRU             *pstCacheMsgInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucCacheMsgNum;

    /* 检查消息长度，避免越界 */
    if (TAF_SPM_MAX_MSG_BUFFER_LEN < (pstMsg->ulLength + VOS_MSG_HEAD_LENGTH))
    {
        return VOS_FALSE;
    }

    /* 获取重拨呼叫缓存数目 */
    ucCacheMsgNum   = TAF_SPM_GetNumberOfCallRedialBuffer();

    /* 获取指定重拨缓存地址 */
    pstCacheMsgInfo = TAF_SPM_GetSpecificedIndexFromCallRedialBuffer(ucCacheMsgNum);

    /* 缓存消息 */
    pstCacheMsgInfo->ulEventType = ulEventType;
    PS_MEM_CPY(&(pstCacheMsgInfo->aucEntryMsgBuffer[0]),
               pstMsg,
               pstMsg->ulLength + VOS_MSG_HEAD_LENGTH);

    /* update number of cached messages */
    ucCacheMsgNum++;
    TAF_SPM_SetNumberOfCallRedialBuffer(ucCacheMsgNum);

    return (VOS_TRUE);
}


VOS_VOID TAF_SPM_FreeSpecificedIndexCallRedialBuffer(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucCacheMsgNum;
    TAF_SPM_ENTRY_MSG_STRU             *pstCachedMsgInfo = VOS_NULL_PTR;

    /* get the specified index message address */
    pstCachedMsgInfo = TAF_SPM_GetSpecificedIndexFromCallRedialBuffer(ucIndex);

    /* get the cached message number */
    ucCacheMsgNum = TAF_SPM_GetNumberOfCallRedialBuffer();

    if (0 < ucCacheMsgNum)
    {
        /* update the cached message number */
        ucCacheMsgNum--;
        TAF_SPM_SetNumberOfCallRedialBuffer(ucCacheMsgNum);

        /* by the way, move the cached messages forward */
        (VOS_VOID)PS_MEM_MOVE(pstCachedMsgInfo,
                    (pstCachedMsgInfo+1),
                    (ucCacheMsgNum - ucIndex) * sizeof(TAF_SPM_ENTRY_MSG_STRU));

        PS_MEM_SET((pstCachedMsgInfo + ucCacheMsgNum), 0, sizeof(TAF_SPM_ENTRY_MSG_STRU));
    }
}


VOS_VOID TAF_SPM_InitSmsRedialBuffer(
    TAF_SPM_SMS_REDIAL_QUEUE_STRU      *pstSmsRedialQueue
)
{
    PS_MEM_SET(pstSmsRedialQueue, 0, sizeof(TAF_SPM_SMS_REDIAL_QUEUE_STRU));
}


VOS_UINT8 TAF_SPM_GetNumberOfSmsRedialBuffer(VOS_VOID)
{
    return (TAF_SPM_GetRedialMsgQueueAddr()->stSmsMsgQueue.ucCacheMsgNum);
}


VOS_VOID TAF_SPM_SetNumberOfSmsRedialBuffer(VOS_UINT8 ucCacheMsgNum)
{
    TAF_SPM_GetRedialMsgQueueAddr()->stSmsMsgQueue.ucCacheMsgNum = ucCacheMsgNum;
}


VOS_UINT8 TAF_SPM_IsSmsRedialBufferEmpty(VOS_VOID)
{
    return (VOS_UINT8)((0 == TAF_SPM_GetNumberOfSmsRedialBuffer())? VOS_TRUE : VOS_FALSE);
}


VOS_UINT8 TAF_SPM_IsSmsRedialBufferFull(VOS_VOID)
{
    return (VOS_UINT8)((TAF_SPM_MAX_SMS_REDIAL_QUEUE_NUM == TAF_SPM_GetNumberOfSmsRedialBuffer())? VOS_TRUE : VOS_FALSE);
}


TAF_SPM_ENTRY_MSG_STRU *TAF_SPM_GetSpecificedIndexFromSmsRedialBuffer(VOS_UINT8 ucIndex)
{
    return &(TAF_SPM_GetRedialMsgQueueAddr()->stSmsMsgQueue.astMsgQueue[ucIndex]);
}


VOS_UINT32 TAF_SPM_PutMsgIntoSmsRedialBuffer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_ENTRY_MSG_STRU             *pstCacheMsgInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucCacheMsgNum;

    /* 检查消息长度，避免越界 */
    if (TAF_SPM_MAX_MSG_BUFFER_LEN < (pstMsg->ulLength + VOS_MSG_HEAD_LENGTH))
    {
        return VOS_FALSE;
    }

    /* 获取重拨呼叫缓存数目 */
    ucCacheMsgNum   = TAF_SPM_GetNumberOfSmsRedialBuffer();
    if (ucCacheMsgNum >= TAF_SPM_MAX_SMS_REDIAL_QUEUE_NUM)
    {
        return VOS_FALSE;
    }
    /* 获取指定重拨缓存地址 */
    pstCacheMsgInfo = TAF_SPM_GetSpecificedIndexFromSmsRedialBuffer(ucCacheMsgNum);

    /* 缓存消息 */
    pstCacheMsgInfo->ulEventType = ulEventType;
    PS_MEM_CPY(&(pstCacheMsgInfo->aucEntryMsgBuffer[0]),
               pstMsg,
               pstMsg->ulLength + VOS_MSG_HEAD_LENGTH);

    /* update number of cached messages */
    ucCacheMsgNum++;
    TAF_SPM_SetNumberOfSmsRedialBuffer(ucCacheMsgNum);

    return (VOS_TRUE);
}


VOS_VOID TAF_SPM_FreeSpecificedIndexSmsRedialBuffer(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucCacheMsgNum;
    TAF_SPM_ENTRY_MSG_STRU             *pstCachedMsgInfo = VOS_NULL_PTR;

    /* get the specified index message address */
    pstCachedMsgInfo = TAF_SPM_GetSpecificedIndexFromSmsRedialBuffer(ucIndex);

    /* get the cached message number */
    ucCacheMsgNum = TAF_SPM_GetNumberOfSmsRedialBuffer();

    if (0 < ucCacheMsgNum)
    {
        /* update the cached message number */
        ucCacheMsgNum--;
        TAF_SPM_SetNumberOfSmsRedialBuffer(ucCacheMsgNum);

        /* by the way, move the cached messages forward */
        (VOS_VOID)PS_MEM_MOVE(pstCachedMsgInfo,
                    (pstCachedMsgInfo+1),
                    (ucCacheMsgNum - ucIndex) * sizeof(TAF_SPM_ENTRY_MSG_STRU));

        PS_MEM_SET((pstCachedMsgInfo + ucCacheMsgNum), 0, sizeof(TAF_SPM_ENTRY_MSG_STRU));
    }
}

/*lint -restore */


TAF_SPM_CALL_ECONF_INFO_STRU* TAF_SPM_GetCallEconfInfoAddr(VOS_VOID)
{
    return &(TAF_SPM_GetSpmCtxAddr()->stEconfInfo);
}


VOS_VOID TAF_SPM_InitEconfInfo(VOS_VOID)
{
    TAF_SPM_CALL_ECONF_INFO_STRU       *pstCallEconfAddr = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;

    pstCallEconfAddr = TAF_SPM_GetCallEconfInfoAddr();

    PS_MEM_SET(pstCallEconfAddr, 0x0, sizeof(TAF_SPM_CALL_ECONF_INFO_STRU));

    for (ulIndex = 0; ulIndex < TAF_CALL_MAX_ECONF_CALLED_NUM; ulIndex++)
    {
        pstCallEconfAddr->astEconfCheckInfo[ulIndex].enCheckRslt    = TAF_CS_CAUSE_SUCCESS;
        pstCallEconfAddr->astEconfCheckInfo[ulIndex].ulCheckCnfFlag = VOS_FALSE;
    }

    return;
}


VOS_UINT32 TAF_SPM_GetEventTypeFromCurrEntityFsmEntryMsg(VOS_VOID)
{
    MN_APP_REQ_MSG_STRU                *pstAppMsg   = VOS_NULL_PTR;
    TAF_SPM_ENTRY_MSG_STRU             *pstEntryMsg = VOS_NULL_PTR;

    pstEntryMsg         = TAF_SPM_GetCurrEntityFsmEntryMsgAddr();
    pstAppMsg           = (MN_APP_REQ_MSG_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    return TAF_BuildEventType(pstAppMsg->ulSenderPid, pstAppMsg->usMsgName);
}


VOS_VOID  TAF_SPM_SetEcallHangUpImsFlag(
    VOS_UINT8                           ucFlag
)
{
    TAF_SPM_GetSpmCtxAddr()->ucEcallHangUpImsFlag = ucFlag;
}


VOS_UINT8 TAF_SPM_GetEcallHangUpImsFlag(VOS_VOID)
{
    return TAF_SPM_GetSpmCtxAddr()->ucEcallHangUpImsFlag;
}




#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

