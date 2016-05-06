/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasLcsOm.c
    Description : LCS的可谓可测
    History     :
            1.lihong  00150010       2015-09-28  Draft Enact
******************************************************************************/



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include    "NasLcsOm.h"
#include    "NasLcsPublic.h"
#include    "PsLogdef.h"
#include    "NasFileId.h"
#include    "TafLcsInterface.h"
#include    "LcsMmInterface.h"
#include    "LcsLppInterface.h"
#include    "LmmLcsInterface.h"
#include    "NasLcsTimerMsgProc.h"
#include    "NasMmlLib.h"


#define    THIS_FILE_ID            PS_FILE_ID_NASLCSOM_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLCSOM_C


#if (FEATURE_LPP == FEATURE_ON)


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

VOS_CHAR                                g_acLcsPrintBuf[NAS_COMM_PRINT_BUFF_LEN] = "";


/* EMM-LCS 消息打印数组 */
NAS_COMM_PRINT_LIST_STRU g_astEmmLcsMsgIdArray[] =
{
    {   ID_LCS_LMM_EST_REQ               ,
            "MSG:  ID_LCS_LMM_EST_REQ                              ",
        VOS_NULL_PTR},
    {   ID_LMM_LCS_EST_CNF               ,
            "MSG:  ID_LMM_LCS_EST_CNF                              ",
        VOS_NULL_PTR},
    {   ID_LCS_LMM_DATA_REQ     ,
            "MSG:  ID_LCS_LMM_DATA_REQ                             ",
        VOS_NULL_PTR},
    {   ID_LMM_LCS_DATA_CNF            ,
            "MSG:  ID_LMM_LCS_DATA_CNF                             ",
        VOS_NULL_PTR},
    {   ID_LMM_LCS_DATA_IND              ,
            "MSG:  ID_LMM_LCS_DATA_IND                             ",
        VOS_NULL_PTR},
    {   ID_LMM_LCS_POS_CAP_INFO_IND              ,
            "MSG:  ID_LMM_LCS_POS_CAP_INFO_IND                     ",
        VOS_NULL_PTR},
    {   ID_LMM_LCS_REL_IND              ,
            "MSG:  ID_LMM_LCS_REL_IND                              ",
        VOS_NULL_PTR}
};

/* MM-LCS 消息打印数组 */
NAS_COMM_PRINT_LIST_STRU g_astMmLcsMsgIdArray[] =
{
    {   ID_LCS_MM_EST_REQ               ,
            "MSG:  ID_LCS_MM_EST_REQ                               ",
        VOS_NULL_PTR},
    {   ID_MM_LCS_EST_CNF               ,
            "MSG:  ID_MM_LCS_EST_CNF                               ",
        VOS_NULL_PTR},
    {   ID_LCS_MM_DATA_REQ     ,
            "MSG:  ID_LCS_MM_DATA_REQ                              ",
        VOS_NULL_PTR},
    {   ID_MM_LCS_DATA_IND            ,
            "MSG:  ID_MM_LCS_DATA_IND                              ",
        VOS_NULL_PTR},
    {   ID_LCS_MM_REL_REQ              ,
            "MSG:  ID_LCS_MM_REL_REQ                               ",
        VOS_NULL_PTR},
    {   ID_MM_LCS_REL_IND              ,
            "MSG:  ID_MM_LCS_REL_IND                               ",
        VOS_NULL_PTR}
};

/* TAF-LCS 消息打印数组 */
NAS_COMM_PRINT_LIST_STRU g_astTafLcsMsgIdArray[] =
{
    {   ID_TAF_LCS_BEGIN_REQ               ,
            "MSG:  ID_TAF_LCS_BEGIN_REQ                            ",
        VOS_NULL_PTR},
    {   ID_TAF_LCS_END_REQ               ,
            "MSG:  ID_TAF_LCS_END_REQ                              ",
        VOS_NULL_PTR},
    {   ID_TAF_LCS_POWER_STATUS_NTF     ,
            "MSG:  ID_TAF_LCS_POWER_STATUS_NTF                     ",
        VOS_NULL_PTR},
    {   ID_LCS_TAF_BEGIN_IND            ,
            "MSG:  ID_LCS_TAF_BEGIN_IND                            ",
        VOS_NULL_PTR},
    {   ID_LCS_TAF_FACILITY_IND              ,
            "MSG:  ID_LCS_TAF_FACILITY_IND                         ",
        VOS_NULL_PTR},
    {   ID_LCS_TAF_END_IND              ,
            "MSG:  ID_LCS_TAF_END_IND                              ",
        VOS_NULL_PTR}
};

/* LPP-LCS 消息打印数组 */
NAS_COMM_PRINT_LIST_STRU g_astLppLcsMsgIdArray[] =
{
    {   ID_LCS_LPP_GNSS_ASSISTDATA_CNF               ,
            "MSG:  ID_LCS_LPP_GNSS_ASSISTDATA_CNF                  ",
        VOS_NULL_PTR},
    {   ID_LPP_LCS_GNSS_ASSISTDATA_REQ               ,
            "MSG:  ID_LPP_LCS_GNSS_ASSISTDATA_REQ                  ",
        VOS_NULL_PTR},
    {   ID_LCS_LPP_LOCATION_INFO_NTF     ,
            "MSG:  ID_LCS_LPP_LOCATION_INFO_NTF                    ",
        VOS_NULL_PTR}
};

