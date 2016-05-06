/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : Rabm_DealTimerMsg.c
  Author       : l47619
  Version      : V200R001
  Date         : 2005-08-30
  Description  : 该C文件给出了R_TIMER模块的实现
  Function List:
        1. NAS_RabmTimerExpiredMsgDispatch
        2. NAS_RabmRoutingAreaUpdateT1Expired
        3. NAS_RabmActReqT1Expired
        4. NAS_Rabm2GTo3GT1Expired
        5. NAS_Rabm3GTo2GT1Expired
        6. NAS_Rabm3GTo2GT3Expired
        7. NAS_RabmFluxReportExpired

  History        :
  1. Date        : 2005-08-30
     Author      : l47619
     Modification:create
  2. Date        : 2006-05-08
     Author      : l47619
     Modification: 根据问题单修改: A32D03487
  3. Date        : 2006-08-11
     Author      : l47619
     Modification: 根据问题单修改: A32D05709
************************************************************************/

/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "Rabm2GInclude.h"
#include "NasRabmMain.h"
#include "NasRabmFastdorm.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e958*/

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_RABM_DEALTIMEOUTMSG_C

/*****************************************************************************
   2 全局变量定义
*****************************************************************************/


/*****************************************************************************
   3 函数实现
*****************************************************************************/

/*****************************************************************************
 Prototype      : NAS_RabmTimerExpiredMsgDispatch()
 Description    : 超时消息分发函数
 Input          : pTimerExpiredMsg     超时消息对应的指针
 Output         :
 Return Value   : 无
 Calls          :
 Called By      :
 History        :
  1.Date        : 2005-08-30
    Author      : l47619
    Modification: Created function
*****************************************************************************/
VOS_VOID  NAS_RabmTimerExpiredMsgDispatch( REL_TIMER_MSG  *pTimerExpiredMsg )
{
    switch ( pTimerExpiredMsg->ulPara )           /*超时消息分发*/
    {
        case RABM_TIMER_PARA_ROUT_AREA_UPDATE_T1:
            /*打印流程信息---收到超时消息:*/
            RABM_LOG_NORMAL( "NAS_RabmTimerExpiredMsgDispatch:NORMAL:RECEIVE Rabm.rout.area.update.T1 Timer Expired Msg" );

            NAS_RabmRoutingAreaUpdateT1Expired( pTimerExpiredMsg );
            break;

        case RABM_TIMER_PARA_3_TO_2_T3:
            /*打印流程信息---收到超时消息:*/
            RABM_LOG_NORMAL( "NAS_RabmTimerExpiredMsgDispatch:NORMAL:RECEIVE Rabm.Sys.3To2.T3 Timer Expired Msg" );

            NAS_Rabm3GTo2GT3Expired( pTimerExpiredMsg );
            break;
        case RABM_TIMER_PARA_ACT_REQ_T1:
            /*打印流程信息---收到超时消息:*/
            RABM_LOG1_NORMAL( "NAS_RabmTimerExpiredMsgDispatch:NORMAL:RECEIVE Rabm.act.req.T1 Timer Expired Msg!: NSAPI:", (VOS_INT32)(pTimerExpiredMsg->ulName + RABM_NSAPI_OFFSET) );

            NAS_RabmActReqT1Expired( pTimerExpiredMsg );
            break;
        case RABM_TIMER_PARA_REESTRAB_TIMER:
            /*打印警告信息--- 收到不合逻辑的消息:*/
            RABM_LOG_WARNING( "NAS_RabmTimerExpiredMsgDispatch:WARNING:RECEIVE Rabm.ReestRab Expired Msg is ILLOGICAL in 2G mode!" );
            break;
        default:
            /*打印警告信息--- 超时消息的ulPara字段出错:*/
            RABM_LOG_WARNING( "NAS_RabmTimerExpiredMsgDispatch:WARNING:RECEIVE an ERROR Expired Msg(The PARA item of the msg is WRONG)!" );
            break;
    }
}



