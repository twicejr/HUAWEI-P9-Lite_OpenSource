

/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名      : Om.c
  版 本 号      : 初稿
  作    者      : 甘兰47350
  生成日期      : 2008年5月3日
  最近修改      :
  功能描述      : 该C文件给出了OM模块的实现
  函数列表      :
  修改历史      :
  1.日    期    : 2008年5月3日
    作    者    : 甘兰47350
    修改内容    : 创建文件

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "NVIM_Interface.h"
#include "TafNvInterface.h"
#include "SCMProc.h"
#include "SCMSoftDecode.h"
#include "cbtapprl.h"
#include "msp_errno.h"
#include "diag_api.h"
#include "CbtPpm.h"


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif


/*lint -e767 修改人：甘兰47350；检视人：李霄46160；原因简述：LOG方案设计需要*/
#define    THIS_FILE_ID        PS_FILE_ID_APP_CBT_FUNC_C


extern VOS_UINT32                       g_ulCbtMsgSN;
extern CBT_RCV_CHAN_CTRL_INFO_STRU      g_stAcpuCbtCtrlInfo;

extern VOS_UINT32 OM_IsAcpuAuthNv(VOS_UINT16 usNvId);

/*****************************************************************************
 Prototype       : OM_ReadNv
 Description     : Read the NV by NV ID and return the content.
                   APP->OM:
                    struct
                    {
                         ulCount               32         要读取的NV项个数
                         ausNvItemId[n]     n*16          要读取的NV项ID数组，其中n= usCount
                    }
                   OM->APP:
                    struct
                    {
                         ulErrorCode           32
                         ulCount               32       返回的NV项个数
                         NvItem1Id         16       第一项NV的Id编号
                         NvItem1Len        16       第一项NV的长度，以Byte为单位
                         NvItem1Data[n1]       n1*16    第一项NV的数据
                    }
 Input           : pstAppToOmMsg  - The input msg received from APP side.
                   usReturnPrimId - The value of the returned PrimId.
 Output          : None.
 Return Value    : VOS_OK  - Success.
                   VOS_ERR - Failure.


 History         : ---
    Date         : 2015-02-27
    Author       : x00263027
    Modification : Created function
 *****************************************************************************/