/* 定时器超时 消息打印数组 */
NAS_COMM_PRINT_MSG_LIST_STRU g_astLcsTimerArray[] =
{
    {   TI_NAS_LCS_WAIT_NW_RSP_TIMER               ,
            "STATE TI:  TI_NAS_LCS_WAIT_NW_RSP_TIMER              "},
    {   TI_NAS_LCS_WAIT_UE_RSP_TIMER     ,
            "STATE TI:  TI_NAS_LCS_WAIT_UE_RSP_TIMER              "},
    {   TI_NAS_LCS_WATI_REEST_TIMER               ,
            "STATE TI:  TI_NAS_LCS_WATI_REEST_TIMER               "},
    {   TI_NAS_LCS_PERIOD_INTERVAL_TIMER               ,
            "STATE TI:  TI_NAS_LCS_PERIOD_INTERVAL_TIMER          "}
};


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 Function Name   : NAS_LCS_SndOmEntityStateInfo
 Description     : 发送实体状态OM信息
 Input           : ulEntityIndex----------------实体索引
                   enOldEntityState-------------上次实体状态
                   enNewEntityState-------------这次实体状态
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2015-10-14  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LCS_SndOmEntityStateInfo
(
    VOS_UINT32                          ulEntityIndex,
    NAS_LCS_ENTITY_STATE_ENUM_UINT8     enOldEntityState,
    NAS_LCS_ENTITY_STATE_ENUM_UINT8     enNewEntityState
)
{
    NAS_LCS_OM_ENTITY_STATE_INFO_STRU   stOmEntityState = {0};

    NAS_LCS_MEM_SET_S(  &stOmEntityState,
                        sizeof(NAS_LCS_OM_ENTITY_STATE_INFO_STRU),
                        0,
                        sizeof(NAS_LCS_OM_ENTITY_STATE_INFO_STRU));

    NAS_LCS_WRITE_OM_MSG_HEAD(  &stOmEntityState,
                                (sizeof(NAS_LCS_OM_ENTITY_STATE_INFO_STRU)-
                                NAS_LCS_LEN_VOS_MSG_HEADER));

    stOmEntityState.ulMsgId         = ID_NAS_LCS_OM_ENTITY_STATE_INFO;
    stOmEntityState.ulEntityIndex   = ulEntityIndex;
    stOmEntityState.enOldEntityState= enOldEntityState;
    stOmEntityState.enNewEntityState= enNewEntityState;

    (VOS_VOID)LTE_MsgHook( (VOS_VOID*)(&stOmEntityState) );

    NAS_LCS_INFO_LOG2("NAS_LCS_SndOmEntityStateInfo:enOldEntityState=, enNewEntityState=", enOldEntityState, enNewEntityState);
    NAS_LCS_INFO_LOG1("NAS_LCS_SndOmEntityStateInfo:ulEntityIndex=", ulEntityIndex);
}