/*****************************************************************************
 Prototype      : NAS_RabmRoutingAreaUpdateT1Expired()
 Description    : 处理Rabm.rout.area.update.T1.Expired超时消息
 Input          : pTimerExpiredMsg     超时消息指针
 Output         :
 Return Value   : 无
 Calls          :
 Called By      :
 History        :
  1.Date        : 2005-08-30
    Author      : l47619
    Modification: Created function
*****************************************************************************/
VOS_VOID  NAS_RabmRoutingAreaUpdateT1Expired( REL_TIMER_MSG  *pTimerExpiredMsg )
{
    VOS_UINT8                               ucLoop;
    VOS_UINT32                              ulLength;
    GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG    *pstRAUpdateRsp;

    /*判断入口参数是否合法:*/
    if ( RABM_TIMER_NAME_COMMON != pTimerExpiredMsg->ulName )
    {
        /*打印警告信息---超时消息名字出错:*/
        RABM_LOG_WARNING( "NAS_RabmRoutingAreaUpdateT1Expired:WARNING:The Name of the Rabm.rout.area.update.T1 Expired Msg is WRONG!" );
        return;
    }

    if ( RABM_ROUTING_AREA_UPDATE_T1_ON != gRabmRAT1Switch )    /*若未打开Rabm.rout.area.update.T1定时器*/

    {
        /*打印警告信息---收到不合逻辑的消息:*/
        RABM_LOG_WARNING( "NAS_RabmRoutingAreaUpdateT1Expired:WARNING:RECEIVE Rabm.rout.area.update.T1 Timer Expired Msg is ILLOGICAL because Rabm.rout.area.update.T1 Timer hasn't started!" );
        return;
    }

    /*发送将Rx N-PDU numbers填为0的GMMRABM_ROUTING_AREA_UPDATE_RSP消息:*/
    ulLength       = sizeof( GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG ) - VOS_MSG_HEAD_LENGTH;
    pstRAUpdateRsp = ( GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG * )PS_ALLOC_MSG( WUEPS_PID_RABM, ulLength );
    if ( VOS_NULL_PTR == pstRAUpdateRsp )
    {
        /*打印出错信息---申请消息包失败:*/
        RABM_LOG_ERROR( "NAS_RabmRoutingAreaUpdateT1Expired:ERROR:Allocates a message packet for ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP msg FAIL!" );
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
    PS_NAS_MEM_SET( pstRAUpdateRsp->aucRecvNPDUNumListIE, 0, RABM_RECV_N_PDU_NUM_LIST_IE_MAXLEN );
    /*填写N-PDU有效标志为无效:*/
    pstRAUpdateRsp->ucNpduValidFlg = GMM_RABM_NPDU_INVALID;
    /*发送该消息:*/
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_RABM, pstRAUpdateRsp ) )
    {
        /*打印警告信息---发送消息失败:*/
        RABM_LOG_WARNING( "NAS_RabmRoutingAreaUpdateT1Expired:WARNING:SEND ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP(N-PDU numbers is 0) msg FAIL!" );
    }
    else
    {
        /*打印流程信息---发送了消息:*/
        RABM_LOG_NORMAL( "NAS_RabmRoutingAreaUpdateT1Expired:NORMAL:SEND ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP(N-PDU numbers is 0) Msg" );
    }

    /*复位Rabm.rout.area.update.T1定时器标志:*/
    gRabmRAT1Switch = RABM_ROUTING_AREA_UPDATE_T1_OFF;

    for ( ucLoop = 0; ucLoop < RABM_2G_MAX_ENT_NUM; ucLoop++ )   /*遍历2G中的每个NSAPI*/
    {
        switch ( gastRabm2GEntity[ucLoop].State )    /*该NSAPI的状态*/
        {
            case RABM_2G_NULL:
            case RABM_NSAPI_OK_TRANSMODE_NO:
            case RABM_DATA_TRANS_READY:
            case RABM_DATA_TRANS_STOP:                  /*这四种状态的处理方式一样*/
                break;
            case RABM_ROUT_AREA_UPDATE:
                /*将该NSAPI的状态置为RABM_DATA_TRANS_READY:*/
                RABM_SetGState((RABM_NSAPI_ENUM)ucLoop, RABM_DATA_TRANS_READY);
                /*打印流程信息---状态切换:*/
                RABM_LOG1_NORMAL( "STATE RABM_ROUT_AREA_UPDATE state CHANGE TO RABM_DATA_TRANS_READY state: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                break;
            default:
                /*打印出错信息---该NSAPI的状态字段出错:*/
                RABM_LOG1_ERROR( "NAS_RabmRoutingAreaUpdateT1Expired:ERROR:This NSAPI's state is WRONG!: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
        }
    }
}



/*****************************************************************************
 Prototype      : NAS_RabmActReqT1Expired()
 Description    : 处理Rabm.act.req.T1.Expired超时消息
 Input          : pTimerExpiredMsg     超时消息指针
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
VOS_VOID  NAS_RabmActReqT1Expired( REL_TIMER_MSG  *pTimerExpiredMsg )
{
    /*判断入口参数是否合法:*/
    if ( pTimerExpiredMsg->ulName > RABM_TIMER_NAME_NSAPI_15 )
    {
        /*打印警告信息---NSAPI超出范围:*/
        RABM_LOG1_WARNING( "NAS_RabmActReqT1Expired:WARNING:The NSAPI item of the Msg is BEYOND Range!: NSAPI:", (VOS_INT32)(pTimerExpiredMsg->ulName + RABM_NSAPI_OFFSET) );
        return;
    }

    /*若未打开Rabm.act.req.T1定时器:*/
    if ( RABM_ACT_REQ_T1_ON != gaRabmActReqT1Switch[pTimerExpiredMsg->ulName] )     /*若未打开该NSAPI的Rabm.act.req.T1定时器*/
    {
        /*打印警告信息---收到不合逻辑的消息:*/
        RABM_LOG1_WARNING( "NAS_RabmActReqT1Expired:WARNING:RECEIVE Rabm.act.req.T1 Timer Expired Msg is ILLOGICAL because Rabm.act.req.T1 Timer hasn't started!: NSAPI:", (VOS_INT32)(pTimerExpiredMsg->ulName + RABM_NSAPI_OFFSET) );
        return;
    }

    /*复位该NSAPI的Rabm.act.req.T1定时器标志:*/
    gaRabmActReqT1Switch[pTimerExpiredMsg->ulName] = RABM_ACT_REQ_T1_OFF;

    if ( RABM_NSAPI_OK_TRANSMODE_NO == gastRabm2GEntity[pTimerExpiredMsg->ulName].State )  /*若该NSAPI处于RABM_NSAPI_OK_TRANSMODE_NO状态*/
    {
        /*将该NSAPI设置为非确认模式:*/
        gastRabm2GEntity[pTimerExpiredMsg->ulName].TransMode = RABM_ADM_ENUM;
        /*打印流程信息---传输模式设为非确认模式:*/
        RABM_LOG1_NORMAL( "NAS_RabmActReqT1Expired:Transmode set to ADM mode: NSAPI:", (VOS_INT32)(pTimerExpiredMsg->ulName + RABM_NSAPI_OFFSET) );

        /*将该NSAPI的状态置为RABM_DATA_TRANS_READY:*/
        RABM_SetGState((RABM_NSAPI_ENUM)(pTimerExpiredMsg->ulName), RABM_DATA_TRANS_READY);

        /*打印流程信息---状态切换:*/
        RABM_LOG1_NORMAL( "STATE RABM_NSAPI_OK_TRANSMODE_NO state CHANGE TO RABM_DATA_TRANS_READY state: NSAPI:", (VOS_INT32)(pTimerExpiredMsg->ulName + RABM_NSAPI_OFFSET) );
    }
    else
    {
        /*打印警告信息---该NSAPI所处的状态不合逻辑:*/
        RABM_LOG1_WARNING( "NAS_RabmActReqT1Expired:WARNING:The NSAPI's state is ILLOGICAL when RECEIVE Rabm.act.req.T1 Timer Expired Msg!: NSAPI:", (VOS_INT32)(pTimerExpiredMsg->ulName + RABM_NSAPI_OFFSET) );
    }
}

