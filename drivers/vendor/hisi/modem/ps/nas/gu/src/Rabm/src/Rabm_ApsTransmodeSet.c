/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : Rabm_ApsTransmodeSet.c
  Author       : l47619
  Version      : V200R001
  Date         : 2005-08-30
  Description  : 该C文件给出了R_APS模块的实现
  Function List:
        1.NAS_RabmSetTransMode
        2.NAS_RabmTransModeError

  History      :
  1. Date:2005-08-30
     Author: l47619
     Modification:create

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
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_RABM_APSTRANSMODESET_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/*****************************************************************************
   2 全局变量定义
*****************************************************************************/


/*****************************************************************************
   3 函数实现
*****************************************************************************/

/*****************************************************************************
 Prototype      : NAS_RabmSetTransMode()
 Description    : APS设置RABM数据传输模式
 Input          : pSetTransMode        传输模式入口指针
 Output         :
 Return Value   : VOID
 Calls          :
 Called By      :
 History        :
  1.Date        : 2005-08-30
    Author      : l47619
    Modification: Created function

  2.日    期   : 2011年12月23日
    作    者   : o00132663
    修改内容   : PS融合项目，通知CDS可以发送数据
  3.日    期   : 2013年04月12日
    作    者   : l65478
    修改内容   : DTS2013031901654:彩信并发发送失败
*****************************************************************************/
VOS_VOID  NAS_RabmSetTransMode( RABM_APS_SET_TRANS_MODE_ST   *pSetTransMode )
{
    RABM_TRANSMODE_LEGITIMACY_ENUM      LegitimacyFlag = RABM_TRANSMODE_LEGAL;             /*入口参数的传输模式字段合法性标记*/
    RABM_NSAPI_ENUM                     NsapiIndex;

    /*检查入口参数是否合法:*/
    if ( VOS_NULL_PTR == pSetTransMode )
    {
        /*打印警告信息---入口指针为空:*/
        RABM_LOG_WARNING( "NAS_RabmSetTransMode:WARNING:Entry Pointer is NULL!" );
        return;
    }

    if ( ( pSetTransMode->ucNsapi < RABM_MIN_NSAPI_NUMBER )
         || ( pSetTransMode->ucNsapi > RABM_MAX_NSAPI_NUMBER ) )
    {
        /*打印警告信息---入口参数的NSAPI超出范围:*/
        RABM_LOG_WARNING( "NAS_RabmSetTransMode:WARNING:The NSAPI of the Input Parameter is BEYOND range!" );
        return;
    }

    /*打印流程信息---设置传输模式:*/
    RABM_LOG1_NORMAL( "NAS_RabmSetTransMode:NORMAL:Set Transmode: NSAPI:", pSetTransMode->ucNsapi );

    if ( ( RABM_ABM_ENUM != pSetTransMode->TransMode )
         && ( RABM_ADM_ENUM != pSetTransMode->TransMode ) )        /*传输模式参数不合法*/
    {
        LegitimacyFlag = RABM_TRANSMODE_ILLEGAL;
        /*打印警告信息---传输模式参数不合法:*/
        RABM_LOG1_WARNING( "NAS_RabmSetTransMode:WARNING:The Transmode of the Input Parameter is ILLEGAL!: NSAPI:", pSetTransMode->ucNsapi );
    }

    NsapiIndex = ( RABM_NSAPI_ENUM )( pSetTransMode->ucNsapi - RABM_2G_NSAPI_OFFSET );

    switch ( gastRabm2GEntity[NsapiIndex].State )    /*指定的NSAPI所对应的RABM实体的状态*/
    {
        case RABM_2G_NULL:
            /*打印警告信息---不合逻辑的事件:*/
            RABM_LOG1_WARNING( "NAS_RabmSetTransMode:WARNING:RABM_2G_NULL State CAN'T set Transmode!: NSAPI:", pSetTransMode->ucNsapi );
            return;
        case RABM_NSAPI_OK_TRANSMODE_NO:
            if ( RABM_ACT_REQ_T1_ON == gaRabmActReqT1Switch[NsapiIndex] )    /*若打开了Rabm.act.req.T1定时器*/
            {
                /*关闭Rabm.act.req.T1定时器:*/
                NAS_RabmStopTimer( ( RABM_TIMER_NAME_ENUM )NsapiIndex, RABM_TIMER_PARA_ACT_REQ_T1 );
            }

            if ( RABM_TRANSMODE_ILLEGAL == LegitimacyFlag )                /*传输模式不合法*/
            {
                NAS_RabmTransModeError( pSetTransMode->ucNsapi );

                /*打印流程信息---设置为非确认模式:*/
                RABM_LOG1_NORMAL( "NAS_RabmSetTransMode:NORMAL:Transmode set to ADM: NSAPI:", pSetTransMode->ucNsapi );

                /*进入RABM-DATA-TRANS-READY状态:*/
                RABM_SetGState(NsapiIndex,RABM_DATA_TRANS_READY);
                /*打印流程信息---状态切换:*/
                RABM_LOG1_NORMAL( "STATE RABM_NSAPI_OK_TRANSMODE_NO state CHANGE TO RABM_DATA_TRANS_READY state: NSAPI:", pSetTransMode->ucNsapi );
            }
            else
            {
                gastRabm2GEntity[NsapiIndex].TransMode = pSetTransMode->TransMode; /*设置TRANSMODE*/

                if ( RABM_ABM_ENUM == pSetTransMode->TransMode )
                {
                    /*打印流程信息---设置为确认模式:*/
                    RABM_LOG1_NORMAL( "NAS_RabmSetTransMode:NORMAL:Transmode set to ABM: NSAPI:", pSetTransMode->ucNsapi );
                }
                else
                {
                    /*打印流程信息---设置为非确认模式:*/
                    RABM_LOG1_NORMAL( "NAS_RabmSetTransMode:NORMAL:Transmode set to ADM: NSAPI:", pSetTransMode->ucNsapi );
                }

                /*进入RABM-DATA-TRANS-READY状态:*/
                RABM_SetGState(NsapiIndex,RABM_DATA_TRANS_READY);

                /*打印流程信息---状态切换:*/
                RABM_LOG1_NORMAL( "STATE RABM_NSAPI_OK_TRANSMODE_NO state CHANGE TO RABM_DATA_TRANS_READY state: NSAPI:", pSetTransMode->ucNsapi );
            }


            /* 通知CDS可以发送数据 */
            NAS_RABM_SndCdsSendBuffDataInd(pSetTransMode->ucNsapi,
                                           CDS_RABM_SEND_BUFF_DATA_ALLOWED_TYPE_SERVICE_SUCC);



            break;
        case RABM_ROUT_AREA_UPDATE:
            /*打印警告信息---不合逻辑的事件:*/
            RABM_LOG1_WARNING( "NAS_RabmSetTransMode:WARNING:RABM_ROUT_AREA_UPDATE State CAN'T set Transmode!: NSAPI:", pSetTransMode->ucNsapi );
            return;
        case RABM_DATA_TRANS_READY:
        case RABM_DATA_TRANS_STOP:                          /*这两种状态下，发生了PDP修改，处理一样*/
            if ( RABM_TRANSMODE_ILLEGAL == LegitimacyFlag ) /*传输模式不合法*/
            {
                NAS_RabmTransModeError( pSetTransMode->ucNsapi );
                /*打印流程信息---修改为非确认模式:*/
                RABM_LOG1_NORMAL( "NAS_RabmSetTransMode:NORMAL:Transmode modify to ADM: NSAPI:", pSetTransMode->ucNsapi );
            }
            else
            {
                gastRabm2GEntity[NsapiIndex].TransMode = pSetTransMode->TransMode; /*设置TRANSMODE*/

                if ( RABM_ABM_ENUM == pSetTransMode->TransMode )
                {
                    /*打印流程信息---修改为确认模式:*/
                    RABM_LOG1_NORMAL( "NAS_RabmSetTransMode:NORMAL:Transmode modify to ABM: NSAPI:", pSetTransMode->ucNsapi );
                }
                else
                {
                    /*打印流程信息---修改为非确认模式:*/
                    RABM_LOG1_NORMAL( "NAS_RabmSetTransMode:NORMAL:Transmode modify to ADM: NSAPI:", pSetTransMode->ucNsapi );
                }
            }
            break;
        default:
            /*打印出错信息---该NSAPI所对应的状态出错:*/
            RABM_LOG1_ERROR( "NAS_RabmSetTransMode:ERROR:This NSAPI's state is WRONG!: NSAPI:", pSetTransMode->ucNsapi );
            return;
    }
}



/*****************************************************************************
 Prototype      : NAS_RabmTransModeError()
 Description    : 设置传输模式时，入口参数中传输模式字段出错的处理
 Input          : ucNsapi         指定的NSAPI
 Output         :
 Return Value   : 无
 Calls          :
 Called By      :
 History        :
  1.Date        : 2005-08-30
    Author      : l47619
    Modification: Created function
*****************************************************************************/
VOS_VOID    NAS_RabmTransModeError( VOS_UINT8  ucNsapi )
{
    RABM_NSAPI_ENUM                     NsapiIndex;

    NsapiIndex = ( RABM_NSAPI_ENUM )( ucNsapi - RABM_2G_NSAPI_OFFSET );
    /*将该NSAPI设置为非确认模式:*/
    gastRabm2GEntity[NsapiIndex].TransMode = RABM_ADM_ENUM;
}

/*lint +e958*/


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
