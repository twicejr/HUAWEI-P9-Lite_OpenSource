/******************************************************************************

@(#)Copyright(C)2008,Hisilicon Co. LTD.

******************************************************************************
File name   : NasLcsPublic.c
Description : LCS的公共处理
History     :
1.lihong  00150010       2015-09-28  Draft Enact
******************************************************************************/

/*****************************************************************************
1 Include HeadFile
*****************************************************************************/

#include    "PsCommonDef.h"
#include    "PsTypeDef.h"
#include    "NasCommPrint.h"
#include    "PsLogdef.h"
#include    "NasMmlCtx.h"
#include    "NasUtranCtrlInterface.h"
#include    "NasLcsOm.h"
#include    "LcsLppInterface.h"
#include    "NasLcsMain.h"
#include    "NasMmlLib.h"
#include    "NasLcsTafMsgProc.h"
#include    "NasLcsEncode.h"
#include    "NasLcsMmMsgProc.h"
#include    "NasLcsEmmMsgProc.h"
#include    "NasLcsLppMsgProc.h"
#include    "NasLcsPublic.h"
#include    "LNasNvInterface.h"
#include    "LNvCommon.h"
#include    "ImsaInterface.h"

#define    THIS_FILE_ID            PS_FILE_ID_NASLCSPUBLIC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLCSPUBLIC_C
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
NAS_LCS_PUB_INFO_STRU   g_stLcsInfo; /* LCS全局信息 */
NAS_LCS_PUB_INFO_STRU  *pg_stLcsInfo = &g_stLcsInfo;



/*****************************************************************************
3 Function
*****************************************************************************/

/*****************************************************************************
Function Name  : NAS_LCS_IsLteSupportEpcLcs
Discription    : 判断LTE是否支持EPC-LCS
Input          : None
Output         : None
Return         : VOS_UINT32
History:
1.lihong 00150010 2015-9-30 Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LCS_IsLteSupportEpcLcs( VOS_VOID )
{
    NAS_LCS_NW_CAP_INFO_STRU           *pstNwLcsCap     = NAS_LCS_NULL_PTR;
    NAS_MML_UE_NETWORK_CAPABILITY_STRU *pstUeNwCap      = NAS_LCS_NULL_PTR;

    pstNwLcsCap = NAS_LCS_GetNwLcsCap();
    pstUeNwCap  = NAS_MML_GetUeNetWorkCapability();

    /* UE NETWORK CAP里不包含LCS和LPP能力，则认为不支持 */
    if (pstUeNwCap->ucUeNetCapLen < NAS_LCS_UE_NW_CAP_LEN_INCLUDE_LCS)
    {
        return PS_FALSE;
    }

    /* 如果UE不支持LCS或LPP，则认为不支持,格式如下:
    ProSe-dd ProSe H.245-ASH ACC-CSFB LPP LCS 1xSRVCC NF */
    if ((0 == (pstUeNwCap->aucUeNetCap[NAS_LCS_LPP_CAP_INDEX_UE_NW_CAP] & 0x08))
        || (0 == (pstUeNwCap->aucUeNetCap[NAS_LCS_LPP_CAP_INDEX_UE_NW_CAP] & 0x04)))
    {
        return PS_FALSE;
    }

    /* 如果网侧支持EPC-LCS */
    if (NAS_LCS_NW_EPC_LCS_SUPPORT != pstNwLcsCap->enNwEpcLcs)
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}

/*****************************************************************************
Function Name  : NAS_LCS_IsMoLr
Discription    : 判断是否是MO-LR
Input          : None
Output         : None
Return         : VOS_UINT32
History:
1.lihong 00150010 2015-10-08 Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LCS_IsMoLr
(
    VOS_UINT32                          ulIndex
)
{
    if ((NAS_LCS_MO_LR_LPP_INDEX == ulIndex)
        || (NAS_LCS_MO_LR_TAF_INDEX == ulIndex))
    {
        return PS_TRUE;
    }

    return PS_FALSE;
}

/*****************************************************************************
Function Name  : NAS_LCS_IsClassmark2SupportLcs
Discription    : 判断CLASSMARK2是否支持CS-LCS
Input          : None
Output         : None
Return         : VOS_UINT32
History:
1.lihong 00150010 2015-10-13 Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LCS_IsClassmark2SupportLcs( VOS_VOID )
{
    VOS_UINT8                           aucMsClassMark2[NAS_MML_CLASSMARK2_LEN] = {0};

    NAS_MML_Fill_IE_ClassMark2(aucMsClassMark2);

    /* 如果CLASSMARK2的长度未包含LCS能力，则默认认为不支持 */
    if (aucMsClassMark2[0] < NAS_LCS_CLASSMARK2_LEN_INCLUDE_LCS)
    {
        return PS_FALSE;
    }

    /* 如果CLASSMARK2里支持不支持LCS，则认为不支持，格式如下:
    CM3 space LCSVACAP UCS2 SoLSA CMSP A5/3 A5/2 */
    if (0 == (aucMsClassMark2[3] & 0x20))
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}


/*****************************************************************************
Function Name  : NAS_LCS_IsLteSupportCsLcs
Discription    : 判断LTE是否支持CS-LCS
Input          : None
Output         : None
Return         : VOS_UINT32
History:
1.lihong 00150010 2015-9-30 Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LCS_IsLteSupportCsLcs( VOS_VOID )
{
    NAS_LCS_NW_CAP_INFO_STRU           *pstNwLcsCap     = NAS_LCS_NULL_PTR;

    /* 如果存在IMS业务，则不能选择CS-LCS */
    if (PS_TRUE == IMSA_IsExitImsService())
    {
        return PS_FALSE;
    }

    /* 如果CLASSMARK2不支持CS-LCS，则认为不支持 */
    if (PS_FALSE == NAS_LCS_IsClassmark2SupportLcs())
    {
        return PS_FALSE;
    }

    pstNwLcsCap = NAS_LCS_GetNwLcsCap();

    /* 如果网侧支持CS-LCS，则走CS-LCS */
    if ((NAS_LCS_NW_CS_LCS_NO_INFORMATION == pstNwLcsCap->enNwCsLcs)
        || (NAS_LCS_NW_CS_LCS_SUPPORT == pstNwLcsCap->enNwCsLcs))
    {
        return PS_TRUE;
    }

    return PS_FALSE;
}

/*****************************************************************************
Function Name  : NAS_LCS_SelectMolrDomain
Discription    : MO-LR域选择
Input          : None
Output         : None
Return         : NAS_LCS_DOMAIN_TYPE_ENUM_UINT8
History:
1.lihong 00150010 2015-9-29 Draft Enact
*****************************************************************************/
NAS_LCS_DOMAIN_TYPE_ENUM_UINT8 NAS_LCS_SelectMolrDomain( VOS_VOID )
{
    VOS_UINT32                          i               = 0;
    NAS_LCS_ENTITY_INFO_STRU           *pstLcsEntity    = NAS_LCS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat       = NAS_MML_NET_RAT_TYPE_BUTT;

    /* 当前是否存在其他LCS实体，如果存在，则选择现有LCS实体的域 */
    for (i = 0; i < NAS_LCS_MAX_ENTITY_NUM; i++)
    {
        pstLcsEntity = NAS_LCS_GetLcsEntity(i);
        if (NAS_LCS_ENTITY_NOT_USED == pstLcsEntity->enUsedFlag)
        {
            continue;
        }

        return pstLcsEntity->enCurLcsDomain;
    }

    enCurrRat = NAS_MML_GetCurrNetRatType();

    /* 当前接入技术不支持LCS */
    if ((NAS_MML_NET_RAT_TYPE_LTE < enCurrRat)
        || ((NAS_MML_NET_RAT_TYPE_WCDMA == enCurrRat) && (NAS_UTRANCTRL_UTRAN_MODE_FDD != NAS_UTRANCTRL_GetCurrUtranMode())))
    {
        return NAS_LCS_DOMAIN_TYPE_BUTT;
    }

    /* 初始域选择 */
    if (NAS_MML_NET_RAT_TYPE_LTE == enCurrRat)
    {
        /* 如果UE支持LCS和LPP，网侧支持EPC-LCS，则走EPC-LCS */
        if (PS_TRUE == NAS_LCS_IsLteSupportEpcLcs())
        {
            return NAS_LCS_DOMAIN_TYPE_EPC_LCS;
        }

        /* 如果UE支持LCS，网侧支持CS-LCS，则走CS-LCS */
        if (PS_TRUE == NAS_LCS_IsLteSupportCsLcs())
        {
            return NAS_LCS_DOMAIN_TYPE_CS_LCS;
        }

        return NAS_LCS_DOMAIN_TYPE_BUTT;
    }
    else
    {
        /* 如果UE支持LCS，则走CS-LCS */
        if (PS_TRUE == NAS_LCS_IsClassmark2SupportLcs())
        {
            return NAS_LCS_DOMAIN_TYPE_CS_LCS;
        }

        return NAS_LCS_DOMAIN_TYPE_BUTT;
    }
}

/*****************************************************************************
Function Name   : NAS_LCS_IsCurrRatSupportLcs
Description     : 判断当前接入技术是否支持LCS
Input           : NONE
Output          : None
Return          : VOS_UINT32

History         :
1.leixiantiao 00258641 2015-9-29 Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LCS_IsCurrRatSupportLcs(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat       = NAS_MML_NET_RAT_TYPE_BUTT;
    enCurrRat = NAS_MML_GetCurrNetRatType();

    /* TDS/WCDMA不支持LCS */
    if ((NAS_MML_NET_RAT_TYPE_LTE < enCurrRat)
        || ((NAS_MML_NET_RAT_TYPE_WCDMA == enCurrRat) && (NAS_UTRANCTRL_UTRAN_MODE_FDD != NAS_UTRANCTRL_GetCurrUtranMode())))
    {
        return PS_FALSE;
    }

    if (NAS_MML_NET_RAT_TYPE_LTE == enCurrRat)
    {
        /* 如果UE当前驻留在LTE上, 且支持LCS和LPP, 则认为UE当前接入技术支持LCS */
        if (PS_TRUE == NAS_LCS_IsLteSupportEpcLcs())
        {
            return PS_TRUE;
        }
    }
    else
    {
        /* 如果UE当前驻留在GU上, 且支持CS LCS, 则认为UE当前接入技术支持LCS */
        if (PS_TRUE == NAS_LCS_IsClassmark2SupportLcs())
        {
            return PS_TRUE;
        }
    }

    return PS_FALSE;
}

/*****************************************************************************
Function Name   : NAS_LCS_IsTimerNameValid
Description     : 判断定时器名是否合法
Input           : ulIndex---------------------实体索引
                  enLcsTimerType--------------定时器类型
Output          : None
Return          : VOS_UINT32

History         :
1.lihong 00150010 2015-9-29 Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LCS_IsTimerNameValid
(
    VOS_UINT32                          ulIndex,
    NAS_LCS_TIMER_ID_ENUM_UINT8         enLcsTimerType
)
{
    if (enLcsTimerType >= TI_NAS_LCS_TIMER_BUTT)
    {
        return PS_FALSE;
    }

    if (ulIndex < NAS_LCS_MAX_ENTITY_NUM)
    {
        return PS_TRUE;
    }

    return PS_FALSE;
}

/*****************************************************************************
Function Name   : NAS_LCS_GetTimer
Description     : 获取定时器
Input           : ulIndex---------------------实体索引
                  enLcsTimerType--------------定时器类型
Output          : None
Return          : NAS_LCS_TIMER_INFO_STRU*

History         :
1.lihong00150010      2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_TIMER_INFO_STRU*  NAS_LCS_GetTimer
(
    VOS_UINT32                          ulIndex,
    NAS_LCS_TIMER_ID_ENUM_UINT8         enLcsTimerType
)
{
    NAS_LCS_TIMER_INFO_STRU            *pstTimerInfo = NAS_LCS_NULL_PTR;

    /*根据定时器不同类型，获取定时器*/
    switch(enLcsTimerType)
    {
    case TI_NAS_LCS_WAIT_NW_RSP_TIMER:
    case TI_NAS_LCS_WAIT_UE_RSP_TIMER:
    case TI_NAS_LCS_PERIOD_INTERVAL_TIMER:
        pstTimerInfo = NAS_LCS_GetStateTimer(ulIndex);
        break;

    case TI_NAS_LCS_WATI_REEST_TIMER:
        pstTimerInfo = NAS_LCS_GetWaitResetTimer(ulIndex);
        break;

    default :
        break;
    }

    return pstTimerInfo;
}

