/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : Aps_DealSndcpMsg.c
  Author       : 韩鲁峰
  Version      : V200R001
  Date         : 2005-0
  Description  :
  Function List:
        ---Aps_DealAllFromSndcp
        ---Aps_SnMsgModSnActRsp
        ---Aps_SnMsgModSnActRspParaCheck
        ---Aps_SnMsgModSnMdfRsp
        ---Aps_SnMsgModSnMdfRspParaCheck

        ---Aps_SnMsgModSnDeActRsp
        ---Aps_SnMsgModSnDeActRspParaCheck
        ---Aps_SnMsgModSnStatusReq
        ---Aps_SnMsgModSnStatusReqParaCheck
        ---Aps_FindSapiPdp

        ---Aps_FindSapiTransModePdp
        ---Aps_Nsapi2PdpId
        ---
  History      :
  1. Date:2005-10-30
     Author: 韩鲁峰
     Modification:Create
  2. 2006-02-23 modify by 韩鲁峰 FOR A32D02144
  3. 2006-02-28 modify by 韩鲁峰 for A32D02265

  4.日    期   : 2006年4月4日
    作    者   : liuyang id:48197
    修改内容   : 问题单号:A32D01738
  5.日    期   : 2006年7月6日
    作    者   : L47619
    修改内容   : 问题单号:A32D04774
************************************************************************/


/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "Taf_Aps.h"
#include "MnApsComm.h"
#include "TafApsMain.h"
#include "TafApsCtx.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e958*/

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APSDEALSNDCPMSG_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/


/*****************************************************************************
   2 全局变量定义
*****************************************************************************/


/*****************************************************************************
   3 函数实现
*****************************************************************************/


/*****************************************************************************
 Prototype      : Aps_SnMsgModSnActRspParaCheck()
 Description    : SNDCP的激活RSP和修改RSP的消息内容相同,故使用同一个函数来进行
                  参数检查.
 Input          : pSnActRsp
 Output         :
 Return Value   : #define APS_PARA_VALID                  0
                  #define APS_PARA_INVALID                1
 Data Access    :
 Data Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  Aps_SnMsgModSnActRspParaCheck( APS_SNDCP_ACTIVATE_RSP_ST* pSnActRsp)
{
    if ( pSnActRsp->XidParameter.ucMask & SN_XID_PARA_P_CMPR)
    {
        if ( !(APS_SN_P_CMP_VALID(pSnActRsp->XidParameter.ucPCmprAlgrth)) )
        {
            return  APS_PARA_INVALID;
        }
    }

    if ( pSnActRsp->XidParameter.ucMask & SN_XID_PARA_D_CMPR)
    {
        if ( !(APS_SN_H_CMP_VALID(pSnActRsp->XidParameter.ucDCmprAlgrth)) )
        {
            return  APS_PARA_INVALID;
        }
    }
    return  APS_PARA_VALID;

}

/*****************************************************************************
 Prototype      : Aps_SnActRspChngEntity()
 Description    : 收到SN_ACT_RSP后修改状态机参数,包括XID参数,TRANSMODE,状态
 Input          : pSnMdfRsp
 Output         : NO
 Return Value   :
 Data Access    :
 Data Update    :
 Calls          : Rabm_SetTransMode();
                  Aps_DealEntityTrans();
 Called By      : Aps_DealAllFromSndcp()
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID    Aps_SnActRspChngEntity(     APS_SNDCP_ACTIVATE_RSP_ST*  pSnActRsp,
                                        VOS_UINT8                   ucPdpId)
{
    RABM_TRANS_MODE_ENUM                TansMode;

    /*将传来的XID填入状态机*/
    if ( pSnActRsp->XidParameter.ucMask & SN_XID_PARA_P_CMPR)
    {
        g_PdpEntity[ucPdpId].PdpGprsParaFlag        = VOS_TRUE;
        g_PdpEntity[ucPdpId].GprsPara.Op_Xid_PCmp   = VOS_TRUE;
        g_PdpEntity[ucPdpId].GprsPara.ucPCmprAlgrth
                                        = pSnActRsp->XidParameter.ucPCmprAlgrth;
    }

    if ( pSnActRsp->XidParameter.ucMask & SN_XID_PARA_D_CMPR)
    {
        g_PdpEntity[ucPdpId].PdpGprsParaFlag        = VOS_TRUE;
        g_PdpEntity[ucPdpId].GprsPara.Op_Xid_DCmp   = VOS_TRUE;
        g_PdpEntity[ucPdpId].GprsPara.ucDCmprAlgrth
                                        = pSnActRsp->XidParameter.ucDCmprAlgrth;
    }

    Aps_DecideTransMode( ucPdpId, &TansMode );

    /*填写状态机中的TRANSMODE*/
    g_PdpEntity[ucPdpId].GprsPara.Op_TransMode  = VOS_TRUE;
    g_PdpEntity[ucPdpId].GprsPara.TransMode     = TansMode;

    return;
}

