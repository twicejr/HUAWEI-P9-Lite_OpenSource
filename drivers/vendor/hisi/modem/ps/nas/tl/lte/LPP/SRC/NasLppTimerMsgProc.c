/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasLppTimerMsgProc.c
    Description : 处理定时器超时消息
    History     :
    1. lifuxin 00253982 2015-7-7  新开发
******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/

#include    "PsCommonDef.h"
#include    "NasLppTimerMsgProc.h"
#include    "NasLppPublic.h"
#include    "NasLppEmmMsgProc.h"
#include    "NasLppLrrcMsgProc.h"
#include    "NasLppOm.h"
#include    "NasLppSendMsg.h"
#include    "NasLppIntraMsgProc.h"
#include    "NasLppUpPublic.h"

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
#define    THIS_FILE_ID            PS_FILE_ID_NASLPPTIMERMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLPPTIMERMSGPROC_C




#if (FEATURE_LPP == FEATURE_ON)


/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name   : NAS_LPP_TimerInit
 Description     : 定时器的初始化
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-7-31  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_TimerInit( VOS_VOID )
{

    NAS_LPP_TimerReg(TI_NAS_LPP_UPLINK_MSG_RETRANS  , NAS_LPP_RcvUpMsgRetransTimer,      TI_NAS_LPP_UPLINK_MSG_RETRANS_TIMER_LEN    );
    NAS_LPP_TimerReg(TI_NAS_LPP_WAIT_CN_ASSIST_DATA , NAS_LPP_RcvWaitCnAssistDataTimer,  TI_NAS_LPP_WAIT_CN_ASSIST_DATA_TIMER_LEN    );
    NAS_LPP_TimerReg(TI_NAS_LPP_WAIT_LRRC_MEAS_CNF  , NAS_LPP_RcvWaitLrrcMeasCnfTimer,   TI_NAS_LPP_WAIT_LRRC_MEAS_CNF_TIMER_LEN    );
    NAS_LPP_TimerReg(TI_NAS_LPP_WAIT_GNSS_CAP_CNF   , NAS_LPP_RcvWaitGnssCapCnfTimer,    TI_NAS_LPP_WAIT_GNSS_CAP_TIMER_LEN   );
    NAS_LPP_TimerReg(TI_NAS_LPP_WAIT_INTRA_DATE_CNF , NAS_LPP_RcvIntraDataCnfTimerExpire,NAS_LPP_GetLppIntraDataCnfTimerLen()  );
    NAS_LPP_TimerReg(TI_NAS_LPP_WAIT_EST_CNF        , NAS_LPP_RcvWaitEstCnfTimer,        TI_NAS_LPP_WAIT_EST_CNF_TIMER_LEN  );
    NAS_LPP_TimerReg(TI_NAS_LPP_WAIT_RE_EST         , NAS_LPP_RcvWaitReEstTimer,         0  );
    NAS_LPP_TimerReg(TI_NAS_LPP_RESPONSE_TIMER      , NAS_LPP_RcvWaitResponseTimer,      0  );
    NAS_LPP_TimerReg(TI_NAS_LPP_PERIODICAL_REPORT   , NAS_LPP_RcvWaitPeriodicalTimer,    0  );
    NAS_LPP_TimerReg(TI_NAS_LPP_REPORT_DURATION     , NAS_LPP_RcvWaitReportDurationTimer,0  );
    NAS_LPP_TimerReg(TI_NAS_LPP_LOCATION_INVALID    , NAS_LPP_RcvLocationInvalidTimer,   NAS_LPP_GNSS_LOC_INFO_INVALID_TIMER_LEN  );
    NAS_LPP_TimerReg(TI_NAS_LPP_UP_PERIODICAL_REPORT, NAS_LPP_RcvUpPeriodicalReportTimer,0  );
    NAS_LPP_TimerReg(TI_NAS_LPP_UP_REPORT_DURATION  , NAS_LPP_RcvUpReportDurationTimer,  0  );
    NAS_LPP_TimerReg(TI_NAS_LPP_UP_RESPONSE_TIMER   , NAS_LPP_RcvUpResponseTimer,        0  );
    NAS_LPP_TimerReg(TI_NAS_LPP_UP_WAIT_CN_ASSIST_DATA, NAS_LPP_RcvUpWaitCnAssistDataTimer,TI_NAS_LPP_UP_WAIT_CN_ASSIST_DATA_LEN  );
    NAS_LPP_TimerReg(TI_NAS_LPP_UP_WAIT_LRRC_ECID_MEAS_CNF, NAS_LPP_RcvUpWaitLrrcEcidMeasCnfTimer,TI_NAS_LPP_WAIT_LRRC_MEAS_CNF_TIMER_LEN  );
    NAS_LPP_TimerReg(TI_NAS_LPP_UP_WAIT_LRRC_OTDOA_MEAS_CNF, NAS_LPP_RcvUpWaitLrrcOtdoaMeasCnfTimer,TI_NAS_LPP_WAIT_LRRC_MEAS_CNF_TIMER_LEN  );
    NAS_LPP_TimerReg(TI_NAS_LPP_SEQUENCE_NUMBER_INVALID, NAS_LPP_RcvWaitSequenceNumberTimer,TI_NAS_LPP_SEQUENCE_NUMBER_INVALID_LEN  );
}