/*****************************************************************************
Function Name   : NAS_LCS_GetTimerLen
Description     : 获取定时器时长
Input           : ulIndex---------------------实体索引
                  enLcsTimerType--------------定时器类型
Output          : None
Return          : VOS_UINT32

History         :
1.lihong00150010      2015-9-29  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LCS_GetTimerLen
(
    VOS_UINT32                          ulIndex,
    NAS_LCS_TIMER_ID_ENUM_UINT8         enLcsTimerType
)
{
    VOS_UINT32                          ulTimerLen      = 0;
    LCS_MOLR_PARA_STRU                 *pstMolrPara     = NAS_LCS_NULL_PTR;
    NAS_LCS_COMM_NV_PARA_STRU          *pstCommNvPara   = NAS_LCS_NULL_PTR;

    pstMolrPara     = NAS_LCS_GetTafMolrRecord();
    pstCommNvPara   = NAS_LCS_GetCommNvPara();

    /*根据定时器不同类型，定时器时长不同*/
    switch( enLcsTimerType )
    {
        case TI_NAS_LCS_WAIT_NW_RSP_TIMER:
            if (NAS_LCS_MO_LR_LPP_INDEX == ulIndex)
            {
                ulTimerLen = TI_NAS_LCS_LPP_WAIT_NW_RSP_TIMER_LEN;
            }
            else
            {
                ulTimerLen  = pstMolrPara->usTimeOut * 1000;
            }

            break;

        case TI_NAS_LCS_WAIT_UE_RSP_TIMER:
            ulTimerLen = TI_NAS_LCS_LPP_WAIT_USER_RSP_TIMER_LEN;
            break;

        case TI_NAS_LCS_WATI_REEST_TIMER:
            ulTimerLen = pstCommNvPara->usRetryTimerLen * 1000;
            break;

        case TI_NAS_LCS_PERIOD_INTERVAL_TIMER:
            ulTimerLen = pstMolrPara->usInterval * 1000;
            break;

        default :
            break;
    }

    return ulTimerLen;
}


/*****************************************************************************
Function Name  : NAS_LCS_StartTimer
Discription    : 启动定时器
Input          : ulIndex---------------------实体索引
                 enLcsTimerType--------------定时器类型
Output         : None
Return         : None
History:
1.lihong 00150010 2015-9-29 Draft Enact
*****************************************************************************/
VOS_VOID NAS_LCS_StartTimer
(
    VOS_UINT32                          ulIndex,
    NAS_LCS_TIMER_ID_ENUM_UINT8         enLcsTimerType
)
{
    VOS_UINT32                          ulTimerLen   = NAS_LCS_NULL;
    NAS_LCS_TIMER_INFO_STRU            *pstTimerInfo = NAS_LCS_NULL_PTR;

    /*对ulIndex合法性判断*/
    if (PS_FALSE == NAS_LCS_IsTimerNameValid(ulIndex, enLcsTimerType))
    {
        /*打印异常信息*/
        NAS_LCS_WARN_LOG("NAS_LCS_StartTimer: WARN: Input Para(ulIndex) err !");
        TLPS_PRINT2LAYER_WARNING1(NAS_LCS_StartTimer_ENUM, LNAS_PARAM_INVALID, 1);
        return;
    }

    /*根据消息对应的索引号和定时器类型,获取相关联的定时器*/
    pstTimerInfo = NAS_LCS_GetTimer(ulIndex, enLcsTimerType);
    if (pstTimerInfo == VOS_NULL_PTR)
    {
        /*打印异常信息*/
        NAS_LCS_ERR_LOG("NAS_LCS_StartTimer:ERROR: Get Timer failed.");
        TLPS_PRINT2LAYER_ERROR1(NAS_LCS_StartTimer_ENUM, LNAS_PARAM_INVALID, 2);
        return;
    }

    /*判断定时器是否打开，已打开则关闭*/
    if(VOS_NULL_PTR != pstTimerInfo->hTimer)
    {
        /*关闭失败，则报警返回*/
        if (VOS_OK != PS_STOP_REL_TIMER(&(pstTimerInfo->hTimer)))
        {
            /*打印异常信息*/
            NAS_LCS_WARN_LOG("NAS_LCS_StartTimer:WARN: stop reltimer error!");
            TLPS_PRINT2LAYER_WARNING(NAS_LCS_StartTimer_ENUM, LNAS_LCS_StopTimerFail);
            return;
        }

        /*打印异常信息*/
        NAS_LCS_ERR_LOG2("(TimerType) Timer not close!",pstTimerInfo->enLcsTimerType, ulIndex);
        TLPS_PRINT2LAYER_INFO2(NAS_LCS_StartTimer_ENUM, LNAS_LCS_StartTimerWhichIsRunning, pstTimerInfo->enLcsTimerType, ulIndex);
    }

    /*根据定时器不同类型，定时器信息不同*/
    ulTimerLen = NAS_LCS_GetTimerLen(ulIndex, enLcsTimerType);
    if (ulTimerLen == NAS_LCS_NULL)
    {
        /*打印异常信息*/
        NAS_LCS_ERR_LOG("NAS_LCS_StartTimer:ERROR: start unreasonable reltimer.");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_StartTimer_ENUM, LNAS_LCS_TimerLengthInvalid);
        return;
    }

    /*设定定时器NAME,enLcsTimerType设定定时器Para，打开失败则报警返回*/
    if (VOS_OK !=\
            PS_START_REL_TIMER(&(pstTimerInfo->hTimer),WUEPS_PID_LCS,\
                                ulTimerLen,ulIndex,\
                                (VOS_UINT32)enLcsTimerType,VOS_RELTIMER_NOLOOP))
    {
        /*打印异常信息*/
        NAS_LCS_WARN_LOG("NAS_LCS_StartTimer:WARN: start reltimer error!");
        TLPS_PRINT2LAYER_WARNING(NAS_LCS_StartTimer_ENUM, LNAS_LCS_StartTimerFail);
        return;
    }

    /*更新定时器开启信息和定时器类别*/
    pstTimerInfo->enLcsTimerType = enLcsTimerType;

    /*钩出当前的定时器信息 */
    NAS_LCS_SndOmTimerStart(ulIndex, enLcsTimerType, ulTimerLen);
}

/*****************************************************************************
Function Name  : NAS_LCS_StopTimer
Discription    : 停止某一承载定时器
Input          : ulIndex---------------------实体索引
                 enLcsTimerType--------------定时器类型
Output         : VOS_VOID
Return         : None
History:
1.lihong 00150010    2015-09-29  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LCS_StopTimer
(
    VOS_UINT32                          ulIndex,
    NAS_LCS_TIMER_ID_ENUM_UINT8         enLcsTimerType
)
{
    NAS_LCS_TIMER_INFO_STRU            *pstTimerInfo        = NAS_LCS_NULL_PTR;
    VOS_UINT32                          ulTimerRemainLen    = 0;

    /*对ulIndex合法性判断*/
    if (PS_FALSE == NAS_LCS_IsTimerNameValid(ulIndex, enLcsTimerType))
    {
        /*打印异常信息*/
        NAS_LCS_WARN_LOG("NAS_LCS_StopTimer: WARN: Input Para(ulIndex) err !");
        TLPS_PRINT2LAYER_WARNING1(NAS_LCS_StopTimer_ENUM, LNAS_PARAM_INVALID, 1);
        return;
    }

    /*根据消息对应的索引号和定时器类型,获取相关联的定时器*/
    pstTimerInfo = NAS_LCS_GetTimer(ulIndex, enLcsTimerType);
    if (pstTimerInfo == VOS_NULL_PTR)
    {
        /*打印异常信息*/
        NAS_LCS_ERR_LOG("NAS_LCS_StopTimer:ERROR:Get Timer failed.");
        TLPS_PRINT2LAYER_ERROR1(NAS_LCS_StopTimer_ENUM, LNAS_PARAM_INVALID, 2);
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
            NAS_LCS_WARN_LOG("NAS_LCS_StopTimer:WARN: stop reltimer error!");
            TLPS_PRINT2LAYER_WARNING(NAS_LCS_StopTimer_ENUM, LNAS_LCS_StopTimerFail);
            return;
        }

        /*更新定时器超时次数*/
        pstTimerInfo->ucExpireTimes = 0;


        /*钩出当前的定时器信息 */
        NAS_LCS_SndOmTimerStop(ulIndex, enLcsTimerType, ulTimerRemainLen);
    }
}

/*****************************************************************************
Function Name  : NAS_LCS_IsTimerRunning
Discription    : 判断某一定时器是否运行
Input          : ulIndex---------------------实体索引
                 enLcsTimerType--------------定时器类型
Output         : VOS_VOID
Return         : NAS_LCS_TIMER_RUN_STA_ENUM_UINT32
History:
1.lihong 00150010    2015-10-10  Draft Enact
*****************************************************************************/
NAS_LCS_TIMER_RUN_STA_ENUM_UINT32  NAS_LCS_IsTimerRunning
(
    VOS_UINT32                          ulIndex,
    NAS_LCS_TIMER_ID_ENUM_UINT8         enLcsTimerType
)
{
    NAS_LCS_TIMER_INFO_STRU            *pstTimerInfo = NAS_LCS_NULL_PTR;

    /*获取该协议定时器控制块地址*/
    pstTimerInfo = NAS_LCS_GetTimer(ulIndex, enLcsTimerType);
    if ( NAS_LCS_NULL_PTR == pstTimerInfo )
    {
        NAS_LCS_ERR_LOG("NAS_LCS_IsTimerRunning: pstPtlTimer NULL.");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_IsTimerRunning_ENUM, LNAS_NULL_PTR);
        return NAS_LCS_TIMER_INVALID;
    }

    /*检查该状态定时器是否在运行*/
    if ( NAS_LCS_NULL_PTR != pstTimerInfo->hTimer )
    {
        return NAS_LCS_TIMER_RUNNING;
    }
    else
    {
        return NAS_LCS_TIMER_STOPED;
    }
}

/*****************************************************************************
Function Name  : NAS_LCS_StopAllTimer
Discription    : 停止所有定时器
Input          : ulIndex---------------------实体索引
Output         : VOS_VOID
Return         : None
History:
1.lihong 00150010    2015-10-08  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LCS_StopAllTimer
(
    VOS_UINT32                          ulIndex
)
{
    VOS_UINT8                          i = 0;

    for (i = TI_NAS_LCS_WAIT_NW_RSP_TIMER; i < TI_NAS_LCS_TIMER_BUTT; i++)
    {
        NAS_LCS_StopTimer(ulIndex, i);
    }
}


/*****************************************************************************
Function Name  : NAS_LCS_CreateHandleId
Discription    : 创建handlle id
Input          : None
Output         : None
Return         : VOS_UINT8
History:
1.lihong 00150010 2015-9-29 Draft Enact
*****************************************************************************/
VOS_UINT8 NAS_LCS_CreateHandleId(VOS_VOID)
{
    /* 如果达到最大值，则从0开始 */
    if (NAS_LCS_MAX_HANDLE_ID == NAS_LCS_GetCurHandleId())
    {
        NAS_LCS_SetCurHandleId(0);
        return 0;
    }

    NAS_LCS_GetCurHandleId() = NAS_LCS_GetCurHandleId() + 1;
    return NAS_LCS_GetCurHandleId();
}

/*****************************************************************************
Function Name  : NAS_LCS_CreateInvokeId
Discription    : 创建invoke id
Input          : None
Output         : None
Return         : VOS_UINT8
History:
1.lihong 00150010 2015-10-16 Draft Enact
*****************************************************************************/
VOS_UINT8 NAS_LCS_CreateInvokeId( VOS_VOID )
{
    /* 如果达到最大值，则从0开始 */
    if (NAS_LCS_MAX_INVOKE_ID == NAS_LCS_GetCurInvokeId())
    {
        NAS_LCS_SetCurInvokeId(0);
        return 0;
    }

    NAS_LCS_GetCurInvokeId() = NAS_LCS_GetCurInvokeId() + 1;
    return NAS_LCS_GetCurInvokeId();
}

/*****************************************************************************
Function Name  : NAS_LCS_CreateMoTi
Discription    : 创建MO TI
此函数创建的TI值比上行空口中传输的MO TI值大8，
这样做的目的是为了适配MM，以区分网侧主动发送的下行消息的TI，
同时网侧回复REGISTER时，网侧会在上行空口的TI基础上加8，这样到时通过
收到网侧下发TI值进行查询时就不用转换了
Input          : None
Output         : None
Return         : VOS_UINT8
History:
1.lihong 00150010 2015-10-16 Draft Enact
*****************************************************************************/
VOS_UINT8 NAS_LCS_CreateMoTi
(
    VOS_UINT32                          ulIndex
)
{
    /* 先用14和13，而不用8和9，是为了尽量不和SS产生的TI重复 */
    if (NAS_LCS_MO_LR_TAF_INDEX == ulIndex)
    {
        return NAS_LCS_TAF_MO_LR_TI;
    }
    else
    {
        return NAS_LCS_LPP_MO_LR_TI;
    }
}