/*****************************************************************************
 Prototype      : Aps_SnMsgModSnMdfRsp()
 Description    : APS修改指示SNDCP后,SNDCP应该返回APS响应信息.该函数用于处理这
                  个响应消息.并调用RABM提供的函数设置RABM的TRANSMODE,然后上报
                  APP修改是否成功的事件。
 Input          : pSnMdfRsp
 Output         : NO
 Return Value   :
 Data Access    :
 Data Update    :
 Calls          : Rabm_SetTransMode();
                  Aps_DealEntityTrans();
 Called By      : Aps_DealAllFromSndcp()
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID    Aps_SnMsgModSnMdfRsp  ( APS_SNDCP_MODIFY_RSP_ST*  pSnMdfRsp )
{
    VOS_UINT8                       ucPdpId;
    RABM_APS_SET_TRANS_MODE_ST      ApsRabmSetTRansMod;

    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    Aps_SnMdfRspChngEntity(pSnMdfRsp, ucPdpId);

    ApsRabmSetTRansMod.ucNsapi      = pSnMdfRsp->ucNsapi;
    ApsRabmSetTRansMod.TransMode    = g_PdpEntity[ucPdpId].GprsPara.TransMode;

    /*设置RABM的传输模式*/
    if ( TAF_APS_SUCC != Aps_SetRabmTransMode(&ApsRabmSetTRansMod))
    {
        APS_WARN_LOG("NAS_RabmSetTransMode ERR ");
        return;
    }

    return;
}

/*****************************************************************************
 Prototype      : Aps_SnMsgModSnMdfRspParaCheck()
 Description    :
 Input          : pSnActRsp
 Output         :
 Return Value   : #define APS_PARA_VALID                  0
                  #define APS_PARA_INVALID                1
                  APS_NSAPI_INVALID
 Data Access    :
 Data Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  Aps_SnMsgModSnMdfRspParaCheck( APS_SNDCP_MODIFY_RSP_ST*   pSnActRsp)
{
    if ( !(APS_JUDGE_NSAPI_VALID(pSnActRsp->ucNsapi)))
    {
        return  APS_NSAPI_INVALID;
    }

    return  APS_PARA_VALID;
}

/*****************************************************************************
 Prototype      : Aps_SnMdfRspChngEntity()
 Description    : 收到SN_MDF_RSP后修改状态机参数,TRANSMODE,状态
 Input          : pSnMdfRsp
 Output         : NO
 Return Value   :
 Data Access    :
 Data Update    :
 Calls          : Rabm_SetTransMode();
                  Aps_DealEntityTrans();
 Called By      : Aps_DealAllFromSndcp()
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
 2.日    期   : 2011年12月17日
   作    者   : s62952
   修改内容   : PS融合项目修改 :删除状态处理
*****************************************************************************/
VOS_VOID    Aps_SnMdfRspChngEntity(
    APS_SNDCP_MODIFY_RSP_ST            *pSnMdfRsp,
    VOS_UINT8                           ucPdpId
)
{
    RABM_TRANS_MODE_ENUM                TansMode;

    Aps_DecideTransMode( ucPdpId, &TansMode );

    /*填写状态机中的TRANSMODE*/
    g_PdpEntity[ucPdpId].GprsPara.Op_TransMode  = VOS_TRUE;
    g_PdpEntity[ucPdpId].GprsPara.TransMode     = TansMode;

    return;
}