/*****************************************************************************
 Function Name   : NAS_LPP_RcvWaitSequenceNumberTimer
 Description     : Sequence Number Invalid定时器超时
 Input           : ucSessionIndx session的索引
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lifuxin      2015-11-24  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LPP_RcvWaitSequenceNumberTimer
(
    VOS_UINT8                       ucSessionIndx,
    VOS_UINT8                       ucSessionTransIndx,
    VOS_UINT8                       ucUpReqTechType,
    VOS_VOID                       *pRcvMsg
)
{
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU     *pstSessionEntity = NAS_LPP_NULL_PTR;

    NAS_LPP_INFO_LOG("NAS_LPP_RcvWaitSequenceNumberTimer enter !");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvUpWaitSequenceNumberTimer_ENUM, LNAS_LPP_Func_Enter);

    pstSessionEntity = NAS_LPP_GetSessionEntity(ucSessionIndx);
    if(NAS_LPP_NULL_PTR == pstSessionEntity)
    {
        NAS_LPP_ERR_LOG2("NAS_LPP_RcvWaitSequenceNumberTimer: don't find SessionEntity!", ucSessionIndx, ucSessionTransIndx);

        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvUpWaitSequenceNumberTimer_ENUM, LNAS_LPP_GetSessionEntityFail);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvUpWaitSequenceNumberTimer_ENUM, LNAS_LPP_SessionIndex,ucSessionIndx);
        return;
    }

    pstSessionEntity->enRcvedDownMsg = PS_FALSE;

    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_RcvUpWaitLrrcOtdoaMeasCnfTimer
 Description     : 用户面wait LRRC OTDOA 测量回复定时器超时
 Input           : enPosTechType 用户面请求定位技术类型
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lifuxin      2015-11-24  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LPP_RcvUpWaitLrrcOtdoaMeasCnfTimer
(
    VOS_UINT8                       ucSessionIndx,
    VOS_UINT8                       ucSessionTransIndx,
    VOS_UINT8                       ucUpReqTechType,
    VOS_VOID                       *pRcvMsg
)
{
    NAS_LPP_UP_ECID_INFO_STRU              *pstLppUpEcidInfo    = NAS_LPP_NULL_PTR;

    pstLppUpEcidInfo    = NAS_LPP_GetLppUpEcidCtx();

    NAS_LPP_INFO_LOG("NAS_LPP_RcvUpWaitLrrcOtdoaMeasCnfTimer");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvUpWaitLrrcOtdoaMeasCnfTimer_ENUM, LNAS_LPP_Func_Enter);

    /*上报OTDOA测量不可用，测量error*/
    NAS_LPP_SndUpLppMtaOtdoaMeasmentInd(LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_UNABLE_TO_MEAS_ANY_NEIGHBOUR_CELL);
    if(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID_AND_OTDOA == ucUpReqTechType)
    {
        /*如果同时请求OTDOA以及ECID*/
        if((LPP_UP_STATE_WAIT_LRRC_MEAS_IND == pstLppUpEcidInfo->enLppUpState)
           || (LPP_UP_STATE_WAIT_LRRC_ECID_MEAS_CNF == pstLppUpEcidInfo->enLppUpState))
        {
            /*ECID测量可用,或者ECID的测量cnf还没有回复*/
            NAS_LPP_UPClrOtdoaCtx();
        }
        else if(LPP_UP_STATE_IDLE == pstLppUpEcidInfo->enLppUpState)
        {
            /*ECID也测量也不可用*/
            NAS_LPP_UPClrEntity();
        }
        else
        {
        }
    }
    else if(NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA == ucUpReqTechType)
    {
        /*如果单请求OTDOA，则上报OTDOA测量error*/

        NAS_LPP_UPClrOtdoaCtx();
    }
    else
    {
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_RcvUpWaitLrrcEcidMeasCnfTimer
 Description     : 用户面wait LRRC ECID 测量回复定时器超时
 Input           : enPosTechType 用户面请求定位技术类型
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lifuxin      2015-11-24  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LPP_RcvUpWaitLrrcEcidMeasCnfTimer
(
    VOS_UINT8                       ucSessionIndx,
    VOS_UINT8                       ucSessionTransIndx,
    VOS_UINT8                       ucUpReqTechType,
    VOS_VOID                       *pRcvMsg
)
{
    NAS_LPP_UP_OTDOA_INFO_STRU             *pstLppUpOtdoaInfo   = NAS_LPP_NULL_PTR;

    pstLppUpOtdoaInfo   = NAS_LPP_GetLppUpOtdoaCtx();

    NAS_LPP_INFO_LOG("NAS_LPP_RcvUpWaitLrrcEcidMeasCnfTimer");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvUpWaitLrrcEcidMeasCnfTimer_ENUM, LNAS_LPP_Func_Enter);

    NAS_LPP_SndUpLppMtaEcidMeasmentInd(LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_REQ_MEAS_NOT_AVAIL);
    if(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID_AND_OTDOA == ucUpReqTechType)
    {
        /*如果同时请求OTDOA以及ECID*/
        if((LPP_UP_STATE_WAIT_LRRC_MEAS_IND == pstLppUpOtdoaInfo->enLppUpState)
           || (LPP_UP_STATE_WAIT_LRRC_OTDOA_MEAS_CNF == pstLppUpOtdoaInfo->enLppUpState))
        {
            /*OTDOA测量可用,或者OTDOA的测量cnf还没有回复*/
            NAS_LPP_UPClrEcidCtx();
        }
        else if(LPP_UP_STATE_IDLE == pstLppUpOtdoaInfo->enLppUpState)
        {
            /*OTDOA也测量也不可用*/
            NAS_LPP_UPClrEntity();
        }
        else
        {
        }
    }
    else if(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID == ucUpReqTechType)
    {
        /*如果单请求ECID，则上报ECID测量error*/

        NAS_LPP_UPClrEcidCtx();
    }
    else
    {
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_RcvUpWaitCnAssistDataTimer
 Description     : 用户面wait cn Assist Data定时器超时
 Input           : enPosTechType 用户面请求定位技术类型
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lifuxin      2015-11-24  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LPP_RcvUpWaitCnAssistDataTimer
(
    VOS_UINT8                       ucSessionIndx,
    VOS_UINT8                       ucSessionTransIndx,
    VOS_UINT8                       ucUpReqTechType,
    VOS_VOID                       *pRcvMsg
)
{
    NAS_LPP_UP_ECID_INFO_STRU              *pstLppUpEcidInfo    = NAS_LPP_NULL_PTR;

    pstLppUpEcidInfo    = NAS_LPP_GetLppUpEcidCtx();

    NAS_LPP_INFO_LOG("NAS_LPP_RcvUpWaitCnAssistDataTimer");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvUpWaitCnAssistDataTimer_ENUM, LNAS_LPP_Func_Enter);

    /*如果该定时器超时，则说明是一定是先来OTDOA的测量请求，没有辅助数据
     LPP主动请求辅助数据的场景，此时直接回复OTDOA的测量eror即可*/
    NAS_LPP_SndUpLppMtaOtdoaMeasmentInd(LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_UNABLE_TO_MEAS_ANY_NEIGHBOUR_CELL);
    if(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID_AND_OTDOA == ucUpReqTechType)
    {
        /*如果同时请求OTDOA以及ECID*/
        if((LPP_UP_STATE_WAIT_LRRC_MEAS_IND == pstLppUpEcidInfo->enLppUpState)
           || (LPP_UP_STATE_WAIT_LRRC_ECID_MEAS_CNF == pstLppUpEcidInfo->enLppUpState))
        {
            /*ECID测量可用,或者ECID的测量cnf还没有回复*/
            NAS_LPP_UPClrOtdoaCtx();
        }
        else if(LPP_UP_STATE_IDLE == pstLppUpEcidInfo->enLppUpState)
        {
            /*ECID也测量也不可用*/
            NAS_LPP_UPClrEntity();
        }
        else
        {
        }
    }
    else if(NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA == ucUpReqTechType)
    {
        /*如果单请求OTDOA，则上报OTDOA测量error*/
        NAS_LPP_UPClrOtdoaCtx();
    }
    else
    {
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_RcvUpResponseTimer
 Description     : 用户面response定时器超时
 Input           : enPosTechType 用户面请求定位技术类型
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lifuxin      2015-11-24  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LPP_RcvUpResponseTimer
(
    VOS_UINT8                       ucSessionIndx,
    VOS_UINT8                       ucSessionTransIndx,
    VOS_UINT8                       ucUpReqTechType,
    VOS_VOID                       *pRcvMsg
)
{
    NAS_LPP_INFO_LOG("NAS_LPP_RcvUpResponseTimer");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvUpResponseTimer_ENUM, LNAS_LPP_Func_Enter);

    if(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID_AND_OTDOA == ucUpReqTechType)
    {
        /*同时上报场景如果定时器超时说明一定有一个测量在超时期间LRRC没有上报测量IND*/
        if(PS_TRUE == NAS_LPP_GetEcidLrrcMeasFlag())
        {
            /*OTDOA测量LRRC没有上报*/
            NAS_LPP_SndUpLppMtaEcidMeasAndOtodaErrInd(LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_UNABLE_TO_MEAS_ANY_NEIGHBOUR_CELL);
        }
        else if(PS_TRUE == NAS_LPP_GetOtodaLrrcMeasFlag())
        {
            /*ECID测量没有上报*/
            NAS_LPP_SndUpLppMtaOtodaMeasAndEcidErrInd(LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_REQ_MEAS_NOT_AVAIL);
        }
        else
        {
            /*ECID和OTDOA测量都没有上报*/
            NAS_LPP_SndUpLppMtaEcidAndOtodaMeasmentInd(LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_REQ_MEAS_NOT_AVAIL,
                                                      LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_UNABLE_TO_MEAS_ANY_NEIGHBOUR_CELL);
        }

        NAS_LPP_UPClrEntity();
    }
    else if(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID == ucUpReqTechType)
    {
        /*单独上报ECID测量场景，LRRC在超时期间没有上报测量IND*/
        NAS_LPP_SndUpLppMtaEcidMeasmentInd(LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_REQ_MEAS_NOT_AVAIL);

        NAS_LPP_UPClrEcidCtx();
    }
    else if(NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA == ucUpReqTechType)
    {
        /*单独上报OTDOA测量场景，LRRC在超时期间没有上报测量IND*/
        NAS_LPP_SndUpLppMtaOtdoaMeasmentInd(LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_UNABLE_TO_MEAS_ANY_NEIGHBOUR_CELL);

        NAS_LPP_UPClrOtdoaCtx();
    }
    else
    {
        NAS_LPP_ERR_LOG("NAS_LPP_RcvUpResponseTimer: req pos type error");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvUpResponseTimer_ENUM, LNAS_LPP_PosReqTechErr);
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_RcvUpReportDurationTimer
 Description     : 用户面duration定时器超时
 Input           : enPosTechType 用户面请求定位技术类型
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lifuxin      2015-11-24  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LPP_RcvUpReportDurationTimer
(
    VOS_UINT8                       ucSessionIndx,
    VOS_UINT8                       ucSessionTransIndx,
    VOS_UINT8                       ucUpReqTechType,
    VOS_VOID                       *pRcvMsg
)
{
    NAS_LPP_INFO_LOG("NAS_LPP_RcvUpReportDurationTimer");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvUpReportDurationTimer_ENUM, LNAS_LPP_Func_Enter);

    /*触发上报的场景只有跟ECID相关，则说明当前一定是单ECID的上报场景*/
    if(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID == ucUpReqTechType)
    {
        /*跟信令面保持一致，duration定时器超时，也上报一次位置信息*/
        NAS_LPP_SndUpLppMtaMeasInd(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID);
        NAS_LPP_UPClrEcidCtx();
    }
    else
    {
        NAS_LPP_ERR_LOG("NAS_LPP_RcvUpReportDurationTimer: req pos type error");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvUpReportDurationTimer_ENUM, LNAS_LPP_PosReqTechErr);
    }

    return;
}
/*****************************************************************************
 Function Name   : NAS_LPP_SndUpLppMtaPeriodReportEcidAndOtdoaMeasInd
 Description     : 用户面周期性定时器超时给MTA发送消息逻辑
 Input           : enPosTechType 用户面请求定位技术类型
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangensheng      2015-12-16  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LPP_SndUpLppMtaPeriodReportEcidAndOtdoaMeasInd()
{

    /*同时上报场景*/
    if((PS_TRUE == NAS_LPP_GetEcidLrrcMeasFlag())
       && (PS_TRUE == NAS_LPP_GetOtodaLrrcMeasFlag()))
    {
        /*ECID以及OTDOA的测量都有效*/
        NAS_LPP_SndUpLppMtaMeasInd(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID_AND_OTDOA);
    }
    else if((PS_TRUE == NAS_LPP_GetEcidLrrcMeasFlag())
            && (PS_FALSE == NAS_LPP_GetOtodaLrrcMeasFlag()))
    {
        /*ECID的测量有效，OTDOA的测量无效*/
        NAS_LPP_SndUpLppMtaEcidMeasAndOtodaErrInd(LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_UNABLE_TO_MEAS_ANY_NEIGHBOUR_CELL);
    }
    else if((PS_FALSE == NAS_LPP_GetEcidLrrcMeasFlag())
            && (PS_TRUE == NAS_LPP_GetOtodaLrrcMeasFlag()))
    {
        /*ECID的测量无效，OTDOA的测量有效*/
        NAS_LPP_SndUpLppMtaOtodaMeasAndEcidErrInd(LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_REQ_MEAS_NOT_AVAIL);
    }
    else
    {
        NAS_LPP_SndUpLppMtaEcidAndOtodaMeasmentInd(LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_REQ_MEAS_NOT_AVAIL,
                                                  LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_UNABLE_TO_MEAS_ANY_NEIGHBOUR_CELL);
    }
}

