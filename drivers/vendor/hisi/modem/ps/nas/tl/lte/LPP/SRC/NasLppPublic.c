/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasLppPublic.c
    Description : LPP的公共处理
    History     :
    1. lifuxin 00253982 2015-7-7  新开发
******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/

#include    "PsCommonDef.h"
#include    "PsTypeDef.h"
#include    "OmCommon.h"
#include    "NasLppOm.h"
#include    "NasLppPublic.h"
#include    "NasCommPrint.h"
#include    "LNasNvInterface.h"
#include    "LNvCommon.h"
#include    "PsLogdef.h"
#include    "NasLppTimerMsgProc.h"
#include    "NasLppSendMsg.h"
#include    "NasLppIntraInterface.h"


#define    THIS_FILE_ID            PS_FILE_ID_NASLPPPUBLIC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLPPPUBLIC_C
/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (FEATURE_LPP == FEATURE_ON)


/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
NAS_LPP_ENTITY_STRU     g_stNasLppEntity; /*LPP 实体定义*/
LPP_MESSAGE_STRU        stLppMsgBuff;


/*状态机的定时器的函数表*/
NAS_LPP_TIMER_PROC_FUNC g_afNasLppTimerFun[TI_NAS_LPP_TIMER_PARA_BUTT] = {0};

/* 状态定时器的长度。周期定时器的长度分别放到transaction或seesion里*/
VOS_UINT32 g_aulTimerLen[TI_NAS_LPP_STATE_TIMER_MAX_NUM] = {0};



/*****************************************************************************
  3 Function
*****************************************************************************/
/*lint -e701*/


VOS_VOID  NAS_LPP_ReadLppNvConfig( VOS_VOID)
{
    LNAS_LPP_NV_CONFIG_PARA_STRU        stNvLppConfig;
    VOS_UINT32                          ulRslt;
    NAS_LPP_NV_CONFIG_STRU             *pstLppNvParaConfig = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_ReadLppNvConfig enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_ReadLppNvConfig_ENUM, LNAS_LPP_ReadLppNvConfigEnter);
    pstLppNvParaConfig = NAS_LPP_GetLppNvParaConfig();

    ulRslt = LPP_NV_Read(EN_NV_ID_LPP_PARA_CONFIG, &stNvLppConfig,\
                 sizeof(LNAS_LPP_NV_CONFIG_PARA_STRU));

    if(ulRslt == VOS_OK)
    {
        /*根据NV内容设置*/
        pstLppNvParaConfig->usAttempeTransCnt  = stNvLppConfig.usAttempeTransCnt;
        NAS_LPP_ModifyTimerLen(TI_NAS_LPP_UPLINK_MSG_RETRANS,
                               PS_NULL_UINT8,
                               PS_NULL_UINT8,
                               stNvLppConfig.usReTransTimerLen);
        pstLppNvParaConfig->usReTransTimerLen   = stNvLppConfig.usReTransTimerLen;
        pstLppNvParaConfig->ucLppLayerSwitch    = stNvLppConfig.ucLppLayerSwitch;
        pstLppNvParaConfig->ucLppLayerNorm      = stNvLppConfig.ucLppLayerNorm;
        pstLppNvParaConfig->ucLppLayerInfo      = stNvLppConfig.ucLppLayerInfo;
        pstLppNvParaConfig->ucLppLayerWarn      = stNvLppConfig.ucLppLayerWarn;
        pstLppNvParaConfig->ucLppLayerErr       = stNvLppConfig.ucLppLayerErr;
    }
    else
    {
        NAS_LPP_WARN_LOG("NAS_LPP_ReadLppNvConfig, Read NV Err.");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_ReadLppNvConfig_ENUM, LNAS_LPP_ReadLppNvConfigReadNVError);
        /*读NV不成功，设置初始值*/
        pstLppNvParaConfig->usAttempeTransCnt  = 3; /*默认上行消息传输三次不成功，则不再尝试*/
        NAS_LPP_ModifyTimerLen(TI_NAS_LPP_UPLINK_MSG_RETRANS,
                               PS_NULL_UINT8,
                               PS_NULL_UINT8,
                               250);/*重传定时器时长，默认配置250ms*/
        pstLppNvParaConfig->usReTransTimerLen   = 250;
        pstLppNvParaConfig->ucLppLayerSwitch    = NAS_LPP_SLCT;
        pstLppNvParaConfig->ucLppLayerNorm      = NAS_LPP_NO_SLCT;
        pstLppNvParaConfig->ucLppLayerInfo      = NAS_LPP_NO_SLCT;
        pstLppNvParaConfig->ucLppLayerWarn      = NAS_LPP_SLCT;
        pstLppNvParaConfig->ucLppLayerErr       = NAS_LPP_SLCT;
    }
    NAS_LPP_OmNVRead(pstLppNvParaConfig);
    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_TimerReg
 Description     :  定时器登记到表
 Input           : ulTimerLen:需要根据协议LPP消息才能确定的协议定时器长度，输入值可为0;
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-7-31  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_TimerReg
(
    NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName,
    NAS_LPP_TIMER_PROC_FUNC             fFun,
    VOS_UINT32                          ulTimerLen
)
{
    if (enTimeName >= TI_NAS_LPP_TIMER_PARA_BUTT)
    {
        NAS_LPP_ERR_LOG1("TimerReg with wrong timer name", enTimeName);
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_TimerReg_ENUM, LNAS_LPP_TimerRegInvalidTimerName);
        return;
    }
    g_afNasLppTimerFun[enTimeName] = fFun;

    if (enTimeName < TI_NAS_LPP_STATE_TIMER_MAX_NUM)
    {
        g_aulTimerLen[enTimeName] = ulTimerLen;
    }

}

/*****************************************************************************
 Function Name   : NAS_LPP_ModifyPrtclTimerLen
 Description     : 修改除了状态定时器之外的定时器的长度
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-5  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_ModifyPrtclTimerLen
(
    NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName,
    VOS_UINT8                           ucSessionIndex,
    VOS_UINT8                           ucSessionTransIndx,
    VOS_UINT32                          ulTimerLen
)
{
    NAS_LPP_ENTITY_STRU                 *pstCtx;
    NAS_LPP_COMM_CONFIG_INFO_STRU       *pstLppCommCfgInfo = NAS_LPP_NULL_PTR;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransElementEntity;
    VOS_UINT8 ucTransIndx;

    pstCtx = NAS_LPP_GetLppEntityCtx();
    if ( TI_NAS_LPP_LOCATION_INVALID == enTimeName)
    {
        pstCtx->ulInvalidLen = ulTimerLen ;
        return;
    }

    ucTransIndx= NAS_LPP_GetTransIdIndex(ucSessionIndex,ucSessionTransIndx);
    pstTransElementEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if(NAS_LPP_NULL_PTR == pstTransElementEntity)
    {
        NAS_LPP_ERR_LOG2("mod ptl timer len: don't find TransEntity!", ucSessionIndex, ucSessionTransIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_ModifyPrtclTimerLen_ENUM, LNAS_LPP_ModifyPrtclTimerLenNotFindTransaction,ucTransIndx);
        return;
    }

    pstLppCommCfgInfo = NAS_LPP_GetCommCfgInfoElementByIndex(pstTransElementEntity->ucCommCfgIndex);
    if ( NAS_LPP_NULL_PTR == pstLppCommCfgInfo )
    {
        NAS_LPP_ERR_LOG1(": period don't find comm cfg! index",  pstTransElementEntity->ucCommCfgIndex);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_ModifyPrtclTimerLen_ENUM, LNAS_LPP_ModifyPrtclTimerLenNotFindCFGIndex, pstTransElementEntity->ucCommCfgIndex);
        return;
    }

    switch (enTimeName)
    {
        case TI_NAS_LPP_RESPONSE_TIMER :
        {
            if (NAS_LPP_REPORT_LOCATION_TYPE_ONCE != pstLppCommCfgInfo->stReportCriteria.enType)
            {
                NAS_LPP_ERR_LOG1(": response timer not match ! index",  pstTransElementEntity->ucCommCfgIndex);
                TLPS_PRINT2LAYER_ERROR1(NAS_LPP_ModifyPrtclTimerLen_ENUM, LNAS_LPP_ModifyPrtclTimerLenReportOnceTimerTypeError, pstTransElementEntity->ucCommCfgIndex);
            }
            else
            {
                pstLppCommCfgInfo->stReportCriteria.u.stReportOnce.ulResponseTime = ulTimerLen;
            }
            break;
        }
        case TI_NAS_LPP_PERIODICAL_REPORT :
        {
            if (NAS_LPP_REPORT_LOCATION_TYPE_PERIOD != pstLppCommCfgInfo->stReportCriteria.enType)
            {
                NAS_LPP_ERR_LOG1(": period timer not match ! index",  pstTransElementEntity->ucCommCfgIndex);
                TLPS_PRINT2LAYER_ERROR1(NAS_LPP_ModifyPrtclTimerLen_ENUM, LNAS_LPP_ModifyPrtclTimerLenPeriodTimerTypeError, pstTransElementEntity->ucCommCfgIndex);

            }
            else
            {
                pstLppCommCfgInfo->stReportCriteria.u.stReportPeriod.ulReportIntraval = ulTimerLen;
            }
            break;
        }
        case TI_NAS_LPP_REPORT_DURATION :
        {
            if (NAS_LPP_REPORT_LOCATION_TYPE_TRIGGER != pstLppCommCfgInfo->stReportCriteria.enType)
            {
                NAS_LPP_ERR_LOG1(": trigger timer not match ! index",  pstTransElementEntity->ucCommCfgIndex);
                TLPS_PRINT2LAYER_ERROR1(NAS_LPP_ModifyPrtclTimerLen_ENUM, LNAS_LPP_ModifyPrtclTimerLenDurationTimerTypeError, pstTransElementEntity->ucCommCfgIndex);

            }
            else
            {
                pstLppCommCfgInfo->stReportCriteria.u.stReportTrigger.ulReportDuration = ulTimerLen;
            }
            break;
        }
        default:
            NAS_LPP_ERR_LOG("error timer name");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_ModifyPrtclTimerLen_ENUM, LNAS_LPP_ModifyPrtclTimerLenErrorTimerName);
            break;
    }


}

/*****************************************************************************
 Function Name   : NAS_LPP_ModifyTimerLen
 Description     : 修改定时器的长度
 Input           : 如果是修改状态机的定时器，ucSessionIndex和ucSessionTransIndx都填0XFF.
                   修改协议定时器，ucSessionIndex和ucSessionTransIndx要填对应的值.如果定时器和transaction无关，ucSessionTransIndx也填 0xff。
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-3  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_ModifyTimerLen
(
    NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName,
    VOS_UINT8                           ucSessionIndex,
    VOS_UINT8                           ucSessionTransIndx,
    VOS_UINT32                          ulTimerLen
)
{
    if (enTimeName >= TI_NAS_LPP_TIMER_PARA_BUTT)
    {
        NAS_LPP_ERR_LOG1("mod timer len with wrong timer name", enTimeName);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_ModifyTimerLen_ENUM, LNAS_LPP_ModifyTimerLenErrorTimerName,enTimeName);
        return;
    }
    if (enTimeName < TI_NAS_LPP_STATE_TIMER_MAX_NUM)
    {
        g_aulTimerLen[enTimeName] = ulTimerLen;
    }
    else
    {   /*修改协议定时器的长度*/
        NAS_LPP_ModifyPrtclTimerLen(enTimeName,ucSessionIndex,ucSessionTransIndx,ulTimerLen);
    }
}
/*****************************************************************************
 Function Name   : NAS_LPP_GetTimerProcFun
 Description     : 得到定时器对应的处理函数
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-3  Draft Enact

*****************************************************************************/
NAS_LPP_TIMER_PROC_FUNC  NAS_LPP_GetTimerProcFun( NAS_LPP_TIMER_PARA_ENUM_UINT8 enTimeName )
{
    NAS_LPP_TIMER_PROC_FUNC pfTimerFun = NAS_LPP_NULL_PTR;

   if ( enTimeName < TI_NAS_LPP_TIMER_PARA_BUTT )
    {
         pfTimerFun = g_afNasLppTimerFun[enTimeName];

    }
    else
    {
        NAS_LPP_ERR_LOG1("Wrong timer type for distribute,timer type", enTimeName);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_GetTimerProcFun_ENUM, LNAS_LPP_GetTimerProcFunErrorTimerName,enTimeName);
    }

    return pfTimerFun;
}

/*****************************************************************************
 Function Name   : NAS_LPP_IsTimerNameValid
 Description     : 判断定时器名是否合法
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lifuxin 00253982       2015-07-20  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_IsTimerNameValid
(
    VOS_UINT32                          ulSessionIndex,
    VOS_UINT32                          ucSessionTransIndx,
    NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimerType
)
{
    switch(enTimerType)
    {
        case TI_NAS_LPP_WAIT_EST_CNF:
        case TI_NAS_LPP_WAIT_RE_EST:
        case TI_NAS_LPP_LOCATION_INVALID:
        case TI_NAS_LPP_WAIT_GNSS_CAP_CNF:
        case TI_NAS_LPP_UP_RESPONSE_TIMER:
        case TI_NAS_LPP_UP_PERIODICAL_REPORT:
        case TI_NAS_LPP_UP_REPORT_DURATION:
        case TI_NAS_LPP_UP_WAIT_CN_ASSIST_DATA:
        case TI_NAS_LPP_UP_WAIT_LRRC_ECID_MEAS_CNF:
        case TI_NAS_LPP_UP_WAIT_LRRC_OTDOA_MEAS_CNF:
            return PS_TRUE;

        case TI_NAS_LPP_SEQUENCE_NUMBER_INVALID:
            if(ulSessionIndex < NAS_LPP_MAX_SESSION_COUNT)
            {
                return PS_TRUE;
            }
            break;
        case TI_NAS_LPP_UPLINK_MSG_RETRANS:
        case TI_NAS_LPP_WAIT_CN_ASSIST_DATA:
        case TI_NAS_LPP_WAIT_LRRC_MEAS_CNF:
        case TI_NAS_LPP_RESPONSE_TIMER:
        case TI_NAS_LPP_PERIODICAL_REPORT:
        case TI_NAS_LPP_REPORT_DURATION:
        case TI_NAS_LPP_WAIT_INTRA_DATE_CNF:
            if ((ulSessionIndex < NAS_LPP_MAX_SESSION_COUNT)
                && (ucSessionTransIndx < NAS_LPP_MAX_TRANS_COUNT))
            {
                return PS_TRUE;
            }
            break;

        default:
            break;
    }

    return PS_FALSE;
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetGnssLocInfoInvalidTimer
 Description    : 获取 GNSS 位置信息失效定时器
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : NAS_LPP_TIMER_STRU*

 History        :
      1.wangensheng 00324863 2015-10-22  Draft Enact
*****************************************************************************/
NAS_LPP_TIMER_STRU*  NAS_LPP_GetGnssLocInfoInvalidTimer( VOS_VOID )
{
    return &(NAS_LPP_GetLppEntityCtx()->stStructDataForGnss.stLppGnssLocInfoInvalidTimer);
}
/*****************************************************************************
 Function Name  : NAS_LPP_GetGnssCapCnfTimer
 Description    : 获取GNSS CAP CNF 定时器
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : NAS_LPP_TIMER_STRU*

 History        :
      1.wangensheng 00324863 2015-10-22  Draft Enact
*****************************************************************************/
NAS_LPP_TIMER_STRU*  NAS_LPP_GetGnssCapCnfTimer( VOS_VOID )
{
    return &(NAS_LPP_GetLppEntityCtx()->stStructDataForGnss.stLppWaitForGnssCapCnfTimer);
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetSequenceNumberInvalidTimer
 Description    : Get LPP的SequenceNumberInvalid的定时器
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : NAS_LPP_TIMER_STRU*

 History        :
      1.lifuxin 00253982 2015-7-20  Draft Enact
*****************************************************************************/
NAS_LPP_TIMER_STRU*  NAS_LPP_GetSequenceNumberInvalidTimer
(
    VOS_UINT32                          ulSessionIndex
)
{
    return &(NAS_LPP_GetLppEntityCtx()->stSessionEntityPool.astLppSessionEntity[ulSessionIndex].stSequenceNumInvalid);
}

/*****************************************************************************
 Function Name   : NAS_LPP_GetTimer
 Description     : 获取定时器
 Input           : enTimerType------------------定时器类型
                   ulSessionSuffix--------------定时器所在的会话数组下标
                   ulTransSuffix----------------定时器所在的transaction会话数组下标
 Output          : None
 Return          : NAS_LPP_TIMER_STRU*

 History         :
    1.lifuxin  00253982    2015-07-20  Draft Enact
*****************************************************************************/
NAS_LPP_TIMER_STRU*  NAS_LPP_GetTimer
(
    VOS_UINT32                              ulSessionIndex,
    VOS_UINT32                              ulSessionTransIndx,
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enUpPosTechType,
    NAS_LPP_TIMER_PARA_ENUM_UINT8           enTimerType
)

{
    NAS_LPP_TIMER_STRU         *pstTimerInfo = VOS_NULL_PTR;

    /*根据定时器不同类型，获取定时器*/
    switch( enTimerType )
    {
        case TI_NAS_LPP_UP_RESPONSE_TIMER:
            pstTimerInfo = NAS_LPP_GetUpResponseTimer(enUpPosTechType);
            break;

        case TI_NAS_LPP_UP_PERIODICAL_REPORT:
            pstTimerInfo = NAS_LPP_GetUpPeriodicalTimer(enUpPosTechType);
            break;

        case TI_NAS_LPP_UP_REPORT_DURATION:
            pstTimerInfo = NAS_LPP_GetUpDurationTimer(enUpPosTechType);
            break;

        case TI_NAS_LPP_UP_WAIT_CN_ASSIST_DATA:
        case TI_NAS_LPP_UP_WAIT_LRRC_ECID_MEAS_CNF:
        case TI_NAS_LPP_UP_WAIT_LRRC_OTDOA_MEAS_CNF:
            pstTimerInfo = NAS_LPP_GetUpStateTimer(enUpPosTechType);
            break;

        case TI_NAS_LPP_UPLINK_MSG_RETRANS:
        case TI_NAS_LPP_WAIT_CN_ASSIST_DATA:
        case TI_NAS_LPP_WAIT_LRRC_MEAS_CNF:
        case TI_NAS_LPP_WAIT_INTRA_DATE_CNF:
            pstTimerInfo = NAS_LPP_GetTransactionTimer(ulSessionIndex, ulSessionTransIndx);
            break;

        case TI_NAS_LPP_RESPONSE_TIMER:
            pstTimerInfo = NAS_LPP_GetResPonseTimer((VOS_UINT8)ulSessionIndex,(VOS_UINT8)ulSessionTransIndx);
            break;

        case TI_NAS_LPP_PERIODICAL_REPORT:
            pstTimerInfo = NAS_LPP_GetPeriodTimer((VOS_UINT8)ulSessionIndex,(VOS_UINT8)ulSessionTransIndx);
            break;

        case TI_NAS_LPP_REPORT_DURATION:
            pstTimerInfo = NAS_LPP_GetDurationTimer((VOS_UINT8)ulSessionIndex,(VOS_UINT8)ulSessionTransIndx);
            break;

        case TI_NAS_LPP_WAIT_EST_CNF:
        case TI_NAS_LPP_WAIT_RE_EST:
            pstTimerInfo = NAS_LPP_GetConnManageTimer();
            break;

        case TI_NAS_LPP_WAIT_GNSS_CAP_CNF:
            pstTimerInfo = NAS_LPP_GetGnssCapCnfTimer();
            break;

        case TI_NAS_LPP_LOCATION_INVALID:
            pstTimerInfo = NAS_LPP_GetGnssLocInfoInvalidTimer();
            break;

        case TI_NAS_LPP_SEQUENCE_NUMBER_INVALID:
            pstTimerInfo = NAS_LPP_GetSequenceNumberInvalidTimer(ulSessionIndex);
            break;

        default :
            break;
    }

    return pstTimerInfo;
}

/*****************************************************************************
 Function Name   : NAS_LPP_GetPrtclTimeLen
 Description     : 获取协议定时器的长度
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-5  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LPP_GetPrtclTimeLen
(
    NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName,
    VOS_UINT8                           ucSessionIndex,
    VOS_UINT8                           ucSessionTransIndx
)
{
    NAS_LPP_COMM_CONFIG_INFO_STRU       *pstLppCommCfgInfo = NAS_LPP_NULL_PTR;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransElementEntity;
    VOS_UINT8 ucTransIndx;
    VOS_UINT32 ulLen = PS_NULL_UINT32;

    if ( TI_NAS_LPP_LOCATION_INVALID == enTimeName)
    {
        return NAS_LPP_GNSS_LOC_INFO_INVALID_TIMER_LEN;
    }

    ucTransIndx = NAS_LPP_GetTransIdIndex(ucSessionIndex,ucSessionTransIndx);
    pstTransElementEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if(NAS_LPP_NULL_PTR == pstTransElementEntity)
    {
        NAS_LPP_ERR_LOG2("get ptl timer len: don't find TransEntity!", ucSessionIndex, ucSessionTransIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_GetPrtclTimeLen_ENUM, LNAS_LPP_GetPrtclTimeLenNotFindTransaction, ucTransIndx);
        return ulLen;
    }

    pstLppCommCfgInfo = NAS_LPP_GetCommCfgInfoElementByIndex(pstTransElementEntity->ucCommCfgIndex);
    if ( NAS_LPP_NULL_PTR == pstLppCommCfgInfo )
    {
        NAS_LPP_ERR_LOG1("get period don't find comm cfg! index",  pstTransElementEntity->ucCommCfgIndex);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_GetPrtclTimeLen_ENUM, LNAS_LPP_GetPrtclTimeLenErrorCFGIndex, pstTransElementEntity->ucCommCfgIndex);
        return ulLen;
    }

    switch (enTimeName)
    {
        case TI_NAS_LPP_RESPONSE_TIMER :
        {
            if (NAS_LPP_REPORT_LOCATION_TYPE_ONCE != pstLppCommCfgInfo->stReportCriteria.enType)
            {
                NAS_LPP_ERR_LOG1("get response timer not match ! index",  pstTransElementEntity->ucCommCfgIndex);
                TLPS_PRINT2LAYER_ERROR1(NAS_LPP_GetPrtclTimeLen_ENUM, LNAS_LPP_GetPrtclTimeLenErrorReportTime, pstTransElementEntity->ucCommCfgIndex);

            }
            else
            {
                ulLen = pstLppCommCfgInfo->stReportCriteria.u.stReportOnce.ulResponseTime;
            }
            break;
        }
        case TI_NAS_LPP_PERIODICAL_REPORT :
        {
            if (NAS_LPP_REPORT_LOCATION_TYPE_PERIOD != pstLppCommCfgInfo->stReportCriteria.enType)
            {
                NAS_LPP_ERR_LOG1("get period timer not match ! index",  pstTransElementEntity->ucCommCfgIndex);
                TLPS_PRINT2LAYER_ERROR1(NAS_LPP_GetPrtclTimeLen_ENUM, LNAS_LPP_GetPrtclTimeLenErrorPeriodType, pstTransElementEntity->ucCommCfgIndex);
            }
            else
            {
                ulLen = pstLppCommCfgInfo->stReportCriteria.u.stReportPeriod.ulReportIntraval;
            }
            break;
        }
        case TI_NAS_LPP_REPORT_DURATION :
        {
            if (NAS_LPP_REPORT_LOCATION_TYPE_TRIGGER != pstLppCommCfgInfo->stReportCriteria.enType)
            {
                NAS_LPP_ERR_LOG1("get trigger timer not match ! index",  pstTransElementEntity->ucCommCfgIndex);
                TLPS_PRINT2LAYER_ERROR1(NAS_LPP_GetPrtclTimeLen_ENUM, LNAS_LPP_GetPrtclTimeLenErrorTriggerType, pstTransElementEntity->ucCommCfgIndex);
            }
            else
            {
                ulLen = pstLppCommCfgInfo->stReportCriteria.u.stReportTrigger.ulReportDuration;
            }
            break;
        }
        default:
            NAS_LPP_ERR_LOG("get error timer name");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_GetPrtclTimeLen_ENUM, LNAS_LPP_GetPrtclTimeLenErrorTimerName);
            break;
    }

    return ulLen;
}


/*****************************************************************************
 Function Name   : NAS_LPP_GetTimerLen
 Description     : 获取定时器时长
 Input           : enTimerType------------------定时器类型
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lifuxin 00253982      2015-07-20  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_GetTimerLen
(
    NAS_LPP_TIMER_PARA_ENUM_UINT8           enTimeName,
    VOS_UINT8                               ucSessionIndex,
    VOS_UINT8                               ucSessionTransIndx,
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enPosTechType

)
{
    VOS_UINT32                  ulTimerLen   = 0;

    if (enTimeName < TI_NAS_LPP_STATE_TIMER_MAX_NUM)
    {
        /*信令面获取状态机定时器长度*/
        ulTimerLen  = g_aulTimerLen[enTimeName];
    }
    else if(enTimeName < TI_NAS_LPP_PTC_TIMER_MAX_NUM)
    {
        /*信令面获取协议定时器长度*/
        ulTimerLen = NAS_LPP_GetPrtclTimeLen(enTimeName,ucSessionIndex,ucSessionTransIndx);
    }
    else
    {
        /*用户面获取定时器长度*/
        ulTimerLen = NAS_LPP_GetUpPrtcTimeLen(enTimeName, enPosTechType);
    }

    return ulTimerLen;
}