/*****************************************************************************
 Function Name   : NAS_LCS_SndOmEntityConnStateInfo
 Description     : 发送实体时连接状态OM信息
 Input           : ulEntityIndex----------------实体索引
                   enOldConnState---------------上次连接状态
                   enNewConnState---------------这次连接状态
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2015-10-14  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LCS_SndOmEntityConnStateInfo
(
    VOS_UINT32                          ulEntityIndex,
    NAS_LCS_CONN_STATE_ENUM_UINT8       enOldConnState,
    NAS_LCS_CONN_STATE_ENUM_UINT8       enNewConnState
)
{
    NAS_LCS_OM_CONN_STATE_INFO_STRU     stOmConnState = {0};

    NAS_LCS_MEM_SET_S(  &stOmConnState,
                        sizeof(NAS_LCS_OM_CONN_STATE_INFO_STRU),
                        0,
                        sizeof(NAS_LCS_OM_CONN_STATE_INFO_STRU));

    NAS_LCS_WRITE_OM_MSG_HEAD(  &stOmConnState,
                                (sizeof(NAS_LCS_OM_CONN_STATE_INFO_STRU)-
                                NAS_LCS_LEN_VOS_MSG_HEADER));

    stOmConnState.ulMsgId           = ID_NAS_LCS_OM_CONN_STATE_INFO;
    stOmConnState.ulEntityIndex     = ulEntityIndex;
    stOmConnState.enOldConnState    = enOldConnState;
    stOmConnState.enNewConnState    = enNewConnState;

    (VOS_VOID)LTE_MsgHook( (VOS_VOID*)(&stOmConnState));

    NAS_LCS_INFO_LOG2("NAS_LCS_SndOmEntityConnStateInfo:enOldConnState=, enNewConnState=", enOldConnState, enNewConnState);
    NAS_LCS_INFO_LOG1("NAS_LCS_SndOmEntityConnStateInfo:ulEntityIndex=", ulEntityIndex);
}

/*****************************************************************************
 Function Name   : NAS_LCS_SndOmTimerStart
 Description     : 发送定时器启动OM信息
 Input           : ulEntityIndex----------------实体索引
                   enLcsTimerType---------------定时器类型
                   ulTimerLen-------------------定时器时长
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2015-10-14  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LCS_SndOmTimerStart
(
    VOS_UINT32                          ulEntityIndex,
    NAS_LCS_TIMER_ID_ENUM_UINT8         enLcsTimerType,
    VOS_UINT32                          ulTimerLen
)
{
    NAS_LCS_OM_TIMER_START_STRU         stOmTimerStart = {0};

    NAS_LCS_MEM_SET_S(  &stOmTimerStart,
                        sizeof(NAS_LCS_OM_TIMER_START_STRU),
                        0,
                        sizeof(NAS_LCS_OM_TIMER_START_STRU));

    NAS_LCS_WRITE_OM_MSG_HEAD(  &stOmTimerStart,
                                (sizeof(NAS_LCS_OM_TIMER_START_STRU)-
                                NAS_LCS_LEN_VOS_MSG_HEADER));

    stOmTimerStart.ulMsgId          = ID_NAS_LCS_OM_TIMER_START;
    stOmTimerStart.ulEntityIndex    = ulEntityIndex;
    stOmTimerStart.enLcsTimerType   = enLcsTimerType;
    if (TI_NAS_LCS_WATI_REEST_TIMER == enLcsTimerType)
    {
        stOmTimerStart.usPara       = NAS_LCS_GetEntityEstRetryTimers(ulEntityIndex);
    }
    else if (TI_NAS_LCS_PERIOD_INTERVAL_TIMER == enLcsTimerType)
    {
        stOmTimerStart.usPara       = NAS_LCS_GetEntityPediodRetryTimers(ulEntityIndex);
    }
    else
    {
        stOmTimerStart.usPara       = 0;
    }
    stOmTimerStart.ulTimerLen       = ulTimerLen;

    (VOS_VOID)LTE_MsgHook( (VOS_VOID*)(&stOmTimerStart));

    NAS_LCS_INFO_LOG2("NAS_LCS_SndOmTimerStart:enLcsTimerType=, ulEntityIndex=", enLcsTimerType, ulEntityIndex);
    NAS_LCS_INFO_LOG2("NAS_LCS_SndOmTimerStart:ulTimerLen=, usPara=", ulTimerLen, stOmTimerStart.usPara);
}

/*****************************************************************************
 Function Name   : NAS_LCS_SndOmTimerStop
 Description     : 发送定时器停止OM信息
 Input           : ulEntityIndex----------------实体索引
                   enLcsTimerType---------------定时器类型
                   ulRemainTime-----------------定时器剩余时长
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2015-10-14  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LCS_SndOmTimerStop
(
    VOS_UINT32                          ulEntityIndex,
    NAS_LCS_TIMER_ID_ENUM_UINT8         enLcsTimerType,
    VOS_UINT32                          ulRemainTime
)
{
    NAS_LCS_OM_TIMER_STOP_STRU          stOmTimerStop = {0};

    NAS_LCS_MEM_SET_S(  &stOmTimerStop,
                        sizeof(NAS_LCS_OM_TIMER_STOP_STRU),
                        0,
                        sizeof(NAS_LCS_OM_TIMER_STOP_STRU));

    NAS_LCS_WRITE_OM_MSG_HEAD(  &stOmTimerStop,
                                (sizeof(NAS_LCS_OM_TIMER_STOP_STRU)-
                                NAS_LCS_LEN_VOS_MSG_HEADER));

    stOmTimerStop.ulMsgId           = ID_NAS_LCS_OM_TIMER_STOP;
    stOmTimerStop.ulEntityIndex     = ulEntityIndex;
    stOmTimerStop.enLcsTimerType    = enLcsTimerType;
    stOmTimerStop.ulRemainTime      = ulRemainTime;

    (VOS_VOID)LTE_MsgHook( (VOS_VOID*)(&stOmTimerStop));

    NAS_LCS_INFO_LOG2("NAS_LCS_SndOmTimerStop:enLcsTimerType=, ulEntityIndex=", enLcsTimerType, ulEntityIndex);
    NAS_LCS_INFO_LOG1("NAS_LCS_SndOmTimerStop:ulRemainTime=", ulRemainTime);
}

/*****************************************************************************
 Function Name   : NAS_LCS_SndOmTimerExpire
 Description     : 发送定时器超时OM信息
 Input           : ulEntityIndex----------------实体索引
                   enLcsTimerType---------------定时器类型
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2015-10-14  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LCS_SndOmTimerExpire
(
    VOS_UINT32                          ulEntityIndex,
    NAS_LCS_TIMER_ID_ENUM_UINT8         enLcsTimerType
)
{
    NAS_LCS_OM_TIMER_EXPIRE_STRU        stOmTimerExpire= {0};

    NAS_LCS_MEM_SET_S(  &stOmTimerExpire,
                        sizeof(NAS_LCS_OM_TIMER_EXPIRE_STRU),
                        0,
                        sizeof(NAS_LCS_OM_TIMER_EXPIRE_STRU));

    NAS_LCS_WRITE_OM_MSG_HEAD(  &stOmTimerExpire,
                                (sizeof(NAS_LCS_OM_TIMER_EXPIRE_STRU)-
                                NAS_LCS_LEN_VOS_MSG_HEADER));

    stOmTimerExpire.ulMsgId         = ID_NAS_LCS_OM_TIMER_EXPIRE;
    stOmTimerExpire.ulEntityIndex   = ulEntityIndex;
    stOmTimerExpire.enLcsTimerType  = enLcsTimerType;
    if (TI_NAS_LCS_WATI_REEST_TIMER == enLcsTimerType)
    {
        stOmTimerExpire.usPara      = NAS_LCS_GetEntityEstRetryTimers(ulEntityIndex);
    }
    else if (TI_NAS_LCS_PERIOD_INTERVAL_TIMER == enLcsTimerType)
    {
        stOmTimerExpire.usPara      = NAS_LCS_GetEntityPediodRetryTimers(ulEntityIndex);
    }
    else
    {
        stOmTimerExpire.usPara      = 0;
    }

    (VOS_VOID)LTE_MsgHook( (VOS_VOID*)(&stOmTimerExpire));

    NAS_LCS_INFO_LOG2("NAS_LCS_SndOmTimerExpire:enLcsTimerType=, ulEntityIndex=", enLcsTimerType, ulEntityIndex);
    NAS_LCS_INFO_LOG1("NAS_LCS_SndOmTimerExpire:usPara=", stOmTimerExpire.usPara);
}

/*****************************************************************************
 Function Name   : NAS_LCS_SndOmNvCommonConfig
 Description     : 发送NV的基本配置OM信息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2015-10-14  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LCS_SndOmNvCommonConfig( VOS_VOID )
{
    NAS_LCS_OM_NV_COMMON_CONFIG_STRU    stOmNvCommonConfig = {0};

    NAS_LCS_MEM_SET_S(  &stOmNvCommonConfig,
                        sizeof(NAS_LCS_OM_NV_COMMON_CONFIG_STRU),
                        0,
                        sizeof(NAS_LCS_OM_NV_COMMON_CONFIG_STRU));

    NAS_LCS_WRITE_OM_MSG_HEAD(  &stOmNvCommonConfig,
                                (sizeof(NAS_LCS_OM_NV_COMMON_CONFIG_STRU)-
                                NAS_LCS_LEN_VOS_MSG_HEADER));

    stOmNvCommonConfig.ulMsgId  = ID_NAS_LCS_OM_NV_COMMON_CONFIG;

    NAS_LCS_MEM_CPY_S(  &stOmNvCommonConfig.stLcsNvCommConfig,
                        sizeof(NAS_LCS_COMM_NV_PARA_STRU),
                        NAS_LCS_GetCommNvPara(),
                        sizeof(NAS_LCS_COMM_NV_PARA_STRU));

    (VOS_VOID)LTE_MsgHook( (VOS_VOID*)(&stOmNvCommonConfig));

    NAS_LCS_INFO_LOG2("NAS_LCS_SndOmNvCommonConfig:bitOpPeriodicRptTimes=, usPeriodicRptTimes=", \
                        stOmNvCommonConfig.stLcsNvCommConfig.bitOpPeriodicRptTimes, \
                        stOmNvCommonConfig.stLcsNvCommConfig.usPeriodicRptTimes);
    NAS_LCS_INFO_LOG2("NAS_LCS_SndOmNvCommonConfig:ucMaxRetryTimes=, usRetryTimerLen=", \
                        stOmNvCommonConfig.stLcsNvCommConfig.ucMaxRetryTimes,\
                        stOmNvCommonConfig.stLcsNvCommConfig.usRetryTimerLen);
}

/*****************************************************************************
 Function Name   : NAS_LCS_SndOmDomainSelectInfo
 Description     : 发送域选择的OM信息
 Input           : enSelectedDomain--------------------选择的域
 Output          : None
 Return          : VOS_VOID
 History         :
    1.lihong00150010      2015-10-15  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LCS_SndOmDomainSelectInfo
(
    NAS_LCS_DOMAIN_TYPE_ENUM_UINT8      enSelectedDomain
)
{
    NAS_LCS_OM_DOMAIN_SELECT_INFO_STRU  stOmDomainSelcetInfo = {0};

    NAS_LCS_MEM_SET_S(  &stOmDomainSelcetInfo,
                        sizeof(NAS_LCS_OM_DOMAIN_SELECT_INFO_STRU),
                        0,
                        sizeof(NAS_LCS_OM_DOMAIN_SELECT_INFO_STRU));

    NAS_LCS_WRITE_OM_MSG_HEAD(  &stOmDomainSelcetInfo,
                                (sizeof(NAS_LCS_OM_DOMAIN_SELECT_INFO_STRU)-
                                NAS_LCS_LEN_VOS_MSG_HEADER));

    stOmDomainSelcetInfo.ulMsgId            = ID_NAS_LCS_OM_DOMAIN_SELECT_INFO;
    stOmDomainSelcetInfo.enSelectedDomain   = enSelectedDomain;
    if (NAS_LCS_GetLcsEntityNum() >= 1)
    {
        stOmDomainSelcetInfo.ucHasExistEntity = 1;
    }
    else
    {
        stOmDomainSelcetInfo.ucHasExistEntity = 0;
    }
    stOmDomainSelcetInfo.enCurrRat          = NAS_MML_GetCurrNetRatType();
    stOmDomainSelcetInfo.enUtranMode        = NAS_UTRANCTRL_GetCurrUtranMode();

    NAS_LCS_MEM_CPY_S(  &stOmDomainSelcetInfo.stUeNwCap,
                        sizeof(NAS_MML_UE_NETWORK_CAPABILITY_STRU),
                        NAS_MML_GetUeNetWorkCapability(),
                        sizeof(NAS_MML_UE_NETWORK_CAPABILITY_STRU));

    NAS_LCS_MEM_CPY_S(  &stOmDomainSelcetInfo.stNwLcsCap,
                        sizeof(NAS_LCS_NW_CAP_INFO_STRU),
                        NAS_LCS_GetNwLcsCap(),
                        sizeof(NAS_LCS_NW_CAP_INFO_STRU));

    NAS_MML_Fill_IE_ClassMark2(stOmDomainSelcetInfo.aucMsClassMark2);

    (VOS_VOID)LTE_MsgHook( (VOS_VOID*)(&stOmDomainSelcetInfo));
}

/*****************************************************************************
 Function Name   : NAS_LCS_SndOmDecodeDbgInfo
 Description     : 译码可维可测消息
 Input           : enMsgIe----------------IE
                   enCause----------------译码失败原因
                   ucValue----------------失败对应VALUE
                   ucPara-----------------保留参数
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leixiantiao      2015-9-29  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LCS_SndOmDecodeDbgInfo
(
    NAS_LCS_CN_MSG_IE_TYPE_ENUM_UINT32       enMsgIe,
    NAS_LCS_DECODE_FAIL_CAUSE_ENUM_UINT32    enCause,
    VOS_UINT32                               ulValue,
    VOS_UINT32                               ulPara
)
{
    NAS_LCS_OM_DECODE_DBG_INFO          stDebugInfo;

    NAS_LCS_MEM_SET_S(  &stDebugInfo,
                        sizeof(NAS_LCS_OM_DECODE_DBG_INFO),
                        0,
                        sizeof(NAS_LCS_OM_DECODE_DBG_INFO));

    NAS_LCS_WRITE_OM_MSG_HEAD(  &stDebugInfo,
                                (sizeof(NAS_LCS_OM_DECODE_DBG_INFO)-
                                NAS_LCS_LEN_VOS_MSG_HEADER));
    stDebugInfo.ulMsgId = ID_NAS_LCS_OM_DECODE_DBG_INFO;
    stDebugInfo.enMsgIe = enMsgIe;
    stDebugInfo.enCause = enCause;
    stDebugInfo.ulValue = ulValue;
    stDebugInfo.ulPara  = ulPara;

    (VOS_VOID)LTE_MsgHook( (VOS_VOID*)&stDebugInfo);
}

/*****************************************************************************
 Function Name   : NAS_LCS_SndOmEntityInfo
 Description     : 发送实体的OM信息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2015-10-16  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LCS_SndOmEntityInfo( VOS_VOID )
{
    NAS_LCS_OM_ENITY_INFO_STRU          stOmEntityInfo  = {0};
    NAS_LCS_PUB_INFO_STRU              *pstLcsInfo      = NAS_LCS_NULL_PTR;

    NAS_LCS_MEM_SET_S(  &stOmEntityInfo,
                        sizeof(NAS_LCS_OM_ENITY_INFO_STRU),
                        0,
                        sizeof(NAS_LCS_OM_ENITY_INFO_STRU));

    NAS_LCS_WRITE_OM_MSG_HEAD(  &stOmEntityInfo,
                                (sizeof(NAS_LCS_OM_ENITY_INFO_STRU)-
                                NAS_LCS_LEN_VOS_MSG_HEADER));

    stOmEntityInfo.ulMsgId  = ID_NAS_LCS_OM_ENITY_INFO;
    pstLcsInfo = NAS_LCS_GetLcsInfo();

    NAS_LCS_MEM_CPY_S(  &stOmEntityInfo.stNwLcsCap,
                        sizeof(NAS_LCS_NW_CAP_INFO_STRU),
                        &pstLcsInfo->stNwLcsCap,
                        sizeof(NAS_LCS_NW_CAP_INFO_STRU));

    NAS_LCS_MEM_CPY_S(  &stOmEntityInfo.stCommNvPara,
                        sizeof(NAS_LCS_COMM_NV_PARA_STRU),
                        &pstLcsInfo->stCommNvPara,
                        sizeof(NAS_LCS_COMM_NV_PARA_STRU));

    NAS_LCS_MEM_CPY_S(  stOmEntityInfo.astLcsEntity,
                        sizeof(NAS_LCS_ENTITY_INFO_STRU) * NAS_LCS_MAX_ENTITY_NUM,
                        pstLcsInfo->astLcsEntity,
                        sizeof(NAS_LCS_ENTITY_INFO_STRU) * NAS_LCS_MAX_ENTITY_NUM);

    NAS_LCS_MEM_CPY_S(  &stOmEntityInfo.stTafMsgRecord,
                        sizeof(NAS_LCS_TAF_MSG_RECORD_STRU),
                        &pstLcsInfo->stTafMsgRecord,
                        sizeof(NAS_LCS_TAF_MSG_RECORD_STRU));

    stOmEntityInfo.ucCurHandleId = pstLcsInfo->ucCurHandleId;
    stOmEntityInfo.ucCurInvokeId = pstLcsInfo->ucCurInvokeId;

    (VOS_VOID)LTE_MsgHook( (VOS_VOID*)(&stOmEntityInfo));
}

/*****************************************************************************
 Function Name   : NAS_LCS_SndAirMsgReportInd
 Description     : 发送空口消息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2015-10-15  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LCS_SndAirMsgReportInd
(
    const VOS_UINT8                    *pucData,
    VOS_UINT32                          ulLength,
    NAS_LCS_AIR_MSG_DIR_ENUM_UINT8      enMsgDir,
    OM_PS_AIR_MSG_ENUM_UINT8            enMsgId
)
{
#ifndef PS_ITT_PC_TEST
    DIAG_AIR_IND_STRU           stAirMsg    = {0};
    VOS_UINT8                  *pucTmpData  = VOS_NULL_PTR;

    /*分配空口消息空间*/
    pucTmpData = (VOS_UINT8*)NAS_LCS_MEM_ALLOC(ulLength);

    if(VOS_NULL_PTR == pucTmpData)
    {
        return;
    }

    NAS_LCS_MEM_CPY_S(pucTmpData, ulLength, pucData, ulLength);

    /*z00282933, 多模OM融合添加 - BEGIN*/
    /*设置空口消息方向*/
    if(NAS_LCS_AIR_MSG_DIR_ENUM_UP == enMsgDir)
    {
        stAirMsg.ulModule = LPS_OM_ID(WUEPS_PID_LCS, OS_MSG_UL);
        stAirMsg.ulPid = WUEPS_PID_LCS;
        stAirMsg.ulDirection = DIAG_SIDE_NET;
    }
    else
    {
        stAirMsg.ulModule = LPS_OM_ID(WUEPS_PID_LCS, OS_MSG_DL);
        stAirMsg.ulPid = WUEPS_PID_LCS;
        stAirMsg.ulDirection = DIAG_SIDE_UE;
    }
    stAirMsg.ulMsgId = (VOS_UINT32)(enMsgId+ PS_MSG_ID_AIR_BASE);
    stAirMsg.ulLength = ulLength;
    stAirMsg.pData = (void*)pucTmpData;

    /*上报空口消息*/
    if(ERR_MSP_SUCCESS != LDRV_DIAG_AIRMSGREPORT(&stAirMsg))
    {
        NAS_LCS_WARN_LOG("NAS_LCS_SndAirMsgReportInd: Send Msg Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_LCS_SndAirMsgReportInd_ENUM, LNAS_LCS_ReportAirMsgFail);
    }
    /*z00282933, 多模OM融合添加 - END*/

    /*释放空口消息空间*/
    NAS_LCS_MEM_FREE(pucTmpData);


#endif

    NAS_LCS_NORM_LOG("ESM->OMT: PS_OMT_AIR_MSG_REPORT_IND\r");
    TLPS_PRINT2LAYER_INFO(NAS_LCS_SndAirMsgReportInd_ENUM, 1);
}