/*****************************************************************************
Function Name  : NAS_LCS_CreateLcsEntity
Discription    : 创建LCS实体
Input          : enStartSource---------------启动源
Output         : pulIndex--------------------实体索引
Return         : VOS_UINT32
History:
1.lihong 00150010 2015-9-29 Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LCS_CreateLcsEntity
(
    NAS_LCS_START_SOURCE_ENUM_UINT8     enStartSource,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          i = 0;
    NAS_LCS_ENTITY_INFO_STRU           *pstLcsEntity = NAS_LCS_NULL_PTR;

    /* 如果是MT-LR类型，则需要从下标为2~4的实体中查找是否存在空闲的实体 */
    if (NAS_LCS_START_SOURCE_NW == enStartSource)
    {
        for (i = NAS_LCS_MT_LR_ENTITY_INDEX_BEGIN; i <= NAS_LCS_MT_LR_ENTITY_INDEX_END; i++)
        {
            pstLcsEntity = NAS_LCS_GetLcsEntity(i);
            if (NAS_LCS_ENTITY_NOT_USED == pstLcsEntity->enUsedFlag)
            {
                break;
            }
        }

        if (i > NAS_LCS_MT_LR_ENTITY_INDEX_END)
        {
            return NAS_LCS_FAIL;
        }

        /* 初始化MT-LR实体信息 */
        *pulIndex                   = i;
        pstLcsEntity->enUsedFlag    = NAS_LCS_ENTITY_USED;
        pstLcsEntity->enConnState   = NAS_LCS_CONN_STATE_CONN;
        pstLcsEntity->enEntityState = NAS_LCS_ENTITY_STATE_WAIT_USER_RSP;
        pstLcsEntity->enStartSource = NAS_LCS_START_SOURCE_NW;
        pstLcsEntity->ucHandleId    = NAS_LCS_CreateHandleId();

        return NAS_LCS_SUCC;
    }

    /* 如果是LPP触发的MO-LR，则取下标为0的实体 */
    if (NAS_LCS_START_SOURCE_LPP == enStartSource)
    {
        pstLcsEntity = NAS_LCS_GetLcsEntity(NAS_LCS_MO_LR_LPP_INDEX);

        if (NAS_LCS_ENTITY_NOT_USED != pstLcsEntity->enUsedFlag)
        {
            return NAS_LCS_FAIL;
        }

        /* 初始化MO-LR实体信息 */
        *pulIndex                   = NAS_LCS_MO_LR_LPP_INDEX;
        pstLcsEntity->enUsedFlag    = NAS_LCS_ENTITY_USED;
        pstLcsEntity->enConnState   = NAS_LCS_CONN_STATE_IDLE;
        pstLcsEntity->enEntityState = NAS_LCS_ENTITY_STATE_WAIT_NW_RSP;
        pstLcsEntity->enStartSource = NAS_LCS_START_SOURCE_LPP;

        return NAS_LCS_SUCC;
    }

    /* 如果是TAF触发的MO-LR，则取下标为0的实体 */
    if (NAS_LCS_START_SOURCE_TAF == enStartSource)
    {
        pstLcsEntity = NAS_LCS_GetLcsEntity(NAS_LCS_MO_LR_TAF_INDEX);

        if (NAS_LCS_ENTITY_NOT_USED != pstLcsEntity->enUsedFlag)
        {
            return NAS_LCS_FAIL;
        }

        /* 初始化MO-LR实体信息 */
        *pulIndex                   = NAS_LCS_MO_LR_TAF_INDEX;
        pstLcsEntity->enUsedFlag    = NAS_LCS_ENTITY_USED;
        pstLcsEntity->enConnState   = NAS_LCS_CONN_STATE_IDLE;
        pstLcsEntity->enEntityState = NAS_LCS_ENTITY_STATE_WAIT_NW_RSP;
        pstLcsEntity->enStartSource = NAS_LCS_START_SOURCE_TAF;

        return NAS_LCS_SUCC;
    }

    return NAS_LCS_FAIL;
}

/*****************************************************************************
Function Name  : NAS_LCS_ClearSingleLcsEntity
Discription    : 释放单个LCS实体
Input          : ulIndex---------------索引
                 enCause---------------释放原因值
Output         : None
Return         : VOS_VOID
History:
1.lihong 00150010 2015-9-29 Draft Enact
*****************************************************************************/
VOS_VOID NAS_LCS_ClearSingleLcsEntity
(
    VOS_UINT32                          ulIndex,
    TAF_LCS_CAUSE_ENUM_UINT32           enCause
)
{
    NAS_LCS_ENTITY_INFO_STRU           *pstLcsEntity = NAS_LCS_NULL_PTR;

    /* 如果是LPP出发的MO-LR释放，不需要通知TAF */
    if (NAS_LCS_MO_LR_LPP_INDEX != ulIndex)
    {
        if (NAS_LCS_MO_LR_TAF_INDEX == ulIndex)
        {
            NAS_LCS_SndTafEndInd(TAF_LCS_LR_TYPE_MO, enCause, 0);
        }
        else
        {
            NAS_LCS_SndTafEndInd(TAF_LCS_LR_TYPE_MT, enCause, NAS_LCS_GetEntityHandleId(ulIndex));
        }
    }

    pstLcsEntity = NAS_LCS_GetLcsEntity(ulIndex);

    /* 停止所有定时器 */
    NAS_LCS_StopAllTimer(ulIndex);

    NAS_LCS_MEM_SET_S(  pstLcsEntity,
                        sizeof(NAS_LCS_ENTITY_INFO_STRU),
                        0,
                        sizeof(NAS_LCS_ENTITY_INFO_STRU));

    pstLcsEntity->enCurLcsDomain    = NAS_LCS_DOMAIN_TYPE_BUTT;
    pstLcsEntity->enStartSource     = NAS_LCS_START_SOURCE_BUTT;
    pstLcsEntity->enUsedFlag        = NAS_LCS_ENTITY_NOT_USED;
}

/*****************************************************************************
Function Name  : NAS_LCS_SndFacility
Discription    : 发送FACILITY给网侧
Input          : ulIndex-----------------实体索引
Output         : None
Return         : None
History:
1.lihong 00150010 2015-10-17 Draft Enact
*****************************************************************************/
VOS_VOID NAS_LCS_SndFacility
(
    VOS_UINT32                          ulIndex
)
{
    NAS_LCS_ENCODE_INFO_STRU            stEncodeInfo    = {0};
    NAS_LCS_ENCODE_BUFFER_STRU         *pstEncodeBuffer = NAS_LCS_NULL_PTR;

    NAS_LCS_MEM_SET_S(  &stEncodeInfo,
                        sizeof(NAS_LCS_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_LCS_ENCODE_INFO_STRU));

    stEncodeInfo.ucTi           = NAS_LCS_GetEntityTi(ulIndex) - NAS_LCS_TI_OFFSET;
    stEncodeInfo.enStartSource  = NAS_LCS_GetEntityStrartSource(ulIndex);
    stEncodeInfo.enOperType     = NAS_LCS_OPERATION_MO_LR;
    stEncodeInfo.bitOpInvokeId  = NAS_LCS_OP_TRUE;
    stEncodeInfo.ucInvokeId     = NAS_LCS_GetEntityInvokeId(ulIndex);

    pstEncodeBuffer             = NAS_LCS_GetEncodeBuffer();
    if (NAS_LCS_CAUSE_SUCCESS == NAS_LCS_EncodeFacility(    pstEncodeBuffer->aucBuffer,
                                                            &pstEncodeBuffer->ulBufferLen,
                                                            &stEncodeInfo))
    {
        NAS_LCS_SndAirMsgReportInd( pstEncodeBuffer->aucBuffer,
                                    pstEncodeBuffer->ulBufferLen,
                                    NAS_LCS_AIR_MSG_DIR_ENUM_UP,
                                    LCS_FACILITY);

        /* 根据所属于的域发给响应模块 */
        if (NAS_LCS_DOMAIN_TYPE_CS_LCS == NAS_LCS_GetEntityLcsDomain(ulIndex))
        {
            NAS_LCS_SndMmDataReq(   NAS_LCS_GetEntityTi(ulIndex),
                                    pstEncodeBuffer->ulBufferLen,
                                    pstEncodeBuffer->aucBuffer);
        }
        else
        {
            NAS_LCS_SndLmmDataReq(  NAS_LCS_GetEntityTi(ulIndex),
                                    pstEncodeBuffer->ulBufferLen,
                                    pstEncodeBuffer->aucBuffer);
        }
    }
    else
    {
        /* 释放LCS实体 */
        NAS_LCS_ClearLcsEntityAndNotify(ulIndex, TAF_LCS_CAUSE_OTHERS);
    }
}

/*****************************************************************************
Function Name  : NAS_LCS_SndMtlrRspReleaseComplte
Discription    : 通过RELEASE COMPLTE消息把MTLR用户回复带给网侧
Input          : ulIndex-----------------实体索引
               : enLocNtfRsp-------------用户回复MTLR结果
Output         : None
Return         : None
History:
1.leixiantiao 00258641 2015-10-24 Draft Enact
*****************************************************************************/
VOS_VOID NAS_LCS_SndMtlrRspReleaseComplte
(
    VOS_UINT32                          ulIndex,
    LCS_MTLRA_OP_ENUM_UINT8             enLocNtfRsp
)
{
    NAS_LCS_ENCODE_INFO_STRU            stEncodeInfo    = {0};
    NAS_LCS_ENCODE_BUFFER_STRU         *pstEncodeBuffer = NAS_LCS_NULL_PTR;

    NAS_LCS_MEM_SET_S(  &stEncodeInfo,
                        sizeof(NAS_LCS_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_LCS_ENCODE_INFO_STRU));

    /* 填写空口TI值 */
    stEncodeInfo.ucTi       = NAS_LCS_GetEntityTi(ulIndex) + NAS_LCS_TI_OFFSET;

    /* 填写MTLR回复结果 */
    if (LCS_MTLRA_OP_BUTT != enLocNtfRsp)
    {
        stEncodeInfo.bitLocNtfRsp = NAS_LCS_OP_TRUE;
        stEncodeInfo.enLocNtfRsp  = enLocNtfRsp;
    }

    /* 填写InvokeId */
    stEncodeInfo.bitOpInvokeId  = NAS_LCS_OP_TRUE;
    stEncodeInfo.ucInvokeId     = NAS_LCS_GetEntityInvokeId(ulIndex);

    stEncodeInfo.enOperType     = NAS_LCS_OPERATION_LOC_NOTIFICATION;

    pstEncodeBuffer             = NAS_LCS_GetEncodeBuffer();

    /* 编码RELEASE COMPLETE */
    if (NAS_LCS_CAUSE_SUCCESS == NAS_LCS_EncodeRelComplete( pstEncodeBuffer->aucBuffer,
                                                            &pstEncodeBuffer->ulBufferLen,
                                                            &stEncodeInfo))
    {
        NAS_LCS_SndAirMsgReportInd( pstEncodeBuffer->aucBuffer,
                                    pstEncodeBuffer->ulBufferLen,
                                    NAS_LCS_AIR_MSG_DIR_ENUM_UP,
                                    LCS_RELEASE_COMPLTE);

        /* 根据所属于的域发给响应模块 */
        if (NAS_LCS_DOMAIN_TYPE_CS_LCS == NAS_LCS_GetEntityLcsDomain(ulIndex))
        {
            NAS_LCS_SndMmDataReq(   NAS_LCS_GetEntityTi(ulIndex),
                                    pstEncodeBuffer->ulBufferLen,
                                    pstEncodeBuffer->aucBuffer);
        }
        else
        {
            NAS_LCS_SndLmmDataReq(  NAS_LCS_GetEntityTi(ulIndex),
                                    pstEncodeBuffer->ulBufferLen,
                                    pstEncodeBuffer->aucBuffer);
        }
    }
}

