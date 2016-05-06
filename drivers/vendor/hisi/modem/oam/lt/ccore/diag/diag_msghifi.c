

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#include "diag_msghifi.h"
#include "diag_debug.h"
#include "diag_common.h"

#define    THIS_FILE_ID        MSP_FILE_ID_DIAG_MSGHIFI_C


/*****************************************************************************
 Function Name   : diag_HifiMsgProc
 Description     : HIFI命令直接透传消息给HIFI，并由MSP代替回复
 Input           : VOS_UINT8* pstReq
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.c00326366      2015-06-14  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_HifiMsgProc(DIAG_FRAME_INFO_STRU* pstReq)
{
    VOS_UINT32 ulRet                    = ERR_MSP_SUCCESS;
    DIAG_COMM_CNF_STRU stHifiCnf        = {0};
    MSP_DIAG_CNF_INFO_STRU stDiagInfo   = {0};
    
#if(VOS_OS_VER == VOS_LINUX)
    VOS_UINT32 ulLen;
    DIAG_HIFI_MSG_A_TRANS_C_STRU *pstInfo;
#else
    DIAG_OSA_MSG_STRU *pstMsg           = NULL;
    DIAG_OSA_MSG_STRU *pstVosMsg        = NULL;
#endif

#if(VOS_OS_VER == VOS_LINUX)
    ulLen = sizeof(DIAG_HIFI_MSG_A_TRANS_C_STRU) - VOS_MSG_HEAD_LENGTH + pstReq->ulMsgLen;
    pstInfo = (DIAG_HIFI_MSG_A_TRANS_C_STRU*)VOS_AllocMsg(MSP_PID_DIAG_APP_AGENT, ulLen);
    if(VOS_NULL == pstInfo)
    {
        ulRet = ERR_MSP_MALLOC_FAILUE;
        goto DIAG_ERROR;
    }
    
    pstInfo->ulReceiverPid = MSP_PID_DIAG_AGENT;
    pstInfo->ulSenderPid   = MSP_PID_DIAG_APP_AGENT;
    pstInfo->ulMsgId       = DIAG_MSG_HIFI_A_TRANS_C_REQ;
    
    ulLen = sizeof(DIAG_FRAME_INFO_STRU) + pstReq->ulMsgLen;
    (VOS_VOID)VOS_MemCpy(&pstInfo->stInfo, pstReq, ulLen);
    
    vos_printf("acore send msg to ccore.\n");

    ulRet = VOS_SendMsg(MSP_PID_DIAG_APP_AGENT, pstInfo);
    if(ulRet)
    {
        goto DIAG_ERROR;
    }

    return ulRet;
#else

    pstMsg = (DIAG_OSA_MSG_STRU *)(pstReq->aucData + sizeof(MSP_DIAG_DATA_REQ_STRU));

    pstVosMsg = (DIAG_OSA_MSG_STRU *)VOS_AllocMsg(MSP_PID_DIAG_AGENT, pstMsg->ulLength);

    if (pstVosMsg != NULL)
    {
        pstVosMsg->ulReceiverPid  = pstMsg->ulReceiverPid;

        (VOS_VOID)VOS_MemCpy(&pstVosMsg->ulMsgId, &pstMsg->ulMsgId, pstMsg->ulLength);

        ulRet = VOS_SendMsg(MSP_PID_DIAG_AGENT, pstVosMsg);
        if (ulRet != VOS_OK)
        {
            diag_printf("diag_debug_write VOS_SendMsg failed!\n");
            goto DIAG_ERROR;
        }
    }

#endif
    
DIAG_ERROR:

    stHifiCnf.ulRet  = ulRet;
    DIAG_MSG_COMMON_PROC(stDiagInfo, stHifiCnf, pstReq);

    stDiagInfo.ulMsgType = pstReq->stID.pri4b;

    /*组包回复*/
    ulRet = DIAG_MsgReport(&stDiagInfo, &stHifiCnf, sizeof(stHifiCnf));

    return ulRet;
}

#if(VOS_OS_VER == VOS_LINUX)

/*****************************************************************************
 Function Name   : diag_HifiMsgInit
 Description     : MSG HIFI部分初始化
 Input           : None
 Output          : None
 Return          : None
 History         :

*****************************************************************************/
VOS_VOID diag_HifiMsgInit(VOS_VOID)
{
    /*注册message消息回调*/
    DIAG_MsgProcReg(DIAG_MSG_TYPE_AUDIO, diag_HifiMsgProc);
}

#else

/*****************************************************************************
 Function Name   : diag_AppTransPhyProc
 Description     : A核发过来的phy诊断命令处理
 Input           : pMsgBlock    诊断命令请求的内容
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.c64416      2014-11-18  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_AppTransHifiProc(MsgBlock* pMsgBlock)
{
    DIAG_HIFI_MSG_A_TRANS_C_STRU *pstInfo;

    pstInfo = (DIAG_HIFI_MSG_A_TRANS_C_STRU *)pMsgBlock;

    return diag_HifiMsgProc(&pstInfo->stInfo);
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

