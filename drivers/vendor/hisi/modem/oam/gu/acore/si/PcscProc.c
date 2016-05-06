

/************************************************************************
Copyright   : 2005-2008, Huawei Tech. Co., Ltd.
File name   : PcscProc.c
Author      : w00184875
Version     : V300R002
Date        : 2011-09-19
Description : 该文件定义了ACPU上PCSC流程实现
History     :

1.日    期  : 2011年9月19日
  作    者  : w00184875
  修改内容  : Create
************************************************************************/
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

/*****************************************************************************
函 数 名  :PCSC_AcpuCmdReq
功能描述  :PCSC请求
输入参数  :ulCmdType:命令类型
           pucAPDU  :APDU命令内容
           ulAPDULen:APDU命令长度
输出参数  :无
返 回 值  :VOS_OK
           VOS_ERR
修订记录  :
1. 日    期   : 2010年3月5日
   作    者   : h59254
   修改内容   : Creat
2. 日    期   : 2011年10月10日
   作    者   : w00184875
   修改内容   : 从CCPU移植过来
*****************************************************************************/
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

/*****************************************************************************
函 数 名  :PCSC_GetCardStatus
功能描述  :卡状态接口
输入参数  :无
输出参数  :无
返 回 值  :VOS_OK - 有卡
           VOS_ERROR - 无卡
修订记录  :
1. 日    期   : 2010年10月10日
   作    者   : w00184875
   修改内容   : Creat
*****************************************************************************/
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


/*****************************************************************************
函 数 名  :PCSC_UpdateCardStatus
功能描述  :收到CCPU发送来的卡状态更新消息处理函数
输入参数  :pstMsg:消息体
输出参数  :无
返 回 值  :VOS_VOID
修订记录  :
1. 日    期   : 2011年10月10日
   作    者   : w00184875
   修改内容   : Creat
*****************************************************************************/
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

/*****************************************************************************
函 数 名  :PCSC_AcpuMsgProc
功能描述  :PCSC消息处理函数
输入参数  :pMsg:消息体
输出参数  :无
返 回 值  :VOS_VOID
修订记录  :
1. 日    期   : 2010年10月10日
   作    者   : w00184875
   修改内容   : Creat
*****************************************************************************/
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

/*****************************************************************************
函 数 名  :TestSendPcscCmd
功能描述  :打桩测试双核PCSC命令
输入参数  :
输出参数  :无
返 回 值  :VOS_VOID
修订记录  :
1. 日    期   : 2010年10月15日
   作    者   : w00184875
   修改内容   : Creat
*****************************************************************************/
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