/*****************************************************************************
 Function Name  : NAS_LPP_TimerStart
 Discription    : 启动某一transaction的某种类型的定时器
 Input          : VOS_UINT32  ulIndex
                  NAS_LPP_TIMER_PARA_ENUM_UINT8   enTimerType
 Output         : VOS_VOID
 Return         : None
 History:
    lifuxin 00253982 2015-07-18 新开发
*****************************************************************************/
VOS_VOID NAS_LPP_TimerStart
(
    VOS_UINT32                          ulSessionIndex,
    VOS_UINT32                          ucSessionTransIndx,
    NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimerType
)
{
    VOS_UINT32                  ulTimerLen   = 0;
    NAS_LPP_TIMER_STRU         *pstTimerInfo = VOS_NULL_PTR;
    VOS_UINT32                  ulTimerIndex = 0;

    TLPS_PRINT2LAYER_INFO(NAS_LPP_TimerStart_ENUM, LNAS_LPP_TimerStartEnter);
    /*对ulIndex合法性判断*/
    if (PS_FALSE == NAS_LPP_IsTimerNameValid(ulSessionIndex, ucSessionTransIndx, enTimerType))
    {
        /*打印异常信息*/
        NAS_LPP_WARN_LOG("NAS_LPP_TimerStart: WARN: Input Para(ulIndex) err !");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_TimerStart_ENUM, LNAS_LPP_TimerStartTimerNameInvalid);
        return;
    }

    /*根据消息对应的索引号和定时器类型,获取相关联的定时器*/
    pstTimerInfo = NAS_LPP_GetTimer(ulSessionIndex, ucSessionTransIndx, NAS_LPP_UP_POS_REQ_TECH_TYPE_BUTT, enTimerType);
    if (pstTimerInfo == VOS_NULL_PTR)
    {
        /*打印异常信息*/
        NAS_LPP_ERR_LOG("NAS_LPP_TimerStart:ERROR: Get Timer failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_TimerStart_ENUM, LNAS_LPP_TimerStartTimerInfoError);
        return;
    }

    /*计算timer index*/
    /*高16位是transaction数组索引， 低16是session数组索引*/
    ulTimerIndex = (ucSessionTransIndx << 16) | (ulSessionIndex & 0x00ff);

    /*判断定时器是否打开，已打开则关闭*/
    if(VOS_NULL_PTR != pstTimerInfo->hTimer)
    {
        /*关闭失败，则报警返回*/
        if (VOS_OK != PS_STOP_REL_TIMER(&(pstTimerInfo->hTimer)))
        {
            /*打印异常信息*/
            NAS_LPP_WARN_LOG("NAS_LPP_TimerStart:WARN: stop reltimer error!");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_TimerStart_ENUM, LNAS_LPP_TimerStartTimerCloseOldTimerFail);
            return;
        }

        /*打印异常信息*/
        NAS_LPP_ERR_LOG2("(TimerType) Timer not close!",pstTimerInfo->enTimerId, ulTimerIndex);
        TLPS_PRINT2LAYER_INFO(NAS_LPP_TimerStart_ENUM, LNAS_LPP_TimerStartTimerCloseOldTimer);
    }

    /*根据定时器不同类型，定时器信息不同*/
    ulTimerLen = NAS_LPP_GetTimerLen(enTimerType,
                                     (VOS_UINT8)ulSessionIndex,
                                     (VOS_UINT8)ucSessionTransIndx,
                                     NAS_LPP_UP_POS_REQ_TECH_TYPE_BUTT);
    if (0 == ulTimerLen)
    {
        /*打印异常信息*/
        NAS_LPP_ERR_LOG("NAS_LPP_TimerStart:ERROR: start unreasonable reltimer.");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_TimerStart_ENUM, LNAS_LPP_TimerStartTimerGetTimerLenFail);
        return;
    }

    /*设定定时器NAME,enTimerType设定定时器Para，打开失败则报警返回*/
    if (VOS_OK !=\
            PS_START_REL_TIMER(&(pstTimerInfo->hTimer),PS_PID_LPP,\
                                ulTimerLen, (VOS_UINT32)enTimerType,\
                                 ulTimerIndex, VOS_RELTIMER_NOLOOP))
    {
          /*打印异常信息*/
          NAS_LPP_WARN_LOG("NAS_LPP_TimerStart:WARN: start reltimer error!");
          TLPS_PRINT2LAYER_ERROR(NAS_LPP_TimerStart_ENUM, LNAS_LPP_TimerStartTimerSetTimerFail);
          return;
    }

    /*更新定时器开启信息和定时器类别*/
    pstTimerInfo->enTimerId     = enTimerType;


    /*钩出当前的定时器信息 */
    NAS_LPP_OmTimerStartInd((VOS_UINT8)ulSessionIndex,(VOS_UINT8)ucSessionTransIndx,enTimerType,ulTimerLen);

    /* 打印定时器启动信息 */
    /*TODO*/
}

/*****************************************************************************
 Function Name  : NAS_LPP_TimerStop
 Discription    : 停止LPP的定时器
 Input          :
 Output         : VOS_VOID
 Return         : None
 History:
      1.lifuxin 00253982      2015-07-20  Draft Enac
*****************************************************************************/
/*lint -e438*/
VOS_VOID NAS_LPP_TimerStop
(
    VOS_UINT32                          ulSessionIndex,
    VOS_UINT32                          ulSessionTransIndx,
    NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimerType
)
{
    NAS_LPP_TIMER_STRU         *pstTimerInfo = VOS_NULL_PTR;
    VOS_UINT32                 ulTimerRemainLen = 0;

    TLPS_PRINT2LAYER_INFO(NAS_LPP_TimerStop_ENUM, LNAS_LPP_TimerStopEnter);
    /*对ulIndex合法性判断*/
    if (PS_FALSE == NAS_LPP_IsTimerNameValid(ulSessionIndex, ulSessionTransIndx, enTimerType))
    {
        /*打印异常信息*/
        NAS_LPP_WARN_LOG("NAS_LPP_TimerStop: WARN: Input Para(ulIndex) err !");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_TimerStop_ENUM, LNAS_LPP_TimerStopTimerNameInvalid);
        return;
    }

    /*根据消息对应的索引号和定时器类型,获取相关联的定时器*/
    pstTimerInfo = NAS_LPP_GetTimer(ulSessionIndex, ulSessionTransIndx, NAS_LPP_UP_POS_REQ_TECH_TYPE_BUTT, enTimerType);
    if (pstTimerInfo == VOS_NULL_PTR)
    {
        /*打印异常信息*/
        NAS_LPP_ERR_LOG("NAS_LPP_TimerStop:ERROR:Get Timer failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_TimerStop_ENUM, LNAS_LPP_TimerStopTimerInfoError);
        return;
    }

    /*定时器处于打开状态，则关闭，否则，忽略*/
    if(VOS_NULL_PTR != pstTimerInfo->hTimer)
    {
        /* 获取当前定时器的剩余时间 */
        if (VOS_OK != VOS_GetRelTmRemainTime(&(pstTimerInfo->hTimer), &ulTimerRemainLen ))
        {
            ulTimerRemainLen = 0;
        }

        /*关闭失败，则报警返回*/
        if (VOS_OK != PS_STOP_REL_TIMER(&(pstTimerInfo->hTimer)))
        {
            /*打印异常信息*/
            NAS_LPP_WARN_LOG("NAS_LPP_TimerStop:WARN: stop reltimer error!");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_TimerStop_ENUM, LNAS_LPP_TimerStopTimerFailToCloseTimer);
            return;
        }

        /*钩出当前的定时器信息 */
        NAS_LPP_OmTimerStopInd((VOS_UINT8)ulSessionIndex,(VOS_UINT8)ulSessionTransIndx,enTimerType,ulTimerRemainLen);
    }
}
/*lint +e438*/
/*****************************************************************************
 Function Name  : NAS_LPP_GetLppEntityCtx
 Description    : LPP模块的实体入口
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : NAS_LPP_ENTITY_STRU

 History        :
      1.lifuxin 00253982 2015-7-13  Draft Enact
*****************************************************************************/
NAS_LPP_ENTITY_STRU*  NAS_LPP_GetLppEntityCtx( VOS_VOID )
{
    return (&g_stNasLppEntity);
}

/*****************************************************************************
 Function Name  : NAS_LPP_ClearLppMsgBuff
 Description    : LPP模块的实体入口
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : NAS_LPP_ENTITY_STRU

 History        :
      1.lifuxin 00253982 2015-7-13  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LPP_ClearLppMsgBuff( VOS_VOID )
{
    NAS_LPP_MEM_SET_S(&stLppMsgBuff, sizeof(LPP_MESSAGE_STRU), 0, sizeof(LPP_MESSAGE_STRU));

    return;
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetLppMsgBuff
 Description    : LPP模块的实体入口
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : NAS_LPP_ENTITY_STRU

 History        :
      1.lifuxin 00253982 2015-7-13  Draft Enact
*****************************************************************************/
LPP_MESSAGE_STRU*  NAS_LPP_GetLppMsgBuff( VOS_VOID )
{
    return (&stLppMsgBuff);
}

/*****************************************************************************
 Function Name   : NAS_LPP_GetCommCfgInfoPool
 Description     : 获取common的配置参数信息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.XiaoJun      2015-8-7  Draft Enact
*****************************************************************************/
NAS_LPP_COMM_CONFIG_INFO_POOL_STRU *NAS_LPP_GetCommCfgInfoPool( VOS_VOID )
{
    return &(g_stNasLppEntity.stLppConfig.stCommCfgInfoPool);
}

/*****************************************************************************
 Function Name   : NAS_LPP_GetLocationReq
 Description     : 获取存储的location information request的信息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-7  Draft Enact

*****************************************************************************/
NAS_LPP_LOCATION_REQ_STRU  *NAS_LPP_GetLocationReqBuff( VOS_VOID )
{
    return &(g_stNasLppEntity.stLppConfig.stLocationReq);
}
/*****************************************************************************
 Function Name   : NAS_LPP_GetOtdoaAssisCfg
 Description     : 获取存储的otdoa的assistant data
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.XiaoJun      2015-8-7  Draft Enact

*****************************************************************************/
NAS_LPP_OTDOA_ASSIST_CFG_STRU *NAS_LPP_GetOtdoaAssisCfg( VOS_VOID )
{
    return &(g_stNasLppEntity.stLppConfig.stOtdoaAssisCfg);
}
/*****************************************************************************
 Function Name   : NAS_LPP_GetServingCell
 Description     : 获取服务小区的信息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-18  Draft Enact

*****************************************************************************/
NAS_LPP_SERVING_CELL_STRU *NAS_LPP_GetServingCell( VOS_VOID )
{
    return &(g_stNasLppEntity.stLppConfig.stServingCell);
}
/*****************************************************************************
 Function Name   : NAS_LPP_GetCfgPara
 Description     : 获取配置参数的地址
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-19  Draft Enact

*****************************************************************************/
NAS_LPP_CONFIG_PARA_STRU *NAS_LPP_GetCfgPara( VOS_VOID )
{
    return &(g_stNasLppEntity.stLppConfig);
}

/*****************************************************************************
 Function Name   : NAS_LPP_LppInitExceptCap
 Description     : 初始化LPP的结构内容，除了能力数据
 Input           :VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangensheng      2016-01-05  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_LppInitExceptCap( VOS_VOID )
{
    NAS_LPP_ENTITY_STRU     *pstLppCtx;
    VOS_UINT32  ulLoop;
    VOS_UINT32  ulLoop1 = 0;

    pstLppCtx = NAS_LPP_GetLppEntityCtx();

    for ( ulLoop = 0 ; ulLoop < NAS_LPP_MAX_POS_TECH; ulLoop++ )
    {
        pstLppCtx->stLppConfig.stCommCfgInfoPool.astLppCommCfgInfo[ulLoop].stReportCriteria.enType = NAS_LPP_REPORT_LOCATION_TYPE_BUTT;
    }

    for ( ulLoop = 0 ; ulLoop < NAS_LPP_MAX_TRANS_POOL_COUNT; ulLoop++ )
    {
        pstLppCtx->stTransEntityPool.astTransElementEntity[ulLoop].enLastUpMsgId = NAS_LPP_AIR_MSG_BUTT;
        pstLppCtx->stTransEntityPool.astTransElementEntity[ulLoop].ucCommCfgIndex = PS_NULL_UINT8;
    }

    /*初始化每个session里的transactionindex*/
    for ( ulLoop = 0 ; ulLoop < NAS_LPP_MAX_SESSION_COUNT; ulLoop++ )
    {
        for (ulLoop1 = 0; ulLoop1 <NAS_LPP_MAX_TRANS_COUNT ;ulLoop1++)
        {
            pstLppCtx->stSessionEntityPool.astLppSessionEntity[ulLoop].stLppTrans.aucTransElementIdx[ulLoop1] = PS_NULL_UINT8;
        }
    }

    /* 清空用户面实体 */
    NAS_LPP_UPClrEntity();
}

/*****************************************************************************
 Function Name   : NAS_LPP_LppCtxInit
 Description     : 初始化LPP的context
 Input           :VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.XiaoJun      2015-7-15  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_LppCtxInit( VOS_VOID )
{
    NAS_LPP_ENTITY_STRU     *pstLppCtx;
    VOS_UINT32  ulLoop;
    VOS_UINT32  ulLoop1 = 0;

    NAS_LPP_ERR_LOG("NAS_LPP_LppCtxInit enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_LppCtxInit_ENUM, LNAS_LPP_LppCtxInitEnter);
    pstLppCtx = NAS_LPP_GetLppEntityCtx();

    NAS_LPP_MEM_SET_S(pstLppCtx,sizeof(NAS_LPP_ENTITY_STRU), 0, sizeof(NAS_LPP_ENTITY_STRU));

    for ( ulLoop = 0 ; ulLoop < NAS_LPP_MAX_POS_TECH; ulLoop++ )
    {
        pstLppCtx->stLppConfig.stCommCfgInfoPool.astLppCommCfgInfo[ulLoop].stReportCriteria.enType = NAS_LPP_REPORT_LOCATION_TYPE_BUTT;
    }

    for ( ulLoop = 0 ; ulLoop < NAS_LPP_MAX_TRANS_POOL_COUNT; ulLoop++ )
    {
        pstLppCtx->stTransEntityPool.astTransElementEntity[ulLoop].enLastUpMsgId = NAS_LPP_AIR_MSG_BUTT;
        pstLppCtx->stTransEntityPool.astTransElementEntity[ulLoop].ucCommCfgIndex = PS_NULL_UINT8;
    }

    /*初始化每个session里的transactionindex*/
    for ( ulLoop = 0 ; ulLoop < NAS_LPP_MAX_SESSION_COUNT; ulLoop++ )
    {
        for (ulLoop1 = 0; ulLoop1 <NAS_LPP_MAX_TRANS_COUNT ;ulLoop1++)
        {
            pstLppCtx->stSessionEntityPool.astLppSessionEntity[ulLoop].stLppTrans.aucTransElementIdx[ulLoop1] = PS_NULL_UINT8;
        }
    }

    /* 初始化用户面实体 */
    NAS_LPP_LppUpEntityInit();

    /*初始化timer*/
    NAS_LPP_TimerInit();


}

