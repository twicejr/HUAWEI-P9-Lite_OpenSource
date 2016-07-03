/******************************************************************************/
/* Copyright (c) ,1988-2001,Huawei Tech. Co.,Ltd                              */
/* File name     :Taf_Tafm_Applocal.c                                               */
/* Author        :zzy                                                         */
/* Description   :1、TAF-APP本端API                                           */
/*                2、TAF-MUX本端回调API                                       */
/* Others        :                                                            */
/* Function List :                                                            */
/* History       :                                                            */
/*               :2005-04-13 初稿                                             */
/*               :2005-10-07 增加获取当前ATTACH，DETACH状态函数，修改人:刘飏  */
/******************************************************************************/

#include "Taf_Tafm_Remote.h"
#include "ExtAppRabmInterface.h"
#include "MmaAppLocal.h"
#include "TafClientApi.h"
#include "TafApsApi.h"
#include "TafAppRabm.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_TAFM_APPLOCAL_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/


VOS_UINT32   g_enClientIdRegChk = TAF_TRUE;

/*数传接口RabId与ClientId对应表*/
VOS_UINT16 g_CsRabToClientId[TAF_MAX_RABID + 1] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

VOS_UINT16 g_PsRabToClientId[TAF_MAX_RABID + 1] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};





VOS_VOID Api_AppRabmDataInd(ST_APP_RABM_DATA *p)
{
    /* 对g_stMnCallBackFunc[i].regFunc.pDataIndFunc回调的清理 */
#if 0
    VOS_UINT16 ClientId;
    VOS_UINT8 i;

    if (VOS_NULL_PTR == p)
    {
        TAF_LOG( WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING, "Api_AppRabmDataInd:WARNING:p is null ptr." );
        return;
    }
    if ((p->ucDomain > TAF_DATA_PS_DOMAIN) ||
        (p->ucRabId > TAF_MAX_RABID))
    {
        TAF_LOG( WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING, "Api_AppRabmDataInd:WARNING:Domain or RabId value is error." );
        return;
    }

    /*ClientId*/
    if (TAF_DATA_CS_DOMAIN == p->ucDomain)
    {
        ClientId = g_CsRabToClientId[p->ucRabId];
    }
    else
    {
        ClientId = g_PsRabToClientId[p->ucRabId];
    }

    for (i = 0; i < TAF_MAX_CLIENT_OF_ONE_PROC; i++)
    {   /*查找匹配的ClientId表项*/
        if ((TAF_USED == g_stMnCallBackFunc[i].ucUsed) &&
            (ClientId == g_stMnCallBackFunc[i].clientId ))
        {
            break;
        }
    }
    if(i >= TAF_MAX_CLIENT_OF_ONE_PROC)
    {
        TAF_LOG( WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING, "Api_AppRabmDataInd:WARNING:Can't find match ClientId." );
        return;/*未找到ClientId*/
    }

    if ( VOS_NULL_PTR == g_stMnCallBackFunc[i].regFunc.pDataIndFunc )
    {
        TAF_LOG1( WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING, "Api_AppRabmDataInd:WARNING:Function Pointer is NULL! g_stMnCallBackFunc array index:", i );
        return;
    }

    (*g_stMnCallBackFunc[i].regFunc.pDataIndFunc)
                    (ClientId, p->ucDomain, p->ucRabId, p->ulDataLen, p->pucData);

#endif
    return;
}


VOS_VOID Api_AppRabmStatusInd(ST_APP_RABM_STATUS *p)
{
#if 0
    VOS_UINT16 ClientId;

    if (VOS_NULL_PTR == p)
    {
        TAF_LOG( WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING, "Api_AppRabmStatusInd:WARNING:p is null ptr." );
        return;
    }
    if ((p->ucDomain > TAF_DATA_PS_DOMAIN) ||
        (p->ucRabId > TAF_MAX_RABID))
    {
        TAF_LOG( WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING, "Api_AppRabmStatusInd:WARNING:Domain or RabId value is error." );
        return;
    }

    /*ClientId*/
    if (TAF_DATA_CS_DOMAIN == p->ucDomain)
    {
        ClientId = g_CsRabToClientId[p->ucRabId];
    }
    else
    {
        ClientId = g_PsRabToClientId[p->ucRabId];
    }

    /*调用APP数传状态上报函数*/
    MN_DATASTATUS_SendMsg(ClientId, p->ucDomain, p->ucRabId, p->ucStatus, p->ucStartCause);
#endif
    return;
}


VOS_VOID Api_AppRabmErrInd(ST_APP_RABM_ERROR *p)
{
    VOS_UINT16 ClientId;

    if (VOS_NULL_PTR == p)
    {
        TAF_LOG( WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING, "Api_AppRabmErrInd:WARNING:p is null ptr." );
        return;
    }
    if ((p->ucDomain > TAF_DATA_PS_DOMAIN) ||
        (p->ucRabId > TAF_MAX_RABID))
    {
        TAF_LOG( WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING, "Api_AppRabmErrInd:WARNING:Domain or RabId value is error." );
        return;
    }

    /*ClientId*/
    if (TAF_DATA_CS_DOMAIN == p->ucDomain)
    {
        ClientId = g_CsRabToClientId[p->ucRabId];
    }
    else
    {
        ClientId = g_PsRabToClientId[p->ucRabId];
    }

    /*调用APP数传状态上报函数*/
    MN_DATASTATUS_SendMsg(ClientId, p->ucDomain, p->ucRabId, TAF_DATA_STOP, p->ucErrType);

    return;
}




#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