/*****************************************************************************
 Prototype      : Aps_SnMsgModSnDeActRspParaCheck()
 Description    : 检查SAPI
 Input          : pSnActRsp
 Output         :
 Return Value   : #define APS_PARA_VALID                  0
                  #define APS_PARA_INVALID                1
 Data Access    :
 Data Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  Aps_SnMsgModSnStatusReqParaCheck
                            (   APS_SNDCP_STATUS_REQ_ST    *pSnDeActRsp)
{
    if ( APS_SAPI_VALID != APS_JUDGE_SAPI_VALID(pSnDeActRsp->ucSapi))
    {
        return  APS_PARA_INVALID;
    }

    return  APS_PARA_VALID;
}

/*****************************************************************************
 Prototype      : Aps_SetRabmTransMode
 Description    : 根据找到NSAPI对应的PdpId
 Input          : ucNsapi
 Output         :
 Return Value   : ucPdpId: [0,6], [8,14], 0xFF
 Data Access    :
 Data Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
  2.Date        : 2006-07-06
    Author      : L47619
    Modification: 根据问题单修改:A32D04774
*****************************************************************************/
VOS_UINT32  Aps_SetRabmTransMode(   RABM_APS_SET_TRANS_MODE_ST *pApsRabmSetTRansMod)
{
    VOS_UINT32                      ulRet;
    RABM_APS_SET_TRANSMODE_MSG     *pApsSetRabmTransmodeMsg;

    /*申请消息*/
    pApsSetRabmTransmodeMsg = (RABM_APS_SET_TRANSMODE_MSG *)PS_ALLOC_MSG(WUEPS_PID_TAF, (sizeof(RABM_APS_SET_TRANSMODE_MSG) - VOS_MSG_HEAD_LENGTH));
    if ( VOS_NULL_PTR == pApsSetRabmTransmodeMsg )
    {
        APS_ERR_LOG("Aps_SetRabmTransMode VOS_AllocMsg err ");
        return TAF_APS_FAIL;
    }

    /*构造RABM的消息头*/
    pApsSetRabmTransmodeMsg->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pApsSetRabmTransmodeMsg->ulSenderPid      = WUEPS_PID_TAF;
    pApsSetRabmTransmodeMsg->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pApsSetRabmTransmodeMsg->ulReceiverPid    = WUEPS_PID_RABM;

    pApsSetRabmTransmodeMsg->ulLength         = sizeof(RABM_APS_SET_TRANSMODE_MSG) - VOS_MSG_HEAD_LENGTH;

    /*填消息类型*/
    pApsSetRabmTransmodeMsg->usMsgType        = RABM_APS_SET_TRANSMODE_MSG_TYPE;

    /*填消息内容*/
    pApsSetRabmTransmodeMsg->RabmApsSetTransMode
                                            = *pApsRabmSetTRansMod;

    /*发送消息*/
    ulRet = PS_SEND_MSG(WUEPS_PID_TAF, pApsSetRabmTransmodeMsg );
    if ( VOS_OK != ulRet )
    {
        APS_WARN_LOG("Aps Send RABM_APS_SET_TRANSMODE_MSG ERR ");
        return  TAF_APS_FAIL;
    }

    APS_NORM_LOG("APS->RABM RABM_APS_SET_TRANSMODE_MSG ");

    return TAF_APS_SUCC;

}

/*****************************************************************************
 Prototype      : Aps_RabmMsgActSndcp
 Description    : 收到RABM的切换消息后，若要激活SNDCP，就调用此函数.
 Input          : pRabmMsg
 Output         : ---
 Return Value   : ---
 Data Access    :
 Data Update    :
 Calls          : ---
 Called By      : ---
 History        : ---
  1.Date        : 2005-0
    Author      : 韩鲁峰
    Modification: Created function
  2.日    期   : 2011年5月12日
    作    者   : A00165503
    修改内容   : 问题单号: DTS2011050405023, W2G挂起过程中发起PDP去激活, 重选
                 到G后, APS没有激活SNDCP, 导致SNDCP的状态与当前PDP状态不一致
  3.日    期   : 2011年12月22日
    作    者   : A00165503
    修改内容   : PS Project: 修改激活SNDCP处理逻辑, 去除发送消息失败的处理
*****************************************************************************/
VOS_VOID    Aps_RabmMsgActSndcp (   VOS_UINT8    ucPdpId )
{
    APS_INNER_SN_ACT_ST             InnerSnActInd;
    SM_TAF_QOS_STRU                 SmQos;

    if (APS_SNDCP_ACT == g_PdpEntity[ucPdpId].PdpProcTrack.ucSNDCPActOrNot)
    {
        /* SNDCP已经激活，无须再次激活 */
        return;
    }

    /*填PdpId*/
    InnerSnActInd.ucPdpId           = ucPdpId;

    /*调用函数Aps_PackSmQos ( &(g_PdpEntity[ucPdpId].PdpQos), &SmQos )把状态机
    中的QOS转换为激活SNDCP需要的QOS结构;*/
    PS_MEM_SET(&SmQos,0x00,sizeof(SmQos));
    Aps_PackSmQos ( &(g_PdpEntity[ucPdpId].PdpQos), &SmQos );
    InnerSnActInd.pQos              = &SmQos;

    Aps_SmMsgModSnActInd(&InnerSnActInd, APS_ACT_SN_SYS_CHNG);

    /*为了区别切换引起的激活SNDCP，以免收到SN的激活响应后再上报，在此设置标识*/
    g_PdpEntity[ucPdpId].PdpProcTrackFlag               = VOS_TRUE;
    g_PdpEntity[ucPdpId].PdpProcTrack.ucHowToInitAct    = APS_SYSCHNG_ACT_SN;
    g_PdpEntity[ucPdpId].PdpProcTrack.ucSNDCPActOrNot   = APS_SNDCP_ACT;

    return;
}