/*****************************************************************************
 Prototype      : NAS_Rabm3GTo2GT3Expired()
 Description    : 处理Rabm.Sys.3To2.T3.Expired超时消息
 Input          : pTimerExpiredMsg     超时消息指针
 Output         :
 Return Value   : 无
 Calls          :
 Called By      :
 History        :
  1.Date        : 2005-08-30
    Author      : l47619
    Modification: Created function
  2.Date        : 2006-08-11
    Author      : l47619
    Modification: 根据问题单修改: A32D05709
*****************************************************************************/
VOS_VOID  NAS_Rabm3GTo2GT3Expired( REL_TIMER_MSG  *pTimerExpiredMsg )
{
    VOS_UINT8               ucLoop;
    ST_APP_RABM_STATUS      stReportStatus;

    /*判断入口参数是否合法:*/
    if ( RABM_TIMER_NAME_COMMON != pTimerExpiredMsg->ulName )
    {
        /*打印警告信息---超时消息名字出错:*/
        RABM_LOG_WARNING( "NAS_Rabm3GTo2GT3Expired:WARNING:The Name of the Rabm.Sys.3To2.T3 Timer Expired Msg is WRONG!" );
        return;
    }

    if ( RABM_3G_TO_2G_T3_ON != gRabm3GTo2GT3Switch )         /*若未打开Rabm.Sys.3To2.T3定时器*/
    {
        /*打印警告信息---收到不合逻辑的消息:*/
        RABM_LOG_WARNING( "NAS_Rabm3GTo2GT3Expired:WARNING:RECEIVE Rabm.Sys.3To2.T3 Timer Expired Msg is ILLOGICAL because Rabm.Sys.3To2.T3 Timer hasn't started!" );
        return;
    }

    /*复位Rabm.3To2.T3定时器标志:*/
    gRabm3GTo2GT3Switch = RABM_3G_TO_2G_T3_OFF;

    for ( ucLoop = 0; ucLoop < RABM_2G_MAX_ENT_NUM; ucLoop++ )    /*遍历2G的每个NSAPI*/
    {
        switch ( gastRabm2GEntity[ucLoop].State )    /*该NSAPI所对应的状态*/
        {
            case RABM_2G_NULL:
                /*打印流程信息---状态不变:*/
                RABM_LOG1_NORMAL( "STATE RABM_2G_NULL state keep the same: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                break;
            case RABM_NSAPI_OK_TRANSMODE_NO:
            case RABM_DATA_TRANS_READY:
            case RABM_DATA_TRANS_STOP:                  /*这三种状态的处理方式一样*/
                /*打印警告信息---该NSAPI所对应的状态不合逻辑:*/
                if ( RABM_NSAPI_OK_TRANSMODE_NO == gastRabm2GEntity[ucLoop].State )
                {
                    RABM_LOG1_WARNING( "NAS_Rabm3GTo2GT3Expired:WARNING:RABM_NSAPI_OK_TRANSMODE_NO state RECEIVE Rabm.Sys.3To2.T3 Timer Expired Msg is ILLOGICAL!: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                }
                else if ( RABM_DATA_TRANS_READY == gastRabm2GEntity[ucLoop].State )
                {
                    RABM_LOG1_WARNING( "NAS_Rabm3GTo2GT3Expired:WARNING:RABM_DATA_TRANS_READY state RECEIVE Rabm.Sys.3To2.T3 Timer Expired Msg is ILLOGICAL!: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                }
                else
                {
                    RABM_LOG1_WARNING( "NAS_Rabm3GTo2GT3Expired:WARNING:RABM_DATA_TRANS_STOP state RECEIVE Rabm.Sys.3To2.T3 Timer Expired Msg is ILLOGICAL!: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                }
                break;
            case RABM_ROUT_AREA_UPDATE:
                /*向APP上报TAFRABM_STARTSTOP_IND(START)消息:*/
                stReportStatus.ucDomain     = D_RABM_PS_DOMAIN;
                stReportStatus.ucRabId      = ucLoop + RABM_NSAPI_OFFSET;
                stReportStatus.ucStatus     = TAF_RABM_START_DATA;
                stReportStatus.ucStartCause = TAF_RABM_START_CAUSE_3G_TO_2G_RA_UPDATE_FINISH;
                Api_AppRabmStatusInd( &stReportStatus );             /*通知APP开始数据传输*/
                /*打印流程信息---上报了消息:*/
                RABM_LOG1_NORMAL( "STATE RABM_ROUT_AREA_UPDATE state report TAFRABM_STARTSTOP_IND(START) Msg to APP: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );

                /*将状态置为RABM_DATA_TRANS_READY:*/
                RABM_SetGState((RABM_NSAPI_ENUM)ucLoop, RABM_DATA_TRANS_READY);
                /*打印流程信息---状态切换:*/
                RABM_LOG1_NORMAL( "STATE RABM_ROUT_AREA_UPDATE state CHANGE TO RABM_DATA_TRANS_READY state: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                break;
            default:
                /*打印出错信息---NSAPI对应的状态字段出错:*/
                RABM_LOG1_ERROR( "NAS_Rabm3GTo2GT3Expired:ERROR:This NSAPI's state is WRONG!: NSAPI:", ucLoop + RABM_NSAPI_OFFSET );
                break;
        }
    }

    /*释放在3G向2G切换开始时PDCP缓存的数据:*/
    SN_RabmClear3G2Share();
}


/*****************************************************************************
 函 数 名  : NAS_RABM_ProcTiRabReestRequestExpired
 功能描述  : RAB重建(DATA SERVICE REQUEST)保护定时器超时处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月17日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_RABM_ProcTiRabReestRequestExpired(VOS_VOID)
{
    VOS_UINT8                           ucEntId;

    NAS_NORMAL_LOG(WUEPS_PID_RABM,
        "NAS_RABM_ProcTiRabReestRequestExpired: RABM_TIMER_PARA_REESTRAB_TIMER");

    /* 清除RAB重建定时器启动标识 */
    NAS_RABM_ClearRabRsestTimerFlg();

    /* 遍历RABM实体, 通知CDS模块释放触发业务重建的缓存 */
    for (ucEntId = 0; ucEntId < RABM_3G_PS_MAX_ENT_NUM; ucEntId++)
    {
        if (VOS_TRUE == NAS_RABM_GetWPsEntRabReestFlg(ucEntId))
        {
            NAS_RABM_ClearWPsEntRabReestFlg(ucEntId);
            NAS_RABM_SndCdsFreeBuffDataInd(ucEntId + RABM_NSAPI_OFFSET);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_RABM_ProcTiRabReestPendingExpired
 功能描述  : RB建立保护定时器超时处理
 输入参数  : ucRabId - RABID [5,15]
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月17日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_RABM_ProcTiRabReestPendingExpired(VOS_UINT8 ucRabId)
{
    NAS_NORMAL_LOG(WUEPS_PID_RABM,
        "NAS_RABM_ProcTiRabReestPendingExpired: RABM_TIMER_RAB_REESTABLISH_PENDING");

    /* 清除实体重建标识 */
    NAS_RABM_ClearWPsEntRabReestFlg(ucRabId - RABM_NSAPI_OFFSET);

    /* 通知CDS数传重建失败 */
    NAS_RABM_SndCdsFreeBuffDataInd(ucRabId);

    return;
}

/*lint +e958*/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