/*****************************************************************************
 Function Name   : NAS_LPP_SndUpLppMtaPeriodReprotMeasInd
 Description     : 用户面周期性定时器超时给MTA发送消息逻辑
 Input           : enPosTechType 用户面请求定位技术类型
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lifuxin      2015-11-24  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LPP_SndUpLppMtaPeriodReprotMeasInd
(
    VOS_UINT8                       ucUpReqTechType
)
{
    NAS_LPP_INFO_LOG("NAS_LPP_SndUpLppMtaPeriodReprotMeasInd");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SndUpLppMtaPeriodReprotMeasInd_ENUM, LNAS_LPP_Func_Enter);

    if(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID_AND_OTDOA == ucUpReqTechType)
    {
        /* 同时上报ECID和OTDOA，圈复杂度超限提取 */
        NAS_LPP_SndUpLppMtaPeriodReportEcidAndOtdoaMeasInd();
    }
    else if(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID == ucUpReqTechType)
    {
        /*仅请求ECID场景*/
        if(PS_TRUE == NAS_LPP_GetEcidLrrcMeasFlag())
        {
            /*有ECID*/
            NAS_LPP_SndUpLppMtaMeasInd(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID);
        }
        else
        {
            /*无ECID测量*/
            NAS_LPP_SndUpLppMtaEcidMeasmentInd(LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_REQ_MEAS_NOT_AVAIL);
        }
    }
    else if(NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA == ucUpReqTechType)
    {
        /*仅请求OTDOA场景*/
        if(PS_TRUE == NAS_LPP_GetOtodaLrrcMeasFlag())
        {
            /*有OTDOA测量*/
            NAS_LPP_SndUpLppMtaMeasInd(NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA);
        }
        else
        {
            /*无OTDOA测量*/
            NAS_LPP_SndUpLppMtaOtdoaMeasmentInd(LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_UNABLE_TO_MEAS_ANY_NEIGHBOUR_CELL);
        }
    }
    else
    {
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_UpStartPeriodReportTimer
 Description     : 用户面周期性定时器超时
 Input           : enPosTechType 用户面请求定位技术类型
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lifuxin      2015-11-24  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LPP_UpStartPeriodReportTimer
(
    VOS_UINT8                       ucUpReqTechType
)
{
    if(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID_AND_OTDOA == ucUpReqTechType)
    {
        NAS_LPP_UpTimerStart(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID_AND_OTDOA,
                             TI_NAS_LPP_UP_PERIODICAL_REPORT);
    }
    else if(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID == ucUpReqTechType)
    {
        NAS_LPP_UpTimerStart(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID,
                             TI_NAS_LPP_UP_PERIODICAL_REPORT);
    }
    else if(NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA == ucUpReqTechType)
    {
        NAS_LPP_UpTimerStart(NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA,
                             TI_NAS_LPP_UP_PERIODICAL_REPORT);
    }
    else
    {

    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_RcvUpPeriodicalReportTimer
 Description     : 用户面周期性定时器超时
 Input           : enPosTechType 用户面请求定位技术类型
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lifuxin      2015-11-24  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LPP_RcvUpPeriodicalReportTimer
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTransIndx,
    VOS_UINT8                           ucUpReqTechType,
    VOS_VOID                           *pRcvMsg
)
{
    VOS_UINT8                               ucPeriodReportNum   = 0;
    NAS_LPP_UP_REPORT_CRITERIA_STRU        *pstReportCriteria   = NAS_LPP_NULL_PTR;
    NAS_LPP_UP_ECID_INFO_STRU              *pstLppUpEcidInfo    = NAS_LPP_NULL_PTR;
    NAS_LPP_UP_OTDOA_INFO_STRU             *pstLppUpOtdoaInfo   = NAS_LPP_NULL_PTR;
    NAS_LPP_UP_MULTI_POS_TECH_INFO_STRU    *pstLppMultiPosTech  = NAS_LPP_NULL_PTR;

    NAS_LPP_INFO_LOG("NAS_LPP_RcvUpPeriodicalReportTimer");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvUpPeriodicalReportTimer_ENUM, LNAS_LPP_Func_Enter);
    pstLppUpOtdoaInfo   = NAS_LPP_GetLppUpOtdoaCtx();
    pstLppUpEcidInfo    = NAS_LPP_GetLppUpEcidCtx();
    pstLppMultiPosTech  = NAS_LPP_GetLppUpMultiPosTechCtx();

    switch (ucUpReqTechType)
    {
        case NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID_AND_OTDOA:
            ucPeriodReportNum = pstLppMultiPosTech->stReportCriteria.u.stReportPeriod.ucReportAmount;
            pstReportCriteria = &pstLppMultiPosTech->stReportCriteria;
            break;

        case NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID:
            ucPeriodReportNum = pstLppUpEcidInfo->stReportCriteria.u.stReportPeriod.ucReportAmount;
            pstReportCriteria = &pstLppUpEcidInfo->stReportCriteria;
            break;

        case NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA:
            ucPeriodReportNum = pstLppUpOtdoaInfo->stReportCriteria.u.stReportPeriod.ucReportAmount;
            pstReportCriteria = &pstLppUpOtdoaInfo->stReportCriteria;
            break;

        default:
            TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvUpPeriodicalReportTimer_ENUM, LNAS_LPP_Error_Tech_Enum);
            return;
    }

    if(NAS_LPP_INFINITY_CNT == ucPeriodReportNum)
    {
        /*无线次数上报场景*/
        /*给MTA上报测量值*/
        NAS_LPP_SndUpLppMtaPeriodReprotMeasInd(ucUpReqTechType);

        /*重启周期性定时器*/
        NAS_LPP_UpStartPeriodReportTimer(ucUpReqTechType);
    }
    else
    {
        /*上报未达到上报次数*/
        /*周期性上报次数加1*/
        pstReportCriteria->u.stReportPeriod.ucReportingAmount += 1;

        /*给MTA上报测量值*/
        NAS_LPP_SndUpLppMtaPeriodReprotMeasInd(ucUpReqTechType);

        /*重启周期性定时器*/
        NAS_LPP_UpStartPeriodReportTimer(ucUpReqTechType);

        if(pstReportCriteria->u.stReportPeriod.ucReportingAmount >= ucPeriodReportNum)
        {
            switch (ucUpReqTechType)
            {
                case NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID_AND_OTDOA:
                    /*达到最大上报次数，清空用户面实体信息*/
                    NAS_LPP_UPClrEntity();
                    break;

                case NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID:
                    NAS_LPP_UPClrEcidCtx();
                    break;

                default:
                    NAS_LPP_UPClrOtdoaCtx();
                    break;
            }
        }
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_TimerMsgDistr
 Description     :
 Input           :ucSessionTransIndx用法:  aucTransElementIdx[ucSessionTransIndx]
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-22  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_RcvUpMsgRetransTimer( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx , VOS_UINT8 ucUpReqTechType, VOS_VOID *pRcvMsg)
{
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU * pstSessionElement;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransEntity = NAS_LPP_NULL_PTR;
    VOS_UINT8                                ucTransIndx = 0;
    NAS_LPP_TRANS_ID_STRU                    stTransId;

    NAS_LPP_INFO_LOG("NAS_LPP_RcvUpMsgRetransTimer");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvUpMsgRetransTimer_ENUM, LNAS_LPP_Func_Enter);

    if ( (ucSessionIndx >= NAS_LPP_MAX_SESSION_COUNT)||(ucSessionTransIndx >= NAS_LPP_MAX_TRANS_COUNT) )
    {
        NAS_LPP_ERR_LOG2("ACK timter expire,wrong ucSessionIndx ,ucSessionTransIndx",ucSessionIndx ,ucSessionTransIndx);

        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvUpMsgRetransTimer_ENUM, LNAS_LPP_ValueOverflow );
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvUpMsgRetransTimer_ENUM, LNAS_LPP_SessionIndex,ucSessionIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvUpMsgRetransTimer_ENUM, LNAS_LPP_SessionTransIndex,ucSessionTransIndx);
        return;
    }

    pstSessionElement = NAS_LPP_GetSessionElementByIndex(ucSessionIndx);

    ucTransIndx     = NAS_LPP_GetTransIdIndex(ucSessionIndx,ucSessionTransIndx);
    pstTransEntity  = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if(NAS_LPP_NULL_PTR == pstTransEntity)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_RcvUpMsgRetransTimer: don't find transaction entity");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvUpMsgRetransTimer_ENUM,LNAS_LPP_GetTransElementByIndexFail );
        return;
    }

    /*如果发生次数达到最大的四次，结束transaction*/
    if ( pstTransEntity->ucRetranNum >= NAS_LPP_MAX_RETRANS_COUNT )
    {
        /* 这是一个比较大的错误，停止对应的session */
        NAS_LPP_ReleaseSessionEntityByIndex(ucSessionIndx);
    }
    else
    {
        /*继续下次重传*/
        pstTransEntity->ucRetranNum++;

        /*进入等待intra data conf的状态*/
        NAS_LPP_ChangeTransFsmState(ucSessionIndx,ucSessionTransIndx,pstTransEntity->enLppMainState,LPP_SS_WAIT_INTRA_DATA_CNF);

        /*发送消息*/
        stTransId = pstTransEntity->stTransId;
        NAS_LPP_ResendUplinkMsg(pstSessionElement->ulSessionId,&stTransId);
    }

}
/*****************************************************************************
 Function Name   : NAS_LPP_RcvWaitCnAssistDataTimer
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-27  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_RcvWaitCnAssistDataTimer( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx , VOS_UINT8 ucUpReqTechType, VOS_VOID *pRcvMsg)
{
    NAS_LPP_LOC_TECH_MAP_STRU          *pstTechMap;
    NAS_LPP_CONFIG_PARA_STRU           *pstCfgPara;
    NAS_LPP_LOC_TECH_RUNING_STRU        stPosSearchRslt = {0};
    VOS_UINT8 ucTransIndx;
    VOS_UINT8                           ucRslt;
    NAS_LPP_TRANS_ID_STRU               stTransId = {0};

    pstCfgPara = NAS_LPP_GetCfgPara();
    ucTransIndx = NAS_LPP_GetTransIdIndex(ucSessionIndx,ucSessionTransIndx);
    if (PS_NULL_UINT8 == ucTransIndx )
    {
        NAS_LPP_ERR_LOG2("wait cn assist data timer wrong index", ucSessionIndx, ucSessionTransIndx);

        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvWaitCnAssistDataTimer_ENUM, LNAS_LPP_GetTransIdIndexFail);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitCnAssistDataTimer_ENUM, LNAS_LPP_SessionIndex,ucSessionIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitCnAssistDataTimer_ENUM, LNAS_LPP_SessionTransIndex,ucSessionTransIndx);
        return;
    }

    /*结束assist data 的transaction*/
    NAS_LPP_ReleaseTransEntity(ucSessionIndx, ucSessionTransIndx);
    ucRslt = NAS_LPP_SndUpLppAbortMsg(ucSessionIndx,ucSessionTransIndx,ucTransIndx,LPP_COMMON_IES_ABORT_TARGET_DEVCIE_ABORT,VOS_FALSE,VOS_TRUE);
    if(NAS_LPP_SUCCESS != ucRslt)
    {
        stTransId.enInitiator =
            NAS_LPP_GetLppEntityCtx()->stTransEntityPool.astTransElementEntity[ucTransIndx].stTransId.enInitiator;
        stTransId.ucTransactionNumber =
            NAS_LPP_GetLppEntityCtx()->stTransEntityPool.astTransElementEntity[ucTransIndx].stTransId.ucTransactionNumber;
        NAS_LPP_ReleaseTransactionOrSession(ucSessionIndx,
                                            ucSessionTransIndx,
                                            &stTransId);
        return;
    }

    /* 如果本transaction的assist数据有修改otdoa的辅助数据，*/
    if (NAS_LPP_SLCT == pstCfgPara->bitOtdoaAssisChng)
    {
        /* 找到otdoa的transaction*/
        pstTechMap = NAS_LPP_SearchRunningPositionTech(NAS_LPP_POSITION_TECH_OTDOA);
        if ( NAS_LPP_NULL_PTR != pstTechMap)
        {
            NAS_LPP_SearchRunningPosTechByTransIndx(pstTechMap->ucTransIndx,&stPosSearchRslt);

            /*如果otdoa的transaction还有ecid/gnss的在跑， */
            if (stPosSearchRslt.ucNum > 1)
            {
                /*  如果otdoa的测量已经配置了LRRC，要停止LRRC的otdoa测量 */
                NAS_LPP_ReleasePosTechMeas(pstTechMap->ucSessionIndx, pstTechMap->ucSessionTranIndx,NAS_LPP_POSITION_TECH_OTDOA);
            }
            else /*如果otdoa的transaction没有其他技术(ecid/gnss)的在跑， */
            {
                /*结束本transaction*/
                NAS_LPP_ReleaseTransEntity(pstTechMap->ucSessionIndx, pstTechMap->ucSessionTranIndx);
            }
        }

        pstCfgPara->bitOtdoaAssisChng = NAS_LPP_NO_SLCT;
    }