/*****************************************************************************
Function Name  : NAS_LCS_SndReleaseComplte
Discription    : 发送RELEASE COMPLTE给网侧
Input          : ulIndex-----------------实体索引
Output         : None
Return         : None
History:
1.lihong 00150010 2015-10-16 Draft Enact
*****************************************************************************/
VOS_VOID NAS_LCS_SndReleaseComplte
(
    VOS_UINT32                          ulIndex
)
{
    NAS_LCS_ENCODE_INFO_STRU            stEncodeInfo    = {0};
    NAS_LCS_ENCODE_BUFFER_STRU         *pstEncodeBuffer = NAS_LCS_NULL_PTR;

    NAS_LCS_MEM_SET_S(  &stEncodeInfo,
                        sizeof(NAS_LCS_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_LCS_ENCODE_INFO_STRU));

    /* 填写空口TI值 */
    if (PS_TRUE == NAS_LCS_IsMoLr(ulIndex))
    {
        stEncodeInfo.ucTi       = NAS_LCS_GetEntityTi(ulIndex) - NAS_LCS_TI_OFFSET;
    }
    else
    {
        stEncodeInfo.ucTi       = NAS_LCS_GetEntityTi(ulIndex) + NAS_LCS_TI_OFFSET;
    }

    /* 填写InvokeId */
    stEncodeInfo.bitOpInvokeId  = NAS_LCS_OP_TRUE;
    stEncodeInfo.ucInvokeId     = NAS_LCS_GetEntityInvokeId(ulIndex);

    pstEncodeBuffer             = NAS_LCS_GetEncodeBuffer();

    /* 编码RELEASE COMPLETE */
    if (NAS_LCS_CAUSE_SUCCESS == NAS_LCS_EncodeRelComplete( pstEncodeBuffer->aucBuffer,
                                                            &pstEncodeBuffer->ulBufferLen,
                                                            &stEncodeInfo))
    {
        NAS_LCS_SndAirMsgReportInd( pstEncodeBuffer->aucBuffer,
                                    pstEncodeBuffer->ulBufferLen,
                                    NAS_LCS_AIR_MSG_DIR_ENUM_UP,
                                    LCS_RELEASE_COMPLTE);

        /* 根据所属于的域发给响应模块 */
        if (NAS_LCS_DOMAIN_TYPE_CS_LCS == NAS_LCS_GetEntityLcsDomain(ulIndex))
        {
            NAS_LCS_SndMmDataReq(   NAS_LCS_GetEntityTi(ulIndex),
                                    pstEncodeBuffer->ulBufferLen,
                                    pstEncodeBuffer->aucBuffer);
        }
        else
        {
            NAS_LCS_SndLmmDataReq(  NAS_LCS_GetEntityTi(ulIndex),
                                    pstEncodeBuffer->ulBufferLen,
                                    pstEncodeBuffer->aucBuffer);
        }
    }
}

/*****************************************************************************
Function Name  : NAS_LCS_SndMtlrFailReleaseComplte
Discription    : 由于MT LR失败发送RELEASE COMPLTE给网侧
Input          : ucDlAirTi---------------下行空口TI
enLcsDomainType---------域
enCause-----------------原因值
Output         : None
Return         : None
History:
1.lihong 00150010 2015-10-13 Draft Enact
*****************************************************************************/
VOS_VOID NAS_LCS_SndMtlrFailReleaseComplte
(
    VOS_UINT8                           ucDlAirTi,
    VOS_UINT8                           ucInvokeId,
    NAS_LCS_DOMAIN_TYPE_ENUM_UINT8      enLcsDomainType,
    NAS_LCS_NW_CAUSE_ENUM_UINT32        enCause
)
{
    NAS_LCS_ENCODE_INFO_STRU            stEncodeInfo    = {0};
    NAS_LCS_ENCODE_BUFFER_STRU         *pstEncodeBuffer = NAS_LCS_NULL_PTR;

    NAS_LCS_MEM_SET_S(  &stEncodeInfo,
                        sizeof(NAS_LCS_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_LCS_ENCODE_INFO_STRU));

    /* 填写空口TI值 */
    stEncodeInfo.ucTi           = ucDlAirTi + NAS_LCS_TI_OFFSET;

    if (NAS_LCS_NW_CAUSE_BUTT != enCause)
    {
        stEncodeInfo.bitOpCause = NAS_LCS_OP_TRUE;
        stEncodeInfo.enCause    = enCause;
    }

    /* 填写InvokeId */
    stEncodeInfo.bitOpInvokeId  = NAS_LCS_OP_TRUE;
    stEncodeInfo.ucInvokeId     = ucInvokeId;

    pstEncodeBuffer             = NAS_LCS_GetEncodeBuffer();

    /* 编码RELEASE COMPLETE */
    if (NAS_LCS_CAUSE_SUCCESS == NAS_LCS_EncodeRelComplete( pstEncodeBuffer->aucBuffer,
                                                            &pstEncodeBuffer->ulBufferLen,
                                                            &stEncodeInfo))
    {
        NAS_LCS_SndAirMsgReportInd( pstEncodeBuffer->aucBuffer,
                                    pstEncodeBuffer->ulBufferLen,
                                    NAS_LCS_AIR_MSG_DIR_ENUM_UP,
                                    LCS_RELEASE_COMPLTE);

        /* 根据所属于的域发给响应模块 */
        if (NAS_LCS_DOMAIN_TYPE_CS_LCS == enLcsDomainType)
        {
            NAS_LCS_SndMmDataReq(   ucDlAirTi,
                                    pstEncodeBuffer->ulBufferLen,
                                    pstEncodeBuffer->aucBuffer);
        }
        else
        {
            NAS_LCS_SndLmmDataReq(  ucDlAirTi,
                                    pstEncodeBuffer->ulBufferLen,
                                    pstEncodeBuffer->aucBuffer);
        }
    }
}


/*****************************************************************************
Function Name  : NAS_LCS_SndRegister
Discription    : 发送REGISTER给网侧
Input          : ulIndex-----------------实体索引
Output         : None
Return         : None
History:
1.lihong 00150010 2015-10-13 Draft Enact
*****************************************************************************/
VOS_VOID NAS_LCS_SndRegister
(
    VOS_UINT32                          ulIndex
)
{
    NAS_LCS_ENCODE_INFO_STRU            stEncodeInfo    = {0};
    NAS_LCS_ENCODE_BUFFER_STRU         *pstEncodeBuffer = NAS_LCS_NULL_PTR;

    NAS_LCS_MEM_SET_S(  &stEncodeInfo,
                        sizeof(NAS_LCS_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_LCS_ENCODE_INFO_STRU));

    stEncodeInfo.ucTi           = NAS_LCS_GetEntityTi(ulIndex) - NAS_LCS_TI_OFFSET;
    stEncodeInfo.enStartSource  = NAS_LCS_GetEntityStrartSource(ulIndex);
    stEncodeInfo.enOperType     = NAS_LCS_OPERATION_MO_LR;
    stEncodeInfo.bitOpInvokeId  = NAS_LCS_OP_TRUE;
    stEncodeInfo.ucInvokeId     = NAS_LCS_GetEntityInvokeId(ulIndex);

    pstEncodeBuffer             = NAS_LCS_GetEncodeBuffer();
    if (NAS_LCS_CAUSE_SUCCESS == NAS_LCS_EncodeRegister(    pstEncodeBuffer->aucBuffer,
                                                            &pstEncodeBuffer->ulBufferLen,
                                                            &stEncodeInfo))
    {
        NAS_LCS_SndAirMsgReportInd( pstEncodeBuffer->aucBuffer,
                                    pstEncodeBuffer->ulBufferLen,
                                    NAS_LCS_AIR_MSG_DIR_ENUM_UP,
                                    LCS_REGISTER);

        /* 根据所属于的域发给响应模块 */
        if (NAS_LCS_DOMAIN_TYPE_CS_LCS == NAS_LCS_GetEntityLcsDomain(ulIndex))
        {
            NAS_LCS_SndMmDataReq(   NAS_LCS_GetEntityTi(ulIndex),
                                    pstEncodeBuffer->ulBufferLen,
                                    pstEncodeBuffer->aucBuffer);
        }
        else
        {
            NAS_LCS_SndLmmDataReq(  NAS_LCS_GetEntityTi(ulIndex),
                                    pstEncodeBuffer->ulBufferLen,
                                    pstEncodeBuffer->aucBuffer);
        }
    }
    else
    {
        /* 释放LCS实体 */
        NAS_LCS_ClearLcsEntityAndNotify(ulIndex, TAF_LCS_CAUSE_OTHERS);
    }
}


/*****************************************************************************
Function Name  : NAS_LCS_ClearAllEntity
Discription    : 释放所有实体
Input          : None
Output         : None
Return         : None
History:
1.lihong 00150010 2015-10-13 Draft Enact
*****************************************************************************/
VOS_VOID NAS_LCS_ClearAllEntity ( VOS_VOID )
{
    NAS_LCS_ENTITY_INFO_STRU           *pstLcsEntity    = NAS_LCS_NULL_PTR;
    VOS_UINT32                          i               = 0;

    for (i = NAS_LCS_MO_LR_LPP_INDEX; i <= NAS_LCS_MT_LR_ENTITY_INDEX_END; i++)
    {
        pstLcsEntity = NAS_LCS_GetLcsEntity(i);
        if (NAS_LCS_ENTITY_USED != pstLcsEntity->enUsedFlag)
        {
            continue ;
        }

        if (NAS_LCS_CONN_STATE_CONN == NAS_LCS_GetEntityConnState(i))
        {
            /* 编码RELEASE COMPLTE消息，发给网侧 */
            NAS_LCS_SndReleaseComplte(i);
        }

        NAS_LCS_ClearLcsEntityAndNotify(i, TAF_LCS_CAUSE_SUCCESS);
    }

    return ;
}

/*****************************************************************************
Function Name  : NAS_LCS_ClearResource
Discription    : 清除资源
Input          : None
Output         : None
Return         : None
History:
1.lihong 00150010 2015-10-13 Draft Enact
*****************************************************************************/
VOS_VOID NAS_LCS_ClearResource ( VOS_VOID )
{
    NAS_LCS_ClearAllEntity();

    NAS_LCS_Init();
}


/*****************************************************************************
Function Name  : NAS_LCS_ClearLcsEntityAndNotify
Discription    : 释放单个LCS实体并通知相关组件
Input          : ulIndex---------------索引
                 enCause---------------释放原因值
Output         : None
Return         : VOS_VOID
History:
1.lihong 00150010 2015-9-29 Draft Enact
*****************************************************************************/
VOS_VOID NAS_LCS_ClearLcsEntityAndNotify
(
    VOS_UINT32                          ulIndex,
    TAF_LCS_CAUSE_ENUM_UINT32           enCause
)
{
    if (NAS_LCS_MO_LR_LPP_INDEX == ulIndex)
    {
        /* 通知LPP获取辅助信息失败 */
        if (TAF_LCS_CAUSE_SUCCESS == enCause)
        {
            NAS_LCS_SndLppGnssAssistDataCnf(LCS_LPP_RSLT_SUCC);
        }
        else
        {
            NAS_LCS_SndLppGnssAssistDataCnf(LCS_LPP_RSLT_FAIL);
        }
    }

    /* 通知MM可以释放与此TI相关的LCS实体信息 */
    NAS_LCS_JudgeSndMmRelReq(ulIndex);

    /* 释放LCS实体 */
    NAS_LCS_ClearSingleLcsEntity(ulIndex, enCause);
}