/*****************************************************************************
 Function Name   : NAS_LPP_GetLppSessionEntityPool
 Description     : 获取session pool
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-15  Draft Enact

*****************************************************************************/

NAS_LPP_SESSION_ENTITY_POOL_STRU* NAS_LPP_GetLppSessionEntityPool( VOS_VOID )
{
    return (&(g_stNasLppEntity.stSessionEntityPool));
}


/*****************************************************************************
 Function Name   : NAS_LPP_GetLppTransEntityPool
 Description     : 获取trans pool
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-15  Draft Enact

*****************************************************************************/
NAS_LPP_TRANSACTION_ENTITY_POOL_STRU * NAS_LPP_GetLppTransEntityPool( VOS_VOID )
{
    return (&(g_stNasLppEntity.stTransEntityPool));
}
/*****************************************************************************
 Function Name   : NAS_LPP_GetRuningPosTch
 Description     : 获取正在运行的定位技术
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-29  Draft Enact

*****************************************************************************/
NAS_LPP_LOC_TECH_RUNING_STRU  *NAS_LPP_GetRuningLocTech( VOS_VOID )
{
    return (&(g_stNasLppEntity.stRuningLocTech));
}


/*****************************************************************************
 Function Name   : NAS_LPP_GetLppUpMsgBuffPool
 Description     :  获取重传的地址
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-20  Draft Enact

*****************************************************************************/
NAS_LPP_UP_MSG_BUFF_POOL_STRU * NAS_LPP_GetLppUpMsgBuffPool( VOS_VOID )
{
    return (&(g_stNasLppEntity.stUpMsgBuffPool));
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetLppConnStatus
 Description    : Get LPP的连接状态
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : NAS_LPP_CONN_STATUS_ENUM_UINT32

 History        :
      1.lifuxin 00253982 2015-7-13  Draft Enact
*****************************************************************************/
NAS_LPP_CONN_STATUS_ENUM_UINT32  NAS_LPP_GetLppConnStatus( VOS_VOID )
{
    return (NAS_LPP_GetLppEntityCtx()->stLppConnManage.enConectStatus);
}

/*****************************************************************************
 Function Name  : NAS_LPP_SetLppConnStatus
 Description    : set LPP的连接状态
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lifuxin 00253982 2015-7-13  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LPP_SetLppConnStatus(NAS_LPP_CONN_STATUS_ENUM_UINT32 enConnStatus)
{
    NAS_LPP_INFO_LOG1("NAS_LPP_SetLppConnStatus: CONN STATUS =!", enConnStatus);
    TLPS_PRINT2LAYER_INFO1(NAS_LPP_SetLppConnStatus_ENUM,LNAS_LPP_SetLppConnStatusHandle,enConnStatus);
    NAS_LPP_GetLppEntityCtx()->stLppConnManage.enConectStatus = enConnStatus;
    NAS_LPP_OmSetConnStatus(enConnStatus);

    return;
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetLppNvParaConfig
 Description    : Get LPP NV配置结构
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : NAS_LPP_CONN_STATUS_ENUM_UINT32

 History        :
      1.lifuxin 00253982 2015-7-13  Draft Enact
*****************************************************************************/
NAS_LPP_NV_CONFIG_STRU*  NAS_LPP_GetLppNvParaConfig(VOS_VOID)
{

    return &(NAS_LPP_GetLppEntityCtx()->stLppNvConfig);
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetLppTransAttepCnt
 Description    : Get LPP 消息尝试传输计数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lifuxin 00253982 2015-7-13  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_GetLppTransAttepCnt(VOS_VOID)
{
    VOS_UINT32      usAttempeTransCnt = 0;

    usAttempeTransCnt = NAS_LPP_GetLppEntityCtx()->stLppNvConfig.usAttempeTransCnt;
    TLPS_PRINT2LAYER_INFO1(NAS_LPP_GetLppTransAttepCnt_ENUM, LNAS_LPP_GetLppTransAttepCnt, usAttempeTransCnt);

    return usAttempeTransCnt;
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetLppLayerSwitchFlag
 Description    : 是否打开LPP可维可测消息的总开关
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lifuxin 00253982 2015-9-24  Draft Enact
*****************************************************************************/
VOS_UINT8  NAS_LPP_GetLppLayerSwitchFlag(VOS_VOID)
{

    return (NAS_LPP_GetLppEntityCtx()->stLppNvConfig.ucLppLayerSwitch);
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetLppLayerNormFlag
 Description    : 是否打开LPP可维可测消息NORMAL等级
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lifuxin 00253982 2015-9-24  Draft Enact
*****************************************************************************/
VOS_UINT8  NAS_LPP_GetLppLayerNormFlag(VOS_VOID)
{

    return (NAS_LPP_GetLppEntityCtx()->stLppNvConfig.ucLppLayerNorm);
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetLppLayerInfoFlag
 Description    : 是否打开LPP可维可测消息INFO等级
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lifuxin 00253982 2015-9-24  Draft Enact
*****************************************************************************/
VOS_UINT8  NAS_LPP_GetLppLayerInfoFlag(VOS_VOID)
{

    return (NAS_LPP_GetLppEntityCtx()->stLppNvConfig.ucLppLayerInfo);
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetLppLayerWarnFlag
 Description    : 是否打开LPP可维可测消息WARN等级
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lifuxin 00253982 2015-9-24  Draft Enact
*****************************************************************************/
VOS_UINT8  NAS_LPP_GetLppLayerWarnFlag(VOS_VOID)
{

    return (NAS_LPP_GetLppEntityCtx()->stLppNvConfig.ucLppLayerWarn);
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetLppLayerErrFlag
 Description    : 是否打开LPP可维可测消息Err等级
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lifuxin 00253982 2015-9-24  Draft Enact
*****************************************************************************/
VOS_UINT8  NAS_LPP_GetLppLayerErrFlag(VOS_VOID)
{

    return (NAS_LPP_GetLppEntityCtx()->stLppNvConfig.ucLppLayerErr);
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetLppIntraDataCnfTimerLen
 Description    : Get LPP Intra Data Cnf 的定时器时长
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lifuxin 00253982 2015-7-13  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_GetLppIntraDataCnfTimerLen(VOS_VOID)
{
    /*等内部data cnf的时间等于建链次数乘以最大的等待建链定时器时长10s，然后乘以1000转成毫秒*/
    /* 建链次数为0时，缺省为1 */
    if ( 0 == NAS_LPP_GetLppTransAttepCnt())
    {
        return 10 * 1000;
    }
    return (NAS_LPP_GetLppTransAttepCnt()* 10 * 1000);
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetLppEstCnt
 Description    : Get LPP的建链次数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : NAS_LPP_CONN_STATUS_ENUM_UINT32

 History        :
      1.lifuxin 00253982 2015-7-13  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_GetTransLppMsgCnt( VOS_VOID )
{
    VOS_UINT32      ulEstOrDataCnt = 0;

    ulEstOrDataCnt = NAS_LPP_GetLppEntityCtx()->stLppConnManage.ulEstOrDataCnt;
    TLPS_PRINT2LAYER_INFO1(NAS_LPP_GetTransLppMsgCnt_ENUM, LNAS_LPP_GetTransLppMsgCnt, ulEstOrDataCnt);

    return ulEstOrDataCnt;
}

/*****************************************************************************
 Function Name  : NAS_LPP_TransLppMsgAddCnt
 Description    : LPP消息建链直传次数加1
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lifuxin 00253982 2015-7-13  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LPP_TransLppMsgAddCnt(VOS_VOID)
{
    NAS_LPP_GetLppEntityCtx()->stLppConnManage.ulEstOrDataCnt += 1;

    return;
}

/*****************************************************************************
 Function Name  : NAS_LPP_ClearLppEstCnt
 Description    : 清空建链次数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : NAS_LPP_CONN_STATUS_ENUM_UINT32

 History        :
      1.lifuxin 00253982 2015-7-13  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LPP_ClearLppTransCnt(VOS_VOID)
{
    NAS_LPP_GetLppEntityCtx()->stLppConnManage.ulEstOrDataCnt = 0;

    return;
}


/*****************************************************************************
 Function Name  : NAS_LPP_GetSessionEntity
 Description    : Get某一session实体
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : NAS_LPP_SESSION_ENTITY_ELEMENT_STRU*

 History        :
      1.lifuxin 00253982 2015-7-13  Draft Enact
*****************************************************************************/
NAS_LPP_SESSION_ENTITY_ELEMENT_STRU*  NAS_LPP_GetSessionEntity
(
    VOS_UINT32                          ulSessionIndex
)
{
    if (NAS_LPP_MAX_SESSION_COUNT <= ulSessionIndex)
    {
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_GetSessionEntity_ENUM, LNAS_LPP_GetSessionEntityIncorrectIndex);
        return  NAS_LPP_NULL_PTR;
    }
    return &(NAS_LPP_GetLppEntityCtx()->stSessionEntityPool.astLppSessionEntity[ulSessionIndex]);
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetTransEntityIndx
 Description    : Get某一transaction实体index

 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32(返回的transaction实体在内存池中的索引值)

 History        :
      1.lifuxin 00253982 2015-7-13  Draft Enact
*****************************************************************************/
VOS_UINT8  NAS_LPP_GetTransIdIndex
(
    VOS_UINT8                          ucSessionIndex,
    VOS_UINT8                          ucSessionTransIndex
)
{
    VOS_UINT8 ucIndex = PS_NULL_UINT8;

    if ( (ucSessionIndex >= NAS_LPP_MAX_SESSION_COUNT)||(ucSessionTransIndex >= NAS_LPP_MAX_TRANS_COUNT))
    {
        NAS_LPP_ERR_LOG2("Get trans index with wrong ulSessionIndex,ulSessionTransIndex", ucSessionIndex, ucSessionTransIndex);
        TLPS_PRINT2LAYER_ERROR2(NAS_LPP_GetTransIdIndex_ENUM, LNAS_LPP_GetTransIdIndexErrorIndexValue, ucSessionIndex, ucSessionTransIndex);
        return ucIndex;
    }

    ucIndex = NAS_LPP_GetSessionEntity(ucSessionIndex)->stLppTrans.aucTransElementIdx[ucSessionTransIndex];

    return ucIndex;
}
/*****************************************************************************
 Function Name   : NAS_LPP_GetTransEntity
 Description     : 获取transaction的实体指针
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-30  Draft Enact

*****************************************************************************/
NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU  *NAS_LPP_GetTransEntity
(
    VOS_UINT32                          ulSessionIndex,
    VOS_UINT32                          ulSessionTransIndex
)
{
    VOS_UINT8                                   ucTransIndex = 0;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU    *pstTransElementEntity = NAS_LPP_NULL_PTR;

    /*取出session中transaction实体中存储单元的index*/
    ucTransIndex = (VOS_UINT8)NAS_LPP_GetTransIdIndex((VOS_UINT8)ulSessionIndex, (VOS_UINT8)ulSessionTransIndex);

    /*根据index去得到内存池中的transaction实体*/
    pstTransElementEntity = NAS_LPP_GetTransElementByIndex(ucTransIndex);

    return pstTransElementEntity;
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetTransactionTimer
 Description    : Get LPP的Transaction timer
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : NAS_LPP_TIMER_STRU*s

 History        :
      1.lifuxin 00253982 2015-7-20  Draft Enact
*****************************************************************************/
NAS_LPP_TIMER_STRU*  NAS_LPP_GetTransactionTimer
(
    VOS_UINT32                          ulSessionIndex,
    VOS_UINT32                          ulSessionTransIndx
)
{
    VOS_UINT8                                   ucTransIndex = 0;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU    *pstTransElementEntity = NAS_LPP_NULL_PTR;

    /*取出session中transaction实体中存储单元的index*/
    ucTransIndex = (VOS_UINT8)NAS_LPP_GetTransIdIndex((VOS_UINT8)ulSessionIndex, (VOS_UINT8)ulSessionTransIndx);

    /*根据index去得到内存池中的transaction实体*/
    pstTransElementEntity = NAS_LPP_GetTransElementByIndex(ucTransIndex);

    return &(pstTransElementEntity->stLppTimer);
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetResPonseTimer
 Description    : Get LPP的Response Timer
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : NAS_LPP_TIMER_STRU*

 History        :
      1.lifuxin 00253982 2015-7-20  Draft Enact
*****************************************************************************/
NAS_LPP_TIMER_STRU*  NAS_LPP_GetResPonseTimer
(
    VOS_UINT8                          ucSessionIndex,
    VOS_UINT8                          ucSessionTransIndx
)
{
    NAS_LPP_COMM_CONFIG_INFO_STRU       *pstLppCommCfgInfo = NAS_LPP_NULL_PTR;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransElementEntity;
    VOS_UINT8 ucTransIndx;

    ucTransIndx= NAS_LPP_GetTransIdIndex(ucSessionIndex,ucSessionTransIndx);
    pstTransElementEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if(NAS_LPP_NULL_PTR == pstTransElementEntity)
    {
        NAS_LPP_ERR_LOG2("get response timer : don't find TransEntity!", ucSessionIndex, ucSessionTransIndx);
        TLPS_PRINT2LAYER_ERROR2(NAS_LPP_GetResPonseTimer_ENUM, LNAS_LPP_GetResPonseTimerNotFindTransaction, ucSessionIndex, ucSessionTransIndx);
        return NAS_LPP_NULL_PTR;
    }

    pstLppCommCfgInfo = NAS_LPP_GetCommCfgInfoElementByIndex(pstTransElementEntity->ucCommCfgIndex);
    if ( NAS_LPP_NULL_PTR == pstLppCommCfgInfo )
    {
        NAS_LPP_ERR_LOG1("response don't find comm cfg! index",  pstTransElementEntity->ucCommCfgIndex);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_GetResPonseTimer_ENUM, LNAS_LPP_GetResPonseTimerCFGIndexError, pstTransElementEntity->ucCommCfgIndex);
        return NAS_LPP_NULL_PTR;
    }

    if (NAS_LPP_REPORT_LOCATION_TYPE_ONCE != pstLppCommCfgInfo->stReportCriteria.enType)
    {
        NAS_LPP_ERR_LOG1("get response don't find comm cfg! index",  pstTransElementEntity->ucCommCfgIndex);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_GetResPonseTimer_ENUM, LNAS_LPP_GetResPonseTimerCFGTypeError, pstTransElementEntity->ucCommCfgIndex);
        return NAS_LPP_NULL_PTR;
    }

    return &(pstLppCommCfgInfo->stReportCriteria.u.stReportOnce.stLppTimer);
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetPeriodTimer
 Description    : Get LPP的Period Timer
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : NAS_LPP_TIMER_STRU*

 History        :
      1.lifuxin 00253982 2015-7-20  Draft Enact
*****************************************************************************/
NAS_LPP_TIMER_STRU*  NAS_LPP_GetPeriodTimer
(
    VOS_UINT8                          ucSessionIndex,
    VOS_UINT8                          ucSessionTransIndx
)
{
    NAS_LPP_COMM_CONFIG_INFO_STRU       *pstLppCommCfgInfo = NAS_LPP_NULL_PTR;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransElementEntity;
    VOS_UINT8 ucTransIndx;

    ucTransIndx= NAS_LPP_GetTransIdIndex(ucSessionIndex,ucSessionTransIndx);
    pstTransElementEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if(NAS_LPP_NULL_PTR == pstTransElementEntity)
    {
        NAS_LPP_ERR_LOG2("get period timer : don't find TransEntity!", ucSessionIndex, ucSessionTransIndx);
        TLPS_PRINT2LAYER_ERROR2(NAS_LPP_GetPeriodTimer_ENUM, LNAS_LPP_GetPeriodTimerNOTFindTransaction, ucSessionIndex, ucSessionTransIndx);
        return NAS_LPP_NULL_PTR;
    }

    pstLppCommCfgInfo = NAS_LPP_GetCommCfgInfoElementByIndex(pstTransElementEntity->ucCommCfgIndex);
    if ( NAS_LPP_NULL_PTR == pstLppCommCfgInfo )
    {
        NAS_LPP_ERR_LOG1("period don't find comm cfg! index",  pstTransElementEntity->ucCommCfgIndex);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_GetPeriodTimer_ENUM, LNAS_LPP_GetPeriodTimerCFGIndexError, pstTransElementEntity->ucCommCfgIndex);
        return NAS_LPP_NULL_PTR;
    }

    if (NAS_LPP_REPORT_LOCATION_TYPE_PERIOD != pstLppCommCfgInfo->stReportCriteria.enType)
    {
        NAS_LPP_ERR_LOG1("get period don't find comm cfg! index",  pstTransElementEntity->ucCommCfgIndex);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_GetPeriodTimer_ENUM, LNAS_LPP_GetPeriodTimerCFGReportTypeError, pstTransElementEntity->ucCommCfgIndex);
        return NAS_LPP_NULL_PTR;
    }

    return &(pstLppCommCfgInfo->stReportCriteria.u.stReportPeriod.stLppTimer);
}


/*****************************************************************************
 Function Name  : NAS_LPP_GetDurationTimer
 Description    : Get LPP的Duration Timer
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : NAS_LPP_TIMER_STRU*

 History        :
      1.lifuxin 00253982 2015-7-20  Draft Enact
*****************************************************************************/
NAS_LPP_TIMER_STRU*  NAS_LPP_GetDurationTimer
(
    VOS_UINT8                          ucSessionIndex,
    VOS_UINT8                          ucSessionTransIndx
)
{
    NAS_LPP_COMM_CONFIG_INFO_STRU       *pstLppCommCfgInfo = NAS_LPP_NULL_PTR;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransElementEntity;
    VOS_UINT8 ucTransIndx;

    ucTransIndx= NAS_LPP_GetTransIdIndex(ucSessionIndex,ucSessionTransIndx);
    pstTransElementEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if(NAS_LPP_NULL_PTR == pstTransElementEntity)
    {
        NAS_LPP_ERR_LOG2("get duration timer : don't find TransEntity!", ucSessionIndex, ucSessionTransIndx);
        TLPS_PRINT2LAYER_ERROR2(NAS_LPP_GetDurationTimer_ENUM, LNAS_LPP_GetDurationTimerNOTFindTransaction, ucSessionIndex, ucSessionTransIndx);
        return NAS_LPP_NULL_PTR;
    }

    pstLppCommCfgInfo = NAS_LPP_GetCommCfgInfoElementByIndex(pstTransElementEntity->ucCommCfgIndex);
    if ( NAS_LPP_NULL_PTR == pstLppCommCfgInfo )
    {
        NAS_LPP_ERR_LOG1("duration don't find comm cfg! index",  pstTransElementEntity->ucCommCfgIndex);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_GetDurationTimer_ENUM, LNAS_LPP_GetDurationTimerCFGIndexError, pstTransElementEntity->ucCommCfgIndex);
        return NAS_LPP_NULL_PTR;
    }

    if (NAS_LPP_REPORT_LOCATION_TYPE_TRIGGER != pstLppCommCfgInfo->stReportCriteria.enType)
    {
        NAS_LPP_ERR_LOG1("get duration don't find comm cfg! index",  pstTransElementEntity->ucCommCfgIndex);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_GetDurationTimer_ENUM, LNAS_LPP_GetDurationTimerReportTypeError, pstTransElementEntity->ucCommCfgIndex);
        return NAS_LPP_NULL_PTR;
    }

    return &(pstLppCommCfgInfo->stReportCriteria.u.stReportTrigger.stLppTimer);
}


/*****************************************************************************
 Function Name  : NAS_LPP_GetLastTriggerCellGloId
 Description    : Get LPP的小区改变的ID信息
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : NAS_LPP_TIMER_STRU*

 History        :
      1.lifuxin 00253982 2015-7-20  Draft Enact
*****************************************************************************/
LRRC_LPP_CELL_GLOBAL_ID_INFO_STRU*  NAS_LPP_GetLastTriggerCellGloId( VOS_VOID )
{
    NAS_LPP_ECID_MEAS_RESULT_STRU *pstEcidMeasRslt;

    pstEcidMeasRslt = NAS_LPP_GetEcidMeasRsltAddr();

    return &(pstEcidMeasRslt->stLastGlobalIdInfo);
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetLastTriggerLastPhyCellId
 Description    : Get LPP上次驻留的物理小区ID
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : NAS_LPP_TIMER_STRU*

 History        :
      1.lifuxin 00253982 2015-7-20  Draft Enact
*****************************************************************************/
VOS_UINT16  NAS_LPP_GetLastTriggerLastPhyCellId( VOS_VOID )
{
    NAS_LPP_ECID_MEAS_RESULT_STRU *pstEcidMeasRslt;

    pstEcidMeasRslt = NAS_LPP_GetEcidMeasRsltAddr();

    return (pstEcidMeasRslt->usLastPhyCellId);
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetLastTriggerLastPhyCellId
 Description    : Get LPP上次驻留的物理小区ID
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : NAS_LPP_TIMER_STRU*

 History        :
      1.lifuxin 00253982 2015-7-20  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LPP_SetLastTriggerLastPhyCellId(VOS_UINT16 usPhyCellId)
{
    NAS_LPP_ECID_MEAS_RESULT_STRU *pstEcidMeasRslt;

    pstEcidMeasRslt = NAS_LPP_GetEcidMeasRsltAddr();

    pstEcidMeasRslt->usLastPhyCellId = usPhyCellId;

    return;
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetConnManageTimer
 Description    : Get LPP的connMange timer
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : NAS_LPP_TIMER_STRU*

 History        :
      1.lifuxin 00253982 2015-7-20  Draft Enact
*****************************************************************************/
NAS_LPP_TIMER_STRU*  NAS_LPP_GetConnManageTimer( VOS_VOID )
{
    return &(NAS_LPP_GetLppEntityCtx()->stLppConnManage.stLppTimer);
}
/*****************************************************************************
 Function Name  : NAS_LPP_GetSessionEntityReportType
 Description    : Get LPP上报位置方式枚举
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : NAS_LPP_REPORT_LOCATION_TYPE_ENUM_UINT8

 History        :
      1.lifuxin 00253982 2015-7-20  Draft Enact
*****************************************************************************/
VOS_UINT8  NAS_LPP_GetSessionEntityReportType
(
    VOS_UINT8                           ucSessionIndex,
    VOS_UINT8                           ucSessionTransIndex
)
{
    NAS_LPP_COMM_CONFIG_INFO_STRU       *pstLppCommCfgInfo = NAS_LPP_NULL_PTR;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransElementEntity;
    VOS_UINT8 ucTransIndx;

    ucTransIndx= NAS_LPP_GetTransIdIndex(ucSessionIndex,ucSessionTransIndex);
    pstTransElementEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if(NAS_LPP_NULL_PTR == pstTransElementEntity)
    {
        NAS_LPP_ERR_LOG2("get reprt type : don't find TransEntity!", ucSessionIndex, ucSessionTransIndex);
        TLPS_PRINT2LAYER_ERROR2(NAS_LPP_GetSessionEntityReportType_ENUM, LNAS_LPP_GetSessionEntityReportTypeTransElement, ucSessionIndex, ucSessionTransIndex);
        return NAS_LPP_REPORT_LOCATION_TYPE_BUTT;
    }

    pstLppCommCfgInfo = NAS_LPP_GetCommCfgInfoElementByIndex(pstTransElementEntity->ucCommCfgIndex);
    if ( NAS_LPP_NULL_PTR == pstLppCommCfgInfo )
    {
        NAS_LPP_ERR_LOG1("get reprt type don't find comm cfg! index",  pstTransElementEntity->ucCommCfgIndex);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_GetSessionEntityReportType_ENUM, LNAS_LPP_GetSessionEntityReportTypeCFGError, pstTransElementEntity->ucCommCfgIndex);

        return NAS_LPP_REPORT_LOCATION_TYPE_BUTT;
    }

    return(pstLppCommCfgInfo->stReportCriteria.enType);
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetDownLinkLocationReqIEAddr
 Description    : Get LPP下行位置信息请求的实际地址
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT8

 History        :
      1.lifuxin 00253982 2015-7-20  Draft Enact
*****************************************************************************/
LPP_REQ_LOCATION_INFO_R9_IES_STRU*  NAS_LPP_GetDownLinkLocationReqIEAddr
(
    LPP_MESSAGE_STRU                   *pstLppMsg
)
{
    return &(pstLppMsg->stLppMessageBody.u.stC1.u.stRequestLocationInformation.u.stC1.u.stReqLocationInfoR9);
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetDownLinkCapReqIEAddr
 Description    : Get LPP下行能力信息请求的实际地址
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT8

 History        :
      1.lifuxin 00253982 2015-7-20  Draft Enact
*****************************************************************************/
LPP_REQUEST_CAPABILITIES_R9_IES_STRU*  NAS_LPP_GetDownLinkCapReqIEAddr
(
    LPP_MESSAGE_STRU                   *pstLppMsg
)
{
    return &(pstLppMsg->stLppMessageBody.u.stC1.u.stRequestCapabilities.u.stC1.u.stRequestCapabilitiesR9);
}


/*****************************************************************************
 Function Name  : NAS_LPP_GetUpLinkProvideCapIEAddr
 Description    : Get LPP下行能力请求的实际地址
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT8

 History        :
      1.lifuxin 00253982 2015-7-20  Draft Enact
*****************************************************************************/
LPP_PROVIDE_CAPABILITIES_R9_IES_STRU*  NAS_LPP_GetUpLinkProvideCapIEAddr
(
    LPP_MESSAGE_STRU                   *pstLppMsg
)
{
    return &(pstLppMsg->stLppMessageBody.u.stC1.u.stProvideCapabilities.u.stC1.u.stProvideCapabilitiesR9);
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetUpLinkProvideLocIEAddr
 Description    : Get LPP下行能力请求的实际地址
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT8

 History        :
      1.lifuxin 00253982 2015-7-20  Draft Enact
*****************************************************************************/
LPP_PROVIDE_LOCATION_INFO_R9_IES_STRU*  NAS_LPP_GetUpLinkProvideLocIEAddr
(
    LPP_MESSAGE_STRU                   *pstLppMsg
)
{
    return &(pstLppMsg->stLppMessageBody.u.stC1.u.stProvideLocationInformation.u.stC1.u.stProLocationInfoR9);
}

/*****************************************************************************
 Function Name   : NAS_LPP_GetLrrcCap
 Description     : 获取LRRC的能力值
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-19  Draft Enact

*****************************************************************************/
LRRC_SUPPORT_CAPABILITY_STRU *NAS_LPP_GetLrrcCap( VOS_VOID )
{
    return (&g_stNasLppEntity.stLrrcSupCapability);
}

/*****************************************************************************
 Function Name   : NAS_LPP_GetLrrcCap
 Description     : 获取LRRC的能力值
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-19  Draft Enact

*****************************************************************************/
NAS_LPP_GNSS_DATA_STRU *NAS_LPP_GetGnssData( VOS_VOID )
{
    return (&g_stNasLppEntity.stStructDataForGnss);
}


/*****************************************************************************
 Function Name  : NAS_LPP_GetLrrcRxTxTimeDiffMeasFlag
 Description    : 得到LRRC是否支持RxTxTimeDiffMeas
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT8

 History        :
      1.lifuxin 00253982 2015-7-20  Draft Enact
*****************************************************************************/
VOS_UINT8  NAS_LPP_GetLrrcRxTxTimeDiffMeasFlag(VOS_VOID)
{
    return (NAS_LPP_GetLppEntityCtx()->stLrrcSupCapability.stRrcCapbility.ucUeRxTxTimeDiffMeasFlag);
}



/*****************************************************************************
 Function Name  : NAS_LPP_GetPositionTechEcid
 Description    : 获取网侧请求的定位技术ECID
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT8

 History        :
      1.lifuxin 00253982 2015-7-20  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_GetPositionTechEcid(VOS_UINT8 ucTransIndx)
{
    NAS_LPP_LOC_TECH_RUNING_STRU  stPosSearchRslt;
    VOS_UINT32 ulRslt = 0,ulLoop;

    NAS_LPP_SearchRunningPosTechByTransIndx(ucTransIndx,&stPosSearchRslt);
     for ( ulLoop = 0 ; ulLoop < stPosSearchRslt.ucNum; ulLoop++ )
     {
         if (NAS_LPP_POSITION_TECH_ECID == stPosSearchRslt.astLocTechMap[ulLoop].enPositionTech)
         {
             ulRslt= NAS_LPP_SLCT;
             break;
         }
     }

    return ulRslt;
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetPositionTechOtdoa
 Description    : 获取网侧请求的定位技术Otdoa
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT8

 History        :
      1.lifuxin 00253982 2015-7-20  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_GetPositionTechOtdoa(VOS_UINT8 ucTransIndx)
{
    NAS_LPP_LOC_TECH_RUNING_STRU  stPosSearchRslt;
    VOS_UINT32 ulRslt = 0,ulLoop;

    NAS_LPP_SearchRunningPosTechByTransIndx(ucTransIndx,&stPosSearchRslt);
     for ( ulLoop = 0 ; ulLoop < stPosSearchRslt.ucNum; ulLoop++ )
     {
         if (NAS_LPP_POSITION_TECH_OTDOA == stPosSearchRslt.astLocTechMap[ulLoop].enPositionTech)
         {
             ulRslt= NAS_LPP_SLCT;
             break;
         }
     }

    return ulRslt;
}


/*****************************************************************************
 Function Name  : NAS_LPP_GetPositionTechGnss
 Description    : 获取网侧请求的定位技术Gnss
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT8

 History        :
      1.lifuxin 00253982 2015-7-20  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_GetPositionTechGnss(VOS_UINT8 ucTransIndx)
{
    NAS_LPP_LOC_TECH_RUNING_STRU  stPosSearchRslt;
    VOS_UINT32 ulRslt = 0,ulLoop;

    NAS_LPP_SearchRunningPosTechByTransIndx(ucTransIndx,&stPosSearchRslt);
     for ( ulLoop = 0 ; ulLoop < stPosSearchRslt.ucNum; ulLoop++ )
     {
         if (NAS_LPP_POSITION_TECH_GNSS == stPosSearchRslt.astLocTechMap[ulLoop].enPositionTech)
         {
             ulRslt= NAS_LPP_SLCT;
             break;
         }
     }

    return ulRslt;
}

/*****************************************************************************
 Function Name  : NAS_LPP_SearchRunningPositionTech
 Description    : 获取指定定位技术的运行实体的ID
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT8

 History        :
      1.lifuxin 00253982 2015-7-20  Draft Enact
*****************************************************************************/
NAS_LPP_LOC_TECH_MAP_STRU*  NAS_LPP_SearchRunningPositionTech
(
    NAS_LPP_POSITION_TECH_ENUM_UINT8        enPositionTech
)
{
    NAS_LPP_LOC_TECH_RUNING_STRU  *pstRunLocTech;
    VOS_UINT32 ulLoop;

    pstRunLocTech = NAS_LPP_GetRuningLocTech();

    if ( pstRunLocTech->ucNum > NAS_LPP_MAX_POS_TECH)
    {
        NAS_LPP_ERR_LOG1("Search runing pos tech num overflow", pstRunLocTech->ucNum);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_SearchRunningPositionTech_ENUM, LNAS_LPP_SearchRunningPositionTechRunningTechNumOverFlow, pstRunLocTech->ucNum);
        return NAS_LPP_NULL_PTR;
    }

    for(ulLoop = 0; ulLoop < pstRunLocTech->ucNum; ulLoop++)
    {
        if(pstRunLocTech->astLocTechMap[ulLoop].enPositionTech == enPositionTech)
        {
            /*找到了对应的定位技术，返回实体*/
            return &(pstRunLocTech->astLocTechMap[ulLoop]);
        }
    }

    /*没有找到，返回空*/
    return NAS_LPP_NULL_PTR;
}

/*****************************************************************************
 Function Name   : NAS_LPP_GetUpMsgSequenceNum
 Description     : 获取存储下行SequenceNumber
 Input           :VOS_VOID
 Output          : None
 Return          : VOS_UINT8

 History         :
    1.lifuxin      2015-7-30  Draft Enact

*****************************************************************************/
VOS_UINT16 NAS_LPP_GetDownLinkMsgSequenceNum
(
    VOS_UINT8               ucSessionIndx
)
{
    NAS_LPP_ENTITY_STRU     *pstLppCtx;

    pstLppCtx = NAS_LPP_GetLppEntityCtx();
    return (pstLppCtx->stSessionEntityPool.astLppSessionEntity[ucSessionIndx].ucLastDownSequenceNum);
}

/*****************************************************************************
 Function Name   : NAS_LPP_SetUpMsgSequenceNum
 Description     : 获取存储下行SequenceNumber
 Input           :VOS_VOID
 Output          : None
 Return          : VOS_UINT8

 History         :
    1.lifuxin      2015-7-30  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_SetDownLinkMsgSequenceNum
(
    VOS_UINT8               ucSessionIndx,
    VOS_UINT8               ucSequenceNumber
)
{
    NAS_LPP_ENTITY_STRU     *pstLppCtx;

    pstLppCtx = NAS_LPP_GetLppEntityCtx();

    pstLppCtx->stSessionEntityPool.astLppSessionEntity[ucSessionIndx].ucLastDownSequenceNum =
              ucSequenceNumber;
}


/*****************************************************************************
 Function Name   : NAS_LPP_SearchRunningPosTechByTransIndx
 Description     : 一个transaction里可能同时存在多个定位技术
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-29  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_SearchRunningPosTechByTransIndx
(
    VOS_UINT8 ucTransIndx,
    NAS_LPP_LOC_TECH_RUNING_STRU *pstPosSearchRslt
)
{
    NAS_LPP_LOC_TECH_RUNING_STRU  *pstRunLocTech;
    VOS_UINT32 ulLoop;

    pstPosSearchRslt->ucNum = 0;

    pstRunLocTech = NAS_LPP_GetRuningLocTech();

    if ( pstRunLocTech->ucNum > NAS_LPP_MAX_POS_TECH)
    {
        NAS_LPP_ERR_LOG1("Search runing pos tech by index, num overflow", pstRunLocTech->ucNum);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_SearchRunningPosTechByTransIndx_ENUM, LNAS_LPP_SearchRunningPosTechByTransIndxNumOverFlow, pstRunLocTech->ucNum);
        return;
    }

    for(ulLoop = 0; ulLoop < pstRunLocTech->ucNum; ulLoop++)
    {
        if(pstRunLocTech->astLocTechMap[ulLoop].ucTransIndx == ucTransIndx)
        {
            pstPosSearchRslt->astLocTechMap[pstPosSearchRslt->ucNum] = pstRunLocTech->astLocTechMap[ulLoop];
            pstPosSearchRslt->ucNum++;
        }
    }

    return;
}
/*****************************************************************************
 Function Name   : NAS_LPP_SearchRunningPosTechBySessionIndx
 Description     : 一个Session里可能同时存在多个定位技术
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-29  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_SearchRunningPosTechBySessionIndx
(
    VOS_UINT8 ucSessionIndx,
    NAS_LPP_LOC_TECH_RUNING_STRU *pstPosSearchRslt
)
{
    NAS_LPP_LOC_TECH_RUNING_STRU  *pstRunLocTech;
    VOS_UINT32 ulLoop;

    pstPosSearchRslt->ucNum = 0;

    pstRunLocTech = NAS_LPP_GetRuningLocTech();

    if ( pstRunLocTech->ucNum > NAS_LPP_MAX_POS_TECH)
    {
        NAS_LPP_ERR_LOG1("Search runing pos tech by index, num overflow", pstRunLocTech->ucNum);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_SearchRunningPosTechBySessionIndx_ENUM, LNAS_LPP_SearchRunningPosTechBySessionIndxNumOverFlow, pstRunLocTech->ucNum);
        return;
    }

    for(ulLoop = 0; ulLoop < pstRunLocTech->ucNum; ulLoop++)
    {
        if(pstRunLocTech->astLocTechMap[ulLoop].ucSessionIndx == ucSessionIndx)
        {
            pstPosSearchRslt->astLocTechMap[pstPosSearchRslt->ucNum] = pstRunLocTech->astLocTechMap[ulLoop];
            pstPosSearchRslt->ucNum++;
        }
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_SearchRunningPosTechByIndx2
 Description     : 一个transaction里可能同时存在多个定位技术
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-29  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_SearchRunningPosTechByIndx2
(
    VOS_UINT8 ucSessionIndx,
    VOS_UINT8 ucSessionTranIndx,
    NAS_LPP_LOC_TECH_RUNING_STRU *pstPosSearchRslt
)
{
    NAS_LPP_LOC_TECH_RUNING_STRU  *pstRunLocTech;
    VOS_UINT32 ulLoop;

    pstPosSearchRslt->ucNum = 0;

    pstRunLocTech = NAS_LPP_GetRuningLocTech();
    if ( pstRunLocTech->ucNum > NAS_LPP_MAX_POS_TECH)
    {
        NAS_LPP_ERR_LOG1("Search runing pos tech by index 2, num overflow", pstRunLocTech->ucNum);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_SearchRunningPosTechByIndx2_ENUM, LNAS_LPP_SearchRunningPosTechByIndx2TechNumOverFlow, pstRunLocTech->ucNum);
        return;
    }

    for(ulLoop = 0; ulLoop < pstRunLocTech->ucNum; ulLoop++)
    {
        if( (pstRunLocTech->astLocTechMap[ulLoop].ucSessionIndx == ucSessionIndx)
          &&(pstRunLocTech->astLocTechMap[ulLoop].ucSessionTranIndx == ucSessionTranIndx) )
        {
            pstPosSearchRslt->astLocTechMap[pstPosSearchRslt->ucNum] = pstRunLocTech->astLocTechMap[ulLoop];
            pstPosSearchRslt->ucNum++;
        }
    }

    return;
}
#if 0
/*****************************************************************************
 Function Name   : NAS_LPP_SearchSessionTransIndxByTransIndx
 Description     : 根据TransaIndx得到SessionTransIndx
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.lifuxin 00253982      2015-10-24  Draft Enact
*****************************************************************************/
VOS_UINT8 NAS_LPP_SearchSessionTransIndxByTransIndx(VOS_UINT8 ulSessionIndx, VOS_UINT8 ucTransIndx )
{
    NAS_LPP_SESSION_ENTITY_POOL_STRU        *pstSessionEntityPool = NAS_LPP_NULL_PTR;
    VOS_UINT8 ucLoop,ucSessionTransIndx;

    pstSessionEntityPool = NAS_LPP_GetLppSessionEntityPool();

    ucSessionTransIndx = PS_NULL_UINT8;
    for ( ucLoop = 0 ; ucLoop < NAS_LPP_MAX_TRANS_COUNT; ucLoop++ )
    {
        if(pstSessionEntityPool->astLppSessionEntity[ulSessionIndx].stLppTrans.aucTransElementIdx[ucLoop] == ucTransIndx)
        {
             ucSessionTransIndx = ucLoop;
             break;
        }
    }

    return ucSessionTransIndx;
}
#endif
/*****************************************************************************
 Function Name  : NAS_LPP_AddRunningPositionTech
 Description    : 获取指定定位技术的运行实体的ID
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT8

 History        :
      1.lifuxin 00253982 2015-7-20  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LPP_AddRunningPositionTech
(
    NAS_LPP_POSITION_TECH_ENUM_UINT8        enPositionTech,
    VOS_UINT8                               ucSessionIndx,
    VOS_UINT8                               ucSessionTransIndx,
    VOS_UINT8                               ucTransIndx
)
{
    NAS_LPP_LOC_TECH_RUNING_STRU  *pstRunLocTech;
    VOS_UINT32 ulLoop;

    pstRunLocTech = NAS_LPP_GetRuningLocTech();

    if ( pstRunLocTech->ucNum >= NAS_LPP_MAX_POS_TECH)
    {
        NAS_LPP_ERR_LOG2("add running tech overflow", ucSessionIndx,ucSessionTransIndx);
        TLPS_PRINT2LAYER_ERROR2(NAS_LPP_AddRunningPositionTech_ENUM, LNAS_LPP_AddRunningPositionTechRunningTechOverFlow, ucSessionIndx, ucSessionTransIndx);
        return;
    }

    ulLoop = pstRunLocTech->ucNum;

    /*该位置可用，保存*/
    pstRunLocTech->astLocTechMap[ulLoop].enPositionTech = enPositionTech;
    pstRunLocTech->astLocTechMap[ulLoop].ucSessionIndx  = ucSessionIndx;
    pstRunLocTech->astLocTechMap[ulLoop].ucSessionTranIndx  = ucSessionTransIndx;
    pstRunLocTech->astLocTechMap[ulLoop].ucTransIndx    = ucTransIndx;

    pstRunLocTech->ucNum++;

    NAS_LPP_OmAddLocTechInd(enPositionTech, pstRunLocTech);
    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_DeleteRunningPositionTech
 Description     : 删除一个正在运行的定位技术
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-29  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_DeleteRunningPositionTech(  NAS_LPP_POSITION_TECH_ENUM_UINT8 enPositionTech )
{
    NAS_LPP_LOC_TECH_RUNING_STRU  *pstRunLocTech;
    VOS_UINT32 ulLoop,ulIndex = PS_NULL_UINT32,ulLastIndex;

    pstRunLocTech = NAS_LPP_GetRuningLocTech();

    if ( (pstRunLocTech->ucNum > NAS_LPP_MAX_POS_TECH)||(0 == pstRunLocTech->ucNum) )
    {
        NAS_LPP_ERR_LOG1("del running tech overflow", pstRunLocTech->ucNum);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_DeleteRunningPositionTech_ENUM, LNAS_LPP_DeleteRunningPositionTechRunningTechNumError, pstRunLocTech->ucNum);
        return;
    }

    ulLastIndex = pstRunLocTech->ucNum - 1;

    for ( ulLoop = 0 ; ulLoop < pstRunLocTech->ucNum; ulLoop++ )
    {
        if ( pstRunLocTech->astLocTechMap[ulLoop].enPositionTech == enPositionTech)
        {
            ulIndex = ulLoop;
            break;
        }
    }

    if ( ulIndex <= ulLastIndex)
    {
        if ( ulIndex == ulLastIndex )
        {
        }
        else
        {
/*lint -e797*/
/*lint -e804*/

            NAS_LPP_MEM_MOVE_S(&(pstRunLocTech->astLocTechMap[ulIndex]),
                                sizeof(NAS_LPP_LOC_TECH_MAP_STRU),
                                &(pstRunLocTech->astLocTechMap[ulLastIndex]),
                                sizeof(NAS_LPP_LOC_TECH_MAP_STRU));
/*lint +e804*/
/*lint +e797*/
        }

        pstRunLocTech->ucNum--;

        NAS_LPP_OmDelLocTechInd( enPositionTech,  pstRunLocTech );
    }
    else
    {
        NAS_LPP_ERR_LOG2("del running tech not found,PosTch,all tech num", enPositionTech,pstRunLocTech->ucNum);
        TLPS_PRINT2LAYER_ERROR2(NAS_LPP_DeleteRunningPositionTech_ENUM, LNAS_LPP_DeleteRunningPositionTechErrorTechOrNum, enPositionTech, pstRunLocTech->ucNum);
    }

    return;
}


/*****************************************************************************
 Function Name   : NAS_LPP_InitRunningPositionTech
 Description     : 初始化
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-29  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_InitRunningLocTech( VOS_VOID )
{
    NAS_LPP_LOC_TECH_RUNING_STRU  *pstRunLocTech;

    pstRunLocTech = NAS_LPP_GetRuningLocTech();

    NAS_LPP_MEM_SET_S(pstRunLocTech,sizeof(NAS_LPP_LOC_TECH_RUNING_STRU),0,sizeof(NAS_LPP_LOC_TECH_RUNING_STRU));

}

/*****************************************************************************
 Function Name   : NAS_LPP_ClearGnssInfo
 Description     : 清空GNSS的相关信息
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.lifuxin 00253982      2015-10-21  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_ClearGnssInfo(VOS_VOID)
{
    NAS_LPP_GNSS_MEAS_RESLT_STRU       *pstGnssMeasRslt = NAS_LPP_NULL_PTR;
    VOS_UINT32                          ulLoop          = 0;
    VOS_UINT32                          ulGNSSMeasListCnt = 0;

    /*TODO:MEM*/
    pstGnssMeasRslt = NAS_LPP_GetGnssMeasRsltAddr();
    ulGNSSMeasListCnt = pstGnssMeasRslt->stGnssReqLocationInfo.stGNSSsignalMeasInfo.stGNSSMeasList.ulGNSSMeasListCnt;
    /*释放对应的消息测量ind的malloc的内存*/
    for(ulLoop = 0; ulLoop < ulGNSSMeasListCnt; ulLoop++)
    {
        NAS_LPP_MEM_FREE(pstGnssMeasRslt->stGnssReqLocationInfo.stGNSSsignalMeasInfo.stGNSSMeasList.pastGNSSMeasListArray[ulLoop]);
    }
    NAS_LPP_MEM_SET_S(pstGnssMeasRslt,sizeof(NAS_LPP_GNSS_MEAS_RESLT_STRU), 0, sizeof(NAS_LPP_GNSS_MEAS_RESLT_STRU));

    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_ReleasePosTechMeas
 Description     : 释放对应的定位测量
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-30  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_ReleasePosTechMeas
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTransIndx,
    NAS_LPP_POSITION_TECH_ENUM_UINT8    enPosTech
)
{

    if (NAS_LPP_POSITION_TECH_ECID == enPosTech)
    {
        NAS_LPP_SndLppLrrcEcidMeasReq(ucSessionIndx,ucSessionTransIndx,LPP_LRRC_LCS_MEAS_CMD_REL);
    }
    else if (NAS_LPP_POSITION_TECH_OTDOA == enPosTech)
    {
        NAS_LPP_SndOtdoaMeasReq(ucSessionIndx,ucSessionTransIndx,LPP_LRRC_LCS_MEAS_CMD_REL);
    }
    else if (NAS_LPP_POSITION_TECH_GNSS == enPosTech)
    {
        NAS_LPP_ClearGnssInfo();
    }
    else
    {
    }

    /*从正在运行的定位记录表里删除此定位*/
    NAS_LPP_DeleteRunningPositionTech(enPosTech);
}
/*****************************************************************************
 Function Name   : NAS_LPP_SetWaitMeasCnfFlag
 Description     :
 Input           : ulFlag:NAS_LPP_SLCT或NAS_LPP_NO_SLCT
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-6  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_SetWaitMeasCnfFlag
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTranIndx,
    NAS_LPP_POSITION_TECH_ENUM_UINT8    enPosTech,
    VOS_UINT32                          ulFlag
)
{
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU    *pstTransElementEntity = NAS_LPP_NULL_PTR;
    pstTransElementEntity = NAS_LPP_GetTransEntity(ucSessionIndx,ucSessionTranIndx);
    if (NAS_LPP_NULL_PTR == pstTransElementEntity)
    {
        NAS_LPP_ERR_LOG2("set flag with wrong index", ucSessionIndx, ucSessionTranIndx);
        TLPS_PRINT2LAYER_ERROR2(NAS_LPP_SetWaitMeasCnfFlag_ENUM, LNAS_LPP_SetWaitMeasCnfFlagNOTFindTransaction, ucSessionIndx, ucSessionTranIndx);
        return;
    }

    switch ( enPosTech )
    {
        case NAS_LPP_POSITION_TECH_ECID:
            pstTransElementEntity->bitOpWaitEcidMeasCnf = ulFlag;
            break;
        case NAS_LPP_POSITION_TECH_OTDOA :
            pstTransElementEntity->bitOpWaitOtdoaMeasCnf = ulFlag;
            break;
        default:
            NAS_LPP_ERR_LOG1("set flag with wrong tech", enPosTech);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_SetWaitMeasCnfFlag_ENUM, LNAS_LPP_SetWaitMeasCnfErrorTechFlag, enPosTech);
            break;
    }
}
/*****************************************************************************
 Function Name   : NAS_LPP_GetWaitMeasCnfFlag
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-6  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LPP_GetWaitMeasCnfFlag
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTranIndx,
    NAS_LPP_POSITION_TECH_ENUM_UINT8    enPosTech
)
{
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU    *pstTransElementEntity;
    VOS_UINT32 ulFlag = NAS_LPP_NO_SLCT;

    pstTransElementEntity = NAS_LPP_GetTransEntity(ucSessionIndx,ucSessionTranIndx);
    if (NAS_LPP_NULL_PTR == pstTransElementEntity)
    {
        NAS_LPP_ERR_LOG2("get flag with wrong index", ucSessionIndx, ucSessionTranIndx);
        TLPS_PRINT2LAYER_ERROR2(NAS_LPP_GetWaitMeasCnfFlag_ENUM, LNAS_LPP_NOTFindTransactionBySessionSessionTransIndex, ucSessionIndx, ucSessionTranIndx);
        return NAS_LPP_NO_SLCT;
    }

    switch ( enPosTech )
    {
        case NAS_LPP_POSITION_TECH_ECID:
            ulFlag = pstTransElementEntity->bitOpWaitEcidMeasCnf;
            break;
        case NAS_LPP_POSITION_TECH_OTDOA :
            ulFlag = pstTransElementEntity->bitOpWaitOtdoaMeasCnf;
            break;
        default:
            NAS_LPP_ERR_LOG1("Get flag with wrong tech", enPosTech);
            TLPS_PRINT2LAYER_ERROR1(NAS_LPP_GetWaitMeasCnfFlag_ENUM, LNAS_LPP_GetErrorTechFlag, enPosTech);
            break;
    }

    return ulFlag;
}



/*****************************************************************************
 Function Name   : NAS_LPP_GetMeasRsltAddr
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-28  Draft Enact

*****************************************************************************/
NAS_LPP_MEAS_RESULT_STRU*  NAS_LPP_GetMeasRsltAddr( VOS_VOID )
{
    return &(NAS_LPP_GetLppEntityCtx()->stMeasResult);
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetEcidMeasRsltAddr
 Description    : 得到保存ECID测量rslt的地址
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT8

 History        :
      1.lifuxin 00253982 2015-7-20  Draft Enact
*****************************************************************************/
NAS_LPP_ECID_MEAS_RESULT_STRU*  NAS_LPP_GetEcidMeasRsltAddr( VOS_VOID )
{
    return &(NAS_LPP_GetLppEntityCtx()->stMeasResult.stEcidMeasRslt);
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetGnssMeasRsltAddr
 Description    : 得到保存GNSS测量rslt的地址
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT8

 History        :
      1.lifuxin 00253982 2015-10-20  Draft Enact
*****************************************************************************/
NAS_LPP_GNSS_MEAS_RESLT_STRU*  NAS_LPP_GetGnssMeasRsltAddr( VOS_VOID )
{
    return &(NAS_LPP_GetLppEntityCtx()->stMeasResult.stGnssMeasRslt);
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetSessionIdBySessionIndx
 Description    : 通过sessionIndx，得到sessionId
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT8

 History        :
      1.lifuxin 00253982 2015-7-20  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_GetSessionIdBySessionIndx
(
    VOS_UINT8                           ucSessionIndx
)
{

    return (NAS_LPP_GetLppEntityCtx()->stSessionEntityPool.astLppSessionEntity[ucSessionIndx].ulSessionId);
}

/*****************************************************************************
 Function Name   : NAS_LPP_IsReqLocInfoTrans
 Description     : 判断是否是req location information的transaction
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-10-21  Draft Enact

*****************************************************************************/
VOS_BOOL  NAS_LPP_IsReqLocInfoTrans( NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransEntity )
{
    if ( pstTransEntity->ucCommCfgIndex < NAS_LPP_MAX_POS_TECH)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 Function Name   : NAS_LPP_ClearMeasRslt
 Description     :  清除测量的结果
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-10-21  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_ClearMeasRslt(NAS_LPP_POSITION_TECH_ENUM_UINT8 enPosTech)
{
    NAS_LPP_MEAS_RESULT_STRU               *pstMeasRslt;

    pstMeasRslt = NAS_LPP_GetMeasRsltAddr();

    switch ( enPosTech )
    {
        case NAS_LPP_POSITION_TECH_ECID :
            NAS_LPP_MEM_SET_S(&pstMeasRslt->stEcidMeasRslt, sizeof(NAS_LPP_ECID_MEAS_RESULT_STRU),0, sizeof(NAS_LPP_ECID_MEAS_RESULT_STRU));
            break;
        case NAS_LPP_POSITION_TECH_OTDOA :
            NAS_LPP_MEM_SET_S(&pstMeasRslt->stOtdoaMeasRslt,sizeof(NAS_LPP_OTDOA_MEAS_RESLT_STRU), 0, sizeof(NAS_LPP_OTDOA_MEAS_RESLT_STRU));
            break;
        case NAS_LPP_POSITION_TECH_GNSS :
            NAS_LPP_MEM_SET_S(&pstMeasRslt->stGnssMeasRslt, sizeof(NAS_LPP_GNSS_MEAS_RESLT_STRU),0, sizeof(NAS_LPP_GNSS_MEAS_RESLT_STRU));
            break;
        default:
            break;
    }
}

/*****************************************************************************
 Function Name   : NAS_LPP_SetEndTransFlg
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32
 History         :
    1.XiaoJun      2015-7-29  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_SetEndTransFlg( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx ,PS_BOOL_ENUM_UINT8 enTransEndFlg)
{
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransElementEntity  = NAS_LPP_NULL_PTR;
    VOS_UINT8                                ucTransIndx            = 0;

    ucTransIndx= NAS_LPP_GetTransIdIndex(ucSessionIndx,ucSessionTransIndx);
    pstTransElementEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if (NAS_LPP_NULL_PTR == pstTransElementEntity)
    {
        NAS_LPP_ERR_LOG2("wrong session index,session trans index for end flag set",ucSessionIndx,ucSessionTransIndx);
        TLPS_PRINT2LAYER_ERROR2(NAS_LPP_SetEndTransFlg_ENUM, LNAS_LPP_NOTFindTransactionBySessionSessionTransIndex, ucSessionIndx, ucSessionTransIndx);
        return;
    }

    pstTransElementEntity->ucTransEndFlag = enTransEndFlg;
}

/*****************************************************************************
 Function Name   : NAS_LPP_GetEndTransFlg
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32
 History         :
    1.LIFUXIN      2015-7-29  Draft Enact

*****************************************************************************/
VOS_UINT8  NAS_LPP_GetEndTransFlg( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx )
{
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransElementEntity  = NAS_LPP_NULL_PTR;
    VOS_UINT8                                ucTransIndx            = 0;

    ucTransIndx= NAS_LPP_GetTransIdIndex(ucSessionIndx,ucSessionTransIndx);
    pstTransElementEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if (NAS_LPP_NULL_PTR == pstTransElementEntity)
    {
        NAS_LPP_ERR_LOG2("wrong session index,session trans index for end flag set", ucSessionIndx, ucSessionTransIndx);
        TLPS_PRINT2LAYER_ERROR2(NAS_LPP_SetEndTransFlg_ENUM, LNAS_LPP_NOTFindTransactionBySessionSessionTransIndex, ucSessionIndx, ucSessionTransIndx);

        return NAS_LPP_NULL_PTR;
    }

   return pstTransElementEntity->ucTransEndFlag;
}

/*****************************************************************************
 Function Name   : NAS_LPP_SearchSessionIndx
 Description     :  根据session id搜索session entity
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-15  Draft Enact
*****************************************************************************/
VOS_UINT8 NAS_LPP_SearchSessionIndx( VOS_UINT32 ulSessionId )
{
    NAS_LPP_SESSION_ENTITY_POOL_STRU        *pstSessionEntityPool = NAS_LPP_NULL_PTR;
    VOS_UINT8 ucLoop,ucSessionIndex;

    pstSessionEntityPool = NAS_LPP_GetLppSessionEntityPool();

    ucSessionIndex = PS_NULL_UINT8;
    for ( ucLoop = 0 ; ucLoop < NAS_LPP_MAX_SESSION_COUNT; ucLoop++ )
    {
        /*在所有使用的session entity中查找*/
        if (0 != ( pstSessionEntityPool->ulSessionActiveBitmap & (0x1<<ucLoop) ) )
        {
            if ( pstSessionEntityPool->astLppSessionEntity[ucLoop].ulSessionId == ulSessionId )
            {
                ucSessionIndex = ucLoop;
                break;
            }
        }
    }

    return ucSessionIndex;
}

/*****************************************************************************
 Function Name   : NAS_LPP_GetTransElementByIndex
 Description     : 通过索引，获取在transaction entity pool里的entity实体的指
                   针。
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-16  Draft Enact

*****************************************************************************/
NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU* NAS_LPP_GetTransElementByIndex(VOS_UINT8 ucIndex)
{
    NAS_LPP_TRANSACTION_ENTITY_POOL_STRU    *pstTransEntityPool = NAS_LPP_NULL_PTR;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransEntity = NAS_LPP_NULL_PTR;

    pstTransEntityPool = NAS_LPP_GetLppTransEntityPool();
    if (ucIndex < NAS_LPP_MAX_TRANS_POOL_COUNT)
    {
        pstTransEntity = &pstTransEntityPool->astTransElementEntity[ucIndex];
    }

    return pstTransEntity;
}

/*****************************************************************************
 Function Name   : NAS_LPP_GetSessionElementByIndex
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-21  Draft Enact

*****************************************************************************/
NAS_LPP_SESSION_ENTITY_ELEMENT_STRU * NAS_LPP_GetSessionElementByIndex(VOS_UINT8 ucIndex)
{
    NAS_LPP_SESSION_ENTITY_POOL_STRU        *pstSessionEntityPool = NAS_LPP_NULL_PTR;
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU     *pstSessionEntity = NAS_LPP_NULL_PTR;

    pstSessionEntityPool = NAS_LPP_GetLppSessionEntityPool();
    if (ucIndex >= NAS_LPP_MAX_SESSION_COUNT)
    {
        return pstSessionEntity;
    }

    pstSessionEntity = &pstSessionEntityPool->astLppSessionEntity[ucIndex];
    return pstSessionEntity;
}


/*****************************************************************************
 Function Name   : NAS_LPP_SearchSessionElement
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-21  Draft Enact

*****************************************************************************/
NAS_LPP_SESSION_ENTITY_ELEMENT_STRU*  NAS_LPP_SearchSessionElement( VOS_UINT32 ulSessionId )
{
    VOS_UINT8 ucIndx;

    ucIndx = NAS_LPP_SearchSessionIndx(ulSessionId);

    return (NAS_LPP_GetSessionElementByIndex(ucIndx));
}

/*****************************************************************************
 Function Name   : NAS_LPP_DelTransEntityFromSession
 Description     : 从session把此transaction entity删除
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-17  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_DelTransEntityFromSession( NAS_LPP_SESSION_ENTITY_ELEMENT_STRU *pstSessionEntity, VOS_UINT8 ucSessionTransIndx )
{
    VOS_UINT8 ucLastIndx = 0;

    if ( (0 == pstSessionEntity->stLppTrans.ucTransIdCount)
      || (NAS_LPP_MAX_TRANS_COUNT < pstSessionEntity->stLppTrans.ucTransIdCount) )
    {
        NAS_LPP_ERR_LOG1("wrong trans num in session",pstSessionEntity->stLppTrans.ucTransIdCount);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_DelTransEntityFromSession_ENUM, LNAS_LPP_ErrorTransNumInSession, pstSessionEntity->stLppTrans.ucTransIdCount);
        return;
    }

    ucLastIndx = pstSessionEntity->stLppTrans.ucTransIdCount - 1;

    /*如果是最后一个*/
    if ( ucLastIndx == ucSessionTransIndx )
    {
        /*null*/
    }
    else
    {
        pstSessionEntity->stLppTrans.aucTransElementIdx[ucSessionTransIndx]
                = pstSessionEntity->stLppTrans.aucTransElementIdx[ucLastIndx];
    }

    pstSessionEntity->stLppTrans.ucTransIdCount--;
}

/*****************************************************************************
 Function Name   : NAS_LPP_AddTransEntityToSession
 Description     : 把trans entity实体加入到session里
 Input           : None
 Output          : None
 Return          : VOS_UITN32

 History         :
    1.XiaoJun      2015-7-20  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_LPP_AddTransEntityToSession( NAS_LPP_SESSION_ENTITY_ELEMENT_STRU *pstSessionEntity ,VOS_UINT8 ucIndex,VOS_UINT8 *pucSessionTransIndex)
{

    if ( NAS_LPP_MAX_TRANS_COUNT <= pstSessionEntity->stLppTrans.ucTransIdCount )
    {
        NAS_LPP_ERR_LOG1("overflow trans num in session",pstSessionEntity->stLppTrans.ucTransIdCount);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_AddTransEntityToSession_ENUM, LNAS_LPP_ErrorTransNumInSession, pstSessionEntity->stLppTrans.ucTransIdCount);

        return NAS_LPP_FAILURE;
    }

    *pucSessionTransIndex = pstSessionEntity->stLppTrans.ucTransIdCount;
    pstSessionEntity->stLppTrans.aucTransElementIdx[ pstSessionEntity->stLppTrans.ucTransIdCount ] = ucIndex;

    pstSessionEntity->stLppTrans.ucTransIdCount++;

    NAS_LPP_OmAddTransToSessionInd(NAS_LPP_SearchSessionIndx(pstSessionEntity->ulSessionId),
                                   ucIndex,
                                   &pstSessionEntity->stLppTrans);

    return NAS_LPP_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LPP_ReInitTransEntity
 Description     : 把transaction entity全部再次初始化
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.XiaoJun      2015-7-17  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_ReInitTransEntity
(
    VOS_UINT8       ucTransIndex,
    VOS_UINT8       ucSessionIndx,
    VOS_UINT8       ucSessionTransIndx
)
{
    NAS_LPP_TRANSACTION_ENTITY_POOL_STRU    *pstTransEntityPool = NAS_LPP_NULL_PTR;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransEntity;

    pstTransEntityPool = NAS_LPP_GetLppTransEntityPool();
    if ( ucTransIndex >= NAS_LPP_MAX_TRANS_POOL_COUNT )
    {
        NAS_LPP_ERR_LOG1("re_init wrong trans  index in pool",ucTransIndex);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_ReInitTransEntity_ENUM, LNAS_LPP_WrongTransactionIndex, ucTransIndex);
        return;
    }

    pstTransEntity = &pstTransEntityPool->astTransElementEntity[ucTransIndex];

    /*先停定时器*/
    NAS_LPP_TimerStop(ucSessionIndx,
                      ucSessionTransIndx,
                      pstTransEntity->stLppTimer.enTimerId);

    NAS_LPP_MEM_SET_S(pstTransEntity,
                      sizeof(NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU),
                      0,
                      sizeof(NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU));

    pstTransEntity->enLastUpMsgId = NAS_LPP_AIR_MSG_BUTT;
    pstTransEntity->ucCommCfgIndex = PS_NULL_UINT8;

    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_ReturnTransEntityToPool
 Description     :  把transaction entity 归还到pool里
 Input           : ucTransIndx--要归还的TransEntity在pool里对应的索引
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-17  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_ReturnTransEntityToPool( VOS_UINT8 ucTransIndex )
{
    NAS_LPP_TRANSACTION_ENTITY_POOL_STRU    *pstTransEntityPool = NAS_LPP_NULL_PTR;

    pstTransEntityPool = NAS_LPP_GetLppTransEntityPool();
    if ( ucTransIndex >= NAS_LPP_MAX_TRANS_POOL_COUNT )
    {
        NAS_LPP_ERR_LOG1("return wrong  trans  index in pool",ucTransIndex);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_ReturnTransEntityToPool_ENUM, LNAS_LPP_WrongTransactionIndex, ucTransIndex);
        return;
    }

    /* 把此trans entity在trans pool里的状态置为空闲*/

    /*lint -e502*/
    pstTransEntityPool->ulTransBitmap = (pstTransEntityPool->ulTransBitmap & (~(0x1<<ucTransIndex)));
    /*lint +e502*/

    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_ReleaseTransEntityByIndx
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-28  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_ReleaseTransEntityByIndx(VOS_UINT8 ucSessionIndx ,VOS_UINT8 ucSessionTransIndx )
{
    NAS_LPP_ReleaseTransEntity(ucSessionIndx,ucSessionTransIndx);
}


/*****************************************************************************
 Function Name   : NAS_LPP_ReleaseTransEntityElementOnly
 Description     : 释放一个transaction entity到pool里
 Input           : ucSessionTransIndx---NAS_LPP_TRANSACTION_STRU里的aucTransElementIdx[ucSessionTransIndx]
 Output          : None
 Return          : VOS_VOID

 History         :
    1.XiaoJun      2015-7-15  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LPP_ReleaseTransEntityElementOnly( VOS_UINT8 ucSessionIndx, VOS_UINT8 ucSessionTransIndx )
{
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransEntity = NAS_LPP_NULL_PTR;
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU *pstSessionEntity = NAS_LPP_NULL_PTR;
    VOS_UINT8 ucTransIndex = 0;

    pstSessionEntity = NAS_LPP_GetSessionElementByIndex(ucSessionIndx);
    if ( NAS_LPP_NULL_PTR == pstSessionEntity )
    {
        NAS_LPP_ERR_LOG1("release trans only wrong sessiong index,",ucSessionIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_ReleaseTransEntityElementOnly_ENUM, LNAS_LPP_WrongSessionIndex, ucTransIndex);
        return;
    }

    if ( ucSessionTransIndx >= pstSessionEntity->stLppTrans.ucTransIdCount )
    {
        NAS_LPP_ERR_LOG2("rel wrong session transaction indx",ucSessionTransIndx,pstSessionEntity->stLppTrans.ucTransIdCount);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_ReleaseTransEntityElementOnly_ENUM, LNAS_LPP_WrongSessionTransactionIndex, ucSessionTransIndx);
        return;
    }

    ucTransIndex = pstSessionEntity->stLppTrans.aucTransElementIdx[ucSessionTransIndx];
    pstTransEntity = NAS_LPP_GetTransElementByIndex(ucTransIndex);
    if ( NAS_LPP_NULL_PTR == pstTransEntity )
    {
        NAS_LPP_ERR_LOG1("releas trans wrong trans  index in pool",ucTransIndex);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_ReleaseTransEntityElementOnly_ENUM, LNAS_LPP_WrongSessionIndex, ucTransIndex);
        return;
    }

    /*把trans element的索引从pstSessionEntity->stLppTran删除*/
    NAS_LPP_DelTransEntityFromSession( pstSessionEntity,  ucSessionTransIndx );

    /* 归还到pool里*/
    NAS_LPP_ReturnTransEntityToPool(ucTransIndex);

    NAS_LPP_ReInitTransEntity(ucTransIndex, ucSessionIndx, ucSessionTransIndx);

    NAS_LPP_OmTransRelInd(ucSessionIndx, ucTransIndex, &pstSessionEntity->stLppTrans);

    return;
}
/*****************************************************************************
 Function Name   : NAS_LPP_ReleaseTransEntityAction
 Description     : 释放一个transaction时，释放对应的测量配置的动作
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-29  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_ReleaseTransEntityAction
(
    VOS_UINT8                               ucSessionIndx,
    VOS_UINT8                               ucSessionTransIndx
)
{
    NAS_LPP_POSITION_TECH_ENUM_UINT8    enPosTech;
    VOS_UINT8                           ucTransIndx;
    VOS_UINT32                          ulLoop;
    NAS_LPP_LOC_TECH_RUNING_STRU        stPosSearchRslt = {0};
    NAS_LPP_UP_MSG_BUFF_SEARCH_RSLT_STRU stSearchRslt = {0};
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransEntity;

    ucTransIndx = NAS_LPP_GetTransIdIndex(ucSessionIndx,ucSessionTransIndx);
    pstTransEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if ( NAS_LPP_NULL_PTR == pstTransEntity)
    {
        NAS_LPP_ERR_LOG2("relase trans err sessinon index and session trans index", ucSessionIndx,ucSessionTransIndx);
        TLPS_PRINT2LAYER_ERROR2(NAS_LPP_ReleaseTransEntityAction_ENUM, LNAS_LPP_NOTFindTransactionBySessionSessionTransIndex, ucSessionIndx, ucSessionTransIndx);
        return;
    }

    /*判断此transaction是否对应n个定位技术的测量 ,如果是，要停止对应的测量*/
    NAS_LPP_SearchRunningPosTechByTransIndx(ucTransIndx, &stPosSearchRslt);

    for ( ulLoop = 0 ; ulLoop < stPosSearchRslt.ucNum; ulLoop++ )
    {
        enPosTech = stPosSearchRslt.astLocTechMap[ulLoop].enPositionTech;
        if ( (enPosTech < NAS_LPP_POSITION_TECH_BUTT)&&(NAS_LPP_POSITION_TECH_NULL != enPosTech) )
        {
            NAS_LPP_ReleasePosTechMeas(ucSessionIndx, ucSessionTransIndx, enPosTech);
            NAS_LPP_ClearMeasRslt(enPosTech);
        };
    }

    NAS_LPP_ReleaseCommCfgInfoElementByIndex(ucTransIndx,pstTransEntity->ucCommCfgIndex);

    /*删除此transaction对应的上行Buffer:有多个删除多个*/
    NAS_LPP_SearchUpMsgBuffByTrnasId(&(pstTransEntity->stTransId),&stSearchRslt);

    for ( ulLoop = 0 ; ulLoop < stSearchRslt.ucNum; ulLoop++ )
    {
        NAS_LPP_RelUpMsgBufferByIndex(stSearchRslt.aucIndex[ulLoop]);
    }

    for ( ulLoop = 0 ; ulLoop < pstTransEntity->stFsmBuff.ucHighNum; ulLoop++ )
    {
        NAS_LPP_MEM_FREE(pstTransEntity->stFsmBuff.astHighMsg[ulLoop].pMsg);
        pstTransEntity->stFsmBuff.astHighMsg[ulLoop].pMsg = NAS_LPP_NULL_PTR;
    }

    for ( ulLoop = 0 ; ulLoop < pstTransEntity->stFsmBuff.ucLowNum; ulLoop++ )
    {
        NAS_LPP_MEM_FREE(pstTransEntity->stFsmBuff.astLowMsg[ulLoop].pMsg);
        pstTransEntity->stFsmBuff.astLowMsg[ulLoop].pMsg = NAS_LPP_NULL_PTR;
    }

}

/*****************************************************************************
 Function Name   : NAS_LPP_ReleaseTransEntity
 Description     : 释放对应的trans实体，并判断是否需要做其他的释放动作：如，
                   停测量
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-30  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_ReleaseTransEntity( VOS_UINT8 ucSessionIndx, VOS_UINT8 ucSessionTransIndx )
{

    NAS_LPP_ReleaseTransEntityAction( ucSessionIndx, ucSessionTransIndx );

    NAS_LPP_ReleaseTransEntityElementOnly( ucSessionIndx, ucSessionTransIndx );
}

/*****************************************************************************
 Function Name   : NAS_LPP_RelAllTransEntity
 Description     : VOS_VOID
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-21  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_RelAllTransEntity( VOS_VOID )
{
    NAS_LPP_SESSION_ENTITY_POOL_STRU        *pstSessionEntityPool = NAS_LPP_NULL_PTR;
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU     *pstSessionEntity = NAS_LPP_NULL_PTR;
    VOS_UINT32 ulLoop;
    VOS_UINT8 ucLoop1,ucTransIdCount;

    pstSessionEntityPool = NAS_LPP_GetLppSessionEntityPool();

    for ( ulLoop = 0 ; ulLoop < NAS_LPP_MAX_SESSION_COUNT; ulLoop++ )
    {
        /*找到一个激活的session entity*/
        if (0 != ( pstSessionEntityPool->ulSessionActiveBitmap & (0x1<<ulLoop) ) )
        {
            pstSessionEntity = (&pstSessionEntityPool->astLppSessionEntity[ulLoop]);
            ucTransIdCount = pstSessionEntity->stLppTrans.ucTransIdCount;

            if (ucTransIdCount > 0)
            {
                for ( ucLoop1 = (ucTransIdCount ) ; ucLoop1 > 0; ucLoop1-- )
                {
                    NAS_LPP_ReleaseTransEntity((VOS_UINT8)ulLoop, ucLoop1-1);
                }
            }
            /*lint -e502*/
            pstSessionEntityPool->ulSessionActiveBitmap = (pstSessionEntityPool->ulSessionActiveBitmap & (~(0x1<<ulLoop)));
            /*lint +e502*/
        }
    }

    return;
}



/*****************************************************************************
 Function Name   : NAS_LPP_MallocTransEntityIndx
 Description     : 从transaction entity pool里申请一个空闲的entity
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-15  Draft Enact

*****************************************************************************/
VOS_UINT8 NAS_LPP_MallocTransEntityIndx
(
    LPP_TRANSACTION_ID_STRU                 *pstUuTransactionId
)
{
    NAS_LPP_TRANSACTION_ENTITY_POOL_STRU    *pstTransEntityPool = NAS_LPP_NULL_PTR;
    VOS_UINT8 ucLoop;
    VOS_UINT8 ucIndex = PS_NULL_UINT8;

    pstTransEntityPool = NAS_LPP_GetLppTransEntityPool();

    for ( ucLoop = 0; ucLoop < NAS_LPP_MAX_TRANS_POOL_COUNT; ucLoop++ )
    {
        if ( 0 == (pstTransEntityPool->ulTransBitmap & (0x1<<ucLoop)) )
        {
            pstTransEntityPool->ulTransBitmap = pstTransEntityPool->ulTransBitmap | (0x1<<ucLoop);
            ucIndex = ucLoop;
            pstTransEntityPool->astTransElementEntity[ucLoop].stTransId.enInitiator =
                                                        pstUuTransactionId->enInitiator;
            pstTransEntityPool->astTransElementEntity[ucLoop].stTransId.ucTransactionNumber =
                                                        pstUuTransactionId->ucTransactionNumber;

            break;
        }
    }

    if (NAS_LPP_MAX_TRANS_POOL_COUNT <= ucIndex)
    {
        return ucIndex;
    }
    NAS_LPP_OmTransMallocInd(ucIndex,
                             pstTransEntityPool->ulTransBitmap,
                             &pstTransEntityPool->astTransElementEntity[ucIndex].stTransId);

    return ucIndex;
}

/*****************************************************************************
 Function Name   : NAS_LPP_MallocTransEntityIndx
 Description     : 从transaction entity pool里申请一个空闲的entity
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.lifuxin 00253982      2015-7-24  Draft Enact

*****************************************************************************/
NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU* NAS_LPP_MallocTransEntity
(
    LPP_TRANSACTION_ID_STRU                 *pstUuTransactionId
)
{

    VOS_UINT8 ucIndex = PS_NULL_UINT8;

    ucIndex = NAS_LPP_MallocTransEntityIndx(pstUuTransactionId);
    if(PS_NULL_UINT8 == ucIndex)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_MallocTransEntity: Transaction space is full!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_MallocTransEntity_ENUM, LNAS_LPP_MALLOCTRANSENTITYFAIL);
        return NAS_LPP_NULL_PTR;
    }

    return NAS_LPP_GetTransElementByIndex(ucIndex);
}

/*****************************************************************************
 Function Name   : NAS_LPP_SearchTransEntityIndx
 Description     :  搜索transaction 实体
 Input           : None
 Output          : pucTransIndx---在transaction entity pool里的位置,
                   pucSessionTransIndx-- pucTransIndx-在session entity里aucTransElementIdx[NAS_LPP_MAX_TRANS_COUNT]的位置
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-16  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_SearchTransEntityIndx(
    VOS_UINT8                       ucSessionIndx,
    NAS_LPP_TRANS_ID_STRU          *pstTransId,
    VOS_UINT8                      *pucTransIndx,
    VOS_UINT8                      *pucSessionTransIndx )
{
    NAS_LPP_SESSION_ENTITY_POOL_STRU        *pstSessionEntityPool = NAS_LPP_NULL_PTR;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransEntity = NAS_LPP_NULL_PTR;
    VOS_UINT8 ucTranIndx, ucLoop, ucTransIdCount;

    pstSessionEntityPool = NAS_LPP_GetLppSessionEntityPool();

    *pucTransIndx = PS_NULL_UINT8;
    *pucSessionTransIndx = PS_NULL_UINT8;

    if ( ucSessionIndx >= NAS_LPP_MAX_SESSION_COUNT )
    {
        NAS_LPP_ERR_LOG1("search wrong session Id when search trans entity",ucSessionIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_SearchTransEntityIndx_ENUM, LNAS_LPP_SEARCHWRONGSESSIONBYINDEX, ucSessionIndx);
        return;
    }

    ucTransIdCount = pstSessionEntityPool->astLppSessionEntity[ucSessionIndx].stLppTrans.ucTransIdCount;
    for ( ucLoop = 0 ; ucLoop < ucTransIdCount; ucLoop++ )
    {
        ucTranIndx = pstSessionEntityPool->astLppSessionEntity[ucSessionIndx].stLppTrans.aucTransElementIdx[ucLoop];
        pstTransEntity = NAS_LPP_GetTransElementByIndex(ucTranIndx);
        if(NAS_LPP_NULL_PTR == pstTransEntity)
        {
            NAS_LPP_ERR_LOG1("search wrong transaction index",ucTranIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_SearchTransEntityIndx_ENUM, LNAS_LPP_SEARCHWRONGTRANSACTIONINDEX, ucTranIndx);
            continue;
        }
        if ((pstTransEntity->stTransId.ucTransactionNumber == pstTransId->ucTransactionNumber)
          &&(pstTransEntity->stTransId.enInitiator == pstTransId->enInitiator) )
        {
            *pucTransIndx = ucTranIndx;
            *pucSessionTransIndx = ucLoop;
            break;
        }
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_IsThereOtherTransactionRunningInSession
 Description     : 根据sessionId去查找当前session下，是否多个除pstTransId之外的transaction正在running
 Input           : pstTransId:表示除之外的transaction
 Output          : VOS_TRUE:    表示除了pstTransId之外，还有其他的transaction在本session运行。
 Return          : UINT32

 History         :
    1.lifuxin      2015-9-6  Draft Enact

*****************************************************************************/
VOS_BOOL NAS_LPP_IsThereOtherTransactionRunningInSession
(
    VOS_UINT8                       ucSessionIndx,
    NAS_LPP_TRANS_ID_STRU          *pstTransId
)
{
    NAS_LPP_SESSION_ENTITY_POOL_STRU        *pstSessionEntityPool = NAS_LPP_NULL_PTR;
    VOS_UINT8  ucTransIdCount;
    VOS_UINT8  ucTransIndx = PS_NULL_UINT8, ucSessionTransIndx = PS_NULL_UINT8;


    pstSessionEntityPool = NAS_LPP_GetLppSessionEntityPool();

    if ( ucSessionIndx >= NAS_LPP_MAX_SESSION_COUNT )
    {
        NAS_LPP_ERR_LOG1("NAS_LPP_IsThereOtherTransactionRunningInSession: ",ucSessionIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_IsThereOtherTransactionRunningInSession_ENUM, LNAS_LPP_SEARCHWRONGSESSIONBYINDEX, ucSessionIndx);
        return PS_FALSE;
    }

    ucTransIdCount = pstSessionEntityPool->astLppSessionEntity[ucSessionIndx].stLppTrans.ucTransIdCount;
    if( ucTransIdCount > 0)
    {
        NAS_LPP_SearchTransEntityIndx(ucSessionIndx,pstTransId,&ucTransIndx,&ucSessionTransIndx);
        if (PS_NULL_UINT8 == ucTransIndx)
        {
            /*指定的transaction就不在session里*/
            return PS_TRUE;
        }
        else
        {
            /*pstTransId指定的transaction在sessioon里*/
            if ( ucTransIdCount > 1)
            {
                /*有其他的transaction在运行*/
                return PS_TRUE;
            }
            else
            {
                return PS_FALSE;
            }
        }
    }
    else
    {
        /*没有*/
        return PS_FALSE;
    }

}

/*****************************************************************************
 Function Name   : NAS_LPP_SearchTransEntity
 Description     : 根据session id和transaction number搜索transaction element
                   ，返回transaction element指针
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-20  Draft Enact

*****************************************************************************/
NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU * NAS_LPP_SearchTransEntity
(
    VOS_UINT32                          ulSessionId,
    NAS_LPP_TRANS_ID_STRU               *pstTransId,
    VOS_UINT8                           *pucSessionTransIndx
)
{
    VOS_UINT8 ucSessionIndx,ucTransEntityIndx;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransEntity = NAS_LPP_NULL_PTR;

    ucSessionIndx = NAS_LPP_SearchSessionIndx(ulSessionId);

    NAS_LPP_SearchTransEntityIndx(ucSessionIndx,pstTransId,&ucTransEntityIndx,pucSessionTransIndx);

    pstTransEntity = NAS_LPP_GetTransElementByIndex(ucTransEntityIndx);

    return pstTransEntity;
}
/*****************************************************************************
 Function Name   : NAS_LPP_CreatNewTrans
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-26  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_CreatNewTrans
(
    VOS_UINT8       ucSessionIndx ,
    VOS_UINT8      *pucSessionTransIndx,
    VOS_UINT8      *pucTransIndex
)
{

    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU    *pstSessionEntity = NAS_LPP_NULL_PTR;
    LPP_TRANSACTION_ID_STRU                 stUuTransactionId;
    VOS_UINT8 ucIndex;

    *pucTransIndex = PS_NULL_UINT8;
    *pucSessionTransIndx = PS_NULL_UINT8;

    pstSessionEntity = NAS_LPP_GetSessionElementByIndex(ucSessionIndx);
    if ( NAS_LPP_NULL_PTR == pstSessionEntity )
    {
        NAS_LPP_ERR_LOG1("creat new trans with wrong session index", ucSessionIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_CreatNewTrans_ENUM, LNAS_LPP_SEARCHWRONGSESSIONBYINDEX, ucSessionIndx);
        return;
    }

    if (pstSessionEntity->stLppTrans.ucTransIdCount >= NAS_LPP_MAX_TRANS_COUNT)
    {
        NAS_LPP_ERR_LOG1("creat new trans with  session full", pstSessionEntity->stLppTrans.ucTransIdCount);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_CreatNewTrans_ENUM, LNAS_LPP_ERRORSESIONTRANSACTIONCOUNT, pstSessionEntity->stLppTrans.ucTransIdCount);
        return;
    }

    stUuTransactionId.enInitiator = LPP_INITIATOR_TYPE_TARGET_DEVICE;
    stUuTransactionId.ucTransactionNumber = NAS_LPP_ApplyTransNum();
    ucIndex = NAS_LPP_MallocTransEntityIndx(&stUuTransactionId);
    if ( PS_NULL_UINT8 == ucIndex )
    {
        NAS_LPP_ERR_LOG("creat new trans malloc trans fail" );
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_CreatNewTrans_ENUM, LNAS_LPP_MALLOCTRANSENTITYFAIL);
        return;
    }

    *pucTransIndex = ucIndex;

    (VOS_VOID)NAS_LPP_AddTransEntityToSession(pstSessionEntity,ucIndex,pucSessionTransIndx);
}
/*****************************************************************************
 Function Name   : NAS_LPP_SessionEntityReInit
 Description     : VOS_VOID
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-15  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_SessionEntityReInit( VOS_UINT8 ucSessionIndx )
{
    VOS_UINT8 ucLoop,ucTransIdCount;
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU *pstSessionEntity = NAS_LPP_NULL_PTR;

    pstSessionEntity = NAS_LPP_GetSessionElementByIndex(ucSessionIndx);
    if ( NAS_LPP_NULL_PTR == pstSessionEntity )
    {
        NAS_LPP_ERR_LOG1("session reinit  wrong sessiong index,",ucSessionIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_SessionEntityReInit_ENUM, LNAS_LPP_SEARCHWRONGSESSIONBYINDEX, ucSessionIndx);
        return;
    }

    ucTransIdCount = pstSessionEntity->stLppTrans.ucTransIdCount;

    if ( ucTransIdCount > 0 )
    {
        /*先把单个transaction实体单独释放掉,从最后一个删除*/
        for ( ucLoop = (ucTransIdCount) ; ucLoop > 0; ucLoop-- )
        {
            NAS_LPP_ReleaseTransEntity(ucSessionIndx, ucLoop-1);
        }
    }

    if(NAS_LPP_NULL_PTR != pstSessionEntity->stSequenceNumInvalid.hTimer)
    {
        NAS_LPP_TimerStop(ucSessionIndx, PS_NULL_UINT32, TI_NAS_LPP_SEQUENCE_NUMBER_INVALID);
    }

    NAS_LPP_MEM_SET_S(pstSessionEntity,sizeof(NAS_LPP_SESSION_ENTITY_ELEMENT_STRU), 0, sizeof(NAS_LPP_SESSION_ENTITY_ELEMENT_STRU));

}

/*****************************************************************************
 Function Name   : NAS_LPP_MallocSessionEntity
 Description     : 为最新的一个session申请一个session实体
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-15  Draft Enact

*****************************************************************************/
NAS_LPP_SESSION_ENTITY_ELEMENT_STRU* NAS_LPP_MallocSessionEntity( VOS_UINT32  ulSessionId )
{
    NAS_LPP_SESSION_ENTITY_POOL_STRU        *pstSessionEntityPool = NAS_LPP_NULL_PTR;
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU     *pstSessionEntity = NAS_LPP_NULL_PTR;
    VOS_UINT32 ulLoop;

    pstSessionEntityPool = NAS_LPP_GetLppSessionEntityPool();

    for ( ulLoop = 0 ; ulLoop < NAS_LPP_MAX_SESSION_COUNT; ulLoop++ )
    {
        /*找到一个空闲的session entity*/
        if (0 == ( pstSessionEntityPool->ulSessionActiveBitmap & (0x1<<ulLoop) ) )
        {
            /*将此session entity置为忙*/
            pstSessionEntityPool->ulSessionActiveBitmap = pstSessionEntityPool->ulSessionActiveBitmap | (0x1<<ulLoop);
            pstSessionEntity = (&pstSessionEntityPool->astLppSessionEntity[ulLoop]);
            pstSessionEntity->ulSessionId = ulSessionId;
            break;
        }
    }

    NAS_LPP_OmSessionMallocInd((VOS_UINT8)ulLoop,ulSessionId,pstSessionEntityPool->ulSessionActiveBitmap);

    return pstSessionEntity;
}
/*****************************************************************************
 Function Name   : NAS_LPP_ReleaseSessionEntity
 Description     :  释放一个session 实体
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.XiaoJun      2015-7-15  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_ReleaseSessionEntity(VOS_UINT32 ulSessionId)
{
    NAS_LPP_SESSION_ENTITY_POOL_STRU        *pstSessionEntityPool = NAS_LPP_NULL_PTR;
    VOS_UINT8 ucIndex;

    pstSessionEntityPool = NAS_LPP_GetLppSessionEntityPool();

    ucIndex = NAS_LPP_SearchSessionIndx(ulSessionId);

    if ( ucIndex < NAS_LPP_MAX_SESSION_COUNT )
    {
    /*lint -e502*/
        pstSessionEntityPool->ulSessionActiveBitmap
            = (pstSessionEntityPool->ulSessionActiveBitmap & (~(0x1<<ucIndex)));
    /*lint +e502*/

        NAS_LPP_SessionEntityReInit(ucIndex);
    }
    else
    {
        NAS_LPP_ERR_LOG1("release wrong session Id",ulSessionId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_ReleaseSessionEntity_ENUM, LNAS_LPP_SearchWrongSessionBySessionID, ulSessionId);

    }

    NAS_LPP_OmSessionRelInd(ucIndex,ulSessionId,pstSessionEntityPool->ulSessionActiveBitmap);

}
/*****************************************************************************
 Function Name   : NAS_LPP_ReleaseSessionEntityByIndex
 Description     : 根据session index释放session
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-5  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_ReleaseSessionEntityByIndex( VOS_UINT8 ucSessionIndx )
{
    NAS_LPP_SESSION_ENTITY_POOL_STRU        *pstSessionEntityPool = NAS_LPP_NULL_PTR;
    VOS_UINT32 ulSessionId = PS_NULL_UINT32;

    pstSessionEntityPool = NAS_LPP_GetLppSessionEntityPool();
    if ( ucSessionIndx < NAS_LPP_MAX_SESSION_COUNT )
    {
    /*lint -e502*/
        pstSessionEntityPool->ulSessionActiveBitmap
            = (pstSessionEntityPool->ulSessionActiveBitmap & (~(0x1<<ucSessionIndx)));
    /*lint +e502*/
        ulSessionId = pstSessionEntityPool->astLppSessionEntity[ucSessionIndx].ulSessionId;

        NAS_LPP_SessionEntityReInit(ucSessionIndx);
    }
    else
    {
        NAS_LPP_ERR_LOG1("release wrong session index",ucSessionIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_ReleaseSessionEntityByIndex_ENUM, LNAS_LPP_SEARCHWRONGSESSIONBYINDEX, ucSessionIndx);

    }

    NAS_LPP_OmSessionRelInd(ucSessionIndx,ulSessionId,pstSessionEntityPool->ulSessionActiveBitmap);
}


