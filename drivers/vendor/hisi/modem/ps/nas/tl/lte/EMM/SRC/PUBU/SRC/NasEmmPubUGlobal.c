/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEmmPubUGlobal.c
    Description :
    History     :
      1.  hanlufeng 41410  Draft Enact
      2.  hanlufeng 41410  2009-03-11  BA8D01164 增加对EMM INFO处理的接口
      3.  leili 00132387   2010-08-04  DTS2010072301741
******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "msp.h"
#include    "NasEmmPubUInclude.h"
#include    "LRrcLPhyInterface.h"
#include    "LPsOm.h"
#include    "EmmUeModeInterface.h"
#include    "SysNvId.h"
#include    "NVIM_Interface.h"
#include    "NasEmmSecuSmc.h"
#include    "NasNvInterface.h"
#include    "msp_nvim.h"
#include    "ScInterface.h"
#include    "NasCommSndOm.h"
#include    "NasMmlCtx.h"

#if (FEATURE_LPP == FEATURE_ON)
#include    "NasEmmSsMsgProc.h"
#endif

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMPUBUGLOBAL_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMPUBUGLOBAL_C
/*lint +e767*/


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

/*VOS_UINT32                              g_ulRatMode = 2;*/    /* PS_FIRST_CALL 使用 */
NAS_EMM_PUB_INFO_STRU                   g_stEmmInfo;
VOS_UINT32                              g_ulSmcControl      = NAS_EMM_SMC_CLOSE;
VOS_UINT32                              g_ulUeSecuCapMatch  = NAS_EMM_SMC_OPEN;
VOS_UINT32                              g_ulEmmT3402length  = 720000;

VOS_UINT32                              g_ulEmmTauReqSndFailFlag = PS_FALSE;
/*
VOS_UINT32                              g_ulDetachPowerOff  = NAS_EMM_DO_DETACH_WHEN_POWEROFF;
*/
/*VOS_UINT32                              g_ulAutoStartFlag   = NOT_AUTO_START;*/
VOS_UINT32                              g_ulAutoAttFlag     = NAS_EMM_AUTO_ATTACH_ALLOW;
VOS_UINT32                              g_ulCsAutoAttFlag   = NAS_EMM_AUTO_ATTACH_ALLOW;
NAS_LMM_SYSINFO_COUNT_STRU               g_stMsgSysInfCnt;

OM_EMM_STATE_INFO_STRU                   g_stEmmOmInfo;

#if (FEATURE_ON == FEATURE_DSDS)
NAS_LMM_SESSION_TYPE_MAP_STRU g_astDsdsCvtSessionTypeTbl[]=
{
    {WUEPS_PID_MMC,   MMC_LMM_SESSION_TYPE_CS_MO_NORMAL_CALL,        LRRC_LNAS_SESSION_TYPE_MO_NORMAL_CALL},
    {WUEPS_PID_MMC,   MMC_LMM_SESSION_TYPE_CS_MO_EMERGENCY_CALL,     LRRC_LNAS_SESSION_TYPE_MO_EMERGENCY_CALL},
    {WUEPS_PID_MMC,   MMC_LMM_SESSION_TYPE_CS_MO_SS,                 LRRC_LNAS_SESSION_TYPE_MO_SS},
    {WUEPS_PID_MMC,   MMC_LMM_SESSION_TYPE_CS_MO_SMS,                LRRC_LNAS_SESSION_TYPE_MO_SMS},
    {WUEPS_PID_MMC,   MMC_LMM_SESSION_TYPE_PS_CONVERSAT_CALL,        LRRC_LNAS_SESSION_TYPE_PS_CONVERSAT_CALL},
    {WUEPS_PID_MMC,   MMC_LMM_SESSION_TYPE_PS_STREAM_CALL,           LRRC_LNAS_SESSION_TYPE_PS_STREAM_CALL},
    {WUEPS_PID_MMC,   MMC_LMM_SESSION_TYPE_PS_INTERACT_CALL,         LRRC_LNAS_SESSION_TYPE_PS_INTERACT_CALL},
    {WUEPS_PID_MMC,   MMC_LMM_SESSION_TYPE_PS_BACKGROUND_CALL,       LRRC_LNAS_SESSION_TYPE_PS_BACKGROUND_CALL},
    {WUEPS_PID_MMC,   MMC_LMM_SESSION_TYPE_PS_SUBSCRIB_TRAFFIC_CALL, LRRC_LNAS_SESSION_TYPE_PS_SUBSCRIB_TRAFFIC_CALL},

    {WUEPS_PID_MM,    MM_LMM_SESSION_TYPE_MO_NORMAL_CALL,            LRRC_LNAS_SESSION_TYPE_MO_NORMAL_CALL},
    {WUEPS_PID_MM,    MM_LMM_SESSION_TYPE_MO_EMERGENCY_CALL,         LRRC_LNAS_SESSION_TYPE_MO_EMERGENCY_CALL},
    {WUEPS_PID_MM,    MM_LMM_SESSION_TYPE_MO_SS,                     LRRC_LNAS_SESSION_TYPE_MO_SS},
    {WUEPS_PID_MM,    MM_LMM_SESSION_TYPE_MO_SMS,                    LRRC_LNAS_SESSION_TYPE_MO_SMS},
    {WUEPS_PID_MM,    MM_LMM_SESSION_TYPE_MT_NORMAL_CALL,            LRRC_LNAS_SESSION_TYPE_MT_NORMAL_CALL},
    {WUEPS_PID_MM,    MM_LMM_SESSION_TYPE_MT_SMS,                    LRRC_LNAS_SESSION_TYPE_MT_SMS},
    {WUEPS_PID_MM,    MM_LMM_SESSION_TYPE_MT_SS,                     LRRC_LNAS_SESSION_TYPE_MT_SS},
    {WUEPS_PID_MM,    MM_LMM_SESSION_TYPE_MO_NORMAL_CSFB,            LRRC_LNAS_SESSION_TYPE_MO_NORMAL_CSFB},
    {WUEPS_PID_MM,    MM_LMM_SESSION_TYPE_MO_EMERGENCY_CSFB,         LRRC_LNAS_SESSION_TYPE_MO_EMERGENCY_CSFB},
    {WUEPS_PID_MM,    MM_LMM_SESSION_TYPE_MT_CSFB,                   LRRC_LNAS_SESSION_TYPE_MT_CSFB},

    {WUEPS_PID_GMM,   GMM_LMM_SESSION_TYPE_MO_SMS,                   LRRC_LNAS_SESSION_TYPE_MO_SMS},
    {WUEPS_PID_GMM,   GMM_LMM_SESSION_TYPE_MT_SMS,                   LRRC_LNAS_SESSION_TYPE_MT_SMS},

    {PS_PID_ESM,      EMM_ESM_SESSION_TYPE_ESM,                      LRRC_LNAS_SESSION_TYPE_PS_ESM}
};

VOS_UINT32 g_astDsdsCvtSessionTypeTblLen = sizeof(g_astDsdsCvtSessionTypeTbl)
                                                                /sizeof(NAS_LMM_SESSION_TYPE_MAP_STRU);

/*统计输出的消息个数*/
NAS_LMM_DSDS_MSG_COUNT_STRU  g_astDsdsNotifyMsgNum[LRRC_LNAS_SESSION_TYPE_BUTT];

/*统计输入的消息个数*/
NAS_LMM_DSDS_MSG_COUNT_STRU  g_astDsdsInputNotifyMsgNum[NAS_EMM_INPUT_DSDS_MSG_NUM];

/*DSDS特性，RF共享开关，vc环境默认关闭*/
#if (VOS_OS_VER != VOS_WIN32)
VOS_UINT32 g_ulDsdsRFSharedFlag = PS_TRUE;
#else
VOS_UINT32 g_ulDsdsRFSharedFlag = PS_FALSE;
#endif

#endif

VOS_UINT32  g_ulCsfbProcedureFlag = PS_FALSE;

LNAS_LMM_LTE_NO_SUBSCRIBE_CONFIG_STRU    stLteNoSubscribeConfig;
/* 可维可测上报控制开关 */
LNAS_NV_OM_SWITCH_STRU g_stNasOmSwitch;
VOS_UINT32  g_aulNasFunFlg[8];

VOS_UINT32                       g_ulPtmsiTauActiveFlag = PS_FALSE;

/* 渐进被禁优化控制 */
VOS_UINT8                               g_ucLmmGradualForbFlag        = PS_FALSE;
NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST  g_stGradualForbTempForbTaList;
VOS_UINT32                              g_ulGradualForbTimerFirstLen  = 300 * 1000;
VOS_UINT32                              g_ulGradualForbTimerSecondLen = 1200 * 1000;
VOS_UINT32                              g_ulGradualForbAgingTimerLen  = 7200 * 1000;
VOS_UINT32                              g_ulGradualForbTaTimerPara    = 0;


/*****************************************************************************
  3 Function
*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
/*****************************************************************************
 Function Name   : NAS_LMM_EmmStateInit
 Description     : 初始化EMM的状态机的NULL状态
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2009-4-14  Draft Enact

*****************************************************************************/

VOS_VOID    NAS_LMM_EmmStateInit( VOS_VOID )
{

    NAS_LMM_FSM_STATE_STRU              *pEmmCurState;

    /* 当前状态初始化 */
    pEmmCurState = NAS_LMM_GetCurFsmAddr(NAS_LMM_PARALLEL_FSM_EMM);
    pEmmCurState->enFsmId               = NAS_LMM_PARALLEL_FSM_EMM;
    pEmmCurState->enMainState           = EMM_MS_NULL;
    pEmmCurState->enSubState            = EMM_SS_NULL_WAIT_APP_START_REQ;
    pEmmCurState->enStaTId              = TI_NAS_EMM_STATE_NO_TIMER;

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_FsmInit
 Description     : g_stMmMainContext 中的EMM状态机 初始化
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h41410      2008-10-23  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_EMM_FsmInit(            VOS_VOID )
{

    NAS_LMM_FSM_STATE_STRU              *pEmmCurState;
    NAS_LMM_FSM_STATE_STACK_STRU        *pEmmStack;

    NAS_LMM_PUBM_LOG_NORM(
    "NAS_EMM_FsmInit                   START INIT...");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_FsmInit_ENUM,LNAS_BEGIN);

    /* 当前状态初始化 */
    pEmmCurState = NAS_LMM_GetCurFsmAddr(NAS_LMM_PARALLEL_FSM_EMM);
    pEmmCurState->enFsmId               = NAS_LMM_PARALLEL_FSM_EMM;
    pEmmCurState->enMainState           = EMM_MS_NULL;
    pEmmCurState->enSubState            = EMM_SS_NULL_WAIT_APP_START_REQ;
    pEmmCurState->enStaTId              = TI_NAS_EMM_STATE_NO_TIMER;


    /* 状态机栈 初始化 */
    pEmmStack   = NAS_LMM_GetFsmStackAddr(NAS_LMM_PARALLEL_FSM_EMM);
    pEmmStack->ucStackDepth             = NAS_EMM_STACK_EMPTY;

    NAS_EMM_InitBufMsgQue();

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_PubmInfoUeIdInit
 Description     : EMM 全局信息初始化中的stMmUeId初始化
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h41410      2008-10-27  Draft Enact
    2.z00148421   2009.04.17  Modify
*****************************************************************************/
VOS_VOID    NAS_EMM_PubmInfoUeIdInit(   VOS_VOID )
{
    /*IMSI,IMEI必须有，所以初始化UeId有效*/
    NAS_LMM_GetEmmInfoAddr()->bitOpUeId  = NAS_EMM_BIT_SLCT;

    NAS_LMM_GetEmmInfoUeidAddr()->bitOpTmsi     = NAS_EMM_BIT_NO_SLCT;
    NAS_LMM_GetEmmInfoUeidAddr()->bitOpPtmsi    = NAS_EMM_BIT_NO_SLCT;
    NAS_LMM_GetEmmInfoUeidAddr()->bitOpTmgiMbms = NAS_EMM_BIT_NO_SLCT;
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_PubmInfoNetInfoInit
 Description     : EMM 全局信息初始化中的stNetInfo初始化
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h41410      2008-10-27  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_EMM_PubmInfoNetInfoInit(VOS_VOID )
{
    /*初始网络信息有效*/
    NAS_LMM_GetEmmInfoAddr()->bitOpNetInfo = NAS_EMM_BIT_SLCT;

    /*如果IMSI有效，即卡有效，设置HPLMN有效，MMC初始化时计算赋值*/
    if (NAS_EMM_BIT_SLCT == NAS_LMM_GetEmmInfoUeidAddr()->bitOpImsi)
    {
        NAS_LMM_GetEmmInfoNetInfoAddr()->bitOpHplmn = NAS_EMM_BIT_SLCT;
    }

    /*未开机，当前网络信息无效*/
    NAS_LMM_GetEmmInfoNetInfoAddr()->bitOpPresentNetId = NAS_EMM_BIT_NO_SLCT;
    NAS_LMM_UndefPlmn(NAS_LMM_GetEmmInfoPresentPlmnAddr());

    /*未开机，上次尝试发起注册的TA信息无效*/
    NAS_LMM_GetEmmInfoNetInfoAddr()->bitOpLastAttmpRegTa = NAS_EMM_BIT_NO_SLCT;
    NAS_LMM_UndefPlmn(NAS_LMM_GetEmmInfoLastAttmpRegPlmnAddr());
    NAS_LMM_UndefCsgId(&(NAS_LMM_GetEmmInfoNetInfoLastAttmpRegCsgInfoAddr()->ulCsgId));


    /* 将当前网络信息中TAC及Cell ID初始化为无效值*/
    NAS_EMMC_DeleteCurrentAreaCellId();
    NAS_LMM_UndefTac(&(NAS_LMM_GetEmmInfoNetInfoPresentNetAddr()->stTac));
    NAS_LMM_UndefCsgId(&(NAS_LMM_GetEmmInfoNetInfoPresentNetAddr()->ulCsgId));

    /*ForbTaList For Roaming关机时擦除,上电无效*/
    /*ForbTaList For Rpos关机时擦除,上电无效*/
    NAS_LMM_GetEmmInfoNetInfoAddr()->bitOpFoibTaForRoam = NAS_EMM_BIT_NO_SLCT;
    NAS_LMM_GetEmmInfoNetInfoAddr()->bitOpFoibTaForRpos = NAS_EMM_BIT_NO_SLCT;

    NAS_LMM_GetEmmInfoNetInfoForbTaForRoamAddr()->ulTaNum = 0;
    NAS_LMM_GetEmmInfoNetInfoForbTaForRposAddr()->ulTaNum = 0;

    /*EHPLMN List目前未使用,初始化无效*/
    NAS_LMM_GetEmmInfoNetInfoAddr()->bitOpEHplmnList = NAS_EMM_BIT_NO_SLCT;


    /*L.V.R TAI初始化*/
    NAS_EMM_ClearLVRTai();

    return;
}


VOS_VOID  NAS_EMM_PubmInfoDrxInit(VOS_VOID)
{
    /*PC REPLAY DEL BY LEILI */

    /*设置DRX改变标识*/
    NAS_LMM_SetEmmInfoDrxNetCapChange(NAS_EMM_NO);
    NAS_EMM_SetDrxCycleLenChangeFlag(NAS_EMM_DRX_CYCLE_LEN_CHANGED);

    return;
}

VOS_UINT32  NAS_EMM_IsGuContainPsRegDrx(VOS_VOID)
{
    NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_IsGuContainPsRegDrx:NAS_MML_GetPsRegContainDrx =",
                           NAS_MML_GetPsRegContainDrx());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_IsGuContainPsRegDrx_ENUM,LNAS_FUNCTION_LABEL1,NAS_MML_GetPsRegContainDrx());
    #ifndef __PS_WIN32_RECUR__
    if (NAS_MML_GU_PS_REG_CONTAIN_DRX_PARA == NAS_MML_GetPsRegContainDrx())
    {
       NAS_LMM_LogPsRegContainDrxInfo(NAS_MML_GetPsRegContainDrx());
       return NAS_EMM_SUCC;
    }
    NAS_LMM_LogPsRegContainDrxInfo(NAS_MML_GetPsRegContainDrx());
    return NAS_EMM_FAIL;
    #else
    if (NAS_MML_GU_PS_REG_CONTAIN_DRX_PARA == Stub_NAS_MML_GetPsRegContainDrx())
    {
        return NAS_EMM_SUCC;
    }
    return NAS_EMM_FAIL;
    #endif
}

VOS_VOID  NAS_EMM_UpdateLteContainDrxFlag( VOS_VOID )
{
    NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_UpdateLteContainDrxFlag before:NAS_MML_GetPsRegContainDrx() = ",
                               NAS_MML_GetPsRegContainDrx());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_UpdateLteContainDrxFlag_ENUM,LNAS_FUNCTION_LABEL1,NAS_MML_GetPsRegContainDrx());
    if (NAS_EMM_YES == NAS_EMM_TAU_GetEmmTauContainDrxFlag())
    {
        NAS_MML_SetPsRegContainDrx(NAS_MML_LTE_PS_REG_CONTAIN_DRX_PARA);
    }
    else
    {
        NAS_MML_SetPsRegContainDrx(NAS_MML_LTE_PS_REG_NOT_CONTAIN_DRX_PARA);
    }
    NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_UpdateLteContainDrxFlag After:NAS_MML_GetPsRegContainDrx() = ",
                               NAS_MML_GetPsRegContainDrx());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_UpdateLteContainDrxFlag_ENUM,LNAS_FUNCTION_LABEL2,NAS_MML_GetPsRegContainDrx());
    return;
}









/*****************************************************************************
 Function Name   : NAS_EMM_ReadNvUeNetCap
 Description     : 从NVIM中读取 UE network capability
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h41410      2009-1-7  Draft Enact
    2.zhengjunyan 00148421 2011-06-03 MOD:缺省值修改为0xE0 0xE0 0x40 0x40,
                                     支持从NVIM中读取，暂未实现与接入技术对应的验证
    3.sunjitan 00193151  2012-05-05  DTS2012041105089  增加将UeNetCap写入MML
*****************************************************************************/
VOS_VOID    NAS_EMM_ReadNvUeNetCap(VOS_VOID)
{
    LNAS_LMM_NV_UE_NET_CAP_STRU         stNvUeNetCap;
    NAS_MM_UE_NET_CAP_STRU             *pstUeNetCap = VOS_NULL_PTR;
    NAS_EMM_PUB_INFO_STRU              *pstEmmInfo  = VOS_NULL_PTR;
    VOS_VOID                           *pData = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    VOS_UINT16                          usDataLen;
    /* leixiantiao 2014-10-23 begin */
    #if (VOS_OS_VER != VOS_WIN32)
    FTM_TMODE_ENUM                      enMspFtmMode = EN_FTM_TMODE_SIGNAL ;
    #endif
    /* leixiantiao 2014-10-23 end */
    NAS_MML_UE_NETWORK_CAPABILITY_STRU  stUeNetworkCapbility = {0};

    /* 指向 UeNetCap*/
    pstEmmInfo  = NAS_LMM_GetEmmInfoAddr();
    pstUeNetCap = NAS_LMM_GetEmmInfoSecuParaUeNetCapAddr();

    /* 初始化写入MML的UeNetCap为默认值 */
    /*stUeNetworkCapbility.bitOpUeNetCap      = NAS_EMM_BIT_SLCT;*/
    stUeNetworkCapbility.ucUeNetCapLen      = 0x05;

    stUeNetworkCapbility.aucUeNetCap[0]     = 0xF0;
    stUeNetworkCapbility.aucUeNetCap[1]     = 0xF0;
    stUeNetworkCapbility.aucUeNetCap[2]     = 0x40;
    stUeNetworkCapbility.aucUeNetCap[3]     = 0x40;
    stUeNetworkCapbility.aucUeNetCap[4]     = 0x0;

    /* 初始化本地全局变量UeNetCap为默认值 */
    pstEmmInfo->bitOpUeNetCap       = NAS_EMM_BIT_SLCT;
    pstUeNetCap->ucUeNetCapLen      = 0x05;

    pstUeNetCap->aucUeNetCap[0]     = 0xF0;
    pstUeNetCap->aucUeNetCap[1]     = 0xF0;

    pstUeNetCap->aucUeNetCap[2]     = 0x40;
    pstUeNetCap->aucUeNetCap[3]     = 0x40;
    pstUeNetCap->aucUeNetCap[4]     = 0x0;

#if (VOS_OS_VER != VOS_WIN32)
    /*如果获取当前模式失败，则默认为当前模式为EN_FTM_TMODE_SIGNAL，打印错误信息*/
    if(LPS_OM_GetTmode(&enMspFtmMode)!= ERR_MSP_SUCCESS)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_EMM_ReadNvUeNetCap : FTM_GetMode() called fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_ReadNvUeNetCap_ENUM,LNAS_FAIL);
    }
    else
    {
        /*产线测试模式，则取默认值:0xE0,0xE0,0x40,0x40*/
        if( EN_FTM_TMODE_SIGNAL_NOCARD == enMspFtmMode)
        {
            NAS_LMM_PUBM_LOG_INFO("NAS_EMM_ReadNvUeNetCap : EN_FTM_TMODE_SIGNAL_NOCARD, UE NetCap is 0xe0,0xe0!");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ReadNvUeNetCap_ENUM,LNAS_FUNCTION_LABEL1);

            /* 将默认值写入MML */
            NAS_MML_SetUeNetWorkCapability(&stUeNetworkCapbility);

            return;
        }
    }
#endif
    /*read UE NET CAP from NVIM*/
    pData = (VOS_VOID *)&(stNvUeNetCap);
    usDataLen = sizeof(LNAS_LMM_NV_UE_NET_CAP_STRU);

    ulRslt = NAS_LMM_NvimRead(EN_NV_ID_UE_NET_CAPABILITY, pData, &usDataLen);

    /* 读取 NVIM成功 */
    if((NAS_LMM_NVIM_OK == ulRslt) && (NAS_EMM_BIT_SLCT == stNvUeNetCap.bitOpUeNetCap))
    {
        /*验证读取数据的有效性:目前阶段只验证长度符合协议。
          后续实现还需要考虑EEA,EIA,UEA,UIA的取值，与开机支持的接入技术是否符合，
          例如开机指示支持L和U，如果读取的UEA,UIA不支持任何算法，则认为数据无效，
          与接入模式的验证，目前阶段暂未实现
        */
        if ((NAS_MM_MIN_UE_NET_CAP_LEN <= stNvUeNetCap.stUeNetCap.ucUeNetCapLen)
            && (NAS_MM_MAX_UE_NET_CAP_LEN >= stNvUeNetCap.stUeNetCap.ucUeNetCapLen))
        {
            NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ReadNvUeNetCap:NV value is Valid");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ReadNvUeNetCap_ENUM,LNAS_FUNCTION_LABEL2);

            #if (VOS_OS_VER != VOS_WIN32)
            #if (FEATURE_LPP == FEATURE_OFF)

            /* 当LPP宏没有打开且UE网络能力中携带LPP和LCS能力时需要把UE网络能力需要设置为不支持LCS和LPP */
            if (5 <= stNvUeNetCap.stUeNetCap.ucUeNetCapLen)
            {
                stNvUeNetCap.stUeNetCap.aucUeNetCap[4] &= NAS_EMM_UENETCAP_WITHOUT_LCS;
                stNvUeNetCap.stUeNetCap.aucUeNetCap[4] &= NAS_EMM_UENETCAP_WITHOUT_LPP;
            }
            #endif
            #endif

            pstEmmInfo->bitOpUeNetCap           = NAS_EMM_BIT_SLCT;
            NAS_LMM_MEM_CPY_S(  pstUeNetCap,
                                sizeof(NAS_MM_UE_NET_CAP_STRU),
                                &(stNvUeNetCap.stUeNetCap),
                                sizeof(NAS_MM_UE_NET_CAP_STRU));

            /* 设置写入MML的UeNetCap为NV中读取出的值 */
            NAS_LMM_MEM_SET_S(  &stUeNetworkCapbility,
                                sizeof(NAS_MML_UE_NETWORK_CAPABILITY_STRU),
                                0,
                                sizeof(NAS_MML_UE_NETWORK_CAPABILITY_STRU));

            stUeNetworkCapbility.ucUeNetCapLen = stNvUeNetCap.stUeNetCap.ucUeNetCapLen;
            NAS_LMM_MEM_CPY_S(  &(stUeNetworkCapbility.aucUeNetCap[0]),
                                NAS_MML_MAX_UE_NETWORK_CAPABILITY_LEN,
                                &(stNvUeNetCap.stUeNetCap.aucUeNetCap[0]),
                                stUeNetworkCapbility.ucUeNetCapLen);
        }
        /* NVIM中读取的数据无效，则赋为默认值*/
        else
        {
            NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ReadNvUeNetCap:Nv value is Invalid");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ReadNvUeNetCap_ENUM,LNAS_FUNCTION_LABEL3);
        }
    }
    /* 读取 NVIM 失败，赋为默认值*/
    else
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_EMM_ReadNvUeNetCap:Read Net Cap Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_ReadNvUeNetCap_ENUM,LNAS_FUNCTION_LABEL4);
    }

    /* 如果UeNetCap读取成功，将读NV得到的值写入MML；如果失败，写入默认值 */
    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ReadNvUeNetCap: Set to MML UeNetCap value is:");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ReadNvUeNetCap_ENUM,LNAS_FUNCTION_LABEL5);
    NAS_MML_SetUeNetWorkCapability(&stUeNetworkCapbility);

    NAS_COMM_PrintArray(    NAS_COMM_GET_MM_PRINT_BUF(),
                            (VOS_UINT8*)&stUeNetworkCapbility,
                            sizeof(NAS_MML_UE_NETWORK_CAPABILITY_STRU));

    return;
}



/*****************************************************************************
 Function Name   : NAS_EMM_ReadNvVoiceDomain
 Description     : 从NV项读取voice domain for E-UTRAN
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-6-29  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_ReadNvVoiceDomain(VOS_VOID )
{
    NAS_EMM_PUB_INFO_STRU              *pstPubInfo;
#if (FEATURE_ON == FEATURE_IMS)
    LNAS_LMM_NV_VOICE_DOMAIN_STRU       stNvVoiceDomain;
    VOS_VOID                           *pData = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    VOS_UINT16                          usDataLen;
#endif
    pstPubInfo = NAS_LMM_GetEmmInfoAddr();
    pstPubInfo->bitOpVoiceDomain      = NAS_EMM_BIT_SLCT;
    pstPubInfo->ulVoiceDomain         = NAS_LMM_VOICE_DOMAIN_CS_ONLY;
    NAS_MML_SetVoiceDomainPreference(NAS_LMM_VOICE_DOMAIN_CS_ONLY);
#if (FEATURE_ON == FEATURE_IMS)
    pData                               = (VOS_VOID *)&(stNvVoiceDomain);
    usDataLen = sizeof(LNAS_LMM_NV_VOICE_DOMAIN_STRU);

    ulRslt = NAS_LMM_NvimRead(          EN_NV_ID_UE_VOICE_DOMAIN,
                                        pData,
                                        &usDataLen);

    /*sunbing 49683 2013-10-28 VoLTE begin*/
    if((EN_NV_OK == ulRslt) && (stNvVoiceDomain.bitOpVoicDomain == NAS_EMM_BIT_SLCT))
    {
        NAS_LMM_PUBM_LOG1_NORM("NAS_EMM_ReadNvVoiceDomain: read NV success.",
            stNvVoiceDomain.enVoicDomain);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ReadNvVoiceDomain_ENUM,LNAS_EMM_VOICE_DOMAIN,stNvVoiceDomain.enVoicDomain);

        if (NAS_LMM_VOICE_DOMAIN_IMS_PS_PREFERRED >= stNvVoiceDomain.enVoicDomain)
        {
            pstPubInfo->bitOpVoiceDomain = NAS_EMM_BIT_SLCT;
            pstPubInfo->ulVoiceDomain = stNvVoiceDomain.enVoicDomain;

            NAS_MML_SetVoiceDomainPreference((VOS_UINT8)pstPubInfo->ulVoiceDomain);

        }
        else
        {
            NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ReadNvVoiceDomain:NV Value is Invalid");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ReadNvVoiceDomain_ENUM,LNAS_PARAM_INVALID);
            pstPubInfo->bitOpVoiceDomain  = NAS_EMM_BIT_SLCT;
            pstPubInfo->ulVoiceDomain     = NAS_LMM_VOICE_DOMAIN_IMS_PS_PREFERRED;

            NAS_MML_SetVoiceDomainPreference(NAS_LMM_VOICE_DOMAIN_IMS_PS_PREFERRED);

        }
    }
    else
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ReadNvVoiceDomain: read NV err.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ReadNvVoiceDomain_ENUM,LNAS_ERROR);
        pstPubInfo->bitOpVoiceDomain      = NAS_EMM_BIT_SLCT;
        pstPubInfo->ulVoiceDomain         = NAS_LMM_VOICE_DOMAIN_IMS_PS_PREFERRED;

        NAS_MML_SetVoiceDomainPreference(NAS_LMM_VOICE_DOMAIN_IMS_PS_PREFERRED);

    }
    /*sunbing 49683 2013-10-28 VoLTE end*/
#endif
    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_ReadNvNasRelease
 Description     : 从NV项读取NAS支持的版本
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2013-2-6  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_ReadNvNasRelease(VOS_VOID )
{
    LNAS_LMM_NV_NAS_RELEASE_STRU        stNvNasRelease;
    NAS_EMM_PUB_INFO_STRU              *pstPubInfo;
    VOS_VOID                           *pData = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    VOS_UINT16                          usDataLen;

    pstPubInfo = NAS_LMM_GetEmmInfoAddr();
    pData                               = (VOS_VOID *)&(stNvNasRelease);
    usDataLen = sizeof(LNAS_LMM_NV_NAS_RELEASE_STRU);

    ulRslt = NAS_LMM_NvimRead(          EN_NV_ID_NAS_RELEASE,
                                        pData,
                                        &usDataLen);

    if((EN_NV_OK == ulRslt)
        && (stNvNasRelease.bitOpReleaseName  == NAS_EMM_BIT_SLCT))
    {

        NAS_LMM_PUBM_LOG1_NORM("NAS_EMM_ReadNvNasRelease: read NV success.",
            stNvNasRelease.ulReleaseName);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ReadNvNasRelease_ENUM,LNAS_FUNCTION_LABEL1,
            stNvNasRelease.ulReleaseName);

        pstPubInfo->ulNasRelease = stNvNasRelease.ulReleaseName;
    }
    else
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ReadNvNasRelease: read NV err.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ReadNvNasRelease_ENUM,LNAS_ERROR);
        pstPubInfo->ulNasRelease        = 0x00000900;

    }

    return;
}

/*sunbing 49683 2013-10-21 VoLTE begin*/
/*****************************************************************************
 Function Name   : NAS_EMM_ReadNvUmtsCodecInfo
 Description     : 从NV项读取Umts codec支持信息
                   参考MN_CALL_FillUmtsSupCodecList,MN_CALL_UmtsCapaProcInit的实现
 Input           : None
 Output          : None
 Return          : None

 History         :
    1.sunbing 49683      2013-10-21  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_ReadNvUmtsCodecInfo(NAS_EMM_SUPPORT_CODEC_UNION *punCodecList)
{
    VOS_UINT8       aucNvCodecInfo[NAS_EMM_MAX_UMTS_CODEC_TYPE_NUM+1];/*codec个数+具体codec信息*/
    VOS_UINT32      ulDefaultValue;
    VOS_UINT32      i;
    VOS_UINT16      usDataLen;

    NAS_LMM_MEM_SET_S(  aucNvCodecInfo,
                        sizeof(aucNvCodecInfo),
                        0x00,
                        sizeof(aucNvCodecInfo));

    ulDefaultValue          = VOS_FALSE;

    usDataLen               = sizeof(aucNvCodecInfo);

    /*该项NV的结构的原始定义为MN_CALL_UMTS_CODEC_TYPE_STRU，codec个数+具体codec信息*/
    if ( NAS_LMM_NVIM_OK != NAS_LMM_NvimRead(en_NV_Item_UMTS_CODEC_TYPE,
                                   aucNvCodecInfo,
                                   &usDataLen))
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ReadNvUmtsCodecInfo: read NV err.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ReadNvUmtsCodecInfo_ENUM,LNAS_ERROR);
        ulDefaultValue = VOS_TRUE;
    }

    /* 检查NVIM中的参数是否合法,不合法则使用默认值,个数是否越界 */
    if ( aucNvCodecInfo[0] > NAS_EMM_MAX_UMTS_CODEC_TYPE_NUM )
    {
        ulDefaultValue     = VOS_TRUE;

        aucNvCodecInfo[0]  = NAS_EMM_MAX_UMTS_CODEC_TYPE_NUM;

        NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ReadNvUmtsCodecInfo: Codec num is err.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ReadNvUmtsCodecInfo_ENUM,LNAS_FUNCTION_LABEL1);

    }

    /* 检查是否有重复定义和超出范围的codec类型*/
    for ( i = 0; i < aucNvCodecInfo[0]; i++ )
    {
        switch ( aucNvCodecInfo[i+1])
        {
            case NAS_EMM_UMTS_CODEC_TYPE_AMR :
                punCodecList->stSupportCodec.CodecType_UMTSAMR     = VOS_TRUE;
                break;

            case NAS_EMM_UMTS_CODEC_TYPE_AMR2 :
                punCodecList->stSupportCodec.CodecType_UMTSAMR2     = VOS_TRUE;
                break;

            case NAS_EMM_UMTS_CODEC_TYPE_AMRWB :
                punCodecList->stSupportCodec.CodecType_UMTSAMRWB   = VOS_TRUE;
                break;

            default:
                NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ReadNvUmtsCodecInfo: Codec Type is err.");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_ReadNvUmtsCodecInfo_ENUM,LNAS_FUNCTION_LABEL2);
                ulDefaultValue = VOS_TRUE;
                break;
        }

        if(ulDefaultValue == VOS_TRUE)
        {
            /*NV内容错误，清空*/
            punCodecList->usSupportCodec = 0;
            break;
        }

    }

    if ( VOS_TRUE == ulDefaultValue )
    {
        punCodecList->stSupportCodec.CodecType_UMTSAMR     = VOS_TRUE;
        punCodecList->stSupportCodec.CodecType_UMTSAMR2    = VOS_TRUE;
    }

}

/*****************************************************************************
 Function Name   : NAS_EMM_ReadNvGsmCodecInfo
 Description     : 从NV项读取Gsm codec支持信息
                   参考MN_CALL_FillGsmSupCodecList,MN_CALL_GsmCapaProcInit的实现
 Input           : None
 Output          : None
 Return          : None

 History         :
    1.sunbing 49683      2013-10-21  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_ReadNvGsmCodecInfo(NAS_EMM_SUPPORT_CODEC_UNION *punCodecList)
{
    VOS_UINT8       aucNvGsmCodecInfo[NAS_EMM_BC_MAX_SPH_VER_NUM + 2] ;/*codec个数+具体codec信息+1个spare byte*/
    VOS_UINT32      ulDefaultValue;
    VOS_UINT32      i;
    VOS_UINT16      usDataLen;

    NAS_LMM_MEM_SET_S(  aucNvGsmCodecInfo,
                        sizeof(aucNvGsmCodecInfo),
                        0x00,
                        sizeof(aucNvGsmCodecInfo));

    ulDefaultValue          = VOS_FALSE;

    usDataLen               = sizeof(aucNvGsmCodecInfo);

    /*该项NV的结构的原始定义为MN_CALL_NIMV_ITEM_CODEC_TYPE_STRU，codec个数+具体codec信息*/
    if ( NAS_LMM_NVIM_OK != NAS_LMM_NvimRead(en_NV_Item_MED_CODEC_TYPE,
                         aucNvGsmCodecInfo,
                          &usDataLen))
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ReadNvGsmCodecInfo: read NV err.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ReadNvGsmCodecInfo_ENUM,LNAS_FUNCTION_LABEL1);
        ulDefaultValue = VOS_TRUE;
    }

    /* 检查NVIM中的参数是否合法,不合法则使用默认值,个数是否越界 */
    if ( aucNvGsmCodecInfo[0] > NAS_EMM_BC_MAX_SPH_VER_NUM )
    {
        ulDefaultValue = VOS_TRUE;

        aucNvGsmCodecInfo[0] = NAS_EMM_BC_MAX_SPH_VER_NUM;

        NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ReadNvGsmCodecInfo: Codec num is err.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ReadNvGsmCodecInfo_ENUM,LNAS_FUNCTION_LABEL2);
    }

    /* 检查是否有重复定义和超出范围的codec类型*/
    for ( i = 0; i < aucNvGsmCodecInfo[0] ; i++ )
    {
        switch ( aucNvGsmCodecInfo[i+1])
        {
            case NAS_EMM_BC_VAL_SPH_VER_FR_1 :
                punCodecList->stSupportCodec.CodecType_GSMFR        = VOS_TRUE;
                break;

            case NAS_EMM_BC_VAL_SPH_VER_FR_2 :
                punCodecList->stSupportCodec.CodecType_GSMEFR       = VOS_TRUE;
                break;

            case NAS_EMM_BC_VAL_SPH_VER_FR_3 :
                punCodecList->stSupportCodec.CodecType_GSMFRAMR     = VOS_TRUE;
                break;

            case NAS_EMM_BC_VAL_SPH_VER_HR_1 :
                punCodecList->stSupportCodec.CodecType_GSMHR        = VOS_TRUE;
                break;

            case NAS_EMM_BC_VAL_SPH_VER_HR_3 :
                punCodecList->stSupportCodec.CodecType_GSMHRAMR     = VOS_TRUE;
                break;

            case NAS_EMM_BC_VAL_SPH_VER_FR_5 :
                punCodecList->stSupportCodec.CodecType_GSMFRAMRWB   = VOS_TRUE;
                break;

            default:
                NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ReadNvGsmCodecInfo: Codec Type is err.");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_ReadNvGsmCodecInfo_ENUM,LNAS_FUNCTION_LABEL3);
                ulDefaultValue = VOS_TRUE;
                break;

        }

        if(ulDefaultValue == VOS_TRUE)
        {
            /*NV内容错误，清空*/
            punCodecList->usSupportCodec = 0;
            break;
        }
    }

    /* 此处表示需要使用默认值 */
    if ( VOS_TRUE == ulDefaultValue )
    {
        punCodecList->stSupportCodec.CodecType_GSMFR        = VOS_TRUE;
        punCodecList->stSupportCodec.CodecType_GSMEFR       = VOS_TRUE;
        punCodecList->stSupportCodec.CodecType_GSMFRAMR     = VOS_TRUE;
        punCodecList->stSupportCodec.CodecType_GSMHR        = VOS_TRUE;
        punCodecList->stSupportCodec.CodecType_GSMHRAMR     = VOS_TRUE;
        punCodecList->stSupportCodec.CodecType_GSMFRAMRWB   = VOS_TRUE;
    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_ReadNvCodecSupportList
 Description     : 从NV项读取GU codec支持list信息
 Input           : None
 Output          : None
 Return          : None

 History         :
    1.sunbing 49683      2013-10-21  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_ReadNvCodecSupportList(VOS_VOID )
{
    NAS_LMM_PUB_INFO_STRU               *pstPubInfo;
    NAS_EMM_SUPPORT_CODEC_UNION          unCodec;

    pstPubInfo = NAS_LMM_GetEmmInfoAddr();

    pstPubInfo->bitOpSupCodecList               = NAS_EMM_BIT_SLCT;
    pstPubInfo->stSupCodecList.ucLenOfCodecList = 0x08;

     /* 设置支持的列表，目前填入了GSM和UMTS支持的codec list,
       00 表示GSM, 04表示UMTS */
    /* 具体赋值的含义参见26.103 */

    NAS_LMM_MEM_SET_S(&unCodec,sizeof(unCodec),0x00,sizeof(unCodec));

    NAS_EMM_ReadNvUmtsCodecInfo(&unCodec);
    pstPubInfo->stSupCodecList.astCodec[0].ucSysId = 0x04;
    pstPubInfo->stSupCodecList.astCodec[0].ucLenOfBitmap = 0x02;
    pstPubInfo->stSupCodecList.astCodec[0].aucCodecBitmap[0] = (VOS_UINT8)(unCodec.usSupportCodec);
    pstPubInfo->stSupCodecList.astCodec[0].aucCodecBitmap[1] = (VOS_UINT8)(unCodec.usSupportCodec >> 8);

    NAS_LMM_MEM_SET_S(&unCodec,sizeof(unCodec),0x00,sizeof(unCodec));

    NAS_EMM_ReadNvGsmCodecInfo(&unCodec);
    pstPubInfo->stSupCodecList.astCodec[1].ucSysId = 0x00;
    pstPubInfo->stSupCodecList.astCodec[1].ucLenOfBitmap = 0x02;
    pstPubInfo->stSupCodecList.astCodec[1].aucCodecBitmap[0] = (VOS_UINT8)(unCodec.usSupportCodec);
    pstPubInfo->stSupCodecList.astCodec[1].aucCodecBitmap[1] = (VOS_UINT8)(unCodec.usSupportCodec >> 8);

}
/*sunbing 49683 2013-10-21 VoLTE end*/

/*****************************************************************************
 Function Name   : NAS_EMM_ReadNvNasRelease
 Description     : 从NV项读取用户配置的网侧原因
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2013-2-6  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_ReadNvConfigNwCause(VOS_VOID )
{
    LNAS_LMM_NV_CONFIG_NWCAUSE_STRU    stNvConfigCause;
    NAS_EMM_PUB_INFO_STRU              *pstPubInfo;
    VOS_VOID                           *pData = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    VOS_UINT16                          usDataLen;

    pstPubInfo = NAS_LMM_GetEmmInfoAddr();
    pData                               = (VOS_VOID *)&(stNvConfigCause);
    usDataLen = sizeof(LNAS_LMM_NV_CONFIG_NWCAUSE_STRU);

    ulRslt = NAS_LMM_NvimRead(          EN_NV_ID_CONFIG_NWCAUSE,
                                        pData,
                                        &usDataLen);

    if((EN_NV_OK == ulRslt)
        && (stNvConfigCause.ucCauseNum > NAS_EMM_NULL))
    {

        NAS_LMM_PUBM_LOG1_NORM("NAS_EMM_ReadNvConfigNwCause: read NV success, CauseNum=",
            stNvConfigCause.ucCauseNum);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ReadNvConfigNwCause_ENUM,LNAS_CAUSE_NUMBER,
            stNvConfigCause.ucCauseNum);
        if ((NAS_EMM_NULL == stNvConfigCause.ucCauseNum)
            || (NAS_LMM_MAX_CAUSE_NUM < stNvConfigCause.ucCauseNum))
        {
            NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ReadNvConfigNwCause: config NV err.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ReadNvConfigNwCause_ENUM,LNAS_FUNCTION_LABEL1);
            return;
        }

        pstPubInfo->stConfCause.ucCauseNum = stNvConfigCause.ucCauseNum;
        NAS_LMM_MEM_CPY_S(  pstPubInfo->stConfCause.astAdaptCause,
                            sizeof(NAS_LMM_ADAPTION_CAUSE_STRU) * NAS_LMM_MAX_CAUSE_NUM,
                            stNvConfigCause.astAdaptCause,
                            sizeof(NAS_LMM_ADAPTION_CAUSE_STRU) * NAS_LMM_MAX_CAUSE_NUM);
    }
    else
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ReadNvConfigNwCause: read NV err.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ReadNvConfigNwCause_ENUM,LNAS_FUNCTION_LABEL2);
        pstPubInfo->stConfCause.ucCauseNum = 0;

        NAS_LMM_MEM_SET_S(  pstPubInfo->stConfCause.astAdaptCause,
                            sizeof(NAS_LMM_ADAPTION_CAUSE_STRU) * NAS_LMM_MAX_CAUSE_NUM,
                            0,
                            sizeof(NAS_LMM_ADAPTION_CAUSE_STRU) * NAS_LMM_MAX_CAUSE_NUM);

    }
    return;
}



/*****************************************************************************
 Function Name   : NAS_EMM_SetLteUeUsageSetting2Mml
 Description     : 将UE's setting设置到MML中
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong 00150010      2012-07-16  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_SetLteUeUsageSetting2Mml
(
    NAS_EMM_USAGE_SETTING_UINT32        enUeUsageSetting
)
{
    NAS_LMM_PUBM_LOG1_NORM("NAS_EMM_SetLteUeUsageSetting2Mml: ue's usage setting:",
                           enUeUsageSetting);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_SetLteUeUsageSetting2Mml_ENUM,LNAS_EMM_UE_USG_SETTING,
                           enUeUsageSetting);

    NAS_MML_SetLteUeUsageSetting((VOS_UINT8)enUeUsageSetting);
}

/*****************************************************************************
 Function Name   : NAS_EMM_ReadNvUeSetting
 Description     : 从NV项中读取UE's setting，并设置到MML中
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010      2012-02-28  Draft Enact
    2.wangchen 00209181    2012-06-29  Modify:cs/ps1
*****************************************************************************/
VOS_VOID  NAS_EMM_ReadNvUeSetting( VOS_VOID )
{
    VOS_VOID                           *pData           = VOS_NULL_PTR;
    LNAS_LMM_NV_UE_CENTER_STRU          stNvUeCenter    = {0};
    NAS_EMM_PUB_INFO_STRU              *pstPubInfo      = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt          = NAS_EMM_NULL;
    VOS_UINT16                          usDataLen       = NAS_EMM_NULL;

    pstPubInfo  = NAS_LMM_GetEmmInfoAddr();
    pData       = (VOS_VOID *)&(stNvUeCenter);
    usDataLen   = sizeof(LNAS_LMM_NV_UE_CENTER_STRU);

    ulRslt      = NAS_LMM_NvimRead(     EN_NV_ID_UE_CENTER,
                                        pData,
                                        &usDataLen);

    if((EN_NV_OK == ulRslt)
        && (stNvUeCenter.bitOpUeCenter == NAS_EMM_BIT_SLCT))
    {
        NAS_LMM_PUBM_LOG1_NORM("NAS_EMM_ReadNvUeSetting: read NV success.",
            stNvUeCenter.enUeCenter);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ReadNvUeSetting_ENUM,LNAS_FUNCTION_LABEL1,
            stNvUeCenter.enUeCenter);
        if (EMM_USAGE_SETTING_BUTT > stNvUeCenter.enUeCenter)
        {
            pstPubInfo->ulUsageSetting  = stNvUeCenter.enUeCenter;
        }
        else
        {
            NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ReadNvUeSetting:NV Value is Invalid");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ReadNvUeSetting_ENUM,LNAS_FUNCTION_LABEL2);
            pstPubInfo->ulUsageSetting  = EMM_SETTING_DATA_CENTRIC;
        }
    }
    else
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ReadNvUeSetting: read NV err.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ReadNvUeSetting_ENUM,LNAS_FUNCTION_LABEL3);
        pstPubInfo->ulUsageSetting      = EMM_SETTING_DATA_CENTRIC;
    }

    NAS_EMM_SetLteUeUsageSetting2Mml(pstPubInfo->ulUsageSetting);

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_PubmInfoSupCodecListInit
 Description     : EMM 全局信息初始化中的SupCodecList初始化
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h41410      2009-1-5  Draft Enact
    2.l00132387   2011-7-5  Modify
    3.sunbing 49683 2013-10-21  Modify
*****************************************************************************/
VOS_VOID    NAS_EMM_PubmInfoSupCodecListInit( VOS_VOID )
{
    NAS_LMM_PUB_INFO_STRU               *pstPubInfo;

    pstPubInfo = NAS_LMM_GetEmmInfoAddr();

    /*sunbing 49683 2013-10-14 VoLTE begin*/
    /*初始化设置为无效，后续读取NV，会进一步赋值*/
    pstPubInfo->bitOpSupCodecList       = NAS_EMM_BIT_NO_SLCT;

     /* 设置支持的列表，目前填入了GSM和UMTS支持的codec list,
       00 表示GSM, 04表示UMTS */
    /* 具体赋值的含义参见26.103 */
    /*
    pstPubInfo->stSupCodecList.ucLenOfCodecList = 0x08;
    pstPubInfo->stSupCodecList.astCodec[0].ucSysId = 0x04;
    pstPubInfo->stSupCodecList.astCodec[0].ucLenOfBitmap = 0x02;
    pstPubInfo->stSupCodecList.astCodec[0].aucCodecBitmap[0] = 0x60;
    pstPubInfo->stSupCodecList.astCodec[0].aucCodecBitmap[1] = 0x00;
    pstPubInfo->stSupCodecList.astCodec[1].ucSysId = 0x00;
    pstPubInfo->stSupCodecList.astCodec[1].ucLenOfBitmap = 0x02;
    pstPubInfo->stSupCodecList.astCodec[1].aucCodecBitmap[0] = 0x1F;
    pstPubInfo->stSupCodecList.astCodec[1].aucCodecBitmap[1] = 0x00;
    */
    /*sunbing 49683 2013-10-14 VoLTE end*/

    return;
}

/*****************************************************************************
 Function Name   :  NAS_EMM_PubmInfoBearerContextInit()
 Description     : EMM 全局信息初始化中的承载上下文初始化
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421 2009.03.26 New Draft
*****************************************************************************/
VOS_VOID     NAS_EMM_PubmInfoBearerContextInit(VOS_VOID)
{
    NAS_MML_PS_BEARER_CONTEXT_STRU      *pstPsBearerCtx = NAS_EMM_NULL_PTR;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PubmInfoBearerContextInit is entry");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PubmInfoBearerContextInit_ENUM,LNAS_ENTRY);

    pstPsBearerCtx = NAS_EMM_GetPsBearerCtx();

    NAS_LMM_MEM_SET_S(  pstPsBearerCtx,
                        sizeof(NAS_MML_PS_BEARER_CONTEXT_STRU) * NAS_MML_MAX_PS_BEARER_NUM,
                        0,
                        EMM_ESM_MAX_EPS_BEARER_NUM*sizeof(NAS_MML_PS_BEARER_CONTEXT_STRU));

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PubmInfoBearerContextInit: UPDATE MML PS BEARER INFO:");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PubmInfoBearerContextInit_ENUM,LNAS_FUNCTION_LABEL2);
    NAS_LMM_LogPsBearerCtxInfo(pstPsBearerCtx);

    return;
}

/*****************************************************************************
 Function Name  : RRC_CMM_FsmReg
 Discription    : CMM状态机注册函数
 Input          : None
 Output         : None
 Return         : None

 History:
    1.h41410      2008-10-13  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_EMM_FsmReg( VOS_VOID )
{
    VOS_UINT32                      ulRslt = NAS_LMM_FAIL;

    VOS_UINT32                      ulSizeof1;
    VOS_UINT32                      ulSizeof2;

    ulSizeof1                       = g_ulSizeof_g_astEmmStaTbl;
    ulSizeof2                       = sizeof(NAS_LMM_STA_STRU);

    /* 注册RRC_FSM_CESL状态机 */
    ulRslt = NAS_LMM_FsmRegisterFsm(NAS_LMM_PARALLEL_FSM_EMM,
                                    (VOS_UINT32)(ulSizeof1 / ulSizeof2),
                                    g_astEmmStaTbl,
                                    NAS_EMM_FsmErr);
    if (ulRslt != NAS_LMM_SUCC)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_FsmReg, register fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_FsmReg_ENUM,LNAS_FAIL);
    }
    else
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_FsmReg, register SUCC!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_FsmReg_ENUM,LNAS_SUCC);
    }

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_FsmErr
 Description     : EMM状态机的出错处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h41410      2008-10-13  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_FsmErr(             VOS_UINT32           ulMsgId,
                                                VOS_VOID             *pMsg )
{
/*    NAS_LMM_PUBM_LOG2_ERR("NAS_EMM_FsmErr: ", ulMsgId, pMsg);*/
    (VOS_VOID)(ulMsgId);
    (VOS_VOID)(pMsg);
    return  NAS_LMM_MSG_DISCARD;
}

/*****************************************************************************
 Function Name  :NAS_EMM_FSM_PushState
 Discription    :
 Input          :
 Output         : None
 Return         : None
 History:
    1.h41410      2008-10-13  Draft Enact
*****************************************************************************/
VOS_VOID    NAS_EMM_FSM_PushState(VOS_VOID)
{
    NAS_LMM_FSM_PushStackCombine(NAS_LMM_PARALLEL_FSM_EMM);
    return;
}

/*****************************************************************************
 Function Name  :NAS_EMM_FSM_PopState
 Discription    :
 Input          :
 Output         : None
 Return         : None
 History:
    1.h41410      2008-10-13  Draft Enact
*****************************************************************************/
VOS_VOID    NAS_EMM_FSM_PopState(VOS_VOID)
{
    NAS_LMM_FSM_PopStackCombine(NAS_LMM_PARALLEL_FSM_EMM);
    return;
}

/*****************************************************************************
 Function Name  :NAS_EMM_FSM_PopState
 Discription    :把栈的所有压入的状态全部弹出来，最底层
                 的状态弹成当前状态
 Input          :
 Output         : None
 Return         : None
 History:
    1.h41410      2010-10-18  Draft Enact
*****************************************************************************/
VOS_VOID    NAS_EMM_FSM_PopAllState(VOS_VOID)
{
    VOS_UINT32                          ulStackCurDepth;
    NAS_LMM_FSM_STATE_STACK_STRU        *pstFsmStack;        /* 状态机栈地址 */


    /* 获取EMM状态机当前状态的地址和状态机栈的地址 */
    pstFsmStack = NAS_LMM_GetFsmStackAddr(NAS_LMM_PARALLEL_FSM_EMM);
    ulStackCurDepth = pstFsmStack->ucStackDepth;
    NAS_LMM_PUBM_LOG1_INFO("NAS_EMM_FSM_PopAllState: ulStackCurDepth = ", ulStackCurDepth);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_FSM_PopAllState_ENUM,LNAS_FUNCTION_LABEL1,ulStackCurDepth);

    for(; 0 < ulStackCurDepth; ulStackCurDepth-- )
    {
        NAS_LMM_FSM_PopStackCombine(NAS_LMM_PARALLEL_FSM_EMM);
    }

    return;
}


VOS_VOID    NAS_EMM_FSM_ClearState(VOS_VOID)
{
    NAS_LMM_FSM_ClearStackCombine(NAS_LMM_PARALLEL_FSM_EMM);
    return;
}



/*****************************************************************************
 Function Name   : NAS_LMM_MatchNvImsi
 Description     : 取ME的NV中IMSI与内存中的IMSI比较
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    leili  00132387      2010-1-12  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_MatchNvImsi( VOS_VOID )
{
    VOS_VOID                           *pData;
    LNAS_LMM_NV_IMSI_STRU               stNvImsi;
    VOS_UINT32                          ulRslt;
    VOS_UINT16                          usDataLen;


    /*read Imsi from Nvim*/
    pData                               = &(stNvImsi);
    usDataLen                           = sizeof(LNAS_LMM_NV_IMSI_STRU);
    ulRslt = NAS_LMM_NvimRead(           EN_NV_ID_IMSI,
                                        pData,
                                        &usDataLen);

    if((NAS_LMM_NVIM_OK == ulRslt) && (NAS_EMM_BIT_SLCT == stNvImsi.bitOpImsi))
    {
        if (0 == NAS_LMM_MEM_CMP((const VOS_VOID *) g_stEmmInfo.stMmUeId.aucImsi,
                         (const VOS_VOID *) stNvImsi.aucImsi,
                         NAS_LMM_NVIM_IMSI_FILE_LEN))
        {
            NAS_LMM_PUBM_LOG_INFO("NAS_LMM_MatchNvImsi: IMSI EQUAL. ");
            TLPS_PRINT2LAYER_INFO(NAS_LMM_MatchNvImsi_ENUM,LNAS_FUNCTION_LABEL1);
            return NAS_EMM_SUCC;

        }
    }

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_MatchNvImsi: IMSI DIFF. ");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_MatchNvImsi_ENUM,LNAS_FUNCTION_LABEL2);
    return NAS_EMM_FAIL;
}


VOS_VOID  NAS_LMM_UpdateNvImsi(const VOS_UINT8  *pucImsi )
{

    VOS_UINT32                          ulRst;
    VOS_VOID                           *pData;
    LNAS_LMM_NV_IMSI_STRU               stNvImsi;
    VOS_UINT16                          usDataLen;
    NAS_LMM_UEID_STRU                    *pstUeId;

    NAS_LMM_NVIM_LOG_INFO("NAS_LMM_UpdateNvImsi is entered");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_UpdateNvImsi_ENUM,LNAS_ENTRY);

    NAS_LMM_MEM_SET_S(&stNvImsi, sizeof(LNAS_LMM_NV_IMSI_STRU), 0, sizeof(LNAS_LMM_NV_IMSI_STRU));

    pstUeId                             = NAS_LMM_GetEmmInfoUeidAddr();

    /*填充新的IMSI*/
    stNvImsi.bitOpImsi                  = pstUeId->bitOpImsi;
    NAS_LMM_MEM_CPY_S(                  stNvImsi.aucImsi,
                                        NAS_MM_MAX_UEID_BUF_SIZE,
                                        pucImsi,
                                        NAS_LMM_NVIM_IMSI_FILE_LEN);

    /*write new IMSI to NVIM*/
    pData                               = &stNvImsi;
    usDataLen                           = sizeof(LNAS_LMM_NV_IMSI_STRU);

    ulRst = NAS_LMM_NvimWrite(           EN_NV_ID_IMSI,
                                        pData,
                                        usDataLen);
    if(EN_NV_OK != ulRst)
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_UpdateNvImsi: nvim ERR!!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_UpdateNvImsi_ENUM,LNAS_ERROR);
        return;
    }

    return;
}


/*****************************************************************************
 Function Name   : NAS_LMM_ReadNvimImei
 Description     : 读取IMSI
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2009-02-27  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LMM_ReadNvimImei(VOS_VOID)
{
    VOS_UINT8                           aucDefImei[NAS_MM_MAX_UEID_BUF_SIZE] = {0};

    VOS_UINT8                           aucBuf[NV_ITEM_IMEI_SIZE] = {0};

    VOS_UINT32                          i = 0;

    /*IMEI读取失败，则使用缺省值*/
    if(ERR_MSP_SUCCESS != SC_PERS_VerifyNvReadImei(MODEM_ID_0, en_NV_Item_IMEI, aucBuf, NV_ITEM_IMEI_SIZE))
    {
        NAS_LMM_MEM_SET_S(aucDefImei,  NAS_MM_MAX_UEID_BUF_SIZE, 0, NAS_MM_MAX_UEID_BUF_SIZE);

        aucDefImei[0] = 0x08;
        aucDefImei[1] = 0x3A;
        aucDefImei[2] = 0x65;
        aucDefImei[3] = 0x26;
        aucDefImei[4] = 0x06;
        aucDefImei[5] = 0x70;
        aucDefImei[6] = 0x37;
        aucDefImei[7] = 0x71;
        aucDefImei[8] = 0x04;
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_ReadNvimImei: Read IMEI from NV fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_ReadNvimImei_ENUM,LNAS_FAIL);
    }
    else
    {
        /* NV读取成功则重新计算IMEI校验位，并转换为LNAS内部IMEI号存储格式 */
        aucDefImei[0] = 0x08;
        aucDefImei[1] = 0x0A;

        /* 将NV中格式转变为LNAS内部IMEI存放格式 */
        for (i = 0; i < (NV_ITEM_IMEI_SIZE - 1); i++)
        {
             aucDefImei[((i + 1) / 2) + 1] |= (VOS_UINT8)(aucBuf[i] << (((i + 1) % 2) * NAS_LMM_MOVEMENT_4_BITS));
        }
    }

    NAS_LMM_GetEmmInfoUeidAddr()->bitOpImei = NAS_EMM_BIT_SLCT;
    NAS_LMM_MEM_CPY_S(              NAS_LMM_GetEmmInfoUeidImeiAddr(),
                                    NAS_MM_MAX_UEID_BUF_SIZE,
                                    aucDefImei,
                                    NAS_MM_MAX_UEID_BUF_SIZE);
    /* 打印获取到的IMEI值 */
    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ReadNvimImei: IMEI value is :");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadNvimImei_ENUM,LNAS_FUNCTION_LABEL1);
    NAS_COMM_PrintArray(NAS_COMM_GET_MM_PRINT_BUF(),
                   NAS_LMM_GetEmmInfoUeidImeiAddr(),
                   NAS_MM_MAX_UEID_BUF_SIZE);

    return;
}





VOS_VOID  NAS_LMM_ReadNvEpsSecContext(VOS_VOID )
{
    LNAS_LMM_NV_EPS_SEC_CONTEXT_STRU    stNvEpsSecContext;
    NAS_LMM_SECU_CONTEXT_STRU            stSecuCurContext;
    VOS_UINT32                          ulRslt;
    VOS_UINT16                          usDataLen;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ReadNvEpsSecContext is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadNvEpsSecContext_ENUM,LNAS_ENTRY);

    /*read  from Nvim*/
    usDataLen                           = sizeof(LNAS_LMM_NV_EPS_SEC_CONTEXT_STRU);
    ulRslt = NAS_LMM_NvimRead(           EN_NV_ID_SEC_CONTEXT,
                                        (VOS_VOID *)&(stNvEpsSecContext),
                                        &usDataLen);

    /* 从NV的数据结构向 NAS 核心结构转换 */
    NAS_LMM_MEM_SET_S(  &stSecuCurContext,
                        sizeof(NAS_LMM_SECU_CONTEXT_STRU),
                        0,
                        sizeof(NAS_LMM_SECU_CONTEXT_STRU));

    NAS_LMM_MEM_SET_S(  NAS_LMM_GET_USIM_EPS_SECU_CONTEXT_ADDR(),
                        NAS_NVIM_SECU_CONTEXT_MAX_LEN,
                        0,
                        NAS_NVIM_SECU_CONTEXT_MAX_LEN);

    /*process the result of reading,具体处理方式有待需求确定*/
    if((NAS_LMM_NVIM_OK == ulRslt) && (NAS_EMM_BIT_SLCT == stNvEpsSecContext.bitOpEpsSec))
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ReadNvEpsSecContext: read NV Succ.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadNvEpsSecContext_ENUM,LNAS_SUCC);

        /* 将NV中的安全上下文码流保存在上次写卡的全局变量中，用于下次写卡时的比较 */
        NAS_LMM_MEM_CPY_S(  NAS_LMM_GET_USIM_EPS_SECU_CONTEXT_ADDR(),
                            NAS_NVIM_SECU_CONTEXT_MAX_LEN,
                            (VOS_VOID *)&(stNvEpsSecContext),
                            sizeof(LNAS_LMM_NV_EPS_SEC_CONTEXT_STRU));

  /*当前安全上下文结构赋值*/
        stSecuCurContext.ucKSIasme      = stNvEpsSecContext.ucKSIasme;

        NAS_LMM_MEM_CPY_S(              stSecuCurContext.aucKasme,
                                        NAS_LMM_SECU_AUTH_KEY_ASME_LEN,
                                        stNvEpsSecContext.aucKasme,
                                        NAS_MM_AUTH_KEY_ASME_LEN);
        stSecuCurContext.ulUlNasCount   = stNvEpsSecContext.ulUlNasCount;
        stSecuCurContext.ulDlNasCount   = stNvEpsSecContext.ulDlNasCount;
        stSecuCurContext.ucSecuAlg      = stNvEpsSecContext.ucSecuAlg;

        /*调用安全上下文更新函数,并计算NasCK ,NasIk*/
        NAS_EMM_SecuSetCurCntxt(&stSecuCurContext);
    }

    else
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_ReadNvEpsSecContext: read NV Fail!");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadNvEpsSecContext_ENUM,LNAS_FAIL);
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_ReadNvATTDamParaCServiceAndPlmnList
 Description     : 读取AT&T定制需求参数NV项
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    sunjitan 00193151      2015-01-04  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_ReadNvDamParaCServiceAndPlmnList(VOS_VOID )
{
    PS_NV_DAM_CONFIG_PARA_STRU            stNvDamPara = {0};
    VOS_UINT32                            ulRslt    = NAS_LMM_NVIM_FAIL;
    VOS_UINT16                            usDataLen = 0;
    NAS_MM_DAM_PLMN_LIST_STRU            *pstDamPlmnList;
    NAS_DAM_IMSI_PLMN_LIST               *pstImsiPlmnList;

    pstDamPlmnList   = NAS_EMM_GetEmmInfoDamParaPlmnListAddr();
    pstImsiPlmnList  = NAS_EMM_GetEmmInfoDamParaImsiPlmnListAddr();

    /* 读NV之前先赋值默认值，读取成功后再进行刷新 */
    NAS_EMM_GetEmmInfoDamParaCserviceMax() = NAS_LMM_DAM_CSERVICE_DEFAULT_VALUE;

    NAS_LMM_MEM_SET_S(  pstDamPlmnList,
                        sizeof(NAS_MM_DAM_PLMN_LIST_STRU),
                        0,
                        sizeof(NAS_MM_DAM_PLMN_LIST_STRU));
    NAS_LMM_MEM_SET_S(  pstImsiPlmnList,
                        sizeof(NAS_DAM_IMSI_PLMN_LIST),
                        0,
                        sizeof(NAS_DAM_IMSI_PLMN_LIST));

    /* 读NV */
    usDataLen = sizeof(PS_NV_DAM_CONFIG_PARA_STRU);
    ulRslt = NAS_LMM_NvimRead(EN_NV_ID_DAM_CONFIG_PARA,
                              (VOS_VOID *)&(stNvDamPara),
                              &usDataLen);

    if(NAS_LMM_NVIM_OK == ulRslt)
    {
        /* CService的值有效且必须处于1-60之间 */
        if((NAS_LMM_DAM_NV_CSERVICE_MAX_VALUE >= stNvDamPara.ulCService)
            &&(NAS_LMM_DAM_NV_CSERVICE_MIN_VALUE <= stNvDamPara.ulCService))
        {
            NAS_EMM_GetEmmInfoDamParaCserviceMax() = stNvDamPara.ulCService;
        }

        if((0 < stNvDamPara.stDamConfigPlmnPara.stDamPlmnList.ulPlmnNum)
            &&(NAS_MM_DAM_MAX_PLMN_NUM >= stNvDamPara.stDamConfigPlmnPara.stDamPlmnList.ulPlmnNum))
        {
            pstDamPlmnList->ulPlmnNum = stNvDamPara.stDamConfigPlmnPara.stDamPlmnList.ulPlmnNum;

            NAS_LMM_MEM_CPY_S(  pstDamPlmnList->astPlmnId,
                                sizeof(NAS_MM_PLMN_ID_STRU)*NAS_MM_DAM_MAX_PLMN_NUM,
                                stNvDamPara.stDamConfigPlmnPara.stDamPlmnList.astPlmnId,
                                sizeof(NAS_MM_PLMN_ID_STRU)*NAS_MM_DAM_MAX_PLMN_NUM);
        }

        if((0 < stNvDamPara.stDamConfigPlmnPara.stImsiPlmnList.ulPlmnNum)
            &&(NAS_MM_DAM_MAX_PLMN_NUM >= stNvDamPara.stDamConfigPlmnPara.stImsiPlmnList.ulPlmnNum))
        {
            pstImsiPlmnList->ulPlmnNum = stNvDamPara.stDamConfigPlmnPara.stImsiPlmnList.ulPlmnNum;

            NAS_LMM_MEM_CPY_S(  pstImsiPlmnList->astPlmnId,
                                sizeof(NAS_MM_PLMN_ID_STRU)*NAS_MM_DAM_MAX_PLMN_NUM,
                                stNvDamPara.stDamConfigPlmnPara.stImsiPlmnList.astPlmnId,
                                sizeof(NAS_MM_PLMN_ID_STRU)*NAS_MM_DAM_MAX_PLMN_NUM);
        }
    }
    else
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ReadNvATTDamParaCServiceAndPlmnList: read NV Fail.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadNvDamParaCServiceAndPlmnList_ENUM,LNAS_FAIL);
    }

    /* 输出读出的NV参数到HIDS */
    NAS_LMM_SndOmDamPara();

    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_ReadRej19AtmptCnt
 Description     : 读取NV项EN_NV_ID_LNAS_COMM_CONFIG_PARA中设置的ucRej19AtmptCntFlag
 Input           : None
 Output          : None
 Return          : VOS_VOID
 History         :
    1.    sunjitan 00193151      2015-01-04  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_ReadRej19AtmptCntFlag(VOS_UINT8 ucRej19AtmptCntFlag)
{
    NAS_EMM_GetEmmInfoRej19AtmptCntFlag() = ucRej19AtmptCntFlag;
    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_ReadTmoImsiHplmnListAndSetTmoUsimCardFlag
 Description     : 读取NV项EN_NV_ID_LNAS_COMM_CONFIG_PARA中设置的TmoImsiHplmnList，
                   然后设置是否是TMO卡的标识
 Input           : None
 Output          : None
 Return          : VOS_VOID
 History         :
    1.    sunjitan 00193151      2015-03-15  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_ReadTmoImsiHplmnListAndSetTmoUsimCardFlag
(
    NAS_TMO_IMSI_HPLMN_LIST *pstTmoImsiHplmnList
)
{
    VOS_UINT8                 *pucImsi = 0;
    NAS_MM_PLMN_ID_STRU        stHplmn;
    VOS_UINT32                 ulIndex = 0;

    NAS_LMM_MEM_SET_S(&stHplmn, sizeof(NAS_MM_PLMN_ID_STRU), 0x00, sizeof(NAS_MM_PLMN_ID_STRU));

    pucImsi = (VOS_UINT8*)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_PARA_IMSI);

    /* 初始化Flag为非TMO卡 */
    NAS_EMM_GetEmmInfoTmoUsimCardFlag() = VOS_FALSE;

    /* 约定；NV中关于IMSI的PLMN判断如果只设置1个PLMN且全为0XFF，则默认所有卡都是TMO卡 */
    if((1 == pstTmoImsiHplmnList->ulPlmnNum)
        &&(NAS_LMM_BYTE_FF == pstTmoImsiHplmnList->astPlmnId[0].aucPlmnId[0])
        &&(NAS_LMM_BYTE_FF == pstTmoImsiHplmnList->astPlmnId[0].aucPlmnId[1])
        &&(NAS_LMM_BYTE_FF == pstTmoImsiHplmnList->astPlmnId[0].aucPlmnId[2]))
    {
        NAS_EMM_GetEmmInfoTmoUsimCardFlag() = VOS_TRUE;
        return;
    }

    NAS_LMM_PUBM_LOG3_INFO("NAS_LMM_ReadTmoImsiHplmnListAndSetTmoUsimCardFlag: plmnNum/0/1",
                           pstTmoImsiHplmnList->ulPlmnNum,
                           pstTmoImsiHplmnList->astPlmnId[0].aucPlmnId[0],
                           pstTmoImsiHplmnList->astPlmnId[0].aucPlmnId[1]);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_ReadTmoImsiHplmnListAndSetTmoUsimCardFlag_ENUM,LNAS_EMM_PLMN,
                           pstTmoImsiHplmnList->ulPlmnNum);
    TLPS_PRINT2LAYER_INFO2(NAS_LMM_ReadTmoImsiHplmnListAndSetTmoUsimCardFlag_ENUM,LNAS_FUNCTION_LABEL1,
                            pstTmoImsiHplmnList->astPlmnId[0].aucPlmnId[0],
                           pstTmoImsiHplmnList->astPlmnId[0].aucPlmnId[1]);
    NAS_LMM_PUBM_LOG1_INFO("NAS_LMM_ReadTmoImsiHplmnListAndSetTmoUsimCardFlag: id2",
                           pstTmoImsiHplmnList->astPlmnId[0].aucPlmnId[2]);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_ReadTmoImsiHplmnListAndSetTmoUsimCardFlag_ENUM,LNAS_FUNCTION_LABEL2,
                           pstTmoImsiHplmnList->astPlmnId[0].aucPlmnId[2]);

    /* 需要判断卡 */
    /* 获取HPLMN，然后跟IMSI PLMN列表进行比对，获取成功且比对成功才是TMO的卡 */
    if(NAS_EMM_SUCC == NAS_EMM_GetImsiHplmn(pucImsi, &stHplmn))
    {
        for(ulIndex = 0; ulIndex < pstTmoImsiHplmnList->ulPlmnNum; ulIndex++)
        {
            if(NAS_LMM_MATCH_SUCCESS == NAS_LMM_PlmnMatch(&(stHplmn),
                (NAS_MM_PLMN_ID_STRU*)&(pstTmoImsiHplmnList->astPlmnId[ulIndex])))
            {
                NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ReadTmoImsiHplmnListAndSetTmoUsimCardFlag: TMO Card.");
                TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadTmoImsiHplmnListAndSetTmoUsimCardFlag_ENUM,LNAS_FUNCTION_LABEL3);
                NAS_EMM_GetEmmInfoTmoUsimCardFlag() = VOS_TRUE;
                return;
            }
        }
    }

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_LteNoSubscribeInit
 Description     : 4G未开户问题全局变量初始化
 Input           : None
 Output          : None
 Return          : VOS_VOID
 History         :
    1.    lifuxin  00253982      2015-02-26  4G未开户问题修改
    2.    sunbing  00265702      2015-10-15  为通过移动入网测试，
                                             增加NV控制，可以定制关闭协议规定的4G未开户功能功能
*****************************************************************************/
VOS_VOID  NAS_EMM_LteNoSubscribeInit(
            LNAS_LMM_NV_LTE_NO_SUBSCRIBE_CONFIG_STRU stLteNoSubscribeNvConfig)
{
    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_LteNoSubscribeInit is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_LteNoSubscribeInit_ENUM,LNAS_ENTRY);

    NAS_LMM_MEM_SET_S(  NAS_EMM_GetLteNoSubscribeAddr(),
                        sizeof(LNAS_LMM_LTE_NO_SUBSCRIBE_CONFIG_STRU),
                        0,
                        sizeof(LNAS_LMM_NV_LTE_NO_SUBSCRIBE_CONFIG_STRU));

    /*非仪器测试场景才进行部分定制功能的初始化*/
    if(PS_SUCC != LPS_OM_IsTestMode())
    {
        NAS_EMM_SetLteNoSubscribeNvConfigHplmnSwitch(
                    stLteNoSubscribeNvConfig.ucLteNoSubscribeHplmnSwitch);
        NAS_EMM_SetLteNoSubscribeNvConfigVplmnSwitch(
                    stLteNoSubscribeNvConfig.ucLteNoSubscribeVplmnSwitch);
    }

    /*如果定时时长大于最大值，则设置成最大值*/
    if( NAS_MAX_PUBLISHMENT_TIMER_LEN < stLteNoSubscribeNvConfig.ulPublishmentTimerVplmnLen)
    {
        stLteNoSubscribeNvConfig.ulPublishmentTimerVplmnLen = NAS_MAX_PUBLISHMENT_TIMER_LEN;
    }

    /*如果定时时长等于0， 则设置成默认值1个小时*/
    if(0 == stLteNoSubscribeNvConfig.ulPublishmentTimerVplmnLen)
    {
        stLteNoSubscribeNvConfig.ulPublishmentTimerVplmnLen = NAS_PUBLISHMENT_LEN_ONE_HOUR;
    }

    /*如果定时时长大于最大值，则设置成最大值*/
    if( NAS_MAX_PUBLISHMENT_TIMER_LEN < stLteNoSubscribeNvConfig.ulPublishmentTimerHplmnLen)
    {
        stLteNoSubscribeNvConfig.ulPublishmentTimerHplmnLen = NAS_MAX_PUBLISHMENT_TIMER_LEN;
    }

    /*如果定时时长等于0， 则设置成默认值1个小时*/
    if(0 == stLteNoSubscribeNvConfig.ulPublishmentTimerHplmnLen)
    {
        stLteNoSubscribeNvConfig.ulPublishmentTimerHplmnLen = NAS_PUBLISHMENT_LEN_ONE_HOUR;
    }

    NAS_EMM_SetLteNoSubscribeNvConfigPublishmentTimerVplmnLen(
        stLteNoSubscribeNvConfig.ulPublishmentTimerVplmnLen);
    NAS_EMM_SetLteNoSubscribeNvConfigPublishmentTimerHplmnLen(
        stLteNoSubscribeNvConfig.ulPublishmentTimerHplmnLen);

    /*默认支持协议规定的4G未开户功能*/
    if(0 == stLteNoSubscribeNvConfig.ucDiscardExtendedEmmCauseFlag)
    {
        NAS_EMM_SetLteNoSubscribeNvConfigDiscardExtCauseFlag(PS_FALSE);
    }
    else
    {
        NAS_EMM_SetLteNoSubscribeNvConfigDiscardExtCauseFlag(PS_TRUE);
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_ReadNvLmmCommConfigPara
 Description     : 读取LMM公共定制需求参数NV项
 Input           : None
 Output          : None
 Return          : VOS_VOID
 History         :
    1.    sunjitan 00193151      2015-01-04  Draft Enact
    2.    lifuxin  00253982      2015-4-3    4G未开户特性NV
*****************************************************************************/
VOS_VOID  NAS_LMM_ReadNvLmmCommConfigPara(VOS_VOID )
{
    LNAS_LMM_NV_COMM_CONFIG_PARA_STRU     stNvCommPara;
    VOS_UINT32                            ulRslt      = NAS_LMM_NVIM_FAIL;
    VOS_UINT16                            usDataLen   = 0;

    NAS_LMM_MEM_SET_S(  &stNvCommPara,
                        sizeof(LNAS_LMM_NV_COMM_CONFIG_PARA_STRU),
                        0,
                        sizeof(LNAS_LMM_NV_COMM_CONFIG_PARA_STRU));

    /* 读NV */
    usDataLen = sizeof(LNAS_LMM_NV_COMM_CONFIG_PARA_STRU);
    ulRslt = NAS_LMM_NvimRead(EN_NV_ID_LNAS_COMM_CONFIG_PARA,
                              (VOS_VOID *)&(stNvCommPara),
                              &usDataLen);

    if(NAS_LMM_NVIM_OK == ulRslt)
    {
        /* 读取成功，输出读出的NV参数到HIDS */
        NAS_LMM_SndOmCommConfigPara(&stNvCommPara);
    }
    else
    {
        /* 读NV失败则清空目标变量，所有相应NV都按默认值初始化 */
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ReadNvLmmCommConfigPara: read NV Fail.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadNvLmmCommConfigPara_ENUM,LNAS_FAIL);
    }

    /* 读取ulRej19AtmptCnt的值 */
    NAS_LMM_ReadRej19AtmptCntFlag(stNvCommPara.ucRej19AtmptCntFlag);

    /* 读取TMO卡HPLMN列表并设置是否是TMO卡标记 */
    NAS_LMM_ReadTmoImsiHplmnListAndSetTmoUsimCardFlag(&stNvCommPara.stTmoImsiHplmnList);

    NAS_EMM_LteNoSubscribeInit(stNvCommPara.stLteNoSubscribeConfig);

    /* 读取其它项的值，后续如有在此补充 */

    return;
}


/*****************************************************************************
 Function Name   : NAS_LMM_ReadSimEpsSecContext
 Description     : 从USIM中读取安全参数
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1. leili    00132387      2010-01-18  Draft Enact
    2. sunjitan 00193151      2015-03-15  Modify
*****************************************************************************/
VOS_VOID  NAS_LMM_ReadSimEpsSecContext( VOS_VOID )
{
    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ReadSimEpsSecContext is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadSimEpsSecContext_ENUM,LNAS_ENTRY);

    NAS_LMM_UsimFileRead(USIMM_USIM_EFEPSNSC_ID);
    return;
}


VOS_VOID  NAS_LMM_ReadNvPsLoc( VOS_VOID )
{
    VOS_VOID                            *pData;
    LNAS_LMM_NV_EPS_LOC_STRU            stNvPsLoc;
    VOS_UINT32                          ulRslt;
    VOS_UINT16                          usDataLen;
    NAS_LMM_UEID_STRU                    *pstUeId;
    NAS_MM_NETWORK_ID_STRU              stMmNetId;
    VOS_UINT8                          *pstLastPsLoc;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ReadNvPsLoc is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadNvPsLoc_ENUM,LNAS_ENTRY);

    pstUeId                             = NAS_LMM_GetEmmInfoUeidAddr();
    pstLastPsLoc                        =NAS_LMM_GetEmmInfoLastWriteUsimPsLocAddr();

    /*read EPS PS LOC from Nvim*/
    pData                               = &(stNvPsLoc);
    usDataLen                           = sizeof(LNAS_LMM_NV_EPS_LOC_STRU);
    ulRslt = NAS_LMM_NvimRead(           EN_NV_ID_EPS_LOC,
                                        pData,
                                        &usDataLen);

    /*process the result of reading,具体处理方式有待需求确定*/
    if(NAS_LMM_NVIM_OK == ulRslt)
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ReadNvPsLoc: read NV Succ.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadNvPsLoc_ENUM,LNAS_SUCC);

        /* 读NV成功，将本次读NV的码流保存到上次成功写卡的全局变量中 */
        NAS_LMM_MEM_CPY_S(  pstLastPsLoc,
                            NAS_EMM_EPS_LOC_MAX_LEN,
                            pData,
                            sizeof(LNAS_LMM_NV_EPS_LOC_STRU));

        /*GUTI*/
        if (NAS_EMM_BIT_SLCT == stNvPsLoc.bitOpGuti)
        {
            NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ReadNvPsLoc: GUTI VALID");
            TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadNvPsLoc_ENUM,LNAS_FUNCTION_LABEL1);
            pstUeId->bitOpGuti          = NAS_EMM_BIT_SLCT;
            NAS_LMM_MEM_CPY_S(          &pstUeId->stGuti,
                                        sizeof(NAS_MM_GUTI_STRU),
                                        &(stNvPsLoc.stGuti),
                                        sizeof(NAS_LMM_GUTI_STRU));

            NAS_EMM_SetLteNoSubscribeLteRegFlag(NAS_LMM_HAVE_REG_SUCC_ON_LTE);
        }

        /*L.R.V TAI*/
        if (NAS_EMM_BIT_SLCT == stNvPsLoc.bitOpTai)
        {
            NAS_LMM_MEM_CPY_S(          &(stMmNetId.stPlmnId),
                                        sizeof(NAS_MM_PLMN_ID_STRU),
                                        &(stNvPsLoc.stLastRegTai.stPlmnId),
                                        sizeof(NAS_MM_PLMN_ID_STRU));

            NAS_LMM_MEM_CPY_S(          &(stMmNetId.stTac),
                                        sizeof(NAS_MM_TAC_STRU),
                                        &(stNvPsLoc.stLastRegTai.stTac),
                                        sizeof(NAS_MM_TAC_STRU));


            /*PLMN有效时,更新全局变量*/
            if (VOS_FALSE == NAS_LMM_CheckPlmnIsInvalid(&stMmNetId.stPlmnId))
            {
                NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ReadNvPsLoc: L.V.R TAI PLMN VALID");
                TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadNvPsLoc_ENUM,LNAS_FUNCTION_LABEL2);
                if (VOS_TRUE == NAS_LMM_TacIsUnexist(&(stMmNetId.stTac)))
                {
                    NAS_LMM_UndefTac(&(stMmNetId.stTac));
                }
                NAS_EMM_SetLVRTai(&stMmNetId);
            }
            else
            {
                NAS_EMM_ClearLVRTai();
            }

        }

        /*UPDATE STATUS*/
        if (NAS_EMM_BIT_SLCT == stNvPsLoc.bitOpUpState)
        {
            NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ReadNvPsLoc: EU VALID");
            TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadNvPsLoc_ENUM,LNAS_FUNCTION_LABEL3);
            NAS_EMM_TAUSER_SaveAuxFsmUpStat((VOS_UINT8)stNvPsLoc.enUpdateState);

        }
    }
    else
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_ReadNvPsLoc: read NV Fail!");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadNvPsLoc_ENUM,LNAS_FUNCTION_LABEL4);
        NAS_EMM_ClearGuti();
        NAS_EMM_ClearLVRTai();
    }

    return;
}


VOS_VOID  NAS_LMM_ReadSimPsLoc( VOS_VOID )
{
    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ReadSimPsLoc is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadSimPsLoc_ENUM,LNAS_ENTRY);

    NAS_LMM_UsimFileRead(USIMM_USIM_EFEPSLOCI_ID);
    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_ReadSimMncLen
 Description     : 读取USIM卡中的MNC长度
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1. sunjitan 00193151      2015-01-04  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_ReadSimMncLen(VOS_VOID)
{
    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ReadSimMncLen is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadSimMncLen_ENUM,LNAS_ENTRY);

    NAS_LMM_UsimFileRead(USIMM_USIM_EFAD_ID);
    return ;
}


VOS_VOID  NAS_LMM_WriteSimEpsSecurityContext(NAS_NV_ITEM_OP_TYPE_ENUM_UINT32 enOpType)
{
    LNAS_LMM_NV_EPS_SEC_CONTEXT_STRU    stNvSecContext;
    NAS_LMM_SECU_CONTEXT_STRU          *pstCurSecuCntxt = VOS_NULL_PTR;

    NAS_LMM_NVIM_LOG_INFO("NAS_LMM_WriteSimEpsSecurityContext is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_WriteSimEpsSecurityContext_ENUM,LNAS_ENTRY);

    NAS_LMM_MEM_SET_S(  &stNvSecContext,
                        sizeof(LNAS_LMM_NV_EPS_SEC_CONTEXT_STRU),
                        0,
                        sizeof(LNAS_LMM_NV_EPS_SEC_CONTEXT_STRU));

    if(NAS_NV_ITEM_UPDATE == enOpType)
    {
        /*获取当前安全上下文*/
        pstCurSecuCntxt = NAS_EMM_SecuGetCurCntxtAddr();

        /* 如果算法是EIA0，则不写卡，直接退出 */
        if (NAS_EMM_SECU_ALG_EIA0 == (pstCurSecuCntxt->ucSecuAlg & NAS_EMM_LOW_3_BITS_F))
        {
            NAS_LMM_NVIM_LOG_INFO("NAS_LMM_WriteSimEpsSecurityContext:EIA0");
            TLPS_PRINT2LAYER_INFO(NAS_LMM_WriteSimEpsSecurityContext_ENUM,LNAS_FUNCTION_LABEL1);
            return ;
        }

        /* 如果注册状态为紧急注册，则不写卡，直接退出 */
        if (NAS_LMM_REG_STATUS_EMC_REGED == NAS_LMM_GetEmmInfoRegStatus())
        {
            NAS_LMM_NVIM_LOG_INFO("NAS_LMM_WriteSimEpsSecurityContext:emc regged");
            TLPS_PRINT2LAYER_INFO(NAS_LMM_WriteSimEpsSecurityContext_ENUM,LNAS_FUNCTION_LABEL2);
            return ;
        }

        /*填充写入USIM的数据*/
        stNvSecContext.ucKSIsgsn        = pstCurSecuCntxt->ucKSIsgsn;
        stNvSecContext.ucKSIasme        = pstCurSecuCntxt->ucKSIasme;
        stNvSecContext.ucSecuAlg        = pstCurSecuCntxt->ucSecuAlg;
        stNvSecContext.ulUlNasCount     = pstCurSecuCntxt->ulUlNasCount;
        stNvSecContext.ulDlNasCount     = pstCurSecuCntxt->ulDlNasCount;
        NAS_LMM_MEM_CPY_S(               stNvSecContext.aucKasme,
                                        NAS_MM_AUTH_KEY_ASME_LEN,
                                        pstCurSecuCntxt->aucKasme,
                                        NAS_LMM_SECU_AUTH_KEY_ASME_LEN);
    }
    else
    {
        NAS_LMM_MEM_SET_S(  &stNvSecContext,
                            sizeof(LNAS_LMM_NV_EPS_SEC_CONTEXT_STRU),
                            (VOS_CHAR)0xff,
                            sizeof(LNAS_LMM_NV_EPS_SEC_CONTEXT_STRU));
    }

    /*write EPS SECURITY CONTEXT to USIM*/
    NAS_LMM_UsimFileWrite(USIMM_USIM_EFEPSNSC_ID,
                          &stNvSecContext,
                          sizeof(LNAS_LMM_NV_EPS_SEC_CONTEXT_STRU));

    return;
}



VOS_VOID  NAS_LMM_WriteNvEpsSecurityContext( NAS_NV_ITEM_OP_TYPE_ENUM_UINT32 enOpType )
{
    VOS_UINT32                          ulRst;
    LNAS_LMM_NV_EPS_SEC_CONTEXT_STRU    stNvSecContext;
    NAS_LMM_SECU_CONTEXT_STRU           *pstCurSecuCntxt = VOS_NULL_PTR;

    NAS_LMM_NVIM_LOG_INFO("NAS_LMM_WriteNvEpsSecurityContext entered.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_WriteNvEpsSecurityContext_ENUM,LNAS_ENTRY);

    NAS_LMM_MEM_SET_S(  &stNvSecContext,
                        sizeof(LNAS_LMM_NV_EPS_SEC_CONTEXT_STRU),
                        0,
                        sizeof(LNAS_LMM_NV_EPS_SEC_CONTEXT_STRU));

    if (NAS_NV_ITEM_UPDATE == enOpType)
    {
        /*获取当前安全上下文*/
        pstCurSecuCntxt = NAS_EMM_SecuGetCurCntxtAddr();

        /* 如果算法是EIA0，则不写NV，直接退出 */
        if (NAS_EMM_SECU_ALG_EIA0 == (pstCurSecuCntxt->ucSecuAlg & NAS_EMM_LOW_3_BITS_F))
        {
            NAS_LMM_NVIM_LOG_INFO("NAS_LMM_WriteNvEpsSecurityContext:EIA0");
            TLPS_PRINT2LAYER_INFO(NAS_LMM_WriteNvEpsSecurityContext_ENUM,LNAS_FUNCTION_LABEL1);
            return ;
        }

        /* 如果注册状态为紧急注册，则不写NV，直接退出 */
        if (NAS_LMM_REG_STATUS_EMC_REGED == NAS_LMM_GetEmmInfoRegStatus())
        {
            NAS_LMM_NVIM_LOG_INFO("NAS_LMM_WriteNvEpsSecurityContext:emc regged");
            TLPS_PRINT2LAYER_INFO(NAS_LMM_WriteNvEpsSecurityContext_ENUM,LNAS_FUNCTION_LABEL2);
            return ;
        }

        /*填充写入USIM的数据*/
        stNvSecContext.bitOpEpsSec      = NAS_NVIM_BIT_SLCT;

        stNvSecContext.ucKSIsgsn        = pstCurSecuCntxt->ucKSIsgsn;
        stNvSecContext.ucKSIasme        = pstCurSecuCntxt->ucKSIasme;
        stNvSecContext.ucSecuAlg        = pstCurSecuCntxt->ucSecuAlg;
        stNvSecContext.ulUlNasCount     = pstCurSecuCntxt->ulUlNasCount;
        stNvSecContext.ulDlNasCount     = pstCurSecuCntxt->ulDlNasCount;
        NAS_LMM_MEM_CPY_S(               stNvSecContext.aucKasme,
                                        NAS_MM_AUTH_KEY_ASME_LEN,
                                        pstCurSecuCntxt->aucKasme,
                                        NAS_LMM_SECU_AUTH_KEY_ASME_LEN);
    }
    else
    {
        stNvSecContext.bitOpEpsSec      = NAS_NVIM_BIT_SLCT;
        stNvSecContext.ucKSIasme        = NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE;
        stNvSecContext.ucKSIsgsn        = NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE;
    }

    /* 如果NV项中保存的与本次要写入的完全相同，则无需写入 */
    if((0 == NAS_LMM_MEM_CMP( (const VOS_VOID *)NAS_LMM_GET_USIM_EPS_SECU_CONTEXT_ADDR(),
                              (const VOS_VOID *)&stNvSecContext,
                              sizeof(LNAS_LMM_NV_EPS_SEC_CONTEXT_STRU))))
    {
        NAS_LMM_NVIM_LOG_INFO("NAS_LMM_WriteNvEpsSecurityContext:  Don't need to write Nvim.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_WriteNvEpsSecurityContext_ENUM,LNAS_FUNCTION_LABEL3);
        return;
    }


    /*write EPS SECURITY CONTEXT to NVIM*/
    ulRst = NAS_LMM_NvimWrite(       EN_NV_ID_SEC_CONTEXT,
                                    &stNvSecContext,
                                    sizeof(LNAS_LMM_NV_EPS_SEC_CONTEXT_STRU));
    if(EN_NV_OK != ulRst)
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_WriteNvEpsSecurityContext: Write nvim Err!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_WriteNvEpsSecurityContext_ENUM,LNAS_ERROR);
    }
    else
    {
        NAS_LMM_NVIM_LOG_INFO("NAS_LMM_WriteNvEpsSecurityContext:Write Nvim SUCC, update last write NV EpsSecurityContext.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_WriteNvEpsSecurityContext_ENUM,LNAS_FUNCTION_LABEL4);

        /* 写NV成功需将本次写NV内容更新到上次写卡EpsSecurityContext信息中 */
        NAS_LMM_MEM_SET_S(  NAS_LMM_GET_USIM_EPS_SECU_CONTEXT_ADDR(),
                            NAS_NVIM_SECU_CONTEXT_MAX_LEN,
                            0,
                            NAS_NVIM_SECU_CONTEXT_MAX_LEN);

        NAS_LMM_MEM_CPY_S(  NAS_LMM_GET_USIM_EPS_SECU_CONTEXT_ADDR(),
                            NAS_NVIM_SECU_CONTEXT_MAX_LEN,
                            &stNvSecContext,
                            sizeof(LNAS_LMM_NV_EPS_SEC_CONTEXT_STRU));
    }


    return;
}


VOS_VOID  NAS_LMM_WriteNvPsLoc
(
    NAS_NV_ITEM_OP_TYPE_ENUM_UINT32     enOpType
)
{
    VOS_UINT32                          ulRst;
    LNAS_LMM_NV_EPS_LOC_STRU            stNvPsLoc = {0};
    NAS_LMM_UEID_STRU                    *pstUeId;
    NAS_MM_NETWORK_ID_STRU              *pstNetId;
    VOS_UINT8                          *pstLastPsLoc;

    NAS_LMM_NVIM_LOG_INFO("NAS_LMM_WriteNvPsLoc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_WriteNvPsLoc_ENUM,LNAS_ENTRY);

    pstLastPsLoc                        =NAS_LMM_GetEmmInfoLastWriteUsimPsLocAddr();

    /*填充新的GUTI*/
    if (NAS_NV_ITEM_UPDATE == enOpType)
    {
        pstUeId                         = NAS_LMM_GetEmmInfoUeidAddr();
        pstNetId                        = NAS_LMM_GetEmmInfoNetInfoLastRegNetAddr();
        stNvPsLoc.bitOpGuti             = pstUeId->bitOpGuti;
        stNvPsLoc.bitOpTai              = NAS_EMM_GetLVRTaiOpBit();
        stNvPsLoc.bitOpUpState          = NAS_NVIM_BIT_SLCT;

        NAS_LMM_MEM_CPY_S(              &(stNvPsLoc.stGuti),
                                        sizeof(NAS_MM_GUTI_STRU),
                                        &(pstUeId->stGuti),
                                        sizeof(NAS_LMM_GUTI_STRU));


        NAS_LMM_MEM_CPY_S(              &(stNvPsLoc.stLastRegTai.stPlmnId),
                                        sizeof(NAS_MM_PLMN_ID_STRU),
                                        &(pstNetId->stPlmnId),
                                        sizeof(NAS_MM_PLMN_ID_STRU));

        NAS_LMM_MEM_CPY_S(              &(stNvPsLoc.stLastRegTai.stTac),
                                        sizeof(NAS_MM_TAC_STRU),
                                        &(pstNetId->stTac),
                                        sizeof(NAS_MM_TAC_STRU));

        stNvPsLoc.enUpdateState         = NAS_EMM_UPDATE_STAE;
    }
    else
    {
        NAS_LMM_MEM_SET_S(  &stNvPsLoc,
                            sizeof(LNAS_LMM_NV_EPS_LOC_STRU),
                            0,
                            sizeof(LNAS_LMM_NV_EPS_LOC_STRU));

        NAS_LMM_UndefPlmn(&stNvPsLoc.stLastRegTai.stPlmnId);
        NAS_LMM_UndefTac(&stNvPsLoc.stLastRegTai.stTac);

    }

    /* 如果NV项中保存的与本次要写入的完全相同，则无需写入 */
    if((0 == NAS_LMM_MEM_CMP( (const VOS_VOID *)pstLastPsLoc,
                              (const VOS_VOID *)&stNvPsLoc,
                              sizeof(LNAS_LMM_NV_EPS_LOC_STRU))))
    {
        NAS_LMM_NVIM_LOG_INFO("NAS_LMM_WriteNvPsLoc:  Don't need to write Nvim.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_WriteNvPsLoc_ENUM,LNAS_FUNCTION_LABEL1);
        return;
    }

    /*write new PS LOC to NVIM*/
    ulRst = NAS_LMM_NvimWrite(           EN_NV_ID_EPS_LOC,
                                        &stNvPsLoc,
                                        sizeof(LNAS_LMM_NV_EPS_LOC_STRU));
    if(EN_NV_OK != ulRst)
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_WriteNvPsLoc: nvim ERR!!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_WriteNvPsLoc_ENUM,LNAS_ERROR);
    }
    else
    {
        NAS_LMM_NVIM_LOG_INFO("NAS_LMM_WriteNvPsLoc:Write Nvim SUCC, update last write NV EPS LOC  info.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_WriteNvPsLoc_ENUM,LNAS_FUNCTION_LABEL2);

        /* 写NV成功需将本次写NV内容更新到上次写卡PS LOC信息中 */
        NAS_LMM_MEM_CPY_S(  pstLastPsLoc,
                            sizeof(LNAS_LMM_NV_EPS_LOC_STRU),
                            &stNvPsLoc,
                            sizeof(LNAS_LMM_NV_EPS_LOC_STRU));
    }

    return;
}


VOS_VOID  NAS_LMM_WriteSimPsLoc( VOS_VOID )
{

    LNAS_LMM_NV_EPS_LOC_STRU             stNvPsLoc;
    NAS_LMM_UEID_STRU                    *pstUeid;
    NAS_MM_GUTI_STRU                    *pstGuti;
    NAS_MM_NETWORK_ID_STRU              *pstNetId;

    NAS_LMM_NVIM_LOG_INFO("NAS_LMM_WriteSimPsLoc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_WriteSimPsLoc_ENUM,LNAS_ENTRY);

    NAS_LMM_MEM_SET_S(  &stNvPsLoc,
                        sizeof(LNAS_LMM_NV_EPS_LOC_STRU),
                        0,
                        sizeof(LNAS_LMM_NV_EPS_LOC_STRU));

    pstUeid                             = NAS_LMM_GetEmmInfoUeidAddr();
    pstGuti                             = NAS_LMM_GetEmmInfoUeidGutiAddr();
    pstNetId                            = NAS_LMM_GetEmmInfoNetInfoLastRegNetAddr();

    /*GUTI的填充*/
    if (NAS_NVIM_BIT_NO_SLCT == pstUeid->bitOpGuti)
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_WriteSimPsLoc : GUTI Invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_WriteSimPsLoc_ENUM,LNAS_FUNCTION_LABEL1);

        NAS_LMM_SetArrayAllBytesFF((VOS_UINT8 *)&stNvPsLoc.stGuti,
                                   sizeof(NAS_LMM_GUTI_STRU));
        stNvPsLoc.stGuti.stGutiHead.ucLenth = NAS_LMM_NVIM_GUTI_AND_OETOI_LEN;
        stNvPsLoc.stGuti.stGutiHead.ucOeToi = NAS_LMM_NVIM_GUTI_OETOI;

    }
    else
    {
        NAS_LMM_MEM_CPY_S(              &stNvPsLoc.stGuti,
                                        sizeof(NAS_MM_GUTI_STRU),
                                        pstGuti,
                                        sizeof(NAS_LMM_GUTI_STRU));
    }

    /*L.V.R TAI的填充*/
    if (NAS_NVIM_BIT_NO_SLCT == NAS_EMM_GetLVRTaiOpBit())
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_WriteSimPsLoc : L.V.R Invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_WriteSimPsLoc_ENUM,LNAS_FUNCTION_LABEL2);
        NAS_LMM_UndefPlmn(&stNvPsLoc.stLastRegTai.stPlmnId);
        NAS_LMM_UndefTac(&stNvPsLoc.stLastRegTai.stTac);
    }
    else
    {
        NAS_LMM_MEM_CPY_S(              &stNvPsLoc.stLastRegTai.stPlmnId,
                                        sizeof(NAS_MM_PLMN_ID_STRU),
                                        &(pstNetId->stPlmnId),
                                        sizeof(NAS_MM_PLMN_ID_STRU));

        NAS_LMM_MEM_CPY_S(              &stNvPsLoc.stLastRegTai.stTac,
                                        sizeof(NAS_MM_TAC_STRU),
                                        &(pstNetId->stTac),
                                        sizeof(NAS_MM_TAC_STRU));
    }

    /*EU的填写*/
    stNvPsLoc.enUpdateState             = NAS_EMM_UPDATE_STAE;

    /*write new PS LOC to USIM*/
    NAS_LMM_UsimFileWrite(USIMM_USIM_EFEPSLOCI_ID,
                          &stNvPsLoc,
                          sizeof(LNAS_LMM_NV_EPS_LOC_STRU));

    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_WriteEpsSecuContext
 Description     : 保存安全上下文到USIM或者NVIM中
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-2-26  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LMM_WriteEpsSecuContext( NAS_NV_ITEM_OP_TYPE_ENUM_UINT32 enOpType )
{
    VOS_UINT32                          ulRslt;

    NAS_LMM_NVIM_LOG_INFO("NAS_LMM_WriteEpsSecuContext enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_WriteEpsSecuContext_ENUM,LNAS_ENTRY);
    /* 勾出当前安全上下文 */
    NAS_EMM_SndOmLogEpsSecContextInfo();

    if (NAS_LMM_SIM_STATUS_UNAVAILABLE == NAS_LMM_GetSimState())
    {
        return ;
    }
    ulRslt = NAS_EMM_IsServiceAvailable(USIM_SVR_EPS_INFO);

    if (PS_USIM_SERVICE_AVAILIABLE == ulRslt)
    {
        /* 向USIM写入EPS SECURITY CONTEXT */
        NAS_LMM_WriteSimEpsSecurityContext(enOpType);
    }
    else
    {
        /*向NV中写入EPS SECURITY CONTEXT*/
        NAS_LMM_WriteNvEpsSecurityContext(enOpType);
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_WritePsLoc
 Description     : 保存PS LOC信息到USIM或者NVIM中
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-2-26  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LMM_WritePsLoc
(
    NAS_NV_ITEM_OP_TYPE_ENUM_UINT32     enOpType
)
{
    VOS_UINT32                          ulRslt;

    NAS_LMM_NVIM_LOG_INFO("NAS_LMM_WritePsLoc enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_WritePsLoc_ENUM,LNAS_ENTRY);

    /* 上报EPS  LOC 信息 */
    NAS_EMM_SndOmLogEpsLocInfo();

    if (NAS_LMM_SIM_STATUS_UNAVAILABLE == NAS_LMM_GetSimState())
    {
        NAS_LMM_NVIM_LOG_INFO("NAS_LMM_WritePsLoc: USIM is unavailable!.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_WritePsLoc_ENUM,LNAS_FUNCTION_LABEL1);
        return;
    }
    ulRslt = NAS_EMM_IsServiceAvailable(USIM_SVR_EPS_INFO);
    if (PS_USIM_SERVICE_AVAILIABLE == ulRslt)
    {
        /*向USIM写入PS LOC*/
        NAS_LMM_WriteSimPsLoc();
    }
    else
    {
        /*向NV中写入PS LOC*/
        NAS_LMM_WriteNvPsLoc(enOpType);
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SetTinType
 Description     : 保存TIN信息到NVIM中
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    leili     00132387    2012-3-2        Draft  Enact
    2.    yanglei   00307272    2015-07-28      可维可测，上报紧急呼列表
*****************************************************************************/
VOS_VOID  NAS_EMM_SetTinType(MMC_LMM_TIN_TYPE_ENUM_UINT32 ulTinType)
{
    NAS_NVIM_TIN_INFO_STRU         stNvTinType;
    VOS_UINT32                          ulRslt;

    NAS_LMM_MEM_SET_S(  &stNvTinType,
                        sizeof(NAS_NVIM_TIN_INFO_STRU),
                        0,
                        sizeof(NAS_NVIM_TIN_INFO_STRU));

    /* 读全局变量中的TIN*/

    /*更新MML参数*/
    NAS_MML_SetTinType((VOS_UINT8)ulTinType);

    NAS_LMM_LogTinInfo(ulTinType,PS_PID_MM,PS_PID_MM);

    /* 如果是紧急注册过程中或者紧急注册，则直接退出，不写NV */
    if ((NAS_LMM_REG_STATUS_EMC_REGING == NAS_LMM_GetEmmInfoRegStatus())
         || (NAS_LMM_REG_STATUS_EMC_REGED == NAS_LMM_GetEmmInfoRegStatus()))
    {
        NAS_LMM_NVIM_LOG_INFO("NAS_EMM_SetTinType : Need not write nv!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SetTinType_ENUM,LNAS_FUNCTION_LABEL1);
        return ;
    }
    /*lint -e718*/
    /*lint -e732*/
    /*lint -e516*/
    /*lint -e746*/
    /*lint -e830*/
    ulRslt = LPs_NvimItem_Read(en_NV_Item_TIN_INFO, &stNvTinType, sizeof(NAS_NVIM_TIN_INFO_STRU));
    /*lint +e830*/
    /*lint +e746*/
    /*lint +e516*/
    /*lint +e732*/
    /*lint +e718*/
    if ((ERR_MSP_SUCCESS != ulRslt) || (MMC_LMM_TIN_INVALID < stNvTinType.ucTinType))
    {
        NAS_LMM_NVIM_LOG_INFO("NAS_EMM_SetTinType:read NVIM fail or Value Invalid!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SetTinType_ENUM,LNAS_FUNCTION_LABEL2);
    }

    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_SetTinType: read NV ITEM VALUE:IMSI = \n");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SetTinType_ENUM,LNAS_FUNCTION_LABEL3);
    NAS_COMM_PrintArray(                NAS_COMM_GET_MM_PRINT_BUF(),
                                        stNvTinType.aucImsi,
                                        NVIM_ITEM_MAX_IMSI_LEN);

    NAS_LMM_PUBM_LOG1_NORM("NAS_EMM_SetTinType: read NV ITEM VALUE:ulTinType = ",stNvTinType.ucTinType);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_SetTinType_ENUM,LNAS_EMM_TIN_TYPE,stNvTinType.ucTinType);

    /*填充 NV  TIN 结构*/
    stNvTinType.ucTinType = (VOS_UINT8)ulTinType;
    /*lint -e718*/
    /*lint -e746*/
    /*lint -e732*/
    /*lint -e516*/
    ulRslt = LPs_NvimItem_Write(en_NV_Item_TIN_INFO, &stNvTinType, sizeof(NAS_NVIM_TIN_INFO_STRU));
    /*lint +e516*/
    /*lint +e732*/
    /*lint +e746*/
    /*lint +e718*/
    if (ERR_MSP_SUCCESS != ulRslt)
    {
        NAS_LMM_NVIM_LOG_INFO("NAS_EMM_SetTinType:write NVIM fail!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SetTinType_ENUM,LNAS_FAIL);
    }


    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_SetTinType: write NV ITEM VALUE:IMSI = \n");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SetTinType_ENUM,LNAS_FUNCTION_LABEL4);
    NAS_COMM_PrintArray(                NAS_COMM_GET_MM_PRINT_BUF(),
                                           stNvTinType.aucImsi,
                                           NAS_MML_MAX_IMSI_LEN);

    NAS_LMM_PUBM_LOG1_NORM("NAS_EMM_SetTinType: write NV ITEM VALUE:ulTinType = ",stNvTinType.ucTinType);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_SetTinType_ENUM,LNAS_FUNCTION_LABEL5,stNvTinType.ucTinType);


    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_WriteNvMmInfo
 Description     : 写入EMM NV相关信息
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.luojian 00107747      2009-4-17  Draft Enact
    2.leili 00132387        2010-01-18 modify
*****************************************************************************/
VOS_VOID NAS_EMM_WriteNvMmInfo(VOS_VOID)
{
    if (NAS_LMM_SIM_STATUS_AVAILABLE == NAS_LMM_GetSimState())
    {
        /*保存安全上下文*/
        NAS_LMM_WriteEpsSecuContext(NAS_NV_ITEM_UPDATE);

        /* 判断没有放到函数NAS_LMM_WritePsLoc中来做，是由于紧急注册被拒或者尝试
           次数达到5次时还是要删除参数 ，协议只规定是紧急注册成功后才不写卡或者
           NV项 */
        if ((NAS_LMM_REG_STATUS_EMC_REGING != NAS_LMM_GetEmmInfoRegStatus())
            && (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus()))
        {
            /*保存PS LOC信息*/
            NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
        }


        /*GU维护，L不再 写NV*/
        /*NAS_LMM_WriteGuUeMode();*/
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_GetImeisvFromImei
 Description     : 开机，根据IMEI计算IMEISV
 Input           :
 Return          :
 History         :
    1.zhengjunyan 2009.05.11 New Draft
    2.yangfan 00159566    2010-03-24  固定了IMEI,IMEISV的长度

*****************************************************************************/
VOS_VOID NAS_LMM_GetImeisvFromImei(VOS_VOID)
{

    VOS_UINT8                           aucImeiSvn[4] = {0,0,0,0};

    if (NAS_EMM_BIT_SLCT != NAS_LMM_GetEmmInfoUeidAddr()->bitOpImei)
    {
        NAS_LMM_ReadNvimImei();
    }

    NAS_LMM_GetEmmInfoUeidAddr()->bitOpImeisv   = NAS_EMM_BIT_SLCT;
    NAS_LMM_MEM_CPY_S(                  NAS_LMM_GetEmmInfoUeidImeisvAddr(),
                                        NAS_MM_MAX_UEID_BUF_SIZE,
                                        NAS_LMM_GetEmmInfoUeidImeiAddr(),
                                        NAS_MM_MAX_UEID_BUF_SIZE);
    NAS_LMM_GetEmmInfoUeidAddr()->aucImeisv[0] =  0x09; /*长度为固定值9*/
    NAS_LMM_GetEmmInfoUeidAddr()->aucImeisv[1] &= 0xF0;
    NAS_LMM_GetEmmInfoUeidAddr()->aucImeisv[1] |= 0x03;
    NAS_LMM_GetEmmInfoUeidAddr()->aucImeisv[8] &= 0x0F;
    NAS_LMM_GetEmmInfoUeidAddr()->aucImeisv[9] = 0xF0;

    /* 获取IMEISV的内容 */
    /*lint -e516*/
    if (NV_OK != NVM_Read(en_NV_Item_Imei_Svn,
                   aucImeiSvn, sizeof(aucImeiSvn)))
    {
       NAS_LMM_PUBM_LOG_WARN("NAS_LMM_GetImeisvFromImei:Read Nvim Failed");
       TLPS_PRINT2LAYER_WARNING(NAS_LMM_GetImeisvFromImei_ENUM,LNAS_FAIL);
       return;
    }
    /*lint +e516*/

    /* NV项有效,则更新 */
    if (VOS_TRUE == aucImeiSvn[0])
    {
        NAS_LMM_GetEmmInfoUeidAddr()->aucImeisv[8] &= 0x0F;
        NAS_LMM_GetEmmInfoUeidAddr()->aucImeisv[9] &= 0x00;
        NAS_LMM_GetEmmInfoUeidAddr()->aucImeisv[8] |= (VOS_UINT8)(aucImeiSvn[1] << NAS_LMM_MOVEMENT_4_BITS);
        NAS_LMM_GetEmmInfoUeidAddr()->aucImeisv[9] |= (aucImeiSvn[2] | 0xF0);
    }

     /* 打印获取到的IMEISV值 */
    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_GetImeisvFromImei: IMEISV value is :");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_GetImeisvFromImei_ENUM,LNAS_FUNCTION_LABEL1);
    NAS_COMM_PrintArray(NAS_COMM_GET_MM_PRINT_BUF(),
                   NAS_LMM_GetEmmInfoUeidImeisvAddr(),
                   NAS_MM_MAX_UEID_BUF_SIZE);

    return;
}



/***************************************************************************
 Function Name  :NAS_EMM_GetEmmGlobleAddr
 Discription    :用于调用其他模块的全局变量
 Input          :
 Output         : None
 Return         : None
 History:
      1.  yangfan  2009-10-19  Draft Enact
*****************************************************************************/
VOS_UINT32  * NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_PARA_ENUM_UINT32 ulGlobleParaName)
{
    VOS_UINT32  * pucGlobleAddr;

    /* PRINT */

    switch(ulGlobleParaName )
    {
        case    NAS_LMM_GLOBLE_PARA_IMSI:
            pucGlobleAddr = (VOS_VOID * )NAS_LMM_GetEmmInfoUeidImsiAddr();
            break;

        case    NAS_LMM_GLOBLE_PARA_UEID:
            pucGlobleAddr = (VOS_VOID * )NAS_LMM_GetEmmInfoUeidAddr();
            break;

        case    NAS_LMM_GLOBLE_PARA_MNC_LEN:
            pucGlobleAddr = (VOS_VOID * )NAS_LMM_GetEmmInfoUeidImsiMncLenAddr();
            break;

        case    NAS_LMM_GLOBLE_FORB_TA_FOR_ROAMING:
            pucGlobleAddr = (VOS_VOID * )NAS_LMM_GetEmmInfoNetInfoForbTaForRoamAddr();
            break;
        case    NAS_LMM_GLOBLE_FORB_TA_FOR_RPOS:
            pucGlobleAddr = (VOS_VOID * )NAS_LMM_GetEmmInfoNetInfoForbTaForRposAddr();
            break;
        case    NAS_LMM_GLOBLE_PRESENT_NET_ID:
            pucGlobleAddr = (VOS_VOID * )NAS_LMM_GetEmmInfoNetInfoPresentNetAddr();
            break;
        case    NAS_LMM_GLOBLE_NET_INFO:
            pucGlobleAddr = (VOS_VOID * )NAS_LMM_GetEmmInfoNetInfoAddr();
            break;

        case    NAS_LMM_GLOBLE_TA_LIST:
            pucGlobleAddr = (VOS_VOID * )NAS_LMM_GetEmmInfoNetInfoTaiListAddr();
            break;

        default :
            pucGlobleAddr = VOS_NULL;
            break;
    }

    return pucGlobleAddr;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SendIntraConn2IdleReq
 Description     : 发送内部消息INTRA_CONN2IDLE_REQ
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2009-9-29  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SendIntraConn2IdleReq( VOS_VOID )
{
    NAS_EMM_INTRA_CONN2IDLE_REQ_STRU   *pIntraConn2IdleReq = NAS_LMM_NULL_PTR;
    VOS_UINT32                          ulLen;

    /*确定消息长度*/
/*    ulLen = NAS_EMM_GIM_VOS_MSG_HEADER_LEN + NAS_EMM_MSG_ID_LEN;*/
    ulLen = sizeof(NAS_EMM_INTRA_CONN2IDLE_REQ_STRU);

    /*分配空间*/
    pIntraConn2IdleReq  = (VOS_VOID *)NAS_LMM_GetSendIntraMsgBuffAddr(ulLen);
    if(NAS_EMM_NULL_PTR == pIntraConn2IdleReq)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_SendIntraConn2IdleReq: INTRA MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SendIntraConn2IdleReq_ENUM,LNAS_NULL_PTR);
        return;
    }

    /* 打包VOS消息头 */
    NAS_EMM_INTRA_MSG_HEADER(pIntraConn2IdleReq,(ulLen-NAS_EMM_GIM_VOS_MSG_HEADER_LEN));

    /* 填充DOPRA消息ID    */
    pIntraConn2IdleReq->ulMsgId = ID_NAS_LMM_INTRA_CONN2IDLE_REQ;

    /*发送内部消息入队列*/
    NAS_EMM_SEND_INTRA_MSG(pIntraConn2IdleReq);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_CommProcConn2Ilde
 Description     : 函数执行两个动作:
                   1.发送内部消息INTRA_CONN2IDLE_REQ
                   2.更新连接状态
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2009-11-9  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_CommProcConn2Ilde( VOS_VOID )
{
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_CommProcConn2Ilde enter!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_CommProcConn2Ilde_ENUM,LNAS_ENTRY);

    /*如果当前连接状态不是IDLE，则向 MMC上报*/
    if((NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
        && (NAS_EMM_CONN_WAIT_SYS_INFO != NAS_EMM_GetConnState()))
    {
        NAS_EMM_SendMmcStatusInd(MMC_LMM_STATUS_TYPE_CONN_STATE,
                                 MMC_LMM_CONN_IDLE);

        #if (FEATURE_LPP == FEATURE_ON)
        NAS_LMM_SndLcsRelInd();
        #endif
    }

    if((NAS_EMM_CONN_SIG == NAS_EMM_GetConnState())
        || (NAS_EMM_CONN_DATA == NAS_EMM_GetConnState())
        || (NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
        || (NAS_EMM_CONN_WAIT_SYS_INFO == NAS_EMM_GetConnState()))
    {
        /*将连接状态设置成NAS_EMM_CONN_WAIT_SYS_INFO， 当前RRC当前的链路出现问题
          或者主动释放链路，RRC都要重新搜网，LNAS等待LRRC上报系统消息。
        */
        NAS_EMM_SetConnState(NAS_EMM_CONN_WAIT_SYS_INFO);
    }
    else
    {
        /* 把RRC连接状态设置为IDLE */
        NAS_EMM_SetConnState(NAS_EMM_CONN_IDLE);
    }

    if (NAS_LMM_CONNECTION_CLIENT_ID_SMS == NAS_LMM_GetConnectionClientId())
    {
        NAS_LMM_SndLmmSmsErrInd(LMM_SMS_ERR_CAUSE_OTHERS);
        NAS_LMM_SetConnectionClientId(NAS_LMM_CONNECTION_CLIENT_ID_NULL);
    }
    /*连接态从CONN进入IDLE，导致当前安全上下文状态变化*/
    NAS_EMM_ConnToIdleTransSecuSta();

    /*发送内部消息:INTRA_CONN2IDLE_REQ*/
    NAS_EMM_SendIntraConn2IdleReq();

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_SaveAppMsgPara
 Description     : 设置App消息信息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.y00159566      2010-3-15  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_SaveAppMsgPara( VOS_UINT32 ulMsgId, VOS_UINT32 ulOpId)
{
    g_stEmmInfo.bitOpAppPara         = NAS_EMM_BIT_SLCT;
    g_stEmmInfo.stAppPara.ulMsgId    = ulMsgId;
    g_stEmmInfo.stAppPara.ulOpId     = ulOpId;

    return;
}



VOS_VOID  NAS_EMM_ClearAppMsgPara( VOS_VOID )
{
    /*清空APP参数*/
    g_stEmmInfo.bitOpAppPara       = NAS_EMM_BIT_NO_SLCT;

    NAS_LMM_MEM_SET_S(  &g_stEmmInfo.stAppPara,
                        sizeof(NAS_LMM_APP_PARA_STRU),
                        0,
                        sizeof(NAS_LMM_APP_PARA_STRU));
}


VOS_UINT32  NAS_EMM_CheckAppMsgPara( VOS_UINT32 ulMsgId )
{
    if ((ulMsgId              == g_stEmmInfo.stAppPara.ulMsgId)
        && (NAS_EMM_BIT_SLCT  == g_stEmmInfo.bitOpAppPara))
    {
        return                   VOS_OK;
    }
    else
    {
        return                   VOS_ERR;
    }
}


VOS_UINT32  NAS_EMM_GetAppMsgOpId( VOS_VOID )
{
    return                      g_stEmmInfo.stAppPara.ulOpId;
}

/*****************************************************************************
 Function Name   : NAS_LMM_CountSysInfo
 Description     : 用于记录等待RRC EstCnf/RelCnf/RelInd 时收到SysInfo次数
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.y00159566     2010-1-13  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LMM_CountSysInfo( VOS_UINT16 usSubState )
{
    NAS_LMM_SYSINFO_COUNT_STRU           *pstSysInfoCnt;

    pstSysInfoCnt                      = NAS_EMM_GetSysInfCntAddr();

    switch( usSubState )
    {
        case    EMM_SS_RRC_CONN_WAIT_EST_CNF:
            pstSysInfoCnt->ulEstCnfCount++;
            NAS_LMM_PUBM_LOG1_INFO("MsRrcConnEstInitSsWaitRrcEstCnf: Receive SysInfo ",pstSysInfoCnt->ulEstCnfCount);
            TLPS_PRINT2LAYER_INFO1(NAS_LMM_CountSysInfo_ENUM,LNAS_FUNCTION_LABEL1,pstSysInfoCnt->ulEstCnfCount);
            break;

        case    EMM_SS_RRC_CONN_WAIT_REL_CNF:
            pstSysInfoCnt->ulRelCnfCount++;
            NAS_LMM_PUBM_LOG1_INFO("MsRrcConnRelInitSsWaitRrcRelCnf: Receive SysInfo ",pstSysInfoCnt->ulRelCnfCount);
            TLPS_PRINT2LAYER_INFO1(NAS_LMM_CountSysInfo_ENUM,LNAS_FUNCTION_LABEL2,pstSysInfoCnt->ulRelCnfCount);
            break;

        /*case    EMM_SS_ATTACH_WAIT_RRC_REL_IND:
            pstSysInfoCnt->ulRegInitRrcRelIndCount++;
            NAS_LMM_PUBM_LOG1_INFO("MsRegInitSsWaitRrcRelInd: Receive SysInfo ",pstSysInfoCnt->ulRegInitRrcRelIndCount);
            break;*/


        default :
            NAS_LMM_PUBM_LOG_ERR("NAS_LMM_CountSysInfo,Error State!");
            TLPS_PRINT2LAYER_ERROR(NAS_LMM_CountSysInfo_ENUM,LNAS_ERROR);
            break;
    }

}

/*****************************************************************************
 Function Name   : NAS_LMM_EmmInfoInit
 Description     :
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.y00159566      2010-3-2  Draft Enact
    2.z00148421      2010-3-24 安全重构:删除NAS_EMM_PubmInfoSecuParaInit
    3.y00159566      2010-5-31 Modify
*****************************************************************************/
VOS_VOID  NAS_LMM_EmmInfoInit( VOS_VOID )
{
    NAS_EMM_PubmInfoUeIdInit();
    NAS_EMM_PubmInfoNetInfoInit();
    NAS_EMM_PubmInfoSupCodecListInit();
    NAS_EMM_PubmInfoBearerContextInit();
    NAS_EMM_PubmInfoDrxInit();

    /*H41410 UE MODE BEGIN*/
    NAS_EMM_PubmInfoUeModeInit();
    /*H41410 UE MODE END*/

    /*根据IMSI的读取设置卡状态*/
    /* NAS_EMM_InitSimState();*/
    NAS_EMM_SetUsimState(NAS_LMM_SIM_STATUS_UNAVAILABLE);

    NAS_LMM_SetPsSimValidity(NAS_LMM_SIM_VALID);

    /* 开机参数赋值 */
    NAS_EMM_GetTransceiverType()        = NAS_EMM_TRANSCEIVER_TYPE_BUTT;
    NAS_LMM_GetCurGsmPrio()             = NAS_LMM_RAT_PRIO_BUTT;
    NAS_LMM_GetCurWcdmaPrio()           = NAS_LMM_RAT_PRIO_BUTT;
    NAS_LMM_GetCurLtePrio()             = NAS_LMM_RAT_PRIO_BUTT;
    NAS_LMM_SetTempEmmInfoTinType(MMC_LMM_TIN_BUTT);

    NAS_EMM_GetEmmInfoDamParaT3402Len() = NAS_LMM_TIMER_T3402_LEN;
    NAS_EMM_GetEmmInfoDamParaCserviceCnt() = 0;

    /*清除TAU_REQ发送失败原因是LRRC释放标识*/
    NAS_LMM_SetTauReqSndFailFlag(PS_FALSE);

    NAS_LMM_ModifyPtlTimer(TI_NAS_EMM_PTL_SER_BACKOFF_TIMER,NAS_LMM_TIMER_T3402_LEN);



    return;
}


VOS_VOID  NAS_EMM_ReadEmmNvim( VOS_VOID )
{
    /*无卡开机时需读取的基本基础的NV*/
    NAS_EMM_ReadNvimNoImsi();

}


VOS_VOID  NAS_EMM_ReadNvimNoImsi( VOS_VOID )
{
    /*read IMEI from NVIM*/
    NAS_LMM_ReadNvimImei();

    /*caculate Imeisv with IMEI*/
    NAS_LMM_GetImeisvFromImei();



    /*read UeNetCap from NVIM*/
    NAS_EMM_ReadNvUeNetCap();

    /*read ue operation mode from NVIM*/
    /*NAS_EMM_ReadNvUeOperationMode();*/

    /*read CsService from NVIM*/

    /*NAS_EMM_ReadNvCsService();*/


    /*read Voice Domain for E-UTRAN from NVIM*/
    NAS_EMM_ReadNvVoiceDomain();

    /* 从NV项中读取UE's setting，并设置到MML中 */
    NAS_EMM_ReadNvUeSetting();


    /*read ClassMark from NVIM*/
    /*NAS_EMM_ReadNvClassMark();*/

    /*read Drx from NVIM*/
    /*NAS_EMM_ReadNvDrx();*/

    /*read RaMod from NVIM*/
    NAS_EMM_ReadNvNasRelease();

    /*sunbing 49683 2013-10-21 VoLTE begin*/
    NAS_EMM_ReadNvCodecSupportList();
    /*sunbing 49683 2013-10-21 VoLTE end*/
    NAS_EMM_ReadNvConfigNwCause();

    NAS_LMM_ReadNvDamParaCServiceAndPlmnList();
    NAS_LMM_ReadNvLmmCommConfigPara();
    /*  LNAS功能开关NV读取 */
    NAS_LMM_ReadNvLmmSwitchPara();
    NAS_EMM_SndOmLogUeImportantCapabilityInfo();
    NAS_EMM_SndOmLogUeIdInfo();
    /* 勾出当前安全上下文 */
    NAS_EMM_SndOmLogEpsSecContextInfo();
    /* 勾出EPS LOC信息 */
    NAS_EMM_SndOmLogEpsLocInfo();
    NAS_LMM_SndOmStaticUeIdInfo();
}


/*****************************************************************************
 Function Name   : NAS_EMM_NoUsimInit
 Description     : 无卡、或读必读文件失败、超时后，认为无卡，则使用此函数。
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.y00159566      2010-3-3  Draft Enact
    2.z00148421      2010-3-24 安全模块重构
*****************************************************************************/
VOS_VOID  NAS_EMM_NoUsimInit( VOS_VOID )
{
    /* 删除不用变量 */

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_NoUsimInit IS ENTERED ");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_NoUsimInit_ENUM,LNAS_ENTRY);

    /****无卡环境下初始化EMM*****/
    /* 从NV中读取无卡状态下所需要的项 */
    NAS_EMM_ReadNvimNoImsi();

    /*为解决在工信部卡接口一致性测试时,测试时手机开机时设置PIN码,无卡开机进入此函数删除了NV中的安全上下文，用例失败,
      由于该NV各版本都是默认打开, 而且若再次插卡开机, 若IMSI不同的话会删除安全上下文, 所以为防止误把该NV关闭导致用例
      失败, 此处无卡删除安全上下文代码删除*/

    /*无卡场景下，不再删除NV中的PS LOC*/
    /*NAS_LMM_WriteNvPsLoc(0);*/

    NAS_EMM_PubmInfoNetInfoInit();
    NAS_EMM_SecuInit();

    return;

}


VOS_UINT32  NAS_LMM_CheckPlmnAct(VOS_UINT8 const *pucPlmn)
{

    if ((NAS_LMM_NULL == (pucPlmn[NAS_EMM_PLMNACT_IDEN] & NAS_LMM_BYTE_FF))
        && (NAS_LMM_NULL == (pucPlmn[NAS_EMM_PLMNACT_IDEN + 1] & NAS_LMM_BYTE_FF)))
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_CheckPlmnAct: PLMNAct is support");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_CheckPlmnAct_ENUM,LNAS_FUNCTION_LABEL1);
        return VOS_OK;
    }
    switch ( NAS_LMM_GetEmmInfoRaMod())
    {
        case    NAS_MM_RAT_LTE_FDD:
        case    NAS_MM_RAT_LTE_TDD:
            if (NAS_EMM_PLMNACT_LTE == (pucPlmn[NAS_EMM_PLMNACT_IDEN] & NAS_EMM_PLMNACT_LTE))
            {
                NAS_LMM_PUBM_LOG_INFO("NAS_LMM_CheckPlmnAct: PLMNAct: LTE");
                TLPS_PRINT2LAYER_INFO(NAS_LMM_CheckPlmnAct_ENUM,LNAS_FUNCTION_LABEL2);
                return VOS_OK;
            }
            break;

        case    NAS_MM_RAT_WCDMA:
        case    NAS_MM_RAT_GSM_GPRS:
            break;

        default:
            break;
    }

    NAS_LMM_PUBM_LOG_WARN("NAS_LMM_CheckPlmnAct: PLMNAct: NO LTE");
    TLPS_PRINT2LAYER_WARNING(NAS_LMM_CheckPlmnAct_ENUM,LNAS_FUNCTION_LABEL3);
    return VOS_ERR;

}


VOS_VOID NAS_EMM_ClearTaiList( VOS_VOID )
{
    NAS_LMM_GetEmmInfoNetInfoAddr()->bitOpTaiList  = NAS_EMM_BIT_NO_SLCT;

    /*删除TA LIST*/
    NAS_LMM_MEM_SET_S(  NAS_LMM_GetEmmInfoNetInfoTaiListAddr(),
                        sizeof(NAS_MM_TA_LIST_STRU),
                        0,
                        sizeof(NAS_EMM_TA_LIST_STRU));
}


VOS_VOID  NAS_EMM_ClearLVRTai( VOS_VOID )
{
    /*删除 L.V.R TAI*/
    NAS_LMM_GetEmmInfoNetInfoAddr()->bitOpLastRegNetId      = NAS_EMM_BIT_NO_SLCT;
    NAS_LMM_GetEmmInfoNetInfoLastRegNetAddr()->bitOpTac     = NAS_EMM_BIT_NO_SLCT;

    NAS_LMM_UndefPlmn(NAS_LMM_GetEmmInfoLastRegPlmnAddr());
    NAS_LMM_UndefTac(NAS_LMM_GetEmmInfoLastRegTacAddr());
    NAS_LMM_UndefCsgId(&(NAS_LMM_GetEmmInfoNetInfoLastRegNetAddr()->ulCsgId));
}



/*****************************************************************************
 Function Name   : NAS_EMM_SetLVRTacInvalid
 Description     : 拒绝后删除L.V.R TAI时,TAC设置为0xfffe,PLMN设置:如果当前L.V.R
                    有效,
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2012-5-9  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SetLVRTacInvalid( VOS_VOID )
{
    NAS_LMM_UndefTac(NAS_LMM_GetEmmInfoLastRegTacAddr());

    if (NAS_EMM_BIT_NO_SLCT == NAS_EMM_GetLVRTaiOpBit())
    {
        NAS_LMM_UndefPlmn(NAS_LMM_GetEmmInfoLastRegPlmnAddr());
    }
    return;
}




VOS_UINT32 NAS_EMM_GetLVRTaiOpBit(VOS_VOID)
{
    NAS_LMM_NETWORK_INFO_STRU            *pstNetInfo;
    VOS_UINT32                          ulRslt;

    pstNetInfo = NAS_LMM_GetEmmInfoNetInfoAddr();

    ulRslt = (pstNetInfo->bitOpLastRegNetId) && (pstNetInfo->stLastRegNetId.bitOpTac);

    return ulRslt;
}


VOS_VOID  NAS_EMM_SetLVRTai(const NAS_MM_NETWORK_ID_STRU *pstNetId)
{
    NAS_LMM_NETWORK_INFO_STRU            *pstNetInfo;

    pstNetInfo = NAS_LMM_GetEmmInfoNetInfoAddr();

    if (NAS_EMM_NULL_PTR == pstNetId)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_EMM_SetLVRTai: Point is null");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_SetLVRTai_ENUM,LNAS_NULL_PTR);

        return;
    }

    pstNetInfo->bitOpLastRegNetId       = NAS_EMM_BIT_SLCT;
    pstNetInfo->stLastRegNetId.bitOpTac = NAS_EMM_BIT_SLCT;

    NAS_LMM_MEM_CPY_S (                 &pstNetInfo->stLastRegNetId.stPlmnId,
                                        sizeof(NAS_MM_PLMN_ID_STRU),
                                        &pstNetId->stPlmnId,
                                        sizeof(NAS_MM_PLMN_ID_STRU));

    NAS_LMM_MEM_CPY_S (                 &pstNetInfo->stLastRegNetId.stTac,
                                        sizeof(NAS_MM_TAC_STRU),
                                        &pstNetId->stTac,
                                        sizeof(NAS_MM_TAC_STRU));
    return;
}


VOS_VOID  NAS_EMM_SetGuti
(
    const NAS_EMM_GUTI_STRU *pstGuti
)
{
    NAS_LMM_UEID_STRU                   *pstUeId;

    pstUeId = NAS_LMM_GetEmmInfoUeidAddr();

    if (NAS_EMM_NULL_PTR == pstGuti)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_EMM_SetGuti: Point is null");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_SetGuti_ENUM,LNAS_NULL_PTR);

        return;
    }

    pstUeId->bitOpGuti                  = NAS_EMM_BIT_SLCT;
    NAS_LMM_MEM_CPY_S (                 &(pstUeId->stGuti),
                                        sizeof(NAS_LMM_GUTI_STRU),
                                        pstGuti,
                                        sizeof(NAS_LMM_GUTI_STRU));
    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_UpdatePresentPlmnInfo
 Description     : 根据GUTI中的PLMN，决定是否更新当前PLMN，
                   如果二者不相同，将当前PLMN更新为GUTI中的PLMN
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151      2012-08-13  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_UpdatePresentPlmnInfo(VOS_VOID)
{
    VOS_UINT32                          ulCount          = 0;
    VOS_UINT32                          ulUpdateResult   = NAS_EMM_FAIL;
    NAS_LMM_UEID_STRU                  *pstMmUeId        = NAS_EMM_NULL_PTR;
    NAS_MM_PLMN_ID_STRU                *pstPresentPlmnId = NAS_EMM_NULL_PTR;
    NAS_MM_GUTI_STRU                   *pstGuti          = NAS_EMM_NULL_PTR;

    pstGuti          = NAS_LMM_GetEmmInfoUeidGutiAddr();
    pstMmUeId        = NAS_LMM_GetEmmInfoUeidAddr();
    pstPresentPlmnId = NAS_LMM_GetEmmInfoPresentPlmnAddr();

    /* 存在GUTI, 并且Present Plmn ID 与GUTI中的Plmn ID不同, 将Present Plmn ID更新成GUTI中的Plmn ID */
    if ( NAS_EMM_BIT_SLCT== pstMmUeId->bitOpGuti )
    {
        for ( ulCount = 0; ulCount < 3; ulCount++ )
        {
            if ( pstPresentPlmnId->aucPlmnId[ulCount] != pstGuti->stPlmnId.aucPlmnId[ulCount] )
            {
                pstPresentPlmnId->aucPlmnId[ulCount] = pstGuti->stPlmnId.aucPlmnId[ulCount];
                ulUpdateResult = NAS_EMM_SUCC;
            }
        }
    }

    return   ulUpdateResult;

}


/*****************************************************************************
 Function Name   : NAS_EMM_GetMmlFormatMcc
 Description     : 获取MML格式的MCC
 Input           : pstPlmnId
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010     2012-03-14     Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_GetMmlFormatMcc
(
    const NAS_MM_PLMN_ID_STRU             *pstPlmnId
)
{
    VOS_UINT32                          ulMcc       = NAS_EMM_NULL;
    VOS_UINT8                           ucMccDigit  = NAS_EMM_NULL;

    /* 获取MCC DIGIT1 */
    ucMccDigit  = pstPlmnId->aucPlmnId[0] & NAS_EMM_LOW_4_BIT;
    ulMcc       |=  ucMccDigit;

    /* 获取MCC DIGIT2 */
    ucMccDigit  = (pstPlmnId->aucPlmnId[0] & NAS_EMM_HIGH_4_BIT) >> NAS_EMM_MOVEMENT_4_BITS;
    ulMcc       |=  (ucMccDigit << NAS_EMM_MOVEMENT_8_BITS);

    /* 获取MCC DIGIT3 */
    ucMccDigit  = pstPlmnId->aucPlmnId[1] & NAS_EMM_LOW_4_BIT;
    ulMcc       |=  (ucMccDigit << NAS_EMM_MOVEMENT_16_BITS);

    return ulMcc;
}

/*****************************************************************************
 Function Name   : NAS_EMM_IsMccChanged
 Description     : 判断MCC是否发生变更
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010     2012-03-14     Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_IsMccChanged( VOS_VOID )
{
    NAS_MML_EMERGENCY_NUM_LIST_STRU    *pstMmlEmerNumLIst   = VOS_NULL_PTR;
    VOS_UINT32                          ulMcc               = NAS_EMM_NULL;

    pstMmlEmerNumLIst = NAS_EMM_GetEmergencyListFromMml();

    /* 获取当前PLMN中的MCC，格式与MML中一致 */
    ulMcc = NAS_EMM_GetMmlFormatMcc(NAS_LMM_GetEmmInfoPresentPlmnAddr());

    /* 判断当前网络PLMN中的MCC与MML中存储的MCC是否一致 */
    if (ulMcc == (pstMmlEmerNumLIst->ulMcc & NAS_EMM_LOW_3_BYTE_F))
    {
        return VOS_FALSE;
    }
    return VOS_TRUE;
}
/*****************************************************************************
 Function Name   : NAS_EMM_IsUSAMcc
 Description     : 判断MCC是否代表美国,MCC310-MCC316都代表美国
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen 00209181     2014-09-04     Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_IsUSAMcc(VOS_UINT32 ulMcc)
{
    if ((ulMcc & NAS_EMM_FIRST_BYTE_F) == 0x03)
    {
        if (((ulMcc & NAS_EMM_SECOND_BYTE_F) >> NAS_EMM_MOVEMENT_8_BITS) == 0x01)
        {
            if (((ulMcc & NAS_EMM_THIRD_BYTE_F)>> NAS_EMM_MOVEMENT_16_BITS) < 0x07)
            {
                return VOS_TRUE;
            }
        }
    }
    return VOS_FALSE;
}
/*****************************************************************************
 Function Name   : NAS_EMM_IsIndiaMcc
 Description     : 判断MCC是否是印度MCC，MCC404-MCC406都代表印度
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen 00209181 2014-09-04     Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_IsIndiaMcc(VOS_UINT32 ulMcc)
{
    if ((ulMcc & NAS_EMM_FIRST_BYTE_F) == 0x04)
    {
        if (((ulMcc & NAS_EMM_SECOND_BYTE_F) >> NAS_EMM_MOVEMENT_8_BITS) == 0x00)
        {
            if ((((ulMcc & NAS_EMM_THIRD_BYTE_F) >> NAS_EMM_MOVEMENT_16_BITS) > 0x03) &&
                (((ulMcc & NAS_EMM_THIRD_BYTE_F) >> NAS_EMM_MOVEMENT_16_BITS) < 0x07) )
            {
                return VOS_TRUE;
            }
        }
    }
    return VOS_FALSE;
}
/*****************************************************************************
 Function Name   : NAS_EMM_IsCountryChanged
 Description     : 判断国家是否发生变化
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen 00209181 2014-09-04     Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_EMM_IsCountryChanged()
{
    NAS_MML_EMERGENCY_NUM_LIST_STRU    *pstMmlEmerNumLIst   = VOS_NULL_PTR;
    VOS_UINT32                          ulMcc               = NAS_EMM_NULL;

    pstMmlEmerNumLIst = NAS_EMM_GetEmergencyListFromMml();

    /* 获取当前PLMN中的MCC，格式与MML中一致 */
    ulMcc = NAS_EMM_GetMmlFormatMcc(NAS_LMM_GetEmmInfoPresentPlmnAddr());

    /* 判断当前网络PLMN中的MCC和MML中存储的MCC是否都属于美国的MCC */
    if ((VOS_TRUE == NAS_EMM_IsUSAMcc(ulMcc)) &&
        (VOS_TRUE == NAS_EMM_IsUSAMcc(pstMmlEmerNumLIst->ulMcc)))
    {
        return VOS_FALSE;
    }
    /* 判断当前网络PLMN中的MCC和MML中存储的MCC是否都属于印度的MCC */
    if ((VOS_TRUE == NAS_EMM_IsIndiaMcc(ulMcc)) &&
        (VOS_TRUE == NAS_EMM_IsIndiaMcc(pstMmlEmerNumLIst->ulMcc)))
    {
        return VOS_FALSE;
    }

    /* 判断当前网络PLMN中的MCC与MML中存储的MCC是否一致 */
    if (ulMcc == (pstMmlEmerNumLIst->ulMcc & NAS_EMM_LOW_3_BYTE_F))
    {
        return VOS_FALSE;
    }
    return VOS_TRUE;
}

/*****************************************************************************
 Function Name   : NAS_EMM_PrintEmergencyList
 Description     : 打印紧急呼号码列表信息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong 00150010     2012-03-15     Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_PrintEmergencyList
(
    NAS_MML_EMERGENCY_NUM_LIST_STRU    *pstMmlEmerNumList
)
{
    VOS_UINT32                          ulMcc           = NAS_EMM_NULL;
    VOS_UINT8                           ucMccDigit      = NAS_EMM_NULL;
    VOS_UINT32                          ulLoop          = NAS_EMM_NULL;
    VOS_UINT32                          ulLoop2         = NAS_EMM_NULL;
    NAS_MML_EMERGENCY_NUM_STRU         *pstMmlEmerNum   = VOS_NULL_PTR;

    if(NULL == pstMmlEmerNumList)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_PrintEmergencyList: NULL Input!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_PrintEmergencyList_ENUM,LNAS_NULL_PTR);
        return;
    }

    /* 打印MCC信息 */
    ulMcc = pstMmlEmerNumList->ulMcc;
    ucMccDigit = ulMcc & NAS_EMM_FIRST_BYTE_F;
    NAS_LMM_PUBM_LOG1_NORM("MCC DIGIT1: ",ucMccDigit);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_PrintEmergencyList_ENUM,LNAS_FUNCTION_LABEL1,ucMccDigit);

    ucMccDigit = (ulMcc & NAS_EMM_SECOND_BYTE_F) >> NAS_EMM_MOVEMENT_8_BITS;
    NAS_LMM_PUBM_LOG1_NORM("MCC DIGIT2: ",ucMccDigit);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_PrintEmergencyList_ENUM,LNAS_FUNCTION_LABEL2,ucMccDigit);

    ucMccDigit = (ulMcc & NAS_EMM_THIRD_BYTE_F) >> NAS_EMM_MOVEMENT_16_BITS;
    NAS_LMM_PUBM_LOG1_NORM("MCC DIGIT3: ",ucMccDigit);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_PrintEmergencyList_ENUM,LNAS_FUNCTION_LABEL3,ucMccDigit);

    /* 打印紧急呼号码列表 */
    NAS_LMM_PUBM_LOG1_NORM("EMERGENCY NUM LIST AMOUT: ",pstMmlEmerNumList->ucEmergencyNumber);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_PrintEmergencyList_ENUM,LNAS_FUNCTION_LABEL4,pstMmlEmerNumList->ucEmergencyNumber);

    for (ulLoop = NAS_EMM_NULL; ulLoop < pstMmlEmerNumList->ucEmergencyNumber; ulLoop++)
    {
        pstMmlEmerNum = &pstMmlEmerNumList->aucEmergencyList[ulLoop];

        NAS_LMM_PUBM_LOG1_NORM("EMER NUM INFO",ulLoop);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_PrintEmergencyList_ENUM,LNAS_FUNCTION_LABEL5,ulLoop);

        NAS_LMM_PUBM_LOG1_NORM("EMER NUM CATOGORY: ",pstMmlEmerNum->ucCategory);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_PrintEmergencyList_ENUM,LNAS_FUNCTION_LABEL6,pstMmlEmerNum->ucCategory);

        for (ulLoop2 = NAS_EMM_NULL; ulLoop2 < pstMmlEmerNum->ucEmcNumLen; ulLoop2++)
        {
            NAS_LMM_PUBM_LOG1_NORM("EMER NUM : ",pstMmlEmerNum->aucEmcNum[ulLoop2]);
            TLPS_PRINT2LAYER_INFO1(NAS_EMM_PrintEmergencyList_ENUM,LNAS_FUNCTION_LABEL7,pstMmlEmerNum->aucEmcNum[ulLoop2]);
        }
    }
}
/*****************************************************************************
 Function Name   : NAS_EMM_GetEmergencyListFromMml
 Description     : 从MML中读取紧急呼号码列表信息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong 00150010     2012-03-15     Draft Enact

*****************************************************************************/
NAS_MML_EMERGENCY_NUM_LIST_STRU*  NAS_EMM_GetEmergencyListFromMml( VOS_VOID )
{
    NAS_MML_EMERGENCY_NUM_LIST_STRU    *pstMmlEmerNumList = VOS_NULL_PTR;
    #ifndef __PS_WIN32_RECUR__
    pstMmlEmerNumList = NAS_MML_GetEmergencyNumList();

    /* 打印从MML读取的紧急呼号码列表信息 */
    NAS_EMM_PrintEmergencyList(pstMmlEmerNumList);

    NAS_LMM_LogEmergencyNumListInfo(pstMmlEmerNumList,WUEPS_PID_MMC,PS_PID_MM);

    #else
    pstMmlEmerNumList = Stub_NAS_MML_GetEmergencyNumList();
    #endif
    return pstMmlEmerNumList;
}
/*****************************************************************************
 Function Name   : NAS_EMM_SetEmergencyList2Mml
 Description     : 将紧急呼号码列表设置到MML
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong    00150010    2012-03-14      Draft Enact
    2.yanglei   00307272    2015-07-28      可维可测，上报紧急呼列表

*****************************************************************************/
VOS_VOID  NAS_EMM_SetEmergencyList2Mml
(
    const NAS_MM_PLMN_ID_STRU             *pstCurPlmnId,
    const NAS_LMM_EMERGENCY_NUM_LIST_STRU *pstEmerNumList
)
{
    VOS_UINT32                          ulMcc           = NAS_EMM_NULL;
    NAS_MML_EMERGENCY_NUM_LIST_STRU     stMmlEmerNumList= {NAS_EMM_NULL};

    /* 取出当前PLMN中的MCC，并转化为MML中MCC的格式 */
    ulMcc = NAS_EMM_GetMmlFormatMcc(pstCurPlmnId);

    stMmlEmerNumList.ulMcc              = ulMcc;
    stMmlEmerNumList.ucEmergencyNumber  = pstEmerNumList->ucEmergencyNumAmount;
    NAS_LMM_MEM_CPY_S(  stMmlEmerNumList.aucEmergencyList,
                        sizeof(NAS_MML_EMERGENCY_NUM_STRU) * NAS_MML_EMERGENCY_NUM_LIST_MAX_RECORDS,
                        pstEmerNumList->astEmergencyNumList,
                        sizeof(LMM_MM_EMERGENCY_NUM_STRU) * NAS_MML_EMERGENCY_NUM_LIST_MAX_RECORDS);

    /* 打印写入MML的紧急呼列表信息 */
    NAS_EMM_PrintEmergencyList(&stMmlEmerNumList);

    NAS_MML_SetEmergencyNumList(&stMmlEmerNumList);

    NAS_LMM_LogEmergencyNumListInfo(&stMmlEmerNumList,PS_PID_MM,PS_PID_MM);
}

/*****************************************************************************
 Function Name   : NAS_EMM_ClearEmergencyList
 Description     : 清除紧急呼号码列表
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong 00150010     2012-03-14     Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_ClearEmergencyList( VOS_VOID )
{
    NAS_LMM_EMERGENCY_NUM_LIST_STRU      stEmerNumListTmp   = {NAS_EMM_NULL};

    /* 清除MML中的紧急呼号码列表 */
    NAS_EMM_SetEmergencyList2Mml(   NAS_LMM_GetEmmInfoPresentPlmnAddr(),
                                    &stEmerNumListTmp);
}


/*****************************************************************************
 Function Name   : NAS_EMM_SetEmergencyList
 Description     : 设置Emergency number list
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2011-7-4      Draft Enact
    2.lihong 00150010     2012-02-28    Modify

*****************************************************************************/
VOS_VOID  NAS_EMM_SetEmergencyList
(
    VOS_UINT32                             ulOpEmerList,
    const NAS_LMM_EMERGENCY_NUM_LIST_STRU *pstEmerNumList
)
{
    NAS_LMM_PUB_INFO_STRU               *pstPubInfo = VOS_NULL_PTR;

    pstPubInfo = NAS_LMM_GetEmmInfoAddr();

    if (NAS_EMM_NULL_PTR == pstEmerNumList)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_EMM_SetEmergencyList: Point is null");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_SetEmergencyList_ENUM,LNAS_NULL_PTR);

        return;
    }

    if (NAS_EMM_BIT_SLCT == ulOpEmerList)
    {
        /* 将紧急呼号码列表设置到MML */
        NAS_EMM_SetEmergencyList2Mml(   &pstPubInfo->stNetInfo.stPresentNetId.stPlmnId,
                                        pstEmerNumList);
        return ;
    }

    /* 如果空口没有携带紧急呼号码列表，则比较当前PLMN中的MCC是否变更，若发生变更，
       则设置紧急呼号码列表个数为0 */
    /* The emergency number(s) received in the Emergency Number List IE are valid only in networks
        in the same country as the cell on which this IE is received.    */
    if ((NAS_RELEASE_R11 && (VOS_TRUE == NAS_EMM_IsCountryChanged()))
          || (VOS_TRUE == NAS_EMM_IsMccChanged()))
    {
        NAS_EMM_ClearEmergencyList();
        return ;
    }
}


/*****************************************************************************
 Function Name   : NAS_EMM_SetEpsNetFeature
 Description     : 设置EPS network feature support
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2011-7-5      Draft Enact
    2.lihong 00150010     2012-02-27    Modify

*****************************************************************************/
VOS_VOID  NAS_EMM_SetEpsNetFeature
(
    VOS_UINT32                          ulOpNetFeature,
    VOS_UINT8                           ucNetFeature
)
{
    NAS_LMM_PUB_INFO_STRU               *pstPubInfo = VOS_NULL_PTR;

    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_SetEpsNetFeature is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SetEpsNetFeature_ENUM,LNAS_ENTRY);

    pstPubInfo = NAS_LMM_GetEmmInfoAddr();

    if (NAS_EMM_BIT_SLCT == ulOpNetFeature)
    {
        pstPubInfo->bitOpNetFeature         = NAS_EMM_BIT_SLCT;
        pstPubInfo->ucNetFeature            = ucNetFeature;
    }
    else
    {
        pstPubInfo->bitOpNetFeature         = NAS_EMM_BIT_NO_SLCT;
        pstPubInfo->ucNetFeature            = NAS_EMM_NULL;
    }

    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_SetAddUpdateRslt
 Description     : 设置Additional update result
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2011-7-5      Draft Enact
    2.lihong 00150010     2012-02-27    Modify

*****************************************************************************/
VOS_VOID  NAS_EMM_SetAddUpdateRslt
(
    VOS_UINT32                                  ulOpAddUpdateRslt,
    NAS_LMM_ADDITIONAL_UPDATE_RSLT_ENUM_UINT32  enAddUpdateRslt
)
{
    NAS_LMM_PUB_INFO_STRU              *pstEmmInfo = VOS_NULL_PTR;

    pstEmmInfo = NAS_LMM_GetEmmInfoAddr();

    /* ATTACH ACP或者TAU ACCEPT携带Additional update result,更新Additional update
       result到全局变量中 */
    if (NAS_EMM_BIT_SLCT == ulOpAddUpdateRslt)
    {
        NAS_LMM_PUBM_LOG1_NORM("NAS_EMM_SetAddUpdateRslt:enAddUpdateRslt = ,",
                               enAddUpdateRslt);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_SetAddUpdateRslt_ENUM,LNAS_EMM_ADD_UPDATE_RST,
                               enAddUpdateRslt);

        pstEmmInfo->enAdditionUpRslt = enAddUpdateRslt;
        /*NAS_MML_SetAdditionUpdateRslt((VOS_UINT8)enAddUpdateRslt);*/
        return ;
    }

    /* 如果UE能力不支持CSFB，只支持SMS ONLY，则即使ATTACH ACCPET中没有携带
       Additional update result信元，也要将EMM INFO全局变量中的Additional update
       result值设为SMS ONLY */
    if (NAS_LMM_CS_SERVICE_SMS_ONLY == NAS_EMM_GetCsService())
    {
        NAS_LMM_PUBM_LOG1_NORM("NAS_EMM_SetAddUpdateRslt:enAddUpdateRslt = ,",
                               NAS_MML_ADDITION_UPDATE_RSLT_SMS_ONLY);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_SetAddUpdateRslt_ENUM,LNAS_FUNCTION_LABEL1,
                               NAS_MML_ADDITION_UPDATE_RSLT_SMS_ONLY);

        pstEmmInfo->enAdditionUpRslt = NAS_LMM_ADDITIONAL_UPDATE_SMS_ONLY;
        /*NAS_MML_SetAdditionUpdateRslt(NAS_MML_ADDITION_UPDATE_RSLT_SMS_ONLY);*/
    }
    else
    {
        NAS_LMM_PUBM_LOG1_NORM("NAS_EMM_SetAddUpdateRslt:enAddUpdateRslt = ,",
                               NAS_MML_ADDITION_UPDATE_RSLT_BUTT);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_SetAddUpdateRslt_ENUM,LNAS_FUNCTION_LABEL2,
                               NAS_MML_ADDITION_UPDATE_RSLT_BUTT);

        pstEmmInfo->enAdditionUpRslt = NAS_LMM_ADDITIONAL_UPDATE_BUTT;
        /*NAS_MML_SetAdditionUpdateRslt(NAS_MML_ADDITION_UPDATE_RSLT_BUTT);*/
    }

    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_GetAddUpdateRslt
 Description     : 获取Additional update result
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2012-3-23      Draft Enact
*****************************************************************************/
NAS_LMM_ADDITIONAL_UPDATE_RSLT_ENUM_UINT32  NAS_EMM_GetAddUpdateRslt
(
   VOS_VOID
)
{
    NAS_LMM_ADDITIONAL_UPDATE_RSLT_ENUM_UINT32  enAddUpdateRslt;
    NAS_LMM_PUB_INFO_STRU                      *pstEmmInfo = VOS_NULL_PTR;

    pstEmmInfo = NAS_LMM_GetEmmInfoAddr();

    /*enAddUpdateRslt = NAS_MML_GetAdditionUpdateRslt();*/
    enAddUpdateRslt = pstEmmInfo->enAdditionUpRslt;

    NAS_LMM_PUBM_LOG1_NORM("NAS_EMM_GetAddUpdateRslt:enAddUpdateRslt = ",
                            enAddUpdateRslt);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_GetAddUpdateRslt_ENUM,LNAS_EMM_ADD_UPDATE_RST,
                            enAddUpdateRslt);

    NAS_LMM_LogAdditionUpdateRsltInfo(enAddUpdateRslt);
    return enAddUpdateRslt;
}

/* leili moidfy for isr end */



/*****************************************************************************
 Function Name   : NAS_EMM_GetCurrentTa
 Description     : 获取当前TAs
 Input           : NAS_MM_PLMN_ID_STRU stPlmnId
 Output          : None
 Return          : VOS_VOID

 History         :
    1.luojian 00107747      2008-10-15  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_GetCurrentTa( NAS_MM_TA_STRU *pstTa )
{
    NAS_EMM_NETWORK_ID_STRU             *pstAreaInfo;

    pstAreaInfo                         = NAS_LMM_GetEmmInfoNetInfoPresentNetAddr();

    NAS_LMM_PlmnCpy(&(pstTa->stPlmnId), &pstAreaInfo->stPlmnId);

    pstTa->stTac.ucTac                  = pstAreaInfo->stTac.ucTac;

    pstTa->stTac.ucTacCnt               = pstAreaInfo->stTac.ucTacCnt;

    return;
}
/*****************************************************************************
 Function Name   : NAS_EMMC_AddForbTa
 Description     : 添加一个禁止TA
 Input           : NAS_MM_PLMN_ID_STRU stPlmnId
 Output          : None
 Return          : VOS_VOID

 History         :
    1.luojian 00107747      2008-10-15  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_AddForbTa
(
    const NAS_MM_TA_STRU               *pstTa,
    NAS_MM_TA_LIST_STRU                *pstTaList
)
{
    NAS_LMM_PUBM_LOG_NORM("NAS_EMMC_AddForbTa is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_AddForbTa_ENUM,LNAS_ENTRY);

    NAS_LMM_AddTaInTaList(pstTa, pstTaList, NAS_LMM_MAX_FORBTA_NUM);
    /* DEL FORB TA PROID定时器未启动时启动定时器,防止出现A小区加入TA被禁列表,定时器快超时时,
        B小区被禁加入TA被禁列表重新启动定时器,导致出现A小区长时间无法被解禁 */
    if(NAS_LMM_TIMER_RUNNING != NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_DEL_FORB_TA_PROID))
    {
        NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_DEL_FORB_TA_PROID);
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_IsNeedAddForbTa
 Description     : 判断是否需要更新被禁列表
 Input           : NAS_MM_PLMN_ID_STRU stPlmnId
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangchen 00209181     2014-09-26  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_IsNeedAddForbTa
(
    VOS_VOID
)
{
    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_IsNeedAddForbTa is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_IsNeedAddForbTa_ENUM,LNAS_ENTRY);

    if ((VOS_TRUE == NAS_EMMC_GetShareNetFlag()) &&
         (NAS_EMM_CONN_DATA == NAS_EMM_TAU_GetEmmTauStartConnSta()))
    {
        return NAS_EMM_NO;
    }
    return NAS_EMM_YES;
}

/*****************************************************************************
 Function Name   : NAS_LMM_IsLastAttemptRegTaInTaiList
 Description     : 判断上次尝试发起注册或者TAU的TA是否在TAI列表中
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.    sunjitan 00193151      2012-7-6  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LMM_IsLastAttemptRegTaInTaiList(VOS_VOID)
{
    NAS_MM_TA_STRU                     *pstLastAttmpRegTa = NAS_EMM_NULL_PTR;
    NAS_LMM_NETWORK_INFO_STRU          *pstNetInfo        = NAS_EMM_NULL_PTR;

    pstNetInfo                         = NAS_LMM_GetEmmInfoNetInfoAddr();
    pstLastAttmpRegTa                  = NAS_LMM_GetEmmInfoNetInfoLastAttmpRegTaAddr();

    if (NAS_EMM_BIT_NO_SLCT == pstNetInfo->bitOpLastAttmpRegTa)
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_IsLastAttemptRegTaInTaiList: Not exist last attempt TA.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_IsLastAttemptRegTaInTaiList_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_NO;
    }

    if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatchTaList(pstLastAttmpRegTa, NAS_LMM_GetEmmInfoNetInfoTaiListAddr()))
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_IsLastAttemptRegTaInTaiList: Last attempt TA is in TAI LIST.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_IsLastAttemptRegTaInTaiList_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_YES;
    }
    else
    {
        return NAS_EMM_NO;
    }

}

/*****************************************************************************
 Function Name   : NAS_EMM_GetImsiHplmn
 Description     : 获取USIM的IMSI的HPLMN信息
 Input           : None
 Output          : None
 Return          : VOS_UINT8

 History         :
    1.sunjitan 00193151    2015-01-04  Draft Enact
*****************************************************************************/
VOS_UINT8  NAS_EMM_GetImsiHplmn
(
    VOS_UINT8             *pucImsi,
    NAS_MM_PLMN_ID_STRU   *pstHplmn
)
{
    NAS_MM_PLMN_ID_STRU       stHplmn;
    VOS_UINT32               *pulImsiMncLen;

    /* 获取USIM中指示的MNC的长度 */
    pulImsiMncLen = NAS_LMM_GetEmmInfoUeidImsiMncLenAddr();

    NAS_LMM_MEM_SET_S(&stHplmn, sizeof(NAS_MM_PLMN_ID_STRU), 0, sizeof(NAS_MM_PLMN_ID_STRU));

    /* 将IMSI转换成LMM使用的格式 */

    /* 跳过IMSI第0字节(长度)和第1字节的低4bit(校验位)，即跳过pucImsi[0]和pucImsi[1]的低4bit*/

    /* 获取MCC */
    /* 第1字节的高4bit为MCC第1位，保存在HPLMN第0个字节的低4位 */
    stHplmn.aucPlmnId[0] |= ((pucImsi[1] & NAS_EMM_HIGH_HALF_BYTE_F) >> NAS_EMM_MOVEMENT_4_BYTE);

    /* 第2字节的低4bit为MCC第2位，保存在HPLMN第0个字节的高4位 */
    stHplmn.aucPlmnId[0] |= ((pucImsi[2] & NAS_EMM_LOW_HALF_BYTE_F) << NAS_EMM_MOVEMENT_4_BYTE);

    /* 第2字节的高4bit为MCC第3位，保存在HPLMN第1个字节的低4位 */
    stHplmn.aucPlmnId[1] |= ((pucImsi[2] & NAS_EMM_HIGH_HALF_BYTE_F) >> NAS_EMM_MOVEMENT_4_BYTE);

    /* 获取MNC */
    /* 第3字节的低4bit为MNC第1位，保存在HPLMN第2个字节的低4位 */
    stHplmn.aucPlmnId[2] |= (pucImsi[3] & NAS_EMM_LOW_HALF_BYTE_F);

    /* 第3字节的高4bit为MNC第2位，保存在HPLMN第2个字节的高4位 */
    stHplmn.aucPlmnId[2] |= (pucImsi[3] & NAS_EMM_HIGH_HALF_BYTE_F);

    /* 如果MNC长度为2，则将MNC第3位设置为F，也就是HPLMN的第1字节的高4bit，否则继续解析MNC第3位 */
    if(NAS_LMM_NVIM_MNCLEN_VALUE_2 == (*pulImsiMncLen))
    {
        stHplmn.aucPlmnId[1] |= 0xF0;
    }
    else
    {
        stHplmn.aucPlmnId[1] |= ((pucImsi[4] & NAS_EMM_LOW_HALF_BYTE_F) << NAS_EMM_MOVEMENT_4_BYTE);
    }

    NAS_LMM_MEM_CPY_S(pstHplmn, sizeof(NAS_MM_PLMN_ID_STRU), &stHplmn, sizeof(NAS_MM_PLMN_ID_STRU));

    return NAS_EMM_SUCC;
}


/*****************************************************************************
 Function Name   : NAS_EMM_IsDamUsimCard
 Description     : 判断当前是否是满足DAM使用条件的USIM卡
 Input           : None
 Output          : None
 Return          : VOS_UINT8

 History         :
    1. sunjitan 00193151    2015-01-04  Draft Enact
*****************************************************************************/
VOS_UINT8  NAS_EMM_IsDamUsimCard(VOS_VOID)
{
    VOS_UINT8                *pucImsi;
    NAS_MM_PLMN_ID_STRU       stHplmn;
    VOS_UINT32                ulIndex;
    NAS_DAM_IMSI_PLMN_LIST   *pstDamImsiPlmnList;

    NAS_LMM_MEM_SET_S(&stHplmn, sizeof(NAS_MM_PLMN_ID_STRU), 0x00, sizeof(NAS_MM_PLMN_ID_STRU));

    pucImsi            = (VOS_UINT8*)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_PARA_IMSI);
    pstDamImsiPlmnList = NAS_EMM_GetEmmInfoDamParaImsiPlmnListAddr();

    /* 约定；NV中关于IMSI的PLMN判断如果只设置1个PLMN且全为0XFF，则默认对所有卡类别
             不做判断，仅根据是否驻留在DAM PLMN上来确定是否启用DAM,在此场景下，直
             接返回是DAM卡，这样后续只判断驻留PLMN即可                             */
    if((1 == pstDamImsiPlmnList->ulPlmnNum)
        &&(NAS_LMM_BYTE_FF == pstDamImsiPlmnList->astPlmnId[0].aucPlmnId[0])
        &&(NAS_LMM_BYTE_FF == pstDamImsiPlmnList->astPlmnId[0].aucPlmnId[1])
        &&(NAS_LMM_BYTE_FF == pstDamImsiPlmnList->astPlmnId[0].aucPlmnId[2]))
    {
        return NAS_EMM_YES;
    }

    /* 需要判断卡 */
    /* 获取HPLMN，然后跟IMSI PLMN列表进行比对，获取失败直接返回不是DAM卡 */
    if(NAS_EMM_SUCC == NAS_EMM_GetImsiHplmn(pucImsi, &stHplmn))
    {
        for(ulIndex = 0; ulIndex < pstDamImsiPlmnList->ulPlmnNum; ulIndex++)
        {
            if(NAS_LMM_MATCH_SUCCESS == NAS_LMM_PlmnMatch(&(stHplmn),
                (NAS_MM_PLMN_ID_STRU*)&(pstDamImsiPlmnList->astPlmnId[ulIndex])))
            {
                NAS_LMM_PUBM_LOG_INFO("NAS_EMM_IsCampOnATTPlmn: DAM Card.");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_IsDamUsimCard_ENUM,LNAS_EMM_JUDGE_FLAG);
                return NAS_EMM_YES;
            }
        }
    }

   return NAS_EMM_NO;

}

/*****************************************************************************
 Function Name   : NAS_EMM_IsTmoUsimCard
 Description     : 判断当前是否是TMO的USIM卡
 Input           : None
 Output          : None
 Return          : VOS_UINT8

 History         :
    1. sunjitan 00193151    2015-03-15  Draft Enact
*****************************************************************************/
VOS_UINT8  NAS_EMM_IsTmoUsimCard(VOS_VOID)
{
    NAS_LMM_PUBM_LOG1_INFO("NAS_EMM_IsTmoUsimCard: TmoUsimCardFlag is ", NAS_EMM_GetEmmInfoTmoUsimCardFlag());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_IsTmoUsimCard_ENUM,LNAS_EMM_JUDGE_FLAG,NAS_EMM_GetEmmInfoTmoUsimCardFlag());

    if(VOS_TRUE == NAS_EMM_GetEmmInfoTmoUsimCardFlag())
    {
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;

}

/*****************************************************************************
 Function Name   : NAS_EMM_IsPtmsiTauActiveFlagSatified
 Description     : 判断当前P-TMSI设置active flag标识的定制需求条件是否满足
 Input           : None
 Output          : None
 Return          : VOS_UINT8

 History         :
    1. lihong 00150010    2015-07-10  Draft Enact
*****************************************************************************/
VOS_UINT8  NAS_EMM_IsPtmsiTauActiveFlagSatified(VOS_VOID)
{
    /* 如果NV项打开，且不为测试卡，且TIN为P-TMSI，则条件满足，否则条件不满足 */
    if ((PS_TRUE == g_ulPtmsiTauActiveFlag)
        && (PS_SUCC != LPS_OM_IsTestMode())
        && (MMC_LMM_TIN_P_TMSI == NAS_EMM_GetTinType()))
    {
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}

/*****************************************************************************
 Function Name   : NAS_EMM_IsCampOnDamPlmn
 Description     : 判断当前是否驻留在AT&T的PLMN上
 Input           : None
 Output          : None
 Return          : VOS_UINT8

 History         :
    1. sunjitan 00193151    2015-01-04  Draft Enact
*****************************************************************************/
VOS_UINT8  NAS_EMM_IsCampOnDamPlmn(VOS_VOID)
{
    VOS_UINT32                          ulIndex;
    NAS_MM_NETWORK_ID_STRU             *pstAreaInfo;
    NAS_MM_DAM_PLMN_LIST_STRU          *pstDamPlmnList;

    pstDamPlmnList = NAS_EMM_GetEmmInfoDamParaPlmnListAddr();
    pstAreaInfo = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_PRESENT_NET_ID);

    /* 约定；NV中关于驻留的PLMN判断如果只设置1个PLMN且全为0XFF，则默认对驻留的PLMN
             不做判断，仅根据是否是DAM卡来确定是否启用DAM,在此场景下，直
             接返回驻留在DAM的PLMN上，这样后续只判断卡类型即可                    */
    if((1 == pstDamPlmnList->ulPlmnNum)
        &&(NAS_LMM_BYTE_FF == pstDamPlmnList->astPlmnId[0].aucPlmnId[0])
        &&(NAS_LMM_BYTE_FF == pstDamPlmnList->astPlmnId[0].aucPlmnId[1])
        &&(NAS_LMM_BYTE_FF == pstDamPlmnList->astPlmnId[0].aucPlmnId[2]))
    {
        return NAS_EMM_YES;
    }

    for(ulIndex = 0; ulIndex < pstDamPlmnList->ulPlmnNum; ulIndex++)
    {
        if(NAS_LMM_MATCH_SUCCESS == NAS_LMM_PlmnMatch(&(pstAreaInfo->stPlmnId),
            (NAS_MM_PLMN_ID_STRU*)&(pstDamPlmnList->astPlmnId[ulIndex])))
        {
            NAS_LMM_PUBM_LOG_INFO("NAS_EMM_IsCampOnATTPlmn: Camp on DAM PLMN.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_IsCampOnDamPlmn_ENUM,LNAS_EMM_JUDGE_FLAG);
            return NAS_EMM_YES;
        }
    }

    return NAS_EMM_NO;

}

/*****************************************************************************
 Function Name   : NAS_EMM_IsDamConfitionSatisfied
 Description     : 判断当前是否需要使用DAM
 Input           : None
 Output          : None
 Return          : VOS_UINT8

 History         :
    1. sunjitan 00193151    2015-01-04  Draft Enact
*****************************************************************************/
VOS_UINT8  NAS_EMM_IsDamConfitionSatisfied(VOS_VOID)
{
    if((NAS_EMM_YES == NAS_EMM_IsDamUsimCard())
        &&(NAS_EMM_YES== NAS_EMM_IsCampOnDamPlmn()))
    {
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SendMMCT3402LenNotify
 Description     : 给MMC发送ID_LMM_MMC_T3402_LEN_NOTIFY消息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151      2015-01-04  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_SendMMCT3402LenNotify(VOS_UINT32 ulT3402Len)
{
    LMM_MMC_T3402_LEN_NOTIFY_STRU           *pstT3402LenMsg;

    /* 申请MMC内部消息 */
    pstT3402LenMsg = (VOS_VOID *)NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_T3402_LEN_NOTIFY_STRU));

    if (NAS_LMM_NULL_PTR == pstT3402LenMsg)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_SendMMCT3402LenNotify: MSG ALLOC ERROR!!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_SendMMCT3402LenNotify_ENUM,LNAS_NULL_PTR);
        return;
    }

    /* 清空 */
    NAS_LMM_MEM_SET_S(  pstT3402LenMsg,
                        sizeof(LMM_MMC_T3402_LEN_NOTIFY_STRU),
                        0,
                        sizeof(LMM_MMC_T3402_LEN_NOTIFY_STRU));

    /* 打包VOS消息头 */
    EMM_PUBU_COMP_MMC_MSG_HEADER((pstT3402LenMsg),NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LMM_MMC_T3402_LEN_NOTIFY_STRU));

    /* 填充消息ID */
    pstT3402LenMsg->ulMsgId             = ID_LMM_MMC_T3402_LEN_NOTIFY;

    /* 填充消息体 */
    pstT3402LenMsg->ulOpId              = NAS_EMM_OPID_MMC;

    pstT3402LenMsg->ulT3402Len          = ulT3402Len;

    NAS_EMM_PUBU_LOG1_WARN("NAS_EMM_SendMMCT3402LenNotify: ulT3402Len=",ulT3402Len);
    TLPS_PRINT2LAYER_WARNING1(NAS_EMM_SendMMCT3402LenNotify_ENUM,LNAS_EMM_T3402_LEN,ulT3402Len);

    /* 发送MMC内部消息 */
    NAS_LMM_SendLmmMmcMsg(pstT3402LenMsg);

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_IsRegStatusEmcRegingOrContainEmcBear
 Description     : 判断是否是紧急注册、紧急注册过程中或者正常注册包含紧急承载
                   是: NAS_EMM_YES
                   否: NAS_EMM_NO
 Input           : None
 Output          : None
 Return          : VOS_UINT32
 History         :
    1.    sunjitan 00193151      2013-01-08  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_IsRegStatusEmcRegingOrContainEmcBear(VOS_VOID)
{
    /* 处于紧急注册过程中 */
    if(NAS_LMM_REG_STATUS_EMC_REGING == NAS_LMM_GetEmmInfoRegStatus())
    {
        return NAS_EMM_YES;
    }

    /* 处于已经紧急注册或者正常注册有紧急承载 */
    if ((NAS_LMM_REG_STATUS_EMC_REGED == NAS_LMM_GetEmmInfoRegStatus())
        ||(NAS_LMM_REG_STATUS_NORM_REGED_AND_EMC_BEAR == NAS_LMM_GetEmmInfoRegStatus()))
    {
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;

}


/*****************************************************************************
 Function Name  : Nas_Emm_GutiDelete
 Discription    : 删除GUTI信息
 Input          : None
 Output         : None
 Return         : None
 History:
      1.  yangfan  00159566  2010-03-30  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_ClearGuti(VOS_VOID)
{
    NAS_LMM_GetEmmInfoUeidAddr()->bitOpGuti      = NAS_EMM_BIT_NO_SLCT;
    NAS_LMM_MEM_SET_S(  NAS_LMM_GetEmmInfoUeidGutiAddr(),
                        sizeof(NAS_MM_GUTI_STRU),
                        0,
                        sizeof(NAS_EMM_GUTI_STRU));
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ClearRegInfo
 Description     : 删除GUTI,LVR TAI,TAI list,KSIasme
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.y00159566      2010-4-1  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_ClearRegInfo(VOS_UINT32 ulDeleteRplmn )
{
    /*删除GUTI*/
    NAS_EMM_ClearGuti();

    /*删除LVR TAI*/

    if (NAS_EMM_DELETE_RPLMN == ulDeleteRplmn)
    {
        NAS_EMM_ClearLVRTai();
    }
    else
    {
        NAS_EMM_SetLVRTacInvalid();
    }
    /*删除TAI list*/
    NAS_EMM_ClearTaiList();

    /*删除KSIasme*/
    /*NAS_EMM_ClearCurSecuCntxt();*/
    NAS_EMM_ClearAllSecuCntxt();

    /* 将无效的安全上下文直接在函数内部写卡 */
    NAS_LMM_WriteEpsSecuContext(NAS_NV_ITEM_UPDATE);

    /*保存PS LOC信息*/
    NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
}

/*****************************************************************************
 Function Name   : NAS_EMM_ClearResumeInfo
 Description     : 清除异系统变换的触发和类型信息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151     2012-5-24  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_ClearResumeInfo( VOS_VOID )
{
    NAS_EMM_FSM_STATE_STRU             *pstStateBeforeResume;

    NAS_LMM_PUBM_LOG_NORM( "NAS_EMM_ClearResumeInfoOriTypeDir: ResumeInfo  is  cleared!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ClearResumeInfo_ENUM,LNAS_ENTRY);

    pstStateBeforeResume = NAS_EMM_GetStateBeforeResumeAddr();

    pstStateBeforeResume->enMainState   = NAS_LMM_MAIN_STATE_BUTT;
    pstStateBeforeResume->enSubState    = MM_SS_BUTT;
    pstStateBeforeResume->enStaTId      = TI_NAS_EMM_STATE_NO_TIMER;

    NAS_EMM_SetResumeOri(NAS_LMM_SYS_CHNG_ORI_BUTT);
    NAS_EMM_SetResumeType(NAS_LMM_SYS_CHNG_TYPE_BUTT);
    NAS_EMM_SetResumeDir(LRRC_LMM_RSM_SYS_CHNG_DIR_BUTT);

    return;

}

/*****************************************************************************
 Function Name   : NAS_LMM_ClearEmmInfoMmcAttachReason
 Description     : 清除attach 原因值
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leixianitao 00258641     2014-2-14  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_ClearEmmInfoMmcAttachReason( VOS_VOID )
{
    NAS_LMM_PUBM_LOG_NORM( "NAS_LMM_ClearEmmInfoMmcAttachReason is  enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_ClearEmmInfoMmcAttachReason_ENUM,LNAS_ENTRY);
    NAS_LMM_SetEmmInfoMmcAttachReason(MMC_LMM_ATT_REASON_INITIAL);
    return;

}


/*****************************************************************************
 Function Name   : NAS_EMM_LocalDetachProc
 Description     :
            1）停Emm定时器
            2）清理缓存
            3）清理栈空间
            4）通知ESM,RABM清理资源
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.y00159566      2010-6-18  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_LocalDetachProc( VOS_VOID )
{
    /* 关闭当前EMM的除Del Forb Ta Proid之外的状态定时器, Del Forb Ta Proid只能在关机时停止*/
    NAS_LMM_StopAllStateTimerExceptDelForbTaProidTimer();

    /* 停止所有协议定时器 */
    NAS_LMM_StopAllPtlTimer();

    /* 释放可能存在的动态内存 */
    NAS_LMM_FreeDynMem();

    /* 通知ESM清除资源 */
    NAS_EMM_PLMN_SendEmmEsmStautsInd(   EMM_ESM_ATTACH_STATUS_DETACHED);

    /*清除bar流程和类型*/
    NAS_EMM_ClearBarResouce();

    /*通知 RABM:RRC_CONN_REL_IND*/
    NAS_LMM_SendRabmRrcConRelInd(EMM_ERABM_REL_CAUSE_NULL);
}

/*****************************************************************************
 Function Name   : NAS_EMM_TransferUeSpecDrxCycleLen
 Description     : 将Drx Param中的 DRX value for S1 mode转换为DRX cycle
                   参考:24008-930 10.5.5.6
 Input           : None
 Output          : UE_Specific_Drx_Cycle
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-9-9  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_TransferUeSpecDrxCycleLen( VOS_VOID )
{
    VOS_UINT32                  ulUeSpecDrxCycle = 0;
    VOS_UINT8                   ucUeEutranPsDrxLen = 0;
    /*NAS_MM_DRX_STRU            *pstUeDrxParam = VOS_NULL_PTR;*/

    /*获取UE指定的DRX参数*/
    /*pstUeDrxParam = NAS_LMM_GetEmmInfoDrxAddr();*/
    /*根据24008-930 10.5.5.6协议描述进行转换*/
    switch(NAS_EMM_GetUeEutranPsDrxLen())
    {
        case NAS_LMM_DEC_DIGIT_0:
            ulUeSpecDrxCycle = 0;
            break;

        case NAS_LMM_DEC_DIGIT_6:
            ulUeSpecDrxCycle = 32;
            break;

        case NAS_LMM_DEC_DIGIT_7:
            ulUeSpecDrxCycle = 64;
            break;

        case NAS_LMM_DEC_DIGIT_8:
            ulUeSpecDrxCycle = 128;
            break;
        case NAS_LMM_DEC_DIGIT_9:
            ulUeSpecDrxCycle = 256;
            break;

             /*其他值，报错,转换为0*/
        default:
            ucUeEutranPsDrxLen = NAS_MML_GetUeEutranPsDrxLen();
            NAS_EMM_PUBU_LOG1_WARN("NAS_EMM_TransferUeSpecDrxCycleLen:Drx Err.",
                                        ucUeEutranPsDrxLen);
            TLPS_PRINT2LAYER_WARNING(NAS_EMM_TransferUeSpecDrxCycleLen_ENUM,LNAS_ERROR);
            ulUeSpecDrxCycle = 0;
            break;
    }

    return ulUeSpecDrxCycle;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SendUeSpecDrxCycleLenToRrc
 Description     : 发送RRC_MM_INFO_CHANGE_REQ给RRC,携带UE指定的 DRX_Cycle_Len
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-9-9  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SendUeSpecDrxCycleLenToRrc( VOS_VOID )
{
    LRRC_LNAS_INFO_STRU                   stNasInfo;
    VOS_UINT32                          ulUeSpecDrxCycle;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_SendUeSpecDrxCycleLenToRrc entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendUeSpecDrxCycleLenToRrc_ENUM,LNAS_ENTRY);

    /*清空内存*/
    NAS_LMM_MEM_SET_S(&stNasInfo, sizeof(LRRC_LNAS_INFO_STRU), 0, sizeof(LRRC_LNAS_INFO_STRU));

    /*获取全局变量中的DRX Param,并按照协议转换为 UeSpecDrxCycle*/
    ulUeSpecDrxCycle = NAS_EMM_TransferUeSpecDrxCycleLen();

    /*填充UE指定的 DRX_Cycle_Len*/
    stNasInfo.bitOpDrxLength            = NAS_EMM_BIT_SLCT;
    stNasInfo.ulDrxLength               = ulUeSpecDrxCycle;

    /*发送RRC_MM_INFO_CHANGE_REQ消息给RRC*/
    NAS_EMM_SendInfoChangeReqMsg(&stNasInfo);

    return;

}

/*****************************************************************************
 Function Name   : NAS_EMM_SendInfoChangeReqMsg
 Description     : 发送RRC_MM_NAS_INFO_CHANGE_REQ消息给RRC，目前实现需要通知RRC
                   的信息有两类:
                   1)安全参数:Kasme + Ul_NasCount
                   2)UeSpecDrxCycleLen
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-9-9  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SendInfoChangeReqMsg( CONST LRRC_LNAS_INFO_STRU *pstNasInfo )
{
    LRRC_LMM_NAS_INFO_CHANGE_REQ_STRU    *pstInfoChgReqMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLen;

    /*计算长度不包含VOS消息头*/
    ulMsgLen     = NAS_EMM_MSG_ID_LEN + sizeof(LRRC_LNAS_INFO_STRU);

    /*分配内存*/
    pstInfoChgReqMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(ulMsgLen + NAS_EMM_LEN_VOS_MSG_HEADER);
    if(NAS_EMM_NULL_PTR == pstInfoChgReqMsg)
    {
        return;
    }

    /*清空申请到的消息空间*/
    NAS_LMM_MEM_SET_S(  pstInfoChgReqMsg,
                        sizeof(LRRC_LMM_NAS_INFO_CHANGE_REQ_STRU),
                        0,
                        sizeof(LRRC_LMM_NAS_INFO_CHANGE_REQ_STRU));

    /*填充VOS消息头*/
    NAS_EMM_SET_RRC_MSG_HEADER(pstInfoChgReqMsg, ulMsgLen);

    /*填充消息ID*/
    pstInfoChgReqMsg->enMsgId           = ID_LRRC_LMM_NAS_INFO_CHANGE_REQ;

    /*填充消息体 */
    NAS_LMM_MEM_CPY_S(                  &(pstInfoChgReqMsg->stNasInfo),
                                        sizeof(LRRC_LNAS_INFO_STRU),
                                        pstNasInfo,
                                        sizeof(LRRC_LNAS_INFO_STRU));

    /* 发送RRC_MM_NAS_INFO_CHANGE_REQ */
    NAS_LMM_SEND_MSG(pstInfoChgReqMsg);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_PUBU_ClearResource
 Description     : DETACH后，
                    释放动态内存；
                    停止定时器；
                    全局变量赋初始值；
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1. h41410 DRAFT 2010 10 15

*****************************************************************************/
VOS_VOID    NAS_EMM_PUBU_ClearResource(VOS_VOID)
{
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PUBU_ClearResource: enter.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PUBU_ClearResource_ENUM,LNAS_ENTRY);

    /* 清除ESM的承载状态 */
    NAS_EMM_PubmInfoBearerContextInit();

    /* 清除保存的APP来的消息的参数 */
    /*NAS_EMM_ClearAppMsgPara();*/

    /* 清除最后一个发出的CN消息的类型 */
    NAS_LMM_GetLastAirMsgType() = EMM_MSG_TYPE_INVALID;

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_PUBU_SuspendClearResource
 Description     : 挂起时，
                    释放动态内存；
                    停止定时器；
                    全局变量赋初始值；
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1. h41410 DRAFT 2010 10 15

*****************************************************************************/
VOS_VOID    NAS_EMM_PUBU_SuspendClearResource(VOS_VOID)
{
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PUBU_SuspendClearResource: enter.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PUBU_SuspendClearResource_ENUM,LNAS_ENTRY);

    /* 清除ESM的承载状态 */
    /*NAS_EMM_PubmInfoBearerContextInit();*/

    /* 清除保存的APP来的消息的参数 */
    /*NAS_EMM_ClearAppMsgPara();*/

    /* 清除最后一个发出的CN消息的类型 */
    NAS_LMM_GetLastAirMsgType() = EMM_MSG_TYPE_INVALID;

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_SetUsimState
 Description     : 设置卡状态
 Input           : NAS_LMM_SIM_STAT_ENUM_UINT32 ulUsimStatus
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-3-3  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_EMM_SetUsimState( NAS_LMM_SIM_STAT_ENUM_UINT32 ulUsimStatus )
{
    NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_SetUsimState: set ulUsimStatus = ", ulUsimStatus);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_SetUsimState_ENUM,LNAS_EMM_USIM_STATE,ulUsimStatus);

    if( (NAS_LMM_SIM_STATUS_UNAVAILABLE != ulUsimStatus) &&
        (NAS_LMM_SIM_STATUS_AVAILABLE != ulUsimStatus))
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_SetUsimState: Input Para err ! ");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SetUsimState_ENUM,LNAS_PARAM_INVALID);
        return;
    }
    else
    {
        NAS_LMM_GetSimState() = ulUsimStatus;
        return;
    }
}


VOS_VOID NAS_EMM_LmmEmmInfo2MmcEmmInfo(const NAS_EMM_INFO_STRU *pstLmmEmmInfo, MMC_EMM_INFO_STRU *pstMmcEmmInfo)
{
    /* convert bit flag field */
    pstMmcEmmInfo->bitOpLocTimeZone        = pstLmmEmmInfo->bitOpLocTimeZone;
    pstMmcEmmInfo->bitOpUniTimeLocTimeZone = pstLmmEmmInfo->bitOpUniTimeLocTimeZone;
    pstMmcEmmInfo->bitOpDaylightTime       = pstLmmEmmInfo->bitOpDaylightTime;
    pstMmcEmmInfo->bitReserved             = pstLmmEmmInfo->bitShare;

    /* convert LTZ field */
    if (NAS_LMM_TIMEZONE_POSITIVE == pstLmmEmmInfo->stLocTimeZone.enPosNegTimeZone)
    {
        pstMmcEmmInfo->cLocTimeZone =  (VOS_INT8)(pstLmmEmmInfo->stLocTimeZone.ucTimeZone & 0x7F);
    }
    else
    {
        pstMmcEmmInfo->cLocTimeZone = -(VOS_INT8)(pstLmmEmmInfo->stLocTimeZone.ucTimeZone & 0x7F);
    }

    /* convert UT_LTZ field */
    pstMmcEmmInfo->stTimeZoneAndTime.ucYear   = pstLmmEmmInfo->stTimeZoneAndTime.ucYear;
    pstMmcEmmInfo->stTimeZoneAndTime.ucMonth  = pstLmmEmmInfo->stTimeZoneAndTime.ucMonth;
    pstMmcEmmInfo->stTimeZoneAndTime.ucDay    = pstLmmEmmInfo->stTimeZoneAndTime.ucDay;
    pstMmcEmmInfo->stTimeZoneAndTime.ucHour   = pstLmmEmmInfo->stTimeZoneAndTime.ucHour;
    pstMmcEmmInfo->stTimeZoneAndTime.ucMinute = pstLmmEmmInfo->stTimeZoneAndTime.ucMinute;
    pstMmcEmmInfo->stTimeZoneAndTime.ucSecond = pstLmmEmmInfo->stTimeZoneAndTime.ucSecond;
    if (NAS_LMM_TIMEZONE_POSITIVE == pstLmmEmmInfo->stTimeZoneAndTime.stTimeZone.enPosNegTimeZone)
    {
        pstMmcEmmInfo->stTimeZoneAndTime.cTimeZone =  (VOS_INT8)(pstLmmEmmInfo->stTimeZoneAndTime.stTimeZone.ucTimeZone & 0x7F);
    }
    else
    {
        pstMmcEmmInfo->stTimeZoneAndTime.cTimeZone = -(VOS_INT8)(pstLmmEmmInfo->stTimeZoneAndTime.stTimeZone.ucTimeZone & 0x7F);
    }
    /* convert DST field */
    switch(pstLmmEmmInfo->enDaylightSavingTime)
    {
    case NAS_LMM_DAYLIGHT_NO_ADJUST:
        pstMmcEmmInfo->enDaylightSavingTime = MMC_EMM_INFO_DST_NO_ADJUST;
        break;
    case NAS_LMM_DAYLIGHT_1_HOUR_ADJUST:
        pstMmcEmmInfo->enDaylightSavingTime = MMC_EMM_INFO_DST_1_HOUR_ADJUST;
        break;
    case NAS_LMM_DAYLIGHT_2_HOUR_ADJUST:
        pstMmcEmmInfo->enDaylightSavingTime = MMC_EMM_INFO_DST_2_HOUR_ADJUST;
        break;
    default:
        pstMmcEmmInfo->enDaylightSavingTime = MMC_EMM_INFO_DST_BUTT;
    }
}


VOS_VOID NAS_EMM_SendMmcEmmInfoInd(const NAS_EMM_INFO_STRU *pLmmEmmInfo)
{
    LMM_MMC_EMM_INFO_IND_STRU *pstMmcEmmInfoIndMsg = VOS_NULL_PTR;
    NAS_EMM_INFO_STRU                   *pstEmmInfo;


    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_SendMmcEmmInfoInd: enter");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendMmcEmmInfoInd_ENUM,LNAS_ENTRY);

    /* check input parameter */
    if (NAS_LMM_NULL_PTR == pLmmEmmInfo)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_SendMmcEmmInfoInd: invalid input parameter");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SendMmcEmmInfoInd_ENUM,LNAS_NULL_PTR);
        return;
    }

    /* alloc memory */
    pstMmcEmmInfoIndMsg = (VOS_VOID *)NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_EMM_INFO_IND_STRU));
    if (NAS_LMM_NULL_PTR == pstMmcEmmInfoIndMsg)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_SendMmcEmmInfoInd: MSG ALLOC ERROR");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SendMmcEmmInfoInd_ENUM,LNAS_ERROR);
        return;
    }

    /* initialization */
    NAS_LMM_MEM_SET_S(pstMmcEmmInfoIndMsg, sizeof(LMM_MMC_EMM_INFO_IND_STRU), 0, sizeof(LMM_MMC_EMM_INFO_IND_STRU));

    /* composite message header */
    EMM_PUBU_COMP_MMC_MSG_HEADER((pstMmcEmmInfoIndMsg), NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LMM_MMC_EMM_INFO_IND_STRU));

    /* assign message id */
    pstMmcEmmInfoIndMsg->ulMsgId = ID_LMM_MMC_EMM_INFO_IND;

    /* assign message context */
    NAS_EMM_LmmEmmInfo2MmcEmmInfo(pLmmEmmInfo, &pstMmcEmmInfoIndMsg->stLteEmmInfo);


    pstEmmInfo  = NAS_LMM_GetEmmInfoNasEmmInfoListAddr();

    if(NAS_EMM_BIT_SLCT == pstEmmInfo->bitOpFullName)
    {
        pstMmcEmmInfoIndMsg->stLteEmmInfo.bitOpLongName = NAS_EMM_BIT_SLCT;
        NAS_LMM_MEM_CPY_S(  pstMmcEmmInfoIndMsg->stLteEmmInfo.aucOperatorNameLong,
                            MMC_LMM_MAX_OPER_LONG_NAME_LEN,
                            pLmmEmmInfo->aucOperatorNameLong,
                            MMC_LMM_MAX_OPER_LONG_NAME_LEN);
    }

    if(NAS_EMM_BIT_SLCT == pstEmmInfo->bitOpShortName)
    {
        pstMmcEmmInfoIndMsg->stLteEmmInfo.bitOpShortName = NAS_EMM_BIT_SLCT;
        NAS_LMM_MEM_CPY_S(  pstMmcEmmInfoIndMsg->stLteEmmInfo.aucOperatorNameShort,
                            MMC_LMM_MAX_OPER_SHORT_NAME_LEN,
                            pLmmEmmInfo->aucOperatorNameShort,
                            MMC_LMM_MAX_OPER_SHORT_NAME_LEN);
    }

    /* send message to MMC */
    NAS_LMM_SendLmmMmcMsg(pstMmcEmmInfoIndMsg);
}


VOS_VOID    NAS_EMM_SendMmcStatusInd(
                                MMC_LMM_STATUS_TYPE_ENUM_UINT32 ulMmcLmmStaType,
                                MMC_LMM_CONN_STATE_ENUM_UINT32  ulConnState )
{
    LMM_MMC_STATUS_IND_STRU           *pstMmcStatusIndMsg = VOS_NULL_PTR;

    NAS_EMM_PUBU_LOG2_INFO("NAS_EMM_SendMmcStatusInd: ulMmcLmmStaType = , ulConnState =",
                        ulMmcLmmStaType,
                        ulConnState);
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_SendMmcStatusInd_ENUM,LNAS_FUNCTION_LABEL1,
                        ulMmcLmmStaType,
                        ulConnState);
    /* 申请MMC内部消息 */
    pstMmcStatusIndMsg = (VOS_VOID *) NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_STATUS_IND_STRU));
    if (NAS_LMM_NULL_PTR == pstMmcStatusIndMsg)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_SendMmcStatusInd: MSG ALLOC ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SendMmcStatusInd_ENUM,LNAS_NULL_PTR);
        return ;
    }

    /* 清空 */
    NAS_LMM_MEM_SET_S(  pstMmcStatusIndMsg,
                        sizeof(LMM_MMC_STATUS_IND_STRU),
                        0,
                        sizeof(LMM_MMC_STATUS_IND_STRU));

    /* 打包VOS消息头 */
    EMM_PUBU_COMP_MMC_MSG_HEADER((pstMmcStatusIndMsg),
                             NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LMM_MMC_STATUS_IND_STRU));

    /* 填充消息ID */
    pstMmcStatusIndMsg->ulMsgId         = ID_LMM_MMC_STATUS_IND;

    /* 填充消息体 */
    pstMmcStatusIndMsg->ulOpId          = NAS_EMM_OPID_MMC;
    pstMmcStatusIndMsg->ulStatusType    = ulMmcLmmStaType;

    /* 如果上报的类型为MMC_LMM_STATUS_TYPE_CONN_STATE，则填充连接状态*/
    if(MMC_LMM_STATUS_TYPE_CONN_STATE == ulMmcLmmStaType)
    {
        pstMmcStatusIndMsg->bitOpConnState  = NAS_EMM_BIT_SLCT;
        pstMmcStatusIndMsg->ulConnState     = ulConnState;
    }

    /* 发送MMC内部消息 */
    NAS_LMM_SendLmmMmcMsg(pstMmcStatusIndMsg);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SendMmcUsimStatusCnf
 Description     : 向MMC发送LMM_MMC_USIM_STATUS_CNF消息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-7-2  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_SendMmcUsimStatusCnf( VOS_VOID )
{
    LMM_MMC_USIM_STATUS_CNF_STRU       *pstMmcUsimStatusCnf = VOS_NULL_PTR;

    /* 申请MMC内部消息*/
    pstMmcUsimStatusCnf = (VOS_VOID *) NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_USIM_STATUS_CNF_STRU));
    if (NAS_LMM_NULL_PTR == pstMmcUsimStatusCnf)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_SendMmcUsimStatusCnf: MSG ALLOC ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SendMmcUsimStatusCnf_ENUM,LNAS_NULL_PTR);
        return ;
    }

    /* 清空 */
    NAS_LMM_MEM_SET_S(  pstMmcUsimStatusCnf,
                        sizeof(LMM_MMC_USIM_STATUS_CNF_STRU),
                        0,
                        sizeof(LMM_MMC_USIM_STATUS_CNF_STRU));

    /* 打包VOS消息头 */
    EMM_PUBU_COMP_MMC_MSG_HEADER((pstMmcUsimStatusCnf),
                             NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LMM_MMC_USIM_STATUS_CNF_STRU));

    /* 填充消息ID */
    pstMmcUsimStatusCnf->ulMsgId    = ID_LMM_MMC_USIM_STATUS_CNF;

    /* 填充消息体 */
    pstMmcUsimStatusCnf->ulOpId     = NAS_EMM_OPID_MMC;

    /* 发送MMC内部消息 */
    NAS_LMM_SendLmmMmcMsg(pstMmcUsimStatusCnf);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_CheckSupportMode
 Description     : 判断是否支持Iu mode或A/Gb mode
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-5-13  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_CheckSupportGUMode( VOS_VOID)
{
    if ( ((NAS_LMM_RAT_PRIO_NULL < NAS_LMM_GetCurGsmPrio())
       &&(NAS_LMM_RAT_PRIO_BUTT > NAS_LMM_GetCurGsmPrio()))
      ||((NAS_LMM_RAT_PRIO_NULL < NAS_LMM_GetCurWcdmaPrio())
       &&(NAS_LMM_RAT_PRIO_BUTT > NAS_LMM_GetCurWcdmaPrio())))
    {
        return NAS_LMM_SUCC;
    }
    return NAS_EMM_FAIL;
}


/*****************************************************************************
 Function Name   : NAS_EMM_CheckMutiModeSupport
 Description     : 判断是否支持Iu mode或A/Gb mode
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-5-9  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_CheckMutiModeSupport(VOS_VOID  )
{
    VOS_UINT32                          ulRslt = NAS_EMM_FAIL;

    if ( (NAS_LMM_RAT_PRIO_NULL == NAS_LMM_GetCurLtePrio ())
       ||(NAS_LMM_RAT_PRIO_BUTT == NAS_LMM_GetCurLtePrio ()))
    {
        ulRslt = NAS_LMM_FAIL;
    }
    else if( (NAS_LMM_RAT_PRIO_NULL < NAS_LMM_GetCurLtePrio ())
            &&(NAS_LMM_RAT_PRIO_BUTT > NAS_LMM_GetCurLtePrio ()))
    {
        ulRslt = NAS_EMM_CheckSupportGUMode();
    }
    else
    {
    }
    return ulRslt;

}

/*****************************************************************************
 Function Name   : NAS_EMM_CheckPtmsiAndRaiValidity
 Description     : 判断P-TMSI和RAI是否有效
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-5-9  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_CheckPtmsiAndRaiValidity( VOS_VOID )
{
    NAS_GUMM_INFO_STRU                  stGuInfo;
    MMC_LMM_RESULT_ID_ENUM_UINT32       ulRslt1;
    MMC_LMM_RESULT_ID_ENUM_UINT32       ulRslt2;
    /*判断P-TMSI 和 RAI是否有效*/
    ulRslt1 = NAS_EMM_GetGuInfo(NAS_GUMM_PTMSI,&stGuInfo);

    ulRslt2 = NAS_EMM_GetGuInfo(NAS_GUMM_RAI,&stGuInfo);

    if ((MMC_LMM_SUCC == ulRslt1) &&
        (MMC_LMM_SUCC == ulRslt2))
    {

        return NAS_EMM_SUCC;
    }

    return NAS_EMM_FAIL;

}

/*****************************************************************************
 Function Name   : NAS_EMM_GetPtmsiAndRai
 Description     : 获取P-TMSI和RAI的值
 Input           : None
 Output          : pstPtmsi------P-TMSI的值
                   pstRai--------RAI的值
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2011-5-9  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_GetPtmsiAndRai
(
    NAS_GUMM_PTMSI_STRU     *pstPtmsi,
    MMC_LMM_RAI_STRU        *pstRai
)
{
    NAS_GUMM_INFO_STRU                  stGuInfo;
    MMC_LMM_RESULT_ID_ENUM_UINT32       ulRslt1;
    MMC_LMM_RESULT_ID_ENUM_UINT32       ulRslt2;

    /*初始化*/
    NAS_LMM_MEM_SET_S(&stGuInfo, sizeof(NAS_GUMM_INFO_STRU), 0, sizeof(NAS_GUMM_INFO_STRU));

    /*判断P-TMSI 和 RAI是否有效*/
    ulRslt1 = NAS_EMM_GetGuInfo(NAS_GUMM_PTMSI,&stGuInfo);

    if (MMC_LMM_SUCC == ulRslt1)
    {
        NAS_LMM_MEM_CPY_S(              pstPtmsi,
                                        sizeof(NAS_GUMM_PTMSI_STRU),
                                        &(stGuInfo.u.stPtmsi),
                                        sizeof(NAS_GUMM_PTMSI_STRU));
    }

    ulRslt2 = NAS_EMM_GetGuInfo(NAS_GUMM_RAI,&stGuInfo);

    if (MMC_LMM_SUCC == ulRslt2)
    {
        NAS_LMM_MEM_CPY_S(              pstRai,
                                        sizeof(MMC_LMM_RAI_STRU),
                                        &(stGuInfo.u.stRAI),
                                        sizeof(MMC_LMM_RAI_STRU));
    }
    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_DeriveMappedGuti
 Description     : 获取P-TMSI和RAI的值,计算Mapped GUTI
 Input           : None
 Output          :

 Return          : VOS_VOID

 History         :
    1.zhengjunyan 00148421      2011-5-19  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_DeriveMappedGuti
(
    NAS_LMM_GUTI_STRU                   *pstMappedGuti
)
{
    NAS_GUMM_PTMSI_STRU                 stPtmsi;
    MMC_LMM_RAI_STRU                    stRai;

    NAS_LMM_MEM_SET_S(&stPtmsi, sizeof(NAS_GUMM_PTMSI_STRU), 0, sizeof(NAS_GUMM_PTMSI_STRU));
    NAS_LMM_MEM_SET_S(&stRai, sizeof(MMC_LMM_RAI_STRU), 0, sizeof(MMC_LMM_RAI_STRU));

    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_DeriveMappedGuti entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_DeriveMappedGuti_ENUM,LNAS_ENTRY);

    if(VOS_NULL_PTR == pstMappedGuti)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_DeriveMappedGuti: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DeriveMappedGuti_ENUM,LNAS_PARAM_INVALID);
        return;
    }
    /* 清空入参空间*/
    NAS_LMM_MEM_SET_S(pstMappedGuti, sizeof(NAS_LMM_GUTI_STRU), 0, sizeof(NAS_LMM_GUTI_STRU));

    /* 获取 P-TMSI和 RAI*/
    NAS_EMM_GetPtmsiAndRai(&stPtmsi,&stRai);

    /* 组装Mapped GUTI*/
    pstMappedGuti->stGutiHead.ucLenth   = NAS_EMM_AD_LEN_GUTI;
    pstMappedGuti->stGutiHead.ucOeToi   = NAS_EMM_AD_ID_GUTI;

    NAS_LMM_MEM_CPY_S(                  &(pstMappedGuti->stPlmnId),
                                        sizeof(MMC_LMM_PLMN_ID_STRU),
                                        &(stRai.stLai.stPlmnId),
                                        sizeof(NAS_MM_PLMN_ID_STRU));
    pstMappedGuti->stMmeGroupId.ucGroupId = stRai.stLai.stLac.ucLac;
    pstMappedGuti->stMmeGroupId.ucGroupIdCnt = stRai.stLai.stLac.ucLacCnt;
    pstMappedGuti->stMmeCode.ucMmeCode  = stPtmsi.aucPtmsi[1];
    pstMappedGuti->stMTmsi.ucMTmsi      = ((stPtmsi.aucPtmsi[0])|(NAS_EMM_HITH_2_BITS_F));
    pstMappedGuti->stMTmsi.ucMTmsiCnt1  = stRai.ucRac;
    pstMappedGuti->stMTmsi.ucMTmsiCnt2  = stPtmsi.aucPtmsi[2];
    pstMappedGuti->stMTmsi.ucMTmsiCnt3  = stPtmsi.aucPtmsi[3];

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_GetTinType
 Description     : 获取TIN的值
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-5-9  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_GetTinType(VOS_VOID )
{
    MMC_LMM_TIN_TYPE_ENUM_UINT32        ulTinType;

    #ifndef __PS_WIN32_RECUR__
    ulTinType = NAS_MML_GetTinType();

    /* coverity[unchecked_value] */
    NAS_LMM_LogTinInfo(ulTinType,WUEPS_PID_MMC,PS_PID_MM);
    NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_GetTinType: ulTinType = ", ulTinType);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_GetTinType_ENUM,LNAS_EMM_TIN_TYPE,ulTinType);

    #else

    ulTinType = Stub_NAS_MML_GetTinType();
    #endif
    return ulTinType;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SendTimerStateNotify
 Description     : 给MMC发送LMM_MMC_TIMER_STATE_NOTIFY消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2012-2-28  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SendTimerStateNotify
(
    NAS_LMM_PTL_TI_ENUM_UINT16      ulTimerId,
    LMM_MMC_TIMER_STATE_ENUM_UINT32  ulTimerState
)
{
    LMM_MMC_TIMER_STATE_NOTIFY_STRU           *pstTimerStateMsg;

    /* 申请MMC内部消息 */
    pstTimerStateMsg = (VOS_VOID *) NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_TIMER_STATE_NOTIFY_STRU));

    NAS_EMM_PUBU_LOG2_INFO("NAS_EMM_SendTimerStateNotify", ulTimerId, ulTimerState);
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_SendTimerStateNotify_ENUM,LNAS_FUNCTION_LABEL1,
                                        ulTimerId,
                                        ulTimerState);

    if (NAS_LMM_NULL_PTR == pstTimerStateMsg)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_SendTimerStateNotify: MSG ALLOC ERROR!!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_SendTimerStateNotify_ENUM,LNAS_NULL_PTR);
        return ;
    }

    /* 清空 */
    NAS_LMM_MEM_SET_S(  pstTimerStateMsg,
                        sizeof(LMM_MMC_TIMER_STATE_NOTIFY_STRU),
                        0,
                        sizeof(LMM_MMC_TIMER_STATE_NOTIFY_STRU));

    /* 打包VOS消息头 */
    EMM_PUBU_COMP_MMC_MSG_HEADER((pstTimerStateMsg),
                             NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LMM_MMC_TIMER_STATE_NOTIFY_STRU));

    /* 填充消息ID */
    pstTimerStateMsg->ulMsgId           = ID_LMM_MMC_TIMER_STATE_NOTIFY;

    /* 填充消息体 */
    pstTimerStateMsg->ulOpId            = NAS_EMM_OPID_MMC;

    if (TI_NAS_EMM_PTL_T3412 == ulTimerId)
    {
        pstTimerStateMsg->bitOpT3412    = NAS_EMM_BIT_SLCT;
        pstTimerStateMsg->enT3412State  = ulTimerState;
    }
    else if (TI_NAS_EMM_PTL_T3423 == ulTimerId)
    {
        pstTimerStateMsg->bitOpT3423    = NAS_EMM_BIT_SLCT;
        pstTimerStateMsg->enT3423State  = ulTimerState;
    }
    else if (TI_NAS_EMM_PTL_T3402 == ulTimerId)
    {
        pstTimerStateMsg->bitOpT3402    = NAS_EMM_BIT_SLCT;
        pstTimerStateMsg->enT3402State  = ulTimerState;
    }
    else
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_SendTimerStateNotify: Timer type is err!!!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SendTimerStateNotify_ENUM,LNAS_ERROR);
    }

    /* 发送MMC内部消息 */
    NAS_LMM_SendLmmMmcMsg(pstTimerStateMsg);

    return;
}


/*****************************************************************************
 Function Name  : LNAS_LPSOM_GetCampedCellInfo()
 Description    : 提供给PS OM的API，用于获取TA LIST、GUTI、IMSI等信息
 Input          : LPS_NAS_MM_TA_LIST_STRU *pstRegPlmnTaList,
                  LPS_NAS_IMSI_STRU *pstImsiInfo,LPS_NAS_MM_GUTI_STRU *pstGutiInfo
 Output         : LPS_NAS_MM_TA_LIST_STRU *pstRegPlmnTaList,
                  LPS_NAS_IMSI_STRU *pstImsiInfo,LPS_NAS_MM_GUTI_STRU *pstGutiInfo
 Return Value   : VOS_VOID

 History        :
      1.zhangwei 00103912      2011-05-25  Draft Enact
*****************************************************************************/
VOS_VOID LNAS_LPSOM_GetCampedCellInfo(LPS_NAS_MM_TA_LIST_STRU *pstRegPlmnTaList,
    LPS_NAS_IMSI_STRU *pstImsiInfo,LPS_NAS_MM_GUTI_STRU *pstGutiInfo)
{
    VOS_UINT8                          *pucImsi;

    pucImsi = (VOS_UINT8 *)NAS_LMM_GetEmmInfoUeidImsiAddr();
    NAS_LMM_MEM_CPY_S(  pstRegPlmnTaList,
                        sizeof(LPS_NAS_MM_TA_LIST_STRU),
                        NAS_LMM_GetEmmInfoNetInfoTaiListAddr(),
                        sizeof(NAS_MM_TA_LIST_STRU));
    NAS_LMM_MEM_CPY_S(  pstGutiInfo,
                        sizeof(LPS_NAS_MM_GUTI_STRU),
                        NAS_LMM_GetEmmInfoUeidGutiAddr(),
                        sizeof(NAS_MM_GUTI_STRU));
    NAS_LMM_MEM_CPY_S(  &(pstImsiInfo->aucImsi[0]),
                        LPS_NAS_MM_MAX_UEID_BUF_SIZE,
                        pucImsi,
                        NAS_LMM_NVIM_IMSI_FILE_LEN);

    return;
}
/*****************************************************************************
 Function Name  : NAS_EMM_IsCsPsUeMode
 Description    : 判断是否为CP/PS1或者CS/PS2
 Input          : None
 Output         : None
 Return Value   : VOS_UINT32

 History        :
      1.lihong00150010      2011-08-27  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_EMM_IsCsPsUeMode( VOS_VOID )
{
    NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32                   ulLteUeMode;
    ulLteUeMode  = NAS_LMM_GetEmmInfoUeOperationMode();

    if ((NAS_LMM_UE_CS_PS_MODE_1 == ulLteUeMode)
        || (NAS_LMM_UE_CS_PS_MODE_2 == ulLteUeMode))
    {
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}


/*****************************************************************************
 Function Name   : Nas_InitUeModeInfo
 Description     : 初始化GU的UE MODE 信息
 Input           : ulInfoType:
 Output          :
 Return          :
 History         :
     1.    hanlufeng 41410       2011-9-27   Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_PubmInfoUeModeInit(VOS_VOID)
{
    NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32       ulLteUeMode;
    NAS_EMM_PUB_INFO_STRU                       *pstPubInfo = NAS_LMM_GetEmmInfoAddr();


    /* 给全局变量赋值

    NAS_LMM_GU_UE_MODE_ENUM_UINT32              ulGuUeMode;
    NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32       ulLteUeMode;
    NAS_EMM_USAGE_SETTING_UINT8                 ulUsageSetting;
    NAS_LMM_CS_SERVICE_ENUM_UINT32              ulCsService;


    NAS_LMM_SUP_ENUM_UINT32                     aulLmmSupVoiceDomain[NAS_LMM_SUP_VOICE_DOMAIN_BUTT];
    NAS_LMM_VOICE_DOMAIN_ENUM_UINT32            ulVoiceDomain;

    NAS_LMM_SUP_ENUM_UINT32                     aulLmmSupSmsDomain[NAS_LMM_SUP_SMS_DOMAIN_BUTT];
    NAS_LMM_SUP_SMS_DOMAIN_ENUM_UINT32          ulSmsDomainPrefer;

    NAS_LMM_SUP_ENUM_UINT32                     ulLmmSupIms;
    NAS_LMM_SUP_ENUM_UINT32                     ulCSFBAvail;

    NAS_LMM_EMERGENCY_NUM_LIST_STRU             stEmergencyNumList;
    VOS_UINT8                                   ucNetFeature;
    VOS_UINT8                                   aucRsv1[3];
    NAS_LMM_ADDITIONAL_UPDATE_RSLT_ENUM_UINT32  ulAdditionUpRslt;
    */

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PubmInfoUeModeInit:  UE MODE init begin: ");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PubmInfoUeModeInit_ENUM,LNAS_BEGIN);


    /* 该值随后在读NV时更新 NAS_EMM_ReadNvUeOperationMode，届时也同步更新LTE UE MODE*/
    NAS_LMM_SetEmmInfoGuUeMode(NAS_LMM_GU_UE_MODE_PS);

    NAS_LMM_SetEmmInfoUeCenter(EMM_SETTING_DATA_CENTRIC);
    NAS_EMM_PUBU_LOG1_INFO("UE CENTER = ",
                            NAS_LMM_GetEmmInfoUeCenter());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_PubmInfoUeModeInit_ENUM,LNAS_EMM_UE_CENTER,
                            NAS_LMM_GetEmmInfoUeCenter());

    /* 生成对应的LTE UE MODE */
    ulLteUeMode  = NAS_LMM_GetEmmInfoUeOperationMode();
    NAS_LMM_SetEmmInfoUeOperationMode(ulLteUeMode);

    NAS_EMM_PUBU_LOG1_INFO("LTE UE MODE = ",
                            ulLteUeMode);

    pstPubInfo->ulCsService = NAS_LMM_CS_SERVICE_BUTT;  /* 该值随后在读NV时更新 */
    NAS_EMM_PUBU_LOG1_INFO("ulCsService = ",
                            pstPubInfo->ulCsService);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_PubmInfoUeModeInit_ENUM,LNAS_EMM_CSSERVICECFG,
                            pstPubInfo->ulCsService);

    pstPubInfo->aulLmmSupVoiceDomain[NAS_LMM_SUP_VOICE_DOMAIN_CS]  = NAS_LMM_NOT_SUP;
    pstPubInfo->aulLmmSupVoiceDomain[NAS_LMM_SUP_VOICE_DOMAIN_IMS] = NAS_LMM_NOT_SUP;
    NAS_EMM_PUBU_LOG2_INFO("aulLmmSupVoiceDomain CS and PS = ",
                            pstPubInfo->aulLmmSupVoiceDomain[NAS_LMM_SUP_VOICE_DOMAIN_CS],
                            pstPubInfo->aulLmmSupVoiceDomain[NAS_LMM_SUP_VOICE_DOMAIN_IMS]);
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_PubmInfoUeModeInit_ENUM,LNAS_EMM_VOICE_DOMAIN_CS_PS,
                            pstPubInfo->aulLmmSupVoiceDomain[NAS_LMM_SUP_VOICE_DOMAIN_CS],
                            pstPubInfo->aulLmmSupVoiceDomain[NAS_LMM_SUP_VOICE_DOMAIN_IMS]);

    /* 该值随后在读NV时更新 NAS_EMM_ReadNvVoiceDomain*/
    pstPubInfo->ulVoiceDomain = NAS_LMM_VOICE_DOMAIN_BUTT;
    NAS_EMM_PUBU_LOG1_INFO("ulVoiceDomain = ",
                            pstPubInfo->ulVoiceDomain);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_PubmInfoUeModeInit_ENUM,LNAS_EMM_VOICE_DOMAIN,
                            pstPubInfo->ulVoiceDomain);

    pstPubInfo->aulLmmSupSmsDomain[NAS_LMM_SUP_SMS_DOMAIN_SGS]  = NAS_LMM_NOT_SUP;
    pstPubInfo->aulLmmSupSmsDomain[NAS_LMM_SUP_SMS_DOMAIN_IP ]  = NAS_LMM_NOT_SUP;
    NAS_EMM_PUBU_LOG2_INFO("aulLmmSupSmsDomain SGS and IP = ",
                            pstPubInfo->aulLmmSupSmsDomain[NAS_LMM_SUP_SMS_DOMAIN_SGS],
                            pstPubInfo->aulLmmSupSmsDomain[NAS_LMM_SUP_SMS_DOMAIN_IP]);
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_PubmInfoUeModeInit_ENUM,LNAS_EMM_SMS_DOMAIN_SGS_IP,
                            pstPubInfo->aulLmmSupSmsDomain[NAS_LMM_SUP_SMS_DOMAIN_SGS],
                            pstPubInfo->aulLmmSupSmsDomain[NAS_LMM_SUP_SMS_DOMAIN_IP]);

    /* 由于暂不支持SMS，故填为无效值 */
    pstPubInfo->ulSmsDomainPrefer = NAS_LMM_SUP_SMS_DOMAIN_BUTT;
    NAS_EMM_PUBU_LOG1_INFO("ulSmsDomainPrefer = ",
                            pstPubInfo->ulSmsDomainPrefer);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_PubmInfoUeModeInit_ENUM,LNAS_EMM_SMS_DOMAIN_PREFER,
                            pstPubInfo->ulSmsDomainPrefer);

    pstPubInfo->ulLmmSupIms = NAS_LMM_NOT_SUP;
    NAS_EMM_PUBU_LOG1_INFO("ulLmmSupIms = ",
                            pstPubInfo->ulLmmSupIms);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_PubmInfoUeModeInit_ENUM,LNAS_EMM_JUDGE_FLAG,
                            pstPubInfo->ulSmsDomainPrefer);

    /*
    pstPubInfo->ulCSFBAvail = NAS_LMM_NOT_SUP;
    NAS_EMM_PUBU_LOG1_INFO("ulCSFBAvail = ",
                            pstPubInfo->ulCSFBAvail);
    */
    /* 初始值赋为NOT_ATTACHED */
    pstPubInfo->enAdditionUpRslt = NAS_LMM_ADDITIONAL_UPDATE_NOT_ATTACHED;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PubmInfoUeModeInit:  UE MODE init END. ");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PubmInfoUeModeInit_ENUM,LNAS_END);

    return;
}

/*****************************************************************************
 Function Name   : Nas_SetLteUeModeInfo
 Description     : 设置GU的UE MODE, 给LNAS的内部模块调用;

 Input           : ulInfoType:
 Output          :
 Return          :
 History         :
    1.  H41410 20111012 第一阶段只允许修改 NAS_LMM_UEMODE_INFO_GU_UEMODE；

*****************************************************************************/
VOS_UINT32  Nas_LMM_SetLteUeModeInfo(
    NAS_LMM_UEMODE_TYPE_ENUM_UINT32     ulInfoType,
    NAS_LMM_UEMODE_INFO_STRU           *pstLmmUeModeInfo)
{

    NAS_EMM_PUBU_LOG2_INFO("Nas_LMM_SetLteUeModeInfo:  ulInfoType = , pstLmmUeModeInfo = ",
                            ulInfoType,
                            pstLmmUeModeInfo);
    TLPS_PRINT2LAYER_INFO2(Nas_LMM_SetLteUeModeInfo_ENUM,LNAS_EMM_UE_MODE_TYPE_INFO,
                            ulInfoType,
                            pstLmmUeModeInfo);

    /* 入参检查 */
    if((NAS_EMM_NULL_PTR == pstLmmUeModeInfo) ||
        (NAS_LMM_UEMODE_INFO_GU_UEMODE != ulInfoType))
    {

        NAS_EMM_PUBU_LOG_WARN("Nas_LMM_SetLteUeModeInfo: ERR.");
        TLPS_PRINT2LAYER_WARNING(Nas_LMM_SetLteUeModeInfo_ENUM,LNAS_ERROR);
        return  NAS_EMM_FAIL;
    }

    NAS_EMM_PUBU_LOG_INFO("Nas_LMM_SetLteUeModeInfo: NAS_LMM_UEMODE_INFO_STRU content are :");
    TLPS_PRINT2LAYER_INFO(Nas_LMM_SetLteUeModeInfo_ENUM,LNAS_EMM_UE_MODE_INFO);
    NAS_COMM_PrintArray(             NAS_COMM_GET_MM_PRINT_BUF(),
                                     (VOS_UINT8 *)pstLmmUeModeInfo,
                                     sizeof(NAS_LMM_UEMODE_INFO_STRU));

    /*Coverity 告警消除 2013-9-26 Begin*/
    NAS_LMM_SetGuUeMode(pstLmmUeModeInfo->u.ulGuUeMode);
    /*Coverity 告警消除 2013-9-26 End*/

    return  NAS_EMM_SUCC;
}

/*****************************************************************************
 Function Name   : Nas_GetLteUeModeInfo
 Description     : 设置GU的UE MODE，给LNAS的内部模块调用
 Input           : ulInfoType:
 Output          :
 Return          :
 History         :
    1.Hanlufeng 41410      2011-10-13  Draft Enact

*****************************************************************************/
VOS_UINT32  Nas_LMM_GetLteUeModeInfo(
    NAS_LMM_UEMODE_TYPE_ENUM_UINT32     ulInfoType,
    NAS_LMM_UEMODE_INFO_STRU           *pstLmmUeModeInfo)
{

    NAS_EMM_PUB_INFO_STRU                       *pstPubInfo = NAS_LMM_GetEmmInfoAddr();
    NAS_MML_MS_MODE_ENUM_UINT8         ucMsMode;
    ucMsMode = NAS_EMM_GetMsMode();

    NAS_EMM_PUBU_LOG2_INFO("Nas_LMM_GetLteUeModeInfo:  ulInfoType = , pstLmmUeModeInfo = ",
                            ulInfoType,
                            pstLmmUeModeInfo);
    TLPS_PRINT2LAYER_INFO2(Nas_LMM_GetLteUeModeInfo_ENUM,LNAS_EMM_UE_MODE_TYPE_INFO,
                            ulInfoType,
                            pstLmmUeModeInfo);

    /* 入参检查 */
    if((NAS_EMM_NULL_PTR == pstLmmUeModeInfo) ||
        (NAS_LMM_UEMODE_INFO_BUTT <= ulInfoType))
    {
        NAS_EMM_PUBU_LOG_WARN("Nas_LMM_GetLteUeModeInfo:  ERR");
        TLPS_PRINT2LAYER_WARNING(Nas_LMM_GetLteUeModeInfo_ENUM,LNAS_ERROR);
        return  NAS_EMM_FAIL;
    }

    switch(ulInfoType)
    {
        case    NAS_LMM_UEMODE_INFO_GU_UEMODE:
                pstLmmUeModeInfo->u.ulGuUeMode = ucMsMode;
                break;

        case    NAS_LMM_UEMODE_INFO_CENTER:
                pstLmmUeModeInfo->u.ulUsageSetting = NAS_LMM_GetEmmInfoUeCenter();
                break;

        case    NAS_LMM_UEMODE_INFO_LTE_UEMODE:
                pstLmmUeModeInfo->u.ulLteUeMode
                    = NAS_LMM_ComputeLteUeMode( ucMsMode,
                                                NAS_LMM_GetEmmInfoUeCenter());
                break;
        case    NAS_LMM_UEMODE_INFO_SUP_VOICE_DOMAIN:
                pstLmmUeModeInfo->u.aulLmmSupVoiceDomain[NAS_LMM_SUP_VOICE_DOMAIN_CS ]
                    = pstPubInfo->aulLmmSupVoiceDomain[NAS_LMM_SUP_VOICE_DOMAIN_CS ];
                pstLmmUeModeInfo->u.aulLmmSupVoiceDomain[NAS_LMM_SUP_VOICE_DOMAIN_IMS]
                    = pstPubInfo->aulLmmSupVoiceDomain[NAS_LMM_SUP_VOICE_DOMAIN_IMS ];
                break;

        case    NAS_LMM_UEMODE_INFO_VOICE_DOMAIN_PRE:
                pstLmmUeModeInfo->u.ulVoiceDomain
                    = pstPubInfo->ulVoiceDomain;
                break;

        case    NAS_LMM_UEMODE_INFO_SUP_SMS_DOMAIN:
                pstLmmUeModeInfo->u.aulLmmSupSmsDomain[NAS_LMM_SUP_SMS_DOMAIN_SGS ]
                    = pstPubInfo->aulLmmSupSmsDomain[NAS_LMM_SUP_SMS_DOMAIN_SGS];
                pstLmmUeModeInfo->u.aulLmmSupSmsDomain[NAS_LMM_SUP_SMS_DOMAIN_IP]
                    = pstPubInfo->aulLmmSupSmsDomain[NAS_LMM_SUP_SMS_DOMAIN_IP ];
                break;

        case    NAS_LMM_UEMODE_INFO_SMS_DOMAIN_PRE:
                pstLmmUeModeInfo->u.ulSmsDomainPrefer
                    = pstPubInfo->ulSmsDomainPrefer;
                break;

        case    NAS_LMM_UEMODE_INFO_SUP_IMS:
                pstLmmUeModeInfo->u.ulLmmSupIms
                    = pstPubInfo->ulLmmSupIms;
                break;

        case    NAS_LMM_UEMODE_INFO_NET_FEATURE:
                pstLmmUeModeInfo->u.ucNetFeature
                    = pstPubInfo->ucNetFeature;
                break;

        default:
                NAS_EMM_PUBU_LOG_WARN("Nas_LMM_GetLteUeModeInfo: TYPE ERR.");
                TLPS_PRINT2LAYER_WARNING(Nas_LMM_GetLteUeModeInfo_ENUM,LNAS_FUNCTION_LABEL1);
                return  NAS_EMM_FAIL;
    }

    NAS_EMM_PUBU_LOG_INFO("Nas_LMM_GetLteUeModeInfo: NAS_LMM_UEMODE_INFO_STRU content are :");
    TLPS_PRINT2LAYER_INFO(Nas_LMM_GetLteUeModeInfo_ENUM,LNAS_EMM_UE_MODE_INFO);
    NAS_COMM_PrintArray(             NAS_COMM_GET_MM_PRINT_BUF(),
                                     (VOS_UINT8 *)pstLmmUeModeInfo,
                                     sizeof(NAS_LMM_UEMODE_INFO_STRU));

    return  NAS_EMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LMM_SetGuUeMode
 Description     : GU UE MODE改变会导致LTE UE MODE修改
                   从GU的UE MODE和UE CENTER生成LTE UE MODE，并设置入全局变量
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.Hanlufeng 41410      2011-10-10  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LMM_SetGuUeMode
(
    NAS_LMM_GU_UE_MODE_ENUM_UINT32      ulGuUeMode
)
{
    NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32   ulLteUeModeCur;
    NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32   ulLteUeModeNew;
    NAS_MML_MS_MODE_ENUM_UINT8         ucMsMode;
    ucMsMode = NAS_EMM_GetMsMode();

    NAS_EMM_PUBU_LOG1_INFO("NAS_LMM_SetGuUeMode: income ulGuUeMode = ", ulGuUeMode);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_SetGuUeMode_ENUM,LNAS_EMM_GU_UE_MODE,ulGuUeMode);
    /* 获取当前的 LTE UE MODE */
    ulLteUeModeCur = NAS_LMM_ComputeLteUeMode(ucMsMode,
                                              NAS_LMM_GetEmmInfoUeCenter());

    /* 从GU的UE MODE和UE CENTER生成LTE UE MODE */
    ulLteUeModeNew = NAS_LMM_ComputeLteUeMode(ucMsMode, NAS_LMM_GetEmmInfoUeCenter());
    /* 打印变化前后的数据 */
    NAS_EMM_PUBU_LOG1_INFO(" NAS_LMM_SetGuUeMode: CUR LTE_UE_MODE = ", ulLteUeModeCur);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_SetGuUeMode_ENUM,LNAS_EMM_LTE_UE_MODE,ulLteUeModeCur);
    NAS_EMM_PUBU_LOG_INFO("  LTE_UE_MODE change   ===>");
    NAS_EMM_PUBU_LOG1_INFO(" NAS_LMM_SetGuUeMode: NEW LTE_UE_MODE = ", ulLteUeModeNew);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_SetGuUeMode_ENUM,LNAS_EMM_UE_MODE_CHANGE_TO,ulLteUeModeNew);


    /* LMM的全局变量设置GU UE MODE */
    NAS_LMM_SetEmmInfoGuUeMode(ulGuUeMode);
    NAS_LMM_SetEmmInfoUeOperationMode(ulLteUeModeNew);

    /* Ue Center 变化对应的各模块的操作 */
    NAS_LMM_LteModeChange(ulLteUeModeCur, ulLteUeModeNew);

    return;
}
/*****************************************************************************
 Function Name   : NAS_LMM_GetEmmInfoGuUeMode
 Description     : 返回GU的operation mode
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhangcaxia 00179470      2011-11-28  Draft Enact

*****************************************************************************/
NAS_LMM_GU_UE_MODE_ENUM_UINT32  NAS_LMM_GetEmmInfoGuUeMode(VOS_VOID)
{
    /* 返回GU OPERATION MODE，MML开放后用MML函数代替 */
    NAS_LMM_GU_UE_MODE_ENUM_UINT32      ulGuOperationMode;

    ulGuOperationMode       = NAS_LMM_GetEmmInfoAddr()->ulGuUeMode;
    return ulGuOperationMode;
}
/*****************************************************************************
 Function Name   : NAS_LMM_GetEmmInfoUeOperationMode
 Description     : 返回LTE的operation mode
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhangcaxia 00179470      2011-11-28  Draft Enact

*****************************************************************************/
NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32  NAS_LMM_GetEmmInfoUeOperationMode(VOS_VOID)
{
    /* 返回lte OPERATION MODE，
        实时获取GU OPRATION MODE，加上ue setting 计算出LTE OPERATION MODE*/
    NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32      ullteOperationMode;
    ullteOperationMode = NAS_LMM_ComputeLteUeMode( NAS_EMM_GetMsMode(),
                                            NAS_LMM_GetEmmInfoUeCenter());
    return ullteOperationMode;
}

/*****************************************************************************
 Function Name   : NAS_LMM_LteModeChange
 Description     : 各模块在此添加函数 ,以把LTE UE MODE的变更通知给自己
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.Hanlufeng 41410      2011-10-13  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LMM_LteModeChange(
    NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32   ulLteUeModeCur,
    NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32   ulLteUeModeNew)
{
    /* 需要及时了解LTE UE MODE变更的模块在此添加回调函数 */

    (void)ulLteUeModeCur;
    (void)ulLteUeModeNew;
    return;
}


/*****************************************************************************
 Function Name   :NAS_LMM_ComputeLteUeMode
 Description     :从GU的UE MODE和UE CENTER生成LTE UE MODE，
 Input           :
 Output          :
 Return          :
 History         :
    1.Hanlufeng 41410      2011-10-13  Draft Enact
    2.zhangcaixia 00179470 2011-12-1   mml打桩获取GU MODE
*****************************************************************************/
NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32   NAS_LMM_ComputeLteUeMode
(
    NAS_MML_MS_MODE_ENUM_UINT8          ulGuUeMode,
    NAS_EMM_USAGE_SETTING_UINT32        ulUeCenter
)
{

    NAS_EMM_PUBU_LOG2_INFO("NAS_LMM_ComputeLteUeMode: ulGuUeMode =,  ucUeCenter = ",
                             ulGuUeMode, ulUeCenter);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_ComputeLteUeMode_ENUM,LNAS_EMM_GU_UE_MODE,ulGuUeMode);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_ComputeLteUeMode_ENUM,LNAS_EMM_UE_CENTER,ulUeCenter);

    NAS_EMM_PUBU_LOG_INFO("Compute out : LTE UE MODE = ");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_ComputeLteUeMode_ENUM,LNAS_EMM_UE_CENTER);

    /* 从GU的UE MODE和UE CENTER生成LTE UE MODE */
    if( (NAS_MML_MS_MODE_PS_ONLY == ulGuUeMode) ||
        (NAS_MML_MS_MODE_CS_ONLY == ulGuUeMode))
    {   /* GU PS  ,GU的CS没有协议对应，SRS要求当做LTE 的PS来处理 */

        if(EMM_SETTING_DATA_CENTRIC == ulUeCenter)
        {
            NAS_EMM_PUBU_LOG_INFO(" NAS_LMM_UE_PS_MODE_2 ");
            TLPS_PRINT2LAYER_INFO(NAS_LMM_ComputeLteUeMode_ENUM,LNAS_FUNCTION_LABEL1);
            return  NAS_LMM_UE_PS_MODE_2;
        }
        else
        {
            NAS_EMM_PUBU_LOG_INFO(" NAS_LMM_UE_PS_MODE_1 ");
            TLPS_PRINT2LAYER_INFO(NAS_LMM_ComputeLteUeMode_ENUM,LNAS_FUNCTION_LABEL2);
            return  NAS_LMM_UE_PS_MODE_1;
        }
    }
    else
    {   /*CS_PS*/

        if(EMM_SETTING_DATA_CENTRIC == ulUeCenter)
        {
            NAS_EMM_PUBU_LOG_INFO(" NAS_LMM_UE_CS_PS_MODE_2 ");
            TLPS_PRINT2LAYER_INFO(NAS_LMM_ComputeLteUeMode_ENUM,LNAS_FUNCTION_LABEL3);
            return  NAS_LMM_UE_CS_PS_MODE_2;
        }
        else
        {
            NAS_EMM_PUBU_LOG_INFO("NAS_LMM_UE_CS_PS_MODE_1 ");
            TLPS_PRINT2LAYER_INFO(NAS_LMM_ComputeLteUeMode_ENUM,LNAS_FUNCTION_LABEL4);
            return  NAS_LMM_UE_CS_PS_MODE_1;
        }
    }
}
/*****************************************************************************
 Function Name   : NAS_EMM_lteRatIsExist
 Description     :
 Input           :
 Output          :
 Return          : NAS_LMM_FAIL:接入技术中无L
                   NAS_LMM_SUCC:接入技术中有L
 History         :
    1.ZHANGCAIXIA      2011-9-9  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_lteRatIsExist(VOS_VOID)
{
    if ( (NAS_LMM_RAT_PRIO_NULL ==  NAS_LMM_GetCurLtePrio())
      ||(NAS_LMM_RAT_PRIO_BUTT == NAS_LMM_GetCurLtePrio()))
    {
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_lteRatIsExist: MMC START REQ RAT LIST LTE NOT EXIST ");
        TLPS_PRINT2LAYER_ERROR1(NAS_EMM_lteRatIsExist_ENUM,LNAS_EMM_JUDGE_FLAG,NAS_LMM_FAIL);
        return NAS_LMM_FAIL;
    }
    return NAS_LMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_IsLteDisabled
 Description     : 判断LTE是否被DISABLE,是返回NAS_LMM_SUCC，反之返回NAS_LMM_FAIL
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-11-10  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_IsLteDisabled( VOS_VOID )
{
    if(NAS_LMM_LTE_DISABLED == NAS_EMM_GetLteEnableSta())
    {
        NAS_LMM_EMM_PLMN_LOG_INFO("NAS_EMM_IsLteDisabled:LTE DISABLTED.");
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_IsLteDisabled_ENUM,LNAS_EMM_JUDGE_FLAG,NAS_LMM_SUCC);
        return NAS_LMM_SUCC;
    }

    return NAS_LMM_FAIL;
}
/*****************************************************************************
 Function Name   : NAS_EMM_SendMmCombinedStartNotifyReq
 Description     : 向MM发送LMM_MM_COMBINED_START_NOTIFY_REQ消息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-11-15  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_SendMmCombinedStartNotifyReq
(
    MM_LMM_COMBINED_TYPE_ENUM_UINT32    enCombinedType
)
{
    LMM_MM_COMBINED_START_NOTIFY_REQ_STRU   *pstMmComStartNotfiyReq = VOS_NULL_PTR;

    /* 申请DOPRA消息 */
    pstMmComStartNotfiyReq = (VOS_VOID *) NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MM_COMBINED_START_NOTIFY_REQ_STRU));
    if (NAS_LMM_NULL_PTR == pstMmComStartNotfiyReq)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_SendMmCombinedStartNotifyReq: MSG ALLOC ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SendMmCombinedStartNotifyReq_ENUM,LNAS_NULL_PTR);
        return ;
    }

    /* 清空 */
    NAS_LMM_MEM_SET_S(  pstMmComStartNotfiyReq,
                        sizeof(LMM_MM_COMBINED_START_NOTIFY_REQ_STRU),
                        0,
                        sizeof(LMM_MM_COMBINED_START_NOTIFY_REQ_STRU));

    /* 打包VOS消息头 */
    EMM_PUBU_COMP_MM_MSG_HEADER((pstMmComStartNotfiyReq),
                             NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LMM_MM_COMBINED_START_NOTIFY_REQ_STRU));

    /* 填充消息ID */
    pstMmComStartNotfiyReq->ulMsgId    = ID_LMM_MM_COMBINED_START_NOTIFY_REQ;

    /* 填充消息体 */
    pstMmComStartNotfiyReq->ulOpId     = NAS_EMM_OPID_MM;

    /* 填充联合流程类型 */
    pstMmComStartNotfiyReq->enCombinedType = enCombinedType;

    /* 发送DOPRA消息 */
    NAS_LMM_SendLmmMmcMsg((VOS_VOID*)pstMmComStartNotfiyReq);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SetTauTypeNoProcedure
 Description     : 未发起TAU流程时UE当前是否有能力发起联合TAU来填写TAU类型
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-11-15  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_SetTauTypeNoProcedure( VOS_VOID )
{
    /* LMM会根据当前注册域来填写TAU请求类型，如果当前注册域为CS+PS，则TAU请求类
       型填为MMC_LMM_COMBINED_TA_LA_UPDATING；如果当前注册域为PS，则TAU请求类型
       填为MMC_LMM_TA_UPDATING；*/
    if (NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain())
    {
        NAS_EMM_TAU_SaveTAUtype(NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_UPDATING);
    }
    else if (NAS_LMM_REG_DOMAIN_PS == NAS_LMM_GetEmmInfoRegDomain())
    {
        NAS_EMM_TAU_SaveTAUtype(NAS_EMM_CN_TAU_TYPE_TA_UPDATING);
    }
    else
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_SetTauTypeNoProcedure: Reg Domain is NULL!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SetTauTypeNoProcedure_ENUM,LNAS_ERROR);
    }
}

/*****************************************************************************
 Function Name   : NAS_LMM_SetEmmInfoUeRadioCapChg
 Description     : UE无线能力设置
 Input           : NAS_LMM_UE_RADIO_CAP_CHANGE_ENUM_UINT32 当前更新类型和上次
                   更新类型
 Output          : UE能力更新类型是否刷新
 Return          : VOS_UINT32

 History         :
    1.lifuxin   00253982      2014-03-24  UE cap change

*****************************************************************************/
VOS_UINT32 NAS_LMM_SetEmmInfoUeRadioCapChg(
           NAS_LMM_UE_RADIO_CAP_CHANGE_ENUM_UINT32   enCurrentUeCapChg,
           NAS_LMM_UE_RADIO_CAP_CHANGE_ENUM_UINT32   enLastUeCapChg)
{
    NAS_EMM_PUBU_LOG_INFO("NAS_LMM_SetEmmInfoUeRadioCapChg is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_SetEmmInfoUeRadioCapChg_ENUM,LNAS_ENTRY);

    /*如果当前的更新类型大于等于上次的更新类型，则设置当前的UE能力改变，
      否则不再重新设置更新类型, 这里为什么要等于? 解释如下:
      等于时也认为需要更新，主要是考虑到NAS_LMM_ProcRrcSysCfgCnfNotSuspend
      函数在REG+REG_IMSI_DETACH_WATI_CN_DETACH_CNF状态和AUTH_INIT+AUTH_WAIT_CN_AUTH
      状态下的低优先级缓存分支，如果等于不认为需要更新，则当处理低优先级缓存的SYSCFG
      时会认为没有更新而直接退出
     */
    if(enCurrentUeCapChg >= enLastUeCapChg ||
       NAS_LMM_UE_RADIO_CAP_CHG_BUTT == enLastUeCapChg)
    {
        NAS_LMM_SetEmmInfoUeRadioCapChgFlag(enCurrentUeCapChg);
        return NAS_UE_CAP_CHG_HAVE_UPDATE;
    }
    else
    {
        return  NAS_UE_CAP_CHG_NO_UPDATE;
    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_RecordUeRadioAccCapChg
 Description     : 记录UE无线能力的变化
 Input           : VOS_UINT8     RRC上报的UE能力变化标识
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan  00193151      2012-01-13  Draft Enact
    2.lifuxin   00253982      2014-03-24  UE cap change

*****************************************************************************/
VOS_UINT32  NAS_EMM_RecordUeRadioAccCapChg(
    VOS_UINT8                           ucRadioAccCapChgInd )
{
    NAS_UE_CAP_CHG_UPDATE_TYPE_ENUM_UINT32      enResult = NAS_UE_CAP_CHG_BUTT;

    NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_RecordUeRadioAccCapChg: ucRadioAccCapChgInd value ="
                             , ucRadioAccCapChgInd);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_RecordUeRadioAccCapChg_ENUM,LNAS_EMM_RADIO_ACC_CAP_CHG,
                                ucRadioAccCapChgInd);
    /*如果当前的主状态是EMM_MS_DEREG，直接返回无线变更类型没有更新*/
    if(EMM_MS_DEREG == NAS_EMM_CUR_MAIN_STAT)
    {
        return  NAS_UE_CAP_CHG_NO_UPDATE;
    }

    /* LTE能力发生变化*/
    if(NAS_EMM_UE_LTE_RADIO_CAP_NOT_CHG != (ucRadioAccCapChgInd & NAS_EMM_BIT_3))
    {

        /* 如果是挂起态下收到L无线能力变化，为了回到L模发起TAU而非ATTACH，改为记录成GU变化 */
        if (NAS_LMM_CUR_LTE_SUSPEND == NAS_EMM_GetCurLteState())
        {
            NAS_EMM_PUBU_LOG_NORM("NAS_EMM_RecordUeRadioAccCapChg: LTE current is suspended, record GU change.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_RecordUeRadioAccCapChg_ENUM,LNAS_FUNCTION_LABEL1);
            enResult = NAS_LMM_SetEmmInfoUeRadioCapChg(NAS_LMM_UE_RADIO_CAP_GU_CHG,
                                                       NAS_LMM_GetEmmInfoUeRadioCapChgFlag());
        }
        else
        {
            enResult = NAS_LMM_SetEmmInfoUeRadioCapChg(NAS_LMM_UE_RADIO_CAP_LTE_CHG,
                                                       NAS_LMM_GetEmmInfoUeRadioCapChgFlag());
        }
    }

    /* GU能力发生变化 */
    else if (NAS_EMM_UE_GU_RADIO_CAP_NOT_CHG != (ucRadioAccCapChgInd & NAS_EMM_LOW_2_BITS_F))
    {
        enResult = NAS_LMM_SetEmmInfoUeRadioCapChg(NAS_LMM_UE_RADIO_CAP_GU_CHG,
                                                   NAS_LMM_GetEmmInfoUeRadioCapChgFlag());
    }

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* EHRPD能力发生变化，后续处理跟GU变化完全相同 */
    else if (NAS_EMM_UE_HRPD_RADIO_CAP_NOT_CHG != (ucRadioAccCapChgInd & NAS_EMM_FIFTH_BITS_F))
    {
        enResult = NAS_LMM_SetEmmInfoUeRadioCapChg(NAS_LMM_UE_RADIO_CAP_GU_CHG,
                                                   NAS_LMM_GetEmmInfoUeRadioCapChgFlag());
    }
    #endif

    /* 无变化 */
    else
    {
        enResult = NAS_LMM_SetEmmInfoUeRadioCapChg(NAS_LMM_UE_RADIO_CAP_NOT_CHG,
                                                   NAS_LMM_GetEmmInfoUeRadioCapChgFlag());
    }
    return enResult;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ClearUeRadioAccCapChgFlag
 Description     : 清除UE无线能力的变化的记录
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan  00193151      2012-01-16  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ClearUeRadioAccCapChgFlag(VOS_VOID)
{
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_ClearUeRadioAccCapChgFlag: UeRadioCapChgFlag is cleared !");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ClearUeRadioAccCapChgFlag_ENUM,LNAS_BEGIN);

    NAS_LMM_SetEmmInfoUeRadioCapChgFlag(NAS_LMM_UE_RADIO_CAP_NOT_CHG);

    return ;
}



/*****************************************************************************
 Function Name   : NAS_EMM_SomeStateRcvMsgSysInfoUeLteRadioCapChgProc
 Description     : 已记录LTE能力发生变化时收到RRC系统消息进行的公共处理。
 Input           : None
 Output          : None
 Return          : VOS_VOID
 History         :
    1.sunjitan  00193151      2012-01-16  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_SomeStateRcvMsgSysInfoLteRadioCapChgCommProc(VOS_VOID)
{
        VOS_UINT32                      ulRst = NAS_EMM_FAIL;

        /* 本地DETACH, 同时释放各模块资源:动态内存、赋初值 */
        NAS_EMM_LocalDetachProc();

        #if (FEATURE_PTM == FEATURE_ON)
        NAS_EMM_LocalDetachErrRecord(EMM_ERR_LOG_LOCAL_DETACH_TYPE_RADIO_CAP_CHANGE);
        #endif
        NAS_LMM_DeregReleaseResource();

        NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                              EMM_SS_DEREG_NORMAL_SERVICE,
                              TI_NAS_EMM_STATE_NO_TIMER);


        /* 向MMC发送本地LMM_MMC_DETACH_IND消息 */
        NAS_EMM_MmcSendDetIndLocal(MMC_LMM_L_LOCAL_DETACH_OTHERS);

        /* 重新发起ATTACH */
        ulRst = NAS_EMM_SendIntraAttachReq();
        if (NAS_EMM_SUCC != ulRst)
        {
            NAS_EMM_PUBU_LOG_ERR("NAS_EMM_SomeStateRcvMsgSysInfoLteRadioCapChgCommProc:  send INTRA ATTACH REQ ERR !");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_SomeStateRcvMsgSysInfoLteRadioCapChgCommProc_ENUM,LNAS_ERROR);
        }

    return;
}



/*****************************************************************************
 Function Name   : NAS_EMM_SendMmcInfoChangeNotify
 Description     : 通知MMC紧急呼号码列表，网侧是否支持IMS VOICE和紧急呼，以及
                   LTE的CS域能力
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.x00253310      2014-05-29  Draft Enact
*****************************************************************************/
VOS_VOID    NAS_EMM_SendMmcInfoChangeNotify( VOS_VOID )
{
    LMM_MMC_INFO_CHANGE_NOTIFY_STRU    *pstMmcInfoChangeNotify  = VOS_NULL_PTR;
    NAS_LMM_PUB_INFO_STRU              *pstPubInfo              = VOS_NULL_PTR;
    NAS_MML_EMERGENCY_NUM_LIST_STRU    *pstMmlEmerNumList       = VOS_NULL_PTR;
    NAS_LMM_ADDITIONAL_UPDATE_RSLT_ENUM_UINT32  enAddUpdateRslt;

    enAddUpdateRslt = NAS_EMM_GetAddUpdateRslt();

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_SendMmcInfoChangeNotify is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendMmcInfoChangeNotify_ENUM,LNAS_ENTRY);

    /* 申请MMC内部消息 */
    pstMmcInfoChangeNotify = (VOS_VOID *) NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_INFO_CHANGE_NOTIFY_STRU));
    if (NAS_LMM_NULL_PTR == pstMmcInfoChangeNotify)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_SendMmcInfoChangeNotify: MSG ALLOC ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SendMmcInfoChangeNotify_ENUM,LNAS_NULL_PTR);
        return ;
    }

    /* 清空 */
    NAS_LMM_MEM_SET_S(  pstMmcInfoChangeNotify,
                        sizeof(LMM_MMC_INFO_CHANGE_NOTIFY_STRU),
                        0,
                        sizeof(LMM_MMC_INFO_CHANGE_NOTIFY_STRU));

    /* 打包VOS消息头 */
    EMM_PUBU_COMP_MMC_MSG_HEADER((pstMmcInfoChangeNotify),
                             NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LMM_MMC_INFO_CHANGE_NOTIFY_STRU));

    /* 填充消息ID */
    pstMmcInfoChangeNotify->ulMsgId                 = ID_LMM_MMC_INFO_CHANGE_NOTIFY;

    /* 填充消息体 */
    pstMmcInfoChangeNotify->ulOpId                  = NAS_EMM_OPID_MM;

    pstMmlEmerNumList   = NAS_EMM_GetEmergencyListFromMml();
    pstPubInfo          = NAS_LMM_GetEmmInfoAddr();

    /* 填充紧急呼号码列表 */
    /* 与GU同事确认LMM_MMC_INFO_CHANGE_NOTIFY_STRU中所有bit 位都去掉 */
    /*pstMmcInfoChangeNotify->bitOpEmcNumList         = NAS_EMM_BIT_SLCT;*/
    pstMmcInfoChangeNotify->ucEmergencyNumAmount    = pstMmlEmerNumList->ucEmergencyNumber;
    NAS_LMM_MEM_CPY_S(  pstMmcInfoChangeNotify->astEmergencyNumList,
                        sizeof(LMM_MMC_EMERGENCY_NUM_STRU) * LMM_MMC_EMERGENCY_NUM_LIST_MAX_RECORDS,
                        pstMmlEmerNumList->aucEmergencyList,
                        sizeof(LMM_MMC_EMERGENCY_NUM_STRU) * LMM_MMC_EMERGENCY_NUM_LIST_MAX_RECORDS);

    /* 填充网侧是否支持IMS VOICE和紧急呼 */
    if (NAS_EMM_BIT_SLCT == pstPubInfo->bitOpNetFeature)
    {
        /*pstMmcInfoChangeNotify->bitOpImsVoPS        = NAS_EMM_BIT_SLCT;*/
        pstMmcInfoChangeNotify->enNwImsVoPS         = pstPubInfo->ucNetFeature & NAS_EMM_BIT_1;

        /*pstMmcInfoChangeNotify->bitOpEmcBS          = NAS_EMM_BIT_SLCT;*/
        pstMmcInfoChangeNotify->enNwEmcBS           = (pstPubInfo->ucNetFeature & NAS_EMM_BIT_2) >> NAS_EMM_MOVEMENT_1_BYTE;
    }
    else
    {
        /*pstMmcInfoChangeNotify->bitOpImsVoPS        = NAS_EMM_BIT_SLCT;*/
        pstMmcInfoChangeNotify->enNwImsVoPS         = LMM_MMC_NW_IMS_VOICE_NOT_SUPPORTED;

        /*pstMmcInfoChangeNotify->bitOpEmcBS          = NAS_EMM_BIT_SLCT;*/
        pstMmcInfoChangeNotify->enNwEmcBS           = LMM_MMC_NW_EMC_BS_NOT_SUPPORTED;
    }
    /* pstMmcInfoChangeNotify->bitOpLteCsCap           = NAS_EMM_BIT_SLCT; */
    if (NAS_LMM_ADDITIONAL_UPDATE_BUTT == enAddUpdateRslt)
    {
        pstMmcInfoChangeNotify->enLteCsCap          = LMM_MMC_LTE_CS_CAPBILITY_NO_ADDITION_INFO;
    }
    else
    {
        pstMmcInfoChangeNotify->enLteCsCap          = enAddUpdateRslt;
    }

    /* 发送MMC内部消息 */
    NAS_LMM_SendLmmMmcMsg((VOS_VOID*)pstMmcInfoChangeNotify);

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_SaveLastAttemptRegTa
 Description     : 将当前TA信息记录到LAST attempt TA中
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151      2012-07-10  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SaveLastAttemptRegTa(VOS_VOID)
{
    NAS_MM_NETWORK_ID_STRU             *pstPresentNetInfo       = NAS_EMM_NULL_PTR;
    NAS_LMM_NETWORK_INFO_STRU          *pstNetInfo              = NAS_EMM_NULL_PTR;
    NAS_MM_TA_STRU                     *pstLastAttmpRegTa       = NAS_EMM_NULL_PTR;
#if(FEATURE_ON == FEATURE_CSG)
    NAS_MM_CSG_INFO_STRU               *pstLastAttmpRegCsgInfo  = NAS_EMM_NULL_PTR;
#endif
    pstNetInfo                         = NAS_LMM_GetEmmInfoNetInfoAddr();
    pstPresentNetInfo                  = NAS_LMM_GetEmmInfoNetInfoPresentNetAddr();
    pstLastAttmpRegTa                  = NAS_LMM_GetEmmInfoNetInfoLastAttmpRegTaAddr();

    pstNetInfo->bitOpLastAttmpRegTa    = NAS_EMM_BIT_SLCT;
    pstLastAttmpRegTa->stTac.ucTac     = pstPresentNetInfo->stTac.ucTac;
    pstLastAttmpRegTa->stTac.ucTacCnt  = pstPresentNetInfo->stTac.ucTacCnt;
    NAS_LMM_PlmnCpy(&pstLastAttmpRegTa->stPlmnId, &pstPresentNetInfo->stPlmnId);

#if(FEATURE_ON == FEATURE_CSG)
    pstLastAttmpRegCsgInfo                      = NAS_LMM_GetEmmInfoNetInfoLastAttmpRegCsgInfoAddr();
    /* 记录celltype */
    pstLastAttmpRegCsgInfo->ucCellType          = pstPresentNetInfo->ucCellType;

    if(NAS_EMM_YES == NAS_LMM_IsCsgCampOn())
    {
        pstLastAttmpRegCsgInfo->ulCsgId         = pstPresentNetInfo->ulCsgId;
    }
    /* 尝试注册的小区是宏小区，则设置成无效值，下次驻留在CSG小区且CSG ID不在LIST中
        直接发起TAU */
    else
    {
        NAS_LMM_UndefCsgId(&(pstLastAttmpRegCsgInfo->ulCsgId));
    }
#endif

}

/*****************************************************************************
 Function Name   : NAS_EMM_IsT3411orT3402Running
 Description     : 判断是否有定时器3411或3402在运行
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151      2012-07-10  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_EMM_IsT3411orT3402Running
(
    NAS_LMM_PTL_TI_ENUM_UINT16  *pPtlTimerId
)
{
    VOS_UINT32    ulCheckRslt = NAS_EMM_NO;
    if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3411))
    {
        *pPtlTimerId = TI_NAS_EMM_PTL_T3411;
        ulCheckRslt = NAS_EMM_YES;
    }
    else if (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3402))
    {
        *pPtlTimerId = TI_NAS_EMM_PTL_T3402;
        ulCheckRslt = NAS_EMM_YES;
    }
    else
    {
        *pPtlTimerId = NAS_LMM_PTL_TI_BUTT;
        ulCheckRslt = NAS_EMM_NO;
    }

    return ulCheckRslt;
}

/*****************************************************************************
 Function Name   : NAS_LMM_IsRrcConnectStatusIdle
 Description     : 判断对当前RRC连接状态是否为IDLE
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.    sunjitan 00193151      2012-10-15  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LMM_IsRrcConnectStatusIdle(VOS_VOID)
{
    /* IDLE态和释放过程中对于MMC和RRC来讲都认为是IDLE, 仅LMM内部进行区分 */
    if ((NAS_EMM_CONN_IDLE == NAS_EMM_GetConnState())
        || (NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
        || (NAS_EMM_CONN_WAIT_SYS_INFO == NAS_EMM_GetConnState()))
    {
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;

}


/*****************************************************************************
 Function Name   : NAS_EMM_DisableLteCommonProc
 Description     : DISABL LTE的公共处理
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangchen 00209181      2012-11-07  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_DisableLteCommonProc( VOS_VOID )
{
   if(NAS_EMM_TAU_COMPLETE_VALID == NAS_EMM_TAU_GetEmmTauCompleteFlag())
   {
       NAS_LMM_PUBM_LOG_NORM("NAS_EMM_DisableLteCommonProc,TAU COMPLETE NEEDED DELAY");
       TLPS_PRINT2LAYER_INFO(NAS_EMM_DisableLteCommonProc_ENUM,LNAS_EMM_TAU_CMP_NEED_DELAY);

       /* 延迟500ms，是为了使得TAU COMPLETE消息能够尽量发送出去 */
       (VOS_VOID)TLPS_TaskDelay(500);
   }
   NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
}

/*****************************************************************************
 Function Name   : NAS_EMM_SendIntraEia0ActNotify
 Description     : 发送内部消息,通知EMM EIA0算法启用
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong 00150010      2012-10-19  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SendIntraEia0ActNotify( VOS_VOID )
{
    NAS_LMM_INTRA_EIA0_ACT_NOTIFY_STRU         *pstEia0ActNotify    = NAS_LMM_NULL_PTR;
    VOS_UINT32                                  ulLen               = NAS_EMM_NULL;

    /*确定消息长度*/
    ulLen = sizeof(NAS_LMM_INTRA_EIA0_ACT_NOTIFY_STRU);

    /*分配空间*/
    pstEia0ActNotify  = (VOS_VOID *)NAS_LMM_GetSendIntraMsgBuffAddr(ulLen);
    if(NAS_EMM_NULL_PTR == pstEia0ActNotify)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_SendIntraEia0ActNotify: INTRA MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SendIntraEia0ActNotify_ENUM,LNAS_NULL_PTR);
        return;
    }

    /* 打包VOS消息头 */
    NAS_EMM_INTRA_MSG_HEADER(pstEia0ActNotify,(ulLen-NAS_EMM_VOS_HEADER_LEN));

    /* 填充DOPRA消息ID    */
    pstEia0ActNotify->ulMsgId = ID_NAS_LMM_INTRA_EIA0_ACT_NOTIFY;

    /*发送内部消息入队列*/
    NAS_EMM_SEND_INTRA_MSG(pstEia0ActNotify);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_IsSmsOnlyCsfbNotPrefDisableNeeded
 Description     : 识别是否满足SMS only或者CS fallback not preferred disable L模的场景
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010 & wangchen 00209181      2012-06-28  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_EMM_IsSmsOnlyCsfbNotPrefDisableNeeded( VOS_VOID )
{
    NAS_LMM_ADDITIONAL_UPDATE_RSLT_ENUM_UINT32  enAddUpdateRslt;

    enAddUpdateRslt = NAS_EMM_GetAddUpdateRslt();

    if (NAS_LMM_REG_DOMAIN_CS_PS != NAS_LMM_GetEmmInfoRegDomain())
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_EMM_IsCsPs1DisableNeeded:Reg domain is not cs+ps");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsSmsOnlyCsfbNotPrefDisableNeeded_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_NO;
    }

    if (NAS_LMM_UE_CS_PS_MODE_1 != NAS_LMM_GetEmmInfoUeOperationMode())
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_EMM_IsCsPs1DisableNeeded:ue mode is not cs/ps1");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsSmsOnlyCsfbNotPrefDisableNeeded_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_NO;
    }

    if (NAS_EMM_SUCC != NAS_EMM_CheckMutiModeSupport())
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_EMM_IsCsPs1DisableNeeded:lte only");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsSmsOnlyCsfbNotPrefDisableNeeded_ENUM,LNAS_FUNCTION_LABEL3);
        return NAS_EMM_NO;
    }

    if ((NAS_LMM_ADDITIONAL_UPDATE_SMS_ONLY == enAddUpdateRslt)
            || (NAS_LMM_ADDITIONAL_UPDATE_CSFB_NOT_PREFERED == enAddUpdateRslt))
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_EMM_IsCsPs1DisableNeeded:SMS ONLY or CSFB not preferred");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsSmsOnlyCsfbNotPrefDisableNeeded_ENUM,LNAS_FUNCTION_LABEL4);
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}

/*****************************************************************************
 Function Name   : NAS_EMM_RecogAndProcSmsOnlyCsfbNotPrefDisable
 Description     : 识别SMS only或者CS fallback not preferred disable L模的场景，
                   释放链路
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong 00150010 & wangchen 00209181      2012-06-28  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_RecogAndProcSmsOnlyCsfbNotPrefDisable( VOS_VOID )
{
    if (NAS_EMM_YES == NAS_EMM_IsSmsOnlyCsfbNotPrefDisableNeeded())
    {

        NAS_EMM_DisableLteCommonProc();

    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_ClearEmcEsmMsg
 Description     : 清除紧急类型的ESM消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2012-10-31  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_ClearEmcEsmMsg( VOS_VOID )
{
    VOS_UINT8                          *pucEsmMsg   = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulRslt      = NAS_EMM_NULL;

    pucEsmMsg = NAS_LMM_GetEmmInfoEsmBuffAddr();

    if (NAS_EMM_NULL_PTR == pucEsmMsg)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_EMM_ClearEmcEsmMsg, Memory is null");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_ClearEmcEsmMsg_ENUM,LNAS_NULL_PTR);
        return ;
    }

    ulRslt = NAS_COMM_FreeBuffItem(NAS_COMM_BUFF_TYPE_EMM,(VOS_VOID *)pucEsmMsg);

    if (NAS_COMM_BUFF_SUCCESS != ulRslt)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_EMM_ClearEmcEsmMsg, Memory Free is not succ");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_ClearEmcEsmMsg_ENUM,LNAS_FAIL);
    }

    NAS_LMM_GetEmmInfoEsmBuffAddr() = NAS_EMM_NULL_PTR;

    return ;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SndEmcEsmMsg
 Description     : 发送紧急类型的ESM消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2012-12-13  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_SndEmcEsmMsg( VOS_VOID )
{
    NAS_EMM_ESM_MSG_BUFF_STRU          *pstEsmMsg   = NAS_EMM_NULL_PTR;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_SndEmcEsmMsg is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SndEmcEsmMsg_ENUM,LNAS_ENTRY);

    pstEsmMsg = (NAS_EMM_ESM_MSG_BUFF_STRU *)(VOS_VOID*)NAS_LMM_GetEmmInfoEsmBuffAddr();

    if (NAS_EMM_NULL_PTR == pstEsmMsg)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_EMM_SndEmcEsmMsg, Memory is null");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_SndEmcEsmMsg_ENUM,LNAS_NULL_PTR);
        return ;
    }

    NAS_EMM_SER_SendMrrcDataReq_ESMdata(&pstEsmMsg->stEsmMsg, pstEsmMsg->ulOpid);

    /* 紧急PDN引起SERVICE，然后被TAU打断，TAU成功完成发送紧急PDN建链请求消息后，
       需要清除SERVICE缓存中存储的紧急PDN建链请求消息，否则在SERVICE冲突处理时，
       还会发送一次 */
    NAS_EMM_SER_DeleteEsmMsg(pstEsmMsg->ulOpid);

    NAS_EMM_ClearEmcEsmMsg();

    return ;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SaveEmcEsmMsg
 Description     : 保存紧急类型的ESM消息
 Input           : pstMsgStru
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2012-10-31  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_SaveEmcEsmMsg
(
    VOS_VOID                           *pMsgStru
)
{
    NAS_EMM_ESM_MSG_BUFF_STRU          *pstEsmMsg       = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulBufSize       = NAS_EMM_NULL;
    EMM_ESM_DATA_REQ_STRU              *pstEsmDataReq   = NAS_EMM_NULL_PTR;

    if (NAS_EMM_NULL_PTR != NAS_LMM_GetEmmInfoEsmBuffAddr())
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_EMM_SaveEmcEsmMsg, Memory is already used!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_SaveEmcEsmMsg_ENUM,LNAS_NULL_PTR);
        NAS_EMM_ClearEmcEsmMsg();
    }

    pstEsmDataReq = (EMM_ESM_DATA_REQ_STRU*)pMsgStru;

    /* 分配空间 */
    ulBufSize = (sizeof(NAS_EMM_ESM_MSG_BUFF_STRU) +
                                        pstEsmDataReq->stEsmMsg.ulEsmMsgSize) - 4;

    NAS_LMM_GetEmmInfoEsmBuffAddr() = NAS_COMM_AllocBuffItem(   NAS_COMM_BUFF_TYPE_EMM,
                                                                ulBufSize);

    if (NAS_LMM_NULL_PTR != NAS_LMM_GetEmmInfoEsmBuffAddr())
    {
        pstEsmMsg = (NAS_EMM_ESM_MSG_BUFF_STRU*)(VOS_VOID*)NAS_LMM_GetEmmInfoEsmBuffAddr();

        /* 存储ESM消息 */
        pstEsmMsg->stEsmMsg.ulEsmMsgSize = pstEsmDataReq->stEsmMsg.ulEsmMsgSize;

        NAS_LMM_MEM_CPY_S(      pstEsmMsg->stEsmMsg.aucEsmMsg,
                                pstEsmDataReq->stEsmMsg.ulEsmMsgSize,
                                pstEsmDataReq->stEsmMsg.aucEsmMsg,
                                pstEsmDataReq->stEsmMsg.ulEsmMsgSize);

        /* 存储OPID */
        pstEsmMsg->ulOpid       = pstEsmDataReq->ulOpId;

        /* 存储紧急标识 */
        pstEsmMsg->ulIsEmcType  = pstEsmDataReq->ulIsEmcType;
    }
    else
    {
        NAS_LMM_PUBM_LOG_WARN( "NAS_EMM_SaveEmcEsmMsg: NAS_AllocBuffItem return null pointer.");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_SaveEmcEsmMsg_ENUM,LNAS_RETRUN_RST);
    }

    return ;
}

/*****************************************************************************
 Function Name   : NAS_EMM_IsDeregState
 Description     : 判断是否是DEREG态
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2012-10-31  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_IsDeregState( VOS_VOID )
{

    VOS_UINT32                          ulCurEmmStat            = NAS_EMM_NULL;

    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(   NAS_EMM_CUR_MAIN_STAT,
                                                NAS_EMM_CUR_SUB_STAT);

    /* 当前状态为RESUME+EMM_SS_RESUME_RRCORI_WAIT_SYS_INFO_IND时，如果是回退，
       则查看挂起前状态，否则查看恢复前状态 */
    if (ulCurEmmStat == NAS_LMM_PUB_COMP_EMMSTATE(  EMM_MS_RESUME,
                                                    EMM_SS_RESUME_RRCORI_WAIT_SYS_INFO_IND))
    {
        if ((NAS_LMM_SYS_CHNG_TYPE_REVERSE_RSL == NAS_EMM_GetResumeType())
            || (NAS_LMM_SYS_CHNG_TYPE_REVERSE_HO == NAS_EMM_GetResumeType())
            || (NAS_LMM_SYS_CHNG_TYPE_REVERSE_CCO == NAS_EMM_GetResumeType())
            || (NAS_LMM_SYS_CHNG_TYPE_REVERSE_REDIR == NAS_EMM_GetResumeType()))
        {
            /* 判断挂起前状态 */
            if (EMM_MS_DEREG == NAS_EMM_GetMsBefSuspend())
            {
                return NAS_EMM_YES;
            }

            return NAS_EMM_NO;
        }
        else
        {
            /* 判断恢复前状态 */
            if (EMM_MS_DEREG == NAS_EMM_GetMsBefResume())
            {
                return NAS_EMM_YES;
            }

            return NAS_EMM_NO;
        }
    }

    if (ulCurEmmStat == NAS_LMM_PUB_COMP_EMMSTATE(  EMM_MS_RESUME,
                                                    EMM_SS_RESUME_MMCORI_WAIT_SYS_INFO_IND))
    {
        /* 判断恢复前状态 */
        if (EMM_MS_DEREG == NAS_EMM_GetMsBefResume())
        {
            return NAS_EMM_YES;
        }

        return NAS_EMM_NO;
    }

    if (EMM_MS_DEREG == NAS_EMM_CUR_MAIN_STAT)
    {
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SendUsimStatusToRrc
 Description     : 发送RRC_MM_INFO_CHANGE_REQ给RRC,携带USI卡状态
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2013-1-6  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SendUsimStatusToRrc( LRRC_LNAS_SIM_STATUS_ENUM_UINT32  enSimStatus)
{
    LRRC_LNAS_INFO_STRU                   stNasInfo;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_SendSecuParamToRrc entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendUsimStatusToRrc_ENUM,LNAS_ENTRY);

    /*清空内存*/
    NAS_LMM_MEM_SET_S(&stNasInfo, sizeof(LRRC_LNAS_INFO_STRU), 0, sizeof(LRRC_LNAS_INFO_STRU));

    /*填充安全参数: Kasme + UL_NasCount*/
    stNasInfo.bitOpUsimStatus = NAS_EMM_BIT_SLCT;
    stNasInfo.enUsimStatus = enSimStatus;

    /*发送RRC_MM_INFO_CHANGE_REQ消息给RRC*/
    NAS_EMM_SendInfoChangeReqMsg(&stNasInfo);

    return;

}



VOS_VOID  NAS_LMM_ChangeRegRejCauseAvoidInvalidSim
(
    VOS_UINT8        *pucCause
)
{
    VOS_UINT32                          ulRslt     = MMC_LMM_FAIL;
    VOS_UINT32                          i          = 0;
    NAS_EMM_PUB_INFO_STRU              *pstPubInfo = NAS_EMM_NULL_PTR;

    pstPubInfo = NAS_LMM_GetEmmInfoAddr();
    ulRslt     = NAS_LMM_IsRegisteredInHplmn();

    for (i = 0; i < pstPubInfo->stConfCause.ucCauseNum; i++)
    {
        if (pstPubInfo->stConfCause.astAdaptCause[i].ucCnCause == *pucCause)
        {
            if (NAS_EMM_YES == ulRslt)
            {
                NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ChangeRegRejCauseAvoidInvalidSim:HPLMN entered.");
                TLPS_PRINT2LAYER_INFO(NAS_LMM_ChangeRegRejCauseAvoidInvalidSim_ENUM,LNAS_FUNCTION_LABEL1);
                /* 当前PLMN在HPLMN/EHPLMN中时，使用用户配置的HPLMN原因值 */
                NAS_EMM_HandleHplmnRejCauseChange(pucCause, pstPubInfo->stConfCause.astAdaptCause[i].ucHplmnCause);
            }
            else
            {
                NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ChangeRegRejCauseAvoidInvalidSim:NOT HPLMN entered.");
                TLPS_PRINT2LAYER_INFO(NAS_LMM_ChangeRegRejCauseAvoidInvalidSim_ENUM,LNAS_FUNCTION_LABEL2);
                /* 获取失败，或者当前PLMN不在HPLMN/EHPLMN中时，使用用户配置的非HPLMN原因值 */
                NAS_EMM_HandleVplmnRejCauseChange(pucCause, pstPubInfo->stConfCause.astAdaptCause[i].ucNotHplmnCause);
            }
            NAS_EMM_SndOmLogConfigNwCauseInfo(  pstPubInfo->stConfCause.astAdaptCause[i].ucCnCause,
                                               *pucCause,
                                                ulRslt);
            break;
        }
    }

    /* 不是用户需要修改的原因值，不做任何修改返回 */
    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_AdaptRegRejCau
 Description     : 判断是否为GCF等仪器测试模式(非装备模式的)，
                   如果是，不修改原因值；如果不是，根据自适应网络拒绝原因值开关
                   是否打开以及当前原因值来确定是否进行修改
 Input           : 原因值
 Output          : None
 Return          : VOS_VOID
 History         :
    1.sunjitan 00193151     2013-10-31  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_AdaptRegRejCau(VOS_UINT8 *pucCause)
{
    NAS_EMM_PUB_INFO_STRU              *pstPubInfo;


    pstPubInfo = NAS_LMM_GetEmmInfoAddr();
#if (VOS_OS_VER != VOS_WIN32)

    /* 是测试卡，不考虑特性开关直接走协议流程，不修改原因值 */
    if (PS_SUCC == LPS_OM_IsTestMode())
    {
        return;
    }
    if(VOS_NULL_PTR != pucCause)
    {
        NAS_MML_SetOriginalRejectCause(*pucCause);
    }
#endif

    /* 不是测试卡, 如果自适应网络拒绝原因值特性开关打开，修正原因值 */

    if (NAS_LMM_NULL < pstPubInfo->stConfCause.ucCauseNum)
    {
        /* coverity[var_deref_model] */
        NAS_LMM_ChangeRegRejCauseAvoidInvalidSim(pucCause);
    }

    return;

}


/* s00193151 end for 自适应网络拒绝原因值 */


/*****************************************************************************
 Function Name   : NAS_EMM_GetGulPubInfo
 Description     : 获取MMC的PUB INFO
 Input           : None
 Output          : None
 Return          : MMC_LMM_RESULT_ID_ENUM_UINT32

 History         :
    1.leili 00132387    2013-4-10  Draft Enact

*****************************************************************************/
MMC_LMM_RESULT_ID_ENUM_UINT32 NAS_EMM_GetGulPubInfo
(
    MMC_LMM_INFO_TYPE_ENUM_UINT32    ulInfoType,
    MMC_LMM_PUB_INFO_STRU           *pPubInfo
)
{
    MMC_LMM_RESULT_ID_ENUM_UINT32       ulRslt;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_GetGulPubInfo is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_GetGulPubInfo_ENUM,LNAS_ENTRY);

    #ifndef __PS_WIN32_RECUR__
    ulRslt = Nas_GetPubInfo (ulInfoType, pPubInfo);

    NAS_LMM_LogPubInfo(ulInfoType, pPubInfo,ulRslt);
    #else
    /*调用API的桩函数*/
    ulRslt = Stub_Nas_GetPubInfo(ulInfoType, pPubInfo);
    #endif

    return ulRslt;
}


/*****************************************************************************
 Function Name   : NAS_EMM_GetGuInfo
 Description     : 获取MMC的GU INFO
 Input           : None
 Output          : None
 Return          : MMC_LMM_RESULT_ID_ENUM_UINT32

 History         :
    1.leili 00132387    2013-4-10  Draft Enact

*****************************************************************************/
MMC_LMM_RESULT_ID_ENUM_UINT32 NAS_EMM_GetGuInfo
(
    NAS_GUMM_INFO_TYPE_ENUM_UINT32  ulInfoType,
    NAS_GUMM_INFO_STRU *            pstGuInfo
)
{
    MMC_LMM_RESULT_ID_ENUM_UINT32       ulRslt;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_GetGuInfo is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_GetGuInfo_ENUM,LNAS_ENTRY);

    #ifndef __PS_WIN32_RECUR__
    ulRslt = Nas_GetGuInfo (ulInfoType, pstGuInfo);

    NAS_LMM_LogGuInfo(ulInfoType, pstGuInfo,ulRslt);
    #else
    /*调用API的桩函数*/
    ulRslt = Stub_Nas_GetGuInfo(ulInfoType, pstGuInfo);
    #endif

    return ulRslt;
}

/*****************************************************************************
 Function Name   : NAS_EMM_GetMsNetworkCapability
 Description     : 获取MMC的MS NET CAP
 Input           : None
 Output          : None
 Return          : MMC_LMM_RESULT_ID_ENUM_UINT32

 History         :
    1.leili 00132387    2013-4-10  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_GetMsNetworkCapability
(
    NAS_MML_MS_NETWORK_CAPACILITY_STRU  *pstMsNetworkCapbility
)
{
    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_GetMsNetworkCapability is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_GetMsNetworkCapability_ENUM,LNAS_ENTRY);

    #ifndef __PS_WIN32_RECUR__
    NAS_MML_GetMsNetworkCapability (pstMsNetworkCapbility);

    NAS_LMM_LogMsNetworkCapabilityInfo(pstMsNetworkCapbility);

    #else
    /*调用API的桩函数*/
    Stub_NAS_MML_GetMsNetworkCapability(pstMsNetworkCapbility);
    #endif

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_GetUeIdTmsi
 Description     : 获取MML的TMSI信息
 Input           : None
 Output          : None
 Return          : MMC_LMM_RESULT_ID_ENUM_UINT32

 History         :
    1.leili 00132387    2013-4-10  Draft Enact

*****************************************************************************/
VOS_UINT8* NAS_EMM_GetUeIdTmsi(VOS_VOID)
{

    VOS_UINT8               *pucTmsi;
    #ifndef __PS_WIN32_RECUR__
    pucTmsi = NAS_MML_GetUeIdTmsi ();

    NAS_LMM_LogUeIdTmsiInfo (pucTmsi);
    #else
    pucTmsi = Stub_NAS_MML_GetUeIdTmsi();
    #endif
    return pucTmsi;

}

/*****************************************************************************
 Function Name   : NAS_EMM_GetLteCsServiceCfg
 Description     : 获取MML的lte cs service config信息
 Input           : None
 Output          : None
 Return          : MMC_LMM_RESULT_ID_ENUM_UINT32

 History         :
    1.leili 00132387    2013-4-11  Draft Enact

*****************************************************************************/
NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8  NAS_EMM_GetLteCsServiceCfg(  VOS_VOID  )
{
    NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8   ucRslt;

    #ifndef __PS_WIN32_RECUR__
    ucRslt = NAS_MML_GetLteCsServiceCfg ();

    NAS_LMM_LogCsServiceCfgInfo(ucRslt);
    #else

    ucRslt = Stub_NAS_MML_GetLteCsServiceCfg();
    #endif
    return ucRslt;
}

/*****************************************************************************
 Function Name   : NAS_EMM_GetPsBearerCtx
 Description     : 获取MML的PS BEARER CONTEXT信息
 Input           : None
 Output          : None
 Return          : NAS_MML_PS_BEARER_CONTEXT_STRU

 History         :
    1.leili 00132387    2013-4-11  Draft Enact

*****************************************************************************/
NAS_MML_PS_BEARER_CONTEXT_STRU* NAS_EMM_GetPsBearerCtx(VOS_VOID)
{
    NAS_MML_PS_BEARER_CONTEXT_STRU *pstPsBearerCtx;
    #ifndef __PS_WIN32_RECUR__
    pstPsBearerCtx   =  NAS_MML_GetPsBearerCtx();

    NAS_LMM_LogPsBearerCtxInfo(pstPsBearerCtx);

    #else
    pstPsBearerCtx = Stub_NAS_MML_GetPsBearerCtx();

    #endif

    return pstPsBearerCtx;
}

/*****************************************************************************
 Function Name   : NAS_EMM_GetUeEutranPsDrxLen
 Description     : 获取MML的UE EUTRAN PS DRX LEN信息
 Input           : None
 Output          : None
 Return          : VOS_UINT8

 History         :
    1.leili 00132387    2013-5-7  Draft Enact

*****************************************************************************/
VOS_UINT8  NAS_EMM_GetUeEutranPsDrxLen(  VOS_VOID  )
{
    VOS_UINT8                 ucRslt;
    #ifndef __PS_WIN32_RECUR__
    ucRslt = NAS_MML_GetUeEutranPsDrxLen ();

    NAS_LMM_LogUeEutranPsDrxLenInfo (ucRslt);

    #else
    ucRslt = Stub_NAS_MML_GetUeEutranPsDrxLen();

    #endif

    return ucRslt;

}
/*****************************************************************************
 Function Name   : NAS_EMM_GetNonDrxTimer
 Description     : 获取MML的NON DRX TIMER信息
 Input           : None
 Output          : None
 Return          : VOS_UINT8

 History         :
    1.leili 00132387    2013-5-7  Draft Enact

*****************************************************************************/
VOS_UINT8  NAS_EMM_GetNonDrxTimer(  VOS_VOID  )
{
    VOS_UINT8                 ucRslt;
    #ifndef __PS_WIN32_RECUR__
    ucRslt = NAS_MML_GetNonDrxTimer ();

    NAS_LMM_LogNonDrxTimerInfo (ucRslt);
    #else
    ucRslt = Stub_NAS_MML_GetNonDrxTimer();
    #endif
    return ucRslt;
}

/*****************************************************************************
 Function Name   : NAS_EMM_GetSplitPgCycleCode
 Description     : 获取MML的SPLIT PG CYCLE CODE信息
 Input           : None
 Output          : None
 Return          : VOS_UINT8

 History         :
    1.leili 00132387    2013-5-7  Draft Enact

*****************************************************************************/
VOS_UINT8  NAS_EMM_GetSplitPgCycleCode(  VOS_VOID  )
{
    VOS_UINT8                 ucRslt;
    #ifndef __PS_WIN32_RECUR__
    ucRslt = NAS_MML_GetSplitPgCycleCode ();

    NAS_LMM_LogDrxSplitPgCycleCodeInfo (ucRslt);
    #else
    ucRslt = Stub_NAS_MML_GetSplitPgCycleCode();
    #endif
    return ucRslt;
}
/*****************************************************************************
 Function Name   : NAS_EMM_GetSplitOnCcch
 Description     : 获取MML的SPLIT ON CCCH信息
 Input           : None
 Output          : None
 Return          : VOS_UINT8

 History         :
    1.leili 00132387    2013-5-7  Draft Enact

*****************************************************************************/
VOS_UINT8  NAS_EMM_GetSplitOnCcch(  VOS_VOID  )
{
    VOS_UINT8                 ucRslt;

    #ifndef __PS_WIN32_RECUR__
    ucRslt = NAS_MML_GetSplitOnCcch ();

    NAS_LMM_LogDrxSplitOnCcch(ucRslt);

    #else

    ucRslt = Stub_NAS_MML_GetSplitOnCcch();
    #endif

    return ucRslt;
}

/*****************************************************************************
 Function Name   : NAS_EMM_FillIEClassMark2
 Description     : 获取MML的CLASS MARK 2信息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387    2013-5-7  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_FillIEClassMark2(VOS_UINT8  *pClassMark2)
{

    #ifndef __PS_WIN32_RECUR__
    NAS_MML_Fill_IE_ClassMark2(pClassMark2);

    NAS_LMM_LogClassMark2Info(pClassMark2);

    #else

    Stub_NAS_MML_Fill_IE_ClassMark2(pClassMark2);
    #endif
    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_GetCsAttachAllowFlg
 Description     : 获取MML的CS ATTACH ALLOW FLAG信息
 Input           : None
 Output          : None
 Return          : VOS_UINT8

 History         :
    1.leili 00132387    2013-5-8  Draft Enact

*****************************************************************************/
VOS_UINT8  NAS_EMM_GetCsAttachAllowFlg(  VOS_VOID  )
{
    VOS_UINT8                 ucRslt;
    #ifndef __PS_WIN32_RECUR__
    ucRslt = NAS_MML_GetCsAttachAllowFlg ();

    /* coverity[unchecked_value] */
    NAS_LMM_LogCsAttachAllowFlgInfo (ucRslt);
    #else
    ucRslt = Stub_NAS_MML_GetCsAttachAllowFlg();
    #endif
    return ucRslt;
}
/*****************************************************************************
 Function Name   : NAS_EMM_GetPsAttachAllowFlg
 Description     : 获取MML的PS ATTACH ALLOW FLAG信息
 Input           : None
 Output          : None
 Return          : VOS_UINT8

 History         :
    1.leili 00132387    2013-5-8  Draft Enact

*****************************************************************************/
VOS_UINT8  NAS_EMM_GetPsAttachAllowFlg(  VOS_VOID  )
{
    VOS_UINT8                 ucRslt;
    #ifndef __PS_WIN32_RECUR__
    ucRslt = NAS_MML_GetPsAttachAllowFlg ();

    NAS_LMM_LogPsAttachAllowFlgInfo (ucRslt);
    #else
    ucRslt = Stub_NAS_MML_GetPsAttachAllowFlg();
    #endif

    return ucRslt;
}

/*****************************************************************************
 Function Name   : NAS_EMM_GetMsMode
 Description     : 获取MML的MS MODE信息
 Input           : None
 Output          : None
 Return          : VOS_UINT8

 History         :
    1.leili 00132387    2013-5-8  Draft Enact

*****************************************************************************/
NAS_MML_MS_MODE_ENUM_UINT8  NAS_EMM_GetMsMode(  VOS_VOID  )
{
    NAS_MML_MS_MODE_ENUM_UINT8         ucMsMode;
    #ifndef __PS_WIN32_RECUR__
    ucMsMode = NAS_MML_GetMsMode ();

    /* coverity[unchecked_value] */
    NAS_LMM_LogMsMode (ucMsMode);
    #else

    ucMsMode = Stub_NAS_MML_GetMsMode();
    #endif
    return ucMsMode;
}

/*****************************************************************************
 Function Name   : NAS_EMM_PlmnIdIsForbid
 Description     : 获取MML的PLMN IS FORBID信息
 Input           : None
 Output          : None
 Return          : VOS_UINT8

 History         :
    1.leili 00132387    2013-5-8  Draft Enact

*****************************************************************************/
MMC_LMM_PLMN_CTRL_ENUM_UINT32  NAS_EMM_PlmnIdIsForbid(MMC_LMM_PLMN_ID_STRU *pstPlmn )
{
    MMC_LMM_PLMN_CTRL_ENUM_UINT32      ulRslt;
    #ifndef __PS_WIN32_RECUR__
    ulRslt = Nas_PlmnIdIsForbid (pstPlmn);

    NAS_LMM_LogPlmnIsForbid (pstPlmn,ulRslt);
    #else

    ulRslt = Stub_Nas_PlmnIdIsForbid(pstPlmn);
    #endif
    return ulRslt;
}

/*****************************************************************************
 Function Name   : NAS_EMM_GetPsRegStatus
 Description     : 获取MML的PS REG STATUS信息
 Input           : None
 Output          : None
 Return          : VOS_UINT8

 History         :
    1.leili 00132387    2013-5-8  Draft Enact

*****************************************************************************/
NAS_MML_REG_STATUS_ENUM_UINT8  NAS_EMM_GetPsRegStatus( VOS_VOID)
{
    NAS_MML_REG_STATUS_ENUM_UINT8      ucPsRegStatus;
    #ifndef __PS_WIN32_RECUR__
    ucPsRegStatus = NAS_MML_GetPsRegStatus ();

    /* coverity[unchecked_value] */
    NAS_LMM_LogPsRegStatus (ucPsRegStatus);
    #else
    ucPsRegStatus = Stub_NAS_MML_GetPsRegStatus();
    #endif
    return ucPsRegStatus;
}

/*****************************************************************************
 Function Name   : NAS_EMM_GetSimType
 Description     : 获取MML的SIM TYPE信息
 Input           : None
 Output          : None
 Return          : VOS_UINT8

 History         :
    1.leili 00132387    2013-5-8  Draft Enact

*****************************************************************************/
NAS_MML_REG_STATUS_ENUM_UINT8  NAS_EMM_GetSimType( VOS_VOID)
{
    NAS_MML_SIM_TYPE_ENUM_UINT8      ucSimType;
    #ifndef __PS_WIN32_RECUR__
    ucSimType = NAS_MML_GetSimType ();

    /* coverity[unchecked_value] */
    NAS_LMM_LogSimType (ucSimType);
    #else
    ucSimType = Stub_NAS_MML_GetSimType();
    #endif
    return ucSimType;
}

/*****************************************************************************
 Function Name   : NAS_EMM_GetCardIMSI
 Description     : 获取USIM的IMSI信息
 Input           : None
 Output          : None
 Return          : VOS_UINT8

 History         :
    1.leili 00132387    2013-5-9  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_GetCardIMSI
(
    VOS_UINT8      *pucImsi
)
{
    VOS_UINT32      ulRslt;
    #ifndef __PS_WIN32_RECUR__
    ulRslt = USIMM_GetCardIMSI (pucImsi);

    /* coverity[unchecked_value] */
    NAS_LMM_LogCardIMSIInfo (pucImsi,ulRslt);
    #else
    ulRslt = Stub_USIMM_GetCardIMSI(pucImsi);
    #endif
    return ulRslt;
}

/*****************************************************************************
 Function Name   : NAS_EMM_IsServiceAvailable
 Description     : 获取USIM的service table中EMM MOBILE信息
 Input           : None
 Output          : None
 Return          : VOS_UINT8

 History         :
    1.leili 00132387    2013-5-9  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_IsServiceAvailable
(
    UICC_SERVICES_TYPE_ENUM_UINT32  enService
)
{
    VOS_UINT32      ulRslt;
    #ifndef __PS_WIN32_RECUR__
    ulRslt = USIMM_IsServiceAvailable (enService);
    /*lint -e718*/
    /*lint -e746*/
    /* coverity[unchecked_value] */
    NAS_LMM_LogUsimServiceInfo (enService,ulRslt);
    /*lint +e746*/
    /*lint +e718*/
    #else
    ulRslt = Stub_USIMM_IsServiceAvailable();
    #endif
    return ulRslt;
}

/*****************************************************************************
 Function Name   : NAS_EMM_IsAnnexP2ConditionSatisfied
 Description     : 判断是否满足24.008 annex P.2条件
 P.2 Activation of mobility management for IMS voice termination
 An MS activates mobility management for IMS voice termination when:
 1)  the MS's availability for voice calls in the IMS (see 3GPP TS 24.301 [120], subclause 3.1) changes from "not available" to "available";
 2)  the MS is configured with "Mobility Management for IMS Voice Termination" enabled as defined in 3GPP TS 24.167 [134];
 3)  the IMS voice over PS session indicator received for Iu mode has the value
 -   "IMS voice over PS session supported in Iu mode, but not supported in A/Gb mode", or
     the IMS voice over PS session indicator received for S1 mode has the value
 -   "IMS voice over PS session in S1 mode supported"; and
 4)  at least one of the two parameters voice domain preference for UTRAN and voice domain preference for E UTRAN as defined in 3GPP TS 24.167 [134] is not "CS voice only".
 The MS deactivates mobility management for IMS voice termination when the MS's availability for voice calls in the IMS (see 3GPP TS 24.301 [120], subclause 3.1) changes from "available" to "not available"
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2013-12-16  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_IsAnnexP2ConditionSatisfied(VOS_VOID)
{
    NAS_EMM_PUB_INFO_STRU              *pstPubInfo;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_IsAnnexP2ConditionSatisfied is entry");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_IsAnnexP2ConditionSatisfied_ENUM,LNAS_ENTRY);

    pstPubInfo = NAS_LMM_GetEmmInfoAddr();

    /*1.IMS voice从not available变为available
      2.NV Mobility Management for IMS Voice Termination为enable
      3.IMS voice over PS session in S1 mode supported或
        IMS voice over PS session supported in Iu mode, but not supported in A/Gb mode
      4.voice domain preference for UTRAN不为CS voice only 或
        voice domain preference for E-UTRAN不为CS voice only*/
    if ((VOS_TRUE == NAS_LMM_GetImsVoiceMMEnableFlg())
        &&((NAS_MML_NW_IMS_VOICE_SUPPORTED == NAS_LMM_GetLteNwImsVoiceSupportFlag())
            ||(NAS_MML_NW_IMS_VOICE_SUPPORTED == NAS_LMM_GetGUNwImsVoiceSupportFlg()))
        &&((NAS_EMM_BIT_SLCT == pstPubInfo->bitOpVoiceDomain)
            && (NAS_LMM_VOICE_DOMAIN_CS_ONLY != pstPubInfo->ulVoiceDomain)))
    {

        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}

/*****************************************************************************
 Function Name   : NAS_EMM_IsAnnexP4ConditionSatisfied
 Description     : 判断是否满足24.008 annex P.4条件
 P.3 Inter-system change between A/Gb mode and Iu mode
 1)  the upper layers have indicated that the MS is available for voice calls in the IMS (see 3GPP TS 24.301 [120], subclause 3.1);
 2)  the MS is configured with "Mobility Management for IMS Voice Termination" enabled as defined in 3GPP TS 24.167 [134];
 P.4 Inter-system change between A/Gb mode and S1 mode
 An MS is required to perform routing area updating for IMS voice termination at inter-system change from S1 mode to A/Gb mode and tracking area updating for IMS voice termination at inter-system change from A/Gb mode to S1 mode if:
 1)  conditions 1 and 2 of annex P.3 are fulfilled;
 2)  the "IMS voice over PS session indicator" received for S1 mode has the value "IMS voice over PS session in S1 mode supported"; and
 3)  the voice domain preference for E UTRAN as defined in 3GPP TS 24.167 [134] is not "CS voice only"
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2013-12-16  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_IsAnnexP4ConditionSatisfied(VOS_VOID)
{
    NAS_EMM_PUB_INFO_STRU              *pstPubInfo;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_IsAnnexP4ConditionSatisfied is entry");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_IsAnnexP4ConditionSatisfied_ENUM,LNAS_ENTRY);

    pstPubInfo = NAS_LMM_GetEmmInfoAddr();

     /*1.IMS voice为available
       2.NV Mobility Management for IMS Voice Termination为enable
       3.IMS voice over PS session in S1 mode supported
       4.voice domain preference for E-UTRAN不为CS voice only*/
    if ((MMC_LMM_IMS_VOICE_CAP_AVAILABLE == pstPubInfo->enImsaVoiceCap)
        &&(VOS_TRUE == NAS_LMM_GetImsVoiceMMEnableFlg())
        &&(NAS_MML_NW_IMS_VOICE_SUPPORTED == NAS_LMM_GetLteNwImsVoiceSupportFlag())
        &&((NAS_EMM_BIT_SLCT == pstPubInfo->bitOpVoiceDomain)
            && (NAS_LMM_VOICE_DOMAIN_CS_ONLY != pstPubInfo->ulVoiceDomain)))
    {

        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}


/*****************************************************************************
 Function Name   : NAS_EMM_IsEnterRegLimitService
 Description     : 判断是否进入REG+LIMIT_SERVICE态
 Input           : pstMsgStru
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2012-10-31  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_IsEnterRegLimitService( VOS_VOID )
{
    NAS_MM_NETWORK_ID_STRU             *pstPresentNwInfo = NAS_EMM_NULL_PTR;

    /* 如果无卡，则进入REG+LIMIT_SERVICE */
    if (NAS_LMM_SIM_STATUS_UNAVAILABLE == NAS_LMM_GetSimState())
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_IsEnterRegLimitService:NO CARD");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsEnterRegLimitService_ENUM,LNAS_EMM_NO_CARD);
        return VOS_TRUE;
    }

    /* 如果卡无效，则进入REG+LIMIT_SERVICE */
    if (NAS_LMM_SIM_INVALID == NAS_LMM_GetPsSimValidity())
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_IsEnterRegLimitService:CARD INVALID");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsEnterRegLimitService_ENUM,LNAS_EMM_CARD_INVALID);
        return VOS_TRUE;
    }

    /* 如果注册状态为紧急注册，则进入REG+LIMIT_SERVICE */
    if (NAS_LMM_REG_STATUS_EMC_REGED == NAS_LMM_GetEmmInfoRegStatus())
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_IsEnterRegLimitService:EMC REGED");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsEnterRegLimitService_ENUM,LNAS_EMM_EMC_REG);
        return VOS_TRUE;
    }

    pstPresentNwInfo = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_PRESENT_NET_ID);

    /* 当前网络的小区是被禁小区，则进入REG+LIMIT_SERVICE */
    if (EMMC_EMM_NO_FORBIDDEN != pstPresentNwInfo->ulForbiddenInfo)
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_IsEnterRegLimitService:forbidden");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsEnterRegLimitService_ENUM,LNAS_EMM_FORBIDDEN);
        return VOS_TRUE;
    }

    /* 当前网络的小区是ANYCELL小区，则进入REG+LIMIT_SERVICE */
    if (EMMC_EMM_CELL_STATUS_ANYCELL == pstPresentNwInfo->ulCellStatus)
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_IsEnterRegLimitService:forbidden");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsEnterRegLimitService_ENUM,LNAS_FUNCTION_LABEL1);
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 Function Name   : NAS_EMM_TranStateRegNormalServiceOrRegLimitService
 Description     : 转到REG+NORMAL_SERVICE态或者REG+LIMIT_SERVICE态
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010    2012-12-18  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_TranStateRegNormalServiceOrRegLimitService(VOS_VOID)
{
    if (VOS_TRUE == NAS_EMM_IsEnterRegLimitService())
    {
        NAS_EMM_TAUSER_FSMTranState(    EMM_MS_REG,
                                        EMM_SS_REG_LIMITED_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);
    }
    else
    {
        NAS_EMM_TAUSER_FSMTranState(    EMM_MS_REG,
                                        EMM_SS_REG_NORMAL_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);
    }
}

#if (FEATURE_ON == FEATURE_DSDS)

VOS_VOID NAS_LMM_SndOmDsdsPreProcMsgInfo
(
    NAS_LMM_DSDS_MSG_TYPE_ENUM_UINT32                 enMsgType,
    VOS_UINT32                                        ulIndex
)
{
    NAS_LMM_DSDS_PREPROC_MSG_INFO_STRU            *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                                    ulMsgName = NAS_OM_LOG_DSDS_MSG_PREPROC;

    pstMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(NAS_LMM_DSDS_PREPROC_MSG_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_SndOmDsdsPreProcMsgInfo: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_SndOmDsdsPreProcMsgInfo_ENUM,LNAS_NULL_PTR);
        return;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LMM_DSDS_PREPROC_MSG_INFO_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;

    pstMsg->stMsgHeader.ulMsgName       = ulMsgName + PS_MSG_ID_DSDS_DEBUG_BASE;
    pstMsg->enMsgType                   = enMsgType;
    pstMsg->ulInputType                 = ulIndex;
    pstMsg->ulBeginMsgTotal             = g_astDsdsInputNotifyMsgNum[ulIndex].ulBeginMsgCnt;
    pstMsg->ulEndMsgTotal               = g_astDsdsInputNotifyMsgNum[ulIndex].ulEndMsgCnt;

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);

    NAS_LMM_FREE_MSG(pstMsg);

    return;
}



VOS_VOID NAS_LMM_SndOmDsdsSessionMsgInfo
(
    NAS_LMM_DSDS_MSG_TYPE_ENUM_UINT32                 enMsgType,
    MM_SESSION_TYPE_ENUM_UINT32                       enSessionType
)
{
    NAS_LMM_DSDS_SESSION_MSG_INFO_STRU            *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                                    ulMsgName = NAS_OM_LOG_DSDS_MSG_SEND;

    pstMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(NAS_LMM_DSDS_SESSION_MSG_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_SndDsdsSessionMsgInfo: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_SndOmDsdsSessionMsgInfo_ENUM,LNAS_NULL_PTR);
        return;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LMM_DSDS_SESSION_MSG_INFO_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;

    pstMsg->stMsgHeader.ulMsgName       = ulMsgName + PS_MSG_ID_DSDS_DEBUG_BASE;
    pstMsg->enMsgType                   = enMsgType;
    pstMsg->enOutputSessionType         = enSessionType;
    pstMsg->ulBeginMsgTotal             = g_astDsdsNotifyMsgNum[enSessionType].ulBeginMsgCnt;
    pstMsg->ulEndMsgTotal               = g_astDsdsNotifyMsgNum[enSessionType].ulEndMsgCnt;

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);

    NAS_LMM_FREE_MSG(pstMsg);

    return;
}


/*****************************************************************************
 Function Name   : NAS_LMM_SendRrcDsdsBeginNotify
 Description     : 组装消息ID_LRRC_LMM_BEGIN_SESSION_NOTIFY发送给MRRC模块进行处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.c00134407    2014-7-9  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SendRrcDsdsBeginNotify(LRRC_LNAS_SESSION_TYPE_ENUM_UINT8  ucSessionType)
{
    LRRC_LMM_BEGIN_SESSION_NOTIFY_STRU   *pstRrcBeginNotifyMsg;

    if(PS_FALSE == g_ulDsdsRFSharedFlag)
    {
        /*如果射频共享开关关闭，则不进行下面的处理*/
        NAS_EMM_PUBU_LOG_INFO("NAS_LMM_SendRrcDsdsBeginNotify: g_ulDsdsRFSharedFlag=PS_FALSE!!!");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_SendRrcDsdsBeginNotify_ENUM,LNAS_FUNCTION_LABEL1);
        return;
    }

    if(LRRC_LNAS_SESSION_TYPE_BUTT <= ucSessionType)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_EMM_PUBU_LOG_ERR("NAS_LMM_SendRrcDsdsBeginNotify: INPUT PARA ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_SendRrcDsdsBeginNotify_ENUM,LNAS_PARAM_INVALID);
        return;
    }

    /* 申请DOPRA消息 */
    pstRrcBeginNotifyMsg = (VOS_VOID *) NAS_LMM_ALLOC_MSG(sizeof(LRRC_LMM_BEGIN_SESSION_NOTIFY_STRU));
    if(NAS_EMM_PLMN_NULL_PTR == pstRrcBeginNotifyMsg)
    {
        return;
    }

    NAS_EMM_PUBU_LOG1_INFO("DSDS Protection procedure begin,SessionType = ",ucSessionType);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_SendRrcDsdsBeginNotify_ENUM,LNAS_EMM_SESSION_TYPE,ucSessionType);

    /* 设置为0 */
    NAS_LMM_MEM_SET_S(  pstRrcBeginNotifyMsg,
                        sizeof(LRRC_LMM_BEGIN_SESSION_NOTIFY_STRU),
                        0,
                        sizeof(LRRC_LMM_BEGIN_SESSION_NOTIFY_STRU));

    /* 打包VOS消息头 */
    NAS_EMM_SET_RRC_MSG_HEADER((pstRrcBeginNotifyMsg),
                                      NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LRRC_LMM_BEGIN_SESSION_NOTIFY_STRU));

    /* 填充消息ID */
    pstRrcBeginNotifyMsg->enMsgId          = ID_LRRC_LMM_BEGIN_SESSION_NOTIFY;

    /* 填充消息体 */
     pstRrcBeginNotifyMsg->enSessionType            = ucSessionType;

    /* 发送DOPRA消息 */
    NAS_LMM_SEND_MSG(                   pstRrcBeginNotifyMsg);

    /*发送完begin消息后，将对应session type的计数加1*/
    g_astDsdsNotifyMsgNum[ucSessionType].ulBeginMsgCnt++;

    /* DSDS发送消息信息勾包出来 */
    NAS_LMM_SndOmDsdsSessionMsgInfo(NAS_LMM_DSDS_MSG_TYPE_BEGIN,ucSessionType);

    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_SendRrcDsdsEndNotify
 Description     : 组装消息ID_LRRC_LMM_END_SESSION_NOTIFY发送给MRRC模块进行处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.c00134407    2014-7-9  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_ENUM_UINT8  ucSessionType)
{
    LRRC_LMM_END_SESSION_NOTIFY_STRU   *pstRrcEndNotifyMsg;

    if(PS_FALSE == g_ulDsdsRFSharedFlag)
    {
        /*如果射频共享开关关闭，则不进行下面的处理*/
        NAS_EMM_PUBU_LOG_INFO("NAS_LMM_SendRrcDsdsEndNotify: g_ulDsdsRFSharedFlag=PS_SWITCH_OFF!!!");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_SendRrcDsdsEndNotify_ENUM,LNAS_FUNCTION_LABEL1);
        return;
    }

    if(LRRC_LNAS_SESSION_TYPE_BUTT <= ucSessionType)
    {
        /* 打印异常，ERROR_LEVEL */
        NAS_EMM_PUBU_LOG_ERR("NAS_LMM_SendRrcDsdsEndNotify: INPUT PARA ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_SendRrcDsdsEndNotify_ENUM,LNAS_PARAM_INVALID);
        return;
    }

    /*对LNAS流程进行异常保护，如果结束消息个数与开始消息个数相同，则说明已经发送了结束消息，不再重复发送*/
    if(((LRRC_LNAS_SESSION_TYPE_PS_ATTACH <= ucSessionType) && (LRRC_LNAS_SESSION_TYPE_PS_ESM >= ucSessionType))
        && (g_astDsdsNotifyMsgNum[ucSessionType].ulBeginMsgCnt <= g_astDsdsNotifyMsgNum[ucSessionType].ulEndMsgCnt))
    {
        NAS_EMM_PUBU_LOG1_WARN("NAS_LMM_SendRrcDsdsEndNotify: begin=end，session =",ucSessionType);
        TLPS_PRINT2LAYER_WARNING1(NAS_LMM_SendRrcDsdsEndNotify_ENUM,LNAS_EMM_SESSION_TYPE,ucSessionType);
        /* DSDS发送消息信息勾包出来 */
        NAS_LMM_SndOmDsdsSessionMsgInfo(NAS_LMM_DSDS_MSG_TYPE_END,ucSessionType);
        return;
    }

    /* 申请DOPRA消息 */
    pstRrcEndNotifyMsg = (VOS_VOID *) NAS_LMM_ALLOC_MSG(sizeof(LRRC_LMM_END_SESSION_NOTIFY_STRU));
    if(NAS_EMM_PLMN_NULL_PTR == pstRrcEndNotifyMsg)
    {
        return;
    }

    NAS_EMM_PUBU_LOG1_INFO("DSDS Protection procedure end,SessionType = ",ucSessionType);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_SendRrcDsdsEndNotify_ENUM,LNAS_FUNCTION_LABEL1,ucSessionType);

    /* 设置为0 */
    NAS_LMM_MEM_SET_S(  pstRrcEndNotifyMsg,
                        sizeof(LRRC_LMM_END_SESSION_NOTIFY_STRU),
                        0,
                        sizeof(LRRC_LMM_END_SESSION_NOTIFY_STRU));

    /* 打包VOS消息头 */
    NAS_EMM_SET_RRC_MSG_HEADER((pstRrcEndNotifyMsg),
                                      NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LRRC_LMM_END_SESSION_NOTIFY_STRU));

    /* 填充消息ID */
    pstRrcEndNotifyMsg->enMsgId          = ID_LRRC_LMM_END_SESSION_NOTIFY;

    /* 填充消息体 */
    pstRrcEndNotifyMsg->enSessionType            = ucSessionType;

    /* 发送DOPRA消息 */
    NAS_LMM_SEND_MSG(                   pstRrcEndNotifyMsg);

    /*若发送end消息，则将计数加1*/
    /*lint -e661*/
    g_astDsdsNotifyMsgNum[ucSessionType].ulEndMsgCnt++;
    /*lint +e661*/

    /* DSDS发送消息信息勾包出来 */
    NAS_LMM_SndOmDsdsSessionMsgInfo(NAS_LMM_DSDS_MSG_TYPE_END,ucSessionType);

    return;
}
#endif

/*****************************************************************************
Function Name   : NAS_EMM_HandleHplmnRejCauseChange
Description     : 如果NV配置的PS域HPLMN拒绝原因值为#17，则判断是否需要替换
Input           : VOS_UINT8    *pucRcvMsg, 当前处理的消息
Output          : None
Return          : None

History         :
    1.houzhiyuan 00285180    2014-10-20  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_HandleHplmnRejCauseChange(
    VOS_UINT8                          *pucRcvMsg,
    VOS_UINT8                           ucConfigCauseNvim
)
{
    if (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE == ucConfigCauseNvim)
    {
        if (VOS_TRUE != NAS_MML_GetHplmnPsRejChangeTo17Flg())
        {
            /* 如果替换后原因值为#17，且替换次数是已经达到上限，则不再替换 */
            return;
        }

        /* 计数器+1 */
        NAS_MML_IncHplmnPsRejCauseChangedCounter();
    }

    /* 如果替换后的原因值非#17，或替换后的原因值为#17且替换次数未达到上限，则替换 */
    *pucRcvMsg = ucConfigCauseNvim;
}

/*****************************************************************************
Function Name   : NAS_EMM_HandleVplmnRejCauseChange
Description     : 如果NV配置的PS域VPLMN拒绝原因值为#17，则判断是否需要替换
Input           : VOS_UINT8    *pucRcvMsg, 当前处理的消息
Output          : None
Return          : None

History         :
    1.houzhiyuan 00285180    2014-10-20  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_HandleVplmnRejCauseChange(
    VOS_UINT8                          *pucRcvMsg,
    VOS_UINT8                           ucConfigCauseNvim
)
{
    if (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE == ucConfigCauseNvim)
    {
        if (VOS_TRUE != NAS_MML_GetVplmnPsRejChangeTo17Flg())
        {
            /* 如果替换后原因值为#17，且替换次数是已经达到上限，则不再替换 */
            return;
        }

        /* 计数器+1 */
        NAS_MML_IncVplmnPsRejCauseChangedCounter();
    }

    /* 如果替换后的原因值非#17，或替换后的原因值为#17且替换次数未达到上限，则替换 */
    *pucRcvMsg = ucConfigCauseNvim;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ResetRejCauseChangedCounter
 Description     : 收到attach、tau Accept消息时reset计数器
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.houzhiyuan 00285180    2014-10-20  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_ResetRejCauseChangedCounter(VOS_VOID)
{
    NAS_MML_ResetHplmnPsRejCauseChangedCounter();
    NAS_MML_ResetVplmnPsRejCauseChangedCounter();
}

/*****************************************************************************
 Function Name   : NAS_EMM_IsNeedIgnoreHplmnAuthRej
 Description     : 获取是否需要忽略HPLMN下auth rej标识
 Input           : None
 Output          : None
 Return          : NAS_EMM_YES表示标识有效，需要忽略auth rej消息
                   NAS_EMM_NO表示标识无效，不需要忽略auth rej消息
 History         :
    1.h00285180      2014-12-17  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_IsNeedIgnoreHplmnAuthRej(VOS_VOID)
{
    NAS_MML_IGNORE_AUTH_REJ_INFO_STRU  *pstAuthRejInfo = NAS_EMM_NULL_PTR;

    pstAuthRejInfo = NAS_MML_GetAuthRejInfo();

    if (NAS_EMM_NULL_PTR == pstAuthRejInfo)
    {
        return NAS_EMM_NO;
    }

    /* VPLMN下,功能打开且忽略auth rej消息次数未达到最大值，则需要忽略 */
    if (   (NAS_EMM_YES == NAS_LMM_IsRegisteredInHplmn())
        && (VOS_TRUE    == pstAuthRejInfo->ucIgnoreAuthRejFlg)
        && (pstAuthRejInfo->ucHplmnPsAuthRejCounter < pstAuthRejInfo->ucMaxAuthRejNo))
    {
        pstAuthRejInfo->ucHplmnPsAuthRejCounter++;
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ResetHplmnAuthRejCout
 Description     : 复位PS域auth rej被忽略次数计数器，在attach/tau成功时调用
 Input           : None
 Output          : None
 Return          : None
 History         :
    1.h00285180      2014-12-17  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_ResetHplmnAuthRejCout(VOS_VOID)
{
    NAS_MML_IGNORE_AUTH_REJ_INFO_STRU  *pstAuthRejInfo = NAS_EMM_NULL_PTR;

    pstAuthRejInfo = NAS_MML_GetAuthRejInfo();

    if (pstAuthRejInfo)
    {
        pstAuthRejInfo->ucHplmnPsAuthRejCounter = 0;
    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_GetCurrentCampInfo
 Description     : 获取当前驻留的PLMN
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen 00209181 2014-09-05  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_GetCurrentCampInfo
(
    ESM_EMM_PLMN_ID_STRU *pstCurrentCampInfo
)
{
    NAS_MM_NETWORK_ID_STRU             *pstAreaInfo;

    NAS_LMM_EMMC_LOG_INFO("NAS_EMM_GetCurrentCampInfo enter");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_GetCurrentCampInfo_ENUM,LNAS_ENTRY);

    pstAreaInfo = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_PRESENT_NET_ID);

    NAS_LMM_MEM_CPY_S(  pstCurrentCampInfo,
                        sizeof(ESM_EMM_PLMN_ID_STRU),
                        &(pstAreaInfo->stPlmnId),
                        sizeof(ESM_EMM_PLMN_ID_STRU));

    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_GetEplmnList
 Description     : 获取等效PLMN列表
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen 00209181 2014-09-05  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_GetEplmnList
(
    NAS_ESM_PLMN_LIST_STRU *pstEplmnList
)
{

    NAS_LMM_EMMC_LOG_INFO("NAS_EMM_GetEplmnList enter");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_GetEplmnList_ENUM,LNAS_ENTRY);

    NAS_LMM_MEM_CPY_S(pstEplmnList,
                    sizeof(NAS_ESM_PLMN_LIST_STRU),
                    NAS_EMMC_GetEplmnListAddr(),
                    sizeof(MMC_LMM_EPLMN_STRU));

    return ;
}
/*****************************************************************************
 Function Name   : NAS_EMM_GetEplmnList
 Description     : 获取等效PLMN列表
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen 00209181 2014-09-05  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_GetNasRelease(VOS_VOID)
{

    NAS_LMM_EMMC_LOG_INFO("NAS_EMM_GetNasRelease enter");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_GetNasRelease_ENUM,LNAS_ENTRY);

    return NAS_LMM_GetNasRelease();
}

/*****************************************************************************
 Function Name   : NAS_EMM_SndOmLogUeIdInfo
 Description     : 勾出UE ID信息
 Input           : None
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao 00258641 2015-03-19  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_SndOmLogUeIdInfo(VOS_VOID)
{
    NAS_LMM_OM_LOG_UE_ID_INFO_STRU      *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LMM_OM_LOG_UE_ID_INFO_STRU *)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_LOG_UE_ID_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_SndOmLogForbPlmnInfo: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SndOmLogUeIdInfo_ENUM,LNAS_NULL_PTR);
        return;
    }

    NAS_LMM_MEM_SET_S(  pstMsg,
                        sizeof(NAS_LMM_OM_LOG_UE_ID_INFO_STRU),
                        0,
                        sizeof(NAS_LMM_OM_LOG_UE_ID_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LMM_OM_LOG_UE_ID_INFO_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName = ID_NAS_LMM_OM_LOG_UE_ID_INFO;
    NAS_LMM_MEM_CPY_S(&pstMsg->stMmUeId, sizeof(NAS_LMM_UEID_STRU), &g_stEmmInfo.stMmUeId, sizeof(NAS_LMM_UEID_STRU));
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_LMM_MEM_FREE(pstMsg);
}
/*****************************************************************************
 Function Name   : NAS_EMM_SndOmLogNvEpsLocInfo
 Description     : NV 中EPS LOC可维可测
 Input           : None
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao 00258641 2015-03-19  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_SndOmLogEpsLocInfo(VOS_VOID)
{
    NAS_LMM_OM_LOG_EPS_LOC_INFO_STRU          *pstMsg = VOS_NULL_PTR;
    NAS_LMM_UEID_STRU                         *pstUeId;
    NAS_MM_NETWORK_ID_STRU                    *pstNetId;

    pstMsg = (NAS_LMM_OM_LOG_EPS_LOC_INFO_STRU *)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_LOG_EPS_LOC_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMM_SndOmLogEpsLocInfo: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SndOmLogEpsLocInfo_ENUM,LNAS_NULL_PTR);
        return;
    }

    NAS_LMM_MEM_SET_S(  pstMsg,
                        sizeof(NAS_LMM_OM_LOG_EPS_LOC_INFO_STRU),
                        0,
                        sizeof(NAS_LMM_OM_LOG_EPS_LOC_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LMM_OM_LOG_EPS_LOC_INFO_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName   = ID_NAS_LMM_OM_LOG_EPS_LOC_INFO;
    pstMsg->enUpdateState           = NAS_EMM_UPDATE_STAE;

    pstUeId                         = NAS_LMM_GetEmmInfoUeidAddr();
    pstNetId                        = NAS_LMM_GetEmmInfoNetInfoLastRegNetAddr();
    pstMsg->bitOpGuti               = pstUeId->bitOpGuti;
    pstMsg->bitOpTai                = NAS_EMM_GetLVRTaiOpBit();
    pstMsg->bitOpUpState            = NAS_NVIM_BIT_SLCT;

    NAS_LMM_MEM_CPY_S(              &(pstMsg->stGuti),
                                    sizeof(NAS_LMM_GUTI_STRU),
                                    &(pstUeId->stGuti),
                                    sizeof(NAS_LMM_GUTI_STRU));


    NAS_LMM_MEM_CPY_S(              &(pstMsg->stLastRegTai.stPlmnId),
                                    sizeof(NAS_MM_PLMN_ID_STRU),
                                    &(pstNetId->stPlmnId),
                                    sizeof(NAS_MM_PLMN_ID_STRU));

    NAS_LMM_MEM_CPY_S(              &(pstMsg->stLastRegTai.stTac),
                                    sizeof(NAS_MM_TAC_STRU),
                                    &(pstNetId->stTac),
                                    sizeof(NAS_MM_TAC_STRU));

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_LMM_MEM_FREE(pstMsg);
}
/*****************************************************************************
 Function Name   : NAS_EMM_SndOmLogEpsSecContextInfo
 Description     : SecContext可维可测
 Input           : None
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao 00258641 2015-03-19  Draft Enact
    2.yanglei     00307272 2015-08-13 for KEY_INFO_REPORT2 新增7个参数
*****************************************************************************/
VOS_VOID NAS_EMM_SndOmLogEpsSecContextInfo(VOS_VOID)
{
    NAS_LMM_OM_LOG_EPS_SEC_CONTEXT_INFO_STRU                *pstMsg = VOS_NULL_PTR;
    NAS_LMM_SECU_CONTEXT_STRU                               *pstCurSecuCntxt = VOS_NULL_PTR;
    NAS_LMM_SECU_CONTEXT_STRU                               *pstNewMappedSecuCntxt = VOS_NULL_PTR;
    NAS_LMM_SECU_CONTEXT_STRU                               *pstNewNativeCurSecuCntxt = VOS_NULL_PTR;
    NAS_LMM_SECU_CONTEXT_STRU                               *pstNonCurNativeSecuCntxt = VOS_NULL_PTR;
    NAS_LMM_SECU_KEY_STRU                                   *pstCurNasKey = VOS_NULL_PTR;
    NAS_GUMM_UMTS_CONTEXT_STRU                              *pstUmtsSecuContext = VOS_NULL_PTR;
    NAS_MM_UE_NET_CAP_STRU                                  *pstUeNetCap = VOS_NULL_PTR;
    NAS_MM_MS_NET_CAP_STRU                                  *pstMsNetCap = VOS_NULL_PTR;



    pstMsg = (NAS_LMM_OM_LOG_EPS_SEC_CONTEXT_INFO_STRU *)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_LOG_EPS_SEC_CONTEXT_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMM_SndOmLogEpsSecContextInfo: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SndOmLogEpsSecContextInfo_ENUM,LNAS_NULL_PTR);
        return;
    }

    NAS_LMM_MEM_SET_S(  pstMsg,
                        sizeof(NAS_LMM_OM_LOG_EPS_SEC_CONTEXT_INFO_STRU),
                        0,
                        sizeof(NAS_LMM_OM_LOG_EPS_SEC_CONTEXT_INFO_STRU));


    /*获取当前安全上下文*/
    pstCurSecuCntxt                     = NAS_EMM_SecuGetCurCntxtAddr();
    pstNewMappedSecuCntxt               = NAS_EMM_GetSecuNewMappedCntxtAddr();
    pstNewNativeCurSecuCntxt            = NAS_EMM_GetSecuNewNativeCntxtAddr();
    pstNonCurNativeSecuCntxt            = NAS_EMM_GetSecuNonCurNativeCntxtAddr();
    pstCurNasKey                        = NAS_EMM_GetSecuCurNasKeyAddr();
    pstUmtsSecuContext                  = NAS_EMM_GetUmtsSecuContextAddr();
    pstUeNetCap                         = NAS_LMM_GetEmmInfoSecuParaUeNetCapAddr();
    pstMsNetCap                         = NAS_LMM_GetEmmInfoMsNetCapAddr();

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LMM_OM_LOG_EPS_SEC_CONTEXT_INFO_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName       = ID_NAS_LMM_OM_LOG_EPS_SEC_CONTEXT_INFO;
    NAS_LMM_MEM_CPY_S(&pstMsg->stCurSecContext, sizeof(NAS_LMM_SECU_CONTEXT_STRU), pstCurSecuCntxt, sizeof(NAS_LMM_SECU_CONTEXT_STRU));
    NAS_LMM_MEM_CPY_S(&pstMsg->stNewMappedSecuContext, sizeof(NAS_LMM_SECU_CONTEXT_STRU), pstNewMappedSecuCntxt, sizeof(NAS_LMM_SECU_CONTEXT_STRU));
    NAS_LMM_MEM_CPY_S(&pstMsg->stNewNativeSecuContext, sizeof(NAS_LMM_SECU_CONTEXT_STRU), pstNewNativeCurSecuCntxt, sizeof(NAS_LMM_SECU_CONTEXT_STRU));
    NAS_LMM_MEM_CPY_S(&pstMsg->stNonCurNativeSecuContext, sizeof(NAS_LMM_SECU_CONTEXT_STRU), pstNonCurNativeSecuCntxt, sizeof(NAS_LMM_SECU_CONTEXT_STRU));
    NAS_LMM_MEM_CPY_S(&pstMsg->stTempNasKey, sizeof(NAS_LMM_SECU_KEY_STRU), pstCurNasKey, sizeof(NAS_LMM_SECU_KEY_STRU));
    NAS_LMM_MEM_CPY_S(&pstMsg->stUmtsSecuContext, sizeof(NAS_GUMM_UMTS_CONTEXT_STRU), pstUmtsSecuContext, sizeof(NAS_GUMM_UMTS_CONTEXT_STRU));
    NAS_LMM_MEM_CPY_S(&pstMsg->stUeNetCap, sizeof(NAS_MM_UE_NET_CAP_STRU), pstUeNetCap, sizeof(NAS_MM_UE_NET_CAP_STRU));
    NAS_LMM_MEM_CPY_S(&pstMsg->stMsNetCap, sizeof(NAS_MM_MS_NET_CAP_STRU), pstMsNetCap, sizeof(NAS_MM_MS_NET_CAP_STRU));

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_LMM_MEM_FREE(pstMsg);
}
/*****************************************************************************
 Function Name   : NAS_EMM_SndOmLogUeImportantCapabilityInfo
 Description     : UE能力
 Input           : None
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao 00258641 2015-03-19  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_SndOmLogUeImportantCapabilityInfo(VOS_VOID)
{
    NAS_LMM_OM_LOG_UE_IMPORTANT_CAPABILITY_INFO_STRU      *pstMsg          = VOS_NULL_PTR;
    NAS_EMM_PUB_INFO_STRU                 *pstPubInfo      = VOS_NULL_PTR;

    pstPubInfo  = NAS_LMM_GetEmmInfoAddr();

    pstMsg = (NAS_LMM_OM_LOG_UE_IMPORTANT_CAPABILITY_INFO_STRU *)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_LOG_UE_IMPORTANT_CAPABILITY_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMM_SndOmLogUeImportantCapabilityInfo: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SndOmLogUeImportantCapabilityInfo_ENUM,LNAS_NULL_PTR);
        return;
    }

    NAS_LMM_MEM_SET_S(  pstMsg,
                        sizeof(NAS_LMM_OM_LOG_UE_IMPORTANT_CAPABILITY_INFO_STRU),
                        0,
                        sizeof(NAS_LMM_OM_LOG_UE_IMPORTANT_CAPABILITY_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LMM_OM_LOG_UE_IMPORTANT_CAPABILITY_INFO_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName = ID_NAS_LMM_OM_LOG_UE_IMPORTANT_CAPABILITY;
    pstMsg->ulVoiceDomain = pstPubInfo->ulVoiceDomain;
    pstMsg->enUeCenter = pstPubInfo->ulUsageSetting;
    pstMsg->ulNasRelease = pstPubInfo->ulNasRelease;
    NAS_LMM_MEM_CPY_S(&pstMsg->stRrcNasAc, sizeof(LRRC_NAS_AC_CLASS_STRU), &gstRrcNasAc, sizeof(LRRC_NAS_AC_CLASS_STRU));
    NAS_LMM_MEM_CPY_S(&pstMsg->stSupCodecList, sizeof(NAS_LMM_CODEC_LIST_STRU), &pstPubInfo->stSupCodecList, sizeof(NAS_LMM_CODEC_LIST_STRU));
    NAS_LMM_MEM_CPY_S(&pstMsg->stConfCause, sizeof(LNAS_LMM_CONFIG_NWCAUSE_STRU), &pstPubInfo->stConfCause, sizeof(LNAS_LMM_CONFIG_NWCAUSE_STRU));
    NAS_LMM_MEM_CPY_S(&pstMsg->stUeNetCap, sizeof(NAS_MM_UE_NET_CAP_STRU), &pstPubInfo->stUeNetCap, sizeof(NAS_MM_UE_NET_CAP_STRU));
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_LMM_MEM_FREE(pstMsg);
}
/*****************************************************************************
 Function Name   : NAS_EMM_SndOmLogConfigNwCauseInfo
 Description     : 网侧原因值转化信息上报
 Input           : VOS_UINT8                           ucCnCause,
                   VOS_UINT8                           ucModifiedCnCause
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao 00258641 2015-03-19  Draft Enact
    2.yanglei     00307272 2015-08-18  for KEY_INFO_REPORT3,新增信元上报

*****************************************************************************/
VOS_VOID NAS_EMM_SndOmLogConfigNwCauseInfo
(
    VOS_UINT8                           ucCnCause,
    VOS_UINT8                           ucModifiedCnCause,
    VOS_UINT32                          ucIsHplmn
)
{
    NAS_LMM_OM_LOG_CONFIG_NW_CAUSE_INFO_STRU *pstMsg          = VOS_NULL_PTR;
    NAS_EMM_PUB_INFO_STRU                    *pstPubInfo      = VOS_NULL_PTR;

    pstPubInfo  = NAS_LMM_GetEmmInfoAddr();

    pstMsg = (NAS_LMM_OM_LOG_CONFIG_NW_CAUSE_INFO_STRU *)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_LOG_CONFIG_NW_CAUSE_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMM_SndOmLogConfigNwCauseInfo: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SndOmLogConfigNwCauseInfo_ENUM,LNAS_NULL_PTR);
        return;
    }

    NAS_LMM_MEM_SET_S(  pstMsg,
                        sizeof(NAS_LMM_OM_LOG_CONFIG_NW_CAUSE_INFO_STRU),
                        0,
                        sizeof(NAS_LMM_OM_LOG_CONFIG_NW_CAUSE_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LMM_OM_LOG_CONFIG_NW_CAUSE_INFO_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName       = ID_NAS_LMM_OM_LOG_NW_CAUSE_CHANGE_INFO;
    pstMsg->ucCnCause                   = ucCnCause;
    pstMsg->ucModifiedCnCause           = ucModifiedCnCause;
    pstMsg->ucIsHplmn                   = ucIsHplmn;
    pstMsg->ucHplmnPsRejChangeTo17Flg   = NAS_MML_GetHplmnPsRejChangeTo17Flg();
    pstMsg->ucModifiedCnCause           = NAS_MML_GetVplmnPsRejChangeTo17Flg();
    NAS_LMM_MEM_CPY_S(  &pstMsg->stConfCause,
                        sizeof(LNAS_LMM_CONFIG_NWCAUSE_STRU),
                        &pstPubInfo->stConfCause,
                        sizeof(LNAS_LMM_CONFIG_NWCAUSE_STRU));

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_LMM_MEM_FREE(pstMsg);
    return;
}


/*****************************************************************************
 Function Name   : NAS_LMM_LteNoSubscribeIsRegisteredInHplmn
 Description     : 判断GU上面驻留的PLMN是否在HPLMN上
 Input           : None
 Output          : None
 Return          : VOS_UINT32
 History         :
    1.lifuxin 00253982      2015-04-02  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LMM_LteNoSubscribeIsRegisteredInHplmn(NAS_EMM_PLMN_ID_STRU  *pstPlmn)
{
    NAS_MM_PLMN_LIST_STRU               stEHplmnList    = {0};
    VOS_UINT32                          ulRslt          = MMC_LMM_FAIL;
    MMC_LMM_PUB_INFO_STRU               stPubInfo;
    NAS_EMM_PLMN_ID_STRU               *pstCurentPlmn   = VOS_NULL_PTR;

    pstCurentPlmn = pstPlmn;

    NAS_LMM_PUBM_LOG_NORM("NAS_LMM_LteNoSubscribeIsRegisteredInHplmn is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_LteNoSubscribeIsRegisteredInHplmn_ENUM,LNAS_ENTRY);

    NAS_LMM_MEM_SET_S(&stPubInfo, sizeof(MMC_LMM_PUB_INFO_STRU), 0, sizeof(MMC_LMM_PUB_INFO_STRU));

    /* 如果EHPLMN获取成功，且个数不为0，则判断当前PLMN是否在EHPLMN列表中，如果
       存在，则是注册在HPLMN上，否则就是注册到RPLMN上 */
    ulRslt = NAS_EMM_GetGulPubInfo(MMC_LMM_EHPLMN, &stPubInfo);

    if ((MMC_LMM_SUCC == ulRslt) && (stPubInfo.u.stEHplmnList.ulPlmnNum > 0))
    {
        NAS_LMM_MEM_CPY_S(  &stEHplmnList,
                            sizeof(NAS_MM_PLMN_LIST_STRU),
                            &stPubInfo.u.stEHplmnList,
                            sizeof(MMC_LMM_PLMN_LIST_STRU));

        if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_PlmnIDMatchHplmnList(pstCurentPlmn, &stEHplmnList))
        {
            return NAS_EMM_YES;
        }

        return NAS_EMM_NO;
    }

    /* 如果EHPLMN无效，则判断当前PLMN与HPLMN是否相同，如果相同，则是注册在HPLMN
       上，否则就是注册到RPLMN上 */
    ulRslt = NAS_EMM_GetGulPubInfo(MMC_LMM_HPLMN, &stPubInfo);
    if (MMC_LMM_SUCC != ulRslt)
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_LteNoSubscribeIsRegisteredInHplmn:Hplmn cannot be got!");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_LteNoSubscribeIsRegisteredInHplmn_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_NO;
    }

    if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_HplmnMatch((NAS_MM_PLMN_ID_STRU *)(&stPubInfo.u.stHplmn), pstCurentPlmn))
    {
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}

/*****************************************************************************
 Function Name   : NAS_LMM_LteNoSubscribeAtLeastHaveOneHplmn
 Description     : 判断PLMN列表中至少有一个在EHPLMN或者HPLMN中
 Input           : None
 Output          : None
 Return          : NAS_EMM_YES 至少有一个
                   NAS_EMM_NO 都没有
 History         :
    1.lifuxin 00253982      2015-04-02  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LMM_LteNoSubscribeAtLeastHaveOneHplmn(
                    MMC_LMM_LTE_NO_SUBSCRIBE_PLMN_LIST_STRU  *pstLteNoSubsPLmnList)
{
    VOS_UINT32 i = 0;

    for(i = 0; i < pstLteNoSubsPLmnList->ulPlmnNum; i++)
    {
        if(NAS_EMM_YES == NAS_LMM_LteNoSubscribeIsRegisteredInHplmn(
                        (NAS_EMM_PLMN_ID_STRU*)&pstLteNoSubsPLmnList->astPlmnId[i]))
        {
            /*如果找到了一个plmn在EHPLMN列表中，则返回YES*/
            return NAS_EMM_YES;
        }
    }

    /*如果都没有找到，则返回NO*/
    return NAS_EMM_NO;
}

/*****************************************************************************
 Function Name   : NAS_LMM_SendMmcEutranNotAllowNotify
 Description     : 向MMC通知LTE NO subscribe
 Input           : None
 Output          : None
 Return          : NAS_EMM_SEND_MMC_OK  -- 发送成功
 History         :
    1.lifuxin 00253982      2015-4-16  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LMM_SendMmcEutranNotAllowNotify(
                                            VOS_UINT8  ucNetWorkTriggerFlag,
                                            VOS_UINT32 ulTimerLen,
                                            MMC_LMM_LTE_NO_SUBSCRIBE_PLMN_LIST_STRU  *pstLteNoSubsPLmnList)
{
    LMM_MMC_EUTRAN_NOT_ALLOW_NOTIFY_STRU           *pstMmcEutranNotAllowMsg    = NAS_EMM_NULL_PTR;
    VOS_UINT32                                      ulSendResult;

    NAS_LMM_PUBM_LOG_INFO( "NAS_LMM_SendMmcEutranNotAllowNotify: enter");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_SendMmcEutranNotAllowNotify_ENUM,LNAS_ENTRY);

    /* 申请MMC内部消息 */
    pstMmcEutranNotAllowMsg = (VOS_VOID *)NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_EUTRAN_NOT_ALLOW_NOTIFY_STRU));

    if(NAS_EMM_NULL_PTR == pstMmcEutranNotAllowMsg)
    {
        NAS_LMM_PUBM_LOG_ERR( "NAS_LMM_SendMmcEutranNotAllowNotify: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_SendMmcEutranNotAllowNotify_ENUM,LNAS_NULL_PTR);
        ulSendResult = NAS_EMM_SEND_MMC_ERR;
        return ulSendResult;
    }

    /*lint -e960*/
    NAS_LMM_MEM_SET_S(  pstMmcEutranNotAllowMsg,
                        sizeof(LMM_MMC_EUTRAN_NOT_ALLOW_NOTIFY_STRU),
                        0,
                        sizeof(LMM_MMC_EUTRAN_NOT_ALLOW_NOTIFY_STRU));

    /* 填写ID_LMM_MMC_EUTRAN_NOT_ALLOW_NOTIFY 的DOPRA消息头 */
    EMM_PUBU_COMP_MMC_MSG_HEADER(pstMmcEutranNotAllowMsg,
            sizeof(LMM_MMC_EUTRAN_NOT_ALLOW_NOTIFY_STRU) - EMM_LEN_VOS_MSG_HEADER);
    /*lint +e960*/

    /* 填写ID_LMM_MMC_EUTRAN_NOT_ALLOW_NOTIFY 的消息ID标识 */
    pstMmcEutranNotAllowMsg->ulMsgId = ID_LMM_MMC_EUTRAN_NOT_ALLOW_NOTIFY;
    pstMmcEutranNotAllowMsg->ulOpId = 0;
    pstMmcEutranNotAllowMsg->ucPlmnNum = (VOS_UINT8)pstLteNoSubsPLmnList->ulPlmnNum;
    pstMmcEutranNotAllowMsg->ulTimerLen = ulTimerLen;
    pstMmcEutranNotAllowMsg->ucNetWorkTriggerFlag = ucNetWorkTriggerFlag;
    NAS_LMM_MEM_CPY_S(  &(pstMmcEutranNotAllowMsg->astPlmnIdList[0]),
                        sizeof(MMC_LMM_PLMN_ID_STRU) * MMC_LMM_MAX_EUTRAN_NOT_ALLOW_PLMN_NUM,
                        &(pstLteNoSubsPLmnList->astPlmnId[0]),
                        sizeof(MMC_LMM_PLMN_ID_STRU)*(pstLteNoSubsPLmnList->ulPlmnNum));

    /* 发送消息 */
    NAS_LMM_SendLmmMmcMsg(pstMmcEutranNotAllowMsg);

    ulSendResult = NAS_EMM_SEND_MMC_OK;

    return ulSendResult;
}

/*****************************************************************************
 Function Name   : NAS_LMM_LteNoSubscribeWithExtCauseHandle
 Description     : 4G未开户被网络侧拒绝携带了扩展原因值的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32
 History         :
    1.lifuxin 00253982      2015-04-02  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_LteNoSubscribeWithExtCauseHandle(
                               MMC_LMM_LTE_NO_SUBSCRIBE_PLMN_LIST_STRU  *pstLteNoSubsPLmnList)
{
    VOS_UINT32              ulTimerLen;

    NAS_LMM_PUBM_LOG_INFO( "NAS_LMM_LteNoSubscribeWithExtCauseHandle: enter");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_LteNoSubscribeWithExtCauseHandle_ENUM,LNAS_ENTRY);

    if(NAS_EMM_YES == NAS_LMM_LteNoSubscribeAtLeastHaveOneHplmn(pstLteNoSubsPLmnList))
    {
        /*HPLMN*/
        ulTimerLen = NAS_EMM_GetLteNoSubscribeNvConfigPublishmentTimerHplmnLen();
    }
    else
    {
        /*VPLMN*/
        ulTimerLen = NAS_EMM_GetLteNoSubscribeNvConfigPublishmentTimerVplmnLen();
    }

    /*被禁时间最大8小时*/
    if(ulTimerLen > NAS_MAX_EXT_PUBLISHMENT_TIMER_LEN)
    {
        ulTimerLen = NAS_MAX_EXT_PUBLISHMENT_TIMER_LEN;
    }

    ( VOS_VOID )NAS_LMM_SendMmcEutranNotAllowNotify(NAS_LMM_WITH_EXT_CAUSE, ulTimerLen, pstLteNoSubsPLmnList);

    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_LteNoSubscribeWithOutExtCauseHandle
 Description     : 4G未开户被网络侧拒绝携带了扩展原因值的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32
 History         :
    1.lifuxin 00253982      2015-04-02  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_LteNoSubscribeWithOutExtCauseHandle(
                        MMC_LMM_LTE_NO_SUBSCRIBE_PLMN_LIST_STRU  *pstLteNoSubsPLmnList)
{
    /*如果是测试卡，则直接退出*/
    if(PS_SUCC == LPS_OM_IsTestMode())
    {
        return;
    }

    /*非测试卡*/
    if(NAS_EMM_YES == NAS_LMM_LteNoSubscribeAtLeastHaveOneHplmn(pstLteNoSubsPLmnList))
    {
        NAS_LMM_PUBM_LOG_INFO( "NAS_LMM_LteNoSubscribeWithOutExtCauseHandle: Hplmn");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_LteNoSubscribeWithOutExtCauseHandle_ENUM,LNAS_FUNCTION_LABEL1);
        /*Hplmn*/
        /*Hplmn定制NV是打开的，而且没有在L上面注册成功过*/
        if((PS_TRUE == NAS_EMM_GetLteNoSubscribeNvConfigHplmnSwitch())
            && (NAS_LMM_NO_REG_SUCC_ON_LTE == NAS_EMM_GetLteNoSubscribeLteRegFlag()))
        {
            ( VOS_VOID )NAS_LMM_SendMmcEutranNotAllowNotify(
                                            NAS_LMM_WITHOUT_EXT_CAUSE,
                                            NAS_EMM_GetLteNoSubscribeNvConfigPublishmentTimerHplmnLen(),
                                            pstLteNoSubsPLmnList);

            #if (FEATURE_ON == FEATURE_PTM)
            NAS_EMM_ImprovePerformceeErrReport(EMM_OM_ERRLOG_IMPROVEMENT_TYPE_LTE_NO_SUBSCRIBE);
            #endif
        }
    }
    else
    {
        NAS_LMM_PUBM_LOG_INFO( "NAS_LMM_LteNoSubscribeWithOutExtCauseHandle: Vplmn");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_LteNoSubscribeWithOutExtCauseHandle_ENUM,LNAS_FUNCTION_LABEL2);
        /*Vplmn*/
        /*Vplmn定制NV是打开的*/
        if(PS_TRUE == NAS_EMM_GetLteNoSubscribeNvConfigVplmnSwitch())
        {
            ( VOS_VOID )NAS_LMM_SendMmcEutranNotAllowNotify(
                                            NAS_LMM_WITHOUT_EXT_CAUSE,
                                            NAS_EMM_GetLteNoSubscribeNvConfigPublishmentTimerVplmnLen(),
                                            pstLteNoSubsPLmnList);

            #if (FEATURE_ON == FEATURE_PTM)
            NAS_EMM_ImprovePerformceeErrReport(EMM_OM_ERRLOG_IMPROVEMENT_TYPE_LTE_NO_SUBSCRIBE);
            #endif
        }

    }

    return;
}
/*****************************************************************************
 Function Name   : NAS_LMM_ReadNvLmmSwitchPara
 Description     : 读取LMM开关控制NV,LNAS所有开关NV都将放入此NV中
 Input           : None
 Output          : None
 Return          : VOS_VOID
 History         :
    1.    leixiantiao 00258641      2015-06-18  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_ReadNvLmmSwitchPara(VOS_VOID )
{
    LNAS_NV_SWITCH_PARA_STRU              stNvSwitchPara;
    VOS_UINT32                            ulRslt      = NAS_LMM_NVIM_FAIL;
    VOS_UINT16                            usDataLen   = 0;

    NAS_LMM_MEM_SET_S(  &stNvSwitchPara,
                        sizeof(LNAS_NV_SWITCH_PARA_STRU),
                        0,
                        sizeof(LNAS_NV_SWITCH_PARA_STRU));

    /* 读NV */
    usDataLen = sizeof(LNAS_NV_SWITCH_PARA_STRU);
    ulRslt = NAS_LMM_NvimRead(EN_NV_ID_LNAS_SWITCH_PARA,
                              (VOS_VOID *)&(stNvSwitchPara),
                              &usDataLen);

    if(NAS_LMM_NVIM_OK != ulRslt)
    {
        /* 读NV失败则清空目标变量，所有相应NV都按默认值初始化 */
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_ReadNvLmmSwitchPara: read NV Fail.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_ReadNvLmmSwitchPara_ENUM,LNAS_FAIL);
    }

    g_aulNasFunFlg[0]     = *((VOS_UINT32 * )(&(stNvSwitchPara.stNasFunFlag01)));
    g_aulNasFunFlg[1]     = *((VOS_UINT32 * )(&(stNvSwitchPara.stNasFunFlag02)));
    g_aulNasFunFlg[2]     = *((VOS_UINT32 * )(&(stNvSwitchPara.stNasFunFlag03)));
    g_aulNasFunFlg[3]     = *((VOS_UINT32 * )(&(stNvSwitchPara.stNasFunFlag04)));
    g_aulNasFunFlg[4]     = *((VOS_UINT32 * )(&(stNvSwitchPara.stNasFunFlag05)));
    g_aulNasFunFlg[5]     = *((VOS_UINT32 * )(&(stNvSwitchPara.stNasFunFlag06)));
    g_aulNasFunFlg[6]     = *((VOS_UINT32 * )(&(stNvSwitchPara.stNasFunFlag07)));
    g_aulNasFunFlg[7]     = *((VOS_UINT32 * )(&(stNvSwitchPara.stNasFunFlag08)));

    /* NV读取时要按顺序读,不要出现穿插 */
    /************************stNasFunFlag01 Begin***************************/
    /* OM可维可测控制开关 */
    NAS_EMM_GetOmSwitchKeyInfoFlag()    = LNAS_NV_GET_NAS_FUN_FLAG(0, LNAS_NV_GET_KEY_INFO_FLAG_BIT);
    NAS_EMM_GetOmSwitchKeyInfoFlag()    = (0 != NAS_EMM_GetOmSwitchKeyInfoFlag()) ? NAS_EMM_YES : NAS_EMM_NO;
    NAS_EMM_GetOmSwitchKeyEventFlag()   = LNAS_NV_GET_NAS_FUN_FLAG(0, LNAS_NV_GET_KEY_EVENT_FLAG_BIT);
    NAS_EMM_GetOmSwitchKeyEventFlag()   = (0 != NAS_EMM_GetOmSwitchKeyEventFlag()) ? NAS_EMM_YES : NAS_EMM_NO;
    NAS_EMM_GetOmSwitchApiFlag()        = LNAS_NV_GET_NAS_FUN_FLAG(0, LNAS_NV_GET_API_FLAG_BIT);
    NAS_EMM_GetOmSwitchApiFlag()        = (0 != NAS_EMM_GetOmSwitchApiFlag()) ? NAS_EMM_YES : NAS_EMM_NO;
    NAS_EMM_GetOmSwitchSuccRatioFlag()  = LNAS_NV_GET_NAS_FUN_FLAG(0, LNAS_NV_GET_SUCC_RATIO_FLAG_BIT);
    NAS_EMM_GetOmSwitchSuccRatioFlag()  = (0 != NAS_EMM_GetOmSwitchSuccRatioFlag()) ? NAS_EMM_YES : NAS_EMM_NO;
    NAS_EMM_GetOmSwitchDelayFlag()      = LNAS_NV_GET_NAS_FUN_FLAG(0, LNAS_NV_GET_DELAY_FLAG_BIT);
    NAS_EMM_GetOmSwitchDelayFlag()      = (0 != NAS_EMM_GetOmSwitchDelayFlag()) ? NAS_EMM_YES : NAS_EMM_NO;

    g_ulEsrRej39OptimizeCtr             = LNAS_NV_GET_NAS_FUN_FLAG(0, LNAS_NV_GET_ESR_REJ39_OPTIMIZE_BIT);
    g_ulEsrRej39OptimizeCtr             = (0 != g_ulEsrRej39OptimizeCtr) ? NAS_EMM_YES : NAS_EMM_NO;

    g_ulNasAustraliaFlag             = LNAS_NV_GET_NAS_FUN_FLAG(0, LNAS_NV_GET_AUSTRALIA_OPTIMIZE_BIT);
    g_ulNasAustraliaFlag             = (0 != g_ulNasAustraliaFlag) ? NAS_EMM_YES : NAS_EMM_NO;

    /* Gradual Forb参数初始化 */
    NAS_LMM_GradualForbParaInit(stNvSwitchPara.stGradualForbPara);
    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_SndEsmClearAllClBearerNotify
 Description     : 向ESM发送清除所有CL承载指示
 Input           : None
 Output          : None
 Return          : VOS_VOID
 History         :
    1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_SndEsmClearAllClBearerNotify(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    EMM_ESM_CLEAR_CL_BEARER_NOTIFY_STRU           *pstEsmMsg;

    /* 申请DOPRA消息 */
    pstEsmMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(EMM_ESM_CLEAR_CL_BEARER_NOTIFY_STRU));

    if (NAS_LMM_NULL_PTR == pstEsmMsg)
    {
        return;
    }

    /* 清空 */
    NAS_LMM_MEM_SET_S(  pstEsmMsg,
                        sizeof(EMM_ESM_CLEAR_CL_BEARER_NOTIFY_STRU),
                        0,
                        sizeof(EMM_ESM_CLEAR_CL_BEARER_NOTIFY_STRU));

    /* 打包VOS消息头 */
    EMM_PUBU_COMP_ESM_MSG_HEADER((pstEsmMsg),     \
                                       NAS_EMM_GET_MSG_LENGTH_NO_HEADER(EMM_ESM_CLEAR_CL_BEARER_NOTIFY_STRU));

    /* 填充消息ID */
    pstEsmMsg->ulMsgId                 = ID_EMM_ESM_CLEAR_CL_BEARER_NOTIFY;

    /* 发送DOPRA消息 */
    NAS_LMM_SEND_MSG(pstEsmMsg);
#endif
    return;
}
/*****************************************************************************
 Function Name   : NAS_LMM_SetVoiceDomain
 Description     : 设置VOICE DOMAIN，并上报UE能力
 Input           : MMC_LMM_VOICE_DOMAIN_ENUM_UINT32     enVoiceDomain
 Output          : None
 Return          : VOS_VOID
 History         :
    1.    yanglei 00307272      2015-07-28  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SetVoiceDomain(MMC_LMM_VOICE_DOMAIN_ENUM_UINT32     enVoiceDomain )
{
    NAS_LMM_SetEmmInfoVoiceDomain(enVoiceDomain);
    NAS_EMM_SndOmLogUeImportantCapabilityInfo();

    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_GetImsVoiceMMEnableFlg
 Description     : 获取Ims Voice 移动性管理是否打开标志并上报
 Input           : None
 Output          : None
 Return          : VOS_UINT8
 History         :
    1.    yanglei 00307272      2015-07-28  Draft Enact
*****************************************************************************/
VOS_UINT8  NAS_LMM_GetImsVoiceMMEnableFlg( VOS_VOID )
{
    VOS_UINT8                           ucRslt;

    ucRslt = NAS_MML_GetImsVoiceMMEnableFlg();
    NAS_LMM_SndOmLogImsVoiceMMEnableFlgInfo();

    return ucRslt;
}

/*****************************************************************************
 Function Name   : NAS_LMM_SndOmLogImsVoiceMMEnableFlgInfo
 Description     : 上报Ims Voice 移动性管理是否打开标志
 Input           : None
 Output          : None
 Return          : VOS_VOID
 History         :
    1.    yanglei 00307272      2015-07-28  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmLogImsVoiceMMEnableFlgInfo( VOS_VOID )
{
    NAS_LMM_OM_LOG_IMS_VOICE_MM_ENABLE_FLAG_INFO_STRU       *pstMsg          = VOS_NULL_PTR;

    pstMsg = (NAS_LMM_OM_LOG_IMS_VOICE_MM_ENABLE_FLAG_INFO_STRU *)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_LOG_IMS_VOICE_MM_ENABLE_FLAG_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_LMM_MEM_SET_S(  pstMsg,
                        sizeof(NAS_LMM_OM_LOG_IMS_VOICE_MM_ENABLE_FLAG_INFO_STRU),
                        0,
                        sizeof(NAS_LMM_OM_LOG_IMS_VOICE_MM_ENABLE_FLAG_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LMM_OM_LOG_IMS_VOICE_MM_ENABLE_FLAG_INFO_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName       = LNAS_OM_LOG_IMS_VOICE_MM_ENABLE_FLAG_INFO_IND;
    pstMsg->ucImsVoiceMMEnable          = NAS_MML_GetImsVoiceMMEnableFlg();
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_LMM_MEM_FREE(pstMsg);
    return;
}
/*****************************************************************************
 Function Name   : NAS_LMM_GetLteNwImsVoiceSupportFlag
 Description     : 获取EPS网络对IMS Voice 支持信息并上报
 Input           : None
 Output          : None
 Return          : NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8
 History         :
    1.    yanglei 00307272      2015-07-28  Draft Enact
*****************************************************************************/
NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8  NAS_LMM_GetLteNwImsVoiceSupportFlag( VOS_VOID )
{
    NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8 ucRslt;

    ucRslt = NAS_MML_GetLteNwImsVoiceSupportFlg();
    NAS_LMM_SndOmLogLteNwImsVoiceSupportFlagInfo();

    return ucRslt;
}
/*****************************************************************************
 Function Name   : NAS_LMM_SndOmLogLteNwImsVoiceSupportFlagInfo
 Description     : 上报EPS网络对IMS Voice 支持信息
 Input           : None
 Output          : None
 Return          : VOS_VOID
 History         :
    1.    yanglei 00307272      2015-07-28  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmLogLteNwImsVoiceSupportFlagInfo( VOS_VOID )
{
    NAS_LMM_OM_LOG_NW_IMS_VOICE_CAP_STRU                    *pstMsg          = VOS_NULL_PTR;

    pstMsg = (NAS_LMM_OM_LOG_NW_IMS_VOICE_CAP_STRU *)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_LOG_NW_IMS_VOICE_CAP_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_LMM_MEM_SET_S(  pstMsg,
                        sizeof(NAS_LMM_OM_LOG_NW_IMS_VOICE_CAP_STRU),
                        0,
                        sizeof(NAS_LMM_OM_LOG_NW_IMS_VOICE_CAP_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LMM_OM_LOG_NW_IMS_VOICE_CAP_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName       = LNAS_OM_LOG_LTE_NW_IMS_VOICE_CAP_INFO_IND;
    pstMsg->enNwImsVoCap                = NAS_MML_GetLteNwImsVoiceSupportFlg();
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_LMM_MEM_FREE(pstMsg);
    return;
}
/*****************************************************************************
 Function Name   : NAS_LMM_GeGUNwImsVoiceSupportFlg
 Description     : 获取PS网络下Ims Voice 支持能力并上报
 Input           : None
 Output          : None
 Return          : NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8
 History         :
    1.    yanglei 00307272      2015-07-28  Draft Enact
*****************************************************************************/
NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8  NAS_LMM_GetGUNwImsVoiceSupportFlg( VOS_VOID )
{
    NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8 ucRslt;

    ucRslt = NAS_MML_GetGUNwImsVoiceSupportFlg();
    NAS_LMM_SndOmLogGUNwImsVoiceSupportFlagInfo();

    return ucRslt;
}
/*****************************************************************************
 Function Name   : NAS_LMM_SndOmLogGUNwImsVoiceSupportFlagInfo
 Description     : 上报PS网络对IMS Voice 支持信息
 Input           : None
 Output          : None
 Return          : VOS_VOID
 History         :
    1.    yanglei 00307272      2015-07-28  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmLogGUNwImsVoiceSupportFlagInfo( VOS_VOID )
{
    NAS_LMM_OM_LOG_NW_IMS_VOICE_CAP_STRU                    *pstMsg          = VOS_NULL_PTR;

    pstMsg = (NAS_LMM_OM_LOG_NW_IMS_VOICE_CAP_STRU *)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_LOG_NW_IMS_VOICE_CAP_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_LMM_MEM_SET_S(  pstMsg,
                        sizeof(NAS_LMM_OM_LOG_NW_IMS_VOICE_CAP_STRU),
                        0,
                        sizeof(NAS_LMM_OM_LOG_NW_IMS_VOICE_CAP_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LMM_OM_LOG_NW_IMS_VOICE_CAP_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName       = LNAS_OM_LOG_GU_NW_IMS_VOICE_CAP_INFO_IND;
    pstMsg->enNwImsVoCap                = NAS_MML_GetGUNwImsVoiceSupportFlg();
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_LMM_MEM_FREE(pstMsg);
    return;
}
/*****************************************************************************
 Function Name   : NAS_LMM_GetRoamingRejectNoRetryFlg
 Description     : 获取是否打开了reject #17的定制的标识并上报
 Input           : VOS_UINT8 ucCause
 Output          : None
 Return          : VOS_UINT8
 History         :
    1.    yanglei 00307272      2015-07-28  Draft Enact
*****************************************************************************/
VOS_UINT8  NAS_LMM_GetRoamingRejectNoRetryFlg( VOS_UINT8 ucCause )
{
    VOS_UINT8                           ucRslt;

    ucRslt = NAS_MML_IsRoamingRejectNoRetryFlgActived(ucCause);
    NAS_LMM_SndOmLogRoamingRejectNoRetryFlgInfo(ucCause);

    return ucRslt;
}
/*****************************************************************************
 Function Name   : NAS_LMM_SndOmLogRoamingRejectNoRetryFlgInfo
 Description     : 上报是否打开了reject #17的定制的标识信息
 Input           : VOS_UINT8 ucCause
 Output          : None
 Return          : VOS_VOID
 History         :
    1.    yanglei 00307272      2015-07-28  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmLogRoamingRejectNoRetryFlgInfo( VOS_UINT8 ucCause )
{
    NAS_LMM_OM_LOG_ROAMING_REJECT_NO_RETRY_FLG_STRU         *pstMsg          = VOS_NULL_PTR;

    pstMsg = (NAS_LMM_OM_LOG_ROAMING_REJECT_NO_RETRY_FLG_STRU *)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_LOG_ROAMING_REJECT_NO_RETRY_FLG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_LMM_MEM_SET_S(  pstMsg,
                        sizeof(NAS_LMM_OM_LOG_ROAMING_REJECT_NO_RETRY_FLG_STRU),
                        0,
                        sizeof(NAS_LMM_OM_LOG_ROAMING_REJECT_NO_RETRY_FLG_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LMM_OM_LOG_ROAMING_REJECT_NO_RETRY_FLG_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName       = LNAS_OM_LOG_ROAMING_REJECT_NO_RETRY_FLG_INFO_IND;
    pstMsg->ucRoamingRejectNoRetryFlg   = NAS_MML_IsRoamingRejectNoRetryFlgActived(ucCause);
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_LMM_MEM_FREE(pstMsg);
    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_GetGradualForbTaTimerPara
 Description     : 获取OPID, 用于唯一确定定时器超时时对应的TA
 Input           : None
 Output          : None
 Return          : Opid
 History         :
    1.leixiantiao 00258641      2015-07-31  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_LMM_GetGradualForbTaTimerPara(VOS_VOID)
{
    /* Timer Para从1开始, 用于初始启动Forb惩罚定时器当入参参入, 当定时器超时用于判断对应TA */
    g_ulGradualForbTaTimerPara++;

    return g_ulGradualForbTaTimerPara;
}
/*****************************************************************************
 Function Name   : NAS_LMM_IsGradualForbidenOptimizationOpened
 Description     : 判断渐进Forb优化是否打开
 Input           : None
 Output          : None
 Return          : NAS_EMM_YES:打开 NAS_EMM_NO:关闭
 History         :
    1.leixiantiao 00258641      2015-07-31  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_LMM_IsGradualForbidenOptimizationOpened(VOS_VOID)
{
    /* 判断NV是否打开 */
    if(PS_FALSE == g_ucLmmGradualForbFlag)
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_IsGradualForbidenOptimizationOpened: NV IS CLOSE");
        return NAS_EMM_NO;
    }

    /*如果是测试卡，返回未打开*/
    if(PS_SUCC == LPS_OM_IsTestMode())
    {
        NAS_LMM_PUBM_LOG_WARN( "NAS_LMM_IsGradualForbidenOptimizationOpened: Test Mode");
        return NAS_EMM_NO;
    }
    /* 优化打开 */
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_TaMatchTempTaList
 Description     : 判断TA是否在临时Forb列表中
 Input           : pstTa   : 需要判断的TA信息
 Output          : pulIndex: TA所在列表的索引,此索引只在匹配成功时生效
 Return          : 匹配结果
 History         :
    1.leixiantiao 00258641      2015-07-31  Draft Enact

*****************************************************************************/
NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_TaMatchGradualForbTaList(const NAS_MM_TA_STRU  *pstTa, VOS_UINT32 *pulIndex)
{
    VOS_UINT8                               i;
    NAS_LMM_MATCH_RESULT_ENUM_UINT32        ulMatchResult = NAS_LMM_MATCH_FAIL;
    NAS_MM_TA_STRU                          stTa;
    NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST  *pstTaList     = VOS_NULL_PTR;
    VOS_UINT32                              ulIndex       = 0;

    /* 入参检查 */
    if ((VOS_NULL_PTR == pstTa) || (VOS_NULL_PTR == pulIndex))
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_TaMatchGradualForbTaList VOS NULL PTR");
        return NAS_LMM_MATCH_PTR_NULL;
    }
    pstTaList = NAS_LMM_GetGradualForbTempForbTaListAddr();

    /* 判断列表是否为空 */
    if (0 == pstTaList->ulTaNum)
    {
        return NAS_LMM_MATCH_FAIL;
    }

    /* 匹配TA列表 */
    for (i = 0; i < NAS_LMM_GRADUAL_FORB_MAX_TEMP_TA_NUM; i++)
    {
        NAS_LMM_TaCpy(&stTa, &(pstTaList->astGradualForbTa[i].stTa));

        /* 与Ta List里的每个TA对比 */
        if ((NAS_EMM_GRADUAL_FORBIDDEN_TA_USED == pstTaList->astGradualForbTa[i].enUsedFlag)
             && (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatch(pstTa, &stTa)))
        {
            /* 记录当前索引 */
            ulMatchResult           = NAS_LMM_MATCH_SUCCESS;
            ulIndex                 = i;

            /* 如果有一项匹配成功，立即结束循环 */
            break;
        }
    }
    /* 赋值索引 */
    *pulIndex = ulIndex;
    return ulMatchResult;
}
/*****************************************************************************
 Function Name   : NAS_LMM_DelTaFromTempForbList
 Description     : 从临时列表中删除TA
 Input           : ulIndex: 列表索引
 Output          : None
 Return          : NONE
 History         :
    1.leixiantiao 00258641      2015-07-31  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LMM_DelTaFromTempForbList(VOS_UINT32 ulIndex)
{
    NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST   *pstTaList;
    pstTaList = NAS_LMM_GetGradualForbTempForbTaListAddr();

    /* 检查入参及列表中TA个数 */
    if ((ulIndex >= NAS_LMM_GRADUAL_FORB_MAX_TEMP_TA_NUM) || (0 == pstTaList->ulTaNum))
    {
        NAS_LMM_PUBM_LOG2_WARN(" NAS_LMM_DelTaFromTempForbList ulIdex =,TaNum =", ulIndex, pstTaList->ulTaNum);
        return;
    }
    /* 判断是否被使用, 若未被使用, 则返回 */
    if (NAS_EMM_GRADUAL_FORBIDDEN_TA_NOT_USED == pstTaList->astGradualForbTa[ulIndex].enUsedFlag)
    {
        NAS_LMM_PUBM_LOG1_WARN(" NAS_LMM_DelTaFromTempForbList TA NOT USED ulIdex =", ulIndex);
        return;
    }
    /* 先把定时器停了 */
    NAS_LMM_StopGradualForbiddenTimer(ulIndex, TI_NAS_EMM_PTL_GRADUAL_FORB_TIMER);
    NAS_LMM_StopGradualForbiddenTimer(ulIndex, TI_NAS_EMM_PTL_GRADUAL_FORB_AGING_TIMER);

    /* 清除当前TA信息 */
    NAS_LMM_MEM_SET_S(  &pstTaList->astGradualForbTa[ulIndex],
                        sizeof(NAS_LMM_GRADUAL_FORB_TA),
                        0,
                        sizeof(NAS_LMM_GRADUAL_FORB_TA));

    pstTaList->astGradualForbTa[ulIndex].enUsedFlag = NAS_EMM_GRADUAL_FORBIDDEN_TA_NOT_USED;

    /* 维护临时列表TA计数 */
    pstTaList->ulTaNum--;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddNewTaWithTempTaListNotFull
 Description     : 临时列表没有满时新加TA
 Input           : pstTa: TA信息
 Output          : None
 Return          : NONE
 History         :
    1.leixiantiao 00258641      2015-07-31  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LMM_AddNewTaWithTempTaListNotFull(NAS_MM_TA_STRU   *pstTa)
{
    NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST      *pstTaList    = VOS_NULL_PTR;
    VOS_UINT32                                  ulTimerPara  = NAS_LMM_GetGradualForbTaTimerPara();
    VOS_UINT32                                  ulIndex      = 0;
    VOS_UINT32                                  i;

    /* 获取临时列表地址 */
    pstTaList          = NAS_LMM_GetGradualForbTempForbTaListAddr();

    /* 查找临时列表未使用的位置 */
    for (i = 0; i < NAS_LMM_GRADUAL_FORB_MAX_TEMP_TA_NUM; i++)
    {
        if (NAS_EMM_GRADUAL_FORBIDDEN_TA_NOT_USED == pstTaList->astGradualForbTa[i].enUsedFlag)
        {
            /* 找到第一个跳出循环 */
            break;
        }
    }

    /* 当i小于列表最大个数时, 把新TA放入该位置 */
    if (i < NAS_LMM_GRADUAL_FORB_MAX_TEMP_TA_NUM)
    {
        ulIndex = i;
    }
    else
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_AddNewTaWithTempTaListNotFull TA LIST is Full  ");
        return;
    }

    /* 初始化被拒次数 */
    pstTaList->astGradualForbTa[ulIndex].uc15RejTimes = NAS_LMM_GRADUAL_FORB_REJ_FIRST;

    /* 保存Timer Para, 用于定时器判断找到对应TA */
    pstTaList->astGradualForbTa[ulIndex].ulTimerPara  = ulTimerPara;

    /* 记录该位置已经被使用 */
    pstTaList->astGradualForbTa[ulIndex].enUsedFlag   = NAS_EMM_GRADUAL_FORBIDDEN_TA_USED;

    /* 保存TA信息 */
    pstTaList->astGradualForbTa[ulIndex].stTa.stPlmnId.aucPlmnId[0] = pstTa->stPlmnId.aucPlmnId[0];
    pstTaList->astGradualForbTa[ulIndex].stTa.stPlmnId.aucPlmnId[1] = pstTa->stPlmnId.aucPlmnId[1];
    pstTaList->astGradualForbTa[ulIndex].stTa.stPlmnId.aucPlmnId[2] = pstTa->stPlmnId.aucPlmnId[2];
    pstTaList->astGradualForbTa[ulIndex].stTa.stTac.ucTac           = pstTa->stTac.ucTac;
    pstTaList->astGradualForbTa[ulIndex].stTa.stTac.ucTacCnt        = pstTa->stTac.ucTacCnt;

    /* 启动惩罚定时器和老化定时器 */
    NAS_LMM_StartGradualForbiddenTimer(ulIndex, TI_NAS_EMM_PTL_GRADUAL_FORB_TIMER, ulTimerPara);
    NAS_LMM_StartGradualForbiddenTimer(ulIndex, TI_NAS_EMM_PTL_GRADUAL_FORB_AGING_TIMER, ulTimerPara);

    /* TA个数加 1 */
    pstTaList->ulTaNum++;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddNewTaInGradualForbTempTaList
 Description     : 把一个新的TA加入到临时列表中
 Input           : pstTa :TA信息
 Output          : None
 Return          :
 History         :
    1.leixiantiao 00258641      2015-07-31  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LMM_AddNewTaInGradualForbTempTaList(NAS_MM_TA_STRU   *pstTa)
{
    NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST      *pstTaList = VOS_NULL_PTR;
    VOS_UINT32                                  ulLoop;
    VOS_UINT32                                  ulDelIndex;

    pstTaList          = NAS_LMM_GetGradualForbTempForbTaListAddr();

    /* 当临时列表没有满时直接加入列表中 */
    if(NAS_LMM_GRADUAL_FORB_MAX_TEMP_TA_NUM > pstTaList->ulTaNum)
    {
        NAS_LMM_AddNewTaWithTempTaListNotFull(pstTa);
    }
    else
    {
        for(ulLoop = 0; ulLoop < NAS_LMM_GRADUAL_FORB_MAX_TEMP_TA_NUM; ulLoop++)
        {
            /* 从0开始遍历, 找到第一个定时器已经停止的TA, 跳出循环 */
            if(NAS_LMM_TIMER_STOPED == NAS_LMM_IsGradualForbiddenTimerRunning(ulLoop, TI_NAS_EMM_PTL_GRADUAL_FORB_TIMER))
            {
                break;
            }
        }
        if (ulLoop < NAS_LMM_GRADUAL_FORB_MAX_TEMP_TA_NUM)
        {
            /* 找到定时器未在运行中最早加入列表的TA, 把该TA从列表中剔除 */
            ulDelIndex = ulLoop;
        }
        else
        {
            /* 若定时器都在运行, 则把第一个加入列表中的TA剔除 */
            ulDelIndex = 0;
        }
        /* 剔除选中的TA */
        NAS_LMM_DelTaFromTempForbList(ulDelIndex);

        /* 由于前面把一个TA剔除了, 所以此处只需把新TA信息加入临时列表中 */
        NAS_LMM_AddNewTaWithTempTaListNotFull(pstTa);
    }
}
/*****************************************************************************
 Function Name   : NAS_LMM_IsGradualForbidenOptimizationOpened
 Description     : 判断渐进Forb优化是否打开
 Input           : None
 Output          : None
 Return          : NAS_EMM_YES:打开 NAS_EMM_NO:关闭
 History         :
    1.leixiantiao 00258641      2015-07-31  Draft Enact

*****************************************************************************/
NAS_EMM_GRADUAL_FORBIDDEN_RESULT_ENUM_UINT32 NAS_LMM_AddTaInGradualForbTempTaList(NAS_MM_TA_STRU   *pstTa)
{
    NAS_MMC_TA_LIST_STRU                         *pstForbTaForRoming;
    VOS_UINT32                                   ulIndex = 0;
    NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST       *pstTaList = VOS_NULL_PTR;
    VOS_UINT32                                   ulTimerPara;
    NAS_EMM_GRADUAL_FORBIDDEN_RESULT_ENUM_UINT32 enResult = NAS_EMM_GRADUAL_FORB_TA_IN_TEMP_LIST;

    /* 判断特性是否打开 */
    if (NAS_EMM_NO == NAS_LMM_IsGradualForbidenOptimizationOpened())
    {
        return NAS_EMM_GRADUAL_FORB_TA_NEED_ADD_ROAM_LIST;
    }
    pstTaList          = NAS_LMM_GetGradualForbTempForbTaListAddr();
    pstForbTaForRoming = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_FORB_TA_FOR_ROAMING);

    /* 判断TA是否在Roming列表中 */
    if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatchTaList(pstTa, pstForbTaForRoming))
    {
        return NAS_EMM_GRADUAL_FORB_TA_NEED_ADD_ROAM_LIST;
    }

    /* 判断TA是否在临时列表中 */
    if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatchGradualForbTaList(pstTa, &ulIndex))
    {
        /* 切换到Forb Ta发起TAU被拒时惩罚定时器可能会启动着, 所以此处先停定时器 */
        NAS_LMM_StopGradualForbiddenTimer(ulIndex, TI_NAS_EMM_PTL_GRADUAL_FORB_TIMER);

        /* 再次被拒时, 先停老化定时器, 若被拒次数未达到上限时, 再重新启动 */
        NAS_LMM_StopGradualForbiddenTimer(ulIndex, TI_NAS_EMM_PTL_GRADUAL_FORB_AGING_TIMER);

        /* 被#15拒两次, 则从临时列表中删除, 加到原有列表中 */
        if (pstTaList->astGradualForbTa[ulIndex].uc15RejTimes >= NAS_LMM_GRADUAL_FORB_REJ_SECOND)
        {
            NAS_LMM_DelTaFromTempForbList(ulIndex);
            enResult = NAS_EMM_GRADUAL_FORB_TA_NEED_ADD_ROAM_LIST;
        }
        else
        {
            /* 先更新#15拒绝次数, 后启动定时器, 启动定时器时会根据拒绝次数调整定时器长度 */
            pstTaList->astGradualForbTa[ulIndex].uc15RejTimes++;
            ulTimerPara = pstTaList->astGradualForbTa[ulIndex].ulTimerPara;
            NAS_LMM_StartGradualForbiddenTimer(ulIndex, TI_NAS_EMM_PTL_GRADUAL_FORB_TIMER, ulTimerPara);
            NAS_LMM_StartGradualForbiddenTimer(ulIndex, TI_NAS_EMM_PTL_GRADUAL_FORB_AGING_TIMER, ulTimerPara);
            enResult = NAS_EMM_GRADUAL_FORB_TA_IN_TEMP_LIST;
        }
    }
    else
    {
        /* 当TA不在临时列表中, 加入临时列表 */
        NAS_LMM_AddNewTaInGradualForbTempTaList(pstTa);
        enResult = NAS_EMM_GRADUAL_FORB_ADD_TA_SUCC;
    }

    /* 勾出可维可测 */
    if(NAS_EMM_GRADUAL_FORB_TA_NEED_ADD_ROAM_LIST == enResult)
    {
        NAS_EMM_SndOmGradualForbTaInfo(pstTa, NAS_LMM_GRADUAL_FORB_TA_OPERATION_TYPE_DEL);
    }
    else
    {
        NAS_EMM_SndOmGradualForbTaInfo(pstTa, NAS_LMM_GRADUAL_FORB_TA_OPERATION_TYPE_ADD);
    }
    return enResult;
}
/*****************************************************************************
 Function Name   : NAS_LMM_FillTempTaInRrcNasForbTaList
 Description     : 把临时列表填充到给LRRC的Forb列表中
 Input           : pstRrcNasForbTaList: 给LRRC的Forb列表
 Output          : None
 Return          : None
 History         :
    1.leixiantiao 00258641      2015-07-31  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LMM_FillTempTaInRrcNasForbTaList(LRRC_LNAS_FORB_TA_LIST_STRU *pstRrcNasForbTaList)
{
    VOS_UINT32                                  ulIndex;
    NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST      *pstTaList = VOS_NULL_PTR;
    VOS_UINT32                                  ulLoop;

    pstTaList          = NAS_LMM_GetGradualForbTempForbTaListAddr();

    /* 判断特性是否打开 */
    if (NAS_EMM_NO == NAS_LMM_IsGradualForbidenOptimizationOpened())
    {
        return;
    }

    /* 判断给RRC的ForbTaList是否满了, 若满了, 直接返回 */
    if (pstRrcNasForbTaList->ulTaNum >= LRRC_LNAS_MAX_FORBTA_NUM)
    {
        return;
    }

    /* 临时列表为空时, 直接返回 */
    if (0 == pstTaList->ulTaNum)
    {
        return;
    }

    /* 给RRC的ForbTaList没满, 临时列表不为空, 则继续把临时列表填充进去 */
    /* 获取RRC的ForbTaList下一个填充位置 */
    ulIndex     = pstRrcNasForbTaList->ulTaNum;

    /* 遍历临时列表, 填充RRC列表 */
    for (ulLoop = 0; ulLoop < NAS_LMM_GRADUAL_FORB_MAX_TEMP_TA_NUM; ulLoop++)
    {
        /* 判断给RRC的列表是否填满了 */
        if (LRRC_LNAS_MAX_FORBTA_NUM <= ulIndex)
        {
            return;
        }
        /* 找到被使用的TA */
        if (NAS_EMM_GRADUAL_FORBIDDEN_TA_USED == pstTaList->astGradualForbTa[ulLoop].enUsedFlag)
        {
            /* 惩罚定时器启动的最新加入临时列表中的TA */
            if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsGradualForbiddenTimerRunning(ulLoop, TI_NAS_EMM_PTL_GRADUAL_FORB_TIMER))
            {
                /* 由于临时列表和RRC列表结构体不一样, 所以此处不用拷贝函数 */
                pstRrcNasForbTaList->astForbTa[ulIndex].stPlmnId.aucPlmnId[0]
                    = pstTaList->astGradualForbTa[ulLoop].stTa.stPlmnId.aucPlmnId[0];
                pstRrcNasForbTaList->astForbTa[ulIndex].stPlmnId.aucPlmnId[1]
                    = pstTaList->astGradualForbTa[ulLoop].stTa.stPlmnId.aucPlmnId[1];
                pstRrcNasForbTaList->astForbTa[ulIndex].stPlmnId.aucPlmnId[2]
                    = pstTaList->astGradualForbTa[ulLoop].stTa.stPlmnId.aucPlmnId[2];
                pstRrcNasForbTaList->astForbTa[ulIndex].stTac.ucTac
                    = pstTaList->astGradualForbTa[ulLoop].stTa.stTac.ucTac;
                pstRrcNasForbTaList->astForbTa[ulIndex].stTac.ucTacCont
                    = pstTaList->astGradualForbTa[ulLoop].stTa.stTac.ucTacCnt;

                /* 下一个填充索引加1 */
                ulIndex++;

                /* Ta个数加1 */
                pstRrcNasForbTaList->ulTaNum++;
            }
        }
    }
}
/*****************************************************************************
 Function Name   : NAS_LMM_FillUserSpecRrcNasForbTaListWithTempTa
 Description     : 用户指定搜,把临时列表带给LRRC
 Input           : pstPlmnId    : 用户指定搜PLMN
                   pstRrcTaList : 带给LRRC的Forb列表
 Output          : None
 Return          : None
 History         :
    1.leixiantiao 00258641      2015-07-31  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LMM_FillUserSpecRrcNasForbTaListWithTempTa
(
    const NAS_MM_PLMN_ID_STRU  *pstPlmnId,
    NAS_MM_TA_LIST_STRU        *pstRrcTaList
)
{
    NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST      *pstTaList = VOS_NULL_PTR;
    VOS_UINT32                                  ulLoop;

    pstTaList          = NAS_LMM_GetGradualForbTempForbTaListAddr();

    /* 判断特性是否打开 */
    if (NAS_EMM_NO == NAS_LMM_IsGradualForbidenOptimizationOpened())
    {
        return;
    }

    /* 判断给RRC的ForbTaList是否满了, 若满了, 直接返回 */
    if (pstRrcTaList->ulTaNum >= NAS_MM_MAX_TA_NUM)
    {
        return;
    }

    /* 临时列表为空时, 直接返回 */
    if (0 == pstTaList->ulTaNum)
    {
        return;
    }

    /* 遍历临时列表, 填充RRC列表 */
    for (ulLoop = 0; ulLoop < NAS_LMM_GRADUAL_FORB_MAX_TEMP_TA_NUM; ulLoop++)
    {
        /* 找到被使用的TA */
        if (NAS_EMM_GRADUAL_FORBIDDEN_TA_USED == pstTaList->astGradualForbTa[ulLoop].enUsedFlag)
        {
            /* 把非指定PLMN下的Forb TA带给LRRC */
            if (NAS_LMM_MATCH_SUCCESS != NAS_LMM_PlmnMatch(pstPlmnId,&pstTaList->astGradualForbTa[ulLoop].stTa.stPlmnId))
            {
                /* 惩罚定时器启动的最新加入临时列表中的TA */
                if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsGradualForbiddenTimerRunning(ulLoop, TI_NAS_EMM_PTL_GRADUAL_FORB_TIMER))
                {
                    NAS_LMM_AddTaInTaList(   &pstTaList->astGradualForbTa[ulLoop].stTa,
                                             pstRrcTaList,
                                             NAS_LMM_MAX_FORBTA_NUM);
                }
            }
        }
    }
}

/*****************************************************************************
 Function Name   : NAS_LMM_UpdateGradualForbTempTaList
 Description     : TAU等流程成功后, 更新临时列表
 Input           : pstRrcNasForbTaList: 给LRRC的Forb列表
 Output          : None
 Return          : None
 History         :
    1.leixiantiao 00258641      2015-07-31  Draft Enact

*****************************************************************************/
NAS_EMM_GRADUAL_FORBIDDEN_RESULT_ENUM_UINT32 NAS_LMM_UpdateGradualForbTempTaList(VOS_VOID)
{
    VOS_UINT32                                   ulIndex        = 0;
    NAS_MM_TA_LIST_STRU                          *pstCurTaiList = VOS_NULL_PTR;
    NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST       *pstTempTaList = VOS_NULL_PTR;
    VOS_UINT32                                   i              = 0;
    NAS_EMM_GRADUAL_FORBIDDEN_RESULT_ENUM_UINT32 enUpdateResult = NAS_EMM_GRADUAL_FORB_TA_LIST_NOT_CHANGED;

    /* 判断特性是否打开 */
    if (NAS_EMM_NO == NAS_LMM_IsGradualForbidenOptimizationOpened())
    {
        return NAS_EMM_GRADUAL_FORB_TA_LIST_NOT_CHANGED;
    }

    /*获取当前的TAI List,ForTA for Roaming,ForbTA for RPOS*/
    pstCurTaiList = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_TA_LIST);
    pstTempTaList = NAS_LMM_GetGradualForbTempForbTaListAddr();
    if(0 == pstTempTaList->ulTaNum)
    {
        return NAS_EMM_GRADUAL_FORB_TA_LIST_NOT_CHANGED;
    }

    /* 判断TA LIST是否在临时列表中 */
    for(i = 0; i < pstCurTaiList->ulTaNum; i++)
    {
        if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatchGradualForbTaList(&(pstCurTaiList->astTa[i]), &ulIndex))
        {
            /* TA在临时列表中, 剔除该TA */
            enUpdateResult = NAS_EMM_GRADUAL_FORB_TA_LIST_CHANGED;

            /* 从列表中删除匹配上的TA */
            NAS_LMM_DelTaFromTempForbList(ulIndex);

            /* 勾出可维可测 */
            NAS_EMM_SndOmGradualForbTaInfo(&(pstCurTaiList->astTa[i]), NAS_LMM_GRADUAL_FORB_TA_OPERATION_TYPE_DEL);
        }
    }
    return enUpdateResult;
}
/*****************************************************************************
 Function Name   : NAS_LMM_CheckNvGradualForbiddenTimerLenVaild
 Description     : 判断Gradual Forb优化NV设置的定时器长度是否有消息
 Input           : ulTimerLen: 定时器时长
 Output          : None
 Return          : VOS_UINT32: 0: 无效; 1: 有效
 History         :
    1.leixiantiao 00258641      2015-07-31  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_LMM_CheckNvGradualForbiddenTimerLenVaild(VOS_UINT32 ulTimerLen)
{
    /* 定时器长度为0时无效 */
    if(0 == ulTimerLen)
    {
        return NAS_EMM_NO;
    }
    /* 定时器长度不小于原有Forb定时器长度时无效 */
    if(NAS_LMM_TIMER_EMM_DEL_FORB_TA_PRIOD_LEN <= ulTimerLen)
    {
        return NAS_EMM_NO;
    }

    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_ReadNvGradualForbPara
 Description     : Gradual Forb优化NV读取函数
 Input           : None
 Output          : None
 Return          : None
 History         :
    1.leixiantiao 00258641      2015-07-31  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LMM_GradualForbParaInit(LNAS_LMM_NV_GRADUAL_FORBIDDEN_PARA_STRU stNvGradualForbPara)
{
    VOS_UINT32                                ulTimerLen;

    /* 读NV前先赋默认值 */
    g_ucLmmGradualForbFlag               = PS_FALSE;
    g_ulGradualForbTimerFirstLen         = 300*1000;
    g_ulGradualForbTimerSecondLen        = 1200*1000;
    g_ulGradualForbAgingTimerLen         = 7200*1000;

    /* 当控制开关非0时, 特性打开 */
    if (0 != stNvGradualForbPara.ucGradualForbFlag)
    {
        g_ucLmmGradualForbFlag       = PS_TRUE;
    }

    /* 判断第一次惩罚定时器长度配置是否有效 */
    ulTimerLen = stNvGradualForbPara.usGradualForbTimerFirstLen * 60 * 1000;
    if (NAS_EMM_YES == NAS_LMM_CheckNvGradualForbiddenTimerLenVaild(ulTimerLen))
    {
        g_ulGradualForbTimerFirstLen = ulTimerLen;
    }
    /* 判断第二次惩罚定时器长度配置是否有效 */
    ulTimerLen = stNvGradualForbPara.usGradualForbTimerSecondLen * 60 * 1000;
    if (NAS_EMM_YES == NAS_LMM_CheckNvGradualForbiddenTimerLenVaild(ulTimerLen))
    {
        g_ulGradualForbTimerSecondLen = ulTimerLen;
    }
    /* 判断老化定时器长度配置是否有效 */
    ulTimerLen = stNvGradualForbPara.ulGradualForbAgingTimerLen * 60 *1000;
    if (NAS_EMM_YES == NAS_LMM_CheckNvGradualForbiddenTimerLenVaild(ulTimerLen))
    {
        g_ulGradualForbAgingTimerLen = ulTimerLen;
    }

    /* 把配置信息购到HIDS上 */
    NAS_EMM_SndOmGradualForbParaLog(stNvGradualForbPara);
}

/*****************************************************************************
 Function Name   : NAS_LMM_GradualForbTaListInit
 Description     : Gradual Forb优化本地维护临时列表初始化, 开机时调用
 Input           : None
 Output          : None
 Return          : None
 History         :
    1.leixiantiao 00258641      2015-07-31  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LMM_GradualForbTaListInit(VOS_VOID)
{
    NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST       *pstTempTaList = VOS_NULL_PTR;
    VOS_UINT32                                   ulLoop;

    pstTempTaList = NAS_LMM_GetGradualForbTempForbTaListAddr();

    /* 初始化Gradual Forb临时列表本地维护的信息 */
    NAS_LMM_MEM_SET_S(  pstTempTaList,
                        sizeof(NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST),
                        0,
                        sizeof(NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST));

    for (ulLoop = 0; ulLoop < NAS_LMM_GRADUAL_FORB_MAX_TEMP_TA_NUM; ulLoop++)
    {
        pstTempTaList->astGradualForbTa[ulLoop].enUsedFlag = NAS_EMM_GRADUAL_FORBIDDEN_TA_NOT_USED;
    }

    /* 把TimerPara全局变量清除 */
    g_ulGradualForbTaTimerPara= 0;
}

/*****************************************************************************
 Function Name   : NAS_LMM_StopAllGradualForbiddenTimer
 Description     : 停止所有Gradual Forb优化定时器, 关机时调用
 Input           : None
 Output          : None
 Return          : None
 History         :
    1.leixiantiao 00258641      2015-07-31  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LMM_StopAllGradualForbiddenTimer(VOS_VOID)
{
    NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST       *pstTempTaList = VOS_NULL_PTR;
    VOS_UINT32                                    ulIndex;

    pstTempTaList = NAS_LMM_GetGradualForbTempForbTaListAddr();

    for (ulIndex = 0; ulIndex < NAS_LMM_GRADUAL_FORB_MAX_TEMP_TA_NUM; ulIndex++)
    {
        if (NAS_EMM_GRADUAL_FORBIDDEN_TA_USED == pstTempTaList->astGradualForbTa[ulIndex].enUsedFlag)
        {
            /* 判断惩罚定时器是否在运行, 若在运行则停止惩罚定时器 */
            if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsGradualForbiddenTimerRunning(ulIndex, TI_NAS_EMM_PTL_GRADUAL_FORB_TIMER))
            {
                NAS_LMM_StopGradualForbiddenTimer(ulIndex, TI_NAS_EMM_PTL_GRADUAL_FORB_TIMER);
            }
            /* 判断老化定时器是否在运行, 若在运行则停止老化定时器 */
            if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsGradualForbiddenTimerRunning(ulIndex, TI_NAS_EMM_PTL_GRADUAL_FORB_AGING_TIMER))
            {
                NAS_LMM_StopGradualForbiddenTimer(ulIndex, TI_NAS_EMM_PTL_GRADUAL_FORB_AGING_TIMER);
            }
        }
    }
    return;
}
/*****************************************************************************
 Function Name   : NAS_LMM_StopAllGradualForbiddenTimer
 Description     : 清空所有Gradual Forb TA列表本地维护信息, 关机时调用
 Input           : None
 Output          : None
 Return          : None
 History         :
    1.leixiantiao 00258641      2015-07-31  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LMM_ClearAllGradualForbTaList(VOS_VOID)
{
    NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST       *pstTempTaList = VOS_NULL_PTR;

    pstTempTaList = NAS_LMM_GetGradualForbTempForbTaListAddr();

    /* 停止所有Gradual Forb定时器 */
    NAS_LMM_StopAllGradualForbiddenTimer();

    /* 停止定时器后, 清空Gradual Forb临时列表本地维护的信息 */
    NAS_LMM_MEM_SET_S(  pstTempTaList,
                        sizeof(NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST),
                        0,
                        sizeof(NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST));

    /* 把TimerPara全局变量清除 */
    g_ulGradualForbTaTimerPara= 0;
}
/*****************************************************************************
 Function Name   : NAS_LMM_OpidMatchGradualForbTaList
 Description     : 根据Opid查找Gradual Forb列表中对应的TA, 用于定时器超时时区分
                   对应TA
 Input           : ulOpid  :opid信息
 Output          : pulIndex:对应TA索引, 该值只在函数返回SUCC生效
 Return          : 查找结果, 1: 为成功; 其他都为失败
 History         :
    1.leixiantiao 00258641      2015-07-31  Draft Enact

*****************************************************************************/
NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_TimerParaMatchGradualForbTaList(VOS_UINT32 ulTimerPara, VOS_UINT32 *pulIndex)
{
    VOS_UINT8                               i;
    NAS_LMM_MATCH_RESULT_ENUM_UINT32        ulMatchResult = NAS_LMM_MATCH_FAIL;
    NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST  *pstTaList     = VOS_NULL_PTR;
    VOS_UINT32                              ulIndex       = 0;
    if(VOS_NULL_PTR == pulIndex)
    {
        return NAS_LMM_MATCH_PTR_NULL;
    }

    pstTaList = NAS_LMM_GetGradualForbTempForbTaListAddr();

    /* TA个数检查 */
    if (0 == pstTaList->ulTaNum)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_TaMatchTempTaList is empty ");
        return NAS_LMM_MATCH_FAIL;
    }

    for(i = 0; i < NAS_LMM_GRADUAL_FORB_MAX_TEMP_TA_NUM; i++)
    {
        if ((NAS_EMM_GRADUAL_FORBIDDEN_TA_USED == pstTaList->astGradualForbTa[i].enUsedFlag)
            && (ulTimerPara == pstTaList->astGradualForbTa[i].ulTimerPara))
        {
            ulIndex       = i;
            ulMatchResult = NAS_LMM_MATCH_SUCCESS;
            break;
        }
    }
    *pulIndex = ulIndex;
    return ulMatchResult;
}
/*****************************************************************************
 Function Name   : NAS_LMM_GetGradualForbTaWithIndex
 Description     : 获取索引对应TA信息
 Input           : ulIndex: 索引
 Output          : pstTa  : 对应TA信息
 Return          :
 History         :
    1.leixiantiao 00258641      2015-07-31  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LMM_GetGradualForbTaWithIndex(VOS_UINT32 ulIndex, NAS_MM_TA_STRU *pstTa)
{
    NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST  *pstTaList     = VOS_NULL_PTR;

    /* 获取临时列表 */
    pstTaList = NAS_LMM_GetGradualForbTempForbTaListAddr();

    /* 拷贝对应TA信息 */
    NAS_LMM_MEM_CPY_S(pstTa, sizeof(NAS_MM_TA_STRU), &pstTaList->astGradualForbTa[ulIndex].stTa, sizeof(NAS_MM_TA_STRU));
    return;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTaInForbListWithTauRejCauseVal15
 Description     : TAU REJ 15时, Forb列表维护
 Input           : ulIsEutranNotAllowed :网侧是否携带扩展原因值指示4G为开户
 Output          : None
 Return          : 是否要走4G未开户流程, 加入临时列表的情况下不走4G未开户流程
 History         :
    1.leixiantiao 00258641      2015-07-31  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LMM_AddTaInForbListWithTauRejCauseVal15(VOS_UINT32 ulIsWithExtCause,
                                                                        VOS_UINT32 *pulIsNeedExecLteNotAllow)
{
    NAS_MM_TA_STRU                              stCurrentTa;

    *pulIsNeedExecLteNotAllow  = NAS_EMM_YES;

    NAS_LMM_MEM_SET_S(&stCurrentTa, sizeof(NAS_MM_TA_STRU), 0, sizeof(NAS_MM_TA_STRU));

    /* 获取当前驻留TA */
    NAS_EMM_GetCurrentTa(&stCurrentTa);

    /* 用户指定搜, 加入Rej #15列表中 */
    if (NAS_EMMC_USER_SPEC_PLMN_YES == NAS_EMMC_GetUserSpecPlmnFlag())
    {
        NAS_EMM_AddForbTa(&stCurrentTa,NAS_LMM_GetEmmInfoNetInfoForbTaForRej15Addr());

        *pulIsNeedExecLteNotAllow = NAS_EMM_YES;
        return;
    }

    /* R11需要判断是否是共享网络 */
    if (NAS_RELEASE_R11)
    {
        /* 需要加入Forb 列表 */
        if (NAS_EMM_YES == NAS_EMM_IsNeedAddForbTa())
        {
            /* 携带扩展原因值指示4G未开户, 加入Roaming列表 */
            if (NAS_EMM_YES == ulIsWithExtCause)
            {
                /*store the current TAI in the list of
                        "forbidden tracking areas for roaming"*/
                NAS_EMM_AddForbTa(&stCurrentTa,NAS_LMM_GetEmmInfoNetInfoForbTaForRoamAddr());
                *pulIsNeedExecLteNotAllow = NAS_EMM_YES;
            }
            else if (NAS_EMM_GRADUAL_FORB_TA_NEED_ADD_ROAM_LIST == NAS_LMM_AddTaInGradualForbTempTaList(&stCurrentTa))
            {
                /* 没有加入临时列表 */
                /*store the current TAI in the list of
                        "forbidden tracking areas for roaming"*/
                NAS_EMM_AddForbTa(&stCurrentTa,NAS_LMM_GetEmmInfoNetInfoForbTaForRoamAddr());
                *pulIsNeedExecLteNotAllow = NAS_EMM_YES;
            }
            else
            {
                /* 若走到该分支, 说明TA加入临时列表中, 则不需要走4G未开户流程 */
                *pulIsNeedExecLteNotAllow = NAS_EMM_NO;
            }
            NAS_EMMC_SendRrcCellSelectionReq(LRRC_LNAS_FORBTA_CHANGE);
        }
        else
        {
            *pulIsNeedExecLteNotAllow = NAS_EMM_YES;
        }
    }
    else
    {
        /* 携带扩展原因值指示4G未开户, 加入Roaming列表 */
        if (NAS_EMM_YES == ulIsWithExtCause)
        {
            /*store the current TAI in the list of
                    "forbidden tracking areas for roaming"*/
            NAS_EMM_AddForbTa(&stCurrentTa,NAS_LMM_GetEmmInfoNetInfoForbTaForRoamAddr());
            *pulIsNeedExecLteNotAllow = NAS_EMM_YES;
        }
        else if (NAS_EMM_GRADUAL_FORB_TA_NEED_ADD_ROAM_LIST == NAS_LMM_AddTaInGradualForbTempTaList(&stCurrentTa))
        {
            /* 没有加入临时列表 */
            /*store the current TAI in the list of
                    "forbidden tracking areas for roaming"*/
            NAS_EMM_AddForbTa(&stCurrentTa,NAS_LMM_GetEmmInfoNetInfoForbTaForRoamAddr());
            *pulIsNeedExecLteNotAllow = NAS_EMM_YES;
        }
        else
        {
            /* 若走到该分支, 说明TA加入临时列表中, 则不需要走4G未开户流程 */
            *pulIsNeedExecLteNotAllow = NAS_EMM_NO;
        }
        NAS_EMMC_SendRrcCellSelectionReq(LRRC_LNAS_FORBTA_CHANGE);
    }
    return;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTaInForbListWithAttRejCauseVal15
 Description     : Attach REJ 15时, Forb列表维护
 Input           : ulIsEutranNotAllowed :网侧是否携带扩展原因值指示4G为开户
 Output          : None
 Return          : 是否要走4G未开户流程, 加入临时列表的情况下不走4G未开户流程
 History         :
    1.leixiantiao 00258641      2015-07-31  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LMM_AddTaInForbListWithAttRejCauseVal15(VOS_UINT32 ulIsWithExtCause,
                                                                         VOS_UINT32 *pulIsNeedExecLteNotAllow)
{
    NAS_MM_TA_STRU                              stCurrentTa;
    *pulIsNeedExecLteNotAllow   = NAS_EMM_NO;

    NAS_LMM_MEM_SET_S(  &stCurrentTa,
                        sizeof(NAS_MM_TA_STRU),
                        0,
                        sizeof(NAS_MM_TA_STRU));

    /* 获取当前驻留TA */
    NAS_EMM_GetCurrentTa(&stCurrentTa);

    /* 用户指定搜, 加入Rej #15列表中 */
    if (NAS_EMMC_USER_SPEC_PLMN_YES == NAS_EMMC_GetUserSpecPlmnFlag())
    {
        NAS_EMM_AddForbTa(&stCurrentTa,NAS_LMM_GetEmmInfoNetInfoForbTaForRej15Addr());
        *pulIsNeedExecLteNotAllow   = NAS_EMM_YES;
        return;
    }

    /* 网侧携带扩展原因值, 指示4G未开户, 直接加到Roam 列表中 */
    if (NAS_EMM_YES == ulIsWithExtCause)
    {
        /*store the current TAI in the list of "forbidden tracking areas for roaming"*/
        NAS_EMM_AddForbTa(&stCurrentTa,NAS_LMM_GetEmmInfoNetInfoForbTaForRoamAddr());
        NAS_EMMC_SendRrcCellSelectionReq(LRRC_LNAS_FORBTA_CHANGE);
        *pulIsNeedExecLteNotAllow   = NAS_EMM_YES;
        return;
    }

    /* 当网侧没有携带扩展原因值, 则需要加入临时被禁列表中 */
    /* 判断是否需要加入Roam列表中, 加入Form列表 */
    if (NAS_EMM_GRADUAL_FORB_TA_NEED_ADD_ROAM_LIST == NAS_LMM_AddTaInGradualForbTempTaList(&stCurrentTa))
    {
        /*store the current TAI in the list of "forbidden tracking areas for roaming"*/
        NAS_EMM_AddForbTa(&stCurrentTa,NAS_LMM_GetEmmInfoNetInfoForbTaForRoamAddr());
        NAS_EMMC_SendRrcCellSelectionReq(LRRC_LNAS_FORBTA_CHANGE);
        *pulIsNeedExecLteNotAllow   = NAS_EMM_YES;
    }
    else
    {
        /* 加入临时列表 */
        NAS_EMMC_SendRrcCellSelectionReq(LRRC_LNAS_FORBTA_CHANGE);
        *pulIsNeedExecLteNotAllow   = NAS_EMM_NO;
    }
    return;
}
/*****************************************************************************
 Function Name   : NAS_LMM_DelCurrTaFromGradualForbTaList
 Description     : 从Gradual Forb列表中删除TA
 Input           : pstCurrTa :需要删除的TA
 Output          : None
 Return          : None
 History         :
    1.leixiantiao 00258641      2015-07-31  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LMM_DelCurrTaFromGradualForbTaList(NAS_MM_TA_STRU   *pstCurrTa)
{
    VOS_UINT32                          ulIndex = 0;

    /* Gradual Forb优化打开, 需要把当前TA从临时列表中剔除 */
    if (NAS_EMM_YES == NAS_LMM_IsGradualForbidenOptimizationOpened())
    {
        if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatchGradualForbTaList(pstCurrTa, &ulIndex))
        {
            NAS_LMM_DelTaFromTempForbList(ulIndex);

            /* 勾出可维可测 */
            NAS_EMM_SndOmGradualForbTaInfo(pstCurrTa, NAS_LMM_GRADUAL_FORB_TA_OPERATION_TYPE_DEL);
        }
    }
    return;
}
/*****************************************************************************
 Function Name   : NAS_LMM_DelCurrTaFromGradualForbTaList
 Description     : 从Gradual Forb列表中删除TA
 Input           : pstCurrTa :需要删除的TA
 Output          : None
 Return          : None
 History         :
    1.leixiantiao 00258641      2015-07-31  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LMM_UpdateGradualForbListWithTauRejCause13(NAS_MM_TA_STRU   *pstCurrTa)
{
    if (NAS_RELEASE_R11)
    {
        if (NAS_EMM_YES == NAS_EMM_IsNeedAddForbTa())
        {
            /* 被#13拒, 需要加入Roaming 列表, 所以此时需要把Ta从临时列表中删除 */
            NAS_LMM_DelCurrTaFromGradualForbTaList(pstCurrTa);
        }
    }
    else
    {
        NAS_LMM_DelCurrTaFromGradualForbTaList(pstCurrTa);
    }
}
/*****************************************************************************
 Function Name   : NAS_LMM_ExistTaInTempTaListWithForbTimerRunning
 Description     : 判断Gradual Forb临时列表中是否存在TA惩罚定时器启动着
 Input           : None
 Output          : None
 Return          : 0: Gradual列表中不存在惩罚定时器启动着的TA
                   1: Gradual列表中存在惩罚定时器启动着的TA
 History         :
    1.leixiantiao 00258641      2015-07-31  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_LMM_ExistTaInTempTaListWithForbTimerRunning(VOS_VOID)
{
    NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST  *pstTaList     = VOS_NULL_PTR;
    VOS_UINT32                              ulLoop;
    VOS_UINT32                              ulIsExistTa   = NAS_EMM_NO;

    /* 获取临时列表 */
    pstTaList = NAS_LMM_GetGradualForbTempForbTaListAddr();

    /* 临时列表中TA个数为0, 则不存在TA在临时列表且惩罚定时器启动着 */
    if (0 == pstTaList->ulTaNum)
    {
        return NAS_EMM_NO;
    }

    for (ulLoop = 0; ulLoop < NAS_LMM_GRADUAL_FORB_MAX_TEMP_TA_NUM; ulLoop++)
    {
        if (NAS_EMM_GRADUAL_FORBIDDEN_TA_USED == pstTaList->astGradualForbTa[ulLoop].enUsedFlag)
        {
            if (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsGradualForbiddenTimerRunning(ulLoop, TI_NAS_EMM_PTL_GRADUAL_FORB_TIMER))
            {
                /* 找到TA在临时列表且惩罚定时器启动着, 退出循环*/
                ulIsExistTa   = NAS_EMM_YES;
                break;
            }
        }
    }
    return ulIsExistTa;
}
/*****************************************************************************
 Function Name   : NAS_LMM_TaMatchTempTaListWithForbTimerRunning
 Description     : 判断TA是否在Gradual Forb临时列表中且惩罚定时器启动着
 Input           : None
 Output          : None
 Return          : 1: 在临时列表中且惩罚定时器启动着
 History         :
    1.leixiantiao 00258641      2015-07-31  Draft Enact

*****************************************************************************/
NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_TaMatchTempTaListWithForbTimerRunning
(
    const NAS_MMC_TA_STRU                    *pstTa
)
{
    VOS_UINT32                      ulIndex;
    if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatchGradualForbTaList(pstTa, &ulIndex))
    {
        /* 当TA在Gradul Forb临时列表中, 且惩罚定时器在运行, 则被禁 */
        if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsGradualForbiddenTimerRunning(ulIndex, TI_NAS_EMM_PTL_GRADUAL_FORB_TIMER))
        {
            return NAS_LMM_MATCH_SUCCESS;
        }
    }
    return NAS_LMM_MATCH_FAIL;
}

/*****************************************************************************
 Function Name   : NAS_LMM_GetEmmInfoRegDomain
 Description     : 获取当前注册域
 Input           : None
 Output          : None
 Return          : 当前注册域
 History         :
    1.leixiantiao 00258641      2015-08-28  Draft Enact

*****************************************************************************/
NAS_LMM_REG_DOMAIN_ENUM_UINT32 NAS_LMM_GetEmmInfoRegDomain(VOS_VOID)
{
    NAS_EMM_PUB_INFO_STRU                   *pstEmmInfo;
    NAS_LMM_REG_DOMAIN_ENUM_UINT32          enRegDomainCur;

    pstEmmInfo = NAS_LMM_GetEmmInfoAddr();

    /* 获取当前注册域 */
    enRegDomainCur = pstEmmInfo->enRegisteredDomain;

    return enRegDomainCur;
}
/*****************************************************************************
 Function Name   : NAS_LMM_SetEmmInfoRegDomain
 Description     : 设置注册域
 Input           : enRegDomainDst : 目标注册域
 Output          : None
 Return          : None
 History         :
    1.leixiantiao 00258641      2015-08-28  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_ENUM_UINT32 enRegDomainDst)
{
    NAS_EMM_PUB_INFO_STRU                   *pstEmmInfo;
    NAS_LMM_REG_DOMAIN_ENUM_UINT32          enRegDomainCur;

    pstEmmInfo = NAS_LMM_GetEmmInfoAddr();

    /* 修改注册域前,获取当前注册域 */
    enRegDomainCur = pstEmmInfo->enRegisteredDomain;

    /* 修改注册域 */
    pstEmmInfo->enRegisteredDomain = enRegDomainDst;

    #if (VOS_WIN32 != VOS_OS_VER)
    /* 勾出可维可测 */
    NAS_LMM_SndOmRegDomainInfo(enRegDomainCur, enRegDomainDst);
    #endif
}

/*****************************************************************************
 Function Name   : NAS_LMM_IsMsgContainsSMS
 Description     : 判断空口消息是否含有未加密的短信内容
 Input           : None
 Output          : None
 Return          : VOS_UINT8
 History         :
    1.zhaochen 00308719      2015-04-02  Draft Enact
*****************************************************************************/
VOS_UINT8  NAS_LMM_IsMsgContainsSMS(VOS_UINT32 ulMsgSize, VOS_UINT8 *pstMsg)
{
    /* 如果屏蔽短信消息的NV没有打开，则直接返回不包含 */
    if (VOS_TRUE != NAS_MML_GetSmsFilterFlg())
    {
        return NAS_EMM_NO;
    }
    NAS_EMM_PUBU_LOG2_INFO("NAS_LMM_IsMsgContainsSMS: pstMsg[0]=, pstMsg[1] ="
                             , pstMsg[0] ,pstMsg[1]);
    NAS_EMM_PUBU_LOG2_INFO("NAS_LMM_IsMsgContainsSMS: pstMsg[6]=, pstMsg[7] ="
                             , pstMsg[6] ,pstMsg[7]);
    /* 此处可以读NV，若关闭则直接返回NO? */
    /* 长度为0或1时，不可能存在短信内容 */
    if (2 > ulMsgSize)
    {
        return NAS_EMM_NO;
    }
    /* 判断是否为短信 */
    if (0x07 == pstMsg[0] && (0x62 == pstMsg[1] || 0x63 == pstMsg[1]))
    {
        /* 空口消息为未加密的短信 */
        return NAS_EMM_YES;
    }
    if (0x27 == pstMsg[0])
    {
        /* 有加密和完整性保护的情况，需要判断消息长度，长度小于8则不会带有短信内容 */
        if (8 > ulMsgSize)
        {
            return NAS_EMM_NO;
        }
        /* 跳过安全头，检查消息是否为明文的短信 */
        if (0x07 == pstMsg[6] && (0x62 == pstMsg[7] || 0x63 == pstMsg[7]))
        {
            return NAS_EMM_YES;
        }
    }
    return NAS_EMM_NO;
}
/*****************************************************************************
 Function Name   : NAS_EMM_IsNotIdle
 Description     : 非IDLE态
 Input           :
 Output          :
 Return          :
 History         :
    1.yanglei  00307272      2015-11-03  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_IsNotIdle(VOS_VOID)
{
    if ((NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
        && (NAS_EMM_CONN_RELEASING != NAS_EMM_GetConnState())
        && (NAS_EMM_CONN_WAIT_SYS_INFO != NAS_EMM_GetConnState()))

    {
        return NAS_EMM_YES;
    }
    return NAS_EMM_NO;
}

/*****************************************************************************
 Function Name   : NAS_EMM_IsEhrpdOr1XRatExist
 Description     : 判断是否存在EHRPD接入技术
 Input           : VOS_VOID
 Output          : VOS_VOID
 Return          : NAS_LMM_FAIL:接入技术中无EHRPD
                   NAS_LMM_SUCC:接入技术中有EHRPD
 History         :
    1.sunjitan 00193151    2016-01-14  Mofify for CL多模互操作
*****************************************************************************/
VOS_UINT32  NAS_EMM_IsEhrpdOr1XRatExist(VOS_VOID)
{
    if (((NAS_LMM_RAT_PRIO_NULL ==  NAS_LMM_GetCurHrpdPrio())
      ||(NAS_LMM_RAT_PRIO_BUTT <= NAS_LMM_GetCurHrpdPrio()))
      &&((NAS_LMM_RAT_PRIO_NULL ==  NAS_LMM_GetCurCdma1xPrio())
      ||(NAS_LMM_RAT_PRIO_BUTT <=  NAS_LMM_GetCurCdma1xPrio())))
    {
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_IsEhrpdOr1XRatExist: EHRPD RAT NOT EXIST ");
        TLPS_PRINT2LAYER_ERROR1(NAS_EMM_IsEhrpdOr1XRatExist_ENUM, LNAS_EMM_JUDGE_FLAG, NAS_LMM_FAIL);
        return NAS_LMM_FAIL;
    }

    return NAS_LMM_SUCC;
}


/*lint +e961*/
/*lint +e960*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

/* end of 子系统+模块+文件名.c */