#if 0
    /* 如果本transaction的assist数据有修改gnss的辅助数据 */
    if ()
    {
        /* 找到gnss的transaction */


        /* 如果gnss的transaction还有ecid/otdoa的在跑 */
        if ()
        {
            /*  如果gnss的测量已经配置了gps，要停止gps的gnss测量 */
            if  ()
            {

            }
        }
        else
        {
            /*结束本transaction*/
        }
    }
#endif

    /*结束otdoa 的transaction*/
    pstTechMap = NAS_LPP_SearchRunningPositionTech(NAS_LPP_POSITION_TECH_OTDOA);
    if (NAS_LPP_NULL_PTR != pstTechMap)
    {
        NAS_LPP_ReleaseTransEntity(pstTechMap->ucSessionIndx, pstTechMap->ucSessionTranIndx);
    }
    else
    {
    }

}

/*****************************************************************************
 Function Name   : NAS_LPP_RcvLocationInvalidTimer
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.wangensheng      2015-10-22  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_RcvLocationInvalidTimer( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx , VOS_UINT8 ucUpReqTechType, VOS_VOID *pRcvMsg)
{

    MTA_LPP_MEAS_REF_TIME_STRU         *pstMtaLppMeasRefTime    = NAS_LPP_NULL_PTR;
    LOC_COM_VELOCITY_STRU              *pstVelocityEstimate     = NAS_LPP_NULL_PTR;
    LOC_COM_COORDINATE_STRU            *pstLocationEstimate     = NAS_LPP_NULL_PTR;
    LPP_LRRC_INFO_FLAG_ENUM_UINT8       enGnssDataFlag          = LPP_LRRC_INFO_FLAG_INVALID;
    NAS_LPP_SERVING_CELL_STRU          *pstServingCell          = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_RcvLocationInvalidTimer enter");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SndLppLrrcLocationInfo_ENUM, LNAS_LPP_Func_Enter);

    /* 每次给RRC发位置信息时清除小区改变标志位 */
    pstServingCell = NAS_LPP_GetServingCell();
    if ( NAS_LPP_SLCT == pstServingCell->bitCELLIDChng )
    {
        NAS_LPP_SndLppLrrcLocationInfo( pstMtaLppMeasRefTime,  pstVelocityEstimate,  pstLocationEstimate, enGnssDataFlag);
    }
    else
    {
        /* 重启 GNSS LOC INFO 定时器 */
        NAS_LPP_TimerStart(NAS_LPP_TIMER_INVAILD_PARA,
                           NAS_LPP_TIMER_INVAILD_PARA,
                           TI_NAS_LPP_LOCATION_INVALID);
    }
}
/*****************************************************************************
 Function Name   : NAS_LPP_RcvWaitLrrcMeasCnfTimer
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-27  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_RcvWaitLrrcMeasCnfTimer( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx , VOS_UINT8 ucUpReqTechType, VOS_VOID *pRcvMsg)
{
    NAS_LPP_LOC_TECH_RUNING_STRU stPosSearchRslt = {0};
    PS_BOOL_ENUM_UINT8 enGnssPosExist = PS_FALSE;
    VOS_UINT32 ulLoop;

    NAS_LPP_ERR_LOG2("LPP rcv LRRC meas cnf time expire!", ucSessionIndx, ucSessionTransIndx);

    TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvWaitLrrcMeasCnfTimer_ENUM, LNAS_LPP_Func_Enter);
    TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitLrrcMeasCnfTimer_ENUM, LNAS_LPP_SessionIndex,ucSessionIndx);
    TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitLrrcMeasCnfTimer_ENUM, LNAS_LPP_SessionTransIndex,ucSessionTransIndx);

    NAS_LPP_SearchRunningPosTechByIndx2(ucSessionIndx,ucSessionTransIndx,&stPosSearchRslt);

    for ( ulLoop = 0 ; ulLoop < stPosSearchRslt.ucNum; ulLoop++ )
    {
        if ( NAS_LPP_POSITION_TECH_GNSS == stPosSearchRslt.astLocTechMap[ulLoop].enPositionTech)
        {
            enGnssPosExist = PS_TRUE;
            break;
        }
    }

    /*如果本transaction存在gps的，不释放transaction*/
    if (PS_FALSE == enGnssPosExist)
    {
        NAS_LPP_ReleaseSessionEntityByIndex(ucSessionIndx);
    }
    else
    {
        NAS_LPP_ERR_LOG("GNSS exist and not release trans");

        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvWaitLrrcMeasCnfTimer_ENUM, LNAS_LPP_GnssExistAndNotRelTrans);
    }
}