/*****************************************************************************
 Function Name   : NAS_LPP_ReleaseAllSession
 Description     : 释放所有的session
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-29  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_ReleaseAllSession( VOS_VOID )
{
    NAS_LPP_SESSION_ENTITY_POOL_STRU        *pstSessionEntityPool = NAS_LPP_NULL_PTR;
    VOS_UINT32 ulLoop;
    VOS_UINT32 ulSessionId = PS_NULL_UINT32;

    pstSessionEntityPool = NAS_LPP_GetLppSessionEntityPool();

    for ( ulLoop = 0 ; ulLoop < NAS_LPP_MAX_SESSION_COUNT; ulLoop++ )
    {
        if ( 0 != (pstSessionEntityPool->ulSessionActiveBitmap & (0x1<<ulLoop)) )
        {
        /*lint -e502*/
            pstSessionEntityPool->ulSessionActiveBitmap
                = (pstSessionEntityPool->ulSessionActiveBitmap & (~(0x1<<ulLoop)));
        /*lint +e502*/

            ulSessionId = pstSessionEntityPool->astLppSessionEntity[ulLoop].ulSessionId;

            NAS_LPP_SessionEntityReInit((VOS_UINT8)ulLoop);

            NAS_LPP_OmSessionRelInd((VOS_UINT8)ulLoop,ulSessionId,pstSessionEntityPool->ulSessionActiveBitmap);
        }
    }
}