VOS_UINT32 CBT_AcpuReadNv(CBT_UNIFORM_MSG_STRU *pstAppToCbtMsg, VOS_UINT16 usReturnPrimId)
{
    CBT_UNIFORM_MSG_STRU               *pstCbtToAppMsg;
    CBT_READ_NV_REQ_STRU               *pstAppToCbtReadNv;
    CBT_READ_NV_IND_STRU               *pstCbtToAppReadNv;
    CBT_READ_NV_CNF_STRU                stCbtReadNvCnf;
    VOS_UINT16                         *pusCbtToAppPara;
    VOS_UINT32                          ulCount;
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulTotalSize = 0;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usNvId;
    VOS_UINT32                          ulNvLen;

    pstAppToCbtReadNv = (CBT_READ_NV_REQ_STRU *)(pstAppToCbtMsg->aucPara);
    ulCount = pstAppToCbtReadNv->ulCount;

    /*Get the total length of all NV items.*/
    for (ulIndex = 0; ulIndex < ulCount; ulIndex++)
    {
        usNvId = pstAppToCbtReadNv->ausNvItemId[ulIndex];
        ulResult = NV_GetLength(usNvId, &ulNvLen);
        if (VOS_OK != ulResult)
        {
            stCbtReadNvCnf.ulErrorCode = ulResult;
            stCbtReadNvCnf.ulErrNvId   = (VOS_UINT32)usNvId;
            stCbtReadNvCnf.ulCount     = ulCount;
            stCbtReadNvCnf.ulMsgLength = CBT_READ_NV_HEAD_SIZE;
            CBT_AcpuSendContentChannel(pstAppToCbtMsg->stMsgHeader.stModemSsid, pstAppToCbtMsg->stCompMode, usReturnPrimId, (CBT_UNIFORM_MSG_STRU *)&stCbtReadNvCnf);

            return ulResult;
        }
        ulTotalSize += ulNvLen;
    }

    /*Allocate the memory space.*/
    ulTotalSize += CBT_MSG_HEAD_EX_LENGTH + CBT_READ_NV_HEAD_SIZE + (ulCount*CBT_NV_ITEM_SIZE);
    pstCbtToAppMsg = (CBT_UNIFORM_MSG_STRU *)VOS_AssistantMemAlloc(ACPU_PID_CBT,
                                                   DYNAMIC_MEM_PT, ulTotalSize);
    if (VOS_NULL_PTR == pstCbtToAppMsg)
    {
        CBT_AcpuSendResultChannel(pstAppToCbtMsg->stMsgHeader.stModemSsid, pstAppToCbtMsg->stCompMode, usReturnPrimId, VOS_ERR);

        return VOS_ERR;
    }
    /*Assign the return value and the count to struct's fields.*/
    pstCbtToAppReadNv = (CBT_READ_NV_IND_STRU *)(pstCbtToAppMsg->aucPara);
    pstCbtToAppReadNv->ulErrorCode = VOS_OK;
    pstCbtToAppReadNv->ulErrNvId   = 0;
    pstCbtToAppReadNv->ulCount     = ulCount;

    pusCbtToAppPara = (VOS_UINT16*)(pstCbtToAppReadNv->ausNVItemData);
    /*Read the NV content by the NV Id.*/
    for(ulIndex = 0; ulIndex < ulCount; ulIndex++)
    {
        usNvId = pstAppToCbtReadNv->ausNvItemId[ulIndex];
        ulResult = NV_GetLength(usNvId, &ulNvLen);
        if (VOS_OK != ulResult)
        {
            stCbtReadNvCnf.ulErrorCode = ulResult;
            stCbtReadNvCnf.ulErrNvId   = (VOS_UINT32)usNvId;
            stCbtReadNvCnf.ulCount     = ulCount;
            stCbtReadNvCnf.ulMsgLength = CBT_READ_NV_HEAD_SIZE;
            CBT_AcpuSendContentChannel(pstAppToCbtMsg->stMsgHeader.stModemSsid, pstAppToCbtMsg->stCompMode, usReturnPrimId, (CBT_UNIFORM_MSG_STRU *)&stCbtReadNvCnf);
            /*lint -e534*/
            VOS_MemFree(ACPU_PID_CBT, pstCbtToAppMsg);
            /*lint +e534*/

            return ulResult;
        }

        *pusCbtToAppPara = usNvId;
        pusCbtToAppPara++;
        *pusCbtToAppPara = (VOS_UINT16)ulNvLen;
        pusCbtToAppPara++;

        ulResult = NV_ReadEx(pstAppToCbtMsg->stMsgHeader.stModemSsid.ucModem,
                            usNvId, pusCbtToAppPara, ulNvLen);
        if (NV_OK != ulResult)
        {
            stCbtReadNvCnf.ulErrorCode    = ulResult;
            stCbtReadNvCnf.ulErrNvId      = (VOS_UINT32)usNvId;
            stCbtReadNvCnf.ulCount        = ulCount;
            stCbtReadNvCnf.ulMsgLength    = CBT_READ_NV_HEAD_SIZE;
            CBT_AcpuSendContentChannel(pstAppToCbtMsg->stMsgHeader.stModemSsid, pstAppToCbtMsg->stCompMode, usReturnPrimId, (CBT_UNIFORM_MSG_STRU *)&stCbtReadNvCnf);
            /*lint -e534*/
            VOS_MemFree(ACPU_PID_CBT, pstCbtToAppMsg);
            /*lint +e534*/

            return ulResult;
        }
        pusCbtToAppPara += ulNvLen/sizeof(VOS_UINT16);
    }

    pstCbtToAppMsg->ulMsgLength = ulTotalSize - CBT_MSG_HEAD_EX_LENGTH;
    CBT_AcpuSendContentChannel(pstAppToCbtMsg->stMsgHeader.stModemSsid, pstAppToCbtMsg->stCompMode, usReturnPrimId, pstCbtToAppMsg);
    /*lint -e534*/
    VOS_MemFree(ACPU_PID_CBT, pstCbtToAppMsg);
    /*lint +e534*/

    return VOS_OK;
}