/*****************************************************************************
 Function Name   : NAS_LCS_PrintTimer
 Description     : 打印收到定时器超时消息(文件内部调用函数)
 Input           : None
 Output          : None
 Return          : VOS_INT32

 History         :
    1.lihong 00150010      2015-10-17  Draft Enact

*****************************************************************************/
VOS_INT32  NAS_LCS_PrintTimer
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    VOS_UINT32                           ulTimerType
)

{
    VOS_UINT32                          ulLcsTimerNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* 获得消息表的长度 */
    ulLcsTimerNum = sizeof(g_astLcsTimerArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    /* 打印对应的消息 */
    if ( ulTimerType < ulLcsTimerNum )
    {
        NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         (VOS_CHAR *)(g_astLcsTimerArray[ulTimerType].aucPrintString),
                         &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                           usTotalLen,
                           "[ TICK : %ld ]",
                           PS_GET_TICK(),
                          &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        NAS_LCS_ERR_LOG1("NAS_LCS_PrintTimer, Invalid enMsgId: ",ulTimerType);
    }

    return (usTotalLen - usOffset);

}


/*****************************************************************************
 Function Name   : NAS_LCS_PrintTafMsg
 Description     : 打印收到TAF消息(文件内部调用函数)
 Input           : pcBuff   -- Formatted buffer
                   usOffset -- Offset
                   pstMsg   -- 消息指针
 Output          : None
 Return          : The number of bytes that have been stored in the output buffer pcBuff
                   If the input parameter is erroneous, the return value will be 0.

 History         :
    1.lihong 00150010      2015-10-17  Draft Enact

*****************************************************************************/
VOS_INT32   NAS_LCS_PrintTafMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulTafLcsMsgNum;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    ulTafLcsMsgNum = sizeof(g_astTafLcsMsgIdArray)/sizeof(NAS_COMM_PRINT_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulTafLcsMsgNum; ulLoop++)
    {
        if (pstMsg->ulMsgName == g_astTafLcsMsgIdArray[ulLoop].ulId)
        {
            break;
        }
    }

    if ( ulLoop < ulTafLcsMsgNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astTafLcsMsgIdArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                               usTotalLen,
                               "[ TICK : %ld ]",
                               PS_GET_TICK(),
                              &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        if (VOS_NULL_PTR != g_astTafLcsMsgIdArray[ulLoop].pfActionFun)
        {
            ilOutPutLen = g_astTafLcsMsgIdArray[ulLoop].pfActionFun(pcBuff,
                                                                   usTotalLen,
                                                                   pstMsg);
        }

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        NAS_LCS_ERR_LOG1("NAS_LCS_PrintTafMsg, Invalid enMsgId: ",
                           pstMsg->ulMsgName);
    }

    return (usTotalLen - usOffset);
}

