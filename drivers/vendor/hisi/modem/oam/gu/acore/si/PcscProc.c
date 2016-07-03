


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "PcscProc.h"

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID PS_FILE_ID_PCSC_APP_PROC_C
/*lint +e767*/

/*ACPU上维护卡状态的全局变量*/
USIMM_CARD_SERVIC_ENUM_UINT32 g_enAcpuCardStatus = USIMM_CARD_SERVIC_BUTT;

extern VOS_VOID OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_ENUM_UINT32 enNumber, VOS_UINT32 ulSendPid, VOS_UINT32 ulRcvPid, VOS_UINT32 ulMsgName);
extern VOS_VOID OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_ENUM_UINT32 enNumber);


VOS_UINT32 PCSC_AcpuCmdReq(VOS_UINT32 ulCmdType, VOS_UINT8 *pucAPDU, VOS_UINT32 ulAPDULen)
{
    SI_PIH_PCSC_REQ_STRU     *pstMsg;

    if((ulAPDULen > 5)&&(pucAPDU[4] != ulAPDULen-5))
    {
        PS_LOG(ACPU_PID_PCSC, 0, PS_PRINT_ERROR, "PCSC_AcpuCmdReq: Data Len is Not Eq P3");
        return VOS_ERR;
    }

    pstMsg = (SI_PIH_PCSC_REQ_STRU *)VOS_AllocMsg(ACPU_PID_PCSC,
                        (sizeof(SI_PIH_PCSC_REQ_STRU) - VOS_MSG_HEAD_LENGTH) + ulAPDULen);
    if (VOS_NULL_PTR == pstMsg)
    {
        /* 打印错误 */
        PS_LOG(ACPU_PID_PCSC, 0, PS_PRINT_WARNING, "PCSC_AcpuCmdReq: VOS_AllocMsg is Failed");
        /*lint -e534*/
        vos_printf("PCSC_AcpuCmdReq: VOS_AllocMsg is Failed.\r\n");
        /*lint +e534*/

        return VOS_ERR; /* 返回函数错误信息 */
    }

    pstMsg->stMsgHeader.ulReceiverPid = MAPS_PIH_PID;
    pstMsg->stMsgHeader.ulMsgName     = SI_PIH_PCSC_DATA_REQ;
    pstMsg->stMsgHeader.ulEventType   = ulCmdType;
    pstMsg->stMsgHeader.usClient      = 0xFFFF;
    pstMsg->ulCmdType                 = ulCmdType;
    pstMsg->ulCmdLen                  = ulAPDULen;

    if(ulAPDULen != 0)
    {
        /*lint -e534*/
        VOS_MemCpy(pstMsg->aucAPDU, pucAPDU, ulAPDULen);
        /*lint +e534*/
    }

    if (VOS_OK != VOS_SendMsg(ACPU_PID_PCSC, pstMsg))
    {
        /*打印错误*/
        PS_LOG(ACPU_PID_PCSC, 0, PS_PRINT_WARNING, "PCSC_AcpuCmdReq: VOS_SendMsg is Failed.");
        /*lint -e534*/
        vos_printf("PCSC_AcpuCmdReq: VOS_SendMsg is Failed.");
        /*lint +e534*/
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_INT PCSC_AcpuGetCardStatus(VOS_VOID)
{
    if (USIMM_CARD_SERVIC_ABSENT == g_enAcpuCardStatus)
    {
        /*上报无卡状态*/
        return VOS_ERROR;
    }
    /*上报有卡状态*/
    return VOS_OK;
}



VOS_VOID PCSC_UpdateCardStatus(USIMM_CARDSTATUS_IND_STRU *pstMsg)
{
    if (USIMM_CARD_SERVIC_BUTT == g_enAcpuCardStatus)
    {
        /*lint -e534*/
        vos_printf("Reg PCSC Func.\r\n");
        /*lint +e534*/
    }

    /*更新本地卡状态的全局变量*/
    g_enAcpuCardStatus = pstMsg->stUsimSimInfo.enCardService;

    /*lint -e534*/
    vos_printf("Update Card Status: %d .\r\n", g_enAcpuCardStatus);
    /*lint +e534*/


    return;
}


VOS_VOID  PCSC_AcpuMsgProc( MsgBlock *pMsg)
{
    SI_PIH_PCSC_CNF_STRU *pstPCSCMsg;

    pstPCSCMsg = (SI_PIH_PCSC_CNF_STRU*)pMsg;

    OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, pMsg->ulSenderPid, ACPU_PID_PCSC, *((VOS_UINT32*)pMsg->aucValue));

    switch(pstPCSCMsg->ulMsgName)
    {
        case SI_PIH_PCSC_DATA_CNF:
            break;
        case USIMM_CARDSTATUS_IND:
            PCSC_UpdateCardStatus((USIMM_CARDSTATUS_IND_STRU *)pMsg);
            break;
        default:
            PS_LOG(ACPU_PID_PCSC, 0, PS_PRINT_WARNING, "PCSC_AcpuMsgProc: unknow MsgType");
            break;
    }

    OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

    return;
}


VOS_UINT32 TestSendPcscCmd(VOS_UINT32 ulCmdType)
{
    VOS_UINT8 aucApduData[5];

    aucApduData[4] = '\0';

    return PCSC_AcpuCmdReq(ulCmdType,aucApduData,5);
}

#ifdef __cplusplus
  #if __cplusplus
  }
  #endif
#endif