/*****************************************************************************
 Prototype       : OM_WriteNv
 Description     :
                  APP->OM:
                  struct
                  {
                        ulCount 32             要读取的NV项个数
                        NvItem1Id   16         第一项NV的Id编号
                        NvItem1Len  16         第一项NV的长度，以Byte为单位
                        NvItem1Data[n1] n1*16  第一项NV的数据
                  }
                  OM->APP:
                  ulErrorCode   32      请参见"表65 UlErrorCode定义表"

 Input           : pstAppToOmMsg  - The input msg received from APP side.
                   usReturnPrimId - The value of the returned PrimId.
 Output          : None.
 Return Value    : VOS_OK  - Success.
                   VOS_ERR - Failure.

 History         : ---
    Date         : 2015-02-27
    Author       : x00263027
    Modification : Created function
 *****************************************************************************/
VOS_UINT32 CBT_AcpuWriteNv(CBT_UNIFORM_MSG_STRU *pstAppToCbtMsg, VOS_UINT16 usReturnPrimId)
{
    CBT_WRITE_NV_REQ_STRU   *pstAppCbtWriteNv;
    CBT_WRITE_NV_CNF_STRU    stCbtWriteNvCnf;
    VOS_UINT16              *pusAppToCbtPara;
    VOS_UINT32               ulCount;
    VOS_UINT32               ulIndex;
    VOS_UINT16               usNvId;
    VOS_UINT16               usNvLen;
    VOS_UINT32               ulResult;

    pstAppCbtWriteNv = (CBT_WRITE_NV_REQ_STRU *)(pstAppToCbtMsg->aucPara);
    /*Get the number of all NV Id.*/
    ulCount = pstAppCbtWriteNv->ulCount;

    pusAppToCbtPara = (VOS_UINT16*)(pstAppCbtWriteNv->ausNvItemData);
    /*Write the NV content by NV Id.*/
    for (ulIndex = 0; ulIndex < ulCount; ulIndex++)
    {
        usNvId  = *pusAppToCbtPara;
        pusAppToCbtPara++;
        usNvLen = *pusAppToCbtPara;
        pusAppToCbtPara++;

        ulResult = NV_WriteEx(pstAppToCbtMsg->stMsgHeader.stModemSsid.ucModem,
                                usNvId, pusAppToCbtPara, (VOS_UINT32)usNvLen);
        if(NV_OK != ulResult)
        {
            stCbtWriteNvCnf.ulErrorCode    = ulResult;
            stCbtWriteNvCnf.ulErrNvId      = (VOS_UINT16)usNvId;
            stCbtWriteNvCnf.ulMsgLength    = CBT_WRITE_NV_HEAD_SIZE;
            CBT_AcpuSendContentChannel(pstAppToCbtMsg->stMsgHeader.stModemSsid, pstAppToCbtMsg->stCompMode, \
                                usReturnPrimId, (CBT_UNIFORM_MSG_STRU *)&stCbtWriteNvCnf);

            return VOS_ERR;
        }
        /*由于返回的usNvLen以byte为单位，所以需要除以指针指向类型的大小*/
        pusAppToCbtPara += (usNvLen/sizeof(VOS_UINT16));
    }

    stCbtWriteNvCnf.ulErrorCode    = NV_OK;
    stCbtWriteNvCnf.ulErrNvId      = 0;
    stCbtWriteNvCnf.ulMsgLength    = CBT_WRITE_NV_HEAD_SIZE;
    CBT_AcpuSendContentChannel(pstAppToCbtMsg->stMsgHeader.stModemSsid, pstAppToCbtMsg->stCompMode, \
                        usReturnPrimId, (CBT_UNIFORM_MSG_STRU *)&stCbtWriteNvCnf);

    return VOS_OK;
}