/*****************************************************************************
 Function Name   : NAS_LCS_PrintLppMsg
 Description     : 打印收到LPP消息(文件内部调用函数)
 Input           : pcBuff   -- Formatted buffer
                   usOffset -- Offset
                   pstMsg   -- 消息指针
 Output          : None
 Return          : The number of bytes that have been stored in the output buffer pcBuff
                   If the input parameter is erroneous, the return value will be 0.

 History         :
    1.lihong 00150010      2015-10-17  Draft Enact

*****************************************************************************/
VOS_INT32   NAS_LCS_PrintLppMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulLppLcsMsgNum;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    ulLppLcsMsgNum = sizeof(g_astLppLcsMsgIdArray)/sizeof(NAS_COMM_PRINT_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulLppLcsMsgNum; ulLoop++)
    {
        if (pstMsg->ulMsgName == g_astLppLcsMsgIdArray[ulLoop].ulId)
        {
            break;
        }
    }

    if ( ulLoop < ulLppLcsMsgNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astLppLcsMsgIdArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                               usTotalLen,
                               "[ TICK : %ld ]",
                               PS_GET_TICK(),
                              &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        if (VOS_NULL_PTR != g_astLppLcsMsgIdArray[ulLoop].pfActionFun)
        {
            ilOutPutLen = g_astLppLcsMsgIdArray[ulLoop].pfActionFun(pcBuff,
                                                                   usTotalLen,
                                                                   pstMsg);
        }

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        NAS_LCS_ERR_LOG1("NAS_LCS_PrintLppMsg, Invalid enMsgId: ",
                           pstMsg->ulMsgName);
    }

    return (usTotalLen - usOffset);
}