/*****************************************************************************
Function Name  : NAS_LCS_QueryMolrEntity
Discription    : 通过TI查找MO-LR实体
Input          : ulTi------------------TI
Output         : pulIndex--------------实体索引指针
Return         : VOS_UINT32
History:
1.lihong 00150010 2015-9-29 Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LCS_QueryMolrEntity
(
    VOS_UINT32                          ulTi,
    VOS_UINT32                         *pulIndex
)
{
    NAS_LCS_ENTITY_INFO_STRU           *pstLcsEntity = NAS_LCS_NULL_PTR;

    pstLcsEntity = NAS_LCS_GetLcsEntity(NAS_LCS_MO_LR_LPP_INDEX);
    if ((NAS_LCS_ENTITY_USED == pstLcsEntity->enUsedFlag) && (ulTi == pstLcsEntity->ucTi))
    {
        *pulIndex = NAS_LCS_MO_LR_LPP_INDEX;
        return NAS_LCS_SUCC;
    }

    pstLcsEntity = NAS_LCS_GetLcsEntity(NAS_LCS_MO_LR_TAF_INDEX);
    if ((NAS_LCS_ENTITY_USED == pstLcsEntity->enUsedFlag) && (ulTi == pstLcsEntity->ucTi))
    {
        *pulIndex = NAS_LCS_MO_LR_TAF_INDEX;
        return NAS_LCS_SUCC;
    }

    return NAS_LCS_FAIL;
}

/*****************************************************************************
Function Name  : NAS_LCS_QueryMtLrEntity
Discription    : 通过TI查找MT-LR实体
Input          : ucHandleId------------Handle id
Output         : pulIndex--------------实体索引指针
Return         : VOS_UINT32
History:
1.lihong 00150010 2015-10-10 Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LCS_QueryMtLrEntity
(
    VOS_UINT8                           ucHandleId,
    VOS_UINT32                         *pulIndex
)
{
    NAS_LCS_ENTITY_INFO_STRU           *pstLcsEntity    = NAS_LCS_NULL_PTR;
    VOS_UINT32                          i               = 0;

    for (i = NAS_LCS_MT_LR_ENTITY_INDEX_BEGIN; i <= NAS_LCS_MT_LR_ENTITY_INDEX_END; i++)
    {
        pstLcsEntity = NAS_LCS_GetLcsEntity(i);
        if ((NAS_LCS_ENTITY_USED == pstLcsEntity->enUsedFlag) && (ucHandleId == pstLcsEntity->ucHandleId))
        {
            *pulIndex = i;
            return NAS_LCS_SUCC;
        }
    }

    return NAS_LCS_FAIL;
}

/*****************************************************************************
Function Name  : NAS_LCS_QueryLcsEntity
Discription    : 通过TI查找LCS实体
Input          : ulTi------------------TI
Output         : pulIndex--------------实体索引指针
Return         : VOS_UINT32
History:
1.lihong 00150010 2015-10-09 Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LCS_QueryLcsEntity
(
    VOS_UINT32                          ulTi,
    VOS_UINT32                         *pulIndex
)
{
    NAS_LCS_ENTITY_INFO_STRU           *pstLcsEntity    = NAS_LCS_NULL_PTR;
    VOS_UINT32                          i               = 0;

    pstLcsEntity = NAS_LCS_GetLcsEntity(NAS_LCS_MO_LR_LPP_INDEX);
    if ((NAS_LCS_ENTITY_USED == pstLcsEntity->enUsedFlag) && (ulTi == pstLcsEntity->ucTi))
    {
        *pulIndex = NAS_LCS_MO_LR_LPP_INDEX;
        return NAS_LCS_SUCC;
    }

    pstLcsEntity = NAS_LCS_GetLcsEntity(NAS_LCS_MO_LR_TAF_INDEX);
    if ((NAS_LCS_ENTITY_USED == pstLcsEntity->enUsedFlag) && (ulTi == pstLcsEntity->ucTi))
    {
        *pulIndex = NAS_LCS_MO_LR_TAF_INDEX;
        return NAS_LCS_SUCC;
    }

    for (i = NAS_LCS_MT_LR_ENTITY_INDEX_BEGIN; i <= NAS_LCS_MT_LR_ENTITY_INDEX_END; i++)
    {
        pstLcsEntity = NAS_LCS_GetLcsEntity(i);
        if ((NAS_LCS_ENTITY_USED == pstLcsEntity->enUsedFlag) && (ulTi == pstLcsEntity->ucTi))
        {
            *pulIndex = i;
            return NAS_LCS_SUCC;
        }
    }

    return NAS_LCS_FAIL;
}

/*****************************************************************************
Function Name  : NAS_LCS_ReadLcsNvCommonConfig
Discription    : 读取LCS公共NV配置
Input          : None
Output         : None
Return         : None
History:
1.lihong 00150010 2015-10-12 Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LCS_ReadLcsNvCommonConfig( VOS_VOID)
{
    VOS_UINT32                          ulRslt              = 0;
    LNAS_LCS_NV_COMMON_CONFIG_STRU      stLcsNvCommonConfig;
    NAS_LCS_COMM_NV_PARA_STRU          *pstCommNvPara       = NAS_LCS_NULL_PTR;

    NAS_LCS_NORM_LOG("NAS_LCS_ReadLcsNvCommonConfig enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LCS_ReadLcsNvCommonConfig_ENUM, LNAS_ENTRY);

    pstCommNvPara = NAS_LCS_GetCommNvPara();

    ulRslt = NAS_LCS_ReadNv(EN_NV_ID_LCS_COMMON_CONFIG, &stLcsNvCommonConfig,\
                                sizeof(LNAS_LCS_NV_COMMON_CONFIG_STRU));

    if(ulRslt == VOS_OK)
    {
        /*根据NV内容设置*/
        pstCommNvPara->bitOpPeriodicRptTimes    = stLcsNvCommonConfig.stLcsFeatureBit.bitOpPeriodicRptTimes;
        pstCommNvPara->ucMaxRetryTimes          = stLcsNvCommonConfig.ucMaxRetryTimes;
        pstCommNvPara->usPeriodicRptTimes       = stLcsNvCommonConfig.usPeriodicRptTimes;
        pstCommNvPara->usRetryTimerLen          = stLcsNvCommonConfig.usRetryTimerLen;
    }
    else
    {
        NAS_LCS_WARN_LOG("NAS_LCS_ReadLcsNvCommonConfig, Read NV Err.");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_ReadLcsNvCommonConfig_ENUM, LNAS_LCS_ReadNvCommonConfigFail);

        pstCommNvPara->bitOpPeriodicRptTimes    = NAS_LCS_OP_FALSE;
        pstCommNvPara->ucMaxRetryTimes          = 2;
        pstCommNvPara->usPeriodicRptTimes       = 0;
        pstCommNvPara->usRetryTimerLen          = 2;
    }

    return;
}


/*****************************************************************************
Function Name  : NAS_LCS_GetLcsEntityNum
Description    : 获取LCS实体个数
Input          : None
Output         : None
Return Value   : VOS_UINT32

History        :
lihong 00150010 2015-10-10  新开发
*****************************************************************************/
VOS_UINT32  NAS_LCS_GetLcsEntityNum( VOS_VOID )
{
    NAS_LCS_ENTITY_INFO_STRU           *pstLcsEntity    = NAS_LCS_NULL_PTR;
    VOS_UINT32                          i               = 0;
    VOS_UINT32                          ulEntityNum     = 0;

    for (i = NAS_LCS_MO_LR_LPP_INDEX; i <= NAS_LCS_MT_LR_ENTITY_INDEX_END; i++)
    {
        pstLcsEntity = NAS_LCS_GetLcsEntity(i);
        if (NAS_LCS_ENTITY_USED == pstLcsEntity->enUsedFlag)
        {
            ulEntityNum++;
        }
    }

    return ulEntityNum;
}

/*****************************************************************************
Function Name  : NAS_LCS_SetEntityState
Description    : 设置实体状态
Input          : ulIndex-------------实体索引
                 enEntityState-------实体状态
Output         : None
Return Value   : VOS_UINT32

History        :
lihong 00150010 2015-10-10  新开发
*****************************************************************************/
VOS_VOID NAS_LCS_SetEntityState
(
    VOS_UINT32                          ulIndex,
    NAS_LCS_ENTITY_STATE_ENUM_UINT8     enEntityState
)
{
    NAS_LCS_SndOmEntityStateInfo(ulIndex, NAS_LCS_GetEntityState(ulIndex), enEntityState);

    NAS_LCS_GetEntityState(ulIndex) = enEntityState;
}

/*****************************************************************************
Function Name  : NAS_LCS_SetEntityConnState
Description    : 设置实体连接状态
Input          : ulIndex-------------实体索引
                 enEntityState-------实体状态
Output         : None
Return Value   : VOS_UINT32

History        :
lihong 00150010 2015-10-10  新开发
*****************************************************************************/
VOS_VOID NAS_LCS_SetEntityConnState
(
    VOS_UINT32                          ulIndex,
    NAS_LCS_CONN_STATE_ENUM_UINT8       enConnState
)
{
    NAS_LCS_SndOmEntityConnStateInfo(ulIndex, NAS_LCS_GetEntityConnState(ulIndex), enConnState);

    NAS_LCS_GetEntityConnState(ulIndex) = enConnState;
}


/*****************************************************************************
Function Name  : NAS_LCS_ProcMolrConnAbnormal
Description    : 处理MOLR流程链路异常
Input          : ulIndex-------------实体索引
                 enTafLcsCause-------原因值
Output         : None
Return Value   : VOS_VOID

History        :
lihong 00150010 2015-10-10  新开发
*****************************************************************************/
VOS_VOID  NAS_LCS_ProcMolrConnAbnormal
(
    VOS_UINT32                          ulIndex,
    TAF_LCS_CAUSE_ENUM_UINT32           enTafLcsCause
)
{
    /* 尝试次数加1 */
    NAS_LCS_AddEntityEstRetryTimers(ulIndex);

    /* 如果尝试次数已达最大次数，则如果能换域尝试则换域，否则释放实体信息 */
    if (NAS_LCS_GetEntityEstRetryTimers(ulIndex) >= NAS_LCS_GetNvMaxRetryTimes())
    {
        /* 如果是周期性的，则认为单次结束，否则尝试换域 */
        if ((NAS_LCS_MO_LR_TAF_INDEX == ulIndex) && (LCS_REP_MODE_PERIODIC_RPT == NAS_LCS_GetMolrMode()))
        {
            /* 重置建链尝试次数 */
            NAS_LCS_ResetEntityEstRetryTimers(ulIndex);

            /* 周期性MO-LR单次失败处理 */
            NAS_LCS_ProcPeriodMolrOnceAbnormalEnd(ulIndex, enTafLcsCause);
        }
        else
        {
            /* 尝试换域 */
            NAS_LCS_TryToChangeDomain(ulIndex, enTafLcsCause);
        }

        return ;
    }

    /* 设置连接状态为IDLE态 */
    NAS_LCS_SetEntityConnState(ulIndex, NAS_LCS_CONN_STATE_IDLE);

    /* 启动等待重建定时器，待定时器超时后再发起 */
    NAS_LCS_StartTimer(ulIndex, TI_NAS_LCS_WATI_REEST_TIMER);
}


/*****************************************************************************
Function Name  : NAS_LCS_GetPeriodicRptTimesSwtich
Description    : 获取周期性上报次数特性开关
Input          : pstCnMsgStru----------译码后内容结构指针
Output         : None
Return Value   : VOS_VOID

History        :
lihong 00150010 2015-10-08  新开发
*****************************************************************************/
VOS_UINT32  NAS_LCS_GetPeriodicRptTimesSwtich( VOS_VOID )
{
    NAS_LCS_COMM_NV_PARA_STRU          *pstCommNvPara = NAS_LCS_NULL_PTR;

    pstCommNvPara = NAS_LCS_GetCommNvPara();
    if (NAS_LCS_OP_TRUE == pstCommNvPara->bitOpPeriodicRptTimes)
    {
        return PS_TRUE;
    }

    return PS_FALSE;
}

/*****************************************************************************
Function Name  : NAS_LCS_ProcPeriodMolrOnceNormalEnd
Description    : 处理周期性MOLR单次正常结束
Input          : ulIndex-------------------------实体索引
Output         : None
Return Value   : VOS_VOID

History        :
lihong 00150010 2015-10-09  新开发
*****************************************************************************/
VOS_VOID  NAS_LCS_ProcPeriodMolrOnceNormalEnd
(
    VOS_UINT32                          ulIndex
)
{
    /* 判断周期性计数的特性功能是否打开 */
    if (PS_FALSE == NAS_LCS_GetPeriodicRptTimesSwtich())
    {
        /* 状态转到周期间隔 */
        NAS_LCS_SetEntityState(ulIndex, NAS_LCS_ENTITY_STATE_PERIOD_INTERVAL);

        /* 启动周期间隔定时器 */
        NAS_LCS_StartTimer(ulIndex, TI_NAS_LCS_PERIOD_INTERVAL_TIMER);

        return ;
    }

    /* 周期尝试次数加1 */
    NAS_LCS_AddEntityPediodRetryTimers(ulIndex);

    /* 如果尝试次数还未达到最大次数 */
    if (NAS_LCS_GetEntityPediodRetryTimers(ulIndex) < NAS_LCS_GetNvMaxPeriodicRptTimes())
    {
        /* 状态转到周期间隔 */
        NAS_LCS_SetEntityState(ulIndex, NAS_LCS_ENTITY_STATE_PERIOD_INTERVAL);

        /* 启动周期间隔定时器 */
        NAS_LCS_StartTimer(ulIndex, TI_NAS_LCS_PERIOD_INTERVAL_TIMER);

        return ;
    }

    /* 编码RELEASE COMPLTE，发给网侧 */
    NAS_LCS_SndReleaseComplte(ulIndex);

    /* 通知MM可以释放与此TI相关的LCS实体信息 */
    NAS_LCS_JudgeSndMmRelReq(ulIndex);

    /* 释放LCS实体 */
    NAS_LCS_ClearSingleLcsEntity(ulIndex, TAF_LCS_CAUSE_SUCCESS);
}

/*****************************************************************************
Function Name  : NAS_LCS_ProcPeriodMolrOnceAbnormalEnd
Description    : 处理周期性MOLR单次异常结束
Input          : ulIndex-------------------------实体索引
                 enCause-------------------------异常原因
Output         : None
Return Value   : VOS_VOID

History        :
lihong 00150010 2015-10-09  新开发
*****************************************************************************/
VOS_VOID  NAS_LCS_ProcPeriodMolrOnceAbnormalEnd
(
    VOS_UINT32                          ulIndex,
    TAF_LCS_CAUSE_ENUM_UINT32           enCause
)
{

    NAS_LCS_StopTimer(ulIndex, NAS_LCS_ENTITY_STATE_WAIT_NW_RSP);

    /* 判断周期性计数的特性功能是否打开 */
    if (PS_FALSE == NAS_LCS_GetPeriodicRptTimesSwtich())
    {
        /* 状态转到周期间隔 */
        NAS_LCS_SetEntityState(ulIndex, NAS_LCS_ENTITY_STATE_PERIOD_INTERVAL);

        /* 启动周期间隔定时器 */
        NAS_LCS_StartTimer(ulIndex, TI_NAS_LCS_PERIOD_INTERVAL_TIMER);

        /* 通过LCS_TAF_FACILITY_IND告知TAF单次MO-LR错误 */
        NAS_LCS_SndTafFacilityInd(NAS_LCS_NULL_PTR, NAS_LCS_NULL_PTR, enCause);

        return ;
    }

    /* 周期尝试次数加1 */
    NAS_LCS_AddEntityPediodRetryTimers(ulIndex);

    /* 如果尝试次数还未达到最大次数 */
    if (NAS_LCS_GetEntityPediodRetryTimers(ulIndex) < NAS_LCS_GetNvMaxPeriodicRptTimes())
    {
        /* 状态转到周期间隔 */
        NAS_LCS_SetEntityState(ulIndex, NAS_LCS_ENTITY_STATE_PERIOD_INTERVAL);

        /* 启动周期间隔定时器 */
        NAS_LCS_StartTimer(ulIndex, TI_NAS_LCS_PERIOD_INTERVAL_TIMER);

        /* 通过LCS_TAF_FACILITY_IND告知TAF单次MO-LR错误 */
        NAS_LCS_SndTafFacilityInd(NAS_LCS_NULL_PTR, NAS_LCS_NULL_PTR, enCause);

        return ;
    }

    /* 通知MM可以释放与此TI相关的LCS实体信息 */
    NAS_LCS_JudgeSndMmRelReq(ulIndex);

    /* 释放LCS实体 */
    NAS_LCS_ClearSingleLcsEntity(ulIndex, enCause);
}