/*****************************************************************************
 Function Name   : NAS_LPP_MsgDuplicateDetect
 Description     : LPP 下行消息的重复检查
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-7-15  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_LPP_MsgDuplicateDetect( VOS_UINT32 ulSessionId, VOS_UINT8 ucNewMsgSequenecNum )
{
    NAS_LPP_SESSION_ENTITY_POOL_STRU        *pstSessionEntityPool = NAS_LPP_NULL_PTR;
    VOS_UINT8 ucIndex;

    NAS_LPP_NORM_LOG("NAS_LPP_MsgDuplicateDetect is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_MsgDuplicateDetect_ENUM, LNAS_LPP_MsgDuplicateDetectEnter);
    pstSessionEntityPool = NAS_LPP_GetLppSessionEntityPool();

    /*根据session id搜索到session entity*/
    ucIndex = NAS_LPP_SearchSessionIndx(ulSessionId);

    /*如果session没有搜索到，返回错误值*/
    if ( ucIndex >= NAS_LPP_MAX_SESSION_COUNT )
    {
        NAS_LPP_INFO_LOG1("Fisrt Lpp Msg",ulSessionId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_MsgDuplicateDetect_ENUM, LNAS_LPP_SearchWrongSessionBySessionID, ucIndex);
        return NAS_LPP_SUCCESS;
    }

    /*如果这个session没有收到过下行LPP消息*/
    if (PS_FALSE == pstSessionEntityPool->astLppSessionEntity[ucIndex].enRcvedDownMsg)
    {
        pstSessionEntityPool->astLppSessionEntity[ucIndex].enRcvedDownMsg = PS_TRUE;
        return NAS_LPP_SUCCESS;
    }

    /*如果sequence number是重复的，返回重复*/
    if ( ucNewMsgSequenecNum == pstSessionEntityPool->astLppSessionEntity[ucIndex].ucLastDownSequenceNum )
    {
        NAS_LPP_ERR_LOG2("discard duplicate msg,sessionId,newSeqNum",ulSessionId,ucNewMsgSequenecNum);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_MsgDuplicateDetect_ENUM, LNAS_LPP_DuplicateMessageSeqNum, ucNewMsgSequenecNum);
        return NAS_LPP_MSG_DUPLICATE;
    }
    else
    {
        return NAS_LPP_SUCCESS;
    }
}

