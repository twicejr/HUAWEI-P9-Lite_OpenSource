/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : Rabm_DealSmMsg.c
  Author       : l47619
  Version      : V200R001
  Date         : 2005-08-30
  Description  : 该C文件给出了R_SM模块的实现
  Function List:
        1. NAS_RabmSmPdpActivateIndMsg
        2. NAS_RabmSmPdpDeactivateIndMsg
        3. NAS_RabmSmPdpModifyIndMsg

  History      :
  1. Date:2005-08-30
     Author: l47619
     Modification:create
  2. Date        : 2006-05-18
     Author      : l47619
     Modification: 根据问题单修改:A32D03487
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

/*lint -e958*/

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_RABM_DEALSMMSG_C

/*****************************************************************************
   2 全局变量定义
*****************************************************************************/

/*标识流量上报定时器是否启动*/
extern RABM_FLUX_WRITE_NV_TIMER_SWITCH_ENUM_U32  g_stRabmWriteFluxToNvTimerSwitch;



/*****************************************************************************
   3 函数实现
*****************************************************************************/

/*****************************************************************************
 Prototype      : NAS_RabmSmPdpActivateIndMsg()
 Description    : 处理SM 发送的PDP 激活消息
 Input          : pMsg                 PDP 激活消息指针
 Output         :
 Return Value   : 无
 Calls          :
 Called By      :
 History        :
  1.Date        : 2005-08-30
    Author      : l47619
    Modification: Created function

  2.日    期   : 2010年12月13日
    作    者   : lijun 00171473
    修改内容   : DTS2010112903583, 起个Timer, 流量数据每10分钟保存一次NV
                 PDP 激活时如果未起定时器则起定时器

  3.日    期   : 2011年12月19日
    作    者   : o00132663
    修改内容   : PS融合项目，PDP激活成功后调用CDS提供的流控接口将QOS信息通知-
                 CDS

  4.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : RABM保存的QOS由动态内存改为静态数组

  5.日    期   : 2014年7月29日
    作    者   : m00217266
    修改内容   : modify for DTS2014072803655,添加在等待第二条激活成功消息过来时，
                 进入suspend状态，在suspend状态收到第二条激活成功消息的处理
*****************************************************************************/
VOS_VOID  NAS_RabmSmPdpActivateIndMsg( VOS_VOID *pMsg )
{
    RABMSM_ACTIVATE_IND_STRU           *pstPdpActivateIndMsg;
    RABM_NSAPI_ENUM                     NsapiIndex;
    QCI_TYPE_ENUM_UINT8                 enQci;

    pstPdpActivateIndMsg = ( RABMSM_ACTIVATE_IND_STRU * )pMsg;

    if ( ( pstPdpActivateIndMsg->ulNsapi < RABM_MIN_NSAPI_NUMBER )
        || ( pstPdpActivateIndMsg->ulNsapi > RABM_MAX_NSAPI_NUMBER ) )
    {
        /*打印警告信息---入口消息非法:*/
        RABM_LOG_WARNING( "NAS_RabmSmPdpActivateIndMsg:WARNING:The NSAPI item of the Entry Parameter is BEYOND range!" );

        return;
    }

    if ( ( RABMSM_ACT_MSG_1 != pstPdpActivateIndMsg->ulActMsgType )
         && ( RABMSM_ACT_MSG_2 != pstPdpActivateIndMsg->ulActMsgType ) )
    {
        /*打印警告信息---入口消息中消息的标识非法:*/
        RABM_LOG1_WARNING( "NAS_RabmSmPdpActivateIndMsg:WARNING:The MsgType item of the Entry Parameter is ERROR!: NSAPI:", (VOS_INT32)(pstPdpActivateIndMsg->ulNsapi) );

        return;
    }

    NsapiIndex = ( RABM_NSAPI_ENUM )( pstPdpActivateIndMsg->ulNsapi - RABM_2G_NSAPI_OFFSET );

    switch ( gastRabm2GEntity[NsapiIndex].State )    /*该NSAPI所对应的状态*/
    {
        case RABM_2G_NULL:
            if ( RABMSM_ACT_MSG_1 == pstPdpActivateIndMsg->ulActMsgType )
            {
                /*打印流程信息---收到第一条PDP激活消息:*/
                RABM_LOG1_NORMAL( "NAS_RabmSmPdpActivateIndMsg:NORMAL:RECEIVE The FIRST PdpActivateInd Msg: NSAPI:", (VOS_INT32)(pstPdpActivateIndMsg->ulNsapi) );

                /*获取ucPppFlg:*/
                if( RABM_SM_PPP_PROT == pstPdpActivateIndMsg->ulPppFlag )
                {
                    gastRabm2GEntity[NsapiIndex].ucPppFlg = RABM_SM_PPP_PROT;
                }
                else
                {
                    gastRabm2GEntity[NsapiIndex].ucPppFlg = RABM_SM_IP_PROT;
                }

                return;
            }

            if ((RABMSM_ACT_MSG_2 == pstPdpActivateIndMsg->ulActMsgType)
             && (VOS_TRUE == NAS_RABM_GetDataSuspendFlg()))
            {
                /*打印流程信息---状态切换:*/
                RABM_LOG1_NORMAL( "STATE RABM_2G_NULL state CHANGE TO RABM_DATA_TRANS_STOP state: NSAPI:", (VOS_INT32)(pstPdpActivateIndMsg->ulNsapi) );

                /*将该NSAPI的状态置为RABM_DATA_TRANS_STOP:*/
                RABM_SetGState(NsapiIndex, RABM_DATA_TRANS_STOP);
            }
            else
            {
                /*启动Rabm.act.req.T1定时器:*/
                NAS_RabmStartTimer( ( RABM_TIMER_NAME_ENUM )NsapiIndex, RABM_TIMER_PARA_ACT_REQ_T1 );

                /*打印流程信息---启动了Rabm.act.req.T1定时器:*/
                RABM_LOG1_NORMAL( "NAS_RabmSmPdpActivateIndMsg:NORMAL:Start Rabm.act.req.T1 Timer SUCCESS: NSAPI:", (VOS_INT32)(pstPdpActivateIndMsg->ulNsapi) );

                /*将该NSAPI的状态置为RABM_NSAPI_OK_TRANSMODE_NO:*/
                RABM_SetGState(NsapiIndex, RABM_NSAPI_OK_TRANSMODE_NO);

                /*打印流程信息---状态切换:*/
                RABM_LOG1_NORMAL( "STATE RABM_2G_NULL state CHANGE TO RABM_NSAPI_OK_TRANSMODE_NO state: NSAPI:", (VOS_INT32)(pstPdpActivateIndMsg->ulNsapi) );
            }

            gastRabm2GEntity[NsapiIndex].stQos.ulQosLength = pstPdpActivateIndMsg->Qos.ulLength;
            PS_MEM_CPY(gastRabm2GEntity[NsapiIndex].stQos.aucQosValue,
                       pstPdpActivateIndMsg->Qos.aucQosValue,
                       NAS_RABM_MAX_QOS_LEN);

            /*创建RAB_MAP映射实体*/
            NAS_RABM_CreateRabMapEntity((VOS_UINT8)(pstPdpActivateIndMsg->ulNsapi),
                                        (VOS_UINT8)(pstPdpActivateIndMsg->ulLinkdNsapi),
                                        (VOS_UINT8)(pstPdpActivateIndMsg->ulNsapi));

            /* 给CDS发送消息通知CDS QOS信息 */
            enQci = NAS_RABM_GetQciFromQos(gastRabm2GEntity[NsapiIndex].stQos.ulQosLength,
                                           gastRabm2GEntity[NsapiIndex].stQos.aucQosValue);

            NAS_RABM_SndCdsQosFcRabCreateInd(NsapiIndex + RABM_NSAPI_OFFSET, enQci);
            break;
        case RABM_NSAPI_OK_TRANSMODE_NO:
        case RABM_DATA_TRANS_READY:
        case RABM_ROUT_AREA_UPDATE:
        case RABM_DATA_TRANS_STOP:                     /*激活此四种非空状态下的NSAPI，则只进行QoS的更新，故处理方式一样*/
            if ( RABMSM_ACT_MSG_1 == pstPdpActivateIndMsg->ulActMsgType )
            {
                /*打印流程信息---收到第一条PDP激活消息:*/
                RABM_LOG1_NORMAL( "NAS_RabmSmPdpActivateIndMsg:NORMAL:RECEIVE The FIRST PdpActivateInd Msg: NSAPI:", (VOS_INT32)(pstPdpActivateIndMsg->ulNsapi) );

                return;
            }

            /*打印流程信息---此时该NSAPI已激活，故更新Qos:*/
            RABM_LOG1_NORMAL( "NAS_RabmSmPdpActivateIndMsg:NORMAL:This NSAPI has been Activated,so UPDATE the QoS: NSAPI:", (VOS_INT32)(pstPdpActivateIndMsg->ulNsapi) );

            gastRabm2GEntity[NsapiIndex].stQos.ulQosLength = pstPdpActivateIndMsg->Qos.ulLength;
            PS_MEM_CPY(gastRabm2GEntity[NsapiIndex].stQos.aucQosValue,
                       pstPdpActivateIndMsg->Qos.aucQosValue,
                       NAS_RABM_MAX_QOS_LEN);

            break;
        default:
            /*打印出错信息---该NSAPI的状态字段出错:*/
            RABM_LOG1_ERROR( "NAS_RabmSmPdpActivateIndMsg:ERROR:This NSAPI's state is WRONG!: NSAPI:", (VOS_INT32)(pstPdpActivateIndMsg->ulNsapi) );
            break;
    }

    return;
}


/*****************************************************************************
 Prototype      : NAS_RabmSmPdpDeactivateIndMsg()
 Description    : 处理SM发送的PDP去激活消息
 Input          : pMsg                 PDP 去激活消息 指针
 Output         :
 Return Value   : 无
 Called By      :
 History        :
  1.Date        : 2005-08-30
    Author      : l47619
    Modification: Created function
  2.Date        : 2006-05-18
    Author      : l47619
    Modification: 根据问题单修改:A32D03487
  3.日    期   : 2010年12月13日
    作    者   : lijun 00171473
    修改内容   : DTS2010112903583, 起个Timer, 流量数据每10分钟保存一次NV
                 PDP去激活后停定时器, 写流量到NV

  4.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : RABM保存的QOS由动态内存改为静态数组
*****************************************************************************/
VOS_VOID  NAS_RabmSmPdpDeactivateIndMsg( VOS_VOID *pMsg )
{
    VOS_UINT8                            ucLoop;
    RABM_NSAPI_ENUM                      NsapiIndex;
    RABMSM_DEACTIVATE_IND_STRU          *pstPdpDeactiveIndMsg;

    pstPdpDeactiveIndMsg = ( RABMSM_DEACTIVATE_IND_STRU * )pMsg;

    if ( pstPdpDeactiveIndMsg->ulDeactiveNum > RABM_2G_MAX_ENT_NUM )
    {
        RABM_LOG_WARNING( "NAS_RabmSmPdpDeactivateIndMsg:WARNING:The DeactiveNum item of the Entry Parameter is BEYOND range!" );
        return;
    }

    for ( ucLoop = 0; ucLoop < pstPdpDeactiveIndMsg->ulDeactiveNum; ucLoop++ )/*遍历消息中指示的需去激活的NSAPI的个数*/
    {
        if ( ( pstPdpDeactiveIndMsg->aulNsapiList[ucLoop] < RABM_MIN_NSAPI_NUMBER )
             || ( pstPdpDeactiveIndMsg->aulNsapiList[ucLoop] > RABM_MAX_NSAPI_NUMBER ) )
        {
            /*打印警告信息---消息中的NSAPI不在范围之内:*/
            RABM_LOG1_WARNING( "NAS_RabmSmPdpDeactivateIndMsg:WARNING:The NSAPI item of the Entry Parameter is BEYOND range!: NSAPI:", (VOS_INT32)(pstPdpDeactiveIndMsg->aulNsapiList[ucLoop]) );
            continue;
        }

        NsapiIndex = ( RABM_NSAPI_ENUM )( pstPdpDeactiveIndMsg->aulNsapiList[ucLoop] - RABM_2G_NSAPI_OFFSET );

        switch ( gastRabm2GEntity[NsapiIndex].State )   /*该NSAPI所对应的状态*/
        {
            case RABM_2G_NULL:
                /*打印流程信息---状态不变:*/
                RABM_LOG1_NORMAL( "STATE RABM_2G_NULL state keep the same: NSAPI:", (VOS_INT32)(pstPdpDeactiveIndMsg->aulNsapiList[ucLoop]) );
                break;
            case RABM_NSAPI_OK_TRANSMODE_NO:
                if ( RABM_ACT_REQ_T1_ON == gaRabmActReqT1Switch[NsapiIndex] )   /*若打开了Rabm.act.req.T1定时器*/
                {
                    /*关闭Rabm.act.req.T1定时器:*/
                    NAS_RabmStopTimer( ( RABM_TIMER_NAME_ENUM )NsapiIndex, RABM_TIMER_PARA_ACT_REQ_T1 );
                }

                /*将该NSAPI的状态置为RABM_2G_NULL:*/
                RABM_SetGState(NsapiIndex, RABM_2G_NULL);
                /*打印流程信息---状态切换:*/
                RABM_LOG1_NORMAL( "STATE RABM_NSAPI_OK_TRANSMODE_NO state CHANGE TO RABM_2G_NULL state: NSAPI:", (VOS_INT32)(pstPdpDeactiveIndMsg->aulNsapiList[ucLoop]) );

                /*清空QoS:*/
                gastRabm2GEntity[NsapiIndex].stQos.ulQosLength = 0;
                PS_MEM_SET(gastRabm2GEntity[NsapiIndex].stQos.aucQosValue,
                           0x00,
                           sizeof(gastRabm2GEntity[NsapiIndex].stQos.aucQosValue));

                break;
            case RABM_ROUT_AREA_UPDATE:
                if ( RABM_NO == NAS_RabmQueryRAUState( NsapiIndex ) )
                {
                    if ( RABM_ROUTING_AREA_UPDATE_T1_ON == gRabmRAT1Switch )    /*若打开了rout.area.update.T1定时器*/
                    {
                        /*关闭rout.area.update.T1定时器:*/
                        NAS_RabmStopTimer( RABM_TIMER_NAME_COMMON, RABM_TIMER_PARA_ROUT_AREA_UPDATE_T1 );
                    }
                    else
                    {
                        if ( RABM_3G_TO_2G_T3_ON == gRabm3GTo2GT3Switch )         /*若打开了Rabm.sys.3To2.T3定时器*/
                        {
                            /*关闭Rabm.sys.3To2.T3定时器:*/
                            NAS_RabmStopTimer( RABM_TIMER_NAME_COMMON, RABM_TIMER_PARA_3_TO_2_T3 );
                        }
                    }
                }

                /*打印流程信息---状态切换:*/
                RABM_LOG1_NORMAL( "STATE RABM_ROUT_AREA_UPDATE state CHANGE TO RABM_2G_NULL state: NSAPI:", (VOS_INT32)(pstPdpDeactiveIndMsg->aulNsapiList[ucLoop]) );
                /*将该NSAPI的状态置为RABM_2G_NULL:*/
                RABM_SetGState(NsapiIndex, RABM_2G_NULL);

                /*清空QoS:*/
                gastRabm2GEntity[NsapiIndex].stQos.ulQosLength = 0;
                PS_MEM_SET(gastRabm2GEntity[NsapiIndex].stQos.aucQosValue,
                           0x00,
                           sizeof(gastRabm2GEntity[NsapiIndex].stQos.aucQosValue));

                break;
            case RABM_DATA_TRANS_READY:
                /*no break here*/
            case RABM_DATA_TRANS_STOP:
                /*打印流程信息---状态切换:*/
                if ( RABM_DATA_TRANS_READY == gastRabm2GEntity[NsapiIndex].State )
                {
                    RABM_LOG1_NORMAL( "STATE RABM_DATA_TRANS_READY state CHANGE TO RABM_2G_NULL state: NSAPI:", (VOS_INT32)(pstPdpDeactiveIndMsg->aulNsapiList[ucLoop]) );
                }
                else
                {
                    RABM_LOG1_NORMAL( "STATE RABM_DATA_TRANS_STOP state CHANGE TO RABM_2G_NULL state: NSAPI:", (VOS_INT32)(pstPdpDeactiveIndMsg->aulNsapiList[ucLoop]) );
                }
                /*将该NSAPI的状态置为RABM_2G_NULL:*/
                RABM_SetGState(NsapiIndex, RABM_2G_NULL);

                /*清空QoS:*/
                gastRabm2GEntity[NsapiIndex].stQos.ulQosLength = 0;
                PS_MEM_SET(gastRabm2GEntity[NsapiIndex].stQos.aucQosValue,
                           0x00,
                           sizeof(gastRabm2GEntity[NsapiIndex].stQos.aucQosValue));

                break;
            default:
                /*打印出错信息---该NSAPI所对应的状态字段出错:*/
                RABM_LOG1_ERROR( "NAS_RabmSmPdpDeactivateIndMsg:ERROR:This NSAPI's state is WRONG!: NSAPI:", (VOS_INT32)(pstPdpDeactiveIndMsg->aulNsapiList[ucLoop]) );
                /*将该NSAPI的状态置为RABM_2G_NULL:*/
                RABM_SetGState(NsapiIndex, RABM_2G_NULL);

                /*打印警告信息---将该状态出错的NSAPI的状态置为RABM_2G_NULL:*/
                RABM_LOG1_WARNING( "NAS_RabmSmPdpDeactivateIndMsg:WARNING:Set this NSAPI's state to RABM_2G_NULL!: NSAPI:", (VOS_INT32)(pstPdpDeactiveIndMsg->aulNsapiList[ucLoop]) );

                /*清空QoS:*/
                gastRabm2GEntity[NsapiIndex].stQos.ulQosLength = 0;
                PS_MEM_SET(gastRabm2GEntity[NsapiIndex].stQos.aucQosValue,
                           0x00,
                           sizeof(gastRabm2GEntity[NsapiIndex].stQos.aucQosValue));

                break;
        }

        /*删除RAB_MAP实体*/
        RABM_DelRabMap((VOS_UINT8)(pstPdpDeactiveIndMsg->aulNsapiList[ucLoop]));
    }

    return;
}