VOS_UINT32 CBT_AcpuEstablishProc(CBT_UNIFORM_MSG_STRU * pstAppToCbtMsg)
{
    CBT_UNIFORM_MSG_STRU       *pstCbtToAppMsg;
    CBT_ESTABLISH_IND_STRU     *pstCbtToAppEstablish;

    MsgBlock                   *pMsg;
    VOS_UINT32                  ulTotalSize = 0;

    /* 先断开链路 */
    g_stAcpuCbtCtrlInfo.ulCbtSwitchOnOff = CBT_STATE_IDLE;
    g_ulCbtMsgSN                         = 0;

    /*Allocate the memory space.*/
    ulTotalSize = CBT_MSG_HEAD_EX_LENGTH + CBT_IND_RESULT_SIZE + CBT_EST_IND_RSV_LEN;
    pstCbtToAppMsg = (CBT_UNIFORM_MSG_STRU *)VOS_AssistantMemAlloc(ACPU_PID_CBT,
                                                   DYNAMIC_MEM_PT, ulTotalSize);
    if (VOS_NULL_PTR == pstCbtToAppMsg)
    {
        CBT_AcpuSendResultChannel(pstAppToCbtMsg->stMsgHeader.stModemSsid, pstAppToCbtMsg->stCompMode, OM_APP_ESTABLISH_CNF, VOS_ERR);
        return VOS_ERR;
    }

    pstCbtToAppEstablish = (CBT_ESTABLISH_IND_STRU *)pstCbtToAppMsg->aucPara;
    /* 以兼容校准工具，建链成功回复状态字0x02 */
    pstCbtToAppEstablish->ulResult = 0x0002;

    /*lint -e419 -e416 -e534 */
    VOS_MemSet(pstCbtToAppEstablish->ausReserve, 0, CBT_EST_IND_RSV_LEN);    /*预留字段，暂时赋值为全0*/
    /*lint +e419 +e416 +e534 */

    pstCbtToAppMsg->ulMsgLength = ulTotalSize - CBT_MSG_HEAD_EX_LENGTH;
    /* 给工具回复建链成功状态 */
    CBT_AcpuSendContentChannel(pstAppToCbtMsg->stMsgHeader.stModemSsid, pstAppToCbtMsg->stCompMode, OM_APP_ESTABLISH_CNF, pstCbtToAppMsg);

    if (VOS_OK != VOS_MemFree(ACPU_PID_CBT, pstCbtToAppMsg))
    {
    }

    /* 激活链路 */
    g_stAcpuCbtCtrlInfo.ulCbtSwitchOnOff = CBT_STATE_ACTIVE;

    /* 通知CCPU链路状态 */
    pMsg = (MsgBlock *)VOS_AllocMsg(PC_PID_TOOL, sizeof(CBT_UNIFORM_MSG_STRU));

    if (VOS_NULL_PTR == pMsg)
    {
        return VOS_ERR;
    }

    pMsg->ulReceiverPid      = CCPU_PID_CBT;

    /*lint -e419 -e416  */
    if (VOS_OK != VOS_MemCpy((VOS_VOID *)(pMsg->aucValue), (VOS_VOID *)pstAppToCbtMsg, pstAppToCbtMsg->ulMsgLength + CBT_MSG_HEAD_EX_LENGTH))
    {
    }
    /*lint +e419 +e416  */

    if (VOS_OK != VOS_SendMsg(PC_PID_TOOL, pMsg))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 CBT_AcpuReleaseProc(CBT_UNIFORM_MSG_STRU * pstAppToCbtMsg)
{
    MsgBlock                           *pMsg;

    g_stAcpuCbtCtrlInfo.ulCbtSwitchOnOff       = CBT_STATE_IDLE;

    pMsg = (MsgBlock *)VOS_AllocMsg(PC_PID_TOOL, sizeof(CBT_UNIFORM_MSG_STRU));

    if (VOS_NULL_PTR == pMsg)
    {
        return VOS_ERR;
    }

    pMsg->ulReceiverPid      = CCPU_PID_CBT;

    /*lint -e419 -e416 -e534 */
    VOS_MemCpy((VOS_VOID *)(pMsg->aucValue), (VOS_VOID *)pstAppToCbtMsg, sizeof(CBT_UNIFORM_MSG_STRU) );
    /*lint +e419 +e416 +e534 */

    if (VOS_OK != VOS_SendMsg(PC_PID_TOOL, pMsg))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 Prototype       : CBT_AppMsgProc
 Description     : Handle all messages sent to OM.
 Input           : pMsg -- The pointer of the msg.
 Output          : None
 Return Value    : VOS_VOID

 History         : ---
    Date         : 2008-03-20
    Author       : g47350
    Modification : Created function
 *****************************************************************************/
VOS_VOID CBT_AppMsgProc(MsgBlock* pMsg)
{
    CBT_CTOA_MSG_STRU           *pstCbtMsg;
    CBT_UNIFORM_MSG_STRU        *pstPcToCbtMsg;
    VOS_UINT16                   usMsgId;

    DIAG_TraceReport((VOS_VOID *)pMsg);

    if (PC_PID_TOOL == pMsg->ulSenderPid)
    {
        pstPcToCbtMsg = (CBT_UNIFORM_MSG_STRU *)pMsg->aucValue;
        usMsgId = pstPcToCbtMsg->usMsgId;

        switch (usMsgId)
        {
            case APP_OM_ESTABLISH_REQ:
                /*lint -e534*/
                CBT_AcpuEstablishProc(pstPcToCbtMsg);
                /*lint +e534*/
                break;

            case APP_OM_RELEASE_REQ:
                /*lint -e534*/
                CBT_AcpuReleaseProc(pstPcToCbtMsg);
                /*lint +e534*/
                break;

            case APP_OM_READ_NV_REQ:
                /*lint -e534*/
                CBT_AcpuReadNv(pstPcToCbtMsg, OM_APP_READ_NV_IND);
                /*lint +e534*/
                break;

            case APP_OM_WRITE_NV_REQ:
                /*lint -e534*/
                CBT_AcpuWriteNv(pstPcToCbtMsg, OM_APP_WRITE_NV_CNF);
                /*lint +e534*/
                break;

            default:
                CBT_AcpuSendResultChannel(pstPcToCbtMsg->stMsgHeader.stModemSsid, pstPcToCbtMsg->stCompMode, usMsgId, VOS_ERR);
                break;
        }
    }
    else if (CCPU_PID_CBT == pMsg->ulSenderPid)
    {
        pstCbtMsg = (CBT_CTOA_MSG_STRU *)pMsg;

        if (OM_CBT_SEND_DATA_REQ == pstCbtMsg->usPrimId)/* C核发过来的校准数据 */
        {
            /*lint -e534*/
            CBT_AcpuSendData((CBT_UNIFORM_MSG_STRU *)(pstCbtMsg->aucData), pstCbtMsg->usLen);
            /*lint +e534*/
            return;
        }
    }
    else
    {
    }

    return;
}


VOS_UINT32 CBT_AppPidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    switch( ip )
    {
        case VOS_IP_RESTART:
            CBTPPM_OamCbtPortInit();
            break;

        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 Prototype       : CBTAppFidInit
 Description     : OM' initializtion function
 Input           : None
 Output          : None
 Return Value    : VOS_UINT32

 History         : ---
    Date         : 2008-03-20
    Author       : g47350
    Modification : Created function
 *****************************************************************************/
VOS_UINT32 CBTAppFidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32 ulRslt;

    switch( ip )
    {
        case VOS_IP_LOAD_CONFIG:
        {

            ulRslt = VOS_RegisterPIDInfo(ACPU_PID_CBT,
                                        (Init_Fun_Type)CBT_AppPidInit,
                                        (Msg_Fun_Type)CBT_AppMsgProc);
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterMsgTaskPrio(ACPU_FID_CBT, VOS_PRIORITY_M2);
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }
            /*lint -e534*/
            CBT_AcpuInit();
            /*lint +e534*/
            /* CBT自处理任务创建 */
            if (VOS_OK != CBTSCM_SoftDecodeReqRcvTaskInit())
            {
                return VOS_ERR;
            }

            if (VOS_OK != CBTPPM_SocketTaskInit())
            {
                return VOS_ERR;
            }

            break;
        }

        default:
            break;
    }
    return VOS_OK;
}


#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif