/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : Rabm_DataAndFlux.c
  Author       : l47619
  Version      : V200R001
  Date         : 2005-08-30
  Description  : 该C文件给出了R_DataAndFlux模块的实现
  Function List:
        1. NAS_RabmAppDataTransReq
        2. NAS_RabmSnDataReq
        5. Taf_RabmFlowClear
        6. NAS_RabmFlowClearTotal
        7. NAS_RabmFlowClearWithRabId
        8. Taf_RabmFlowQuery
        9. NAS_RabmFlowQueryAccumulate
        10.NAS_RabmFlowQueryWithRabId
        11.NAS_RabmFlowQueryTotal
        12.NAS_RabmFlowReport
        13.NAS_RabmFlowReportAccumulate
        14.NAS_RabmFlowReportWithRabId
        15.NAS_RabmFlowReportTotal
        16.NAS_RabmSetFlowReportMode
        17.Taf_RabmStartFlowReport
        18.Taf_RabmStopFlowReport
        19.NAS_RabmCalculateFluxRate
        20.NAS_Rabm64BitsDivide32Bits

  History      :
  1. Date:2005-08-30
     Author: l47619
     Modification:create
  2.Date        : 2006-03-08
    Author      : l47619
    Modification: 问题单: A32D02344
  3.Date        : 2006-05-05
    Author      : l47619
    Modification: 问题单: A32D03487
  4.Date        : 2007-10-16
    Author      : F62575
    Modification: 问题单A32D13062(文档校对发现问题)
************************************************************************/

/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "Rabm2GInclude.h"
#include "NasRabmMain.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_RABM_DATAANDFLUX_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/*****************************************************************************
   2 全局变量定义
*****************************************************************************/


/*****************************************************************************
   3 函数实现
*****************************************************************************/




/*****************************************************************************
 Prototype      : NAS_RabmAppDataTransReq()
 Description    : APP调用此函数发送上行数据，RABM根据当前系统进行选择:
                  若为3G，则调用3G中的Api_AppRabmDataReq()函数进行处理；
                  若为2G, 则调用SNDCP 提供的函数进行处理。
 Input          : pRabmDataReq        上行用户面数据结构体指针
 Output         :
 Return Value   : 无
 Calls          :
 Called By      :
 History        :
  1.Date        : 2005-08-30
    Author      : l47619
    Modification: Created function
  2.Date        : 2006-05-05
    Author      : l47619
    Modification: 根据问题单修改:A32D03487

  3.日    期   : 2010年4月22日
    作    者   : o00132663
    修改内容   : AT2D18350, GCF 14.2.4 环回测试失败
*****************************************************************************/
VOS_VOID  NAS_RabmAppDataTransReq( ST_APP_RABM_DATA  *pRabmDataReq )
{
    TTF_MEM_ST * pstData;

    /*检查入口参数是否合法:*/
    if ( VOS_NULL_PTR == pRabmDataReq )
    {
        /*打印警告信息---入口参数非法:*/
        RABM_LOG_WARNING( "NAS_RabmAppDataTransReq:WARNING:Entry Pointer is NULL!" );
        return;
    }

    if ( VOS_NULL_PTR == pRabmDataReq->pucData )
    {
        /*打印警告信息---入口参数中的指针为空:*/
        RABM_LOG_WARNING( "NAS_RabmAppDataTransReq:WARNING:The pucData Pointer item of the Entry Parameter is NULL!" );
        return;
    }

    if( pRabmDataReq->ucDomain == D_RABM_PS_DOMAIN )
    {
        if ( ( pRabmDataReq->ucRabId < RABM_MIN_NSAPI_NUMBER )
             || ( pRabmDataReq->ucRabId > RABM_MAX_NSAPI_NUMBER ) )
        {
            /*打印警告信息---入口参数中的RABID超出范围:*/
            RABM_LOG_WARNING( "NAS_RabmAppDataTransReq:WARNING:The NSAPI item of the Entry Parameter is BEYOND range!" );
            return;
        }
    }

    if ( ( pRabmDataReq->ucDomain != D_RABM_CS_DOMAIN )
        && ( pRabmDataReq->ucDomain != D_RABM_PS_DOMAIN ) )
    {
        /*打印警告信息---入口参数中的CN域字段不正确:*/
        RABM_LOG_WARNING( "NAS_RabmAppDataTransReq:WARNING:The DOMAIN item of the Entry Parameter is Error!" );
        return;
    }

    if (D_RABM_CS_DOMAIN == pRabmDataReq->ucDomain)     /*CS域数据*/
    {
        /*执行3G中CS域数据发送操作(该函数将数据打包，以消息形式发送给RABM):*/
        if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_RABM_GetCurrentSysMode())
        {
            Api_AppRabmDataReq(pRabmDataReq);
            return;
        }
        else
        {
            /*打印警告信息---2G模式下，RABM不处理CS域数据:*/
            RABM_LOG_WARNING( "NAS_RabmAppDataTransReq:WARNING:RABM doesn't process CS Domain data in 2G mode!" );
            return;
        }
    }

    /*将线性内存转换为零拷贝内存*/
    pstData = TTF_MemBlkCopyAlloc(WUEPS_PID_RABM, TTF_MEM_POOL_ID_UL_RLC_SDU, pRabmDataReq->pucData, (VOS_UINT16)pRabmDataReq->ulDataLen);
    if(VOS_NULL_PTR == pstData)
    {
        RABM_LOG_ERROR( "NAS_RabmAppDataTransReq:ERROR:The Alloc TTF mem fail!" );
        return;
    }

    /*发送上行数据(GNA/API等应用)*/
    RABM_SendUlData(pRabmDataReq->ucRabId, pstData);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_RabmRcvTafGprsPsDataReq
 功能描述  : RABM处理APP发送的上行数据消息RABM_TAF_GPRS_PS_DATA_REQ_MSG_TYPE
 输入参数  : TAFRABM_PS_DATA_REQ_STRU *pPsDataReqMsg - 上行用户面数据消息指针
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年03月06日
    作    者   : L47619
    修改内容   : 新生成函数

  2.日    期   : 2010年11月26日
    作    者   : A00165503
    修改内容   : 问题单号: DTS2010112505628
                 G下数传过程中进行语音业务，语音业务结束后，数传概率性恢复慢
  3.日    期   : 2011年12月8日
    作    者   : s46746
    修改内容   : 问题单号：DTS2011111603445,接收到系统消息而且层2已经指派后才能恢复RABM

*****************************************************************************/
VOS_VOID  NAS_RabmRcvTafGprsPsDataReq(TAFRABM_PS_DATA_REQ_STRU *pPsDataReqMsg)
{
    RABM_NSAPI_ENUM                     NsapiIndex;
    ST_APP_RABM_ERROR                   stReportError;
    ST_APP_RABM_STATUS                  stReportStatus;

    /*检查入口参数是否合法:*/
    if ( VOS_NULL_PTR == pPsDataReqMsg )
    {
        /*打印警告信息---入口参数非法:*/
        RABM_LOG_WARNING( "NAS_RabmRcvTafGprsPsDataReq:WARNING:Entry Pointer is NULL!" );
        return;
    }

    if ( VOS_NULL_PTR == pPsDataReqMsg->pData )
    {
        /*打印警告信息---入口参数中的指针为空:*/
        RABM_LOG_WARNING( "NAS_RabmRcvTafGprsPsDataReq:WARNING:The pstData Pointer item of the Entry Parameter is NULL!" );
        return;
    }

    NsapiIndex = ( RABM_NSAPI_ENUM )( pPsDataReqMsg->ulNsapi - RABM_2G_NSAPI_OFFSET );

    switch ( gastRabm2GEntity[NsapiIndex].State )
    {
        case RABM_2G_NULL:
            /*打印警告信息---此时不能传输用户面数据:*/
            RABM_LOG1_WARNING( "NAS_RabmRcvTafGprsPsDataReq:WARNING:RABM_2G_NULL state CAN'T send user data!: NSAPI:", (VOS_INT32)pPsDataReqMsg->ulNsapi );

            /*RABM向APP上报出错信息:*/
            stReportError.ucDomain  = D_RABM_PS_DOMAIN;
            stReportError.ucRabId   = (VOS_UINT8)(pPsDataReqMsg->ulNsapi);
            stReportError.ucErrType = TAF_DATA_CAUSE_LOWLAYER_INDICATION;
            Api_AppRabmErrInd( &stReportError );
            /*打印流程信息---上报了出错信息:*/
            RABM_LOG1_NORMAL( "NAS_RabmRcvTafGprsPsDataReq:NORMAL:Report ERROR info to APP!: NSAPI:", (VOS_INT32)pPsDataReqMsg->ulNsapi );

            /*直接丢弃该上行数据块:*/
            TTF_MemFree(WUEPS_PID_RABM, pPsDataReqMsg->pData);
            return;
        case RABM_NSAPI_OK_TRANSMODE_NO:
            /*打印警告信息---此时不能传输用户面数据:*/
            RABM_LOG1_WARNING( "NAS_RabmRcvTafGprsPsDataReq:WARNING:RABM_NSAPI_OK_TRANSMODE_NO state CAN'T send user data!: NSAPI:", (VOS_INT32)pPsDataReqMsg->ulNsapi );

            /*RABM向APP上报出错信息:*/
            stReportError.ucDomain  = D_RABM_PS_DOMAIN;
            stReportError.ucRabId   = (VOS_UINT8)(pPsDataReqMsg->ulNsapi);
            stReportError.ucErrType = TAF_DATA_CAUSE_NO_TRANSMODE;
            Api_AppRabmErrInd( &stReportError );
            /*打印流程信息---上报了出错信息:*/
            RABM_LOG1_NORMAL( "NAS_RabmRcvTafGprsPsDataReq:NORMAL:Report ERROR info to APP!: NSAPI:", (VOS_INT32)pPsDataReqMsg->ulNsapi );

            /*直接丢弃该上行数据块:*/
            TTF_MemFree(WUEPS_PID_RABM, pPsDataReqMsg->pData);
            return;
        case RABM_ROUT_AREA_UPDATE:
            if ( ( RABM_RA_UPDATE_CAUSE_NORMAL != gastRabm2GEntity[NsapiIndex].RAUpdateCause )
                 && ( RABM_RA_UPDATE_CAUSE_3G_TO_2G != gastRabm2GEntity[NsapiIndex].RAUpdateCause ) )
            {
                /*打印警告信息---路由区更新原因值出错:*/
                RABM_LOG1_WARNING( "NAS_RabmRcvTafGprsPsDataReq:WARNING:RA update cause is ERROR!: NSAPI:", (VOS_INT32)pPsDataReqMsg->ulNsapi );

                /*打印警告信息---此时不能传输用户面数据:*/
                RABM_LOG1_WARNING( "NAS_RabmRcvTafGprsPsDataReq:WARNING:RABM_ROUT_AREA_UPDATE(RA update cause is ERROR) state CAN'T send user data!: NSAPI:", (VOS_INT32)pPsDataReqMsg->ulNsapi );

                /*RABM向APP上报出错信息:*/
                stReportError.ucDomain  = D_RABM_PS_DOMAIN;
                stReportError.ucRabId   = (VOS_UINT8)(pPsDataReqMsg->ulNsapi);
                stReportError.ucErrType = TAF_DATA_CAUSE_LOWLAYER_INDICATION;
                Api_AppRabmErrInd( &stReportError );
                /*打印流程信息---上报了出错信息:*/
                RABM_LOG1_NORMAL( "NAS_RabmRcvTafGprsPsDataReq:NORMAL:Report ERROR info to APP!: NSAPI:", (VOS_INT32)pPsDataReqMsg->ulNsapi );

                /*直接丢弃该上行数据块:*/
                TTF_MemFree(WUEPS_PID_RABM, pPsDataReqMsg->pData);
                return;
            }

            if ( RABM_RA_UPDATE_CAUSE_3G_TO_2G == gastRabm2GEntity[NsapiIndex].RAUpdateCause )
            {
                /*打印警告信息---此时不能传输用户面数据:*/
                RABM_LOG1_WARNING( "NAS_RabmRcvTafGprsPsDataReq:WARNING:RABM_ROUT_AREA_UPDATE(RA update cause is RABM_RA_UPDATE_CAUSE_3G_TO_2G)state CAN'T send user data!: NSAPI:", (VOS_INT32)pPsDataReqMsg->ulNsapi );

                /*RABM向APP上报出错信息:*/
                stReportError.ucDomain  = D_RABM_PS_DOMAIN;
                stReportError.ucRabId   = (VOS_UINT8)(pPsDataReqMsg->ulNsapi);
                stReportError.ucErrType = TAF_DATA_CAUSE_3G_TO_2G_RA_UPDATE;
                Api_AppRabmErrInd( &stReportError );
                /*打印流程信息---上报了出错信息:*/
                RABM_LOG1_NORMAL( "NAS_RabmRcvTafGprsPsDataReq:NORMAL:Report ERROR info to APP!: NSAPI:", (VOS_INT32)pPsDataReqMsg->ulNsapi );

                /*直接丢弃该上行数据块:*/
                TTF_MemFree(WUEPS_PID_RABM, pPsDataReqMsg->pData);
                return;
            }

            /*2G中的路由区更新，调用上行数据发送接口:*/
            (VOS_VOID)RABM_SndSndcpUlDataCallBack((VOS_UINT8)(pPsDataReqMsg->ulNsapi),
                                        (VOS_UINT8)(pPsDataReqMsg->ulNsapi),
                                        pPsDataReqMsg->pData);

            break;

        case RABM_DATA_TRANS_STOP:
            /*向APP上报TAFRABM_STARTSTOP_IND(STOP)消息:*/
            stReportStatus.ucDomain     = D_RABM_PS_DOMAIN;
            stReportStatus.ucRabId      = (VOS_UINT8)(pPsDataReqMsg->ulNsapi);
            stReportStatus.ucStatus     = TAF_RABM_STOP_DATA;
            stReportStatus.ucStartCause = TAF_RABM_STOP_CAUSE_NORMAL;
            Api_AppRabmStatusInd( &stReportStatus );             /*通知APP停止数据传输*/
            /*打印流程信息---上报了消息:*/
            RABM_LOG1_NORMAL( "STATE RABM_DATA_TRANS_STOP state report TAFRABM_STARTSTOP_IND(STOP) msg to APP: NSAPI:", (VOS_INT32)pPsDataReqMsg->ulNsapi );

            /*直接丢弃该上行数据块:*/
            TTF_MemFree(WUEPS_PID_RABM, pPsDataReqMsg->pData);

            break;

        case RABM_DATA_TRANS_READY:
            /*打印警告信息---该状态下RABM收到数据是异常的:*/
            RABM_LOG1_WARNING( "NAS_RabmRcvTafGprsPsDataReq:WARNING:RABM RCV UL Data in RABM_DATA_TRANS_READY State Is Abnormal!: NSAPI:", (VOS_INT32)pPsDataReqMsg->ulNsapi );

            /*直接丢弃该上行数据块:*/
            TTF_MemFree(WUEPS_PID_RABM, pPsDataReqMsg->pData);
            break;
        default:
            /*打印出错信息---该NSAPI所对应的状态出错:*/
            RABM_LOG1_ERROR( "NAS_RabmRcvTafGprsPsDataReq:ERROR:This NSAPI's state is WRONG!: NSAPI:", (VOS_INT32)pPsDataReqMsg->ulNsapi );

            /*直接丢弃该上行数据块:*/
            TTF_MemFree(WUEPS_PID_RABM, pPsDataReqMsg->pData);
            break;
    }
}


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