/*****************************************************************************
 Function Name   : NAS_LCS_PrintMmMsg
 Description     : 打印收到MM消息(文件内部调用函数)
 Input           : pcBuff   -- Formatted buffer
                   usOffset -- Offset
                   pstMsg   -- 消息指针
 Output          : None
 Return          : The number of bytes that have been stored in the output buffer pcBuff
                   If the input parameter is erroneous, the return value will be 0.

 History         :
    1.lihong 00150010      2015-10-17  Draft Enact

*****************************************************************************/
VOS_INT32   NAS_LCS_PrintMmMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMmLcsMsgNum;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    ulMmLcsMsgNum = sizeof(g_astMmLcsMsgIdArray)/sizeof(NAS_COMM_PRINT_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulMmLcsMsgNum; ulLoop++)
    {
        if (pstMsg->ulMsgName == g_astMmLcsMsgIdArray[ulLoop].ulId)
        {
            break;
        }
    }

    if ( ulLoop < ulMmLcsMsgNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astMmLcsMsgIdArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                               usTotalLen,
                               "[ TICK : %ld ]",
                               PS_GET_TICK(),
                              &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        if (VOS_NULL_PTR != g_astMmLcsMsgIdArray[ulLoop].pfActionFun)
        {
            ilOutPutLen = g_astMmLcsMsgIdArray[ulLoop].pfActionFun(pcBuff,
                                                                   usTotalLen,
                                                                   pstMsg);
        }

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        NAS_LCS_ERR_LOG1("NAS_LCS_PrintMmMsg, Invalid enMsgId: ",
                           pstMsg->ulMsgName);
    }

    return (usTotalLen - usOffset);
}