/*****************************************************************************
 Function Name   : NAS_LPP_GetUpMsgSequenceNum
 Description     : 为将要发送的上行LPP消息获取一个sequence number
 Input           :VOS_VOID
 Output          : None
 Return          : VOS_UINT8

 History         :
    1.XiaoJun      2015-7-15  Draft Enact

*****************************************************************************/
VOS_UINT8 NAS_LPP_GetUpMsgSequenceNum( VOS_VOID )
{
    NAS_LPP_ENTITY_STRU     *pstLppCtx;
    VOS_UINT8                ucSequencNum;

    pstLppCtx = NAS_LPP_GetLppEntityCtx();

    ucSequencNum = pstLppCtx->ucUpSequenceNumMax;
    pstLppCtx->ucUpSequenceNumMax++;

    return ucSequencNum;
}

/*****************************************************************************
 Function Name   : NAS_LPP_ApplyTransNum
 Description     : 当UE创建、发起一个transaction时，需要申请一个transaction
                   number。
 Input           :VOS_VOID
 Output          : None
 Return          : VOS_UINT8

 History         :
    1.XiaoJun      2015-7-15  Draft Enact

*****************************************************************************/
VOS_UINT8 NAS_LPP_ApplyTransNum( VOS_VOID )
{
    NAS_LPP_ENTITY_STRU     *pstLppCtx;
    VOS_UINT8 ucTransNum;

    pstLppCtx = NAS_LPP_GetLppEntityCtx();
    ucTransNum = pstLppCtx->ucTransNum;
    pstLppCtx->ucTransNum++;

    return ucTransNum;
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetUpLinkMsgIndetity
 Description    : 得到上行缓存buffer的消息的识别信息
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-7-13  新开发
*****************************************************************************/
NAS_LPP_MSG_IDENTITY_STRU* NAS_LPP_GetUpLinkMsgIndetity
(
    VOS_UINT32          ulUpBufferIndex
)
{
    return &(NAS_LPP_GetLppUpMsgBuffPool()->astLppUpMsg[ulUpBufferIndex].stLppMsgIdentity);
}
/*****************************************************************************
 Function Name  : NAS_LPP_GetUpLinkSessionId
 Description    : 得到上行缓存buffer的sessionID
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-7-13  新开发
*****************************************************************************/
VOS_UINT32 NAS_LPP_GetUpLinkSessionId
(
    VOS_UINT32          ulUpBufferIndex
)
{
    return NAS_LPP_GetUpLinkMsgIndetity(ulUpBufferIndex)->ulSessionId;
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetUpLinkSequenceNumber
 Description    : 得到上行缓存中的sequenceNumber
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-7-13  新开发
*****************************************************************************/
VOS_UINT32 NAS_LPP_GetUpLinkTransactionNumber
(
    VOS_UINT32          ulUpBufferIndex
)
{
    return NAS_LPP_GetUpLinkMsgIndetity(ulUpBufferIndex)->stTransId.ucTransactionNumber;
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetUpLinkSequenceNumber
 Description    : 得到上行缓存中的sequenceNumber
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-7-13  新开发
*****************************************************************************/
VOS_UINT32 NAS_LPP_GetUpLinkSequenceNumber
(
    VOS_UINT32          ulUpBufferIndex
)
{
    return NAS_LPP_GetUpLinkMsgIndetity(ulUpBufferIndex)->usSequnceNum;
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetDownlinkMsgType
 Description    : 得到下行空口消息的类型
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-7-13  新开发
*****************************************************************************/
VOS_UINT32 NAS_LPP_GetDownlinkMsgType
(
    LPP_MESSAGE_STRU                   *pstLppMsg
)
{
    return  (pstLppMsg->stLppMessageBody.u.stC1.ulChoice);
}

/*****************************************************************************
 Function Name  : NAS_LPP_FindUpLinkBuffer
 Description    : 根据网络侧下发的ACK indicator以及sessionID找到对应的buffer实体
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-7-13  新开发
*****************************************************************************/
LPP_UPLINK_MSG_BUF_STRU* NAS_LPP_FindUpLinkBuffer
(
    VOS_UINT8                           ucSequenceNum,
    VOS_UINT32                          ulSessionId
)
{
    VOS_UINT32                      ulLoop              = 0;
    NAS_LPP_UP_MSG_BUFF_POOL_STRU  *pstUpMsgBuffPool    = NAS_LPP_NULL_PTR;

    pstUpMsgBuffPool = NAS_LPP_GetLppUpMsgBuffPool();

    for(ulLoop = 0; ulLoop < NAS_LPP_MAX_BUFF_MSG_COUNT; ulLoop++)
    {
        /*等于1表示对应的buffer是数据实体的，则查找*/
        if(0 != ((pstUpMsgBuffPool->ulBitMap) & (0x1<<ulLoop)))
        {
            if((NAS_LPP_GetUpLinkSessionId(ulLoop) == ulSessionId)
                && (NAS_LPP_GetUpLinkSequenceNumber(ulLoop) == ucSequenceNum))
            {
                /*如果找到了，则返回对应的上行缓存buffer*/
                return &(NAS_LPP_GetLppUpMsgBuffPool()->astLppUpMsg[ulLoop]);
            }
        }
    }

    /*如果遍历完成没有找到，则返回空*/
    return NAS_LPP_NULL_PTR;
}

/*****************************************************************************
 Function Name   : NAS_LPP_SearchUpMsgBuff
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-30  Draft Enact

*****************************************************************************/
LPP_UPLINK_MSG_BUF_STRU*   NAS_LPP_SearchUpMsgBuff
(
    VOS_UINT32             ulSessionId,
    NAS_LPP_TRANS_ID_STRU *pstTransId
)
{
    VOS_UINT32                      ulLoop              = 0;
    NAS_LPP_UP_MSG_BUFF_POOL_STRU  *pstUpMsgBuffPool    = NAS_LPP_NULL_PTR;

    pstUpMsgBuffPool = NAS_LPP_GetLppUpMsgBuffPool();

    for(ulLoop = 0; ulLoop < NAS_LPP_MAX_BUFF_MSG_COUNT; ulLoop++)
    {
        /*等于1表示对应的buffer是数据实体的，则查找*/
        if(0 != ((pstUpMsgBuffPool->ulBitMap) & (0x1<<ulLoop)))
        {
            if( (NAS_LPP_GetUpLinkSessionId(ulLoop) == ulSessionId)
              &&(NAS_LPP_GetUpLinkTransactionNumber(ulLoop) == pstTransId->ucTransactionNumber)
              &&(NAS_LPP_UPLINK_MSG_TYPE_PROCESS == NAS_LPP_GetUpLinkMsgIndetity(ulLoop)->enUplinkMsgType))
            {
                /*如果找到了，则返回对应的上行缓存buffer*/
                return &(NAS_LPP_GetLppUpMsgBuffPool()->astLppUpMsg[ulLoop]);
            }
        }
    }

    /*如果遍历完成没有找到，则返回空*/
    return NAS_LPP_NULL_PTR;
}

/*****************************************************************************
 Function Name   : NAS_LPP_SearchUpMsgBuffByTrnasId
 Description     : 根据trans id搜寻上行的缓冲buffer
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.XiaoJun      2015-8-6  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_SearchUpMsgBuffByTrnasId
(
    NAS_LPP_TRANS_ID_STRU                *pstTransId,
    NAS_LPP_UP_MSG_BUFF_SEARCH_RSLT_STRU *pstSearchRslt
)
{
    VOS_UINT32                      ulLoop              = 0;
    NAS_LPP_UP_MSG_BUFF_POOL_STRU  *pstUpMsgBuffPool    = NAS_LPP_NULL_PTR;
    LPP_UPLINK_MSG_BUF_STRU        *pstLppUpMsgBuf      = NAS_LPP_NULL_PTR;

    pstUpMsgBuffPool = NAS_LPP_GetLppUpMsgBuffPool();

    pstSearchRslt->ucNum = 0;

    for(ulLoop = 0; ulLoop < NAS_LPP_MAX_BUFF_MSG_COUNT; ulLoop++)
    {
        /*等于1表示对应的buffer是数据实体的，则查找*/
        if(0 != ((pstUpMsgBuffPool->ulBitMap) & (0x1<<ulLoop)))
        {
            pstLppUpMsgBuf = &(pstUpMsgBuffPool->astLppUpMsg[ulLoop]);

            if( (pstLppUpMsgBuf->stLppMsgIdentity.stTransId.ucTransactionNumber == pstTransId->ucTransactionNumber)
              &&(pstLppUpMsgBuf->stLppMsgIdentity.stTransId.enInitiator == pstTransId->enInitiator) )
            {
                pstSearchRslt->aucIndex[pstSearchRslt->ucNum] = (VOS_UINT8)ulLoop;
                pstSearchRslt->ucNum++;

                /*如果装满了，退出*/
                if ( pstSearchRslt->ucNum >= NAS_LPP_MAX_UP_MSG_PER_TRANSACTION)
                {
                    NAS_LPP_ERR_LOG2("search up buffer overflow,transnum,init", pstTransId->ucTransactionNumber,pstTransId->enInitiator);
                    TLPS_PRINT2LAYER_ERROR1(NAS_LPP_SearchUpMsgBuffByTrnasId_ENUM, LNAS_LPP_TransactionUpBufferOverFlow, pstSearchRslt->ucNum);
                    break;
                }

            }
        }
    }


    return;
}



/*****************************************************************************
 Function Name   : NAS_LPP_MallocUpMsgBuffer
 Description     : 为上行LPP消息申请重传的缓冲buffer
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-20  Draft Enact

*****************************************************************************/
LPP_UPLINK_MSG_BUF_STRU  *NAS_LPP_MallocUpMsgBuffer(VOS_UINT8 *pucUplinkBuffIndx)
{
    VOS_UINT32 ulLoop;
    NAS_LPP_UP_MSG_BUFF_POOL_STRU *pstUpMsgBuffPool;
    LPP_UPLINK_MSG_BUF_STRU *pstLppUpMsgBuf = NAS_LPP_NULL_PTR;

    pstUpMsgBuffPool = NAS_LPP_GetLppUpMsgBuffPool();
    *pucUplinkBuffIndx = PS_NULL_UINT8;

    for ( ulLoop = 0 ; ulLoop < NAS_LPP_MAX_BUFF_MSG_COUNT; ulLoop++ )
    {
        if ( 0 == (pstUpMsgBuffPool->ulBitMap & (0x1<<ulLoop)) )
        {
            pstLppUpMsgBuf = &pstUpMsgBuffPool->astLppUpMsg[ulLoop];

            pstUpMsgBuffPool->ulBitMap = pstUpMsgBuffPool->ulBitMap | (0x1<<ulLoop);
            *pucUplinkBuffIndx  = (VOS_UINT8)ulLoop;
            break;
        }
    }

    if (*pucUplinkBuffIndx >= NAS_LPP_MAX_BUFF_MSG_COUNT)
    {
        NAS_LPP_OmUpMsgBuffMallocFailInd(pstUpMsgBuffPool->astUpmsgSeq,pstUpMsgBuffPool->ulBitMap);
    }

    return pstLppUpMsgBuf;
}

/*****************************************************************************
 Function Name   : NAS_LPP_GetUpLinkMsgBuffSeqByIndex
 Description     : 通过上行缓存buffer的索引值或者存储索引值的结构实体
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lifuxin 00253982      2015-9-2  Draft Enact

*****************************************************************************/
NAS_LPP_UP_MSG_SEQUENCE_STRU* NAS_LPP_GetUpLinkMsgBuffSeqByIndex(VOS_UINT8 ucIndex, VOS_UINT8 *pucLoop)
{
    VOS_UINT8                       ucLoop              = 0;
    NAS_LPP_UP_MSG_BUFF_POOL_STRU  *pstUpMsgBuffPool    = NAS_LPP_NULL_PTR;
    *pucLoop  = PS_NULL_UINT8;

    pstUpMsgBuffPool = NAS_LPP_GetLppUpMsgBuffPool();
    for(ucLoop = 0; ucLoop < NAS_LPP_MAX_BUFF_MSG_COUNT; ucLoop++)
    {
        if((PS_TRUE == pstUpMsgBuffPool->astUpmsgSeq[ucLoop].ucUsedFlag)
           &&(ucIndex == pstUpMsgBuffPool->astUpmsgSeq[ucLoop].ucUpLinkBuffIndex))
        {
            *pucLoop = ucLoop;
            return &(pstUpMsgBuffPool->astUpmsgSeq[ucLoop]);
        }
    }

    return NAS_LPP_NULL_PTR;
}

/*****************************************************************************
 Function Name   : NAS_LPP_ClearUpLinkMsgIndex
 Description     : 清空上行indx的相关项，并且同时将后面存储的数据依次移动
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lifuxin 00253982      2015-9-2  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_ClearUpLinkMsgIndex(VOS_UINT8 ucUpLinkBuffIndex)
{
    NAS_LPP_UP_MSG_SEQUENCE_STRU        *pstUpLinkSeq       = NAS_LPP_NULL_PTR;
    VOS_UINT8                            ucUplinkSeqLoop    = 0;
    VOS_UINT32                           ulLoop             = 0;
    NAS_LPP_UP_MSG_BUFF_POOL_STRU       *pstUpMsgBuffPool    = NAS_LPP_NULL_PTR;

    pstUpMsgBuffPool = NAS_LPP_GetLppUpMsgBuffPool();
    TLPS_PRINT2LAYER_INFO(NAS_LPP_ClearUpLinkMsgIndex_ENUM, LNAS_LPP_Func_Enter);
    pstUpLinkSeq = NAS_LPP_GetUpLinkMsgBuffSeqByIndex(ucUpLinkBuffIndex, &ucUplinkSeqLoop);
    if(NAS_LPP_NULL_PTR == pstUpLinkSeq)
    {
        NAS_LPP_ERR_LOG1("NAS_LPP_ClearUpLinkMsgIndex: Don't find Uplink Seq, UpBuffer Index =", ucUpLinkBuffIndex);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_ClearUpLinkMsgIndex_ENUM, LNAS_LPP_SEARCH_UPLINK_BUFFER_FAIL, ucUpLinkBuffIndex);
        return;
    }

    /*移动的时候自然会覆盖原有index逻辑， 显示的写上，方便理解*/
    pstUpLinkSeq->ucUsedFlag = PS_FALSE;
    pstUpLinkSeq->ucUpLinkBuffIndex = PS_NULL_UINT8;

    /*假设删除的就是最后一个成员，则直接返回，不用移动*/
    if((NAS_LPP_MAX_BUFF_MSG_COUNT - 1) == ucUplinkSeqLoop)
    {
        return;
    }

    for(ulLoop = ucUplinkSeqLoop; ulLoop < NAS_LPP_MAX_BUFF_MSG_COUNT - 1; ulLoop++)
    {
        pstUpMsgBuffPool->astUpmsgSeq[ulLoop].ucUsedFlag        =
                                    pstUpMsgBuffPool->astUpmsgSeq[ulLoop + 1].ucUsedFlag;
        pstUpMsgBuffPool->astUpmsgSeq[ulLoop].ucUpLinkBuffIndex =
                                    pstUpMsgBuffPool->astUpmsgSeq[ulLoop + 1].ucUpLinkBuffIndex;
    }

    /*移动完成后，最后一个成员赋值成没有使用的状态*/
    pstUpMsgBuffPool->astUpmsgSeq[ulLoop].ucUsedFlag        = PS_FALSE;
    pstUpMsgBuffPool->astUpmsgSeq[ulLoop].ucUpLinkBuffIndex = PS_NULL_UINT8;

    return;
}


/*****************************************************************************
 Function Name   : NAS_LPP_RelUpMsgBuffer
 Description     : 释放上行LPP重传的buffer
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.XiaoJun      2015-7-20  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_RelUpMsgBuffer( LPP_UPLINK_MSG_BUF_STRU **ppstLppUpMsgBuf )
{
    VOS_UINT32 ulLoop;
    NAS_LPP_UP_MSG_BUFF_POOL_STRU *pstUpMsgBuffPool;

    pstUpMsgBuffPool = NAS_LPP_GetLppUpMsgBuffPool();

    for ( ulLoop = 0 ; ulLoop < NAS_LPP_MAX_BUFF_MSG_COUNT; ulLoop++ )
    {
        if ( *ppstLppUpMsgBuf == &pstUpMsgBuffPool->astLppUpMsg[ulLoop] )
        {
            TLPS_PRINT2LAYER_INFO1(NAS_LPP_RelUpMsgBuffer_ENUM, LNAS_LPP_SUCC_RELEASE_UPLINK_MSG_BUFFER, ulLoop);
            /*清空缓存buffer的index*/
            NAS_LPP_ClearUpLinkMsgIndex((VOS_UINT8)ulLoop);

            /*lint -e502*/
            pstUpMsgBuffPool->ulBitMap = (pstUpMsgBuffPool->ulBitMap &(~(0x1<<ulLoop)));
            /*lint +e502*/

            NAS_LPP_MEM_SET_S(*ppstLppUpMsgBuf,sizeof(LPP_UPLINK_MSG_BUF_STRU), 0,sizeof(LPP_UPLINK_MSG_BUF_STRU));

            NAS_LPP_OmUpMsgBuffRelInd((VOS_UINT8)ulLoop,pstUpMsgBuffPool->astUpmsgSeq,pstUpMsgBuffPool->ulBitMap);
            break;
        }
    }

    *ppstLppUpMsgBuf = NAS_LPP_NULL_PTR;
}

