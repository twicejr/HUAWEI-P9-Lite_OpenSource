/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : Rabm_DealSnMsg.c
  Author       : l47619
  Version      : V200R001
  Date         : 2005-08-30
  Description  : 该C文件给出了R_SN模块的实现
  Function List:
        1.NAS_RabmSnSequenceRspMsg
        2.NAS_RabmDeal2GSnSequence
        3.NAS_RabmDealChangeSnSequence

  History      :
  1. Date:2005-08-30
     Author: l47619
     Modification:create
  2. Date:2006-04-13
     Author: l47619
     Modification:根据问题单修改 : A32D03129
  3. Date:2006-05-08
     Author: l47619
     Modification:根据问题单修改 : A32D03487
  4. Date: 2006-06-24
     Author: l47619
     Modification:根据问题单修改 : A32D05709
************************************************************************/

/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "Rabm2GInclude.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_RABM_DEALSNMSG_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/*****************************************************************************
   2 全局变量定义
*****************************************************************************/


/*****************************************************************************
   3 函数实现
*****************************************************************************/

/*****************************************************************************
 Prototype      : NAS_RabmSnSequenceRspMsg()
 Description    : 处理SNDCP模块发送过来的SNRABM-SEQUENCE.response信息
 Input          : pMsg                 SNRABM-SEQUENCE.response消息所对应的指针
 Output         :
 Return Value   : 无
 Calls          :
 Called By      :
 History        :
  1.Date        : 2005-08-30
    Author      : l47619
    Modification: Created function
  2.Date        :2006-05-08
    Author      : l47619
    Modification:根据问题单修改 : A32D03487
*****************************************************************************/
VOS_VOID  NAS_RabmSnSequenceRspMsg( VOS_VOID *pMsg )
{
    VOS_UINT8                                ucLoop;
    VOS_UINT8                                ucFlag = VOS_FALSE;
    ST_APP_RABM_STATUS                       stReportStatus;

    if ( ( RABM_ROUTING_AREA_UPDATE_T1_ON != gRabmRAT1Switch )
         && ( RABM_3G_TO_2G_T3_ON != gRabm3GTo2GT3Switch ) )   /*两个定时器都没开*/
    {
        /*打印警告信息---收到不合逻辑的消息:*/
        RABM_LOG_WARNING( "NAS_RabmSnSequenceRspMsg:WARNING:RECEIVE an ILLOGICAL SnSequenceRsp Msg because rout.area.update.T1 and Rabm.sys.3To2.T3 Timer are OFF!" );
        return;
    }

    if ( ( RABM_ROUTING_AREA_UPDATE_T1_ON == gRabmRAT1Switch )
         && ( RABM_3G_TO_2G_T3_ON == gRabm3GTo2GT3Switch ) )   /*两个定时器都开了*/
    {
        /*打印警告信息---收到不合逻辑的消息:*/
        RABM_LOG_WARNING( "NAS_RabmSnSequenceRspMsg:WARNING:RECEIVE an ILLOGICAL SnSequenceRsp Msg because rout.area.update.T1 and Rabm.sys.3To2.T3 Timer are ON!" );
        return;
    }

    /*打印流程信息---收到消息:*/
    RABM_LOG_NORMAL( "NAS_RabmSnSequenceRspMsg:NORMAL:RECEIVE RABM_SN_SEQUENCE_RSP_MSG Msg From UEPS_PID_SN" );

    if ( RABM_3G_TO_2G_T3_ON == gRabm3GTo2GT3Switch )
    {
        ucFlag = VOS_TRUE;
    }

    for ( ucLoop = 0; ucLoop < RABM_2G_MAX_ENT_NUM; ucLoop++ )   /*遍历2G中的每个NSAPI*/
    {
        switch ( gastRabm2GEntity[ucLoop].State )   /*该NSAPI的状态*/
        {
            case RABM_2G_NULL:
                break;
            case RABM_NSAPI_OK_TRANSMODE_NO:
            case RABM_DATA_TRANS_READY:
            case RABM_DATA_TRANS_STOP:                      /*这三种状态的处理方式一样*/
                if ( VOS_TRUE == ucFlag )
                {
                    if ( RABM_NSAPI_OK_TRANSMODE_NO == gastRabm2GEntity[ucLoop].State )
                    {
                        RABM_LOG1_WARNING( "NAS_RabmSnSequenceRspMsg:WARNING:RABM_NSAPI_OK_TRANSMODE_NO state receive SnSequenceRsp Msg is ILLOGICAL: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                    }
                    else if ( RABM_DATA_TRANS_READY == gastRabm2GEntity[ucLoop].State )
                    {
                        RABM_LOG1_WARNING( "NAS_RabmSnSequenceRspMsg:WARNING:RABM_DATA_TRANS_READY state receive SnSequenceRsp Msg is ILLOGICAL: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                    }
                    else
                    {
                        RABM_LOG1_WARNING( "NAS_RabmSnSequenceRspMsg:WARNING:RABM_DATA_TRANS_STOP state receive SnSequenceRsp Msg is ILLOGICAL: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                    }
                }
                break;
            case RABM_ROUT_AREA_UPDATE:
                /*将该NSAPI的状态置为RABM_DATA_TRANS_READY:*/
                RABM_SetGState((RABM_NSAPI_ENUM)ucLoop, RABM_DATA_TRANS_READY);
                /*打印流程信息---状态切换:*/
                RABM_LOG1_NORMAL( "STATE RABM_ROUT_AREA_UPDATE state CHANGE TO RABM_DATA_TRANS_READY state: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );

                if ( RABM_ROUTING_AREA_UPDATE_T1_ON == gRabmRAT1Switch )   /*若打开了rout.area.update.T1定时器*/
                {
                    /*进行2G中的处理:*/
                    NAS_RabmDeal2GSnSequence(pMsg);

                    /*向APP上报TAFRABM_STARTSTOP_IND(START)消息:*/
                    stReportStatus.ucDomain     = D_RABM_PS_DOMAIN;
                    stReportStatus.ucRabId      = ucLoop + RABM_NSAPI_OFFSET;
                    stReportStatus.ucStatus     = TAF_RABM_START_DATA;
                    stReportStatus.ucStartCause = TAF_RABM_START_CAUSE_3G_TO_2G_RA_UPDATE_FINISH;
                    Api_AppRabmStatusInd( &stReportStatus );             /*通知APP开始数据传输*/
                    /*打印流程信息---上报了消息:*/
                    RABM_LOG1_NORMAL( "STATE RABM_ROUT_AREA_UPDATE state report TAFRABM_STARTSTOP_IND(START) Msg to APP: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );

                }
                else if ( RABM_3G_TO_2G_T3_ON == gRabm3GTo2GT3Switch )           /*若打开了Rabm.sys.3To2.T3定时器*/
                {
                    /*进行切换中的处理*/
                    NAS_RabmDealChangeSnSequence();

                    /*向APP上报TAFRABM_STARTSTOP_IND(START)消息:*/
                    stReportStatus.ucDomain     = D_RABM_PS_DOMAIN;
                    stReportStatus.ucRabId      = ucLoop + RABM_NSAPI_OFFSET;
                    stReportStatus.ucStatus     = TAF_RABM_START_DATA;
                    stReportStatus.ucStartCause = TAF_RABM_START_CAUSE_3G_TO_2G_RA_UPDATE_FINISH;
                    Api_AppRabmStatusInd( &stReportStatus );             /*通知APP开始数据传输*/
                    /*打印流程信息---上报了消息:*/
                    RABM_LOG1_NORMAL( "STATE RABM_ROUT_AREA_UPDATE state report TAFRABM_STARTSTOP_IND(START) Msg to APP: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                }
                else
                {
                    /*向APP上报TAFRABM_STARTSTOP_IND(START)消息:*/
                    stReportStatus.ucDomain     = D_RABM_PS_DOMAIN;
                    stReportStatus.ucRabId      = ucLoop + RABM_NSAPI_OFFSET;
                    stReportStatus.ucStatus     = TAF_RABM_START_DATA;
                    stReportStatus.ucStartCause = TAF_RABM_START_CAUSE_3G_TO_2G_RA_UPDATE_FINISH;
                    Api_AppRabmStatusInd( &stReportStatus );             /*通知APP开始数据传输*/
                    /*打印流程信息---上报了消息:*/
                    RABM_LOG1_NORMAL( "STATE RABM_ROUT_AREA_UPDATE state report TAFRABM_STARTSTOP_IND(START) Msg to APP: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                }
                break;
            default:
                /*打印出错信息---该NSAPI的状态字段出错:*/
                RABM_LOG1_ERROR( "NAS_RabmSnSequenceRspMsg:ERROR:This NSAPI's state is WRONG!: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
        }
    }

}


/*****************************************************************************
 Prototype      : NAS_RabmDeal2GSnSequence()
 Description    : 收到SNRABM-SEQUENCE.response消息后，
                  需遍历所有NSAPI以进行相应的状态切换(2G中)
 Input          : pMsg                      入口消息指针
 Output         :
 Return Value   : 无
 Calls          :
 Called By      :
 History        :
  1.Date        : 2005-09-17
    Author      : l47619
    Modification: Created function
*****************************************************************************/
VOS_VOID  NAS_RabmDeal2GSnSequence( VOS_VOID * pMsg )
{
    VOS_UINT32                               ulLength;
    RABM_SN_SEQUENCE_RSP_MSG                *pstSequenceRsp;
    GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG     *pstRAUpdateRsp;

    pstSequenceRsp = ( RABM_SN_SEQUENCE_RSP_MSG * )pMsg;

    /*关闭rout.area.update.T1定时器:*/
    NAS_RabmStopTimer( RABM_TIMER_NAME_COMMON, RABM_TIMER_PARA_ROUT_AREA_UPDATE_T1 );

    /*发送GMMRABM_ROUTING_AREA_UPDATE_RSP消息:*/
    ulLength       = sizeof( GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG ) - VOS_MSG_HEAD_LENGTH;
    pstRAUpdateRsp = ( GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG * )PS_ALLOC_MSG( WUEPS_PID_RABM, ulLength );
    if ( VOS_NULL_PTR == pstRAUpdateRsp )
    {
        /*打印出错信息---申请消息包失败:*/
        RABM_LOG_ERROR( "NAS_RabmDeal2GSnSequence:ERROR:Allocates a message packet for ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP msg FAIL!" );
        return;
    }
    /*填写消息头:*/
    pstRAUpdateRsp->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstRAUpdateRsp->MsgHeader.ulSenderPid     = WUEPS_PID_RABM;
    pstRAUpdateRsp->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstRAUpdateRsp->MsgHeader.ulReceiverPid   = WUEPS_PID_GMM;
    pstRAUpdateRsp->MsgHeader.ulLength        = ulLength;

    pstRAUpdateRsp->MsgHeader.ulMsgName       = ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP;
    /*填写消息体:*/
    /*置N-PDU为有效:*/
    pstRAUpdateRsp->ucNpduValidFlg            = GMM_RABM_NPDU_VALID;
    /*填入N-PDU码流:*/
    NAS_RabmEncodeNPdu( pstRAUpdateRsp , &pstSequenceRsp->RabmSnSequenceRsp.RecvNPduNumList );
    /*发送该消息:*/
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_RABM, pstRAUpdateRsp ) )
    {
        /*打印警告信息---发送消息失败:*/
        RABM_LOG_WARNING( "NAS_RabmDeal2GSnSequence:WARNING:SEND ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP msg FAIL!" );
    }
    else
    {
        /*打印流程信息---发送了消息:*/
        RABM_LOG_NORMAL( "NAS_RabmDeal2GSnSequence:NORMAL:SEND ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP Msg" );
    }

}



/*****************************************************************************
 Prototype      : NAS_RabmDealChangeSnSequence()
 Description    : 收到SNRABM-SEQUENCE.response消息后，
                  需遍历所有NSAPI以进行相应的状态切换(切换中)
 Input          : 无
 Output         :
 Return Value   : 无
 Calls          :
 Called By      :
 History        :
  1.Date        : 2005-09-17
    Author      : l47619
    Modification: Created function
  1.Date        : 2006-06-27
    Author      : l47619
    Modification: 根据问题单修改: A32D05709
*****************************************************************************/
VOS_VOID  NAS_RabmDealChangeSnSequence( VOS_VOID )
{
    /*关闭Rabm.sys.3To2.T3定时器:*/
    NAS_RabmStopTimer( RABM_TIMER_NAME_COMMON, RABM_TIMER_PARA_3_TO_2_T3 );

    /*向SNDCP发送RABM_SNDCP_RESUME_DATA_IND消息:*/
    NAS_RabmSndSnDataResumeInd();
}


/*****************************************************************************
 Prototype      : NAS_RabmSnSaveDataRspMsg()
 Description    : 2G切入3G，RABM向SNDCP发送数据缓存指示后，SNDCP向RABM发送的回复消息
 Input          : VOS_VOID
 Output         :
 Return Value   : 无
 Calls          :
 Called By      :
 History        :
  1.Date        : 2006-06-24
    Author      : l47619
    Modification: Created function
*****************************************************************************/
VOS_VOID  NAS_RabmSnSaveDataRspMsg(VOS_VOID)
{
    /*打印流程信息--收到RABM_SNDCP_SAVE_DATA_RSP消息:*/
    RABM_LOG_NORMAL("NAS_RabmSnSaveDataRspMsg:NORMAL:Recv RABM_SNDCP_SAVE_DATA_RSP msg");

    return;
}



/*****************************************************************************
 Prototype      : NAS_RabmSnResumeDataRspMsg()
 Description    : 3G向2G切换完成后，RABM向SNDCP发送回复数传指示后，SNDCP向RABM发送的回复消息
 Input          : VOS_VOID
 Output         :
 Return Value   : 无
 Calls          :
 Called By      :
 History        :
  1.Date        : 2006-06-24
    Author      : l47619
    Modification: Created function
*****************************************************************************/
VOS_VOID  NAS_RabmSnResumeDataRspMsg(VOS_VOID)
{
    /*打印流程信息--收到RABM_SNDCP_RESUME_DATA_RSP消息:*/
    RABM_LOG_NORMAL("NAS_RabmSnSaveDataRspMsg:NORMAL:Recv RABM_SNDCP_RESUME_DATA_RSP msg");

    return;
}


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