/*****************************************************************************
 Function Name   : NAS_LCS_PrintEmmMsg
 Description     : 打印收到EMM消息(文件内部调用函数)
 Input           : pcBuff   -- Formatted buffer
                   usOffset -- Offset
                   pstMsg   -- 消息指针
 Output          : None
 Return          : The number of bytes that have been stored in the output buffer pcBuff
                   If the input parameter is erroneous, the return value will be 0.

 History         :
    1.lihong 00150010      2015-10-17  Draft Enact

*****************************************************************************/
VOS_INT32   NAS_LCS_PrintEmmMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulEmmLcsMsgNum;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    ulEmmLcsMsgNum = sizeof(g_astEmmLcsMsgIdArray)/sizeof(NAS_COMM_PRINT_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulEmmLcsMsgNum; ulLoop++)
    {
        if (pstMsg->ulMsgName == g_astEmmLcsMsgIdArray[ulLoop].ulId)
        {
            break;
        }
    }

    if ( ulLoop < ulEmmLcsMsgNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astEmmLcsMsgIdArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                               usTotalLen,
                               "[ TICK : %ld ]",
                               PS_GET_TICK(),
                              &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        if (VOS_NULL_PTR != g_astEmmLcsMsgIdArray[ulLoop].pfActionFun)
        {
            ilOutPutLen = g_astEmmLcsMsgIdArray[ulLoop].pfActionFun(pcBuff,
                                                                   usTotalLen,
                                                                   pstMsg);
        }

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        NAS_LCS_ERR_LOG1("NAS_LCS_PrintEmmMsg, Invalid enMsgId: ",
                           pstMsg->ulMsgName);
    }

    return (usTotalLen - usOffset);
}