/*****************************************************************************
 Function Name   : NAS_LPP_RcvWaitEstCnfTimer
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-27  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_RcvWaitEstCnfTimer( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx, VOS_UINT8 ucUpReqTechType, VOS_VOID *pRcvMsg )
{
    if(NAS_LPP_GetTransLppMsgCnt() < NAS_LPP_GetLppTransAttepCnt())
    {
        /*建链次数没有达到最大，发起建链*/
        NAS_LPP_LppLmmEstReq();

        /*启动建链定时器*/
        NAS_LPP_TimerStart(NAS_LPP_TIMER_INVAILD_PARA,
                          NAS_LPP_TIMER_INVAILD_PARA,
                          TI_NAS_LPP_WAIT_EST_CNF);

        /*传输次数加1*/
        NAS_LPP_TransLppMsgAddCnt();
    }
    else
    {
        /*建链次数达到最大次数，通知Session释放所有的资源*/
        NAS_LPP_ConnFailHandle();
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_RcvWaitReEstTimer
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-27  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_RcvWaitReEstTimer( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx, VOS_UINT8 ucUpReqTechType, VOS_VOID *pRcvMsg )
{
    NAS_LPP_INFO_LOG("NAS_LPP_RcvWaitReEstTimer!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvWaitReEstTimer_ENUM, LNAS_LPP_Func_Enter);

    if(NAS_LPP_GetTransLppMsgCnt() < NAS_LPP_GetLppTransAttepCnt())
    {
        /*建链次数没有达到最大，发起建链*/
        NAS_LPP_LppLmmEstReq();

        /*启动建链定时器*/
        NAS_LPP_TimerStart(NAS_LPP_TIMER_INVAILD_PARA,
                          NAS_LPP_TIMER_INVAILD_PARA,
                          TI_NAS_LPP_WAIT_RE_EST);

        /*传输次数加1*/
        NAS_LPP_TransLppMsgAddCnt();
    }
    else
    {
        /*建链次数达到最大次数，通知Session释放所有的资源*/
        NAS_LPP_ConnFailHandle();
    }

    return;
}
/*****************************************************************************
 Function Name   : NAS_LPP_RcvWaitResponseTimer
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-27  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_RcvWaitResponseTimer( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx , VOS_UINT8 ucUpReqTechType, VOS_VOID *pRcvMsg)
{
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU     *pstSessionEntity = NAS_LPP_NULL_PTR;
    VOS_UINT8                                ucTransIndx           = 0;

    NAS_LPP_INFO_LOG("NAS_LPP_RcvWaitResponseTimer!!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvWaitResponseTimer_ENUM, LNAS_LPP_Func_Enter);

    pstSessionEntity = NAS_LPP_GetSessionEntity(ucSessionIndx);
    if(NAS_LPP_NULL_PTR == pstSessionEntity)
    {
        NAS_LPP_ERR_LOG2("NAS_LPP_RcvWaitResponseTimer: don't find SessionEntity!", ucSessionIndx, ucSessionTransIndx);

        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvWaitResponseTimer_ENUM, LNAS_LPP_GetSessionEntityFail);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitResponseTimer_ENUM, LNAS_LPP_SessionIndex,ucSessionIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitResponseTimer_ENUM, LNAS_LPP_SessionTransIndex,ucSessionTransIndx);
        return;
    }
    ucTransIndx= NAS_LPP_GetTransIdIndex(ucSessionIndx,ucSessionTransIndx);
    if(PS_NULL_UINT8 == ucTransIndx)
    {
        NAS_LPP_ERR_LOG2("NAS_LPP_RcvWaitResponseTimer: don't find TransEntity!", ucSessionIndx, ucSessionTransIndx);

        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvWaitResponseTimer_ENUM, LNAS_LPP_GetTransIdIndexFail);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitResponseTimer_ENUM, LNAS_LPP_SessionIndex,ucSessionIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitResponseTimer_ENUM, LNAS_LPP_SessionTransIndex,ucSessionTransIndx);
        return;
    }

    /*end transaction为true*/
    NAS_LPP_SetEndTransFlg(ucSessionIndx,ucSessionTransIndx,PS_TRUE);

    /*上报位置信息*/
    NAS_LPP_SndProvideLocInfoAndChngState(ucSessionIndx,
                                          ucSessionTransIndx,
                                          ucTransIndx);

    /*这里不能结束本transaction，要等provide location info发送完成*/
}


/*****************************************************************************
 Function Name   : NAS_LPP_RcvWaitPeriodicalTimer
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-27  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_RcvWaitPeriodicalTimer( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx, VOS_UINT8 ucUpReqTechType, VOS_VOID *pRcvMsg )
{
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU     *pstSessionEntity = NAS_LPP_NULL_PTR;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransElementEntity = NAS_LPP_NULL_PTR;
    NAS_LPP_COMM_CONFIG_INFO_STRU           *pstLppCommCfgInfo = NAS_LPP_NULL_PTR;
    VOS_UINT8                                ucTransIndx           = 0;

    NAS_LPP_INFO_LOG("NAS_LPP_RcvWaitPeriodicalTimer!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvWaitPeriodicalTimer_ENUM, LNAS_LPP_Func_Enter);

    pstSessionEntity = NAS_LPP_GetSessionEntity(ucSessionIndx);
    if(NAS_LPP_NULL_PTR == pstSessionEntity)
    {
        NAS_LPP_ERR_LOG2(": don't find SessionEntity!", ucSessionIndx, ucSessionTransIndx);

        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvWaitPeriodicalTimer_ENUM, LNAS_LPP_GetSessionEntityFail);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitPeriodicalTimer_ENUM, LNAS_LPP_SessionIndex,ucSessionIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitPeriodicalTimer_ENUM, LNAS_LPP_SessionTransIndex, ucSessionTransIndx);
        return;
    }
    ucTransIndx= NAS_LPP_GetTransIdIndex(ucSessionIndx,ucSessionTransIndx);
    pstTransElementEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if(NAS_LPP_NULL_PTR == pstTransElementEntity)
    {
        NAS_LPP_ERR_LOG2("NAS_LPP_RcvWaitPeriodicalTimer: don't find TransEntity!", ucSessionIndx, ucSessionTransIndx);

        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvWaitPeriodicalTimer_ENUM, LNAS_LPP_GetTransElementByIndexFail);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitPeriodicalTimer_ENUM, LNAS_LPP_SessionIndex,ucSessionIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitPeriodicalTimer_ENUM, LNAS_LPP_SessionTransIndex, ucSessionTransIndx);
        return;
    }

    pstLppCommCfgInfo = NAS_LPP_GetCommCfgInfoElementByIndex(pstTransElementEntity->ucCommCfgIndex);
    if ( NAS_LPP_NULL_PTR == pstLppCommCfgInfo )
    {
        NAS_LPP_ERR_LOG1(": period don't find comm cfg! index",  pstTransElementEntity->ucCommCfgIndex);

        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvWaitPeriodicalTimer_ENUM, LNAS_LPP_GetCommCfgInfoElementByIndexFail);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitPeriodicalTimer_ENUM, LNAS_LPP_CommCfgIndex,pstTransElementEntity->ucCommCfgIndex);
        return;
    }

    if ( NAS_LPP_REPORT_LOCATION_TYPE_PERIOD != pstLppCommCfgInfo->stReportCriteria.enType)
    {
        NAS_LPP_ERR_LOG1(": period don't match comm cfg! index",  pstTransElementEntity->ucCommCfgIndex);

        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvWaitPeriodicalTimer_ENUM, LNAS_LPP_ReportCriteriaMatchFail);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitPeriodicalTimer_ENUM, LNAS_LPP_CommCfgIndex,pstTransElementEntity->ucCommCfgIndex);
        return;
    }

    /*上报次数加1*/
    pstLppCommCfgInfo->stReportCriteria.u.stReportPeriod.ucReportingAmount++;

    /*判断上报的次数是否达到最后一次: 如果是最后一次的LPP周期上报，end transaction为true，并结束本transaction*/
    if ( (PS_FALSE == NAS_LPP_IsReportInfinity(pstLppCommCfgInfo->stReportCriteria.u.stReportPeriod.ucReportAmount))
       &&( pstLppCommCfgInfo->stReportCriteria.u.stReportPeriod.ucReportingAmount >=
            pstLppCommCfgInfo->stReportCriteria.u.stReportPeriod.ucReportAmount)  )
    {
        NAS_LPP_INFO_LOG("NAS_LPP_RcvWaitPeriodicalTimer: Up Max Report Count!");
        TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvWaitPeriodicalTimer_ENUM, LNAS_LPP_PeriodReportUpToMaxNum);

        /*end transaction为true*/
        NAS_LPP_SetEndTransFlg(ucSessionIndx,ucSessionTransIndx,PS_TRUE);

        /*上报位置信息*/
        NAS_LPP_SndProvideLocInfoAndChngState(ucSessionIndx,
                                                  ucSessionTransIndx,
                                                  ucTransIndx);

        /*这里不能结束本transaction，要等provide location info发送完成*/
    }
    else
    {
        NAS_LPP_INFO_LOG("NAS_LPP_RcvWaitPeriodicalTimer: Don't Up Max Report Count!");
        TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvWaitPeriodicalTimer_ENUM, LNAS_LPP_PeriodReportNotUpToMaxNum);

        /*重新启动周期上报定时器*/
        NAS_LPP_TimerStart(ucSessionIndx,ucSessionTransIndx,TI_NAS_LPP_PERIODICAL_REPORT);

        /*上报位置信息*/
        NAS_LPP_SndProvideLocInfoAndChngState(ucSessionIndx,
                                                  ucSessionTransIndx,
                                                  ucTransIndx);
    }

}
/*****************************************************************************
 Function Name   : NAS_LPP_RcvWaitReportDurationTimer
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-27  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_RcvWaitReportDurationTimer( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx , VOS_UINT8 ucUpReqTechType, VOS_VOID *pRcvMsg)
{
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU     *pstSessionEntity = NAS_LPP_NULL_PTR;
    VOS_UINT8                                ucTransIndx      = 0;

    NAS_LPP_INFO_LOG("NAS_LPP_RcvWaitReportDurationTimer!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvWaitReportDurationTimer_ENUM, LNAS_LPP_Func_Enter);

    pstSessionEntity = NAS_LPP_GetSessionEntity(ucSessionIndx);
    if(NAS_LPP_NULL_PTR == pstSessionEntity)
    {
        NAS_LPP_ERR_LOG2("DurationTimer: don't find SessionEntity!", ucSessionIndx, ucSessionTransIndx);

        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvWaitReportDurationTimer_ENUM, LNAS_LPP_GetSessionEntityFail);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitReportDurationTimer_ENUM, LNAS_LPP_SessionIndex,ucSessionIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitReportDurationTimer_ENUM, LNAS_LPP_SessionTransIndex,ucSessionTransIndx);
        return;
    }

    ucTransIndx= NAS_LPP_GetTransIdIndex(ucSessionIndx,ucSessionTransIndx);
    if(PS_NULL_UINT8 == ucTransIndx)
    {
        NAS_LPP_ERR_LOG2("DurationTimer: don't find TransEntity!", ucSessionIndx, ucSessionTransIndx);

        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvWaitReportDurationTimer_ENUM, LNAS_LPP_GetTransIdIndexFail);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitReportDurationTimer_ENUM, LNAS_LPP_SessionIndex,ucSessionIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitReportDurationTimer_ENUM, LNAS_LPP_SessionTransIndex,ucSessionTransIndx);
        return;
    }

    /*结束本session*/
    /*NAS_LPP_ReleaseSessionEntityByIndex(ucSessionIndx);*/

    /*end transaction为true*/
    NAS_LPP_SetEndTransFlg(ucSessionIndx,ucSessionTransIndx,PS_TRUE);

    /*上报位置信息*/
    NAS_LPP_SndProvideLocInfoAndChngState(ucSessionIndx,
                                          ucSessionTransIndx,
                                          ucTransIndx);
}
/*****************************************************************************
 Function Name   : NAS_LPP_RcvWaitGnssCapCnfTimer
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.wangensheng      2015-10-22  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LPP_RcvWaitGnssCapCnfTimer( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx, VOS_UINT8 ucUpReqTechType, VOS_VOID *pRcvMsg )
{
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU     *pstSessionEntity   = NAS_LPP_NULL_PTR;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransElementEntity = NAS_LPP_NULL_PTR;
    VOS_UINT8                                ucTransIndx        = 0;
    NAS_LPP_MSG_HEAD_STRU                    stLppMsgHead       = {0};
    VOS_UINT32                               ulSessionId        = 0;
    VOS_UINT32                               ucRslt             = 0;
    NAS_LPP_TRANS_ID_STRU                    stTransId         = {0};

    NAS_LPP_ERR_LOG("NAS_LPP_RcvWaitGnssCapCnfTimer:LPP rcv GNSS CAP data time expire!");
    TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvWaitGnssCapCnfTimer_ENUM, LNAS_WAIT_GNSS_CAP_TIME_OUT);

    if((NAS_LPP_TIMER_INVAILD_PARA == ucSessionIndx)
       && (NAS_LPP_TIMER_INVAILD_PARA == ucSessionTransIndx))
    {
        /*如果定时器超时解出的sessionIndx以及ucSessionTransIndx是无效值，则说明是
          是开机初始请求GNSS能力的超时，对于此场景，不做任何事情*/
        NAS_LPP_ERR_LOG("NAS_LPP_RcvWaitGnssCapCnfTimer: Req GNSS Cap Timeout!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvWaitGnssCapCnfTimer_ENUM, LNAS_WAIT_GNSS_CAP_INIT_TIMEOUT);
        return;
    }

    pstSessionEntity = NAS_LPP_GetSessionEntity(ucSessionIndx);
    if(NAS_LPP_NULL_PTR == pstSessionEntity)
    {
        NAS_LPP_ERR_LOG2(": don't find SessionEntity!", ucSessionIndx, ucSessionTransIndx);

        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvWaitGnssCapCnfTimer_ENUM, LNAS_LPP_GetSessionEntityFail);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitGnssCapCnfTimer_ENUM, LNAS_LPP_SessionIndex,ucSessionIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitGnssCapCnfTimer_ENUM, LNAS_LPP_SessionTransIndex, ucSessionTransIndx);
        return;
    }

    ucTransIndx= NAS_LPP_GetTransIdIndex(ucSessionIndx,ucSessionTransIndx);
    if(NAS_LPP_MAX_TRANS_POOL_COUNT < ucTransIndx)
    {
        return;
    }
    pstTransElementEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if(NAS_LPP_NULL_PTR == pstTransElementEntity)
    {
        NAS_LPP_ERR_LOG2("NAS_LPP_RcvWaitGnssCapCnfTimer: don't find TransEntity!", ucSessionIndx, ucSessionTransIndx);

        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvWaitGnssCapCnfTimer_ENUM, LNAS_LPP_GetTransElementByIndexFail);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitGnssCapCnfTimer_ENUM, LNAS_LPP_SessionIndex,ucSessionIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitGnssCapCnfTimer_ENUM, LNAS_LPP_SessionTransIndex, ucSessionTransIndx);
        return;
    }

    stLppMsgHead.stTransactionId.enInitiator = pstTransElementEntity->stTransId.enInitiator;
    stLppMsgHead.stTransactionId.ucTransactionNumber = pstTransElementEntity->stTransId.ucTransactionNumber;
    ulSessionId = pstSessionEntity->ulSessionId;

    /*回复ProvideCapbility消息*/
    ucRslt = NAS_LPP_SndUplinkProvideCapbilityMsg(&stLppMsgHead, ulSessionId,ucTransIndx);
    if(NAS_LPP_SUCCESS != ucRslt)
    {
        stTransId.enInitiator = stLppMsgHead.stTransactionId.enInitiator;
        stTransId.ucTransactionNumber = stLppMsgHead.stTransactionId.ucTransactionNumber;
        NAS_LPP_ReleaseTransactionOrSession(ucSessionIndx,
                                            ucSessionTransIndx,
                                            &stTransId);
        return;
    }

    /*表示当前transaction如果收到网络侧的ACK之后，就可以结束了*/
    pstTransElementEntity->ucTransEndFlag   = PS_TRUE;

    /*记录当前发送的空口消息，用于收到网络侧的消息之后决定转到什么状态*/
    pstTransElementEntity->enLastUpMsgId    = NAS_LPP_AIR_MSG_PROVIDE_CAP;

    /*转状态,转到能力交互，子状态等内部的data cnf，也就是确认把空口消息发送到了基站, 同时启动等待相应的定时器*/
    NAS_LPP_ChangeTransFsmState(ucSessionIndx,
                                ucSessionTransIndx,
                                LPP_MS_CAPABILITY,
                                LPP_SS_WAIT_INTRA_DATA_CNF);

    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_RcvWaitIntraDataCnfTimerExpire
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-22  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_RcvIntraDataCnfTimerExpire( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx , VOS_UINT8 ucUpReqTechType, VOS_VOID *pRcvMsg)
{
    NAS_LPP_ERR_LOG2("LPP rcv intra data time expire!", ucSessionIndx, ucSessionTransIndx);
    TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvIntraDataCnfTimerExpire_ENUM, LNAS_LPP_SessionIndex, ucSessionIndx);
    TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvIntraDataCnfTimerExpire_ENUM, LNAS_LPP_SessionTransIndex, ucSessionTransIndx);

    /* 这是一个比较大的错误，停止所有的session */
    NAS_LPP_ReleaseAllSession();
}