/*****************************************************************************
 Function Name   : NAS_LPP_RelUpMsgBufferByIndex
 Description     : 根据index释放上行msg的buffer
 Input           :VOS_UINT8 ucIndex
 Output          : None
 Return          : VOS_VOID

 History         :
    1.XiaoJun      2015-8-6  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_RelUpMsgBufferByIndex( VOS_UINT8 ucIndex )
{
    NAS_LPP_UP_MSG_BUFF_POOL_STRU *pstUpMsgBuffPool;

    pstUpMsgBuffPool = NAS_LPP_GetLppUpMsgBuffPool();

    if (ucIndex >= NAS_LPP_MAX_BUFF_MSG_COUNT)
    {
        NAS_LPP_ERR_LOG1("wrong index for release up msg", ucIndex);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RelUpMsgBufferByIndex_ENUM, LNAS_LPP_ERROR_INDEX_FOR_UPLINK_MSG, ucIndex);
        return;
    }

    /*清空缓存buffer的index*/
    NAS_LPP_ClearUpLinkMsgIndex(ucIndex);

    /*lint -e502*/
    pstUpMsgBuffPool->ulBitMap = (pstUpMsgBuffPool->ulBitMap &(~(0x1<<ucIndex)));
    /*lint +e502*/

    NAS_LPP_MEM_SET_S(&(pstUpMsgBuffPool->astLppUpMsg[ucIndex]),sizeof(LPP_UPLINK_MSG_BUF_STRU),0,sizeof(LPP_UPLINK_MSG_BUF_STRU));

    NAS_LPP_OmUpMsgBuffRelInd(ucIndex,pstUpMsgBuffPool->astUpmsgSeq,pstUpMsgBuffPool->ulBitMap);
    return;
}