/*****************************************************************************
Function Name  : NAS_LCS_ProcAirMsgFacility
Description    : 处理空口消息FICILITY
Input          : pstCnMsgStru----------译码后内容结构指针
Output         : None
Return Value   : VOS_VOID

History        :
lihong 00150010 2015-10-08  新开发
*****************************************************************************/
VOS_VOID  NAS_LCS_ProcAirMsgFacility
(
    NAS_LCS_CN_MSG_STRU                *pstCnMsgStru
)
{
    VOS_UINT32                          ulRslt              = 0;
    VOS_UINT32                          ulIndex             = 0;
    LOC_COM_COORDINATE_STRU            *pstLocationEstimate = NAS_LCS_NULL_PTR;
    LOC_COM_VELOCITY_STRU              *pstVelocityEstimate = NAS_LCS_NULL_PTR;

    /* 通过TI查找关联实体 */
    ulRslt = NAS_LCS_QueryMolrEntity(pstCnMsgStru->ucTi, &ulIndex);
    if (NAS_LCS_FAIL == ulRslt)
    {
        NAS_LCS_WARN_LOG("NAS_LCS_ProcAirMsgFacility:query entity fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_ProcAirMsgFacility_ENUM, LNAS_LCS_QueryEntityFail);
        NAS_LCS_SndOmEntityInfo();
        return ;
    }

    /* 判断实体状态是否为等待网侧响应，若不是，则直接返回 */
    if (NAS_LCS_ENTITY_STATE_WAIT_NW_RSP != NAS_LCS_GetEntityState(ulIndex))
    {
        NAS_LCS_WARN_LOG("NAS_LCS_ProcAirMsgFacility:entity state invalid!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_ProcAirMsgFacility_ENUM, LNAS_LCS_EntityStateInvalid);
        return ;
    }

    /* 停止等待网侧相应定时器 */
    NAS_LCS_StopTimer(ulIndex, TI_NAS_LCS_WAIT_NW_RSP_TIMER);

    /* 如果是LPP出发的MO-LR，则给LPP回复成功，释放LCS实体 */
    if (NAS_LCS_MO_LR_LPP_INDEX == ulIndex)
    {
        /* 通知LPP获取辅助信息成功 */
        NAS_LCS_SndLppGnssAssistDataCnf(LCS_LPP_RSLT_SUCC);

        /* 编码RELEASE COMPLTE，发给网侧 */
        NAS_LCS_SndReleaseComplte(ulIndex);

        /* 释放LCS实体 */
        NAS_LCS_ClearSingleLcsEntity(NAS_LCS_MO_LR_LPP_INDEX, TAF_LCS_CAUSE_SUCCESS);

        return ;
    }

    /*如果是TAF出发的MOLR流程*/
    if (NAS_LCS_MO_LR_TAF_INDEX == ulIndex)
    {
        /* 给TAF发送定位结果 */
        if (NAS_LCS_OP_TRUE ==  pstCnMsgStru->stMolrResult.bitOpLocationEstimate)
        {
            pstLocationEstimate = &pstCnMsgStru->stMolrResult.stLocationEstimate;
        }

        if (NAS_LCS_OP_TRUE ==  pstCnMsgStru->stMolrResult.bitOpVelocityEstimate)
        {
            pstVelocityEstimate = &pstCnMsgStru->stMolrResult.stVelocityEstimate;
        }

        NAS_LCS_SndTafFacilityInd(pstLocationEstimate, pstVelocityEstimate, TAF_LCS_CAUSE_SUCCESS);

        /* 当选择域为EPC LCS时需要通知LPP位置信息 */
        if (NAS_LCS_DOMAIN_TYPE_EPC_LCS == NAS_LCS_GetEntityLcsDomain(ulIndex))
        {
            /* 给LPP发送位置信息 */
            NAS_LCS_SndLppLocationInfoNtf(pstLocationEstimate, pstVelocityEstimate);
        }

        /* 区分是单次还是周期类型，分别处理 */
        if (LCS_REP_MODE_SINGLE_RPT == NAS_LCS_GetMolrMode())
        {
            /* 编码RELEASE COMPLTE，发给网侧 */
            NAS_LCS_SndReleaseComplte(ulIndex);

            /* 通知MM可以释放与此TI相关的LCS实体信息 */
            NAS_LCS_JudgeSndMmRelReq(ulIndex);

            /* 释放LCS实体 */
            NAS_LCS_ClearSingleLcsEntity(ulIndex, TAF_LCS_CAUSE_SUCCESS);

            return ;
        }
        else
        {
            /* 处理周期性MOLR单次结束 */
            NAS_LCS_ProcPeriodMolrOnceNormalEnd(ulIndex);

            return ;
        }
    }
}

/*****************************************************************************
Function Name  : NAS_LCS_ProcAirMsgReleaseComplete
Description    : 处理空口消息RELEASE COMPLTE
Input          : pstCnMsgStru----------译码后内容结构指针
Output         : None
Return Value   : VOS_VOID

History        :
lihong 00150010 2015-10-09  新开发
*****************************************************************************/
VOS_VOID  NAS_LCS_ProcAirMsgReleaseComplete
(
    NAS_LCS_CN_MSG_STRU                *pstCnMsgStru
)
{
    VOS_UINT32                          ulRslt  = 0;
    VOS_UINT32                          ulIndex = 0;

    /* 通过TI查找关联实体 */
    ulRslt = NAS_LCS_QueryLcsEntity(pstCnMsgStru->ucTi, &ulIndex);
    if (NAS_LCS_FAIL == ulRslt)
    {
        NAS_LCS_WARN_LOG("NAS_LCS_ProcAirMsgReleaseComplete:query entity fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_ProcAirMsgReleaseComplete_ENUM, LNAS_LCS_QueryEntityFail);
        NAS_LCS_SndOmEntityInfo();
        return ;
    }

    /* 停止所有定时器 */
    NAS_LCS_StopAllTimer(ulIndex);

    /* 释放单个LCS实体并通知相关组件 */
    if (NAS_LCS_OP_TRUE == pstCnMsgStru->bitOpNwCause)
    {
        NAS_LCS_ClearLcsEntityAndNotify(ulIndex, pstCnMsgStru->enNwCause + TAF_LCS_CAUSE_NW_SECTION_BEGIN);
    }
    else
    {
        NAS_LCS_ClearLcsEntityAndNotify(ulIndex, TAF_LCS_CAUSE_SUCCESS);
    }
}

/*****************************************************************************
Function Name  : NAS_LCS_ValidateAirMsgRegister
Description    : 合法性检测空口消息GEGISTER
Input          : pstCnMsgStru----------译码后内容结构指针
Output         : None
Return Value   : VOS_UINT32

History        :
lihong 00150010 2015-10-10  新开发
*****************************************************************************/
VOS_UINT32  NAS_LCS_ValidateAirMsgRegister
(
    NAS_LCS_CN_MSG_STRU                *pstCnMsgStru
)
{
    /* 判断OPERATION CODE是否合法 */
    if ((NAS_LCS_OP_FALSE == pstCnMsgStru->bitOperationCode)
        || (NAS_LCS_OPERATION_LOC_NOTIFICATION != pstCnMsgStru->ucOperationCode))
    {
        NAS_LCS_WARN_LOG("NAS_LCS_ValidateAirMsgRegister:operation code is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_ValidateAirMsgRegister_ENUM, LNAS_LCS_InvalidOperationCode);

        return NAS_LCS_FAIL;
    }

    /* 如果没有locationNotification，即operation code为116，则返回失败 */
    if (NAS_LCS_OP_FALSE == pstCnMsgStru->bitOpLocNotification)
    {
        NAS_LCS_WARN_LOG("NAS_LCS_ValidateAirMsgRegister:LocationNotification not exist");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_ValidateAirMsgRegister_ENUM, LNAS_LCS_LocationNotificationNotExist);

        return NAS_LCS_FAIL;
    }

    /* 如果为location not allowed，则返回失败 */
    if (NAS_LCS_NOTIFY_TYPE_LOC_NOT_ALLOWED == pstCnMsgStru->stLocNotication.enNtfType)
    {
        NAS_LCS_WARN_LOG("NAS_LCS_ValidateAirMsgRegister:LocationNotAllowed");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_ValidateAirMsgRegister_ENUM, LNAS_LCS_LocationNotAllowed);

        return NAS_LCS_FAIL;
    }

    /* 如果为location not allowed，则返回失败 */
    if ((NAS_LCS_LOCATION_TYPE_ACT_DEFER_LOC == pstCnMsgStru->stLocNotication.stLocationType.enLocType)
        || (NAS_LCS_LOCATION_TYPE_CANCEL_DEFER_LOC == pstCnMsgStru->stLocNotication.stLocationType.enLocType))
    {
        NAS_LCS_WARN_LOG("NAS_LCS_ValidateAirMsgRegister:enLocType Invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_ValidateAirMsgRegister_ENUM, LNAS_LCS_InvalidLocType);

        return NAS_LCS_FAIL;
    }

    return NAS_LCS_SUCC;
}

/*****************************************************************************
Function Name  : NAS_LCS_ProcAirMsgRegister
Description    : 处理空口消息GEGISTER
Input          : pstCnMsgStru----------译码后内容结构指针
                 enLcsDomainType-------LCS域
Output         : None
Return Value   : VOS_VOID

History        :
lihong 00150010 2015-10-10  新开发
*****************************************************************************/
VOS_VOID  NAS_LCS_ProcAirMsgRegister
(
    NAS_LCS_CN_MSG_STRU                *pstCnMsgStru,
    NAS_LCS_DOMAIN_TYPE_ENUM_UINT8      enLcsDomainType
)
{
    VOS_UINT32                          ulIndex             = 0;
    VOS_UINT8                           ucHandleId          = 0;
    NAS_LCS_NW_MSG_RECORD_STRU         *pstLcsNwMsgRecord   = NAS_LCS_NULL_PTR;

    /* 判断当前驻留接入技术是否支持LCS */
    if (PS_FALSE == NAS_LCS_IsCurrRatSupportLcs())
    {
        NAS_LCS_WARN_LOG("NAS_LCS_ProcAirMsgRegister:Curr Rat Not Support Lcs!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_ProcAirMsgRegister_ENUM, LNAS_LCS_NotSupportLcs);
        return;
    }

    /* 消息合法性检测 */
    if (NAS_LCS_FAIL == NAS_LCS_ValidateAirMsgRegister(pstCnMsgStru))
    {
        /* 编码RELEASE COMPLTE消息发给网侧 */
        NAS_LCS_SndMtlrFailReleaseComplte(  pstCnMsgStru->ucTi,
                                            pstCnMsgStru->ucInvokeId,
                                            enLcsDomainType,
                                            NAS_LCS_CAUSE_NW_ERR_UNEXPECT_DATA_VALUE);
        return ;
    }

    /* 创建网侧触发的MT-LR实体，如果创建失败，则直接给网侧回复RELEASE COMPLTE */
    if (NAS_LCS_FAIL == NAS_LCS_CreateLcsEntity(    NAS_LCS_START_SOURCE_NW,
                                                    &ulIndex))
    {
        NAS_LCS_WARN_LOG("NAS_LCS_ProcAirMsgRegister:create entity fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_ProcAirMsgRegister_ENUM, LNAS_LCS_CreateEntityFail);
        NAS_LCS_SndOmEntityInfo();

        /* 编码RELEASE COMPLTE消息发给网侧 */
        NAS_LCS_SndMtlrFailReleaseComplte(  pstCnMsgStru->ucTi,
                                            pstCnMsgStru->ucInvokeId,
                                            enLcsDomainType,
                                            NAS_LCS_NW_CAUSE_BUTT);

        return ;
    }

    /* 存储MT-LR实体信息 */
    pstLcsNwMsgRecord = NAS_LCS_GetEntityNwMsgRecord(ulIndex);
    pstLcsNwMsgRecord->enNotificationType = pstCnMsgStru->stLocNotication.enNtfType;

    /* 存储Invoke Id */
    NAS_LCS_SetEntityInvokeId(ulIndex, pstCnMsgStru->ucInvokeId);

    /* 记录实体域信息为选择的域 */
    NAS_LCS_SetEntityLcsDomain(ulIndex, enLcsDomainType);

    /* 存储TI */
    NAS_LCS_SetEntityTi(ulIndex, pstCnMsgStru->ucTi);

    /* 启动等待用户响应定时器 */
    NAS_LCS_StartTimer(ulIndex, TI_NAS_LCS_WAIT_UE_RSP_TIMER);

    /* 获取在实体创建时保持的HAND ID, 带给TAF */
    ucHandleId = NAS_LCS_GetEntityHandleId(ulIndex);

    /* 给TAF发LCS_TAF_BEGIN_IND */
    NAS_LCS_SndTafBeginInd(&pstCnMsgStru->stLocNotication, ucHandleId);

    /* 更新实体连接状态为建链过程中 */
    NAS_LCS_SetEntityConnState(ulIndex, NAS_LCS_CONN_STATE_CONN);
}

/*****************************************************************************
Function Name  : NAS_LCS_SndDecodeFailRelComplete
Description    : 空口译码失败,回复网侧RelComplete
Input          : enCause---------------回复网络原因值
Output         : pstCnMsgStru----------译码后内容结构指针
Return Value   : VOS_VOID

History        :
leixiantiao 00258641 2015-10-08  新开发
*****************************************************************************/
VOS_VOID NAS_LCS_SndDecodeFailRelComplete
(
    NAS_LCS_NW_CAUSE_ENUM_UINT32        enCause,
    NAS_LCS_CN_MSG_STRU                *pstCnMsgStru,
    NAS_LCS_DOMAIN_TYPE_ENUM_UINT8      enLcsDomainType
)
{
    NAS_LCS_ENCODE_INFO_STRU            stEncodeInfo;
    NAS_LCS_ENCODE_BUFFER_STRU         *pstEncodeBuffer = NAS_LCS_NULL_PTR;

    NAS_LCS_MEM_SET_S(  &stEncodeInfo,
                        sizeof(NAS_LCS_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_LCS_ENCODE_INFO_STRU));

    /* 填写空口TI值原因值以及InvokeId */
    if (NAS_LCS_TI_OFFSET > pstCnMsgStru->ucTi)
    {
        stEncodeInfo.ucTi   = pstCnMsgStru->ucTi + NAS_LCS_TI_OFFSET;
    }
    else
    {
        stEncodeInfo.ucTi   = pstCnMsgStru->ucTi - NAS_LCS_TI_OFFSET;
    }

    stEncodeInfo.bitOpCause = NAS_LCS_OP_TRUE;
    stEncodeInfo.enCause    = enCause;
    if (NAS_LCS_OP_TRUE == pstCnMsgStru->bitOpInvokeId)
    {
        stEncodeInfo.bitOpInvokeId = NAS_LCS_OP_TRUE;
        stEncodeInfo.ucInvokeId    = pstCnMsgStru->ucInvokeId;
    }

    pstEncodeBuffer             = NAS_LCS_GetEncodeBuffer();

    /* 编码RELEASE COMPLETE */
    if (NAS_LCS_CAUSE_SUCCESS == NAS_LCS_EncodeRelComplete( pstEncodeBuffer->aucBuffer,
                                                            &pstEncodeBuffer->ulBufferLen,
                                                            &stEncodeInfo))
    {
        NAS_LCS_SndAirMsgReportInd( pstEncodeBuffer->aucBuffer,
                                    pstEncodeBuffer->ulBufferLen,
                                    NAS_LCS_AIR_MSG_DIR_ENUM_UP,
                                    LCS_RELEASE_COMPLTE);

        /* 根据所属于的域发给响应模块 */
        if (NAS_LCS_DOMAIN_TYPE_CS_LCS == enLcsDomainType)
        {
            NAS_LCS_SndMmDataReq(   pstCnMsgStru->ucTi,
                                    pstEncodeBuffer->ulBufferLen,
                                    pstEncodeBuffer->aucBuffer);
        }
        else
        {
            NAS_LCS_SndLmmDataReq(  pstCnMsgStru->ucTi,
                                    pstEncodeBuffer->ulBufferLen,
                                    pstEncodeBuffer->aucBuffer);
        }
    }
}

/*****************************************************************************
Function Name  : NAS_LCS_ProcNwMsgDecodeFail
Description    : 处理空口译码失败
Input          : enRslt----------------空口译码结果
Output         : pstCnMsgStru----------译码后内容结构指针
Return Value   : VOS_VOID

History        :
leixiantiao 00258641 2015-10-08  新开发
*****************************************************************************/
VOS_VOID NAS_LCS_ProcNwMsgDecodeFail
(
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt,
    NAS_LCS_CN_MSG_STRU                *pstCnMsgStru,
    NAS_LCS_DOMAIN_TYPE_ENUM_UINT8      enLcsDomainType
)
{
    NAS_LCS_NW_CAUSE_ENUM_UINT32        enNwCause;
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulIndex;

    /* 者普通失败不需要处理,直接丢弃 */
    if (NAS_LCS_CAUSE_FAIL == enRslt)
    {
        return;
    }
    else
    {
        /* 只有网侧的Facility和Register消息译码失败需要处理 */
        if ((NAS_LCS_CN_MSG_FACILITY == pstCnMsgStru->enCnMsgType)
            || (NAS_LCS_CN_MSG_REGISTER == pstCnMsgStru->enCnMsgType))
        {
            switch(enRslt)
            {
                case NAS_LCS_CAUSE_UNRECOGNIZED_COMPONENT:
                    enNwCause = NAS_LCS_NW_CAUSE_UNRECOGNIZED_COMPONENT;
                    break;

                case NAS_LCS_CAUSE_MISTYPED_PARAMETER:
                    if (NAS_LCS_CN_MSG_FACILITY == pstCnMsgStru->enCnMsgType)
                    {
                        enNwCause = NAS_LCS_NW_CAUSE_RETURN_RSLT_MISTYPED_PARAMETER;
                    }
                    else
                    {
                        enNwCause = NAS_LCS_NW_CAUSE_INVOKE_MISTYPED_PARAMETER;
                    }
                    break;

                default:
                    enNwCause = NAS_LCS_CAUSE_NW_ERR_UNEXPECT_DATA_VALUE;
                    break;
            }

            /* 回复网侧Rel Cmp */
            NAS_LCS_SndDecodeFailRelComplete(enNwCause, pstCnMsgStru, enLcsDomainType);
        }

        /* 通过TI查找关联实体 */
        ulRslt = NAS_LCS_QueryLcsEntity(pstCnMsgStru->ucTi, &ulIndex);
        if (NAS_LCS_FAIL == ulRslt)
        {
            return;
        }

        /* 若存在当前实体, 则需要释放单个LCS实体并通知相关组件 */
        NAS_LCS_ClearLcsEntityAndNotify(ulIndex, TAF_LCS_CAUSE_OTHERS);
    }
    return;
}

/*****************************************************************************
Function Name  : NAS_LCS_SndDownAirMsgReportInd
Description    : 勾LCS下行空口
Input          : pucMsg----------------空口消息指针
                 ulLen-----------------空口消息长度
                 enCnMsgType-----------空口类型
Output         : NONE
Return Value   : VOS_VOID

History        :
lihong 00150010 2015-10-08  新开发
*****************************************************************************/
VOS_VOID NAS_LCS_SndDownAirMsgReportInd
(
    VOS_UINT8                          *pucMsg,
    VOS_UINT32                          ulLen,
    NAS_LCS_CN_MSG_TYPE_ENUM_UINT32     enCnMsgType

)
{

    OM_PS_AIR_MSG_ENUM_UINT8            enMsgId;

    if (NAS_LCS_CN_MSG_REL_CML == enCnMsgType)
    {
        enMsgId = LCS_RELEASE_COMPLTE;
    }
    else if (NAS_LCS_CN_MSG_FACILITY == enCnMsgType)
    {
        enMsgId = LCS_FACILITY;
    }
    else if (NAS_LCS_CN_MSG_REGISTER == enCnMsgType)
    {
        enMsgId = LCS_REGISTER;
    }
    else
    {
        TLPS_PRINT2LAYER_ERROR1(NAS_LCS_SndDownAirMsgReportInd_ENUM, LNAS_LCS_MsgTypeInvalid, enCnMsgType);
        NAS_LCS_ERR_LOG1("NAS_LCS_SndDownAirMsgReportInd CnMsgType Error ", enCnMsgType);
        return;
    }

    /* 抛出空口可维可测 */
    NAS_LCS_SndAirMsgReportInd( pucMsg,
                                ulLen,
                                NAS_LCS_AIR_MSG_DIR_ENUM_DOWN,
                                enMsgId);
}
/*****************************************************************************
Function Name  : NAS_LCS_ProcAirMsg
Description    : 处理空口消息
Input          : pucMsg----------------空口消息指针
                 ulLen-----------------空口消息长度
                 enLcsDomainType-------LCS域
Output         : pstCnMsgStru----------译码后内容结构指针
Return Value   : VOS_VOID

History        :
lihong 00150010 2015-10-08  新开发
*****************************************************************************/
VOS_VOID  NAS_LCS_ProcAirMsg
(
    VOS_UINT8                          *pucMsg,
    VOS_UINT32                          ulLen,
    NAS_LCS_CN_MSG_STRU                *pstCnMsgStru,
    NAS_LCS_DOMAIN_TYPE_ENUM_UINT8      enLcsDomainType
)
{
    VOS_UINT32                          ulRslt      = 0;
    VOS_UINT32                          ulLenTmp    = ulLen;

    NAS_LCS_MEM_SET_S(  pstCnMsgStru,
                        sizeof(NAS_LCS_CN_MSG_STRU),
                        0,
                        sizeof(NAS_LCS_CN_MSG_STRU));

    /* 进行译码 */
    ulRslt = NAS_LCS_DecodeCnMsg(   pucMsg,
                                    &ulLenTmp,
                                    pstCnMsgStru);

    /* 勾出空口消息 */
    NAS_LCS_SndDownAirMsgReportInd(pucMsg, ulLen, pstCnMsgStru->enCnMsgType);

    /* 译码失败，则丢弃消息不处理 */
    if (NAS_LCS_CAUSE_SUCCESS != ulRslt)
    {
        NAS_LCS_WARN_LOG("NAS_LCS_ProcAirMsg,Decode fail");
        TLPS_PRINT2LAYER_WARNING(NAS_LCS_ProcAirMsg_ENUM, LNAS_LCS_DecodeFail);
        NAS_LCS_ProcNwMsgDecodeFail(ulRslt, pstCnMsgStru, enLcsDomainType);
        return ;
    }

    /* 对各空口消息进行分别处理 */
    switch (pstCnMsgStru->enCnMsgType)
    {
        case NAS_LCS_CN_MSG_REL_CML:
            NAS_LCS_ProcAirMsgReleaseComplete(pstCnMsgStru);
            break;

        case NAS_LCS_CN_MSG_FACILITY:
            NAS_LCS_ProcAirMsgFacility(pstCnMsgStru);
            break;

        case NAS_LCS_CN_MSG_REGISTER:
            NAS_LCS_ProcAirMsgRegister(pstCnMsgStru, enLcsDomainType);
            break;

        default:
            NAS_LCS_WARN_LOG("NAS_LCS_ProcAirMsg,Invalid Msg");
            TLPS_PRINT2LAYER_WARNING(NAS_LCS_ProcAirMsg_ENUM, LNAS_LCS_InvalidMsg);
            break;
    }
}

/*****************************************************************************
Function Name  : NAS_LCS_LmmEstCnfCauseMap
Description    : 把LMM EST结果转换为TAF与LCS之间的原因值
Input          : enCause----------------LMM EST原因值
Output         : NULL
Return Value   : TAF_LCS_CAUSE_ENUM_UINT32: 转换后原因值

History        :
leixiantiao 00258641 2015-10-08  新开发
*****************************************************************************/
TAF_LCS_CAUSE_ENUM_UINT32 NAS_LCS_LmmEstCnfCauseMap(const LMM_LCS_EST_RESULT_ENUM_UINT32 enCause)
{
    TAF_LCS_CAUSE_ENUM_UINT32 enTafCause = TAF_LCS_CAUSE_SUCCESS;

    switch(enCause)
    {
        case LMM_LCS_EST_RSLT_SUCC:
            enTafCause = TAF_LCS_CAUSE_SUCCESS;
            break;

        case LMM_LCS_EST_RSLT_FAIL_PS_NOT_ATTACHED:
            enTafCause = TAF_LCS_CAUSE_LMM_PS_NOT_ATTACHED;
            break;

        case LMM_LCS_EST_RSLT_FAIL_PS_ATTACH_NOT_ALLOWED:
            enTafCause = TAF_LCS_CAUSE_LMM_PS_ATTACH_NOT_ALLOWED;
            break;

        case LMM_LCS_EST_RSLT_FAIL_USIM_PS_INVALID:
            enTafCause = TAF_LCS_CAUSE_LMM_USIM_PS_INVAILD;
            break;

        case LMM_LCS_EST_RSLT_FAIL_ACCESS_BARRED:
            enTafCause = TAF_LCS_CAUSE_LMM_ACCESS_BARRED;
            break;

        case LMM_LCS_EST_RSLT_FAIL_STATE_CANNOT_SERVICE:
            enTafCause = TAF_LCS_CAUSE_LMM_STATE_CANNOT_SERVICE;
            break;

        case LMM_LCS_EST_RSLT_FAIL_EPC_LCS_NOT_SUPPORT:
            enTafCause = TAF_LCS_CAUSE_LMM_EPC_LCS_NOT_SUPPORT;
            break;

        case LMM_LCS_EST_RSLT_FAIL_3411_RUNNING:
            enTafCause = TAF_LCS_CAUSE_LMM_3411_RUNNING;
            break;

        case LMM_LCS_EST_RSLT_FAIL_SERVICE_FAIL:
            enTafCause = TAF_LCS_CAUSE_LMM_SERVICE_FAIL;
            break;

        default:
            enTafCause = TAF_LCS_CAUSE_LMM_OTHERS;
            break;
    }
    return enTafCause;
}

/*****************************************************************************
Function Name  : NAS_LCS_LmmDataCnfCauseMap
Description    : 把LMM Data Cnf结果转换为TAF与LCS之间的原因值
Input          : enCause----------------LMM Data Cnf原因值
Output         : NULL
Return Value   : TAF_LCS_CAUSE_ENUM_UINT32: 转换后原因值

History        :
leixiantiao 00258641 2015-10-08  新开发
*****************************************************************************/
TAF_LCS_CAUSE_ENUM_UINT32 NAS_LCS_LmmDataCnfCauseMap(const LMM_LCS_SEND_RSLT_ENUM_UINT32 enCause)
{
    TAF_LCS_CAUSE_ENUM_UINT32 enTafCause = TAF_LCS_CAUSE_SUCCESS;

    switch(enCause)
    {
        case LMM_LCS_SEND_RSLT_SUCCESS:
            enTafCause = TAF_LCS_CAUSE_SUCCESS;
            break;

        case LMM_LCS_SEND_RSLT_FAIL_PS_NOT_ATTACHED:
            enTafCause = TAF_LCS_CAUSE_LMM_PS_NOT_ATTACHED;
            break;

        case LMM_LCS_SEND_RSLT_FAIL_PS_ATTACH_NOT_ALLOWED:
            enTafCause = TAF_LCS_CAUSE_LMM_PS_ATTACH_NOT_ALLOWED;
            break;

        case LMM_LCS_SEND_RSLT_FAIL_USIM_PS_INVALID:
            enTafCause = TAF_LCS_CAUSE_LMM_USIM_PS_INVAILD;
            break;

        case LMM_LCS_SEND_RSLT_FAIL_ACCESS_BARRED:
            enTafCause = TAF_LCS_CAUSE_LMM_ACCESS_BARRED;
            break;

        case LMM_LCS_SEND_RSLT_FAIL_RRC_CONN_NOT_EXIST:
            enTafCause = TAF_LCS_CAUSE_LMM_RRC_CONN_NOT_EXIST;
            break;

        case LMM_LCS_SEND_RSLT_FAIL_EPC_LCS_NOT_SUPPORT:
            enTafCause = TAF_LCS_CAUSE_LMM_EPC_LCS_NOT_SUPPORT;
            break;

        case LMM_LCS_SEND_RSLT_RSLT_FAIL_3411_RUNNING:
            enTafCause = TAF_LCS_CAUSE_LMM_3411_RUNNING;
            break;

        case LMM_LCS_SEND_RSLT_FAIL_LOW_LAYER:
            enTafCause = TAF_LCS_CAUSE_LMM_LOW_LAYER;
            break;

        default:
            enTafCause = TAF_LCS_CAUSE_LMM_OTHERS;
            break;
    }
    return enTafCause;
}

/*****************************************************************************
Function Name  : NAS_LCS_LmmRelCauseMap
Description    : 把LMM Rel原因值转换为TAF与LCS之间的原因值
Input          : enCause----------------LMM REl原因值
Output         : NULL
Return Value   : TAF_LCS_CAUSE_ENUM_UINT32: 转换后原因值

History        :
leixiantiao 00258641 2015-10-08  新开发
*****************************************************************************/
TAF_LCS_CAUSE_ENUM_UINT32 NAS_LCS_LmmRelCauseMap(const LMM_LCS_REL_CAUSE_ENUM_UINT32 enCause)
{
    TAF_LCS_CAUSE_ENUM_UINT32 enTafCause;

    if (LMM_LCS_REL_CAUSE_USER_INACTIVITY == enCause)
    {
        enTafCause = TAF_LCS_CAUSE_LMM_USER_INACTIVITY;
    }
    else
    {
        enTafCause = TAF_LCS_CAUSE_LMM_OTHERS;
    }
    return enTafCause;
}

/*****************************************************************************
Function Name  : NAS_LCS_CheckLcsOperationCode
Description    : 确认Operation是否是LCS的Operation
Input          : enOperaCode----------------需确认的Operation
Output         : NULL
Return Value   : 结果,0:该Operation是LCS的Operation
1:该Operation不是LCS的Operation

History        :
leixiantiao 00258641 2015-10-08  新开发
*****************************************************************************/
VOS_UINT32 NAS_LCS_CheckLcsOperationCode(NAS_LCS_OPERATION_TYPE_UINT32 enOperaCode)
{
    VOS_UINT32                          ulRslt = NAS_LCS_FAIL;

    switch(enOperaCode)
    {
        case NAS_LCS_OPERATION_MO_LR:
        case NAS_LCS_OPERATION_LOC_NOTIFICATION:
        case NAS_LCS_OPERATION_AREA_EVENT_REQUEST:
        case NAS_LCS_OPERATION_AREA_EVENT_REPORT:
        case NAS_LCS_OPERATION_AREA_EVENT_CACELLATION:
        case NAS_LCS_OPERATION_PERIODIDC_LOCATION_REQUEST:
        case NAS_LCS_OPERATION_LOCATION_UPDATE:
        case NAS_LCS_OPERATION_PERIODIDC_LOCATION_CACELLATION:
            ulRslt = NAS_LCS_SUCC;
            break;

        default:
            ulRslt = NAS_LCS_FAIL;
    }
    return ulRslt;
}
#endif
/*****************************************************************************
Function Name  : NAS_LCS_JudgeLcsNwMsg
Description    : 判断空口消息是否为LCS空口,用于当MM模块收到空口消息为PD为0xB时
                 判断是否该空口消息为LCS空口消息
Input          : pucMsg----------------空口消息码流
                 ulMsgLen--------------空口消息码流长度
Output         : NULL
Return Value   : 结果,LCS_MM_NOT_LCS_NW_MSG:该空口消息不是LCS空口消息
LCS_MM_LCS_NW_MSG    :该空口消息时LCS空口消息

History        :
leixiantiao 00258641 2015-10-08  新开发
*****************************************************************************/
VOS_UINT32 NAS_LCS_IsLcsNwMsg(VOS_UINT8 *pucMsg, VOS_UINT32 ulMsgLen)
{
    #if (FEATURE_LPP == FEATURE_ON)
    VOS_UINT8                           ucTi;
    VOS_UINT8                           ucSum         = 0;
    NAS_LCS_CN_MSG_TYPE_ENUM_UINT32     enCnMsgType;
    NAS_LCS_OPERATION_TYPE_UINT32       enOperaCode   = 0;
    VOS_UINT32                          ulUndecodeLen = ulMsgLen;
    VOS_UINT32                          ulIndex       = 0;

    if (NAS_LCS_NULL_PTR == pucMsg)
    {
        return LCS_MM_NOT_LCS_NW_MSG;
    }

    if (NAS_LCS_MSG_MIN_LEN > ulUndecodeLen)
    {
        return LCS_MM_NOT_LCS_NW_MSG;
    }

    /* 获取保存transaction identifier */
    ucTi = pucMsg[ucSum++] >> NAS_LCS_MOVEMENT_4_BITS;

    /* 获取Msg Type */
    enCnMsgType = pucMsg[ucSum++];

    ulUndecodeLen = ulUndecodeLen - ucSum;

    if ((NAS_LCS_CN_MSG_REL_CML == enCnMsgType)
        || (NAS_LCS_CN_MSG_FACILITY == enCnMsgType))
    {
        if (NAS_LCS_SUCC != NAS_LCS_QueryLcsEntity(ucTi, &ulIndex))
        {
            return LCS_MM_NOT_LCS_NW_MSG;
        }
    }
    else if(NAS_LCS_CN_MSG_REGISTER == enCnMsgType)
    {
        enOperaCode = NAS_LCS_GetRegisterOperaCode(&pucMsg[ucSum], ulUndecodeLen);

        if (NAS_LCS_SUCC != NAS_LCS_CheckLcsOperationCode(enOperaCode))
        {
            return LCS_MM_NOT_LCS_NW_MSG;
        }
    }
    else
    {
        return LCS_MM_NOT_LCS_NW_MSG;
    }
    return LCS_MM_LCS_NW_MSG;

    #else
    return LCS_MM_NOT_LCS_NW_MSG;
    #endif

}

/*****************************************************************************
 Function Name   : NAS_LCS_SecuMemCpy
 Description     : 安全memcpy
 Input           : VOS_VOID* pDst, VOS_UINT32 ulMaxBuffer, const VOS_VOID* pSrc,
                   VOS_UINT32  ulLength, VOS_UINT32 ulLineNO, VOS_UINT32 ulFileID
 Output          : None
 Return          : VOS_INT32

 History         :
    1.z00297373    2015-12-28  Draft Enact
*****************************************************************************/
VOS_INT32 NAS_LCS_SecuMemCpy
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

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