/*****************************************************************************
 Function Name   : NAS_LPP_GetPosReqTypeByEntimerType
 Description     : 从定时器超时中解析出定位技术的请求类型
                   index
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.lifuxin      2015-11-27  Draft Enact
*****************************************************************************/
VOS_UINT8  NAS_LPP_GetPosReqTypeByEntimerType
(
    VOS_UINT32                              ulPara,
    NAS_LPP_TIMER_PARA_ENUM_UINT8           enTimerType
)
{
    switch(enTimerType)
    {
        case TI_NAS_LPP_UP_WAIT_CN_ASSIST_DATA:
        case TI_NAS_LPP_UP_WAIT_LRRC_OTDOA_MEAS_CNF:
            return NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA;

        case TI_NAS_LPP_UP_WAIT_LRRC_ECID_MEAS_CNF:
            return NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID;

        case TI_NAS_LPP_UP_RESPONSE_TIMER:
        case TI_NAS_LPP_UP_PERIODICAL_REPORT:
        case TI_NAS_LPP_UP_REPORT_DURATION:
            if(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID == ulPara)
            {
                return NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID;
            }
            else if(NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA == ulPara)
            {
                return NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA;
            }
			else
			{
				return NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID_AND_OTDOA;
			}

        default:
            break;
    }

    return NAS_LPP_UP_POS_REQ_TECH_TYPE_BUTT;
}