/*****************************************************************************
 Prototype      : Aps_RabmMsgDeActSndcp
 Description    : 收到RABM的切换消息后，若要发起去激活SNDCP，就调用此函数.
 Input          : pRabmMsg
 Output         : ---
 Return Value   : ---
 Data Access    :
 Data Update    :
 Calls          : Aps_SmMsgModSnDeActInd    (   VOS_UINT8    ucPdpId )
 Called By      : ---
 History        : ---
  1.Date        : 2005-0
    Author      : 韩鲁峰
    Modification: Created function
*****************************************************************************/
VOS_VOID    Aps_RabmMsgDeActSndcp ( VOS_UINT8    ucPdpId )
{
    if (APS_SNDCP_INACT == g_PdpEntity[ucPdpId].PdpProcTrack.ucSNDCPActOrNot)
    {
        /*SNDCP未被激活*/
        APS_WARN_LOG("Aps_RabmMsgDeActSndcp: SNDCP has been deactived already!!");
        return;
    }

    (VOS_VOID)Aps_SmMsgModSnDeActInd(ucPdpId);

    g_PdpEntity[ucPdpId].PdpProcTrack.ucSNDCPActOrNot = APS_SNDCP_INACT;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_ValidatePdpForSnStatusReq
 功能描述  : 检查当前APS实体中的SAPI是否满足SN STATUS消息中指定的SAPI
 输入参数  : ucPdpId                    - APS实体索引
             pstSnStatusReq             - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 满足
             VOS_FALSE                  - 不满足
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月24日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_ValidatePdpForSnStatusReq(
    VOS_UINT8                           ucPdpId,
    APS_SNDCP_STATUS_REQ_ST            *pstSnStatusReq
)
{
    VOS_UINT32                          ulResult;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    /* 获取该PDPID的PDP实体内容地址 */
    ulResult                            = VOS_FALSE;
    pstPdpEntity                        = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    switch (pstSnStatusReq->usSnCause)
    {
        case SN_CAUSE_NORMAL_REL:           /*Cause "normal release"*/
            /*SM shall then deactivate all PDP contexts for that SAPI requiring
              acknowledged peer-to-peer LLC operation*/

        case SN_CAUSE_DM_RCV:               /*Cause "DM received"*/
            /*SM shall then deactivate all PDP contexts for that SAPI requiring
              acknowledged peer-to-peer LLC operation*/

            if ( (VOS_TRUE               == pstPdpEntity->PdpGprsParaFlag)
              && (VOS_TRUE               == pstPdpEntity->GprsPara.Op_Sapi)
              && (pstSnStatusReq->ucSapi == pstPdpEntity->GprsPara.ucSapi)
              && (VOS_TRUE               == pstPdpEntity->GprsPara.Op_TransMode)
              && (RABM_ABM_ENUM          == pstPdpEntity->GprsPara.TransMode) )
            {
                ulResult = VOS_TRUE;
            }
            break;

        case    SN_CAUSE_NO_PEER_RSP:          /*Cause "no peer response"*/
            /*处理方式同下面的CASE,故不用break*/

        case    SN_CAUSE_INVALID_XID_RSP:      /*Cause "invalid XID response"*/
            /*SM shall then deactivate all PDP contexts for that SAPI*/
            /*处理方式同下面的CASE,故不用break*/

        case    SN_CAUSE_INVALID_XID_CMD:       /*Cause "invalid XID command"*/
            /*SM shall then deactivate all PDP contexts for this SAPI*/

            if ( (VOS_TRUE               == pstPdpEntity->PdpGprsParaFlag)
              && (VOS_TRUE               == pstPdpEntity->GprsPara.Op_Sapi)
              && (pstSnStatusReq->ucSapi == pstPdpEntity->GprsPara.ucSapi) )
            {
                ulResult = VOS_TRUE;
            }
            break;

        default :
            APS_WARN_LOG("SNDCP -> Aps : invalid Status Msg Cause !");
            break;
    }

    return ulResult;
}

/*lint +e958*/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