/*****************************************************************************
 Function Name   : NAS_LCS_PrintLcsSendMsg
 Description     : 打印发送的消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010      2015-10-17  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LCS_PrintLcsSendMsg
(
    const PS_MSG_HEADER_STRU           *pstMsg,
    VOS_CHAR                           *pcBuff
)
{
#if (VOS_WIN32 == VOS_OS_VER)
    VOS_INT32                           ilOutPutLenHead     = 0;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen          = 0;

    NAS_COMM_nsprintf(  pcBuff,
                        usTotalLen,
                        "NAS LCS Send Message:",
                        &ilOutPutLen);

    if ( 0 == ilOutPutLen )
    {
        NAS_LCS_WARN_LOG("NAS_LCS_PrintLcsSendMsg, Print send msg header exception.");
        return ;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印各个PID的消息 */
    switch ( pstMsg->ulReceiverPid )
    {
        case PS_PID_MM :
            NAS_COMM_nsprintf(  pcBuff,
                                usTotalLen,
                                "LCS-->EMM\t",
                                &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_LCS_PrintEmmMsg(  pcBuff,
                                                usTotalLen,
                                                pstMsg);
            break;

        case WUEPS_PID_MM:
            NAS_COMM_nsprintf(  pcBuff,
                                usTotalLen,
                                "LCS-->MM\t",
                                &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_LCS_PrintMmMsg(   pcBuff,
                                                usTotalLen,
                                                pstMsg);
            break;

        case WUEPS_PID_TAF:
            NAS_COMM_nsprintf(  pcBuff,
                                usTotalLen,
                                "LCS-->TAF\t",
                                &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_LCS_PrintTafMsg(  pcBuff,
                                                usTotalLen,
                                                pstMsg);
            break;

        case PS_PID_LPP:
            NAS_COMM_nsprintf(  pcBuff,
                                usTotalLen,
                                "LCS-->LPP\t",
                                &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_LCS_PrintLppMsg(  pcBuff,
                                                usTotalLen,
                                                pstMsg);

            break;

        default:
            NAS_LCS_ERR_LOG2(   "NAS_LCS_PrintLcsSendMsg,Invalid Pid, MsgId: ",
                                pstMsg->ulReceiverPid,
                                pstMsg->ulMsgName);
            return ;
    }

    if ( 0 == ilOutPutLen )
    {
        NAS_LCS_ERR_LOG2(       "NAS_LCS_PrintLcsSendMsg, print return zero length. ReceiverPid, MsgId: ",
                                pstMsg->ulReceiverPid,
                                pstMsg->ulMsgName);
        return;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    NAS_COMM_Print(pcBuff,usTotalLen);
#endif
    return ;
}


/*****************************************************************************
 Function Name   : NAS_LCS_PrintLcsRevMsg
 Description     : 打印收到的消息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong 00150010      2015-10-17  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LCS_PrintLcsRevMsg
(
    const PS_MSG_HEADER_STRU           *pstMsg,
    VOS_CHAR                           *pcBuff
)
{
#if (VOS_WIN32 == VOS_OS_VER)
    VOS_INT32                           ilOutPutLenHead     = 0;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen          = 0;

    NAS_COMM_nsprintf(  pcBuff,
                        usTotalLen,
                        "NAS LCS Receive Message:",
                        &ilOutPutLen);

    if ( 0 == ilOutPutLen )
    {
        NAS_LCS_WARN_LOG("NAS_LCS_PrintLcsRevMsg, Print receive msg header exception.");
        return ;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印各个PID的消息 */
    switch ( pstMsg->ulSenderPid )
    {
        case PS_PID_MM:
            NAS_COMM_nsprintf(  pcBuff,
                                usTotalLen,
                                "EMM-->LCS\t",
                                &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_LCS_PrintEmmMsg(  pcBuff,
                                                usTotalLen,
                                                pstMsg);

            break;

        case WUEPS_PID_MM:
            NAS_COMM_nsprintf(  pcBuff,
                                usTotalLen,
                                "EMM-->LCS\t",
                                &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_LCS_PrintMmMsg(   pcBuff,
                                                usTotalLen,
                                                pstMsg);

            break;

        case WUEPS_PID_TAF:
            NAS_COMM_nsprintf(  pcBuff,
                                usTotalLen,
                                "TAF-->LCS\t",
                                &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_LCS_PrintTafMsg(  pcBuff,
                                                usTotalLen,
                                                pstMsg);
            break;

        case VOS_PID_TIMER  :
            NAS_COMM_nsprintf(  pcBuff,
                                usTotalLen,
                                "TIMER-->LCS\t",
                                &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_LCS_PrintTimer(   pcBuff,
                                                usTotalLen,
                                                ((REL_TIMER_MSG *)(VOS_VOID *)pstMsg)->ulPara);
            break;

        case PS_PID_LPP:
            NAS_COMM_nsprintf(  pcBuff,
                                usTotalLen,
                                "LPP-->LCS\t",
                                &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_LCS_PrintLppMsg(  pcBuff,
                                                usTotalLen,
                                                pstMsg);

            break;

        default:
            NAS_LCS_ERR_LOG2(   "NAS_LCS_PrintLcsRevMsg,Invalid Pid, MsgId: ",
                                pstMsg->ulSenderPid,
                                pstMsg->ulMsgName);

            return ;
    }

    if ( 0 == ilOutPutLen )
    {
        NAS_LCS_ERR_LOG2(   "NAS_LCS_PrintLcsRevMsg, print return zero length.SenderPid, MsgId: ",
                            pstMsg->ulSenderPid,
                            pstMsg->ulMsgName);
        return;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    NAS_COMM_Print(pcBuff, usTotalLen);
#endif

    return ;
}


#endif /*#if (FEATURE_LPP == FEATURE_ON)*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