/*****************************************************************************
 Function Name   : NAS_LPP_ParsIndxFromTimePara
 Description     : 从定时器的parameter参数分解出session index和transaction
                   index
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-22  Draft Enact
*****************************************************************************/
VOS_UINT8  NAS_LPP_ParsIndxFromTimePara
(
    VOS_UINT32                              ulPara,
    VOS_UINT8                              *pucSessionIndx,
    VOS_UINT8                              *pucSessionTransIndx,
    NAS_LPP_TIMER_PARA_ENUM_UINT8           enTimerType
)
{
    VOS_UINT32 ulTmp;
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8     enPosReqType = NAS_LPP_UP_POS_REQ_TECH_TYPE_BUTT;

    if((enTimerType >= TI_NAS_LPP_PTC_TIMER_MAX_NUM )
       || ((enTimerType >=TI_NAS_LPP_UP_STATE_TIMER_START_NUM)
       &&(enTimerType < TI_NAS_LPP_STATE_TIMER_MAX_NUM)))
    {
        /*用户面定时器*/
        enPosReqType =  NAS_LPP_GetPosReqTypeByEntimerType(ulPara, enTimerType);
    }
    else
    {
        /*信令面定时器*/
        ulTmp = ulPara & 0xFF;

        *pucSessionIndx  = (VOS_UINT8)ulTmp;

        ulTmp = (ulPara>>16)&0xFF;
        *pucSessionTransIndx = (VOS_UINT8)ulTmp;
    }

    return enPosReqType;
}