/*****************************************************************************
 Function Name   : NAS_LPP_MallocCommCfgInfoElement
 Description     : 获取一个空闲的公共配置的单元
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-7  Draft Enact

*****************************************************************************/
VOS_UINT8  NAS_LPP_MallocCommCfgInfoElementIndex( VOS_UINT8 ucTransIndex )
{
    NAS_LPP_COMM_CONFIG_INFO_POOL_STRU  *pstCommCfgInfoPool;
    VOS_UINT8 ucIndex = PS_NULL_UINT8;
    VOS_UINT8 ucLoop;

    pstCommCfgInfoPool = NAS_LPP_GetCommCfgInfoPool();
    for ( ucLoop = 0 ; ucLoop < NAS_LPP_MAX_POS_TECH; ucLoop++ )
    {
        if ( 0 == (pstCommCfgInfoPool->ulBitmap & (0x1 << ucLoop)) )
        {
            pstCommCfgInfoPool->ulBitmap = (pstCommCfgInfoPool->ulBitmap | (0x1 << ucLoop));
            ucIndex = ucLoop;
            break;
        }
    }

    NAS_LPP_OmCommCfgPoolMallocInd(ucTransIndex,ucIndex,pstCommCfgInfoPool->ulBitmap);

    return ucIndex;
}
/*****************************************************************************
 Function Name   : NAS_LPP_ReleaseCommCfgInfoElementByIndex
 Description     : 通过index释放公共配置单元
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-7  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_ReleaseCommCfgInfoElementByIndex( VOS_UINT8 ucTransIndex, VOS_UINT8 ucIndex)
{
    NAS_LPP_COMM_CONFIG_INFO_POOL_STRU  *pstCommCfgInfoPool;

    pstCommCfgInfoPool = NAS_LPP_GetCommCfgInfoPool();
    if ( ucIndex >= NAS_LPP_MAX_POS_TECH )
    {
        NAS_LPP_INFO_LOG1("release wrong comm cfg pool index", ucIndex);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_ReleaseCommCfgInfoElementByIndex_ENUM, LNAS_LPP_SEARCH_WRONG_CFG_INDEX, ucIndex);
        return;
    }
    /*lint -e502*/
    pstCommCfgInfoPool->ulBitmap = (pstCommCfgInfoPool->ulBitmap & (~(0x1 << ucIndex)));
    /*lint +e502*/

    NAS_LPP_MEM_SET_S( &pstCommCfgInfoPool->astLppCommCfgInfo[ucIndex],sizeof(NAS_LPP_COMM_CONFIG_INFO_STRU), 0, sizeof(NAS_LPP_COMM_CONFIG_INFO_STRU) );

    pstCommCfgInfoPool->astLppCommCfgInfo[ucIndex].stReportCriteria.enType = NAS_LPP_REPORT_LOCATION_TYPE_BUTT;

    NAS_LPP_OmCommCfgPoolRelInd( ucTransIndex, ucIndex, pstCommCfgInfoPool->ulBitmap);

    return;
}
/*****************************************************************************
 Function Name   : NAS_LPP_GetCommCfgInfoElementByIndex
 Description     : 获取comm cfg info的单元的地址
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-7  Draft Enact

*****************************************************************************/
NAS_LPP_COMM_CONFIG_INFO_STRU *NAS_LPP_GetCommCfgInfoElementByIndex( VOS_UINT8 ucIndex)
{
    NAS_LPP_COMM_CONFIG_INFO_POOL_STRU  *pstCommCfgInfoPool;
    NAS_LPP_COMM_CONFIG_INFO_STRU       *pstLppCommCfgInfo = NAS_LPP_NULL_PTR;

    pstCommCfgInfoPool = NAS_LPP_GetCommCfgInfoPool();

    if ( ucIndex >= NAS_LPP_MAX_POS_TECH )
    {
        NAS_LPP_ERR_LOG1("get wrong comm cfg pool index", ucIndex);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_GetCommCfgInfoElementByIndex_ENUM, LNAS_LPP_SEARCH_WRONG_INDEX_FOR_POSITION_TECH, ucIndex);
        return pstLppCommCfgInfo;
    }

    pstLppCommCfgInfo = &(pstCommCfgInfoPool->astLppCommCfgInfo[ucIndex]);

    return pstLppCommCfgInfo;
}


/*****************************************************************************
 Function Name   : NAS_LPP_LppPlmn2NasPlmn
 Description     : 把LPP空口的PLMN格式转成当前NAS的通用格式
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-19  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_LppPlmn2NasPlmn
(
    LPP_MTA_COMMON_PLMN_IDENTITY_STRU   *pstLppPlmnId,
    VOS_UINT8                           *pucNasPlmnId
)
{
    pucNasPlmnId[0] = pstLppPlmnId->aucMcc[0] & 0x0f;
    pucNasPlmnId[0] = pucNasPlmnId[0] | ((VOS_UINT8)( pstLppPlmnId->aucMcc[1] << 4));

    pucNasPlmnId[1] = pstLppPlmnId->aucMcc[2] & 0x0f;

    if ( 3 == pstLppPlmnId->ucMncNum )
    {
        pucNasPlmnId[1] = pucNasPlmnId[1] | ((VOS_UINT8)(pstLppPlmnId->aucMnc[2] << 4));
    }

    pucNasPlmnId[2] = pstLppPlmnId->aucMnc[0] &0x0f;
    pucNasPlmnId[2] = pucNasPlmnId[2] | ((VOS_UINT8)(pstLppPlmnId->aucMnc[1] << 4));
}
/*****************************************************************************
 Function Name   : NAS_LPP_NasPlmn2LppPlmn
 Description     : 把NAS 通用的PLMN转成LPP空口的PLMN格式
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-19  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_NasPlmn2LppPlmn
(
    VOS_UINT8                           *pucNasPlmnId,
    LPP_MTA_COMMON_PLMN_IDENTITY_STRU   *pstLppPlmnId
)
{
    /*plmn, 规则是 MCC0->PLMN0低4， MCC1->PLMN0高4， MCC2->PLMN1低4， MNC0->PLMN2低4,
    MNC1->PLMN2高4， MNC2->PLMN1 高4，这个如果是FF，则表示只有2个数字*/
    pstLppPlmnId->aucMcc[0] = pucNasPlmnId[0] & 0x0f;

    pstLppPlmnId->aucMcc[1] = (pucNasPlmnId[0] & 0xf0) >> 4;

    pstLppPlmnId->aucMcc[2] = pucNasPlmnId[1] & 0x0f;

    pstLppPlmnId->aucMnc[0] = pucNasPlmnId[2] & 0x0f;

    pstLppPlmnId->aucMnc[1] = (pucNasPlmnId[2] & 0xf0) >> 4;
    if(0x0f != ((pucNasPlmnId[1] & 0xf0) >> 4))
    {
        pstLppPlmnId->ucMncNum = 3;
        pstLppPlmnId->aucMnc[2] = (pucNasPlmnId[1] & 0xf0) >> 4;
    }
    else
    {
        pstLppPlmnId->ucMncNum = 2;
    }
}
/*****************************************************************************
 Function Name   : NAS_LPP_OtdoaAssistDataChng
 Description     : 当前是否有otdoa相关的辅助数据在接收provide assist data时
                   变化了，
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-2  Draft Enact

*****************************************************************************/
VOS_BOOL  NAS_LPP_IsOtdoaAssistDataChng( VOS_VOID )
{
    NAS_LPP_CONFIG_PARA_STRU               *pstCfgPara;

    pstCfgPara = NAS_LPP_GetCfgPara();

    /*如果otdoa的辅助数据有变化，1、配置LRRC前，provide location info时不上报otdoa的；2/otdoa的measure ind不处理*/

    if (NAS_LPP_SLCT == pstCfgPara->bitOtdoaAssisChng)
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}
/*****************************************************************************
 Function Name   : NAS_LPP_IsGnssAssistDataChng
 Description     : gnss的辅助数据是否变化
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-2  Draft Enact

*****************************************************************************/
VOS_BOOL  NAS_LPP_IsGnssAssistDataChng( VOS_VOID )
{
    NAS_LPP_CONFIG_PARA_STRU               *pstCfgPara;

    pstCfgPara = NAS_LPP_GetCfgPara();

    /*如果otdoa的辅助数据有变化，1、配置LRRC前，provide location info时不上报gnss的；2/gnss的measure ind不处理*/
    if (NAS_LPP_SLCT == pstCfgPara->bitGnssAssisChng)
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 Function Name   : NAS_LPP_SecuMemCpy
 Description     : 安全memcpy
 Input           : VOS_VOID* pDst, VOS_UINT32 ulMaxBuffer, const VOS_VOID* pSrc,
                   VOS_UINT32  ulLength, VOS_UINT32 ulLineNO, VOS_UINT32 ulFileID
 Output          : None
 Return          : VOS_INT32

 History         :
    1.z00297373    2015-12-28  Draft Enact
*****************************************************************************/
VOS_INT32 NAS_LPP_SecuMemCpy
(
    VOS_VOID            * pDst,
    VOS_UINT32          ulMaxBuffer,
    const VOS_VOID      * pSrc,
    VOS_UINT32          ulLength,
    VOS_UINT32          ulLineNO,
    VOS_UINT32          ulFileID
)
{
    /*如果源地址和目的地址重叠，需改用TLPS_MEM_MOVE_S，否则安全拷贝失败 */
    if(((pSrc > pDst) && ((VOS_UINT8 *)pSrc <= ((VOS_UINT8 *)pDst + ulMaxBuffer)))
        ||((pDst> pSrc) && ((VOS_UINT8 *)pDst <= ((VOS_UINT8 *)pSrc + ulLength)))
        || (pSrc == pDst))
    {
        return TLPS_MEM_MOVE_S((pDst), (ulMaxBuffer), (pSrc), (ulLength), (ulLineNO), (ulFileID));
    }
    else
    {
        return TLPS_MEM_CPY_S((pDst), (ulMaxBuffer), (pSrc), (ulLength), (ulLineNO), (ulFileID));
    }
}


/*lint +e701*/

#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