/*****************************************************************************
 Prototype      : NAS_RabmSmPdpModifyIndMsg()
 Description    : 处理SM发送的修改PDP消息
 Input          : pMsg                 修改PDP消息指针
 Output         :
 Return Value   : 无
 Calls          :
 Called By      :
 History        :
  1.Date        : 2005-09-13
    Author      : l47619
    Modification: Created function

  2.日    期   : 2011年12月19日
    作    者   : o00132663
    修改内容   : PS融合项目，PDP激活成功后调用CDS提供的流控接口将QOS信息通知-
                 CDS

  3.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : RABM保存的QOS由动态内存改为静态数组
*****************************************************************************/
VOS_VOID  NAS_RabmSmPdpModifyIndMsg( VOS_VOID *pMsg )
{
    RABMSM_MODIFY_IND_STRU             *pstPdpModifyIndMsg;
    RABM_NSAPI_ENUM                     NsapiIndex;
    QCI_TYPE_ENUM_UINT8                 enQci;

    pstPdpModifyIndMsg = ( RABMSM_MODIFY_IND_STRU * )pMsg;

    /*打印流程信息---收到消息:*/
    RABM_LOG1_NORMAL( "NAS_RabmSmPdpModifyIndMsg:NORMAL:RECEIVE RABMSM_MODIFY_IND Msg: NSAPI:", (VOS_INT32)(pstPdpModifyIndMsg->ulNsapi) );

    if ( ( pstPdpModifyIndMsg->ulNsapi < RABM_MIN_NSAPI_NUMBER )
         || ( pstPdpModifyIndMsg->ulNsapi > RABM_MAX_NSAPI_NUMBER ) )
    {
        /*打印警告信息---消息中的NSAPI不在范围之内:*/
        RABM_LOG1_WARNING( "NAS_RabmSmPdpModifyIndMsg:WARNING:The NSAPI item of the Entry Parameter is BEYOND range!: NSAPI:", (VOS_INT32)(pstPdpModifyIndMsg->ulNsapi) );

        return;
    }

    NsapiIndex = ( RABM_NSAPI_ENUM )( pstPdpModifyIndMsg->ulNsapi - RABM_2G_NSAPI_OFFSET );

    if ( ( gastRabm2GEntity[NsapiIndex].State >= RABM_NSAPI_OK_TRANSMODE_NO )
         && ( gastRabm2GEntity[NsapiIndex].State <= RABM_DATA_TRANS_STOP ) )
    {
        /*更新该NSAPI中的QoS参数:*/
        gastRabm2GEntity[NsapiIndex].stQos.ulQosLength = pstPdpModifyIndMsg->Qos.ulLength;
        PS_MEM_CPY(gastRabm2GEntity[NsapiIndex].stQos.aucQosValue,
                   pstPdpModifyIndMsg->Qos.aucQosValue,
                   NAS_RABM_MAX_QOS_LEN);

        /* 给CDS发送消息通知CDS QOS信息 */
        enQci = NAS_RABM_GetQciFromQos(gastRabm2GEntity[NsapiIndex].stQos.ulQosLength,
                                       gastRabm2GEntity[NsapiIndex].stQos.aucQosValue);

        NAS_RABM_SndCdsQosFcRabCreateInd(NsapiIndex + RABM_NSAPI_OFFSET, enQci);

    }
    else if ( RABM_2G_NULL == gastRabm2GEntity[NsapiIndex].State )
    {
        /*打印警告信息---该NSAPI未激活:*/
        RABM_LOG1_WARNING( "NAS_RabmSmPdpModifyIndMsg:WARNING:This NSAPI hasn't been activated!: NSAPI:", (VOS_INT32)(pstPdpModifyIndMsg->ulNsapi) );
    }
    else
    {
        /*打印错误信息---该NSAPI的状态出错:*/
        RABM_LOG1_ERROR( "NAS_RabmSmPdpModifyIndMsg:ERROR:This NSAPI's state is WRONG!: NSAPI:", (VOS_INT32)(pstPdpModifyIndMsg->ulNsapi) );
    }

    return;
}

/*lint +e958*/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