/*****************************************************************************
 Function Name  : NAS_LPP_TimerMsgDistr()
 Description    : LPP模块TIMER消息分发函数
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
 1. xiaojun 2015-7-7 新开发
*****************************************************************************/
VOS_VOID NAS_LPP_TimerMsgDistr(VOS_VOID *pRcvMsg )
{
    NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimerType     = TI_NAS_LPP_TIMER_PARA_BUTT;
    NAS_LPP_TIMER_PROC_FUNC             pfTimerFun      = NAS_LPP_NULL_PTR;
    VOS_UINT8                           ucSessionIndx   = PS_NULL_UINT8;
    VOS_UINT8                           ucSessionTransIndx = PS_NULL_UINT8;
    VOS_UINT32                          ulPara          = 0;
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8     enPosTechType = NAS_LPP_UP_POS_REQ_TECH_TYPE_NULL;

    NAS_LPP_NORM_LOG("NAS_LPP_TimerMsgDistr is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_TimerMsgDistr_ENUM, LNAS_LPP_Func_Enter);

    enTimerType = (NAS_LPP_TIMER_PARA_ENUM_UINT8)PS_GET_REL_TIMER_NAME(pRcvMsg);
    ulPara = PS_GET_REL_TIMER_PARA(pRcvMsg);

    enPosTechType = NAS_LPP_ParsIndxFromTimePara(ulPara,
                                                 &ucSessionIndx,
                                                 &ucSessionTransIndx,
                                                 enTimerType);

    NAS_LPP_OmTimerExpireInd(ucSessionIndx,ucSessionTransIndx,enTimerType);

    pfTimerFun = NAS_LPP_GetTimerProcFun(enTimerType);
    if ( NAS_LPP_NULL_PTR != pfTimerFun )
    {
        pfTimerFun(ucSessionIndx, ucSessionTransIndx, enPosTechType, pRcvMsg);
    }
}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
